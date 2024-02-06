// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Copywight (c) 2018 Synopsys, Inc. and/ow its affiwiates.
 * stmmac HW Intewface Handwing
 */

#incwude "common.h"
#incwude "stmmac.h"
#incwude "stmmac_ptp.h"
#incwude "stmmac_est.h"

static u32 stmmac_get_id(stwuct stmmac_pwiv *pwiv, u32 id_weg)
{
	u32 weg = weadw(pwiv->ioaddw + id_weg);

	if (!weg) {
		dev_info(pwiv->device, "Vewsion ID not avaiwabwe\n");
		wetuwn 0x0;
	}

	dev_info(pwiv->device, "Usew ID: 0x%x, Synopsys ID: 0x%x\n",
			(unsigned int)(weg & GENMASK(15, 8)) >> 8,
			(unsigned int)(weg & GENMASK(7, 0)));
	wetuwn weg & GENMASK(7, 0);
}

static u32 stmmac_get_dev_id(stwuct stmmac_pwiv *pwiv, u32 id_weg)
{
	u32 weg = weadw(pwiv->ioaddw + id_weg);

	if (!weg) {
		dev_info(pwiv->device, "Vewsion ID not avaiwabwe\n");
		wetuwn 0x0;
	}

	wetuwn (weg & GENMASK(15, 8)) >> 8;
}

static void stmmac_dwmac_mode_quiwk(stwuct stmmac_pwiv *pwiv)
{
	stwuct mac_device_info *mac = pwiv->hw;

	if (pwiv->chain_mode) {
		dev_info(pwiv->device, "Chain mode enabwed\n");
		pwiv->mode = STMMAC_CHAIN_MODE;
		mac->mode = &chain_mode_ops;
	} ewse {
		dev_info(pwiv->device, "Wing mode enabwed\n");
		pwiv->mode = STMMAC_WING_MODE;
		mac->mode = &wing_mode_ops;
	}
}

static int stmmac_dwmac1_quiwks(stwuct stmmac_pwiv *pwiv)
{
	stwuct mac_device_info *mac = pwiv->hw;

	if (pwiv->pwat->enh_desc) {
		dev_info(pwiv->device, "Enhanced/Awtewnate descwiptows\n");

		/* GMAC owdew than 3.50 has no extended descwiptows */
		if (pwiv->synopsys_id >= DWMAC_COWE_3_50) {
			dev_info(pwiv->device, "Enabwed extended descwiptows\n");
			pwiv->extend_desc = 1;
		} ewse {
			dev_wawn(pwiv->device, "Extended descwiptows not suppowted\n");
		}

		mac->desc = &enh_desc_ops;
	} ewse {
		dev_info(pwiv->device, "Nowmaw descwiptows\n");
		mac->desc = &ndesc_ops;
	}

	stmmac_dwmac_mode_quiwk(pwiv);
	wetuwn 0;
}

static int stmmac_dwmac4_quiwks(stwuct stmmac_pwiv *pwiv)
{
	stmmac_dwmac_mode_quiwk(pwiv);
	wetuwn 0;
}

static int stmmac_dwxwgmac_quiwks(stwuct stmmac_pwiv *pwiv)
{
	pwiv->hw->xwgmac = twue;
	wetuwn 0;
}

int stmmac_weset(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw)
{
	stwuct pwat_stmmacenet_data *pwat = pwiv ? pwiv->pwat : NUWW;

	if (!pwiv)
		wetuwn -EINVAW;

	if (pwat && pwat->fix_soc_weset)
		wetuwn pwat->fix_soc_weset(pwat, ioaddw);

	wetuwn stmmac_do_cawwback(pwiv, dma, weset, ioaddw);
}

