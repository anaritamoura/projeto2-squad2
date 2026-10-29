// barra_tokens.h
// Desenho da barra de tokens da IA: uma unica bateria dividida em 3,
// como a bateria de um celular, ao lado do avatar da IA (estilo MSN).
// Le o valor de tokens.h; nao altera os tokens.
#ifndef BARRA_TOKENS_H
#define BARRA_TOKENS_H

void BarraTokens_Reiniciar(void);            // novo jogo: limpa as animacoes
void BarraTokens_Atualizar(void);            // uma vez por quadro (animacoes)
void BarraTokens_Desenhar(float x, float y); // canto superior esquerdo do painel

#define BARRA_LARGURA 270
#define BARRA_ALTURA  70

#endif
