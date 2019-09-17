/**************************************************************/
/*                                                            */
/*   Program to demonstrate the implmentation of a            */
/*   linked list of books in a library.				      */
/*                                                            */
/**************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define bool int
#define false 0
#define true (!false)

//Libraries
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


//Preprocessor Variable
#define SIZE 10

//Stucture template for data part of a LinearNode
struct book {
	char id[9];
	char bookName[80];
	char author[80];
	int year;
	bool loaned;
	char customerName[80];
	int timesLoaned;
};

//Stucture template for one node
struct LinearNode {
	struct book *element;
	struct LinearNode *next;
};


// Function prototypes
void input(FILE *); //displays menu to user
void addBook();  //adding books to end of the list
bool checkId(char *); //checks ID format
void borrowBook(); //lets user borrow a book from the list
void returnBook(); //lets user return a book
void writeToFile(FILE *); //write list of books to file
void readFromFile(FILE *); // reads in a list of books from file
void deleteBook(); // delete a specific book
void viewBook(); //displays a specific book from the list
void viewAllBooks(); //displays all books in the list
void bookPopularity(); //displays most and least popular books
bool isEmpty(); //checks if list has any books




				// Global Variables
struct LinearNode *front = NULL;
struct LinearNode *last = NULL;
bool read = false;
/**************MAIN FUNCTION*******************/
int main() {
	FILE *fp;
	
	if ((fp = fopen("book.dat", "rb")) == NULL) {
	printf("User database does not exist, you need to add books\n");
	addBook();
	}
	else if (read == false) {
	read = true;
	readFromFile(fp);
	viewAllBooks();
	printf("Books have been populated\n\n");
	}

	input(fp);

	getchar();
	getchar();
}

void input(FILE *fp) {
	
	
	int choice;
	
	do {
		printf("Press 1 to add a new book to the library\n");
		printf("Press 2 to take out a book \n");
		printf("Press 3 to return a book\n");
		printf("Press 4 to delete an old book from stock\n");
		printf("Press 5 to view all books \n");
		printf("Press 6 to view a specific book\n");
		printf("Press 7 to view details of most popular and least popular books\n");
		printf("Press 8 to custom\n");
		printf("Press 9 to exit the system\n");
		printf("Enter your choice:\n");
		scanf("%d", &choice);

		switch (choice) {
		case 1: {
			addBook();
			break;
		}
		case 2: {
			borrowBook();
			break;
		}
		case 3: {
			returnBook();
			break;
		}
		case 4: {
			deleteBook();
			break;
		}
		case 5: {
			viewAllBooks();
			break;
		}
		case 6: {
			viewBook();
			break;
		}
		case 7: {
			bookPopularity();
			break;
		}
		/*
		case 8: {

		input();
		break;
		}
		*/
		case 9: {
			printf("All books will be copied to books.dat\n");
			writeToFile(fp);
			break;
		}

		default:
			printf("wrong Input\n");
		}
	} while (choice != 9);
}

void addBook() {
	if (SIZE <= 10) {
		bool error = false;
		int choice = 0;
		struct LinearNode *aNode;
		struct book *anElement;
		char id[9];
		int year;
		//Create space for book part of node
		anElement = (struct book *)malloc(sizeof(struct book));


		if (anElement == NULL)
			printf("Error - no space for the new element\n");
		else
		{
			//Input value into the book part
			printf("Enter id of the book\n");
			scanf("%s", id);
			while(checkId(id)){
				printf("ID format error, please try again\n");
				scanf("%s", id);
				checkId(id);
			}
				strcpy(anElement->id , id);
				printf("Enter name of the book\n");
				scanf("%s", anElement->bookName);
				printf("Enter author of the book\n");
				scanf("%s", anElement->author);
				printf("Enter year of the book\n");
				scanf("%d", &year);
				if (year < 2008) { printf("Book cannot be older than 2008\n"); }
				else {
					anElement->year = year;
					printf("Is the book loaned?\nEnter 1 if yes and 0 if no\n");
					scanf("%d", &choice);
					switch (choice) {
					case 0: {
						anElement->loaned = false;
						anElement->timesLoaned = 0;
						break;
					}
					case 1: {
						anElement->loaned = true;
						anElement->timesLoaned = 1;
						break;
					}
					default:
						printf("wrong Input\n");
					}
					if (anElement->loaned == true) {
						printf("Enter customer name\n");
						scanf("%s", anElement->customerName);
					}
					else
						strcpy(anElement->customerName, "");
					// create space for new node that will contain book
					aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));

					if (aNode == NULL)
						printf("Error - no space for the new node\n");
					else { // add book part to the node
						aNode->element = anElement;
						aNode->next = NULL;

						//add node to end of the list
						if (isEmpty())
						{
							front = aNode;
							last = aNode;
						}
						else {
							last->next = aNode;
							last = aNode;
						} //end else	
					}//end else
				}//end else 
			}
		
	}
	else
		printf("Maximum number of books is 10");
} //end addBook

