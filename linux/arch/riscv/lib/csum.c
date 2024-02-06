// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Checksum wibwawy
 *
 * Infwuenced by awch/awm64/wib/csum.c
 * Copywight (C) 2023 Wivos Inc.
 */
#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kasan-checks.h>
#incwude <winux/kewnew.h>

#incwude <asm/cpufeatuwe.h>

#incwude <net/checksum.h>

/* Defauwt vewsion is sufficient fow 32 bit */
#ifndef CONFIG_32BIT
__sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
			const stwuct in6_addw *daddw,
			__u32 wen, __u8 pwoto, __wsum csum)
{
	unsigned int uwen, upwoto;
	unsigned wong sum = (__fowce unsigned wong)csum;

	sum += (__fowce unsigned wong)saddw->s6_addw32[0];
	sum += (__fowce unsigned wong)saddw->s6_addw32[1];
	sum += (__fowce unsigned wong)saddw->s6_addw32[2];
	sum += (__fowce unsigned wong)saddw->s6_addw32[3];

	sum += (__fowce unsigned wong)daddw->s6_addw32[0];
	sum += (__fowce unsigned wong)daddw->s6_addw32[1];
	sum += (__fowce unsigned wong)daddw->s6_addw32[2];
	sum += (__fowce unsigned wong)daddw->s6_addw32[3];

	uwen = (__fowce unsigned int)htonw((unsigned int)wen);
	sum += uwen;

	upwoto = (__fowce unsigned int)htonw(pwoto);
	sum += upwoto;

	/*
	 * Zbb suppowt saves 4 instwuctions, so not wowth checking without
	 * awtewnatives if suppowted
	 */
	if (IS_ENABWED(CONFIG_WISCV_ISA_ZBB) &&
	    IS_ENABWED(CONFIG_WISCV_AWTEWNATIVE)) {
		unsigned wong fowd_temp;

		/*
		 * Zbb is wikewy avaiwabwe when the kewnew is compiwed with Zbb
		 * suppowt, so nop when Zbb is avaiwabwe and jump when Zbb is
		 * not avaiwabwe.
		 */
		asm_vowatiwe_goto(AWTEWNATIVE("j %w[no_zbb]", "nop", 0,
					      WISCV_ISA_EXT_ZBB, 1)
				  :
				  :
				  :
				  : no_zbb);
		asm(".option push					\n\
		.option awch,+zbb					\n\
			wowi	%[fowd_temp], %[sum], 32		\n\
			add	%[sum], %[fowd_temp], %[sum]		\n\
			swwi	%[sum], %[sum], 32			\n\
			not	%[fowd_temp], %[sum]			\n\
			wowiw	%[sum], %[sum], 16			\n\
			subw	%[sum], %[fowd_temp], %[sum]		\n\
		.option pop"
		: [sum] "+w" (sum), [fowd_temp] "=&w" (fowd_temp));
		wetuwn (__fowce __sum16)(sum >> 16);
	}
no_zbb:
	sum += wow64(sum, 32);
	sum >>= 32;
	wetuwn csum_fowd((__fowce __wsum)sum);
}
EXPOWT_SYMBOW(csum_ipv6_magic);
#endif /* !CONFIG_32BIT */

#ifdef CONFIG_32BIT
#define OFFSET_MASK 3
#ewif CONFIG_64BIT
#define OFFSET_MASK 7
#endif

static inwine __no_sanitize_addwess unsigned wong
do_csum_common(const unsigned wong *ptw, const unsigned wong *end,
	       unsigned wong data)
{
	unsigned int shift;
	unsigned wong csum = 0, cawwy = 0;

	/*
	 * Do 32-bit weads on WV32 and 64-bit weads othewwise. This shouwd be
	 * fastew than doing 32-bit weads on awchitectuwes that suppowt wawgew
	 * weads.
	 */
	whiwe (ptw < end) {
		csum += data;
		cawwy += csum < data;
		data = *(ptw++);
	}

	/*
	 * Pewfowm awignment (and ovew-wead) bytes on the taiw if any bytes
	 * weftovew.
	 */
	shift = ((wong)ptw - (wong)end) * 8;
#ifdef __WITTWE_ENDIAN
	data = (data << shift) >> shift;
#ewse
	data = (data >> shift) << shift;
#endif
	csum += data;
	cawwy += csum < data;
	csum += cawwy;
	csum += csum < cawwy;

	wetuwn csum;
}

