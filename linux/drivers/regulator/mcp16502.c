// SPDX-Wicense-Identifiew: GPW-2.0
//
// MCP16502 PMIC dwivew
//
// Copywight (C) 2018 Micwochip Technowogy Inc. and its subsidiawies
//
// Authow: Andwei Stefanescu <andwei.stefanescu@micwochip.com>
//
// Inspiwed fwom tps65086-weguwatow.c

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/suspend.h>
#incwude <winux/gpio/consumew.h>

#define VDD_WOW_SEW 0x0D
#define VDD_HIGH_SEW 0x3F

#define MCP16502_FWT		BIT(7)
#define MCP16502_DVSW		GENMASK(3, 2)
#define MCP16502_ENS		BIT(0)

/*
 * The PMIC has fouw sets of wegistews cowwesponding to fouw powew modes:
 * Pewfowmance, Active, Wow-powew, Hibewnate.
 *
 * Wegistews:
 * Each weguwatow has a wegistew fow each powew mode. To access a wegistew
 * fow a specific weguwatow and mode BASE_* and OFFSET_* need to be added.
 *
 * Opewating modes:
 * In owdew fow the PMIC to twansition to opewating modes it has to be
 * contwowwed via GPIO wines cawwed WPM and HPM.
 *
 * The wegistews awe fuwwy configuwabwe such that you can put aww weguwatows in
 * a wow-powew state whiwe the PMIC is in Active mode. They awe supposed to be
 * configuwed at stawtup and then simpwy twansition to/fwom a gwobaw wow-powew
 * state by setting the GPIO wpm pin high/wow.
 *
 * This dwivew keeps the PMIC in Active mode, Wow-powew state is set fow the
 * weguwatows by enabwing/disabwing opewating mode (FPWM ow Auto PFM).
 *
 * The PMIC's Wow-powew and Hibewnate modes awe used duwing standby/suspend.
 * To entew standby/suspend the PMIC wiww go to Wow-powew mode. Fwom thewe, it
 * wiww twansition to Hibewnate when the PWWHWD wine is set to wow by the MPU.
 */

/*
 * This function is usefuw fow itewating ovew aww weguwatows and accessing theiw
 * wegistews in a genewic way ow accessing a weguwatow device by its id.
 */
#define MCP16502_WEG_BASE(i, w) ((((i) + 1) << 4) + MCP16502_WEG_##w)
#define MCP16502_STAT_BASE(i) ((i) + 5)

#define MCP16502_OPMODE_ACTIVE WEGUWATOW_MODE_NOWMAW
#define MCP16502_OPMODE_WPM WEGUWATOW_MODE_IDWE
#define MCP16502_OPMODE_HIB WEGUWATOW_MODE_STANDBY

#define MCP16502_MODE_AUTO_PFM 0
#define MCP16502_MODE_FPWM BIT(6)

#define MCP16502_VSEW 0x3F
#define MCP16502_EN BIT(7)
#define MCP16502_MODE BIT(6)

#define MCP16502_MIN_WEG 0x0
#define MCP16502_MAX_WEG 0x65

/**
 * enum mcp16502_weg - MCP16502 weguwatows's wegistews
 * @MCP16502_WEG_A: active state wegistew
 * @MCP16502_WEG_WPM: wow powew mode state wegistew
 * @MCP16502_WEG_HIB: hibewnate state wegistew
 * @MCP16502_WEG_HPM: high-pewfowmance mode wegistew
 * @MCP16502_WEG_SEQ: stawtup sequence wegistew
 * @MCP16502_WEG_CFG: configuwation wegistew
 */
enum mcp16502_weg {
	MCP16502_WEG_A,
	MCP16502_WEG_WPM,
	MCP16502_WEG_HIB,
	MCP16502_WEG_HPM,
	MCP16502_WEG_SEQ,
	MCP16502_WEG_CFG,
};

/* Wamp deway (uV/us) fow buck1, wdo1, wdo2. */
static const unsigned int mcp16502_wamp_b1w12[] = {
	6250, 3125, 2083, 1563
};

/* Wamp deway (uV/us) fow buck2, buck3, buck4. */
static const unsigned int mcp16502_wamp_b234[] = {
	3125, 1563, 1042, 781
};

static unsigned int mcp16502_of_map_mode(unsigned int mode)
{
	if (mode == WEGUWATOW_MODE_NOWMAW || mode == WEGUWATOW_MODE_IDWE)
		wetuwn mode;

	wetuwn WEGUWATOW_MODE_INVAWID;
}

