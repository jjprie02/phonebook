#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//structs
typedef struct {
	char firstname[20];
	char lastname[20];
	char phonenumber[20];
} Friend;

//global variables
int user_input = 0;
int size = 0;
char searchfirst[20];
char searchlast[20];
int sizeofarray = 0;
int deleteordont = 0;
char filename[20];

//compare function for sorting alphabetically
int compare(const void *a, const void *b) {
	Friend *friendA = (Friend *)a;
	Friend *friendB = (Friend *)b;
	
	return strcmp(friendA->firstname, friendB->firstname);
}

//function declarations
void addfriend(Friend **arrayofstructs, int *size);
void deletefriend(Friend **arrayofstructs, int *size);
void showphonebook(Friend *arrayofstructs, int size);
void sortalphabetically(Friend *arrayofstructs, int *size);
void findphonenumber(Friend *arrayofstructs, int *size);
void randfriendselect(Friend *arrayofstructs, int size);
void deleteall(Friend **arrayofstructs, int *size);
void savefile(Friend *arrayofstructs, int *size);

// main function
int main() {
	Friend *arrayofstructs;
	arrayofstructs = malloc(sizeof(Friend) * size);
	srand(time(NULL));
	
	do {
		printf("\n\nPhone Book Application\n\t1) Add friend\n\t2) Delete friend\n\t3) Show phone book\n\t4) Sort phone book alphabetically");
		printf("\n\t5) Find phone number\n\t6) Select a friend to call randomly\n\t7) Delete everyone in phone book\n\t8) Exit\n\t9) Store phone book\n\nWhat do you want to do: ");
		
		// input validation loop
        while (scanf("%d", &user_input) != 1 || user_input < 1 || user_input > 9) {
            printf("Invalid input. Please enter a number between 1 and 9: ");
            // clear invalid input
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
	
		switch (user_input) {
			case 1: {
				addfriend(&arrayofstructs, &size);
				break;
			}
			case 2: {
				deletefriend(&arrayofstructs, &size);
				break;
			}
			case 3: {
				showphonebook(arrayofstructs, size);
				break;
			}
			case 4: {
				sortalphabetically(arrayofstructs, &size);
				break;
			}
			case 5: {
				findphonenumber(arrayofstructs, &size);
				break;
			}
			case 6: {
				randfriendselect(arrayofstructs, size);
				break;
			}
			case 7: {
				deleteall(&arrayofstructs, &size);
				break;
			}
			case 8: {
				break;
			}
			case 9: {
				savefile(arrayofstructs, &size);
				break;
			}
		}
	} while (user_input != 8);
	
	free(arrayofstructs);
	return 0;
}

//function definitions-

void addfriend(Friend **arrayofstructs, int *size) {
	(*size)++;
	*arrayofstructs = realloc((*arrayofstructs), sizeof(Friend) * (*size));
		if (*arrayofstructs == NULL) {
		printf("Failed to reallocate memory for arrayofstructs\n\n");
	}
		
	printf("First name: ");
	scanf("%19s", (*arrayofstructs)[(*size) - 1].firstname);
	
	printf("Last name: ");
	scanf("%19s", (*arrayofstructs)[(*size) - 1].lastname);
	
	printf("Phone number: ");
	scanf("%19s", (*arrayofstructs)[(*size) - 1].phonenumber);
	
	printf("Record added to the phone book.");
}

void deletefriend(Friend **arrayofstructs, int *size) {

	printf("First name: ");
	scanf("%s", searchfirst);
	printf("Last name: ");
	scanf("%s", searchlast);

	int found = -1;
	
	for (int i = 0; i < *size; i++) {
		if((strcmp((*arrayofstructs)[i].firstname, searchfirst) == 0) && (strcmp((*arrayofstructs)[i].lastname, searchlast) == 0)) {
			found = i;
			break;
		}	
	}
	
	if (found == -1) {
		printf("This person does not exist\n");
		return;
	}
	
	for (int i = found; i < (*size) - 1; i++) {
		(*arrayofstructs)[i] = (*arrayofstructs)[i + 1];
	}
	
	(*size)--;
	*arrayofstructs = realloc(*arrayofstructs, sizeof(Friend) * (*size));
	if (*arrayofstructs == NULL && *size > 0) {
		printf("Failed to reallocate memory for arrayofstructs\n\n");
		exit(1);
	}
	
	printf("Person has been deleted.");
}

void showphonebook(Friend *arrayofstructs, int size) {
	printf("\n\nPhone Book Entries: \n");
	for (int i = 0; i < size; i++) {
		printf("%s %s %s\n", arrayofstructs[i].firstname, arrayofstructs[i].lastname, arrayofstructs[i].phonenumber);
	}	
}

void sortalphabetically(Friend *arrayofstructs, int *size) {
	qsort((arrayofstructs), (*size), sizeof(Friend), compare);
}

void findphonenumber(Friend *arrayofstructs, int *size) {

	printf("First name: ");
	scanf("%s", searchfirst);
	printf("Last name: ");
	scanf("%s", searchlast);

	int found = -1;
	
	for (int i = 0; i < *size; i++) {
		if((strcmp(arrayofstructs[i].firstname, searchfirst) == 0) && (strcmp(arrayofstructs[i].lastname, searchlast) == 0)) {
			found = i;
			break;
		}	
	}
	
	if (found == -1) {
		printf("This person does not exist\n");
		return;
	}
	
	printf("That person's phone number is %s", arrayofstructs[found].phonenumber);
}

void randfriendselect(Friend *arrayofstructs, int size) {
	if (size == 0) {
		printf("The phone book is currently empty.\n");
		return;
	}
	
	int temprandom = rand() % size;
	printf("You should call %s %s, their phone number is %s.", arrayofstructs[temprandom].firstname, arrayofstructs[temprandom].lastname, arrayofstructs[temprandom].phonenumber);
}

void deleteall(Friend **arrayofstructs, int *size) {
	
	printf("Are you sure you want to delete every person in the phone book? This action cannot be undone. ");
	printf("\nEnter '1' to proceed, or '2' to cancel process.");
	scanf("%d", &deleteordont);

	if (deleteordont == 1) {
		free(*arrayofstructs);
		*arrayofstructs = NULL;
		*size = 0;
		printf("All entries have been deleted.\n\n");
	}
	
}

void savefile(Friend *arrayofstructs, int *size) {
	
	printf("What would you like to name the file this information will be saved to?: ");
	scanf("%s", filename);
	
	// open file stream
	FILE* file_pointer = fopen(filename, "w");
	if (file_pointer == NULL) {
		printf("\n\n\nError in opening file for writing.\n\n\n");
		return;
	}
	
	// stores all information into file
	for (int i = 0; i < (*size); i++) {
		fprintf(file_pointer, "%s %s %s\n", arrayofstructs[i].firstname, arrayofstructs[i].lastname, arrayofstructs[i].phonenumber);
	}
	
	//close file stream
	fclose(file_pointer);
	printf("Phonebook has been saved successfully.");
}