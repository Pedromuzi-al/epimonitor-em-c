📌 Sobre o projeto

O Epimonitor em C é um sistema simples feito em linguagem C que simula um monitoramento de sintomas na população.
A ideia é coletar dados de pessoas, registrar sintomas e, com base nisso, indicar possíveis doenças e gerar alertas por bairro.

Esse tipo de sistema pode ajudar a entender como doenças podem se espalhar em uma comunidade.

⚙️ Como o sistema funciona

O programa funciona em etapas bem simples:

1️⃣ Cadastro da pessoa

O usuário informa:

Nome
CPF
Idade
Telefone
Bairro onde mora

👉 Os bairros já estão pré-definidos no sistema.

2️⃣ Registro de sintomas

Após o cadastro, o usuário pode escolher registrar sintomas.

Ele responde com:

1 → sim
0 → não

Para sintomas como:

Febre
Dor de cabeça
Dor de barriga
Tosse
Vômito
Diarreia
Dor no corpo
Dor de garganta
3️⃣ Identificação de possível doença

O sistema analisa os sintomas e tenta associar com doenças como:

Gripe
Resfriado
Dengue
Gastroenterite
COVID-19
Leptospirose
Infecção intestinal
Intoxicação alimentar

⚠️ Importante:
Isso não é um diagnóstico médico, apenas uma simulação baseada em lógica simples.

4️⃣ Estatísticas

O sistema mostra:

Quantidade de sintomas por bairro
Quantidade de casos por doença
5️⃣ Sistema de alerta

Se um bairro tiver mais de 10 sintomas registrados, ele entra em:

⚠️ ALERTA

Isso indica que pode haver um aumento de casos naquela região.

🖥️ Como executar o programa
▶️ Compilar

No terminal:

gcc *.c -o sistema
▶️ Executar
.\sistema.exe
📁 Estrutura do projeto
main.c → controla o fluxo do programa
sistema.c → contém toda a lógica
sistema.h → declara funções e constantes
🎯 Objetivo do projeto

Este projeto foi desenvolvido com o objetivo de:

Praticar programação em C
Trabalhar com estruturas (struct)
Criar um sistema organizado em múltiplos arquivos
Simular um problema real (monitoramento de saúde)
🚀 Possíveis melhorias

No futuro, o sistema pode evoluir com:

Salvamento em arquivo (banco de dados simples)
Busca por CPF
Interface gráfica
Relatórios automáticos
👨‍💻 Conclusão

O Epimonitor mostra como conceitos básicos de programação podem ser usados para criar soluções úteis no mundo real.

Mesmo sendo simples, ele já demonstra:

organização de código
uso de lógica
manipulação de dados
