/*****************************************************************************
* @author  Filipe da Silva e Samuca
* @brief   Decifra uma frase codificada em cifra de C�sar
*
* @name
* @version 0.1
* @date    28/10/20 + 29/10/20
*
* @description
    Um arquivo no formato texto cont�m uma mensagem codificada atrav�s
da cifra de c�sar. A mensagem � composta somente por letras mai�sculas do
alfabeto oficial da l�ngua portuguesa. A mensagem n�o cont�m espa�os.
    O programa desenvolvido deve auxiliar o usu�rio na decodifica��o desta
mensagem. A aplica��o(o programa) deve, de alguma maneira, orientar o
usu�rio na opera��o do programa.
    A decodifica��o autom�tica da mensagem, embora desej�vel, n�o �
obrigat�ria. O processo de decodifica��o pode ser feita atrav�s de intera��o
com o usu�rio.
    O nome do arquivo dever� ser informado pelo usu�rio.
    O resultado do programa � apresentado em formato de arquivo
texto, cujo nome � o mesmo do arquivo original, acrescido do sulfixo _dec.
A extens�o do arquivo permanece a mesma.
******************************************************************************/
// Includes
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <locale.h>


//========= PROT�TIPO DE FUN��ES =========//

//fun��o para dar uma nova linha
void nl(void);
//fun��o para nomear o arquivo
void Nomeia(char *nome);

//========= -------------------- =========//

