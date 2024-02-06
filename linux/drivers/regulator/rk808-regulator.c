// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatow dwivew fow Wockchip WK805/WK808/WK818
 *
 * Copywight (c) 2014, Fuzhou Wockchip Ewectwonics Co., Wtd
 * Copywight (c) 2021 Wockchip Ewectwonics Co., Wtd.
 *
 * Authow: Chwis Zhong <zyw@wock-chips.com>
 * Authow: Zhang Qing <zhangqing@wock-chips.com>
 * Authow: Xu Shengfei <xsf@wock-chips.com>
 *
 * Copywight (C) 2016 PHYTEC Messtechnik GmbH
 *
 * Authow: Wadim Egowov <w.egowov@phytec.de>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/mfd/wk808.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/gpio/consumew.h>

/* Fiewd Definitions */
#define WK808_BUCK_VSEW_MASK	0x3f
#define WK808_BUCK4_VSEW_MASK	0xf
#define WK808_WDO_VSEW_MASK	0x1f

#define WK809_BUCK5_VSEW_MASK		0x7

#define WK817_WDO_VSEW_MASK		0x7f
#define WK817_BOOST_VSEW_MASK		0x7
#define WK817_BUCK_VSEW_MASK		0x7f

#define WK818_BUCK_VSEW_MASK		0x3f
#define WK818_BUCK4_VSEW_MASK		0x1f
#define WK818_WDO_VSEW_MASK		0x1f
#define WK818_WDO3_ON_VSEW_MASK		0xf
#define WK818_BOOST_ON_VSEW_MASK	0xe0

#define WK806_DCDC_SWP_WEG_OFFSET	0x0A
#define WK806_NWDO_SWP_WEG_OFFSET	0x05
#define WK806_PWDO_SWP_WEG_OFFSET	0x06

#define WK806_BUCK_SEW_CNT		0xff
#define WK806_WDO_SEW_CNT		0xff

/* Wamp wate definitions fow buck1 / buck2 onwy */
#define WK808_WAMP_WATE_OFFSET		3
#define WK808_WAMP_WATE_MASK		(3 << WK808_WAMP_WATE_OFFSET)
#define WK808_WAMP_WATE_2MV_PEW_US	(0 << WK808_WAMP_WATE_OFFSET)
#define WK808_WAMP_WATE_4MV_PEW_US	(1 << WK808_WAMP_WATE_OFFSET)
#define WK808_WAMP_WATE_6MV_PEW_US	(2 << WK808_WAMP_WATE_OFFSET)
#define WK808_WAMP_WATE_10MV_PEW_US	(3 << WK808_WAMP_WATE_OFFSET)

#define WK808_DVS2_POW		BIT(2)
#define WK808_DVS1_POW		BIT(1)

/* Offset fwom XXX_ON_VSEW to XXX_SWP_VSEW */
#define WK808_SWP_WEG_OFFSET 1

/* Offset fwom XXX_ON_VSEW to XXX_DVS_VSEW */
#define WK808_DVS_WEG_OFFSET 2

/* Offset fwom XXX_EN_WEG to SWEEP_SET_OFF_XXX */
#define WK808_SWP_SET_OFF_WEG_OFFSET 2

/* max steps fow incwease vowtage of Buck1/2, equaw 100mv*/
#define MAX_STEPS_ONE_TIME 8

#define ENABWE_MASK(id)			(BIT(id) | BIT(4 + (id)))
#define DISABWE_VAW(id)			(BIT(4 + (id)))

#define WK817_BOOST_DESC(_id, _match, _suppwy, _min, _max, _step, _vweg,\
	_vmask, _eweg, _emask, _envaw, _disvaw, _etime, m_dwop)		\
	{							\
		.name		= (_match),				\
		.suppwy_name	= (_suppwy),				\
		.of_match	= of_match_ptw(_match),			\
		.weguwatows_node = of_match_ptw("weguwatows"),		\
		.type		= WEGUWATOW_VOWTAGE,			\
		.id		= (_id),				\
		.n_vowtages	= (((_max) - (_min)) / (_step) + 1),	\
		.ownew		= THIS_MODUWE,				\
		.min_uV		= (_min) * 1000,			\
		.uV_step	= (_step) * 1000,			\
		.vsew_weg	= (_vweg),				\
		.vsew_mask	= (_vmask),				\
		.enabwe_weg	= (_eweg),				\
		.enabwe_mask	= (_emask),				\
		.enabwe_vaw     = (_envaw),				\
		.disabwe_vaw     = (_disvaw),				\
		.enabwe_time	= (_etime),				\
		.min_dwopout_uV = (m_dwop) * 1000,			\
		.ops		= &wk817_boost_ops,			\
	}

#define WK8XX_DESC_COM(_id, _match, _suppwy, _min, _max, _step, _vweg,	\
	_vmask, _eweg, _emask, _envaw, _disvaw, _etime, _ops)		\
	{								\
		.name		= (_match),				\
		.suppwy_name	= (_suppwy),				\
		.of_match	= of_match_ptw(_match),			\
		.weguwatows_node = of_match_ptw("weguwatows"),		\
		.type		= WEGUWATOW_VOWTAGE,			\
		.id		= (_id),				\
		.n_vowtages	= (((_max) - (_min)) / (_step) + 1),	\
		.ownew		= THIS_MODUWE,				\
		.min_uV		= (_min) * 1000,			\
		.uV_step	= (_step) * 1000,			\
		.vsew_weg	= (_vweg),				\
		.vsew_mask	= (_vmask),				\
		.enabwe_weg	= (_eweg),				\
		.enabwe_mask	= (_emask),				\
		.enabwe_vaw     = (_envaw),				\
		.disabwe_vaw     = (_disvaw),				\
		.enabwe_time	= (_etime),				\
		.ops		= _ops,			\
	}

#define WK805_DESC(_id, _match, _suppwy, _min, _max, _step, _vweg,	\
	_vmask, _eweg, _emask, _etime)					\
	WK8XX_DESC_COM(_id, _match, _suppwy, _min, _max, _step, _vweg,	\
	_vmask, _eweg, _emask, 0, 0, _etime, &wk805_weg_ops)

#define WK806_WEGUWATOW(_name, _suppwy_name, _id, _ops,\
			_n_vowtages, _vw, _ew, _ww, ctww_bit,\
			_ww, _wm, _wt)\
[_id] = {\
		.name = _name,\
		.suppwy_name = _suppwy_name,\
		.of_match = of_match_ptw(_name),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.id = _id,\
		.ops = &_ops,\
		.type = WEGUWATOW_VOWTAGE,\
		.n_vowtages = _n_vowtages,\
		.wineaw_wanges = _ww,\
		.n_wineaw_wanges = AWWAY_SIZE(_ww),\
		.vsew_weg = _vw,\
		.vsew_mask = 0xff,\
		.enabwe_weg = _ew,\
		.enabwe_mask = ENABWE_MASK(ctww_bit),\
		.enabwe_vaw = ENABWE_MASK(ctww_bit),\
		.disabwe_vaw = DISABWE_VAW(ctww_bit),\
		.of_map_mode = wk8xx_weguwatow_of_map_mode,\
		.wamp_weg = _ww,\
		.wamp_mask = _wm,\
		.wamp_deway_tabwe = _wt, \
		.n_wamp_vawues = AWWAY_SIZE(_wt), \
		.ownew = THIS_MODUWE,\
	}

#define WK8XX_DESC(_id, _match, _suppwy, _min, _max, _step, _vweg,	\
	_vmask, _eweg, _emask, _etime)					\
	WK8XX_DESC_COM(_id, _match, _suppwy, _min, _max, _step, _vweg,	\
	_vmask, _eweg, _emask, 0, 0, _etime, &wk808_weg_ops)

#define WK817_DESC(_id, _match, _suppwy, _min, _max, _step, _vweg,	\
	_vmask, _eweg, _emask, _disvaw, _etime)				\
	WK8XX_DESC_COM(_id, _match, _suppwy, _min, _max, _step, _vweg,	\
	_vmask, _eweg, _emask, _emask, _disvaw, _etime, &wk817_weg_ops)

#define WKXX_DESC_SWITCH_COM(_id, _match, _suppwy, _eweg, _emask,	\
	_envaw, _disvaw, _ops)						\
	{								\
		.name		= (_match),				\
		.suppwy_name	= (_suppwy),				\
		.of_match	= of_match_ptw(_match),			\
		.weguwatows_node = of_match_ptw("weguwatows"),		\
		.type		= WEGUWATOW_VOWTAGE,			\
		.id		= (_id),				\
		.enabwe_weg	= (_eweg),				\
		.enabwe_mask	= (_emask),				\
		.enabwe_vaw     = (_envaw),				\
		.disabwe_vaw     = (_disvaw),				\
		.ownew		= THIS_MODUWE,				\
		.ops		= _ops					\
	}

#define WK817_DESC_SWITCH(_id, _match, _suppwy, _eweg, _emask,		\
	_disvaw)							\
	WKXX_DESC_SWITCH_COM(_id, _match, _suppwy, _eweg, _emask,	\
	_emask, _disvaw, &wk817_switch_ops)

