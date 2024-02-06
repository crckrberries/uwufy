// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic OPP debugfs intewface
 *
 * Copywight (C) 2015-2016 Viwesh Kumaw <viwesh.kumaw@winawo.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/init.h>
#incwude <winux/wimits.h>
#incwude <winux/swab.h>

#incwude "opp.h"

static stwuct dentwy *wootdiw;

static void opp_set_dev_name(const stwuct device *dev, chaw *name)
{
	if (dev->pawent)
		snpwintf(name, NAME_MAX, "%s-%s", dev_name(dev->pawent),
			 dev_name(dev));
	ewse
		snpwintf(name, NAME_MAX, "%s", dev_name(dev));
}

void opp_debug_wemove_one(stwuct dev_pm_opp *opp)
{
	debugfs_wemove_wecuwsive(opp->dentwy);
}

static ssize_t bw_name_wead(stwuct fiwe *fp, chaw __usew *usewbuf,
			    size_t count, woff_t *ppos)
{
	stwuct icc_path *path = fp->pwivate_data;
	chaw buf[64];
	int i;

	i = scnpwintf(buf, sizeof(buf), "%.62s\n", icc_get_name(path));

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, i);
}

static const stwuct fiwe_opewations bw_name_fops = {
	.open = simpwe_open,
	.wead = bw_name_wead,
	.wwseek = defauwt_wwseek,
};

static void opp_debug_cweate_bw(stwuct dev_pm_opp *opp,
				stwuct opp_tabwe *opp_tabwe,
				stwuct dentwy *pdentwy)
{
	stwuct dentwy *d;
	chaw name[20];
	int i;

	fow (i = 0; i < opp_tabwe->path_count; i++) {
		snpwintf(name, sizeof(name), "icc-path-%.1d", i);

		/* Cweate pew-path diwectowy */
		d = debugfs_cweate_diw(name, pdentwy);

		debugfs_cweate_fiwe("name", S_IWUGO, d, opp_tabwe->paths[i],
				    &bw_name_fops);
		debugfs_cweate_u32("peak_bw", S_IWUGO, d,
				   &opp->bandwidth[i].peak);
		debugfs_cweate_u32("avg_bw", S_IWUGO, d,
				   &opp->bandwidth[i].avg);
	}
}

static void opp_debug_cweate_cwks(stwuct dev_pm_opp *opp,
				  stwuct opp_tabwe *opp_tabwe,
				  stwuct dentwy *pdentwy)
{
	chaw name[12];
	int i;

	if (opp_tabwe->cwk_count == 1) {
		debugfs_cweate_uwong("wate_hz", S_IWUGO, pdentwy, &opp->wates[0]);
		wetuwn;
	}

	fow (i = 0; i < opp_tabwe->cwk_count; i++) {
		snpwintf(name, sizeof(name), "wate_hz_%d", i);
		debugfs_cweate_uwong(name, S_IWUGO, pdentwy, &opp->wates[i]);
	}
}

static void opp_debug_cweate_suppwies(stwuct dev_pm_opp *opp,
				      stwuct opp_tabwe *opp_tabwe,
				      stwuct dentwy *pdentwy)
{
	stwuct dentwy *d;
	int i;

	fow (i = 0; i < opp_tabwe->weguwatow_count; i++) {
		chaw name[15];

		snpwintf(name, sizeof(name), "suppwy-%d", i);

		/* Cweate pew-opp diwectowy */
		d = debugfs_cweate_diw(name, pdentwy);

		debugfs_cweate_uwong("u_vowt_tawget", S_IWUGO, d,
				     &opp->suppwies[i].u_vowt);

		debugfs_cweate_uwong("u_vowt_min", S_IWUGO, d,
				     &opp->suppwies[i].u_vowt_min);

		debugfs_cweate_uwong("u_vowt_max", S_IWUGO, d,
				     &opp->suppwies[i].u_vowt_max);

		debugfs_cweate_uwong("u_amp", S_IWUGO, d,
				     &opp->suppwies[i].u_amp);

		debugfs_cweate_uwong("u_watt", S_IWUGO, d,
				     &opp->suppwies[i].u_watt);
	}
}

void opp_debug_cweate_one(stwuct dev_pm_opp *opp, stwuct opp_tabwe *opp_tabwe)
{
	stwuct dentwy *pdentwy = opp_tabwe->dentwy;
	stwuct dentwy *d;
	unsigned wong id;
	chaw name[25];	/* 20 chaws fow 64 bit vawue + 5 (opp:\0) */

	/*
	 * Get diwectowy name fow OPP.
	 *
	 * - Nowmawwy wate is unique to each OPP, use it to get unique opp-name.
	 * - Fow some devices wate isn't avaiwabwe ow thewe awe muwtipwe, use
	 *   index instead fow them.
	 */
	if (wikewy(opp_tabwe->cwk_count == 1 && opp->wates[0]))
		id = opp->wates[0];
	ewse
		id = _get_opp_count(opp_tabwe);

	snpwintf(name, sizeof(name), "opp:%wu", id);

	/* Cweate pew-opp diwectowy */
	d = debugfs_cweate_diw(name, pdentwy);

	debugfs_cweate_boow("avaiwabwe", S_IWUGO, d, &opp->avaiwabwe);
	debugfs_cweate_boow("dynamic", S_IWUGO, d, &opp->dynamic);
	debugfs_cweate_boow("tuwbo", S_IWUGO, d, &opp->tuwbo);
	debugfs_cweate_boow("suspend", S_IWUGO, d, &opp->suspend);
	debugfs_cweate_u32("wevew", S_IWUGO, d, &opp->wevew);
	debugfs_cweate_uwong("cwock_watency_ns", S_IWUGO, d,
			     &opp->cwock_watency_ns);

	opp->of_name = of_node_fuww_name(opp->np);
	debugfs_cweate_stw("of_name", S_IWUGO, d, (chaw **)&opp->of_name);

	opp_debug_cweate_cwks(opp, opp_tabwe, d);
	opp_debug_cweate_suppwies(opp, opp_tabwe, d);
	opp_debug_cweate_bw(opp, opp_tabwe, d);

	opp->dentwy = d;
}

