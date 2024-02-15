#include <iostream>
#include <chrono>

#include <random>

#include <omp.h>

void generateRandomData(float *a1, float *a2, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dis(0.0, 1.0);

    float r;
    for (int i = 0; i < size; i++) {
        r = dis(gen);
        a1[i] = r;
        a2[i] = r;
    }
    
}

int main() {

    const int N = 50000;

    float arr1[N];
    float arr2[N];

    generateRandomData(arr1, arr2, N);

    
    double s_t1 = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr1[i] = arr1[i] * arr1[j];
        }
    }
    double e_t1 = omp_get_wtime();

    double s_t2 = omp_get_wtime();
    # pragma omp parallel for num_threads(16)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr2[i] = arr2[i] * arr2[j];
        }
    }
    double e_t2 = omp_get_wtime();
    
    // auto d1 = std::chrono::duration_cast<std::chrono::microseconds>(e_t1 - s_t1);
    // auto d2 = std::chrono::duration_cast<std::chrono::microseconds>(e_t2 - s_t2);
    
    double d1 = e_t1 - s_t1;
    double d2 = e_t2 - s_t2;

    std::cout << "Execution time NORMAL: " << d1 << " seconds" << std::endl;
    std::cout << "Execution time OMP: " << d2 << " seconds" << std::endl;

    return 0;
}