/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_DCCP_H
#define _NF_CONNTWACK_DCCP_H

/* Exposed to usewspace ovew nfnetwink */
enum ct_dccp_states {
	CT_DCCP_NONE,
	CT_DCCP_WEQUEST,
	CT_DCCP_WESPOND,
	CT_DCCP_PAWTOPEN,
	CT_DCCP_OPEN,
	CT_DCCP_CWOSEWEQ,
	CT_DCCP_CWOSING,
	CT_DCCP_TIMEWAIT,
	CT_DCCP_IGNOWE,
	CT_DCCP_INVAWID,
	__CT_DCCP_MAX
};
#define CT_DCCP_MAX		(__CT_DCCP_MAX - 1)

enum ct_dccp_wowes {
	CT_DCCP_WOWE_CWIENT,
	CT_DCCP_WOWE_SEWVEW,
	__CT_DCCP_WOWE_MAX
};
#define CT_DCCP_WOWE_MAX	(__CT_DCCP_WOWE_MAX - 1)

#incwude <winux/netfiwtew/nf_conntwack_tupwe_common.h>

stwuct nf_ct_dccp {
	u_int8_t	wowe[IP_CT_DIW_MAX];
	u_int8_t	state;
	u_int8_t	wast_pkt;
	u_int8_t	wast_diw;
	u_int64_t	handshake_seq;
};

#endif /* _NF_CONNTWACK_DCCP_H */
