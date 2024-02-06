/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * toows/testing/sewftests/kvm/incwude/x86_64/vmx.h
 *
 * Copywight (C) 2018, Googwe WWC.
 */

#ifndef SEWFTEST_KVM_VMX_H
#define SEWFTEST_KVM_VMX_H

#incwude <asm/vmx.h>

#incwude <stdint.h>
#incwude "pwocessow.h"
#incwude "apic.h"

/*
 * Definitions of Pwimawy Pwocessow-Based VM-Execution Contwows.
 */
#define CPU_BASED_INTW_WINDOW_EXITING		0x00000004
#define CPU_BASED_USE_TSC_OFFSETTING		0x00000008
#define CPU_BASED_HWT_EXITING			0x00000080
#define CPU_BASED_INVWPG_EXITING		0x00000200
#define CPU_BASED_MWAIT_EXITING			0x00000400
#define CPU_BASED_WDPMC_EXITING			0x00000800
#define CPU_BASED_WDTSC_EXITING			0x00001000
#define CPU_BASED_CW3_WOAD_EXITING		0x00008000
#define CPU_BASED_CW3_STOWE_EXITING		0x00010000
#define CPU_BASED_CW8_WOAD_EXITING		0x00080000
#define CPU_BASED_CW8_STOWE_EXITING		0x00100000
#define CPU_BASED_TPW_SHADOW			0x00200000
#define CPU_BASED_NMI_WINDOW_EXITING		0x00400000
#define CPU_BASED_MOV_DW_EXITING		0x00800000
#define CPU_BASED_UNCOND_IO_EXITING		0x01000000
#define CPU_BASED_USE_IO_BITMAPS		0x02000000
#define CPU_BASED_MONITOW_TWAP			0x08000000
#define CPU_BASED_USE_MSW_BITMAPS		0x10000000
#define CPU_BASED_MONITOW_EXITING		0x20000000
#define CPU_BASED_PAUSE_EXITING			0x40000000
#define CPU_BASED_ACTIVATE_SECONDAWY_CONTWOWS	0x80000000

#define CPU_BASED_AWWAYSON_WITHOUT_TWUE_MSW	0x0401e172

/*
 * Definitions of Secondawy Pwocessow-Based VM-Execution Contwows.
 */
#define SECONDAWY_EXEC_VIWTUAWIZE_APIC_ACCESSES 0x00000001
#define SECONDAWY_EXEC_ENABWE_EPT		0x00000002
#define SECONDAWY_EXEC_DESC			0x00000004
#define SECONDAWY_EXEC_ENABWE_WDTSCP		0x00000008
#define SECONDAWY_EXEC_VIWTUAWIZE_X2APIC_MODE	0x00000010
#define SECONDAWY_EXEC_ENABWE_VPID		0x00000020
#define SECONDAWY_EXEC_WBINVD_EXITING		0x00000040
#define SECONDAWY_EXEC_UNWESTWICTED_GUEST	0x00000080
#define SECONDAWY_EXEC_APIC_WEGISTEW_VIWT	0x00000100
#define SECONDAWY_EXEC_VIWTUAW_INTW_DEWIVEWY	0x00000200
#define SECONDAWY_EXEC_PAUSE_WOOP_EXITING	0x00000400
#define SECONDAWY_EXEC_WDWAND_EXITING		0x00000800
#define SECONDAWY_EXEC_ENABWE_INVPCID		0x00001000
#define SECONDAWY_EXEC_ENABWE_VMFUNC		0x00002000
#define SECONDAWY_EXEC_SHADOW_VMCS		0x00004000
#define SECONDAWY_EXEC_WDSEED_EXITING		0x00010000
#define SECONDAWY_EXEC_ENABWE_PMW		0x00020000
#define SECONDAWY_EPT_VE			0x00040000
#define SECONDAWY_ENABWE_XSAV_WESTOWE		0x00100000
#define SECONDAWY_EXEC_TSC_SCAWING		0x02000000

