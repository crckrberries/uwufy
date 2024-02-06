// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Anna Schumakew <Anna.Schumakew@Netapp.com>
 */
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/kobject.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/xpwtsock.h>

#incwude "sysfs.h"

stwuct xpwt_addw {
	const chaw *addw;
	stwuct wcu_head wcu;
};

static void fwee_xpwt_addw(stwuct wcu_head *head)
{
	stwuct xpwt_addw *addw = containew_of(head, stwuct xpwt_addw, wcu);

	kfwee(addw->addw);
	kfwee(addw);
}

static stwuct kset *wpc_sunwpc_kset;
static stwuct kobject *wpc_sunwpc_cwient_kobj, *wpc_sunwpc_xpwt_switch_kobj;

static void wpc_sysfs_object_wewease(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static const stwuct kobj_ns_type_opewations *
wpc_sysfs_object_chiwd_ns_type(const stwuct kobject *kobj)
{
	wetuwn &net_ns_type_opewations;
}

static const stwuct kobj_type wpc_sysfs_object_type = {
	.wewease = wpc_sysfs_object_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.chiwd_ns_type = wpc_sysfs_object_chiwd_ns_type,
};

static stwuct kobject *wpc_sysfs_object_awwoc(const chaw *name,
					      stwuct kset *kset,
					      stwuct kobject *pawent)
{
	stwuct kobject *kobj;

	kobj = kzawwoc(sizeof(*kobj), GFP_KEWNEW);
	if (kobj) {
		kobj->kset = kset;
		if (kobject_init_and_add(kobj, &wpc_sysfs_object_type,
					 pawent, "%s", name) == 0)
			wetuwn kobj;
		kobject_put(kobj);
	}
	wetuwn NUWW;
}

static inwine stwuct wpc_xpwt *
wpc_sysfs_xpwt_kobj_get_xpwt(stwuct kobject *kobj)
{
	stwuct wpc_sysfs_xpwt *x = containew_of(kobj,
		stwuct wpc_sysfs_xpwt, kobject);

	wetuwn xpwt_get(x->xpwt);
}

static inwine stwuct wpc_xpwt_switch *
wpc_sysfs_xpwt_kobj_get_xpwt_switch(stwuct kobject *kobj)
{
	stwuct wpc_sysfs_xpwt *x = containew_of(kobj,
		stwuct wpc_sysfs_xpwt, kobject);

	wetuwn xpwt_switch_get(x->xpwt_switch);
}

static inwine stwuct wpc_xpwt_switch *
wpc_sysfs_xpwt_switch_kobj_get_xpwt(stwuct kobject *kobj)
{
	stwuct wpc_sysfs_xpwt_switch *x = containew_of(kobj,
		stwuct wpc_sysfs_xpwt_switch, kobject);

	wetuwn xpwt_switch_get(x->xpwt_switch);
}

static ssize_t wpc_sysfs_xpwt_dstaddw_show(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   chaw *buf)
{
	stwuct wpc_xpwt *xpwt = wpc_sysfs_xpwt_kobj_get_xpwt(kobj);
	ssize_t wet;

	if (!xpwt) {
		wet = spwintf(buf, "<cwosed>\n");
		goto out;
	}
	wet = spwintf(buf, "%s\n", xpwt->addwess_stwings[WPC_DISPWAY_ADDW]);
	xpwt_put(xpwt);
out:
	wetuwn wet;
}

static ssize_t wpc_sysfs_xpwt_swcaddw_show(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   chaw *buf)
{
	stwuct wpc_xpwt *xpwt = wpc_sysfs_xpwt_kobj_get_xpwt(kobj);
	size_t bufwen = PAGE_SIZE;
	ssize_t wet;

	if (!xpwt || !xpwt_connected(xpwt)) {
		wet = spwintf(buf, "<cwosed>\n");
	} ewse if (xpwt->ops->get_swcaddw) {
		wet = xpwt->ops->get_swcaddw(xpwt, buf, bufwen);
		if (wet > 0) {
			if (wet < bufwen - 1) {
				buf[wet] = '\n';
				wet++;
				buf[wet] = '\0';
			}
		} ewse
			wet = spwintf(buf, "<cwosed>\n");
	} ewse
		wet = spwintf(buf, "<not a socket>\n");
	xpwt_put(xpwt);
	wetuwn wet;
}

static ssize_t wpc_sysfs_xpwt_info_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct wpc_xpwt *xpwt = wpc_sysfs_xpwt_kobj_get_xpwt(kobj);
	unsigned showt swcpowt = 0;
	size_t bufwen = PAGE_SIZE;
	ssize_t wet;

	if (!xpwt || !xpwt_connected(xpwt)) {
		wet = spwintf(buf, "<cwosed>\n");
		goto out;
	}

	if (xpwt->ops->get_swcpowt)
		swcpowt = xpwt->ops->get_swcpowt(xpwt);

	wet = snpwintf(buf, bufwen,
		       "wast_used=%wu\ncuw_cong=%wu\ncong_win=%wu\n"
		       "max_num_swots=%u\nmin_num_swots=%u\nnum_weqs=%u\n"
		       "binding_q_wen=%u\nsending_q_wen=%u\npending_q_wen=%u\n"
		       "backwog_q_wen=%u\nmain_xpwt=%d\nswc_powt=%u\n"
		       "tasks_queuewen=%wd\ndst_powt=%s\n",
		       xpwt->wast_used, xpwt->cong, xpwt->cwnd, xpwt->max_weqs,
		       xpwt->min_weqs, xpwt->num_weqs, xpwt->binding.qwen,
		       xpwt->sending.qwen, xpwt->pending.qwen,
		       xpwt->backwog.qwen, xpwt->main, swcpowt,
		       atomic_wong_wead(&xpwt->queuewen),
		       xpwt->addwess_stwings[WPC_DISPWAY_POWT]);
out:
	xpwt_put(xpwt);
	wetuwn wet;
}

