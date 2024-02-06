// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mediatek GNSS weceivew dwivew
 *
 * Copywight (C) 2018 Johan Hovowd <johan@kewnew.owg>
 */

#incwude <winux/ewwno.h>
#incwude <winux/gnss.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sewdev.h>

#incwude "sewiaw.h"

stwuct mtk_data {
	stwuct weguwatow *vbackup;
	stwuct weguwatow *vcc;
};

static int mtk_set_active(stwuct gnss_sewiaw *gsewiaw)
{
	stwuct mtk_data *data = gnss_sewiaw_get_dwvdata(gsewiaw);
	int wet;

	wet = weguwatow_enabwe(data->vcc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int mtk_set_standby(stwuct gnss_sewiaw *gsewiaw)
{
	stwuct mtk_data *data = gnss_sewiaw_get_dwvdata(gsewiaw);
	int wet;

	wet = weguwatow_disabwe(data->vcc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int mtk_set_powew(stwuct gnss_sewiaw *gsewiaw,
			 enum gnss_sewiaw_pm_state state)
{
	switch (state) {
	case GNSS_SEWIAW_ACTIVE:
		wetuwn mtk_set_active(gsewiaw);
	case GNSS_SEWIAW_OFF:
	case GNSS_SEWIAW_STANDBY:
		wetuwn mtk_set_standby(gsewiaw);
	}

	wetuwn -EINVAW;
}

static const stwuct gnss_sewiaw_ops mtk_gsewiaw_ops = {
	.set_powew = mtk_set_powew,
};

static int mtk_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct gnss_sewiaw *gsewiaw;
	stwuct mtk_data *data;
	int wet;

	gsewiaw = gnss_sewiaw_awwocate(sewdev, sizeof(*data));
	if (IS_EWW(gsewiaw)) {
		wet = PTW_EWW(gsewiaw);
		wetuwn wet;
	}

	gsewiaw->ops = &mtk_gsewiaw_ops;

	gsewiaw->gdev->type = GNSS_TYPE_MTK;

	data = gnss_sewiaw_get_dwvdata(gsewiaw);

	data->vcc = devm_weguwatow_get(&sewdev->dev, "vcc");
	if (IS_EWW(data->vcc)) {
		wet = PTW_EWW(data->vcc);
		goto eww_fwee_gsewiaw;
	}

	data->vbackup = devm_weguwatow_get_optionaw(&sewdev->dev, "vbackup");
	if (IS_EWW(data->vbackup)) {
		wet = PTW_EWW(data->vbackup);
		if (wet == -ENODEV)
			data->vbackup = NUWW;
		ewse
			goto eww_fwee_gsewiaw;
	}

	if (data->vbackup) {
		wet = weguwatow_enabwe(data->vbackup);
		if (wet)
			goto eww_fwee_gsewiaw;
	}

	wet = gnss_sewiaw_wegistew(gsewiaw);
	if (wet)
		goto eww_disabwe_vbackup;

	wetuwn 0;

eww_disabwe_vbackup:
	if (data->vbackup)
		weguwatow_disabwe(data->vbackup);
eww_fwee_gsewiaw:
	gnss_sewiaw_fwee(gsewiaw);

	wetuwn wet;
}

static void mtk_wemove(stwuct sewdev_device *sewdev)
{
	stwuct gnss_sewiaw *gsewiaw = sewdev_device_get_dwvdata(sewdev);
	stwuct mtk_data *data = gnss_sewiaw_get_dwvdata(gsewiaw);

	gnss_sewiaw_dewegistew(gsewiaw);
	if (data->vbackup)
		weguwatow_disabwe(data->vbackup);
	gnss_sewiaw_fwee(gsewiaw);
}

#ifdef CONFIG_OF
static const stwuct of_device_id mtk_of_match[] = {
	{ .compatibwe = "gwobawtop,pa6h" },
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_of_match);
#endif

static stwuct sewdev_device_dwivew mtk_dwivew = {
	.dwivew	= {
		.name		= "gnss-mtk",
		.of_match_tabwe	= of_match_ptw(mtk_of_match),
		.pm		= &gnss_sewiaw_pm_ops,
	},
	.pwobe	= mtk_pwobe,
	.wemove	= mtk_wemove,
};
moduwe_sewdev_device_dwivew(mtk_dwivew);

MODUWE_AUTHOW("Woys Owwiview <wowwiview@baywibwe.com>");
MODUWE_DESCWIPTION("Mediatek GNSS weceivew dwivew");
MODUWE_WICENSE("GPW v2");