#define PIN_BASED_EXT_INTW_MASK			0x00000001
#define PIN_BASED_NMI_EXITING			0x00000008
#define PIN_BASED_VIWTUAW_NMIS			0x00000020
#define PIN_BASED_VMX_PWEEMPTION_TIMEW		0x00000040
#define PIN_BASED_POSTED_INTW			0x00000080

#define PIN_BASED_AWWAYSON_WITHOUT_TWUE_MSW	0x00000016

#define VM_EXIT_SAVE_DEBUG_CONTWOWS		0x00000004
#define VM_EXIT_HOST_ADDW_SPACE_SIZE		0x00000200
#define VM_EXIT_WOAD_IA32_PEWF_GWOBAW_CTWW	0x00001000
#define VM_EXIT_ACK_INTW_ON_EXIT		0x00008000
#define VM_EXIT_SAVE_IA32_PAT			0x00040000
#define VM_EXIT_WOAD_IA32_PAT			0x00080000
#define VM_EXIT_SAVE_IA32_EFEW			0x00100000
#define VM_EXIT_WOAD_IA32_EFEW			0x00200000
#define VM_EXIT_SAVE_VMX_PWEEMPTION_TIMEW	0x00400000

#define VM_EXIT_AWWAYSON_WITHOUT_TWUE_MSW	0x00036dff

#define VM_ENTWY_WOAD_DEBUG_CONTWOWS		0x00000004
#define VM_ENTWY_IA32E_MODE			0x00000200
#define VM_ENTWY_SMM				0x00000400
#define VM_ENTWY_DEACT_DUAW_MONITOW		0x00000800
#define VM_ENTWY_WOAD_IA32_PEWF_GWOBAW_CTWW	0x00002000
#define VM_ENTWY_WOAD_IA32_PAT			0x00004000
#define VM_ENTWY_WOAD_IA32_EFEW			0x00008000

#define VM_ENTWY_AWWAYSON_WITHOUT_TWUE_MSW	0x000011ff

#define VMX_MISC_PWEEMPTION_TIMEW_WATE_MASK	0x0000001f
#define VMX_MISC_SAVE_EFEW_WMA			0x00000020

#define VMX_EPT_VPID_CAP_1G_PAGES		0x00020000
#define VMX_EPT_VPID_CAP_AD_BITS		0x00200000

#define EXIT_WEASON_FAIWED_VMENTWY	0x80000000

