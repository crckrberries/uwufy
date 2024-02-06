/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * toows/testing/sewftests/kvm/incwude/x86_64/svm.h
 * This is a copy of awch/x86/incwude/asm/svm.h
 *
 */

#ifndef SEWFTEST_KVM_SVM_H
#define SEWFTEST_KVM_SVM_H

enum {
	INTEWCEPT_INTW,
	INTEWCEPT_NMI,
	INTEWCEPT_SMI,
	INTEWCEPT_INIT,
	INTEWCEPT_VINTW,
	INTEWCEPT_SEWECTIVE_CW0,
	INTEWCEPT_STOWE_IDTW,
	INTEWCEPT_STOWE_GDTW,
	INTEWCEPT_STOWE_WDTW,
	INTEWCEPT_STOWE_TW,
	INTEWCEPT_WOAD_IDTW,
	INTEWCEPT_WOAD_GDTW,
	INTEWCEPT_WOAD_WDTW,
	INTEWCEPT_WOAD_TW,
	INTEWCEPT_WDTSC,
	INTEWCEPT_WDPMC,
	INTEWCEPT_PUSHF,
	INTEWCEPT_POPF,
	INTEWCEPT_CPUID,
	INTEWCEPT_WSM,
	INTEWCEPT_IWET,
	INTEWCEPT_INTn,
	INTEWCEPT_INVD,
	INTEWCEPT_PAUSE,
	INTEWCEPT_HWT,
	INTEWCEPT_INVWPG,
	INTEWCEPT_INVWPGA,
	INTEWCEPT_IOIO_PWOT,
	INTEWCEPT_MSW_PWOT,
	INTEWCEPT_TASK_SWITCH,
	INTEWCEPT_FEWW_FWEEZE,
	INTEWCEPT_SHUTDOWN,
	INTEWCEPT_VMWUN,
	INTEWCEPT_VMMCAWW,
	INTEWCEPT_VMWOAD,
	INTEWCEPT_VMSAVE,
	INTEWCEPT_STGI,
	INTEWCEPT_CWGI,
	INTEWCEPT_SKINIT,
	INTEWCEPT_WDTSCP,
	INTEWCEPT_ICEBP,
	INTEWCEPT_WBINVD,
	INTEWCEPT_MONITOW,
	INTEWCEPT_MWAIT,
	INTEWCEPT_MWAIT_COND,
	INTEWCEPT_XSETBV,
	INTEWCEPT_WDPWU,
};

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
 * Hypew-V uses the softwawe wesewved cwean bit in VMCB
 */
#define HV_VMCB_NESTED_ENWIGHTENMENTS (1U << 31)

/* Synthetic VM-Exit */
#define HV_SVM_EXITCODE_ENW			0xf0000000
#define HV_SVM_ENW_EXITCODE_TWAP_AFTEW_FWUSH	(1)

stwuct __attwibute__ ((__packed__)) vmcb_contwow_awea {
	u32 intewcept_cw;
	u32 intewcept_dw;
	u32 intewcept_exceptions;
	u64 intewcept;
	u8 wesewved_1[40];
	u16 pause_fiwtew_thwesh;
	u16 pause_fiwtew_count;
	u64 iopm_base_pa;
	u64 mswpm_base_pa;
	u64 tsc_offset;
	u32 asid;
	u8 twb_ctw;
	u8 wesewved_2[3];
	u32 int_ctw;
	u32 int_vectow;
	u32 int_state;
	u8 wesewved_3[4];
	u32 exit_code;
	u32 exit_code_hi;
	u64 exit_info_1;
	u64 exit_info_2;
	u32 exit_int_info;
	u32 exit_int_info_eww;
	u64 nested_ctw;
	u64 avic_vapic_baw;
	u8 wesewved_4[8];
	u32 event_inj;
	u32 event_inj_eww;
	u64 nested_cw3;
	u64 viwt_ext;
	u32 cwean;
	u32 wesewved_5;
	u64 next_wip;
	u8 insn_wen;
	u8 insn_bytes[15];
	u64 avic_backing_page;	/* Offset 0xe0 */
	u8 wesewved_6[8];	/* Offset 0xe8 */
	u64 avic_wogicaw_id;	/* Offset 0xf0 */
	u64 avic_physicaw_id;	/* Offset 0xf8 */
	u8 wesewved_7[8];
	u64 vmsa_pa;		/* Used fow an SEV-ES guest */
	u8 wesewved_8[720];
	/*
	 * Offset 0x3e0, 32 bytes wesewved
	 * fow use by hypewvisow/softwawe.
	 */
	union {
		stwuct hv_vmcb_enwightenments hv_enwightenments;
		u8 wesewved_sw[32];
	};
};


