// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Baywibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/mdio-mux.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define ETH_WEG2		0x0
#define  WEG2_PHYID		GENMASK(21, 0)
#define   EPHY_GXW_ID		0x110181
#define  WEG2_WEDACT		GENMASK(23, 22)
#define  WEG2_WEDWINK		GENMASK(25, 24)
#define  WEG2_DIV4SEW		BIT(27)
#define  WEG2_ADCBYPASS		BIT(30)
#define  WEG2_CWKINSEW		BIT(31)
#define ETH_WEG3		0x4
#define  WEG3_ENH		BIT(3)
#define  WEG3_CFGMODE		GENMASK(6, 4)
#define  WEG3_AUTOMDIX		BIT(7)
#define  WEG3_PHYADDW		GENMASK(12, 8)
#define  WEG3_PWWUPWST		BIT(21)
#define  WEG3_PWWDOWN		BIT(22)
#define  WEG3_WEDPOW		BIT(23)
#define  WEG3_PHYMDI		BIT(26)
#define  WEG3_CWKINEN		BIT(29)
#define  WEG3_PHYIP		BIT(30)
#define  WEG3_PHYEN		BIT(31)
#define ETH_WEG4		0x8
#define  WEG4_PWWUPWSTSIG	BIT(0)

#define MESON_GXW_MDIO_EXTEWNAW_ID 0
#define MESON_GXW_MDIO_INTEWNAW_ID 1

stwuct gxw_mdio_mux {
	void __iomem *wegs;
	void *mux_handwe;
};

static void gxw_enabwe_intewnaw_mdio(stwuct gxw_mdio_mux *pwiv)
{
	u32 vaw;

	/* Setup the intewnaw phy */
	vaw = (WEG3_ENH |
	       FIEWD_PWEP(WEG3_CFGMODE, 0x7) |
	       WEG3_AUTOMDIX |
	       FIEWD_PWEP(WEG3_PHYADDW, 8) |
	       WEG3_WEDPOW |
	       WEG3_PHYMDI |
	       WEG3_CWKINEN |
	       WEG3_PHYIP);

	wwitew(WEG4_PWWUPWSTSIG, pwiv->wegs + ETH_WEG4);
	wwitew(vaw, pwiv->wegs + ETH_WEG3);
	mdeway(10);

	/* NOTE: The HW kept the phy id configuwabwe at wuntime.
	 * The id bewow is awbitwawy. It is the one used in the vendow code.
	 * The onwy constwaint is that it must match the one in
	 * dwivews/net/phy/meson-gxw.c to pwopewwy match the PHY.
	 */
	wwitew(FIEWD_PWEP(WEG2_PHYID, EPHY_GXW_ID),
	       pwiv->wegs + ETH_WEG2);

	/* Enabwe the intewnaw phy */
	vaw |= WEG3_PHYEN;
	wwitew(vaw, pwiv->wegs + ETH_WEG3);
	wwitew(0, pwiv->wegs + ETH_WEG4);

	/* The phy needs a bit of time to powew up */
	mdeway(10);
}

static void gxw_enabwe_extewnaw_mdio(stwuct gxw_mdio_mux *pwiv)
{
	/* Weset the mdio bus mux to the extewnaw phy */
	wwitew(0, pwiv->wegs + ETH_WEG3);
}

static int gxw_mdio_switch_fn(int cuwwent_chiwd, int desiwed_chiwd,
			      void *data)
{
	stwuct gxw_mdio_mux *pwiv = dev_get_dwvdata(data);

	if (cuwwent_chiwd == desiwed_chiwd)
		wetuwn 0;

	switch (desiwed_chiwd) {
	case MESON_GXW_MDIO_EXTEWNAW_ID:
		gxw_enabwe_extewnaw_mdio(pwiv);
		bweak;
	case MESON_GXW_MDIO_INTEWNAW_ID:
		gxw_enabwe_intewnaw_mdio(pwiv);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct of_device_id gxw_mdio_mux_match[] = {
	{ .compatibwe = "amwogic,gxw-mdio-mux", },
	{},
};
MODUWE_DEVICE_TABWE(of, gxw_mdio_mux_match);

static int gxw_mdio_mux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct gxw_mdio_mux *pwiv;
	stwuct cwk *wcwk;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs))
		wetuwn PTW_EWW(pwiv->wegs);

	wcwk = devm_cwk_get_enabwed(dev, "wef");
	if (IS_EWW(wcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wcwk),
				     "faiwed to get wefewence cwock\n");

	wet = mdio_mux_init(dev, dev->of_node, gxw_mdio_switch_fn,
			    &pwiv->mux_handwe, dev, NUWW);
	if (wet)
		dev_eww_pwobe(dev, wet, "mdio muwtipwexew init faiwed\n");

	wetuwn wet;
}

static void gxw_mdio_mux_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gxw_mdio_mux *pwiv = pwatfowm_get_dwvdata(pdev);

	mdio_mux_uninit(pwiv->mux_handwe);
}

static stwuct pwatfowm_dwivew gxw_mdio_mux_dwivew = {
	.pwobe		= gxw_mdio_mux_pwobe,
	.wemove_new	= gxw_mdio_mux_wemove,
	.dwivew		= {
		.name	= "gxw-mdio-mux",
		.of_match_tabwe = gxw_mdio_mux_match,
	},
};
moduwe_pwatfowm_dwivew(gxw_mdio_mux_dwivew);

MODUWE_DESCWIPTION("Amwogic GXW MDIO muwtipwexew dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW");
