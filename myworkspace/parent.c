// parent.c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{        
    int fd = open("test.txt",O_RDWR|O_APPEND);

    if (fd == -1)
    {       
        printf("The file test.txt open failed ! The fd = %d\n",fd);
        execl( "/bin/touch", "touch", "test.txt", (char*)NULL );
        return 0;
    }
    else
    {       
        printf("The file test.txt open success ! The fd = %d\n", fd);
    }

    printf("fork!\n");

// 和 fcntl(fd, F_SETFD, 1) 等效，但这是标准写法，即用 FD_CLOEXEC 取代直接写1
int tFlags = fcntl(fd, F_GETFD);
fcntl(fd, F_SETFD, tFlags | FD_CLOEXEC );

    // 什么也不写，相当于系统默认 fcntl(fd, F_SETFD, 0) ，即用 execl 执行子进程时，
    // 不打开“执行时关闭”标识位 FD_CLOEXEC，此时子进程可以向 test.txt 写入字符串
char *s="The Parent Process Writed !\n";

    pid_t pid = fork();
    if(pid == 0)                                        /* Child Process */
    {       
        printf("***** exec child *****\n");
        execl("child", "./child", &fd, NULL);
        printf("**********************\n");
    }

    // 等待子进程执行完毕
    wait(NULL);
    ssize_t writebytes = write(fd,s,strlen(s));
    if ( writebytes == -1 )
    {
         printf("The Parent Process Write To fd : %d Failed !\n", fd);
    }

    close(fd);
    return 0;
}
