#include <stdio.h>    // Biblioteca de comunica��o com o usu�rio
#include <stdlib.h>   // Biblioteca para fun��es de aloca��o, system, remove etc.
#include <locale.h>   // Biblioteca para suporte a localiza��o (acentua��o)
#include <string.h>   // Biblioteca para manipula��o de strings

// Fun��o que registra um novo usu�rio criando um arquivo com nome do CPF e salvando os dados
int registro() {
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);

    strcpy(arquivo, cpf); // Usa o CPF como nome do arquivo

    // Cria o arquivo para escrita ("w" sobrescreve se existir)
    FILE *file = fopen(arquivo, "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1; // Retorna erro se n�o conseguir criar arquivo
    }

    fprintf(file, "%s,", cpf); // Escreve o CPF no arquivo
    fclose(file);              // Fecha arquivo

    printf("Digite o nome a ser cadastrado: ");
    scanf("%s", nome);

    file = fopen(arquivo, "a"); // Abre arquivo para adicionar ("a")
    fprintf(file, "%s,", nome); // Escreve o nome
    fclose(file);

    printf("Digite o sobrenome a ser cadastrado: ");
    scanf("%s", sobrenome);

    file = fopen(arquivo, "a"); // Abre arquivo para adicionar
    fprintf(file, "%s,", sobrenome); // Escreve o sobrenome
    fclose(file);

    printf("Digite o cargo a ser cadastrado: ");
    scanf("%s", cargo);

    file = fopen(arquivo, "a"); // Abre arquivo para adicionar
    fprintf(file, "%s", cargo); // Escreve o cargo (�ltimo dado, sem v�rgula no final)
    fclose(file);

    printf("Registro salvo com sucesso!\n");
    system("pause"); // Pausa para o usu�rio ver a mensagem

    return 0;
}

// Fun��o que consulta um registro existente, lendo o arquivo com o nome do CPF
int consulta() {
    setlocale(LC_ALL, "Portuguese"); // Configura acentua��o

    char cpf[40];
    char conteudo[200];

    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);

    FILE *file = fopen(cpf, "r"); // Abre arquivo para leitura

    if (file == NULL) { // Verifica se o arquivo existe
        printf("N�o foi poss�vel abrir o arquivo. CPF n�o localizado!\n");
        system("pause");
        return 1; // Retorna erro
    }

    printf("\nEssas s�o as informa��es do usu�rio:\n");

    // L� o conte�do do arquivo linha por linha e imprime na tela
    while (fgets(conteudo, 200, file) != NULL) {
        printf("%s\n", conteudo);
    }

    fclose(file);     // Fecha o arquivo
    system("pause");  // Pausa para o usu�rio ver a mensagem

    return 0;
}

// Fun��o que deleta um registro, removendo o arquivo com nome do CPF
int deletar() {
    setlocale(LC_ALL, "Portuguese"); // Configura acentua��o

    char cpf[40];

    printf("Digite o CPF a ser deletado: ");
    scanf("%s", cpf);

    // Tenta remover o arquivo, retorna 0 se sucesso
    if (remove(cpf) == 0) {
        printf("Registro deletado com sucesso!\n");
    } else {
        printf("Erro ao deletar o registro. CPF n�o encontrado.\n");
    }

    system("pause"); // Pausa para o usu�rio ver a mensagem
    return 0;
}

int main() {
    setlocale(LC_ALL, "Portuguese"); // Configura acentua��o
    int opcao;

    while (1) { // Loop infinito para mostrar menu continuamente
        system("cls"); // Limpa tela (Windows)

        // Menu principal
        printf("### Cart�rio da EBAC ###\n\n");
        printf("Escolha a op��o desejada do menu:\n\n");
        printf("\t1 - Registrar nome\n");
        printf("\t2 - Consultar nome\n");
        printf("\t3 - Deletar nome\n");
        printf("\t0 - Sair\n\n");
        printf("Op��o: ");

        scanf("%d", &opcao); // L� op��o do usu�rio
        system("cls");       // Limpa a tela novamente

        switch (opcao) {
            case 1:
                registro(); // Chama fun��o de registro
                break;

            case 2:
                consulta(); // Chama fun��o de consulta
                break;

            case 3:
                deletar();  // Chama fun��o de deletar
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                return 0;  // Sai do programa

            default:
                printf("Esta op��o n�o est� dispon�vel!\n");
                system("pause");
                break;
        }
    }

    return 0;
}