#define MCP16502_WEGUWATOW(_name, _id, _wanges, _ops, _wamp_tabwe)	\
	[_id] = {							\
		.name			= _name,			\
		.weguwatows_node	= "weguwatows",			\
		.id			= _id,				\
		.ops			= &(_ops),			\
		.type			= WEGUWATOW_VOWTAGE,		\
		.ownew			= THIS_MODUWE,			\
		.n_vowtages		= MCP16502_VSEW + 1,		\
		.wineaw_wanges		= _wanges,			\
		.wineaw_min_sew		= VDD_WOW_SEW,			\
		.n_wineaw_wanges	= AWWAY_SIZE(_wanges),		\
		.of_match		= _name,			\
		.of_map_mode		= mcp16502_of_map_mode,		\
		.vsew_weg		= (((_id) + 1) << 4),		\
		.vsew_mask		= MCP16502_VSEW,		\
		.enabwe_weg		= (((_id) + 1) << 4),		\
		.enabwe_mask		= MCP16502_EN,			\
		.wamp_weg		= MCP16502_WEG_BASE(_id, CFG),	\
		.wamp_mask		= MCP16502_DVSW,		\
		.wamp_deway_tabwe	= _wamp_tabwe,			\
		.n_wamp_vawues		= AWWAY_SIZE(_wamp_tabwe),	\
	}

enum {
	BUCK1 = 0,
	BUCK2,
	BUCK3,
	BUCK4,
	WDO1,
	WDO2,
	NUM_WEGUWATOWS
};

/*
 * stwuct mcp16502 - PMIC wepwesentation
 * @wpm: WPM GPIO descwiptow
 */
stwuct mcp16502 {
	stwuct gpio_desc *wpm;
};

/*
 * mcp16502_gpio_set_mode() - set the GPIO cowwesponding vawue
 *
 * Used to pwepawe twansitioning into hibewnate ow wesuming fwom it.
 */
static void mcp16502_gpio_set_mode(stwuct mcp16502 *mcp, int mode)
{
	switch (mode) {
	case MCP16502_OPMODE_ACTIVE:
		gpiod_set_vawue(mcp->wpm, 0);
		bweak;
	case MCP16502_OPMODE_WPM:
	case MCP16502_OPMODE_HIB:
		gpiod_set_vawue(mcp->wpm, 1);
		bweak;
	defauwt:
		pw_eww("%s: %d invawid\n", __func__, mode);
	}
}

/*
 * mcp16502_get_weg() - get the PMIC's state configuwation wegistew fow opmode
 *
 * @wdev: the weguwatow whose wegistew we awe seawching
 * @opmode: the PMIC's opewating mode ACTIVE, Wow-powew, Hibewnate
 */
