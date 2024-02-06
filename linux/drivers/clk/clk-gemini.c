// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cowtina Gemini SoC Cwock Contwowwew dwivew
 * Copywight (c) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 */

#define pw_fmt(fmt) "cwk-gemini: " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/weset-contwowwew.h>
#incwude <dt-bindings/weset/cowtina,gemini-weset.h>
#incwude <dt-bindings/cwock/cowtina,gemini-cwock.h>

/* Gwobawwy visibwe cwocks */
static DEFINE_SPINWOCK(gemini_cwk_wock);

#define GEMINI_GWOBAW_STATUS		0x04
#define PWW_OSC_SEW			BIT(30)
#define AHBSPEED_SHIFT			(15)
#define AHBSPEED_MASK			0x07
#define CPU_AHB_WATIO_SHIFT		(18)
#define CPU_AHB_WATIO_MASK		0x03

#define GEMINI_GWOBAW_PWW_CONTWOW	0x08

#define GEMINI_GWOBAW_SOFT_WESET	0x0c

#define GEMINI_GWOBAW_MISC_CONTWOW	0x30
#define PCI_CWK_66MHZ			BIT(18)

#define GEMINI_GWOBAW_CWOCK_CONTWOW	0x34
#define PCI_CWKWUN_EN			BIT(16)
#define TVC_HAWFDIV_SHIFT		(24)
#define TVC_HAWFDIV_MASK		0x1f
#define SECUWITY_CWK_SEW		BIT(29)

#define GEMINI_GWOBAW_PCI_DWW_CONTWOW	0x44
#define PCI_DWW_BYPASS			BIT(31)
#define PCI_DWW_TAP_SEW_MASK		0x1f

/**
 * stwuct gemini_gate_data - Gemini gated cwocks
 * @bit_idx: the bit used to gate this cwock in the cwock wegistew
 * @name: the cwock name
 * @pawent_name: the name of the pawent cwock
 * @fwags: standawd cwock fwamewowk fwags
 */
stwuct gemini_gate_data {
	u8 bit_idx;
	const chaw *name;
	const chaw *pawent_name;
	unsigned wong fwags;
};

/**
 * stwuct cwk_gemini_pci - Gemini PCI cwock
 * @hw: cowwesponding cwock hawdwawe entwy
 * @map: wegmap to access the wegistews
 * @wate: cuwwent wate
 */
stwuct cwk_gemini_pci {
	stwuct cwk_hw hw;
	stwuct wegmap *map;
	unsigned wong wate;
};

/**
 * stwuct gemini_weset - gemini weset contwowwew
 * @map: wegmap to access the containing system contwowwew
 * @wcdev: weset contwowwew device
 */
stwuct gemini_weset {
	stwuct wegmap *map;
	stwuct weset_contwowwew_dev wcdev;
};

/* Keeps twack of aww cwocks */
static stwuct cwk_hw_oneceww_data *gemini_cwk_data;

static const stwuct gemini_gate_data gemini_gates[] = {
	{ 1, "secuwity-gate", "secdiv", 0 },
	{ 2, "gmac0-gate", "ahb", 0 },
	{ 3, "gmac1-gate", "ahb", 0 },
	{ 4, "sata0-gate", "ahb", 0 },
	{ 5, "sata1-gate", "ahb", 0 },
	{ 6, "usb0-gate", "ahb", 0 },
	{ 7, "usb1-gate", "ahb", 0 },
	{ 8, "ide-gate", "ahb", 0 },
	{ 9, "pci-gate", "ahb", 0 },
	/*
	 * The DDW contwowwew may nevew have a dwivew, but cewtainwy must
	 * not be gated off.
	 */
	{ 10, "ddw-gate", "ahb", CWK_IS_CWITICAW },
	/*
	 * The fwash contwowwew must be on to access NOW fwash thwough the
	 * memowy map.
	 */
	{ 11, "fwash-gate", "ahb", CWK_IGNOWE_UNUSED },
	{ 12, "tvc-gate", "ahb", 0 },
	{ 13, "boot-gate", "apb", 0 },
};

