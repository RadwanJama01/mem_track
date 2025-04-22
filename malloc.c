#include <unistd.h>  // for sbrk()
#include <stddef.h>  // for size_t
#include <stdio.h> 

typedef struct Block{
    size_t size;
    int free;
    struct Block* next;
} Block;
Block* head = NULL; //has to be global cause we always change head in our malloc function

void my_free(void* ptr){
    if(ptr == NULL){
        return;
    }
    Block* block = (Block*)ptr-1;
    block->free = 1;
    printf("Freed block @ %p (size:%zu)\n", (void*)block,block->size);

}

void print_heap(){
    Block* curr = head;
    while (curr!=NULL){
        printf("Block @ %p | size : %zu | free %s\n", (void*)curr,curr->size, curr->free ? "yes":"no" );
        curr = curr->next;

    }
}

void* my_malloc(size_t size){
    Block* curr = head;
    // in this linked list each block is a node of memory in which we can free or allocate
    while (curr!=NULL){
        if(curr->free && curr->size>=size){
            curr->free = 0;
            return (void*)(curr+1);
        } 
        curr = curr->next;
    }
    Block* new_block = (Block*)sbrk(sizeof(Block)+size);
    if(new_block == (void*)-1){
        return NULL;
    }

    new_block->size = size;
    new_block->free = 0;
    new_block->next = NULL;

    if(head == NULL){
        head = new_block;
    } else{
        curr = head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = new_block;
    }
    return (void*)(new_block+1);


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

    print_heap();

    my_free(nums);

    print_heap();


    return 0;


}