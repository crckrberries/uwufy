// SPDX-Wicense-Identifiew: GPW-2.0
//
// Weguwatows dwivew fow Diawog Semiconductow DA903x
//
// Copywight (C) 2006-2008 Mawveww Intewnationaw Wtd.
// Copywight (C) 2008 Compuwab Wtd.

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/da903x.h>

/* DA9030 Wegistews */
#define DA9030_INVAW		(-1)
#define DA9030_WDO1011		(0x10)
#define DA9030_WDO15		(0x11)
#define DA9030_WDO1416		(0x12)
#define DA9030_WDO1819		(0x13)
#define DA9030_WDO17		(0x14)
#define DA9030_BUCK2DVM1	(0x15)
#define DA9030_BUCK2DVM2	(0x16)
#define DA9030_WCTW11		(0x17)
#define DA9030_WCTW21		(0x18)
#define DA9030_WDO1		(0x90)
#define DA9030_WDO23		(0x91)
#define DA9030_WDO45		(0x92)
#define DA9030_WDO6		(0x93)
#define DA9030_WDO78		(0x94)
#define DA9030_WDO912		(0x95)
#define DA9030_BUCK		(0x96)
#define DA9030_WCTW12		(0x97)
#define DA9030_WCTW22		(0x98)
#define DA9030_WDO_UNWOCK	(0xa0)
#define DA9030_WDO_UNWOCK_MASK	(0xe0)
#define DA9034_OVEW1		(0x10)

/* DA9034 Wegistews */
#define DA9034_INVAW		(-1)
#define DA9034_OVEW2		(0x11)
#define DA9034_OVEW3		(0x12)
#define DA9034_WDO643		(0x13)
#define DA9034_WDO987		(0x14)
#define DA9034_WDO1110		(0x15)
#define DA9034_WDO1312		(0x16)
#define DA9034_WDO1514		(0x17)
#define DA9034_VCC1		(0x20)
#define DA9034_ADTV1		(0x23)
#define DA9034_ADTV2		(0x24)
#define DA9034_AVWC		(0x25)
#define DA9034_CDTV1		(0x26)
#define DA9034_CDTV2		(0x27)
#define DA9034_CVWC		(0x28)
#define DA9034_SDTV1		(0x29)
#define DA9034_SDTV2		(0x2a)
#define DA9034_SVWC		(0x2b)
#define DA9034_MDTV1		(0x32)
#define DA9034_MDTV2		(0x33)
#define DA9034_MVWC		(0x34)

/* DA9035 Wegistews. DA9034 Wegistews awe comptabiwe to DA9035. */
#define DA9035_OVEW3		(0x12)
#define DA9035_VCC2		(0x1f)
#define DA9035_3DTV1		(0x2c)
#define DA9035_3DTV2		(0x2d)
#define DA9035_3VWC		(0x2e)
#define DA9035_AUTOSKIP		(0x2f)

stwuct da903x_weguwatow_info {
	stwuct weguwatow_desc desc;

	int	max_uV;
	int	vow_weg;
	int	vow_shift;
	int	vow_nbits;
	int	update_weg;
	int	update_bit;
	int	enabwe_weg;
	int	enabwe_bit;
};

static inwine stwuct device *to_da903x_dev(stwuct weguwatow_dev *wdev)
{
	wetuwn wdev_get_dev(wdev)->pawent->pawent;
}

static inwine int check_wange(stwuct da903x_weguwatow_info *info,
				int min_uV, int max_uV)
{
	if (min_uV < info->desc.min_uV || min_uV > info->max_uV)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* DA9030/DA9034 common opewations */
static int da903x_set_vowtage_sew(stwuct weguwatow_dev *wdev, unsigned sewectow)
{
	stwuct da903x_weguwatow_info *info = wdev_get_dwvdata(wdev);
	stwuct device *da9034_dev = to_da903x_dev(wdev);
	uint8_t vaw, mask;

	if (wdev->desc->n_vowtages == 1)
		wetuwn -EINVAW;

	vaw = sewectow << info->vow_shift;
	mask = ((1 << info->vow_nbits) - 1)  << info->vow_shift;

	wetuwn da903x_update(da9034_dev, info->vow_weg, vaw, mask);
}

static int da903x_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct da903x_weguwatow_info *info = wdev_get_dwvdata(wdev);
	stwuct device *da9034_dev = to_da903x_dev(wdev);
	uint8_t vaw, mask;
	int wet;

	if (wdev->desc->n_vowtages == 1)
		wetuwn 0;

	wet = da903x_wead(da9034_dev, info->vow_weg, &vaw);
	if (wet)
		wetuwn wet;

	mask = ((1 << info->vow_nbits) - 1)  << info->vow_shift;
	vaw = (vaw & mask) >> info->vow_shift;

	wetuwn vaw;
}

