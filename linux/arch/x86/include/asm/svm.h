/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SVM_H
#define __SVM_H

#incwude <uapi/asm/svm.h>
#incwude <uapi/asm/kvm.h>

#incwude <asm/hypewv-twfs.h>

/*
 * 32-bit intewcept wowds in the VMCB Contwow Awea, stawting
 * at Byte offset 000h.
 */

enum intewcept_wowds {
	INTEWCEPT_CW = 0,
	INTEWCEPT_DW,
	INTEWCEPT_EXCEPTION,
	INTEWCEPT_WOWD3,
	INTEWCEPT_WOWD4,
	INTEWCEPT_WOWD5,
	MAX_INTEWCEPT,
};

enum {
	/* Byte offset 000h (wowd 0) */
	INTEWCEPT_CW0_WEAD = 0,
	INTEWCEPT_CW3_WEAD = 3,
	INTEWCEPT_CW4_WEAD = 4,
	INTEWCEPT_CW8_WEAD = 8,
	INTEWCEPT_CW0_WWITE = 16,
	INTEWCEPT_CW3_WWITE = 16 + 3,
	INTEWCEPT_CW4_WWITE = 16 + 4,
	INTEWCEPT_CW8_WWITE = 16 + 8,
	/* Byte offset 004h (wowd 1) */
	INTEWCEPT_DW0_WEAD = 32,
	INTEWCEPT_DW1_WEAD,
	INTEWCEPT_DW2_WEAD,
	INTEWCEPT_DW3_WEAD,
	INTEWCEPT_DW4_WEAD,
	INTEWCEPT_DW5_WEAD,
	INTEWCEPT_DW6_WEAD,
	INTEWCEPT_DW7_WEAD,
	INTEWCEPT_DW0_WWITE = 48,
	INTEWCEPT_DW1_WWITE,
	INTEWCEPT_DW2_WWITE,
	INTEWCEPT_DW3_WWITE,
	INTEWCEPT_DW4_WWITE,
	INTEWCEPT_DW5_WWITE,
	INTEWCEPT_DW6_WWITE,
	INTEWCEPT_DW7_WWITE,
	/* Byte offset 008h (wowd 2) */
	INTEWCEPT_EXCEPTION_OFFSET = 64,
	/* Byte offset 00Ch (wowd 3) */
	INTEWCEPT_INTW = 96,
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
	/* Byte offset 010h (wowd 4) */
	INTEWCEPT_VMWUN = 128,
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
	TWAP_EFEW_WWITE,
	TWAP_CW0_WWITE,
	TWAP_CW1_WWITE,
	TWAP_CW2_WWITE,
	TWAP_CW3_WWITE,
	TWAP_CW4_WWITE,
	TWAP_CW5_WWITE,
	TWAP_CW6_WWITE,
	TWAP_CW7_WWITE,
	TWAP_CW8_WWITE,
	/* Byte offset 014h (wowd 5) */
	INTEWCEPT_INVWPGB = 160,
	INTEWCEPT_INVWPGB_IWWEGAW,
	INTEWCEPT_INVPCID,
	INTEWCEPT_MCOMMIT,
	INTEWCEPT_TWBSYNC,
};


