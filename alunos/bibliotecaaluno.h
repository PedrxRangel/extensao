
#ifndef BIBLIOTECAALUNO_H
#define BIBLIOTECAALUNO_H

#include <stdio.h>
#include "bibliotecageral.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[200];
    int matricula;
    char status[50];
    float conceito;
    char ano_conceito[20];
} ALUNO;

void lancar_nota(char* identificador);
void imprimir_historico_aluno(char* identificador);
void imprimir_aluno(ALUNO* aluno);
void menu();

void lancar_nota(char* identificador) {
    FILE *arquivo_escrita, *arquivo_escrita_dois;
    arquivo_escrita = fopen("notas_lancadas.bin", "a");
    arquivo_escrita_dois = fopen("historico_de_notas.bin", "a");

    ALUNO aluno;
    GERAL* geral = buscar_cadastro(identificador);

    if(geral == NULL){
        free(geral);
        return;
    }

    strcpy(aluno.nome, geral->nome);
    aluno.matricula = geral->matricula;

    printf("Qual eh o ano em que esse aluno alcancou esse conceito? ex:(2024) ");
    scanf("%s", aluno.ano_conceito);
    printf("Digite qual foi o conceito alcancado: ");
    scanf("%f", &aluno.conceito);

    if(aluno.conceito >= 7) {
        strcpy(aluno.status, "APROVADO");
    } else {
        strcpy(aluno.status, "REPROVADO");
    }

    fwrite(&aluno, 1, sizeof(ALUNO), arquivo_escrita);
    fwrite(&aluno, 1, sizeof(ALUNO), arquivo_escrita_dois);

    fclose(arquivo_escrita);
    fclose(arquivo_escrita_dois);
    free(geral);
}

void imprimir_historico_aluno(char* identificador) {
    FILE* arquivo_leitura = fopen("historico_de_notas.bin", "r");
    ALUNO* aluno = (ALUNO*) malloc(sizeof(ALUNO));

    int identificador_int = atoi(identificador);

    while((fread(aluno, sizeof(ALUNO), 1, arquivo_leitura) == 1)) {
        
        if((strcmp(aluno->nome, identificador) == 0) || identificador_int == aluno->matricula) {
            imprimir_aluno(aluno);
        }
    }

    fclose(arquivo_leitura);
    free(aluno);
}

void imprimir_aluno(ALUNO* aluno) {
    char comando = 0;

    printf("Nome: %s\n", aluno->nome);
    printf("Matricula: %d\n", aluno->matricula);
    printf("Situacao: %s\n", aluno->status);
    printf("Conceito: %.2f\n", aluno->conceito);
    printf("Ano referente ao conceito: %s\n", aluno->ano_conceito);

    while(comando != 'C') {
        fflush(stdin);
        printf("Digite C para continuar: ");
        scanf("%c", &comando);
    }
    
    system("cls");

}

void menu() {


    int comando = 1;
    int matricula;
    char identificador[200];

    while(comando != 0) {

        printf("SISTEMA DE MATRICULAS\n");
        printf("========================================================\n");
        printf("1 - Matricular Aluno\n2 - Excluir matricula\n3 - Buscar informacoes do aluno\n4 - Exibir as informacoes de todas as matriculas\n5 - Lancar nota\n6 - Imprimir historico de notas do aluno\n0 - Sair do sistema\n");
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
                scanf(" %d", &matricula);
                excluircadastro(matricula);    
                system("cls");
                break;
            case 3 : 
                system("cls");
                printf("Digite a matricula/nome/cpf do aluno: ");
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
                printf("Digite a matricula do aluno: ");
                fgets(identificador, 200, stdin);
                retirar_quebra(identificador);
                system("cls");

                lancar_nota(identificador);
                system("cls");
                break;
            case 6 :
                system("cls");
                printf("Digite a matricula ou o nome do aluno: ");
                fgets(identificador, 200, stdin);
                retirar_quebra(identificador);
                system("cls");

                imprimir_historico_aluno(identificador);
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


#endif