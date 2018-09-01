#include <stdio.h>
#include <stdlib.h>
#include <openssl/rc4.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "standalonerc42.h"
//#include <rc4_skey.c>
//#include <rc4_enc.c>
//Note to self: its bad practice to #include a source file :(
//#include <rc4_locl.h>

#define H_KEY "yufytugjhbgytcrtxc"

int encryp(int fd, int fd2){

RC4_KEY key;
off_t filesize; //will hold the size of the file
filesize = lseek(fd,0,SEEK_END); //records the size of file in bytes

if(filesize < 0){ //checks for error
perror("Cannot provide offset");
exit(0);
}

lseek(fd,0,SEEK_SET);// set byte counter back to first byte

unsigned char *inbuff = (unsigned char*)malloc(filesize); //input buffer
unsigned char *outbuff = (unsigned char*)malloc(filesize); //output buffer

if(read(fd,inbuff,filesize) == -1){ //checks if file is readable
    perror("cannot read file");
    exit(0);
}
//encryption / decryption
RC4_set_key(&key,sizeof(H_KEY),(const unsigned char *)H_KEY);
RC4(&key,filesize,inbuff,outbuff);


//write encryption to new file
lseek(fd,0,SEEK_SET);// set byte counter back to first byte

if(write(fd2,outbuff,filesize) == -1){

    perror("cannot write to file");
    exit(0);
}
free(inbuff);
free(outbuff); //free memory that was allocated for outbuff
return 0;
};


int main(int argc, char* argv[]){
    int input;
    int output;

//check for the number of arguments

if(argc != 3) //8
{
    perror("Incorrect number of arguments!");
  //  exit(0);
}

//open both files
input = open(argv[1],O_RDONLY,0644);
if(input == -1){

    perror("error opening the input file");
}
output = open(argv[2],O_WRONLY|O_APPEND|O_CREAT,0644);
if(output == -1){

    perror("error opening the output file");
}
//pass both files to encryption file

encryp(input,output);

//close both files
close(input);
close(output);

return 0;
};
