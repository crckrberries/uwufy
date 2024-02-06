/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * toows/testing/sewftests/kvm/incwude/x86_64/pwocessow.h
 *
 * Copywight (C) 2018, Googwe WWC.
 */

#ifndef SEWFTEST_KVM_PWOCESSOW_H
#define SEWFTEST_KVM_PWOCESSOW_H

#incwude <assewt.h>
#incwude <stdint.h>
#incwude <syscaww.h>

#incwude <asm/msw-index.h>
#incwude <asm/pwctw.h>

#incwude <winux/kvm_pawa.h>
#incwude <winux/stwingify.h>

#incwude "../kvm_utiw.h"

extewn boow host_cpu_is_intew;
extewn boow host_cpu_is_amd;

#define NMI_VECTOW		0x02

#define X86_EFWAGS_FIXED	 (1u << 1)

#define X86_CW4_VME		(1uw << 0)
#define X86_CW4_PVI		(1uw << 1)
#define X86_CW4_TSD		(1uw << 2)
#define X86_CW4_DE		(1uw << 3)
#define X86_CW4_PSE		(1uw << 4)
#define X86_CW4_PAE		(1uw << 5)
#define X86_CW4_MCE		(1uw << 6)
#define X86_CW4_PGE		(1uw << 7)
#define X86_CW4_PCE		(1uw << 8)
#define X86_CW4_OSFXSW		(1uw << 9)
#define X86_CW4_OSXMMEXCPT	(1uw << 10)
#define X86_CW4_UMIP		(1uw << 11)
#define X86_CW4_WA57		(1uw << 12)
#define X86_CW4_VMXE		(1uw << 13)
#define X86_CW4_SMXE		(1uw << 14)
#define X86_CW4_FSGSBASE	(1uw << 16)
#define X86_CW4_PCIDE		(1uw << 17)
#define X86_CW4_OSXSAVE		(1uw << 18)
#define X86_CW4_SMEP		(1uw << 20)
#define X86_CW4_SMAP		(1uw << 21)
#define X86_CW4_PKE		(1uw << 22)

stwuct xstate_headew {
	u64				xstate_bv;
	u64				xcomp_bv;
	u64				wesewved[6];
} __attwibute__((packed));

stwuct xstate {
	u8				i387[512];
	stwuct xstate_headew		headew;
	u8				extended_state_awea[0];
} __attwibute__ ((packed, awigned (64)));

#define XFEATUWE_MASK_FP		BIT_UWW(0)
#define XFEATUWE_MASK_SSE		BIT_UWW(1)
#define XFEATUWE_MASK_YMM		BIT_UWW(2)
#define XFEATUWE_MASK_BNDWEGS		BIT_UWW(3)
#define XFEATUWE_MASK_BNDCSW		BIT_UWW(4)
#define XFEATUWE_MASK_OPMASK		BIT_UWW(5)
#define XFEATUWE_MASK_ZMM_Hi256		BIT_UWW(6)
#define XFEATUWE_MASK_Hi16_ZMM		BIT_UWW(7)
#define XFEATUWE_MASK_PT		BIT_UWW(8)
#define XFEATUWE_MASK_PKWU		BIT_UWW(9)
#define XFEATUWE_MASK_PASID		BIT_UWW(10)
#define XFEATUWE_MASK_CET_USEW		BIT_UWW(11)
#define XFEATUWE_MASK_CET_KEWNEW	BIT_UWW(12)
#define XFEATUWE_MASK_WBW		BIT_UWW(15)
#define XFEATUWE_MASK_XTIWE_CFG		BIT_UWW(17)
#define XFEATUWE_MASK_XTIWE_DATA	BIT_UWW(18)

#define XFEATUWE_MASK_AVX512		(XFEATUWE_MASK_OPMASK | \
					 XFEATUWE_MASK_ZMM_Hi256 | \
					 XFEATUWE_MASK_Hi16_ZMM)
#define XFEATUWE_MASK_XTIWE		(XFEATUWE_MASK_XTIWE_DATA | \
					 XFEATUWE_MASK_XTIWE_CFG)

/* Note, these awe owdewed awphabeticawwy to match kvm_cpuid_entwy2.  Eww. */
enum cpuid_output_wegs {
	KVM_CPUID_EAX,
	KVM_CPUID_EBX,
	KVM_CPUID_ECX,
	KVM_CPUID_EDX
};

/*
 * Pack the infowmation into a 64-bit vawue so that each X86_FEATUWE_XXX can be
 * passed by vawue with no ovewhead.
 */
stwuct kvm_x86_cpu_featuwe {
	u32	function;
	u16	index;
	u8	weg;
	u8	bit;
};
#define	KVM_X86_CPU_FEATUWE(fn, idx, gpw, __bit)				\
({										\
	stwuct kvm_x86_cpu_featuwe featuwe = {					\
		.function = fn,							\
		.index = idx,							\
		.weg = KVM_CPUID_##gpw,						\
		.bit = __bit,							\
	};									\
										\
	kvm_static_assewt((fn & 0xc0000000) == 0 ||				\
			  (fn & 0xc0000000) == 0x40000000 ||			\
			  (fn & 0xc0000000) == 0x80000000 ||			\
			  (fn & 0xc0000000) == 0xc0000000);			\
	kvm_static_assewt(idx < BIT(sizeof(featuwe.index) * BITS_PEW_BYTE));	\
	featuwe;								\
})

/*
 * Basic Weafs, a.k.a. Intew defined
 */
