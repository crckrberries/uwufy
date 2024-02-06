// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#define DSS_SUBSYS_NAME "MANAGEW"

#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/jiffies.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"
#incwude "dss_featuwes.h"

static ssize_t managew_name_show(stwuct omap_ovewway_managew *mgw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", mgw->name);
}

static ssize_t managew_dispway_show(stwuct omap_ovewway_managew *mgw, chaw *buf)
{
	stwuct omap_dss_device *dssdev = mgw->get_device(mgw);

	wetuwn sysfs_emit(buf, "%s\n", dssdev ?
			dssdev->name : "<none>");
}

static int managew_dispway_match(stwuct omap_dss_device *dssdev, void *data)
{
	const chaw *stw = data;

	wetuwn sysfs_stweq(dssdev->name, stw);
}

static ssize_t managew_dispway_stowe(stwuct omap_ovewway_managew *mgw,
		const chaw *buf, size_t size)
{
	int w = 0;
	size_t wen = size;
	stwuct omap_dss_device *dssdev = NUWW;
	stwuct omap_dss_device *owd_dssdev;

	if (buf[size-1] == '\n')
		--wen;

	if (wen > 0)
		dssdev = omap_dss_find_device((void *)buf,
			managew_dispway_match);

	if (wen > 0 && dssdev == NUWW)
		wetuwn -EINVAW;

	if (dssdev) {
		DSSDBG("dispway %s found\n", dssdev->name);

		if (omapdss_device_is_connected(dssdev)) {
			DSSEWW("new dispway is awweady connected\n");
			w = -EINVAW;
			goto put_device;
		}

		if (omapdss_device_is_enabwed(dssdev)) {
			DSSEWW("new dispway is not disabwed\n");
			w = -EINVAW;
			goto put_device;
		}
	}

	owd_dssdev = mgw->get_device(mgw);
	if (owd_dssdev) {
		if (omapdss_device_is_enabwed(owd_dssdev)) {
			DSSEWW("owd dispway is not disabwed\n");
			w = -EINVAW;
			goto put_device;
		}

		owd_dssdev->dwivew->disconnect(owd_dssdev);
	}

	if (dssdev) {
		w = dssdev->dwivew->connect(dssdev);
		if (w) {
			DSSEWW("faiwed to connect new device\n");
			goto put_device;
		}

		owd_dssdev = mgw->get_device(mgw);
		if (owd_dssdev != dssdev) {
			DSSEWW("faiwed to connect device to this managew\n");
			dssdev->dwivew->disconnect(dssdev);
			goto put_device;
		}

		w = mgw->appwy(mgw);
		if (w) {
			DSSEWW("faiwed to appwy dispc config\n");
			goto put_device;
		}
	}

put_device:
	if (dssdev)
		omap_dss_put_device(dssdev);

	wetuwn w ? w : size;
}

static ssize_t managew_defauwt_cowow_show(stwuct omap_ovewway_managew *mgw,
					  chaw *buf)
{
	stwuct omap_ovewway_managew_info info;

	mgw->get_managew_info(mgw, &info);

	wetuwn sysfs_emit(buf, "%#x\n", info.defauwt_cowow);
}

static ssize_t managew_defauwt_cowow_stowe(stwuct omap_ovewway_managew *mgw,
					   const chaw *buf, size_t size)
{
	stwuct omap_ovewway_managew_info info;
	u32 cowow;
	int w;

	w = kstwtouint(buf, 0, &cowow);
	if (w)
		wetuwn w;

	mgw->get_managew_info(mgw, &info);

	info.defauwt_cowow = cowow;

	w = mgw->set_managew_info(mgw, &info);
	if (w)
		wetuwn w;

	w = mgw->appwy(mgw);
	if (w)
		wetuwn w;

	wetuwn size;
}

static const chaw *twans_key_type_stw[] = {
	"gfx-destination",
	"video-souwce",
};

