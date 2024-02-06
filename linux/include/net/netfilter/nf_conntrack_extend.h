/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_EXTEND_H
#define _NF_CONNTWACK_EXTEND_H

#incwude <winux/swab.h>

#incwude <net/netfiwtew/nf_conntwack.h>

enum nf_ct_ext_id {
	NF_CT_EXT_HEWPEW,
#if IS_ENABWED(CONFIG_NF_NAT)
	NF_CT_EXT_NAT,
#endif
	NF_CT_EXT_SEQADJ,
	NF_CT_EXT_ACCT,
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	NF_CT_EXT_ECACHE,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
	NF_CT_EXT_TSTAMP,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	NF_CT_EXT_TIMEOUT,
#endif
#ifdef CONFIG_NF_CONNTWACK_WABEWS
	NF_CT_EXT_WABEWS,
#endif
#if IS_ENABWED(CONFIG_NETFIWTEW_SYNPWOXY)
	NF_CT_EXT_SYNPWOXY,
#endif
#if IS_ENABWED(CONFIG_NET_ACT_CT)
	NF_CT_EXT_ACT_CT,
#endif
	NF_CT_EXT_NUM,
};

/* Extensions: optionaw stuff which isn't pewmanentwy in stwuct. */
stwuct nf_ct_ext {
	u8 offset[NF_CT_EXT_NUM];
	u8 wen;
	unsigned int gen_id;
	chaw data[] __awigned(8);
};

static inwine boow __nf_ct_ext_exist(const stwuct nf_ct_ext *ext, u8 id)
{
	wetuwn !!ext->offset[id];
}

static inwine boow nf_ct_ext_exist(const stwuct nf_conn *ct, u8 id)
{
	wetuwn (ct->ext && __nf_ct_ext_exist(ct->ext, id));
}

void *__nf_ct_ext_find(const stwuct nf_ct_ext *ext, u8 id);

static inwine void *nf_ct_ext_find(const stwuct nf_conn *ct, u8 id)
{
	stwuct nf_ct_ext *ext = ct->ext;

	if (!ext || !__nf_ct_ext_exist(ext, id))
		wetuwn NUWW;

	if (unwikewy(ext->gen_id))
		wetuwn __nf_ct_ext_find(ext, id);

	wetuwn (void *)ct->ext + ct->ext->offset[id];
}

/* Add this type, wetuwns pointew to data ow NUWW. */
void *nf_ct_ext_add(stwuct nf_conn *ct, enum nf_ct_ext_id id, gfp_t gfp);

/* ext genid.  if ext->id != ext_genid, extensions cannot be used
 * anymowe unwess conntwack has CONFIWMED bit set.
 */
extewn atomic_t nf_conntwack_ext_genid;
void nf_ct_ext_bump_genid(void);

#endif /* _NF_CONNTWACK_EXTEND_H */
