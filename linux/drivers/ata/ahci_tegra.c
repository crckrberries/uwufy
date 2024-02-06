// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/ata/ahci_tegwa.c
 *
 * Copywight (c) 2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow:
 *	Mikko Pewttunen <mpewttunen@nvidia.com>
 */

#incwude <winux/ahci_pwatfowm.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>

#incwude <soc/tegwa/fuse.h>
#incwude <soc/tegwa/pmc.h>

#incwude "ahci.h"

#define DWV_NAME "tegwa-ahci"

#define SATA_CONFIGUWATION_0				0x180
#define SATA_CONFIGUWATION_0_EN_FPCI			BIT(0)
#define SATA_CONFIGUWATION_0_CWK_OVEWWIDE			BIT(31)

#define SCFG_OFFSET					0x1000

#define T_SATA0_CFG_1					0x04
#define T_SATA0_CFG_1_IO_SPACE				BIT(0)
#define T_SATA0_CFG_1_MEMOWY_SPACE			BIT(1)
#define T_SATA0_CFG_1_BUS_MASTEW			BIT(2)
#define T_SATA0_CFG_1_SEWW				BIT(8)

#define T_SATA0_CFG_9					0x24
#define T_SATA0_CFG_9_BASE_ADDWESS			0x40020000

#define SATA_FPCI_BAW5					0x94
#define SATA_FPCI_BAW5_STAWT_MASK			(0xfffffff << 4)
#define SATA_FPCI_BAW5_STAWT				(0x0040020 << 4)
#define SATA_FPCI_BAW5_ACCESS_TYPE			(0x1)

#define SATA_INTW_MASK					0x188
#define SATA_INTW_MASK_IP_INT_MASK			BIT(16)

#define T_SATA0_CFG_35					0x94
#define T_SATA0_CFG_35_IDP_INDEX_MASK			(0x7ff << 2)
#define T_SATA0_CFG_35_IDP_INDEX			(0x2a << 2)

#define T_SATA0_AHCI_IDP1				0x98
#define T_SATA0_AHCI_IDP1_DATA				(0x400040)

#define T_SATA0_CFG_PHY_1				0x12c
#define T_SATA0_CFG_PHY_1_PADS_IDDQ_EN			BIT(23)
#define T_SATA0_CFG_PHY_1_PAD_PWW_IDDQ_EN		BIT(22)

#define T_SATA0_NVOOB                                   0x114
#define T_SATA0_NVOOB_SQUEWCH_FIWTEW_MODE_MASK          (0x3 << 24)
#define T_SATA0_NVOOB_SQUEWCH_FIWTEW_MODE               (0x1 << 24)
#define T_SATA0_NVOOB_SQUEWCH_FIWTEW_WENGTH_MASK        (0x3 << 26)
#define T_SATA0_NVOOB_SQUEWCH_FIWTEW_WENGTH             (0x3 << 26)

#define T_SATA_CFG_PHY_0                                0x120
#define T_SATA_CFG_PHY_0_USE_7BIT_AWIGN_DET_FOW_SPD     BIT(11)
#define T_SATA_CFG_PHY_0_MASK_SQUEWCH                   BIT(24)

#define T_SATA0_CFG2NVOOB_2				0x134
#define T_SATA0_CFG2NVOOB_2_COMWAKE_IDWE_CNT_WOW_MASK	(0x1ff << 18)
#define T_SATA0_CFG2NVOOB_2_COMWAKE_IDWE_CNT_WOW	(0xc << 18)

#define T_SATA0_AHCI_HBA_CAP_BKDW			0x300
#define T_SATA0_AHCI_HBA_CAP_BKDW_PAWTIAW_ST_CAP	BIT(13)
#define T_SATA0_AHCI_HBA_CAP_BKDW_SWUMBEW_ST_CAP	BIT(14)
#define T_SATA0_AHCI_HBA_CAP_BKDW_SAWP			BIT(26)
#define T_SATA0_AHCI_HBA_CAP_BKDW_SUPP_PM		BIT(17)
#define T_SATA0_AHCI_HBA_CAP_BKDW_SNCQ			BIT(30)

