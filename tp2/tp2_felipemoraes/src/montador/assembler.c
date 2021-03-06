/*========================================================================================================================================
TRABALHO PRATICO 2 - SOFTWARE BASICO
@FELIPE MORAES GOMES

*ASSEMBLER.C - Define funcoes do Montador
========================================================================================================================================*/

#include "assembler.h"
#include "io.h"
#include "lista.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Insere Opcode numa lista
void insert_opcode(TipoLista *opcode_table, char* opcode, int code){
    TipoItem x;
    int n;
    //Tamanho do opcode
    n = (int) strlen(opcode)+1;
    x.Chave = (char*) calloc(n,sizeof(char));
    x.Chave = opcode;
    x.ID = code;
    Insere(&x, opcode_table);

}

//Cria tabela de opcode

void create_opcode_table(TipoLista *opcode_table){
    insert_opcode(opcode_table,"LOAD\0",01);
    insert_opcode(opcode_table,"STORE\0",02);
    insert_opcode(opcode_table,"READ\0",03);
    insert_opcode(opcode_table,"WRITE\0",04);
    insert_opcode(opcode_table,"COPY\0",05);
    insert_opcode(opcode_table,"ADD\0",06);
    insert_opcode(opcode_table,"SUB\0",07);
    insert_opcode(opcode_table,"AND\0",8);
    insert_opcode(opcode_table,"OR\0",9);
    insert_opcode(opcode_table,"XOR\0",10);
    insert_opcode(opcode_table,"NOT\0",11);
    insert_opcode(opcode_table,"JMP\0",12);
    insert_opcode(opcode_table,"JZ\0",13);
    insert_opcode(opcode_table,"JNZ\0",14);
    insert_opcode(opcode_table,"JN\0",15);
    insert_opcode(opcode_table,"JNN\0",16);
    insert_opcode(opcode_table,"PUSH\0",17);
    insert_opcode(opcode_table,"POP\0",18);
    insert_opcode(opcode_table,"CALL\0",19);
    insert_opcode(opcode_table,"RET\0",20);
    insert_opcode(opcode_table,"HALT\0",21);
    insert_opcode(opcode_table,"WORD\0",22);
    insert_opcode(opcode_table,"END\0",23);
}

//Cria tabela de tamanhos
void create_size_table(TipoLista *opcode_table){

    insert_opcode(opcode_table,"LOAD\0",3);
    insert_opcode(opcode_table,"STORE\0",3);
    insert_opcode(opcode_table,"READ\0",2);
    insert_opcode(opcode_table,"WRITE\0",2);
    insert_opcode(opcode_table,"COPY\0",3);
    insert_opcode(opcode_table,"ADD\0",3);
    insert_opcode(opcode_table,"SUB\0",3);
    insert_opcode(opcode_table,"AND\0",3);
    insert_opcode(opcode_table,"OR\0",3);
    insert_opcode(opcode_table,"XOR\0",3);
    insert_opcode(opcode_table,"NOT\0",2);
    insert_opcode(opcode_table,"JMP\0",2);
    insert_opcode(opcode_table,"JZ\0",2);
    insert_opcode(opcode_table,"JNZ\0",2);
    insert_opcode(opcode_table,"JN\0",2);
    insert_opcode(opcode_table,"JNN\0",2);
    insert_opcode(opcode_table,"PUSH\0",2);
    insert_opcode(opcode_table,"POP\0",2);
    insert_opcode(opcode_table,"CALL\0",2);
    insert_opcode(opcode_table,"RET\0",1);
    insert_opcode(opcode_table,"HALT\0",1);
    insert_opcode(opcode_table,"WORD\0",1);
    insert_opcode(opcode_table,"END\0",1);

}


//Primeiro passo
void Primeiro_Passo (char* filename, TipoLista *symbol_table, TipoLista *opcode_table, TipoLista *size_table){
    int ILC = 0;
    char *line;
    char * word;
    int i,end,size;
    FILE *fin;
    fin = fopen(filename,"r");
    while (!feof(fin)) {
        //Le uma linha do arquivo de entrada
        line = readline(fin);
        //Recebe proxima palavra
        word = next_word(line);
        if(word ==NULL)
            continue;
        //Descobre tamanho
        end = (int) strlen(word);
        //Se palavra for um simbolo
        if (word[end-1]==':'){
                TipoItem x;
                //Retira os : do simbolo
                word[end-1] = '\0';
                x.ID = ILC;
                x.Chave = (char*)calloc(end,sizeof(char));
                x.Chave = word;
                //Insere simbolo na tabela de simbolos
                Insere(&x,symbol_table);
                //Recebe a proxima palavra (Deve ser uma instrucao)
                word = next_word(line);
                // Busca tamanho da instrucao
                size = Busca(word,*size_table);
                // Incrementa ILC
                ILC +=size;

            }
            // Se palavra nao for simbolo
            else{
                //Busca tamanho da instrucao
                size = Busca(word,*size_table);
                // Se for END - termina primeiro passo
                if (size ==23)
                    return;
                //Incrementa ILC
                ILC +=size;

            }
            i++;
        //Desaloca linha
        free(line);
    }
    //Fecha arquivo
    fclose(fin);
}

