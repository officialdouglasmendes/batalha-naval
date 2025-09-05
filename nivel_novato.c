
#include <stdio.h>
#include <stdbool.h> // Dependência para o tipo booleano

// Constantes de configuração do jogo
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

int main() {
    // Matriz que representa o estado do tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int i, j;

    // Inicializa a matriz do tabuleiro com 0 (água)
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Coordenadas estáticas para posicionamento dos navios (hardcoded)
    int navio_h_linha = 2;
    int navio_h_coluna = 1;
    int navio_v_linha = 4;
    int navio_v_coluna = 5;

    // --- Posicionamento do Navio Horizontal ---

    // Validação de limites (bounds checking)
    if (navio_h_coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Aloca as posições na matriz, representando o navio com o valor 3
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_h_linha][navio_h_coluna + i] = 3;
        }
    } else {
        // Tratamento de erro caso a posição seja inválida
        printf("Erro de alocação: navio horizontal fora dos limites.\n");
    }

    // --- Posicionamento do Navio Vertical ---

    // Validação de limites (bounds checking)
    if (navio_v_linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        bool sobreposicao = false; // Flag de controle para detectar colisão

        // Itera sobre as células de destino para checar se já estão ocupadas
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_v_linha + i][navio_v_coluna] != 0) {
                sobreposicao = true;
                break; // Otimização: para a verificação se a colisão for encontrada
            }
        }

        // Se não houver sobreposição, aloca o navio
        if (!sobreposicao) {
            for (i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_v_linha + i][navio_v_coluna] = 3;
            }
        } else {
            printf("Erro de alocação: sobreposição de navios detectada.\n");
        }

    } else {
        printf("Erro de alocação: navio vertical fora dos limites.\n");
    }


    // Renderiza o estado final do tabuleiro no console
    printf("\n--- Tabuleiro Final de Batalha Naval ---\n");
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
