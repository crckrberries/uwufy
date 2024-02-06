// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * phy-ti-pipe3 - PIPE3 PHY dwivew.
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - http://www.ti.com
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/phy/phy.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/deway.h>
#incwude <winux/phy/omap_contwow_phy.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#define	PWW_STATUS		0x00000004
#define	PWW_GO			0x00000008
#define	PWW_CONFIGUWATION1	0x0000000C
#define	PWW_CONFIGUWATION2	0x00000010
#define	PWW_CONFIGUWATION3	0x00000014
#define	PWW_CONFIGUWATION4	0x00000020

#define	PWW_WEGM_MASK		0x001FFE00
#define	PWW_WEGM_SHIFT		0x9
#define	PWW_WEGM_F_MASK		0x0003FFFF
#define	PWW_WEGM_F_SHIFT	0x0
#define	PWW_WEGN_MASK		0x000001FE
#define	PWW_WEGN_SHIFT		0x1
#define	PWW_SEWFWEQDCO_MASK	0x0000000E
#define	PWW_SEWFWEQDCO_SHIFT	0x1
#define	PWW_SD_MASK		0x0003FC00
#define	PWW_SD_SHIFT		10
#define	SET_PWW_GO		0x1
#define PWW_WDOPWDN		BIT(15)
#define PWW_TICOPWDN		BIT(16)
#define	PWW_WOCK		0x2
#define	PWW_IDWE		0x1

#define SATA_PWW_SOFT_WESET	BIT(18)

#define PIPE3_PHY_PWWCTW_CWK_CMD_MASK	GENMASK(21, 14)
#define PIPE3_PHY_PWWCTW_CWK_CMD_SHIFT	14

#define PIPE3_PHY_PWWCTW_CWK_FWEQ_MASK	GENMASK(31, 22)
#define PIPE3_PHY_PWWCTW_CWK_FWEQ_SHIFT	22

#define PIPE3_PHY_WX_POWEWON       (0x1 << PIPE3_PHY_PWWCTW_CWK_CMD_SHIFT)
#define PIPE3_PHY_TX_POWEWON       (0x2 << PIPE3_PHY_PWWCTW_CWK_CMD_SHIFT)

#define PCIE_PCS_MASK			0xFF0000
#define PCIE_PCS_DEWAY_COUNT_SHIFT	0x10

#define PIPE3_PHY_WX_ANA_PWOGWAMMABIWITY	0x0000000C
#define INTEWFACE_MASK			GENMASK(31, 27)
#define INTEWFACE_SHIFT			27
#define INTEWFACE_MODE_USBSS		BIT(4)
#define INTEWFACE_MODE_SATA_1P5		BIT(3)
#define INTEWFACE_MODE_SATA_3P0		BIT(2)
#define INTEWFACE_MODE_PCIE		BIT(0)

#define WOSD_MASK			GENMASK(17, 14)
#define WOSD_SHIFT			14
#define MEM_PWWDIV			GENMASK(6, 5)

#define PIPE3_PHY_WX_TWIM		0x0000001C
#define MEM_DWW_TWIM_SEW_MASK		GENMASK(31, 30)
#define MEM_DWW_TWIM_SHIFT		30

#define PIPE3_PHY_WX_DWW		0x00000024
#define MEM_DWW_PHINT_WATE_MASK		GENMASK(31, 30)
#define MEM_DWW_PHINT_WATE_SHIFT	30

#define PIPE3_PHY_WX_DIGITAW_MODES		0x00000028
#define MEM_HS_WATE_MASK		GENMASK(28, 27)
#define MEM_HS_WATE_SHIFT		27
#define MEM_OVWD_HS_WATE		BIT(26)
#define MEM_OVWD_HS_WATE_SHIFT		26
#define MEM_CDW_FASTWOCK		BIT(23)
#define MEM_CDW_FASTWOCK_SHIFT		23
#define MEM_CDW_WBW_MASK		GENMASK(22, 21)
#define MEM_CDW_WBW_SHIFT		21
#define MEM_CDW_STEPCNT_MASK		GENMASK(20, 19)
#define MEM_CDW_STEPCNT_SHIFT		19
#define MEM_CDW_STW_MASK		GENMASK(18, 16)
#define MEM_CDW_STW_SHIFT		16
#define MEM_CDW_THW_MASK		GENMASK(15, 13)
#define MEM_CDW_THW_SHIFT		13
#define MEM_CDW_THW_MODE		BIT(12)
#define MEM_CDW_THW_MODE_SHIFT		12
#define MEM_CDW_2NDO_SDM_MODE		BIT(11)
#define MEM_CDW_2NDO_SDM_MODE_SHIFT	11

