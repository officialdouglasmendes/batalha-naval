
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Usada para a função abs() (valor absoluto)

// --- Constantes Globais ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // Define um tamanho fixo para as matrizes de habilidade

// --- Protótipos das Funções (Documentação) ---

// Funções do desafio anterior
bool posicionarNavio(int tabuleiro[][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao);

// Novas funções para o nível Mestre
void gerarMatrizHabilidade(int matriz[][TAMANHO_HABILIDADE], char tipo);
void aplicarHabilidade(int tabuleiro[][TAMANHO_TABULEIRO], int habilidade[][TAMANHO_HABILIDADE], int origem_linha, int origem_coluna);
void exibirTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
void exibirMatrizHabilidade(int matriz[][TAMANHO_HABILIDADE], const char* nomeHabilidade);


int main() {
    // --- 1. Definir o Tabuleiro e Posicionar Navios ---
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0}; // Inicializa o tabuleiro com zeros

    // Posiciona os navios do desafio anterior
    posicionarNavio(tabuleiro, 1, 1, 'H');
    posicionarNavio(tabuleiro, 3, 8, 'V');
    posicionarNavio(tabuleiro, 0, 5, 'D');
    posicionarNavio(tabuleiro, 6, 3, 'A');

    // --- 2. Criar Matrizes de Habilidade ---
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Gera dinamicamente cada matriz de habilidade usando condicionais
    gerarMatrizHabilidade(habilidadeCone, 'C');     // 'C' para Cone
    gerarMatrizHabilidade(habilidadeCruz, 'X');     // 'X' para Cruz
    gerarMatrizHabilidade(habilidadeOctaedro, 'O'); // 'O' para Octaedro

    // Exibe as matrizes de habilidade geradas para visualização
    exibirMatrizHabilidade(habilidadeCone, "Habilidade: Cone");
    exibirMatrizHabilidade(habilidadeCruz, "Habilidade: Cruz");
    exibirMatrizHabilidade(habilidadeOctaedro, "Habilidade: Octaedro (Losango)");

    // --- 3. Integrar Habilidades ao Tabuleiro ---
    printf("\nAplicando habilidades especiais no tabuleiro...\n");

    // Define os pontos de origem (alvos) para cada habilidade no tabuleiro principal
    aplicarHabilidade(tabuleiro, habilidadeCone, 1, 4);     // Topo do cone em (1, 4)
    aplicarHabilidade(tabuleiro, habilidadeCruz, 7, 7);     // Centro da cruz em (7, 7)
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 4, 2); // Centro do octaedro em (4, 2)

    // --- 4. Exibir o Tabuleiro com Habilidades ---
    exibirTabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Gera a matriz de área de efeito para uma habilidade.
 * @param matriz A matriz 5x5 a ser preenchida.
 * @param tipo O caractere que define a forma ('C', 'X', 'O').
 */
void gerarMatrizHabilidade(int matriz[][TAMANHO_HABILIDADE], char tipo) {
    int i, j;
    int centro = TAMANHO_HABILIDADE / 2; // O centro da matriz (ex: 2 para uma matriz 5x5)

    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            bool afetado = false; // Flag para marcar se a posição é afetada

            // Lógica condicional para definir a forma da habilidade
            switch (tipo) {
                case 'C': // Cone (origem no topo-centro e expande para baixo)
                    if (i <= centro && j >= centro - i && j <= centro + i) {
                        afetado = true;
                    }
                    break;
                case 'X': // Cruz (afeta a linha e a coluna centrais)
                    if (i == centro || j == centro) {
                        afetado = true;
                    }
                    break;
                case 'O': // Octaedro (forma de losango/diamante)
                    // Usa a distância de Manhattan do centro
                    if (abs(i - centro) + abs(j - centro) <= centro) {
                        afetado = true;
                    }
                    break;
            }
            matriz[i][j] = afetado ? 1 : 0; // Preenche com 1 (afetado) ou 0 (não afetado)
        }
    }
}

