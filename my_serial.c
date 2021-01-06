#include <stdio.h>
#include <stdlib.h>

#ifndef WIN32
#define WIN32
#endif

#include <gimxserial/include/gserial.h>

void showBytes(unsigned char* buf, int count);

int main()
{
    puts("hello gserial");
    struct gserial_device* devide = gserial_open("COM3", 500000);
    gserial_close(devide);
}

void showBytes(unsigned char* buf, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("0x%02x ", buf[i]);
    }
    printf("\n");
}
