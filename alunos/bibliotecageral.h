/*Essa biblioteca realiza as operações cadastrar, buscar, excluir e editar
com a estrutura "GERAL" e utiliza de algumas funções auxiliares*/

#ifndef BIBLIOTECAGERAL_H
#define BIBLIOTECAGERAL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "bibliotecaverifica.h"

int cadastrar ();
int gera_matricula(int ano_ingresso);
void excluircadastro (int matricula);
void imprimir_cadastro(char *identificador_char);
void imprimir_todos_cadastros();
void retirar_quebra(char* nome);
void acessar_sistema();
void imprimir(GERAL* cadastro);
void editar_cadastro(char* identificador_char);
int menu_editar();
GERAL* buscar_cadastro (char *identificador_char);
int calcular_idade(char* data_nascimento);


int cadastrar (){
    
    GERAL* cadastro;
    cadastro = (GERAL*) malloc(sizeof(GERAL));
    

    FILE* arquivo;
    arquivo = fopen("cadastro.bin", "a");

    if(arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        return 1;
    }

    printf("Nome completo: ");
    fgets(cadastro->nome, 200, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->nome);

    printf("Data de nascimento(ex: 05/06/2003): ");
    fgets(cadastro->data_nascimento, 15, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->data_nascimento);

    while(!(verificar_data_nascimento(cadastro->data_nascimento))) {
        printf("Data de nascimento invalida, digite uma data de nascimento valida (ex: 14/08/2003 ):\n");
        fgets(cadastro->data_nascimento, 15, stdin);
        fflush(stdin);
        retirar_quebra(cadastro->data_nascimento);
    }

    printf("Ano de ingresso: ");
    fgets(cadastro->ano_ingresso, 10, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->ano_ingresso);

    while(!(verificar_ano(cadastro->ano_ingresso))) {
        printf("Ano de ingresso invalido, digite um ano de ingresso valida (ex: 2024 ):\n");
        fgets(cadastro->ano_ingresso, 10, stdin);
        fflush(stdin);
        retirar_quebra(cadastro->ano_ingresso);
    }

    printf("Numero de telefone(ex: (021) 98765-4321): ");
    fgets(cadastro->telefone, 20, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->telefone);

    while(!(verificar_telefone(cadastro->telefone))) {
        printf("telefone invalido. Por favor, digite um telefone valido (ex: (021) 98765-4321) ):\n");
        fgets(cadastro->telefone, 20, stdin);
        fflush(stdin);
        retirar_quebra(cadastro->telefone);
    }

    printf("Informe o CPF (ex: xxx.xxx.xxx-xx): ");
    fgets(cadastro->cpf, 15, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->cpf);


    while(!(verificar_cpf(cadastro->cpf))) { //verifica se o cpf eh valido.
        printf("CPF invalido, digite um CPF valido (ex: xxx.xxx.xxx-xx):\n");
        fgets(cadastro->cpf, 15, stdin);
        fflush(stdin);
        retirar_quebra(cadastro->cpf);
    }

    printf("Funcao exercida(ex: Funcao): ");
    fgets(cadastro->funcao, 15, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->funcao);

    while(!(verifica_funcao(cadastro->funcao))) { //verifica se a função é válida.
        printf("Funçao invalida, digite uma funçao valida(ex: Funcao):\n");
        fgets(cadastro->funcao, 15, stdin);
        fflush(stdin);
        retirar_quebra(cadastro->funcao);
    }
    
    printf("Cep (ex: 26534-125): ");
    fgets(cadastro->cep, 11, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->cep);

    while(!(verificar_cep(cadastro->cep))){ //verifica se o cep eh valido.
        printf("CEP invalido, digite um CEP valido (ex: 26534-125):\n");
        fgets(cadastro->cep, 11, stdin);
        fflush(stdin);
        retirar_quebra(cadastro->cep);
    }
    
    printf("Rua: ");
    fgets(cadastro->rua, 30, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->rua);

    printf("Numero da casa: ");
    fgets(cadastro->rua_num, 5, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->rua_num);

    printf("Complemento: ");
    fgets(cadastro->complemento, 30, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->complemento);

    printf("Estado: ");
    fgets(cadastro->estado, 30, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->estado);

    printf("Cidade: ");
    fgets(cadastro->cidade, 30, stdin);
    fflush(stdin);
    retirar_quebra(cadastro->cidade);

    cadastro->matricula = gera_matricula(atoi(cadastro->ano_ingresso));

    fwrite(cadastro, sizeof(GERAL), 1, arquivo);

    fclose(arquivo);
    free(cadastro);
    
    return 0;
}

