#include "../hdr/utilities.h"

// *** BIT-OPERATIONS ***

/*!
 * \param n The REP_TYPE of which the "1"-bits are to be counted
 * \param N The number of bits counted beginning with the 2^0-bit in which you are interested
 * \return The number of "1"-bits among the \c N rightmost bits in \c n.
 */
int count_set_bits(REP_TYPE n, int N) {
    int count = 0;
    n = set_overhang_zero(n, N);
    while (n) {
        n &= (n-1);
        count++;
    }
    return count;
}

/*!
 * \param n The REP_TYPE of which the bits shall be rotated
 * \param N The number of bits counted beginning with the 2^0-bit in which you are interested
 * \return <tt>REP_TYPE</tt> with the cyclically rotated bits.
 */
REP_TYPE rotl(REP_TYPE n, int N) {
    n = set_overhang_zero(n, N);
    return ((n << 1) | ((n >> (N - 1)) & 1)) % ((REP_TYPE) 1 << N);
}

/*!
 * \param n The REP_TYPE of which the bits shall be rotated
 * \param N The number of bits counted beginning with the 2^0-bit in which you are interested
 * \return <tt>REP_TYPE</tt> with the cyclically rotated bits.
 */
REP_TYPE rotr(REP_TYPE n, int N) {
    n = set_overhang_zero(n, N);
    return ((n >> 1) | ((n & 1) << (N - 1))) % ((REP_TYPE) 1 << N);
}

/*!
 * \param n The <tt>REP_TYPE</tt> of which the excess bits shall be set to zero
 * \param N The number of bits counted beginning with the 2^0-bit in which you are interested
 * \return Copy of \c n with all but the N rightmost bits set to zero.
 */
REP_TYPE set_overhang_zero(REP_TYPE n, int N) {
	return n % ((REP_TYPE) 1 << N);
}

/*!
 * \param n The <tt>REP_TYPE</tt> of which the bits shall be reflected
 * \param N The number of bits counted beginning with the 2^0-bit in which you are interested
 * \return Result of the parity (reflection) operation
 */
REP_TYPE reflect_bits(REP_TYPE n, int N) {
	REP_TYPE r = 0;
	int i;

	for(i=0; i<N; i++) {
		n = rotl(n, N);
		r = r | ((n & 1) << i);
	}
	return r;
}

/*!
 * \param n The <tt>REP_TYPE</tt> of which the bits shall be inverted.
 * \param N The number of bits counted beginning with the 2^0-bit in which you are interested
 * \return Result of the inversion operation
 */
REP_TYPE invert_bits(REP_TYPE n, int N) {
    REP_TYPE mask = ((REP_TYPE) 1 << N) -1;
	return ~n & mask;
}

/*!
 * \param n The <tt>REP_TYPE</tt> in which the values of two bits shall be swapped.
 * \param N The number of bits counted starting from the 2^0-bit in which you are interested.
 * \param i The index (counted from left) of the one bit.
 * \param j The index (counted from left) of the other bit.
 * \return Copy of \c n with swapped values of bits \c i and \c j.
 */
REP_TYPE swap_bits(REP_TYPE n, int N, int i, int j) {
	REP_TYPE mask_i, mask_j, val_i, val_j, tmp;

	i=i%N;
	j=j%N;

    if(i<0) i+=N;
    if(j<0) j+=N;

	if(i>j) {
		tmp = j;
		j = i;
		i = tmp;
	}

	mask_i = ((REP_TYPE) 1 << (N-i-1));
	mask_j = ((REP_TYPE) 1 << (N-j-1));

	val_i = (n&mask_i) >> (j-i);
	val_j = (n&mask_j) << (j-i);

	if((n&mask_i)^val_j) {
		if(val_i) {
			n-=mask_i;
		} else {
			n+=mask_i;
		}
	}
	if((n&mask_j)^val_i) {
		if(val_j) {
			n-=mask_j;
		} else {
			n+=mask_j;
		}
	}

	return n;
}