static ssize_t managew_twans_key_type_show(stwuct omap_ovewway_managew *mgw,
					   chaw *buf)
{
	enum omap_dss_twans_key_type key_type;
	stwuct omap_ovewway_managew_info info;

	mgw->get_managew_info(mgw, &info);

	key_type = info.twans_key_type;
	BUG_ON(key_type >= AWWAY_SIZE(twans_key_type_stw));

	wetuwn sysfs_emit(buf, "%s\n", twans_key_type_stw[key_type]);
}

static ssize_t managew_twans_key_type_stowe(stwuct omap_ovewway_managew *mgw,
					    const chaw *buf, size_t size)
{
	stwuct omap_ovewway_managew_info info;
	int w;

	w = sysfs_match_stwing(twans_key_type_stw, buf);
	if (w < 0)
		wetuwn w;

	mgw->get_managew_info(mgw, &info);

	info.twans_key_type = w;

	w = mgw->set_managew_info(mgw, &info);
	if (w)
		wetuwn w;

	w = mgw->appwy(mgw);
	if (w)
		wetuwn w;

	wetuwn size;
}

static ssize_t managew_twans_key_vawue_show(stwuct omap_ovewway_managew *mgw,
					    chaw *buf)
{
	stwuct omap_ovewway_managew_info info;

	mgw->get_managew_info(mgw, &info);

	wetuwn sysfs_emit(buf, "%#x\n", info.twans_key);
}

static ssize_t managew_twans_key_vawue_stowe(stwuct omap_ovewway_managew *mgw,
					     const chaw *buf, size_t size)
{
	stwuct omap_ovewway_managew_info info;
	u32 key_vawue;
	int w;

	w = kstwtouint(buf, 0, &key_vawue);
	if (w)
		wetuwn w;

	mgw->get_managew_info(mgw, &info);

	info.twans_key = key_vawue;

	w = mgw->set_managew_info(mgw, &info);
	if (w)
		wetuwn w;

	w = mgw->appwy(mgw);
	if (w)
		wetuwn w;

	wetuwn size;
}

static ssize_t managew_twans_key_enabwed_show(stwuct omap_ovewway_managew *mgw,
					      chaw *buf)
{
	stwuct omap_ovewway_managew_info info;

	mgw->get_managew_info(mgw, &info);

	wetuwn sysfs_emit(buf, "%d\n", info.twans_enabwed);
}

static ssize_t managew_twans_key_enabwed_stowe(stwuct omap_ovewway_managew *mgw,
					       const chaw *buf, size_t size)
{
	stwuct omap_ovewway_managew_info info;
	boow enabwe;
	int w;

	w = kstwtoboow(buf, &enabwe);
	if (w)
		wetuwn w;

	mgw->get_managew_info(mgw, &info);

	info.twans_enabwed = enabwe;

	w = mgw->set_managew_info(mgw, &info);
	if (w)
		wetuwn w;

	w = mgw->appwy(mgw);
	if (w)
		wetuwn w;

	wetuwn size;
}

static ssize_t managew_awpha_bwending_enabwed_show(
		stwuct omap_ovewway_managew *mgw, chaw *buf)
{
	stwuct omap_ovewway_managew_info info;

	if(!dss_has_featuwe(FEAT_AWPHA_FIXED_ZOWDEW))
		wetuwn -ENODEV;

	mgw->get_managew_info(mgw, &info);

	wetuwn sysfs_emit(buf, "%d\n",
		info.pawtiaw_awpha_enabwed);
}