int gera_matricula(int ano_ingresso){
    FILE* arquivo;
    arquivo = fopen("cadastro.bin", "r");

    if(arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        return 1;
    }
    
    GERAL *copia;
    copia = (GERAL*) malloc (sizeof(GERAL));

    fseek(arquivo, -sizeof(GERAL), SEEK_END);

    fread(copia, sizeof(GERAL), 1, arquivo);

    int ano_matricula;
    ano_matricula = copia->matricula / 10000;

    if(ano_ingresso == ano_matricula) {
        return copia->matricula + 1;
    }

    int matricula = 0;
    matricula = ano_ingresso * 10000 + 1;

    free(copia);
    fclose(arquivo);

    return matricula;

}

void excluircadastro (int matricula) {

    FILE *arquivo, *novoarquivo;
    arquivo = fopen("cadastro.bin", "r");
    novoarquivo = fopen("novocadastro.bin", "w");

    if(arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        getchar();
        return;
    }

    GERAL *copia;
    copia = (GERAL*) malloc (sizeof(GERAL));

    while((fread(copia, sizeof(GERAL), 1, arquivo) == 1)) {

        if(copia->matricula != matricula) {
            fwrite(copia, sizeof(GERAL), 1, novoarquivo);
        }
    }

    fclose(arquivo);
    fclose(novoarquivo);
    free(copia);

    system("del cadastro.bin");
    system("rename novocadastro.bin cadastro.bin");
}

void imprimir_cadastro(char *identificador_char){

    char comando = 'A';
    FILE* arquivo;

    GERAL *individuo;

    individuo = (GERAL*) malloc(sizeof(GERAL));

    arquivo = fopen("cadastro.bin", "r");

    if(arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        return;
    }

    int identificador_int = atoi(identificador_char);
    while((fread(individuo, sizeof(GERAL), 1, arquivo) == 1)){

        if(individuo->matricula == identificador_int || !strcmp(individuo->nome, identificador_char) || !strcmp(individuo->cpf, identificador_char)){

            imprimir(individuo);

            while(comando != 'S' && comando != 'E') {
            printf("Digite 'S' para retornar ao menu principal ou 'E' caso queira editar o cadastro.\n");
            scanf("%c", &comando);
            fflush(stdin);
            }

            if(comando == 'E') {
                free(individuo);
                fclose(arquivo);
                editar_cadastro(identificador_char);
                
                free(individuo);
                fclose(arquivo);
                return;
            }
            
            printf("\nVoltando ao menu...\n");
            
            free(individuo);
            fclose(arquivo);
            return;

        }

    }

    if(!(fread(individuo, sizeof(GERAL), 1, arquivo) == 1)){
        printf("Nao foi encontrado o cadastro referente a matricula.\n");
    }

    free(individuo);
    fclose(arquivo);

}

void imprimir_todos_cadastros(){

    FILE* arquivo;

    GERAL *individuo;

    individuo = (GERAL*) malloc(sizeof(GERAL));

    arquivo = fopen("cadastro.bin", "r");
    
    if(arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        getchar();
        return;
    }

    char comando;

    while((fread(individuo, sizeof(GERAL), 1, arquivo) == 1)){
       
            system("cls");
            
            printf("DADOS DO CADASTRO: \n");
            printf("Nome: %s\n", individuo->nome);
            printf("Funcao: %s\n", individuo->funcao);
            printf("Matricula: %d\n", individuo->matricula);
            printf("Ano de ingresso: %s\n", individuo->ano_ingresso);
            printf("Telefone: %s\n", individuo->telefone);
            printf("Data de nascimento: %s\n", individuo->data_nascimento);
            printf("Idade: %d\n", calcular_idade(individuo->data_nascimento));
            printf("CPF: %s\n", individuo->cpf);
            printf("\n");

            printf("DADOS DO ENDERECO: \n");
            printf("%s %s, %s\n", individuo->rua, individuo->rua_num, individuo->complemento);
            printf("CEP: %s\n", individuo->cep);
            printf("Estado: %s\n", individuo->estado);
            printf("Cidade: %s\n", individuo->cidade);
            printf("\n");
            
            printf("Digite uma tecla qualquer para exibir a proxima matricula ou 'S' para voltar ao menu principal.\n");
            scanf(" %c", &comando);
            system("cls");

            if(comando == 'S') {
                free(individuo);
                fclose(arquivo);
                return;
            }

    }

    if(!(fread(individuo, sizeof(GERAL), 1, arquivo) == 1)){
        system("cls");
        printf("Nao ha mais matriculas cadastradas, digite uma tecla qualquer para retornar ao menu.\n");
        fflush(stdin);
        getchar();
    }

    free(individuo);

    fclose(arquivo);

}

