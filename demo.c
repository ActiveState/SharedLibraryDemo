#include <stdio.h>
#include <unistr.h>
#include <unistring/version.h>

void main()
{
	char name[] = "Testing";
    printf("libunistring size: %d\n", (int)u8_strlen(name));
    printf(_LIBUNISTRING_VERSION);
}
