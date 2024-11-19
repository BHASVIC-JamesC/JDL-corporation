#include <stdio.h>
#include <string.h>

void dinner(char tables[2][3][12], char data[7][12][20], char userDetails[12]);
int eligible(char data[7][12][20], char bookingIDdinner[20]);
void findTable(char tables[2][3][12], char data[7][12][20], char bookingIDdinner[20], char userDetails[12]);
void quitProgram(char userDetails[12]);

int main(void) {
    int run = 1;
    char data[7][12][20] = {
        {"james","cook","16","0","2","FB","3","N","3","cook1234"},
        {"emma","smith","31","1","1","BB","5","Y","1","smith2345"},
        {"liam","johnson","38","2","2","HB","7","N","6","johnson6789"},
        {"olivia","brown","22","0","1","FB","4","Y","2","brown4521"},
        {"noah","williams","29","1","2","FB","10","N","4","williams7890"},
        {"sophia","martin","35","3","2","HB","6","Y","5","martin3456"}
    };

    char tables[2][3][12] = {
        {"","",""},
        {"","",""}
    };
    while(run == 1) {

        char userDetails[12][12] = {"james","cook","22/09/2007","16","0","2","FB","3","N","3","cook1234"};

        dinner(tables, data, userDetails);
    }
    return 0;
}

void dinner(char tables[2][3][12], char data[7][12][20], char userDetails[12]) {
    char bookingIDdinner[20];
    printf("\nHello! Welcome to dinner.\n");

    if (eligible(data, bookingIDdinner) == 1) {
        findTable(tables, data, bookingIDdinner, userDetails);
    } else {
        quitProgram(userDetails);
    }
}

int eligible(char data[7][12][20], char bookingIDdinner[20]) {
    printf("\nwhat's your booking ID?: ");
    scanf("%s",bookingIDdinner);


    for (int i = 0; i < 7; i++) {
        if (strcmp(data[i][10], bookingIDdinner) == 0) {
            if (strcmp(data[i][6], "FB") == 0 || strcmp(data[i][6], "HB") == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void findTable(char tables[2][3][12], char data[7][12][20], char bookingIDdinner[20], char userDetails[12]) {
    char tableChoice[10];
    int available = 0;

    // Display available tables
    if (strcmp(tables[0][0], "") == 0) {
        printf("\nEndor is available at 7pm.\n");
        available = 1;
    }
    if (strcmp(tables[0][1], "") == 0) {
        printf("Naboo is available at 7pm.\n");
        available = 1;
    }
    if (strcmp(tables[0][2], "") == 0) {
        printf("Tatooine is available at 7pm.\n");
        available = 1;
    }
    if (strcmp(tables[1][0], "") == 0) {
        printf("Endor is available at 9pm.\n");
        available = 1;
    }
    if (strcmp(tables[1][1], "") == 0) {
        printf("Naboo is available at 9pm.\n");
        available = 1;
    }
    if (strcmp(tables[1][2], "") == 0) {
        printf("Tatooine is available at 9pm.\n");
        available = 1;
    }

    if (!available) {
        printf("\nNo tables available right now.\n");
        quitProgram(userDetails);
        return;
    }

    printf("\nWhich table and time would you like to book?\nFor example, type: Naboo7 for table Naboo at 7pm\nEnter: ");
    scanf("%s",tableChoice);


    // Process table choice
    if (strcmp(tableChoice, "Endor7") == 0 && strcmp(tables[0][0], "") == 0) {
        strcpy(tables[0][0], bookingIDdinner);
        printf("\nthat's all good for you :) \n");
    } else if (strcmp(tableChoice, "Naboo7") == 0 && strcmp(tables[0][1], "") == 0) {
        strcpy(tables[0][1], bookingIDdinner);
        printf("\nthat's all good for you :) \n");
    } else if (strcmp(tableChoice, "Tatooine7") == 0 && strcmp(tables[0][2], "") == 0) {
        strcpy(tables[0][2], bookingIDdinner);
        printf("\nthat's all good for you :) \n");
    } else if (strcmp(tableChoice, "Endor9") == 0 && strcmp(tables[1][0], "") == 0) {
        strcpy(tables[1][0], bookingIDdinner);
        printf("\nthat's all good for you :) \n");
    } else if (strcmp(tableChoice, "Naboo9") == 0 && strcmp(tables[1][1], "") == 0) {
        strcpy(tables[1][1], bookingIDdinner);
        printf("\nthat's all good for you :) \n");
    } else if (strcmp(tableChoice, "Tatooine9") == 0 && strcmp(tables[1][2], "") == 0) {
        strcpy(tables[1][2], bookingIDdinner);
        printf("\nthat's all good for you :) \n");
    } else {
        printf("That is not a valid table/time or it is already booked. Try again later.\n");
    }

    quitProgram(userDetails);
}

void quitProgram(char userDetails[12]) {
    char empty[12] = "";
    strcpy(userDetails, empty);
}

