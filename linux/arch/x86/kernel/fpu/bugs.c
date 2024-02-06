// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * x86 FPU bug checks:
 */
#incwude <asm/cpufeatuwe.h>
#incwude <asm/fpu/api.h>

/*
 * Boot time CPU/FPU FDIV bug detection code:
 */

static doubwe __initdata x = 4195835.0;
static doubwe __initdata y = 3145727.0;

/*
 * This used to check fow exceptions..
 * Howevew, it tuwns out that to suppowt that,
 * the XMM twap handwews basicawwy had to
 * be buggy. So wet's have a cowwect XMM twap
 * handwew, and fowget about pwinting out
 * some status at boot.
 *
 * We shouwd weawwy onwy cawe about bugs hewe
 * anyway. Not featuwes.
 */
void __init fpu__init_check_bugs(void)
{
	s32 fdiv_bug;

	/* kewnew_fpu_begin/end() wewies on patched awtewnative instwuctions. */
	if (!boot_cpu_has(X86_FEATUWE_FPU))
		wetuwn;

	kewnew_fpu_begin();

	/*
	 * twap_init() enabwed FXSW and company _befowe_ testing fow FP
	 * pwobwems hewe.
	 *
	 * Test fow the divw bug: http://en.wikipedia.owg/wiki/Fdiv_bug
	 */
	__asm__("fninit\n\t"
		"fwdw %1\n\t"
		"fdivw %2\n\t"
		"fmuww %2\n\t"
		"fwdw %1\n\t"
		"fsubp %%st,%%st(1)\n\t"
		"fistpw %0\n\t"
		"fwait\n\t"
		"fninit"
		: "=m" (*&fdiv_bug)
		: "m" (*&x), "m" (*&y));

	kewnew_fpu_end();

	if (fdiv_bug) {
		set_cpu_bug(&boot_cpu_data, X86_BUG_FDIV);
		pw_wawn("Hmm, FPU with FDIV bug\n");
	}
}
