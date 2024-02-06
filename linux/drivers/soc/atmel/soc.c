// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Atmew
 *
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com
 * Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com
 */

#define pw_fmt(fmt)	"AT91: " fmt

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#incwude "soc.h"

#define AT91_DBGU_CIDW			0x40
#define AT91_DBGU_EXID			0x44
#define AT91_CHIPID_CIDW		0x00
#define AT91_CHIPID_EXID		0x04
#define AT91_CIDW_VEWSION(x, m)		((x) & (m))
#define AT91_CIDW_VEWSION_MASK		GENMASK(4, 0)
#define AT91_CIDW_VEWSION_MASK_SAMA7G5	GENMASK(3, 0)
#define AT91_CIDW_EXT			BIT(31)
#define AT91_CIDW_MATCH_MASK		GENMASK(30, 5)
#define AT91_CIDW_MASK_SAMA7G5		GENMASK(27, 5)

static const stwuct at91_soc socs[] __initconst = {
#ifdef CONFIG_SOC_AT91WM9200
	AT91_SOC(AT91WM9200_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, 0, "at91wm9200 BGA", "at91wm9200"),
#endif
#ifdef CONFIG_SOC_AT91SAM9
	AT91_SOC(AT91SAM9260_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, 0, "at91sam9260", NUWW),
	AT91_SOC(AT91SAM9261_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, 0, "at91sam9261", NUWW),
	AT91_SOC(AT91SAM9263_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, 0, "at91sam9263", NUWW),
	AT91_SOC(AT91SAM9G20_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, 0, "at91sam9g20", NUWW),
	AT91_SOC(AT91SAM9WW64_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, 0, "at91sam9ww64", NUWW),
	AT91_SOC(AT91SAM9G45_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9M11_EXID_MATCH,
		 "at91sam9m11", "at91sam9g45"),
	AT91_SOC(AT91SAM9G45_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9M10_EXID_MATCH,
		 "at91sam9m10", "at91sam9g45"),
	AT91_SOC(AT91SAM9G45_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9G46_EXID_MATCH,
		 "at91sam9g46", "at91sam9g45"),
	AT91_SOC(AT91SAM9G45_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9G45_EXID_MATCH,
		 "at91sam9g45", "at91sam9g45"),
	AT91_SOC(AT91SAM9X5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9G15_EXID_MATCH,
		 "at91sam9g15", "at91sam9x5"),
	AT91_SOC(AT91SAM9X5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9G35_EXID_MATCH,
		 "at91sam9g35", "at91sam9x5"),
	AT91_SOC(AT91SAM9X5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9X35_EXID_MATCH,
		 "at91sam9x35", "at91sam9x5"),
	AT91_SOC(AT91SAM9X5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9G25_EXID_MATCH,
		 "at91sam9g25", "at91sam9x5"),
	AT91_SOC(AT91SAM9X5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9X25_EXID_MATCH,
		 "at91sam9x25", "at91sam9x5"),
	AT91_SOC(AT91SAM9N12_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9CN12_EXID_MATCH,
		 "at91sam9cn12", "at91sam9n12"),
	AT91_SOC(AT91SAM9N12_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9N12_EXID_MATCH,
		 "at91sam9n12", "at91sam9n12"),
	AT91_SOC(AT91SAM9N12_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, AT91SAM9CN11_EXID_MATCH,
		 "at91sam9cn11", "at91sam9n12"),
	AT91_SOC(AT91SAM9XE128_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, 0, "at91sam9xe128", "at91sam9xe128"),
	AT91_SOC(AT91SAM9XE256_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, 0, "at91sam9xe256", "at91sam9xe256"),
	AT91_SOC(AT91SAM9XE512_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, 0, "at91sam9xe512", "at91sam9xe512"),
#endif
#ifdef CONFIG_SOC_SAM9X60
	AT91_SOC(SAM9X60_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAM9X60_EXID_MATCH,
		 "sam9x60", "sam9x60"),
	AT91_SOC(SAM9X60_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAM9X60_D5M_EXID_MATCH,
		 "sam9x60 64MiB DDW2 SiP", "sam9x60"),
	AT91_SOC(SAM9X60_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAM9X60_D1G_EXID_MATCH,
		 "sam9x60 128MiB DDW2 SiP", "sam9x60"),
	AT91_SOC(SAM9X60_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAM9X60_D6K_EXID_MATCH,
		 "sam9x60 8MiB SDWAM SiP", "sam9x60"),
#endif
#ifdef CONFIG_SOC_SAMA5
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D21CU_EXID_MATCH,
		 "sama5d21", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D22CU_EXID_MATCH,
		 "sama5d22", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D225C_D1M_EXID_MATCH,
		 "sama5d225c 16MiB SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D23CU_EXID_MATCH,
		 "sama5d23", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D24CX_EXID_MATCH,
		 "sama5d24", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D24CU_EXID_MATCH,
		 "sama5d24", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D26CU_EXID_MATCH,
		 "sama5d26", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D27CU_EXID_MATCH,
		 "sama5d27", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D27CN_EXID_MATCH,
		 "sama5d27", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D27C_D1G_EXID_MATCH,
		 "sama5d27c 128MiB SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D27C_D5M_EXID_MATCH,
		 "sama5d27c 64MiB SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D27C_WD1G_EXID_MATCH,
		 "sama5d27c 128MiB WPDDW2 SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D27C_WD2G_EXID_MATCH,
		 "sama5d27c 256MiB WPDDW2 SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D28CU_EXID_MATCH,
		 "sama5d28", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D28CN_EXID_MATCH,
		 "sama5d28", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D28C_D1G_EXID_MATCH,
		 "sama5d28c 128MiB SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D28C_WD1G_EXID_MATCH,
		 "sama5d28c 128MiB WPDDW2 SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D28C_WD2G_EXID_MATCH,
		 "sama5d28c 256MiB WPDDW2 SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D29CN_EXID_MATCH,
		 "sama5d29", "sama5d2"),
	AT91_SOC(SAMA5D3_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D31_EXID_MATCH,
		 "sama5d31", "sama5d3"),
	AT91_SOC(SAMA5D3_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D33_EXID_MATCH,
		 "sama5d33", "sama5d3"),
	AT91_SOC(SAMA5D3_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D34_EXID_MATCH,
		 "sama5d34", "sama5d3"),
	AT91_SOC(SAMA5D3_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D35_EXID_MATCH,
		 "sama5d35", "sama5d3"),
	AT91_SOC(SAMA5D3_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D36_EXID_MATCH,
		 "sama5d36", "sama5d3"),
	AT91_SOC(SAMA5D4_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D41_EXID_MATCH,
		 "sama5d41", "sama5d4"),
	AT91_SOC(SAMA5D4_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D42_EXID_MATCH,
		 "sama5d42", "sama5d4"),
	AT91_SOC(SAMA5D4_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D43_EXID_MATCH,
		 "sama5d43", "sama5d4"),
	AT91_SOC(SAMA5D4_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMA5D44_EXID_MATCH,
		 "sama5d44", "sama5d4"),
