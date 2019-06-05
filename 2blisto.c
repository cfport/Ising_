#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define D 32

int pob(int *red,int d, float p);
int imprimir(int d, int *red);
int probas_libre(float *p_l, float B);
int pinteraccion(float *pint, float J);
int interacciones(int *red, int d, int up, int down, int left, int right)
int flip(int *red, int d, float B, float J, float *de, float *mag,float *p_l, float *pint, float *energia, float *h);
float magnetizacion(int *red, int d);
float enl(float B,float J, int d, int *red);
float el(float B, int d, int *red);


int main(int argc, char* argv[])

{
  int d;
  int *red;
  float *de;
  float *mag;
  float p;
  float *p_l;
  int *spin;
  float *pint;
  float *J;
  float h;
  int n;
  float energia;
  
  d=D;
  FILE *nc;
  p=0.5;

  

  nc=fopen("J", "w");

  if (argc==2)
   {
    sscanf(argv[1], "%d", &d);
    
   }
  else printf("\nWrong number of parameters....\n");

p_l=(float*)malloc(2*sizeof(float));
red=(int*)malloc(d*d*sizeof(int));
de=(float*)malloc(sizeof(float));
mag=(float*)malloc(sizeof(float));
spin=(int*)malloc(sizeof(int));	
h=(float*)malloc(sizeof(float));
pint=(float*)malloc(5*sizeof(float));
   


pob(red,d, p);
  


  for (J=0.1; J<0.6; J=J+0.0001) 

   {
      probas_libre(p_l, 0);
       pinteraccion(pint, J);
        flip(red, d, 0, J, de, mag, p_l, pint, energia, h);
  


  fprintf(nc, "%f %f %f \n", J, *mag, *h);

   }



  free(red);
  free(de);
  free(p_l);
  free(pint);
  free(mag);
  free(spin);
  free(h);
  fclose(nc);

 return 0;

}

float aleatorio(void)

{

   float a;
   a=((float)(rand()))/((float)(RAND_MAX));

return a;

}

int pob (int *red,int d, float p)

{
    int i;

    

    for (i=0; i<d*d; i++)
    {
        if(aleatorio()<p){
        *(red+i)=1;}
        else *(red+i)=-1;

    }

    return 0;
}

int probas_libre(float *p_l,float B)

{
	
	*p_l=exp(-2*B);
	*(p_l+1)=exp(2*B);

return 0;
}



int pinteraccion(float *pint, float J)

{  int i;
   
   for (i=0;i<5;i++)
     {
        *pint=exp(-4*(1.0-0.5*((float)(i)))*J);
      }

return 0;

}

int interacciones(int *red, int d, int up, int down, int left, int right)

{  
  
  int s_rand_i, s_rand_j;
  int c_m;
  int D_E;
 
  s_rand_i=rand()%d;
  s_rand_j=rand()%d;

  up=(s_rand_i-1+d)%d;
  down=(s_rand_i+1+d)%d;
  left=(s_rand_j-1+d)%d;
  right=(s_rand_j+1+d)%d;
 
 
D_E=(float)(J*(*(red + d*s_rand_i + s_rand_j)))*( *(red +up*d + s_rand_j)+ *(red+down*d + s_rand_j) + *(red+d*s_rand_i+left)+ *(red+d*s_rand_i+right));
c_m=*(red +up*d + s_rand_j)+ *(red+down*d + s_rand_j) + *(red+d*s_rand_i+left)+ *(red+d*s_rand_i+right);

return 0;

}



int imprimir(int d, int *red)
{

    int i,j;
    for(i=0; i<d;i++)
    {
        for(j=0; j<d; j++)
        {
            
                printf("%d ", *(red+ i*d+j));
            }
        printf("\n");
    }
    printf("\n");
    return 0;
}


int flip(int *red, int d, float B, float J, float *de, float *mag,float *p_l, float *pint, float *energia, float *h)

{ int acepto;
  int r,spin, i;
  int indice, indiceint;
  float interac;


  interac=int interacciones(red, d, up, down, left, right)
  *de=2*(float)spin*(B+J*interac); //si b es distinto de , (B+J*vecinos)
  indice=((float)spin+1)/2;								
  indiceint=(((float)spin)*interac+4)/2;	

 
  acepto=0;

  for(i=0;i<100000;i++)
     {
	 r=(int)(aleatorio()*((float)(d*d)));	
	 
	 *spin=*(red+r);
	 *de=2*(float)spin*B;
    

	//printf("%d\n", r);
	 if (*de<0.0)
	{
	   *(red+r)=(-1)*spin;
	   acepto++;
        }
	else 
        {
          
	   indice=((float)spin+1)/2;
           indiceint=(spin*c_m+4)/2;

           if (aleatorio()<(*(pint + indiceint))*(*(p_l+indice))) 

            {  *(red+r)=(-1)**(float)spin;
               acepto++;
              
            }

          }

   *(h+i+1)=*(h+i)+*de;
   *(mag+i+1)=*(mag+i)+2*(*(float)spin); 


        }


*mag=magnetizacion(red, d);
*energia=enl(B, J, d, red);
*h=el(B, d, red);


      
return acepto;
  
}


float magnetizacion(int *red, int d)

{  
   float m;
   int i;
  //cuando tengo interaccion, deberia incluir el hamiltoniano 
  
   m=0;
   
	

   for(i=0;i<d*d;i++)
     {
       m=m+(*(red+i));

      }

return m/(d*d);


}

 
float enl(float B,float J, int d, int *red)//energia no libre, cuando tengo interaccion
{
   float e;
   int i;
   
   e=0; //inicio en 0
   
   for (i=0; i<d*d; i++)
     { 
       e=e+B*(*(red+i));
     }

	
return e;
}

float el(float B, int d, int *red)//energia libre

{ 
  float e; //energia
  int i;

  e=0;	//inicio con e=0

   for(i=0;i<d*d;i++)
        {
         e=e+B*(*(red+i));
	}

return e;

}
