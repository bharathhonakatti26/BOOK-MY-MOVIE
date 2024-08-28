#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>

typedef struct {

    char name[100];
    char timings[3][100];

} Movie;

typedef struct {

    Movie movies[3];

} Theatre;

typedef struct {

    char theatre_names[3][100];
    char seat_type[3][100]; 
    Theatre theatre[3];
    int rates[3];                  
    
} Theatres;

#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
#define MAX_PHONE_LENGTH 10

typedef struct about_Customer{

    char user_name[100];
    char user_email[100];
    char user_password[100];
    char phone_number[MAX_PHONE_LENGTH];

}user_imformation;

//SEAT TYPE
int PREMIUM[100];
int EXECUTIVE[300];
int NORMAL[100];

// USER LOGIN 
char confirm_email[100];
char confirm_passowrd[100];

//WORKER LOGIN 
char worker_email[100];
char worker_password[100];

int file_prototype;
int id_number;

int seat_numbers[270];

int transaction_number;
int ticket_number;
int enter_ticket_number;
int rand_box_office_number;
int rand_sl_no;
int choice;

Theatres theatres;

bool validate_email_id(const char *email) {

    char mode_email[2][200] = { "@gmail.com" , "@yahoo.com" };
    int n = strlen(email);
    char *ptr = strchr(email, '@');
    int index = -1;

    if (ptr != NULL) {
        index = ptr - email; 
    }
    int j = 0;
    char pro[100];
    if (index != -1){
        for (int i = index ; i < n ; i++) {
          pro[j++] = email[i];        
        }
        pro[j] = '\0';

    }
    int i;
    int found = 0;
    for (i = 0; i < 2; i++) {
        if (strcmp(pro, mode_email[i]) == 0) {
            found = 1;
            break;
        }
    }
    if (found) {
        return true;
    } else {
        return false;
    }
    
}

bool validate_phone_number(const char *number) {
    int length = strlen(number);
    if (length != 10) 
        return false;

    for (int i = 0; i < length; i++) { 
        if (!isdigit(number[i]))
            return true;
    }
    return true; 
}

void prints_finally_ticket(int seats, int x, char *theatre_name, char *movie_name, char *show_time);

void User_Register(){

    user_imformation data ;

    printf("\n\t\t\t\tSign up  \n");
    printf("\n");
    printf("\t\tEnter your Name         :  ");
    scanf("\n");
    fgets(data.user_name,100,stdin);
    printf("\n");
   
    do
    {
        printf("\t\tEnter an email address  :  ");
        scanf("%s" , data.user_email);
        if(!validate_email_id(data.user_email)){
            printf("\t\tInvalid Email ID . Please enter again .\n");
            printf("\t\tCheck once with your Prototype .\n\n");
        }     
    } while (!validate_email_id(data.user_email));
    printf("\n");

    printf("\t\tEnter your password     :  ");
    scanf("%s", data.user_password);
    printf("\n");  

    do 
    {
        printf("\t\tEnter your Phone Number : +91 ");
        scanf("%s", data.phone_number);
        if (!validate_phone_number(data.phone_number)){
            printf("\t\tInvalid phone number. Please enter again.\n\n");
        }
    } while (!validate_phone_number(data.phone_number));

    printf("\n"); 
    printf("\t\tloading.....\n");
    sleep(5);

    srand(time(0));
    file_prototype = rand()% 9000 + 1000 ; 
        
    FILE *user_file; 

    char filename[20];
    sprintf(filename, "%d.txt", file_prototype);

    user_file = fopen(filename, "a");  
    
    fprintf(user_file, "\n");
    fprintf(user_file, "                                    NAME                     :  %s", data.user_name);
    fprintf(user_file, "                                    EMAIL                    :  %s \n", data.user_email);
    fprintf(user_file, "                                    Customer file number     :  %d \n", file_prototype);
    fprintf(user_file, "                                    PASSWORD                 :  %s \n", data.user_password);
    fprintf(user_file, "                                    PHONE NUMBER             :  %s \n\n", data.phone_number);
    fprintf(user_file, "                    -------------------------------------------------------------------");
    fprintf(user_file, "\n                                            History or Recent Ticket\n");

    fclose(user_file);

    FILE *reg_info = fopen("Register Details.txt", "a");
    fprintf(reg_info , "\n");

    fprintf(reg_info , "                                    *******************************************************************\n\n");

    fprintf(reg_info , "                                            NAME OF THE USER          :  %s" , data.user_name);
    fprintf(reg_info , "                                            EMAIL OF THE USER         :  %s \n" , data.user_email);
    fprintf(reg_info , "                                            PASSWORD OF THE USER      :  *************\n");
    fprintf(reg_info , "                                            CUSTOMER FILE NUMBER      :  %d \n", file_prototype);
    fprintf(reg_info , "                                            PHONE NUMBER OF THE USER  :  %s \n" , data.phone_number);

    fclose(reg_info); 

    FILE *con = fopen("User Confidential.txt", "a");
    fprintf(con, "%s %s %d\n", data.user_email , data.user_password , file_prototype);
    fclose(con);

    printf("\n\t\tCustomer ID Number : %d \n" , file_prototype);
    printf("\t\tNOTE ---> You need this *Customer ID Number* everytime when you need to login \n\n");
    printf("\n\t\t\t****** Registration successful ! ******\n\n");

}

int user_login() {

    user_imformation loginUser;

    printf("\n");
    printf("\t\tEnter your Email Id  : ");
    scanf("%s", confirm_email);
    printf("\n");
    printf("\t\tEnter your password  : ");
    scanf("%s", confirm_passowrd);
    printf("\n");
    printf("\t\tEnter your ID Number : ");
    scanf("%d", &id_number);

    FILE *con = fopen("User Confidential.txt", "r");
  
    while (fscanf(con , "%s %s %d", loginUser.user_email , loginUser.user_password , &file_prototype) == 3) {
        if (strcmp(confirm_email, loginUser.user_email) == 0 
            && strcmp(confirm_passowrd, loginUser.user_password ) == 0 
                && id_number == file_prototype ) {
                
            fclose(con);
            return 1; 
        }
    }

    fclose(con);

    return 0; 
     
}

int Customerprofile(){

    FILE *profileFile;
    char line[100];

    char profileFilename[20];
    sprintf(profileFilename, "%d.txt", id_number);
    profileFile = fopen(profileFilename, "r");

    printf("\n\t\t\t\t\t\tPROFILE\n\n");
    for (int i = 0 ; i < 7 ; i++) {
        if (fgets(line, sizeof(line), profileFile) != NULL) {
            printf("%s", line);
            sleep(1);
        } else {
            break; 
        }
    }

    fclose(profileFile);

    return 0;
}

int view_past_history(){

    #define MAX_LINE_LENGTH 1024
    #define NUM_LINES 29

    printf("\n\t1. VIew my recent Tickect \n");
    printf("\t2. View all my Tickect \n\n");

    while (1){
        printf("\tEnter your choice : ");
        if (scanf("%d", &choice) != 1) {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            while (getchar() != '\n'); 
            continue;
        }
        if (choice < 1 || choice > 2) {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            continue;
        }
            break;
    }

    if (choice == 1 ){

            char recenthistoryfile[20];
            sprintf(recenthistoryfile, "%d.txt", id_number);
            FILE *file = fopen(recenthistoryfile, "r");
        if (file == NULL) {
            printf("Error opening file.\n");
            return 0;
        }

        char *lines[NUM_LINES];
        for (int i = 0; i < NUM_LINES; i++) {
            lines[i] = malloc(MAX_LINE_LENGTH);
            if (lines[i] == NULL) {
                printf("Error allocating memory.\n");
                return 0;
            }
        }

        int index = 0;
        while (fgets(lines[index % NUM_LINES], MAX_LINE_LENGTH, file)) {
            index++;
        }

        int start = index >= NUM_LINES ? (index % NUM_LINES) : 0;
        int count = index >= NUM_LINES ? NUM_LINES : index;

        for (int i = 0; i < count; i++) {
            printf("%s", lines[(start + i) % NUM_LINES]);
        }

        for (int i = 0; i < NUM_LINES; i++) {
            free(lines[i]);
        }

        fclose(file);

    }

    else if (choice == 2 ){

        FILE *historyFile;
        char line[10000];
        int start_line = 10;
        int current_line = 0;

        char historyfile[20];
        sprintf(historyfile, "%d.txt", id_number);
        historyFile = fopen(historyfile, "r");
        printf("\n                                            These are your Tickets History\n");
        printf("                                         ---------------------------------------\n\n");

        while (fgets(line, sizeof(line), historyFile)) {
            
            current_line++;

            printf("%s", line);
        }
        printf("\n\n");

        fclose(historyFile);
    }

    return 0;
}