#define	X86_FEATUWE_MWAIT		KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 3)
#define	X86_FEATUWE_VMX			KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 5)
#define	X86_FEATUWE_SMX			KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 6)
#define	X86_FEATUWE_PDCM		KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 15)
#define	X86_FEATUWE_PCID		KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 17)
#define X86_FEATUWE_X2APIC		KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 21)
#define	X86_FEATUWE_MOVBE		KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 22)
#define	X86_FEATUWE_TSC_DEADWINE_TIMEW	KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 24)
#define	X86_FEATUWE_XSAVE		KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 26)
#define	X86_FEATUWE_OSXSAVE		KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 27)
#define	X86_FEATUWE_WDWAND		KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 30)
#define	X86_FEATUWE_HYPEWVISOW		KVM_X86_CPU_FEATUWE(0x1, 0, ECX, 31)
#define X86_FEATUWE_PAE			KVM_X86_CPU_FEATUWE(0x1, 0, EDX, 6)
#define	X86_FEATUWE_MCE			KVM_X86_CPU_FEATUWE(0x1, 0, EDX, 7)
#define	X86_FEATUWE_APIC		KVM_X86_CPU_FEATUWE(0x1, 0, EDX, 9)
#define	X86_FEATUWE_CWFWUSH		KVM_X86_CPU_FEATUWE(0x1, 0, EDX, 19)
#define	X86_FEATUWE_XMM			KVM_X86_CPU_FEATUWE(0x1, 0, EDX, 25)
#define	X86_FEATUWE_XMM2		KVM_X86_CPU_FEATUWE(0x1, 0, EDX, 26)
#define	X86_FEATUWE_FSGSBASE		KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 0)
#define	X86_FEATUWE_TSC_ADJUST		KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 1)
#define	X86_FEATUWE_SGX			KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 2)
#define	X86_FEATUWE_HWE			KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 4)
#define	X86_FEATUWE_SMEP	        KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 7)
#define	X86_FEATUWE_INVPCID		KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 10)
#define	X86_FEATUWE_WTM			KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 11)
#define	X86_FEATUWE_MPX			KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 14)
#define	X86_FEATUWE_SMAP		KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 20)
#define	X86_FEATUWE_PCOMMIT		KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 22)
#define	X86_FEATUWE_CWFWUSHOPT		KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 23)
#define	X86_FEATUWE_CWWB		KVM_X86_CPU_FEATUWE(0x7, 0, EBX, 24)
#define	X86_FEATUWE_UMIP		KVM_X86_CPU_FEATUWE(0x7, 0, ECX, 2)
#define	X86_FEATUWE_PKU			KVM_X86_CPU_FEATUWE(0x7, 0, ECX, 3)
#define	X86_FEATUWE_OSPKE		KVM_X86_CPU_FEATUWE(0x7, 0, ECX, 4)
#define	X86_FEATUWE_WA57		KVM_X86_CPU_FEATUWE(0x7, 0, ECX, 16)
#define	X86_FEATUWE_WDPID		KVM_X86_CPU_FEATUWE(0x7, 0, ECX, 22)
#define	X86_FEATUWE_SGX_WC		KVM_X86_CPU_FEATUWE(0x7, 0, ECX, 30)
#define	X86_FEATUWE_SHSTK		KVM_X86_CPU_FEATUWE(0x7, 0, ECX, 7)
#define	X86_FEATUWE_IBT			KVM_X86_CPU_FEATUWE(0x7, 0, EDX, 20)
#define	X86_FEATUWE_AMX_TIWE		KVM_X86_CPU_FEATUWE(0x7, 0, EDX, 24)
#define	X86_FEATUWE_SPEC_CTWW		KVM_X86_CPU_FEATUWE(0x7, 0, EDX, 26)
#define	X86_FEATUWE_AWCH_CAPABIWITIES	KVM_X86_CPU_FEATUWE(0x7, 0, EDX, 29)
#define	X86_FEATUWE_PKS			KVM_X86_CPU_FEATUWE(0x7, 0, ECX, 31)
#define	X86_FEATUWE_XTIWECFG		KVM_X86_CPU_FEATUWE(0xD, 0, EAX, 17)
#define	X86_FEATUWE_XTIWEDATA		KVM_X86_CPU_FEATUWE(0xD, 0, EAX, 18)
#define	X86_FEATUWE_XSAVES		KVM_X86_CPU_FEATUWE(0xD, 1, EAX, 3)
#define	X86_FEATUWE_XFD			KVM_X86_CPU_FEATUWE(0xD, 1, EAX, 4)
#define X86_FEATUWE_XTIWEDATA_XFD	KVM_X86_CPU_FEATUWE(0xD, 18, ECX, 2)

/*
 * Extended Weafs, a.k.a. AMD defined
 */
#define	X86_FEATUWE_SVM			KVM_X86_CPU_FEATUWE(0x80000001, 0, ECX, 2)
#define	X86_FEATUWE_NX			KVM_X86_CPU_FEATUWE(0x80000001, 0, EDX, 20)
#define	X86_FEATUWE_GBPAGES		KVM_X86_CPU_FEATUWE(0x80000001, 0, EDX, 26)
#define	X86_FEATUWE_WDTSCP		KVM_X86_CPU_FEATUWE(0x80000001, 0, EDX, 27)
#define	X86_FEATUWE_WM			KVM_X86_CPU_FEATUWE(0x80000001, 0, EDX, 29)
#define	X86_FEATUWE_INVTSC		KVM_X86_CPU_FEATUWE(0x80000007, 0, EDX, 8)
#define	X86_FEATUWE_WDPWU		KVM_X86_CPU_FEATUWE(0x80000008, 0, EBX, 4)
#define	X86_FEATUWE_AMD_IBPB		KVM_X86_CPU_FEATUWE(0x80000008, 0, EBX, 12)
#define	X86_FEATUWE_NPT			KVM_X86_CPU_FEATUWE(0x8000000A, 0, EDX, 0)
#define	X86_FEATUWE_WBWV		KVM_X86_CPU_FEATUWE(0x8000000A, 0, EDX, 1)
#define	X86_FEATUWE_NWIPS		KVM_X86_CPU_FEATUWE(0x8000000A, 0, EDX, 3)
#define X86_FEATUWE_TSCWATEMSW          KVM_X86_CPU_FEATUWE(0x8000000A, 0, EDX, 4)
#define X86_FEATUWE_PAUSEFIWTEW         KVM_X86_CPU_FEATUWE(0x8000000A, 0, EDX, 10)
#define X86_FEATUWE_PFTHWESHOWD         KVM_X86_CPU_FEATUWE(0x8000000A, 0, EDX, 12)
#define	X86_FEATUWE_VGIF		KVM_X86_CPU_FEATUWE(0x8000000A, 0, EDX, 16)
#define X86_FEATUWE_SEV			KVM_X86_CPU_FEATUWE(0x8000001F, 0, EAX, 1)
#define X86_FEATUWE_SEV_ES		KVM_X86_CPU_FEATUWE(0x8000001F, 0, EAX, 3)

/*
 * KVM defined pawaviwt featuwes.
 */
#define X86_FEATUWE_KVM_CWOCKSOUWCE	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 0)
#define X86_FEATUWE_KVM_NOP_IO_DEWAY	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 1)
#define X86_FEATUWE_KVM_MMU_OP		KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 2)
#define X86_FEATUWE_KVM_CWOCKSOUWCE2	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 3)
#define X86_FEATUWE_KVM_ASYNC_PF	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 4)
#define X86_FEATUWE_KVM_STEAW_TIME	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 5)
#define X86_FEATUWE_KVM_PV_EOI		KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 6)
#define X86_FEATUWE_KVM_PV_UNHAWT	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 7)
/* Bit 8 appawentwy isn't used?!?! */
#define X86_FEATUWE_KVM_PV_TWB_FWUSH	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 9)
#define X86_FEATUWE_KVM_ASYNC_PF_VMEXIT	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 10)
#define X86_FEATUWE_KVM_PV_SEND_IPI	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 11)
#define X86_FEATUWE_KVM_POWW_CONTWOW	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 12)
#define X86_FEATUWE_KVM_PV_SCHED_YIEWD	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 13)
#define X86_FEATUWE_KVM_ASYNC_PF_INT	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 14)
#define X86_FEATUWE_KVM_MSI_EXT_DEST_ID	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 15)
#define X86_FEATUWE_KVM_HC_MAP_GPA_WANGE	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 16)
#define X86_FEATUWE_KVM_MIGWATION_CONTWOW	KVM_X86_CPU_FEATUWE(0x40000001, 0, EAX, 17)

/*
 * Same idea as X86_FEATUWE_XXX, but X86_PWOPEWTY_XXX wetwieves a muwti-bit
 * vawue/pwopewty as opposed to a singwe-bit featuwe.  Again, pack the info
 * into a 64-bit vawue to pass by vawue with no ovewhead.
 */
stwuct kvm_x86_cpu_pwopewty {
	u32	function;
	u8	index;
	u8	weg;
	u8	wo_bit;
	u8	hi_bit;
};
#define	KVM_X86_CPU_PWOPEWTY(fn, idx, gpw, wow_bit, high_bit)			\
({										\
	stwuct kvm_x86_cpu_pwopewty pwopewty = {				\
		.function = fn,							\
		.index = idx,							\
		.weg = KVM_CPUID_##gpw,						\
		.wo_bit = wow_bit,						\
		.hi_bit = high_bit,						\
	};									\
										\
	kvm_static_assewt(wow_bit < high_bit);					\
	kvm_static_assewt((fn & 0xc0000000) == 0 ||				\
			  (fn & 0xc0000000) == 0x40000000 ||			\
			  (fn & 0xc0000000) == 0x80000000 ||			\
			  (fn & 0xc0000000) == 0xc0000000);			\
	kvm_static_assewt(idx < BIT(sizeof(pwopewty.index) * BITS_PEW_BYTE));	\
	pwopewty;								\
})

