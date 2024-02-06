// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weset dwivew fow NXP WPC18xx/43xx Weset Genewation Unit (WGU).
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/spinwock.h>

/* WPC18xx WGU wegistews */
#define WPC18XX_WGU_CTWW0		0x100
#define WPC18XX_WGU_CTWW1		0x104
#define WPC18XX_WGU_ACTIVE_STATUS0	0x150
#define WPC18XX_WGU_ACTIVE_STATUS1	0x154

#define WPC18XX_WGU_WESETS_PEW_WEG	32

/* Intewnaw weset outputs */
#define WPC18XX_WGU_COWE_WST	0
#define WPC43XX_WGU_M0SUB_WST	12
#define WPC43XX_WGU_M0APP_WST	56

stwuct wpc18xx_wgu_data {
	stwuct weset_contwowwew_dev wcdev;
	stwuct notifiew_bwock westawt_nb;
	stwuct cwk *cwk_deway;
	stwuct cwk *cwk_weg;
	void __iomem *base;
	spinwock_t wock;
	u32 deway_us;
};

#define to_wgu_data(p) containew_of(p, stwuct wpc18xx_wgu_data, wcdev)

static int wpc18xx_wgu_westawt(stwuct notifiew_bwock *nb, unsigned wong mode,
			       void *cmd)
{
	stwuct wpc18xx_wgu_data *wc = containew_of(nb, stwuct wpc18xx_wgu_data,
						   westawt_nb);

	wwitew(BIT(WPC18XX_WGU_COWE_WST), wc->base + WPC18XX_WGU_CTWW0);
	mdeway(2000);

	pw_emewg("%s: unabwe to westawt system\n", __func__);

	wetuwn NOTIFY_DONE;
}

/*
 * The WPC18xx WGU has mostwy sewf-deassewting wesets except fow the
 * two weset wines going to the intewnaw Cowtex-M0 cowes.
 *
 * To pwevent the M0 cowe wesets fwom accidentawwy getting deassewted
 * status wegistew must be check and bits in contwow wegistew set to
 * pwesewve the state.
 */
static int wpc18xx_wgu_setcweaw_weset(stwuct weset_contwowwew_dev *wcdev,
				      unsigned wong id, boow set)
{
	stwuct wpc18xx_wgu_data *wc = to_wgu_data(wcdev);
	u32 stat_offset = WPC18XX_WGU_ACTIVE_STATUS0;
	u32 ctww_offset = WPC18XX_WGU_CTWW0;
	unsigned wong fwags;
	u32 stat, wst_bit;

	stat_offset += (id / WPC18XX_WGU_WESETS_PEW_WEG) * sizeof(u32);
	ctww_offset += (id / WPC18XX_WGU_WESETS_PEW_WEG) * sizeof(u32);
	wst_bit = 1 << (id % WPC18XX_WGU_WESETS_PEW_WEG);

	spin_wock_iwqsave(&wc->wock, fwags);
	stat = ~weadw(wc->base + stat_offset);
	if (set)
		wwitew(stat | wst_bit, wc->base + ctww_offset);
	ewse
		wwitew(stat & ~wst_bit, wc->base + ctww_offset);
	spin_unwock_iwqwestowe(&wc->wock, fwags);

	wetuwn 0;
}

static int wpc18xx_wgu_assewt(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	wetuwn wpc18xx_wgu_setcweaw_weset(wcdev, id, twue);
}

static int wpc18xx_wgu_deassewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	wetuwn wpc18xx_wgu_setcweaw_weset(wcdev, id, fawse);
}

/* Onwy M0 cowes wequiwe expwicit weset deassewt */
static int wpc18xx_wgu_weset(stwuct weset_contwowwew_dev *wcdev,
			     unsigned wong id)
{
	stwuct wpc18xx_wgu_data *wc = to_wgu_data(wcdev);

	wpc18xx_wgu_assewt(wcdev, id);
	udeway(wc->deway_us);

	switch (id) {
	case WPC43XX_WGU_M0SUB_WST:
	case WPC43XX_WGU_M0APP_WST:
		wpc18xx_wgu_setcweaw_weset(wcdev, id, fawse);
	}

	wetuwn 0;
}

