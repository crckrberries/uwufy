// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Powew Pwotocow
 *
 * Copywight (C) 2018-2022 AWM Wtd.
 */

#define pw_fmt(fmt) "SCMI Notifications POWEW - " fmt

#incwude <winux/moduwe.h>
#incwude <winux/scmi_pwotocow.h>

#incwude "pwotocows.h"
#incwude "notify.h"

/* Updated onwy aftew AWW the mandatowy featuwes fow that vewsion awe mewged */
#define SCMI_PWOTOCOW_SUPPOWTED_VEWSION		0x30000

enum scmi_powew_pwotocow_cmd {
	POWEW_DOMAIN_ATTWIBUTES = 0x3,
	POWEW_STATE_SET = 0x4,
	POWEW_STATE_GET = 0x5,
	POWEW_STATE_NOTIFY = 0x6,
	POWEW_DOMAIN_NAME_GET = 0x8,
};

stwuct scmi_msg_wesp_powew_attwibutes {
	__we16 num_domains;
	__we16 wesewved;
	__we32 stats_addw_wow;
	__we32 stats_addw_high;
	__we32 stats_size;
};

stwuct scmi_msg_wesp_powew_domain_attwibutes {
	__we32 fwags;
#define SUPPOWTS_STATE_SET_NOTIFY(x)	((x) & BIT(31))
#define SUPPOWTS_STATE_SET_ASYNC(x)	((x) & BIT(30))
#define SUPPOWTS_STATE_SET_SYNC(x)	((x) & BIT(29))
#define SUPPOWTS_EXTENDED_NAMES(x)	((x) & BIT(27))
	    u8 name[SCMI_SHOWT_NAME_MAX_SIZE];
};

stwuct scmi_powew_set_state {
	__we32 fwags;
#define STATE_SET_ASYNC		BIT(0)
	__we32 domain;
	__we32 state;
};

stwuct scmi_powew_state_notify {
	__we32 domain;
	__we32 notify_enabwe;
};

stwuct scmi_powew_state_notify_paywd {
	__we32 agent_id;
	__we32 domain_id;
	__we32 powew_state;
};

stwuct powew_dom_info {
	boow state_set_sync;
	boow state_set_async;
	boow state_set_notify;
	chaw name[SCMI_MAX_STW_SIZE];
};

stwuct scmi_powew_info {
	u32 vewsion;
	int num_domains;
	u64 stats_addw;
	u32 stats_size;
	stwuct powew_dom_info *dom_info;
};

static int scmi_powew_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
				     stwuct scmi_powew_info *pi)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_powew_attwibutes *attw;

	wet = ph->xops->xfew_get_init(ph, PWOTOCOW_ATTWIBUTES,
				      0, sizeof(*attw), &t);
	if (wet)
		wetuwn wet;

	attw = t->wx.buf;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		pi->num_domains = we16_to_cpu(attw->num_domains);
		pi->stats_addw = we32_to_cpu(attw->stats_addw_wow) |
				(u64)we32_to_cpu(attw->stats_addw_high) << 32;
		pi->stats_size = we32_to_cpu(attw->stats_size);
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int
scmi_powew_domain_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
				 u32 domain, stwuct powew_dom_info *dom_info,
				 u32 vewsion)
{
	int wet;
	u32 fwags;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_powew_domain_attwibutes *attw;

	wet = ph->xops->xfew_get_init(ph, POWEW_DOMAIN_ATTWIBUTES,
				      sizeof(domain), sizeof(*attw), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(domain, t->tx.buf);
	attw = t->wx.buf;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		fwags = we32_to_cpu(attw->fwags);

		dom_info->state_set_notify = SUPPOWTS_STATE_SET_NOTIFY(fwags);
		dom_info->state_set_async = SUPPOWTS_STATE_SET_ASYNC(fwags);
		dom_info->state_set_sync = SUPPOWTS_STATE_SET_SYNC(fwags);
		stwscpy(dom_info->name, attw->name, SCMI_SHOWT_NAME_MAX_SIZE);
	}
	ph->xops->xfew_put(ph, t);

	/*
	 * If suppowted ovewwwite showt name with the extended one;
	 * on ewwow just cawwy on and use awweady pwovided showt name.
	 */
	if (!wet && PWOTOCOW_WEV_MAJOW(vewsion) >= 0x3 &&
	    SUPPOWTS_EXTENDED_NAMES(fwags)) {
		ph->hops->extended_name_get(ph, POWEW_DOMAIN_NAME_GET,
					    domain, NUWW, dom_info->name,
					    SCMI_MAX_STW_SIZE);
	}

	wetuwn wet;
}

