#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int returnRandomNumber(int x, int y){
    srand(time(NULL));
    return rand() % (x + y);
}

int getRandomNumber3(int num1, int num2, int num3) {
    srand(time(NULL));
    int possible_values[] = {num1, num2, num3};
    int num_values = sizeof(possible_values) / sizeof(possible_values[0]);
    
    if (num_values == 0) {
        // Handle the case where the array is empty
        // You can return an error code, print a message, or take appropriate action
        return -1;
    }

    int random_index = rand() % num_values;
    int random_number = possible_values[random_index];
    return random_number;
}

int initDisplay(char boxSet[9]) {
    int getUserInput = 0; 
    printf("\nPic Your Input\n%c%c%c\n%c%c%c\n%c%c%c\n >", boxSet[0], boxSet[1], boxSet[2], 
                                         boxSet[3], boxSet[4], boxSet[5], 
                                         boxSet[6], boxSet[7], boxSet[8]);
    scanf("%d", &getUserInput);
    return getUserInput;
}

void gameEngine(){
    int inhibitor[9] = {0,0,0,0,0,0,0,0,0};//initializing inhibitors
    int playerChoose = 0;//initializing Player Selection Variable
    int CPUchoose = 0;//Initializng CPU Selection Variable
    int skiP = 0;
    int maxProberHA = 0, maxProberVA = 0, maxProberDA = 0;
    int maxProberH = 0, maxProberV = 0, maxProberD = 0;
    int ProberH[3], ProberV[3], ProberD[3];
    char boxSet[9] = {'#', '#', '#',
                      '#', '#', '#',
                      '#', '#', '#'};//Initializing Boxes
    for (int i=0; i > -1; i++){
        system("clear");
        playerChoose = initDisplay(boxSet)-1;
        if(inhibitor[playerChoose] == 0) { //Check if the selected slot is inhibited, if not mark the slot as X
            boxSet[playerChoose] = 'x';
            inhibitor[playerChoose] = 1;
        } else {
            printf("Inhibitors active for selected position !, Retry...");
        }
        //Plotting the CPU draw, (if iteration = 0 randomize else calcualte the probability)
        if (i == 0){ //Randomizing the CPU Move for the first iterration
            CPUchoose = returnRandomNumber(0,8);
            if (inhibitor[CPUchoose] == 0) {
                boxSet[CPUchoose] = 'o';
                inhibitor[CPUchoose] = 2;
            }
        } else { // Calulating Probability to be able to win
            for(int i = 0; i < 9; i++){
                if (inhibitor[i] == 2){
                    //Horizontal Total
                    if (i < 3){
                        ProberH[0] ++;
                    }
                    if (i < 6){
                        ProberH[1] ++;
                    }
                    if (i < 9){
                        ProberH[2] ++;
                    }
                    //Vertical Total
                    if (i == 0 || i == 3 || i == 6){
                        ProberV[0] ++;
                    }
                    if (i == 1 || i == 4 || i == 7){
                        ProberV[1] ++;
                    }
                    if (i == 2 || i == 5 || i == 8){
                        ProberV[2] ++;
                    }
                    //Diagnonal Total
                    if (i == 0 || i == 4 || i == 8){
                        ProberD[0] ++;
                    }
                    if (i == 2 || i == 4 || i == 6){
                        ProberD[1] ++;
                    }
                }
                //Maximum Probability on Horizontal
                if (ProberH[0] > ProberH[1]){
                    if (ProberH[0] > ProberH[3]){
                        maxProberH = ProberH[0];
                        maxProberHA = 0;
                    } else {
                        maxProberH = ProberH[3];
                        maxProberHA = 3;
                    }
                } else {
                    if (ProberH[1] > ProberH[3]){
                        maxProberH = ProberH[1];
                        maxProberHA = 1;
                    } else {
                        maxProberH = ProberH[3];
                        maxProberHA = 3;
                    }
                }
                //Maximum Probability Vertical
                if (ProberV[0] > ProberV[1]){
                    if (ProberV[0] > ProberV[3]){
                        maxProberV = ProberV[0];
                        maxProberVA = 0;
                    } else {
                        maxProberV = ProberV[3];
                        maxProberVA = 3;
                    }
                } else {
                    if (ProberV[1] > ProberV[3]){
                        maxProberV = ProberV[1];
                        maxProberVA = 1;
                    } else {
                        maxProberV = ProberV[3];
                        maxProberVA = 3;
                    }
                }
                //Maximum Probability Diagonal
                if (ProberD[0] > ProberD[1]){
                    maxProberD = ProberD[0];
                    maxProberDA = 0;
                } else {
                    maxProberD = ProberD[1];
                    maxProberDA = 1;
                }
                //Placing the courser based on probability
                if(maxProberH > maxProberV){
                    if(maxProberD > maxProberH){
                        if (maxProberDA == 0){
                            while (skiP == 1){
                                CPUchoose = getRandomNumber3(0,4,8);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        } else if (maxProberDA == 1) {
                            CPUchoose = getRandomNumber3(2,4,6);
                            while (skiP == 1){
                                CPUchoose = getRandomNumber3(0,4,8);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        }
                    } else {
                        if (maxProberHA == 0){
                            while (skiP == 1){
                                CPUchoose = returnRandomNumber(0,2);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        } else if (maxProberHA == 1) {
                            while (skiP == 1){
                                CPUchoose = returnRandomNumber(4,6);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        }
                         else if (maxProberHA == 2) {
                            while (skiP == 1){
                                CPUchoose = returnRandomNumber(7,9);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        }
                        
                    }
                } else {
                    if(maxProberD > maxProberV){
                        if (maxProberDA == 0){
                            while (skiP == 1){
                                CPUchoose = getRandomNumber3(0,4,8);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        } else if (maxProberDA == 1) {
                            CPUchoose = getRandomNumber3(2,4,6);
                            while (skiP == 1){
                                CPUchoose = getRandomNumber3(0,4,8);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        }
                    } else {
                        if (maxProberVA == 0){
                            while (skiP == 1){
                                CPUchoose = getRandomNumber3(0,3,6);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        } else if (maxProberVA == 1) {
                            while (skiP == 1){
                                CPUchoose = getRandomNumber3(1,4,7);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        }
                         else if (maxProberVA == 2) {
                            while (skiP == 1){
                                CPUchoose = getRandomNumber3(2,5,8);
                                if (inhibitor[CPUchoose] == 0) {
                                    boxSet[CPUchoose] = 'o';
                                    inhibitor[CPUchoose] = 2;
                                    skiP = 1;
                                }else{
                                    skiP = 0;
                                }
                            }
                            skiP = 0;
                        }
                        
                    }
                }
            }
        }
    }
}




int main(){
    gameEngine();
}