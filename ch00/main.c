#include <stdio.h>
 
typedef struct
{
    int age;
    int salary;
    
}person;


void demo(){

    printf("\n HELLO \n");
}

 
int main(void)
{
    person tom = {0};
    tom.age = 22;
    tom.salary = 100;

    person alex = {33,1000};


    demo();

   printf("Age: %d \t salary: %d \n", tom.age, tom.salary);
   printf("Age: %d \t salary: %d \n", alex.age, alex.salary);



    return 0;
}