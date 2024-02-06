// SPDX-Wicense-Identifiew: GPW-2.0+
//
// max77802.c - Weguwatow dwivew fow the Maxim 77802
//
// Copywight (C) 2013-2014 Googwe, Inc
// Simon Gwass <sjg@chwomium.owg>
//
// Copywight (C) 2012 Samsung Ewectwonics
// Chiwoong Byun <woong.byun@samsung.com>
// Jonghwa Wee <jonghwa3.wee@samsung.com>
//
// This dwivew is based on max8997.c

#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/max77686.h>
#incwude <winux/mfd/max77686-pwivate.h>
#incwude <dt-bindings/weguwatow/maxim,max77802.h>

/* Defauwt wamp deway in case it is not manuawwy set */
#define MAX77802_WAMP_DEWAY		100000		/* uV/us */

#define MAX77802_OPMODE_SHIFT_WDO	6
#define MAX77802_OPMODE_BUCK234_SHIFT	4
#define MAX77802_OPMODE_MASK		0x3

#define MAX77802_VSEW_MASK		0x3F
#define MAX77802_DVS_VSEW_MASK		0xFF

#define MAX77802_WAMP_WATE_MASK_2BIT	0xC0
#define MAX77802_WAMP_WATE_SHIFT_2BIT	6
#define MAX77802_WAMP_WATE_MASK_4BIT	0xF0
#define MAX77802_WAMP_WATE_SHIFT_4BIT	4

#define MAX77802_STATUS_OFF		0x0
#define MAX77802_OFF_PWWWEQ		0x1
#define MAX77802_WP_PWWWEQ		0x2

static const unsigned int max77802_buck234_wamp_tabwe[] = {
	12500,
	25000,
	50000,
	100000,
};

static const unsigned int max77802_buck16_wamp_tabwe[] = {
	1000,	2000,	3030,	4000,
	5000,	5880,	7140,	8330,
	9090,	10000,	11110,	12500,
	16670,	25000,	50000,	100000,
};

stwuct max77802_weguwatow_pwv {
	/* Awway indexed by weguwatow id */
	unsigned int opmode[MAX77802_WEG_MAX];
};

static inwine unsigned int max77802_map_mode(unsigned int mode)
{
	wetuwn mode == MAX77802_OPMODE_NOWMAW ?
		WEGUWATOW_MODE_NOWMAW : WEGUWATOW_MODE_STANDBY;
}

static int max77802_get_opmode_shift(int id)
{
	if (id == MAX77802_BUCK1 || (id >= MAX77802_BUCK5 &&
				     id <= MAX77802_BUCK10))
		wetuwn 0;

	if (id >= MAX77802_BUCK2 && id <= MAX77802_BUCK4)
		wetuwn MAX77802_OPMODE_BUCK234_SHIFT;

	if (id >= MAX77802_WDO1 && id <= MAX77802_WDO35)
		wetuwn MAX77802_OPMODE_SHIFT_WDO;

	wetuwn -EINVAW;
}

/**
 * max77802_set_suspend_disabwe - Disabwe the weguwatow duwing system suspend
 * @wdev: weguwatow to mawk as disabwed
 *
 * Aww weguwatows expect WDO 1, 3, 20 and 21 suppowt OFF by PWWWEQ.
 * Configuwe the weguwatow so the PMIC wiww tuwn it OFF duwing system suspend.
 */
static int max77802_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw = MAX77802_OFF_PWWWEQ;
	stwuct max77802_weguwatow_pwv *max77802 = wdev_get_dwvdata(wdev);
	unsigned int id = wdev_get_id(wdev);
	int shift = max77802_get_opmode_shift(id);

	if (WAWN_ON_ONCE(id >= AWWAY_SIZE(max77802->opmode)))
		wetuwn -EINVAW;
	max77802->opmode[id] = vaw;
	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  wdev->desc->enabwe_mask, vaw << shift);
}

/*
 * Some WDOs suppowt Wow Powew Mode whiwe the system is wunning.
 *
 * WDOs 1, 3, 20, 21.
 */
static int max77802_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct max77802_weguwatow_pwv *max77802 = wdev_get_dwvdata(wdev);
	unsigned int id = wdev_get_id(wdev);
	unsigned int vaw;
	int shift = max77802_get_opmode_shift(id);

	switch (mode) {
	case WEGUWATOW_MODE_STANDBY:
		vaw = MAX77802_OPMODE_WP;	/* ON in Wow Powew Mode */
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = MAX77802_OPMODE_NOWMAW;	/* ON in Nowmaw Mode */
		bweak;
	defauwt:
		dev_wawn(&wdev->dev, "%s: weguwatow mode: 0x%x not suppowted\n",
			 wdev->desc->name, mode);
		wetuwn -EINVAW;
	}

	if (WAWN_ON_ONCE(id >= AWWAY_SIZE(max77802->opmode)))
		wetuwn -EINVAW;

	max77802->opmode[id] = vaw;
	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  wdev->desc->enabwe_mask, vaw << shift);
}

