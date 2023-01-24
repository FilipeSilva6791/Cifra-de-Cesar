/*****************************************************************************
* @author  Filipe da Silva e Samuca
* @brief   Decifra uma frase codificada em cifra de César
*
* @name
* @version 0.1
* @date    28/10/20 + 29/10/20
*
* @description
    Um arquivo no formato texto contém uma mensagem codificada através
da cifra de césar. A mensagem é composta somente por letras maiúsculas do
alfabeto oficial da língua portuguesa. A mensagem não contém espaços.
    O programa desenvolvido deve auxiliar o usuário na decodificação desta
mensagem. A aplicação(o programa) deve, de alguma maneira, orientar o
usuário na operação do programa.
    A decodificação automática da mensagem, embora desejável, não é
obrigatória. O processo de decodificação pode ser feita através de interação
com o usuário.
    O nome do arquivo deverá ser informado pelo usuário.
    O resultado do programa é apresentado em formato de arquivo
texto, cujo nome é o mesmo do arquivo original, acrescido do sulfixo _dec.
A extensão do arquivo permanece a mesma.
******************************************************************************/
// Includes
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <locale.h>


//========= PROTÓTIPO DE FUNÇÕES =========//

//função para dar uma nova linha
void nl(void);
//função para nomear o arquivo
void Nomeia(char *nome);

//========= -------------------- =========//

