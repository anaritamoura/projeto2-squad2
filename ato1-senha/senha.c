// senha.c
// Minijogo da senha do PC (Ato 1): logica proposicional com fragmentos.
//
// Regras (roteiro, Ato 1, Cena 2):
// - A senha e Y2K7. A jogadora monta a senha clicando em quatro fragmentos
//   (K, 7, Y, 2), que aparecem fora de ordem. Tambem pode digitar K, 7, Y ou 2.
// - Na tela, desde o inicio: os fragmentos, as proposicoes p, q, r, s, as
//   quatro expressoes com o resultado (verdadeiro/falso) e a dica da senha,
//   que e uma tautologia (s v ¬s) e nao ajuda em nada.
// - BACKSPACE devolve o ultimo fragmento. ENTER (ou a seta verde) confirma.
// - No 3o erro de cada rodada, a IA oferece ajuda num pop-up de MSN:
//     1. Fazer o primeiro passo -> Tokens_Gastar()    (-1)
//     2. Tentar de novo sozinha -> Tokens_Recuperar() (+1, max. 3)
// - Se a jogadora aceitar a ajuda UMA vez, o pop-up nunca mais aparece.
//   Assim a senha gasta no maximo 1 token no jogo inteiro.
// - No 5o erro, a LIA diz uma fala e volta para o quarto, sem custo.
//   No quarto aparece o botao "Tentar a senha novamente"; ao clicar,
//   os erros recomecam do zero.
//
// Os simbolos usam a fonte padrao da raylib: ¬ aparece; "e" vira ^,
// "ou" vira v e "se... entao" vira ->.

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
#define COR_DICA     (Color){ 255, 251, 224, 255 }
#define COR_DICA_TXT (Color){  61,  58,  30, 255 }

// ---------- conteudo do desafio (US19) ----------
typedef struct {
    char letra;            // o caractere que entra na senha
    const char *nome;      // "Fragmento A"
    const char *pista;     // de onde vem o caractere
} Fragmento;

static const Fragmento FRAGMENTOS[SENHA_TAMANHO] = {
    { 'K', "Fragmento A", "inicial de Kilo" },
    { '7', "Fragmento B", "último algarismo de 2007" },
    { 'Y', "Fragmento C", "inicial de Year" },
    { '2', "Fragmento D", "o 2 de 2007" },
};

static const char *PROPOSICOES[] = {
    "p   Y aparece antes de K",
    "q   2 aparece antes de 7",
    "r   K aparece logo depois de 2",
    "s   7 ocupa a última posição",
};

static const char *EXPRESSOES[]  = { "p ^ q", "¬q v r", "r ^ ¬s", "¬p ^ s" };
static const bool  RESULTADOS[]  = { true,    true,     false,    false    };

// ---------- estado ----------
typedef enum {
    SENHA_MONTANDO,
    SENHA_POPUP_IA,
    SENHA_ACERTOU,      // mostra a senha certa por um instante
    SENHA_FIM,
    SENHA_FALA_SAIDA,   // fala da LIA antes de voltar para o quarto
    SENHA_SAIU
} EstadoSenha;

static EstadoSenha estado;
static int  campos[SENHA_TAMANHO];   // indice do fragmento em cada campo (-1 = vazio)
static int  quantidade;              // quantos campos estao preenchidos
static int  erros;                   // erros desde que a LIA sentou no PC
static bool ajudaAceita;             // vale para o jogo inteiro
static bool mostrarPrimeiroPasso;    // fala da IA depois de aceitar a ajuda

static float tempoAvisoErro;         // segundos restantes do aviso "Senha incorreta"
static float tempoAcerto;            // pausa depois de acertar

// ---------- posicoes (tela 1280 x 720) ----------
static const Rectangle PAINEL_LIA = { 440, 140, 400, 90 };
static const Rectangle BOTAO_IR   = { 774, 172, 46, 46 };
static const Rectangle POPUP      = { 330, 210, 620, 250 };
static const Rectangle BOTAO_1    = { 395, 345, 490, 40 };
static const Rectangle BOTAO_2    = { 395, 395, 490, 40 };
static const Rectangle BOTAO_TENTAR_DE_NOVO = { 880, 630, 370, 56 };  // canto do quarto