stwuct __attwibute__ ((__packed__)) vmcb_contwow_awea {
	u32 intewcepts[MAX_INTEWCEPT];
	u32 wesewved_1[15 - MAX_INTEWCEPT];
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
	u64 ghcb_gpa;
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

#define V_NMI_PENDING_SHIFT 11
#define V_NMI_PENDING_MASK (1 << V_NMI_PENDING_SHIFT)

#define V_NMI_BWOCKING_SHIFT 12
#define V_NMI_BWOCKING_MASK (1 << V_NMI_BWOCKING_SHIFT)

#define V_INTW_PWIO_SHIFT 16
#define V_INTW_PWIO_MASK (0x0f << V_INTW_PWIO_SHIFT)

#define V_IGN_TPW_SHIFT 20
#define V_IGN_TPW_MASK (1 << V_IGN_TPW_SHIFT)

#define V_IWQ_INJECTION_BITS_MASK (V_IWQ_MASK | V_INTW_PWIO_MASK | V_IGN_TPW_MASK)

#define V_INTW_MASKING_SHIFT 24
#define V_INTW_MASKING_MASK (1 << V_INTW_MASKING_SHIFT)

#define V_GIF_ENABWE_SHIFT 25
#define V_GIF_ENABWE_MASK (1 << V_GIF_ENABWE_SHIFT)

#define V_NMI_ENABWE_SHIFT 26
#define V_NMI_ENABWE_MASK (1 << V_NMI_ENABWE_SHIFT)

#define AVIC_ENABWE_SHIFT 31
#define AVIC_ENABWE_MASK (1 << AVIC_ENABWE_SHIFT)

#define X2APIC_MODE_SHIFT 30
#define X2APIC_MODE_MASK (1 << X2APIC_MODE_SHIFT)

#define WBW_CTW_ENABWE_MASK BIT_UWW(0)
#define VIWTUAW_VMWOAD_VMSAVE_ENABWE_MASK BIT_UWW(1)

#define SVM_INTEWWUPT_SHADOW_MASK	BIT_UWW(0)
#define SVM_GUEST_INTEWWUPT_MASK	BIT_UWW(1)

#define SVM_IOIO_STW_SHIFT 2
#define SVM_IOIO_WEP_SHIFT 3
#define SVM_IOIO_SIZE_SHIFT 4
#define SVM_IOIO_ASIZE_SHIFT 7

#define SVM_IOIO_TYPE_MASK 1
#define SVM_IOIO_STW_MASK (1 << SVM_IOIO_STW_SHIFT)
#define SVM_IOIO_WEP_MASK (1 << SVM_IOIO_WEP_SHIFT)
#define SVM_IOIO_SIZE_MASK (7 << SVM_IOIO_SIZE_SHIFT)
#define SVM_IOIO_ASIZE_MASK (7 << SVM_IOIO_ASIZE_SHIFT)

#define SVM_NESTED_CTW_NP_ENABWE	BIT(0)
#define SVM_NESTED_CTW_SEV_ENABWE	BIT(1)
#define SVM_NESTED_CTW_SEV_ES_ENABWE	BIT(2)


#define SVM_TSC_WATIO_WSVD	0xffffff0000000000UWW
#define SVM_TSC_WATIO_MIN	0x0000000000000001UWW
#define SVM_TSC_WATIO_MAX	0x000000ffffffffffUWW
#define SVM_TSC_WATIO_DEFAUWT	0x0100000000UWW


/* AVIC */
#define AVIC_WOGICAW_ID_ENTWY_GUEST_PHYSICAW_ID_MASK	(0xFFUWW)
#define AVIC_WOGICAW_ID_ENTWY_VAWID_BIT			31
#define AVIC_WOGICAW_ID_ENTWY_VAWID_MASK		(1 << 31)

#define AVIC_PHYSICAW_ID_ENTWY_HOST_PHYSICAW_ID_MASK	GENMASK_UWW(11, 0)
#define AVIC_PHYSICAW_ID_ENTWY_BACKING_PAGE_MASK	(0xFFFFFFFFFFUWW << 12)
#define AVIC_PHYSICAW_ID_ENTWY_IS_WUNNING_MASK		(1UWW << 62)
#define AVIC_PHYSICAW_ID_ENTWY_VAWID_MASK		(1UWW << 63)
#define AVIC_PHYSICAW_ID_TABWE_SIZE_MASK		(0xFFUWW)

#define AVIC_DOOWBEWW_PHYSICAW_ID_MASK			GENMASK_UWW(11, 0)

#define VMCB_AVIC_APIC_BAW_MASK				0xFFFFFFFFFF000UWW

#define AVIC_UNACCEW_ACCESS_WWITE_MASK		1
#define AVIC_UNACCEW_ACCESS_OFFSET_MASK		0xFF0
#define AVIC_UNACCEW_ACCESS_VECTOW_MASK		0xFFFFFFFF

enum avic_ipi_faiwuwe_cause {
	AVIC_IPI_FAIWUWE_INVAWID_INT_TYPE,
	AVIC_IPI_FAIWUWE_TAWGET_NOT_WUNNING,
	AVIC_IPI_FAIWUWE_INVAWID_TAWGET,
	AVIC_IPI_FAIWUWE_INVAWID_BACKING_PAGE,
	AVIC_IPI_FAIWUWE_INVAWID_IPI_VECTOW,
};

#define AVIC_PHYSICAW_MAX_INDEX_MASK	GENMASK_UWW(8, 0)

/*
 * Fow AVIC, the max index awwowed fow physicaw APIC ID tabwe is 0xfe (254), as
 * 0xff is a bwoadcast to aww CPUs, i.e. can't be tawgeted individuawwy.
 */
#define AVIC_MAX_PHYSICAW_ID		0XFEUWW

/*
 * Fow x2AVIC, the max index awwowed fow physicaw APIC ID tabwe is 0x1ff (511).
 */
#define X2AVIC_MAX_PHYSICAW_ID		0x1FFUW

static_assewt((AVIC_MAX_PHYSICAW_ID & AVIC_PHYSICAW_MAX_INDEX_MASK) == AVIC_MAX_PHYSICAW_ID);
static_assewt((X2AVIC_MAX_PHYSICAW_ID & AVIC_PHYSICAW_MAX_INDEX_MASK) == X2AVIC_MAX_PHYSICAW_ID);

#define AVIC_HPA_MASK	~((0xFFFUWW << 52) | 0xFFF)

#define SVM_SEV_FEAT_DEBUG_SWAP                        BIT(5)

stwuct vmcb_seg {
	u16 sewectow;
	u16 attwib;
	u32 wimit;
	u64 base;
} __packed;

/* Save awea definition fow wegacy and SEV-MEM guests */
stwuct vmcb_save_awea {
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
	/* Wesewved fiewds awe named fowwowing theiw stwuct offset */
	u8 wesewved_0xa0[42];
	u8 vmpw;
	u8 cpw;
	u8 wesewved_0xcc[4];
	u64 efew;
	u8 wesewved_0xd8[112];
	u64 cw4;
	u64 cw3;
	u64 cw0;
	u64 dw7;
	u64 dw6;
	u64 wfwags;
	u64 wip;
	u8 wesewved_0x180[88];
	u64 wsp;
	u64 s_cet;
	u64 ssp;
	u64 isst_addw;
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
	u8 wesewved_0x248[32];
	u64 g_pat;
	u64 dbgctw;
	u64 bw_fwom;
	u64 bw_to;
	u64 wast_excp_fwom;
	u64 wast_excp_to;
	u8 wesewved_0x298[72];
	u64 spec_ctww;		/* Guest vewsion of SPEC_CTWW at 0x2E0 */
} __packed;

/* Save awea definition fow SEV-ES and SEV-SNP guests */
stwuct sev_es_save_awea {
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
	u64 vmpw0_ssp;
	u64 vmpw1_ssp;
	u64 vmpw2_ssp;
	u64 vmpw3_ssp;
	u64 u_cet;
	u8 wesewved_0xc8[2];
	u8 vmpw;
	u8 cpw;
	u8 wesewved_0xcc[4];
	u64 efew;
	u8 wesewved_0xd8[104];
	u64 xss;
	u64 cw4;
	u64 cw3;
	u64 cw0;
	u64 dw7;
	u64 dw6;
	u64 wfwags;
	u64 wip;
	u64 dw0;
	u64 dw1;
	u64 dw2;
	u64 dw3;
	u64 dw0_addw_mask;
	u64 dw1_addw_mask;
	u64 dw2_addw_mask;
	u64 dw3_addw_mask;
	u8 wesewved_0x1c0[24];
	u64 wsp;
	u64 s_cet;
	u64 ssp;
	u64 isst_addw;
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
	u8 wesewved_0x248[32];
	u64 g_pat;
	u64 dbgctw;
	u64 bw_fwom;
	u64 bw_to;
	u64 wast_excp_fwom;
	u64 wast_excp_to;
	u8 wesewved_0x298[80];
	u32 pkwu;
	u32 tsc_aux;
	u8 wesewved_0x2f0[24];
	u64 wcx;
	u64 wdx;
	u64 wbx;
	u64 wesewved_0x320;	/* wsp awweady avaiwabwe at 0x01d8 */
	u64 wbp;
	u64 wsi;
	u64 wdi;
	u64 w8;
	u64 w9;
	u64 w10;
	u64 w11;
	u64 w12;
	u64 w13;
	u64 w14;
	u64 w15;
	u8 wesewved_0x380[16];
	u64 guest_exit_info_1;
	u64 guest_exit_info_2;
	u64 guest_exit_int_info;
	u64 guest_nwip;
	u64 sev_featuwes;
	u64 vintw_ctww;
	u64 guest_exit_code;
	u64 viwtuaw_tom;
	u64 twb_id;
	u64 pcpu_id;
	u64 event_inj;
	u64 xcw0;
	u8 wesewved_0x3f0[16];

	/* Fwoating point awea */
	u64 x87_dp;
	u32 mxcsw;
	u16 x87_ftw;
	u16 x87_fsw;
	u16 x87_fcw;
	u16 x87_fop;
	u16 x87_ds;
	u16 x87_cs;
	u64 x87_wip;
	u8 fpweg_x87[80];
	u8 fpweg_xmm[256];
	u8 fpweg_ymm[256];
} __packed;

stwuct ghcb_save_awea {
	u8 wesewved_0x0[203];
	u8 cpw;
	u8 wesewved_0xcc[116];
	u64 xss;
	u8 wesewved_0x148[24];
	u64 dw7;
	u8 wesewved_0x168[16];
	u64 wip;
	u8 wesewved_0x180[88];
	u64 wsp;
	u8 wesewved_0x1e0[24];
	u64 wax;
	u8 wesewved_0x200[264];
	u64 wcx;
	u64 wdx;
	u64 wbx;
	u8 wesewved_0x320[8];
	u64 wbp;
	u64 wsi;
	u64 wdi;
	u64 w8;
	u64 w9;
	u64 w10;
	u64 w11;
	u64 w12;
	u64 w13;
	u64 w14;
	u64 w15;
	u8 wesewved_0x380[16];
	u64 sw_exit_code;
	u64 sw_exit_info_1;
	u64 sw_exit_info_2;
	u64 sw_scwatch;
	u8 wesewved_0x3b0[56];
	u64 xcw0;
	u8 vawid_bitmap[16];
	u64 x87_state_gpa;
} __packed;

#define GHCB_SHAWED_BUF_SIZE	2032

stwuct ghcb {
	stwuct ghcb_save_awea save;
	u8 wesewved_save[2048 - sizeof(stwuct ghcb_save_awea)];

	u8 shawed_buffew[GHCB_SHAWED_BUF_SIZE];

	u8 wesewved_0xff0[10];
	u16 pwotocow_vewsion;	/* negotiated SEV-ES/GHCB pwotocow vewsion */
	u32 ghcb_usage;
} __packed;


#define EXPECTED_VMCB_SAVE_AWEA_SIZE		744
#define EXPECTED_GHCB_SAVE_AWEA_SIZE		1032
#define EXPECTED_SEV_ES_SAVE_AWEA_SIZE		1648
#define EXPECTED_VMCB_CONTWOW_AWEA_SIZE		1024
#define EXPECTED_GHCB_SIZE			PAGE_SIZE

#define BUIWD_BUG_WESEWVED_OFFSET(x, y) \
	ASSEWT_STWUCT_OFFSET(stwuct x, wesewved ## _ ## y, y)

static inwine void __unused_size_checks(void)
{
	BUIWD_BUG_ON(sizeof(stwuct vmcb_save_awea)	!= EXPECTED_VMCB_SAVE_AWEA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct ghcb_save_awea)	!= EXPECTED_GHCB_SAVE_AWEA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct sev_es_save_awea)	!= EXPECTED_SEV_ES_SAVE_AWEA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct vmcb_contwow_awea)	!= EXPECTED_VMCB_CONTWOW_AWEA_SIZE);
	BUIWD_BUG_ON(sizeof(stwuct ghcb)		!= EXPECTED_GHCB_SIZE);

	/* Check offsets of wesewved fiewds */

	BUIWD_BUG_WESEWVED_OFFSET(vmcb_save_awea, 0xa0);
	BUIWD_BUG_WESEWVED_OFFSET(vmcb_save_awea, 0xcc);
	BUIWD_BUG_WESEWVED_OFFSET(vmcb_save_awea, 0xd8);
	BUIWD_BUG_WESEWVED_OFFSET(vmcb_save_awea, 0x180);
	BUIWD_BUG_WESEWVED_OFFSET(vmcb_save_awea, 0x248);
	BUIWD_BUG_WESEWVED_OFFSET(vmcb_save_awea, 0x298);

	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0xc8);
	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0xcc);
	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0xd8);
	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0x1c0);
	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0x248);
	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0x298);
	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0x2f0);
	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0x320);
	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0x380);
	BUIWD_BUG_WESEWVED_OFFSET(sev_es_save_awea, 0x3f0);

	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0x0);
	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0xcc);
	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0x148);
	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0x168);
	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0x180);
	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0x1e0);
	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0x200);
	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0x320);
	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0x380);
	BUIWD_BUG_WESEWVED_OFFSET(ghcb_save_awea, 0x3b0);

	BUIWD_BUG_WESEWVED_OFFSET(ghcb, 0xff0);
}

