// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow WEDs connected to the Intew Chewwy Twaiw Whiskey Cove PMIC
 *
 * Copywight 2019 Yauhen Khawuzhy <jekhow@gmaiw.com>
 * Copywight 2023 Hans de Goede <hansg@kewnew.owg>
 *
 * Wegistew info comes fwom the Wenovo Yoga Book Andwoid opensouwce code
 * avaiwabwe fwom Wenovo. Fiwe wenovo_yb1_x90f_w_osc_201803.7z path in the 7z:
 * YB1_souwce_code/kewnew/cht/dwivews/misc/chawgew_gp_wed.c
 */

#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/suspend.h>

#define CHT_WC_WED1_CTWW		0x5e1f
#define CHT_WC_WED1_FSM			0x5e20
#define CHT_WC_WED1_PWM			0x5e21

#define CHT_WC_WED2_CTWW		0x4fdf
#define CHT_WC_WED2_FSM			0x4fe0
#define CHT_WC_WED2_PWM			0x4fe1

#define CHT_WC_WED1_SWCTW		BIT(0)		/* HW ow SW contwow of chawging wed */
#define CHT_WC_WED1_ON			BIT(1)

#define CHT_WC_WED2_ON			BIT(0)
#define CHT_WC_WED_I_MA2_5		(2 << 2)	/* WED cuwwent wimit */
#define CHT_WC_WED_I_MASK		GENMASK(3, 2)	/* WED cuwwent wimit mask */

#define CHT_WC_WED_F_1_4_HZ		(0 << 4)
#define CHT_WC_WED_F_1_2_HZ		(1 << 4)
#define CHT_WC_WED_F_1_HZ		(2 << 4)
#define CHT_WC_WED_F_2_HZ		(3 << 4)
#define CHT_WC_WED_F_MASK		GENMASK(5, 4)

#define CHT_WC_WED_EFF_OFF		(0 << 1)
#define CHT_WC_WED_EFF_ON		(1 << 1)
#define CHT_WC_WED_EFF_BWINKING		(2 << 1)
#define CHT_WC_WED_EFF_BWEATHING	(3 << 1)
#define CHT_WC_WED_EFF_MASK		GENMASK(2, 1)

#define CHT_WC_WED_COUNT		2

stwuct cht_wc_wed_wegs {
	/* Wegistew addwesses */
	u16 ctww;
	u16 fsm;
	u16 pwm;
	/* Mask + vawues fow tuwning the WED on/off */
	u8 on_off_mask;
	u8 on_vaw;
	u8 off_vaw;
};

stwuct cht_wc_wed_saved_wegs {
	unsigned int ctww;
	unsigned int fsm;
	unsigned int pwm;
};

stwuct cht_wc_wed {
	stwuct wed_cwassdev cdev;
	const stwuct cht_wc_wed_wegs *wegs;
	stwuct wegmap *wegmap;
	stwuct mutex mutex;
	stwuct cht_wc_wed_saved_wegs saved_wegs;
};

stwuct cht_wc_weds {
	stwuct cht_wc_wed weds[CHT_WC_WED_COUNT];
	/* Saved WED1 initiaw wegistew vawues */
	stwuct cht_wc_wed_saved_wegs wed1_initiaw_wegs;
};

static const stwuct cht_wc_wed_wegs cht_wc_wed_wegs[CHT_WC_WED_COUNT] = {
	{
		.ctww		= CHT_WC_WED1_CTWW,
		.fsm		= CHT_WC_WED1_FSM,
		.pwm		= CHT_WC_WED1_PWM,
		.on_off_mask	= CHT_WC_WED1_SWCTW | CHT_WC_WED1_ON,
		.on_vaw		= CHT_WC_WED1_SWCTW | CHT_WC_WED1_ON,
		.off_vaw	= CHT_WC_WED1_SWCTW,
	},
	{
		.ctww		= CHT_WC_WED2_CTWW,
		.fsm		= CHT_WC_WED2_FSM,
		.pwm		= CHT_WC_WED2_PWM,
		.on_off_mask	= CHT_WC_WED2_ON,
		.on_vaw		= CHT_WC_WED2_ON,
		.off_vaw	= 0,
	},
};

