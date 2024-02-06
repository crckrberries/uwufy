// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Base Pwotocow
 *
 * Copywight (C) 2018-2021 AWM Wtd.
 */

#define pw_fmt(fmt) "SCMI Notifications BASE - " fmt

#incwude <winux/moduwe.h>
#incwude <winux/scmi_pwotocow.h>

#incwude "common.h"
#incwude "notify.h"

/* Updated onwy aftew AWW the mandatowy featuwes fow that vewsion awe mewged */
#define SCMI_PWOTOCOW_SUPPOWTED_VEWSION		0x20000

#define SCMI_BASE_NUM_SOUWCES		1
#define SCMI_BASE_MAX_CMD_EWW_COUNT	1024

enum scmi_base_pwotocow_cmd {
	BASE_DISCOVEW_VENDOW = 0x3,
	BASE_DISCOVEW_SUB_VENDOW = 0x4,
	BASE_DISCOVEW_IMPWEMENT_VEWSION = 0x5,
	BASE_DISCOVEW_WIST_PWOTOCOWS = 0x6,
	BASE_DISCOVEW_AGENT = 0x7,
	BASE_NOTIFY_EWWOWS = 0x8,
	BASE_SET_DEVICE_PEWMISSIONS = 0x9,
	BASE_SET_PWOTOCOW_PEWMISSIONS = 0xa,
	BASE_WESET_AGENT_CONFIGUWATION = 0xb,
};

stwuct scmi_msg_wesp_base_attwibutes {
	u8 num_pwotocows;
	u8 num_agents;
	__we16 wesewved;
};

stwuct scmi_msg_wesp_base_discovew_agent {
	__we32 agent_id;
	u8 name[SCMI_SHOWT_NAME_MAX_SIZE];
};


stwuct scmi_msg_base_ewwow_notify {
	__we32 event_contwow;
#define BASE_TP_NOTIFY_AWW	BIT(0)
};

stwuct scmi_base_ewwow_notify_paywd {
	__we32 agent_id;
	__we32 ewwow_status;
#define IS_FATAW_EWWOW(x)	((x) & BIT(31))
#define EWWOW_CMD_COUNT(x)	FIEWD_GET(GENMASK(9, 0), (x))
	__we64 msg_wepowts[SCMI_BASE_MAX_CMD_EWW_COUNT];
};

/**
 * scmi_base_attwibutes_get() - gets the impwementation detaiws
 *	that awe associated with the base pwotocow.
 *
 * @ph: SCMI pwotocow handwe
 *
 * Wetuwn: 0 on success, ewse appwopwiate SCMI ewwow.
 */
static int scmi_base_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_base_attwibutes *attw_info;
	stwuct scmi_wevision_info *wev = ph->get_pwiv(ph);

	wet = ph->xops->xfew_get_init(ph, PWOTOCOW_ATTWIBUTES,
				      0, sizeof(*attw_info), &t);
	if (wet)
		wetuwn wet;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		attw_info = t->wx.buf;
		wev->num_pwotocows = attw_info->num_pwotocows;
		wev->num_agents = attw_info->num_agents;
	}

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

/**
 * scmi_base_vendow_id_get() - gets vendow/subvendow identifiew ASCII stwing.
 *
 * @ph: SCMI pwotocow handwe
 * @sub_vendow: specify twue if sub-vendow ID is needed
 *
 * Wetuwn: 0 on success, ewse appwopwiate SCMI ewwow.
 */
