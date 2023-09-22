#include <iostream>
#include <omp.h>

int main() {
    int a = 7;
    int b = 8;

    std::cout << "Before entering parallel regions: a = " << a << ", b = " << b << std::endl;

#pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        int thread_id = omp_get_thread_num();
        a += thread_id;
        b += thread_id;

#pragma omp critical
        {
            std::cout << "Inside parallel region 1: Thread " << thread_id << " : a = " << a << ", b = " << b << std::endl;
        }
    }

#pragma omp parallel num_threads(4) shared(a) private(b)
    {
        int thread_id = omp_get_thread_num();
        a -= thread_id;
        b -= thread_id;

#pragma omp critical
        {
            std::cout << "Inside parallel region 2: Thread " << thread_id << " : a = " << a << ", b = " << b << std::endl;
        }
    }

    std::cout << "After exiting parallel regions: a = " << a << ", b = " << b << std::endl;

    return 0;
}
