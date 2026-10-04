#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
using namespace std;

// Criação da função Insertion Sort, que vai fazer a odernação por inserção, usando o & no parâmetro para otimizar a execução
void insertionSort(vector<int> &A, int esq, int dir)
{
    // Laço para iterar o vetor
    for (int i = esq + 1; i < dir; i++)
    {
        int p = A[i];  // Variável que recebe o valor do elemento atual do vetor
        int j = i - 1; // Variável que recebe o valor da posição do indice a esquerda da posição atual do vetor

        // Laço para mudar posição dos valores
        while (j >= esq && A[j] > p)
        {
            A[j + 1] = A[j]; // Caso a condição do while seja verdadeira, coloca o valor maior para a direita
            j--;             // Passo para respeita a iteração decrescente do indice
        }

        A[j + 1] = p; // Posição que vai ficar elemento p
    }
}

// Criação da função Selection Sort
void selectionSort(vector<int> &A, int esq, int dir)
{
    // Laço para iterar o vetor
    for (int i = esq; i < dir - 1; i++)
    {
        int min_idx = i; // criação da variável para guardar o menor indice do elemento da iteração

        // Laço aninhado para procurar o indice de menor valor
        for (int j = i + 1; j < dir; j++)
        {

            // Condição para comparar se o valor do elemento atual é menor que o valor do menor elemento até aquela iteração
            if (A[j] < A[min_idx])
            {
                min_idx = j; // Se for, o indice do menor elemento é atualizado
            }
        }
        // Troca do menor elemento encontrado para a sua posição correta da parte ordenada
        int aux = A[i]; // Variável para auxiliar na troca dos elementos
        A[i] = A[min_idx];
        A[min_idx] = aux;
    }
}

// Criação da função Bubble Sort
void bubbleSort(vector<int> &A, int esq, int dir)
{
    // Laço que percorre o vector da direita para a esquerda
    for (int i = dir - 1; i > esq; i--)
    {
        // Laço que coloca o maior elemento para o final, colocando em ordem
        for (int j = esq; j < i; j++)
        {
            // Essa condição verifica a ordem dos elementos, caso eles estejam na ordem errada ela troca eles
            if (A[j] > A[j + 1])
            {
                int aux = A[j]; // Variável para auxiliar na troca dos elementos
                A[j] = A[j + 1];
                A[j + 1] = aux;
            }
        }
    }
}

// Criação da função Quick Sort
void quickSort(vector<int> &A, int esq, int dir)
{
    // A condição verifica se o tamanho do vetor é válido para a utilização da função Quick Sort
    if (dir - esq <= 1)
    {
        return; // Se o vetor tiver tamanho menor ou igual a 1 ele já está ordenado, a condição para o código aqui mesmo.
    }

    int u = A[dir - 1]; // Variável que guarda o valor do pivô
    int i = esq - 1;    // Variável que guarda o limite dos elementos menores que o pivô

    // Laço que percorrer o vetor e separa os elementos
    for (int j = esq; j < dir - 1; j++)
    {
        if (A[j] <= u)
        {
            i++;
            int aux_1 = A[j]; // Primeira variável criada para auxiliar na troca dos elementos
            A[j] = A[i];
            A[i] = aux_1;
        }
    }

    int aux_2 = A[i + 1]; // Segunda variável criada para auxiliar na troca dos elementos
    A[i + 1] = A[dir - 1];
    A[dir - 1] = aux_2;

    int posicao_final = i + 1; // Variável para guardar a posição final do elemento que ta sendo comparado

    // Usando a recursividade
    quickSort(A, esq, posicao_final);
    quickSort(A, posicao_final + 1, dir);
}

