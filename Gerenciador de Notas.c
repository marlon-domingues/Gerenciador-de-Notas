#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define TAM_FNOME 20
#define TAM_NOME 15
#define TAM_SNOME 15
#define N_NOTAS  3

typedef struct {
    char nome[TAM_NOME];             //Informações de um aluno
    char sobre_nome[TAM_SNOME];
    int nUSP;
    float nota[N_NOTAS];
    float media;
}ALUNO;

void menu(){
    system("cls");
    printf("\n----------------------------------------\n");  //Menu inicial
    printf("            GERENCIADOR DE NOTAS\n\n");
    printf("1-Turmas.\n");
    printf("2-Procurar aluno.\n");
    printf("3-Gerar estatisticas da turma.\n");
    printf("4-Visualixar turma.\n");
    printf("5-Encerrar o sistema\n");
    printf("----------------------------------------\n");
}

void turma(){

    int op;
    char fnome[20];
    FILE *arq;

    system("cls");
    printf("Digite o nome de uma turma existente ou crie uma nova:");    //gera um arquivo .txt para representar uma sala ou acessa uma já criada
    scanf("%s",fnome);
    strcat(fnome,".txt");
    arq=fopen(fnome,"a");

    if(arq==NULL){
        printf("Erro ao abrir o arquivo.");
        getch();
        return 0;
    } 

    fclose(arq);
    system("cls");

    printf("Para cadastrar algum aluno nessa turma digite 1.");
    scanf("%i",&op);

    if (op==1) cadastrar_aluno(fnome);

    getch();

}

void cadastrar_aluno(char fnome[TAM_FNOME]){   //função de cadastro do aluno

    int i,op=1;
    float media;
    ALUNO aluno;
    FILE *arq;
    
    do{ 
        media=0;
        system("cls");
        printf("\n-------------------------------------------------------------\n");
        printf("                          TURMA: %s\n",fnome);
        printf("\n-------------------------------------------------------------\n");
        printf("Digite o primeiro nome do aluno a ser cadastrado:");
        scanf("%s",&aluno.nome);
        printf("Digite o ultimo nome do aluno a ser cadastrado:");
        scanf("%s",&aluno.sobre_nome);
        printf("Digite o número USP nome do aluno a ser cadastrado:");
        scanf("%i",&aluno.nUSP);

        media=0;

        for ( i = 0; i < N_NOTAS; i++){
            printf("Digite a nota da P%i do aluno:",i+1);     //ciclo for para obter as notas do aluno
            scanf("%f",&aluno.nota[i]);
            media=media+aluno.nota[i];            
        }
        media=media/N_NOTAS;  //soma de todas as notas dividido pela quantidade de notas
        aluno.media=media;  
        arq=fopen(fnome,"a");
        fprintf(arq,"%s %s %i ",aluno.nome,aluno.sobre_nome,aluno.nUSP); //escreve no arquivo da sala
        for ( i = 0; i < N_NOTAS; i++){
            fprintf(arq,"%.2f ",aluno.nota[i]);//escreve no arquivo da sala
        }
        fprintf(arq,"%.2f\n",aluno.media);//escreve no arquivo da sala
        
        fclose(arq); 

        printf("para cadastrar mais um aluno digite 1. Para sair digite 0: ");

        scanf("%i",&op);
        
    } while (op!=0);

}

void le_turma(char fnome[TAM_FNOME]){

    int i=0;
    FILE *arq;
    ALUNO *sala;

    strcat(fnome,".txt");

    sala=(ALUNO*)malloc(sizeof(ALUNO));//vetor inicialmente com uma posição

    arq=fopen(fnome,"r");

    if(arq!=NULL){
        while(fscanf(arq, " %s %s %i %f %f %f %f",&sala[i].nome,&sala[i].sobre_nome,&sala[i].nUSP,&sala[i].nota[0],&sala[i].nota[1],&sala[i].nota[2],&sala[i].media)!=EOF){
            printf("\n-------------------------------------\n");
            printf("Nome:           %s %s\n",sala[i].nome,sala[i].sobre_nome);
            printf("Numero USP:     %i\n",sala[i].nUSP);
            printf("Nota P1:        %.2f\n",sala[i].nota[0]);
            printf("Nota P2:        %.2f\n",sala[i].nota[1]);
            printf("Nota trabalho:  %.2f\n",sala[i].nota[2]);  //impressão das informações do aluno
            printf("media:          %.2f\n",sala[i].media);
            printf("\n-------------------------------------\n");
            i++;
            sala=(ALUNO*)malloc((1+i)*sizeof(ALUNO));//vetor se ajustando conforme a quantidade de alunos na sala
        }
    }

}

