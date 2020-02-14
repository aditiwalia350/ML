//
//  main.c
//  Ques15
//
//  Created by Aditi Walia on 2/11/20.
//  Copyright © 2020 Aditi Walia. All rights reserved.
//


#include <stdio.h>
#include <unistd.h>
#include<limits.h>
#include<string.h>
#include <dirent.h>
#include<stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include<math.h>
#include <time.h>


#define N 26
#define M 54
#define T 408

double A[N][N]={0};
double B[N][M]={0};
double pi[N]={0};
int O[T]={0 ,1 ,2 ,3 ,4 ,3 ,5 ,6 ,1 ,7 ,8 ,9 ,10 ,11 ,12 ,10 ,6
,13 ,14 ,15 ,16 ,17 ,18 ,19 ,20 ,0 ,21, 2 ,22 ,23 ,24 ,25 ,18 ,16
,26 ,27 ,18 ,28 ,5 ,29 ,7 ,30 ,25 ,31 ,32 ,33 ,34 ,18 ,35 ,36 ,37
,38 ,39 ,3 ,0 ,40 ,6 ,2 ,8 ,9 ,41 ,5 ,1 ,42 ,9 ,43 ,25 ,44
,7 ,28 ,45 ,26 ,4 ,27 ,46 ,47 ,48 ,11 ,19 ,21 ,14 ,13 ,16 ,49 ,18
,22 ,15 ,25 ,17 ,35 ,0 ,23 ,29 ,37 ,20 ,25 ,12 ,49 ,36 ,50 ,38 ,39
,9 ,33 ,32 ,29 ,18 ,44 ,43 ,8 ,49 ,25 ,17 ,6 ,31 ,34 ,38 ,40 ,6
,45 ,46 ,3 ,2 ,40 ,6 ,22 ,12 ,25 ,44 ,21 ,26 ,5 ,28 ,9 ,9 ,7
,51 ,4 ,23 ,25 ,11 ,29 ,37 ,13 ,25 ,24 ,49 ,36 ,45 ,26 ,47 ,0 ,40
,6 ,2 ,35 ,9 ,15 ,53 ,10 ,20 ,48 ,33 ,39 ,16 ,44 ,5 ,21 ,7 ,19
,4 ,51 ,11 ,8 ,14 ,13 ,29 ,36 ,15 ,32 ,45 ,37 ,43 ,28 ,9 ,20 ,21
,29 ,0 ,35 ,9 ,52 ,31 ,18 ,47 ,48 ,46 ,16 ,3 ,22 ,12 ,27 ,34 ,41
,2 ,36 ,26 ,49 ,9 ,5 ,32 ,1 ,45 ,37 ,33 ,14 ,44 ,23 ,21 ,10 ,17
,47 ,29 ,24 ,27 ,7 ,36 ,0 ,49 ,45 ,26 ,43 ,33 ,41 ,37 ,4 ,39 ,2
,50 ,5 ,11 ,7 ,41 ,0 ,40 ,6 ,14 ,13 ,48 ,15 ,14 ,31 ,32 ,8 ,2
,28 ,10 ,38 ,47 ,43 ,42 ,5 ,16 ,20 ,30 ,35 ,50 ,17 ,1 ,1 ,29 ,26
,33 ,7 ,37 ,38 ,51 ,44 ,3 ,0 ,1 ,1 ,4 ,42 ,41 ,2 ,40 ,6 ,14
,11 ,16 ,12 ,25 ,13 ,25 ,52 ,19 ,40 ,49 ,51 ,15 ,22 ,0 ,41 ,0 ,6
,1 ,8 ,31 ,36 ,9 ,5 ,51 ,15 ,52 ,46 ,18 ,25 ,52 ,28 ,38 ,25 ,13
,14 ,4 ,16 ,17 ,18 ,23 ,44 ,52 ,31 ,18 ,41 ,0 ,1 ,40 ,45 ,32 ,52
,21 ,24 ,19 ,6 ,12 ,0 ,50 ,12 ,41 ,35 ,46 ,48 ,30 ,45 ,24 ,10 ,25
,52 ,16 ,46 ,40 ,40 ,20 ,16 ,36 ,2 ,8 ,9 ,12 ,34 ,19 ,1 ,17 ,51
,4 ,22 ,27 ,31 ,32 ,25 ,52 ,49 ,27 ,29 ,15 ,47 ,6 ,2 ,34 ,13 ,20
,14 ,44 ,12 ,47 ,0 ,13 ,29 ,20 ,25 ,44 ,21 ,26 ,37 ,10 ,5 ,29 ,7};


