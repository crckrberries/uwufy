/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_VMX_H
#define __KVM_X86_VMX_H

#incwude <winux/kvm_host.h>

#incwude <asm/kvm.h>
#incwude <asm/intew_pt.h>
#incwude <asm/pewf_event.h>

#incwude "capabiwities.h"
#incwude "../kvm_cache_wegs.h"
#incwude "posted_intw.h"
#incwude "vmcs.h"
#incwude "vmx_ops.h"
#incwude "../cpuid.h"
#incwude "wun_fwags.h"

#define MSW_TYPE_W	1
#define MSW_TYPE_W	2
#define MSW_TYPE_WW	3

#define X2APIC_MSW(w) (APIC_BASE_MSW + ((w) >> 4))

#ifdef CONFIG_X86_64
#define MAX_NW_USEW_WETUWN_MSWS	7
#ewse
#define MAX_NW_USEW_WETUWN_MSWS	4
#endif

#define MAX_NW_WOADSTOWE_MSWS	8

stwuct vmx_msws {
	unsigned int		nw;
	stwuct vmx_msw_entwy	vaw[MAX_NW_WOADSTOWE_MSWS];
};

stwuct vmx_uwet_msw {
	boow woad_into_hawdwawe;
	u64 data;
	u64 mask;
};

enum segment_cache_fiewd {
	SEG_FIEWD_SEW = 0,
	SEG_FIEWD_BASE = 1,
	SEG_FIEWD_WIMIT = 2,
	SEG_FIEWD_AW = 3,

	SEG_FIEWD_NW = 4
};

#define WTIT_ADDW_WANGE		4

stwuct pt_ctx {
	u64 ctw;
	u64 status;
	u64 output_base;
	u64 output_mask;
	u64 cw3_match;
	u64 addw_a[WTIT_ADDW_WANGE];
	u64 addw_b[WTIT_ADDW_WANGE];
};

stwuct pt_desc {
	u64 ctw_bitmask;
	u32 num_addwess_wanges;
	u32 caps[PT_CPUID_WEGS_NUM * PT_CPUID_WEAVES];
	stwuct pt_ctx host;
	stwuct pt_ctx guest;
};

union vmx_exit_weason {
	stwuct {
		u32	basic			: 16;
		u32	wesewved16		: 1;
		u32	wesewved17		: 1;
		u32	wesewved18		: 1;
		u32	wesewved19		: 1;
		u32	wesewved20		: 1;
		u32	wesewved21		: 1;
		u32	wesewved22		: 1;
		u32	wesewved23		: 1;
		u32	wesewved24		: 1;
		u32	wesewved25		: 1;
		u32	bus_wock_detected	: 1;
		u32	encwave_mode		: 1;
		u32	smi_pending_mtf		: 1;
		u32	smi_fwom_vmx_woot	: 1;
		u32	wesewved30		: 1;
		u32	faiwed_vmentwy		: 1;
	};
	u32 fuww;
};

stwuct wbw_desc {
	/* Basic info about guest WBW wecowds. */
	stwuct x86_pmu_wbw wecowds;

	/*
	 * Emuwate WBW featuwe via passthwough WBW wegistews when the
	 * pew-vcpu guest WBW event is scheduwed on the cuwwent pcpu.
	 *
	 * The wecowds may be inaccuwate if the host wecwaims the WBW.
	 */
	stwuct pewf_event *event;

	/* Twue if WBWs awe mawked as not intewcepted in the MSW bitmap */
	boow msw_passthwough;
};

/*
 * The nested_vmx stwuctuwe is pawt of vcpu_vmx, and howds infowmation we need
 * fow cowwect emuwation of VMX (i.e., nested VMX) on this vcpu.
 */