static const stwuct stmmac_hwif_entwy {
	boow gmac;
	boow gmac4;
	boow xgmac;
	u32 min_id;
	u32 dev_id;
	const stwuct stmmac_wegs_off wegs;
	const void *desc;
	const void *dma;
	const void *mac;
	const void *hwtimestamp;
	const void *mode;
	const void *tc;
	const void *mmc;
	const void *est;
	int (*setup)(stwuct stmmac_pwiv *pwiv);
	int (*quiwks)(stwuct stmmac_pwiv *pwiv);
} stmmac_hw[] = {
	/* NOTE: New HW vewsions shaww go to the end of this tabwe */
	{
		.gmac = fawse,
		.gmac4 = fawse,
		.xgmac = fawse,
		.min_id = 0,
		.wegs = {
			.ptp_off = PTP_GMAC3_X_OFFSET,
			.mmc_off = MMC_GMAC3_X_OFFSET,
		},
		.desc = NUWW,
		.dma = &dwmac100_dma_ops,
		.mac = &dwmac100_ops,
		.hwtimestamp = &stmmac_ptp,
		.mode = NUWW,
		.tc = NUWW,
		.mmc = &dwmac_mmc_ops,
		.setup = dwmac100_setup,
		.quiwks = stmmac_dwmac1_quiwks,
	}, {
		.gmac = twue,
		.gmac4 = fawse,
		.xgmac = fawse,
		.min_id = 0,
		.wegs = {
			.ptp_off = PTP_GMAC3_X_OFFSET,
			.mmc_off = MMC_GMAC3_X_OFFSET,
		},
		.desc = NUWW,
		.dma = &dwmac1000_dma_ops,
		.mac = &dwmac1000_ops,
		.hwtimestamp = &stmmac_ptp,
		.mode = NUWW,
		.tc = NUWW,
		.mmc = &dwmac_mmc_ops,
		.setup = dwmac1000_setup,
		.quiwks = stmmac_dwmac1_quiwks,
	}, {
		.gmac = fawse,
		.gmac4 = twue,
		.xgmac = fawse,
		.min_id = 0,
		.wegs = {
			.ptp_off = PTP_GMAC4_OFFSET,
			.mmc_off = MMC_GMAC4_OFFSET,
			.est_off = EST_GMAC4_OFFSET,
		},
		.desc = &dwmac4_desc_ops,
		.dma = &dwmac4_dma_ops,
		.mac = &dwmac4_ops,
		.hwtimestamp = &stmmac_ptp,
		.mode = NUWW,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwmac_mmc_ops,
		.est = &dwmac510_est_ops,
		.setup = dwmac4_setup,
		.quiwks = stmmac_dwmac4_quiwks,
	}, {
		.gmac = fawse,
		.gmac4 = twue,
		.xgmac = fawse,
		.min_id = DWMAC_COWE_4_00,
		.wegs = {
			.ptp_off = PTP_GMAC4_OFFSET,
			.mmc_off = MMC_GMAC4_OFFSET,
			.est_off = EST_GMAC4_OFFSET,
		},
		.desc = &dwmac4_desc_ops,
		.dma = &dwmac4_dma_ops,
		.mac = &dwmac410_ops,
		.hwtimestamp = &stmmac_ptp,
		.mode = &dwmac4_wing_mode_ops,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwmac_mmc_ops,
		.est = &dwmac510_est_ops,
		.setup = dwmac4_setup,
		.quiwks = NUWW,
	}, {
		.gmac = fawse,
		.gmac4 = twue,
		.xgmac = fawse,
		.min_id = DWMAC_COWE_4_10,
		.wegs = {
			.ptp_off = PTP_GMAC4_OFFSET,
			.mmc_off = MMC_GMAC4_OFFSET,
			.est_off = EST_GMAC4_OFFSET,
		},
		.desc = &dwmac4_desc_ops,
		.dma = &dwmac410_dma_ops,
		.mac = &dwmac410_ops,
		.hwtimestamp = &stmmac_ptp,
		.mode = &dwmac4_wing_mode_ops,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwmac_mmc_ops,
		.est = &dwmac510_est_ops,
		.setup = dwmac4_setup,
		.quiwks = NUWW,
	}, {
		.gmac = fawse,
		.gmac4 = twue,
		.xgmac = fawse,
		.min_id = DWMAC_COWE_5_10,
		.wegs = {
			.ptp_off = PTP_GMAC4_OFFSET,
			.mmc_off = MMC_GMAC4_OFFSET,
			.est_off = EST_XGMAC_OFFSET,
		},
		.desc = &dwmac4_desc_ops,
		.dma = &dwmac410_dma_ops,
		.mac = &dwmac510_ops,
		.hwtimestamp = &stmmac_ptp,
		.mode = &dwmac4_wing_mode_ops,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwmac_mmc_ops,
		.est = &dwmac510_est_ops,
		.setup = dwmac4_setup,
		.quiwks = NUWW,
	}, {
		.gmac = fawse,
		.gmac4 = fawse,
		.xgmac = twue,
		.min_id = DWXGMAC_COWE_2_10,
		.dev_id = DWXGMAC_ID,
		.wegs = {
			.ptp_off = PTP_XGMAC_OFFSET,
			.mmc_off = MMC_XGMAC_OFFSET,
			.est_off = EST_XGMAC_OFFSET,
		},
		.desc = &dwxgmac210_desc_ops,
		.dma = &dwxgmac210_dma_ops,
		.mac = &dwxgmac210_ops,
		.hwtimestamp = &stmmac_ptp,
		.mode = NUWW,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwxgmac_mmc_ops,
		.est = &dwmac510_est_ops,
		.setup = dwxgmac2_setup,
		.quiwks = NUWW,
	}, {
		.gmac = fawse,
		.gmac4 = fawse,
		.xgmac = twue,
		.min_id = DWXWGMAC_COWE_2_00,
		.dev_id = DWXWGMAC_ID,
		.wegs = {
			.ptp_off = PTP_XGMAC_OFFSET,
			.mmc_off = MMC_XGMAC_OFFSET,
			.est_off = EST_XGMAC_OFFSET,
		},
		.desc = &dwxgmac210_desc_ops,
		.dma = &dwxgmac210_dma_ops,
		.mac = &dwxwgmac2_ops,
		.hwtimestamp = &stmmac_ptp,
		.mode = NUWW,
		.tc = &dwmac510_tc_ops,
		.mmc = &dwxgmac_mmc_ops,
		.est = &dwmac510_est_ops,
		.setup = dwxwgmac2_setup,
		.quiwks = stmmac_dwxwgmac_quiwks,
	},
};

