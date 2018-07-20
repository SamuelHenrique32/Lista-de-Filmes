#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>

typedef struct lista1
{
    char filme[100];
    int ano;
    struct lista1 *filmeant;
    struct lista1 *filmeprox;
    struct lista2 *iniciolistaatores;
    struct lista3 *iniciolistadir;
}filmes;

typedef struct lista2
{
    char nome[100];
    char personagem[100];
    struct lista2 *faprox;
}fatores;

typedef struct lista3
{
    char nome[100];
    struct lista3 *fdirprox;
}fdiretores;

typedef struct lista4
{
    char nome[100];
    struct lista4 *atorant;
    struct lista4 *atorprox;
    struct lista5 *iniciolistaafilmes;
}atores;

typedef struct lista5
{
    char filme[100];
    int ano;
    int copiaano;
    char personagem[100];
    struct lista5 *fatorprox;
}afilmes;

//--------------------------------------------------------------------------------------------------------------------------------questao 6
typedef struct lista6
{
    char diretor[100];
    struct lista6 *diretorprox;
    struct lista6 *diretorant;
    struct lista7 *iniciolistafilmes;                           //inicio da simplesmente encadeada com os filmes e anos de cada diretor questao 6
}diretores;

typedef struct lista7                                           //simplesmente encadeada com os filmes e anos de cada diretor questao 6
{
    char filme[100];
    int ano, anoaux;                                            //anoauxparaordenacao
    struct lista7 *filmeprox;
}filmesaq6;

//--------------------------------------------------------------------------------------------------------------------------------fim questao 6

//--------------------------------------------------------------------------------------------------------------------------------questao 7
typedef struct lista8
{
    char colega[50];
    char filme[100];
    struct lista8 *colegaprox;
}colegas;
//--------------------------------------------------------------------------------------------------------------------------------fim questao 7

//--------------------------------------------------------------------------------------------------------------------------------questao 8
typedef struct lista9
{
        char colega[50];
        char filme[100];
        struct lista9 *colegaprox;
}colegasdir;
//--------------------------------------------------------------------------------------------------------------------------------fim questao 8

//--------------------------------------------------------------------------------------------------------------------------------questao 9
typedef struct lista10
{
    char nomefdup[100];
    struct lista10 *fdupprox;
}fduplicados;
//--------------------------------------------------------------------------------------------------------------------------------fimquestao 9

//---------------------------------------------------------------------------------------------------------------------------------questao 10




//----------------------------------------------------------------------------------------------------------------------------------fim questao 10

void insereAfilmes(afilmes **fainicio, char filme[100], char ano[4], char personagem[100])
{
    afilmes *novo, *novo2;
    novo=(afilmes *)malloc(sizeof(afilmes));
    int conv;
	strcpy(novo->filme, filme);
    conv=atoi(ano);
    novo->ano=conv;
    strcpy(novo->personagem, personagem);
    novo->fatorprox=NULL;
    if(*fainicio==NULL)
    {
        *fainicio=novo;
    }
    else
    {
        novo2=*fainicio;
        while(novo2->fatorprox!=NULL)
            novo2=novo2->fatorprox;
        novo2->fatorprox=novo;
    }
}


void insereA(atores **ainicio, atores **afim, char nome[100], char titulo[100], char ano[4], char pers1[100])
{
    int flagae=0;
    atores *novo, *aux;
    afilmes *fapinicio=NULL;                                //in?cio lista simplesmete encadeada
    aux=*ainicio;
    novo=(atores *)malloc(sizeof(atores));
    strcpy(novo->nome, nome);
    //printf("ATOR= %s", novo);

    if(*ainicio==NULL)                                      //lista vazia
    {
        novo->atorant=NULL;
        novo->atorprox=NULL;
        *ainicio=novo;
        *afim=novo;
        insereAfilmes(&fapinicio, titulo, ano, pers1);
        (*afim)->iniciolistaafilmes=fapinicio;
    }
    else
    {
        do								                          //verifica se ja possui o ator na lista
        {

			if(strcmp(aux->nome,nome)==0)
            {

                flagae=1;
                break;
            }
			aux=aux->atorprox;
        }while(aux!=NULL);

		if (flagae==0)                                          //n?o encontrou o ator, insere no final
        {
            aux=*ainicio;
            while(aux->atorprox!=NULL)
                aux=aux->atorprox;
            aux->atorprox=novo;
            novo->atorant=aux;
            novo->atorprox=NULL;
            *afim=novo;
            insereAfilmes(&fapinicio, titulo, ano, pers1);
            (*afim)->iniciolistaafilmes=fapinicio;

        }
        if(flagae==1)
            insereAfilmes(&aux->iniciolistaafilmes, titulo, ano, pers1);

    }

}

void printAfilmes(afilmes *afinicio)
{
    afilmes *aux;
    aux= afinicio;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("FILME= %s ANO=%d PERSONAGEM=%s\n ", aux->filme, aux->ano, aux->personagem);
            aux= aux->fatorprox;
        } while(aux!=NULL);
    }

}

void printatores(atores *ainicio)
{
    atores *aux;
    aux=ainicio;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("\nATOR= %s\n", aux->nome);
			printAfilmes(aux->iniciolistaafilmes);



            aux=aux->atorprox;
        } while(aux!=NULL);
    }
}



void insereF(filmes **inicio, filmes **fim, char titulo[100], char ano[4])      //priemiro pointer da lista fatores
{
    int conv;
    filmes *novo, *aux;
    fatores *fainicio=NULL;
    novo=(filmes *)malloc(sizeof(filmes));
    conv=atoi(ano);
    novo->ano=conv;                                                              //copia o ano
    strcpy(novo->filme, titulo);                                                 //copia o nome do filme
    if(*inicio==NULL)
    {
        novo->filmeant=NULL;
        novo->filmeprox=NULL;
        *inicio=novo;
        *fim=novo;
    }
    else
    {
        aux=*inicio;
        while(aux->filmeprox!=NULL)
            aux=aux->filmeprox;
        aux->filmeprox=novo;
        novo->filmeant=aux;
        novo->filmeprox=NULL;
        *fim=novo;
    }

}

void insereFatores(fatores **fainicio, char nome[100], char personagem[100])
{
    fatores *novo, *novo2;
    novo=(fatores *)malloc(sizeof(fatores));
    strcpy(novo->nome, nome);
    strcpy(novo->personagem, personagem);
    novo->faprox=NULL;
    if(*fainicio==NULL)
    {
        *fainicio=novo;
    }
    else
    {
        novo2=*fainicio;
        while(novo2->faprox!=NULL)
            novo2=novo2->faprox;
        novo2->faprox=novo;
    }

}

void insereFdiretores(fdiretores **fdinicio, char nome[100])
{
    fdiretores *novo, *novo2;
    novo=(fdiretores *)malloc(sizeof(fdiretores));
    strcpy(novo->nome, nome);
    novo->fdirprox=NULL;
    if(*fdinicio==NULL)
    {
        *fdinicio=novo;
    }
    else
    {
        novo2=*fdinicio;
        while(novo2->fdirprox!=NULL)
            novo2=novo2->fdirprox;
        novo2->fdirprox=novo;
    }
}

void printfatores(fatores *fainicio)
{
    fatores *aux;
    aux= fainicio;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("%s %s \n", aux->nome, aux->personagem);      //elemento da primeira c?lula e n de aux
            aux= aux-> faprox;
        } while(aux!=NULL);
    }
}


void printfdir(fdiretores *fdinicio)
{
    fdiretores *aux;
    aux= fdinicio;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("%s \n", aux->nome);      //elemento da primeira c?lula e n de aux
            aux= aux-> fdirprox;
        } while(aux!=NULL);
    }
}

