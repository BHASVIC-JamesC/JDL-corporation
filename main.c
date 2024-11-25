#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//check in subroutines
void checkIn();


//dinner subroutines
void dinner(char userDetails[12][24]);
int eligible(char bookingIDdinner[20]);
void findTable(char bookingIDdinner[20], char userDetails[12][24]);
void quitProgram(char userDetails[12][24]);

//check out
int getbill();


char data[7][12][24] = {0};
char tables[2][3][12];
int guest=0;
int main(void) {
    int run = 1;
    char userDetails[12][24] = {0};    // Initialize user details


    printf("Welcome to Kashyyk Hotel\n");
    while (run == 1) {
        char userChoice[5];
        printf("Would you like to check in(a), Book dinner(b) or check out(c):");
        fflush(stdin);
        scanf(" %s", &userChoice);
        int length = strlen(userChoice);
        if(length > 1) {
            userChoice[0] = 'd';
        }
        switch (userChoice[0]) {
            case 'a':
                checkIn(data, userDetails);
            break;
            case 'b':
                dinner(userDetails);
            break;
            case 'c':
                getbill();
            break;
            default:
                printf("That is not a valid option. Please try again.\n");
            break;
        }
    }

    return 0;
}


void checkIn(char userDetails[12][24]) {
    int state = 0;
    for(int x = 0; x<=5;x++) {
        if(data[x][8][0] == 0){
            state = 0;
            break;}
        else {
            state = 1;
        }
    }
    if(state == 1) {
        printf("we are full right now,sorry!\n");
        return;
    }
    char firstName[20], lastName[20], board[4], newspaper[2], bookingID[24], temp[20],term,term2,term3;
    int day, month, year, age,kids,guests, adults, days, room, valid = 0, random,dayinteger,monthinteger,yearinteger,number,number2,number3,nameValid,validDOB;
    srand(time(NULL));
    do {
        nameValid = 0;
        printf("Enter your first name:");
        fflush(stdin);
        scanf("%s",firstName);
        printf("\nEnter your surname:");
        fflush(stdin);
        scanf("%s",lastName);
        for(int letter = 0;letter<strlen(firstName);letter++){
            if(isdigit(firstName[letter])) {
                nameValid = 1;
            }
        }
        for(int letter = 0;letter<strlen(lastName);letter++){
            if(isdigit(lastName[letter])) {
                nameValid = 1;
            }
        }
        if(strlen(firstName)>150 || strlen(lastName)> 150 || nameValid == 1) {
            printf("\ninvalid names entered. Do better.\n");
        }

    }
    while(strlen(firstName)>150 || strlen(lastName)> 150 || nameValid == 1);
    // Date of birth and age validation
    do {
        validDOB =  1;
        printf("What is your \ndate of birth?Enter day,month,and year(dd/mm/yy):");
        fflush(stdin);
        scanf("%d/%d/%d", &day, &month, &year);
        int currentYear = 2024;
        if(year == 0) {
            age = currentYear - 2000;}

        else if(year == 8 && month == 12) {
            age = 10;
        }
        else if(year > 8 && year < 24) {
            age = 10;
        }
        else if(year == 59 && month == 12) {
            age = 64;
        }
        else {
            age = currentYear - (year < 24 ? 2000 + year : 1900 + year);
        }
        if (age < 16) {
            printf("You must be at least 16 years old to check in.\n");
        }
        if(day > 31 || day<0||month<0|| month>12) {
            validDOB = 0;
            printf("please enter valid days/month/year.\n");
        }
        if(month == 2 && day > 29 && year%4 == 0 || month == 2 && day > 28 && year%4 != 0) {
            printf("please enter valid days/month/year.\n");
        }
        if( month == 4 && day == 31 || month == 6 && day == 31 || month == 9 && day == 31|| month == 11 && day == 31) {
            printf("please enter valid days/month/year.\n");
        }


    } while (age < 16 || day > 31 || month > 12|| day<0||month<0 || day ==0 || month ==0 ||month == 2 && day > 29 && year%4 == 0 || month == 2 && day > 28 && year%4 != 0||month == 4 && day == 31 || month == 6 && day == 31 || month == 9 && day == 31|| month == 11 && day == 31);

    // Guest and children validation
    do {
        printf("Enter the number of guests (max 4):");
        fflush(stdin);
        number = scanf("%d%c", &guests,&term);
        if ((number != 2 || term != '\n') || (guests < 1 || guests>4)) {
            printf("Invalid number of guests. Please enter between 1 and 4.\n");
        }
    } while ((number != 2 || term != '\n') || (guests < 1 || guests>4));

    do {
        printf("\nHow many adults will be staying with you?:");
        fflush(stdin);
        number2 = scanf("%d%c", &adults,&term2);
        if ((number2 != 2 || term2 != '\n') || (adults > guests || adults<1)) {
            printf("Invalid number of adults. Please enter between 0 and %d.\n", guests);
        }
    } while ((number2 != 2 || term2 != '\n') || (adults > guests || adults<1));

    kids = guests - adults;

    // Board type selection
    do {
        printf("\nWhat board type do you want to book?\nFull Board(FB)\tHalf Board(HB)\tBed and Breakfast(BB):");
        fflush(stdin);
        scanf("%s", board);
        if (strcmp(board, "FB") != 0 && strcmp(board, "HB") != 0 && strcmp(board, "BB") != 0) {
            printf("Invalid board type. Please try again.\n");
        }
    } while (strcmp(board, "FB") != 0 && strcmp(board, "HB") != 0 && strcmp(board, "BB") != 0);

    // Stay duration
    do {
        printf("\nHow many days will you be staying with us?:");
        fflush(stdin);
        scanf("%d", &days);
        if (days <= 0) {
            printf("Invalid number of days. Please enter a positive number.\n");
        }
    } while (days <= 0);

    // Newspaper preference
    do {
        printf("\nDo you want a daily newspaper? (Y/N): ");
        fflush(stdin);
        scanf(" %c", newspaper);
        if (newspaper[0] != 'Y' && newspaper[0] != 'N') {
            printf("Invalid option. Please enter Y or N.\n");
        }
    } while (newspaper[0] != 'Y' && newspaper[0] != 'N');

    // Room selection
    do {
        printf("What room would you like to book (1-6):\n"
               "Room 1(100)\tRoom 2(100)\tRoom 3(85)\tRoom 4(75)\tRoom 5(75)\tRoom 6(50):");
        fflush(stdin);
        number3 = scanf("%d%c", &room,&term3);
        if ((room < 1 || room > 6) || ( number3 != 2 || term3 != '\n')) {
            printf("Invalid room number.\nPlease select between 1 and 6.\n");
            valid = 0;
        } else {
            valid = 1;
            for (int i = 0; i < 7; i++) {
                if (data[i][8][0] != '\0' && atoi(data[i][8]) == room) {
                    printf("Sorry, that room is unavailable.\nPlease pick another.\n");
                    valid = 0;
                    break;
                }
            }
        }
    } while (!valid);

    // Generate booking ID
    random = 1000 + rand() % 9000;
    snprintf(temp, sizeof(temp), "%d", random);
    snprintf(bookingID, sizeof(bookingID), "%s%d", lastName, random);
    printf("Booking ID:%s\n", bookingID);
    // Save to `data` and `userDetails`

    for(int k = 0; k<=6;k++) {
        if(data[k][8][0] ==0){
            guest = k;
            break;
        }
    }

    snprintf(data[guest][0], 24, "%s", firstName);
    snprintf(data[guest][1], 24, "%s", lastName);
    snprintf(data[guest][2], 24, "%d", age);
    snprintf(data[guest][3], 24, "%d", kids);
    snprintf(data[guest][4], 24, "%d", adults);
    snprintf(data[guest][5], 24, "%s", board);
    snprintf(data[guest][6], 24, "%d", days);
    data[guest][7][0] = newspaper[0];
    snprintf(data[guest][8], 24, "%d", room);
    snprintf(data[guest][9], 24, "%s", bookingID);



    printf("Check-in complete!\n");
}


