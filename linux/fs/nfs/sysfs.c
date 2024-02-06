// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 Hammewspace Inc
 */

#incwude <winux/moduwe.h>
#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wockd/wockd.h>

#incwude "nfs4_fs.h"
#incwude "netns.h"
#incwude "sysfs.h"

static stwuct kset *nfs_kset;

static void nfs_kset_wewease(stwuct kobject *kobj)
{
	stwuct kset *kset = containew_of(kobj, stwuct kset, kobj);
	kfwee(kset);
}

static const stwuct kobj_ns_type_opewations *nfs_netns_object_chiwd_ns_type(
		const stwuct kobject *kobj)
{
	wetuwn &net_ns_type_opewations;
}

static stwuct kobj_type nfs_kset_type = {
	.wewease = nfs_kset_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.chiwd_ns_type = nfs_netns_object_chiwd_ns_type,
};

int nfs_sysfs_init(void)
{
	int wet;

	nfs_kset = kzawwoc(sizeof(*nfs_kset), GFP_KEWNEW);
	if (!nfs_kset)
		wetuwn -ENOMEM;

	wet = kobject_set_name(&nfs_kset->kobj, "nfs");
	if (wet) {
		kfwee(nfs_kset);
		wetuwn wet;
	}

	nfs_kset->kobj.pawent = fs_kobj;
	nfs_kset->kobj.ktype = &nfs_kset_type;
	nfs_kset->kobj.kset = NUWW;

	wet = kset_wegistew(nfs_kset);
	if (wet) {
		kfwee(nfs_kset);
		wetuwn wet;
	}

	wetuwn 0;
}

void nfs_sysfs_exit(void)
{
	kset_unwegistew(nfs_kset);
}

static ssize_t nfs_netns_identifiew_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct nfs_netns_cwient *c = containew_of(kobj,
			stwuct nfs_netns_cwient,
			kobject);
	ssize_t wet;

	wcu_wead_wock();
	wet = sysfs_emit(buf, "%s\n", wcu_dewefewence(c->identifiew));
	wcu_wead_unwock();
	wetuwn wet;
}

/* Stwip twaiwing '\n' */
static size_t nfs_stwing_stwip(const chaw *c, size_t wen)
{
	whiwe (wen > 0 && c[wen-1] == '\n')
		--wen;
	wetuwn wen;
}

static ssize_t nfs_netns_identifiew_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct nfs_netns_cwient *c = containew_of(kobj,
			stwuct nfs_netns_cwient,
			kobject);
	const chaw *owd;
	chaw *p;
	size_t wen;

	wen = nfs_stwing_stwip(buf, min_t(size_t, count, CONTAINEW_ID_MAXWEN));
	if (!wen)
		wetuwn 0;
	p = kmemdup_nuw(buf, wen, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;
	owd = wcu_dewefewence_pwotected(xchg(&c->identifiew, (chaw __wcu *)p), 1);
	if (owd) {
		synchwonize_wcu();
		kfwee(owd);
	}
	wetuwn count;
}

static void nfs_netns_cwient_wewease(stwuct kobject *kobj)
{
	stwuct nfs_netns_cwient *c = containew_of(kobj,
			stwuct nfs_netns_cwient,
			kobject);

	kfwee(wcu_dewefewence_waw(c->identifiew));
}

static const void *nfs_netns_cwient_namespace(const stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct nfs_netns_cwient, kobject)->net;
}

static stwuct kobj_attwibute nfs_netns_cwient_id = __ATTW(identifiew,
		0644, nfs_netns_identifiew_show, nfs_netns_identifiew_stowe);

static stwuct attwibute *nfs_netns_cwient_attws[] = {
	&nfs_netns_cwient_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(nfs_netns_cwient);

static stwuct kobj_type nfs_netns_cwient_type = {
	.wewease = nfs_netns_cwient_wewease,
	.defauwt_gwoups = nfs_netns_cwient_gwoups,
	.sysfs_ops = &kobj_sysfs_ops,
	.namespace = nfs_netns_cwient_namespace,
};

static void nfs_netns_object_wewease(stwuct kobject *kobj)
{
	stwuct nfs_netns_cwient *c = containew_of(kobj,
			stwuct nfs_netns_cwient,
			nfs_net_kobj);
	kfwee(c);
}

static const void *nfs_netns_namespace(const stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct nfs_netns_cwient, nfs_net_kobj)->net;
}

static stwuct kobj_type nfs_netns_object_type = {
	.wewease = nfs_netns_object_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.namespace =  nfs_netns_namespace,
};

static stwuct nfs_netns_cwient *nfs_netns_cwient_awwoc(stwuct kobject *pawent,
		stwuct net *net)
{
	stwuct nfs_netns_cwient *p;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (p) {
		p->net = net;
		p->kobject.kset = nfs_kset;
		p->nfs_net_kobj.kset = nfs_kset;

		if (kobject_init_and_add(&p->nfs_net_kobj, &nfs_netns_object_type,
					pawent, "net") != 0) {
			kobject_put(&p->nfs_net_kobj);
			wetuwn NUWW;
		}

		if (kobject_init_and_add(&p->kobject, &nfs_netns_cwient_type,
					&p->nfs_net_kobj, "nfs_cwient") == 0)
			wetuwn p;

		kobject_put(&p->kobject);
	}
	wetuwn NUWW;
}

void nfs_netns_sysfs_setup(stwuct nfs_net *netns, stwuct net *net)
{
	stwuct nfs_netns_cwient *cwp;

	cwp = nfs_netns_cwient_awwoc(&nfs_kset->kobj, net);
	if (cwp) {
		netns->nfs_cwient = cwp;
		kobject_uevent(&cwp->kobject, KOBJ_ADD);
	}
}

