#!/bin/bash

LIBPATH=$AS_LIB_DIR

CFLAGS="-I/$LIBPATH/../include" 
LDFLAGS="-L/$LIBPATH"


for lib in $@
do
   case $lib in
      libunistring)
        CFLAGS+=" -DHAVE_UNISTRING=1"
        LINKFLAGS+=" -lunistring"
      ;;
      zlib)
         CFLAGS+=" -DHAVE_ZLIB=1"
         LINKFLAGS+=" -lz"
      ;;
      libpng)
         CFLAGS+=" -DHAVE_LIBPNG=1"
         LINKFLAGS+=" -lpng16"
      ;;
      esac
done

if [[ -z "$1" ]] then
    CFLAGS+=" -DHAVE_UNISTRING=1 -DHAVE_ZLIB=1 -DHAVE_LIBPNG=1"
    LINKFLAGS+=" -lunistring -lz -lpng16"
fi

make CFLAGS="$CFLAGS" LDFLAGS="$LDFLAGS" LINKFLAGS="$LINKFLAGS"

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LIBPATH

./demo