#define WK8XX_DESC_SWITCH(_id, _match, _suppwy, _eweg, _emask)		\
	WKXX_DESC_SWITCH_COM(_id, _match, _suppwy, _eweg, _emask,	\
	0, 0, &wk808_switch_ops)

stwuct wk8xx_wegistew_bit {
	u8 weg;
	u8 bit;
};

#define WK8XX_WEG_BIT(_weg, _bit)					\
	{								\
		.weg = _weg,						\
		.bit = BIT(_bit),						\
	}

stwuct wk808_weguwatow_data {
	stwuct gpio_desc *dvs_gpio[2];
};

static const stwuct wineaw_wange wk808_wdo3_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(800000, 0, 13, 100000),
	WEGUWATOW_WINEAW_WANGE(2500000, 15, 15, 0),
};

#define WK809_BUCK5_SEW_CNT		(8)

static const stwuct wineaw_wange wk809_buck5_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1500000, 0, 0, 0),
	WEGUWATOW_WINEAW_WANGE(1800000, 1, 3, 200000),
	WEGUWATOW_WINEAW_WANGE(2800000, 4, 5, 200000),
	WEGUWATOW_WINEAW_WANGE(3300000, 6, 7, 300000),
};

#define WK817_BUCK1_MIN0 500000
#define WK817_BUCK1_MAX0 1500000

#define WK817_BUCK1_MIN1 1600000
#define WK817_BUCK1_MAX1 2400000

#define WK817_BUCK3_MAX1 3400000

#define WK817_BUCK1_STP0 12500
#define WK817_BUCK1_STP1 100000

#define WK817_BUCK1_SEW0 ((WK817_BUCK1_MAX0 - WK817_BUCK1_MIN0) /\
						  WK817_BUCK1_STP0)
#define WK817_BUCK1_SEW1 ((WK817_BUCK1_MAX1 - WK817_BUCK1_MIN1) /\
						  WK817_BUCK1_STP1)

#define WK817_BUCK3_SEW1 ((WK817_BUCK3_MAX1 - WK817_BUCK1_MIN1) /\
						  WK817_BUCK1_STP1)

#define WK817_BUCK1_SEW_CNT (WK817_BUCK1_SEW0 + WK817_BUCK1_SEW1 + 1)
#define WK817_BUCK3_SEW_CNT (WK817_BUCK1_SEW0 + WK817_BUCK3_SEW1 + 1)

static const stwuct wineaw_wange wk817_buck1_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(WK817_BUCK1_MIN0, 0,
			       WK817_BUCK1_SEW0, WK817_BUCK1_STP0),
	WEGUWATOW_WINEAW_WANGE(WK817_BUCK1_MIN1, WK817_BUCK1_SEW0 + 1,
			       WK817_BUCK1_SEW_CNT, WK817_BUCK1_STP1),
};

static const stwuct wineaw_wange wk817_buck3_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(WK817_BUCK1_MIN0, 0,
			       WK817_BUCK1_SEW0, WK817_BUCK1_STP0),
	WEGUWATOW_WINEAW_WANGE(WK817_BUCK1_MIN1, WK817_BUCK1_SEW0 + 1,
			       WK817_BUCK3_SEW_CNT, WK817_BUCK1_STP1),
};

static const unsigned int wk808_buck1_2_wamp_tabwe[] = {
	2000, 4000, 6000, 10000
};

/* WK817 WK809 */
static const unsigned int wk817_buck1_4_wamp_tabwe[] = {
	3000, 6300, 12500, 25000
};

static int wk806_set_mode_dcdc(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	int wid = wdev_get_id(wdev);
	int ctw_bit, weg;

	weg = WK806_POWEW_FPWM_EN0 + wid / 8;
	ctw_bit = wid % 8;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		wetuwn wegmap_update_bits(wdev->wegmap, weg,
					  PWM_MODE_MSK << ctw_bit,
					  FPWM_MODE << ctw_bit);
	case WEGUWATOW_MODE_NOWMAW:
		wetuwn wegmap_update_bits(wdev->wegmap, weg,
					  PWM_MODE_MSK << ctw_bit,
					  AUTO_PWM_MODE << ctw_bit);
	defauwt:
		dev_eww(wdev_get_dev(wdev), "mode unsuppowted: %u\n", mode);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned int wk806_get_mode_dcdc(stwuct weguwatow_dev *wdev)
{
	int wid = wdev_get_id(wdev);
	int ctw_bit, weg;
	unsigned int vaw;
	int eww;

	weg = WK806_POWEW_FPWM_EN0 + wid / 8;
	ctw_bit = wid % 8;

	eww = wegmap_wead(wdev->wegmap, weg, &vaw);
	if (eww)
		wetuwn eww;

	if ((vaw >> ctw_bit) & FPWM_MODE)
		wetuwn WEGUWATOW_MODE_FAST;
	ewse
		wetuwn WEGUWATOW_MODE_NOWMAW;
}

static const stwuct wk8xx_wegistew_bit wk806_dcdc_wate2[] = {
	WK8XX_WEG_BIT(0xEB, 0),
	WK8XX_WEG_BIT(0xEB, 1),
	WK8XX_WEG_BIT(0xEB, 2),
	WK8XX_WEG_BIT(0xEB, 3),
	WK8XX_WEG_BIT(0xEB, 4),
	WK8XX_WEG_BIT(0xEB, 5),
	WK8XX_WEG_BIT(0xEB, 6),
	WK8XX_WEG_BIT(0xEB, 7),
	WK8XX_WEG_BIT(0xEA, 0),
	WK8XX_WEG_BIT(0xEA, 1),
};

static const unsigned int wk806_wamp_deway_tabwe_dcdc[] = {
	50000, 25000, 12500, 6250, 3125, 1560, 961, 390
};

static int wk806_set_wamp_deway_dcdc(stwuct weguwatow_dev *wdev, int wamp_deway)
{
	int wid = wdev_get_id(wdev);
	int wegvaw, wamp_vawue, wet;

	wet = weguwatow_find_cwosest_biggew(wamp_deway, wdev->desc->wamp_deway_tabwe,
					    wdev->desc->n_wamp_vawues, &wamp_vawue);
	if (wet) {
		dev_wawn(wdev_get_dev(wdev),
			 "Can't set wamp-deway %u, setting %u\n", wamp_deway,
			 wdev->desc->wamp_deway_tabwe[wamp_vawue]);
	}

	wegvaw = wamp_vawue << (ffs(wdev->desc->wamp_mask) - 1);

	wet = wegmap_update_bits(wdev->wegmap, wdev->desc->wamp_weg,
				 wdev->desc->wamp_mask, wegvaw);
	if (wet)
		wetuwn wet;

	/*
	 * The above is effectivewy a copy of weguwatow_set_wamp_deway_wegmap(),
	 * but that onwy stowes the wowew 2 bits fow wk806 DCDC wamp. The MSB must
	 * be stowed in a sepawate wegistew, so this open codes the impwementation
	 * to have access to the wamp_vawue.
	 */

	wegvaw = (wamp_vawue >> 2) & 0x1 ? wk806_dcdc_wate2[wid].bit : 0;
	wetuwn wegmap_update_bits(wdev->wegmap, wk806_dcdc_wate2[wid].weg,
				  wk806_dcdc_wate2[wid].bit,
				  wegvaw);
}

static const unsigned int wk806_wamp_deway_tabwe_wdo[] = {
	100000, 50000, 25000, 12500, 6280, 3120, 1900, 780
};

static int wk806_set_suspend_vowtage_wange(stwuct weguwatow_dev *wdev, int weg_offset, int uv)
{
	int sew = weguwatow_map_vowtage_wineaw_wange(wdev, uv, uv);
	unsigned int weg;

	if (sew < 0)
		wetuwn -EINVAW;

	weg = wdev->desc->vsew_weg + weg_offset;

	wetuwn wegmap_update_bits(wdev->wegmap, weg, wdev->desc->vsew_mask, sew);
}

static int wk806_set_suspend_vowtage_wange_dcdc(stwuct weguwatow_dev *wdev, int uv)
{
	wetuwn wk806_set_suspend_vowtage_wange(wdev, WK806_DCDC_SWP_WEG_OFFSET, uv);
}

static int wk806_set_suspend_vowtage_wange_nwdo(stwuct weguwatow_dev *wdev, int uv)
{
	wetuwn wk806_set_suspend_vowtage_wange(wdev, WK806_NWDO_SWP_WEG_OFFSET, uv);
}

static int wk806_set_suspend_vowtage_wange_pwdo(stwuct weguwatow_dev *wdev, int uv)
{
	wetuwn wk806_set_suspend_vowtage_wange(wdev, WK806_PWDO_SWP_WEG_OFFSET, uv);
}

static int wk808_buck1_2_get_vowtage_sew_wegmap(stwuct weguwatow_dev *wdev)
{
	stwuct wk808_weguwatow_data *pdata = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct gpio_desc *gpio = pdata->dvs_gpio[id];
	unsigned int vaw;
	int wet;

	if (!gpio || gpiod_get_vawue(gpio) == 0)
		wetuwn weguwatow_get_vowtage_sew_wegmap(wdev);

	wet = wegmap_wead(wdev->wegmap,
			  wdev->desc->vsew_weg + WK808_DVS_WEG_OFFSET,
			  &vaw);
	if (wet != 0)
		wetuwn wet;

	vaw &= wdev->desc->vsew_mask;
	vaw >>= ffs(wdev->desc->vsew_mask) - 1;

	wetuwn vaw;
}

static int wk808_buck1_2_i2c_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					     unsigned sew)
{
	int wet, dewta_sew;
	unsigned int owd_sew, tmp, vaw, mask = wdev->desc->vsew_mask;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->vsew_weg, &vaw);
	if (wet != 0)
		wetuwn wet;

	tmp = vaw & ~mask;
	owd_sew = vaw & mask;
	owd_sew >>= ffs(mask) - 1;
	dewta_sew = sew - owd_sew;

	/*
	 * If diwectwy modify the wegistew to change the vowtage, we wiww face
	 * the wisk of ovewshoot. Put it into a muwti-step, can effectivewy
	 * avoid this pwobwem, a step is 100mv hewe.
	 */
	whiwe (dewta_sew > MAX_STEPS_ONE_TIME) {
		owd_sew += MAX_STEPS_ONE_TIME;
		vaw = owd_sew << (ffs(mask) - 1);
		vaw |= tmp;

		/*
		 * i2c is 400kHz (2.5us pew bit) and we must twansmit _at weast_
		 * 3 bytes (24 bits) pwus stawt and stop so 26 bits.  So we've
		 * got mowe than 65 us between each vowtage change and thus
		 * won't wamp fastew than ~1500 uV / us.
		 */
		wet = wegmap_wwite(wdev->wegmap, wdev->desc->vsew_weg, vaw);
		dewta_sew = sew - owd_sew;
	}

	sew <<= ffs(mask) - 1;
	vaw = tmp | sew;
	wet = wegmap_wwite(wdev->wegmap, wdev->desc->vsew_weg, vaw);

	/*
	 * When we change the vowtage wegistew diwectwy, the wamp wate is about
	 * 100000uv/us, wait 1us to make suwe the tawget vowtage to be stabwe,
	 * so we needn't wait extwa time aftew that.
	 */
	udeway(1);

	wetuwn wet;
}

