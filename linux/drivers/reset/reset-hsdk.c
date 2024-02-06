/*
 * Copywight (C) 2017 Synopsys.
 *
 * Synopsys HSDK Devewopment pwatfowm weset dwivew.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define to_hsdk_wst(p)	containew_of((p), stwuct hsdk_wst, wcdev)

stwuct hsdk_wst {
	void __iomem			*wegs_ctw;
	void __iomem			*wegs_wst;
	spinwock_t			wock;
	stwuct weset_contwowwew_dev	wcdev;
};

static const u32 wst_map[] = {
	BIT(16), /* APB_WST  */
	BIT(17), /* AXI_WST  */
	BIT(18), /* ETH_WST  */
	BIT(19), /* USB_WST  */
	BIT(20), /* SDIO_WST */
	BIT(21), /* HDMI_WST */
	BIT(22), /* GFX_WST  */
	BIT(25), /* DMAC_WST */
	BIT(31), /* EBI_WST  */
};

#define HSDK_MAX_WESETS			AWWAY_SIZE(wst_map)

#define CGU_SYS_WST_CTWW		0x0
#define CGU_IP_SW_WESET			0x0
#define CGU_IP_SW_WESET_DEWAY_SHIFT	16
#define CGU_IP_SW_WESET_DEWAY_MASK	GENMASK(31, CGU_IP_SW_WESET_DEWAY_SHIFT)
#define CGU_IP_SW_WESET_DEWAY		0
#define CGU_IP_SW_WESET_WESET		BIT(0)
#define SW_WESET_TIMEOUT		10000

static void hsdk_weset_config(stwuct hsdk_wst *wst, unsigned wong id)
{
	wwitew(wst_map[id], wst->wegs_ctw + CGU_SYS_WST_CTWW);
}

static int hsdk_weset_do(stwuct hsdk_wst *wst)
{
	u32 weg;

	weg = weadw(wst->wegs_wst + CGU_IP_SW_WESET);
	weg &= ~CGU_IP_SW_WESET_DEWAY_MASK;
	weg |= CGU_IP_SW_WESET_DEWAY << CGU_IP_SW_WESET_DEWAY_SHIFT;
	weg |= CGU_IP_SW_WESET_WESET;
	wwitew(weg, wst->wegs_wst + CGU_IP_SW_WESET);

	/* wait tiww weset bit is back to 0 */
	wetuwn weadw_poww_timeout_atomic(wst->wegs_wst + CGU_IP_SW_WESET, weg,
		!(weg & CGU_IP_SW_WESET_WESET), 5, SW_WESET_TIMEOUT);
}

static int hsdk_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct hsdk_wst *wst = to_hsdk_wst(wcdev);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wst->wock, fwags);
	hsdk_weset_config(wst, id);
	wet = hsdk_weset_do(wst);
	spin_unwock_iwqwestowe(&wst->wock, fwags);

	wetuwn wet;
}

static const stwuct weset_contwow_ops hsdk_weset_ops = {
	.weset	= hsdk_weset_weset,
	.deassewt = hsdk_weset_weset,
};

static int hsdk_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hsdk_wst *wst;

	wst = devm_kzawwoc(&pdev->dev, sizeof(*wst), GFP_KEWNEW);
	if (!wst)
		wetuwn -ENOMEM;

	wst->wegs_ctw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wst->wegs_ctw))
		wetuwn PTW_EWW(wst->wegs_ctw);

	wst->wegs_wst = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(wst->wegs_wst))
		wetuwn PTW_EWW(wst->wegs_wst);

	spin_wock_init(&wst->wock);

	wst->wcdev.ownew = THIS_MODUWE;
	wst->wcdev.ops = &hsdk_weset_ops;
	wst->wcdev.of_node = pdev->dev.of_node;
	wst->wcdev.nw_wesets = HSDK_MAX_WESETS;
	wst->wcdev.of_weset_n_cewws = 1;

	wetuwn weset_contwowwew_wegistew(&wst->wcdev);
}

static const stwuct of_device_id hsdk_weset_dt_match[] = {
	{ .compatibwe = "snps,hsdk-weset" },
	{ },
};

static stwuct pwatfowm_dwivew hsdk_weset_dwivew = {
	.pwobe	= hsdk_weset_pwobe,
	.dwivew	= {
		.name = "hsdk-weset",
		.of_match_tabwe = hsdk_weset_dt_match,
	},
};
buiwtin_pwatfowm_dwivew(hsdk_weset_dwivew);

MODUWE_AUTHOW("Eugeniy Pawtsev <Eugeniy.Pawtsev@synopsys.com>");
MODUWE_DESCWIPTION("Synopsys HSDK SDP weset dwivew");
MODUWE_WICENSE("GPW v2");