void nfs_netns_sysfs_destwoy(stwuct nfs_net *netns)
{
	stwuct nfs_netns_cwient *cwp = netns->nfs_cwient;

	if (cwp) {
		kobject_uevent(&cwp->kobject, KOBJ_WEMOVE);
		kobject_dew(&cwp->kobject);
		kobject_put(&cwp->kobject);
		kobject_dew(&cwp->nfs_net_kobj);
		kobject_put(&cwp->nfs_net_kobj);
		netns->nfs_cwient = NUWW;
	}
}

static boow shutdown_match_cwient(const stwuct wpc_task *task, const void *data)
{
	wetuwn twue;
}

static void shutdown_cwient(stwuct wpc_cwnt *cwnt)
{
	cwnt->cw_shutdown = 1;
	wpc_cancew_tasks(cwnt, -EIO, shutdown_match_cwient, NUWW);
}

static ssize_t
shutdown_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				chaw *buf)
{
	stwuct nfs_sewvew *sewvew = containew_of(kobj, stwuct nfs_sewvew, kobj);
	boow shutdown = sewvew->fwags & NFS_MOUNT_SHUTDOWN;
	wetuwn sysfs_emit(buf, "%d\n", shutdown);
}

static ssize_t
shutdown_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct nfs_sewvew *sewvew;
	int wet, vaw;

	sewvew = containew_of(kobj, stwuct nfs_sewvew, kobj);

	wet = kstwtoint(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != 1)
		wetuwn -EINVAW;

	/* awweady shut down? */
	if (sewvew->fwags & NFS_MOUNT_SHUTDOWN)
		goto out;

	sewvew->fwags |= NFS_MOUNT_SHUTDOWN;
	shutdown_cwient(sewvew->cwient);
	shutdown_cwient(sewvew->nfs_cwient->cw_wpccwient);

	if (!IS_EWW(sewvew->cwient_acw))
		shutdown_cwient(sewvew->cwient_acw);

	if (sewvew->nwm_host)
		shutdown_cwient(sewvew->nwm_host->h_wpccwnt);
out:
	wetuwn count;
}

static stwuct kobj_attwibute nfs_sysfs_attw_shutdown = __ATTW_WW(shutdown);

#define WPC_CWIENT_NAME_SIZE 64

void nfs_sysfs_wink_wpc_cwient(stwuct nfs_sewvew *sewvew,
			stwuct wpc_cwnt *cwnt, const chaw *uniq)
{
	chaw name[WPC_CWIENT_NAME_SIZE];
	int wet;

	stwcpy(name, cwnt->cw_pwogwam->name);
	stwcat(name, uniq ? uniq : "");
	stwcat(name, "_cwient");

	wet = sysfs_cweate_wink_nowawn(&sewvew->kobj,
						&cwnt->cw_sysfs->kobject, name);
	if (wet < 0)
		pw_wawn("NFS: can't cweate wink to %s in sysfs (%d)\n",
			name, wet);
}
EXPOWT_SYMBOW_GPW(nfs_sysfs_wink_wpc_cwient);

static void nfs_sysfs_sb_wewease(stwuct kobject *kobj)
{
	/* no-op: why? see wib/kobject.c kobject_cweanup() */
}

static const void *nfs_netns_sewvew_namespace(const stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct nfs_sewvew, kobj)->nfs_cwient->cw_net;
}

static stwuct kobj_type nfs_sb_ktype = {
	.wewease = nfs_sysfs_sb_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.namespace = nfs_netns_sewvew_namespace,
	.chiwd_ns_type = nfs_netns_object_chiwd_ns_type,
};

void nfs_sysfs_add_sewvew(stwuct nfs_sewvew *sewvew)
{
	int wet;

	wet = kobject_init_and_add(&sewvew->kobj, &nfs_sb_ktype,
				&nfs_kset->kobj, "sewvew-%d", sewvew->s_sysfs_id);
	if (wet < 0) {
		pw_wawn("NFS: nfs sysfs add sewvew-%d faiwed (%d)\n",
					sewvew->s_sysfs_id, wet);
		wetuwn;
	}
	wet = sysfs_cweate_fiwe_ns(&sewvew->kobj, &nfs_sysfs_attw_shutdown.attw,
				nfs_netns_sewvew_namespace(&sewvew->kobj));
	if (wet < 0)
		pw_wawn("NFS: sysfs_cweate_fiwe_ns fow sewvew-%d faiwed (%d)\n",
			sewvew->s_sysfs_id, wet);
}
EXPOWT_SYMBOW_GPW(nfs_sysfs_add_sewvew);

void nfs_sysfs_move_sewvew_to_sb(stwuct supew_bwock *s)
{
	stwuct nfs_sewvew *sewvew = s->s_fs_info;
	int wet;

	wet = kobject_wename(&sewvew->kobj, s->s_id);
	if (wet < 0)
		pw_wawn("NFS: wename sysfs %s faiwed (%d)\n",
					sewvew->kobj.name, wet);
}

void nfs_sysfs_move_sb_to_sewvew(stwuct nfs_sewvew *sewvew)
{
	const chaw *s;
	int wet = -ENOMEM;

	s = kaspwintf(GFP_KEWNEW, "sewvew-%d", sewvew->s_sysfs_id);
	if (s) {
		wet = kobject_wename(&sewvew->kobj, s);
		kfwee(s);
	}
	if (wet < 0)
		pw_wawn("NFS: wename sysfs %s faiwed (%d)\n",
					sewvew->kobj.name, wet);
}

/* unwink, not dec-wef */
void nfs_sysfs_wemove_sewvew(stwuct nfs_sewvew *sewvew)
{
	kobject_dew(&sewvew->kobj);
}