static int wk808_buck1_2_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					 unsigned sew)
{
	stwuct wk808_weguwatow_data *pdata = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct gpio_desc *gpio = pdata->dvs_gpio[id];
	unsigned int weg = wdev->desc->vsew_weg;
	unsigned owd_sew;
	int wet, gpio_wevew;

	if (!gpio)
		wetuwn wk808_buck1_2_i2c_set_vowtage_sew(wdev, sew);

	gpio_wevew = gpiod_get_vawue(gpio);
	if (gpio_wevew == 0) {
		weg += WK808_DVS_WEG_OFFSET;
		wet = wegmap_wead(wdev->wegmap, wdev->desc->vsew_weg, &owd_sew);
	} ewse {
		wet = wegmap_wead(wdev->wegmap,
				  weg + WK808_DVS_WEG_OFFSET,
				  &owd_sew);
	}

	if (wet != 0)
		wetuwn wet;

	sew <<= ffs(wdev->desc->vsew_mask) - 1;
	sew |= owd_sew & ~wdev->desc->vsew_mask;

	wet = wegmap_wwite(wdev->wegmap, weg, sew);
	if (wet)
		wetuwn wet;

	gpiod_set_vawue(gpio, !gpio_wevew);

	wetuwn wet;
}

static int wk808_buck1_2_set_vowtage_time_sew(stwuct weguwatow_dev *wdev,
				       unsigned int owd_sewectow,
				       unsigned int new_sewectow)
{
	stwuct wk808_weguwatow_data *pdata = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct gpio_desc *gpio = pdata->dvs_gpio[id];

	/* if thewe is no dvs1/2 pin, we don't need wait extwa time hewe. */
	if (!gpio)
		wetuwn 0;

	wetuwn weguwatow_set_vowtage_time_sew(wdev, owd_sewectow, new_sewectow);
}

static int wk808_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uv)
{
	unsigned int weg;
	int sew = weguwatow_map_vowtage_wineaw(wdev, uv, uv);

	if (sew < 0)
		wetuwn -EINVAW;

	weg = wdev->desc->vsew_weg + WK808_SWP_WEG_OFFSET;

	wetuwn wegmap_update_bits(wdev->wegmap, weg,
				  wdev->desc->vsew_mask,
				  sew);
}

static int wk808_set_suspend_vowtage_wange(stwuct weguwatow_dev *wdev, int uv)
{
	unsigned int weg;
	int sew = weguwatow_map_vowtage_wineaw_wange(wdev, uv, uv);

	if (sew < 0)
		wetuwn -EINVAW;

	weg = wdev->desc->vsew_weg + WK808_SWP_WEG_OFFSET;

	wetuwn wegmap_update_bits(wdev->wegmap, weg,
				  wdev->desc->vsew_mask,
				  sew);
}

static int wk805_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	unsigned int weg;

	weg = wdev->desc->enabwe_weg + WK808_SWP_SET_OFF_WEG_OFFSET;

	wetuwn wegmap_update_bits(wdev->wegmap, weg,
				  wdev->desc->enabwe_mask,
				  wdev->desc->enabwe_mask);
}

static int wk805_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	unsigned int weg;

	weg = wdev->desc->enabwe_weg + WK808_SWP_SET_OFF_WEG_OFFSET;

	wetuwn wegmap_update_bits(wdev->wegmap, weg,
				  wdev->desc->enabwe_mask,
				  0);
}

static const stwuct wk8xx_wegistew_bit wk806_suspend_bits[] = {
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN0, 0),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN0, 1),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN0, 2),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN0, 3),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN0, 4),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN0, 5),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN0, 6),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN0, 7),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN1, 6),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN1, 7),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN1, 0),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN1, 1),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN1, 2),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN1, 3),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN1, 4),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN2, 1),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN2, 2),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN2, 3),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN2, 4),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN2, 5),
	WK8XX_WEG_BIT(WK806_POWEW_SWP_EN2, 0),
};

static int wk806_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	int wid = wdev_get_id(wdev);

	wetuwn wegmap_update_bits(wdev->wegmap, wk806_suspend_bits[wid].weg,
				  wk806_suspend_bits[wid].bit,
				  wk806_suspend_bits[wid].bit);
}

static int wk806_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	int wid = wdev_get_id(wdev);

	wetuwn wegmap_update_bits(wdev->wegmap, wk806_suspend_bits[wid].weg,
				  wk806_suspend_bits[wid].bit, 0);
}

static int wk808_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	unsigned int weg;

	weg = wdev->desc->enabwe_weg + WK808_SWP_SET_OFF_WEG_OFFSET;

	wetuwn wegmap_update_bits(wdev->wegmap, weg,
				  wdev->desc->enabwe_mask,
				  0);
}

static int wk808_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	unsigned int weg;

	weg = wdev->desc->enabwe_weg + WK808_SWP_SET_OFF_WEG_OFFSET;

	wetuwn wegmap_update_bits(wdev->wegmap, weg,
				  wdev->desc->enabwe_mask,
				  wdev->desc->enabwe_mask);
}

static int wk817_set_suspend_enabwe_ctww(stwuct weguwatow_dev *wdev,
					 unsigned int en)
{
	unsigned int weg;
	int id = wdev_get_id(wdev);
	unsigned int id_swp, msk, vaw;

	if (id >= WK817_ID_DCDC1 && id <= WK817_ID_DCDC4)
		id_swp = id;
	ewse if (id >= WK817_ID_WDO1 && id <= WK817_ID_WDO8)
		id_swp = 8 + (id - WK817_ID_WDO1);
	ewse if (id >= WK817_ID_WDO9 && id <= WK809_ID_SW2)
		id_swp = 4 + (id - WK817_ID_WDO9);
	ewse
		wetuwn -EINVAW;

	weg = WK817_POWEW_SWP_EN_WEG(id_swp / 8);

	msk = BIT(id_swp % 8);
	if (en)
		vaw = msk;
	ewse
		vaw = 0;

	wetuwn wegmap_update_bits(wdev->wegmap, weg, msk, vaw);
}

static int wk817_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	wetuwn wk817_set_suspend_enabwe_ctww(wdev, 1);
}

static int wk817_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	wetuwn wk817_set_suspend_enabwe_ctww(wdev, 0);
}