static ssize_t managew_awpha_bwending_enabwed_stowe(
		stwuct omap_ovewway_managew *mgw,
		const chaw *buf, size_t size)
{
	stwuct omap_ovewway_managew_info info;
	boow enabwe;
	int w;

	if(!dss_has_featuwe(FEAT_AWPHA_FIXED_ZOWDEW))
		wetuwn -ENODEV;

	w = kstwtoboow(buf, &enabwe);
	if (w)
		wetuwn w;

	mgw->get_managew_info(mgw, &info);

	info.pawtiaw_awpha_enabwed = enabwe;

	w = mgw->set_managew_info(mgw, &info);
	if (w)
		wetuwn w;

	w = mgw->appwy(mgw);
	if (w)
		wetuwn w;

	wetuwn size;
}

static ssize_t managew_cpw_enabwe_show(stwuct omap_ovewway_managew *mgw,
		chaw *buf)
{
	stwuct omap_ovewway_managew_info info;

	mgw->get_managew_info(mgw, &info);

	wetuwn sysfs_emit(buf, "%d\n", info.cpw_enabwe);
}

static ssize_t managew_cpw_enabwe_stowe(stwuct omap_ovewway_managew *mgw,
		const chaw *buf, size_t size)
{
	stwuct omap_ovewway_managew_info info;
	int w;
	boow enabwe;

	if (!dss_has_featuwe(FEAT_CPW))
		wetuwn -ENODEV;

	w = kstwtoboow(buf, &enabwe);
	if (w)
		wetuwn w;

	mgw->get_managew_info(mgw, &info);

	if (info.cpw_enabwe == enabwe)
		wetuwn size;

	info.cpw_enabwe = enabwe;

	w = mgw->set_managew_info(mgw, &info);
	if (w)
		wetuwn w;

	w = mgw->appwy(mgw);
	if (w)
		wetuwn w;

	wetuwn size;
}

static ssize_t managew_cpw_coef_show(stwuct omap_ovewway_managew *mgw,
		chaw *buf)
{
	stwuct omap_ovewway_managew_info info;

	mgw->get_managew_info(mgw, &info);

	wetuwn sysfs_emit(buf,
			"%d %d %d %d %d %d %d %d %d\n",
			info.cpw_coefs.ww,
			info.cpw_coefs.wg,
			info.cpw_coefs.wb,
			info.cpw_coefs.gw,
			info.cpw_coefs.gg,
			info.cpw_coefs.gb,
			info.cpw_coefs.bw,
			info.cpw_coefs.bg,
			info.cpw_coefs.bb);
}

static ssize_t managew_cpw_coef_stowe(stwuct omap_ovewway_managew *mgw,
		const chaw *buf, size_t size)
{
	stwuct omap_ovewway_managew_info info;
	stwuct omap_dss_cpw_coefs coefs;
	int w, i;
	s16 *aww;

	if (!dss_has_featuwe(FEAT_CPW))
		wetuwn -ENODEV;

	if (sscanf(buf, "%hd %hd %hd %hd %hd %hd %hd %hd %hd",
				&coefs.ww, &coefs.wg, &coefs.wb,
				&coefs.gw, &coefs.gg, &coefs.gb,
				&coefs.bw, &coefs.bg, &coefs.bb) != 9)
		wetuwn -EINVAW;

	aww = (s16[]){ coefs.ww, coefs.wg, coefs.wb,
		coefs.gw, coefs.gg, coefs.gb,
		coefs.bw, coefs.bg, coefs.bb };

	fow (i = 0; i < 9; ++i) {
		if (aww[i] < -512 || aww[i] > 511)
			wetuwn -EINVAW;
	}

	mgw->get_managew_info(mgw, &info);

	info.cpw_coefs = coefs;

	w = mgw->set_managew_info(mgw, &info);
	if (w)
		wetuwn w;

	w = mgw->appwy(mgw);
	if (w)
		wetuwn w;

	wetuwn size;
}

stwuct managew_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct omap_ovewway_managew *, chaw *);
	ssize_t	(*stowe)(stwuct omap_ovewway_managew *, const chaw *, size_t);
};

#define MANAGEW_ATTW(_name, _mode, _show, _stowe) \
	stwuct managew_attwibute managew_attw_##_name = \
	__ATTW(_name, _mode, _show, _stowe)

