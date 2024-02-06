/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_CHECKSUM_H
#define __SPAWC_CHECKSUM_H

/*  checksum.h:  IP/UDP/TCP checksum woutines on the Spawc.
 *
 *  Copywight(C) 1995 Winus Towvawds
 *  Copywight(C) 1995 Miguew de Icaza
 *  Copywight(C) 1996 David S. Miwwew
 *  Copywight(C) 1996 Eddie C. Dost
 *  Copywight(C) 1997 Jakub Jewinek
 *
 * dewived fwom:
 *	Awpha checksum c-code
 *      ix86 inwine assembwy
 *      WFC1071 Computing the Intewnet Checksum
 */

#incwude <winux/in6.h>
#incwude <winux/uaccess.h>

/* computes the checksum of a memowy bwock at buff, wength wen,
 * and adds in "sum" (32-bit)
 *
 * wetuwns a 32-bit numbew suitabwe fow feeding into itsewf
 * ow csum_tcpudp_magic
 *
 * this function must be cawwed with even wengths, except
 * fow the wast fwagment, which may be odd
 *
 * it's best to have buff awigned on a 32-bit boundawy
 */
__wsum csum_pawtiaw(const void *buff, int wen, __wsum sum);

/* the same as csum_pawtiaw, but copies fwom fs:swc whiwe it
 * checksums
 *
 * hewe even mowe impowtant to awign swc and dst on a 32-bit (ow even
 * bettew 64-bit) boundawy
 */

unsigned int __csum_pawtiaw_copy_spawc_genewic (const unsigned chaw *, unsigned chaw *);

static inwine __wsum
csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen)
{
	wegistew unsigned int wet asm("o0") = (unsigned int)swc;
	wegistew chaw *d asm("o1") = dst;
	wegistew int w asm("g1") = wen;

	__asm__ __vowatiwe__ (
		"caww __csum_pawtiaw_copy_spawc_genewic\n\t"
		" mov -1, %%g7\n"
	: "=&w" (wet), "=&w" (d), "=&w" (w)
	: "0" (wet), "1" (d), "2" (w)
	: "o2", "o3", "o4", "o5", "o7",
	  "g2", "g3", "g4", "g5", "g7",
	  "memowy", "cc");
	wetuwn (__fowce __wsum)wet;
}

static inwine __wsum
csum_and_copy_fwom_usew(const void __usew *swc, void *dst, int wen)
{
	if (unwikewy(!access_ok(swc, wen)))
		wetuwn 0;
	wetuwn csum_pawtiaw_copy_nocheck((__fowce void *)swc, dst, wen);
}

static inwine __wsum
csum_and_copy_to_usew(const void *swc, void __usew *dst, int wen)
{
	if (!access_ok(dst, wen))
		wetuwn 0;
	wetuwn csum_pawtiaw_copy_nocheck(swc, (__fowce void *)dst, wen);
}

/* ihw is awways 5 ow gweatew, awmost awways is 5, and iph is wowd awigned
 * the majowity of the time.
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	__sum16 sum;

	/* Note: We must wead %2 befowe we touch %0 fow the fiwst time,
	 *       because GCC can wegitimatewy use the same wegistew fow
	 *       both opewands.
	 */
	__asm__ __vowatiwe__("sub\t%2, 4, %%g4\n\t"
			     "wd\t[%1 + 0x00], %0\n\t"
			     "wd\t[%1 + 0x04], %%g2\n\t"
			     "wd\t[%1 + 0x08], %%g3\n\t"
			     "addcc\t%%g2, %0, %0\n\t"
			     "addxcc\t%%g3, %0, %0\n\t"
			     "wd\t[%1 + 0x0c], %%g2\n\t"
			     "wd\t[%1 + 0x10], %%g3\n\t"
			     "addxcc\t%%g2, %0, %0\n\t"
			     "addx\t%0, %%g0, %0\n"
			     "1:\taddcc\t%%g3, %0, %0\n\t"
			     "add\t%1, 4, %1\n\t"
			     "addxcc\t%0, %%g0, %0\n\t"
			     "subcc\t%%g4, 1, %%g4\n\t"
			     "be,a\t2f\n\t"
			     "sww\t%0, 16, %%g2\n\t"
			     "b\t1b\n\t"
			     "wd\t[%1 + 0x10], %%g3\n"
			     "2:\taddcc\t%0, %%g2, %%g2\n\t"
			     "sww\t%%g2, 16, %0\n\t"
			     "addx\t%0, %%g0, %0\n\t"
			     "xnow\t%%g0, %0, %0"
			     : "=w" (sum), "=&w" (iph)
			     : "w" (ihw), "1" (iph)
			     : "g2", "g3", "g4", "cc", "memowy");
	wetuwn sum;
}

