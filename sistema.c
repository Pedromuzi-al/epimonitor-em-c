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

void removerQuebrasLinha(char texto[]) {
    texto[strcspn(texto, "\r\n")] = '\0';
}

// ───────── CPF DUPLICADO ─────────
int cpfExiste(char cpf[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(pessoas[i].cpf, cpf) == 0)
            return 1;
    }
    return 0;
}

// ───────── VALIDAÇÃO DE CPF ─────────
int validarCPF(const char *cpf) {
    int soma = 0, resto, i;

    if (strlen(cpf) != 11) return 0;

    for (i = 0; i < 9; i++)
        soma += (cpf[i] - '0') * (10 - i);

    resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) resto = 0;
    if (resto != (cpf[9] - '0')) return 0;

    soma = 0;
    for (i = 0; i < 10; i++)
        soma += (cpf[i] - '0') * (11 - i);

    resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) resto = 0;

    return resto == (cpf[10] - '0');
}

// ───────── VALIDAÇÃO DE NOME ─────────
int validarNome(const char *nome) {
    return strlen(nome) > 0;
}

// ───────── VALIDAÇÃO DE TELEFONE ─────────
int validarTelefone(const char *telefone) {
    if (strlen(telefone) < 10 || strlen(telefone) > 15) return 0;
    for (int i = 0; telefone[i] != '\0'; i++) {
        if (telefone[i] < '0' || telefone[i] > '9') return 0;
    }
    return 1;
}

// ───────── SALVAR COM SINTOMAS ─────────
void salvarArquivo(Pessoa p) {
    FILE *f = fopen("dados.txt", "a");

    if (!f) return;

    removerQuebrasLinha(p.nome);
    removerQuebrasLinha(p.cpf);
    removerQuebrasLinha(p.telefone);

    fprintf(f, "%s;%s;%d;%s;%d;%d;",
        p.nome, p.cpf, p.idade,
        p.telefone, p.bairro, p.doenca);

    for (int i = 0; i < SINT; i++)
        fprintf(f, "%d", p.sintomas[i]);

    fprintf(f, "\n");

    fclose(f);
}

// ───────── CARREGAR ARQUIVO ─────────
void carregarArquivo() {
    FILE *f = fopen("dados.txt", "r");
    if (!f) return;

    while (1) {
        Pessoa p;

        if (fscanf(f, " %49[^;];%19[^;];%d;%19[^;];%d;%d;",
            p.nome, p.cpf, &p.idade,
            p.telefone, &p.bairro, &p.doenca) != 6)
            break;

        removerQuebrasLinha(p.nome);
        removerQuebrasLinha(p.cpf);
        removerQuebrasLinha(p.telefone);

        char s[50];
        fscanf(f, "%49s", s);

        for (int i = 0; i < SINT; i++) {
            p.sintomas[i] = s[i] - '0';

            if (p.sintomas[i])
                contBairro[p.bairro]++;
        }

        if (p.doenca != -1)
            contDoenca[p.doenca]++;

        pessoas[total++] = p;
    }

    fclose(f);
}

// ───────── SEU DIAGNÓSTICO COM PORCENTAGEM ─────────
void detectarDoenca(int s[], float porcentagem[], int *maisProvavel) {

    int score[DOENCAS] = {0};

    if (s[0]) score[0]+=2;
    if (s[3]) score[0]+=2;
    if (s[9]) score[0]+=1;

    if (!s[0]) score[1]+=2;
    if (s[8]) score[1]+=2;

    if (s[0] && s[1]) score[2]+=3;

    if (s[2] && s[5]) score[3]+=3;

    if (s[11]) score[4]+=3;

    if (s[6]) score[5]+=2;

    if (s[2] && s[5]) score[6]+=2;

    if (s[2] && s[4]) score[7]+=2;

    int totalScore = 0;
    for (int i = 0; i < DOENCAS; i++)
        totalScore += score[i];

    int maior = 0, idx = -1;

    for (int i = 0; i < DOENCAS; i++) {
        porcentagem[i] = totalScore ? (score[i]*100.0)/totalScore : 0;

        if (score[i] > maior) {
            maior = score[i];
            idx = i;
        }
    }

    *maisProvavel = idx;
}

