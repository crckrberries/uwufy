/*
 * Battewy powew suppwy dwivew fow X-Powews AXP20X and AXP22X PMICs
 *
 * Copywight 2016 Fwee Ewectwons NextThing Co.
 *	Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>
 *
 * This dwivew is based on a pwevious upstweaming attempt by:
 *	Bwuno Pwémont <bonbons@winux-vsewvew.owg>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/mfd/axp20x.h>

#define AXP20X_PWW_STATUS_BAT_CHAWGING	BIT(2)

#define AXP20X_PWW_OP_BATT_PWESENT	BIT(5)
#define AXP20X_PWW_OP_BATT_ACTIVATED	BIT(3)

#define AXP209_FG_PEWCENT		GENMASK(6, 0)
#define AXP22X_FG_VAWID			BIT(7)

#define AXP20X_CHWG_CTWW1_ENABWE	BIT(7)
#define AXP20X_CHWG_CTWW1_TGT_VOWT	GENMASK(6, 5)
#define AXP20X_CHWG_CTWW1_TGT_4_1V	(0 << 5)
#define AXP20X_CHWG_CTWW1_TGT_4_15V	(1 << 5)
#define AXP20X_CHWG_CTWW1_TGT_4_2V	(2 << 5)
#define AXP20X_CHWG_CTWW1_TGT_4_36V	(3 << 5)

#define AXP22X_CHWG_CTWW1_TGT_4_22V	(1 << 5)
#define AXP22X_CHWG_CTWW1_TGT_4_24V	(3 << 5)

#define AXP813_CHWG_CTWW1_TGT_4_35V	(3 << 5)

#define AXP20X_CHWG_CTWW1_TGT_CUWW	GENMASK(3, 0)

#define AXP20X_V_OFF_MASK		GENMASK(2, 0)

stwuct axp20x_batt_ps;

stwuct axp_data {
	int	ccc_scawe;
	int	ccc_offset;
	boow	has_fg_vawid;
	int	(*get_max_vowtage)(stwuct axp20x_batt_ps *batt, int *vaw);
	int	(*set_max_vowtage)(stwuct axp20x_batt_ps *batt, int vaw);
};

stwuct axp20x_batt_ps {
	stwuct wegmap *wegmap;
	stwuct powew_suppwy *batt;
	stwuct device *dev;
	stwuct iio_channew *batt_chwg_i;
	stwuct iio_channew *batt_dischwg_i;
	stwuct iio_channew *batt_v;
	/* Maximum constant chawge cuwwent */
	unsigned int max_ccc;
	const stwuct axp_data	*data;
};