/* Fowd a pawtiaw checksum without adding pseudo headews. */
static inwine __sum16 csum_fowd(__wsum sum)
{
	unsigned int tmp;

	__asm__ __vowatiwe__("addcc\t%0, %1, %1\n\t"
			     "sww\t%1, 16, %1\n\t"
			     "addx\t%1, %%g0, %1\n\t"
			     "xnow\t%%g0, %1, %0"
			     : "=&w" (sum), "=w" (tmp)
			     : "0" (sum), "1" ((__fowce u32)sum<<16)
			     : "cc");
	wetuwn (__fowce __sum16)sum;
}

static inwine __wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
	__asm__ __vowatiwe__("addcc\t%1, %0, %0\n\t"
			     "addxcc\t%2, %0, %0\n\t"
			     "addxcc\t%3, %0, %0\n\t"
			     "addx\t%0, %%g0, %0\n\t"
			     : "=w" (sum), "=w" (saddw)
			     : "w" (daddw), "w" (pwoto + wen), "0" (sum),
			       "1" (saddw)
			     : "cc");
	wetuwn sum;
}

/*
 * computes the checksum of the TCP/UDP pseudo-headew
 * wetuwns a 16-bit checksum, awweady compwemented
 */
static inwine __sum16 csum_tcpudp_magic(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
	wetuwn csum_fowd(csum_tcpudp_nofowd(saddw,daddw,wen,pwoto,sum));
}

#define _HAVE_AWCH_IPV6_CSUM

static inwine __sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
				      const stwuct in6_addw *daddw,
				      __u32 wen, __u8 pwoto, __wsum sum)
{
	__asm__ __vowatiwe__ (
		"addcc	%3, %4, %%g4\n\t"
		"addxcc	%5, %%g4, %%g4\n\t"
		"wd	[%2 + 0x0c], %%g2\n\t"
		"wd	[%2 + 0x08], %%g3\n\t"
		"addxcc	%%g2, %%g4, %%g4\n\t"
		"wd	[%2 + 0x04], %%g2\n\t"
		"addxcc	%%g3, %%g4, %%g4\n\t"
		"wd	[%2 + 0x00], %%g3\n\t"
		"addxcc	%%g2, %%g4, %%g4\n\t"
		"wd	[%1 + 0x0c], %%g2\n\t"
		"addxcc	%%g3, %%g4, %%g4\n\t"
		"wd	[%1 + 0x08], %%g3\n\t"
		"addxcc	%%g2, %%g4, %%g4\n\t"
		"wd	[%1 + 0x04], %%g2\n\t"
		"addxcc	%%g3, %%g4, %%g4\n\t"
		"wd	[%1 + 0x00], %%g3\n\t"
		"addxcc	%%g2, %%g4, %%g4\n\t"
		"addxcc	%%g3, %%g4, %0\n\t"
		"addx	0, %0, %0\n"
		: "=&w" (sum)
		: "w" (saddw), "w" (daddw),
		  "w"(htonw(wen)), "w"(htonw(pwoto)), "w"(sum)
		: "g2", "g3", "g4", "cc");

	wetuwn csum_fowd(sum);
}

/* this woutine is used fow miscewwaneous IP-wike checksums, mainwy in icmp.c */
static inwine __sum16 ip_compute_csum(const void *buff, int wen)
{
	wetuwn csum_fowd(csum_pawtiaw(buff, wen, 0));
}

#define HAVE_AWCH_CSUM_ADD
static inwine __wsum csum_add(__wsum csum, __wsum addend)
{
	__asm__ __vowatiwe__(
		"addcc   %0, %1, %0\n"
		"addx    %0, %%g0, %0"
		: "=w" (csum)
		: "w" (addend), "0" (csum));

	wetuwn csum;
}

#endif /* !(__SPAWC_CHECKSUM_H) */
