#include <iostream>
#include <sstream>
#include <omp.h>

using namespace std;

void sum(char* output, const long unsigned int d, const long unsigned int n);

void sum(char* output, const long unsigned int d, const long unsigned int n) {
    long unsigned int digits[d+11];

    // Zera o array global
    for(long unsigned int digit=0; digit<d+11; ++digit) {
       digits[digit]=0;
    }

    // Abre o bloco paralelo
    #pragma omp parallel
    {
        // 1. Cada thread cria e zera o seu próprio array local (o rascunho)
        long unsigned int local_digits[d+11];
        for(long unsigned int digit=0; digit<d+11; ++digit) {
            local_digits[digit]=0;
        }

        // 2. O OpenMP divide o loop 'n' automaticamente entre as threads
        #pragma omp for
        for(long unsigned int i=1; i<=n; ++i) {
           long unsigned int remainder=1;

           for(long unsigned int digit=0; digit<d+11 && remainder; ++digit) {
              long unsigned int div = remainder/i;
              long unsigned int mod = remainder%i;

              // ATENÇÃO: Soma no array LOCAL, não no global!
              local_digits[digit] += div;
              remainder = mod*10;
           }
        }

        // 3. Junta tudo!
        // A diretiva 'critical' obriga as threads a fazerem uma fila.
        // Apenas uma thread entra nesse bloco por vez para evitar atropelos na memória.
        #pragma omp critical
        {
            for(long unsigned int digit=0; digit<d+11; ++digit) {
                digits[digit] += local_digits[digit];
            }
        }

    } // FIM DO BLOCO PARALELO. A partir daqui volta a ser uma thread só.

    // 4. Arrumando o "vai um" do array global
    // Isso deve ser feito de forma sequencial, depois de juntar tudo.
    for(long unsigned int i=d+11-1; i>0; --i) {
       digits[i-1] += digits[i]/10;
       digits[i] %= 10;
    }

    if(digits[d+1] >= 5) {
       ++digits[d];
    }

    for(long unsigned int i=d; i>0; --i) {
       digits[i-1] += digits[i]/10;
       digits[i] %= 10;
    }

    stringstream stringstreamA;
    stringstreamA << digits[0] << ",";
    for(long unsigned int i=1; i<=d; ++i) {
       stringstreamA << digits[i];
    }
    string stringA = stringstreamA.str();
    stringA.copy(output, stringA.size());

    output[stringA.size()] = '\0';
}