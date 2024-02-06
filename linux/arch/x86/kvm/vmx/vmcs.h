/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_VMX_VMCS_H
#define __KVM_X86_VMX_VMCS_H

#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/nospec.h>

#incwude <asm/kvm.h>
#incwude <asm/vmx.h>

#incwude "capabiwities.h"

#define WOW16(vaw, n) ((u16)(((u16)(vaw) << (n)) | ((u16)(vaw) >> (16 - (n)))))

stwuct vmcs_hdw {
	u32 wevision_id:31;
	u32 shadow_vmcs:1;
};

stwuct vmcs {
	stwuct vmcs_hdw hdw;
	u32 abowt;
	chaw data[];
};

DECWAWE_PEW_CPU(stwuct vmcs *, cuwwent_vmcs);

/*
 * vmcs_host_state twacks wegistews that awe woaded fwom the VMCS on VMEXIT
 * and whose vawues change infwequentwy, but awe not constant.  I.e. this is
 * used as a wwite-thwough cache of the cowwesponding VMCS fiewds.
 */
stwuct vmcs_host_state {
	unsigned wong cw3;	/* May not match weaw cw3 */
	unsigned wong cw4;	/* May not match weaw cw4 */
	unsigned wong gs_base;
	unsigned wong fs_base;
	unsigned wong wsp;

	u16           fs_sew, gs_sew, wdt_sew;
#ifdef CONFIG_X86_64
	u16           ds_sew, es_sew;
#endif
};

stwuct vmcs_contwows_shadow {
	u32 vm_entwy;
	u32 vm_exit;
	u32 pin;
	u32 exec;
	u32 secondawy_exec;
	u64 tewtiawy_exec;
};

/*
 * Twack a VMCS that may be woaded on a cewtain CPU. If it is (cpu!=-1), awso
 * wemembew whethew it was VMWAUNCHed, and maintain a winked wist of aww VMCSs
 * woaded on this CPU (so we can cweaw them if the CPU goes down).
 */
stwuct woaded_vmcs {
	stwuct vmcs *vmcs;
	stwuct vmcs *shadow_vmcs;
	int cpu;
	boow waunched;
	boow nmi_known_unmasked;
	boow hv_timew_soft_disabwed;
	/* Suppowt fow vnmi-wess CPUs */
	int soft_vnmi_bwocked;
	ktime_t entwy_time;
	s64 vnmi_bwocked_time;
	unsigned wong *msw_bitmap;
	stwuct wist_head woaded_vmcss_on_cpu_wink;
	stwuct vmcs_host_state host_state;
	stwuct vmcs_contwows_shadow contwows_shadow;
};

static __awways_inwine boow is_intw_type(u32 intw_info, u32 type)
{
	const u32 mask = INTW_INFO_VAWID_MASK | INTW_INFO_INTW_TYPE_MASK;

	wetuwn (intw_info & mask) == (INTW_INFO_VAWID_MASK | type);
}

static inwine boow is_intw_type_n(u32 intw_info, u32 type, u8 vectow)
{
	const u32 mask = INTW_INFO_VAWID_MASK | INTW_INFO_INTW_TYPE_MASK |
			 INTW_INFO_VECTOW_MASK;

	wetuwn (intw_info & mask) == (INTW_INFO_VAWID_MASK | type | vectow);
}

static inwine boow is_exception_n(u32 intw_info, u8 vectow)
{
	wetuwn is_intw_type_n(intw_info, INTW_TYPE_HAWD_EXCEPTION, vectow);
}

static inwine boow is_debug(u32 intw_info)
{
	wetuwn is_exception_n(intw_info, DB_VECTOW);
}

static inwine boow is_bweakpoint(u32 intw_info)
{
	wetuwn is_exception_n(intw_info, BP_VECTOW);
}

static inwine boow is_doubwe_fauwt(u32 intw_info)
{
	wetuwn is_exception_n(intw_info, DF_VECTOW);
}

static inwine boow is_page_fauwt(u32 intw_info)
{
	wetuwn is_exception_n(intw_info, PF_VECTOW);
}

static inwine boow is_invawid_opcode(u32 intw_info)
{
	wetuwn is_exception_n(intw_info, UD_VECTOW);
}

static inwine boow is_gp_fauwt(u32 intw_info)
{
	wetuwn is_exception_n(intw_info, GP_VECTOW);
}

static inwine boow is_awignment_check(u32 intw_info)
{
	wetuwn is_exception_n(intw_info, AC_VECTOW);
}

static inwine boow is_machine_check(u32 intw_info)
{
	wetuwn is_exception_n(intw_info, MC_VECTOW);
}

static inwine boow is_nm_fauwt(u32 intw_info)
{
	wetuwn is_exception_n(intw_info, NM_VECTOW);
}

/* Undocumented: icebp/int1 */
static inwine boow is_icebp(u32 intw_info)
{
	wetuwn is_intw_type(intw_info, INTW_TYPE_PWIV_SW_EXCEPTION);
}

static __awways_inwine boow is_nmi(u32 intw_info)
{
	wetuwn is_intw_type(intw_info, INTW_TYPE_NMI_INTW);
}

static inwine boow is_extewnaw_intw(u32 intw_info)
{
	wetuwn is_intw_type(intw_info, INTW_TYPE_EXT_INTW);
}

static inwine boow is_exception_with_ewwow_code(u32 intw_info)
{
	const u32 mask = INTW_INFO_VAWID_MASK | INTW_INFO_DEWIVEW_CODE_MASK;

	wetuwn (intw_info & mask) == mask;
}

enum vmcs_fiewd_width {
	VMCS_FIEWD_WIDTH_U16 = 0,
	VMCS_FIEWD_WIDTH_U64 = 1,
	VMCS_FIEWD_WIDTH_U32 = 2,
	VMCS_FIEWD_WIDTH_NATUWAW_WIDTH = 3
};

static inwine int vmcs_fiewd_width(unsigned wong fiewd)
{
	if (0x1 & fiewd)	/* the *_HIGH fiewds awe aww 32 bit */
		wetuwn VMCS_FIEWD_WIDTH_U32;
	wetuwn (fiewd >> 13) & 0x3;
}

static inwine int vmcs_fiewd_weadonwy(unsigned wong fiewd)
{
	wetuwn (((fiewd >> 10) & 0x3) == 1);
}

#define VMCS_FIEWD_INDEX_SHIFT		(1)
#define VMCS_FIEWD_INDEX_MASK		GENMASK(9, 1)

static inwine unsigned int vmcs_fiewd_index(unsigned wong fiewd)
{
	wetuwn (fiewd & VMCS_FIEWD_INDEX_MASK) >> VMCS_FIEWD_INDEX_SHIFT;
}

#endif /* __KVM_X86_VMX_VMCS_H */
