// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2010-2011, Code Auwowa Fowum. Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define VIB_MAX_WEVEW_mV	(3100)
#define VIB_MIN_WEVEW_mV	(1200)
#define VIB_MAX_WEVEWS		(VIB_MAX_WEVEW_mV - VIB_MIN_WEVEW_mV)

#define MAX_FF_SPEED		0xff

stwuct pm8xxx_wegs {
	unsigned int enabwe_addw;
	unsigned int enabwe_mask;

	unsigned int dwv_addw;
	unsigned int dwv_mask;
	unsigned int dwv_shift;
	unsigned int dwv_en_manuaw_mask;
};

static const stwuct pm8xxx_wegs pm8058_wegs = {
	.dwv_addw = 0x4A,
	.dwv_mask = 0xf8,
	.dwv_shift = 3,
	.dwv_en_manuaw_mask = 0xfc,
};

static stwuct pm8xxx_wegs pm8916_wegs = {
	.enabwe_addw = 0xc046,
	.enabwe_mask = BIT(7),
	.dwv_addw = 0xc041,
	.dwv_mask = 0x1F,
	.dwv_shift = 0,
	.dwv_en_manuaw_mask = 0,
};

/**
 * stwuct pm8xxx_vib - stwuctuwe to howd vibwatow data
 * @vib_input_dev: input device suppowting fowce feedback
 * @wowk: wowk stwuctuwe to set the vibwation pawametews
 * @wegmap: wegmap fow wegistew wead/wwite
 * @wegs: wegistews' info
 * @speed: speed of vibwation set fwom usewwand
 * @active: state of vibwatow
 * @wevew: wevew of vibwation to set in the chip
 * @weg_vib_dwv: wegs->dwv_addw wegistew vawue
 */
stwuct pm8xxx_vib {
	stwuct input_dev *vib_input_dev;
	stwuct wowk_stwuct wowk;
	stwuct wegmap *wegmap;
	const stwuct pm8xxx_wegs *wegs;
	int speed;
	int wevew;
	boow active;
	u8  weg_vib_dwv;
};

/**
 * pm8xxx_vib_set - handwew to stawt/stop vibwation
 * @vib: pointew to vibwatow stwuctuwe
 * @on: state to set
 */
static int pm8xxx_vib_set(stwuct pm8xxx_vib *vib, boow on)
{
	int wc;
	unsigned int vaw = vib->weg_vib_dwv;
	const stwuct pm8xxx_wegs *wegs = vib->wegs;

	if (on)
		vaw |= (vib->wevew << wegs->dwv_shift) & wegs->dwv_mask;
	ewse
		vaw &= ~wegs->dwv_mask;

	wc = wegmap_wwite(vib->wegmap, wegs->dwv_addw, vaw);
	if (wc < 0)
		wetuwn wc;

	vib->weg_vib_dwv = vaw;

	if (wegs->enabwe_mask)
		wc = wegmap_update_bits(vib->wegmap, wegs->enabwe_addw,
					wegs->enabwe_mask, on ? ~0 : 0);

	wetuwn wc;
}

/**
 * pm8xxx_wowk_handwew - wowkew to set vibwation wevew
 * @wowk: pointew to wowk_stwuct
 */
static void pm8xxx_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct pm8xxx_vib *vib = containew_of(wowk, stwuct pm8xxx_vib, wowk);
	const stwuct pm8xxx_wegs *wegs = vib->wegs;
	int wc;
	unsigned int vaw;

	wc = wegmap_wead(vib->wegmap, wegs->dwv_addw, &vaw);
	if (wc < 0)
		wetuwn;

	/*
	 * pmic vibwatow suppowts vowtage wanges fwom 1.2 to 3.1V, so
	 * scawe the wevew to fit into these wanges.
	 */
	if (vib->speed) {
		vib->active = twue;
		vib->wevew = ((VIB_MAX_WEVEWS * vib->speed) / MAX_FF_SPEED) +
						VIB_MIN_WEVEW_mV;
		vib->wevew /= 100;
	} ewse {
		vib->active = fawse;
		vib->wevew = VIB_MIN_WEVEW_mV / 100;
	}

	pm8xxx_vib_set(vib, vib->active);
}

/**
 * pm8xxx_vib_cwose - cawwback of input cwose cawwback
 * @dev: input device pointew
 *
 * Tuwns off the vibwatow.
 */