void printacomano(filmes *inicio)
{
    filmes *aux;
    aux=inicio;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("TITULO= %s\n  ANO= %d\n\n", aux->filme, aux->ano);
            printfdir(aux->iniciolistadir);
            printf("\n\n");
            printfatores(aux->iniciolistaatores);
            aux=aux->filmeprox;
        } while(aux!=NULL);
    }
}


void insereFordenado(filmes **inicioordenadaf, filmes **fimordenadaf, char titulo[100])										//copia a lista de filmes para uma segunda lista para posteriormente ser ordenada
{
    filmes *novo, *aux;
    novo=(filmes *)malloc(sizeof(filmes));
    strcpy(novo->filme, titulo);
    if(*inicioordenadaf==NULL)
    {
        novo->filmeant=NULL;
        novo->filmeprox=NULL;
        *inicioordenadaf=novo;
        *fimordenadaf=novo;
    }
    else
    {
        aux=*inicioordenadaf;
        while(aux->filmeprox!=NULL)
            aux=aux->filmeprox;
        aux->filmeprox=novo;
        novo->filmeant=aux;
        novo->filmeprox=NULL;
        *fimordenadaf=novo;
	}
}

void percorrefilmes(filmes **finicio, filmes **ffim, filmes **inicioordenadaf, filmes **fimordenadaf)					//percorre lista de filmes passando para a segunda lista os nomes dos filmes
{
	filmes *aux;
	aux=*finicio;
	while(aux!=NULL)
	{
		//printf("%s\n", aux->filme);
		insereFordenado(inicioordenadaf, fimordenadaf, aux->filme);
		aux=aux->filmeprox;
	}
}


int verificacrescentef(filmes **inicioordenadaf, filmes **fimordenadaf)											//condicao de repeticao da funçao de ordenaçao
{
    int retorno=1;
    filmes *ant, *aux;
    ant=*inicioordenadaf;
    aux=ant->filmeprox;
    while(aux!=NULL)
    {
        if(strcmp(ant->filme, aux->filme)<=0)
        {
            ant=aux;
            aux=aux->filmeprox;
        }
        else
        {
            retorno=0;
            break;
        }
    }
    return retorno;
}

void ordenaf(filmes **inicioordenadaf, filmes **fimordenadaf)													//ordena a segunda lista
{
    filmes *aux, *ant;
    char titulo[200];
    ant=*inicioordenadaf;
    aux=ant->filmeprox;
    while(verificacrescentef(inicioordenadaf, fimordenadaf)!=1)
    {
        if(strcmp(ant->filme, aux->filme)>0)
        {
            strcpy(titulo, ant->filme);
            strcpy(ant->filme, aux->filme);
            strcpy(aux->filme, titulo);
        }
        ant=aux;
        aux=aux->filmeprox;
        if(aux==NULL)
        {
            ant=*inicioordenadaf;
            aux=*inicioordenadaf;
        }
    }
}

void printaordenadafilmes(filmes *inicioordenadaf)												//printa função ordenada de filmes
{
    filmes *aux;
    aux=inicioordenadaf;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("%s\n", aux->filme);
            aux=aux->filmeprox;
        } while(aux!=NULL);
    }
}

void printaordenadafilmesreversa(filmes *fimordenadaf)												//printa função ordenada de filmes
{
    filmes *aux;
    aux=fimordenadaf;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("%s\n", aux->filme);
            aux=aux->filmeant;
        } while(aux!=NULL);
    }
}

void insereAordenado(atores **inicioordenadaa, atores **fimordenadaa, char ator[100])										//copia a lista de atores para uma segunda lista para posteriormente ser ordenada
{
    atores *novo, *aux;
    novo=(atores *)malloc(sizeof(atores));
    strcpy(novo->nome, ator);
    if(*inicioordenadaa==NULL)
    {
        novo->atorant=NULL;
        novo->atorprox=NULL;
        *inicioordenadaa=novo;
        *fimordenadaa=novo;
    }
    else
    {
        aux=*inicioordenadaa;
        while(aux->atorprox!=NULL)
            aux=aux->atorprox;
        aux->atorprox=novo;
        novo->atorant=aux;
        novo->atorprox=NULL;
        *fimordenadaa=novo;
	}
}

void percorreatores(atores **ainicio, atores **afim, atores **inicioordenadaa, atores **fimordenadaa)					//percorre lista de atores passando para a segunda lista os nomes dos atores
{
	atores *aux;
	aux=*ainicio;
	while(aux!=NULL)
	{
		//printf("%s\n", aux->nome);
		insereAordenado(inicioordenadaa, fimordenadaa, aux->nome);
		aux=aux->atorprox;
	}
}

int verificacrescentea(atores **inicioordenadaa, atores **fimordenadaa)											//condicao de repeticao da funçao de ordenaçao
{
    int retorno=1;
    atores *ant, *aux;
    ant=*inicioordenadaa;
    aux=ant->atorprox;
    while(aux!=NULL)
    {
        if(strcmp(ant->nome, aux->nome)<=0)
        {
            ant=aux;
            aux=aux->atorprox;
        }
        else
        {
            retorno=0;
            break;
        }
    }
    return retorno;
}

void ordenaa(atores **inicioordenadaa, atores **fimordenadaa)													//ordena a segunda lista de atores
{
    atores *aux, *ant;
    char nome[200];
    ant=*inicioordenadaa;
    aux=ant->atorprox;
    while(verificacrescentea(inicioordenadaa, fimordenadaa)!=1)
    {
        if(strcmp(ant->nome, aux->nome)>0)
        {
            strcpy(nome, ant->nome);
            strcpy(ant->nome, aux->nome);
            strcpy(aux->nome, nome);
        }
        ant=aux;
        aux=aux->atorprox;
        if(aux==NULL)
        {
            ant=*inicioordenadaa;
            aux=*inicioordenadaa;
        }
    }
}

void printaordenadatores(atores *inicioordenadaa)
{
    atores *aux;
    aux=inicioordenadaa;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("%s\n", aux->nome);
            aux=aux->atorprox;
        } while(aux!=NULL);
    }
}

void printaordenadatoresreverso(atores *fimordenadaa)
{
    atores *aux;
    aux=fimordenadaa;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("%s\n", aux->nome);
            aux=aux->atorant;
        } while(aux!=NULL);
    }
}


void printaocronologicafilmes(afilmes **iniciocronologica)						//printa os filmes em ordem crononologica, os que nao possuem ano vao para o final
{
    afilmes *aux;
    aux=*iniciocronologica;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            //printf("%s %d\n", aux->filme, aux->ano);
            printf("%s\n", aux->filme);
            aux=aux->fatorprox;
        } while(aux!=NULL);
    }
}

int verificacronologica(afilmes **iniciocronologica)
{
	afilmes *aux=*iniciocronologica;
	int retorno=1;
	while(aux->fatorprox!=NULL)
	{
		if(aux->copiaano>aux->fatorprox->copiaano)
		{
			retorno=0;
			break;
		}
		aux=aux->fatorprox;
	}
	return retorno;
}

void ordenaAfilmessecundaria(afilmes **iniciocronologica)					//ordena pela copia do ano (casos sem ano devem ir para o final)
{

	afilmes *ant, *aux;
	ant=*iniciocronologica;
    aux=ant->fatorprox;
	int anoaux;
    char copiafilme[100];
   	while(verificacronologica(iniciocronologica)!=1)
   	{
		if(ant->copiaano>aux->copiaano)
		{
			strcpy(copiafilme, ant->filme);
           	strcpy(ant->filme, aux->filme);
           	strcpy(aux->filme, copiafilme);
           	anoaux=ant->copiaano;
           	ant->copiaano=aux->copiaano;
           	aux->copiaano=anoaux;
		}
		ant=aux;
        aux=aux->fatorprox;
        if(aux==NULL)
        {
            ant=*iniciocronologica;
            aux=*iniciocronologica;
        }
	}
}