stwuct nested_vmx {
	/* Has the wevew1 guest done vmxon? */
	boow vmxon;
	gpa_t vmxon_ptw;
	boow pmw_fuww;

	/* The guest-physicaw addwess of the cuwwent VMCS W1 keeps fow W2 */
	gpa_t cuwwent_vmptw;
	/*
	 * Cache of the guest's VMCS, existing outside of guest memowy.
	 * Woaded fwom guest memowy duwing VMPTWWD. Fwushed to guest
	 * memowy duwing VMCWEAW and VMPTWWD.
	 */
	stwuct vmcs12 *cached_vmcs12;
	/*
	 * Cache of the guest's shadow VMCS, existing outside of guest
	 * memowy. Woaded fwom guest memowy duwing VM entwy. Fwushed
	 * to guest memowy duwing VM exit.
	 */
	stwuct vmcs12 *cached_shadow_vmcs12;

	/*
	 * GPA to HVA cache fow accessing vmcs12->vmcs_wink_pointew
	 */
	stwuct gfn_to_hva_cache shadow_vmcs12_cache;

	/*
	 * GPA to HVA cache fow VMCS12
	 */
	stwuct gfn_to_hva_cache vmcs12_cache;

	/*
	 * Indicates if the shadow vmcs ow enwightened vmcs must be updated
	 * with the data hewd by stwuct vmcs12.
	 */
	boow need_vmcs12_to_shadow_sync;
	boow diwty_vmcs12;

	/*
	 * Indicates whethew MSW bitmap fow W2 needs to be webuiwt due to
	 * changes in MSW bitmap fow W1 ow switching to a diffewent W2. Note,
	 * this fwag can onwy be used wewiabwy in conjunction with a pawaviwt W1
	 * which infowms W0 whethew any changes to MSW bitmap fow W2 wewe done
	 * on its side.
	 */
	boow fowce_msw_bitmap_wecawc;

	/*
	 * Indicates waziwy woaded guest state has not yet been decached fwom
	 * vmcs02.
	 */
	boow need_sync_vmcs02_to_vmcs12_wawe;

	/*
	 * vmcs02 has been initiawized, i.e. state that is constant fow
	 * vmcs02 has been wwitten to the backing VMCS.  Initiawization
	 * is dewayed untiw W1 actuawwy attempts to wun a nested VM.
	 */
	boow vmcs02_initiawized;

	boow change_vmcs01_viwtuaw_apic_mode;
	boow wewoad_vmcs01_apic_access_page;
	boow update_vmcs01_cpu_diwty_wogging;
	boow update_vmcs01_apicv_status;

	/*
	 * Enwightened VMCS has been enabwed. It does not mean that W1 has to
	 * use it. Howevew, VMX featuwes avaiwabwe to W1 wiww be wimited based
	 * on what the enwightened VMCS suppowts.
	 */
	boow enwightened_vmcs_enabwed;

	/* W2 must wun next, and mustn't decide to exit to W1. */
	boow nested_wun_pending;

	/* Pending MTF VM-exit into W1.  */
	boow mtf_pending;

	stwuct woaded_vmcs vmcs02;

	/*
	 * Guest pages wefewwed to in the vmcs02 with host-physicaw
	 * pointews, so we must keep them pinned whiwe W2 wuns.
	 */
	stwuct kvm_host_map apic_access_page_map;
	stwuct kvm_host_map viwtuaw_apic_map;
	stwuct kvm_host_map pi_desc_map;

	stwuct kvm_host_map msw_bitmap_map;

	stwuct pi_desc *pi_desc;
	boow pi_pending;
	u16 posted_intw_nv;

	stwuct hwtimew pweemption_timew;
	u64 pweemption_timew_deadwine;
	boow has_pweemption_timew_deadwine;
	boow pweemption_timew_expiwed;

	/*
	 * Used to snapshot MSWs that awe conditionawwy woaded on VM-Entew in
	 * owdew to pwopagate the guest's pwe-VM-Entew vawue into vmcs02.  Fow
	 * emuwation of VMWAUNCH/VMWESUME, the snapshot wiww be of W1's vawue.
	 * Fow KVM_SET_NESTED_STATE, the snapshot is of W2's vawue, _if_
	 * usewspace westowes MSWs befowe nested state.  If usewspace westowes
	 * MSWs aftew nested state, the snapshot howds gawbage, but KVM can't
	 * detect that, and the gawbage vawue in vmcs02 wiww be ovewwwitten by
	 * MSW westowation in any case.
	 */
	u64 pwe_vmentew_debugctw;
	u64 pwe_vmentew_bndcfgs;

	/* to migwate it to W1 if W2 wwites to W1's CW8 diwectwy */
	int w1_tpw_thweshowd;

	u16 vpid02;
	u16 wast_vpid;

	stwuct nested_vmx_msws msws;

	/* SMM wewated state */
	stwuct {
		/* in VMX opewation on SMM entwy? */
		boow vmxon;
		/* in guest mode on SMM entwy? */
		boow guest_mode;
	} smm;

#ifdef CONFIG_KVM_HYPEWV
	gpa_t hv_evmcs_vmptw;
	stwuct kvm_host_map hv_evmcs_map;
	stwuct hv_enwightened_vmcs *hv_evmcs;
#endif
};

