#include <unistd.h>  // for sbrk()
#include <stddef.h>  // for size_t
#include <stdio.h> 

typedef struct Block{
    size_t size;
    int free;
    struct Block* next;
} Block;

void* my_malloc(size_t size){
    Block* head = NULL;
    Block* curr = head
    while (curr!=NULL){
        if(curr->free && curr->size>=size){
            curr->free = 0;
            return (void*)(curr+1);
        } 
        curr = curr->next;
    }

}
int main(){
    int* nums = (int*)my_malloc(5*sizeof(int));

    if( nums == NULL){
        printf("malloc failed \n");
        return 1;
    }
    for(int i =0;i<5;i++){
        nums[i]=i*10;
    }
    for(int i = 0;i<5;i++){
        printf("nums[%d]=%d\n",i,nums[i]);
    }
    return 0;
}