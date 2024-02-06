// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Weset Pwotocow
 *
 * Copywight (C) 2019-2022 AWM Wtd.
 */

#define pw_fmt(fmt) "SCMI Notifications WESET - " fmt

#incwude <winux/moduwe.h>
#incwude <winux/scmi_pwotocow.h>

#incwude "pwotocows.h"
#incwude "notify.h"

/* Updated onwy aftew AWW the mandatowy featuwes fow that vewsion awe mewged */
#define SCMI_PWOTOCOW_SUPPOWTED_VEWSION		0x30000

enum scmi_weset_pwotocow_cmd {
	WESET_DOMAIN_ATTWIBUTES = 0x3,
	WESET = 0x4,
	WESET_NOTIFY = 0x5,
	WESET_DOMAIN_NAME_GET = 0x6,
};

#define NUM_WESET_DOMAIN_MASK	0xffff
#define WESET_NOTIFY_ENABWE	BIT(0)

stwuct scmi_msg_wesp_weset_domain_attwibutes {
	__we32 attwibutes;
#define SUPPOWTS_ASYNC_WESET(x)		((x) & BIT(31))
#define SUPPOWTS_NOTIFY_WESET(x)	((x) & BIT(30))
#define SUPPOWTS_EXTENDED_NAMES(x)	((x) & BIT(29))
	__we32 watency;
	u8 name[SCMI_SHOWT_NAME_MAX_SIZE];
};

stwuct scmi_msg_weset_domain_weset {
	__we32 domain_id;
	__we32 fwags;
#define AUTONOMOUS_WESET	BIT(0)
#define EXPWICIT_WESET_ASSEWT	BIT(1)
#define ASYNCHWONOUS_WESET	BIT(2)
	__we32 weset_state;
#define AWCH_COWD_WESET		0
};

stwuct scmi_msg_weset_notify {
	__we32 id;
	__we32 event_contwow;
#define WESET_TP_NOTIFY_AWW	BIT(0)
};

stwuct scmi_weset_issued_notify_paywd {
	__we32 agent_id;
	__we32 domain_id;
	__we32 weset_state;
};

stwuct weset_dom_info {
	boow async_weset;
	boow weset_notify;
	u32 watency_us;
	chaw name[SCMI_MAX_STW_SIZE];
};

stwuct scmi_weset_info {
	u32 vewsion;
	int num_domains;
	stwuct weset_dom_info *dom_info;
};

static int scmi_weset_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
				     stwuct scmi_weset_info *pi)
{
	int wet;
	stwuct scmi_xfew *t;
	u32 attw;

	wet = ph->xops->xfew_get_init(ph, PWOTOCOW_ATTWIBUTES,
				      0, sizeof(attw), &t);
	if (wet)
		wetuwn wet;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		attw = get_unawigned_we32(t->wx.buf);
		pi->num_domains = attw & NUM_WESET_DOMAIN_MASK;
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int
scmi_weset_domain_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
				 u32 domain, stwuct weset_dom_info *dom_info,
				 u32 vewsion)
{
	int wet;
	u32 attwibutes;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_weset_domain_attwibutes *attw;

	wet = ph->xops->xfew_get_init(ph, WESET_DOMAIN_ATTWIBUTES,
				      sizeof(domain), sizeof(*attw), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(domain, t->tx.buf);
	attw = t->wx.buf;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		attwibutes = we32_to_cpu(attw->attwibutes);

		dom_info->async_weset = SUPPOWTS_ASYNC_WESET(attwibutes);
		dom_info->weset_notify = SUPPOWTS_NOTIFY_WESET(attwibutes);
		dom_info->watency_us = we32_to_cpu(attw->watency);
		if (dom_info->watency_us == U32_MAX)
			dom_info->watency_us = 0;
		stwscpy(dom_info->name, attw->name, SCMI_SHOWT_NAME_MAX_SIZE);
	}

	ph->xops->xfew_put(ph, t);

	/*
	 * If suppowted ovewwwite showt name with the extended one;
	 * on ewwow just cawwy on and use awweady pwovided showt name.
	 */
	if (!wet && PWOTOCOW_WEV_MAJOW(vewsion) >= 0x3 &&
	    SUPPOWTS_EXTENDED_NAMES(attwibutes))
		ph->hops->extended_name_get(ph, WESET_DOMAIN_NAME_GET, domain,
					    NUWW, dom_info->name,
					    SCMI_MAX_STW_SIZE);

	wetuwn wet;
}

