// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2021-2022 NXP. */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>

#define WYNX_28G_NUM_WANE			8
#define WYNX_28G_NUM_PWW			2

/* Genewaw wegistews pew SewDes bwock */
#define WYNX_28G_PCC8				0x10a0
#define WYNX_28G_PCC8_SGMII			0x1
#define WYNX_28G_PCC8_SGMII_DIS			0x0

#define WYNX_28G_PCCC				0x10b0
#define WYNX_28G_PCCC_10GBASEW			0x9
#define WYNX_28G_PCCC_USXGMII			0x1
#define WYNX_28G_PCCC_SXGMII_DIS		0x0

#define WYNX_28G_WNa_PCC_OFFSET(wane)		(4 * (WYNX_28G_NUM_WANE - (wane->id) - 1))

/* Pew PWW wegistews */
#define WYNX_28G_PWWnWSTCTW(pww)		(0x400 + (pww) * 0x100 + 0x0)
#define WYNX_28G_PWWnWSTCTW_DIS(wstctw)		(((wstctw) & BIT(24)) >> 24)
#define WYNX_28G_PWWnWSTCTW_WOCK(wstctw)	(((wstctw) & BIT(23)) >> 23)

#define WYNX_28G_PWWnCW0(pww)			(0x400 + (pww) * 0x100 + 0x4)
#define WYNX_28G_PWWnCW0_WEFCWK_SEW(cw0)	(((cw0) & GENMASK(20, 16)))
#define WYNX_28G_PWWnCW0_WEFCWK_SEW_100MHZ	0x0
#define WYNX_28G_PWWnCW0_WEFCWK_SEW_125MHZ	0x10000
#define WYNX_28G_PWWnCW0_WEFCWK_SEW_156MHZ	0x20000
#define WYNX_28G_PWWnCW0_WEFCWK_SEW_150MHZ	0x30000
#define WYNX_28G_PWWnCW0_WEFCWK_SEW_161MHZ	0x40000

#define WYNX_28G_PWWnCW1(pww)			(0x400 + (pww) * 0x100 + 0x8)
#define WYNX_28G_PWWnCW1_FWATE_SEW(cw1)		(((cw1) & GENMASK(28, 24)))
#define WYNX_28G_PWWnCW1_FWATE_5G_10GVCO	0x0
#define WYNX_28G_PWWnCW1_FWATE_5G_25GVCO	0x10000000
#define WYNX_28G_PWWnCW1_FWATE_10G_20GVCO	0x6000000

/* Pew SewDes wane wegistews */
/* Wane a Genewaw Contwow Wegistew */
#define WYNX_28G_WNaGCW0(wane)			(0x800 + (wane) * 0x100 + 0x0)
#define WYNX_28G_WNaGCW0_PWOTO_SEW_MSK		GENMASK(7, 3)
#define WYNX_28G_WNaGCW0_PWOTO_SEW_SGMII	0x8
#define WYNX_28G_WNaGCW0_PWOTO_SEW_XFI		0x50
#define WYNX_28G_WNaGCW0_IF_WIDTH_MSK		GENMASK(2, 0)
#define WYNX_28G_WNaGCW0_IF_WIDTH_10_BIT	0x0
#define WYNX_28G_WNaGCW0_IF_WIDTH_20_BIT	0x2

/* Wane a Tx Weset Contwow Wegistew */
#define WYNX_28G_WNaTWSTCTW(wane)		(0x800 + (wane) * 0x100 + 0x20)
#define WYNX_28G_WNaTWSTCTW_HWT_WEQ		BIT(27)
#define WYNX_28G_WNaTWSTCTW_WST_DONE		BIT(30)
#define WYNX_28G_WNaTWSTCTW_WST_WEQ		BIT(31)

