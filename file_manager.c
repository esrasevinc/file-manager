#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SIZE 1000

// function to create a file
void createFile(char *fileName)
{
    FILE *fp;  // file pointer
    // check if the file already exists
    if (fp=fopen(fileName,"r")) // open file with read mode
    {
      fclose(fp);
      printf("File already exists!\n");
    }
    else
    {
      fp=fopen(fileName,"w"); // open file with write mode
      printf("File created successfully.\n");
    }
}


// function to rename a file
void renameFile(char *oldName, char *newName)
{
    // rename() function takes the existing file name and new file names as arguments and renames the file
    if (rename(oldName, newName) == 0)  // rename() returns 0 if the file is renamed successfully, else it returns a non-zero value
    {                            
        printf("File renamed successfully.\n");
    }
    else
    {
        printf("Unable to rename files. Please check files exist and you have permissions to modify files.\n");
    }
}


// function to copy a file
void copyFile(char *sourceFile, char *targetFile)
{
   FILE *source, *target;
   char ch;
   // Open source file for reading
   source = fopen(sourceFile, "r");

   if (source == NULL)
   {
      printf("Cannot open file %s \n", sourceFile);
   }
   // Open target file for writing
   target = fopen(targetFile, "w");

   if (target == NULL)
   {
      fclose(source);
      printf("Cannot open file %s \n", targetFile);
   }

   while ((ch = fgetc(source)) != EOF) // read contents from file until source equals to EOF
      fputc(ch, target); // writing single character into file 

   printf("File copied successfully.\n");
   fclose(source); // closing the file pointers
   fclose(target);
}


// function to remove a file
void removeFile(char *fileName)
{
  int status;
  status = remove(fileName); // the remove() function can be used to delete a file

  if (status == 0) // the function returns 0 if files is deleted successfully, other returns a non-zero value
    printf("%s file deleted successfully.\n", fileName);
  else
  {
    printf("Unable to delete the file\n");
    perror("Following error occurred");
  }
}


// function to append text to the end of a file
void appendData(char *filePath)
{
  FILE * fptr;  // file pointer to hold reference of input file
  int i,n; 
  char str[100];
		
  fptr = fopen(filePath, "a"); // open all file in append mode
  // fopen() return NULL if unable to open file in given mode
  if (fptr == NULL)
  {
    printf("\nUnable to open '%s' file.\n", filePath);
    printf("Please check whether file exists and you have write privilege.\n");
  }
  scanf("%d", &n); 
  for(i = 0; i < n+1;i++)
  {
    fgets(str, sizeof str, stdin); // input data to append from user
    fputs(str, fptr); // append data to file
  }
  printf("Data succesfully appended.\n");
  fclose (fptr);
}


// function to remove all text present in a file
void deleteAllContent(char *fileName)
{
  fclose(fopen(fileName, "w")); // write: create an empty file for output operations
  // if a file with the same name already exists, its contents are discarded and the file is treated as a new empty file
  printf("Content succesfully deleted.\n");
}


// function to show the content of a text data store, with the ability to pause per page
void display(char *fileName, char *num)
{
    FILE *fp; 
    char ch[200];
    char answer[10];
    int line = 0;
    int number = atoi(num); // the number of lines per page
    // open file with read mode
    if((fp=fopen(fileName,"r"))==NULL)
    {
        printf("File cannot be opened!\n");
    }
    else{
        while (!feof(fp)){ // until it reaches the end of the file (by checking the feof() function), it writes the character it reads to the screen
            if (line < number){
                if (fgets(ch,200,fp)) // write to the screen along the line
                    printf("%s",ch);
                line+=1;
            }
            if (line == number){  // if the screen finishes typing, it prompts the user to press the c key to continue
                printf("Press 'c' to continue.\n");
                scanf("%s",answer);
                if (strcmp(answer,"c") == 0){  // comparing strings answer and c, it does the operation if the strings are equal
                    line = 0;
                }
            }
        }
        fclose(fp);
    }
}


// function to move a file from one folder to another
void moveFile(char *file, char *target)
{
  strcat(target,"/"); // concatenates target and "/"
  strcat(target, file); // concatenates target and file
  copyFile(file, target); // copying the file with copyFile() function to target
  remove(file); // remove source file
}