// FUNCTION TO CHECK UP REGISTER DETAILS

void check_up_register_details(){

    FILE *registerFile;
    registerFile = fopen("Register Details.txt" , "r");
    char line[10000];
    while(fgets(line,50,registerFile) != NULL){
    printf("%s" , line);
    }
    printf("\n\t\t\t\t*************************** !! DONE !! ***************************\n\n");
}

// FUNCTION TO CHECK UP LOGIN DETAILS

void check_up_login_details(){

    FILE *loginFile;
    loginFile = fopen("Login Details.txt" , "r");
    char line[10000];
    while(fgets(line,50,loginFile) != NULL){
    printf("%s" , line);
  }
    printf("\n\t\t\t\t*************************** !! DONE !! ***************************\n\n");

}

void Theatre_Seat_Matrix() {

    FILE *seatmatrix;
    seatmatrix = fopen("Theatre_Seat_Matrix.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    {
        printf("%s", line);
    }

}

void seat_matrix_theater_1_movie_1() {

    FILE *seatmatrix;
    seatmatrix = fopen("t1m1seats.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    printf("\t\t\t\t");
    {
        printf("%s", line);
    }
    printf("\n\n");
}

void seat_matrix_theater_1_movie_2() {

    FILE *seatmatrix;
    seatmatrix = fopen("t1m2seats.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    printf("\t\t\t\t");
    {
        printf("%s", line);
    }
    printf("\n\n");
}

void seat_matrix_theater_1_movie_3() {

    FILE *seatmatrix;
    seatmatrix = fopen("t1m3seats.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    printf("\t\t\t\t");
    {
        printf("%s", line);
    }
    printf("\n\n");
}

void seat_matrix_theater_2_movie_1() {

    FILE *seatmatrix;
    seatmatrix = fopen("t2m1seats.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    printf("\t\t\t\t");
    {
        printf("%s", line);
    }
    printf("\n\n");
}

void seat_matrix_theater_2_movie_2() {

    FILE *seatmatrix;
    seatmatrix = fopen("t2m2seats.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    printf("\t\t\t\t");
    {
        printf("%s", line);
    }
    printf("\n\n");
}

void seat_matrix_theater_2_movie_3() {

    FILE *seatmatrix;
    seatmatrix = fopen("t2m3seats.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    printf("\t\t\t\t");
    {
        printf("%s", line);
    }
    printf("\n\n");
}

void seat_matrix_theater_3_movie_1() {

    FILE *seatmatrix;
    seatmatrix = fopen("t3m1seats.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    printf("\t\t\t\t");
    {
        printf("%s", line);
    }
    printf("\n\n");
}

void seat_matrix_theater_3_movie_2() {

    FILE *seatmatrix;
    seatmatrix = fopen("t3m2seats.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    printf("\t\t\t\t");
    {
        printf("%s", line);
    }
    printf("\n\n");
}

void seat_matrix_theater_3_movie_3() {

    FILE *seatmatrix;
    seatmatrix = fopen("t3m3seats.txt", "r");
    char line[1000];
    while (fgets(line , 50, seatmatrix) != NULL)
    printf("\t\t\t\t");
    {
        printf("%s", line);
    }
    printf("\n\n");
}

void clear_file(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fclose(file);
    } else {
        printf("Error opening file.\n");
    }
}

void refresh_seats(){
    
    do
    {
           
        printf("\n\t\t\t\tSELECT THEATRE THEN MOVIE\n\n");
        for (int i = 0; i < 3; i++) {
            printf("\t\t\t%d. %s \n" , i+1 , theatres.theatre_names[i] );
        }
        printf("\t\t\t0. Back \n");
        printf("\n");

        while (1){
            printf("\tEnter your choice : ");
            if (scanf("%d", &choice) != 1) {
                sleep(2);
                printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                while (getchar() != '\n'); 
                continue;
            }
            if (choice < 0 || choice > 3) {
                sleep(2);
                printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                continue;
            }
            break;
        }

        switch (choice)
        {
            case 1:

                printf("\n\t\t\t\tSELECT MOVIE AND SHOW TIME\n\n");
                for(int i =  0 ; i <3; i++){
                printf("\n\t\t\t%d. %-20s \t-  %s " , i+1 , theatres.theatre[0].movies[i].name, theatres.theatre[0].movies[i].timings[0] );  
                }
                printf("\n\n");

                while (1)
                {
                    printf("\tEnter your choice : ");
                    if (scanf("%d", &choice) != 1) {
                        sleep(2);
                        printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choice < 1 || choice > 3) {
                        sleep(2);
                        printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                        continue;
                    }
                    break;
                }
                    switch (choice)
                    {
                    case 1:
                        printf("\n\t\t\tRefreshing seats ..... \n");
                        sleep(2);
                        clear_file("t1m1seats.txt");
                        printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
                        break;
                    
                    case 2:
                        printf("\n\t\t\tRefreshing seats ..... \n");
                        sleep(2);
                        clear_file("t1m2seats.txt");
                        printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
                        
                        break;
                    case 3:
                        printf("\n\t\t\tRefreshing seats ..... \n");
                        sleep(2);
                        clear_file("t1m3seats.txt");
                        printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
                        break;
                    }
                                        
                    break;
                    
                case 2:

                    printf("\n\t\t\t\tSELECT MOVIE AND SHOW TIME\n\n");
                    for(int i =  0 ; i <3; i++){
                    printf("\n\t\t\t%d. %-25s \t  -  %s " , i+1 , theatres.theatre[1].movies[i].name, theatres.theatre[1].movies[i].timings[0] );  
                    }
                    printf("\n\n");

                    while (1)
                    {
                        printf("\tEnter your choice : ");
                        if (scanf("%d", &choice) != 1) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            while (getchar() != '\n'); 
                            continue;
                        }
                        if (choice < 1 || choice > 3) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            continue;
                        }
                        break;
                    }
                    switch (choice)
                    {
                    case 1:
                        printf("\n\t\t\tRefreshing seats ..... \n");
                        sleep(2);
                        clear_file("t2m1seats.txt");
                        printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
                        break;
                    
                    case 2:
                        printf("\n\t\t\tRefreshing seats ..... \n");
                        sleep(2);
                        clear_file("t2m2seats.txt");
                        printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
                        break;
                    case 3:
                        printf("\n\t\t\tRefreshing seats ..... \n");
                        sleep(2);
                        clear_file("t2m3seats.txt");
                        printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
                        break;
                    }
                    
                        
                    break;

                case 3:

                    printf("\n\t\t\t\tSELECT MOVIE AND SHOW TIME\n\n");
                    for(int i =  0 ; i <3; i++){
                    printf("\n\t\t\t%d. %-25s \t  -  %s " , i+1 , theatres.theatre[2].movies[i].name, theatres.theatre[2].movies[i].timings[0] );  
                    }
                    printf("\n\n");

                    while (1)
                    {
                        printf("\tEnter your choice : ");
                        if (scanf("%d", &choice) != 1) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            while (getchar() != '\n'); 
                            continue;
                        }
                        if (choice < 1 || choice > 3) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            continue;
                        }
                        break;
                    }
                    switch (choice)
                    {
                    case 1:
                        printf("\n\t\t\tRefreshing seats ..... \n");
                        sleep(2);
                        clear_file("t3m1seats.txt");
                        printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
                        break;
                    
                    case 2:
                        printf("\n\t\t\tRefreshing seats ..... \n");
                        sleep(2);
                        clear_file("t3m2seats.txt");
                        printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
                        break;
                    case 3:
                        printf("\n\t\t\tRefreshing seats ..... \n");
                        sleep(2);
                        clear_file("t3m3seats.txt");
                        printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
                        break;
                    }
                                        
                    break;

                }
                
            
            } while (choice != 0);

}

void worker_interface(){

    printf("\n\n\t\t\t\t\t\t<<<< WELCOME TO WORKER SPACE >>>>\n");

    do
    {
        printf("\n\t1. Check up Register Details \n");
        printf("\t2. Check up Login Datails \n");
        printf("\t3. View about Ticket \n");
        printf("\t4. Refresh the Seats \n");
        printf("\t5. Refresh Login Datails \n");
        printf("\t6. Logout\n\n");

        while (1)
        {
            printf("\tEnter your choice : ");
            if (scanf("%d", &choice) != 1) 
            {
                sleep(2);
                printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                while (getchar() != '\n'); 
                continue;
            }
            if (choice < 1 || choice > 6) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            continue;
            }
            break;
        }

        switch (choice)
        {
        case 1:
            printf("\n\n\t\t\t*************************** These are the Registrations ***************************\n\n");
            check_up_register_details();
            break;

        case 2:
            printf("\n\n\t\t\t*************************** These are the Recent Login ***************************\n\n");
            check_up_login_details();
            break;

        case 3:

            do
            {
           
                printf("\n\t\t\t\tSELECT THEATRE THEN MOVIE\n\n");
                for (int i = 0; i < 3; i++) {
                    printf("\t\t\t%d. %s \n" , i+1 , theatres.theatre_names[i] );
                }
                printf("\t\t\t0. Back \n");
                printf("\n");

                while (1)
                {
                    printf("\tEnter your choice : ");
                    if (scanf("%d", &choice) != 1) 
                    {
                        sleep(2);
                        printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choice < 0 || choice > 3) 
                    {
                    sleep(2);
                    printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                    continue;
                    }
                    break;
                }

                switch (choice)
                {
                case 1:

                    printf("\n\t\t\t\tSELECT MOVIE AND SHOW TIME\n\n");
                    for(int i =  0 ; i <3; i++){
                    printf("\n\t\t\t%d. %-20s \t-  %s " , i+1 , theatres.theatre[0].movies[i].name, theatres.theatre[0].movies[i].timings[0] );  
                    }
                    printf("\n\n");

                    while (1)
                    {
                        printf("\tEnter your choice : ");
                        if (scanf("%d", &choice) != 1) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            while (getchar() != '\n'); 
                            continue;
                        }
                        if (choice < 1 || choice > 3) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            continue;
                        }
                        break;
                    }
                    switch (choice)
                    {
                    case 1:
                        printf("\n\n\t\t\tTHESE ARE THE BOOKED SEAT NUMBER \n\n");
                        seat_matrix_theater_1_movie_1();
                        break;
                    
                    case 2:
                       printf("\n\n\t\t\tTHESE ARE THE BOOKED SEAT NUMBER \n\n");
                        seat_matrix_theater_1_movie_2();
                        break;
                    case 3:
                       printf("\n\n\t\t\tTHESE ARE THE BOOKED SEAT NUMBER \n\n");
                        seat_matrix_theater_1_movie_3();
                        break;
                    }
                                        
                    break;
                    
                case 2:

                    printf("\n\t\t\t\tSELECT MOVIE AND SHOW TIME\n\n");
                    for(int i =  0 ; i <3; i++){
                    printf("\n\t\t\t%d. %-25s \t  -  %s " , i+1 , theatres.theatre[1].movies[i].name, theatres.theatre[1].movies[i].timings[0] );  
                    }
                    printf("\n\n");

                    while (1)
                    {
                        printf("\tEnter your choice : ");
                        if (scanf("%d", &choice) != 1) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            while (getchar() != '\n'); 
                            continue;
                        }
                        if (choice < 1 || choice > 3) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            continue;
                        }
                        break;
                    }
                    switch (choice)
                    {
                    case 1:
                       printf("\n\n\t\t\tTHESE ARE THE BOOKED SEAT NUMBER \n\n");
                        seat_matrix_theater_2_movie_1();
                        break;
                    
                    case 2:
                       printf("\n\n\t\t\tTHESE ARE THE BOOKED SEAT NUMBER \n\n");
                        seat_matrix_theater_2_movie_2();
                        break;
                    case 3:
                       printf("\n\n\t\t\tTHESE ARE THE BOOKED SEAT NUMBER \n\n");
                        seat_matrix_theater_2_movie_3();
                        break;
                    }
                    
                        
                    break;

                case 3:

                    printf("\n\t\t\t\tSELECT MOVIE AND SHOW TIME\n\n");
                    for(int i =  0 ; i <3; i++){
                    printf("\n\t\t\t%d. %-25s \t  -  %s " , i+1 , theatres.theatre[2].movies[i].name, theatres.theatre[2].movies[i].timings[0] );  
                    }
                    printf("\n\n");

                    while (1)
                    {
                        printf("\tEnter your choice : ");
                        if (scanf("%d", &choice) != 1) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            while (getchar() != '\n'); 
                            continue;
                        }
                        if (choice < 1 || choice > 3) {
                            sleep(2);
                            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                            continue;
                        }
                        break;
                    }
                    switch (choice)
                    {
                    case 1:
                       printf("\n\n\t\t\tTHESE ARE THE BOOKED SEAT NUMBER \n\n");
                        seat_matrix_theater_3_movie_1();
                        break;
                    
                    case 2:
                       printf("\n\n\t\t\tTHESE ARE THE BOOKED SEAT NUMBER \n\n");
                        seat_matrix_theater_3_movie_2();
                        break;
                    case 3:
                       printf("\n\n\t\t\tTHESE ARE THE BOOKED SEAT NUMBER \n\n");
                        seat_matrix_theater_3_movie_3();
                        break;
                    }
                                        
                    break;

                }
                
            
            } while (choice != 0);

            break;

        case 4:
            refresh_seats();
            break;
        
        case 5:

            printf("\n\t\t\tRefreshing Login Details ..... \n");
            sleep(2);
            FILE *file = fopen("Login Details.txt", "w");
            if (file != NULL) {
                fclose(file);
            } else {
                printf("Error opening file.\n");
            }
            printf("\n\t\t\tSuccessfully Refreshed ..... ! \n\n");
            
            break;

        case 6:
            sleep(1);
            printf("\n\t\t\t****** logout successfully ! ******\n\n");
            break;

        }      

    } while (choice != 6);
    
}

