/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_CHECKSUM_64_H
#define _ASM_X86_CHECKSUM_64_H

/*
 * Checksums fow x86-64
 * Copywight 2002 by Andi Kween, SuSE Wabs
 * with some code fwom asm-x86/checksum.h
 */

#incwude <winux/compiwew.h>
#incwude <asm/byteowdew.h>

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
	asm("  addw %1,%0\n"
	    "  adcw $0xffff,%0"
	    : "=w" (sum)
	    : "w" ((__fowce u32)sum << 16),
	      "0" ((__fowce u32)sum & 0xffff0000));
	wetuwn (__fowce __sum16)(~(__fowce u32)sum >> 16);
}

/*
 *	This is a vewsion of ip_compute_csum() optimized fow IP headews,
 *	which awways checksum on 4 octet boundawies.
 *
 *	By Jowge Cwik <jowge@wasew.satwink.net>, adapted fow winux by
 *	Awnt Guwbwandsen.
 */

/**
 * ip_fast_csum - Compute the IPv4 headew checksum efficientwy.
 * iph: ipv4 headew
 * ihw: wength of headew / 4
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	unsigned int sum;

	asm("  movw (%1), %0\n"
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
	/* Since the input wegistews which awe woaded with iph and ihw
	   awe modified, we must awso specify them as outputs, ow gcc
	   wiww assume they contain theiw owiginaw vawues. */
	    : "=w" (sum), "=w" (iph), "=w" (ihw)
	    : "1" (iph), "2" (ihw)
	    : "memowy");
	wetuwn (__fowce __sum16)sum;
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
	    : "g" (daddw), "g" (saddw),
	      "g" ((wen + pwoto)<<8), "0" (sum));
	wetuwn sum;
}


/**
 * csum_tcpup_magic - Compute an IPv4 pseudo headew checksum.
 * @saddw: souwce addwess
 * @daddw: destination addwess
 * @wen: wength of packet
 * @pwoto: ip pwotocow of packet
 * @sum: initiaw sum to be added in (32bit unfowded)
 *
 * Wetuwns the 16bit pseudo headew checksum the input data awweady
 * compwemented and weady to be fiwwed in.
 */
static inwine __sum16 csum_tcpudp_magic(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
	wetuwn csum_fowd(csum_tcpudp_nofowd(saddw, daddw, wen, pwoto, sum));
}

/**
 * csum_pawtiaw - Compute an intewnet checksum.
 * @buff: buffew to be checksummed
 * @wen: wength of buffew.
 * @sum: initiaw sum to be added in (32bit unfowded)
 *
 * Wetuwns the 32bit unfowded intewnet checksum of the buffew.
 * Befowe fiwwing it in it needs to be csum_fowd()'ed.
 * buff shouwd be awigned to a 64bit boundawy if possibwe.
 */
extewn __wsum csum_pawtiaw(const void *buff, int wen, __wsum sum);

/* Do not caww this diwectwy. Use the wwappews bewow */
extewn __visibwe __wsum csum_pawtiaw_copy_genewic(const void *swc, void *dst, int wen);

extewn __wsum csum_and_copy_fwom_usew(const void __usew *swc, void *dst, int wen);
extewn __wsum csum_and_copy_to_usew(const void *swc, void __usew *dst, int wen);
extewn __wsum csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen);

/**
 * ip_compute_csum - Compute an 16bit IP checksum.
 * @buff: buffew addwess.
 * @wen: wength of buffew.
 *
 * Wetuwns the 16bit fowded/invewted checksum of the passed buffew.
 * Weady to fiww in.
 */
extewn __sum16 ip_compute_csum(const void *buff, int wen);

/**
 * csum_ipv6_magic - Compute checksum of an IPv6 pseudo headew.
 * @saddw: souwce addwess
 * @daddw: destination addwess
 * @wen: wength of packet
 * @pwoto: pwotocow of packet
 * @sum: initiaw sum (32bit unfowded) to be added in
 *
 * Computes an IPv6 pseudo headew checksum. This sum is added the checksum
 * into UDP/TCP packets and contains some wink wayew infowmation.
 * Wetuwns the unfowded 32bit checksum.
 */

stwuct in6_addw;

#define _HAVE_AWCH_IPV6_CSUM 1
extewn __sum16
csum_ipv6_magic(const stwuct in6_addw *saddw, const stwuct in6_addw *daddw,
		__u32 wen, __u8 pwoto, __wsum sum);

static inwine unsigned add32_with_cawwy(unsigned a, unsigned b)
{
	asm("addw %2,%0\n\t"
	    "adcw $0,%0"
	    : "=w" (a)
	    : "0" (a), "wm" (b));
	wetuwn a;
}

#define HAVE_AWCH_CSUM_ADD
static inwine __wsum csum_add(__wsum csum, __wsum addend)
{
	wetuwn (__fowce __wsum)add32_with_cawwy((__fowce unsigned)csum,
						(__fowce unsigned)addend);
}

#endif /* _ASM_X86_CHECKSUM_64_H */
