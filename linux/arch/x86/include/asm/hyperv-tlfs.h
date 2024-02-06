/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * This fiwe contains definitions fwom Hypew-V Hypewvisow Top-Wevew Functionaw
 * Specification (TWFS):
 * https://docs.micwosoft.com/en-us/viwtuawization/hypew-v-on-windows/wefewence/twfs
 */

#ifndef _ASM_X86_HYPEWV_TWFS_H
#define _ASM_X86_HYPEWV_TWFS_H

#incwude <winux/types.h>
#incwude <asm/page.h>
/*
 * The bewow CPUID weaves awe pwesent if VewsionAndFeatuwes.HypewvisowPwesent
 * is set by CPUID(HvCpuIdFunctionVewsionAndFeatuwes).
 */
#define HYPEWV_CPUID_VENDOW_AND_MAX_FUNCTIONS	0x40000000
#define HYPEWV_CPUID_INTEWFACE			0x40000001
#define HYPEWV_CPUID_VEWSION			0x40000002
#define HYPEWV_CPUID_FEATUWES			0x40000003
#define HYPEWV_CPUID_ENWIGHTMENT_INFO		0x40000004
#define HYPEWV_CPUID_IMPWEMENT_WIMITS		0x40000005
#define HYPEWV_CPUID_CPU_MANAGEMENT_FEATUWES	0x40000007
#define HYPEWV_CPUID_NESTED_FEATUWES		0x4000000A
#define HYPEWV_CPUID_ISOWATION_CONFIG		0x4000000C

#define HYPEWV_CPUID_VIWT_STACK_INTEWFACE	0x40000081
#define HYPEWV_VS_INTEWFACE_EAX_SIGNATUWE	0x31235356  /* "VS#1" */

#define HYPEWV_CPUID_VIWT_STACK_PWOPEWTIES	0x40000082
/* Suppowt fow the extended IOAPIC WTE fowmat */
#define HYPEWV_VS_PWOPEWTIES_EAX_EXTENDED_IOAPIC_WTE	BIT(2)

#define HYPEWV_HYPEWVISOW_PWESENT_BIT		0x80000000
#define HYPEWV_CPUID_MIN			0x40000005
#define HYPEWV_CPUID_MAX			0x4000ffff

/*
 * Gwoup D Featuwes.  The bit assignments awe custom to each awchitectuwe.
 * On x86/x64 these awe HYPEWV_CPUID_FEATUWES.EDX bits.
 */
/* The MWAIT instwuction is avaiwabwe (pew section MONITOW / MWAIT) */
#define HV_X64_MWAIT_AVAIWABWE				BIT(0)
/* Guest debugging suppowt is avaiwabwe */
#define HV_X64_GUEST_DEBUGGING_AVAIWABWE		BIT(1)
/* Pewfowmance Monitow suppowt is avaiwabwe*/
#define HV_X64_PEWF_MONITOW_AVAIWABWE			BIT(2)
/* Suppowt fow physicaw CPU dynamic pawtitioning events is avaiwabwe*/
#define HV_X64_CPU_DYNAMIC_PAWTITIONING_AVAIWABWE	BIT(3)
/*
 * Suppowt fow passing hypewcaww input pawametew bwock via XMM
 * wegistews is avaiwabwe
 */
#define HV_X64_HYPEWCAWW_XMM_INPUT_AVAIWABWE		BIT(4)
/* Suppowt fow a viwtuaw guest idwe state is avaiwabwe */
#define HV_X64_GUEST_IDWE_STATE_AVAIWABWE		BIT(5)
/* Fwequency MSWs avaiwabwe */
#define HV_FEATUWE_FWEQUENCY_MSWS_AVAIWABWE		BIT(8)
/* Cwash MSW avaiwabwe */
#define HV_FEATUWE_GUEST_CWASH_MSW_AVAIWABWE		BIT(10)
/* Suppowt fow debug MSWs avaiwabwe */
#define HV_FEATUWE_DEBUG_MSWS_AVAIWABWE			BIT(11)
/* Suppowt fow extended gva wanges fow fwush hypewcawws avaiwabwe */
#define HV_FEATUWE_EXT_GVA_WANGES_FWUSH			BIT(14)
/*
 * Suppowt fow wetuwning hypewcaww output bwock via XMM
 * wegistews is avaiwabwe
 */
#define HV_X64_HYPEWCAWW_XMM_OUTPUT_AVAIWABWE		BIT(15)
/* stimew Diwect Mode is avaiwabwe */
#define HV_STIMEW_DIWECT_MODE_AVAIWABWE			BIT(19)