//dinner stuff now

void dinner(char userDetails[12][24]) {
    char bookingIDdinner[20];
    printf("\nHello! Welcome to dinner.\n");
        printf("\n");



    printf("\nWhat's your booking ID?:");
    fflush(stdin);
    fgets(bookingIDdinner, sizeof(bookingIDdinner), stdin);
    bookingIDdinner[strcspn(bookingIDdinner, "\n")] = '\0'; // Remove trailing newline

    if (eligible(bookingIDdinner) == 1) {
        findTable(bookingIDdinner,userDetails);
    } else {
        printf("Sorry, you're not eligible for dinner. Only Full Board (FB) and Half Board (HB) guest are allowed.\n");
        quitProgram(userDetails);
    }
}


int eligible(char bookingIDdinner[20]) {


    for (int i = 0; i < 7; i++) {
        if (strcmp(data[i][9], bookingIDdinner) == 0) {
            if (strcmp(data[i][5], "FB") == 0 || strcmp(data[i][5], "HB") == 0) {
                printf("Booking ID '%s' is eligible for dinner.\n", bookingIDdinner);
                return 1; // Eligible
            } else {
                printf("Booking ID '%s' found, but board type '%s' is not eligible.\n", bookingIDdinner, data[i][5]);
            }
        }
    }
    printf("Booking ID '%s' not found or not eligible.\n", bookingIDdinner);
    return 0; // Not eligible
}


