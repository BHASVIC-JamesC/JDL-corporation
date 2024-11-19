#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
int checkIn();

char data[7][12][24];
int guest = 0;
char   firstName[20], lastName[20], board[4], newspaper[2], bookingID[24], temp[20], temp2[20];
int guests, kids,adults, days, day, month, year, daysa, age, room, valid = 0,  random;
int main(void){
    int personalDetails;
    char userChoice;
    printf("Welcome to Kashyyk Hotel\n");
    printf("Would you like to check in(a), Book dinner(b) or Check out(c):");
    fflush(stdin);
    scanf("%c", &userChoice);
    switch (userChoice) {
        case'a':
            checkIn();
            break;
        case'b':
            //dinner()
            break;
        case'c':
            //checkOut()
            break;
        default:
            printf("that is not a valid option.");
            break;
    }
    return 0;
}
int checkIn() {
    srand(time(NULL));
    printf("Enter your full name:");
    fflush(stdin);
    scanf("%s %s", &firstName, &lastName);
    printf("%s %s\n", firstName, lastName);
    do {
        printf("What is your date of birth, enter day month then year in this format (dd/mm/yy):");
        fflush(stdin);
        scanf("%d/%d/%d",&day,&month,&year);
        fflush(stdin);
        printf("%d/%d/%d\n", day, month, year);
        if (year>24) {
            daysa = (14 - day) + 12*(11 - month) + 365*(24 + (100-year));
        }
        else {
            daysa = (14 - day) + 12*(11 - month) + 365*(24 - year);
        }
        age = daysa / 365;
        printf("%d\n", age);
    }while (age < 16);
    do {
        printf("Enter your guests:");
        fflush(stdin);
        scanf("%d", &guests);
        if (guests > 4) {
            printf("The max guests is 4. Enter again\n");
        }
    }while (guests > 4 || guests < 0);
    do {
        printf("How many children will be staying with you:");
        fflush(stdin);
        scanf("%d", &kids);
        if (kids >= guests) {
            printf("Enter a valid amount of children\n");
            guests = 2;
        }
    }while (kids > guests);
    do {
        adults = guests-kids;
        printf("What board type do you want to book:\nFull Board(FB)\tHalf Board(HB)\tBed and Breakfast(BB):");
        fflush(stdin);
        scanf("%s",board);
        printf("%s",board);
        if(strcmp(board,"FB") != 0 && strcmp(board,"HB") != 0 && strcmp(board,"BB") != 0 ) {
            printf("You entered an invalid board. Please try again.\n");
        }
    }while (strcmp(board,"FB") != 0 && strcmp(board,"HB") != 0 && strcmp(board,"BB") != 0);
    do {
        printf("\nHow many days will you be staying with us:");
        fflush(stdin);
        scanf("%d", &days);
        if(days < 0) {
            printf("You entered an invalid day. Please try again.\n");
        }
    }while(days < 0);
    do {
        printf("Do you want a daily newspaper? (Y) or (N):");
        fflush(stdin);
        scanf("%c", &newspaper);
        if (newspaper[0] != 'Y' && newspaper[0] != 'N') {
            printf("Enter a valid newspaper option 'Y' or 'N'");
        }
    }while (newspaper[guest] != 'Y' && newspaper[guest] != 'N');
    do {
        printf("What Room would you like to book\n(Prices are displayed per day in pounds):\nRoom 1(100)\tRoom 2(100)\tRoom 3(85)\tRoom 4(75)\tRoom 5(75)\tRoom 6(50):");
        fflush(stdin);
        scanf("%d", &room);
        if (room > 6 || room < 1) {
            printf("You entered an invalid room. Please try again.\n");
        }
        else {
            valid = 1;
        }
        for (int i = 0; i <6 ; i++) {
            if(data[i][8][0] == room && i != guest) {
                valid = 0;
                printf("Sorry that room is unavailable, please pick another\n");
                break;
            }
        }
    }while(valid == 0);
    random = 999 + rand() % (9999 - 999);
    itoa(random, temp, 10);
    strcpy(temp2, lastName);
    strcat(temp2, temp);
    strcpy(bookingID, temp2);
    printf("Booking ID: %s\n", bookingID);
    strncpy(data[guest][0], firstName,24);
    strncpy(data[guest][1], lastName, 24);
    snprintf(data[guest][2], 24,"%d", age);
    snprintf(data[guest][3], 24, "%d", kids);
    snprintf(data[guest][4], 24, "%d", adults);
    strncpy(data[guest][5], board, 24);
    snprintf(data[guest][6], 24, "%d", days);
    data[guest][7][0] = newspaper[guest];
    snprintf(data[guest][8], 24, "%d", room);
    strncpy(data[guest][9], bookingID, 24);
    guest++;
    return guest, data;
}