void retirar_quebra(char* nome) {

    int i;

    for(i = 0; nome[i] != '\0'; i++) {
        if(nome[i] == '\n') {
            nome[i] = '\0';
            break;
        }
    }
}

void imprimir(GERAL* cadastro) {
            
printf("DADOS DO CADASTRO: \n");
printf("Nome: %s\n", cadastro->nome);
printf("Funcao: %s\n", cadastro->funcao);
printf("Matricula: %d\n", cadastro->matricula);
printf("Ano de ingresso: %s\n", cadastro->ano_ingresso);
printf("Telefone: %s\n", cadastro->telefone);
printf("Data de nascimento: %s\n", cadastro->data_nascimento);
printf("Idade: %d\n", calcular_idade(cadastro->data_nascimento));
printf("CPF: %s\n", cadastro->cpf);
printf("\n");

printf("DADOS DO ENDERECO: \n");
printf("%s %s, %s\n", cadastro->rua, cadastro->rua_num, cadastro->complemento);
printf("CEP: %s\n", cadastro->cep);
printf("Estado: %s\n", cadastro->estado);
printf("Cidade: %s\n", cadastro->cidade);
printf("\n");

}

void editar_cadastro(char* identificador_char) {
    int campo;
    char novo[100];
    FILE* arquivo_leitura;
    FILE* arquivo_escrita;
    GERAL *individuo;

    individuo = (GERAL*) malloc(sizeof(GERAL));

    arquivo_leitura = fopen("cadastro.bin", "r");
    arquivo_escrita = fopen("novocadastro.bin", "w");

    if(arquivo_leitura == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        return;
    }

    int identificador_int = atoi(identificador_char);
    
    while(fread(individuo, sizeof(GERAL), 1, arquivo_leitura) ==  1){

        if(individuo->matricula == identificador_int || !strcmp(individuo->nome, identificador_char) || !strcmp(individuo->cpf, identificador_char)){
            
        campo = menu_editar();
        
        switch(campo) {
            
            case 1: //Alteração da função exercida
            printf("Digite a nova funcao exercida(ex: Funcao): ");
            scanf("%s", novo);
            fflush(stdin);
            
            while(!(verifica_funcao(novo))) { //verifica se a função é válida.
                printf("Funcao invalida, digite uma funcao valida(ex: Funcao):\n");
                scanf("%s", novo);
                fflush(stdin);
            }

            strcpy(individuo->funcao, novo);
            printf("\nAlteracao feita!");
            break;
            
            case 2: //Alteração do telefone
            printf("Numero de telefone(ex: (021) 98765-4321): ");
            fflush(stdin);
            fgets(novo, 100, stdin);
            retirar_quebra(novo);

            while(!(verificar_telefone(novo))) {
                printf("Telefone invalido. Por favor, digite um telefone valido (ex: (021) 98765-4321) ):\n");
                fgets(novo, 100, stdin);
                fflush(stdin);
                retirar_quebra(novo);
            }

            strcpy(individuo->telefone, novo);
            printf("\nAlteracao feita!");
            break;
            
            case 3: //Alteração do endereço
            printf("Cep (ex: 26534-125): ");
            fflush(stdin);
            fgets(novo, 100, stdin);
            retirar_quebra(novo);

            while(!(verificar_cep(novo))){ //verifica se o cep eh valido.
                printf("CEP invalido, digite um CEP valido (ex: 26534-125):\n");
                fgets(novo, 100, stdin);
                fflush(stdin);
                retirar_quebra(novo);
            }

            strcpy(individuo->cep, novo);
    
            printf("Rua: ");
            fflush(stdin);
            fgets(novo, 100, stdin);
            retirar_quebra(novo);
            strcpy(individuo->rua, novo);

            printf("Numero da casa: ");
            fflush(stdin);
            fgets(novo, 100, stdin);
            retirar_quebra(novo);
            strcpy(individuo->rua_num, novo);

            printf("Complemento: ");
            fflush(stdin);
            fgets(novo, 100, stdin);
            retirar_quebra(novo);
            strcpy(individuo->complemento, novo);

            printf("Estado: ");
            fflush(stdin);
            fgets(novo, 100, stdin);
            retirar_quebra(novo);
            strcpy(individuo->estado, novo);

            printf("Cidade: ");
            fflush(stdin);
            fgets(novo, 100, stdin);
            retirar_quebra(novo);
            strcpy(individuo->cidade, novo);
            printf("\nAlteracao feita!");
            break;

            case 0:
            break;
        }

        fwrite(individuo, sizeof(GERAL), 1, arquivo_escrita);
        
        } else {
            fwrite(individuo, sizeof(GERAL), 1, arquivo_escrita);
        }

    }


    free(individuo);
    fclose(arquivo_leitura);
    fclose(arquivo_escrita);

    system("del cadastro.bin");
    system("rename novocadastro.bin cadastro.bin");
}