// function to insert text in a specific position within the file 
void appendSpecificPlace(char *fileName, char *index, char *data)
{
    FILE *fp;  
    char first[200],end[200],ch;  // first reads and stores from the beginning of the file to the index entered, 
    // end reads from the entered index to the end of the file and stores it
    int counter=0;
    int ind = atoi(index);  // it keeps which index we want to insert
    if((fp=fopen(fileName,"r"))==NULL)  // open file with read mode and error if file does not exist
    {
        printf("File cannot be opened!");
    }
    
    else{
        while (counter < ind) { // fill the first string
            ch = fgetc(fp);
            first[counter] = ch;
            counter++;
        }
        fseek(fp,ind,SEEK_SET);  // reset the read pointer at the index entered from the beginning
        counter=0;
        // fill the end string
        while(ch != EOF){  // until ch equals to eof
            ch = fgetc(fp);  // taking input single character at a time
            end[counter] = ch;
            counter++;
        }
        fclose(fp);
        fp = fopen(fileName,"w");  // open file with write mode
        fputs(first,fp);  // adding first,data,end respectively to data
        fputs(data,fp);
        fputs(end,fp);
        printf("Data appended successfully.\n");
        fclose(fp);
    }
}

int main()
{
    char command[10];  // keeps command received from user
    char arg[50];  // keeps the desired operation command
    char arg2[50];
    char arg3[50];
    printf("Welcome to our file management system!\n");
    printf("Enter [help command name] to get help.\n");
    printf("Enter 'q' to quit.\n");
    printf("Enter your command: ");
    scanf("%s", command);

    while(strcmp(command, "q") != 0){  // if the user presses q, they will exit the manager
      if (strcmp(command, "help") == 0){ // if the user types help followed by the desired action, it will show the usage of the command
          scanf("%s",arg);

          if (strcmp(arg,"create") == 0)  // help property for create command
            printf("'create' command helps us to create a new file:\ncreate [filename]\n");
          
          else if (strcmp(arg,"remove") == 0)  // help property for remove command
            printf("'remove' command helps us to remove a file:\nremove [filename]\n");

          else if (strcmp(arg,"rename") == 0)  // help property for rename command
            printf("'rename' command helps us to rename a file: rename [filename newname]\n");

          else if (strcmp(arg,"copy") == 0)   // help property for copy command
            printf("'copy' command helps us to copy a file:\ncopy [filename targetname]\n");

          else if (strcmp(arg,"append") == 0)  // help property for append command
            printf("'append' command helps us to append data to a txt file:\nappend [filename data]\n");

          else if (strcmp(arg,"clear") == 0)  // help property for clear command
            printf("'clear' command helps us to clear a txt file's content:\nclear[filename]\n");

          else if (strcmp(arg,"display") == 0)  // help property for display command
            printf("'display' command helps us to display a file:\ndisplay [filename line_num]\n");

          else if (strcmp(arg,"move") == 0)   // help property for move command
            printf("'move' command helps us to move a file from a directory:\nmove [filename newpath]\n");

          else if (strcmp(arg,"appendto") == 0)   // help property for appendto command
            printf("'appendto' command helps us to append data to a specific place in a file:\nappendto [filename data index]\n");

          else {  // gives an error message if an invalid command is entered
            printf("Wrong choice. Try again!\n");

          }
      }

      else if (strcmp(command, "create") == 0){  // call the createFile function if the create command is entered
            scanf("%s",arg);
            createFile(arg);
      }

      else if (strcmp(command, "remove") == 0){  // call the removeFile function if the remove command is entered
            scanf("%s",arg);
            removeFile(arg);
      }
    
      else if (strcmp(command, "rename") == 0){  // call the renameFile function if the rename command is entered
            scanf("%s %s",arg,arg2);
            renameFile(arg,arg2);
      }

      else if (strcmp(command, "copy") == 0){   // call the copyFile function if the copy command is entered
            scanf("%s %s",arg,arg2);
            copyFile(arg,arg2);
      }

      else if (strcmp(command, "append") == 0){  // call the appendData function if the append command is entered
            scanf("%s",arg);  
            appendData(arg);
      }

      else if (strcmp(command, "display") == 0){   // call the display function if the display command is entered
            scanf("%s %s",arg,arg2);
            display(arg,arg2);
      }
        
      else if (strcmp(command, "clear") == 0){  // call the deleteAllContent function if the clear command is entered
            scanf("%s",arg);
            deleteAllContent(arg);
      }

      else if (strcmp(command, "move") == 0){   // call the moveeFile function if the move command is entered
            scanf("%s %s",arg,arg2);
            moveFile(arg,arg2);
      }

      else if (strcmp(command, "appendto") == 0){  // call the appendSpecificPlace function if the appendto command is entered
            scanf("%s %s %s",arg,arg2,arg3);
            appendSpecificPlace(arg,arg2,arg3);
      }

      else   // gives an error message if an invalid command is entered
        printf("Wrong choice. Try again!\n");

      printf("Enter your command: ");
      scanf("%s", command);
  }

  printf("Thank you for using our file management system. Good bye!\n");
  exit(0);
    
  return 0;
}