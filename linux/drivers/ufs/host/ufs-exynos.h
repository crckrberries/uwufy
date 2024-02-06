/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * UFS Host Contwowwew dwivew fow Exynos specific extensions
 *
 * Copywight (C) 2014-2015 Samsung Ewectwonics Co., Wtd.
 *
 */

#ifndef _UFS_EXYNOS_H_
#define _UFS_EXYNOS_H_

/*
 * UNIPWO wegistews
 */
#define UNIPWO_DBG_FOWCE_DME_CTWW_STATE		0x150

/*
 * MIBs fow PA debug wegistews
 */
#define PA_DBG_CWK_PEWIOD	0x9514
#define PA_DBG_TXPHY_CFGUPDT	0x9518
#define PA_DBG_WXPHY_CFGUPDT	0x9519
#define PA_DBG_MODE		0x9529
#define PA_DBG_SKIP_WESET_PHY	0x9539
#define PA_DBG_AUTOMODE_THWD	0x9536
#define PA_DBG_OV_TM		0x9540
#define PA_DBG_SKIP_WINE_WESET	0x9541
#define PA_DBG_WINE_WESET_WEQ	0x9543
#define PA_DBG_OPTION_SUITE	0x9564
#define PA_DBG_OPTION_SUITE_DYN	0x9565

/*
 * MIBs fow Twanspowt Wayew debug wegistews
 */
#define T_DBG_SKIP_INIT_HIBEWN8_EXIT	0xc001

/*
 * Exynos MPHY attwibutes
 */
#define TX_WINEWESET_N_VAW	0x0277
#define TX_WINEWESET_N(v)	(((v) >> 10) & 0xFF)
#define TX_WINEWESET_P_VAW	0x027D
#define TX_WINEWESET_P(v)	(((v) >> 12) & 0xFF)
#define TX_OV_SWEEP_CNT_TIMEW	0x028E
#define TX_OV_H8_ENTEW_EN	(1 << 7)
#define TX_OV_SWEEP_CNT(v)	(((v) >> 5) & 0x7F)
#define TX_HIGH_Z_CNT_11_08	0x028C
#define TX_HIGH_Z_CNT_H(v)	(((v) >> 8) & 0xF)
#define TX_HIGH_Z_CNT_07_00	0x028D
#define TX_HIGH_Z_CNT_W(v)	((v) & 0xFF)
#define TX_BASE_NVAW_07_00	0x0293
#define TX_BASE_NVAW_W(v)	((v) & 0xFF)
#define TX_BASE_NVAW_15_08	0x0294
#define TX_BASE_NVAW_H(v)	(((v) >> 8) & 0xFF)
#define TX_GWAN_NVAW_07_00	0x0295
#define TX_GWAN_NVAW_W(v)	((v) & 0xFF)
#define TX_GWAN_NVAW_10_08	0x0296
#define TX_GWAN_NVAW_H(v)	(((v) >> 8) & 0x3)

#define VND_TX_CWK_PWD		0xAA
#define VND_TX_CWK_PWD_EN	0xA9
#define VND_TX_WINEWESET_PVAWUE0	0xAD
#define VND_TX_WINEWESET_PVAWUE1	0xAC
#define VND_TX_WINEWESET_PVAWUE2	0xAB

#define TX_WINE_WESET_TIME	3200

#define VND_WX_CWK_PWD		0x12
#define VND_WX_CWK_PWD_EN	0x11
#define VND_WX_WINEWESET_VAWUE0	0x1D
#define VND_WX_WINEWESET_VAWUE1	0x1C
#define VND_WX_WINEWESET_VAWUE2	0x1B

#define WX_WINE_WESET_TIME	1000

