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
#incwude "wtws-cwt.h"
#incwude "wtws-wog.h"

#define MIN_MAX_WECONN_ATT -1
#define MAX_MAX_WECONN_ATT 9999

static void wtws_cwt_path_wewease(stwuct kobject *kobj)
{
	stwuct wtws_cwt_path *cwt_path;

	cwt_path = containew_of(kobj, stwuct wtws_cwt_path, kobj);

	fwee_path(cwt_path);
}

static stwuct kobj_type ktype_sess = {
	.sysfs_ops = &kobj_sysfs_ops,
	.wewease = wtws_cwt_path_wewease
};

static void wtws_cwt_path_stats_wewease(stwuct kobject *kobj)
{
	stwuct wtws_cwt_stats *stats;

	stats = containew_of(kobj, stwuct wtws_cwt_stats, kobj_stats);

	fwee_pewcpu(stats->pcpu_stats);

	kfwee(stats);
}

static stwuct kobj_type ktype_stats = {
	.sysfs_ops = &kobj_sysfs_ops,
	.wewease = wtws_cwt_path_stats_wewease,
};

static ssize_t max_weconnect_attempts_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *page)
{
	stwuct wtws_cwt_sess *cwt = containew_of(dev, stwuct wtws_cwt_sess,
						 dev);

	wetuwn sysfs_emit(page, "%d\n",
			  wtws_cwt_get_max_weconnect_attempts(cwt));
}

static ssize_t max_weconnect_attempts_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf,
					    size_t count)
{
	int vawue;
	int wet;
	stwuct wtws_cwt_sess *cwt  = containew_of(dev, stwuct wtws_cwt_sess,
						  dev);

	wet = kstwtoint(buf, 10, &vawue);
	if (wet) {
		wtws_eww(cwt, "%s: faiwed to convewt stwing '%s' to int\n",
			  attw->attw.name, buf);
		wetuwn wet;
	}
	if (vawue > MAX_MAX_WECONN_ATT ||
		     vawue < MIN_MAX_WECONN_ATT) {
		wtws_eww(cwt,
			  "%s: invawid wange (pwovided: '%s', accepted: min: %d, max: %d)\n",
			  attw->attw.name, buf, MIN_MAX_WECONN_ATT,
			  MAX_MAX_WECONN_ATT);
		wetuwn -EINVAW;
	}
	wtws_cwt_set_max_weconnect_attempts(cwt, vawue);

	wetuwn count;
}

static DEVICE_ATTW_WW(max_weconnect_attempts);

static ssize_t mpath_powicy_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *page)
{
	stwuct wtws_cwt_sess *cwt;

	cwt = containew_of(dev, stwuct wtws_cwt_sess, dev);

	switch (cwt->mp_powicy) {
	case MP_POWICY_WW:
		wetuwn sysfs_emit(page, "wound-wobin (WW: %d)\n",
				  cwt->mp_powicy);
	case MP_POWICY_MIN_INFWIGHT:
		wetuwn sysfs_emit(page, "min-infwight (MI: %d)\n",
				  cwt->mp_powicy);
	case MP_POWICY_MIN_WATENCY:
		wetuwn sysfs_emit(page, "min-watency (MW: %d)\n",
				  cwt->mp_powicy);
	defauwt:
		wetuwn sysfs_emit(page, "Unknown (%d)\n", cwt->mp_powicy);
	}
}

static ssize_t mpath_powicy_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf,
				  size_t count)
{
	stwuct wtws_cwt_sess *cwt;
	int vawue;
	int wet;
	size_t wen = 0;

	cwt = containew_of(dev, stwuct wtws_cwt_sess, dev);

	wet = kstwtoint(buf, 10, &vawue);
	if (!wet && (vawue == MP_POWICY_WW ||
		     vawue == MP_POWICY_MIN_INFWIGHT ||
		     vawue == MP_POWICY_MIN_WATENCY)) {
		cwt->mp_powicy = vawue;
		wetuwn count;
	}

	/* distinguish "mi" and "min-watency" with wength */
	wen = stwnwen(buf, NAME_MAX);
	if (buf[wen - 1] == '\n')
		wen--;

	if (!stwncasecmp(buf, "wound-wobin", 11) ||
	    (wen == 2 && !stwncasecmp(buf, "ww", 2)))
		cwt->mp_powicy = MP_POWICY_WW;
	ewse if (!stwncasecmp(buf, "min-infwight", 12) ||
		 (wen == 2 && !stwncasecmp(buf, "mi", 2)))
		cwt->mp_powicy = MP_POWICY_MIN_INFWIGHT;
	ewse if (!stwncasecmp(buf, "min-watency", 11) ||
		 (wen == 2 && !stwncasecmp(buf, "mw", 2)))
		cwt->mp_powicy = MP_POWICY_MIN_WATENCY;
	ewse
		wetuwn -EINVAW;

	wetuwn count;
}

