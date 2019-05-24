#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define D 15

int pob(int d, float p);
int imprimir(int d, int *red);
int probas_libre(float B);
int alg(int *red, int d, float B, float *de, float *mag);

int main(int argc, char* argv[])
{
  int d;
  int *red;
  float B;
  float p; 
  d=D;
  FILE *nc;
  p=0.5;

  nc=fopen("noc.dat", "w");

  if (argc==2)
   {
    sscanf(argv[1], "%d", &d);
    
   }
  else printf("\nWrong number of parameters....\n");


  pob(d, p);
  B=0.1;
  probas_libre(B);
  imprimir(d, red);


  free(red);
  fclose(nc);

 return 0;

}

float aleatorio(void)

{

   float ca;
   ca=((float)(rand()))/((float)(RAND_MAX));

return ca;

}

int pob (int d, float p)

{
    int i;
    int *red;
    red=(int*)malloc(sizeof(int));

    for (i=0; i<d*d; i++)
    {
        if(aleatorio<p)
        *(red+i)=1;
        else *(red+i)=-1;

    }

    return 0;
}

int probas_libre(float B)

{
	float *p_l;
	p_l=(float*)malloc(2*sizeof(float));
	*p_l=exp(-2*B);
	*(p_l+1)=exp(2*B);

return 0;
}


int imprimir(int d, int *red)
{

    int i,j;
    for(i=0; i<d;i++)
    {
        for(j=0; j<d; j++)
        {
            if(*(red+ i*d+j)<0)
                printf("%d ", 0);
            else
                printf("%d ", *(red +i*d+j));
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}



int alg(int *red, int d, float B, float *de, float *mag)

{ int acepto;
  int r,spin, i, indice;
  float *p_l;
  for(i=0;i<1000;i++)
     {
	 r=(int)((float)((rand())*(d*d))/(float)(RAND_MAX));	 
	 spin=*(red+r);
	 *de=2*spin*B;

	 if (de<0)
	{
	   *(red+r)=(-1)*spin;
	   acepto++;
        }
	else 
        {
	   indice=(spin+1)/2;
           if (rand()<(int)((*(p_l+indice)))*RAND_MAX) //hacer funcion que devuelva un numero random entre 0 y 1

            {  *(red+r)=(-1)*spin;
               acepto++;
              
            }

          }
 

         }

      }

return acepto;
  
}
 