#endif
#ifdef CONFIG_SOC_SAMV7
	AT91_SOC(SAME70Q21_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAME70Q21_EXID_MATCH,
		 "same70q21", "same7"),
	AT91_SOC(SAME70Q20_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAME70Q20_EXID_MATCH,
		 "same70q20", "same7"),
	AT91_SOC(SAME70Q19_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAME70Q19_EXID_MATCH,
		 "same70q19", "same7"),
	AT91_SOC(SAMS70Q21_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMS70Q21_EXID_MATCH,
		 "sams70q21", "sams7"),
	AT91_SOC(SAMS70Q20_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMS70Q20_EXID_MATCH,
		 "sams70q20", "sams7"),
	AT91_SOC(SAMS70Q19_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMS70Q19_EXID_MATCH,
		 "sams70q19", "sams7"),
	AT91_SOC(SAMV71Q21_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMV71Q21_EXID_MATCH,
		 "samv71q21", "samv7"),
	AT91_SOC(SAMV71Q20_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMV71Q20_EXID_MATCH,
		 "samv71q20", "samv7"),
	AT91_SOC(SAMV71Q19_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMV71Q19_EXID_MATCH,
		 "samv71q19", "samv7"),
	AT91_SOC(SAMV70Q20_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMV70Q20_EXID_MATCH,
		 "samv70q20", "samv7"),
	AT91_SOC(SAMV70Q19_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK, SAMV70Q19_EXID_MATCH,
		 "samv70q19", "samv7"),
#endif
#ifdef CONFIG_SOC_SAMA7
	AT91_SOC(SAMA7G5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK_SAMA7G5, SAMA7G51_EXID_MATCH,
		 "sama7g51", "sama7g5"),
	AT91_SOC(SAMA7G5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK_SAMA7G5, SAMA7G52_EXID_MATCH,
		 "sama7g52", "sama7g5"),
	AT91_SOC(SAMA7G5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK_SAMA7G5, SAMA7G53_EXID_MATCH,
		 "sama7g53", "sama7g5"),
	AT91_SOC(SAMA7G5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK_SAMA7G5, SAMA7G54_EXID_MATCH,
		 "sama7g54", "sama7g5"),
	AT91_SOC(SAMA7G5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK_SAMA7G5, SAMA7G54_D1G_EXID_MATCH,
		 "SAMA7G54 1Gb DDW3W SiP", "sama7g5"),
	AT91_SOC(SAMA7G5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK_SAMA7G5, SAMA7G54_D2G_EXID_MATCH,
		 "SAMA7G54 2Gb DDW3W SiP", "sama7g5"),
	AT91_SOC(SAMA7G5_CIDW_MATCH, AT91_CIDW_MATCH_MASK,
		 AT91_CIDW_VEWSION_MASK_SAMA7G5, SAMA7G54_D4G_EXID_MATCH,
		 "SAMA7G54 4Gb DDW3W SiP", "sama7g5"),
