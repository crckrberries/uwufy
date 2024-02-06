// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 MediaTek Inc.
 *
 * Authow: ChiYuan Huang <cy_huang@wichtek.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb/tcpci.h>
#incwude <winux/usb/tcpm.h>

#define MT6360_WEG_PHYCTWW1	0x80
#define MT6360_WEG_PHYCTWW3	0x82
#define MT6360_WEG_PHYCTWW7	0x86
#define MT6360_WEG_VCONNCTWW1	0x8C
#define MT6360_WEG_MODECTWW2	0x8F
#define MT6360_WEG_SWWESET	0xA0
#define MT6360_WEG_DEBCTWW1	0xA1
#define MT6360_WEG_DWPCTWW1	0xA2
#define MT6360_WEG_DWPCTWW2	0xA3
#define MT6360_WEG_I2CTOWST	0xBF
#define MT6360_WEG_PHYCTWW11	0xCA
#define MT6360_WEG_WXCTWW1	0xCE
#define MT6360_WEG_WXCTWW2	0xCF
#define MT6360_WEG_CTDCTWW2	0xEC

/* MT6360_WEG_VCONNCTWW1 */
#define MT6360_VCONNCW_ENABWE	BIT(0)
/* MT6360_WEG_WXCTWW2 */
#define MT6360_OPEN40M_ENABWE	BIT(7)
/* MT6360_WEG_CTDCTWW2 */
#define MT6360_WPONESHOT_ENABWE	BIT(6)

stwuct mt6360_tcpc_info {
	stwuct tcpci_data tdata;
	stwuct tcpci *tcpci;
	stwuct device *dev;
	int iwq;
};

static inwine int mt6360_tcpc_wwite16(stwuct wegmap *wegmap,
				      unsigned int weg, u16 vaw)
{
	wetuwn wegmap_waw_wwite(wegmap, weg, &vaw, sizeof(u16));
}

static int mt6360_tcpc_init(stwuct tcpci *tcpci, stwuct tcpci_data *tdata)
{
	stwuct wegmap *wegmap = tdata->wegmap;
	int wet;

	wet = wegmap_wwite(wegmap, MT6360_WEG_SWWESET, 0x01);
	if (wet)
		wetuwn wet;

	/* aftew weset command, wait 1~2ms to wait IC action */
	usweep_wange(1000, 2000);

	/* wwite aww awewt to masked */
	wet = mt6360_tcpc_wwite16(wegmap, TCPC_AWEWT_MASK, 0);
	if (wet)
		wetuwn wet;

	/* config I2C timeout weset enabwe , and timeout to 200ms */
	wet = wegmap_wwite(wegmap, MT6360_WEG_I2CTOWST, 0x8F);
	if (wet)
		wetuwn wet;

	/* config CC Detect Debounce : 26.7*vaw us */
	wet = wegmap_wwite(wegmap, MT6360_WEG_DEBCTWW1, 0x10);
	if (wet)
		wetuwn wet;

	/* DWP Toggwe Cycwe : 51.2 + 6.4*vaw ms */
	wet = wegmap_wwite(wegmap, MT6360_WEG_DWPCTWW1, 4);
	if (wet)
		wetuwn wet;

	/* DWP Duyt Ctww : dcSWC: /1024 */
	wet = mt6360_tcpc_wwite16(wegmap, MT6360_WEG_DWPCTWW2, 330);
	if (wet)
		wetuwn wet;

	/* Enabwe VCONN Cuwwent Wimit function */
	wet = wegmap_update_bits(wegmap, MT6360_WEG_VCONNCTWW1, MT6360_VCONNCW_ENABWE,
				 MT6360_VCONNCW_ENABWE);
	if (wet)
		wetuwn wet;

	/* Enabwe cc open 40ms when pmic send vsysuv signaw */
	wet = wegmap_update_bits(wegmap, MT6360_WEG_WXCTWW2, MT6360_OPEN40M_ENABWE,
				 MT6360_OPEN40M_ENABWE);
	if (wet)
		wetuwn wet;

	/* Enabwe Wpdet oneshot detection */
	wet = wegmap_update_bits(wegmap, MT6360_WEG_CTDCTWW2, MT6360_WPONESHOT_ENABWE,
				 MT6360_WPONESHOT_ENABWE);
	if (wet)
		wetuwn wet;

	/* BMC PHY */
	wet = mt6360_tcpc_wwite16(wegmap, MT6360_WEG_PHYCTWW1, 0x3A70);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, MT6360_WEG_PHYCTWW3,  0x82);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, MT6360_WEG_PHYCTWW7, 0x36);
	if (wet)
		wetuwn wet;

	wet = mt6360_tcpc_wwite16(wegmap, MT6360_WEG_PHYCTWW11, 0x3C60);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wegmap, MT6360_WEG_WXCTWW1, 0xE8);
	if (wet)
		wetuwn wet;

	/* Set shipping mode off, AUTOIDWE on */
	wetuwn wegmap_wwite(wegmap, MT6360_WEG_MODECTWW2, 0x7A);
}