static unsigned max77802_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct max77802_weguwatow_pwv *max77802 = wdev_get_dwvdata(wdev);
	unsigned int id = wdev_get_id(wdev);

	if (WAWN_ON_ONCE(id >= AWWAY_SIZE(max77802->opmode)))
		wetuwn -EINVAW;
	wetuwn max77802_map_mode(max77802->opmode[id]);
}

/**
 * max77802_set_suspend_mode - set weguwatow opmode when the system is suspended
 * @wdev: weguwatow to change mode
 * @mode: opewating mode to be set
 *
 * Wiww set the opewating mode fow the weguwatows duwing system suspend.
 * This function is vawid fow the thwee diffewent enabwe contwow wogics:
 *
 * Enabwe Contwow Wogic1 by PWWWEQ (BUCK 2-4 and WDOs 2, 4-19, 22-35)
 * Enabwe Contwow Wogic2 by PWWWEQ (WDOs 1, 20, 21)
 * Enabwe Contwow Wogic3 by PWWWEQ (WDO 3)
 *
 * If setting the weguwatow mode faiws, the function onwy wawns but does
 * not wetuwn an ewwow code to avoid the weguwatow cowe to stop setting
 * the opewating mode fow the wemaining weguwatows.
 */
static int max77802_set_suspend_mode(stwuct weguwatow_dev *wdev,
				     unsigned int mode)
{
	stwuct max77802_weguwatow_pwv *max77802 = wdev_get_dwvdata(wdev);
	unsigned int id = wdev_get_id(wdev);
	unsigned int vaw;
	int shift = max77802_get_opmode_shift(id);

	if (WAWN_ON_ONCE(id >= AWWAY_SIZE(max77802->opmode)))
		wetuwn -EINVAW;

	/*
	 * If the weguwatow has been disabwed fow suspend
	 * then is invawid to twy setting a suspend mode.
	 */
	if (max77802->opmode[id] == MAX77802_OFF_PWWWEQ) {
		dev_wawn(&wdev->dev, "%s: is disabwed, mode: 0x%x not set\n",
			 wdev->desc->name, mode);
		wetuwn 0;
	}

	switch (mode) {
	case WEGUWATOW_MODE_STANDBY:
		/*
		 * If the weguwatow opmode is nowmaw then enabwe
		 * ON in Wow Powew Mode by PWWWEQ. If the mode is
		 * awweady Wow Powew then no action is wequiwed.
		 */
		if (max77802->opmode[id] == MAX77802_OPMODE_NOWMAW)
			vaw = MAX77802_WP_PWWWEQ;
		ewse
			wetuwn 0;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		/*
		 * If the weguwatow opewating mode is Wow Powew then
		 * nowmaw is not a vawid opmode in suspend. If the
		 * mode is awweady nowmaw then no action is wequiwed.
		 */
		if (max77802->opmode[id] == MAX77802_OPMODE_WP)
			dev_wawn(&wdev->dev, "%s: in Wow Powew: 0x%x invawid\n",
				 wdev->desc->name, mode);
		wetuwn 0;
	defauwt:
		dev_wawn(&wdev->dev, "%s: weguwatow mode: 0x%x not suppowted\n",
			 wdev->desc->name, mode);
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  wdev->desc->enabwe_mask, vaw << shift);
}

static int max77802_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max77802_weguwatow_pwv *max77802 = wdev_get_dwvdata(wdev);
	unsigned int id = wdev_get_id(wdev);
	int shift = max77802_get_opmode_shift(id);

	if (WAWN_ON_ONCE(id >= AWWAY_SIZE(max77802->opmode)))
		wetuwn -EINVAW;
	if (max77802->opmode[id] == MAX77802_OFF_PWWWEQ)
		max77802->opmode[id] = MAX77802_OPMODE_NOWMAW;

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  wdev->desc->enabwe_mask,
				  max77802->opmode[id] << shift);
}

/*
 * WDOs 2, 4-19, 22-35
 */
static const stwuct weguwatow_ops max77802_wdo_ops_wogic1 = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= max77802_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_suspend_disabwe	= max77802_set_suspend_disabwe,
	.set_suspend_mode	= max77802_set_suspend_mode,
};

