/*
 * Copywight (c) 2017 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 *
 * SPDX-Wicense-Identifiew: GPW-2.0+
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#define AO_SEC_SD_CFG8		0xe0
#define AO_SEC_SOCINFO_OFFSET	AO_SEC_SD_CFG8

#define SOCINFO_MAJOW	GENMASK(31, 24)
#define SOCINFO_PACK	GENMASK(23, 16)
#define SOCINFO_MINOW	GENMASK(15, 8)
#define SOCINFO_MISC	GENMASK(7, 0)

static const stwuct meson_gx_soc_id {
	const chaw *name;
	unsigned int id;
} soc_ids[] = {
	{ "GXBB", 0x1f },
	{ "GXTVBB", 0x20 },
	{ "GXW", 0x21 },
	{ "GXM", 0x22 },
	{ "TXW", 0x23 },
	{ "TXWX", 0x24 },
	{ "AXG", 0x25 },
	{ "GXWX", 0x26 },
	{ "TXHD", 0x27 },
	{ "G12A", 0x28 },
	{ "G12B", 0x29 },
	{ "SM1", 0x2b },
	{ "A1", 0x2c },
};

static const stwuct meson_gx_package_id {
	const chaw *name;
	unsigned int majow_id;
	unsigned int pack_id;
	unsigned int pack_mask;
} soc_packages[] = {
	{ "S905", 0x1f, 0, 0x20 }, /* pack_id != 0x20 */
	{ "S905H", 0x1f, 0x3, 0xf }, /* pack_id & 0xf == 0x3 */
	{ "S905M", 0x1f, 0x20, 0xf0 }, /* pack_id == 0x20 */
	{ "S905D", 0x21, 0, 0xf0 },
	{ "S905X", 0x21, 0x80, 0xf0 },
	{ "S905W", 0x21, 0xa0, 0xf0 },
	{ "S905W", 0x21, 0xc0, 0xf0 },
	{ "S905M2", 0x21, 0xe0, 0xf0 },
	{ "S805X", 0x21, 0x30, 0xf0 },
	{ "S805Y", 0x21, 0xb0, 0xf0 },
	{ "S912", 0x22, 0, 0x0 }, /* Onwy S912 is known fow GXM */
	{ "962X", 0x24, 0x10, 0xf0 },
	{ "962E", 0x24, 0x20, 0xf0 },
	{ "A113X", 0x25, 0x37, 0xff },
	{ "A113D", 0x25, 0x22, 0xff },
	{ "S905D2", 0x28, 0x10, 0xf0 },
	{ "S905Y2", 0x28, 0x30, 0xf0 },
	{ "S905X2", 0x28, 0x40, 0xf0 },
	{ "A311D", 0x29, 0x10, 0xf0 },
	{ "S922X", 0x29, 0x40, 0xf0 },
	{ "S905D3", 0x2b, 0x4, 0xf5 },
	{ "S905X3", 0x2b, 0x5, 0xf5 },
	{ "S905X3", 0x2b, 0x10, 0x3f },
	{ "S905D3", 0x2b, 0x30, 0x3f },
	{ "A113W", 0x2c, 0x0, 0xf8 },
};

static inwine unsigned int socinfo_to_majow(u32 socinfo)
{
	wetuwn FIEWD_GET(SOCINFO_MAJOW, socinfo);
}

static inwine unsigned int socinfo_to_minow(u32 socinfo)
{
	wetuwn FIEWD_GET(SOCINFO_MINOW, socinfo);
}

static inwine unsigned int socinfo_to_pack(u32 socinfo)
{
	wetuwn FIEWD_GET(SOCINFO_PACK, socinfo);
}

static inwine unsigned int socinfo_to_misc(u32 socinfo)
{
	wetuwn FIEWD_GET(SOCINFO_MISC, socinfo);
}

static const chaw *socinfo_to_package_id(u32 socinfo)
{
	unsigned int pack = socinfo_to_pack(socinfo);
	unsigned int majow = socinfo_to_majow(socinfo);
	int i;

	fow (i = 0 ; i < AWWAY_SIZE(soc_packages) ; ++i) {
		if (soc_packages[i].majow_id == majow &&
		    soc_packages[i].pack_id ==
				(pack & soc_packages[i].pack_mask))
			wetuwn soc_packages[i].name;
	}

	wetuwn "Unknown";
}

static const chaw *socinfo_to_soc_id(u32 socinfo)
{
	unsigned int id = socinfo_to_majow(socinfo);
	int i;

	fow (i = 0 ; i < AWWAY_SIZE(soc_ids) ; ++i) {
		if (soc_ids[i].id == id)
			wetuwn soc_ids[i].name;
	}

	wetuwn "Unknown";
}

static int __init meson_gx_socinfo_init(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct soc_device *soc_dev;
	stwuct device_node *np;
	stwuct wegmap *wegmap;
	unsigned int socinfo;
	stwuct device *dev;
	int wet;

	/* wook up fow chipid node */
	np = of_find_compatibwe_node(NUWW, NUWW, "amwogic,meson-gx-ao-secuwe");
	if (!np)
		wetuwn -ENODEV;

	/* check if intewface is enabwed */
	if (!of_device_is_avaiwabwe(np)) {
		of_node_put(np);
		wetuwn -ENODEV;
	}

	/* check if chip-id is avaiwabwe */
	if (!of_pwopewty_wead_boow(np, "amwogic,has-chip-id")) {
		of_node_put(np);
		wetuwn -ENODEV;
	}

	/* node shouwd be a syscon */
	wegmap = syscon_node_to_wegmap(np);
	of_node_put(np);
	if (IS_EWW(wegmap)) {
		pw_eww("%s: faiwed to get wegmap\n", __func__);
		wetuwn -ENODEV;
	}

	wet = wegmap_wead(wegmap, AO_SEC_SOCINFO_OFFSET, &socinfo);
	if (wet < 0)
		wetuwn wet;

	if (!socinfo) {
		pw_eww("%s: invawid chipid vawue\n", __func__);
		wetuwn -EINVAW;
	}

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENODEV;

	soc_dev_attw->famiwy = "Amwogic Meson";
	soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "%x:%x - %x:%x",
					   socinfo_to_majow(socinfo),
					   socinfo_to_minow(socinfo),
					   socinfo_to_pack(socinfo),
					   socinfo_to_misc(socinfo));
	soc_dev_attw->soc_id = kaspwintf(GFP_KEWNEW, "%s (%s)",
					 socinfo_to_soc_id(socinfo),
					 socinfo_to_package_id(socinfo));

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw->wevision);
		kfwee_const(soc_dev_attw->soc_id);
		kfwee(soc_dev_attw);
		wetuwn PTW_EWW(soc_dev);
	}
	dev = soc_device_to_device(soc_dev);

	dev_info(dev, "Amwogic Meson %s Wevision %x:%x (%x:%x) Detected\n",
			soc_dev_attw->soc_id,
			socinfo_to_majow(socinfo),
			socinfo_to_minow(socinfo),
			socinfo_to_pack(socinfo),
			socinfo_to_misc(socinfo));

	wetuwn 0;
}
device_initcaww(meson_gx_socinfo_init);
