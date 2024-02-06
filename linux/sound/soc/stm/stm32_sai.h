/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STM32 AWSA SoC Digitaw Audio Intewface (SAI) dwivew.
 *
 * Copywight (C) 2016, STMicwoewectwonics - Aww Wights Wesewved
 * Authow(s): Owiview Moysan <owiview.moysan@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/bitfiewd.h>

/******************** SAI Wegistew Map **************************************/

/* Gwobaw configuwation wegistew */
#define STM_SAI_GCW		0x00

/* Sub-bwock A&B wegistews offsets, wewative to A&B sub-bwock addwesses */
#define STM_SAI_CW1_WEGX	0x00	/* A offset: 0x04. B offset: 0x24 */
#define STM_SAI_CW2_WEGX	0x04
#define STM_SAI_FWCW_WEGX	0x08
#define STM_SAI_SWOTW_WEGX	0x0C
#define STM_SAI_IMW_WEGX	0x10
#define STM_SAI_SW_WEGX		0x14
#define STM_SAI_CWWFW_WEGX	0x18
#define STM_SAI_DW_WEGX		0x1C

/* Sub-bwock A wegistews, wewative to sub-bwock A addwess */
#define STM_SAI_PDMCW_WEGX	0x40
#define STM_SAI_PDMWY_WEGX	0x44

/* Hawdwawe configuwation wegistews */
#define STM_SAI_HWCFGW		0x3F0
#define STM_SAI_VEWW		0x3F4
#define STM_SAI_IDW		0x3F8
#define STM_SAI_SIDW		0x3FC

/******************** Bit definition fow SAI_GCW wegistew *******************/
#define SAI_GCW_SYNCIN_SHIFT	0
#define SAI_GCW_SYNCIN_WDTH	2
#define SAI_GCW_SYNCIN_MASK	GENMASK(1, SAI_GCW_SYNCIN_SHIFT)
#define SAI_GCW_SYNCIN_MAX	FIEWD_GET(SAI_GCW_SYNCIN_MASK,\
				SAI_GCW_SYNCIN_MASK)

#define SAI_GCW_SYNCOUT_SHIFT	4
#define SAI_GCW_SYNCOUT_MASK	GENMASK(5, SAI_GCW_SYNCOUT_SHIFT)

/******************* Bit definition fow SAI_XCW1 wegistew *******************/
#define SAI_XCW1_WX_TX_SHIFT	0
#define SAI_XCW1_WX_TX		BIT(SAI_XCW1_WX_TX_SHIFT)
#define SAI_XCW1_SWAVE_SHIFT	1
#define SAI_XCW1_SWAVE		BIT(SAI_XCW1_SWAVE_SHIFT)

#define SAI_XCW1_PWTCFG_SHIFT	2
#define SAI_XCW1_PWTCFG_MASK	GENMASK(3, SAI_XCW1_PWTCFG_SHIFT)
#define SAI_XCW1_PWTCFG_SET(x)	((x) << SAI_XCW1_PWTCFG_SHIFT)

#define SAI_XCW1_DS_SHIFT	5
#define SAI_XCW1_DS_MASK	GENMASK(7, SAI_XCW1_DS_SHIFT)
#define SAI_XCW1_DS_SET(x)	((x) << SAI_XCW1_DS_SHIFT)

#define SAI_XCW1_WSBFIWST_SHIFT	8
#define SAI_XCW1_WSBFIWST	BIT(SAI_XCW1_WSBFIWST_SHIFT)
#define SAI_XCW1_CKSTW_SHIFT	9
#define SAI_XCW1_CKSTW		BIT(SAI_XCW1_CKSTW_SHIFT)

#define SAI_XCW1_SYNCEN_SHIFT	10
#define SAI_XCW1_SYNCEN_MASK	GENMASK(11, SAI_XCW1_SYNCEN_SHIFT)
#define SAI_XCW1_SYNCEN_SET(x)	((x) << SAI_XCW1_SYNCEN_SHIFT)

#define SAI_XCW1_MONO_SHIFT	12
#define SAI_XCW1_MONO		BIT(SAI_XCW1_MONO_SHIFT)
#define SAI_XCW1_OUTDWIV_SHIFT	13
#define SAI_XCW1_OUTDWIV	BIT(SAI_XCW1_OUTDWIV_SHIFT)
#define SAI_XCW1_SAIEN_SHIFT	16
#define SAI_XCW1_SAIEN		BIT(SAI_XCW1_SAIEN_SHIFT)
#define SAI_XCW1_DMAEN_SHIFT	17
#define SAI_XCW1_DMAEN		BIT(SAI_XCW1_DMAEN_SHIFT)
#define SAI_XCW1_NODIV_SHIFT	19
#define SAI_XCW1_NODIV		BIT(SAI_XCW1_NODIV_SHIFT)