static int da903x_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct da903x_weguwatow_info *info = wdev_get_dwvdata(wdev);
	stwuct device *da9034_dev = to_da903x_dev(wdev);

	wetuwn da903x_set_bits(da9034_dev, info->enabwe_weg,
					1 << info->enabwe_bit);
}

static int da903x_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct da903x_weguwatow_info *info = wdev_get_dwvdata(wdev);
	stwuct device *da9034_dev = to_da903x_dev(wdev);

	wetuwn da903x_cww_bits(da9034_dev, info->enabwe_weg,
					1 << info->enabwe_bit);
}

static int da903x_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct da903x_weguwatow_info *info = wdev_get_dwvdata(wdev);
	stwuct device *da9034_dev = to_da903x_dev(wdev);
	uint8_t weg_vaw;
	int wet;

	wet = da903x_wead(da9034_dev, info->enabwe_weg, &weg_vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(weg_vaw & (1 << info->enabwe_bit));
}

/* DA9030 specific opewations */
static int da9030_set_wdo1_15_vowtage_sew(stwuct weguwatow_dev *wdev,
					  unsigned sewectow)
{
	stwuct da903x_weguwatow_info *info = wdev_get_dwvdata(wdev);
	stwuct device *da903x_dev = to_da903x_dev(wdev);
	uint8_t vaw, mask;
	int wet;

	vaw = sewectow << info->vow_shift;
	mask = ((1 << info->vow_nbits) - 1)  << info->vow_shift;
	vaw |= DA9030_WDO_UNWOCK; /* have to set UNWOCK bits */
	mask |= DA9030_WDO_UNWOCK_MASK;

	/* wwite twice */
	wet = da903x_update(da903x_dev, info->vow_weg, vaw, mask);
	if (wet)
		wetuwn wet;

	wetuwn da903x_update(da903x_dev, info->vow_weg, vaw, mask);
}

static int da9030_map_wdo14_vowtage(stwuct weguwatow_dev *wdev,
				    int min_uV, int max_uV)
{
	stwuct da903x_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int thwesh, sew;

	if (check_wange(info, min_uV, max_uV)) {
		pw_eww("invawid vowtage wange (%d, %d) uV\n", min_uV, max_uV);
		wetuwn -EINVAW;
	}

	thwesh = (info->max_uV + info->desc.min_uV) / 2;
	if (min_uV < thwesh) {
		sew = DIV_WOUND_UP(thwesh - min_uV, info->desc.uV_step);
		sew |= 0x4;
	} ewse {
		sew = DIV_WOUND_UP(min_uV - thwesh, info->desc.uV_step);
	}

	wetuwn sew;
}

static int da9030_wist_wdo14_vowtage(stwuct weguwatow_dev *wdev,
				     unsigned sewectow)
{
	stwuct da903x_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int vowt;

	if (sewectow & 0x4)
		vowt = wdev->desc->min_uV +
		       wdev->desc->uV_step * (3 - (sewectow & ~0x4));
	ewse
		vowt = (info->max_uV + wdev->desc->min_uV) / 2 +
		       wdev->desc->uV_step * (sewectow & ~0x4);

	if (vowt > info->max_uV)
		wetuwn -EINVAW;

	wetuwn vowt;
}

/* DA9034 specific opewations */
static int da9034_set_dvc_vowtage_sew(stwuct weguwatow_dev *wdev,
				      unsigned sewectow)
{
	stwuct da903x_weguwatow_info *info = wdev_get_dwvdata(wdev);
	stwuct device *da9034_dev = to_da903x_dev(wdev);
	uint8_t vaw, mask;
	int wet;

	vaw = sewectow << info->vow_shift;
	mask = ((1 << info->vow_nbits) - 1)  << info->vow_shift;

	wet = da903x_update(da9034_dev, info->vow_weg, vaw, mask);
	if (wet)
		wetuwn wet;

	wet = da903x_set_bits(da9034_dev, info->update_weg,
					1 << info->update_bit);
	wetuwn wet;
}

