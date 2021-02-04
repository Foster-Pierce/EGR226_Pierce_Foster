#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
char title[255];
char author_name[50];
char ISBN[10];
int pages;
int year_published;
}book;

void print_book(book books);
void search_title(book book_array[],int MaxElements, char titles[]);
void search_author(book book_array[],int MaxElements,char authors[]);
void search_ISBN(book book_array[],int MaxElements,char ISBNs[]);

#define MaxElements 360

int main()
{
book book_array[MaxElements];
char filename[] = {"BookList.csv"};
char titles[255], authors[50], ISBNs[10];

int i, input,num=0, decision=1;
parse_file(filename, book_array);

for (i=0;i<MaxElements;i++){
print_book(book_array[i]);
}
while (decision!=0){
printf("[0] Search by Title\n[1] Search by Author Name\n[2] Search by ISBN\n");
scanf("%d",&input);

if (input==0){
search_title(book_array,MaxElements,titles);

}
else if (input ==1){
search_author(book_array,MaxElements,authors);

}
else if (input ==2){
search_ISBN(book_array,MaxElements,ISBNs);

}

else
    printf("error, try again");
printf("to try again press '1' or '0' to quit: \n");
scanf("%d",&decision);
}
    return 0;
}

void print_book(book books){
char n_a[] = {"N/A"};
if (books.pages == -1)
printf("Title: %s\nAuthor: %s\nISBN: %s\nPages: N/A\nYear Published: %d\n", books.title,books.author_name,books.ISBN,books.year_published);
else if (books.year_published == -1)
printf("Title: %s\nAuthor: %s\nISBN: %s\nPages: %d\nYear Published: N/A\n", books.title,books.author_name,books.ISBN,books.pages);
else if ((books.pages == -1) && (books.year_published == -1))
printf("Title: %s\nAuthor: %s\nISBN: %s\nPages: N/A\nYear Published: N/A\n", books.title,books.author_name,books.ISBN);
else
    printf("Title: %s\nAuthor: %s\nISBN: %s\nPages: %d\nYear Published: %d\n", books.title,books.author_name,books.ISBN,books.pages,books.year_published);
}
/*-----------------------------------------------------------
* Function: parse_file
* Description: Sift through a file of books to populate
* an empty book array
* Inputs:
* (char*) filename: file to open and parse
* (book*) book_array: array of book structures to
* populate
* Outputs:
* (int) parse status, 1 if successful, 0 otherwise.
*---------------------------------------------------------*/
int parse_file(char filename[], book book_array[]) {
 FILE* infile = fopen(filename, "r"); // Attempt to open file
 if (infile == NULL) // Return 0 (failure) if file could not open
 return 0;

 char buffer[512]; // Create temporary string buffer variable
 int i = 0; // Indexer for book array

 while (fgets(buffer, 512, infile)) { // Loop collecting each line from the file

 char * ptr = strtok(buffer,",\n"); // Parse string by commas and newline
 if(strcmp(ptr,"N/A")) // Validate string
    strcpy(book_array[i].title,ptr);// First parse is title
 else
    strcpy(book_array[i].title,"N/A");


  ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
    strcpy(book_array[i].author_name,ptr);
 else
    strcpy(book_array[i].author_name,"N/A");


  ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
    strcpy(book_array[i].ISBN,ptr);
 else
    strcpy(book_array[i].ISBN,"N/A");


  ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
    book_array[i].pages = atoi(ptr);
 else
    book_array[i].pages = -1;


  ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
    book_array[i].year_published = atoi(ptr);
 else
    book_array[i].year_published = -1;
 i++;
 }

 return 1;
}
void search_title(book book_array[],int num , char titles[]){
char tsearch[50];
int i;

printf("enter title:\n");
scanf("%s", &tsearch);
for(i=0;i<MaxElements;i++){
  if (strstr(book_array[i].title,tsearch)){
    print_book(book_array[i]);
  }
}
}

void search_author(book book_array[],int num,char authors[]){
char tsearch[50];
int i;

printf("enter author name:\n");
scanf("%s", &tsearch);
for(i=0;i<MaxElements;i++){
  if (strstr(book_array[i].author_name,tsearch)){
    print_book(book_array[i]);
  }
}


}

void search_ISBN(book book_array[],int num,char ISBNs[]){
char tsearch[50];
int i;

printf("enter ISBN code:\n");
scanf("%s", &tsearch);
for(i=0;i<MaxElements;i++){
  if (strstr(book_array[i].ISBN,tsearch)){
    print_book(book_array[i]);
  }
}


}

