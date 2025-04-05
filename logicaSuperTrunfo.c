#include <stdio.h>
#include <string.h>

#define NUM_ATRIBUTOS 5
#define NUM_CARTAS 3

typedef struct {
    char nome[30];
    int populacao;
    int area;
    int pib;
    int expectativa_vida;
    int densidade_demografica;
} Carta;

// Função para exibir os atributos disponíveis
void mostrar_opcoes(int ignorar) {
    printf("Escolha um atributo:\n");
    if (ignorar != 1) printf("1 - População\n");
    if (ignorar != 2) printf("2 - Área\n");
    if (ignorar != 3) printf("3 - PIB\n");
    if (ignorar != 4) printf("4 - Expectativa de Vida\n");
    if (ignorar != 5) printf("5 - Densidade Demográfica\n");
}

// Função para obter valor do atributo
int obter_valor(Carta c, int atributo) {
    switch (atributo) {
        case 1: return c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return c.expectativa_vida;
        case 5: return c.densidade_demografica;
        default: return 0;
    }
}

// Nome do atributo para exibição
const char* nome_atributo(int atributo) {
    switch (atributo) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Expectativa de Vida";
        case 5: return "Densidade Demográfica";
        default: return "Desconhecido";
    }
}

// Compara valores individuais (leva em conta exceção da densidade demográfica)
int comparar(int valor1, int valor2, int atributo) {
    if (atributo == 5) // Densidade: menor é melhor
        return (valor1 < valor2) ? 1 : (valor2 < valor1) ? 2 : 0;
    else
        return (valor1 > valor2) ? 1 : (valor2 > valor1) ? 2 : 0;
}

int main() {
    Carta cartas[NUM_CARTAS] = {
        {"Brasil", 213000000, 8516000, 5000, 76, 330},
        {"Japão", 125000000, 378000, 5000, 84, 330},
        {"Canadá", 38000000, 9985000, 1700, 82, 4}
    };

    int carta1 = 0, carta2 = 1;
    int atributo1 = 0, atributo2 = 0;

    printf("Cartas disponíveis:\n");
    for (int i = 0; i < NUM_CARTAS; i++) {
        printf("%d - %s\n", i + 1, cartas[i].nome);
    }

    printf("\nEscolha a primeira carta (1-%d): ", NUM_CARTAS);
    scanf("%d", &carta1);
    printf("Escolha a segunda carta (1-%d): ", NUM_CARTAS);
    scanf("%d", &carta2);
    carta1--; carta2--;

    if (carta1 == carta2 || carta1 < 0 || carta1 >= NUM_CARTAS || carta2 < 0 || carta2 >= NUM_CARTAS) {
        printf("Seleção inválida de cartas.\n");
        return 1;
    }

    // Escolha do primeiro atributo
    do {
        mostrar_opcoes(0);
        printf("Escolha o primeiro atributo: ");
        scanf("%d", &atributo1);
    } while (atributo1 < 1 || atributo1 > 5);

    // Escolha do segundo atributo (não pode repetir)
    do {
        mostrar_opcoes(atributo1);
        printf("Escolha o segundo atributo: ");
        scanf("%d", &atributo2);
        if (atributo2 == atributo1)
            printf("Você já escolheu esse atributo. Escolha outro.\n");
    } while (atributo2 < 1 || atributo2 > 5 || atributo2 == atributo1);

    int valor1_attr1 = obter_valor(cartas[carta1], atributo1);
    int valor2_attr1 = obter_valor(cartas[carta2], atributo1);
    int valor1_attr2 = obter_valor(cartas[carta1], atributo2);
    int valor2_attr2 = obter_valor(cartas[carta2], atributo2);

    int soma1 = valor1_attr1 + valor1_attr2;
    int soma2 = valor2_attr1 + valor2_attr2;

    printf("\nComparando cartas:\n");
    printf("%s vs %s\n", cartas[carta1].nome, cartas[carta2].nome);
    printf("%s: %d vs %d\n", nome_atributo(atributo1), valor1_attr1, valor2_attr1);
    printf("%s: %d vs %d\n", nome_atributo(atributo2), valor1_attr2, valor2_attr2);
    printf("Soma dos atributos: %d vs %d\n", soma1, soma2);

    if (soma1 > soma2)
        printf("Vencedor: %s\n", cartas[carta1].nome);
    else if (soma2 > soma1)
        printf("Vencedor: %s\n", cartas[carta2].nome);
    else
        printf("Empate!\n");

    return 0;
}
