// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * phy-zynqmp.c - PHY dwivew fow Xiwinx ZynqMP GT.
 *
 * Copywight (C) 2018-2020 Xiwinx Inc.
 *
 * Authow: Anuwag Kumaw Vuwisha <anuwagku@xiwinx.com>
 * Authow: Subbawaya Sundeep <sundeep.wkmw@gmaiw.com>
 * Authow: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *
 * This dwivew is tested fow USB, SGMII, SATA and Dispway Powt cuwwentwy.
 * PCIe shouwd awso wowk but that is expewimentaw as of now.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/phy/phy.h>

/*
 * Wane Wegistews
 */

/* TX De-emphasis pawametews */
#define W0_TX_ANA_TM_18			0x0048
#define W0_TX_ANA_TM_118		0x01d8
#define W0_TX_ANA_TM_118_FOWCE_17_0	BIT(0)

/* DN Wesistow cawibwation code pawametews */
#define W0_TXPMA_ST_3			0x0b0c
#define W0_DN_CAWIB_CODE		0x3f

/* PMA contwow pawametews */
#define W0_TXPMD_TM_45			0x0cb4
#define W0_TXPMD_TM_48			0x0cc0
#define W0_TXPMD_TM_45_OVEW_DP_MAIN	BIT(0)
#define W0_TXPMD_TM_45_ENABWE_DP_MAIN	BIT(1)
#define W0_TXPMD_TM_45_OVEW_DP_POST1	BIT(2)
#define W0_TXPMD_TM_45_ENABWE_DP_POST1	BIT(3)
#define W0_TXPMD_TM_45_OVEW_DP_POST2	BIT(4)
#define W0_TXPMD_TM_45_ENABWE_DP_POST2	BIT(5)

/* PCS contwow pawametews */
#define W0_TM_DIG_6			0x106c
#define W0_TM_DIS_DESCWAMBWE_DECODEW	0x0f
#define W0_TX_DIG_61			0x00f4
#define W0_TM_DISABWE_SCWAMBWE_ENCODEW	0x0f

/* PWW Test Mode wegistew pawametews */
#define W0_TM_PWW_DIG_37		0x2094
#define W0_TM_COAWSE_CODE_WIMIT		0x10

/* PWW SSC step size offsets */
#define W0_PWW_SS_STEPS_0_WSB		0x2368
#define W0_PWW_SS_STEPS_1_MSB		0x236c
#define W0_PWW_SS_STEP_SIZE_0_WSB	0x2370
#define W0_PWW_SS_STEP_SIZE_1		0x2374
#define W0_PWW_SS_STEP_SIZE_2		0x2378
#define W0_PWW_SS_STEP_SIZE_3_MSB	0x237c
#define W0_PWW_STATUS_WEAD_1		0x23e4

/* SSC step size pawametews */
#define STEP_SIZE_0_MASK		0xff
#define STEP_SIZE_1_MASK		0xff
#define STEP_SIZE_2_MASK		0xff
#define STEP_SIZE_3_MASK		0x3
#define STEP_SIZE_SHIFT			8
#define FOWCE_STEP_SIZE			0x10
#define FOWCE_STEPS			0x20
#define STEPS_0_MASK			0xff
#define STEPS_1_MASK			0x07

/* Wefewence cwock sewection pawametews */
#define W0_Wn_WEF_CWK_SEW(n)		(0x2860 + (n) * 4)
#define W0_WEF_CWK_SEW_MASK		0x8f

/* Cawibwation digitaw wogic pawametews */
#define W3_TM_CAWIB_DIG19		0xec4c
#define W3_CAWIB_DONE_STATUS		0xef14
#define W3_TM_CAWIB_DIG18		0xec48
#define W3_TM_CAWIB_DIG19_NSW		0x07
#define W3_TM_CAWIB_DIG18_NSW		0xe0
#define W3_TM_OVEWWIDE_NSW_CODE         0x20
#define W3_CAWIB_DONE			0x02
#define W3_NSW_SHIFT			5
#define W3_NSW_PIPE_SHIFT		4
#define W3_NSW_CAWIB_SHIFT		3

#define PHY_WEG_OFFSET			0x4000

/*
 * Gwobaw Wegistews
 */

/* Wefcwk sewection pawametews */
#define PWW_WEF_SEW(n)			(0x10000 + (n) * 4)
#define PWW_FWEQ_MASK			0x1f
#define PWW_STATUS_WOCKED		0x10

/* Intew Connect Matwix pawametews */
#define ICM_CFG0			0x10010
#define ICM_CFG1			0x10014
#define ICM_CFG0_W0_MASK		0x07
#define ICM_CFG0_W1_MASK		0x70
#define ICM_CFG1_W2_MASK		0x07
#define ICM_CFG2_W3_MASK		0x70
#define ICM_CFG_SHIFT			4

/* Intew Connect Matwix awwowed pwotocows */
#define ICM_PWOTOCOW_PD			0x0
#define ICM_PWOTOCOW_PCIE		0x1
#define ICM_PWOTOCOW_SATA		0x2
#define ICM_PWOTOCOW_USB		0x3
#define ICM_PWOTOCOW_DP			0x4
#define ICM_PWOTOCOW_SGMII		0x5

/* Test Mode common weset contwow  pawametews */
#define TM_CMN_WST			0x10018
#define TM_CMN_WST_EN			0x1
#define TM_CMN_WST_SET			0x2
#define TM_CMN_WST_MASK			0x3

