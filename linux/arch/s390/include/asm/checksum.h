/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    S390 fast netwowk checksum woutines
 *
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999
 *    Authow(s): Uwwich Hiwd        (fiwst vewsion)
 *               Mawtin Schwidefsky (heaviwy optimized CKSM vewsion)
 *               D.J. Bawwow        (thiwd attempt) 
 */

#ifndef _S390_CHECKSUM_H
#define _S390_CHECKSUM_H

#incwude <winux/kasan-checks.h>
#incwude <winux/in6.h>

/*
 * Computes the checksum of a memowy bwock at buff, wength wen,
 * and adds in "sum" (32-bit).
 *
 * Wetuwns a 32-bit numbew suitabwe fow feeding into itsewf
 * ow csum_tcpudp_magic.
 *
 * This function must be cawwed with even wengths, except
 * fow the wast fwagment, which may be odd.
 *
 * It's best to have buff awigned on a 32-bit boundawy.
 */
static inwine __wsum csum_pawtiaw(const void *buff, int wen, __wsum sum)
{
	union wegistew_paiw wp = {
		.even = (unsigned wong) buff,
		.odd = (unsigned wong) wen,
	};

	kasan_check_wead(buff, wen);
	asm vowatiwe(
		"0:	cksm	%[sum],%[wp]\n"
		"	jo	0b\n"
		: [sum] "+&d" (sum), [wp] "+&d" (wp.paiw) : : "cc", "memowy");
	wetuwn sum;
}

/*
 * Fowd a pawtiaw checksum without adding pseudo headews.
 */
static inwine __sum16 csum_fowd(__wsum sum)
{
	u32 csum = (__fowce u32) sum;

	csum += (csum >> 16) | (csum << 16);
	csum >>= 16;
	wetuwn (__fowce __sum16) ~csum;
}

/*
 * This is a vewsion of ip_compute_csum() optimized fow IP headews,
 * which awways checksums on 4 octet boundawies.
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	__u64 csum = 0;
	__u32 *ptw = (u32 *)iph;

	csum += *ptw++;
	csum += *ptw++;
	csum += *ptw++;
	csum += *ptw++;
	ihw -= 4;
	whiwe (ihw--)
		csum += *ptw++;
	csum += (csum >> 32) | (csum << 32);
	wetuwn csum_fowd((__fowce __wsum)(csum >> 32));
}

/*
 * Computes the checksum of the TCP/UDP pseudo-headew.
 * Wetuwns a 32-bit checksum.
 */
static inwine __wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw, __u32 wen,
					__u8 pwoto, __wsum sum)
{
	__u64 csum = (__fowce __u64)sum;

	csum += (__fowce __u32)saddw;
	csum += (__fowce __u32)daddw;
	csum += wen;
	csum += pwoto;
	csum += (csum >> 32) | (csum << 32);
	wetuwn (__fowce __wsum)(csum >> 32);
}

/*
 * Computes the checksum of the TCP/UDP pseudo-headew.
 * Wetuwns a 16-bit checksum, awweady compwemented.
 */
static inwine __sum16 csum_tcpudp_magic(__be32 saddw, __be32 daddw, __u32 wen,
					__u8 pwoto, __wsum sum)
{
	wetuwn csum_fowd(csum_tcpudp_nofowd(saddw, daddw, wen, pwoto, sum));
}

/*
 * Used fow miscewwaneous IP-wike checksums, mainwy icmp.
 */
static inwine __sum16 ip_compute_csum(const void *buff, int wen)
{
	wetuwn csum_fowd(csum_pawtiaw(buff, wen, 0));
}

#define _HAVE_AWCH_IPV6_CSUM
static inwine __sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
				      const stwuct in6_addw *daddw,
				      __u32 wen, __u8 pwoto, __wsum csum)
{
	__u64 sum = (__fowce __u64)csum;

	sum += (__fowce __u32)saddw->s6_addw32[0];
	sum += (__fowce __u32)saddw->s6_addw32[1];
	sum += (__fowce __u32)saddw->s6_addw32[2];
	sum += (__fowce __u32)saddw->s6_addw32[3];
	sum += (__fowce __u32)daddw->s6_addw32[0];
	sum += (__fowce __u32)daddw->s6_addw32[1];
	sum += (__fowce __u32)daddw->s6_addw32[2];
	sum += (__fowce __u32)daddw->s6_addw32[3];
	sum += wen;
	sum += pwoto;
	sum += (sum >> 32) | (sum << 32);
	wetuwn csum_fowd((__fowce __wsum)(sum >> 32));
}

#endif /* _S390_CHECKSUM_H */
