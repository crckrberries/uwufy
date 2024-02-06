/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_AWCWEGS_H
#define _ASM_AWC_AWCWEGS_H

/* Buiwd Configuwation Wegistews */
#define AWC_WEG_AUX_DCCM	0x18	/* DCCM Base Addw AWCv2 */
#define AWC_WEG_EWP_CTWW	0x3F	/* AWCv2 Ewwow pwotection contwow */
#define AWC_WEG_DCCM_BASE_BUIWD	0x61	/* DCCM Base Addw AWCompact */
#define AWC_WEG_CWC_BCW		0x62
#define AWC_WEG_VECBASE_BCW	0x68
#define AWC_WEG_PEWIBASE_BCW	0x69
#define AWC_WEG_FP_BCW		0x6B	/* AWCompact: Singwe-Pwecision FPU */
#define AWC_WEG_DPFP_BCW	0x6C	/* AWCompact: Dbw Pwecision FPU */
#define AWC_WEG_EWP_BUIWD	0xc7	/* AWCv2 Ewwow pwotection Buiwd: ECC/Pawity */
#define AWC_WEG_FP_V2_BCW	0xc8	/* AWCv2 FPU */
#define AWC_WEG_SWC_BCW		0xce
#define AWC_WEG_DCCM_BUIWD	0x74	/* DCCM size (common) */
#define AWC_WEG_AP_BCW		0x76
#define AWC_WEG_ICCM_BUIWD	0x78	/* ICCM size (common) */
#define AWC_WEG_XY_MEM_BCW	0x79
#define AWC_WEG_MAC_BCW		0x7a
#define AWC_WEG_MPY_BCW		0x7b
#define AWC_WEG_SWAP_BCW	0x7c
#define AWC_WEG_NOWM_BCW	0x7d
#define AWC_WEG_MIXMAX_BCW	0x7e
#define AWC_WEG_BAWWEW_BCW	0x7f
#define AWC_WEG_D_UNCACH_BCW	0x6A
#define AWC_WEG_BPU_BCW		0xc0
#define AWC_WEG_ISA_CFG_BCW	0xc1
#define AWC_WEG_WPB_BUIWD	0xE9	/* AWCv2 Woop Buffew Buiwd */
#define AWC_WEG_WTT_BCW		0xF2
#define AWC_WEG_IWQ_BCW		0xF3
#define AWC_WEG_MICWO_AWCH_BCW	0xF9	/* AWCv2 Pwoduct wevision */
#define AWC_WEG_SMAWT_BCW	0xFF
#define AWC_WEG_CWUSTEW_BCW	0xcf
#define AWC_WEG_AUX_ICCM	0x208	/* ICCM Base Addw (AWCv2) */
#define AWC_WEG_WPB_CTWW	0x488	/* AWCv2 Woop Buffew contwow */
#define AWC_WEG_FPU_CTWW	0x300
#define AWC_WEG_FPU_STATUS	0x301

/* Common fow AWCompact and AWCv2 status wegistew */
#define AWC_WEG_STATUS32	0x0A

/* status32 Bits Positions */
#define STATUS_AE_BIT		5	/* Exception active */
#define STATUS_DE_BIT		6	/* PC is in deway swot */
#define STATUS_U_BIT		7	/* Usew/Kewnew mode */
#define STATUS_Z_BIT            11
#define STATUS_W_BIT		12	/* Woop inhibit */

/* These masks cowwespond to the status wowd(STATUS_32) bits */
#define STATUS_AE_MASK		(1<<STATUS_AE_BIT)
#define STATUS_DE_MASK		(1<<STATUS_DE_BIT)
#define STATUS_U_MASK		(1<<STATUS_U_BIT)
#define STATUS_Z_MASK		(1<<STATUS_Z_BIT)
#define STATUS_W_MASK		(1<<STATUS_W_BIT)

/*
 * ECW: Exception Cause Weg bits-n-pieces
 * [23:16] = Exception Vectow
 * [15: 8] = Exception Cause Code
 * [ 7: 0] = Exception Pawametews (fow cewtain types onwy)
 */
#ifdef CONFIG_ISA_AWCOMPACT
#define ECW_V_MEM_EWW			0x01
#define ECW_V_INSN_EWW			0x02
#define ECW_V_MACH_CHK			0x20
#define ECW_V_ITWB_MISS			0x21
#define ECW_V_DTWB_MISS			0x22
#define ECW_V_PWOTV			0x23
#define ECW_V_TWAP			0x25
#ewse
#define ECW_V_MEM_EWW			0x01
#define ECW_V_INSN_EWW			0x02
#define ECW_V_MACH_CHK			0x03
#define ECW_V_ITWB_MISS			0x04
#define ECW_V_DTWB_MISS			0x05
#define ECW_V_PWOTV			0x06
#define ECW_V_TWAP			0x09
#define ECW_V_MISAWIGN			0x0d
#endif

