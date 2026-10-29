// senha.c
// Minijogo da senha do PC (Ato 1).
//
// Regras (roteiro, Ato 1, escolha A1-E1):
// - A senha tem 4 digitos: 0712. Pistas: "07" na capa do diario e
//   o dia 12 circulado no calendario do quarto.
// - O campo limpa sozinho a cada erro.
// - No 2o e no 4o erro, a IA oferece ajuda num pop-up de MSN:
//     1. Mostrar onde errei     -> Tokens_Gastar()    (-1)
//     2. Tentar de novo sozinha -> Tokens_Recuperar() (+1, max. 3)
// - Se a jogadora aceitar a ajuda UMA vez, o pop-up nunca mais aparece.
//   Assim a senha gasta no maximo 1 token no jogo inteiro.
// - "Mostrar onde errei" marca os digitos certos e errados da ultima
//   tentativa.
// - No 5o erro, a LIA diz uma fala e volta para o quarto. Sair nao custa
//   token. No quarto aparece o botao "Tentar a senha novamente"; ao clicar,
//   a jogadora volta ao PC e os erros recomecam do zero.
// - Ao voltar do quarto, vale a mesma regra do pop-up:
//     ainda nao aceitou a ajuda -> o pop-up aparece de novo no 2o e no 4o erro;
//     ja aceitou a ajuda        -> o pop-up nao aparece mais.
//   No 5o erro, volta ao quarto de novo.

#include "senha.h"
#include "tokens.h"
#include "raylib.h"
#include <string.h>

// ---------- cores (paleta do kit visual) ----------
#define COR_CLARA    (Color){ 232, 240, 250, 255 }  // #E8F0FA
#define COR_AZUL_MED (Color){ 143, 178, 213, 255 }  // #8FB2D5
#define COR_MARINHO  (Color){  29,  38,  96, 255 }  // #1D2660
#define COR_ROSA     (Color){ 227,  93, 215, 255 }  // #E35DD7
#define COR_AZUL     (Color){  39, 172, 234, 255 }  // #27ACEA
#define COR_VERMELHO (Color){ 234,  84, 119, 255 }  // #EA5477
#define COR_VERDE    (Color){  76, 175,  80, 255 }  // status "online" do MSN

// ---------- estado ----------
typedef enum {
    SENHA_DIGITANDO,
    SENHA_POPUP_IA,
    SENHA_ACERTOU,      // mostra a senha certa por um instante
    SENHA_FIM,
    SENHA_FALA_SAIDA,   // fala da LIA antes de voltar para o quarto
    SENHA_SAIU
} EstadoSenha;

static EstadoSenha estado;
static char digitado[SENHA_DIGITOS + 1];
static int  quantidade;            // quantos digitos ja foram digitados
static int  erros;                 // erros desde que a LIA sentou no PC
static bool ajudaAceita;           // vale para o jogo inteiro

static char ultimaTentativa[SENHA_DIGITOS + 1];
static bool mostrarMarcas;
static char tentativaMarcada[SENHA_DIGITOS + 1];
static bool digitoCerto[SENHA_DIGITOS];

static float tempoAvisoErro;       // segundos restantes do aviso "Senha incorreta"
static float tempoAcerto;          // pausa depois de acertar

// ---------- posicoes (tela 1280 x 720) ----------
static const Rectangle PAINEL   = { 380, 170, 520, 330 };
static const Rectangle POPUP    = { 360, 210, 560, 250 };
static const Rectangle BOTAO_1  = { 395, 345, 490, 40 };
static const Rectangle BOTAO_2  = { 395, 395, 490, 40 };
static const Rectangle BOTAO_TENTAR_DE_NOVO = { 880, 630, 370, 56 };  // canto inferior direito do quarto

#define CAIXA_LARG 70
#define CAIXA_ALT  80
#define CAIXA_ESPACO 20
#define CAIXAS_Y 260

// ---------- funcoes auxiliares ----------
static float CaixaX(int i)
{
    float larguraTotal = SENHA_DIGITOS * CAIXA_LARG + (SENHA_DIGITOS - 1) * CAIXA_ESPACO;
    float inicio = PAINEL.x + (PAINEL.width - larguraTotal) / 2.0f;
    return inicio + i * (CAIXA_LARG + CAIXA_ESPACO);
}

static void TextoCentralizado(const char *texto, float centroX, float y, int tamanho, Color cor)
{
    int largura = MeasureText(texto, tamanho);
    DrawText(texto, (int)(centroX - largura / 2.0f), (int)y, tamanho, cor);
}