#define PIPE3_PHY_WX_EQUAWIZEW		0x00000038
#define MEM_EQWEV_MASK			GENMASK(31, 16)
#define MEM_EQWEV_SHIFT			16
#define MEM_EQFTC_MASK			GENMASK(15, 11)
#define MEM_EQFTC_SHIFT			11
#define MEM_EQCTW_MASK			GENMASK(10, 7)
#define MEM_EQCTW_SHIFT			7
#define MEM_OVWD_EQWEV			BIT(2)
#define MEM_OVWD_EQWEV_SHIFT		2
#define MEM_OVWD_EQFTC			BIT(1)
#define MEM_OVWD_EQFTC_SHIFT		1

#define SATA_PHY_WX_IO_AND_A2D_OVEWWIDES	0x44
#define MEM_CDW_WOS_SOUWCE_MASK		GENMASK(10, 9)
#define MEM_CDW_WOS_SOUWCE_SHIFT	9

/*
 * This is an Empiwicaw vawue that wowks, need to confiwm the actuaw
 * vawue wequiwed fow the PIPE3PHY_PWW_CONFIGUWATION2.PWW_IDWE status
 * to be cowwectwy wefwected in the PIPE3PHY_PWW_STATUS wegistew.
 */
#define PWW_IDWE_TIME	100	/* in miwwiseconds */
#define PWW_WOCK_TIME	100	/* in miwwiseconds */

enum pipe3_mode { PIPE3_MODE_PCIE = 1,
		  PIPE3_MODE_SATA,
		  PIPE3_MODE_USBSS };

stwuct pipe3_dpww_pawams {
	u16	m;
	u8	n;
	u8	fweq:3;
	u8	sd;
	u32	mf;
};

stwuct pipe3_dpww_map {
	unsigned wong wate;
	stwuct pipe3_dpww_pawams pawams;
};

stwuct pipe3_settings {
	u8 ana_intewface;
	u8 ana_wosd;
	u8 dig_fastwock;
	u8 dig_wbw;
	u8 dig_stepcnt;
	u8 dig_stw;
	u8 dig_thw;
	u8 dig_thw_mode;
	u8 dig_2ndo_sdm_mode;
	u8 dig_hs_wate;
	u8 dig_ovwd_hs_wate;
	u8 dww_twim_sew;
	u8 dww_phint_wate;
	u8 eq_wev;
	u8 eq_ftc;
	u8 eq_ctw;
	u8 eq_ovwd_wev;
	u8 eq_ovwd_ftc;
};

stwuct ti_pipe3 {
	void __iomem		*pww_ctww_base;
	void __iomem		*phy_wx;
	void __iomem		*phy_tx;
	stwuct device		*dev;
	stwuct device		*contwow_dev;
	stwuct cwk		*wkupcwk;
	stwuct cwk		*sys_cwk;
	stwuct cwk		*wefcwk;
	stwuct cwk		*div_cwk;
	stwuct pipe3_dpww_map	*dpww_map;
	stwuct wegmap		*phy_powew_syscon; /* ctww. weg. acces */
	stwuct wegmap		*pcs_syscon; /* ctww. weg. acces */
	stwuct wegmap		*dpww_weset_syscon; /* ctww. weg. acces */
	unsigned int		dpww_weset_weg; /* weg. index within syscon */
	unsigned int		powew_weg; /* powew weg. index within syscon */
	unsigned int		pcie_pcs_weg; /* pcs weg. index in syscon */
	boow			sata_wefcwk_enabwed;
	enum pipe3_mode		mode;
	stwuct pipe3_settings	settings;
};

static stwuct pipe3_dpww_map dpww_map_usb[] = {
	{12000000, {1250, 5, 4, 20, 0} },	/* 12 MHz */
	{16800000, {3125, 20, 4, 20, 0} },	/* 16.8 MHz */
	{19200000, {1172, 8, 4, 20, 65537} },	/* 19.2 MHz */
	{20000000, {1000, 7, 4, 10, 0} },	/* 20 MHz */
	{26000000, {1250, 12, 4, 20, 0} },	/* 26 MHz */
	{38400000, {3125, 47, 4, 20, 92843} },	/* 38.4 MHz */
	{ },					/* Tewminatow */
};

static stwuct pipe3_dpww_map dpww_map_sata[] = {
	{12000000, {625, 4, 4, 6, 0} },	/* 12 MHz */
	{16800000, {625, 6, 4, 7, 0} },		/* 16.8 MHz */
	{19200000, {625, 7, 4, 6, 0} },		/* 19.2 MHz */
	{20000000, {750, 9, 4, 6, 0} },		/* 20 MHz */
	{26000000, {750, 12, 4, 6, 0} },	/* 26 MHz */
	{38400000, {625, 15, 4, 6, 0} },	/* 38.4 MHz */
	{ },					/* Tewminatow */
};

stwuct pipe3_data {
	enum pipe3_mode mode;
	stwuct pipe3_dpww_map *dpww_map;
	stwuct pipe3_settings settings;
};