void insereAfilmessecundaria(afilmes **iniciocronologica, char filme[100], int ano)		//lista para ser ordenada por ordem cronológica
{
	afilmes *novo, *novo2;
    novo=(afilmes *)malloc(sizeof(afilmes));
    afilmes *auxprinta=*iniciocronologica;
	strcpy(novo->filme, filme);
    novo->ano=ano;
    if(ano==0)
		novo->copiaano=9999;																	//casos sem ano
	else
		novo->copiaano=ano;
    novo->fatorprox=NULL;
    if(*iniciocronologica==NULL)
    {
		*iniciocronologica=novo;
    }
    else
    {
        novo2=*iniciocronologica;
        while(novo2->fatorprox!=NULL)
            novo2=novo2->fatorprox;
        novo2->fatorprox=novo;
    }
}

void percorrelistasimples(afilmes **iniciolistafilmes, afilmes **iniciocronologica)
{
	afilmes *aux=*iniciolistafilmes;
	while(aux!=NULL)																//percorre a lista simplesmente encadeada de filmes
	{
		//printf("%s %d\n", aux->filme, aux->ano);
		insereAfilmessecundaria(iniciocronologica, aux->filme, aux->ano);								//insere os filmes e anos numa lista secundária
		aux=aux->fatorprox;
	}
}

int procuraator(atores **ainicio, atores **afim, afilmes **iniciocronologica, char consultaator[100])				//encontra o ator na lista duplamente encadeada de atores e passa para a função percorre lista simples de filmes
{
	atores *aux=*ainicio;
	int retorno=0;
	while(aux!=NULL)
	{
		if(strcmp(aux->nome, consultaator)==0)
		{
			break;
		}
		aux=aux->atorprox;
	}
	if(aux==NULL)
	{

	}
	else
	{
		percorrelistasimples(&aux->iniciolistaafilmes, iniciocronologica);													//passa o ponteiro para percorrer a lista simples do nodo do determinado ator
		retorno=1;
	}
	return retorno;
}

void verificafinalator(char ator1[100])																							//revolve problema de quebra da linha
{
	if(ator1[strlen(ator1)-1]=='\t' || ator1[strlen(ator1)-1]=='\n')
		ator1[strlen(ator1)-1]=0;
}


int exclui_duplafilmes(filmes ** inicio , filmes **fim , char filme[100])															//caso ficar algum ator sem filme, exlui o nodo da dupla de atores
{
	filmes *ptaux , *ant , *prox ;
	if (*inicio==NULL )
		return 0;
	if(strcmp((*inicio)->filme, filme)==0)
	{
		ptaux= *inicio;
		prox= (*inicio)->filmeprox;
		ant=(*inicio)->filmeant;
		if(prox!=NULL)
			prox->filmeant=(*inicio)->filmeant;
		else
			(*fim)=(*inicio)->filmeant;
		if(ant!=NULL)
			ant->filmeprox=(*inicio)->filmeprox;
		else
			(*inicio)=(*inicio)->filmeprox ;
		free ( ptaux );
		return 1;
	}
	return exclui_duplafilmes(&((* inicio )->filmeprox), fim, filme);
}


int exclui_duplatores(atores ** inicio , atores **fim , char ator[100])															//caso ficar algum ator sem filme, exlui o nodo da dupla de atores
{
	atores *ptaux , *ant , *prox ;
	if (*inicio==NULL )
		return 0;
	if(strcmp((*inicio)->nome, ator)==0)
	{
		ptaux= *inicio;
		prox= (*inicio)->atorprox;
		ant=(*inicio)->atorant;
		if(prox!=NULL)
			prox->atorant=(*inicio)->atorant;
		else
			(*fim)=(*inicio)->atorant;
		if(ant!=NULL)
			ant->atorprox=(*inicio)->atorprox;
		else
			(*inicio)=(*inicio)->atorprox ;
		free ( ptaux );
		return 1;
	}
	return exclui_duplatores(&((* inicio )->atorprox), fim, ator);
}


void verificaatorsemfilme(atores **inicio, atores **fim)													//verifica se há atores sem filme para remover seu nodo
{
	atores *aux=*inicio;
	while(aux!=NULL)
	{
		if(aux->iniciolistaafilmes==NULL)
		{
			//printf("O ator %s está sem filme\n", aux->nome);
			exclui_duplatores(inicio, fim, aux->nome);														//se encontrar ator sem filme, remove o ator
		}
		aux=aux->atorprox;
	}
}

void removeAfilmes(afilmes **inicio, char nomeremocao[100])													//percorre simplesmente encadeada em cada nodo de duplamente
{																											//encadeada dos atores para remover os filmes
	afilmes *aux;
	aux=*inicio;
	if (*inicio==NULL)
		return;
	if (strcmp((*inicio)->filme, nomeremocao)!=0)
	{
		removeAfilmes(&((*inicio)->fatorprox), nomeremocao);
		return;
	}
	aux=*inicio;
	(*inicio)=(*inicio)->fatorprox;
	free(aux);
}

void printaatualizadaAfilmes(afilmes **inicio)
{
	afilmes *aux;
	aux=*inicio;
	while(aux!=NULL)
	{
		printf("%s\n", aux->filme);
		aux=aux->fatorprox;
	}
}

void procuraatores(atores **ainicio, atores **afim, char ator[100], char nomeremocao[100])								//percorre duplamente encadeada de atores para remover o filme de cada ator
{
	atores *aux=*ainicio;
	while(aux!=NULL)
	{
		if(strcmp(aux->nome, ator)==0)
			break;
		aux=aux->atorprox;
	}

	//printf("\nATOR= %s\nFilmes nos quais o ator participou:\n", ator);
	//printaatualizadaAfilmes(&aux->iniciolistaafilmes);
	removeAfilmes(&aux->iniciolistaafilmes, nomeremocao);
	//printf("\nLista atualizada:\n");
	//printaatualizadaAfilmes(&aux->iniciolistaafilmes);
}


void procurafatores(atores **ainicio, atores **afim, fatores **fainicio, char nomeremocao[100])							//percorre simplesmente encadeada de atores dentro da dupla de filmes																						//percorre a simplesmente encadeada de atores
{
	fatores *aux=*fainicio;
	while(aux!=NULL)
	{
		//printf("%s\n", aux->nome);
		procuraatores(ainicio, afim, aux->nome, nomeremocao);
		aux=aux->faprox;
	}
}

int procurafilme(filmes **finicio, filmes **ffim, atores **ainicio, atores **afim, char nomeremocao[100])  				//encontra o nodo do filme a ser removido
{
	int retorno=0;
	filmes *aux=*finicio;
	while(aux!=NULL)
	{
		if(strcmp(aux->filme, nomeremocao)==0)
		{
			retorno=1;
			break;
		}
		aux=aux->filmeprox;
	}
	if(retorno==1)
		procurafatores(ainicio, afim, &aux->iniciolistaatores, nomeremocao);															//VERIFICAR CASO O FILME NAO TENHA ATORES
	return retorno;
	//chamar a lista simples de atores
	//para cada ator encontralho na lista dupla e removier o filme da sua lista simples
	//caso a lista simples do outor suma remover o autor da dupla
}

//------------------------------------------------------------------------------------------------------------------------------------------ questao 6 (switch 8)

void insereDfilmes(filmesaq6 **faq6inicio, char filme[100], int ano, int anoaux)
{
    filmesaq6 *aux, *anterior;
    if((*faq6inicio==NULL) || (*faq6inicio)->anoaux>=anoaux)        //insere no inicio
    {
        aux=(filmesaq6 *)malloc(sizeof(filmesaq6));
        strcpy(aux->filme, filme);
        aux->ano=ano;
        aux->anoaux=anoaux;
        aux->filmeprox=*faq6inicio;
        *faq6inicio=aux;
        return;
    }
    aux=*faq6inicio;
    while((aux!=NULL) && (aux->anoaux<anoaux))                      //avança ate encontrar um nodo com ano maior ou ate o final da lista
    {
        anterior=aux;
        aux=aux->filmeprox;
    }
    aux=(filmesaq6 *)malloc(sizeof(filmesaq6));                   //insere na posição
    strcpy(aux->filme, filme);
    aux->ano=ano;
    aux->anoaux=anoaux;
    aux->filmeprox=anterior->filmeprox;
    anterior->filmeprox=aux;
}