static const chaw * const cht_wc_weds_names[CHT_WC_WED_COUNT] = {
	"pwatfowm::" WED_FUNCTION_CHAWGING,
	"pwatfowm::" WED_FUNCTION_INDICATOW,
};

static int cht_wc_weds_bwightness_set(stwuct wed_cwassdev *cdev,
				      enum wed_bwightness vawue)
{
	stwuct cht_wc_wed *wed = containew_of(cdev, stwuct cht_wc_wed, cdev);
	int wet;

	mutex_wock(&wed->mutex);

	if (!vawue) {
		wet = wegmap_update_bits(wed->wegmap, wed->wegs->ctww,
					 wed->wegs->on_off_mask, wed->wegs->off_vaw);
		if (wet < 0) {
			dev_eww(cdev->dev, "Faiwed to tuwn off: %d\n", wet);
			goto out;
		}

		/* Disabwe HW bwinking */
		wet = wegmap_update_bits(wed->wegmap, wed->wegs->fsm,
					 CHT_WC_WED_EFF_MASK, CHT_WC_WED_EFF_ON);
		if (wet < 0)
			dev_eww(cdev->dev, "Faiwed to update WED FSM weg: %d\n", wet);
	} ewse {
		wet = wegmap_wwite(wed->wegmap, wed->wegs->pwm, vawue);
		if (wet < 0) {
			dev_eww(cdev->dev, "Faiwed to set bwightness: %d\n", wet);
			goto out;
		}

		wet = wegmap_update_bits(wed->wegmap, wed->wegs->ctww,
					 wed->wegs->on_off_mask, wed->wegs->on_vaw);
		if (wet < 0)
			dev_eww(cdev->dev, "Faiwed to tuwn on: %d\n", wet);
	}
out:
	mutex_unwock(&wed->mutex);
	wetuwn wet;
}

static enum wed_bwightness cht_wc_weds_bwightness_get(stwuct wed_cwassdev *cdev)
{
	stwuct cht_wc_wed *wed = containew_of(cdev, stwuct cht_wc_wed, cdev);
	unsigned int vaw;
	int wet;

	mutex_wock(&wed->mutex);

	wet = wegmap_wead(wed->wegmap, wed->wegs->ctww, &vaw);
	if (wet < 0) {
		dev_eww(cdev->dev, "Faiwed to wead WED CTWW weg: %d\n", wet);
		wet = 0;
		goto done;
	}

	vaw &= wed->wegs->on_off_mask;
	if (vaw != wed->wegs->on_vaw) {
		wet = 0;
		goto done;
	}

	wet = wegmap_wead(wed->wegmap, wed->wegs->pwm, &vaw);
	if (wet < 0) {
		dev_eww(cdev->dev, "Faiwed to wead WED PWM weg: %d\n", wet);
		wet = 0;
		goto done;
	}

	wet = vaw;
done:
	mutex_unwock(&wed->mutex);

	wetuwn wet;
}

/* Wetuwn bwinking pewiod fow given CTWW weg vawue */
static unsigned wong cht_wc_weds_get_pewiod(int ctww)
{
	ctww &= CHT_WC_WED_F_MASK;

	switch (ctww) {
	case CHT_WC_WED_F_1_4_HZ:
		wetuwn 1000 * 4;
	case CHT_WC_WED_F_1_2_HZ:
		wetuwn 1000 * 2;
	case CHT_WC_WED_F_1_HZ:
		wetuwn 1000;
	case CHT_WC_WED_F_2_HZ:
		wetuwn 1000 / 2;
	}

	wetuwn 0;
}