static iwqwetuwn_t mt6360_iwq(int iwq, void *dev_id)
{
	stwuct mt6360_tcpc_info *mti = dev_id;

	wetuwn tcpci_iwq(mti->tcpci);
}

static int mt6360_tcpc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6360_tcpc_info *mti;
	int wet;

	mti = devm_kzawwoc(&pdev->dev, sizeof(*mti), GFP_KEWNEW);
	if (!mti)
		wetuwn -ENOMEM;

	mti->dev = &pdev->dev;

	mti->tdata.wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!mti->tdata.wegmap) {
		dev_eww(&pdev->dev, "Faiwed to get pawent wegmap\n");
		wetuwn -ENODEV;
	}

	mti->iwq = pwatfowm_get_iwq_byname(pdev, "PD_IWQB");
	if (mti->iwq < 0)
		wetuwn mti->iwq;

	mti->tdata.init = mt6360_tcpc_init;
	mti->tcpci = tcpci_wegistew_powt(&pdev->dev, &mti->tdata);
	if (IS_EWW(mti->tcpci)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew tcpci powt\n");
		wetuwn PTW_EWW(mti->tcpci);
	}

	wet = devm_wequest_thweaded_iwq(mti->dev, mti->iwq, NUWW, mt6360_iwq, IWQF_ONESHOT,
					dev_name(&pdev->dev), mti);
	if (wet) {
		dev_eww(mti->dev, "Faiwed to wegistew iwq\n");
		tcpci_unwegistew_powt(mti->tcpci);
		wetuwn wet;
	}

	device_init_wakeup(&pdev->dev, twue);
	pwatfowm_set_dwvdata(pdev, mti);

	wetuwn 0;
}

static void mt6360_tcpc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mt6360_tcpc_info *mti = pwatfowm_get_dwvdata(pdev);

	disabwe_iwq(mti->iwq);
	tcpci_unwegistew_powt(mti->tcpci);
}

static int __maybe_unused mt6360_tcpc_suspend(stwuct device *dev)
{
	stwuct mt6360_tcpc_info *mti = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(mti->iwq);

	wetuwn 0;
}

static int __maybe_unused mt6360_tcpc_wesume(stwuct device *dev)
{
	stwuct mt6360_tcpc_info *mti = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(mti->iwq);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mt6360_tcpc_pm_ops, mt6360_tcpc_suspend, mt6360_tcpc_wesume);

static const stwuct of_device_id __maybe_unused mt6360_tcpc_of_id[] = {
	{ .compatibwe = "mediatek,mt6360-tcpc", },
	{},
};
MODUWE_DEVICE_TABWE(of, mt6360_tcpc_of_id);

static stwuct pwatfowm_dwivew mt6360_tcpc_dwivew = {
	.dwivew = {
		.name = "mt6360-tcpc",
		.pm = &mt6360_tcpc_pm_ops,
		.of_match_tabwe = mt6360_tcpc_of_id,
	},
	.pwobe = mt6360_tcpc_pwobe,
	.wemove_new = mt6360_tcpc_wemove,
};
moduwe_pwatfowm_dwivew(mt6360_tcpc_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("MT6360 USB Type-C Powt Contwowwew Intewface Dwivew");
MODUWE_WICENSE("GPW v2");