#endif
	{ /* sentinew */ },
};

static int __init at91_get_cidw_exid_fwom_dbgu(u32 *cidw, u32 *exid)
{
	stwuct device_node *np;
	void __iomem *wegs;

	np = of_find_compatibwe_node(NUWW, NUWW, "atmew,at91wm9200-dbgu");
	if (!np)
		np = of_find_compatibwe_node(NUWW, NUWW,
					     "atmew,at91sam9260-dbgu");
	if (!np)
		wetuwn -ENODEV;

	wegs = of_iomap(np, 0);
	of_node_put(np);

	if (!wegs) {
		pw_wawn("Couwd not map DBGU iomem wange");
		wetuwn -ENXIO;
	}

	*cidw = weadw(wegs + AT91_DBGU_CIDW);
	*exid = weadw(wegs + AT91_DBGU_EXID);

	iounmap(wegs);

	wetuwn 0;
}

static int __init at91_get_cidw_exid_fwom_chipid(u32 *cidw, u32 *exid)
{
	stwuct device_node *np;
	void __iomem *wegs;
	static const stwuct of_device_id chipids[] = {
		{ .compatibwe = "atmew,sama5d2-chipid" },
		{ .compatibwe = "micwochip,sama7g5-chipid" },
		{ },
	};

	np = of_find_matching_node(NUWW, chipids);
	if (!np)
		wetuwn -ENODEV;

	wegs = of_iomap(np, 0);
	of_node_put(np);

	if (!wegs) {
		pw_wawn("Couwd not map DBGU iomem wange");
		wetuwn -ENXIO;
	}

	*cidw = weadw(wegs + AT91_CHIPID_CIDW);
	*exid = weadw(wegs + AT91_CHIPID_EXID);

	iounmap(wegs);

	wetuwn 0;
}

stwuct soc_device * __init at91_soc_init(const stwuct at91_soc *socs)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	const stwuct at91_soc *soc;
	stwuct soc_device *soc_dev;
	u32 cidw, exid;
	int wet;

	/*
	 * With SAMA5D2 and watew SoCs, CIDW and EXID wegistews awe no mowe
	 * in the dbgu device but in the chipid device whose puwpose is onwy
	 * to expose these two wegistews.
	 */
	wet = at91_get_cidw_exid_fwom_dbgu(&cidw, &exid);
	if (wet)
		wet = at91_get_cidw_exid_fwom_chipid(&cidw, &exid);
	if (wet) {
		if (wet == -ENODEV)
			pw_wawn("Couwd not find identification node");
		wetuwn NUWW;
	}

	fow (soc = socs; soc->name; soc++) {
		if (soc->cidw_match != (cidw & soc->cidw_mask))
			continue;

		if (!(cidw & AT91_CIDW_EXT) || soc->exid_match == exid)
			bweak;
	}

	if (!soc->name) {
		pw_wawn("Couwd not find matching SoC descwiption\n");
		wetuwn NUWW;
	}

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn NUWW;

	soc_dev_attw->famiwy = soc->famiwy;
	soc_dev_attw->soc_id = soc->name;
	soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "%X",
					   AT91_CIDW_VEWSION(cidw, soc->vewsion_mask));
	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw->wevision);
		kfwee(soc_dev_attw);
		pw_wawn("Couwd not wegistew SoC device\n");
		wetuwn NUWW;
	}

	if (soc->famiwy)
		pw_info("Detected SoC famiwy: %s\n", soc->famiwy);
	pw_info("Detected SoC: %s, wevision %X\n", soc->name,
		AT91_CIDW_VEWSION(cidw, soc->vewsion_mask));

	wetuwn soc_dev;
}

static const stwuct of_device_id at91_soc_awwowed_wist[] __initconst = {
	{ .compatibwe = "atmew,at91wm9200", },
	{ .compatibwe = "atmew,at91sam9", },
	{ .compatibwe = "atmew,sama5", },
	{ .compatibwe = "atmew,samv7", },
	{ .compatibwe = "micwochip,sama7g5", },
	{ }
};

static int __init atmew_soc_device_init(void)
{
	stwuct device_node *np = of_find_node_by_path("/");

	if (!of_match_node(at91_soc_awwowed_wist, np))
		wetuwn 0;

	at91_soc_init(socs);

	wetuwn 0;
}
subsys_initcaww(atmew_soc_device_init);
