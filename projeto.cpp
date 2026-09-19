#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 50
#define MAX_TREINOS 5


void cadastrarAluno();
void listarAlunos();
void buscarAluno();
void alterarAluno();
void registrarPeso();
void calcularIMC();
void classificarIMC();
void registrarTreino();
void consultarTreinos();
void listarAlunosAtivos();

int main() {
    
  
    int opcao;
    

    do {
		printf("========================================\n");
	    printf("         ???  ACADEMIA FÁCIL             \n");
	    printf("========================================\n");
	    printf(" 1. Cadastrar Aluno\n");
	    printf(" 2. Listar Todos os Alunos\n");
	    printf(" 3. Buscar Aluno por ID\n");
	    printf(" 4. Alterar Dados do Aluno\n");
	    printf(" 5. Registrar Novo Peso\n");
	    printf(" 6. Calcular e Exibir IMC\n");
	    printf(" 7. Registrar Treino (Matriz)\n");
	    printf(" 8. Consultar Historico de Treinos\n");
	    printf(" 9. Listar Apenas Alunos Ativos\n");
	    printf(" 0. Sair\n");
	    printf("========================================\n");
		
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarAluno();
                break;
            case 2:
                listarAlunos();
                break;
            case 3:
                buscarAluno();
                break;
            case 4:
                alterarAluno();
                break;
            case 5:
                registrarPeso();
                break;
            case 6:
                calcularIMC();
                break;
            case 7:
                registrarTreino();
                break;
            case 8:
                consultarTreinos();
                break;
            case 9:
                listarAlunosAtivos();
                break;
            case 0:
                printf("\nSaindo do sistema\n");
                break;
        }
    } while (opcao != 0);

    system("pause");
}


void cadastrarAluno(char nomes[][50], float pesos[], float alturas[], int ativos[], int *total) {
    if (*total >= MAX_ALUNOS) {
        printf("\nLimite de alunos atingido!\n");
        return;
    }
    
    int idx = *total;
    
    printf("\nNome do Aluno: ");
    fgets(nomes[idx], 50, stdin);
    strtok(nomes[idx], "\n"); // Remove a quebra de linha

    printf("Peso (kg): ");
    scanf("%f", &pesos[idx]);
    printf("Altura (m): ");
    scanf("%f", &alturas[idx]);
    
    ativos[idx] = 1; // Aluno entra como ativo por padrao

    (*total)++;
    printf("\nAluno cadastrado com sucesso! (ID: %d)\n", *total);
}