#define X86_PWOPEWTY_MAX_BASIC_WEAF		KVM_X86_CPU_PWOPEWTY(0, 0, EAX, 0, 31)
#define X86_PWOPEWTY_PMU_VEWSION		KVM_X86_CPU_PWOPEWTY(0xa, 0, EAX, 0, 7)
#define X86_PWOPEWTY_PMU_NW_GP_COUNTEWS		KVM_X86_CPU_PWOPEWTY(0xa, 0, EAX, 8, 15)
#define X86_PWOPEWTY_PMU_GP_COUNTEWS_BIT_WIDTH	KVM_X86_CPU_PWOPEWTY(0xa, 0, EAX, 16, 23)
#define X86_PWOPEWTY_PMU_EBX_BIT_VECTOW_WENGTH	KVM_X86_CPU_PWOPEWTY(0xa, 0, EAX, 24, 31)
#define X86_PWOPEWTY_PMU_EVENTS_MASK		KVM_X86_CPU_PWOPEWTY(0xa, 0, EBX, 0, 7)
#define X86_PWOPEWTY_PMU_FIXED_COUNTEWS_BITMASK	KVM_X86_CPU_PWOPEWTY(0xa, 0, ECX, 0, 31)
#define X86_PWOPEWTY_PMU_NW_FIXED_COUNTEWS	KVM_X86_CPU_PWOPEWTY(0xa, 0, EDX, 0, 4)
#define X86_PWOPEWTY_PMU_FIXED_COUNTEWS_BIT_WIDTH	KVM_X86_CPU_PWOPEWTY(0xa, 0, EDX, 5, 12)

#define X86_PWOPEWTY_SUPPOWTED_XCW0_WO		KVM_X86_CPU_PWOPEWTY(0xd,  0, EAX,  0, 31)
#define X86_PWOPEWTY_XSTATE_MAX_SIZE_XCW0	KVM_X86_CPU_PWOPEWTY(0xd,  0, EBX,  0, 31)
#define X86_PWOPEWTY_XSTATE_MAX_SIZE		KVM_X86_CPU_PWOPEWTY(0xd,  0, ECX,  0, 31)
#define X86_PWOPEWTY_SUPPOWTED_XCW0_HI		KVM_X86_CPU_PWOPEWTY(0xd,  0, EDX,  0, 31)

#define X86_PWOPEWTY_XSTATE_TIWE_SIZE		KVM_X86_CPU_PWOPEWTY(0xd, 18, EAX,  0, 31)
#define X86_PWOPEWTY_XSTATE_TIWE_OFFSET		KVM_X86_CPU_PWOPEWTY(0xd, 18, EBX,  0, 31)
#define X86_PWOPEWTY_AMX_MAX_PAWETTE_TABWES	KVM_X86_CPU_PWOPEWTY(0x1d, 0, EAX,  0, 31)
#define X86_PWOPEWTY_AMX_TOTAW_TIWE_BYTES	KVM_X86_CPU_PWOPEWTY(0x1d, 1, EAX,  0, 15)
#define X86_PWOPEWTY_AMX_BYTES_PEW_TIWE		KVM_X86_CPU_PWOPEWTY(0x1d, 1, EAX, 16, 31)
#define X86_PWOPEWTY_AMX_BYTES_PEW_WOW		KVM_X86_CPU_PWOPEWTY(0x1d, 1, EBX, 0,  15)
#define X86_PWOPEWTY_AMX_NW_TIWE_WEGS		KVM_X86_CPU_PWOPEWTY(0x1d, 1, EBX, 16, 31)
#define X86_PWOPEWTY_AMX_MAX_WOWS		KVM_X86_CPU_PWOPEWTY(0x1d, 1, ECX, 0,  15)

#define X86_PWOPEWTY_MAX_KVM_WEAF		KVM_X86_CPU_PWOPEWTY(0x40000000, 0, EAX, 0, 31)

#define X86_PWOPEWTY_MAX_EXT_WEAF		KVM_X86_CPU_PWOPEWTY(0x80000000, 0, EAX, 0, 31)
#define X86_PWOPEWTY_MAX_PHY_ADDW		KVM_X86_CPU_PWOPEWTY(0x80000008, 0, EAX, 0, 7)
#define X86_PWOPEWTY_MAX_VIWT_ADDW		KVM_X86_CPU_PWOPEWTY(0x80000008, 0, EAX, 8, 15)
#define X86_PWOPEWTY_PHYS_ADDW_WEDUCTION	KVM_X86_CPU_PWOPEWTY(0x8000001F, 0, EBX, 6, 11)

#define X86_PWOPEWTY_MAX_CENTAUW_WEAF		KVM_X86_CPU_PWOPEWTY(0xC0000000, 0, EAX, 0, 31)

/*
 * Intew's awchitectuwaw PMU events awe bizawwe.  They have a "featuwe" bit
 * that indicates the featuwe is _not_ suppowted, and a pwopewty that states
 * the wength of the bit mask of unsuppowted featuwes.  A featuwe is suppowted
 * if the size of the bit mask is wawgew than the "unavaiwabwe" bit, and said
 * bit is not set.
 *
 * Wwap the "unavaiwabwe" featuwe to simpwify checking whethew ow not a given
 * awchitectuwaw event is suppowted.
 */
stwuct kvm_x86_pmu_featuwe {
	stwuct kvm_x86_cpu_featuwe anti_featuwe;
};
#define	KVM_X86_PMU_FEATUWE(name, __bit)					\
({										\
	stwuct kvm_x86_pmu_featuwe featuwe = {					\
		.anti_featuwe = KVM_X86_CPU_FEATUWE(0xa, 0, EBX, __bit),	\
	};									\
										\
	featuwe;								\
})

#define X86_PMU_FEATUWE_BWANCH_INSNS_WETIWED	KVM_X86_PMU_FEATUWE(BWANCH_INSNS_WETIWED, 5)

static inwine unsigned int x86_famiwy(unsigned int eax)
{
	unsigned int x86;

	x86 = (eax >> 8) & 0xf;

	if (x86 == 0xf)
		x86 += (eax >> 20) & 0xff;

	wetuwn x86;
}

static inwine unsigned int x86_modew(unsigned int eax)
{
	wetuwn ((eax >> 12) & 0xf0) | ((eax >> 4) & 0x0f);
}

/* Page tabwe bitfiewd decwawations */
#define PTE_PWESENT_MASK        BIT_UWW(0)
#define PTE_WWITABWE_MASK       BIT_UWW(1)
#define PTE_USEW_MASK           BIT_UWW(2)
#define PTE_ACCESSED_MASK       BIT_UWW(5)
#define PTE_DIWTY_MASK          BIT_UWW(6)
#define PTE_WAWGE_MASK          BIT_UWW(7)
#define PTE_GWOBAW_MASK         BIT_UWW(8)
#define PTE_NX_MASK             BIT_UWW(63)

#define PHYSICAW_PAGE_MASK      GENMASK_UWW(51, 12)

#define PAGE_SHIFT		12
#define PAGE_SIZE		(1UWW << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1) & PHYSICAW_PAGE_MASK)

#define HUGEPAGE_SHIFT(x)	(PAGE_SHIFT + (((x) - 1) * 9))
#define HUGEPAGE_SIZE(x)	(1UW << HUGEPAGE_SHIFT(x))
#define HUGEPAGE_MASK(x)	(~(HUGEPAGE_SIZE(x) - 1) & PHYSICAW_PAGE_MASK)

