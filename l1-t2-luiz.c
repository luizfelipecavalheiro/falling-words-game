// l123b - t2
// programa para digitar palavras dentro do limite de tempo
// Luiz Felipe Cavalheiro dos Santos
// 2023-11-11

// Para rodar o jogo, digite: gcc l1-t2-luiz.c tecla.c tela.c -o l1-t2-luiz -lm && ./l1-t2-luiz

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "tecla.h"
#include "tela.h"

// definições de constantes
// quantas letras gerar
#define N_LETRA 16
// quantas palavras gerar
#define N_PALAVRAS 10
// quantos segundos para digitar
#define TEMPO 3 * N_PALAVRAS
// quantidade de jogadores no hall da fama
#define MAX_JOGADORES 3

// definições de structs
typedef struct {
  char palavra[N_LETRA];
  int pos_horizontal;
  int hora_ativacao;
  int tempo_digitacao;

}Palavra;

typedef struct {
  char nome[50];
  int pontos;
}Jogador;

// definições de funções
// retorna true se encontrou a letra
bool acha_letra(Palavra *palavras, int p_sel, char letra);
// remove a letra digitada
void remove_pos(Palavra *palavras, int p_sel);
// seleciona uma palavra das palavras
int seleciona_palavra(Palavra *palavras, int n_palavras, char l, double inicio);
// remove a palavra selecionada após ela ser totalmente digitada
void remove_palavra(Palavra *palavras, int p_sel);
// verifica se ja foi digitado todas as letras da palavra selecionada
bool palavra_selecionada_terminou(Palavra *palavras,int p_sel);
// verifica se caractere é valido
bool caractere_valido(char l);
// transforma caractere maiusculo em minusculo caso seja necessario
char converte_caractere(char l);
// verifica se numero esta no vetor
bool numero_jah_sorteado(int num, int vet[N_PALAVRAS]);
// apresenta o jogo
void apresentacao();
// faz o encerramento do jogo
void encerramento(int n_palavras, int pontos);
// executa uma partida
void jogo();
// verifica a vontade do jogador
bool quer_jogar_de_novo();
// sorteia palavras do arquivo
void preenche_palavras(Palavra *palavras);
// define posicao horizontal das palavras
void preenche_pos_horizontal(Palavra *palavras);
// define hora de ativacao das palavras
void preenche_hora_ativacao(Palavra *palavras);
// define tempo para digitacao das palavras
void preenche_tempo_digitacao(Palavra *palavras);
// limpa a linha de entrada
void espera_enter();
// lê uma tecla, vê se é a correta e age de acordo
void processa_entrada(Palavra *palavras, int *p_selecionada, int *n_palavras, int *pontos, double inicio, double *tempo_ultima_letra);
// mostra o estado do programa para o usuário 
void desenha_tela(Palavra *palavras, int n_palavra, int p_selecionada, int pontos, double inicio);
// retorna tamanho da palavra
int tam_palavra(char palavra[N_LETRA]);
// verifica se tempo de digitacao da palavra expirou
bool tempo_digitacao_expirou(Palavra *palavras, double inicio, int n_palavra);
// le recordes do jogo e armazena jogador e pontuacao
void le_recordes(Jogador* jogadores, int *num_jogadores);
// atualiza os recordes do jogo
void atualiza_recordes(Jogador* jogadores, int num_jogadores, int pontos);
// mostra recordes do jogo na tela
void mostra_recordes();
// verifica se pontuacao é uma das 3 maiores
bool pontuacao_top3(Jogador* jogadores, int num_jogadores, int pontos);


int main()
{
  // inicializa o gerador de números aleatórios
  srand(time(0));

	tela_ini();
	tecla_ini();

  do {
    apresentacao();
    jogo();
  } while (quer_jogar_de_novo());

  tecla_fim();
	tela_fim();
}

