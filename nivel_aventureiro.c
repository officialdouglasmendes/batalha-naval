
#include <stdio.h>
#include <stdbool.h> // Para usar o tipo booleano (true/false)

// --- Requisitos não funcionais: Legibilidade e Manutenção ---
// Constantes para configurar o jogo. Facilita futuras modificações.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// --- Documentação: Protótipo da Função ---
// Declara a função que será usada para posicionar os navios.
// Isso permite que a função main() a chame antes de sua implementação completa.
bool posicionarNavio(
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
    int linha,
    int coluna,
    char orientacao
);

int main() {
    // --- 1. Criar um Tabuleiro 10x10 ---
    // Declara a matriz que representa o tabuleiro do jogo.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int i, j;

    // Inicializa todas as posições com 0, representando 'água'.
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // --- 2. Posicionar Quatro Navios ---
    // As coordenadas e orientações são definidas diretamente no código.
    // Orientações: 'H' -> Horizontal, 'V' -> Vertical, 'D' -> Diagonal Principal, 'A' -> Diagonal Antiga

    printf("Iniciando posicionamento dos navios...\n");

    // Tenta posicionar cada navio e informa o resultado.
    if (posicionarNavio(tabuleiro, 1, 1, 'H')) {
        printf("Navio Horizontal posicionado com sucesso!\n");
    }
    if (posicionarNavio(tabuleiro, 3, 8, 'V')) {
        printf("Navio Vertical posicionado com sucesso!\n");
    }
    if (posicionarNavio(tabuleiro, 0, 5, 'D')) {
        printf("Navio Diagonal Principal posicionado com sucesso!\n");
    }
    if (posicionarNavio(tabuleiro, 6, 3, 'A')) {
        printf("Navio Diagonal Antiga posicionado com sucesso!\n");
    }

    printf("\n");

    // --- 3. Exibir o Tabuleiro ---
    // Utiliza loops aninhados para percorrer e imprimir a matriz.
    printf("--- Tabuleiro Final de Batalha Naval ---\n");
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da célula (0 ou 3) seguido de um espaço para alinhar.
            printf("%d ", tabuleiro[i][j]);
        }
        // Ao final de cada linha, pula para a próxima.
        printf("\n");
    }

    return 0; // Finaliza o programa com sucesso.
}

/**
 * @brief Função para posicionar um navio no tabuleiro.
 *
 * Esta função realiza duas validações principais:
 * 1. Validação de Limites (Bounds Checking): Verifica se o navio cabe inteiramente no tabuleiro.
 * 2. Validação de Sobreposição: Verifica se as posições desejadas já estão ocupadas.
 * Se ambas as validações passarem, a função modifica a matriz do tabuleiro.
 *
 * @param tabuleiro A matriz 10x10 do jogo.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param orientacao O tipo de orientação: 'H', 'V', 'D', ou 'A'.
 * @return true se o navio foi posicionado com sucesso, false caso contrário.
 */
bool posicionarNavio(
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
    int linha,
    int coluna,
    char orientacao
) {
    int i;

    // --- Validação de Limites (Bounds Checking) ---
    // Verifica se, a partir da posição inicial, o navio cabe no tabuleiro.
    switch (orientacao) {
        case 'H': // Horizontal
            if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
            break;
        case 'V': // Vertical
            if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
            break;
        case 'D': // Diagonal Principal (linha++ e coluna++)
            if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false;
            break;
        case 'A': // Diagonal Antiga (linha++ e coluna--)
            if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - TAMANHO_NAVIO + 1 < 0) return false;
            break;
        default: // Orientação inválida
            return false;
    }

    // --- Validação de Sobreposição ---
    // Percorre as posições futuras para garantir que todas são 'água' (0).
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        switch (orientacao) {
            case 'H':
                if (tabuleiro[linha][coluna + i] != 0) return false;
                break;
            case 'V':
                if (tabuleiro[linha + i][coluna] != 0) return false;
                break;
            case 'D':
                if (tabuleiro[linha + i][coluna + i] != 0) return false;
                break;
            case 'A':
                if (tabuleiro[linha + i][coluna - i] != 0) return false;
                break;
        }
    }

    // --- Posicionamento ---
    // Se todas as validações passaram, modifica a matriz para posicionar o navio.
    // O valor 3 é usado para representar uma parte de um navio.
    for (i = 0; i < TAMANHO_NAVIO; i++) {
         switch (orientacao) {
            case 'H':
                tabuleiro[linha][coluna + i] = 3;
                break;
            case 'V':
                tabuleiro[linha + i][coluna] = 3;
                break;
            case 'D':
                tabuleiro[linha + i][coluna + i] = 3;
                break;
            case 'A':
                tabuleiro[linha + i][coluna - i] = 3;
                break;
        }
    }

    return true; // Retorna verdadeiro indicando sucesso.
}
