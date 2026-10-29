// tokens.h
// Barra de tokens da IA (0 a 3), usada pelos tres atos.
// Este arquivo pertence ao nucleo. As duplas de ato so chamam as funcoes.
#ifndef TOKENS_H
#define TOKENS_H

#include <stdbool.h>

#define TOKENS_MAX 3

void Tokens_Reiniciar(void);   // novo jogo: volta para 3 e a reserva fica disponivel
void Tokens_Gastar(void);      // -1 (IA ajuda um pouco)
void Tokens_Recuperar(void);   // +1, maximo 3 (LIA faz sozinha)
void Tokens_Zerar(void);       // IA faz tudo
int  Tokens_Valor(void);       // 0 a 3
bool Tokens_IAOffline(void);   // true quando chega a 0

// Token de reserva (inicio do Ato 3). Se a barra estiver em 0 e a reserva
// ainda nao foi usada, a barra vai para 1 e a funcao devolve true.
// Nos outros casos nao faz nada e devolve false.
bool Tokens_UsarReserva(void);
bool Tokens_ReservaUsada(void);  // true depois que a reserva entrou (a barra mostra esse token em vermelho)

#endif
