#include <stdio.h>
#include <stdlib.h>

#ifndef WIN32
#define WIN32
#endif

#include <gimxserial/include/gserial.h>

#define BYTE_VERSION      0x77
#define BYTE_LEN_0_BYTE   0x00

void showBytes(unsigned char* buf, int count);

int on_read(void * user, const void * buf, int status) {
    puts("on_read");
    return 0;
}
int on_write(void * user, int status) {
    puts("on_write");
    return 0;
}
int on_close(void * user) {
    puts("on_close");
    return 0;
}
int on_register(HANDLE handle, void * user, const GPOLL_CALLBACKS * callbacks) {
    puts("on_register");
    return 0;
}
int on_remove(HANDLE handle) {
    puts("on_remove");
    return 0;
}

int main()
{
    puts("hello gserial");
    struct gserial_device* device = gserial_open("COM3", 500000);

    GSERIAL_CALLBACKS callbacks = {
        .fp_read = on_read,
        .fp_write = on_write,
        .fp_close = on_close,
        .fp_register = on_register,
        .fp_remove = on_remove,
    };

    int ret2 = gserial_set_read_size(device, 4);
    int ret0 = gserial_register(device, "koudai", &callbacks);

    unsigned char buf[] = { 0x77, 0x00 };
    int ret1 = gserial_write_timeout(device, buf, 2, 1000);
    gserial_write_timeout(device, buf, 2, 1000);
    gserial_write_timeout(device, buf, 2, 1000);

    unsigned char buf2[] = { 0x01,0x02,0x03,0x04,0x05, };

    int ret3 = gserial_read_timeout(device,buf2,4,1000);
    showBytes(buf2, 5);

    printf("ret0=%d, ret1=%d, ret2=%d, ret3=%d\n", ret0, ret1, ret2, ret3);
    getchar();
    gserial_close(device);
}

void showBytes(unsigned char* buf, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("0x%02x ", buf[i]);
    }
    printf("\n");
}
