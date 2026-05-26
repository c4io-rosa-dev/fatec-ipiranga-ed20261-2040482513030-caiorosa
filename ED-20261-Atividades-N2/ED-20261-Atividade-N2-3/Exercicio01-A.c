// RA: 2040482513030 - Caio Rosa
#include <stdio.h>

void trocar(int *a, int *b) {
    *a = *a + *b;   //a desreferencia: passa a guardar a soma dos valores      
    *b = *a - *b;   // *b recebe (a+b) - b_original = a_original                 
    *a = *a - *b;   // *a recebe (a+b) - novo *b (=a_original) = b_original      
}

int main(void) {
    int x = 7;
    int y = 13;

    printf("==== ANTES da troca ====\n");
    printf("x = %d  | endereco de x: %p\n", x, (void*)&x);  // &x = endereco da var x
    printf("y = %d  | endereco de y: %p\n", y, (void*)&y);  // &y = endereco da var y

    trocar(&x, &y);  // &x e &y passam os ENDERECOS das variaveis para a funcao  

    printf("\n==== DEPOIS da troca ====\n");
    printf("x = %d  | endereco de x: %p\n", x, (void*)&x);
    printf("y = %d  | endereco de y: %p\n", y, (void*)&y);

    return 0;
}