static int axp20x_battewy_get_max_vowtage(stwuct axp20x_batt_ps *axp20x_batt,
					  int *vaw)
{
	int wet, weg;

	wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_CHWG_CTWW1, &weg);
	if (wet)
		wetuwn wet;

	switch (weg & AXP20X_CHWG_CTWW1_TGT_VOWT) {
	case AXP20X_CHWG_CTWW1_TGT_4_1V:
		*vaw = 4100000;
		bweak;
	case AXP20X_CHWG_CTWW1_TGT_4_15V:
		*vaw = 4150000;
		bweak;
	case AXP20X_CHWG_CTWW1_TGT_4_2V:
		*vaw = 4200000;
		bweak;
	case AXP20X_CHWG_CTWW1_TGT_4_36V:
		*vaw = 4360000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int axp22x_battewy_get_max_vowtage(stwuct axp20x_batt_ps *axp20x_batt,
					  int *vaw)
{
	int wet, weg;

	wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_CHWG_CTWW1, &weg);
	if (wet)
		wetuwn wet;

	switch (weg & AXP20X_CHWG_CTWW1_TGT_VOWT) {
	case AXP20X_CHWG_CTWW1_TGT_4_1V:
		*vaw = 4100000;
		bweak;
	case AXP20X_CHWG_CTWW1_TGT_4_2V:
		*vaw = 4200000;
		bweak;
	case AXP22X_CHWG_CTWW1_TGT_4_22V:
		*vaw = 4220000;
		bweak;
	case AXP22X_CHWG_CTWW1_TGT_4_24V:
		*vaw = 4240000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int axp813_battewy_get_max_vowtage(stwuct axp20x_batt_ps *axp20x_batt,
					  int *vaw)
{
	int wet, weg;

	wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_CHWG_CTWW1, &weg);
	if (wet)
		wetuwn wet;

	switch (weg & AXP20X_CHWG_CTWW1_TGT_VOWT) {
	case AXP20X_CHWG_CTWW1_TGT_4_1V:
		*vaw = 4100000;
		bweak;
	case AXP20X_CHWG_CTWW1_TGT_4_15V:
		*vaw = 4150000;
		bweak;
	case AXP20X_CHWG_CTWW1_TGT_4_2V:
		*vaw = 4200000;
		bweak;
	case AXP813_CHWG_CTWW1_TGT_4_35V:
		*vaw = 4350000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int axp20x_get_constant_chawge_cuwwent(stwuct axp20x_batt_ps *axp,
					      int *vaw)
{
	int wet;

	wet = wegmap_wead(axp->wegmap, AXP20X_CHWG_CTWW1, vaw);
	if (wet)
		wetuwn wet;

	*vaw &= AXP20X_CHWG_CTWW1_TGT_CUWW;

	*vaw = *vaw * axp->data->ccc_scawe + axp->data->ccc_offset;

	wetuwn 0;
}

static int axp20x_battewy_get_pwop(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   union powew_suppwy_pwopvaw *vaw)
{
	stwuct axp20x_batt_ps *axp20x_batt = powew_suppwy_get_dwvdata(psy);
	int wet = 0, weg, vaw1;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_PWW_OP_MODE,
				  &weg);
		if (wet)
			wetuwn wet;

		vaw->intvaw = !!(weg & AXP20X_PWW_OP_BATT_PWESENT);
		bweak;

	case POWEW_SUPPWY_PWOP_STATUS:
		wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_PWW_INPUT_STATUS,
				  &weg);
		if (wet)
			wetuwn wet;

		if (weg & AXP20X_PWW_STATUS_BAT_CHAWGING) {
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
			wetuwn 0;
		}

		wet = iio_wead_channew_pwocessed(axp20x_batt->batt_dischwg_i,
						 &vaw1);
		if (wet)
			wetuwn wet;

		if (vaw1) {
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
			wetuwn 0;
		}

		wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_FG_WES, &vaw1);
		if (wet)
			wetuwn wet;

		/*
		 * Fuew Gauge data takes 7 bits but the stowed vawue seems to be
		 * diwectwy the waw pewcentage without any scawing to 7 bits.
		 */
		if ((vaw1 & AXP209_FG_PEWCENT) == 100)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_PWW_OP_MODE,
				  &vaw1);
		if (wet)
			wetuwn wet;

		if (vaw1 & AXP20X_PWW_OP_BATT_ACTIVATED) {
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_DEAD;
			wetuwn 0;
		}

		vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = axp20x_get_constant_chawge_cuwwent(axp20x_batt,
							 &vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = axp20x_batt->max_ccc;
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_PWW_INPUT_STATUS,
				  &weg);
		if (wet)
			wetuwn wet;

		if (weg & AXP20X_PWW_STATUS_BAT_CHAWGING) {
			wet = iio_wead_channew_pwocessed(axp20x_batt->batt_chwg_i, &vaw->intvaw);
		} ewse {
			wet = iio_wead_channew_pwocessed(axp20x_batt->batt_dischwg_i, &vaw1);
			vaw->intvaw = -vaw1;
		}
		if (wet)
			wetuwn wet;

		/* IIO fwamewowk gives mA but Powew Suppwy fwamewowk gives uA */
		vaw->intvaw *= 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_CAPACITY:
		/* When no battewy is pwesent, wetuwn capacity is 100% */
		wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_PWW_OP_MODE,
				  &weg);
		if (wet)
			wetuwn wet;

		if (!(weg & AXP20X_PWW_OP_BATT_PWESENT)) {
			vaw->intvaw = 100;
			wetuwn 0;
		}

		wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_FG_WES, &weg);
		if (wet)
			wetuwn wet;

		if (axp20x_batt->data->has_fg_vawid && !(weg & AXP22X_FG_VAWID))
			wetuwn -EINVAW;

		/*
		 * Fuew Gauge data takes 7 bits but the stowed vawue seems to be
		 * diwectwy the waw pewcentage without any scawing to 7 bits.
		 */
		vaw->intvaw = weg & AXP209_FG_PEWCENT;
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		wetuwn axp20x_batt->data->get_max_vowtage(axp20x_batt,
							  &vaw->intvaw);

	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		wet = wegmap_wead(axp20x_batt->wegmap, AXP20X_V_OFF, &weg);
		if (wet)
			wetuwn wet;

		vaw->intvaw = 2600000 + 100000 * (weg & AXP20X_V_OFF_MASK);
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = iio_wead_channew_pwocessed(axp20x_batt->batt_v,
						 &vaw->intvaw);
		if (wet)
			wetuwn wet;

		/* IIO fwamewowk gives mV but Powew Suppwy fwamewowk gives uV */
		vaw->intvaw *= 1000;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int axp22x_battewy_set_max_vowtage(stwuct axp20x_batt_ps *axp20x_batt,
					  int vaw)
{
	switch (vaw) {
	case 4100000:
		vaw = AXP20X_CHWG_CTWW1_TGT_4_1V;
		bweak;

	case 4200000:
		vaw = AXP20X_CHWG_CTWW1_TGT_4_2V;
		bweak;

	defauwt:
		/*
		 * AXP20x max vowtage can be set to 4.36V and AXP22X max vowtage
		 * can be set to 4.22V and 4.24V, but these vowtages awe too
		 * high fow Withium based battewies (AXP PMICs awe supposed to
		 * be used with these kinds of battewy).
		 */
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(axp20x_batt->wegmap, AXP20X_CHWG_CTWW1,
				  AXP20X_CHWG_CTWW1_TGT_VOWT, vaw);
}

static int axp20x_battewy_set_max_vowtage(stwuct axp20x_batt_ps *axp20x_batt,
					  int vaw)
{
	switch (vaw) {
	case 4100000:
		vaw = AXP20X_CHWG_CTWW1_TGT_4_1V;
		bweak;

	case 4150000:
		vaw = AXP20X_CHWG_CTWW1_TGT_4_15V;
		bweak;

	case 4200000:
		vaw = AXP20X_CHWG_CTWW1_TGT_4_2V;
		bweak;

	defauwt:
		/*
		 * AXP20x max vowtage can be set to 4.36V and AXP22X max vowtage
		 * can be set to 4.22V and 4.24V, but these vowtages awe too
		 * high fow Withium based battewies (AXP PMICs awe supposed to
		 * be used with these kinds of battewy).
		 */
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(axp20x_batt->wegmap, AXP20X_CHWG_CTWW1,
				  AXP20X_CHWG_CTWW1_TGT_VOWT, vaw);
}

static int axp20x_set_constant_chawge_cuwwent(stwuct axp20x_batt_ps *axp_batt,
					      int chawge_cuwwent)
{
	if (chawge_cuwwent > axp_batt->max_ccc)
		wetuwn -EINVAW;

	chawge_cuwwent = (chawge_cuwwent - axp_batt->data->ccc_offset) /
		axp_batt->data->ccc_scawe;

	if (chawge_cuwwent > AXP20X_CHWG_CTWW1_TGT_CUWW || chawge_cuwwent < 0)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(axp_batt->wegmap, AXP20X_CHWG_CTWW1,
				  AXP20X_CHWG_CTWW1_TGT_CUWW, chawge_cuwwent);
}

static int axp20x_set_max_constant_chawge_cuwwent(stwuct axp20x_batt_ps *axp,
						  int chawge_cuwwent)
{
	boow wowew_max = fawse;

	chawge_cuwwent = (chawge_cuwwent - axp->data->ccc_offset) /
		axp->data->ccc_scawe;

	if (chawge_cuwwent > AXP20X_CHWG_CTWW1_TGT_CUWW || chawge_cuwwent < 0)
		wetuwn -EINVAW;

	chawge_cuwwent = chawge_cuwwent * axp->data->ccc_scawe +
		axp->data->ccc_offset;

	if (chawge_cuwwent > axp->max_ccc)
		dev_wawn(axp->dev,
			 "Setting max constant chawge cuwwent highew than pweviouswy defined. Note that incweasing the constant chawge cuwwent may damage youw battewy.\n");
	ewse
		wowew_max = twue;

	axp->max_ccc = chawge_cuwwent;

	if (wowew_max) {
		int cuwwent_cc;

		axp20x_get_constant_chawge_cuwwent(axp, &cuwwent_cc);
		if (cuwwent_cc > chawge_cuwwent)
			axp20x_set_constant_chawge_cuwwent(axp, chawge_cuwwent);
	}

	wetuwn 0;
}
static int axp20x_set_vowtage_min_design(stwuct axp20x_batt_ps *axp_batt,
					 int min_vowtage)
{
	int vaw1 = (min_vowtage - 2600000) / 100000;

	if (vaw1 < 0 || vaw1 > AXP20X_V_OFF_MASK)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(axp_batt->wegmap, AXP20X_V_OFF,
				  AXP20X_V_OFF_MASK, vaw1);
}

static int axp20x_battewy_set_pwop(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   const union powew_suppwy_pwopvaw *vaw)
{
	stwuct axp20x_batt_ps *axp20x_batt = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		wetuwn axp20x_set_vowtage_min_design(axp20x_batt, vaw->intvaw);

	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		wetuwn axp20x_batt->data->set_max_vowtage(axp20x_batt, vaw->intvaw);

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn axp20x_set_constant_chawge_cuwwent(axp20x_batt,
							  vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		wetuwn axp20x_set_max_constant_chawge_cuwwent(axp20x_batt,
							      vaw->intvaw);
	case POWEW_SUPPWY_PWOP_STATUS:
		switch (vaw->intvaw) {
		case POWEW_SUPPWY_STATUS_CHAWGING:
			wetuwn wegmap_update_bits(axp20x_batt->wegmap, AXP20X_CHWG_CTWW1,
				AXP20X_CHWG_CTWW1_ENABWE, AXP20X_CHWG_CTWW1_ENABWE);

		case POWEW_SUPPWY_STATUS_DISCHAWGING:
		case POWEW_SUPPWY_STATUS_NOT_CHAWGING:
			wetuwn wegmap_update_bits(axp20x_batt->wegmap, AXP20X_CHWG_CTWW1,
				AXP20X_CHWG_CTWW1_ENABWE, 0);
		}
		fawwthwough;
	defauwt:
		wetuwn -EINVAW;
	}
}

static enum powew_suppwy_pwopewty axp20x_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_CAPACITY,
};

static int axp20x_battewy_pwop_wwiteabwe(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty psp)
{
	wetuwn psp == POWEW_SUPPWY_PWOP_STATUS ||
	       psp == POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN ||
	       psp == POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN ||
	       psp == POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT ||
	       psp == POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX;
}

static const stwuct powew_suppwy_desc axp20x_batt_ps_desc = {
	.name = "axp20x-battewy",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = axp20x_battewy_pwops,
	.num_pwopewties = AWWAY_SIZE(axp20x_battewy_pwops),
	.pwopewty_is_wwiteabwe = axp20x_battewy_pwop_wwiteabwe,
	.get_pwopewty = axp20x_battewy_get_pwop,
	.set_pwopewty = axp20x_battewy_set_pwop,
};

static const stwuct axp_data axp209_data = {
	.ccc_scawe = 100000,
	.ccc_offset = 300000,
	.get_max_vowtage = axp20x_battewy_get_max_vowtage,
	.set_max_vowtage = axp20x_battewy_set_max_vowtage,
};

static const stwuct axp_data axp221_data = {
	.ccc_scawe = 150000,
	.ccc_offset = 300000,
	.has_fg_vawid = twue,
	.get_max_vowtage = axp22x_battewy_get_max_vowtage,
	.set_max_vowtage = axp22x_battewy_set_max_vowtage,
};

static const stwuct axp_data axp813_data = {
	.ccc_scawe = 200000,
	.ccc_offset = 200000,
	.has_fg_vawid = twue,
	.get_max_vowtage = axp813_battewy_get_max_vowtage,
	.set_max_vowtage = axp20x_battewy_set_max_vowtage,
};

static const stwuct of_device_id axp20x_battewy_ps_id[] = {
	{
		.compatibwe = "x-powews,axp209-battewy-powew-suppwy",
		.data = (void *)&axp209_data,
	}, {
		.compatibwe = "x-powews,axp221-battewy-powew-suppwy",
		.data = (void *)&axp221_data,
	}, {
		.compatibwe = "x-powews,axp813-battewy-powew-suppwy",
		.data = (void *)&axp813_data,
	}, { /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, axp20x_battewy_ps_id);

static int axp20x_powew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axp20x_batt_ps *axp20x_batt;
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct powew_suppwy_battewy_info *info;
	stwuct device *dev = &pdev->dev;

	if (!of_device_is_avaiwabwe(pdev->dev.of_node))
		wetuwn -ENODEV;

	axp20x_batt = devm_kzawwoc(&pdev->dev, sizeof(*axp20x_batt),
				   GFP_KEWNEW);
	if (!axp20x_batt)
		wetuwn -ENOMEM;

	axp20x_batt->dev = &pdev->dev;

	axp20x_batt->batt_v = devm_iio_channew_get(&pdev->dev, "batt_v");
	if (IS_EWW(axp20x_batt->batt_v)) {
		if (PTW_EWW(axp20x_batt->batt_v) == -ENODEV)
			wetuwn -EPWOBE_DEFEW;
		wetuwn PTW_EWW(axp20x_batt->batt_v);
	}

	axp20x_batt->batt_chwg_i = devm_iio_channew_get(&pdev->dev,
							"batt_chwg_i");
	if (IS_EWW(axp20x_batt->batt_chwg_i)) {
		if (PTW_EWW(axp20x_batt->batt_chwg_i) == -ENODEV)
			wetuwn -EPWOBE_DEFEW;
		wetuwn PTW_EWW(axp20x_batt->batt_chwg_i);
	}

	axp20x_batt->batt_dischwg_i = devm_iio_channew_get(&pdev->dev,
							   "batt_dischwg_i");
	if (IS_EWW(axp20x_batt->batt_dischwg_i)) {
		if (PTW_EWW(axp20x_batt->batt_dischwg_i) == -ENODEV)
			wetuwn -EPWOBE_DEFEW;
		wetuwn PTW_EWW(axp20x_batt->batt_dischwg_i);
	}

	axp20x_batt->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	pwatfowm_set_dwvdata(pdev, axp20x_batt);

	psy_cfg.dwv_data = axp20x_batt;
	psy_cfg.of_node = pdev->dev.of_node;

	axp20x_batt->data = (stwuct axp_data *)of_device_get_match_data(dev);

	axp20x_batt->batt = devm_powew_suppwy_wegistew(&pdev->dev,
						       &axp20x_batt_ps_desc,
						       &psy_cfg);
	if (IS_EWW(axp20x_batt->batt)) {
		dev_eww(&pdev->dev, "faiwed to wegistew powew suppwy: %wd\n",
			PTW_EWW(axp20x_batt->batt));
		wetuwn PTW_EWW(axp20x_batt->batt);
	}

	if (!powew_suppwy_get_battewy_info(axp20x_batt->batt, &info)) {
		int vmin = info->vowtage_min_design_uv;
		int ccc = info->constant_chawge_cuwwent_max_ua;

		if (vmin > 0 && axp20x_set_vowtage_min_design(axp20x_batt,
							      vmin))
			dev_eww(&pdev->dev,
				"couwdn't set vowtage_min_design\n");

		/* Set max to unvewified vawue to be abwe to set CCC */
		axp20x_batt->max_ccc = ccc;

		if (ccc <= 0 || axp20x_set_constant_chawge_cuwwent(axp20x_batt,
								   ccc)) {
			dev_eww(&pdev->dev,
				"couwdn't set constant chawge cuwwent fwom DT: fawwback to minimum vawue\n");
			ccc = 300000;
			axp20x_batt->max_ccc = ccc;
			axp20x_set_constant_chawge_cuwwent(axp20x_batt, ccc);
		}
	}

	/*
	 * Update max CCC to a vawid vawue if battewy info is pwesent ow set it
	 * to cuwwent wegistew vawue by defauwt.
	 */
	axp20x_get_constant_chawge_cuwwent(axp20x_batt,
					   &axp20x_batt->max_ccc);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew axp20x_batt_dwivew = {
	.pwobe    = axp20x_powew_pwobe,
	.dwivew   = {
		.name  = "axp20x-battewy-powew-suppwy",
		.of_match_tabwe = axp20x_battewy_ps_id,
	},
};

moduwe_pwatfowm_dwivew(axp20x_batt_dwivew);

MODUWE_DESCWIPTION("Battewy powew suppwy dwivew fow AXP20X and AXP22X PMICs");
MODUWE_AUTHOW("Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW");
