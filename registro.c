#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#define MAX 1000
#define NOME_ARQUIVO "registro.dat"


typedef struct DaTa{
    int dia;
    int mes;
    int ano;
}dataT;

//Struct para coletar os dados do registro
typedef struct registro{   
    int codigo;
    dataT data; 
    char nome[30]; 
    char servico[50]; 
    char telefone[20];
    char cpf[15];
    float preco;
}RegistroT;

//Struct Lista sequencial, para facilitar na busca dos registros
typedef struct lista_s{
    RegistroT A[MAX]; //Vetor de structs de registro 
    int elemnum; //Numero de registros feitos
    float faturamento;
}listaseq;

//Função para incializar o numero de elementos em 0
void initialize0(listaseq *l){
    l->elemnum = 0;
    l->faturamento = 0.0f;
}

//Função que realiza a busca de um registro utilizando uma chave/codigo
int search0(listaseq *l, int ch){
    int i;
    for(i=0;i<l->elemnum;i++){
        //se o codigo do struct for igual à ao codigo que eu quero, a função retorna a posição do registro
        if(l->A[i].codigo == ch) return i; 
    }
    //Se não achar, retorna -1.
    return -1;
}

int search1(listaseq *l, char ch[]){
    int i;
    for(i=0;i<l->elemnum;i++){
        //se o codigo do struct for igual à ao codigo que eu quero, a função retorna a posição do registro
        if(strcmp(l->A[i].telefone, ch) == 0) return i; 
    }
    //Se não achar, retorna -1.
    return -1;
}

//Função que verifica se o codigo/chave do registro ja existe
bool exclusivkey(listaseq *l, int ch){
    int i;
    for(i=1;i<l->elemnum;i++){
        //Se a chave ja existir, retorna falso, mostrando que a nova chave não é exclusiva
        if(l->A[i-1].codigo == ch) return false;
    }
    //Se a chave não existir, mostra que a nova chave é exclusiva
    return true;
}

void exclude(listaseq *l, int ch){
    int posicao = search0(l, ch);
    int i;
    for(i=posicao+1;i<l->elemnum;i++){
        l->A[i-1] = l->A[i]; 
    }
    l->elemnum--;
}

void exclude2(listaseq *l, char ch[]){
    int posicao = search1(l, ch);
    int i;
    for(i=posicao+1;i<l->elemnum;i++){
        l->A[i-1] = l->A[i]; 
    }
    l->elemnum--;
}

//Função que seleciona aleatoriamente numeros entre um mínimo e máximo 
int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

void salvarDados(listaseq *l) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "wb"); // "wb" = Write Binary (Escrever em Binário)
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo para salvar os dados.\n");
        return;
    }

    // Escreve a struct 'listaseq' inteira de uma vez no arquivo.
    fwrite(l, sizeof(listaseq), 1, arquivo);

    fclose(arquivo);
}

void carregarDados(listaseq *l) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "rb"); // "rb" = Read Binary (Ler em Binário)

    // Se o arquivo não existe, apenas inicializa uma lista vazia.
    if (arquivo == NULL) {
        initialize0(l);
        printf("Nenhum banco de dados encontrado. Iniciando um novo registro.\n");
        return;
    }

    // Lê a struct 'listaseq' inteira do arquivo para a nossa variável.
    fread(l, sizeof(listaseq), 1, arquivo);

    fclose(arquivo);
    printf("Dados carregados com sucesso! %d registros encontrados.\n", l->elemnum);
}

