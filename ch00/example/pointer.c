#include <stdio.h>


int pointer_one(void){

    int x = 10;     // определяем переменную
    int *p;         // определяем указатель
    p = &x;         // указатель получает адрес переменной

    // Какой именно адрес имеет переменная x? Для вывода значения указателя можно использовать специальный спецификатор %p
    printf("Address = %p \n", (void*) p); // 0060FEA8
    printf("x = %d \n", *p);

    return 0;

}

int pointer_one_one(){

    char c = 'N';
    int d = 10;
    short s = 2;

    char *pc = &c;          // получаем адрес переменной с типа char
    int *pd = &d;           // получаем адрес переменной d типа int
    short *ps = &s;         // получаем адрес переменной s типа short

    printf("Variable c: address=%p \t value=%c \n", (void*) pc, *pc);
    printf("Variable d: address=%p \t value=%d \n", (void*) pd, *pd);
    printf("Variable s: address=%p \t value=%hd \n", (void*) ps, *ps);

    return 0;

}

int pointer_two(){

    int a = 10;

    int *pa = &a;
    int *pb = pa;

    *pa = 25;

    printf("Value on pointer pa: %d \n", *pa);  // 25
    printf("Value on pointer pb: %d \n", *pb);  // 25
    printf("Value of variable a: %d \n", a);    // 25

    return 0;
}




int pointer_three(){
    int a = 123;
    int *p1 = &a;

    //Теперь p2 хранит тот же адрес, что и p1.
    int *p2 = &a;

    *p1 -= 3; // a = 123 - 3.
    printf("*p2 = %d\n", *p2); //Выведет 120

    return 0;
}

int pointer_four(){

    int x = 123;
    int *ip = &x;                   // указатель хранит адрес объекта int
    void *vp = ip;                  // void-указатель получает адрес из указателя ip
    printf("vp: %p\n", vp);         // получаем адрес, который хранится в указателе vp
    printf("ip: %p\n", (void*)ip);  // преобразование к типу void* - получаем адрес из указателя ip

    return 0;

}

int pointer_five(){

    int a = 10;
    int *pa = &a;
    printf("address of pointer=%p \n",  (void*)&pa);  // адрес указателя
    printf("address in pointer=%p \n",  (void*)pa);   // адрес, который хранится в указателе - адрес переменной a
    printf("value on pointer=%d \n", *pa);            // значение по адресу в указателе - значение переменной a

    return 0;
}

int pointer_vife_one(){
    int n = 10;

    int *ptr = &n;
    printf("address=%p \t value=%d \n", (void*)ptr, *ptr);

    ptr++;
    printf("address=%p \t value=%d \n", (void*)ptr, *ptr);

    ptr--;
    printf("address=%p \t value=%d \n", (void*)ptr, *ptr);

    return 0;

    /*
     *  address=0060FEA8	value=10
        address=0060FEAC	value=6356652
        address=0060FEA8	value=10
    */
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

    return 0;
}

int pointer_eight(){

    int A[2] = {100, 200};
    const int *a0 = A;
    printf("content of a0 = %d\n", *a0);

    //*a0 *= 10; //error: cannot change constant value.

    a0 = (A + 1); // A[1]
    printf("content of a0 = %d\n", *a0); //prints: A[1]

    return 0;
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

    return 0;
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

    return 0;
}

int pointer_array_one(){

    int array[5] = {1, 2, 3, 4, 5};

    for(int i = 0; i < 5; i++)
    {
        void* address = array + i;  // получаем адрес i-го элемента массива
        int value = *(array + i);   // получаем значение i-го элемента массива
        printf("array[%d]: address=%p \t value=%d \n", i, address, value);
    }
    return 0;
}

int pointer_two_array(){
    int array[3][4] = { {1, 2, 3, 4} , {5, 6, 7, 8}, {9, 10, 11, 12}};
    int n = sizeof(array)/sizeof(array[0]);         // число строк
    int m = sizeof(array[0])/sizeof(array[0][0]);   // число столбцов

    int *final = array[0] + n * m - 1;  // указатель на самый последний элемент
    for(int *ptr=array[0], i = 1; ptr <= final; ptr++, i++)
    {
        printf("%d \t", *ptr);
        // если остаток от целочисленного деления равен 0,
        // переходим на новую строку
        if(i%m==0)
        {
            printf("\n");
        }
    }
    return 0;
}

int pointer_array_char(){

    char *fruit[] = {"apricot", "apple", "banana", "lemon", "orange"};
    for(int i=0; i < 5; i++)
    {
        printf("%s \n", fruit[i]);
    }
    return 0;
}

int pointer_pointer(){

    /*
        Указатели на указатели
        Кроме обычных указателей в языке Си мы можем создавать указатели на другие указатели.
        Если указатель хранит адрес переменной, то указатель на указатель хранит адрес указателя,
        на который он указывает. Такие ситуации еще называются многоуровневой адресацией.
        int **ptr;
        Переменная ptr представляет указатель на указатель на объект типа int.
        Две звездочки в определении указателя говорят о том, что мы имеем дело с двухуровневой адресацией.
        Например:

    */

    int  x = 22;
    int *px = &x;       // указатель px хранит адрес переменной x
    int **ppx = &px;    // указатель ppx хранит адрес указателя px

    printf("Address of px: %p \n", (void *)ppx);
    printf("Address of x: %p \n", (void *)*ppx);
    printf("Value of x: %d \n", **ppx);
    return 0;


    /*

    Здесь указатель ppx хранит адрес указателя px.
    Поэтому через выражение *ppx можно получить значение, которое хранится в указателе px - адрес переменной x.
    А через выражение **ppx можно получить значение по адресу из px, то есть значение переменной x.

    */


}

int main()
{
    pointer_array_char();


    return 0;
}
