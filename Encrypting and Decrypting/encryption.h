#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string> 
using namespace std;


char en(char c, int key);
char de(char c, int key);

char en(char c, int key){
    int idx;
    if (c> 96 && c<123){
    idx = (((c-97)+key)% 26)+97;
    }
    
    else if(c> 64 && c<91){
    idx = (((c-65)+key)% 26)+65;
    }
    
    else{
        return c;
    }
    
    return (char) idx;
}

char de(char c, int key){
    int idx;
    if (c> 96 && c<123){
    idx = (((c-97)-key+26)% 26)+97;
    }
    
    else if(c> 64 && c<91){
    idx = (((c-65)-key+26)% 26)+65;
    }
    
    else{
        return c;
    }
    return (char) idx;
}


#endif