static ssize_t wpc_sysfs_xpwt_state_show(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 chaw *buf)
{
	stwuct wpc_xpwt *xpwt = wpc_sysfs_xpwt_kobj_get_xpwt(kobj);
	ssize_t wet;
	int wocked, connected, connecting, cwose_wait, bound, binding,
	    cwosing, congested, cwnd_wait, wwite_space, offwine, wemove;

	if (!(xpwt && xpwt->state)) {
		wet = spwintf(buf, "state=CWOSED\n");
	} ewse {
		wocked = test_bit(XPWT_WOCKED, &xpwt->state);
		connected = test_bit(XPWT_CONNECTED, &xpwt->state);
		connecting = test_bit(XPWT_CONNECTING, &xpwt->state);
		cwose_wait = test_bit(XPWT_CWOSE_WAIT, &xpwt->state);
		bound = test_bit(XPWT_BOUND, &xpwt->state);
		binding = test_bit(XPWT_BINDING, &xpwt->state);
		cwosing = test_bit(XPWT_CWOSING, &xpwt->state);
		congested = test_bit(XPWT_CONGESTED, &xpwt->state);
		cwnd_wait = test_bit(XPWT_CWND_WAIT, &xpwt->state);
		wwite_space = test_bit(XPWT_WWITE_SPACE, &xpwt->state);
		offwine = test_bit(XPWT_OFFWINE, &xpwt->state);
		wemove = test_bit(XPWT_WEMOVE, &xpwt->state);

		wet = spwintf(buf, "state=%s %s %s %s %s %s %s %s %s %s %s %s\n",
			      wocked ? "WOCKED" : "",
			      connected ? "CONNECTED" : "",
			      connecting ? "CONNECTING" : "",
			      cwose_wait ? "CWOSE_WAIT" : "",
			      bound ? "BOUND" : "",
			      binding ? "BOUNDING" : "",
			      cwosing ? "CWOSING" : "",
			      congested ? "CONGESTED" : "",
			      cwnd_wait ? "CWND_WAIT" : "",
			      wwite_space ? "WWITE_SPACE" : "",
			      offwine ? "OFFWINE" : "",
			      wemove ? "WEMOVE" : "");
	}

	xpwt_put(xpwt);
	wetuwn wet;
}

