// Éderson Luis dos Reis Fernandes (2N)
// Funcao = recebe 2 valores e retorna media.
// Procedimento = recebe media, status e retorna status.

#include<stdio.h>
#include<stdlib.h>

float calcularMedia(float n1, float n2);
void aprova(float m, int *s);

main(){
       float nota1, nota2;
       int status=0;
       
       printf("Digite a nota um: ");
       scanf("%f",&nota1);
       
       printf("\nDigite a nota dois: ");
       scanf("%f",&nota2);
       
       printf("\nMedia: %.2f\n", calcularMedia(nota1,nota2));
       
       aprova(calcularMedia(nota1, nota2), &status);
       
       if (status)
           printf("\nAprovado!\n\n");
       else
           printf("\nReprovado!\n\n");
       
       system("pause");
}

float calcularMedia(float n1, float n2) {
      return (n1+n2)/2;
}

void aprova(float m, int *s) {
     if (m>=6)
         *s = 1;
     else
         *s = 0;
}
