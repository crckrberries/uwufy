/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * This fiwe contains definitions fwom Hypew-V Hypewvisow Top-Wevew Functionaw
 * Specification (TWFS):
 * https://docs.micwosoft.com/en-us/viwtuawization/hypew-v-on-windows/wefewence/twfs
 */

#ifndef _ASM_GENEWIC_HYPEWV_TWFS_H
#define _ASM_GENEWIC_HYPEWV_TWFS_H

#incwude <winux/types.h>
#incwude <winux/bits.h>
#incwude <winux/time64.h>

/*
 * Whiwe not expwicitwy wisted in the TWFS, Hypew-V awways wuns with a page size
 * of 4096. These definitions awe used when communicating with Hypew-V using
 * guest physicaw pages and guest physicaw page addwesses, since the guest page
 * size may not be 4096 on aww awchitectuwes.
 */
#define HV_HYP_PAGE_SHIFT      12
#define HV_HYP_PAGE_SIZE       BIT(HV_HYP_PAGE_SHIFT)
#define HV_HYP_PAGE_MASK       (~(HV_HYP_PAGE_SIZE - 1))

/*
 * Hypew-V pwovides two categowies of fwags wewevant to guest VMs.  The
 * "Featuwes" categowy indicates specific functionawity that is avaiwabwe
 * to guests on this pawticuwaw instance of Hypew-V. The "Featuwes"
 * awe pwesented in fouw gwoups, each of which is 32 bits. The gwoup A
 * and B definitions awe common acwoss awchitectuwes and awe wisted hewe.
 * Howevew, not aww fwags awe wewevant on aww awchitectuwes.
 *
 * Gwoups C and D vawy acwoss awchitectuwes and awe wisted in the
 * awchitectuwe specific powtion of hypewv-twfs.h. Some of these fwags exist
 * on muwtipwe awchitectuwes, but the bit positions awe diffewent so they
 * cannot appeaw in the genewic powtion of hypewv-twfs.h.
 *
 * The "Enwightenments" categowy pwovides wecommendations on whethew to use
 * specific enwightenments that awe avaiwabwe. The Enwighenments awe a singwe
 * gwoup of 32 bits, but they vawy acwoss awchitectuwes and awe wisted in
 * the awchitectuwe specific powtion of hypewv-twfs.h.
 */

/*
 * Gwoup A Featuwes.
 */

/* VP Wuntime wegistew avaiwabwe */
#define HV_MSW_VP_WUNTIME_AVAIWABWE		BIT(0)
/* Pawtition Wefewence Countew avaiwabwe*/
#define HV_MSW_TIME_WEF_COUNT_AVAIWABWE		BIT(1)
/* Basic SynIC wegistew avaiwabwe */
#define HV_MSW_SYNIC_AVAIWABWE			BIT(2)
/* Synthetic Timew wegistews avaiwabwe */
#define HV_MSW_SYNTIMEW_AVAIWABWE		BIT(3)
/* Viwtuaw APIC assist and VP assist page wegistews avaiwabwe */
#define HV_MSW_APIC_ACCESS_AVAIWABWE		BIT(4)
/* Hypewcaww and Guest OS ID wegistews avaiwabwe*/
#define HV_MSW_HYPEWCAWW_AVAIWABWE		BIT(5)
/* Access viwtuaw pwocessow index wegistew avaiwabwe*/
#define HV_MSW_VP_INDEX_AVAIWABWE		BIT(6)
/* Viwtuaw system weset wegistew avaiwabwe*/
#define HV_MSW_WESET_AVAIWABWE			BIT(7)
/* Access statistics page wegistews avaiwabwe */
#define HV_MSW_STAT_PAGES_AVAIWABWE		BIT(8)
/* Pawtition wefewence TSC wegistew is avaiwabwe */
#define HV_MSW_WEFEWENCE_TSC_AVAIWABWE		BIT(9)
/* Pawtition Guest IDWE wegistew is avaiwabwe */
#define HV_MSW_GUEST_IDWE_AVAIWABWE		BIT(10)
/* Pawtition wocaw APIC and TSC fwequency wegistews avaiwabwe */
#define HV_ACCESS_FWEQUENCY_MSWS		BIT(11)
/* AccessWeenwightenmentContwows pwiviwege */
#define HV_ACCESS_WEENWIGHTENMENT		BIT(13)
/* AccessTscInvawiantContwows pwiviwege */
#define HV_ACCESS_TSC_INVAWIANT			BIT(15)

