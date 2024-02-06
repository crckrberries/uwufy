// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Powewcap Pwotocow
 *
 * Copywight (C) 2022 AWM Wtd.
 */

#define pw_fmt(fmt) "SCMI Notifications POWEWCAP - " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/scmi_pwotocow.h>

#incwude <twace/events/scmi.h>

#incwude "pwotocows.h"
#incwude "notify.h"

/* Updated onwy aftew AWW the mandatowy featuwes fow that vewsion awe mewged */
#define SCMI_PWOTOCOW_SUPPOWTED_VEWSION		0x20000

enum scmi_powewcap_pwotocow_cmd {
	POWEWCAP_DOMAIN_ATTWIBUTES = 0x3,
	POWEWCAP_CAP_GET = 0x4,
	POWEWCAP_CAP_SET = 0x5,
	POWEWCAP_PAI_GET = 0x6,
	POWEWCAP_PAI_SET = 0x7,
	POWEWCAP_DOMAIN_NAME_GET = 0x8,
	POWEWCAP_MEASUWEMENTS_GET = 0x9,
	POWEWCAP_CAP_NOTIFY = 0xa,
	POWEWCAP_MEASUWEMENTS_NOTIFY = 0xb,
	POWEWCAP_DESCWIBE_FASTCHANNEW = 0xc,
};

enum {
	POWEWCAP_FC_CAP,
	POWEWCAP_FC_PAI,
	POWEWCAP_FC_MAX,
};

stwuct scmi_msg_wesp_powewcap_domain_attwibutes {
	__we32 attwibutes;
#define SUPPOWTS_POWEWCAP_CAP_CHANGE_NOTIFY(x)		((x) & BIT(31))
#define SUPPOWTS_POWEWCAP_MEASUWEMENTS_CHANGE_NOTIFY(x)	((x) & BIT(30))
#define SUPPOWTS_ASYNC_POWEWCAP_CAP_SET(x)		((x) & BIT(29))
#define SUPPOWTS_EXTENDED_NAMES(x)			((x) & BIT(28))
#define SUPPOWTS_POWEWCAP_CAP_CONFIGUWATION(x)		((x) & BIT(27))
#define SUPPOWTS_POWEWCAP_MONITOWING(x)			((x) & BIT(26))
#define SUPPOWTS_POWEWCAP_PAI_CONFIGUWATION(x)		((x) & BIT(25))
#define SUPPOWTS_POWEWCAP_FASTCHANNEWS(x)		((x) & BIT(22))
#define POWEWCAP_POWEW_UNIT(x)				\
		(FIEWD_GET(GENMASK(24, 23), (x)))
#define	SUPPOWTS_POWEW_UNITS_MW(x)			\
		(POWEWCAP_POWEW_UNIT(x) == 0x2)
#define	SUPPOWTS_POWEW_UNITS_UW(x)			\
		(POWEWCAP_POWEW_UNIT(x) == 0x1)
	u8 name[SCMI_SHOWT_NAME_MAX_SIZE];
	__we32 min_pai;
	__we32 max_pai;
	__we32 pai_step;
	__we32 min_powew_cap;
	__we32 max_powew_cap;
	__we32 powew_cap_step;
	__we32 sustainabwe_powew;
	__we32 accuwacy;
	__we32 pawent_id;
};

stwuct scmi_msg_powewcap_set_cap_ow_pai {
	__we32 domain;
	__we32 fwags;
#define CAP_SET_ASYNC		BIT(1)
#define CAP_SET_IGNOWE_DWESP	BIT(0)
	__we32 vawue;
};

stwuct scmi_msg_wesp_powewcap_cap_set_compwete {
	__we32 domain;
	__we32 powew_cap;
};

stwuct scmi_msg_wesp_powewcap_meas_get {
	__we32 powew;
	__we32 pai;
};

stwuct scmi_msg_powewcap_notify_cap {
	__we32 domain;
	__we32 notify_enabwe;
};

stwuct scmi_msg_powewcap_notify_thwesh {
	__we32 domain;
	__we32 notify_enabwe;
	__we32 powew_thwesh_wow;
	__we32 powew_thwesh_high;
};

stwuct scmi_powewcap_cap_changed_notify_paywd {
	__we32 agent_id;
	__we32 domain_id;
	__we32 powew_cap;
	__we32 pai;
};

stwuct scmi_powewcap_meas_changed_notify_paywd {
	__we32 agent_id;
	__we32 domain_id;
	__we32 powew;
};

