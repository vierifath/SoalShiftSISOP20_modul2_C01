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

* Source code file.sh
```
#!/bin/bash
mkdir "$(date)"        
```

* Bukti Output
![kjwadaghk](https://user-images.githubusercontent.com/61290164/76613885-9385d780-6551-11ea-9cf4-87a82ea9d42b.PNG)





2. Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program.
a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].
b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss].
c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).
d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.
e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi. Buatlah program dalam mimpi Kiwa jadi nyata!
Catatan:
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal
Hint:
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran tertentu
- Epoch Unix bisa didapatkan dari time()


``` MAAF MAS MASIH BELUM SELESAI. MASIH KURANG MEMAHAMI MATERI ```

3. Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing).
a. Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.
c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.
d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat program tersebut.
Catatan :
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk


```MAAF MAS MASIH BELUM SELESAI. MASIH KURANG MEMAHAMI MATERI```

     
        
        
        
        

