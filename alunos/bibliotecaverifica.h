#ifndef BIBLIOTEVERIFICA_H
#define BIBLIOTEVERIFICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[200]; //ver dps o nome responsavel
    char funcao[15];
    int matricula;
    char ano_ingresso[10];
    char telefone[20];
    char data_nascimento[15]; //especificar o modelo no cadastro
    char cpf[15];
    char cep[11]; 
    char rua[30];
    char rua_num[5];
    char estado[30];
    char cidade[30];
    char complemento[30];
    
}GERAL;

int verifica_funcao(char *funcao_realizada);
int verificar_cpf(char *CPF);
int verificar_cep(char *cep);
int verificar_telefone(char *telefone);
int verificar_data_nascimento(char *data);
int verificar_ano(char *ano);

int verificar_cpf(char *CPF) {
    FILE* arquivo;
    GERAL* individuo;

    individuo = (GERAL*) malloc(sizeof(GERAL));

    arquivo = fopen("cadastro.bin", "r");

    if(arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }

    while((fread(individuo, sizeof(GERAL), 1, arquivo) == 1)){
        if(strcmp(individuo->cpf, CPF) == 0){
            printf("O cpf ja foi cadastrado\n");
            return 0;
        }
    }

    free(individuo);

    fclose(arquivo);

    int status = 1;

    for(int i = 0; i < 14; i++) {
        
        if (((i >= 0 && i <= 2) || (i >= 4 && i <= 6) || (i >= 8 && i <= 10) || (i >= 12 && i <= 13)) && (CPF[i] < '0' && CPF[i] > '9')) {
            status = 0;
            return status;
        }

        if ((i == 3 || i == 7) && (CPF[i] != '.')){
            status = 0;
            return status;
        }

        if(i == 11 && CPF[i] != '-'){
            status = 0;
            return status;
        }
    }

    if(((CPF[0] == CPF[1]) && (CPF[1] == CPF[2]) && (CPF[2] == CPF[4]) && (CPF[4] == CPF[5]) && (CPF[5] == CPF[6]) && 
    (CPF[6] == CPF[8]) && (CPF[8] == CPF[9]) && (CPF[9] == CPF[10]) && (CPF[10] == CPF[12]) && (CPF[12] == CPF[13]))) {
        status = 0;
        return status;
    }

    int primeiro_digito_verificador, segundo_digito_verificador, soma = 0, peso = 10;

    for(int i = 0; CPF[i] != '-'; i++) {
        
        if(CPF[i] >= '0' && CPF[i] <= '9') {
            soma = soma + ((CPF[i] - '0') * peso);
            peso--;
        }

    }

    primeiro_digito_verificador = (soma * 10) % 11;
    
    if(primeiro_digito_verificador == 10) {
        primeiro_digito_verificador = 0;
    }

    if((CPF[12] - '0') != primeiro_digito_verificador) {
        status = 0;
        return status;
    }

    peso = 11;
    soma = 0;

    for(int i = 0; i < 13; i++) {
        
        if(CPF[i] >= '0' && CPF[i] <= '9') {
            soma = soma + (CPF[i] - '0') * peso;
            peso--;
        }

    }

    segundo_digito_verificador = (soma * 10) % 11;

    if(segundo_digito_verificador == 10) {
        segundo_digito_verificador = 0;
    }

    if((CPF[13] - '0') != segundo_digito_verificador) {
        status = 0;
        return status;
    }

    return status;

}

int verificar_cep(char *cep) {
    int status = 1;

    if(cep[5] != '-') {
        status = 0;
        return status;
    }

    for (int i = 0; cep[i] != '\0'; i++) {
        if((i != 5) && (cep[i] < '0' || cep[i] > '9')) {
            status = 0;
            return status;
        }
    }

    if(strlen(cep) != 9){
        status = 0;
        return status;
    }
    
    return status;
}

int verificar_telefone(char *telefone){

    char numerosTelefone[20];
    int cont = 0;
    int i = 0;

    while(telefone[i] != '\0'){

        if((telefone[i] <= '9') && (telefone[i] >= '0')){

            numerosTelefone[cont] = telefone[i];
            cont++;

        }

        i++;

    }

    if(numerosTelefone[0] == '0'){ // ddd do tipo 021

        if(numerosTelefone[3] == '8' || numerosTelefone[3] == '9'){

            if(cont == 9 || cont == 10 || cont == 11 || cont == 12){

                return 1;

            }

            else{

                return 0;

            }

        }

        else{

            return 0;

        }

    }

    else if(numerosTelefone[0] != '0'){ //ddd do tipo 21

        if(numerosTelefone[2] == '8' || numerosTelefone[2] == '9'){

            if(cont == 8 || cont == 9 || cont == 10 || cont == 11){

                return 1;

            }

            else{

                return 0;

            }

        }

        else{

            return 0;

        }

    }

    else{

        return 0;

    }

}

int verificar_data_nascimento(char *data){

    if(!(data[2] == '/')){ // verifica se tem a primeira /

        return 0;

    }

    else if(!(data[5] == '/')){ // verifica se tem a segunda /

        return 0;

    }


    if(!((data[0] <= '9') && (data[0] >= '0'))){
        return 0;
    }
    if(!((data[1] <= '9') && (data[1] >= '0'))){
        return 0;
    }
    if(!((data[3] <= '9') && (data[3] >= '0'))){
        return 0;
    }
    if(!((data[4] <= '9') && (data[4] >= '0'))){
        return 0;
    }
    if(!((data[6] <= '9') && (data[6] >= '0'))){
        return 0;
    }
    if(!((data[7] <= '9') && (data[7] >= '0'))){
        return 0;
    }
    if(!((data[8] <= '9') && (data[8] >= '0'))){
        return 0;
    }
    if(!((data[9] <= '9') && (data[9] >= '0'))){
        return 0;
    }

    if(!(strlen(data) == 10)){ // verifica se o tamanho está diferente do padrão

        return 0;

    }

    return 1;

}

int verificar_ano(char *ano){

    int i = 0;

    while(ano[i] != '\0'){ //enquanto o vetor não acaba:

        if(!((ano[i] <= '9') && (ano[i] >= '0'))){ // verifica se todas as posições do vetor são numeros

            return 0;

        }

        i++;

    }

    int numero_ano = atoi(ano); //transformei o vetor de char em int

    if(!((numero_ano >= 1800) && (numero_ano <= 9999))){ //verifica se o ano é [1800, 9999]

        return 0;

    }

    return 1;

}

int verifica_funcao(char *funcao_realizada) {
    char *funcoes_permitidas[] = {"Limpeza", "Secretario", "Estagiario", "Gerente", "Aluno", "Consultor", "Seguranca"};
    int num_funcoes_permitidas = sizeof(funcoes_permitidas) / sizeof(funcoes_permitidas[0]);

    for (int i = 0; i < num_funcoes_permitidas; i++) {
        if (strcmp(funcao_realizada, funcoes_permitidas[i]) == 0) {
            return 1; // Função encontrada na lista de funções permitidas
        }
    }

    return 0; // Função não encontrada na lista de funções permitidas
}
#endif