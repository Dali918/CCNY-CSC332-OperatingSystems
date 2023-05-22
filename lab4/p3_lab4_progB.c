#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 100
#define MESSAGE_TYPE 1

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

    // Generate the same key used by progA
    key = ftok("./p3_lab4_progA.c", 'A');
    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    // Connect to the existing message queue
    msgid = msgget(key, 0666);
    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    // Send and receive messages
    while (1)
    {
        // Receive message from progA
        msgrcv(msgid, &msg, sizeof(msg.mtext), MESSAGE_TYPE, 0);
        printf("From ProgA: %s", msg.mtext);

        // Send message from progB to progA
        printf("ProgB: ");
        fgets(msg.mtext, MAX_MESSAGE_SIZE, stdin);
        msg.mtype = MESSAGE_TYPE;
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
    }

    return 0;
}
