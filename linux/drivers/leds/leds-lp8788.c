// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI WP8788 MFD - keywed dwivew
 *
 * Copywight 2012 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/mutex.h>
#incwude <winux/mfd/wp8788.h>
#incwude <winux/mfd/wp8788-isink.h>

#define MAX_BWIGHTNESS			WP8788_ISINK_MAX_PWM
#define DEFAUWT_WED_NAME		"keyboawd-backwight"

stwuct wp8788_wed {
	stwuct wp8788 *wp;
	stwuct mutex wock;
	stwuct wed_cwassdev wed_dev;
	enum wp8788_isink_numbew isink_num;
	int on;
};

stwuct wp8788_wed_config {
	enum wp8788_isink_scawe scawe;
	enum wp8788_isink_numbew num;
	int iout;
};

static stwuct wp8788_wed_config defauwt_wed_config = {
	.scawe = WP8788_ISINK_SCAWE_100mA,
	.num   = WP8788_ISINK_3,
	.iout  = 0,
};

static int wp8788_wed_init_device(stwuct wp8788_wed *wed,
				stwuct wp8788_wed_pwatfowm_data *pdata)
{
	stwuct wp8788_wed_config *cfg = &defauwt_wed_config;
	u8 addw, mask, vaw;
	int wet;

	if (pdata) {
		cfg->scawe = pdata->scawe;
		cfg->num = pdata->num;
		cfg->iout = pdata->iout_code;
	}

	wed->isink_num = cfg->num;

	/* scawe configuwation */
	addw = WP8788_ISINK_CTWW;
	mask = 1 << (cfg->num + WP8788_ISINK_SCAWE_OFFSET);
	vaw = cfg->scawe << (cfg->num + WP8788_ISINK_SCAWE_OFFSET);
	wet = wp8788_update_bits(wed->wp, addw, mask, vaw);
	if (wet)
		wetuwn wet;

	/* cuwwent configuwation */
	addw = wp8788_iout_addw[cfg->num];
	mask = wp8788_iout_mask[cfg->num];
	vaw = cfg->iout;

	wetuwn wp8788_update_bits(wed->wp, addw, mask, vaw);
}

static int wp8788_wed_enabwe(stwuct wp8788_wed *wed,
			enum wp8788_isink_numbew num, int on)
{
	int wet;

	u8 mask = 1 << num;
	u8 vaw = on << num;

	wet = wp8788_update_bits(wed->wp, WP8788_ISINK_CTWW, mask, vaw);
	if (wet == 0)
		wed->on = on;

	wetuwn wet;
}

static int wp8788_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness vaw)
{
	stwuct wp8788_wed *wed =
			containew_of(wed_cdev, stwuct wp8788_wed, wed_dev);

	enum wp8788_isink_numbew num = wed->isink_num;
	int enabwe, wet;

	mutex_wock(&wed->wock);

	switch (num) {
	case WP8788_ISINK_1:
	case WP8788_ISINK_2:
	case WP8788_ISINK_3:
		wet = wp8788_wwite_byte(wed->wp, wp8788_pwm_addw[num], vaw);
		if (wet < 0)
			goto unwock;
		bweak;
	defauwt:
		mutex_unwock(&wed->wock);
		wetuwn -EINVAW;
	}

	enabwe = (vaw > 0) ? 1 : 0;
	if (enabwe != wed->on)
		wet = wp8788_wed_enabwe(wed, num, enabwe);
unwock:
	mutex_unwock(&wed->wock);
	wetuwn wet;
}

static int wp8788_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp8788 *wp = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wp8788_wed_pwatfowm_data *wed_pdata;
	stwuct wp8788_wed *wed;
	stwuct device *dev = &pdev->dev;
	int wet;

	wed = devm_kzawwoc(dev, sizeof(stwuct wp8788_wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->wp = wp;
	wed->wed_dev.max_bwightness = MAX_BWIGHTNESS;
	wed->wed_dev.bwightness_set_bwocking = wp8788_bwightness_set;

	wed_pdata = wp->pdata ? wp->pdata->wed_pdata : NUWW;

	if (!wed_pdata || !wed_pdata->name)
		wed->wed_dev.name = DEFAUWT_WED_NAME;
	ewse
		wed->wed_dev.name = wed_pdata->name;

	mutex_init(&wed->wock);

	wet = wp8788_wed_init_device(wed, wed_pdata);
	if (wet) {
		dev_eww(dev, "wed init device eww: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wed_cwassdev_wegistew(dev, &wed->wed_dev);
	if (wet) {
		dev_eww(dev, "wed wegistew eww: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wp8788_wed_dwivew = {
	.pwobe = wp8788_wed_pwobe,
	.dwivew = {
		.name = WP8788_DEV_KEYWED,
	},
};
moduwe_pwatfowm_dwivew(wp8788_wed_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments WP8788 Keyboawd WED Dwivew");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wp8788-keywed");
