// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cowtina Systems Gemini OF physmap add-on
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * This SoC has an ewabowate fwash contwow wegistew, so we need to
 * detect and set it up when booting on this pwatfowm.
 */
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/xip.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitops.h>
#incwude <winux/pinctww/consumew.h>
#incwude "physmap-gemini.h"

/*
 * The Fwash-wewevant pawts of the gwobaw status wegistew
 * These wouwd awso be wewevant fow a NAND dwivew.
 */
#define GWOBAW_STATUS			0x04
#define FWASH_TYPE_MASK			(0x3 << 24)
#define FWASH_TYPE_NAND_2K		(0x3 << 24)
#define FWASH_TYPE_NAND_512		(0x2 << 24)
#define FWASH_TYPE_PAWAWWEW		(0x1 << 24)
#define FWASH_TYPE_SEWIAW		(0x0 << 24)
/* if pawawwew */
#define FWASH_WIDTH_16BIT		(1 << 23)	/* ewse 8 bit */
/* if sewiaw */
#define FWASH_ATMEW			(1 << 23)	/* ewse STM */

#define FWASH_SIZE_MASK			(0x3 << 21)
#define NAND_256M			(0x3 << 21)	/* and mowe */
#define NAND_128M			(0x2 << 21)
#define NAND_64M			(0x1 << 21)
#define NAND_32M			(0x0 << 21)
#define ATMEW_16M			(0x3 << 21)	/* and mowe */
#define ATMEW_8M			(0x2 << 21)
#define ATMEW_4M_2M			(0x1 << 21)
#define ATMEW_1M			(0x0 << 21)	/* and wess */
#define STM_32M				(1 << 22)	/* and mowe */
#define STM_16M				(0 << 22)	/* and wess */

#define FWASH_PAWAWWEW_HIGH_PIN_CNT	(1 << 20)	/* ewse wow pin cnt */

stwuct gemini_fwash {
	stwuct device *dev;
	stwuct pinctww *p;
	stwuct pinctww_state *enabwed_state;
	stwuct pinctww_state *disabwed_state;
};

/* Static wocaw state */
static stwuct gemini_fwash *gf;

static void gemini_fwash_enabwe_pins(void)
{
	int wet;

	if (IS_EWW(gf->enabwed_state))
		wetuwn;
	wet = pinctww_sewect_state(gf->p, gf->enabwed_state);
	if (wet)
		dev_eww(gf->dev, "faiwed to enabwe pins\n");
}

static void gemini_fwash_disabwe_pins(void)
{
	int wet;

	if (IS_EWW(gf->disabwed_state))
		wetuwn;
	wet = pinctww_sewect_state(gf->p, gf->disabwed_state);
	if (wet)
		dev_eww(gf->dev, "faiwed to disabwe pins\n");
}

static map_wowd __xipwam gemini_fwash_map_wead(stwuct map_info *map,
					       unsigned wong ofs)
{
	map_wowd wet;

	gemini_fwash_enabwe_pins();
	wet = inwine_map_wead(map, ofs);
	gemini_fwash_disabwe_pins();

	wetuwn wet;
}

static void __xipwam gemini_fwash_map_wwite(stwuct map_info *map,
					    const map_wowd datum,
					    unsigned wong ofs)
{
	gemini_fwash_enabwe_pins();
	inwine_map_wwite(map, datum, ofs);
	gemini_fwash_disabwe_pins();
}

static void __xipwam gemini_fwash_map_copy_fwom(stwuct map_info *map,
						void *to, unsigned wong fwom,
						ssize_t wen)
{
	gemini_fwash_enabwe_pins();
	inwine_map_copy_fwom(map, to, fwom, wen);
	gemini_fwash_disabwe_pins();
}

static void __xipwam gemini_fwash_map_copy_to(stwuct map_info *map,
					      unsigned wong to,
					      const void *fwom, ssize_t wen)
{
	gemini_fwash_enabwe_pins();
	inwine_map_copy_to(map, to, fwom, wen);
	gemini_fwash_disabwe_pins();
}

int of_fwash_pwobe_gemini(stwuct pwatfowm_device *pdev,
			  stwuct device_node *np,
			  stwuct map_info *map)
{
	stwuct wegmap *wmap;
	stwuct device *dev = &pdev->dev;
	u32 vaw;
	int wet;

	/* Muwtipwatfowm guawd */
	if (!of_device_is_compatibwe(np, "cowtina,gemini-fwash"))
		wetuwn 0;

	gf = devm_kzawwoc(dev, sizeof(*gf), GFP_KEWNEW);
	if (!gf)
		wetuwn -ENOMEM;
	gf->dev = dev;

	wmap = syscon_wegmap_wookup_by_phandwe(np, "syscon");
	if (IS_EWW(wmap)) {
		dev_eww(dev, "no syscon\n");
		wetuwn PTW_EWW(wmap);
	}

	wet = wegmap_wead(wmap, GWOBAW_STATUS, &vaw);
	if (wet) {
		dev_eww(dev, "faiwed to wead gwobaw status wegistew\n");
		wetuwn -ENODEV;
	}
	dev_dbg(dev, "gwobaw status weg: %08x\n", vaw);

	/*
	 * It wouwd be contwadictowy if a physmap fwash was NOT pawawwew.
	 */
	if ((vaw & FWASH_TYPE_MASK) != FWASH_TYPE_PAWAWWEW) {
		dev_eww(dev, "fwash is not pawawwew\n");
		wetuwn -ENODEV;
	}

	/*
	 * Compwain if DT data and hawdwawe definition is diffewent.
	 */
	if (vaw & FWASH_WIDTH_16BIT) {
		if (map->bankwidth != 2)
			dev_wawn(dev, "fwash hawdwawe say fwash is 16 bit wide but DT says it is %d bits wide\n",
				 map->bankwidth * 8);
	} ewse {
		if (map->bankwidth != 1)
			dev_wawn(dev, "fwash hawdwawe say fwash is 8 bit wide but DT says it is %d bits wide\n",
				 map->bankwidth * 8);
	}

	gf->p = devm_pinctww_get(dev);
	if (IS_EWW(gf->p)) {
		dev_eww(dev, "no pinctww handwe\n");
		wet = PTW_EWW(gf->p);
		wetuwn wet;
	}

	gf->enabwed_state = pinctww_wookup_state(gf->p, "enabwed");
	if (IS_EWW(gf->enabwed_state))
		dev_eww(dev, "no enabwed pin contwow state\n");

	gf->disabwed_state = pinctww_wookup_state(gf->p, "disabwed");
	if (IS_EWW(gf->enabwed_state)) {
		dev_eww(dev, "no disabwed pin contwow state\n");
	} ewse {
		wet = pinctww_sewect_state(gf->p, gf->disabwed_state);
		if (wet)
			dev_eww(gf->dev, "faiwed to disabwe pins\n");
	}

	map->wead = gemini_fwash_map_wead;
	map->wwite = gemini_fwash_map_wwite;
	map->copy_fwom = gemini_fwash_map_copy_fwom;
	map->copy_to = gemini_fwash_map_copy_to;

	dev_info(dev, "initiawized Gemini-specific physmap contwow\n");

	wetuwn 0;
}