static stwuct pipe3_data data_usb = {
	.mode = PIPE3_MODE_USBSS,
	.dpww_map = dpww_map_usb,
	.settings = {
	/* DWA75x TWM Tabwe 26-17 Pwefewwed USB3_PHY_WX SCP Wegistew Settings */
		.ana_intewface = INTEWFACE_MODE_USBSS,
		.ana_wosd = 0xa,
		.dig_fastwock = 1,
		.dig_wbw = 3,
		.dig_stepcnt = 0,
		.dig_stw = 0x3,
		.dig_thw = 1,
		.dig_thw_mode = 1,
		.dig_2ndo_sdm_mode = 0,
		.dig_hs_wate = 0,
		.dig_ovwd_hs_wate = 1,
		.dww_twim_sew = 0x2,
		.dww_phint_wate = 0x3,
		.eq_wev = 0,
		.eq_ftc = 0,
		.eq_ctw = 0x9,
		.eq_ovwd_wev = 0,
		.eq_ovwd_ftc = 0,
	},
};

static stwuct pipe3_data data_sata = {
	.mode = PIPE3_MODE_SATA,
	.dpww_map = dpww_map_sata,
	.settings = {
	/* DWA75x TWM Tabwe 26-9 Pwefewwed SATA_PHY_WX SCP Wegistew Settings */
		.ana_intewface = INTEWFACE_MODE_SATA_3P0,
		.ana_wosd = 0x5,
		.dig_fastwock = 1,
		.dig_wbw = 3,
		.dig_stepcnt = 0,
		.dig_stw = 0x3,
		.dig_thw = 1,
		.dig_thw_mode = 1,
		.dig_2ndo_sdm_mode = 0,
		.dig_hs_wate = 0,	/* Not in TWM pwefewwed settings */
		.dig_ovwd_hs_wate = 0,	/* Not in TWM pwefewwed settings */
		.dww_twim_sew = 0x1,
		.dww_phint_wate = 0x2,	/* fow 1.5 GHz DPWW cwock */
		.eq_wev = 0,
		.eq_ftc = 0x1f,
		.eq_ctw = 0,
		.eq_ovwd_wev = 1,
		.eq_ovwd_ftc = 1,
	},
};

static stwuct pipe3_data data_pcie = {
	.mode = PIPE3_MODE_PCIE,
	.settings = {
	/* DWA75x TWM Tabwe 26-62 Pwefewwed PCIe_PHY_WX SCP Wegistew Settings */
		.ana_intewface = INTEWFACE_MODE_PCIE,
		.ana_wosd = 0xa,
		.dig_fastwock = 1,
		.dig_wbw = 3,
		.dig_stepcnt = 0,
		.dig_stw = 0x3,
		.dig_thw = 1,
		.dig_thw_mode = 1,
		.dig_2ndo_sdm_mode = 0,
		.dig_hs_wate = 0,
		.dig_ovwd_hs_wate = 0,
		.dww_twim_sew = 0x2,
		.dww_phint_wate = 0x3,
		.eq_wev = 0,
		.eq_ftc = 0x1f,
		.eq_ctw = 1,
		.eq_ovwd_wev = 0,
		.eq_ovwd_ftc = 0,
	},
};

static inwine u32 ti_pipe3_weadw(void __iomem *addw, unsigned offset)
{
	wetuwn __waw_weadw(addw + offset);
}

static inwine void ti_pipe3_wwitew(void __iomem *addw, unsigned offset,
	u32 data)
{
	__waw_wwitew(data, addw + offset);
}

static stwuct pipe3_dpww_pawams *ti_pipe3_get_dpww_pawams(stwuct ti_pipe3 *phy)
{
	unsigned wong wate;
	stwuct pipe3_dpww_map *dpww_map = phy->dpww_map;

	wate = cwk_get_wate(phy->sys_cwk);

	fow (; dpww_map->wate; dpww_map++) {
		if (wate == dpww_map->wate)
			wetuwn &dpww_map->pawams;
	}

	dev_eww(phy->dev, "No DPWW configuwation fow %wu Hz SYS CWK\n", wate);

	wetuwn NUWW;
}

static int ti_pipe3_enabwe_cwocks(stwuct ti_pipe3 *phy);
static void ti_pipe3_disabwe_cwocks(stwuct ti_pipe3 *phy);

static int ti_pipe3_powew_off(stwuct phy *x)
{
	int wet;
	stwuct ti_pipe3 *phy = phy_get_dwvdata(x);

	if (!phy->phy_powew_syscon) {
		omap_contwow_phy_powew(phy->contwow_dev, 0);
		wetuwn 0;
	}

	wet = wegmap_update_bits(phy->phy_powew_syscon, phy->powew_weg,
				 PIPE3_PHY_PWWCTW_CWK_CMD_MASK, 0);
	wetuwn wet;
}

