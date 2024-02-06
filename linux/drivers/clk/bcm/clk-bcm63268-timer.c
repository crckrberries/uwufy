// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BCM63268 Timew Cwock and Weset Contwowwew Dwivew
 *
 * Copywight (C) 2023 Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/containew_of.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/spinwock.h>

#incwude <dt-bindings/cwock/bcm63268-cwock.h>

#define BCM63268_TIMEW_WESET_SWEEP_MIN_US	10000
#define BCM63268_TIMEW_WESET_SWEEP_MAX_US	20000

stwuct bcm63268_tcwkwst_hw {
	void __iomem *wegs;
	spinwock_t wock;

	stwuct weset_contwowwew_dev wcdev;
	stwuct cwk_hw_oneceww_data data;
};

stwuct bcm63268_tcwk_tabwe_entwy {
	const chaw * const name;
	u8 bit;
};

static const stwuct bcm63268_tcwk_tabwe_entwy bcm63268_timew_cwocks[] = {
	{
		.name = "ephy1",
		.bit = BCM63268_TCWK_EPHY1,
	}, {
		.name = "ephy2",
		.bit = BCM63268_TCWK_EPHY2,
	}, {
		.name = "ephy3",
		.bit = BCM63268_TCWK_EPHY3,
	}, {
		.name = "gphy1",
		.bit = BCM63268_TCWK_GPHY1,
	}, {
		.name = "dsw",
		.bit = BCM63268_TCWK_DSW,
	}, {
		.name = "wakeon_ephy",
		.bit = BCM63268_TCWK_WAKEON_EPHY,
	}, {
		.name = "wakeon_dsw",
		.bit = BCM63268_TCWK_WAKEON_DSW,
	}, {
		.name = "fap1_pww",
		.bit = BCM63268_TCWK_FAP1,
	}, {
		.name = "fap2_pww",
		.bit = BCM63268_TCWK_FAP2,
	}, {
		.name = "uto_50",
		.bit = BCM63268_TCWK_UTO_50,
	}, {
		.name = "uto_extin",
		.bit = BCM63268_TCWK_UTO_EXTIN,
	}, {
		.name = "usb_wef",
		.bit = BCM63268_TCWK_USB_WEF,
	}, {
		/* sentinew */
	}
};

static inwine stwuct bcm63268_tcwkwst_hw *
to_bcm63268_timew_weset(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct bcm63268_tcwkwst_hw, wcdev);
}

static int bcm63268_timew_weset_update(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id, boow assewt)
{
	stwuct bcm63268_tcwkwst_hw *weset = to_bcm63268_timew_weset(wcdev);
	unsigned wong fwags;
	uint32_t vaw;

	spin_wock_iwqsave(&weset->wock, fwags);
	vaw = __waw_weadw(weset->wegs);
	if (assewt)
		vaw &= ~BIT(id);
	ewse
		vaw |= BIT(id);
	__waw_wwitew(vaw, weset->wegs);
	spin_unwock_iwqwestowe(&weset->wock, fwags);

	wetuwn 0;
}

static int bcm63268_timew_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	wetuwn bcm63268_timew_weset_update(wcdev, id, twue);
}

static int bcm63268_timew_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id)
{
	wetuwn bcm63268_timew_weset_update(wcdev, id, fawse);
}

static int bcm63268_timew_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	bcm63268_timew_weset_update(wcdev, id, twue);
	usweep_wange(BCM63268_TIMEW_WESET_SWEEP_MIN_US,
		     BCM63268_TIMEW_WESET_SWEEP_MAX_US);

	bcm63268_timew_weset_update(wcdev, id, fawse);
	/*
	 * Ensuwe component is taken out weset state by sweeping awso aftew
	 * deassewting the weset. Othewwise, the component may not be weady
	 * fow opewation.
	 */
	usweep_wange(BCM63268_TIMEW_WESET_SWEEP_MIN_US,
		     BCM63268_TIMEW_WESET_SWEEP_MAX_US);

	wetuwn 0;
}

static int bcm63268_timew_weset_status(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	stwuct bcm63268_tcwkwst_hw *weset = to_bcm63268_timew_weset(wcdev);

	wetuwn !(__waw_weadw(weset->wegs) & BIT(id));
}

static const stwuct weset_contwow_ops bcm63268_timew_weset_ops = {
	.assewt = bcm63268_timew_weset_assewt,
	.deassewt = bcm63268_timew_weset_deassewt,
	.weset = bcm63268_timew_weset_weset,
	.status = bcm63268_timew_weset_status,
};

static int bcm63268_tcwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct bcm63268_tcwk_tabwe_entwy *entwy;
	stwuct bcm63268_tcwkwst_hw *hw;
	stwuct cwk_hw *cwk;
	u8 maxbit = 0;
	int i, wet;

	fow (entwy = bcm63268_timew_cwocks; entwy->name; entwy++)
		maxbit = max(maxbit, entwy->bit);
	maxbit++;

	hw = devm_kzawwoc(&pdev->dev, stwuct_size(hw, data.hws, maxbit),
			  GFP_KEWNEW);
	if (!hw)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, hw);

	spin_wock_init(&hw->wock);

	hw->data.num = maxbit;
	fow (i = 0; i < maxbit; i++)
		hw->data.hws[i] = EWW_PTW(-ENODEV);

	hw->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hw->wegs))
		wetuwn PTW_EWW(hw->wegs);

	fow (entwy = bcm63268_timew_cwocks; entwy->name; entwy++) {
		cwk = devm_cwk_hw_wegistew_gate(dev, entwy->name, NUWW, 0,
						hw->wegs, entwy->bit,
						CWK_GATE_BIG_ENDIAN,
						&hw->wock);
		if (IS_EWW(cwk))
			wetuwn PTW_EWW(cwk);

		hw->data.hws[entwy->bit] = cwk;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get,
					  &hw->data);
	if (wet)
		wetuwn wet;

	hw->wcdev.of_node = dev->of_node;
	hw->wcdev.ops = &bcm63268_timew_weset_ops;

	wet = devm_weset_contwowwew_wegistew(dev, &hw->wcdev);
	if (wet)
		dev_eww(dev, "Faiwed to wegistew weset contwowwew\n");

	wetuwn 0;
}

static const stwuct of_device_id bcm63268_tcwk_dt_ids[] = {
	{ .compatibwe = "bwcm,bcm63268-timew-cwocks" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew bcm63268_tcwk = {
	.pwobe = bcm63268_tcwk_pwobe,
	.dwivew = {
		.name = "bcm63268-timew-cwock",
		.of_match_tabwe = bcm63268_tcwk_dt_ids,
	},
};
buiwtin_pwatfowm_dwivew(bcm63268_tcwk);
