/* ================================================= */
/* Exemplo de implementacao Listas Simplesmente Enc. */
/* Exercicios da apostila                            */
/* Profa Fabiana Lorenzi                             */
/* Estruturas de Dados I                             */
/* ================================================= */

#include <stdio.h>
#include <conio.h>
#include <malloc.h>

/* estrutura da Lista Simplesmente Encadeada...*/
struct nodo {
 int dados;
 struct nodo *proximo;
};

void insere_esquerda(struct nodo **inicio, struct nodo **fim, int valor, int *sinal);
void insere_antes_de_k (struct nodo **inicio, struct nodo *k, int valor , int *sinal);


/* ==================================== */
/* Insere um nodo a esquerda (no inicio)*/
/* ==================================== */
void insere_esquerda(struct nodo **inicio, struct nodo **fim, int valor, int *sinal)
{
  struct nodo *p;

     p = (struct nodo *) malloc (sizeof(struct nodo));
     if (p)
     {
	    p->dados=valor;
	    p->proximo=*inicio;
	    *inicio = p;
	    if (*fim==NULL)
	       *fim = p;
        *sinal=1;
     }
     else
	*sinal=0;
}

/* =============================== */
/* Insere um nodo antes do nodo K; */
/* =============================== */
void insere_antes_de_k (struct nodo **inicio, struct nodo *k, int valor , int *sinal)
{
  struct nodo *ant, *aux, *p;
   
  if (*inicio) 		//Se a lista não está vazia
  {	  p= (struct nodo *) malloc (sizeof(struct nodo));
 	  if (p == NULL)     //Se não foi possível alocar espaço em memória 
             *sinal = 0;
          else 
          {
    	    p->dados = valor;
            aux = *inicio;
            while (aux != k && aux != NULL)  //Percorre a lista até achar o nodo k  ou até chegar ao fim da lista.
		    {   ant = aux;
		        aux = aux->proximo;
            }
            if (aux != NULL)
            {
	           if (k==*inicio)
               {
   		         p->proximo=*inicio;
 		         *inicio=p;
                 *sinal = 1;
		       }
               else
		       {
		         ant->proximo = p;
  		         p->proximo = k;
		         *sinal = 1;
       	       }
	        } 
            else   		//não encontrou k
		    {  *sinal= 0;
		       free(p);
   	        }
           }  //se reservou memoria para p
   } else
	*sinal= 0;  //nao existe lista
}

/* ====================================================================== */
/* funcao que conta quantos elementos tem a lista simplesmente encadeada. */
/* ====================================================================== */
int conta (struct nodo *lista)
{
  int cont=0;

  while (lista != NULL)
  {
      cont = cont+1;
      lista=lista->proximo;
  }
  return cont;
}

/* ====================================================================== */
/* funcao que retorna o nodo com maior elemento da lista simp. encadeada. */
/* ====================================================================== */
struct nodo *maior_valor (struct nodo *lista)
{
  int ma=0;
  struct nodo *p, *ant;

  if (lista == NULL)
  {
    p=NULL;
  }
  else
  {
     ma=lista->dados;
     p=lista; /* guarda o end. do nodo, caso o maior seja o 1o. nodo da lista */
     ant=lista;
     lista=lista->proximo;
     while (lista != NULL)
     {
	   if (lista->dados > ma) /* procura o maior valor da lista... */
       {
	     ma = lista->dados; /* guarda o valor em MA */
  	     p = ant->proximo;  /* guarda o endereco do maior valor em P */
       }
       ant=lista;
       lista=lista->proximo;
     }
  }
  return p; /* funcao sempre retorna valor. */
}

/* =============================================== */
/* Procedimento para mostrar o conteudo da lista.  */
/* =============================================== */
void mostra_lista (struct nodo *lista)
{
  struct nodo *aux;

  aux=lista;
  while (aux != NULL) /* Enquanto nao for final da lista... */
  {
    printf("Valores-> %i\n",aux->dados);
    aux=aux->proximo;
  }
}

/* =============================================== */
/* Procedimento que libera todo conteudo da lista  */
/* =============================================== */
void libera_lista (struct nodo **lista)
{
  struct nodo *aux, *p;

  aux=*lista;
  while (aux != NULL) /* Enquanto nao for final da lista... */
  { 
    p=aux;
    aux=aux->proximo;
    free(p);
  }
}









