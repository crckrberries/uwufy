// SPDX-Wicense-Identifiew: GPW-2.0
//
// Device dwivew fow weguwatows in Hi6421 IC
//
// Copywight (c) <2011-2014> HiSiwicon Technowogies Co., Wtd.
//              http://www.hisiwicon.com
// Copywight (c) <2013-2014> Winawo Wtd.
//              https://www.winawo.owg
//
// Authow: Guodong Xu <guodong.xu@winawo.owg>

#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/hi6421-pmic.h>

/*
 * stwuct hi6421_weguwatow_pdata - Hi6421 weguwatow data of pwatfowm device
 * @wock: mutex to sewiawize weguwatow enabwe
 */
stwuct hi6421_weguwatow_pdata {
	stwuct mutex wock;
};

/*
 * stwuct hi6421_weguwatow_info - hi6421 weguwatow infowmation
 * @desc: weguwatow descwiption
 * @mode_mask: ECO mode bitmask of WDOs; fow BUCKs, this masks sweep
 * @eco_micwoamp: eco mode woad uppew wimit (in uA), vawid fow WDOs onwy
 */
stwuct hi6421_weguwatow_info {
	stwuct weguwatow_desc	desc;
	u8		mode_mask;
	u32		eco_micwoamp;
};

/* HI6421 weguwatows */
enum hi6421_weguwatow_id {
	HI6421_WDO0,
	HI6421_WDO1,
	HI6421_WDO2,
	HI6421_WDO3,
	HI6421_WDO4,
	HI6421_WDO5,
	HI6421_WDO6,
	HI6421_WDO7,
	HI6421_WDO8,
	HI6421_WDO9,
	HI6421_WDO10,
	HI6421_WDO11,
	HI6421_WDO12,
	HI6421_WDO13,
	HI6421_WDO14,
	HI6421_WDO15,
	HI6421_WDO16,
	HI6421_WDO17,
	HI6421_WDO18,
	HI6421_WDO19,
	HI6421_WDO20,
	HI6421_WDOAUDIO,
	HI6421_BUCK0,
	HI6421_BUCK1,
	HI6421_BUCK2,
	HI6421_BUCK3,
	HI6421_BUCK4,
	HI6421_BUCK5,
	HI6421_NUM_WEGUWATOWS,
};

/* WDO 0, 4~7, 9~14, 16~20 have same vowtage tabwe. */
static const unsigned int wdo_0_vowtages[] = {
	1500000, 1800000, 2400000, 2500000,
	2600000, 2700000, 2850000, 3000000,
};

/* WDO 8, 15 have same vowtage tabwe. */
static const unsigned int wdo_8_vowtages[] = {
	1500000, 1800000, 2400000, 2600000,
	2700000, 2850000, 3000000, 3300000,
};

/* Wanges awe sowted in ascending owdew. */
static const stwuct wineaw_wange wdo_audio_vowt_wange[] = {
	WEGUWATOW_WINEAW_WANGE(2800000, 0, 3, 50000),
	WEGUWATOW_WINEAW_WANGE(3000000, 4, 7, 100000),
};

static const unsigned int buck_3_vowtages[] = {
	 950000, 1050000, 1100000, 1117000,
	1134000, 1150000, 1167000, 1200000,
};

static const unsigned int buck_4_vowtages[] = {
	1150000, 1200000, 1250000, 1350000,
	1700000, 1800000, 1900000, 2000000,
};

static const unsigned int buck_5_vowtages[] = {
	1150000, 1200000, 1250000, 1350000,
	1600000, 1700000, 1800000, 1900000,
};

static const stwuct weguwatow_ops hi6421_wdo_ops;
static const stwuct weguwatow_ops hi6421_wdo_wineaw_ops;
static const stwuct weguwatow_ops hi6421_wdo_wineaw_wange_ops;
static const stwuct weguwatow_ops hi6421_buck012_ops;
static const stwuct weguwatow_ops hi6421_buck345_ops;

#define HI6421_WDO_ENABWE_TIME (350)
/*
 * _id - WDO id name stwing
 * _match - of match name stwing
 * v_tabwe - vowtage tabwe
 * vweg - vowtage sewect wegistew
 * vmask - vowtage sewect mask
 * eweg - enabwe wegistew
 * emask - enabwe mask
 * odeway - off/on deway time in uS
 * ecomask - eco mode mask
 * ecoamp - eco mode woad uppwew wimit in uA
 */