void jogo()
{
  int n_palavras = N_PALAVRAS;
  int p_selecionada = -1;  
  Palavra palavrass[N_PALAVRAS];
  
  preenche_palavras(palavrass);
  preenche_pos_horizontal(palavrass);
  preenche_hora_ativacao(palavrass);
  preenche_tempo_digitacao(palavrass);

  Jogador jogadores[MAX_JOGADORES];
  int num_jogadores = 0;
  
  le_recordes(jogadores,&num_jogadores);

  // quando o programa começou, para calcular o tempo restante
  double inicio = tela_relogio();
  double tempo_restante = TEMPO;
  double tempo_ultima_letra = 0.0;
  
  // quantas letras já foram acertadas
  int pontos = 0;
  
  while (tempo_restante > 0 && n_palavras > 0 ) {
    tempo_restante = TEMPO - (tela_relogio() - inicio);
    if (tempo_digitacao_expirou(palavrass,inicio,n_palavras)) {
      break;
    }
    processa_entrada(palavrass,&p_selecionada,&n_palavras,&pontos,inicio,&tempo_ultima_letra); 
    desenha_tela(palavrass, n_palavras, p_selecionada, pontos, inicio);
  }
  
  encerramento(n_palavras,pontos);
  
  if (pontuacao_top3(jogadores,num_jogadores,pontos)) {
    atualiza_recordes(jogadores,num_jogadores,pontos);
  }

  mostra_recordes();

}

void espera_enter()
{
  char l;
  do {
    l = tecla_le_char();
  } while (l != '\n'); 
  tela_atualiza();
}

void apresentacao()
{
  tela_limpa();
  tela_cor_normal();
  int lin = tela_nlin() / 3;
  int col = tela_ncol() / 2 - 70/2;
  
  tela_lincol(lin, col);
  tela_cor_letra(0,240,0);
  printf("+---------------------------------------------------------------------+");
  tela_lincol(++lin, col);
  printf("| ");
  tela_lincol(lin,col+2);
  tela_cor_normal();
  printf("Você deve digitar as palavras que aparecerão na tela");
  tela_cor_letra(0,240,0);
  tela_lincol(lin,col+70);
  printf("|");
  tela_lincol(++lin, col);
  printf("| ");
  tela_lincol(lin,col+2);
  tela_cor_normal();
  printf("Você deve digitar a primeira letra de uma palavra para selecioná-la ");
  tela_cor_letra(0,240,0);
  tela_lincol(lin,col+70);
  printf("|");
  tela_lincol(++lin, col);
  printf("| ");
  tela_lincol(lin,col+2);
  tela_cor_normal();
  printf("Então ela aparecerá na parte de baixo da tela entre setas");
  tela_cor_letra(0,240,0);
  tela_lincol(lin,col+70);
  printf("|");
  tela_lincol(++lin, col);
  printf("| ");
  tela_lincol(lin,col+2);
  tela_cor_normal();
  printf("Quanto mais baixa a palavra estiver, menor o tempo para digitá-la   ");
  tela_cor_letra(0,240,0);
  tela_lincol(lin,col+70);
  printf("|");
  tela_lincol(++lin, col);
  printf("+---------------------------------------------------------------------+");
  tela_lincol(++lin, tela_ncol() / 2 - 27 / 2);
  tela_cor_letra(250, 250, 30);
  printf("Tecle <enter> para iniciar");
  tela_atualiza();
  espera_enter();
}

void le_recordes(Jogador* jogadores, int *num_jogadores)
{
  FILE *arquivo;
  arquivo = fopen("recordes.txt", "r");

  if (arquivo == NULL) {
    arquivo = fopen("recordes.txt", "w");
    fclose(arquivo);
    arquivo = fopen("recordes.txt", "r");
  }
  
  char linha[100];
  int tamanho_nome;
  while (*num_jogadores < MAX_JOGADORES && fgets(linha, sizeof(linha), arquivo) != NULL) {
    size_t length = strlen(linha);
    if (linha[length - 1] == '\n') {
      linha[length - 1] = '\0';
    }

    if (sscanf(linha, "%*d) %[^-] - %d pontos", jogadores[*num_jogadores].nome, &jogadores[*num_jogadores].pontos) == 2) {
      tamanho_nome = strlen(jogadores[*num_jogadores].nome);
      jogadores[*num_jogadores].nome[tamanho_nome-1] = '\0'; //para retirar o carcatere de espaço
      (*num_jogadores)++;
    }
  }

  fclose(arquivo);
}

void encerramento(int n_palavra, int pontos)
{
  tela_limpa();

  int lin = tela_nlin() / 2 - 3;
  int col = tela_ncol() / 2 - 30/2;
  
  tela_lincol(lin, col);

  if (n_palavra <= 0) {
    tela_cor_letra(250, 250, 30);
    printf("PARABÉNS!! VOCÊ VENCEU!!!");
    tela_lincol(++lin, col);
  } else {
    tela_cor_letra(230, 10, 10);
    printf("FIM DE JOGO!!!");
    tela_lincol(++lin, col);
  }
  
  printf("TOTAL:  %d PONTOS",pontos);
  tela_lincol(++lin, col);
  printf("Tecle <enter> para seguir");

  tela_atualiza();
  espera_enter();
}

