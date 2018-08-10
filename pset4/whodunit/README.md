# Questions

## What's `stdint.h`?

`stdint.h` provides new identifiers/synonyms(typedefs) for integer types that can only hold a range of values(fixed-width integer types).
`stdint.h` makes it easier for code to be run on different machines since it defines the basic data types.
Since the basic data types are defined into specific names, you can use the specific names when you want an exact number of bits.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

### `uint8_t`
`uint8_t` is part of `typedef unsigned char uint8_t` in `stdint.h`, which means that `uint8_t` is an alias for `unsigned char`.
Since it is unsigned, the integer type can range from 0 to 2^n - 1. In this case, `n = 8`, so `uint8_t` can range from 0 through 255 decimal.
`uint8_t`, called a `BYTE` in `bmp.h`, is used for when you want exactly 8 unsigned bits or an unsigned byte.
An example of `uint8_t` being used is the amount of blue, green, or red in a pixel.

### `uint32_t`
`uint32_t` is part of `typedef unsigned int uint32_t` in `stdint.h`, which means that `uint32_t` is an alias for `unsigned int`.
Since it is unsigned, the integer type can range from 0 through 4294967295 decimal.
`uint32_t`, called a `DWORD` in `bmp.h`, is used for when you want exactly 32 unsigned bits, or 4 unsigned bytes.
An example of `uint32_t` being used is denoting the size of a bitmap file in bytes.

### `int32_t`
`int32_t` is part of `typedef int int32_t` in `stdint.h`, which means that `int32_t` is an alias for `int`.
Since it is signed, the integer type can range from -(2^(n-1)) to 2^(n-1) - 1. In this case, `int32_t` can range from –2147483648 through 2147483647 decimal.
`int32_t`, called a `LONG` in `bmp.h`, is used for when you want exactly 32 signed bits, or 4 signed bytes.
An example of `int32_t` being used is denoting the width of the bitmap file in pixels.

### `uint16_t`
`uint16_t` is part of `typedef unsigned short uint16_t` in `stdint.h`, which means that `uint16_t` is an alias for `unsigned short`.
`uint16_t` can range from 0 through 65535 decimal.
`uinta6_t`, called a `WORD` in `bmp.h`, is used for when you want exactly 16 unsigned bits, or 2 unsigned bytes.
An example of `uint16_t` being used is denoting the width of the bitmap file in pixels.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

A `BYTE` is 1 byte, a `DWORD` is 4 bytes, a `LONG` is also 4 bytes, and a `WORD` is 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The two bytes that are at the beginning of any bmp file are "BM" in ascii, 16973 in decimal, and 42 4D in hexadecimal.

## What's the difference between `bfSize` and `biSize`?

`bfsize` is the size of the bitmap file in bytes, while `bisize` is the size of `BITMAPINFOHEADER`, in bytes.
In a 24-bit BITMAP file, `bisize` will be 28, since 28 in hexadecimal is 40 decimal.

## What does it mean if `biHeight` is negative?

If `biHeight` is negative, the way the bitmap file is compressed changes.
The bitmap file is not compressed(biCompression is BI_RGB).
For 16-bit and 32-bit bimaps, the bitmap is not compressed and three `DWORDS` are placed directly after the `BITMAPINFOHEADER`.
These three `DWORDS` are color masks, which outline the red, green, and blue components of each pixel.
Ex -
Red: 0111110000000000
Green: 0000001111100000
Blue: 0000000000011111
These masks show that 5 bits of the `DWORD` of each pixel is for red, green, and blue, respectively.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount` specifies the bits per pixel of the BMP.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the input file cannot be opened for reading, `fopen` might return `NULL`.

## Why is the third argument to `fread` always `1` in our code?

`fread`'s usage is `fread(<buffer>, <size>, <qty>, <file pointer>)`.
This basically means: I want _<qty>_ many things that are _<size>_ big from the file pointed to by _<file pointer>_ and I want everything I get to be stored in _<buffer>_
In `copy.c`, `fread(<buffer>, <size>, <qty>, <file pointer>)` is ` fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);`.
When translated into a statement, it would be: I want _1_ many units that are _14 bytes_(for 24-bit bitmaps) big from the file pointed to by _inptr_(this file is _infile_), stored in _&bf_, which is the address of the struct `BITMAPFILEHEADER`.
The third argument of `fread` is 1 because a bitmap has at most 1 `BITMAPFILEHEADER`, so only the bytes that make up 1 `BITMAPFILEHEADER` should be stored.
If it was more than or less than 1, different or no bytes would get stored as the bitmap file header, which is indesirable since then we would be stepping into bitmapinfoheader territory.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

Padding is assigned ((4 - 3 * 3) % 4) % 4 = _3_ if `bi.biWidth` is `3`.

## What does `fseek` do?

`fseek` is like the wheel on an old cd/dvd player in how it allows you to move through the file.
`fseek` is used like: `fseek(FILE *pointer, offset, position)`.
Translated into english, `fseek` is: I want to go _offset_ many bytes away from _position_ in the file pointed to by _*pointer_.
Ex -
`fseek(fptr, 8, SEEK_SET)` means: move _8_ bytes away from the beginning(`SEEK_SET` means beginning) in the file pointed to by _fptr_.


## What is `SEEK_CUR`?

`SEEK_CUR` is the current position in a file.

## Whodunit?

It was Professor Plum with the candlestick in the library.