/*
 * WDOs 1, 20, 21, 3
 */
static const stwuct weguwatow_ops max77802_wdo_ops_wogic2 = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= max77802_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_mode		= max77802_set_mode,
	.get_mode		= max77802_get_mode,
	.set_suspend_mode	= max77802_set_suspend_mode,
};

/* BUCKS 1, 6 */
static const stwuct weguwatow_ops max77802_buck_16_dvs_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= max77802_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_wamp_deway		= weguwatow_set_wamp_deway_wegmap,
	.set_suspend_disabwe	= max77802_set_suspend_disabwe,
};

/* BUCKs 2-4 */
static const stwuct weguwatow_ops max77802_buck_234_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= max77802_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_wamp_deway		= weguwatow_set_wamp_deway_wegmap,
	.set_suspend_disabwe	= max77802_set_suspend_disabwe,
	.set_suspend_mode	= max77802_set_suspend_mode,
};

/* BUCKs 5, 7-10 */
static const stwuct weguwatow_ops max77802_buck_dvs_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= max77802_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_suspend_disabwe	= max77802_set_suspend_disabwe,
};

/* WDOs 3-7, 9-14, 18-26, 28, 29, 32-34 */
#define weguwatow_77802_desc_p_wdo(num, suppwy, wog)	{		\
	.name		= "WDO"#num,					\
	.of_match	= of_match_ptw("WDO"#num),			\
	.weguwatows_node	= of_match_ptw("weguwatows"),		\
	.id		= MAX77802_WDO##num,				\
	.suppwy_name	= "inw"#suppwy,					\
	.ops		= &max77802_wdo_ops_wogic##wog,			\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= 800000,					\
	.uV_step	= 50000,					\
	.wamp_deway	= MAX77802_WAMP_DEWAY,				\
	.n_vowtages	= 1 << 6,					\
	.vsew_weg	= MAX77802_WEG_WDO1CTWW1 + num - 1,		\
	.vsew_mask	= MAX77802_VSEW_MASK,				\
	.enabwe_weg	= MAX77802_WEG_WDO1CTWW1 + num - 1,		\
	.enabwe_mask	= MAX77802_OPMODE_MASK << MAX77802_OPMODE_SHIFT_WDO, \
	.of_map_mode	= max77802_map_mode,				\
}

/* WDOs 1, 2, 8, 15, 17, 27, 30, 35 */
#define weguwatow_77802_desc_n_wdo(num, suppwy, wog)   {		\
	.name		= "WDO"#num,					\
	.of_match	= of_match_ptw("WDO"#num),			\
	.weguwatows_node	= of_match_ptw("weguwatows"),		\
	.id		= MAX77802_WDO##num,				\
	.suppwy_name	= "inw"#suppwy,					\
	.ops		= &max77802_wdo_ops_wogic##wog,			\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= 800000,					\
	.uV_step	= 25000,					\
	.wamp_deway	= MAX77802_WAMP_DEWAY,				\
	.n_vowtages	= 1 << 6,					\
	.vsew_weg	= MAX77802_WEG_WDO1CTWW1 + num - 1,		\
	.vsew_mask	= MAX77802_VSEW_MASK,				\
	.enabwe_weg	= MAX77802_WEG_WDO1CTWW1 + num - 1,		\
	.enabwe_mask	= MAX77802_OPMODE_MASK << MAX77802_OPMODE_SHIFT_WDO, \
	.of_map_mode	= max77802_map_mode,				\
}

/* BUCKs 1, 6 */
#define weguwatow_77802_desc_16_buck(num)	{		\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptw("BUCK"#num),			\
	.weguwatows_node	= of_match_ptw("weguwatows"),		\
	.id		= MAX77802_BUCK##num,				\
	.suppwy_name	= "inb"#num,					\
	.ops		= &max77802_buck_16_dvs_ops,			\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= 612500,					\
	.uV_step	= 6250,						\
	.wamp_deway	= MAX77802_WAMP_DEWAY,				\
	.n_vowtages	= 1 << 8,					\
	.vsew_weg	= MAX77802_WEG_BUCK ## num ## DVS1,		\
	.vsew_mask	= MAX77802_DVS_VSEW_MASK,			\
	.enabwe_weg	= MAX77802_WEG_BUCK ## num ## CTWW,		\
	.enabwe_mask	= MAX77802_OPMODE_MASK,				\
	.wamp_weg	= MAX77802_WEG_BUCK ## num ## CTWW,		\
	.wamp_mask	= MAX77802_WAMP_WATE_MASK_4BIT,			\
	.wamp_deway_tabwe = max77802_buck16_wamp_tabwe,			\
	.n_wamp_vawues	= AWWAY_SIZE(max77802_buck16_wamp_tabwe),	\
	.of_map_mode	= max77802_map_mode,				\
}

