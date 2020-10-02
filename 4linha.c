#include <stdlib.h>
#include <stdio.h>

#define TAM_TAB 8
#define TOT_TAM_TAB (TAM_TAB * TAM_TAB)
#define VAZIO '_'
#define JOG_1 'O'
#define JOG_2 'X'

typedef struct __t_estado {
	char pos[TAM_TAB][TAM_TAB];
	char jogador;
} t_estado;

static void print_estado(t_estado * estado) {
	// Linha dos números
	for(int y = 0; y < TAM_TAB; ++y) {
		if (y >= 9) {
			printf("%d ", y + 1);
		} else {
			printf(" %d ", y + 1);
		}
	}
	printf("\n");

	// Tabuleiro
	for(int y = 0; y < TAM_TAB; ++y) {
		for(int x = 0; x < TAM_TAB; ++x) {
			printf(" %c ", estado->pos[x][y]);
		}
		printf("\n");
	}

	printf("\nO jogador atual é o %c\n", estado->jogador);
}

static int igual(t_estado * estado, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
	char c0 = estado->pos[x0][y0];
	char c1 = estado->pos[x1][y1];
	char c2 = estado->pos[x2][y2];
	char c3 = estado->pos[x3][y3];

	return c0 != VAZIO && c0 == c1 && c1 == c2 && c2 == c3;
}

static int fim_de_jogo(t_estado * estado, char * vencedor) {
	// horizontal
	for(int x = 0; x < TAM_TAB - 3; ++x) {
		for(int y = 0; y < TAM_TAB; ++y) {
			if (igual(estado, x, y, x + 1, y, x + 2, y, x + 3, y)) {
				*vencedor = estado->pos[x][y];
				return 1;
			}
		}
	}

	// vertical
	for(int x = 0; x < TAM_TAB; ++x) {
		for(int y = 0; y < TAM_TAB - 3; ++y) {
			if (igual(estado, x, y, x, y + 1, x, y + 2, x, y + 3)) {
				*vencedor = estado->pos[x][y];
				return 1;
			}
		}
	}

	// diagonal
	for(int x = 0; x < TAM_TAB - 3; ++x) {
		for(int y = 0; y < TAM_TAB - 3; ++y) {
			if (igual(estado, x, y, x + 1, y + 1, x + 2, y + 2, x + 3, y + 3)) {
				*vencedor = estado->pos[x][y];
				return 1;
			}
		}
	}

	// diagonal invertida
	for(int x = 3; x < TAM_TAB; ++x) {
		for(int y = 0; y < TAM_TAB - 3; ++y) {
			if (igual(estado, x, y, x - 1, y + 1, x - 2, y + 2, x - 3, y + 3)) {
				*vencedor = estado->pos[x][y];
				return 1;
			}
		}
	}

	return 0;
}

static void inicializar(t_estado * inicial) {
	for(int x = 0; x < TAM_TAB; ++x) {
		for(int y = 0; y < TAM_TAB; ++y) {
			inicial->pos[x][y] = VAZIO;
		}
	}

	inicial->jogador = JOG_1;
}


static int pedir_jogada(const t_estado * atual) {
	printf("Introduza a sua jogada [1..%d]: ", TAM_TAB);

	int c;

	while((c = getchar()) == '\n');

	if (c == -1) {
		exit(1);
	}

	c = c - '0';

	if (c < 1 || c > TAM_TAB) {
		return pedir_jogada(atual);
	}

	if (atual->pos[c][0] != VAZIO) {
		return pedir_jogada(atual);
	}

	return c - 1;
}

static void atualizar_estado(t_estado * atual, int jogada) {
	for(int y = TAM_TAB - 1; y >= 0; --y) {
		if (atual->pos[jogada][y] == VAZIO) {
			atual->pos[jogada][y] = atual->jogador;
			return;
		}
	}
}

static void trocar_jogador(t_estado * atual) {
	// Alternativa: 
	// atual->jogador = (atual->jogador == JOG_1) ? JOG_2 : JOG_1;

	if (atual->jogador == JOG_1) {
		atual->jogador = JOG_2;
	} else {
		atual->jogador = JOG_1;
	}
}

t_estado atual;
char vencedor;

int main() {
	// &atual obtem uma referencia de memória
	inicializar(&atual);

	while(!fim_de_jogo(&atual, &vencedor)) {
		print_estado(&atual);

		int jogada = pedir_jogada(&atual);

		atualizar_estado(&atual, jogada);

		trocar_jogador(&atual);
	}

	printf("Fim de jogo, venceram as %c\n", vencedor);

	return 0;
}