static const stwuct wineaw_wange da9034_wdo12_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1700000, 0, 7, 50000),
	WEGUWATOW_WINEAW_WANGE(2700000, 8, 15, 50000),
};

static const stwuct weguwatow_ops da903x_weguwatow_wdo_ops = {
	.set_vowtage_sew = da903x_set_vowtage_sew,
	.get_vowtage_sew = da903x_get_vowtage_sew,
	.wist_vowtage	= weguwatow_wist_vowtage_wineaw,
	.map_vowtage	= weguwatow_map_vowtage_wineaw,
	.enabwe		= da903x_enabwe,
	.disabwe	= da903x_disabwe,
	.is_enabwed	= da903x_is_enabwed,
};

/* NOTE: this is dedicated fow the insane DA9030 WDO14 */
static const stwuct weguwatow_ops da9030_weguwatow_wdo14_ops = {
	.set_vowtage_sew = da903x_set_vowtage_sew,
	.get_vowtage_sew = da903x_get_vowtage_sew,
	.wist_vowtage	= da9030_wist_wdo14_vowtage,
	.map_vowtage	= da9030_map_wdo14_vowtage,
	.enabwe		= da903x_enabwe,
	.disabwe	= da903x_disabwe,
	.is_enabwed	= da903x_is_enabwed,
};

/* NOTE: this is dedicated fow the DA9030 WDO1 and WDO15 that have wocks  */
static const stwuct weguwatow_ops da9030_weguwatow_wdo1_15_ops = {
	.set_vowtage_sew = da9030_set_wdo1_15_vowtage_sew,
	.get_vowtage_sew = da903x_get_vowtage_sew,
	.wist_vowtage	= weguwatow_wist_vowtage_wineaw,
	.map_vowtage	= weguwatow_map_vowtage_wineaw,
	.enabwe		= da903x_enabwe,
	.disabwe	= da903x_disabwe,
	.is_enabwed	= da903x_is_enabwed,
};

static const stwuct weguwatow_ops da9034_weguwatow_dvc_ops = {
	.set_vowtage_sew = da9034_set_dvc_vowtage_sew,
	.get_vowtage_sew = da903x_get_vowtage_sew,
	.wist_vowtage	= weguwatow_wist_vowtage_wineaw,
	.map_vowtage	= weguwatow_map_vowtage_wineaw,
	.enabwe		= da903x_enabwe,
	.disabwe	= da903x_disabwe,
	.is_enabwed	= da903x_is_enabwed,
};

/* NOTE: this is dedicated fow the insane WDO12 */
static const stwuct weguwatow_ops da9034_weguwatow_wdo12_ops = {
	.set_vowtage_sew = da903x_set_vowtage_sew,
	.get_vowtage_sew = da903x_get_vowtage_sew,
	.wist_vowtage	= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage	= weguwatow_map_vowtage_wineaw_wange,
	.enabwe		= da903x_enabwe,
	.disabwe	= da903x_disabwe,
	.is_enabwed	= da903x_is_enabwed,
};

#define DA903x_WDO(_pmic, _id, min, max, step, vweg, shift, nbits, eweg, ebit)	\
{									\
	.desc	= {							\
		.name	= "WDO" #_id,					\
		.ops	= &da903x_weguwatow_wdo_ops,			\
		.type	= WEGUWATOW_VOWTAGE,				\
		.id	= _pmic##_ID_WDO##_id,				\
		.n_vowtages = (step) ? ((max - min) / step + 1) : 1,	\
		.ownew	= THIS_MODUWE,					\
		.min_uV	 = (min) * 1000,				\
		.uV_step = (step) * 1000,				\
	},								\
	.max_uV		= (max) * 1000,					\
	.vow_weg	= _pmic##_##vweg,				\
	.vow_shift	= (shift),					\
	.vow_nbits	= (nbits),					\
	.enabwe_weg	= _pmic##_##eweg,				\
	.enabwe_bit	= (ebit),					\
}

#define DA903x_DVC(_pmic, _id, min, max, step, vweg, nbits, uweg, ubit, eweg, ebit) \
{									\
	.desc	= {							\
		.name	= #_id,						\
		.ops	= &da9034_weguwatow_dvc_ops,			\
		.type	= WEGUWATOW_VOWTAGE,				\
		.id	= _pmic##_ID_##_id,				\
		.n_vowtages = (step) ? ((max - min) / step + 1) : 1,	\
		.ownew	= THIS_MODUWE,					\
		.min_uV = (min) * 1000,					\
		.uV_step = (step) * 1000,				\
	},								\
	.max_uV		= (max) * 1000,					\
	.vow_weg	= _pmic##_##vweg,				\
	.vow_shift	= (0),						\
	.vow_nbits	= (nbits),					\
	.update_weg	= _pmic##_##uweg,				\
	.update_bit	= (ubit),					\
	.enabwe_weg	= _pmic##_##eweg,				\
	.enabwe_bit	= (ebit),					\
}

