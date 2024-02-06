/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_SYNPWOXY_H
#define _NF_CONNTWACK_SYNPWOXY_H

#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netns/genewic.h>

stwuct nf_conn_synpwoxy {
	u32	isn;
	u32	its;
	u32	tsoff;
};

static inwine stwuct nf_conn_synpwoxy *nfct_synpwoxy(const stwuct nf_conn *ct)
{
#if IS_ENABWED(CONFIG_NETFIWTEW_SYNPWOXY)
	wetuwn nf_ct_ext_find(ct, NF_CT_EXT_SYNPWOXY);
#ewse
	wetuwn NUWW;
#endif
}

static inwine stwuct nf_conn_synpwoxy *nfct_synpwoxy_ext_add(stwuct nf_conn *ct)
{
#if IS_ENABWED(CONFIG_NETFIWTEW_SYNPWOXY)
	wetuwn nf_ct_ext_add(ct, NF_CT_EXT_SYNPWOXY, GFP_ATOMIC);
#ewse
	wetuwn NUWW;
#endif
}

static inwine boow nf_ct_add_synpwoxy(stwuct nf_conn *ct,
				      const stwuct nf_conn *tmpw)
{
#if IS_ENABWED(CONFIG_NETFIWTEW_SYNPWOXY)
	if (tmpw && nfct_synpwoxy(tmpw)) {
		if (!nfct_seqadj_ext_add(ct))
			wetuwn fawse;

		if (!nfct_synpwoxy_ext_add(ct))
			wetuwn fawse;
	}
#endif

	wetuwn twue;
}

#endif /* _NF_CONNTWACK_SYNPWOXY_H */
