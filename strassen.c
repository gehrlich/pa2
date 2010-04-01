#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    // Super matrix
    int * mat;
    
    // Row and col of top left corner of matrix
    int r;
    int c;
    
    int dim;
    int full;
    
} sub;

sub standard(sub a, sub b);
sub strassen(sub x, sub y, int cross);
sub compose(sub tl, sub tr, sub bl, sub br);
void printmat(sub a);
int rbyc(sub a, sub b, int i, int j);
sub matadd(sub a, sub b, int x);


int main(int argc, char * argv[])
{
    char * usage = "Usage: strassen 0 dimension inputfile";
    if(argc != 4)
    {
        printf("%s\n",usage);
        return 1;
    }

    int dim = atoi(argv[2]);

    char *infile = argv[3];
    FILE *inptr = fopen(infile, "r");
    if(inptr == NULL)
    {
        fclose(inptr);
        printf("Could not open %s.\n", infile);
        return 2;
    }

    int * mat1 = malloc(dim * dim * sizeof(int));
    int * mat2 = malloc(dim * dim * sizeof(int));
    int * result = malloc(dim * dim * sizeof(int));

    if (mat1 == NULL || mat2 == NULL || result == NULL)
    {
        printf("Memory allocation failed.\n");
        return 3;
    }
    
/*    for (int i = 0; i < dim; i++)
    {
        mat1[i] = malloc(dim * sizeof(int));
        mat2[i] = malloc(dim * sizeof(int));
        result[i] = malloc(dim * sizeof(int));
        
        if (mat1[i] == NULL || mat2[i] == NULL || result[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            return 3;
        }
    }
*/
//    int mat1 [dim][dim];
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
           fscanf(inptr, "%d\n", &mat1[i * dim + j]);
        }
    }
//    int mat2 [dim][dim];
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            fscanf(inptr, "%d\n", &mat2[i * dim + j]);
        } 
    }
//    int test [dim][dim];
    
    sub a = {mat1, 0, 0, dim, dim};
    sub b = {mat2, 0, 0, dim, dim};
    
    printmat(a);
    printmat(b);
    
    sub res = strassen(a, b, 3);
    printmat(res);
    sub res2 = standard (a, b);
    printmat(res2);

/*    for (int i = 0; i < dim; i++)
    {
        free(mat1[i]);
        free(mat2[i]);
        free(result[i]);
    }

    free(mat1);
    free(mat2);
    free(result);
    fclose(inptr);
*/
}


sub
strassen(sub x, sub y, int cross)
{
    int dim = x.dim;
   // if (dim == 1)
     //   return x;
  //  printf("%d ", dim);
 
    if(dim < cross)
        return standard(x,y);
    
    //idea optimize by not allocating any memeory here.  just pass in a start
    //val and an end val and do additions in place
    
    //even only version:
    //lots of memory allocation CUT DOWN!
    sub a = {x.mat, 0, 0, dim / 2, dim};
    sub b = {x.mat, 0, dim / 2, dim / 2, dim};
    sub c = {x.mat, dim / 2, 0, dim / 2, dim};
    sub d = {x.mat, dim / 2, dim / 2, dim / 2, dim};
    sub e = {y.mat, 0, 0, dim / 2, dim};
    sub f = {y.mat, 0, dim / 2, dim / 2, dim};
    sub g = {y.mat, dim / 2, 0, dim / 2, dim};
    sub h = {y.mat, dim / 2, dim / 2, dim / 2, dim};
    
    
    sub p1 = strassen(a, matadd(f, h, -1), cross);
    sub p2 = strassen(matadd(a, b, 1), h, cross);
    sub p3 = strassen(matadd(c, d, 1), e, cross);
    sub p4 = strassen(d, matadd(g, e, -1), cross);
    sub p5 = strassen(matadd(a, d, 1), matadd(e, h, 1), cross);
    sub p6 = strassen(matadd(b, d, -1), matadd(g, h, 1), cross);
    sub p7 = strassen(matadd(a, c, -1), matadd(e, f, 1), cross);

    sub tl = matadd(matadd(p5, p4, 1), matadd(p6, p2, -1), 1);
    sub tr = matadd(p1, p2, 1);
    sub bl = matadd(p3, p4, 1);
    sub br = matadd(matadd(p5, p1, 1), matadd(p3, p7, 1), -1);
    
 //   printmat(p1);
   // printf("x\n");
//    printmat(p2);
 //   printmat(p3);
   // printf("y\n");
  //  printmat(p4);
//    printmat(p5);
 //   printf("mat 2\n");
  //  printmat(p6);
  //  printmat(p7);
//    printmat(g);
//    printmat(e);
//    printmat(d);
//    printmat(standard(d,matadd(g,e,-1)));
//    printmat(h);*/
/*
    printmat(p1);
    printmat(p2);
    printmat(p3);
    printmat(p4);
*/    return compose(tl, tr, bl, br);
   // return a;
    
}

