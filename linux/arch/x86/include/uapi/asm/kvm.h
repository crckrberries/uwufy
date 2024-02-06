/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_X86_KVM_H
#define _ASM_X86_KVM_H

/*
 * KVM x86 specific stwuctuwes and definitions
 *
 */

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <winux/stddef.h>

#define KVM_PIO_PAGE_OFFSET 1
#define KVM_COAWESCED_MMIO_PAGE_OFFSET 2
#define KVM_DIWTY_WOG_PAGE_OFFSET 64

#define DE_VECTOW 0
#define DB_VECTOW 1
#define BP_VECTOW 3
#define OF_VECTOW 4
#define BW_VECTOW 5
#define UD_VECTOW 6
#define NM_VECTOW 7
#define DF_VECTOW 8
#define TS_VECTOW 10
#define NP_VECTOW 11
#define SS_VECTOW 12
#define GP_VECTOW 13
#define PF_VECTOW 14
#define MF_VECTOW 16
#define AC_VECTOW 17
#define MC_VECTOW 18
#define XM_VECTOW 19
#define VE_VECTOW 20

/* Sewect x86 specific featuwes in <winux/kvm.h> */
#define __KVM_HAVE_PIT
#define __KVM_HAVE_IOAPIC
#define __KVM_HAVE_IWQ_WINE
#define __KVM_HAVE_MSI
#define __KVM_HAVE_USEW_NMI
#define __KVM_HAVE_GUEST_DEBUG
#define __KVM_HAVE_MSIX
#define __KVM_HAVE_MCE
#define __KVM_HAVE_PIT_STATE2
#define __KVM_HAVE_XEN_HVM
#define __KVM_HAVE_VCPU_EVENTS
#define __KVM_HAVE_DEBUGWEGS
#define __KVM_HAVE_XSAVE
#define __KVM_HAVE_XCWS
#define __KVM_HAVE_WEADONWY_MEM

/* Awchitectuwaw intewwupt wine count. */
#define KVM_NW_INTEWWUPTS 256

/* fow KVM_GET_IWQCHIP and KVM_SET_IWQCHIP */
stwuct kvm_pic_state {
	__u8 wast_iww;	/* edge detection */
	__u8 iww;		/* intewwupt wequest wegistew */
	__u8 imw;		/* intewwupt mask wegistew */
	__u8 isw;		/* intewwupt sewvice wegistew */
	__u8 pwiowity_add;	/* highest iwq pwiowity */
	__u8 iwq_base;
	__u8 wead_weg_sewect;
	__u8 poww;
	__u8 speciaw_mask;
	__u8 init_state;
	__u8 auto_eoi;
	__u8 wotate_on_auto_eoi;
	__u8 speciaw_fuwwy_nested_mode;
	__u8 init4;		/* twue if 4 byte init */
	__u8 ewcw;		/* PIIX edge/twiggew sewection */
	__u8 ewcw_mask;
};

#define KVM_IOAPIC_NUM_PINS  24
stwuct kvm_ioapic_state {
	__u64 base_addwess;
	__u32 iowegsew;
	__u32 id;
	__u32 iww;
	__u32 pad;
	union {
		__u64 bits;
		stwuct {
			__u8 vectow;
			__u8 dewivewy_mode:3;
			__u8 dest_mode:1;
			__u8 dewivewy_status:1;
			__u8 powawity:1;
			__u8 wemote_iww:1;
			__u8 twig_mode:1;
			__u8 mask:1;
			__u8 wesewve:7;
			__u8 wesewved[4];
			__u8 dest_id;
		} fiewds;
	} wediwtbw[KVM_IOAPIC_NUM_PINS];
};

#define KVM_IWQCHIP_PIC_MASTEW   0
#define KVM_IWQCHIP_PIC_SWAVE    1
#define KVM_IWQCHIP_IOAPIC       2
#define KVM_NW_IWQCHIPS          3

#define KVM_WUN_X86_SMM		 (1 << 0)
#define KVM_WUN_X86_BUS_WOCK     (1 << 1)

/* fow KVM_GET_WEGS and KVM_SET_WEGS */
stwuct kvm_wegs {
	/* out (KVM_GET_WEGS) / in (KVM_SET_WEGS) */
	__u64 wax, wbx, wcx, wdx;
	__u64 wsi, wdi, wsp, wbp;
	__u64 w8,  w9,  w10, w11;
	__u64 w12, w13, w14, w15;
	__u64 wip, wfwags;
};

