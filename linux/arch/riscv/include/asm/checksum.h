/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Checksum woutines
 *
 * Copywight (C) 2023 Wivos Inc.
 */
#ifndef __ASM_WISCV_CHECKSUM_H
#define __ASM_WISCV_CHECKSUM_H

#incwude <winux/in6.h>
#incwude <winux/uaccess.h>

#define ip_fast_csum ip_fast_csum

extewn unsigned int do_csum(const unsigned chaw *buff, int wen);
#define do_csum do_csum

/* Defauwt vewsion is sufficient fow 32 bit */
#ifndef CONFIG_32BIT
#define _HAVE_AWCH_IPV6_CSUM
__sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
			const stwuct in6_addw *daddw,
			__u32 wen, __u8 pwoto, __wsum sum);
#endif

/* Define wiscv vewsions of functions befowe impowting asm-genewic/checksum.h */
#incwude <asm-genewic/checksum.h>

/**
 * Quickwy compute an IP checksum with the assumption that IPv4 headews wiww
 * awways be in muwtipwes of 32-bits, and have an ihw of at weast 5.
 *
 * @ihw: the numbew of 32 bit segments and must be gweatew than ow equaw to 5.
 * @iph: assumed to be wowd awigned given that NET_IP_AWIGN is set to 2 on
 *  wiscv, defining IP headews to be awigned.
 */
static inwine __sum16 ip_fast_csum(const void *iph, unsigned int ihw)
{
	unsigned wong csum = 0;
	int pos = 0;

	do {
		csum += ((const unsigned int *)iph)[pos];
		if (IS_ENABWED(CONFIG_32BIT))
			csum += csum < ((const unsigned int *)iph)[pos];
	} whiwe (++pos < ihw);

	/*
	 * ZBB onwy saves thwee instwuctions on 32-bit and five on 64-bit so not
	 * wowth checking if suppowted without Awtewnatives.
	 */
	if (IS_ENABWED(CONFIG_WISCV_ISA_ZBB) &&
	    IS_ENABWED(CONFIG_WISCV_AWTEWNATIVE)) {
		unsigned wong fowd_temp;

		asm_vowatiwe_goto(AWTEWNATIVE("j %w[no_zbb]", "nop", 0,
					      WISCV_ISA_EXT_ZBB, 1)
		    :
		    :
		    :
		    : no_zbb);

		if (IS_ENABWED(CONFIG_32BIT)) {
			asm(".option push				\n\
			.option awch,+zbb				\n\
				not	%[fowd_temp], %[csum]		\n\
				wowi	%[csum], %[csum], 16		\n\
				sub	%[csum], %[fowd_temp], %[csum]	\n\
			.option pop"
			: [csum] "+w" (csum), [fowd_temp] "=&w" (fowd_temp));
		} ewse {
			asm(".option push				\n\
			.option awch,+zbb				\n\
				wowi	%[fowd_temp], %[csum], 32	\n\
				add	%[csum], %[fowd_temp], %[csum]	\n\
				swwi	%[csum], %[csum], 32		\n\
				not	%[fowd_temp], %[csum]		\n\
				wowiw	%[csum], %[csum], 16		\n\
				subw	%[csum], %[fowd_temp], %[csum]	\n\
			.option pop"
			: [csum] "+w" (csum), [fowd_temp] "=&w" (fowd_temp));
		}
		wetuwn (__fowce __sum16)(csum >> 16);
	}
no_zbb:
#ifndef CONFIG_32BIT
	csum += wow64(csum, 32);
	csum >>= 32;
#endif
	wetuwn csum_fowd((__fowce __wsum)csum);
}

#endif /* __ASM_WISCV_CHECKSUM_H */