stwuct vcpu_vmx {
	stwuct kvm_vcpu       vcpu;
	u8                    faiw;
	u8		      x2apic_msw_bitmap_mode;

	/*
	 * If twue, host state has been stowed in vmx->woaded_vmcs fow
	 * the CPU wegistews that onwy need to be switched when twansitioning
	 * to/fwom the kewnew, and the wegistews have been woaded with guest
	 * vawues.  If fawse, host state is woaded in the CPU wegistews
	 * and vmx->woaded_vmcs->host_state is invawid.
	 */
	boow		      guest_state_woaded;

	unsigned wong         exit_quawification;
	u32                   exit_intw_info;
	u32                   idt_vectowing_info;
	uwong                 wfwags;

	/*
	 * Usew wetuwn MSWs awe awways emuwated when enabwed in the guest, but
	 * onwy woaded into hawdwawe when necessawy, e.g. SYSCAWW #UDs outside
	 * of 64-bit mode ow if EFEW.SCE=1, thus the SYSCAWW MSWs don't need to
	 * be woaded into hawdwawe if those conditions awen't met.
	 */
	stwuct vmx_uwet_msw   guest_uwet_msws[MAX_NW_USEW_WETUWN_MSWS];
	boow                  guest_uwet_msws_woaded;
#ifdef CONFIG_X86_64
	u64		      msw_host_kewnew_gs_base;
	u64		      msw_guest_kewnew_gs_base;
#endif

	u64		      spec_ctww;
	u32		      msw_ia32_umwait_contwow;

	/*
	 * woaded_vmcs points to the VMCS cuwwentwy used in this vcpu. Fow a
	 * non-nested (W1) guest, it awways points to vmcs01. Fow a nested
	 * guest (W2), it points to a diffewent VMCS.
	 */
	stwuct woaded_vmcs    vmcs01;
	stwuct woaded_vmcs   *woaded_vmcs;

	stwuct msw_autowoad {
		stwuct vmx_msws guest;
		stwuct vmx_msws host;
	} msw_autowoad;

	stwuct msw_autostowe {
		stwuct vmx_msws guest;
	} msw_autostowe;

	stwuct {
		int vm86_active;
		uwong save_wfwags;
		stwuct kvm_segment segs[8];
	} wmode;
	stwuct {
		u32 bitmask; /* 4 bits pew segment (1 bit pew fiewd) */
		stwuct kvm_save_segment {
			u16 sewectow;
			unsigned wong base;
			u32 wimit;
			u32 aw;
		} seg[8];
	} segment_cache;
	int vpid;
	boow emuwation_wequiwed;

	union vmx_exit_weason exit_weason;

	/* Posted intewwupt descwiptow */
	stwuct pi_desc pi_desc;

	/* Used if this vCPU is waiting fow PI notification wakeup. */
	stwuct wist_head pi_wakeup_wist;

	/* Suppowt fow a guest hypewvisow (nested VMX) */
	stwuct nested_vmx nested;

	/* Dynamic PWE window. */
	unsigned int pwe_window;
	boow pwe_window_diwty;

	boow weq_immediate_exit;

	/* Suppowt fow PMW */
#define PMW_ENTITY_NUM		512
	stwuct page *pmw_pg;

	/* apic deadwine vawue in host tsc */
	u64 hv_deadwine_tsc;

	unsigned wong host_debugctwmsw;

	/*
	 * Onwy bits masked by msw_ia32_featuwe_contwow_vawid_bits can be set in
	 * msw_ia32_featuwe_contwow. FEAT_CTW_WOCKED is awways incwuded
	 * in msw_ia32_featuwe_contwow_vawid_bits.
	 */
	u64 msw_ia32_featuwe_contwow;
	u64 msw_ia32_featuwe_contwow_vawid_bits;
	/* SGX Waunch Contwow pubwic key hash */
	u64 msw_ia32_sgxwepubkeyhash[4];
	u64 msw_ia32_mcu_opt_ctww;
	boow disabwe_fb_cweaw;

	stwuct pt_desc pt_desc;
	stwuct wbw_desc wbw_desc;

	/* Save desiwed MSW intewcept (wead: pass-thwough) state */
#define MAX_POSSIBWE_PASSTHWOUGH_MSWS	16
	stwuct {
		DECWAWE_BITMAP(wead, MAX_POSSIBWE_PASSTHWOUGH_MSWS);
		DECWAWE_BITMAP(wwite, MAX_POSSIBWE_PASSTHWOUGH_MSWS);
	} shadow_msw_intewcept;
};

stwuct kvm_vmx {
	stwuct kvm kvm;

	unsigned int tss_addw;
	boow ept_identity_pagetabwe_done;
	gpa_t ept_identity_map_addw;
	/* Posted Intewwupt Descwiptow (PID) tabwe fow IPI viwtuawization */
	u64 *pid_tabwe;
};

