#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <dirent.h>
#include <sys/stat.h>

int readable(char *inputPath);
void deleteBuffers(int length, void **buffers);
void closeAndFreeDirp(DIR *dirp);

void deleteBuffers(int length, void **buffers){
    int i = 0;
    while(i < length){
        free(buffers[i]);
        i++;
    }

    free(buffers);
    return;
}

void closeAndFreeDirp(DIR *dirp){
    int out = 0;

    out = closedir(dirp);
    if(out < 0){
        fprintf (stderr, "%s: Can't close dirp --%s --errno=%d\n"
                 ,"readable" , strerror(errno), errno);
    }

    return;
}

int readable(char *input_path){
    int length_of_buffer_array = 0;
    void **buffer_array = calloc(10, sizeof(void**));
    int access_return = 1;
    int stat_return = 0;
    int readable_files = 0;
    DIR *dirp = NULL;
    struct dirent *my_dirent = NULL;
    errno = 0;
    char *file_path = NULL;
    char *new_file_path = NULL;
    struct stat* stat_buf = malloc(sizeof(struct stat));
    buffer_array[length_of_buffer_array++] = stat_buf;

    if(input_path == NULL){
        input_path = malloc(PATH_MAX);
        if(input_path == NULL){
            fprintf (stderr, "%s: Can't allocate memory --%s --errno=%d\n"
                     ,"readable" , strerror(errno), errno);
            deleteBuffers(length_of_buffer_array, buffer_array);
            closeAndFreeDirp(dirp);
            return(-1);
        }
        input_path = getcwd(input_path, PATH_MAX);
        if(input_path == NULL){
            fprintf (stderr, "%s: Can't access PWD variable for path --%s --errno=%d\n"
                     ,"readable" , strerror(errno), errno);
            deleteBuffers(length_of_buffer_array, buffer_array);
            closeAndFreeDirp(dirp);
            return(-1);
        }
        buffer_array[length_of_buffer_array++] = input_path;
    }

    printf("input_path is %s\n", input_path);

    stat_return = stat(input_path, stat_buf);
    if(stat_return < 0){
        fprintf (stderr, "%s: Can't get status of file with path %s --%s --errno=%d\n"
                 ,"readable" , input_path, strerror(errno), errno);
        deleteBuffers(length_of_buffer_array, buffer_array);
        return(readable_files);
    }

    access_return = access(input_path, R_OK);
    if(access_return < 0){
        fprintf (stderr, "%s: Can't access file with path %s --%s --errno=%d\n"
                 ,"readable" , input_path, strerror(errno), errno);
        deleteBuffers(length_of_buffer_array, buffer_array);
        return(readable_files);
    }

    if(S_ISREG(stat_buf->st_mode) 
       && access_return == 0){
        
        deleteBuffers(length_of_buffer_array, buffer_array);
        readable_files++;
        return(readable_files); 
    }else if(access_return = access(input_path, X_OK), access_return < 0){
        fprintf (stderr, "%s: Can't access directory named %s --%s --errno=%d\n"
                 ,"readable" , input_path, strerror(errno), errno);
        deleteBuffers(length_of_buffer_array, buffer_array);
        return(readable_files);
    }else{
        dirp = opendir(input_path);
        if(dirp == NULL){
            fprintf (stderr, "%s: Can't open directory named %s --%s --errno=%d\n"
                     ,"readable" , input_path, strerror(errno), errno);
            deleteBuffers(length_of_buffer_array, buffer_array);
            closeAndFreeDirp(dirp);
            return(readable_files);
        }
    }

    while(my_dirent = readdir(dirp), my_dirent != NULL){
        printf("my_dirent->d_name is %s\n", my_dirent->d_name);
        new_file_path = malloc(PATH_MAX);

        file_path = malloc(PATH_MAX);
        strcpy(file_path, input_path);
        strcat(file_path, "/");
        strcat(file_path, my_dirent->d_name);
        access_return = access(file_path, R_OK);

        if(my_dirent->d_type == DT_REG && access_return == 0){
            readable_files++;
        }else if(my_dirent->d_type == DT_DIR 
                 && strcmp(my_dirent->d_name, "..") != 0
                 && strcmp(my_dirent->d_name, ".") != 0){
            
            strcpy(new_file_path, file_path);
            readable_files = readable_files + readable(new_file_path);
        }

        free(file_path);
        free(new_file_path);
        file_path = NULL;
    }

    //check if readdir errored
    if(errno != 0){
        fprintf (stderr, "%s: Can't read dirp --%s --errno=%d\n"
                 ,"readable", strerror(errno), errno);

        deleteBuffers(length_of_buffer_array, buffer_array);
        closeAndFreeDirp(dirp);
        return(readable_files);
    }

    deleteBuffers(length_of_buffer_array, buffer_array);
    closeAndFreeDirp(dirp);
    return(readable_files);
}