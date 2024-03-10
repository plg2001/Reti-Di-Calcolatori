#include <stdlib.h>
#include <stdio.h>
#include "database.h"


int main(){
    Persona* p1 = create_Persona("Pierluca","Grasso","Via della Grotta 121",22); 
    Persona* p2 = create_Persona("Maurzio","Bellissimo","Via 1",557); 
    Persona* p3 = create_Persona("Mauro","Rossi","Via 2",13); 
    Persona* p4 = create_Persona("Elisa","Verdi","Via 3",15); 
    Persona* p5 = create_Persona("Asia","Gialli","Via 4",56); 
    Persona* p6 = create_Persona("Massimo","Bianchi","Via 5",47); 
    Persona* p7 = create_Persona("yuri","Quaranta","Via 6",44); 
    Persona* p8 = create_Persona("Ombretta","De Angelis","Via 7",21); 
    Persona* p9 = create_Persona("Angelo","Brutto","Via 8",5); 
    Persona* p10 = create_Persona("Luca","Croce","Via 9",1200);
    Persona* p11 = create_Persona("Luca","Ciao","Via 10",14);
    Database* D = create_database(p1);

    insert(D,p2);
    insert(D,p3);
    insert(D,p4);
    insert(D,p5);
    insert(D,p6);
    insert(D,p7);
    insert(D,p8);
    insert(D,p9);
    insert(D,p10);
    insert(D,p11);
    
    Persona* risultato = findByName(D,"Luca");
    if (risultato != NULL)
    {
        printf("Persona: %s\n",risultato->surname);
    }
    
    
    
}