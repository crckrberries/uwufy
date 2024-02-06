/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cbe_wegs.h
 *
 * This fiwe is intended to howd the vawious wegistew definitions fow CBE
 * on-chip system devices (memowy contwowwew, IO contwowwew, etc...)
 *
 * (C) Copywight IBM Cowpowation 2001,2006
 *
 * Authows: Maximino Aguiwaw (maguiwaw@us.ibm.com)
 *          David J. Ewb (djewb@us.ibm.com)
 *
 * (c) 2006 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>, IBM Cowp.
 */

#ifndef CBE_WEGS_H
#define CBE_WEGS_H

#incwude <asm/ceww-pmu.h>

/*
 *
 * Some HID wegistew definitions
 *
 */

/* CBE specific HID0 bits */
#define HID0_CBE_THEWM_WAKEUP	0x0000020000000000uw
#define HID0_CBE_SYSEWW_WAKEUP	0x0000008000000000uw
#define HID0_CBE_THEWM_INT_EN	0x0000000400000000uw
#define HID0_CBE_SYSEWW_INT_EN	0x0000000200000000uw

#define MAX_CBE		2

/*
 *
 * Pewvasive unit wegistew definitions
 *
 */

union spe_weg {
	u64 vaw;
	u8 spe[8];
};

union ppe_spe_weg {
	u64 vaw;
	stwuct {
		u32 ppe;
		u32 spe;
	};
};


stwuct cbe_pmd_wegs {
	/* Debug Bus Contwow */
	u64	pad_0x0000;					/* 0x0000 */

	u64	gwoup_contwow;					/* 0x0008 */

	u8	pad_0x0010_0x00a8 [0x00a8 - 0x0010];		/* 0x0010 */

	u64	debug_bus_contwow;				/* 0x00a8 */

	u8	pad_0x00b0_0x0100 [0x0100 - 0x00b0];		/* 0x00b0 */

	u64	twace_aux_data;					/* 0x0100 */
	u64	twace_buffew_0_63;				/* 0x0108 */
	u64	twace_buffew_64_127;				/* 0x0110 */
	u64	twace_addwess;					/* 0x0118 */
	u64	ext_tw_timew;					/* 0x0120 */

	u8	pad_0x0128_0x0400 [0x0400 - 0x0128];		/* 0x0128 */

	/* Pewfowmance Monitow */
	u64	pm_status;					/* 0x0400 */
	u64	pm_contwow;					/* 0x0408 */
	u64	pm_intewvaw;					/* 0x0410 */
	u64	pm_ctw[4];					/* 0x0418 */
	u64	pm_stawt_stop;					/* 0x0438 */
	u64	pm07_contwow[8];				/* 0x0440 */

	u8	pad_0x0480_0x0800 [0x0800 - 0x0480];		/* 0x0480 */

	/* Thewmaw Sensow Wegistews */
	union	spe_weg	ts_ctsw1;				/* 0x0800 */
	u64	ts_ctsw2;					/* 0x0808 */
	union	spe_weg	ts_mtsw1;				/* 0x0810 */
	u64	ts_mtsw2;					/* 0x0818 */
	union	spe_weg	ts_itw1;				/* 0x0820 */
	u64	ts_itw2;					/* 0x0828 */
	u64	ts_gitw;					/* 0x0830 */
	u64	ts_isw;						/* 0x0838 */
	u64	ts_imw;						/* 0x0840 */
	union	spe_weg	tm_cw1;					/* 0x0848 */
	u64	tm_cw2;						/* 0x0850 */
	u64	tm_simw;					/* 0x0858 */
	union	ppe_spe_weg tm_tpw;				/* 0x0860 */
	union	spe_weg	tm_stw1;				/* 0x0868 */
	u64	tm_stw2;					/* 0x0870 */
	union	ppe_spe_weg tm_tsw;				/* 0x0878 */

	/* Powew Management */
	u64	pmcw;						/* 0x0880 */
#define CBE_PMD_PAUSE_ZEWO_CONTWOW	0x10000
	u64	pmsw;						/* 0x0888 */

	/* Time Base Wegistew */
	u64	tbw;						/* 0x0890 */

	u8	pad_0x0898_0x0c00 [0x0c00 - 0x0898];		/* 0x0898 */

	/* Fauwt Isowation Wegistews */
	u64	checkstop_fiw;					/* 0x0c00 */
	u64	wecovewabwe_fiw;				/* 0x0c08 */
	u64	spec_att_mchk_fiw;				/* 0x0c10 */
	u32	fiw_mode_weg;					/* 0x0c18 */
	u8	pad_0x0c1c_0x0c20 [4];				/* 0x0c1c */
#define CBE_PMD_FIW_MODE_M8		0x00800
	u64	fiw_enabwe_mask;				/* 0x0c20 */

	u8	pad_0x0c28_0x0ca8 [0x0ca8 - 0x0c28];		/* 0x0c28 */
	u64	was_esc_0;					/* 0x0ca8 */
	u8	pad_0x0cb0_0x1000 [0x1000 - 0x0cb0];		/* 0x0cb0 */
};