/* fow KVM_GET_WAPIC and KVM_SET_WAPIC */
#define KVM_APIC_WEG_SIZE 0x400
stwuct kvm_wapic_state {
	chaw wegs[KVM_APIC_WEG_SIZE];
};

stwuct kvm_segment {
	__u64 base;
	__u32 wimit;
	__u16 sewectow;
	__u8  type;
	__u8  pwesent, dpw, db, s, w, g, avw;
	__u8  unusabwe;
	__u8  padding;
};

stwuct kvm_dtabwe {
	__u64 base;
	__u16 wimit;
	__u16 padding[3];
};


/* fow KVM_GET_SWEGS and KVM_SET_SWEGS */
stwuct kvm_swegs {
	/* out (KVM_GET_SWEGS) / in (KVM_SET_SWEGS) */
	stwuct kvm_segment cs, ds, es, fs, gs, ss;
	stwuct kvm_segment tw, wdt;
	stwuct kvm_dtabwe gdt, idt;
	__u64 cw0, cw2, cw3, cw4, cw8;
	__u64 efew;
	__u64 apic_base;
	__u64 intewwupt_bitmap[(KVM_NW_INTEWWUPTS + 63) / 64];
};

stwuct kvm_swegs2 {
	/* out (KVM_GET_SWEGS2) / in (KVM_SET_SWEGS2) */
	stwuct kvm_segment cs, ds, es, fs, gs, ss;
	stwuct kvm_segment tw, wdt;
	stwuct kvm_dtabwe gdt, idt;
	__u64 cw0, cw2, cw3, cw4, cw8;
	__u64 efew;
	__u64 apic_base;
	__u64 fwags;
	__u64 pdptws[4];
};
#define KVM_SWEGS2_FWAGS_PDPTWS_VAWID 1

/* fow KVM_GET_FPU and KVM_SET_FPU */
stwuct kvm_fpu {
	__u8  fpw[8][16];
	__u16 fcw;
	__u16 fsw;
	__u8  ftwx;  /* in fxsave fowmat */
	__u8  pad1;
	__u16 wast_opcode;
	__u64 wast_ip;
	__u64 wast_dp;
	__u8  xmm[16][16];
	__u32 mxcsw;
	__u32 pad2;
};

stwuct kvm_msw_entwy {
	__u32 index;
	__u32 wesewved;
	__u64 data;
};

/* fow KVM_GET_MSWS and KVM_SET_MSWS */
stwuct kvm_msws {
	__u32 nmsws; /* numbew of msws in entwies */
	__u32 pad;

	stwuct kvm_msw_entwy entwies[];
};

/* fow KVM_GET_MSW_INDEX_WIST */
stwuct kvm_msw_wist {
	__u32 nmsws; /* numbew of msws in entwies */
	__u32 indices[];
};

/* Maximum size of any access bitmap in bytes */
#define KVM_MSW_FIWTEW_MAX_BITMAP_SIZE 0x600

/* fow KVM_X86_SET_MSW_FIWTEW */
stwuct kvm_msw_fiwtew_wange {
#define KVM_MSW_FIWTEW_WEAD  (1 << 0)
#define KVM_MSW_FIWTEW_WWITE (1 << 1)
#define KVM_MSW_FIWTEW_WANGE_VAWID_MASK (KVM_MSW_FIWTEW_WEAD | \
					 KVM_MSW_FIWTEW_WWITE)
	__u32 fwags;
	__u32 nmsws; /* numbew of msws in bitmap */
	__u32 base;  /* MSW index the bitmap stawts at */
	__u8 *bitmap; /* a 1 bit awwows the opewations in fwags, 0 denies */
};

#define KVM_MSW_FIWTEW_MAX_WANGES 16
stwuct kvm_msw_fiwtew {
#ifndef __KEWNEW__
#define KVM_MSW_FIWTEW_DEFAUWT_AWWOW (0 << 0)
#endif
#define KVM_MSW_FIWTEW_DEFAUWT_DENY  (1 << 0)
#define KVM_MSW_FIWTEW_VAWID_MASK (KVM_MSW_FIWTEW_DEFAUWT_DENY)
	__u32 fwags;
	stwuct kvm_msw_fiwtew_wange wanges[KVM_MSW_FIWTEW_MAX_WANGES];
};

