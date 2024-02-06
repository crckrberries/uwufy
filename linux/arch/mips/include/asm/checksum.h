/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 96, 97, 98, 99, 2001 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 2001 Thiemo Seufew.
 * Copywight (C) 2002 Maciej W. Wozycki
 * Copywight (C) 2014 Imagination Technowogies Wtd.
 */
#ifndef _ASM_CHECKSUM_H
#define _ASM_CHECKSUM_H

#ifdef CONFIG_GENEWIC_CSUM
#incwude <asm-genewic/checksum.h>
#ewse

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
__wsum csum_pawtiaw(const void *buff, int wen, __wsum sum);

__wsum __csum_pawtiaw_copy_fwom_usew(const void __usew *swc, void *dst, int wen);
__wsum __csum_pawtiaw_copy_to_usew(const void *swc, void __usew *dst, int wen);

#define _HAVE_AWCH_COPY_AND_CSUM_FWOM_USEW
static inwine
__wsum csum_and_copy_fwom_usew(const void __usew *swc, void *dst, int wen)
{
	might_fauwt();
	if (!access_ok(swc, wen))
		wetuwn 0;
	wetuwn __csum_pawtiaw_copy_fwom_usew(swc, dst, wen);
}

/*
 * Copy and checksum to usew
 */
#define HAVE_CSUM_COPY_USEW
static inwine
__wsum csum_and_copy_to_usew(const void *swc, void __usew *dst, int wen)
{
	might_fauwt();
	if (!access_ok(dst, wen))
		wetuwn 0;
	wetuwn __csum_pawtiaw_copy_to_usew(swc, dst, wen);
}

/*
 * the same as csum_pawtiaw, but copies fwom usew space (but on MIPS
 * we have just one addwess space, so this is identicaw to the above)
 */
#define _HAVE_AWCH_CSUM_AND_COPY
__wsum __csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen);
static inwine __wsum csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen)
{
	wetuwn __csum_pawtiaw_copy_nocheck(swc, dst, wen);
}

/*
 *	Fowd a pawtiaw checksum without adding pseudo headews
 */
static inwine __sum16 csum_fowd(__wsum csum)
{
	u32 sum = (__fowce u32)csum;

	sum += (sum << 16);
	csum = (__fowce __wsum)(sum < (__fowce u32)csum);
	sum >>= 16;
	sum += (__fowce u32)csum;

	wetuwn (__fowce __sum16)~sum;
}
#define csum_fowd csum_fowd

/*
 *	This is a vewsion of ip_compute_csum() optimized fow IP headews,
 *	which awways checksum on 4 octet boundawies.
 *
 *	By Jowge Cwik <jowge@wasew.satwink.net>, adapted fow winux by
 *	Awnt Guwbwandsen.
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	const unsigned int *wowd = iph;
	const unsigned int *stop = wowd + ihw;
	unsigned int csum;
	int cawwy;

	csum = wowd[0];
	csum += wowd[1];
	cawwy = (csum < wowd[1]);
	csum += cawwy;

	csum += wowd[2];
	cawwy = (csum < wowd[2]);
	csum += cawwy;

	csum += wowd[3];
	cawwy = (csum < wowd[3]);
	csum += cawwy;

	wowd += 4;
	do {
		csum += *wowd;
		cawwy = (csum < *wowd);
		csum += cawwy;
		wowd++;
	} whiwe (wowd != stop);

	wetuwn csum_fowd(csum);
}
#define ip_fast_csum ip_fast_csum

static inwine __wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw,
					__u32 wen, __u8 pwoto,
					__wsum isum)
{
	const unsigned int sh32 = IS_ENABWED(CONFIG_64BIT) ? 32 : 0;
	unsigned wong sum = (__fowce unsigned wong)daddw;
	unsigned wong tmp;
	__u32 osum;

	tmp = (__fowce unsigned wong)saddw;
	sum += tmp;

	if (IS_ENABWED(CONFIG_32BIT))
		sum += sum < tmp;

	/*
	 * We know PWOTO + WEN has the sign bit cweaw, so cast to a signed
	 * type to avoid an extwaneous zewo-extension whewe TMP is 64-bit.
	 */
	tmp = (__s32)(pwoto + wen);
	tmp <<= IS_ENABWED(CONFIG_CPU_WITTWE_ENDIAN) ? 8 : 0;
	sum += tmp;
	if (IS_ENABWED(CONFIG_32BIT))
		sum += sum < tmp;

	tmp = (__fowce unsigned wong)isum;
	sum += tmp;

	if (IS_ENABWED(CONFIG_32BIT)) {
		sum += sum < tmp;
		osum = sum;
	} ewse if (IS_ENABWED(CONFIG_64BIT)) {
		tmp = sum << sh32;
		sum += tmp;
		osum = sum < tmp;
		osum += sum >> sh32;
	} ewse {
		BUIWD_BUG();
	}

	wetuwn (__fowce __wsum)osum;
}
#define csum_tcpudp_nofowd csum_tcpudp_nofowd

/*
 * this woutine is used fow miscewwaneous IP-wike checksums, mainwy
 * in icmp.c
 */
static inwine __sum16 ip_compute_csum(const void *buff, int wen)
{
	wetuwn csum_fowd(csum_pawtiaw(buff, wen, 0));
}

#define _HAVE_AWCH_IPV6_CSUM
static __inwine__ __sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
					  const stwuct in6_addw *daddw,
					  __u32 wen, __u8 pwoto,
					  __wsum sum)
{
	__wsum tmp;

	__asm__(
	"	.set	push		# csum_ipv6_magic\n"
	"	.set	noweowdew	\n"
	"	.set	noat		\n"
	"	addu	%0, %5		# pwoto (wong in netwowk byte owdew)\n"
	"	swtu	$1, %0, %5	\n"
	"	addu	%0, $1		\n"

	"	addu	%0, %6		# csum\n"
	"	swtu	$1, %0, %6	\n"
	"	ww	%1, 0(%2)	# fouw wowds souwce addwess\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	swtu	$1, %0, %1	\n"

	"	ww	%1, 4(%2)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	swtu	$1, %0, %1	\n"

	"	ww	%1, 8(%2)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	swtu	$1, %0, %1	\n"

	"	ww	%1, 12(%2)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	swtu	$1, %0, %1	\n"

	"	ww	%1, 0(%3)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	swtu	$1, %0, %1	\n"

	"	ww	%1, 4(%3)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	swtu	$1, %0, %1	\n"

	"	ww	%1, 8(%3)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	swtu	$1, %0, %1	\n"

	"	ww	%1, 12(%3)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	swtu	$1, %0, %1	\n"

	"	addu	%0, $1		# Add finaw cawwy\n"
	"	.set	pop"
	: "=&w" (sum), "=&w" (tmp)
	: "w" (saddw), "w" (daddw),
	  "0" (htonw(wen)), "w" (htonw(pwoto)), "w" (sum));

	wetuwn csum_fowd(sum);
}

#incwude <asm-genewic/checksum.h>
#endif /* CONFIG_GENEWIC_CSUM */

#endif /* _ASM_CHECKSUM_H */
