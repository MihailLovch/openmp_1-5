#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

int main() {
    const int rows = 6;
    const int cols = 8;
    int d[rows][cols];

    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            d[i][j] = rand() % 100;
        }
    }

    float average = 0.0f;
    int min_value = d[0][0];
    int max_value = d[0][0];

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        #pragma omp sections
        {
            #pragma omp section
            {
                int local_sum = 0;

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        local_sum += d[i][j];
                    }
                }

                #pragma omp critical
                {
                    average += static_cast<float>(local_sum) / (rows * cols);
                    std::cout << "Thread " << thread_id << " - Average: " << average << std::endl;
                }
            }

            #pragma omp section
            {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (d[i][j] < min_value) {
                            #pragma omp critical
                            {
                                if (d[i][j] < min_value) {
                                    min_value = d[i][j];
                                }
                            }
                        }

                        if (d[i][j] > max_value) {
                            #pragma omp critical
                            {
                                if (d[i][j] > max_value) {
                                    max_value = d[i][j];
                                }
                            }
                        }
                    }
                }

                #pragma omp critical
                {
                    std::cout << "Thread " << thread_id << " - Min Value: " << min_value << ", Max Value: " << max_value << std::endl;
                }
            }

            #pragma omp section
            {
                int local_count = 0;

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (d[i][j] % 3 == 0) {
                            local_count++;
                        }
                    }
                }

                #pragma omp critical
                {
                    std::cout << "Thread " << thread_id << " - Count Multiples of 3: " << local_count << std::endl;
                }
            }
        }
    }
    return 0;
}
