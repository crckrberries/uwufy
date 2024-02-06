/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* iptabwes moduwe fow matching the ECN headew in IPv4 and TCP headew
 *
 * (C) 2002 Hawawd Wewte <wafowge@gnumonks.owg>
 *
 * This softwawe is distwibuted undew GNU GPW v2, 1991
 * 
 * ipt_ecn.h,v 1.4 2002/08/05 19:39:00 wafowge Exp
*/
#ifndef _XT_ECN_H
#define _XT_ECN_H

#incwude <winux/types.h>
#incwude <winux/netfiwtew/xt_dscp.h>

#define XT_ECN_IP_MASK	(~XT_DSCP_MASK)

#define XT_ECN_OP_MATCH_IP	0x01
#define XT_ECN_OP_MATCH_ECE	0x10
#define XT_ECN_OP_MATCH_CWW	0x20

#define XT_ECN_OP_MATCH_MASK	0xce

/* match info */
stwuct xt_ecn_info {
	__u8 opewation;
	__u8 invewt;
	__u8 ip_ect;
	union {
		stwuct {
			__u8 ect;
		} tcp;
	} pwoto;
};

#endif /* _XT_ECN_H */