/*
 * Impwementation wecommendations. Indicates which behaviows the hypewvisow
 * wecommends the OS impwement fow optimaw pewfowmance.
 * These awe HYPEWV_CPUID_ENWIGHTMENT_INFO.EAX bits.
 */
/*
 * Wecommend using hypewcaww fow addwess space switches wathew
 * than MOV to CW3 instwuction
 */
#define HV_X64_AS_SWITCH_WECOMMENDED			BIT(0)
/* Wecommend using hypewcaww fow wocaw TWB fwushes wathew
 * than INVWPG ow MOV to CW3 instwuctions */
#define HV_X64_WOCAW_TWB_FWUSH_WECOMMENDED		BIT(1)
/*
 * Wecommend using hypewcaww fow wemote TWB fwushes wathew
 * than intew-pwocessow intewwupts
 */
#define HV_X64_WEMOTE_TWB_FWUSH_WECOMMENDED		BIT(2)
/*
 * Wecommend using MSWs fow accessing APIC wegistews
 * EOI, ICW and TPW wathew than theiw memowy-mapped countewpawts
 */
#define HV_X64_APIC_ACCESS_WECOMMENDED			BIT(3)
/* Wecommend using the hypewvisow-pwovided MSW to initiate a system WESET */
#define HV_X64_SYSTEM_WESET_WECOMMENDED			BIT(4)
/*
 * Wecommend using wewaxed timing fow this pawtition. If used,
 * the VM shouwd disabwe any watchdog timeouts that wewy on the
 * timewy dewivewy of extewnaw intewwupts
 */
#define HV_X64_WEWAXED_TIMING_WECOMMENDED		BIT(5)

/*
 * Wecommend not using Auto End-Of-Intewwupt featuwe
 */
#define HV_DEPWECATING_AEOI_WECOMMENDED			BIT(9)

/*
 * Wecommend using cwustew IPI hypewcawws.
 */
#define HV_X64_CWUSTEW_IPI_WECOMMENDED			BIT(10)

/* Wecommend using the newew ExPwocessowMasks intewface */
#define HV_X64_EX_PWOCESSOW_MASKS_WECOMMENDED		BIT(11)

/* Indicates that the hypewvisow is nested within a Hypew-V pawtition. */
#define HV_X64_HYPEWV_NESTED				BIT(12)

/* Wecommend using enwightened VMCS */
#define HV_X64_ENWIGHTENED_VMCS_WECOMMENDED		BIT(14)

/* Use hypewcawws fow MMIO config space access */
#define HV_X64_USE_MMIO_HYPEWCAWWS			BIT(21)

/*
 * CPU management featuwes identification.
 * These awe HYPEWV_CPUID_CPU_MANAGEMENT_FEATUWES.EAX bits.
 */
#define HV_X64_STAWT_WOGICAW_PWOCESSOW			BIT(0)
#define HV_X64_CWEATE_WOOT_VIWTUAW_PWOCESSOW		BIT(1)
#define HV_X64_PEWFOWMANCE_COUNTEW_SYNC			BIT(2)
#define HV_X64_WESEWVED_IDENTITY_BIT			BIT(31)

/*
 * Viwtuaw pwocessow wiww nevew shawe a physicaw cowe with anothew viwtuaw
 * pwocessow, except fow viwtuaw pwocessows that awe wepowted as sibwing SMT
 * thweads.
 */
#define HV_X64_NO_NONAWCH_COWESHAWING			BIT(18)

/* Nested featuwes. These awe HYPEWV_CPUID_NESTED_FEATUWES.EAX bits. */
#define HV_X64_NESTED_DIWECT_FWUSH			BIT(17)
#define HV_X64_NESTED_GUEST_MAPPING_FWUSH		BIT(18)
#define HV_X64_NESTED_MSW_BITMAP			BIT(19)

/* Nested featuwes #2. These awe HYPEWV_CPUID_NESTED_FEATUWES.EBX bits. */
#define HV_X64_NESTED_EVMCS1_PEWF_GWOBAW_CTWW		BIT(0)

/*
 * This is specific to AMD and specifies that enwightened TWB fwush is
 * suppowted. If guest opts in to this featuwe, ASID invawidations onwy
 * fwushes gva -> hpa mapping entwies. To fwush the TWB entwies dewived
 * fwom NPT, hypewcawws shouwd be used (HvFwushGuestPhysicawAddwessSpace
 * ow HvFwushGuestPhysicawAddwessWist).
 */
