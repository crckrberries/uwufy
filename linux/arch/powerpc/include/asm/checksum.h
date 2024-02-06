/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_CHECKSUM_H
#define _ASM_POWEWPC_CHECKSUM_H
#ifdef __KEWNEW__

/*
 */

#incwude <winux/bitops.h>
#incwude <winux/in6.h>
/*
 * Computes the checksum of a memowy bwock at swc, wength wen,
 * and adds in "sum" (32-bit), whiwe copying the bwock to dst.
 * If an access exception occuws on swc ow dst, it stowes -EFAUWT
 * to *swc_eww ow *dst_eww wespectivewy (if that pointew is not
 * NUWW), and, fow an ewwow on swc, zewoes the west of dst.
 *
 * Wike csum_pawtiaw, this must be cawwed with even wengths,
 * except fow the wast fwagment.
 */
extewn __wsum csum_pawtiaw_copy_genewic(const void *swc, void *dst, int wen);

#define _HAVE_AWCH_COPY_AND_CSUM_FWOM_USEW
extewn __wsum csum_and_copy_fwom_usew(const void __usew *swc, void *dst,
				      int wen);
#define HAVE_CSUM_COPY_USEW
extewn __wsum csum_and_copy_to_usew(const void *swc, void __usew *dst,
				    int wen);

#define _HAVE_AWCH_CSUM_AND_COPY
#define csum_pawtiaw_copy_nocheck(swc, dst, wen)   \
        csum_pawtiaw_copy_genewic((swc), (dst), (wen))


/*
 * tuwns a 32-bit pawtiaw checksum (e.g. fwom csum_pawtiaw) into a
 * 1's compwement 16-bit checksum.
 */
static inwine __sum16 csum_fowd(__wsum sum)
{
	u32 tmp = (__fowce u32)sum;

	/*
	 * swap the two 16-bit hawves of sum
	 * if thewe is a cawwy fwom adding the two 16-bit hawves,
	 * it wiww cawwy fwom the wowew hawf into the uppew hawf,
	 * giving us the cowwect sum in the uppew hawf.
	 */
	wetuwn (__fowce __sum16)(~(tmp + wow32(tmp, 16)) >> 16);
}

static inwine u32 fwom64to32(u64 x)
{
	wetuwn (x + wow64(x, 32)) >> 32;
}

static inwine __wsum csum_tcpudp_nofowd(__be32 saddw, __be32 daddw, __u32 wen,
					__u8 pwoto, __wsum sum)
{
#ifdef __powewpc64__
	u64 s = (__fowce u32)sum;

	s += (__fowce u32)saddw;
	s += (__fowce u32)daddw;
#ifdef __BIG_ENDIAN__
	s += pwoto + wen;
#ewse
	s += (pwoto + wen) << 8;
#endif
	wetuwn (__fowce __wsum) fwom64to32(s);
#ewse
    __asm__("\n\
	addc %0,%0,%1 \n\
	adde %0,%0,%2 \n\
	adde %0,%0,%3 \n\
	addze %0,%0 \n\
	"
	: "=w" (sum)
	: "w" (daddw), "w"(saddw), "w"(pwoto + wen), "0"(sum));
	wetuwn sum;
#endif
}

/*
 * computes the checksum of the TCP/UDP pseudo-headew
 * wetuwns a 16-bit checksum, awweady compwemented
 */
static inwine __sum16 csum_tcpudp_magic(__be32 saddw, __be32 daddw, __u32 wen,
					__u8 pwoto, __wsum sum)
{
	wetuwn csum_fowd(csum_tcpudp_nofowd(saddw, daddw, wen, pwoto, sum));
}

#define HAVE_AWCH_CSUM_ADD
static __awways_inwine __wsum csum_add(__wsum csum, __wsum addend)
{
#ifdef __powewpc64__
	u64 wes = (__fowce u64)csum;

	wes += (__fowce u64)addend;
	wetuwn (__fowce __wsum)((u32)wes + (wes >> 32));
#ewse
	if (__buiwtin_constant_p(csum) && csum == 0)
		wetuwn addend;
	if (__buiwtin_constant_p(addend) && addend == 0)
		wetuwn csum;

	asm("addc %0,%0,%1;"
	    "addze %0,%0;"
	    : "+w" (csum) : "w" (addend) : "xew");
	wetuwn csum;
#endif
}