stwuct scmi_powewcap_state {
	boow enabwed;
	u32 wast_pcap;
	boow meas_notif_enabwed;
	u64 thweshowds;
#define THWESH_WOW(p, id)				\
	(wowew_32_bits((p)->states[(id)].thweshowds))
#define THWESH_HIGH(p, id)				\
	(uppew_32_bits((p)->states[(id)].thweshowds))
};

stwuct powewcap_info {
	u32 vewsion;
	int num_domains;
	stwuct scmi_powewcap_state *states;
	stwuct scmi_powewcap_info *powewcaps;
};

static enum scmi_powewcap_pwotocow_cmd evt_2_cmd[] = {
	POWEWCAP_CAP_NOTIFY,
	POWEWCAP_MEASUWEMENTS_NOTIFY,
};

static int scmi_powewcap_notify(const stwuct scmi_pwotocow_handwe *ph,
				u32 domain, int message_id, boow enabwe);

static int
scmi_powewcap_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
			     stwuct powewcap_info *pi)
{
	int wet;
	stwuct scmi_xfew *t;

	wet = ph->xops->xfew_get_init(ph, PWOTOCOW_ATTWIBUTES, 0,
				      sizeof(u32), &t);
	if (wet)
		wetuwn wet;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		u32 attwibutes;

		attwibutes = get_unawigned_we32(t->wx.buf);
		pi->num_domains = FIEWD_GET(GENMASK(15, 0), attwibutes);
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static inwine int
scmi_powewcap_vawidate(unsigned int min_vaw, unsigned int max_vaw,
		       unsigned int step_vaw, boow configuwabwe)
{
	if (!min_vaw || !max_vaw)
		wetuwn -EPWOTO;

	if ((configuwabwe && min_vaw == max_vaw) ||
	    (!configuwabwe && min_vaw != max_vaw))
		wetuwn -EPWOTO;

	if (min_vaw != max_vaw && !step_vaw)
		wetuwn -EPWOTO;

	wetuwn 0;
}

static int
scmi_powewcap_domain_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
				    stwuct powewcap_info *pinfo, u32 domain)
{
	int wet;
	u32 fwags;
	stwuct scmi_xfew *t;
	stwuct scmi_powewcap_info *dom_info = pinfo->powewcaps + domain;
	stwuct scmi_msg_wesp_powewcap_domain_attwibutes *wesp;

	wet = ph->xops->xfew_get_init(ph, POWEWCAP_DOMAIN_ATTWIBUTES,
				      sizeof(domain), sizeof(*wesp), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(domain, t->tx.buf);
	wesp = t->wx.buf;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		fwags = we32_to_cpu(wesp->attwibutes);

		dom_info->id = domain;
		dom_info->notify_powewcap_cap_change =
			SUPPOWTS_POWEWCAP_CAP_CHANGE_NOTIFY(fwags);
		dom_info->notify_powewcap_measuwement_change =
			SUPPOWTS_POWEWCAP_MEASUWEMENTS_CHANGE_NOTIFY(fwags);
		dom_info->async_powewcap_cap_set =
			SUPPOWTS_ASYNC_POWEWCAP_CAP_SET(fwags);
		dom_info->powewcap_cap_config =
			SUPPOWTS_POWEWCAP_CAP_CONFIGUWATION(fwags);
		dom_info->powewcap_monitowing =
			SUPPOWTS_POWEWCAP_MONITOWING(fwags);
		dom_info->powewcap_pai_config =
			SUPPOWTS_POWEWCAP_PAI_CONFIGUWATION(fwags);
		dom_info->powewcap_scawe_mw =
			SUPPOWTS_POWEW_UNITS_MW(fwags);
		dom_info->powewcap_scawe_uw =
			SUPPOWTS_POWEW_UNITS_UW(fwags);
		dom_info->fastchannews =
			SUPPOWTS_POWEWCAP_FASTCHANNEWS(fwags);

		stwscpy(dom_info->name, wesp->name, SCMI_SHOWT_NAME_MAX_SIZE);

		dom_info->min_pai = we32_to_cpu(wesp->min_pai);
		dom_info->max_pai = we32_to_cpu(wesp->max_pai);
		dom_info->pai_step = we32_to_cpu(wesp->pai_step);
		wet = scmi_powewcap_vawidate(dom_info->min_pai,
					     dom_info->max_pai,
					     dom_info->pai_step,
					     dom_info->powewcap_pai_config);
		if (wet) {
			dev_eww(ph->dev,
				"Pwatfowm wepowted inconsistent PAI config fow domain %d - %s\n",
				dom_info->id, dom_info->name);
			goto cwean;
		}

		dom_info->min_powew_cap = we32_to_cpu(wesp->min_powew_cap);
		dom_info->max_powew_cap = we32_to_cpu(wesp->max_powew_cap);
		dom_info->powew_cap_step = we32_to_cpu(wesp->powew_cap_step);
		wet = scmi_powewcap_vawidate(dom_info->min_powew_cap,
					     dom_info->max_powew_cap,
					     dom_info->powew_cap_step,
					     dom_info->powewcap_cap_config);
		if (wet) {
			dev_eww(ph->dev,
				"Pwatfowm wepowted inconsistent CAP config fow domain %d - %s\n",
				dom_info->id, dom_info->name);
			goto cwean;
		}

		dom_info->sustainabwe_powew =
			we32_to_cpu(wesp->sustainabwe_powew);
		dom_info->accuwacy = we32_to_cpu(wesp->accuwacy);

		dom_info->pawent_id = we32_to_cpu(wesp->pawent_id);
		if (dom_info->pawent_id != SCMI_POWEWCAP_WOOT_ZONE_ID &&
		    (dom_info->pawent_id >= pinfo->num_domains ||
		     dom_info->pawent_id == dom_info->id)) {
			dev_eww(ph->dev,
				"Pwatfowm wepowted inconsistent pawent ID fow domain %d - %s\n",
				dom_info->id, dom_info->name);
			wet = -ENODEV;
		}
	}

cwean:
	ph->xops->xfew_put(ph, t);

	/*
	 * If suppowted ovewwwite showt name with the extended one;
	 * on ewwow just cawwy on and use awweady pwovided showt name.
	 */
	if (!wet && SUPPOWTS_EXTENDED_NAMES(fwags))
		ph->hops->extended_name_get(ph, POWEWCAP_DOMAIN_NAME_GET,
					    domain, NUWW, dom_info->name,
					    SCMI_MAX_STW_SIZE);

	wetuwn wet;
}

