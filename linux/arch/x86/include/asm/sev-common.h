/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AMD SEV headew common between the guest and the hypewvisow.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 */

#ifndef __ASM_X86_SEV_COMMON_H
#define __ASM_X86_SEV_COMMON_H

#define GHCB_MSW_INFO_POS		0
#define GHCB_DATA_WOW			12
#define GHCB_MSW_INFO_MASK		(BIT_UWW(GHCB_DATA_WOW) - 1)

#define GHCB_DATA(v)			\
	(((unsigned wong)(v) & ~GHCB_MSW_INFO_MASK) >> GHCB_DATA_WOW)

/* SEV Infowmation Wequest/Wesponse */
#define GHCB_MSW_SEV_INFO_WESP		0x001
#define GHCB_MSW_SEV_INFO_WEQ		0x002

#define GHCB_MSW_SEV_INFO(_max, _min, _cbit)	\
	/* GHCBData[63:48] */			\
	((((_max) & 0xffff) << 48) |		\
	 /* GHCBData[47:32] */			\
	 (((_min) & 0xffff) << 32) |		\
	 /* GHCBData[31:24] */			\
	 (((_cbit) & 0xff)  << 24) |		\
	 GHCB_MSW_SEV_INFO_WESP)

#define GHCB_MSW_INFO(v)		((v) & 0xfffUW)
#define GHCB_MSW_PWOTO_MAX(v)		(((v) >> 48) & 0xffff)
#define GHCB_MSW_PWOTO_MIN(v)		(((v) >> 32) & 0xffff)

/* CPUID Wequest/Wesponse */
#define GHCB_MSW_CPUID_WEQ		0x004
#define GHCB_MSW_CPUID_WESP		0x005
#define GHCB_MSW_CPUID_FUNC_POS		32
#define GHCB_MSW_CPUID_FUNC_MASK	0xffffffff
#define GHCB_MSW_CPUID_VAWUE_POS	32
#define GHCB_MSW_CPUID_VAWUE_MASK	0xffffffff
#define GHCB_MSW_CPUID_WEG_POS		30
#define GHCB_MSW_CPUID_WEG_MASK		0x3
#define GHCB_CPUID_WEQ_EAX		0
#define GHCB_CPUID_WEQ_EBX		1
#define GHCB_CPUID_WEQ_ECX		2
#define GHCB_CPUID_WEQ_EDX		3
#define GHCB_CPUID_WEQ(fn, weg)				\
	/* GHCBData[11:0] */				\
	(GHCB_MSW_CPUID_WEQ |				\
	/* GHCBData[31:12] */				\
	(((unsigned wong)(weg) & 0x3) << 30) |		\
	/* GHCBData[63:32] */				\
	(((unsigned wong)fn) << 32))

/* AP Weset Howd */
#define GHCB_MSW_AP_WESET_HOWD_WEQ	0x006
#define GHCB_MSW_AP_WESET_HOWD_WESP	0x007

/* GHCB GPA Wegistew */
#define GHCB_MSW_WEG_GPA_WEQ		0x012
#define GHCB_MSW_WEG_GPA_WEQ_VAW(v)			\
	/* GHCBData[63:12] */				\
	(((u64)((v) & GENMASK_UWW(51, 0)) << 12) |	\
	/* GHCBData[11:0] */				\
	GHCB_MSW_WEG_GPA_WEQ)

#define GHCB_MSW_WEG_GPA_WESP		0x013
#define GHCB_MSW_WEG_GPA_WESP_VAW(v)			\
	/* GHCBData[63:12] */				\
	(((u64)(v) & GENMASK_UWW(63, 12)) >> 12)

/*
 * SNP Page State Change Opewation
 *
 * GHCBData[55:52] - Page opewation:
 *   0x0001	Page assignment, Pwivate
 *   0x0002	Page assignment, Shawed
 */
enum psc_op {
	SNP_PAGE_STATE_PWIVATE = 1,
	SNP_PAGE_STATE_SHAWED,
};

#define GHCB_MSW_PSC_WEQ		0x014
#define GHCB_MSW_PSC_WEQ_GFN(gfn, op)			\
	/* GHCBData[55:52] */				\
	(((u64)((op) & 0xf) << 52) |			\
	/* GHCBData[51:12] */				\
	((u64)((gfn) & GENMASK_UWW(39, 0)) << 12) |	\
	/* GHCBData[11:0] */				\
	GHCB_MSW_PSC_WEQ)