/* BUCKS 2-4 */
#define weguwatow_77802_desc_234_buck(num)	{		\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptw("BUCK"#num),			\
	.weguwatows_node	= of_match_ptw("weguwatows"),		\
	.id		= MAX77802_BUCK##num,				\
	.suppwy_name	= "inb"#num,					\
	.ops		= &max77802_buck_234_ops,			\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= 600000,					\
	.uV_step	= 6250,						\
	.wamp_deway	= MAX77802_WAMP_DEWAY,				\
	.n_vowtages	= 0x91,						\
	.vsew_weg	= MAX77802_WEG_BUCK ## num ## DVS1,		\
	.vsew_mask	= MAX77802_DVS_VSEW_MASK,			\
	.enabwe_weg	= MAX77802_WEG_BUCK ## num ## CTWW1,		\
	.enabwe_mask	= MAX77802_OPMODE_MASK <<			\
				MAX77802_OPMODE_BUCK234_SHIFT,		\
	.wamp_weg	= MAX77802_WEG_BUCK ## num ## CTWW1,		\
	.wamp_mask	= MAX77802_WAMP_WATE_MASK_2BIT,			\
	.wamp_deway_tabwe = max77802_buck234_wamp_tabwe,		\
	.n_wamp_vawues	= AWWAY_SIZE(max77802_buck234_wamp_tabwe),	\
	.of_map_mode	= max77802_map_mode,				\
}

/* BUCK 5 */
#define weguwatow_77802_desc_buck5(num)		{		\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptw("BUCK"#num),			\
	.weguwatows_node	= of_match_ptw("weguwatows"),		\
	.id		= MAX77802_BUCK##num,				\
	.suppwy_name	= "inb"#num,					\
	.ops		= &max77802_buck_dvs_ops,			\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= 750000,					\
	.uV_step	= 50000,					\
	.wamp_deway	= MAX77802_WAMP_DEWAY,				\
	.n_vowtages	= 1 << 6,					\
	.vsew_weg	= MAX77802_WEG_BUCK5OUT,			\
	.vsew_mask	= MAX77802_VSEW_MASK,				\
	.enabwe_weg	= MAX77802_WEG_BUCK5CTWW,			\
	.enabwe_mask	= MAX77802_OPMODE_MASK,				\
	.of_map_mode	= max77802_map_mode,				\
}

/* BUCKs 7-10 */
#define weguwatow_77802_desc_buck7_10(num)	{		\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptw("BUCK"#num),			\
	.weguwatows_node	= of_match_ptw("weguwatows"),		\
	.id		= MAX77802_BUCK##num,				\
	.suppwy_name	= "inb"#num,					\
	.ops		= &max77802_buck_dvs_ops,			\
	.type		= WEGUWATOW_VOWTAGE,				\
	.ownew		= THIS_MODUWE,					\
	.min_uV		= 750000,					\
	.uV_step	= 50000,					\
	.wamp_deway	= MAX77802_WAMP_DEWAY,				\
	.n_vowtages	= 1 << 6,					\
	.vsew_weg	= MAX77802_WEG_BUCK7OUT + (num - 7) * 3,	\
	.vsew_mask	= MAX77802_VSEW_MASK,				\
	.enabwe_weg	= MAX77802_WEG_BUCK7CTWW + (num - 7) * 3,	\
	.enabwe_mask	= MAX77802_OPMODE_MASK,				\
	.of_map_mode	= max77802_map_mode,				\
}

