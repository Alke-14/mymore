/* 
 * mymore.c --  simplified version of Linux more command
 * This command reads a file and prints the first 24 lines. 
 * Then, the program pauses for a few special commands to continue or quit.
 * 
 * ADDITIONAL EDITS MADE BY: Kevin A Hernandez Garcia
 */

 #include <stdio.h>
 #include <stdlib.h>
 
 #define PAGELEN 24  /* Number of lines per page */
 #define LINELEN 512 /* Maximum line length */
 
 void do_more(FILE *);   /* Function prototype */
 int see_more();
 
 /* The main function */
 int main (int ac, char *av[])
 {
     FILE *fp; /* File pointer */
 
     if( ac == 1 ) {
         printf("No entry file to display\n"); // Display error if no file is provided
         exit(1); // Read from standard input
     }
     else {
         int file_not_found = 0;
         while( --ac ) 
         {
             if( (fp=fopen( *++av, "r")) != NULL) // Check if the first file can be found                 
             {
                 do_more (fp);   
                 fclose(fp);    
             }
             else 
             {
                 
                 printf("Cannot open file %s\n", *av); // display error if the first file cannot be found 
                 file_not_found = 1;  
             }
         }
         if (file_not_found) {// Exit if the second file cannot be found
             exit(1);
         }
    }
    return 0; // Exit successfully
 }
    
 /* Read PAGELEN lines, then call see_more() for further instructions */
 void do_more(FILE *fp)
 {
     char line[LINELEN]; // Buffer to hold each line
     int num_of_lines = 0;
     int reply;
 
     while( fgets(line, LINELEN, fp) )      
     {       
         if( num_of_lines == PAGELEN ) 
         {   
             reply = see_more();
             if(reply == 0)     
                 break; // Exit on 'q'
             num_of_lines -= reply;    
         }
         if( fputs(line, stdout) == EOF )  
         {
             printf("Cannot write to output\n"); // Display error if writing to output fails
             exit(1); // Exit if writing to output fails
         }
         num_of_lines++;                  
     }
 }
 
 /* Display prompt and wait for user response
    q: quit, space: next page, enter: next line */
 int see_more()
 {
     int c;
     printf("\033[7m more? q: quit, space: next page, enter: next line  \033[m"); // Display "more?" in reverse video
     while( (c=getchar()) != EOF)    
     {           
         if(c=='q')                          
             return 0;                       
         if(c==' ')                          
             return PAGELEN;                 
         if(c=='\n')        
             return 1;
     }
     return 0;
 }
 