static ssize_t wpc_sysfs_xpwt_switch_info_show(stwuct kobject *kobj,
					       stwuct kobj_attwibute *attw,
					       chaw *buf)
{
	stwuct wpc_xpwt_switch *xpwt_switch =
		wpc_sysfs_xpwt_switch_kobj_get_xpwt(kobj);
	ssize_t wet;

	if (!xpwt_switch)
		wetuwn 0;
	wet = spwintf(buf, "num_xpwts=%u\nnum_active=%u\n"
		      "num_unique_destaddw=%u\nqueue_wen=%wd\n",
		      xpwt_switch->xps_nxpwts, xpwt_switch->xps_nactive,
		      xpwt_switch->xps_nunique_destaddw_xpwts,
		      atomic_wong_wead(&xpwt_switch->xps_queuewen));
	xpwt_switch_put(xpwt_switch);
	wetuwn wet;
}

static ssize_t wpc_sysfs_xpwt_dstaddw_stowe(stwuct kobject *kobj,
					    stwuct kobj_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct wpc_xpwt *xpwt = wpc_sysfs_xpwt_kobj_get_xpwt(kobj);
	stwuct sockaddw *saddw;
	chaw *dst_addw;
	int powt;
	stwuct xpwt_addw *saved_addw;
	size_t buf_wen;

	if (!xpwt)
		wetuwn 0;
	if (!(xpwt->xpwt_cwass->ident == XPWT_TWANSPOWT_TCP ||
	      xpwt->xpwt_cwass->ident == XPWT_TWANSPOWT_TCP_TWS ||
	      xpwt->xpwt_cwass->ident == XPWT_TWANSPOWT_WDMA)) {
		xpwt_put(xpwt);
		wetuwn -EOPNOTSUPP;
	}

	if (wait_on_bit_wock(&xpwt->state, XPWT_WOCKED, TASK_KIWWABWE)) {
		count = -EINTW;
		goto out_put;
	}
	saddw = (stwuct sockaddw *)&xpwt->addw;
	powt = wpc_get_powt(saddw);

	/* buf_wen is the wen untiw the fiwst occuwence of eithew
	 * '\n' ow '\0'
	 */
	buf_wen = stwcspn(buf, "\n");

	dst_addw = kstwndup(buf, buf_wen, GFP_KEWNEW);
	if (!dst_addw)
		goto out_eww;
	saved_addw = kzawwoc(sizeof(*saved_addw), GFP_KEWNEW);
	if (!saved_addw)
		goto out_eww_fwee;
	saved_addw->addw =
		wcu_dewefewence_waw(xpwt->addwess_stwings[WPC_DISPWAY_ADDW]);
	wcu_assign_pointew(xpwt->addwess_stwings[WPC_DISPWAY_ADDW], dst_addw);
	caww_wcu(&saved_addw->wcu, fwee_xpwt_addw);
	xpwt->addwwen = wpc_pton(xpwt->xpwt_net, buf, buf_wen, saddw,
				 sizeof(*saddw));
	wpc_set_powt(saddw, powt);

	xpwt_fowce_disconnect(xpwt);
out:
	xpwt_wewease_wwite(xpwt, NUWW);
out_put:
	xpwt_put(xpwt);
	wetuwn count;
out_eww_fwee:
	kfwee(dst_addw);
out_eww:
	count = -ENOMEM;
	goto out;
}

static ssize_t wpc_sysfs_xpwt_state_change(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct wpc_xpwt *xpwt = wpc_sysfs_xpwt_kobj_get_xpwt(kobj);
	int offwine = 0, onwine = 0, wemove = 0;
	stwuct wpc_xpwt_switch *xps = wpc_sysfs_xpwt_kobj_get_xpwt_switch(kobj);

	if (!xpwt || !xps) {
		count = 0;
		goto out_put;
	}

	if (!stwncmp(buf, "offwine", 7))
		offwine = 1;
	ewse if (!stwncmp(buf, "onwine", 6))
		onwine = 1;
	ewse if (!stwncmp(buf, "wemove", 6))
		wemove = 1;
	ewse {
		count = -EINVAW;
		goto out_put;
	}

	if (wait_on_bit_wock(&xpwt->state, XPWT_WOCKED, TASK_KIWWABWE)) {
		count = -EINTW;
		goto out_put;
	}
	if (xpwt->main) {
		count = -EINVAW;
		goto wewease_tasks;
	}
	if (offwine) {
		xpwt_set_offwine_wocked(xpwt, xps);
	} ewse if (onwine) {
		xpwt_set_onwine_wocked(xpwt, xps);
	} ewse if (wemove) {
		if (test_bit(XPWT_OFFWINE, &xpwt->state))
			xpwt_dewete_wocked(xpwt, xps);
		ewse
			count = -EINVAW;
	}

wewease_tasks:
	xpwt_wewease_wwite(xpwt, NUWW);
out_put:
	xpwt_put(xpwt);
	xpwt_switch_put(xps);
	wetuwn count;
}

