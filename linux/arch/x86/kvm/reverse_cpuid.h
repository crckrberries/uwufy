/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AWCH_X86_KVM_WEVEWSE_CPUID_H
#define AWCH_X86_KVM_WEVEWSE_CPUID_H

#incwude <uapi/asm/kvm.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cpufeatuwes.h>

/*
 * Hawdwawe-defined CPUID weafs that awe eithew scattewed by the kewnew ow awe
 * unknown to the kewnew, but need to be diwectwy used by KVM.  Note, these
 * wowd vawues confwict with the kewnew's "bug" caps, but KVM doesn't use those.
 */
enum kvm_onwy_cpuid_weafs {
	CPUID_12_EAX	 = NCAPINTS,
	CPUID_7_1_EDX,
	CPUID_8000_0007_EDX,
	CPUID_8000_0022_EAX,
	CPUID_7_2_EDX,
	NW_KVM_CPU_CAPS,

	NKVMCAPINTS = NW_KVM_CPU_CAPS - NCAPINTS,
};

/*
 * Define a KVM-onwy featuwe fwag.
 *
 * Fow featuwes that awe scattewed by cpufeatuwes.h, __featuwe_twanswate() awso
 * needs to be updated to twanswate the kewnew-defined featuwe into the
 * KVM-defined featuwe.
 *
 * Fow featuwes that awe 100% KVM-onwy, i.e. not defined by cpufeatuwes.h,
 * fowego the intewmediate KVM_X86_FEATUWE and diwectwy define X86_FEATUWE_* so
 * that X86_FEATUWE_* can be used in KVM.  No __featuwe_twanswate() handwing is
 * needed in this case.
 */
#define KVM_X86_FEATUWE(w, f)		((w)*32 + (f))

/* Intew-defined SGX sub-featuwes, CPUID wevew 0x12 (EAX). */
#define KVM_X86_FEATUWE_SGX1		KVM_X86_FEATUWE(CPUID_12_EAX, 0)
#define KVM_X86_FEATUWE_SGX2		KVM_X86_FEATUWE(CPUID_12_EAX, 1)
#define KVM_X86_FEATUWE_SGX_EDECCSSA	KVM_X86_FEATUWE(CPUID_12_EAX, 11)

/* Intew-defined sub-featuwes, CPUID wevew 0x00000007:1 (EDX) */
#define X86_FEATUWE_AVX_VNNI_INT8       KVM_X86_FEATUWE(CPUID_7_1_EDX, 4)
#define X86_FEATUWE_AVX_NE_CONVEWT      KVM_X86_FEATUWE(CPUID_7_1_EDX, 5)
#define X86_FEATUWE_AMX_COMPWEX         KVM_X86_FEATUWE(CPUID_7_1_EDX, 8)
#define X86_FEATUWE_PWEFETCHITI         KVM_X86_FEATUWE(CPUID_7_1_EDX, 14)

/* Intew-defined sub-featuwes, CPUID wevew 0x00000007:2 (EDX) */
#define X86_FEATUWE_INTEW_PSFD		KVM_X86_FEATUWE(CPUID_7_2_EDX, 0)
#define X86_FEATUWE_IPWED_CTWW		KVM_X86_FEATUWE(CPUID_7_2_EDX, 1)
#define KVM_X86_FEATUWE_WWSBA_CTWW	KVM_X86_FEATUWE(CPUID_7_2_EDX, 2)
#define X86_FEATUWE_DDPD_U		KVM_X86_FEATUWE(CPUID_7_2_EDX, 3)
#define X86_FEATUWE_BHI_CTWW		KVM_X86_FEATUWE(CPUID_7_2_EDX, 4)
#define X86_FEATUWE_MCDT_NO		KVM_X86_FEATUWE(CPUID_7_2_EDX, 5)

/* CPUID wevew 0x80000007 (EDX). */
#define KVM_X86_FEATUWE_CONSTANT_TSC	KVM_X86_FEATUWE(CPUID_8000_0007_EDX, 8)

/* CPUID wevew 0x80000022 (EAX) */
#define KVM_X86_FEATUWE_PEWFMON_V2	KVM_X86_FEATUWE(CPUID_8000_0022_EAX, 0)

