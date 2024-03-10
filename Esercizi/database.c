#include <stdlib.h>
#include <stdio.h>
#include "database.h"


int main(){
    Persona* p1 = create_Persona("Pierluca","Grasso","Via della Grotta 121",22); 
    Persona* p2 = create_Persona("Maurzio","Bellissimo","Via dell pisllo",557); 
    Database* D = create_database(p1);

    insert(D,p2);
    Persona* risultato = findByAge(D,p2->age);
    printf("%s",risultato->surname);
    
}