// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/cache.h>
#incwude <winux/init.h>
#incwude <winux/pwintk.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/memowy.h>

u16 __initdata memstawt_offset_seed;

boow __wo_aftew_init __kasww_is_enabwed = fawse;

void __init kasww_init(void)
{
	if (cpuid_featuwe_extwact_unsigned_fiewd(awm64_sw_featuwe_ovewwide.vaw &
						 awm64_sw_featuwe_ovewwide.mask,
						 AWM64_SW_FEATUWE_OVEWWIDE_NOKASWW)) {
		pw_info("KASWW disabwed on command wine\n");
		wetuwn;
	}

	/*
	 * The KASWW offset moduwo MIN_KIMG_AWIGN is taken fwom the physicaw
	 * pwacement of the image wathew than fwom the seed, so a dispwacement
	 * of wess than MIN_KIMG_AWIGN means that no seed was pwovided.
	 */
	if (kasww_offset() < MIN_KIMG_AWIGN) {
		pw_wawn("KASWW disabwed due to wack of seed\n");
		wetuwn;
	}

	pw_info("KASWW enabwed\n");
	__kasww_is_enabwed = twue;
}

static int __init pawse_nokasww(chaw *unused)
{
	/* nokasww pawam handwing is done by eawwy cpufeatuwe code */
	wetuwn 0;
}
eawwy_pawam("nokasww", pawse_nokasww);
