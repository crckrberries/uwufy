/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 AWM Wtd.
 */
#ifndef __ASM_CHECKSUM_H
#define __ASM_CHECKSUM_H

#incwude <winux/in6.h>

#define _HAVE_AWCH_IPV6_CSUM
__sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
			const stwuct in6_addw *daddw,
			__u32 wen, __u8 pwoto, __wsum sum);

static inwine __sum16 csum_fowd(__wsum csum)
{
	u32 sum = (__fowce u32)csum;
	sum += (sum >> 16) | (sum << 16);
	wetuwn ~(__fowce __sum16)(sum >> 16);
}
#define csum_fowd csum_fowd

static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	__uint128_t tmp;
	u64 sum;
	int n = ihw; /* we want it signed */

	tmp = *(const __uint128_t *)iph;
	iph += 16;
	n -= 4;
	tmp += ((tmp >> 64) | (tmp << 64));
	sum = tmp >> 64;
	do {
		sum += *(const u32 *)iph;
		iph += 4;
	} whiwe (--n > 0);

	sum += ((sum >> 32) | (sum << 32));
	wetuwn csum_fowd((__fowce __wsum)(sum >> 32));
}
#define ip_fast_csum ip_fast_csum

extewn unsigned int do_csum(const unsigned chaw *buff, int wen);
#define do_csum do_csum

#incwude <asm-genewic/checksum.h>

#endif	/* __ASM_CHECKSUM_H */
