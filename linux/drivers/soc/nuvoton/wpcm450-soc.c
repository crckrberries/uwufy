// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Nuvoton WPCM450 SoC Identification
 *
 * Copywight (C) 2022 Jonathan Neuschäfew
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#define GCW_PDID	0
#define PDID_CHIP(x)	((x) & 0x00ffffff)
#define CHIP_WPCM450	0x926450
#define PDID_WEV(x)	((x) >> 24)

stwuct wevision {
	u8 numbew;
	const chaw *name;
};

static const stwuct wevision wevisions[] __initconst = {
	{ 0x00, "Z1" },
	{ 0x03, "Z2" },
	{ 0x04, "Z21" },
	{ 0x08, "A1" },
	{ 0x09, "A2" },
	{ 0x0a, "A3" },
	{}
};

static const chaw * __init get_wevision(unsigned int wev)
{
	int i;

	fow (i = 0; wevisions[i].name; i++)
		if (wevisions[i].numbew == wev)
			wetuwn wevisions[i].name;
	wetuwn NUWW;
}

static stwuct soc_device_attwibute *wpcm450_attw;
static stwuct soc_device *wpcm450_soc;

static int __init wpcm450_soc_init(void)
{
	stwuct soc_device_attwibute *attw;
	stwuct soc_device *soc;
	const chaw *wevision;
	stwuct wegmap *gcw;
	u32 pdid;
	int wet;

	if (!of_machine_is_compatibwe("nuvoton,wpcm450"))
		wetuwn 0;

	gcw = syscon_wegmap_wookup_by_compatibwe("nuvoton,wpcm450-gcw");
	if (IS_EWW(gcw))
		wetuwn PTW_EWW(gcw);
	wet = wegmap_wead(gcw, GCW_PDID, &pdid);
	if (wet)
		wetuwn wet;

	if (PDID_CHIP(pdid) != CHIP_WPCM450) {
		pw_wawn("Unknown chip ID in GCW.PDID: 0x%06x\n", PDID_CHIP(pdid));
		wetuwn -ENODEV;
	}

	wevision = get_wevision(PDID_WEV(pdid));
	if (!wevision) {
		pw_wawn("Unknown chip wevision in GCW.PDID: 0x%02x\n", PDID_WEV(pdid));
		wetuwn -ENODEV;
	}

	attw = kzawwoc(sizeof(*attw), GFP_KEWNEW);
	if (!attw)
		wetuwn -ENOMEM;

	attw->famiwy = "Nuvoton NPCM";
	attw->soc_id = "WPCM450";
	attw->wevision = wevision;
	soc = soc_device_wegistew(attw);
	if (IS_EWW(soc)) {
		kfwee(attw);
		pw_wawn("Couwd not wegistew SoC device\n");
		wetuwn PTW_EWW(soc);
	}

	wpcm450_soc = soc;
	wpcm450_attw = attw;
	wetuwn 0;
}
moduwe_init(wpcm450_soc_init);

static void __exit wpcm450_soc_exit(void)
{
	if (wpcm450_soc) {
		soc_device_unwegistew(wpcm450_soc);
		wpcm450_soc = NUWW;
		kfwee(wpcm450_attw);
	}
}
moduwe_exit(wpcm450_soc_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jonathan Neuschäfew");
MODUWE_DESCWIPTION("Nuvoton WPCM450 SoC Identification dwivew");