void loginhistory(){

    //GIVES DATE AND TIME 
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    FILE *login_info = fopen("Login Details.txt", "a");

    fprintf(login_info , "				*******************************************************************\n\n");

    fprintf(login_info , "                                            EMAIL OF THE USER      :  %s\n" , confirm_email);
    fprintf(login_info , "                                            PASSWORD OF THE USER   :  *************\n");
    fprintf(login_info , "                                            ID Number              :  %d\n" , id_number);
    fprintf(login_info , "                                            LOGIN DETAILS          :  %02d:%02d:%02d  %02d-%02d-%04d\n\n" , tm.tm_hour, tm.tm_min, tm.tm_sec , tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900 ); 

    fclose(login_info);
    printf("\n");

}

// THIS FUNCTION CHECK'S THE SEAT NUMBER CONFORMATION

#define MAX_SEAT 270
#define MIN_SEAT 1

void enter_seat_number(int num_seats, char *filename) {
    int seat_number;
    FILE *file;

    for (int i = 0; i < num_seats; i++) {
        printf("\n\t\tEnter seat number %d to reserve : ", i + 1);
        scanf("%d", &seat_number);

        if (seat_number < MIN_SEAT || seat_number > MAX_SEAT) {
            printf("\t\tInvalid seat number. Please enter a seat number between %d and %d.\n\n", MIN_SEAT, MAX_SEAT);
            i--;
            continue;
        }

        file = fopen(filename, "r");
        if (file != NULL) {
            int reserved_seat;
            while (fscanf(file, "%d   ", &reserved_seat) != EOF) {
                if (reserved_seat == seat_number) {
                    printf("\t\tSeat number %d is already selected. Please choose a different seat.\n\n", seat_number);
                    i--;
                    fclose(file);
                    continue;
                }
            }
            fclose(file);
        }

        file = fopen(filename, "a");
        if (file != NULL) {
            fprintf(file, "%d  ", seat_number);
            fclose(file);
        } else {
            printf("Error opening file.\n");
            return;
        }
        seat_numbers[i] = seat_number;
    }
}