int correct_mapping[26][7] = {
{43,17,49,38,54,54,54},
{14,54,54,54,54,54,54},
{16,54,54,54,54,54,54},
{50,42,54,54,54,54,54},
{15,11,13,33,4,20,44},
{27,34,54,54,54,54,54},
{9,54,54,54,54,54,54},
{26,37,54,54,54,54,54},
{5,7,0,2,54,54,54},
{54,54,54,54,54,54,54},
{3,54,54,54,54,54,54},
{6,1,40,54,54,54,54},
{25,54,54,54,54,54,54},
{8,39,28,35,54,54,54},
{46,31,12,24,54,54,54},
{10,54,54,54,54,54,54},
{54,54,54,54,54,54,54},
{32,47,48,54,54,54,54},
{19,23,30,22,54,54,54},
{36,45,21,29,54,54,54},
{18,54,54,54,54,54,54},
{51,54,54,54,54,54,54},
{41,54,54,54,54,54,54},
{53,54,54,54,54,54,54},
{52,54,54,54,54,54,54},
{54,54,54,54,54,54,54}
};


double c[T];
double alpha[T][N];
double beta[T][N];
double gama[T][N];
double digama[T][N][N];
int minIters=200;
int iters=0;
double oldLogProb=-INFINITY;
double logProb=0.0;
int epsilon=10;
int n=100000;
int n_counter=0;
int shift=3;
double highest_score=0;



void process_corpus(char *folder_name);
void alpha_pass(void);
void beta_pass(void);
void gama_digama_pass(void);
void restimate(void);
void compute_log(void);
void check_iter(void);
void calls(void);
void reinitialize_matrices(void);