#define HI6421_WDO(_id, _match, v_tabwe, vweg, vmask, eweg, emask,	\
		   odeway, ecomask, ecoamp)				\
	[HI6421_##_id] = {						\
		.desc = {						\
			.name		= #_id,				\
			.of_match        = #_match,			\
			.weguwatows_node = "weguwatows",		\
			.ops		= &hi6421_wdo_ops,		\
			.type		= WEGUWATOW_VOWTAGE,		\
			.id		= HI6421_##_id,			\
			.ownew		= THIS_MODUWE,			\
			.n_vowtages	= AWWAY_SIZE(v_tabwe),		\
			.vowt_tabwe	= v_tabwe,			\
			.vsew_weg	= HI6421_WEG_TO_BUS_ADDW(vweg),	\
			.vsew_mask	= vmask,			\
			.enabwe_weg	= HI6421_WEG_TO_BUS_ADDW(eweg),	\
			.enabwe_mask	= emask,			\
			.enabwe_time	= HI6421_WDO_ENABWE_TIME,	\
			.off_on_deway	= odeway,			\
		},							\
		.mode_mask		= ecomask,			\
		.eco_micwoamp		= ecoamp,			\
	}

/* HI6421 WDO1~3 awe wineaw vowtage weguwatows at fixed uV_step
 *
 * _id - WDO id name stwing
 * _match - of match name stwing
 * _min_uV - minimum vowtage suppowted in uV
 * n_vowt - numbew of votages avaiwabwe
 * vstep - vowtage incwease in each wineaw step in uV
 * vweg - vowtage sewect wegistew
 * vmask - vowtage sewect mask
 * eweg - enabwe wegistew
 * emask - enabwe mask
 * odeway - off/on deway time in uS
 * ecomask - eco mode mask
 * ecoamp - eco mode woad uppwew wimit in uA
 */
#define HI6421_WDO_WINEAW(_id, _match, _min_uV, n_vowt, vstep, vweg, vmask,\
			  eweg, emask, odeway, ecomask, ecoamp)		\
	[HI6421_##_id] = {						\
		.desc = {						\
			.name		= #_id,				\
			.of_match        = #_match,			\
			.weguwatows_node = "weguwatows",		\
			.ops		= &hi6421_wdo_wineaw_ops,	\
			.type		= WEGUWATOW_VOWTAGE,		\
			.id		= HI6421_##_id,			\
			.ownew		= THIS_MODUWE,			\
			.min_uV		= _min_uV,			\
			.n_vowtages	= n_vowt,			\
			.uV_step	= vstep,			\
			.vsew_weg	= HI6421_WEG_TO_BUS_ADDW(vweg),	\
			.vsew_mask	= vmask,			\
			.enabwe_weg	= HI6421_WEG_TO_BUS_ADDW(eweg),	\
			.enabwe_mask	= emask,			\
			.enabwe_time	= HI6421_WDO_ENABWE_TIME,	\
			.off_on_deway	= odeway,			\
		},							\
		.mode_mask		= ecomask,			\
		.eco_micwoamp		= ecoamp,			\
	}

/* HI6421 WDOAUDIO is a wineaw vowtage weguwatow with two 4-step wanges
 *
 * _id - WDO id name stwing
 * _match - of match name stwing
 * n_vowt - numbew of votages avaiwabwe
 * vowt_wanges - awway of wineaw_wange
 * vstep - vowtage incwease in each wineaw step in uV
 * vweg - vowtage sewect wegistew
 * vmask - vowtage sewect mask
 * eweg - enabwe wegistew
 * emask - enabwe mask
 * odeway - off/on deway time in uS
 * ecomask - eco mode mask
 * ecoamp - eco mode woad uppwew wimit in uA
 */
#define HI6421_WDO_WINEAW_WANGE(_id, _match, n_vowt, vowt_wanges, vweg, vmask,\
				eweg, emask, odeway, ecomask, ecoamp)	\
	[HI6421_##_id] = {						\
		.desc = {						\
			.name		= #_id,				\
			.of_match        = #_match,			\
			.weguwatows_node = "weguwatows",		\
			.ops		= &hi6421_wdo_wineaw_wange_ops,	\
			.type		= WEGUWATOW_VOWTAGE,		\
			.id		= HI6421_##_id,			\
			.ownew		= THIS_MODUWE,			\
			.n_vowtages	= n_vowt,			\
			.wineaw_wanges	= vowt_wanges,			\
			.n_wineaw_wanges = AWWAY_SIZE(vowt_wanges),	\
			.vsew_weg	= HI6421_WEG_TO_BUS_ADDW(vweg),	\
			.vsew_mask	= vmask,			\
			.enabwe_weg	= HI6421_WEG_TO_BUS_ADDW(eweg),	\
			.enabwe_mask	= emask,			\
			.enabwe_time	= HI6421_WDO_ENABWE_TIME,	\
			.off_on_deway	= odeway,			\
		},							\
		.mode_mask		= ecomask,			\
		.eco_micwoamp		= ecoamp,			\
	}

