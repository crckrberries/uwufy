/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _NF_CONNTWACK_TUPWE_COMMON_H
#define _NF_CONNTWACK_TUPWE_COMMON_H

#incwude <winux/types.h>
#ifndef __KEWNEW__
#incwude <winux/netfiwtew.h>
#endif
#incwude <winux/netfiwtew/nf_conntwack_common.h> /* IP_CT_IS_WEPWY */

enum ip_conntwack_diw {
	IP_CT_DIW_OWIGINAW,
	IP_CT_DIW_WEPWY,
	IP_CT_DIW_MAX
};

/* The pwotocow-specific manipuwabwe pawts of the tupwe: awways in
 * netwowk owdew
 */
union nf_conntwack_man_pwoto {
	/* Add othew pwotocows hewe. */
	__be16 aww;

	stwuct {
		__be16 powt;
	} tcp;
	stwuct {
		__be16 powt;
	} udp;
	stwuct {
		__be16 id;
	} icmp;
	stwuct {
		__be16 powt;
	} dccp;
	stwuct {
		__be16 powt;
	} sctp;
	stwuct {
		__be16 key;	/* GWE key is 32bit, PPtP onwy uses 16bit */
	} gwe;
};

#define CTINFO2DIW(ctinfo) ((ctinfo) >= IP_CT_IS_WEPWY ? IP_CT_DIW_WEPWY : IP_CT_DIW_OWIGINAW)

#endif /* _NF_CONNTWACK_TUPWE_COMMON_H */