void insereD(diretores **dinicio, diretores **dfim, char diretor[100], char titulo[100], char ano[4])               //insere na duplamente encadeada de diretores
{
    int flagae=0, conv, anoaux;
    diretores *novo, *aux;
    filmesaq6 *faq6inicio=NULL;                                //inicio lista simplesmete encadeada
    aux=*dinicio;
    novo=(diretores *)malloc(sizeof(diretores));
    strcpy(novo->diretor, diretor);

    conv=atoi(ano);                                         //anoaux para inserir ordenado
    if(conv!=0)
        anoaux=conv;
    else
        if(conv==0)
            anoaux=99999;

    if(*dinicio==NULL)                                      //lista vazia
    {
        novo->diretorant=NULL;
        novo->diretorprox=NULL;
        *dinicio=novo;
        *dfim=novo;
        insereDfilmes(&faq6inicio, titulo, conv, anoaux);
        (*dfim)->iniciolistafilmes=faq6inicio;
    }
    else
    {
        do								                          //verifica se ja possui o diretor na lista
        {

			if(strcmp(aux->diretor,diretor)==0)
            {
                flagae=1;
                break;
            }
			aux=aux->diretorprox;
        }while(aux!=NULL);

		if (flagae==0)                                          //nao encontrou o diretor, insere no final
        {
            aux=*dinicio;
            while(aux->diretorprox!=NULL)
                aux=aux->diretorprox;
            aux->diretorprox=novo;
            novo->diretorant=aux;
            novo->diretorprox=NULL;
            *dfim=novo;
            insereDfilmes(&faq6inicio, titulo, conv, anoaux);
            (*dfim)->iniciolistafilmes=faq6inicio;

        }
        if(flagae==1)                                                       //encontrou o ator, atualiza a lista de filmes
            insereDfilmes(&aux->iniciolistafilmes, titulo, conv, anoaux);
    }

}

void printDfilmes(filmesaq6 *faq6inicio)
{
    filmesaq6 *aux;
    aux= faq6inicio;
    if(aux==NULL)
    {

    }
    else
    {
        do
        {
            printf("\n%s\n", aux->filme);
            aux= aux->filmeprox;
        } while(aux!=NULL);
    }
}

int procuradiretor(diretores **dinicio, diretores **dfim, char consultadiretor[100])				//encontra o diretor na lista duplamente encadeada de diretores e passa para a função percorre lista simples de filmes
{
	diretores *aux=*dinicio;
	int retorno=0;
	if(aux==NULL)
	{

	}
	else
    {
        while(aux!=NULL)
        {
            if(strcmp(aux->diretor, consultadiretor)==0)
            {
                retorno=1;
                printDfilmes(aux->iniciolistafilmes);
                break;
            }
            aux=aux->diretorprox;
        }
    }
	return retorno;
}

//-----------------------------------------------------------------------------------------------------------------------------------------fim questao 6 (switch 8)

//-----------------------------------------------------------------------------------------------------------------------------------------questao 7 (switch 9)


void printaatorescolegas(colegas **cinicio, char nomeator[50])
{
	system("cls");
	printf("Atores que trabalharam com %s\n\n", nomeator);
	colegas *aux;
	aux=*cinicio;
	while(aux!=NULL)
	{
		if(strcmp(aux->colega, nomeator)!=0)																		//nao printar se o atual for igual ao lido
			printf("%s no filme %s\n\n", aux->colega, aux->filme);
		aux=aux->colegaprox;
	}
}


void insereatorescolegas(colegas **cinicio, char ator[50], char filme[100])                                         //insere na lista de atores colegas
{
    colegas *novo, *novo2;
    novo=(colegas *)malloc(sizeof(colegas));
    strcpy(novo->colega, ator);
    strcpy(novo->filme, filme);
    novo->colegaprox=NULL;
    if(*cinicio==NULL)
    {
        *cinicio=novo;
    }
    else
    {
        novo2=*cinicio;
        while(novo2->colegaprox!=NULL)
        {
            //if(strcmp(novo2->colega,ator)==0)                  //se o ator já esta na lista, nao deve ser inserido novamente(testar)
              //  break;
            //else
                novo2=novo2->colegaprox;
        }
        novo2->colegaprox=novo;
    }
}


void percorreatoresfilme(fatores **inicio, char nomefilme[100], colegas **cinicio)                                                     //percorre simples de atores de determinado filme
{
    fatores *aux;
    aux=*inicio;
    while(aux!=NULL)
    {
        //printf("%s\n", aux->nome);
        insereatorescolegas(cinicio, aux->nome, nomefilme);
        aux=aux->faprox;
    }
}

void buscafilmes(filmes **finicio, filmes **ffim, char nomefilme[50], colegas **cinicio)                                               //percorre a dupla de filmes
{
    filmes *aux;
    aux=*finicio;
    while(aux!=NULL)
    {
        if(strcmp(aux->filme, nomefilme)==0)
        {
            //printf("ENCONTROU %s\n", aux->filme);
            percorreatoresfilme(&aux->iniciolistaatores, aux->filme, cinicio);
            break;
        }
        aux=aux->filmeprox;
    }
}

void percorrefilmesator(afilmes **inicio, filmes **finicio, filmes **ffim, colegas **cinicio)                                              //percorre a lista simpples de filmes de cada ator
{
    afilmes *aux;
    aux=*inicio;
    while(aux!=NULL)
    {
       // printf("%s\n", aux->filme);
        buscafilmes(finicio, ffim, aux->filme, cinicio);                                                                     //buscar na dupla de filmes
        aux=aux->fatorprox;
    }
}

int buscaator(atores **ainicio, atores **afim, char nomeator[50], filmes **finicio, filmes **ffim, colegas **cinicio)                   //busca o ator informado na dupla de atores
{
    atores *aux;
    aux=*ainicio;
    int retorno=0;
    while(aux!=NULL)
    {
        if(strcmp(aux->nome, nomeator)==0)
        {
            retorno=1;
            //printf("Encontrou %s", aux->nome);
            percorrefilmesator(&aux->iniciolistaafilmes, finicio, ffim, cinicio);
            break;
        }
        aux=aux->atorprox;
    }

    return retorno;
}

//-----------------------------------------------------------------------------------------------------------------------------------------fim questao 7 (switch 9)

//-----------------------------------------------------------------------------------------------------------------------------------------questao 8 (switch 10)
void printaatorescolegasdir(colegasdir **cdinicio, char nomediretor[50])
{
	system("cls");
	printf("Atores que trabalharam com %s\n\n", nomediretor);
	colegasdir *aux;
	aux=*cdinicio;
	while(aux!=NULL)
	{
		if(strcmp(aux->colega, nomediretor)!=0)																		//nao printar se o atual for igual ao lido
			printf("%s no filme %s\n\n", aux->colega, aux->filme);
		aux=aux->colegaprox;
	}
}

void insereatorescolegasdir(colegasdir **cdinicio, char ator[50], char filme[100])                                         //insere na lista de atores colegas
{
    colegasdir *novo, *novo2;
    novo=(colegasdir *)malloc(sizeof(colegasdir));
    strcpy(novo->colega, ator);
    strcpy(novo->filme, filme);
    novo->colegaprox=NULL;
    if(*cdinicio==NULL)
    {
        *cdinicio=novo;
    }
    else
    {
        novo2=*cdinicio;
        while(novo2->colegaprox!=NULL)
        {
            novo2=novo2->colegaprox;
        }
        novo2->colegaprox=novo;
    }
}

