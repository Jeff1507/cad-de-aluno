#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MA 1000
#define NT 4

typedef struct{
    int dia;
    int mes;
    int ano;
}TData;

typedef struct{
    char *nome;
    float nota[NT];
    TData nasc;
}TAluno;

TAluno *_turma;
int _numAluno = 0;

void limparBuffer();
void menu();
void op_menu(int op);
void mensagem_erro(int erro);
TAluno criaAluno();
int validar_dt(int dia, int mes, int ano);
int incluir();
void listar_aluno(TAluno a);
void salvar_arquivo();
void recuperar_arquivo();

int main(){
    int op=1;

    while(op!=5){
        menu();
        scanf("%d", &op);
      //  limparBuffer();
        fflush(stdin);
        system("cls");
        //system("clear");
        op_menu(op);
    }
    return 0;
}
void limparBuffer()
{
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}
void menu(){
    system("cls");
    //system("clear");
    printf("\n===================");
    printf("\n(1) para incluir");
    printf("\n(2) para listar");
    printf("\n(3) para alterar");
    printf("\n(4) para excluir");
    printf("\n(5) para sair");
    printf("\n===================");
    printf("\n> ");
}
void op_menu(int op){
    int erro ;//opS=-1;
    if(op<1 || op>5){
        mensagem_erro(0);
    }
    else if(op<5){
        if(op==1){
            erro=incluir();
        }
        if(erro<0){
            mensagem_erro(erro);
        }
    }
    else
    {   
        printf("\nSaindo...");
        if(_numAluno>0)
        {
            salvar_arquivo();
        }
    }
}
void mensagem_erro(int erro){
    switch (erro)
    {
    case 0:
        printf("Opcao invalida!\n");
        break;
    case -1:
        printf("\nLista cheia!\n");
        break;
    case -10:
        printf("\nErro de alocacao de memoria!\n");
        break;
    
    default: printf("ERRO!\n");
        break;
    }
    system("pause");
}
int incluir(){
    char cont='s';
    while(!(cont=='n' || cont=='N')){
        if(cont=='s' || cont=='S'){
            if(_numAluno==MA){
                return -1;
            }
            if(_numAluno==0){
                _turma=(TAluno*)malloc(1*sizeof(TAluno));
            }
            else{
                _turma=(TAluno*)realloc(_turma,(_numAluno+1) * sizeof(TAluno));
            }
            if(!_turma){
                return -10;
            }
            printf("\nAluno %d", _numAluno+1);
            _turma[_numAluno]=criaAluno();

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
TAluno criaAluno(){
    TAluno a;
    char strAux[100];
    //int erro=-1;

    //limparBuffer();
    fflush(stdin);
    printf("\nNome: ");
    gets(strAux);
    a.nome=(char*)malloc((strlen(strAux)+1)*sizeof(char));
    strcpy(a.nome,strAux);
   // limparBuffer();
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
int validar_dt(int dia, int mes, int ano)
{
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
void listar_aluno(TAluno a)
{
    printf("Nome: %s\n",a.nome);
    printf("Data de nascimento: %d/%d/%d\n", a.nasc.dia, a.nasc.mes, a.nasc.ano);
    printf("Nota: ");
    for(int i=0;i<NT;i++)
    {
        printf("[%0.2f] ", a.nota[i]);
    }
}
void salvar_arquivo()
{
    int i, j;

    FILE *pArq;

    pArq = fopen("alunos.txt", "w");

    if(pArq==NULL){
        printf("Nao foi possivel criar o arquivo!");
        exit(0);
    }
    for(i=0;i<_numAluno;i++)
    {
        fprintf(pArq, "%s;", _turma[i].nome);
        fprintf(pArq, "%d/", _turma[i].nasc.dia);
        fprintf(pArq, "%d/", _turma[i].nasc.mes);
        fprintf(pArq, "%d/", _turma[i].nasc.ano);
        for(j=0;j<NT;j++){
            fprintf(pArq, "%0.2f#", _turma[i].nota[j]);
        }
        fprintf(pArq, "%c", '\n');
        fclose(pArq);
    }
}
void recuperar_arquivo()
{
    int i; //sep;
    char str[100],c;

    FILE *pArq;

    pArq = fopen("alunos.txt", "r");
    if(pArq){
        i=0;
        //sep=0;
        while(!feof(pArq)){
            c=fgetc(pArq);
            if ((c!='\n') && (c!=';') && (c!='/') && (c!='#') && (c!=EOF))
            {
               str[i]=c;
               i++; 
            }
            else if((c=='\n') || (c==';') || (c=='/') || (c=='#')){
                str[i]='\0';
                i=0;

                if(c==';'){
                    if(_numAluno==0){
                        _turma=(TAluno*)malloc(1*sizeof(TAluno));
                    }
                    else{
                        _turma=(TAluno*)realloc(_turma, (_numAluno+1) *sizeof(TAluno));
                    }
                    _turma[_numAluno].nome=(char*)malloc((strlen(str)+1)*sizeof(char));
                    strcpy(_turma[_numAluno].nome, str);
                }
            }

            
        }
    }
    fclose(pArq);
}