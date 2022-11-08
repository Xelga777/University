#include <stdio.h>                                                                                     
#include "interface.h"

void display_result(int code_result) {
    switch (code_result) {
        case -1:
            printf("\nInitialized "fail"");
            break;
        case 1:
            printf("\nInitialized "success"\n");
            break;
        case -2:
            printf("\nInserted "fail"\n");
            break;
        case 2:
            printf("\nInserted "success"\n");
            break;
        case -3:
            printf("\nDeleted "fail"\n");
            break;
        case 3:
            printf("\nDeleted "success"\n");
            break;
        case -4:
            printf("\nData processed "fail"\n");
            break;
        case 4:
            printf("\nData processed "success"\n");
            break;
        default:
            break;
    }
}

void display_menu(int mode) {
    clear_screen();
    if (mode == 0) {
        printf("1.\tInitializing array\n");
        printf("2.\tInsert new element into array\n");
        printf("3.\tDelete an element from array\n");
        printf("4.\tData handling\n");
        printf("5.\tDisplay info\n");
        printf("6.\tQuit program\n");
    } else if (mode == 1) {
        printf("\nINITIALIZING MODE\n");
    } else if (mode == 2) {
        printf("\nINSERTING MODE\n");
    } else if (mode == 3) {
        printf("\nDELETING MODE\n");
    } else if (mode == 4) {
        printf("\nDATA PROCESSING MODE\n");
    } else if (mode == 5) {
        printf("\nOUTPUT MODE\n");
    }
}

void clear_screen() {
    printf("\033[2J");
    printf("\033[0;0f");
}

void menu(int* chooser) {
    int has_choice = false;

    while (!has_choice) {
        if (!scanf("%d", chooser) || *chooser < 1 || *chooser > 6) {
            display_menu(0);
            printf("Incorrect menu choice\nTry again\n");
            scanf("%*[^\n]");
        } else {
            has_choice = true;
        }
    }
}