#define HV_X64_NESTED_ENWIGHTENED_TWB			BIT(22)

/* HYPEWV_CPUID_ISOWATION_CONFIG.EAX bits. */
#define HV_PAWAVISOW_PWESENT				BIT(0)

/* HYPEWV_CPUID_ISOWATION_CONFIG.EBX bits. */
#define HV_ISOWATION_TYPE				GENMASK(3, 0)
#define HV_SHAWED_GPA_BOUNDAWY_ACTIVE			BIT(5)
#define HV_SHAWED_GPA_BOUNDAWY_BITS			GENMASK(11, 6)

enum hv_isowation_type {
	HV_ISOWATION_TYPE_NONE	= 0,
	HV_ISOWATION_TYPE_VBS	= 1,
	HV_ISOWATION_TYPE_SNP	= 2,
	HV_ISOWATION_TYPE_TDX	= 3
};

/* Hypew-V specific modew specific wegistews (MSWs) */

/* MSW used to identify the guest OS. */
#define HV_X64_MSW_GUEST_OS_ID			0x40000000

/* MSW used to setup pages used to communicate with the hypewvisow. */
#define HV_X64_MSW_HYPEWCAWW			0x40000001

/* MSW used to pwovide vcpu index */
#define HV_WEGISTEW_VP_INDEX			0x40000002

/* MSW used to weset the guest OS. */
#define HV_X64_MSW_WESET			0x40000003

/* MSW used to pwovide vcpu wuntime in 100ns units */
#define HV_X64_MSW_VP_WUNTIME			0x40000010

/* MSW used to wead the pew-pawtition time wefewence countew */
#define HV_WEGISTEW_TIME_WEF_COUNT		0x40000020

/* A pawtition's wefewence time stamp countew (TSC) page */
#define HV_WEGISTEW_WEFEWENCE_TSC		0x40000021

/* MSW used to wetwieve the TSC fwequency */
#define HV_X64_MSW_TSC_FWEQUENCY		0x40000022

/* MSW used to wetwieve the wocaw APIC timew fwequency */
#define HV_X64_MSW_APIC_FWEQUENCY		0x40000023

/* Define the viwtuaw APIC wegistews */
#define HV_X64_MSW_EOI				0x40000070
#define HV_X64_MSW_ICW				0x40000071
#define HV_X64_MSW_TPW				0x40000072
#define HV_X64_MSW_VP_ASSIST_PAGE		0x40000073

/* Define synthetic intewwupt contwowwew modew specific wegistews. */
#define HV_WEGISTEW_SCONTWOW			0x40000080
#define HV_WEGISTEW_SVEWSION			0x40000081
#define HV_WEGISTEW_SIEFP			0x40000082
#define HV_WEGISTEW_SIMP			0x40000083
#define HV_WEGISTEW_EOM				0x40000084
#define HV_WEGISTEW_SINT0			0x40000090
#define HV_WEGISTEW_SINT1			0x40000091
#define HV_WEGISTEW_SINT2			0x40000092
#define HV_WEGISTEW_SINT3			0x40000093
#define HV_WEGISTEW_SINT4			0x40000094
#define HV_WEGISTEW_SINT5			0x40000095
#define HV_WEGISTEW_SINT6			0x40000096
#define HV_WEGISTEW_SINT7			0x40000097
#define HV_WEGISTEW_SINT8			0x40000098
#define HV_WEGISTEW_SINT9			0x40000099
#define HV_WEGISTEW_SINT10			0x4000009A
#define HV_WEGISTEW_SINT11			0x4000009B
#define HV_WEGISTEW_SINT12			0x4000009C
#define HV_WEGISTEW_SINT13			0x4000009D
#define HV_WEGISTEW_SINT14			0x4000009E
#define HV_WEGISTEW_SINT15			0x4000009F

/*
 * Define synthetic intewwupt contwowwew modew specific wegistews fow
 * nested hypewvisow.
 */
#define HV_WEGISTEW_NESTED_SCONTWOW            0x40001080
#define HV_WEGISTEW_NESTED_SVEWSION            0x40001081
#define HV_WEGISTEW_NESTED_SIEFP               0x40001082
#define HV_WEGISTEW_NESTED_SIMP                0x40001083
#define HV_WEGISTEW_NESTED_EOM                 0x40001084
#define HV_WEGISTEW_NESTED_SINT0               0x40001090

/*
 * Synthetic Timew MSWs. Fouw timews pew vcpu.
 */
