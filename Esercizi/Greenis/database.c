#include <stdlib.h>
#include <stdio.h>
#include "database.h"


// TODO implement the following methods
// The method return a Persona or NULL 
Persona* create_Persona( char* name,char* surname,char* address,int age){
    Persona* p = malloc(sizeof(Persona));
    p->age = age;
    strncpy(p->name,name,strlen(name));
    strncpy(p->surname,surname,strlen(surname));
    strncpy(p->address,address,strlen(address));
    return p;
}
IndexNodeInt* create_NodeInt(int value,Persona* Persona){
    IndexNodeInt* ris = malloc(sizeof(IndexNodeInt));
    ris->value = value;
    ris->left = NULL;
    ris->right = NULL;
    ris->persona = Persona;
    return ris;
}
IndexNodeString* create_NodeStr(char* value,Persona* Persona){
    IndexNodeString* ris = malloc(sizeof(IndexNodeString));
    ris->value = value;
    ris->left = NULL;
    ris->right = NULL;
    ris->persona = Persona;
    return ris;
}
Database* create_database(Persona* persona){
    Database* D = malloc(sizeof(Database));
    D->address = create_NodeStr(persona->address,persona);
    D->name = create_NodeStr(persona->name,persona);
    D->surname = create_NodeStr(persona->surname,persona);
    D->age = create_NodeInt(persona->age,persona);
    return D;
}


void insert_inorder(IndexNodeString* TreeString ,char* value,Persona* persona){
    if(TreeString == NULL){
        return;
    }

    if(strcmp(value,TreeString->value) <= 0){
        if(TreeString->left == NULL){
        
            IndexNodeString * new = create_NodeStr(value,persona);
            TreeString->left = new;
            return;
        }
        
        insert_inorder(TreeString->left,value,persona);
        return;
    }

    if(strcmp(value,TreeString->value) > 0){
        if(TreeString->right == NULL){
            IndexNodeString * new = create_NodeStr(value,persona);
            TreeString->right = new;
            return;
        }
        insert_inorder(TreeString->right,value,persona);
        return;  
    }


}

void insert_inorder_int(IndexNodeInt* TreeInt ,int value,Persona* persona){
    if(TreeInt == NULL){
        return;
    }

    if(value <= TreeInt->value){
        if(TreeInt->left == NULL){
            IndexNodeInt * new = create_NodeInt(value,persona);
            TreeInt->left = new;
            return;
        }
        
        insert_inorder_int(TreeInt->left,value,persona);
        return;
    }

    if(value > TreeInt->value){
        if(TreeInt->right == NULL){
            IndexNodeInt * new = create_NodeInt(value,persona);
            TreeInt->right = new;
            return;
        }
        insert_inorder_int(TreeInt->right,value,persona);
        return;  
    }


}

Persona* find_in_order(IndexNodeString* TreeString,char* key){
    if (TreeString == NULL) return NULL;

    if(strcmp(TreeString->value,key) == 0) return TreeString->persona;

    if(strcmp(key,TreeString->value) <= 0){
        return find_in_order(TreeString->left,key);
    }

    else return find_in_order(TreeString->right,key);
    
}
Persona* find_in_order_int(IndexNodeInt* TreeInt,int key){
    if (TreeInt == NULL) return NULL;

    if(TreeInt->value == key) return TreeInt->persona;

    if(key <= TreeInt->value){
        return find_in_order_int(TreeInt->left,key);
    }

    else return find_in_order_int(TreeInt->right,key);
    
}

void insert(Database * database, Persona * persona){
    if( database == NULL || persona == NULL){
        return;
    }

    // Insert ByName
    insert_inorder(database->name,persona->name,persona);
    // Insert BySurname
    insert_inorder(database->surname,persona->surname,persona);
    //Insert ByAddress
    insert_inorder(database->address,persona->address,persona);
    //Insert ByInt
    insert_inorder_int(database->age,persona->age,persona);


}
Persona* findByName(Database * database, char * name){
    Persona * ris = find_in_order(database->name,name);
    if(ris ==  NULL) {
        printf("Non Trovato\n"); 
        return NULL;
    }
    return ris;
  
}
Persona* findBySurname(Database * database, char * surname){
    Persona * ris = find_in_order(database->surname,surname);
    if(ris ==  NULL) {
        printf("Non Trovato\n"); 
        return NULL;
    }
    return ris;
}
Persona* findByAddress(Database * database, char * address){
   Persona * ris = find_in_order(database->address,address);
    if(ris ==  NULL) {
        printf("Non Trovato\n"); 
        return NULL;
    }
    return ris;
}
Persona* findByAge(Database * database, int age){
   Persona * ris = find_in_order_int(database->age,age);
    if(ris ==  NULL) {
        printf("Non Trovato\n"); 
        return NULL;
    }
    return ris; 
}