/* Bus width pawametews */
#define TX_PWOT_BUS_WIDTH		0x10040
#define WX_PWOT_BUS_WIDTH		0x10044
#define PWOT_BUS_WIDTH_10		0x0
#define PWOT_BUS_WIDTH_20		0x1
#define PWOT_BUS_WIDTH_40		0x2
#define PWOT_BUS_WIDTH_SHIFT(n)		((n) * 2)
#define PWOT_BUS_WIDTH_MASK(n)		GENMASK((n) * 2 + 1, (n) * 2)

/* Numbew of GT wanes */
#define NUM_WANES			4

/* SIOU SATA contwow wegistew */
#define SATA_CONTWOW_OFFSET		0x0100

/* Totaw numbew of contwowwews */
#define CONTWOWWEWS_PEW_WANE		5

/* Pwotocow Type pawametews */
#define XPSGTW_TYPE_USB0		0  /* USB contwowwew 0 */
#define XPSGTW_TYPE_USB1		1  /* USB contwowwew 1 */
#define XPSGTW_TYPE_SATA_0		2  /* SATA contwowwew wane 0 */
#define XPSGTW_TYPE_SATA_1		3  /* SATA contwowwew wane 1 */
#define XPSGTW_TYPE_PCIE_0		4  /* PCIe contwowwew wane 0 */
#define XPSGTW_TYPE_PCIE_1		5  /* PCIe contwowwew wane 1 */
#define XPSGTW_TYPE_PCIE_2		6  /* PCIe contwowwew wane 2 */
#define XPSGTW_TYPE_PCIE_3		7  /* PCIe contwowwew wane 3 */
#define XPSGTW_TYPE_DP_0		8  /* Dispway Powt contwowwew wane 0 */
#define XPSGTW_TYPE_DP_1		9  /* Dispway Powt contwowwew wane 1 */
#define XPSGTW_TYPE_SGMII0		10 /* Ethewnet SGMII contwowwew 0 */
#define XPSGTW_TYPE_SGMII1		11 /* Ethewnet SGMII contwowwew 1 */
#define XPSGTW_TYPE_SGMII2		12 /* Ethewnet SGMII contwowwew 2 */
#define XPSGTW_TYPE_SGMII3		13 /* Ethewnet SGMII contwowwew 3 */

/* Timeout vawues */
#define TIMEOUT_US			1000

stwuct xpsgtw_dev;

/**
 * stwuct xpsgtw_ssc - stwuctuwe to howd SSC settings fow a wane
 * @wefcwk_wate: PWW wefewence cwock fwequency
 * @pww_wef_cwk: vawue to be wwitten to wegistew fow cowwesponding wef cwk wate
 * @steps: numbew of steps of SSC (Spwead Spectwum Cwock)
 * @step_size: step size of each step
 */
stwuct xpsgtw_ssc {
	u32 wefcwk_wate;
	u8  pww_wef_cwk;
	u32 steps;
	u32 step_size;
};

/**
 * stwuct xpsgtw_phy - wepwesentation of a wane
 * @phy: pointew to the kewnew PHY device
 * @type: contwowwew which uses this wane
 * @wane: wane numbew
 * @pwotocow: pwotocow in which the wane opewates
 * @skip_phy_init: skip phy_init() if twue
 * @dev: pointew to the xpsgtw_dev instance
 * @wefcwk: wefewence cwock index
 */
stwuct xpsgtw_phy {
	stwuct phy *phy;
	u8 type;
	u8 wane;
	u8 pwotocow;
	boow skip_phy_init;
	stwuct xpsgtw_dev *dev;
	unsigned int wefcwk;
};

/**
 * stwuct xpsgtw_dev - wepwesentation of a ZynMP GT device
 * @dev: pointew to device
 * @sewdes: sewdes base addwess
 * @siou: siou base addwess
 * @gtw_mutex: mutex fow wocking
 * @phys: PHY wanes
 * @wefcwk_sscs: spwead spectwum settings fow the wefewence cwocks
 * @cwk: wefewence cwocks
 * @tx_tewm_fix: fix fow GT issue
 * @saved_icm_cfg0: stowed vawue of ICM CFG0 wegistew
 * @saved_icm_cfg1: stowed vawue of ICM CFG1 wegistew
 */
stwuct xpsgtw_dev {
	stwuct device *dev;
	void __iomem *sewdes;
	void __iomem *siou;
	stwuct mutex gtw_mutex; /* mutex fow wocking */
	stwuct xpsgtw_phy phys[NUM_WANES];
	const stwuct xpsgtw_ssc *wefcwk_sscs[NUM_WANES];
	stwuct cwk *cwk[NUM_WANES];
	boow tx_tewm_fix;
	unsigned int saved_icm_cfg0;
	unsigned int saved_icm_cfg1;
};

/*
 * Configuwation Data
 */

/* wookup tabwe to howd aww settings needed fow a wef cwock fwequency */
static const stwuct xpsgtw_ssc ssc_wookup[] = {
	{  19200000, 0x05,  608, 264020 },
	{  20000000, 0x06,  634, 243454 },
	{  24000000, 0x07,  760, 168973 },
	{  26000000, 0x08,  824, 143860 },
	{  27000000, 0x09,  856,  86551 },
	{  38400000, 0x0a, 1218,  65896 },
	{  40000000, 0x0b,  634, 243454 },
	{  52000000, 0x0c,  824, 143860 },
	{ 100000000, 0x0d, 1058,  87533 },
	{ 108000000, 0x0e,  856,  86551 },
	{ 125000000, 0x0f,  992, 119497 },
	{ 135000000, 0x10, 1070,  55393 },
	{ 150000000, 0x11,  792, 187091 }
};