int mobile_online_ticket(){

    printf("\n\t\tBy proceeding, I express my consent to complete this transaction\n");
    sleep(3);
    printf("\n\t\tredirect for payment.....\n");                
    sleep(1);
    printf("\n\t\tloading...\n");
    sleep(3);
    printf("\n\t\tprocessing payment.......\n");
    sleep(3);
    printf("\n\t\tPayment Successfully\n");
    sleep(1);
    srand(time(0));
    transaction_number = rand() % 90000000 + 10000000;           
    printf("\n\t\tTransaction ID is  %d  \n" , transaction_number);
    sleep(2);        
    printf("\n\t\tTicket Serial Number is %d \n" , ticket_number );
    printf("\n\t\tNOTE : Ticket Serial Number is Must to Download your Ticket  ...\n");
    printf("\n\t\t--> Terms and Condition Apply <--\n\n");
    sleep(2);
    printf("\n\t\t\t\t------> Your ticket has been booked . <------\n");
    printf("\n");
    printf("*************************************************************************************************************************************\n\n");

    FILE * mobile_Ticket_Serial_file;
    mobile_Ticket_Serial_file = fopen("Ticket_Serial_Number.txt" , "a");
    fprintf(mobile_Ticket_Serial_file ,"%d \n" , ticket_number);
    fclose(mobile_Ticket_Serial_file);

    FILE * print_finally_ticket;
    char file_name[25];
    sprintf(file_name , "%d.txt", ticket_number);
    print_finally_ticket = fopen(file_name , "a");
    fclose(print_finally_ticket);

    return 0;
}

void box_office_pickup(){
    printf("\n\t\tPick your tickets from Box Office.\n");
    printf("\n\t\tloading...\n");
    sleep(6);
    srand(time(0));
    rand_box_office_number = rand()% 4000 + 6000 ;       
    printf("\n\t\tBox Office Token Number is %d \n" , rand_box_office_number );
    sleep(6);
    printf("\n\t\t--> Terms and Condition Apply <--\n\n");
    sleep(2);
    printf("\n\t\tSaved Successfully\n");
    sleep(2);
    printf("\n\t\t\t\t------> Your seats has been blocked . <------\n");
    printf("\n");
    printf("*************************************************************************************************************************************\n\n");

    FILE * Box_Ticket_Serial_file;
    Box_Ticket_Serial_file = fopen("Box_Office_Number.txt", "a");
    fprintf(Box_Ticket_Serial_file ,"%d \n" , rand_box_office_number);
    fclose(Box_Ticket_Serial_file);

}

void mini_ticket(int seats , char * theatre_name , char * movie_name, char * show_time){

    
    srand(time(0));
    ticket_number = rand()% 4001 + 1000 ; 

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int Premium_seat = 0;
    int Executive_seat = 0;
    int Normal_seat = 0;

    printf("\n");
    printf("\t\t**************************************************************************************************************************\n\n");
    printf("			%s\n" , theatre_name);
    printf("			%s\n" , movie_name);
    printf("			%s\n\n\n" , show_time);
    printf("							BOOKING SUMMARY\n\n");
    for (int i = 0 ; i < seats ; i++){
        if (seat_numbers[i] >= 1 && seat_numbers[i] <= 66){
            Premium_seat++;
        }
        else if (seat_numbers[i] >= 70 && seat_numbers[i] <= 201){
            Executive_seat++;
        }
        else if (seat_numbers[i] >= 205 && seat_numbers[i] <= 270){
            Normal_seat++;
        }
        
    }

    printf("						PREMIUM   ( %d Tickets) ( 1 Seat = 1500 )             Rs. %-6d\n", Premium_seat , Premium_seat*1500 );
    printf("						EXECUTIVE ( %d Tickets) ( 1 Seat = 800 )              Rs. %-6d\n", Executive_seat , Executive_seat*800 );
    printf("						NORMAL    ( %d Tickets) ( 1 Seat = 550 )              Rs. %-6d\n", Normal_seat , Normal_seat*550 );

    printf("						Selected seats : ");

    for (int i = 0; i < seats ; i++) {
        printf("%d ", seat_numbers[i]);
    }
    printf("\n");
    printf("						%-28s                         Rs. %-10.2f\n", "Base Amount", 300.00);
    printf("						%-28s                         Rs. %-10.2f\n", "Integrated GST (IGST) @ 0.18", 199.00);
    printf("\n");
    printf("				---------------------------------------------------------------------------------------------\n");
    printf("						%-28s                         Rs. %-10.2d\n", "Amount Payable", 199 + 300 + ( Premium_seat*1500 + Normal_seat*550 + Executive_seat*800 ));

    printf("\n");
    printf("			Date : %02d:%02d:%02d  %02d-%02d-%04d\n" , tm.tm_hour, tm.tm_min, tm.tm_sec , tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900 );
    printf("                        GST Code - 09AAACP4526D1Z0 \n\n");
    printf("                                                                        ENJOY THE SHOW \n");
    printf("                                                                    Terms and Condition Apply \n\n");
    printf("\t\t**************************************************************************************************************************\n\n");

}

void print_mini_ticket( int seats , char * theatre_name , char * movie_name, char * show_time , int X){

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int Premium_seat = 0;
    int Executive_seat = 0;
    int Normal_seat = 0;

    FILE *print_ticket;
    char file_name[25];
    sprintf(file_name , "%d.txt", id_number);
    print_ticket = fopen(file_name , "a");
    fprintf(print_ticket , "\t\t**************************************************************************************************************************\n\n");
    fprintf(print_ticket , "			%s\n" , theatre_name);
    fprintf(print_ticket , "			%s\n" , movie_name);
    fprintf(print_ticket , "			%s\n\n\n" , show_time);
    fprintf(print_ticket , "							BOOKING SUMMARY\n\n");
    for (int i = 0 ; i < seats ; i++){
        if (seat_numbers[i] >= 1 && seat_numbers[i] <= 66){
            Premium_seat++;
        }
        else if (seat_numbers[i] >= 70 && seat_numbers[i] <= 201){
            Executive_seat++;
        }
        else if (seat_numbers[i] >= 205 && seat_numbers[i] <= 270){
            Normal_seat++;
        }
        
    }
    fprintf(print_ticket , "						PREMIUM   ( %d Tickets) ( 1 Seat = 1500 )             Rs. %-6d\n", Premium_seat , Premium_seat*1500 );
    fprintf(print_ticket , "						EXECUTIVE ( %d Tickets) ( 1 Seat = 800 )              Rs. %-6d\n", Executive_seat , Executive_seat*800 );
    fprintf(print_ticket , "						NORMAL    ( %d Tickets) ( 1 Seat = 550 )              Rs. %-6d\n", Normal_seat , Normal_seat*550 );
    fprintf(print_ticket , "						Selected seats : ");

    for (int i = 0; i < seats ; i++) {
        fprintf(print_ticket , "%d ", seat_numbers[i]);
    }
    fprintf(print_ticket , "\n");
    fprintf(print_ticket , "						%-28s                         Rs. %-10.2f\n", "Base Amount", 300.00);
    fprintf(print_ticket , "						%-28s                         Rs. %-10.2f\n", "Integrated GST (IGST) @ 0.18", 199.00);
    fprintf(print_ticket , "\n");
    fprintf(print_ticket , "				---------------------------------------------------------------------------------------------\n");
    fprintf(print_ticket , "						%-28s                         Rs. %-10.2d\n", "Amount Payable", 199 + 300 + ( Premium_seat*1500 + Normal_seat*550 + Executive_seat*800 ));

    fprintf(print_ticket , "\n");
    fprintf(print_ticket , "			Date : %02d:%02d:%02d  %02d-%02d-%04d\n" , tm.tm_hour, tm.tm_min, tm.tm_sec , tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900 );
    if (X == 1){
        fprintf(print_ticket , "                        Ticket Serial Number : %d\n" , ticket_number);
    }
    else if(X == 2 ){
        fprintf(print_ticket , "                        Ticket Serial Number : %d\n" , rand_box_office_number);
    }
    
    
    fprintf(print_ticket , "                        GST Code - 09AAACP4526D1Z0 \n\n");
    fprintf(print_ticket , "                                                                        ENJOY THE SHOW \n");
    fprintf(print_ticket , "                                                                    Terms and Condition Apply \n\n");
    fprintf(print_ticket , "\t\t**************************************************************************************************************************\n\n");

    fclose(print_ticket);

}