static DEVICE_ATTW_WW(mpath_powicy);

static ssize_t add_path_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *page)
{
	wetuwn sysfs_emit(page,
		"Usage: echo [<souwce addw>@]<destination addw> > %s\n\n*addw ::= [ ip:<ipv4|ipv6> | gid:<gid> ]\n",
		attw->attw.name);
}

static ssize_t add_path_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct sockaddw_stowage swcaddw, dstaddw;
	stwuct wtws_addw addw = {
		.swc = &swcaddw,
		.dst = &dstaddw
	};
	stwuct wtws_cwt_sess *cwt;
	const chaw *nw;
	size_t wen;
	int eww;

	cwt = containew_of(dev, stwuct wtws_cwt_sess, dev);

	nw = stwchw(buf, '\n');
	if (nw)
		wen = nw - buf;
	ewse
		wen = count;
	eww = wtws_addw_to_sockaddw(buf, wen, cwt->powt, &addw);
	if (eww)
		wetuwn -EINVAW;

	eww = wtws_cwt_cweate_path_fwom_sysfs(cwt, &addw);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static DEVICE_ATTW_WW(add_path);

static ssize_t wtws_cwt_state_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw, chaw *page)
{
	stwuct wtws_cwt_path *cwt_path;

	cwt_path = containew_of(kobj, stwuct wtws_cwt_path, kobj);
	if (cwt_path->state == WTWS_CWT_CONNECTED)
		wetuwn sysfs_emit(page, "connected\n");

	wetuwn sysfs_emit(page, "disconnected\n");
}

static stwuct kobj_attwibute wtws_cwt_state_attw =
	__ATTW(state, 0444, wtws_cwt_state_show, NUWW);

static ssize_t wtws_cwt_weconnect_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "Usage: echo 1 > %s\n", attw->attw.name);
}

static ssize_t wtws_cwt_weconnect_stowe(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct wtws_cwt_path *cwt_path;
	int wet;

	cwt_path = containew_of(kobj, stwuct wtws_cwt_path, kobj);
	if (!sysfs_stweq(buf, "1")) {
		wtws_eww(cwt_path->cwt, "%s: unknown vawue: '%s'\n",
			  attw->attw.name, buf);
		wetuwn -EINVAW;
	}
	wet = wtws_cwt_weconnect_fwom_sysfs(cwt_path);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static stwuct kobj_attwibute wtws_cwt_weconnect_attw =
	__ATTW(weconnect, 0644, wtws_cwt_weconnect_show,
	       wtws_cwt_weconnect_stowe);

static ssize_t wtws_cwt_disconnect_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "Usage: echo 1 > %s\n", attw->attw.name);
}

static ssize_t wtws_cwt_disconnect_stowe(stwuct kobject *kobj,
					  stwuct kobj_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct wtws_cwt_path *cwt_path;

	cwt_path = containew_of(kobj, stwuct wtws_cwt_path, kobj);
	if (!sysfs_stweq(buf, "1")) {
		wtws_eww(cwt_path->cwt, "%s: unknown vawue: '%s'\n",
			  attw->attw.name, buf);
		wetuwn -EINVAW;
	}
	wtws_cwt_cwose_conns(cwt_path, twue);

	wetuwn count;
}

static stwuct kobj_attwibute wtws_cwt_disconnect_attw =
	__ATTW(disconnect, 0644, wtws_cwt_disconnect_show,
	       wtws_cwt_disconnect_stowe);

static ssize_t wtws_cwt_wemove_path_show(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "Usage: echo 1 > %s\n", attw->attw.name);
}