// Criação da função Merge Sort em duas etapas
// Função intercala
void intercala(vector<int> &A, int esq, int metade, int dir)
{
    // Vetores criados para assegurar os dados
    vector<int> E;
    vector<int> D;

    // Laço que coloca os elementos no vetor E
    for (int i = esq; i < metade; i++)
    {
        E.push_back(A[i]);
    }

    // Laço que coloca os elementos no vetor D
    for (int i = metade; i < dir; i++)
    {
        D.push_back(A[i]);
    }

    // Indices que vão controlar a intercalação
    int i = 0;
    int j = 0;
    int k = esq;

    // Laço que itera enquanto tiver elementos nos vetores
    while (i < E.size() && j < D.size())
    {
        // Se o lado direito for maior ou igual o da esquerda, ele vai para o vetor original
        if (E[i] <= D[j])
        {
            A[k] = E[i];
            i++;
            // Se o lado esquerdo for maior ou igual o da direita, ele vai para o vetor original
        }
        else
        {
            A[k] = D[j];
            j++;
        }
        k++;
    }

    // Laço para alocar o restante dos elementos do lado esquerdo, se tiverem
    while (i < E.size())
    {
        A[k] = E[i];
        i++;
        k++;
    }

    // Laço para alocar o restante dos elementos do direito, se tiverem
    while (j < D.size())
    {
        A[k] = D[j];
        j++;
        k++;
    }
}

// Função mergeSorte
void mergeSort(vector<int> &A, int esq, int dir)
{
    // A condição verifica se o tamanho do vetor é válido para a utilização da função Merge Sort
    if (dir - esq <= 1)
    {
        return; // Se o vetor tiver tamanho menor ou igual a 1 ele já está ordenado, a condição para o código aqui mesmo.
    }

    int metade = esq + (dir - esq) / 2; // Variável que calcula a metade do intervalo atual

    // Usando a recursividade
    mergeSort(A, esq, metade);
    mergeSort(A, metade, dir);

    // Função que junta tudo no final
    intercala(A, esq, metade, dir);
}