#define CAMPO_X0     550
#define CAMPO_Y      172
#define CAMPO_LADO   46
#define CAMPO_ESPACO 10

#define FRAG_Y       300
#define FRAG_LARG    170
#define FRAG_ALT     88
#define FRAG_ESPACO  16

// ---------- funcoes auxiliares ----------
static void TextoCentralizado(const char *texto, float centroX, float y, int tamanho, Color cor)
{
    int largura = MeasureText(texto, tamanho);
    DrawText(texto, (int)(centroX - largura / 2.0f), (int)y, tamanho, cor);
}

static Rectangle RetanguloFragmento(int i)
{
    float total = SENHA_TAMANHO * FRAG_LARG + (SENHA_TAMANHO - 1) * FRAG_ESPACO;
    float x0 = (1280 - total) / 2.0f;
    return (Rectangle){ x0 + i * (FRAG_LARG + FRAG_ESPACO), FRAG_Y, FRAG_LARG, FRAG_ALT };
}

static Rectangle RetanguloCampo(int i)
{
    return (Rectangle){ CAMPO_X0 + i * (CAMPO_LADO + CAMPO_ESPACO), CAMPO_Y, CAMPO_LADO, CAMPO_LADO };
}

static bool FragmentoUsado(int f)
{
    for (int i = 0; i < quantidade; i++) {
        if (campos[i] == f) return true;
    }
    return false;
}

static void LimparCampos(void)
{
    for (int i = 0; i < SENHA_TAMANHO; i++) campos[i] = -1;
    quantidade = 0;
}

static void ColocarFragmento(int f)
{
    if (quantidade < SENHA_TAMANHO && !FragmentoUsado(f)) {
        campos[quantidade++] = f;
    }
}

static void DevolverUltimo(void)
{
    if (quantidade > 0) campos[--quantidade] = -1;
}

static void ConferirTentativa(void)
{
    char tentativa[SENHA_TAMANHO + 1];
    for (int i = 0; i < SENHA_TAMANHO; i++) tentativa[i] = FRAGMENTOS[campos[i]].letra;
    tentativa[SENHA_TAMANHO] = '\0';

    if (strcmp(tentativa, SENHA_CORRETA) == 0) {
        estado = SENHA_ACERTOU;
        tempoAcerto = 1.0f;
        return;
    }

    erros++;
    LimparCampos();               // os fragmentos voltam para a mesa
    tempoAvisoErro = 1.5f;

    if (erros >= SENHA_LIMITE_ERROS) {
        estado = SENHA_FALA_SAIDA;
    } else if (!ajudaAceita && erros == SENHA_ERRO_AJUDA) {
        estado = SENHA_POPUP_IA;  // 3o erro da rodada
    }
}

static void EscolherPrimeiroPasso(void)
{
    Tokens_Gastar();
    ajudaAceita = true;
    mostrarPrimeiroPasso = true;
    estado = SENHA_MONTANDO;
}

static void EscolherTentarSozinha(void)
{
    Tokens_Recuperar();
    estado = SENHA_MONTANDO;
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
    mostrarPrimeiroPasso = false;
    Senha_Iniciar();
}

void Senha_Iniciar(void)
{
    estado = SENHA_MONTANDO;
    LimparCampos();
    erros = 0;
    tempoAvisoErro = 0.0f;
    tempoAcerto = 0.0f;
}

