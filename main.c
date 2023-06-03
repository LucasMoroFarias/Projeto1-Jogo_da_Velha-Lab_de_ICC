#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#define LC 3

void printTable(char table[LC][LC]) //função para imprimir tabela
{   printf("\t   1 2 3\n");
    printf("\t  %c%c%c%c%c%c%c\n",218,196,194,196,194,196,191);
    printf("\t1 %c%c%c%c%c%c%c\n",179,table[0][0],179,table[0][1],179,table[0][2],179);
    printf("\t  %c%c%c%c%c%c%c\n",195,196,197,196,197,196,180);
    printf("\t2 %c%c%c%c%c%c%c\n",179,table[1][0],179,table[1][1],179,table[1][2],179);
    printf("\t  %c%c%c%c%c%c%c\n",195,196,197,196,197,196,180);
    printf("\t3 %c%c%c%c%c%c%c\n",179,table[2][0],179,table[2][1],179,table[2][2],179);
    printf("\t  %c%c%c%c%c%c%c\n",192,196,193,196,193,196,217);
}

bool verifyWinner(char table[LC][LC], char *winner) //retorna true => fim de jogo / retorna falso => jogo continua
{
    //declaração de variáveis
    char aux1, aux2, aux3;

    //verificação de fim de jogo por linha
    for(int i = 0; i < LC; i++) {
        //salva toda a linha i nas variáveis auxiliares
        aux1 = table[i][0];
        aux2 = table[i][1];
        aux3 = table[i][2];

        //verifica se a linha inteira é igual e diferente de vazio, caso seja o jogador venceu
        if(aux1 == aux2 && aux2 == aux3 && aux1 == aux3 && aux1 != ' ') {
            //variável winner é salva com o valor do vencedor
            *winner = aux1;
            return true;
        }
    }

    //verificação de fim de jogo por coluna
    for(int j = 0; j < LC; j++) {
        //salva toda a coluna j nas variáveis auxiliares
        aux1 = table[0][j];
        aux2 = table[1][j];
        aux3 = table[2][j];
        //verifica se a coluna inteira é igual e diferente de vazio, caso seja o jogador venceu
        if(aux1 == aux2 && aux2 == aux3 && aux1 == aux3 && aux1 != ' ') {
            //variável winner é salva com o valor do vencedor
            *winner = aux1;
            return true;
        }
    }

    //verifica se a diagonal 1 é inteira do mesmo valor e se é diferente de vazio, caso seja há um vencedor
    if(table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[0][0] == table[2][2] && table[1][1] != ' ') { //verificação diagonal 1
            //variável winner é salva com o valor do vencedor
            *winner = table[1][1];
            return true;
    }
    //verifica se a diagonal 2 é inteira do mesmo valor e se é diferente de vazio, caso seja há um vencedor
    if(table[2][0] == table[1][1] && table[0][2] == table[1][1] && table[0][2] == table[2][0] && table[1][1] != ' ') { //verificação diagonal 2
            //variável winner é salva com o valor do vencedor
            *winner = table[1][1];
            return true;
    }

    //verifica se ainda há espaços vazios no tabuleiro, caso ainda tenha ele retorna falso para buscar novas inserções
    for(int k = 0; k < LC; k++) {
        for(int w = 0; w < LC; w++) {
            if(table[k][w] == ' ')
                return false;
        }
    }

    //caso não entre em nenhum dos casos acima, não houve vencedor e não há espaço vago no tabuleiro, logo o jogo deu velha
    *winner = 'V';
    return true;
}

char verifyValueChar(char lastValue)
{
    //declaração de variáveis
    char insertValue;
    bool verified = false;
    //repete enquanto o caractere inserido foi inválido
    do {
        printf("Digite seu caractere [X ou O]: ");
        scanf(" %c",&insertValue);

        //verifica se o caractere é X ou O, caso não seja acusa erro
        if(insertValue == 'X' || insertValue == 'O')
            if(insertValue != lastValue) //verifica se o valor insere é diferente do último inserido, caso seja igual acusa erro
                verified = true;
            else {
                printf("ERRO: CARACTERE INSERIDO ANTERIORMENTE\n");
            }
        else
            printf("ERRO: CARACTERE INVALIDO\n");
    }while(!verified);
    return insertValue; //retorna valor após ser validado
}

void verifyValueLC(char table[LC][LC], int *line, int *column)
{
    //declaração de variáveis
    bool validLine, validColumn, validLC;
    //repete o código até ter linha e coluna válida
    while(!validLC) {
        validLine = false, validColumn = false;
        //verificação se a linha está valida
        while (!validLine){
            printf("Digite a linha escolhida [1 a 3]: ");
            scanf("%d",&*line);

            //linha tem que estar entre 1 e 3, caso contrário acusa erro
            if(*line < 1 || *line > 3) {
                printf("ERRO: LINHA INSERIDA INVALIDA\n");
                continue;
            } else {validLine = true;}
        }

        //verificação se a coluna será válida
        while(!validColumn) {
            printf("Digite a coluna escolhida [1 a 3]: ");
            scanf("%d",&*column);

            //coluna tem que ser entre 1 e 3, caso contrário acusa erro
            if(*column < 1 || *column > 3) {
                printf("ERRO: COLUNA INSERIDA INVALIDA\n");
                continue;
            } else {validColumn = true;}
        }

        //verifica se a linha e coluna já está preenchida, caso esteja pede nova linha e nova coluna
        if(table[*line-1][*column-1] != ' ') {
            printf("ERRO: POSICAO JA PREENCHIDA ANTERIORMENTE\n");
            continue;
        } else {validLC = true;}
    }
}

int main()
{
    //declaração de variáveis
    char table[LC][LC], lastValue = ' ', insertValue = ' ', winner = ' ';
    int line, column;
    bool endGame = false;

    //Inicializa a tabela de jogo
    for(int i=0; i < LC; i++) {
        for(int j=0; j < LC; j++) {
            table[i][j] = ' ';
        }
    }


    do {
        //chama função de printar a tabela
        printTable(table);
        //inserir valor com consistência
        insertValue = verifyValueChar(insertValue);
        //insere na tabela com consistência
        verifyValueLC(table, &line, &column);
        table[line-1][column-1] = insertValue;
        //verifica se teve ganhador
        endGame = verifyWinner(table, &winner);
        //limpa a tela
        system("cls");
    }while(!endGame);



    //limpa a tala
    system("cls");
    //imprime tabela
    printTable(table);
    //verifica quem venceu o jogo
    if(winner == 'X')
        printf("\tX vencedor");
    else if(winner == 'O')
        printf("\tO vencedor");
    else if(winner == 'V')
        printf("\tDeu velha");

    return 0;
}