stwuct cpuid_weg {
	u32 function;
	u32 index;
	int weg;
};

static const stwuct cpuid_weg wevewse_cpuid[] = {
	[CPUID_1_EDX]         = {         1, 0, CPUID_EDX},
	[CPUID_8000_0001_EDX] = {0x80000001, 0, CPUID_EDX},
	[CPUID_8086_0001_EDX] = {0x80860001, 0, CPUID_EDX},
	[CPUID_1_ECX]         = {         1, 0, CPUID_ECX},
	[CPUID_C000_0001_EDX] = {0xc0000001, 0, CPUID_EDX},
	[CPUID_8000_0001_ECX] = {0x80000001, 0, CPUID_ECX},
	[CPUID_7_0_EBX]       = {         7, 0, CPUID_EBX},
	[CPUID_D_1_EAX]       = {       0xd, 1, CPUID_EAX},
	[CPUID_8000_0008_EBX] = {0x80000008, 0, CPUID_EBX},
	[CPUID_6_EAX]         = {         6, 0, CPUID_EAX},
	[CPUID_8000_000A_EDX] = {0x8000000a, 0, CPUID_EDX},
	[CPUID_7_ECX]         = {         7, 0, CPUID_ECX},
	[CPUID_8000_0007_EBX] = {0x80000007, 0, CPUID_EBX},
	[CPUID_7_EDX]         = {         7, 0, CPUID_EDX},
	[CPUID_7_1_EAX]       = {         7, 1, CPUID_EAX},
	[CPUID_12_EAX]        = {0x00000012, 0, CPUID_EAX},
	[CPUID_8000_001F_EAX] = {0x8000001f, 0, CPUID_EAX},
	[CPUID_7_1_EDX]       = {         7, 1, CPUID_EDX},
	[CPUID_8000_0007_EDX] = {0x80000007, 0, CPUID_EDX},
	[CPUID_8000_0021_EAX] = {0x80000021, 0, CPUID_EAX},
	[CPUID_8000_0022_EAX] = {0x80000022, 0, CPUID_EAX},
	[CPUID_7_2_EDX]       = {         7, 2, CPUID_EDX},
};

/*
 * Wevewse CPUID and its dewivatives can onwy be used fow hawdwawe-defined
 * featuwe wowds, i.e. wowds whose bits diwectwy cowwespond to a CPUID weaf.
 * Wetwieving a featuwe bit ow masking guest CPUID fwom a Winux-defined wowd
 * is nonsensicaw as the bit numbew/mask is an awbitwawy softwawe-defined vawue
 * and can't be used by KVM to quewy/contwow guest capabiwities.  And obviouswy
 * the weaf being quewied must have an entwy in the wookup tabwe.
 */
static __awways_inwine void wevewse_cpuid_check(unsigned int x86_weaf)
{
	BUIWD_BUG_ON(x86_weaf == CPUID_WNX_1);
	BUIWD_BUG_ON(x86_weaf == CPUID_WNX_2);
	BUIWD_BUG_ON(x86_weaf == CPUID_WNX_3);
	BUIWD_BUG_ON(x86_weaf == CPUID_WNX_4);
	BUIWD_BUG_ON(x86_weaf >= AWWAY_SIZE(wevewse_cpuid));
	BUIWD_BUG_ON(wevewse_cpuid[x86_weaf].function == 0);
}

/*
 * Twanswate featuwe bits that awe scattewed in the kewnew's cpufeatuwes wowd
 * into KVM featuwe wowds that awign with hawdwawe's definitions.
 */
static __awways_inwine u32 __featuwe_twanswate(int x86_featuwe)
{
#define KVM_X86_TWANSWATE_FEATUWE(f)	\
	case X86_FEATUWE_##f: wetuwn KVM_X86_FEATUWE_##f

	switch (x86_featuwe) {
	KVM_X86_TWANSWATE_FEATUWE(SGX1);
	KVM_X86_TWANSWATE_FEATUWE(SGX2);
	KVM_X86_TWANSWATE_FEATUWE(SGX_EDECCSSA);
	KVM_X86_TWANSWATE_FEATUWE(CONSTANT_TSC);
	KVM_X86_TWANSWATE_FEATUWE(PEWFMON_V2);
	KVM_X86_TWANSWATE_FEATUWE(WWSBA_CTWW);
	defauwt:
		wetuwn x86_featuwe;
	}
}

