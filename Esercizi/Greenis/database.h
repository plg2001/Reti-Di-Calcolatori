#include <string.h>
// This represent a record in the only schema of this database
typedef struct {
   char key[50];
   char value[50];
}Record;

typedef struct Node {
    Record* data;
    struct Node* left;
    struct Node* right;
} Node;

// TODO implement the following methods
// The method return a Persona or NULL 
Record* create_Record( char* key,char* value){
    Record* r = malloc(sizeof(Record));
    strncpy(r->key,key,strlen(key));
    strncpy(r->value,value,strlen(value));
    return r;
}

Node* create_Node(Record* data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;

}



/*Persona* find_in_order(IndexNodeString* TreeString,char* key){
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
*/
void set(Node* Database, Record * data){
    if( Database == NULL || data == NULL){
        return;
    }

    if(Database->data == NULL ){
        Database->data = data;
        return;
    }

    if(strcmp(data->key,Database->data->key) <= 0){
        if(Database->left == NULL){
            Database->left = create_Node(data);
            return;
        }
        
        set(Database->left,data);
        return;
    }

    if(strcmp(data->key,Database->data->key) > 0){
        if(Database->right == NULL){
            Database->right = create_Node(data);
            return;
        }
        set(Database->right,data);
        return;  
    }


}
/*Persona* findByName(Database * database, char * name){
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
*/


Node* minValueNode(Node* node) {
    Node* current = node;

    // Trova il nodo più a sinistra
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

Node* deleteNode(Node* root, char* key) {
    if (root == NULL) return root;

    // Trova il nodo da eliminare
    int cmp = strcmp(key, root->data->key);
    if (cmp < 0)
        root->left = deleteNode(root->left, key);
    else if (cmp > 0)
        root->right = deleteNode(root->right, key);
    else {
        // Se il nodo ha uno o nessun figlio
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Se il nodo ha due figli, prendi il successore in ordine (nodo più piccolo nell'albero destro)
        Node* temp = minValueNode(root->right);

        // Copia il contenuto del successore in ordine in questo nodo
        root->data = temp->data;

        // Elimina il successore in ordine
        root->right = deleteNode(root->right, temp->data->key);
    }
    return root;
}

