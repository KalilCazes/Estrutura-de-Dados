#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char* word;
    int count;
    int search_status;
    struct node *right;
    struct node *left;
    struct node *up;
    int height;
}node;

node* root;
void balance(node* tree);

void rotacao_direita(node* tree){

    node* new_root = tree->left;
    new_root->up = tree->up;

    if (new_root->up){
        int comp = strcmp(new_root->up->right->word, tree->word);
        //printf("\nD: %s - E: %s : REAL: %s\n",new_root->up->right->word, new_root->up->left->word, tree->word);
        if(comp == 0){
            new_root->up->right = new_root;
        }else{
            new_root->up->left = new_root;
        }
    }else{
        root = new_root;
    }

    node* new_root_old_child = new_root->right;

    new_root->right = tree;
    new_root->height += 1;

    tree->up = new_root;
    tree->left = new_root_old_child;
    if(new_root_old_child){
        new_root_old_child->up = tree;
    }
    tree->height -= 1;

    //printf("\nNew root: %s - Right: %s - Left: %s\n", new_root->word, new_root->right->word, new_root->left->word);
    
    balance(new_root);
}

void rotacao_dupla_direita(node* tree){

    node* new_root = tree->left->right;
    new_root->up = tree->up;

    if (new_root->up){
        int comp = strcmp(new_root->up->right->word, tree->word);
        if(comp == 0){
            new_root->up->right = new_root;
        }else{
            new_root->up->left = new_root;
        }
    }else{
        root = new_root;
    }

    node* new_root_old_left_child = new_root->left;
    node* new_root_old_right_child = new_root->right;

    node* tree_left = tree->left;

    new_root->right = tree;
    new_root->left = tree_left;
    new_root->height += 2;

    tree->up = new_root;
    tree_left->up = new_root;

    tree->left = new_root_old_right_child;
    if(new_root_old_right_child){
        new_root_old_right_child->up = tree;
    }
    tree_left->right = new_root_old_left_child;
    if(new_root_old_left_child){
        new_root_old_left_child->up = tree_left;
    }

    tree->height -= 1;
    tree_left->height -= 1;

    //printf("\nNew root: %s - Right: %s - Left: %s\n", new_root->word, new_root->right->word, new_root->left->word);
    
    balance(new_root);
} 

void rotacao_esquerda(node* tree){

    node* new_root = tree->right;
    new_root->up = tree->up;

    if (new_root->up){
        int comp = strcmp(new_root->up->right->word, tree->word);
        if(comp == 0){
            new_root->up->right = new_root;
        }else{
            new_root->up->left = new_root;
        }
    }else{
        root = new_root;
    }

    node* new_root_old_child = new_root->left;

    new_root->left = tree;
    new_root->height += 1;

    tree->up = new_root;
    tree->right = new_root_old_child;
    if(new_root_old_child){
        new_root_old_child->up = tree;
    }
    tree->height -= 1;

    //printf("\nNew root: %s - Right: %s - Left: %s\n", new_root->word, new_root->right->word, new_root->left->word);
    
    balance(new_root);

}

void rotacao_dupla_esquerda(node* tree){

    node* new_root = tree->right->left;
    new_root->up = tree->up;

    if (new_root->up){
        int comp = strcmp(new_root->up->right->word, tree->word);
        if(comp == 0){
            new_root->up->right = new_root;
        }else{
            new_root->up->left = new_root;
        }
    }else{
        root = new_root;
    }

    node* new_root_old_left_child = new_root->left;
    node* new_root_old_right_child = new_root->right;

    node* tree_right = tree->right;

    new_root->left = tree;
    new_root->right = tree_right;
    new_root->height += 2;

    tree->up = new_root;
    tree_right->up = new_root;

    tree->right = new_root_old_left_child;
    if(new_root_old_left_child){
        new_root_old_left_child->up = tree;
    }
    tree_right->left = new_root_old_right_child;
    if(new_root_old_right_child){
        new_root_old_right_child->up = tree_right;
    }

    tree->height -= 1;
    tree_right->height -= 1;

    //printf("\nNew root: %s - Right: %s - Left: %s\n", new_root->word, new_root->right->word, new_root->left->word);
    
    balance(new_root);
}