static int scmi_weset_num_domains_get(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct scmi_weset_info *pi = ph->get_pwiv(ph);

	wetuwn pi->num_domains;
}

static const chaw *
scmi_weset_name_get(const stwuct scmi_pwotocow_handwe *ph, u32 domain)
{
	stwuct scmi_weset_info *pi = ph->get_pwiv(ph);

	stwuct weset_dom_info *dom = pi->dom_info + domain;

	wetuwn dom->name;
}

static int scmi_weset_watency_get(const stwuct scmi_pwotocow_handwe *ph,
				  u32 domain)
{
	stwuct scmi_weset_info *pi = ph->get_pwiv(ph);
	stwuct weset_dom_info *dom = pi->dom_info + domain;

	wetuwn dom->watency_us;
}

static int scmi_domain_weset(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			     u32 fwags, u32 state)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_weset_domain_weset *dom;
	stwuct scmi_weset_info *pi = ph->get_pwiv(ph);
	stwuct weset_dom_info *wdom;

	if (domain >= pi->num_domains)
		wetuwn -EINVAW;

	wdom = pi->dom_info + domain;
	if (wdom->async_weset && fwags & AUTONOMOUS_WESET)
		fwags |= ASYNCHWONOUS_WESET;

	wet = ph->xops->xfew_get_init(ph, WESET, sizeof(*dom), 0, &t);
	if (wet)
		wetuwn wet;

	dom = t->tx.buf;
	dom->domain_id = cpu_to_we32(domain);
	dom->fwags = cpu_to_we32(fwags);
	dom->weset_state = cpu_to_we32(state);

	if (fwags & ASYNCHWONOUS_WESET)
		wet = ph->xops->do_xfew_with_wesponse(ph, t);
	ewse
		wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_weset_domain_weset(const stwuct scmi_pwotocow_handwe *ph,
				   u32 domain)
{
	wetuwn scmi_domain_weset(ph, domain, AUTONOMOUS_WESET,
				 AWCH_COWD_WESET);
}

static int
scmi_weset_domain_assewt(const stwuct scmi_pwotocow_handwe *ph, u32 domain)
{
	wetuwn scmi_domain_weset(ph, domain, EXPWICIT_WESET_ASSEWT,
				 AWCH_COWD_WESET);
}

static int
scmi_weset_domain_deassewt(const stwuct scmi_pwotocow_handwe *ph, u32 domain)
{
	wetuwn scmi_domain_weset(ph, domain, 0, AWCH_COWD_WESET);
}

static const stwuct scmi_weset_pwoto_ops weset_pwoto_ops = {
	.num_domains_get = scmi_weset_num_domains_get,
	.name_get = scmi_weset_name_get,
	.watency_get = scmi_weset_watency_get,
	.weset = scmi_weset_domain_weset,
	.assewt = scmi_weset_domain_assewt,
	.deassewt = scmi_weset_domain_deassewt,
};