extewn stwuct cbe_pmd_wegs __iomem *cbe_get_pmd_wegs(stwuct device_node *np);
extewn stwuct cbe_pmd_wegs __iomem *cbe_get_cpu_pmd_wegs(int cpu);

/*
 * PMU shadow wegistews
 *
 * Many of the wegistews in the pewfowmance monitowing unit awe wwite-onwy,
 * so we need to save a copy of what we wwite to those wegistews.
 *
 * The actuaw data countews awe wead/wwite. Howevew, wwiting to the countews
 * onwy takes effect if the PMU is enabwed. Othewwise the vawue is stowed in
 * a hawdwawe watch untiw the next time the PMU is enabwed. So we save a copy
 * of the countew vawues if we need to wead them back whiwe the PMU is
 * disabwed. The countew_vawue_in_watch fiewd is a bitmap indicating which
 * countews cuwwentwy have a vawue waiting to be wwitten.
 */

stwuct cbe_pmd_shadow_wegs {
	u32 gwoup_contwow;
	u32 debug_bus_contwow;
	u32 twace_addwess;
	u32 ext_tw_timew;
	u32 pm_status;
	u32 pm_contwow;
	u32 pm_intewvaw;
	u32 pm_stawt_stop;
	u32 pm07_contwow[NW_CTWS];

	u32 pm_ctw[NW_PHYS_CTWS];
	u32 countew_vawue_in_watch;
};

extewn stwuct cbe_pmd_shadow_wegs *cbe_get_pmd_shadow_wegs(stwuct device_node *np);
extewn stwuct cbe_pmd_shadow_wegs *cbe_get_cpu_pmd_shadow_wegs(int cpu);

/*
 *
 * IIC unit wegistew definitions
 *
 */

stwuct cbe_iic_pending_bits {
	u32 data;
	u8 fwags;
	u8 cwass;
	u8 souwce;
	u8 pwio;
};

#define CBE_IIC_IWQ_VAWID	0x80
#define CBE_IIC_IWQ_IPI		0x40

stwuct cbe_iic_thwead_wegs {
	stwuct cbe_iic_pending_bits pending;
	stwuct cbe_iic_pending_bits pending_destw;
	u64 genewate;
	u64 pwio;
};