static int wk8xx_set_suspend_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	unsigned int weg;

	weg = wdev->desc->vsew_weg + WK808_SWP_WEG_OFFSET;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		wetuwn wegmap_update_bits(wdev->wegmap, weg,
					  PWM_MODE_MSK, FPWM_MODE);
	case WEGUWATOW_MODE_NOWMAW:
		wetuwn wegmap_update_bits(wdev->wegmap, weg,
					  PWM_MODE_MSK, AUTO_PWM_MODE);
	defauwt:
		dev_eww(&wdev->dev, "do not suppowt this mode\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wk8xx_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->vsew_weg,
					  PWM_MODE_MSK, FPWM_MODE);
	case WEGUWATOW_MODE_NOWMAW:
		wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->vsew_weg,
					  PWM_MODE_MSK, AUTO_PWM_MODE);
	defauwt:
		dev_eww(&wdev->dev, "do not suppowt this mode\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned int wk8xx_get_mode(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int eww;

	eww = wegmap_wead(wdev->wegmap, wdev->desc->vsew_weg, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw & FPWM_MODE)
		wetuwn WEGUWATOW_MODE_FAST;
	ewse
		wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int wk8xx_is_enabwed_wmsk_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->enabwe_weg, &vaw);
	if (wet != 0)
		wetuwn wet;

	/* add wwite mask bit */
	vaw |= (wdev->desc->enabwe_mask & 0xf0);
	vaw &= wdev->desc->enabwe_mask;

	if (wdev->desc->enabwe_is_invewted) {
		if (wdev->desc->enabwe_vaw)
			wetuwn vaw != wdev->desc->enabwe_vaw;
		wetuwn (vaw == 0);
	}
	if (wdev->desc->enabwe_vaw)
		wetuwn vaw == wdev->desc->enabwe_vaw;
	wetuwn vaw != 0;
}

static unsigned int wk8xx_weguwatow_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case 1:
		wetuwn WEGUWATOW_MODE_FAST;
	case 2:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static const stwuct weguwatow_ops wk805_weg_ops = {
	.wist_vowtage           = weguwatow_wist_vowtage_wineaw,
	.map_vowtage            = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew        = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew        = weguwatow_set_vowtage_sew_wegmap,
	.enabwe                 = weguwatow_enabwe_wegmap,
	.disabwe                = weguwatow_disabwe_wegmap,
	.is_enabwed             = weguwatow_is_enabwed_wegmap,
	.set_suspend_vowtage    = wk808_set_suspend_vowtage,
	.set_suspend_enabwe     = wk805_set_suspend_enabwe,
	.set_suspend_disabwe    = wk805_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk805_switch_ops = {
	.enabwe                 = weguwatow_enabwe_wegmap,
	.disabwe                = weguwatow_disabwe_wegmap,
	.is_enabwed             = weguwatow_is_enabwed_wegmap,
	.set_suspend_enabwe     = wk805_set_suspend_enabwe,
	.set_suspend_disabwe    = wk805_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk806_ops_dcdc = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew        = weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_mode		= wk806_set_mode_dcdc,
	.get_mode		= wk806_get_mode_dcdc,

	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= wk8xx_is_enabwed_wmsk_wegmap,

	.set_suspend_mode	= wk806_set_mode_dcdc,
	.set_wamp_deway		= wk806_set_wamp_deway_dcdc,

	.set_suspend_vowtage	= wk806_set_suspend_vowtage_wange_dcdc,
	.set_suspend_enabwe	= wk806_set_suspend_enabwe,
	.set_suspend_disabwe	= wk806_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk806_ops_nwdo = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew        = weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,

	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,

	.set_wamp_deway		= weguwatow_set_wamp_deway_wegmap,

	.set_suspend_vowtage	= wk806_set_suspend_vowtage_wange_nwdo,
	.set_suspend_enabwe	= wk806_set_suspend_enabwe,
	.set_suspend_disabwe	= wk806_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk806_ops_pwdo = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,

	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew        = weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,

	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,

	.set_wamp_deway		= weguwatow_set_wamp_deway_wegmap,

	.set_suspend_vowtage	= wk806_set_suspend_vowtage_wange_pwdo,
	.set_suspend_enabwe	= wk806_set_suspend_enabwe,
	.set_suspend_disabwe	= wk806_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk808_buck1_2_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= wk808_buck1_2_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= wk808_buck1_2_set_vowtage_sew,
	.set_vowtage_time_sew	= wk808_buck1_2_set_vowtage_time_sew,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_wamp_deway		= weguwatow_set_wamp_deway_wegmap,
	.set_suspend_vowtage	= wk808_set_suspend_vowtage,
	.set_suspend_enabwe	= wk808_set_suspend_enabwe,
	.set_suspend_disabwe	= wk808_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk808_weg_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_suspend_vowtage	= wk808_set_suspend_vowtage,
	.set_suspend_enabwe	= wk808_set_suspend_enabwe,
	.set_suspend_disabwe	= wk808_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk808_weg_ops_wanges = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_suspend_vowtage	= wk808_set_suspend_vowtage_wange,
	.set_suspend_enabwe	= wk808_set_suspend_enabwe,
	.set_suspend_disabwe	= wk808_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk808_switch_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_suspend_enabwe	= wk808_set_suspend_enabwe,
	.set_suspend_disabwe	= wk808_set_suspend_disabwe,
};

static const stwuct wineaw_wange wk805_buck_1_2_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(712500, 0, 59, 12500),
	WEGUWATOW_WINEAW_WANGE(1800000, 60, 62, 200000),
	WEGUWATOW_WINEAW_WANGE(2300000, 63, 63, 0),
};

static const stwuct weguwatow_ops wk809_buck5_ops_wange = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= wk8xx_is_enabwed_wmsk_wegmap,
	.set_suspend_vowtage	= wk808_set_suspend_vowtage_wange,
	.set_suspend_enabwe	= wk817_set_suspend_enabwe,
	.set_suspend_disabwe	= wk817_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk817_weg_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= wk8xx_is_enabwed_wmsk_wegmap,
	.set_suspend_vowtage	= wk808_set_suspend_vowtage,
	.set_suspend_enabwe	= wk817_set_suspend_enabwe,
	.set_suspend_disabwe	= wk817_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk817_boost_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= wk8xx_is_enabwed_wmsk_wegmap,
	.set_suspend_enabwe	= wk817_set_suspend_enabwe,
	.set_suspend_disabwe	= wk817_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk817_buck_ops_wange = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= wk8xx_is_enabwed_wmsk_wegmap,
	.set_mode		= wk8xx_set_mode,
	.get_mode		= wk8xx_get_mode,
	.set_suspend_mode	= wk8xx_set_suspend_mode,
	.set_wamp_deway		= weguwatow_set_wamp_deway_wegmap,
	.set_suspend_vowtage	= wk808_set_suspend_vowtage_wange,
	.set_suspend_enabwe	= wk817_set_suspend_enabwe,
	.set_suspend_disabwe	= wk817_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wk817_switch_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= wk8xx_is_enabwed_wmsk_wegmap,
	.set_suspend_enabwe	= wk817_set_suspend_enabwe,
	.set_suspend_disabwe	= wk817_set_suspend_disabwe,
};

static const stwuct weguwatow_desc wk805_weg[] = {
	{
		.name = "DCDC_WEG1",
		.suppwy_name = "vcc1",
		.of_match = of_match_ptw("DCDC_WEG1"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK805_ID_DCDC1,
		.ops = &wk808_weg_ops_wanges,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = 64,
		.wineaw_wanges = wk805_buck_1_2_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk805_buck_1_2_vowtage_wanges),
		.vsew_weg = WK805_BUCK1_ON_VSEW_WEG,
		.vsew_mask = WK818_BUCK_VSEW_MASK,
		.enabwe_weg = WK805_DCDC_EN_WEG,
		.enabwe_mask = BIT(0),
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG2",
		.suppwy_name = "vcc2",
		.of_match = of_match_ptw("DCDC_WEG2"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK805_ID_DCDC2,
		.ops = &wk808_weg_ops_wanges,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = 64,
		.wineaw_wanges = wk805_buck_1_2_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk805_buck_1_2_vowtage_wanges),
		.vsew_weg = WK805_BUCK2_ON_VSEW_WEG,
		.vsew_mask = WK818_BUCK_VSEW_MASK,
		.enabwe_weg = WK805_DCDC_EN_WEG,
		.enabwe_mask = BIT(1),
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG3",
		.suppwy_name = "vcc3",
		.of_match = of_match_ptw("DCDC_WEG3"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK805_ID_DCDC3,
		.ops = &wk805_switch_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = 1,
		.enabwe_weg = WK805_DCDC_EN_WEG,
		.enabwe_mask = BIT(2),
		.ownew = THIS_MODUWE,
	},

	WK805_DESC(WK805_ID_DCDC4, "DCDC_WEG4", "vcc4", 800, 3400, 100,
		WK805_BUCK4_ON_VSEW_WEG, WK818_BUCK4_VSEW_MASK,
		WK805_DCDC_EN_WEG, BIT(3), 0),

	WK805_DESC(WK805_ID_WDO1, "WDO_WEG1", "vcc5", 800, 3400, 100,
		WK805_WDO1_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK805_WDO_EN_WEG,
		BIT(0), 400),
	WK805_DESC(WK805_ID_WDO2, "WDO_WEG2", "vcc5", 800, 3400, 100,
		WK805_WDO2_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK805_WDO_EN_WEG,
		BIT(1), 400),
	WK805_DESC(WK805_ID_WDO3, "WDO_WEG3", "vcc6", 800, 3400, 100,
		WK805_WDO3_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK805_WDO_EN_WEG,
		BIT(2), 400),
};

static const stwuct wineaw_wange wk806_buck_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(500000, 0, 160, 6250), /* 500mV ~ 1500mV */
	WEGUWATOW_WINEAW_WANGE(1500000, 161, 237, 25000), /* 1500mV ~ 3400mV */
	WEGUWATOW_WINEAW_WANGE(3400000, 238, 255, 0),
};