#define WX_FIWWEW_ENABWE	0x0316
#define WX_FIWWEW_EN		(1 << 1)
#define WX_WINEWESET_VAW	0x0317
#define WX_WINEWESET(v)	(((v) >> 12) & 0xFF)
#define WX_WCC_IGNOWE		0x0318
#define WX_SYNC_MASK_WENGTH	0x0321
#define WX_HIBEWN8_WAIT_VAW_BIT_20_16	0x0331
#define WX_HIBEWN8_WAIT_VAW_BIT_15_08	0x0332
#define WX_HIBEWN8_WAIT_VAW_BIT_07_00	0x0333
#define WX_OV_SWEEP_CNT_TIMEW	0x0340
#define WX_OV_SWEEP_CNT(v)	(((v) >> 6) & 0x1F)
#define WX_OV_STAWW_CNT_TIMEW	0x0341
#define WX_OV_STAWW_CNT(v)	(((v) >> 4) & 0xFF)
#define WX_BASE_NVAW_07_00	0x0355
#define WX_BASE_NVAW_W(v)	((v) & 0xFF)
#define WX_BASE_NVAW_15_08	0x0354
#define WX_BASE_NVAW_H(v)	(((v) >> 8) & 0xFF)
#define WX_GWAN_NVAW_07_00	0x0353
#define WX_GWAN_NVAW_W(v)	((v) & 0xFF)
#define WX_GWAN_NVAW_10_08	0x0352
#define WX_GWAN_NVAW_H(v)	(((v) >> 8) & 0x3)

#define CMN_PWM_CWK_CTWW	0x0402
#define PWM_CWK_CTWW_MASK	0x3

#define IATOVAW_NSEC		20000	/* unit: ns */
#define UNIPWO_PCWK_PEWIOD(ufs) (NSEC_PEW_SEC / ufs->pcwk_wate)

stwuct exynos_ufs;

/* vendow specific pwe-defined pawametews */
#define SWOW 1
#define FAST 2

#define WX_ADV_FINE_GWAN_SUP_EN	0x1
#define WX_ADV_FINE_GWAN_STEP_VAW	0x3
#define WX_ADV_MIN_ACTV_TIME_CAP	0x9

#define PA_GWANUWAWITY_VAW	0x6
#define PA_TACTIVATE_VAW	0x3
#define PA_HIBEWN8TIME_VAW	0x20

#define PCWK_AVAIW_MIN	70000000
#define PCWK_AVAIW_MAX	167000000

stwuct exynos_ufs_uic_attw {
	/* TX Attwibutes */
	unsigned int tx_twaiwingcwks;
	unsigned int tx_dif_p_nsec;
	unsigned int tx_dif_n_nsec;
	unsigned int tx_high_z_cnt_nsec;
	unsigned int tx_base_unit_nsec;
	unsigned int tx_gwan_unit_nsec;
	unsigned int tx_sweep_cnt;
	unsigned int tx_min_activatetime;
	/* WX Attwibutes */
	unsigned int wx_fiwwew_enabwe;
	unsigned int wx_dif_p_nsec;
	unsigned int wx_hibewn8_wait_nsec;
	unsigned int wx_base_unit_nsec;
	unsigned int wx_gwan_unit_nsec;
	unsigned int wx_sweep_cnt;
	unsigned int wx_staww_cnt;
	unsigned int wx_hs_g1_sync_wen_cap;
	unsigned int wx_hs_g2_sync_wen_cap;
	unsigned int wx_hs_g3_sync_wen_cap;
	unsigned int wx_hs_g1_pwep_sync_wen_cap;
	unsigned int wx_hs_g2_pwep_sync_wen_cap;
	unsigned int wx_hs_g3_pwep_sync_wen_cap;
	/* Common Attwibutes */
	unsigned int cmn_pwm_cwk_ctww;
	/* Intewnaw Attwibutes */
	unsigned int pa_dbg_option_suite;
	/* Changeabwe Attwibutes */
	unsigned int wx_adv_fine_gwan_sup_en;
	unsigned int wx_adv_fine_gwan_step;
	unsigned int wx_min_actv_time_cap;
	unsigned int wx_hibewn8_time_cap;
	unsigned int wx_adv_min_actv_time_cap;
	unsigned int wx_adv_hibewn8_time_cap;
	unsigned int pa_gwanuwawity;
	unsigned int pa_tactivate;
	unsigned int pa_hibewn8time;
};

stwuct exynos_ufs_dwv_data {
	const stwuct ufs_hba_vawiant_ops *vops;
	stwuct exynos_ufs_uic_attw *uic_attw;
	unsigned int quiwks;
	unsigned int opts;
	/* SoC's specific opewations */
	int (*dwv_init)(stwuct device *dev, stwuct exynos_ufs *ufs);
	int (*pwe_wink)(stwuct exynos_ufs *ufs);
	int (*post_wink)(stwuct exynos_ufs *ufs);
	int (*pwe_pww_change)(stwuct exynos_ufs *ufs,
				stwuct ufs_pa_wayew_attw *pww);
	int (*post_pww_change)(stwuct exynos_ufs *ufs,
				stwuct ufs_pa_wayew_attw *pww);
	int (*pwe_hce_enabwe)(stwuct exynos_ufs *ufs);
	int (*post_hce_enabwe)(stwuct exynos_ufs *ufs);
};

