#include <stdio.h>


int pointer_one(void){

    int a = 12; /* usual variable */
    int * ptr = &a; /* ptr-variable which contains address of variable a */
    int **pptr = &ptr; /* ptr-variable which contains address of variable ptr */
    int aval = **pptr; /* get value by adress which is contained in pptr. */
    int aval2 = *ptr; /* get value of a by address (value of ptr) */


    return 0;
}

int pointer_two(){
    char a = 'x';
    char *pa = &a; /* save address of a into pa */
    *pa = 'H'; /* change content of variable a */
    printf("%c\n", a); /* prints: y */
}

int pointer_three(){
    int a = 123;
    int *p1 = &a;

    //Теперь p2 хранит тот же адрес, что и p1.
    int *p2 = &a;

    *p1 -= 3; // a = 123 - 3.
    printf("*p2 = %d\n", *p2); //Выведет 120
}

int pointer_four(){

    int b = 0xff;
    void *pb = &b;
    void **ppb = &pb;
    int bval1 = *((int *) pb);
    int bval2 = *((int *) *ppb);


}

int pointer_five(){

    char a = 'x';
    char *pa = &a; /* save address of a into pa */
    *pa = 'y'; /* change content of variable a */
    printf("%c\n", a); /* prints: y */
}

int pointer_six(int *a, int *b){

        if(a == NULL || b == NULL)
            return -1;
        int temp = *a;
        *a = *b;
        *b = temp;
        return 0;

}

int ponter_seven(){
        int A[2] = {40, 20};

        // A -> (int *) ptr to A[0] element, &A -> (int (*)[]) -> ptr to whole Array.
        int *ptr = A;
        printf("ptr -> A[1] = %d\n", *(ptr + 1)); // A[1] => 20.

        //Illegal usage of A.
        // int a_2 = ++A;  //expected lvalue.

        //But with ptr you can do this.
        int b_2 = *++ptr; //Now ptr contains address of A[1]. (b_2 = A[1]);

        int (*ptr2)[2] = &A; //ptr to array, not to literal element.

        //*ptr2 => get array.
        //**ptr2 => get first element of array.
        //*ptr2 + 1 => get address of second element of array.
        printf("ptr2 -> A[1] = %d\n", *( *ptr2 + 1) );

        int M[2][2] = { {1, 2} , {3, 4} };

        // (*mp)[k] => (*mp)[k] => mp[0][k].
        int (*mp)[2] = M; //again you must not add '&' to variable M.
        printf("M[0][0] = %d\n", **mp);//get array and extract it first element
        printf("M[1][0] = %d\n", **(mp + 1));//move to the address of second element
        printf("M[1][1] = %d\n", *( *(mp + 1) + 1));
}

int pointer_eight(){

        int A[2] = {100, 200};
        const int *a0 = A;
        printf("content of a0 = %d\n", *a0);

        //*a0 *= 10; //error: cannot change constant value.

        a0 = (A + 1); // A[1]
        printf("content of a0 = %d\n", *a0); //prints: A[1]

}

int pointer_nine(){

/*
Чтобы запретить менять адрес (значение переменной) указателя,
надо добавить слово const ПОСЛЕ звёздочки. Кроме того, можно добавить ключевые слова const перед и после '*',
чтобы сделать переменную фиксированной ещё сильнее, например так:


        // Переменная с постоянным адресом и постоянным содержимым.
        const int *const ptr = A; // constant address with constant content

        // Переменная с постоянным адресом (содержимое можно менять)
        int *const ptr2 = A; // constant address only.

        // Переменная с постоянным содержимым, но с изменяемым адресом (значение справа)
        const int *ptr3 = A; // constant content only (can change address (rvalue))
*/

}

int pointer_ten(){

        int *pointer;
        int *iptr1, *iptr2;
        int *iptr3, iptr4; /* iptr3 is a pointer variable, whereas iptr4 is misnamed and is an int */

        int value2 = 10;
        pointer = &value2;
        printf("Value from pointer: %d\n", *pointer);

        printf("Size of int pointer: %zu\n", sizeof (int*)); /* size 8 bytes */
        printf("Size of int variable: %zu\n", sizeof (int)); /* size 4 bytes */
        printf("Size of char pointer: %zu\n", sizeof (char*)); /* size 8 bytes */
        printf("Size of char variable: %zu\n", sizeof (char)); /* size 1 bytes */
        printf("Size of short pointer: %zu\n", sizeof (short*)); /* size 8 bytes */
        printf("Size of short variable: %zu\n", sizeof (short)); /* size 2 bytes */
        return 0;


}

int pointer_array(){
        double point[3] = {0.0, 1.0, 2.0};
        double *ptr = point;

        /* prints x 0.0, y 1.0 z 2.0 */
        printf("x %f y %f z %f\n", ptr[0], ptr[1], ptr[2]);

       // printf("length of point is %s\n", length(point));


}

int main()
{
        pointer_array();


    return 0;
}
