#include <stdio.h>    // Biblioteca de comunica��o com o usu�rio
#include <stdlib.h>   // Biblioteca de aloca��o de espa�o em mem�ria
#include <locale.h>   // Biblioteca para suporte a localiza��o
#include <string.h>   // Biblioteca para manipula��o de strings

int registro() {
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);

    strcpy(arquivo, cpf); // Copia o CPF para usar como nome do arquivo

    FILE *file = fopen(arquivo, "w"); // Cria o arquivo
    if (file == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }

    fprintf(file, "%s,", cpf);
    fclose(file);

    printf("Digite o nome a ser cadastrado: ");
    scanf("%s", nome);

    file = fopen(arquivo, "a");
    fprintf(file, "%s,", nome);
    fclose(file);

    printf("Digite o sobrenome a ser cadastrado: ");
    scanf("%s", sobrenome);

    file = fopen(arquivo, "a");
    fprintf(file, "%s,", sobrenome);
    fclose(file);

    printf("Digite o cargo a ser cadastrado: ");
    scanf("%s", cargo);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", cargo);
    fclose(file);

    printf("Registro salvo com sucesso!\n");
    system("pause");

    return 0;
}

int consulta() {
    setlocale(LC_ALL, "Portuguese");

    char cpf[40];
    char conteudo[200];

    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);

    FILE *file = fopen(cpf, "r");

    if (file == NULL) {
        printf("N�o foi poss�vel abrir o arquivo. CPF n�o localizado!\n");
        system("pause");
        return 1;
    }

    printf("\nEssas s�o as informa��es do usu�rio:\n");

    while (fgets(conteudo, 200, file) != NULL) {
        printf("%s\n", conteudo);
    }

    fclose(file);
    system("pause");

    return 0;
}

int deletar() {
    setlocale(LC_ALL, "Portuguese");

    char cpf[40];

    printf("Digite o CPF a ser deletado: ");
    scanf("%s", cpf);

    if (remove(cpf) == 0) {
        printf("Registro deletado com sucesso!\n");
    } else {
        printf("Erro ao deletar o registro. CPF n�o encontrado.\n");
    }

    system("pause");
    return 0;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    while (1) {
        system("cls");

        printf("### Cart�rio da EBAC ###\n\n");
        printf("Escolha a op��o desejada do menu:\n\n");
        printf("\t1 - Registrar nome\n");
        printf("\t2 - Consultar nome\n");
        printf("\t3 - Deletar nome\n");
        printf("\t0 - Sair\n\n");
        printf("Op��o: ");

        scanf("%d", &opcao);
        system("cls");

        switch (opcao) {
            case 1:
                registro();
                break;

            case 2:
                consulta();
                break;

            case 3:
                deletar();
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                return 0;

            default:
                printf("Esta op��o n�o est� dispon�vel!\n");
                system("pause");
                break;
        }
    }

    return 0;
}