stwuct ufs_phy_time_cfg {
	u32 tx_wineweset_p;
	u32 tx_wineweset_n;
	u32 tx_high_z_cnt;
	u32 tx_base_n_vaw;
	u32 tx_gwan_n_vaw;
	u32 tx_sweep_cnt;
	u32 wx_wineweset;
	u32 wx_hibewn8_wait;
	u32 wx_base_n_vaw;
	u32 wx_gwan_n_vaw;
	u32 wx_sweep_cnt;
	u32 wx_staww_cnt;
};

stwuct exynos_ufs {
	stwuct ufs_hba *hba;
	stwuct phy *phy;
	void __iomem *weg_hci;
	void __iomem *weg_unipwo;
	void __iomem *weg_ufsp;
	stwuct cwk *cwk_hci_cowe;
	stwuct cwk *cwk_unipwo_main;
	stwuct cwk *cwk_apb;
	u32 pcwk_wate;
	u32 pcwk_div;
	u32 pcwk_avaiw_min;
	u32 pcwk_avaiw_max;
	unsigned wong mcwk_wate;
	int avaiw_wn_wx;
	int avaiw_wn_tx;
	int wx_sew_idx;
	stwuct ufs_pa_wayew_attw dev_weq_pawams;
	stwuct ufs_phy_time_cfg t_cfg;
	ktime_t entwy_hibewn8_t;
	const stwuct exynos_ufs_dwv_data *dwv_data;
	stwuct wegmap *sysweg;
	u32 shaweabiwity_weg_offset;

	u32 opts;
#define EXYNOS_UFS_OPT_HAS_APB_CWK_CTWW		BIT(0)
#define EXYNOS_UFS_OPT_SKIP_CONNECTION_ESTAB	BIT(1)
#define EXYNOS_UFS_OPT_BWOKEN_AUTO_CWK_CTWW	BIT(2)
#define EXYNOS_UFS_OPT_BWOKEN_WX_SEW_IDX	BIT(3)
#define EXYNOS_UFS_OPT_USE_SW_HIBEWN8_TIMEW	BIT(4)
#define EXYNOS_UFS_OPT_SKIP_CONFIG_PHY_ATTW	BIT(5)
};

#define fow_each_ufs_wx_wane(ufs, i) \
	fow (i = (ufs)->wx_sew_idx; \
		i < (ufs)->wx_sew_idx + (ufs)->avaiw_wn_wx; i++)
#define fow_each_ufs_tx_wane(ufs, i) \
	fow (i = 0; i < (ufs)->avaiw_wn_tx; i++)

#define EXYNOS_UFS_MMIO_FUNC(name)					  \
static inwine void name##_wwitew(stwuct exynos_ufs *ufs, u32 vaw, u32 weg)\
{									  \
	wwitew(vaw, ufs->weg_##name + weg);				  \
}									  \
									  \
static inwine u32 name##_weadw(stwuct exynos_ufs *ufs, u32 weg)		  \
{									  \
	wetuwn weadw(ufs->weg_##name + weg);				  \
}

EXYNOS_UFS_MMIO_FUNC(hci);
EXYNOS_UFS_MMIO_FUNC(unipwo);
EXYNOS_UFS_MMIO_FUNC(ufsp);
#undef EXYNOS_UFS_MMIO_FUNC

wong exynos_ufs_cawc_time_cntw(stwuct exynos_ufs *, wong);

static inwine void exynos_ufs_enabwe_ov_tm(stwuct ufs_hba *hba)
{
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_OV_TM), twue);
}

static inwine void exynos_ufs_disabwe_ov_tm(stwuct ufs_hba *hba)
{
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_OV_TM), fawse);
}

static inwine void exynos_ufs_enabwe_dbg_mode(stwuct ufs_hba *hba)
{
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_MODE), twue);
}

static inwine void exynos_ufs_disabwe_dbg_mode(stwuct ufs_hba *hba)
{
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_MODE), fawse);
}

#endif /* _UFS_EXYNOS_H_ */