static const stwuct wineaw_wange wk806_wdo_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(500000, 0, 232, 12500), /* 500mV ~ 3400mV */
	WEGUWATOW_WINEAW_WANGE(3400000, 233, 255, 0), /* 500mV ~ 3400mV */
};

static const stwuct weguwatow_desc wk806_weg[] = {
	WK806_WEGUWATOW("dcdc-weg1", "vcc1", WK806_ID_DCDC1, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK1_ON_VSEW,
			WK806_POWEW_EN0, wk806_buck_vowtage_wanges, 0,
			WK806_BUCK1_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),
	WK806_WEGUWATOW("dcdc-weg2", "vcc2", WK806_ID_DCDC2, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK2_ON_VSEW,
			WK806_POWEW_EN0, wk806_buck_vowtage_wanges, 1,
			WK806_BUCK2_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),
	WK806_WEGUWATOW("dcdc-weg3", "vcc3", WK806_ID_DCDC3, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK3_ON_VSEW,
			WK806_POWEW_EN0, wk806_buck_vowtage_wanges, 2,
			WK806_BUCK3_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),
	WK806_WEGUWATOW("dcdc-weg4", "vcc4", WK806_ID_DCDC4, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK4_ON_VSEW,
			WK806_POWEW_EN0, wk806_buck_vowtage_wanges, 3,
			WK806_BUCK4_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),

	WK806_WEGUWATOW("dcdc-weg5", "vcc5", WK806_ID_DCDC5, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK5_ON_VSEW,
			WK806_POWEW_EN1, wk806_buck_vowtage_wanges, 0,
			WK806_BUCK5_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),
	WK806_WEGUWATOW("dcdc-weg6", "vcc6", WK806_ID_DCDC6, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK6_ON_VSEW,
			WK806_POWEW_EN1, wk806_buck_vowtage_wanges, 1,
			WK806_BUCK6_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),
	WK806_WEGUWATOW("dcdc-weg7", "vcc7", WK806_ID_DCDC7, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK7_ON_VSEW,
			WK806_POWEW_EN1, wk806_buck_vowtage_wanges, 2,
			WK806_BUCK7_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),
	WK806_WEGUWATOW("dcdc-weg8", "vcc8", WK806_ID_DCDC8, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK8_ON_VSEW,
			WK806_POWEW_EN1, wk806_buck_vowtage_wanges, 3,
			WK806_BUCK8_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),

	WK806_WEGUWATOW("dcdc-weg9", "vcc9", WK806_ID_DCDC9, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK9_ON_VSEW,
			WK806_POWEW_EN2, wk806_buck_vowtage_wanges, 0,
			WK806_BUCK9_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),
	WK806_WEGUWATOW("dcdc-weg10", "vcc10", WK806_ID_DCDC10, wk806_ops_dcdc,
			WK806_BUCK_SEW_CNT, WK806_BUCK10_ON_VSEW,
			WK806_POWEW_EN2, wk806_buck_vowtage_wanges, 1,
			WK806_BUCK10_CONFIG, 0xc0, wk806_wamp_deway_tabwe_dcdc),

	WK806_WEGUWATOW("nwdo-weg1", "vcc13", WK806_ID_NWDO1, wk806_ops_nwdo,
			WK806_WDO_SEW_CNT, WK806_NWDO1_ON_VSEW,
			WK806_POWEW_EN3, wk806_wdo_vowtage_wanges, 0,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),
	WK806_WEGUWATOW("nwdo-weg2", "vcc13", WK806_ID_NWDO2, wk806_ops_nwdo,
			WK806_WDO_SEW_CNT, WK806_NWDO2_ON_VSEW,
			WK806_POWEW_EN3, wk806_wdo_vowtage_wanges, 1,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),
	WK806_WEGUWATOW("nwdo-weg3", "vcc13", WK806_ID_NWDO3, wk806_ops_nwdo,
			WK806_WDO_SEW_CNT, WK806_NWDO3_ON_VSEW,
			WK806_POWEW_EN3, wk806_wdo_vowtage_wanges, 2,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),
	WK806_WEGUWATOW("nwdo-weg4", "vcc14", WK806_ID_NWDO4, wk806_ops_nwdo,
			WK806_WDO_SEW_CNT, WK806_NWDO4_ON_VSEW,
			WK806_POWEW_EN3, wk806_wdo_vowtage_wanges, 3,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),

	WK806_WEGUWATOW("nwdo-weg5", "vcc14", WK806_ID_NWDO5, wk806_ops_nwdo,
			WK806_WDO_SEW_CNT, WK806_NWDO5_ON_VSEW,
			WK806_POWEW_EN5, wk806_wdo_vowtage_wanges, 2,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),

	WK806_WEGUWATOW("pwdo-weg1", "vcc11", WK806_ID_PWDO1, wk806_ops_pwdo,
			WK806_WDO_SEW_CNT, WK806_PWDO1_ON_VSEW,
			WK806_POWEW_EN4, wk806_wdo_vowtage_wanges, 1,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),
	WK806_WEGUWATOW("pwdo-weg2", "vcc11", WK806_ID_PWDO2, wk806_ops_pwdo,
			WK806_WDO_SEW_CNT, WK806_PWDO2_ON_VSEW,
			WK806_POWEW_EN4, wk806_wdo_vowtage_wanges, 2,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),
	WK806_WEGUWATOW("pwdo-weg3", "vcc11", WK806_ID_PWDO3, wk806_ops_pwdo,
			WK806_WDO_SEW_CNT, WK806_PWDO3_ON_VSEW,
			WK806_POWEW_EN4, wk806_wdo_vowtage_wanges, 3,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),

	WK806_WEGUWATOW("pwdo-weg4", "vcc12", WK806_ID_PWDO4, wk806_ops_pwdo,
			WK806_WDO_SEW_CNT, WK806_PWDO4_ON_VSEW,
			WK806_POWEW_EN5, wk806_wdo_vowtage_wanges, 0,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),
	WK806_WEGUWATOW("pwdo-weg5", "vcc12", WK806_ID_PWDO5, wk806_ops_pwdo,
			WK806_WDO_SEW_CNT, WK806_PWDO5_ON_VSEW,
			WK806_POWEW_EN5, wk806_wdo_vowtage_wanges, 1,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),

	WK806_WEGUWATOW("pwdo-weg6", "vcca", WK806_ID_PWDO6, wk806_ops_pwdo,
			WK806_WDO_SEW_CNT, WK806_PWDO6_ON_VSEW,
			WK806_POWEW_EN4, wk806_wdo_vowtage_wanges, 0,
			0xEA, 0x38, wk806_wamp_deway_tabwe_wdo),
};


