//
//  main.c
//  homework2
//
//  Created by Aditi Walia on 2/11/20.
//  Copyright © 2020 Aditi Walia. All rights reserved.
//
//
//  ques10b.c
//  A
//
//  Created by Aditi Walia on 2/5/20.
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
#define M 26
#define T 300

double A[N][N]={0};
double B[N][M]={0};
double pi[N]={0};
int O[T];
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
int n=1000;
int n_counter=0;
int shift=3;
double highest_score=0;

int i=0,j=0,k=0,t=0;


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
    
    
    
    
    FILE *fp = fopen("test.txt", "r");
    
    char plaintext[1000];
    char ciphertext[1000];
    i=0;
    while ((c = fgetc(fp)) != EOF && i<T){
        plaintext[i]=c;
        i++;
    }
    printf("\n plaintext is %s \n",plaintext);
    char ch;
    for(int i=0;i<T;i++){
        
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
    
    for(int i=0;i<T;i++){
        O[i]=ciphertext[i]-'a';
    }}

void reinitialize_matrices()
{
    //printf("Will print B matrix");
    
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
        }
    }
    
    double sum=0;
    for(int i=0;i<N;i++){
        pi[i]=min + (rand() / div);
        sum=sum+pi[i];
        
    }
    
    for(int i=0;i<N;i++){
        pi[i]=pi[i]/sum;
    }
    
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
        logProb=logProb+log(c[i]);
    }
    logProb*=-1;
    
    //printf("LogProb is %lf \n", logProb);
    

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
        printf("\n -----In Model %d -------- \n",i);
        printf("\n Log probability is %lf \n",logProb);
        int right_count=0;
        for(int i=0;i<N;i++){
            double highest_in_row=0;
            int highest_in_row_index=0;
            double expected_highest_in_row_index=0;

            for(int j=0;j<M;j++){
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

        printf("\n right count is %d / 26 \n",right_count);
        printf("\n right count %% age is %lf \n",(right_count/26.0)*100);
        
        if(highest_score<(right_count/26.0)*100){
            highest_score=(right_count/26.0)*100;
        }
        //write B and pi matrix to file
               
               
               
               fprintf(fp,"\n -----In iteration %d -------- \n",i);
               fprintf(fp,"\n B matrix is \n");
               for(int i=0;i<N;i++){
                   for(j=0;j<M;j++){
                       fprintf(fp,"%lf ",B[i][j]);
                   }fprintf(fp,"\n");
               }
               
               fprintf(fp,"pi matrix is \n");
               for(int i=0;i<N;i++){
                   fprintf(fp,"%lf ", pi[i]);
               }

    }
    printf("\n highest score is %lf \n",highest_score);
   return 0;
}






    




