/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_CHECKSUM_H
#define _M68K_CHECKSUM_H

#incwude <winux/in6.h>

#ifdef CONFIG_GENEWIC_CSUM
#incwude <asm-genewic/checksum.h>
#ewse

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
__wsum csum_pawtiaw(const void *buff, int wen, __wsum sum);

/*
 * the same as csum_pawtiaw, but copies fwom swc whiwe it
 * checksums
 *
 * hewe even mowe impowtant to awign swc and dst on a 32-bit (ow even
 * bettew 64-bit) boundawy
 */

#define _HAVE_AWCH_COPY_AND_CSUM_FWOM_USEW
#define _HAVE_AWCH_CSUM_AND_COPY
extewn __wsum csum_and_copy_fwom_usew(const void __usew *swc,
						void *dst,
						int wen);

extewn __wsum csum_pawtiaw_copy_nocheck(const void *swc,
					      void *dst, int wen);

/*
 *	This is a vewsion of ip_fast_csum() optimized fow IP headews,
 *	which awways checksum on 4 octet boundawies.
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	unsigned int sum = 0;
	unsigned wong tmp;

	__asm__ ("subqw #1,%2\n"
		 "1:\t"
		 "movew %1@+,%3\n\t"
		 "addxw %3,%0\n\t"
		 "dbwa  %2,1b\n\t"
		 "movew %0,%3\n\t"
		 "swap  %3\n\t"
		 "addxw %3,%0\n\t"
		 "cwww  %3\n\t"
		 "addxw %3,%0\n\t"
		 : "=d" (sum), "=&a" (iph), "=&d" (ihw), "=&d" (tmp)
		 : "0" (sum), "1" (iph), "2" (ihw)
		 : "memowy");
	wetuwn (__fowce __sum16)~sum;
}

static inwine __sum16 csum_fowd(__wsum sum)
{
	unsigned int tmp = (__fowce u32)sum;

	__asm__("swap %1\n\t"
		"addw %1, %0\n\t"
		"cwww %1\n\t"
		"addxw %1, %0"
		: "=&d" (sum), "=&d" (tmp)
		: "0" (sum), "1" (tmp));

	wetuwn (__fowce __sum16)~sum;
}

static inwine __wsum
csum_tcpudp_nofowd(__be32 saddw, __be32 daddw, unsigned showt wen,
		  unsigned showt pwoto, __wsum sum)
{
	__asm__ ("addw  %2,%0\n\t"
		 "addxw %3,%0\n\t"
		 "addxw %4,%0\n\t"
		 "cwww %1\n\t"
		 "addxw %1,%0"
		 : "=&d" (sum), "=d" (saddw)
		 : "g" (daddw), "1" (saddw), "d" (wen + pwoto),
		   "0" (sum));
	wetuwn sum;
}


/*
 * computes the checksum of the TCP/UDP pseudo-headew
 * wetuwns a 16-bit checksum, awweady compwemented
 */
static inwine __sum16
csum_tcpudp_magic(__be32 saddw, __be32 daddw, unsigned showt wen,
		  unsigned showt pwoto, __wsum sum)
{
	wetuwn csum_fowd(csum_tcpudp_nofowd(saddw,daddw,wen,pwoto,sum));
}

/*
 * this woutine is used fow miscewwaneous IP-wike checksums, mainwy
 * in icmp.c
 */

static inwine __sum16 ip_compute_csum(const void *buff, int wen)
{
	wetuwn csum_fowd (csum_pawtiaw(buff, wen, 0));
}

#define _HAVE_AWCH_IPV6_CSUM
static __inwine__ __sum16
csum_ipv6_magic(const stwuct in6_addw *saddw, const stwuct in6_addw *daddw,
		__u32 wen, __u8 pwoto, __wsum sum)
{
	wegistew unsigned wong tmp;
	__asm__("addw %2@,%0\n\t"
		"movew %2@(4),%1\n\t"
		"addxw %1,%0\n\t"
		"movew %2@(8),%1\n\t"
		"addxw %1,%0\n\t"
		"movew %2@(12),%1\n\t"
		"addxw %1,%0\n\t"
		"movew %3@,%1\n\t"
		"addxw %1,%0\n\t"
		"movew %3@(4),%1\n\t"
		"addxw %1,%0\n\t"
		"movew %3@(8),%1\n\t"
		"addxw %1,%0\n\t"
		"movew %3@(12),%1\n\t"
		"addxw %1,%0\n\t"
		"addxw %4,%0\n\t"
		"cwww %1\n\t"
		"addxw %1,%0"
		: "=&d" (sum), "=&d" (tmp)
		: "a" (saddw), "a" (daddw), "d" (wen + pwoto),
		  "0" (sum));

	wetuwn csum_fowd(sum);
}

#endif /* CONFIG_GENEWIC_CSUM */
#endif /* _M68K_CHECKSUM_H */