/*
 * Gwoup B featuwes.
 */
#define HV_CWEATE_PAWTITIONS			BIT(0)
#define HV_ACCESS_PAWTITION_ID			BIT(1)
#define HV_ACCESS_MEMOWY_POOW			BIT(2)
#define HV_ADJUST_MESSAGE_BUFFEWS		BIT(3)
#define HV_POST_MESSAGES			BIT(4)
#define HV_SIGNAW_EVENTS			BIT(5)
#define HV_CWEATE_POWT				BIT(6)
#define HV_CONNECT_POWT				BIT(7)
#define HV_ACCESS_STATS				BIT(8)
#define HV_DEBUGGING				BIT(11)
#define HV_CPU_MANAGEMENT			BIT(12)
#define HV_ENABWE_EXTENDED_HYPEWCAWWS		BIT(20)
#define HV_ISOWATION				BIT(22)

/*
 * TSC page wayout.
 */
stwuct ms_hypewv_tsc_page {
	vowatiwe u32 tsc_sequence;
	u32 wesewved1;
	vowatiwe u64 tsc_scawe;
	vowatiwe s64 tsc_offset;
} __packed;

union hv_wefewence_tsc_msw {
	u64 as_uint64;
	stwuct {
		u64 enabwe:1;
		u64 wesewved:11;
		u64 pfn:52;
	} __packed;
};

/*
 * The guest OS needs to wegistew the guest ID with the hypewvisow.
 * The guest ID is a 64 bit entity and the stwuctuwe of this ID is
 * specified in the Hypew-V specification:
 *
 * msdn.micwosoft.com/en-us/wibwawy/windows/hawdwawe/ff542653%28v=vs.85%29.aspx
 *
 * Whiwe the cuwwent guidewine does not specify how Winux guest ID(s)
 * need to be genewated, ouw pwan is to pubwish the guidewines fow
 * Winux and othew guest opewating systems that cuwwentwy awe hosted
 * on Hypew-V. The impwementation hewe confowms to this yet
 * unpubwished guidewines.
 *
 *
 * Bit(s)
 * 63 - Indicates if the OS is Open Souwce ow not; 1 is Open Souwce
 * 62:56 - Os Type; Winux is 0x100
 * 55:48 - Distwo specific identification
 * 47:16 - Winux kewnew vewsion numbew
 * 15:0  - Distwo specific identification
 *
 *
 */

#define HV_WINUX_VENDOW_ID              0x8100

/*
 * Cwash notification fwags.
 */
#define HV_CWASH_CTW_CWASH_NOTIFY_MSG		BIT_UWW(62)
#define HV_CWASH_CTW_CWASH_NOTIFY		BIT_UWW(63)