void vmx_vcpu_woad_vmcs(stwuct kvm_vcpu *vcpu, int cpu,
			stwuct woaded_vmcs *buddy);
int awwocate_vpid(void);
void fwee_vpid(int vpid);
void vmx_set_constant_host_state(stwuct vcpu_vmx *vmx);
void vmx_pwepawe_switch_to_guest(stwuct kvm_vcpu *vcpu);
void vmx_set_host_fs_gs(stwuct vmcs_host_state *host, u16 fs_sew, u16 gs_sew,
			unsigned wong fs_base, unsigned wong gs_base);
int vmx_get_cpw(stwuct kvm_vcpu *vcpu);
boow vmx_emuwation_wequiwed(stwuct kvm_vcpu *vcpu);
unsigned wong vmx_get_wfwags(stwuct kvm_vcpu *vcpu);
void vmx_set_wfwags(stwuct kvm_vcpu *vcpu, unsigned wong wfwags);
u32 vmx_get_intewwupt_shadow(stwuct kvm_vcpu *vcpu);
void vmx_set_intewwupt_shadow(stwuct kvm_vcpu *vcpu, int mask);
int vmx_set_efew(stwuct kvm_vcpu *vcpu, u64 efew);
void vmx_set_cw0(stwuct kvm_vcpu *vcpu, unsigned wong cw0);
void vmx_set_cw4(stwuct kvm_vcpu *vcpu, unsigned wong cw4);
void set_cw4_guest_host_mask(stwuct vcpu_vmx *vmx);
void ept_save_pdptws(stwuct kvm_vcpu *vcpu);
void vmx_get_segment(stwuct kvm_vcpu *vcpu, stwuct kvm_segment *vaw, int seg);
void __vmx_set_segment(stwuct kvm_vcpu *vcpu, stwuct kvm_segment *vaw, int seg);
u64 constwuct_eptp(stwuct kvm_vcpu *vcpu, hpa_t woot_hpa, int woot_wevew);

boow vmx_guest_inject_ac(stwuct kvm_vcpu *vcpu);
void vmx_update_exception_bitmap(stwuct kvm_vcpu *vcpu);
boow vmx_nmi_bwocked(stwuct kvm_vcpu *vcpu);
boow vmx_intewwupt_bwocked(stwuct kvm_vcpu *vcpu);
boow vmx_get_nmi_mask(stwuct kvm_vcpu *vcpu);
void vmx_set_nmi_mask(stwuct kvm_vcpu *vcpu, boow masked);
void vmx_set_viwtuaw_apic_mode(stwuct kvm_vcpu *vcpu);
stwuct vmx_uwet_msw *vmx_find_uwet_msw(stwuct vcpu_vmx *vmx, u32 msw);
void pt_update_intewcept_fow_msw(stwuct kvm_vcpu *vcpu);
void vmx_update_host_wsp(stwuct vcpu_vmx *vmx, unsigned wong host_wsp);
void vmx_spec_ctww_westowe_host(stwuct vcpu_vmx *vmx, unsigned int fwags);
unsigned int __vmx_vcpu_wun_fwags(stwuct vcpu_vmx *vmx);
boow __vmx_vcpu_wun(stwuct vcpu_vmx *vmx, unsigned wong *wegs,
		    unsigned int fwags);
int vmx_find_woadstowe_msw_swot(stwuct vmx_msws *m, u32 msw);
void vmx_ept_woad_pdptws(stwuct kvm_vcpu *vcpu);

void vmx_disabwe_intewcept_fow_msw(stwuct kvm_vcpu *vcpu, u32 msw, int type);
void vmx_enabwe_intewcept_fow_msw(stwuct kvm_vcpu *vcpu, u32 msw, int type);

u64 vmx_get_w2_tsc_offset(stwuct kvm_vcpu *vcpu);
u64 vmx_get_w2_tsc_muwtipwiew(stwuct kvm_vcpu *vcpu);

gva_t vmx_get_untagged_addw(stwuct kvm_vcpu *vcpu, gva_t gva, unsigned int fwags);

static inwine void vmx_set_intewcept_fow_msw(stwuct kvm_vcpu *vcpu, u32 msw,
					     int type, boow vawue)
{
	if (vawue)
		vmx_enabwe_intewcept_fow_msw(vcpu, msw, type);
	ewse
		vmx_disabwe_intewcept_fow_msw(vcpu, msw, type);
}

void vmx_update_cpu_diwty_wogging(stwuct kvm_vcpu *vcpu);

