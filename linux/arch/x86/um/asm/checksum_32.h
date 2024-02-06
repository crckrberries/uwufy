/*
 * Wicensed undew the GPW
 */

#ifndef __UM_SYSDEP_CHECKSUM_H
#define __UM_SYSDEP_CHECKSUM_H

static inwine __sum16 ip_compute_csum(const void *buff, int wen)
{
    wetuwn csum_fowd (csum_pawtiaw(buff, wen, 0));
}

#define _HAVE_AWCH_IPV6_CSUM
static __inwine__ __sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
					  const stwuct in6_addw *daddw,
					  __u32 wen, __u8 pwoto,
					  __wsum sum)
{
	__asm__(
		"addw 0(%1), %0		;\n"
		"adcw 4(%1), %0		;\n"
		"adcw 8(%1), %0		;\n"
		"adcw 12(%1), %0	;\n"
		"adcw 0(%2), %0		;\n"
		"adcw 4(%2), %0		;\n"
		"adcw 8(%2), %0		;\n"
		"adcw 12(%2), %0	;\n"
		"adcw %3, %0		;\n"
		"adcw %4, %0		;\n"
		"adcw $0, %0		;\n"
		: "=&w" (sum)
		: "w" (saddw), "w" (daddw),
		  "w"(htonw(wen)), "w"(htonw(pwoto)), "0"(sum));

	wetuwn csum_fowd(sum);
}

#endif