int menu_editar() {
    int comando;
    system("cls");
    printf("1 - Alterar funcao exercida\n2 - Alterar telefone\n3 - Alterar o endereco\n0 - Cancelar alteracao\n");
    printf("Digite o numero correspondente ao campo que deseja editar: ");
    scanf("%d", &comando);

    while(comando != 0 && comando != 1 && comando!= 2 && comando != 3) {
        printf("Digite um numero valido: ");
        scanf("%d", &comando);
    }

    return comando;
}

GERAL* buscar_cadastro (char *identificador_char) {
    
    FILE* arquivo;

    GERAL *individuo;

    individuo = (GERAL*) malloc(sizeof(GERAL));

    arquivo = fopen("cadastro.bin", "r");

    if(arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        fclose(arquivo);
        return NULL;
    }

    int identificador_int = atoi(identificador_char);

     while((fread(individuo, sizeof(GERAL), 1, arquivo) == 1)){

        if(individuo->matricula == identificador_int || !strcmp(individuo->nome, identificador_char) || !strcmp(individuo->cpf, identificador_char)) {
            fclose(arquivo);
            return individuo;
        }
    }

    printf("Essa pessoa nao possui um cadastro\n");
    fclose(arquivo);
    return NULL;
    
}

int calcular_idade(char* data_nascimento) {
    int dia = (data_nascimento[0] - '0')*10 + (data_nascimento[1] - '0');
    int mes = (data_nascimento[3] - '0')*10 + (data_nascimento[4] - '0') - 1; // Ajustando o mês para 0-11
    int ano = (data_nascimento[6] - '0')*1000 + (data_nascimento[7] - '0')*100 + (data_nascimento[8] - '0')*10 + (data_nascimento[9] - '0');

    time_t segundos;
    struct tm *data_hora_atual;
    
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    
    int ano_atual = data_hora_atual->tm_year + 1900;
    int mes_atual = data_hora_atual->tm_mon;
    int dia_atual = data_hora_atual->tm_mday;

    int idade = ano_atual - ano;

    if (mes_atual < mes || (mes_atual == mes && dia_atual < dia)) {
        idade--;
    }

    return idade;
}

void acessar_sistema(){
    char senha_definida[10] = "1234";
    char senha_testar[10];

    printf("Insira a senha para acessar o sistema: ");
    fgets(senha_testar, 10, stdin);
    retirar_quebra(senha_testar);


    while(strcmp(senha_definida, senha_testar) != 0){
        printf("Senha invalida, tente novamente: \n");
        fgets(senha_testar, 10, stdin);
        retirar_quebra(senha_testar);
    }

    system("cls");

}

#endif