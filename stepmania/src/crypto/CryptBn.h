#ifndef SSHBN_H
#define SSHBN_H

#if defined __GNUC__ && defined __i386__
typedef unsigned long BignumInt;
typedef unsigned long long BignumDblInt;
#define BIGNUM_INT_MASK  0xFFFFFFFFUL
#define BIGNUM_TOP_BIT   0x80000000UL
#define BIGNUM_INT_BITS  32
#define MUL_WORD(w1, w2) ((BignumDblInt)w1 * w2)
#define DIVMOD_WORD(q, r, hi, lo, w) \
__asm__("div %2" : \
		"=d" (r), "=a" (q) : \
		"r" (w), "d" (hi), "a" (lo))
#else
typedef unsigned short BignumInt;
typedef unsigned long BignumDblInt;
#define BIGNUM_INT_MASK  0xFFFFU
#define BIGNUM_TOP_BIT   0x8000U
#define BIGNUM_INT_BITS  16
#define MUL_WORD(w1, w2) ((BignumDblInt)w1 * w2)
#define DIVMOD_WORD(q, r, hi, lo, w) do { \
	BignumDblInt n = (((BignumDblInt)hi) << BIGNUM_INT_BITS) | lo; \
		q = n / w; \
		r = n % w; \
} while (0)
#endif

#define BIGNUM_INT_BYTES (BIGNUM_INT_BITS / 8)
typedef BignumInt *Bignum;

Bignum copybn(Bignum b);
Bignum bn_power_2(int n);
void bn_restore_invariant(Bignum b);
Bignum bignum_from_long(unsigned long n);
void freebn(Bignum b);
Bignum modpow(Bignum base, Bignum exp, Bignum mod);
Bignum modmul(Bignum a, Bignum b, Bignum mod);
void decbn(Bignum n);
extern Bignum Zero, One;
unsigned char *bignum_to_buffer( const Bignum bn, int *nbytes );
Bignum bignum_from_buffer(const unsigned char *data, int nbytes);
Bignum bignum_from_bytes(const unsigned char *data, int nbytes);
unsigned char *bignum_to_bytes( const Bignum bn, int *nbytes );
int ssh1_read_bignum(const unsigned char *data, Bignum * result);
int bignum_bitcount(Bignum bn);
int ssh1_bignum_length(Bignum bn);
int ssh2_bignum_length(Bignum bn);
unsigned char bignum_byte( const Bignum bn, int i );
int bignum_bit( const Bignum bn, int i );
void bignum_set_bit(Bignum bn, int i, int value);
int ssh1_write_bignum(void *data, Bignum bn);
Bignum biggcd(Bignum a, Bignum b);
unsigned short bignum_mod_short(Bignum number, unsigned short modulus);
Bignum bignum_add_long(Bignum number, unsigned long addend);
Bignum bigmul(Bignum a, Bignum b);
Bignum bigmuladd(Bignum a, Bignum b, Bignum addend);
Bignum bigdiv(Bignum a, Bignum b);
Bignum bigmod(Bignum a, Bignum b);
Bignum modinv(Bignum number, Bignum modulus);
Bignum bignum_bitmask(Bignum number);
Bignum bignum_rshift(Bignum number, int shift);
int bignum_cmp(Bignum a, Bignum b);
char *bignum_decimal(Bignum x);

#endif