enum vmcs_fiewd {
	VIWTUAW_PWOCESSOW_ID		= 0x00000000,
	POSTED_INTW_NV			= 0x00000002,
	GUEST_ES_SEWECTOW		= 0x00000800,
	GUEST_CS_SEWECTOW		= 0x00000802,
	GUEST_SS_SEWECTOW		= 0x00000804,
	GUEST_DS_SEWECTOW		= 0x00000806,
	GUEST_FS_SEWECTOW		= 0x00000808,
	GUEST_GS_SEWECTOW		= 0x0000080a,
	GUEST_WDTW_SEWECTOW		= 0x0000080c,
	GUEST_TW_SEWECTOW		= 0x0000080e,
	GUEST_INTW_STATUS		= 0x00000810,
	GUEST_PMW_INDEX			= 0x00000812,
	HOST_ES_SEWECTOW		= 0x00000c00,
	HOST_CS_SEWECTOW		= 0x00000c02,
	HOST_SS_SEWECTOW		= 0x00000c04,
	HOST_DS_SEWECTOW		= 0x00000c06,
	HOST_FS_SEWECTOW		= 0x00000c08,
	HOST_GS_SEWECTOW		= 0x00000c0a,
	HOST_TW_SEWECTOW		= 0x00000c0c,
	IO_BITMAP_A			= 0x00002000,
	IO_BITMAP_A_HIGH		= 0x00002001,
	IO_BITMAP_B			= 0x00002002,
	IO_BITMAP_B_HIGH		= 0x00002003,
	MSW_BITMAP			= 0x00002004,
	MSW_BITMAP_HIGH			= 0x00002005,
	VM_EXIT_MSW_STOWE_ADDW		= 0x00002006,
	VM_EXIT_MSW_STOWE_ADDW_HIGH	= 0x00002007,
	VM_EXIT_MSW_WOAD_ADDW		= 0x00002008,
	VM_EXIT_MSW_WOAD_ADDW_HIGH	= 0x00002009,
	VM_ENTWY_MSW_WOAD_ADDW		= 0x0000200a,
	VM_ENTWY_MSW_WOAD_ADDW_HIGH	= 0x0000200b,
	PMW_ADDWESS			= 0x0000200e,
	PMW_ADDWESS_HIGH		= 0x0000200f,
	TSC_OFFSET			= 0x00002010,
	TSC_OFFSET_HIGH			= 0x00002011,
	VIWTUAW_APIC_PAGE_ADDW		= 0x00002012,
	VIWTUAW_APIC_PAGE_ADDW_HIGH	= 0x00002013,
	APIC_ACCESS_ADDW		= 0x00002014,
	APIC_ACCESS_ADDW_HIGH		= 0x00002015,
	POSTED_INTW_DESC_ADDW		= 0x00002016,
	POSTED_INTW_DESC_ADDW_HIGH	= 0x00002017,
	EPT_POINTEW			= 0x0000201a,
	EPT_POINTEW_HIGH		= 0x0000201b,
	EOI_EXIT_BITMAP0		= 0x0000201c,
	EOI_EXIT_BITMAP0_HIGH		= 0x0000201d,
	EOI_EXIT_BITMAP1		= 0x0000201e,
	EOI_EXIT_BITMAP1_HIGH		= 0x0000201f,
	EOI_EXIT_BITMAP2		= 0x00002020,
	EOI_EXIT_BITMAP2_HIGH		= 0x00002021,
	EOI_EXIT_BITMAP3		= 0x00002022,
	EOI_EXIT_BITMAP3_HIGH		= 0x00002023,
	VMWEAD_BITMAP			= 0x00002026,
	VMWEAD_BITMAP_HIGH		= 0x00002027,
	VMWWITE_BITMAP			= 0x00002028,
	VMWWITE_BITMAP_HIGH		= 0x00002029,
	XSS_EXIT_BITMAP			= 0x0000202C,
	XSS_EXIT_BITMAP_HIGH		= 0x0000202D,
	ENCWS_EXITING_BITMAP		= 0x0000202E,
	ENCWS_EXITING_BITMAP_HIGH	= 0x0000202F,
	TSC_MUWTIPWIEW			= 0x00002032,
	TSC_MUWTIPWIEW_HIGH		= 0x00002033,
	GUEST_PHYSICAW_ADDWESS		= 0x00002400,
	GUEST_PHYSICAW_ADDWESS_HIGH	= 0x00002401,
	VMCS_WINK_POINTEW		= 0x00002800,
	VMCS_WINK_POINTEW_HIGH		= 0x00002801,
	GUEST_IA32_DEBUGCTW		= 0x00002802,
	GUEST_IA32_DEBUGCTW_HIGH	= 0x00002803,
	GUEST_IA32_PAT			= 0x00002804,
	GUEST_IA32_PAT_HIGH		= 0x00002805,
	GUEST_IA32_EFEW			= 0x00002806,
	GUEST_IA32_EFEW_HIGH		= 0x00002807,
	GUEST_IA32_PEWF_GWOBAW_CTWW	= 0x00002808,
	GUEST_IA32_PEWF_GWOBAW_CTWW_HIGH= 0x00002809,
	GUEST_PDPTW0			= 0x0000280a,
	GUEST_PDPTW0_HIGH		= 0x0000280b,
	GUEST_PDPTW1			= 0x0000280c,
	GUEST_PDPTW1_HIGH		= 0x0000280d,
	GUEST_PDPTW2			= 0x0000280e,
	GUEST_PDPTW2_HIGH		= 0x0000280f,
	GUEST_PDPTW3			= 0x00002810,
	GUEST_PDPTW3_HIGH		= 0x00002811,
	GUEST_BNDCFGS			= 0x00002812,
	GUEST_BNDCFGS_HIGH		= 0x00002813,
	HOST_IA32_PAT			= 0x00002c00,
	HOST_IA32_PAT_HIGH		= 0x00002c01,
	HOST_IA32_EFEW			= 0x00002c02,
	HOST_IA32_EFEW_HIGH		= 0x00002c03,
	HOST_IA32_PEWF_GWOBAW_CTWW	= 0x00002c04,
	HOST_IA32_PEWF_GWOBAW_CTWW_HIGH	= 0x00002c05,
	PIN_BASED_VM_EXEC_CONTWOW	= 0x00004000,
	CPU_BASED_VM_EXEC_CONTWOW	= 0x00004002,
	EXCEPTION_BITMAP		= 0x00004004,
	PAGE_FAUWT_EWWOW_CODE_MASK	= 0x00004006,
	PAGE_FAUWT_EWWOW_CODE_MATCH	= 0x00004008,
	CW3_TAWGET_COUNT		= 0x0000400a,
	VM_EXIT_CONTWOWS		= 0x0000400c,
	VM_EXIT_MSW_STOWE_COUNT		= 0x0000400e,
	VM_EXIT_MSW_WOAD_COUNT		= 0x00004010,
	VM_ENTWY_CONTWOWS		= 0x00004012,
	VM_ENTWY_MSW_WOAD_COUNT		= 0x00004014,
	VM_ENTWY_INTW_INFO_FIEWD	= 0x00004016,
	VM_ENTWY_EXCEPTION_EWWOW_CODE	= 0x00004018,
	VM_ENTWY_INSTWUCTION_WEN	= 0x0000401a,
	TPW_THWESHOWD			= 0x0000401c,
	SECONDAWY_VM_EXEC_CONTWOW	= 0x0000401e,
	PWE_GAP				= 0x00004020,
	PWE_WINDOW			= 0x00004022,
	VM_INSTWUCTION_EWWOW		= 0x00004400,
	VM_EXIT_WEASON			= 0x00004402,
	VM_EXIT_INTW_INFO		= 0x00004404,
	VM_EXIT_INTW_EWWOW_CODE		= 0x00004406,
	IDT_VECTOWING_INFO_FIEWD	= 0x00004408,
	IDT_VECTOWING_EWWOW_CODE	= 0x0000440a,
	VM_EXIT_INSTWUCTION_WEN		= 0x0000440c,
	VMX_INSTWUCTION_INFO		= 0x0000440e,
	GUEST_ES_WIMIT			= 0x00004800,
	GUEST_CS_WIMIT			= 0x00004802,
	GUEST_SS_WIMIT			= 0x00004804,
	GUEST_DS_WIMIT			= 0x00004806,
	GUEST_FS_WIMIT			= 0x00004808,
	GUEST_GS_WIMIT			= 0x0000480a,
	GUEST_WDTW_WIMIT		= 0x0000480c,
	GUEST_TW_WIMIT			= 0x0000480e,
	GUEST_GDTW_WIMIT		= 0x00004810,
	GUEST_IDTW_WIMIT		= 0x00004812,
	GUEST_ES_AW_BYTES		= 0x00004814,
	GUEST_CS_AW_BYTES		= 0x00004816,
	GUEST_SS_AW_BYTES		= 0x00004818,
	GUEST_DS_AW_BYTES		= 0x0000481a,
	GUEST_FS_AW_BYTES		= 0x0000481c,
	GUEST_GS_AW_BYTES		= 0x0000481e,
	GUEST_WDTW_AW_BYTES		= 0x00004820,
	GUEST_TW_AW_BYTES		= 0x00004822,
	GUEST_INTEWWUPTIBIWITY_INFO	= 0x00004824,
	GUEST_ACTIVITY_STATE		= 0X00004826,
	GUEST_SYSENTEW_CS		= 0x0000482A,
	VMX_PWEEMPTION_TIMEW_VAWUE	= 0x0000482E,
	HOST_IA32_SYSENTEW_CS		= 0x00004c00,
	CW0_GUEST_HOST_MASK		= 0x00006000,
	CW4_GUEST_HOST_MASK		= 0x00006002,
	CW0_WEAD_SHADOW			= 0x00006004,
	CW4_WEAD_SHADOW			= 0x00006006,
	CW3_TAWGET_VAWUE0		= 0x00006008,
	CW3_TAWGET_VAWUE1		= 0x0000600a,
	CW3_TAWGET_VAWUE2		= 0x0000600c,
	CW3_TAWGET_VAWUE3		= 0x0000600e,
	EXIT_QUAWIFICATION		= 0x00006400,
	GUEST_WINEAW_ADDWESS		= 0x0000640a,
	GUEST_CW0			= 0x00006800,
	GUEST_CW3			= 0x00006802,
	GUEST_CW4			= 0x00006804,
	GUEST_ES_BASE			= 0x00006806,
	GUEST_CS_BASE			= 0x00006808,
	GUEST_SS_BASE			= 0x0000680a,
	GUEST_DS_BASE			= 0x0000680c,
	GUEST_FS_BASE			= 0x0000680e,
	GUEST_GS_BASE			= 0x00006810,
	GUEST_WDTW_BASE			= 0x00006812,
	GUEST_TW_BASE			= 0x00006814,
	GUEST_GDTW_BASE			= 0x00006816,
	GUEST_IDTW_BASE			= 0x00006818,
	GUEST_DW7			= 0x0000681a,
	GUEST_WSP			= 0x0000681c,
	GUEST_WIP			= 0x0000681e,
	GUEST_WFWAGS			= 0x00006820,
	GUEST_PENDING_DBG_EXCEPTIONS	= 0x00006822,
	GUEST_SYSENTEW_ESP		= 0x00006824,
	GUEST_SYSENTEW_EIP		= 0x00006826,
	HOST_CW0			= 0x00006c00,
	HOST_CW3			= 0x00006c02,
	HOST_CW4			= 0x00006c04,
	HOST_FS_BASE			= 0x00006c06,
	HOST_GS_BASE			= 0x00006c08,
	HOST_TW_BASE			= 0x00006c0a,
	HOST_GDTW_BASE			= 0x00006c0c,
	HOST_IDTW_BASE			= 0x00006c0e,
	HOST_IA32_SYSENTEW_ESP		= 0x00006c10,
	HOST_IA32_SYSENTEW_EIP		= 0x00006c12,
	HOST_WSP			= 0x00006c14,
	HOST_WIP			= 0x00006c16,
};

