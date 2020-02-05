#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define NUM_HILOS 5
pthread_mutex_t lock; 
//Compilar con gcc BucketSort.c -lpthread

int I=0;
int numerocubetas;
int tamanios[100];
int contador=0;
void swap(int *xp, int *yp){ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void bubbleSort(int arr[], int n){ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 
  
void printArray(int arr[], int size){ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 

void *codigo_del_hilo(void *arreglo){
    int size;


    pthread_mutex_lock(&lock);
    printf("\n\nNumero de elementos que tiene la canasta %d: %d",contador,tamanios[contador]);
    size = tamanios[contador];//Method
    contador++;
    pthread_mutex_unlock(&lock);

 
    bubbleSort(arreglo, size);
    //printf("Se ordenaron: \n\n");
    //printArray(arreglo,size);


    pthread_exit(arreglo);
}







     

void main(int argc, char *argv[]){
    int h;
    pthread_t hilos[NUM_HILOS];
    //int id[NUM_HILOS]={1,2,3,4,5};
    int error;
    int *salida;
    int arreglogrande[3500];
    int hora = time(NULL);  
    int tamanioarreglomini;

    for(int contador = 0; contador<3500; contador++){ //Generar numeros  
  
        arreglogrande[contador] = rand()%999;  
                 
    }  


    printf("Cuantas cubetas desea");
    scanf("%d",&numerocubetas);

    tamanioarreglomini=999/numerocubetas;
    int arreglosmini[numerocubetas][3500];
    int posicion[numerocubetas];
    for(int t=0;t<numerocubetas;t++){
        posicion[t]=0;
    }

    for(int j=0;j<3500;j++){//recorre todo el arreglo grande

        for(int k=0;k<numerocubetas;k++){

        if((arreglogrande[j]>tamanioarreglomini*k) && (arreglogrande[j]<tamanioarreglomini*(k+1))){
            arreglosmini[k][posicion[k]]=arreglogrande[j];
            posicion[k]+=1;
        }


        }


    }
printf("Estos son los numeros que se generaron:\n");
for(int o=0;o<3500;o++){
    printf("%d,",arreglogrande[o]);
}
/*
for(int y=0;y<numerocubetas;y++){

printf("Tamaño de el arreglo posicion en %d, posicion: %d",y,posicion[y]);

}
*/
for(int g=0;g<numerocubetas;g++){
    tamanios[g]=posicion[g];
}

for(int o=0;o<numerocubetas;o++){
    printf("Estos son los numeros que se guardaron en la cubeta %d :\n",o);
    for(int m=0;m<100;m++){
    printf("%d,",arreglosmini[o][m]);}
}
printf("\n\n\nDEBUG\n\n\n");
for(int j=0;j<tamanios[5];j++){
    printf("%d,",arreglosmini[5][j]);
}




    for(h=0;h<numerocubetas;h++){
        error=pthread_create(&hilos[h],NULL,codigo_del_hilo,arreglosmini[h]);
        if(error){
            fprintf(stderr,"Error %d; %s\n",error,strerror(error));
            exit(-1);
        }
    }
    for(h=0;h<numerocubetas;h++){
        error=pthread_join(hilos[h],(void**)&salida);
    }
    if(error)
        fprintf(stderr, "error %d: %s\n",error,strerror(error));
    else
    {
        printf("\n\nHilo %d terminado\n",*salida);
    }
    
    printf("\n\n\nDEBUG\n\n\n");
for(int j=0;j<tamanios[5];j++){
    printf("%d,",arreglosmini[5][j]);
}




    for(int d=0;d<numerocubetas;d++){
        printf("numero de cubeta %d\n",d);
        for(int n=0;n<tamanios[d];n++){
            printf("%d, ",arreglosmini[d][n]);
        }
    }
}