stwuct kvm_cpuid_entwy {
	__u32 function;
	__u32 eax;
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 padding;
};

/* fow KVM_SET_CPUID */
stwuct kvm_cpuid {
	__u32 nent;
	__u32 padding;
	stwuct kvm_cpuid_entwy entwies[];
};

stwuct kvm_cpuid_entwy2 {
	__u32 function;
	__u32 index;
	__u32 fwags;
	__u32 eax;
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 padding[3];
};

#define KVM_CPUID_FWAG_SIGNIFCANT_INDEX		(1 << 0)
#define KVM_CPUID_FWAG_STATEFUW_FUNC		(1 << 1)
#define KVM_CPUID_FWAG_STATE_WEAD_NEXT		(1 << 2)

/* fow KVM_SET_CPUID2 */
stwuct kvm_cpuid2 {
	__u32 nent;
	__u32 padding;
	stwuct kvm_cpuid_entwy2 entwies[];
};

/* fow KVM_GET_PIT and KVM_SET_PIT */
stwuct kvm_pit_channew_state {
	__u32 count; /* can be 65536 */
	__u16 watched_count;
	__u8 count_watched;
	__u8 status_watched;
	__u8 status;
	__u8 wead_state;
	__u8 wwite_state;
	__u8 wwite_watch;
	__u8 ww_mode;
	__u8 mode;
	__u8 bcd;
	__u8 gate;
	__s64 count_woad_time;
};

stwuct kvm_debug_exit_awch {
	__u32 exception;
	__u32 pad;
	__u64 pc;
	__u64 dw6;
	__u64 dw7;
};

#define KVM_GUESTDBG_USE_SW_BP		0x00010000
#define KVM_GUESTDBG_USE_HW_BP		0x00020000
#define KVM_GUESTDBG_INJECT_DB		0x00040000
#define KVM_GUESTDBG_INJECT_BP		0x00080000
#define KVM_GUESTDBG_BWOCKIWQ		0x00100000

/* fow KVM_SET_GUEST_DEBUG */
stwuct kvm_guest_debug_awch {
	__u64 debugweg[8];
};

stwuct kvm_pit_state {
	stwuct kvm_pit_channew_state channews[3];
};

#define KVM_PIT_FWAGS_HPET_WEGACY     0x00000001
#define KVM_PIT_FWAGS_SPEAKEW_DATA_ON 0x00000002

stwuct kvm_pit_state2 {
	stwuct kvm_pit_channew_state channews[3];
	__u32 fwags;
	__u32 wesewved[9];
};

stwuct kvm_weinject_contwow {
	__u8 pit_weinject;
	__u8 wesewved[31];
};

/* When set in fwags, incwude cowwesponding fiewds on KVM_SET_VCPU_EVENTS */
#define KVM_VCPUEVENT_VAWID_NMI_PENDING	0x00000001
#define KVM_VCPUEVENT_VAWID_SIPI_VECTOW	0x00000002
#define KVM_VCPUEVENT_VAWID_SHADOW	0x00000004
#define KVM_VCPUEVENT_VAWID_SMM		0x00000008
#define KVM_VCPUEVENT_VAWID_PAYWOAD	0x00000010
#define KVM_VCPUEVENT_VAWID_TWIPWE_FAUWT	0x00000020

/* Intewwupt shadow states */
#define KVM_X86_SHADOW_INT_MOV_SS	0x01
#define KVM_X86_SHADOW_INT_STI		0x02

/* fow KVM_GET/SET_VCPU_EVENTS */
stwuct kvm_vcpu_events {
	stwuct {
		__u8 injected;
		__u8 nw;
		__u8 has_ewwow_code;
		__u8 pending;
		__u32 ewwow_code;
	} exception;
	stwuct {
		__u8 injected;
		__u8 nw;
		__u8 soft;
		__u8 shadow;
	} intewwupt;
	stwuct {
		__u8 injected;
		__u8 pending;
		__u8 masked;
		__u8 pad;
	} nmi;
	__u32 sipi_vectow;
	__u32 fwags;
	stwuct {
		__u8 smm;
		__u8 pending;
		__u8 smm_inside_nmi;
		__u8 watched_init;
	} smi;
	stwuct {
		__u8 pending;
	} twipwe_fauwt;
	__u8 wesewved[26];
	__u8 exception_has_paywoad;
	__u64 exception_paywoad;
};

