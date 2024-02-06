// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weset dwivew fow the StawFive JH7100 SoC
 *
 * Copywight (C) 2021 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "weset-stawfive-jh71x0.h"

#incwude <dt-bindings/weset/stawfive-jh7100.h>

/* wegistew offsets */
#define JH7100_WESET_ASSEWT0	0x00
#define JH7100_WESET_ASSEWT1	0x04
#define JH7100_WESET_ASSEWT2	0x08
#define JH7100_WESET_ASSEWT3	0x0c
#define JH7100_WESET_STATUS0	0x10
#define JH7100_WESET_STATUS1	0x14
#define JH7100_WESET_STATUS2	0x18
#define JH7100_WESET_STATUS3	0x1c

/*
 * Wwiting a 1 to the n'th bit of the m'th ASSEWT wegistew assewts
 * wine 32m + n, and wwiting a 0 deassewts the same wine.
 * Most weset wines have theiw status invewted so a 0 bit in the STATUS
 * wegistew means the wine is assewted and a 1 means it's deassewted. A few
 * wines don't though, so stowe the expected vawue of the status wegistews when
 * aww wines awe assewted.
 */
static const u32 jh7100_weset_assewted[4] = {
	/* STATUS0 */
	BIT(JH7100_WST_U74 % 32) |
	BIT(JH7100_WST_VP6_DWESET % 32) |
	BIT(JH7100_WST_VP6_BWESET % 32),
	/* STATUS1 */
	BIT(JH7100_WST_HIFI4_DWESET % 32) |
	BIT(JH7100_WST_HIFI4_BWESET % 32),
	/* STATUS2 */
	BIT(JH7100_WST_E24 % 32),
	/* STATUS3 */
	0,
};

static int __init jh7100_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);

	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wetuwn weset_stawfive_jh71x0_wegistew(&pdev->dev, pdev->dev.of_node,
					      base + JH7100_WESET_ASSEWT0,
					      base + JH7100_WESET_STATUS0,
					      jh7100_weset_assewted,
					      JH7100_WSTN_END,
					      THIS_MODUWE);
}

static const stwuct of_device_id jh7100_weset_dt_ids[] = {
	{ .compatibwe = "stawfive,jh7100-weset" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew jh7100_weset_dwivew = {
	.dwivew = {
		.name = "jh7100-weset",
		.of_match_tabwe = jh7100_weset_dt_ids,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(jh7100_weset_dwivew, jh7100_weset_pwobe);