static void LimparDigitado(void)
{
    memset(digitado, 0, sizeof(digitado));
    quantidade = 0;
}

static void ConferirTentativa(void)
{
    if (strcmp(digitado, SENHA_CORRETA) == 0) {
        estado = SENHA_ACERTOU;
        tempoAcerto = 1.0f;
        return;
    }

    erros++;
    strcpy(ultimaTentativa, digitado);
    LimparDigitado();
    tempoAvisoErro = 1.5f;

    if (erros >= SENHA_LIMITE_ERROS) {
        estado = SENHA_FALA_SAIDA;
    } else if (!ajudaAceita && erros % 2 == 0) {
        estado = SENHA_POPUP_IA;   // 2o e 4o erro
    }
}

static void EscolherMostrarOndeErrei(void)
{
    Tokens_Gastar();
    ajudaAceita = true;
    strcpy(tentativaMarcada, ultimaTentativa);
    for (int i = 0; i < SENHA_DIGITOS; i++) {
        digitoCerto[i] = (tentativaMarcada[i] == SENHA_CORRETA[i]);
    }
    mostrarMarcas = true;
    estado = SENHA_DIGITANDO;
}

static void EscolherTentarSozinha(void)
{
    Tokens_Recuperar();
    estado = SENHA_DIGITANDO;
}

// Botao com mudanca de cor quando o mouse passa por cima (US11).
// Devolve true no quadro em que foi clicado.
static bool Botao(Rectangle r, const char *texto, bool desenhar)
{
    bool emCima = CheckCollisionPointRec(GetMousePosition(), r);

    if (desenhar) {
        Color fundo = emCima ? COR_AZUL : COR_CLARA;
        Color letra = emCima ? COR_CLARA : COR_MARINHO;
        DrawRectangleRounded(r, 0.5f, 8, fundo);
        DrawRectangleRoundedLinesEx(r, 0.5f, 8, 2.0f, COR_AZUL);
        TextoCentralizado(texto, r.x + r.width / 2.0f, r.y + 10, 20, letra);
    }

    return emCima && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

// ---------- funcoes publicas ----------
void Senha_ComecarJogo(void)
{
    ajudaAceita = false;
    mostrarMarcas = false;
    memset(tentativaMarcada, 0, sizeof(tentativaMarcada));
    Senha_Iniciar();
}

void Senha_Iniciar(void)
{
    // As marcas da ajuda continuam na tela se a LIA voltar ao PC.
    estado = SENHA_DIGITANDO;
    LimparDigitado();
    erros = 0;
    memset(ultimaTentativa, 0, sizeof(ultimaTentativa));
    tempoAvisoErro = 0.0f;
    tempoAcerto = 0.0f;
}

void Senha_Atualizar(void)
{
    float dt = GetFrameTime();
    if (tempoAvisoErro > 0.0f) tempoAvisoErro -= dt;

    switch (estado) {
    case SENHA_DIGITANDO: {
        int tecla = GetCharPressed();
        while (tecla > 0) {
            if (tecla >= '0' && tecla <= '9' && quantidade < SENHA_DIGITOS) {
                digitado[quantidade++] = (char)tecla;
            }
            tecla = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && quantidade > 0) {
            digitado[--quantidade] = '\0';
        }

        bool enter = IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER);
        if (enter && quantidade == SENHA_DIGITOS) {
            ConferirTentativa();
        }
    } break;

    case SENHA_POPUP_IA:
        if (Botao(BOTAO_1, "", false) || IsKeyPressed(KEY_ONE)) {
            EscolherMostrarOndeErrei();
        } else if (Botao(BOTAO_2, "", false) || IsKeyPressed(KEY_TWO)) {
            EscolherTentarSozinha();
        }
        break;

    case SENHA_ACERTOU:
        tempoAcerto -= dt;
        if (tempoAcerto <= 0.0f) estado = SENHA_FIM;
        break;

    case SENHA_FALA_SAIDA:
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) ||
            IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            estado = SENHA_SAIU;
        }
        break;

    case SENHA_FIM:
    case SENHA_SAIU:
        break;
    }
}

