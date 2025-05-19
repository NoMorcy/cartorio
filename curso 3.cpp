#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Estrutura para armazenar dados do usu�rio
typedef struct {
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];
} Usuario;

// Fun��o auxiliar para pausar o sistema
void pausar() {
    printf("Pressione Enter para continuar...");
    getchar(); // espera o Enter
}

// Fun��o para registrar usu�rios
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
            printf("Este CPF j� est� cadastrado.\n");
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
        printf("Deseja registrar outro usu�rio? (s/n): ");
        fgets(resposta, sizeof(resposta), stdin);
        continuar = resposta[0];

        system(CLEAR);
    }
    return 0;
}

// Fun��o para consultar usu�rios
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
            printf("CPF n�o encontrado!\n");
            pausar();
        } else {
            fgets(conteudo, sizeof(conteudo), file);
            sscanf(conteudo, "%[^,],%[^,],%[^,],%s", usuario.cpf, usuario.nome, usuario.sobrenome, usuario.cargo);

            printf("\nInforma��es do usu�rio:\n");
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

// Fun��o para deletar usu�rios
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
            printf("Erro ao deletar. CPF n�o encontrado.\n");
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

// Fun��o principal com menu
int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    while (1) {
        system(CLEAR);
        printf("### Cart�rio da EBAC ###\n\n");
        printf("Escolha uma op��o:\n");
        printf("1 - Registrar novo usu�rio\n");
        printf("2 - Consultar usu�rio\n");
        printf("3 - Deletar usu�rio\n");
        printf("0 - Sair\n\n");
        printf("Op��o: ");
        scanf("%d", &opcao);
        getchar(); // limpa o \n que fica ap�s digitar n�mero
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
                printf("Op��o inv�lida.\n");
                pausar();
                break;
        }
    }

    return 0;
}
