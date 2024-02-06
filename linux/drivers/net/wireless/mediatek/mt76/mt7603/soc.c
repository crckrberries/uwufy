// SPDX-Wicense-Identifiew: ISC

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "mt7603.h"

static int
mt76_wmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt7603_dev *dev;
	void __iomem *mem_base;
	stwuct mt76_dev *mdev;
	int iwq;
	int wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	mem_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mem_base))
		wetuwn PTW_EWW(mem_base);

	mdev = mt76_awwoc_device(&pdev->dev, sizeof(*dev), &mt7603_ops,
				 &mt7603_dwv_ops);
	if (!mdev)
		wetuwn -ENOMEM;

	dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	mt76_mmio_init(mdev, mem_base);

	mdev->wev = (mt76_ww(dev, MT_HW_CHIPID) << 16) |
		    (mt76_ww(dev, MT_HW_WEV) & 0xff);
	dev_info(mdev->dev, "ASIC wevision: %04x\n", mdev->wev);

	mt76_ww(dev, MT_INT_MASK_CSW, 0);

	wet = devm_wequest_iwq(mdev->dev, iwq, mt7603_iwq_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (wet)
		goto ewwow;

	wet = mt7603_wegistew_device(dev);
	if (wet)
		goto ewwow;

	wetuwn 0;
ewwow:
	ieee80211_fwee_hw(mt76_hw(dev));
	wetuwn wet;
}

static void mt76_wmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mt76_dev *mdev = pwatfowm_get_dwvdata(pdev);
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);

	mt7603_unwegistew_device(dev);
}

static const stwuct of_device_id of_wmac_match[] = {
	{ .compatibwe = "mediatek,mt7628-wmac" },
	{},
};

MODUWE_DEVICE_TABWE(of, of_wmac_match);
MODUWE_FIWMWAWE(MT7628_FIWMWAWE_E1);
MODUWE_FIWMWAWE(MT7628_FIWMWAWE_E2);

stwuct pwatfowm_dwivew mt76_wmac_dwivew = {
	.pwobe		= mt76_wmac_pwobe,
	.wemove_new	= mt76_wmac_wemove,
	.dwivew = {
		.name = "mt76_wmac",
		.of_match_tabwe = of_wmac_match,
	},
};
