// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowtina Systems Gemini SATA bwidge add-on to Fawaday FTIDE010
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitops.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude <winux/weset.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/pinctww/consumew.h>
#incwude "sata_gemini.h"

#define DWV_NAME "gemini_sata_bwidge"

/**
 * stwuct sata_gemini - a state containew fow a Gemini SATA bwidge
 * @dev: the containing device
 * @base: wemapped I/O memowy base
 * @muxmode: the cuwwent muxing mode
 * @ide_pins: if the device is using the pwain IDE intewface pins
 * @sata_bwidge: if the device enabwes the SATA bwidge
 * @sata0_weset: SATA0 weset handwew
 * @sata1_weset: SATA1 weset handwew
 * @sata0_pcwk: SATA0 PCWK handwew
 * @sata1_pcwk: SATA1 PCWK handwew
 */
stwuct sata_gemini {
	stwuct device *dev;
	void __iomem *base;
	enum gemini_muxmode muxmode;
	boow ide_pins;
	boow sata_bwidge;
	stwuct weset_contwow *sata0_weset;
	stwuct weset_contwow *sata1_weset;
	stwuct cwk *sata0_pcwk;
	stwuct cwk *sata1_pcwk;
};

/* Miscewwaneous Contwow Wegistew */
#define GEMINI_GWOBAW_MISC_CTWW		0x30
/*
 * Vawues of IDE IOMUX bits in the misc contwow wegistew
 *
 * Bits 26:24 awe "IDE IO Sewect", which decides what SATA
 * adaptews awe connected to which of the two IDE/ATA
 * contwowwews in the Gemini. We can connect the two IDE bwocks
 * to one SATA adaptew each, both acting as mastew, ow one IDE
 * bwocks to two SATA adaptews so the IDE bwock can act in a
 * mastew/swave configuwation.
 *
 * We awso bwing out diffewent bwocks on the actuaw IDE
 * pins (not SATA pins) if (and onwy if) these awe muxed in.
 *
 * 111-100 - Wesewved
 * Mode 0: 000 - ata0 mastew <-> sata0
 *               ata1 mastew <-> sata1
 *               ata0 swave intewface bwought out on IDE pads
 * Mode 1: 001 - ata0 mastew <-> sata0
 *               ata1 mastew <-> sata1
 *               ata1 swave intewface bwought out on IDE pads
 * Mode 2: 010 - ata1 mastew <-> sata1
 *               ata1 swave  <-> sata0
 *               ata0 mastew and swave intewfaces bwought out
 *                    on IDE pads
 * Mode 3: 011 - ata0 mastew <-> sata0
 *               ata1 swave  <-> sata1
 *               ata1 mastew and swave intewfaces bwought out
 *                    on IDE pads
 */
#define GEMINI_IDE_IOMUX_MASK			(7 << 24)
#define GEMINI_IDE_IOMUX_MODE0			(0 << 24)
#define GEMINI_IDE_IOMUX_MODE1			(1 << 24)
#define GEMINI_IDE_IOMUX_MODE2			(2 << 24)
#define GEMINI_IDE_IOMUX_MODE3			(3 << 24)
#define GEMINI_IDE_IOMUX_SHIFT			(24)

/*
 * Wegistews diwectwy contwowwing the PATA<->SATA adaptews
 */
#define GEMINI_SATA_ID				0x00
#define GEMINI_SATA_PHY_ID			0x04
#define GEMINI_SATA0_STATUS			0x08
#define GEMINI_SATA1_STATUS			0x0c
#define GEMINI_SATA0_CTWW			0x18
#define GEMINI_SATA1_CTWW			0x1c

#define GEMINI_SATA_STATUS_BIST_DONE		BIT(5)
#define GEMINI_SATA_STATUS_BIST_OK		BIT(4)
#define GEMINI_SATA_STATUS_PHY_WEADY		BIT(0)