void balance(node* tree){

    int l_height = 0;
    int r_height = 0;

    if(tree->left){
        l_height = tree->left->height;
    }
    
    if(tree->right){
        r_height = tree->right->height;
    }

    //printf("\nTree: %s - Balanco: %d - l_h: %d - r_h: %d\n", tree->word, abs(r_height-l_height), l_height, r_height);

    if(abs(r_height-l_height) > 1){
        
        //printf("\nDesbalanceada - Valor: %s - ", tree->word);
        
        int tree_h = r_height-l_height;
        int child_h = 0;

        int l_child_height = 0;
        int r_child_height = 0;   

        if (tree_h > 0){

            if(tree->right->left){
                l_child_height = tree->right->left->height;
            }
            
            if(tree->right->right){
                r_child_height = tree->right->right->height;
            }

            child_h = r_child_height - l_child_height;

            if(child_h > 0){
                //printf("Rotacao: Esquerda");
                rotacao_esquerda(tree);
            }else{
                //printf("Rotacao: Dupla Esquerda");
                rotacao_dupla_esquerda(tree);
            }

        }else{

            if(tree->left->left){
                l_child_height = tree->left->left->height;
            }
            
            if(tree->left->right){
                r_child_height = tree->left->right->height;
            }

            child_h = r_child_height - l_child_height;

            if(child_h > 0){
                //printf("Rotacao: Dupla Direita");
                rotacao_dupla_direita(tree);
            }else{
                //printf("Rotacao: Direita");
                rotacao_direita(tree);
            }

        }
    
    }else{

        if (l_height > r_height){
            tree->height = 1 + l_height;
        }else{
            tree->height = 1 + r_height;
        }

        if(tree->up){
            balance(tree->up);
        }
    }
}

void insert(node* root, char* word){

    char* new_word = (char*) calloc(1000, sizeof(char));
    int current_i = 0;
    while( *word != '\0' ){
        *(new_word + current_i) = *word;
        current_i++;
        word++;
    }

    if(!root->word){
        root->word = new_word;
        root->search_status = 0;
        root->height = 1;
        root->count = 1;
        return;
    }

    int comp = strcmp(new_word, root->word);

    if(comp > 0){

        if(root->right){
            insert(root->right, new_word);
        }else{
            node* r = (node*) calloc(1, sizeof(node));
            r->word = new_word;
            r->up = root;
            r->search_status = 0;
            r->height = 1;
            r->count = 1;
            root->right = r;

            //printf("\nNovo Balanco direita: %s\n", r->word);
            balance(root);
        }

    }else{

        if(root->left){
            insert(root->left, new_word);
        }else{
            node* l = (node*) calloc(1, sizeof(node));
            l->word = new_word;
            l->up = root;
            l->search_status = 0;
            l->height = 1;
            l->count = 1;
            root->left = l;

            //printf("\nNovo Balanco esquerda: %s\n", l->word);
            balance(root);
        }

    }

}

void print_height(node* root, int type){

    if(root->search_status == 0){
        root->search_status = 1;
        if(type == 1){
            printf("\nValor = %s ; Altura = %d\n", root->word, root->height);
        }
    }

    if(root->left){

        if(root->left->search_status == 2){
            if(root->search_status != 2){
                root->search_status = 2;
                if(type == 0){
                    printf("%s - %d\n", root->word, root->count);
                }
            }
        }else{
            print_height(root->left, type);
            return;
        }

    }else{
        if(root->search_status != 2){
            root->search_status = 2;
            if(type == 0){
                printf("%s - %d\n", root->word, root->count);
            }
        }       
    }
    
    if(root->right){

        if(root->right->search_status == 2){
            if(root->up){
                print_height(root->up, type);
            }
            return;
        }else{
            print_height(root->right, type);
            return;
        }

    }

    if(root->search_status != 2){
        root->search_status = 2;
        if(type == 0){
            printf("%s - %d\n", root->word, root->count);
        }
    } 

    if(root->up){
        print_height(root->up, type);
    }
}

int find(node* tree, char* c){

    if(tree->word){
        int comp = strcmp(c, tree->word);

        if(comp==0){
            //printf("\nrepetida %s\n", c);
            tree->count+=1;
            return 1;
        }else if(comp < 0){
            if(tree->left){
                find(tree->left, c);
            }else{
                return 0;
            }
        }else{
            if(tree->right){
                find(tree->right, c);
            }else{
                return 0;
            }
        }
    }else{
        return 0;
    }
}

int main(){

    root = (node*) calloc(1, sizeof(node));

    char* word = (char*) calloc(1000, sizeof(char));

    while(scanf("%s",word) != -1){
        if(!find(root, word)){
            //printf("new: %s\n", word);
            insert(root, word);
        }
    }

    print_height(root, 0);

    return 0;

    /*int arr[] = {94, 33, 50, 76, 96, 67, 56, 65, 83, 34};
    root = (node*) calloc(1, sizeof(node));

    for(int i =0;i<10;i++){
        insert(root,arr[i]);
    }

    print_height(root,1);

    if(find(root, 23233)){
        printf("show pa!");
    }else{
        printf("show pei!");
    }*/


}