void process_corpus(char *folder_name)
{
    int counter=0;
    //Get the corpus directory
    //printf("Corpus Directory is %s \n",argv[1]);
    char cwd[PATH_MAX];
    getcwd(cwd,sizeof(cwd));
    //printf("current cwd is %s \n",cwd);
    strcat(cwd,"/");
    strcat(cwd,folder_name);
    printf("Corpus directory is %s \n",cwd);

    //read files from corpus directory to a single file
    struct dirent * entry;
    DIR *d = opendir(cwd);
    if (d == 0) {
        perror("opendir");
        exit(0);
    }
    FILE *fp1 = fopen("test.txt", "w+");
    char c;
    if(fp1==NULL){
        printf("Couldnt open file one");
        exit(0);
    }

    while ((entry = readdir(d)) != 0) {
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,folder_name);
        int result,result1,result2;
        result=strcmp(entry->d_name,".");
        result1=strcmp(entry->d_name,"..");
        result2=strcmp(entry->d_name,".DS_Store");

    
    
        if (result1==0 || result==0 || result2==0)
        {
            continue;
        }
        else{
            char *name=entry->d_name;
            strcat(cwd,"/");
            strcat(cwd,name);
            //printf("opening %s \n ",cwd);
            FILE *fp=fopen(cwd,"r");
            if(fp==NULL){
                printf("Couldnt open file two");
                continue;
            }
            
            int bufferLength = 255;
            char buffer[bufferLength];
            
            
            while(fgets(buffer, bufferLength, fp)) {
                //printf("%s\n", buffer);
                int totrim=15;
                memmove(buffer, buffer+ totrim, strlen(buffer) + 1 - totrim);
                //printf("%s\n", buffer);
                for(int i=0;i<strlen(buffer);i++){
                    if(isalpha(buffer[i]) && counter<1000000){
                        fputc(tolower(buffer[i]), fp1);
                        counter=counter+1;
                    }
                }
            }
            
    } //end of else

    }
    
    // generate A digraph matrix
    fclose(fp1);
    closedir(d);
    FILE *fp2 = fopen("test.txt", "r");
    int pre=fgetc(fp2)-'a';
    while ((c = fgetc(fp2)) != EOF){
        int post=c-'a';
        A[pre][post]=A[pre][post]+1;
        pre=post;
    }
    
    for(int i=0;i<N;i++){
        double sum=0;
        for(int j=0;j<N;j++){
            //printf("%lf", A[i][j]);
            A[i][j]=A[i][j]+5;
            sum=sum+A[i][j];
        }//printf("\n");
        for(int k=0;k<N;k++){
            A[i][k]=A[i][k]/sum;
        }
    }
    
    /*
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%lf", A[i][j]);
        }printf("\n");
    }*/
    
    
    /*
    
    FILE *fp = fopen("test.txt", "r");
    
    char plaintext[1000];
    char ciphertext[1000];
    int i=0;
    while ((c = fgetc(fp)) != EOF && i<1000){
        plaintext[i]=c;
        i++;
    }
    printf("\n plaintext is %s \n",plaintext);
    char ch;
    for(int i=0;i<1000;i++){
        
        ch = plaintext[i];

        if(ch >= 'a' && ch <= 'z'){

          ch = ch + shift;

          if(ch > 'z'){

            ch = ch - 'z' + 'a' - 1;

          }

          ciphertext[i] = ch;

        }

    }
    
    printf("\n cipher text is %s \n",ciphertext);
    */
    }
     
     
    
void reinitialize_matrices()
{
    //printf("in reinitialize matrix");
    double max=0.5;
    double min=0.4;
    double range = (max - min);
    double div = RAND_MAX / range;
    for(int i=0;i<N;i++){
        double sum=0;
        for(int j=0;j<M;j++){
            B[i][j]=min + (rand() / div);
            //printf("%lf",B[i][j]);
            sum=sum+B[i][j];
        }
        for(int k=0;k<M;k++){
            B[i][k]=B[i][k]/sum;
            //printf("%lf",B[i][k]);
        }//printf("\n");
    }
    
    double sum=0;
    for(int i=0;i<N;i++){
        pi[i]=min + (rand() / div);
        sum=sum+pi[i];
        
    }
    //printf("will print pi");
    //double sum1=0;
    for(int i=0;i<N;i++){
        pi[i]=pi[i]/sum;
        //sum1=sum1+pi[i];
        //printf("%lf \n",pi[i]);
    }        //printf("pi sum is %lf",sum1);

    
}





void alpha_pass(){
    //printf("IN ALPHA PASS");
    //compute alpha[0][i]
    c[0]=0;
    for(int i=0;i<N;i++){
        alpha[0][i]=pi[i]*B[i][O[0]];
        c[0]=c[0]+alpha[0][i];
    }
    //scale the alpha[0][i]
    c[0]=1.0/c[0];

    for(int i=0;i<N;i++){
        alpha[0][i]=c[0]*alpha[0][i];

    }
    //compute alpha[t][i]
    for(int t=1;t<T;t++){
        c[t]=0;
        for(int i=0;i<N;i++){
            alpha[t][i]=0;
            for(int j=0;j<N;j++){
                alpha[t][i]=alpha[t][i]+alpha[t-1][j]*A[j][i];
            }
            alpha[t][i]=alpha[t][i]*B[i][O[t]];
            c[t]=c[t]+alpha[t][i];
        }
        c[t]=1/c[t];
        for (int i=0;i<N;i++){
            alpha[t][i]=c[t]*alpha[t][i];
        }
    }
   
}


