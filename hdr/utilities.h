/*! \file utilities.h
 * Contains declarations for utility functions (bit operations).
 *
 * Indexing
 *
 * \author Markus Schmitt
 * \date Jan 2015
 */


#ifndef utilities
#define utilities

#ifndef REP_TYPE
#define REP_TYPE unsigned int
#endif

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

//! Function to count the "1"-bits in an REP_TYPE
/*!
 * This function counts the number of bits set to "1" among the \c N rightmost bits in an <tt>REP_TYPE</tt>.
 */
int count_set_bits(REP_TYPE n, int N);

//! Function to perform cyclic bit shift to the left
/*!
 * This function performs a cyclic shift to the left of the \c N rightmost bits in an <tt>REP_TYPE</tt>.
 */
REP_TYPE rotl(REP_TYPE n, int N);

//! Function to perform cyclic bit shift to the right
/*!
 * This function performs a cyclic shift to the right of the \c N rightmost bits in an <tt>REP_TYPE</tt>.
 */
REP_TYPE rotr(REP_TYPE n, int N);

//! Function to perform a parity operation on bits
/*
 * This function performs a parity operation on the \c N rightmost bits of an <tt>REP_TYPE</tt>.
 * It exchanges the values of bit b_i and bit b_[N-i].
 */
REP_TYPE reflect_bits(REP_TYPE n, int N);

//! Function to invert bits.
/*
 * This function inverts the \c N rightmost bits of an <tt>unsigned</tt> int.
 */
REP_TYPE invert_bits(REP_TYPE n, int N);

//! Function to set leftmost bits to zero.
/*
 * This function sets all but the \c N rightmost bits of an <tt>REP_TYPE</tt> to zero.
 */
REP_TYPE set_overhang_zero(REP_TYPE n, int N);

//! Function to swap bits.
/*!
 * This function swaps the values of bit \c i and \c j of an <tt>REP_TYPE</tt>.
 */
REP_TYPE swap_bits(REP_TYPE n, int N, int i, int j);

//! Function to compare bits.
/*!
 * Function to compare the values of bit \c i and \c j of an <tt>REP_TYPE</tt>.
 */
int compare_bits(REP_TYPE n, int i, REP_TYPE o, int j, int N);

int cnt_smaller_same_magn(REP_TYPE n, int N); 
int binomial_coeff(int n, int k);
REP_TYPE get_section(REP_TYPE n, int i, int j, int N);

//! Function to convert an \c integer representation into a string of "1" and "0"
/*!
 * Reads the bit sequence of an <tt>REP_TYPE</tt> representation and builds a string of "1" and "0" accordingly.
 * If \c NULL is passed as \c buf argument, the needed \c char array is internally allocated (need not be freed).
 */
char* int2bin(REP_TYPE n, char* buf);

//! Function to print the bits of an \c integer representation to the screen
/*!
 * Prints the rightmost \c len bits of the given <tt>REP_TYPE</tt> representation to the screen.
 */
void print_bits(REP_TYPE n, int N);

void *extend_memory(void** ptr, int* oldSize, int extensionSize, int elem_size);

REP_TYPE string_to_state(char* str, int N);

#endif