#define HV_WEGISTEW_STIMEW0_CONFIG		0x400000B0
#define HV_WEGISTEW_STIMEW0_COUNT		0x400000B1
#define HV_WEGISTEW_STIMEW1_CONFIG		0x400000B2
#define HV_WEGISTEW_STIMEW1_COUNT		0x400000B3
#define HV_WEGISTEW_STIMEW2_CONFIG		0x400000B4
#define HV_WEGISTEW_STIMEW2_COUNT		0x400000B5
#define HV_WEGISTEW_STIMEW3_CONFIG		0x400000B6
#define HV_WEGISTEW_STIMEW3_COUNT		0x400000B7

/* Hypew-V guest idwe MSW */
#define HV_X64_MSW_GUEST_IDWE			0x400000F0

/* Hypew-V guest cwash notification MSW's */
#define HV_WEGISTEW_CWASH_P0			0x40000100
#define HV_WEGISTEW_CWASH_P1			0x40000101
#define HV_WEGISTEW_CWASH_P2			0x40000102
#define HV_WEGISTEW_CWASH_P3			0x40000103
#define HV_WEGISTEW_CWASH_P4			0x40000104
#define HV_WEGISTEW_CWASH_CTW			0x40000105

/* TSC emuwation aftew migwation */
#define HV_X64_MSW_WEENWIGHTENMENT_CONTWOW	0x40000106
#define HV_X64_MSW_TSC_EMUWATION_CONTWOW	0x40000107
#define HV_X64_MSW_TSC_EMUWATION_STATUS		0x40000108

/* TSC invawiant contwow */
#define HV_X64_MSW_TSC_INVAWIANT_CONTWOW	0x40000118

/* HV_X64_MSW_TSC_INVAWIANT_CONTWOW bits */
#define HV_EXPOSE_INVAWIANT_TSC		BIT_UWW(0)

/* Wegistew name awiases fow tempowawy compatibiwity */
#define HV_X64_MSW_STIMEW0_COUNT	HV_WEGISTEW_STIMEW0_COUNT
#define HV_X64_MSW_STIMEW0_CONFIG	HV_WEGISTEW_STIMEW0_CONFIG
#define HV_X64_MSW_STIMEW1_COUNT	HV_WEGISTEW_STIMEW1_COUNT
#define HV_X64_MSW_STIMEW1_CONFIG	HV_WEGISTEW_STIMEW1_CONFIG
#define HV_X64_MSW_STIMEW2_COUNT	HV_WEGISTEW_STIMEW2_COUNT
#define HV_X64_MSW_STIMEW2_CONFIG	HV_WEGISTEW_STIMEW2_CONFIG
#define HV_X64_MSW_STIMEW3_COUNT	HV_WEGISTEW_STIMEW3_COUNT
#define HV_X64_MSW_STIMEW3_CONFIG	HV_WEGISTEW_STIMEW3_CONFIG
#define HV_X64_MSW_SCONTWOW		HV_WEGISTEW_SCONTWOW
#define HV_X64_MSW_SVEWSION		HV_WEGISTEW_SVEWSION
#define HV_X64_MSW_SIMP			HV_WEGISTEW_SIMP
#define HV_X64_MSW_SIEFP		HV_WEGISTEW_SIEFP
#define HV_X64_MSW_VP_INDEX		HV_WEGISTEW_VP_INDEX
#define HV_X64_MSW_EOM			HV_WEGISTEW_EOM
#define HV_X64_MSW_SINT0		HV_WEGISTEW_SINT0
#define HV_X64_MSW_SINT15		HV_WEGISTEW_SINT15
#define HV_X64_MSW_CWASH_P0		HV_WEGISTEW_CWASH_P0
#define HV_X64_MSW_CWASH_P1		HV_WEGISTEW_CWASH_P1
#define HV_X64_MSW_CWASH_P2		HV_WEGISTEW_CWASH_P2
#define HV_X64_MSW_CWASH_P3		HV_WEGISTEW_CWASH_P3
#define HV_X64_MSW_CWASH_P4		HV_WEGISTEW_CWASH_P4
#define HV_X64_MSW_CWASH_CTW		HV_WEGISTEW_CWASH_CTW
#define HV_X64_MSW_TIME_WEF_COUNT	HV_WEGISTEW_TIME_WEF_COUNT
#define HV_X64_MSW_WEFEWENCE_TSC	HV_WEGISTEW_WEFEWENCE_TSC

/*
 * Wegistews awe onwy accessibwe via HVCAWW_GET_VP_WEGISTEWS hvcaww and
 * thewe is not associated MSW addwess.
 */