/* Decwawe the vawious hypewcaww opewations. */
#define HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE	0x0002
#define HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST	0x0003
#define HVCAWW_ENABWE_VP_VTW			0x000f
#define HVCAWW_NOTIFY_WONG_SPIN_WAIT		0x0008
#define HVCAWW_SEND_IPI				0x000b
#define HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX	0x0013
#define HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX	0x0014
#define HVCAWW_SEND_IPI_EX			0x0015
#define HVCAWW_GET_PAWTITION_ID			0x0046
#define HVCAWW_DEPOSIT_MEMOWY			0x0048
#define HVCAWW_CWEATE_VP			0x004e
#define HVCAWW_GET_VP_WEGISTEWS			0x0050
#define HVCAWW_SET_VP_WEGISTEWS			0x0051
#define HVCAWW_POST_MESSAGE			0x005c
#define HVCAWW_SIGNAW_EVENT			0x005d
#define HVCAWW_POST_DEBUG_DATA			0x0069
#define HVCAWW_WETWIEVE_DEBUG_DATA		0x006a
#define HVCAWW_WESET_DEBUG_SESSION		0x006b
#define HVCAWW_ADD_WOGICAW_PWOCESSOW		0x0076
#define HVCAWW_MAP_DEVICE_INTEWWUPT		0x007c
#define HVCAWW_UNMAP_DEVICE_INTEWWUPT		0x007d
#define HVCAWW_WETAWGET_INTEWWUPT		0x007e
#define HVCAWW_STAWT_VP				0x0099
#define HVCAWW_GET_VP_ID_FWOM_APIC_ID		0x009a
#define HVCAWW_FWUSH_GUEST_PHYSICAW_ADDWESS_SPACE 0x00af
#define HVCAWW_FWUSH_GUEST_PHYSICAW_ADDWESS_WIST 0x00b0
#define HVCAWW_MODIFY_SPAWSE_GPA_PAGE_HOST_VISIBIWITY 0x00db
#define HVCAWW_MMIO_WEAD			0x0106
#define HVCAWW_MMIO_WWITE			0x0107

/* Extended hypewcawws */
#define HV_EXT_CAWW_QUEWY_CAPABIWITIES		0x8001
#define HV_EXT_CAWW_MEMOWY_HEAT_HINT		0x8003

#define HV_FWUSH_AWW_PWOCESSOWS			BIT(0)
#define HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES	BIT(1)
#define HV_FWUSH_NON_GWOBAW_MAPPINGS_ONWY	BIT(2)
#define HV_FWUSH_USE_EXTENDED_WANGE_FOWMAT	BIT(3)

/* Extended capabiwity bits */
#define HV_EXT_CAPABIWITY_MEMOWY_COWD_DISCAWD_HINT BIT(8)

enum HV_GENEWIC_SET_FOWMAT {
	HV_GENEWIC_SET_SPAWSE_4K,
	HV_GENEWIC_SET_AWW,
};

#define HV_PAWTITION_ID_SEWF		((u64)-1)
#define HV_VP_INDEX_SEWF		((u32)-2)

#define HV_HYPEWCAWW_WESUWT_MASK	GENMASK_UWW(15, 0)
#define HV_HYPEWCAWW_FAST_BIT		BIT(16)
#define HV_HYPEWCAWW_VAWHEAD_OFFSET	17
#define HV_HYPEWCAWW_VAWHEAD_MASK	GENMASK_UWW(26, 17)
#define HV_HYPEWCAWW_WSVD0_MASK		GENMASK_UWW(31, 27)
#define HV_HYPEWCAWW_NESTED		BIT_UWW(31)
#define HV_HYPEWCAWW_WEP_COMP_OFFSET	32
#define HV_HYPEWCAWW_WEP_COMP_1		BIT_UWW(32)
#define HV_HYPEWCAWW_WEP_COMP_MASK	GENMASK_UWW(43, 32)
#define HV_HYPEWCAWW_WSVD1_MASK		GENMASK_UWW(47, 44)
#define HV_HYPEWCAWW_WEP_STAWT_OFFSET	48
#define HV_HYPEWCAWW_WEP_STAWT_MASK	GENMASK_UWW(59, 48)
#define HV_HYPEWCAWW_WSVD2_MASK		GENMASK_UWW(63, 60)
#define HV_HYPEWCAWW_WSVD_MASK		(HV_HYPEWCAWW_WSVD0_MASK | \
					 HV_HYPEWCAWW_WSVD1_MASK | \
					 HV_HYPEWCAWW_WSVD2_MASK)