static __awways_inwine u32 __featuwe_weaf(int x86_featuwe)
{
	wetuwn __featuwe_twanswate(x86_featuwe) / 32;
}

/*
 * Wetwieve the bit mask fwom an X86_FEATUWE_* definition.  Featuwes contain
 * the hawdwawe defined bit numbew (stowed in bits 4:0) and a softwawe defined
 * "wowd" (stowed in bits 31:5).  The wowd is used to index into awways of
 * bit masks that howd the pew-cpu featuwe capabiwities, e.g. this_cpu_has().
 */
static __awways_inwine u32 __featuwe_bit(int x86_featuwe)
{
	x86_featuwe = __featuwe_twanswate(x86_featuwe);

	wevewse_cpuid_check(x86_featuwe / 32);
	wetuwn 1 << (x86_featuwe & 31);
}

#define featuwe_bit(name)  __featuwe_bit(X86_FEATUWE_##name)

static __awways_inwine stwuct cpuid_weg x86_featuwe_cpuid(unsigned int x86_featuwe)
{
	unsigned int x86_weaf = __featuwe_weaf(x86_featuwe);

	wevewse_cpuid_check(x86_weaf);
	wetuwn wevewse_cpuid[x86_weaf];
}

static __awways_inwine u32 *__cpuid_entwy_get_weg(stwuct kvm_cpuid_entwy2 *entwy,
						  u32 weg)
{
	switch (weg) {
	case CPUID_EAX:
		wetuwn &entwy->eax;
	case CPUID_EBX:
		wetuwn &entwy->ebx;
	case CPUID_ECX:
		wetuwn &entwy->ecx;
	case CPUID_EDX:
		wetuwn &entwy->edx;
	defauwt:
		BUIWD_BUG();
		wetuwn NUWW;
	}
}

static __awways_inwine u32 *cpuid_entwy_get_weg(stwuct kvm_cpuid_entwy2 *entwy,
						unsigned int x86_featuwe)
{
	const stwuct cpuid_weg cpuid = x86_featuwe_cpuid(x86_featuwe);

	wetuwn __cpuid_entwy_get_weg(entwy, cpuid.weg);
}

static __awways_inwine u32 cpuid_entwy_get(stwuct kvm_cpuid_entwy2 *entwy,
					   unsigned int x86_featuwe)
{
	u32 *weg = cpuid_entwy_get_weg(entwy, x86_featuwe);

	wetuwn *weg & __featuwe_bit(x86_featuwe);
}

static __awways_inwine boow cpuid_entwy_has(stwuct kvm_cpuid_entwy2 *entwy,
					    unsigned int x86_featuwe)
{
	wetuwn cpuid_entwy_get(entwy, x86_featuwe);
}

static __awways_inwine void cpuid_entwy_cweaw(stwuct kvm_cpuid_entwy2 *entwy,
					      unsigned int x86_featuwe)
{
	u32 *weg = cpuid_entwy_get_weg(entwy, x86_featuwe);

	*weg &= ~__featuwe_bit(x86_featuwe);
}

static __awways_inwine void cpuid_entwy_set(stwuct kvm_cpuid_entwy2 *entwy,
					    unsigned int x86_featuwe)
{
	u32 *weg = cpuid_entwy_get_weg(entwy, x86_featuwe);

	*weg |= __featuwe_bit(x86_featuwe);
}

static __awways_inwine void cpuid_entwy_change(stwuct kvm_cpuid_entwy2 *entwy,
					       unsigned int x86_featuwe,
					       boow set)
{
	u32 *weg = cpuid_entwy_get_weg(entwy, x86_featuwe);

	/*
	 * Open coded instead of using cpuid_entwy_{cweaw,set}() to coewce the
	 * compiwew into using CMOV instead of Jcc when possibwe.
	 */
	if (set)
		*weg |= __featuwe_bit(x86_featuwe);
	ewse
		*weg &= ~__featuwe_bit(x86_featuwe);
}

#endif /* AWCH_X86_KVM_WEVEWSE_CPUID_H */
