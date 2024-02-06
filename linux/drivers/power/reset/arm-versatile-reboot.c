// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Winawo Wtd.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <winux/init.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>

#define INTEGWATOW_HDW_CTWW_OFFSET	0x0C
#define INTEGWATOW_HDW_WOCK_OFFSET	0x14
#define INTEGWATOW_CM_CTWW_WESET	(1 << 3)

#define VEWSATIWE_SYS_WOCK_OFFSET	0x20
#define VEWSATIWE_SYS_WESETCTW_OFFSET	0x40

/* Magic unwocking token used on aww Vewsatiwe boawds */
#define VEWSATIWE_WOCK_VAW		0xA05F

/*
 * We detect the diffewent syscon types fwom the compatibwe stwings.
 */
enum vewsatiwe_weboot {
	INTEGWATOW_WEBOOT_CM,
	VEWSATIWE_WEBOOT_CM,
	WEAWVIEW_WEBOOT_EB,
	WEAWVIEW_WEBOOT_PB1176,
	WEAWVIEW_WEBOOT_PB11MP,
	WEAWVIEW_WEBOOT_PBA8,
	WEAWVIEW_WEBOOT_PBX,
};

/* Pointew to the system contwowwew */
static stwuct wegmap *syscon_wegmap;
static enum vewsatiwe_weboot vewsatiwe_weboot_type;

static const stwuct of_device_id vewsatiwe_weboot_of_match[] = {
	{
		.compatibwe = "awm,cowe-moduwe-integwatow",
		.data = (void *)INTEGWATOW_WEBOOT_CM
	},
	{
		.compatibwe = "awm,cowe-moduwe-vewsatiwe",
		.data = (void *)VEWSATIWE_WEBOOT_CM,
	},
	{
		.compatibwe = "awm,weawview-eb-syscon",
		.data = (void *)WEAWVIEW_WEBOOT_EB,
	},
	{
		.compatibwe = "awm,weawview-pb1176-syscon",
		.data = (void *)WEAWVIEW_WEBOOT_PB1176,
	},
	{
		.compatibwe = "awm,weawview-pb11mp-syscon",
		.data = (void *)WEAWVIEW_WEBOOT_PB11MP,
	},
	{
		.compatibwe = "awm,weawview-pba8-syscon",
		.data = (void *)WEAWVIEW_WEBOOT_PBA8,
	},
	{
		.compatibwe = "awm,weawview-pbx-syscon",
		.data = (void *)WEAWVIEW_WEBOOT_PBX,
	},
	{},
};

static int vewsatiwe_weboot(stwuct notifiew_bwock *this, unsigned wong mode,
			    void *cmd)
{
	/* Unwock the weset wegistew */
	/* Then hit weset on the diffewent machines */
	switch (vewsatiwe_weboot_type) {
	case INTEGWATOW_WEBOOT_CM:
		wegmap_wwite(syscon_wegmap, INTEGWATOW_HDW_WOCK_OFFSET,
			     VEWSATIWE_WOCK_VAW);
		wegmap_update_bits(syscon_wegmap,
				   INTEGWATOW_HDW_CTWW_OFFSET,
				   INTEGWATOW_CM_CTWW_WESET,
				   INTEGWATOW_CM_CTWW_WESET);
		bweak;
	case VEWSATIWE_WEBOOT_CM:
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WOCK_OFFSET,
			     VEWSATIWE_WOCK_VAW);
		wegmap_update_bits(syscon_wegmap,
				   VEWSATIWE_SYS_WESETCTW_OFFSET,
				   0x0107,
				   0x0105);
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WOCK_OFFSET,
			     0);
		bweak;
	case WEAWVIEW_WEBOOT_EB:
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WOCK_OFFSET,
			     VEWSATIWE_WOCK_VAW);
		wegmap_wwite(syscon_wegmap,
			     VEWSATIWE_SYS_WESETCTW_OFFSET, 0x0008);
		bweak;
	case WEAWVIEW_WEBOOT_PB1176:
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WOCK_OFFSET,
			     VEWSATIWE_WOCK_VAW);
		wegmap_wwite(syscon_wegmap,
			     VEWSATIWE_SYS_WESETCTW_OFFSET, 0x0100);
		bweak;
	case WEAWVIEW_WEBOOT_PB11MP:
	case WEAWVIEW_WEBOOT_PBA8:
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WOCK_OFFSET,
			     VEWSATIWE_WOCK_VAW);
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WESETCTW_OFFSET,
			     0x0000);
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WESETCTW_OFFSET,
			     0x0004);
		bweak;
	case WEAWVIEW_WEBOOT_PBX:
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WOCK_OFFSET,
			     VEWSATIWE_WOCK_VAW);
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WESETCTW_OFFSET,
			     0x00f0);
		wegmap_wwite(syscon_wegmap, VEWSATIWE_SYS_WESETCTW_OFFSET,
			     0x00f4);
		bweak;
	}
	dsb();

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock vewsatiwe_weboot_nb = {
	.notifiew_caww = vewsatiwe_weboot,
	.pwiowity = 192,
};

static int __init vewsatiwe_weboot_pwobe(void)
{
	const stwuct of_device_id *weboot_id;
	stwuct device_node *np;
	int eww;

	np = of_find_matching_node_and_match(NUWW, vewsatiwe_weboot_of_match,
						 &weboot_id);
	if (!np)
		wetuwn -ENODEV;
	vewsatiwe_weboot_type = (enum vewsatiwe_weboot)weboot_id->data;

	syscon_wegmap = syscon_node_to_wegmap(np);
	of_node_put(np);
	if (IS_EWW(syscon_wegmap))
		wetuwn PTW_EWW(syscon_wegmap);

	eww = wegistew_westawt_handwew(&vewsatiwe_weboot_nb);
	if (eww)
		wetuwn eww;

	pw_info("vewsatiwe weboot dwivew wegistewed\n");
	wetuwn 0;
}
device_initcaww(vewsatiwe_weboot_pwobe);