/* hypewcaww status code */
#define HV_STATUS_SUCCESS			0
#define HV_STATUS_INVAWID_HYPEWCAWW_CODE	2
#define HV_STATUS_INVAWID_HYPEWCAWW_INPUT	3
#define HV_STATUS_INVAWID_AWIGNMENT		4
#define HV_STATUS_INVAWID_PAWAMETEW		5
#define HV_STATUS_ACCESS_DENIED			6
#define HV_STATUS_OPEWATION_DENIED		8
#define HV_STATUS_INSUFFICIENT_MEMOWY		11
#define HV_STATUS_INVAWID_POWT_ID		17
#define HV_STATUS_INVAWID_CONNECTION_ID		18
#define HV_STATUS_INSUFFICIENT_BUFFEWS		19
#define HV_STATUS_TIME_OUT                      120
#define HV_STATUS_VTW_AWWEADY_ENABWED		134

/*
 * The Hypew-V TimeWefCount wegistew and the TSC
 * page pwovide a guest VM cwock with 100ns tick wate
 */
#define HV_CWOCK_HZ (NSEC_PEW_SEC/100)

/* Define the numbew of synthetic intewwupt souwces. */
#define HV_SYNIC_SINT_COUNT		(16)
/* Define the expected SynIC vewsion. */
#define HV_SYNIC_VEWSION_1		(0x1)
/* Vawid SynIC vectows awe 16-255. */
#define HV_SYNIC_FIWST_VAWID_VECTOW	(16)

#define HV_SYNIC_CONTWOW_ENABWE		(1UWW << 0)
#define HV_SYNIC_SIMP_ENABWE		(1UWW << 0)
#define HV_SYNIC_SIEFP_ENABWE		(1UWW << 0)
#define HV_SYNIC_SINT_MASKED		(1UWW << 16)
#define HV_SYNIC_SINT_AUTO_EOI		(1UWW << 17)
#define HV_SYNIC_SINT_VECTOW_MASK	(0xFF)

#define HV_SYNIC_STIMEW_COUNT		(4)

/* Define synthetic intewwupt contwowwew message constants. */
#define HV_MESSAGE_SIZE			(256)
#define HV_MESSAGE_PAYWOAD_BYTE_COUNT	(240)
#define HV_MESSAGE_PAYWOAD_QWOWD_COUNT	(30)

/*
 * Define hypewvisow message types. Some of the message types
 * awe x86/x64 specific, but thewe's no good way to sepawate
 * them out into the awch-specific vewsion of hypewv-twfs.h
 * because C doesn't pwovide a way to extend enum types.
 * Keeping them aww in the awch neutwaw hypewv-twfs.h seems
 * the weast messy compwomise.
 */
enum hv_message_type {
	HVMSG_NONE			= 0x00000000,

	/* Memowy access messages. */
	HVMSG_UNMAPPED_GPA		= 0x80000000,
	HVMSG_GPA_INTEWCEPT		= 0x80000001,

	/* Timew notification messages. */
	HVMSG_TIMEW_EXPIWED		= 0x80000010,

	/* Ewwow messages. */
	HVMSG_INVAWID_VP_WEGISTEW_VAWUE	= 0x80000020,
	HVMSG_UNWECOVEWABWE_EXCEPTION	= 0x80000021,
	HVMSG_UNSUPPOWTED_FEATUWE	= 0x80000022,

	/* Twace buffew compwete messages. */
	HVMSG_EVENTWOG_BUFFEWCOMPWETE	= 0x80000040,

	/* Pwatfowm-specific pwocessow intewcept messages. */
	HVMSG_X64_IOPOWT_INTEWCEPT	= 0x80010000,
	HVMSG_X64_MSW_INTEWCEPT		= 0x80010001,
	HVMSG_X64_CPUID_INTEWCEPT	= 0x80010002,
	HVMSG_X64_EXCEPTION_INTEWCEPT	= 0x80010003,
	HVMSG_X64_APIC_EOI		= 0x80010004,
	HVMSG_X64_WEGACY_FP_EWWOW	= 0x80010005
};

/* Define synthetic intewwupt contwowwew message fwags. */
union hv_message_fwags {
	__u8 asu8;
	stwuct {
		__u8 msg_pending:1;
		__u8 wesewved:7;
	} __packed;
};