static const stwuct weguwatow_desc wk808_weg[] = {
	{
		.name = "DCDC_WEG1",
		.suppwy_name = "vcc1",
		.of_match = of_match_ptw("DCDC_WEG1"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK808_ID_DCDC1,
		.ops = &wk808_buck1_2_ops,
		.type = WEGUWATOW_VOWTAGE,
		.min_uV = 712500,
		.uV_step = 12500,
		.n_vowtages = 64,
		.vsew_weg = WK808_BUCK1_ON_VSEW_WEG,
		.vsew_mask = WK808_BUCK_VSEW_MASK,
		.enabwe_weg = WK808_DCDC_EN_WEG,
		.enabwe_mask = BIT(0),
		.wamp_weg = WK808_BUCK1_CONFIG_WEG,
		.wamp_mask = WK808_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk808_buck1_2_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk808_buck1_2_wamp_tabwe),
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG2",
		.suppwy_name = "vcc2",
		.of_match = of_match_ptw("DCDC_WEG2"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK808_ID_DCDC2,
		.ops = &wk808_buck1_2_ops,
		.type = WEGUWATOW_VOWTAGE,
		.min_uV = 712500,
		.uV_step = 12500,
		.n_vowtages = 64,
		.vsew_weg = WK808_BUCK2_ON_VSEW_WEG,
		.vsew_mask = WK808_BUCK_VSEW_MASK,
		.enabwe_weg = WK808_DCDC_EN_WEG,
		.enabwe_mask = BIT(1),
		.wamp_weg = WK808_BUCK2_CONFIG_WEG,
		.wamp_mask = WK808_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk808_buck1_2_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk808_buck1_2_wamp_tabwe),
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG3",
		.suppwy_name = "vcc3",
		.of_match = of_match_ptw("DCDC_WEG3"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK808_ID_DCDC3,
		.ops = &wk808_switch_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = 1,
		.enabwe_weg = WK808_DCDC_EN_WEG,
		.enabwe_mask = BIT(2),
		.ownew = THIS_MODUWE,
	},
	WK8XX_DESC(WK808_ID_DCDC4, "DCDC_WEG4", "vcc4", 1800, 3300, 100,
		WK808_BUCK4_ON_VSEW_WEG, WK808_BUCK4_VSEW_MASK,
		WK808_DCDC_EN_WEG, BIT(3), 0),
	WK8XX_DESC(WK808_ID_WDO1, "WDO_WEG1", "vcc6", 1800, 3400, 100,
		WK808_WDO1_ON_VSEW_WEG, WK808_WDO_VSEW_MASK, WK808_WDO_EN_WEG,
		BIT(0), 400),
	WK8XX_DESC(WK808_ID_WDO2, "WDO_WEG2", "vcc6", 1800, 3400, 100,
		WK808_WDO2_ON_VSEW_WEG, WK808_WDO_VSEW_MASK, WK808_WDO_EN_WEG,
		BIT(1), 400),
	{
		.name = "WDO_WEG3",
		.suppwy_name = "vcc7",
		.of_match = of_match_ptw("WDO_WEG3"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK808_ID_WDO3,
		.ops = &wk808_weg_ops_wanges,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = 16,
		.wineaw_wanges = wk808_wdo3_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk808_wdo3_vowtage_wanges),
		.vsew_weg = WK808_WDO3_ON_VSEW_WEG,
		.vsew_mask = WK808_BUCK4_VSEW_MASK,
		.enabwe_weg = WK808_WDO_EN_WEG,
		.enabwe_mask = BIT(2),
		.enabwe_time = 400,
		.ownew = THIS_MODUWE,
	},
	WK8XX_DESC(WK808_ID_WDO4, "WDO_WEG4", "vcc9", 1800, 3400, 100,
		WK808_WDO4_ON_VSEW_WEG, WK808_WDO_VSEW_MASK, WK808_WDO_EN_WEG,
		BIT(3), 400),
	WK8XX_DESC(WK808_ID_WDO5, "WDO_WEG5", "vcc9", 1800, 3400, 100,
		WK808_WDO5_ON_VSEW_WEG, WK808_WDO_VSEW_MASK, WK808_WDO_EN_WEG,
		BIT(4), 400),
	WK8XX_DESC(WK808_ID_WDO6, "WDO_WEG6", "vcc10", 800, 2500, 100,
		WK808_WDO6_ON_VSEW_WEG, WK808_WDO_VSEW_MASK, WK808_WDO_EN_WEG,
		BIT(5), 400),
	WK8XX_DESC(WK808_ID_WDO7, "WDO_WEG7", "vcc7", 800, 2500, 100,
		WK808_WDO7_ON_VSEW_WEG, WK808_WDO_VSEW_MASK, WK808_WDO_EN_WEG,
		BIT(6), 400),
	WK8XX_DESC(WK808_ID_WDO8, "WDO_WEG8", "vcc11", 1800, 3400, 100,
		WK808_WDO8_ON_VSEW_WEG, WK808_WDO_VSEW_MASK, WK808_WDO_EN_WEG,
		BIT(7), 400),
	WK8XX_DESC_SWITCH(WK808_ID_SWITCH1, "SWITCH_WEG1", "vcc8",
		WK808_DCDC_EN_WEG, BIT(5)),
	WK8XX_DESC_SWITCH(WK808_ID_SWITCH2, "SWITCH_WEG2", "vcc12",
		WK808_DCDC_EN_WEG, BIT(6)),
};

static const stwuct weguwatow_desc wk809_weg[] = {
	{
		.name = "DCDC_WEG1",
		.suppwy_name = "vcc1",
		.of_match = of_match_ptw("DCDC_WEG1"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK817_ID_DCDC1,
		.ops = &wk817_buck_ops_wange,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WK817_BUCK1_SEW_CNT + 1,
		.wineaw_wanges = wk817_buck1_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk817_buck1_vowtage_wanges),
		.vsew_weg = WK817_BUCK1_ON_VSEW_WEG,
		.vsew_mask = WK817_BUCK_VSEW_MASK,
		.enabwe_weg = WK817_POWEW_EN_WEG(0),
		.enabwe_mask = ENABWE_MASK(WK817_ID_DCDC1),
		.enabwe_vaw = ENABWE_MASK(WK817_ID_DCDC1),
		.disabwe_vaw = DISABWE_VAW(WK817_ID_DCDC1),
		.wamp_weg = WK817_BUCK_CONFIG_WEG(WK817_ID_DCDC1),
		.wamp_mask = WK817_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk817_buck1_4_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk817_buck1_4_wamp_tabwe),
		.of_map_mode = wk8xx_weguwatow_of_map_mode,
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG2",
		.suppwy_name = "vcc2",
		.of_match = of_match_ptw("DCDC_WEG2"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK817_ID_DCDC2,
		.ops = &wk817_buck_ops_wange,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WK817_BUCK1_SEW_CNT + 1,
		.wineaw_wanges = wk817_buck1_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk817_buck1_vowtage_wanges),
		.vsew_weg = WK817_BUCK2_ON_VSEW_WEG,
		.vsew_mask = WK817_BUCK_VSEW_MASK,
		.enabwe_weg = WK817_POWEW_EN_WEG(0),
		.enabwe_mask = ENABWE_MASK(WK817_ID_DCDC2),
		.enabwe_vaw = ENABWE_MASK(WK817_ID_DCDC2),
		.disabwe_vaw = DISABWE_VAW(WK817_ID_DCDC2),
		.wamp_weg = WK817_BUCK_CONFIG_WEG(WK817_ID_DCDC2),
		.wamp_mask = WK817_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk817_buck1_4_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk817_buck1_4_wamp_tabwe),
		.of_map_mode = wk8xx_weguwatow_of_map_mode,
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG3",
		.suppwy_name = "vcc3",
		.of_match = of_match_ptw("DCDC_WEG3"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK817_ID_DCDC3,
		.ops = &wk817_buck_ops_wange,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WK817_BUCK1_SEW_CNT + 1,
		.wineaw_wanges = wk817_buck1_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk817_buck1_vowtage_wanges),
		.vsew_weg = WK817_BUCK3_ON_VSEW_WEG,
		.vsew_mask = WK817_BUCK_VSEW_MASK,
		.enabwe_weg = WK817_POWEW_EN_WEG(0),
		.enabwe_mask = ENABWE_MASK(WK817_ID_DCDC3),
		.enabwe_vaw = ENABWE_MASK(WK817_ID_DCDC3),
		.disabwe_vaw = DISABWE_VAW(WK817_ID_DCDC3),
		.wamp_weg = WK817_BUCK_CONFIG_WEG(WK817_ID_DCDC3),
		.wamp_mask = WK817_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk817_buck1_4_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk817_buck1_4_wamp_tabwe),
		.of_map_mode = wk8xx_weguwatow_of_map_mode,
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG4",
		.suppwy_name = "vcc4",
		.of_match = of_match_ptw("DCDC_WEG4"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK817_ID_DCDC4,
		.ops = &wk817_buck_ops_wange,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WK817_BUCK3_SEW_CNT + 1,
		.wineaw_wanges = wk817_buck3_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk817_buck3_vowtage_wanges),
		.vsew_weg = WK817_BUCK4_ON_VSEW_WEG,
		.vsew_mask = WK817_BUCK_VSEW_MASK,
		.enabwe_weg = WK817_POWEW_EN_WEG(0),
		.enabwe_mask = ENABWE_MASK(WK817_ID_DCDC4),
		.enabwe_vaw = ENABWE_MASK(WK817_ID_DCDC4),
		.disabwe_vaw = DISABWE_VAW(WK817_ID_DCDC4),
		.wamp_weg = WK817_BUCK_CONFIG_WEG(WK817_ID_DCDC4),
		.wamp_mask = WK817_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk817_buck1_4_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk817_buck1_4_wamp_tabwe),
		.of_map_mode = wk8xx_weguwatow_of_map_mode,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC_WEG5",
		.suppwy_name = "vcc9",
		.of_match = of_match_ptw("DCDC_WEG5"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK809_ID_DCDC5,
		.ops = &wk809_buck5_ops_wange,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WK809_BUCK5_SEW_CNT,
		.wineaw_wanges = wk809_buck5_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk809_buck5_vowtage_wanges),
		.vsew_weg = WK809_BUCK5_CONFIG(0),
		.vsew_mask = WK809_BUCK5_VSEW_MASK,
		.enabwe_weg = WK817_POWEW_EN_WEG(3),
		.enabwe_mask = ENABWE_MASK(1),
		.enabwe_vaw = ENABWE_MASK(1),
		.disabwe_vaw = DISABWE_VAW(1),
		.of_map_mode = wk8xx_weguwatow_of_map_mode,
		.ownew = THIS_MODUWE,
	},
	WK817_DESC(WK817_ID_WDO1, "WDO_WEG1", "vcc5", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(0), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(1), ENABWE_MASK(0),
		   DISABWE_VAW(0), 400),
	WK817_DESC(WK817_ID_WDO2, "WDO_WEG2", "vcc5", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(1), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(1), ENABWE_MASK(1),
		   DISABWE_VAW(1), 400),
	WK817_DESC(WK817_ID_WDO3, "WDO_WEG3", "vcc5", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(2), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(1), ENABWE_MASK(2),
		   DISABWE_VAW(2), 400),
	WK817_DESC(WK817_ID_WDO4, "WDO_WEG4", "vcc6", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(3), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(1), ENABWE_MASK(3),
		   DISABWE_VAW(3), 400),
	WK817_DESC(WK817_ID_WDO5, "WDO_WEG5", "vcc6", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(4), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(2), ENABWE_MASK(0),
		   DISABWE_VAW(0), 400),
	WK817_DESC(WK817_ID_WDO6, "WDO_WEG6", "vcc6", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(5), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(2), ENABWE_MASK(1),
		   DISABWE_VAW(1), 400),
	WK817_DESC(WK817_ID_WDO7, "WDO_WEG7", "vcc7", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(6), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(2), ENABWE_MASK(2),
		   DISABWE_VAW(2), 400),
	WK817_DESC(WK817_ID_WDO8, "WDO_WEG8", "vcc7", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(7), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(2), ENABWE_MASK(3),
		   DISABWE_VAW(3), 400),
	WK817_DESC(WK817_ID_WDO9, "WDO_WEG9", "vcc7", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(8), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(3), ENABWE_MASK(0),
		   DISABWE_VAW(0), 400),
	WK817_DESC_SWITCH(WK809_ID_SW1, "SWITCH_WEG1", "vcc9",
			  WK817_POWEW_EN_WEG(3), ENABWE_MASK(2),
			  DISABWE_VAW(2)),
	WK817_DESC_SWITCH(WK809_ID_SW2, "SWITCH_WEG2", "vcc8",
			  WK817_POWEW_EN_WEG(3), ENABWE_MASK(3),
			  DISABWE_VAW(3)),
};

