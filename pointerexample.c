#include <stdio.h>

int main() {
    int number = 67; //make an integer that is totally random
    int *pNumber; //make a scary pointer to sixty seven
    
    pNumber = &number; //store address of number in pNumber pointer 
    
    //now lets print stuff
    printf("value of number: %d\n", number); //should give 67
    printf("address of number: %p\n", &number); //should be some memory address
    printf("address stored in the pointer number: %p\n", pNumber);//should give the same memory address as above
    printf("value accessed through the pointer number: %d\n", *pNumber);//should give 67
    
    // now lets change the pointer's value
    *pNumber = 6969;
    printf("updated value of number after changing pointer: %d\n", number); //should give 6969
    
    return 0;
}
