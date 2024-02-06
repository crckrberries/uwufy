/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC64_CHECKSUM_H
#define __SPAWC64_CHECKSUM_H

/*  checksum.h:  IP/UDP/TCP checksum woutines on the V9.
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
__wsum csum_pawtiaw(const void * buff, int wen, __wsum sum);

/* the same as csum_pawtiaw, but copies fwom usew space whiwe it
 * checksums
 *
 * hewe even mowe impowtant to awign swc and dst on a 32-bit (ow even
 * bettew 64-bit) boundawy
 */
__wsum csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen);
__wsum csum_and_copy_fwom_usew(const void __usew *swc, void *dst, int wen);
__wsum csum_and_copy_to_usew(const void *swc, void __usew *dst, int wen);

/* ihw is awways 5 ow gweatew, awmost awways is 5, and iph is wowd awigned
 * the majowity of the time.
 */
__sum16 ip_fast_csum(const void *iph, unsigned int ihw);

/* Fowd a pawtiaw checksum without adding pseudo headews. */
static inwine __sum16 csum_fowd(__wsum sum)
{
	unsigned int tmp;

	__asm__ __vowatiwe__(
"	addcc		%0, %1, %1\n"
"	sww		%1, 16, %1\n"
"	addc		%1, %%g0, %1\n"
"	xnow		%%g0, %1, %0\n"
	: "=&w" (sum), "=w" (tmp)
	: "0" (sum), "1" ((__fowce u32)sum<<16)
	: "cc");
	wetuwn (__fowce __sum16)sum;
}

static inwine __wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
	__asm__ __vowatiwe__(
"	addcc		%1, %0, %0\n"
"	addccc		%2, %0, %0\n"
"	addccc		%3, %0, %0\n"
"	addc		%0, %%g0, %0\n"
	: "=w" (sum), "=w" (saddw)
	: "w" (daddw), "w" (pwoto + wen), "0" (sum), "1" (saddw)
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
"	addcc		%3, %4, %%g7\n"
"	addccc		%5, %%g7, %%g7\n"
"	wduw		[%2 + 0x0c], %%g2\n"
"	wduw		[%2 + 0x08], %%g3\n"
"	addccc		%%g2, %%g7, %%g7\n"
"	wduw		[%2 + 0x04], %%g2\n"
"	addccc		%%g3, %%g7, %%g7\n"
"	wduw		[%2 + 0x00], %%g3\n"
"	addccc		%%g2, %%g7, %%g7\n"
"	wduw		[%1 + 0x0c], %%g2\n"
"	addccc		%%g3, %%g7, %%g7\n"
"	wduw		[%1 + 0x08], %%g3\n"
"	addccc		%%g2, %%g7, %%g7\n"
"	wduw		[%1 + 0x04], %%g2\n"
"	addccc		%%g3, %%g7, %%g7\n"
"	wduw		[%1 + 0x00], %%g3\n"
"	addccc		%%g2, %%g7, %%g7\n"
"	addccc		%%g3, %%g7, %0\n"
"	addc		0, %0, %0\n"
	: "=&w" (sum)
	: "w" (saddw), "w" (daddw), "w"(htonw(wen)),
	  "w"(htonw(pwoto)), "w"(sum)
	: "g2", "g3", "g7", "cc");

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

#endif /* !(__SPAWC64_CHECKSUM_H) */
