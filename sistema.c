#include <stdio.h>
#include <string.h>
#include "sistema.h"

// ───────── DADOS FIXOS ─────────
char *bairros[BAIRROS] = {
    "Anapolis","Dario Grossi","Esperanca","Esplanada",
    "Limoeiro","Nossa Senhora Aparecida","Nossa Senhora das Gracas",
    "Salatiel","Santa Cruz","Santa Zita",
    "Santo Antonio","Zacarias Cimini"
};

char *sintomasNome[SINT] = {
    "Febre","Dor de cabeca","Dor de barriga",
    "Tosse","Vomito","Diarreia",
    "Dor no corpo","Dor de garganta",
    "Coriza","Fadiga","Calafrios","Perda de olfato"
};

char *doencas[DOENCAS] = {
    "Gripe","Resfriado","Dengue","Gastroenterite",
    "COVID-19","Leptospirose","Infeccao intestinal",
    "Intoxicacao alimentar"
};

// ───────── STRUCT ─────────
typedef struct {
    char nome[50];
    char cpf[20];
    int idade;
    char telefone[20];
    int bairro;
    int sintomas[SINT];
    int doenca;
} Pessoa;

Pessoa pessoas[MAX];
int total = 0;

int contBairro[BAIRROS] = {0};
int contDoenca[DOENCAS] = {0};

// ───────── LIMPAR BUFFER ─────────
void limparBuffer() {
    while (getchar() != '\n');
}

// ───────── NOVO DIAGNÓSTICO (COM PORCENTAGEM) ─────────
void detectarDoenca(int s[], float porcentagem[], int *maisProvavel) {

    int score[DOENCAS] = {0};

    // GRIPE
    if (s[0]) score[0] += 2;
    if (s[1]) score[0] += 1;
    if (s[3]) score[0] += 2;
    if (s[7]) score[0] += 1;
    if (s[9]) score[0] += 1;
    if (s[10]) score[0] += 1;

    // RESFRIADO
    if (!s[0]) score[1] += 2;
    if (s[3]) score[1] += 1;
    if (s[7]) score[1] += 2;
    if (s[8]) score[1] += 2;

    // DENGUE
    if (s[0]) score[2] += 2;
    if (s[1]) score[2] += 2;
    if (s[6]) score[2] += 2;
    if (s[10]) score[2] += 1;

    // GASTROENTERITE
    if (s[2]) score[3] += 2;
    if (s[4]) score[3] += 2;
    if (s[5]) score[3] += 2;

    // COVID
    if (s[0]) score[4] += 1;
    if (s[3]) score[4] += 2;
    if (s[11]) score[4] += 3;
    if (s[9]) score[4] += 1;

    // LEPTOSPIROSE
    if (s[0]) score[5] += 2;
    if (s[1]) score[5] += 1;
    if (s[6]) score[5] += 2;
    if (s[4]) score[5] += 1;

    // INFECÇÃO INTESTINAL
    if (s[2]) score[6] += 2;
    if (s[5]) score[6] += 2;
    if (s[4]) score[6] += 1;

    // INTOXICAÇÃO ALIMENTAR
    if (s[2]) score[7] += 2;
    if (s[4]) score[7] += 2;
    if (!s[0]) score[7] += 1;

    int totalScore = 0;
    for (int i = 0; i < DOENCAS; i++) {
        totalScore += score[i];
    }

    if (totalScore == 0) {
        for (int i = 0; i < DOENCAS; i++)
            porcentagem[i] = 0;
        *maisProvavel = -1;
        return;
    }

    int maior = 0;
    int idx = -1;

    for (int i = 0; i < DOENCAS; i++) {
        porcentagem[i] = (score[i] * 100.0) / totalScore;

        if (score[i] > maior) {
            maior = score[i];
            idx = i;
        }
    }

    *maisProvavel = idx;
}

// ───────── SALVAR EM ARQUIVO ─────────
void salvarArquivo(Pessoa p) {
    FILE *f = fopen("dados.txt", "a");

    if (f == NULL) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }

    fprintf(f, "%s;%s;%d;%s;%d;%d\n",
        p.nome, p.cpf, p.idade,
        p.telefone, p.bairro, p.doenca);

    fclose(f);
}

