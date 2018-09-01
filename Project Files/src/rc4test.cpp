#include <iostream>
#include <openssl/rc4.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "rc4test.h"

using namespace std;

#define H_KEY "yufytugjhbgytcrtxc"
int encryp(int fd){

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

if(write(fd,outbuff,filesize) == -1){

    perror("cannot write to file");
    exit(0);
}
free(inbuff);
free(outbuff); //free memory that was allocated for outbuff
return 0;
};