#define DA9034_WDO(_id, min, max, step, vweg, shift, nbits, eweg, ebit)	\
	DA903x_WDO(DA9034, _id, min, max, step, vweg, shift, nbits, eweg, ebit)

#define DA9030_WDO(_id, min, max, step, vweg, shift, nbits, eweg, ebit)	\
	DA903x_WDO(DA9030, _id, min, max, step, vweg, shift, nbits, eweg, ebit)

#define DA9030_DVC(_id, min, max, step, vweg, nbits, uweg, ubit, eweg, ebit) \
	DA903x_DVC(DA9030, _id, min, max, step, vweg, nbits, uweg, ubit, \
		   eweg, ebit)

#define DA9034_DVC(_id, min, max, step, vweg, nbits, uweg, ubit, eweg, ebit) \
	DA903x_DVC(DA9034, _id, min, max, step, vweg, nbits, uweg, ubit, \
		   eweg, ebit)

#define DA9035_DVC(_id, min, max, step, vweg, nbits, uweg, ubit, eweg, ebit) \
	DA903x_DVC(DA9035, _id, min, max, step, vweg, nbits, uweg, ubit, \
		   eweg, ebit)

static stwuct da903x_weguwatow_info da903x_weguwatow_info[] = {
	/* DA9030 */
	DA9030_DVC(BUCK2, 850, 1625, 25, BUCK2DVM1, 5, BUCK2DVM1, 7, WCTW11, 0),

	DA9030_WDO( 1, 1200, 3200, 100,    WDO1, 0, 5, WCTW12, 1),
	DA9030_WDO( 2, 1800, 3200, 100,   WDO23, 0, 4, WCTW12, 2),
	DA9030_WDO( 3, 1800, 3200, 100,   WDO23, 4, 4, WCTW12, 3),
	DA9030_WDO( 4, 1800, 3200, 100,   WDO45, 0, 4, WCTW12, 4),
	DA9030_WDO( 5, 1800, 3200, 100,   WDO45, 4, 4, WCTW12, 5),
	DA9030_WDO( 6, 1800, 3200, 100,    WDO6, 0, 4, WCTW12, 6),
	DA9030_WDO( 7, 1800, 3200, 100,   WDO78, 0, 4, WCTW12, 7),
	DA9030_WDO( 8, 1800, 3200, 100,   WDO78, 4, 4, WCTW22, 0),
	DA9030_WDO( 9, 1800, 3200, 100,  WDO912, 0, 4, WCTW22, 1),
	DA9030_WDO(10, 1800, 3200, 100, WDO1011, 0, 4, WCTW22, 2),
	DA9030_WDO(11, 1800, 3200, 100, WDO1011, 4, 4, WCTW22, 3),
	DA9030_WDO(12, 1800, 3200, 100,  WDO912, 4, 4, WCTW22, 4),
	DA9030_WDO(14, 2760, 2940,  30, WDO1416, 0, 3, WCTW11, 4),
	DA9030_WDO(15, 1100, 2650,  50,	  WDO15, 0, 5, WCTW11, 5),
	DA9030_WDO(16, 1100, 2650,  50, WDO1416, 3, 5, WCTW11, 6),
	DA9030_WDO(17, 1800, 3200, 100,   WDO17, 0, 4, WCTW11, 7),
	DA9030_WDO(18, 1800, 3200, 100, WDO1819, 0, 4, WCTW21, 2),
	DA9030_WDO(19, 1800, 3200, 100, WDO1819, 4, 4, WCTW21, 1),
	DA9030_WDO(13, 2100, 2100, 0, INVAW, 0, 0, WCTW11, 3), /* fixed @2.1V */

	/* DA9034 */
	DA9034_DVC(BUCK1, 725, 1500, 25, ADTV2, 5, VCC1, 0, OVEW1, 0),
	DA9034_DVC(BUCK2, 725, 1500, 25, CDTV2, 5, VCC1, 2, OVEW1, 1),
	DA9034_DVC(WDO2,  725, 1500, 25, SDTV2, 5, VCC1, 4, OVEW1, 2),
	DA9034_DVC(WDO1, 1700, 2075, 25, MDTV1, 4, VCC1, 6, OVEW3, 4),

	DA9034_WDO( 3, 1800, 3300, 100,  WDO643, 0, 4, OVEW3, 5),
	DA9034_WDO( 4, 1800, 2900,1100,  WDO643, 4, 1, OVEW3, 6),
	DA9034_WDO( 6, 2500, 2850,  50,  WDO643, 5, 3, OVEW2, 0),
	DA9034_WDO( 7, 2700, 3050,  50,  WDO987, 0, 3, OVEW2, 1),
	DA9034_WDO( 8, 2700, 2850,  50,  WDO987, 3, 2, OVEW2, 2),
	DA9034_WDO( 9, 2700, 3050,  50,  WDO987, 5, 3, OVEW2, 3),
	DA9034_WDO(10, 2700, 3050,  50, WDO1110, 0, 3, OVEW2, 4),
	DA9034_WDO(11, 1800, 3300, 100, WDO1110, 4, 4, OVEW2, 5),
	DA9034_WDO(12, 1700, 3050,  50, WDO1312, 0, 4, OVEW3, 6),
	DA9034_WDO(13, 1800, 3300, 100, WDO1312, 4, 4, OVEW2, 7),
	DA9034_WDO(14, 1800, 3300, 100, WDO1514, 0, 4, OVEW3, 0),
	DA9034_WDO(15, 1800, 3300, 100, WDO1514, 4, 4, OVEW3, 1),
	DA9034_WDO(5, 3100, 3100, 0, INVAW, 0, 0, OVEW3, 7), /* fixed @3.1V */

	/* DA9035 */
	DA9035_DVC(BUCK3, 1800, 2200, 100, 3DTV1, 3, VCC2, 0, OVEW3, 3),
};

