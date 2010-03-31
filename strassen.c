#include <stdio.h>
#include <stdlib.h>


void standard(int dim,int a[dim][dim], int b[dim][dim], int c[dim][dim]);
void strassen(int dim, int a[dim][dim],int b[dim][dim], int c[dim][dim], int cross);
void printmat(int dim, int a[dim][dim]);
int rbyc(int dim, int a[dim][dim],int b[dim][dim], int i, int j);
void matadd(int dim, int a [dim][dim], int b[dim][dim], int c[dim][dim], int x);
void copypart(int dim1, int dim2, int x, int y, int a[dim1][dim1], int b[dim2][dim2]);



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

    int mat1 [dim][dim];
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j<dim; j++)
        {
            fscanf(inptr, "%d\n", &mat1[i][j]);
        }
    }
    int mat2 [dim][dim];
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j<dim; j++)
        {
            fscanf(inptr, "%d\n", &mat2[i][j]);
        }
    }
    int test [dim][dim];
    standard(dim,mat1, mat2,test);

    printmat(dim,test);

    
    fclose(inptr);

}

void
strassen(int dim, int x [dim][dim], int y [dim][dim], int z[dim][dim], int cross)
{
    if(dim < cross)
        standard(dim,x,y,z);
    
    //idea optimize by not allocating any memeory here.  just pass in a start
    //val and an end val and do additions in place
    
    //even only version:
    //lots of memory allocation CUT DOWN!
    int a [dim/2][dim/2]; 
    int b [dim/2][dim/2]; 
    int c [dim/2][dim/2];
    int d [dim/2][dim/2];

    int e [dim/2][dim/2];
    int f [dim/2][dim/2];
    int g [dim/2][dim/2];
    int h [dim/2][dim/2];

    copypart(dim, dim/2, 0, 0,  x, a);
    copypart(dim, dim/2, 0, dim/2,  x, b);
    copypart(dim, dim/2, dim/2, 0,  x, c);
    copypart(dim, dim/2, dim/2, dim/2,  x, d);
    copypart(dim, dim/2, 0, 0,  y, e);
    copypart(dim, dim/2, 0, dim/2,  y, f);
    copypart(dim, dim/2, dim/2, 0,  y, g);
    copypart(dim, dim/2, dim/2, dim/2,  y, h);

   // int p1 [dim/2][dim/2] = strassen(dim/2 ,a,matadd(1,f,h),z,cross); 
    
}

void
copypart(int dim1, int dim2, int x, int y, int a [dim1][dim1], int b [dim2][dim2])
{
    for(int i = 0; i < dim2; i++)
    {
        for(int j = 0; j < dim2; j++)
        {
            b[i][j] = a [i+x][j+y];
        }
    }
}
void
standard(int dim, int a[dim][dim],int b[dim][dim], int c [dim][dim])
{
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j< dim; j++)
        {
          c[i][j] = rbyc(dim,a,b,i,j); 
        }
    }
}

int
rbyc(int dim, int a[dim][dim],int b[dim][dim], int i, int j)
{
    int sum = 0;
    for(int k= 0; k < dim; k++)
    {
        sum +=a[i][k] *b[k][j]; 
    }
    return sum;
}

void 
printmat(int dim, int a [dim][dim])
{
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j< dim; j++)
        {
          printf("%d ",a[i][j]); 
        }
        printf("\n");
    }

}

void
matadd(int dim, int a [dim][dim], int b[dim][dim], int c[dim][dim], int x)
{
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j< dim; j++)
        {
            if(x==0)
                c[i][j] = a[i][j] + b[i][j];
            else
                c[i][j] = a[i][j] - b[i][j];
        }
    }

}

