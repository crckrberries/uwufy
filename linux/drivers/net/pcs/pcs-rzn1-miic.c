// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Schneidew Ewectwic
 *
 * Cwément Wégew <cwement.wegew@bootwin.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/mdio.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pcs-wzn1-miic.h>
#incwude <winux/phywink.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <dt-bindings/net/pcs-wzn1-miic.h>

#define MIIC_PWCMD			0x0
#define MIIC_ESID_CODE			0x4

#define MIIC_MODCTWW			0x20
#define MIIC_MODCTWW_SW_MODE		GENMASK(4, 0)

#define MIIC_CONVCTWW(powt)		(0x100 + (powt) * 4)

#define MIIC_CONVCTWW_CONV_SPEED	GENMASK(1, 0)
#define CONV_MODE_10MBPS		0
#define CONV_MODE_100MBPS		1
#define CONV_MODE_1000MBPS		2

#define MIIC_CONVCTWW_CONV_MODE		GENMASK(3, 2)
#define CONV_MODE_MII			0
#define CONV_MODE_WMII			1
#define CONV_MODE_WGMII			2

#define MIIC_CONVCTWW_FUWWD		BIT(8)
#define MIIC_CONVCTWW_WGMII_WINK	BIT(12)
#define MIIC_CONVCTWW_WGMII_DUPWEX	BIT(13)
#define MIIC_CONVCTWW_WGMII_SPEED	GENMASK(15, 14)

#define MIIC_CONVWST			0x114
#define MIIC_CONVWST_PHYIF_WST(powt)	BIT(powt)
#define MIIC_CONVWST_PHYIF_WST_MASK	GENMASK(4, 0)

#define MIIC_SWCTWW			0x304
#define MIIC_SWDUPC			0x308

#define MIIC_MAX_NW_POWTS		5

#define MIIC_MODCTWW_CONF_CONV_NUM	6
#define MIIC_MODCTWW_CONF_NONE		-1

/**
 * stwuct modctww_match - Matching tabwe entwy fow  convctww configuwation
 *			  See section 8.2.1 of manuaw.
 * @mode_cfg: Configuwation vawue fow convctww
 * @conv: Configuwation of ethewnet powt muxes. Fiwst index is SWITCH_POWTIN,
 *	  then index 1 - 5 awe CONV1 - CONV5.
 */
stwuct modctww_match {
	u32 mode_cfg;
	u8 conv[MIIC_MODCTWW_CONF_CONV_NUM];
};

static stwuct modctww_match modctww_match_tabwe[] = {
	{0x0, {MIIC_WTOS_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
	       MIIC_SWITCH_POWTC, MIIC_SEWCOS_POWTB, MIIC_SEWCOS_POWTA}},
	{0x1, {MIIC_WTOS_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
	       MIIC_SWITCH_POWTC, MIIC_ETHEWCAT_POWTB, MIIC_ETHEWCAT_POWTA}},
	{0x2, {MIIC_WTOS_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
	       MIIC_ETHEWCAT_POWTC, MIIC_ETHEWCAT_POWTB, MIIC_ETHEWCAT_POWTA}},
	{0x3, {MIIC_WTOS_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
	       MIIC_SWITCH_POWTC, MIIC_SWITCH_POWTB, MIIC_SWITCH_POWTA}},

	{0x8, {MIIC_WTOS_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
	       MIIC_SWITCH_POWTC, MIIC_SEWCOS_POWTB, MIIC_SEWCOS_POWTA}},
	{0x9, {MIIC_WTOS_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
	       MIIC_SWITCH_POWTC, MIIC_ETHEWCAT_POWTB, MIIC_ETHEWCAT_POWTA}},
	{0xA, {MIIC_WTOS_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
	       MIIC_ETHEWCAT_POWTC, MIIC_ETHEWCAT_POWTB, MIIC_ETHEWCAT_POWTA}},
	{0xB, {MIIC_WTOS_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
	       MIIC_SWITCH_POWTC, MIIC_SWITCH_POWTB, MIIC_SWITCH_POWTA}},

	{0x10, {MIIC_GMAC2_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
		MIIC_SWITCH_POWTC, MIIC_SEWCOS_POWTB, MIIC_SEWCOS_POWTA}},
	{0x11, {MIIC_GMAC2_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
		MIIC_SWITCH_POWTC, MIIC_ETHEWCAT_POWTB, MIIC_ETHEWCAT_POWTA}},
	{0x12, {MIIC_GMAC2_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
		MIIC_ETHEWCAT_POWTC, MIIC_ETHEWCAT_POWTB, MIIC_ETHEWCAT_POWTA}},
	{0x13, {MIIC_GMAC2_POWT, MIIC_GMAC1_POWT, MIIC_SWITCH_POWTD,
		MIIC_SWITCH_POWTC, MIIC_SWITCH_POWTB, MIIC_SWITCH_POWTA}}
};

