// senha.h
// Minijogo da senha do PC (Ato 1, escolha A1-E1).
#ifndef SENHA_H
#define SENHA_H

#include <stdbool.h>

#define SENHA_CORRETA "0712"   // "07" do diario + "12" do calendario
#define SENHA_DIGITOS 4
#define SENHA_LIMITE_ERROS 5   // no 5o erro, a LIA volta para o quarto

void Senha_ComecarJogo(void);  // novo jogo: esquece se a ajuda ja foi aceita
void Senha_Iniciar(void);      // cada vez que a LIA senta no PC (zera os erros)
void Senha_Atualizar(void);    // uma vez por quadro
void Senha_Desenhar(void);     // entre BeginDrawing e EndDrawing

bool Senha_Concluida(void);           // acertou: segue para a conversa com a IA
bool Senha_PrecisaVoltarAoQuarto(void); // errou 5 vezes: volta para o quarto

// Botao "Tentar a senha novamente", para a cena do quarto.
// Use so depois que Senha_PrecisaVoltarAoQuarto() ficou true.
// Quando ele devolver true, chame Senha_Iniciar() e mostre o PC de novo.
bool Senha_BotaoTentarDeNovoClicado(void);  // no Atualizar da cena do quarto
void Senha_DesenharBotaoTentarDeNovo(void); // no Desenhar da cena do quarto

#endif