// ───────── CADASTRO ─────────
void cadastrarPessoa() {

    if (total >= MAX) {
        printf("Limite de cadastros atingido!\n");
        return;
    }

    Pessoa p;

    printf("\n=== CADASTRO ===\n");

    printf("Nome: ");
    limparBuffer();
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;

    printf("CPF: ");
    fgets(p.cpf, sizeof(p.cpf), stdin);
    p.cpf[strcspn(p.cpf, "\n")] = 0;

    printf("Idade: ");
    while (scanf("%d", &p.idade) != 1) {
        printf("Idade invalida! Digite novamente: ");
        limparBuffer();
    }

    printf("Telefone: ");
    limparBuffer();
    fgets(p.telefone, sizeof(p.telefone), stdin);
    p.telefone[strcspn(p.telefone, "\n")] = 0;

    printf("\nEscolha o bairro:\n");
    for (int i = 0; i < BAIRROS; i++)
        printf("%d - %s\n", i + 1, bairros[i]);

    printf("Informe seu bairro: ");
    while (scanf("%d", &p.bairro) != 1 || p.bairro < 1 || p.bairro > BAIRROS) {
        printf("Opcao invalida! Digite novamente: ");
        limparBuffer();
    }

    p.bairro--;

    printf("\nRegistrar sintomas:\n");

    for (int i = 0; i < SINT; i++) {
        do {
            printf("%s (1=sim 0=nao): ", sintomasNome[i]);
            scanf("%d", &p.sintomas[i]);
        } while (p.sintomas[i] != 0 && p.sintomas[i] != 1);

        if (p.sintomas[i] == 1)
            contBairro[p.bairro]++;
    }

    // 🔥 NOVO DIAGNÓSTICO
    float porcentagem[DOENCAS];
    int maisProvavel;

    detectarDoenca(p.sintomas, porcentagem, &maisProvavel);

    printf("\n=== POSSIVEIS DOENCAS ===\n");

    for (int i = 0; i < DOENCAS; i++) {
        if (porcentagem[i] > 0)
            printf("%s: %.1f%%\n", doencas[i], porcentagem[i]);
    }

    if (maisProvavel != -1) {
        p.doenca = maisProvavel;
        contDoenca[maisProvavel]++;
        printf("\nDiagnostico mais provavel: %s\n", doencas[maisProvavel]);
    } else {
        p.doenca = -1;
        printf("\nDoenca nao identificada.\n");
    }

    pessoas[total++] = p;

    salvarArquivo(p);

    printf("\nCadastro salvo com sucesso!\n");
}

// ───────── BUSCAR CPF ─────────
void buscarCPF() {
    char cpf[20];

    printf("Digite o CPF: ");
    limparBuffer();
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(pessoas[i].cpf, cpf) == 0) {
            printf("\n=== DADOS ===\n");
            printf("Nome: %s\n", pessoas[i].nome);
            printf("Bairro: %s\n", bairros[pessoas[i].bairro]);

            if (pessoas[i].doenca != -1)
                printf("Doenca: %s\n", doencas[pessoas[i].doenca]);
            else
                printf("Doenca: Nao identificada\n");

            return;
        }
    }

    printf("Nao encontrado!\n");
}

// ───────── ESTATISTICAS ─────────
void estatisticas() {
    printf("\n=== ESTATISTICAS ===\n");

    printf("\nPor bairro:\n");
    for (int i = 0; i < BAIRROS; i++)
        printf("%s: %d sintomas\n", bairros[i], contBairro[i]);

    printf("\nDoencas:\n");
    for (int i = 0; i < DOENCAS; i++)
        printf("%s: %d casos\n", doencas[i], contDoenca[i]);
}

// ───────── ALERTAS ─────────
void alertas() {
    printf("\n=== ALERTAS ===\n");

    int encontrou = 0;

    for (int i = 0; i < BAIRROS; i++) {
        if (contBairro[i] > 10) {
            printf("Cuidado! ALERTA EM %s (%d sintomas)\n",
                   bairros[i], contBairro[i]);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum alerta ativo.\n");
}

// ───────── MENU ─────────
void menu() {
    int op;

    do {
        printf("\n=== EPIMONITOR ===\n");
        printf("1 - Cadastrar pessoa\n");
        printf("2 - Ver estatisticas\n");
        printf("3 - Ver alertas\n");
        printf("4 - Buscar por CPF\n");
        printf("5 - Sair\n");

        printf("Escolha: ");

        if (scanf("%d", &op) != 1) {
            printf("Entrada invalida!\n");
            limparBuffer();
            continue;
        }

        switch(op) {
            case 1: cadastrarPessoa(); break;
            case 2: estatisticas(); break;
            case 3: alertas(); break;
            case 4: buscarCPF(); break;
            case 5: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (op != 5);
}