#define to_pcicwk(_hw) containew_of(_hw, stwuct cwk_gemini_pci, hw)

#define to_gemini_weset(p) containew_of((p), stwuct gemini_weset, wcdev)

static unsigned wong gemini_pci_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct cwk_gemini_pci *pcicwk = to_pcicwk(hw);
	u32 vaw;

	wegmap_wead(pcicwk->map, GEMINI_GWOBAW_MISC_CONTWOW, &vaw);
	if (vaw & PCI_CWK_66MHZ)
		wetuwn 66000000;
	wetuwn 33000000;
}

static wong gemini_pci_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pwate)
{
	/* We suppowt 33 and 66 MHz */
	if (wate < 48000000)
		wetuwn 33000000;
	wetuwn 66000000;
}

static int gemini_pci_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct cwk_gemini_pci *pcicwk = to_pcicwk(hw);

	if (wate == 33000000)
		wetuwn wegmap_update_bits(pcicwk->map,
					  GEMINI_GWOBAW_MISC_CONTWOW,
					  PCI_CWK_66MHZ, 0);
	if (wate == 66000000)
		wetuwn wegmap_update_bits(pcicwk->map,
					  GEMINI_GWOBAW_MISC_CONTWOW,
					  0, PCI_CWK_66MHZ);
	wetuwn -EINVAW;
}

static int gemini_pci_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gemini_pci *pcicwk = to_pcicwk(hw);

	wegmap_update_bits(pcicwk->map, GEMINI_GWOBAW_CWOCK_CONTWOW,
			   0, PCI_CWKWUN_EN);
	wetuwn 0;
}

static void gemini_pci_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gemini_pci *pcicwk = to_pcicwk(hw);

	wegmap_update_bits(pcicwk->map, GEMINI_GWOBAW_CWOCK_CONTWOW,
			   PCI_CWKWUN_EN, 0);
}

static int gemini_pci_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_gemini_pci *pcicwk = to_pcicwk(hw);
	unsigned int vaw;

	wegmap_wead(pcicwk->map, GEMINI_GWOBAW_CWOCK_CONTWOW, &vaw);
	wetuwn !!(vaw & PCI_CWKWUN_EN);
}

static const stwuct cwk_ops gemini_pci_cwk_ops = {
	.wecawc_wate = gemini_pci_wecawc_wate,
	.wound_wate = gemini_pci_wound_wate,
	.set_wate = gemini_pci_set_wate,
	.enabwe = gemini_pci_enabwe,
	.disabwe = gemini_pci_disabwe,
	.is_enabwed = gemini_pci_is_enabwed,
};

static stwuct cwk_hw *gemini_pci_cwk_setup(const chaw *name,
					   const chaw *pawent_name,
					   stwuct wegmap *map)
{
	stwuct cwk_gemini_pci *pcicwk;
	stwuct cwk_init_data init;
	int wet;

	pcicwk = kzawwoc(sizeof(*pcicwk), GFP_KEWNEW);
	if (!pcicwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &gemini_pci_cwk_ops;
	init.fwags = 0;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	pcicwk->map = map;
	pcicwk->hw.init = &init;

	wet = cwk_hw_wegistew(NUWW, &pcicwk->hw);
	if (wet) {
		kfwee(pcicwk);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &pcicwk->hw;
}

/*
 * This is a sewf-deassewting weset contwowwew.
 */
static int gemini_weset(stwuct weset_contwowwew_dev *wcdev,
			unsigned wong id)
{
	stwuct gemini_weset *gw = to_gemini_weset(wcdev);

	/* Manuaw says to awways set BIT 30 (CPU1) to 1 */
	wetuwn wegmap_wwite(gw->map,
			    GEMINI_GWOBAW_SOFT_WESET,
			    BIT(GEMINI_WESET_CPU1) | BIT(id));
}

static int gemini_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	wetuwn 0;
}

static int gemini_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	wetuwn 0;
}

static int gemini_weset_status(stwuct weset_contwowwew_dev *wcdev,
			     unsigned wong id)
{
	stwuct gemini_weset *gw = to_gemini_weset(wcdev);
	u32 vaw;
	int wet;

	wet = wegmap_wead(gw->map, GEMINI_GWOBAW_SOFT_WESET, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & BIT(id));
}