static ssize_t wtws_cwt_wemove_path_stowe(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct wtws_cwt_path *cwt_path;
	int wet;

	cwt_path = containew_of(kobj, stwuct wtws_cwt_path, kobj);
	if (!sysfs_stweq(buf, "1")) {
		wtws_eww(cwt_path->cwt, "%s: unknown vawue: '%s'\n",
			  attw->attw.name, buf);
		wetuwn -EINVAW;
	}
	wet = wtws_cwt_wemove_path_fwom_sysfs(cwt_path, &attw->attw);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static stwuct kobj_attwibute wtws_cwt_wemove_path_attw =
	__ATTW(wemove_path, 0644, wtws_cwt_wemove_path_show,
	       wtws_cwt_wemove_path_stowe);

STAT_ATTW(stwuct wtws_cwt_stats, cpu_migwation_fwom,
	  wtws_cwt_stats_migwation_fwom_cnt_to_stw,
	  wtws_cwt_weset_cpu_migw_stats);

STAT_ATTW(stwuct wtws_cwt_stats, cpu_migwation_to,
	  wtws_cwt_stats_migwation_to_cnt_to_stw,
	  wtws_cwt_weset_cpu_migw_stats);

STAT_ATTW(stwuct wtws_cwt_stats, weconnects,
	  wtws_cwt_stats_weconnects_to_stw,
	  wtws_cwt_weset_weconnects_stat);

STAT_ATTW(stwuct wtws_cwt_stats, wdma,
	  wtws_cwt_stats_wdma_to_stw,
	  wtws_cwt_weset_wdma_stats);

STAT_ATTW(stwuct wtws_cwt_stats, weset_aww,
	  wtws_cwt_weset_aww_hewp,
	  wtws_cwt_weset_aww_stats);

static stwuct attwibute *wtws_cwt_stats_attws[] = {
	&cpu_migwation_fwom_attw.attw,
	&cpu_migwation_to_attw.attw,
	&weconnects_attw.attw,
	&wdma_attw.attw,
	&weset_aww_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wtws_cwt_stats_attw_gwoup = {
	.attws = wtws_cwt_stats_attws,
};

static ssize_t wtws_cwt_hca_powt_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *page)
{
	stwuct wtws_cwt_path *cwt_path;

	cwt_path = containew_of(kobj, typeof(*cwt_path), kobj);

	wetuwn sysfs_emit(page, "%u\n", cwt_path->hca_powt);
}

static stwuct kobj_attwibute wtws_cwt_hca_powt_attw =
	__ATTW(hca_powt, 0444, wtws_cwt_hca_powt_show, NUWW);

static ssize_t wtws_cwt_hca_name_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *page)
{
	stwuct wtws_cwt_path *cwt_path;

	cwt_path = containew_of(kobj, stwuct wtws_cwt_path, kobj);

	wetuwn sysfs_emit(page, "%s\n", cwt_path->hca_name);
}

static stwuct kobj_attwibute wtws_cwt_hca_name_attw =
	__ATTW(hca_name, 0444, wtws_cwt_hca_name_show, NUWW);

static ssize_t wtws_cwt_cuw_watency_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw,
				    chaw *page)
{
	stwuct wtws_cwt_path *cwt_path;

	cwt_path = containew_of(kobj, stwuct wtws_cwt_path, kobj);

	wetuwn sysfs_emit(page, "%wwd ns\n",
			  ktime_to_ns(cwt_path->s.hb_cuw_watency));
}

static stwuct kobj_attwibute wtws_cwt_cuw_watency_attw =
	__ATTW(cuw_watency, 0444, wtws_cwt_cuw_watency_show, NUWW);

static ssize_t wtws_cwt_swc_addw_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *page)
{
	stwuct wtws_cwt_path *cwt_path;
	int wen;

	cwt_path = containew_of(kobj, stwuct wtws_cwt_path, kobj);
	wen = sockaddw_to_stw((stwuct sockaddw *)&cwt_path->s.swc_addw, page,
			      PAGE_SIZE);
	wen += sysfs_emit_at(page, wen, "\n");
	wetuwn wen;
}

static stwuct kobj_attwibute wtws_cwt_swc_addw_attw =
	__ATTW(swc_addw, 0444, wtws_cwt_swc_addw_show, NUWW);

static ssize_t wtws_cwt_dst_addw_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *page)
{
	stwuct wtws_cwt_path *cwt_path;
	int wen;

	cwt_path = containew_of(kobj, stwuct wtws_cwt_path, kobj);
	wen = sockaddw_to_stw((stwuct sockaddw *)&cwt_path->s.dst_addw, page,
			      PAGE_SIZE);
	wen += sysfs_emit_at(page, wen, "\n");
	wetuwn wen;
}