/*
 * Compose four submatrices into one full matrix
 * Precondition: tl, tr, bl, br all have equal dimensions
 */
sub
compose(sub tl, sub tr, sub bl, sub br)
{
    // Initialize the result array on the heap
    int dim = tl.dim + bl.dim;
    int * result = malloc(dim * dim * sizeof(int));

    if (result == NULL)
    {
        printf("Memory allocation failed.\n");
        //return 3;
    }
    
/*    for (int i = 0; i < dim; i++)
    {
        result[i] = malloc(dim * sizeof(int));
        
        if (result[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            //return 3;
        }
    }
*/    
    // Compose four submatrices
    
    for (int i = 0; i < tl.dim; i++)
   {
        for (int j = 0; j < tl.dim; j++)
        {
            result[i * dim + j]         
                    = tl.mat[(i + tl.r) * tl.full + (j + tl.c)];
            result[(i + tl.dim) * dim + j]
                    = bl.mat[(i + bl.r) * bl.full + (j + bl.c)];
            result[i * dim + (j + tl.dim)]          
                    = tr.mat[(i + tr.r) * tr.full + (j + tr.c)];
            result[(i + tl.dim) * dim + (j + tl.dim)] 
                    = br.mat[(i + br.r) * br.full + (j + tr.c)];
        }
    }
    
    sub z = {result, 0, 0, dim, dim};
    return z;
    
}


/*
 * Standard method of matrix multiplication
 * Puts result of A * B into C
 */
sub
standard(sub a, sub b)
{
    int dim = a.dim;
    int * c = malloc(dim * dim * sizeof(int));
    if (c == NULL)
    {
        printf("Memory allocation failed.\n");
        //return 3;
    }
/*    for (int i = 0; i < dim; i++)
    {
        c[i] = malloc(dim * sizeof(int));
        
        if (c[i] == NULL )
        {
            printf("Memory allocation failed.\n");
           // return 3;
        }
    }
*/
    for(int i = 0; i < a.dim; i++)
    {
        for(int j = 0; j < a.dim; j++)
        {
          c[i * dim + j] = rbyc(a, b, i, j); 
        }
    }
    
    sub res = {c, 0, 0, a.dim, a.dim};
    
    return res;
}

/*
 * Matrix Multiplication helper
 * Multiplies row i of matrix a with column j of matrix b
 */
int
rbyc(sub a, sub b, int i, int j)
{
    int sum = 0;
    for(int k = 0; k < a.dim; k++)
    {
        sum += a.mat[(i + a.r) * a.full + (k + a.c)] * 
               b.mat[(k + b.r) * b.full + (j + b.c)]; 
    }
    
    return sum;
}

/*
 * Prints the contents of a matrix
 */
void 
printmat(sub a)
{
    for(int i = 0; i < a.dim; i++)
    {
        for(int j = 0; j < a.dim; j++)
        {
          printf("%3d ", a.mat[(i + a.r) * a.full + (j + a.c)]); 
        }
        printf("\n");
    }
    printf("\n");
    
}

/*
 * Adds or subtracts two matrices and stores contents in C
 */
sub
matadd(sub a, sub b, int sign)
{
    // Initialize the result array on the heap
    int dim = a.dim;
    int * result = malloc(dim * dim * sizeof(int));

    if (result == NULL)
    {
        printf("Memory allocation failed.\n");
    }
    
/*    for (int i = 0; i < dim; i++)
    {
        result[i] = malloc(dim * sizeof(int));
        
        if (result[i] == NULL)
        {
            printf("Memory allocation failed.\n");
//            return 3;
        }
    }
*/    

    // Perform the computation
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            if(sign > 0)
                result[i * dim + j] = a.mat[(i + a.r) * a.full + (j + a.c)] + 
                                      b.mat[(i + b.r) * b.full + (j + b.c)];
            else
                result[i * dim + j] = a.mat[(i + a.r) * a.full + (j + a.c)] -
                                      b.mat[(i + b.r) * b.full + (j + b.c)];
        }
    }
    
    sub z = {result, 0, 0, dim, dim};
    return z;

}
