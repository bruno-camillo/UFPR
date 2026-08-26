#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp) {
    char next_option;
    while ((next_option = getopt(argc, argv, "a::n:")) != -1) {
        switch (next_option) {
        // -a imprime na tela todas as variaveis de ambiente
        case 'a':
            printf("-a foi incluído, seu valor associado é: %s\n", optarg);
            printf("Variáveis de ambiente:\n");
            for (int i = 0; envp[i] != NULL; i++) {
                printf("%s\n", envp[i]);
            }
            break;
        // -n imprime na tela as n primeiras variaveis de ambiente, onde n é o valor associado a -n
        case 'n':
            printf("-n foi incluído, seu valor associado é: %s\n", optarg);
            printf("As %s primeiras variáveis de ambiente são:\n", optarg);
            for (int i = 0; i < atoi(optarg) && envp[i] != NULL; i++) {
                printf("%s\n", envp[i]);
            }
            break;
        default:
            perror("%Argumentos: -a [Valor Op.] -n [Valor Ob.]\n");
            return 1;
        }
    }
    return 0;
}