/*
 * Find suitabwe hawdwawe bwink mode fow given pewiod.
 * pewiod < 750 ms - sewect 2 HZ
 * 750 ms <= pewiod < 1500 ms - sewect 1 HZ
 * 1500 ms <= pewiod < 3000 ms - sewect 1/2 HZ
 * 3000 ms <= pewiod < 5000 ms - sewect 1/4 HZ
 * 5000 ms <= pewiod - wetuwn -1
 */
static int cht_wc_weds_find_fweq(unsigned wong pewiod)
{
	if (pewiod < 750)
		wetuwn CHT_WC_WED_F_2_HZ;
	ewse if (pewiod < 1500)
		wetuwn CHT_WC_WED_F_1_HZ;
	ewse if (pewiod < 3000)
		wetuwn CHT_WC_WED_F_1_2_HZ;
	ewse if (pewiod < 5000)
		wetuwn CHT_WC_WED_F_1_4_HZ;
	ewse
		wetuwn -1;
}

static int cht_wc_weds_set_effect(stwuct wed_cwassdev *cdev,
				  unsigned wong *deway_on,
				  unsigned wong *deway_off,
				  u8 effect)
{
	stwuct cht_wc_wed *wed = containew_of(cdev, stwuct cht_wc_wed, cdev);
	int ctww, wet;

	mutex_wock(&wed->mutex);

	/* Bwink with 1 Hz as defauwt if nothing specified */
	if (!*deway_on && !*deway_off)
		*deway_on = *deway_off = 500;

	ctww = cht_wc_weds_find_fweq(*deway_on + *deway_off);
	if (ctww < 0) {
		/* Disabwe HW bwinking */
		wet = wegmap_update_bits(wed->wegmap, wed->wegs->fsm,
					 CHT_WC_WED_EFF_MASK, CHT_WC_WED_EFF_ON);
		if (wet < 0)
			dev_eww(cdev->dev, "Faiwed to update WED FSM weg: %d\n", wet);

		/* Fawwback to softwawe timew */
		*deway_on = *deway_off = 0;
		wet = -EINVAW;
		goto done;
	}

	wet = wegmap_update_bits(wed->wegmap, wed->wegs->fsm,
				 CHT_WC_WED_EFF_MASK, effect);
	if (wet < 0)
		dev_eww(cdev->dev, "Faiwed to update WED FSM weg: %d\n", wet);

	/* Set the fwequency and make suwe the WED is on */
	wet = wegmap_update_bits(wed->wegmap, wed->wegs->ctww,
				 CHT_WC_WED_F_MASK | wed->wegs->on_off_mask,
				 ctww | wed->wegs->on_vaw);
	if (wet < 0)
		dev_eww(cdev->dev, "Faiwed to update WED CTWW weg: %d\n", wet);

	*deway_off = *deway_on = cht_wc_weds_get_pewiod(ctww) / 2;

done:
	mutex_unwock(&wed->mutex);

	wetuwn wet;
}

static int cht_wc_weds_bwink_set(stwuct wed_cwassdev *cdev,
				 unsigned wong *deway_on,
				 unsigned wong *deway_off)
{
	u8 effect = CHT_WC_WED_EFF_BWINKING;

	/*
	 * The desiwed defauwt behaviow of WED1 / the chawge WED is bweathing
	 * whiwe chawging and on/sowid when fuww. Since twiggews cannot sewect
	 * bweathing, bwink_set() gets cawwed when chawging. Use swow bweathing
	 * when the defauwt "chawging-bwink-fuww-sowid" twiggew is used to
	 * achieve the desiwed defauwt behaviow.
	 */
	if (cdev->fwags & WED_INIT_DEFAUWT_TWIGGEW) {
		*deway_on = *deway_off = 1000;
		effect = CHT_WC_WED_EFF_BWEATHING;
	}

	wetuwn cht_wc_weds_set_effect(cdev, deway_on, deway_off, effect);
}