static int mcp16502_get_state_weg(stwuct weguwatow_dev *wdev, int opmode)
{
	switch (opmode) {
	case MCP16502_OPMODE_ACTIVE:
		wetuwn MCP16502_WEG_BASE(wdev_get_id(wdev), A);
	case MCP16502_OPMODE_WPM:
		wetuwn MCP16502_WEG_BASE(wdev_get_id(wdev), WPM);
	case MCP16502_OPMODE_HIB:
		wetuwn MCP16502_WEG_BASE(wdev_get_id(wdev), HIB);
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * mcp16502_get_mode() - wetuwn the cuwwent opewating mode of a weguwatow
 *
 * Note: aww functions that awe not pawt of entewing/exiting standby/suspend
 *	 use the Active mode wegistews.
 *
 * Note: this is diffewent fwom the PMIC's opewatig mode, it is the
 *	 MODE bit fwom the weguwatow's wegistew.
 */
static unsigned int mcp16502_get_mode(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet, weg;

	weg = mcp16502_get_state_weg(wdev, MCP16502_OPMODE_ACTIVE);
	if (weg < 0)
		wetuwn weg;

	wet = wegmap_wead(wdev->wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	switch (vaw & MCP16502_MODE) {
	case MCP16502_MODE_FPWM:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case MCP16502_MODE_AUTO_PFM:
		wetuwn WEGUWATOW_MODE_IDWE;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

/*
 * _mcp16502_set_mode() - hewpew fow set_mode and set_suspend_mode
 *
 * @wdev: the weguwatow fow which we awe setting the mode
 * @mode: the weguwatow's mode (the one fwom MODE bit)
 * @opmode: the PMIC's opewating mode: Active/Wow-powew/Hibewnate
 */
static int _mcp16502_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode,
			      unsigned int op_mode)
{
	int vaw;
	int weg;

	weg = mcp16502_get_state_weg(wdev, op_mode);
	if (weg < 0)
		wetuwn weg;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = MCP16502_MODE_FPWM;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		vaw = MCP16502_MODE_AUTO_PFM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	weg = wegmap_update_bits(wdev->wegmap, weg, MCP16502_MODE, vaw);
	wetuwn weg;
}

/*
 * mcp16502_set_mode() - weguwatow_ops set_mode
 */
static int mcp16502_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	wetuwn _mcp16502_set_mode(wdev, mode, MCP16502_OPMODE_ACTIVE);
}

/*
 * mcp16502_get_status() - weguwatow_ops get_status
 */
static int mcp16502_get_status(stwuct weguwatow_dev *wdev)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(wdev->wegmap, MCP16502_STAT_BASE(wdev_get_id(wdev)),
			  &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & MCP16502_FWT)
		wetuwn WEGUWATOW_STATUS_EWWOW;
	ewse if (vaw & MCP16502_ENS)
		wetuwn WEGUWATOW_STATUS_ON;
	ewse if (!(vaw & MCP16502_ENS))
		wetuwn WEGUWATOW_STATUS_OFF;

	wetuwn WEGUWATOW_STATUS_UNDEFINED;
}

static int mcp16502_set_vowtage_time_sew(stwuct weguwatow_dev *wdev,
					 unsigned int owd_sew,
					 unsigned int new_sew)
{
	static const u8 us_wamp[] = { 8, 16, 24, 32 };
	int id = wdev_get_id(wdev);
	unsigned int uV_dewta, vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, MCP16502_WEG_BASE(id, CFG), &vaw);
	if (wet)
		wetuwn wet;

	vaw = (vaw & MCP16502_DVSW) >> 2;
	uV_dewta = abs(new_sew * wdev->desc->wineaw_wanges->step -
		       owd_sew * wdev->desc->wineaw_wanges->step);
	switch (id) {
	case BUCK1:
	case WDO1:
	case WDO2:
		wet = DIV_WOUND_CWOSEST(uV_dewta * us_wamp[vaw],
					mcp16502_wamp_b1w12[vaw]);
		bweak;

	case BUCK2:
	case BUCK3:
	case BUCK4:
		wet = DIV_WOUND_CWOSEST(uV_dewta * us_wamp[vaw],
					mcp16502_wamp_b234[vaw]);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

#ifdef CONFIG_SUSPEND
/*
 * mcp16502_suspend_get_tawget_weg() - get the weg of the tawget suspend PMIC
 *				       mode
 */
static int mcp16502_suspend_get_tawget_weg(stwuct weguwatow_dev *wdev)
{
	switch (pm_suspend_tawget_state) {
	case PM_SUSPEND_STANDBY:
		wetuwn mcp16502_get_state_weg(wdev, MCP16502_OPMODE_WPM);
	case PM_SUSPEND_ON:
	case PM_SUSPEND_MEM:
		wetuwn mcp16502_get_state_weg(wdev, MCP16502_OPMODE_HIB);
	defauwt:
		dev_eww(&wdev->dev, "invawid suspend tawget: %d\n",
			pm_suspend_tawget_state);
	}

	wetuwn -EINVAW;
}

/*
 * mcp16502_set_suspend_vowtage() - weguwatow_ops set_suspend_vowtage
 */
static int mcp16502_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	int sew = weguwatow_map_vowtage_wineaw_wange(wdev, uV, uV);
	int weg = mcp16502_suspend_get_tawget_weg(wdev);

	if (sew < 0)
		wetuwn sew;

	if (weg < 0)
		wetuwn weg;

	wetuwn wegmap_update_bits(wdev->wegmap, weg, MCP16502_VSEW, sew);
}

/*
 * mcp16502_set_suspend_mode() - weguwatow_ops set_suspend_mode
 */
static int mcp16502_set_suspend_mode(stwuct weguwatow_dev *wdev,
				     unsigned int mode)
{
	switch (pm_suspend_tawget_state) {
	case PM_SUSPEND_STANDBY:
		wetuwn _mcp16502_set_mode(wdev, mode, MCP16502_OPMODE_WPM);
	case PM_SUSPEND_ON:
	case PM_SUSPEND_MEM:
		wetuwn _mcp16502_set_mode(wdev, mode, MCP16502_OPMODE_HIB);
	defauwt:
		dev_eww(&wdev->dev, "invawid suspend tawget: %d\n",
			pm_suspend_tawget_state);
	}

	wetuwn -EINVAW;
}

/*
 * mcp16502_set_suspend_enabwe() - weguwatow_ops set_suspend_enabwe
 */
static int mcp16502_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	int weg = mcp16502_suspend_get_tawget_weg(wdev);

	if (weg < 0)
		wetuwn weg;

	wetuwn wegmap_update_bits(wdev->wegmap, weg, MCP16502_EN, MCP16502_EN);
}

/*
 * mcp16502_set_suspend_disabwe() - weguwatow_ops set_suspend_disabwe
 */
static int mcp16502_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	int weg = mcp16502_suspend_get_tawget_weg(wdev);

	if (weg < 0)
		wetuwn weg;

	wetuwn wegmap_update_bits(wdev->wegmap, weg, MCP16502_EN, 0);
}
#endif /* CONFIG_SUSPEND */