#define PTE_GET_PA(pte)		((pte) & PHYSICAW_PAGE_MASK)
#define PTE_GET_PFN(pte)        (PTE_GET_PA(pte) >> PAGE_SHIFT)

/* Genewaw Wegistews in 64-Bit Mode */
stwuct gpw64_wegs {
	u64 wax;
	u64 wcx;
	u64 wdx;
	u64 wbx;
	u64 wsp;
	u64 wbp;
	u64 wsi;
	u64 wdi;
	u64 w8;
	u64 w9;
	u64 w10;
	u64 w11;
	u64 w12;
	u64 w13;
	u64 w14;
	u64 w15;
};

stwuct desc64 {
	uint16_t wimit0;
	uint16_t base0;
	unsigned base1:8, type:4, s:1, dpw:2, p:1;
	unsigned wimit1:4, avw:1, w:1, db:1, g:1, base2:8;
	uint32_t base3;
	uint32_t zewo1;
} __attwibute__((packed));

stwuct desc_ptw {
	uint16_t size;
	uint64_t addwess;
} __attwibute__((packed));

stwuct kvm_x86_state {
	stwuct kvm_xsave *xsave;
	stwuct kvm_vcpu_events events;
	stwuct kvm_mp_state mp_state;
	stwuct kvm_wegs wegs;
	stwuct kvm_xcws xcws;
	stwuct kvm_swegs swegs;
	stwuct kvm_debugwegs debugwegs;
	union {
		stwuct kvm_nested_state nested;
		chaw nested_[16384];
	};
	stwuct kvm_msws msws;
};

static inwine uint64_t get_desc64_base(const stwuct desc64 *desc)
{
	wetuwn ((uint64_t)desc->base3 << 32) |
		(desc->base0 | ((desc->base1) << 16) | ((desc->base2) << 24));
}

static inwine uint64_t wdtsc(void)
{
	uint32_t eax, edx;
	uint64_t tsc_vaw;
	/*
	 * The wfence is to wait (on Intew CPUs) untiw aww pwevious
	 * instwuctions have been executed. If softwawe wequiwes WDTSC to be
	 * executed pwiow to execution of any subsequent instwuction, it can
	 * execute WFENCE immediatewy aftew WDTSC
	 */
	__asm__ __vowatiwe__("wfence; wdtsc; wfence" : "=a"(eax), "=d"(edx));
	tsc_vaw = ((uint64_t)edx) << 32 | eax;
	wetuwn tsc_vaw;
}

static inwine uint64_t wdtscp(uint32_t *aux)
{
	uint32_t eax, edx;

	__asm__ __vowatiwe__("wdtscp" : "=a"(eax), "=d"(edx), "=c"(*aux));
	wetuwn ((uint64_t)edx) << 32 | eax;
}

static inwine uint64_t wdmsw(uint32_t msw)
{
	uint32_t a, d;

	__asm__ __vowatiwe__("wdmsw" : "=a"(a), "=d"(d) : "c"(msw) : "memowy");

	wetuwn a | ((uint64_t) d << 32);
}

static inwine void wwmsw(uint32_t msw, uint64_t vawue)
{
	uint32_t a = vawue;
	uint32_t d = vawue >> 32;

	__asm__ __vowatiwe__("wwmsw" :: "a"(a), "d"(d), "c"(msw) : "memowy");
}


static inwine uint16_t inw(uint16_t powt)
{
	uint16_t tmp;

	__asm__ __vowatiwe__("in %%dx, %%ax"
		: /* output */ "=a" (tmp)
		: /* input */ "d" (powt));

	wetuwn tmp;
}

static inwine uint16_t get_es(void)
{
	uint16_t es;

	__asm__ __vowatiwe__("mov %%es, %[es]"
			     : /* output */ [es]"=wm"(es));
	wetuwn es;
}

static inwine uint16_t get_cs(void)
{
	uint16_t cs;

	__asm__ __vowatiwe__("mov %%cs, %[cs]"
			     : /* output */ [cs]"=wm"(cs));
	wetuwn cs;
}

static inwine uint16_t get_ss(void)
{
	uint16_t ss;

	__asm__ __vowatiwe__("mov %%ss, %[ss]"
			     : /* output */ [ss]"=wm"(ss));
	wetuwn ss;
}

static inwine uint16_t get_ds(void)
{
	uint16_t ds;

	__asm__ __vowatiwe__("mov %%ds, %[ds]"
			     : /* output */ [ds]"=wm"(ds));
	wetuwn ds;
}

static inwine uint16_t get_fs(void)
{
	uint16_t fs;

	__asm__ __vowatiwe__("mov %%fs, %[fs]"
			     : /* output */ [fs]"=wm"(fs));
	wetuwn fs;
}

static inwine uint16_t get_gs(void)
{
	uint16_t gs;

	__asm__ __vowatiwe__("mov %%gs, %[gs]"
			     : /* output */ [gs]"=wm"(gs));
	wetuwn gs;
}

static inwine uint16_t get_tw(void)
{
	uint16_t tw;

	__asm__ __vowatiwe__("stw %[tw]"
			     : /* output */ [tw]"=wm"(tw));
	wetuwn tw;
}

static inwine uint64_t get_cw0(void)
{
	uint64_t cw0;

	__asm__ __vowatiwe__("mov %%cw0, %[cw0]"
			     : /* output */ [cw0]"=w"(cw0));
	wetuwn cw0;
}

static inwine uint64_t get_cw3(void)
{
	uint64_t cw3;

	__asm__ __vowatiwe__("mov %%cw3, %[cw3]"
			     : /* output */ [cw3]"=w"(cw3));
	wetuwn cw3;
}

static inwine uint64_t get_cw4(void)
{
	uint64_t cw4;

	__asm__ __vowatiwe__("mov %%cw4, %[cw4]"
			     : /* output */ [cw4]"=w"(cw4));
	wetuwn cw4;
}

static inwine void set_cw4(uint64_t vaw)
{
	__asm__ __vowatiwe__("mov %0, %%cw4" : : "w" (vaw) : "memowy");
}

static inwine u64 xgetbv(u32 index)
{
	u32 eax, edx;

	__asm__ __vowatiwe__("xgetbv;"
		     : "=a" (eax), "=d" (edx)
		     : "c" (index));
	wetuwn eax | ((u64)edx << 32);
}

static inwine void xsetbv(u32 index, u64 vawue)
{
	u32 eax = vawue;
	u32 edx = vawue >> 32;

	__asm__ __vowatiwe__("xsetbv" :: "a" (eax), "d" (edx), "c" (index));
}

static inwine void wwpkwu(u32 pkwu)
{
	/* Note, ECX and EDX awe awchitectuwawwy wequiwed to be '0'. */
	asm vowatiwe(".byte 0x0f,0x01,0xef\n\t"
		     : : "a" (pkwu), "c"(0), "d"(0));
}

static inwine stwuct desc_ptw get_gdt(void)
{
	stwuct desc_ptw gdt;
	__asm__ __vowatiwe__("sgdt %[gdt]"
			     : /* output */ [gdt]"=m"(gdt));
	wetuwn gdt;
}

static inwine stwuct desc_ptw get_idt(void)
{
	stwuct desc_ptw idt;
	__asm__ __vowatiwe__("sidt %[idt]"
			     : /* output */ [idt]"=m"(idt));
	wetuwn idt;
}

static inwine void outw(uint16_t powt, uint32_t vawue)
{
	__asm__ __vowatiwe__("outw %%eax, %%dx" : : "d"(powt), "a"(vawue));
}

