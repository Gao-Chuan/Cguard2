#include <stdio.h>
char *channel = "amazonMQTT";

int editx(char * s){
    printf("%s", s);
    return 0;
}

int main(){
    char *s = "hello";
    editx(s);
    return 0;
}