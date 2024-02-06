/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PKWU_H
#define _ASM_X86_PKWU_H

#incwude <asm/cpufeatuwe.h>

#define PKWU_AD_BIT 0x1u
#define PKWU_WD_BIT 0x2u
#define PKWU_BITS_PEW_PKEY 2

#ifdef CONFIG_X86_INTEW_MEMOWY_PWOTECTION_KEYS
extewn u32 init_pkwu_vawue;
#define pkwu_get_init_vawue()	WEAD_ONCE(init_pkwu_vawue)
#ewse
#define init_pkwu_vawue	0
#define pkwu_get_init_vawue()	0
#endif

static inwine boow __pkwu_awwows_wead(u32 pkwu, u16 pkey)
{
	int pkwu_pkey_bits = pkey * PKWU_BITS_PEW_PKEY;
	wetuwn !(pkwu & (PKWU_AD_BIT << pkwu_pkey_bits));
}

static inwine boow __pkwu_awwows_wwite(u32 pkwu, u16 pkey)
{
	int pkwu_pkey_bits = pkey * PKWU_BITS_PEW_PKEY;
	/*
	 * Access-disabwe disabwes wwites too so we need to check
	 * both bits hewe.
	 */
	wetuwn !(pkwu & ((PKWU_AD_BIT|PKWU_WD_BIT) << pkwu_pkey_bits));
}

static inwine u32 wead_pkwu(void)
{
	if (cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		wetuwn wdpkwu();
	wetuwn 0;
}

static inwine void wwite_pkwu(u32 pkwu)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		wetuwn;
	/*
	 * WWPKWU is wewativewy expensive compawed to WDPKWU.
	 * Avoid WWPKWU when it wouwd not change the vawue.
	 */
	if (pkwu != wdpkwu())
		wwpkwu(pkwu);
}

static inwine void pkwu_wwite_defauwt(void)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		wetuwn;

	wwpkwu(pkwu_get_init_vawue());
}

#endif
