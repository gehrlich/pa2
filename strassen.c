#include <stdio.h>
#include <stdlib.h>


void standard(int dim,int a[dim][dim], int b[dim][dim], int c[dim][dim]);
void strassen(int dim, int a[dim][dim],int b[dim][dim], int c[dim][dim]);
void printmat(int dim, int a[dim][dim]);
int rbyc(int dim, int a[dim][dim],int b[dim][dim], int i, int j);

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
strassen(int dim, int a [dim][dim], int b [dim][dim], int c[dim][dim])
{
    
}

void
standard(int dim, int a[dim][dim],int b[dim][dim], int c [dim][dim])
{
    for(int i = 0; i < dim; i++)
    a{
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
