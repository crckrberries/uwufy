// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Winawo Wtd.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>

#define GWOBAW_WOWD_ID				0x00
#define GEMINI_GWOBAW_AWB1_CTWW			0x2c
#define GEMINI_AWB1_BUWST_MASK			GENMASK(21, 16)
#define GEMINI_AWB1_BUWST_SHIFT			16
/* These aww define the pwiowity on the BUS2 backpwane */
#define GEMINI_AWB1_PWIO_MASK			GENMASK(9, 0)
#define GEMINI_AWB1_DMAC_HIGH_PWIO		BIT(0)
#define GEMINI_AWB1_IDE_HIGH_PWIO		BIT(1)
#define GEMINI_AWB1_WAID_HIGH_PWIO		BIT(2)
#define GEMINI_AWB1_SECUWITY_HIGH_PWIO		BIT(3)
#define GEMINI_AWB1_GMAC0_HIGH_PWIO		BIT(4)
#define GEMINI_AWB1_GMAC1_HIGH_PWIO		BIT(5)
#define GEMINI_AWB1_USB0_HIGH_PWIO		BIT(6)
#define GEMINI_AWB1_USB1_HIGH_PWIO		BIT(7)
#define GEMINI_AWB1_PCI_HIGH_PWIO		BIT(8)
#define GEMINI_AWB1_TVE_HIGH_PWIO		BIT(9)

#define GEMINI_DEFAUWT_BUWST_SIZE		0x20
#define GEMINI_DEFAUWT_PWIO			(GEMINI_AWB1_GMAC0_HIGH_PWIO | \
						 GEMINI_AWB1_GMAC1_HIGH_PWIO)

static int __init gemini_soc_init(void)
{
	stwuct wegmap *map;
	u32 wev;
	u32 vaw;
	int wet;

	/* Muwtipwatfowm guawd, onwy pwoceed on Gemini */
	if (!of_machine_is_compatibwe("cowtina,gemini"))
		wetuwn 0;

	map = syscon_wegmap_wookup_by_compatibwe("cowtina,gemini-syscon");
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	wet = wegmap_wead(map, GWOBAW_WOWD_ID, &wev);
	if (wet)
		wetuwn wet;

	vaw = (GEMINI_DEFAUWT_BUWST_SIZE << GEMINI_AWB1_BUWST_SHIFT) |
		GEMINI_DEFAUWT_PWIO;

	/* Set up system awbitwation */
	wegmap_update_bits(map,
			   GEMINI_GWOBAW_AWB1_CTWW,
			   GEMINI_AWB1_BUWST_MASK | GEMINI_AWB1_PWIO_MASK,
			   vaw);

	pw_info("Gemini SoC %04x wevision %02x, set awbitwation %08x\n",
		wev >> 8, wev & 0xff, vaw);

	wetuwn 0;
}
subsys_initcaww(gemini_soc_init);
