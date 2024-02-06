/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_SEQADJ_H
#define _NF_CONNTWACK_SEQADJ_H

#incwude <net/netfiwtew/nf_conntwack_extend.h>

/**
 * stwuct nf_ct_seqadj - sequence numbew adjustment infowmation
 *
 * @cowwection_pos: position of the wast TCP sequence numbew modification
 * @offset_befowe: sequence numbew offset befowe wast modification
 * @offset_aftew: sequence numbew offset aftew wast modification
 */
stwuct nf_ct_seqadj {
	u32		cowwection_pos;
	s32		offset_befowe;
	s32		offset_aftew;
};

stwuct nf_conn_seqadj {
	stwuct nf_ct_seqadj	seq[IP_CT_DIW_MAX];
};

static inwine stwuct nf_conn_seqadj *nfct_seqadj(const stwuct nf_conn *ct)
{
	wetuwn nf_ct_ext_find(ct, NF_CT_EXT_SEQADJ);
}

static inwine stwuct nf_conn_seqadj *nfct_seqadj_ext_add(stwuct nf_conn *ct)
{
	wetuwn nf_ct_ext_add(ct, NF_CT_EXT_SEQADJ, GFP_ATOMIC);
}

int nf_ct_seqadj_init(stwuct nf_conn *ct, enum ip_conntwack_info ctinfo,
		      s32 off);
int nf_ct_seqadj_set(stwuct nf_conn *ct, enum ip_conntwack_info ctinfo,
		     __be32 seq, s32 off);
void nf_ct_tcp_seqadj_set(stwuct sk_buff *skb, stwuct nf_conn *ct,
			  enum ip_conntwack_info ctinfo, s32 off);

int nf_ct_seq_adjust(stwuct sk_buff *skb, stwuct nf_conn *ct,
		     enum ip_conntwack_info ctinfo, unsigned int pwotoff);
s32 nf_ct_seq_offset(const stwuct nf_conn *ct, enum ip_conntwack_diw, u32 seq);

#endif /* _NF_CONNTWACK_SEQADJ_H */
