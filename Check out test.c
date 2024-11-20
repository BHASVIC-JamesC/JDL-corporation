//
// Created by taylo on 15/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getbill(char data[7][12][20]);






int main(void){

        //firstname surname dob age children days board guests newspaper rooms Id
    char data[7][12][20] = {
        {"james","cook","22/09/2007","16","0","2","FB","3","N","3","cook1234"},
        {"emma","smith","10/05/1992","31","1","1","BB","5","Y","1","smith2345"},
        {"liam","johnson","15/08/1985","38","2","2","HB","7","N","6","johnson6789"},
        {"olivia","brown","28/11/2001","22","0","1","FB","4","Y","2","brown4521"},
        {"noah","williams","04/02/1995","29","1","2","FB","10","N","4","williams7890"},
        {"sophia","martin","19/07/1988","35","3","2","HB","6","Y","5","martin3456"}
    };



    getbill(data);
    return 0;
}
int getbill(char data[7][12][20]) {
    int person = 0;
    char who[20];
    //gets who is checking out
    printf("Enter your ID:");
    scanf("%s",&who);
    for (int i = 0;i<7;i++) {
        if (strcmp(who,data[i][10])==0) {
            person = i;
        }
    }
    //just gets some of the data from the array and makes it a variable
    char paper = data[person][8];
    float total_bill = 0;
    float Roomcost = 0;
    int children = data[person][4];
    int age = data[person][3];
    float adultboard = 0;
    float childboard = 0;
    float total_board = 0;
    int rooms = data[person][9];
    int days = data[person][5];
    int adults = data[person][7] - data[person][4];

    // adds 5.5 on to total if there is paper
    if (paper == 'Y'){
        total_bill = total_bill + 5.5;
    }
    //checks how many rooms someone has and then gets the roomcost
    if(rooms == 1 || rooms == 2) {
        Roomcost =  rooms * 100 * days;
    }
    else if(rooms == 3) {
        Roomcost = rooms *85 * days;
    }
    else if(rooms == 4 || rooms == 5) {
        Roomcost = rooms * 75 * days;
    }
    else if(rooms == 6) {
        Roomcost = rooms * 50 * days;
    }
    // gives discount if over 65
    if (age >= 65){
        Roomcost = Roomcost * 0.9;
    }
    //sees what board they got then gets the childs one
    if (children >= 1){
        if (strcmp(data[person][6], "FB") == 0){
            childboard = children * 20;
        }
        else if(strcmp(data[person][6], "HB") == 0){
            childboard = children * 15;
        }
        else if(strcmp(data[person][6], "BB") == 0){
            childboard = children * 5;
        }
    //divides by 2 as they are under 16
    childboard = childboard /2;
    }
    //does food cost for adults
    if (strcmp(data[person][6], "FB") == 0){
        adultboard = adults * 20;
    }
    else if(strcmp(data[person][6], "HB") == 0){
        adultboard = adults * 15;
    }
    else if(strcmp(data[person][6], "BB") == 0){
        adultboard = adults * 5;
    }

    //gets total food bill
    total_board = childboard + adultboard;
    //gets total bill
    total_bill = total_bill + Roomcost + total_board;
                //firstname surname ID childboard adultboard Roomcost Total
    printf("\n%s %s \n%s \n%f \n%f \n%f \nTotal:%f",data[person][0],data[person][1], data[person][10], childboard, adultboard, Roomcost, total_bill);
    //removes the person from the data
    for(int i=0;i<10;i++) {
        strcpy(data[person][i] , data[person +1][i]);
    }

    printf("\nThank You For staying");
    return 0;
}



