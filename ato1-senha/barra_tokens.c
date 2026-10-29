// barra_tokens.c
// Barra de tokens da IA: painel de vidro, avatar redondo da IA com status
// do MSN e UMA bateria dividida em 3 partes, como a de um celular.
//
// Cores da bateria:
// - tokens normais: azul;
// - token de reserva (Ato 3): vermelho;
// - partes vazias e barra em 0: cinza (com 0, o status vira "offline").
//
// Animacoes:
// - ao perder um token, a parte vai do azul para o cinza;
// - ao ganhar um token (sozinha ou reserva), a parte acende com brilho rosa.

#include "barra_tokens.h"
#include "tokens.h"
#include "raylib.h"
#include <math.h>

#define COR_CLARA    (Color){ 232, 240, 250, 255 }  // #E8F0FA
#define COR_AZUL_MED (Color){ 143, 178, 213, 255 }  // #8FB2D5
#define COR_MARINHO  (Color){  29,  38,  96, 255 }  // #1D2660
#define COR_ROSA     (Color){ 227,  93, 215, 255 }  // #E35DD7
#define COR_AZUL     (Color){  39, 172, 234, 255 }  // #27ACEA
#define COR_VERMELHO (Color){ 234,  84, 119, 255 }  // #EA5477
#define COR_VERDE    (Color){  76, 175,  80, 255 }
#define COR_CINZA    (Color){ 150, 156, 170, 255 }

#define DURACAO_ANIM 0.6f

static int   valorAnterior = -1;
static float animPerda[TOKENS_MAX];   // tempo restante da animacao de perda
static float animGanho[TOKENS_MAX];   // tempo restante da animacao de ganho
static float tempoTotal = 0.0f;       // para o brilho "respirando"

void BarraTokens_Reiniciar(void)
{
    for (int i = 0; i < TOKENS_MAX; i++) {
        animPerda[i] = 0.0f;
        animGanho[i] = 0.0f;
    }
    valorAnterior = Tokens_Valor();
}

void BarraTokens_Atualizar(void)
{
    float dt = GetFrameTime();
    tempoTotal += dt;

    int atual = Tokens_Valor();
    if (valorAnterior < 0) valorAnterior = atual;

    if (atual < valorAnterior) {
        for (int i = atual; i < valorAnterior; i++) animPerda[i] = DURACAO_ANIM;
    } else if (atual > valorAnterior) {
        for (int i = valorAnterior; i < atual; i++) animGanho[i] = DURACAO_ANIM;
    }
    valorAnterior = atual;

    for (int i = 0; i < TOKENS_MAX; i++) {
        if (animPerda[i] > 0.0f) animPerda[i] -= dt;
        if (animGanho[i] > 0.0f) animGanho[i] -= dt;
    }
}

// Mistura duas cores (t = 0 da a primeira, t = 1 da a segunda)
static Color Misturar(Color a, Color b, float t)
{
    return (Color){ (unsigned char)(a.r + (b.r - a.r) * t),
                    (unsigned char)(a.g + (b.g - a.g) * t),
                    (unsigned char)(a.b + (b.b - a.b) * t), 255 };
}

// Reflexo branco na metade de cima, que da o efeito de vidro
static void Reflexo(Rectangle r, float opacidade)
{
    Rectangle topo = { r.x + 3, r.y + 2, r.width - 6, r.height * 0.42f };
    DrawRectangleRounded(topo, 1.0f, 8, Fade(WHITE, opacidade));
}

