// teste_senha.c
// Programa de teste do minijogo da senha, separado do jogo.
// Mostra a barra de tokens no canto. No jogo, quem desenha a barra e o nucleo.
// O "quarto" aqui e so uma tela provisoria, para testar a volta depois de 5 erros.
//
// Compilar (Windows, w64devkit):
//   gcc teste_senha.c senha.c barra_tokens.c tokens_provisorio.c -o teste_senha.exe -lraylib -lopengl32 -lgdi32 -lwinmm
// Compilar (macOS):
//   cc teste_senha.c senha.c barra_tokens.c tokens_provisorio.c -o teste_senha $(pkg-config --cflags --libs raylib)
//
// Clique nos fragmentos (ou digite K, 7, Y, 2), BACKSPACE devolve, ENTER confirma. No pop-up: clique ou 1 / 2.
// No quarto provisorio: o botao "Tentar a senha novamente" volta ao PC. Depois de acertar: R reinicia.

#include "raylib.h"
#include "senha.h"
#include "tokens.h"
#include "barra_tokens.h"

int main(void)
{
    InitWindow(1280, 720, "re:7 - teste da senha (Ato 1)");
    SetTargetFPS(60);

    bool noQuarto = false;

    Tokens_Reiniciar();
    BarraTokens_Reiniciar();
    Senha_ComecarJogo();

    while (!WindowShouldClose()) {
        if (noQuarto) {
            if (Senha_BotaoTentarDeNovoClicado()) {
                noQuarto = false;
                Senha_Iniciar();          // senta no PC de novo: erros voltam a 0
            }
        } else {
            Senha_Atualizar();
            if (Senha_PrecisaVoltarAoQuarto()) noQuarto = true;
        }
        BarraTokens_Atualizar();

        if (Senha_Concluida() && IsKeyPressed(KEY_R)) {
            Tokens_Reiniciar();
            BarraTokens_Reiniciar();
            Senha_ComecarJogo();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        if (noQuarto) {
            ClearBackground((Color){ 60, 45, 70, 255 });
            DrawText("QUARTO (tela provisoria)", 40, 40, 30, RAYWHITE);
            DrawText("Aqui ficam os hotspots: diario (07) e calendario de 2007.", 40, 90, 20, RAYWHITE);
            Senha_DesenharBotaoTentarDeNovo();
        } else {
            Senha_Desenhar();
        }
        BarraTokens_Desenhar(990, 20);
        if (Senha_Concluida()) {
            DrawText("Teste concluido. R reinicia.", 20, 20, 20, RAYWHITE);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
