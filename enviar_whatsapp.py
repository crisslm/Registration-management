import pywhatkit
import sys
import pywhatkit
import datetime

def enviar_notificacao():
    # Verifica se os argumentos necessários foram passados
    if len(sys.argv) != 4:
        print("Erro: Uso incorreto. Forneca o telefone, nome do cliente e o servico.")
        # Exemplo: python enviar_whatsapp.py "+5511999998888" "Maria" "Manutencao"
        sys.exit(1) # Sai do script com um código de erro

    # Pega os argumentos da linha de comando
    telefone_cliente = sys.argv[1]
    nome_cliente = sys.argv[2]
    servico_realizado = sys.argv[3]

    # Cria a mensagem personalizada
    mensagem = f"Olá, {nome_cliente}! Temos uma ótima notícia da nossa sapataria! O seu serviço '{servico_realizado}' foi finalizado e seu pedido já está pronto para ser retirado! Agradecemos a preferência!"

    try:
        print(f"Preparando para enviar mensagem para {nome_cliente} no número {telefone_cliente}...")
        
        # Função principal que envia a mensagem instantaneamente
        pywhatkit.sendwhatmsg_instantly(
            phone_no=telefone_cliente,
            message=mensagem,
            wait_time=30,  # Tempo em segundos para o WhatsApp Web abrir e carregar
            tab_close=True # Fecha a aba do navegador após enviar
        )
        print("Mensagem enviada com sucesso!")

    except Exception as e:
        print(f"Ocorreu um erro ao tentar enviar a mensagem: {e}")

# Ponto de entrada do script
if __name__ == "__main__":
    enviar_notificacao()