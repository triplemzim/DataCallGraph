#include <stdio.h>
#include <stdbool.h>

int alive=100;
int pera=0;

void getAdmission(){
    printf("I am admitted in IIT, " );
    printf("Alive percentage: %d\n",alive);
}


void pass1to6thsem(){
    int i=0;
    for(i=0; i<6; i++){
        appearSemesterFinal();
        failInExam();
        while(true){
            AppearSupply();
            if(passSupply()==1) break;
        }



    }

}

void appearSemesterFinal(){
    pera=pera+1;
    alive= alive-4;
}

void failInExam(){
    pera=pera+2;
    alive= alive-1;
}

void AppearSupply(){
    pera=pera+1;
    alive= alive-5;
}

int passSupply(){
    pera=pera-1;
    return 1;
}

void takeInternshipCourse(){
    pera = pera+1;
    alive= alive -1;
}
void submitReasearch_Project(){
    pera = pera-1;

}

void graduate(){
    pera = pera-1;
     printf("I am graduating from IIT, " );
    printf("Alive percentage: %d\n",alive);
}


int main(){
    getAdmission();
    pass1to6thsem();
    takeInternshipCourse();
    submitReasearch_Project();
    graduate();

    return 0;
}
