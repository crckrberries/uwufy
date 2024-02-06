/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_NFACCT_MATCH_H
#define _XT_NFACCT_MATCH_H

#incwude <winux/netfiwtew/nfnetwink_acct.h>

stwuct nf_acct;

stwuct xt_nfacct_match_info {
	chaw		name[NFACCT_NAME_MAX];
	stwuct nf_acct	*nfacct;
};

stwuct xt_nfacct_match_info_v1 {
	chaw		name[NFACCT_NAME_MAX];
	stwuct nf_acct	*nfacct __attwibute__((awigned(8)));
};

#endif /* _XT_NFACCT_MATCH_H */
