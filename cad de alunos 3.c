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
int numAluno = 0;

TAluno criarAluno();
int validar_dt(int dia, int mes, int ano);
void menu(int op);
void incluir();
void listar(TAluno a);
void listarTurma();
void alterar();
void alterar_aluno(int indice);
void excluir();
void excluir_aluno(int indice);
void reorganizar_turma(int indice);

TAluno a;

int main(){
    int o;
    menu(o);
    return 0;
}
void menu(int op){
    op=1;

    while(op!=5){
        system("cls || clear");
        //system("clear");
        printf("\n===================");
        printf("\n(1) para incluir");
        printf("\n(2) para listar");
        printf("\n(3) para alterar");
        printf("\n(4) para excluir");
        printf("\n(5) para sair");
        printf("\n===================");
        printf("\n> ");
        scanf("%d",&op);
        fflush(stdin);
        //__fpurge(stdin);
        
        if(op==1){
            incluir();
        }
        else if(op==2){
            listarTurma();
            system("pause");
        }
        else if(op==3){
            alterar();
        }
        else if(op==4){
            excluir();
        }
        else if(op==5){
            //system("cls");
            system("cls || clear");
            printf("\nSaindo...\n");
        }
        else {
            system("cls || clear");
            printf("Opcao invalida!\n");
            system("pause");

        }
    }
}
TAluno criarAluno()
{
    fflush(stdin);
    //__fpurge(stdin);
    printf("\nNome: ");
    gets(a.nome);
    fflush(stdin);
    //__fpurge(stdin);
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
        //__fpurge(stdin);

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
void incluir()
{
    char cont='s';
    
    while(!(cont=='n' || cont=='N')){
        system("cls || clear");
        if(cont=='s' || cont=='S')
        {
            if(numAluno==AL)
            {
                printf("\nLista cheia!\n");
            }
            else{
                printf("\nAluno %d\n", numAluno+1);
                turma[numAluno]=criarAluno();
                numAluno++;
            }  
        }
        else{
            printf("\nOpcao invalida!");
            printf("\nTente novamente\n");

        }
        printf("\nDeseja continuar?(S/N): ");
        scanf("%c", &cont);
        fflush(stdin);
        //__fpurge(stdin);
        
    }
}

void listar(TAluno a)
{
    printf("Nome: %s\n",a.nome);
    printf("Data de nascimento: %d/%d/%d\n", a.nasc.dia, a.nasc.mes, a.nasc.ano);
    printf("Nota: ");
    for(int i=0;i<NT;i++)
    {
        printf("[%0.2f] ", a.nota[i]);
    }
}

void listarTurma(){
    if(numAluno==0){
        printf("\nA lista esta vazia!\n");
    }
    for(int i=0;i<numAluno;i++)
    {
        printf("\nAluno %d\n", i+1);
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
void alterar(){
    int indice = -1;
    if(numAluno<=0)
    {
        printf("\nA lista esta vazia!\n");
        system("pause");
    }
    else{
       while(indice < 0 || indice >= numAluno)
       {
            listarTurma();
            printf("\nDigite o numero do aluno que deseja alterar: ");
            scanf("%d", &indice);
            indice--;
            if(indice<0 || indice>=numAluno){
                printf("\nNumero invalido\n");
            }
            else{
                alterar_aluno(indice);
            }
       } 
        //system("cls");
        system("cls || clear");
        listar(turma[indice]);
        printf("\n");
        system("pause");
    }
    
    
}
void alterar_aluno(int indice){

    fflush(stdin);
    //__fpurge(stdin);
    printf("\nNome: ");
    gets(turma[indice].nome);
    fflush(stdin);
    //__fpurge(stdin);
    printf("\nData de nascimento(dd/mm/aa): ");
    scanf("%d%d%d", &turma[indice].nasc.dia,&turma[indice].nasc.mes,&turma[indice].nasc.ano);
    
    validar_dt(turma[indice].nasc.dia, turma[indice].nasc.mes, turma[indice].nasc.ano);

    while(validar_dt(a.nasc.dia, a.nasc.mes, a.nasc.ano)==0){
        
        printf("\nData de nascimento invalida!");
        printf("\nDigite novamente(dd/mm/aa): ");
        scanf("%d%d%d", &turma[indice].nasc.dia,&turma[indice].nasc.mes,&turma[indice].nasc.ano);
        
    }

    for(int i=0;i<NT;)
    {
        printf("\nNota %d: ",i+1);
        scanf("%f",&turma[indice].nota[i]);
        fflush(stdin);
        //__fpurge(stdin);

        if(turma[indice].nota[i]<0 || turma[indice].nota[i]>10)
        {
            printf("\nDigite a nota novamente!");
        }
        else
        {
            i++;
        }
    }

}
void excluir()
{
    int indice = -1;
    if(numAluno<=0)
    {
        printf("\nA lista esta vazia!\n");
        system("pause");
    }
    else{
       while(indice < 0 || indice >= numAluno)
        {
            listarTurma();
            printf("\nDigite o numero do aluno que deseja excluir: ");
            scanf("%d", &indice);
            indice--;
            if(indice<0 || indice>=numAluno){
                printf("\nNumero invalido\n");
            }
            else{
                excluir_aluno(indice);
                
                break;
            }
        } 
        //system("cls");
        system("cls || clear");
        printf("\nAluno excluido com sucesso!");
        printf("\n");
        system("pause");
    }
}
void excluir_aluno(int indice)
{
    if(numAluno==1){
        numAluno=0;
    }
    else if((numAluno-1)==indice){
        numAluno--;
    }
    else{
        reorganizar_turma(indice);
    }
}
void reorganizar_turma(int indice)
{
    for(int i=indice;i<numAluno-1;i++)
    {
        turma[i]=turma[i+1];
    }
    numAluno--;
}