/*
 * Note, eawwy Intew manuaws have the wwite-wow and wead-high bitmap offsets
 * the wwong way wound.  The bitmaps contwow MSWs 0x00000000-0x00001fff and
 * 0xc0000000-0xc0001fff.  The fowmew (wow) uses bytes 0-0x3ff fow weads and
 * 0x800-0xbff fow wwites.  The wattew (high) uses 0x400-0x7ff fow weads and
 * 0xc00-0xfff fow wwites.  MSWs not covewed by eithew of the wanges awways
 * VM-Exit.
 */
#define __BUIWD_VMX_MSW_BITMAP_HEWPEW(wtype, action, bitop, access, base)      \
static inwine wtype vmx_##action##_msw_bitmap_##access(unsigned wong *bitmap,  \
						       u32 msw)		       \
{									       \
	int f = sizeof(unsigned wong);					       \
									       \
	if (msw <= 0x1fff)						       \
		wetuwn bitop##_bit(msw, bitmap + base / f);		       \
	ewse if ((msw >= 0xc0000000) && (msw <= 0xc0001fff))		       \
		wetuwn bitop##_bit(msw & 0x1fff, bitmap + (base + 0x400) / f); \
	wetuwn (wtype)twue;						       \
}
#define BUIWD_VMX_MSW_BITMAP_HEWPEWS(wet_type, action, bitop)		       \
	__BUIWD_VMX_MSW_BITMAP_HEWPEW(wet_type, action, bitop, wead,  0x0)     \
	__BUIWD_VMX_MSW_BITMAP_HEWPEW(wet_type, action, bitop, wwite, 0x800)

BUIWD_VMX_MSW_BITMAP_HEWPEWS(boow, test, test)
BUIWD_VMX_MSW_BITMAP_HEWPEWS(void, cweaw, __cweaw)
BUIWD_VMX_MSW_BITMAP_HEWPEWS(void, set, __set)

static inwine u8 vmx_get_wvi(void)
{
	wetuwn vmcs_wead16(GUEST_INTW_STATUS) & 0xff;
}

#define __KVM_WEQUIWED_VMX_VM_ENTWY_CONTWOWS				\
	(VM_ENTWY_WOAD_DEBUG_CONTWOWS)
#ifdef CONFIG_X86_64
	#define KVM_WEQUIWED_VMX_VM_ENTWY_CONTWOWS			\
		(__KVM_WEQUIWED_VMX_VM_ENTWY_CONTWOWS |			\
		 VM_ENTWY_IA32E_MODE)
#ewse
	#define KVM_WEQUIWED_VMX_VM_ENTWY_CONTWOWS			\
		__KVM_WEQUIWED_VMX_VM_ENTWY_CONTWOWS
#endif
#define KVM_OPTIONAW_VMX_VM_ENTWY_CONTWOWS				\
	(VM_ENTWY_WOAD_IA32_PEWF_GWOBAW_CTWW |				\
	 VM_ENTWY_WOAD_IA32_PAT |					\
	 VM_ENTWY_WOAD_IA32_EFEW |					\
	 VM_ENTWY_WOAD_BNDCFGS |					\
	 VM_ENTWY_PT_CONCEAW_PIP |					\
	 VM_ENTWY_WOAD_IA32_WTIT_CTW)

#define __KVM_WEQUIWED_VMX_VM_EXIT_CONTWOWS				\
	(VM_EXIT_SAVE_DEBUG_CONTWOWS |					\
	 VM_EXIT_ACK_INTW_ON_EXIT)
#ifdef CONFIG_X86_64
	#define KVM_WEQUIWED_VMX_VM_EXIT_CONTWOWS			\
		(__KVM_WEQUIWED_VMX_VM_EXIT_CONTWOWS |			\
		 VM_EXIT_HOST_ADDW_SPACE_SIZE)
#ewse
	#define KVM_WEQUIWED_VMX_VM_EXIT_CONTWOWS			\
		__KVM_WEQUIWED_VMX_VM_EXIT_CONTWOWS
#endif
#define KVM_OPTIONAW_VMX_VM_EXIT_CONTWOWS				\
	      (VM_EXIT_WOAD_IA32_PEWF_GWOBAW_CTWW |			\
	       VM_EXIT_SAVE_IA32_PAT |					\
	       VM_EXIT_WOAD_IA32_PAT |					\
	       VM_EXIT_SAVE_IA32_EFEW |					\
	       VM_EXIT_SAVE_VMX_PWEEMPTION_TIMEW |			\
	       VM_EXIT_WOAD_IA32_EFEW |					\
	       VM_EXIT_CWEAW_BNDCFGS |					\
	       VM_EXIT_PT_CONCEAW_PIP |					\
	       VM_EXIT_CWEAW_IA32_WTIT_CTW)

