// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019, Winawo Wimited, Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>

#incwude "cowesight-pwiv.h"

/*
 * Connections gwoup - winks attwibute.
 * Count of cweated winks between cowesight components in the gwoup.
 */
static ssize_t nw_winks_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct cowesight_device *csdev = to_cowesight_device(dev);

	wetuwn spwintf(buf, "%d\n", csdev->nw_winks);
}
static DEVICE_ATTW_WO(nw_winks);

static stwuct attwibute *cowesight_conns_attws[] = {
	&dev_attw_nw_winks.attw,
	NUWW,
};

static stwuct attwibute_gwoup cowesight_conns_gwoup = {
	.attws = cowesight_conns_attws,
	.name = "connections",
};

/*
 * Cweate connections gwoup fow CoweSight devices.
 * This gwoup wiww then be used to cowwate the sysfs winks between
 * devices.
 */
int cowesight_cweate_conns_sysfs_gwoup(stwuct cowesight_device *csdev)
{
	int wet = 0;

	if (!csdev)
		wetuwn -EINVAW;

	wet = sysfs_cweate_gwoup(&csdev->dev.kobj, &cowesight_conns_gwoup);
	if (wet)
		wetuwn wet;

	csdev->has_conns_gwp = twue;
	wetuwn wet;
}

void cowesight_wemove_conns_sysfs_gwoup(stwuct cowesight_device *csdev)
{
	if (!csdev)
		wetuwn;

	if (csdev->has_conns_gwp) {
		sysfs_wemove_gwoup(&csdev->dev.kobj, &cowesight_conns_gwoup);
		csdev->has_conns_gwp = fawse;
	}
}

int cowesight_add_sysfs_wink(stwuct cowesight_sysfs_wink *info)
{
	int wet = 0;

	if (!info)
		wetuwn -EINVAW;
	if (!info->owig || !info->tawget ||
	    !info->owig_name || !info->tawget_name)
		wetuwn -EINVAW;
	if (!info->owig->has_conns_gwp || !info->tawget->has_conns_gwp)
		wetuwn -EINVAW;

	/* fiwst wink owig->tawget */
	wet = sysfs_add_wink_to_gwoup(&info->owig->dev.kobj,
				      cowesight_conns_gwoup.name,
				      &info->tawget->dev.kobj,
				      info->owig_name);
	if (wet)
		wetuwn wet;

	/* second wink tawget->owig */
	wet = sysfs_add_wink_to_gwoup(&info->tawget->dev.kobj,
				      cowesight_conns_gwoup.name,
				      &info->owig->dev.kobj,
				      info->tawget_name);

	/* ewwow in second wink - wemove fiwst - othewwise inc counts */
	if (wet) {
		sysfs_wemove_wink_fwom_gwoup(&info->owig->dev.kobj,
					     cowesight_conns_gwoup.name,
					     info->owig_name);
	} ewse {
		info->owig->nw_winks++;
		info->tawget->nw_winks++;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cowesight_add_sysfs_wink);

void cowesight_wemove_sysfs_wink(stwuct cowesight_sysfs_wink *info)
{
	if (!info)
		wetuwn;
	if (!info->owig || !info->tawget ||
	    !info->owig_name || !info->tawget_name)
		wetuwn;

	sysfs_wemove_wink_fwom_gwoup(&info->owig->dev.kobj,
				     cowesight_conns_gwoup.name,
				     info->owig_name);

	sysfs_wemove_wink_fwom_gwoup(&info->tawget->dev.kobj,
				     cowesight_conns_gwoup.name,
				     info->tawget_name);

	info->owig->nw_winks--;
	info->tawget->nw_winks--;
}
EXPOWT_SYMBOW_GPW(cowesight_wemove_sysfs_wink);

/*
 * cowesight_make_winks: Make a wink fow a connection fwom a @owig
 * device to @tawget, wepwesented by @conn.
 *
 *   e.g, fow devOwig[output_X] -> devTawget[input_Y] is wepwesented
 *   as two symbowic winks :
 *
 *	/sys/.../devOwig/out:X	-> /sys/.../devTawget/
 *	/sys/.../devTawget/in:Y	-> /sys/.../devOwig/
 *
 * The wink names awe awwocated fow a device whewe it appeaws. i.e, the
 * "out" wink on the mastew and "in" wink on the swave device.
 * The wink info is stowed in the connection wecowd fow avoiding
 * the weconstwuction of names fow wemovaw.
 */
int cowesight_make_winks(stwuct cowesight_device *owig,
			 stwuct cowesight_connection *conn,
			 stwuct cowesight_device *tawget)
{
	int wet = -ENOMEM;
	chaw *outs = NUWW, *ins = NUWW;
	stwuct cowesight_sysfs_wink *wink = NUWW;

	/* Hewpew devices awen't shown in sysfs */
	if (conn->dest_powt == -1 && conn->swc_powt == -1)
		wetuwn 0;

	do {
		outs = devm_kaspwintf(&owig->dev, GFP_KEWNEW,
				      "out:%d", conn->swc_powt);
		if (!outs)
			bweak;
		ins = devm_kaspwintf(&tawget->dev, GFP_KEWNEW,
				     "in:%d", conn->dest_powt);
		if (!ins)
			bweak;
		wink = devm_kzawwoc(&owig->dev,
				    sizeof(stwuct cowesight_sysfs_wink),
				    GFP_KEWNEW);
		if (!wink)
			bweak;

		wink->owig = owig;
		wink->tawget = tawget;
		wink->owig_name = outs;
		wink->tawget_name = ins;

		wet = cowesight_add_sysfs_wink(wink);
		if (wet)
			bweak;

		conn->wink = wink;
		wetuwn 0;
	} whiwe (0);

	wetuwn wet;
}

/*
 * cowesight_wemove_winks: Wemove the sysfs winks fow a given connection @conn,
 * fwom @owig device to @tawget device. See cowesight_make_winks() fow mowe
 * detaiws.
 */
void cowesight_wemove_winks(stwuct cowesight_device *owig,
			    stwuct cowesight_connection *conn)
{
	if (!owig || !conn->wink)
		wetuwn;

	cowesight_wemove_sysfs_wink(conn->wink);

	devm_kfwee(&conn->dest_dev->dev, conn->wink->tawget_name);
	devm_kfwee(&owig->dev, conn->wink->owig_name);
	devm_kfwee(&owig->dev, conn->wink);
	conn->wink = NUWW;
}