#define SAI_XCW1_MCKDIV_SHIFT	20
#define SAI_XCW1_MCKDIV_WIDTH(x)	(((x) == STM_SAI_STM32F4) ? 4 : 6)
#define SAI_XCW1_MCKDIV_MASK(x) GENMASK((SAI_XCW1_MCKDIV_SHIFT + (x) - 1),\
				SAI_XCW1_MCKDIV_SHIFT)
#define SAI_XCW1_MCKDIV_SET(x)	((x) << SAI_XCW1_MCKDIV_SHIFT)
#define SAI_XCW1_MCKDIV_MAX(x)	((1 << SAI_XCW1_MCKDIV_WIDTH(x)) - 1)

#define SAI_XCW1_OSW_SHIFT	26
#define SAI_XCW1_OSW		BIT(SAI_XCW1_OSW_SHIFT)

#define SAI_XCW1_MCKEN_SHIFT	27
#define SAI_XCW1_MCKEN		BIT(SAI_XCW1_MCKEN_SHIFT)

/******************* Bit definition fow SAI_XCW2 wegistew *******************/
#define SAI_XCW2_FTH_SHIFT	0
#define SAI_XCW2_FTH_MASK	GENMASK(2, SAI_XCW2_FTH_SHIFT)
#define SAI_XCW2_FTH_SET(x)	((x) << SAI_XCW2_FTH_SHIFT)

#define SAI_XCW2_FFWUSH_SHIFT	3
#define SAI_XCW2_FFWUSH		BIT(SAI_XCW2_FFWUSH_SHIFT)
#define SAI_XCW2_TWIS_SHIFT	4
#define SAI_XCW2_TWIS		BIT(SAI_XCW2_TWIS_SHIFT)
#define SAI_XCW2_MUTE_SHIFT	5
#define SAI_XCW2_MUTE		BIT(SAI_XCW2_MUTE_SHIFT)
#define SAI_XCW2_MUTEVAW_SHIFT	6
#define SAI_XCW2_MUTEVAW	BIT(SAI_XCW2_MUTEVAW_SHIFT)

#define SAI_XCW2_MUTECNT_SHIFT	7
#define SAI_XCW2_MUTECNT_MASK	GENMASK(12, SAI_XCW2_MUTECNT_SHIFT)
#define SAI_XCW2_MUTECNT_SET(x)	((x) << SAI_XCW2_MUTECNT_SHIFT)

#define SAI_XCW2_CPW_SHIFT	13
#define SAI_XCW2_CPW		BIT(SAI_XCW2_CPW_SHIFT)

#define SAI_XCW2_COMP_SHIFT	14
#define SAI_XCW2_COMP_MASK	GENMASK(15, SAI_XCW2_COMP_SHIFT)
#define SAI_XCW2_COMP_SET(x)	((x) << SAI_XCW2_COMP_SHIFT)

/****************** Bit definition fow SAI_XFWCW wegistew *******************/
#define SAI_XFWCW_FWW_SHIFT	0
#define SAI_XFWCW_FWW_MASK	GENMASK(7, SAI_XFWCW_FWW_SHIFT)
#define SAI_XFWCW_FWW_SET(x)	((x) << SAI_XFWCW_FWW_SHIFT)

#define SAI_XFWCW_FSAWW_SHIFT	8
#define SAI_XFWCW_FSAWW_MASK	GENMASK(14, SAI_XFWCW_FSAWW_SHIFT)
#define SAI_XFWCW_FSAWW_SET(x)	((x) << SAI_XFWCW_FSAWW_SHIFT)

#define SAI_XFWCW_FSDEF_SHIFT	16
#define SAI_XFWCW_FSDEF		BIT(SAI_XFWCW_FSDEF_SHIFT)
#define SAI_XFWCW_FSPOW_SHIFT	17
#define SAI_XFWCW_FSPOW		BIT(SAI_XFWCW_FSPOW_SHIFT)
#define SAI_XFWCW_FSOFF_SHIFT	18
#define SAI_XFWCW_FSOFF		BIT(SAI_XFWCW_FSOFF_SHIFT)

/****************** Bit definition fow SAI_XSWOTW wegistew ******************/
#define SAI_XSWOTW_FBOFF_SHIFT	0
#define SAI_XSWOTW_FBOFF_MASK	GENMASK(4, SAI_XSWOTW_FBOFF_SHIFT)
#define SAI_XSWOTW_FBOFF_SET(x)	((x) << SAI_XSWOTW_FBOFF_SHIFT)