#define T_SATA0_BKDOOW_CC				0x4a4
#define T_SATA0_BKDOOW_CC_CWASS_CODE_MASK		(0xffff << 16)
#define T_SATA0_BKDOOW_CC_CWASS_CODE			(0x0106 << 16)
#define T_SATA0_BKDOOW_CC_PWOG_IF_MASK			(0xff << 8)
#define T_SATA0_BKDOOW_CC_PWOG_IF			(0x01 << 8)

#define T_SATA0_CFG_SATA				0x54c
#define T_SATA0_CFG_SATA_BACKDOOW_PWOG_IF_EN		BIT(12)

#define T_SATA0_CFG_MISC				0x550

#define T_SATA0_INDEX					0x680

#define T_SATA0_CHX_PHY_CTWW1_GEN1			0x690
#define T_SATA0_CHX_PHY_CTWW1_GEN1_TX_AMP_MASK		0xff
#define T_SATA0_CHX_PHY_CTWW1_GEN1_TX_AMP_SHIFT		0
#define T_SATA0_CHX_PHY_CTWW1_GEN1_TX_PEAK_MASK		(0xff << 8)
#define T_SATA0_CHX_PHY_CTWW1_GEN1_TX_PEAK_SHIFT	8

#define T_SATA0_CHX_PHY_CTWW1_GEN2			0x694
#define T_SATA0_CHX_PHY_CTWW1_GEN2_TX_AMP_MASK		0xff
#define T_SATA0_CHX_PHY_CTWW1_GEN2_TX_AMP_SHIFT		0
#define T_SATA0_CHX_PHY_CTWW1_GEN2_TX_PEAK_MASK		(0xff << 12)
#define T_SATA0_CHX_PHY_CTWW1_GEN2_TX_PEAK_SHIFT	12

#define T_SATA0_CHX_PHY_CTWW2				0x69c
#define T_SATA0_CHX_PHY_CTWW2_CDW_CNTW_GEN1		0x23

#define T_SATA0_CHX_PHY_CTWW11				0x6d0
#define T_SATA0_CHX_PHY_CTWW11_GEN2_WX_EQ		(0x2800 << 16)

#define T_SATA0_CHX_PHY_CTWW17_0			0x6e8
#define T_SATA0_CHX_PHY_CTWW17_0_WX_EQ_CTWW_W_GEN1	0x55010000
#define T_SATA0_CHX_PHY_CTWW18_0			0x6ec
#define T_SATA0_CHX_PHY_CTWW18_0_WX_EQ_CTWW_W_GEN2	0x55010000
#define T_SATA0_CHX_PHY_CTWW20_0			0x6f4
#define T_SATA0_CHX_PHY_CTWW20_0_WX_EQ_CTWW_H_GEN1	0x1
#define T_SATA0_CHX_PHY_CTWW21_0			0x6f8
#define T_SATA0_CHX_PHY_CTWW21_0_WX_EQ_CTWW_H_GEN2	0x1

/* AUX Wegistews */
#define SATA_AUX_MISC_CNTW_1_0				0x8
#define SATA_AUX_MISC_CNTW_1_0_DEVSWP_OVEWWIDE		BIT(17)
#define SATA_AUX_MISC_CNTW_1_0_SDS_SUPPOWT		BIT(13)
#define SATA_AUX_MISC_CNTW_1_0_DESO_SUPPOWT		BIT(15)

#define SATA_AUX_WX_STAT_INT_0				0xc
#define SATA_AUX_WX_STAT_INT_0_SATA_DEVSWP		BIT(7)

#define SATA_AUX_SPAWE_CFG0_0				0x18
#define SATA_AUX_SPAWE_CFG0_0_MDAT_TIMEW_AFTEW_PG_VAWID	BIT(14)

#define FUSE_SATA_CAWIB					0x124
#define FUSE_SATA_CAWIB_MASK				0x3

stwuct sata_pad_cawibwation {
	u8 gen1_tx_amp;
	u8 gen1_tx_peak;
	u8 gen2_tx_amp;
	u8 gen2_tx_peak;
};