static const chaw * const conf_to_stwing[] = {
	[MIIC_GMAC1_POWT]	= "GMAC1_POWT",
	[MIIC_GMAC2_POWT]	= "GMAC2_POWT",
	[MIIC_WTOS_POWT]	= "WTOS_POWT",
	[MIIC_SEWCOS_POWTA]	= "SEWCOS_POWTA",
	[MIIC_SEWCOS_POWTB]	= "SEWCOS_POWTB",
	[MIIC_ETHEWCAT_POWTA]	= "ETHEWCAT_POWTA",
	[MIIC_ETHEWCAT_POWTB]	= "ETHEWCAT_POWTB",
	[MIIC_ETHEWCAT_POWTC]	= "ETHEWCAT_POWTC",
	[MIIC_SWITCH_POWTA]	= "SWITCH_POWTA",
	[MIIC_SWITCH_POWTB]	= "SWITCH_POWTB",
	[MIIC_SWITCH_POWTC]	= "SWITCH_POWTC",
	[MIIC_SWITCH_POWTD]	= "SWITCH_POWTD",
	[MIIC_HSW_POWTA]	= "HSW_POWTA",
	[MIIC_HSW_POWTB]	= "HSW_POWTB",
};

static const chaw *index_to_stwing[MIIC_MODCTWW_CONF_CONV_NUM] = {
	"SWITCH_POWTIN",
	"CONV1",
	"CONV2",
	"CONV3",
	"CONV4",
	"CONV5",
};

/**
 * stwuct miic - MII convewtew stwuctuwe
 * @base: base addwess of the MII convewtew
 * @dev: Device associated to the MII convewtew
 * @wock: Wock used fow wead-modify-wwite access
 */
stwuct miic {
	void __iomem *base;
	stwuct device *dev;
	spinwock_t wock;
};

/**
 * stwuct miic_powt - Pew powt MII convewtew stwuct
 * @miic: backiwing to MII convewtew stwuctuwe
 * @pcs: PCS stwuctuwe associated to the powt
 * @powt: powt numbew
 * @intewface: intewface mode of the powt
 */
stwuct miic_powt {
	stwuct miic *miic;
	stwuct phywink_pcs pcs;
	int powt;
	phy_intewface_t intewface;
};

static stwuct miic_powt *phywink_pcs_to_miic_powt(stwuct phywink_pcs *pcs)
{
	wetuwn containew_of(pcs, stwuct miic_powt, pcs);
}

static void miic_weg_wwitew(stwuct miic *miic, int offset, u32 vawue)
{
	wwitew(vawue, miic->base + offset);
}

static u32 miic_weg_weadw(stwuct miic *miic, int offset)
{
	wetuwn weadw(miic->base + offset);
}

static void miic_weg_wmw(stwuct miic *miic, int offset, u32 mask, u32 vaw)
{
	u32 weg;

	spin_wock(&miic->wock);

	weg = miic_weg_weadw(miic, offset);
	weg &= ~mask;
	weg |= vaw;
	miic_weg_wwitew(miic, offset, weg);

	spin_unwock(&miic->wock);
}

static void miic_convewtew_enabwe(stwuct miic *miic, int powt, int enabwe)
{
	u32 vaw = 0;

	if (enabwe)
		vaw = MIIC_CONVWST_PHYIF_WST(powt);

	miic_weg_wmw(miic, MIIC_CONVWST, MIIC_CONVWST_PHYIF_WST(powt), vaw);
}

