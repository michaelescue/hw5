/**
 * @file randarray.h
 * @author Michael Escue 
 * @brief 
 * @version 0.1
 * @date 2019-03-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef VARIABLES
#define VARIABLES
#define ARRAY_SIZE 64000
#define SIZE_MODULUS 10000
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef ERRNO_H
#define ERRNO_H
#include <errno.h>
#endif

/**
 * @brief Creates a pointer to an allocated int array of size "array_size".
 * 
 * @param array_size int size of the array.
 * @return int* pointer to the start of the int array.
 */
#ifndef RANDARRAY_H
#define RANDARRAY_H
int *randarray(void);
#endif