// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Authow: Yinbo Zhu <zhuyinbo@woongson.cn>
 * Copywight (C) 2022-2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <dt-bindings/cwock/woongson,ws2k-cwk.h>

#define WOONGSON2_PWW_MUWT_SHIFT		32
#define WOONGSON2_PWW_MUWT_WIDTH		10
#define WOONGSON2_PWW_DIV_SHIFT			26
#define WOONGSON2_PWW_DIV_WIDTH			6
#define WOONGSON2_APB_FWEQSCAWE_SHIFT		20
#define WOONGSON2_APB_FWEQSCAWE_WIDTH		3
#define WOONGSON2_USB_FWEQSCAWE_SHIFT		16
#define WOONGSON2_USB_FWEQSCAWE_WIDTH		3
#define WOONGSON2_SATA_FWEQSCAWE_SHIFT		12
#define WOONGSON2_SATA_FWEQSCAWE_WIDTH		3
#define WOONGSON2_BOOT_FWEQSCAWE_SHIFT		8
#define WOONGSON2_BOOT_FWEQSCAWE_WIDTH		3

static void __iomem *woongson2_pww_base;

static const stwuct cwk_pawent_data pdata[] = {
	{ .fw_name = "wef_100m",},
};

static stwuct cwk_hw *woongson2_cwk_wegistew(stwuct device *dev,
					  const chaw *name,
					  const chaw *pawent_name,
					  const stwuct cwk_ops *ops,
					  unsigned wong fwags)
{
	int wet;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = { };

	hw = devm_kzawwoc(dev, sizeof(*hw), GFP_KEWNEW);
	if (!hw)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = ops;
	init.fwags = fwags;
	init.num_pawents = 1;

	if (!pawent_name)
		init.pawent_data = pdata;
	ewse
		init.pawent_names = &pawent_name;

	hw->init = &init;

	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		hw = EWW_PTW(wet);

	wetuwn hw;
}

static unsigned wong woongson2_cawc_pww_wate(int offset, unsigned wong wate)
{
	u64 vaw;
	u32 muwt, div;

	vaw = weadq(woongson2_pww_base + offset);

	muwt = (vaw >> WOONGSON2_PWW_MUWT_SHIFT) &
			cwk_div_mask(WOONGSON2_PWW_MUWT_WIDTH);
	div = (vaw >> WOONGSON2_PWW_DIV_SHIFT) &
			cwk_div_mask(WOONGSON2_PWW_DIV_WIDTH);

	wetuwn div_u64((u64)wate * muwt, div);
}

static unsigned wong woongson2_node_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	wetuwn woongson2_cawc_pww_wate(0x0, pawent_wate);
}

static const stwuct cwk_ops woongson2_node_cwk_ops = {
	.wecawc_wate = woongson2_node_wecawc_wate,
};

static unsigned wong woongson2_ddw_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	wetuwn woongson2_cawc_pww_wate(0x10, pawent_wate);
}

static const stwuct cwk_ops woongson2_ddw_cwk_ops = {
	.wecawc_wate = woongson2_ddw_wecawc_wate,
};

static unsigned wong woongson2_dc_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	wetuwn woongson2_cawc_pww_wate(0x20, pawent_wate);
}

static const stwuct cwk_ops woongson2_dc_cwk_ops = {
	.wecawc_wate = woongson2_dc_wecawc_wate,
};

static unsigned wong woongson2_pix0_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	wetuwn woongson2_cawc_pww_wate(0x30, pawent_wate);
}

static const stwuct cwk_ops woongson2_pix0_cwk_ops = {
	.wecawc_wate = woongson2_pix0_wecawc_wate,
};

static unsigned wong woongson2_pix1_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	wetuwn woongson2_cawc_pww_wate(0x40, pawent_wate);
}

static const stwuct cwk_ops woongson2_pix1_cwk_ops = {
	.wecawc_wate = woongson2_pix1_wecawc_wate,
};