//Main, onde o programa é executado
int main(){
    listaseq a;
    int opcao, opcao2, opcao3, lista, chave;
    char chave1[20];

    carregarDados(&a);

    //loop que mantem opções de ações abertas até o usuário sair do programa, selecionando 4. 
    do{
        printf("\n------------------------------\n");
        printf("Acoes disponiveis: \n");
        printf("(1)Buscar pedido por codigo.\n");
        printf("(2)Buscar pedido por telefone.\n");
        printf("(3)Vizualizar pedidos feitos\n");
        printf("(4)Realizar Novo Pedido.\n");
        printf("(5)Relatorio/estisticas.\n");
        printf("(6)Sair do sistema.\n");
        printf("Digite aqui: ");
        scanf("%d",&opcao);
        printf("--------------------------------\n");
        //Switch que define as ações das opções e executa a ação desejada pelo usuário 
        switch(opcao){
            case 1:
               //Caso o usuário tente buscar um registro e ainda não houver, o programa informa ao usuário
               if(a.elemnum == 0){
                printf("Nao ha Pedidos!");
                break; //finaliza a ação do switch
               }
               printf("Insira o codigo unico do cliente: ");
               scanf("%d",&chave);
               //Ao receber a chave, ela é inserida na função search, que retorna a posição do registro.
               lista = search0(&a, chave);
               //Se a chave foi encontrada, ele coloca na tela as informações do registro desejado
               if(!(lista == -1)){
                   printf("Data de entrega: %d/%d/%d",a.A[lista].data.dia,a.A[lista].data.mes,a.A[lista].data.ano);
                   printf("\nNome: %s\n", a.A[lista].nome);
                   printf("Servico: %s\n", a.A[lista].servico);
                   printf("Telefone: %s\n", a.A[lista].telefone);
                   printf("CPF: %s\n", a.A[lista].cpf);
                   printf("Preco: %.2f\n", a.A[lista].preco);
                   printf("\nO que deseja fazer com esse pedido?\n");
                   do{
                       printf("(0) Voltar ao menu principal.\n");
                       printf("(1) Excluir pedido.\n");
                       printf("(2) Finalizar servico e notificar cliente por WhatsApp.\n"); // <-- NOSSA NOVA OPÇÃO
                       printf("Insira aqui: ");
                       scanf("%d",&opcao2);
                       getchar();
                       switch(opcao2){
                           case 0: break;
                           break;
                           case 1:
                                exclude(&a, chave);
                                printf("\nPedido excluido com sucesso!");
                           break;
                           case 2:
                                { // Usamos chaves para criar um escopo local para a variável 'comando'
                                 char comando[300]; // String para montar nosso comando
                        
                                 // Monta o comando que será executado no terminal
                                 // Exemplo: python enviar_whatsapp.py "+5511999998888" "Maria" "Troca de Tela"
                                 sprintf(comando, "python enviar_whatsapp.py \"%s\" \"%s\" \"%s\"", 
                                     a.A[lista].telefone, 
                                     a.A[lista].nome, 
                                     a.A[lista].servico);
                        
                                 printf("\nExecutando automacao para notificar o cliente...\n");
                                 system(comando); // Executa o comando!
                                 printf("\nAutomacao finalizada.\n");
                                 opcao2 = 0; // Força a saída do loop
                                }

                           break;
                           default: printf("Opcao invalida!");
                           break;
                        }
                   } while(!(opcao2 == 0 || 1));
                   salvarDados(&a);
               }
               //Se o retorno de search0 for -1, retorna que a lista não foi encontrada
               else printf("Codigo nao encontrado.");
            break;
            case 2:
                //Caso o usuário tente buscar um registro e ainda não houver, o programa informa ao usuário
               if(a.elemnum == 0){
                printf("Nao ha Pedidos!");
                break; //finaliza a ação do switch
               }
               printf("Insira o telefone do cliente: ");
               scanf("%s", chave1);
               //Ao receber o numero, ela é inserida na função search, que retorna a posição do registro.
               lista = search1(&a, chave1);
               //Se a chave foi encontrada, ele coloca na tela as informações do registro desejado
               if(!(lista == -1)){
                   printf("Data de entrega: %d/%d/%d",a.A[lista].data.dia,a.A[lista].data.mes,a.A[lista].data.ano);
                   printf("\nNome: %s\n", a.A[lista].nome);
                   printf("Servico: %s\n", a.A[lista].servico);
                   printf("Telefone: %s\n", a.A[lista].telefone);
                   printf("CPF: %s\n", a.A[lista].cpf);
                   printf("Preco: %.2f\n", a.A[lista].preco);
                   printf("\nO que deseja fazer com esse pedido?\n");
                   do{
                       printf("(0) Voltar ao menu principal.\n");
                       printf("(1) Excluir pedido.\n");
                       printf("(2) Finalizar servico e notificar cliente por WhatsApp.\n"); // <-- NOSSA NOVA OPÇÃO
                       printf("Insira aqui: ");
                       scanf("%d",&opcao2);
                       getchar();
                       switch(opcao2){
                           case 0: break;
                           break;
                           case 1:
                                exclude2(&a, chave1);
                                printf("\nPedido excluido com sucesso!");
                           break;
                           case 2:
                                { // Usamos chaves para criar um escopo local para a variável 'comando'
                                 char comando[300]; // String para montar nosso comando
                        
                                 // Monta o comando que será executado no terminal
                                 // Exemplo: python enviar_whatsapp.py "+5511999998888" "Maria" "Troca de Tela"
                                 sprintf(comando, "python enviar_whatsapp.py \"%s\" \"%s\" \"%s\"", 
                                     a.A[lista].telefone, 
                                     a.A[lista].nome, 
                                     a.A[lista].servico);
                        
                                 printf("\nExecutando automacao para notificar o cliente...\n");
                                 system(comando); // Executa o comando!
                                 printf("\nAutomacao finalizada.\n");
                                 opcao2 = 0; // Força a saída do loop
                                }

                           break;
                           default: printf("Opcao invalida!");
                           break;
                        }
                   } while(!(opcao2 == 0 || 1));
                   salvarDados(&a);
               }
                

            break;

            case 3:
                if(a.elemnum == 0){
                printf("Nao ha Pedidos!");
                }
                else{
                    for(int j=0;j<a.elemnum;j++){
                        printf("\nData: %d/%d/%d",a.A[j].data.dia,a.A[j].data.mes,a.A[j].data.ano);
                        printf("\nCodigo do cliente: %d",a.A[j].codigo);
                        printf("\nNome: %s",a.A[j].nome);
                        printf("\nServico: %s",a.A[j].servico);
                        printf("\nTelefone: %s",a.A[j].telefone);
                        printf("\n");                       
                    }
                }
            break;

            case 4:
               //Função que reliza a seleção aleatoria de um numero entre 1 a 9999, que sera o codigo a ser utilizado
               srand(time(NULL));
               int num = random_int(1000, 9999);
               //Este while é utilizado para evitar que dois códigos iguais sejam aplicados em registros diferentes 
               while(exclusivkey(&a, num) == false){
                   num = random_int(0, 9999); //Se o codigo gerado existir, ele gera um novo, ate que novo seja diferente dos existentes
               }
               printf("Codigo do cliente: %d\n",num);
               a.A[a.elemnum].codigo = num; //Salva o codigo do registro no struct registro
               printf("Data de entrega: ");
               scanf("%d%d%d",&a.A[a.elemnum].data.dia,&a.A[a.elemnum].data.mes,&a.A[a.elemnum].data.ano);
               printf("Nome do cliente: ");
               scanf(" %99[^\n]", a.A[a.elemnum].nome);
               printf("Servico: ");
               scanf(" %99[^\n]", a.A[a.elemnum].servico);
               printf("Telefone (insira +55 e o ddd): ");
               scanf("%s", a.A[a.elemnum].telefone);
               printf("CPF: ");
               scanf("%s", a.A[a.elemnum].cpf);
               printf("Valor do servico: ");
               scanf("%f", &a.A[a.elemnum].preco);
               printf("\nPedido registrado com sucesso!\n");
               a.faturamento += a.A[a.elemnum].preco; //a cada registro ele adiciona os valores de cada serviço.
               a.elemnum++; //A cada novo registro, é adicionado 1 ao numero de elementos da lista.
               salvarDados(&a);
               printf("Dados salvos com sucesso.\n");
    
            break;
            case 5:
               //Relatório que apresenta dados atuais do sistema.
               printf("\nRegistros feitos: %d\n",a.elemnum);
               printf("\nAinda podem ser feitos %d registros.\n",1000-a.elemnum);
               printf("\nFaturamento total: R$%.2f\n",a.faturamento);
               if(a.faturamento != 0){
                   printf("Deseja reiniciar o faturamento? \n");
                   do {
                       printf("(0)Nao.\n");
                       printf("(1)Sim.\n");
                       printf("Insira aqui: ");
                       scanf("%d",&opcao3);
                       switch(opcao3){
                           case 0: break;
                           break;

                           case 1: a.faturamento = 0.0f;
                           break;

                           default: printf("Opcao invalida");
                           break;
                   }
               } while(!(opcao3 == 0 || 1));

            }
            break;
            case 6:
               //Opção que encerra o programa.
               salvarDados(&a);
               printf("Dados salvos com sucesso.\n");
               return 0;               
            break;
            //Se o usuário selecionar uma opção invalida, ele é informado sobre
            default: printf("Opcao invalida!");
            break;
        }
    } while(opcao != 6);   
    
    return 0;
}