// ───────── CADASTRO (ATUALIZADO) ─────────
void cadastrarPessoa() {
    if (total >= MAX) {
        printf("Limite atingido!\n");
        return;
    }

    Pessoa p;

    printf("\n=== CADASTRO ===\n");

    do {
        printf("Nome: ");
        limparBuffer();
        fgets(p.nome, 50, stdin);
        p.nome[strcspn(p.nome, "\n")] = 0;

        if (!validarNome(p.nome)) {
            printf("Nome invalido! Tente novamente.\n");
        }
    } while (!validarNome(p.nome));

    do {
        printf("CPF (somente numeros): ");
        fgets(p.cpf, 20, stdin);
        p.cpf[strcspn(p.cpf, "\n")] = 0;

        if (!validarCPF(p.cpf)) {
            printf("CPF invalido! Tente novamente.\n");
        } else if (cpfExiste(p.cpf)) {
            printf("CPF ja cadastrado!\n");
            return;
        }
    } while (!validarCPF(p.cpf));

    printf("Idade: ");
    scanf("%d", &p.idade);

    do {
        printf("Telefone: ");
        limparBuffer();
        fgets(p.telefone, 20, stdin);
        p.telefone[strcspn(p.telefone, "\n")] = 0;

        if (!validarTelefone(p.telefone)) {
            printf("Telefone invalido! Tente novamente.\n");
        }
    } while (!validarTelefone(p.telefone));

    printf("\nInforme seu bairro:\n");
    for (int i = 0; i < BAIRROS; i++)
        printf("%d - %s\n", i + 1, bairros[i]);

    scanf("%d", &p.bairro);
    p.bairro--;

    printf("\nSintomas:\n");
    for (int i = 0; i < SINT; i++) {
        printf("%s (1/0): ", sintomasNome[i]);
        scanf("%d", &p.sintomas[i]);

        if (p.sintomas[i])
            contBairro[p.bairro]++;
    }

    float porcentagem[DOENCAS];
    int mais;
    detectarDoenca(p.sintomas, porcentagem, &mais);

    printf("\n=== POSSIVEIS DOENCAS ===\n");
    for (int i = 0; i < DOENCAS; i++)
        if (porcentagem[i] > 0)
            printf("%s: %.1f%%\n", doencas[i], porcentagem[i]);

    p.doenca = mais;

    if (mais != -1) {
        contDoenca[mais]++;
        printf("Mais provavel: %s\n", doencas[mais]);
    }

    pessoas[total++] = p;
    salvarArquivo(p);

    printf("Salvo!\n");
}

// ───────── ESTATISTICAS COM RANKING ─────────
void estatisticas() {

    printf("\n=== BAIRROS ===\n");

    for(int i=0;i<BAIRROS;i++)
        printf("%s: %d\n",bairros[i],contBairro[i]);

    printf("\n=== RANKING DOENCAS ===\n");

    for(int i=0;i<DOENCAS;i++){
        for(int j=i+1;j<DOENCAS;j++){
            if(contDoenca[j]>contDoenca[i]){
                int t=contDoenca[i];
                contDoenca[i]=contDoenca[j];
                contDoenca[j]=t;

                char *n=doencas[i];
                doencas[i]=doencas[j];
                doencas[j]=n;
            }
        }
    }

    for(int i=0;i<DOENCAS;i++)
        printf("%dº %s (%d)\n", i + 1, doencas[i], contDoenca[i]);
}

// ───────── ALERTAS COM NÍVEL ─────────
void alertas() {

    printf("\n=== ALERTAS ===\n");

    for(int i=0;i<BAIRROS;i++){

        if(contBairro[i]>=30)
            printf("🔥 CRITICO: %s\n",bairros[i]);

        else if(contBairro[i]>=20)
            printf("🚨 ALTO: %s\n",bairros[i]);

        else if(contBairro[i]>=10)
            printf("⚠ MODERADO: %s\n",bairros[i]);
    }
}

// ───────── EXIBIR CADASTROS (CORRIGIDO) ─────────
void exibirCadastros() {
    if (total == 0) {
        printf("\nNenhuma pessoa cadastrada.\n");
        return;
    }

    printf("\n=== LISTA DE CADASTROS ===\n");
    for (int i = 0; i < total; i++) {
        printf("\nPessoa %d:\n", i + 1);
        printf("Nome: %s\n", pessoas[i].nome);
        printf("CPF: %s\n", pessoas[i].cpf);
        printf("Idade: %d\n", pessoas[i].idade);
        printf("Telefone: %s\n", pessoas[i].telefone);
        printf("Bairro: %s\n", bairros[pessoas[i].bairro]);
        printf("Doenca mais provavel: %s\n", pessoas[i].doenca != -1 ? doencas[pessoas[i].doenca] : "Nenhuma");
        printf("Sintomas:\n");
        int hasSintomas = 0;
        for (int j = 0; j < SINT; j++) {
            if (pessoas[i].sintomas[j]) {
                printf("- %s\n", sintomasNome[j]);
                hasSintomas = 1;
            }
        }
        if (!hasSintomas) {
            printf("- Nenhum\n");
        }
        printf("-----------------------------\n");
    }
}

// ───────── MENU ─────────
void menu() {
    int op;

    do {
        printf("\n=== EPIMONITOR ===\n");
        printf("\n1-Cadastrar\n2-Estatisticas\n3-Alertas\n4-Ver Cadastros\n5-Sair\n");
        scanf("%d", &op);

        switch(op){
            case 1: cadastrarPessoa(); printf("\n-----------------------------\n"); break;
            case 2: estatisticas(); printf("\n-----------------------------\n"); break;
            case 3: alertas(); printf("\n-----------------------------\n"); break;
            case 4: exibirCadastros(); printf("\n-----------------------------\n"); break;
        }

    } while(op!=5);

    printf("\n-----------------------------\n");
}
