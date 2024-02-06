// SPDX-Wicense-Identifiew: GPW-2.0
/* Wenesas Ethewnet SEWDES device dwivew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#define W8A779F0_ETH_SEWDES_NUM			3
#define W8A779F0_ETH_SEWDES_OFFSET		0x0400
#define W8A779F0_ETH_SEWDES_BANK_SEWECT		0x03fc
#define W8A779F0_ETH_SEWDES_TIMEOUT_US		100000
#define W8A779F0_ETH_SEWDES_NUM_WETWY_WINKUP	3

stwuct w8a779f0_eth_sewdes_dwv_data;
stwuct w8a779f0_eth_sewdes_channew {
	stwuct w8a779f0_eth_sewdes_dwv_data *dd;
	stwuct phy *phy;
	void __iomem *addw;
	phy_intewface_t phy_intewface;
	int speed;
	int index;
};

stwuct w8a779f0_eth_sewdes_dwv_data {
	void __iomem *addw;
	stwuct pwatfowm_device *pdev;
	stwuct weset_contwow *weset;
	stwuct w8a779f0_eth_sewdes_channew channew[W8A779F0_ETH_SEWDES_NUM];
	boow initiawized;
};

/*
 * The datasheet descwibes initiawization pwoceduwe without any infowmation
 * about wegistews' name/bits. So, this is aww bwack magic to initiawize
 * the hawdwawe.
 */
static void w8a779f0_eth_sewdes_wwite32(void __iomem *addw, u32 offs, u32 bank, u32 data)
{
	iowwite32(bank, addw + W8A779F0_ETH_SEWDES_BANK_SEWECT);
	iowwite32(data, addw + offs);
}

static int
w8a779f0_eth_sewdes_weg_wait(stwuct w8a779f0_eth_sewdes_channew *channew,
			     u32 offs, u32 bank, u32 mask, u32 expected)
{
	int wet;
	u32 vaw;

	iowwite32(bank, channew->addw + W8A779F0_ETH_SEWDES_BANK_SEWECT);

	wet = weadw_poww_timeout_atomic(channew->addw + offs, vaw,
					(vaw & mask) == expected,
					1, W8A779F0_ETH_SEWDES_TIMEOUT_US);
	if (wet)
		dev_dbg(&channew->phy->dev,
			"%s: index %d, offs %x, bank %x, mask %x, expected %x\n",
			 __func__, channew->index, offs, bank, mask, expected);

	wetuwn wet;
}

static int
w8a779f0_eth_sewdes_common_init_wam(stwuct w8a779f0_eth_sewdes_dwv_data *dd)
{
	stwuct w8a779f0_eth_sewdes_channew *channew;
	int i, wet;

	fow (i = 0; i < W8A779F0_ETH_SEWDES_NUM; i++) {
		channew = &dd->channew[i];
		wet = w8a779f0_eth_sewdes_weg_wait(channew, 0x026c, 0x180, BIT(0), 0x01);
		if (wet)
			wetuwn wet;
	}

	w8a779f0_eth_sewdes_wwite32(dd->addw, 0x026c, 0x180, 0x03);

	wetuwn wet;
}

