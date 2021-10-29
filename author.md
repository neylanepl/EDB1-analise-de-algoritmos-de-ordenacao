# Identificação Pessoal

Preencha os dados abaixo para identificar a autoria do trabalho.

- Nome: *<Jonas de Oliveira Freire Filho e Neylane Pereira Lopes>*
- Email: *<jonas.oliveira.111@ufrn.edu.br e neylane.lopes.127@ufrn.edu.br>*
- Turma: *<DIM0119 - T01>*

# Indique quais algoritmos foram implementados nos experimentos

- [x] Insertion sort
- [x] Selection sort
- [x] Bubble sort
- [x] Shell sort
- [x] Quick sort
- [x] Merge sort
- [x] Radix sort

# Indique quais dos cenários de dados abaixo você conseguiu simular nos experimentos

- [x] todos randômicos
- [x] parcialmente ordenado (75%)
- [x] parcialmente ordenado (50%)
- [x] parcialmente ordenado (25%)
- [x] dados em ordem não-decrescente
- [x] dados em ordem não-crescente

# Escreva a quantidade de amostras coletadas por experimento

- Utilizei 25 amostras por experimento

# Indique quais das perguntas abaixo foram respondidas no relatório

- [x] O que você descobriu de maneira geral.
- [x] Quais algoritmos são recomendados para quais cenários?
- [x] Como o algoritmo de decomposição de chave (radix) se compara com o melhor algoritmo baseado em _comparação_ de chaves?
- [x] É verdade que o _quick sort_, na prática, é mesmo mais rápido do que o _merge sort_?
- [x] Aconteceu algo inesperado nas medições? (por exemplo, picos ou vales nos gráficos) Se sim, por que?
- [ ] Com base nos resultados empíricos, faça uma estimativa para os 7 algoritmos estudados de quanto tempo seria necessário para rodar uma amostra de $10^12$ elementos.
- [x] A análise empírica é compatível com a análise de complexidade matemática? Ou seja, você consegui ajustar uma curva compatível com a complexidade aos dados?

# Instruções de como compilar e executar o programa

### Como compilar o projeto

Para compilar o projeto, pode-se usar o **g++**.

#### Compilando com o g++

1. Entre na pasta do projeto.

2. Execute abaixo para **compilar** o projeto:
```
g++ -Wall -pedantic -std=c++17 -fsanitize=address -o bin/analisysEmpirical source/main.cpp source/lib/sorting.h source/lib/scenarios.h source/lib/ClassDataScenarios.h source/lib/ClassSortingCollection.h
```

### Como executar o projeto

1. Execute o arquivo `analisysEmpirical` que se encontra dento da pasta `bin` com o seguinte comando:
```
./bin/analisysEmpirical [min_sample_sz] [max_sample_sz] [n_samples] [which_algs] [which_scenarios] [n_runs]
```

--------
&copy; DIMAp/UFRN 2021.