int main()
{
    const int TRIALS = 5;
    const int START_SIZE = 0;
    const int END_SIZE = 500000;
    const int STEP = 25000;

    // --- ESCUDOS DE SEGURANÇA PARA NÃO TRAVAR O SEU PC ---
    const int LIMIT_LENTOS = 50000;   
    const int LIMIT_QUICK_PIOR = 20000; 

    // --------------------------------------------------------------------------
    // TESTE 1: PIOR CASO (Vetor em ordem decrescente)
    // --------------------------------------------------------------------------
    cout << "--- TESTE 1: PIOR CASO (DECRESCENTE) ---\n";
    cout << "Tamanho,Insertion,Selection,Bubble,Quick,Merge\n";

    for (int size = START_SIZE; size <= END_SIZE; size += STEP)
    {
        long long t_ins = 0, t_sel = 0, t_bub = 0, t_qui = 0, t_mer = 0;

        for (int t = 0; t < TRIALS; ++t)
        {
            vector<int> base(size);
            for (int i = 0; i < size; ++i)
                base[i] = size - i;

            vector<int> v1 = base, v2 = base, v3 = base, v4 = base, v5 = base;

            if (size <= LIMIT_LENTOS)
            {
                auto start = chrono::high_resolution_clock::now();
                insertionSort(v1, 0, size);
                auto end = chrono::high_resolution_clock::now();
                t_ins += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                start = chrono::high_resolution_clock::now();
                selectionSort(v2, 0, size);
                end = chrono::high_resolution_clock::now();
                t_sel += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                start = chrono::high_resolution_clock::now();
                bubbleSort(v3, 0, size);
                end = chrono::high_resolution_clock::now();
                t_bub += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }
            if (size <= LIMIT_QUICK_PIOR)
            {
                auto start = chrono::high_resolution_clock::now();
                quickSort(v4, 0, size);
                auto end = chrono::high_resolution_clock::now();
                t_qui += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }
            // Merge Sort aguenta TUDO, roda sempre!
            auto start = chrono::high_resolution_clock::now();
            mergeSort(v5, 0, size);
            auto end = chrono::high_resolution_clock::now();
            t_mer += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        }
        cout << size << "," << (t_ins / TRIALS) << "," << (t_sel / TRIALS) << "," << (t_bub / TRIALS) << "," << (t_qui / TRIALS) << "," << (t_mer / TRIALS) << "\n";
    }
    cout << "\n";

    // --------------------------------------------------------------------------
    // TESTE 2: MELHOR CASO (Vetor já ordenado crescente)
    // --------------------------------------------------------------------------
    cout << "--- TESTE 2: MELHOR CASO (CRESCENTE) ---\n";
    cout << "Tamanho,Insertion,Selection,Bubble,Quick,Merge\n";

    for (int size = START_SIZE; size <= END_SIZE; size += STEP)
    {
        long long t_ins = 0, t_sel = 0, t_bub = 0, t_qui = 0, t_mer = 0;

        for (int t = 0; t < TRIALS; ++t)
        {
            vector<int> base(size);
            for (int i = 0; i < size; ++i)
                base[i] = i;

            vector<int> v1 = base, v2 = base, v3 = base, v4 = base, v5 = base;

            if (size <= LIMIT_LENTOS)
            {
                auto start = chrono::high_resolution_clock::now();
                insertionSort(v1, 0, size);
                auto end = chrono::high_resolution_clock::now();
                t_ins += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                start = chrono::high_resolution_clock::now();
                selectionSort(v2, 0, size);
                end = chrono::high_resolution_clock::now();
                t_sel += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                start = chrono::high_resolution_clock::now();
                bubbleSort(v3, 0, size);
                end = chrono::high_resolution_clock::now();
                t_bub += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }
            if (size <= LIMIT_QUICK_PIOR)
            { // Para o Partição Lomuto, vetor crescente também quebra o Quick Sort!
                auto start = chrono::high_resolution_clock::now();
                quickSort(v4, 0, size);
                auto end = chrono::high_resolution_clock::now();
                t_qui += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }
            auto start = chrono::high_resolution_clock::now();
            mergeSort(v5, 0, size);
            auto end = chrono::high_resolution_clock::now();
            t_mer += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        }
        cout << size << "," << (t_ins / TRIALS) << "," << (t_sel / TRIALS) << "," << (t_bub / TRIALS) << "," << (t_qui / TRIALS) << "," << (t_mer / TRIALS) << "\n";
    }
    cout << "\n";

    // --------------------------------------------------------------------------
    // TESTE 3: CASO MÉDIO (Vetor com números aleatórios)
    // --------------------------------------------------------------------------
    cout << "--- TESTE 3: CASO MEDIO (ALEATORIO) ---\n";
    cout << "Tamanho,Insertion,Selection,Bubble,Quick,Merge\n";

    for (int size = START_SIZE; size <= END_SIZE; size += STEP)
    {
        long long t_ins = 0, t_sel = 0, t_bub = 0, t_qui = 0, t_mer = 0;

        for (int t = 0; t < TRIALS; ++t)
        {
            vector<int> base(size);
            for (int i = 0; i < size; ++i)
                base[i] = rand() % 100000;

            vector<int> v1 = base, v2 = base, v3 = base, v4 = base, v5 = base;

            if (size <= LIMIT_LENTOS)
            {
                auto start = chrono::high_resolution_clock::now();
                insertionSort(v1, 0, size);
                auto end = chrono::high_resolution_clock::now();
                t_ins += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                start = chrono::high_resolution_clock::now();
                selectionSort(v2, 0, size);
                end = chrono::high_resolution_clock::now();
                t_sel += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                start = chrono::high_resolution_clock::now();
                bubbleSort(v3, 0, size);
                end = chrono::high_resolution_clock::now();
                t_bub += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }
            // No caso aleatório, o Quick Sort é muito eficiente! Pode rodar até os 500.000 sem proteção
            auto start_q = chrono::high_resolution_clock::now();
            quickSort(v4, 0, size);
            auto end_q = chrono::high_resolution_clock::now();
            t_qui += chrono::duration_cast<chrono::nanoseconds>(end_q - start_q).count();
            auto start_m = chrono::high_resolution_clock::now();
            mergeSort(v5, 0, size);
            auto end_m = chrono::high_resolution_clock::now();
            t_mer += chrono::duration_cast<chrono::nanoseconds>(end_m - start_m).count();
        }
        cout << size << "," << (t_ins / TRIALS) << "," << (t_sel / TRIALS) << "," << (t_bub / TRIALS) << "," << (t_qui / TRIALS) << "," << (t_mer / TRIALS) << "\n";
    }

    return 0;
}