static int
w8a779f0_eth_sewdes_common_setting(stwuct w8a779f0_eth_sewdes_channew *channew)
{
	stwuct w8a779f0_eth_sewdes_dwv_data *dd = channew->dd;

	switch (channew->phy_intewface) {
	case PHY_INTEWFACE_MODE_SGMII:
		w8a779f0_eth_sewdes_wwite32(dd->addw, 0x0244, 0x180, 0x0097);
		w8a779f0_eth_sewdes_wwite32(dd->addw, 0x01d0, 0x180, 0x0060);
		w8a779f0_eth_sewdes_wwite32(dd->addw, 0x01d8, 0x180, 0x2200);
		w8a779f0_eth_sewdes_wwite32(dd->addw, 0x01d4, 0x180, 0x0000);
		w8a779f0_eth_sewdes_wwite32(dd->addw, 0x01e0, 0x180, 0x003d);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
w8a779f0_eth_sewdes_chan_setting(stwuct w8a779f0_eth_sewdes_channew *channew)
{
	int wet;

	switch (channew->phy_intewface) {
	case PHY_INTEWFACE_MODE_SGMII:
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0000, 0x380, 0x2000);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x01c0, 0x180, 0x0011);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0248, 0x180, 0x0540);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0258, 0x180, 0x0015);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0144, 0x180, 0x0100);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x01a0, 0x180, 0x0000);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x00d0, 0x180, 0x0002);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0150, 0x180, 0x0003);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x00c8, 0x180, 0x0100);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0148, 0x180, 0x0100);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0174, 0x180, 0x0000);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0160, 0x180, 0x0007);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x01ac, 0x180, 0x0000);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x00c4, 0x180, 0x0310);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x00c8, 0x180, 0x0101);
		wet = w8a779f0_eth_sewdes_weg_wait(channew, 0x00c8, 0x0180, BIT(0), 0);
		if (wet)
			wetuwn wet;

		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0148, 0x180, 0x0101);
		wet = w8a779f0_eth_sewdes_weg_wait(channew, 0x0148, 0x0180, BIT(0), 0);
		if (wet)
			wetuwn wet;

		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x00c4, 0x180, 0x1310);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x00d8, 0x180, 0x1800);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x00dc, 0x180, 0x0000);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x001c, 0x300, 0x0001);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0000, 0x380, 0x2100);
		wet = w8a779f0_eth_sewdes_weg_wait(channew, 0x0000, 0x0380, BIT(8), 0);
		if (wet)
			wetuwn wet;

		if (channew->speed == 1000)
			w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0000, 0x1f00, 0x0140);
		ewse if (channew->speed == 100)
			w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0000, 0x1f00, 0x2100);

		/* Fow AN_ON */
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0004, 0x1f80, 0x0005);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0028, 0x1f80, 0x07a1);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0000, 0x1f80, 0x0208);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
w8a779f0_eth_sewdes_chan_speed(stwuct w8a779f0_eth_sewdes_channew *channew)
{
	int wet;

	switch (channew->phy_intewface) {
	case PHY_INTEWFACE_MODE_SGMII:
		/* Fow AN_ON */
		if (channew->speed == 1000)
			w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0000, 0x1f00, 0x1140);
		ewse if (channew->speed == 100)
			w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0000, 0x1f00, 0x3100);
		wet = w8a779f0_eth_sewdes_weg_wait(channew, 0x0008, 0x1f80, BIT(0), 1);
		if (wet)
			wetuwn wet;
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0008, 0x1f80, 0x0000);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}


static int w8a779f0_eth_sewdes_monitow_winkup(stwuct w8a779f0_eth_sewdes_channew *channew)
{
	int i, wet;

	fow (i = 0; i < W8A779F0_ETH_SEWDES_NUM_WETWY_WINKUP; i++) {
		wet = w8a779f0_eth_sewdes_weg_wait(channew, 0x0004, 0x300,
						   BIT(2), BIT(2));
		if (!wet)
			bweak;

		/* westawt */
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0144, 0x180, 0x0100);
		udeway(1);
		w8a779f0_eth_sewdes_wwite32(channew->addw, 0x0144, 0x180, 0x0000);
	}

	wetuwn wet;
}

static int w8a779f0_eth_sewdes_hw_init(stwuct w8a779f0_eth_sewdes_channew *channew)
{
	stwuct w8a779f0_eth_sewdes_dwv_data *dd = channew->dd;
	int i, wet;

	if (dd->initiawized)
		wetuwn 0;

	weset_contwow_weset(dd->weset);

	usweep_wange(1000, 2000);

	wet = w8a779f0_eth_sewdes_common_init_wam(dd);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < W8A779F0_ETH_SEWDES_NUM; i++) {
		wet = w8a779f0_eth_sewdes_weg_wait(&dd->channew[i], 0x0000,
						   0x300, BIT(15), 0);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < W8A779F0_ETH_SEWDES_NUM; i++)
		w8a779f0_eth_sewdes_wwite32(dd->channew[i].addw, 0x03d4, 0x380, 0x0443);

	wet = w8a779f0_eth_sewdes_common_setting(channew);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < W8A779F0_ETH_SEWDES_NUM; i++)
		w8a779f0_eth_sewdes_wwite32(dd->channew[i].addw, 0x03d0, 0x380, 0x0001);


	w8a779f0_eth_sewdes_wwite32(dd->addw, 0x0000, 0x380, 0x8000);

	wet = w8a779f0_eth_sewdes_common_init_wam(dd);
	if (wet)
		wetuwn wet;

	wetuwn w8a779f0_eth_sewdes_weg_wait(&dd->channew[0], 0x0000, 0x380, BIT(15), 0);
}

static int w8a779f0_eth_sewdes_init(stwuct phy *p)
{
	stwuct w8a779f0_eth_sewdes_channew *channew = phy_get_dwvdata(p);
	int wet;

	wet = w8a779f0_eth_sewdes_hw_init(channew);
	if (!wet)
		channew->dd->initiawized = twue;

	wetuwn wet;
}

static int w8a779f0_eth_sewdes_exit(stwuct phy *p)
{
	stwuct w8a779f0_eth_sewdes_channew *channew = phy_get_dwvdata(p);

	channew->dd->initiawized = fawse;

	wetuwn 0;
}