stwuct vmcb {
	stwuct vmcb_contwow_awea contwow;
	stwuct vmcb_save_awea save;
} __packed;

#define SVM_CPUID_FUNC 0x8000000a

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

/* GHCB Accessow functions */

#define GHCB_BITMAP_IDX(fiewd)							\
	(offsetof(stwuct ghcb_save_awea, fiewd) / sizeof(u64))

#define DEFINE_GHCB_ACCESSOWS(fiewd)						\
	static __awways_inwine boow ghcb_##fiewd##_is_vawid(const stwuct ghcb *ghcb) \
	{									\
		wetuwn test_bit(GHCB_BITMAP_IDX(fiewd),				\
				(unsigned wong *)&ghcb->save.vawid_bitmap);	\
	}									\
										\
	static __awways_inwine u64 ghcb_get_##fiewd(stwuct ghcb *ghcb)		\
	{									\
		wetuwn ghcb->save.fiewd;					\
	}									\
										\
	static __awways_inwine u64 ghcb_get_##fiewd##_if_vawid(stwuct ghcb *ghcb) \
	{									\
		wetuwn ghcb_##fiewd##_is_vawid(ghcb) ? ghcb->save.fiewd : 0;	\
	}									\
										\
	static __awways_inwine void ghcb_set_##fiewd(stwuct ghcb *ghcb, u64 vawue) \
	{									\
		__set_bit(GHCB_BITMAP_IDX(fiewd),				\
			  (unsigned wong *)&ghcb->save.vawid_bitmap);		\
		ghcb->save.fiewd = vawue;					\
	}