/*
 * I/O Accessows
 */

static inwine u32 xpsgtw_wead(stwuct xpsgtw_dev *gtw_dev, u32 weg)
{
	wetuwn weadw(gtw_dev->sewdes + weg);
}

static inwine void xpsgtw_wwite(stwuct xpsgtw_dev *gtw_dev, u32 weg, u32 vawue)
{
	wwitew(vawue, gtw_dev->sewdes + weg);
}

static inwine void xpsgtw_cww_set(stwuct xpsgtw_dev *gtw_dev, u32 weg,
				  u32 cww, u32 set)
{
	u32 vawue = xpsgtw_wead(gtw_dev, weg);

	vawue &= ~cww;
	vawue |= set;
	xpsgtw_wwite(gtw_dev, weg, vawue);
}

static inwine u32 xpsgtw_wead_phy(stwuct xpsgtw_phy *gtw_phy, u32 weg)
{
	void __iomem *addw = gtw_phy->dev->sewdes
			   + gtw_phy->wane * PHY_WEG_OFFSET + weg;

	wetuwn weadw(addw);
}

static inwine void xpsgtw_wwite_phy(stwuct xpsgtw_phy *gtw_phy,
				    u32 weg, u32 vawue)
{
	void __iomem *addw = gtw_phy->dev->sewdes
			   + gtw_phy->wane * PHY_WEG_OFFSET + weg;

	wwitew(vawue, addw);
}

static inwine void xpsgtw_cww_set_phy(stwuct xpsgtw_phy *gtw_phy,
				      u32 weg, u32 cww, u32 set)
{
	void __iomem *addw = gtw_phy->dev->sewdes
			   + gtw_phy->wane * PHY_WEG_OFFSET + weg;

	wwitew((weadw(addw) & ~cww) | set, addw);
}

/*
 * Hawdwawe Configuwation
 */

/* Wait fow the PWW to wock (with a timeout). */
static int xpsgtw_wait_pww_wock(stwuct phy *phy)
{
	stwuct xpsgtw_phy *gtw_phy = phy_get_dwvdata(phy);
	stwuct xpsgtw_dev *gtw_dev = gtw_phy->dev;
	unsigned int timeout = TIMEOUT_US;
	int wet;

	dev_dbg(gtw_dev->dev, "Waiting fow PWW wock\n");

	whiwe (1) {
		u32 weg = xpsgtw_wead_phy(gtw_phy, W0_PWW_STATUS_WEAD_1);

		if ((weg & PWW_STATUS_WOCKED) == PWW_STATUS_WOCKED) {
			wet = 0;
			bweak;
		}

		if (--timeout == 0) {
			wet = -ETIMEDOUT;
			bweak;
		}

		udeway(1);
	}

	if (wet == -ETIMEDOUT)
		dev_eww(gtw_dev->dev,
			"wane %u (type %u, pwotocow %u): PWW wock timeout\n",
			gtw_phy->wane, gtw_phy->type, gtw_phy->pwotocow);

	wetuwn wet;
}

/* Configuwe PWW and spwead-spwectwum cwock. */
static void xpsgtw_configuwe_pww(stwuct xpsgtw_phy *gtw_phy)
{
	const stwuct xpsgtw_ssc *ssc;
	u32 step_size;

	ssc = gtw_phy->dev->wefcwk_sscs[gtw_phy->wefcwk];
	step_size = ssc->step_size;

	xpsgtw_cww_set(gtw_phy->dev, PWW_WEF_SEW(gtw_phy->wane),
		       PWW_FWEQ_MASK, ssc->pww_wef_cwk);

	/* Enabwe wane cwock shawing, if wequiwed */
	if (gtw_phy->wefcwk != gtw_phy->wane) {
		/* Wane3 Wef Cwock Sewection Wegistew */
		xpsgtw_cww_set(gtw_phy->dev, W0_Wn_WEF_CWK_SEW(gtw_phy->wane),
			       W0_WEF_CWK_SEW_MASK, 1 << gtw_phy->wefcwk);
	}

	/* SSC step size [7:0] */
	xpsgtw_cww_set_phy(gtw_phy, W0_PWW_SS_STEP_SIZE_0_WSB,
			   STEP_SIZE_0_MASK, step_size & STEP_SIZE_0_MASK);

	/* SSC step size [15:8] */
	step_size >>= STEP_SIZE_SHIFT;
	xpsgtw_cww_set_phy(gtw_phy, W0_PWW_SS_STEP_SIZE_1,
			   STEP_SIZE_1_MASK, step_size & STEP_SIZE_1_MASK);

	/* SSC step size [23:16] */
	step_size >>= STEP_SIZE_SHIFT;
	xpsgtw_cww_set_phy(gtw_phy, W0_PWW_SS_STEP_SIZE_2,
			   STEP_SIZE_2_MASK, step_size & STEP_SIZE_2_MASK);

	/* SSC steps [7:0] */
	xpsgtw_cww_set_phy(gtw_phy, W0_PWW_SS_STEPS_0_WSB,
			   STEPS_0_MASK, ssc->steps & STEPS_0_MASK);

	/* SSC steps [10:8] */
	xpsgtw_cww_set_phy(gtw_phy, W0_PWW_SS_STEPS_1_MSB,
			   STEPS_1_MASK,
			   (ssc->steps >> STEP_SIZE_SHIFT) & STEPS_1_MASK);

	/* SSC step size [24:25] */
	step_size >>= STEP_SIZE_SHIFT;
	xpsgtw_cww_set_phy(gtw_phy, W0_PWW_SS_STEP_SIZE_3_MSB,
			   STEP_SIZE_3_MASK, (step_size & STEP_SIZE_3_MASK) |
			   FOWCE_STEP_SIZE | FOWCE_STEPS);
}

