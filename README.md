# Coloração de vértices – Campello e Maculan (Welsh–Powell)

Implementação em C++ da heurística gulosa de coloração de vértices com pré-ordenação por graus, usando as estruturas de grafos do GrafoCC (matriz e lista de adjacência).

O programa executa duas versões do algoritmo sobre o mesmo grafo:

- por classes de cor, sobre a matriz de adjacência, com custo O(n²);
- first-fit, sobre listas de adjacência, com custo O(m + n log n).

## Arquivos de entrada

| Arquivo | O que mostra | Resultado |
|---|---|---|
| `entrada_exemplo.txt` | O grafo de 8 vértices e 13 arestas do artigo (A a H = 0 a 7) | 3 cores, coloração ótima, limite de Welsh–Powell = 4 |
| `entrada_coroa_pior.txt` | Grafo coroa com n = 4, vértices numerados de forma intercalada (a₁, b₁, a₂, b₂…) | 4 cores |
| `entrada_coroa_melhor.txt` | O mesmo grafo coroa, com a₁…aₙ seguidos de b₁…bₙ | 2 cores, que é o ótimo |

Os dois grafos coroa são o mesmo grafo com numerações diferentes. Eles mostram que o resultado depende dos desempates.

## Formato da entrada

A primeira linha traz `n m`, e cada uma das `m` linhas seguintes traz uma aresta, com vértices numerados a partir de 0.

## Como rodar

```
g++ -O2 -o wp ColoracaoWP.cpp
./wp < entradas/entrada_exemplo.txt
```