bool checkId(char *id){
	bool error = false;
	if (strlen(id) < 9) {
				//printf("ID is too short\n");
				error = true;
			}
			else{
				for (int i = 0; id[i] != '\0'; i++) {
					if (i < 4 || i >4) {
					if (!isdigit(id[i]))
						error = true;}
	 				else {
					if (!ispunct(id[i]))
						error = true;}
			//	printf("%c at position %d\n", id[i], i);
				}
			}			
	return error;		
}

void borrowBook() {
	struct LinearNode *current;
	char id[9];
	char name[80];
	bool found = false;
	printf("\n");
	printf("Enter book ID to be borrowed\n");
	scanf("%s", id);
	current = front;

	while (current != NULL) {
		if (strcmp(current->element->id, id) == 0) {
			found = true;
			if (current->element->loaned != true) {
				current->element->loaned = true;
				printf("Enter customer name\n");
				scanf("%s", name);
				strcpy(current->element->customerName, name);
				current->element->timesLoaned += 1;
			}//end if
			else
				printf("Book is already borrowed\n");
			break;
		}//end   
		else
			current = current->next;
	}//end while

	if (found == false)
		printf("Book is not in the list\n");
}

void returnBook() {
	struct LinearNode *current;
	char id[9];
	char name[80];
	bool found = false;
	printf("\n");
	printf("Enter ID of book borrowed\n");
	scanf("%s", id);
	printf("Enter name of customer\n");
	scanf("%s", name);
	current = front;

	while (current != NULL) {
		if (strcmp(current->element->id, id) == 0) {
			found = true;
			if (current->element->loaned != true)
				printf("Book is not loaned\n");
			else {
				if (strcmp(current->element->customerName, name) == 0) {
					current->element->loaned = false;
					strcpy(current->element->customerName, "");
					printf("Book %s has been returned\n", id);
				}//end if
				else
					printf("Book has been borrowed under a different name\n");
			}//end else
			break;
		}//end if   
		else
			current = current->next;
	}//end while

	if (found == false)
		printf("Book is not in the list\n");
}

bool isEmpty() {
	if (front == NULL)
		return true;
	else
		return false;
}

void writeToFile(FILE *fp) {
	struct LinearNode *current;
	current = front;
	fp = fopen("book.dat", "wb");
	if (fp != NULL) {
		while ( current != NULL) {
			fwrite(current->element, sizeof(struct book), 1, fp);
			printf("Writing:%s to file\n", current->element->id);
			current = current->next;
		}
	}
	else
		printf("Error opening file\n");
	fclose(fp);

}

void readFromFile(FILE *fp) {
	struct LinearNode *node;
	struct book *element;
	element = (struct book *)malloc(sizeof(struct book));
	//Try casting to book or linear node
	node = NULL;
	fp = fopen("book.dat", "rb");
	if (fp != NULL) {
		fseek(fp, 0, SEEK_END);
		long fileSize = ftell(fp);
		rewind(fp);
		int numEntries = (int)(fileSize / sizeof(struct book));
		printf("numEntries: %d\n", numEntries);

		
		while (fread(element, sizeof(struct book), 1, fp) != NULL) {
			node = (struct LinearNode *)malloc(sizeof(struct LinearNode));
			if (node == NULL)
				printf("Error - no space for the new node\n");
			else { // add book part to the node
				node->element = element;
				node->next = NULL;
				
				//add node to end of the list
				if (isEmpty())
				{
					front = node;
					last = node;
					printf("in if(isEmpty())\n");
				}
				else {
					last->next = node;
					last = node;
					printf("in else\n");
				} //end else
				printf("Book ID: %s\n", node->element->id);
				/*
			printf("Book ID: %s\n", current->element->id);
			printf("Book name: %s\n", current->element->bookName);
			printf("Book author: %s\n", current->element->author);
			printf("Book year: %d\n", current->element->year);

			if (current->element->loaned == true) {
				printf("Book availability: unavailable\n");
				printf("Book loaned by: %s\n", current->element->customerName);
			}
			else
				printf("Book availability: available\n");

			printf("Book has been loaned %d times\n\n", current->element->timesLoaned);
			*/
			}//end else
			
		}
	}
	else
		printf("File open error");
	fclose(fp);
}