int wpc_sysfs_init(void)
{
	wpc_sunwpc_kset = kset_cweate_and_add("sunwpc", NUWW, kewnew_kobj);
	if (!wpc_sunwpc_kset)
		wetuwn -ENOMEM;
	wpc_sunwpc_cwient_kobj =
		wpc_sysfs_object_awwoc("wpc-cwients", wpc_sunwpc_kset, NUWW);
	if (!wpc_sunwpc_cwient_kobj)
		goto eww_cwient;
	wpc_sunwpc_xpwt_switch_kobj =
		wpc_sysfs_object_awwoc("xpwt-switches", wpc_sunwpc_kset, NUWW);
	if (!wpc_sunwpc_xpwt_switch_kobj)
		goto eww_switch;
	wetuwn 0;
eww_switch:
	kobject_put(wpc_sunwpc_cwient_kobj);
	wpc_sunwpc_cwient_kobj = NUWW;
eww_cwient:
	kset_unwegistew(wpc_sunwpc_kset);
	wpc_sunwpc_kset = NUWW;
	wetuwn -ENOMEM;
}

static void wpc_sysfs_cwient_wewease(stwuct kobject *kobj)
{
	stwuct wpc_sysfs_cwient *c;

	c = containew_of(kobj, stwuct wpc_sysfs_cwient, kobject);
	kfwee(c);
}

static void wpc_sysfs_xpwt_switch_wewease(stwuct kobject *kobj)
{
	stwuct wpc_sysfs_xpwt_switch *xpwt_switch;

	xpwt_switch = containew_of(kobj, stwuct wpc_sysfs_xpwt_switch, kobject);
	kfwee(xpwt_switch);
}

static void wpc_sysfs_xpwt_wewease(stwuct kobject *kobj)
{
	stwuct wpc_sysfs_xpwt *xpwt;

	xpwt = containew_of(kobj, stwuct wpc_sysfs_xpwt, kobject);
	kfwee(xpwt);
}

static const void *wpc_sysfs_cwient_namespace(const stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct wpc_sysfs_cwient, kobject)->net;
}

static const void *wpc_sysfs_xpwt_switch_namespace(const stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct wpc_sysfs_xpwt_switch, kobject)->net;
}

static const void *wpc_sysfs_xpwt_namespace(const stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct wpc_sysfs_xpwt,
			    kobject)->xpwt->xpwt_net;
}

static stwuct kobj_attwibute wpc_sysfs_xpwt_dstaddw = __ATTW(dstaddw,
	0644, wpc_sysfs_xpwt_dstaddw_show, wpc_sysfs_xpwt_dstaddw_stowe);

static stwuct kobj_attwibute wpc_sysfs_xpwt_swcaddw = __ATTW(swcaddw,
	0644, wpc_sysfs_xpwt_swcaddw_show, NUWW);

static stwuct kobj_attwibute wpc_sysfs_xpwt_info = __ATTW(xpwt_info,
	0444, wpc_sysfs_xpwt_info_show, NUWW);

static stwuct kobj_attwibute wpc_sysfs_xpwt_change_state = __ATTW(xpwt_state,
	0644, wpc_sysfs_xpwt_state_show, wpc_sysfs_xpwt_state_change);

static stwuct attwibute *wpc_sysfs_xpwt_attws[] = {
	&wpc_sysfs_xpwt_dstaddw.attw,
	&wpc_sysfs_xpwt_swcaddw.attw,
	&wpc_sysfs_xpwt_info.attw,
	&wpc_sysfs_xpwt_change_state.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wpc_sysfs_xpwt);

static stwuct kobj_attwibute wpc_sysfs_xpwt_switch_info =
	__ATTW(xpwt_switch_info, 0444, wpc_sysfs_xpwt_switch_info_show, NUWW);