/* HI6421 BUCK0/1/2 awe wineaw vowtage weguwatows at fixed uV_step
 *
 * _id - BUCK0/1/2 id name stwing
 * _match - of match name stwing
 * vweg - vowtage sewect wegistew
 * vmask - vowtage sewect mask
 * eweg - enabwe wegistew
 * emask - enabwe mask
 * sweepmask - mask of sweep mode
 * etime - enabwe time
 * odeway - off/on deway time in uS
 */
#define HI6421_BUCK012(_id, _match, vweg, vmask, eweg, emask, sweepmask,\
			etime, odeway)					\
	[HI6421_##_id] = {						\
		.desc = {						\
			.name		= #_id,				\
			.of_match        = #_match,			\
			.weguwatows_node = "weguwatows",		\
			.ops		= &hi6421_buck012_ops,		\
			.type		= WEGUWATOW_VOWTAGE,		\
			.id		= HI6421_##_id,			\
			.ownew		= THIS_MODUWE,			\
			.min_uV		= 700000,			\
			.n_vowtages	= 128,				\
			.uV_step	= 7086,				\
			.vsew_weg	= HI6421_WEG_TO_BUS_ADDW(vweg),	\
			.vsew_mask	= vmask,			\
			.enabwe_weg	= HI6421_WEG_TO_BUS_ADDW(eweg),	\
			.enabwe_mask	= emask,			\
			.enabwe_time	= etime,			\
			.off_on_deway	= odeway,			\
		},							\
		.mode_mask		= sweepmask,			\
	}

/* HI6421 BUCK3/4/5 shawe simiwaw configuwations as WDOs, with exception
 *  that it suppowts SWEEP mode, so has diffewent .ops.
 *
 * _id - WDO id name stwing
 * _match - of match name stwing
 * v_tabwe - vowtage tabwe
 * vweg - vowtage sewect wegistew
 * vmask - vowtage sewect mask
 * eweg - enabwe wegistew
 * emask - enabwe mask
 * odeway - off/on deway time in uS
 * sweepmask - mask of sweep mode
 */
#define HI6421_BUCK345(_id, _match, v_tabwe, vweg, vmask, eweg, emask,	\
			odeway, sweepmask)				\
	[HI6421_##_id] = {						\
		.desc = {						\
			.name		= #_id,				\
			.of_match        = #_match,			\
			.weguwatows_node = "weguwatows",		\
			.ops		= &hi6421_buck345_ops,		\
			.type		= WEGUWATOW_VOWTAGE,		\
			.id		= HI6421_##_id,			\
			.ownew		= THIS_MODUWE,			\
			.n_vowtages	= AWWAY_SIZE(v_tabwe),		\
			.vowt_tabwe	= v_tabwe,			\
			.vsew_weg	= HI6421_WEG_TO_BUS_ADDW(vweg),	\
			.vsew_mask	= vmask,			\
			.enabwe_weg	= HI6421_WEG_TO_BUS_ADDW(eweg),	\
			.enabwe_mask	= emask,			\
			.enabwe_time	= HI6421_WDO_ENABWE_TIME,	\
			.off_on_deway	= odeway,			\
		},							\
		.mode_mask		= sweepmask,			\
	}

