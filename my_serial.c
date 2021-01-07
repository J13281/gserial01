#include <stdio.h>
#include <stdlib.h>

#ifndef WIN32
#define WIN32
#endif

#include <gimxserial/include/gserial.h>

#define BYTE_VERSION      0x77
#define BYTE_LEN_0_BYTE   0x00

void showBytes(unsigned char* buf, int count);

static int on_read(void * user, const void * buf, int status) {
    puts("on_read");
    return status;
}
static int on_write(void * user, int status) {
    puts("on_write");
    return status;
}
static int on_close(void * user) {
    puts("on_close");
    return 1;
}
static int on_register(HANDLE handle, void * user, const GPOLL_CALLBACKS * callbacks) {
    puts("on_register");
    return 1;
}
static int on_remove(HANDLE handle) {
    puts("on_remove");
    return 1;
}

int main()
{
    puts("hello gserial");
    struct gserial_device* device = gserial_open("COM3", 500000);
    GSERIAL_CALLBACKS callbacks = {
        .fp_read = on_read,
        .fp_write = on_write,
        .fp_close = on_close,
        .fp_register = gpoll_register_handle,
        .fp_remove = gpoll_remove_handle,
    };

    int ret0 = gserial_set_read_size(device, 0xFF);
    int ret1 = gserial_register(device, "koudai", &callbacks);

    const unsigned char buf[] = { BYTE_VERSION, BYTE_LEN_0_BYTE };
    unsigned char buf2[] = { 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, };
    int c = 0;
    while ((c = getchar()) != 'q')
    {
        int ret3 = gserial_write(device, (void*)buf, 2);
        printf("ret3=%d", ret3);
        // int ret4 = gserial_read_timeout(device, buf2, sizeof(buf2), 100);
        //printf("ret3=%d, ret4=%d\n", ret3, ret4);
    }

    gserial_close(device);
}

void showBytes(unsigned char* buf, int count)
{
    for (int i = 0; i < count; i++) printf("0x%02x ", buf[i]);
    printf("\n");
}
