#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>

//Criação da função insertionSort, que vai fazer a odernação por inserção, usando o & no parâmetro para otimizar a execução
void insertionSort(vector<int>& A, int esq, int dir) {
    //Laço para iterar o vetor
    for(int i = esq + 1; i < dir; i++){
        int p = A[i];             //Variável que recebe o valor do elemento atual do vetor
        int j = i - 1;           //Variável que recebe o valor da posição do indice a esquerda da posição atual do vetor

        //Laço para mudar posição dos valores
        while(j >= esq && A[j] > p){
            A[j + 1] = A[j];    //Caso a condição do while seja verdadeira, coloca o valor maior para a direita
            j--;                //Passo para respeita a iteração decrescente do indice
        }

        A[j + 1] = p;           //Posição que vai ficar elemento p
    }
}









int main() {
    const int TRIALS = 5;
    const int START_SIZE = 0;
    const int END_SIZE = 20000; // Limite viável para O(N^2)
    const int STEP = 1000;

    // --------------------------------------------------------------------------
    // 1. MELHOR CASO (Vetor já ordenado em ordem crescente) -> O(N)
    // --------------------------------------------------------------------------
    std::cout << "MELHORES CASOS - INSERTION SORT\n";
    std::cout << "Tamanho,Tempo_ns\n";

    for (int size = START_SIZE; size <= END_SIZE; size += STEP) {
        if (size == 0) {
            std::cout << "0,0\n";
            continue;
        }

        long long totalDuration = 0;
        for (int t = 0; t < TRIALS; ++t) {
            std::vector<int> vec(size);
            for (int i = 0; i < size; ++i) vec[i] = i; // Vetor crescente

            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(vec, 0, size);
            auto end = std::chrono::high_resolution_clock::now();

            totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        std::cout << size << "," << (totalDuration / TRIALS) << "\n";
    }

    std::cout << "\n";

    // --------------------------------------------------------------------------
    // 2. PIOR CASO (Vetor em ordem estritamente decrescente) -> O(N^2)
    // --------------------------------------------------------------------------
    std::cout << "PIORES CASOS - INSERTION SORT\n";
    std::cout << "Tamanho,Tempo_ns\n";

    for (int size = START_SIZE; size <= END_SIZE; size += STEP) {
        if (size == 0) {
            std::cout << "0,0\n";
            continue;
        }

        long long totalDuration = 0;
        for (int t = 0; t < TRIALS; ++t) {
            std::vector<int> vec(size);
            for (int i = 0; i < size; ++i) vec[i] = size - i; // Vetor decrescente

            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(vec, 0, size);
            auto end = std::chrono::high_resolution_clock::now();

            totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        std::cout << size << "," << (totalDuration / TRIALS) << "\n";
    }

    return 0;
}