/**
 * @file falling-words.c
 *
 * @brief Jogo para digitar palavras dentro do limite de tempo.
 *
 * Este programa implementa um jogo em que o jogador deve digitar palavras que aparecem
 * na tela dentro de um limite de tempo. O jogo é reiniciado se o jogador desejar jogar novamente.
 *
 * @author Luiz Felipe Cavalheiro
 *
 * @note Para rodar o jogo, digite: gcc falling-words.c funcoes.c tela.c tecla.c -o falling-words -lm && ./falling-words
 */

#include "funcoes.h"

/**
 * @brief Função principal do programa.
 *
 * Inicializa o gerador de números aleatórios, configura a interface gráfica e de teclado,
 * e executa o jogo. Apresenta a tela inicial e, enquanto o jogador desejar jogar novamente,
 * reinicia o jogo.
 *
 * @return Retorna 0 se a execução for bem-sucedida.
 */
int main()
{
  // Inicializa o gerador de números aleatórios
  srand(time(0));

  // Inicializa a interface gráfica e de teclado
  tela_ini();
  tecla_ini();

  do {
    // Apresenta a tela inicial
    apresentacao();

    // Executa o jogo
    jogo();

  } while (quer_jogar_de_novo());

  // Finaliza a interface de teclado e tela
  tecla_fim();
  tela_fim();

  return 0;
}