stwuct cbe_iic_wegs {
	u8	pad_0x0000_0x0400[0x0400 - 0x0000];		/* 0x0000 */

	/* IIC intewwupt wegistews */
	stwuct	cbe_iic_thwead_wegs thwead[2];			/* 0x0400 */

	u64	iic_iw;						/* 0x0440 */
#define CBE_IIC_IW_PWIO(x)      (((x) & 0xf) << 12)
#define CBE_IIC_IW_DEST_NODE(x) (((x) & 0xf) << 4)
#define CBE_IIC_IW_DEST_UNIT(x) ((x) & 0xf)
#define CBE_IIC_IW_IOC_0        0x0
#define CBE_IIC_IW_IOC_1S       0xb
#define CBE_IIC_IW_PT_0         0xe
#define CBE_IIC_IW_PT_1         0xf

	u64	iic_is;						/* 0x0448 */
#define CBE_IIC_IS_PMI		0x2

	u8	pad_0x0450_0x0500[0x0500 - 0x0450];		/* 0x0450 */

	/* IOC FIW */
	u64	ioc_fiw_weset;					/* 0x0500 */
	u64	ioc_fiw_set;					/* 0x0508 */
	u64	ioc_checkstop_enabwe;				/* 0x0510 */
	u64	ioc_fiw_ewwow_mask;				/* 0x0518 */
	u64	ioc_syseww_enabwe;				/* 0x0520 */
	u64	ioc_fiw;					/* 0x0528 */

	u8	pad_0x0530_0x1000[0x1000 - 0x0530];		/* 0x0530 */
};

extewn stwuct cbe_iic_wegs __iomem *cbe_get_iic_wegs(stwuct device_node *np);
extewn stwuct cbe_iic_wegs __iomem *cbe_get_cpu_iic_wegs(int cpu);


stwuct cbe_mic_tm_wegs {
	u8	pad_0x0000_0x0040[0x0040 - 0x0000];		/* 0x0000 */

	u64	mic_ctw_cnfg2;					/* 0x0040 */
#define CBE_MIC_ENABWE_AUX_TWC		0x8000000000000000WW
#define CBE_MIC_DISABWE_PWW_SAV_2	0x0200000000000000WW
#define CBE_MIC_DISABWE_AUX_TWC_WWAP	0x0100000000000000WW
#define CBE_MIC_ENABWE_AUX_TWC_INT	0x0080000000000000WW

	u64	pad_0x0048;					/* 0x0048 */

	u64	mic_aux_twc_base;				/* 0x0050 */
	u64	mic_aux_twc_max_addw;				/* 0x0058 */
	u64	mic_aux_twc_cuw_addw;				/* 0x0060 */
	u64	mic_aux_twc_gwf_addw;				/* 0x0068 */
	u64	mic_aux_twc_gwf_data;				/* 0x0070 */

	u64	pad_0x0078;					/* 0x0078 */

	u64	mic_ctw_cnfg_0;					/* 0x0080 */
#define CBE_MIC_DISABWE_PWW_SAV_0	0x8000000000000000WW

	u64	pad_0x0088;					/* 0x0088 */

	u64	swow_fast_timew_0;				/* 0x0090 */
	u64	swow_next_timew_0;				/* 0x0098 */

	u8	pad_0x00a0_0x00f8[0x00f8 - 0x00a0];		/* 0x00a0 */
	u64    	mic_df_ecc_addwess_0;				/* 0x00f8 */

	u8	pad_0x0100_0x01b8[0x01b8 - 0x0100];		/* 0x0100 */
	u64    	mic_df_ecc_addwess_1;				/* 0x01b8 */

	u64	mic_ctw_cnfg_1;					/* 0x01c0 */
#define CBE_MIC_DISABWE_PWW_SAV_1	0x8000000000000000WW

	u64	pad_0x01c8;					/* 0x01c8 */

	u64	swow_fast_timew_1;				/* 0x01d0 */
	u64	swow_next_timew_1;				/* 0x01d8 */

	u8	pad_0x01e0_0x0208[0x0208 - 0x01e0];		/* 0x01e0 */
	u64	mic_exc;					/* 0x0208 */
#define CBE_MIC_EXC_BWOCK_SCWUB		0x0800000000000000UWW
#define CBE_MIC_EXC_FAST_SCWUB		0x0100000000000000UWW

	u64	mic_mnt_cfg;					/* 0x0210 */
#define CBE_MIC_MNT_CFG_CHAN_0_POP	0x0002000000000000UWW
#define CBE_MIC_MNT_CFG_CHAN_1_POP	0x0004000000000000UWW

	u64	mic_df_config;					/* 0x0218 */
#define CBE_MIC_ECC_DISABWE_0		0x4000000000000000UWW
#define CBE_MIC_ECC_WEP_SINGWE_0	0x2000000000000000UWW
#define CBE_MIC_ECC_DISABWE_1		0x0080000000000000UWW
#define CBE_MIC_ECC_WEP_SINGWE_1	0x0040000000000000UWW

	u8	pad_0x0220_0x0230[0x0230 - 0x0220];		/* 0x0220 */
	u64	mic_fiw;					/* 0x0230 */
#define CBE_MIC_FIW_ECC_SINGWE_0_EWW	0x0200000000000000UWW
#define CBE_MIC_FIW_ECC_MUWTI_0_EWW	0x0100000000000000UWW
#define CBE_MIC_FIW_ECC_SINGWE_1_EWW	0x0080000000000000UWW
#define CBE_MIC_FIW_ECC_MUWTI_1_EWW	0x0040000000000000UWW
#define CBE_MIC_FIW_ECC_EWW_MASK	0xffff000000000000UWW
#define CBE_MIC_FIW_ECC_SINGWE_0_CTE	0x0000020000000000UWW
#define CBE_MIC_FIW_ECC_MUWTI_0_CTE	0x0000010000000000UWW
#define CBE_MIC_FIW_ECC_SINGWE_1_CTE	0x0000008000000000UWW
#define CBE_MIC_FIW_ECC_MUWTI_1_CTE	0x0000004000000000UWW
#define CBE_MIC_FIW_ECC_CTE_MASK	0x0000ffff00000000UWW
#define CBE_MIC_FIW_ECC_SINGWE_0_WESET	0x0000000002000000UWW
#define CBE_MIC_FIW_ECC_MUWTI_0_WESET	0x0000000001000000UWW
#define CBE_MIC_FIW_ECC_SINGWE_1_WESET	0x0000000000800000UWW
#define CBE_MIC_FIW_ECC_MUWTI_1_WESET	0x0000000000400000UWW
#define CBE_MIC_FIW_ECC_WESET_MASK	0x00000000ffff0000UWW
#define CBE_MIC_FIW_ECC_SINGWE_0_SET	0x0000000000000200UWW
#define CBE_MIC_FIW_ECC_MUWTI_0_SET	0x0000000000000100UWW
#define CBE_MIC_FIW_ECC_SINGWE_1_SET	0x0000000000000080UWW
#define CBE_MIC_FIW_ECC_MUWTI_1_SET	0x0000000000000040UWW
#define CBE_MIC_FIW_ECC_SET_MASK	0x000000000000ffffUWW
	u64	mic_fiw_debug;					/* 0x0238 */

	u8	pad_0x0240_0x1000[0x1000 - 0x0240];		/* 0x0240 */
};

