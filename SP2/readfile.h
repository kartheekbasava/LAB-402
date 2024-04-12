#ifndef _READFILE_H_
#define _READFILE_H_

//Declaration of the functions
int open_file(char *filename);
void close_file();
int read_int(char x[], int option, int* var);
int read_string(char x[], int option, char y[]);

#endif