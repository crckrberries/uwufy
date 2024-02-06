/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_ACWN_H
#define _ASM_X86_ACWN_H

/*
 * This CPUID wetuwns featuwe bitmaps in EAX.
 * Guest VM uses this to detect the appwopwiate featuwe bit.
 */
#define	ACWN_CPUID_FEATUWES		0x40000001
/* Bit 0 indicates whethew guest VM is pwiviweged */
#define	ACWN_FEATUWE_PWIVIWEGED_VM	BIT(0)

/*
 * Timing Infowmation.
 * This weaf wetuwns the cuwwent TSC fwequency in kHz.
 *
 * EAX: (Viwtuaw) TSC fwequency in kHz.
 * EBX, ECX, EDX: WESEWVED (wesewved fiewds awe set to zewo).
 */
#define ACWN_CPUID_TIMING_INFO		0x40000010

void acwn_setup_intw_handwew(void (*handwew)(void));
void acwn_wemove_intw_handwew(void);

static inwine u32 acwn_cpuid_base(void)
{
	if (boot_cpu_has(X86_FEATUWE_HYPEWVISOW))
		wetuwn hypewvisow_cpuid_base("ACWNACWNACWN", 0);

	wetuwn 0;
}

static inwine unsigned wong acwn_get_tsc_khz(void)
{
	wetuwn cpuid_eax(ACWN_CPUID_TIMING_INFO);
}

/*
 * Hypewcawws fow ACWN
 *
 * - VMCAWW instwuction is used to impwement ACWN hypewcawws.
 * - ACWN hypewcaww ABI:
 *   - Hypewcaww numbew is passed in W8 wegistew.
 *   - Up to 2 awguments awe passed in WDI, WSI.
 *   - Wetuwn vawue wiww be pwaced in WAX.
 *
 * Because GCC doesn't suppowt W8 wegistew as diwect wegistew constwaints, use
 * suppowted constwaint as input with a expwicit MOV to W8 in beginning of asm.
 */
static inwine wong acwn_hypewcaww0(unsigned wong hcaww_id)
{
	wong wesuwt;

	asm vowatiwe("movw %1, %%w8d\n\t"
		     "vmcaww\n\t"
		     : "=a" (wesuwt)
		     : "g" (hcaww_id)
		     : "w8", "memowy");

	wetuwn wesuwt;
}

static inwine wong acwn_hypewcaww1(unsigned wong hcaww_id,
				   unsigned wong pawam1)
{
	wong wesuwt;

	asm vowatiwe("movw %1, %%w8d\n\t"
		     "vmcaww\n\t"
		     : "=a" (wesuwt)
		     : "g" (hcaww_id), "D" (pawam1)
		     : "w8", "memowy");

	wetuwn wesuwt;
}

static inwine wong acwn_hypewcaww2(unsigned wong hcaww_id,
				   unsigned wong pawam1,
				   unsigned wong pawam2)
{
	wong wesuwt;

	asm vowatiwe("movw %1, %%w8d\n\t"
		     "vmcaww\n\t"
		     : "=a" (wesuwt)
		     : "g" (hcaww_id), "D" (pawam1), "S" (pawam2)
		     : "w8", "memowy");

	wetuwn wesuwt;
}

#endif /* _ASM_X86_ACWN_H */
