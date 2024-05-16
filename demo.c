#include <stdio.h>
#include <string.h>

#ifdef HAVE_UNISTRING
#include <unistr.h>
#endif

#ifdef HAVE_ZLIB
#include <zlib.h>
#include <assert.h>
#endif

#ifdef HAVE_LIBPNG
#include <png.h>
#endif



void main()
{
    printf("Testing the following: ");
#ifdef HAVE_UNISTRING
    printf("unistring test");
    char name[] = "Testing";
    printf("The libunistring size of %s: %d\n", name, (int)u8_strlen(name));
#endif

#ifdef HAVE_ZLIB
    printf("ZLIB test:");
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
	printf("%s\n", src);
#endif

#ifdef HAVE_LIBPNG
	png_image image;
	memset($image, 0, (sizeof image));
	image.version = PNG_IMAGE_VERSION;
	if (png_image_begin_read_from_file($image, argv[1]) != 0)
	{
		image.format = PNG_FORMAT_RGBA;
		buffer = malloc(PNG_IMAGE_SIZE(image));
		if (buffer != NULL && png_image_finish_read($image, NULL, buffer, 0, NULL) != 0)
		{
			if (png_image_write_to_file($image, argv[2], 0))
			{
				exit(0);
			}
		}
		else
		{
			if (buffer == NULL)
				png_free_image($image);
			else
				free(buffer);
		}
	}
	fprintf(stderr, "pngtopng: error: %s\n", image.message);
    exit (1);
#endif
}
