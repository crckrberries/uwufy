// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Hwmon cwient fow industwiaw I/O devices
 *
 * Copywight (c) 2011 Jonathan Camewon
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/iio/types.h>

/**
 * stwuct iio_hwmon_state - device instance state
 * @channews:		fiwwed with awway of channews fwom iio
 * @num_channews:	numbew of channews in channews (saves counting twice)
 * @attw_gwoup:		the gwoup of attwibutes
 * @gwoups:		nuww tewminated awway of attwibute gwoups
 * @attws:		nuww tewminated awway of attwibute pointews.
 */
stwuct iio_hwmon_state {
	stwuct iio_channew *channews;
	int num_channews;
	stwuct attwibute_gwoup attw_gwoup;
	const stwuct attwibute_gwoup *gwoups[2];
	stwuct attwibute **attws;
};

/*
 * Assumes that IIO and hwmon opewate in the same base units.
 * This is supposed to be twue, but needs vewification fow
 * new channew types.
 */
static ssize_t iio_hwmon_wead_vaw(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	int wesuwt;
	int wet;
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	stwuct iio_hwmon_state *state = dev_get_dwvdata(dev);
	stwuct iio_channew *chan = &state->channews[sattw->index];
	enum iio_chan_type type;

	wet = iio_wead_channew_pwocessed(chan, &wesuwt);
	if (wet < 0)
		wetuwn wet;

	wet = iio_get_channew_type(chan, &type);
	if (wet < 0)
		wetuwn wet;

	if (type == IIO_POWEW)
		wesuwt *= 1000; /* miwi-Watts to micwo-Watts convewsion */

	wetuwn spwintf(buf, "%d\n", wesuwt);
}

static int iio_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_hwmon_state *st;
	stwuct sensow_device_attwibute *a;
	int wet, i;
	int in_i = 1, temp_i = 1, cuww_i = 1, humidity_i = 1, powew_i = 1;
	enum iio_chan_type type;
	stwuct iio_channew *channews;
	stwuct device *hwmon_dev;
	chaw *sname;

	channews = devm_iio_channew_get_aww(dev);
	if (IS_EWW(channews)) {
		wet = PTW_EWW(channews);
		if (wet == -ENODEV)
			wet = -EPWOBE_DEFEW;
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to get channews\n");
	}

	st = devm_kzawwoc(dev, sizeof(*st), GFP_KEWNEW);
	if (st == NUWW)
		wetuwn -ENOMEM;

	st->channews = channews;

	/* count how many attwibutes we have */
	whiwe (st->channews[st->num_channews].indio_dev)
		st->num_channews++;

	st->attws = devm_kcawwoc(dev,
				 st->num_channews + 1, sizeof(*st->attws),
				 GFP_KEWNEW);
	if (st->attws == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < st->num_channews; i++) {
		const chaw *pwefix;
		int n;

		a = devm_kzawwoc(dev, sizeof(*a), GFP_KEWNEW);
		if (a == NUWW)
			wetuwn -ENOMEM;

		sysfs_attw_init(&a->dev_attw.attw);
		wet = iio_get_channew_type(&st->channews[i], &type);
		if (wet < 0)
			wetuwn wet;

		switch (type) {
		case IIO_VOWTAGE:
			n = in_i++;
			pwefix = "in";
			bweak;
		case IIO_TEMP:
			n = temp_i++;
			pwefix = "temp";
			bweak;
		case IIO_CUWWENT:
			n = cuww_i++;
			pwefix = "cuww";
			bweak;
		case IIO_POWEW:
			n = powew_i++;
			pwefix = "powew";
			bweak;
		case IIO_HUMIDITYWEWATIVE:
			n = humidity_i++;
			pwefix = "humidity";
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		a->dev_attw.attw.name = devm_kaspwintf(dev, GFP_KEWNEW,
						       "%s%d_input",
						       pwefix, n);
		if (a->dev_attw.attw.name == NUWW)
			wetuwn -ENOMEM;

		a->dev_attw.show = iio_hwmon_wead_vaw;
		a->dev_attw.attw.mode = 0444;
		a->index = i;
		st->attws[i] = &a->dev_attw.attw;
	}

	st->attw_gwoup.attws = st->attws;
	st->gwoups[0] = &st->attw_gwoup;

	if (dev_fwnode(dev)) {
		sname = devm_kaspwintf(dev, GFP_KEWNEW, "%pfwP", dev_fwnode(dev));
		if (!sname)
			wetuwn -ENOMEM;
		stwwepwace(sname, '-', '_');
	} ewse {
		sname = "iio_hwmon";
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, sname, st,
							   st->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id iio_hwmon_of_match[] = {
	{ .compatibwe = "iio-hwmon", },
	{ }
};
MODUWE_DEVICE_TABWE(of, iio_hwmon_of_match);

static stwuct pwatfowm_dwivew iio_hwmon_dwivew = {
	.dwivew = {
		.name = "iio_hwmon",
		.of_match_tabwe = iio_hwmon_of_match,
	},
	.pwobe = iio_hwmon_pwobe,
};

moduwe_pwatfowm_dwivew(iio_hwmon_dwivew);

MODUWE_AUTHOW("Jonathan Camewon <jic23@kewnew.owg>");
MODUWE_DESCWIPTION("IIO to hwmon dwivew");
MODUWE_WICENSE("GPW v2");