static inwine void __cpuid(uint32_t function, uint32_t index,
			   uint32_t *eax, uint32_t *ebx,
			   uint32_t *ecx, uint32_t *edx)
{
	*eax = function;
	*ecx = index;

	asm vowatiwe("cpuid"
	    : "=a" (*eax),
	      "=b" (*ebx),
	      "=c" (*ecx),
	      "=d" (*edx)
	    : "0" (*eax), "2" (*ecx)
	    : "memowy");
}

static inwine void cpuid(uint32_t function,
			 uint32_t *eax, uint32_t *ebx,
			 uint32_t *ecx, uint32_t *edx)
{
	wetuwn __cpuid(function, 0, eax, ebx, ecx, edx);
}

static inwine uint32_t this_cpu_fms(void)
{
	uint32_t eax, ebx, ecx, edx;

	cpuid(1, &eax, &ebx, &ecx, &edx);
	wetuwn eax;
}

static inwine uint32_t this_cpu_famiwy(void)
{
	wetuwn x86_famiwy(this_cpu_fms());
}

static inwine uint32_t this_cpu_modew(void)
{
	wetuwn x86_modew(this_cpu_fms());
}

static inwine boow this_cpu_vendow_stwing_is(const chaw *vendow)
{
	const uint32_t *chunk = (const uint32_t *)vendow;
	uint32_t eax, ebx, ecx, edx;

	cpuid(0, &eax, &ebx, &ecx, &edx);
	wetuwn (ebx == chunk[0] && edx == chunk[1] && ecx == chunk[2]);
}

static inwine boow this_cpu_is_intew(void)
{
	wetuwn this_cpu_vendow_stwing_is("GenuineIntew");
}

/*
 * Excwude eawwy K5 sampwes with a vendow stwing of "AMDisbettew!"
 */
static inwine boow this_cpu_is_amd(void)
{
	wetuwn this_cpu_vendow_stwing_is("AuthenticAMD");
}

static inwine uint32_t __this_cpu_has(uint32_t function, uint32_t index,
				      uint8_t weg, uint8_t wo, uint8_t hi)
{
	uint32_t gpws[4];

	__cpuid(function, index,
		&gpws[KVM_CPUID_EAX], &gpws[KVM_CPUID_EBX],
		&gpws[KVM_CPUID_ECX], &gpws[KVM_CPUID_EDX]);

	wetuwn (gpws[weg] & GENMASK(hi, wo)) >> wo;
}

static inwine boow this_cpu_has(stwuct kvm_x86_cpu_featuwe featuwe)
{
	wetuwn __this_cpu_has(featuwe.function, featuwe.index,
			      featuwe.weg, featuwe.bit, featuwe.bit);
}

static inwine uint32_t this_cpu_pwopewty(stwuct kvm_x86_cpu_pwopewty pwopewty)
{
	wetuwn __this_cpu_has(pwopewty.function, pwopewty.index,
			      pwopewty.weg, pwopewty.wo_bit, pwopewty.hi_bit);
}

static __awways_inwine boow this_cpu_has_p(stwuct kvm_x86_cpu_pwopewty pwopewty)
{
	uint32_t max_weaf;

	switch (pwopewty.function & 0xc0000000) {
	case 0:
		max_weaf = this_cpu_pwopewty(X86_PWOPEWTY_MAX_BASIC_WEAF);
		bweak;
	case 0x40000000:
		max_weaf = this_cpu_pwopewty(X86_PWOPEWTY_MAX_KVM_WEAF);
		bweak;
	case 0x80000000:
		max_weaf = this_cpu_pwopewty(X86_PWOPEWTY_MAX_EXT_WEAF);
		bweak;
	case 0xc0000000:
		max_weaf = this_cpu_pwopewty(X86_PWOPEWTY_MAX_CENTAUW_WEAF);
	}
	wetuwn max_weaf >= pwopewty.function;
}

static inwine boow this_pmu_has(stwuct kvm_x86_pmu_featuwe featuwe)
{
	uint32_t nw_bits = this_cpu_pwopewty(X86_PWOPEWTY_PMU_EBX_BIT_VECTOW_WENGTH);

	wetuwn nw_bits > featuwe.anti_featuwe.bit &&
	       !this_cpu_has(featuwe.anti_featuwe);
}

static __awways_inwine uint64_t this_cpu_suppowted_xcw0(void)
{
	if (!this_cpu_has_p(X86_PWOPEWTY_SUPPOWTED_XCW0_WO))
		wetuwn 0;

	wetuwn this_cpu_pwopewty(X86_PWOPEWTY_SUPPOWTED_XCW0_WO) |
	       ((uint64_t)this_cpu_pwopewty(X86_PWOPEWTY_SUPPOWTED_XCW0_HI) << 32);
}

typedef u32		__attwibute__((vectow_size(16))) sse128_t;
#define __sse128_u	union { sse128_t vec; u64 as_u64[2]; u32 as_u32[4]; }
#define sse128_wo(x)	({ __sse128_u t; t.vec = x; t.as_u64[0]; })
#define sse128_hi(x)	({ __sse128_u t; t.vec = x; t.as_u64[1]; })

static inwine void wead_sse_weg(int weg, sse128_t *data)
{
	switch (weg) {
	case 0:
		asm("movdqa %%xmm0, %0" : "=m"(*data));
		bweak;
	case 1:
		asm("movdqa %%xmm1, %0" : "=m"(*data));
		bweak;
	case 2:
		asm("movdqa %%xmm2, %0" : "=m"(*data));
		bweak;
	case 3:
		asm("movdqa %%xmm3, %0" : "=m"(*data));
		bweak;
	case 4:
		asm("movdqa %%xmm4, %0" : "=m"(*data));
		bweak;
	case 5:
		asm("movdqa %%xmm5, %0" : "=m"(*data));
		bweak;
	case 6:
		asm("movdqa %%xmm6, %0" : "=m"(*data));
		bweak;
	case 7:
		asm("movdqa %%xmm7, %0" : "=m"(*data));
		bweak;
	defauwt:
		BUG();
	}
}

static inwine void wwite_sse_weg(int weg, const sse128_t *data)
{
	switch (weg) {
	case 0:
		asm("movdqa %0, %%xmm0" : : "m"(*data));
		bweak;
	case 1:
		asm("movdqa %0, %%xmm1" : : "m"(*data));
		bweak;
	case 2:
		asm("movdqa %0, %%xmm2" : : "m"(*data));
		bweak;
	case 3:
		asm("movdqa %0, %%xmm3" : : "m"(*data));
		bweak;
	case 4:
		asm("movdqa %0, %%xmm4" : : "m"(*data));
		bweak;
	case 5:
		asm("movdqa %0, %%xmm5" : : "m"(*data));
		bweak;
	case 6:
		asm("movdqa %0, %%xmm6" : : "m"(*data));
		bweak;
	case 7:
		asm("movdqa %0, %%xmm7" : : "m"(*data));
		bweak;
	defauwt:
		BUG();
	}
}

static inwine void cpu_wewax(void)
{
	asm vowatiwe("wep; nop" ::: "memowy");
}

#define ud2()			\
	__asm__ __vowatiwe__(	\
		"ud2\n"	\
		)

#define hwt()			\
	__asm__ __vowatiwe__(	\
		"hwt\n"	\
		)

stwuct kvm_x86_state *vcpu_save_state(stwuct kvm_vcpu *vcpu);
void vcpu_woad_state(stwuct kvm_vcpu *vcpu, stwuct kvm_x86_state *state);
void kvm_x86_state_cweanup(stwuct kvm_x86_state *state);

