#include <stdio.h>
#include <stdlib.h>

typedef struct {
char title[255];
char author_name[50];
char ISBN[10];
int pages;
int year_published;
}book;

void print_book(book_array);
void search_title(book book_array,int MaxElements, char);
void searth_author();
void search_ISBN();


#define MaxElements 360

int main()
{
book book_array[MaxElements];
printf("[0] Search by Title\n[1] Search by Author Name\n[2] Search by ISBN\n");

print_book(book_array);

    return 0;
}

void print_book(book_array){
int i;

for(i=0;i<360;i++){
    printf("Title: %c", book_array[i].title);
}



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
 char * ptr = strtok(buffer,","); // Parse string by commas and newline
 if(strcmp(ptr,"N/A")) // Validate string
 strcpy(book_array[i].title,ptr);// First parse is title

 char none="N/A";

 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
 strcpy(book_array[i].author_name,ptr);
 if(book_array[i].author_name == "N/A")
 strcpy(book_array[i].author_name,none);

 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
 strcpy(book_array[i].ISBN,ptr);
 if(book_array[i].ISBN == "N/A")
 strcpy(book_array[i].ISBN,none);

 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
 strcpy(book_array[i].pages,ptr);
 if(book_array[i].pages == "N/A")
 book_array[i].pages=(char)"N/A";

 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
 strcpy(book_array[i].year_published,ptr);
 if(book_array[i].year_published == "N/A")
 book_array[i].year_published=(char)"N/A";
 i++;
 }

 return 1;
}
