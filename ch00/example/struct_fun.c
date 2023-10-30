#include <stdio.h>
  
typedef struct
{
    char* name;
    int age;
} person;
  
void print_person(person user)
{
    printf("Name: %s \n", user.name);
    printf("Age: %d \n", user.age);
}
 
int main(void)
{
    person tom = {.name = "Tom", .age=38 };
    print_person(tom);
    return 0;
}