bool quer_jogar_de_novo()
{
  tela_limpa();
  tela_cor_letra(0,240,0);
  int lin = tela_nlin() / 3;
  int col = tela_ncol() / 2 - 46/2;
  tela_lincol(lin,col);
  printf("Digite 's' para jogar de novo ou 'n' para sair");
  tela_lincol(lin+1,col);
  printf(">: ");
  tela_atualiza();
  char c;
  while (true) {
    c = tecla_le_char();
    if (c == 's' || c == 'S') {
      return true;
    } else if (c == 'n' || c == 'N') {
      return false;
    }
  }
}

void preenche_palavras(Palavra *palavras)
{
  int linha_atual = 1, qtde_palavras_add = 0;
	int numeros_sorteados[N_PALAVRAS]; 
	int num_sorteado, j=0;
	char caractere;

  for (int i = 0; i < N_PALAVRAS; i++) {
    numeros_sorteados[i] = 0;
  }

	FILE *arquivo;
  arquivo = fopen("palavras", "r");

  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    exit(1);
  }

	while(qtde_palavras_add < N_PALAVRAS) {
		arquivo = fopen("palavras", "r");
		
		//numero sorteado nao pode estar no vetor
		do {
			num_sorteado = rand() % 920 + 1;
		} while(numero_jah_sorteado(num_sorteado,numeros_sorteados));

		// varre as linhas do arquivo até chegar na linha desejada
		while(linha_atual < num_sorteado && (caractere = fgetc(arquivo)) != EOF) {
			if (caractere == '\n')
				linha_atual++;
			if (linha_atual == num_sorteado)
			  break;
		}

		// adiciona caracteres na matriz
		do {
			caractere = fgetc(arquivo);
			if (caractere_valido(caractere)) {
				caractere = converte_caractere(caractere);
				palavras[qtde_palavras_add].palavra[j] = caractere;
				j++;
			} else {
				break;
			}
		} while(caractere != '\n');

		if (caractere == '\n') {
			palavras[qtde_palavras_add].palavra[j] = '\0';
			numeros_sorteados[qtde_palavras_add] = num_sorteado;
			qtde_palavras_add++;
		}

		linha_atual = 1;
		j = 0;
	}
	
	fclose(arquivo);
}

int seleciona_palavra(Palavra *palavras, int n_palavras, char l, double inicio)
{
  int menor_tempo_ativacao = 0;
  int pos = -1;
  for (int i = 0; i < n_palavras; i++) {
    if (palavras[i].palavra[0] == l && palavras[i].hora_ativacao <= tela_relogio() - inicio) {
      if (menor_tempo_ativacao == 0) {
        menor_tempo_ativacao = palavras[i].hora_ativacao;
        pos = i;
      } else if (palavras[i].hora_ativacao < menor_tempo_ativacao) {
        menor_tempo_ativacao = palavras[i].hora_ativacao;
        pos = i;
      }
    }
  }
  return pos;
}

bool acha_letra(Palavra *palavras, int p_sel, char letra)
{
  return palavras[p_sel].palavra[0] == letra;
}

void remove_pos(Palavra *palavras, int p_sel)
{
  int i = 0;
  while (palavras[p_sel].palavra[i] != '\0') {
    palavras[p_sel].palavra[i] = palavras[p_sel].palavra[i+1];
    i++;
  }
}

void remove_palavra(Palavra *palavras, int p_sel)
{
  Palavra aux;
  int i;
  for (i = p_sel; i < N_PALAVRAS; i++) {
    if (i == p_sel) {
      aux = palavras[i];
    }
    if (i+1 == N_LETRA) {
      palavras[i] = aux;
    } else {
      palavras[i] = palavras[i+1];
    }
  }
}

bool palavra_selecionada_terminou(Palavra *palavras,int p_sel)
{
  if (p_sel != -1 && palavras[p_sel].palavra[0] == '\0') {
    return true;
  } else {
    return false;   
  }
}

bool caractere_valido(char l)
{
	if((l >= 'A' && l <= 'Z') || (l >= 'a' && l <= 'z')) {
		return true;
	} else {
		return false;
  }
}