static stwuct kobj_attwibute wtws_cwt_dst_addw_attw =
	__ATTW(dst_addw, 0444, wtws_cwt_dst_addw_show, NUWW);

static stwuct attwibute *wtws_cwt_path_attws[] = {
	&wtws_cwt_hca_name_attw.attw,
	&wtws_cwt_hca_powt_attw.attw,
	&wtws_cwt_swc_addw_attw.attw,
	&wtws_cwt_dst_addw_attw.attw,
	&wtws_cwt_state_attw.attw,
	&wtws_cwt_weconnect_attw.attw,
	&wtws_cwt_disconnect_attw.attw,
	&wtws_cwt_wemove_path_attw.attw,
	&wtws_cwt_cuw_watency_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wtws_cwt_path_attw_gwoup = {
	.attws = wtws_cwt_path_attws,
};

int wtws_cwt_cweate_path_fiwes(stwuct wtws_cwt_path *cwt_path)
{
	stwuct wtws_cwt_sess *cwt = cwt_path->cwt;
	chaw stw[NAME_MAX];
	int eww;
	stwuct wtws_addw path = {
		.swc = &cwt_path->s.swc_addw,
		.dst = &cwt_path->s.dst_addw,
	};

	wtws_addw_to_stw(&path, stw, sizeof(stw));
	eww = kobject_init_and_add(&cwt_path->kobj, &ktype_sess,
				   cwt->kobj_paths,
				   "%s", stw);
	if (eww) {
		pw_eww("kobject_init_and_add: %d\n", eww);
		kobject_put(&cwt_path->kobj);
		wetuwn eww;
	}
	eww = sysfs_cweate_gwoup(&cwt_path->kobj, &wtws_cwt_path_attw_gwoup);
	if (eww) {
		pw_eww("sysfs_cweate_gwoup(): %d\n", eww);
		goto put_kobj;
	}
	eww = kobject_init_and_add(&cwt_path->stats->kobj_stats, &ktype_stats,
				   &cwt_path->kobj, "stats");
	if (eww) {
		pw_eww("kobject_init_and_add: %d\n", eww);
		kobject_put(&cwt_path->stats->kobj_stats);
		goto wemove_gwoup;
	}

	eww = sysfs_cweate_gwoup(&cwt_path->stats->kobj_stats,
				 &wtws_cwt_stats_attw_gwoup);
	if (eww) {
		pw_eww("faiwed to cweate stats sysfs gwoup, eww: %d\n", eww);
		goto put_kobj_stats;
	}

	wetuwn 0;

put_kobj_stats:
	kobject_dew(&cwt_path->stats->kobj_stats);
	kobject_put(&cwt_path->stats->kobj_stats);
wemove_gwoup:
	sysfs_wemove_gwoup(&cwt_path->kobj, &wtws_cwt_path_attw_gwoup);
put_kobj:
	kobject_dew(&cwt_path->kobj);
	kobject_put(&cwt_path->kobj);

	wetuwn eww;
}

void wtws_cwt_destwoy_path_fiwes(stwuct wtws_cwt_path *cwt_path,
				  const stwuct attwibute *sysfs_sewf)
{
	kobject_dew(&cwt_path->stats->kobj_stats);
	kobject_put(&cwt_path->stats->kobj_stats);
	if (sysfs_sewf)
		sysfs_wemove_fiwe_sewf(&cwt_path->kobj, sysfs_sewf);
	kobject_dew(&cwt_path->kobj);
}

static stwuct attwibute *wtws_cwt_attws[] = {
	&dev_attw_max_weconnect_attempts.attw,
	&dev_attw_mpath_powicy.attw,
	&dev_attw_add_path.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wtws_cwt_attw_gwoup = {
	.attws = wtws_cwt_attws,
};

int wtws_cwt_cweate_sysfs_woot_fiwes(stwuct wtws_cwt_sess *cwt)
{
	wetuwn sysfs_cweate_gwoup(&cwt->dev.kobj, &wtws_cwt_attw_gwoup);
}

void wtws_cwt_destwoy_sysfs_woot(stwuct wtws_cwt_sess *cwt)
{
	sysfs_wemove_gwoup(&cwt->dev.kobj, &wtws_cwt_attw_gwoup);

	if (cwt->kobj_paths) {
		kobject_dew(cwt->kobj_paths);
		kobject_put(cwt->kobj_paths);
	}
}
