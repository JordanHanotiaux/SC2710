import numpy as np
import matplotlib.pyplot as plt

# Fichiers de benchmarks
filename_opt = "Benchmark/benchmark_ScalarProduct.txt"
filename_naive = "Benchmark/benchmark_SubMul.txt"

sizes_opt = []
times_opt = []

sizes_naive = []
times_naive = []

# Lire les résultats à partir du premier fichier (optimisé)
with open(filename_opt, "r") as file:
    next(file)  # Skip header
    for line in file:
        line = line.strip()
        if line:
            try:
                size, time = map(float, line.split(","))
                sizes_opt.append(int(size))
                times_opt.append(time)
            except ValueError:
                print(f"Skipping malformed line: {line}")

# Lire les résultats à partir du second fichier (naïf)
with open(filename_naive, "r") as file:
    next(file)  # Skip header
    for line in file:
        line = line.strip()
        if line:
            try:
                size, time = map(float, line.split(","))
                sizes_naive.append(int(size))
                times_naive.append(time)
            except ValueError:
                print(f"Skipping malformed line: {line}")

# Convertir les tailles en array numpy
sizes_opt_np = np.array(sizes_opt)
sizes_naive_np = np.array(sizes_naive)

# Calcul des temps théoriques O(N^2) avec une constante d'ajustement
theoretical_times_opt = 1e-7 * sizes_opt_np**2
theoretical_times_naive = 1e-7 * sizes_naive_np**2

# Tracer les courbes
plt.figure(figsize=(8, 6))

plt.plot(sizes_opt, times_opt, 'o-', label="Scalar Product", color="blue")
plt.plot(sizes_naive, times_naive, 's-', label="Sub_Mul", color="red")

plt.plot(sizes_opt_np, theoretical_times_opt, '--', label="Theoretical $O(N^2)$", color="green")

plt.xlabel("Matrix Size")
plt.ylabel("Execution Time (s)")
plt.title("Multiplication Operations Performance")
plt.legend()
plt.grid(True)
plt.xscale("log")
plt.yscale("log")
plt.show()