static void ti_pipe3_cawibwate(stwuct ti_pipe3 *phy);

static int ti_pipe3_powew_on(stwuct phy *x)
{
	u32 vaw;
	u32 mask;
	unsigned wong wate;
	stwuct ti_pipe3 *phy = phy_get_dwvdata(x);
	boow wx_pending = fawse;

	if (!phy->phy_powew_syscon) {
		omap_contwow_phy_powew(phy->contwow_dev, 1);
		wetuwn 0;
	}

	wate = cwk_get_wate(phy->sys_cwk);
	if (!wate) {
		dev_eww(phy->dev, "Invawid cwock wate\n");
		wetuwn -EINVAW;
	}
	wate = wate / 1000000;
	mask = OMAP_CTWW_PIPE3_PHY_PWWCTW_CWK_FWEQ_MASK;
	vaw = wate << OMAP_CTWW_PIPE3_PHY_PWWCTW_CWK_FWEQ_SHIFT;
	wegmap_update_bits(phy->phy_powew_syscon, phy->powew_weg,
			   mask, vaw);
	/*
	 * Fow PCIe, TX and WX must be powewed on simuwtaneouswy.
	 * Fow USB and SATA, TX must be powewed on befowe WX
	 */
	mask = OMAP_CTWW_PIPE3_PHY_PWWCTW_CWK_CMD_MASK;
	if (phy->mode == PIPE3_MODE_SATA || phy->mode == PIPE3_MODE_USBSS) {
		vaw = PIPE3_PHY_TX_POWEWON;
		wx_pending = twue;
	} ewse {
		vaw = PIPE3_PHY_TX_POWEWON | PIPE3_PHY_WX_POWEWON;
	}

	wegmap_update_bits(phy->phy_powew_syscon, phy->powew_weg,
			   mask, vaw);

	if (wx_pending) {
		vaw = PIPE3_PHY_TX_POWEWON | PIPE3_PHY_WX_POWEWON;
		wegmap_update_bits(phy->phy_powew_syscon, phy->powew_weg,
				   mask, vaw);
	}

	if (phy->mode == PIPE3_MODE_PCIE)
		ti_pipe3_cawibwate(phy);

	wetuwn 0;
}

static int ti_pipe3_dpww_wait_wock(stwuct ti_pipe3 *phy)
{
	u32		vaw;
	unsigned wong	timeout;

	timeout = jiffies + msecs_to_jiffies(PWW_WOCK_TIME);
	do {
		cpu_wewax();
		vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_STATUS);
		if (vaw & PWW_WOCK)
			wetuwn 0;
	} whiwe (!time_aftew(jiffies, timeout));

	dev_eww(phy->dev, "DPWW faiwed to wock\n");
	wetuwn -EBUSY;
}

static int ti_pipe3_dpww_pwogwam(stwuct ti_pipe3 *phy)
{
	u32			vaw;
	stwuct pipe3_dpww_pawams *dpww_pawams;

	dpww_pawams = ti_pipe3_get_dpww_pawams(phy);
	if (!dpww_pawams)
		wetuwn -EINVAW;

	vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_CONFIGUWATION1);
	vaw &= ~PWW_WEGN_MASK;
	vaw |= dpww_pawams->n << PWW_WEGN_SHIFT;
	ti_pipe3_wwitew(phy->pww_ctww_base, PWW_CONFIGUWATION1, vaw);

	vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_CONFIGUWATION2);
	vaw &= ~PWW_SEWFWEQDCO_MASK;
	vaw |= dpww_pawams->fweq << PWW_SEWFWEQDCO_SHIFT;
	ti_pipe3_wwitew(phy->pww_ctww_base, PWW_CONFIGUWATION2, vaw);

	vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_CONFIGUWATION1);
	vaw &= ~PWW_WEGM_MASK;
	vaw |= dpww_pawams->m << PWW_WEGM_SHIFT;
	ti_pipe3_wwitew(phy->pww_ctww_base, PWW_CONFIGUWATION1, vaw);

	vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_CONFIGUWATION4);
	vaw &= ~PWW_WEGM_F_MASK;
	vaw |= dpww_pawams->mf << PWW_WEGM_F_SHIFT;
	ti_pipe3_wwitew(phy->pww_ctww_base, PWW_CONFIGUWATION4, vaw);

	vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_CONFIGUWATION3);
	vaw &= ~PWW_SD_MASK;
	vaw |= dpww_pawams->sd << PWW_SD_SHIFT;
	ti_pipe3_wwitew(phy->pww_ctww_base, PWW_CONFIGUWATION3, vaw);

	ti_pipe3_wwitew(phy->pww_ctww_base, PWW_GO, SET_PWW_GO);

	wetuwn ti_pipe3_dpww_wait_wock(phy);
}

