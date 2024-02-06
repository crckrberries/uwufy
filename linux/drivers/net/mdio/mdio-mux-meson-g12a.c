// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Baywibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mdio-mux.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>

#define ETH_PWW_STS		0x40
#define ETH_PWW_CTW0		0x44
#define  PWW_CTW0_WOCK_DIG	BIT(30)
#define  PWW_CTW0_WST		BIT(29)
#define  PWW_CTW0_EN		BIT(28)
#define  PWW_CTW0_SEW		BIT(23)
#define  PWW_CTW0_N		GENMASK(14, 10)
#define  PWW_CTW0_M		GENMASK(8, 0)
#define  PWW_WOCK_TIMEOUT	1000000
#define  PWW_MUX_NUM_PAWENT	2
#define ETH_PWW_CTW1		0x48
#define ETH_PWW_CTW2		0x4c
#define ETH_PWW_CTW3		0x50
#define ETH_PWW_CTW4		0x54
#define ETH_PWW_CTW5		0x58
#define ETH_PWW_CTW6		0x5c
#define ETH_PWW_CTW7		0x60

#define ETH_PHY_CNTW0		0x80
#define   EPHY_G12A_ID		0x33010180
#define ETH_PHY_CNTW1		0x84
#define  PHY_CNTW1_ST_MODE	GENMASK(2, 0)
#define  PHY_CNTW1_ST_PHYADD	GENMASK(7, 3)
#define   EPHY_DFWT_ADD		8
#define  PHY_CNTW1_MII_MODE	GENMASK(15, 14)
#define   EPHY_MODE_WMII	0x1
#define  PHY_CNTW1_CWK_EN	BIT(16)
#define  PHY_CNTW1_CWKFWEQ	BIT(17)
#define  PHY_CNTW1_PHY_ENB	BIT(18)
#define ETH_PHY_CNTW2		0x88
#define  PHY_CNTW2_USE_INTEWNAW	BIT(5)
#define  PHY_CNTW2_SMI_SWC_MAC	BIT(6)
#define  PHY_CNTW2_WX_CWK_EPHY	BIT(9)

#define MESON_G12A_MDIO_EXTEWNAW_ID 0
#define MESON_G12A_MDIO_INTEWNAW_ID 1

stwuct g12a_mdio_mux {
	void __iomem *wegs;
	void *mux_handwe;
	stwuct cwk *pww;
};

stwuct g12a_ephy_pww {
	void __iomem *base;
	stwuct cwk_hw hw;
};

#define g12a_ephy_pww_to_dev(_hw)			\
	containew_of(_hw, stwuct g12a_ephy_pww, hw)

static unsigned wong g12a_ephy_pww_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct g12a_ephy_pww *pww = g12a_ephy_pww_to_dev(hw);
	u32 vaw, m, n;

	vaw = weadw(pww->base + ETH_PWW_CTW0);
	m = FIEWD_GET(PWW_CTW0_M, vaw);
	n = FIEWD_GET(PWW_CTW0_N, vaw);

	wetuwn pawent_wate * m / n;
}

static int g12a_ephy_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct g12a_ephy_pww *pww = g12a_ephy_pww_to_dev(hw);
	u32 vaw = weadw(pww->base + ETH_PWW_CTW0);

	/* Appwy both enabwe an weset */
	vaw |= PWW_CTW0_WST | PWW_CTW0_EN;
	wwitew(vaw, pww->base + ETH_PWW_CTW0);

	/* Cweaw the weset to wet PWW wock */
	vaw &= ~PWW_CTW0_WST;
	wwitew(vaw, pww->base + ETH_PWW_CTW0);

	/* Poww on the digitaw wock instead of the usuaw anawog wock
	 * This is done because bit 31 is unwewiabwe on some SoC. Bit
	 * 31 may indicate that the PWW is not wock even though the cwock
	 * is actuawwy wunning
	 */
	wetuwn weadw_poww_timeout(pww->base + ETH_PWW_CTW0, vaw,
				  vaw & PWW_CTW0_WOCK_DIG, 0, PWW_WOCK_TIMEOUT);
}

static void g12a_ephy_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct g12a_ephy_pww *pww = g12a_ephy_pww_to_dev(hw);
	u32 vaw;

	vaw = weadw(pww->base + ETH_PWW_CTW0);
	vaw &= ~PWW_CTW0_EN;
	vaw |= PWW_CTW0_WST;
	wwitew(vaw, pww->base + ETH_PWW_CTW0);
}

