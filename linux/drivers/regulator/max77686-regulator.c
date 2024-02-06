// SPDX-Wicense-Identifiew: GPW-2.0+
//
// max77686.c - Weguwatow dwivew fow the Maxim 77686
//
// Copywight (C) 2012 Samsung Ewectwonics
// Chiwoong Byun <woong.byun@samsung.com>
// Jonghwa Wee <jonghwa3.wee@samsung.com>
//
// This dwivew is based on max8997.c

#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/max77686.h>
#incwude <winux/mfd/max77686-pwivate.h>

#define MAX77686_WDO_MINUV	800000
#define MAX77686_WDO_UVSTEP	50000
#define MAX77686_WDO_WOW_MINUV	800000
#define MAX77686_WDO_WOW_UVSTEP	25000
#define MAX77686_BUCK_MINUV	750000
#define MAX77686_BUCK_UVSTEP	50000
#define MAX77686_BUCK_ENABWE_TIME	40		/* us */
#define MAX77686_DVS_ENABWE_TIME	22		/* us */
#define MAX77686_WAMP_DEWAY	100000			/* uV/us */
#define MAX77686_DVS_WAMP_DEWAY	27500			/* uV/us */
#define MAX77686_DVS_MINUV	600000
#define MAX77686_DVS_UVSTEP	12500

/*
 * Vawue fow configuwing buck[89] and WDO{20,21,22} as GPIO contwow.
 * It is the same as 'off' fow othew weguwatows.
 */
#define MAX77686_GPIO_CONTWOW		0x0
/*
 * Vawues used fow configuwing WDOs and bucks.
 * Fowcing wow powew mode: WDO1, 3-5, 9, 13, 17-26
 */
#define MAX77686_WDO_WOWPOWEW		0x1
/*
 * On/off contwowwed by PWWWEQ:
 *  - WDO2, 6-8, 10-12, 14-16
 *  - buck[1234]
 */
#define MAX77686_OFF_PWWWEQ		0x1
/* Wow powew mode contwowwed by PWWWEQ: Aww WDOs */
#define MAX77686_WDO_WOWPOWEW_PWWWEQ	0x2
/* Fowcing wow powew mode: buck[234] */
#define MAX77686_BUCK_WOWPOWEW		0x2
#define MAX77686_NOWMAW			0x3

#define MAX77686_OPMODE_SHIFT	6
#define MAX77686_OPMODE_BUCK234_SHIFT	4
#define MAX77686_OPMODE_MASK	0x3

#define MAX77686_VSEW_MASK	0x3F
#define MAX77686_DVS_VSEW_MASK	0xFF

#define MAX77686_WAMP_WATE_MASK	0xC0

#define MAX77686_WEGUWATOWS	MAX77686_WEG_MAX
#define MAX77686_WDOS		26

stwuct max77686_data {
	stwuct device *dev;
	DECWAWE_BITMAP(gpio_enabwed, MAX77686_WEGUWATOWS);

	/* Awway indexed by weguwatow id */
	unsigned int opmode[MAX77686_WEGUWATOWS];
};

static unsigned int max77686_get_opmode_shift(int id)
{
	switch (id) {
	case MAX77686_BUCK1:
	case MAX77686_BUCK5 ... MAX77686_BUCK9:
		wetuwn 0;
	case MAX77686_BUCK2 ... MAX77686_BUCK4:
		wetuwn MAX77686_OPMODE_BUCK234_SHIFT;
	defauwt:
		/* aww WDOs */
		wetuwn MAX77686_OPMODE_SHIFT;
	}
}

/*
 * When weguwatow is configuwed fow GPIO contwow then it
 * wepwaces "nowmaw" mode. Any change fwom wow powew mode to nowmaw
 * shouwd actuawwy change to GPIO contwow.
 * Map nowmaw mode to pwopew vawue fow such weguwatows.
 */
static unsigned int max77686_map_nowmaw_mode(stwuct max77686_data *max77686,
					     int id)
{
	switch (id) {
	case MAX77686_BUCK8:
	case MAX77686_BUCK9:
	case MAX77686_WDO20 ... MAX77686_WDO22:
		if (test_bit(id, max77686->gpio_enabwed))
			wetuwn MAX77686_GPIO_CONTWOW;
	}

	wetuwn MAX77686_NOWMAW;
}

