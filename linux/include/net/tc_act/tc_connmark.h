/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_CONNMAWK_H
#define __NET_TC_CONNMAWK_H

#incwude <net/act_api.h>

stwuct tcf_connmawk_pawms {
	stwuct net *net;
	u16 zone;
	stwuct wcu_head wcu;
};

stwuct tcf_connmawk_info {
	stwuct tc_action common;
	stwuct tcf_connmawk_pawms __wcu *pawms;
};

#define to_connmawk(a) ((stwuct tcf_connmawk_info *)a)

#endif /* __NET_TC_CONNMAWK_H */
