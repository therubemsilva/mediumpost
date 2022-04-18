#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define MAX_SIZE 10

struct Move {
    int linha, coluna;
};

typedef struct Move Move;
//matrix X*X
int resolveLabirinto(int LAB[MAX_SIZE][MAX_SIZE], Move move[], int linhaInp, int colunaInp, int linhaEnd, int colunaEnd);

/**
  linhaInp  = linha inicial
  colunaInp  = coluna inicial
  linhaEnd  = linha final
  colunaEnd  = coluna final
*/

void imprimeLabirinto(int LAB[MAX_SIZE][MAX_SIZE], int n, int m) {

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (LAB[i][j] == -2) printf("1");                  //obstaculo
                if (LAB[i][j] == -1) printf("0");              //livre
                if (LAB[i][j] >= 0) printf("*");               //cont
                //if (M[i][j] >= 0) printf("%d", M[i][j]);
        }
    printf("\n");
    }
    printf("\n");
}

void obtemLabirinto(int LAB[MAX_SIZE][MAX_SIZE], int *n, int *m, int *linhaInp, int *colunaInp, int *linhaEnd, int *colunaEnd){
    int i, j, d, kk, ll;


    printf("\n");
    printf("Digite a dimensão da matrix (MAX 10): ");
    scanf("%d", n);

    printf("Cole aqui o seu mapa contido no arquivos mapas.txt: \n\n");


//
    int a,b;
    int grid[8][8];

    FILE *fp;

    fp= fopen("matrix_2.txt","r");
    while(!feof(fp)){
      for(i=0;i<8;i++){
          for(j=0;j<8;j++){
            fscanf(fp,"%d",&grid[i][j]);
          }
      }
    }

    for(a=0;a<8;a++)
    {
        for(b=0;b<8;b++)
        {
            printf("%d",grid[a][b]);
        }
        printf("\n");
    }

    fclose(fp);

//


    for (i = 0; i < *n; i++)
        for (j = 0; j < *n; j++) {
          scanf("%d", &d);
          if (d == 1)
              LAB[i][j] = -2;
          else
              LAB[i][j] = -1;
        }

    printf("\n");
    printf("Digite posicao INICIAL separado por espaco (LINHA COLUNA) correspondente ao mapa informado:");
    scanf("%d %d", linhaInp, colunaInp);

    printf("Digite posicao FINAL separado por espaco (LINHA COLUNA) correspondente ao mapa informado: ");
    scanf("%d %d", linhaEnd, colunaEnd);

}

int main() {
    int LAB[MAX_SIZE][MAX_SIZE], resp, n, m, linhaInp, colunaInp, linhaEnd, colunaEnd;

    /* movimentacao */
    Move move[4] = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

    /* info */
    obtemLabirinto(LAB, &n, &m, &linhaInp, &colunaInp, &linhaEnd, &colunaEnd);
    LAB[linhaInp - 1][colunaInp - 1] = 0; /* posicao inicial */

    resp = resolveLabirinto(LAB, move, linhaInp - 1, colunaInp - 1, linhaEnd - 1, colunaEnd - 1);
    if (resp == 0) {
        printf("\n");
        printf("Nao possui solucao. =/ \n");
    } else {
        printf("\n");
        printf("Existe uma solucao em %d passos Lo| \n", resp);
        printf("\n");

        imprimeLabirinto(LAB, n, m);
      }

return 0;

}

int resolveLabirinto(int LAB[MAX_SIZE][MAX_SIZE], Move move[], int linhaInp, int colunaInp, int linhaEnd, int colunaEnd){
    int L, C, k, passos;
    if ((linhaInp == linhaEnd) && (colunaInp == colunaEnd)) return LAB[linhaInp][colunaInp];

    /* Possibilidades a partir da posicao atual */
    for (k = 0; k < 4; k++) {
        L = linhaInp + move[k].linha;
        C = colunaInp + move[k].coluna;
        /* Verifica o movimento */
        if (LAB[L][C] == -1) {
            LAB[L][C] = LAB[linhaInp][colunaInp] + 1;
            passos = resolveLabirinto(LAB, move, L, C, linhaEnd, colunaEnd);
            if (passos > 0) return passos;
          }
    }

return 0;

}


/**
void informacoes(){

    scanf("%c",&c);
    printf("Neste projeto você deve sair do canto \n");
    printf("superior esquerdo e caminhar até o canto \n");
    printf("inferior direito [Digite Enter] \n");
    scanf("%c",&c);
    printf("Existem 4 movimentos possíveis \n");
    printf("para cima/para baixo/direita/esquerda \n");
    printf(" [Digite Enter] \n");
    scanf("%c",&c);
    printf("Só é permitido andar sobre zeros. \n");
    printf("O valor 1 é considerado um bloqueio. \n");
    printf(" [Digite Enter] \n");
    scanf("%c",&c);

    printf("Você deve desenhar um caminho (caso exista)\n sobre ");
    printf("o labirinto, usando * do canto superior \n");
    printf("esquerto até o canto inferior direito [Digite Enter] \n");
    scanf("%c",&c);

    resolveLabirinto();

    printf("Abaixo um exemplo  \n");

    imprimeLabirinto();

    printf("Só que este exemplo passa sobre bloqueios\n valores 1 [Digite Enter] \n");
    scanf("%c",&c);
    printf("Desenhe um caminho que não passa sobre 1 [Digite Enter] \n");
    scanf("%c",&c);
    printf("Trabalho em dupla. [Digite Enter] \n");
    scanf("%c",&c);
}
*/