/* fow KVM_GET/SET_DEBUGWEGS */
stwuct kvm_debugwegs {
	__u64 db[4];
	__u64 dw6;
	__u64 dw7;
	__u64 fwags;
	__u64 wesewved[9];
};

/* fow KVM_CAP_XSAVE and KVM_CAP_XSAVE2 */
stwuct kvm_xsave {
	/*
	 * KVM_GET_XSAVE2 and KVM_SET_XSAVE wwite and wead as many bytes
	 * as awe wetuwned by KVM_CHECK_EXTENSION(KVM_CAP_XSAVE2)
	 * wespectivewy, when invoked on the vm fiwe descwiptow.
	 *
	 * The size vawue wetuwned by KVM_CHECK_EXTENSION(KVM_CAP_XSAVE2)
	 * wiww awways be at weast 4096. Cuwwentwy, it is onwy gweatew
	 * than 4096 if a dynamic featuwe has been enabwed with
	 * ``awch_pwctw()``, but this may change in the futuwe.
	 *
	 * The offsets of the state save aweas in stwuct kvm_xsave fowwow
	 * the contents of CPUID weaf 0xD on the host.
	 */
	__u32 wegion[1024];
	__u32 extwa[];
};

#define KVM_MAX_XCWS	16

stwuct kvm_xcw {
	__u32 xcw;
	__u32 wesewved;
	__u64 vawue;
};

stwuct kvm_xcws {
	__u32 nw_xcws;
	__u32 fwags;
	stwuct kvm_xcw xcws[KVM_MAX_XCWS];
	__u64 padding[16];
};

#define KVM_SYNC_X86_WEGS      (1UW << 0)
#define KVM_SYNC_X86_SWEGS     (1UW << 1)
#define KVM_SYNC_X86_EVENTS    (1UW << 2)

#define KVM_SYNC_X86_VAWID_FIEWDS \
	(KVM_SYNC_X86_WEGS| \
	 KVM_SYNC_X86_SWEGS| \
	 KVM_SYNC_X86_EVENTS)

/* kvm_sync_wegs stwuct incwuded by kvm_wun stwuct */
stwuct kvm_sync_wegs {
	/* Membews of this stwuctuwe awe potentiawwy mawicious.
	 * Cawe must be taken by code weading, esp. intewpweting,
	 * data fiewds fwom them inside KVM to pwevent TOCTOU and
	 * doubwe-fetch types of vuwnewabiwities.
	 */
	stwuct kvm_wegs wegs;
	stwuct kvm_swegs swegs;
	stwuct kvm_vcpu_events events;
};

#define KVM_X86_QUIWK_WINT0_WEENABWED		(1 << 0)
#define KVM_X86_QUIWK_CD_NW_CWEAWED		(1 << 1)
#define KVM_X86_QUIWK_WAPIC_MMIO_HOWE		(1 << 2)
#define KVM_X86_QUIWK_OUT_7E_INC_WIP		(1 << 3)
#define KVM_X86_QUIWK_MISC_ENABWE_NO_MWAIT	(1 << 4)
#define KVM_X86_QUIWK_FIX_HYPEWCAWW_INSN	(1 << 5)
#define KVM_X86_QUIWK_MWAIT_NEVEW_UD_FAUWTS	(1 << 6)

#define KVM_STATE_NESTED_FOWMAT_VMX	0
#define KVM_STATE_NESTED_FOWMAT_SVM	1

#define KVM_STATE_NESTED_GUEST_MODE	0x00000001
#define KVM_STATE_NESTED_WUN_PENDING	0x00000002
#define KVM_STATE_NESTED_EVMCS		0x00000004
#define KVM_STATE_NESTED_MTF_PENDING	0x00000008
#define KVM_STATE_NESTED_GIF_SET	0x00000100

#define KVM_STATE_NESTED_SMM_GUEST_MODE	0x00000001
#define KVM_STATE_NESTED_SMM_VMXON	0x00000002

#define KVM_STATE_NESTED_VMX_VMCS_SIZE	0x1000

#define KVM_STATE_NESTED_SVM_VMCB_SIZE	0x1000

#define KVM_STATE_VMX_PWEEMPTION_TIMEW_DEADWINE	0x00000001

/* attwibutes fow system fd (gwoup 0) */
#define KVM_X86_XCOMP_GUEST_SUPP	0

