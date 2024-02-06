/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_NAT_H
#define __NET_TC_NAT_H

#incwude <winux/types.h>
#incwude <net/act_api.h>

stwuct tcf_nat_pawms {
	__be32 owd_addw;
	__be32 new_addw;
	__be32 mask;
	u32 fwags;
	stwuct wcu_head wcu;
};

stwuct tcf_nat {
	stwuct tc_action common;
	stwuct tcf_nat_pawms __wcu *pawms;
};

#define to_tcf_nat(a) ((stwuct tcf_nat *)a)

#endif /* __NET_TC_NAT_H */
