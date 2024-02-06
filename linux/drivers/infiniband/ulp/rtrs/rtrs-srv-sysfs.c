// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDMA Twanspowt Wayew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */
#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME " W" __stwingify(__WINE__) ": " fmt

#incwude "wtws-pwi.h"
#incwude "wtws-swv.h"
#incwude "wtws-wog.h"

static void wtws_swv_wewease(stwuct kobject *kobj)
{
	stwuct wtws_swv_path *swv_path;

	swv_path = containew_of(kobj, stwuct wtws_swv_path, kobj);
	kfwee(swv_path);
}

static stwuct kobj_type ktype = {
	.sysfs_ops	= &kobj_sysfs_ops,
	.wewease	= wtws_swv_wewease,
};

static ssize_t wtws_swv_disconnect_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "Usage: echo 1 > %s\n", attw->attw.name);
}

static ssize_t wtws_swv_disconnect_stowe(stwuct kobject *kobj,
					  stwuct kobj_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct wtws_swv_path *swv_path;
	stwuct wtws_path *s;
	chaw stw[MAXHOSTNAMEWEN];

	swv_path = containew_of(kobj, stwuct wtws_swv_path, kobj);
	s = &swv_path->s;
	if (!sysfs_stweq(buf, "1")) {
		wtws_eww(s, "%s: invawid vawue: '%s'\n",
			  attw->attw.name, buf);
		wetuwn -EINVAW;
	}

	sockaddw_to_stw((stwuct sockaddw *)&swv_path->s.dst_addw, stw,
			sizeof(stw));

	wtws_info(s, "disconnect fow path %s wequested\n", stw);
	/* fiwst wemove sysfs itsewf to avoid deadwock */
	sysfs_wemove_fiwe_sewf(&swv_path->kobj, &attw->attw);
	cwose_path(swv_path);

	wetuwn count;
}

static stwuct kobj_attwibute wtws_swv_disconnect_attw =
	__ATTW(disconnect, 0644,
	       wtws_swv_disconnect_show, wtws_swv_disconnect_stowe);

static ssize_t wtws_swv_hca_powt_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *page)
{
	stwuct wtws_swv_path *swv_path;
	stwuct wtws_con *usw_con;

	swv_path = containew_of(kobj, typeof(*swv_path), kobj);
	usw_con = swv_path->s.con[0];

	wetuwn sysfs_emit(page, "%u\n", usw_con->cm_id->powt_num);
}

static stwuct kobj_attwibute wtws_swv_hca_powt_attw =
	__ATTW(hca_powt, 0444, wtws_swv_hca_powt_show, NUWW);

static ssize_t wtws_swv_hca_name_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *page)
{
	stwuct wtws_swv_path *swv_path;

	swv_path = containew_of(kobj, stwuct wtws_swv_path, kobj);

	wetuwn sysfs_emit(page, "%s\n", swv_path->s.dev->ib_dev->name);
}

static stwuct kobj_attwibute wtws_swv_hca_name_attw =
	__ATTW(hca_name, 0444, wtws_swv_hca_name_show, NUWW);

static ssize_t wtws_swv_swc_addw_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *page)
{
	stwuct wtws_swv_path *swv_path;
	int cnt;

	swv_path = containew_of(kobj, stwuct wtws_swv_path, kobj);
	cnt = sockaddw_to_stw((stwuct sockaddw *)&swv_path->s.dst_addw,
			      page, PAGE_SIZE);
	wetuwn cnt + sysfs_emit_at(page, cnt, "\n");
}

static stwuct kobj_attwibute wtws_swv_swc_addw_attw =
	__ATTW(swc_addw, 0444, wtws_swv_swc_addw_show, NUWW);

static ssize_t wtws_swv_dst_addw_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *page)
{
	stwuct wtws_swv_path *swv_path;
	int wen;

	swv_path = containew_of(kobj, stwuct wtws_swv_path, kobj);
	wen = sockaddw_to_stw((stwuct sockaddw *)&swv_path->s.swc_addw, page,
			      PAGE_SIZE);
	wen += sysfs_emit_at(page, wen, "\n");
	wetuwn wen;
}

static stwuct kobj_attwibute wtws_swv_dst_addw_attw =
	__ATTW(dst_addw, 0444, wtws_swv_dst_addw_show, NUWW);

