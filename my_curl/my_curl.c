#include "my_curl.h"
#include <stdio.h>

int check(char* src, char* sub)
{
    int i = 0;
    while (sub[i] != '\0')
    {
        if (src[i] != sub[i])
        { 
            return 0;
        }
        i++;
    }
    return 1;
}

char* find_path_index_or_protocol(char* url, int flag)
{
    if (check(url, "https://"))
    {
        url += 8;
    }
    else if (check(url, "http://"))
    {
        url += 7;
    }
    int i = 0;
    while (url[i] != '\0')
    {
        if (flag == 0 && url[i] == '/')
        {
            return &url[i+1];
        }
        else if (flag == 1 && url[i] == '/'){
            url[i] = '\0';
            break;
        }
        i++;
    }
    if (flag == 0)
    {
        return "-1";
    }
    return url;
}

char* to_copy_url(char* url, int index, char* dest)
{
    int dest_index = 0;
    int i = index;
    while (url[i] != '\0')
    {
        dest[dest_index++] = url[i++];
    }
    return dest;
}

int fl;

#if __linux__ || __APPLE__
    int fl = 1;
#elif _WIN64
    DWORD timeout = SOCKET_TIMEOUT * 500;
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout,sizeof(timeout));
#endif

#define SOCKET_TIMEOUT 10 // set to 10 seconds (adjust as needed)

void check_system(int fl, int fd){
    if(fl == 1){
        struct timeval time_val;
        time_val.tv_sec = 1;
        time_val.tv_usec = 0;
        setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&time_val, sizeof(time_val));
    }else if(fl == 2) {
        int timeout = SOCKET_TIMEOUT * 500;
        setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
    }
}

int connector_to_name(char *local_name)
{
    struct total total;
    int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket failed");
        return -1;
    }
    if ((total.host = gethostbyname(local_name)) == NULL)
    {
        fprintf(stderr, "could not resolve host: %s\n", local_name);
        return -1;
    }
    total.address.sin_family = AF_INET;
    total.address.sin_addr = *((struct in_addr*)total.host->h_addr);
    int port = 80;
    total.address.sin_port = ntohs(port);
        memset(&total.address.sin_zero, '\0', sizeof(total.address.sin_zero));
        check_system(fl, fd);
            
        if (connect(fd, (struct sockaddr *)&total.address, sizeof(struct sockaddr)) == -1)
        {
            perror("cannot connect");
            return -1;
        }
    return fd;
}

int print_code( int socked_fd)
{
    char*pointer;
    char* res = (char*)malloc(sizeof(char)*1024);
    char resp[256];
    int bytes_readed, content_len;
    int base;
    content_len = base = 0;
    if (write(socked_fd, BUFFER, strlen(BUFFER)) < 0)
    {
        printf("write error");
        return -1;
    }
    send(socked_fd, BUFFER, strlen(BUFFER), 0);
    while ((bytes_readed = recv(socked_fd, resp, sizeof(resp), 0)) > 0)
    {
            while (content_len < bytes_readed)
            {
                res[content_len + base] = resp[content_len];
                content_len += 1;
            }
            base = content_len + base;
            res = realloc(res, base + 1024);
            content_len = 0;
    }
    if ((pointer = strstr(res, "Content-Length:")) != NULL)
    {
        int n = atoi(pointer + 16);
      
        if (strcmp("200 OK", res + base - n) == 0) {
            fprintf(stdout, "Success");
        }
        else{
            fprintf(stdout, "%s", res + base - n);
        }
    }
    
    free(res);
    return 0;
}

int my_curl(int ac, char** av)
{
    if (ac != 2) {
        printf("Please enter url\n");
        return -1;
    }
   char* host_name = malloc(strlen(av[1]) + 1);
    char* path = malloc(strlen(av[1]));
    if ((host_name = find_path_index_or_protocol(strdup(av[1]), 1)) == NULL)
    {
        return 1;
    }
    strcpy(path, find_path_index_or_protocol(strdup(av[1]), 0));
    int fd;
    if ((fd = connector_to_name(host_name)))
    {
        memset(BUFFER, 0, BUFFER_SIZE);
        sprintf(BUFFER, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, host_name);
        print_code(fd);
        close(fd);
    }
    return 0;
}

int main(int ac, char** av)
{
    my_curl (ac, av);
    return 0;
}