#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define D 100

float integral(float x); //la integral que voy a calcular
float aleatorio(void);
float camino(float x, float delta); //caminata al azar
float aceptacion(float *x, int d, float delta, float *sumatoria); //para ver los aceptados y eso
float barrido(float x0 ,int d); //para relizar el barrido de delta


int main(int argc, char *argv[])
{
  int d;
  d=D;

  if (argc==2)
   {
    sscanf(argv[1], "%d", &d);
    
   }
  else printf("\nWrong number of parameters....\n");

srand(time(NULL));

barrido(0.5 ,d); 

return 0;
}

float integral(float x) //float
{ float I; //float
  I=exp((-x*x)/2.0);
  return I;
}

float aleatorio(void)

{

   float ca;
   ca=((float)(rand()))/((float)(RAND_MAX));

return ca;

}

//armo una caminata al azar:
float camino(float x,float delta) //float
{  float ca; //float
   float fun;

   //ca=rand();

   ca=aleatorio(); 
   fun= x+(ca-0.5)*delta;

  return fun;
}

float aceptacion(float *x, int d, float delta, float *sumatoria)
{ int i;
  float I3;
  float x1;
  float I2;//float
  int acepta;
  float pi;
 
  
  pi=3.14159;	
  i=0;
  acepta=0;
 
 while (i<d-1)
{ x1=camino(*(x+i), delta); //uso punteros porque me va a servir
  I2=-(((*(x+i))*(*(x+i)))-(x1*x1));
  if (I2<0)
  { *(x+i+1)=x1;
    acepta++;
   }
    else 
     { I3=(exp(-I2/2.0))/(2.0*delta); 
        if (rand()<I3)
           {*(x+i+1)=x1;
	    acepta++;		
            }
	else{
		*(x+i+1)=*(x+i);
	}

      }
    i++;
 }

FILE *mues=fopen("muestreo", "w");
	for(i=0;i<d;i++){
		fprintf(mues, "%f ", *(x+i));	
	}
	fprintf(mues, "\n");
*sumatoria=0;
for(i=0; i<d; i++)
{ *sumatoria=*sumatoria+ (*(x+i))*(*(x+i))/((float)d);
}

*sumatoria=sqrt(2*pi)*(*sumatoria);



return ((float)acepta)/((float)d);
fclose(mues);
}

float barrido(float x0 ,int d)
{  
   int i;
   float h; //pasito
   float d0, df;
   float *x; //igual que en *delta
   int l; //longitud del vector 
   float *sumatoria;
   float a;
   float *delta;
   
   
   
   d0=0.4; //barro delta desde aca
   df=0.8; //hasta aca
   l=1000; //cantidad de pasos en los que voy a barrer
   h=((float)(df-d0))/((float)l); 
   FILE *de=fopen("barrido", "w");
   
  sumatoria=(float*)malloc(sizeof(float));
  x=(float*)malloc(d*sizeof(float));
  delta=(float*)malloc(l*sizeof(float));
  *delta=d0;
  
  for (i=0; i<l; i++){ 
	*x=x0;
	*(delta+i)=d0+h*i;
	a=aceptacion(x, d, *(delta+i), sumatoria);
	fprintf(de, "%f %f %f\n", *(delta+i) ,*sumatoria,a);}
 
 
			
free(x);
free(delta);
fclose(de);
return 0;

}

