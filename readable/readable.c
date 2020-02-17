#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

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
    bool executable_flag = 1;
    int readable_files = 0;
    DIR* dirp = NULL;

    if(input_path == NULL){
        input_path = get_current_dir_name();
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
    executable_flag = access(input_path, X_OK);
    if(executable_flag < 0){
        fprintf (stderr, "%s: Can't access execute directory named %s --%s --errno=%d\n"
                 ,"readable" , input_path, strerror(errno), errno);
        return(readable_files);
    }else{
        dirp = opendir(input_path);
        if(dirp == NULL){
            fprintf (stderr, "%s: Can't open directory named %s --%s --errno=%d\n"
                     ,"readable" , input_path, strerror(errno), errno);
            return(readable_files);
        }
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

    

    return(1);
}