void percorreatoresfilmedir(fatores **inicio, char nomefilme[100], colegasdir **cdinicio)                                                     //percorre simples de atores de determinado filme
{
    fatores *aux;
    aux=*inicio;
    while(aux!=NULL)
    {
        //printf("%s\n", aux->nome);
        insereatorescolegasdir(cdinicio, aux->nome, nomefilme);
        aux=aux->faprox;
    }
}

void buscafilmesdir(filmes **finicio, filmes **ffim, char nomefilme[50], colegasdir **cdinicio)														//percorre a dupla de filmes
{
	filmes *aux;
	aux=*finicio;
	while(aux!=NULL)
	{
		if(strcmp(aux->filme, nomefilme)==0)
		{
			//printf("ENCONTROU %s\n", aux->filme);
            percorreatoresfilmedir(&aux->iniciolistaatores, aux->filme, cdinicio);
            break;
    	}
    	aux=aux->filmeprox;
	}
}



void percorrefilmesdiretor(filmesaq6 **inicio, filmes **finicio, filmes **ffim, colegasdir **cdinicio)													//percorre a simples de filmes de cada diretor
{
	filmesaq6 *aux;
	aux=*inicio;
	while(aux!=NULL)
	{
		//printf("%s\n", aux->filme);
		buscafilmesdir(finicio, ffim, aux->filme, cdinicio);
		aux=aux->filmeprox;
	}
}

int buscadiretor(diretores **dinicio, diretores **dfim, char nomediretor[50], filmes **finicio, filmes **ffim, colegasdir **cdinicio)                   //busca o diretor informado na dupla de diretores
{
    diretores *aux;
    aux=*dinicio;
    int retorno=0;
    while(aux!=NULL)
    {
        if(strcmp(aux->diretor, nomediretor)==0)
        {
            retorno=1;
            //printf("Encontrou %s", aux->diretor);
            percorrefilmesdiretor(&aux->iniciolistafilmes, finicio, ffim, cdinicio);
            break;
        }
        aux=aux->diretorprox;
    }

    return retorno;
}

//-------------------------------------------------------------------------------------------------------------------------------------------fim questao 8 (switch 10)

//-------------------------------------------------------------------------------------------------------------------------------------------questao 9 (switch 11)




