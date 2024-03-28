#include <string.h>
// This represent a record in the only schema of this database
typedef struct {
   char key[50];
   char value[50];
}Record;

typedef struct {
    Record* Node;
    struct Database* left;
    struct Database* right;
} Database;

// TODO implement the following methods
// The method return a Persona or NULL 
Record* create_Record( char* key,char* value){
    Record* r = malloc(sizeof(Record));
    strncpy(r->key,key,strlen(key));
    strncpy(r->value,value,strlen(value));
    return r;
}

Database* create_database(){
    Database* D = malloc(sizeof(Database));
    D->Node = NULL;
    D->left = NULL;
    D->right = NULL;
    return D;
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

void set(Database * database, Record * record){
    if( database == NULL || record == NULL){
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