/**
 * @brief Sobrepõe a matriz de habilidade no tabuleiro principal.
 * @param tabuleiro O tabuleiro 10x10 do jogo.
 * @param habilidade A matriz 5x5 da habilidade.
 * @param origem_linha A linha alvo no tabuleiro (será o centro da habilidade).
 * @param origem_coluna A coluna alvo no tabuleiro.
 */
void aplicarHabilidade(int tabuleiro[][TAMANHO_TABULEIRO], int habilidade[][TAMANHO_HABILIDADE], int origem_linha, int origem_coluna) {
    int i, j;
    int centro = TAMANHO_HABILIDADE / 2;

    // Itera sobre a matriz de habilidade 5x5
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Se a posição na matriz de habilidade for 1 (área de efeito)
            if (habilidade[i][j] == 1) {
                // Calcula a coordenada correspondente no tabuleiro principal
                int linha_tabuleiro = origem_linha - centro + i;
                int coluna_tabuleiro = origem_coluna - centro + j;

                // Validação de Limites: garante que a habilidade não "saia" do tabuleiro
                if (linha_tabuleiro >= 0 && linha_tabuleiro < TAMANHO_TABULEIRO &&
                    coluna_tabuleiro >= 0 && coluna_tabuleiro < TAMANHO_TABULEIRO) {
                    // Marca a área afetada no tabuleiro com o valor 5
                    tabuleiro[linha_tabuleiro][coluna_tabuleiro] = 5;
                }
            }
        }
    }
}

/**
 * @brief Exibe o tabuleiro final com uma legenda clara.
 * @param tabuleiro O tabuleiro 10x10 do jogo.
 */
void exibirTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    printf("\n--- Tabuleiro Final com Habilidades ---\n");
    printf("Legenda:  . (Agua)  N (Navio)  * (Area de Efeito)\n\n");

    int i, j;
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            switch (tabuleiro[i][j]) {
                case 0: // Água
                    printf(". ");
                    break;
                case 3: // Navio
                    printf("N ");
                    break;
                case 5: // Área de Habilidade
                    printf("* ");
                    break;
                default:
                    printf("? "); // Caractere para valores inesperados
                    break;
            }
        }
        printf("\n");
    }
}

/**
 * @brief Função auxiliar para exibir uma matriz de habilidade.
 * @param matriz A matriz 5x5 da habilidade.
 * @param nomeHabilidade O nome da habilidade a ser exibido.
 */
void exibirMatrizHabilidade(int matriz[][TAMANHO_HABILIDADE], const char* nomeHabilidade) {
    printf("\n%s (formato 5x5):\n", nomeHabilidade);
    int i, j;
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}


// Implementação da função do desafio anterior (necessária para o programa funcionar)
bool posicionarNavio(int tabuleiro[][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    int i;
    // Validação de Limites
    switch (orientacao) {
        case 'H': if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false; break;
        case 'V': if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false; break;
        case 'D': if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return false; break;
        case 'A': if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - TAMANHO_NAVIO + 1 < 0) return false; break;
        default: return false;
    }
    // Validação de Sobreposição
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        switch (orientacao) {
            case 'H': if (tabuleiro[linha][coluna + i] != 0) return false; break;
            case 'V': if (tabuleiro[linha + i][coluna] != 0) return false; break;
            case 'D': if (tabuleiro[linha + i][coluna + i] != 0) return false; break;
            case 'A': if (tabuleiro[linha + i][coluna - i] != 0) return false; break;
        }
    }
    // Posicionamento
    for (i = 0; i < TAMANHO_NAVIO; i++) {
         switch (orientacao) {
            case 'H': tabuleiro[linha][coluna + i] = 3; break;
            case 'V': tabuleiro[linha + i][coluna] = 3; break;
            case 'D': tabuleiro[linha + i][coluna + i] = 3; break;
            case 'A': tabuleiro[linha + i][coluna - i] = 3; break;
        }
    }
    return true;
}
