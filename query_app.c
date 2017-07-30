#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
 
#include "query_ioctl.h"
 
void get_vars(int fd)
{
    input q;
     
    if (ioctl(fd, QUERY_GET_VARIABLES, &q) == -1)
    {
        perror("query_apps ioctl get");
    }
    
    if (strlen(q.pass)==0)
    {
        printf("Password not set");
    }
    else{
	printf("Password set");
    }
}
void clr_vars(int fd)
{
    if (ioctl(fd, QUERY_CLR_VARIABLES) == -1)
    {
        perror("Error in query_ioctl clr");
    }
}
void set_vars(int fd)
{
    char pass[50];
    input q;
 
    printf("Enter Password: ");
    scanf("%s", pass);
    getchar();
    strcpy(q.pass,pass);
    
    if (ioctl(fd, QUERY_SET_VARIABLES, &q) == -1)
    {
        perror("Error in query_ioctl set");
    }
}
void ver_vars(int fd)
{
    char pass[50];
    input q;
    
    if(ioctl(fd, QUERY_GET_VARIABLES, &q)==-1)
    {
	perror("Error in query_ioctl get");
    }

    printf("Enter Password: ");
    scanf("%s", pass);
    getchar();
  
    if(strcmp(q.pass,pass)==0)
    {
	printf("Correct Password");
	pid_t c=fork();
	if(c==0)
	{
	   execv("insmod","usb_storage");
	}
    }
    else
    {
	printf("Wrong Password");
    }
    
}
 
int main(int argc, char *argv[])
{
    char *file_name = "/dev/query";
    int fd;
    enum
    {
        e_get,
        e_clr,
        e_set,
        e_ver
    } option;
 
    if (argc == 1)
    {
        option = e_get;
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-g") == 0)
        {
            option = e_get;
        }
        else if (strcmp(argv[1], "-c") == 0)
        {
            option = e_clr;
        }
        else if (strcmp(argv[1], "-s") == 0)
        {
            option = e_set;
        }
        else if (strcmp(argv[1], "-v") == 0)
        {
            option = e_ver;
        }
        else
        {
            fprintf(stderr, "Wrong input. Input should be  -g/-c/-s/-v\n", argv[0]);
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Wrong input. Input should be  -g/-c/-s/-v\n", argv[0]);
        return 1;
    }
    fd = open(file_name, O_RDWR);
    if (fd == -1)
    {
        perror("query_apps open");
        return 2;
    }
 
    switch (option)
    {
        case e_get:
            get_vars(fd);
            break;
        case e_clr:
            clr_vars(fd);
            break;
        case e_set:
            set_vars(fd);
            break;
        case e_ver:
            ver_vars(fd);
        default:
            break;
    }
 
    close (fd);
 
    return 0;
}
