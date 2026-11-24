#include <bits/stdc++.h>
using namespace std;

// Estruturas de GrafoCC (GrafoMatriz.cpp e GrafoLista.cpp)
typedef vector<vector<int>> Matriz;
typedef vector<vector<int>> Lista;
typedef vector<pair<int, int>> Arestas;

void leituraGrafoMatriz(Matriz &, const Arestas &);
void leituraGrafoLista(Lista &, const Arestas &);
void escritaGrafoMatriz(Matriz &);
void escritaGrafoLista(Lista &);

vector<int> grausMatriz(const Matriz &);
vector<int> grausLista(const Lista &);
vector<int> ordenaPorGrau(const vector<int> &);
int limiteWelshPowell(const vector<int> &, const vector<int> &);
int coloracaoMatriz(const Matriz &, const vector<int> &, vector<int> &);
int coloracaoLista(const Lista &, const vector<int> &, vector<int> &);
bool coloracaoValida(const Lista &, const vector<int> &);

int main()
{
    int n, m;
    cin >> n >> m;
    Arestas E(m);
    for (auto &e : E)
        cin >> e.first >> e.second;

    Matriz GM;
    GM.assign(n, vector<int>(n, 0));
    leituraGrafoMatriz(GM, E);
    Lista GL;
    GL.assign(n, vector<int>());
    leituraGrafoLista(GL, E);
    escritaGrafoMatriz(GM);
    escritaGrafoLista(GL);

    // Passos 1 e 2: graus e lista L
    vector<int> grau = grausLista(GL);
    vector<int> L = ordenaPorGrau(grau);
    cout << "Ordem L:";
    for (int v : L)
        cout << " " << v << "(" << grau[v] << ")";
    cout << endl;

    // Passos 3 a 6: duas versões do algoritmo
    vector<int> corM, corL;
    int kM = coloracaoMatriz(GM, L, corM);
    int kL = coloracaoLista(GL, L, corL);

    cout << "Cores (matriz): " << kM << endl;
    cout << "Cores (lista):  " << kL << endl;
    cout << "Mesma coloração: " << (corM == corL ? "sim" : "não") << endl;
    cout << "Coloração válida: " << (coloracaoValida(GL, corL) ? "sim" : "não") << endl;
    cout << "Limite de Welsh-Powell: " << limiteWelshPowell(L, grau) << endl;
    for (int v = 0; v < n; v++)
        cout << "Vértice " << v << ": cor " << corL[v] << endl;
    cout << "Total Vértices: " << n << endl;
    cout << "Total Arestas: " << m << endl;
    return 0;
}

void leituraGrafoMatriz(Matriz &G, const Arestas &E)
{
    for (auto e : E)
    {
        G[e.first][e.second] = 1;
        G[e.second][e.first] = 1;
    }
}

void leituraGrafoLista(Lista &G, const Arestas &E)
{
    for (auto e : E)
    {
        G[e.first].push_back(e.second);
        G[e.second].push_back(e.first);
    }
}

void escritaGrafoMatriz(Matriz &G)
{
    int n = G.size();
    cout << "Matriz de Adjacência:" << endl;
    cout << "   ";
    for (int u = 0; u < n; u++)
        cout << u << " ";
    cout << endl;
    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";
        for (int v = 0; v < n; v++)
            cout << G[u][v] << " ";
        cout << endl;
    }
}

void escritaGrafoLista(Lista &G)
{
    int n = G.size();
    cout << "Lista de Adjacência:" << endl;
    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";
        for (auto v : G[u])
            cout << v << " ";
        cout << endl;
    }
}

// Passo 1: graus (O(n^2) com matriz, O(n) com listas apos a leitura)
vector<int> grausMatriz(const Matriz &G)
{
    int n = G.size();
    vector<int> grau(n, 0);
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            grau[u] += G[u][v];
    return grau;
}

vector<int> grausLista(const Lista &G)
{
    int n = G.size();
    vector<int> grau(n);
    for (int u = 0; u < n; u++)
        grau[u] = G[u].size();
    return grau;
}

// Passo 2: ordem não crescente de grau; empates por índice (estável)
vector<int> ordenaPorGrau(const vector<int> &grau)
{
    int n = grau.size();
    vector<int> L(n);
    iota(L.begin(), L.end(), 0);
    stable_sort(L.begin(), L.end(),
                [&](int a, int b) { return grau[a] > grau[b]; });
    return L;
}

// max_i min(i, d(v_i)+1), com i começando em 1
int limiteWelshPowell(const vector<int> &L, const vector<int> &grau)
{
    int lim = 0;
    for (int i = 1; i <= (int)L.size(); i++)
        lim = max(lim, min(i, grau[L[i - 1]] + 1));
    return lim;
}

// Passos 3 a 6 por classes de cor, sobre a matriz: O(n^2)
int coloracaoMatriz(const Matriz &G, const vector<int> &L, vector<int> &cor)
{
    int n = G.size(), k = 0, coloridos = 0;
    cor.assign(n, 0);
    while (coloridos < n)
    {
        k++;
        vector<int> classe;
        for (int v : L)
        {
            if (cor[v] != 0)
                continue;
            bool livre = true;
            for (int u : classe)
                if (G[v][u] == 1)
                {
                    livre = false;
                    break;
                }
            if (livre)
            {
                cor[v] = k;
                classe.push_back(v);
                coloridos++;
            }
        }
    }
    return k;
}

// Versão first-fit equivalente, sobre listas: O(n + m)
int coloracaoLista(const Lista &G, const vector<int> &L, vector<int> &cor)
{
    int n = G.size(), k = 0;
    cor.assign(n, 0);
    vector<int> marca(n + 2, -1);
    for (int v : L)
    {
        for (int u : G[v])
            if (cor[u] != 0)
                marca[cor[u]] = v;
        int c = 1;
        while (marca[c] == v)
            c++;
        cor[v] = c;
        k = max(k, c);
    }
    return k;
}

bool coloracaoValida(const Lista &G, const vector<int> &cor)
{
    for (int u = 0; u < (int)G.size(); u++)
    {
        if (cor[u] == 0)
            return false;
        for (int v : G[u])
            if (cor[u] == cor[v])
                return false;
    }
    return true;
}
