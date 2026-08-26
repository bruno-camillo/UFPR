#include <stdio.h>
#include <string.h>

void function () {
    printf("Hello World\n");
}

int function2 (int x) {
    return x * x;
}

void funcao1 (){
    printf("Hello World\n");
}

void funcao2(){
    printf("Olá Mundo!\n");
}

void falar(char *personagem, void (*mensagem)()){
    printf("%s: ", personagem);
    mensagem();
}

int main () {
    void (*ptr)() = function;
    int (*ptr2)(int) = function2;
    int k = 2;

    ptr();
    printf("%d\n", ptr2(k));

    printf("Teste professor\n");

    char language[10] = "pt-br";
    if (!strcmp("pt-br", language)) 
        falar("Robert", funcao2);
    else if (!strcmp("en", language)) 
        falar("Robert", funcao1);
    else 
        printf("????\n");

    return 0;
}
    