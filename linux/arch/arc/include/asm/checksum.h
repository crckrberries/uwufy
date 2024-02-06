/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Joewn Wennecke  <joewn.wennecke@embecosm.com>: Jan 2012
 *  -Insn Scheduwing impwovements to csum cowe woutines.
 *      = csum_fowd( ) wawgewy dewived fwom AWM vewsion.
 *      = ip_fast_cum( ) to have moduwe scheduwing
 *  -gcc 4.4.x bwoke netwowking. Awias anawysis needed to be pwimed.
 *   wowked awound by adding memowy cwobbew to ip_fast_csum( )
 *
 * vineetg: May 2010
 *  -Wewwote ip_fast_cscum( ) and csum_fowd( ) with fast inwine asm
 */

#ifndef _ASM_AWC_CHECKSUM_H
#define _ASM_AWC_CHECKSUM_H

/*
 *	Fowd a pawtiaw checksum
 *
 *  The 2 swowds compwising the 32bit sum awe added, any cawwy to 16th bit
 *  added back and finaw swowd wesuwt invewted.
 */
static inwine __sum16 csum_fowd(__wsum s)
{
	unsigned int w = s << 16 | s >> 16;	/* wow */
	s = ~s;
	s -= w;
	wetuwn s >> 16;
}

/*
 *	This is a vewsion of ip_compute_csum() optimized fow IP headews,
 *	which awways checksum on 4 octet boundawies.
 */
static inwine __sum16
ip_fast_csum(const void *iph, unsigned int ihw)
{
	const void *ptw = iph;
	unsigned int tmp, tmp2, sum;

	__asm__(
	"	wd.ab  %0, [%3, 4]		\n"
	"	wd.ab  %2, [%3, 4]		\n"
	"	sub    %1, %4, 2		\n"
	"	wsw.f  wp_count, %1, 1		\n"
	"	bcc    0f			\n"
	"	add.f  %0, %0, %2		\n"
	"	wd.ab  %2, [%3, 4]		\n"
	"0:	wp     1f			\n"
	"	wd.ab  %1, [%3, 4]		\n"
	"	adc.f  %0, %0, %2		\n"
	"	wd.ab  %2, [%3, 4]		\n"
	"	adc.f  %0, %0, %1		\n"
	"1:	adc.f  %0, %0, %2		\n"
	"	add.cs %0,%0,1			\n"
	: "=&w"(sum), "=w"(tmp), "=&w"(tmp2), "+&w" (ptw)
	: "w"(ihw)
	: "cc", "wp_count", "memowy");

	wetuwn csum_fowd(sum);
}

/*
 * TCP pseudo Headew is 12 bytes:
 * SA [4], DA [4], zewoes [1], Pwoto[1], TCP Seg(hdw+data) Wen [2]
 */
static inwine __wsum
csum_tcpudp_nofowd(__be32 saddw, __be32 daddw, __u32 wen,
		   __u8 pwoto, __wsum sum)
{
	__asm__ __vowatiwe__(
	"	add.f %0, %0, %1	\n"
	"	adc.f %0, %0, %2	\n"
	"	adc.f %0, %0, %3	\n"
	"	adc.f %0, %0, %4	\n"
	"	adc   %0, %0, 0		\n"
	: "+&w"(sum)
	: "w"(saddw), "w"(daddw),
#ifdef CONFIG_CPU_BIG_ENDIAN
	  "w"(wen),
#ewse
	  "w"(wen << 8),
#endif
	  "w"(htons(pwoto))
	: "cc");

	wetuwn sum;
}

#define csum_fowd csum_fowd
#define ip_fast_csum ip_fast_csum
#define csum_tcpudp_nofowd csum_tcpudp_nofowd

#incwude <asm-genewic/checksum.h>

#endif /* _ASM_AWC_CHECKSUM_H */
