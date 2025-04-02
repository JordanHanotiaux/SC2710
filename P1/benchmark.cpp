#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <filesystem>
#include <functional>
#include "Matrix.hpp"

namespace fs = std::filesystem;

// Fonction générique pour exécuter un benchmark et enregistrer les résultats
// Aide de Chat-GPT pour les arguments de la fonction et la création du folder Benchmark
void RunBenchmark(const std::string& filename, const std::vector<int>& sizes, 
                  std::function<void(int)> benchmarkFunc) {
    std::ofstream file("Benchmark/" + filename);
    file << "MatrixSize,ExecutionTime(s)\n";

    for (int size : sizes) {
        auto start = std::chrono::high_resolution_clock::now();
        benchmarkFunc(size);
        auto end = std::chrono::high_resolution_clock::now();

        double execTime = std::chrono::duration<double>(end - start).count();
        file << size << "," << execTime << "\n";
    }

    file.close();
}

void Benchmark() {
    fs::create_directory("Benchmark");
    std::vector<int> sizes_MatrixMultiplication = {10, 50, 100, 200, 500, 1000, 2000, 4000};
    std::vector<int> sizes_ScalarProduct = {1000, 5000, 10000, 20000};
    std::vector<int> sizes_SubMul = {1000, 5000, 10000, 20000};

    // Benchmark du produit matriciel
    RunBenchmark("benchmark_MatrixMultiplication.txt", sizes_MatrixMultiplication, [](int size) {
        Matrix A(size, size), B(size, size);
        A.fill(1.5);
        B.fill(2.0);
        Matrix C = A * B;
    });

    // Benchmark du produit scalaire
    RunBenchmark("benchmark_ScalarProduct.txt", sizes_ScalarProduct, [](int size) {
        Matrix A(size, size);
        A.fill(1.5);
        double B = 4.5;
        Matrix C = A * B;
    });

    // Benchmark de sub_mul
    RunBenchmark("benchmark_SubMul.txt", sizes_SubMul, [](int size) {
        Matrix A(size, size), B(size, size);
        A.fill(1.5);
        B.fill(2.0);
        A.sub_mul(0.5, B);
    });

    std::cout << "Benchmarks completed!" << std::endl;
}

int main(){
    Benchmark();
}