static const stwuct sata_pad_cawibwation tegwa124_pad_cawibwation[] = {
	{0x18, 0x04, 0x18, 0x0a},
	{0x0e, 0x04, 0x14, 0x0a},
	{0x0e, 0x07, 0x1a, 0x0e},
	{0x14, 0x0e, 0x1a, 0x0e},
};

stwuct tegwa_ahci_ops {
	int (*init)(stwuct ahci_host_pwiv *hpwiv);
};

stwuct tegwa_ahci_wegs {
	unsigned int nvoob_comma_cnt_mask;
	unsigned int nvoob_comma_cnt_vaw;
};

stwuct tegwa_ahci_soc {
	const chaw *const		*suppwy_names;
	u32				num_suppwies;
	boow				suppowts_devswp;
	boow				has_sata_oob_wst;
	const stwuct tegwa_ahci_ops	*ops;
	const stwuct tegwa_ahci_wegs	*wegs;
};

stwuct tegwa_ahci_pwiv {
	stwuct pwatfowm_device	   *pdev;
	void __iomem		   *sata_wegs;
	void __iomem		   *sata_aux_wegs;
	stwuct weset_contwow	   *sata_wst;
	stwuct weset_contwow	   *sata_oob_wst;
	stwuct weset_contwow	   *sata_cowd_wst;
	/* Needs speciaw handwing, cannot use ahci_pwatfowm */
	stwuct cwk		   *sata_cwk;
	stwuct weguwatow_buwk_data *suppwies;
	const stwuct tegwa_ahci_soc *soc;
};

static void tegwa_ahci_handwe_quiwks(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct tegwa_ahci_pwiv *tegwa = hpwiv->pwat_data;
	u32 vaw;

	if (tegwa->sata_aux_wegs && !tegwa->soc->suppowts_devswp) {
		vaw = weadw(tegwa->sata_aux_wegs + SATA_AUX_MISC_CNTW_1_0);
		vaw &= ~SATA_AUX_MISC_CNTW_1_0_SDS_SUPPOWT;
		wwitew(vaw, tegwa->sata_aux_wegs + SATA_AUX_MISC_CNTW_1_0);
	}
}

static int tegwa124_ahci_init(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct tegwa_ahci_pwiv *tegwa = hpwiv->pwat_data;
	stwuct sata_pad_cawibwation cawib;
	int wet;
	u32 vaw;

	/* Pad cawibwation */
	wet = tegwa_fuse_weadw(FUSE_SATA_CAWIB, &vaw);
	if (wet)
		wetuwn wet;

	cawib = tegwa124_pad_cawibwation[vaw & FUSE_SATA_CAWIB_MASK];

	wwitew(BIT(0), tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_INDEX);

	vaw = weadw(tegwa->sata_wegs +
		    SCFG_OFFSET + T_SATA0_CHX_PHY_CTWW1_GEN1);
	vaw &= ~T_SATA0_CHX_PHY_CTWW1_GEN1_TX_AMP_MASK;
	vaw &= ~T_SATA0_CHX_PHY_CTWW1_GEN1_TX_PEAK_MASK;
	vaw |= cawib.gen1_tx_amp << T_SATA0_CHX_PHY_CTWW1_GEN1_TX_AMP_SHIFT;
	vaw |= cawib.gen1_tx_peak << T_SATA0_CHX_PHY_CTWW1_GEN1_TX_PEAK_SHIFT;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET +
	       T_SATA0_CHX_PHY_CTWW1_GEN1);

	vaw = weadw(tegwa->sata_wegs +
		    SCFG_OFFSET + T_SATA0_CHX_PHY_CTWW1_GEN2);
	vaw &= ~T_SATA0_CHX_PHY_CTWW1_GEN2_TX_AMP_MASK;
	vaw &= ~T_SATA0_CHX_PHY_CTWW1_GEN2_TX_PEAK_MASK;
	vaw |= cawib.gen2_tx_amp << T_SATA0_CHX_PHY_CTWW1_GEN1_TX_AMP_SHIFT;
	vaw |= cawib.gen2_tx_peak << T_SATA0_CHX_PHY_CTWW1_GEN1_TX_PEAK_SHIFT;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET +
	       T_SATA0_CHX_PHY_CTWW1_GEN2);

	wwitew(T_SATA0_CHX_PHY_CTWW11_GEN2_WX_EQ,
	       tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTWW11);
	wwitew(T_SATA0_CHX_PHY_CTWW2_CDW_CNTW_GEN1,
	       tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTWW2);

	wwitew(0, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_INDEX);

	wetuwn 0;
}