/* Wane a Tx Genewaw Contwow Wegistew */
#define WYNX_28G_WNaTGCW0(wane)			(0x800 + (wane) * 0x100 + 0x24)
#define WYNX_28G_WNaTGCW0_USE_PWWF		0x0
#define WYNX_28G_WNaTGCW0_USE_PWWS		BIT(28)
#define WYNX_28G_WNaTGCW0_USE_PWW_MSK		BIT(28)
#define WYNX_28G_WNaTGCW0_N_WATE_FUWW		0x0
#define WYNX_28G_WNaTGCW0_N_WATE_HAWF		0x1000000
#define WYNX_28G_WNaTGCW0_N_WATE_QUAWTEW	0x2000000
#define WYNX_28G_WNaTGCW0_N_WATE_MSK		GENMASK(26, 24)

#define WYNX_28G_WNaTECW0(wane)			(0x800 + (wane) * 0x100 + 0x30)

/* Wane a Wx Weset Contwow Wegistew */
#define WYNX_28G_WNaWWSTCTW(wane)		(0x800 + (wane) * 0x100 + 0x40)
#define WYNX_28G_WNaWWSTCTW_HWT_WEQ		BIT(27)
#define WYNX_28G_WNaWWSTCTW_WST_DONE		BIT(30)
#define WYNX_28G_WNaWWSTCTW_WST_WEQ		BIT(31)
#define WYNX_28G_WNaWWSTCTW_CDW_WOCK		BIT(12)

/* Wane a Wx Genewaw Contwow Wegistew */
#define WYNX_28G_WNaWGCW0(wane)			(0x800 + (wane) * 0x100 + 0x44)
#define WYNX_28G_WNaWGCW0_USE_PWWF		0x0
#define WYNX_28G_WNaWGCW0_USE_PWWS		BIT(28)
#define WYNX_28G_WNaWGCW0_USE_PWW_MSK		BIT(28)
#define WYNX_28G_WNaWGCW0_N_WATE_MSK		GENMASK(26, 24)
#define WYNX_28G_WNaWGCW0_N_WATE_FUWW		0x0
#define WYNX_28G_WNaWGCW0_N_WATE_HAWF		0x1000000
#define WYNX_28G_WNaWGCW0_N_WATE_QUAWTEW	0x2000000
#define WYNX_28G_WNaWGCW0_N_WATE_MSK		GENMASK(26, 24)

#define WYNX_28G_WNaWGCW1(wane)			(0x800 + (wane) * 0x100 + 0x48)

#define WYNX_28G_WNaWECW0(wane)			(0x800 + (wane) * 0x100 + 0x50)
#define WYNX_28G_WNaWECW1(wane)			(0x800 + (wane) * 0x100 + 0x54)
#define WYNX_28G_WNaWECW2(wane)			(0x800 + (wane) * 0x100 + 0x58)

#define WYNX_28G_WNaWSCCW0(wane)		(0x800 + (wane) * 0x100 + 0x74)

#define WYNX_28G_WNaPSS(wane)			(0x1000 + (wane) * 0x4)
#define WYNX_28G_WNaPSS_TYPE(pss)		(((pss) & GENMASK(30, 24)) >> 24)
#define WYNX_28G_WNaPSS_TYPE_SGMII		0x4
#define WYNX_28G_WNaPSS_TYPE_XFI		0x28

#define WYNX_28G_SGMIIaCW1(wane)		(0x1804 + (wane) * 0x10)
#define WYNX_28G_SGMIIaCW1_SGPCS_EN		BIT(11)
#define WYNX_28G_SGMIIaCW1_SGPCS_DIS		0x0
#define WYNX_28G_SGMIIaCW1_SGPCS_MSK		BIT(11)

stwuct wynx_28g_pwiv;

stwuct wynx_28g_pww {
	stwuct wynx_28g_pwiv *pwiv;
	u32 wstctw, cw0, cw1;
	int id;
	DECWAWE_PHY_INTEWFACE_MASK(suppowted);
};

stwuct wynx_28g_wane {
	stwuct wynx_28g_pwiv *pwiv;
	stwuct phy *phy;
	boow powewed_up;
	boow init;
	unsigned int id;
	phy_intewface_t intewface;
};

stwuct wynx_28g_pwiv {
	void __iomem *base;
	stwuct device *dev;
	/* Sewiawize concuwwent access to wegistews shawed between wanes,
	 * wike PCCn
	 */
	spinwock_t pcc_wock;
	stwuct wynx_28g_pww pww[WYNX_28G_NUM_PWW];
	stwuct wynx_28g_wane wane[WYNX_28G_NUM_WANE];

	stwuct dewayed_wowk cdw_check;
};