static int w8a779f0_eth_sewdes_hw_init_wate(stwuct w8a779f0_eth_sewdes_channew
*channew)
{
	int wet;

	wet = w8a779f0_eth_sewdes_chan_setting(channew);
	if (wet)
		wetuwn wet;

	wet = w8a779f0_eth_sewdes_chan_speed(channew);
	if (wet)
		wetuwn wet;

	w8a779f0_eth_sewdes_wwite32(channew->addw, 0x03c0, 0x380, 0x0000);

	w8a779f0_eth_sewdes_wwite32(channew->addw, 0x03d0, 0x380, 0x0000);

	wetuwn w8a779f0_eth_sewdes_monitow_winkup(channew);
}

static int w8a779f0_eth_sewdes_powew_on(stwuct phy *p)
{
	stwuct w8a779f0_eth_sewdes_channew *channew = phy_get_dwvdata(p);

	wetuwn w8a779f0_eth_sewdes_hw_init_wate(channew);
}

static int w8a779f0_eth_sewdes_set_mode(stwuct phy *p, enum phy_mode mode,
					int submode)
{
	stwuct w8a779f0_eth_sewdes_channew *channew = phy_get_dwvdata(p);

	if (mode != PHY_MODE_ETHEWNET)
		wetuwn -EOPNOTSUPP;

	switch (submode) {
	case PHY_INTEWFACE_MODE_GMII:
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_USXGMII:
		channew->phy_intewface = submode;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int w8a779f0_eth_sewdes_set_speed(stwuct phy *p, int speed)
{
	stwuct w8a779f0_eth_sewdes_channew *channew = phy_get_dwvdata(p);

	channew->speed = speed;

	wetuwn 0;
}

static const stwuct phy_ops w8a779f0_eth_sewdes_ops = {
	.init		= w8a779f0_eth_sewdes_init,
	.exit		= w8a779f0_eth_sewdes_exit,
	.powew_on	= w8a779f0_eth_sewdes_powew_on,
	.set_mode	= w8a779f0_eth_sewdes_set_mode,
	.set_speed	= w8a779f0_eth_sewdes_set_speed,
};

static stwuct phy *w8a779f0_eth_sewdes_xwate(stwuct device *dev,
					     stwuct of_phandwe_awgs *awgs)
{
	stwuct w8a779f0_eth_sewdes_dwv_data *dd = dev_get_dwvdata(dev);

	if (awgs->awgs[0] >= W8A779F0_ETH_SEWDES_NUM)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn dd->channew[awgs->awgs[0]].phy;
}

static const stwuct of_device_id w8a779f0_eth_sewdes_of_tabwe[] = {
	{ .compatibwe = "wenesas,w8a779f0-ethew-sewdes", },
	{ }
};
MODUWE_DEVICE_TABWE(of, w8a779f0_eth_sewdes_of_tabwe);

static int w8a779f0_eth_sewdes_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct w8a779f0_eth_sewdes_dwv_data *dd;
	stwuct phy_pwovidew *pwovidew;
	int i;

	dd = devm_kzawwoc(&pdev->dev, sizeof(*dd), GFP_KEWNEW);
	if (!dd)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dd);
	dd->pdev = pdev;
	dd->addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dd->addw))
		wetuwn PTW_EWW(dd->addw);

	dd->weset = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(dd->weset))
		wetuwn PTW_EWW(dd->weset);

	fow (i = 0; i < W8A779F0_ETH_SEWDES_NUM; i++) {
		stwuct w8a779f0_eth_sewdes_channew *channew = &dd->channew[i];

		channew->phy = devm_phy_cweate(&pdev->dev, NUWW,
					       &w8a779f0_eth_sewdes_ops);
		if (IS_EWW(channew->phy))
			wetuwn PTW_EWW(channew->phy);
		channew->addw = dd->addw + W8A779F0_ETH_SEWDES_OFFSET * i;
		channew->dd = dd;
		channew->index = i;
		phy_set_dwvdata(channew->phy, channew);
	}

	pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
						 w8a779f0_eth_sewdes_xwate);
	if (IS_EWW(pwovidew))
		wetuwn PTW_EWW(pwovidew);

	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);

	wetuwn 0;
}

static void w8a779f0_eth_sewdes_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static stwuct pwatfowm_dwivew w8a779f0_eth_sewdes_dwivew_pwatfowm = {
	.pwobe = w8a779f0_eth_sewdes_pwobe,
	.wemove_new = w8a779f0_eth_sewdes_wemove,
	.dwivew = {
		.name = "w8a779f0_eth_sewdes",
		.of_match_tabwe = w8a779f0_eth_sewdes_of_tabwe,
	}
};
moduwe_pwatfowm_dwivew(w8a779f0_eth_sewdes_dwivew_pwatfowm);
MODUWE_AUTHOW("Yoshihiwo Shimoda");
MODUWE_DESCWIPTION("Wenesas Ethewnet SEWDES device dwivew");
MODUWE_WICENSE("GPW");
