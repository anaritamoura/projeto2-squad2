# Ato 1: minijogo da senha

Minijogo da senha do Ato 1, barra de tokens e programa de teste.

## Arquivos

- `senha.c` / `senha.h`: minijogo da senha
- `barra_tokens.c` / `barra_tokens.h`: desenho da barra de tokens
- `tokens.h`: funções dos tokens (interface do núcleo)
- `tokens_provisorio.c`: versão provisória dos tokens, só para testar
- `teste_senha.c`: programa de teste do minijogo

## Compilar no Windows

Pelo terminal do w64devkit, dentro desta pasta:

```
gcc teste_senha.c senha.c barra_tokens.c tokens_provisorio.c -o teste_senha.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

Para rodar:

```
teste_senha.exe
```

## Compilar no macOS

Precisa da raylib instalada pelo Homebrew (`brew install raylib pkg-config`). Dentro desta pasta:

```
cc teste_senha.c senha.c barra_tokens.c tokens_provisorio.c -o teste_senha $(pkg-config --cflags --libs raylib)
```

Para rodar:

```
./teste_senha
```

## Teclas do teste

- Números: digitar a senha
- BACKSPACE: apagar
- ENTER: confirmar
- No pop-up da IA: clique ou teclas 1 / 2
- Depois de acertar: R reinicia
