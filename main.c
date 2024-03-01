#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;


void ConvertToData(Data * data,char* dataStr){
    sscanf(dataStr,"%d/%d/%d",&data->giorno,&data->mese,&data->anno);

}

int checkFormato(char* data){
    int formato = 1;
    
    if (data[0] < '0' || data[0] > '9'){
        formato = 0;
    }
    
     if (data[1] < '0' || data[1] > '9'){
        formato = 0;
    }

     if (data[2] != '/'){
        formato = 0;
    }

     if (data[3] < '0' || data[3] > '9'){
        formato = 0;
    }

     if (data[4] < '0' || data[4] > '9'){
        formato = 0;
    }

     if (data[5] != '/'){
        formato = 0;
    }

     if (data[6] < '0' || data[6] > '9'){
        formato = 0;
    }
     if (data[7] < '0' || data[7] > '9'){
        formato = 0;
    }
     if (data[8] < '0' || data[8] > '9'){
        formato = 0;
    }
     if (data[9] < '0' || data[9] > '9'){
        formato = 0;
    }
    

    return formato;
}
int main(){
    Data data1;
    Data data2;
     
    
    char dataStr1[11];
    char dataStr2[11];
   
    int formato = 0;
    while (formato == 0){
        printf("inserisci la data 1: ");
        scanf("%s",dataStr1);
        //formato = checkFormato(dataStr1);   
        formato = 1;
    }

   formato = 0;

    /*while (formato == 0){
        printf("inserisci la data 2: ");
        scanf("%s",dataStr2);
        formato = checkFormato(dataStr2);   
    }*/

    sscanf(dataStr1,"%d/%d/%d",&data1.giorno,&data1.mese,&data1.anno);
    sscanf(dataStr2,"%d/%d/%d",&data2.giorno,&data2.mese,&data2.anno);

   

    printf("%d\n",data1.giorno); 
    printf("%d\n",data1.mese);
    printf("%d\n",data1.anno);

    

}