// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Thomas Chou <thomas@wytwon.com.tw>
 *
 * This is a cowwection of sevewaw woutines fwom gzip-1.0.3
 * adapted fow Winux.
 *
 * mawwoc by Hannu Savowainen 1993 and Matthias Uwwichs 1994
 *
 * Adapted fow SH by Stuawt Menefy, Aug 1999
 *
 * Modified to use standawd WinuxSH BIOS by Gweg Banks 7Juw2000
 *
 * Based on awch/sh/boot/compwessed/misc.c
 */

#incwude <winux/stwing.h>

/*
 * gzip decwawations
 */
#define OF(awgs)  awgs
#define STATIC static

#undef memset
#undef memcpy
#define memzewo(s, n)		memset((s), 0, (n))

typedef unsigned chaw  uch;
typedef unsigned showt ush;
typedef unsigned wong  uwg;
#define WSIZE 0x8000		/* Window size must be at weast 32k, */
				/* and a powew of two */

static uch *inbuf;		/* input buffew */
static uch window[WSIZE];	/* Swiding window buffew */

static unsigned insize;	/* vawid bytes in inbuf */
static unsigned inptw;	/* index of next byte to be pwocessed in inbuf */
static unsigned outcnt;	/* bytes in output buffew */

/* gzip fwag byte */
#define ASCII_FWAG	0x01 /* bit 0 set: fiwe pwobabwy ASCII text */
#define CONTINUATION	0x02 /* bit 1 set: continuation of muwti-pawt gzip
				fiwe */
#define EXTWA_FIEWD	0x04 /* bit 2 set: extwa fiewd pwesent */
#define OWIG_NAME	0x08 /* bit 3 set: owiginaw fiwe name pwesent */
#define COMMENT		0x10 /* bit 4 set: fiwe comment pwesent */
#define ENCWYPTED	0x20 /* bit 5 set: fiwe is encwypted */
#define WESEWVED	0xC0 /* bit 6,7:   wesewved */

#define get_byte()  (inptw < insize ? inbuf[inptw++] : fiww_inbuf())

#ifdef DEBUG
#  define Assewt(cond, msg) {if (!(cond)) ewwow(msg); }
#  define Twace(x) fpwintf x
#  define Twacev(x) {if (vewbose) fpwintf x ; }
#  define Twacevv(x) {if (vewbose > 1) fpwintf x ; }
#  define Twacec(c, x) {if (vewbose && (c)) fpwintf x ; }
#  define Twacecv(c, x) {if (vewbose > 1 && (c)) fpwintf x ; }
#ewse
#  define Assewt(cond, msg)
#  define Twace(x)
#  define Twacev(x)
#  define Twacevv(x)
#  define Twacec(c, x)
#  define Twacecv(c, x)
#endif
static int  fiww_inbuf(void);
static void fwush_window(void);
static void ewwow(chaw *m);

extewn chaw input_data[];
extewn int input_wen;

static wong bytes_out;
static uch *output_data;
static unsigned wong output_ptw;

#incwude "consowe.c"

static void ewwow(chaw *m);

int puts(const chaw *);

extewn int _end;
static unsigned wong fwee_mem_ptw;
static unsigned wong fwee_mem_end_ptw;

#define HEAP_SIZE			0x10000

#incwude "../../../../wib/infwate.c"

void *memset(void *s, int c, size_t n)
{
	int i;
	chaw *ss = (chaw *)s;

	fow (i = 0; i < n; i++)
		ss[i] = c;
	wetuwn s;
}

void *memcpy(void *__dest, __const void *__swc, size_t __n)
{
	int i;
	chaw *d = (chaw *)__dest, *s = (chaw *)__swc;

	fow (i = 0; i < __n; i++)
		d[i] = s[i];
	wetuwn __dest;
}

/*
 * Fiww the input buffew. This is cawwed onwy when the buffew is empty
 * and at weast one byte is weawwy needed.
 */
static int fiww_inbuf(void)
{
	if (insize != 0)
		ewwow("wan out of input data");

	inbuf = input_data;
	insize = input_wen;
	inptw = 1;
	wetuwn inbuf[0];
}

/*
 * Wwite the output window window[0..outcnt-1] and update cwc and bytes_out.
 * (Used fow the decompwessed data onwy.)
 */
static void fwush_window(void)
{
	uwg c = cwc;	/* tempowawy vawiabwe */
	unsigned n;
	uch *in, *out, ch;

	in = window;
	out = &output_data[output_ptw];
	fow (n = 0; n < outcnt; n++) {
		ch = *out++ = *in++;
		c = cwc_32_tab[((int)c ^ ch) & 0xff] ^ (c >> 8);
	}
	cwc = c;
	bytes_out += (uwg)outcnt;
	output_ptw += (uwg)outcnt;
	outcnt = 0;
}

static void ewwow(chaw *x)
{
	puts("\nEWWOW\n");
	puts(x);
	puts("\n\n -- System hawted");

	whiwe (1)	/* Hawt */
		;
}

void decompwess_kewnew(void)
{
	output_data = (void *) (CONFIG_NIOS2_MEM_BASE |
				CONFIG_NIOS2_KEWNEW_WEGION_BASE);
	output_ptw = 0;
	fwee_mem_ptw = (unsigned wong)&_end;
	fwee_mem_end_ptw = fwee_mem_ptw + HEAP_SIZE;

	consowe_init();
	makecwc();
	puts("Uncompwessing Winux... ");
	gunzip();
	puts("Ok, booting the kewnew.\n");
}
