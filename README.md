# Coloração de vértices: algoritmo de Campello e Maculan (Welsh–Powell) em C++

Implementação em C++ da heurística gulosa de coloração de vértices com pré-ordenação por graus, descrita por Campello e Maculan (1994) e conhecida como algoritmo de Welsh–Powell. O código reaproveita as estruturas de grafos dos exemplos do GrafoCC (matriz e lista de adjacência).

**Autor:** Célio Omar Cabral de Assis Júnior, Instituto Federal Goiano (IF Goiano)

## Conteúdo

| Arquivo | Descrição |
|---|---|
| `ColoracaoWP.cpp` | Programa completo, com as duas versões do algoritmo |
| `entradas/entrada_exemplo.txt` | Grafo de 8 vértices e 13 arestas do artigo |
| `entradas/entrada_coroa_pior.txt` | Grafo coroa (n = 4) com numeração que leva a 4 cores |
| `entradas/entrada_coroa_melhor.txt` | O mesmo grafo coroa, com numeração que leva a 2 cores |
| `Artigo_Coloracao_Grafos_SBC.pdf` | Artigo sobre a implementação |

## Como compilar e executar

```bash
g++ -O2 -o wp ColoracaoWP.cpp
./wp < entradas/entrada_exemplo.txt
```

## Formato da entrada

A primeira linha traz `n m` (número de vértices e de arestas). Cada uma das `m` linhas seguintes traz os extremos de uma aresta, com vértices numerados de `0` a `n-1`. O grafo é não orientado.

```
8 13
0 1
0 2
...
```

## O que o programa faz

1. Lê o grafo e monta a matriz e a lista de adjacência, escrevendo as duas.
2. Calcula os graus e ordena os vértices em ordem não crescente de grau (empates pelo menor índice).
3. Colore o grafo de duas formas equivalentes:
   - **Matriz de adjacência**, por classes de cor: custo O(n²).
   - **Lista de adjacência**, no estilo first-fit: custo O(m + n log n).
4. Confere se as duas colorações coincidem e se são válidas, e imprime o limite de Welsh–Powell, `max min(i, d(vᵢ) + 1)`.

## Saída esperada

Para `entrada_exemplo.txt` (vértices 0 a 7 correspondem a A a H):

```
Ordem L: 0(4) 2(4) 3(4) 1(3) 4(3) 5(3) 6(3) 7(2)
Cores (matriz): 3
Cores (lista):  3
Mesma coloração: sim
Coloração válida: sim
Limite de Welsh-Powell: 4
Vértice 0: cor 1
Vértice 1: cor 3
Vértice 2: cor 2
Vértice 3: cor 3
Vértice 4: cor 2
Vértice 5: cor 1
Vértice 6: cor 3
Vértice 7: cor 1
```

Resultados dos três arquivos de entrada:

| Entrada | Cores |
|---|---|
| `entrada_exemplo.txt` | 3 (ótimo) |
| `entrada_coroa_pior.txt` | 4 |
| `entrada_coroa_melhor.txt` | 2 (ótimo) |

Os dois grafos coroa são o mesmo grafo com numerações diferentes. Como todos os vértices têm o mesmo grau, a ordem de processamento depende apenas dos desempates, e o resultado muda de 2 para 4 cores. Isso ilustra que o método não garante o número mínimo de cores.

## Uso com as estruturas com peso

As estruturas `GrafoMatrizPeso` e `GrafoListaPeso` podem ser usadas ignorando os pesos. Basta que a leitura insira a aresta nos dois sentidos (nos exemplos originais essa linha está comentada). Detalhes na seção 5.5 do artigo.

## Referência

CAMPELLO, Ruy Eduardo; MACULAN, Nelson. *Algoritmos e heurísticas: desenvolvimento e avaliação de performance*. Niterói: EDUFF, 1994.
