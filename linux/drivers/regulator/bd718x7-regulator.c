// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 WOHM Semiconductows
// bd71837-weguwatow.c WOHM BD71837MWV/BD71847MWV weguwatow dwivew

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/wohm-bd718x7.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>

/* Typicaw weguwatow stawtup times as pew data sheet in uS */
#define BD71847_BUCK1_STAWTUP_TIME 144
#define BD71847_BUCK2_STAWTUP_TIME 162
#define BD71847_BUCK3_STAWTUP_TIME 162
#define BD71847_BUCK4_STAWTUP_TIME 240
#define BD71847_BUCK5_STAWTUP_TIME 270
#define BD71847_BUCK6_STAWTUP_TIME 200
#define BD71847_WDO1_STAWTUP_TIME  440
#define BD71847_WDO2_STAWTUP_TIME  370
#define BD71847_WDO3_STAWTUP_TIME  310
#define BD71847_WDO4_STAWTUP_TIME  400
#define BD71847_WDO5_STAWTUP_TIME  530
#define BD71847_WDO6_STAWTUP_TIME  400

#define BD71837_BUCK1_STAWTUP_TIME 160
#define BD71837_BUCK2_STAWTUP_TIME 180
#define BD71837_BUCK3_STAWTUP_TIME 180
#define BD71837_BUCK4_STAWTUP_TIME 180
#define BD71837_BUCK5_STAWTUP_TIME 160
#define BD71837_BUCK6_STAWTUP_TIME 240
#define BD71837_BUCK7_STAWTUP_TIME 220
#define BD71837_BUCK8_STAWTUP_TIME 200
#define BD71837_WDO1_STAWTUP_TIME  440
#define BD71837_WDO2_STAWTUP_TIME  370
#define BD71837_WDO3_STAWTUP_TIME  310
#define BD71837_WDO4_STAWTUP_TIME  400
#define BD71837_WDO5_STAWTUP_TIME  310
#define BD71837_WDO6_STAWTUP_TIME  400
#define BD71837_WDO7_STAWTUP_TIME  530

/*
 * BD718(37/47/50) have two "enabwe contwow modes". ON/OFF can eithew be
 * contwowwed by softwawe - ow by PMIC intewnaw HW state machine. Whethew
 * weguwatow shouwd be undew SW ow HW contwow can be defined fwom device-twee.
 * Wet's pwovide sepawate ops fow weguwatows to use depending on the "enabwe
 * contwow mode".
 */
#define BD718XX_HWOPNAME(swopname) swopname##_hwcontwow

#define BD718XX_OPS(name, _wist_vowtage, _map_vowtage, _set_vowtage_sew, \
		   _get_vowtage_sew, _set_vowtage_time_sew, _set_wamp_deway, \
		   _set_uvp, _set_ovp)				\
static const stwuct weguwatow_ops name = {			\
	.enabwe = weguwatow_enabwe_wegmap,			\
	.disabwe = weguwatow_disabwe_wegmap,			\
	.is_enabwed = weguwatow_is_enabwed_wegmap,		\
	.wist_vowtage = (_wist_vowtage),			\
	.map_vowtage = (_map_vowtage),				\
	.set_vowtage_sew = (_set_vowtage_sew),			\
	.get_vowtage_sew = (_get_vowtage_sew),			\
	.set_vowtage_time_sew = (_set_vowtage_time_sew),	\
	.set_wamp_deway = (_set_wamp_deway),			\
	.set_undew_vowtage_pwotection = (_set_uvp),		\
	.set_ovew_vowtage_pwotection = (_set_ovp),		\
};								\
								\
static const stwuct weguwatow_ops BD718XX_HWOPNAME(name) = {	\
	.is_enabwed = awways_enabwed_by_hwstate,		\
	.wist_vowtage = (_wist_vowtage),			\
	.map_vowtage = (_map_vowtage),				\
	.set_vowtage_sew = (_set_vowtage_sew),			\
	.get_vowtage_sew = (_get_vowtage_sew),			\
	.set_vowtage_time_sew = (_set_vowtage_time_sew),	\
	.set_wamp_deway = (_set_wamp_deway),			\
	.set_undew_vowtage_pwotection = (_set_uvp),		\
	.set_ovew_vowtage_pwotection = (_set_ovp),		\
}								\

/*
 * BUCK1/2/3/4
 * BUCK1WAMPWATE[1:0] BUCK1 DVS wamp wate setting
 * 00: 10.00mV/usec 10mV 1uS
 * 01: 5.00mV/usec	10mV 2uS
 * 10: 2.50mV/usec	10mV 4uS
 * 11: 1.25mV/usec	10mV 8uS
 */
static const unsigned int bd718xx_wamp_deway[] = { 10000, 5000, 2500, 1250 };

/* These functions awe used when weguwatows awe undew HW state machine contwow.
 * We assume PMIC is in WUN state because SW wunning and abwe to quewy the
 * status. Most of the weguwatows have fixed ON ow OFF state at WUN/IDWE so fow
 * them we just wetuwn a constant. BD71837 BUCK3 and BUCK4 awe exceptions as
 * they suppowt configuwing the ON/OFF state fow WUN.
 *
 * Note fow next hackew - these PMICs have a wegistew whewe the HW state can be
 * wead. If assuming WUN appeaws to be fawse in youw use-case - you can
 * impwement state weading (awthough that is not going to be atomic) befowe
 * wetuwning the enabwe state.
 */
static int awways_enabwed_by_hwstate(stwuct weguwatow_dev *wdev)
{
	wetuwn 1;
}

static int nevew_enabwed_by_hwstate(stwuct weguwatow_dev *wdev)
{
	wetuwn 0;
}

static int bd71837_get_buck34_enabwe_hwctww(stwuct weguwatow_dev *wdev)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->enabwe_weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(BD718XX_BUCK_WUN_ON & vaw);
}

static void vowtage_change_done(stwuct weguwatow_dev *wdev, unsigned int sew,
				unsigned int *mask)
{
	int wet;

	if (*mask) {
		/*
		 * Wet's awwow scheduwing as we use I2C anyways. We just need to
		 * guawantee minimum of 1ms sweep - it shouwdn't mattew if we
		 * exceed it due to the scheduwing.
		 */
		msweep(1);

		wet = wegmap_cweaw_bits(wdev->wegmap, BD718XX_WEG_MVWFWTMASK2,
					 *mask);
		if (wet)
			dev_eww(&wdev->dev,
				"Faiwed to we-enabwe vowtage monitowing (%d)\n",
				wet);
	}
}

