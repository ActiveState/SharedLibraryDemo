#include <stdio.h>
#include <string.h>

#ifdef HAVE_UNISTRING
#include <unistr.h>
#endif

#ifdef HAVE_ZLIB
#include <zlib.h>
#include <assert.h>
#include <stdlib.h>
#endif

#ifdef HAVE_LIBPNG
#include <png.h>
#include <stdlib.h>

png_infop info_ptr; 
png_bytepp row_pointers; 


void read_png(char *file_name)
{
    printf("libpng: Reading %s file\n", file_name);	
    FILE *fp = fopen(file_name, "rb");
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);   
    png_init_io(png_ptr, fp);
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
    row_pointers = png_get_rows(png_ptr, info_ptr);
    png_destroy_read_struct(&png_ptr, NULL, NULL); 
    fclose(fp);
    printf("libpng: Done reading %s file\n", file_name);
}

void write_png(char *file_name)
{
    printf("libpng: Writing duplicate %s file\n", file_name);
    FILE *fp = fopen(file_name, "wb");
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    printf("libpng: Done writing %s file\n", file_name);
}

#endif

void main()
{
#ifdef HAVE_UNISTRING
    printf("\n\e[32mTesting libunistring...\n\e[0m");
    char name[] = "Testing";
    printf("The libunistring size of %s: %d\n", name, (int)u8_strlen(name));
    printf("\e[32mTest passes.\n\e[0m");
#endif

#ifdef HAVE_ZLIB
        printf("\n");
        printf("\e[32mTesting zlib...\n\e[0m");
	char src[] = "The initialization of the state is the same, except that there is no compression level, of course, and two more elements of the structure are initialized. avail_in and next_in must be initialized before calling inflateInit(). This is because the application has the option to provide the start of the zlib stream in order for inflateInit() to have access to information about the compression method to aid in memory allocation. In the current implementation of zlib (up through versions 1.2.x), the method-dependent memory allocations are deferred to the first call of inflate() anyway. However those fields must be initialized since later versions of zlib that provide more compression methods may take advantage of this interface. In any case, no decompression is performed by inflateInit(), so the avail_out and next_out fields do not need to be initialized before calling.";
	long unsigned int src_len = strlen(src) + 1;

	long unsigned int dest_len = compressBound(src_len);
	char *dest = malloc(dest_len);
	printf("buffer len=%lu\n", dest_len);
	
	/* compress */
	assert(compress(dest, &dest_len, src, src_len) == Z_OK);

	printf("orgin len=%lu\n", src_len);
	printf("after compress, len=%lu\n", dest_len);

	/* decompress */
	src_len = sizeof(src);
	memset(src, 0, sizeof(src));
	
	assert(uncompress(src, &src_len, dest, dest_len) == Z_OK);
	printf("after decompress, len=%lu\n", src_len);
	
	free(dest);
        printf("\e[32mTest passes.\n\e[0m");	
#endif

#ifdef HAVE_LIBPNG
    printf("\n");
    printf("\e[32mTesting libpng...\n\e[0m");
    char file_name[] = "Sample.png";
    char outfile_name[] = "duplicate.png";
    read_png(file_name);
    write_png(outfile_name);
    printf("\e[32mTest passes.\n\e[0m\n");
#endif
}
