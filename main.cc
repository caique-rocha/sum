#include <iostream>
#include <iomanip> // Biblioteca para formatar a tabela (espaçamentos)
#include <omp.h>

using namespace std;

// Assinatura da função
void sum(char* output, const long unsigned int d, const long unsigned int n);

int main() {
    const long unsigned int d = 1000;
    const long unsigned int n = 10000000;

    // Lista com a quantidade de threads que queremos testar
    int testes_threads[] = {1, 2, 4, 8};

    // Variável para guardar o tempo da versão sequencial e calcular o Speedup depois
    double tempo_sequencial = 0.0;

    cout << "Iniciando Benchmark da Soma Harmônica Paralela..." << endl;
    cout << "Termos (n): " << n << " | Casas Decimais (d): " << d << "\n" << endl;

    // Cabeçalho da Tabela
    cout << "------------------------------------------------" << endl;
    cout << left << setw(10) << "Threads"
         << "| " << setw(15) << "Tempo (seg)"
         << "| " << "Speedup (Aceleração)" << endl;
    cout << "------------------------------------------------" << endl;

    // Loop que vai rodar o programa 4 vezes (para 1, 2, 4 e 8 threads)
    for (int num_threads : testes_threads) {

        // Define o número de threads para esta rodada
        omp_set_num_threads(num_threads);

        // Cria um array limpinho para cada teste
        char output[15000] = {0};

        // --- CRONÔMETRO LIGADO ---
        double inicio = omp_get_wtime();

        sum(output, d, n);

        // --- CRONÔMETRO DESLIGADO ---
        double fim = omp_get_wtime();
        double tempo_gasto = fim - inicio;

        // Se for o teste com 1 thread, salvamos o tempo como nossa "âncora" (Sequencial)
        if (num_threads == 1) {
            tempo_sequencial = tempo_gasto;
        }

        // Calcula o Speedup (Tempo Sequencial / Tempo Atual)
        double speedup = tempo_sequencial / tempo_gasto;

        // Imprime a linha da tabela formatada
        cout << left << setw(10) << num_threads
             << "| " << setw(15) << fixed << setprecision(4) << tempo_gasto
             << "| " << speedup << "x" << endl;
    }

    cout << "------------------------------------------------" << endl;
    cout << "Benchmark finalizado com sucesso!" << endl;

    return 0;
}