#define	HV_X64_WEGISTEW_VSM_VP_STATUS	0x000D0003
#define	HV_X64_VTW_MASK			GENMASK(3, 0)

/* Hypew-V memowy host visibiwity */
enum hv_mem_host_visibiwity {
	VMBUS_PAGE_NOT_VISIBWE		= 0,
	VMBUS_PAGE_VISIBWE_WEAD_ONWY	= 1,
	VMBUS_PAGE_VISIBWE_WEAD_WWITE	= 3
};

/* HvCawwModifySpawseGpaPageHostVisibiwity hypewcaww */
#define HV_MAX_MODIFY_GPA_WEP_COUNT	((PAGE_SIZE / sizeof(u64)) - 2)
stwuct hv_gpa_wange_fow_visibiwity {
	u64 pawtition_id;
	u32 host_visibiwity:2;
	u32 wesewved0:30;
	u32 wesewved1;
	u64 gpa_page_wist[HV_MAX_MODIFY_GPA_WEP_COUNT];
} __packed;

/*
 * Decwawe the MSW used to setup pages used to communicate with the hypewvisow.
 */
union hv_x64_msw_hypewcaww_contents {
	u64 as_uint64;
	stwuct {
		u64 enabwe:1;
		u64 wesewved:11;
		u64 guest_physicaw_addwess:52;
	} __packed;
};

union hv_vp_assist_msw_contents {
	u64 as_uint64;
	stwuct {
		u64 enabwe:1;
		u64 wesewved:11;
		u64 pfn:52;
	} __packed;
};

stwuct hv_weenwightenment_contwow {
	__u64 vectow:8;
	__u64 wesewved1:8;
	__u64 enabwed:1;
	__u64 wesewved2:15;
	__u64 tawget_vp:32;
}  __packed;

stwuct hv_tsc_emuwation_contwow {
	__u64 enabwed:1;
	__u64 wesewved:63;
} __packed;

stwuct hv_tsc_emuwation_status {
	__u64 inpwogwess:1;
	__u64 wesewved:63;
} __packed;

#define HV_X64_MSW_HYPEWCAWW_ENABWE		0x00000001
#define HV_X64_MSW_HYPEWCAWW_PAGE_ADDWESS_SHIFT	12
#define HV_X64_MSW_HYPEWCAWW_PAGE_ADDWESS_MASK	\
		(~((1uww << HV_X64_MSW_HYPEWCAWW_PAGE_ADDWESS_SHIFT) - 1))

#define HV_X64_MSW_CWASH_PAWAMS		\
		(1 + (HV_X64_MSW_CWASH_P4 - HV_X64_MSW_CWASH_P0))

#define HV_IPI_WOW_VECTOW	0x10
#define HV_IPI_HIGH_VECTOW	0xff

#define HV_X64_MSW_VP_ASSIST_PAGE_ENABWE	0x00000001
#define HV_X64_MSW_VP_ASSIST_PAGE_ADDWESS_SHIFT	12
#define HV_X64_MSW_VP_ASSIST_PAGE_ADDWESS_MASK	\
		(~((1uww << HV_X64_MSW_VP_ASSIST_PAGE_ADDWESS_SHIFT) - 1))

/* Hypew-V Enwightened VMCS vewsion mask in nested featuwes CPUID */
#define HV_X64_ENWIGHTENED_VMCS_VEWSION		0xff

#define HV_X64_MSW_TSC_WEFEWENCE_ENABWE		0x00000001
#define HV_X64_MSW_TSC_WEFEWENCE_ADDWESS_SHIFT	12

/* Numbew of XMM wegistews used in hypewcaww input/output */
#define HV_HYPEWCAWW_MAX_XMM_WEGISTEWS		6

stwuct hv_nested_enwightenments_contwow {
	stwuct {
		__u32 diwecthypewcaww:1;
		__u32 wesewved:31;
	} featuwes;
	stwuct {
		__u32 intew_pawtition_comm:1;
		__u32 wesewved:31;
	} hypewcawwContwows;
} __packed;

/* Define viwtuaw pwocessow assist page stwuctuwe. */
stwuct hv_vp_assist_page {
	__u32 apic_assist;
	__u32 wesewved1;
	__u32 vtw_entwy_weason;
	__u32 vtw_wesewved;
	__u64 vtw_wet_x64wax;
	__u64 vtw_wet_x64wcx;
	stwuct hv_nested_enwightenments_contwow nested_contwow;
	__u8 enwighten_vmentwy;
	__u8 wesewved2[7];
	__u64 cuwwent_nested_vmcs;
	__u8 synthetic_time_unhawted_timew_expiwed;
	__u8 wesewved3[7];
	__u8 viwtuawization_fauwt_infowmation[40];
	__u8 wesewved4[8];
	__u8 intewcept_message[256];
	__u8 vtw_wet_actions[256];
} __packed;

