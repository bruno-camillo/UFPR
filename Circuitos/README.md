# 🔌 Circuitos e Arquitetura de Computadores

Este diretório concentra as atividades, simulações e projetos práticos das disciplinas voltadas ao hardware da graduação de Ciência da Computação (UFPR). O foco aqui vai desde a lógica de portas booleanas básicas até o design de arquiteturas de processadores e programação em Assembly.

## 📁 Estrutura do Diretório

### 🖥️ Arquitetura de Computadores (`Arquitetura_Zanata/`)
Projetos avançados de arquitetura e organização de computadores, envolvendo simulação de processadores e programação de baixo nível.
- **Desenvolvimento em Assembly:** Códigos em Assembly (`.asm`) e testes binários/hexadecimais (`.hex`) para validação de instruções.
- **Design de Datapath e Memória:**
  - Simulações de memória RAM dual port (`NEW_dual_port_ram.circ`).
  - Diagramas e modelagem de arquiteturas **VLIW** e arquitetura educacional **REDUX-V** (`breg-VLIW.png`, `datapath-VLIW.png`).
- **Relatórios Técnicos:** Documentação rigorosa em PDF detalhando o funcionamento, as decisões de projeto e o fluxo de dados (pipeline) dos trabalhos.

### 🚥 Circuitos Digitais (`Circuitos Digitais/`)
Desenvolvimento de hardware lógico combinacional e sequencial utilizando o simulador Logisim.
- `semaforo.circ`: Implementação da lógica de controle de estados de um semáforo.
- `sequencia123.circ`: Circuito sequencial e máquinas de estado.
- Trabalhos finais de validação da disciplina.

### ⚙️ Projetos Digitais (`Projetos Digitais/`)
Aprofundamento na integração entre software e hardware.
- Implementação de circuitos complexos (`trabalhoProjetos.circ`).
- Testes de instruções da arquitetura **RISC-V** (`teste_risc-v.s`).

## 🛠️ Ferramentas Utilizadas
- **Logisim:** Para desenho, simulação e teste de circuitos lógicos (`.circ`).
- **Simuladores Assembly:** Para testar os códigos `.asm` e gerar os binários `.hex`.
- **C:** Para criação de pequenos scripts de teste para os hardwares virtuais.

## ▶️ Como visualizar os circuitos
Os arquivos com extensão `.circ` devem ser abertos utilizando o **Logisim**:
1. Instale e abra o [Logisim](http://www.cburch.com/logisim/).
2. Vá em `File > Open` e selecione o circuito desejado para interagir com os pinos de entrada e observar o fluxo dos bits.