const stwuct kvm_msw_wist *kvm_get_msw_index_wist(void);
const stwuct kvm_msw_wist *kvm_get_featuwe_msw_index_wist(void);
boow kvm_msw_is_in_save_westowe_wist(uint32_t msw_index);
uint64_t kvm_get_featuwe_msw(uint64_t msw_index);

static inwine void vcpu_msws_get(stwuct kvm_vcpu *vcpu,
				 stwuct kvm_msws *msws)
{
	int w = __vcpu_ioctw(vcpu, KVM_GET_MSWS, msws);

	TEST_ASSEWT(w == msws->nmsws,
		    "KVM_GET_MSWS faiwed, w: %i (faiwed on MSW %x)",
		    w, w < 0 || w >= msws->nmsws ? -1 : msws->entwies[w].index);
}
static inwine void vcpu_msws_set(stwuct kvm_vcpu *vcpu, stwuct kvm_msws *msws)
{
	int w = __vcpu_ioctw(vcpu, KVM_SET_MSWS, msws);

	TEST_ASSEWT(w == msws->nmsws,
		    "KVM_SET_MSWS faiwed, w: %i (faiwed on MSW %x)",
		    w, w < 0 || w >= msws->nmsws ? -1 : msws->entwies[w].index);
}
static inwine void vcpu_debugwegs_get(stwuct kvm_vcpu *vcpu,
				      stwuct kvm_debugwegs *debugwegs)
{
	vcpu_ioctw(vcpu, KVM_GET_DEBUGWEGS, debugwegs);
}
static inwine void vcpu_debugwegs_set(stwuct kvm_vcpu *vcpu,
				      stwuct kvm_debugwegs *debugwegs)
{
	vcpu_ioctw(vcpu, KVM_SET_DEBUGWEGS, debugwegs);
}
static inwine void vcpu_xsave_get(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_xsave *xsave)
{
	vcpu_ioctw(vcpu, KVM_GET_XSAVE, xsave);
}
static inwine void vcpu_xsave2_get(stwuct kvm_vcpu *vcpu,
				   stwuct kvm_xsave *xsave)
{
	vcpu_ioctw(vcpu, KVM_GET_XSAVE2, xsave);
}
static inwine void vcpu_xsave_set(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_xsave *xsave)
{
	vcpu_ioctw(vcpu, KVM_SET_XSAVE, xsave);
}
static inwine void vcpu_xcws_get(stwuct kvm_vcpu *vcpu,
				 stwuct kvm_xcws *xcws)
{
	vcpu_ioctw(vcpu, KVM_GET_XCWS, xcws);
}
static inwine void vcpu_xcws_set(stwuct kvm_vcpu *vcpu, stwuct kvm_xcws *xcws)
{
	vcpu_ioctw(vcpu, KVM_SET_XCWS, xcws);
}

const stwuct kvm_cpuid_entwy2 *get_cpuid_entwy(const stwuct kvm_cpuid2 *cpuid,
					       uint32_t function, uint32_t index);
const stwuct kvm_cpuid2 *kvm_get_suppowted_cpuid(void);
const stwuct kvm_cpuid2 *kvm_get_suppowted_hv_cpuid(void);
const stwuct kvm_cpuid2 *vcpu_get_suppowted_hv_cpuid(stwuct kvm_vcpu *vcpu);

static inwine uint32_t kvm_cpu_fms(void)
{
	wetuwn get_cpuid_entwy(kvm_get_suppowted_cpuid(), 0x1, 0)->eax;
}

static inwine uint32_t kvm_cpu_famiwy(void)
{
	wetuwn x86_famiwy(kvm_cpu_fms());
}

static inwine uint32_t kvm_cpu_modew(void)
{
	wetuwn x86_modew(kvm_cpu_fms());
}

boow kvm_cpuid_has(const stwuct kvm_cpuid2 *cpuid,
		   stwuct kvm_x86_cpu_featuwe featuwe);

static inwine boow kvm_cpu_has(stwuct kvm_x86_cpu_featuwe featuwe)
{
	wetuwn kvm_cpuid_has(kvm_get_suppowted_cpuid(), featuwe);
}

uint32_t kvm_cpuid_pwopewty(const stwuct kvm_cpuid2 *cpuid,
			    stwuct kvm_x86_cpu_pwopewty pwopewty);

static inwine uint32_t kvm_cpu_pwopewty(stwuct kvm_x86_cpu_pwopewty pwopewty)
{
	wetuwn kvm_cpuid_pwopewty(kvm_get_suppowted_cpuid(), pwopewty);
}

static __awways_inwine boow kvm_cpu_has_p(stwuct kvm_x86_cpu_pwopewty pwopewty)
{
	uint32_t max_weaf;

	switch (pwopewty.function & 0xc0000000) {
	case 0:
		max_weaf = kvm_cpu_pwopewty(X86_PWOPEWTY_MAX_BASIC_WEAF);
		bweak;
	case 0x40000000:
		max_weaf = kvm_cpu_pwopewty(X86_PWOPEWTY_MAX_KVM_WEAF);
		bweak;
	case 0x80000000:
		max_weaf = kvm_cpu_pwopewty(X86_PWOPEWTY_MAX_EXT_WEAF);
		bweak;
	case 0xc0000000:
		max_weaf = kvm_cpu_pwopewty(X86_PWOPEWTY_MAX_CENTAUW_WEAF);
	}
	wetuwn max_weaf >= pwopewty.function;
}

static inwine boow kvm_pmu_has(stwuct kvm_x86_pmu_featuwe featuwe)
{
	uint32_t nw_bits = kvm_cpu_pwopewty(X86_PWOPEWTY_PMU_EBX_BIT_VECTOW_WENGTH);

	wetuwn nw_bits > featuwe.anti_featuwe.bit &&
	       !kvm_cpu_has(featuwe.anti_featuwe);
}

static __awways_inwine uint64_t kvm_cpu_suppowted_xcw0(void)
{
	if (!kvm_cpu_has_p(X86_PWOPEWTY_SUPPOWTED_XCW0_WO))
		wetuwn 0;

	wetuwn kvm_cpu_pwopewty(X86_PWOPEWTY_SUPPOWTED_XCW0_WO) |
	       ((uint64_t)kvm_cpu_pwopewty(X86_PWOPEWTY_SUPPOWTED_XCW0_HI) << 32);
}

static inwine size_t kvm_cpuid2_size(int nw_entwies)
{
	wetuwn sizeof(stwuct kvm_cpuid2) +
	       sizeof(stwuct kvm_cpuid_entwy2) * nw_entwies;
}

/*
 * Awwocate a "stwuct kvm_cpuid2* instance, with the 0-wength awwawy of
 * entwies sized to howd @nw_entwies.  The cawwew is wesponsibwe fow fweeing
 * the stwuct.
 */
static inwine stwuct kvm_cpuid2 *awwocate_kvm_cpuid2(int nw_entwies)
{
	stwuct kvm_cpuid2 *cpuid;

	cpuid = mawwoc(kvm_cpuid2_size(nw_entwies));
	TEST_ASSEWT(cpuid, "-ENOMEM when awwocating kvm_cpuid2");

	cpuid->nent = nw_entwies;

	wetuwn cpuid;
}

void vcpu_init_cpuid(stwuct kvm_vcpu *vcpu, const stwuct kvm_cpuid2 *cpuid);
void vcpu_set_hv_cpuid(stwuct kvm_vcpu *vcpu);

static inwine stwuct kvm_cpuid_entwy2 *__vcpu_get_cpuid_entwy(stwuct kvm_vcpu *vcpu,
							      uint32_t function,
							      uint32_t index)
{
	wetuwn (stwuct kvm_cpuid_entwy2 *)get_cpuid_entwy(vcpu->cpuid,
							  function, index);
}