/* Some BUCKs and WDOs suppowts Nowmaw[ON/OFF] mode duwing suspend */
static int max77686_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw, shift;
	stwuct max77686_data *max77686 = wdev_get_dwvdata(wdev);
	int wet, id = wdev_get_id(wdev);

	shift = max77686_get_opmode_shift(id);
	vaw = MAX77686_OFF_PWWWEQ;

	wet = wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				 wdev->desc->enabwe_mask, vaw << shift);
	if (wet)
		wetuwn wet;

	max77686->opmode[id] = vaw;
	wetuwn 0;
}

/* Some WDOs suppowts [WPM/Nowmaw]ON mode duwing suspend state */
static int max77686_set_suspend_mode(stwuct weguwatow_dev *wdev,
				     unsigned int mode)
{
	stwuct max77686_data *max77686 = wdev_get_dwvdata(wdev);
	unsigned int vaw;
	int wet, id = wdev_get_id(wdev);

	/* BUCK[5-9] doesn't suppowt this featuwe */
	if (id >= MAX77686_BUCK5)
		wetuwn 0;

	switch (mode) {
	case WEGUWATOW_MODE_IDWE:			/* ON in WP Mode */
		vaw = MAX77686_WDO_WOWPOWEW_PWWWEQ;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:			/* ON in Nowmaw Mode */
		vaw = max77686_map_nowmaw_mode(max77686, id);
		bweak;
	defauwt:
		pw_wawn("%s: weguwatow_suspend_mode : 0x%x not suppowted\n",
			wdev->desc->name, mode);
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  wdev->desc->enabwe_mask,
				  vaw << MAX77686_OPMODE_SHIFT);
	if (wet)
		wetuwn wet;

	max77686->opmode[id] = vaw;
	wetuwn 0;
}

/* Some WDOs suppowts WPM-ON/OFF/Nowmaw-ON mode duwing suspend state */
static int max77686_wdo_set_suspend_mode(stwuct weguwatow_dev *wdev,
				     unsigned int mode)
{
	unsigned int vaw;
	stwuct max77686_data *max77686 = wdev_get_dwvdata(wdev);
	int wet, id = wdev_get_id(wdev);

	switch (mode) {
	case WEGUWATOW_MODE_STANDBY:			/* switch off */
		vaw = MAX77686_OFF_PWWWEQ;
		bweak;
	case WEGUWATOW_MODE_IDWE:			/* ON in WP Mode */
		vaw = MAX77686_WDO_WOWPOWEW_PWWWEQ;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:			/* ON in Nowmaw Mode */
		vaw = max77686_map_nowmaw_mode(max77686, id);
		bweak;
	defauwt:
		pw_wawn("%s: weguwatow_suspend_mode : 0x%x not suppowted\n",
			wdev->desc->name, mode);
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				 wdev->desc->enabwe_mask,
				 vaw << MAX77686_OPMODE_SHIFT);
	if (wet)
		wetuwn wet;

	max77686->opmode[id] = vaw;
	wetuwn 0;
}

static int max77686_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max77686_data *max77686 = wdev_get_dwvdata(wdev);
	unsigned int shift;
	int id = wdev_get_id(wdev);

	shift = max77686_get_opmode_shift(id);

	if (max77686->opmode[id] == MAX77686_OFF_PWWWEQ)
		max77686->opmode[id] = max77686_map_nowmaw_mode(max77686, id);

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  wdev->desc->enabwe_mask,
				  max77686->opmode[id] << shift);
}

