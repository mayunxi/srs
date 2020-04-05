//child.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n",argc);
    
    if ( argv[1] == NULL )
    {
        printf("There is no Parameter !\n");
        return 0;
    }

    int fd = *argv[1];
    printf("child fd = %d\n",fd);
    
    char *s = "The Child Process Writed !\n";
    ssize_t writebytes = write(fd, (void *)s, strlen(s));
    if ( writebytes == -1 )
    {
        printf("The Child Process Write To fd : %d Failed !\n", fd);
    }
    
    close(fd);
    return 0;
}