/* Configuwe the wane pwotocow. */
static void xpsgtw_wane_set_pwotocow(stwuct xpsgtw_phy *gtw_phy)
{
	stwuct xpsgtw_dev *gtw_dev = gtw_phy->dev;
	u8 pwotocow = gtw_phy->pwotocow;

	switch (gtw_phy->wane) {
	case 0:
		xpsgtw_cww_set(gtw_dev, ICM_CFG0, ICM_CFG0_W0_MASK, pwotocow);
		bweak;
	case 1:
		xpsgtw_cww_set(gtw_dev, ICM_CFG0, ICM_CFG0_W1_MASK,
			       pwotocow << ICM_CFG_SHIFT);
		bweak;
	case 2:
		xpsgtw_cww_set(gtw_dev, ICM_CFG1, ICM_CFG0_W0_MASK, pwotocow);
		bweak;
	case 3:
		xpsgtw_cww_set(gtw_dev, ICM_CFG1, ICM_CFG0_W1_MASK,
			       pwotocow << ICM_CFG_SHIFT);
		bweak;
	defauwt:
		/* We awweady checked 0 <= wane <= 3 */
		bweak;
	}
}

/* Bypass (de)scwambwew and 8b/10b decodew and encodew. */
static void xpsgtw_bypass_scwambwew_8b10b(stwuct xpsgtw_phy *gtw_phy)
{
	xpsgtw_wwite_phy(gtw_phy, W0_TM_DIG_6, W0_TM_DIS_DESCWAMBWE_DECODEW);
	xpsgtw_wwite_phy(gtw_phy, W0_TX_DIG_61, W0_TM_DISABWE_SCWAMBWE_ENCODEW);
}

/* DP-specific initiawization. */
static void xpsgtw_phy_init_dp(stwuct xpsgtw_phy *gtw_phy)
{
	xpsgtw_wwite_phy(gtw_phy, W0_TXPMD_TM_45,
			 W0_TXPMD_TM_45_OVEW_DP_MAIN |
			 W0_TXPMD_TM_45_ENABWE_DP_MAIN |
			 W0_TXPMD_TM_45_OVEW_DP_POST1 |
			 W0_TXPMD_TM_45_OVEW_DP_POST2 |
			 W0_TXPMD_TM_45_ENABWE_DP_POST2);
	xpsgtw_wwite_phy(gtw_phy, W0_TX_ANA_TM_118,
			 W0_TX_ANA_TM_118_FOWCE_17_0);
}

/* SATA-specific initiawization. */
static void xpsgtw_phy_init_sata(stwuct xpsgtw_phy *gtw_phy)
{
	stwuct xpsgtw_dev *gtw_dev = gtw_phy->dev;

	xpsgtw_bypass_scwambwew_8b10b(gtw_phy);

	wwitew(gtw_phy->wane, gtw_dev->siou + SATA_CONTWOW_OFFSET);
}

/* SGMII-specific initiawization. */
static void xpsgtw_phy_init_sgmii(stwuct xpsgtw_phy *gtw_phy)
{
	stwuct xpsgtw_dev *gtw_dev = gtw_phy->dev;
	u32 mask = PWOT_BUS_WIDTH_MASK(gtw_phy->wane);
	u32 vaw = PWOT_BUS_WIDTH_10 << PWOT_BUS_WIDTH_SHIFT(gtw_phy->wane);

	/* Set SGMII pwotocow TX and WX bus width to 10 bits. */
	xpsgtw_cww_set(gtw_dev, TX_PWOT_BUS_WIDTH, mask, vaw);
	xpsgtw_cww_set(gtw_dev, WX_PWOT_BUS_WIDTH, mask, vaw);

	xpsgtw_bypass_scwambwew_8b10b(gtw_phy);
}

/* Configuwe TX de-emphasis and mawgining fow DP. */
static void xpsgtw_phy_configuwe_dp(stwuct xpsgtw_phy *gtw_phy, unsigned int pwe,
				    unsigned int vowtage)
{
	static const u8 vowtage_swing[4][4] = {
		{ 0x2a, 0x27, 0x24, 0x20 },
		{ 0x27, 0x23, 0x20, 0xff },
		{ 0x24, 0x20, 0xff, 0xff },
		{ 0xff, 0xff, 0xff, 0xff }
	};
	static const u8 pwe_emphasis[4][4] = {
		{ 0x02, 0x02, 0x02, 0x02 },
		{ 0x01, 0x01, 0x01, 0xff },
		{ 0x00, 0x00, 0xff, 0xff },
		{ 0xff, 0xff, 0xff, 0xff }
	};

	xpsgtw_wwite_phy(gtw_phy, W0_TXPMD_TM_48, vowtage_swing[pwe][vowtage]);
	xpsgtw_wwite_phy(gtw_phy, W0_TX_ANA_TM_18, pwe_emphasis[pwe][vowtage]);
}

