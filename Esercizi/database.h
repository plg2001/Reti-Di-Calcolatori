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

Database* create_database(){
    Database* D = malloc(sizeof(Database));
    D->address = NULL;
    D->age = NULL;
    D->name = NULL;
    D->surname = NULL;

    return D;
}

void insert(Database * database, Persona * persona){
    if( database == NULL || persona == NULL){
        return;
    }
    
    if(strcmp(database->name->value,persona->name) > 0){
        if(database->name->left == NULL){
            
        }
    }


}
Persona* findByName(Database * database, char * name);
Persona* findBySurname(Database * database, char * surname);
Persona* findByAddress(Database * database, char * address);
Persona* findByAge(Database * database, int age);