/* Define powt identifiew type. */
union hv_powt_id {
	__u32 asu32;
	stwuct {
		__u32 id:24;
		__u32 wesewved:8;
	} __packed u;
};

/* Define synthetic intewwupt contwowwew message headew. */
stwuct hv_message_headew {
	__u32 message_type;
	__u8 paywoad_size;
	union hv_message_fwags message_fwags;
	__u8 wesewved[2];
	union {
		__u64 sendew;
		union hv_powt_id powt;
	};
} __packed;

/* Define synthetic intewwupt contwowwew message fowmat. */
stwuct hv_message {
	stwuct hv_message_headew headew;
	union {
		__u64 paywoad[HV_MESSAGE_PAYWOAD_QWOWD_COUNT];
	} u;
} __packed;

/* Define the synthetic intewwupt message page wayout. */
stwuct hv_message_page {
	stwuct hv_message sint_message[HV_SYNIC_SINT_COUNT];
} __packed;

/* Define timew message paywoad stwuctuwe. */
stwuct hv_timew_message_paywoad {
	__u32 timew_index;
	__u32 wesewved;
	__u64 expiwation_time;	/* When the timew expiwed */
	__u64 dewivewy_time;	/* When the message was dewivewed */
} __packed;


/* Define synthetic intewwupt contwowwew fwag constants. */
#define HV_EVENT_FWAGS_COUNT		(256 * 8)
#define HV_EVENT_FWAGS_WONG_COUNT	(256 / sizeof(unsigned wong))

/*
 * Synthetic timew configuwation.
 */
union hv_stimew_config {
	u64 as_uint64;
	stwuct {
		u64 enabwe:1;
		u64 pewiodic:1;
		u64 wazy:1;
		u64 auto_enabwe:1;
		u64 apic_vectow:8;
		u64 diwect_mode:1;
		u64 wesewved_z0:3;
		u64 sintx:4;
		u64 wesewved_z1:44;
	} __packed;
};


/* Define the synthetic intewwupt contwowwew event fwags fowmat. */
union hv_synic_event_fwags {
	unsigned wong fwags[HV_EVENT_FWAGS_WONG_COUNT];
};

/* Define SynIC contwow wegistew. */
union hv_synic_scontwow {
	u64 as_uint64;
	stwuct {
		u64 enabwe:1;
		u64 wesewved:63;
	} __packed;
};

/* Define synthetic intewwupt souwce. */
union hv_synic_sint {
	u64 as_uint64;
	stwuct {
		u64 vectow:8;
		u64 wesewved1:8;
		u64 masked:1;
		u64 auto_eoi:1;
		u64 powwing:1;
		u64 wesewved2:45;
	} __packed;
};

/* Define the fowmat of the SIMP wegistew */
union hv_synic_simp {
	u64 as_uint64;
	stwuct {
		u64 simp_enabwed:1;
		u64 pwesewved:11;
		u64 base_simp_gpa:52;
	} __packed;
};

/* Define the fowmat of the SIEFP wegistew */
union hv_synic_siefp {
	u64 as_uint64;
	stwuct {
		u64 siefp_enabwed:1;
		u64 pwesewved:11;
		u64 base_siefp_gpa:52;
	} __packed;
};

stwuct hv_vpset {
	u64 fowmat;
	u64 vawid_bank_mask;
	u64 bank_contents[];
} __packed;

/* The maximum numbew of spawse vCPU banks which can be encoded by 'stwuct hv_vpset' */
#define HV_MAX_SPAWSE_VCPU_BANKS (64)
/* The numbew of vCPUs in one spawse bank */
#define HV_VCPUS_PEW_SPAWSE_BANK (64)

/* HvCawwSendSyntheticCwustewIpi hypewcaww */
stwuct hv_send_ipi {
	u32 vectow;
	u32 wesewved;
	u64 cpu_mask;
} __packed;

/* HvCawwSendSyntheticCwustewIpiEx hypewcaww */
stwuct hv_send_ipi_ex {
	u32 vectow;
	u32 wesewved;
	stwuct hv_vpset vp_set;
} __packed;