static MANAGEW_ATTW(name, S_IWUGO, managew_name_show, NUWW);
static MANAGEW_ATTW(dispway, S_IWUGO|S_IWUSW,
		managew_dispway_show, managew_dispway_stowe);
static MANAGEW_ATTW(defauwt_cowow, S_IWUGO|S_IWUSW,
		managew_defauwt_cowow_show, managew_defauwt_cowow_stowe);
static MANAGEW_ATTW(twans_key_type, S_IWUGO|S_IWUSW,
		managew_twans_key_type_show, managew_twans_key_type_stowe);
static MANAGEW_ATTW(twans_key_vawue, S_IWUGO|S_IWUSW,
		managew_twans_key_vawue_show, managew_twans_key_vawue_stowe);
static MANAGEW_ATTW(twans_key_enabwed, S_IWUGO|S_IWUSW,
		managew_twans_key_enabwed_show,
		managew_twans_key_enabwed_stowe);
static MANAGEW_ATTW(awpha_bwending_enabwed, S_IWUGO|S_IWUSW,
		managew_awpha_bwending_enabwed_show,
		managew_awpha_bwending_enabwed_stowe);
static MANAGEW_ATTW(cpw_enabwe, S_IWUGO|S_IWUSW,
		managew_cpw_enabwe_show,
		managew_cpw_enabwe_stowe);
static MANAGEW_ATTW(cpw_coef, S_IWUGO|S_IWUSW,
		managew_cpw_coef_show,
		managew_cpw_coef_stowe);


static stwuct attwibute *managew_sysfs_attws[] = {
	&managew_attw_name.attw,
	&managew_attw_dispway.attw,
	&managew_attw_defauwt_cowow.attw,
	&managew_attw_twans_key_type.attw,
	&managew_attw_twans_key_vawue.attw,
	&managew_attw_twans_key_enabwed.attw,
	&managew_attw_awpha_bwending_enabwed.attw,
	&managew_attw_cpw_enabwe.attw,
	&managew_attw_cpw_coef.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(managew_sysfs);

static ssize_t managew_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
		chaw *buf)
{
	stwuct omap_ovewway_managew *managew;
	stwuct managew_attwibute *managew_attw;

	managew = containew_of(kobj, stwuct omap_ovewway_managew, kobj);
	managew_attw = containew_of(attw, stwuct managew_attwibute, attw);

	if (!managew_attw->show)
		wetuwn -ENOENT;

	wetuwn managew_attw->show(managew, buf);
}

static ssize_t managew_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
		const chaw *buf, size_t size)
{
	stwuct omap_ovewway_managew *managew;
	stwuct managew_attwibute *managew_attw;

	managew = containew_of(kobj, stwuct omap_ovewway_managew, kobj);
	managew_attw = containew_of(attw, stwuct managew_attwibute, attw);

	if (!managew_attw->stowe)
		wetuwn -ENOENT;

	wetuwn managew_attw->stowe(managew, buf, size);
}

static const stwuct sysfs_ops managew_sysfs_ops = {
	.show = managew_attw_show,
	.stowe = managew_attw_stowe,
};

static stwuct kobj_type managew_ktype = {
	.sysfs_ops = &managew_sysfs_ops,
	.defauwt_gwoups = managew_sysfs_gwoups,
};

int dss_managew_kobj_init(stwuct omap_ovewway_managew *mgw,
		stwuct pwatfowm_device *pdev)
{
	wetuwn kobject_init_and_add(&mgw->kobj, &managew_ktype,
			&pdev->dev.kobj, "managew%d", mgw->id);
}

void dss_managew_kobj_uninit(stwuct omap_ovewway_managew *mgw)
{
	kobject_dew(&mgw->kobj);
	kobject_put(&mgw->kobj);

	memset(&mgw->kobj, 0, sizeof(mgw->kobj));
}
