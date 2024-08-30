#ifndef BIBLIOTECAFUNCIONARIO_H
#define BIBLIOTECAFUNCIONARIO_H

#include "bibliotecageral.h"

#define SALARIO_HORA_GERENTE 125
#define SALARIO_HORA_CONSULTOR 62.5
#define SALARIO_HORA_SEGURANCA 37.5
#define SALARIO_HORA_LIMPEZA 18.75
#define SALARIO_HORA_SECRETARIO 31.25
#define SALARIO_HORA_ESTAGIARIO 5
#define LIMITE_HORA_EXTRA_MES 40
#define LIMITE_HORA_MES 160

typedef struct{
    int matricula;
    double salario;
    int horas_trabalhadas;
    int horas_extras_trabalhadas;
} FUNCIONARIO;

void menu();
void calcular_salario(char* identificador);

void menu() {

    int comando = 1;
    int matricula;
    char identificador[200];

    while(comando != 0) {

        printf("SISTEMA DE MATRICULAS\n");
        printf("========================================================\n");
        printf("1 - Cadastrar funcionario\n2 - Excluir matricula\n3 - Buscar informacoes do funcionario\n4 - Exibir as informacoes de todas as matriculas\n5 - Calcular salario\n0 - Sair do sistema\n");
        printf("========================================================\n");
        printf("Digite a operacao que deseja realizar: ");
        scanf(" %d", &comando);
        getchar();

        switch(comando) {
            case 1 :
                system("cls");
                cadastrar();
                system("cls");
                break;
            case 2 :
                system("cls");
                printf("Digite o numero da matricula que deseja excluir: ");
                fgets(identificador, 9, stdin);
                retirar_quebra(identificador);
                matricula = atoi(identificador);
                excluircadastro(matricula);    
                system("cls");
                break;
            case 3 : 
                system("cls");
                printf("Digite a matricula/nome/cpf do funcionario: ");
                fgets(identificador, 200, stdin);
                retirar_quebra(identificador);
                system("cls");

                imprimir_cadastro(identificador);
                getchar();
                system("cls");
                break;
            case 4 :
                imprimir_todos_cadastros();
                system("cls");
                break;
            case 5 :
                system("cls");
                printf("Digite a matricula/nome/cpf do funcionario: ");
                fgets(identificador, 200, stdin);
                retirar_quebra(identificador);
                system("cls");

                calcular_salario(identificador);
                getchar();
                system("cls");
                break;
            case 0 : 
                system("cls");
                printf("Saindo do sistema...\n");
                break;
            default : 
                 system("cls");
                 printf("Tecla invalida.\nDigite uma tecla qualquer para retornar ao menu principal.\n");
                 getchar();
                 system("cls");
                 break;
        }

    }

}

void calcular_salario(char* identificador) {
    GERAL* geral = buscar_cadastro(identificador);

    if(geral == NULL){
        free(geral);
        return;
    }

    FUNCIONARIO* funcionario = (FUNCIONARIO*) malloc (sizeof(FUNCIONARIO));
    funcionario->matricula = geral->matricula;
    
    printf("Digite a quantidade de horas trabalhadas pelo funcionario: ");
    scanf("%d", &funcionario->horas_trabalhadas);

    printf("Digite a quantidade de hora extra feita pelo funcionario: ");
    scanf("%d", &funcionario->horas_extras_trabalhadas);

    int horas_totais = funcionario->horas_extras_trabalhadas + funcionario->horas_trabalhadas;

    if(strcmp(geral->funcao, "Gerente") == 0) {
        funcionario->salario = SALARIO_HORA_GERENTE * horas_totais;
    }

    if(strcmp(geral->funcao, "Consultor") == 0) {
        funcionario->salario = SALARIO_HORA_CONSULTOR * horas_totais;
    }

    if(strcmp(geral->funcao, "Seguranca") == 0) {
        funcionario->salario = SALARIO_HORA_SEGURANCA * horas_totais;
    }

    if(strcmp(geral->funcao, "Limpeza") == 0) {
        funcionario->salario = SALARIO_HORA_LIMPEZA * horas_totais;
    }

    if(strcmp(geral->funcao, "Secretario") == 0) {
        funcionario->salario = SALARIO_HORA_SECRETARIO * horas_totais;
    }

    if(strcmp(geral->funcao, "Estagiario") == 0) {
        funcionario->salario = SALARIO_HORA_ESTAGIARIO * horas_totais;
    }

    printf("O valor a ser pago ao funcionario eh: R$ %.2lf\nDigite qualquer tecla para voltar ao menu.", funcionario->salario);
    fflush(stdin);
    getchar();

    FILE* arquivo = fopen("historico_pagamento.bin", "a");
    fwrite(funcionario, 1, sizeof(FUNCIONARIO), arquivo);

    free(geral);
    fclose(arquivo);
}


#endif