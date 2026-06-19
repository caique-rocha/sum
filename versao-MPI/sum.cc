#include <iostream>
#include <sstream>
#include <mpi.h> 

using namespace std;

void sum(char* output, const long unsigned int d, const long unsigned int n, int rank, int size) {
    long unsigned int d_extended = d + 11;
    long unsigned int digits[d_extended] = {0};
    long unsigned int local_digits[d_extended] = {0};

    // Todos os processos limpam suas memórias locais
    for(long unsigned int digit = 0; digit < d_extended; ++digit) {
        local_digits[digit] = 0;
        digits[digit] = 0;
    }

    // DIVISÃO DO TRABALHO: Cada processo pula de acordo com o total de processos (size)
    // Ex: Se forem 4 processos, o Rank 0 faz 1, 5, 9... O Rank 1 faz 2, 6, 10...
    for(long unsigned int i = rank + 1; i <= n; i += size) {
        long unsigned int remainder = 1;

        for(long unsigned int digit = 0; digit < d_extended && remainder; ++digit) {
            long unsigned int div = remainder / i;
            long unsigned int mod = remainder % i;

            local_digits[digit] += div;
            remainder = mod * 10;
        }
    }

    // REDUÇÃO: Soma os vetores 'local_digits' de todos os nós e armazena em 'digits' do Rank 0
    MPI_Reduce(local_digits, digits, d_extended, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // APENAS O RANK 0 faz o pós-processamento do "vai um" e gera o texto final
    if (rank == 0) {
        for(long unsigned int i = d_extended - 1; i > 0; --i) {
            digits[i-1] += digits[i] / 10;
            digits[i] %= 10;
        }

        if(digits[d+1] >= 5) {
            ++digits[d];
        }

        for(long unsigned int i = d; i > 0; --i) {
            digits[i-1] += digits[i] / 10;
            digits[i] %= 10;
        }

        stringstream stringstreamA;
        stringstreamA << digits[0] << ",";
        for(long unsigned int i = 1; i <= d; ++i) {
            stringstreamA << digits[i];
        }
        string stringA = stringstreamA.str();
        stringA.copy(output, stringA.size());

        output[stringA.size()] = '\0';
    }
}