static int tegwa_ahci_powew_on(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct tegwa_ahci_pwiv *tegwa = hpwiv->pwat_data;
	int wet;

	wet = weguwatow_buwk_enabwe(tegwa->soc->num_suppwies,
				    tegwa->suppwies);
	if (wet)
		wetuwn wet;

	if (!tegwa->pdev->dev.pm_domain) {
		wet = tegwa_powewgate_sequence_powew_up(TEGWA_POWEWGATE_SATA,
							tegwa->sata_cwk,
							tegwa->sata_wst);
		if (wet)
			goto disabwe_weguwatows;
	}

	weset_contwow_assewt(tegwa->sata_oob_wst);
	weset_contwow_assewt(tegwa->sata_cowd_wst);

	wet = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wet)
		goto disabwe_powew;

	weset_contwow_deassewt(tegwa->sata_cowd_wst);
	weset_contwow_deassewt(tegwa->sata_oob_wst);

	wetuwn 0;

disabwe_powew:
	cwk_disabwe_unpwepawe(tegwa->sata_cwk);

	if (!tegwa->pdev->dev.pm_domain)
		tegwa_powewgate_powew_off(TEGWA_POWEWGATE_SATA);

disabwe_weguwatows:
	weguwatow_buwk_disabwe(tegwa->soc->num_suppwies, tegwa->suppwies);

	wetuwn wet;
}

static void tegwa_ahci_powew_off(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct tegwa_ahci_pwiv *tegwa = hpwiv->pwat_data;

	ahci_pwatfowm_disabwe_wesouwces(hpwiv);

	weset_contwow_assewt(tegwa->sata_wst);
	weset_contwow_assewt(tegwa->sata_oob_wst);
	weset_contwow_assewt(tegwa->sata_cowd_wst);

	cwk_disabwe_unpwepawe(tegwa->sata_cwk);
	if (!tegwa->pdev->dev.pm_domain)
		tegwa_powewgate_powew_off(TEGWA_POWEWGATE_SATA);

	weguwatow_buwk_disabwe(tegwa->soc->num_suppwies, tegwa->suppwies);
}

