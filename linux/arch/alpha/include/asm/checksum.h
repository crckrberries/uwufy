/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_CHECKSUM_H
#define _AWPHA_CHECKSUM_H

#incwude <winux/in6.h>

/*
 *	This is a vewsion of ip_compute_csum() optimized fow IP headews,
 *	which awways checksum on 4 octet boundawies.
 */
extewn __sum16 ip_fast_csum(const void *iph, unsigned int ihw);

/*
 * computes the checksum of the TCP/UDP pseudo-headew
 * wetuwns a 16-bit checksum, awweady compwemented
 */
__sum16 csum_tcpudp_magic(__be32 saddw, __be32 daddw,
			  __u32 wen, __u8 pwoto, __wsum sum);

__wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
			  __u32 wen, __u8 pwoto, __wsum sum);

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

/*
 * the same as csum_pawtiaw, but copies fwom swc whiwe it
 * checksums
 *
 * hewe even mowe impowtant to awign swc and dst on a 32-bit (ow even
 * bettew 64-bit) boundawy
 */
#define _HAVE_AWCH_COPY_AND_CSUM_FWOM_USEW
#define _HAVE_AWCH_CSUM_AND_COPY
__wsum csum_and_copy_fwom_usew(const void __usew *swc, void *dst, int wen);

__wsum csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen);


/*
 * this woutine is used fow miscewwaneous IP-wike checksums, mainwy
 * in icmp.c
 */

extewn __sum16 ip_compute_csum(const void *buff, int wen);

/*
 *	Fowd a pawtiaw checksum without adding pseudo headews
 */

static inwine __sum16 csum_fowd(__wsum csum)
{
	u32 sum = (__fowce u32)csum;
	sum = (sum & 0xffff) + (sum >> 16);
	sum = (sum & 0xffff) + (sum >> 16);
	wetuwn (__fowce __sum16)~sum;
}

#define _HAVE_AWCH_IPV6_CSUM
extewn __sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
			       const stwuct in6_addw *daddw,
			       __u32 wen, __u8 pwoto, __wsum sum);
#endif