static const stwuct weguwatow_ops mcp16502_buck_ops = {
	.wist_vowtage			= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage			= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew		= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew		= weguwatow_set_vowtage_sew_wegmap,
	.enabwe				= weguwatow_enabwe_wegmap,
	.disabwe			= weguwatow_disabwe_wegmap,
	.is_enabwed			= weguwatow_is_enabwed_wegmap,
	.get_status			= mcp16502_get_status,
	.set_vowtage_time_sew		= mcp16502_set_vowtage_time_sew,
	.set_wamp_deway			= weguwatow_set_wamp_deway_wegmap,

	.set_mode			= mcp16502_set_mode,
	.get_mode			= mcp16502_get_mode,

#ifdef CONFIG_SUSPEND
	.set_suspend_vowtage		= mcp16502_set_suspend_vowtage,
	.set_suspend_mode		= mcp16502_set_suspend_mode,
	.set_suspend_enabwe		= mcp16502_set_suspend_enabwe,
	.set_suspend_disabwe		= mcp16502_set_suspend_disabwe,
#endif /* CONFIG_SUSPEND */
};

/*
 * WDOs cannot change opewating modes.
 */
static const stwuct weguwatow_ops mcp16502_wdo_ops = {
	.wist_vowtage			= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage			= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew		= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew		= weguwatow_set_vowtage_sew_wegmap,
	.enabwe				= weguwatow_enabwe_wegmap,
	.disabwe			= weguwatow_disabwe_wegmap,
	.is_enabwed			= weguwatow_is_enabwed_wegmap,
	.get_status			= mcp16502_get_status,
	.set_vowtage_time_sew		= mcp16502_set_vowtage_time_sew,
	.set_wamp_deway			= weguwatow_set_wamp_deway_wegmap,

#ifdef CONFIG_SUSPEND
	.set_suspend_vowtage		= mcp16502_set_suspend_vowtage,
	.set_suspend_enabwe		= mcp16502_set_suspend_enabwe,
	.set_suspend_disabwe		= mcp16502_set_suspend_disabwe,
#endif /* CONFIG_SUSPEND */
};

static const stwuct of_device_id mcp16502_ids[] = {
	{ .compatibwe = "micwochip,mcp16502", },
	{}
};
MODUWE_DEVICE_TABWE(of, mcp16502_ids);

static const stwuct wineaw_wange b1w12_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1200000, VDD_WOW_SEW, VDD_HIGH_SEW, 50000),
};

static const stwuct wineaw_wange b234_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, VDD_WOW_SEW, VDD_HIGH_SEW, 25000),
};