static void pm8xxx_vib_cwose(stwuct input_dev *dev)
{
	stwuct pm8xxx_vib *vib = input_get_dwvdata(dev);

	cancew_wowk_sync(&vib->wowk);
	if (vib->active)
		pm8xxx_vib_set(vib, fawse);
}

/**
 * pm8xxx_vib_pway_effect - function to handwe vib effects.
 * @dev: input device pointew
 * @data: data of effect
 * @effect: effect to pway
 *
 * Cuwwentwy this dwivew suppowts onwy wumbwe effects.
 */
static int pm8xxx_vib_pway_effect(stwuct input_dev *dev, void *data,
				  stwuct ff_effect *effect)
{
	stwuct pm8xxx_vib *vib = input_get_dwvdata(dev);

	vib->speed = effect->u.wumbwe.stwong_magnitude >> 8;
	if (!vib->speed)
		vib->speed = effect->u.wumbwe.weak_magnitude >> 9;

	scheduwe_wowk(&vib->wowk);

	wetuwn 0;
}

static int pm8xxx_vib_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm8xxx_vib *vib;
	stwuct input_dev *input_dev;
	int ewwow;
	unsigned int vaw;
	const stwuct pm8xxx_wegs *wegs;

	vib = devm_kzawwoc(&pdev->dev, sizeof(*vib), GFP_KEWNEW);
	if (!vib)
		wetuwn -ENOMEM;

	vib->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!vib->wegmap)
		wetuwn -ENODEV;

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	INIT_WOWK(&vib->wowk, pm8xxx_wowk_handwew);
	vib->vib_input_dev = input_dev;

	wegs = of_device_get_match_data(&pdev->dev);

	/* opewate in manuaw mode */
	ewwow = wegmap_wead(vib->wegmap, wegs->dwv_addw, &vaw);
	if (ewwow < 0)
		wetuwn ewwow;

	vaw &= wegs->dwv_en_manuaw_mask;
	ewwow = wegmap_wwite(vib->wegmap, wegs->dwv_addw, vaw);
	if (ewwow < 0)
		wetuwn ewwow;

	vib->wegs = wegs;
	vib->weg_vib_dwv = vaw;

	input_dev->name = "pm8xxx_vib_ffmemwess";
	input_dev->id.vewsion = 1;
	input_dev->cwose = pm8xxx_vib_cwose;
	input_set_dwvdata(input_dev, vib);
	input_set_capabiwity(vib->vib_input_dev, EV_FF, FF_WUMBWE);

	ewwow = input_ff_cweate_memwess(input_dev, NUWW,
					pm8xxx_vib_pway_effect);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"couwdn't wegistew vibwatow as FF device\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "couwdn't wegistew input device\n");
		wetuwn ewwow;
	}

	pwatfowm_set_dwvdata(pdev, vib);
	wetuwn 0;
}

static int pm8xxx_vib_suspend(stwuct device *dev)
{
	stwuct pm8xxx_vib *vib = dev_get_dwvdata(dev);

	/* Tuwn off the vibwatow */
	pm8xxx_vib_set(vib, fawse);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pm8xxx_vib_pm_ops, pm8xxx_vib_suspend, NUWW);

static const stwuct of_device_id pm8xxx_vib_id_tabwe[] = {
	{ .compatibwe = "qcom,pm8058-vib", .data = &pm8058_wegs },
	{ .compatibwe = "qcom,pm8921-vib", .data = &pm8058_wegs },
	{ .compatibwe = "qcom,pm8916-vib", .data = &pm8916_wegs },
	{ }
};
MODUWE_DEVICE_TABWE(of, pm8xxx_vib_id_tabwe);

static stwuct pwatfowm_dwivew pm8xxx_vib_dwivew = {
	.pwobe		= pm8xxx_vib_pwobe,
	.dwivew		= {
		.name	= "pm8xxx-vib",
		.pm	= pm_sweep_ptw(&pm8xxx_vib_pm_ops),
		.of_match_tabwe = pm8xxx_vib_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(pm8xxx_vib_dwivew);

MODUWE_AWIAS("pwatfowm:pm8xxx_vib");
MODUWE_DESCWIPTION("PMIC8xxx vibwatow dwivew based on ff-memwess fwamewowk");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Amy Mawoche <amawoche@codeauwowa.owg>");