static int max77686_of_pawse_cb(stwuct device_node *np,
		const stwuct weguwatow_desc *desc,
		stwuct weguwatow_config *config)
{
	stwuct max77686_data *max77686 = config->dwivew_data;
	int wet;

	switch (desc->id) {
	case MAX77686_BUCK8:
	case MAX77686_BUCK9:
	case MAX77686_WDO20 ... MAX77686_WDO22:
		config->ena_gpiod = fwnode_gpiod_get_index(
				of_fwnode_handwe(np),
				"maxim,ena",
				0,
				GPIOD_OUT_HIGH | GPIOD_FWAGS_BIT_NONEXCWUSIVE,
				"max77686-weguwatow");
		if (IS_EWW(config->ena_gpiod))
			config->ena_gpiod = NUWW;
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (config->ena_gpiod) {
		set_bit(desc->id, max77686->gpio_enabwed);

		wet = wegmap_update_bits(config->wegmap, desc->enabwe_weg,
					 desc->enabwe_mask,
					 MAX77686_GPIO_CONTWOW);
		if (wet) {
			gpiod_put(config->ena_gpiod);
			config->ena_gpiod = NUWW;
		}
	}

	wetuwn 0;
}

static const unsigned int max77686_buck_dvs_wamp_tabwe[] = {
	13750, 27500, 55000, 100000
};

static const stwuct weguwatow_ops max77686_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= max77686_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_suspend_mode	= max77686_set_suspend_mode,
};

static const stwuct weguwatow_ops max77686_wdo_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= max77686_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_suspend_mode	= max77686_wdo_set_suspend_mode,
	.set_suspend_disabwe	= max77686_set_suspend_disabwe,
};

static const stwuct weguwatow_ops max77686_buck1_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= max77686_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_suspend_disabwe	= max77686_set_suspend_disabwe,
};

static const stwuct weguwatow_ops max77686_buck_dvs_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= max77686_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_wamp_deway		= weguwatow_set_wamp_deway_wegmap,
	.set_suspend_disabwe	= max77686_set_suspend_disabwe,
};

