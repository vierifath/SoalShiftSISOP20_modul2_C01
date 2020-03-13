# SoalShiftSISOP20_modul2_C01

### KELOMPOK        : C1
ANGGOTA         :

* Vieri Fath Ayuba     (05111840000153)
* Himawan Wijaya       (05111640000133)


### Jawaban Soal Shift Modul 2
### NO 1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai
c. Program hanya menerima 1 config cron
d. Program berjalan di background (daemon)
e. Tidak boleh menggunakan fungsi system()
Contoh: ./program \* 34 7 /home/somi/test.sh


### SOURCE CODE
```
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

void  warning(){
        printf("Argumen yang Anda input tidak sesuai");
}
//fungsi checknum,
int checknum(char isi[]){
    if(strlen(isi) == 1)
        if(isi[0] == '*')
            return 1;
    else{
        for(int i = 0; i < strlen(isi); i+=1){
            if(isi[i] > '0' || isi[i] < '9')
return 2;
        }
    } 
}
//main
int main(int argc, char *argv[]){
        int hour;
        int minute;
        int second;
        char path[100];

        int newhour;
        int newminute;
        int newsecond;

        //no1b
        if(argc > 5 && argc < 5){  warning();
                return 0;
        }

        if((strcmp(argv[1], "*")) == 0) 
                second = 60;
        else if(checknum(argv[1]))
                second = atoi(argv[1]);
 else if(second <= 0 || second >= 60){
                warning();
                return 0;
        }
        else{
                warning();
                        return 0;
        }


        if((strcmp(argv[2], "*")) == 0) 
                minute = 60;
        else if(checknum(argv[2]))
                minute = atoi(argv[2]);

        else if(minute <= 0 || minute >= 60){
                warning();
                return 0;
        }

        else{
                warning();
                return 0;
        }
        if((strcmp(argv[3], "*")) == 0) 
                hour = 24;
         else if(checknum(argv[1]))
                hour = atoi(argv[1]);

         else if(hour <= 0 || hour >= 60){
                warning();
                return 0;
         }
         else{
                warning();
                return 0;
                }

        //path
        strncpy(path, argv[4], 99);
        path[100] = '\0';

        //daemon
        pid_t pid, sid;
        pid = fork();
        if (pid < 0)
                exit(EXIT_FAILURE);


        if (pid > 0)
        exit(EXIT_SUCCESS);

        umask(0);

        sid = setsid();
        if (sid < 0)
        exit(EXIT_FAILURE);

if ((chdir("/")) < 0)
        exit(EXIT_FAILURE);


        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        while(1){
        time_t raw = time(NULL);
        struct tm *timeinfo;
        timeinfo = localtime(&raw);
        
        newsecond = timeinfo->tm_sec;
        newminute = timeinfo->tm_min;
        newhour = timeinfo->tm_hour;

        if((newhour == hour || hour == 60) && (newminute == minute || minute == 60) && (newsecond == second || second == 60)){



        pid_t child;
        child = fork();

        int status;
        if(child == 0){
                char *script[] = {"bash", argv[4], NULL};
                execv("/bin/bash", script);
        }


        else
                while((wait(&status)) > 0);

        }       
        sleep(1);
        }
}        
```
        
     
        
        
        
        