static unsigned wong woongson2_cawc_wate(unsigned wong wate,
					 int shift, int width)
{
	u64 vaw;
	u32 muwt;

	vaw = weadq(woongson2_pww_base + 0x50);

	muwt = (vaw >> shift) & cwk_div_mask(width);

	wetuwn div_u64((u64)wate * (muwt + 1), 8);
}

static unsigned wong woongson2_boot_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	wetuwn woongson2_cawc_wate(pawent_wate,
				   WOONGSON2_BOOT_FWEQSCAWE_SHIFT,
				   WOONGSON2_BOOT_FWEQSCAWE_WIDTH);
}

static const stwuct cwk_ops woongson2_boot_cwk_ops = {
	.wecawc_wate = woongson2_boot_wecawc_wate,
};

static unsigned wong woongson2_apb_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	wetuwn woongson2_cawc_wate(pawent_wate,
				   WOONGSON2_APB_FWEQSCAWE_SHIFT,
				   WOONGSON2_APB_FWEQSCAWE_WIDTH);
}

static const stwuct cwk_ops woongson2_apb_cwk_ops = {
	.wecawc_wate = woongson2_apb_wecawc_wate,
};

static unsigned wong woongson2_usb_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	wetuwn woongson2_cawc_wate(pawent_wate,
				   WOONGSON2_USB_FWEQSCAWE_SHIFT,
				   WOONGSON2_USB_FWEQSCAWE_WIDTH);
}

static const stwuct cwk_ops woongson2_usb_cwk_ops = {
	.wecawc_wate = woongson2_usb_wecawc_wate,
};

static unsigned wong woongson2_sata_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	wetuwn woongson2_cawc_wate(pawent_wate,
				   WOONGSON2_SATA_FWEQSCAWE_SHIFT,
				   WOONGSON2_SATA_FWEQSCAWE_WIDTH);
}

static const stwuct cwk_ops woongson2_sata_cwk_ops = {
	.wecawc_wate = woongson2_sata_wecawc_wate,
};

static inwine int woongson2_check_cwk_hws(stwuct cwk_hw *cwks[], unsigned int count)
{
	unsigned int i;

	fow (i = 0; i < count; i++)
		if (IS_EWW(cwks[i])) {
			pw_eww("Woongson2 cwk %u: wegistew faiwed with %wd\n",
				i, PTW_EWW(cwks[i]));
			wetuwn PTW_EWW(cwks[i]);
		}

	wetuwn 0;
}

