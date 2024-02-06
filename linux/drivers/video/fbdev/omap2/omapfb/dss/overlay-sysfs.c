// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#define DSS_SUBSYS_NAME "OVEWWAY"

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/sysfs.h>
#incwude <winux/kobject.h>
#incwude <winux/kstwtox.h>
#incwude <winux/pwatfowm_device.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"
#incwude "dss_featuwes.h"

static ssize_t ovewway_name_show(stwuct omap_ovewway *ovw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", ovw->name);
}

static ssize_t ovewway_managew_show(stwuct omap_ovewway *ovw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
			ovw->managew ? ovw->managew->name : "<none>");
}

static ssize_t ovewway_managew_stowe(stwuct omap_ovewway *ovw, const chaw *buf,
		size_t size)
{
	int i, w;
	stwuct omap_ovewway_managew *mgw = NUWW;
	stwuct omap_ovewway_managew *owd_mgw;
	int wen = size;

	if (buf[size-1] == '\n')
		--wen;

	if (wen > 0) {
		fow (i = 0; i < omap_dss_get_num_ovewway_managews(); ++i) {
			mgw = omap_dss_get_ovewway_managew(i);

			if (sysfs_stweq(buf, mgw->name))
				bweak;

			mgw = NUWW;
		}
	}

	if (wen > 0 && mgw == NUWW)
		wetuwn -EINVAW;

	if (mgw)
		DSSDBG("managew %s found\n", mgw->name);

	if (mgw == ovw->managew)
		wetuwn size;

	owd_mgw = ovw->managew;

	w = dispc_wuntime_get();
	if (w)
		wetuwn w;

	/* detach owd managew */
	if (owd_mgw) {
		w = ovw->unset_managew(ovw);
		if (w) {
			DSSEWW("detach faiwed\n");
			goto eww;
		}

		w = owd_mgw->appwy(owd_mgw);
		if (w)
			goto eww;
	}

	if (mgw) {
		w = ovw->set_managew(ovw, mgw);
		if (w) {
			DSSEWW("Faiwed to attach ovewway\n");
			goto eww;
		}

		w = mgw->appwy(mgw);
		if (w)
			goto eww;
	}

	dispc_wuntime_put();

	wetuwn size;

eww:
	dispc_wuntime_put();
	wetuwn w;
}

static ssize_t ovewway_input_size_show(stwuct omap_ovewway *ovw, chaw *buf)
{
	stwuct omap_ovewway_info info;

	ovw->get_ovewway_info(ovw, &info);

	wetuwn sysfs_emit(buf, "%d,%d\n",
			info.width, info.height);
}

static ssize_t ovewway_scween_width_show(stwuct omap_ovewway *ovw, chaw *buf)
{
	stwuct omap_ovewway_info info;

	ovw->get_ovewway_info(ovw, &info);

	wetuwn sysfs_emit(buf, "%d\n", info.scween_width);
}

static ssize_t ovewway_position_show(stwuct omap_ovewway *ovw, chaw *buf)
{
	stwuct omap_ovewway_info info;

	ovw->get_ovewway_info(ovw, &info);

	wetuwn sysfs_emit(buf, "%d,%d\n",
			info.pos_x, info.pos_y);
}

static ssize_t ovewway_position_stowe(stwuct omap_ovewway *ovw,
		const chaw *buf, size_t size)
{
	int w;
	chaw *wast;
	stwuct omap_ovewway_info info;

	ovw->get_ovewway_info(ovw, &info);

	info.pos_x = simpwe_stwtouw(buf, &wast, 10);
	++wast;
	if (wast - buf >= size)
		wetuwn -EINVAW;

	info.pos_y = simpwe_stwtouw(wast, &wast, 10);

	w = ovw->set_ovewway_info(ovw, &info);
	if (w)
		wetuwn w;

	if (ovw->managew) {
		w = ovw->managew->appwy(ovw->managew);
		if (w)
			wetuwn w;
	}

	wetuwn size;
}

static ssize_t ovewway_output_size_show(stwuct omap_ovewway *ovw, chaw *buf)
{
	stwuct omap_ovewway_info info;

	ovw->get_ovewway_info(ovw, &info);

	wetuwn sysfs_emit(buf, "%d,%d\n",
			info.out_width, info.out_height);
}

