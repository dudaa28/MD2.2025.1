#include <stdio.h>

// Apresentando primeiro Protótipos das funções:

int verificar_coprimalidade(int a, int b);
int encontrar_inverso(int G, int n);
int testar_primalidade(int num);
int calcular_fun_euler(int n);
int potencia_mod(int base, int exp, int mod);
void executar_verificacao(int H, int G, int n, int x, int n1);

int main() {
    int H, G, n, x, n1; // Variáeis de Entrada 

    /* - três números inteiros positivos H, G e n, usados para calcular a base a
        - um expoente x
        - um módulo n1*/
    
    printf("Calculadora de Verificação Modular\n");
    printf("Formato: a = H⊘G em Zn, depois a^x mod n1\n");
    printf("Digite H G n (separados por espaço): ");
    scanf("%d %d %d", &H, &G, &n);
    printf("Digite x e n1 (separados por espaço): ");
    scanf("%d %d", &x, &n1);
    
    executar_verificacao(H, G, n, x, n1);
    
    return 0;
}

// Implementação das funções

int verificar_coprimalidade(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return (a == 1);
}


int encontrar_inverso(int G, int n) {
    for (int x = 1; x < n; x++) {
        if ((G * x) % n == 1) {
            return x;
        }
    }
    return -1;
}

int testar_primalidade(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int calcular_fun_euler(int n) {
    int res = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

int potencia_mod(int base, int exp, int mod) {
    int res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

/* --- 01. Verificar se G e n são primos utilizando o Algoritmo de Euclides
            (se não forem, justificar que a divisão não é possível)*/

void executar_verificacao(int H, int G, int n, int x, int n1) {
    printf("\n--- Etapa 1: Verificação Inicial ---\n");
    if (!verificar_coprimalidade(G, n)) {
        printf("Erro: %d e %d não são coprimos. Divisão impossível.\n", G, n);
        return;
    }
    printf("%d e %d são coprimos (MDC = 1)\n", G, n);

/* --- 02. Calcular o inverso de G em Zn utilizando divisões sucessivas
            (se G−1 não pertencer a Zn verificar equivalência)*/

    printf("\n--- Etapa 2: Cálculo do Inverso ---\n");
    int inv = encontrar_inverso(G, n);
    if (inv == -1) {
        printf("Inverso de %d em Z%d não existe\n", G, n);
        return;
    }
    printf("Inverso de %d em Z%d = %d\n", G, n, inv);

/* --- 03. Dividir H por G e encontrar a */

    printf("\n--- Etapa 3: Base da Operação ---\n");
    int a = (H * inv) % n;
    printf("a = (%d * %d) mod %d = %d\n", H, inv, n, a);

/* --- 04. Verificar se a e n1 são coprimos */

    printf("\n--- Etapa 4: Verificação Final ---\n");
    if (!verificar_coprimalidade(a, n1)) {
        printf("Aviso: %d e %d não são coprimos\n", a, n1);
    } else {
        printf("%d e %d são coprimos\n", a, n1);
    }

/* --- 05. 5. Verificar se n1 é primo */

    printf("\n--- Etapa 5: Preparação do Expoente ---\n");
    int x1;
    if (testar_primalidade(n1)) {
        printf("%d é primo (Fermat)\n", n1);
        x1 = n1 - 1;
    } else {
        printf("%d não é primo (Euler)\n", n1);
        x1 = calcular_fun_euler(n1);
        printf("φ(%d) = %d\n", n1, x1);
    }

/* --- 06. Se n1 for primo, aplicar o Pequeno Teorema de Fermat, e definir x₁=n −1*/

    printf("\n--- Etapa 6: Decomposição ---\n");
    int q = x / x1;
    int r = x % x1;
    printf("%d = %d*%d + %d\n", x, x1, q, r);

    printf("\n--- Etapa 7: Cálculo Modular ---\n");
    int passo1 = potencia_mod(a, x1, n1);
    printf("1) %d^%d mod %d = %d\n", a, x1, n1, passo1);
    
    int passo2 = potencia_mod(passo1, q, n1);
    printf("2) (%d)^%d mod %d = %d\n", passo1, q, n1, passo2);
    
    int passo3 = potencia_mod(a, r, n1);
    printf("3) %d^%d mod %d = %d\n", a, r, n1, passo3);

    printf("\n--- Resultado Final ---\n");
    int resultado = (passo2 * passo3) % n1;
    printf("(%d * %d) mod %d = %d\n", passo2, passo3, n1, resultado);
}