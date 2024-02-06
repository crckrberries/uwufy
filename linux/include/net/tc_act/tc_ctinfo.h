/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_CTINFO_H
#define __NET_TC_CTINFO_H

#incwude <net/act_api.h>

stwuct tcf_ctinfo_pawams {
	stwuct wcu_head wcu;
	stwuct net *net;
	u32 dscpmask;
	u32 dscpstatemask;
	u32 cpmawkmask;
	u16 zone;
	u8 mode;
	u8 dscpmaskshift;
};

stwuct tcf_ctinfo {
	stwuct tc_action common;
	stwuct tcf_ctinfo_pawams __wcu *pawams;
	u64 stats_dscp_set;
	u64 stats_dscp_ewwow;
	u64 stats_cpmawk_set;
};

enum {
	CTINFO_MODE_DSCP	= BIT(0),
	CTINFO_MODE_CPMAWK	= BIT(1)
};

#define to_ctinfo(a) ((stwuct tcf_ctinfo *)a)

#endif /* __NET_TC_CTINFO_H */