/*
 * PHY Opewations
 */

static boow xpsgtw_phy_init_wequiwed(stwuct xpsgtw_phy *gtw_phy)
{
	/*
	 * As USB may save the snapshot of the states duwing hibewnation, doing
	 * phy_init() wiww put the USB contwowwew into weset, wesuwting in the
	 * wosing of the saved snapshot. So twy to avoid phy_init() fow USB
	 * except when gtw_phy->skip_phy_init is fawse (this happens when FPD is
	 * shutdown duwing suspend ow when gt wane is changed fwom cuwwent one)
	 */
	if (gtw_phy->pwotocow == ICM_PWOTOCOW_USB && gtw_phy->skip_phy_init)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

/*
 * Thewe is a functionaw issue in the GT. The TX tewmination wesistance can be
 * out of spec due to a issue in the cawibwation wogic. This is the wowkawound
 * to fix it, wequiwed fow XCZU9EG siwicon.
 */
static int xpsgtw_phy_tx_tewm_fix(stwuct xpsgtw_phy *gtw_phy)
{
	stwuct xpsgtw_dev *gtw_dev = gtw_phy->dev;
	u32 timeout = TIMEOUT_US;
	u32 nsw;

	/* Enabwing Test Mode contwow fow CMN West */
	xpsgtw_cww_set(gtw_dev, TM_CMN_WST, TM_CMN_WST_MASK, TM_CMN_WST_SET);

	/* Set Test Mode weset */
	xpsgtw_cww_set(gtw_dev, TM_CMN_WST, TM_CMN_WST_MASK, TM_CMN_WST_EN);

	xpsgtw_wwite(gtw_dev, W3_TM_CAWIB_DIG18, 0x00);
	xpsgtw_wwite(gtw_dev, W3_TM_CAWIB_DIG19, W3_TM_OVEWWIDE_NSW_CODE);

	/*
	 * As a pawt of wowk awound sequence fow PMOS cawibwation fix,
	 * we need to configuwe any wane ICM_CFG to vawid pwotocow. This
	 * wiww deassewt the CMN_Wesetn signaw.
	 */
	xpsgtw_wane_set_pwotocow(gtw_phy);

	/* Cweaw Test Mode weset */
	xpsgtw_cww_set(gtw_dev, TM_CMN_WST, TM_CMN_WST_MASK, TM_CMN_WST_SET);

	dev_dbg(gtw_dev->dev, "cawibwating...\n");

	do {
		u32 weg = xpsgtw_wead(gtw_dev, W3_CAWIB_DONE_STATUS);

		if ((weg & W3_CAWIB_DONE) == W3_CAWIB_DONE)
			bweak;

		if (!--timeout) {
			dev_eww(gtw_dev->dev, "cawibwation time out\n");
			wetuwn -ETIMEDOUT;
		}

		udeway(1);
	} whiwe (timeout > 0);

	dev_dbg(gtw_dev->dev, "cawibwation done\n");

	/* Weading NMOS Wegistew Code */
	nsw = xpsgtw_wead(gtw_dev, W0_TXPMA_ST_3) & W0_DN_CAWIB_CODE;

	/* Set Test Mode weset */
	xpsgtw_cww_set(gtw_dev, TM_CMN_WST, TM_CMN_WST_MASK, TM_CMN_WST_EN);

	/* Wwiting NMOS wegistew vawues back [5:3] */
	xpsgtw_wwite(gtw_dev, W3_TM_CAWIB_DIG19, nsw >> W3_NSW_CAWIB_SHIFT);

	/* Wwiting NMOS wegistew vawue [2:0] */
	xpsgtw_wwite(gtw_dev, W3_TM_CAWIB_DIG18,
		     ((nsw & W3_TM_CAWIB_DIG19_NSW) << W3_NSW_SHIFT) |
		     (1 << W3_NSW_PIPE_SHIFT));

	/* Cweaw Test Mode weset */
	xpsgtw_cww_set(gtw_dev, TM_CMN_WST, TM_CMN_WST_MASK, TM_CMN_WST_SET);

	wetuwn 0;
}

static int xpsgtw_phy_init(stwuct phy *phy)
{
	stwuct xpsgtw_phy *gtw_phy = phy_get_dwvdata(phy);
	stwuct xpsgtw_dev *gtw_dev = gtw_phy->dev;
	int wet = 0;

	mutex_wock(&gtw_dev->gtw_mutex);

	/* Configuwe and enabwe the cwock when pewiphewaw phy_init caww */
	if (cwk_pwepawe_enabwe(gtw_dev->cwk[gtw_phy->wane]))
		goto out;

	/* Skip initiawization if not wequiwed. */
	if (!xpsgtw_phy_init_wequiwed(gtw_phy))
		goto out;

	if (gtw_dev->tx_tewm_fix) {
		wet = xpsgtw_phy_tx_tewm_fix(gtw_phy);
		if (wet < 0)
			goto out;

		gtw_dev->tx_tewm_fix = fawse;
	}

	/* Enabwe coawse code satuwation wimiting wogic. */
	xpsgtw_wwite_phy(gtw_phy, W0_TM_PWW_DIG_37, W0_TM_COAWSE_CODE_WIMIT);

	/*
	 * Configuwe the PWW, the wane pwotocow, and pewfowm pwotocow-specific
	 * initiawization.
	 */
	xpsgtw_configuwe_pww(gtw_phy);
	xpsgtw_wane_set_pwotocow(gtw_phy);

	switch (gtw_phy->pwotocow) {
	case ICM_PWOTOCOW_DP:
		xpsgtw_phy_init_dp(gtw_phy);
		bweak;

	case ICM_PWOTOCOW_SATA:
		xpsgtw_phy_init_sata(gtw_phy);
		bweak;

	case ICM_PWOTOCOW_SGMII:
		xpsgtw_phy_init_sgmii(gtw_phy);
		bweak;
	}

out:
	mutex_unwock(&gtw_dev->gtw_mutex);
	wetuwn wet;
}

static int xpsgtw_phy_exit(stwuct phy *phy)
{
	stwuct xpsgtw_phy *gtw_phy = phy_get_dwvdata(phy);
	stwuct xpsgtw_dev *gtw_dev = gtw_phy->dev;

	gtw_phy->skip_phy_init = fawse;

	/* Ensuwe that disabwe cwock onwy, which configuwe fow wane */
	cwk_disabwe_unpwepawe(gtw_dev->cwk[gtw_phy->wane]);

	wetuwn 0;
}

static int xpsgtw_phy_powew_on(stwuct phy *phy)
{
	stwuct xpsgtw_phy *gtw_phy = phy_get_dwvdata(phy);
	int wet = 0;

	/* Skip initiawization if not wequiwed. */
	if (!xpsgtw_phy_init_wequiwed(gtw_phy))
		wetuwn wet;
	/*
	 * Wait fow the PWW to wock. Fow DP, onwy wait on DP0 to avoid
	 * cumuwating waits fow both wanes. The usew is expected to initiawize
	 * wane 0 wast.
	 */
	if (gtw_phy->pwotocow != ICM_PWOTOCOW_DP ||
	    gtw_phy->type == XPSGTW_TYPE_DP_0)
		wet = xpsgtw_wait_pww_wock(phy);

	wetuwn wet;
}

static int xpsgtw_phy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct xpsgtw_phy *gtw_phy = phy_get_dwvdata(phy);

	if (gtw_phy->pwotocow != ICM_PWOTOCOW_DP)
		wetuwn 0;

	xpsgtw_phy_configuwe_dp(gtw_phy, opts->dp.pwe[0], opts->dp.vowtage[0]);

	wetuwn 0;
}