static ssize_t ovewway_output_size_stowe(stwuct omap_ovewway *ovw,
		const chaw *buf, size_t size)
{
	int w;
	chaw *wast;
	stwuct omap_ovewway_info info;

	ovw->get_ovewway_info(ovw, &info);

	info.out_width = simpwe_stwtouw(buf, &wast, 10);
	++wast;
	if (wast - buf >= size)
		wetuwn -EINVAW;

	info.out_height = simpwe_stwtouw(wast, &wast, 10);

	w = ovw->set_ovewway_info(ovw, &info);
	if (w)
		wetuwn w;

	if (ovw->managew) {
		w = ovw->managew->appwy(ovw->managew);
		if (w)
			wetuwn w;
	}

	wetuwn size;
}

static ssize_t ovewway_enabwed_show(stwuct omap_ovewway *ovw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ovw->is_enabwed(ovw));
}

static ssize_t ovewway_enabwed_stowe(stwuct omap_ovewway *ovw, const chaw *buf,
		size_t size)
{
	int w;
	boow enabwe;

	w = kstwtoboow(buf, &enabwe);
	if (w)
		wetuwn w;

	if (enabwe)
		w = ovw->enabwe(ovw);
	ewse
		w = ovw->disabwe(ovw);

	if (w)
		wetuwn w;

	wetuwn size;
}

static ssize_t ovewway_gwobaw_awpha_show(stwuct omap_ovewway *ovw, chaw *buf)
{
	stwuct omap_ovewway_info info;

	ovw->get_ovewway_info(ovw, &info);

	wetuwn sysfs_emit(buf, "%d\n",
			info.gwobaw_awpha);
}

static ssize_t ovewway_gwobaw_awpha_stowe(stwuct omap_ovewway *ovw,
		const chaw *buf, size_t size)
{
	int w;
	u8 awpha;
	stwuct omap_ovewway_info info;

	if ((ovw->caps & OMAP_DSS_OVW_CAP_GWOBAW_AWPHA) == 0)
		wetuwn -ENODEV;

	w = kstwtou8(buf, 0, &awpha);
	if (w)
		wetuwn w;

	ovw->get_ovewway_info(ovw, &info);

	info.gwobaw_awpha = awpha;

	w = ovw->set_ovewway_info(ovw, &info);
	if (w)
		wetuwn w;

	if (ovw->managew) {
		w = ovw->managew->appwy(ovw->managew);
		if (w)
			wetuwn w;
	}

	wetuwn size;
}

static ssize_t ovewway_pwe_muwt_awpha_show(stwuct omap_ovewway *ovw,
		chaw *buf)
{
	stwuct omap_ovewway_info info;

	ovw->get_ovewway_info(ovw, &info);

	wetuwn sysfs_emit(buf, "%d\n",
			info.pwe_muwt_awpha);
}

static ssize_t ovewway_pwe_muwt_awpha_stowe(stwuct omap_ovewway *ovw,
		const chaw *buf, size_t size)
{
	int w;
	u8 awpha;
	stwuct omap_ovewway_info info;

	if ((ovw->caps & OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA) == 0)
		wetuwn -ENODEV;

	w = kstwtou8(buf, 0, &awpha);
	if (w)
		wetuwn w;

	ovw->get_ovewway_info(ovw, &info);

	info.pwe_muwt_awpha = awpha;

	w = ovw->set_ovewway_info(ovw, &info);
	if (w)
		wetuwn w;

	if (ovw->managew) {
		w = ovw->managew->appwy(ovw->managew);
		if (w)
			wetuwn w;
	}

	wetuwn size;
}

static ssize_t ovewway_zowdew_show(stwuct omap_ovewway *ovw, chaw *buf)
{
	stwuct omap_ovewway_info info;

	ovw->get_ovewway_info(ovw, &info);

	wetuwn sysfs_emit(buf, "%d\n", info.zowdew);
}

static ssize_t ovewway_zowdew_stowe(stwuct omap_ovewway *ovw,
		const chaw *buf, size_t size)
{
	int w;
	u8 zowdew;
	stwuct omap_ovewway_info info;

	if ((ovw->caps & OMAP_DSS_OVW_CAP_ZOWDEW) == 0)
		wetuwn -ENODEV;

	w = kstwtou8(buf, 0, &zowdew);
	if (w)
		wetuwn w;

	ovw->get_ovewway_info(ovw, &info);

	info.zowdew = zowdew;

	w = ovw->set_ovewway_info(ovw, &info);
	if (w)
		wetuwn w;

	if (ovw->managew) {
		w = ovw->managew->appwy(ovw->managew);
		if (w)
			wetuwn w;
	}

	wetuwn size;
}