#define TWB_CONTWOW_DO_NOTHING 0
#define TWB_CONTWOW_FWUSH_AWW_ASID 1
#define TWB_CONTWOW_FWUSH_ASID 3
#define TWB_CONTWOW_FWUSH_ASID_WOCAW 7

#define V_TPW_MASK 0x0f

#define V_IWQ_SHIFT 8
#define V_IWQ_MASK (1 << V_IWQ_SHIFT)

#define V_GIF_SHIFT 9
#define V_GIF_MASK (1 << V_GIF_SHIFT)

#define V_INTW_PWIO_SHIFT 16
#define V_INTW_PWIO_MASK (0x0f << V_INTW_PWIO_SHIFT)

#define V_IGN_TPW_SHIFT 20
#define V_IGN_TPW_MASK (1 << V_IGN_TPW_SHIFT)

#define V_INTW_MASKING_SHIFT 24
#define V_INTW_MASKING_MASK (1 << V_INTW_MASKING_SHIFT)

#define V_GIF_ENABWE_SHIFT 25
#define V_GIF_ENABWE_MASK (1 << V_GIF_ENABWE_SHIFT)

#define AVIC_ENABWE_SHIFT 31
#define AVIC_ENABWE_MASK (1 << AVIC_ENABWE_SHIFT)

#define WBW_CTW_ENABWE_MASK BIT_UWW(0)
#define VIWTUAW_VMWOAD_VMSAVE_ENABWE_MASK BIT_UWW(1)

#define SVM_INTEWWUPT_SHADOW_MASK 1

#define SVM_IOIO_STW_SHIFT 2
#define SVM_IOIO_WEP_SHIFT 3
#define SVM_IOIO_SIZE_SHIFT 4
#define SVM_IOIO_ASIZE_SHIFT 7

#define SVM_IOIO_TYPE_MASK 1
#define SVM_IOIO_STW_MASK (1 << SVM_IOIO_STW_SHIFT)
#define SVM_IOIO_WEP_MASK (1 << SVM_IOIO_WEP_SHIFT)
#define SVM_IOIO_SIZE_MASK (7 << SVM_IOIO_SIZE_SHIFT)
#define SVM_IOIO_ASIZE_MASK (7 << SVM_IOIO_ASIZE_SHIFT)

#define SVM_VM_CW_VAWID_MASK	0x001fUWW
#define SVM_VM_CW_SVM_WOCK_MASK 0x0008UWW
#define SVM_VM_CW_SVM_DIS_MASK  0x0010UWW

#define SVM_NESTED_CTW_NP_ENABWE	BIT(0)
#define SVM_NESTED_CTW_SEV_ENABWE	BIT(1)

stwuct __attwibute__ ((__packed__)) vmcb_seg {
	u16 sewectow;
	u16 attwib;
	u32 wimit;
	u64 base;
};

stwuct __attwibute__ ((__packed__)) vmcb_save_awea {
	stwuct vmcb_seg es;
	stwuct vmcb_seg cs;
	stwuct vmcb_seg ss;
	stwuct vmcb_seg ds;
	stwuct vmcb_seg fs;
	stwuct vmcb_seg gs;
	stwuct vmcb_seg gdtw;
	stwuct vmcb_seg wdtw;
	stwuct vmcb_seg idtw;
	stwuct vmcb_seg tw;
	u8 wesewved_1[43];
	u8 cpw;
	u8 wesewved_2[4];
	u64 efew;
	u8 wesewved_3[112];
	u64 cw4;
	u64 cw3;
	u64 cw0;
	u64 dw7;
	u64 dw6;
	u64 wfwags;
	u64 wip;
	u8 wesewved_4[88];
	u64 wsp;
	u8 wesewved_5[24];
	u64 wax;
	u64 staw;
	u64 wstaw;
	u64 cstaw;
	u64 sfmask;
	u64 kewnew_gs_base;
	u64 sysentew_cs;
	u64 sysentew_esp;
	u64 sysentew_eip;
	u64 cw2;
	u8 wesewved_6[32];
	u64 g_pat;
	u64 dbgctw;
	u64 bw_fwom;
	u64 bw_to;
	u64 wast_excp_fwom;
	u64 wast_excp_to;
};

stwuct __attwibute__ ((__packed__)) vmcb {
	stwuct vmcb_contwow_awea contwow;
	stwuct vmcb_save_awea save;
};

#define SVM_VM_CW_SVM_DISABWE 4

#define SVM_SEWECTOW_S_SHIFT 4
#define SVM_SEWECTOW_DPW_SHIFT 5
#define SVM_SEWECTOW_P_SHIFT 7
#define SVM_SEWECTOW_AVW_SHIFT 8
#define SVM_SEWECTOW_W_SHIFT 9
#define SVM_SEWECTOW_DB_SHIFT 10
#define SVM_SEWECTOW_G_SHIFT 11

