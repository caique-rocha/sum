#include <iostream>
#include <iomanip>
#include <mpi.h> 

using namespace std;

// Assinatura da função atualizada para receber as variáveis do MPI
void sum(char* output, const long unsigned int d, const long unsigned int n, int rank, int size);

int main(int argc, char** argv) {
    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ID do processo atual
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Total de processos ativos

    const long unsigned int d = 1000;
    const long unsigned int n = 10000000;

    char output[15000] = {0};
    double inicio = 0.0, fim = 0.0, tempo_gasto = 0.0;

    // Apenas o processo mestre (Rank 0) exibe o cabeçalho e controla o tempo global
    if (rank == 0) {
        cout << "Iniciando Benchmark da Soma Harmônica Paralela com MPI..." << endl;
        cout << "Processos totais (size): " << size << endl;
        cout << "Termos (n): " << n << " | Casas Decimais (d): " << d << "\n" << endl;
        inicio = MPI_Wtime(); // Cronômetro do MPI
    }

    // Executa a soma distribuída passando o rank e o size
    sum(output, d, n, rank, size); 

    // Garante que todos os processos terminaram antes de parar o relógio
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        fim = MPI_Wtime();
        tempo_gasto = fim - inicio;

        cout << "------------------------------------------------" << endl;
        cout << "Processos: " << size << " | Tempo: " << fixed << setprecision(4) << tempo_gasto << " seg" << endl;
        cout << "------------------------------------------------" << endl;
    }

    // Finaliza o ambiente MPI
    MPI_Finalize();
    return 0;
}