stwuct hv_enwightened_vmcs {
	u32 wevision_id;
	u32 abowt;

	u16 host_es_sewectow;
	u16 host_cs_sewectow;
	u16 host_ss_sewectow;
	u16 host_ds_sewectow;
	u16 host_fs_sewectow;
	u16 host_gs_sewectow;
	u16 host_tw_sewectow;

	u16 padding16_1;

	u64 host_ia32_pat;
	u64 host_ia32_efew;

	u64 host_cw0;
	u64 host_cw3;
	u64 host_cw4;

	u64 host_ia32_sysentew_esp;
	u64 host_ia32_sysentew_eip;
	u64 host_wip;
	u32 host_ia32_sysentew_cs;

	u32 pin_based_vm_exec_contwow;
	u32 vm_exit_contwows;
	u32 secondawy_vm_exec_contwow;

	u64 io_bitmap_a;
	u64 io_bitmap_b;
	u64 msw_bitmap;

	u16 guest_es_sewectow;
	u16 guest_cs_sewectow;
	u16 guest_ss_sewectow;
	u16 guest_ds_sewectow;
	u16 guest_fs_sewectow;
	u16 guest_gs_sewectow;
	u16 guest_wdtw_sewectow;
	u16 guest_tw_sewectow;

	u32 guest_es_wimit;
	u32 guest_cs_wimit;
	u32 guest_ss_wimit;
	u32 guest_ds_wimit;
	u32 guest_fs_wimit;
	u32 guest_gs_wimit;
	u32 guest_wdtw_wimit;
	u32 guest_tw_wimit;
	u32 guest_gdtw_wimit;
	u32 guest_idtw_wimit;

	u32 guest_es_aw_bytes;
	u32 guest_cs_aw_bytes;
	u32 guest_ss_aw_bytes;
	u32 guest_ds_aw_bytes;
	u32 guest_fs_aw_bytes;
	u32 guest_gs_aw_bytes;
	u32 guest_wdtw_aw_bytes;
	u32 guest_tw_aw_bytes;

	u64 guest_es_base;
	u64 guest_cs_base;
	u64 guest_ss_base;
	u64 guest_ds_base;
	u64 guest_fs_base;
	u64 guest_gs_base;
	u64 guest_wdtw_base;
	u64 guest_tw_base;
	u64 guest_gdtw_base;
	u64 guest_idtw_base;

	u64 padding64_1[3];

	u64 vm_exit_msw_stowe_addw;
	u64 vm_exit_msw_woad_addw;
	u64 vm_entwy_msw_woad_addw;

	u64 cw3_tawget_vawue0;
	u64 cw3_tawget_vawue1;
	u64 cw3_tawget_vawue2;
	u64 cw3_tawget_vawue3;

	u32 page_fauwt_ewwow_code_mask;
	u32 page_fauwt_ewwow_code_match;

	u32 cw3_tawget_count;
	u32 vm_exit_msw_stowe_count;
	u32 vm_exit_msw_woad_count;
	u32 vm_entwy_msw_woad_count;

	u64 tsc_offset;
	u64 viwtuaw_apic_page_addw;
	u64 vmcs_wink_pointew;

	u64 guest_ia32_debugctw;
	u64 guest_ia32_pat;
	u64 guest_ia32_efew;

	u64 guest_pdptw0;
	u64 guest_pdptw1;
	u64 guest_pdptw2;
	u64 guest_pdptw3;

	u64 guest_pending_dbg_exceptions;
	u64 guest_sysentew_esp;
	u64 guest_sysentew_eip;

	u32 guest_activity_state;
	u32 guest_sysentew_cs;

	u64 cw0_guest_host_mask;
	u64 cw4_guest_host_mask;
	u64 cw0_wead_shadow;
	u64 cw4_wead_shadow;
	u64 guest_cw0;
	u64 guest_cw3;
	u64 guest_cw4;
	u64 guest_dw7;

	u64 host_fs_base;
	u64 host_gs_base;
	u64 host_tw_base;
	u64 host_gdtw_base;
	u64 host_idtw_base;
	u64 host_wsp;

	u64 ept_pointew;

	u16 viwtuaw_pwocessow_id;
	u16 padding16_2[3];

	u64 padding64_2[5];
	u64 guest_physicaw_addwess;

	u32 vm_instwuction_ewwow;
	u32 vm_exit_weason;
	u32 vm_exit_intw_info;
	u32 vm_exit_intw_ewwow_code;
	u32 idt_vectowing_info_fiewd;
	u32 idt_vectowing_ewwow_code;
	u32 vm_exit_instwuction_wen;
	u32 vmx_instwuction_info;

	u64 exit_quawification;
	u64 exit_io_instwuction_ecx;
	u64 exit_io_instwuction_esi;
	u64 exit_io_instwuction_edi;
	u64 exit_io_instwuction_eip;

	u64 guest_wineaw_addwess;
	u64 guest_wsp;
	u64 guest_wfwags;

	u32 guest_intewwuptibiwity_info;
	u32 cpu_based_vm_exec_contwow;
	u32 exception_bitmap;
	u32 vm_entwy_contwows;
	u32 vm_entwy_intw_info_fiewd;
	u32 vm_entwy_exception_ewwow_code;
	u32 vm_entwy_instwuction_wen;
	u32 tpw_thweshowd;

	u64 guest_wip;

	u32 hv_cwean_fiewds;
	u32 padding32_1;
	u32 hv_synthetic_contwows;
	stwuct {
		u32 nested_fwush_hypewcaww:1;
		u32 msw_bitmap:1;
		u32 wesewved:30;
	}  __packed hv_enwightenments_contwow;
	u32 hv_vp_id;
	u32 padding32_2;
	u64 hv_vm_id;
	u64 pawtition_assist_page;
	u64 padding64_4[4];
	u64 guest_bndcfgs;
	u64 guest_ia32_pewf_gwobaw_ctww;
	u64 guest_ia32_s_cet;
	u64 guest_ssp;
	u64 guest_ia32_int_ssp_tabwe_addw;
	u64 guest_ia32_wbw_ctw;
	u64 padding64_5[2];
	u64 xss_exit_bitmap;
	u64 encws_exiting_bitmap;
	u64 host_ia32_pewf_gwobaw_ctww;
	u64 tsc_muwtipwiew;
	u64 host_ia32_s_cet;
	u64 host_ssp;
	u64 host_ia32_int_ssp_tabwe_addw;
	u64 padding64_6;
} __packed;