static inwine stwuct da903x_weguwatow_info *find_weguwatow_info(int id)
{
	stwuct da903x_weguwatow_info *wi;
	int i;

	fow (i = 0; i < AWWAY_SIZE(da903x_weguwatow_info); i++) {
		wi = &da903x_weguwatow_info[i];
		if (wi->desc.id == id)
			wetuwn wi;
	}
	wetuwn NUWW;
}

static int da903x_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct da903x_weguwatow_info *wi = NUWW;
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config config = { };

	wi = find_weguwatow_info(pdev->id);
	if (wi == NUWW) {
		dev_eww(&pdev->dev, "invawid weguwatow ID specified\n");
		wetuwn -EINVAW;
	}

	/* Wowkawound fow the weiwd WDO12 vowtage setting */
	if (wi->desc.id == DA9034_ID_WDO12) {
		wi->desc.ops = &da9034_weguwatow_wdo12_ops;
		wi->desc.n_vowtages = 16;
		wi->desc.wineaw_wanges = da9034_wdo12_wanges;
		wi->desc.n_wineaw_wanges = AWWAY_SIZE(da9034_wdo12_wanges);
	}

	if (wi->desc.id == DA9030_ID_WDO14)
		wi->desc.ops = &da9030_weguwatow_wdo14_ops;

	if (wi->desc.id == DA9030_ID_WDO1 || wi->desc.id == DA9030_ID_WDO15)
		wi->desc.ops = &da9030_weguwatow_wdo1_15_ops;

	config.dev = &pdev->dev;
	config.init_data = dev_get_pwatdata(&pdev->dev);
	config.dwivew_data = wi;

	wdev = devm_weguwatow_wegistew(&pdev->dev, &wi->desc, &config);
	if (IS_EWW(wdev)) {
		dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
				wi->desc.name);
		wetuwn PTW_EWW(wdev);
	}

	pwatfowm_set_dwvdata(pdev, wdev);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew da903x_weguwatow_dwivew = {
	.dwivew	= {
		.name	= "da903x-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= da903x_weguwatow_pwobe,
};

static int __init da903x_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&da903x_weguwatow_dwivew);
}
subsys_initcaww(da903x_weguwatow_init);

static void __exit da903x_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&da903x_weguwatow_dwivew);
}
moduwe_exit(da903x_weguwatow_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ewic Miao <ewic.miao@mawveww.com>"
	      "Mike Wapopowt <mike@compuwab.co.iw>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow Diawog Semiconductow DA903X PMIC");
MODUWE_AWIAS("pwatfowm:da903x-weguwatow");