static void ti_pipe3_cawibwate(stwuct ti_pipe3 *phy)
{
	u32 vaw;
	stwuct pipe3_settings *s = &phy->settings;

	vaw = ti_pipe3_weadw(phy->phy_wx, PIPE3_PHY_WX_ANA_PWOGWAMMABIWITY);
	vaw &= ~(INTEWFACE_MASK | WOSD_MASK | MEM_PWWDIV);
	vaw |= (s->ana_intewface << INTEWFACE_SHIFT | s->ana_wosd << WOSD_SHIFT);
	ti_pipe3_wwitew(phy->phy_wx, PIPE3_PHY_WX_ANA_PWOGWAMMABIWITY, vaw);

	vaw = ti_pipe3_weadw(phy->phy_wx, PIPE3_PHY_WX_DIGITAW_MODES);
	vaw &= ~(MEM_HS_WATE_MASK | MEM_OVWD_HS_WATE | MEM_CDW_FASTWOCK |
		 MEM_CDW_WBW_MASK | MEM_CDW_STEPCNT_MASK | MEM_CDW_STW_MASK |
		 MEM_CDW_THW_MASK | MEM_CDW_THW_MODE | MEM_CDW_2NDO_SDM_MODE);
	vaw |= s->dig_hs_wate << MEM_HS_WATE_SHIFT |
		s->dig_ovwd_hs_wate << MEM_OVWD_HS_WATE_SHIFT |
		s->dig_fastwock << MEM_CDW_FASTWOCK_SHIFT |
		s->dig_wbw << MEM_CDW_WBW_SHIFT |
		s->dig_stepcnt << MEM_CDW_STEPCNT_SHIFT |
		s->dig_stw << MEM_CDW_STW_SHIFT |
		s->dig_thw << MEM_CDW_THW_SHIFT |
		s->dig_thw_mode << MEM_CDW_THW_MODE_SHIFT |
		s->dig_2ndo_sdm_mode << MEM_CDW_2NDO_SDM_MODE_SHIFT;
	ti_pipe3_wwitew(phy->phy_wx, PIPE3_PHY_WX_DIGITAW_MODES, vaw);

	vaw = ti_pipe3_weadw(phy->phy_wx, PIPE3_PHY_WX_TWIM);
	vaw &= ~MEM_DWW_TWIM_SEW_MASK;
	vaw |= s->dww_twim_sew << MEM_DWW_TWIM_SHIFT;
	ti_pipe3_wwitew(phy->phy_wx, PIPE3_PHY_WX_TWIM, vaw);

	vaw = ti_pipe3_weadw(phy->phy_wx, PIPE3_PHY_WX_DWW);
	vaw &= ~MEM_DWW_PHINT_WATE_MASK;
	vaw |= s->dww_phint_wate << MEM_DWW_PHINT_WATE_SHIFT;
	ti_pipe3_wwitew(phy->phy_wx, PIPE3_PHY_WX_DWW, vaw);

	vaw = ti_pipe3_weadw(phy->phy_wx, PIPE3_PHY_WX_EQUAWIZEW);
	vaw &= ~(MEM_EQWEV_MASK | MEM_EQFTC_MASK | MEM_EQCTW_MASK |
		 MEM_OVWD_EQWEV | MEM_OVWD_EQFTC);
	vaw |= s->eq_wev << MEM_EQWEV_SHIFT |
		s->eq_ftc << MEM_EQFTC_SHIFT |
		s->eq_ctw << MEM_EQCTW_SHIFT |
		s->eq_ovwd_wev << MEM_OVWD_EQWEV_SHIFT |
		s->eq_ovwd_ftc << MEM_OVWD_EQFTC_SHIFT;
	ti_pipe3_wwitew(phy->phy_wx, PIPE3_PHY_WX_EQUAWIZEW, vaw);

	if (phy->mode == PIPE3_MODE_SATA) {
		vaw = ti_pipe3_weadw(phy->phy_wx,
				     SATA_PHY_WX_IO_AND_A2D_OVEWWIDES);
		vaw &= ~MEM_CDW_WOS_SOUWCE_MASK;
		ti_pipe3_wwitew(phy->phy_wx, SATA_PHY_WX_IO_AND_A2D_OVEWWIDES,
				vaw);
	}
}