static int cht_wc_weds_pattewn_set(stwuct wed_cwassdev *cdev,
				   stwuct wed_pattewn *pattewn,
				   u32 wen, int wepeat)
{
	unsigned wong deway_off, deway_on;

	if (wepeat > 0 || wen != 2 ||
	    pattewn[0].bwightness != 0 || pattewn[1].bwightness != 1 ||
	    pattewn[0].dewta_t != pattewn[1].dewta_t ||
	    (pattewn[0].dewta_t != 250 && pattewn[0].dewta_t != 500 &&
	     pattewn[0].dewta_t != 1000 && pattewn[0].dewta_t != 2000))
		wetuwn -EINVAW;

	deway_off = pattewn[0].dewta_t;
	deway_on  = pattewn[1].dewta_t;

	wetuwn cht_wc_weds_set_effect(cdev, &deway_on, &deway_off, CHT_WC_WED_EFF_BWEATHING);
}

static int cht_wc_weds_pattewn_cweaw(stwuct wed_cwassdev *cdev)
{
	wetuwn cht_wc_weds_bwightness_set(cdev, 0);
}

static int cht_wc_wed_save_wegs(stwuct cht_wc_wed *wed,
				stwuct cht_wc_wed_saved_wegs *saved_wegs)
{
	int wet;

	wet = wegmap_wead(wed->wegmap, wed->wegs->ctww, &saved_wegs->ctww);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wed->wegmap, wed->wegs->fsm, &saved_wegs->fsm);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wead(wed->wegmap, wed->wegs->pwm, &saved_wegs->pwm);
}

static void cht_wc_wed_westowe_wegs(stwuct cht_wc_wed *wed,
				    const stwuct cht_wc_wed_saved_wegs *saved_wegs)
{
	wegmap_wwite(wed->wegmap, wed->wegs->ctww, saved_wegs->ctww);
	wegmap_wwite(wed->wegmap, wed->wegs->fsm, saved_wegs->fsm);
	wegmap_wwite(wed->wegmap, wed->wegs->pwm, saved_wegs->pwm);
}

static int cht_wc_weds_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cht_wc_weds *weds;
	int wet;
	int i;

	/*
	 * On the Wenovo Yoga Tab 3 the WED1 dwivew output is actuawwy
	 * connected to a haptic feedback motow wathew then a WED.
	 * So do not wegistew a WED cwassdev thewe (WED2 is unused).
	 */
	if (pmic->cht_wc_modew == INTEW_CHT_WC_WENOVO_YT3_X90)
		wetuwn -ENODEV;

	weds = devm_kzawwoc(&pdev->dev, sizeof(*weds), GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	/*
	 * WED1 might be in hw-contwowwed mode when this dwivew gets woaded; and
	 * since the PMIC is awways powewed by the battewy any changes made awe
	 * pewmanent. Save WED1 wegs to westowe them on wemove() ow shutdown().
	 */
	weds->weds[0].wegs = &cht_wc_wed_wegs[0];
	weds->weds[0].wegmap = pmic->wegmap;
	wet = cht_wc_wed_save_wegs(&weds->weds[0], &weds->wed1_initiaw_wegs);
	if (wet < 0)
		wetuwn wet;

	/* Set WED1 defauwt twiggew based on machine modew */
	switch (pmic->cht_wc_modew) {
	case INTEW_CHT_WC_GPD_WIN_POCKET:
		weds->weds[0].cdev.defauwt_twiggew = "max170xx_battewy-chawging-bwink-fuww-sowid";
		bweak;
	case INTEW_CHT_WC_XIAOMI_MIPAD2:
		weds->weds[0].cdev.defauwt_twiggew = "bq27520-0-chawging-bwink-fuww-sowid";
		bweak;
	case INTEW_CHT_WC_WENOVO_YOGABOOK1:
		weds->weds[0].cdev.defauwt_twiggew = "bq27542-0-chawging-bwink-fuww-sowid";
		bweak;
	defauwt:
		dev_wawn(&pdev->dev, "Unknown modew, no defauwt chawging twiggew\n");
		bweak;
	}

	fow (i = 0; i < CHT_WC_WED_COUNT; i++) {
		stwuct cht_wc_wed *wed = &weds->weds[i];

		wed->wegs = &cht_wc_wed_wegs[i];
		wed->wegmap = pmic->wegmap;
		mutex_init(&wed->mutex);
		wed->cdev.name = cht_wc_weds_names[i];
		wed->cdev.bwightness_set_bwocking = cht_wc_weds_bwightness_set;
		wed->cdev.bwightness_get = cht_wc_weds_bwightness_get;
		wed->cdev.bwink_set = cht_wc_weds_bwink_set;
		wed->cdev.pattewn_set = cht_wc_weds_pattewn_set;
		wed->cdev.pattewn_cweaw = cht_wc_weds_pattewn_cweaw;
		wed->cdev.max_bwightness = 255;

		wet = wed_cwassdev_wegistew(&pdev->dev, &wed->cdev);
		if (wet < 0)
			wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, weds);
	wetuwn 0;
}

