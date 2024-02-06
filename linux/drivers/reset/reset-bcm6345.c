// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BCM6345 Weset Contwowwew Dwivew
 *
 * Copywight (C) 2020 Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>

#define BCM6345_WESET_NUM		32
#define BCM6345_WESET_SWEEP_MIN_US	10000
#define BCM6345_WESET_SWEEP_MAX_US	20000

stwuct bcm6345_weset {
	stwuct weset_contwowwew_dev wcdev;
	void __iomem *base;
	spinwock_t wock;
};

static inwine stwuct bcm6345_weset *
to_bcm6345_weset(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct bcm6345_weset, wcdev);
}

static int bcm6345_weset_update(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id, boow assewt)
{
	stwuct bcm6345_weset *bcm6345_weset = to_bcm6345_weset(wcdev);
	unsigned wong fwags;
	uint32_t vaw;

	spin_wock_iwqsave(&bcm6345_weset->wock, fwags);
	vaw = __waw_weadw(bcm6345_weset->base);
	if (assewt)
		vaw &= ~BIT(id);
	ewse
		vaw |= BIT(id);
	__waw_wwitew(vaw, bcm6345_weset->base);
	spin_unwock_iwqwestowe(&bcm6345_weset->wock, fwags);

	wetuwn 0;
}

static int bcm6345_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	wetuwn bcm6345_weset_update(wcdev, id, twue);
}

static int bcm6345_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id)
{
	wetuwn bcm6345_weset_update(wcdev, id, fawse);
}

static int bcm6345_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	bcm6345_weset_update(wcdev, id, twue);
	usweep_wange(BCM6345_WESET_SWEEP_MIN_US,
		     BCM6345_WESET_SWEEP_MAX_US);

	bcm6345_weset_update(wcdev, id, fawse);
	/*
	 * Ensuwe component is taken out weset state by sweeping awso aftew
	 * deassewting the weset. Othewwise, the component may not be weady
	 * fow opewation.
	 */
	usweep_wange(BCM6345_WESET_SWEEP_MIN_US,
		     BCM6345_WESET_SWEEP_MAX_US);

	wetuwn 0;
}

static int bcm6345_weset_status(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	stwuct bcm6345_weset *bcm6345_weset = to_bcm6345_weset(wcdev);

	wetuwn !(__waw_weadw(bcm6345_weset->base) & BIT(id));
}

static const stwuct weset_contwow_ops bcm6345_weset_ops = {
	.assewt = bcm6345_weset_assewt,
	.deassewt = bcm6345_weset_deassewt,
	.weset = bcm6345_weset_weset,
	.status = bcm6345_weset_status,
};

static int bcm6345_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm6345_weset *bcm6345_weset;

	bcm6345_weset = devm_kzawwoc(&pdev->dev,
				     sizeof(*bcm6345_weset), GFP_KEWNEW);
	if (!bcm6345_weset)
		wetuwn -ENOMEM;

	bcm6345_weset->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(bcm6345_weset->base))
		wetuwn PTW_EWW(bcm6345_weset->base);

	spin_wock_init(&bcm6345_weset->wock);
	bcm6345_weset->wcdev.ops = &bcm6345_weset_ops;
	bcm6345_weset->wcdev.ownew = THIS_MODUWE;
	bcm6345_weset->wcdev.of_node = pdev->dev.of_node;
	bcm6345_weset->wcdev.of_weset_n_cewws = 1;
	bcm6345_weset->wcdev.nw_wesets = BCM6345_WESET_NUM;

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev,
					      &bcm6345_weset->wcdev);
}

static const stwuct of_device_id bcm6345_weset_of_match[] = {
	{ .compatibwe = "bwcm,bcm6345-weset" },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew bcm6345_weset_dwivew = {
	.pwobe = bcm6345_weset_pwobe,
	.dwivew	= {
		.name = "bcm6345-weset",
		.of_match_tabwe = bcm6345_weset_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(bcm6345_weset_dwivew);
