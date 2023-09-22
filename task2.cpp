#include <iostream>
#include <omp.h>

int main() {
    int num_threads1 = 3;
    int num_threads2 = 1;

    omp_set_num_threads(num_threads1);
#pragma omp parallel if(num_threads1 > 1)
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        if (num_threads1 > 1) {
#pragma omp critical
            {
                std::cout << "Parallel Region 1: Thread ID = " << thread_id << ", Total Threads = " << num_threads
                          << std::endl;
            }
        }
    }
    omp_set_num_threads(num_threads2);
#pragma omp parallel if(num_threads2 > 1)
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        if (num_threads2 > 1) {
#pragma omp critical
            {
                std::cout << "Parallel Region 2: Thread ID = " << thread_id << ", Total Threads = " << num_threads
                          << std::endl;
            }
        }
    }

    return 0;
}