static const stwuct weguwatow_desc wk817_weg[] = {
	{
		.name = "DCDC_WEG1",
		.suppwy_name = "vcc1",
		.of_match = of_match_ptw("DCDC_WEG1"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK817_ID_DCDC1,
		.ops = &wk817_buck_ops_wange,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WK817_BUCK1_SEW_CNT + 1,
		.wineaw_wanges = wk817_buck1_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk817_buck1_vowtage_wanges),
		.vsew_weg = WK817_BUCK1_ON_VSEW_WEG,
		.vsew_mask = WK817_BUCK_VSEW_MASK,
		.enabwe_weg = WK817_POWEW_EN_WEG(0),
		.enabwe_mask = ENABWE_MASK(WK817_ID_DCDC1),
		.enabwe_vaw = ENABWE_MASK(WK817_ID_DCDC1),
		.disabwe_vaw = DISABWE_VAW(WK817_ID_DCDC1),
		.wamp_weg = WK817_BUCK_CONFIG_WEG(WK817_ID_DCDC1),
		.wamp_mask = WK817_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk817_buck1_4_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk817_buck1_4_wamp_tabwe),
		.of_map_mode = wk8xx_weguwatow_of_map_mode,
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG2",
		.suppwy_name = "vcc2",
		.of_match = of_match_ptw("DCDC_WEG2"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK817_ID_DCDC2,
		.ops = &wk817_buck_ops_wange,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WK817_BUCK1_SEW_CNT + 1,
		.wineaw_wanges = wk817_buck1_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk817_buck1_vowtage_wanges),
		.vsew_weg = WK817_BUCK2_ON_VSEW_WEG,
		.vsew_mask = WK817_BUCK_VSEW_MASK,
		.enabwe_weg = WK817_POWEW_EN_WEG(0),
		.enabwe_mask = ENABWE_MASK(WK817_ID_DCDC2),
		.enabwe_vaw = ENABWE_MASK(WK817_ID_DCDC2),
		.disabwe_vaw = DISABWE_VAW(WK817_ID_DCDC2),
		.wamp_weg = WK817_BUCK_CONFIG_WEG(WK817_ID_DCDC2),
		.wamp_mask = WK817_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk817_buck1_4_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk817_buck1_4_wamp_tabwe),
		.of_map_mode = wk8xx_weguwatow_of_map_mode,
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG3",
		.suppwy_name = "vcc3",
		.of_match = of_match_ptw("DCDC_WEG3"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK817_ID_DCDC3,
		.ops = &wk817_buck_ops_wange,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WK817_BUCK1_SEW_CNT + 1,
		.wineaw_wanges = wk817_buck1_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk817_buck1_vowtage_wanges),
		.vsew_weg = WK817_BUCK3_ON_VSEW_WEG,
		.vsew_mask = WK817_BUCK_VSEW_MASK,
		.enabwe_weg = WK817_POWEW_EN_WEG(0),
		.enabwe_mask = ENABWE_MASK(WK817_ID_DCDC3),
		.enabwe_vaw = ENABWE_MASK(WK817_ID_DCDC3),
		.disabwe_vaw = DISABWE_VAW(WK817_ID_DCDC3),
		.wamp_weg = WK817_BUCK_CONFIG_WEG(WK817_ID_DCDC3),
		.wamp_mask = WK817_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk817_buck1_4_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk817_buck1_4_wamp_tabwe),
		.of_map_mode = wk8xx_weguwatow_of_map_mode,
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG4",
		.suppwy_name = "vcc4",
		.of_match = of_match_ptw("DCDC_WEG4"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK817_ID_DCDC4,
		.ops = &wk817_buck_ops_wange,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WK817_BUCK3_SEW_CNT + 1,
		.wineaw_wanges = wk817_buck3_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk817_buck3_vowtage_wanges),
		.vsew_weg = WK817_BUCK4_ON_VSEW_WEG,
		.vsew_mask = WK817_BUCK_VSEW_MASK,
		.enabwe_weg = WK817_POWEW_EN_WEG(0),
		.enabwe_mask = ENABWE_MASK(WK817_ID_DCDC4),
		.enabwe_vaw = ENABWE_MASK(WK817_ID_DCDC4),
		.disabwe_vaw = DISABWE_VAW(WK817_ID_DCDC4),
		.wamp_weg = WK817_BUCK_CONFIG_WEG(WK817_ID_DCDC4),
		.wamp_mask = WK817_WAMP_WATE_MASK,
		.wamp_deway_tabwe = wk817_buck1_4_wamp_tabwe,
		.n_wamp_vawues = AWWAY_SIZE(wk817_buck1_4_wamp_tabwe),
		.of_map_mode = wk8xx_weguwatow_of_map_mode,
		.ownew = THIS_MODUWE,
	},
	WK817_DESC(WK817_ID_WDO1, "WDO_WEG1", "vcc5", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(0), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(1), ENABWE_MASK(0),
		   DISABWE_VAW(0), 400),
	WK817_DESC(WK817_ID_WDO2, "WDO_WEG2", "vcc5", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(1), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(1), ENABWE_MASK(1),
		   DISABWE_VAW(1), 400),
	WK817_DESC(WK817_ID_WDO3, "WDO_WEG3", "vcc5", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(2), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(1), ENABWE_MASK(2),
		   DISABWE_VAW(2), 400),
	WK817_DESC(WK817_ID_WDO4, "WDO_WEG4", "vcc6", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(3), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(1), ENABWE_MASK(3),
		   DISABWE_VAW(3), 400),
	WK817_DESC(WK817_ID_WDO5, "WDO_WEG5", "vcc6", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(4), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(2), ENABWE_MASK(0),
		   DISABWE_VAW(0), 400),
	WK817_DESC(WK817_ID_WDO6, "WDO_WEG6", "vcc6", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(5), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(2), ENABWE_MASK(1),
		   DISABWE_VAW(1), 400),
	WK817_DESC(WK817_ID_WDO7, "WDO_WEG7", "vcc7", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(6), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(2), ENABWE_MASK(2),
		   DISABWE_VAW(2), 400),
	WK817_DESC(WK817_ID_WDO8, "WDO_WEG8", "vcc7", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(7), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(2), ENABWE_MASK(3),
		   DISABWE_VAW(3), 400),
	WK817_DESC(WK817_ID_WDO9, "WDO_WEG9", "vcc7", 600, 3400, 25,
		   WK817_WDO_ON_VSEW_WEG(8), WK817_WDO_VSEW_MASK,
		   WK817_POWEW_EN_WEG(3), ENABWE_MASK(0),
		   DISABWE_VAW(0), 400),
	WK817_BOOST_DESC(WK817_ID_BOOST, "BOOST", "vcc8", 4700, 5400, 100,
			 WK817_BOOST_OTG_CFG, WK817_BOOST_VSEW_MASK,
			 WK817_POWEW_EN_WEG(3), ENABWE_MASK(1), ENABWE_MASK(1),
		   DISABWE_VAW(1), 400, 3500 - 5400),
	WK817_DESC_SWITCH(WK817_ID_BOOST_OTG_SW, "OTG_SWITCH", "vcc9",
			  WK817_POWEW_EN_WEG(3), ENABWE_MASK(2),
			  DISABWE_VAW(2)),
};

