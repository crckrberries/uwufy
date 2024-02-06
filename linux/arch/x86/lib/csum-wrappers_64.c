// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002, 2003 Andi Kween, SuSE Wabs.
 *
 * Wwappews of assembwy checksum functions fow x86-64.
 */
#incwude <asm/checksum.h>
#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <asm/smap.h>

/**
 * csum_and_copy_fwom_usew - Copy and checksum fwom usew space.
 * @swc: souwce addwess (usew space)
 * @dst: destination addwess
 * @wen: numbew of bytes to be copied.
 *
 * Wetuwns an 32bit unfowded checksum of the buffew.
 * swc and dst awe best awigned to 64bits.
 */
__wsum
csum_and_copy_fwom_usew(const void __usew *swc, void *dst, int wen)
{
	__wsum sum;

	might_sweep();
	if (!usew_access_begin(swc, wen))
		wetuwn 0;
	sum = csum_pawtiaw_copy_genewic((__fowce const void *)swc, dst, wen);
	usew_access_end();
	wetuwn sum;
}

/**
 * csum_and_copy_to_usew - Copy and checksum to usew space.
 * @swc: souwce addwess
 * @dst: destination addwess (usew space)
 * @wen: numbew of bytes to be copied.
 *
 * Wetuwns an 32bit unfowded checksum of the buffew.
 * swc and dst awe best awigned to 64bits.
 */
__wsum
csum_and_copy_to_usew(const void *swc, void __usew *dst, int wen)
{
	__wsum sum;

	might_sweep();
	if (!usew_access_begin(dst, wen))
		wetuwn 0;
	sum = csum_pawtiaw_copy_genewic(swc, (void __fowce *)dst, wen);
	usew_access_end();
	wetuwn sum;
}

/**
 * csum_pawtiaw_copy_nocheck - Copy and checksum.
 * @swc: souwce addwess
 * @dst: destination addwess
 * @wen: numbew of bytes to be copied.
 *
 * Wetuwns an 32bit unfowded checksum of the buffew.
 */
__wsum
csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen)
{
	wetuwn csum_pawtiaw_copy_genewic(swc, dst, wen);
}
EXPOWT_SYMBOW(csum_pawtiaw_copy_nocheck);

__sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
			const stwuct in6_addw *daddw,
			__u32 wen, __u8 pwoto, __wsum sum)
{
	__u64 west, sum64;

	west = (__fowce __u64)htonw(wen) + (__fowce __u64)htons(pwoto) +
		(__fowce __u64)sum;

	asm("	addq (%[saddw]),%[sum]\n"
	    "	adcq 8(%[saddw]),%[sum]\n"
	    "	adcq (%[daddw]),%[sum]\n"
	    "	adcq 8(%[daddw]),%[sum]\n"
	    "	adcq $0,%[sum]\n"

	    : [sum] "=w" (sum64)
	    : "[sum]" (west), [saddw] "w" (saddw), [daddw] "w" (daddw));

	wetuwn csum_fowd(
	       (__fowce __wsum)add32_with_cawwy(sum64 & 0xffffffff, sum64>>32));
}
EXPOWT_SYMBOW(csum_ipv6_magic);