void bookmyshow(){

    int num_seats;

    do
    {

    printf("\n\t\t\t\tSELECT THEATRE THEN MOVIE\n\n");
    for (int i = 0; i < 3; i++) {
        printf("\t\t\t%d. %s \n" , i+1 , theatres.theatre_names[i] );
    }
    printf("\t\t\t4. Back \n");
    printf("\n");

    while (1) 
        {
            printf("\tEnter your choice : ");
            if (scanf("%d", &choice) != 1) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            while (getchar() != '\n'); 
            continue;
            }
            if (choice < 1 || choice > 4)
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            continue;
            }
            break;
        }
    
    switch (choice)
    {
    case 1:

        printf("\n\t\t\t\tSELECT MOVIE AND SHOW TIME\n\n");
        for(int i =  0 ; i < 3; i++){
            printf("\n\t\t\t%d. %-25s \t  -  %s " , i+1 , theatres.theatre[0].movies[i].name, theatres.theatre[0].movies[i].timings[0] );  
        }
        printf("\n\n");

        while (1) 
        {
            printf("\tEnter your choice : ");
            if (scanf("%d", &choice) != 1) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            while (getchar() != '\n'); 
            continue;
            }
            if (choice < 1 || choice > 4) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            continue;
            }
            break;
        }
        switch (choice)
        {
            case 1:
                printf("\n\t\t\t\t SELECT SEAT TYPE \n\n");
                Theatre_Seat_Matrix();
                printf("\n\t\tHow many seats do you want to reserve ? ");
                scanf("%d", &num_seats);
                enter_seat_number(num_seats, "t1m1seats.txt");
                mini_ticket(num_seats , "PVR : Phoenix Mall of Asia"  , "K.G.F: Chapter 1" , "10:30 AM -- 01:30 PM" );
                printf("\n\t\t\t\t SELECT TICKET TYPE \n");
                printf("\n");
                printf("\n\t\t\t1 . M - Ticket ( Online Ticket ) \t" );
                printf("\n\t\t\t2 . Box Office Pickup ( Offline Ticket )  \t\n\n" );

                while (1) 
                {
                    printf("\tEnter your choice : ");
                    if (scanf("%d", &choice) != 1){
                        sleep(1);
                        printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choice < 1 || choice > 2){
                        sleep(1);
                        printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                        continue;
                    }
                    break;
                }
                printf("\n");
                switch (choice)
                {
                    case 1:
                        mobile_online_ticket();
                        print_mini_ticket(num_seats , "PVR : Phoenix Mall of Asia"  , "K.G.F: Chapter 1" , "10:30 AM -- 01:30 PM" , 1 );
                        prints_finally_ticket(num_seats , 0 , "PVR : Phoenix Mall of Asia" , "K.G.F: Chapter 1" , "10:30 AM -- 01:30 PM" );
                        break;
                    case 2:
                        box_office_pickup();
                        print_mini_ticket(num_seats , "PVR : Phoenix Mall of Asia"  , "K.G.F: Chapter 1" , "10:30 AM -- 01:30 PM" , 2 );
                        break;
                    }

                break;

            case 2:
                printf("\n\t\t\t\t SELECT SEAT TYPE \n\n");
                Theatre_Seat_Matrix();
                printf("\n\t\tHow many seats do you want to reserve ? ");
                scanf("%d", &num_seats);
                enter_seat_number(num_seats, "t1m2seats.txt");
                mini_ticket(num_seats , "PVR : Phoenix Mall of Asia"  , "Mr And Mrs Ramchari" , "03:00 PM -- 06:00 PM" );
                printf("\n\t\t\t\t SELECT TICKET TYPE \n");
                printf("\n");
                printf("\n\t\t\t1 . M - Ticket ( Online Ticket ) \t" );
                printf("\n\t\t\t2 . Box Office Pickup ( Offline Ticket )  \t\n\n" );

                while (1) 
                {
                    printf("\tEnter your choice : ");
                    if (scanf("%d", &choice) != 1){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choice < 1 || choice > 2){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        continue;
                    }
                    break;
                }
                printf("\n");
                switch (choice)
                {
                    case 1:
                        mobile_online_ticket();
                        print_mini_ticket(num_seats ,  "PVR : Phoenix Mall of Asia" , "Mr And Mrs Ramchari" , "03:00 PM -- 06:00 PM" , 1 );
                        prints_finally_ticket(num_seats , 0 , "PVR : Phoenix Mall of Asia" , "Mr And Mrs Ramchari" , "03:00 PM -- 06:00 PM");
                        break;
                    case 2:
                        box_office_pickup();
                        print_mini_ticket(num_seats , "PVR : Phoenix Mall of Asia" , "Mr And Mrs Ramchari" , "03:00 PM -- 06:00 PM" , 2 );
                        break;
                    }

                break;

            case 3:
                printf("\n\t\t\t\t SELECT SEAT TYPE \n\n");
                Theatre_Seat_Matrix();
                printf("\n\t\tHow many seats do you want to reserve ? ");
                scanf("%d", &num_seats);
                enter_seat_number(num_seats, "t1m3seats.txt");
                mini_ticket(num_seats , "PVR : Phoenix Mall of Asia"  , "K.G.F: Chapter 2" , "07:30 PM -- 10:00 PM" );
                printf("\n\t\t\t\t SELECT TICKET TYPE \n");
                printf("\n");
                printf("\n\t\t\t1 . M - Ticket ( Online Ticket ) \t" );
                printf("\n\t\t\t2 . Box Office Pickup ( Offline Ticket )  \t\n\n" );

                while (1) 
                {
                    printf("\tEnter your choice : ");
                    if (scanf("%d", &choice) != 1){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choice < 1 || choice > 2){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        continue;
                    }
                    break;
                }
                printf("\n");
                switch (choice)
                {
                    case 1:
                        mobile_online_ticket();
                        print_mini_ticket(num_seats , "PVR : Phoenix Mall of Asia"  , "K.G.F: Chapter 2" , "07:30 PM -- 10:00 PM" , 1 );
                        prints_finally_ticket(num_seats , 0 , "PVR : Phoenix Mall of Asia" ,  "K.G.F: Chapter 2" , "07:30 PM -- 10:00 PM" );
                        break;
                    case 2:
                        box_office_pickup();
                        print_mini_ticket(num_seats , "PVR : Phoenix Mall of Asia"  , "K.G.F: Chapter 2" , "07:30 PM -- 10:00 PM" , 2 );
                        break;
                    }

                break;
        }
        break;
    
     case 2:
        
        printf("\n\t\t\t\tSELECT MOVIE AND SHOW TIME\n\n");
        for(int i =  0 ; i < 3; i++){
            printf("\n\t\t\t%d. %-25s \t  -  %s " , i+1 , theatres.theatre[1].movies[i].name, theatres.theatre[1].movies[i].timings[0] );  
        }
        printf("\n\n");

        while (1) 
        {
            printf("\tEnter your choice : ");
            if (scanf("%d", &choice) != 1) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            while (getchar() != '\n'); 
            continue;
            }
            if (choice < 1 || choice > 4) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            continue;
            }
            break;
        }
        switch (choice)
        {
        case 1:
            printf("\n\t\t\t\t SELECT SEAT TYPE \n\n");
            Theatre_Seat_Matrix();
            printf("\n\t\tHow many seats do you want to reserve ? ");
            scanf("%d", &num_seats);
            enter_seat_number(num_seats, "t2m1seats.txt");
            mini_ticket(num_seats , "PVR: Nexus (Formerly Forum)"  , "Fighter" , "10:30 AM -- 01:30 PM" );
            printf("\n\t\t\t\t SELECT TICKET TYPE \n");
            printf("\n");
            printf("\n\t\t\t1 . M - Ticket ( Online Ticket ) \t" );
            printf("\n\t\t\t2 . Box Office Pickup ( Offline Ticket )  \t\n\n" );

            while (1) 
            {
                printf("\tEnter your choice : ");
                if (scanf("%d", &choice) != 1){
                    sleep(1);
                    printf("\tWrong Entry! Please enter the correct option.\n\n");
                    while (getchar() != '\n'); 
                    continue;
                }
                if (choice < 1 || choice > 2){
                    sleep(1);
                    printf("\tWrong Entry! Please enter the correct option.\n\n");
                    continue;
                }

                break;

            }
            printf("\n");

            switch (choice)
            {
                case 1:
                    mobile_online_ticket();
                    print_mini_ticket(num_seats ,  "PVR: Nexus (Formerly Forum)"  , "Fighter" , "10:30 AM -- 01:30 PM", 1 );
                    prints_finally_ticket(num_seats , 1 , "PVR: Nexus (Formerly Forum)"  , "Fighter" , "10:30 AM -- 01:30 PM" );
                    break;
                case 2:
                    box_office_pickup();
                    print_mini_ticket(num_seats ,  "PVR: Nexus (Formerly Forum)"  , "Fighter" , "10:30 AM -- 01:30 PM" , 2 );
                    break;
                }

            break;
        
        case 2:
            printf("\n\t\t\t\t SELECT SEAT TYPE \n\n");
            Theatre_Seat_Matrix();
            printf("\n\t\tHow many seats do you want to reserve ? ");
            scanf("%d", &num_seats);
            enter_seat_number(num_seats, "t2m2seats.txt");
            mini_ticket(num_seats , "PVR: Nexus (Formerly Forum)" ,  "Operation Valentine" , "05:10 PM -- 08:30 PM" );
            printf("\n\t\t\t\t SELECT TICKET TYPE \n");
            printf("\n");
            printf("\n\t\t\t1 . M - Ticket ( Online Ticket ) \t" );
            printf("\n\t\t\t2 . Box Office Pickup ( Offline Ticket )  \t\n\n" );

            while (1) 
            {
                printf("\tEnter your choice : ");
                if (scanf("%d", &choice) != 1){
                sleep(1);
                printf("\tWrong Entry! Please enter the correct option.\n\n");
                while (getchar() != '\n'); 
                continue;
            }
            if (choice < 1 || choice > 2){
                sleep(1);
                printf("\tWrong Entry! Please enter the correct option.\n\n");
                continue;
            }
            break;
            }
            printf("\n");
            switch (choice)
            {
                case 1:
                    mobile_online_ticket();
                    print_mini_ticket(num_seats ,  "PVR: Nexus (Formerly Forum)"  , "Operation Valentine" , "05:10 PM -- 08:30 PM" , 1 );
                    prints_finally_ticket(num_seats , 1 , "PVR: Nexus (Formerly Forum)"  ,  "Operation Valentine" , "05:10 PM -- 08:30 PM"  );
                    break;
                case 2:
                    box_office_pickup();
                    print_mini_ticket(num_seats ,  "PVR: Nexus (Formerly Forum)"  , "Operation Valentine" , "05:10 PM -- 08:30 PM" , 2 );
                    break;
            }
                
            break;

        case 3:
            printf("\n\t\t\t\t SELECT SEAT TYPE \n\n");
            Theatre_Seat_Matrix();
            printf("\n\t\tHow many seats do you want to reserve ? ");
            scanf("%d", &num_seats);
            enter_seat_number(num_seats, "t2m3seats.txt");
            mini_ticket(num_seats , "PVR: Nexus (Formerly Forum)" , "Article 370" , "10:00 AM -- 01:00 PM");
            printf("\n\t\t\t\t SELECT TICKET TYPE \n");
            printf("\n");
            printf("\n\t\t\t1 . M - Ticket ( Online Ticket ) \t" );
            printf("\n\t\t\t2 . Box Office Pickup ( Offline Ticket )  \t\n\n" );

            while (1) 
            {
            printf("\tEnter your choice : ");
            if (scanf("%d", &choice) != 1){
            sleep(1);
            printf("\tWrong Entry! Please enter the correct option.\n\n");
            while (getchar() != '\n'); 
            continue;
            }
            if (choice < 1 || choice > 2){
            sleep(1);
            printf("\tWrong Entry! Please enter the correct option.\n\n");
            continue;
            }
            break;
            }
            printf("\n");
            switch (choice)
            {
                case 1:
                    mobile_online_ticket();
                    print_mini_ticket(num_seats ,  "PVR: Nexus (Formerly Forum)"  , "Article 370" , "10:00 AM -- 01:00 PM" , 1 );
                    prints_finally_ticket(num_seats , 1 , "PVR: Nexus (Formerly Forum)"  , "Article 370" , "10:00 AM -- 01:00 PM" );
                    break;
                case 2:
                    box_office_pickup();
                    print_mini_ticket(num_seats ,  "PVR: Nexus (Formerly Forum)"  , "Article 370" , "10:00 AM -- 01:00 PM" , 2 );
                    break;
            }
                
            break;
        }

        break;

    case 3:

        printf("\n\t\t\t\tSELECT MOVIE AND SHOW TIME\n\n");
        for(int i =  0 ; i < 3; i++){
            printf("\n\t\t\t%d. %-25s \t  -  %s " , i+1 , theatres.theatre[2].movies[i].name , theatres.theatre[2].movies[i].timings[0]);  
        }
        printf("\n\n");

        while (1) 
        {
            printf("\tEnter your choice : ");
            if (scanf("%d", &choice) != 1) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            while (getchar() != '\n'); 
            continue;
            }
            if (choice < 1 || choice > 4) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            continue;
            }
            break;
        }
        switch (choice)
        {
        case 1:
            printf("\n\t\t\t\t SELECT SEAT TYPE \n\n");
            Theatre_Seat_Matrix();
            printf("\n\t\tHow many seats do you want to reserve ? ");
            scanf("%d", &num_seats);
            enter_seat_number(num_seats, "t3m1seats.txt");
            mini_ticket(num_seats , "Cinepolis : Orion East Mall" , "Chhoti Si Baat" , "11:00 AM -- 01:00 PM" );
            printf("\n\t\t\t\t SELECT TICKET TYPE \n");
                printf("\n");
                printf("\n\t\t\t1 . M - Ticket ( Online Ticket ) \t" );
                printf("\n\t\t\t2 . Box Office Pickup ( Offline Ticket )  \t\n\n" );

                while (1) 
                {
                    printf("\tEnter your choice : ");
                    if (scanf("%d", &choice) != 1){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choice < 1 || choice > 2){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        continue;
                    }
                    break;
                }
                printf("\n");
                switch (choice)
                {
                    case 1:
                        mobile_online_ticket();
                        print_mini_ticket(num_seats , "Cinepolis : Orion East Mall" , "Chhoti Si Baat" , "11:00 AM -- 01:00 PM" , 1 );
                        prints_finally_ticket(num_seats , 2 ,"Cinepolis : Orion East Mall" , "Chhoti Si Baat" , "11:00 AM -- 01:00 PM" );
                        break;
                    case 2:
                        box_office_pickup();
                        print_mini_ticket(num_seats , "Cinepolis : Orion East Mall" , "Chhoti Si Baat" , "11:00 AM -- 01:00 PM" , 2 );
                        break;
                    }
            break;
        
        case 2:
            printf("\n\t\t\t\t SELECT SEAT TYPE \n\n");
            Theatre_Seat_Matrix();
            printf("\n\t\tHow many seats do you want to reserve ? ");
            scanf("%d", &num_seats);
            enter_seat_number(num_seats, "t3m2seats.txt");
            mini_ticket(num_seats , "Cinepolis : Orion East Mall" ,  "Mother India" , "02:10 PM -- 05:30 PM" );
            printf("\n\t\t\t\t SELECT TICKET TYPE \n");
                printf("\n");
                printf("\n\t\t\t1 . M - Ticket ( Online Ticket ) \t" );
                printf("\n\t\t\t2 . Box Office Pickup ( Offline Ticket )  \t\n\n" );

                while (1) 
                {
                    printf("\tEnter your choice : ");
                    if (scanf("%d", &choice) != 1){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choice < 1 || choice > 2){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        continue;
                    }
                    break;
                }
                printf("\n");
                switch (choice)
                {
                    case 1:
                        mobile_online_ticket();
                        print_mini_ticket(num_seats , "Cinepolis : Orion East Mall" , "Mother India" , "02:10 PM -- 05:30 PM" , 1 );
                        prints_finally_ticket(num_seats , 2 , "Cinepolis : Orion East Mall" , "Mother India" , "02:10 PM -- 05:30 PM");
                        break;
                    case 2:
                        box_office_pickup();
                        print_mini_ticket(num_seats , "Cinepolis : Orion East Mall" , "Mother India" , "02:10 PM -- 05:30 PM" , 2 );
                        break;
                    }

            break;

        case 3:
            printf("\n\t\t\t\t SELECT SEAT TYPE \n\n");
            Theatre_Seat_Matrix();
            printf("\n\t\tHow many seats do you want to reserve ? ");
            scanf("%d", &num_seats);
            enter_seat_number(num_seats, "t3m3seats.txt");
            mini_ticket(num_seats , "Cinepolis : Orion East Mall" , "Gol Maal" , "07:00 PM -- 09:30 PM");
            printf("\n\t\t\t\t SELECT TICKET TYPE \n");
                printf("\n");
                printf("\n\t\t\t1 . M - Ticket ( Online Ticket ) \t" );
                printf("\n\t\t\t2 . Box Office Pickup ( Offline Ticket )  \t\n\n" );

                while (1) 
                {
                    printf("\tEnter your choice : ");
                    if (scanf("%d", &choice) != 1){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choice < 1 || choice > 2){
                        sleep(1);
                        printf("\tWrong Entry! Please enter the correct option.\n\n");
                        continue;
                    }
                    break;
                }
                printf("\n");
                switch (choice)
                {
                    case 1:
                        mobile_online_ticket();
                        print_mini_ticket(num_seats ,"Cinepolis : Orion East Mall" , "Gol Maal" , "07:00 PM -- 09:30 PM"  , 1 );
                        prints_finally_ticket(num_seats , 2 , "Cinepolis : Orion East Mall" , "Gol Maal" , "07:00 PM -- 09:30 PM" );
                        break;
                    case 2:
                        box_office_pickup();
                        print_mini_ticket(num_seats ,"Cinepolis : Orion East Mall" , "Gol Maal" , "07:00 PM -- 09:30 PM" , 2 );
                        break;
                    }
                
            break;

        }

        break;

    }

    } while (choice != 4 );

}