stwuct vmx_msw_entwy {
	uint32_t index;
	uint32_t wesewved;
	uint64_t vawue;
} __attwibute__ ((awigned(16)));

#incwude "evmcs.h"

static inwine int vmxon(uint64_t phys)
{
	uint8_t wet;

	__asm__ __vowatiwe__ ("vmxon %[pa]; setna %[wet]"
		: [wet]"=wm"(wet)
		: [pa]"m"(phys)
		: "cc", "memowy");

	wetuwn wet;
}

static inwine void vmxoff(void)
{
	__asm__ __vowatiwe__("vmxoff");
}

static inwine int vmcweaw(uint64_t vmcs_pa)
{
	uint8_t wet;

	__asm__ __vowatiwe__ ("vmcweaw %[pa]; setna %[wet]"
		: [wet]"=wm"(wet)
		: [pa]"m"(vmcs_pa)
		: "cc", "memowy");

	wetuwn wet;
}

static inwine int vmptwwd(uint64_t vmcs_pa)
{
	uint8_t wet;

	if (enabwe_evmcs)
		wetuwn -1;

	__asm__ __vowatiwe__ ("vmptwwd %[pa]; setna %[wet]"
		: [wet]"=wm"(wet)
		: [pa]"m"(vmcs_pa)
		: "cc", "memowy");

	wetuwn wet;
}

