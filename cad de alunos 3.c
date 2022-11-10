#include<stdio.h>
#include<stdlib.h>
#define NT 4
#define AL 3

typedef struct{
    int dia;
    int mes;
    int ano;
}TData;
typedef struct{
    char nome[50];
    TData nasc;
    float nota[NT];
}TAluno;

TAluno turma[AL];

TAluno criarAluno();
int validar_dt(int dia, int mes, int ano);
void menu(int op);
void incluir();
void listar(TAluno a);
void listarTurma();

TAluno a;

int main(){
    int o;
    menu(o);
    return 0;
}
void menu(int op){
    op=0;
    
    while(op!=3){
        printf("\n===================");
        printf("\n(1) para incluir");
        printf("\n(2) para listar");
        printf("\n(3) para sair");
        printf("\n===================");
        printf("\n> ");
        scanf("%d",&op);
        fflush(stdin);
        
        if(op==1){
            incluir();
        }
        else if(op==2){
            listarTurma();
        }
        else if(op==3){
            system("cls");
            printf("\nSaindo...\n");
        }
        else {
            system("cls");
            printf("\nERRO!");
            printf("\nTente novamente");
        }
    }
}
TAluno criarAluno()
{
    fflush(stdin);
    printf("\nNome: ");
    gets(a.nome);
    fflush(stdin);
    printf("\nData de nascimento(dd/mm/aa): ");
    scanf("%d%d%d", &a.nasc.dia,&a.nasc.mes,&a.nasc.ano);
    
    validar_dt(a.nasc.dia, a.nasc.mes, a.nasc.ano);

    while(validar_dt(a.nasc.dia, a.nasc.mes, a.nasc.ano)==0){
        
        printf("\nData de nascimento invalida!");
        printf("\nDigite novamente(dd/mm/aa): ");
        scanf("%d%d%d", &a.nasc.dia,&a.nasc.mes,&a.nasc.ano);
        
    }

    for(int i=0;i<NT;)
    {
        printf("\nNota %d: ",i+1);
        scanf("%f",&a.nota[i]);
        fflush(stdin);

        if(a.nota[i]<0 || a.nota[i]>10)
        {
            printf("\nDigite a nota novamente!");
        }
        else
        {
            i++;
        }
    }

    return a;
}
void listar(TAluno a)
{
    printf("Nome: %s\n",a.nome);
    printf("Data de nascimento: %d/%d/%d\n", a.nasc.dia, a.nasc.mes, a.nasc.ano);
    printf("Nota: [");
    for(int i=0;i<NT;i++)
    {
        printf("%0.2f  ", a.nota[i]);
    }
    printf("]");
}
void incluir()
{
    int cont=1,i=0;
    
    while(cont!=0){
        if(cont>1 && cont<=9){
            printf("\nOpcao invalida!");
            printf("\nTente novamente\n");
        }
        else if(cont==1){
            printf("\nAluno %d\n",i+1);
            turma[i]=criarAluno();
            i++;
        }
        printf("\nDeseja continuar?(SIM=1/NAO=0): ");
        scanf("%d", &cont);
        
    }
}
void listarTurma(){
    for(int i=0;i<AL;i++){
        listar(turma[i]);
        printf("\n");
    }
}
int validar_dt(int dia, int mes, int ano){

    if(dia<1 || dia>31){
        return 0;
    }
    else if(mes<1 || mes>12){
        return 0;
    }
    else if(ano<0){
        return 0;
    }
    else if(mes==2){
        if(dia>29){
            return 0;
        }
        else if(!((ano%4==0 && ano%100!=0)||ano%400==0) && (dia>28)){
            return 0;
        }
    }
    else if((mes==4 || mes==6 || mes==9 || mes==11) && (dia>30)){
        return 0;
    }
    return 1;
}