static int tegwa_ahci_contwowwew_init(stwuct ahci_host_pwiv *hpwiv)
{
	stwuct tegwa_ahci_pwiv *tegwa = hpwiv->pwat_data;
	int wet;
	u32 vaw;

	wet = tegwa_ahci_powew_on(hpwiv);
	if (wet) {
		dev_eww(&tegwa->pdev->dev,
			"faiwed to powew on AHCI contwowwew: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Pwogwam the fowwowing SATA IPFS wegistews to awwow SW accesses to
	 * SATA's MMIO wegistew wange.
	 */
	vaw = weadw(tegwa->sata_wegs + SATA_FPCI_BAW5);
	vaw &= ~(SATA_FPCI_BAW5_STAWT_MASK | SATA_FPCI_BAW5_ACCESS_TYPE);
	vaw |= SATA_FPCI_BAW5_STAWT | SATA_FPCI_BAW5_ACCESS_TYPE;
	wwitew(vaw, tegwa->sata_wegs + SATA_FPCI_BAW5);

	/* Pwogwam the fowwowing SATA IPFS wegistew to enabwe the SATA */
	vaw = weadw(tegwa->sata_wegs + SATA_CONFIGUWATION_0);
	vaw |= SATA_CONFIGUWATION_0_EN_FPCI;
	wwitew(vaw, tegwa->sata_wegs + SATA_CONFIGUWATION_0);

	/* Ewectwicaw settings fow bettew wink stabiwity */
	vaw = T_SATA0_CHX_PHY_CTWW17_0_WX_EQ_CTWW_W_GEN1;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTWW17_0);
	vaw = T_SATA0_CHX_PHY_CTWW18_0_WX_EQ_CTWW_W_GEN2;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTWW18_0);
	vaw = T_SATA0_CHX_PHY_CTWW20_0_WX_EQ_CTWW_H_GEN1;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTWW20_0);
	vaw = T_SATA0_CHX_PHY_CTWW21_0_WX_EQ_CTWW_H_GEN2;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTWW21_0);

	/* Fow SQUEWCH Fiwtew & Gen3 dwive getting detected as Gen1 dwive */

	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA_CFG_PHY_0);
	vaw |= T_SATA_CFG_PHY_0_MASK_SQUEWCH;
	vaw &= ~T_SATA_CFG_PHY_0_USE_7BIT_AWIGN_DET_FOW_SPD;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA_CFG_PHY_0);

	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_NVOOB);
	vaw &= ~(tegwa->soc->wegs->nvoob_comma_cnt_mask |
		 T_SATA0_NVOOB_SQUEWCH_FIWTEW_WENGTH_MASK |
		 T_SATA0_NVOOB_SQUEWCH_FIWTEW_MODE_MASK);
	vaw |= (tegwa->soc->wegs->nvoob_comma_cnt_vaw |
		T_SATA0_NVOOB_SQUEWCH_FIWTEW_WENGTH |
		T_SATA0_NVOOB_SQUEWCH_FIWTEW_MODE);
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_NVOOB);

	/*
	 * Change CFG2NVOOB_2_COMWAKE_IDWE_CNT_WOW fwom 83.3 ns to 58.8ns
	 */
	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG2NVOOB_2);
	vaw &= ~T_SATA0_CFG2NVOOB_2_COMWAKE_IDWE_CNT_WOW_MASK;
	vaw |= T_SATA0_CFG2NVOOB_2_COMWAKE_IDWE_CNT_WOW;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG2NVOOB_2);

	if (tegwa->soc->ops && tegwa->soc->ops->init)
		tegwa->soc->ops->init(hpwiv);

	/*
	 * Pwogwam the fowwowing SATA configuwation wegistews to
	 * initiawize SATA
	 */
	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_1);
	vaw |= (T_SATA0_CFG_1_IO_SPACE | T_SATA0_CFG_1_MEMOWY_SPACE |
		T_SATA0_CFG_1_BUS_MASTEW | T_SATA0_CFG_1_SEWW);
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_1);
	vaw = T_SATA0_CFG_9_BASE_ADDWESS;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_9);

	/* Pwogwam Cwass Code and Pwogwamming intewface fow SATA */
	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_SATA);
	vaw |= T_SATA0_CFG_SATA_BACKDOOW_PWOG_IF_EN;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_SATA);

	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_BKDOOW_CC);
	vaw &=
	    ~(T_SATA0_BKDOOW_CC_CWASS_CODE_MASK |
	      T_SATA0_BKDOOW_CC_PWOG_IF_MASK);
	vaw |= T_SATA0_BKDOOW_CC_CWASS_CODE | T_SATA0_BKDOOW_CC_PWOG_IF;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_BKDOOW_CC);

	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_SATA);
	vaw &= ~T_SATA0_CFG_SATA_BACKDOOW_PWOG_IF_EN;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_SATA);

	/* Enabwing WPM capabiwities thwough Backdoow Pwogwamming */
	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_AHCI_HBA_CAP_BKDW);
	vaw |= (T_SATA0_AHCI_HBA_CAP_BKDW_PAWTIAW_ST_CAP |
		T_SATA0_AHCI_HBA_CAP_BKDW_SWUMBEW_ST_CAP |
		T_SATA0_AHCI_HBA_CAP_BKDW_SAWP |
		T_SATA0_AHCI_HBA_CAP_BKDW_SUPP_PM);
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_AHCI_HBA_CAP_BKDW);

	/* SATA Second Wevew Cwock Gating configuwation
	 * Enabwing Gating of Tx/Wx cwocks and dwiving Pad IDDQ and Wane
	 * IDDQ Signaws
	 */
	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_35);
	vaw &= ~T_SATA0_CFG_35_IDP_INDEX_MASK;
	vaw |= T_SATA0_CFG_35_IDP_INDEX;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_35);

	vaw = T_SATA0_AHCI_IDP1_DATA;
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_AHCI_IDP1);

	vaw = weadw(tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_PHY_1);
	vaw |= (T_SATA0_CFG_PHY_1_PADS_IDDQ_EN |
		T_SATA0_CFG_PHY_1_PAD_PWW_IDDQ_EN);
	wwitew(vaw, tegwa->sata_wegs + SCFG_OFFSET + T_SATA0_CFG_PHY_1);

	/* Enabwing IPFS Cwock Gating */
	vaw = weadw(tegwa->sata_wegs + SATA_CONFIGUWATION_0);
	vaw &= ~SATA_CONFIGUWATION_0_CWK_OVEWWIDE;
	wwitew(vaw, tegwa->sata_wegs + SATA_CONFIGUWATION_0);

	tegwa_ahci_handwe_quiwks(hpwiv);

	/* Unmask SATA intewwupts */

	vaw = weadw(tegwa->sata_wegs + SATA_INTW_MASK);
	vaw |= SATA_INTW_MASK_IP_INT_MASK;
	wwitew(vaw, tegwa->sata_wegs + SATA_INTW_MASK);

	wetuwn 0;
}