void beta_pass(){
    //printf("IN BETA PASS");
    //let beta[T-1][i] =1 scaled by c[T-1]
    for(int i=0;i<N;i++){
        beta[T-1][i]=c[T-1];
    }
    for(int t=T-2;t>=0;t--){
        for(int i=0;i<N;i++){
            beta[t][i]=0;
            for(int j=0;j<N;j++){
                beta[t][i]=beta[t][i]+A[i][j]*B[j][O[t+1]]*beta[t+1][j];
            }
            beta[t][i]=c[t]*beta[t][i];
        }
    }
    
}


void gama_digama_pass(){
    //printf("IN GAMA DIGAMA");
    for(int t=0;t<T-1;t++){
        double denom=0.0;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                denom=denom+(alpha[t][i]*A[i][j]*B[j][O[t+1]]*beta[t+1][j]);
            }
        }
        for(int i=0;i<N;i++){
            gama[t][i]=0;
            for(int j=0;j<N;j++){
                digama[t][i][j]=(alpha[t][i]*A[i][j]*B[j][O[t+1]]*beta[t+1][j])/denom;
                gama[t][i]=gama[t][i]+digama[t][i][j];
            }
        }
    }
    float denom=0;
    for(int i=0;i<N;i++){
        denom=denom+alpha[T-1][i];
    }
    for(int i=0;i<N;i++){
        gama[T-1][i]=(alpha[T-1][i])/denom;
    }
    
            
}


void restimate(){
    //restimate pi
    for(int i=0; i<N;i++){
        pi[i]=gama[0][i];
        //printf("%lf",pi[i]=gama[0][i]);
    }
    
    /*
    //restimate A
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            double numer=0.0;
            double denom=0.0;
            for(int t=0;t<T-1;t++){
                numer=numer+digama[t][i][j];
                denom=denom+gama[t][i];
                
            }
            A[i][j]=numer/denom;
            
        }
    }*/
    
    
    //restimate B
    //printf("restimated B");
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            double numer=0.0;
            double denom=0.0;
            for(int t=0;t<T;t++){
                if(O[t]==j){
                    numer=numer+gama[t][i];
                }
                denom=denom+gama[t][i];
        }
            B[i][j]=numer/denom;
            
            
            
        }}
}

void compute_log(){
    logProb=0.0;
    for(int i=0;i<T;i++){
        //printf("log c[i] %lf",log(c[i]));
        logProb=logProb+log(c[i]);
    }
    //printf("Log prob pre check %lf",logProb);
    logProb*=-1;
    
    //printf("LogProb Check is %lf \n", logProb);
    

}

