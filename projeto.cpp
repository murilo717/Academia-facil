#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 50
#define MAX_TREINOS 5

// Definicao da estrutura para representar um Aluno (ID removido)
typedef struct {
    char matricula[20];
    char nome[50];
    float peso;
    float altura;
    int ativo; // 1 para ativo, 0 para inativo
    int treinos[MAX_TREINOS];
} Aluno;

// Prototipos das funcoes
void cadastrarAluno(Aluno alunos[], int *total);
void listarAlunos(const Aluno alunos[], int total);
void buscarAluno(const Aluno alunos[], int total);
void alterarAluno(Aluno alunos[], int total);
void registrarPeso(Aluno alunos[], int total);
void calcularIMC(const Aluno alunos[], int total);
void classificarIMC(float imc);
void registrarTreino(Aluno alunos[], int total);
void consultarTreinos(const Aluno alunos[], int total);
void listarAlunosAtivos(const Aluno alunos[], int total);
int encontrarAlunoPorMatricula(const Aluno alunos[], int total, const char *matricula);
void menuPrincipal();

int main() {
    Aluno alunos[MAX_ALUNOS];
    int totalAlunos = 0;
    int opcao;

    do {
        menuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1: cadastrarAluno(alunos, &totalAlunos); break;
            case 2: listarAlunos(alunos, totalAlunos); break;
            case 3: buscarAluno(alunos, totalAlunos); break;
            case 4: alterarAluno(alunos, totalAlunos); break;
            case 5: registrarPeso(alunos, totalAlunos); break;
            case 6: calcularIMC(alunos, totalAlunos); break;
            case 7: registrarTreino(alunos, totalAlunos); break;
            case 8: consultarTreinos(alunos, totalAlunos); break;
            case 9: listarAlunosAtivos(alunos, totalAlunos); break;
            case 0: printf("\nSaindo do sistema... Ate logo!\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
        printf("\nPressione Enter para continuar...");
        getchar();
    } while (opcao != 0);

    return 0;
}

void menuPrincipal() {
    printf("========================================\n");
    printf("           ACADEMIA FACIL               \n");
    printf("========================================\n");
    printf(" 1. Cadastrar Aluno\n");
    printf(" 2. Listar Todos os Alunos\n");
    printf(" 3. Buscar Aluno por Matricula\n");
    printf(" 4. Alterar Dados do Aluno\n");
    printf(" 5. Registrar Novo Peso\n");
    printf(" 6. Calcular e Exibir IMC\n");
    printf(" 7. Registrar Treino\n");
    printf(" 8. Consultar Historico de Treinos\n");
    printf(" 9. Listar Apenas Alunos Ativos\n");
    printf(" 0. Sair\n");
    printf("========================================\n");
}

int encontrarAlunoPorMatricula(const Aluno alunos[], int total, const char *matricula) {
    for (int i = 0; i < total; i++) {
        if (strcmp(alunos[i].matricula, matricula) == 0) {
            return i; // Retorna o índice do aluno no vetor
        }
    }
    return -1; // Retorna -1 se não encontrar
}

void cadastrarAluno(Aluno alunos[], int *total) {
    if (*total >= MAX_ALUNOS) {
        printf("\nLimite de alunos atingido!\n");
        return;
    }

    int idx = *total;
    char tempMatricula[20];

    printf("\nCodigo de Matricula: ");
    fgets(tempMatricula, 20, stdin);
    strtok(tempMatricula, "\n");

    // Verifica se a matrícula já existe no sistema
    if (encontrarAlunoPorMatricula(alunos, *total, tempMatricula) != -1) {
        printf("\nErro: Matricula ja cadastrada! Operacao cancelada.\n");
        return;
    }

    strcpy(alunos[idx].matricula, tempMatricula);

    printf("Nome do Aluno: ");
    fgets(alunos[idx].nome, 50, stdin);
    strtok(alunos[idx].nome, "\n");

    printf("Peso (kg): ");
    scanf("%f", &alunos[idx].peso);
    
    printf("Altura (m): ");
    scanf("%f", &alunos[idx].altura);
    getchar();

    alunos[idx].ativo = 1;

    for (int j = 0; j < MAX_TREINOS; j++) {
        alunos[idx].treinos[j] = 0;
    }

    (*total)++;
    printf("\nAluno cadastrado com sucesso! (Matricula: %s)\n", alunos[idx].matricula);
}

void listarAlunos(const Aluno alunos[], int total) {
    if (total == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }
    printf("\n--- LISTA DE ALUNOS ---\n");
    for (int i = 0; i < total; i++) {
        printf("Matricula: %s | Nome: %s | Peso: %.2fkg | Altura: %.2fm | Status: %s\n",
               alunos[i].matricula, alunos[i].nome, alunos[i].peso, alunos[i].altura,
               alunos[i].ativo ? "Ativo" : "Inativo");
    }
}

void buscarAluno(const Aluno alunos[], int total) {
    char matricula[20];
    printf("\nDigite a Matricula do aluno: ");
    fgets(matricula, 20, stdin);
    strtok(matricula, "\n");

    int idx = encontrarAlunoPorMatricula(alunos, total, matricula);

    if (idx != -1) {
        printf("Encontrado: Matricula: %s - Nome: %s\n", alunos[idx].matricula, alunos[idx].nome);
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

void alterarAluno(Aluno alunos[], int total) {
    char matriculaBusca[20];
    printf("\nDigite a Matricula atual do aluno para alterar: ");
    fgets(matriculaBusca, 20, stdin);
    strtok(matriculaBusca, "\n");

    int idx = encontrarAlunoPorMatricula(alunos, total, matriculaBusca);

    if (idx != -1) {
        char tempMatricula[20];
        printf("Nova Matricula (atual: %s): ", alunos[idx].matricula);
        fgets(tempMatricula, 20, stdin);
        strtok(tempMatricula, "\n");

        // Verifica se a nova matrícula digitada já existe e não é a dele mesmo
        int busca = encontrarAlunoPorMatricula(alunos, total, tempMatricula);
        if (busca != -1 && busca != idx) {
            printf("\nErro: Esta matricula ja pertence a outro aluno! Alteracao cancelada.\n");
            return;
        }

        strcpy(alunos[idx].matricula, tempMatricula);

        printf("Novo Nome: ");
        fgets(alunos[idx].nome, 50, stdin);
        strtok(alunos[idx].nome, "\n");
        
        printf("Status (1 para Ativo, 0 para Inativo): ");
        scanf("%d", &alunos[idx].ativo);
        getchar();

        printf("Dados atualizados com sucesso!\n");
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

void registrarPeso(Aluno alunos[], int total) {
    char matricula[20];
    printf("\nDigite a Matricula do aluno: ");
    fgets(matricula, 20, stdin);
    strtok(matricula, "\n");

    int idx = encontrarAlunoPorMatricula(alunos, total, matricula);

    if (idx != -1) {
        printf("Novo peso (kg): ");
        scanf("%f", &alunos[idx].peso);
        getchar();
        printf("Peso atualizado com sucesso!\n");
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

void classificarIMC(float imc) {
    if (imc < 18.5) printf("Classificacao: Abaixo do peso\n");
    else if (imc < 25.0) printf("Classificacao: Peso normal\n");
    else if (imc < 30.0) printf("Classificacao: Sobrepeso\n");
    else printf("Classificacao: Obesidade\n");
}

void calcularIMC(const Aluno alunos[], int total) {
    char matricula[20];
    printf("\nDigite a Matricula do aluno: ");
    fgets(matricula, 20, stdin);
    strtok(matricula, "\n");

    int idx = encontrarAlunoPorMatricula(alunos, total, matricula);

    if (idx != -1) {
        if (alunos[idx].altura <= 0) {
            printf("Altura invalida para calculo do IMC.\n");
            return;
        }
        float imc = alunos[idx].peso / (alunos[idx].altura * alunos[idx].altura);
        printf("\nAluno: %s | Matricula: %s\n", alunos[idx].nome, alunos[idx].matricula);
        printf("IMC: %.2f\n", imc);
        classificarIMC(imc);
    } else {
        printf("Aluno com a matricula '%s' nao encontrado.\n", matricula);
    }
}

void registrarTreino(Aluno alunos[], int total) {
    char matricula[20];
    int codigoTreino;
    
    printf("\nDigite a Matricula do aluno: ");
    fgets(matricula, 20, stdin);
    strtok(matricula, "\n");

    int idx = encontrarAlunoPorMatricula(alunos, total, matricula);

    if (idx != -1) {
        printf("Digite o codigo do treino (ex: 101, 102): ");
        scanf("%d", &codigoTreino);
        getchar();

        for (int j = 0; j < MAX_TREINOS; j++) {
            if (alunos[idx].treinos[j] == 0) {
                alunos[idx].treinos[j] = codigoTreino;
                printf("Treino registrado no slot %d com sucesso!\n", j + 1);
                return;
            }
        }
        printf("Historico de treinos cheio para este aluno.\n");
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

void consultarTreinos(const Aluno alunos[], int total) {
    char matricula[20];
    printf("\nDigite a Matricula do aluno: ");
    fgets(matricula, 20, stdin);
    strtok(matricula, "\n");

    int idx = encontrarAlunoPorMatricula(alunos, total, matricula);

    if (idx != -1) {
        printf("Treinos registrados para %s (Matricula: %s): ", alunos[idx].nome, alunos[idx].matricula);
        for (int j = 0; j < MAX_TREINOS; j++) {
            printf("[%d] ", alunos[idx].treinos[j]);
        }
        printf("\n");
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

void listarAlunosAtivos(const Aluno alunos[], int total) {
    printf("\n--- ALUNOS ATIVOS ---\n");
    int encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (alunos[i].ativo) {
            printf("Matricula: %s | Nome: %s\n", alunos[i].matricula, alunos[i].nome);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum aluno ativo encontrado.\n");
}