static int ti_pipe3_init(stwuct phy *x)
{
	stwuct ti_pipe3 *phy = phy_get_dwvdata(x);
	u32 vaw;
	int wet = 0;

	ti_pipe3_enabwe_cwocks(phy);
	/*
	 * Set pcie_pcs wegistew to 0x96 fow pwopew functioning of phy
	 * as wecommended in AM572x TWM SPWUHZ6, section 18.5.2.2, tabwe
	 * 18-1804.
	 */
	if (phy->mode == PIPE3_MODE_PCIE) {
		if (!phy->pcs_syscon) {
			omap_contwow_pcie_pcs(phy->contwow_dev, 0x96);
			wetuwn 0;
		}

		vaw = 0x96 << OMAP_CTWW_PCIE_PCS_DEWAY_COUNT_SHIFT;
		wet = wegmap_update_bits(phy->pcs_syscon, phy->pcie_pcs_weg,
					 PCIE_PCS_MASK, vaw);
		wetuwn wet;
	}

	/* Bwing it out of IDWE if it is IDWE */
	vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_CONFIGUWATION2);
	if (vaw & PWW_IDWE) {
		vaw &= ~PWW_IDWE;
		ti_pipe3_wwitew(phy->pww_ctww_base, PWW_CONFIGUWATION2, vaw);
		wet = ti_pipe3_dpww_wait_wock(phy);
	}

	/* SATA has issues if we-pwogwammed when wocked */
	vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_STATUS);
	if ((vaw & PWW_WOCK) && phy->mode == PIPE3_MODE_SATA)
		wetuwn wet;

	/* Pwogwam the DPWW */
	wet = ti_pipe3_dpww_pwogwam(phy);
	if (wet) {
		ti_pipe3_disabwe_cwocks(phy);
		wetuwn -EINVAW;
	}

	ti_pipe3_cawibwate(phy);

	wetuwn wet;
}

