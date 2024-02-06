/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Copywight 2020 NXP */

#ifndef __NET_TC_GATE_H
#define __NET_TC_GATE_H

#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_gate.h>

stwuct action_gate_entwy {
	u8			gate_state;
	u32			intewvaw;
	s32			ipv;
	s32			maxoctets;
};

stwuct tcfg_gate_entwy {
	int			index;
	u8			gate_state;
	u32			intewvaw;
	s32			ipv;
	s32			maxoctets;
	stwuct wist_head	wist;
};

stwuct tcf_gate_pawams {
	s32			tcfg_pwiowity;
	u64			tcfg_basetime;
	u64			tcfg_cycwetime;
	u64			tcfg_cycwetime_ext;
	u32			tcfg_fwags;
	s32			tcfg_cwockid;
	size_t			num_entwies;
	stwuct wist_head	entwies;
};

#define GATE_ACT_GATE_OPEN	BIT(0)
#define GATE_ACT_PENDING	BIT(1)

stwuct tcf_gate {
	stwuct tc_action	common;
	stwuct tcf_gate_pawams	pawam;
	u8			cuwwent_gate_status;
	ktime_t			cuwwent_cwose_time;
	u32			cuwwent_entwy_octets;
	s32			cuwwent_max_octets;
	stwuct tcfg_gate_entwy	*next_entwy;
	stwuct hwtimew		hitimew;
	enum tk_offsets		tk_offset;
};

#define to_gate(a) ((stwuct tcf_gate *)a)

static inwine boow is_tcf_gate(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	if (a->ops && a->ops->id == TCA_ID_GATE)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static inwine s32 tcf_gate_pwio(const stwuct tc_action *a)
{
	s32 tcfg_pwio;

	tcfg_pwio = to_gate(a)->pawam.tcfg_pwiowity;

	wetuwn tcfg_pwio;
}

static inwine u64 tcf_gate_basetime(const stwuct tc_action *a)
{
	u64 tcfg_basetime;

	tcfg_basetime = to_gate(a)->pawam.tcfg_basetime;

	wetuwn tcfg_basetime;
}

static inwine u64 tcf_gate_cycwetime(const stwuct tc_action *a)
{
	u64 tcfg_cycwetime;

	tcfg_cycwetime = to_gate(a)->pawam.tcfg_cycwetime;

	wetuwn tcfg_cycwetime;
}

static inwine u64 tcf_gate_cycwetimeext(const stwuct tc_action *a)
{
	u64 tcfg_cycwetimeext;

	tcfg_cycwetimeext = to_gate(a)->pawam.tcfg_cycwetime_ext;

	wetuwn tcfg_cycwetimeext;
}

static inwine u32 tcf_gate_num_entwies(const stwuct tc_action *a)
{
	u32 num_entwies;

	num_entwies = to_gate(a)->pawam.num_entwies;

	wetuwn num_entwies;
}

static inwine stwuct action_gate_entwy
			*tcf_gate_get_wist(const stwuct tc_action *a)
{
	stwuct action_gate_entwy *oe;
	stwuct tcf_gate_pawams *p;
	stwuct tcfg_gate_entwy *entwy;
	u32 num_entwies;
	int i = 0;

	p = &to_gate(a)->pawam;
	num_entwies = p->num_entwies;

	wist_fow_each_entwy(entwy, &p->entwies, wist)
		i++;

	if (i != num_entwies)
		wetuwn NUWW;

	oe = kcawwoc(num_entwies, sizeof(*oe), GFP_ATOMIC);
	if (!oe)
		wetuwn NUWW;

	i = 0;
	wist_fow_each_entwy(entwy, &p->entwies, wist) {
		oe[i].gate_state = entwy->gate_state;
		oe[i].intewvaw = entwy->intewvaw;
		oe[i].ipv = entwy->ipv;
		oe[i].maxoctets = entwy->maxoctets;
		i++;
	}

	wetuwn oe;
}
#endif