void verificaduplicados(filmes **finicio, filmes **ffim, fduplicados **fdupinicio)
{
    filmes *aux, *aux2;
    aux=*finicio;
    while(aux!=NULL)
    {
        aux2=aux->filmeprox;
        while(aux2!=NULL)
        {
            if((strcmp(aux2->filme, aux->filme)==0) && (aux2->ano==aux->ano))
            {
                printf("%s\n", aux->filme);
                //insereduplicada(inicioduplicada, aux->filme);
            }
            aux2=aux2->filmeprox;
        }
        aux=aux->filmeprox;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------fim questao 9  (switch 11)

//-------------------------------------------------------------------------------------------------------------------------------------------questao 10     (switch 12)
int percorresimplespers(afilmes **fainicio, char ator[50], char personagem[50])
{
    afilmes *aux;
    aux=*fainicio;
    int retorno=0;
    while(aux!=NULL)
    {
        if(strcmp(personagem, aux->personagem)==0)
        {
            printf("%s no filme %s ano %d\n", ator, aux->filme, aux->ano);
            retorno=1;
        }
        aux=aux->fatorprox;
    }
    return retorno;
}

int perccoreatorespers(atores **ainicio, atores **afim, char personagem[50])                                                           //percorre dupla de atores passando pointer para simples de personagens
{
    atores *aux;
    aux=*ainicio;
    int retorno=0;
    while (aux!=NULL)
    {
        if(percorresimplespers(&aux->iniciolistaafilmes, aux->nome, personagem)==1)
            retorno=1;
        aux=aux->atorprox;
    }
    return retorno;
}
//-------------------------------------------------------------------------------------------------------------------------------------------fim questao 10 (switch12)


int main( )
{
    system ("color 0B");
	FILE *arqin, *arqin2;
    filmes *finicio=NULL;                   //inser??o de filmes
    filmes *ffim=NULL;                      //inser??o de filmes
    filmes *inicioordenadaf;				//lista ordenada de filmes
    filmes *fimordenadaf;					//fim lista ordenada de filmes

    fatores *fainicio=NULL;                 //inser??o de filmes lista simplesmente encadeada de atores

    fdiretores *fdinicio=NULL;              //inser??o de filmes lista simplesmente encadeada de diretores

    atores *ainicio=NULL;                   //inser??o de atores
    atores *afim=NULL;                      //inser??o de atores
    atores *inicioordenadaa;				//lista ordenada de atores
    atores *fimordenadaa;					//fim lista ordenada de atores

    afilmes *iniciocronologica=NULL;		//inicio cronológica de filmes dentro da duplamente encadeada de atores

    int opcao=0;							//escolha da opção
    char consultaator[100];
    char nomeremocao[100];
    char inseretitulo[100];
    char insereano[4];
    char inserediretor[100];
    char insereator[100];
    char inserepersonagem[100];
    char flagfilmesnovos;
    char flagpersonagem;

    //-------------------------------------------------------------questao 6         (switch 8)
    char consultadiretor[50];
    int c;
    diretores *dinicio=NULL;
    diretores *dfim=NULL;
    //-------------------------------------------------------------fim questao 6    (switch 8)

    //-------------------------------------------------------------questao 7        (switch 9)
    char nomeator[50];
    colegas *cinicio=NULL;
    //-------------------------------------------------------------fim questao 7    (switch 9)

    //------------------------------------------------------------questao 8         (switch 10)
    char nomediretor[50];
    colegasdir *cdinicio=NULL;
    //------------------------------------------------------------fim questao 8     (switch 10)

    //------------------------------------------------------------questao 9         (switch 11)
    fduplicados **fdupinicio=NULL;
    //------------------------------------------------------------fim questao 9    (switch 11)

    //------------------------------------------------------------questao 10        (switch 12)
    char nomepers[50];
    //-------------------------------------------------------------fim questao 10    (switch 12)

    char linha[2000], linhaaux[2000], *partes;
    setlocale(LC_ALL,"Portuguese");
    if((arqin=fopen("resumo.txt", "rt"))==NULL)
        printf("\nErro na abertura do arquivo!\n");
    else
    {
        arqin2=fopen("resumo.txt", "rt");
        while((fgets(linha, sizeof(linha), arqin2))!=NULL)              //enquanto a quebra de linha n?o chegar no final
        {
            for(int c=0; c<strlen(linha); c++)
				linha[c]=toupper(linha[c]);
			strcpy(linhaaux, linha);
			fatores *fainicio=NULL;                                     //inser??o de filmes lista simplesmente encadeada de atores
    		fdiretores *fdinicio=NULL;                                  //passar para fun??o mestra
			afilmes *afinicio=NULL;

            int i=0;
            int d=0;
            char titulo [100];
            char ano[4];
            char dir1[100];
            char dir2[100];
            char diraux[100];
            char ator1[100];
            char pers1[100];
            int apos=0;
            int dpos=0;
            int Apos=0;
            int ppos=0;
            int flag=1;
            int flagd=1;
            int flagp=1;
            for(int l=0 ; l<99 ; l++)
            {
                titulo[l]=0;
                dir1[l]=0;
                dir2[l]=0;
                pers1[l]=0;
                ator1[l]=0;
            }
            for(int a=0 ; a<3 ; a++)
            {
                ano[a]=0;
            }

            while(i<=strlen(linhaaux)-1)
            {
        //-----------------------------------------------------------------------------------------------------------------------------------------------------Titulo
                if ((flag==1) && (linhaaux[i]!=','))//------------------------------Copia o Titulo letra a letra
                {
                    while(linhaaux[i]!=44)
                    {
                        titulo[i]=linhaaux[i];
                        i++;
                    }
                }
                if((flag==1) && (linhaaux[i]==44))//--------------------------------passa para o ano
                {
                    flag=2;
                    i++;//----------------------------------------------------------titulo pronto
                    //printf("\n TITULO= %s", titulo);
                }
        //-----------------------------------------------------------------------------------------------------------------------------------------------------ano
                if (flag==2 && linhaaux[i]!=44)//-----------------------------------copia o ano letra a letra
                {
                    while(linhaaux[i]!=44)
                    {
                        ano[apos]=linhaaux[i];
                        apos++;
                        i++;
                    }
                }
                if(flag==2 && (linhaaux[i]==44))//----------------------------------passa para o primeiro dir
                {
                    flag=3;
                    i++;//----------------------------------------------------------ano pronto
                    //printf("\n ANO= %s", ano);

                    insereF(&finicio, &ffim, titulo, ano);                          //chama a fun??o que preenche a lista de filmes com titulo e ano

                }
        //-----------------------------------------------------------------------------------------------------------------------------------------------------primeiro dir
                if (flag==3 && flagd==1 && linhaaux[i]!=44)//-----------------------copia o primeiro dir letra a letra
                {
                    while(linhaaux[i]!=44)
                    {
                        dir1[dpos]=linhaaux[i];
                        dpos++;
                        i++ ;
                    }

                }

                if (flag==3 && flagd==1 && (linhaaux[i]==44))//---------------------passa para os diretores com Dir:
                {
                    dpos=0;
                    i++;
                    flagd=2;
                    flag=3;
                    //printf("\n", d DIR= %sir1);//------------------------------------dir1 pronto

                    verificafinalator(dir1);

                    insereFdiretores(&fdinicio, dir1);
                    insereD(&dinicio, &dfim, dir1, titulo, ano);
                }
                if(flag==3 && flagd==1 && (linhaaux[i]==0))//-----------------------caso termine no primeiro dir
                {
                    while(linhaaux[i]!=44)
                    {
                        dir1[dpos]=linhaaux[i];
                        dpos++;
                        i++ ;
                    }
                    //printf("\n DIR= %s", dir1);   //-----------------------------------dir1 pronto
                    verificafinalator(dir1);

                    insereFdiretores(&fdinicio, dir1);
                    insereD(&dinicio, &dfim, dir1, titulo, ano);
                    break;
                }
        //-----------------------------------------------------------------------------------------------------------------------------------------------------dir:
                if (flag==3 && flagd==2 && linhaaux[i]=='d' && linhaaux[i+1]=='i' && linhaaux[i+2]=='r' && linhaaux[i+3]==':')//copia os diretores com dir:letra a letra
                {

                    while(linhaaux[i]!=44)
                    {
                        dir2[dpos]=linhaaux[i];
                        dpos++;
                        i++;
                    }
                    i++;
                    dpos=0;

                    d=0;
                    strcpy(diraux,dir2);
                    while (diraux[d]!=0)//-----------------------------------------------------limpa dir:
                    {
                        dir2[d]=diraux[d+4];
                        d++ ;
                    }
                    verificafinalator(dir2);
                    //printf("\n DIR= %s", dir2);
                    insereFdiretores(&fdinicio, dir2);
                    insereD(&dinicio, &dfim, dir1, titulo, ano);
                }
                if (flag==3 && flagd==2 && (linhaaux[i]!='d' || linhaaux[i+1]!='i' || linhaaux[i+2]!='r' || linhaaux[i+3]!=':'))//----------------passa para os atores
                {
                    flag=4;
                }
        //-------------------------------------------------------------------------------------------------------------------------------------------ator
                if(flag==4 && flagp==1 && linhaaux[i]!=44)//------------------------------------copia os atores letra a letra
                {
                    while(linhaaux[i]!=',' && linhaaux[i]!='=' && linhaaux[i]!='\0')
                    {

                        ator1[Apos]=linhaaux[i];
                        Apos++;
                        i++ ;
                    }
                }
                //verificafinalator(ator1);
                if(flag==4 && flagp==1 &&  (linhaaux[i]==44||linhaaux[i]==0))//------------------passa para o ator seguinte ou para a fun??o
                {
                    Apos=0;
                    i++;
                    //printf("\n ATOR= %s", ator1);//---------------------------------------------ator pronto
                }
        //-----------------------------------------------------------------------------------------------------------------------------------------------------ator/pers
                if(flag==4 && flagp==1 && linhaaux[i]==61)//--------------------------------------------troca para pers caso tenha
                {
                    Apos=0;
                    flagp=2;
                    i++ ;
                    //printf("\n ATOR= %s", ator1);
                }
        //-----------------------------------------------------------------------------------------------------------------------------------------------------pers
                if(flag==4 && flagp==2 && linhaaux[i]!=44)//-------------------------------------------copia pers letra a letra
                {
                    while(linhaaux[i]!=44 && linhaaux[i]!=0)
                    {
                        pers1[ppos]=linhaaux[i];
                        ppos++;
                        i++;
                    }

                }
                if(flag==4 && flagp==2 && (linhaaux[i]==44||linhaaux[i]==0))//-----------------------troca devolta para o ator caso tenha ou para a fun??o
                {
                    flagp=1;
                    ppos=0;
                    i++ ;
                    //printf("\n PERS= %s", pers1);//----------------------------------------------------personagem pronto
                }
                if(ator1[0]!='1' && ator1[0]!='2')
                {
                	verificafinalator(pers1);
                	insereFatores(&fainicio, ator1, pers1);
                	insereA(&ainicio, &afim, ator1, titulo, ano, pers1);
				}
				for(int l=0 ; l<99 ; l++)
                {
                    dir2[l]=0;
                    diraux[l]=0;
                    ator1[l]=0;
                    pers1[l]=0;
                }
            }
            ffim->iniciolistadir=fdinicio;
		    ffim->iniciolistaatores=fainicio;
            printf("\n");

        }
        printf("Informe a opção desejada e em seguida tecle enter:\n");
	    printf("1- Listar atores em ordem alfabética \n");
		printf("2- Listar atores em ordem alfabética reversa \n");
		printf("3- Listar filmes de um ator em ordem cronológica \n");
		printf("4- Listar filmes em ordem alfabética \n");
		printf("5- Listar filmes em ordem alfabética reversa \n");
		printf("6- Inserir novos filmes\n");
		printf("7- Remoção de filmes\n");
		printf("8- Listar filmes de um diretor em ordem cronológica\n");
		printf("9- Listar atores que trabalharam com determinado ator\n");
		printf("10- Listar atores que trabalharam com determinado diretor\n");
		printf("11- Listar filmes duplicados\n");
		printf("12- Listar atores que interpretaram determinado personagem\n");
        printf("13- Sair\n");
		printf("\nOpção escolhida:");
		scanf("%d", &opcao);																					//lê a opção informada

		while(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4 && opcao!=5 && opcao!=6 && opcao!=7 && opcao!=8 && opcao!=9 &&opcao!=10 && opcao!=11 && opcao!=12 && opcao!=13)		//enquanto a opção informada não for válida, repete até ser informada
		{																										//uma válida
			if(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4 && opcao!=5 && opcao!=6 && opcao!=7 && opcao!=8 && opcao!=9 &&opcao!=10 && opcao!=11 && opcao!=12 && opcao!=13)
			{
				system("cls");
				printf("Opção inválida! informe uma opção válida: \n");
				printf("1- Listar atores em ordem alfabética \n");
				printf("2- Listar atores em ordem alfabética reversa \n");
		    	printf("3- Listar filmes de um ator em ordem cronológica \n");
		 	    printf("4- Listar filmes em ordem alfabética \n");
		 	    printf("5- Listar filmes em ordem alfabética reversa \n");
			    printf("6- Inserir novos filmes\n");
			    printf("7- Remoção de filmes\n");
			    printf("8- Listar filmes de um diretor em ordem cronológica\n");
			    printf("9- Listar atores que trabalharam com determinado ator\n");
			    printf("10- Listar atores que trabalharam com determinado diretor\n");
			    printf("11- Listar filmes duplicados\n");
			    printf("12- Listar atores que interpretaram determinado personagem\n");
			    printf("13- Sair\n");
			    printf("\nOpção escolhida: ");
			}
			scanf("%d", &opcao);
			system("cls");
		}
		system("cls");
		if(opcao==1 || opcao==2 || opcao==3 || opcao==4 || opcao==5 || opcao==6 || opcao==7 || opcao==8 || opcao==9 || opcao==10 || opcao==11 || opcao==12 ||  opcao==13)
		{
			while(opcao!=13)
			{
				switch(opcao)
				{
					case 1:
					{
						percorreatores(&ainicio, &afim, &inicioordenadaa, &fimordenadaa);
						ordenaa(&inicioordenadaa, &fimordenadaa);
						printf("\n");
						printaordenadatores(inicioordenadaa);
						break;
					}
					case 2:
					{
						percorreatores(&ainicio, &afim, &inicioordenadaa, &fimordenadaa);
						ordenaa(&inicioordenadaa, &fimordenadaa);
						printf("\n");
						printaordenadatoresreverso(fimordenadaa);
						break;
					}
					case 3:
					{
						printf("Informe o nome do ator:\n");
						fflush(stdin);
						gets(consultaator);
						for(int c=0; c<strlen(consultaator); c++) 												//não diferenciar minúscula de maiúsculas
							consultaator[c]=toupper(consultaator[c]);
						printf("\n");
						if(procuraator(&ainicio, &afim, &iniciocronologica, consultaator)==1)
						{
							ordenaAfilmessecundaria(&iniciocronologica);
							printf("\n");
							printaocronologicafilmes(&iniciocronologica);
						}
						else
						{
							system("cls");
							printf("Ator não encontrado! Informe outro:");
							while(procuraator(&ainicio, &afim, &iniciocronologica, consultaator)!=1)
							{
								fflush(stdin);
								gets(consultaator);
								for(int c=0; c<strlen(consultaator); c++) 												//não diferenciar minúscula de maiúsculas
									consultaator[c]=toupper(consultaator[c]);
								if(procuraator(&ainicio, &afim, &iniciocronologica, consultaator)==1)
								{
									ordenaAfilmessecundaria(&iniciocronologica);
									printf("\n");
									printaocronologicafilmes(&iniciocronologica);
								}
								else
								{
									system("cls");
									printf("Ator não encontrado! Informe outro:");
								}
							}
						}
						break;
					}
					case 4:
					{
						percorrefilmes(&finicio, &ffim, &inicioordenadaf, &fimordenadaf);			//percorre lista de filmes
						ordenaf(&inicioordenadaf, &fimordenadaf);
						printf("\n");
						printaordenadafilmes(inicioordenadaf);
						break;

					}
					case 5:
					{
						percorrefilmes(&finicio, &ffim, &inicioordenadaf, &fimordenadaf);			//percorre lista de filmes
						ordenaf(&inicioordenadaf, &fimordenadaf);
						printf("\n");
						printaordenadafilmesreversa(fimordenadaf);
						break;
					}
					case 6:
					{
						for(int l=0 ; l<99 ; l++)													//limpa as variáveis
            			{
                			inseretitulo[l]=0;
			                inserediretor[l]=0;
			                insereator[l]=0;
			                inserepersonagem[l]=0;
			            }
			            for(int a=0 ; a<3 ; a++)
			            {
			                insereano[a]=0;
            			}

						printf("Informe o nome do filme:");
						fflush(stdin);
						gets(inseretitulo);															//lê o título
						for(int c=0; c<strlen(inseretitulo); c++) 									//não diferenciar minúscula de maiúsculas
							inseretitulo[c]=toupper(inseretitulo[c]);
						system("cls");
						printf("O filme possui ano? s/n:");
						fflush(stdin);
						scanf("%c", &flagfilmesnovos);												//verifica se há ano
						if(flagfilmesnovos=='s')
						{
							system("cls");
							printf("Informe o ano:");
							fflush(stdin);
							gets(insereano);														//lê o ano
						}

						insereF(&finicio, &ffim, inseretitulo, insereano);							//função para inserir filme e ano;

						system("cls");
						printf("O filme possui diretor? s/n:");
						fflush(stdin);
						scanf("%c", &flagfilmesnovos);
						if(flagfilmesnovos=='s')
						{
							system("cls");
							printf("Informe o nome do diretor:");
							fflush(stdin);
							gets(inserediretor);													//lê o diretor
							for(int c=0; c<strlen(inserediretor); c++) 								//não diferenciar minúscula de maiúsculas
								inserediretor[c]=toupper(inserediretor[c]);
							insereFdiretores(&fdinicio, inserediretor);
							insereD(&dinicio, &dfim, inserediretor, inseretitulo, insereano);
							system("cls");
							printf("O filme possui outro diretor? s/n");
							fflush(stdin);
							scanf("%c", &flagfilmesnovos);											//verifica outros diretores
							while(flagfilmesnovos=='s')
							{
								system("cls");
								printf("Informe outro diretor:");
								fflush(stdin);
								gets(inserediretor);
								for(int c=0; c<strlen(inserediretor); c++) 							//não diferenciar minúscula de maiúsculas
									inserediretor[c]=toupper(inserediretor[c]);
								insereFdiretores(&fdinicio, inserediretor);
								insereD(&dinicio, &dfim, inserediretor, inseretitulo, insereano);
								system("cls");
								printf("O filme possui outro diretor s/n?");
								fflush(stdin);
								scanf("%c", &flagfilmesnovos);
							}
							ffim->iniciolistadir=fdinicio;
						}
						system("cls");

						printf("O filme possui ator? s/n:");
						fflush(stdin);
						scanf("%c", &flagfilmesnovos);
						if(flagfilmesnovos=='s')
						{
							system("cls");
							printf("Informe o nome do ator:");
							fflush(stdin);
							gets(insereator);
							for(int c=0; c<strlen(insereator); c++) 							//não diferenciar minúscula de maiúsculas
								insereator[c]=toupper(insereator[c]);
							system("cls");
							printf("O ator possui personagem? s/n");
							fflush(stdin);
							scanf("%c", &flagpersonagem);											//verificapersonagem
							if(flagpersonagem=='s')
							{
								for(int l=0 ; l<99 ; l++)											//limpa personagem
                				{
                    				inserepersonagem[l]=0;
                				}
								system("cls");
								printf("Informe o nome do personagem:");
								fflush(stdin);
								gets(inserepersonagem);
								for(int c=0; c<strlen(inserepersonagem); c++) 							//não diferenciar minúscula de maiúsculas
									inserepersonagem[c]=toupper(inserepersonagem[c]);
							}
							insereFatores(&fainicio, insereator, inserepersonagem);
							insereA(&ainicio, &afim, insereator, inseretitulo, insereano, inserepersonagem);
							system("cls");
							printf("O filme possui outro ator s/n?");
							fflush(stdin);
							scanf("%c", &flagfilmesnovos);											//verifica outros diretores
							while(flagfilmesnovos=='s')
							{
								system("cls");
								printf("Informe outro ator:");
								fflush(stdin);
								gets(insereator);
								for(int c=0; c<strlen(insereator); c++) 							//não diferenciar minúscula de maiúsculas
									insereator[c]=toupper(insereator[c]);
								system("cls");
								printf("O ator possui personagem? s/n");
								fflush(stdin);
								scanf("%c", &flagpersonagem);											//verificapersonagem
								if(flagpersonagem=='s')
								{
									for(int l=0 ; l<99 ; l++)											//limpa personagem
                					{
                    					inserepersonagem[l]=0;
                					}
									system("cls");
									printf("Informe o nome do personagem:");
									fflush(stdin);
									gets(inserepersonagem);
									for(int c=0; c<strlen(inserepersonagem); c++) 							//não diferenciar minúscula de maiúsculas
										inserepersonagem[c]=toupper(inserepersonagem[c]);
								}
								insereFatores(&fainicio, insereator, inserepersonagem);
								insereA(&ainicio, &afim, insereator, inseretitulo, insereano, inserepersonagem);
								system("cls");
								printf("O filme possui outro ator s/n?");
								fflush(stdin);
								scanf("%c", &flagfilmesnovos);
							}
						}
						ffim->iniciolistaatores=fainicio;
						system("cls");
						break;
					}
					case 7:
					{
						printf("Informe um filme para ser removido:\n");
						fflush(stdin);
						gets(nomeremocao);
						for(int c=0; c<strlen(nomeremocao); c++) 							//não diferenciar minúscula de maiúsculas
							nomeremocao[c]=toupper(nomeremocao[c]);
						if(procurafilme(&finicio, &ffim, &ainicio, &afim, nomeremocao)==1)
						{
							exclui_duplafilmes(&finicio, &ffim, nomeremocao);						//exclui o nodo do filme
						}
						else
						{
							while(procurafilme(&finicio, &ffim, &ainicio, &afim, nomeremocao)!=1)
							{
								system("cls");
								printf("Filme não encontrado! Informe um filme válido:\n");
								fflush(stdin);
								gets(nomeremocao);
								for(int c=0; c<strlen(nomeremocao); c++) 							//não diferenciar minúscula de maiúsculas
									nomeremocao[c]=toupper(nomeremocao[c]);
							}
							exclui_duplafilmes(&finicio, &ffim, nomeremocao);						//exclui o nodo do filme
						}
						system("cls");
						printf("Filme removido com sucesso! Lista de filmes de cada ator atualizada\n");
						verificaatorsemfilme(&ainicio, &afim);										//verifica se há ator na dupla que está sem filme, caso houver, remover
						break;
					}
					case 8:
                    {
                        printf("Informe o nome do diretor:\n");
                        fflush(stdin);
                        gets(consultadiretor);
                        for(c=0; c<strlen(consultadiretor); c++) 												//não diferenciar minúscula de maiúsculas
                            consultadiretor[c]=toupper(consultadiretor[c]);
                        printf("\n");
                        if(procuradiretor(&dinicio, &dfim, consultadiretor)==1)                                        //procura o diretor na duplamente encadeada de diretores
                        {

                        }
                        else
                        {
                            system("cls");
                            printf("Diretor não encontrado! Informe outro:\n\n");
                            while(procuradiretor(&dinicio, &dfim, consultadiretor)!=1)
                            {
                                fflush(stdin);
                                gets(consultadiretor);
                                for(c=0; c<strlen(consultadiretor); c++) 												//não diferenciar minúscula de maiúsculas
                                    consultadiretor[c]=toupper(consultadiretor[c]);
                                system("cls");
                                printf("Diretor não encontrado! Informe outro:");
                            }
                        }
                        break;
                    }

                    case 9:
                    {
                        cinicio=NULL;
						printf("Infore o nome de um ator:");
                        fflush(stdin);
                        gets(nomeator);
                        for(c=0; c<strlen(nomeator); c++) 												//não diferenciar minúscula de maiúsculas
                            nomeator[c]=toupper(nomeator[c]);
                        while(buscaator(&ainicio, &afim, nomeator, &finicio, &ffim, &cinicio)!=1)
                        {
                            system("cls");
                            printf("Informe um ator válido:");
                            fflush(stdin);
                            gets(nomeator);
                            for(c=0; c<strlen(nomeator); c++) 												//não diferenciar minúscula de maiúsculas
                                    nomeator[c]=toupper(nomeator[c]);
                        }
                        printaatorescolegas(&cinicio, nomeator);
                        break;
                    }
					case 10:
					{
						cdinicio=NULL;
						printf("Informe o nome de um diretor:");
                        fflush(stdin);
                        gets(nomediretor);
                        for(c=0; c<strlen(nomediretor); c++) 												//não diferenciar minúscula de maiúsculas
                            nomediretor[c]=toupper(nomediretor[c]);
						while(buscadiretor(&dinicio, &dfim, nomediretor, &finicio, &ffim, &cdinicio)!=1)
						{
							system("cls");
                            printf("Informe um diretor válido:");
                            fflush(stdin);
                            gets(nomediretor);
                            for(c=0; c<strlen(nomediretor); c++) 												//não diferenciar minúscula de maiúsculas
                                    nomediretor[c]=toupper(nomediretor[c]);
                    	}
                    	printaatorescolegasdir(&cdinicio, nomediretor);
                    	break;
					}
					case 11:
                    {
                        printf("Filmes duplicados:\n\n");
                        verificaduplicados(&finicio, &ffim, fdupinicio);
                        break;
                    }
                    case 12:
                    {
                        printf("Informe o nome de um personagem:");
                        fflush(stdin);
                        gets(nomepers);
                        for(c=0; c<strlen(nomepers); c++) 												//não diferenciar minúscula de maiúsculas
                            nomepers[c]=toupper(nomepers[c]);
                        system("cls");
                        if(perccoreatorespers(&ainicio, &afim, nomepers)==1)
                        {

                        }
                        else
                            printf("Nenhum ator interpretou %s\n", nomepers);
                            break;
                    }
					case 13:
					{
						break;
					}
				}

				iniciocronologica=NULL;                                                              //criação de uma nova lista
				inicioordenadaa=NULL;
				inicioordenadaa=NULL;
				fimordenadaa=NULL;
				inicioordenadaf=NULL;
				fimordenadaf=NULL;

				printf("\nInforme outra opção:");
				scanf("%d", &opcao);
				system("cls");

				while(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4 && opcao!=5 && opcao!=6 && opcao!=7 && opcao!=8 && opcao!=9 && opcao!=10 && opcao!=11 && opcao!=12 && opcao!=13)		//enquanto a opção informada não for válida, repete até ser informada
				{																										//uma válida
					if(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4 && opcao!=5 && opcao!=6 && opcao!=7 && opcao!=8  && opcao!=9 && opcao!=10 && opcao!=11 && opcao!=12 && opcao!=13)
					{
						system("cls");
						printf("Opção inválida! informe uma opção válida: \n");
						printf("1- Listar atores em ordem alfabética \n");
						printf("2- Listar atores em ordem alfabética reversa \n");
				    	printf("3- Listar filmes de um ator em ordem cronológica \n");
				 	    printf("4- Listar filmes em ordem alfabética \n");
				 	    printf("5- Listar filmes em ordem alfabética reversa \n");
					    printf("6- Inserir novos filmes\n");
					    printf("7- Remoção de filmes\n");
					    printf("8- Listar filmes de um diretor em ordem cronológica\n");
                        printf("9- Listar atores que trabalharam com determinado ator\n");
                        printf("10- Listar atores que trabalharam com determinado diretor\n");
                        printf("11- Listar filmes duplicados\n");
                        printf("12- Listar atores que interpretaram determinado personagem\n");
                        printf("13- Sair\n");
					    printf("\nOpção escolhida: ");
					}
					scanf("%d", &opcao);
					system("cls");
				}
			}
		}
	}

	//printatores(ainicio);
    //printacomano(finicio);
    //ordena(&finicio, &ffim);
    //printacomano(finicio);
    //printatores(ainicio);
    printf("\n\n");
    printf("\n\n");
    system("pause");
}