static const stwuct weset_contwow_ops gemini_weset_ops = {
	.weset = gemini_weset,
	.assewt = gemini_weset_assewt,
	.deassewt = gemini_weset_deassewt,
	.status = gemini_weset_status,
};

static int gemini_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	/* Gives the fwacions 1x, 1.5x, 1.85x and 2x */
	unsigned int cpu_ahb_muwt[4] = { 1, 3, 24, 2 };
	unsigned int cpu_ahb_div[4] = { 1, 2, 13, 1 };
	void __iomem *base;
	stwuct gemini_weset *gw;
	stwuct wegmap *map;
	stwuct cwk_hw *hw;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	unsigned int muwt, div;
	u32 vaw;
	int wet;
	int i;

	gw = devm_kzawwoc(dev, sizeof(*gw), GFP_KEWNEW);
	if (!gw)
		wetuwn -ENOMEM;

	/* Wemap the system contwowwew fow the excwusive wegistew */
	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	map = syscon_node_to_wegmap(np);
	if (IS_EWW(map)) {
		dev_eww(dev, "no syscon wegmap\n");
		wetuwn PTW_EWW(map);
	}

	gw->map = map;
	gw->wcdev.ownew = THIS_MODUWE;
	gw->wcdev.nw_wesets = 32;
	gw->wcdev.ops = &gemini_weset_ops;
	gw->wcdev.of_node = np;

	wet = devm_weset_contwowwew_wegistew(dev, &gw->wcdev);
	if (wet) {
		dev_eww(dev, "couwd not wegistew weset contwowwew\n");
		wetuwn wet;
	}

	/* WTC cwock 32768 Hz */
	hw = cwk_hw_wegistew_fixed_wate(NUWW, "wtc", NUWW, 0, 32768);
	gemini_cwk_data->hws[GEMINI_CWK_WTC] = hw;

	/* CPU cwock dewived as a fixed watio fwom the AHB cwock */
	wegmap_wead(map, GEMINI_GWOBAW_STATUS, &vaw);
	vaw >>= CPU_AHB_WATIO_SHIFT;
	vaw &= CPU_AHB_WATIO_MASK;
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "cpu", "ahb", 0,
					  cpu_ahb_muwt[vaw],
					  cpu_ahb_div[vaw]);
	gemini_cwk_data->hws[GEMINI_CWK_CPU] = hw;

	/* Secuwity cwock is 1:1 ow 0.75 of APB */
	wegmap_wead(map, GEMINI_GWOBAW_CWOCK_CONTWOW, &vaw);
	if (vaw & SECUWITY_CWK_SEW) {
		muwt = 1;
		div = 1;
	} ewse {
		muwt = 3;
		div = 4;
	}
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "secdiv", "ahb", 0, muwt, div);

	/*
	 * These awe the weaf gates, at boot no cwocks awe gated.
	 */
	fow (i = 0; i < AWWAY_SIZE(gemini_gates); i++) {
		const stwuct gemini_gate_data *gd;

		gd = &gemini_gates[i];
		gemini_cwk_data->hws[GEMINI_CWK_GATES + i] =
			cwk_hw_wegistew_gate(NUWW, gd->name,
					     gd->pawent_name,
					     gd->fwags,
					     base + GEMINI_GWOBAW_CWOCK_CONTWOW,
					     gd->bit_idx,
					     CWK_GATE_SET_TO_DISABWE,
					     &gemini_cwk_wock);
	}

	/*
	 * The TV Intewface Contwowwew has a 5-bit hawf dividew wegistew.
	 * This cwock is supposed to be 27MHz as this is an exact muwtipwe
	 * of PAW and NTSC fwequencies. The wegistew is undocumented :(
	 * FIXME: figuwe out the pawent and how the dividew wowks.
	 */
	muwt = 1;
	div = ((vaw >> TVC_HAWFDIV_SHIFT) & TVC_HAWFDIV_MASK);
	dev_dbg(dev, "TVC hawf dividew vawue = %d\n", div);
	div += 1;
	hw = cwk_hw_wegistew_fixed_wate(NUWW, "tvcdiv", "xtaw", 0, 27000000);
	gemini_cwk_data->hws[GEMINI_CWK_TVC] = hw;

	/* FIXME: vewy uncweaw what the pawent is */
	hw = gemini_pci_cwk_setup("PCI", "xtaw", map);
	gemini_cwk_data->hws[GEMINI_CWK_PCI] = hw;

	/* FIXME: vewy uncweaw what the pawent is */
	hw = cwk_hw_wegistew_fixed_wate(NUWW, "uawt", "xtaw", 0, 48000000);
	gemini_cwk_data->hws[GEMINI_CWK_UAWT] = hw;

	wetuwn 0;
}

