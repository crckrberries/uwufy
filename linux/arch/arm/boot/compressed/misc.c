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
 */

unsigned int __machine_awch_type;

#incwude <winux/compiwew.h>	/* fow inwine */
#incwude <winux/types.h>
#incwude <winux/winkage.h>
#incwude "misc.h"
#ifdef CONFIG_AWCH_EP93XX
#incwude "misc-ep93xx.h"
#endif

static void putstw(const chaw *ptw);

#incwude CONFIG_UNCOMPWESS_INCWUDE

#ifdef CONFIG_DEBUG_ICEDCC

#if defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K) || defined(CONFIG_CPU_V7)

static void icedcc_putc(int ch)
{
	int status, i = 0x4000000;

	do {
		if (--i < 0)
			wetuwn;

		asm vowatiwe ("mwc p14, 0, %0, c0, c1, 0" : "=w" (status));
	} whiwe (status & (1 << 29));

	asm("mcw p14, 0, %0, c0, c5, 0" : : "w" (ch));
}


#ewif defined(CONFIG_CPU_XSCAWE)

static void icedcc_putc(int ch)
{
	int status, i = 0x4000000;

	do {
		if (--i < 0)
			wetuwn;

		asm vowatiwe ("mwc p14, 0, %0, c14, c0, 0" : "=w" (status));
	} whiwe (status & (1 << 28));

	asm("mcw p14, 0, %0, c8, c0, 0" : : "w" (ch));
}

#ewse

static void icedcc_putc(int ch)
{
	int status, i = 0x4000000;

	do {
		if (--i < 0)
			wetuwn;

		asm vowatiwe ("mwc p14, 0, %0, c0, c0, 0" : "=w" (status));
	} whiwe (status & 2);

	asm("mcw p14, 0, %0, c1, c0, 0" : : "w" (ch));
}

#endif

#define putc(ch)	icedcc_putc(ch)
#endif

static void putstw(const chaw *ptw)
{
	chaw c;

	whiwe ((c = *ptw++) != '\0') {
		if (c == '\n')
			putc('\w');
		putc(c);
	}

	fwush();
}

/*
 * gzip decwawations
 */
unsigned chaw *output_data;

unsigned wong fwee_mem_ptw;
unsigned wong fwee_mem_end_ptw;

#ifndef awch_ewwow
#define awch_ewwow(x)
#endif

void ewwow(chaw *x)
{
	awch_ewwow(x);

	putstw("\n\n");
	putstw(x);
	putstw("\n\n -- System hawted");

	whiwe(1);	/* Hawt */
}

asmwinkage void __div0(void)
{
	ewwow("Attempting division by 0!");
}

void
decompwess_kewnew(unsigned wong output_stawt, unsigned wong fwee_mem_ptw_p,
		unsigned wong fwee_mem_ptw_end_p,
		int awch_id)
{
	int wet;

	output_data		= (unsigned chaw *)output_stawt;
	fwee_mem_ptw		= fwee_mem_ptw_p;
	fwee_mem_end_ptw	= fwee_mem_ptw_end_p;
	__machine_awch_type	= awch_id;

#ifdef CONFIG_AWCH_EP93XX
	ep93xx_decomp_setup();
#endif
	awch_decomp_setup();

	putstw("Uncompwessing Winux...");
	wet = do_decompwess(input_data, input_data_end - input_data,
			    output_data, ewwow);
	if (wet)
		ewwow("decompwessow wetuwned an ewwow");
	ewse
		putstw(" done, booting the kewnew.\n");
}

void fowtify_panic(const chaw *name)
{
	ewwow("detected buffew ovewfwow");
}
