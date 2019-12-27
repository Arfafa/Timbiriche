#include <stdio.h>
#include <stdlib.h>

#define TAM 11

int create(char matriz[TAM][TAM]);
int exibir(char matriz[TAM][TAM]);
int jogada(char matriz[TAM][TAM], int y, int x);
int computer_move(char matriz[TAM][TAM]);
int contagem(char matriz[TAM][TAM], int player, int *score);
char menu();

int main() {
  char TABULEIRO[TAM][TAM];
  char game_mode;
  int SCORE_MIN;
  int score[2] = {0, 0};
  int y, x;
  int player = 0;
  int aux;

  SCORE_MIN = (TAM - 1) / 2;
  SCORE_MIN *= SCORE_MIN;
  SCORE_MIN /= 2;
  SCORE_MIN++;

  create(TABULEIRO);

  game_mode = menu();

  switch (game_mode) {

  case '1':
    while (score[0] < SCORE_MIN && score[1] < SCORE_MIN) {
      system("clear");

      player %= 2;

      printf("Jogador (1):    %d\n", score[0]);
      printf("Computador (2): %d\n\n", score[1]);

      exibir(TABULEIRO);

      if (!player) {
        printf("\nVez do jogador %d:\n", player + 1);
        scanf("%d%d", &y, &x);
        aux = jogada(TABULEIRO, y, x);
      }

      else
        aux = computer_move(TABULEIRO);

      if (!aux) {
        aux = score[player];
        contagem(TABULEIRO, player + 1, &score[player]);

        if (aux == score[player])
          player++;
      }
    }

    system("clear");

    printf("Jogador (1):    %d\n", score[0]);
    printf("Computador (2): %d\n\n", score[1]);

    exibir(TABULEIRO);

    player = (score[0] < score[1]) ? 2 : 1;

    if (player == 1)
      printf("O vencedor foi o jogador!\n");

    else
      printf("O vencedor foi o computador!\n");

    break;

  case '2':
    while (score[0] < SCORE_MIN && score[1] < SCORE_MIN) {
      system("clear");

      player %= 2;

      printf("Jogador 1: %d\n", score[0]);
      printf("Jogador 2: %d\n\n", score[1]);

      exibir(TABULEIRO);

      printf("\nVez do jogador %d:\n", player + 1);
      scanf("%d%d", &y, &x);

      aux = jogada(TABULEIRO, y, x);

      if (!aux) {
        aux = score[player];
        contagem(TABULEIRO, player + 1, &score[player]);

        if (aux == score[player])
          player++;
      }
    }

    system("clear");

    printf("Jogador 1: %d\n", score[0]);
    printf("Jogador 2: %d\n\n", score[1]);

    exibir(TABULEIRO);

    player = (score[0] < score[1]) ? 2 : 1;
    printf("O vencedor foi o jogador %d!\n", player);

    break;

  case 'q':
    system("clear");

    break;
  }

  return 0;
}

int create(char matriz[TAM][TAM]) {

  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++) {
      if (i % 2)
        matriz[i][j] = ' ';

      else {
        if (j % 2)
          matriz[i][j] = ' ';

        else
          matriz[i][j] = 'o';
      }
    }
  }

  return 0;
}

int exibir(char matriz[TAM][TAM]) {
  for (int i = 0; i < TAM; i++) {
    for (int j = 0; j < TAM; j++)
      printf("%c", matriz[i][j]);

    printf("\n");
  }

  return 0;
}

int jogada(char matriz[TAM][TAM], int y, int x) {

  if (y < TAM && x < TAM) {

    if (y % 2 && !(x % 2) && matriz[y][x] == ' ')
      matriz[y][x] = '|';

    else if (!(y % 2) && x % 2 && matriz[y][x] == ' ')
      matriz[y][x] = '-';

    else
      return 1;
  }

  else
    return 1;

  return 0;
}

int contagem(char matriz[TAM][TAM], int player, int *score) {
  char up, down, left, right;

  for (int i = 1; i < TAM; i += 2) {
    for (int j = 1; j < TAM; j += 2) {
      up = matriz[i - 1][j];
      down = matriz[i + 1][j];
      left = matriz[i][j - 1];
      right = matriz[i][j + 1];

      if (up != ' ' && down != ' ' && left != ' ' && right != ' ') {
        if (matriz[i][j] == ' ') {
          matriz[i][j] = player + '0';
          *score = *score + 1;
        }
      }
    }
  }

  return 0;
}

int computer_move(char matriz[TAM][TAM]) {
  char up, down, left, right;
  int vector[4];
  int count;
  int aux = 0;
  int y, x;

  for (int i = 1; i < TAM; i += 2) {
    for (int j = 1; j < TAM; j += 2) {
      up = matriz[i - 1][j];
      down = matriz[i + 1][j];
      left = matriz[i][j - 1];
      right = matriz[i][j + 1];

      vector[0] = (up == ' ') ? 0 : 1;
      vector[1] = (down == ' ') ? 0 : 1;
      vector[2] = (left == ' ') ? 0 : 1;
      vector[3] = (right == ' ') ? 0 : 1;

      count = 0;

      for (int k = 0; k < 4; k++)
        count += vector[k];

      if (count == 3) {

        aux = 1;

        if (up == ' ')
          matriz[i - 1][j] = '-';

        else if (down == ' ')
          matriz[i + 1][j] = '-';

        else if (left == ' ')
          matriz[i][j - 1] = '|';

        else
          matriz[i][j + 1] = '|';

        i = TAM + 1;
        j = TAM + 1;
      }
    }
  }

  if (!aux) {

    do {
      aux = 0;

      y = rand() % TAM;
      x = rand() % TAM;

      if (y % 2 && !(x % 2) && matriz[y][x] == ' ')
        matriz[y][x] = '|';

      else if (!(y % 2) && x % 2 && matriz[y][x] == ' ')
        matriz[y][x] = '-';

      else
        aux = 1;

    } while (aux);
  }

  return 0;
}

char menu() {
  char resp;

  do {
    system("clear");
    printf("    MENU:\n\n");
    printf(" 1 Jogador  (1)\n");
    printf("2 Jogadores (2)\n");
    printf("    Sair    (q)\n");

    scanf("%c", &resp);
  } while (resp != 'q' && resp != '1' && resp != '2');

  return resp;
}