int Download_your_mobile_ticket () {

    FILE *con = fopen("Ticket_Serial_Number.txt", "r");
  
    while (fscanf(con , "%d ", &ticket_number ) == 1) {
        if (ticket_number == enter_ticket_number ) {
            fclose(con);
            return 1; 
        }
    }

    fclose(con);

    return 0; 

}

int Download_your_box_ticket () {

    FILE *con = fopen("Box_Office_Number.txt", "r");
  
    while (fscanf(con , "%d ", &ticket_number ) == 1) {
        if (ticket_number == enter_ticket_number ) {
            fclose(con);
            return 1; 
        }
    }

    fclose(con);

    return 0; 

}


void Customer_main_Login(){

    printf("\n\n\t\t\t\t\t\t<<<< WELCOME TO ONLINE MOVIE TICKET BOOKING >>>>\n");

    do
    {
    
        printf("\n\t1. Profile\n");
        printf("\t2. Book your show \n");
        printf("\t3. Download your ticket\n");
        printf("\t4. Past History \n");
        printf("\t0. Logout \n\n");

        while (1) 
        {
            printf("\tEnter your choice : ");
            if (scanf("%d", &choice) != 1) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            while (getchar() != '\n'); 
            continue;
            }
            if (choice < 0 || choice > 4) 
            {
            sleep(2);
            printf("\t\tWrong Entry! Please enter the correct option.\n\n");
            continue;
            }
            break;
        }

        switch (choice)
        {
        case 1:
            Customerprofile();
            break;

        case 2:
            bookmyshow();
            break;

        case 3:

            printf("\n\t\tEnter Ticket Serial Number :  ");
            scanf("%d", &enter_ticket_number);

            if (Download_your_mobile_ticket()){

                printf("\n");
                printf("\t Downloading .....  \n\n");
                sleep(2);
                
                FILE * Download_your_ticket;
                char filename[25];
                sprintf(filename , "%d.txt" , enter_ticket_number);
                Download_your_ticket = fopen(filename , "r" );
                char line[10000];
                while(fgets(line,50,Download_your_ticket) != NULL){
                    printf("%s" , line);
                }
                
            } 

            else if( Download_your_box_ticket()){

                printf("\n\n\t\tYour ticket has been blocked by the system.\n");
                printf("\t\tTransaction is pending !\n");
                printf("\t\tProcess your payment near by your box office !. \n\n");
            }

            else
                printf("\n\n\t\tEntered Ticket Number is Incorrect  ! \n\n");

            break;

        case 4:
            view_past_history();
            break;

        case 0:
            sleep(3);
            printf("\n\t\t\t****** logout successfully ! ******\n\n");
            break;

        }                       

    } while (choice != 0);   


}


