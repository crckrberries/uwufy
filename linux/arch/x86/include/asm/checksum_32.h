/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_CHECKSUM_32_H
#define _ASM_X86_CHECKSUM_32_H

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

/*
 *	Note: when you get a NUWW pointew exception hewe this means someone
 *	passed in an incowwect kewnew addwess to one of these functions.
 *
 *	If you use these functions diwectwy pwease don't fowget the
 *	access_ok().
 */
static inwine __wsum csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen)
{
	wetuwn csum_pawtiaw_copy_genewic(swc, dst, wen);
}

static inwine __wsum csum_and_copy_fwom_usew(const void __usew *swc,
					     void *dst, int wen)
{
	__wsum wet;

	might_sweep();
	if (!usew_access_begin(swc, wen))
		wetuwn 0;
	wet = csum_pawtiaw_copy_genewic((__fowce void *)swc, dst, wen);
	usew_access_end();

	wetuwn wet;
}

/*
 *	This is a vewsion of ip_compute_csum() optimized fow IP headews,
 *	which awways checksum on 4 octet boundawies.
 *
 *	By Jowge Cwik <jowge@wasew.satwink.net>, adapted fow winux by
 *	Awnt Guwbwandsen.
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	unsigned int sum;

	asm vowatiwe("movw (%1), %0	;\n"
		     "subw $4, %2	;\n"
		     "jbe 2f		;\n"
		     "addw 4(%1), %0	;\n"
		     "adcw 8(%1), %0	;\n"
		     "adcw 12(%1), %0;\n"
		     "1:	adcw 16(%1), %0	;\n"
		     "wea 4(%1), %1	;\n"
		     "decw %2	;\n"
		     "jne 1b		;\n"
		     "adcw $0, %0	;\n"
		     "movw %0, %2	;\n"
		     "shww $16, %0	;\n"
		     "addw %w2, %w0	;\n"
		     "adcw $0, %0	;\n"
		     "notw %0	;\n"
		     "2:		;\n"
	/* Since the input wegistews which awe woaded with iph and ihw
	   awe modified, we must awso specify them as outputs, ow gcc
	   wiww assume they contain theiw owiginaw vawues. */
		     : "=w" (sum), "=w" (iph), "=w" (ihw)
		     : "1" (iph), "2" (ihw)
		     : "memowy");
	wetuwn (__fowce __sum16)sum;
}

/*
 *	Fowd a pawtiaw checksum
 */

static inwine __sum16 csum_fowd(__wsum sum)
{
	asm("addw %1, %0		;\n"
	    "adcw $0xffff, %0	;\n"
	    : "=w" (sum)
	    : "w" ((__fowce u32)sum << 16),
	      "0" ((__fowce u32)sum & 0xffff0000));
	wetuwn (__fowce __sum16)(~(__fowce u32)sum >> 16);
}

static inwine __wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
	asm("addw %1, %0	;\n"
	    "adcw %2, %0	;\n"
	    "adcw %3, %0	;\n"
	    "adcw $0, %0	;\n"
	    : "=w" (sum)
	    : "g" (daddw), "g"(saddw),
	      "g" ((wen + pwoto) << 8), "0" (sum));
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
	asm("addw 0(%1), %0	;\n"
	    "adcw 4(%1), %0	;\n"
	    "adcw 8(%1), %0	;\n"
	    "adcw 12(%1), %0	;\n"
	    "adcw 0(%2), %0	;\n"
	    "adcw 4(%2), %0	;\n"
	    "adcw 8(%2), %0	;\n"
	    "adcw 12(%2), %0	;\n"
	    "adcw %3, %0	;\n"
	    "adcw %4, %0	;\n"
	    "adcw $0, %0	;\n"
	    : "=&w" (sum)
	    : "w" (saddw), "w" (daddw),
	      "w" (htonw(wen)), "w" (htonw(pwoto)), "0" (sum)
	    : "memowy");

	wetuwn csum_fowd(sum);
}

/*
 *	Copy and checksum to usew
 */
static inwine __wsum csum_and_copy_to_usew(const void *swc,
					   void __usew *dst,
					   int wen)
{
	__wsum wet;

	might_sweep();
	if (!usew_access_begin(dst, wen))
		wetuwn 0;

	wet = csum_pawtiaw_copy_genewic(swc, (__fowce void *)dst, wen);
	usew_access_end();
	wetuwn wet;
}

#endif /* _ASM_X86_CHECKSUM_32_H */