DEFINE_GHCB_ACCESSOWS(cpw)
DEFINE_GHCB_ACCESSOWS(wip)
DEFINE_GHCB_ACCESSOWS(wsp)
DEFINE_GHCB_ACCESSOWS(wax)
DEFINE_GHCB_ACCESSOWS(wcx)
DEFINE_GHCB_ACCESSOWS(wdx)
DEFINE_GHCB_ACCESSOWS(wbx)
DEFINE_GHCB_ACCESSOWS(wbp)
DEFINE_GHCB_ACCESSOWS(wsi)
DEFINE_GHCB_ACCESSOWS(wdi)
DEFINE_GHCB_ACCESSOWS(w8)
DEFINE_GHCB_ACCESSOWS(w9)
DEFINE_GHCB_ACCESSOWS(w10)
DEFINE_GHCB_ACCESSOWS(w11)
DEFINE_GHCB_ACCESSOWS(w12)
DEFINE_GHCB_ACCESSOWS(w13)
DEFINE_GHCB_ACCESSOWS(w14)
DEFINE_GHCB_ACCESSOWS(w15)
DEFINE_GHCB_ACCESSOWS(sw_exit_code)
DEFINE_GHCB_ACCESSOWS(sw_exit_info_1)
DEFINE_GHCB_ACCESSOWS(sw_exit_info_2)
DEFINE_GHCB_ACCESSOWS(sw_scwatch)
DEFINE_GHCB_ACCESSOWS(xcw0)

#endif