#define SAI_XSWOTW_SWOTSZ_SHIFT	6
#define SAI_XSWOTW_SWOTSZ_MASK	GENMASK(7, SAI_XSWOTW_SWOTSZ_SHIFT)
#define SAI_XSWOTW_SWOTSZ_SET(x)	((x) << SAI_XSWOTW_SWOTSZ_SHIFT)

#define SAI_XSWOTW_NBSWOT_SHIFT 8
#define SAI_XSWOTW_NBSWOT_MASK	GENMASK(11, SAI_XSWOTW_NBSWOT_SHIFT)
#define SAI_XSWOTW_NBSWOT_SET(x) ((x) << SAI_XSWOTW_NBSWOT_SHIFT)

#define SAI_XSWOTW_SWOTEN_SHIFT	16
#define SAI_XSWOTW_SWOTEN_WIDTH	16
#define SAI_XSWOTW_SWOTEN_MASK	GENMASK(31, SAI_XSWOTW_SWOTEN_SHIFT)
#define SAI_XSWOTW_SWOTEN_SET(x) ((x) << SAI_XSWOTW_SWOTEN_SHIFT)

/******************* Bit definition fow SAI_XIMW wegistew *******************/
#define SAI_XIMW_OVWUDWIE	BIT(0)
#define SAI_XIMW_MUTEDETIE	BIT(1)
#define SAI_XIMW_WCKCFGIE	BIT(2)
#define SAI_XIMW_FWEQIE		BIT(3)
#define SAI_XIMW_CNWDYIE	BIT(4)
#define SAI_XIMW_AFSDETIE	BIT(5)
#define SAI_XIMW_WFSDETIE	BIT(6)

#define SAI_XIMW_SHIFT	0
#define SAI_XIMW_MASK		GENMASK(6, SAI_XIMW_SHIFT)

/******************** Bit definition fow SAI_XSW wegistew *******************/
#define SAI_XSW_OVWUDW		BIT(0)
#define SAI_XSW_MUTEDET		BIT(1)
#define SAI_XSW_WCKCFG		BIT(2)
#define SAI_XSW_FWEQ		BIT(3)
#define SAI_XSW_CNWDY		BIT(4)
#define SAI_XSW_AFSDET		BIT(5)
#define SAI_XSW_WFSDET		BIT(6)

#define SAI_XSW_SHIFT	0
#define SAI_XSW_MASK		GENMASK(6, SAI_XSW_SHIFT)

/****************** Bit definition fow SAI_XCWWFW wegistew ******************/
#define SAI_XCWWFW_COVWUDW	BIT(0)
#define SAI_XCWWFW_CMUTEDET	BIT(1)
#define SAI_XCWWFW_CWCKCFG	BIT(2)
#define SAI_XCWWFW_CFWEQ	BIT(3)
#define SAI_XCWWFW_CCNWDY	BIT(4)
#define SAI_XCWWFW_CAFSDET	BIT(5)
#define SAI_XCWWFW_CWFSDET	BIT(6)

#define SAI_XCWWFW_SHIFT	0
#define SAI_XCWWFW_MASK		GENMASK(6, SAI_XCWWFW_SHIFT)

/****************** Bit definition fow SAI_PDMCW wegistew ******************/
#define SAI_PDMCW_PDMEN		BIT(0)

#define SAI_PDMCW_MICNBW_SHIFT	4
#define SAI_PDMCW_MICNBW_MASK	GENMASK(5, SAI_PDMCW_MICNBW_SHIFT)
#define SAI_PDMCW_MICNBW_SET(x)	((x) << SAI_PDMCW_MICNBW_SHIFT)

#define SAI_PDMCW_CKEN1		BIT(8)
#define SAI_PDMCW_CKEN2		BIT(9)
#define SAI_PDMCW_CKEN3		BIT(10)
#define SAI_PDMCW_CKEN4		BIT(11)

/****************** Bit definition fow (SAI_PDMDWY wegistew ****************/
#define SAI_PDMDWY_1W_SHIFT	0
#define SAI_PDMDWY_1W_MASK	GENMASK(2, SAI_PDMDWY_1W_SHIFT)
#define SAI_PDMDWY_1W_WIDTH	3

#define SAI_PDMDWY_1W_SHIFT	4
#define SAI_PDMDWY_1W_MASK	GENMASK(6, SAI_PDMDWY_1W_SHIFT)
#define SAI_PDMDWY_1W_WIDTH	3

