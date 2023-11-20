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
    scanf("%d",&getUserInput);
    return getUserInput;
}

void placeDot3in(int x, int y, int z, int inhibitor[9], char boxSet[9]){
    int skiP = 0;
    int CPUchoose = 0;
    while (skiP != 1){
        CPUchoose = getRandomNumber3(x,y,z);
        if (inhibitor[CPUchoose] == 0) {
            boxSet[CPUchoose] = 'o';
            inhibitor[CPUchoose] = 2;
            skiP = 1;
        }else{
            skiP = 0;
        }
    }
}

void placeDot2in(int x, int y, int inhibitor[9], char boxSet[9]){
    int CPUchoose = 0;
    int skiP = 0;
    while (skiP != 1){
        CPUchoose = returnRandomNumber(x,y);
        if (inhibitor[CPUchoose] == 0) {
            boxSet[CPUchoose] = 'o';
            inhibitor[CPUchoose] = 2;
            skiP = 1;
        }else{
            skiP = 0;
        }
    }
}

void gameEngine(){
    int inhibitor[9] = {0,0,0,0,0,0,0,0,0};//initializing inhibitors
    int playerChoose = 0;//initializing Player Selection Variable
    int CPUchoose = 0;//Initializng CPU Selection Variable
    int skiP = 0;
    int maxProberHA = 0, maxProberVA = 0, maxProberDA = 0;
    int maxProberH = 0, maxProberV = 0, maxProberD = 0;
    int DrawV = 0, DrawH = 0, DrawD = 0;
    int ProberH[3], ProberV[3], ProberD[3];
    char boxSet[9] = {'#', '#', '#',
                      '#', '#', '#',
                      '#', '#', '#'};//Initializing Boxes
    for (int i=0; i > -1; i++){
        maxProberHA = 0, maxProberVA = 0, maxProberDA = 0;
        maxProberH = 0, maxProberV = 0, maxProberD = 0;
        DrawV = 0, DrawH = 0, DrawD = 0;
        system("clear");
        playerChoose = initDisplay(boxSet)-1;
        if(inhibitor[playerChoose] == 0) { //Check if the selected slot is inhibited, if not mark the slot as X
            boxSet[playerChoose] = 'x';
            inhibitor[playerChoose] = 1;
        } else {
            printf("Inhibitors active for selected position !, Retry...");
            continue;
        }
        //Plotting the CPU draw, (if iteration = 0 randomize else calcualte the probability)
        if (i == 0){ //Randomizing the CPU Move for the first iterration
            CPUchoose = returnRandomNumber(0,8);
            if (inhibitor[CPUchoose] == 0) {
                boxSet[CPUchoose] = 'o';
                inhibitor[CPUchoose] = 2;
            }
        } else { // Calulating Probability to be able to win
            for(int i = 0; i < 9; i++) {
                if (inhibitor[i] == 2){
                    //Horizontal Total
                    if (i < 3){
                        ProberH[0] ++;
                    }
                    if (i < 6 && i > 3){
                        ProberH[1] ++;
                    }
                    if (i < 9 && i > 6){
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
                } else if (inhibitor[i] == 1) {
                    //Horizontal Total
                    if (i < 3){
                        ProberH[0] --;
                    }
                    if (i < 6 && i > 3){
                        ProberH[1] --;
                    }
                    if (i < 9 && i >6){
                        ProberH[2] --;
                    }
                    //Vertical Total
                    if (i == 0 || i == 3 || i == 6){
                        ProberV[0] --;
                    }
                    if (i == 1 || i == 4 || i == 7){
                        ProberV[1] --;
                    }
                    if (i == 2 || i == 5 || i == 8){
                        ProberV[2] --;
                    }
                    //Diagnonal Total
                    if (i == 0 || i == 4 || i == 8){
                        ProberD[0] --;
                    }
                    if (i == 2 || i == 4 || i == 6){
                        ProberD[1] --;
                    }
                }
            }
            //Maximum Probability on Horizontal
            if (ProberH[0] > ProberH[1]){
                if (ProberH[0] > ProberH[2]){
                    maxProberH = ProberH[0];
                    maxProberHA = 0;
                } else if (ProberH[2] > ProberH[0]) {
                    maxProberH = ProberH[2];
                    maxProberHA = 2;
                }
            } else if (ProberH[1] > ProberH[0]){
                if (ProberH[1] > ProberH[2]){
                    maxProberH = ProberH[1];
                    maxProberHA = 1;
                } else if(ProberH[2] > ProberH[1]){
                    maxProberH = ProberH[2];
                    maxProberHA = 2;
                }
            } else if (ProberH[1] == ProberH[0] && ProberH[0] == ProberH[2]){
                //BRAINDRAW
                DrawH ++;
            } else {
                maxProberH = ProberH[2];
                maxProberHA = 2;
            }
            //Maximum Probability Vertical
            if (ProberV[0] > ProberV[1]){
                if (ProberV[0] > ProberV[2]){
                    maxProberV = ProberV[0];
                    maxProberVA = 0;
                } else if (ProberV[2] > ProberV[0]){
                    maxProberV = ProberV[2];
                    maxProberVA = 2;
                }
            } else if (ProberV[1] > ProberV[0]){
                if (ProberV[1] > ProberV[2]){
                    maxProberV = ProberV[1];
                    maxProberVA = 1;
                } else if (ProberV[2] > ProberV[1]){
                    maxProberV = ProberV[2];
                    maxProberVA = 2;
                } else if (ProberV[1] == ProberV[0] && ProberV[0] == ProberV[2]){
                    //BRAINDRAW
                    DrawV ++;
                } else {
                    maxProberV = ProberV[2];
                    maxProberVA = 2;
                }
            }
            //Maximum Probability Diagonal
            if (ProberD[0] > ProberD[1]){
                maxProberD = ProberD[0];
                maxProberDA = 0;
            } else if(ProberD[0] < ProberD[1]){
                maxProberD = ProberD[1];
                maxProberDA = 1;
            } else{
                DrawD ++;
            }
            if (DrawD == DrawH && DrawH == DrawV){
                placeDot2in(8,2,inhibitor,boxSet);
                skiP = 0;
            } else  {
                //GameEngine - Try To win Mode
                if(maxProberH > maxProberV){
                    if(maxProberD > maxProberH){
                        if (maxProberDA == 0){
                            placeDot3in(0,4,8,inhibitor,boxSet);
                        } else if (maxProberDA == 1) {
                            placeDot3in(2,4,6,inhibitor,boxSet);
                        }
                    } else {
                        if (maxProberHA == 0){
                            placeDot2in(0,2,inhibitor,boxSet);
                        } else if (maxProberHA == 1) {
                            placeDot2in(4,6,inhibitor,boxSet);
                        }
                        else if (maxProberHA == 2) {
                            placeDot2in(7,9,inhibitor,boxSet);
                        }
                    }
                } else if(maxProberV > maxProberH){
                    if(maxProberD > maxProberV){
                        if (maxProberDA == 0){
                            placeDot3in(0,4,8,inhibitor,boxSet);
                            skiP = 0;
                        } else if (maxProberDA == 1) {
                            placeDot3in(2,4,6,inhibitor,boxSet);
                        }
                    } else {
                        if (maxProberVA == 0){
                            placeDot3in(0,3,6,inhibitor,boxSet);
                        } else if (maxProberVA == 1) {
                            placeDot3in(1,4,7,inhibitor,boxSet);
                        }
                        else if (maxProberVA == 2) {
                            placeDot3in(2,5,8,inhibitor,boxSet);
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