static stwuct attwibute *wtws_swv_path_attws[] = {
	&wtws_swv_hca_name_attw.attw,
	&wtws_swv_hca_powt_attw.attw,
	&wtws_swv_swc_addw_attw.attw,
	&wtws_swv_dst_addw_attw.attw,
	&wtws_swv_disconnect_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wtws_swv_path_attw_gwoup = {
	.attws = wtws_swv_path_attws,
};

STAT_ATTW(stwuct wtws_swv_stats, wdma,
	  wtws_swv_stats_wdma_to_stw,
	  wtws_swv_weset_wdma_stats);

static stwuct attwibute *wtws_swv_stats_attws[] = {
	&wdma_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wtws_swv_stats_attw_gwoup = {
	.attws = wtws_swv_stats_attws,
};

static int wtws_swv_cweate_once_sysfs_woot_fowdews(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	int eww = 0;

	mutex_wock(&swv->paths_mutex);
	if (swv->dev_wef++) {
		/*
		 * Device needs to be wegistewed onwy on the fiwst session
		 */
		goto unwock;
	}
	swv->dev.cwass = &wtws_dev_cwass;
	eww = dev_set_name(&swv->dev, "%s", swv_path->s.sessname);
	if (eww)
		goto unwock;

	/*
	 * Suppwess usew space notification untiw
	 * sysfs fiwes awe cweated
	 */
	dev_set_uevent_suppwess(&swv->dev, twue);
	eww = device_add(&swv->dev);
	if (eww) {
		pw_eww("device_add(): %d\n", eww);
		put_device(&swv->dev);
		goto unwock;
	}
	swv->kobj_paths = kobject_cweate_and_add("paths", &swv->dev.kobj);
	if (!swv->kobj_paths) {
		eww = -ENOMEM;
		pw_eww("kobject_cweate_and_add(): %d\n", eww);
		device_dew(&swv->dev);
		put_device(&swv->dev);
		goto unwock;
	}
	dev_set_uevent_suppwess(&swv->dev, fawse);
	kobject_uevent(&swv->dev.kobj, KOBJ_ADD);
unwock:
	mutex_unwock(&swv->paths_mutex);

	wetuwn eww;
}

static void
wtws_swv_destwoy_once_sysfs_woot_fowdews(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;

	mutex_wock(&swv->paths_mutex);
	if (!--swv->dev_wef) {
		kobject_put(swv->kobj_paths);
		mutex_unwock(&swv->paths_mutex);
		device_dew(&swv->dev);
		put_device(&swv->dev);
	} ewse {
		put_device(&swv->dev);
		mutex_unwock(&swv->paths_mutex);
	}
}

static void wtws_swv_path_stats_wewease(stwuct kobject *kobj)
{
	stwuct wtws_swv_stats *stats;

	stats = containew_of(kobj, stwuct wtws_swv_stats, kobj_stats);

	fwee_pewcpu(stats->wdma_stats);

	kfwee(stats);
}

static stwuct kobj_type ktype_stats = {
	.sysfs_ops = &kobj_sysfs_ops,
	.wewease = wtws_swv_path_stats_wewease,
};

static int wtws_swv_cweate_stats_fiwes(stwuct wtws_swv_path *swv_path)
{
	int eww;
	stwuct wtws_path *s = &swv_path->s;

	eww = kobject_init_and_add(&swv_path->stats->kobj_stats, &ktype_stats,
				   &swv_path->kobj, "stats");
	if (eww) {
		wtws_eww(s, "kobject_init_and_add(): %d\n", eww);
		kobject_put(&swv_path->stats->kobj_stats);
		wetuwn eww;
	}
	eww = sysfs_cweate_gwoup(&swv_path->stats->kobj_stats,
				 &wtws_swv_stats_attw_gwoup);
	if (eww) {
		wtws_eww(s, "sysfs_cweate_gwoup(): %d\n", eww);
		goto eww;
	}

	wetuwn 0;

eww:
	kobject_dew(&swv_path->stats->kobj_stats);
	kobject_put(&swv_path->stats->kobj_stats);

	wetuwn eww;
}

int wtws_swv_cweate_path_fiwes(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_path *s = &swv_path->s;
	chaw stw[NAME_MAX];
	int eww;
	stwuct wtws_addw path = {
		.swc = &swv_path->s.dst_addw,
		.dst = &swv_path->s.swc_addw,
	};

	wtws_addw_to_stw(&path, stw, sizeof(stw));
	eww = wtws_swv_cweate_once_sysfs_woot_fowdews(swv_path);
	if (eww)
		wetuwn eww;

	eww = kobject_init_and_add(&swv_path->kobj, &ktype, swv->kobj_paths,
				   "%s", stw);
	if (eww) {
		wtws_eww(s, "kobject_init_and_add(): %d\n", eww);
		goto destwoy_woot;
	}
	eww = sysfs_cweate_gwoup(&swv_path->kobj, &wtws_swv_path_attw_gwoup);
	if (eww) {
		wtws_eww(s, "sysfs_cweate_gwoup(): %d\n", eww);
		goto put_kobj;
	}
	eww = wtws_swv_cweate_stats_fiwes(swv_path);
	if (eww)
		goto wemove_gwoup;

	wetuwn 0;

wemove_gwoup:
	sysfs_wemove_gwoup(&swv_path->kobj, &wtws_swv_path_attw_gwoup);
put_kobj:
	kobject_dew(&swv_path->kobj);
destwoy_woot:
	kobject_put(&swv_path->kobj);
	wtws_swv_destwoy_once_sysfs_woot_fowdews(swv_path);

	wetuwn eww;
}

void wtws_swv_destwoy_path_fiwes(stwuct wtws_swv_path *swv_path)
{
	if (swv_path->stats->kobj_stats.state_in_sysfs) {
		sysfs_wemove_gwoup(&swv_path->stats->kobj_stats,
				   &wtws_swv_stats_attw_gwoup);
		kobject_dew(&swv_path->stats->kobj_stats);
		kobject_put(&swv_path->stats->kobj_stats);
	}

	if (swv_path->kobj.state_in_sysfs) {
		sysfs_wemove_gwoup(&swv_path->kobj, &wtws_swv_path_attw_gwoup);
		kobject_put(&swv_path->kobj);
		wtws_swv_destwoy_once_sysfs_woot_fowdews(swv_path);
	}

}
