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
https://github.com/vierifath/SoalShiftSISOP20_modul2_C01/blob/master/soal1/soal1.c

## PEMBAHASAN
A. Menginisialiasasi main() dengan 2 argumen, yang pertama yaitu argc (Argument Count) dan *argv[] (Argument Vector). Argumen pertama adalah jumlah argumen baris perintah dan yang kedua adalah daftar argumen baris perintah.
```
int main(int argc, char *argv[]) {
```

B. Menginisialisasi program menerima 4 argumen yaitu detik, menit, jam, (Pembahasan No. 1A)
   
   ```
   int second = 0 , minute = 0 , hour = 0;
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
  ```


C. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai (Pembahasan No.1B)
```
  if(argc < 5 || argc > 5){
        printf("Argumen yang Anda masukkan tidak sesuai\n");
        return 0;
    }
```


D. Program hanya menerima 1 config cron (Pembahasan No. 1C)
```   
   if(strcmp(argv[1], savetime) == 0 && second == 0)
      second = 1;
    if(strcmp(argv[2], savetime) == 0 && minute == 0)
      minute = 1;
    if(strcmp(argv[3], savetime) == 0 && (i < 24 || i == 60) && hour == 0){
      hour = 1;
    }
```



E. DAEMON ( Pembahasan No. 1D)
Daemon adalah suatu program yang berjalan di background secara terus menerus tanpa adanya interaksi secara langsung dengan user yang sedang aktif. Kode dibawah merupakan hasil gabungan dari langkah- langkah pembuatan daemon, yang mana kode ini template fungsi Daemon :
```
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
```




F. CURRENT TIME
Untuk mendapatkan waktu lokal file, kita menggunakan fungsi time() dan fungsi localtime() yang terdapat di library <time.h>

```
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
```


G. Jika kondisi didalam if bernilai true, maka menjalankan fungsi fork()

```
      if ((strcmp(argv[1], "*") == 0 || strcmp(argv[1], arrsec) == 0) && (strcmp(argv[2], "*") == 0 || strcmp(argv[2], arrmin) == 0) &&(strcmp(argv[3], "*") == 0 || strcmp(argv[3], arrhour) == 0)) {
          pid_t child_id = fork();
```


H. Setelah dilakukan fork(), child akan menjalankan bash
```
if (child_id == 0){
          char *argv2[] = {"bash",argv[4], NULL};
          execv("/bin/bash", argv2);
        }
```

I. ```sleep (1)``` digunakan untuk mengatur agar fungsi while berjalan setiap satu detik.

**Source Code file.sh
```
#!/bin/bash

date >> /home/vierifath/SOALMODUL2/date.txt
```

**Output
![3](https://user-images.githubusercontent.com/61290164/77190074-29e66a00-6b0b-11ea-92a2-b8f02a4d800c.PNG)


Setelah program dijalankan, maka akan membuat file date.txt yang berisi
![4](https://user-images.githubusercontent.com/61290164/77190079-2bb02d80-6b0b-11ea-8136-642c47ad764b.PNG)


### NO 2
2. Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program.
a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].

b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.

e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi. Buatlah program dalam mimpi Kiwa jadi nyata!

## PEMBAHASAN


a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].


**CURRENT TIME
Untuk mendapatkan waktu lokal file, kita menggunakan fungsi time() dan fungsi localtime() yang terdapat di library <time.h>
```
    now = time(NULL);
   
   info = localtime(&now);
```

Untuk membuat sebuah folder khusus dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].

```
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
```

** Membuat sebuah program C yang per 30 detik 

```
else
      sleep(30);
```


b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss].

Jadi, kode dibawah ini melakukan download dari https://picsum.photos/. Hasil download nya akan di simpan di setiap folder yang telah dibuat. Pertama kita membuat perulangan ```for (int i = 0; i < 20; i++)``` tujuannya, kita dapat mengisi tiap-tiap folder dengan 20 gambar. ```chdir(dirname);``` digunakan agar hasil download yang akan dilakukan masuk ke directory. ```execv("/usr/bin/wget", argv);``` eksekusi menggunakan execv.
```
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
```



c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).

```  execv("/usr/bin/zip", argv);``` -> digunakan execv untuk melakukan archive zip
```
 char zipname[150];
        sprintf(zipname, "%s.zip", dirname);
        char *argv[] = {"zip", "-qrm", zipname, dirname, NULL};
        execv("/usr/bin/zip", argv);
```

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.

e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete).

```
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
```
### NO 3

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

## PEMBAHASAN

a. Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu lima detik kemudian membuat direktori yang kedua bernama “sedaap”.