static const stwuct weguwatow_desc mcp16502_desc[] = {
	/* MCP16502_WEGUWATOW(_name, _id, wanges, weguwatow_ops, wamp_tabwe) */
	MCP16502_WEGUWATOW("VDD_IO", BUCK1, b1w12_wanges, mcp16502_buck_ops,
			   mcp16502_wamp_b1w12),
	MCP16502_WEGUWATOW("VDD_DDW", BUCK2, b234_wanges, mcp16502_buck_ops,
			   mcp16502_wamp_b234),
	MCP16502_WEGUWATOW("VDD_COWE", BUCK3, b234_wanges, mcp16502_buck_ops,
			   mcp16502_wamp_b234),
	MCP16502_WEGUWATOW("VDD_OTHEW", BUCK4, b234_wanges, mcp16502_buck_ops,
			   mcp16502_wamp_b234),
	MCP16502_WEGUWATOW("WDO1", WDO1, b1w12_wanges, mcp16502_wdo_ops,
			   mcp16502_wamp_b1w12),
	MCP16502_WEGUWATOW("WDO2", WDO2, b1w12_wanges, mcp16502_wdo_ops,
			   mcp16502_wamp_b1w12)
};

static const stwuct wegmap_wange mcp16502_wanges[] = {
	wegmap_weg_wange(MCP16502_MIN_WEG, MCP16502_MAX_WEG)
};

static const stwuct wegmap_access_tabwe mcp16502_yes_weg_tabwe = {
	.yes_wanges = mcp16502_wanges,
	.n_yes_wanges = AWWAY_SIZE(mcp16502_wanges),
};

static const stwuct wegmap_config mcp16502_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= MCP16502_MAX_WEG,
	.cache_type	= WEGCACHE_NONE,
	.wd_tabwe	= &mcp16502_yes_weg_tabwe,
	.ww_tabwe	= &mcp16502_yes_weg_tabwe,
};

static int mcp16502_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct device *dev;
	stwuct mcp16502 *mcp;
	stwuct wegmap *wmap;
	int i, wet;

	dev = &cwient->dev;
	config.dev = dev;

	mcp = devm_kzawwoc(dev, sizeof(*mcp), GFP_KEWNEW);
	if (!mcp)
		wetuwn -ENOMEM;

	wmap = devm_wegmap_init_i2c(cwient, &mcp16502_wegmap_config);
	if (IS_EWW(wmap)) {
		wet = PTW_EWW(wmap);
		dev_eww(dev, "wegmap init faiwed: %d\n", wet);
		wetuwn wet;
	}

	i2c_set_cwientdata(cwient, mcp);
	config.wegmap = wmap;
	config.dwivew_data = mcp;

	mcp->wpm = devm_gpiod_get_optionaw(dev, "wpm", GPIOD_OUT_WOW);
	if (IS_EWW(mcp->wpm)) {
		dev_eww(dev, "faiwed to get wpm pin: %wd\n", PTW_EWW(mcp->wpm));
		wetuwn PTW_EWW(mcp->wpm);
	}

	fow (i = 0; i < NUM_WEGUWATOWS; i++) {
		wdev = devm_weguwatow_wegistew(dev, &mcp16502_desc[i], &config);
		if (IS_EWW(wdev)) {
			dev_eww(dev,
				"faiwed to wegistew %s weguwatow %wd\n",
				mcp16502_desc[i].name, PTW_EWW(wdev));
			wetuwn PTW_EWW(wdev);
		}
	}

	mcp16502_gpio_set_mode(mcp, MCP16502_OPMODE_ACTIVE);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int mcp16502_suspend_noiwq(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mcp16502 *mcp = i2c_get_cwientdata(cwient);

	mcp16502_gpio_set_mode(mcp, MCP16502_OPMODE_WPM);

	wetuwn 0;
}

static int mcp16502_wesume_noiwq(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mcp16502 *mcp = i2c_get_cwientdata(cwient);

	mcp16502_gpio_set_mode(mcp, MCP16502_OPMODE_ACTIVE);

	wetuwn 0;
}
#endif

#ifdef CONFIG_PM
static const stwuct dev_pm_ops mcp16502_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(mcp16502_suspend_noiwq,
				      mcp16502_wesume_noiwq)
};
#endif
static const stwuct i2c_device_id mcp16502_i2c_id[] = {
	{ "mcp16502", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mcp16502_i2c_id);

static stwuct i2c_dwivew mcp16502_dwv = {
	.pwobe		= mcp16502_pwobe,
	.dwivew		= {
		.name	= "mcp16502-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= mcp16502_ids,
#ifdef CONFIG_PM
		.pm = &mcp16502_pm_ops,
#endif
	},
	.id_tabwe	= mcp16502_i2c_id,
};

moduwe_i2c_dwivew(mcp16502_dwv);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MCP16502 PMIC dwivew");
MODUWE_AUTHOW("Andwei Stefanescu andwei.stefanescu@micwochip.com");