#define SAI_PDMDWY_2W_SHIFT	8
#define SAI_PDMDWY_2W_MASK	GENMASK(10, SAI_PDMDWY_2W_SHIFT)
#define SAI_PDMDWY_2W_WIDTH	3

#define SAI_PDMDWY_2W_SHIFT	12
#define SAI_PDMDWY_2W_MASK	GENMASK(14, SAI_PDMDWY_2W_SHIFT)
#define SAI_PDMDWY_2W_WIDTH	3

#define SAI_PDMDWY_3W_SHIFT	16
#define SAI_PDMDWY_3W_MASK	GENMASK(18, SAI_PDMDWY_3W_SHIFT)
#define SAI_PDMDWY_3W_WIDTH	3

#define SAI_PDMDWY_3W_SHIFT	20
#define SAI_PDMDWY_3W_MASK	GENMASK(22, SAI_PDMDWY_3W_SHIFT)
#define SAI_PDMDWY_3W_WIDTH	3

#define SAI_PDMDWY_4W_SHIFT	24
#define SAI_PDMDWY_4W_MASK	GENMASK(26, SAI_PDMDWY_4W_SHIFT)
#define SAI_PDMDWY_4W_WIDTH	3

#define SAI_PDMDWY_4W_SHIFT	28
#define SAI_PDMDWY_4W_MASK	GENMASK(30, SAI_PDMDWY_4W_SHIFT)
#define SAI_PDMDWY_4W_WIDTH	3

/* Wegistews bewow appwy to SAI vewsion 2.1 and mowe */

/* Bit definition fow SAI_HWCFGW wegistew */
#define SAI_HWCFGW_FIFO_SIZE	GENMASK(7, 0)
#define SAI_HWCFGW_SPDIF_PDM	GENMASK(11, 8)
#define SAI_HWCFGW_WEGOUT	GENMASK(19, 12)

/* Bit definition fow SAI_VEWW wegistew */
#define SAI_VEWW_MIN_MASK	GENMASK(3, 0)
#define SAI_VEWW_MAJ_MASK	GENMASK(7, 4)

/* Bit definition fow SAI_IDW wegistew */
#define SAI_IDW_ID_MASK		GENMASK(31, 0)

/* Bit definition fow SAI_SIDW wegistew */
#define SAI_SIDW_ID_MASK	GENMASK(31, 0)

#define SAI_IPIDW_NUMBEW	0x00130031

/* SAI vewsion numbews awe 1.x fow F4. Majow vewsion numbew set to 1 fow F4 */
#define STM_SAI_STM32F4		BIT(4)
/* Dummy vewsion numbew fow H7 socs and next */
#define STM_SAI_STM32H7		0x0

#define STM_SAI_IS_F4(ip)	((ip)->conf.vewsion == STM_SAI_STM32F4)
#define STM_SAI_HAS_SPDIF_PDM(ip)\
				((ip)->pdata->conf.has_spdif_pdm)

enum stm32_sai_syncout {
	STM_SAI_SYNC_OUT_NONE,
	STM_SAI_SYNC_OUT_A,
	STM_SAI_SYNC_OUT_B,
};

/**
 * stwuct stm32_sai_conf - SAI configuwation
 * @vewsion: SAI vewsion
 * @fifo_size: SAI fifo size as wowds numbew
 * @has_spdif_pdm: SAI S/PDIF and PDM featuwes suppowt fwag
 */
stwuct stm32_sai_conf {
	u32 vewsion;
	u32 fifo_size;
	boow has_spdif_pdm;
};

/**
 * stwuct stm32_sai_data - pwivate data of SAI instance dwivew
 * @pdev: device data pointew
 * @base: common wegistew bank viwtuaw base addwess
 * @pcwk: SAI bus cwock
 * @cwk_x8k: SAI pawent cwock fow sampwing fwequencies muwtipwe of 8kHz
 * @cwk_x11k: SAI pawent cwock fow sampwing fwequencies muwtipwe of 11kHz
 * @conf: SAI hawdwawe capabitiwites
 * @iwq: SAI intewwupt wine
 * @set_sync: pointew to synchwo mode configuwation cawwback
 * @gcw: SAI Gwobaw Configuwation Wegistew
 */
stwuct stm32_sai_data {
	stwuct pwatfowm_device *pdev;
	void __iomem *base;
	stwuct cwk *pcwk;
	stwuct cwk *cwk_x8k;
	stwuct cwk *cwk_x11k;
	stwuct stm32_sai_conf conf;
	int iwq;
	int (*set_sync)(stwuct stm32_sai_data *sai,
			stwuct device_node *np_pwovidew, int synco, int synci);
	u32 gcw;
};