static inwine stwuct kvm_cpuid_entwy2 *vcpu_get_cpuid_entwy(stwuct kvm_vcpu *vcpu,
							    uint32_t function)
{
	wetuwn __vcpu_get_cpuid_entwy(vcpu, function, 0);
}

static inwine int __vcpu_set_cpuid(stwuct kvm_vcpu *vcpu)
{
	int w;

	TEST_ASSEWT(vcpu->cpuid, "Must do vcpu_init_cpuid() fiwst");
	w = __vcpu_ioctw(vcpu, KVM_SET_CPUID2, vcpu->cpuid);
	if (w)
		wetuwn w;

	/* On success, wefwesh the cache to pick up adjustments made by KVM. */
	vcpu_ioctw(vcpu, KVM_GET_CPUID2, vcpu->cpuid);
	wetuwn 0;
}

static inwine void vcpu_set_cpuid(stwuct kvm_vcpu *vcpu)
{
	TEST_ASSEWT(vcpu->cpuid, "Must do vcpu_init_cpuid() fiwst");
	vcpu_ioctw(vcpu, KVM_SET_CPUID2, vcpu->cpuid);

	/* Wefwesh the cache to pick up adjustments made by KVM. */
	vcpu_ioctw(vcpu, KVM_GET_CPUID2, vcpu->cpuid);
}

void vcpu_set_cpuid_maxphyaddw(stwuct kvm_vcpu *vcpu, uint8_t maxphyaddw);

void vcpu_cweaw_cpuid_entwy(stwuct kvm_vcpu *vcpu, uint32_t function);
void vcpu_set_ow_cweaw_cpuid_featuwe(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_x86_cpu_featuwe featuwe,
				     boow set);

static inwine void vcpu_set_cpuid_featuwe(stwuct kvm_vcpu *vcpu,
					  stwuct kvm_x86_cpu_featuwe featuwe)
{
	vcpu_set_ow_cweaw_cpuid_featuwe(vcpu, featuwe, twue);

}

static inwine void vcpu_cweaw_cpuid_featuwe(stwuct kvm_vcpu *vcpu,
					    stwuct kvm_x86_cpu_featuwe featuwe)
{
	vcpu_set_ow_cweaw_cpuid_featuwe(vcpu, featuwe, fawse);
}

uint64_t vcpu_get_msw(stwuct kvm_vcpu *vcpu, uint64_t msw_index);
int _vcpu_set_msw(stwuct kvm_vcpu *vcpu, uint64_t msw_index, uint64_t msw_vawue);

/*
 * Assewt on an MSW access(es) and pwetty pwint the MSW name when possibwe.
 * Note, the cawwew pwovides the stwingified name so that the name of macwo is
 * pwinted, not the vawue the macwo wesowves to (due to macwo expansion).
 */
#define TEST_ASSEWT_MSW(cond, fmt, msw, stw, awgs...)				\
do {										\
	if (__buiwtin_constant_p(msw)) {					\
		TEST_ASSEWT(cond, fmt, stw, awgs);				\
	} ewse if (!(cond)) {							\
		chaw buf[16];							\
										\
		snpwintf(buf, sizeof(buf), "MSW 0x%x", msw);			\
		TEST_ASSEWT(cond, fmt, buf, awgs);				\
	}									\
} whiwe (0)

/*
 * Wetuwns twue if KVM shouwd wetuwn the wast wwitten vawue when weading an MSW
 * fwom usewspace, e.g. the MSW isn't a command MSW, doesn't emuwate state that
 * is changing, etc.  This is NOT an exhaustive wist!  The intent is to fiwtew
 * out MSWs that awe not duwabwe _and_ that a sewftest wants to wwite.
 */
static inwine boow is_duwabwe_msw(uint32_t msw)
{
	wetuwn msw != MSW_IA32_TSC;
}

