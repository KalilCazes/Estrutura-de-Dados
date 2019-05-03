#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char *word;
    int count;
    struct node *next;
}node;

int main(int argc, char** argv){
    
    int i, j;
    node *root = (node*) calloc(1, sizeof(node));
    root->word = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    root->next=NULL;

    char* word = (char*) calloc(1000, sizeof(char));

    while(scanf("%s",word) != -1){

        //printf("%s ", word);

        node *current = root;
        node *last;

        if(root->next == NULL){
            
            node *new_node = (node*) calloc(1, sizeof(node));
            
            char* new_word = (char*) calloc(1000, sizeof(char));
            int current_i = 0;
            while( *word != '\0' ){
                *(new_word + current_i) = *word;
                current_i++;
                word++;
            }

            new_node->word = new_word;
            new_node->count = 1;
            new_node->next = root;
            root = new_node;
            continue;
        }

        while(current != NULL){

            j = 0;

            int ascii_letter_new = (int) *(word);
            int ascii_letter_current = (int) *(current->word);

            /*while(ascii_letter_new == ascii_letter_current && *(word) != '\0' && *(current->word) != '\0'){
                j++;
                word++;
                current->word++;
                ascii_letter_new =(int) *(word);
                ascii_letter_current = (int) *(current->word);
            }

            word-=j;
            current->word-=j;*/

            int comp = strcmp(word,current->word);
        
            if(comp == 0){
                current->count++;
                break;
            }else{    
                if(comp > 0){
                    last = current;
                    current = current->next;
                }else{
                    
                    node *new_node = (node*) calloc(1, sizeof(node));

                    char* new_word = (char*) calloc(1000, sizeof(char));
                    int current_i = 0;
                    while( *word != '\0' ){
                        *(new_word + current_i) = *word;
                        current_i++;
                        word++;
                    }

                    new_node->word = new_word;
                    new_node->count = 1;
                    new_node->next = current;

                    if(current == root){
                        root = new_node;
                    }else{
                        last->next=new_node;
                    }

                    break;
                }
            }
        }
    }

    node *current = root;
    while(current->next != NULL){
        printf("%s - %d\n", current->word, current->count);
        current = current->next;
    }

    return 0;   
}
