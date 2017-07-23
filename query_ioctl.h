#ifndef QUERY_IOCTL_H
#define QUERY_IOCTL_H
#include <linux/ioctl.h>
 
typedef struct
{
    char pass[50];
} input;
 
#define QUERY_GET_VARIABLES _IOR('q', 1, input *)
#define QUERY_CLR_VARIABLES _IO('q', 2)
#define QUERY_SET_VARIABLES _IOW('q', 3, input *)
 
#endif