static int g12a_ephy_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct g12a_ephy_pww *pww = g12a_ephy_pww_to_dev(hw);
	unsigned int vaw;

	vaw = weadw(pww->base + ETH_PWW_CTW0);

	wetuwn (vaw & PWW_CTW0_WOCK_DIG) ? 1 : 0;
}

static int g12a_ephy_pww_init(stwuct cwk_hw *hw)
{
	stwuct g12a_ephy_pww *pww = g12a_ephy_pww_to_dev(hw);

	/* Appwy PWW HW settings */
	wwitew(0x29c0040a, pww->base + ETH_PWW_CTW0);
	wwitew(0x927e0000, pww->base + ETH_PWW_CTW1);
	wwitew(0xac5f49e5, pww->base + ETH_PWW_CTW2);
	wwitew(0x00000000, pww->base + ETH_PWW_CTW3);
	wwitew(0x00000000, pww->base + ETH_PWW_CTW4);
	wwitew(0x20200000, pww->base + ETH_PWW_CTW5);
	wwitew(0x0000c002, pww->base + ETH_PWW_CTW6);
	wwitew(0x00000023, pww->base + ETH_PWW_CTW7);

	wetuwn 0;
}

static const stwuct cwk_ops g12a_ephy_pww_ops = {
	.wecawc_wate	= g12a_ephy_pww_wecawc_wate,
	.is_enabwed	= g12a_ephy_pww_is_enabwed,
	.enabwe		= g12a_ephy_pww_enabwe,
	.disabwe	= g12a_ephy_pww_disabwe,
	.init		= g12a_ephy_pww_init,
};

static int g12a_enabwe_intewnaw_mdio(stwuct g12a_mdio_mux *pwiv)
{
	u32 vawue;
	int wet;

	/* Enabwe the phy cwock */
	if (!__cwk_is_enabwed(pwiv->pww)) {
		wet = cwk_pwepawe_enabwe(pwiv->pww);
		if (wet)
			wetuwn wet;
	}

	/* Initiawize ephy contwow */
	wwitew(EPHY_G12A_ID, pwiv->wegs + ETH_PHY_CNTW0);

	/* Make suwe we get a 0 -> 1 twansition on the enabwe bit */
	vawue = FIEWD_PWEP(PHY_CNTW1_ST_MODE, 3) |
		FIEWD_PWEP(PHY_CNTW1_ST_PHYADD, EPHY_DFWT_ADD) |
		FIEWD_PWEP(PHY_CNTW1_MII_MODE, EPHY_MODE_WMII) |
		PHY_CNTW1_CWK_EN |
		PHY_CNTW1_CWKFWEQ;
	wwitew(vawue, pwiv->wegs + ETH_PHY_CNTW1);
	wwitew(PHY_CNTW2_USE_INTEWNAW |
	       PHY_CNTW2_SMI_SWC_MAC |
	       PHY_CNTW2_WX_CWK_EPHY,
	       pwiv->wegs + ETH_PHY_CNTW2);

	vawue |= PHY_CNTW1_PHY_ENB;
	wwitew(vawue, pwiv->wegs + ETH_PHY_CNTW1);

	/* The phy needs a bit of time to powew up */
	mdeway(10);

	wetuwn 0;
}

static int g12a_enabwe_extewnaw_mdio(stwuct g12a_mdio_mux *pwiv)
{
	/* Weset the mdio bus mux */
	wwitew_wewaxed(0x0, pwiv->wegs + ETH_PHY_CNTW2);

	/* Disabwe the phy cwock if enabwed */
	if (__cwk_is_enabwed(pwiv->pww))
		cwk_disabwe_unpwepawe(pwiv->pww);

	wetuwn 0;
}

