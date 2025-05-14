#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALUNOS 100

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void pause() {
    #ifdef _WIN32
        system("pause");
    #else
        printf("Pressione ENTER para continuar...");
        while(getchar() != '\n');
        getchar();
    #endif
}

struct Aluno {
    char nome[50];
    int rgm;
    float notas[3]; // A1, A2 e AF
    float media;
};

void calcularMedia(struct Aluno *aluno) {
    float a1 = aluno->notas[0];
    float a2 = aluno->notas[1];
    float media = a1 + a2;

    if (media < 6.0) {
        printf("Aluno com média %.2f precisa fazer AF.\n", media);

        do {
            printf("Digite a nota da AF (0 a 5): ");
            scanf("%f", &aluno->notas[2]);
            if (aluno->notas[2] < 0 || aluno->notas[2] > 5)
                printf("Nota inválida! Digite um valor entre 0 e 5.\n");
        } while (aluno->notas[2] < 0 || aluno->notas[2] > 5);

        if (a1 < a2)
            aluno->notas[0] = aluno->notas[2];
        else
            aluno->notas[1] = aluno->notas[2];
    }

    aluno->media = aluno->notas[0] + aluno->notas[1];

    if (aluno->media >= 6.0)
        printf("Aluno aprovado com média %.2f!\n", aluno->media);
    else
        printf("Aluno reprovado com média %.2f.\n", aluno->media);
}

void cadastrarAluno(struct Aluno alunos[], int *numAlunos) {
    if (*numAlunos >= MAX_ALUNOS) {
        printf("Limite de alunos atingido!\n");
        return;
    }

    struct Aluno novoAluno;
    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]", novoAluno.nome);

    printf("Digite a RGM do aluno: ");
    scanf("%d", &novoAluno.rgm);

    do {
        printf("Digite a nota A1 (0 a 5): ");
        scanf("%f", &novoAluno.notas[0]);
        if (novoAluno.notas[0] < 0 || novoAluno.notas[0] > 5)
            printf("Nota inválida! Digite um valor entre 0 e 5.\n");
    } while (novoAluno.notas[0] < 0 || novoAluno.notas[0] > 5);

    do {
        printf("Digite a nota A2 (0 a 5): ");
        scanf("%f", &novoAluno.notas[1]);
        if (novoAluno.notas[1] < 0 || novoAluno.notas[1] > 5)
            printf("Nota inválida! Digite um valor entre 0 e 5.\n");
    } while (novoAluno.notas[1] < 0 || novoAluno.notas[1] > 5);

    novoAluno.notas[2] = 0.0;

    calcularMedia(&novoAluno);
    alunos[*numAlunos] = novoAluno;
    (*numAlunos)++;
    printf("\nAluno cadastrado com sucesso!\n");
    pause();
}

void listarAlunos(struct Aluno alunos[], int numAlunos) {
    if (numAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Alunos ---\n");
    for (int i = 0; i < numAlunos; i++) {
        printf("Aluno %d:\n", i + 1);
        printf("Nome: %s\n", alunos[i].nome);
        printf("RGM: %d\n", alunos[i].rgm);
        printf("Notas: A1 = %.2f, A2 = %.2f, AF = %.2f\n",
               alunos[i].notas[0], alunos[i].notas[1], alunos[i].notas[2]);
        printf("Média: %.2f\n", alunos[i].media);
        printf("Status: %s\n\n", alunos[i].media >= 6.0 ? "Aprovado" : "Reprovado");
        pause();
    }
}

void atualizarAluno(struct Aluno alunos[], int numAlunos) {
    int matricula, encontrado = 0;
    printf("Digite a RGM do aluno que deseja atualizar: ");
    scanf("%d", &matricula);

    for (int i = 0; i < numAlunos; i++) {
        if (alunos[i].rgm == matricula) {
            printf("Aluno encontrado! Atualize as informações.\n");

            printf("Novo nome: ");
            scanf(" %[^\n]", alunos[i].nome);

            do {
                printf("Nova nota A1 (0 a 5): ");
                scanf("%f", &alunos[i].notas[0]);
                if (alunos[i].notas[0] < 0 || alunos[i].notas[0] > 5)
                    printf("Nota inválida! Digite um valor entre 0 e 5.\n");
            } while (alunos[i].notas[0] < 0 || alunos[i].notas[0] > 5);

            do {
                printf("Nova nota A2 (0 a 5): ");
                scanf("%f", &alunos[i].notas[1]);
                if (alunos[i].notas[1] < 0 || alunos[i].notas[1] > 5)
                    printf("Nota inválida! Digite um valor entre 0 e 5.\n");
            } while (alunos[i].notas[1] < 0 || alunos[i].notas[1] > 5);

            do {
                printf("Nota AF (0 a 5): ");
                scanf("%f", &alunos[i].notas[2]);
                if (alunos[i].notas[2] < 0 || alunos[i].notas[2] > 5)
                    printf("Nota inválida! Digite um valor entre 0 e 5.\n");
            } while (alunos[i].notas[2] < 0 || alunos[i].notas[2] > 5);

            calcularMedia(&alunos[i]);
            printf("Informações do aluno atualizadas com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno com RGM %d não encontrado.\n", matricula);
    }
    pause();
}

void excluirAluno(struct Aluno alunos[], int *numAlunos) {
    int matricula, encontrado = 0;
    printf("Digite a RGM do aluno que deseja excluir: ");
    scanf("%d", &matricula);

    for (int i = 0; i < *numAlunos; i++) {
        if (alunos[i].rgm == matricula) {
            for (int j = i; j < *numAlunos - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*numAlunos)--;
            printf("Aluno excluído com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno com RGM %d não encontrado.\n", matricula);
    }
    pause();
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct Aluno alunos[MAX_ALUNOS];
    int numAlunos = 0;
    int opcao;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Listar Alunos\n");
        printf("3. Atualizar Aluno\n");
        printf("4. Excluir Aluno\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarAluno(alunos, &numAlunos);
                break;
            case 2:
                listarAlunos(alunos, numAlunos);
                break;
            case 3:
                atualizarAluno(alunos, numAlunos);
                break;
            case 4:
                excluirAluno(alunos, &numAlunos);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

