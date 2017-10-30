// COMP1511 17s2 -- Image ADT implementation
// 2017-09-10    Jashank Jeremy <{jashankj,z5017851}@cse.unsw.edu.au>
//
// You probably shouldn't change this file.
// Instead, compile it with your own code by running
//
//     $ dcc -o myProgram myProgram.c Image.c imageAsBMP.c

#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "Image.h"

#ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wreserved-id-macro"
# pragma clang diagnostic ignored "-Wunused-macros"
#endif
#ifndef __unused
#define __unused __attribute__((unused))
#endif // !defined(__unused)
#ifdef __clang__
# pragma clang diagnostic pop
#endif // __clang__

// Various definitions for a BMP header.
#define PIXEL_START 26
#define PIXEL_BYTES 3
#define PIXEL_ALIGN 4
#define PIXEL_BITS  24
#define HEADER_SIZE 12

// Helper functions that manage image allocation and writing.
static size_t allocImageBuffer (Image, unsigned char **);
static void writeDIBHeader (Image, size_t, unsigned char *);
static void writeBMP (Image, size_t, unsigned char *);

// Given an image, and a reference to a buffer, allocates an array of
// `unsigned char`s to fit the header and pixels in, containing a BMP
// image, and returns the size of the allocation.
//
// Strictly, this definition shouldn't be in this ADT header file, as
// it is an ADT consumer, but we're keeping it here for convenience.
// You could write a somewhat better version of this with access to
// the ADT's innards.
//
// To use it, you would do:
//
//     unsigned char *buf;
//     int size = imageAsBMP (i, &buf);
//
// Now you have a full image in `buf`; you could write this to
// standard output, for example, by using the `fwrite` standard
// library function from <stdio.h>:
//
//     fwrite (buf, sizeof (unsigned char), size, stdout);
//
// This writes `buf`, which contains `size` items of `unsigned char`
// size each, to `stdout`.
//
// Don't forget to `free` the allocation that was made!
//
//     free (buf);
//
int imageAsBMP (
    Image i,
    unsigned char **buf) {

    size_t allocSize = allocImageBuffer (i, buf);
    writeDIBHeader (i, allocSize, *buf);
    writeBMP (i, allocSize, *buf);

    // Explicitly downcast the allocation size to `int`, to suppress
    // a Clang angry.
    return (int)allocSize;
}

static size_t allocImageBuffer (
    Image i,
    unsigned char **buf) {

    // For an image that's W*H, we need W*H*sizeof(pixel) bytes for
    // the body, and `PIXEL_START` bytes for the header.
    size_t allocSize =
        PIXEL_START +
        (imageGetWidth (i) * imageGetHeight (i) * sizeof (pixel));

    *buf = calloc (allocSize, sizeof (unsigned char));
    if (*buf == NULL) {
        err (EX_OSERR,
            "imageAsBMP: couldn't allocate %zu bytes", allocSize);
    }

    return allocSize;
}

static void writeDIBHeader (
    Image i,
    size_t allocSize __unused,
    unsigned char *buf) {

    // Create a buffer to put the bitmap header data in, temporarily.
    // We'll copy it across to the final buffer shortly.
    char headerBuffer[PIXEL_START] = {'\0'};

    // The initial `BM` bytes.
    headerBuffer[0x00] = 'B';
    headerBuffer[0x01] = 'M';

    // File size
    unsigned int rowSize = imageGetWidth (i) * PIXEL_BYTES;
    unsigned int rowPadding = 0;
    if (rowSize % PIXEL_ALIGN != 0) {
        // Pad pixel to align properly
        rowPadding = PIXEL_ALIGN - (rowSize % PIXEL_ALIGN);
        rowSize += rowPadding;
    }
    unsigned int pixelData = (rowSize * imageGetHeight (i));

    // We use memcpy so you don't have to
    unsigned int fileSize = PIXEL_START + pixelData;
    memcpy (&(headerBuffer[0x02]), &fileSize, sizeof (fileSize));

    // Fields 6 and 8 are reserved, so now skip to field 0xA.
    // Pixels start immediately after header.
    unsigned int pixelStart = PIXEL_START;
    memcpy (&(headerBuffer[0x0A]), &pixelStart, sizeof (pixelStart));

    // The various different header formats are marked by the size of
    // the header.  We're writing in the classic `BITMAPCOREHEADER`
    // format (as supported by Microsoft Windows 2.0!) which has a
    // 12-byte header.
    unsigned int headerSize = HEADER_SIZE;
    memcpy (&(headerBuffer[0x0E]), &headerSize, sizeof (headerSize));

    // Image width and height
    unsigned short width = (unsigned short)imageGetWidth (i);
    memcpy (&(headerBuffer[0x12]), &width, sizeof (width));
    unsigned short height = (unsigned short)imageGetHeight (i);
    memcpy (&(headerBuffer[0x14]), &height, sizeof (height));

    // Number of image planes (1)
    unsigned short planes = 1;
    memcpy (&(headerBuffer[0x16]), &planes, sizeof (planes));

    // Number of bits per pixel (3 pixels * 8 bits = 24 bpp)
    unsigned short bitsPerPixel = PIXEL_BITS;
    memcpy (&(headerBuffer[0x18]), &bitsPerPixel, sizeof (bitsPerPixel));

    // OK, copy headerBuffer into the target buffer.  With luck, the
    // compiler will optimise all the other `memcpy`s to this one...
    memcpy (buf, headerBuffer, PIXEL_START);
}

static void writeBMP (
    Image i,
    size_t allocSize __unused,
    unsigned char *buf) {

    unsigned int rowSize = imageGetWidth (i) * PIXEL_BYTES;
    unsigned int rowPadding = 0;
    if (rowSize % PIXEL_ALIGN != 0) {
        // Pad pixel to align properly
        rowPadding = PIXEL_ALIGN - (rowSize % PIXEL_ALIGN);
        rowSize += rowPadding;
    }

    size_t y = 0;
    while (y < imageGetHeight (i)) {
        size_t x = 0;
        while (x < imageGetWidth (i)) {
			point p = { (unsigned int)x, (unsigned int)y };
            pixel pixel = imageGetPixel (i, p);
            size_t byteIndex = (y * rowSize) + (x * PIXEL_BYTES);

            // Write the blue, green, then red pixels
            buf[PIXEL_START + byteIndex + 0] = pixel.blue;
            buf[PIXEL_START + byteIndex + 1] = pixel.green;
            buf[PIXEL_START + byteIndex + 2] = pixel.red;
            x++;
        }
        y++;
    }
}