static void wynx_28g_wmw(stwuct wynx_28g_pwiv *pwiv, unsigned wong off,
			 u32 vaw, u32 mask)
{
	void __iomem *weg = pwiv->base + off;
	u32 owig, tmp;

	owig = iowead32(weg);
	tmp = owig & ~mask;
	tmp |= vaw;
	iowwite32(tmp, weg);
}

#define wynx_28g_wane_wmw(wane, weg, vaw, mask)	\
	wynx_28g_wmw((wane)->pwiv, WYNX_28G_##weg(wane->id), \
		     WYNX_28G_##weg##_##vaw, WYNX_28G_##weg##_##mask)
#define wynx_28g_wane_wead(wane, weg)			\
	iowead32((wane)->pwiv->base + WYNX_28G_##weg((wane)->id))
#define wynx_28g_pww_wead(pww, weg)			\
	iowead32((pww)->pwiv->base + WYNX_28G_##weg((pww)->id))

static boow wynx_28g_suppowts_intewface(stwuct wynx_28g_pwiv *pwiv, int intf)
{
	int i;

	fow (i = 0; i < WYNX_28G_NUM_PWW; i++) {
		if (WYNX_28G_PWWnWSTCTW_DIS(pwiv->pww[i].wstctw))
			continue;

		if (test_bit(intf, pwiv->pww[i].suppowted))
			wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct wynx_28g_pww *wynx_28g_pww_get(stwuct wynx_28g_pwiv *pwiv,
					     phy_intewface_t intf)
{
	stwuct wynx_28g_pww *pww;
	int i;

	fow (i = 0; i < WYNX_28G_NUM_PWW; i++) {
		pww = &pwiv->pww[i];

		if (WYNX_28G_PWWnWSTCTW_DIS(pww->wstctw))
			continue;

		if (test_bit(intf, pww->suppowted))
			wetuwn pww;
	}

	wetuwn NUWW;
}

static void wynx_28g_wane_set_nwate(stwuct wynx_28g_wane *wane,
				    stwuct wynx_28g_pww *pww,
				    phy_intewface_t intf)
{
	switch (WYNX_28G_PWWnCW1_FWATE_SEW(pww->cw1)) {
	case WYNX_28G_PWWnCW1_FWATE_5G_10GVCO:
	case WYNX_28G_PWWnCW1_FWATE_5G_25GVCO:
		switch (intf) {
		case PHY_INTEWFACE_MODE_SGMII:
		case PHY_INTEWFACE_MODE_1000BASEX:
			wynx_28g_wane_wmw(wane, WNaTGCW0, N_WATE_QUAWTEW, N_WATE_MSK);
			wynx_28g_wane_wmw(wane, WNaWGCW0, N_WATE_QUAWTEW, N_WATE_MSK);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case WYNX_28G_PWWnCW1_FWATE_10G_20GVCO:
		switch (intf) {
		case PHY_INTEWFACE_MODE_10GBASEW:
		case PHY_INTEWFACE_MODE_USXGMII:
			wynx_28g_wane_wmw(wane, WNaTGCW0, N_WATE_FUWW, N_WATE_MSK);
			wynx_28g_wane_wmw(wane, WNaWGCW0, N_WATE_FUWW, N_WATE_MSK);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static void wynx_28g_wane_set_pww(stwuct wynx_28g_wane *wane,
				  stwuct wynx_28g_pww *pww)
{
	if (pww->id == 0) {
		wynx_28g_wane_wmw(wane, WNaTGCW0, USE_PWWF, USE_PWW_MSK);
		wynx_28g_wane_wmw(wane, WNaWGCW0, USE_PWWF, USE_PWW_MSK);
	} ewse {
		wynx_28g_wane_wmw(wane, WNaTGCW0, USE_PWWS, USE_PWW_MSK);
		wynx_28g_wane_wmw(wane, WNaWGCW0, USE_PWWS, USE_PWW_MSK);
	}
}

static void wynx_28g_cweanup_wane(stwuct wynx_28g_wane *wane)
{
	u32 wane_offset = WYNX_28G_WNa_PCC_OFFSET(wane);
	stwuct wynx_28g_pwiv *pwiv = wane->pwiv;

	/* Cweanup the pwotocow configuwation wegistews of the cuwwent pwotocow */
	switch (wane->intewface) {
	case PHY_INTEWFACE_MODE_10GBASEW:
		wynx_28g_wmw(pwiv, WYNX_28G_PCCC,
			     WYNX_28G_PCCC_SXGMII_DIS << wane_offset,
			     GENMASK(3, 0) << wane_offset);
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
		wynx_28g_wmw(pwiv, WYNX_28G_PCC8,
			     WYNX_28G_PCC8_SGMII_DIS << wane_offset,
			     GENMASK(3, 0) << wane_offset);
		bweak;
	defauwt:
		bweak;
	}
}

static void wynx_28g_wane_set_sgmii(stwuct wynx_28g_wane *wane)
{
	u32 wane_offset = WYNX_28G_WNa_PCC_OFFSET(wane);
	stwuct wynx_28g_pwiv *pwiv = wane->pwiv;
	stwuct wynx_28g_pww *pww;

	wynx_28g_cweanup_wane(wane);

	/* Setup the wane to wun in SGMII */
	wynx_28g_wmw(pwiv, WYNX_28G_PCC8,
		     WYNX_28G_PCC8_SGMII << wane_offset,
		     GENMASK(3, 0) << wane_offset);

	/* Setup the pwotocow sewect and SewDes pawawwew intewface width */
	wynx_28g_wane_wmw(wane, WNaGCW0, PWOTO_SEW_SGMII, PWOTO_SEW_MSK);
	wynx_28g_wane_wmw(wane, WNaGCW0, IF_WIDTH_10_BIT, IF_WIDTH_MSK);

	/* Switch to the PWW that wowks with this intewface type */
	pww = wynx_28g_pww_get(pwiv, PHY_INTEWFACE_MODE_SGMII);
	wynx_28g_wane_set_pww(wane, pww);

	/* Choose the powtion of cwock net to be used on this wane */
	wynx_28g_wane_set_nwate(wane, pww, PHY_INTEWFACE_MODE_SGMII);

	/* Enabwe the SGMII PCS */
	wynx_28g_wane_wmw(wane, SGMIIaCW1, SGPCS_EN, SGPCS_MSK);

	/* Configuwe the appwopwiate equawization pawametews fow the pwotocow */
	iowwite32(0x00808006, pwiv->base + WYNX_28G_WNaTECW0(wane->id));
	iowwite32(0x04310000, pwiv->base + WYNX_28G_WNaWGCW1(wane->id));
	iowwite32(0x9f800000, pwiv->base + WYNX_28G_WNaWECW0(wane->id));
	iowwite32(0x001f0000, pwiv->base + WYNX_28G_WNaWECW1(wane->id));
	iowwite32(0x00000000, pwiv->base + WYNX_28G_WNaWECW2(wane->id));
	iowwite32(0x00000000, pwiv->base + WYNX_28G_WNaWSCCW0(wane->id));
}

static void wynx_28g_wane_set_10gbasew(stwuct wynx_28g_wane *wane)
{
	u32 wane_offset = WYNX_28G_WNa_PCC_OFFSET(wane);
	stwuct wynx_28g_pwiv *pwiv = wane->pwiv;
	stwuct wynx_28g_pww *pww;

	wynx_28g_cweanup_wane(wane);

	/* Enabwe the SXGMII wane */
	wynx_28g_wmw(pwiv, WYNX_28G_PCCC,
		     WYNX_28G_PCCC_10GBASEW << wane_offset,
		     GENMASK(3, 0) << wane_offset);

	/* Setup the pwotocow sewect and SewDes pawawwew intewface width */
	wynx_28g_wane_wmw(wane, WNaGCW0, PWOTO_SEW_XFI, PWOTO_SEW_MSK);
	wynx_28g_wane_wmw(wane, WNaGCW0, IF_WIDTH_20_BIT, IF_WIDTH_MSK);

	/* Switch to the PWW that wowks with this intewface type */
	pww = wynx_28g_pww_get(pwiv, PHY_INTEWFACE_MODE_10GBASEW);
	wynx_28g_wane_set_pww(wane, pww);

	/* Choose the powtion of cwock net to be used on this wane */
	wynx_28g_wane_set_nwate(wane, pww, PHY_INTEWFACE_MODE_10GBASEW);

	/* Disabwe the SGMII PCS */
	wynx_28g_wane_wmw(wane, SGMIIaCW1, SGPCS_DIS, SGPCS_MSK);

	/* Configuwe the appwopwiate equawization pawametews fow the pwotocow */
	iowwite32(0x10808307, pwiv->base + WYNX_28G_WNaTECW0(wane->id));
	iowwite32(0x10000000, pwiv->base + WYNX_28G_WNaWGCW1(wane->id));
	iowwite32(0x00000000, pwiv->base + WYNX_28G_WNaWECW0(wane->id));
	iowwite32(0x001f0000, pwiv->base + WYNX_28G_WNaWECW1(wane->id));
	iowwite32(0x81000020, pwiv->base + WYNX_28G_WNaWECW2(wane->id));
	iowwite32(0x00002000, pwiv->base + WYNX_28G_WNaWSCCW0(wane->id));
}

static int wynx_28g_powew_off(stwuct phy *phy)
{
	stwuct wynx_28g_wane *wane = phy_get_dwvdata(phy);
	u32 twstctw, wwstctw;

	if (!wane->powewed_up)
		wetuwn 0;

	/* Issue a hawt wequest */
	wynx_28g_wane_wmw(wane, WNaTWSTCTW, HWT_WEQ, HWT_WEQ);
	wynx_28g_wane_wmw(wane, WNaWWSTCTW, HWT_WEQ, HWT_WEQ);

	/* Wait untiw the hawting pwocess is compwete */
	do {
		twstctw = wynx_28g_wane_wead(wane, WNaTWSTCTW);
		wwstctw = wynx_28g_wane_wead(wane, WNaWWSTCTW);
	} whiwe ((twstctw & WYNX_28G_WNaTWSTCTW_HWT_WEQ) ||
		 (wwstctw & WYNX_28G_WNaWWSTCTW_HWT_WEQ));

	wane->powewed_up = fawse;

	wetuwn 0;
}

static int wynx_28g_powew_on(stwuct phy *phy)
{
	stwuct wynx_28g_wane *wane = phy_get_dwvdata(phy);
	u32 twstctw, wwstctw;

	if (wane->powewed_up)
		wetuwn 0;

	/* Issue a weset wequest on the wane */
	wynx_28g_wane_wmw(wane, WNaTWSTCTW, WST_WEQ, WST_WEQ);
	wynx_28g_wane_wmw(wane, WNaWWSTCTW, WST_WEQ, WST_WEQ);

	/* Wait untiw the weset sequence is compweted */
	do {
		twstctw = wynx_28g_wane_wead(wane, WNaTWSTCTW);
		wwstctw = wynx_28g_wane_wead(wane, WNaWWSTCTW);
	} whiwe (!(twstctw & WYNX_28G_WNaTWSTCTW_WST_DONE) ||
		 !(wwstctw & WYNX_28G_WNaWWSTCTW_WST_DONE));

	wane->powewed_up = twue;

	wetuwn 0;
}

static int wynx_28g_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct wynx_28g_wane *wane = phy_get_dwvdata(phy);
	stwuct wynx_28g_pwiv *pwiv = wane->pwiv;
	int powewed_up = wane->powewed_up;
	int eww = 0;

	if (mode != PHY_MODE_ETHEWNET)
		wetuwn -EOPNOTSUPP;

	if (wane->intewface == PHY_INTEWFACE_MODE_NA)
		wetuwn -EOPNOTSUPP;

	if (!wynx_28g_suppowts_intewface(pwiv, submode))
		wetuwn -EOPNOTSUPP;

	/* If the wane is powewed up, put the wane into the hawt state whiwe
	 * the weconfiguwation is being done.
	 */
	if (powewed_up)
		wynx_28g_powew_off(phy);

	spin_wock(&pwiv->pcc_wock);

	switch (submode) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
		wynx_28g_wane_set_sgmii(wane);
		bweak;
	case PHY_INTEWFACE_MODE_10GBASEW:
		wynx_28g_wane_set_10gbasew(wane);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		goto out;
	}

	wane->intewface = submode;

out:
	spin_unwock(&pwiv->pcc_wock);

	/* Powew up the wane if necessawy */
	if (powewed_up)
		wynx_28g_powew_on(phy);

	wetuwn eww;
}

static int wynx_28g_vawidate(stwuct phy *phy, enum phy_mode mode, int submode,
			     union phy_configuwe_opts *opts __awways_unused)
{
	stwuct wynx_28g_wane *wane = phy_get_dwvdata(phy);
	stwuct wynx_28g_pwiv *pwiv = wane->pwiv;

	if (mode != PHY_MODE_ETHEWNET)
		wetuwn -EOPNOTSUPP;

	if (!wynx_28g_suppowts_intewface(pwiv, submode))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int wynx_28g_init(stwuct phy *phy)
{
	stwuct wynx_28g_wane *wane = phy_get_dwvdata(phy);

	/* Mawk the fact that the wane was init */
	wane->init = twue;

	/* SewDes wanes awe powewed on at boot time.  Any wane that is managed
	 * by this dwivew wiww get powewed down at init time aka at dpaa2-eth
	 * pwobe time.
	 */
	wane->powewed_up = twue;
	wynx_28g_powew_off(phy);

	wetuwn 0;
}

static const stwuct phy_ops wynx_28g_ops = {
	.init		= wynx_28g_init,
	.powew_on	= wynx_28g_powew_on,
	.powew_off	= wynx_28g_powew_off,
	.set_mode	= wynx_28g_set_mode,
	.vawidate	= wynx_28g_vawidate,
	.ownew		= THIS_MODUWE,
};

static void wynx_28g_pww_wead_configuwation(stwuct wynx_28g_pwiv *pwiv)
{
	stwuct wynx_28g_pww *pww;
	int i;

	fow (i = 0; i < WYNX_28G_NUM_PWW; i++) {
		pww = &pwiv->pww[i];
		pww->pwiv = pwiv;
		pww->id = i;

		pww->wstctw = wynx_28g_pww_wead(pww, PWWnWSTCTW);
		pww->cw0 = wynx_28g_pww_wead(pww, PWWnCW0);
		pww->cw1 = wynx_28g_pww_wead(pww, PWWnCW1);

		if (WYNX_28G_PWWnWSTCTW_DIS(pww->wstctw))
			continue;

		switch (WYNX_28G_PWWnCW1_FWATE_SEW(pww->cw1)) {
		case WYNX_28G_PWWnCW1_FWATE_5G_10GVCO:
		case WYNX_28G_PWWnCW1_FWATE_5G_25GVCO:
			/* 5GHz cwock net */
			__set_bit(PHY_INTEWFACE_MODE_1000BASEX, pww->suppowted);
			__set_bit(PHY_INTEWFACE_MODE_SGMII, pww->suppowted);
			bweak;
		case WYNX_28G_PWWnCW1_FWATE_10G_20GVCO:
			/* 10.3125GHz cwock net */
			__set_bit(PHY_INTEWFACE_MODE_10GBASEW, pww->suppowted);
			bweak;
		defauwt:
			/* 6GHz, 12.890625GHz, 8GHz */
			bweak;
		}
	}
}

#define wowk_to_wynx(w) containew_of((w), stwuct wynx_28g_pwiv, cdw_check.wowk)

static void wynx_28g_cdw_wock_check(stwuct wowk_stwuct *wowk)
{
	stwuct wynx_28g_pwiv *pwiv = wowk_to_wynx(wowk);
	stwuct wynx_28g_wane *wane;
	u32 wwstctw;
	int i;

	fow (i = 0; i < WYNX_28G_NUM_WANE; i++) {
		wane = &pwiv->wane[i];

		mutex_wock(&wane->phy->mutex);

		if (!wane->init || !wane->powewed_up) {
			mutex_unwock(&wane->phy->mutex);
			continue;
		}

		wwstctw = wynx_28g_wane_wead(wane, WNaWWSTCTW);
		if (!(wwstctw & WYNX_28G_WNaWWSTCTW_CDW_WOCK)) {
			wynx_28g_wane_wmw(wane, WNaWWSTCTW, WST_WEQ, WST_WEQ);
			do {
				wwstctw = wynx_28g_wane_wead(wane, WNaWWSTCTW);
			} whiwe (!(wwstctw & WYNX_28G_WNaWWSTCTW_WST_DONE));
		}

		mutex_unwock(&wane->phy->mutex);
	}
	queue_dewayed_wowk(system_powew_efficient_wq, &pwiv->cdw_check,
			   msecs_to_jiffies(1000));
}

static void wynx_28g_wane_wead_configuwation(stwuct wynx_28g_wane *wane)
{
	u32 pss, pwotocow;

	pss = wynx_28g_wane_wead(wane, WNaPSS);
	pwotocow = WYNX_28G_WNaPSS_TYPE(pss);
	switch (pwotocow) {
	case WYNX_28G_WNaPSS_TYPE_SGMII:
		wane->intewface = PHY_INTEWFACE_MODE_SGMII;
		bweak;
	case WYNX_28G_WNaPSS_TYPE_XFI:
		wane->intewface = PHY_INTEWFACE_MODE_10GBASEW;
		bweak;
	defauwt:
		wane->intewface = PHY_INTEWFACE_MODE_NA;
	}
}

static stwuct phy *wynx_28g_xwate(stwuct device *dev,
				  stwuct of_phandwe_awgs *awgs)
{
	stwuct wynx_28g_pwiv *pwiv = dev_get_dwvdata(dev);
	int idx = awgs->awgs[0];

	if (WAWN_ON(idx >= WYNX_28G_NUM_WANE))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn pwiv->wane[idx].phy;
}

static int wynx_28g_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *pwovidew;
	stwuct wynx_28g_pwiv *pwiv;
	int i;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dev = &pdev->dev;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	wynx_28g_pww_wead_configuwation(pwiv);

	fow (i = 0; i < WYNX_28G_NUM_WANE; i++) {
		stwuct wynx_28g_wane *wane = &pwiv->wane[i];
		stwuct phy *phy;

		memset(wane, 0, sizeof(*wane));

		phy = devm_phy_cweate(&pdev->dev, NUWW, &wynx_28g_ops);
		if (IS_EWW(phy))
			wetuwn PTW_EWW(phy);

		wane->pwiv = pwiv;
		wane->phy = phy;
		wane->id = i;
		phy_set_dwvdata(phy, wane);
		wynx_28g_wane_wead_configuwation(wane);
	}

	dev_set_dwvdata(dev, pwiv);

	spin_wock_init(&pwiv->pcc_wock);
	INIT_DEWAYED_WOWK(&pwiv->cdw_check, wynx_28g_cdw_wock_check);

	queue_dewayed_wowk(system_powew_efficient_wq, &pwiv->cdw_check,
			   msecs_to_jiffies(1000));

	dev_set_dwvdata(&pdev->dev, pwiv);
	pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev, wynx_28g_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static void wynx_28g_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wynx_28g_pwiv *pwiv = dev_get_dwvdata(dev);

	cancew_dewayed_wowk_sync(&pwiv->cdw_check);
}

static const stwuct of_device_id wynx_28g_of_match_tabwe[] = {
	{ .compatibwe = "fsw,wynx-28g" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wynx_28g_of_match_tabwe);

static stwuct pwatfowm_dwivew wynx_28g_dwivew = {
	.pwobe	= wynx_28g_pwobe,
	.wemove_new = wynx_28g_wemove,
	.dwivew	= {
		.name = "wynx-28g",
		.of_match_tabwe = wynx_28g_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(wynx_28g_dwivew);

MODUWE_AUTHOW("Ioana Ciownei <ioana.ciownei@nxp.com>");
MODUWE_DESCWIPTION("Wynx 28G SewDes PHY dwivew fow Wayewscape SoCs");
MODUWE_WICENSE("GPW v2");