char converte_caractere(char l)
{
	if (l >= 'A' && l <= 'Z') {
		return l + 32;
  } else {
		return l;
  }
}

bool numero_jah_sorteado(int num, int vet[N_PALAVRAS])
{
	for (int i = 0;  i < N_PALAVRAS; i++) {
		if (vet[i] == num) {
			return true;
    }
	}
	return false;
}

void processa_entrada(Palavra *palavras, int *p_selecionada, int *n_palavras, int *pontos, double inicio, double *tempo_ultima_letra)
{
  //Se já terminou a palavra selecionada
  if (*p_selecionada != -1 && palavra_selecionada_terminou(palavras,*p_selecionada) ) {
    *n_palavras -= 1;
    remove_palavra(palavras,*p_selecionada);
    *p_selecionada = -1;
  }

  char letra;
  letra = tecla_le_char();

  if(*p_selecionada == -1){
    *p_selecionada = seleciona_palavra(palavras,*n_palavras,letra,inicio);
  }
    
  //se tem palavra selecionada e a letra esta correta, remove a letra
  if (*p_selecionada != -1) {
    if (acha_letra(palavras,*p_selecionada,letra)) {
      remove_pos(palavras, *p_selecionada);
      if (tela_relogio() - *tempo_ultima_letra >= 1) {
        *pontos += 1;
      } else {
        *pontos += 100 * (1 - (tela_relogio() - *tempo_ultima_letra));
      }
      *tempo_ultima_letra = tela_relogio();
      
    } else if(letra != '\0') {  
      if (*pontos - 10 < 0){
        *pontos = 0;
      } else {
        *pontos -= 10; 
      }
      *tempo_ultima_letra = tela_relogio();
    }    
  } 
}

void preenche_pos_horizontal(Palavra *palavras)
{
  for (int i = 0; i < N_PALAVRAS; i++) {
    palavras[i].pos_horizontal = rand() % 101;
  } 
}

void preenche_hora_ativacao(Palavra *palavras)
{
  for (int i = 0; i < N_PALAVRAS; i++) {
    palavras[i].hora_ativacao = rand() % (N_PALAVRAS * 2 + 1);
  } 
}

void preenche_tempo_digitacao(Palavra *palavras)
{
  for (int i = 0; i < N_PALAVRAS; i++) {
    palavras[i].tempo_digitacao = rand() % 26 + 5;
  } 
}

void desenha_tela(Palavra *palavras, int n_palavra, int p_selecionada, int pontos, double inicio)
{
  int i = 0, k = 0, lin = 0, col = 0, l_ini, alt, t_ativa;
  
  tela_limpa();
  tela_lincol(lin,tela_ncol()/2 - 20/2);
  printf("Pontuação: %d ",pontos);
  tela_lincol(lin+=2,0);
  while (k < tela_ncol()) {
    printf("_");
    k++;
  }
  k = 0;

  tela_cor_normal();
  

  while (i < n_palavra) {
    if (i != p_selecionada && palavras[i].hora_ativacao <= tela_relogio() - inicio) {
      col = (tela_ncol() - tam_palavra(palavras[i].palavra)) * palavras[i].pos_horizontal / 100;
      l_ini = 4;
      alt = tela_nlin() - 4;
      t_ativa = tela_relogio() - inicio - palavras[i].hora_ativacao;
      lin = l_ini + alt * t_ativa / palavras[i].tempo_digitacao;
      tela_lincol(lin,col);
      int j = 0;
      while (palavras[i].palavra[j] != '\0') {
        printf("%c", palavras[i].palavra[j]);
        j++;
        tela_atualiza();
      }
    }
    i++;
  }

  if (p_selecionada != -1) {
    col = tela_ncol()/2 - 20/2;
    lin = tela_nlin();
    tela_lincol(lin,col);
    tela_cor_letra(250, 250, 30);
    int j = 0;
    printf(">>>>> ");
    tela_lincol(lin,col+=7);
    while (palavras[p_selecionada].palavra[j] != '\0'){
      printf("%c", palavras[p_selecionada].palavra[j]);
      j++;
    }
    printf(" <<<<<");
  }

  tela_lincol(tela_nlin()-1,0);
  while (k < tela_ncol()) {
    printf("_");
    k++;
  }

  tela_atualiza();

}

int tam_palavra(char palavra[N_LETRA])
{
  int i = 0;
  while(palavra[i] != '\0'){
    i++;
  }
  return i--;
}

