#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This program was  made for linux and will not work on windows
int main(){
    if (getuid()){
        printf("\x1b[31m! The program is not running as root !\n!! The program is terminated !!\n");
        return 1;
    }

    char adaptor[26];
    char mac[18];

    //Data insertion
    printf("Insert the mac address to set to : ");
    gets(mac);
    //Checking if the mac address is a valid one
    if(mac[2] != ':' || mac[5] != ':' || mac[8] != ':' || mac[11] != ':' || mac[14] != ':'){
        printf("\x1b[31mThe mac address is not valid \nThe program is terminated\n");
        return 2;
    }

    printf("Insert the name of the internet adaptor : ");
    gets(adaptor);

    //adding the name of the adaptor to the command string, which will get used later
    int temp = 16;
    char command[101] = "ip link set dev ";
    for (int i = 0; i < strlen(adaptor); i++)
    {
        command[temp] = adaptor[i];
        temp++;
    }
    command[temp] = ' ';
    temp++;

    //The adaptor gets put down
    command[temp] = 'd';
    command[temp + 1] = 'o';
    command[temp + 2] = 'w';
    command[temp + 3] = 'n';
    command[temp + 4] = '\0';

    printf("The adaptor is being put down\n");
    system(command);
    printf("The adaptor is down\n");

    //The adpator mac gets changed 
    command[temp] = 'a';
    command[temp + 1] = 'd';
    command[temp + 2] = 'd';
    command[temp + 3] = 'r';
    command[temp + 4] = 'e';
    command[temp + 5] = 's';
    command[temp + 6] = 's';
    command[temp + 7] = ' ';
    for (int i = 0; i < 18; i++)
        command[(temp + 7) + (i + 1)] = mac[i];

    printf("The mac address is being changed\n");
    system(command);
    printf("The mac address is changed\n");
    
    //The adaptor gets put back up
    command[temp] = 'u';
    command[temp + 1] = 'p';
    command[temp + 2] = '\0';

    printf("The network is coming back up\n");
    system(command);
    printf("The network is back up\n");

    return 0;
}