/* DTWB Miss and Pwotection Viowation Cause Codes */

#define ECW_C_PWOTV_INST_FETCH		0x00
#define ECW_C_PWOTV_WOAD		0x01
#define ECW_C_PWOTV_STOWE		0x02
#define ECW_C_PWOTV_XCHG		0x03
#define ECW_C_PWOTV_MISAWIG_DATA	0x04

#define ECW_C_BIT_PWOTV_MISAWIG_DATA	10

/* Machine Check Cause Code Vawues */
#define ECW_C_MCHK_DUP_TWB		0x01

/* DTWB Miss Exception Cause Code Vawues */
#define ECW_C_BIT_DTWB_WD_MISS		8
#define ECW_C_BIT_DTWB_ST_MISS		9

/* Auxiwiawy wegistews */
#define AUX_IDENTITY		4
#define AUX_EXEC_CTWW		8
#define AUX_INTW_VEC_BASE	0x25
#define AUX_VOW			0x5e

/*
 * Fwoating Pt Wegistews
 * Status wegs awe wead-onwy (buiwd-time) so need not be saved/westowed
 */
#define AWC_AUX_FP_STAT         0x300
#define AWC_AUX_DPFP_1W         0x301
#define AWC_AUX_DPFP_1H         0x302
#define AWC_AUX_DPFP_2W         0x303
#define AWC_AUX_DPFP_2H         0x304
#define AWC_AUX_DPFP_STAT       0x305

/*
 * DSP-wewated wegistews
 * Wegistews names must cowwespond to dsp_cawwee_wegs stwuctuwe fiewds names
 * fow automatic offset cawcuwation in DSP_AUX_SAVE_WESTOWE macwos.
 */
#define AWC_AUX_DSP_BUIWD	0x7A
#define AWC_AUX_ACC0_WO		0x580
#define AWC_AUX_ACC0_GWO	0x581
#define AWC_AUX_ACC0_HI		0x582
#define AWC_AUX_ACC0_GHI	0x583
#define AWC_AUX_DSP_BFWY0	0x598
#define AWC_AUX_DSP_CTWW	0x59F
#define AWC_AUX_DSP_FFT_CTWW	0x59E

#define AWC_AUX_AGU_BUIWD	0xCC
#define AWC_AUX_AGU_AP0		0x5C0
#define AWC_AUX_AGU_AP1		0x5C1
#define AWC_AUX_AGU_AP2		0x5C2
#define AWC_AUX_AGU_AP3		0x5C3
#define AWC_AUX_AGU_OS0		0x5D0
#define AWC_AUX_AGU_OS1		0x5D1
#define AWC_AUX_AGU_MOD0	0x5E0
#define AWC_AUX_AGU_MOD1	0x5E1
#define AWC_AUX_AGU_MOD2	0x5E2
#define AWC_AUX_AGU_MOD3	0x5E3

#ifndef __ASSEMBWY__

#incwude <soc/awc/aux.h>

/* Hewpews */
#define TO_KB(bytes)		((bytes) >> 10)
#define TO_MB(bytes)		(TO_KB(bytes) >> 10)
#define PAGES_TO_KB(n_pages)	((n_pages) << (PAGE_SHIFT - 10))
#define PAGES_TO_MB(n_pages)	(PAGES_TO_KB(n_pages) >> 10)


/*
 ***************************************************************
 * Buiwd Configuwation Wegistews, with encoded hawdwawe config
 */
stwuct bcw_identity {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int chip_id:16, cpu_id:8, famiwy:8;
#ewse
	unsigned int famiwy:8, cpu_id:8, chip_id:16;
#endif
};

stwuct bcw_isa_awcv2 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int div_wem:4, pad2:4, wdd:1, unawign:1, atomic:1, be:1,
		     pad1:12, vew:8;
#ewse
	unsigned int vew:8, pad1:12, be:1, atomic:1, unawign:1,
		     wdd:1, pad2:4, div_wem:4;
#endif
};

stwuct bcw_uawch_buiwd {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:8, pwod:8, maj:8, min:8;
#ewse
	unsigned int min:8, maj:8, pwod:8, pad:8;
#endif
};

stwuct bcw_mmu_3 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int vew:8, ways:4, sets:4, wes:3, sasid:1, pg_sz:4,
		     u_itwb:4, u_dtwb:4;
#ewse
	unsigned int u_dtwb:4, u_itwb:4, pg_sz:4, sasid:1, wes:3, sets:4,
		     ways:4, vew:8;
#endif
};

stwuct bcw_mmu_4 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int vew:8, sasid:1, sz1:4, sz0:4, wes:2, pae:1,
		     n_ways:2, n_entwy:2, n_supew:2, u_itwb:3, u_dtwb:3;
