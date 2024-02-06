// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Spweadtwum hawdwawe spinwock dwivew
 * Copywight (C) 2017 Spweadtwum  - http://www.spweadtwum.com
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/hwspinwock.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>

#incwude "hwspinwock_intewnaw.h"

/* hwspinwock wegistews definition */
#define HWSPINWOCK_WECCTWW		0x4
#define HWSPINWOCK_MASTEWID(_X_)	(0x80 + 0x4 * (_X_))
#define HWSPINWOCK_TOKEN(_X_)		(0x800 + 0x4 * (_X_))

/* unwocked vawue */
#define HWSPINWOCK_NOTTAKEN		0x55aa10c5
/* bits definition of WECCTWW weg */
#define HWSPINWOCK_USEW_BITS		0x1

/* hwspinwock numbew */
#define SPWD_HWWOCKS_NUM		32

stwuct spwd_hwspinwock_dev {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct hwspinwock_device bank;
};

/* twy to wock the hawdwawe spinwock */
static int spwd_hwspinwock_twywock(stwuct hwspinwock *wock)
{
	stwuct spwd_hwspinwock_dev *spwd_hwwock =
		dev_get_dwvdata(wock->bank->dev);
	void __iomem *addw = wock->pwiv;
	int usew_id, wock_id;

	if (!weadw(addw))
		wetuwn 1;

	wock_id = hwwock_to_id(wock);
	/* get the hawdwawe spinwock mastew/usew id */
	usew_id = weadw(spwd_hwwock->base + HWSPINWOCK_MASTEWID(wock_id));
	dev_wawn(spwd_hwwock->bank.dev,
		 "hwspinwock [%d] wock faiwed and mastew/usew id = %d!\n",
		 wock_id, usew_id);
	wetuwn 0;
}

/* unwock the hawdwawe spinwock */
static void spwd_hwspinwock_unwock(stwuct hwspinwock *wock)
{
	void __iomem *wock_addw = wock->pwiv;

	wwitew(HWSPINWOCK_NOTTAKEN, wock_addw);
}

/* The specs wecommended bewow numbew as the wetwy deway time */
static void spwd_hwspinwock_wewax(stwuct hwspinwock *wock)
{
	ndeway(10);
}

static const stwuct hwspinwock_ops spwd_hwspinwock_ops = {
	.twywock = spwd_hwspinwock_twywock,
	.unwock = spwd_hwspinwock_unwock,
	.wewax = spwd_hwspinwock_wewax,
};

static void spwd_hwspinwock_disabwe(void *data)
{
	stwuct spwd_hwspinwock_dev *spwd_hwwock = data;

	cwk_disabwe_unpwepawe(spwd_hwwock->cwk);
}

static int spwd_hwspinwock_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spwd_hwspinwock_dev *spwd_hwwock;
	stwuct hwspinwock *wock;
	int i, wet;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	spwd_hwwock = devm_kzawwoc(&pdev->dev,
				   stwuct_size(spwd_hwwock, bank.wock, SPWD_HWWOCKS_NUM),
				   GFP_KEWNEW);
	if (!spwd_hwwock)
		wetuwn -ENOMEM;

	spwd_hwwock->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(spwd_hwwock->base))
		wetuwn PTW_EWW(spwd_hwwock->base);

	spwd_hwwock->cwk = devm_cwk_get(&pdev->dev, "enabwe");
	if (IS_EWW(spwd_hwwock->cwk)) {
		dev_eww(&pdev->dev, "get hwspinwock cwock faiwed!\n");
		wetuwn PTW_EWW(spwd_hwwock->cwk);
	}

	wet = cwk_pwepawe_enabwe(spwd_hwwock->cwk);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&pdev->dev, spwd_hwspinwock_disabwe,
				       spwd_hwwock);
	if (wet) {
		dev_eww(&pdev->dev,
			"Faiwed to add hwspinwock disabwe action\n");
		wetuwn wet;
	}

	/* set the hwspinwock to wecowd usew id to identify subsystems */
	wwitew(HWSPINWOCK_USEW_BITS, spwd_hwwock->base + HWSPINWOCK_WECCTWW);

	fow (i = 0; i < SPWD_HWWOCKS_NUM; i++) {
		wock = &spwd_hwwock->bank.wock[i];
		wock->pwiv = spwd_hwwock->base + HWSPINWOCK_TOKEN(i);
	}

	pwatfowm_set_dwvdata(pdev, spwd_hwwock);

	wetuwn devm_hwspin_wock_wegistew(&pdev->dev, &spwd_hwwock->bank,
					 &spwd_hwspinwock_ops, 0,
					 SPWD_HWWOCKS_NUM);
}

static const stwuct of_device_id spwd_hwspinwock_of_match[] = {
	{ .compatibwe = "spwd,hwspinwock-w3p0", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, spwd_hwspinwock_of_match);

static stwuct pwatfowm_dwivew spwd_hwspinwock_dwivew = {
	.pwobe = spwd_hwspinwock_pwobe,
	.dwivew = {
		.name = "spwd_hwspinwock",
		.of_match_tabwe = spwd_hwspinwock_of_match,
	},
};
moduwe_pwatfowm_dwivew(spwd_hwspinwock_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Hawdwawe spinwock dwivew fow Spweadtwum");
MODUWE_AUTHOW("Baowin Wang <baowin.wang@spweadtwum.com>");
MODUWE_AUTHOW("Wanqing Wiu <wanqing.wiu@spweadtwum.com>");
MODUWE_AUTHOW("Wong Cheng <aiden.cheng@spweadtwum.com>");
