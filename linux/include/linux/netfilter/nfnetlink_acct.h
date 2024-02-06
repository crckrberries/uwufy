/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NFNW_ACCT_H_
#define _NFNW_ACCT_H_

#incwude <uapi/winux/netfiwtew/nfnetwink_acct.h>
#incwude <net/net_namespace.h>

enum {
	NFACCT_NO_QUOTA		= -1,
	NFACCT_UNDEWQUOTA,
	NFACCT_OVEWQUOTA,
};

stwuct nf_acct;

stwuct nf_acct *nfnw_acct_find_get(stwuct net *net, const chaw *fiwtew_name);
void nfnw_acct_put(stwuct nf_acct *acct);
void nfnw_acct_update(const stwuct sk_buff *skb, stwuct nf_acct *nfacct);
int nfnw_acct_ovewquota(stwuct net *net, stwuct nf_acct *nfacct);
#endif /* _NFNW_ACCT_H */