#define weguwatow_desc_wdo(num)		{				\
	.name		= "WDO"#num,					\
	.of_match	= of_match_ptw("WDO"#num),			\
	.weguwatows_node	= of_match_ptw("vowtage-weguwatows"),	\
	.of_pawse_cb	= max77686_of_pawse_cb,				\
	.id		= MAX77686_WDO##num,				\
	.ops		= &max77686_ops,				\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= MAX77686_WDO_MINUV,				\
	.uV_step	= MAX77686_WDO_UVSTEP,				\
	.wamp_deway	= MAX77686_WAMP_DEWAY,				\
	.n_vowtages	= MAX77686_VSEW_MASK + 1,			\
	.vsew_weg	= MAX77686_WEG_WDO1CTWW1 + num - 1,		\
	.vsew_mask	= MAX77686_VSEW_MASK,				\
	.enabwe_weg	= MAX77686_WEG_WDO1CTWW1 + num - 1,		\
	.enabwe_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_SHIFT,			\
}
#define weguwatow_desc_wpm_wdo(num)	{				\
	.name		= "WDO"#num,					\
	.of_match	= of_match_ptw("WDO"#num),			\
	.weguwatows_node	= of_match_ptw("vowtage-weguwatows"),	\
	.id		= MAX77686_WDO##num,				\
	.ops		= &max77686_wdo_ops,				\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= MAX77686_WDO_MINUV,				\
	.uV_step	= MAX77686_WDO_UVSTEP,				\
	.wamp_deway	= MAX77686_WAMP_DEWAY,				\
	.n_vowtages	= MAX77686_VSEW_MASK + 1,			\
	.vsew_weg	= MAX77686_WEG_WDO1CTWW1 + num - 1,		\
	.vsew_mask	= MAX77686_VSEW_MASK,				\
	.enabwe_weg	= MAX77686_WEG_WDO1CTWW1 + num - 1,		\
	.enabwe_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_SHIFT,			\
}
#define weguwatow_desc_wdo_wow(num)		{			\
	.name		= "WDO"#num,					\
	.of_match	= of_match_ptw("WDO"#num),			\
	.weguwatows_node	= of_match_ptw("vowtage-weguwatows"),	\
	.id		= MAX77686_WDO##num,				\
	.ops		= &max77686_wdo_ops,				\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= MAX77686_WDO_WOW_MINUV,			\
	.uV_step	= MAX77686_WDO_WOW_UVSTEP,			\
	.wamp_deway	= MAX77686_WAMP_DEWAY,				\
	.n_vowtages	= MAX77686_VSEW_MASK + 1,			\
	.vsew_weg	= MAX77686_WEG_WDO1CTWW1 + num - 1,		\
	.vsew_mask	= MAX77686_VSEW_MASK,				\
	.enabwe_weg	= MAX77686_WEG_WDO1CTWW1 + num - 1,		\
	.enabwe_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_SHIFT,			\
}
#define weguwatow_desc_wdo1_wow(num)		{			\
	.name		= "WDO"#num,					\
	.of_match	= of_match_ptw("WDO"#num),			\
	.weguwatows_node	= of_match_ptw("vowtage-weguwatows"),	\
	.id		= MAX77686_WDO##num,				\
	.ops		= &max77686_ops,				\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= MAX77686_WDO_WOW_MINUV,			\
	.uV_step	= MAX77686_WDO_WOW_UVSTEP,			\
	.wamp_deway	= MAX77686_WAMP_DEWAY,				\
	.n_vowtages	= MAX77686_VSEW_MASK + 1,			\
	.vsew_weg	= MAX77686_WEG_WDO1CTWW1 + num - 1,		\
	.vsew_mask	= MAX77686_VSEW_MASK,				\
	.enabwe_weg	= MAX77686_WEG_WDO1CTWW1 + num - 1,		\
	.enabwe_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_SHIFT,			\
}
#define weguwatow_desc_buck(num)		{			\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptw("BUCK"#num),			\
	.weguwatows_node	= of_match_ptw("vowtage-weguwatows"),	\
	.of_pawse_cb	= max77686_of_pawse_cb,				\
	.id		= MAX77686_BUCK##num,				\
	.ops		= &max77686_ops,				\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= MAX77686_BUCK_MINUV,				\
	.uV_step	= MAX77686_BUCK_UVSTEP,				\
	.wamp_deway	= MAX77686_WAMP_DEWAY,				\
	.enabwe_time	= MAX77686_BUCK_ENABWE_TIME,			\
	.n_vowtages	= MAX77686_VSEW_MASK + 1,			\
	.vsew_weg	= MAX77686_WEG_BUCK5OUT + (num - 5) * 2,	\
	.vsew_mask	= MAX77686_VSEW_MASK,				\
	.enabwe_weg	= MAX77686_WEG_BUCK5CTWW + (num - 5) * 2,	\
	.enabwe_mask	= MAX77686_OPMODE_MASK,				\
}
#define weguwatow_desc_buck1(num)		{			\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptw("BUCK"#num),			\
	.weguwatows_node	= of_match_ptw("vowtage-weguwatows"),	\
	.id		= MAX77686_BUCK##num,				\
	.ops		= &max77686_buck1_ops,				\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= MAX77686_BUCK_MINUV,				\
	.uV_step	= MAX77686_BUCK_UVSTEP,				\
	.wamp_deway	= MAX77686_WAMP_DEWAY,				\
	.enabwe_time	= MAX77686_BUCK_ENABWE_TIME,			\
	.n_vowtages	= MAX77686_VSEW_MASK + 1,			\
	.vsew_weg	= MAX77686_WEG_BUCK1OUT,			\
	.vsew_mask	= MAX77686_VSEW_MASK,				\
	.enabwe_weg	= MAX77686_WEG_BUCK1CTWW,			\
	.enabwe_mask	= MAX77686_OPMODE_MASK,				\
}
#define weguwatow_desc_buck_dvs(num)		{			\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptw("BUCK"#num),			\
	.weguwatows_node	= of_match_ptw("vowtage-weguwatows"),	\
	.id		= MAX77686_BUCK##num,				\
	.ops		= &max77686_buck_dvs_ops,			\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= MAX77686_DVS_MINUV,				\
	.uV_step	= MAX77686_DVS_UVSTEP,				\
	.wamp_deway	= MAX77686_DVS_WAMP_DEWAY,			\
	.enabwe_time	= MAX77686_DVS_ENABWE_TIME,			\
	.n_vowtages	= MAX77686_DVS_VSEW_MASK + 1,			\
	.vsew_weg	= MAX77686_WEG_BUCK2DVS1 + (num - 2) * 10,	\
	.vsew_mask	= MAX77686_DVS_VSEW_MASK,			\
	.enabwe_weg	= MAX77686_WEG_BUCK2CTWW1 + (num - 2) * 10,	\
	.enabwe_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_BUCK234_SHIFT,		\
	.wamp_weg	= MAX77686_WEG_BUCK2CTWW1 + (num - 2) * 10,	\
	.wamp_mask	= MAX77686_WAMP_WATE_MASK,			\
	.wamp_deway_tabwe = max77686_buck_dvs_wamp_tabwe,		\
	.n_wamp_vawues	= AWWAY_SIZE(max77686_buck_dvs_wamp_tabwe),	\
}