void Senha_Desenhar(void)
{
    // Fundo da tela de bloqueio, inspirado no login do Windows XP
    DrawRectangleGradientV(0, 0, 1280, 720, COR_MARINHO, COR_AZUL);

    // Painel
    DrawRectangleRounded(PAINEL, 0.08f, 8, COR_CLARA);
    DrawRectangleRoundedLinesEx(PAINEL, 0.08f, 8, 3.0f, COR_AZUL_MED);
    float centro = PAINEL.x + PAINEL.width / 2.0f;
    TextoCentralizado("LIA", centro, PAINEL.y + 25, 30, COR_MARINHO);
    TextoCentralizado("Digite a senha para entrar", centro, PAINEL.y + 62, 20, COR_MARINHO);

    // Caixas dos digitos
    bool acertou = (estado == SENHA_ACERTOU || estado == SENHA_FIM);
    for (int i = 0; i < SENHA_DIGITOS; i++) {
        Rectangle caixa = { CaixaX(i), CAIXAS_Y, CAIXA_LARG, CAIXA_ALT };
        Color borda = acertou ? COR_VERDE : (i == quantidade ? COR_ROSA : COR_AZUL_MED);
        DrawRectangleRec(caixa, WHITE);
        DrawRectangleLinesEx(caixa, 3.0f, borda);

        char d[2] = { 0 };
        d[0] = acertou ? SENHA_CORRETA[i] : digitado[i];
        if (d[0] != '\0') {
            TextoCentralizado(d, caixa.x + CAIXA_LARG / 2.0f, caixa.y + 18, 44, COR_MARINHO);
        }
    }

    // Marcas da ajuda da IA (so depois de "Mostrar onde errei")
    if (mostrarMarcas && !acertou) {
        TextoCentralizado("Sua tentativa anterior:", centro, CAIXAS_Y + 95, 16, COR_MARINHO);
        for (int i = 0; i < SENHA_DIGITOS; i++) {
            float x = CaixaX(i) + 15;
            float y = CAIXAS_Y + 118;
            Rectangle marca = { x, y, 40, 40 };
            Color cor = digitoCerto[i] ? COR_VERDE : COR_VERMELHO;
            DrawRectangleRec(marca, cor);

            char d[2] = { tentativaMarcada[i], '\0' };
            DrawText(d, (int)x + 4, (int)y + 2, 18, WHITE);

            // simbolo desenhado com linhas: certo (V) ou errado (X)
            if (digitoCerto[i]) {
                DrawLineEx((Vector2){ x + 18, y + 26 }, (Vector2){ x + 24, y + 33 }, 3.0f, WHITE);
                DrawLineEx((Vector2){ x + 24, y + 33 }, (Vector2){ x + 35, y + 18 }, 3.0f, WHITE);
            } else {
                DrawLineEx((Vector2){ x + 20, y + 18 }, (Vector2){ x + 34, y + 34 }, 3.0f, WHITE);
                DrawLineEx((Vector2){ x + 34, y + 18 }, (Vector2){ x + 20, y + 34 }, 3.0f, WHITE);
            }
        }
    }

    // Dica da senha (campo de dica do Windows XP)
    float yDica = mostrarMarcas ? CAIXAS_Y + 170 : CAIXAS_Y + 110;
    TextoCentralizado("Dica da senha: o ano + o dia que eu não posso esquecer.",
                      centro, yDica, 18, COR_MARINHO);

    // Contador de erros, para a jogadora saber quando volta ao quarto
    if (!acertou && erros > 0) {
        TextoCentralizado(TextFormat("Tentativas erradas: %d de %d", erros, SENHA_LIMITE_ERROS),
                          centro, PAINEL.y + PAINEL.height - 30, 16, COR_VERMELHO);
    }

    // Aviso de erro ou de acerto
    if (acertou) {
        TextoCentralizado("Senha correta!", centro, PAINEL.y + PAINEL.height + 20, 24, COR_CLARA);
    } else if (tempoAvisoErro > 0.0f) {
        TextoCentralizado("Senha incorreta.", centro, PAINEL.y + PAINEL.height + 20, 24, COR_VERMELHO);
    }

    TextoCentralizado("Digite os números e aperte ENTER. BACKSPACE apaga.",
                      640, 680, 18, COR_CLARA);

    // Pop-up de MSN da IA
    if (estado == SENHA_POPUP_IA) {
        DrawRectangle(0, 0, 1280, 720, Fade(BLACK, 0.4f));

        DrawRectangleRec(POPUP, COR_CLARA);
        DrawRectangleLinesEx(POPUP, 2.0f, COR_AZUL);
        Rectangle barraTitulo = { POPUP.x, POPUP.y, POPUP.width, 34 };
        DrawRectangleGradientH((int)barraTitulo.x, (int)barraTitulo.y,
                               (int)barraTitulo.width, (int)barraTitulo.height,
                               COR_AZUL, COR_MARINHO);
        DrawCircle((int)POPUP.x + 20, (int)POPUP.y + 17, 7, COR_VERDE);
        DrawText("IA (online)", (int)POPUP.x + 35, (int)POPUP.y + 8, 20, COR_CLARA);

        DrawText("IA diz:", (int)POPUP.x + 25, (int)POPUP.y + 55, 18, COR_AZUL);
        // 2o erro: primeira oferta. 4o erro: a IA insiste.
        const char *linha1 = (erros >= 4) ? "Mais duas tentativas erradas. Ainda posso"
                                          : "Duas tentativas erradas. Posso mostrar onde";
        const char *linha2 = (erros >= 4) ? "mostrar onde você errou."
                                          : "você errou ou você tenta de novo.";
        DrawText(linha1, (int)POPUP.x + 25, (int)POPUP.y + 80, 20, COR_MARINHO);
        DrawText(linha2, (int)POPUP.x + 25, (int)POPUP.y + 105, 20, COR_MARINHO);

        Botao(BOTAO_1, "1. Mostrar onde errei (-1 token)", true);
        Botao(BOTAO_2, "2. Tentar de novo sozinha", true);
    }

    // Fala da LIA no 5o erro, numa caixa de dialogo
    if (estado == SENHA_FALA_SAIDA) {
        DrawRectangle(0, 0, 1280, 720, Fade(BLACK, 0.4f));
        Rectangle caixa = { 40, 540, 1200, 150 };
        DrawRectangleRounded(caixa, 0.15f, 8, Fade(COR_CLARA, 0.95f));
        DrawRectangleRoundedLinesEx(caixa, 0.15f, 8, 3.0f, COR_AZUL);
        DrawText("LIA", (int)caixa.x + 30, (int)caixa.y + 20, 24, COR_ROSA);
        DrawText("Calma. Deve ter alguma pista aqui no quarto.",
                 (int)caixa.x + 30, (int)caixa.y + 60, 24, COR_MARINHO);
        DrawText("ENTER para continuar", (int)(caixa.x + caixa.width) - 230,
                 (int)(caixa.y + caixa.height) - 35, 18, COR_AZUL_MED);
    }
}

