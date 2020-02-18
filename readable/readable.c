#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <dirent.h>

void deleteBuffers(int length, char **buffers){
    int i = 0;
    while(i < length){
        free(buffers[i]);
        i++;
    }
    return;
}



int readable(char *input_path){
    int length_of_buffer_array = 0;
    char **buffer_array = calloc(10, sizeof(char**));
    int access_return = 1;
    int readable_files = 0;
    DIR *dirp = malloc(sizeof(DIR*));
    struct dirent *my_dirent = NULL;
    errno = 0;
    char *file_path = NULL;
    char *new_file_path = NULL;

    if(input_path == NULL){
        input_path = malloc(PATH_MAX);
        if(input_path == NULL){
            fprintf (stderr, "%s: Can't allocate memory --%s --errno=%d\n"
                     ,"readable" , strerror(errno), errno);
            return(-1);
        }
        input_path = getcwd(input_path, PATH_MAX);
        if(input_path == NULL){
            fprintf (stderr, "%s: Can't access PWD variable for path --%s --errno=%d\n"
                     ,"readable" , strerror(errno), errno);
            return(-1);
        }
        buffer_array[length_of_buffer_array++] = input_path;
    }

    //try to open the given directory name
    //if you can open it
        //save the fd
    //else if you cant open it 
        //return number of readable files.
    printf("input_path is %s\n", input_path);

    access_return = access(input_path, X_OK);
    if(access_return < 0){
        fprintf (stderr, "%s: Can't access directory named %s --%s --errno=%d\n"
                 ,"readable" , input_path, strerror(errno), errno);
        deleteBuffers(length_of_buffer_array, buffer_array);
        free(buffer_array);
        return(readable_files);
    }else{
        dirp = opendir(input_path);
        if(dirp == NULL){
            fprintf (stderr, "%s: Can't open directory named %s --%s --errno=%d\n"
                     ,"readable" , input_path, strerror(errno), errno);
            deleteBuffers(length_of_buffer_array, buffer_array);
            free(buffer_array);
            return(readable_files);
        }
    }

    while(my_dirent = readdir(dirp), my_dirent != NULL){
        //check get the access permissions on the current file.
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
        free(buffer_array);
        closedir(dirp);
        return(readable_files);
    }
    //iterate over the fd pointer
        //if a file is regular
            //if it is readable
                //increment readable counter
        //else if the files is a dir
            //recursively call the function on directory
        //else if file is symbolic link
            //ignore it
        //else if EOF is reached
            //return readable counter.

    deleteBuffers(length_of_buffer_array, buffer_array);
    free(buffer_array);
    closedir(dirp);
    return(readable_files);
}