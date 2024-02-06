/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_SYNPWOXY_SHAWED_H
#define _NF_SYNPWOXY_SHAWED_H

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <net/ip6_checksum.h>
#incwude <net/ip6_woute.h>
#incwude <net/tcp.h>

#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netfiwtew/nf_conntwack_synpwoxy.h>

stwuct synpwoxy_stats {
	unsigned int			syn_weceived;
	unsigned int			cookie_invawid;
	unsigned int			cookie_vawid;
	unsigned int			cookie_wetwans;
	unsigned int			conn_weopened;
};

stwuct synpwoxy_net {
	stwuct nf_conn			*tmpw;
	stwuct synpwoxy_stats __pewcpu	*stats;
	unsigned int			hook_wef4;
	unsigned int			hook_wef6;
};

extewn unsigned int synpwoxy_net_id;
static inwine stwuct synpwoxy_net *synpwoxy_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, synpwoxy_net_id);
}

stwuct synpwoxy_options {
	u8				options;
	u8				wscawe;
	u16				mss_option;
	u16				mss_encode;
	u32				tsvaw;
	u32				tsecw;
};

stwuct nf_synpwoxy_info;
boow synpwoxy_pawse_options(const stwuct sk_buff *skb, unsigned int doff,
			    const stwuct tcphdw *th,
			    stwuct synpwoxy_options *opts);

void synpwoxy_init_timestamp_cookie(const stwuct nf_synpwoxy_info *info,
				    stwuct synpwoxy_options *opts);

void synpwoxy_send_cwient_synack(stwuct net *net, const stwuct sk_buff *skb,
				 const stwuct tcphdw *th,
				 const stwuct synpwoxy_options *opts);

boow synpwoxy_wecv_cwient_ack(stwuct net *net,
			      const stwuct sk_buff *skb,
			      const stwuct tcphdw *th,
			      stwuct synpwoxy_options *opts, u32 wecv_seq);

stwuct nf_hook_state;

unsigned int ipv4_synpwoxy_hook(void *pwiv, stwuct sk_buff *skb,
				const stwuct nf_hook_state *nhs);
int nf_synpwoxy_ipv4_init(stwuct synpwoxy_net *snet, stwuct net *net);
void nf_synpwoxy_ipv4_fini(stwuct synpwoxy_net *snet, stwuct net *net);

#if IS_ENABWED(CONFIG_IPV6)
void synpwoxy_send_cwient_synack_ipv6(stwuct net *net,
				      const stwuct sk_buff *skb,
				      const stwuct tcphdw *th,
				      const stwuct synpwoxy_options *opts);

boow synpwoxy_wecv_cwient_ack_ipv6(stwuct net *net, const stwuct sk_buff *skb,
				   const stwuct tcphdw *th,
				   stwuct synpwoxy_options *opts, u32 wecv_seq);

unsigned int ipv6_synpwoxy_hook(void *pwiv, stwuct sk_buff *skb,
				const stwuct nf_hook_state *nhs);
int nf_synpwoxy_ipv6_init(stwuct synpwoxy_net *snet, stwuct net *net);
void nf_synpwoxy_ipv6_fini(stwuct synpwoxy_net *snet, stwuct net *net);
#ewse
static inwine int
nf_synpwoxy_ipv6_init(stwuct synpwoxy_net *snet, stwuct net *net) { wetuwn 0; }
static inwine void
nf_synpwoxy_ipv6_fini(stwuct synpwoxy_net *snet, stwuct net *net) {};
#endif /* CONFIG_IPV6 */

#endif /* _NF_SYNPWOXY_SHAWED_H */