Pertama kira memberi kondisi dimana program akan gagal untuk berjalan dengan menggunakan fungsi exit(EXIT_FAILURE);
Kemudian kira membuat directori bernama indomie dan sedaap yang diletakkan di lokasi /home/vierifath/SOALMODUL2
```
 if (child == 0){
        pid_t child_mi = fork();
        
        if (child_mi < 0){
            exit(EXIT_FAILURE);
        }
        
        if (child_mi == 0){
            char *argv[] = {"mkdir", "-p", "/home/vierifath/SOALMODUL2/indomie", NULL};
            execv("/bin/mkdir", argv);
        }else{
            while ((wait(&status)) > 0);
            sleep(5); //program dengan interval waktu 5 detik
            char *argv[] = {"mkdir", "-p", "/home/vierifath/SOALMODUL2/sedaap", NULL};
            execv("/bin/mkdir", argv);
        }
```

![Capture](https://user-images.githubusercontent.com/61290164/77201864-d9c5d280-6b1f-11ea-92c1-250b0a43ec88.PNG)


b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.
Jadi kita mengekstrak file jpg.zip menggunakan fungsi execv ```execv("/usr/bin/unzip", argv);``` 

```
        if (child_unzip == 0){
            char* argv[] = {"unzip", "/home/vierifath/SOALMODUL2/jpg.zip", NULL};
            execv("/usr/bin/unzip", argv);
        }
```       

![Capture](https://user-images.githubusercontent.com/61290164/77201864-d9c5d280-6b1f-11ea-92c1-250b0a43ec88.PNG)


c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.

Fungsi chdir untuk mengubah direktori ke jpg, membuat pointer DIR, fungsi opendir untuk membuka direktori handle, fungsi struct untuk membuat status di tiap proses, if(directory) mengecek directory, fungsi while untuk membuat perulangan sampai nilainya NULL, membuat fork lagi untuk membuat program, dir->d_name untuk membuat variabel untuk mengambil nama direktori, EXIT_FAILURE untuk fungsi program berhenti jika program gagal jalan
```
while ((wait(&status)) > 0);
            chdir("/home/vierifath/SOALMODUL2/jpg/");
            DIR *directory;
            directory = opendir(".");
            struct dirent *dir;
            if(directory){
                while((dir = readdir(directory)) != NULL){
                    pid_t child_team = fork();
                    struct stat st;
                    stat(dir->d_name, &st);
                    
                    if(child_team < 0){
                        exit(EXIT_FAILURE);
                    }
            
                    if(child_team == 0){
                        char path_file[1000];
                        sprintf(path_file, "/home/vierifath/SOALMODUL2/jpg/%s", dir->d_name);
                    
                        if(S_ISDIR(st.st_mode)){
                            if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0);
                    
                            else{
                                pid_t child_txt = fork();
                                
                                if(child_txt < 0){
                                    exit(EXIT_FAILURE);
                                }
                                
                                if(child_txt == 0){
                                    char* argv[] = {"mv", path_file, "/home/vierifath/SOALMODUL2/indomie/", NULL};
                                    execv("/bin/mv", argv);
                                }
```


![2](https://user-images.githubusercontent.com/61290164/77201866-da5e6900-6b1f-11ea-982b-63581da8b031.PNG)

![3](https://user-images.githubusercontent.com/61290164/77201856-d6cae200-6b1f-11ea-9dae-0a0293e8eaf9.PNG)


d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).


```
while((dir = readdir(directory)) != NULL){
                                        pid_t child_indomie = fork();
                                        int kasus;
                                
                                        if(child_indomie == 0){
                                            char target_file[1000];
                                            FILE *target;
                                            sprintf(target_file, "/home/vierifath/SOALMODUL2/indomie/%s/coba1.txt", dir->d_name);
                                            target = fopen(target_file,"w");
                                            fclose(target); 
                                        }else{
                                            while((wait(&kasus)) > 0); 
                                            sleep(3);
                                            char target_file[1000];
                                            FILE *target;
                                            sprintf(target_file, "/home/vierifath/SOALMODUL2/indomie/%s/coba2.txt", dir->d_name);
                                            target = fopen(target_file,"w");
                                            fclose(target);
                                            exit(0);
```
Jadi kita melakukan pengecekan direktori (dir = readdir(directory)) != NULL, membuat program baru dan kasus untuk melanjutkan programnya, membuat string untuk print dengan fungsi sprintf, membuat pointer FILE untuk mengarahkan direktorinya, fungsi fopen untuk membuat file dan fungsi w untuk wrie-only yang hanya bisa membuat file jika belum ada, fclose untuk menutup fopen tadi, disini kita membuat 2 file yaitu coba1.txt dan menggunakan fungsi sleep(3) untuk membuat file selanjutnya coba2,txt, exit(0) untuk menutup program, dan fungsi closedir untuk menutup semua direktori.

![4](https://user-images.githubusercontent.com/61290164/77201862-d894a580-6b1f-11ea-9ac9-abdaef2c3317.PNG)
![5](https://user-images.githubusercontent.com/61290164/77201863-d92d3c00-6b1f-11ea-8d7f-3d725178e301.PNG)