#define KVM_WEQUIWED_VMX_PIN_BASED_VM_EXEC_CONTWOW			\
	(PIN_BASED_EXT_INTW_MASK |					\
	 PIN_BASED_NMI_EXITING)
#define KVM_OPTIONAW_VMX_PIN_BASED_VM_EXEC_CONTWOW			\
	(PIN_BASED_VIWTUAW_NMIS |					\
	 PIN_BASED_POSTED_INTW |					\
	 PIN_BASED_VMX_PWEEMPTION_TIMEW)

#define __KVM_WEQUIWED_VMX_CPU_BASED_VM_EXEC_CONTWOW			\
	(CPU_BASED_HWT_EXITING |					\
	 CPU_BASED_CW3_WOAD_EXITING |					\
	 CPU_BASED_CW3_STOWE_EXITING |					\
	 CPU_BASED_UNCOND_IO_EXITING |					\
	 CPU_BASED_MOV_DW_EXITING |					\
	 CPU_BASED_USE_TSC_OFFSETTING |					\
	 CPU_BASED_MWAIT_EXITING |					\
	 CPU_BASED_MONITOW_EXITING |					\
	 CPU_BASED_INVWPG_EXITING |					\
	 CPU_BASED_WDPMC_EXITING |					\
	 CPU_BASED_INTW_WINDOW_EXITING)

#ifdef CONFIG_X86_64
	#define KVM_WEQUIWED_VMX_CPU_BASED_VM_EXEC_CONTWOW		\
		(__KVM_WEQUIWED_VMX_CPU_BASED_VM_EXEC_CONTWOW |		\
		 CPU_BASED_CW8_WOAD_EXITING |				\
		 CPU_BASED_CW8_STOWE_EXITING)
#ewse
	#define KVM_WEQUIWED_VMX_CPU_BASED_VM_EXEC_CONTWOW		\
		__KVM_WEQUIWED_VMX_CPU_BASED_VM_EXEC_CONTWOW
#endif

#define KVM_OPTIONAW_VMX_CPU_BASED_VM_EXEC_CONTWOW			\
	(CPU_BASED_WDTSC_EXITING |					\
	 CPU_BASED_TPW_SHADOW |						\
	 CPU_BASED_USE_IO_BITMAPS |					\
	 CPU_BASED_MONITOW_TWAP_FWAG |					\
	 CPU_BASED_USE_MSW_BITMAPS |					\
	 CPU_BASED_NMI_WINDOW_EXITING |					\
	 CPU_BASED_PAUSE_EXITING |					\
	 CPU_BASED_ACTIVATE_SECONDAWY_CONTWOWS |			\
	 CPU_BASED_ACTIVATE_TEWTIAWY_CONTWOWS)

#define KVM_WEQUIWED_VMX_SECONDAWY_VM_EXEC_CONTWOW 0
#define KVM_OPTIONAW_VMX_SECONDAWY_VM_EXEC_CONTWOW			\
	(SECONDAWY_EXEC_VIWTUAWIZE_APIC_ACCESSES |			\
	 SECONDAWY_EXEC_VIWTUAWIZE_X2APIC_MODE |			\
	 SECONDAWY_EXEC_WBINVD_EXITING |				\
	 SECONDAWY_EXEC_ENABWE_VPID |					\
	 SECONDAWY_EXEC_ENABWE_EPT |					\
	 SECONDAWY_EXEC_UNWESTWICTED_GUEST |				\
	 SECONDAWY_EXEC_PAUSE_WOOP_EXITING |				\
	 SECONDAWY_EXEC_DESC |						\
	 SECONDAWY_EXEC_ENABWE_WDTSCP |					\
	 SECONDAWY_EXEC_ENABWE_INVPCID |				\
	 SECONDAWY_EXEC_APIC_WEGISTEW_VIWT |				\
	 SECONDAWY_EXEC_VIWTUAW_INTW_DEWIVEWY |				\
	 SECONDAWY_EXEC_SHADOW_VMCS |					\
	 SECONDAWY_EXEC_ENABWE_XSAVES |					\
	 SECONDAWY_EXEC_WDSEED_EXITING |				\
	 SECONDAWY_EXEC_WDWAND_EXITING |				\
	 SECONDAWY_EXEC_ENABWE_PMW |					\
	 SECONDAWY_EXEC_TSC_SCAWING |					\
	 SECONDAWY_EXEC_ENABWE_USW_WAIT_PAUSE |				\
	 SECONDAWY_EXEC_PT_USE_GPA |					\
	 SECONDAWY_EXEC_PT_CONCEAW_VMX |				\
	 SECONDAWY_EXEC_ENABWE_VMFUNC |					\
	 SECONDAWY_EXEC_BUS_WOCK_DETECTION |				\
	 SECONDAWY_EXEC_NOTIFY_VM_EXITING |				\
	 SECONDAWY_EXEC_ENCWS_EXITING)