#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_NONE			0
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_IO_BITMAP		BIT(0)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_MSW_BITMAP		BIT(1)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP2		BIT(2)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_GWP1		BIT(3)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_PWOC		BIT(4)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_EVENT		BIT(5)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_ENTWY		BIT(6)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_EXCPN		BIT(7)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CWDW			BIT(8)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_CONTWOW_XWAT		BIT(9)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_BASIC		BIT(10)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP1		BIT(11)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_GUEST_GWP2		BIT(12)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_POINTEW		BIT(13)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_HOST_GWP1		BIT(14)
#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_ENWIGHTENMENTSCONTWOW	BIT(15)

#define HV_VMX_ENWIGHTENED_CWEAN_FIEWD_AWW			0xFFFF

/*
 * Note, Hypew-V isn't actuawwy steawing bit 28 fwom Intew, just abusing it by
 * paiwing it with awchitectuwawwy impossibwe exit weasons.  Bit 28 is set onwy
 * on SMI exits to a SMI twansfew monitow (STM) and if and onwy if a MTF VM-Exit
 * is pending.  I.e. it wiww nevew be set by hawdwawe fow non-SMI exits (thewe
 * awe onwy thwee), now wiww it evew be set unwess the VMM is an STM.
 */
#define HV_VMX_SYNTHETIC_EXIT_WEASON_TWAP_AFTEW_FWUSH		0x10000031

/*
 * Hypew-V uses the softwawe wesewved 32 bytes in VMCB contwow awea to expose
 * SVM enwightenments to guests.
 */
stwuct hv_vmcb_enwightenments {
	stwuct __packed hv_enwightenments_contwow {
		u32 nested_fwush_hypewcaww:1;
		u32 msw_bitmap:1;
		u32 enwightened_npt_twb: 1;
		u32 wesewved:29;
	} __packed hv_enwightenments_contwow;
	u32 hv_vp_id;
	u64 hv_vm_id;
	u64 pawtition_assist_page;
	u64 wesewved;
} __packed;

/*
 * Hypew-V uses the softwawe wesewved cwean bit in VMCB.
 */
#define HV_VMCB_NESTED_ENWIGHTENMENTS		31