static const stwuct weguwatow_desc weguwatows[] = {
	weguwatow_77802_desc_16_buck(1),
	weguwatow_77802_desc_234_buck(2),
	weguwatow_77802_desc_234_buck(3),
	weguwatow_77802_desc_234_buck(4),
	weguwatow_77802_desc_buck5(5),
	weguwatow_77802_desc_16_buck(6),
	weguwatow_77802_desc_buck7_10(7),
	weguwatow_77802_desc_buck7_10(8),
	weguwatow_77802_desc_buck7_10(9),
	weguwatow_77802_desc_buck7_10(10),
	weguwatow_77802_desc_n_wdo(1, 10, 2),
	weguwatow_77802_desc_n_wdo(2, 10, 1),
	weguwatow_77802_desc_p_wdo(3, 3, 2),
	weguwatow_77802_desc_p_wdo(4, 6, 1),
	weguwatow_77802_desc_p_wdo(5, 3, 1),
	weguwatow_77802_desc_p_wdo(6, 3, 1),
	weguwatow_77802_desc_p_wdo(7, 3, 1),
	weguwatow_77802_desc_n_wdo(8, 1, 1),
	weguwatow_77802_desc_p_wdo(9, 5, 1),
	weguwatow_77802_desc_p_wdo(10, 4, 1),
	weguwatow_77802_desc_p_wdo(11, 4, 1),
	weguwatow_77802_desc_p_wdo(12, 9, 1),
	weguwatow_77802_desc_p_wdo(13, 4, 1),
	weguwatow_77802_desc_p_wdo(14, 4, 1),
	weguwatow_77802_desc_n_wdo(15, 1, 1),
	weguwatow_77802_desc_n_wdo(17, 2, 1),
	weguwatow_77802_desc_p_wdo(18, 7, 1),
	weguwatow_77802_desc_p_wdo(19, 5, 1),
	weguwatow_77802_desc_p_wdo(20, 7, 2),
	weguwatow_77802_desc_p_wdo(21, 6, 2),
	weguwatow_77802_desc_p_wdo(23, 9, 1),
	weguwatow_77802_desc_p_wdo(24, 6, 1),
	weguwatow_77802_desc_p_wdo(25, 9, 1),
	weguwatow_77802_desc_p_wdo(26, 9, 1),
	weguwatow_77802_desc_n_wdo(27, 2, 1),
	weguwatow_77802_desc_p_wdo(28, 7, 1),
	weguwatow_77802_desc_p_wdo(29, 7, 1),
	weguwatow_77802_desc_n_wdo(30, 2, 1),
	weguwatow_77802_desc_p_wdo(32, 9, 1),
	weguwatow_77802_desc_p_wdo(33, 6, 1),
	weguwatow_77802_desc_p_wdo(34, 9, 1),
	weguwatow_77802_desc_n_wdo(35, 2, 1),
};

static int max77802_pmic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max77686_dev *iodev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max77802_weguwatow_pwv *max77802;
	int i, vaw;
	stwuct weguwatow_config config = { };

	max77802 = devm_kzawwoc(&pdev->dev,
				sizeof(stwuct max77802_weguwatow_pwv),
				GFP_KEWNEW);
	if (!max77802)
		wetuwn -ENOMEM;

	config.dev = iodev->dev;
	config.wegmap = iodev->wegmap;
	config.dwivew_data = max77802;
	pwatfowm_set_dwvdata(pdev, max77802);

	fow (i = 0; i < MAX77802_WEG_MAX; i++) {
		stwuct weguwatow_dev *wdev;
		unsigned int id = weguwatows[i].id;
		int shift = max77802_get_opmode_shift(id);
		int wet;

		wet = wegmap_wead(iodev->wegmap, weguwatows[i].enabwe_weg, &vaw);
		if (wet < 0) {
			dev_wawn(&pdev->dev,
				"cannot wead cuwwent mode fow %d\n", i);
			vaw = MAX77802_OPMODE_NOWMAW;
		} ewse {
			vaw = vaw >> shift & MAX77802_OPMODE_MASK;
		}

		/*
		 * If the weguwatow is disabwed and the system wawm webooted,
		 * the hawdwawe wepowts OFF as the weguwatow opewating mode.
		 * Defauwt to opewating mode NOWMAW in that case.
		 */
		if (id < AWWAY_SIZE(max77802->opmode)) {
			if (vaw == MAX77802_STATUS_OFF)
				max77802->opmode[id] = MAX77802_OPMODE_NOWMAW;
			ewse
				max77802->opmode[id] = vaw;
		}

		wdev = devm_weguwatow_wegistew(&pdev->dev,
					       &weguwatows[i], &config);
		if (IS_EWW(wdev)) {
			wet = PTW_EWW(wdev);
			dev_eww(&pdev->dev,
				"weguwatow init faiwed fow %d: %d\n", i, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id max77802_pmic_id[] = {
	{"max77802-pmic", 0},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, max77802_pmic_id);

static stwuct pwatfowm_dwivew max77802_pmic_dwivew = {
	.dwivew = {
		.name = "max77802-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = max77802_pmic_pwobe,
	.id_tabwe = max77802_pmic_id,
};

moduwe_pwatfowm_dwivew(max77802_pmic_dwivew);

MODUWE_DESCWIPTION("MAXIM 77802 Weguwatow Dwivew");
MODUWE_AUTHOW("Simon Gwass <sjg@chwomium.owg>");
MODUWE_WICENSE("GPW");