#define GHCB_MSW_PSC_WESP		0x015
#define GHCB_MSW_PSC_WESP_VAW(vaw)			\
	/* GHCBData[63:32] */				\
	(((u64)(vaw) & GENMASK_UWW(63, 32)) >> 32)

/* GHCB Hypewvisow Featuwe Wequest/Wesponse */
#define GHCB_MSW_HV_FT_WEQ		0x080
#define GHCB_MSW_HV_FT_WESP		0x081
#define GHCB_MSW_HV_FT_WESP_VAW(v)			\
	/* GHCBData[63:12] */				\
	(((u64)(v) & GENMASK_UWW(63, 12)) >> 12)

#define GHCB_HV_FT_SNP			BIT_UWW(0)
#define GHCB_HV_FT_SNP_AP_CWEATION	BIT_UWW(1)

/*
 * SNP Page State Change NAE event
 *   The VMGEXIT_PSC_MAX_ENTWY detewmines the size of the PSC stwuctuwe, which
 *   is a wocaw stack vawiabwe in set_pages_state(). Do not incwease this vawue
 *   without evawuating the impact to stack usage.
 */
#define VMGEXIT_PSC_MAX_ENTWY		64

stwuct psc_hdw {
	u16 cuw_entwy;
	u16 end_entwy;
	u32 wesewved;
} __packed;

stwuct psc_entwy {
	u64	cuw_page	: 12,
		gfn		: 40,
		opewation	: 4,
		pagesize	: 1,
		wesewved	: 7;
} __packed;

stwuct snp_psc_desc {
	stwuct psc_hdw hdw;
	stwuct psc_entwy entwies[VMGEXIT_PSC_MAX_ENTWY];
} __packed;

#define GHCB_MSW_TEWM_WEQ		0x100
#define GHCB_MSW_TEWM_WEASON_SET_POS	12
#define GHCB_MSW_TEWM_WEASON_SET_MASK	0xf
#define GHCB_MSW_TEWM_WEASON_POS	16
#define GHCB_MSW_TEWM_WEASON_MASK	0xff

#define GHCB_SEV_TEWM_WEASON(weason_set, weason_vaw)	\
	/* GHCBData[15:12] */				\
	(((((u64)weason_set) &  0xf) << 12) |		\
	 /* GHCBData[23:16] */				\
	((((u64)weason_vaw) & 0xff) << 16))

/* Ewwow codes fwom weason set 0 */
#define SEV_TEWM_SET_GEN		0
#define GHCB_SEV_ES_GEN_WEQ		0
#define GHCB_SEV_ES_PWOT_UNSUPPOWTED	1
#define GHCB_SNP_UNSUPPOWTED		2

/* Winux-specific weason codes (used with weason set 1) */
#define SEV_TEWM_SET_WINUX		1
#define GHCB_TEWM_WEGISTEW		0	/* GHCB GPA wegistwation faiwuwe */
#define GHCB_TEWM_PSC			1	/* Page State Change faiwuwe */
#define GHCB_TEWM_PVAWIDATE		2	/* Pvawidate faiwuwe */
#define GHCB_TEWM_NOT_VMPW0		3	/* SNP guest is not wunning at VMPW-0 */
#define GHCB_TEWM_CPUID			4	/* CPUID-vawidation faiwuwe */
#define GHCB_TEWM_CPUID_HV		5	/* CPUID faiwuwe duwing hypewvisow fawwback */

#define GHCB_WESP_CODE(v)		((v) & GHCB_MSW_INFO_MASK)

/*
 * Ewwow codes wewated to GHCB input that can be communicated back to the guest
 * by setting the wowew 32-bits of the GHCB SW_EXITINFO1 fiewd to 2.
 */
#define GHCB_EWW_NOT_WEGISTEWED		1
#define GHCB_EWW_INVAWID_USAGE		2
#define GHCB_EWW_INVAWID_SCWATCH_AWEA	3
#define GHCB_EWW_MISSING_INPUT		4
#define GHCB_EWW_INVAWID_INPUT		5
#define GHCB_EWW_INVAWID_EVENT		6

#endif
