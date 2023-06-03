#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#define LC 3

void printTable(char table[LC][LC]) //fun��o para imprimir tabela
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
    //declara��o de vari�veis
    char aux1, aux2, aux3;

    //verifica��o de fim de jogo por linha
    for(int i = 0; i < LC; i++) {
        //salva toda a linha i nas vari�veis auxiliares
        aux1 = table[i][0];
        aux2 = table[i][1];
        aux3 = table[i][2];

        //verifica se a linha inteira � igual e diferente de vazio, caso seja o jogador venceu
        if(aux1 == aux2 && aux2 == aux3 && aux1 == aux3 && aux1 != ' ') {
            //vari�vel winner � salva com o valor do vencedor
            *winner = aux1;
            return true;
        }
    }

    //verifica��o de fim de jogo por coluna
    for(int j = 0; j < LC; j++) {
        //salva toda a coluna j nas vari�veis auxiliares
        aux1 = table[0][j];
        aux2 = table[1][j];
        aux3 = table[2][j];
        //verifica se a coluna inteira � igual e diferente de vazio, caso seja o jogador venceu
        if(aux1 == aux2 && aux2 == aux3 && aux1 == aux3 && aux1 != ' ') {
            //vari�vel winner � salva com o valor do vencedor
            *winner = aux1;
            return true;
        }
    }

    //verifica se a diagonal 1 � inteira do mesmo valor e se � diferente de vazio, caso seja h� um vencedor
    if(table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[0][0] == table[2][2] && table[1][1] != ' ') { //verifica��o diagonal 1
            //vari�vel winner � salva com o valor do vencedor
            *winner = table[1][1];
            return true;
    }
    //verifica se a diagonal 2 � inteira do mesmo valor e se � diferente de vazio, caso seja h� um vencedor
    if(table[2][0] == table[1][1] && table[0][2] == table[1][1] && table[0][2] == table[2][0] && table[1][1] != ' ') { //verifica��o diagonal 2
            //vari�vel winner � salva com o valor do vencedor
            *winner = table[1][1];
            return true;
    }

    //verifica se ainda h� espa�os vazios no tabuleiro, caso ainda tenha ele retorna falso para buscar novas inser��es
    for(int k = 0; k < LC; k++) {
        for(int w = 0; w < LC; w++) {
            if(table[k][w] == ' ')
                return false;
        }
    }

    //caso n�o entre em nenhum dos casos acima, n�o houve vencedor e n�o h� espa�o vago no tabuleiro, logo o jogo deu velha
    *winner = 'V';
    return true;
}

char verifyValueChar(char lastValue)
{
    //declara��o de vari�veis
    char insertValue;
    bool verified = false;
    //repete enquanto o caractere inserido foi inv�lido
    do {
        printf("Digite seu caractere [X ou O]: ");
        scanf(" %c",&insertValue);

        //verifica se o caractere � X ou O, caso n�o seja acusa erro
        if(insertValue == 'X' || insertValue == 'O')
            if(insertValue != lastValue) //verifica se o valor insere � diferente do �ltimo inserido, caso seja igual acusa erro
                verified = true;
            else {
                printf("ERRO: CARACTERE INSERIDO ANTERIORMENTE\n");
            }
        else
            printf("ERRO: CARACTERE INVALIDO\n");
    }while(!verified);
    return insertValue; //retorna valor ap�s ser validado
}

void verifyValueLC(char table[LC][LC], int *line, int *column)
{
    //declara��o de vari�veis
    bool validLine, validColumn, validLC;
    //repete o c�digo at� ter linha e coluna v�lida
    while(!validLC) {
        validLine = false, validColumn = false;
        //verifica��o se a linha est� valida
        while (!validLine){
            printf("Digite a linha escolhida [1 a 3]: ");
            scanf("%d",&*line);

            //linha tem que estar entre 1 e 3, caso contr�rio acusa erro
            if(*line < 1 || *line > 3) {
                printf("ERRO: LINHA INSERIDA INVALIDA\n");
                continue;
            } else {validLine = true;}
        }

        //verifica��o se a coluna ser� v�lida
        while(!validColumn) {
            printf("Digite a coluna escolhida [1 a 3]: ");
            scanf("%d",&*column);

            //coluna tem que ser entre 1 e 3, caso contr�rio acusa erro
            if(*column < 1 || *column > 3) {
                printf("ERRO: COLUNA INSERIDA INVALIDA\n");
                continue;
            } else {validColumn = true;}
        }

        //verifica se a linha e coluna j� est� preenchida, caso esteja pede nova linha e nova coluna
        if(table[*line-1][*column-1] != ' ') {
            printf("ERRO: POSICAO JA PREENCHIDA ANTERIORMENTE\n");
            continue;
        } else {validLC = true;}
    }
}

int main()
{
    //declara��o de vari�veis
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
        //chama fun��o de printar a tabela
        printTable(table);
        //inserir valor com consist�ncia
        insertValue = verifyValueChar(insertValue);
        //insere na tabela com consist�ncia
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