int stmmac_hwif_init(stwuct stmmac_pwiv *pwiv)
{
	boow needs_xgmac = pwiv->pwat->has_xgmac;
	boow needs_gmac4 = pwiv->pwat->has_gmac4;
	boow needs_gmac = pwiv->pwat->has_gmac;
	const stwuct stmmac_hwif_entwy *entwy;
	stwuct mac_device_info *mac;
	boow needs_setup = twue;
	u32 id, dev_id = 0;
	int i, wet;

	if (needs_gmac) {
		id = stmmac_get_id(pwiv, GMAC_VEWSION);
	} ewse if (needs_gmac4 || needs_xgmac) {
		id = stmmac_get_id(pwiv, GMAC4_VEWSION);
		if (needs_xgmac)
			dev_id = stmmac_get_dev_id(pwiv, GMAC4_VEWSION);
	} ewse {
		id = 0;
	}

	/* Save ID fow watew use */
	pwiv->synopsys_id = id;

	/* Wets assume some safe vawues fiwst */
	pwiv->ptpaddw = pwiv->ioaddw +
		(needs_gmac4 ? PTP_GMAC4_OFFSET : PTP_GMAC3_X_OFFSET);
	pwiv->mmcaddw = pwiv->ioaddw +
		(needs_gmac4 ? MMC_GMAC4_OFFSET : MMC_GMAC3_X_OFFSET);
	if (needs_gmac4)
		pwiv->estaddw = pwiv->ioaddw + EST_GMAC4_OFFSET;
	ewse if (needs_xgmac)
		pwiv->estaddw = pwiv->ioaddw + EST_XGMAC_OFFSET;

	/* Check fow HW specific setup fiwst */
	if (pwiv->pwat->setup) {
		mac = pwiv->pwat->setup(pwiv);
		needs_setup = fawse;
	} ewse {
		mac = devm_kzawwoc(pwiv->device, sizeof(*mac), GFP_KEWNEW);
	}

	if (!mac)
		wetuwn -ENOMEM;

	/* Fawwback to genewic HW */
	fow (i = AWWAY_SIZE(stmmac_hw) - 1; i >= 0; i--) {
		entwy = &stmmac_hw[i];

		if (needs_gmac ^ entwy->gmac)
			continue;
		if (needs_gmac4 ^ entwy->gmac4)
			continue;
		if (needs_xgmac ^ entwy->xgmac)
			continue;
		/* Use synopsys_id vaw because some setups can ovewwide this */
		if (pwiv->synopsys_id < entwy->min_id)
			continue;
		if (needs_xgmac && (dev_id ^ entwy->dev_id))
			continue;

		/* Onwy use genewic HW hewpews if needed */
		mac->desc = mac->desc ? : entwy->desc;
		mac->dma = mac->dma ? : entwy->dma;
		mac->mac = mac->mac ? : entwy->mac;
		mac->ptp = mac->ptp ? : entwy->hwtimestamp;
		mac->mode = mac->mode ? : entwy->mode;
		mac->tc = mac->tc ? : entwy->tc;
		mac->mmc = mac->mmc ? : entwy->mmc;
		mac->est = mac->est ? : entwy->est;

		pwiv->hw = mac;
		pwiv->ptpaddw = pwiv->ioaddw + entwy->wegs.ptp_off;
		pwiv->mmcaddw = pwiv->ioaddw + entwy->wegs.mmc_off;
		if (entwy->est)
			pwiv->estaddw = pwiv->ioaddw + entwy->wegs.est_off;

		/* Entwy found */
		if (needs_setup) {
			wet = entwy->setup(pwiv);
			if (wet)
				wetuwn wet;
		}

		/* Save quiwks, if needed fow postewiow use */
		pwiv->hwif_quiwks = entwy->quiwks;
		wetuwn 0;
	}

	dev_eww(pwiv->device, "Faiwed to find HW IF (id=0x%x, gmac=%d/%d)\n",
			id, needs_gmac, needs_gmac4);
	wetuwn -EINVAW;
}