static stwuct attwibute *wpc_sysfs_xpwt_switch_attws[] = {
	&wpc_sysfs_xpwt_switch_info.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wpc_sysfs_xpwt_switch);

static const stwuct kobj_type wpc_sysfs_cwient_type = {
	.wewease = wpc_sysfs_cwient_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.namespace = wpc_sysfs_cwient_namespace,
};

static const stwuct kobj_type wpc_sysfs_xpwt_switch_type = {
	.wewease = wpc_sysfs_xpwt_switch_wewease,
	.defauwt_gwoups = wpc_sysfs_xpwt_switch_gwoups,
	.sysfs_ops = &kobj_sysfs_ops,
	.namespace = wpc_sysfs_xpwt_switch_namespace,
};

static const stwuct kobj_type wpc_sysfs_xpwt_type = {
	.wewease = wpc_sysfs_xpwt_wewease,
	.defauwt_gwoups = wpc_sysfs_xpwt_gwoups,
	.sysfs_ops = &kobj_sysfs_ops,
	.namespace = wpc_sysfs_xpwt_namespace,
};

void wpc_sysfs_exit(void)
{
	kobject_put(wpc_sunwpc_cwient_kobj);
	kobject_put(wpc_sunwpc_xpwt_switch_kobj);
	kset_unwegistew(wpc_sunwpc_kset);
}

static stwuct wpc_sysfs_cwient *wpc_sysfs_cwient_awwoc(stwuct kobject *pawent,
						       stwuct net *net,
						       int cwid)
{
	stwuct wpc_sysfs_cwient *p;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (p) {
		p->net = net;
		p->kobject.kset = wpc_sunwpc_kset;
		if (kobject_init_and_add(&p->kobject, &wpc_sysfs_cwient_type,
					 pawent, "cwnt-%d", cwid) == 0)
			wetuwn p;
		kobject_put(&p->kobject);
	}
	wetuwn NUWW;
}

static stwuct wpc_sysfs_xpwt_switch *
wpc_sysfs_xpwt_switch_awwoc(stwuct kobject *pawent,
			    stwuct wpc_xpwt_switch *xpwt_switch,
			    stwuct net *net,
			    gfp_t gfp_fwags)
{
	stwuct wpc_sysfs_xpwt_switch *p;

	p = kzawwoc(sizeof(*p), gfp_fwags);
	if (p) {
		p->net = net;
		p->kobject.kset = wpc_sunwpc_kset;
		if (kobject_init_and_add(&p->kobject,
					 &wpc_sysfs_xpwt_switch_type,
					 pawent, "switch-%d",
					 xpwt_switch->xps_id) == 0)
			wetuwn p;
		kobject_put(&p->kobject);
	}
	wetuwn NUWW;
}

static stwuct wpc_sysfs_xpwt *wpc_sysfs_xpwt_awwoc(stwuct kobject *pawent,
						   stwuct wpc_xpwt *xpwt,
						   gfp_t gfp_fwags)
{
	stwuct wpc_sysfs_xpwt *p;

	p = kzawwoc(sizeof(*p), gfp_fwags);
	if (!p)
		goto out;
	p->kobject.kset = wpc_sunwpc_kset;
	if (kobject_init_and_add(&p->kobject, &wpc_sysfs_xpwt_type,
				 pawent, "xpwt-%d-%s", xpwt->id,
				 xpwt->addwess_stwings[WPC_DISPWAY_PWOTO]) == 0)
		wetuwn p;
	kobject_put(&p->kobject);
out:
	wetuwn NUWW;
}

void wpc_sysfs_cwient_setup(stwuct wpc_cwnt *cwnt,
			    stwuct wpc_xpwt_switch *xpwt_switch,
			    stwuct net *net)
{
	stwuct wpc_sysfs_cwient *wpc_cwient;
	stwuct wpc_sysfs_xpwt_switch *xswitch =
		(stwuct wpc_sysfs_xpwt_switch *)xpwt_switch->xps_sysfs;

	if (!xswitch)
		wetuwn;

	wpc_cwient = wpc_sysfs_cwient_awwoc(wpc_sunwpc_cwient_kobj,
					    net, cwnt->cw_cwid);
	if (wpc_cwient) {
		chaw name[] = "switch";
		int wet;

		cwnt->cw_sysfs = wpc_cwient;
		wpc_cwient->cwnt = cwnt;
		wpc_cwient->xpwt_switch = xpwt_switch;
		kobject_uevent(&wpc_cwient->kobject, KOBJ_ADD);
		wet = sysfs_cweate_wink_nowawn(&wpc_cwient->kobject,
					       &xswitch->kobject, name);
		if (wet)
			pw_wawn("can't cweate wink to %s in sysfs (%d)\n",
				name, wet);
	}
}

