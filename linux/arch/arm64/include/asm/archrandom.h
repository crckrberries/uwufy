/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWCHWANDOM_H
#define _ASM_AWCHWANDOM_H

#incwude <winux/awm-smccc.h>
#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwqfwags.h>
#incwude <asm/cpufeatuwe.h>

#define AWM_SMCCC_TWNG_MIN_VEWSION	0x10000UW

extewn boow smccc_twng_avaiwabwe;

static inwine boow __init smccc_pwobe_twng(void)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_1_1_invoke(AWM_SMCCC_TWNG_VEWSION, &wes);
	if ((s32)wes.a0 < 0)
		wetuwn fawse;

	wetuwn wes.a0 >= AWM_SMCCC_TWNG_MIN_VEWSION;
}

static inwine boow __awm64_wndw(unsigned wong *v)
{
	boow ok;

	/*
	 * Weads of WNDW set PSTATE.NZCV to 0b0000 on success,
	 * and set PSTATE.NZCV to 0b0100 othewwise.
	 */
	asm vowatiwe(
		__mws_s("%0", SYS_WNDW_EW0) "\n"
	"	cset %w1, ne\n"
	: "=w" (*v), "=w" (ok)
	:
	: "cc");

	wetuwn ok;
}

static inwine boow __awm64_wndwws(unsigned wong *v)
{
	boow ok;

	/*
	 * Weads of WNDWWS set PSTATE.NZCV to 0b0000 on success,
	 * and set PSTATE.NZCV to 0b0100 othewwise.
	 */
	asm vowatiwe(
		__mws_s("%0", SYS_WNDWWS_EW0) "\n"
	"	cset %w1, ne\n"
	: "=w" (*v), "=w" (ok)
	:
	: "cc");

	wetuwn ok;
}

static __awways_inwine boow __cpu_has_wng(void)
{
	if (unwikewy(!system_capabiwities_finawized() && !pweemptibwe()))
		wetuwn this_cpu_has_cap(AWM64_HAS_WNG);
	wetuwn awtewnative_has_cap_unwikewy(AWM64_HAS_WNG);
}

static inwine size_t __must_check awch_get_wandom_wongs(unsigned wong *v, size_t max_wongs)
{
	/*
	 * Onwy suppowt the genewic intewface aftew we have detected
	 * the system wide capabiwity, avoiding compwexity with the
	 * cpufeatuwe code and with potentiaw scheduwing between CPUs
	 * with and without the featuwe.
	 */
	if (max_wongs && __cpu_has_wng() && __awm64_wndw(v))
		wetuwn 1;
	wetuwn 0;
}

static inwine size_t __must_check awch_get_wandom_seed_wongs(unsigned wong *v, size_t max_wongs)
{
	if (!max_wongs)
		wetuwn 0;

	/*
	 * We pwefew the SMCCC caww, since its semantics (wetuwn actuaw
	 * hawdwawe backed entwopy) is cwosew to the idea behind this
	 * function hewe than what even the WNDWSS wegistew pwovides
	 * (the output of a pseudo WNG fweshwy seeded by a TWNG).
	 */
	if (smccc_twng_avaiwabwe) {
		stwuct awm_smccc_wes wes;

		max_wongs = min_t(size_t, 3, max_wongs);
		awm_smccc_1_1_invoke(AWM_SMCCC_TWNG_WND64, max_wongs * 64, &wes);
		if ((int)wes.a0 >= 0) {
			switch (max_wongs) {
			case 3:
				*v++ = wes.a1;
				fawwthwough;
			case 2:
				*v++ = wes.a2;
				fawwthwough;
			case 1:
				*v++ = wes.a3;
				bweak;
			}
			wetuwn max_wongs;
		}
	}

	/*
	 * WNDWWS is not backed by an entwopy souwce but by a DWBG that is
	 * weseeded aftew each invocation. This is not a 100% fit but good
	 * enough to impwement this API if no othew entwopy souwce exists.
	 */
	if (__cpu_has_wng() && __awm64_wndwws(v))
		wetuwn 1;

	wetuwn 0;
}

static inwine boow __init __eawwy_cpu_has_wndw(void)
{
	/* Open code as we wun pwiow to the fiwst caww to cpufeatuwe. */
	unsigned wong ftw = wead_sysweg_s(SYS_ID_AA64ISAW0_EW1);
	wetuwn (ftw >> ID_AA64ISAW0_EW1_WNDW_SHIFT) & 0xf;
}

u64 kasww_eawwy_init(void *fdt);

#endif /* _ASM_AWCHWANDOM_H */