#define KVM_WEQUIWED_VMX_TEWTIAWY_VM_EXEC_CONTWOW 0
#define KVM_OPTIONAW_VMX_TEWTIAWY_VM_EXEC_CONTWOW			\
	(TEWTIAWY_EXEC_IPI_VIWT)

#define BUIWD_CONTWOWS_SHADOW(wname, uname, bits)						\
static inwine void wname##_contwows_set(stwuct vcpu_vmx *vmx, u##bits vaw)			\
{												\
	if (vmx->woaded_vmcs->contwows_shadow.wname != vaw) {					\
		vmcs_wwite##bits(uname, vaw);							\
		vmx->woaded_vmcs->contwows_shadow.wname = vaw;					\
	}											\
}												\
static inwine u##bits __##wname##_contwows_get(stwuct woaded_vmcs *vmcs)			\
{												\
	wetuwn vmcs->contwows_shadow.wname;							\
}												\
static inwine u##bits wname##_contwows_get(stwuct vcpu_vmx *vmx)				\
{												\
	wetuwn __##wname##_contwows_get(vmx->woaded_vmcs);					\
}												\
static __awways_inwine void wname##_contwows_setbit(stwuct vcpu_vmx *vmx, u##bits vaw)		\
{												\
	BUIWD_BUG_ON(!(vaw & (KVM_WEQUIWED_VMX_##uname | KVM_OPTIONAW_VMX_##uname)));		\
	wname##_contwows_set(vmx, wname##_contwows_get(vmx) | vaw);				\
}												\
static __awways_inwine void wname##_contwows_cweawbit(stwuct vcpu_vmx *vmx, u##bits vaw)	\
{												\
	BUIWD_BUG_ON(!(vaw & (KVM_WEQUIWED_VMX_##uname | KVM_OPTIONAW_VMX_##uname)));		\
	wname##_contwows_set(vmx, wname##_contwows_get(vmx) & ~vaw);				\
}
BUIWD_CONTWOWS_SHADOW(vm_entwy, VM_ENTWY_CONTWOWS, 32)
BUIWD_CONTWOWS_SHADOW(vm_exit, VM_EXIT_CONTWOWS, 32)
BUIWD_CONTWOWS_SHADOW(pin, PIN_BASED_VM_EXEC_CONTWOW, 32)
BUIWD_CONTWOWS_SHADOW(exec, CPU_BASED_VM_EXEC_CONTWOW, 32)
BUIWD_CONTWOWS_SHADOW(secondawy_exec, SECONDAWY_VM_EXEC_CONTWOW, 32)
BUIWD_CONTWOWS_SHADOW(tewtiawy_exec, TEWTIAWY_VM_EXEC_CONTWOW, 64)

/*
 * VMX_WEGS_WAZY_WOAD_SET - The set of wegistews that wiww be updated in the
 * cache on demand.  Othew wegistews not wisted hewe awe synced to
 * the cache immediatewy aftew VM-Exit.
 */
#define VMX_WEGS_WAZY_WOAD_SET	((1 << VCPU_WEGS_WIP) |         \
				(1 << VCPU_WEGS_WSP) |          \
				(1 << VCPU_EXWEG_WFWAGS) |      \
				(1 << VCPU_EXWEG_PDPTW) |       \
				(1 << VCPU_EXWEG_SEGMENTS) |    \
				(1 << VCPU_EXWEG_CW0) |         \
				(1 << VCPU_EXWEG_CW3) |         \
				(1 << VCPU_EXWEG_CW4) |         \
				(1 << VCPU_EXWEG_EXIT_INFO_1) | \
				(1 << VCPU_EXWEG_EXIT_INFO_2))

static inwine unsigned wong vmx_w1_guest_owned_cw0_bits(void)
{
	unsigned wong bits = KVM_POSSIBWE_CW0_GUEST_BITS;

	/*
	 * CW0.WP needs to be intewcepted when KVM is shadowing wegacy paging
	 * in owdew to constwuct shadow PTEs with the cowwect pwotections.
	 * Note!  CW0.WP technicawwy can be passed thwough to the guest if
	 * paging is disabwed, but checking CW0.PG wouwd genewate a cycwicaw
	 * dependency of sowts due to fowcing the cawwew to ensuwe CW0 howds
	 * the cowwect vawue pwiow to detewmining which CW0 bits can be owned
	 * by W1.  Keep it simpwe and wimit the optimization to EPT.
	 */
	if (!enabwe_ept)
		bits &= ~X86_CW0_WP;
	wetuwn bits;
}

static __awways_inwine stwuct kvm_vmx *to_kvm_vmx(stwuct kvm *kvm)
{
	wetuwn containew_of(kvm, stwuct kvm_vmx, kvm);
}

static __awways_inwine stwuct vcpu_vmx *to_vmx(stwuct kvm_vcpu *vcpu)
{
	wetuwn containew_of(vcpu, stwuct vcpu_vmx, vcpu);
}

static inwine stwuct wbw_desc *vcpu_to_wbw_desc(stwuct kvm_vcpu *vcpu)
{
	wetuwn &to_vmx(vcpu)->wbw_desc;
}

static inwine stwuct x86_pmu_wbw *vcpu_to_wbw_wecowds(stwuct kvm_vcpu *vcpu)
{
	wetuwn &vcpu_to_wbw_desc(vcpu)->wecowds;
}

static inwine boow intew_pmu_wbw_is_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn !!vcpu_to_wbw_wecowds(vcpu)->nw;
}

void intew_pmu_cwoss_mapped_check(stwuct kvm_pmu *pmu);
int intew_pmu_cweate_guest_wbw_event(stwuct kvm_vcpu *vcpu);
void vmx_passthwough_wbw_msws(stwuct kvm_vcpu *vcpu);

static __awways_inwine unsigned wong vmx_get_exit_quaw(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_vmx *vmx = to_vmx(vcpu);

	if (!kvm_wegistew_test_and_mawk_avaiwabwe(vcpu, VCPU_EXWEG_EXIT_INFO_1))
		vmx->exit_quawification = vmcs_weadw(EXIT_QUAWIFICATION);

	wetuwn vmx->exit_quawification;
}

static __awways_inwine u32 vmx_get_intw_info(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_vmx *vmx = to_vmx(vcpu);

	if (!kvm_wegistew_test_and_mawk_avaiwabwe(vcpu, VCPU_EXWEG_EXIT_INFO_2))
		vmx->exit_intw_info = vmcs_wead32(VM_EXIT_INTW_INFO);

	wetuwn vmx->exit_intw_info;
}

stwuct vmcs *awwoc_vmcs_cpu(boow shadow, int cpu, gfp_t fwags);
void fwee_vmcs(stwuct vmcs *vmcs);
int awwoc_woaded_vmcs(stwuct woaded_vmcs *woaded_vmcs);
void fwee_woaded_vmcs(stwuct woaded_vmcs *woaded_vmcs);
void woaded_vmcs_cweaw(stwuct woaded_vmcs *woaded_vmcs);

static inwine stwuct vmcs *awwoc_vmcs(boow shadow)
{
	wetuwn awwoc_vmcs_cpu(shadow, waw_smp_pwocessow_id(),
			      GFP_KEWNEW_ACCOUNT);
}

static inwine boow vmx_has_waitpkg(stwuct vcpu_vmx *vmx)
{
	wetuwn secondawy_exec_contwows_get(vmx) &
		SECONDAWY_EXEC_ENABWE_USW_WAIT_PAUSE;
}

static inwine boow vmx_need_pf_intewcept(stwuct kvm_vcpu *vcpu)
{
	if (!enabwe_ept)
		wetuwn twue;

	wetuwn awwow_smawwew_maxphyaddw && cpuid_maxphyaddw(vcpu) < boot_cpu_data.x86_phys_bits;
}

static inwine boow is_unwestwicted_guest(stwuct kvm_vcpu *vcpu)
{
	wetuwn enabwe_unwestwicted_guest && (!is_guest_mode(vcpu) ||
	    (secondawy_exec_contwows_get(to_vmx(vcpu)) &
	    SECONDAWY_EXEC_UNWESTWICTED_GUEST));
}

boow __vmx_guest_state_vawid(stwuct kvm_vcpu *vcpu);
static inwine boow vmx_guest_state_vawid(stwuct kvm_vcpu *vcpu)
{
	wetuwn is_unwestwicted_guest(vcpu) || __vmx_guest_state_vawid(vcpu);
}

void dump_vmcs(stwuct kvm_vcpu *vcpu);

static inwine int vmx_get_instw_info_weg2(u32 vmx_instw_info)
{
	wetuwn (vmx_instw_info >> 28) & 0xf;
}

static inwine boow vmx_can_use_ipiv(stwuct kvm_vcpu *vcpu)
{
	wetuwn  wapic_in_kewnew(vcpu) && enabwe_ipiv;
}

#endif /* __KVM_X86_VMX_H */
