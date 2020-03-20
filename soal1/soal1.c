#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[]) {
        int second = 0 , minute = 0 , hour = 0;
        int newsecond, newminute, newhour;

  char savetime[5]="*";
  if(argc < 5 || argc > 5){
        printf("Argumen yang Anda masukkan tidak sesuai\n");
        return 0;
    }

  for(int i = 60 ; i >= 0 ; --i ){
    if(strcmp(argv[1], savetime) == 0 && second == 0)
      second = 1;

    if(strcmp(argv[2], savetime) == 0 && minute == 0)
      minute = 1;
if(strcmp(argv[3], savetime) == 0 && (i < 24 || i == 60) && hour == 0){
      hour = 1;
    }
    sprintf( savetime, "%d", i );
  }
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);
  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  while (1) {
      // pid_t child_id;
        time_t rawtime;
        struct tm * timeinfo;

      time ( &rawtime );
      timeinfo = localtime ( &rawtime );


      char arrsec[10], arrmin[10],arrhour[10];
        newsecond = timeinfo->tm_sec;
        newminute = timeinfo->tm_min;
        newhour   = timeinfo->tm_hour;
        sprintf( arrsec, "%d", newsecond );
        sprintf( arrmin, "%d", newminute );
        sprintf( arrhour, "%d", newhour );

        if (second == 0 || minute == 0|| hour == 0) 
          exit(EXIT_FAILURE); 
        if ((strcmp(argv[1], "*") == 0 || strcmp(argv[1], arrsec) == 0) && (strcmp(argv[2], "*") == 0 || strcmp(argv[2], arrmin) == 0) &&(strcmp(argv[3], "*") == 0 || strcmp(argv[3], arrhour) == 0)) {
          pid_t child_id = fork();
        if (child_id < 0 || second == 0 || minute == 0|| hour == 0){
          exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
        }
        if (child_id == 0){
          char *argv2[] = {"bash",argv[4], NULL};
          execv("/bin/bash", argv2);
        }
        }
        sleep(1);
        }
}
