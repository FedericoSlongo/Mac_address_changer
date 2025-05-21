#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This program was  made for linux and will not work on windows
int main(){
    if (getuid()){
        printf("\x1b[31m! The program is not running as root !\n");
        return 1;
    }
    //The error variable keeps track of an eventual error code
    int error = 0;
    //The name of the network adaptor
    char adaptor[26];
    //The mac address
    char mac[18];
    //Saves the position for string text adding in the command
    int commandStringPos = 0;

    set_mac:
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
    char command[101] = "ip link set dev ";
    commandStringPos = strlen(command);
    for (int i = 0; i < strlen(adaptor); i++)
    {
        command[commandStringPos] = adaptor[i];
        commandStringPos++;
    }
    command[commandStringPos] = ' ';
    commandStringPos++;

    //The adaptor gets put down
    command[commandStringPos] = 'd';
    command[commandStringPos + 1] = 'o';
    command[commandStringPos + 2] = 'w';
    command[commandStringPos + 3] = 'n';
    command[commandStringPos + 4] = '\0';

    printf("The adaptor is being put down\n");
    error = system(command);
    if(error != 0){
        printf("The adaptor isn't down and the exit code is %d", error);
        return 3;
    }
    printf("The adaptor is down\n");

    //The adpator mac gets changed 
    command[commandStringPos] = 'a';
    command[commandStringPos + 1] = 'd';
    command[commandStringPos + 2] = 'd';
    command[commandStringPos + 3] = 'r';
    command[commandStringPos + 4] = 'e';
    command[commandStringPos + 5] = 's';
    command[commandStringPos + 6] = 's';
    command[commandStringPos + 7] = ' ';
    for (int i = 0; i < 18; i++)
        command[(commandStringPos + 7) + (i + 1)] = mac[i];

    printf("The mac address is being changed\n");
    error = system(command);
    if(error != 0){
        printf("The mac isn't changed and the exit code is %d", error);
        return 4;
    }
    printf("The mac address is changed\n");
    
    //The adaptor gets put back up
    command[commandStringPos] = 'u';
    command[commandStringPos + 1] = 'p';
    command[commandStringPos + 2] = '\0';

    printf("The network is coming back up\n");
    system(command);
    if(error != 0){
        printf("The adaptor isn't up and the exit code is %d", error);
        return 5;
    }
    printf("The network is back up\n");

    return 0;
} 