//======================================================== MAIN ========================================================//
int main(void)
{
    system("cls");
    setlocale(LC_ALL,"");

    //========= Declaração das variáveis =========//

    FILE *fp;

    char nameFile[100];     //nome do arquivo a ser aberto
    char ch;                //variável para pegar um caractere do fluxo

    int cont=0;             //conta quantos caracteres a mensagem tem
    int desloc=0;           //desloca os caracteres da mensagem
    int i;
    int l, c;               //manipular a matriz
    int consoante;          //conta a quantidade de consoantes das mensagens
    int vetor_flag[25];     //vetor que indica se a mensagem faz sentido ou não

    //inicializa o vetor com todas as posições igual a 1
    for( i=0 ; i<25 ; i++ )
    vetor_flag[i] = 1;
    //========= ------------------------ =========//

    //============================================================= Interação com o usuário =============================================================//
    printf("\t=============================================================== INTRODUÇÂO ============================================================");
    nl();nl();
    printf("\tEste é um programa desenvolvido para decifrar, de forma automática, mensagens criptografadas com a cifra de César.\n");
    printf("\tObservação: O deslocamento utilizado para decifrar a mensagem é desconhecido.\n");
    printf("\tPara utilização deste programa você deve ter a mensagem cifrada presente no seu computador em um arquivo no formato de texto.\n");
    printf("\tA mensagem precisa conter apenas letras MAIUSCULAS, não pode conter ESPAÇOS e só devem ser usados caracteres presentes no ALFABETO.\n");
    printf("\n\t=======================================================================================================================================");
    //=============================================================== --------------------- =============================================================//

    //============================= ABERTURA DO ARQUIVO =============================//
    //----------- Ler o nome do arquivo -----------//
    Nomeia(nameFile);

    //----------- Abre um arquivo TEXTO para LEITURA -----------//
    fp = fopen(nameFile, "rt");

    //----------- verificação se o arquivo foi aberto -----------//
    if (fp == NULL)  // Se houve erro na abertura
    {
     printf("\n\tProblemas na abertura do arquivo.\n");
     return 0;
    }
    //============================= ------------------- =============================//

    //============================= CONTAGEM DA QUANTIDADE DE CARACTERES DA MENSAGEM =============================//

    //------- percorre todo o arqivo -------//
    while (!feof(fp)) //sai da repetição quando encontra o final do arquivo
    {

        //pega um caractre da mensagem
        ch = getc(fp);

        //contabiliza a quantidade de caracteres da mensagem
        cont++;

    }//end while

    //retira a contagem do final do arquivo
    cont--;

    //============================= ------------------------------------------------ =============================//

    //========= Declaração das variáveis da mensagem =========//

    //essas variáveis devem ser declaras após o tamanho da mensagem ser conhecido

    char msg[cont];          //mensagem original
    char msg_mod[cont];
    char armazem[25][cont];   //armazena as palavras do arquivo

    //========= ----------------------------------- =========//

    //reposiciona o ponteiro do arquivo para o seu início
    rewind(fp);

    //============================= SALVAR A MENSAGEM DO ARQUIVO =============================//

    //inicia o índice do vetor string onde a mensagem vai ser armazenada
    c=0;

    //------- percorre todo o arqivo -------//
    while (!feof(fp)) //sai da repetição quando encontra o final do arquivo
    {
        //pega um caractre da mensagem
        ch = getc(fp);

        msg[c] = ch;
        c++; //passa para o próximo caractere da palavra

    }//end while

    //marca o final da string com o \0
    msg[c-1]='\0';
    //============================= ---------------------------- =============================//

    //============================= Exibindo a mensagem cifrada ======================================//
    printf("\n\n\t============================================================= DECODIFICANDO ===========================================================");
    printf("\n\n\tMensagem cifrada encontrada no local do arquivo indicado: %s",msg);
    //================================================================================================//

    //====================== DESLOCA TODAS AS POSIÇÕES DA MENSAGEM E SALVA NO ARMAZEM ======================//

    /*      **LÓGICA
     *          Pega caracter por caractere da mensagem original
     *          desloca o caractere x vezes e atribui no armazem na linha l
     *          passa para a próxima linha do armazem
     *
     *          se o deslocamento passar da letra Z, ele é defasado de -26, fazendo o deslocamento
     *          voltar para o início
     *
     *          No final, se tem todas as 25 mensagens deslocadas possíveis salvas no armazem
     *
     */

    //inicializa aas linhas do armazem
    l=0;

    for( desloc=1 ; desloc<26 ; desloc++ )  //o deslocamento das letras é de 1 a 25 vezes
    {
        for( c=0 ; c<cont ; c++ )   //percorre cada caractere da mensagem
        {

            if( (msg[c]+desloc)>'Z' )   //quando o deslocamente avança da letra Z, ele é defasado de -26
                armazem[l][c]=msg[c]+desloc-26; //desloca o caractere da mensagem e atribui no armazem

            else
                armazem[l][c]=msg[c]+desloc;    //desloca o caractere da mensagem e atribui no armazem
        }

        //avança para a próxima linha do armazem
        l++;
    }

    //====================== -------------------------------------------------------- =====================//

    //====================== FILTRAGEM DAS POSSÍVEIS MENSAGENS POSSÍVEIS ======================//

    //--------------------------------- primeiro teste ----------------------------------------//

    /*      **LÓGICA
     *          foi adotado o seguinte CRITÉRIO para o primeiro filtro:
     *          4 consoantes consecutivas considera-se uma mensagem sem sentido
     *
     *          Percorre todo o armazem, pegando caractere por caractere
     *          Analiza se o caractere é uma consoante. se for, incrementa um contador
     *          se não for consoante, zera o contador.
     *          se o contador chegar a 4, se tem 4 consoantes consecutivas, então
     *          o vetor_flag sinaliza que a mensagem da linha l não faz sentido
     *
     */

    for( l=0 ; l<25 ; l++ )         //--/
    {                               //   {percorre todas as posições do armazem}
        for( c=0 ; c<cont ; c++ )   //--/
        {

            //se o caractere for uma CONSOANTE
            if ( armazem[l][c]!='A' && armazem[l][c]!='E' && armazem[l][c]!='I' && armazem[l][c]!='O' && armazem[l][c]!='U')
            {
                //contabiliza uma CONSOANTE
                consoante++;
            }
            else
                //se não for consoante, zera o contador
                consoante=0;

            //se houver 4 consoantes consecutivas, o vetor de sinalização indica que a mensagem da linha l não faz sentido
            if (consoante >= 4)
                vetor_flag[l] = 0;
        }

        //printf("linha %d - %d \n", l, vetor_flag[l]);
        consoante=0;
    }

    //--------------------------------- segundo teste ----------------------------------------//
    /*      **LÓGICA
     *          O segundo teste só ocorre quando, a partir do primeiro teste ainda hajam mais
     *          de duas frases possíveis.
     *          Neste filtro, serão retiradas as palavras que contém letras menos usuais na
     *          língua portuguesa, como K,Y e Z.
     *          Primeiro, o código percorre o nosso 'vetor_flag' e incrementa uma variavel
     *          para saber quantas frases passaram no teste. Se esse número for maior que dois
     *          o segundo filtro começa então a ser utilizado.
     */

    i=0;

    for ( l=0 ; l<25 ; l++ )  //percorre o vetor
    {
        i += vetor_flag[l];   //incrementa i
    }

    if ( i>2 )
    {

        for( l=0 ; l<25 ; l++ )  //percorre as linhas
        {
            for( c=0 ; c<cont ; c++ ) //percorre ate o fim da mensagem
            {

                if ( armazem[l][c]=='K' || armazem[l][c]=='W' || armazem[l][c]=='X' || armazem[l][c]=='Y' || armazem[l][c]=='Z') //se o programa encontrar letras menos prováveis
                {
                    vetor_flag[l] = 0;  //zera a posição do vetor_flag, indicando que a palavra da linha 'l' não é a mais provável
                }
            }
        }
    }

    //======================================= EXIBINDO OS RESULTADOS =======================================//
    printf("\n\tEstas são as mensagens mais prováveis que o programa encontrou como resultado da decodificação: \n\n\t");

    for( l=0 ; l<25 ; l++ )      //-------------------------
    {                            //     Percorre a matriz
        for( c=0 ; c<cont ; c++ )//-------------------------
        {

            if ( vetor_flag[l]==1) // quando encontra as palavras que passaram pelos testes, indicadas pelo vetor
            {
                printf("%c", armazem[l][c]); //exibindo as strings provaveis

                if( c==cont-1 ) //quando chegar no fim da string
                {
                  printf("\n\tDeslocamento: %d\n\n\t",25-l);
                }
            }
        }
    }
    printf("\n\t=======================================================================================================================================");
    //====================================================================================================//

    //-------- fecha o arquivo da mensagem codificada --------//
    fclose(fp);

    //============================= ABERTURA DO ARQUIVO DE RESULTADOS =============================//

    //---- acrescentar _dec no nome do arquivo ----//

    //conta a quantidade de caracteres do nome
    i = strlen(nameFile);

    //coloca o \0 no final do nome do arquivo, desconsiderando o .txt
    nameFile[i-4]='\0';

    //concatena o nome do arquivo com _dec.txt
    strcat (nameFile, "_dec.txt");

    //----------- Abre um arquivo TEXTO para ESCRITA -----------//
    fp = fopen(nameFile, "wt");

    //----------- verificação se o arquivo foi aberto -----------//
    if (fp == NULL)  // Se houve erro na abertura
    {
     printf("\n\tProblemas na abertura do arquivo de resultado\n");
     return 0;
    }
    //============================= --------------------------------- =============================//

    //========================================================== Finalização ===========================================================//
    printf("\n\n\t========================================================== ENVIANDO RESULTADOS ========================================================");
    printf("\n\n\tO resultado da decodificação da mensagem foi enviado em formato de texto, para o mesmo diretório do arquivo de texto codificado.\n");
    printf("\tO nome do arquivo que contém o resultado é %s ", nameFile);
    printf("\n\n\tEsperamos que tenha gostado do programa ! Até a próxima ;) \n\n");
    printf("\t=======================================================================================================================================\n\n\t");

    //colocando a mensagem decodificada no arquivo de texto do resultado

    fprintf(fp,"Aqui esta os resultados do programa: \n\nMensagem cifrada: %s\n\n",msg);
    fprintf(fp,"Mensagens decodificadas mais prováveis: \n\n");

    for( l=0 ; l<25 ; l++ )
    {                                       //percorre o armazem
        for( c=0 ; c<cont ; c++ )
        {

            if ( vetor_flag[l]==1)           //encontra as palavras  que passaram nos testes
            {
                fprintf(fp, "%c", armazem[l][c]);  //coloca no arquivo de texto

                if(c==cont-1)
                    fprintf(fp,"\n\n");
            }
        }
    }

    //-------- fecha o arquivo da mensagem decodificada --------//
    fclose(fp);

    system("pause");
    return 0;
}
//======================================================== END MAIN ========================================================//

void nl()
{
    printf("\n");
}

//========= função para ler o nome do arquivo(formato de texto) =========//
void Nomeia(char *nome)
{
    nl();nl();
    printf("\t====================================================== DEFININDO O LOCAL DO ARQUIVO ===================================================");
    printf("\n\n\tDigite neste campo o caminho (endereço) do arquivo de texto que contém a mensagem, conforme o exemplo abaixo.\n");
    printf("\tExemplo: C:\\\\Users\\\\OneDrive\\\\Área de Trabalho\\\\programação\\\\Exercícios\\\\Lista 1\n");
    printf("\tObservação 1: O diretório PRECISA conter DUAS barras entre cada novo endereço para que o programa possa reconhecê-lo.\n");
    printf("\tObservação 2: Se o arquivo estiver presente no mesmo diretório onde o programa se encontra, digite apenas o nome do arquivo.\n");
    printf("\n\tDigite o diretório do seu arquivo: ");

    gets(nome);                         //lê o nome e armazena no ponteiro
    strcat(nome, ".txt");               //adiciona o formato do arquivo

    printf("\n\t=======================================================================================================================================");
}