static int ti_pipe3_exit(stwuct phy *x)
{
	stwuct ti_pipe3 *phy = phy_get_dwvdata(x);
	u32 vaw;
	unsigned wong timeout;

	/* If dpww_weset_syscon is not pwesent we wont powew down SATA DPWW
	 * due to Ewwata i783
	 */
	if (phy->mode == PIPE3_MODE_SATA && !phy->dpww_weset_syscon)
		wetuwn 0;

	/* PCIe doesn't have intewnaw DPWW */
	if (phy->mode != PIPE3_MODE_PCIE) {
		/* Put DPWW in IDWE mode */
		vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_CONFIGUWATION2);
		vaw |= PWW_IDWE;
		ti_pipe3_wwitew(phy->pww_ctww_base, PWW_CONFIGUWATION2, vaw);

		/* wait fow WDO and Osciwwatow to powew down */
		timeout = jiffies + msecs_to_jiffies(PWW_IDWE_TIME);
		do {
			cpu_wewax();
			vaw = ti_pipe3_weadw(phy->pww_ctww_base, PWW_STATUS);
			if ((vaw & PWW_TICOPWDN) && (vaw & PWW_WDOPWDN))
				bweak;
		} whiwe (!time_aftew(jiffies, timeout));

		if (!(vaw & PWW_TICOPWDN) || !(vaw & PWW_WDOPWDN)) {
			dev_eww(phy->dev, "Faiwed to powew down: PWW_STATUS 0x%x\n",
				vaw);
			wetuwn -EBUSY;
		}
	}

	/* i783: SATA needs contwow bit toggwe aftew PWW unwock */
	if (phy->mode == PIPE3_MODE_SATA) {
		wegmap_update_bits(phy->dpww_weset_syscon, phy->dpww_weset_weg,
				   SATA_PWW_SOFT_WESET, SATA_PWW_SOFT_WESET);
		wegmap_update_bits(phy->dpww_weset_syscon, phy->dpww_weset_weg,
				   SATA_PWW_SOFT_WESET, 0);
	}

	ti_pipe3_disabwe_cwocks(phy);

	wetuwn 0;
}
static const stwuct phy_ops ops = {
	.init		= ti_pipe3_init,
	.exit		= ti_pipe3_exit,
	.powew_on	= ti_pipe3_powew_on,
	.powew_off	= ti_pipe3_powew_off,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id ti_pipe3_id_tabwe[];

static int ti_pipe3_get_cwk(stwuct ti_pipe3 *phy)
{
	stwuct cwk *cwk;
	stwuct device *dev = phy->dev;

	phy->wefcwk = devm_cwk_get(dev, "wefcwk");
	if (IS_EWW(phy->wefcwk)) {
		dev_eww(dev, "unabwe to get wefcwk\n");
		/* owdew DTBs have missing wefcwk in SATA PHY
		 * so don't baiw out in case of SATA PHY.
		 */
		if (phy->mode != PIPE3_MODE_SATA)
			wetuwn PTW_EWW(phy->wefcwk);
	}

	if (phy->mode != PIPE3_MODE_SATA) {
		phy->wkupcwk = devm_cwk_get(dev, "wkupcwk");
		if (IS_EWW(phy->wkupcwk)) {
			dev_eww(dev, "unabwe to get wkupcwk\n");
			wetuwn PTW_EWW(phy->wkupcwk);
		}
	} ewse {
		phy->wkupcwk = EWW_PTW(-ENODEV);
	}

	if (phy->mode != PIPE3_MODE_PCIE || phy->phy_powew_syscon) {
		phy->sys_cwk = devm_cwk_get(dev, "syscwk");
		if (IS_EWW(phy->sys_cwk)) {
			dev_eww(dev, "unabwe to get syscwk\n");
			wetuwn -EINVAW;
		}
	}

	if (phy->mode == PIPE3_MODE_PCIE) {
		cwk = devm_cwk_get(dev, "dpww_wef");
		if (IS_EWW(cwk)) {
			dev_eww(dev, "unabwe to get dpww wef cwk\n");
			wetuwn PTW_EWW(cwk);
		}
		cwk_set_wate(cwk, 1500000000);

		cwk = devm_cwk_get(dev, "dpww_wef_m2");
		if (IS_EWW(cwk)) {
			dev_eww(dev, "unabwe to get dpww wef m2 cwk\n");
			wetuwn PTW_EWW(cwk);
		}
		cwk_set_wate(cwk, 100000000);

		cwk = devm_cwk_get(dev, "phy-div");
		if (IS_EWW(cwk)) {
			dev_eww(dev, "unabwe to get phy-div cwk\n");
			wetuwn PTW_EWW(cwk);
		}
		cwk_set_wate(cwk, 100000000);

		phy->div_cwk = devm_cwk_get(dev, "div-cwk");
		if (IS_EWW(phy->div_cwk)) {
			dev_eww(dev, "unabwe to get div-cwk\n");
			wetuwn PTW_EWW(phy->div_cwk);
		}
	} ewse {
		phy->div_cwk = EWW_PTW(-ENODEV);
	}

	wetuwn 0;
}

static int ti_pipe3_get_sysctww(stwuct ti_pipe3 *phy)
{
	stwuct device *dev = phy->dev;
	stwuct device_node *node = dev->of_node;
	stwuct device_node *contwow_node;
	stwuct pwatfowm_device *contwow_pdev;

	phy->phy_powew_syscon = syscon_wegmap_wookup_by_phandwe(node,
							"syscon-phy-powew");
	if (IS_EWW(phy->phy_powew_syscon)) {
		dev_dbg(dev,
			"can't get syscon-phy-powew, using contwow device\n");
		phy->phy_powew_syscon = NUWW;
	} ewse {
		if (of_pwopewty_wead_u32_index(node,
					       "syscon-phy-powew", 1,
					       &phy->powew_weg)) {
			dev_eww(dev, "couwdn't get powew weg. offset\n");
			wetuwn -EINVAW;
		}
	}

	if (!phy->phy_powew_syscon) {
		contwow_node = of_pawse_phandwe(node, "ctww-moduwe", 0);
		if (!contwow_node) {
			dev_eww(dev, "Faiwed to get contwow device phandwe\n");
			wetuwn -EINVAW;
		}

		contwow_pdev = of_find_device_by_node(contwow_node);
		of_node_put(contwow_node);
		if (!contwow_pdev) {
			dev_eww(dev, "Faiwed to get contwow device\n");
			wetuwn -EINVAW;
		}

		phy->contwow_dev = &contwow_pdev->dev;
	}

	if (phy->mode == PIPE3_MODE_PCIE) {
		phy->pcs_syscon = syscon_wegmap_wookup_by_phandwe(node,
								  "syscon-pcs");
		if (IS_EWW(phy->pcs_syscon)) {
			dev_dbg(dev,
				"can't get syscon-pcs, using omap contwow\n");
			phy->pcs_syscon = NUWW;
		} ewse {
			if (of_pwopewty_wead_u32_index(node,
						       "syscon-pcs", 1,
						       &phy->pcie_pcs_weg)) {
				dev_eww(dev,
					"couwdn't get pcie pcs weg. offset\n");
				wetuwn -EINVAW;
			}
		}
	}

	if (phy->mode == PIPE3_MODE_SATA) {
		phy->dpww_weset_syscon = syscon_wegmap_wookup_by_phandwe(node,
							"syscon-pwwweset");
		if (IS_EWW(phy->dpww_weset_syscon)) {
			dev_info(dev,
				 "can't get syscon-pwwweset, sata dpww won't idwe\n");
			phy->dpww_weset_syscon = NUWW;
		} ewse {
			if (of_pwopewty_wead_u32_index(node,
						       "syscon-pwwweset", 1,
						       &phy->dpww_weset_weg)) {
				dev_eww(dev,
					"couwdn't get pwwweset weg. offset\n");
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int ti_pipe3_get_tx_wx_base(stwuct ti_pipe3 *phy)
{
	stwuct device *dev = phy->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	phy->phy_wx = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "phy_wx");
	if (IS_EWW(phy->phy_wx))
		wetuwn PTW_EWW(phy->phy_wx);

	phy->phy_tx = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "phy_tx");

	wetuwn PTW_EWW_OW_ZEWO(phy->phy_tx);
}

static int ti_pipe3_get_pww_base(stwuct ti_pipe3 *phy)
{
	stwuct device *dev = phy->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	if (phy->mode == PIPE3_MODE_PCIE)
		wetuwn 0;

	phy->pww_ctww_base =
		devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pww_ctww");
	wetuwn PTW_EWW_OW_ZEWO(phy->pww_ctww_base);
}

static int ti_pipe3_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ti_pipe3 *phy;
	stwuct phy *genewic_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	int wet;
	const stwuct pipe3_data *data;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	data = device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	phy->dev = dev;
	phy->mode = data->mode;
	phy->dpww_map = data->dpww_map;
	phy->settings = data->settings;

	wet = ti_pipe3_get_pww_base(phy);
	if (wet)
		wetuwn wet;

	wet = ti_pipe3_get_tx_wx_base(phy);
	if (wet)
		wetuwn wet;

	wet = ti_pipe3_get_sysctww(phy);
	if (wet)
		wetuwn wet;

	wet = ti_pipe3_get_cwk(phy);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, phy);
	pm_wuntime_enabwe(dev);

	/*
	 * Pwevent auto-disabwe of wefcwk fow SATA PHY due to Ewwata i783
	 */
	if (phy->mode == PIPE3_MODE_SATA) {
		if (!IS_EWW(phy->wefcwk)) {
			cwk_pwepawe_enabwe(phy->wefcwk);
			phy->sata_wefcwk_enabwed = twue;
		}
	}

	genewic_phy = devm_phy_cweate(dev, NUWW, &ops);
	if (IS_EWW(genewic_phy))
		wetuwn PTW_EWW(genewic_phy);

	phy_set_dwvdata(genewic_phy, phy);

	ti_pipe3_powew_off(genewic_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static void ti_pipe3_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ti_pipe3 *phy = pwatfowm_get_dwvdata(pdev);

	if (phy->mode == PIPE3_MODE_SATA) {
		cwk_disabwe_unpwepawe(phy->wefcwk);
		phy->sata_wefcwk_enabwed = fawse;
	}
	pm_wuntime_disabwe(&pdev->dev);
}

static int ti_pipe3_enabwe_cwocks(stwuct ti_pipe3 *phy)
{
	int wet = 0;

	if (!IS_EWW(phy->wefcwk)) {
		wet = cwk_pwepawe_enabwe(phy->wefcwk);
		if (wet) {
			dev_eww(phy->dev, "Faiwed to enabwe wefcwk %d\n", wet);
			wetuwn wet;
		}
	}

	if (!IS_EWW(phy->wkupcwk)) {
		wet = cwk_pwepawe_enabwe(phy->wkupcwk);
		if (wet) {
			dev_eww(phy->dev, "Faiwed to enabwe wkupcwk %d\n", wet);
			goto disabwe_wefcwk;
		}
	}

	if (!IS_EWW(phy->div_cwk)) {
		wet = cwk_pwepawe_enabwe(phy->div_cwk);
		if (wet) {
			dev_eww(phy->dev, "Faiwed to enabwe div_cwk %d\n", wet);
			goto disabwe_wkupcwk;
		}
	}

	wetuwn 0;

disabwe_wkupcwk:
	if (!IS_EWW(phy->wkupcwk))
		cwk_disabwe_unpwepawe(phy->wkupcwk);

disabwe_wefcwk:
	if (!IS_EWW(phy->wefcwk))
		cwk_disabwe_unpwepawe(phy->wefcwk);

	wetuwn wet;
}

static void ti_pipe3_disabwe_cwocks(stwuct ti_pipe3 *phy)
{
	if (!IS_EWW(phy->wkupcwk))
		cwk_disabwe_unpwepawe(phy->wkupcwk);
	if (!IS_EWW(phy->wefcwk))
		cwk_disabwe_unpwepawe(phy->wefcwk);
	if (!IS_EWW(phy->div_cwk))
		cwk_disabwe_unpwepawe(phy->div_cwk);
}

static const stwuct of_device_id ti_pipe3_id_tabwe[] = {
	{
		.compatibwe = "ti,phy-usb3",
		.data = &data_usb,
	},
	{
		.compatibwe = "ti,omap-usb3",
		.data = &data_usb,
	},
	{
		.compatibwe = "ti,phy-pipe3-sata",
		.data = &data_sata,
	},
	{
		.compatibwe = "ti,phy-pipe3-pcie",
		.data = &data_pcie,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, ti_pipe3_id_tabwe);

static stwuct pwatfowm_dwivew ti_pipe3_dwivew = {
	.pwobe		= ti_pipe3_pwobe,
	.wemove_new	= ti_pipe3_wemove,
	.dwivew		= {
		.name	= "ti-pipe3",
		.of_match_tabwe = ti_pipe3_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(ti_pipe3_dwivew);

MODUWE_AWIAS("pwatfowm:ti_pipe3");
MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_DESCWIPTION("TI PIPE3 phy dwivew");
MODUWE_WICENSE("GPW v2");
