#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This program was  made for linux and will not work on windows
int main(){
    if (getuid()){
        printf("\x1b[31m! The program is not running as root !\n!! The program is terminated !!\n");
        return 1;
    }
    //The error variable keeps track of an eventual error code
    int error = 0;
    //The name of the network adaptor
    char adaptor[26];
    //The mac address
    char mac[18];
    //The coiche 
    char coiche[100];
    //Temporary varibale for the generation of the mac address
    int mac_temp;

    int temp;

    int decimal_Number;

    //Asking the user what to do
    printf("Do you want to create a [r]andom mac address or [s]et your own?\n");
    fflush(stdin);
    gets(coiche);
    fflush(stdin);
    
    if(coiche[0] == 's')
        goto set_mac;
    if(coiche[0] == 'r')
        goto random;
    
    random:

    mac_temp = rand() % (253);

    for(int i = 0; i > 4; i ++){
        goto hex_con;
        inside_of_for:
        mac_temp = rand() % (256);
    }

    hex_con:
    
    decimal_Number = mac_temp;
    int i = 1, j;
    
    while (decimal_Number != 0) {
        temp = decimal_Number % 16;
        
        if (temp < 10)
            temp = temp + 48;
        else
            temp = temp + 55;
        mac[i++] = temp;
        decimal_Number = decimal_Number / 16;
    }

    goto inside_of_for;





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
    temp = 16;
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
    error = system(command);
    if(error != 0){
        printf("The adaptor isn't down and the exit code is %d", error);
        return 3;
    }
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
    error = system(command);
    if(error != 0){
        printf("The mac isn't changed and the exit code is %d", error);
        return 4;
    }
    printf("The mac address is changed\n");
    
    //The adaptor gets put back up
    command[temp] = 'u';
    command[temp + 1] = 'p';
    command[temp + 2] = '\0';

    printf("The network is coming back up\n");
    system(command);
    if(error != 0){
        printf("The adaptor isn't up and the exit code is %d", error);
        return 5;
    }
    printf("The network is back up\n");

    return 0;
} 