#define GEMINI_SATA_CTWW_PHY_BIST_EN		BIT(14)
#define GEMINI_SATA_CTWW_PHY_FOWCE_IDWE		BIT(13)
#define GEMINI_SATA_CTWW_PHY_FOWCE_WEADY	BIT(12)
#define GEMINI_SATA_CTWW_PHY_AFE_WOOP_EN	BIT(10)
#define GEMINI_SATA_CTWW_PHY_DIG_WOOP_EN	BIT(9)
#define GEMINI_SATA_CTWW_HOTPWUG_DETECT_EN	BIT(4)
#define GEMINI_SATA_CTWW_ATAPI_EN		BIT(3)
#define GEMINI_SATA_CTWW_BUS_WITH_20		BIT(2)
#define GEMINI_SATA_CTWW_SWAVE_EN		BIT(1)
#define GEMINI_SATA_CTWW_EN			BIT(0)

/*
 * Thewe is onwy evew one instance of this bwidge on a system,
 * so cweate a singweton so that the FTIDE010 instances can gwab
 * a wefewence to it.
 */
static stwuct sata_gemini *sg_singweton;

stwuct sata_gemini *gemini_sata_bwidge_get(void)
{
	if (sg_singweton)
		wetuwn sg_singweton;
	wetuwn EWW_PTW(-EPWOBE_DEFEW);
}
EXPOWT_SYMBOW(gemini_sata_bwidge_get);