void Senha_Atualizar(void)
{
    float dt = GetFrameTime();
    if (tempoAvisoErro > 0.0f) tempoAvisoErro -= dt;

    switch (estado) {
    case SENHA_MONTANDO: {
        // teclado: K, 7, Y ou 2
        int tecla = GetCharPressed();
        while (tecla > 0) {
            for (int f = 0; f < SENHA_TAMANHO; f++) {
                char c = FRAGMENTOS[f].letra;
                if (tecla == c || (c >= 'A' && c <= 'Z' && tecla == c + 32)) ColocarFragmento(f);
            }
            tecla = GetCharPressed();
        }

        // mouse: clique num fragmento
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 m = GetMousePosition();
            for (int f = 0; f < SENHA_TAMANHO; f++) {
                if (CheckCollisionPointRec(m, RetanguloFragmento(f))) ColocarFragmento(f);
            }
        }

        if (IsKeyPressed(KEY_BACKSPACE)) DevolverUltimo();

        bool confirmar = IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) ||
                         Botao(BOTAO_IR, "", false);
        if (confirmar && quantidade == SENHA_TAMANHO) ConferirTentativa();
    } break;

    case SENHA_POPUP_IA:
        if (Botao(BOTAO_1, "", false) || IsKeyPressed(KEY_ONE)) {
            EscolherPrimeiroPasso();
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

static void DesenharFundo(void)
{
    // tela de boas-vindas do PC: faixas escuras em cima e embaixo
    DrawRectangleGradientV(0, 96, 1280, 544, (Color){ 120, 160, 210, 255 }, (Color){ 42, 90, 168, 255 });
    DrawRectangle(0, 0, 1280, 96, COR_MARINHO);
    DrawRectangle(0, 640, 1280, 80, COR_MARINHO);
    DrawRectangleGradientH(0, 96, 640, 3, Fade(COR_CLARA, 0.2f), COR_ROSA);
    DrawRectangleGradientH(640, 96, 640, 3, COR_ROSA, Fade(COR_CLARA, 0.2f));
    DrawRectangleGradientH(0, 637, 1280, 3, COR_AZUL, COR_CLARA);

    DrawText("PC da", 40, 34, 26, COR_CLARA);
    DrawText("LIA", 40 + MeasureText("PC da ", 26), 34, 26, COR_ROSA);
}

static void DesenharLoginESenha(bool acertou)
{
    TextoCentralizado("Para começar, descubra a senha", 640, 106, 26, WHITE);

    // usuaria LIA com os 4 campos
    DrawRectangleRounded(PAINEL_LIA, 0.15f, 8, Fade(COR_MARINHO, 0.6f));
    Rectangle foto = { PAINEL_LIA.x + 18, PAINEL_LIA.y + 15, 60, 60 };
    DrawRectangleGradientEx(foto, COR_ROSA, COR_AZUL, COR_AZUL, COR_ROSA);
    DrawRectangleLinesEx(foto, 3.0f, COR_CLARA);
    TextoCentralizado("L", foto.x + 30, foto.y + 16, 30, WHITE);
    DrawText("LIA", CAMPO_X0, (int)PAINEL_LIA.y + 6, 24, WHITE);

    for (int i = 0; i < SENHA_TAMANHO; i++) {
        Rectangle c = RetanguloCampo(i);
        Color borda = acertou ? COR_VERDE
                    : (tempoAvisoErro > 0.0f) ? COR_VERMELHO
                    : (i == quantidade ? COR_ROSA : COR_AZUL_MED);
        DrawRectangleRec(c, WHITE);
        DrawRectangleLinesEx(c, 3.0f, borda);

        char letra[2] = { 0 };
        if (acertou) letra[0] = SENHA_CORRETA[i];
        else if (campos[i] >= 0) letra[0] = FRAGMENTOS[campos[i]].letra;
        if (letra[0]) TextoCentralizado(letra, c.x + CAMPO_LADO / 2.0f, c.y + 9, 30, COR_MARINHO);
    }

    // seta verde (confirmar)
    bool pode = (quantidade == SENHA_TAMANHO) && estado == SENHA_MONTANDO;
    bool emCima = CheckCollisionPointRec(GetMousePosition(), BOTAO_IR);
    DrawRectangleRounded(BOTAO_IR, 0.2f, 6, pode ? (emCima ? COR_AZUL : COR_VERDE) : COR_AZUL_MED);
    DrawRectangleRoundedLinesEx(BOTAO_IR, 0.2f, 6, 2.0f, COR_CLARA);
    DrawTriangle((Vector2){ BOTAO_IR.x + 16, BOTAO_IR.y + 12 }, (Vector2){ BOTAO_IR.x + 16, BOTAO_IR.y + 34 },
                 (Vector2){ BOTAO_IR.x + 34, BOTAO_IR.y + 23 }, WHITE);

    // dica da senha (tautologia)
    const char *dica = "Dica da senha: A senha termina com 7 ou não termina.   s v ¬s";
    int larg = MeasureText(dica, 16) + 28;
    Rectangle caixa = { 640 - larg / 2.0f, 240, (float)larg, 28 };
    DrawRectangleRounded(caixa, 0.4f, 8, COR_DICA);
    DrawRectangleRoundedLinesEx(caixa, 0.4f, 8, 1.0f, (Color){ 201, 181, 74, 255 });
    DrawText(dica, (int)caixa.x + 14, (int)caixa.y + 6, 16, COR_DICA_TXT);

    // contador / avisos
    if (acertou) {
        TextoCentralizado("Senha correta!", 640, 276, 18, COR_VERDE);
    } else if (tempoAvisoErro > 0.0f) {
        TextoCentralizado(TextFormat("Senha incorreta. Tentativas erradas: %d de %d", erros, SENHA_LIMITE_ERROS),
                          640, 276, 18, COR_VERMELHO);
    } else if (erros > 0) {
        TextoCentralizado(TextFormat("Tentativas erradas: %d de %d", erros, SENHA_LIMITE_ERROS),
                          640, 276, 18, (Color){ 255, 208, 220, 255 });
    }
}

static void DesenharFragmentos(void)
{
    Vector2 m = GetMousePosition();
    for (int f = 0; f < SENHA_TAMANHO; f++) {
        Rectangle r = RetanguloFragmento(f);
        bool usado = FragmentoUsado(f);
        bool emCima = !usado && estado == SENHA_MONTANDO && CheckCollisionPointRec(m, r);
        float a = usado ? 0.35f : 1.0f;

        DrawRectangleRounded((Rectangle){ r.x + 3, r.y + 4, r.width, r.height }, 0.15f, 8, Fade(BLACK, 0.2f * a));
        DrawRectangleRounded(r, 0.15f, 8, Fade(emCima ? WHITE : COR_CLARA, a));
        DrawRectangleRoundedLinesEx(r, 0.15f, 8, 2.0f, Fade(emCima ? COR_ROSA : COR_AZUL, a));

        float cx = r.x + r.width / 2.0f;
        TextoCentralizado(FRAGMENTOS[f].nome, cx, r.y + 8, 14, Fade(COR_ROSA, a));
        char letra[2] = { FRAGMENTOS[f].letra, '\0' };
        TextoCentralizado(letra, cx, r.y + 26, 36, Fade(COR_MARINHO, a));
        TextoCentralizado(FRAGMENTOS[f].pista, cx, r.y + 66, 12, Fade((Color){ 74, 90, 128, 255 }, a));
    }
}

static void DesenharLogica(void)
{
    Rectangle esq = { 140, 402, 490, 150 };
    Rectangle dir = { 650, 402, 490, 150 };

    DrawRectangleRounded(esq, 0.08f, 8, Fade(COR_MARINHO, 0.5f));
    DrawRectangleRoundedLinesEx(esq, 0.08f, 8, 1.0f, COR_AZUL_MED);
    DrawText("PROPOSIÇÕES", (int)esq.x + 16, (int)esq.y + 10, 14, COR_AZUL_MED);
    for (int i = 0; i < 4; i++) {
        DrawText(PROPOSICOES[i], (int)esq.x + 16, (int)esq.y + 34 + i * 27, 18, COR_CLARA);
    }

    DrawRectangleRounded(dir, 0.08f, 8, Fade(COR_MARINHO, 0.5f));
    DrawRectangleRoundedLinesEx(dir, 0.08f, 8, 1.0f, COR_AZUL_MED);
    DrawText("EXPRESSÕES", (int)dir.x + 16, (int)dir.y + 10, 14, COR_AZUL_MED);
    for (int i = 0; i < 4; i++) {
        int y = (int)dir.y + 34 + i * 27;
        DrawText(EXPRESSOES[i], (int)dir.x + 16, y, 20, (Color){ 255, 214, 251, 255 });
        const char *res = RESULTADOS[i] ? "Verdadeiro" : "Falso";
        Color cor = RESULTADOS[i] ? (Color){ 126, 240, 138, 255 } : (Color){ 255, 157, 181, 255 };
        DrawText(res, (int)(dir.x + dir.width - 16 - MeasureText(res, 18)), y + 1, 18, cor);
    }

    // primeiro passo da IA, depois que a ajuda foi aceita
    if (mostrarPrimeiroPasso) {
        Rectangle r = { 140, 562, 1000, 30 };
        DrawRectangleRounded(r, 0.4f, 8, Fade(COR_CLARA, 0.9f));
        DrawCircle((int)r.x + 16, (int)r.y + 15, 6, COR_VERDE);
        DrawText("IA: p ^ q é verdadeira, então p e q também são: Y vem antes de K, e 2 vem antes de 7. O resto é com você.",
                 (int)r.x + 30, (int)r.y + 7, 16, COR_MARINHO);
    }
}

void Senha_Desenhar(void)
{
    bool acertou = (estado == SENHA_ACERTOU || estado == SENHA_FIM);

    DesenharFundo();
    DesenharLoginESenha(acertou);
    DesenharFragmentos();
    DesenharLogica();

    TextoCentralizado("Clique nos fragmentos (ou digite K, 7, Y, 2). ENTER confirma. BACKSPACE devolve.",
                      640, 670, 18, COR_CLARA);

    // Pop-up de MSN da IA (3o erro)
    if (estado == SENHA_POPUP_IA) {
        DrawRectangle(0, 0, 1280, 720, Fade(BLACK, 0.4f));

        DrawRectangleRec(POPUP, COR_CLARA);
        DrawRectangleLinesEx(POPUP, 2.0f, COR_AZUL);
        DrawRectangleGradientH((int)POPUP.x, (int)POPUP.y, (int)POPUP.width, 34, COR_AZUL, COR_MARINHO);
        DrawCircle((int)POPUP.x + 20, (int)POPUP.y + 17, 7, COR_VERDE);
        DrawText("IA (online)", (int)POPUP.x + 35, (int)POPUP.y + 8, 20, COR_CLARA);

        DrawText("IA diz:", (int)POPUP.x + 25, (int)POPUP.y + 55, 18, COR_AZUL);
        DrawText("Três tentativas erradas. Posso fazer o primeiro",
                 (int)POPUP.x + 25, (int)POPUP.y + 80, 20, COR_MARINHO);
        DrawText("passo da dedução com você ou você tenta de novo.",
                 (int)POPUP.x + 25, (int)POPUP.y + 105, 20, COR_MARINHO);

        Botao(BOTAO_1, "1. Fazer o primeiro passo (-1 token)", true);
        Botao(BOTAO_2, "2. Tentar de novo sozinha", true);
    }

    // Fala da LIA no 5o erro, numa caixa de dialogo
    if (estado == SENHA_FALA_SAIDA) {
        DrawRectangle(0, 0, 1280, 720, Fade(BLACK, 0.4f));
        Rectangle caixa = { 40, 540, 1200, 150 };
        DrawRectangleRounded(caixa, 0.15f, 8, Fade(COR_CLARA, 0.95f));
        DrawRectangleRoundedLinesEx(caixa, 0.15f, 8, 3.0f, COR_AZUL);
        DrawText("LIA", (int)caixa.x + 30, (int)caixa.y + 20, 24, COR_ROSA);
        DrawText("Calma. Vou respirar um pouco e tentar de novo.",
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