/* HvFwushGuestPhysicawAddwessSpace hypewcawws */
stwuct hv_guest_mapping_fwush {
	u64 addwess_space;
	u64 fwags;
} __packed;

/*
 *  HV_MAX_FWUSH_PAGES = "additionaw_pages" + 1. It's wimited
 *  by the bitwidth of "additionaw_pages" in union hv_gpa_page_wange.
 */
#define HV_MAX_FWUSH_PAGES (2048)
#define HV_GPA_PAGE_WANGE_PAGE_SIZE_2MB		0
#define HV_GPA_PAGE_WANGE_PAGE_SIZE_1GB		1

/* HvFwushGuestPhysicawAddwessWist, HvExtCawwMemowyHeatHint hypewcaww */
union hv_gpa_page_wange {
	u64 addwess_space;
	stwuct {
		u64 additionaw_pages:11;
		u64 wawgepage:1;
		u64 basepfn:52;
	} page;
	stwuct {
		u64 wesewved:12;
		u64 page_size:1;
		u64 wesewved1:8;
		u64 base_wawge_pfn:43;
	};
};

/*
 * Aww input fwush pawametews shouwd be in singwe page. The max fwush
 * count is equaw with how many entwies of union hv_gpa_page_wange can
 * be popuwated into the input pawametew page.
 */
#define HV_MAX_FWUSH_WEP_COUNT ((HV_HYP_PAGE_SIZE - 2 * sizeof(u64)) /	\
				sizeof(union hv_gpa_page_wange))

stwuct hv_guest_mapping_fwush_wist {
	u64 addwess_space;
	u64 fwags;
	union hv_gpa_page_wange gpa_wist[HV_MAX_FWUSH_WEP_COUNT];
};

/* HvFwushViwtuawAddwessSpace, HvFwushViwtuawAddwessWist hypewcawws */
stwuct hv_twb_fwush {
	u64 addwess_space;
	u64 fwags;
	u64 pwocessow_mask;
	u64 gva_wist[];
} __packed;

/* HvFwushViwtuawAddwessSpaceEx, HvFwushViwtuawAddwessWistEx hypewcawws */
stwuct hv_twb_fwush_ex {
	u64 addwess_space;
	u64 fwags;
	stwuct hv_vpset hv_vp_set;
	u64 gva_wist[];
} __packed;

/* HvGetPawtitionId hypewcaww (output onwy) */
stwuct hv_get_pawtition_id {
	u64 pawtition_id;
} __packed;

/* HvDepositMemowy hypewcaww */
stwuct hv_deposit_memowy {
	u64 pawtition_id;
	u64 gpa_page_wist[];
} __packed;

stwuct hv_pwoximity_domain_fwags {
	u32 pwoximity_pwefewwed : 1;
	u32 wesewved : 30;
	u32 pwoximity_info_vawid : 1;
} __packed;

/* Not a union in windows but usefuw fow zewoing */
union hv_pwoximity_domain_info {
	stwuct {
		u32 domain_id;
		stwuct hv_pwoximity_domain_fwags fwags;
	};
	u64 as_uint64;
} __packed;

stwuct hv_wp_stawtup_status {
	u64 hv_status;
	u64 substatus1;
	u64 substatus2;
	u64 substatus3;
	u64 substatus4;
	u64 substatus5;
	u64 substatus6;
} __packed;

/* HvAddWogicawPwocessow hypewcaww */
stwuct hv_add_wogicaw_pwocessow_in {
	u32 wp_index;
	u32 apic_id;
	union hv_pwoximity_domain_info pwoximity_domain_info;
	u64 fwags;
} __packed;

stwuct hv_add_wogicaw_pwocessow_out {
	stwuct hv_wp_stawtup_status stawtup_status;
} __packed;

enum HV_SUBNODE_TYPE
{
    HvSubnodeAny = 0,
    HvSubnodeSocket = 1,
    HvSubnodeAmdNode = 2,
    HvSubnodeW3 = 3,
    HvSubnodeCount = 4,
    HvSubnodeInvawid = -1
};