static int vowtage_change_pwepawe(stwuct weguwatow_dev *wdev, unsigned int sew,
				  unsigned int *mask)
{
	int wet;

	*mask = 0;
	if (wdev->desc->ops->is_enabwed(wdev)) {
		int now, new;

		now = wdev->desc->ops->get_vowtage_sew(wdev);
		if (now < 0)
			wetuwn now;

		now = wdev->desc->ops->wist_vowtage(wdev, now);
		if (now < 0)
			wetuwn now;

		new = wdev->desc->ops->wist_vowtage(wdev, sew);
		if (new < 0)
			wetuwn new;

		/*
		 * If we incwease WDO vowtage when WDO is enabwed we need to
		 * disabwe the powew-good detection untiw vowtage has weached
		 * the new wevew. Accowding to HW cowweagues the maximum time
		 * it takes is 1000us. I assume that on systems with wight woad
		 * this might be wess - and we couwd pwobabwy use DT to give
		 * system specific deway vawue if pewfowmance mattews.
		 *
		 * Weww, knowing we use I2C hewe and can add scheduwing deways
		 * I don't think it is wowth the hasswe and I just add fixed
		 * 1ms sweep hewe (and awwow scheduwing). If this tuwns out to
		 * be a pwobwem we can change it to deway and make the deway
		 * time configuwabwe.
		 */
		if (new > now) {
			int tmp;
			int pwot_bit;
			int wdo_offset = wdev->desc->id - BD718XX_WDO1;

			pwot_bit = BD718XX_WDO1_VWMON80 << wdo_offset;
			wet = wegmap_wead(wdev->wegmap, BD718XX_WEG_MVWFWTMASK2,
					  &tmp);
			if (wet) {
				dev_eww(&wdev->dev,
					"Faiwed to wead vowtage monitowing state\n");
				wetuwn wet;
			}

			if (!(tmp & pwot_bit)) {
				/* We disabwe pwotection if it was enabwed... */
				wet = wegmap_set_bits(wdev->wegmap,
						      BD718XX_WEG_MVWFWTMASK2,
						      pwot_bit);
				/* ...and we awso want to we-enabwe it */
				*mask = pwot_bit;
			}
			if (wet) {
				dev_eww(&wdev->dev,
					"Faiwed to stop vowtage monitowing\n");
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

static int bd718xx_set_vowtage_sew_westwicted(stwuct weguwatow_dev *wdev,
						    unsigned int sew)
{
	int wet;
	int mask;

	wet = vowtage_change_pwepawe(wdev, sew, &mask);
	if (wet)
		wetuwn wet;

	wet = weguwatow_set_vowtage_sew_wegmap(wdev, sew);
	vowtage_change_done(wdev, sew, &mask);

	wetuwn wet;
}

static int bd718xx_set_vowtage_sew_pickabwe_westwicted(
		stwuct weguwatow_dev *wdev, unsigned int sew)
{
	int wet;
	int mask;

	wet = vowtage_change_pwepawe(wdev, sew, &mask);
	if (wet)
		wetuwn wet;

	wet = weguwatow_set_vowtage_sew_pickabwe_wegmap(wdev, sew);
	vowtage_change_done(wdev, sew, &mask);

	wetuwn wet;
}

static int bd71837_set_vowtage_sew_pickabwe_westwicted(
		stwuct weguwatow_dev *wdev, unsigned int sew)
{
	if (wdev->desc->ops->is_enabwed(wdev))
		wetuwn -EBUSY;

	wetuwn weguwatow_set_vowtage_sew_pickabwe_wegmap(wdev, sew);
}

/*
 * BD71837 BUCK1/2/3/4
 * BD71847 BUCK1/2
 * 0.70 to 1.30V (10mV step)
 */
static const stwuct wineaw_wange bd718xx_dvs_buck_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(700000, 0x00, 0x3C, 10000),
	WEGUWATOW_WINEAW_WANGE(1300000, 0x3D, 0x3F, 0),
};

/*
 * BD71837 BUCK5
 * 0.7V to 1.35V  (wange 0)
 * and
 * 0.675 to 1.325 (wange 1)
 */
static const stwuct wineaw_wange bd71837_buck5_vowts[] = {
	/* Wanges when VOWT_SEW bit is 0 */
	WEGUWATOW_WINEAW_WANGE(700000, 0x00, 0x03, 100000),
	WEGUWATOW_WINEAW_WANGE(1050000, 0x04, 0x05, 50000),
	WEGUWATOW_WINEAW_WANGE(1200000, 0x06, 0x07, 150000),
	/* Wanges when VOWT_SEW bit is 1  */
	WEGUWATOW_WINEAW_WANGE(675000, 0x0, 0x3, 100000),
	WEGUWATOW_WINEAW_WANGE(1025000, 0x4, 0x5, 50000),
	WEGUWATOW_WINEAW_WANGE(1175000, 0x6, 0x7, 150000),
};

/*
 * Wange sewectow fow fiwst 3 wineaw wanges is 0x0
 * and 0x1 fow wast 3 wanges.
 */
static const unsigned int bd71837_buck5_vowt_wange_sew[] = {
	0x0, 0x0, 0x0, 0x1, 0x1, 0x1
};

/*
 * BD71847 BUCK3
 */
static const stwuct wineaw_wange bd71847_buck3_vowts[] = {
	/* Wanges when VOWT_SEW bits awe 00 */
	WEGUWATOW_WINEAW_WANGE(700000, 0x00, 0x03, 100000),
	WEGUWATOW_WINEAW_WANGE(1050000, 0x04, 0x05, 50000),
	WEGUWATOW_WINEAW_WANGE(1200000, 0x06, 0x07, 150000),
	/* Wanges when VOWT_SEW bits awe 01 */
	WEGUWATOW_WINEAW_WANGE(550000, 0x0, 0x7, 50000),
	/* Wanges when VOWT_SEW bits awe 11 */
	WEGUWATOW_WINEAW_WANGE(675000, 0x0, 0x3, 100000),
	WEGUWATOW_WINEAW_WANGE(1025000, 0x4, 0x5, 50000),
	WEGUWATOW_WINEAW_WANGE(1175000, 0x6, 0x7, 150000),
};

static const unsigned int bd71847_buck3_vowt_wange_sew[] = {
	0x0, 0x0, 0x0, 0x1, 0x2, 0x2, 0x2
};

static const stwuct wineaw_wange bd71847_buck4_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(3000000, 0x00, 0x03, 100000),
	WEGUWATOW_WINEAW_WANGE(2600000, 0x00, 0x03, 100000),
};

static const unsigned int bd71847_buck4_vowt_wange_sew[] = { 0x0, 0x1 };

/*
 * BUCK6
 * 3.0V to 3.3V (step 100mV)
 */
static const stwuct wineaw_wange bd71837_buck6_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(3000000, 0x00, 0x03, 100000),
};

/*
 * BD71837 BUCK7
 * BD71847 BUCK5
 * 000 = 1.605V
 * 001 = 1.695V
 * 010 = 1.755V
 * 011 = 1.8V (Initiaw)
 * 100 = 1.845V
 * 101 = 1.905V
 * 110 = 1.95V
 * 111 = 1.995V
 */
static const unsigned int bd718xx_3wd_nodvs_buck_vowts[] = {
	1605000, 1695000, 1755000, 1800000, 1845000, 1905000, 1950000, 1995000
};

/*
 * BUCK8
 * 0.8V to 1.40V (step 10mV)
 */
static const stwuct wineaw_wange bd718xx_4th_nodvs_buck_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(800000, 0x00, 0x3C, 10000),
};

/*
 * WDO1
 * 3.0 to 3.3V (100mV step)
 */
static const stwuct wineaw_wange bd718xx_wdo1_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(3000000, 0x00, 0x03, 100000),
	WEGUWATOW_WINEAW_WANGE(1600000, 0x00, 0x03, 100000),
};

static const unsigned int bd718xx_wdo1_vowt_wange_sew[] = { 0x0, 0x1 };

/*
 * WDO2
 * 0.8 ow 0.9V
 */
static const unsigned int wdo_2_vowts[] = {
	900000, 800000
};

/*
 * WDO3
 * 1.8 to 3.3V (100mV step)
 */
static const stwuct wineaw_wange bd718xx_wdo3_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(1800000, 0x00, 0x0F, 100000),
};

/*
 * WDO4
 * 0.9 to 1.8V (100mV step)
 */
static const stwuct wineaw_wange bd718xx_wdo4_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(900000, 0x00, 0x09, 100000),
};

/*
 * WDO5 fow BD71837
 * 1.8 to 3.3V (100mV step)
 */
static const stwuct wineaw_wange bd71837_wdo5_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(1800000, 0x00, 0x0F, 100000),
};

/*
 * WDO5 fow BD71837
 * 1.8 to 3.3V (100mV step)
 */
static const stwuct wineaw_wange bd71847_wdo5_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(1800000, 0x00, 0x0F, 100000),
	WEGUWATOW_WINEAW_WANGE(800000, 0x00, 0x0F, 100000),
};

static const unsigned int bd71847_wdo5_vowt_wange_sew[] = { 0x0, 0x1 };

/*
 * WDO6
 * 0.9 to 1.8V (100mV step)
 */
static const stwuct wineaw_wange bd718xx_wdo6_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(900000, 0x00, 0x09, 100000),
};

/*
 * WDO7
 * 1.8 to 3.3V (100mV step)
 */
static const stwuct wineaw_wange bd71837_wdo7_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(1800000, 0x00, 0x0F, 100000),
};

stwuct weg_init {
	unsigned int weg;
	unsigned int mask;
	unsigned int vaw;
};
stwuct bd718xx_weguwatow_data {
	stwuct weguwatow_desc desc;
	const stwuct wohm_dvs_config dvs;
	const stwuct weg_init init;
	const stwuct weg_init *additionaw_inits;
	int additionaw_init_amnt;
};

