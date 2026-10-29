// tokens_provisorio.c
// Versao PROVISORIA da barra de tokens, so para testar o Ato 1 sozinho.
// Quando o nucleo entregar a versao oficial, apague este arquivo e
// compile com o arquivo do nucleo no lugar. Nada mais muda.
#include "tokens.h"

static int  tokens = TOKENS_MAX;
static bool reservaUsada = false;

void Tokens_Reiniciar(void)
{
    tokens = TOKENS_MAX;
    reservaUsada = false;
}

void Tokens_Gastar(void)
{
    if (tokens > 0) tokens--;
}

void Tokens_Recuperar(void)
{
    if (tokens < TOKENS_MAX) tokens++;
}

void Tokens_Zerar(void) { tokens = 0; }

int Tokens_Valor(void) { return tokens; }

bool Tokens_IAOffline(void) { return tokens == 0; }

bool Tokens_UsarReserva(void)
{
    if (tokens != 0 || reservaUsada) return false;
    reservaUsada = true;
    tokens = 1;
    return true;
}

bool Tokens_ReservaUsada(void) { return reservaUsada; }