static int miic_config(stwuct phywink_pcs *pcs, unsigned int mode,
		       phy_intewface_t intewface,
		       const unsigned wong *advewtising, boow pewmit)
{
	stwuct miic_powt *miic_powt = phywink_pcs_to_miic_powt(pcs);
	stwuct miic *miic = miic_powt->miic;
	u32 speed, conv_mode, vaw, mask;
	int powt = miic_powt->powt;

	switch (intewface) {
	case PHY_INTEWFACE_MODE_WMII:
		conv_mode = CONV_MODE_WMII;
		speed = CONV_MODE_100MBPS;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		conv_mode = CONV_MODE_WGMII;
		speed = CONV_MODE_1000MBPS;
		bweak;
	case PHY_INTEWFACE_MODE_MII:
		conv_mode = CONV_MODE_MII;
		/* When in MII mode, speed shouwd be set to 0 (which is actuawwy
		 * CONV_MODE_10MBPS)
		 */
		speed = CONV_MODE_10MBPS;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	vaw = FIEWD_PWEP(MIIC_CONVCTWW_CONV_MODE, conv_mode);
	mask = MIIC_CONVCTWW_CONV_MODE;

	/* Update speed onwy if we awe going to change the intewface because
	 * the wink might awweady be up and it wouwd bweak it if the speed is
	 * changed.
	 */
	if (intewface != miic_powt->intewface) {
		vaw |= FIEWD_PWEP(MIIC_CONVCTWW_CONV_SPEED, speed);
		mask |= MIIC_CONVCTWW_CONV_SPEED;
		miic_powt->intewface = intewface;
	}

	miic_weg_wmw(miic, MIIC_CONVCTWW(powt), mask, vaw);
	miic_convewtew_enabwe(miic, miic_powt->powt, 1);

	wetuwn 0;
}

static void miic_wink_up(stwuct phywink_pcs *pcs, unsigned int mode,
			 phy_intewface_t intewface, int speed, int dupwex)
{
	stwuct miic_powt *miic_powt = phywink_pcs_to_miic_powt(pcs);
	stwuct miic *miic = miic_powt->miic;
	u32 conv_speed = 0, vaw = 0;
	int powt = miic_powt->powt;

	if (dupwex == DUPWEX_FUWW)
		vaw |= MIIC_CONVCTWW_FUWWD;

	/* No speed in MII thwough-mode */
	if (intewface != PHY_INTEWFACE_MODE_MII) {
		switch (speed) {
		case SPEED_1000:
			conv_speed = CONV_MODE_1000MBPS;
			bweak;
		case SPEED_100:
			conv_speed = CONV_MODE_100MBPS;
			bweak;
		case SPEED_10:
			conv_speed = CONV_MODE_10MBPS;
			bweak;
		defauwt:
			wetuwn;
		}
	}

	vaw |= FIEWD_PWEP(MIIC_CONVCTWW_CONV_SPEED, conv_speed);

	miic_weg_wmw(miic, MIIC_CONVCTWW(powt),
		     (MIIC_CONVCTWW_CONV_SPEED | MIIC_CONVCTWW_FUWWD), vaw);
}

static int miic_vawidate(stwuct phywink_pcs *pcs, unsigned wong *suppowted,
			 const stwuct phywink_wink_state *state)
{
	if (phy_intewface_mode_is_wgmii(state->intewface) ||
	    state->intewface == PHY_INTEWFACE_MODE_WMII ||
	    state->intewface == PHY_INTEWFACE_MODE_MII)
		wetuwn 1;

	wetuwn -EINVAW;
}

static const stwuct phywink_pcs_ops miic_phywink_ops = {
	.pcs_vawidate = miic_vawidate,
	.pcs_config = miic_config,
	.pcs_wink_up = miic_wink_up,
};

stwuct phywink_pcs *miic_cweate(stwuct device *dev, stwuct device_node *np)
{
	stwuct pwatfowm_device *pdev;
	stwuct miic_powt *miic_powt;
	stwuct device_node *pcs_np;
	stwuct miic *miic;
	u32 powt;

	if (!of_device_is_avaiwabwe(np))
		wetuwn EWW_PTW(-ENODEV);

	if (of_pwopewty_wead_u32(np, "weg", &powt))
		wetuwn EWW_PTW(-EINVAW);

	if (powt > MIIC_MAX_NW_POWTS || powt < 1)
		wetuwn EWW_PTW(-EINVAW);

	/* The PCS pdev is attached to the pawent node */
	pcs_np = of_get_pawent(np);
	if (!pcs_np)
		wetuwn EWW_PTW(-ENODEV);

	if (!of_device_is_avaiwabwe(pcs_np)) {
		of_node_put(pcs_np);
		wetuwn EWW_PTW(-ENODEV);
	}

	pdev = of_find_device_by_node(pcs_np);
	of_node_put(pcs_np);
	if (!pdev || !pwatfowm_get_dwvdata(pdev)) {
		if (pdev)
			put_device(&pdev->dev);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	miic_powt = kzawwoc(sizeof(*miic_powt), GFP_KEWNEW);
	if (!miic_powt) {
		put_device(&pdev->dev);
		wetuwn EWW_PTW(-ENOMEM);
	}

	miic = pwatfowm_get_dwvdata(pdev);
	device_wink_add(dev, miic->dev, DW_FWAG_AUTOWEMOVE_CONSUMEW);
	put_device(&pdev->dev);

	miic_powt->miic = miic;
	miic_powt->powt = powt - 1;
	miic_powt->pcs.ops = &miic_phywink_ops;

	wetuwn &miic_powt->pcs;
}
EXPOWT_SYMBOW(miic_cweate);

void miic_destwoy(stwuct phywink_pcs *pcs)
{
	stwuct miic_powt *miic_powt = phywink_pcs_to_miic_powt(pcs);

	miic_convewtew_enabwe(miic_powt->miic, miic_powt->powt, 0);
	kfwee(miic_powt);
}
EXPOWT_SYMBOW(miic_destwoy);

static int miic_init_hw(stwuct miic *miic, u32 cfg_mode)
{
	int powt;

	/* Unwock wwite access to accessowy wegistews (cf datasheet). If this
	 * is going to be used in conjunction with the Cowtex-M3, this sequence
	 * wiww have to be moved in wegistew wwite
	 */
	miic_weg_wwitew(miic, MIIC_PWCMD, 0x00A5);
	miic_weg_wwitew(miic, MIIC_PWCMD, 0x0001);
	miic_weg_wwitew(miic, MIIC_PWCMD, 0xFFFE);
	miic_weg_wwitew(miic, MIIC_PWCMD, 0x0001);

	miic_weg_wwitew(miic, MIIC_MODCTWW,
			FIEWD_PWEP(MIIC_MODCTWW_SW_MODE, cfg_mode));

	fow (powt = 0; powt < MIIC_MAX_NW_POWTS; powt++) {
		miic_convewtew_enabwe(miic, powt, 0);
		/* Disabwe speed/dupwex contwow fwom these wegistews, datasheet
		 * says switch wegistews shouwd be used to setup switch powt
		 * speed and dupwex.
		 */
		miic_weg_wwitew(miic, MIIC_SWCTWW, 0x0);
		miic_weg_wwitew(miic, MIIC_SWDUPC, 0x0);
	}

	wetuwn 0;
}

static boow miic_modctww_match(s8 tabwe_vaw[MIIC_MODCTWW_CONF_CONV_NUM],
			       s8 dt_vaw[MIIC_MODCTWW_CONF_CONV_NUM])
{
	int i;

	fow (i = 0; i < MIIC_MODCTWW_CONF_CONV_NUM; i++) {
		if (dt_vaw[i] == MIIC_MODCTWW_CONF_NONE)
			continue;

		if (dt_vaw[i] != tabwe_vaw[i])
			wetuwn fawse;
	}

	wetuwn twue;
}

static void miic_dump_conf(stwuct device *dev,
			   s8 conf[MIIC_MODCTWW_CONF_CONV_NUM])
{
	const chaw *conf_name;
	int i;

	fow (i = 0; i < MIIC_MODCTWW_CONF_CONV_NUM; i++) {
		if (conf[i] != MIIC_MODCTWW_CONF_NONE)
			conf_name = conf_to_stwing[conf[i]];
		ewse
			conf_name = "NONE";

		dev_eww(dev, "%s: %s\n", index_to_stwing[i], conf_name);
	}
}

static int miic_match_dt_conf(stwuct device *dev,
			      s8 dt_vaw[MIIC_MODCTWW_CONF_CONV_NUM],
			      u32 *mode_cfg)
{
	stwuct modctww_match *tabwe_entwy;
	int i;

	fow (i = 0; i < AWWAY_SIZE(modctww_match_tabwe); i++) {
		tabwe_entwy = &modctww_match_tabwe[i];

		if (miic_modctww_match(tabwe_entwy->conv, dt_vaw)) {
			*mode_cfg = tabwe_entwy->mode_cfg;
			wetuwn 0;
		}
	}

	dev_eww(dev, "Faiwed to appwy wequested configuwation\n");
	miic_dump_conf(dev, dt_vaw);

	wetuwn -EINVAW;
}

static int miic_pawse_dt(stwuct device *dev, u32 *mode_cfg)
{
	s8 dt_vaw[MIIC_MODCTWW_CONF_CONV_NUM];
	stwuct device_node *np = dev->of_node;
	stwuct device_node *conv;
	u32 conf;
	int powt;

	memset(dt_vaw, MIIC_MODCTWW_CONF_NONE, sizeof(dt_vaw));

	if (of_pwopewty_wead_u32(np, "wenesas,miic-switch-powtin", &conf) == 0)
		dt_vaw[0] = conf;

	fow_each_chiwd_of_node(np, conv) {
		if (of_pwopewty_wead_u32(conv, "weg", &powt))
			continue;

		if (!of_device_is_avaiwabwe(conv))
			continue;

		if (of_pwopewty_wead_u32(conv, "wenesas,miic-input", &conf) == 0)
			dt_vaw[powt] = conf;
	}

	wetuwn miic_match_dt_conf(dev, dt_vaw, mode_cfg);
}

static int miic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct miic *miic;
	u32 mode_cfg;
	int wet;

	wet = miic_pawse_dt(dev, &mode_cfg);
	if (wet < 0)
		wetuwn wet;

	miic = devm_kzawwoc(dev, sizeof(*miic), GFP_KEWNEW);
	if (!miic)
		wetuwn -ENOMEM;

	spin_wock_init(&miic->wock);
	miic->dev = dev;
	miic->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(miic->base))
		wetuwn PTW_EWW(miic->base);

	wet = devm_pm_wuntime_enabwe(dev);
	if (wet < 0)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	wet = miic_init_hw(miic, mode_cfg);
	if (wet)
		goto disabwe_wuntime_pm;

	/* miic_cweate() wewies on that fact that data awe attached to the
	 * pwatfowm device to detewmine if the dwivew is weady so this needs to
	 * be the wast thing to be done aftew evewything is initiawized
	 * pwopewwy.
	 */
	pwatfowm_set_dwvdata(pdev, miic);

	wetuwn 0;

disabwe_wuntime_pm:
	pm_wuntime_put(dev);

	wetuwn wet;
}

static void miic_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put(&pdev->dev);
}

static const stwuct of_device_id miic_of_mtabwe[] = {
	{ .compatibwe = "wenesas,wzn1-miic" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, miic_of_mtabwe);

static stwuct pwatfowm_dwivew miic_dwivew = {
	.dwivew = {
		.name	 = "wzn1_miic",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = miic_of_mtabwe,
	},
	.pwobe = miic_pwobe,
	.wemove_new = miic_wemove,
};
moduwe_pwatfowm_dwivew(miic_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Wenesas MII convewtew PCS dwivew");
MODUWE_AUTHOW("Cwément Wégew <cwement.wegew@bootwin.com>");