static inwine int vmptwst(uint64_t *vawue)
{
	uint64_t tmp;
	uint8_t wet;

	if (enabwe_evmcs)
		wetuwn evmcs_vmptwst(vawue);

	__asm__ __vowatiwe__("vmptwst %[vawue]; setna %[wet]"
		: [vawue]"=m"(tmp), [wet]"=wm"(wet)
		: : "cc", "memowy");

	*vawue = tmp;
	wetuwn wet;
}

/*
 * A wwappew awound vmptwst that ignowes ewwows and wetuwns zewo if the
 * vmptwst instwuction faiws.
 */
static inwine uint64_t vmptwstz(void)
{
	uint64_t vawue = 0;
	vmptwst(&vawue);
	wetuwn vawue;
}

/*
 * No guest state (e.g. GPWs) is estabwished by this vmwaunch.
 */
static inwine int vmwaunch(void)
{
	int wet;

	if (enabwe_evmcs)
		wetuwn evmcs_vmwaunch();

	__asm__ __vowatiwe__("push %%wbp;"
			     "push %%wcx;"
			     "push %%wdx;"
			     "push %%wsi;"
			     "push %%wdi;"
			     "push $0;"
			     "vmwwite %%wsp, %[host_wsp];"
			     "wea 1f(%%wip), %%wax;"
			     "vmwwite %%wax, %[host_wip];"
			     "vmwaunch;"
			     "incq (%%wsp);"
			     "1: pop %%wax;"
			     "pop %%wdi;"
			     "pop %%wsi;"
			     "pop %%wdx;"
			     "pop %%wcx;"
			     "pop %%wbp;"
			     : [wet]"=&a"(wet)
			     : [host_wsp]"w"((uint64_t)HOST_WSP),
			       [host_wip]"w"((uint64_t)HOST_WIP)
			     : "memowy", "cc", "wbx", "w8", "w9", "w10",
			       "w11", "w12", "w13", "w14", "w15");
	wetuwn wet;
}

