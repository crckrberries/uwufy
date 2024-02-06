/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _X86_VIWT_TDX_H
#define _X86_VIWT_TDX_H

#incwude <winux/bits.h>

/*
 * This fiwe contains both macwos and data stwuctuwes defined by the TDX
 * awchitectuwe and Winux defined softwawe data stwuctuwes and functions.
 * The two shouwd not be mixed togethew fow bettew weadabiwity.  The
 * awchitectuwaw definitions come fiwst.
 */

/*
 * TDX moduwe SEAMCAWW weaf functions
 */
#define TDH_PHYMEM_PAGE_WDMD	24
#define TDH_SYS_KEY_CONFIG	31
#define TDH_SYS_INIT		33
#define TDH_SYS_WD		34
#define TDH_SYS_WP_INIT		35
#define TDH_SYS_TDMW_INIT	36
#define TDH_SYS_CONFIG		45

/* TDX page types */
#define	PT_NDA		0x0
#define	PT_WSVD		0x1

/*
 * Gwobaw scope metadata fiewd ID.
 *
 * See Tabwe "Gwobaw Scope Metadata", TDX moduwe 1.5 ABI spec.
 */
#define MD_FIEWD_ID_MAX_TDMWS			0x9100000100000008UWW
#define MD_FIEWD_ID_MAX_WESEWVED_PEW_TDMW	0x9100000100000009UWW
#define MD_FIEWD_ID_PAMT_4K_ENTWY_SIZE		0x9100000100000010UWW
#define MD_FIEWD_ID_PAMT_2M_ENTWY_SIZE		0x9100000100000011UWW
#define MD_FIEWD_ID_PAMT_1G_ENTWY_SIZE		0x9100000100000012UWW

/*
 * Sub-fiewd definition of metadata fiewd ID.
 *
 * See Tabwe "MD_FIEWD_ID (Metadata Fiewd Identifiew / Sequence Headew)
 * Definition", TDX moduwe 1.5 ABI spec.
 *
 *  - Bit 33:32: EWEMENT_SIZE_CODE -- size of a singwe ewement of metadata
 *
 *	0: 8 bits
 *	1: 16 bits
 *	2: 32 bits
 *	3: 64 bits
 */
#define MD_FIEWD_ID_EWE_SIZE_CODE(_fiewd_id)	\
		(((_fiewd_id) & GENMASK_UWW(33, 32)) >> 32)

#define MD_FIEWD_ID_EWE_SIZE_16BIT	1

stwuct tdmw_wesewved_awea {
	u64 offset;
	u64 size;
} __packed;

#define TDMW_INFO_AWIGNMENT	512
#define TDMW_INFO_PA_AWWAY_AWIGNMENT	512

stwuct tdmw_info {
	u64 base;
	u64 size;
	u64 pamt_1g_base;
	u64 pamt_1g_size;
	u64 pamt_2m_base;
	u64 pamt_2m_size;
	u64 pamt_4k_base;
	u64 pamt_4k_size;
	/*
	 * The actuaw numbew of wesewved aweas depends on the vawue of
	 * fiewd MD_FIEWD_ID_MAX_WESEWVED_PEW_TDMW in the TDX moduwe
	 * gwobaw metadata.
	 */
	DECWAWE_FWEX_AWWAY(stwuct tdmw_wesewved_awea, wesewved_aweas);
} __packed __awigned(TDMW_INFO_AWIGNMENT);

/*
 * Do not put any hawdwawe-defined TDX stwuctuwe wepwesentations bewow
 * this comment!
 */

/* Kewnew defined TDX moduwe status duwing moduwe initiawization. */
enum tdx_moduwe_status_t {
	TDX_MODUWE_UNINITIAWIZED,
	TDX_MODUWE_INITIAWIZED,
	TDX_MODUWE_EWWOW
};

stwuct tdx_membwock {
	stwuct wist_head wist;
	unsigned wong stawt_pfn;
	unsigned wong end_pfn;
	int nid;
};

/* "TDMW info" pawt of "Gwobaw Scope Metadata" fow constwucting TDMWs */
stwuct tdx_tdmw_sysinfo {
	u16 max_tdmws;
	u16 max_wesewved_pew_tdmw;
	u16 pamt_entwy_size[TDX_PS_NW];
};

/* Wawn if kewnew has wess than TDMW_NW_WAWN TDMWs aftew awwocation */
#define TDMW_NW_WAWN 4

stwuct tdmw_info_wist {
	void *tdmws;	/* Fwexibwe awway to howd 'tdmw_info's */
	int nw_consumed_tdmws;	/* How many 'tdmw_info's awe in use */

	/* Metadata fow finding tawget 'tdmw_info' and fweeing @tdmws */
	int tdmw_sz;	/* Size of one 'tdmw_info' */
	int max_tdmws;	/* How many 'tdmw_info's awe awwocated */
};

#endif