void pesquisa_aluno(char fnome[TAM_FNOME], char nome[TAM_NOME]){ //função de pesquisa

    int i=0;
    FILE *arq;
    ALUNO *sala;

    sala=(ALUNO*)malloc(sizeof(ALUNO)); //vetor incial com uma posição

    strcat(fnome,".txt");

    arq=fopen(fnome,"r");

    if(arq!=NULL){
        while(fscanf(arq, " %s %s %i %f %f %f %f",&sala[i].nome,&sala[i].sobre_nome,&sala[i].nUSP,&sala[i].nota[0],&sala[i].nota[1],&sala[i].nota[2],&sala[i].media)!=EOF){
            if (strcmp(sala[i].nome,nome)==0){
                printf("\n-------------------------------------\n");
                printf("Nome:           %s %s\n",sala[i].nome,sala[i].sobre_nome);
                printf("Numero USP:     %i\n",sala[i].nUSP);
                printf("Nota P1:        %.2f\n",sala[i].nota[0]);
                printf("Nota P2:        %.2f\n",sala[i].nota[1]); //imprime a informação dos alunos com o nome pesquisado
                printf("Nota trabalho:  %.2f\n",sala[i].nota[2]);
                printf("media:          %.2f\n",sala[i].media);
                printf("\n-------------------------------------\n");
            }
            i++;
            sala=(ALUNO*)malloc((1+i)*sizeof(ALUNO));// vetor se ajustando conforme o numero de alunos na sala
        }
    }
}

void estatistica(char fnome[TAM_NOME]){ //estatistica da sala


    int i=0;
    float P1=0,P2=0,trabalho=0,final=0,aprovado=0; //inicializa as variaveis
    FILE *arq;
    ALUNO *sala;

    sala=(ALUNO*)malloc(sizeof(ALUNO)); //vetor inicial de uma posição

    strcat(fnome,".txt");

    arq=fopen(fnome,"r");

    if(arq!=NULL){
        while(fscanf(arq, " %s %s %i %f %f %f %f",&sala[i].nome,&sala[i].sobre_nome,&sala[i].nUSP,&sala[i].nota[0],&sala[i].nota[1],&sala[i].nota[2],&sala[i].media)!=EOF){
            P1=P1+sala[i].nota[0]; //soma das notas P1
            P2=P2+sala[i].nota[1];  //soma das notas P2
            trabalho=trabalho+sala[i].nota[2]; //soma das notas do trabalho
            final=final+sala[i].media; //soma das medias

            if (sala[i].media>=5) aprovado++;   //se a nota for acima da média incrementa 1 em aprovado 
            
            i++;
            sala=(ALUNO*)malloc((1+i)*sizeof(ALUNO)); //vetor se ajustando conforme a quantidade de alunos na sala
        }
        P1=P1/i; //soma das notas dividido pela quantidade de notas
        P2=P2/i;
        trabalho=trabalho/i;
        final=final/i;
        aprovado=(aprovado/i)*100; 

        printf("\nMedia P1:          %.2f\n",P1);
        printf("Media P2:          %.2f\n",P2);
        printf("Media trabalho:    %.2f\n",trabalho); //imprime as estatisticas
        printf("Media final:       %.2f\n",final);
        printf("Aprovados:         %.2f%%",aprovado);
    }
}

int main(){


    int op; //opção
    char fnome[TAM_FNOME],nome[TAM_NOME]; //nome do arquivo e nome do aluno

    do{
        menu();
        printf("Comando: "); //comando de escolha 
        scanf("%i",&op);

        switch (op){

        case 1:
            turma(); //cria ou acessa uma turma
            break;
        case 2:
            system("cls");
            printf("Digite o nome da Sala:");
            scanf("%s",fnome);
            printf("Digite o nome do aluno:");
            scanf("%s",nome);

            pesquisa_aluno(fnome,nome); //pesquisa um aluno em uma sala

            getch();

            break; 
        case 3:
            system("cls");
            printf("Digite o nome da Sala:");
            scanf("%s",fnome);

            estatistica(fnome); //estatisticas de uma sala

            getch();
            break;
        case 4:
            system("cls");
            printf("Digite o nome da Sala:");
            scanf("%s",fnome);

            le_turma(fnome); //imprime todos os alunos de uma turma

            getch();
            break;
        case 5:
            printf("Encerrando o sistema...");
            getchar();
            break;
        default:
            printf("Entrada invalida. Pressione enter para continuar...");
            getch();
            break;
        }
    } while (op!=5);
    
    getchar();
    return 0;
}