#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//This program was  made for linux and will not work on windows
int main(){
    if (getuid()){
        printf("! The program is not running as root !\n");
        return 1;
    }

    char adaptor[26];
    char mac[18];

    //Data insertion
    printf("Insert the mac address to set to : ");
    gets(mac);
    printf("Insert the name of the internet adaptor : ");
    gets(adaptor);

    //Checking if the mac address is a valid one
    if(mac[2] != ':'){
        printf("The mac address is not valid");
        return 2;
    }
    //int counter to keep easy track of the command length
    int temp = 16;
    char command[101] = "ip link set dev ";
    for (int i = 0; i < strlen(adaptor); i++)
    {
        command[temp] = adaptor[i];
        temp++;
    }
    command[temp] = ' ';
    command[temp + 1] = 'd';
    command[temp + 2] = 'o';
    command[temp + 3] = 'w';
    command[temp + 4] = 'n';

    printf("%s", command);
    //system(command);

}