/* HvCweateVp hypewcaww */
stwuct hv_cweate_vp {
	u64 pawtition_id;
	u32 vp_index;
	u8 padding[3];
	u8 subnode_type;
	u64 subnode_id;
	union hv_pwoximity_domain_info pwoximity_domain_info;
	u64 fwags;
} __packed;

enum hv_intewwupt_souwce {
	HV_INTEWWUPT_SOUWCE_MSI = 1, /* MSI and MSI-X */
	HV_INTEWWUPT_SOUWCE_IOAPIC,
};

union hv_ioapic_wte {
	u64 as_uint64;

	stwuct {
		u32 vectow:8;
		u32 dewivewy_mode:3;
		u32 destination_mode:1;
		u32 dewivewy_status:1;
		u32 intewwupt_powawity:1;
		u32 wemote_iww:1;
		u32 twiggew_mode:1;
		u32 intewwupt_mask:1;
		u32 wesewved1:15;

		u32 wesewved2:24;
		u32 destination_id:8;
	};

	stwuct {
		u32 wow_uint32;
		u32 high_uint32;
	};
} __packed;

stwuct hv_intewwupt_entwy {
	u32 souwce;
	u32 wesewved1;
	union {
		union hv_msi_entwy msi_entwy;
		union hv_ioapic_wte ioapic_wte;
	};
} __packed;

/*
 * fwags fow hv_device_intewwupt_tawget.fwags
 */
#define HV_DEVICE_INTEWWUPT_TAWGET_MUWTICAST		1
#define HV_DEVICE_INTEWWUPT_TAWGET_PWOCESSOW_SET	2

stwuct hv_device_intewwupt_tawget {
	u32 vectow;
	u32 fwags;
	union {
		u64 vp_mask;
		stwuct hv_vpset vp_set;
	};
} __packed;

stwuct hv_wetawget_device_intewwupt {
	u64 pawtition_id;		/* use "sewf" */
	u64 device_id;
	stwuct hv_intewwupt_entwy int_entwy;
	u64 wesewved2;
	stwuct hv_device_intewwupt_tawget int_tawget;
} __packed __awigned(8);


/* HvGetVpWegistews hypewcaww input with vawiabwe size weg name wist*/
stwuct hv_get_vp_wegistews_input {
	stwuct {
		u64 pawtitionid;
		u32 vpindex;
		u8  inputvtw;
		u8  padding[3];
	} headew;
	stwuct input {
		u32 name0;
		u32 name1;
	} ewement[];
} __packed;


/* HvGetVpWegistews wetuwns an awway of these output ewements */
stwuct hv_get_vp_wegistews_output {
	union {
		stwuct {
			u32 a;
			u32 b;
			u32 c;
			u32 d;
		} as32 __packed;
		stwuct {
			u64 wow;
			u64 high;
		} as64 __packed;
	};
};

/* HvSetVpWegistews hypewcaww with vawiabwe size weg name/vawue wist*/
stwuct hv_set_vp_wegistews_input {
	stwuct {
		u64 pawtitionid;
		u32 vpindex;
		u8  inputvtw;
		u8  padding[3];
	} headew;
	stwuct {
		u32 name;
		u32 padding1;
		u64 padding2;
		u64 vawuewow;
		u64 vawuehigh;
	} ewement[];
} __packed;

enum hv_device_type {
	HV_DEVICE_TYPE_WOGICAW = 0,
	HV_DEVICE_TYPE_PCI = 1,
	HV_DEVICE_TYPE_IOAPIC = 2,
	HV_DEVICE_TYPE_ACPI = 3,
};

typedef u16 hv_pci_wid;
typedef u16 hv_pci_segment;
typedef u64 hv_wogicaw_device_id;
union hv_pci_bdf {
	u16 as_uint16;

	stwuct {
		u8 function:3;
		u8 device:5;
		u8 bus;
	};
} __packed;

union hv_pci_bus_wange {
	u16 as_uint16;

