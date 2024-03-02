#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;


Data CalculateNewDate(Data data1,Data data2){
    Data ris;
    
    ris.giorno =floor((data1.giorno + data2.giorno)/2);
    ris.mese = floor((data1.mese + data2.mese)/2);
    ris.anno = floor((data1.anno + data2.anno)/2);

    return ris;
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
       printf("Inserisci la prima data nel formato gg/mm/aaaa: ");
        scanf("%s",dataStr1);
        formato = checkFormato(dataStr1);
        if(strlen(dataStr1)<8) formato = 0;
        if(formato == 0) printf("\nReinserisci la prima data,c'e' un errore nel formato\n");
    }


    printf("\n\n");
    formato = 0;

    while (formato == 0){
        printf("Inserisci la seconda data nel formato gg/mm/aaaa: ");
        scanf("%s",dataStr2);
        formato = checkFormato(dataStr2);  
        if(strlen(dataStr1)<8) formato = 0;
        if(formato == 0) printf("\nReinserisci la seconda data,c'e' un errore nel formato\n");
    }

    sscanf(dataStr1,"%d/%d/%d",&data1.giorno,&data1.mese,&data1.anno);
    sscanf(dataStr2,"%d/%d/%d",&data2.giorno,&data2.mese,&data2.anno);

   
    Data ris = CalculateNewDate(data1,data2);

    
    
    
    printf("%d/%d/%d",ris.giorno,ris.mese,ris.anno);

    
     
    

}