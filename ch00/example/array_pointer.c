#include <stdio.h>

void array_pointer(){

 int arr[] = {100, 200, 4, 9, 0, 10};

    int ptr_a = *(arr + 3); // 9

    for (int i = 0; i < sizeof(arr) / sizeof(*arr); ++i )
    {
        printf(" %d ", *(arr+i));

    }


}

int pointer_const(){

    int A[2] = {100, 200};
    const int *a0 = A;
    printf("content of a0 = %d\n", *a0);

    //*a0 *= 10; //error: cannot change constant value.

    a0 = (A + 1); // A[1]
    printf("content of a0 = %d\n", *a0); //prints: A[1]

    return 0;

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


int arry_ponter_two(){
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

    return 0;
}