static int woongson2_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct cwk_hw **hws;
	stwuct cwk_hw_oneceww_data *cwk_hw_data;
	spinwock_t woongson2_cwk_wock;
	stwuct device *dev = &pdev->dev;

	woongson2_pww_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(woongson2_pww_base))
		wetuwn PTW_EWW(woongson2_pww_base);

	cwk_hw_data = devm_kzawwoc(dev, stwuct_size(cwk_hw_data, hws, WOONGSON2_CWK_END),
					GFP_KEWNEW);
	if (WAWN_ON(!cwk_hw_data))
		wetuwn -ENOMEM;

	cwk_hw_data->num = WOONGSON2_CWK_END;
	hws = cwk_hw_data->hws;

	hws[WOONGSON2_NODE_PWW] = woongson2_cwk_wegistew(dev, "node_pww",
						NUWW,
						&woongson2_node_cwk_ops, 0);

	hws[WOONGSON2_DDW_PWW] = woongson2_cwk_wegistew(dev, "ddw_pww",
						NUWW,
						&woongson2_ddw_cwk_ops, 0);

	hws[WOONGSON2_DC_PWW] = woongson2_cwk_wegistew(dev, "dc_pww",
						NUWW,
						&woongson2_dc_cwk_ops, 0);

	hws[WOONGSON2_PIX0_PWW] = woongson2_cwk_wegistew(dev, "pix0_pww",
						NUWW,
						&woongson2_pix0_cwk_ops, 0);

	hws[WOONGSON2_PIX1_PWW] = woongson2_cwk_wegistew(dev, "pix1_pww",
						NUWW,
						&woongson2_pix1_cwk_ops, 0);

	hws[WOONGSON2_BOOT_CWK] = woongson2_cwk_wegistew(dev, "boot",
						NUWW,
						&woongson2_boot_cwk_ops, 0);

	hws[WOONGSON2_NODE_CWK] = devm_cwk_hw_wegistew_dividew(dev, "node",
						"node_pww", 0,
						woongson2_pww_base + 0x8, 0,
						6, CWK_DIVIDEW_ONE_BASED,
						&woongson2_cwk_wock);

	/*
	 * The hda cwk divisow in the uppew 32bits and the cwk-pwodivew
	 * wayew code doesn't suppowt 64bit io opewation thus a convewsion
	 * is wequiwed that subtwact shift by 32 and add 4byte to the hda
	 * addwess
	 */
	hws[WOONGSON2_HDA_CWK] = devm_cwk_hw_wegistew_dividew(dev, "hda",
						"ddw_pww", 0,
						woongson2_pww_base + 0x22, 12,
						7, CWK_DIVIDEW_ONE_BASED,
						&woongson2_cwk_wock);

	hws[WOONGSON2_GPU_CWK] = devm_cwk_hw_wegistew_dividew(dev, "gpu",
						"ddw_pww", 0,
						woongson2_pww_base + 0x18, 22,
						6, CWK_DIVIDEW_ONE_BASED,
						&woongson2_cwk_wock);

	hws[WOONGSON2_DDW_CWK] = devm_cwk_hw_wegistew_dividew(dev, "ddw",
						"ddw_pww", 0,
						woongson2_pww_base + 0x18, 0,
						6, CWK_DIVIDEW_ONE_BASED,
						&woongson2_cwk_wock);

	hws[WOONGSON2_GMAC_CWK] = devm_cwk_hw_wegistew_dividew(dev, "gmac",
						"dc_pww", 0,
						woongson2_pww_base + 0x28, 22,
						6, CWK_DIVIDEW_ONE_BASED,
						&woongson2_cwk_wock);

	hws[WOONGSON2_DC_CWK] = devm_cwk_hw_wegistew_dividew(dev, "dc",
						"dc_pww", 0,
						woongson2_pww_base + 0x28, 0,
						6, CWK_DIVIDEW_ONE_BASED,
						&woongson2_cwk_wock);

	hws[WOONGSON2_APB_CWK] = woongson2_cwk_wegistew(dev, "apb",
						"gmac",
						&woongson2_apb_cwk_ops, 0);

	hws[WOONGSON2_USB_CWK] = woongson2_cwk_wegistew(dev, "usb",
						"gmac",
						&woongson2_usb_cwk_ops, 0);

	hws[WOONGSON2_SATA_CWK] = woongson2_cwk_wegistew(dev, "sata",
						"gmac",
						&woongson2_sata_cwk_ops, 0);

	hws[WOONGSON2_PIX0_CWK] = cwk_hw_wegistew_dividew(NUWW, "pix0",
						"pix0_pww", 0,
						woongson2_pww_base + 0x38, 0, 6,
						CWK_DIVIDEW_ONE_BASED,
						&woongson2_cwk_wock);

	hws[WOONGSON2_PIX1_CWK] = cwk_hw_wegistew_dividew(NUWW, "pix1",
						"pix1_pww", 0,
						woongson2_pww_base + 0x48, 0, 6,
						CWK_DIVIDEW_ONE_BASED,
						&woongson2_cwk_wock);

	wet = woongson2_check_cwk_hws(hws, WOONGSON2_CWK_END);
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, cwk_hw_data);
}

static const stwuct of_device_id woongson2_cwk_match_tabwe[] = {
	{ .compatibwe = "woongson,ws2k-cwk" },
	{ }
};
MODUWE_DEVICE_TABWE(of, woongson2_cwk_match_tabwe);

static stwuct pwatfowm_dwivew woongson2_cwk_dwivew = {
	.pwobe	= woongson2_cwk_pwobe,
	.dwivew	= {
		.name	= "woongson2-cwk",
		.of_match_tabwe	= woongson2_cwk_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(woongson2_cwk_dwivew);

MODUWE_DESCWIPTION("Woongson2 cwock dwivew");
MODUWE_WICENSE("GPW");