/*!
 * \param n <tt>REP_TYPE</tt> containing the first bit for the comparison.
 * \param i Index (counted from left) of the first bit for the comparison.
 * \param o <tt>REP_TYPE</tt> containing the second bit for the comparison.
 * \param j Index (counted from left) of the second bit for the comparison.
 * \param N The number of bits counted starting from the 2^0-bit in which you are interested.
 * \return \c 1 if both bits are equal, \c 0 otherwise.
 */
int compare_bits(REP_TYPE n, int i, REP_TYPE o, int j, int N) {
	REP_TYPE mask_i, mask_j;

	int ii=i%N;
	int jj=j%N;

    if(ii < 0) ii+=N;
    if(jj < 0) jj+=N;

	mask_i = ((REP_TYPE) 1 << (N-ii-1));
	mask_j = ((REP_TYPE) 1 << (N-jj-1));

	n = (n&mask_i) >> (N-ii-1);
	o = (o&mask_j) >> (N-jj-1);

	if (n==o) return 1;

	return 0;
}

//Returns bits i (incl.) to j (excl.)
REP_TYPE get_section(REP_TYPE n, int i, int j, int N) {
    REP_TYPE res;
    n = reflect_bits(n,N);
    n = n >> i;

    res = 0;
    for(;i<j; i++) {
        res += n & 1;
        res = res << 1;
        n = n >> 1;
    }
    res = res >> 1;

    return res;
}

int cnt_smaller_same_magn(REP_TYPE n, int N) {
    int i, up;
    int res;
    int s = count_set_bits(n,N);
    
    i = 0;
    up = 0;
    res = 0;
    while(i < N && up < s) {
        if(n & 1) {
            up++;
            res += binomial_coeff(i,up);
        }
        i++;
        n=n >> 1;
    }

    return res;
}

int binomial_coeff(int n, int k) {
    int res = 1, i;

    if(k > n || k < 0) return 0;

    if(k > n-k) k = n - k;

    for(i = 0; i < k; i++) {
        res *= (n-i);
        res /= (i+1);
    }

    return res;
}

// *** MEMORY OPERATIONS ***
void *extend_memory(void** ptr, int* oldSize, int extensionSize, int elemSize) {
	void* tmp_ptr;
	int tmp_size;

	tmp_ptr = NULL;
	tmp_size = 0;
	if(elemSize > 0) {
		tmp_ptr = (void*) calloc(*oldSize+extensionSize, elemSize);

		if(extensionSize >= 0) {
			memcpy(tmp_ptr, *ptr, *oldSize * elemSize);
		} else {
			memcpy(tmp_ptr, *ptr, (*oldSize+extensionSize) * elemSize);
		}

		tmp_size = *oldSize + extensionSize;
	}

	free(*ptr);
	
	*oldSize = tmp_size;
	return tmp_ptr;
}

// *** OUTPUT OF BINARY ***

/*!
 * \param n <tt>REP_TYPE</tt> to be converted to a string of "1" and "0"
 * \param buf Pointer to buffer memory for the output string.
 * \returns Pointer to the output string.
 */
char *int2bin(REP_TYPE n, char* buf) {
	#define BITS sizeof(n) * CHAR_BIT
	static char static_buf[BITS + 1];
    int i;

	if(buf==NULL){
		buf = static_buf;
	}

	for(i = BITS - 1; i >= 0; i--) {
		buf[i] = (n & 1) ? '1' : '0';
		n >>= 1;
	}

	buf[BITS] = '\0';
	return buf;

	#undef BITS
}

/*!
 * \param n <tt>REP_TYPE</tt> of which the bit representation shall be printed to the screen.
 * \param N Number of bits (rightmost) which shall be printed to the screen.
 */
void print_bits(REP_TYPE n, int N) {
	char* out;
	out = int2bin(n,NULL);
	out = &(out[sizeof(REP_TYPE)*CHAR_BIT - N]);

	printf("%s\n", out);
}
