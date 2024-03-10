#include <string.h>
// This represent a record in the only schema of this database
typedef struct {
    char name[20];
    char surname[50];
    char address[100];
    int age;
}Persona;

// This is a node of an index that hold a string
typedef struct IndexNodeString {
    char * value;
    struct IndexNodeString * left;
    struct IndexNodeString * right;
    Persona* persona;
} IndexNodeString;

// This is a node of an index that hold an int
typedef struct IndexNodeInt {
    int value;
    struct IndexNodeInt * left;
    struct IndexNodeInt * right;
    Persona* persona;
} IndexNodeInt;

// A database hold a set of records and a set of indexes
typedef struct {
    IndexNodeString * name;
    IndexNodeString * surname;
    IndexNodeString * address;
    IndexNodeInt * age;
} Database;

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
}
Persona* findBySurname(Database * database, char * surname);
Persona* findByAddress(Database * database, char * address);
Persona* findByAge(Database * database, int age){
    if(database->age->right->value == age) return database->age->right->persona;
    printf("Non trovato");
    return NULL;
}

