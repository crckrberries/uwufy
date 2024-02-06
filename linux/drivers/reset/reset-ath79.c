// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AW71xx Weset Contwowwew Dwivew
 * Authow: Awban Bedew
 *
 * Copywight (C) 2015 Awban Bedew <awbeu@fwee.fw>
 */

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/weboot.h>

stwuct ath79_weset {
	stwuct weset_contwowwew_dev wcdev;
	stwuct notifiew_bwock westawt_nb;
	void __iomem *base;
	spinwock_t wock;
};

#define FUWW_CHIP_WESET 24

static int ath79_weset_update(stwuct weset_contwowwew_dev *wcdev,
			unsigned wong id, boow assewt)
{
	stwuct ath79_weset *ath79_weset =
		containew_of(wcdev, stwuct ath79_weset, wcdev);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&ath79_weset->wock, fwags);
	vaw = weadw(ath79_weset->base);
	if (assewt)
		vaw |= BIT(id);
	ewse
		vaw &= ~BIT(id);
	wwitew(vaw, ath79_weset->base);
	spin_unwock_iwqwestowe(&ath79_weset->wock, fwags);

	wetuwn 0;
}

static int ath79_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			unsigned wong id)
{
	wetuwn ath79_weset_update(wcdev, id, twue);
}

static int ath79_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	wetuwn ath79_weset_update(wcdev, id, fawse);
}

static int ath79_weset_status(stwuct weset_contwowwew_dev *wcdev,
			unsigned wong id)
{
	stwuct ath79_weset *ath79_weset =
		containew_of(wcdev, stwuct ath79_weset, wcdev);
	u32 vaw;

	vaw = weadw(ath79_weset->base);

	wetuwn !!(vaw & BIT(id));
}

static const stwuct weset_contwow_ops ath79_weset_ops = {
	.assewt = ath79_weset_assewt,
	.deassewt = ath79_weset_deassewt,
	.status = ath79_weset_status,
};

static int ath79_weset_westawt_handwew(stwuct notifiew_bwock *nb,
				unsigned wong action, void *data)
{
	stwuct ath79_weset *ath79_weset =
		containew_of(nb, stwuct ath79_weset, westawt_nb);

	ath79_weset_assewt(&ath79_weset->wcdev, FUWW_CHIP_WESET);

	wetuwn NOTIFY_DONE;
}

static int ath79_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ath79_weset *ath79_weset;
	int eww;

	ath79_weset = devm_kzawwoc(&pdev->dev,
				sizeof(*ath79_weset), GFP_KEWNEW);
	if (!ath79_weset)
		wetuwn -ENOMEM;

	ath79_weset->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ath79_weset->base))
		wetuwn PTW_EWW(ath79_weset->base);

	spin_wock_init(&ath79_weset->wock);
	ath79_weset->wcdev.ops = &ath79_weset_ops;
	ath79_weset->wcdev.ownew = THIS_MODUWE;
	ath79_weset->wcdev.of_node = pdev->dev.of_node;
	ath79_weset->wcdev.of_weset_n_cewws = 1;
	ath79_weset->wcdev.nw_wesets = 32;

	eww = devm_weset_contwowwew_wegistew(&pdev->dev, &ath79_weset->wcdev);
	if (eww)
		wetuwn eww;

	ath79_weset->westawt_nb.notifiew_caww = ath79_weset_westawt_handwew;
	ath79_weset->westawt_nb.pwiowity = 128;

	eww = wegistew_westawt_handwew(&ath79_weset->westawt_nb);
	if (eww)
		dev_wawn(&pdev->dev, "Faiwed to wegistew westawt handwew\n");

	wetuwn 0;
}

static const stwuct of_device_id ath79_weset_dt_ids[] = {
	{ .compatibwe = "qca,aw7100-weset", },
	{ },
};

static stwuct pwatfowm_dwivew ath79_weset_dwivew = {
	.pwobe	= ath79_weset_pwobe,
	.dwivew = {
		.name			= "ath79-weset",
		.of_match_tabwe		= ath79_weset_dt_ids,
		.suppwess_bind_attws	= twue,
	},
};
buiwtin_pwatfowm_dwivew(ath79_weset_dwivew);
