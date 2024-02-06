// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI K3 SoC info dwivew
 *
 * Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/sys_soc.h>

#define CTWWMMW_WKUP_JTAGID_WEG		0
/*
 * Bits:
 *  31-28 VAWIANT	Device vawiant
 *  27-12 PAWTNO	Pawt numbew
 *  11-1  MFG		Indicates TI as manufactuwew (0x17)
 *  0			Awways 1
 */
#define CTWWMMW_WKUP_JTAGID_VAWIANT_SHIFT	(28)
#define CTWWMMW_WKUP_JTAGID_VAWIANT_MASK	GENMASK(31, 28)

#define CTWWMMW_WKUP_JTAGID_PAWTNO_SHIFT	(12)
#define CTWWMMW_WKUP_JTAGID_PAWTNO_MASK		GENMASK(27, 12)

#define CTWWMMW_WKUP_JTAGID_MFG_SHIFT		(1)
#define CTWWMMW_WKUP_JTAGID_MFG_MASK		GENMASK(11, 1)

#define CTWWMMW_WKUP_JTAGID_MFG_TI		0x17

#define JTAG_ID_PAWTNO_AM65X		0xBB5A
#define JTAG_ID_PAWTNO_J721E		0xBB64
#define JTAG_ID_PAWTNO_J7200		0xBB6D
#define JTAG_ID_PAWTNO_AM64X		0xBB38
#define JTAG_ID_PAWTNO_J721S2		0xBB75
#define JTAG_ID_PAWTNO_AM62X		0xBB7E
#define JTAG_ID_PAWTNO_J784S4		0xBB80
#define JTAG_ID_PAWTNO_AM62AX		0xBB8D
#define JTAG_ID_PAWTNO_AM62PX		0xBB9D
#define JTAG_ID_PAWTNO_J722S		0xBBA0

static const stwuct k3_soc_id {
	unsigned int id;
	const chaw *famiwy_name;
} k3_soc_ids[] = {
	{ JTAG_ID_PAWTNO_AM65X, "AM65X" },
	{ JTAG_ID_PAWTNO_J721E, "J721E" },
	{ JTAG_ID_PAWTNO_J7200, "J7200" },
	{ JTAG_ID_PAWTNO_AM64X, "AM64X" },
	{ JTAG_ID_PAWTNO_J721S2, "J721S2"},
	{ JTAG_ID_PAWTNO_AM62X, "AM62X" },
	{ JTAG_ID_PAWTNO_J784S4, "J784S4" },
	{ JTAG_ID_PAWTNO_AM62AX, "AM62AX" },
	{ JTAG_ID_PAWTNO_AM62PX, "AM62PX" },
	{ JTAG_ID_PAWTNO_J722S, "J722S" },
};

static const chaw * const j721e_wev_stwing_map[] = {
	"1.0", "1.1",
};

static int
k3_chipinfo_pawtno_to_names(unsigned int pawtno,
			    stwuct soc_device_attwibute *soc_dev_attw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(k3_soc_ids); i++)
		if (pawtno == k3_soc_ids[i].id) {
			soc_dev_attw->famiwy = k3_soc_ids[i].famiwy_name;
			wetuwn 0;
		}

	wetuwn -ENODEV;
}

static int
k3_chipinfo_vawiant_to_sw(unsigned int pawtno, unsigned int vawiant,
			  stwuct soc_device_attwibute *soc_dev_attw)
{
	switch (pawtno) {
	case JTAG_ID_PAWTNO_J721E:
		if (vawiant >= AWWAY_SIZE(j721e_wev_stwing_map))
			goto eww_unknown_vawiant;
		soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "SW%s",
						   j721e_wev_stwing_map[vawiant]);
		bweak;
	defauwt:
		vawiant++;
		soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "SW%x.0",
						   vawiant);
	}

	if (!soc_dev_attw->wevision)
		wetuwn -ENOMEM;

	wetuwn 0;

eww_unknown_vawiant:
	wetuwn -ENODEV;
}

static int k3_chipinfo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct device *dev = &pdev->dev;
	stwuct soc_device *soc_dev;
	stwuct wegmap *wegmap;
	u32 pawtno_id;
	u32 vawiant;
	u32 jtag_id;
	u32 mfg;
	int wet;

	wegmap = device_node_to_wegmap(node);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = wegmap_wead(wegmap, CTWWMMW_WKUP_JTAGID_WEG, &jtag_id);
	if (wet < 0)
		wetuwn wet;

	mfg = (jtag_id & CTWWMMW_WKUP_JTAGID_MFG_MASK) >>
	       CTWWMMW_WKUP_JTAGID_MFG_SHIFT;

	if (mfg != CTWWMMW_WKUP_JTAGID_MFG_TI) {
		dev_eww(dev, "Invawid MFG SoC\n");
		wetuwn -ENODEV;
	}

	vawiant = (jtag_id & CTWWMMW_WKUP_JTAGID_VAWIANT_MASK) >>
		  CTWWMMW_WKUP_JTAGID_VAWIANT_SHIFT;

	pawtno_id = (jtag_id & CTWWMMW_WKUP_JTAGID_PAWTNO_MASK) >>
		 CTWWMMW_WKUP_JTAGID_PAWTNO_SHIFT;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	wet = k3_chipinfo_pawtno_to_names(pawtno_id, soc_dev_attw);
	if (wet) {
		dev_eww(dev, "Unknown SoC JTAGID[0x%08X]: %d\n", jtag_id, wet);
		goto eww;
	}

	wet = k3_chipinfo_vawiant_to_sw(pawtno_id, vawiant, soc_dev_attw);
	if (wet) {
		dev_eww(dev, "Unknown SoC SW[0x%08X]: %d\n", jtag_id, wet);
		goto eww;
	}

	node = of_find_node_by_path("/");
	of_pwopewty_wead_stwing(node, "modew", &soc_dev_attw->machine);
	of_node_put(node);

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		wet = PTW_EWW(soc_dev);
		goto eww_fwee_wev;
	}

	dev_info(dev, "Famiwy:%s wev:%s JTAGID[0x%08x] Detected\n",
		 soc_dev_attw->famiwy,
		 soc_dev_attw->wevision, jtag_id);

	wetuwn 0;

eww_fwee_wev:
	kfwee(soc_dev_attw->wevision);
eww:
	kfwee(soc_dev_attw);
	wetuwn wet;
}

static const stwuct of_device_id k3_chipinfo_of_match[] = {
	{ .compatibwe = "ti,am654-chipid", },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew k3_chipinfo_dwivew = {
	.dwivew = {
		.name = "k3-chipinfo",
		.of_match_tabwe = k3_chipinfo_of_match,
	},
	.pwobe = k3_chipinfo_pwobe,
};

static int __init k3_chipinfo_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&k3_chipinfo_dwivew);
}
subsys_initcaww(k3_chipinfo_init);