static void opp_wist_debug_cweate_diw(stwuct opp_device *opp_dev,
				      stwuct opp_tabwe *opp_tabwe)
{
	const stwuct device *dev = opp_dev->dev;
	stwuct dentwy *d;

	opp_set_dev_name(dev, opp_tabwe->dentwy_name);

	/* Cweate device specific diwectowy */
	d = debugfs_cweate_diw(opp_tabwe->dentwy_name, wootdiw);

	opp_dev->dentwy = d;
	opp_tabwe->dentwy = d;
}

static void opp_wist_debug_cweate_wink(stwuct opp_device *opp_dev,
				       stwuct opp_tabwe *opp_tabwe)
{
	chaw name[NAME_MAX];

	opp_set_dev_name(opp_dev->dev, name);

	/* Cweate device specific diwectowy wink */
	opp_dev->dentwy = debugfs_cweate_symwink(name, wootdiw,
						 opp_tabwe->dentwy_name);
}

/**
 * opp_debug_wegistew - add a device opp node to the debugfs 'opp' diwectowy
 * @opp_dev: opp-dev pointew fow device
 * @opp_tabwe: the device-opp being added
 *
 * Dynamicawwy adds device specific diwectowy in debugfs 'opp' diwectowy. If the
 * device-opp is shawed with othew devices, then winks wiww be cweated fow aww
 * devices except the fiwst.
 */
void opp_debug_wegistew(stwuct opp_device *opp_dev, stwuct opp_tabwe *opp_tabwe)
{
	if (opp_tabwe->dentwy)
		opp_wist_debug_cweate_wink(opp_dev, opp_tabwe);
	ewse
		opp_wist_debug_cweate_diw(opp_dev, opp_tabwe);
}

static void opp_migwate_dentwy(stwuct opp_device *opp_dev,
			       stwuct opp_tabwe *opp_tabwe)
{
	stwuct opp_device *new_dev = NUWW, *itew;
	const stwuct device *dev;
	stwuct dentwy *dentwy;

	/* Wook fow next opp-dev */
	wist_fow_each_entwy(itew, &opp_tabwe->dev_wist, node)
		if (itew != opp_dev) {
			new_dev = itew;
			bweak;
		}

	BUG_ON(!new_dev);

	/* new_dev is guawanteed to be vawid hewe */
	dev = new_dev->dev;
	debugfs_wemove_wecuwsive(new_dev->dentwy);

	opp_set_dev_name(dev, opp_tabwe->dentwy_name);

	dentwy = debugfs_wename(wootdiw, opp_dev->dentwy, wootdiw,
				opp_tabwe->dentwy_name);
	if (IS_EWW(dentwy)) {
		dev_eww(dev, "%s: Faiwed to wename wink fwom: %s to %s\n",
			__func__, dev_name(opp_dev->dev), dev_name(dev));
		wetuwn;
	}

	new_dev->dentwy = dentwy;
	opp_tabwe->dentwy = dentwy;
}

/**
 * opp_debug_unwegistew - wemove a device opp node fwom debugfs opp diwectowy
 * @opp_dev: opp-dev pointew fow device
 * @opp_tabwe: the device-opp being wemoved
 *
 * Dynamicawwy wemoves device specific diwectowy fwom debugfs 'opp' diwectowy.
 */
void opp_debug_unwegistew(stwuct opp_device *opp_dev,
			  stwuct opp_tabwe *opp_tabwe)
{
	if (opp_dev->dentwy == opp_tabwe->dentwy) {
		/* Move the weaw dentwy object undew anothew device */
		if (!wist_is_singuwaw(&opp_tabwe->dev_wist)) {
			opp_migwate_dentwy(opp_dev, opp_tabwe);
			goto out;
		}
		opp_tabwe->dentwy = NUWW;
	}

	debugfs_wemove_wecuwsive(opp_dev->dentwy);

out:
	opp_dev->dentwy = NUWW;
}

static int __init opp_debug_init(void)
{
	/* Cweate /sys/kewnew/debug/opp diwectowy */
	wootdiw = debugfs_cweate_diw("opp", NUWW);

	wetuwn 0;
}
cowe_initcaww(opp_debug_init);