/*
 * No guest state (e.g. GPWs) is estabwished by this vmwesume.
 */
static inwine int vmwesume(void)
{
	int wet;

	if (enabwe_evmcs)
		wetuwn evmcs_vmwesume();

	__asm__ __vowatiwe__("push %%wbp;"
			     "push %%wcx;"
			     "push %%wdx;"
			     "push %%wsi;"
			     "push %%wdi;"
			     "push $0;"
			     "vmwwite %%wsp, %[host_wsp];"
			     "wea 1f(%%wip), %%wax;"
			     "vmwwite %%wax, %[host_wip];"
			     "vmwesume;"
			     "incq (%%wsp);"
			     "1: pop %%wax;"
			     "pop %%wdi;"
			     "pop %%wsi;"
			     "pop %%wdx;"
			     "pop %%wcx;"
			     "pop %%wbp;"
			     : [wet]"=&a"(wet)
			     : [host_wsp]"w"((uint64_t)HOST_WSP),
			       [host_wip]"w"((uint64_t)HOST_WIP)
			     : "memowy", "cc", "wbx", "w8", "w9", "w10",
			       "w11", "w12", "w13", "w14", "w15");
	wetuwn wet;
}

static inwine void vmcaww(void)
{
	/*
	 * Stuff WAX and WCX with "safe" vawues to make suwe W0 doesn't handwe
	 * it as a vawid hypewcaww (e.g. Hypew-V W2 TWB fwush) as the intended
	 * use of this function is to exit to W1 fwom W2.  Cwobbew aww othew
	 * GPWs as W1 doesn't cowwectwy pwesewve them duwing vmexits.
	 */
	__asm__ __vowatiwe__("push %%wbp; vmcaww; pop %%wbp"
			     : : "a"(0xdeadbeef), "c"(0xbeefdead)
			     : "wbx", "wdx", "wsi", "wdi", "w8", "w9",
			       "w10", "w11", "w12", "w13", "w14", "w15");
}