/*
void print_matrices(){
    printf("--------Iter %d-------- \n", counter_iter);
    printf("A matrix : \n");
    printf("\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%lf  ",A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    printf("B matrix : \n");
    printf("\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            printf("%lf ",B[i][j]);
        }
        printf("\n");
    }printf("\n");
    
    double transpose[M][N];
    printf("B transpose");
    
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            //printf("%lf ",B[i][j]);
            transpose[j][i]=B[i][j];
        }
    }
    printf("\n");

    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            printf(" %lf ",transpose[i][j]);
        }printf("\n");

    }printf("\n");


    
    
    
    printf("pi matrix : ");
    for(int i=0;i<N;i++){
        printf("%lf ",pi[i]);
    }
    printf("\n");
    counter_iter=counter_iter+1;
}

*/
/*
void check_iter(){
    
    //printf("-----In iteration %d --------",iters);
    //double delta=fabs(logProb-oldLogProb);
    while((iters<minIters && n_counter<n)){
        //printf("in while for iteration %d",iters);
        //reinitialize_matrices();
        oldLogProb=logProb;
        alpha_pass();
        beta_pass();
        gama_digama_pass();
        restimate();
        compute_log();
        //print_matrices();
        iters=iters+1;
        check_iter();
        
    }
    printf("-----In iteration %d --------",n_counter);
    printf("B matrix is");
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            printf("%lf ",B[i][j]);
        }printf("\n");
    }
    
    printf("pi matrix is");
    for(int i=0;i<N;i++){
        printf("%lf ", pi[i]);
    }
    printf("Log probability is %lf",logProb);
    int right_count=0;
    for(i=0;i<N;i++){
        double highest_in_row=0;
        int highest_in_row_index=0;
        double expected_highest_in_row_index=0;

        for(j=0;j<M;j++){
            if(B[i][j]>highest_in_row)
            {
                highest_in_row=B[i][j];
                highest_in_row_index=j;
            }
            
            
        }if(i+shift<25){
            expected_highest_in_row_index=i+shift;}
        else{
            expected_highest_in_row_index=i+shift-26;
            
        }
        if(expected_highest_in_row_index==highest_in_row_index){
            right_count=right_count+1;
        }
        
        
    }
    
    printf("right count is %d / 26",right_count);
    printf("right count %% age is %lf",right_count/26.0);
    
    if(highest_score<right_count/26.0){
        highest_score=right_count/26.0;
    }
    
    if(n_counter<n){
        reinitialize_matrices();
        n_counter=n_counter+1;
        iters=0;
        check_iter();
    }
    
    else{
        printf("Highest score is %lf \n",highest_score);
        exit(0);
    
            
    }}
*/
int main(void) {

    process_corpus("Corpus");
    //reinitialize_matrices();
    //check_iter();
    FILE *fp = fopen("output.txt", "w+");
    printf("---A matrix is---- \n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%lf ", A[i][j]);
        }printf("\n");
    }


    srand( (unsigned int) time(NULL) );

    for(int i=0;i<n;i++){
        reinitialize_matrices();
        iters=0;
        while(iters<minIters){
            alpha_pass();
            beta_pass();
            gama_digama_pass();
            restimate();
            compute_log();
            iters++;
            //printf("%d \n",iters);
        }
        //printf("i is %d",i);
        printf("\n -----In iteration %d -------- \n",i);
        printf("\n Log probability is %lf \n",logProb);
        
        /* previous check
        int right_count = 0;
        for(int i=0; i<N; i++) {
            int counter=0;
            for(int j=0; j<7; j++) {
                if(correct_mapping[i][j] == 54){
                    continue;}
                if(B[i][correct_mapping[i][j]] <= 0.1)
                    break;
            }
            if(counter == 7) {
                right_count++;
            }

        }
        printf("\n right count is %d / 26 \n",right_count);
        printf("\n right count %% age is %lf \n",(right_count/26.0)*100);
        double score = right_count/26;
        if(score > highest_score){
            highest_score = score;}
        
        
        */
        
        int score=0;
        for(int i=0;i<N;i++){
            
            for(int j=0;j<M;j++){
                if(B[i][j]>=0.1 )
                {

                    for(int a=0;a<7;a++){
                        if(correct_mapping[i][a]==54){
                            continue;
                        }
                        else{
                            if(correct_mapping[i][a]==j){
                            score=score+1;
                            }
                        }
                            
                        }
                    }
                }
                    
            }
        printf("\n score is %d /54 \n",score);
        if((score/54.0)*100>highest_score){
            highest_score=(score/54.0)*100;
        }
                
                
        
        //write B and pi matrix to file
               
               
               
               fprintf(fp,"\n -----In model %d -------- \n",i);
               fprintf(fp,"\n B matrix is \n");
               for(int i=0;i<N;i++){
                   for(int j=0;j<M;j++){
                       fprintf(fp,"%lf ",B[i][j]);
                   }fprintf(fp,"\n");
               }
               
               fprintf(fp,"pi matrix is \n");
               for(int i=0;i<N;i++){
                   fprintf(fp,"%lf ", pi[i]);
               }

    }
    printf("\n highest score is %lf %% \n",highest_score);
   return 0;
}






    