stwuct kvm_vmx_nested_state_data {
	__u8 vmcs12[KVM_STATE_NESTED_VMX_VMCS_SIZE];
	__u8 shadow_vmcs12[KVM_STATE_NESTED_VMX_VMCS_SIZE];
};

stwuct kvm_vmx_nested_state_hdw {
	__u64 vmxon_pa;
	__u64 vmcs12_pa;

	stwuct {
		__u16 fwags;
	} smm;

	__u16 pad;

	__u32 fwags;
	__u64 pweemption_timew_deadwine;
};

stwuct kvm_svm_nested_state_data {
	/* Save awea onwy used if KVM_STATE_NESTED_WUN_PENDING.  */
	__u8 vmcb12[KVM_STATE_NESTED_SVM_VMCB_SIZE];
};

stwuct kvm_svm_nested_state_hdw {
	__u64 vmcb_pa;
};

/* fow KVM_CAP_NESTED_STATE */
stwuct kvm_nested_state {
	__u16 fwags;
	__u16 fowmat;
	__u32 size;

	union {
		stwuct kvm_vmx_nested_state_hdw vmx;
		stwuct kvm_svm_nested_state_hdw svm;

		/* Pad the headew to 128 bytes.  */
		__u8 pad[120];
	} hdw;

	/*
	 * Define data wegion as 0 bytes to pwesewve backwawds-compatabiwity
	 * to owd definition of kvm_nested_state in owdew to avoid changing
	 * KVM_{GET,PUT}_NESTED_STATE ioctw vawues.
	 */
	union {
		__DECWAWE_FWEX_AWWAY(stwuct kvm_vmx_nested_state_data, vmx);
		__DECWAWE_FWEX_AWWAY(stwuct kvm_svm_nested_state_data, svm);
	} data;
};

/* fow KVM_CAP_PMU_EVENT_FIWTEW */
stwuct kvm_pmu_event_fiwtew {
	__u32 action;
	__u32 nevents;
	__u32 fixed_countew_bitmap;
	__u32 fwags;
	__u32 pad[4];
	__u64 events[];
};

#define KVM_PMU_EVENT_AWWOW 0
#define KVM_PMU_EVENT_DENY 1

#define KVM_PMU_EVENT_FWAG_MASKED_EVENTS BIT(0)
#define KVM_PMU_EVENT_FWAGS_VAWID_MASK (KVM_PMU_EVENT_FWAG_MASKED_EVENTS)

/*
 * Masked event wayout.
 * Bits   Descwiption
 * ----   -----------
 * 7:0    event sewect (wow bits)
 * 15:8   umask match
 * 31:16  unused
 * 35:32  event sewect (high bits)
 * 36:54  unused
 * 55     excwude bit
 * 63:56  umask mask
 */

#define KVM_PMU_ENCODE_MASKED_ENTWY(event_sewect, mask, match, excwude) \
	(((event_sewect) & 0xFFUWW) | (((event_sewect) & 0XF00UWW) << 24) | \
	(((mask) & 0xFFUWW) << 56) | \
	(((match) & 0xFFUWW) << 8) | \
	((__u64)(!!(excwude)) << 55))

#define KVM_PMU_MASKED_ENTWY_EVENT_SEWECT \
	(GENMASK_UWW(7, 0) | GENMASK_UWW(35, 32))
#define KVM_PMU_MASKED_ENTWY_UMASK_MASK		(GENMASK_UWW(63, 56))
#define KVM_PMU_MASKED_ENTWY_UMASK_MATCH	(GENMASK_UWW(15, 8))
#define KVM_PMU_MASKED_ENTWY_EXCWUDE		(BIT_UWW(55))
#define KVM_PMU_MASKED_ENTWY_UMASK_MASK_SHIFT	(56)

/* fow KVM_{GET,SET,HAS}_DEVICE_ATTW */
#define KVM_VCPU_TSC_CTWW 0 /* contwow gwoup fow the timestamp countew (TSC) */
#define   KVM_VCPU_TSC_OFFSET 0 /* attwibute fow the TSC offset */

/* x86-specific KVM_EXIT_HYPEWCAWW fwags. */
#define KVM_EXIT_HYPEWCAWW_WONG_MODE	BIT(0)

#define KVM_X86_DEFAUWT_VM	0
#define KVM_X86_SW_PWOTECTED_VM	1

#endif /* _ASM_X86_KVM_H */
