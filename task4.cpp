#include <iostream>
#include <omp.h>

int main() {
    int a[10] = {12, 5, 7, 24, 8, 19, 3, 10, 15, 6};
    int b[10] = {42, 15, 37, 8, 29, 11, 54, 6, 18, 33};

    int min_a = INT_MAX; // Инициализируем min_a максимальным значением int
    int max_b = INT_MIN; // Инициализируем max_b минимальным значением int

#pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();

        if (thread_id == 0) {
            for (int i = 0; i < 10; i++) {
                if (a[i] < min_a) {
                    #pragma omp critical
                    {
                        if (a[i] < min_a) {
                            min_a = a[i];
                        }
                    }
                }
            }
        } else if (thread_id == 1) {
            for (int i = 0; i < 10; i++) {
                if (b[i] > max_b) {
                    #pragma omp critical
                    {
                        if (b[i] > max_b) {
                            max_b = b[i];
                        }
                    }
                }
            }
        }
    }

    std::cout << "Min value in array a: " << min_a << std::endl;
    std::cout << "Max value in array b: " << max_b << std::endl;

    return 0;
}
