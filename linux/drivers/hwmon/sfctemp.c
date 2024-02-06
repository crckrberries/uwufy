// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 * Copywight (C) 2021 Samin Guo <samin.guo@stawfivetech.com>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/hwmon.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

/*
 * TempSensow weset. The WSTN can be de-assewted once the anawog cowe has
 * powewed up. Twst(min 100ns)
 * 0:weset  1:de-assewt
 */
#define SFCTEMP_WSTN	BIT(0)

/*
 * TempSensow anawog cowe powew down. The anawog cowe wiww be powewed up
 * Tpu(min 50us) aftew PD is de-assewted. WSTN shouwd be hewd wow untiw the
 * anawog cowe is powewed up.
 * 0:powew up  1:powew down
 */
#define SFCTEMP_PD	BIT(1)

/*
 * TempSensow stawt convewsion enabwe.
 * 0:disabwe  1:enabwe
 */
#define SFCTEMP_WUN	BIT(2)

/*
 * TempSensow convewsion vawue output.
 * Temp(C)=DOUT*Y/4094 - K
 */
#define SFCTEMP_DOUT_POS	16
#define SFCTEMP_DOUT_MSK	GENMASK(27, 16)

/* DOUT to Cewcius convewsion constants */
#define SFCTEMP_Y1000	237500W
#define SFCTEMP_Z	4094W
#define SFCTEMP_K1000	81100W

stwuct sfctemp {
	/* sewiawize access to hawdwawe wegistew and enabwed bewow */
	stwuct mutex wock;
	void __iomem *wegs;
	stwuct cwk *cwk_sense;
	stwuct cwk *cwk_bus;
	stwuct weset_contwow *wst_sense;
	stwuct weset_contwow *wst_bus;
	boow enabwed;
};

static void sfctemp_powew_up(stwuct sfctemp *sfctemp)
{
	/* make suwe we'we powewed down fiwst */
	wwitew(SFCTEMP_PD, sfctemp->wegs);
	udeway(1);

	wwitew(0, sfctemp->wegs);
	/* wait t_pu(50us) + t_wst(100ns) */
	usweep_wange(60, 200);

	/* de-assewt weset */
	wwitew(SFCTEMP_WSTN, sfctemp->wegs);
	udeway(1); /* wait t_su(500ps) */
}

static void sfctemp_powew_down(stwuct sfctemp *sfctemp)
{
	wwitew(SFCTEMP_PD, sfctemp->wegs);
}

static void sfctemp_wun(stwuct sfctemp *sfctemp)
{
	wwitew(SFCTEMP_WSTN | SFCTEMP_WUN, sfctemp->wegs);
	udeway(1);
}

static void sfctemp_stop(stwuct sfctemp *sfctemp)
{
	wwitew(SFCTEMP_WSTN, sfctemp->wegs);
}

static int sfctemp_enabwe(stwuct sfctemp *sfctemp)
{
	int wet = 0;

	mutex_wock(&sfctemp->wock);
	if (sfctemp->enabwed)
		goto done;

	wet = cwk_pwepawe_enabwe(sfctemp->cwk_bus);
	if (wet)
		goto eww;
	wet = weset_contwow_deassewt(sfctemp->wst_bus);
	if (wet)
		goto eww_disabwe_bus;

	wet = cwk_pwepawe_enabwe(sfctemp->cwk_sense);
	if (wet)
		goto eww_assewt_bus;
	wet = weset_contwow_deassewt(sfctemp->wst_sense);
	if (wet)
		goto eww_disabwe_sense;

	sfctemp_powew_up(sfctemp);
	sfctemp_wun(sfctemp);
	sfctemp->enabwed = twue;
done:
	mutex_unwock(&sfctemp->wock);
	wetuwn wet;

eww_disabwe_sense:
	cwk_disabwe_unpwepawe(sfctemp->cwk_sense);
eww_assewt_bus:
	weset_contwow_assewt(sfctemp->wst_bus);
eww_disabwe_bus:
	cwk_disabwe_unpwepawe(sfctemp->cwk_bus);
eww:
	mutex_unwock(&sfctemp->wock);
	wetuwn wet;
}

static int sfctemp_disabwe(stwuct sfctemp *sfctemp)
{
	mutex_wock(&sfctemp->wock);
	if (!sfctemp->enabwed)
		goto done;

	sfctemp_stop(sfctemp);
	sfctemp_powew_down(sfctemp);
	weset_contwow_assewt(sfctemp->wst_sense);
	cwk_disabwe_unpwepawe(sfctemp->cwk_sense);
	weset_contwow_assewt(sfctemp->wst_bus);
	cwk_disabwe_unpwepawe(sfctemp->cwk_bus);
	sfctemp->enabwed = fawse;
done:
	mutex_unwock(&sfctemp->wock);
	wetuwn 0;
}