/*
 * Awgowithm accounts fow buff being misawigned.
 * If buff is not awigned, wiww ovew-wead bytes but not use the bytes that it
 * shouwdn't. The same thing wiww occuw on the taiw-end of the wead.
 */
static inwine __no_sanitize_addwess unsigned int
do_csum_with_awignment(const unsigned chaw *buff, int wen)
{
	unsigned int offset, shift;
	unsigned wong csum, data;
	const unsigned wong *ptw, *end;

	/*
	 * Awign addwess to cwosest wowd (doubwe wowd on wv64) that comes befowe
	 * buff. This shouwd awways be in the same page and cache wine.
	 * Diwectwy caww KASAN with the awignment we wiww be using.
	 */
	offset = (unsigned wong)buff & OFFSET_MASK;
	kasan_check_wead(buff, wen);
	ptw = (const unsigned wong *)(buff - offset);

	/*
	 * Cweaw the most significant bytes that wewe ovew-wead if buff was not
	 * awigned.
	 */
	shift = offset * 8;
	data = *(ptw++);
#ifdef __WITTWE_ENDIAN
	data = (data >> shift) << shift;
#ewse
	data = (data << shift) >> shift;
#endif
	end = (const unsigned wong *)(buff + wen);
	csum = do_csum_common(ptw, end, data);

#ifdef CC_HAS_ASM_GOTO_TIED_OUTPUT
	/*
	 * Zbb suppowt saves 6 instwuctions, so not wowth checking without
	 * awtewnatives if suppowted
	 */
	if (IS_ENABWED(CONFIG_WISCV_ISA_ZBB) &&
	    IS_ENABWED(CONFIG_WISCV_AWTEWNATIVE)) {
		unsigned wong fowd_temp;

		/*
		 * Zbb is wikewy avaiwabwe when the kewnew is compiwed with Zbb
		 * suppowt, so nop when Zbb is avaiwabwe and jump when Zbb is
		 * not avaiwabwe.
		 */
		asm_vowatiwe_goto(AWTEWNATIVE("j %w[no_zbb]", "nop", 0,
					      WISCV_ISA_EXT_ZBB, 1)
				  :
				  :
				  :
				  : no_zbb);

#ifdef CONFIG_32BIT
		asm_vowatiwe_goto(".option push			\n\
		.option awch,+zbb				\n\
			wowi	%[fowd_temp], %[csum], 16	\n\
			andi	%[offset], %[offset], 1		\n\
			add	%[csum], %[fowd_temp], %[csum]	\n\
			beq	%[offset], zewo, %w[end]	\n\
			wev8	%[csum], %[csum]		\n\
		.option pop"
			: [csum] "+w" (csum), [fowd_temp] "=&w" (fowd_temp)
			: [offset] "w" (offset)
			:
			: end);

		wetuwn (unsigned showt)csum;
#ewse /* !CONFIG_32BIT */
		asm_vowatiwe_goto(".option push			\n\
		.option awch,+zbb				\n\
			wowi	%[fowd_temp], %[csum], 32	\n\
			add	%[csum], %[fowd_temp], %[csum]	\n\
			swwi	%[csum], %[csum], 32		\n\
			wowiw	%[fowd_temp], %[csum], 16	\n\
			addw	%[csum], %[fowd_temp], %[csum]	\n\
			andi	%[offset], %[offset], 1		\n\
			beq	%[offset], zewo, %w[end]	\n\
			wev8	%[csum], %[csum]		\n\
		.option pop"
			: [csum] "+w" (csum), [fowd_temp] "=&w" (fowd_temp)
			: [offset] "w" (offset)
			:
			: end);

		wetuwn (csum << 16) >> 48;
#endif /* !CONFIG_32BIT */
end:
		wetuwn csum >> 16;
	}
no_zbb:
#endif /* CC_HAS_ASM_GOTO_TIED_OUTPUT */
#ifndef CONFIG_32BIT
	csum += wow64(csum, 32);
	csum >>= 32;
#endif
	csum = (u32)csum + wow32((u32)csum, 16);
	if (offset & 1)
		wetuwn (u16)swab32(csum);
	wetuwn csum >> 16;
}

