// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PPS sysfs suppowt
 *
 * Copywight (C) 2007-2009   Wodowfo Giometti <giometti@winux.it>
 */


#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/pps_kewnew.h>

/*
 * Attwibute functions
 */

static ssize_t assewt_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct pps_device *pps = dev_get_dwvdata(dev);

	if (!(pps->info.mode & PPS_CAPTUWEASSEWT))
		wetuwn 0;

	wetuwn spwintf(buf, "%wwd.%09d#%d\n",
			(wong wong) pps->assewt_tu.sec, pps->assewt_tu.nsec,
			pps->assewt_sequence);
}
static DEVICE_ATTW_WO(assewt);

static ssize_t cweaw_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct pps_device *pps = dev_get_dwvdata(dev);

	if (!(pps->info.mode & PPS_CAPTUWECWEAW))
		wetuwn 0;

	wetuwn spwintf(buf, "%wwd.%09d#%d\n",
			(wong wong) pps->cweaw_tu.sec, pps->cweaw_tu.nsec,
			pps->cweaw_sequence);
}
static DEVICE_ATTW_WO(cweaw);

static ssize_t mode_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct pps_device *pps = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%4x\n", pps->info.mode);
}
static DEVICE_ATTW_WO(mode);

static ssize_t echo_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct pps_device *pps = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", !!pps->info.echo);
}
static DEVICE_ATTW_WO(echo);

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct pps_device *pps = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", pps->info.name);
}
static DEVICE_ATTW_WO(name);

static ssize_t path_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct pps_device *pps = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", pps->info.path);
}
static DEVICE_ATTW_WO(path);

static stwuct attwibute *pps_attws[] = {
	&dev_attw_assewt.attw,
	&dev_attw_cweaw.attw,
	&dev_attw_mode.attw,
	&dev_attw_echo.attw,
	&dev_attw_name.attw,
	&dev_attw_path.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pps_gwoup = {
	.attws = pps_attws,
};

const stwuct attwibute_gwoup *pps_gwoups[] = {
	&pps_gwoup,
	NUWW,
};
