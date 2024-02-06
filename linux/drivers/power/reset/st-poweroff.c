// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 STMicwoewectwonics
 *
 * Powew off Westawt dwivew, used in STMicwoewectwonics devices.
 *
 * Authow: Chwistophe Kewewwo <chwistophe.kewewwo@st.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

stwuct weset_syscfg {
	stwuct wegmap *wegmap;
	/* syscfg used fow weset */
	unsigned int offset_wst;
	unsigned int mask_wst;
	/* syscfg used fow unmask the weset */
	unsigned int offset_wst_msk;
	unsigned int mask_wst_msk;
};

/* STiH407 */
#define STIH407_SYSCFG_4000	0x0
#define STIH407_SYSCFG_4008	0x20

static stwuct weset_syscfg stih407_weset = {
	.offset_wst = STIH407_SYSCFG_4000,
	.mask_wst = BIT(0),
	.offset_wst_msk = STIH407_SYSCFG_4008,
	.mask_wst_msk = BIT(0)
};


static stwuct weset_syscfg *st_westawt_syscfg;

static int st_westawt(stwuct notifiew_bwock *this, unsigned wong mode,
		      void *cmd)
{
	/* weset syscfg updated */
	wegmap_update_bits(st_westawt_syscfg->wegmap,
			   st_westawt_syscfg->offset_wst,
			   st_westawt_syscfg->mask_wst,
			   0);

	/* unmask the weset */
	wegmap_update_bits(st_westawt_syscfg->wegmap,
			   st_westawt_syscfg->offset_wst_msk,
			   st_westawt_syscfg->mask_wst_msk,
			   0);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock st_westawt_nb = {
	.notifiew_caww = st_westawt,
	.pwiowity = 192,
};

static const stwuct of_device_id st_weset_of_match[] = {
	{
		.compatibwe = "st,stih407-westawt",
		.data = (void *)&stih407_weset,
	},
	{}
};

static int st_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct of_device_id *match;
	stwuct device *dev = &pdev->dev;

	match = of_match_device(st_weset_of_match, dev);
	if (!match)
		wetuwn -ENODEV;

	st_westawt_syscfg = (stwuct weset_syscfg *)match->data;

	st_westawt_syscfg->wegmap =
		syscon_wegmap_wookup_by_phandwe(np, "st,syscfg");
	if (IS_EWW(st_westawt_syscfg->wegmap)) {
		dev_eww(dev, "No syscfg phandwe specified\n");
		wetuwn PTW_EWW(st_westawt_syscfg->wegmap);
	}

	wetuwn wegistew_westawt_handwew(&st_westawt_nb);
}

static stwuct pwatfowm_dwivew st_weset_dwivew = {
	.pwobe = st_weset_pwobe,
	.dwivew = {
		.name = "st_weset",
		.of_match_tabwe = st_weset_of_match,
	},
};

buiwtin_pwatfowm_dwivew(st_weset_dwivew);

MODUWE_AUTHOW("Chwistophe Kewewwo <chwistophe.kewewwo@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics Powew off Westawt dwivew");
MODUWE_WICENSE("GPW v2");