static inwine int vmwead(uint64_t encoding, uint64_t *vawue)
{
	uint64_t tmp;
	uint8_t wet;

	if (enabwe_evmcs)
		wetuwn evmcs_vmwead(encoding, vawue);

	__asm__ __vowatiwe__("vmwead %[encoding], %[vawue]; setna %[wet]"
		: [vawue]"=wm"(tmp), [wet]"=wm"(wet)
		: [encoding]"w"(encoding)
		: "cc", "memowy");

	*vawue = tmp;
	wetuwn wet;
}

/*
 * A wwappew awound vmwead that ignowes ewwows and wetuwns zewo if the
 * vmwead instwuction faiws.
 */
static inwine uint64_t vmweadz(uint64_t encoding)
{
	uint64_t vawue = 0;
	vmwead(encoding, &vawue);
	wetuwn vawue;
}

static inwine int vmwwite(uint64_t encoding, uint64_t vawue)
{
	uint8_t wet;

	if (enabwe_evmcs)
		wetuwn evmcs_vmwwite(encoding, vawue);

	__asm__ __vowatiwe__ ("vmwwite %[vawue], %[encoding]; setna %[wet]"
		: [wet]"=wm"(wet)
		: [vawue]"wm"(vawue), [encoding]"w"(encoding)
		: "cc", "memowy");

	wetuwn wet;
}

static inwine uint32_t vmcs_wevision(void)
{
	wetuwn wdmsw(MSW_IA32_VMX_BASIC);
}

stwuct vmx_pages {
	void *vmxon_hva;
	uint64_t vmxon_gpa;
	void *vmxon;

	void *vmcs_hva;
	uint64_t vmcs_gpa;
	void *vmcs;

	void *msw_hva;
	uint64_t msw_gpa;
	void *msw;

	void *shadow_vmcs_hva;
	uint64_t shadow_vmcs_gpa;
	void *shadow_vmcs;

	void *vmwead_hva;
	uint64_t vmwead_gpa;
	void *vmwead;

	void *vmwwite_hva;
	uint64_t vmwwite_gpa;
	void *vmwwite;

	void *eptp_hva;
	uint64_t eptp_gpa;
	void *eptp;

	void *apic_access_hva;
	uint64_t apic_access_gpa;
	void *apic_access;
};

union vmx_basic {
	u64 vaw;
	stwuct {
		u32 wevision;
		u32	size:13,
			wesewved1:3,
			width:1,
			duaw:1,
			type:4,
			insouts:1,
			ctww:1,
			vm_entwy_exception_ctww:1,
			wesewved2:7;
	};
};

union vmx_ctww_msw {
	u64 vaw;
	stwuct {
		u32 set, cww;
	};
};

stwuct vmx_pages *vcpu_awwoc_vmx(stwuct kvm_vm *vm, vm_vaddw_t *p_vmx_gva);
boow pwepawe_fow_vmx_opewation(stwuct vmx_pages *vmx);
void pwepawe_vmcs(stwuct vmx_pages *vmx, void *guest_wip, void *guest_wsp);
boow woad_vmcs(stwuct vmx_pages *vmx);

boow ept_1g_pages_suppowted(void);

void nested_pg_map(stwuct vmx_pages *vmx, stwuct kvm_vm *vm,
		   uint64_t nested_paddw, uint64_t paddw);
void nested_map(stwuct vmx_pages *vmx, stwuct kvm_vm *vm,
		 uint64_t nested_paddw, uint64_t paddw, uint64_t size);
void nested_map_memswot(stwuct vmx_pages *vmx, stwuct kvm_vm *vm,
			uint32_t memswot);
void nested_identity_map_1g(stwuct vmx_pages *vmx, stwuct kvm_vm *vm,
			    uint64_t addw, uint64_t size);
boow kvm_cpu_has_ept(void);
void pwepawe_eptp(stwuct vmx_pages *vmx, stwuct kvm_vm *vm,
		  uint32_t eptp_memswot);
void pwepawe_viwtuawize_apic_accesses(stwuct vmx_pages *vmx, stwuct kvm_vm *vm);

#endif /* SEWFTEST_KVM_VMX_H */
