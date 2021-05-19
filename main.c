#include<stdio.h>
#include<conio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>

struct Node{
    char* country;
    char* totalCases;
    char* totalICU;
    char* totalVacc;
    char* totalDeaths;
    char* totalHosp;
    char* totalTests;
    struct Node* next;
};

//this function prints contents of linked list
//starting from the given node
void printList(struct Node* n){
    while(n != NULL){
        printf("Analysis for %s", n->country);
        printf("\n");
        printf("Total Cases = %d", atoi(n->totalCases));
        printf("\n");
        printf("Total Vaccinations = %d", atoi(n->totalVacc));
        printf("\n");
        printf("Total number of patients in ICU = %d", atoi(n->totalICU));
        printf("\n");
        printf("Total number of deaths in ICU = %d", atoi(n->totalDeaths));
        printf("\n");
        printf("Total number of hospital patients = %d", atoi(n->totalHosp));
        printf("\n");
        printf("Total number of tests = %d", atoi(n->totalTests));
        printf("\n------------------------------------\n");
        n = n->next;
    }
}

//this function counts number of nodes in list
int countList(struct Node* n){
    int counter = 0;
    while(n != NULL){
        counter++;
        n = n->next;
    }
    return counter;
}

//Given a reference (pointer to pointer) to the head of a list
//and data (country, totalICU, totalVacc)
//appends a new node at the end
void append(struct Node** headRef, struct Node* node){
    struct Node* last = *headRef; //used in step 3

    //1. This new Node is going to be the last node
    //so make next of it as NULL
    node->next = NULL;

    //2. if the linked list is empty, then make the new node as head
    if(*headRef == NULL){
        *headRef = node;
        return;
    }

    //3. Else traverse till the last node and check if this country
    //already found in list
    //if yes, update it's data
    while(last->next != NULL){
        if(node->country != '\0' && strcmp(node->country, "") != 0 && last->country != '\0'){
            if(strcmp(last->country, node->country) ==  0){
                int cases = atoi(last->totalCases) + atoi(node->totalCases);
                itoa(cases, last->totalCases, 10);
                int icu = atoi(last->totalICU) + atoi(node->totalICU);
                itoa(icu, last->totalICU, 10);
                int vacc = atoi(last->totalVacc) + atoi(node->totalVacc);
                itoa(vacc, last->totalVacc, 10);
                int deaths = atoi(last->totalDeaths) + atoi(node->totalDeaths);
                itoa(deaths, last->totalDeaths, 10);
                int hosp = atoi(last->totalHosp) + atoi(node->totalHosp);
                itoa(hosp, last->totalHosp, 10);
                int tests = atoi(last->totalTests) + atoi(node->totalTests);
                itoa(tests, last->totalTests, 10);
                return;
            }
        }
        last = last->next;
    }

    //4. Once you reach last node check first if this node has same country name
    // if yes, update data
    //if no add new node
    if(node->country != '\0' && strcmp(node->country, "") != 0 && last->country != '\0'){
        if(strcmp(last->country, node->country) ==  0){
            int cases = atoi(last->totalCases) + atoi(node->totalCases);
            itoa(cases, last->totalCases, 10);
            int icu = atoi(last->totalICU) + atoi(node->totalICU);
            itoa(icu, last->totalICU, 10);
            int vacc = atoi(last->totalVacc) + atoi(node->totalVacc);
            itoa(vacc, last->totalVacc, 10);
            int deaths = atoi(last->totalDeaths) + atoi(node->totalDeaths);
            itoa(deaths, last->totalDeaths, 10);
            int hosp = atoi(last->totalHosp) + atoi(node->totalHosp);
            itoa(hosp, last->totalHosp, 10);
            int tests = atoi(last->totalTests) + atoi(node->totalTests);
            itoa(tests, last->totalTests, 10);
            return;
        }
    }

    //5. Change the next of last node
    last->next = node;
}

//get coulmns data from file
//the needed data are: location, new_cases, icu_patients, total_vaccinations
struct Node* getFields(char* line, int num[]){
	char field[100] = "";
    char ch;
    //allocate new node to save data in
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	while(line != "\n"){
        ch = line[0];
        if(ch != ','){
            //append ch to field
            strncat(field, &ch, 1);
        }
        else{
            //reached end of column
            //check if it belongs to one of the needed columns
            if (!--num[0]){
                //column location
                node->country = malloc(sizeof(*(node->country)) * 100);
                strcpy(node->country, field);
            }

            if (!--num[1]){
                //column new_cases
                node->totalCases = malloc(sizeof(*(node->totalCases)) * 100);
                strcpy(node->totalCases, field);
            }

            if(!--num[2]){
                //column new_deaths
                node->totalDeaths = malloc(sizeof(*(node->totalDeaths)) * 100);
                strcpy(node->totalDeaths, field);
            }

            if (!--num[3]){
                //column icu_patients
                node->totalICU = malloc(sizeof(*(node->totalICU)) * 100);
                strcpy(node->totalICU, field);
            }

            if(!--num[4]){
                //column hosp_patients
                node->totalHosp = malloc(sizeof(*(node->totalHosp)) * 100);
                strcpy(node->totalHosp, field);
            }

            if(!--num[5]){
                //column new_tests
                node->totalTests = malloc(sizeof(*(node->totalTests)) * 100);
                strcpy(node->totalTests, field);
            }

            if (!--num[6]){
                //column total_vaccinations
                node->totalVacc = malloc(sizeof(*(node->totalVacc)) * 100);
                strcpy(node->totalVacc, field);
                break;
            }

            strcpy(field, "");
        }
        line++;
	}
    return node;
}

int main(){
    //string for file path
    char fn[] = "owid-covid-data.csv";
    FILE *fp = fopen(fn, "r");

    if(!fp){
        //failed to open file
        printf("Can't open file\n");
    }
    else{
        char* buffer = NULL;
        int len = 1024;
        struct Node* head = NULL;
        
        //get first line
        getline(&buffer, &len, fp);
        while(getline(&buffer, &len, fp)){
            int num[] = {3, 6, 9, 18, 20, 27, 35};
            struct Node* node = getFields(buffer, num);

            //display first 8 locations only for sample output
            if(countList(head) <= 7){
                append(&head, node);
            }
            else{
                break;
            }
        }

        printList(head);
    }

    fclose(fp);
    return 0;
}