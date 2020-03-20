#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <wait.h>


void killer(char array[]);

int main(int argc, char** argv){
    
    pid_t pid, sid;
    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    killer(argv[1]);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    time_t now;
    struct tm* info;

    while (1) 
  {
    now = time(NULL);
    info = localtime(&now);

    char dirname[100];
    strftime(dirname, 100, "%Y-%m-%d_%H:%M:%S", info);

    pid_t c;
    c = fork();

    int status;

    if (c < 0) 
      exit(EXIT_FAILURE);

    if (c == 0)
    { 
      if (fork() == 0)
      {
        char *argv[] = {"mkdir", "-p", dirname, NULL};
        execv("/bin/mkdir", argv);
      }
      else 
      {
        while ((wait(&status)) > 0);
        for (int i = 0; i < 20; i++)
        {
          if (fork() == 0)
          {
            chdir(dirname);
            time_t now1;
            struct tm* info1;
        
            now1 = time(NULL);
            info1 = localtime(&now1);
        
            int t = (int)time(NULL);
            t = (t % 1000) + 100;
            
            char web[100];
            sprintf(web, "https://picsum.photos/%d", t);

            char name[100];
            strftime(name, 100, "%Y-%m-%d_%H:%M:%S", info1);
            char *argv[] = {"wget", web, "-qO", name, NULL};
            execv("/usr/bin/wget", argv);
          }
          sleep(5);
        }
        char zipname[150];
        sprintf(zipname, "%s.zip", dirname);
        char *argv[] = {"zip", "-qrm", zipname, dirname, NULL};
        execv("/usr/bin/zip", argv);
      }
    }
    else
      sleep(30);
  }
}

void killer(char array[])
{
  FILE *target;
  target = fopen("killer.sh", "w");
  int status;

  if (strcmp(array, "-a") == 0)
    fprintf(target, "#!/bin/bash\nkill -9 -%d", getpid());

  if (strcmp(array, "-b") == 0)
    fprintf(target, "#!/bin/bash\nkill %d", getpid());
  
  if(fork() == 0)
  {  
    if (fork() == 0)
    {
      char *argv[] = {"chmod", "u+x", "killer.sh", NULL};
      execv("/bin/chmod", argv);
    }
    else
    {
      while ((wait(&status)) > 0);    

      char *argv[] = {"mv", "killer.sh", "killer", NULL};
      execv("/bin/mv", argv);
    }
  }
    
  fclose(target);
}
