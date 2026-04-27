# 🩺 EPIMONITOR

Sistema simples de monitoramento de sintomas e possíveis doenças por bairro, desenvolvido em linguagem C.

## 📌 Objetivo

O EPIMONITOR foi criado com a proposta de simular um sistema básico de vigilância epidemiológica, permitindo registrar sintomas de pessoas e identificar possíveis doenças com base nesses dados.
Além disso, o sistema acompanha a situação de cada bairro, podendo gerar alertas quando há muitos casos.

---

## ⚙️ Funcionalidades

* Cadastro de pessoas com:

  * Nome
  * CPF
  * Idade
  * Telefone
  * Bairro

* Registro de sintomas:

  * Febre
  * Dor de cabeça
  * Dor de barriga
  * Tosse
  * Vômito
  * Diarreia
  * Dor no corpo
  * Dor de garganta
  * Coriza
  * Fadiga
  * Calafrios
  * Perda de olfato

* Diagnóstico inteligente:

  * O sistema analisa os sintomas informados
  * Calcula uma **porcentagem de chance** para cada doença
  * Indica a doença mais provável

* Doenças analisadas:

  * Gripe
  * Resfriado
  * Dengue
  * Gastroenterite
  * COVID-19
  * Leptospirose
  * Infecção intestinal
  * Intoxicação alimentar

---

## 📊 Estatísticas

O sistema gera:

* Quantidade de sintomas por bairro
* Ranking de doenças mais registradas

Exemplo:

```
1º COVID-19 (10 casos)
2º Gripe (7 casos)
```

---

## 🚨 Sistema de Alertas

Os bairros entram em alerta conforme o número de sintomas registrados:

* ⚠ Moderado → 10+ sintomas
* 🚨 Alto → 20+ sintomas
* 🔥 Crítico → 30+ sintomas

---

## 💾 Armazenamento de Dados

Os dados são salvos automaticamente no arquivo:

```
dados.txt
```

Cada registro contém:

* Informações da pessoa
* Bairro
* Doença detectada
* Sintomas informados

### 🔄 Persistência

Ao iniciar o programa, os dados são carregados automaticamente do arquivo, evitando perda de informações.

---

## 🔒 Validação

* O sistema **não permite CPF duplicado**
* Valida entradas inválidas (ex: idade, opções)

---

## ▶️ Como executar

### Compilar:

```
gcc main.c sistema.c -o sistema
```

### Executar:

```
./sistema
```

(No Windows:)

```
sistema.exe
```

---

## 📁 Estrutura do Projeto

```
📦 epimonitor
 ┣ 📄 main.c
 ┣ 📄 sistema.c
 ┣ 📄 sistema.h
 ┣ 📄 dados.txt
 ┗ 📄 README.md
```

---

## 🧠 Lógica do Sistema

O diagnóstico funciona com base em um sistema de pontuação:

* Cada sintoma contribui com pontos para determinadas doenças
* A soma dos pontos gera uma porcentagem
* A doença com maior pontuação é considerada a mais provável

---

## 🚀 Melhorias Implementadas

Durante o desenvolvimento, foram adicionadas melhorias importantes:

* ✔ Salvamento completo dos sintomas
* ✔ Carregamento automático dos dados
* ✔ Bloqueio de CPF duplicado
* ✔ Sistema de diagnóstico com porcentagem
* ✔ Ranking de doenças
* ✔ Sistema de alertas com níveis

---

## 📚 Considerações

Este projeto foi desenvolvido com fins acadêmicos, com foco em:

* prática da linguagem C
* manipulação de arquivos
* uso de estruturas (struct)
* lógica de programação

Apesar de simples, ele representa uma base para sistemas maiores na área de saúde e análise de dados.

---

## 👨‍💻 Autor

Projeto desenvolvido por estudante de Ciência da Computação.

---

## ⚠️ Observação

Este sistema **não substitui diagnóstico médico real**.
Os resultados são apenas simulações baseadas em lógica simples.

---