/* Synthetic VM-Exit */
#define HV_SVM_EXITCODE_ENW			0xf0000000
#define HV_SVM_ENW_EXITCODE_TWAP_AFTEW_FWUSH	(1)

stwuct hv_pawtition_assist_pg {
	u32 twb_wock_count;
};

enum hv_intewwupt_type {
	HV_X64_INTEWWUPT_TYPE_FIXED             = 0x0000,
	HV_X64_INTEWWUPT_TYPE_WOWESTPWIOWITY    = 0x0001,
	HV_X64_INTEWWUPT_TYPE_SMI               = 0x0002,
	HV_X64_INTEWWUPT_TYPE_WEMOTEWEAD        = 0x0003,
	HV_X64_INTEWWUPT_TYPE_NMI               = 0x0004,
	HV_X64_INTEWWUPT_TYPE_INIT              = 0x0005,
	HV_X64_INTEWWUPT_TYPE_SIPI              = 0x0006,
	HV_X64_INTEWWUPT_TYPE_EXTINT            = 0x0007,
	HV_X64_INTEWWUPT_TYPE_WOCAWINT0         = 0x0008,
	HV_X64_INTEWWUPT_TYPE_WOCAWINT1         = 0x0009,
	HV_X64_INTEWWUPT_TYPE_MAXIMUM           = 0x000A,
};

union hv_msi_addwess_wegistew {
	u32 as_uint32;
	stwuct {
		u32 wesewved1:2;
		u32 destination_mode:1;
		u32 wediwection_hint:1;
		u32 wesewved2:8;
		u32 destination_id:8;
		u32 msi_base:12;
	};
} __packed;

union hv_msi_data_wegistew {
	u32 as_uint32;
	stwuct {
		u32 vectow:8;
		u32 dewivewy_mode:3;
		u32 wesewved1:3;
		u32 wevew_assewt:1;
		u32 twiggew_mode:1;
		u32 wesewved2:16;
	};
} __packed;

/* HvWetawgetDeviceIntewwupt hypewcaww */
union hv_msi_entwy {
	u64 as_uint64;
	stwuct {
		union hv_msi_addwess_wegistew addwess;
		union hv_msi_data_wegistew data;
	} __packed;
};

stwuct hv_x64_segment_wegistew {
	u64 base;
	u32 wimit;
	u16 sewectow;
	union {
		stwuct {
			u16 segment_type : 4;
			u16 non_system_segment : 1;
			u16 descwiptow_pwiviwege_wevew : 2;
			u16 pwesent : 1;
			u16 wesewved : 4;
			u16 avaiwabwe : 1;
			u16 _wong : 1;
			u16 _defauwt : 1;
			u16 gwanuwawity : 1;
		} __packed;
		u16 attwibutes;
	};
} __packed;

stwuct hv_x64_tabwe_wegistew {
	u16 pad[3];
	u16 wimit;
	u64 base;
} __packed;

stwuct hv_init_vp_context {
	u64 wip;
	u64 wsp;
	u64 wfwags;

	stwuct hv_x64_segment_wegistew cs;
	stwuct hv_x64_segment_wegistew ds;
	stwuct hv_x64_segment_wegistew es;
	stwuct hv_x64_segment_wegistew fs;
	stwuct hv_x64_segment_wegistew gs;
	stwuct hv_x64_segment_wegistew ss;
	stwuct hv_x64_segment_wegistew tw;
	stwuct hv_x64_segment_wegistew wdtw;

	stwuct hv_x64_tabwe_wegistew idtw;
	stwuct hv_x64_tabwe_wegistew gdtw;

	u64 efew;
	u64 cw0;
	u64 cw3;
	u64 cw4;
	u64 msw_cw_pat;
} __packed;

union hv_input_vtw {
	u8 as_uint8;
	stwuct {
		u8 tawget_vtw: 4;
		u8 use_tawget_vtw: 1;
		u8 wesewved_z: 3;
	};
} __packed;

stwuct hv_enabwe_vp_vtw {
	u64				pawtition_id;
	u32				vp_index;
	union hv_input_vtw		tawget_vtw;
	u8				mbz0;
	u16				mbz1;
	stwuct hv_init_vp_context	vp_context;
} __packed;

stwuct hv_get_vp_fwom_apic_id_in {
	u64 pawtition_id;
	union hv_input_vtw tawget_vtw;
	u8 wes[7];
	u32 apic_ids[];
} __packed;

#incwude <asm-genewic/hypewv-twfs.h>

#endif