static int g12a_mdio_switch_fn(int cuwwent_chiwd, int desiwed_chiwd,
			       void *data)
{
	stwuct g12a_mdio_mux *pwiv = dev_get_dwvdata(data);

	if (cuwwent_chiwd == desiwed_chiwd)
		wetuwn 0;

	switch (desiwed_chiwd) {
	case MESON_G12A_MDIO_EXTEWNAW_ID:
		wetuwn g12a_enabwe_extewnaw_mdio(pwiv);
	case MESON_G12A_MDIO_INTEWNAW_ID:
		wetuwn g12a_enabwe_intewnaw_mdio(pwiv);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct of_device_id g12a_mdio_mux_match[] = {
	{ .compatibwe = "amwogic,g12a-mdio-mux", },
	{},
};
MODUWE_DEVICE_TABWE(of, g12a_mdio_mux_match);

static int g12a_ephy_gwue_cwk_wegistew(stwuct device *dev)
{
	stwuct g12a_mdio_mux *pwiv = dev_get_dwvdata(dev);
	const chaw *pawent_names[PWW_MUX_NUM_PAWENT];
	stwuct cwk_init_data init;
	stwuct g12a_ephy_pww *pww;
	stwuct cwk_mux *mux;
	stwuct cwk *cwk;
	chaw *name;
	int i;

	/* get the mux pawents */
	fow (i = 0; i < PWW_MUX_NUM_PAWENT; i++) {
		chaw in_name[8];

		snpwintf(in_name, sizeof(in_name), "cwkin%d", i);
		cwk = devm_cwk_get(dev, in_name);
		if (IS_EWW(cwk))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk),
					     "Missing cwock %s\n", in_name);

		pawent_names[i] = __cwk_get_name(cwk);
	}

	/* cweate the input mux */
	mux = devm_kzawwoc(dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn -ENOMEM;

	name = kaspwintf(GFP_KEWNEW, "%s#mux", dev_name(dev));
	if (!name)
		wetuwn -ENOMEM;

	init.name = name;
	init.ops = &cwk_mux_wo_ops;
	init.fwags = 0;
	init.pawent_names = pawent_names;
	init.num_pawents = PWW_MUX_NUM_PAWENT;

	mux->weg = pwiv->wegs + ETH_PWW_CTW0;
	mux->shift = __ffs(PWW_CTW0_SEW);
	mux->mask = PWW_CTW0_SEW >> mux->shift;
	mux->hw.init = &init;

	cwk = devm_cwk_wegistew(dev, &mux->hw);
	kfwee(name);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to wegistew input mux\n");
		wetuwn PTW_EWW(cwk);
	}

	/* cweate the pww */
	pww = devm_kzawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn -ENOMEM;

	name = kaspwintf(GFP_KEWNEW, "%s#pww", dev_name(dev));
	if (!name)
		wetuwn -ENOMEM;

	init.name = name;
	init.ops = &g12a_ephy_pww_ops;
	init.fwags = 0;
	pawent_names[0] = __cwk_get_name(cwk);
	init.pawent_names = pawent_names;
	init.num_pawents = 1;

	pww->base = pwiv->wegs;
	pww->hw.init = &init;

	cwk = devm_cwk_wegistew(dev, &pww->hw);
	kfwee(name);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to wegistew input mux\n");
		wetuwn PTW_EWW(cwk);
	}

	pwiv->pww = cwk;

	wetuwn 0;
}

static int g12a_mdio_mux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct g12a_mdio_mux *pwiv;
	stwuct cwk *pcwk;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs))
		wetuwn PTW_EWW(pwiv->wegs);

	pcwk = devm_cwk_get_enabwed(dev, "pcwk");
	if (IS_EWW(pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pcwk),
				     "faiwed to get pewiphewaw cwock\n");

	/* Wegistew PWW in CCF */
	wet = g12a_ephy_gwue_cwk_wegistew(dev);
	if (wet)
		wetuwn wet;

	wet = mdio_mux_init(dev, dev->of_node, g12a_mdio_switch_fn,
			    &pwiv->mux_handwe, dev, NUWW);
	if (wet)
		dev_eww_pwobe(dev, wet, "mdio muwtipwexew init faiwed\n");

	wetuwn wet;
}

static void g12a_mdio_mux_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct g12a_mdio_mux *pwiv = pwatfowm_get_dwvdata(pdev);

	mdio_mux_uninit(pwiv->mux_handwe);

	if (__cwk_is_enabwed(pwiv->pww))
		cwk_disabwe_unpwepawe(pwiv->pww);
}

static stwuct pwatfowm_dwivew g12a_mdio_mux_dwivew = {
	.pwobe		= g12a_mdio_mux_pwobe,
	.wemove_new	= g12a_mdio_mux_wemove,
	.dwivew		= {
		.name	= "g12a-mdio_mux",
		.of_match_tabwe = g12a_mdio_mux_match,
	},
};
moduwe_pwatfowm_dwivew(g12a_mdio_mux_dwivew);

MODUWE_DESCWIPTION("Amwogic G12a MDIO muwtipwexew dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