void viewAllBooks() {
	struct LinearNode *current;

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the list\n\n");
	else {
		current = front;
		while (current != NULL) {
			printf("Book ID: %s\n", current->element->id);
			printf("Book name: %s\n", current->element->bookName);
			printf("Book author: %s\n", current->element->author);
			printf("Book year: %d\n", current->element->year);

			if (current->element->loaned == true) {
				printf("Book availability: unavailable\n");
				printf("Book loaned by: %s\n", current->element->customerName);
			}
			else
				printf("Book availability: available\n");

			printf("Book has been loaned %d times\n\n", current->element->timesLoaned);
			current = current->next;
		} //end while
	}//end else

} //end viewAllNodes

void deleteBook() {
	struct LinearNode *current, *previous;
	bool notFound = true;
	char id[9];

	printf("\n");
	if (isEmpty())
		printf("Error - there are no nodes in the list\n");
	else {
		printf("Enter ID of book to be deleted\n");
		scanf("%s", id);
		current = previous = front;

		while (notFound && current != NULL) {
			if (strcmp(current->element->id, id) == 0)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}//end else
		} //end while

		if (notFound)
			printf("Error - there is not such book with ID %s\n", id);
		else {
			if (current->element->year > 2009)
				printf("Only books older than 2010 can be deleted\n\n");
			else {
				if (current == front) { //delete front node
					front = front->next;
					free(current);
				} //end else
				else if (current == last) {//delete last node
					free(current);
					previous->next = NULL;
					last = previous;
				}
				else {//delete node in middle of list
					previous->next = current->next;
					free(current);
				} //end else
				printf("Book with ID %s has been deleted\n\n", id);
			}
		}//end else
	}//end else
}// end deleteBook

void viewBook() {



	struct LinearNode *current;
	bool notFound = true;
	char id[9];

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the list\n\n");
	else {
		printf("Enter ID of book you want to view\n");
		scanf("%s", id);

		current = front;
		while (current != NULL) {
			if (strcmp(current->element->id, id) == 0) {
				notFound = false;
				printf("Book ID: %s\n", current->element->id);
				printf("Book name: %s\n", current->element->bookName);
				printf("Book author: %s\n", current->element->author);
				printf("Book year: %d\n", current->element->year);

				if (current->element->loaned == true) {
					printf("Book availability: unavailable\n");
					printf("Book loaned by: %s\n", current->element->customerName);
				}
				else
					printf("Book availability: available\n");

				printf("Book has been loaned %d times\n\n", current->element->timesLoaned);
				break;
			}
			else
				current = current->next;

			if (notFound == true)
				printf("Book is not in the list\n");
		} //end while
	}//end else
}

void bookPopularity() {
	struct LinearNode *current;
	int lp = front->element->timesLoaned;
	int mp = front->element->timesLoaned;
	char mpId[9];
	char lpId[9];
	strcpy(lpId, front->element->id);
	strcpy(mpId, front->element->id);

	current = front;
	if (isEmpty())
		printf("Error - there are no nodes in the list\n");
	else {
		while (current != NULL) {
			if (current->element->timesLoaned < lp) {
				lp = current->element->timesLoaned;
				strcpy(lpId, current->element->id);
			}

			if (current->element->timesLoaned > mp) {
				mp = current->element->timesLoaned;
				strcpy(mpId, current->element->id);
			}
			current = current->next;
		}//end while

		printf("Most popular book is %s\n", mpId);
		printf("Least popular book is %s\n", lpId);
	}//end else

}