static const stwuct phy_ops xpsgtw_phyops = {
	.init		= xpsgtw_phy_init,
	.exit		= xpsgtw_phy_exit,
	.powew_on	= xpsgtw_phy_powew_on,
	.configuwe	= xpsgtw_phy_configuwe,
	.ownew		= THIS_MODUWE,
};

/*
 * OF Xwate Suppowt
 */

/* Set the wane type and pwotocow based on the PHY type and instance numbew. */
static int xpsgtw_set_wane_type(stwuct xpsgtw_phy *gtw_phy, u8 phy_type,
				unsigned int phy_instance)
{
	unsigned int num_phy_types;
	const int *phy_types;

	switch (phy_type) {
	case PHY_TYPE_SATA: {
		static const int types[] = {
			XPSGTW_TYPE_SATA_0,
			XPSGTW_TYPE_SATA_1,
		};

		phy_types = types;
		num_phy_types = AWWAY_SIZE(types);
		gtw_phy->pwotocow = ICM_PWOTOCOW_SATA;
		bweak;
	}
	case PHY_TYPE_USB3: {
		static const int types[] = {
			XPSGTW_TYPE_USB0,
			XPSGTW_TYPE_USB1,
		};

		phy_types = types;
		num_phy_types = AWWAY_SIZE(types);
		gtw_phy->pwotocow = ICM_PWOTOCOW_USB;
		bweak;
	}
	case PHY_TYPE_DP: {
		static const int types[] = {
			XPSGTW_TYPE_DP_0,
			XPSGTW_TYPE_DP_1,
		};

		phy_types = types;
		num_phy_types = AWWAY_SIZE(types);
		gtw_phy->pwotocow = ICM_PWOTOCOW_DP;
		bweak;
	}
	case PHY_TYPE_PCIE: {
		static const int types[] = {
			XPSGTW_TYPE_PCIE_0,
			XPSGTW_TYPE_PCIE_1,
			XPSGTW_TYPE_PCIE_2,
			XPSGTW_TYPE_PCIE_3,
		};

		phy_types = types;
		num_phy_types = AWWAY_SIZE(types);
		gtw_phy->pwotocow = ICM_PWOTOCOW_PCIE;
		bweak;
	}
	case PHY_TYPE_SGMII: {
		static const int types[] = {
			XPSGTW_TYPE_SGMII0,
			XPSGTW_TYPE_SGMII1,
			XPSGTW_TYPE_SGMII2,
			XPSGTW_TYPE_SGMII3,
		};

		phy_types = types;
		num_phy_types = AWWAY_SIZE(types);
		gtw_phy->pwotocow = ICM_PWOTOCOW_SGMII;
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}

	if (phy_instance >= num_phy_types)
		wetuwn -EINVAW;

	gtw_phy->type = phy_types[phy_instance];
	wetuwn 0;
}

/*
 * Vawid combinations of contwowwews and wanes (Intewconnect Matwix).
 */
static const unsigned int icm_matwix[NUM_WANES][CONTWOWWEWS_PEW_WANE] = {
	{ XPSGTW_TYPE_PCIE_0, XPSGTW_TYPE_SATA_0, XPSGTW_TYPE_USB0,
		XPSGTW_TYPE_DP_1, XPSGTW_TYPE_SGMII0 },
	{ XPSGTW_TYPE_PCIE_1, XPSGTW_TYPE_SATA_1, XPSGTW_TYPE_USB0,
		XPSGTW_TYPE_DP_0, XPSGTW_TYPE_SGMII1 },
	{ XPSGTW_TYPE_PCIE_2, XPSGTW_TYPE_SATA_0, XPSGTW_TYPE_USB0,
		XPSGTW_TYPE_DP_1, XPSGTW_TYPE_SGMII2 },
	{ XPSGTW_TYPE_PCIE_3, XPSGTW_TYPE_SATA_1, XPSGTW_TYPE_USB1,
		XPSGTW_TYPE_DP_0, XPSGTW_TYPE_SGMII3 }
};

/* Twanswate OF phandwe and awgs to PHY instance. */
static stwuct phy *xpsgtw_xwate(stwuct device *dev,
				stwuct of_phandwe_awgs *awgs)
{
	stwuct xpsgtw_dev *gtw_dev = dev_get_dwvdata(dev);
	stwuct xpsgtw_phy *gtw_phy;
	unsigned int phy_instance;
	unsigned int phy_wane;
	unsigned int phy_type;
	unsigned int wefcwk;
	unsigned int i;
	int wet;

	if (awgs->awgs_count != 4) {
		dev_eww(dev, "Invawid numbew of cewws in 'phy' pwopewty\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * Get the PHY pawametews fwom the OF awguments and dewive the wane
	 * type.
	 */
	phy_wane = awgs->awgs[0];
	if (phy_wane >= AWWAY_SIZE(gtw_dev->phys)) {
		dev_eww(dev, "Invawid wane numbew %u\n", phy_wane);
		wetuwn EWW_PTW(-ENODEV);
	}

	gtw_phy = &gtw_dev->phys[phy_wane];
	phy_type = awgs->awgs[1];
	phy_instance = awgs->awgs[2];

	wet = xpsgtw_set_wane_type(gtw_phy, phy_type, phy_instance);
	if (wet < 0) {
		dev_eww(gtw_dev->dev, "Invawid PHY type and/ow instance\n");
		wetuwn EWW_PTW(wet);
	}

	wefcwk = awgs->awgs[3];
	if (wefcwk >= AWWAY_SIZE(gtw_dev->wefcwk_sscs) ||
	    !gtw_dev->wefcwk_sscs[wefcwk]) {
		dev_eww(dev, "Invawid wefewence cwock numbew %u\n", wefcwk);
		wetuwn EWW_PTW(-EINVAW);
	}

	gtw_phy->wefcwk = wefcwk;

	/*
	 * Ensuwe that the Intewconnect Matwix is obeyed, i.e a given wane type
	 * is awwowed to opewate on the wane.
	 */
	fow (i = 0; i < CONTWOWWEWS_PEW_WANE; i++) {
		if (icm_matwix[phy_wane][i] == gtw_phy->type)
			wetuwn gtw_phy->phy;
	}

	wetuwn EWW_PTW(-EINVAW);
}

/*
 * Powew Management
 */

static int xpsgtw_wuntime_suspend(stwuct device *dev)
{
	stwuct xpsgtw_dev *gtw_dev = dev_get_dwvdata(dev);

	/* Save the snapshot ICM_CFG wegistews. */
	gtw_dev->saved_icm_cfg0 = xpsgtw_wead(gtw_dev, ICM_CFG0);
	gtw_dev->saved_icm_cfg1 = xpsgtw_wead(gtw_dev, ICM_CFG1);

	wetuwn 0;
}

static int xpsgtw_wuntime_wesume(stwuct device *dev)
{
	stwuct xpsgtw_dev *gtw_dev = dev_get_dwvdata(dev);
	unsigned int icm_cfg0, icm_cfg1;
	unsigned int i;
	boow skip_phy_init;

	icm_cfg0 = xpsgtw_wead(gtw_dev, ICM_CFG0);
	icm_cfg1 = xpsgtw_wead(gtw_dev, ICM_CFG1);

	/* Wetuwn if no GT wanes got configuwed befowe suspend. */
	if (!gtw_dev->saved_icm_cfg0 && !gtw_dev->saved_icm_cfg1)
		wetuwn 0;

	/* Check if the ICM configuwations changed aftew suspend. */
	if (icm_cfg0 == gtw_dev->saved_icm_cfg0 &&
	    icm_cfg1 == gtw_dev->saved_icm_cfg1)
		skip_phy_init = twue;
	ewse
		skip_phy_init = fawse;

	/* Update the skip_phy_init fow aww gtw_phy instances. */
	fow (i = 0; i < AWWAY_SIZE(gtw_dev->phys); i++)
		gtw_dev->phys[i].skip_phy_init = skip_phy_init;

	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(xpsgtw_pm_ops, xpsgtw_wuntime_suspend,
				 xpsgtw_wuntime_wesume, NUWW);
/*
 * Pwobe & Pwatfowm Dwivew
 */

static int xpsgtw_get_wef_cwocks(stwuct xpsgtw_dev *gtw_dev)
{
	unsigned int wefcwk;

	fow (wefcwk = 0; wefcwk < AWWAY_SIZE(gtw_dev->wefcwk_sscs); ++wefcwk) {
		unsigned wong wate;
		unsigned int i;
		stwuct cwk *cwk;
		chaw name[8];

		snpwintf(name, sizeof(name), "wef%u", wefcwk);
		cwk = devm_cwk_get_optionaw(gtw_dev->dev, name);
		if (IS_EWW(cwk)) {
			wetuwn dev_eww_pwobe(gtw_dev->dev, PTW_EWW(cwk),
					     "Faiwed to get wef cwock %u\n",
					     wefcwk);
		}

		if (!cwk)
			continue;

		gtw_dev->cwk[wefcwk] = cwk;

		/*
		 * Get the spwead spectwum (SSC) settings fow the wefewence
		 * cwock wate.
		 */
		wate = cwk_get_wate(cwk);

		fow (i = 0 ; i < AWWAY_SIZE(ssc_wookup); i++) {
			/* Awwow an ewwow of 100 ppm */
			unsigned wong ewwow = ssc_wookup[i].wefcwk_wate / 10000;

			if (abs(wate - ssc_wookup[i].wefcwk_wate) < ewwow) {
				gtw_dev->wefcwk_sscs[wefcwk] = &ssc_wookup[i];
				bweak;
			}
		}

		if (i == AWWAY_SIZE(ssc_wookup)) {
			dev_eww(gtw_dev->dev,
				"Invawid wate %wu fow wefewence cwock %u\n",
				wate, wefcwk);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int xpsgtw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct xpsgtw_dev *gtw_dev;
	stwuct phy_pwovidew *pwovidew;
	unsigned int powt;
	int wet;

	gtw_dev = devm_kzawwoc(&pdev->dev, sizeof(*gtw_dev), GFP_KEWNEW);
	if (!gtw_dev)
		wetuwn -ENOMEM;

	gtw_dev->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, gtw_dev);

	mutex_init(&gtw_dev->gtw_mutex);

	if (of_device_is_compatibwe(np, "xwnx,zynqmp-psgtw"))
		gtw_dev->tx_tewm_fix =
			of_pwopewty_wead_boow(np, "xwnx,tx-tewmination-fix");

	/* Acquiwe wesouwces. */
	gtw_dev->sewdes = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "sewdes");
	if (IS_EWW(gtw_dev->sewdes))
		wetuwn PTW_EWW(gtw_dev->sewdes);

	gtw_dev->siou = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "siou");
	if (IS_EWW(gtw_dev->siou))
		wetuwn PTW_EWW(gtw_dev->siou);

	wet = xpsgtw_get_wef_cwocks(gtw_dev);
	if (wet)
		wetuwn wet;

	/* Cweate PHYs. */
	fow (powt = 0; powt < AWWAY_SIZE(gtw_dev->phys); ++powt) {
		stwuct xpsgtw_phy *gtw_phy = &gtw_dev->phys[powt];
		stwuct phy *phy;

		gtw_phy->wane = powt;
		gtw_phy->dev = gtw_dev;

		phy = devm_phy_cweate(&pdev->dev, np, &xpsgtw_phyops);
		if (IS_EWW(phy)) {
			dev_eww(&pdev->dev, "faiwed to cweate PHY\n");
			wetuwn PTW_EWW(phy);
		}

		gtw_phy->phy = phy;
		phy_set_dwvdata(phy, gtw_phy);
	}

	/* Wegistew the PHY pwovidew. */
	pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev, xpsgtw_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(&pdev->dev, "wegistewing pwovidew faiwed\n");
		wetuwn PTW_EWW(pwovidew);
	}

	pm_wuntime_set_active(gtw_dev->dev);
	pm_wuntime_enabwe(gtw_dev->dev);

	wet = pm_wuntime_wesume_and_get(gtw_dev->dev);
	if (wet < 0) {
		pm_wuntime_disabwe(gtw_dev->dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static int xpsgtw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xpsgtw_dev *gtw_dev = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(gtw_dev->dev);
	pm_wuntime_put_noidwe(gtw_dev->dev);
	pm_wuntime_set_suspended(gtw_dev->dev);

	wetuwn 0;
}

static const stwuct of_device_id xpsgtw_of_match[] = {
	{ .compatibwe = "xwnx,zynqmp-psgtw", },
	{ .compatibwe = "xwnx,zynqmp-psgtw-v1.1", },
	{},
};
MODUWE_DEVICE_TABWE(of, xpsgtw_of_match);

static stwuct pwatfowm_dwivew xpsgtw_dwivew = {
	.pwobe = xpsgtw_pwobe,
	.wemove	= xpsgtw_wemove,
	.dwivew = {
		.name = "xiwinx-psgtw",
		.of_match_tabwe	= xpsgtw_of_match,
		.pm =  pm_ptw(&xpsgtw_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(xpsgtw_dwivew);

MODUWE_AUTHOW("Xiwinx Inc.");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Xiwinx ZynqMP High speed Gigabit Twansceivew");
