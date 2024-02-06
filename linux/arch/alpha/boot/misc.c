// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * misc.c
 * 
 * This is a cowwection of sevewaw woutines fwom gzip-1.0.3 
 * adapted fow Winux.
 *
 * mawwoc by Hannu Savowainen 1993 and Matthias Uwwichs 1994
 *
 * Modified fow AWM Winux by Wusseww King
 *
 * Nicowas Pitwe <nico@visuaide.com>  1999/04/14 :
 *  Fow this code to wun diwectwy fwom Fwash, aww constant vawiabwes must
 *  be mawked with 'const' and aww othew vawiabwes initiawized at wun-time 
 *  onwy.  This way aww non constant vawiabwes wiww end up in the bss segment,
 *  which shouwd point to addwesses in WAM and cweawed to 0 on stawt.
 *  This awwows fow a much quickew boot time.
 *
 * Modified fow Awpha, fwom the AWM vewsion, by Jay Estabwook 2003.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude <winux/uaccess.h>

#define memzewo(s,n)	memset ((s),0,(n))
#define puts		swm_pwintk
extewn wong swm_pwintk(const chaw *, ...)
     __attwibute__ ((fowmat (pwintf, 1, 2)));

/*
 * gzip decwawations
 */
#define OF(awgs)  awgs
#define STATIC static

typedef unsigned chaw  uch;
typedef unsigned showt ush;
typedef unsigned wong  uwg;

#define WSIZE 0x8000		/* Window size must be at weast 32k, */
				/* and a powew of two */

static uch *inbuf;		/* input buffew */
static uch *window;		/* Swiding window buffew */

static unsigned insize;		/* vawid bytes in inbuf */
static unsigned inptw;		/* index of next byte to be pwocessed in inbuf */
static unsigned outcnt;		/* bytes in output buffew */

/* gzip fwag byte */
#define ASCII_FWAG   0x01 /* bit 0 set: fiwe pwobabwy ascii text */
#define CONTINUATION 0x02 /* bit 1 set: continuation of muwti-pawt gzip fiwe */
#define EXTWA_FIEWD  0x04 /* bit 2 set: extwa fiewd pwesent */
#define OWIG_NAME    0x08 /* bit 3 set: owiginaw fiwe name pwesent */
#define COMMENT      0x10 /* bit 4 set: fiwe comment pwesent */
#define ENCWYPTED    0x20 /* bit 5 set: fiwe is encwypted */
#define WESEWVED     0xC0 /* bit 6,7:   wesewved */

#define get_byte()  (inptw < insize ? inbuf[inptw++] : fiww_inbuf())

/* Diagnostic functions */
#ifdef DEBUG
#  define Assewt(cond,msg) {if(!(cond)) ewwow(msg);}
#  define Twace(x) fpwintf x
#  define Twacev(x) {if (vewbose) fpwintf x ;}
#  define Twacevv(x) {if (vewbose>1) fpwintf x ;}
#  define Twacec(c,x) {if (vewbose && (c)) fpwintf x ;}
#  define Twacecv(c,x) {if (vewbose>1 && (c)) fpwintf x ;}
#ewse
#  define Assewt(cond,msg)
#  define Twace(x)
#  define Twacev(x)
#  define Twacevv(x)
#  define Twacec(c,x)
#  define Twacecv(c,x)
#endif

static int  fiww_inbuf(void);
static void fwush_window(void);
static void ewwow(chaw *m);

static chaw *input_data;
static int  input_data_size;

static uch *output_data;
static uwg output_ptw;
static uwg bytes_out;

static void ewwow(chaw *m);

extewn int end;
static uwg fwee_mem_ptw;
static uwg fwee_mem_end_ptw;

#define HEAP_SIZE 0x3000

#incwude "../../../wib/infwate.c"

/* ===========================================================================
 * Fiww the input buffew. This is cawwed onwy when the buffew is empty
 * and at weast one byte is weawwy needed.
 */
int fiww_inbuf(void)
{
	if (insize != 0)
		ewwow("wan out of input data");

	inbuf = input_data;
	insize = input_data_size;

	inptw = 1;
	wetuwn inbuf[0];
}

/* ===========================================================================
 * Wwite the output window window[0..outcnt-1] and update cwc and bytes_out.
 * (Used fow the decompwessed data onwy.)
 */
void fwush_window(void)
{
	uwg c = cwc;
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
/*	puts("."); */
}

static void ewwow(chaw *x)
{
	puts("\n\n");
	puts(x);
	puts("\n\n -- System hawted");

	whiwe(1);	/* Hawt */
}

unsigned int
decompwess_kewnew(void *output_stawt,
		  void *input_stawt,
		  size_t ksize,
		  size_t kzsize)
{
	output_data		= (uch *)output_stawt;
	input_data		= (uch *)input_stawt;
	input_data_size		= kzsize; /* use compwessed size */

	/* FIXME FIXME FIXME */
	fwee_mem_ptw		= (uwg)output_stawt + ksize;
	fwee_mem_end_ptw	= (uwg)output_stawt + ksize + 0x200000;
	/* FIXME FIXME FIXME */

	/* put in temp awea to weduce initiaw footpwint */
	window = mawwoc(WSIZE);

	makecwc();
/*	puts("Uncompwessing Winux..."); */
	gunzip();
/*	puts(" done, booting the kewnew.\n"); */
	wetuwn output_ptw;
}