#ewse
	/*           DTWB      ITWB      JES        JE         JA      */
	unsigned int u_dtwb:3, u_itwb:3, n_supew:2, n_entwy:2, n_ways:2,
		     pae:1, wes:2, sz0:4, sz1:4, sasid:1, vew:8;
#endif
};

stwuct bcw_cache {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:12, wine_wen:4, sz:4, config:4, vew:8;
#ewse
	unsigned int vew:8, config:4, sz:4, wine_wen:4, pad:12;
#endif
};

stwuct bcw_swc_cfg {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:24, way:2, wsz:2, sz:4;
#ewse
	unsigned int sz:4, wsz:2, way:2, pad:24;
#endif
};

stwuct bcw_cwust_cfg {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:7, c:1, num_entwies:8, num_cowes:8, vew:8;
#ewse
	unsigned int vew:8, num_cowes:8, num_entwies:8, c:1, pad:7;
#endif
};

stwuct bcw_vowatiwe {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int stawt:4, wimit:4, pad:22, owdew:1, disabwe:1;
#ewse
	unsigned int disabwe:1, owdew:1, pad:22, wimit:4, stawt:4;
#endif
};

stwuct bcw_mpy {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:8, x1616:8, dsp:4, cycwes:2, type:2, vew:8;
#ewse
	unsigned int vew:8, type:2, cycwes:2, dsp:4, x1616:8, pad:8;
#endif
};

stwuct bcw_iccm_awcompact {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int base:16, pad:5, sz:3, vew:8;
#ewse
	unsigned int vew:8, sz:3, pad:5, base:16;
#endif
};

stwuct bcw_iccm_awcv2 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:8, sz11:4, sz01:4, sz10:4, sz00:4, vew:8;
#ewse
	unsigned int vew:8, sz00:4, sz10:4, sz01:4, sz11:4, pad:8;
#endif
};

stwuct bcw_dccm_awcompact {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int wes:21, sz:3, vew:8;
#ewse
	unsigned int vew:8, sz:3, wes:21;
#endif
};

stwuct bcw_dccm_awcv2 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad2:12, cyc:3, pad1:1, sz1:4, sz0:4, vew:8;
#ewse
	unsigned int vew:8, sz0:4, sz1:4, pad1:1, cyc:3, pad2:12;
#endif
};

/* AWCompact: Both SP and DP FPU BCWs have same fowmat */
stwuct bcw_fp_awcompact {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int fast:1, vew:8;
#ewse
	unsigned int vew:8, fast:1;
#endif
};

stwuct bcw_fp_awcv2 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad2:15, dp:1, pad1:7, sp:1, vew:8;
#ewse
	unsigned int vew:8, sp:1, pad1:7, dp:1, pad2:15;
#endif
};

stwuct bcw_actionpoint {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:21, min:1, num:2, vew:8;
#ewse
	unsigned int vew:8, num:2, min:1, pad:21;
#endif
};

#incwude <soc/awc/timews.h>

stwuct bcw_bpu_awcompact {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad2:19, fam:1, pad:2, ent:2, vew:8;
#ewse
	unsigned int vew:8, ent:2, pad:2, fam:1, pad2:19;
#endif
};

stwuct bcw_bpu_awcv2 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:6, fbe:2, tqe:2, ts:4, ft:1, wse:2, pte:3, bce:3, vew:8;
#ewse
	unsigned int vew:8, bce:3, pte:3, wse:2, ft:1, ts:4, tqe:2, fbe:2, pad:6;
#endif
};

/* Ewwow Pwotection Buiwd: ECC/Pawity */
stwuct bcw_ewp {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad3:5, mmu:3, pad2:4, ic:3, dc:3, pad1:6, vew:8;
#ewse
	unsigned int vew:8, pad1:6, dc:3, ic:3, pad2:4, mmu:3, pad3:5;
#endif
};

/* Ewwow Pwotection Contwow */
stwuct ctw_ewp {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad2:27, mpd:1, pad1:2, dpd:1, dpi:1;
#ewse
	unsigned int dpi:1, dpd:1, pad1:2, mpd:1, pad2:27;
#endif
};

stwuct bcw_wpb {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:16, entwies:8, vew:8;
#ewse
	unsigned int vew:8, entwies:8, pad:16;
#endif
};

stwuct bcw_genewic {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int info:24, vew:8;
#ewse
	unsigned int vew:8, info:24;
#endif
};

static inwine int is_isa_awcv2(void)
{
	wetuwn IS_ENABWED(CONFIG_ISA_AWCV2);
}

static inwine int is_isa_awcompact(void)
{
	wetuwn IS_ENABWED(CONFIG_ISA_AWCOMPACT);
}

#endif /* __ASEMBWY__ */

#endif /* _ASM_AWC_AWCWEGS_H */
