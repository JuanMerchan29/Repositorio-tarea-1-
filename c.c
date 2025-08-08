//factorial_iterativo
unsigned long long factorial_iterativo(int n) {
    unsigned long long resultado = 1;
    for (int i = 1; i <= n; ++i)
        resultado *= i;
    return resultado;
}

//factorial_recursivo
unsigned long long factorial_recursivo(int n) {
    if (n <= 1)
        return 1;
    return n * factorial_recursivo(n - 1);
}

//medir
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>

unsigned long long factorial_iterativo(int n);
unsigned long long factorial_recursivo(int n);

double obtener_memoria_MB() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return (double)pmc.WorkingSetSize / (1024 * 1024);
}

double medir_tiempo(unsigned long long (*func)(int), int n, unsigned long long *resultado) {
    clock_t inicio = clock();
    *resultado = func(n);
    clock_t fin = clock();
    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

int main() {
    int valores[] = {10, 150, 400, 600, 900};
    int num_valores = sizeof(valores) / sizeof(valores[0]);

    printf("%-10s %-15s %-15s %-15s %-15s\n", "n", "Tiempo I (s)", "Memoria I (MB)", "Tiempo R (s)", "Memoria R (MB)");

    for (int i = 0; i < num_valores; i++) {
        int n = valores[i];
        unsigned long long res_i, res_r;

        // Iterativo
        double mem_i_antes = obtener_memoria_MB();
        double tiempo_i = medir_tiempo(factorial_iterativo, n, &res_i);
        double mem_i_despues = obtener_memoria_MB();

        // Recursivo
        double mem_r_antes = obtener_memoria_MB();
        double tiempo_r = medir_tiempo(factorial_recursivo, n, &res_r);
        double mem_r_despues = obtener_memoria_MB();

        printf("%-10d %-15f %-15f %-15f %-15f\n", n, tiempo_i, mem_i_despues - mem_i_antes, tiempo_r, mem_r_despues - mem_r_antes);
    }

    return 0;
}