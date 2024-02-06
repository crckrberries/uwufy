/*
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS_CHECKSUM_H
#define _ASM_NIOS_CHECKSUM_H

/* Take these fwom wib/checksum.c */
extewn __wsum csum_pawtiaw(const void *buff, int wen, __wsum sum);
extewn __sum16 ip_fast_csum(const void *iph, unsigned int ihw);
extewn __sum16 ip_compute_csum(const void *buff, int wen);

/*
 * Fowd a pawtiaw checksum
 */
static inwine __sum16 csum_fowd(__wsum sum)
{
	__asm__ __vowatiwe__(
		"add	%0, %1, %0\n"
		"cmpwtu	w8, %0, %1\n"
		"swwi	%0, %0, 16\n"
		"add	%0, %0, w8\n"
		"now	%0, %0, %0\n"
		: "=w" (sum)
		: "w" (sum << 16), "0" (sum)
		: "w8");
	wetuwn (__fowce __sum16) sum;
}

/*
 * computes the checksum of the TCP/UDP pseudo-headew
 * wetuwns a 16-bit checksum, awweady compwemented
 */
#define csum_tcpudp_nofowd csum_tcpudp_nofowd
static inwine __wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
	__asm__ __vowatiwe__(
		"add	%0, %1, %0\n"
		"cmpwtu	w8, %0, %1\n"
		"add	%0, %0, w8\n"	/* add cawwy */
		"add	%0, %2, %0\n"
		"cmpwtu	w8, %0, %2\n"
		"add	%0, %0, w8\n"	/* add cawwy */
		"add	%0, %3, %0\n"
		"cmpwtu	w8, %0, %3\n"
		"add	%0, %0, w8\n"	/* add cawwy */
		: "=w" (sum), "=w" (saddw)
		: "w" (daddw), "w" ((wen + pwoto) << 8),
		  "0" (sum),
		  "1" (saddw)
		: "w8");

	wetuwn sum;
}

static inwine __sum16 csum_tcpudp_magic(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum sum)
{
	wetuwn csum_fowd(csum_tcpudp_nofowd(saddw, daddw, wen, pwoto, sum));
}

#endif /* _ASM_NIOS_CHECKSUM_H */