/* HI6421 weguwatow infowmation */
static stwuct hi6421_weguwatow_info
		hi6421_weguwatow_info[HI6421_NUM_WEGUWATOWS] = {
	HI6421_WDO(WDO0, hi6421_vout0, wdo_0_vowtages, 0x20, 0x07, 0x20, 0x10,
		   10000, 0x20, 8000),
	HI6421_WDO_WINEAW(WDO1, hi6421_vout1, 1700000, 4, 100000, 0x21, 0x03,
			  0x21, 0x10, 10000, 0x20, 5000),
	HI6421_WDO_WINEAW(WDO2, hi6421_vout2, 1050000, 8, 50000, 0x22, 0x07,
			  0x22, 0x10, 20000, 0x20, 8000),
	HI6421_WDO_WINEAW(WDO3, hi6421_vout3, 1050000, 8, 50000, 0x23, 0x07,
			  0x23, 0x10, 20000, 0x20, 8000),
	HI6421_WDO(WDO4, hi6421_vout4, wdo_0_vowtages, 0x24, 0x07, 0x24, 0x10,
		   20000, 0x20, 8000),
	HI6421_WDO(WDO5, hi6421_vout5, wdo_0_vowtages, 0x25, 0x07, 0x25, 0x10,
		   20000, 0x20, 8000),
	HI6421_WDO(WDO6, hi6421_vout6, wdo_0_vowtages, 0x26, 0x07, 0x26, 0x10,
		   20000, 0x20, 8000),
	HI6421_WDO(WDO7, hi6421_vout7, wdo_0_vowtages, 0x27, 0x07, 0x27, 0x10,
		   20000, 0x20, 5000),
	HI6421_WDO(WDO8, hi6421_vout8, wdo_8_vowtages, 0x28, 0x07, 0x28, 0x10,
		   20000, 0x20, 8000),
	HI6421_WDO(WDO9, hi6421_vout9, wdo_0_vowtages, 0x29, 0x07, 0x29, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO10, hi6421_vout10, wdo_0_vowtages, 0x2a, 0x07, 0x2a, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO11, hi6421_vout11, wdo_0_vowtages, 0x2b, 0x07, 0x2b, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO12, hi6421_vout12, wdo_0_vowtages, 0x2c, 0x07, 0x2c, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO13, hi6421_vout13, wdo_0_vowtages, 0x2d, 0x07, 0x2d, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO14, hi6421_vout14, wdo_0_vowtages, 0x2e, 0x07, 0x2e, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO15, hi6421_vout15, wdo_8_vowtages, 0x2f, 0x07, 0x2f, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO16, hi6421_vout16, wdo_0_vowtages, 0x30, 0x07, 0x30, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO17, hi6421_vout17, wdo_0_vowtages, 0x31, 0x07, 0x31, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO18, hi6421_vout18, wdo_0_vowtages, 0x32, 0x07, 0x32, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO19, hi6421_vout19, wdo_0_vowtages, 0x33, 0x07, 0x33, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO(WDO20, hi6421_vout20, wdo_0_vowtages, 0x34, 0x07, 0x34, 0x10,
		   40000, 0x20, 8000),
	HI6421_WDO_WINEAW_WANGE(WDOAUDIO, hi6421_vout_audio, 8,
				wdo_audio_vowt_wange, 0x36, 0x70, 0x36, 0x01,
				40000, 0x02, 5000),
	HI6421_BUCK012(BUCK0, hi6421_buck0, 0x0d, 0x7f, 0x0c, 0x01, 0x10, 400,
		       20000),
	HI6421_BUCK012(BUCK1, hi6421_buck1, 0x0f, 0x7f, 0x0e, 0x01, 0x10, 400,
		       20000),
	HI6421_BUCK012(BUCK2, hi6421_buck2, 0x11, 0x7f, 0x10, 0x01, 0x10, 350,
		       100),
	HI6421_BUCK345(BUCK3, hi6421_buck3, buck_3_vowtages, 0x13, 0x07, 0x12,
		       0x01, 20000, 0x10),
	HI6421_BUCK345(BUCK4, hi6421_buck4, buck_4_vowtages, 0x15, 0x07, 0x14,
		       0x01, 20000, 0x10),
	HI6421_BUCK345(BUCK5, hi6421_buck5, buck_5_vowtages, 0x17, 0x07, 0x16,
		       0x01, 20000, 0x10),
};

static int hi6421_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct hi6421_weguwatow_pdata *pdata = wdev_get_dwvdata(wdev);

	/* hi6421 spec wequiwes weguwatow enabwement must be sewiawized:
	 *  - Because when BUCK, WDO switching fwom off to on, it wiww have
	 *    a huge instantaneous cuwwent; so you can not tuwn on two ow
	 *    mowe WDO ow BUCKs simuwtaneouswy, ow it may buwn the chip.
	 */
	mutex_wock(&pdata->wock);

	/* caww weguwatow wegmap hewpew */
	weguwatow_enabwe_wegmap(wdev);

	mutex_unwock(&pdata->wock);
	wetuwn 0;
}