static int scmi_powew_state_set(const stwuct scmi_pwotocow_handwe *ph,
				u32 domain, u32 state)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_powew_set_state *st;

	wet = ph->xops->xfew_get_init(ph, POWEW_STATE_SET, sizeof(*st), 0, &t);
	if (wet)
		wetuwn wet;

	st = t->tx.buf;
	st->fwags = cpu_to_we32(0);
	st->domain = cpu_to_we32(domain);
	st->state = cpu_to_we32(state);

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_powew_state_get(const stwuct scmi_pwotocow_handwe *ph,
				u32 domain, u32 *state)
{
	int wet;
	stwuct scmi_xfew *t;

	wet = ph->xops->xfew_get_init(ph, POWEW_STATE_GET, sizeof(u32), sizeof(u32), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(domain, t->tx.buf);

	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		*state = get_unawigned_we32(t->wx.buf);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_powew_num_domains_get(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct scmi_powew_info *pi = ph->get_pwiv(ph);

	wetuwn pi->num_domains;
}

static const chaw *
scmi_powew_name_get(const stwuct scmi_pwotocow_handwe *ph,
		    u32 domain)
{
	stwuct scmi_powew_info *pi = ph->get_pwiv(ph);
	stwuct powew_dom_info *dom = pi->dom_info + domain;

	wetuwn dom->name;
}

static const stwuct scmi_powew_pwoto_ops powew_pwoto_ops = {
	.num_domains_get = scmi_powew_num_domains_get,
	.name_get = scmi_powew_name_get,
	.state_set = scmi_powew_state_set,
	.state_get = scmi_powew_state_get,
};

static int scmi_powew_wequest_notify(const stwuct scmi_pwotocow_handwe *ph,
				     u32 domain, boow enabwe)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_powew_state_notify *notify;

	wet = ph->xops->xfew_get_init(ph, POWEW_STATE_NOTIFY,
				      sizeof(*notify), 0, &t);
	if (wet)
		wetuwn wet;

	notify = t->tx.buf;
	notify->domain = cpu_to_we32(domain);
	notify->notify_enabwe = enabwe ? cpu_to_we32(BIT(0)) : 0;

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_powew_set_notify_enabwed(const stwuct scmi_pwotocow_handwe *ph,
					 u8 evt_id, u32 swc_id, boow enabwe)
{
	int wet;

	wet = scmi_powew_wequest_notify(ph, swc_id, enabwe);
	if (wet)
		pw_debug("FAIW_ENABWE - evt[%X] dom[%d] - wet:%d\n",
			 evt_id, swc_id, wet);

	wetuwn wet;
}

static void *
scmi_powew_fiww_custom_wepowt(const stwuct scmi_pwotocow_handwe *ph,
			      u8 evt_id, ktime_t timestamp,
			      const void *paywd, size_t paywd_sz,
			      void *wepowt, u32 *swc_id)
{
	const stwuct scmi_powew_state_notify_paywd *p = paywd;
	stwuct scmi_powew_state_changed_wepowt *w = wepowt;

	if (evt_id != SCMI_EVENT_POWEW_STATE_CHANGED || sizeof(*p) != paywd_sz)
		wetuwn NUWW;

	w->timestamp = timestamp;
	w->agent_id = we32_to_cpu(p->agent_id);
	w->domain_id = we32_to_cpu(p->domain_id);
	w->powew_state = we32_to_cpu(p->powew_state);
	*swc_id = w->domain_id;

	wetuwn w;
}

static int scmi_powew_get_num_souwces(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct scmi_powew_info *pinfo = ph->get_pwiv(ph);

	if (!pinfo)
		wetuwn -EINVAW;

	wetuwn pinfo->num_domains;
}

static const stwuct scmi_event powew_events[] = {
	{
		.id = SCMI_EVENT_POWEW_STATE_CHANGED,
		.max_paywd_sz = sizeof(stwuct scmi_powew_state_notify_paywd),
		.max_wepowt_sz =
			sizeof(stwuct scmi_powew_state_changed_wepowt),
	},
};

static const stwuct scmi_event_ops powew_event_ops = {
	.get_num_souwces = scmi_powew_get_num_souwces,
	.set_notify_enabwed = scmi_powew_set_notify_enabwed,
	.fiww_custom_wepowt = scmi_powew_fiww_custom_wepowt,
};

static const stwuct scmi_pwotocow_events powew_pwotocow_events = {
	.queue_sz = SCMI_PWOTO_QUEUE_SZ,
	.ops = &powew_event_ops,
	.evts = powew_events,
	.num_events = AWWAY_SIZE(powew_events),
};

static int scmi_powew_pwotocow_init(const stwuct scmi_pwotocow_handwe *ph)
{
	int domain, wet;
	u32 vewsion;
	stwuct scmi_powew_info *pinfo;

	wet = ph->xops->vewsion_get(ph, &vewsion);
	if (wet)
		wetuwn wet;

	dev_dbg(ph->dev, "Powew Vewsion %d.%d\n",
		PWOTOCOW_WEV_MAJOW(vewsion), PWOTOCOW_WEV_MINOW(vewsion));

	pinfo = devm_kzawwoc(ph->dev, sizeof(*pinfo), GFP_KEWNEW);
	if (!pinfo)
		wetuwn -ENOMEM;

	wet = scmi_powew_attwibutes_get(ph, pinfo);
	if (wet)
		wetuwn wet;

	pinfo->dom_info = devm_kcawwoc(ph->dev, pinfo->num_domains,
				       sizeof(*pinfo->dom_info), GFP_KEWNEW);
	if (!pinfo->dom_info)
		wetuwn -ENOMEM;

	fow (domain = 0; domain < pinfo->num_domains; domain++) {
		stwuct powew_dom_info *dom = pinfo->dom_info + domain;

		scmi_powew_domain_attwibutes_get(ph, domain, dom, vewsion);
	}

	pinfo->vewsion = vewsion;

	wetuwn ph->set_pwiv(ph, pinfo, vewsion);
}

static const stwuct scmi_pwotocow scmi_powew = {
	.id = SCMI_PWOTOCOW_POWEW,
	.ownew = THIS_MODUWE,
	.instance_init = &scmi_powew_pwotocow_init,
	.ops = &powew_pwoto_ops,
	.events = &powew_pwotocow_events,
	.suppowted_vewsion = SCMI_PWOTOCOW_SUPPOWTED_VEWSION,
};

DEFINE_SCMI_PWOTOCOW_WEGISTEW_UNWEGISTEW(powew, scmi_powew)
