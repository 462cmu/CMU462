NOTE (sky):
Use the following to build static libraries for freetype:

# i386
./configure CFLAGS="-arch i386" --without-zlib --without-png --without-bzip2
cp objs/.libs/libfreetype.a libfreetype-i386.a

# x86_64
./configure CFLAGS="-arch x86_64" --without-zlib --without-png --without-bzip2
cp objs/.libs/libfreetype.a libfreetype-x86_64.a

On osx, you can create a universal binary
lipo -o libfreetype.a libfreetype-i386.a libfreetype-x86_64.a