void worker_login(){

    printf("\n");
    printf("\t\tEnter Admin Email Id : ");
    scanf("%s", worker_email);
    printf("\n");
    printf("\t\tEnter Admin password : ");
    scanf("%s", worker_password);

    if (strcmp(worker_email, "worker@gmail.com") == 0 && strcmp(worker_password, "worker") == 0) {
        worker_interface();
    }
    else
    {

        sleep(2);
        printf("\n");
        printf("\n\t\t****** Login failed . Invalid email address or password ! ******\n");
    }

}


int main() {

    // Initialize data for theatres
    strcpy(theatres.theatre_names[0], "PVR : Phoenix Mall of Asia" );
    strcpy(theatres.theatre_names[1], "PVR: Nexus (Formerly Forum)" );
    strcpy(theatres.theatre_names[2], "Cinepolis : Orion East Mall" );
    
    // Initialize data for theatre Seat type
    strcpy(theatres.seat_type[0], "PREMIUM" );
    strcpy(theatres.seat_type[1], "EXECUTIVE" );
    strcpy(theatres.seat_type[2], "NORMAL" );

    //Initialize data for theatre Seat Rates
    theatres.rates[0] = 1500;
    theatres.rates[1] = 750;
    theatres.rates[2] = 550;

    // Initialize data for theatre 1
    strcpy(theatres.theatre[0].movies[0].name, "K.G.F: Chapter 1");
    strcpy(theatres.theatre[0].movies[0].timings[0], "10:30 AM -- 01:30 PM");

    strcpy(theatres.theatre[0].movies[1].name, "Mr And Mrs Ramchari");
    strcpy(theatres.theatre[0].movies[1].timings[0], "03:00 PM -- 06:00 PM" );

    strcpy(theatres.theatre[0].movies[2].name, "K.G.F: Chapter 2");
    strcpy(theatres.theatre[0].movies[2].timings[0], "07:30 PM -- 10:00 PM" );

    // Initialize data for theatre 2
    strcpy(theatres.theatre[1].movies[0].name, "Fighter");
    strcpy(theatres.theatre[1].movies[0].timings[0], "10:30 AM -- 01:30 PM");

    strcpy(theatres.theatre[1].movies[1].name, "Operation Valentine");
    strcpy(theatres.theatre[1].movies[1].timings[0], "05:10 PM -- 08:30 PM");

    strcpy(theatres.theatre[1].movies[2].name, "Article 370");
    strcpy(theatres.theatre[1].movies[2].timings[0], "10:00 PM -- 01:00 PM");

    // Initialize data for theatre 3
    strcpy(theatres.theatre[2].movies[0].name, "Chhoti Si Baat");
    strcpy(theatres.theatre[2].movies[0].timings[0], "11:00 AM -- 01:00 PM");

    strcpy(theatres.theatre[2].movies[1].name, "Mother India");
    strcpy(theatres.theatre[2].movies[1].timings[0], "02:10 PM -- 05:30 PM");

    strcpy(theatres.theatre[2].movies[2].name, "Gol Maal");
    strcpy(theatres.theatre[2].movies[2].timings[0], "07:00 PM -- 09:30 PM");

    printf("\n\n\t\t\t\t\t<<<< WELCOME TO ONLINE MOVIE TICKET BOOKING >>>>\n");

    do{

        printf("\n\t1. Sign up\n");
        printf("\t2. Log in\n");
        printf("\t0. Exit\n");
        printf("\n");

        while (1) 
        {
            printf("\tEnter your choice : ");
            if (scanf("%d", &choice) != 1) 
            {
                sleep(1);
                printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                while (getchar() != '\n'); 
                continue;
            }
            if (choice < 0 || choice > 2) 
            {
                sleep(1);
                printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                continue;
            }
            break;
        }

        switch (choice)
        {
        case 1:
            User_Register();
            break;
        
        case 2:
            do
            {
                printf("\n\t1. Customer Login\n");
                printf("\t2. Admin Login\n");
                printf("\t3. Back \n\n");

                while (1) 
                {
                    printf("\tEnter your choice : ");
                    if (scanf("%d", &choice) != 1) 
                    {
                        sleep(2);
                        printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choice < 1 || choice > 3) 
                    {
                        sleep(2);
                        printf("\t\tWrong Entry! Please enter the correct option.\n\n");
                        continue;
                    }
                    break;
                }

                switch (choice)
                {
                case 1:      

                    if (user_login())
                    {
                        printf("\n\t\t\t****** Login successful ! ******\n");
                        loginhistory();
                        Customer_main_Login();

                    } 

                    else 
                    {
                        sleep(2);
                        printf("\n\n\t\t****** Login failed . Invalid email address or password ! ******\n");
                    }

                    break;

                case 2:
                    worker_login();
                    break;

                case 3:
                     
                    sleep(2);
                    printf("\n\t\t\t************************************\n\n");
                    break;
                }

            } while (choice != 3);
            
            break;

        case 0:
            sleep(3);
            printf("\n\n\t\t\t\t\t<<<< THANKS FOR VISITING  >>>>\n\n\n");
            break;
        }

    }while(choice != 0);

    return 0;

}