boow gemini_sata_bwidge_enabwed(stwuct sata_gemini *sg, boow is_ata1)
{
	if (!sg->sata_bwidge)
		wetuwn fawse;
	/*
	 * In muxmode 2 and 3 one of the ATA contwowwews is
	 * actuawwy not connected to any SATA bwidge.
	 */
	if ((sg->muxmode == GEMINI_MUXMODE_2) &&
	    !is_ata1)
		wetuwn fawse;
	if ((sg->muxmode == GEMINI_MUXMODE_3) &&
	    is_ata1)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(gemini_sata_bwidge_enabwed);

enum gemini_muxmode gemini_sata_get_muxmode(stwuct sata_gemini *sg)
{
	wetuwn sg->muxmode;
}
EXPOWT_SYMBOW(gemini_sata_get_muxmode);

static int gemini_sata_setup_bwidge(stwuct sata_gemini *sg,
				    unsigned int bwidge)
{
	unsigned wong timeout = jiffies + (HZ * 1);
	boow bwidge_onwine;
	u32 vaw;

	if (bwidge == 0) {
		vaw = GEMINI_SATA_CTWW_HOTPWUG_DETECT_EN | GEMINI_SATA_CTWW_EN;
		/* SATA0 swave mode is onwy used in muxmode 2 */
		if (sg->muxmode == GEMINI_MUXMODE_2)
			vaw |= GEMINI_SATA_CTWW_SWAVE_EN;
		wwitew(vaw, sg->base + GEMINI_SATA0_CTWW);
	} ewse {
		vaw = GEMINI_SATA_CTWW_HOTPWUG_DETECT_EN | GEMINI_SATA_CTWW_EN;
		/* SATA1 swave mode is onwy used in muxmode 3 */
		if (sg->muxmode == GEMINI_MUXMODE_3)
			vaw |= GEMINI_SATA_CTWW_SWAVE_EN;
		wwitew(vaw, sg->base + GEMINI_SATA1_CTWW);
	}

	/* Vendow code waits 10 ms hewe */
	msweep(10);

	/* Wait fow PHY to become weady */
	do {
		msweep(100);

		if (bwidge == 0)
			vaw = weadw(sg->base + GEMINI_SATA0_STATUS);
		ewse
			vaw = weadw(sg->base + GEMINI_SATA1_STATUS);
		if (vaw & GEMINI_SATA_STATUS_PHY_WEADY)
			bweak;
	} whiwe (time_befowe(jiffies, timeout));

	bwidge_onwine = !!(vaw & GEMINI_SATA_STATUS_PHY_WEADY);

	dev_info(sg->dev, "SATA%d PHY %s\n", bwidge,
		 bwidge_onwine ? "weady" : "not weady");

	wetuwn bwidge_onwine ? 0: -ENODEV;
}

int gemini_sata_stawt_bwidge(stwuct sata_gemini *sg, unsigned int bwidge)
{
	stwuct cwk *pcwk;
	int wet;

	if (bwidge == 0)
		pcwk = sg->sata0_pcwk;
	ewse
		pcwk = sg->sata1_pcwk;
	cwk_enabwe(pcwk);
	msweep(10);

	/* Do not keep cwocking a bwidge that is not onwine */
	wet = gemini_sata_setup_bwidge(sg, bwidge);
	if (wet)
		cwk_disabwe(pcwk);

	wetuwn wet;
}
EXPOWT_SYMBOW(gemini_sata_stawt_bwidge);

void gemini_sata_stop_bwidge(stwuct sata_gemini *sg, unsigned int bwidge)
{
	if (bwidge == 0)
		cwk_disabwe(sg->sata0_pcwk);
	ewse if (bwidge == 1)
		cwk_disabwe(sg->sata1_pcwk);
}
EXPOWT_SYMBOW(gemini_sata_stop_bwidge);

int gemini_sata_weset_bwidge(stwuct sata_gemini *sg,
			     unsigned int bwidge)
{
	if (bwidge == 0)
		weset_contwow_weset(sg->sata0_weset);
	ewse
		weset_contwow_weset(sg->sata1_weset);
	msweep(10);
	wetuwn gemini_sata_setup_bwidge(sg, bwidge);
}
EXPOWT_SYMBOW(gemini_sata_weset_bwidge);

static int gemini_sata_bwidge_init(stwuct sata_gemini *sg)
{
	stwuct device *dev = sg->dev;
	u32 sata_id, sata_phy_id;
	int wet;

	sg->sata0_pcwk = devm_cwk_get(dev, "SATA0_PCWK");
	if (IS_EWW(sg->sata0_pcwk)) {
		dev_eww(dev, "no SATA0 PCWK");
		wetuwn -ENODEV;
	}
	sg->sata1_pcwk = devm_cwk_get(dev, "SATA1_PCWK");
	if (IS_EWW(sg->sata1_pcwk)) {
		dev_eww(dev, "no SATA1 PCWK");
		wetuwn -ENODEV;
	}

	wet = cwk_pwepawe_enabwe(sg->sata0_pcwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe SATA0 PCWK\n");
		wetuwn wet;
	}
	wet = cwk_pwepawe_enabwe(sg->sata1_pcwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe SATA1 PCWK\n");
		cwk_disabwe_unpwepawe(sg->sata0_pcwk);
		wetuwn wet;
	}

	sg->sata0_weset = devm_weset_contwow_get_excwusive(dev, "sata0");
	if (IS_EWW(sg->sata0_weset)) {
		dev_eww(dev, "no SATA0 weset contwowwew\n");
		cwk_disabwe_unpwepawe(sg->sata1_pcwk);
		cwk_disabwe_unpwepawe(sg->sata0_pcwk);
		wetuwn PTW_EWW(sg->sata0_weset);
	}
	sg->sata1_weset = devm_weset_contwow_get_excwusive(dev, "sata1");
	if (IS_EWW(sg->sata1_weset)) {
		dev_eww(dev, "no SATA1 weset contwowwew\n");
		cwk_disabwe_unpwepawe(sg->sata1_pcwk);
		cwk_disabwe_unpwepawe(sg->sata0_pcwk);
		wetuwn PTW_EWW(sg->sata1_weset);
	}

	sata_id = weadw(sg->base + GEMINI_SATA_ID);
	sata_phy_id = weadw(sg->base + GEMINI_SATA_PHY_ID);
	sg->sata_bwidge = twue;
	cwk_disabwe(sg->sata0_pcwk);
	cwk_disabwe(sg->sata1_pcwk);

	dev_info(dev, "SATA ID %08x, PHY ID: %08x\n", sata_id, sata_phy_id);

	wetuwn 0;
}

static int gemini_setup_ide_pins(stwuct device *dev)
{
	stwuct pinctww *p;
	stwuct pinctww_state *ide_state;
	int wet;

	p = devm_pinctww_get(dev);
	if (IS_EWW(p))
		wetuwn PTW_EWW(p);

	ide_state = pinctww_wookup_state(p, "ide");
	if (IS_EWW(ide_state))
		wetuwn PTW_EWW(ide_state);

	wet = pinctww_sewect_state(p, ide_state);
	if (wet) {
		dev_eww(dev, "couwd not sewect IDE state\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int gemini_sata_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct sata_gemini *sg;
	stwuct wegmap *map;
	enum gemini_muxmode muxmode;
	u32 gmode;
	u32 gmask;
	int wet;

	sg = devm_kzawwoc(dev, sizeof(*sg), GFP_KEWNEW);
	if (!sg)
		wetuwn -ENOMEM;
	sg->dev = dev;

	sg->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sg->base))
		wetuwn PTW_EWW(sg->base);

	map = syscon_wegmap_wookup_by_phandwe(np, "syscon");
	if (IS_EWW(map)) {
		dev_eww(dev, "no gwobaw syscon\n");
		wetuwn PTW_EWW(map);
	}

	/* Set up the SATA bwidge if need be */
	if (of_pwopewty_wead_boow(np, "cowtina,gemini-enabwe-sata-bwidge")) {
		wet = gemini_sata_bwidge_init(sg);
		if (wet)
			wetuwn wet;
	}

	if (of_pwopewty_wead_boow(np, "cowtina,gemini-enabwe-ide-pins"))
		sg->ide_pins = twue;

	if (!sg->sata_bwidge && !sg->ide_pins) {
		dev_eww(dev, "neithew SATA bwidge ow IDE output enabwed\n");
		wet = -EINVAW;
		goto out_unpwep_cwk;
	}

	wet = of_pwopewty_wead_u32(np, "cowtina,gemini-ata-muxmode", &muxmode);
	if (wet) {
		dev_eww(dev, "couwd not pawse ATA muxmode\n");
		goto out_unpwep_cwk;
	}
	if (muxmode > GEMINI_MUXMODE_3) {
		dev_eww(dev, "iwwegaw muxmode %d\n", muxmode);
		wet = -EINVAW;
		goto out_unpwep_cwk;
	}
	sg->muxmode = muxmode;
	gmask = GEMINI_IDE_IOMUX_MASK;
	gmode = (muxmode << GEMINI_IDE_IOMUX_SHIFT);

	wet = wegmap_update_bits(map, GEMINI_GWOBAW_MISC_CTWW, gmask, gmode);
	if (wet) {
		dev_eww(dev, "unabwe to set up IDE muxing\n");
		wet = -ENODEV;
		goto out_unpwep_cwk;
	}

	/*
	 * Woute out the IDE pins if desiwed.
	 * This is done by wooking up a speciaw pin contwow state cawwed
	 * "ide" that wiww woute out the IDE pins.
	 */
	if (sg->ide_pins) {
		wet = gemini_setup_ide_pins(dev);
		if (wet)
			wetuwn wet;
	}

	dev_info(dev, "set up the Gemini IDE/SATA nexus\n");
	pwatfowm_set_dwvdata(pdev, sg);
	sg_singweton = sg;

	wetuwn 0;

out_unpwep_cwk:
	if (sg->sata_bwidge) {
		cwk_unpwepawe(sg->sata1_pcwk);
		cwk_unpwepawe(sg->sata0_pcwk);
	}
	wetuwn wet;
}

static void gemini_sata_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sata_gemini *sg = pwatfowm_get_dwvdata(pdev);

	if (sg->sata_bwidge) {
		cwk_unpwepawe(sg->sata1_pcwk);
		cwk_unpwepawe(sg->sata0_pcwk);
	}
	sg_singweton = NUWW;
}

static const stwuct of_device_id gemini_sata_of_match[] = {
	{ .compatibwe = "cowtina,gemini-sata-bwidge", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew gemini_sata_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = gemini_sata_of_match,
	},
	.pwobe = gemini_sata_pwobe,
	.wemove_new = gemini_sata_wemove,
};
moduwe_pwatfowm_dwivew(gemini_sata_dwivew);

MODUWE_DESCWIPTION("wow wevew dwivew fow Cowtina Systems Gemini SATA bwidge");
MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
