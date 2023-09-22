#include <iostream>
#include <omp.h>

int main() {
    int num_threads = 8;
    omp_set_num_threads(num_threads);

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_thread = omp_get_num_threads();
#pragma omp critical
        {
            std::cout << "Thread ID: " << thread_id << ", Total Threads: " << num_thread << ", Hello World" << std::endl;
        }
    }

    return 0;
}

/*
 * Всегда ли вывод идентичен? Почему?:
 * Порядок отличается, тк как потоки выполняются в случайном порядке в заисимости от планировщика OpenMP и ОС
 */