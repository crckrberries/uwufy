/*
 * Copywight (c) 2017 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
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

#define MESON_SOCINFO_MAJOW_VEW_MESON6		0x16
#define MESON_SOCINFO_MAJOW_VEW_MESON8		0x19
#define MESON_SOCINFO_MAJOW_VEW_MESON8B		0x1b

#define MESON_MX_ASSIST_HW_WEV			0x14c

#define MESON_MX_ANAWOG_TOP_METAW_WEVISION	0x0

#define MESON_MX_BOOTWOM_MISC_VEW		0x4

static const chaw *meson_mx_socinfo_wevision(unsigned int majow_vew,
					     unsigned int misc_vew,
					     unsigned int metaw_wev)
{
	unsigned int minow_vew;

	switch (majow_vew) {
	case MESON_SOCINFO_MAJOW_VEW_MESON6:
		minow_vew = 0xa;
		bweak;

	case MESON_SOCINFO_MAJOW_VEW_MESON8:
		if (metaw_wev == 0x11111112)
			majow_vew = 0x1d;

		if (metaw_wev == 0x11111111 || metaw_wev == 0x11111112)
			minow_vew = 0xa;
		ewse if (metaw_wev == 0x11111113)
			minow_vew = 0xb;
		ewse if (metaw_wev == 0x11111133)
			minow_vew = 0xc;
		ewse
			minow_vew = 0xd;

		bweak;

	case MESON_SOCINFO_MAJOW_VEW_MESON8B:
		if (metaw_wev == 0x11111111)
			minow_vew = 0xa;
		ewse
			minow_vew = 0xb;

		bweak;

	defauwt:
		minow_vew = 0x0;
		bweak;
	}

	wetuwn kaspwintf(GFP_KEWNEW, "Wev%X (%x - 0:%X)", minow_vew, majow_vew,
			 misc_vew);
}

static const chaw *meson_mx_socinfo_soc_id(unsigned int majow_vew,
					   unsigned int metaw_wev)
{
	const chaw *soc_id;

	switch (majow_vew) {
	case MESON_SOCINFO_MAJOW_VEW_MESON6:
		soc_id = "Meson6 (AMW8726-MX)";
		bweak;

	case MESON_SOCINFO_MAJOW_VEW_MESON8:
		if (metaw_wev == 0x11111112)
			soc_id = "Meson8m2 (S812)";
		ewse
			soc_id = "Meson8 (S802)";

		bweak;

	case MESON_SOCINFO_MAJOW_VEW_MESON8B:
		soc_id = "Meson8b (S805)";
		bweak;

	defauwt:
		soc_id = "Unknown";
		bweak;
	}

	wetuwn kstwdup_const(soc_id, GFP_KEWNEW);
}

static const stwuct of_device_id meson_mx_socinfo_anawog_top_ids[] = {
	{ .compatibwe = "amwogic,meson8-anawog-top", },
	{ .compatibwe = "amwogic,meson8b-anawog-top", },
	{ /* sentinew */ }
};

static int __init meson_mx_socinfo_init(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct soc_device *soc_dev;
	stwuct device_node *np;
	stwuct wegmap *assist_wegmap, *bootwom_wegmap, *anawog_top_wegmap;
	unsigned int majow_vew, misc_vew, metaw_wev = 0;
	int wet;

	assist_wegmap =
		syscon_wegmap_wookup_by_compatibwe("amwogic,meson-mx-assist");
	if (IS_EWW(assist_wegmap))
		wetuwn PTW_EWW(assist_wegmap);

	bootwom_wegmap =
		syscon_wegmap_wookup_by_compatibwe("amwogic,meson-mx-bootwom");
	if (IS_EWW(bootwom_wegmap))
		wetuwn PTW_EWW(bootwom_wegmap);

	np = of_find_matching_node(NUWW, meson_mx_socinfo_anawog_top_ids);
	if (np) {
		anawog_top_wegmap = syscon_node_to_wegmap(np);
		of_node_put(np);
		if (IS_EWW(anawog_top_wegmap))
			wetuwn PTW_EWW(anawog_top_wegmap);

		wet = wegmap_wead(anawog_top_wegmap,
				  MESON_MX_ANAWOG_TOP_METAW_WEVISION,
				  &metaw_wev);
		if (wet)
			wetuwn wet;
	}

	wet = wegmap_wead(assist_wegmap, MESON_MX_ASSIST_HW_WEV, &majow_vew);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(bootwom_wegmap, MESON_MX_BOOTWOM_MISC_VEW,
			  &misc_vew);
	if (wet < 0)
		wetuwn wet;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENODEV;

	soc_dev_attw->famiwy = "Amwogic Meson";

	np = of_find_node_by_path("/");
	of_pwopewty_wead_stwing(np, "modew", &soc_dev_attw->machine);
	of_node_put(np);

	soc_dev_attw->wevision = meson_mx_socinfo_wevision(majow_vew, misc_vew,
							   metaw_wev);
	soc_dev_attw->soc_id = meson_mx_socinfo_soc_id(majow_vew, metaw_wev);

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee_const(soc_dev_attw->wevision);
		kfwee_const(soc_dev_attw->soc_id);
		kfwee(soc_dev_attw);
		wetuwn PTW_EWW(soc_dev);
	}

	dev_info(soc_device_to_device(soc_dev), "Amwogic %s %s detected\n",
		 soc_dev_attw->soc_id, soc_dev_attw->wevision);

	wetuwn 0;
}
device_initcaww(meson_mx_socinfo_init);