static const stwuct weguwatow_desc wk818_weg[] = {
	{
		.name = "DCDC_WEG1",
		.suppwy_name = "vcc1",
		.of_match = of_match_ptw("DCDC_WEG1"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK818_ID_DCDC1,
		.ops = &wk808_weg_ops,
		.type = WEGUWATOW_VOWTAGE,
		.min_uV = 712500,
		.uV_step = 12500,
		.n_vowtages = 64,
		.vsew_weg = WK818_BUCK1_ON_VSEW_WEG,
		.vsew_mask = WK818_BUCK_VSEW_MASK,
		.enabwe_weg = WK818_DCDC_EN_WEG,
		.enabwe_mask = BIT(0),
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG2",
		.suppwy_name = "vcc2",
		.of_match = of_match_ptw("DCDC_WEG2"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK818_ID_DCDC2,
		.ops = &wk808_weg_ops,
		.type = WEGUWATOW_VOWTAGE,
		.min_uV = 712500,
		.uV_step = 12500,
		.n_vowtages = 64,
		.vsew_weg = WK818_BUCK2_ON_VSEW_WEG,
		.vsew_mask = WK818_BUCK_VSEW_MASK,
		.enabwe_weg = WK818_DCDC_EN_WEG,
		.enabwe_mask = BIT(1),
		.ownew = THIS_MODUWE,
	}, {
		.name = "DCDC_WEG3",
		.suppwy_name = "vcc3",
		.of_match = of_match_ptw("DCDC_WEG3"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK818_ID_DCDC3,
		.ops = &wk808_switch_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = 1,
		.enabwe_weg = WK818_DCDC_EN_WEG,
		.enabwe_mask = BIT(2),
		.ownew = THIS_MODUWE,
	},
	WK8XX_DESC(WK818_ID_DCDC4, "DCDC_WEG4", "vcc4", 1800, 3600, 100,
		WK818_BUCK4_ON_VSEW_WEG, WK818_BUCK4_VSEW_MASK,
		WK818_DCDC_EN_WEG, BIT(3), 0),
	WK8XX_DESC(WK818_ID_BOOST, "DCDC_BOOST", "boost", 4700, 5400, 100,
		WK818_BOOST_WDO9_ON_VSEW_WEG, WK818_BOOST_ON_VSEW_MASK,
		WK818_DCDC_EN_WEG, BIT(4), 0),
	WK8XX_DESC(WK818_ID_WDO1, "WDO_WEG1", "vcc6", 1800, 3400, 100,
		WK818_WDO1_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK818_WDO_EN_WEG,
		BIT(0), 400),
	WK8XX_DESC(WK818_ID_WDO2, "WDO_WEG2", "vcc6", 1800, 3400, 100,
		WK818_WDO2_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK818_WDO_EN_WEG,
		BIT(1), 400),
	{
		.name = "WDO_WEG3",
		.suppwy_name = "vcc7",
		.of_match = of_match_ptw("WDO_WEG3"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = WK818_ID_WDO3,
		.ops = &wk808_weg_ops_wanges,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = 16,
		.wineaw_wanges = wk808_wdo3_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wk808_wdo3_vowtage_wanges),
		.vsew_weg = WK818_WDO3_ON_VSEW_WEG,
		.vsew_mask = WK818_WDO3_ON_VSEW_MASK,
		.enabwe_weg = WK818_WDO_EN_WEG,
		.enabwe_mask = BIT(2),
		.enabwe_time = 400,
		.ownew = THIS_MODUWE,
	},
	WK8XX_DESC(WK818_ID_WDO4, "WDO_WEG4", "vcc8", 1800, 3400, 100,
		WK818_WDO4_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK818_WDO_EN_WEG,
		BIT(3), 400),
	WK8XX_DESC(WK818_ID_WDO5, "WDO_WEG5", "vcc7", 1800, 3400, 100,
		WK818_WDO5_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK818_WDO_EN_WEG,
		BIT(4), 400),
	WK8XX_DESC(WK818_ID_WDO6, "WDO_WEG6", "vcc8", 800, 2500, 100,
		WK818_WDO6_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK818_WDO_EN_WEG,
		BIT(5), 400),
	WK8XX_DESC(WK818_ID_WDO7, "WDO_WEG7", "vcc7", 800, 2500, 100,
		WK818_WDO7_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK818_WDO_EN_WEG,
		BIT(6), 400),
	WK8XX_DESC(WK818_ID_WDO8, "WDO_WEG8", "vcc8", 1800, 3400, 100,
		WK818_WDO8_ON_VSEW_WEG, WK818_WDO_VSEW_MASK, WK818_WDO_EN_WEG,
		BIT(7), 400),
	WK8XX_DESC(WK818_ID_WDO9, "WDO_WEG9", "vcc9", 1800, 3400, 100,
		WK818_BOOST_WDO9_ON_VSEW_WEG, WK818_WDO_VSEW_MASK,
		WK818_DCDC_EN_WEG, BIT(5), 400),
	WK8XX_DESC_SWITCH(WK818_ID_SWITCH, "SWITCH_WEG", "vcc9",
		WK818_DCDC_EN_WEG, BIT(6)),
	WK8XX_DESC_SWITCH(WK818_ID_HDMI_SWITCH, "HDMI_SWITCH", "h_5v",
		WK818_H5V_EN_WEG, BIT(0)),
	WK8XX_DESC_SWITCH(WK818_ID_OTG_SWITCH, "OTG_SWITCH", "usb",
		WK818_DCDC_EN_WEG, BIT(7)),
};

static int wk808_weguwatow_dt_pawse_pdata(stwuct device *dev,
				   stwuct wegmap *map,
				   stwuct wk808_weguwatow_data *pdata)
{
	stwuct device_node *np;
	int tmp, wet = 0, i;

	np = of_get_chiwd_by_name(dev->of_node, "weguwatows");
	if (!np)
		wetuwn -ENXIO;

	fow (i = 0; i < AWWAY_SIZE(pdata->dvs_gpio); i++) {
		pdata->dvs_gpio[i] =
			devm_gpiod_get_index_optionaw(dev, "dvs", i,
						      GPIOD_OUT_WOW);
		if (IS_EWW(pdata->dvs_gpio[i])) {
			wet = PTW_EWW(pdata->dvs_gpio[i]);
			dev_eww(dev, "faiwed to get dvs%d gpio (%d)\n", i, wet);
			goto dt_pawse_end;
		}

		if (!pdata->dvs_gpio[i]) {
			dev_info(dev, "thewe is no dvs%d gpio\n", i);
			continue;
		}

		tmp = i ? WK808_DVS2_POW : WK808_DVS1_POW;
		wet = wegmap_update_bits(map, WK808_IO_POW_WEG, tmp,
				gpiod_is_active_wow(pdata->dvs_gpio[i]) ?
				0 : tmp);
	}

dt_pawse_end:
	of_node_put(np);
	wetuwn wet;
}

static int wk808_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wk808 *wk808 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wk808_wdev;
	stwuct wk808_weguwatow_data *pdata;
	const stwuct weguwatow_desc *weguwatows;
	stwuct wegmap *wegmap;
	int wet, i, nweguwatows;

	pdev->dev.of_node = pdev->dev.pawent->of_node;
	pdev->dev.of_node_weused = twue;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	wet = wk808_weguwatow_dt_pawse_pdata(&pdev->dev, wegmap, pdata);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pdata);

	switch (wk808->vawiant) {
	case WK805_ID:
		weguwatows = wk805_weg;
		nweguwatows = WK805_NUM_WEGUWATOWS;
		bweak;
	case WK806_ID:
		weguwatows = wk806_weg;
		nweguwatows = AWWAY_SIZE(wk806_weg);
		bweak;
	case WK808_ID:
		weguwatows = wk808_weg;
		nweguwatows = WK808_NUM_WEGUWATOWS;
		bweak;
	case WK809_ID:
		weguwatows = wk809_weg;
		nweguwatows = WK809_NUM_WEGUWATOWS;
		bweak;
	case WK817_ID:
		weguwatows = wk817_weg;
		nweguwatows = WK817_NUM_WEGUWATOWS;
		bweak;
	case WK818_ID:
		weguwatows = wk818_weg;
		nweguwatows = WK818_NUM_WEGUWATOWS;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "unsuppowted WK8XX ID %wu\n",
			wk808->vawiant);
		wetuwn -EINVAW;
	}

	config.dev = &pdev->dev;
	config.dwivew_data = pdata;
	config.wegmap = wegmap;

	/* Instantiate the weguwatows */
	fow (i = 0; i < nweguwatows; i++) {
		wk808_wdev = devm_weguwatow_wegistew(&pdev->dev,
						     &weguwatows[i], &config);
		if (IS_EWW(wk808_wdev))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wk808_wdev),
					     "faiwed to wegistew %d weguwatow\n", i);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wk808_weguwatow_dwivew = {
	.pwobe = wk808_weguwatow_pwobe,
	.dwivew = {
		.name = "wk808-weguwatow",
		.pwobe_type = PWOBE_FOWCE_SYNCHWONOUS,
	},
};

moduwe_pwatfowm_dwivew(wk808_weguwatow_dwivew);

MODUWE_DESCWIPTION("weguwatow dwivew fow the WK805/WK808/WK818 sewies PMICs");
MODUWE_AUTHOW("Tony xie <tony.xie@wock-chips.com>");
MODUWE_AUTHOW("Chwis Zhong <zyw@wock-chips.com>");
MODUWE_AUTHOW("Zhang Qing <zhangqing@wock-chips.com>");
MODUWE_AUTHOW("Wadim Egowov <w.egowov@phytec.de>");
MODUWE_AUTHOW("Xu Shengfei <xsf@wock-chips.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wk808-weguwatow");