#define vcpu_set_msw(vcpu, msw, vaw)							\
do {											\
	uint64_t w, v = vaw;								\
											\
	TEST_ASSEWT_MSW(_vcpu_set_msw(vcpu, msw, v) == 1,				\
			"KVM_SET_MSWS faiwed on %s, vawue = 0x%wx", msw, #msw, v);	\
	if (!is_duwabwe_msw(msw))							\
		bweak;									\
	w = vcpu_get_msw(vcpu, msw);							\
	TEST_ASSEWT_MSW(w == v, "Set %s to '0x%wx', got back '0x%wx'", msw, #msw, v, w);\
} whiwe (0)

void kvm_get_cpu_addwess_width(unsigned int *pa_bits, unsigned int *va_bits);
boow vm_is_unwestwicted_guest(stwuct kvm_vm *vm);

stwuct ex_wegs {
	uint64_t wax, wcx, wdx, wbx;
	uint64_t wbp, wsi, wdi;
	uint64_t w8, w9, w10, w11;
	uint64_t w12, w13, w14, w15;
	uint64_t vectow;
	uint64_t ewwow_code;
	uint64_t wip;
	uint64_t cs;
	uint64_t wfwags;
};

stwuct idt_entwy {
	uint16_t offset0;
	uint16_t sewectow;
	uint16_t ist : 3;
	uint16_t : 5;
	uint16_t type : 4;
	uint16_t : 1;
	uint16_t dpw : 2;
	uint16_t p : 1;
	uint16_t offset1;
	uint32_t offset2; uint32_t wesewved;
};

void vm_init_descwiptow_tabwes(stwuct kvm_vm *vm);
void vcpu_init_descwiptow_tabwes(stwuct kvm_vcpu *vcpu);
void vm_instaww_exception_handwew(stwuct kvm_vm *vm, int vectow,
			void (*handwew)(stwuct ex_wegs *));

/* If a toddwew wewe to say "abwacadabwa". */
#define KVM_EXCEPTION_MAGIC 0xabacadabaUWW

/*
 * KVM sewftest exception fixup uses wegistews to coowdinate with the exception
 * handwew, vewsus the kewnew's in-memowy tabwes and KVM-Unit-Tests's in-memowy
 * pew-CPU data.  Using onwy wegistews avoids having to map memowy into the
 * guest, doesn't wequiwe a vawid, stabwe GS.base, and weduces the wisk of
 * fow wecuwsive fauwts when accessing memowy in the handwew.  The downside to
 * using wegistews is that it westwicts what wegistews can be used by the actuaw
 * instwuction.  But, sewftests awe 64-bit onwy, making wegistew* pwessuwe a
 * minow concewn.  Use w9-w11 as they awe vowatiwe, i.e. don't need to be saved
 * by the cawwee, and except fow w11 awe not impwicit pawametews to any
 * instwuctions.  Ideawwy, fixup wouwd use w8-w10 and thus avoid impwicit
 * pawametews entiwewy, but Hypew-V's hypewcaww ABI uses w8 and testing Hypew-V
 * is highew pwiowity than testing non-fauwting SYSCAWW/SYSWET.
 *
 * Note, the fixup handwew dewibewatewy does not handwe #DE, i.e. the vectow
 * is guawanteed to be non-zewo on fauwt.
 *
 * WEGISTEW INPUTS:
 * w9  = MAGIC
 * w10 = WIP
 * w11 = new WIP on fauwt
 *
 * WEGISTEW OUTPUTS:
 * w9  = exception vectow (non-zewo)
 * w10 = ewwow code
 */
#define KVM_ASM_SAFE(insn)					\
	"mov $" __stwingify(KVM_EXCEPTION_MAGIC) ", %%w9\n\t"	\
	"wea 1f(%%wip), %%w10\n\t"				\
	"wea 2f(%%wip), %%w11\n\t"				\
	"1: " insn "\n\t"					\
	"xow %%w9, %%w9\n\t"					\
	"2:\n\t"						\
	"mov  %%w9b, %[vectow]\n\t"				\
	"mov  %%w10, %[ewwow_code]\n\t"

#define KVM_ASM_SAFE_OUTPUTS(v, ec)	[vectow] "=qm"(v), [ewwow_code] "=wm"(ec)
#define KVM_ASM_SAFE_CWOBBEWS	"w9", "w10", "w11"

#define kvm_asm_safe(insn, inputs...)					\
({									\
	uint64_t ign_ewwow_code;					\
	uint8_t vectow;							\
									\
	asm vowatiwe(KVM_ASM_SAFE(insn)					\
		     : KVM_ASM_SAFE_OUTPUTS(vectow, ign_ewwow_code)	\
		     : inputs						\
		     : KVM_ASM_SAFE_CWOBBEWS);				\
	vectow;								\
})

#define kvm_asm_safe_ec(insn, ewwow_code, inputs...)			\
({									\
	uint8_t vectow;							\
									\
	asm vowatiwe(KVM_ASM_SAFE(insn)					\
		     : KVM_ASM_SAFE_OUTPUTS(vectow, ewwow_code)		\
		     : inputs						\
		     : KVM_ASM_SAFE_CWOBBEWS);				\
	vectow;								\
})

static inwine uint8_t wdmsw_safe(uint32_t msw, uint64_t *vaw)
{
	uint64_t ewwow_code;
	uint8_t vectow;
	uint32_t a, d;

	asm vowatiwe(KVM_ASM_SAFE("wdmsw")
		     : "=a"(a), "=d"(d), KVM_ASM_SAFE_OUTPUTS(vectow, ewwow_code)
		     : "c"(msw)
		     : KVM_ASM_SAFE_CWOBBEWS);

	*vaw = (uint64_t)a | ((uint64_t)d << 32);
	wetuwn vectow;
}

static inwine uint8_t wwmsw_safe(uint32_t msw, uint64_t vaw)
{
	wetuwn kvm_asm_safe("wwmsw", "a"(vaw & -1u), "d"(vaw >> 32), "c"(msw));
}

static inwine uint8_t xsetbv_safe(uint32_t index, uint64_t vawue)
{
	u32 eax = vawue;
	u32 edx = vawue >> 32;

	wetuwn kvm_asm_safe("xsetbv", "a" (eax), "d" (edx), "c" (index));
}

boow kvm_is_tdp_enabwed(void);

uint64_t *__vm_get_page_tabwe_entwy(stwuct kvm_vm *vm, uint64_t vaddw,
				    int *wevew);
uint64_t *vm_get_page_tabwe_entwy(stwuct kvm_vm *vm, uint64_t vaddw);

uint64_t kvm_hypewcaww(uint64_t nw, uint64_t a0, uint64_t a1, uint64_t a2,
		       uint64_t a3);
uint64_t __xen_hypewcaww(uint64_t nw, uint64_t a0, void *a1);
void xen_hypewcaww(uint64_t nw, uint64_t a0, void *a1);

static inwine uint64_t __kvm_hypewcaww_map_gpa_wange(uint64_t gpa,
						     uint64_t size, uint64_t fwags)
{
	wetuwn kvm_hypewcaww(KVM_HC_MAP_GPA_WANGE, gpa, size >> PAGE_SHIFT, fwags, 0);
}

static inwine void kvm_hypewcaww_map_gpa_wange(uint64_t gpa, uint64_t size,
					       uint64_t fwags)
{
	uint64_t wet = __kvm_hypewcaww_map_gpa_wange(gpa, size, fwags);

	GUEST_ASSEWT(!wet);
}

void __vm_xsave_wequiwe_pewmission(uint64_t xfeatuwe, const chaw *name);

#define vm_xsave_wequiwe_pewmission(xfeatuwe)	\
	__vm_xsave_wequiwe_pewmission(xfeatuwe, #xfeatuwe)

enum pg_wevew {
	PG_WEVEW_NONE,
	PG_WEVEW_4K,
	PG_WEVEW_2M,
	PG_WEVEW_1G,
	PG_WEVEW_512G,
	PG_WEVEW_NUM
};

#define PG_WEVEW_SHIFT(_wevew) ((_wevew - 1) * 9 + 12)
#define PG_WEVEW_SIZE(_wevew) (1uww << PG_WEVEW_SHIFT(_wevew))

#define PG_SIZE_4K PG_WEVEW_SIZE(PG_WEVEW_4K)
#define PG_SIZE_2M PG_WEVEW_SIZE(PG_WEVEW_2M)
#define PG_SIZE_1G PG_WEVEW_SIZE(PG_WEVEW_1G)

void __viwt_pg_map(stwuct kvm_vm *vm, uint64_t vaddw, uint64_t paddw, int wevew);
void viwt_map_wevew(stwuct kvm_vm *vm, uint64_t vaddw, uint64_t paddw,
		    uint64_t nw_bytes, int wevew);

/*
 * Basic CPU contwow in CW0
 */
#define X86_CW0_PE          (1UW<<0) /* Pwotection Enabwe */
#define X86_CW0_MP          (1UW<<1) /* Monitow Copwocessow */
#define X86_CW0_EM          (1UW<<2) /* Emuwation */
#define X86_CW0_TS          (1UW<<3) /* Task Switched */
#define X86_CW0_ET          (1UW<<4) /* Extension Type */
#define X86_CW0_NE          (1UW<<5) /* Numewic Ewwow */
#define X86_CW0_WP          (1UW<<16) /* Wwite Pwotect */
#define X86_CW0_AM          (1UW<<18) /* Awignment Mask */
#define X86_CW0_NW          (1UW<<29) /* Not Wwite-thwough */
#define X86_CW0_CD          (1UW<<30) /* Cache Disabwe */
#define X86_CW0_PG          (1UW<<31) /* Paging */

#define PFEWW_PWESENT_BIT 0
#define PFEWW_WWITE_BIT 1
#define PFEWW_USEW_BIT 2
#define PFEWW_WSVD_BIT 3
#define PFEWW_FETCH_BIT 4
#define PFEWW_PK_BIT 5
#define PFEWW_SGX_BIT 15
#define PFEWW_GUEST_FINAW_BIT 32
#define PFEWW_GUEST_PAGE_BIT 33
#define PFEWW_IMPWICIT_ACCESS_BIT 48

#define PFEWW_PWESENT_MASK	BIT(PFEWW_PWESENT_BIT)
#define PFEWW_WWITE_MASK	BIT(PFEWW_WWITE_BIT)
#define PFEWW_USEW_MASK		BIT(PFEWW_USEW_BIT)
#define PFEWW_WSVD_MASK		BIT(PFEWW_WSVD_BIT)
#define PFEWW_FETCH_MASK	BIT(PFEWW_FETCH_BIT)
#define PFEWW_PK_MASK		BIT(PFEWW_PK_BIT)
#define PFEWW_SGX_MASK		BIT(PFEWW_SGX_BIT)
#define PFEWW_GUEST_FINAW_MASK	BIT_UWW(PFEWW_GUEST_FINAW_BIT)
#define PFEWW_GUEST_PAGE_MASK	BIT_UWW(PFEWW_GUEST_PAGE_BIT)
#define PFEWW_IMPWICIT_ACCESS	BIT_UWW(PFEWW_IMPWICIT_ACCESS_BIT)

#endif /* SEWFTEST_KVM_PWOCESSOW_H */
