#include <stdio.h>
#include <string.h>
#include "sistema.h"

#define BAIRROS 12
#define SINT 8
#define DOENCAS 8

char *bairros[BAIRROS] = {
    "Anapolis","Dario Grossi","Esperanca","Esplanada",
    "Limoeiro","Nossa Senhora Aparecida","Nossa Senhora das Gracas",
    "Salatiel","Santa Cruz","Santa Zita",
    "Santo Antonio","Zacarias Cimini"
};

char *sintomasNome[SINT] = {
    "Febre","Dor de cabeca","Dor de barriga",
    "Tosse","Vomito","Diarreia",
    "Dor no corpo","Dor de garganta"
};

char *doencas[DOENCAS] = {
    "Gripe","Resfriado","Dengue",
    "Gastroenterite","COVID-19","Leptospirose",
    "Infeccao intestinal","Intoxicacao alimentar"
};

typedef struct {
    char nome[50];
    char cpf[20];
    int idade;
    char telefone[20];
    int bairro;
    int sintomas[SINT];
    int doencaDetectada;
} Pessoa;

Pessoa pessoas[100];
int total = 0;

int contadorBairro[BAIRROS] = {0};
int contadorDoenca[DOENCAS] = {0};

// ───────── DETECÇÃO ─────────
int detectarDoenca(int s[]) {

    if (s[0] && s[1] && s[3]) return 0;
    if (!s[0] && s[3] && s[7]) return 1;
    if (s[0] && s[1] && !s[3]) return 2;
    if (s[2] && s[4] && s[5]) return 3;
    if (s[0] && s[3] && (s[2] || s[4] || s[5])) return 4;
    if (s[0] && s[1] && s[6] && s[4]) return 5;
    if (s[2] && s[5] && s[4]) return 6;
    if (s[2] && s[4] && !s[0]) return 7;
    
    return -1;
}

// ───────── CADASTRO ─────────
void cadastrarPessoa() {

    if (total >= 100) {
        printf("Limite de cadastros atingido!\n");
        return;
    }

    Pessoa p;

    printf("\n=== CADASTRO ===\n");

    printf("Nome: ");
    scanf(" %[^\n]", p.nome);

    printf("CPF: ");
    scanf(" %[^\n]", p.cpf);

    printf("Idade: ");
    scanf("%d", &p.idade);
    while (getchar() != '\n'); // limpa buffer

    printf("Telefone: ");
    scanf(" %[^\n]", p.telefone);

    printf("\nEscolha o bairro:\n");
    for (int i = 0; i < BAIRROS; i++)
        printf("%d - %s\n", i + 1, bairros[i]);

    printf("\nInforme seu bairro: ");
    scanf("%d", &p.bairro);

    p.bairro--;

    if (p.bairro < 0 || p.bairro >= BAIRROS) {
        printf("Bairro invalido!\n");
        return;
    }

    pessoas[total] = p;
    total++;

    printf("\nCadastro realizado!\n");

    int escolha;

    printf("\n1 - Registrar sintomas\n");
    printf("2 - Voltar ao menu\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        registrarSintomas(total - 1);
    }
}

// ───────── SINTOMAS ─────────
void registrarSintomas(int index) {

    printf("\n=== SINTOMAS ===\n");

    for (int i = 0; i < SINT; i++) {
        do {
            printf("%s (1=sim 0=nao): ", sintomasNome[i]);
            scanf("%d", &pessoas[index].sintomas[i]);
        } while (pessoas[index].sintomas[i] != 0 &&
                 pessoas[index].sintomas[i] != 1);

        if (pessoas[index].sintomas[i] == 1) {
            contadorBairro[pessoas[index].bairro]++;
        }
    }

    int d = detectarDoenca(pessoas[index].sintomas);
    pessoas[index].doencaDetectada = d;

    if (d != -1) {
        contadorDoenca[d]++;
        printf("\nPossivel diagnostico: %s\n", doencas[d]);
    } else {
        printf("\nDoenca nao identificada.\n");
    }
}

// ───────── ESTATISTICAS ─────────
void estatisticas() {
    printf("\n=== ESTATISTICAS ===\n");

    printf("\nPor bairro:\n");
    for (int i = 0; i < BAIRROS; i++) {
        printf("%s: %d sintomas\n", bairros[i], contadorBairro[i]);
    }

    printf("\nDoencas:\n");
    for (int i = 0; i < DOENCAS; i++) {
        printf("%s: %d casos\n", doencas[i], contadorDoenca[i]);
    }
}

// ───────── ALERTAS ─────────
void alertas() {
    printf("\n=== ALERTAS ===\n");

    int encontrou = 0;

    for (int i = 0; i < BAIRROS; i++) {
        if (contadorBairro[i] > 10) {
            printf("⚠ ALERTA EM %s (%d sintomas)\n",
                   bairros[i],
                   contadorBairro[i]);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum alerta ativo.\n");
}

// ───────── MENU ─────────
void menu() {
    int opcao;

    do {
        printf("\n=== EPIMONITOR ===\n");
        printf("1 - Cadastrar pessoa\n");
        printf("2 - Ver estatisticas\n");
        printf("3 - Ver alertas\n");
        printf("4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarPessoa(); break;
            case 2: estatisticas(); break;
            case 3: alertas(); break;
            case 4: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (opcao != 4);
}