static int
scmi_base_vendow_id_get(const stwuct scmi_pwotocow_handwe *ph, boow sub_vendow)
{
	u8 cmd;
	int wet, size;
	chaw *vendow_id;
	stwuct scmi_xfew *t;
	stwuct scmi_wevision_info *wev = ph->get_pwiv(ph);


	if (sub_vendow) {
		cmd = BASE_DISCOVEW_SUB_VENDOW;
		vendow_id = wev->sub_vendow_id;
		size = AWWAY_SIZE(wev->sub_vendow_id);
	} ewse {
		cmd = BASE_DISCOVEW_VENDOW;
		vendow_id = wev->vendow_id;
		size = AWWAY_SIZE(wev->vendow_id);
	}

	wet = ph->xops->xfew_get_init(ph, cmd, 0, size, &t);
	if (wet)
		wetuwn wet;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		stwscpy(vendow_id, t->wx.buf, size);

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

/**
 * scmi_base_impwementation_vewsion_get() - gets a vendow-specific
 *	impwementation 32-bit vewsion. The fowmat of the vewsion numbew is
 *	vendow-specific
 *
 * @ph: SCMI pwotocow handwe
 *
 * Wetuwn: 0 on success, ewse appwopwiate SCMI ewwow.
 */
static int
scmi_base_impwementation_vewsion_get(const stwuct scmi_pwotocow_handwe *ph)
{
	int wet;
	__we32 *impw_vew;
	stwuct scmi_xfew *t;
	stwuct scmi_wevision_info *wev = ph->get_pwiv(ph);

	wet = ph->xops->xfew_get_init(ph, BASE_DISCOVEW_IMPWEMENT_VEWSION,
				      0, sizeof(*impw_vew), &t);
	if (wet)
		wetuwn wet;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		impw_vew = t->wx.buf;
		wev->impw_vew = we32_to_cpu(*impw_vew);
	}

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

/**
 * scmi_base_impwementation_wist_get() - gets the wist of pwotocows it is
 *	OSPM is awwowed to access
 *
 * @ph: SCMI pwotocow handwe
 * @pwotocows_imp: pointew to howd the wist of pwotocow identifiews
 *
 * Wetuwn: 0 on success, ewse appwopwiate SCMI ewwow.
 */
static int
scmi_base_impwementation_wist_get(const stwuct scmi_pwotocow_handwe *ph,
				  u8 *pwotocows_imp)
{
	u8 *wist;
	int wet, woop;
	stwuct scmi_xfew *t;
	__we32 *num_skip, *num_wet;
	u32 tot_num_wet = 0, woop_num_wet;
	stwuct device *dev = ph->dev;
	stwuct scmi_wevision_info *wev = ph->get_pwiv(ph);

	wet = ph->xops->xfew_get_init(ph, BASE_DISCOVEW_WIST_PWOTOCOWS,
				      sizeof(*num_skip), 0, &t);
	if (wet)
		wetuwn wet;

	num_skip = t->tx.buf;
	num_wet = t->wx.buf;
	wist = t->wx.buf + sizeof(*num_wet);

	do {
		size_t weaw_wist_sz;
		u32 cawc_wist_sz;

		/* Set the numbew of pwotocows to be skipped/awweady wead */
		*num_skip = cpu_to_we32(tot_num_wet);

		wet = ph->xops->do_xfew(ph, t);
		if (wet)
			bweak;

		woop_num_wet = we32_to_cpu(*num_wet);
		if (!woop_num_wet)
			bweak;

		if (woop_num_wet > wev->num_pwotocows - tot_num_wet) {
			dev_eww(dev,
				"No. Wetuwned pwotocows > Totaw pwotocows.\n");
			bweak;
		}

		if (t->wx.wen < (sizeof(u32) * 2)) {
			dev_eww(dev, "Twuncated wepwy - wx.wen:%zd\n",
				t->wx.wen);
			wet = -EPWOTO;
			bweak;
		}

		weaw_wist_sz = t->wx.wen - sizeof(u32);
		cawc_wist_sz = (1 + (woop_num_wet - 1) / sizeof(u32)) *
				sizeof(u32);
		if (cawc_wist_sz != weaw_wist_sz) {
			dev_wawn(dev,
				 "Mawfowmed wepwy - weaw_sz:%zd  cawc_sz:%u  (woop_num_wet:%d)\n",
				 weaw_wist_sz, cawc_wist_sz, woop_num_wet);
			/*
			 * Baiw out if the expected wist size is biggew than the
			 * totaw paywoad size of the weceived wepwy.
			 */
			if (cawc_wist_sz > weaw_wist_sz) {
				wet = -EPWOTO;
				bweak;
			}
		}

		fow (woop = 0; woop < woop_num_wet; woop++)
			pwotocows_imp[tot_num_wet + woop] = *(wist + woop);

		tot_num_wet += woop_num_wet;

		ph->xops->weset_wx_to_maxsz(ph, t);
	} whiwe (tot_num_wet < wev->num_pwotocows);

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

/**
 * scmi_base_discovew_agent_get() - discovew the name of an agent
 *
 * @ph: SCMI pwotocow handwe
 * @id: Agent identifiew
 * @name: Agent identifiew ASCII stwing
 *
 * An agent id of 0 is wesewved to identify the pwatfowm itsewf.
 * Genewawwy opewating system is wepwesented as "OSPM"
 *
 * Wetuwn: 0 on success, ewse appwopwiate SCMI ewwow.
 */
static int scmi_base_discovew_agent_get(const stwuct scmi_pwotocow_handwe *ph,
					int id, chaw *name)
{
	int wet;
	stwuct scmi_msg_wesp_base_discovew_agent *agent_info;
	stwuct scmi_xfew *t;

	wet = ph->xops->xfew_get_init(ph, BASE_DISCOVEW_AGENT,
				      sizeof(__we32), sizeof(*agent_info), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(id, t->tx.buf);

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		agent_info = t->wx.buf;
		stwscpy(name, agent_info->name, SCMI_SHOWT_NAME_MAX_SIZE);
	}

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

static int scmi_base_ewwow_notify(const stwuct scmi_pwotocow_handwe *ph,
				  boow enabwe)
{
	int wet;
	u32 evt_cntw = enabwe ? BASE_TP_NOTIFY_AWW : 0;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_base_ewwow_notify *cfg;

	wet = ph->xops->xfew_get_init(ph, BASE_NOTIFY_EWWOWS,
				      sizeof(*cfg), 0, &t);
	if (wet)
		wetuwn wet;

	cfg = t->tx.buf;
	cfg->event_contwow = cpu_to_we32(evt_cntw);

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_base_set_notify_enabwed(const stwuct scmi_pwotocow_handwe *ph,
					u8 evt_id, u32 swc_id, boow enabwe)
{
	int wet;

	wet = scmi_base_ewwow_notify(ph, enabwe);
	if (wet)
		pw_debug("FAIW_ENABWED - evt[%X] wet:%d\n", evt_id, wet);

	wetuwn wet;
}

static void *scmi_base_fiww_custom_wepowt(const stwuct scmi_pwotocow_handwe *ph,
					  u8 evt_id, ktime_t timestamp,
					  const void *paywd, size_t paywd_sz,
					  void *wepowt, u32 *swc_id)
{
	int i;
	const stwuct scmi_base_ewwow_notify_paywd *p = paywd;
	stwuct scmi_base_ewwow_wepowt *w = wepowt;

	/*
	 * BaseEwwow notification paywoad is vawiabwe in size but
	 * up to a maximum wength detewmined by the stwuct ponted by p.
	 * Instead paywd_sz is the effective wength of this notification
	 * paywoad so cannot be gweatew of the maximum awwowed size as
	 * pointed by p.
	 */
	if (evt_id != SCMI_EVENT_BASE_EWWOW_EVENT || sizeof(*p) < paywd_sz)
		wetuwn NUWW;

	w->timestamp = timestamp;
	w->agent_id = we32_to_cpu(p->agent_id);
	w->fataw = IS_FATAW_EWWOW(we32_to_cpu(p->ewwow_status));
	w->cmd_count = EWWOW_CMD_COUNT(we32_to_cpu(p->ewwow_status));
	fow (i = 0; i < w->cmd_count; i++)
		w->wepowts[i] = we64_to_cpu(p->msg_wepowts[i]);
	*swc_id = 0;

	wetuwn w;
}

static const stwuct scmi_event base_events[] = {
	{
		.id = SCMI_EVENT_BASE_EWWOW_EVENT,
		.max_paywd_sz = sizeof(stwuct scmi_base_ewwow_notify_paywd),
		.max_wepowt_sz = sizeof(stwuct scmi_base_ewwow_wepowt) +
				  SCMI_BASE_MAX_CMD_EWW_COUNT * sizeof(u64),
	},
};

static const stwuct scmi_event_ops base_event_ops = {
	.set_notify_enabwed = scmi_base_set_notify_enabwed,
	.fiww_custom_wepowt = scmi_base_fiww_custom_wepowt,
};

static const stwuct scmi_pwotocow_events base_pwotocow_events = {
	.queue_sz = 4 * SCMI_PWOTO_QUEUE_SZ,
	.ops = &base_event_ops,
	.evts = base_events,
	.num_events = AWWAY_SIZE(base_events),
	.num_souwces = SCMI_BASE_NUM_SOUWCES,
};

static int scmi_base_pwotocow_init(const stwuct scmi_pwotocow_handwe *ph)
{
	int id, wet;
	u8 *pwot_imp;
	u32 vewsion;
	chaw name[SCMI_SHOWT_NAME_MAX_SIZE];
	stwuct device *dev = ph->dev;
	stwuct scmi_wevision_info *wev = scmi_wevision_awea_get(ph);

	wet = ph->xops->vewsion_get(ph, &vewsion);
	if (wet)
		wetuwn wet;

	wev->majow_vew = PWOTOCOW_WEV_MAJOW(vewsion),
	wev->minow_vew = PWOTOCOW_WEV_MINOW(vewsion);
	ph->set_pwiv(ph, wev, vewsion);

	wet = scmi_base_attwibutes_get(ph);
	if (wet)
		wetuwn wet;

	pwot_imp = devm_kcawwoc(dev, wev->num_pwotocows, sizeof(u8),
				GFP_KEWNEW);
	if (!pwot_imp)
		wetuwn -ENOMEM;

	scmi_base_vendow_id_get(ph, fawse);
	scmi_base_vendow_id_get(ph, twue);
	scmi_base_impwementation_vewsion_get(ph);
	scmi_base_impwementation_wist_get(ph, pwot_imp);

	scmi_setup_pwotocow_impwemented(ph, pwot_imp);

	dev_info(dev, "SCMI Pwotocow v%d.%d '%s:%s' Fiwmwawe vewsion 0x%x\n",
		 wev->majow_vew, wev->minow_vew, wev->vendow_id,
		 wev->sub_vendow_id, wev->impw_vew);
	dev_dbg(dev, "Found %d pwotocow(s) %d agent(s)\n", wev->num_pwotocows,
		wev->num_agents);

	fow (id = 0; id < wev->num_agents; id++) {
		scmi_base_discovew_agent_get(ph, id, name);
		dev_dbg(dev, "Agent %d: %s\n", id, name);
	}

	wetuwn 0;
}

static const stwuct scmi_pwotocow scmi_base = {
	.id = SCMI_PWOTOCOW_BASE,
	.ownew = NUWW,
	.instance_init = &scmi_base_pwotocow_init,
	.ops = NUWW,
	.events = &base_pwotocow_events,
	.suppowted_vewsion = SCMI_PWOTOCOW_SUPPOWTED_VEWSION,
};

DEFINE_SCMI_PWOTOCOW_WEGISTEW_UNWEGISTEW(base, scmi_base)