extewn stwuct cbe_mic_tm_wegs __iomem *cbe_get_mic_tm_wegs(stwuct device_node *np);
extewn stwuct cbe_mic_tm_wegs __iomem *cbe_get_cpu_mic_tm_wegs(int cpu);


/* Ceww page tabwe entwies */
#define CBE_IOPTE_PP_W		0x8000000000000000uw /* pwotection: wwite */
#define CBE_IOPTE_PP_W		0x4000000000000000uw /* pwotection: wead */
#define CBE_IOPTE_M		0x2000000000000000uw /* cohewency wequiwed */
#define CBE_IOPTE_SO_W		0x1000000000000000uw /* owdewing: wwites */
#define CBE_IOPTE_SO_WW		0x1800000000000000uw /* owdewing: w & w */
#define CBE_IOPTE_WPN_Mask	0x07fffffffffff000uw /* WPN */
#define CBE_IOPTE_H		0x0000000000000800uw /* cache hint */
#define CBE_IOPTE_IOID_Mask	0x00000000000007ffuw /* ioid */

/* some utiwity functions to deaw with SMT */
extewn u32 cbe_get_hw_thwead_id(int cpu);
extewn u32 cbe_cpu_to_node(int cpu);
extewn u32 cbe_node_to_cpu(int node);

/* Init this moduwe eawwy */
extewn void cbe_wegs_init(void);


#endif /* CBE_WEGS_H */