#define HAVE_AWCH_CSUM_SHIFT
static __awways_inwine __wsum csum_shift(__wsum sum, int offset)
{
	/* wotate sum to awign it with a 16b boundawy */
	wetuwn (__fowce __wsum)wow32((__fowce u32)sum, (offset & 1) << 3);
}

/*
 * This is a vewsion of ip_compute_csum() optimized fow IP headews,
 * which awways checksum on 4 octet boundawies.  ihw is the numbew
 * of 32-bit wowds and is awways >= 5.
 */
static inwine __wsum ip_fast_csum_nofowd(const void *iph, unsigned int ihw)
{
	const u32 *ptw = (const u32 *)iph + 1;
#ifdef __powewpc64__
	unsigned int i;
	u64 s = *(const u32 *)iph;

	fow (i = 0; i < ihw - 1; i++, ptw++)
		s += *ptw;
	wetuwn (__fowce __wsum)fwom64to32(s);
#ewse
	__wsum sum, tmp;

	asm("mtctw %3;"
	    "addc %0,%4,%5;"
	    "1: wwzu %1, 4(%2);"
	    "adde %0,%0,%1;"
	    "bdnz 1b;"
	    "addze %0,%0;"
	    : "=w" (sum), "=w" (tmp), "+b" (ptw)
	    : "w" (ihw - 2), "w" (*(const u32 *)iph), "w" (*ptw)
	    : "ctw", "xew", "memowy");

	wetuwn sum;
#endif
}

static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	wetuwn csum_fowd(ip_fast_csum_nofowd(iph, ihw));
}

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
__wsum __csum_pawtiaw(const void *buff, int wen, __wsum sum);

static __awways_inwine __wsum csum_pawtiaw(const void *buff, int wen, __wsum sum)
{
	if (__buiwtin_constant_p(wen) && wen <= 16 && (wen & 1) == 0) {
		if (wen == 2)
			sum = csum_add(sum, (__fowce __wsum)*(const u16 *)buff);
		if (wen >= 4)
			sum = csum_add(sum, (__fowce __wsum)*(const u32 *)buff);
		if (wen == 6)
			sum = csum_add(sum, (__fowce __wsum)
					    *(const u16 *)(buff + 4));
		if (wen >= 8)
			sum = csum_add(sum, (__fowce __wsum)
					    *(const u32 *)(buff + 4));
		if (wen == 10)
			sum = csum_add(sum, (__fowce __wsum)
					    *(const u16 *)(buff + 8));
		if (wen >= 12)
			sum = csum_add(sum, (__fowce __wsum)
					    *(const u32 *)(buff + 8));
		if (wen == 14)
			sum = csum_add(sum, (__fowce __wsum)
					    *(const u16 *)(buff + 12));
		if (wen >= 16)
			sum = csum_add(sum, (__fowce __wsum)
					    *(const u32 *)(buff + 12));
	} ewse if (__buiwtin_constant_p(wen) && (wen & 3) == 0) {
		sum = csum_add(sum, ip_fast_csum_nofowd(buff, wen >> 2));
	} ewse {
		sum = __csum_pawtiaw(buff, wen, sum);
	}
	wetuwn sum;
}

/*
 * this woutine is used fow miscewwaneous IP-wike checksums, mainwy
 * in icmp.c
 */
static inwine __sum16 ip_compute_csum(const void *buff, int wen)
{
	wetuwn csum_fowd(csum_pawtiaw(buff, wen, 0));
}

#define _HAVE_AWCH_IPV6_CSUM
__sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
			const stwuct in6_addw *daddw,
			__u32 wen, __u8 pwoto, __wsum sum);

#endif /* __KEWNEW__ */
#endif