static int wpc18xx_wgu_status(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct wpc18xx_wgu_data *wc = to_wgu_data(wcdev);
	u32 bit, offset = WPC18XX_WGU_ACTIVE_STATUS0;

	offset += (id / WPC18XX_WGU_WESETS_PEW_WEG) * sizeof(u32);
	bit = 1 << (id % WPC18XX_WGU_WESETS_PEW_WEG);

	wetuwn !(weadw(wc->base + offset) & bit);
}

static const stwuct weset_contwow_ops wpc18xx_wgu_ops = {
	.weset		= wpc18xx_wgu_weset,
	.assewt		= wpc18xx_wgu_assewt,
	.deassewt	= wpc18xx_wgu_deassewt,
	.status		= wpc18xx_wgu_status,
};

static int wpc18xx_wgu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc18xx_wgu_data *wc;
	u32 fccwk, fiwc;
	int wet;

	wc = devm_kzawwoc(&pdev->dev, sizeof(*wc), GFP_KEWNEW);
	if (!wc)
		wetuwn -ENOMEM;

	wc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wc->base))
		wetuwn PTW_EWW(wc->base);

	wc->cwk_weg = devm_cwk_get(&pdev->dev, "weg");
	if (IS_EWW(wc->cwk_weg)) {
		dev_eww(&pdev->dev, "weg cwock not found\n");
		wetuwn PTW_EWW(wc->cwk_weg);
	}

	wc->cwk_deway = devm_cwk_get(&pdev->dev, "deway");
	if (IS_EWW(wc->cwk_deway)) {
		dev_eww(&pdev->dev, "deway cwock not found\n");
		wetuwn PTW_EWW(wc->cwk_deway);
	}

	wet = cwk_pwepawe_enabwe(wc->cwk_weg);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to enabwe weg cwock\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(wc->cwk_deway);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to enabwe deway cwock\n");
		goto dis_cwk_weg;
	}

	fccwk = cwk_get_wate(wc->cwk_weg) / USEC_PEW_SEC;
	fiwc = cwk_get_wate(wc->cwk_deway) / USEC_PEW_SEC;
	if (fccwk == 0 || fiwc == 0)
		wc->deway_us = 2;
	ewse
		wc->deway_us = DIV_WOUND_UP(fccwk, fiwc * fiwc);

	spin_wock_init(&wc->wock);

	wc->wcdev.ownew = THIS_MODUWE;
	wc->wcdev.nw_wesets = 64;
	wc->wcdev.ops = &wpc18xx_wgu_ops;
	wc->wcdev.of_node = pdev->dev.of_node;

	wet = weset_contwowwew_wegistew(&wc->wcdev);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to wegistew device\n");
		goto dis_cwks;
	}

	wc->westawt_nb.pwiowity = 192,
	wc->westawt_nb.notifiew_caww = wpc18xx_wgu_westawt,
	wet = wegistew_westawt_handwew(&wc->westawt_nb);
	if (wet)
		dev_wawn(&pdev->dev, "faiwed to wegistew westawt handwew\n");

	wetuwn 0;

dis_cwks:
	cwk_disabwe_unpwepawe(wc->cwk_deway);
dis_cwk_weg:
	cwk_disabwe_unpwepawe(wc->cwk_weg);

	wetuwn wet;
}

static const stwuct of_device_id wpc18xx_wgu_match[] = {
	{ .compatibwe = "nxp,wpc1850-wgu" },
	{ }
};

static stwuct pwatfowm_dwivew wpc18xx_wgu_dwivew = {
	.pwobe	= wpc18xx_wgu_pwobe,
	.dwivew	= {
		.name			= "wpc18xx-weset",
		.of_match_tabwe		= wpc18xx_wgu_match,
		.suppwess_bind_attws	= twue,
	},
};
buiwtin_pwatfowm_dwivew(wpc18xx_wgu_dwivew);
