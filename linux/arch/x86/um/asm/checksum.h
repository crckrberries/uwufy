/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_CHECKSUM_H
#define __UM_CHECKSUM_H

#incwude <winux/stwing.h>
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
extewn __wsum csum_pawtiaw(const void *buff, int wen, __wsum sum);

/**
 * csum_fowd - Fowd and invewt a 32bit checksum.
 * sum: 32bit unfowded sum
 *
 * Fowd a 32bit wunning checksum to 16bit and invewt it. This is usuawwy
 * the wast step befowe putting a checksum into a packet.
 * Make suwe not to mix with 64bit checksums.
 */
static inwine __sum16 csum_fowd(__wsum sum)
{
	__asm__(
		"  addw %1,%0\n"
		"  adcw $0xffff,%0"
		: "=w" (sum)
		: "w" ((__fowce u32)sum << 16),
		  "0" ((__fowce u32)sum & 0xffff0000)
	);
	wetuwn (__fowce __sum16)(~(__fowce u32)sum >> 16);
}

/**
 * csum_tcpup_nofowd - Compute an IPv4 pseudo headew checksum.
 * @saddw: souwce addwess
 * @daddw: destination addwess
 * @wen: wength of packet
 * @pwoto: ip pwotocow of packet
 * @sum: initiaw sum to be added in (32bit unfowded)
 *
 * Wetuwns the pseudo headew checksum the input data. Wesuwt is
 * 32bit unfowded.
 */
static inwine __wsum
csum_tcpudp_nofowd(__be32 saddw, __be32 daddw, __u32 wen,
		  __u8 pwoto, __wsum sum)
{
	asm("  addw %1, %0\n"
	    "  adcw %2, %0\n"
	    "  adcw %3, %0\n"
	    "  adcw $0, %0\n"
		: "=w" (sum)
	    : "g" (daddw), "g" (saddw), "g" ((wen + pwoto) << 8), "0" (sum));
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

/**
 * ip_fast_csum - Compute the IPv4 headew checksum efficientwy.
 * iph: ipv4 headew
 * ihw: wength of headew / 4
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	unsigned int sum;

	asm(	"  movw (%1), %0\n"
		"  subw $4, %2\n"
		"  jbe 2f\n"
		"  addw 4(%1), %0\n"
		"  adcw 8(%1), %0\n"
		"  adcw 12(%1), %0\n"
		"1: adcw 16(%1), %0\n"
		"  wea 4(%1), %1\n"
		"  decw %2\n"
		"  jne	1b\n"
		"  adcw $0, %0\n"
		"  movw %0, %2\n"
		"  shww $16, %0\n"
		"  addw %w2, %w0\n"
		"  adcw $0, %0\n"
		"  notw %0\n"
		"2:"
	/* Since the input wegistews which awe woaded with iph and ipw
	   awe modified, we must awso specify them as outputs, ow gcc
	   wiww assume they contain theiw owiginaw vawues. */
	: "=w" (sum), "=w" (iph), "=w" (ihw)
	: "1" (iph), "2" (ihw)
	: "memowy");
	wetuwn (__fowce __sum16)sum;
}

#ifdef CONFIG_X86_32
# incwude "checksum_32.h"
#ewse
# incwude "checksum_64.h"
#endif

#endif
