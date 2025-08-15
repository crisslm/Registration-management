# 📋 Sistema de Gerenciamento de Registros

**Linguagens:** C & Python 🐍  
**Status:** 🚀 Em desenvolvimento / Pronto para uso  

---

## 📖 Sobre o Projeto
Este sistema foi desenvolvido para **gerenciar registros de forma eficiente** utilizando a robustez da linguagem **C** para manipulação e armazenamento de dados, junto com a versatilidade do **Python** para **enviar notificações automáticas aos clientes** quando um serviço é finalizado.

Com ele, você pode:
- 📂 Criar, gerenciar e excluir registros/pedidos.
- 🔍 Buscar informações de forma rápida.
- 📢 Notificar automaticamente o cliente sobre o status do serviço.

---

## 🛠️ Funcionalidades
- **Gerenciamento em C**:
  - Adicionar, remover e atualizar registros.
  - Armazenamento otimizado em arquivo.
- **Integração em Python**:
  - Envio de notificações (Mensagem de aviso ao **whatsapp** do cliente).

---

## 📂 Estrutura do Projeto

/src
├── main.c # Código principal em C
├── registros.c # Módulo de gerenciamento
/python
├── notify.py # Script para notificação
README.md

---

## 🚀 Como Executar

### 1️⃣ Compilar o sistema em C
```bash
gcc src/main.c src/registros.c -o sistema

2️⃣ Executar o sistema
./sistema

⚙️ Requisitos

Para C: 
-GCC ou outro compilador compatível.

Para Python:
-Python 3.x
Bibliotecas necessárias (requirements.txt).

📌 Próximos Passos

 -Adicionar interface gráfica.

 -Melhorar sistema de logs.

 -Suporte a múltiplos idiomas.

 💡 Desenvolvido com dedicação para facilitar o gerenciamento de serviços e melhorar a comunicação com o cliente.