void prints_finally_ticket(  int seats , int x , char *theatre_name , char *movie_name, char *show_time) {

    int Premium_seat = 0;
    int Executive_seat = 0;
    int Normal_seat = 0;

    FILE * prints_finally_ticket;
    char file_name[25];
    sprintf(file_name , "%d.txt", ticket_number );
    prints_finally_ticket = fopen(file_name , "w");

    //GIVES DATE AND TIME 
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    srand(time(0));
    rand_sl_no= rand()% 900000 + 100000 ;

    fprintf( prints_finally_ticket , "\n\n");
    fprintf( prints_finally_ticket , "\t\t\t ___________________________________________________________________________\n");
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                                   INVOICE                                 |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    fprintf( prints_finally_ticket , "\t\t\t|         SL No - %d                                                    |\n" , rand_sl_no);
    fprintf( prints_finally_ticket , "\t\t\t|         %s                            	    |\n" , theatre_name );
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    if( x == 0)
    {
        fprintf( prints_finally_ticket , "\t\t\t|         PVR INOX LIMITED (Formerly know as PVR LIMITED)                   |\n");
        fprintf( prints_finally_ticket , "\t\t\t|         PHOENIX MALL OF ASIA                                              |\n");
        fprintf( prints_finally_ticket , "\t\t\t|         PVR: Phoenix Marketcity Mall, Whitefield Road                     |\n");
        fprintf( prints_finally_ticket , "\t\t\t|         Karnataka 560048, India                                           |\n");
    }
    else if (x == 1)
    {
        fprintf( prints_finally_ticket , "\t\t\t|         PVR INOX LIMITED (Formerly know as PVR LIMITED)                   |\n");
        fprintf( prints_finally_ticket , "\t\t\t|         PVR: Nexus (Formerly Forum)                                       |\n");
        fprintf( prints_finally_ticket , "\t\t\t|         The NEXUS Mall, 21-22 Chikku Lakshmaiah Layout                    |\n");
        fprintf( prints_finally_ticket , "\t\t\t|         Koramangala , Bengaluru , Karnataka 560095 , India                |\n");
    }
    else if ( x == 2)
    {
        fprintf( prints_finally_ticket , "\t\t\t|         PVR INOX LIMITED (Formerly know as PVR LIMITED)                   |\n");
        fprintf( prints_finally_ticket , "\t\t\t|         Cinepolis : Orion East Mall                                       |\n");
        fprintf( prints_finally_ticket , "\t\t\t|         Dodda Banaswadi Main Rd, Jaibharath Nagar                         |\n");
        fprintf( prints_finally_ticket , "\t\t\t|         Maruthi Sevanagar, Bengaluru, Karnataka 560033 , India            |\n");
    }
    fprintf( prints_finally_ticket , "\t\t\t|         www.pvrcinemas.com                                                |\n");
    fprintf( prints_finally_ticket , "\t\t\t|         CIN : L74899DL1995PLC067827                                       |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    fprintf( prints_finally_ticket , "\t\t\t|         %s                                                  |\n", movie_name ); 
    fprintf( prints_finally_ticket , "\t\t\t|         Show Time : %s                                  |\n", show_time);
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    fprintf( prints_finally_ticket , "\t\t\t|   ********************************************************************    |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                      BOOKING SUMMARY                                      |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");

    for (int i = 0 ; i < seats ; i++){
        if (seat_numbers[i] >= 1 && seat_numbers[i] <= 66){
            Premium_seat++;
        }
        else if (seat_numbers[i] >= 70 && seat_numbers[i] <= 201){
            Executive_seat++;
        }
        else if (seat_numbers[i] >= 205 && seat_numbers[i] <= 270){
            Normal_seat++;
        }
        
    }

    fprintf( prints_finally_ticket , "\t\t\t|         PREMIUM                             Rs. %-6d                                |\n", Premium_seat*1500 );
    fprintf( prints_finally_ticket , "\t\t\t|         EXECUTIVE                           Rs. %-6d                                |\n", Executive_seat*800 );
    fprintf( prints_finally_ticket , "\t\t\t|         NORMAL                              Rs. %-6d                                |\n", Normal_seat*550 );
    

    fprintf( prints_finally_ticket , "\t\t\t|         Selected seats : ");                       
    
    for (int i = 0; i < seats; i++) {
        fprintf( prints_finally_ticket , "%d ", seat_numbers[i]);
    }

    fprintf( prints_finally_ticket , " 				            |\n");
    fprintf( prints_finally_ticket , "\t\t\t|         Base Amount                         Rs. 300.00                    |\n");
    fprintf( prints_finally_ticket , "\t\t\t|         Integrated GST (IGST) @ 0.18        Rs. 199.00                    |\n");
    fprintf( prints_finally_ticket , "\t\t\t|         Total Discount                      Rs. 00.00                     |\n");
    fprintf( prints_finally_ticket , "\t\t\t|      ------------------------------------------------------               |\n");
    fprintf( prints_finally_ticket , "\t\t\t|          Amount Payable                     Rs. %d.00                   |\n" , 199 + 300 + ( Premium_seat*1500 + Normal_seat*550 + Executive_seat*800 ) );
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    fprintf( prints_finally_ticket , "\t\t\t|   ********************************************************************    |\n");
    fprintf( prints_finally_ticket , "\t\t\t|    Date : %02d:%02d:%02d  %02d-%02d-%04d                                            |\n" , tm.tm_hour, tm.tm_min, tm.tm_sec , tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900 );
    fprintf( prints_finally_ticket , "\t\t\t|    Ticket Serial Number : %d                                            |\n" , ticket_number);
    fprintf( prints_finally_ticket , "\t\t\t|    GST Code - 09AAACP4526D1Z0                                             |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                           ENJOY THE SHOW                                  |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                      Terms and Condition Apply                            |\n");
    fprintf( prints_finally_ticket , "\t\t\t|                                                                           |\n");
    fprintf( prints_finally_ticket , "\t\t\t|___________________________________________________________________________|\n\n");
    fprintf( prints_finally_ticket , "\n");

    fclose(prints_finally_ticket);

}