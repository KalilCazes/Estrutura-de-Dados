#include<stdio.h>
#include<stdlib.h>

int partition(int* arr, int size){

    int r = size/2;

    int * left_arr = (int*) calloc (1,sizeof(int));
    int left_size = 0;

    int * right_arr = (int*) calloc (1,sizeof(int));
    int right_size = 0;

    int i = 0;

    for(i=0;i<size;i++){
        if(arr[i] < arr[r]){
            left_arr = (int*) realloc ( left_arr, sizeof(int));
            left_arr[left_size] = arr[i];
            left_size+=1;
            
        }else if(arr[i] > arr[r]){
            right_arr = (int*) realloc ( right_arr, sizeof(int));
            right_arr[right_size] = arr[i];
            right_size+=1;
        }
    }

    for(i=0;i<size;i++){
        if(i<left_size){
            arr[i] = left_arr[i];
        } else if(i==left_size){
            arr[i] = arr[r];
        }else{
            arr[i] = right_arr[i-left_size-1];
        }
    }

    return left_size;
}

int quick_select(int* complete_array, int complete_size, int k){

    if( k < 0 || k >= complete_size){
        return -1;
    }

    int selected = -1;
    int left_overs = 0;

    int arr_size = complete_size;
    int* arr = complete_array;

    int i = 0;

    while(selected != k){

        int pivot_i = partition(arr, arr_size);

        selected = pivot_i + left_overs;

        if (selected == k){
            return arr[pivot_i];
        }else if(selected > k){
            arr_size = pivot_i;
        }else{
            left_overs += pivot_i + 1;
            arr_size -= pivot_i + 1;
            for(i=0;i<arr_size;i++){
                arr[i] = arr[pivot_i + 1 + i];
            }
        }
        
    }
}

int main(int argc, char *argv[]) {

    int* arr = (int*) calloc (1,sizeof(int));
    int read = scanf("%d", &arr[0]);

    int arr_size = 0;
    while (read != -1){
        arr_size++;
        arr = (int*) realloc ( arr, sizeof(int));
        read = scanf("%d", &arr[arr_size]);
    }

    int k = atoi(argv[2]); 
    int s = quick_select(arr, arr_size, k);
    printf("\n%d\n",s);

	return 0;
}