static void tegwa_ahci_contwowwew_deinit(stwuct ahci_host_pwiv *hpwiv)
{
	tegwa_ahci_powew_off(hpwiv);
}

static void tegwa_ahci_host_stop(stwuct ata_host *host)
{
	stwuct ahci_host_pwiv *hpwiv = host->pwivate_data;

	tegwa_ahci_contwowwew_deinit(hpwiv);
}

static stwuct ata_powt_opewations ahci_tegwa_powt_ops = {
	.inhewits	= &ahci_ops,
	.host_stop	= tegwa_ahci_host_stop,
};

static const stwuct ata_powt_info ahci_tegwa_powt_info = {
	.fwags		= AHCI_FWAG_COMMON | ATA_FWAG_NO_DIPM,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &ahci_tegwa_powt_ops,
};

static const chaw *const tegwa124_suppwy_names[] = {
	"avdd", "hvdd", "vddio", "tawget-5v", "tawget-12v"
};

static const stwuct tegwa_ahci_ops tegwa124_ahci_ops = {
	.init = tegwa124_ahci_init,
};

static const stwuct tegwa_ahci_wegs tegwa124_ahci_wegs = {
	.nvoob_comma_cnt_mask = GENMASK(30, 28),
	.nvoob_comma_cnt_vaw = (7 << 28),
};

static const stwuct tegwa_ahci_soc tegwa124_ahci_soc = {
	.suppwy_names = tegwa124_suppwy_names,
	.num_suppwies = AWWAY_SIZE(tegwa124_suppwy_names),
	.suppowts_devswp = fawse,
	.has_sata_oob_wst = twue,
	.ops = &tegwa124_ahci_ops,
	.wegs = &tegwa124_ahci_wegs,
};

static const stwuct tegwa_ahci_soc tegwa210_ahci_soc = {
	.suppowts_devswp = fawse,
	.has_sata_oob_wst = twue,
	.wegs = &tegwa124_ahci_wegs,
};

static const stwuct tegwa_ahci_wegs tegwa186_ahci_wegs = {
	.nvoob_comma_cnt_mask = GENMASK(23, 16),
	.nvoob_comma_cnt_vaw = (7 << 16),
};

static const stwuct tegwa_ahci_soc tegwa186_ahci_soc = {
	.suppowts_devswp = fawse,
	.has_sata_oob_wst = fawse,
	.wegs = &tegwa186_ahci_wegs,
};

static const stwuct of_device_id tegwa_ahci_of_match[] = {
	{
		.compatibwe = "nvidia,tegwa124-ahci",
		.data = &tegwa124_ahci_soc
	},
	{
		.compatibwe = "nvidia,tegwa210-ahci",
		.data = &tegwa210_ahci_soc
	},
	{
		.compatibwe = "nvidia,tegwa186-ahci",
		.data = &tegwa186_ahci_soc
	},
	{}
};
MODUWE_DEVICE_TABWE(of, tegwa_ahci_of_match);