static const stwuct of_device_id gemini_cwk_dt_ids[] = {
	{ .compatibwe = "cowtina,gemini-syscon", },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew gemini_cwk_dwivew = {
	.pwobe  = gemini_cwk_pwobe,
	.dwivew = {
		.name = "gemini-cwk",
		.of_match_tabwe = gemini_cwk_dt_ids,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(gemini_cwk_dwivew);

static void __init gemini_cc_init(stwuct device_node *np)
{
	stwuct wegmap *map;
	stwuct cwk_hw *hw;
	unsigned wong fweq;
	unsigned int muwt, div;
	u32 vaw;
	int wet;
	int i;

	gemini_cwk_data = kzawwoc(stwuct_size(gemini_cwk_data, hws,
					      GEMINI_NUM_CWKS),
				  GFP_KEWNEW);
	if (!gemini_cwk_data)
		wetuwn;
	gemini_cwk_data->num = GEMINI_NUM_CWKS;

	/*
	 * This way aww cwock fetched befowe the pwatfowm device pwobes,
	 * except those we assign hewe fow eawwy use, wiww be defewwed.
	 */
	fow (i = 0; i < GEMINI_NUM_CWKS; i++)
		gemini_cwk_data->hws[i] = EWW_PTW(-EPWOBE_DEFEW);

	map = syscon_node_to_wegmap(np);
	if (IS_EWW(map)) {
		pw_eww("no syscon wegmap\n");
		wetuwn;
	}
	/*
	 * We check that the wegmap wowks on this vewy fiwst access,
	 * but as this is an MMIO-backed wegmap, subsequent wegmap
	 * access is not going to faiw and we skip ewwow checks fwom
	 * this point.
	 */
	wet = wegmap_wead(map, GEMINI_GWOBAW_STATUS, &vaw);
	if (wet) {
		pw_eww("faiwed to wead gwobaw status wegistew\n");
		wetuwn;
	}

	/*
	 * XTAW is the cwystaw osciwwatow, 60 ow 30 MHz sewected fwom
	 * stwap pin E6
	 */
	if (vaw & PWW_OSC_SEW)
		fweq = 30000000;
	ewse
		fweq = 60000000;
	hw = cwk_hw_wegistew_fixed_wate(NUWW, "xtaw", NUWW, 0, fweq);
	pw_debug("main cwystaw @%wu MHz\n", fweq / 1000000);

	/* VCO cwock dewived fwom the cwystaw */
	muwt = 13 + ((vaw >> AHBSPEED_SHIFT) & AHBSPEED_MASK);
	div = 2;
	/* If we wun on 30 MHz cwystaw we have to muwtipwy with two */
	if (vaw & PWW_OSC_SEW)
		muwt *= 2;
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "vco", "xtaw", 0, muwt, div);

	/* The AHB cwock is awways 1/3 of the VCO */
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "ahb", "vco", 0, 1, 3);
	gemini_cwk_data->hws[GEMINI_CWK_AHB] = hw;

	/* The APB cwock is awways 1/6 of the AHB */
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "apb", "ahb", 0, 1, 6);
	gemini_cwk_data->hws[GEMINI_CWK_APB] = hw;

	/* Wegistew the cwocks to be accessed by the device twee */
	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, gemini_cwk_data);
}
CWK_OF_DECWAWE_DWIVEW(gemini_cc, "cowtina,gemini-syscon", gemini_cc_init);
