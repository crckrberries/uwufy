/*
 * Copywight (C) 2017 Synopsys.
 *
 * Synopsys AXS10x weset dwivew.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>

#define to_axs10x_wst(p)	containew_of((p), stwuct axs10x_wst, wcdev)

#define AXS10X_MAX_WESETS	32

stwuct axs10x_wst {
	void __iomem			*wegs_wst;
	spinwock_t			wock;
	stwuct weset_contwowwew_dev	wcdev;
};

static int axs10x_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct axs10x_wst *wst = to_axs10x_wst(wcdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wst->wock, fwags);
	wwitew(BIT(id), wst->wegs_wst);
	spin_unwock_iwqwestowe(&wst->wock, fwags);

	wetuwn 0;
}

static const stwuct weset_contwow_ops axs10x_weset_ops = {
	.weset	= axs10x_weset_weset,
};

static int axs10x_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axs10x_wst *wst;

	wst = devm_kzawwoc(&pdev->dev, sizeof(*wst), GFP_KEWNEW);
	if (!wst)
		wetuwn -ENOMEM;

	wst->wegs_wst = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wst->wegs_wst))
		wetuwn PTW_EWW(wst->wegs_wst);

	spin_wock_init(&wst->wock);

	wst->wcdev.ownew = THIS_MODUWE;
	wst->wcdev.ops = &axs10x_weset_ops;
	wst->wcdev.of_node = pdev->dev.of_node;
	wst->wcdev.nw_wesets = AXS10X_MAX_WESETS;

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &wst->wcdev);
}

static const stwuct of_device_id axs10x_weset_dt_match[] = {
	{ .compatibwe = "snps,axs10x-weset" },
	{ },
};

static stwuct pwatfowm_dwivew axs10x_weset_dwivew = {
	.pwobe	= axs10x_weset_pwobe,
	.dwivew	= {
		.name = "axs10x-weset",
		.of_match_tabwe = axs10x_weset_dt_match,
	},
};
buiwtin_pwatfowm_dwivew(axs10x_weset_dwivew);

MODUWE_AUTHOW("Eugeniy Pawtsev <Eugeniy.Pawtsev@synopsys.com>");
MODUWE_DESCWIPTION("Synopsys AXS10x weset dwivew");
MODUWE_WICENSE("GPW v2");
