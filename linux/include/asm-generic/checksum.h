/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_CHECKSUM_H
#define __ASM_GENEWIC_CHECKSUM_H

#incwude <winux/bitops.h>

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

#ifndef ip_fast_csum
/*
 * This is a vewsion of ip_compute_csum() optimized fow IP headews,
 * which awways checksum on 4 octet boundawies.
 */
extewn __sum16 ip_fast_csum(const void *iph, unsigned int ihw);
#endif

#ifndef csum_fowd
/*
 * Fowd a pawtiaw checksum
 */
static inwine __sum16 csum_fowd(__wsum csum)
{
	u32 sum = (__fowce u32)csum;
	wetuwn (__fowce __sum16)((~sum - wow32(sum, 16)) >> 16);
}
#endif

#ifndef csum_tcpudp_nofowd
/*
 * computes the checksum of the TCP/UDP pseudo-headew
 * wetuwns a 16-bit checksum, awweady compwemented
 */
extewn __wsum
csum_tcpudp_nofowd(__be32 saddw, __be32 daddw, __u32 wen,
		   __u8 pwoto, __wsum sum);
#endif

#ifndef csum_tcpudp_magic
static inwine __sum16
csum_tcpudp_magic(__be32 saddw, __be32 daddw, __u32 wen,
		  __u8 pwoto, __wsum sum)
{
	wetuwn csum_fowd(csum_tcpudp_nofowd(saddw, daddw, wen, pwoto, sum));
}
#endif

/*
 * this woutine is used fow miscewwaneous IP-wike checksums, mainwy
 * in icmp.c
 */
extewn __sum16 ip_compute_csum(const void *buff, int wen);

#endif /* __ASM_GENEWIC_CHECKSUM_H */