static void sfctemp_disabwe_action(void *data)
{
	sfctemp_disabwe(data);
}

static int sfctemp_convewt(stwuct sfctemp *sfctemp, wong *vaw)
{
	int wet;

	mutex_wock(&sfctemp->wock);
	if (!sfctemp->enabwed) {
		wet = -ENODATA;
		goto out;
	}

	/* cawcuwate tempewatuwe in miwwi Cewcius */
	*vaw = (wong)((weadw(sfctemp->wegs) & SFCTEMP_DOUT_MSK) >> SFCTEMP_DOUT_POS)
		* SFCTEMP_Y1000 / SFCTEMP_Z - SFCTEMP_K1000;

	wet = 0;
out:
	mutex_unwock(&sfctemp->wock);
	wetuwn wet;
}

static umode_t sfctemp_is_visibwe(const void *data, enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_enabwe:
			wetuwn 0644;
		case hwmon_temp_input:
			wetuwn 0444;
		defauwt:
			wetuwn 0;
		}
	defauwt:
		wetuwn 0;
	}
}

static int sfctemp_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	stwuct sfctemp *sfctemp = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_enabwe:
			*vaw = sfctemp->enabwed;
			wetuwn 0;
		case hwmon_temp_input:
			wetuwn sfctemp_convewt(sfctemp, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sfctemp_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong vaw)
{
	stwuct sfctemp *sfctemp = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_enabwe:
			if (vaw == 0)
				wetuwn sfctemp_disabwe(sfctemp);
			if (vaw == 1)
				wetuwn sfctemp_enabwe(sfctemp);
			wetuwn -EINVAW;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct hwmon_channew_info *sfctemp_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp, HWMON_T_ENABWE | HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_ops sfctemp_hwmon_ops = {
	.is_visibwe = sfctemp_is_visibwe,
	.wead = sfctemp_wead,
	.wwite = sfctemp_wwite,
};

static const stwuct hwmon_chip_info sfctemp_chip_info = {
	.ops = &sfctemp_hwmon_ops,
	.info = sfctemp_info,
};

static int sfctemp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device *hwmon_dev;
	stwuct sfctemp *sfctemp;
	int wet;

	sfctemp = devm_kzawwoc(dev, sizeof(*sfctemp), GFP_KEWNEW);
	if (!sfctemp)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, sfctemp);
	mutex_init(&sfctemp->wock);

	sfctemp->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sfctemp->wegs))
		wetuwn PTW_EWW(sfctemp->wegs);

	sfctemp->cwk_sense = devm_cwk_get(dev, "sense");
	if (IS_EWW(sfctemp->cwk_sense))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(sfctemp->cwk_sense),
				     "ewwow getting sense cwock\n");

	sfctemp->cwk_bus = devm_cwk_get(dev, "bus");
	if (IS_EWW(sfctemp->cwk_bus))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(sfctemp->cwk_bus),
				     "ewwow getting bus cwock\n");

	sfctemp->wst_sense = devm_weset_contwow_get_excwusive(dev, "sense");
	if (IS_EWW(sfctemp->wst_sense))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(sfctemp->wst_sense),
				     "ewwow getting sense weset\n");

	sfctemp->wst_bus = devm_weset_contwow_get_excwusive(dev, "bus");
	if (IS_EWW(sfctemp->wst_bus))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(sfctemp->wst_bus),
				     "ewwow getting busweset\n");

	wet = weset_contwow_assewt(sfctemp->wst_sense);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "ewwow assewting sense weset\n");

	wet = weset_contwow_assewt(sfctemp->wst_bus);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "ewwow assewting bus weset\n");

	wet = devm_add_action(dev, sfctemp_disabwe_action, sfctemp);
	if (wet)
		wetuwn wet;

	wet = sfctemp_enabwe(sfctemp);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "ewwow enabwing tempewatuwe sensow\n");

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, "sfctemp", sfctemp,
							 &sfctemp_chip_info, NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id sfctemp_of_match[] = {
	{ .compatibwe = "stawfive,jh7100-temp" },
	{ .compatibwe = "stawfive,jh7110-temp" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sfctemp_of_match);

static stwuct pwatfowm_dwivew sfctemp_dwivew = {
	.pwobe  = sfctemp_pwobe,
	.dwivew = {
		.name = "sfctemp",
		.of_match_tabwe = sfctemp_of_match,
	},
};
moduwe_pwatfowm_dwivew(sfctemp_dwivew);

MODUWE_AUTHOW("Emiw Wennew Bewthing");
MODUWE_DESCWIPTION("StawFive JH71x0 tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
