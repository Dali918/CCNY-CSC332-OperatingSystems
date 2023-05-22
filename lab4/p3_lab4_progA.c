#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 100 // define the max message size
#define MESSAGE_TYPE 1        //define the message type 

struct message
{
    long mtype;
    char mtext[MAX_MESSAGE_SIZE];
};

int main()
{
    struct message msg;
    key_t key;
    int msgid;

    // Generate a unique key for the message queue
    key = ftok("./p3_lab4_progA.c", 'A');
    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    // Create the message queue
    msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    // Send and receive messages
    while (1)
    {
        // Send message from progA to progB
        printf("Proga: ");
        fgets(msg.mtext, MAX_MESSAGE_SIZE, stdin);
        msg.mtype = MESSAGE_TYPE;
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

        // Receive message from progB
        msgrcv(msgid, &msg, sizeof(msg.mtext), MESSAGE_TYPE, 0);
        printf("From ProgB: %s", msg.mtext);
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        return 1;
    }

    return 0;
}
