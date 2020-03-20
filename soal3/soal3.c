#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(){
    pid_t child = fork();
    int status;  
    if (child < 0){
        exit(EXIT_FAILURE);
    }
    
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
    
    }else{
        while ((wait(&status)) > 0);
        pid_t child_unzip = fork();
        
        if (child_unzip < 0){
            exit(EXIT_FAILURE);
        }

        if (child_unzip == 0){
            char* argv[] = {"unzip", "/home/vierifath/SOALMODUL2/jpg.zip", NULL};
            execv("/usr/bin/unzip", argv);
        }else{
            
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
                                }else{
                                    
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
                                        }
                                    }
                                }
                            }
                        }else{
                            char* argv[] = {"mv", path_file, "/home/vierifath/SOALMODUL2/sedaap/", NULL};
                            execv("/bin/mv", argv);
                        }
                    }
                }
                closedir(directory);
            }
        }
    }
}
