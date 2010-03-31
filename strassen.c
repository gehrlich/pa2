#include <stdio.h>
#include <stdlib.h>

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
    
    fclose(inptr);

}


void
strassen(int a [][], int b [][], int c[][])
{
}

void
standard(int a[][],int b[][], int c [][], int dim)
{
    for(int i = 0; i < dim; i++)
    {
        for(j = 0; j< dim; j++)
        {
          c[i][j] = rbyc(a,b,i,j); 
        }
    }
}

int
rbyc(int a[][],int b[][], int i, int j, int dim)
{
    int sum = 0;
    for(int k= 0; k < dim; k++)
    {
        sum +=a[i][k] *b[k][j]; 
    }
    return sum;:
}
