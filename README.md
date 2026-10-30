# 🎮 PROJETO INTEGRADOR - TEAM 2

<p align="center">
  <img src="assets/logo_smalld.png" alt="Logo Re:7" width="250">
</p>

<p align="center">
  <strong>2007 ligou, você vai atender?</strong>
</p>

---

## 📑 Sumário

- [Sobre o Projeto](#sobre)
- [Gestão do Projeto](#gestao)
- [Épicos e Histórias de Usuário](#epicos)
- [Demonstração da Solução](#demonstracao)
  - [Protótipo Lo-Fi](#prototipo)
  - [Núcleo do Jogo em C (PIF)](#entrega-pif)
- [Colaboração e evidências](#colaboracao)
- [Equipe](#equipe)
- [Organização do Repositório](#organizacao)
- [Links Importantes](#links)

---

<a id="sobre"></a>
## 📖 Sobre o Projeto

**Re:7** é um projeto desenvolvido por estudantes do segundo período de **ADS**, da **CESAR School**, como parte de um Projeto Integrador que visa utilizar conhecimentos de todas as cadeiras simultaneamente.

O projeto consiste no desenvolvimento de uma visual novel interativa em linguagem C, na qual o jogador acompanha uma personagem adulta que, com a intervenção de uma Inteligência Artificial, é transportada de volta para 2007 e precisa lidar novamente com situações e escolhas de sua adolescência.

A proposta combina narrativa interativa, tomada de decisões e elementos visuais inspirados na estética digital dos anos 2000, buscando dialogar tanto com pessoas que vivenciaram esse período quanto com uma geração mais jovem familiarizada com o retorno da estética Y2K.

Nosso objetivo é desenvolver uma experiência narrativa interativa que explore, de forma lúdica, a relação entre tecnologia, escolhas e diferentes perspectivas geracionais, aplicando os conhecimentos de programação e desenvolvimento de software trabalhados ao longo do Projeto Integrador.

---

## 🎯 Objetivo

Desenvolver um jogo educativo de escolhas e consequências voltado ao letramento crítico em Inteligência Artificial.

### Objetivos específicos

* Desenvolver um jogo educativo sobre letramento em IA, baseado em escolhas e consequências.
* Entregar um jogo funcional e validá-lo por meio de testes com usuários.
* Criar um MVP compatível com o conhecimento da equipe, o prazo e as tecnologias disponíveis.
* Promover a compreensão crítica sobre o uso, funcionamento, limites e riscos da IA.
* Concluir e validar o jogo até o final do semestre, em aproximadamente 4 meses.

---

## 🎮 Sobre o Jogo

**Gênero:** Visual Novel / RPG de escolhas

**Tema:** Letramento em Inteligência Artificial, uso crítico da tecnologia e tomada de decisões.

**Ambientação:** 2007, em uma representação inspirada na cultura, tecnologia e estética digital dos anos 2000.

**Público-alvo:** Adolescentes e jovens adultos, incluindo tanto usuários familiarizados com ferramentas de IA quanto pessoas com pouco conhecimento sobre seu funcionamento, limites e riscos.

**Duração estimada:** Aproximadamente 6 minutos para o MVP.

### 📜 Sinopse

Após uma interação inesperada com uma Inteligência Artificial, uma mulher adulta é transportada de volta para 2007, período em que ainda era adolescente.

Para encontrar uma forma de retornar ao presente, ela deverá enfrentar situações e desafios com a ajuda de uma IA que parece saber mais do que deveria.

Ao longo da história, o jogador deverá tomar decisões, solucionar desafios e interagir com diferentes recursos de Inteligência Artificial. Suas escolhas permitem explorar, de forma lúdica, possibilidades, limitações e riscos relacionados ao uso dessas tecnologias.

---

## ✨ Principais Funcionalidades

O projeto prevê as seguintes funcionalidades:

* 💬 **Sistema de diálogos:** progressão da narrativa por meio de diálogos entre personagens e interação com a IA.

* 🔀 **Sistema de escolhas e consequências:** decisões tomadas pelo jogador podem alterar diálogos, acontecimentos e o desenvolvimento da narrativa.

* 🧩 **Minijogos e desafios interativos:** atividades integradas à história que apresentam diferentes situações relacionadas ao uso e funcionamento da Inteligência Artificial.

* 🤖 **Interações voltadas ao letramento em IA:** situações que abordam possibilidades, limitações e riscos da tecnologia dentro do contexto da narrativa.

* 🖥️ **Ambientação inspirada em 2007:** cenários e interfaces baseados na estética, cultura e tecnologias digitais dos anos 2000.

* 📊 **Feedback das decisões:** apresentação das consequências das escolhas e do desempenho nos desafios, incentivando a reflexão sobre as decisões tomadas.

---

## ⚙️ Tecnologias e Ferramentas

Para o desenvolvimento e gerenciamento do projeto, utilizamos:

* **C** — linguagem de programação utilizada para o desenvolvimento da lógica e das funcionalidades do jogo.
* **Raylib** — biblioteca utilizada para o desenvolvimento da interface gráfica, gerenciamento de imagens, textos, áudio e interações do jogo.
* **Figma** — utilizado para prototipação das interfaces e definição da identidade visual do jogo.
* **GitHub** — utilizado para versionamento, armazenamento e colaboração no código do projeto.
* **Jira** — utilizado para organização das tarefas, gerenciamento do backlog e acompanhamento do desenvolvimento.
* **Trello** — utilizado como ferramenta complementar de acompanhamento das atividades.
* **Canva** — utilizado para criação de elementos gráficos e materiais visuais do projeto.
* **PlantUML** — utilizado para construção e documentação dos diagramas de atividades.

---

<a id="gestao"></a>
# 📊 Gestão do Projeto

## 📋 Project Board

O desenvolvimento do projeto é acompanhado por meio das ferramentas de gerenciamento da equipe, permitindo visualizar as tarefas planejadas, em andamento e concluídas.

🔗 **Jira:** [Acessar Jira](https://csprj-adsr-2p-e2.atlassian.net/jira/software/c/projects/PI2/boards/2/timeline?selectedIssue=PI2-81)

🔗 **Trello:** [Acessar Trello](https://trello.com/b/t0u8Iplf)

**Última atualização:** 21/10/2026

---

<a id="epicos"></a>
# 📚 Épicos e Histórias de Usuário

As histórias de usuário representam as principais funcionalidades e experiências previstas para o **Re:7**.

Para garantir a rastreabilidade entre requisitos, modelagem e prototipação, as histórias possuem acesso aos seus respectivos diagramas de atividades protótipos Lo-Fi e, quando disponíveis, Hi-Fi.

As telas e os fluxos estão organizados por história em [`docs/prototipos`](docs/prototipos/). As pastas US11 a US16 também possuem índices com os links dos protótipos e dos arquivos.

**Status:** ⏳ A fazer • 🔄 Em andamento • ✅ Concluído

## 🎮 EPIC 1 — Menu e Controle de Sessão

| Story | Descrição | Modelagem | Protótipo | Status |
|---|---|:---:|:---:|:---:|
| `US01` | Iniciar novo jogo | [Diagrama](docs/diagramas/US01-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo-FDS-Entrega-2?node-id=0-1&p=f&t=vSc3FPiyOPwirv8F-0&scaling=contain&content-scaling=fixed&starting-point-node-id=11%3A10&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |
| `US14` | Sair ou retornar ao menu | [Diagrama](docs/diagramas/US14-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo---FDS---Entrega-2?node-id=277-39&p=f&t=1PD0gciLPUfIR1Lr-0&scaling=contain&content-scaling=fixed&page-id=0%3A1&starting-point-node-id=277%3A39&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1alnN_eCxFPP-PMcsIs-1eZtsNNcv9-dV/view?usp=sharing) | ✅ |

---

## ⏳ EPIC 2 — Introdução e Viagem no Tempo

| Story | Descrição | Modelagem | Protótipo | Status |
|---|---|:---:|:---:|:---:|
| `US02` | Introdução da protagonista | [Diagrama](docs/diagramas/US02-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo-FDS-Entrega-2?node-id=0-1&p=f&t=vSc3FPiyOPwirv8F-0&scaling=contain&content-scaling=fixed&starting-point-node-id=8%3A6&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |
| `US03` | Transporte para 2007 | [Diagrama](docs/diagramas/US03-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/design/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo---FDS---Entrega-2?node-id=8-8&t=vSc3FPiyOPwirv8F-4) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |

---

## 💬 EPIC 3 — Sistema de Diálogo e Narrativa

| Story | Descrição | Modelagem | Protótipo | Status |
|---|---|:---:|:---:|:---:|
| `US04` | Caixa de diálogo com identificação do falante | [Diagrama](docs/diagramas/US04-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo-FDS-Entrega-2?node-id=0-1&p=f&t=vSc3FPiyOPwirv8F-0&scaling=contain&content-scaling=fixed&starting-point-node-id=9%3A42&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |
| `US05` | Avançar diálogos por comando | [Diagrama](docs/diagramas/US05-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo-FDS-Entrega-2?node-id=0-1&p=f&t=vSc3FPiyOPwirv8F-0&scaling=contain&content-scaling=fixed&starting-point-node-id=9%3A41&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |
| `US06` | Interagir com a IA durante a história | [Diagrama](docs/diagramas/US06-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo-FDS-Entrega-2?node-id=0-1&p=f&t=vSc3FPiyOPwirv8F-0&scaling=contain&content-scaling=fixed&starting-point-node-id=11%3A12&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |

---

## 🔀 EPIC 4 — Escolhas e Consequências Narrativas

| Story | Descrição | Modelagem | Protótipo | Status |
|---|---|:---:|:---:|:---:|
| `US07` | Escolhas alteram diálogos ou acontecimentos | [Diagrama](docs/diagramas/US07-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo-FDS-Entrega-2?node-id=0-1&p=f&t=vSc3FPiyOPwirv8F-0&scaling=contain&content-scaling=fixed&starting-point-node-id=9%3A14&show-proto-sidebar=1) | ⏳ |
| `US15` | Desfecho influenciado pelas escolhas | [Diagrama](docs/diagramas/US15-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo---FDS---Entrega-2?node-id=277-43&p=f&t=1PD0gciLPUfIR1Lr-0&scaling=contain&content-scaling=fixed&page-id=0%3A1&starting-point-node-id=277%3A43&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |
| `US16` | Tela de encerramento | [Diagrama](docs/diagramas/US16-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo---FDS---Entrega-2?node-id=277-47&p=f&t=1PD0gciLPUfIR1Lr-0&scaling=contain&content-scaling=fixed&page-id=0%3A1&starting-point-node-id=277%3A47&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/11SMqcWYKV2sYlrRTrBKdvBf2th4eqQNh/view?usp=sharing) | ✅ |

---

## 💿 EPIC 5 — Exploração de Cenários de 2007

| Story | Descrição | Modelagem | Protótipo | Status |
|---|---|:---:|:---:|:---:|
| `US08` | Explorar o quarto da protagonista | [Diagrama](docs/diagramas/US08-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo-FDS-Entrega-2?node-id=0-1&p=f&t=ozYy6Xxx5UzFB3RU-0&scaling=contain&content-scaling=fixed&starting-point-node-id=9%3A5&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |
| `US09` | Cena no ambiente escolar | [Diagrama](docs/diagramas/US09-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo-FDS-Entrega-2?node-id=0-1&p=f&t=vSc3FPiyOPwirv8F-0&scaling=contain&content-scaling=fixed&starting-point-node-id=9%3A19&show-proto-sidebar=1) | ⏳ |
| `US10` | Tecnologia e cultura dos anos 2000 | [Diagrama](docs/diagramas/US10-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo-FDS-Entrega-2?node-id=0-1&p=f&t=vSc3FPiyOPwirv8F-0&scaling=contain&content-scaling=fixed&starting-point-node-id=9%3A20&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |

---

## 🖱️ EPIC 6 — Interface e Usabilidade

| Story | Descrição | Modelagem | Protótipo | Status |
|---|---|:---:|:---:|:---:|
| `US11` | Feedback visual em opções interativas | [Diagrama](docs/diagramas/US11-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo---FDS---Entrega-2?node-id=277-8&p=f&t=1PD0gciLPUfIR1Lr-0&scaling=contain&content-scaling=fixed&page-id=0%3A1&starting-point-node-id=277%3A8&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1xw17i9gdloGMo8wrCM0RVy36mNwig1Xm/view?usp=sharing) | ✅ |

---

## 🎧 EPIC 7 — Áudio e Imersão

| Story | Descrição | Modelagem | Protótipo | Status |
|---|---|:---:|:---:|:---:|
| `US12` | Música ambiente por cena | [Diagrama](docs/diagramas/US12-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo---FDS---Entrega-2?node-id=277-31&p=f&t=1PD0gciLPUfIR1Lr-0&scaling=contain&content-scaling=fixed&page-id=0%3A1&starting-point-node-id=277%3A31&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1GI2XnuIXv_WsrAibHfJz-sT6ZhdGEibN/view?usp=sharing) | ✅ |
| `US13` | Efeitos sonoros de interações e eventos | [Diagrama](docs/diagramas/US13-diagrama-atividades.png) | [Lo-Fi](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo---FDS---Entrega-2?node-id=277-35&p=f&t=1PD0gciLPUfIR1Lr-0&scaling=contain&content-scaling=fixed&page-id=0%3A1&starting-point-node-id=277%3A35&show-proto-sidebar=1) / [Hi-Fi](https://drive.google.com/file/d/1GI2XnuIXv_WsrAibHfJz-sT6ZhdGEibN/view?usp=sharing) | ✅ |

---

<a id="demonstracao"></a>
# 🎥 Demonstração da Solução

<a id="prototipo"></a>
## 🧩 Protótipo Lo-Fi

Para demonstrar o funcionamento da solução proposta durante a etapa de prototipação, foi produzido um **screencast** apresentando o fluxo principal da experiência.

A demonstração permite compreender como o jogador navega pela solução, como as principais interações acontecem e como os fluxos definidos durante a modelagem são representados no protótipo.

O vídeo conta com áudio e/ou legenda para auxiliar na compreensão da apresentação.

🎬 **Screencast:** [Assistir à demonstração](https://github.com/user-attachments/assets/50ce844c-50ce-4cf1-9a50-a5752a2afe01)

<a id="entrega-pif"></a>
## 🧠 Núcleo do Jogo em C (PIF, Unidade 1)

Visual novel em C com a biblioteca [raylib](https://www.raylib.com/) sobre o uso ético da IA. O jogo é compilado e executado pelo terminal e abre uma janela.

O código desta entrega fica em [`entrega_pif/re7`](entrega_pif/re7).

### Requisitos

- Windows com o compilador **GCC** (MinGW-w64, por exemplo o w64devkit)
- Biblioteca **raylib** instalada para esse compilador

### Como compilar

Abra o terminal na raiz do repositório e entre na pasta do jogo:

```
cd entrega_pif/re7
```

Depois compile:

```
gcc src/*.c -o re7.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

O comando deve terminar sem erros nem avisos.

### Como executar

Ainda dentro de `entrega_pif/re7`:

```
.\re7.exe
```

> O jogo precisa ser aberto a partir da pasta `entrega_pif/re7`, porque lê as imagens em `assets/`.

### Como jogar

| Tecla | Ação |
|---|---|
| Mouse | Clicar nos botões do menu e nos objetos do quarto |
| ESPAÇO | Avançar as falas |
| ESC | Voltar ao menu (o progresso é salvo) |
| Minigame (corrida) | ESPAÇO, W ou seta para cima para pular |
| Minigame (puzzle) | WASD/setas movem, ESPAÇO atira, R reinicia a fase |
| Tela FIM | ENTER joga de novo, M volta ao menu, ESC sai |

### O que o jogo contém

- **Menu principal:** Novo Jogo, Continuar (usa o save), Créditos e Sair.
- **Missão jogável do início ao fim:** introdução em 2007, exploração do quarto, minigame de obstáculos com puzzle de 3 fases e epílogo.
- **Tratamento de entradas inválidas:** feito com laço `while` na tela final.
- **Game loop com encerramento controlado:** a tela final pergunta se o jogador quer jogar de novo ou sair.

🎬 **Screencast:** [Assistir à demonstração](https://drive.google.com/file/d/1cgYbGEYNcb32-t48MkWrdA1o_scuL_fV/view?usp=sharing)

O vídeo mostra o jogo rodando, o tratamento de erros em ação e a missão completa sendo jogada.

---

<a id="colaboracao"></a>
# 🤝 Colaboração e evidências

## Programação em pares

Durante a sprint, a equipe realizou sessões de programação em pares, remotamente por chamada com compartilhamento de tela e presencialmente na faculdade. Os integrantes alternaram entre os papéis de **piloto**, responsável por escrever o código, e **navegador**, responsável por acompanhar a implementação, revisar e discutir soluções. Além dessas sessões, a equipe analisou o código em conjunto semanalmente.

Este relato foi elaborado retrospectivamente, com base nas experiências dos participantes.

## Contribuições das duplas

| Dupla | Formato | Trabalho realizado | Papéis desempenhados |
|---|---|---|---|
| Vitória e Aline | Chamada com tela compartilhada | Implementação da US08: exploração do quarto em 2007. | Dev / Dev |
| Juliana e Luiz Mario | Presencial, na faculdade | Implementação do reprodutor de áudio. | Dev / Dev |
| Ana Rita e Luiz Mario | Presencial, na faculdade | Inserção dos áudios no código do jogo. | Dev / Dev |
| Vitória e Luiz Mario | Chamada com tela compartilhada | Integração do reprodutor de áudio com o código da US08. | Dev / Dev |

## Experiência e aprendizados

A organização da US08 foi um ponto positivo do trabalho em dupla. O acompanhamento e o revezamento permitiram discutir a implementação durante o desenvolvimento.

A principal dificuldade foi dividir a implementação dos sons entre diferentes duplas e integrar as partes ao jogo. Essa experiência indicou a necessidade de combinar previamente as responsabilidades e os pontos de integração do código.

Para a próxima sprint, a proposta é registrar cada sessão com três informações: **dupla, tarefa realizada e resultado**, além de associar o trabalho à história e ao commit ou pull request correspondente.

---

<a id="equipe"></a>
# 👥 Equipe

| Integrante | Papel no Projeto | Principais Responsabilidades |
|---|---|---|
| Aline Santos | Game Designer, Desenvolvedora | UX/UI e Narrativa, Desenvolvimento e implementação do produto |
| Ana Rita Correia | Product Owner, Desenvolvedora | Visão do produto e priorização do backlog, Desenvolvimento e implementação do produto |
| Juan Nunes |  |  |
| Juliana Freire | Scrum Master | Organização do fluxo e acompanhamento das tarefas |
| Leandro Luís |  |  |
| Luiz Mario | Desenvolvedor | Desenvolvimento e implementação do produto |
| Vinícius Lino | Desenvolvedor | Desenvolvimento e implementação do produto |
| Vitória Santos | Game Designer, Desenvolvedor | UX/UI, Desenvolvimento e implementação do produto |

### Perfis

* 👤 **Aline Santos** — [GitHub](https://github.com/alines91) | [LinkedIn](https://www.linkedin.com/in/aline-santos-920488111/)
* 👤 **Ana Rita Correia** — [GitHub](https://github.com/anaritamoura) | [LinkedIn](https://www.linkedin.com/in/anaritamcorreia/en)
* 👤 **Gabriel Farias** — [GitHub](https://github.com/gabrielfariaxs) | [LinkedIn](https://www.linkedin.com/in/gabrielfariaxs)
* 👤 **Juan Nunes** — [GitHub](https://github.com/JuanSVJ60)
* 👤 **Juliana Freire** — [GitHub](https://github.com/julianafreire-jpg) | [LinkedIn](https://www.linkedin.com/in/juliana-freire-40393685/)
* 👤 **Leandro Luís** —
* 👤 **Luiz Mario** — [GitHub](https://github.com/romaiziul) | [LinkedIn](https://www.linkedin.com/in/luiz-mario-moreira)
* 👤 **Vinícius Lino** — [GitHub](https://github.com/Vini-Lino)
* 👤 **Vitória Santos** — [GitHub](https://github.com/vitoriaSilva94) | [LinkedIn](https://www.linkedin.com/in/vitoria-rodrigues-493a57248/)

---

<a id="organizacao"></a>
# 📁 Organização do Repositório

```text
📦 projeto2-squad2
├── 📁 assets
│   ├── backlog.png
│   ├── backlog1.png
│   ├── logo_smalld.png
│   └── [IMAGENS E EVIDÊNCIAS DO PROJETO]
│
├── 📁 docs
│   ├── 📁 diagramas
│   │   ├── US01-diagrama-atividades.png
│   │   ├── US02-diagrama-atividades.png
│   │   ├── US03-diagrama-atividades.png
│   │   ├── US04-diagrama-atividades.png
│   │   ├── US05-diagrama-atividades.png
│   │   ├── US06-diagrama-atividades.png
│   │   ├── US07-diagrama-atividades.png
│   │   ├── US08-diagrama-atividades.png
│   │   ├── US09-diagrama-atividades.png
│   │   ├── US10-diagrama-atividades.png
│   │   ├── US11-diagrama-atividades.png
│   │   ├── US12-diagrama-atividades.png
│   │   ├── US13-diagrama-atividades.png
│   │   ├── US14-diagrama-atividades.png
│   │   ├── US15-diagrama-atividades.png
│   │   └── US16-diagrama-atividades.png
│   │
│   ├── 📁 screencasting
│   │   └── screencast.MOV
│   └── 📁 prototipos
│       ├── 📁 US01
│       ├── 📁 US02
│       ├── 📁 US03
│       ├── 📁 US04
│       ├── 📁 US05
│       ├── 📁 US06
│       ├── 📁 US07
│       ├── 📁 US08
│       ├── 📁 US09
│       ├── 📁 US10
│       ├── 📁 US11
│       ├── 📁 US12
│       ├── 📁 US13
│       ├── 📁 US14
│       ├── 📁 US15
│       └── 📁 US16
│
├── 📁 entrega_pif
│   └── 📁 re7
│       ├── 📁 assets
│       │   ├── 📁 backgrounds
│       │   ├── 📁 characters
│       │   ├── 📁 music
│       │   ├── 📁 sounds
│       │   └── 📁 ui
│       ├── 📁 docs
│       │   └── documentacao_audio.md
│       ├── 📁 src
│       │   ├── main.c
│       │   ├── game.c / game.h
│       │   ├── scenes.c / scenes.h
│       │   ├── story.c / story.h
│       │   ├── minigame.c / minigame.h
│       │   ├── room.c / room.h
│       │   ├── ui.c / ui.h
│       │   ├── assets.c / assets.h
│       │   └── audio_manager.c / audio_manager.h
│       ├── re7.exe
│       ├── re7_novo.exe
│       ├── save.dat
│       └── recorde.dat
│
├── 📁 src
│   └── test.gitkeep
│
├── .gitignore
└── README.md
```

---

<a id="links"></a>
# 🔗 Links Importantes

* 🎨 **Figma:** [Acessar no Figma](https://www.figma.com/board/YzFyw4c14ZIFgUF8Eu8Pjm/Projeto-Integrador---Cesar-2026.2?node-id=0-1&t=iAXRReHgs6IUaz6I-1)
* 🧩 **Diagramas de Atividades:** [Acessar diagramas](docs/diagramas/)
* 🎥 **Screencast do Protótipo Lo-Fi:** [Assistir demonstração](https://github.com/user-attachments/assets/50ce844c-50ce-4cf1-9a50-a5752a2afe01)
* 🎥 **Screencast do Núcleo em C (PIF):** [Assistir demonstração](https://drive.google.com/file/d/1cgYbGEYNcb32-t48MkWrdA1o_scuL_fV/view?usp=sharing)
* 📋 **Jira:** [Acessar Jira](https://csprj-adsr-2p-e2.atlassian.net/jira/software/c/projects/PI2/boards/2?atlOrigin=eyJpIjoiMWEwODM2MTk4OTJhNDA4NDliMWQ0OWIxOGRmMmU0NzciLCJwIjoiaiJ9)
* 📋 **Trello:** [Acessar Board](https://trello.com/b/t0u8Iplf)
* 💻 **Repositório:** [Acessar repositório](https://github.com/anaritamoura/projeto2-squad2)
* 🎨 **Protótipo Lo-fi:** [Acessar no Figma](https://www.figma.com/proto/SOWkT7Av6D6rrZESX9XgtQ/Prot%C3%B3tipo---FDS---Entrega-2?node-id=95-194&p=f&t=YOhw8Vmu5wDwYyXY-0&scaling=contain&content-scaling=fixed&page-id=95%3A101&starting-point-node-id=95%3A194&show-proto-sidebar=1)

---

<p align="center">
  Desenvolvido pela <strong>Equipe 2</strong>
</p>

<p align="center">
  CESAR School • ADS • 2026
</p>
