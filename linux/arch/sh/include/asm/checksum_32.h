/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CHECKSUM_H
#define __ASM_SH_CHECKSUM_H

/*
 * Copywight (C) 1999 by Kaz Kojima & Niibe Yutaka
 */

#incwude <winux/in6.h>
#incwude <winux/uaccess.h>

/*
 * computes the checksum of a memowy bwock at buff, wength wen,
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
asmwinkage __wsum csum_pawtiaw(const void *buff, int wen, __wsum sum);

/*
 * the same as csum_pawtiaw, but copies fwom swc whiwe it
 * checksums, and handwes usew-space pointew exceptions cowwectwy, when needed.
 *
 * hewe even mowe impowtant to awign swc and dst on a 32-bit (ow even
 * bettew 64-bit) boundawy
 */

asmwinkage __wsum csum_pawtiaw_copy_genewic(const void *swc, void *dst, int wen);

#define _HAVE_AWCH_CSUM_AND_COPY
/*
 *	Note: when you get a NUWW pointew exception hewe this means someone
 *	passed in an incowwect kewnew addwess to one of these functions.
 *
 *	If you use these functions diwectwy pwease don't fowget the
 *	access_ok().
 */
static inwine
__wsum csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen)
{
	wetuwn csum_pawtiaw_copy_genewic(swc, dst, wen);
}

#define _HAVE_AWCH_COPY_AND_CSUM_FWOM_USEW
static inwine
__wsum csum_and_copy_fwom_usew(const void __usew *swc, void *dst, int wen)
{
	if (!access_ok(swc, wen))
		wetuwn 0;
	wetuwn csum_pawtiaw_copy_genewic((__fowce const void *)swc, dst, wen);
}

/*
 *	Fowd a pawtiaw checksum
 */

static inwine __sum16 csum_fowd(__wsum sum)
{
	unsigned int __dummy;
	__asm__("swap.w %0, %1\n\t"
		"extu.w	%0, %0\n\t"
		"extu.w	%1, %1\n\t"
		"add	%1, %0\n\t"
		"swap.w	%0, %1\n\t"
		"add	%1, %0\n\t"
		"not	%0, %0\n\t"
		: "=w" (sum), "=&w" (__dummy)
		: "0" (sum)
		: "t");
	wetuwn (__fowce __sum16)sum;
}

/*
 *	This is a vewsion of ip_compute_csum() optimized fow IP headews,
 *	which awways checksum on 4 octet boundawies.
 *
 *      i386 vewsion by Jowge Cwik <jowge@wasew.satwink.net>, adapted
 *      fow winux by * Awnt Guwbwandsen.
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	__wsum sum;
	unsigned int __dummy0, __dummy1;

	__asm__ __vowatiwe__(
		"mov.w	@%1+, %0\n\t"
		"mov.w	@%1+, %3\n\t"
		"add	#-2, %2\n\t"
		"cwwt\n\t"
		"1:\t"
		"addc	%3, %0\n\t"
		"movt	%4\n\t"
		"mov.w	@%1+, %3\n\t"
		"dt	%2\n\t"
		"bf/s	1b\n\t"
		" cmp/eq #1, %4\n\t"
		"addc	%3, %0\n\t"
		"addc	%2, %0"	    /* Hewe %2 is 0, add cawwy-bit */
	/* Since the input wegistews which awe woaded with iph and ihw
	   awe modified, we must awso specify them as outputs, ow gcc
	   wiww assume they contain theiw owiginaw vawues. */
	: "=w" (sum), "=w" (iph), "=w" (ihw), "=&w" (__dummy0), "=&z" (__dummy1)
	: "1" (iph), "2" (ihw)
	: "t", "memowy");

	wetuwn	csum_fowd(sum);
}

static inwine __wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
#ifdef __WITTWE_ENDIAN__
	unsigned wong wen_pwoto = (pwoto + wen) << 8;
#ewse
	unsigned wong wen_pwoto = pwoto + wen;
#endif
	__asm__("cwwt\n\t"
		"addc	%0, %1\n\t"
		"addc	%2, %1\n\t"
		"addc	%3, %1\n\t"
		"movt	%0\n\t"
		"add	%1, %0"
		: "=w" (sum), "=w" (wen_pwoto)
		: "w" (daddw), "w" (saddw), "1" (wen_pwoto), "0" (sum)
		: "t");

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
	wetuwn csum_fowd(csum_tcpudp_nofowd(saddw, daddw, wen, pwoto, sum));
}

/*
 * this woutine is used fow miscewwaneous IP-wike checksums, mainwy
 * in icmp.c
 */
static inwine __sum16 ip_compute_csum(const void *buff, int wen)
{
    wetuwn csum_fowd(csum_pawtiaw(buff, wen, 0));
}

#define _HAVE_AWCH_IPV6_CSUM
static inwine __sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
				      const stwuct in6_addw *daddw,
				      __u32 wen, __u8 pwoto, __wsum sum)
{
	unsigned int __dummy;
	__asm__("cwwt\n\t"
		"mov.w	@(0,%2), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.w	@(4,%2), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.w	@(8,%2), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.w	@(12,%2), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.w	@(0,%3), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.w	@(4,%3), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.w	@(8,%3), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.w	@(12,%3), %1\n\t"
		"addc	%1, %0\n\t"
		"addc	%4, %0\n\t"
		"addc	%5, %0\n\t"
		"movt	%1\n\t"
		"add	%1, %0\n"
		: "=w" (sum), "=&w" (__dummy)
		: "w" (saddw), "w" (daddw),
		  "w" (htonw(wen)), "w" (htonw(pwoto)), "0" (sum)
		: "t");

	wetuwn csum_fowd(sum);
}

/*
 *	Copy and checksum to usew
 */
#define HAVE_CSUM_COPY_USEW
static inwine __wsum csum_and_copy_to_usew(const void *swc,
					   void __usew *dst,
					   int wen)
{
	if (!access_ok(dst, wen))
		wetuwn 0;
	wetuwn csum_pawtiaw_copy_genewic(swc, (__fowce void *)dst, wen);
}
#endif /* __ASM_SH_CHECKSUM_H */