// ---------- botao "Tentar a senha novamente" (cena do quarto) ----------
bool Senha_BotaoTentarDeNovoClicado(void)
{
    if (estado != SENHA_SAIU) return false;
    return Botao(BOTAO_TENTAR_DE_NOVO, "", false);
}

void Senha_DesenharBotaoTentarDeNovo(void)
{
    if (estado != SENHA_SAIU) return;

    Rectangle r = BOTAO_TENTAR_DE_NOVO;
    bool emCima = CheckCollisionPointRec(GetMousePosition(), r);

    // sombra, corpo com degrade e reflexo de vidro (estilo XP / Frutiger Aero)
    DrawRectangleRounded((Rectangle){ r.x + 3, r.y + 4, r.width, r.height }, 0.5f, 10, Fade(BLACK, 0.3f));
    DrawRectangleRounded(r, 0.5f, 10, emCima ? COR_ROSA : COR_AZUL);
    DrawRectangleRounded((Rectangle){ r.x + 4, r.y + 3, r.width - 8, r.height * 0.3f },
                         1.0f, 8, Fade(WHITE, emCima ? 0.25f : 0.3f));
    DrawRectangleRoundedLinesEx(r, 0.5f, 10, 2.0f, emCima ? COR_CLARA : COR_MARINHO);

    // icone: cadeado simples
    float ix = r.x + 34, iy = r.y + 14;
    DrawRing((Vector2){ ix + 10, iy + 10 }, 5, 8, 180, 360, 12, WHITE);
    DrawRectangleRounded((Rectangle){ ix, iy + 10, 20, 16 }, 0.3f, 4, WHITE);
    DrawCircle((int)ix + 10, (int)iy + 17, 2, emCima ? COR_ROSA : COR_AZUL);

    const char *texto = "Tentar a senha novamente";
    DrawText(texto, (int)r.x + 76 + 1, (int)r.y + 19, 20, Fade(COR_MARINHO, 0.6f));
    DrawText(texto, (int)r.x + 76, (int)r.y + 18, 20, WHITE);
}

bool Senha_Concluida(void)
{
    return estado == SENHA_FIM;
}

bool Senha_PrecisaVoltarAoQuarto(void)
{
    return estado == SENHA_SAIU;
}
