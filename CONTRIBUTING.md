# Como contribuir com o Re:7

Este guia orienta a configuração do ambiente, a compilação do jogo e o envio de contribuições em C com Raylib.

## 1. Repositórios e organização

- [projeto2-squad2](https://github.com/anaritamoura/projeto2-squad2): repositório principal da entrega, com documentação e evidências do projeto.
- [RE7](https://github.com/romaiziul/RE7): contém a estrutura do jogo usada nas instruções abaixo, em `re7-REL1/`, incluindo `build.ps1`, `src/`, `assets/` e `testes/`.
- [Trello](https://trello.com/b/t0u8Iplf): histórias de usuário, critérios de confirmação, tarefas e evidências dos testes.

Faça a contribuição no repositório que contém os arquivos envolvidos. Os comandos de compilação abaixo se referem a `RE7/re7-REL1`; não devem ser executados na raiz de `projeto2-squad2`, onde esse script não está presente na estrutura consultada. Não é necessário duplicar alterações no repositório antigo. Mantenha no README principal os links para o código e a Release utilizada na entrega.

## 2. Configurar o ambiente no Windows

São necessários Git, PowerShell, GCC/MinGW-w64 e Raylib compatível com o compilador. O VS Code é opcional: o jogo é compilado pelo terminal.

1. Instale o [Git para Windows](https://git-scm.com/downloads/win).
2. Obtenha o pacote de desenvolvimento para Windows indicado pela [Raylib](https://www.raylib.com/). O [instalador oficial](https://raysan5.itch.io/raylib) inclui um ambiente com compilador. Consulte também o [guia para Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows).
3. Configure a instalação para atender aos caminhos utilizados pelo `build.ps1`:

| Componente | Caminho esperado |
| --- | --- |
| GCC | `C:\raylib\w64devkit\bin\gcc.exe` |
| Cabeçalho da Raylib | `C:\raylib\raylib\src\raylib.h` |
| Biblioteca da Raylib | `C:\raylib\raylib\src\libraylib.a` |

Verifique no PowerShell:

```powershell
git --version
& 'C:\raylib\w64devkit\bin\gcc.exe' --version
Test-Path 'C:\raylib\raylib\src\raylib.h'
Test-Path 'C:\raylib\raylib\src\libraylib.a'
```

Os dois últimos comandos devem retornar `True`. A biblioteca deve ter a mesma arquitetura e ser compatível com o GCC utilizado. Caso tenha instalado em outro local, ajuste o caminho do compilador e as opções `-I` e `-L` no `build.ps1`. Apenas adicionar o GCC ao PATH não altera os caminhos fixos desse script.

## 3. Obter o código

Para trabalhar no jogo:

```powershell
git clone https://github.com/romaiziul/RE7.git
cd RE7
```

Para trabalhar na documentação do repositório principal, use uma cópia separada:

```powershell
git clone https://github.com/anaritamoura/projeto2-squad2.git
cd projeto2-squad2
```

Execute cada sequência a partir da pasta em que deseja guardar o respectivo repositório. Antes de editar, confira `git remote -v` para confirmar o destino das contribuições.

## 4. Compilar e executar o jogo

Na raiz da cópia de `RE7`, entre na pasta do jogo:

```powershell
cd re7-REL1
.\build.ps1
```

Confira se o GCC terminou sem erros. Execute o jogo somente após uma compilação bem-sucedida, para não testar um executável antigo:

```powershell
.\re7.exe
```

Mantenha `assets/` junto ao executável e execute a partir de `re7-REL1`, pois os recursos são carregados por caminhos relativos.

Se o PowerShell bloquear o script, revise seu conteúdo e permita a execução somente nesta sessão:

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy RemoteSigned
.\build.ps1
```

O script reúne os arquivos `.c` de `src/`, incluindo subpastas, e exclui `src/escolha.c`, que possui uma função `main` independente. Ele não executa automaticamente os testes de `testes/`.

### Modo desenvolvedor

```powershell
.\build.ps1 -Dev
.\re7_dev.exe
```

Esse modo disponibiliza o painel de testes com F10 e usa `save_dev.dat`. O build normal gera `re7.exe` e não inclui o painel. Para a Release final, utilize o build normal.

## 5. Fluxo de branch e pull request

1. Escolha uma história ou issue e registre a dupla responsável no Trello.
2. Com a árvore de trabalho limpa, atualize a `main` e crie uma branch no repositório correspondente:

```powershell
git switch main
git pull --ff-only origin main
git switch -c feat/us24-selecao-palavras
```

Use nomes como `feat/us24-selecao-palavras`, `fix/ato3-cronometro` ou `docs/contributing`.

3. Implemente a alteração e faça commits por mudança coerente. Antes de registrar, revise `git diff` e `git status`.
4. Adicione somente os arquivos da alteração e faça o commit. Exemplo para este documento, a partir da raiz do repositório:

```powershell
git add CONTRIBUTING.md
git commit -m "docs: adicionar guia de contribuicao"
```

5. Envie a branch. Substitua o nome abaixo pelo nome da branch criada:

```powershell
git push -u origin feat/us24-selecao-palavras
```

6. Abra um pull request com destino à `main` do repositório correspondente. Informe a US/issue, o que mudou, a dupla responsável, como testar e os links das evidências.
7. Solicite revisão de outro integrante, resolva os comentários e integre após a aprovação e a verificação dos testes. Atualize o card do Trello com o link do PR.

Se você não tiver permissão de escrita, faça um fork, trabalhe nele e abra o PR para o repositório de origem. Não envie alterações diretamente à `main` como fluxo habitual da equipe.

## 6. Padrão de commits

Utilize o formato `tipo: descrição objetiva`, acrescentando a US quando houver relação direta.

| Tipo | Uso | Exemplo |
| --- | --- | --- |
| `feat` | Funcionalidade | `feat: adicionar selecao de palavras da US24` |
| `fix` | Correção | `fix: corrigir contagem de erros do Ato 3` |
| `test` | Testes | `test: validar desfechos do Ato 3` |
| `docs` | Documentação | `docs: atualizar relato de pares da Sprint 03` |
| `refactor` | Organização sem mudar o comportamento | `refactor: organizar validacao da digitacao` |
| `chore` | Configuração e manutenção | `chore: ajustar configuracao de compilacao` |

Faça commits frequentes à medida que concluir mudanças reais e revisáveis. Evite mensagens genéricas como “atualização” e commits artificiais apenas para aumentar a contagem.

Configure sua identidade de autoria no repositório, substituindo os exemplos por seus dados:

```powershell
git config user.name "Seu nome"
git config user.email "Seu email associado ao GitHub"
```

## 7. Testes e evidências

Antes de abrir o PR, compile o jogo e verifique os critérios de confirmação da US. Teste o funcionamento esperado e as situações de erro relevantes.

Para executar o teste de lógica do Ato 3 documentado na estrutura consultada, abra o PowerShell em `re7-REL1`:

```powershell
& 'C:\raylib\w64devkit\bin\gcc.exe' testes/teste_ato3.c src/atos/ato3/ato3_logica.c src/systems/tokens.c -Isrc/core -Isrc/systems -Isrc/atos/ato3 -o teste_ato3.exe
if ($LASTEXITCODE -eq 0) { .\teste_ato3.exe }
```

Esse teste cobre regras de lógica; não substitui os testes da interface, áudio e digitação. Se os módulos ou dependências mudarem, atualize também o comando documentado.

- Senha: verificar a combinação correta, combinações incorretas, contador de tentativas e reinício conforme os critérios do card.
- Ato 3: verificar os modos com e sem ajuda, seleção, digitação, tempo esgotado e resultados com zero a três rodadas incorretas.
- Fluxos afetados: verificar a entrada e saída do minijogo e a continuidade da história.

Grave o screencast dos testes, informe o commit ou versão testada e anexe a evidência ao card da US. Marque apenas os critérios efetivamente validados.

Ao encontrar um defeito, abra uma issue contendo:

- Título e US relacionada.
- Versão ou commit testado e ambiente utilizado.
- Passos para reproduzir.
- Resultado esperado e resultado observado.
- Print ou vídeo e impacto do problema.

Relacione a correção à issue e mantenha no README as evidências exigidas pela entrega, incluindo o print das issues da sprint.

## 8. Trabalho em dupla e cuidados com os arquivos

Atualize o relato de pares com data, dupla, US, papéis desempenhados, atividade realizada, resultado e links dos commits ou PRs. Registre a participação real de cada integrante; a autoria também fica documentada no histórico de commits.

Siga a organização dos módulos existentes e mantenha os recursos em `assets/`. Não inclua executáveis gerados, saves pessoais, arquivos temporários ou credenciais nos commits. Distribua o executável e os recursos necessários como anexos da Release final.

Antes de concluir a contribuição, confira:

- [ ] A alteração compila e atende aos critérios da US.
- [ ] Os testes relevantes foram executados e suas evidências foram anexadas.
- [ ] O PR identifica a US, a dupla e as mudanças realizadas.
- [ ] O Trello e o relato de pares estão atualizados.
- [ ] A documentação acompanha mudanças de ambiente ou compilação.