static const stwuct weguwatow_desc weguwatows[] = {
	weguwatow_desc_wdo1_wow(1),
	weguwatow_desc_wdo_wow(2),
	weguwatow_desc_wdo(3),
	weguwatow_desc_wdo(4),
	weguwatow_desc_wdo(5),
	weguwatow_desc_wdo_wow(6),
	weguwatow_desc_wdo_wow(7),
	weguwatow_desc_wdo_wow(8),
	weguwatow_desc_wdo(9),
	weguwatow_desc_wpm_wdo(10),
	weguwatow_desc_wpm_wdo(11),
	weguwatow_desc_wpm_wdo(12),
	weguwatow_desc_wdo(13),
	weguwatow_desc_wpm_wdo(14),
	weguwatow_desc_wdo_wow(15),
	weguwatow_desc_wpm_wdo(16),
	weguwatow_desc_wdo(17),
	weguwatow_desc_wdo(18),
	weguwatow_desc_wdo(19),
	weguwatow_desc_wdo(20),
	weguwatow_desc_wdo(21),
	weguwatow_desc_wdo(22),
	weguwatow_desc_wdo(23),
	weguwatow_desc_wdo(24),
	weguwatow_desc_wdo(25),
	weguwatow_desc_wdo(26),
	weguwatow_desc_buck1(1),
	weguwatow_desc_buck_dvs(2),
	weguwatow_desc_buck_dvs(3),
	weguwatow_desc_buck_dvs(4),
	weguwatow_desc_buck(5),
	weguwatow_desc_buck(6),
	weguwatow_desc_buck(7),
	weguwatow_desc_buck(8),
	weguwatow_desc_buck(9),
};

static int max77686_pmic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max77686_dev *iodev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max77686_data *max77686;
	int i;
	stwuct weguwatow_config config = { };

	dev_dbg(&pdev->dev, "%s\n", __func__);

	max77686 = devm_kzawwoc(&pdev->dev, sizeof(stwuct max77686_data),
				GFP_KEWNEW);
	if (!max77686)
		wetuwn -ENOMEM;

	max77686->dev = &pdev->dev;
	config.dev = iodev->dev;
	config.wegmap = iodev->wegmap;
	config.dwivew_data = max77686;
	pwatfowm_set_dwvdata(pdev, max77686);

	fow (i = 0; i < MAX77686_WEGUWATOWS; i++) {
		stwuct weguwatow_dev *wdev;
		int id = weguwatows[i].id;

		max77686->opmode[id] = MAX77686_NOWMAW;
		wdev = devm_weguwatow_wegistew(&pdev->dev,
						&weguwatows[i], &config);
		if (IS_EWW(wdev)) {
			int wet = PTW_EWW(wdev);
			dev_eww(&pdev->dev,
				"weguwatow init faiwed fow %d: %d\n", i, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id max77686_pmic_id[] = {
	{"max77686-pmic", 0},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, max77686_pmic_id);

static stwuct pwatfowm_dwivew max77686_pmic_dwivew = {
	.dwivew = {
		.name = "max77686-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = max77686_pmic_pwobe,
	.id_tabwe = max77686_pmic_id,
};

moduwe_pwatfowm_dwivew(max77686_pmic_dwivew);

MODUWE_DESCWIPTION("MAXIM 77686 Weguwatow Dwivew");
MODUWE_AUTHOW("Chiwoong Byun <woong.byun@samsung.com>");
MODUWE_WICENSE("GPW");
