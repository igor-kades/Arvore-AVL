#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include <windows.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    printf("Aguarde enquanto o sistema é carregado");
    Sleep(2500);
    system("cls");
    printf("Obrigado por aguardar");
    Sleep(900);
    system("cls");

    int i,op,opi;
    String str;
    char c;
    Avl *a = arv_criavazia();
    FILE *arquivo;

    do
    {
        printf("__________________________________\n");
        printf("_                                _\n");
        printf("_             MENU               _\n");
        printf("_                                _\n");
        printf("__________________________________\n\n");
        printf("1. Ler texto do arquivo TXT\n");
        printf("2. Adicionar as palavras do texto na AVL\n");
        printf("3. Imprimir arvore\n");
        printf("4. Salvar arvore em arquivo\n");
        printf("5. Adicionar nova palavra\n");
        //printf("6. Remover palavra\n");
        printf("6. Desenhar arvore em hierarquia\n");
        printf("0. Sair\n\n");
        printf("- Digite sua escolha - : ");
        scanf ("%i", &op);
        puts("\n");

        switch(op)
        {
            case 1 :
                    /************************************* ler de arquivo *************************************/
                    arquivo = fopen("arquivo.txt", "r");    //Abre o arquivo txt em modo leitura
                    if(arquivo == 0){
                        printf("Erro na abertura do arquivo.\n\n\n");
                        fclose(arquivo);
                    }else{
                        c = fgetc(arquivo);
                        while(c != EOF){
                            printf("%c", c);
                            c = fgetc(arquivo);
                        }
                    }
                    printf("\n\nArquivo lido com sucesso !!\n");
                    system("pause");
                    /*******************************************************************************************/
                    break;
            case 2 :
                    /**************************** Adicionar texto do arquivo na avl ****************************/
                    arquivo = fopen("arquivo.txt", "r");    //Abre o arquivo txt em modo leitura
                    if(arquivo == 0){
                        printf("Erro na abertura do arquivo.\n\n\n");
                        fclose(arquivo);
                    }else{
                        i = 0;
                        do{
                            c = fgetc(arquivo);             //Le caracter por caracter do arquivo
                            if((c != ' ') && (c != EOF)){
                                str[i] = c;                 //Adiciona o char lido a string
                                i++;
                            }else{                          //Chegou ao final de uma palavra
                                str[i] = '\0';              //Finaliza a string
                                a = avl_insere(a, str);     //Insere a string na avl
                                i = 0;                      //Reseta a posição de preenchimento da string
                            }
                            avl_imprime_pre(a);
                            Sleep(75);
                            system("cls");
                        }while(c != EOF);
                        fclose(arquivo);
                    }
                    printf("Palavras adicionadas com sucesso a arvore !!\n");
                    system("pause");
                    /*******************************************************************************************/
                    break;

            case 3 :
                    do{
                        printf("Escolha o metodo a ser usado:\n");
                        printf("1 - inorder\n");
                        printf("2 - posorder\n");
                        printf("3 - preorder\n\n");
                        printf("Digite sua escolha: ");
                        scanf("%i", &opi);

                        if(opi == 1){
                            avl_imprime_in(a);
                            system("pause");
                        }
                        else if(opi == 2){
                            avl_imprime_pos(a);
                            system("pause");
                        }
                        else if(opi == 3){
                            avl_imprime_pre(a);
                            system("pause");
                        }
                        else
                            printf("Escolha incorreta! Tente novamente.\n\n");
                    }while(opi < 1 || opi > 3 );
                    break;

            case 4 :
                    /************************************ gravar em arquivo ************************************/
                   arquivo = fopen("arquivo.txt", "w");   //Abre o arquivo txt em modo gravação
                   if(arquivo == 0){
                       printf("Erro na abertura do arquivo\n\n");
                   }else{
                       avl_gravar_arquivo(arquivo, a);
                       fclose(arquivo);
                       printf("Dados gravados com sucesso\n");
                   }
                   system("pause");
                   break;
                    /*******************************************************************************************/
            case 5 :
                    printf("Digite o texto a ser adicionado na arvore:\n");
                    scanf("\n%[^\n]", str);
                    system("pause");

                    char *token = strtok(str, " ");
                    while (token != NULL)
                    {
                        a = avl_insere(a, token);
                        token = strtok(NULL, " ");
                    }
                    //system("pause");
                    avl_imprime_pre(a);
                    system("pause");
                    break;
            /*case 6 :
                    printf("Digite a palavra a ser retirada: ");
                    scanf("\n%[^\n]", str);
                    //printf("TESTE - %s", str);
                    avl_retira(a, str);
                    system("pause");
                    avl_imprime_in(a);
                    system("pause");
                    break;*/

            case 6 :
                    avl_desenharArquivo(a, 0);
                    system("pause");
                    break;
            case 0 :
                    printf("Obrigado por usar o sistema!\n\n");
                    system("pause");
                    break;

            default :
                    printf("Opcao invalida !\n\n");
                    system("pause");
        }
    system("cls");
    }while(op != 0);

    return 0;
}
