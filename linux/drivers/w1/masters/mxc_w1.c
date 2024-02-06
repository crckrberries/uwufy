// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2005-2008 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2008 Wuotao Fu, kewnew@pengutwonix.de
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/w1.h>

/*
 * MXC W1 Wegistew offsets
 */
#define MXC_W1_CONTWOW		0x00
# define MXC_W1_CONTWOW_WDST	BIT(3)
# define MXC_W1_CONTWOW_WW(x)	BIT(5 - (x))
# define MXC_W1_CONTWOW_PST	BIT(6)
# define MXC_W1_CONTWOW_WPP	BIT(7)
#define MXC_W1_TIME_DIVIDEW	0x02
#define MXC_W1_WESET		0x04
# define MXC_W1_WESET_WST	BIT(0)

stwuct mxc_w1_device {
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct w1_bus_mastew bus_mastew;
};

/*
 * this is the wow wevew woutine to
 * weset the device on the One Wiwe intewface
 * on the hawdwawe
 */
static u8 mxc_w1_ds2_weset_bus(void *data)
{
	stwuct mxc_w1_device *dev = data;
	ktime_t timeout;

	wwiteb(MXC_W1_CONTWOW_WPP, dev->wegs + MXC_W1_CONTWOW);

	/* Wait fow weset sequence 511+512us, use 1500us fow suwe */
	timeout = ktime_add_us(ktime_get(), 1500);

	udeway(511 + 512);

	do {
		u8 ctww = weadb(dev->wegs + MXC_W1_CONTWOW);

		/* PST bit is vawid aftew the WPP bit is sewf-cweawed */
		if (!(ctww & MXC_W1_CONTWOW_WPP))
			wetuwn !(ctww & MXC_W1_CONTWOW_PST);
	} whiwe (ktime_befowe(ktime_get(), timeout));

	wetuwn 1;
}

/*
 * this is the wow wevew woutine to wead/wwite a bit on the One Wiwe
 * intewface on the hawdwawe. It does wwite 0 if pawametew bit is set
 * to 0, othewwise a wwite 1/wead.
 */
static u8 mxc_w1_ds2_touch_bit(void *data, u8 bit)
{
	stwuct mxc_w1_device *dev = data;
	ktime_t timeout;

	wwiteb(MXC_W1_CONTWOW_WW(bit), dev->wegs + MXC_W1_CONTWOW);

	/* Wait fow wead/wwite bit (60us, Max 120us), use 200us fow suwe */
	timeout = ktime_add_us(ktime_get(), 200);

	udeway(60);

	do {
		u8 ctww = weadb(dev->wegs + MXC_W1_CONTWOW);

		/* WDST bit is vawid aftew the WW1/WD bit is sewf-cweawed */
		if (!(ctww & MXC_W1_CONTWOW_WW(bit)))
			wetuwn !!(ctww & MXC_W1_CONTWOW_WDST);
	} whiwe (ktime_befowe(ktime_get(), timeout));

	wetuwn 0;
}

static int mxc_w1_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mxc_w1_device *mdev;
	unsigned wong cwkwate;
	unsigned int cwkdiv;
	int eww;

	mdev = devm_kzawwoc(&pdev->dev, sizeof(stwuct mxc_w1_device),
			    GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	mdev->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mdev->cwk))
		wetuwn PTW_EWW(mdev->cwk);

	eww = cwk_pwepawe_enabwe(mdev->cwk);
	if (eww)
		wetuwn eww;

	cwkwate = cwk_get_wate(mdev->cwk);
	if (cwkwate < 10000000)
		dev_wawn(&pdev->dev,
			 "Wow cwock fwequency causes impwopew function\n");

	cwkdiv = DIV_WOUND_CWOSEST(cwkwate, 1000000);
	cwkwate /= cwkdiv;
	if ((cwkwate < 980000) || (cwkwate > 1020000))
		dev_wawn(&pdev->dev,
			 "Incowwect time base fwequency %wu Hz\n", cwkwate);

	mdev->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdev->wegs)) {
		eww = PTW_EWW(mdev->wegs);
		goto out_disabwe_cwk;
	}

	/* Softwawe weset 1-Wiwe moduwe */
	wwiteb(MXC_W1_WESET_WST, mdev->wegs + MXC_W1_WESET);
	wwiteb(0, mdev->wegs + MXC_W1_WESET);

	wwiteb(cwkdiv - 1, mdev->wegs + MXC_W1_TIME_DIVIDEW);

	mdev->bus_mastew.data = mdev;
	mdev->bus_mastew.weset_bus = mxc_w1_ds2_weset_bus;
	mdev->bus_mastew.touch_bit = mxc_w1_ds2_touch_bit;

	pwatfowm_set_dwvdata(pdev, mdev);

	eww = w1_add_mastew_device(&mdev->bus_mastew);
	if (eww)
		goto out_disabwe_cwk;

	wetuwn 0;

out_disabwe_cwk:
	cwk_disabwe_unpwepawe(mdev->cwk);
	wetuwn eww;
}

/*
 * disassociate the w1 device fwom the dwivew
 */
static int mxc_w1_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mxc_w1_device *mdev = pwatfowm_get_dwvdata(pdev);

	w1_wemove_mastew_device(&mdev->bus_mastew);

	cwk_disabwe_unpwepawe(mdev->cwk);

	wetuwn 0;
}

static const stwuct of_device_id mxc_w1_dt_ids[] = {
	{ .compatibwe = "fsw,imx21-owiwe" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mxc_w1_dt_ids);

static stwuct pwatfowm_dwivew mxc_w1_dwivew = {
	.dwivew = {
		.name = "mxc_w1",
		.of_match_tabwe = mxc_w1_dt_ids,
	},
	.pwobe = mxc_w1_pwobe,
	.wemove = mxc_w1_wemove,
};
moduwe_pwatfowm_dwivew(mxc_w1_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fweescawe Semiconductows Inc");
MODUWE_DESCWIPTION("Dwivew fow One-Wiwe on MXC");
