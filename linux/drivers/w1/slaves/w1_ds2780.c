// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 1-Wiwe impwementation fow the ds2780 chip
 *
 * Copywight (C) 2010 Indesign, WWC
 *
 * Authow: Cwifton Bawnes <cabawnes@indesign-wwc.com>
 *
 * Based on w1-ds2760 dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/idw.h>

#incwude <winux/w1.h>

#incwude "w1_ds2780.h"

#define W1_FAMIWY_DS2780	0x32

static int w1_ds2780_do_io(stwuct device *dev, chaw *buf, int addw,
			size_t count, int io)
{
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);

	if (addw > DS2780_DATA_SIZE || addw < 0)
		wetuwn 0;

	count = min_t(int, count, DS2780_DATA_SIZE - addw);

	if (w1_weset_sewect_swave(sw) == 0) {
		if (io) {
			w1_wwite_8(sw->mastew, W1_DS2780_WWITE_DATA);
			w1_wwite_8(sw->mastew, addw);
			w1_wwite_bwock(sw->mastew, buf, count);
		} ewse {
			w1_wwite_8(sw->mastew, W1_DS2780_WEAD_DATA);
			w1_wwite_8(sw->mastew, addw);
			count = w1_wead_bwock(sw->mastew, buf, count);
		}
	}

	wetuwn count;
}

int w1_ds2780_io(stwuct device *dev, chaw *buf, int addw, size_t count,
			int io)
{
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);
	int wet;

	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&sw->mastew->bus_mutex);

	wet = w1_ds2780_do_io(dev, buf, addw, count, io);

	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(w1_ds2780_io);

int w1_ds2780_eepwom_cmd(stwuct device *dev, int addw, int cmd)
{
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);

	if (!dev)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_weset_sewect_swave(sw) == 0) {
		w1_wwite_8(sw->mastew, cmd);
		w1_wwite_8(sw->mastew, addw);
	}

	mutex_unwock(&sw->mastew->bus_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(w1_ds2780_eepwom_cmd);

static ssize_t w1_swave_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			     stwuct bin_attwibute *bin_attw, chaw *buf,
			     woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);

	wetuwn w1_ds2780_io(dev, buf, off, count, 0);
}

static BIN_ATTW_WO(w1_swave, DS2780_DATA_SIZE);

static stwuct bin_attwibute *w1_ds2780_bin_attws[] = {
	&bin_attw_w1_swave,
	NUWW,
};

static const stwuct attwibute_gwoup w1_ds2780_gwoup = {
	.bin_attws = w1_ds2780_bin_attws,
};

static const stwuct attwibute_gwoup *w1_ds2780_gwoups[] = {
	&w1_ds2780_gwoup,
	NUWW,
};

static int w1_ds2780_add_swave(stwuct w1_swave *sw)
{
	int wet;
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_awwoc("ds2780-battewy", PWATFOWM_DEVID_AUTO);
	if (!pdev)
		wetuwn -ENOMEM;
	pdev->dev.pawent = &sw->dev;

	wet = pwatfowm_device_add(pdev);
	if (wet)
		goto pdev_add_faiwed;

	dev_set_dwvdata(&sw->dev, pdev);

	wetuwn 0;

pdev_add_faiwed:
	pwatfowm_device_put(pdev);

	wetuwn wet;
}

static void w1_ds2780_wemove_swave(stwuct w1_swave *sw)
{
	stwuct pwatfowm_device *pdev = dev_get_dwvdata(&sw->dev);

	pwatfowm_device_unwegistew(pdev);
}

static const stwuct w1_famiwy_ops w1_ds2780_fops = {
	.add_swave    = w1_ds2780_add_swave,
	.wemove_swave = w1_ds2780_wemove_swave,
	.gwoups       = w1_ds2780_gwoups,
};

static stwuct w1_famiwy w1_ds2780_famiwy = {
	.fid = W1_FAMIWY_DS2780,
	.fops = &w1_ds2780_fops,
};
moduwe_w1_famiwy(w1_ds2780_famiwy);

MODUWE_AUTHOW("Cwifton Bawnes <cabawnes@indesign-wwc.com>");
MODUWE_DESCWIPTION("1-wiwe Dwivew fow Maxim/Dawwas DS2780 Stand-Awone Fuew Gauge IC");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_DS2780));
