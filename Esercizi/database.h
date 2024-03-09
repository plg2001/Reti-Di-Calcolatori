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
} IndexNodeString;

// This is a node of an index that hold an int
typedef struct IndexNodeInt {
    int value;
    struct IndexNodeInt * left;
    struct IndexNodeInt * right;
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
IndexNodeInt* create_NodeInt(int value){
    IndexNodeInt* ris = malloc(sizeof(IndexNodeInt));
    ris->value = value;
    ris->left = NULL;
    ris->right = NULL;
    
    return ris;
}
IndexNodeString* create_NodeStr(char* value){
    IndexNodeString* ris = malloc(sizeof(IndexNodeString));
    ris->value = value;
    ris->left = NULL;
    ris->right = NULL;

    return ris;
}
Database* create_database(Persona* persona){
    Database* D = malloc(sizeof(Database));
    D->address = create_NodeStr(persona->address);
    D->name = create_NodeStr(persona->name);
    D->surname = create_NodeStr(persona->surname);
    D->age = create_NodeInt(persona->age);
    return D;
}


void insert_inorder(IndexNodeString* TreeString ,char* value){
    if(TreeString == NULL){
        return;
    }

    if(strcmp(value,TreeString->value) <= 0){
        if(TreeString->left == NULL){
            IndexNodeString * new = create_NodeStr(value);
            TreeString->left = new;
            return;
        }
        insert_inorder(TreeString->left,value);
        return;
    }

    if(strcmp(value,TreeString->value) > 0){
        if(TreeString->right == NULL){
            IndexNodeString * new = create_NodeStr(value);
            TreeString->right = new;
            return;
        }
        insert_inorder(TreeString->right,value);
        return;  
    }


}
void insert(Database * database, Persona * persona){
    if( database == NULL || persona == NULL){
        return;
    }

    // Insert ByName
    insert_inorder(database->name,persona->name);
    // Insert BySurname
    insert_inorder(database->surname,persona->surname);
    //Insert ByAddress
    insert_inorder(database->address,persona->address);


}
Persona* findByName(Database * database, char * name){
    if(database->name->left->value == name){
        return create_Persona(database->name->left->value,database->surname->left->value,database->address->left->value,database->age->left->value);
    }
}
Persona* findBySurname(Database * database, char * surname);
Persona* findByAddress(Database * database, char * address);
Persona* findByAge(Database * database, int age);