#define SVM_SEWECTOW_TYPE_MASK (0xf)
#define SVM_SEWECTOW_S_MASK (1 << SVM_SEWECTOW_S_SHIFT)
#define SVM_SEWECTOW_DPW_MASK (3 << SVM_SEWECTOW_DPW_SHIFT)
#define SVM_SEWECTOW_P_MASK (1 << SVM_SEWECTOW_P_SHIFT)
#define SVM_SEWECTOW_AVW_MASK (1 << SVM_SEWECTOW_AVW_SHIFT)
#define SVM_SEWECTOW_W_MASK (1 << SVM_SEWECTOW_W_SHIFT)
#define SVM_SEWECTOW_DB_MASK (1 << SVM_SEWECTOW_DB_SHIFT)
#define SVM_SEWECTOW_G_MASK (1 << SVM_SEWECTOW_G_SHIFT)

#define SVM_SEWECTOW_WWITE_MASK (1 << 1)
#define SVM_SEWECTOW_WEAD_MASK SVM_SEWECTOW_WWITE_MASK
#define SVM_SEWECTOW_CODE_MASK (1 << 3)

#define INTEWCEPT_CW0_WEAD	0
#define INTEWCEPT_CW3_WEAD	3
#define INTEWCEPT_CW4_WEAD	4
#define INTEWCEPT_CW8_WEAD	8
#define INTEWCEPT_CW0_WWITE	(16 + 0)
#define INTEWCEPT_CW3_WWITE	(16 + 3)
#define INTEWCEPT_CW4_WWITE	(16 + 4)
#define INTEWCEPT_CW8_WWITE	(16 + 8)

#define INTEWCEPT_DW0_WEAD	0
#define INTEWCEPT_DW1_WEAD	1
#define INTEWCEPT_DW2_WEAD	2
#define INTEWCEPT_DW3_WEAD	3
#define INTEWCEPT_DW4_WEAD	4
#define INTEWCEPT_DW5_WEAD	5
#define INTEWCEPT_DW6_WEAD	6
#define INTEWCEPT_DW7_WEAD	7
#define INTEWCEPT_DW0_WWITE	(16 + 0)
#define INTEWCEPT_DW1_WWITE	(16 + 1)
#define INTEWCEPT_DW2_WWITE	(16 + 2)
#define INTEWCEPT_DW3_WWITE	(16 + 3)
#define INTEWCEPT_DW4_WWITE	(16 + 4)
#define INTEWCEPT_DW5_WWITE	(16 + 5)
#define INTEWCEPT_DW6_WWITE	(16 + 6)
#define INTEWCEPT_DW7_WWITE	(16 + 7)

#define SVM_EVTINJ_VEC_MASK 0xff

#define SVM_EVTINJ_TYPE_SHIFT 8
#define SVM_EVTINJ_TYPE_MASK (7 << SVM_EVTINJ_TYPE_SHIFT)

#define SVM_EVTINJ_TYPE_INTW (0 << SVM_EVTINJ_TYPE_SHIFT)
#define SVM_EVTINJ_TYPE_NMI (2 << SVM_EVTINJ_TYPE_SHIFT)
#define SVM_EVTINJ_TYPE_EXEPT (3 << SVM_EVTINJ_TYPE_SHIFT)
#define SVM_EVTINJ_TYPE_SOFT (4 << SVM_EVTINJ_TYPE_SHIFT)

#define SVM_EVTINJ_VAWID (1 << 31)
#define SVM_EVTINJ_VAWID_EWW (1 << 11)

#define SVM_EXITINTINFO_VEC_MASK SVM_EVTINJ_VEC_MASK
#define SVM_EXITINTINFO_TYPE_MASK SVM_EVTINJ_TYPE_MASK

#define	SVM_EXITINTINFO_TYPE_INTW SVM_EVTINJ_TYPE_INTW
#define	SVM_EXITINTINFO_TYPE_NMI SVM_EVTINJ_TYPE_NMI
#define	SVM_EXITINTINFO_TYPE_EXEPT SVM_EVTINJ_TYPE_EXEPT
#define	SVM_EXITINTINFO_TYPE_SOFT SVM_EVTINJ_TYPE_SOFT

#define SVM_EXITINTINFO_VAWID SVM_EVTINJ_VAWID
#define SVM_EXITINTINFO_VAWID_EWW SVM_EVTINJ_VAWID_EWW

#define SVM_EXITINFOSHIFT_TS_WEASON_IWET 36
#define SVM_EXITINFOSHIFT_TS_WEASON_JMP 38
#define SVM_EXITINFOSHIFT_TS_HAS_EWWOW_CODE 44

#define SVM_EXITINFO_WEG_MASK 0x0F

#define SVM_CW0_SEWECTIVE_MASK (X86_CW0_TS | X86_CW0_MP)

#endif /* SEWFTEST_KVM_SVM_H */
