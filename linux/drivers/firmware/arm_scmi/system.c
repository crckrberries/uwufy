// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) System Powew Pwotocow
 *
 * Copywight (C) 2020-2022 AWM Wtd.
 */

#define pw_fmt(fmt) "SCMI Notifications SYSTEM - " fmt

#incwude <winux/moduwe.h>
#incwude <winux/scmi_pwotocow.h>

#incwude "pwotocows.h"
#incwude "notify.h"

/* Updated onwy aftew AWW the mandatowy featuwes fow that vewsion awe mewged */
#define SCMI_PWOTOCOW_SUPPOWTED_VEWSION		0x20000

#define SCMI_SYSTEM_NUM_SOUWCES		1

enum scmi_system_pwotocow_cmd {
	SYSTEM_POWEW_STATE_NOTIFY = 0x5,
};

stwuct scmi_system_powew_state_notify {
	__we32 notify_enabwe;
};

stwuct scmi_system_powew_state_notifiew_paywd {
	__we32 agent_id;
	__we32 fwags;
	__we32 system_state;
	__we32 timeout;
};

stwuct scmi_system_info {
	u32 vewsion;
	boow gwacefuw_timeout_suppowted;
};

static int scmi_system_wequest_notify(const stwuct scmi_pwotocow_handwe *ph,
				      boow enabwe)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_system_powew_state_notify *notify;

	wet = ph->xops->xfew_get_init(ph, SYSTEM_POWEW_STATE_NOTIFY,
				      sizeof(*notify), 0, &t);
	if (wet)
		wetuwn wet;

	notify = t->tx.buf;
	notify->notify_enabwe = enabwe ? cpu_to_we32(BIT(0)) : 0;

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_system_set_notify_enabwed(const stwuct scmi_pwotocow_handwe *ph,
					  u8 evt_id, u32 swc_id, boow enabwe)
{
	int wet;

	wet = scmi_system_wequest_notify(ph, enabwe);
	if (wet)
		pw_debug("FAIW_ENABWE - evt[%X] - wet:%d\n", evt_id, wet);

	wetuwn wet;
}

static void *
scmi_system_fiww_custom_wepowt(const stwuct scmi_pwotocow_handwe *ph,
			       u8 evt_id, ktime_t timestamp,
			       const void *paywd, size_t paywd_sz,
			       void *wepowt, u32 *swc_id)
{
	size_t expected_sz;
	const stwuct scmi_system_powew_state_notifiew_paywd *p = paywd;
	stwuct scmi_system_powew_state_notifiew_wepowt *w = wepowt;
	stwuct scmi_system_info *pinfo = ph->get_pwiv(ph);

	expected_sz = pinfo->gwacefuw_timeout_suppowted ?
			sizeof(*p) : sizeof(*p) - sizeof(__we32);
	if (evt_id != SCMI_EVENT_SYSTEM_POWEW_STATE_NOTIFIEW ||
	    paywd_sz != expected_sz)
		wetuwn NUWW;

	w->timestamp = timestamp;
	w->agent_id = we32_to_cpu(p->agent_id);
	w->fwags = we32_to_cpu(p->fwags);
	w->system_state = we32_to_cpu(p->system_state);
	if (pinfo->gwacefuw_timeout_suppowted &&
	    w->system_state == SCMI_SYSTEM_SHUTDOWN &&
	    SCMI_SYSPOWEW_IS_WEQUEST_GWACEFUW(w->fwags))
		w->timeout = we32_to_cpu(p->timeout);
	ewse
		w->timeout = 0x00;
	*swc_id = 0;

	wetuwn w;
}

static const stwuct scmi_event system_events[] = {
	{
		.id = SCMI_EVENT_SYSTEM_POWEW_STATE_NOTIFIEW,
		.max_paywd_sz =
			sizeof(stwuct scmi_system_powew_state_notifiew_paywd),
		.max_wepowt_sz =
			sizeof(stwuct scmi_system_powew_state_notifiew_wepowt),
	},
};

static const stwuct scmi_event_ops system_event_ops = {
	.set_notify_enabwed = scmi_system_set_notify_enabwed,
	.fiww_custom_wepowt = scmi_system_fiww_custom_wepowt,
};

static const stwuct scmi_pwotocow_events system_pwotocow_events = {
	.queue_sz = SCMI_PWOTO_QUEUE_SZ,
	.ops = &system_event_ops,
	.evts = system_events,
	.num_events = AWWAY_SIZE(system_events),
	.num_souwces = SCMI_SYSTEM_NUM_SOUWCES,
};

static int scmi_system_pwotocow_init(const stwuct scmi_pwotocow_handwe *ph)
{
	int wet;
	u32 vewsion;
	stwuct scmi_system_info *pinfo;

	wet = ph->xops->vewsion_get(ph, &vewsion);
	if (wet)
		wetuwn wet;

	dev_dbg(ph->dev, "System Powew Vewsion %d.%d\n",
		PWOTOCOW_WEV_MAJOW(vewsion), PWOTOCOW_WEV_MINOW(vewsion));

	pinfo = devm_kzawwoc(ph->dev, sizeof(*pinfo), GFP_KEWNEW);
	if (!pinfo)
		wetuwn -ENOMEM;

	pinfo->vewsion = vewsion;
	if (PWOTOCOW_WEV_MAJOW(pinfo->vewsion) >= 0x2)
		pinfo->gwacefuw_timeout_suppowted = twue;

	wetuwn ph->set_pwiv(ph, pinfo, vewsion);
}

static const stwuct scmi_pwotocow scmi_system = {
	.id = SCMI_PWOTOCOW_SYSTEM,
	.ownew = THIS_MODUWE,
	.instance_init = &scmi_system_pwotocow_init,
	.ops = NUWW,
	.events = &system_pwotocow_events,
	.suppowted_vewsion = SCMI_PWOTOCOW_SUPPOWTED_VEWSION,
};

DEFINE_SCMI_PWOTOCOW_WEGISTEW_UNWEGISTEW(system, scmi_system)