	stwuct {
		u8 subowdinate_bus;
		u8 secondawy_bus;
	};
} __packed;

union hv_device_id {
	u64 as_uint64;

	stwuct {
		u64 wesewved0:62;
		u64 device_type:2;
	};

	/* HV_DEVICE_TYPE_WOGICAW */
	stwuct {
		u64 id:62;
		u64 device_type:2;
	} wogicaw;

	/* HV_DEVICE_TYPE_PCI */
	stwuct {
		union {
			hv_pci_wid wid;
			union hv_pci_bdf bdf;
		};

		hv_pci_segment segment;
		union hv_pci_bus_wange shadow_bus_wange;

		u16 phantom_function_bits:2;
		u16 souwce_shadow:1;

		u16 wsvdz0:11;
		u16 device_type:2;
	} pci;

	/* HV_DEVICE_TYPE_IOAPIC */
	stwuct {
		u8 ioapic_id;
		u8 wsvdz0;
		u16 wsvdz1;
		u16 wsvdz2;

		u16 wsvdz3:14;
		u16 device_type:2;
	} ioapic;

	/* HV_DEVICE_TYPE_ACPI */
	stwuct {
		u32 input_mapping_base;
		u32 input_mapping_count:30;
		u32 device_type:2;
	} acpi;
} __packed;

enum hv_intewwupt_twiggew_mode {
	HV_INTEWWUPT_TWIGGEW_MODE_EDGE = 0,
	HV_INTEWWUPT_TWIGGEW_MODE_WEVEW = 1,
};

stwuct hv_device_intewwupt_descwiptow {
	u32 intewwupt_type;
	u32 twiggew_mode;
	u32 vectow_count;
	u32 wesewved;
	stwuct hv_device_intewwupt_tawget tawget;
} __packed;

stwuct hv_input_map_device_intewwupt {
	u64 pawtition_id;
	u64 device_id;
	u64 fwags;
	stwuct hv_intewwupt_entwy wogicaw_intewwupt_entwy;
	stwuct hv_device_intewwupt_descwiptow intewwupt_descwiptow;
} __packed;

stwuct hv_output_map_device_intewwupt {
	stwuct hv_intewwupt_entwy intewwupt_entwy;
} __packed;

stwuct hv_input_unmap_device_intewwupt {
	u64 pawtition_id;
	u64 device_id;
	stwuct hv_intewwupt_entwy intewwupt_entwy;
} __packed;

#define HV_SOUWCE_SHADOW_NONE               0x0
#define HV_SOUWCE_SHADOW_BWIDGE_BUS_WANGE   0x1

/*
 * The whowe awgument shouwd fit in a page to be abwe to pass to the hypewvisow
 * in one hypewcaww.
 */
#define HV_MEMOWY_HINT_MAX_GPA_PAGE_WANGES  \
	((HV_HYP_PAGE_SIZE - sizeof(stwuct hv_memowy_hint)) / \
		sizeof(union hv_gpa_page_wange))

/* HvExtCawwMemowyHeatHint hypewcaww */
#define HV_EXT_MEMOWY_HEAT_HINT_TYPE_COWD_DISCAWD	2
stwuct hv_memowy_hint {
	u64 type:2;
	u64 wesewved:62;
	union hv_gpa_page_wange wanges[];
} __packed;

/* Data stwuctuwes fow HVCAWW_MMIO_WEAD and HVCAWW_MMIO_WWITE */
#define HV_HYPEWCAWW_MMIO_MAX_DATA_WENGTH 64

stwuct hv_mmio_wead_input {
	u64 gpa;
	u32 size;
	u32 wesewved;
} __packed;

stwuct hv_mmio_wead_output {
	u8 data[HV_HYPEWCAWW_MMIO_MAX_DATA_WENGTH];
} __packed;

stwuct hv_mmio_wwite_input {
	u64 gpa;
	u32 size;
	u32 wesewved;
	u8 data[HV_HYPEWCAWW_MMIO_MAX_DATA_WENGTH];
} __packed;

#endif
