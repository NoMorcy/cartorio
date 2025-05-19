#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Estrutura para armazenar dados do usuário
typedef struct {
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];
} Usuario;

// Função auxiliar para pausar o sistema
void pausar() {
    printf("Pressione Enter para continuar...");
    getchar(); // espera o Enter
}

// Função para registrar usuários
int registro() {
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        Usuario usuario;
        char arquivo[50];

        printf("Digite o CPF a ser cadastrado: ");
        scanf("%39s", usuario.cpf);
        getchar(); // limpa o \n do buffer
        sprintf(arquivo, "%s.txt", usuario.cpf);

        FILE *check = fopen(arquivo, "r");
        if (check != NULL) {
            printf("Este CPF já está cadastrado.\n");
            fclose(check);
            pausar();
        } else {
            printf("Digite o nome: ");
            scanf("%39s", usuario.nome);
            getchar();

            printf("Digite o sobrenome: ");
            scanf("%39s", usuario.sobrenome);
            getchar();

            printf("Digite o cargo: ");
            scanf("%39s", usuario.cargo);
            getchar();

            FILE *file = fopen(arquivo, "w");
            if (file == NULL) {
                printf("Erro ao criar o arquivo.\n");
                pausar();
                return 1;
            }

            fprintf(file, "%s,%s,%s,%s", usuario.cpf, usuario.nome, usuario.sobrenome, usuario.cargo);
            fclose(file);

            printf("Registro salvo com sucesso!\n");
            pausar();
        }

        char resposta[10];
        printf("Deseja registrar outro usuário? (s/n): ");
        fgets(resposta, sizeof(resposta), stdin);
        continuar = resposta[0];

        system(CLEAR);
    }
    return 0;
}

// Função para consultar usuários
int consulta() {
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        char cpf[40], arquivo[50], conteudo[200];
        Usuario usuario;

        printf("Digite o CPF a ser consultado: ");
        scanf("%39s", cpf);
        getchar(); // limpa \n
        sprintf(arquivo, "%s.txt", cpf);

        FILE *file = fopen(arquivo, "r");
        if (file == NULL) {
            printf("CPF não encontrado!\n");
            pausar();
        } else {
            fgets(conteudo, sizeof(conteudo), file);
            sscanf(conteudo, "%[^,],%[^,],%[^,],%s", usuario.cpf, usuario.nome, usuario.sobrenome, usuario.cargo);

            printf("\nInformações do usuário:\n");
            printf("CPF: %s\n", usuario.cpf);
            printf("Nome completo: %s %s\n", usuario.nome, usuario.sobrenome);
            printf("Cargo: %s\n", usuario.cargo);
            fclose(file);
            pausar();
        }

        char resposta[10];
        printf("Deseja consultar outro CPF? (s/n): ");
        fgets(resposta, sizeof(resposta), stdin);
        continuar = resposta[0];

        system(CLEAR);
    }
    return 0;
}

// Função para deletar usuários
int deletar() {
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        char cpf[40], arquivo[50];

        printf("Digite o CPF a ser deletado: ");
        scanf("%39s", cpf);
        getchar(); // limpa \n
        sprintf(arquivo, "%s.txt", cpf);

        if (remove(arquivo) == 0) {
            printf("Registro deletado com sucesso!\n");
        } else {
            printf("Erro ao deletar. CPF não encontrado.\n");
        }

        pausar();

        char resposta[10];
        printf("Deseja deletar outro CPF? (s/n): ");
        fgets(resposta, sizeof(resposta), stdin);
        continuar = resposta[0];

        system(CLEAR);
    }
    return 0;
}

// Função principal com menu
int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    while (1) {
        system(CLEAR);
        printf("### Cartório da EBAC ###\n\n");
        printf("Escolha uma opção:\n");
        printf("1 - Registrar novo usuário\n");
        printf("2 - Consultar usuário\n");
        printf("3 - Deletar usuário\n");
        printf("0 - Sair\n\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o \n que fica após digitar número
        system(CLEAR);

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
                printf("Opção inválida.\n");
                pausar();
                break;
        }
    }

    return 0;
}