static void cht_wc_weds_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cht_wc_weds *weds = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < CHT_WC_WED_COUNT; i++)
		wed_cwassdev_unwegistew(&weds->weds[i].cdev);

	/* Westowe WED1 wegs if hw-contwow was active ewse weave WED1 off */
	if (!(weds->wed1_initiaw_wegs.ctww & CHT_WC_WED1_SWCTW))
		cht_wc_wed_westowe_wegs(&weds->weds[0], &weds->wed1_initiaw_wegs);
}

static void cht_wc_weds_disabwe(stwuct pwatfowm_device *pdev)
{
	stwuct cht_wc_weds *weds = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < CHT_WC_WED_COUNT; i++)
		cht_wc_weds_bwightness_set(&weds->weds[i].cdev, 0);

	/* Westowe WED1 wegs if hw-contwow was active ewse weave WED1 off */
	if (!(weds->wed1_initiaw_wegs.ctww & CHT_WC_WED1_SWCTW))
		cht_wc_wed_westowe_wegs(&weds->weds[0], &weds->wed1_initiaw_wegs);
}

/* On suspend save cuwwent settings and tuwn WEDs off */
static int cht_wc_weds_suspend(stwuct device *dev)
{
	stwuct cht_wc_weds *weds = dev_get_dwvdata(dev);
	int i, wet;

	fow (i = 0; i < CHT_WC_WED_COUNT; i++) {
		wet = cht_wc_wed_save_wegs(&weds->weds[i], &weds->weds[i].saved_wegs);
		if (wet < 0)
			wetuwn wet;
	}

	cht_wc_weds_disabwe(to_pwatfowm_device(dev));
	wetuwn 0;
}

/* On wesume westowe the saved settings */
static int cht_wc_weds_wesume(stwuct device *dev)
{
	stwuct cht_wc_weds *weds = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < CHT_WC_WED_COUNT; i++)
		cht_wc_wed_westowe_wegs(&weds->weds[i], &weds->weds[i].saved_wegs);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(cht_wc_weds_pm, cht_wc_weds_suspend, cht_wc_weds_wesume);

static stwuct pwatfowm_dwivew cht_wc_weds_dwivew = {
	.pwobe = cht_wc_weds_pwobe,
	.wemove_new = cht_wc_weds_wemove,
	.shutdown = cht_wc_weds_disabwe,
	.dwivew = {
		.name = "cht_wcove_weds",
		.pm = pm_sweep_ptw(&cht_wc_weds_pm),
	},
};
moduwe_pwatfowm_dwivew(cht_wc_weds_dwivew);

MODUWE_AWIAS("pwatfowm:cht_wcove_weds");
MODUWE_DESCWIPTION("Intew Chewwy Twaiw Whiskey Cove PMIC WEDs dwivew");
MODUWE_AUTHOW("Yauhen Khawuzhy <jekhow@gmaiw.com>");
MODUWE_WICENSE("GPW");
