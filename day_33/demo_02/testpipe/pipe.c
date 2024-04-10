#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void writer(int wfd)
{
    const char *msg = "hello father";
    char buff[128];
    pid_t pid = getpid();
    int cnt = 0;
    while (1)
    {
        snprintf(buff, sizeof(buff), "sent message: %s:,pid: %d,cnt: %d\n", msg, pid, cnt);
        write(wfd, buff, strlen(buff));
        char c = 'A';
        cnt++;

        // write(wfd, &c, 1);
        // printf("%d\n",cnt);
        sleep(1);
        // if (cnt == 10)
        //     break;
    }
    close(wfd);
}

void reader(int rfd)
{
    char buff[1024];
    int cnt = 10;
    while (1)
    {
        sleep(1);
        ssize_t n = read(rfd, buff, sizeof(buff) - 1);
        if (n > 0)
        {
            buff[n] = '\0'; // Add null terminator after reading
            printf("get message: %s ,n: %ld\n", buff, n);
        }
        else if (n == 0)
        {
            printf("read file done!\n");
            break;
        }
        else
        {
            printf("read error!\n");
            break;
        }

        --cnt;
        if (cnt == 0)
            break;
    }
    close(rfd);
    printf("read endpoint done!\n");
}

int main()
{
    int pipefd[2];
    int ret = pipe(pipefd);
    if (ret == -1)
        return -1;

    printf("pipefd[0]:%d,pipefd[1]:%d\n", pipefd[0], pipefd[1]);

    pid_t id = fork();
    if (id == 0)
    {
        close(pipefd[0]);
        // w
        writer(pipefd[1]);
        exit(10);
    }
    // 父进程
    close(pipefd[1]);
    reader(pipefd[0]);

    // wait(NULL);
    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    if (rid == id)
    {
        printf("exit code:%d ,exit signal:%d\n", WEXITSTATUS(status), status & 0x7F);
    }
    return 0;
}