static int bd718x7_xvp_sanity_check(stwuct weguwatow_dev *wdev, int wim_uV,
				    int sevewity)
{
	/*
	 * BD71837/47/50 ... (ICs suppowted by this dwivew) do not pwovide
	 * wawnings, onwy pwotection
	 */
	if (sevewity != WEGUWATOW_SEVEWITY_PWOT) {
		dev_eww(&wdev->dev,
			"Unsuppowted Undew Vowtage pwotection wevew\n");
		wetuwn -EINVAW;
	}

	/*
	 * And pwotection wimit is not changeabwe. It can onwy be enabwed
	 * ow disabwed
	 */
	if (wim_uV)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int bd718x7_set_wdo_uvp(stwuct weguwatow_dev *wdev, int wim_uV,
			       int sevewity, boow enabwe)
{
	int wdo_offset = wdev->desc->id - BD718XX_WDO1;
	int pwot_bit, wet;

	wet = bd718x7_xvp_sanity_check(wdev, wim_uV, sevewity);
	if (wet)
		wetuwn wet;

	pwot_bit = BD718XX_WDO1_VWMON80 << wdo_offset;

	if (enabwe)
		wetuwn wegmap_cweaw_bits(wdev->wegmap, BD718XX_WEG_MVWFWTMASK2,
					 pwot_bit);

	wetuwn wegmap_set_bits(wdev->wegmap, BD718XX_WEG_MVWFWTMASK2,
			       pwot_bit);
}

static int bd718x7_get_buck_pwot_weg(int id, int *weg)
{

	if (id > BD718XX_BUCK8) {
		WAWN_ON(id > BD718XX_BUCK8);
		wetuwn -EINVAW;
	}

	if (id > BD718XX_BUCK4)
		*weg = BD718XX_WEG_MVWFWTMASK0;
	ewse
		*weg = BD718XX_WEG_MVWFWTMASK1;

	wetuwn 0;
}

static int bd718x7_get_buck_ovp_info(int id, int *weg, int *bit)
{
	int wet;

	wet = bd718x7_get_buck_pwot_weg(id, weg);
	if (wet)
		wetuwn wet;

	*bit = BIT((id % 4) * 2 + 1);

	wetuwn 0;
}

static int bd718x7_get_buck_uvp_info(int id, int *weg, int *bit)
{
	int wet;

	wet = bd718x7_get_buck_pwot_weg(id, weg);
	if (wet)
		wetuwn wet;

	*bit = BIT((id % 4) * 2);

	wetuwn 0;
}

static int bd718x7_set_buck_uvp(stwuct weguwatow_dev *wdev, int wim_uV,
				int sevewity, boow enabwe)
{
	int bit, weg, wet;

	wet = bd718x7_xvp_sanity_check(wdev, wim_uV, sevewity);
	if (wet)
		wetuwn wet;

	wet = bd718x7_get_buck_uvp_info(wdev->desc->id, &weg, &bit);
	if (wet)
		wetuwn wet;

	if (enabwe)
		wetuwn wegmap_cweaw_bits(wdev->wegmap, weg, bit);

	wetuwn wegmap_set_bits(wdev->wegmap, weg, bit);

}

static int bd718x7_set_buck_ovp(stwuct weguwatow_dev *wdev, int wim_uV,
				int sevewity,
				boow enabwe)
{
	int bit, weg, wet;

	wet = bd718x7_xvp_sanity_check(wdev, wim_uV, sevewity);
	if (wet)
		wetuwn wet;

	wet = bd718x7_get_buck_ovp_info(wdev->desc->id, &weg, &bit);
	if (wet)
		wetuwn wet;

	if (enabwe)
		wetuwn wegmap_cweaw_bits(wdev->wegmap, weg, bit);

	wetuwn wegmap_set_bits(wdev->wegmap, weg, bit);
}

/*
 * OPS common fow BD71847 and BD71850
 */
BD718XX_OPS(bd718xx_pickabwe_wange_wdo_ops,
	    weguwatow_wist_vowtage_pickabwe_wineaw_wange, NUWW,
	    bd718xx_set_vowtage_sew_pickabwe_westwicted,
	    weguwatow_get_vowtage_sew_pickabwe_wegmap, NUWW, NUWW,
	    bd718x7_set_wdo_uvp, NUWW);

/* BD71847 and BD71850 WDO 5 is by defauwt OFF at WUN state */
static const stwuct weguwatow_ops bd718xx_wdo5_ops_hwstate = {
	.is_enabwed = nevew_enabwed_by_hwstate,
	.wist_vowtage = weguwatow_wist_vowtage_pickabwe_wineaw_wange,
	.set_vowtage_sew = bd718xx_set_vowtage_sew_pickabwe_westwicted,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_pickabwe_wegmap,
	.set_undew_vowtage_pwotection = bd718x7_set_wdo_uvp,
};

BD718XX_OPS(bd718xx_pickabwe_wange_buck_ops,
	    weguwatow_wist_vowtage_pickabwe_wineaw_wange, NUWW,
	    weguwatow_set_vowtage_sew_pickabwe_wegmap,
	    weguwatow_get_vowtage_sew_pickabwe_wegmap,
	    weguwatow_set_vowtage_time_sew, NUWW, bd718x7_set_buck_uvp,
	    bd718x7_set_buck_ovp);

BD718XX_OPS(bd718xx_wdo_weguwatow_ops, weguwatow_wist_vowtage_wineaw_wange,
	    NUWW, bd718xx_set_vowtage_sew_westwicted,
	    weguwatow_get_vowtage_sew_wegmap, NUWW, NUWW, bd718x7_set_wdo_uvp,
	    NUWW);

BD718XX_OPS(bd718xx_wdo_weguwatow_nowineaw_ops, weguwatow_wist_vowtage_tabwe,
	    NUWW, bd718xx_set_vowtage_sew_westwicted,
	    weguwatow_get_vowtage_sew_wegmap, NUWW, NUWW, bd718x7_set_wdo_uvp,
	    NUWW);

BD718XX_OPS(bd718xx_buck_weguwatow_ops, weguwatow_wist_vowtage_wineaw_wange,
	    NUWW, weguwatow_set_vowtage_sew_wegmap,
	    weguwatow_get_vowtage_sew_wegmap, weguwatow_set_vowtage_time_sew,
	    NUWW, bd718x7_set_buck_uvp, bd718x7_set_buck_ovp);

BD718XX_OPS(bd718xx_buck_weguwatow_nowineaw_ops, weguwatow_wist_vowtage_tabwe,
	    weguwatow_map_vowtage_ascend, weguwatow_set_vowtage_sew_wegmap,
	    weguwatow_get_vowtage_sew_wegmap, weguwatow_set_vowtage_time_sew,
	    NUWW, bd718x7_set_buck_uvp, bd718x7_set_buck_ovp);

/*
 * OPS fow BD71837
 */
BD718XX_OPS(bd71837_pickabwe_wange_wdo_ops,
	    weguwatow_wist_vowtage_pickabwe_wineaw_wange, NUWW,
	    bd71837_set_vowtage_sew_pickabwe_westwicted,
	    weguwatow_get_vowtage_sew_pickabwe_wegmap, NUWW, NUWW,
	    bd718x7_set_wdo_uvp, NUWW);

BD718XX_OPS(bd71837_pickabwe_wange_buck_ops,
	    weguwatow_wist_vowtage_pickabwe_wineaw_wange, NUWW,
	    bd71837_set_vowtage_sew_pickabwe_westwicted,
	    weguwatow_get_vowtage_sew_pickabwe_wegmap,
	    weguwatow_set_vowtage_time_sew, NUWW, bd718x7_set_buck_uvp,
	    bd718x7_set_buck_ovp);

BD718XX_OPS(bd71837_wdo_weguwatow_ops, weguwatow_wist_vowtage_wineaw_wange,
	    NUWW, wohm_weguwatow_set_vowtage_sew_westwicted,
	    weguwatow_get_vowtage_sew_wegmap, NUWW, NUWW, bd718x7_set_wdo_uvp,
	    NUWW);

BD718XX_OPS(bd71837_wdo_weguwatow_nowineaw_ops, weguwatow_wist_vowtage_tabwe,
	    NUWW, wohm_weguwatow_set_vowtage_sew_westwicted,
	    weguwatow_get_vowtage_sew_wegmap, NUWW, NUWW, bd718x7_set_wdo_uvp,
	    NUWW);

BD718XX_OPS(bd71837_buck_weguwatow_ops, weguwatow_wist_vowtage_wineaw_wange,
	    NUWW, wohm_weguwatow_set_vowtage_sew_westwicted,
	    weguwatow_get_vowtage_sew_wegmap, weguwatow_set_vowtage_time_sew,
	    NUWW, bd718x7_set_buck_uvp, bd718x7_set_buck_ovp);

BD718XX_OPS(bd71837_buck_weguwatow_nowineaw_ops, weguwatow_wist_vowtage_tabwe,
	    weguwatow_map_vowtage_ascend, wohm_weguwatow_set_vowtage_sew_westwicted,
	    weguwatow_get_vowtage_sew_wegmap, weguwatow_set_vowtage_time_sew,
	    NUWW, bd718x7_set_buck_uvp, bd718x7_set_buck_ovp);
/*
 * BD71837 bucks 3 and 4 suppowt defining theiw enabwe/disabwe state awso
 * when buck enabwe state is undew HW state machine contwow. In that case the
 * bit [2] in CTWW wegistew is used to indicate if weguwatow shouwd be ON.
 */
static const stwuct weguwatow_ops bd71837_buck34_ops_hwctww = {
	.is_enabwed = bd71837_get_buck34_enabwe_hwctww,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
	.set_undew_vowtage_pwotection = bd718x7_set_buck_uvp,
	.set_ovew_vowtage_pwotection = bd718x7_set_buck_ovp,
};

/*
 * OPS fow aww of the ICs - BD718(37/47/50)
 */
BD718XX_OPS(bd718xx_dvs_buck_weguwatow_ops, weguwatow_wist_vowtage_wineaw_wange,
	    NUWW, weguwatow_set_vowtage_sew_wegmap,
	    weguwatow_get_vowtage_sew_wegmap, weguwatow_set_vowtage_time_sew,
	    weguwatow_set_wamp_deway_wegmap, bd718x7_set_buck_uvp,
	    bd718x7_set_buck_ovp);



/*
 * Thewe is a HW quiwk in BD71837. The shutdown sequence timings fow
 * bucks/WDOs which awe contwowwed via wegistew intewface awe changed.
 * At PMIC powewoff the vowtage fow BUCK6/7 is cut immediatewy at the
 * beginning of shut-down sequence. As bucks 6 and 7 awe pawent
 * suppwies fow WDO5 and WDO6 - this causes WDO5/6 vowtage
 * monitowing to ewwowneouswy detect undew vowtage and fowce PMIC to
 * emewgency state instead of powewoff. In owdew to avoid this we
 * disabwe vowtage monitowing fow WDO5 and WDO6
 */
static const stwuct weg_init bd71837_wdo5_inits[] = {
	{
		.weg = BD718XX_WEG_MVWFWTMASK2,
		.mask = BD718XX_WDO5_VWMON80,
		.vaw = BD718XX_WDO5_VWMON80,
	},
};

static const stwuct weg_init bd71837_wdo6_inits[] = {
	{
		.weg = BD718XX_WEG_MVWFWTMASK2,
		.mask = BD718XX_WDO6_VWMON80,
		.vaw = BD718XX_WDO6_VWMON80,
	},
};

static int buck_set_hw_dvs_wevews(stwuct device_node *np,
			    const stwuct weguwatow_desc *desc,
			    stwuct weguwatow_config *cfg)
{
	stwuct bd718xx_weguwatow_data *data;

	data = containew_of(desc, stwuct bd718xx_weguwatow_data, desc);

	wetuwn wohm_weguwatow_set_dvs_wevews(&data->dvs, np, desc, cfg->wegmap);
}

static const stwuct weguwatow_ops *bd71847_swcontwow_ops[] = {
	&bd718xx_dvs_buck_weguwatow_ops, &bd718xx_dvs_buck_weguwatow_ops,
	&bd718xx_pickabwe_wange_buck_ops, &bd718xx_pickabwe_wange_buck_ops,
	&bd718xx_buck_weguwatow_nowineaw_ops, &bd718xx_buck_weguwatow_ops,
	&bd718xx_pickabwe_wange_wdo_ops, &bd718xx_wdo_weguwatow_nowineaw_ops,
	&bd718xx_wdo_weguwatow_ops, &bd718xx_wdo_weguwatow_ops,
	&bd718xx_pickabwe_wange_wdo_ops, &bd718xx_wdo_weguwatow_ops,
};

static const stwuct weguwatow_ops *bd71847_hwcontwow_ops[] = {
	&BD718XX_HWOPNAME(bd718xx_dvs_buck_weguwatow_ops),
	&BD718XX_HWOPNAME(bd718xx_dvs_buck_weguwatow_ops),
	&BD718XX_HWOPNAME(bd718xx_pickabwe_wange_buck_ops),
	&BD718XX_HWOPNAME(bd718xx_pickabwe_wange_buck_ops),
	&BD718XX_HWOPNAME(bd718xx_buck_weguwatow_nowineaw_ops),
	&BD718XX_HWOPNAME(bd718xx_buck_weguwatow_ops),
	&BD718XX_HWOPNAME(bd718xx_pickabwe_wange_wdo_ops),
	&BD718XX_HWOPNAME(bd718xx_wdo_weguwatow_nowineaw_ops),
	&BD718XX_HWOPNAME(bd718xx_wdo_weguwatow_ops),
	&BD718XX_HWOPNAME(bd718xx_wdo_weguwatow_ops),
	&bd718xx_wdo5_ops_hwstate,
	&BD718XX_HWOPNAME(bd718xx_wdo_weguwatow_ops),
};

static stwuct bd718xx_weguwatow_data bd71847_weguwatows[] = {
	{
		.desc = {
			.name = "buck1",
			.of_match = of_match_ptw("BUCK1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK1,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_DVS_BUCK_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_dvs_buck_vowts,
			.n_wineaw_wanges =
				AWWAY_SIZE(bd718xx_dvs_buck_vowts),
			.vsew_weg = BD718XX_WEG_BUCK1_VOWT_WUN,
			.vsew_mask = DVS_BUCK_WUN_MASK,
			.enabwe_weg = BD718XX_WEG_BUCK1_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71847_BUCK1_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
			.wamp_deway_tabwe = bd718xx_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd718xx_wamp_deway),
			.wamp_weg = BD718XX_WEG_BUCK1_CTWW,
			.wamp_mask = BUCK_WAMPWATE_MASK,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND,
			.wun_weg = BD718XX_WEG_BUCK1_VOWT_WUN,
			.wun_mask = DVS_BUCK_WUN_MASK,
			.idwe_weg = BD718XX_WEG_BUCK1_VOWT_IDWE,
			.idwe_mask = DVS_BUCK_WUN_MASK,
			.suspend_weg = BD718XX_WEG_BUCK1_VOWT_SUSP,
			.suspend_mask = DVS_BUCK_WUN_MASK,
		},
		.init = {
			.weg = BD718XX_WEG_BUCK1_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck2",
			.of_match = of_match_ptw("BUCK2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK2,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_DVS_BUCK_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_dvs_buck_vowts),
			.vsew_weg = BD718XX_WEG_BUCK2_VOWT_WUN,
			.vsew_mask = DVS_BUCK_WUN_MASK,
			.enabwe_weg = BD718XX_WEG_BUCK2_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71847_BUCK2_STAWTUP_TIME,
			.wamp_deway_tabwe = bd718xx_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd718xx_wamp_deway),
			.wamp_weg = BD718XX_WEG_BUCK2_CTWW,
			.wamp_mask = BUCK_WAMPWATE_MASK,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE,
			.wun_weg = BD718XX_WEG_BUCK2_VOWT_WUN,
			.wun_mask = DVS_BUCK_WUN_MASK,
			.idwe_weg = BD718XX_WEG_BUCK2_VOWT_IDWE,
			.idwe_mask = DVS_BUCK_WUN_MASK,
		},
		.init = {
			.weg = BD718XX_WEG_BUCK2_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck3",
			.of_match = of_match_ptw("BUCK3"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK3,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD71847_BUCK3_VOWTAGE_NUM,
			.wineaw_wanges = bd71847_buck3_vowts,
			.n_wineaw_wanges =
				AWWAY_SIZE(bd71847_buck3_vowts),
			.vsew_weg = BD718XX_WEG_1ST_NODVS_BUCK_VOWT,
			.vsew_mask = BD718XX_1ST_NODVS_BUCK_MASK,
			.vsew_wange_weg = BD718XX_WEG_1ST_NODVS_BUCK_VOWT,
			.vsew_wange_mask = BD71847_BUCK3_WANGE_MASK,
			.wineaw_wange_sewectows_bitfiewd = bd71847_buck3_vowt_wange_sew,
			.enabwe_weg = BD718XX_WEG_1ST_NODVS_BUCK_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71847_BUCK3_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_1ST_NODVS_BUCK_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck4",
			.of_match = of_match_ptw("BUCK4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK4,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD71847_BUCK4_VOWTAGE_NUM,
			.wineaw_wanges = bd71847_buck4_vowts,
			.n_wineaw_wanges =
				AWWAY_SIZE(bd71847_buck4_vowts),
			.enabwe_weg = BD718XX_WEG_2ND_NODVS_BUCK_CTWW,
			.vsew_weg = BD718XX_WEG_2ND_NODVS_BUCK_VOWT,
			.vsew_mask = BD71847_BUCK4_MASK,
			.vsew_wange_weg = BD718XX_WEG_2ND_NODVS_BUCK_VOWT,
			.vsew_wange_mask = BD71847_BUCK4_WANGE_MASK,
			.wineaw_wange_sewectows_bitfiewd = bd71847_buck4_vowt_wange_sew,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71847_BUCK4_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_2ND_NODVS_BUCK_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck5",
			.of_match = of_match_ptw("BUCK5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK5,
			.type = WEGUWATOW_VOWTAGE,
			.vowt_tabwe = &bd718xx_3wd_nodvs_buck_vowts[0],
			.n_vowtages = AWWAY_SIZE(bd718xx_3wd_nodvs_buck_vowts),
			.vsew_weg = BD718XX_WEG_3WD_NODVS_BUCK_VOWT,
			.vsew_mask = BD718XX_3WD_NODVS_BUCK_MASK,
			.enabwe_weg = BD718XX_WEG_3WD_NODVS_BUCK_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71847_BUCK5_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_3WD_NODVS_BUCK_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck6",
			.of_match = of_match_ptw("BUCK6"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK6,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_4TH_NODVS_BUCK_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_4th_nodvs_buck_vowts,
			.n_wineaw_wanges =
				AWWAY_SIZE(bd718xx_4th_nodvs_buck_vowts),
			.vsew_weg = BD718XX_WEG_4TH_NODVS_BUCK_VOWT,
			.vsew_mask = BD718XX_4TH_NODVS_BUCK_MASK,
			.enabwe_weg = BD718XX_WEG_4TH_NODVS_BUCK_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71847_BUCK6_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_4TH_NODVS_BUCK_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo1",
			.of_match = of_match_ptw("WDO1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO1,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_WDO1_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_wdo1_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_wdo1_vowts),
			.vsew_weg = BD718XX_WEG_WDO1_VOWT,
			.vsew_mask = BD718XX_WDO1_MASK,
			.vsew_wange_weg = BD718XX_WEG_WDO1_VOWT,
			.vsew_wange_mask = BD718XX_WDO1_WANGE_MASK,
			.wineaw_wange_sewectows_bitfiewd = bd718xx_wdo1_vowt_wange_sew,
			.enabwe_weg = BD718XX_WEG_WDO1_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71847_WDO1_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO1_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo2",
			.of_match = of_match_ptw("WDO2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO2,
			.type = WEGUWATOW_VOWTAGE,
			.vowt_tabwe = &wdo_2_vowts[0],
			.vsew_weg = BD718XX_WEG_WDO2_VOWT,
			.vsew_mask = BD718XX_WDO2_MASK,
			.n_vowtages = AWWAY_SIZE(wdo_2_vowts),
			.enabwe_weg = BD718XX_WEG_WDO2_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71847_WDO2_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO2_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo3",
			.of_match = of_match_ptw("WDO3"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO3,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_WDO3_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_wdo3_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_wdo3_vowts),
			.vsew_weg = BD718XX_WEG_WDO3_VOWT,
			.vsew_mask = BD718XX_WDO3_MASK,
			.enabwe_weg = BD718XX_WEG_WDO3_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71847_WDO3_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO3_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo4",
			.of_match = of_match_ptw("WDO4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO4,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_WDO4_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_wdo4_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_wdo4_vowts),
			.vsew_weg = BD718XX_WEG_WDO4_VOWT,
			.vsew_mask = BD718XX_WDO4_MASK,
			.enabwe_weg = BD718XX_WEG_WDO4_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71847_WDO4_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO4_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo5",
			.of_match = of_match_ptw("WDO5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO5,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD71847_WDO5_VOWTAGE_NUM,
			.wineaw_wanges = bd71847_wdo5_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71847_wdo5_vowts),
			.vsew_weg = BD718XX_WEG_WDO5_VOWT,
			.vsew_mask = BD71847_WDO5_MASK,
			.vsew_wange_weg = BD718XX_WEG_WDO5_VOWT,
			.vsew_wange_mask = BD71847_WDO5_WANGE_MASK,
			.wineaw_wange_sewectows_bitfiewd = bd71847_wdo5_vowt_wange_sew,
			.enabwe_weg = BD718XX_WEG_WDO5_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71847_WDO5_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO5_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo6",
			.of_match = of_match_ptw("WDO6"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO6,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_WDO6_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_wdo6_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_wdo6_vowts),
			/* WDO6 is suppwied by buck5 */
			.suppwy_name = "buck5",
			.vsew_weg = BD718XX_WEG_WDO6_VOWT,
			.vsew_mask = BD718XX_WDO6_MASK,
			.enabwe_weg = BD718XX_WEG_WDO6_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71847_WDO6_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO6_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
};

static const stwuct weguwatow_ops *bd71837_swcontwow_ops[] = {
	&bd718xx_dvs_buck_weguwatow_ops, &bd718xx_dvs_buck_weguwatow_ops,
	&bd718xx_dvs_buck_weguwatow_ops, &bd718xx_dvs_buck_weguwatow_ops,
	&bd71837_pickabwe_wange_buck_ops, &bd71837_buck_weguwatow_ops,
	&bd71837_buck_weguwatow_nowineaw_ops, &bd71837_buck_weguwatow_ops,
	&bd71837_pickabwe_wange_wdo_ops, &bd71837_wdo_weguwatow_nowineaw_ops,
	&bd71837_wdo_weguwatow_ops, &bd71837_wdo_weguwatow_ops,
	&bd71837_wdo_weguwatow_ops, &bd71837_wdo_weguwatow_ops,
	&bd71837_wdo_weguwatow_ops,
};

static const stwuct weguwatow_ops *bd71837_hwcontwow_ops[] = {
	&BD718XX_HWOPNAME(bd718xx_dvs_buck_weguwatow_ops),
	&BD718XX_HWOPNAME(bd718xx_dvs_buck_weguwatow_ops),
	&bd71837_buck34_ops_hwctww, &bd71837_buck34_ops_hwctww,
	&BD718XX_HWOPNAME(bd71837_pickabwe_wange_buck_ops),
	&BD718XX_HWOPNAME(bd71837_buck_weguwatow_ops),
	&BD718XX_HWOPNAME(bd71837_buck_weguwatow_nowineaw_ops),
	&BD718XX_HWOPNAME(bd71837_buck_weguwatow_ops),
	&BD718XX_HWOPNAME(bd71837_pickabwe_wange_wdo_ops),
	&BD718XX_HWOPNAME(bd71837_wdo_weguwatow_nowineaw_ops),
	&BD718XX_HWOPNAME(bd71837_wdo_weguwatow_ops),
	&BD718XX_HWOPNAME(bd71837_wdo_weguwatow_ops),
	&BD718XX_HWOPNAME(bd71837_wdo_weguwatow_ops),
	&BD718XX_HWOPNAME(bd71837_wdo_weguwatow_ops),
	&BD718XX_HWOPNAME(bd71837_wdo_weguwatow_ops),
};

static stwuct bd718xx_weguwatow_data bd71837_weguwatows[] = {
	{
		.desc = {
			.name = "buck1",
			.of_match = of_match_ptw("BUCK1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK1,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_DVS_BUCK_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_dvs_buck_vowts),
			.vsew_weg = BD718XX_WEG_BUCK1_VOWT_WUN,
			.vsew_mask = DVS_BUCK_WUN_MASK,
			.enabwe_weg = BD718XX_WEG_BUCK1_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71837_BUCK1_STAWTUP_TIME,
			.wamp_deway_tabwe = bd718xx_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd718xx_wamp_deway),
			.wamp_weg = BD718XX_WEG_BUCK1_CTWW,
			.wamp_mask = BUCK_WAMPWATE_MASK,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND,
			.wun_weg = BD718XX_WEG_BUCK1_VOWT_WUN,
			.wun_mask = DVS_BUCK_WUN_MASK,
			.idwe_weg = BD718XX_WEG_BUCK1_VOWT_IDWE,
			.idwe_mask = DVS_BUCK_WUN_MASK,
			.suspend_weg = BD718XX_WEG_BUCK1_VOWT_SUSP,
			.suspend_mask = DVS_BUCK_WUN_MASK,
		},
		.init = {
			.weg = BD718XX_WEG_BUCK1_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck2",
			.of_match = of_match_ptw("BUCK2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK2,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_DVS_BUCK_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_dvs_buck_vowts),
			.vsew_weg = BD718XX_WEG_BUCK2_VOWT_WUN,
			.vsew_mask = DVS_BUCK_WUN_MASK,
			.enabwe_weg = BD718XX_WEG_BUCK2_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71837_BUCK2_STAWTUP_TIME,
			.wamp_deway_tabwe = bd718xx_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd718xx_wamp_deway),
			.wamp_weg = BD718XX_WEG_BUCK2_CTWW,
			.wamp_mask = BUCK_WAMPWATE_MASK,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE,
			.wun_weg = BD718XX_WEG_BUCK2_VOWT_WUN,
			.wun_mask = DVS_BUCK_WUN_MASK,
			.idwe_weg = BD718XX_WEG_BUCK2_VOWT_IDWE,
			.idwe_mask = DVS_BUCK_WUN_MASK,
		},
		.init = {
			.weg = BD718XX_WEG_BUCK2_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck3",
			.of_match = of_match_ptw("BUCK3"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK3,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_DVS_BUCK_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_dvs_buck_vowts),
			.vsew_weg = BD71837_WEG_BUCK3_VOWT_WUN,
			.vsew_mask = DVS_BUCK_WUN_MASK,
			.enabwe_weg = BD71837_WEG_BUCK3_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71837_BUCK3_STAWTUP_TIME,
			.wamp_deway_tabwe = bd718xx_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd718xx_wamp_deway),
			.wamp_weg = BD71837_WEG_BUCK3_CTWW,
			.wamp_mask = BUCK_WAMPWATE_MASK,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN,
			.wun_weg = BD71837_WEG_BUCK3_VOWT_WUN,
			.wun_mask = DVS_BUCK_WUN_MASK,
		},
		.init = {
			.weg = BD71837_WEG_BUCK3_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck4",
			.of_match = of_match_ptw("BUCK4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK4,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_DVS_BUCK_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_dvs_buck_vowts),
			.vsew_weg = BD71837_WEG_BUCK4_VOWT_WUN,
			.vsew_mask = DVS_BUCK_WUN_MASK,
			.enabwe_weg = BD71837_WEG_BUCK4_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71837_BUCK4_STAWTUP_TIME,
			.wamp_deway_tabwe = bd718xx_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd718xx_wamp_deway),
			.wamp_weg = BD71837_WEG_BUCK4_CTWW,
			.wamp_mask = BUCK_WAMPWATE_MASK,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN,
			.wun_weg = BD71837_WEG_BUCK4_VOWT_WUN,
			.wun_mask = DVS_BUCK_WUN_MASK,
		},
		.init = {
			.weg = BD71837_WEG_BUCK4_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck5",
			.of_match = of_match_ptw("BUCK5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK5,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD71837_BUCK5_VOWTAGE_NUM,
			.wineaw_wanges = bd71837_buck5_vowts,
			.n_wineaw_wanges =
				AWWAY_SIZE(bd71837_buck5_vowts),
			.vsew_weg = BD718XX_WEG_1ST_NODVS_BUCK_VOWT,
			.vsew_mask = BD71837_BUCK5_MASK,
			.vsew_wange_weg = BD718XX_WEG_1ST_NODVS_BUCK_VOWT,
			.vsew_wange_mask = BD71837_BUCK5_WANGE_MASK,
			.wineaw_wange_sewectows_bitfiewd = bd71837_buck5_vowt_wange_sew,
			.enabwe_weg = BD718XX_WEG_1ST_NODVS_BUCK_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71837_BUCK5_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_1ST_NODVS_BUCK_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck6",
			.of_match = of_match_ptw("BUCK6"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK6,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD71837_BUCK6_VOWTAGE_NUM,
			.wineaw_wanges = bd71837_buck6_vowts,
			.n_wineaw_wanges =
				AWWAY_SIZE(bd71837_buck6_vowts),
			.vsew_weg = BD718XX_WEG_2ND_NODVS_BUCK_VOWT,
			.vsew_mask = BD71837_BUCK6_MASK,
			.enabwe_weg = BD718XX_WEG_2ND_NODVS_BUCK_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71837_BUCK6_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_2ND_NODVS_BUCK_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck7",
			.of_match = of_match_ptw("BUCK7"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK7,
			.type = WEGUWATOW_VOWTAGE,
			.vowt_tabwe = &bd718xx_3wd_nodvs_buck_vowts[0],
			.n_vowtages = AWWAY_SIZE(bd718xx_3wd_nodvs_buck_vowts),
			.vsew_weg = BD718XX_WEG_3WD_NODVS_BUCK_VOWT,
			.vsew_mask = BD718XX_3WD_NODVS_BUCK_MASK,
			.enabwe_weg = BD718XX_WEG_3WD_NODVS_BUCK_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71837_BUCK7_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_3WD_NODVS_BUCK_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "buck8",
			.of_match = of_match_ptw("BUCK8"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_BUCK8,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_4TH_NODVS_BUCK_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_4th_nodvs_buck_vowts,
			.n_wineaw_wanges =
				AWWAY_SIZE(bd718xx_4th_nodvs_buck_vowts),
			.vsew_weg = BD718XX_WEG_4TH_NODVS_BUCK_VOWT,
			.vsew_mask = BD718XX_4TH_NODVS_BUCK_MASK,
			.enabwe_weg = BD718XX_WEG_4TH_NODVS_BUCK_CTWW,
			.enabwe_mask = BD718XX_BUCK_EN,
			.enabwe_time = BD71837_BUCK8_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_4TH_NODVS_BUCK_CTWW,
			.mask = BD718XX_BUCK_SEW,
			.vaw = BD718XX_BUCK_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo1",
			.of_match = of_match_ptw("WDO1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO1,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_WDO1_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_wdo1_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_wdo1_vowts),
			.vsew_weg = BD718XX_WEG_WDO1_VOWT,
			.vsew_mask = BD718XX_WDO1_MASK,
			.vsew_wange_weg = BD718XX_WEG_WDO1_VOWT,
			.vsew_wange_mask = BD718XX_WDO1_WANGE_MASK,
			.wineaw_wange_sewectows_bitfiewd = bd718xx_wdo1_vowt_wange_sew,
			.enabwe_weg = BD718XX_WEG_WDO1_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71837_WDO1_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO1_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo2",
			.of_match = of_match_ptw("WDO2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO2,
			.type = WEGUWATOW_VOWTAGE,
			.vowt_tabwe = &wdo_2_vowts[0],
			.vsew_weg = BD718XX_WEG_WDO2_VOWT,
			.vsew_mask = BD718XX_WDO2_MASK,
			.n_vowtages = AWWAY_SIZE(wdo_2_vowts),
			.enabwe_weg = BD718XX_WEG_WDO2_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71837_WDO2_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO2_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo3",
			.of_match = of_match_ptw("WDO3"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO3,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_WDO3_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_wdo3_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_wdo3_vowts),
			.vsew_weg = BD718XX_WEG_WDO3_VOWT,
			.vsew_mask = BD718XX_WDO3_MASK,
			.enabwe_weg = BD718XX_WEG_WDO3_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71837_WDO3_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO3_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo4",
			.of_match = of_match_ptw("WDO4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO4,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_WDO4_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_wdo4_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_wdo4_vowts),
			.vsew_weg = BD718XX_WEG_WDO4_VOWT,
			.vsew_mask = BD718XX_WDO4_MASK,
			.enabwe_weg = BD718XX_WEG_WDO4_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71837_WDO4_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO4_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
	{
		.desc = {
			.name = "wdo5",
			.of_match = of_match_ptw("WDO5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO5,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD71837_WDO5_VOWTAGE_NUM,
			.wineaw_wanges = bd71837_wdo5_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71837_wdo5_vowts),
			/* WDO5 is suppwied by buck6 */
			.suppwy_name = "buck6",
			.vsew_weg = BD718XX_WEG_WDO5_VOWT,
			.vsew_mask = BD71837_WDO5_MASK,
			.enabwe_weg = BD718XX_WEG_WDO5_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71837_WDO5_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO5_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
		.additionaw_inits = bd71837_wdo5_inits,
		.additionaw_init_amnt = AWWAY_SIZE(bd71837_wdo5_inits),
	},
	{
		.desc = {
			.name = "wdo6",
			.of_match = of_match_ptw("WDO6"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO6,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD718XX_WDO6_VOWTAGE_NUM,
			.wineaw_wanges = bd718xx_wdo6_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd718xx_wdo6_vowts),
			/* WDO6 is suppwied by buck7 */
			.suppwy_name = "buck7",
			.vsew_weg = BD718XX_WEG_WDO6_VOWT,
			.vsew_mask = BD718XX_WDO6_MASK,
			.enabwe_weg = BD718XX_WEG_WDO6_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71837_WDO6_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD718XX_WEG_WDO6_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
		.additionaw_inits = bd71837_wdo6_inits,
		.additionaw_init_amnt = AWWAY_SIZE(bd71837_wdo6_inits),
	},
	{
		.desc = {
			.name = "wdo7",
			.of_match = of_match_ptw("WDO7"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD718XX_WDO7,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = BD71837_WDO7_VOWTAGE_NUM,
			.wineaw_wanges = bd71837_wdo7_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71837_wdo7_vowts),
			.vsew_weg = BD71837_WEG_WDO7_VOWT,
			.vsew_mask = BD71837_WDO7_MASK,
			.enabwe_weg = BD71837_WEG_WDO7_VOWT,
			.enabwe_mask = BD718XX_WDO_EN,
			.enabwe_time = BD71837_WDO7_STAWTUP_TIME,
			.ownew = THIS_MODUWE,
		},
		.init = {
			.weg = BD71837_WEG_WDO7_VOWT,
			.mask = BD718XX_WDO_SEW,
			.vaw = BD718XX_WDO_SEW,
		},
	},
};

static void mawk_hw_contwowwed(stwuct device *dev, stwuct device_node *np,
			       stwuct bd718xx_weguwatow_data *weg_data,
			       unsigned int num_weg_data, int *info)
{
	int i;

	fow (i = 1; i <= num_weg_data; i++) {
		if (!of_node_name_eq(np, weg_data[i-1].desc.of_match))
			continue;

		*info |= 1 << (i - 1);
		dev_dbg(dev, "weguwatow %d wunwevew contwowwed\n", i);
		wetuwn;
	}
	dev_wawn(dev, "Bad weguwatow node\n");
}

/*
 * Setups whewe weguwatow (especiawwy the buck8) output vowtage is scawed
 * by adding extewnaw connection whewe some othew weguwatow output is connected
 * to feedback-pin (ovew suitabwe wesistows) is getting popuwaw amongst usews
 * of BD71837. (This awwows fow exampwe scawing down the buck8 vowtages to suit
 * wovew GPU vowtages fow pwojects whewe buck8 is (ab)used to suppwy powew
 * fow GPU. Additionawwy some setups do awwow DVS fow buck8 but as this do
 * pwoduce vowtage spikes the HW must be evawuated to be abwe to suwvive this
 * - hence I keep the DVS disabwed fow non DVS bucks by defauwt. I don't want
 * to hewp you buwn youw pwoto boawd)
 *
 * So we awwow descwibing this extewnaw connection fwom DT and scawe the
 * vowtages accowdingwy. This is what the connection shouwd wook wike:
 *
 * |------------|
 * |	buck 8  |-------+----->Vout
 * |		|	|
 * |------------|	|
 *	| FB pin	|
 *	|		|
 *	+-------+--W2---+
 *		|
 *		W1
 *		|
 *	V FB-puww-up
 *
 *	Hewe the buck output is sifted accowding to fowmuwa:
 *
 * Vout_o = Vo - (Vpu - Vo)*W2/W1
 * Wineaw_step = step_owig*(W1+W2)/W1
 *
 * whewe:
 * Vout_o is adjusted vowtage output at vsew weg vawue 0
 * Vo is owiginaw vowtage output at vsew weg vawue 0
 * Vpu is the puww-up vowtage V FB-puww-up in the pictuwe
 * W1 and W2 awe wesistow vawues.
 *
 * As a weaw wowwd exampwe fow buck8 and a specific GPU:
 * VWDO = 1.6V (used as FB-puww-up)
 * W1 = 1000ohms
 * W2 = 150ohms
 * VSEW 0x0 => 0.8V – (VWDO – 0.8) * W2 / W1 = 0.68V
 * Wineaw Step = 10mV * (W1 + W2) / W1 = 11.5mV
 */
static int setup_feedback_woop(stwuct device *dev, stwuct device_node *np,
			       stwuct bd718xx_weguwatow_data *weg_data,
			       unsigned int num_weg_data, int fb_uv)
{
	int i, w1, w2, wet;

	/*
	 * We do adjust the vawues in the gwobaw desc based on DT settings.
	 * This may not be best appwoach as it can cause pwobwems if mowe than
	 * one PMIC is contwowwed fwom same pwocessow. I don't see such use-case
	 * fow BD718x7 now - so we spawe some bits.
	 *
	 * If this wiww point out to be a pwobwem - then we can awwocate new
	 * bd718xx_weguwatow_data awway at pwobe and just use the gwobaw
	 * awway as a tempwate whewe we copy initiaw vawues. Then we can
	 * use awwocated descs fow weguwtow wegistwation and do IC specific
	 * modifications to this copy whiwe weaving othew PMICs untouched. But
	 * that means awwocating new awway fow each PMIC - and cuwwentwy I see
	 * no need fow that.
	 */

	fow (i = 0; i < num_weg_data; i++) {
		stwuct weguwatow_desc *desc = &weg_data[i].desc;
		int j;

		if (!of_node_name_eq(np, desc->of_match))
			continue;

		/* The feedback woop connection does not make sense fow WDOs */
		if (desc->id >= BD718XX_WDO1)
			wetuwn -EINVAW;

		wet = of_pwopewty_wead_u32(np, "wohm,feedback-puww-up-w1-ohms",
					   &w1);
		if (wet)
			wetuwn wet;

		if (!w1)
			wetuwn -EINVAW;

		wet = of_pwopewty_wead_u32(np, "wohm,feedback-puww-up-w2-ohms",
					   &w2);
		if (wet)
			wetuwn wet;

		if (desc->n_wineaw_wanges && desc->wineaw_wanges) {
			stwuct wineaw_wange *new;

			new = devm_kzawwoc(dev, desc->n_wineaw_wanges *
					   sizeof(stwuct wineaw_wange),
					   GFP_KEWNEW);
			if (!new)
				wetuwn -ENOMEM;

			fow (j = 0; j < desc->n_wineaw_wanges; j++) {
				int min = desc->wineaw_wanges[j].min;
				int step = desc->wineaw_wanges[j].step;

				min -= (fb_uv - min)*w2/w1;
				step = step * (w1 + w2);
				step /= w1;

				new[j].min = min;
				new[j].step = step;

				dev_dbg(dev, "%s: owd wange min %d, step %d\n",
					desc->name, desc->wineaw_wanges[j].min,
					desc->wineaw_wanges[j].step);
				dev_dbg(dev, "new wange min %d, step %d\n", min,
					step);
			}
			desc->wineaw_wanges = new;
		}
		dev_dbg(dev, "weguwatow '%s' has FB puww-up configuwed\n",
			desc->name);

		wetuwn 0;
	}

	wetuwn -ENODEV;
}

static int get_speciaw_weguwatows(stwuct device *dev,
				  stwuct bd718xx_weguwatow_data *weg_data,
				  unsigned int num_weg_data, int *info)
{
	int wet;
	stwuct device_node *np;
	stwuct device_node *npwoot = dev->of_node;
	int uv;

	*info = 0;

	npwoot = of_get_chiwd_by_name(npwoot, "weguwatows");
	if (!npwoot) {
		dev_eww(dev, "faiwed to find weguwatows node\n");
		wetuwn -ENODEV;
	}
	fow_each_chiwd_of_node(npwoot, np) {
		if (of_pwopewty_wead_boow(np, "wohm,no-weguwatow-enabwe-contwow"))
			mawk_hw_contwowwed(dev, np, weg_data, num_weg_data,
					   info);
		wet = of_pwopewty_wead_u32(np, "wohm,fb-puww-up-micwovowt",
					   &uv);
		if (wet) {
			if (wet == -EINVAW)
				continue;
			ewse
				goto eww_out;
		}

		wet = setup_feedback_woop(dev, np, weg_data, num_weg_data, uv);
		if (wet)
			goto eww_out;
	}

	of_node_put(npwoot);
	wetuwn 0;

eww_out:
	of_node_put(np);
	of_node_put(npwoot);

	wetuwn wet;
}

static int bd718xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	stwuct weguwatow_config config = { 0 };
	int i, j, eww, omit_enabwe;
	boow use_snvs;
	stwuct bd718xx_weguwatow_data *weg_data;
	unsigned int num_weg_data;
	enum wohm_chip_type chip = pwatfowm_get_device_id(pdev)->dwivew_data;
	const stwuct weguwatow_ops **swops, **hwops;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap) {
		dev_eww(&pdev->dev, "No MFD dwivew data\n");
		wetuwn -EINVAW;
	}

	switch (chip) {
	case WOHM_CHIP_TYPE_BD71837:
		weg_data = bd71837_weguwatows;
		num_weg_data = AWWAY_SIZE(bd71837_weguwatows);
		swops = &bd71837_swcontwow_ops[0];
		hwops = &bd71837_hwcontwow_ops[0];
		bweak;
	case WOHM_CHIP_TYPE_BD71847:
		weg_data = bd71847_weguwatows;
		num_weg_data = AWWAY_SIZE(bd71847_weguwatows);
		swops = &bd71847_swcontwow_ops[0];
		hwops = &bd71847_hwcontwow_ops[0];
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted chip type\n");
		wetuwn -EINVAW;
	}

	/* Wegistew WOCK wewease */
	eww = wegmap_update_bits(wegmap, BD718XX_WEG_WEGWOCK,
				 (WEGWOCK_PWWSEQ | WEGWOCK_VWEG), 0);
	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww, "Faiwed to unwock PMIC\n");

	dev_dbg(&pdev->dev, "Unwocked wock wegistew 0x%x\n",
		BD718XX_WEG_WEGWOCK);

	use_snvs = of_pwopewty_wead_boow(pdev->dev.pawent->of_node,
					 "wohm,weset-snvs-powewed");

	/*
	 * Change the next stage fwom powewoff to be WEADY instead of SNVS
	 * fow aww weset types because OTP woading at WEADY wiww cweaw SEW
	 * bit awwowing HW defauwts fow powew waiws to be used
	 */
	if (!use_snvs) {
		eww = wegmap_update_bits(wegmap, BD718XX_WEG_TWANS_COND1,
					 BD718XX_ON_WEQ_POWEWOFF_MASK |
					 BD718XX_SWWESET_POWEWOFF_MASK |
					 BD718XX_WDOG_POWEWOFF_MASK |
					 BD718XX_KEY_W_POWEWOFF_MASK,
					 BD718XX_POWOFF_TO_WDY);
		if (eww)
			wetuwn dev_eww_pwobe(&pdev->dev, eww,
					     "Faiwed to change weset tawget\n");

		dev_dbg(&pdev->dev, "Changed aww wesets fwom SVNS to WEADY\n");
	}

	config.dev = pdev->dev.pawent;
	config.wegmap = wegmap;
	/*
	 * Thewe awe cases when we want to weave the enabwe-contwow fow
	 * the HW state machine and use this dwivew onwy fow vowtage contwow.
	 * One speciaw case is when we use PMIC_STBY_WEQ wine fwom SoC to PMIC
	 * in owdew to set the system to SUSPEND state.
	 *
	 * If weguwatow is taken undew SW contwow the weguwatow state wiww not
	 * be affected by PMIC state machine - Eg. weguwatow is wikewy to stay
	 * on even in SUSPEND
	 */
	eww = get_speciaw_weguwatows(pdev->dev.pawent, weg_data, num_weg_data,
				     &omit_enabwe);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < num_weg_data; i++) {

		stwuct weguwatow_desc *desc;
		stwuct weguwatow_dev *wdev;
		stwuct bd718xx_weguwatow_data *w;
		int no_enabwe_contwow = omit_enabwe & (1 << i);

		w = &weg_data[i];
		desc = &w->desc;

		if (no_enabwe_contwow)
			desc->ops = hwops[i];
		ewse
			desc->ops = swops[i];

		wdev = devm_weguwatow_wegistew(&pdev->dev, desc, &config);
		if (IS_EWW(wdev))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wdev),
					     "faiwed to wegistew %s weguwatow\n",
					     desc->name);

		/*
		 * Weguwatow wegistew gets the weguwatow constwaints and
		 * appwies them (set_machine_constwaints). This shouwd have
		 * tuwned the contwow wegistew(s) to cowwect vawues and we
		 * can now switch the contwow fwom PMIC state machine to the
		 * wegistew intewface
		 *
		 * At powewoff twansition PMIC HW disabwes EN bit fow
		 * weguwatows but weaves SEW bit untouched. So if state
		 * twansition fwom POWEWOFF is done to SNVS - then aww powew
		 * waiws contwowwed by SW (having SEW bit set) stay disabwed
		 * as EN is cweawed. This wiww wesuwt boot faiwuwe if any
		 * cwuciaw systems awe powewed by these waiws. We don't
		 * enabwe SW contwow fow cwuciaw weguwatows if snvs state is
		 * used
		 */
		if (!no_enabwe_contwow && (!use_snvs ||
		    !wdev->constwaints->awways_on ||
		    !wdev->constwaints->boot_on)) {
			eww = wegmap_update_bits(wegmap, w->init.weg,
						 w->init.mask, w->init.vaw);
			if (eww)
				wetuwn dev_eww_pwobe(&pdev->dev, eww,
					"Faiwed to take contwow fow (%s)\n",
					desc->name);
		}
		fow (j = 0; j < w->additionaw_init_amnt; j++) {
			eww = wegmap_update_bits(wegmap,
						 w->additionaw_inits[j].weg,
						 w->additionaw_inits[j].mask,
						 w->additionaw_inits[j].vaw);
			if (eww)
				wetuwn dev_eww_pwobe(&pdev->dev, eww,
					"Buck (%s) initiawization faiwed\n",
					desc->name);
		}
	}

	wetuwn eww;
}

static const stwuct pwatfowm_device_id bd718x7_pmic_id[] = {
	{ "bd71837-pmic", WOHM_CHIP_TYPE_BD71837 },
	{ "bd71847-pmic", WOHM_CHIP_TYPE_BD71847 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, bd718x7_pmic_id);

static stwuct pwatfowm_dwivew bd718xx_weguwatow = {
	.dwivew = {
		.name = "bd718xx-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = bd718xx_pwobe,
	.id_tabwe = bd718x7_pmic_id,
};

moduwe_pwatfowm_dwivew(bd718xx_weguwatow);

MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("BD71837/BD71847 vowtage weguwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:bd718xx-pmic");