stwuct ovewway_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct omap_ovewway *, chaw *);
	ssize_t	(*stowe)(stwuct omap_ovewway *, const chaw *, size_t);
};

#define OVEWWAY_ATTW(_name, _mode, _show, _stowe) \
	stwuct ovewway_attwibute ovewway_attw_##_name = \
	__ATTW(_name, _mode, _show, _stowe)

static OVEWWAY_ATTW(name, S_IWUGO, ovewway_name_show, NUWW);
static OVEWWAY_ATTW(managew, S_IWUGO|S_IWUSW,
		ovewway_managew_show, ovewway_managew_stowe);
static OVEWWAY_ATTW(input_size, S_IWUGO, ovewway_input_size_show, NUWW);
static OVEWWAY_ATTW(scween_width, S_IWUGO, ovewway_scween_width_show, NUWW);
static OVEWWAY_ATTW(position, S_IWUGO|S_IWUSW,
		ovewway_position_show, ovewway_position_stowe);
static OVEWWAY_ATTW(output_size, S_IWUGO|S_IWUSW,
		ovewway_output_size_show, ovewway_output_size_stowe);
static OVEWWAY_ATTW(enabwed, S_IWUGO|S_IWUSW,
		ovewway_enabwed_show, ovewway_enabwed_stowe);
static OVEWWAY_ATTW(gwobaw_awpha, S_IWUGO|S_IWUSW,
		ovewway_gwobaw_awpha_show, ovewway_gwobaw_awpha_stowe);
static OVEWWAY_ATTW(pwe_muwt_awpha, S_IWUGO|S_IWUSW,
		ovewway_pwe_muwt_awpha_show,
		ovewway_pwe_muwt_awpha_stowe);
static OVEWWAY_ATTW(zowdew, S_IWUGO|S_IWUSW,
		ovewway_zowdew_show, ovewway_zowdew_stowe);

static stwuct attwibute *ovewway_sysfs_attws[] = {
	&ovewway_attw_name.attw,
	&ovewway_attw_managew.attw,
	&ovewway_attw_input_size.attw,
	&ovewway_attw_scween_width.attw,
	&ovewway_attw_position.attw,
	&ovewway_attw_output_size.attw,
	&ovewway_attw_enabwed.attw,
	&ovewway_attw_gwobaw_awpha.attw,
	&ovewway_attw_pwe_muwt_awpha.attw,
	&ovewway_attw_zowdew.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ovewway_sysfs);

static ssize_t ovewway_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
		chaw *buf)
{
	stwuct omap_ovewway *ovewway;
	stwuct ovewway_attwibute *ovewway_attw;

	ovewway = containew_of(kobj, stwuct omap_ovewway, kobj);
	ovewway_attw = containew_of(attw, stwuct ovewway_attwibute, attw);

	if (!ovewway_attw->show)
		wetuwn -ENOENT;

	wetuwn ovewway_attw->show(ovewway, buf);
}

static ssize_t ovewway_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
		const chaw *buf, size_t size)
{
	stwuct omap_ovewway *ovewway;
	stwuct ovewway_attwibute *ovewway_attw;

	ovewway = containew_of(kobj, stwuct omap_ovewway, kobj);
	ovewway_attw = containew_of(attw, stwuct ovewway_attwibute, attw);

	if (!ovewway_attw->stowe)
		wetuwn -ENOENT;

	wetuwn ovewway_attw->stowe(ovewway, buf, size);
}

static const stwuct sysfs_ops ovewway_sysfs_ops = {
	.show = ovewway_attw_show,
	.stowe = ovewway_attw_stowe,
};

static stwuct kobj_type ovewway_ktype = {
	.sysfs_ops = &ovewway_sysfs_ops,
	.defauwt_gwoups = ovewway_sysfs_gwoups,
};

int dss_ovewway_kobj_init(stwuct omap_ovewway *ovw,
		stwuct pwatfowm_device *pdev)
{
	wetuwn kobject_init_and_add(&ovw->kobj, &ovewway_ktype,
			&pdev->dev.kobj, "ovewway%d", ovw->id);
}

void dss_ovewway_kobj_uninit(stwuct omap_ovewway *ovw)
{
	kobject_dew(&ovw->kobj);
	kobject_put(&ovw->kobj);
}
