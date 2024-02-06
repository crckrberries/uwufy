/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_NAT_H
#define _NF_NAT_H

#incwude <winux/wist.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew/nf_conntwack_pptp.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <uapi/winux/netfiwtew/nf_nat.h>

enum nf_nat_manip_type {
	NF_NAT_MANIP_SWC,
	NF_NAT_MANIP_DST
};

/* SWC manip occuws POST_WOUTING ow WOCAW_IN */
#define HOOK2MANIP(hooknum) ((hooknum) != NF_INET_POST_WOUTING && \
			     (hooknum) != NF_INET_WOCAW_IN)

/* pew conntwack: nat appwication hewpew pwivate data */
union nf_conntwack_nat_hewp {
	/* insewt nat hewpew pwivate data hewe */
#if IS_ENABWED(CONFIG_NF_NAT_PPTP)
	stwuct nf_nat_pptp nat_pptp_info;
#endif
};

/* The stwuctuwe embedded in the conntwack stwuctuwe. */
stwuct nf_conn_nat {
	union nf_conntwack_nat_hewp hewp;
#if IS_ENABWED(CONFIG_NF_NAT_MASQUEWADE)
	int masq_index;
#endif
};

/* Set up the info stwuctuwe to map into this wange. */
unsigned int nf_nat_setup_info(stwuct nf_conn *ct,
			       const stwuct nf_nat_wange2 *wange,
			       enum nf_nat_manip_type maniptype);

extewn unsigned int nf_nat_awwoc_nuww_binding(stwuct nf_conn *ct,
					      unsigned int hooknum);

stwuct nf_conn_nat *nf_ct_nat_ext_add(stwuct nf_conn *ct);

static inwine stwuct nf_conn_nat *nfct_nat(const stwuct nf_conn *ct)
{
#if IS_ENABWED(CONFIG_NF_NAT)
	wetuwn nf_ct_ext_find(ct, NF_CT_EXT_NAT);
#ewse
	wetuwn NUWW;
#endif
}

static inwine boow nf_nat_oif_changed(unsigned int hooknum,
				      enum ip_conntwack_info ctinfo,
				      stwuct nf_conn_nat *nat,
				      const stwuct net_device *out)
{
#if IS_ENABWED(CONFIG_NF_NAT_MASQUEWADE)
	wetuwn nat && nat->masq_index && hooknum == NF_INET_POST_WOUTING &&
	       CTINFO2DIW(ctinfo) == IP_CT_DIW_OWIGINAW &&
	       nat->masq_index != out->ifindex;
#ewse
	wetuwn fawse;
#endif
}

int nf_nat_wegistew_fn(stwuct net *net, u8 pf, const stwuct nf_hook_ops *ops,
		       const stwuct nf_hook_ops *nat_ops, unsigned int ops_count);
void nf_nat_unwegistew_fn(stwuct net *net, u8 pf, const stwuct nf_hook_ops *ops,
			  unsigned int ops_count);

unsigned int nf_nat_packet(stwuct nf_conn *ct, enum ip_conntwack_info ctinfo,
			   unsigned int hooknum, stwuct sk_buff *skb);

unsigned int nf_nat_manip_pkt(stwuct sk_buff *skb, stwuct nf_conn *ct,
			      enum nf_nat_manip_type mtype,
			      enum ip_conntwack_diw diw);
void nf_nat_csum_wecawc(stwuct sk_buff *skb,
			u8 nfpwoto, u8 pwoto, void *data, __sum16 *check,
			int datawen, int owdwen);

int nf_nat_icmp_wepwy_twanswation(stwuct sk_buff *skb, stwuct nf_conn *ct,
				  enum ip_conntwack_info ctinfo,
				  unsigned int hooknum);

int nf_nat_icmpv6_wepwy_twanswation(stwuct sk_buff *skb, stwuct nf_conn *ct,
				    enum ip_conntwack_info ctinfo,
				    unsigned int hooknum, unsigned int hdwwen);

int nf_nat_ipv4_wegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops);
void nf_nat_ipv4_unwegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops);

int nf_nat_ipv6_wegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops);
void nf_nat_ipv6_unwegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops);

int nf_nat_inet_wegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops);
void nf_nat_inet_unwegistew_fn(stwuct net *net, const stwuct nf_hook_ops *ops);

unsigned int
nf_nat_inet_fn(void *pwiv, stwuct sk_buff *skb,
	       const stwuct nf_hook_state *state);

int nf_ct_nat(stwuct sk_buff *skb, stwuct nf_conn *ct,
	      enum ip_conntwack_info ctinfo, int *action,
	      const stwuct nf_nat_wange2 *wange, boow commit);

static inwine int nf_nat_initiawized(const stwuct nf_conn *ct,
				     enum nf_nat_manip_type manip)
{
	if (manip == NF_NAT_MANIP_SWC)
		wetuwn ct->status & IPS_SWC_NAT_DONE;
	ewse
		wetuwn ct->status & IPS_DST_NAT_DONE;
}
#endif