//======================================================== MAIN ========================================================//
int main(void)
{
    system("cls");
    setlocale(LC_ALL,"");

    //========= Declara��o das vari�veis =========//

    FILE *fp;

    char nameFile[100];     //nome do arquivo a ser aberto
    char ch;                //vari�vel para pegar um caractere do fluxo

    int cont=0;             //conta quantos caracteres a mensagem tem
    int desloc=0;           //desloca os caracteres da mensagem
    int i;
    int l, c;               //manipular a matriz
    int consoante;          //conta a quantidade de consoantes das mensagens
    int vetor_flag[25];     //vetor que indica se a mensagem faz sentido ou n�o

    //inicializa o vetor com todas as posi��es igual a 1
    for( i=0 ; i<25 ; i++ )
    vetor_flag[i] = 1;
    //========= ------------------------ =========//

    //============================================================= Intera��o com o usu�rio =============================================================//
    printf("\t=============================================================== INTRODU��O ============================================================");
    nl();nl();
    printf("\tEste � um programa desenvolvido para decifrar, de forma autom�tica, mensagens criptografadas com a cifra de C�sar.\n");
    printf("\tObserva��o: O deslocamento utilizado para decifrar a mensagem � desconhecido.\n");
    printf("\tPara utiliza��o deste programa voc� deve ter a mensagem cifrada presente no seu computador em um arquivo no formato de texto.\n");
    printf("\tA mensagem precisa conter apenas letras MAIUSCULAS, n�o pode conter ESPA�OS e s� devem ser usados caracteres presentes no ALFABETO.\n");
    printf("\n\t=======================================================================================================================================");
    //=============================================================== --------------------- =============================================================//

    //============================= ABERTURA DO ARQUIVO =============================//
    //----------- Ler o nome do arquivo -----------//
    Nomeia(nameFile);

    //----------- Abre um arquivo TEXTO para LEITURA -----------//
    fp = fopen(nameFile, "rt");

    //----------- verifica��o se o arquivo foi aberto -----------//
    if (fp == NULL)  // Se houve erro na abertura
    {
     printf("\n\tProblemas na abertura do arquivo.\n");
     return 0;
    }
    //============================= ------------------- =============================//

    //============================= CONTAGEM DA QUANTIDADE DE CARACTERES DA MENSAGEM =============================//

    //------- percorre todo o arqivo -------//
    while (!feof(fp)) //sai da repeti��o quando encontra o final do arquivo
    {

        //pega um caractre da mensagem
        ch = getc(fp);

        //contabiliza a quantidade de caracteres da mensagem
        cont++;

    }//end while

    //retira a contagem do final do arquivo
    cont--;

    //============================= ------------------------------------------------ =============================//

    //========= Declara��o das vari�veis da mensagem =========//

    //essas vari�veis devem ser declaras ap�s o tamanho da mensagem ser conhecido

    char msg[cont];          //mensagem original
    char msg_mod[cont];
    char armazem[25][cont];   //armazena as palavras do arquivo

    //========= ----------------------------------- =========//

    //reposiciona o ponteiro do arquivo para o seu in�cio
    rewind(fp);

    //============================= SALVAR A MENSAGEM DO ARQUIVO =============================//

    //inicia o �ndice do vetor string onde a mensagem vai ser armazenada
    c=0;

    //------- percorre todo o arqivo -------//
    while (!feof(fp)) //sai da repeti��o quando encontra o final do arquivo
    {
        //pega um caractre da mensagem
        ch = getc(fp);

        msg[c] = ch;
        c++; //passa para o pr�ximo caractere da palavra

    }//end while

    //marca o final da string com o \0
    msg[c-1]='\0';
    //============================= ---------------------------- =============================//

    //============================= Exibindo a mensagem cifrada ======================================//
    printf("\n\n\t============================================================= DECODIFICANDO ===========================================================");
    printf("\n\n\tMensagem cifrada encontrada no local do arquivo indicado: %s",msg);
    //================================================================================================//

    //====================== DESLOCA TODAS AS POSI��ES DA MENSAGEM E SALVA NO ARMAZEM ======================//

    /*      **L�GICA
     *          Pega caracter por caractere da mensagem original
     *          desloca o caractere x vezes e atribui no armazem na linha l
     *          passa para a pr�xima linha do armazem
     *
     *          se o deslocamento passar da letra Z, ele � defasado de -26, fazendo o deslocamento
     *          voltar para o in�cio
     *
     *          No final, se tem todas as 25 mensagens deslocadas poss�veis salvas no armazem
     *
     */

    //inicializa aas linhas do armazem
    l=0;

    for( desloc=1 ; desloc<26 ; desloc++ )  //o deslocamento das letras � de 1 a 25 vezes
    {
        for( c=0 ; c<cont ; c++ )   //percorre cada caractere da mensagem
        {

            if( (msg[c]+desloc)>'Z' )   //quando o deslocamente avan�a da letra Z, ele � defasado de -26
                armazem[l][c]=msg[c]+desloc-26; //desloca o caractere da mensagem e atribui no armazem

            else
                armazem[l][c]=msg[c]+desloc;    //desloca o caractere da mensagem e atribui no armazem
        }

        //avan�a para a pr�xima linha do armazem
        l++;
    }

    //====================== -------------------------------------------------------- =====================//

    //====================== FILTRAGEM DAS POSS�VEIS MENSAGENS POSS�VEIS ======================//

    //--------------------------------- primeiro teste ----------------------------------------//

    /*      **L�GICA
     *          foi adotado o seguinte CRIT�RIO para o primeiro filtro:
     *          4 consoantes consecutivas considera-se uma mensagem sem sentido
     *
     *          Percorre todo o armazem, pegando caractere por caractere
     *          Analiza se o caractere � uma consoante. se for, incrementa um contador
     *          se n�o for consoante, zera o contador.
     *          se o contador chegar a 4, se tem 4 consoantes consecutivas, ent�o
     *          o vetor_flag sinaliza que a mensagem da linha l n�o faz sentido
     *
     */

    for( l=0 ; l<25 ; l++ )         //--/
    {                               //   {percorre todas as posi��es do armazem}
        for( c=0 ; c<cont ; c++ )   //--/
        {

            //se o caractere for uma CONSOANTE
            if ( armazem[l][c]!='A' && armazem[l][c]!='E' && armazem[l][c]!='I' && armazem[l][c]!='O' && armazem[l][c]!='U')
            {
                //contabiliza uma CONSOANTE
                consoante++;
            }
            else
                //se n�o for consoante, zera o contador
                consoante=0;

            //se houver 4 consoantes consecutivas, o vetor de sinaliza��o indica que a mensagem da linha l n�o faz sentido
            if (consoante >= 4)
                vetor_flag[l] = 0;
        }

        //printf("linha %d - %d \n", l, vetor_flag[l]);
        consoante=0;
    }

    //--------------------------------- segundo teste ----------------------------------------//
    /*      **L�GICA
     *          O segundo teste s� ocorre quando, a partir do primeiro teste ainda hajam mais
     *          de duas frases poss�veis.
     *          Neste filtro, ser�o retiradas as palavras que cont�m letras menos usuais na
     *          l�ngua portuguesa, como K,Y e Z.
     *          Primeiro, o c�digo percorre o nosso 'vetor_flag' e incrementa uma variavel
     *          para saber quantas frases passaram no teste. Se esse n�mero for maior que dois
     *          o segundo filtro come�a ent�o a ser utilizado.
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

                if ( armazem[l][c]=='K' || armazem[l][c]=='W' || armazem[l][c]=='X' || armazem[l][c]=='Y' || armazem[l][c]=='Z') //se o programa encontrar letras menos prov�veis
                {
                    vetor_flag[l] = 0;  //zera a posi��o do vetor_flag, indicando que a palavra da linha 'l' n�o � a mais prov�vel
                }
            }
        }
    }

    //======================================= EXIBINDO OS RESULTADOS =======================================//
    printf("\n\tEstas s�o as mensagens mais prov�veis que o programa encontrou como resultado da decodifica��o: \n\n\t");

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

    //----------- verifica��o se o arquivo foi aberto -----------//
    if (fp == NULL)  // Se houve erro na abertura
    {
     printf("\n\tProblemas na abertura do arquivo de resultado\n");
     return 0;
    }
    //============================= --------------------------------- =============================//

    //========================================================== Finaliza��o ===========================================================//
    printf("\n\n\t========================================================== ENVIANDO RESULTADOS ========================================================");
    printf("\n\n\tO resultado da decodifica��o da mensagem foi enviado em formato de texto, para o mesmo diret�rio do arquivo de texto codificado.\n");
    printf("\tO nome do arquivo que cont�m o resultado � %s ", nameFile);
    printf("\n\n\tEsperamos que tenha gostado do programa ! At� a pr�xima ;) \n\n");
    printf("\t=======================================================================================================================================\n\n\t");

    //colocando a mensagem decodificada no arquivo de texto do resultado

    fprintf(fp,"Aqui esta os resultados do programa: \n\nMensagem cifrada: %s\n\n",msg);
    fprintf(fp,"Mensagens decodificadas mais prov�veis: \n\n");

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

//========= fun��o para ler o nome do arquivo(formato de texto) =========//
void Nomeia(char *nome)
{
    nl();nl();
    printf("\t====================================================== DEFININDO O LOCAL DO ARQUIVO ===================================================");
    printf("\n\n\tDigite neste campo o caminho (endere�o) do arquivo de texto que cont�m a mensagem, conforme o exemplo abaixo.\n");
    printf("\tExemplo: C:\\\\Users\\\\OneDrive\\\\�rea de Trabalho\\\\programa��o\\\\Exerc�cios\\\\Lista 1\n");
    printf("\tObserva��o 1: O diret�rio PRECISA conter DUAS barras entre cada novo endere�o para que o programa possa reconhec�-lo.\n");
    printf("\tObserva��o 2: Se o arquivo estiver presente no mesmo diret�rio onde o programa se encontra, digite apenas o nome do arquivo.\n");
    printf("\n\tDigite o diret�rio do seu arquivo: ");

    gets(nome);                         //l� o nome e armazena no ponteiro
    strcat(nome, ".txt");               //adiciona o formato do arquivo

    printf("\n\t=======================================================================================================================================");
}