bool tempo_digitacao_expirou(Palavra *palavras, double inicio, int n_palavra)
{
  for (int i = 0;  i < n_palavra; i++) {
    if (tela_relogio() - inicio >= palavras[i].hora_ativacao &&  tela_relogio() - inicio > palavras[i].hora_ativacao + palavras[i].tempo_digitacao) {
        return true;
    }
  }
  return false;
}

void atualiza_recordes(Jogador* jogadores, int num_jogadores, int pontos)
{

  FILE *arquivo;
  arquivo = fopen("recordes.txt","w");

  if (arquivo == NULL) {
    return;
  }

  tela_limpa();
  int lin = tela_nlin() / 3;
  int col = tela_ncol() / 2 - 40 / 2;
  tela_lincol(lin,col);
  tela_cor_letra(0,240,0); 
  printf("VOCÊ VAI ENTRAR PRA HISTÓRIA!!!");
  tela_lincol(++lin,col);
  printf("Tecle <enter> duas vezes para seguir");
  tela_lincol(++lin,col);
  printf("Digite seu nome >: ");
  
  col+=18;
  int tam_nome = 30;
  char nome[tam_nome];
  
  int i = 0;
  char l;
  while (i < tam_nome-1) {
    l = tecla_le_char();
    if (l == '\n') {
      break;
    }

    if ((l == 8 || l == 127) && i > 0) {
      tela_lincol(lin,col);
      printf(" ");
      i--;
      col--;
      tela_lincol(lin,col+1);
    } else if (caractere_valido(l) || l == ' ') {
      tela_lincol(lin,++col);
      nome[i] = l;
      printf("%c",l);
      i++;
    }
    tela_atualiza();
  }
  nome[i] = '\0';

  // Encontra a posição correta da nova pontuação
  int posicao_inserir = num_jogadores;
  while (posicao_inserir > 0 && pontos > jogadores[posicao_inserir - 1].pontos) {
    posicao_inserir--;
  }

  // Insere a nova pontuação na posição adequada
  if (posicao_inserir < MAX_JOGADORES) {
    // Move as pontuações existentes para abrir espaço
    for (int i = num_jogadores - 1; i >= posicao_inserir; i--) {
      jogadores[i + 1] = jogadores[i];
    }
    
    Jogador player;
    int j = 0;

    do {
      player.nome[j] = nome[j];
      j++;
    }while(nome[j] != '\0');

    player.nome[j] = '\0';
    player.pontos = pontos;
    
    // Insere a nova pontuação
    jogadores[posicao_inserir] = player;

    // Atualiza o número de jogadores se necessário
    if (num_jogadores < MAX_JOGADORES) {
      num_jogadores++;
    }

    // Escreve as três maiores pontuações no arquivo
    for (int i = 0; i < num_jogadores; i++) {
      fprintf(arquivo, "%d) %s - %d pontos\n", i + 1, jogadores[i].nome, jogadores[i].pontos);
    }

  }
  
  tela_atualiza();
  espera_enter();
  fclose(arquivo);
}

void mostra_recordes()
{
  FILE *arquivo;
  arquivo = fopen("recordes.txt","r");

  if (arquivo == NULL) {
    exit(1);
  }

  int pos_ranking = 1;
  char linha[100];

  tela_limpa();

  int lin = tela_nlin() / 3;
  int col = tela_ncol() / 2 - 30/2;
  tela_lincol(lin, col); 
  tela_cor_letra(0,240,0); 
  printf("HALL DA FAMA!!!!");
  lin++;
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (pos_ranking == 1) {
      tela_cor_letra(255,223,0);
    } else if (pos_ranking == 2) {
      tela_cor_letra(192,192,192);
    } else {
      tela_cor_letra(153,101,21);
    }
    tela_lincol(++lin, col);
    printf("%s", linha);
    pos_ranking++;
  }
  tela_lincol(lin+=2,col);
  tela_cor_letra(0,240,0); 
  printf("Tecle <enter> para seguir");
  tela_cor_normal();
  tela_atualiza();
  espera_enter();

  fclose(arquivo);
}

bool pontuacao_top3(Jogador* jogadores, int num_jogadores, int pontos)
{
  if (num_jogadores < MAX_JOGADORES) {
    return true;
  } else {
    for(int i = 0; i < num_jogadores; i++) {
      if (pontos > jogadores[i].pontos) {
        return true;
      }
    }
  }
  return false;
}