static void DesenharBateria(Rectangle corpo, int valor, bool offline)
{
    Color contorno = offline ? COR_CINZA : COR_MARINHO;

    // corpo e polo da bateria
    DrawRectangleRounded(corpo, 0.35f, 8, Fade(COR_MARINHO, 0.10f));
    DrawRectangleRoundedLinesEx(corpo, 0.35f, 8, 2.5f, contorno);
    Rectangle polo = { corpo.x + corpo.width + 2, corpo.y + corpo.height * 0.3f, 6, corpo.height * 0.4f };
    DrawRectangleRounded(polo, 0.5f, 4, contorno);

    float pulso = 0.85f + 0.15f * (0.5f + 0.5f * sinf(tempoTotal * 3.0f));

    // 3 partes dentro do mesmo corpo
    float margem = 4.0f, espaco = 3.0f;
    float largParte = (corpo.width - 2 * margem - 2 * espaco) / 3.0f;
    float altParte  = corpo.height - 2 * margem;

    for (int i = 0; i < TOKENS_MAX; i++) {
        Rectangle parte = { corpo.x + margem + i * (largParte + espaco), corpo.y + margem, largParte, altParte };
        bool cheia = (i < valor) && !offline;
        // o primeiro token e o da reserva quando ela ja entrou
        Color nivel = (i == 0 && Tokens_ReservaUsada()) ? COR_VERMELHO : COR_AZUL;

        if (cheia) {
            // degrade de cima (mais claro) para baixo
            Color topo = Misturar(nivel, WHITE, 0.25f);
            DrawRectangleGradientV((int)parte.x, (int)parte.y, (int)parte.width, (int)parte.height,
                                   Fade(topo, pulso), Fade(nivel, pulso));
            Reflexo(parte, 0.45f);
        } else {
            DrawRectangleRec(parte, Fade(COR_CINZA, 0.30f));
        }

        // perdeu este token: a cor de antes some aos poucos e fica o cinza
        if (animPerda[i] > 0.0f) {
            float t = animPerda[i] / DURACAO_ANIM;           // 1 -> 0
            DrawRectangleRec(parte, Fade(nivel, t));
        }
        // ganhou este token: brilho rosa que cresce e some
        if (animGanho[i] > 0.0f) {
            float t = animGanho[i] / DURACAO_ANIM;
            float extra = (1.0f - t) * 6.0f;
            Rectangle aura = { parte.x - extra, parte.y - extra, parte.width + 2 * extra, parte.height + 2 * extra };
            DrawRectangleLinesEx(aura, 2.5f, Fade(COR_ROSA, t));
        }
    }

    // brilho de vidro por cima de tudo
    Reflexo(corpo, 0.25f);
}

void BarraTokens_Desenhar(float x, float y)
{
    int valor = Tokens_Valor();
    bool offline = Tokens_IAOffline();

    // painel de vidro
    Rectangle painel = { x, y, BARRA_LARGURA, BARRA_ALTURA };
    DrawRectangleRounded((Rectangle){ x + 3, y + 4, painel.width, painel.height }, 0.5f, 12,
                         Fade(BLACK, 0.25f));                       // sombra
    DrawRectangleRounded(painel, 0.5f, 12, Fade(COR_CLARA, 0.92f));
    Reflexo(painel, 0.6f);
    DrawRectangleRoundedLinesEx(painel, 0.5f, 12, 2.0f, offline ? COR_CINZA : COR_AZUL);

    // avatar redondo da IA (bolha do MSN)
    Vector2 c = { x + 36, y + BARRA_ALTURA / 2.0f };
    Color corOrbe = offline ? COR_CINZA : COR_AZUL;
    DrawCircleV(c, 25, offline ? COR_CINZA : COR_MARINHO);
    for (int k = 0; k < 8; k++) {   // degrade feito com circulos
        float raio = 22.0f - k * 2.0f;
        DrawCircleV((Vector2){ c.x, c.y + k * 0.6f }, raio, Misturar(corOrbe, COR_CLARA, k / 14.0f));
    }
    DrawEllipse((int)c.x, (int)c.y - 13, 13, 6, Fade(WHITE, 0.45f));
    int largIA = MeasureText("IA", 20);
    DrawText("IA", (int)c.x - largIA / 2 + 1, (int)c.y - 7, 20, Fade(COR_MARINHO, 0.6f));
    DrawText("IA", (int)c.x - largIA / 2, (int)c.y - 8, 20, WHITE);

    // status do MSN
    Vector2 st = { c.x + 17, c.y + 17 };
    DrawCircleV(st, 8, WHITE);
    DrawCircleV(st, 6, offline ? COR_CINZA : COR_VERDE);

    // titulo, status e contagem
    DrawText("Tokens da IA", (int)x + 72, (int)y + 10, 10, COR_MARINHO);
    const char *status = offline ? "offline" : "online";
    DrawText(status, (int)x + BARRA_LARGURA - 18 - MeasureText(status, 10), (int)y + 10, 10,
             offline ? COR_CINZA : COR_VERDE);

    // bateria unica dividida em 3
    Rectangle corpo = { x + 72, y + 28, 140, 30 };
    DesenharBateria(corpo, valor, offline);

    // numero ao lado, como "3/3"
    const char *txt = TextFormat("%d/%d", valor, TOKENS_MAX);
    DrawText(txt, (int)(corpo.x + corpo.width + 18), (int)corpo.y + 8, 16,
             offline ? COR_CINZA : COR_MARINHO);
}