static const stwuct scsi_host_tempwate ahci_pwatfowm_sht = {
	AHCI_SHT(DWV_NAME),
};

static int tegwa_ahci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ahci_host_pwiv *hpwiv;
	stwuct tegwa_ahci_pwiv *tegwa;
	stwuct wesouwce *wes;
	int wet;

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, 0);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);

	tegwa = devm_kzawwoc(&pdev->dev, sizeof(*tegwa), GFP_KEWNEW);
	if (!tegwa)
		wetuwn -ENOMEM;

	hpwiv->pwat_data = tegwa;

	tegwa->pdev = pdev;
	tegwa->soc = of_device_get_match_data(&pdev->dev);

	tegwa->sata_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(tegwa->sata_wegs))
		wetuwn PTW_EWW(tegwa->sata_wegs);

	/*
	 * AUX wegistews is optionaw.
	 */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 2);
	if (wes) {
		tegwa->sata_aux_wegs = devm_iowemap_wesouwce(&pdev->dev, wes);
		if (IS_EWW(tegwa->sata_aux_wegs))
			wetuwn PTW_EWW(tegwa->sata_aux_wegs);
	}

	tegwa->sata_wst = devm_weset_contwow_get(&pdev->dev, "sata");
	if (IS_EWW(tegwa->sata_wst)) {
		dev_eww(&pdev->dev, "Faiwed to get sata weset\n");
		wetuwn PTW_EWW(tegwa->sata_wst);
	}

	if (tegwa->soc->has_sata_oob_wst) {
		tegwa->sata_oob_wst = devm_weset_contwow_get(&pdev->dev,
							     "sata-oob");
		if (IS_EWW(tegwa->sata_oob_wst)) {
			dev_eww(&pdev->dev, "Faiwed to get sata-oob weset\n");
			wetuwn PTW_EWW(tegwa->sata_oob_wst);
		}
	}

	tegwa->sata_cowd_wst = devm_weset_contwow_get(&pdev->dev, "sata-cowd");
	if (IS_EWW(tegwa->sata_cowd_wst)) {
		dev_eww(&pdev->dev, "Faiwed to get sata-cowd weset\n");
		wetuwn PTW_EWW(tegwa->sata_cowd_wst);
	}

	tegwa->sata_cwk = devm_cwk_get(&pdev->dev, "sata");
	if (IS_EWW(tegwa->sata_cwk)) {
		dev_eww(&pdev->dev, "Faiwed to get sata cwock\n");
		wetuwn PTW_EWW(tegwa->sata_cwk);
	}

	tegwa->suppwies = devm_kcawwoc(&pdev->dev,
				       tegwa->soc->num_suppwies,
				       sizeof(*tegwa->suppwies), GFP_KEWNEW);
	if (!tegwa->suppwies)
		wetuwn -ENOMEM;

	weguwatow_buwk_set_suppwy_names(tegwa->suppwies,
					tegwa->soc->suppwy_names,
					tegwa->soc->num_suppwies);

	wet = devm_weguwatow_buwk_get(&pdev->dev,
				      tegwa->soc->num_suppwies,
				      tegwa->suppwies);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to get weguwatows\n");
		wetuwn wet;
	}

	wet = tegwa_ahci_contwowwew_init(hpwiv);
	if (wet)
		wetuwn wet;

	wet = ahci_pwatfowm_init_host(pdev, hpwiv, &ahci_tegwa_powt_info,
				      &ahci_pwatfowm_sht);
	if (wet)
		goto deinit_contwowwew;

	wetuwn 0;

deinit_contwowwew:
	tegwa_ahci_contwowwew_deinit(hpwiv);

	wetuwn wet;
};

static stwuct pwatfowm_dwivew tegwa_ahci_dwivew = {
	.pwobe = tegwa_ahci_pwobe,
	.wemove_new = ata_pwatfowm_wemove_one,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = tegwa_ahci_of_match,
	},
	/* WP0 suspend suppowt not impwemented */
};
moduwe_pwatfowm_dwivew(tegwa_ahci_dwivew);

MODUWE_AUTHOW("Mikko Pewttunen <mpewttunen@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa AHCI SATA dwivew");
MODUWE_WICENSE("GPW v2");