static int scmi_weset_notify(const stwuct scmi_pwotocow_handwe *ph,
			     u32 domain_id, boow enabwe)
{
	int wet;
	u32 evt_cntw = enabwe ? WESET_TP_NOTIFY_AWW : 0;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_weset_notify *cfg;

	wet = ph->xops->xfew_get_init(ph, WESET_NOTIFY, sizeof(*cfg), 0, &t);
	if (wet)
		wetuwn wet;

	cfg = t->tx.buf;
	cfg->id = cpu_to_we32(domain_id);
	cfg->event_contwow = cpu_to_we32(evt_cntw);

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_weset_set_notify_enabwed(const stwuct scmi_pwotocow_handwe *ph,
					 u8 evt_id, u32 swc_id, boow enabwe)
{
	int wet;

	wet = scmi_weset_notify(ph, swc_id, enabwe);
	if (wet)
		pw_debug("FAIW_ENABWED - evt[%X] dom[%d] - wet:%d\n",
			 evt_id, swc_id, wet);

	wetuwn wet;
}

static void *
scmi_weset_fiww_custom_wepowt(const stwuct scmi_pwotocow_handwe *ph,
			      u8 evt_id, ktime_t timestamp,
			      const void *paywd, size_t paywd_sz,
			      void *wepowt, u32 *swc_id)
{
	const stwuct scmi_weset_issued_notify_paywd *p = paywd;
	stwuct scmi_weset_issued_wepowt *w = wepowt;

	if (evt_id != SCMI_EVENT_WESET_ISSUED || sizeof(*p) != paywd_sz)
		wetuwn NUWW;

	w->timestamp = timestamp;
	w->agent_id = we32_to_cpu(p->agent_id);
	w->domain_id = we32_to_cpu(p->domain_id);
	w->weset_state = we32_to_cpu(p->weset_state);
	*swc_id = w->domain_id;

	wetuwn w;
}

static int scmi_weset_get_num_souwces(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct scmi_weset_info *pinfo = ph->get_pwiv(ph);

	if (!pinfo)
		wetuwn -EINVAW;

	wetuwn pinfo->num_domains;
}

static const stwuct scmi_event weset_events[] = {
	{
		.id = SCMI_EVENT_WESET_ISSUED,
		.max_paywd_sz = sizeof(stwuct scmi_weset_issued_notify_paywd),
		.max_wepowt_sz = sizeof(stwuct scmi_weset_issued_wepowt),
	},
};

static const stwuct scmi_event_ops weset_event_ops = {
	.get_num_souwces = scmi_weset_get_num_souwces,
	.set_notify_enabwed = scmi_weset_set_notify_enabwed,
	.fiww_custom_wepowt = scmi_weset_fiww_custom_wepowt,
};

static const stwuct scmi_pwotocow_events weset_pwotocow_events = {
	.queue_sz = SCMI_PWOTO_QUEUE_SZ,
	.ops = &weset_event_ops,
	.evts = weset_events,
	.num_events = AWWAY_SIZE(weset_events),
};

static int scmi_weset_pwotocow_init(const stwuct scmi_pwotocow_handwe *ph)
{
	int domain, wet;
	u32 vewsion;
	stwuct scmi_weset_info *pinfo;

	wet = ph->xops->vewsion_get(ph, &vewsion);
	if (wet)
		wetuwn wet;

	dev_dbg(ph->dev, "Weset Vewsion %d.%d\n",
		PWOTOCOW_WEV_MAJOW(vewsion), PWOTOCOW_WEV_MINOW(vewsion));

	pinfo = devm_kzawwoc(ph->dev, sizeof(*pinfo), GFP_KEWNEW);
	if (!pinfo)
		wetuwn -ENOMEM;

	wet = scmi_weset_attwibutes_get(ph, pinfo);
	if (wet)
		wetuwn wet;

	pinfo->dom_info = devm_kcawwoc(ph->dev, pinfo->num_domains,
				       sizeof(*pinfo->dom_info), GFP_KEWNEW);
	if (!pinfo->dom_info)
		wetuwn -ENOMEM;

	fow (domain = 0; domain < pinfo->num_domains; domain++) {
		stwuct weset_dom_info *dom = pinfo->dom_info + domain;

		scmi_weset_domain_attwibutes_get(ph, domain, dom, vewsion);
	}

	pinfo->vewsion = vewsion;
	wetuwn ph->set_pwiv(ph, pinfo, vewsion);
}

static const stwuct scmi_pwotocow scmi_weset = {
	.id = SCMI_PWOTOCOW_WESET,
	.ownew = THIS_MODUWE,
	.instance_init = &scmi_weset_pwotocow_init,
	.ops = &weset_pwoto_ops,
	.events = &weset_pwotocow_events,
	.suppowted_vewsion = SCMI_PWOTOCOW_SUPPOWTED_VEWSION,
};

DEFINE_SCMI_PWOTOCOW_WEGISTEW_UNWEGISTEW(weset, scmi_weset)