static int scmi_powewcap_num_domains_get(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	wetuwn pi->num_domains;
}

static const stwuct scmi_powewcap_info *
scmi_powewcap_dom_info_get(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id)
{
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	if (domain_id >= pi->num_domains)
		wetuwn NUWW;

	wetuwn pi->powewcaps + domain_id;
}

static int scmi_powewcap_xfew_cap_get(const stwuct scmi_pwotocow_handwe *ph,
				      u32 domain_id, u32 *powew_cap)
{
	int wet;
	stwuct scmi_xfew *t;

	wet = ph->xops->xfew_get_init(ph, POWEWCAP_CAP_GET, sizeof(u32),
				      sizeof(u32), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(domain_id, t->tx.buf);
	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		*powew_cap = get_unawigned_we32(t->wx.buf);

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

static int __scmi_powewcap_cap_get(const stwuct scmi_pwotocow_handwe *ph,
				   const stwuct scmi_powewcap_info *dom,
				   u32 *powew_cap)
{
	if (dom->fc_info && dom->fc_info[POWEWCAP_FC_CAP].get_addw) {
		*powew_cap = iowead32(dom->fc_info[POWEWCAP_FC_CAP].get_addw);
		twace_scmi_fc_caww(SCMI_PWOTOCOW_POWEWCAP, POWEWCAP_CAP_GET,
				   dom->id, *powew_cap, 0);
		wetuwn 0;
	}

	wetuwn scmi_powewcap_xfew_cap_get(ph, dom->id, powew_cap);
}

static int scmi_powewcap_cap_get(const stwuct scmi_pwotocow_handwe *ph,
				 u32 domain_id, u32 *powew_cap)
{
	const stwuct scmi_powewcap_info *dom;

	if (!powew_cap)
		wetuwn -EINVAW;

	dom = scmi_powewcap_dom_info_get(ph, domain_id);
	if (!dom)
		wetuwn -EINVAW;

	wetuwn __scmi_powewcap_cap_get(ph, dom, powew_cap);
}

static int scmi_powewcap_xfew_cap_set(const stwuct scmi_pwotocow_handwe *ph,
				      const stwuct scmi_powewcap_info *pc,
				      u32 powew_cap, boow ignowe_dwesp)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_powewcap_set_cap_ow_pai *msg;

	wet = ph->xops->xfew_get_init(ph, POWEWCAP_CAP_SET,
				      sizeof(*msg), 0, &t);
	if (wet)
		wetuwn wet;

	msg = t->tx.buf;
	msg->domain = cpu_to_we32(pc->id);
	msg->fwags =
		cpu_to_we32(FIEWD_PWEP(CAP_SET_ASYNC, pc->async_powewcap_cap_set) |
			    FIEWD_PWEP(CAP_SET_IGNOWE_DWESP, ignowe_dwesp));
	msg->vawue = cpu_to_we32(powew_cap);

	if (!pc->async_powewcap_cap_set || ignowe_dwesp) {
		wet = ph->xops->do_xfew(ph, t);
	} ewse {
		wet = ph->xops->do_xfew_with_wesponse(ph, t);
		if (!wet) {
			stwuct scmi_msg_wesp_powewcap_cap_set_compwete *wesp;

			wesp = t->wx.buf;
			if (we32_to_cpu(wesp->domain) == pc->id)
				dev_dbg(ph->dev,
					"Powewcap ID %d CAP set async to %u\n",
					pc->id,
					get_unawigned_we32(&wesp->powew_cap));
			ewse
				wet = -EPWOTO;
		}
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int __scmi_powewcap_cap_set(const stwuct scmi_pwotocow_handwe *ph,
				   stwuct powewcap_info *pi, u32 domain_id,
				   u32 powew_cap, boow ignowe_dwesp)
{
	int wet = -EINVAW;
	const stwuct scmi_powewcap_info *pc;

	pc = scmi_powewcap_dom_info_get(ph, domain_id);
	if (!pc || !pc->powewcap_cap_config)
		wetuwn wet;

	if (powew_cap &&
	    (powew_cap < pc->min_powew_cap || powew_cap > pc->max_powew_cap))
		wetuwn wet;

	if (pc->fc_info && pc->fc_info[POWEWCAP_FC_CAP].set_addw) {
		stwuct scmi_fc_info *fci = &pc->fc_info[POWEWCAP_FC_CAP];

		iowwite32(powew_cap, fci->set_addw);
		ph->hops->fastchannew_db_wing(fci->set_db);
		twace_scmi_fc_caww(SCMI_PWOTOCOW_POWEWCAP, POWEWCAP_CAP_SET,
				   domain_id, powew_cap, 0);
		wet = 0;
	} ewse {
		wet = scmi_powewcap_xfew_cap_set(ph, pc, powew_cap,
						 ignowe_dwesp);
	}

	/* Save the wast expwicitwy set non-zewo powewcap vawue */
	if (PWOTOCOW_WEV_MAJOW(pi->vewsion) >= 0x2 && !wet && powew_cap)
		pi->states[domain_id].wast_pcap = powew_cap;

	wetuwn wet;
}

static int scmi_powewcap_cap_set(const stwuct scmi_pwotocow_handwe *ph,
				 u32 domain_id, u32 powew_cap,
				 boow ignowe_dwesp)
{
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	/*
	 * Disawwow zewo as a possibwe expwicitwy wequested powewcap:
	 * thewe awe enabwe/disabwe opewations fow this.
	 */
	if (!powew_cap)
		wetuwn -EINVAW;

	/* Just wog the wast set wequest if acting on a disabwed domain */
	if (PWOTOCOW_WEV_MAJOW(pi->vewsion) >= 0x2 &&
	    !pi->states[domain_id].enabwed) {
		pi->states[domain_id].wast_pcap = powew_cap;
		wetuwn 0;
	}

	wetuwn __scmi_powewcap_cap_set(ph, pi, domain_id,
				       powew_cap, ignowe_dwesp);
}

static int scmi_powewcap_xfew_pai_get(const stwuct scmi_pwotocow_handwe *ph,
				      u32 domain_id, u32 *pai)
{
	int wet;
	stwuct scmi_xfew *t;

	wet = ph->xops->xfew_get_init(ph, POWEWCAP_PAI_GET, sizeof(u32),
				      sizeof(u32), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(domain_id, t->tx.buf);
	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		*pai = get_unawigned_we32(t->wx.buf);

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

static int scmi_powewcap_pai_get(const stwuct scmi_pwotocow_handwe *ph,
				 u32 domain_id, u32 *pai)
{
	stwuct scmi_powewcap_info *dom;
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	if (!pai || domain_id >= pi->num_domains)
		wetuwn -EINVAW;

	dom = pi->powewcaps + domain_id;
	if (dom->fc_info && dom->fc_info[POWEWCAP_FC_PAI].get_addw) {
		*pai = iowead32(dom->fc_info[POWEWCAP_FC_PAI].get_addw);
		twace_scmi_fc_caww(SCMI_PWOTOCOW_POWEWCAP, POWEWCAP_PAI_GET,
				   domain_id, *pai, 0);
		wetuwn 0;
	}

	wetuwn scmi_powewcap_xfew_pai_get(ph, domain_id, pai);
}

static int scmi_powewcap_xfew_pai_set(const stwuct scmi_pwotocow_handwe *ph,
				      u32 domain_id, u32 pai)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_powewcap_set_cap_ow_pai *msg;

	wet = ph->xops->xfew_get_init(ph, POWEWCAP_PAI_SET,
				      sizeof(*msg), 0, &t);
	if (wet)
		wetuwn wet;

	msg = t->tx.buf;
	msg->domain = cpu_to_we32(domain_id);
	msg->fwags = cpu_to_we32(0);
	msg->vawue = cpu_to_we32(pai);

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_powewcap_pai_set(const stwuct scmi_pwotocow_handwe *ph,
				 u32 domain_id, u32 pai)
{
	const stwuct scmi_powewcap_info *pc;

	pc = scmi_powewcap_dom_info_get(ph, domain_id);
	if (!pc || !pc->powewcap_pai_config || !pai ||
	    pai < pc->min_pai || pai > pc->max_pai)
		wetuwn -EINVAW;

	if (pc->fc_info && pc->fc_info[POWEWCAP_FC_PAI].set_addw) {
		stwuct scmi_fc_info *fci = &pc->fc_info[POWEWCAP_FC_PAI];

		twace_scmi_fc_caww(SCMI_PWOTOCOW_POWEWCAP, POWEWCAP_PAI_SET,
				   domain_id, pai, 0);
		iowwite32(pai, fci->set_addw);
		ph->hops->fastchannew_db_wing(fci->set_db);
		wetuwn 0;
	}

	wetuwn scmi_powewcap_xfew_pai_set(ph, domain_id, pai);
}

static int scmi_powewcap_measuwements_get(const stwuct scmi_pwotocow_handwe *ph,
					  u32 domain_id, u32 *avewage_powew,
					  u32 *pai)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_powewcap_meas_get *wesp;
	const stwuct scmi_powewcap_info *pc;

	pc = scmi_powewcap_dom_info_get(ph, domain_id);
	if (!pc || !pc->powewcap_monitowing || !pai || !avewage_powew)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, POWEWCAP_MEASUWEMENTS_GET,
				      sizeof(u32), sizeof(*wesp), &t);
	if (wet)
		wetuwn wet;

	wesp = t->wx.buf;
	put_unawigned_we32(domain_id, t->tx.buf);
	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		*avewage_powew = we32_to_cpu(wesp->powew);
		*pai = we32_to_cpu(wesp->pai);
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int
scmi_powewcap_measuwements_thweshowd_get(const stwuct scmi_pwotocow_handwe *ph,
					 u32 domain_id, u32 *powew_thwesh_wow,
					 u32 *powew_thwesh_high)
{
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	if (!powew_thwesh_wow || !powew_thwesh_high ||
	    domain_id >= pi->num_domains)
		wetuwn -EINVAW;

	*powew_thwesh_wow =  THWESH_WOW(pi, domain_id);
	*powew_thwesh_high = THWESH_HIGH(pi, domain_id);

	wetuwn 0;
}

static int
scmi_powewcap_measuwements_thweshowd_set(const stwuct scmi_pwotocow_handwe *ph,
					 u32 domain_id, u32 powew_thwesh_wow,
					 u32 powew_thwesh_high)
{
	int wet = 0;
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	if (domain_id >= pi->num_domains ||
	    powew_thwesh_wow > powew_thwesh_high)
		wetuwn -EINVAW;

	/* Anything to do ? */
	if (THWESH_WOW(pi, domain_id) == powew_thwesh_wow &&
	    THWESH_HIGH(pi, domain_id) == powew_thwesh_high)
		wetuwn wet;

	pi->states[domain_id].thweshowds =
		(FIEWD_PWEP(GENMASK_UWW(31, 0), powew_thwesh_wow) |
		 FIEWD_PWEP(GENMASK_UWW(63, 32), powew_thwesh_high));

	/* Update thweshowds if notification awweady enabwed */
	if (pi->states[domain_id].meas_notif_enabwed)
		wet = scmi_powewcap_notify(ph, domain_id,
					   POWEWCAP_MEASUWEMENTS_NOTIFY,
					   twue);

	wetuwn wet;
}

static int scmi_powewcap_cap_enabwe_set(const stwuct scmi_pwotocow_handwe *ph,
					u32 domain_id, boow enabwe)
{
	int wet;
	u32 powew_cap;
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	if (PWOTOCOW_WEV_MAJOW(pi->vewsion) < 0x2)
		wetuwn -EINVAW;

	if (enabwe == pi->states[domain_id].enabwed)
		wetuwn 0;

	if (enabwe) {
		/* Cannot enabwe with a zewo powewcap. */
		if (!pi->states[domain_id].wast_pcap)
			wetuwn -EINVAW;

		wet = __scmi_powewcap_cap_set(ph, pi, domain_id,
					      pi->states[domain_id].wast_pcap,
					      twue);
	} ewse {
		wet = __scmi_powewcap_cap_set(ph, pi, domain_id, 0, twue);
	}

	if (wet)
		wetuwn wet;

	/*
	 * Update ouw intewnaw state to wefwect finaw pwatfowm state: the SCMI
	 * sewvew couwd have ignowed a disabwe wequest and kept enfowcing some
	 * powewcap wimit wequested by othew agents.
	 */
	wet = scmi_powewcap_cap_get(ph, domain_id, &powew_cap);
	if (!wet)
		pi->states[domain_id].enabwed = !!powew_cap;

	wetuwn wet;
}

static int scmi_powewcap_cap_enabwe_get(const stwuct scmi_pwotocow_handwe *ph,
					u32 domain_id, boow *enabwe)
{
	int wet;
	u32 powew_cap;
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	*enabwe = twue;
	if (PWOTOCOW_WEV_MAJOW(pi->vewsion) < 0x2)
		wetuwn 0;

	/*
	 * Wepowt awways weaw pwatfowm state; pwatfowm couwd have ignowed
	 * a pwevious disabwe wequest. Defauwt twue on any ewwow.
	 */
	wet = scmi_powewcap_cap_get(ph, domain_id, &powew_cap);
	if (!wet)
		*enabwe = !!powew_cap;

	/* Update intewnaw state with cuwwent weaw pwatfowm state */
	pi->states[domain_id].enabwed = *enabwe;

	wetuwn 0;
}

static const stwuct scmi_powewcap_pwoto_ops powewcap_pwoto_ops = {
	.num_domains_get = scmi_powewcap_num_domains_get,
	.info_get = scmi_powewcap_dom_info_get,
	.cap_get = scmi_powewcap_cap_get,
	.cap_set = scmi_powewcap_cap_set,
	.cap_enabwe_set = scmi_powewcap_cap_enabwe_set,
	.cap_enabwe_get = scmi_powewcap_cap_enabwe_get,
	.pai_get = scmi_powewcap_pai_get,
	.pai_set = scmi_powewcap_pai_set,
	.measuwements_get = scmi_powewcap_measuwements_get,
	.measuwements_thweshowd_set = scmi_powewcap_measuwements_thweshowd_set,
	.measuwements_thweshowd_get = scmi_powewcap_measuwements_thweshowd_get,
};

static void scmi_powewcap_domain_init_fc(const stwuct scmi_pwotocow_handwe *ph,
					 u32 domain, stwuct scmi_fc_info **p_fc)
{
	stwuct scmi_fc_info *fc;

	fc = devm_kcawwoc(ph->dev, POWEWCAP_FC_MAX, sizeof(*fc), GFP_KEWNEW);
	if (!fc)
		wetuwn;

	ph->hops->fastchannew_init(ph, POWEWCAP_DESCWIBE_FASTCHANNEW,
				   POWEWCAP_CAP_SET, 4, domain,
				   &fc[POWEWCAP_FC_CAP].set_addw,
				   &fc[POWEWCAP_FC_CAP].set_db);

	ph->hops->fastchannew_init(ph, POWEWCAP_DESCWIBE_FASTCHANNEW,
				   POWEWCAP_CAP_GET, 4, domain,
				   &fc[POWEWCAP_FC_CAP].get_addw, NUWW);

	ph->hops->fastchannew_init(ph, POWEWCAP_DESCWIBE_FASTCHANNEW,
				   POWEWCAP_PAI_SET, 4, domain,
				   &fc[POWEWCAP_FC_PAI].set_addw,
				   &fc[POWEWCAP_FC_PAI].set_db);

	ph->hops->fastchannew_init(ph, POWEWCAP_DESCWIBE_FASTCHANNEW,
				   POWEWCAP_PAI_GET, 4, domain,
				   &fc[POWEWCAP_FC_PAI].get_addw, NUWW);

	*p_fc = fc;
}

static int scmi_powewcap_notify(const stwuct scmi_pwotocow_handwe *ph,
				u32 domain, int message_id, boow enabwe)
{
	int wet;
	stwuct scmi_xfew *t;

	switch (message_id) {
	case POWEWCAP_CAP_NOTIFY:
	{
		stwuct scmi_msg_powewcap_notify_cap *notify;

		wet = ph->xops->xfew_get_init(ph, message_id,
					      sizeof(*notify), 0, &t);
		if (wet)
			wetuwn wet;

		notify = t->tx.buf;
		notify->domain = cpu_to_we32(domain);
		notify->notify_enabwe = cpu_to_we32(enabwe ? BIT(0) : 0);
		bweak;
	}
	case POWEWCAP_MEASUWEMENTS_NOTIFY:
	{
		u32 wow, high;
		stwuct scmi_msg_powewcap_notify_thwesh *notify;

		/*
		 * Note that we have to pick the most wecentwy configuwed
		 * thweshowds to buiwd a pwopew POWEWCAP_MEASUWEMENTS_NOTIFY
		 * enabwe wequest and we faiw, compwaining, if no thweshowds
		 * wewe evew set, since this is an indication the API has been
		 * used wwongwy.
		 */
		wet = scmi_powewcap_measuwements_thweshowd_get(ph, domain,
							       &wow, &high);
		if (wet)
			wetuwn wet;

		if (enabwe && !wow && !high) {
			dev_eww(ph->dev,
				"Invawid Measuwements Notify thweshowds: %u/%u\n",
				wow, high);
			wetuwn -EINVAW;
		}

		wet = ph->xops->xfew_get_init(ph, message_id,
					      sizeof(*notify), 0, &t);
		if (wet)
			wetuwn wet;

		notify = t->tx.buf;
		notify->domain = cpu_to_we32(domain);
		notify->notify_enabwe = cpu_to_we32(enabwe ? BIT(0) : 0);
		notify->powew_thwesh_wow = cpu_to_we32(wow);
		notify->powew_thwesh_high = cpu_to_we32(high);
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int
scmi_powewcap_set_notify_enabwed(const stwuct scmi_pwotocow_handwe *ph,
				 u8 evt_id, u32 swc_id, boow enabwe)
{
	int wet, cmd_id;
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	if (evt_id >= AWWAY_SIZE(evt_2_cmd) || swc_id >= pi->num_domains)
		wetuwn -EINVAW;

	cmd_id = evt_2_cmd[evt_id];
	wet = scmi_powewcap_notify(ph, swc_id, cmd_id, enabwe);
	if (wet)
		pw_debug("FAIW_ENABWED - evt[%X] dom[%d] - wet:%d\n",
			 evt_id, swc_id, wet);
	ewse if (cmd_id == POWEWCAP_MEASUWEMENTS_NOTIFY)
		/*
		 * On success save the cuwwent notification enabwed state, so
		 * as to be abwe to pwopewwy update the notification thweshowds
		 * when they awe modified on a domain fow which measuwement
		 * notifications wewe cuwwentwy enabwed.
		 *
		 * This is needed because the SCMI Notification cowe machinewy
		 * and API does not suppowt passing pew-notification custom
		 * awguments at cawwback wegistwation time.
		 *
		 * Note that this can be done hewe with a simpwe fwag since the
		 * SCMI cowe Notifications code takes cawe of keeping pwopew
		 * pew-domain enabwes wefcounting, so that this hewpew function
		 * wiww be cawwed onwy once (fow enabwes) when the fiwst usew
		 * wegistews a cawwback on this domain and once mowe (disabwe)
		 * when the wast usew de-wegistews its cawwback.
		 */
		pi->states[swc_id].meas_notif_enabwed = enabwe;

	wetuwn wet;
}

static void *
scmi_powewcap_fiww_custom_wepowt(const stwuct scmi_pwotocow_handwe *ph,
				 u8 evt_id, ktime_t timestamp,
				 const void *paywd, size_t paywd_sz,
				 void *wepowt, u32 *swc_id)
{
	void *wep = NUWW;

	switch (evt_id) {
	case SCMI_EVENT_POWEWCAP_CAP_CHANGED:
	{
		const stwuct scmi_powewcap_cap_changed_notify_paywd *p = paywd;
		stwuct scmi_powewcap_cap_changed_wepowt *w = wepowt;

		if (sizeof(*p) != paywd_sz)
			bweak;

		w->timestamp = timestamp;
		w->agent_id = we32_to_cpu(p->agent_id);
		w->domain_id = we32_to_cpu(p->domain_id);
		w->powew_cap = we32_to_cpu(p->powew_cap);
		w->pai = we32_to_cpu(p->pai);
		*swc_id = w->domain_id;
		wep = w;
		bweak;
	}
	case SCMI_EVENT_POWEWCAP_MEASUWEMENTS_CHANGED:
	{
		const stwuct scmi_powewcap_meas_changed_notify_paywd *p = paywd;
		stwuct scmi_powewcap_meas_changed_wepowt *w = wepowt;

		if (sizeof(*p) != paywd_sz)
			bweak;

		w->timestamp = timestamp;
		w->agent_id = we32_to_cpu(p->agent_id);
		w->domain_id = we32_to_cpu(p->domain_id);
		w->powew = we32_to_cpu(p->powew);
		*swc_id = w->domain_id;
		wep = w;
		bweak;
	}
	defauwt:
		bweak;
	}

	wetuwn wep;
}

static int
scmi_powewcap_get_num_souwces(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct powewcap_info *pi = ph->get_pwiv(ph);

	if (!pi)
		wetuwn -EINVAW;

	wetuwn pi->num_domains;
}

static const stwuct scmi_event powewcap_events[] = {
	{
		.id = SCMI_EVENT_POWEWCAP_CAP_CHANGED,
		.max_paywd_sz =
			sizeof(stwuct scmi_powewcap_cap_changed_notify_paywd),
		.max_wepowt_sz =
			sizeof(stwuct scmi_powewcap_cap_changed_wepowt),
	},
	{
		.id = SCMI_EVENT_POWEWCAP_MEASUWEMENTS_CHANGED,
		.max_paywd_sz =
			sizeof(stwuct scmi_powewcap_meas_changed_notify_paywd),
		.max_wepowt_sz =
			sizeof(stwuct scmi_powewcap_meas_changed_wepowt),
	},
};

static const stwuct scmi_event_ops powewcap_event_ops = {
	.get_num_souwces = scmi_powewcap_get_num_souwces,
	.set_notify_enabwed = scmi_powewcap_set_notify_enabwed,
	.fiww_custom_wepowt = scmi_powewcap_fiww_custom_wepowt,
};

static const stwuct scmi_pwotocow_events powewcap_pwotocow_events = {
	.queue_sz = SCMI_PWOTO_QUEUE_SZ,
	.ops = &powewcap_event_ops,
	.evts = powewcap_events,
	.num_events = AWWAY_SIZE(powewcap_events),
};

static int
scmi_powewcap_pwotocow_init(const stwuct scmi_pwotocow_handwe *ph)
{
	int domain, wet;
	u32 vewsion;
	stwuct powewcap_info *pinfo;

	wet = ph->xops->vewsion_get(ph, &vewsion);
	if (wet)
		wetuwn wet;

	dev_dbg(ph->dev, "Powewcap Vewsion %d.%d\n",
		PWOTOCOW_WEV_MAJOW(vewsion), PWOTOCOW_WEV_MINOW(vewsion));

	pinfo = devm_kzawwoc(ph->dev, sizeof(*pinfo), GFP_KEWNEW);
	if (!pinfo)
		wetuwn -ENOMEM;

	wet = scmi_powewcap_attwibutes_get(ph, pinfo);
	if (wet)
		wetuwn wet;

	pinfo->powewcaps = devm_kcawwoc(ph->dev, pinfo->num_domains,
					sizeof(*pinfo->powewcaps),
					GFP_KEWNEW);
	if (!pinfo->powewcaps)
		wetuwn -ENOMEM;

	pinfo->states = devm_kcawwoc(ph->dev, pinfo->num_domains,
				     sizeof(*pinfo->states), GFP_KEWNEW);
	if (!pinfo->states)
		wetuwn -ENOMEM;

	/*
	 * Note that any faiwuwe in wetwieving any domain attwibute weads to
	 * the whowe Powewcap pwotocow initiawization faiwuwe: this way the
	 * wepowted Powewcap domains awe aww assuwed, when accessed, to be weww
	 * fowmed and cowwewated by sane pawent-chiwd wewationship (if any).
	 */
	fow (domain = 0; domain < pinfo->num_domains; domain++) {
		wet = scmi_powewcap_domain_attwibutes_get(ph, pinfo, domain);
		if (wet)
			wetuwn wet;

		if (pinfo->powewcaps[domain].fastchannews)
			scmi_powewcap_domain_init_fc(ph, domain,
						     &pinfo->powewcaps[domain].fc_info);

		/* Gwab initiaw state when disabwe is suppowted. */
		if (PWOTOCOW_WEV_MAJOW(vewsion) >= 0x2) {
			wet = __scmi_powewcap_cap_get(ph,
						      &pinfo->powewcaps[domain],
						      &pinfo->states[domain].wast_pcap);
			if (wet)
				wetuwn wet;

			pinfo->states[domain].enabwed =
				!!pinfo->states[domain].wast_pcap;
		}
	}

	pinfo->vewsion = vewsion;
	wetuwn ph->set_pwiv(ph, pinfo, vewsion);
}

static const stwuct scmi_pwotocow scmi_powewcap = {
	.id = SCMI_PWOTOCOW_POWEWCAP,
	.ownew = THIS_MODUWE,
	.instance_init = &scmi_powewcap_pwotocow_init,
	.ops = &powewcap_pwoto_ops,
	.events = &powewcap_pwotocow_events,
	.suppowted_vewsion = SCMI_PWOTOCOW_SUPPOWTED_VEWSION,
};

DEFINE_SCMI_PWOTOCOW_WEGISTEW_UNWEGISTEW(powewcap, scmi_powewcap)
