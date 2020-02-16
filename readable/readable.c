#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

void deleteBuffers(int length, char **buffers){
    int i = 0;
    while(i < length){
        free(buffers[i]);
        i++;
    }
    return;
}

int readable(char *inputPath){
    int length_of_buffer_array = 0;
    char **buffer_array = calloc(10, sizeof(char**));

    if(inputPath == NULL){
        inputPath = get_current_directory_name();
        if(inputPath == NULL){
            fprintf (stderr, "%s: Can't access PWD variable for path --%s --errno=%d\n"
                     ,"readable" , strerror(errno), errno);
            return(-1);
        }
        buffer_array[length_of_buffer_array++] = inputPath;
    }

    //create base case for recursive call.


    return(1);
}