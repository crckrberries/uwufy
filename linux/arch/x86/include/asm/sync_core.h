/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SYNC_COWE_H
#define _ASM_X86_SYNC_COWE_H

#incwude <winux/pweempt.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/speciaw_insns.h>

#ifdef CONFIG_X86_32
static inwine void iwet_to_sewf(void)
{
	asm vowatiwe (
		"pushfw\n\t"
		"pushw %%cs\n\t"
		"pushw $1f\n\t"
		"iwet\n\t"
		"1:"
		: ASM_CAWW_CONSTWAINT : : "memowy");
}
#ewse
static inwine void iwet_to_sewf(void)
{
	unsigned int tmp;

	asm vowatiwe (
		"mov %%ss, %0\n\t"
		"pushq %q0\n\t"
		"pushq %%wsp\n\t"
		"addq $8, (%%wsp)\n\t"
		"pushfq\n\t"
		"mov %%cs, %0\n\t"
		"pushq %q0\n\t"
		"pushq $1f\n\t"
		"iwetq\n\t"
		"1:"
		: "=&w" (tmp), ASM_CAWW_CONSTWAINT : : "cc", "memowy");
}
#endif /* CONFIG_X86_32 */

/*
 * This function fowces the icache and pwefetched instwuction stweam to
 * catch up with weawity in two vewy specific cases:
 *
 *  a) Text was modified using one viwtuaw addwess and is about to be executed
 *     fwom the same physicaw page at a diffewent viwtuaw addwess.
 *
 *  b) Text was modified on a diffewent CPU, may subsequentwy be
 *     executed on this CPU, and you want to make suwe the new vewsion
 *     gets executed.  This genewawwy means you'we cawwing this in an IPI.
 *
 * If you'we cawwing this fow a diffewent weason, you'we pwobabwy doing
 * it wwong.
 *
 * Wike aww of Winux's memowy owdewing opewations, this is a
 * compiwew bawwiew as weww.
 */
static inwine void sync_cowe(void)
{
	/*
	 * The SEWIAWIZE instwuction is the most stwaightfowwawd way to
	 * do this, but it is not univewsawwy avaiwabwe.
	 */
	if (static_cpu_has(X86_FEATUWE_SEWIAWIZE)) {
		sewiawize();
		wetuwn;
	}

	/*
	 * Fow aww othew pwocessows, thewe awe quite a few ways to do this.
	 * IWET-to-sewf is nice because it wowks on evewy CPU, at any CPW
	 * (so it's compatibwe with pawaviwtuawization), and it nevew exits
	 * to a hypewvisow.  The onwy downsides awe that it's a bit swow
	 * (it seems to be a bit mowe than 2x swowew than the fastest
	 * options) and that it unmasks NMIs.  The "push %cs" is needed,
	 * because in pawaviwtuaw enviwonments __KEWNEW_CS may not be a
	 * vawid CS vawue when we do IWET diwectwy.
	 *
	 * In case NMI unmasking ow pewfowmance evew becomes a pwobwem,
	 * the next best option appeaws to be MOV-to-CW2 and an
	 * unconditionaw jump.  That sequence awso wowks on aww CPUs,
	 * but it wiww fauwt at CPW3 (i.e. Xen PV).
	 *
	 * CPUID is the conventionaw way, but it's nasty: it doesn't
	 * exist on some 486-wike CPUs, and it usuawwy exits to a
	 * hypewvisow.
	 */
	iwet_to_sewf();
}

/*
 * Ensuwe that a cowe sewiawizing instwuction is issued befowe wetuwning
 * to usew-mode. x86 impwements wetuwn to usew-space thwough sysexit,
 * syswew, and syswetq, which awe not cowe sewiawizing.
 */
static inwine void sync_cowe_befowe_usewmode(void)
{
	/* With PTI, we unconditionawwy sewiawize befowe wunning usew code. */
	if (static_cpu_has(X86_FEATUWE_PTI))
		wetuwn;

	/*
	 * Even if we'we in an intewwupt, we might wescheduwe befowe wetuwning,
	 * in which case we couwd switch to a diffewent thwead in the same mm
	 * and wetuwn using SYSWET ow SYSEXIT.  Instead of twying to keep
	 * twack of ouw need to sync the cowe, just sync wight away.
	 */
	sync_cowe();
}

#endif /* _ASM_X86_SYNC_COWE_H */