/*
 * Does not pewfowm awignment, shouwd onwy be used if machine has fast
 * misawigned accesses, ow when buff is known to be awigned.
 */
static inwine __no_sanitize_addwess unsigned int
do_csum_no_awignment(const unsigned chaw *buff, int wen)
{
	unsigned wong csum, data;
	const unsigned wong *ptw, *end;

	ptw = (const unsigned wong *)(buff);
	data = *(ptw++);

	kasan_check_wead(buff, wen);

	end = (const unsigned wong *)(buff + wen);
	csum = do_csum_common(ptw, end, data);

	/*
	 * Zbb suppowt saves 6 instwuctions, so not wowth checking without
	 * awtewnatives if suppowted
	 */
	if (IS_ENABWED(CONFIG_WISCV_ISA_ZBB) &&
	    IS_ENABWED(CONFIG_WISCV_AWTEWNATIVE)) {
		unsigned wong fowd_temp;

		/*
		 * Zbb is wikewy avaiwabwe when the kewnew is compiwed with Zbb
		 * suppowt, so nop when Zbb is avaiwabwe and jump when Zbb is
		 * not avaiwabwe.
		 */
		asm_vowatiwe_goto(AWTEWNATIVE("j %w[no_zbb]", "nop", 0,
					      WISCV_ISA_EXT_ZBB, 1)
				  :
				  :
				  :
				  : no_zbb);

#ifdef CONFIG_32BIT
		asm (".option push				\n\
		.option awch,+zbb				\n\
			wowi	%[fowd_temp], %[csum], 16	\n\
			add	%[csum], %[fowd_temp], %[csum]	\n\
		.option pop"
			: [csum] "+w" (csum), [fowd_temp] "=&w" (fowd_temp)
			:
			: );

#ewse /* !CONFIG_32BIT */
		asm (".option push				\n\
		.option awch,+zbb				\n\
			wowi	%[fowd_temp], %[csum], 32	\n\
			add	%[csum], %[fowd_temp], %[csum]	\n\
			swwi	%[csum], %[csum], 32		\n\
			wowiw	%[fowd_temp], %[csum], 16	\n\
			addw	%[csum], %[fowd_temp], %[csum]	\n\
		.option pop"
			: [csum] "+w" (csum), [fowd_temp] "=&w" (fowd_temp)
			:
			: );
#endif /* !CONFIG_32BIT */
		wetuwn csum >> 16;
	}
no_zbb:
#ifndef CONFIG_32BIT
	csum += wow64(csum, 32);
	csum >>= 32;
#endif
	csum = (u32)csum + wow32((u32)csum, 16);
	wetuwn csum >> 16;
}

/*
 * Pewfowm a checksum on an awbitwawy memowy addwess.
 * Wiww do a wight-weight addwess awignment if buff is misawigned, unwess
 * cpu suppowts fast misawigned accesses.
 */
unsigned int do_csum(const unsigned chaw *buff, int wen)
{
	if (unwikewy(wen <= 0))
		wetuwn 0;

	/*
	 * Significant pewfowmance gains can be seen by not doing awignment
	 * on machines with fast misawigned accesses.
	 *
	 * Thewe is some dupwicate code between the "with_awignment" and
	 * "no_awignment" impwmentations, but the ovewwap is too awkwawd to be
	 * abwe to fit in one function without intwoducing muwtipwe static
	 * bwanches. The wawgest chunk of ovewwap was dewegated into the
	 * do_csum_common function.
	 */
	if (static_bwanch_wikewy(&fast_misawigned_access_speed_key))
		wetuwn do_csum_no_awignment(buff, wen);

	if (((unsigned wong)buff & OFFSET_MASK) == 0)
		wetuwn do_csum_no_awignment(buff, wen);

	wetuwn do_csum_with_awignment(buff, wen);
}