//FUncao de identificar o operador

int operator_table(char *op){
    op[2] = '\0';
    if (!strcmp(op,"R0"))
        return 0;
    else if (!strcmp(op,"R1"))
        return 1;
    else if (!strcmp(op,"R2"))
        return 2;
    else if (!strcmp(op,"R3"))
        return 3;
    else if (!strcmp(op,"R4"))
        return 4;
    else if (!strcmp(op,"R5"))
        return 5;
    else if (!strcmp(op,"R6"))
        return 6;
    else if (!strcmp(op,"R7"))
        return 7;
    return 8;
}

//Decodifica instrucao
int Decode(char *line, TipoLista symbol_table, TipoLista opcode_table, int *PC, int *memory){
        char * word;
        int end;
        int code;
        //Recebe primeira palavra da linha
        word = next_word(line);
        //Se for vazia
        if (word==NULL){
            return 0;
        }
        // Se nao for vazia
        else{
            //Procura tamanho
            end = (int) strlen(word);
            //Verifica se simbolo
            if (word[end-1]==':'){
                word = next_word(line);
            }
        }
        //Procura opcode
        code = Busca(word, opcode_table);
        //Se opcode e END termina segundo passo
        if (code == 23)
            return 1;
        int op1,op2;
        //Adiciona opcode
        memory[*PC] = code;
        *PC = *PC + 1;
        //Realiza decodificacao
        switch( code ){
            //LOAD,STORE
            case 1:
            case 2:
                word = next_word(line);
                op1 = operator_table(word);
                memory[*PC] = op1;
                *PC = *PC + 1;
                word = next_word(line);
                op2 = Busca(word, symbol_table);
                op2 = op2 - *PC-1;
                memory[*PC] = op2;
                *PC = *PC + 1;
                break;
            //READ,WRITE,PUSH,POP
            case 3:
            case 4:
            case 17:
            case 18:
                word = next_word(line);
                op1 = operator_table(word);
                memory[*PC] = op1;
                *PC = *PC + 1;
                break;
            //ALU OPs
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                word = next_word(line);
                op1 = operator_table(word);
                memory[*PC] = op1;
                *PC = *PC + 1;
                word = next_word(line);
                op2 = operator_table(word);
                memory[*PC] = op2;
                *PC = *PC + 1;
                break;
            //NOT
            case 11:
                word = next_word(line);
                op1 = operator_table(word);
                 memory[*PC] = op1;
                *PC = *PC + 1;
                break;
            // Branches,JMP e CALL
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 19:
                word = next_word(line);
                op1 = Busca(word, symbol_table);
                *PC = *PC + 1;
                op1 = op1 - *PC;
                memory[*PC-1] = op1;
                break;
            //RET HALT
            case 20:
            case 21:
                break;
            case 22:
                word = next_word(line);
                op1 = atoi(word);
                memory[*PC -1] = op1;
                break;
        }
        return 0;
}



void Segundo_Passo(char* input,char* output, TipoLista *symbol_table, TipoLista *opcode_table, TipoLista *size_table){
    //Inicia PC e SP
    int PC = 0;
    int SP = 1000;
    int *memory;
    memory = (int*) calloc (1000, sizeof(int));
    int halt =1;
    char M = 'M';
    char K = 'K';
    char *line;
    FILE *fin, *fout;
    fin = fopen(input,"r");
    fout = fopen(output,"wb");
    fwrite(&M,1,sizeof(char),fout);
    fwrite(&K,1,sizeof(char),fout);
    fwrite(&PC,1,sizeof(int),fout);
    fwrite(&SP,1,sizeof(int),fout);
    //Le cada linha e decodifica
    while (!feof(fin)) {
        line = readline(fin);
        halt = Decode(line,*symbol_table, *opcode_table, &PC,memory);
        free(line);
        if (halt == 1)
            break;
    }
    fwrite(memory,sizeof(int),1000,fout);
    free(memory);
    fclose(fin);
    fclose(fout);
}
