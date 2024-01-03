/**
 * @file jogo.h
 * 
 * @brief Definição das funções para o jogo de digitação.
 * 
 * @author Luiz Felipe Cavalheiro
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "tecla.h"
#include "tela.h"


#ifndef JOGO_H
#define JOGO_H

// definições de constantes
#define N_LETRA 16   /**< Número de letras a serem geradas. */
#define N_PALAVRAS 10 /**< Número de palavras a serem geradas. */
#define TEMPO 3 * N_PALAVRAS /**< Tempo total para digitar as palavras (em segundos). */
#define MAX_JOGADORES 3 /**< Número máximo de jogadores no hall da fama. */

// definições de structs
/**
 * @brief Estrutura que representa uma palavra no jogo.
 */
typedef struct {
  char palavra[N_LETRA];   /**< Palavra a ser digitada. */
  int pos_horizontal;      /**< Posição horizontal da palavra na tela. */
  int hora_ativacao;       /**< Hora em que a palavra foi ativada. */
  int tempo_digitacao;      /**< Tempo permitido para a digitação da palavra. */
} Palavra;

/**
 * @brief Estrutura que representa um jogador no hall da fama.
 */
typedef struct {
  char nome[50];  /**< Nome do jogador. */
  int pontos;     /**< Pontuação do jogador. */
} Jogador;

// definições de funções

/**
 * @brief Verifica se a letra foi encontrada na palavra.
 *
 * @param palavras Vetor de palavras.
 * @param p_sel Índice da palavra selecionada.
 * @param letra Letra a ser verificada.
 * @return Retorna true se a letra foi encontrada na palavra, false caso contrário.
 */
bool acha_letra(Palavra *palavras, int p_sel, char letra);

/**
 * @brief Remove a letra digitada.
 *
 * @param palavras Vetor de palavras.
 * @param p_sel Índice da palavra selecionada.
 */
void remove_pos(Palavra *palavras, int p_sel);

/**
 * @brief Seleciona uma palavra das palavras.
 *
 * @param palavras Vetor de palavras.
 * @param n_palavras Número total de palavras.
 * @param l Letra para determinar a palavra.
 * @param inicio Tempo de início da partida.
 * @return Índice da palavra selecionada.
 */
int seleciona_palavra(Palavra *palavras, int n_palavras, char l, double inicio);

/**
 * @brief Remove a palavra selecionada após ela ser totalmente digitada.
 *
 * @param palavras Vetor de palavras.
 * @param p_sel Índice da palavra selecionada.
 */
void remove_palavra(Palavra *palavras, int p_sel);

/**
 * @brief Verifica se todas as letras da palavra selecionada foram digitadas.
 *
 * @param palavras Vetor de palavras.
 * @param p_sel Índice da palavra selecionada.
 * @return Retorna true se todas as letras foram digitadas, false caso contrário.
 */
bool palavra_selecionada_terminou(Palavra *palavras, int p_sel);

/**
 * @brief Verifica se o caractere é válido.
 *
 * @param l Caractere a ser verificado.
 * @return Retorna true se o caractere for válido, false caso contrário.
 */
bool caractere_valido(char l);

/**
 * @brief Transforma o caractere maiúsculo em minúsculo, se necessário.
 *
 * @param l Caractere a ser convertido.
 * @return Caractere convertido.
 */
char converte_caractere(char l);

/**
 * @brief Verifica se o número já foi sorteado no vetor.
 *
 * @param num Número a ser verificado.
 * @param vet Vetor de números já sorteados.
 * @return Retorna true se o número já foi sorteado, false caso contrário.
 */
bool numero_jah_sorteado(int num, int vet[N_PALAVRAS]);

/**
 * @brief Apresenta o jogo.
 */
void apresentacao();

/**
 * @brief Faz o encerramento do jogo.
 *
 * @param n_palavras Número total de palavras no jogo.
 * @param pontos Pontuação final do jogador.
 */
void encerramento(int n_palavras, int pontos);

/**
 * @brief Executa uma partida.
 */
void jogo();

/**
 * @brief Verifica a vontade do jogador de jogar novamente.
 *
 * @return Retorna true se o jogador quiser jogar novamente, false caso contrário.
 */
bool quer_jogar_de_novo();

/**
 * @brief Preenche o vetor de palavras com palavras sorteadas.
 *
 * @param palavras Vetor de palavras.
 */
void preenche_palavras(Palavra *palavras);

/**
 * @brief Define a posição horizontal das palavras.
 *
 * @param palavras Vetor de palavras.
 */
void preenche_pos_horizontal(Palavra *palavras);

/**
 * @brief Define a hora de ativação das palavras.
 *
 * @param palavras Vetor de palavras.
 */
void preenche_hora_ativacao(Palavra *palavras);

/**
 * @brief Define o tempo para digitação das palavras.
 *
 * @param palavras Vetor de palavras.
 */
void preenche_tempo_digitacao(Palavra *palavras);

/**
 * @brief Limpa a linha de entrada.
 */
void espera_enter();

/**
 * @brief Lê uma tecla, verifica se é a correta e age de acordo.
 *
 * @param palavras Vetor de palavras.
 * @param p_selecionada Índice da palavra selecionada.
 * @param n_palavras Número total de palavras.
 * @param pontos Pontuação do jogador.
 * @param inicio Tempo de início da partida.
 * @param tempo_ultima_letra Tempo da última letra digitada.
 */
void processa_entrada(Palavra *palavras, int *p_selecionada, int *n_palavras, int *pontos, double inicio, double *tempo_ultima_letra);

/**
 * @brief Mostra o estado do programa para o usuário.
 *
 * @param palavras Vetor de palavras.
 * @param n_palavra Índice da palavra atual.
 * @param p_selecionada Índice da palavra selecionada.
 * @param pontos Pontuação do jogador.
 * @param inicio Tempo de início da partida.
 */
void desenha_tela(Palavra *palavras, int n_palavra, int p_selecionada, int pontos, double inicio);

/**
 * @brief Retorna o tamanho da palavra.
 *
 * @param palavra Palavra a ser medida.
 * @return Tamanho da palavra.
 */
int tam_palavra(char palavra[N_LETRA]);

/**
 * @brief Verifica se o tempo de digitação da palavra expirou.
 *
 * @param palavras Vetor de palavras.
 * @param inicio Tempo de início da partida.
 * @param n_palavra Índice da palavra atual.
 * @return Retorna true se o tempo de digitação expirou, false caso contrário.
 */
bool tempo_digitacao_expirou(Palavra *palavras, double inicio, int n_palavra);

/**
 * @brief Lê os recordes do jogo e armazena o jogador e a pontuação.
 *
 * @param jogadores Vetor de jogadores.
 * @param num_jogadores Número total de jogadores.
 */
void le_recordes(Jogador *jogadores, int *num_jogadores);

/**
 * @brief Atualiza os recordes do jogo.
 *
 * @param jogadores Vetor de jogadores.
 * @param num_jogadores Número total de jogadores.
 * @param pontos Pontuação do jogador.
 */
void atualiza_recordes(Jogador *jogadores, int num_jogadores, int pontos);

/**
 * @brief Mostra os recordes do jogo na tela.
 */
void mostra_recordes();

/**
 * @brief Verifica se a pontuação está entre as 3 melhores.
 *
 * @param jogadores Vetor de jogadores.
 * @param num_jogadores Número total de jogadores.
 * @param pontos Pontuação do jogador.
 * @return Retorna true se a pontuação estiver entre as 3 melhores, false caso contrário.
 */
bool pontuacao_top3(Jogador *jogadores, int num_jogadores, int pontos);

#endif /* JOGO_H */
