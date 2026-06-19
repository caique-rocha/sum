# Cálculo de Alta Precisão da Soma Harmônica

Este projeto foi desenvolvido para calcular a soma de uma progressão harmônica simples com precisão arbitrária de casas decimais:

$$S_{n} = \sum_{i=1}^{n} \left(\frac{1}{i}\right) = 1 + \frac{1}{2} + \frac{1}{3} + \dots + \frac{1}{n}$$

O objetivo principal é comparar o desempenho e o tempo de execução do algoritmo utilizando duas tecnologias diferentes para paralelização:
1. **OpenMP** (Trabalha com threads dividindo a memória do mesmo computador)
2. **MPI** (Trabalha com processos isolados que se comunicam por mensagens)

---

## 📋 Como o problema funciona

* [cite_start]**Entrada:** O programa espera receber dois valores inteiros através do terminal: o número de dígitos de precisão ($D$) e o número de termos para calcular ($N$)[cite: 67, 68].
* [cite_start]**Saída:** O programa imprime uma única linha na tela com o resultado exato e formatado com as $D$ casas decimais solicitadas[cite: 70, 71].

**Exemplo Prático:**
[cite_start]Se a entrada for `12 7` [cite: 74][cite_start], a saída gerada será `2.592857142857`[cite: 76].

---

## 📂 Organização das Pastas

O repositório está estruturado da seguinte forma:

```text
sum/ (Raiz do projeto)
│  ├── main.cc       <-- Código principal com a lógica em OpenMP
│  ├── sum.cc        <-- Algoritmo da soma harmônica paralelizado com OpenMP
│  ├── Makefile      <-- Configuração de compilação para OpenMP
│
└── versao-MPI/      <-- Pasta dedicada à versão MPI
       ├── main.cc   <-- Código principal com inicialização do MPI
       ├── sum.cc    <-- Algoritmo dividindo os termos por processos (MPI_Reduce)
       └── Makefile  <-- Configuração de compilação usando o wrapper mpicxx