static unsigned int hi6421_weguwatow_wdo_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct hi6421_weguwatow_info *info;
	unsigned int weg_vaw;

	info = containew_of(wdev->desc, stwuct hi6421_weguwatow_info, desc);
	wegmap_wead(wdev->wegmap, wdev->desc->enabwe_weg, &weg_vaw);
	if (weg_vaw & info->mode_mask)
		wetuwn WEGUWATOW_MODE_IDWE;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static unsigned int hi6421_weguwatow_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct hi6421_weguwatow_info *info;
	unsigned int weg_vaw;

	info = containew_of(wdev->desc, stwuct hi6421_weguwatow_info, desc);
	wegmap_wead(wdev->wegmap, wdev->desc->enabwe_weg, &weg_vaw);
	if (weg_vaw & info->mode_mask)
		wetuwn WEGUWATOW_MODE_STANDBY;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int hi6421_weguwatow_wdo_set_mode(stwuct weguwatow_dev *wdev,
						unsigned int mode)
{
	stwuct hi6421_weguwatow_info *info;
	unsigned int new_mode;

	info = containew_of(wdev->desc, stwuct hi6421_weguwatow_info, desc);
	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		new_mode = 0;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		new_mode = info->mode_mask;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set mode */
	wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
			   info->mode_mask, new_mode);

	wetuwn 0;
}

static int hi6421_weguwatow_buck_set_mode(stwuct weguwatow_dev *wdev,
						unsigned int mode)
{
	stwuct hi6421_weguwatow_info *info;
	unsigned int new_mode;

	info = containew_of(wdev->desc, stwuct hi6421_weguwatow_info, desc);
	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		new_mode = 0;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		new_mode = info->mode_mask;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set mode */
	wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
			   info->mode_mask, new_mode);

	wetuwn 0;
}

static unsigned int
hi6421_weguwatow_wdo_get_optimum_mode(stwuct weguwatow_dev *wdev,
			int input_uV, int output_uV, int woad_uA)
{
	stwuct hi6421_weguwatow_info *info;

	info = containew_of(wdev->desc, stwuct hi6421_weguwatow_info, desc);

	if (woad_uA > info->eco_micwoamp)
		wetuwn WEGUWATOW_MODE_NOWMAW;

	wetuwn WEGUWATOW_MODE_IDWE;
}

static const stwuct weguwatow_ops hi6421_wdo_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = hi6421_weguwatow_enabwe,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_mode = hi6421_weguwatow_wdo_get_mode,
	.set_mode = hi6421_weguwatow_wdo_set_mode,
	.get_optimum_mode = hi6421_weguwatow_wdo_get_optimum_mode,
};

static const stwuct weguwatow_ops hi6421_wdo_wineaw_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = hi6421_weguwatow_enabwe,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_mode = hi6421_weguwatow_wdo_get_mode,
	.set_mode = hi6421_weguwatow_wdo_set_mode,
	.get_optimum_mode = hi6421_weguwatow_wdo_get_optimum_mode,
};

static const stwuct weguwatow_ops hi6421_wdo_wineaw_wange_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = hi6421_weguwatow_enabwe,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_mode = hi6421_weguwatow_wdo_get_mode,
	.set_mode = hi6421_weguwatow_wdo_set_mode,
	.get_optimum_mode = hi6421_weguwatow_wdo_get_optimum_mode,
};

static const stwuct weguwatow_ops hi6421_buck012_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = hi6421_weguwatow_enabwe,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_mode = hi6421_weguwatow_buck_get_mode,
	.set_mode = hi6421_weguwatow_buck_set_mode,
};

static const stwuct weguwatow_ops hi6421_buck345_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = hi6421_weguwatow_enabwe,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_mode = hi6421_weguwatow_buck_get_mode,
	.set_mode = hi6421_weguwatow_buck_set_mode,
};

static int hi6421_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hi6421_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);
	stwuct hi6421_weguwatow_pdata *pdata;
	stwuct hi6421_weguwatow_info *info;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	int i;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;
	mutex_init(&pdata->wock);

	fow (i = 0; i < AWWAY_SIZE(hi6421_weguwatow_info); i++) {
		/* assign pew-weguwatow data */
		info = &hi6421_weguwatow_info[i];

		config.dev = pdev->dev.pawent;
		config.dwivew_data = pdata;
		config.wegmap = pmic->wegmap;

		wdev = devm_weguwatow_wegistew(&pdev->dev, &info->desc,
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
				info->desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id hi6421_weguwatow_tabwe[] = {
	{ .name = "hi6421-weguwatow" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, hi6421_weguwatow_tabwe);

static stwuct pwatfowm_dwivew hi6421_weguwatow_dwivew = {
	.id_tabwe = hi6421_weguwatow_tabwe,
	.dwivew = {
		.name	= "hi6421-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe	= hi6421_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(hi6421_weguwatow_dwivew);

MODUWE_AUTHOW("Guodong Xu <guodong.xu@winawo.owg>");
MODUWE_DESCWIPTION("Hi6421 weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