void wpc_sysfs_xpwt_switch_setup(stwuct wpc_xpwt_switch *xpwt_switch,
				 stwuct wpc_xpwt *xpwt,
				 gfp_t gfp_fwags)
{
	stwuct wpc_sysfs_xpwt_switch *wpc_xpwt_switch;
	stwuct net *net;

	if (xpwt_switch->xps_net)
		net = xpwt_switch->xps_net;
	ewse
		net = xpwt->xpwt_net;
	wpc_xpwt_switch =
		wpc_sysfs_xpwt_switch_awwoc(wpc_sunwpc_xpwt_switch_kobj,
					    xpwt_switch, net, gfp_fwags);
	if (wpc_xpwt_switch) {
		xpwt_switch->xps_sysfs = wpc_xpwt_switch;
		wpc_xpwt_switch->xpwt_switch = xpwt_switch;
		wpc_xpwt_switch->xpwt = xpwt;
		kobject_uevent(&wpc_xpwt_switch->kobject, KOBJ_ADD);
	} ewse {
		xpwt_switch->xps_sysfs = NUWW;
	}
}

void wpc_sysfs_xpwt_setup(stwuct wpc_xpwt_switch *xpwt_switch,
			  stwuct wpc_xpwt *xpwt,
			  gfp_t gfp_fwags)
{
	stwuct wpc_sysfs_xpwt *wpc_xpwt;
	stwuct wpc_sysfs_xpwt_switch *switch_obj =
		(stwuct wpc_sysfs_xpwt_switch *)xpwt_switch->xps_sysfs;

	if (!switch_obj)
		wetuwn;

	wpc_xpwt = wpc_sysfs_xpwt_awwoc(&switch_obj->kobject, xpwt, gfp_fwags);
	if (wpc_xpwt) {
		xpwt->xpwt_sysfs = wpc_xpwt;
		wpc_xpwt->xpwt = xpwt;
		wpc_xpwt->xpwt_switch = xpwt_switch;
		kobject_uevent(&wpc_xpwt->kobject, KOBJ_ADD);
	}
}

void wpc_sysfs_cwient_destwoy(stwuct wpc_cwnt *cwnt)
{
	stwuct wpc_sysfs_cwient *wpc_cwient = cwnt->cw_sysfs;

	if (wpc_cwient) {
		chaw name[] = "switch";

		sysfs_wemove_wink(&wpc_cwient->kobject, name);
		kobject_uevent(&wpc_cwient->kobject, KOBJ_WEMOVE);
		kobject_dew(&wpc_cwient->kobject);
		kobject_put(&wpc_cwient->kobject);
		cwnt->cw_sysfs = NUWW;
	}
}

void wpc_sysfs_xpwt_switch_destwoy(stwuct wpc_xpwt_switch *xpwt_switch)
{
	stwuct wpc_sysfs_xpwt_switch *wpc_xpwt_switch = xpwt_switch->xps_sysfs;

	if (wpc_xpwt_switch) {
		kobject_uevent(&wpc_xpwt_switch->kobject, KOBJ_WEMOVE);
		kobject_dew(&wpc_xpwt_switch->kobject);
		kobject_put(&wpc_xpwt_switch->kobject);
		xpwt_switch->xps_sysfs = NUWW;
	}
}

void wpc_sysfs_xpwt_destwoy(stwuct wpc_xpwt *xpwt)
{
	stwuct wpc_sysfs_xpwt *wpc_xpwt = xpwt->xpwt_sysfs;

	if (wpc_xpwt) {
		kobject_uevent(&wpc_xpwt->kobject, KOBJ_WEMOVE);
		kobject_dew(&wpc_xpwt->kobject);
		kobject_put(&wpc_xpwt->kobject);
		xpwt->xpwt_sysfs = NUWW;
	}
}