void inseri_4nodo(struct nodo **inicio, struct nodo **fim, int valor, int *sinal) {
	struct nodo *p, *aux;
	int x;
	if (conta(*inicio) < 3) {
		*sinal = 0;
	} else {
		p = (struct nodo *) malloc(sizeof(struct nodo));
	 	if (p == NULL)
            *sinal = 0;
    	else {
			p->dados = valor;
			aux = *inicio;
			for(x=1;x<3;x++) {
				aux = aux->proximo;
			}
			p->proximo = aux->proximo;
			aux->proximo = p;
			if (aux == *fim) {
				*fim = p;
			}
			*sinal=1;
		}
	}
}


void inseri_5elemento(struct nodo **lista, int valor, int *sinal){
	struct nodo *p, *aux;
	int x;
		if(conta(*lista) < 5)
		sinal =0;
			else
			p = (struct nodo *) malloc(sizeof(struct nodo));
		if( p == NULL)
		sinal = 0;
			else{
				p->dados = valor;
				aux = *lista;
					for(x=1; x<3; x++){
						aux = aux->proximo;
						}
				p->proximo = aux->proximo;
				aux->proximo = p;
				*sinal = 1;		
				}
				
	}






/* Programa principal */
int main()
{
  int num, ok;  // variavel global que representa o sinal 

  struct nodo *l1i=NULL, *l1f=NULL, *lk=NULL;

  // l1i = inicio da lista
  // l1f = final da lista
  // lk = lista que armazena o endereco do nodo K

  /* Este trecho do programa serve para que o usuario digite varios valores (ate digitar 0)
     que serao armazenados na lista (insercao no inicio da lista).
  */
  printf("\nPara encerrar a insercao digite 0 !");
  do {
       printf("\nInforme um valor. : ");
       scanf("%d",&num);
       if (num != 0)
       {
      	 insere_esquerda(&l1i, &l1f, num, &ok);
         if (ok == 0)
           printf("\nErro de alocacao de memoria...");
       }
     }
  while (num != 0);

  /* O procedimento mostra_lista serve para mostrar o conteudo da lista
     que est? sendo passada como parametro.
  */
  mostra_lista(l1i);
  getch();

  /* Este trecho do programa serve para que o valor digitado pelo usuario seja
     inserido ANTES do nodo que tem o maior valor.
  */
  printf("\nInforme outro valor: (insercao antes o maior elemento da lista(K)): ");
  scanf("%d",&num);
  if (num != 0)
  {
   /* a vari?vel global lk representa o K.
      a funcao maior_valor ? chamada e o endereco do nodo com o maior valor ?
      armazenado na variavel global lk (K).
   */
   lk=maior_valor(l1i);

   /* Chamada do procedimento Insere_antes_de_k
      =========================================
     Neste exemplo, o valor digitado pelo usuario sera incluido antes do nodo que tem 
     o maior valor (ou seja, a posicao K eh a posicao do nodo que armazena o maior valor
     da lista.
   */
   insere_antes_de_k(&l1i, lk, num, &ok);
   if (ok == 0)       // se deu erro de alocacao de memoria...
     printf("\nErro de alocacao de memoria...");
     
   mostra_lista(l1i);
   getch();
   //libera_lista(&l1i);
   //getch();
  }
  
  
  
  
  
  
  
  
  
 /* printf("\nInforme outro valor: (insercao no 4): ");
  scanf("%d",&num);
  if (num != 0)
  {
   inseri_4nodo(&l1i, &l1f, num, &ok);
   
   if (ok == 0)
     printf("\nErro de alocacao de memoria...");
     
   mostra_lista(l1i);
   getch();
   //libera_lista(&l1i);
   //getch();
  }*/
  
  
printf("\nInforme outro valor: (insercao antes do 5): ");
  scanf("%d",&num);
  if (num != 0)
  {
   inseri_5elemento(&l1i, num, &ok);
   
   if (ok == 0)
     printf("\nErro de alocacao de memoria...");
     
   mostra_lista(l1i);
   getch();
   libera_lista(&l1i);
   getch();
  }
}
