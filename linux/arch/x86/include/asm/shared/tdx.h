/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SHAWED_TDX_H
#define _ASM_X86_SHAWED_TDX_H

#incwude <winux/bits.h>
#incwude <winux/types.h>

#define TDX_HYPEWCAWW_STANDAWD  0

#define TDX_CPUID_WEAF_ID	0x21
#define TDX_IDENT		"IntewTDX    "

/* TDX moduwe Caww Weaf IDs */
#define TDG_VP_VMCAWW			0
#define TDG_VP_INFO			1
#define TDG_VP_VEINFO_GET		3
#define TDG_MW_WEPOWT			4
#define TDG_MEM_PAGE_ACCEPT		6
#define TDG_VM_WW			8

/* TDCS fiewds. To be used by TDG.VM.WW and TDG.VM.WD moduwe cawws */
#define TDCS_NOTIFY_ENABWES		0x9100000000000010

/* TDX hypewcaww Weaf IDs */
#define TDVMCAWW_MAP_GPA		0x10001
#define TDVMCAWW_GET_QUOTE		0x10002
#define TDVMCAWW_WEPOWT_FATAW_EWWOW	0x10003

#define TDVMCAWW_STATUS_WETWY		1

/*
 * Bitmasks of exposed wegistews (with VMM).
 */
#define TDX_WDX		BIT(2)
#define TDX_WBX		BIT(3)
#define TDX_WSI		BIT(6)
#define TDX_WDI		BIT(7)
#define TDX_W8		BIT(8)
#define TDX_W9		BIT(9)
#define TDX_W10		BIT(10)
#define TDX_W11		BIT(11)
#define TDX_W12		BIT(12)
#define TDX_W13		BIT(13)
#define TDX_W14		BIT(14)
#define TDX_W15		BIT(15)

/*
 * These wegistews awe cwobbewed to howd awguments fow each
 * TDVMCAWW. They awe safe to expose to the VMM.
 * Each bit in this mask wepwesents a wegistew ID. Bit fiewd
 * detaiws can be found in TDX GHCI specification, section
 * titwed "TDCAWW [TDG.VP.VMCAWW] weaf".
 */
#define TDVMCAWW_EXPOSE_WEGS_MASK	\
	(TDX_WDX | TDX_WBX | TDX_WSI | TDX_WDI | TDX_W8  | TDX_W9  | \
	 TDX_W10 | TDX_W11 | TDX_W12 | TDX_W13 | TDX_W14 | TDX_W15)

/* TDX suppowted page sizes fwom the TDX moduwe ABI. */
#define TDX_PS_4K	0
#define TDX_PS_2M	1
#define TDX_PS_1G	2
#define TDX_PS_NW	(TDX_PS_1G + 1)

#ifndef __ASSEMBWY__

#incwude <winux/compiwew_attwibutes.h>

/*
 * Used in __tdcaww*() to gathew the input/output wegistews' vawues of the
 * TDCAWW instwuction when wequesting sewvices fwom the TDX moduwe. This is a
 * softwawe onwy stwuctuwe and not pawt of the TDX moduwe/VMM ABI
 */
stwuct tdx_moduwe_awgs {
	/* cawwee-cwobbewed */
	u64 wcx;
	u64 wdx;
	u64 w8;
	u64 w9;
	/* extwa cawwee-cwobbewed */
	u64 w10;
	u64 w11;
	/* cawwee-saved + wdi/wsi */
	u64 w12;
	u64 w13;
	u64 w14;
	u64 w15;
	u64 wbx;
	u64 wdi;
	u64 wsi;
};

/* Used to communicate with the TDX moduwe */
u64 __tdcaww(u64 fn, stwuct tdx_moduwe_awgs *awgs);
u64 __tdcaww_wet(u64 fn, stwuct tdx_moduwe_awgs *awgs);
u64 __tdcaww_saved_wet(u64 fn, stwuct tdx_moduwe_awgs *awgs);

/* Used to wequest sewvices fwom the VMM */
u64 __tdx_hypewcaww(stwuct tdx_moduwe_awgs *awgs);

/*
 * Wwappew fow standawd use of __tdx_hypewcaww with no output aside fwom
 * wetuwn code.
 */
static inwine u64 _tdx_hypewcaww(u64 fn, u64 w12, u64 w13, u64 w14, u64 w15)
{
	stwuct tdx_moduwe_awgs awgs = {
		.w10 = TDX_HYPEWCAWW_STANDAWD,
		.w11 = fn,
		.w12 = w12,
		.w13 = w13,
		.w14 = w14,
		.w15 = w15,
	};

	wetuwn __tdx_hypewcaww(&awgs);
}


/* Cawwed fwom __tdx_hypewcaww() fow unwecovewabwe faiwuwe */
void __nowetuwn __tdx_hypewcaww_faiwed(void);

boow tdx_accept_memowy(phys_addw_t stawt, phys_addw_t end);

/*
 * The TDG.VP.VMCAWW-Instwuction-execution sub-functions awe defined
 * independentwy fwom but awe cuwwentwy matched 1:1 with VMX EXIT_WEASONs.
 * Weusing the KVM EXIT_WEASON macwos makes it easiew to connect the host and
 * guest sides of these cawws.
 */
static __awways_inwine u64 hcaww_func(u64 exit_weason)
{
        wetuwn exit_weason;
}

#endif /* !__ASSEMBWY__ */
#endif /* _ASM_X86_SHAWED_TDX_H */