void findTable(char bookingIDdinner[20], char userDetails[12][24]) {
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
    fflush(stdin);
    scanf("%s", tableChoice);

    // Process table choice
    if (strcmp(tableChoice, "Endor7") == 0 && strcmp(tables[0][0], "") == 0) {
        strcpy(tables[0][0], bookingIDdinner);
        printf("\nReservation confirmed for Endor at 7pm.\n");
    } else if (strcmp(tableChoice, "Naboo7") == 0 && strcmp(tables[0][1], "") == 0) {
        strcpy(tables[0][1], bookingIDdinner);
        printf("\nReservation confirmed for Naboo at 7pm.\n");
    } else if (strcmp(tableChoice, "Tatooine7") == 0 && strcmp(tables[0][2], "") == 0) {
        strcpy(tables[0][2], bookingIDdinner);
        printf("\nReservation confirmed for Tatooine at 7pm.\n");
    } else if (strcmp(tableChoice, "Endor9") == 0 && strcmp(tables[1][0], "") == 0) {
        strcpy(tables[1][0], bookingIDdinner);
        printf("\nReservation confirmed for Endor at 9pm.\n");
    } else if (strcmp(tableChoice, "Naboo9") == 0 && strcmp(tables[1][1], "") == 0) {
        strcpy(tables[1][1], bookingIDdinner);
        printf("\nReservation confirmed for Naboo at 9pm.\n");
    } else if (strcmp(tableChoice, "Tatooine9") == 0 && strcmp(tables[1][2], "") == 0) {
        strcpy(tables[1][2], bookingIDdinner);
        printf("\nReservation confirmed for Tatooine at 9pm.\n");
    } else {
        printf("That is not a valid table/time or it is already booked. Try again later.\n");
    }

    quitProgram(userDetails);
}


//check out
int getbill() {
    int person = -1;
    char who[20];

    // Get the ID of the person checking out
    printf("Enter your ID:");
    scanf("%s", who);

    // Find the person by ID
    for (int i = 0; i < 7; i++) {
        if (strcmp(who, data[i][9]) == 0) {
            person = i;
            break;
        }
    }

    if (person == -1) {
        printf("Error: ID not found.\n");
        return -1;
    }

    // Extract and convert data
    char *paper = data[person][7];
    int kids = atoi(data[person][3]);
    int age = atoi(data[person][2]);
    int rooms = atoi(data[person][8]);
    int days = atoi(data[person][6]);
    int adults = atoi(data[person][4]);
    int guests = kids + adults;

    float total_bill = 0;
    float Roomcost = 0;
    float adultboard = 0;
    float childboard = 0;
    float total_board = 0;

    // Add cost for newspaper
    if (strcmp(paper, "Y") == 0) {
        total_bill += 5.5;
    }

    // Calculate room cost
    if (rooms == 1 || rooms == 2) {
        Roomcost = rooms * 100 * days;
    } else if (rooms == 3) {
        Roomcost = rooms * 85 * days;
    } else if (rooms == 4 || rooms == 5) {
        Roomcost = rooms * 75 * days;
    } else if (rooms == 6) {
        Roomcost = rooms * 50 * days;
    }

    // Discount for senior citizens
    if (age >= 65) {
        Roomcost *= 0.9;
    }

    // Calculate board cost for kids
    if (kids >= 1) {
        if (strcmp(data[person][5], "FB") == 0) {
            childboard = kids * 20;
        } else if (strcmp(data[person][5], "HB") == 0) {
            childboard = kids * 15;
        } else if (strcmp(data[person][5], "BB") == 0) {
            childboard = kids * 5;
        }
        childboard /= 2;  // Half-price for kids under 16
    }

    // Calculate board cost for adults
    if (strcmp(data[person][5], "FB") == 0) {
        adultboard = adults * 20;
    } else if (strcmp(data[person][5], "HB") == 0) {
        adultboard = adults * 15;
    } else if (strcmp(data[person][5], "BB") == 0) {
        adultboard = adults * 5;
    }

    // Calculate total board cost
    total_board = childboard + adultboard;

    // Total bill
    total_bill += Roomcost + total_board;

    // Output the bill
    printf("\n%s %s\nID: %s\nChild Board: %.2f\nAdult Board: %.2f\nRoom Cost: %.2f\nTotal: %.2f\n",
           data[person][0], data[person][1], data[person][9], childboard, adultboard, Roomcost, total_bill);

    // Remove the person from the data array
    for (int j = 0; j < 12; j++) {
        memset(data[person][j], 0, sizeof(data[person][j])); // Clear memory
    }



    printf("\nThank you for staying!\n");
    for(int k = 0;k<3;k++) {
        for(int j = 0; j<4 ; j++) {
            if(strcmp(tables[k][j],who) == 0) {
                strcpy(tables[k][j], "");
            }
        }
    }
    return 0;


}
//quit program

void quitProgram(char userDetails[12][24]) {
    for (int i = 0; i < 12; i++) {
        memset(userDetails[i], 0, 24); // Clear each row of the 2D array
    }
}




