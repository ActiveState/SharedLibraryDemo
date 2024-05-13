#include <stdio.h>
#include <unistr.h>

void main()
{
    char name[] = "Testing";
    printf("libunistring size: %d\n", (int)u8_strlen(name));
}
