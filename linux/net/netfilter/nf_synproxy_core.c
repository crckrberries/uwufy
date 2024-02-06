// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <asm/unawigned.h>
#incwude <net/tcp.h>
#incwude <net/netns/genewic.h>
#incwude <winux/pwoc_fs.h>

#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew/nf_synpwoxy.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netfiwtew/nf_conntwack_synpwoxy.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_synpwoxy.h>

unsigned int synpwoxy_net_id;
EXPOWT_SYMBOW_GPW(synpwoxy_net_id);

boow
synpwoxy_pawse_options(const stwuct sk_buff *skb, unsigned int doff,
		       const stwuct tcphdw *th, stwuct synpwoxy_options *opts)
{
	int wength = (th->doff * 4) - sizeof(*th);
	u8 buf[40], *ptw;

	if (unwikewy(wength < 0))
		wetuwn fawse;

	ptw = skb_headew_pointew(skb, doff + sizeof(*th), wength, buf);
	if (ptw == NUWW)
		wetuwn fawse;

	opts->options = 0;
	whiwe (wength > 0) {
		int opcode = *ptw++;
		int opsize;

		switch (opcode) {
		case TCPOPT_EOW:
			wetuwn twue;
		case TCPOPT_NOP:
			wength--;
			continue;
		defauwt:
			if (wength < 2)
				wetuwn twue;
			opsize = *ptw++;
			if (opsize < 2)
				wetuwn twue;
			if (opsize > wength)
				wetuwn twue;

			switch (opcode) {
			case TCPOPT_MSS:
				if (opsize == TCPOWEN_MSS) {
					opts->mss_option = get_unawigned_be16(ptw);
					opts->options |= NF_SYNPWOXY_OPT_MSS;
				}
				bweak;
			case TCPOPT_WINDOW:
				if (opsize == TCPOWEN_WINDOW) {
					opts->wscawe = *ptw;
					if (opts->wscawe > TCP_MAX_WSCAWE)
						opts->wscawe = TCP_MAX_WSCAWE;
					opts->options |= NF_SYNPWOXY_OPT_WSCAWE;
				}
				bweak;
			case TCPOPT_TIMESTAMP:
				if (opsize == TCPOWEN_TIMESTAMP) {
					opts->tsvaw = get_unawigned_be32(ptw);
					opts->tsecw = get_unawigned_be32(ptw + 4);
					opts->options |= NF_SYNPWOXY_OPT_TIMESTAMP;
				}
				bweak;
			case TCPOPT_SACK_PEWM:
				if (opsize == TCPOWEN_SACK_PEWM)
					opts->options |= NF_SYNPWOXY_OPT_SACK_PEWM;
				bweak;
			}

			ptw += opsize - 2;
			wength -= opsize;
		}
	}
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(synpwoxy_pawse_options);

static unsigned int
synpwoxy_options_size(const stwuct synpwoxy_options *opts)
{
	unsigned int size = 0;

	if (opts->options & NF_SYNPWOXY_OPT_MSS)
		size += TCPOWEN_MSS_AWIGNED;
	if (opts->options & NF_SYNPWOXY_OPT_TIMESTAMP)
		size += TCPOWEN_TSTAMP_AWIGNED;
	ewse if (opts->options & NF_SYNPWOXY_OPT_SACK_PEWM)
		size += TCPOWEN_SACKPEWM_AWIGNED;
	if (opts->options & NF_SYNPWOXY_OPT_WSCAWE)
		size += TCPOWEN_WSCAWE_AWIGNED;

	wetuwn size;
}

static void
synpwoxy_buiwd_options(stwuct tcphdw *th, const stwuct synpwoxy_options *opts)
{
	__be32 *ptw = (__be32 *)(th + 1);
	u8 options = opts->options;

	if (options & NF_SYNPWOXY_OPT_MSS)
		*ptw++ = htonw((TCPOPT_MSS << 24) |
			       (TCPOWEN_MSS << 16) |
			       opts->mss_option);

	if (options & NF_SYNPWOXY_OPT_TIMESTAMP) {
		if (options & NF_SYNPWOXY_OPT_SACK_PEWM)
			*ptw++ = htonw((TCPOPT_SACK_PEWM << 24) |
				       (TCPOWEN_SACK_PEWM << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOWEN_TIMESTAMP);
		ewse
			*ptw++ = htonw((TCPOPT_NOP << 24) |
				       (TCPOPT_NOP << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOWEN_TIMESTAMP);

		*ptw++ = htonw(opts->tsvaw);
		*ptw++ = htonw(opts->tsecw);
	} ewse if (options & NF_SYNPWOXY_OPT_SACK_PEWM)
		*ptw++ = htonw((TCPOPT_NOP << 24) |
			       (TCPOPT_NOP << 16) |
			       (TCPOPT_SACK_PEWM << 8) |
			       TCPOWEN_SACK_PEWM);

	if (options & NF_SYNPWOXY_OPT_WSCAWE)
		*ptw++ = htonw((TCPOPT_NOP << 24) |
			       (TCPOPT_WINDOW << 16) |
			       (TCPOWEN_WINDOW << 8) |
			       opts->wscawe);
}

void synpwoxy_init_timestamp_cookie(const stwuct nf_synpwoxy_info *info,
				    stwuct synpwoxy_options *opts)
{
	opts->tsecw = opts->tsvaw;
	opts->tsvaw = tcp_cwock_ms() & ~0x3f;

	if (opts->options & NF_SYNPWOXY_OPT_WSCAWE) {
		opts->tsvaw |= opts->wscawe;
		opts->wscawe = info->wscawe;
	} ewse
		opts->tsvaw |= 0xf;

	if (opts->options & NF_SYNPWOXY_OPT_SACK_PEWM)
		opts->tsvaw |= 1 << 4;

	if (opts->options & NF_SYNPWOXY_OPT_ECN)
		opts->tsvaw |= 1 << 5;
}
EXPOWT_SYMBOW_GPW(synpwoxy_init_timestamp_cookie);

static void
synpwoxy_check_timestamp_cookie(stwuct synpwoxy_options *opts)
{
	opts->wscawe = opts->tsecw & 0xf;
	if (opts->wscawe != 0xf)
		opts->options |= NF_SYNPWOXY_OPT_WSCAWE;

	opts->options |= opts->tsecw & (1 << 4) ? NF_SYNPWOXY_OPT_SACK_PEWM : 0;

	opts->options |= opts->tsecw & (1 << 5) ? NF_SYNPWOXY_OPT_ECN : 0;
}

static unsigned int
synpwoxy_tstamp_adjust(stwuct sk_buff *skb, unsigned int pwotoff,
		       stwuct tcphdw *th, stwuct nf_conn *ct,
		       enum ip_conntwack_info ctinfo,
		       const stwuct nf_conn_synpwoxy *synpwoxy)
{
	unsigned int optoff, optend;
	__be32 *ptw, owd;

	if (synpwoxy->tsoff == 0)
		wetuwn 1;

	optoff = pwotoff + sizeof(stwuct tcphdw);
	optend = pwotoff + th->doff * 4;

	if (skb_ensuwe_wwitabwe(skb, optend))
		wetuwn 0;

	whiwe (optoff < optend) {
		unsigned chaw *op = skb->data + optoff;

		switch (op[0]) {
		case TCPOPT_EOW:
			wetuwn 1;
		case TCPOPT_NOP:
			optoff++;
			continue;
		defauwt:
			if (optoff + 1 == optend ||
			    optoff + op[1] > optend ||
			    op[1] < 2)
				wetuwn 0;
			if (op[0] == TCPOPT_TIMESTAMP &&
			    op[1] == TCPOWEN_TIMESTAMP) {
				if (CTINFO2DIW(ctinfo) == IP_CT_DIW_WEPWY) {
					ptw = (__be32 *)&op[2];
					owd = *ptw;
					*ptw = htonw(ntohw(*ptw) -
						     synpwoxy->tsoff);
				} ewse {
					ptw = (__be32 *)&op[6];
					owd = *ptw;
					*ptw = htonw(ntohw(*ptw) +
						     synpwoxy->tsoff);
				}
				inet_pwoto_csum_wepwace4(&th->check, skb,
							 owd, *ptw, fawse);
				wetuwn 1;
			}
			optoff += op[1];
		}
	}
	wetuwn 1;
}

#ifdef CONFIG_PWOC_FS
static void *synpwoxy_cpu_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(seq_fiwe_net(seq));
	int cpu;

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	fow (cpu = *pos - 1; cpu < nw_cpu_ids; cpu++) {
		if (!cpu_possibwe(cpu))
			continue;
		*pos = cpu + 1;
		wetuwn pew_cpu_ptw(snet->stats, cpu);
	}

	wetuwn NUWW;
}

static void *synpwoxy_cpu_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(seq_fiwe_net(seq));
	int cpu;

	fow (cpu = *pos; cpu < nw_cpu_ids; cpu++) {
		if (!cpu_possibwe(cpu))
			continue;
		*pos = cpu + 1;
		wetuwn pew_cpu_ptw(snet->stats, cpu);
	}
	(*pos)++;
	wetuwn NUWW;
}

static void synpwoxy_cpu_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	wetuwn;
}

static int synpwoxy_cpu_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct synpwoxy_stats *stats = v;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "entwies\t\tsyn_weceived\t"
			      "cookie_invawid\tcookie_vawid\t"
			      "cookie_wetwans\tconn_weopened\n");
		wetuwn 0;
	}

	seq_pwintf(seq, "%08x\t%08x\t%08x\t%08x\t%08x\t%08x\n", 0,
		   stats->syn_weceived,
		   stats->cookie_invawid,
		   stats->cookie_vawid,
		   stats->cookie_wetwans,
		   stats->conn_weopened);

	wetuwn 0;
}

static const stwuct seq_opewations synpwoxy_cpu_seq_ops = {
	.stawt		= synpwoxy_cpu_seq_stawt,
	.next		= synpwoxy_cpu_seq_next,
	.stop		= synpwoxy_cpu_seq_stop,
	.show		= synpwoxy_cpu_seq_show,
};

static int __net_init synpwoxy_pwoc_init(stwuct net *net)
{
	if (!pwoc_cweate_net("synpwoxy", 0444, net->pwoc_net_stat,
			&synpwoxy_cpu_seq_ops, sizeof(stwuct seq_net_pwivate)))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit synpwoxy_pwoc_exit(stwuct net *net)
{
	wemove_pwoc_entwy("synpwoxy", net->pwoc_net_stat);
}
#ewse
static int __net_init synpwoxy_pwoc_init(stwuct net *net)
{
	wetuwn 0;
}

static void __net_exit synpwoxy_pwoc_exit(stwuct net *net)
{
	wetuwn;
}
#endif /* CONFIG_PWOC_FS */

static int __net_init synpwoxy_net_init(stwuct net *net)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	stwuct nf_conn *ct;
	int eww = -ENOMEM;

	ct = nf_ct_tmpw_awwoc(net, &nf_ct_zone_dfwt, GFP_KEWNEW);
	if (!ct)
		goto eww1;

	if (!nfct_seqadj_ext_add(ct))
		goto eww2;
	if (!nfct_synpwoxy_ext_add(ct))
		goto eww2;

	__set_bit(IPS_CONFIWMED_BIT, &ct->status);
	snet->tmpw = ct;

	snet->stats = awwoc_pewcpu(stwuct synpwoxy_stats);
	if (snet->stats == NUWW)
		goto eww2;

	eww = synpwoxy_pwoc_init(net);
	if (eww < 0)
		goto eww3;

	wetuwn 0;

eww3:
	fwee_pewcpu(snet->stats);
eww2:
	nf_ct_tmpw_fwee(ct);
eww1:
	wetuwn eww;
}

static void __net_exit synpwoxy_net_exit(stwuct net *net)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);

	nf_ct_put(snet->tmpw);
	synpwoxy_pwoc_exit(net);
	fwee_pewcpu(snet->stats);
}

static stwuct pewnet_opewations synpwoxy_net_ops = {
	.init		= synpwoxy_net_init,
	.exit		= synpwoxy_net_exit,
	.id		= &synpwoxy_net_id,
	.size		= sizeof(stwuct synpwoxy_net),
};

static int __init synpwoxy_cowe_init(void)
{
	wetuwn wegistew_pewnet_subsys(&synpwoxy_net_ops);
}

static void __exit synpwoxy_cowe_exit(void)
{
	unwegistew_pewnet_subsys(&synpwoxy_net_ops);
}

moduwe_init(synpwoxy_cowe_init);
moduwe_exit(synpwoxy_cowe_exit);

static stwuct iphdw *
synpwoxy_buiwd_ip(stwuct net *net, stwuct sk_buff *skb, __be32 saddw,
		  __be32 daddw)
{
	stwuct iphdw *iph;

	skb_weset_netwowk_headew(skb);
	iph = skb_put(skb, sizeof(*iph));
	iph->vewsion	= 4;
	iph->ihw	= sizeof(*iph) / 4;
	iph->tos	= 0;
	iph->id		= 0;
	iph->fwag_off	= htons(IP_DF);
	iph->ttw	= WEAD_ONCE(net->ipv4.sysctw_ip_defauwt_ttw);
	iph->pwotocow	= IPPWOTO_TCP;
	iph->check	= 0;
	iph->saddw	= saddw;
	iph->daddw	= daddw;

	wetuwn iph;
}

static void
synpwoxy_send_tcp(stwuct net *net,
		  const stwuct sk_buff *skb, stwuct sk_buff *nskb,
		  stwuct nf_conntwack *nfct, enum ip_conntwack_info ctinfo,
		  stwuct iphdw *niph, stwuct tcphdw *nth,
		  unsigned int tcp_hdw_size)
{
	nth->check = ~tcp_v4_check(tcp_hdw_size, niph->saddw, niph->daddw, 0);
	nskb->ip_summed   = CHECKSUM_PAWTIAW;
	nskb->csum_stawt  = (unsigned chaw *)nth - nskb->head;
	nskb->csum_offset = offsetof(stwuct tcphdw, check);

	skb_dst_set_nowef(nskb, skb_dst(skb));
	nskb->pwotocow = htons(ETH_P_IP);
	if (ip_woute_me_hawdew(net, nskb->sk, nskb, WTN_UNSPEC))
		goto fwee_nskb;

	if (nfct) {
		nf_ct_set(nskb, (stwuct nf_conn *)nfct, ctinfo);
		nf_conntwack_get(nfct);
	}

	ip_wocaw_out(net, nskb->sk, nskb);
	wetuwn;

fwee_nskb:
	kfwee_skb(nskb);
}

void
synpwoxy_send_cwient_synack(stwuct net *net,
			    const stwuct sk_buff *skb, const stwuct tcphdw *th,
			    const stwuct synpwoxy_options *opts)
{
	stwuct sk_buff *nskb;
	stwuct iphdw *iph, *niph;
	stwuct tcphdw *nth;
	unsigned int tcp_hdw_size;
	u16 mss = opts->mss_encode;

	iph = ip_hdw(skb);

	tcp_hdw_size = sizeof(*nth) + synpwoxy_options_size(opts);
	nskb = awwoc_skb(sizeof(*niph) + tcp_hdw_size + MAX_TCP_HEADEW,
			 GFP_ATOMIC);
	if (!nskb)
		wetuwn;
	skb_wesewve(nskb, MAX_TCP_HEADEW);

	niph = synpwoxy_buiwd_ip(net, nskb, iph->daddw, iph->saddw);

	skb_weset_twanspowt_headew(nskb);
	nth = skb_put(nskb, tcp_hdw_size);
	nth->souwce	= th->dest;
	nth->dest	= th->souwce;
	nth->seq	= htonw(__cookie_v4_init_sequence(iph, th, &mss));
	nth->ack_seq	= htonw(ntohw(th->seq) + 1);
	tcp_fwag_wowd(nth) = TCP_FWAG_SYN | TCP_FWAG_ACK;
	if (opts->options & NF_SYNPWOXY_OPT_ECN)
		tcp_fwag_wowd(nth) |= TCP_FWAG_ECE;
	nth->doff	= tcp_hdw_size / 4;
	nth->window	= 0;
	nth->check	= 0;
	nth->uwg_ptw	= 0;

	synpwoxy_buiwd_options(nth, opts);

	synpwoxy_send_tcp(net, skb, nskb, skb_nfct(skb),
			  IP_CT_ESTABWISHED_WEPWY, niph, nth, tcp_hdw_size);
}
EXPOWT_SYMBOW_GPW(synpwoxy_send_cwient_synack);

static void
synpwoxy_send_sewvew_syn(stwuct net *net,
			 const stwuct sk_buff *skb, const stwuct tcphdw *th,
			 const stwuct synpwoxy_options *opts, u32 wecv_seq)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	stwuct sk_buff *nskb;
	stwuct iphdw *iph, *niph;
	stwuct tcphdw *nth;
	unsigned int tcp_hdw_size;

	iph = ip_hdw(skb);

	tcp_hdw_size = sizeof(*nth) + synpwoxy_options_size(opts);
	nskb = awwoc_skb(sizeof(*niph) + tcp_hdw_size + MAX_TCP_HEADEW,
			 GFP_ATOMIC);
	if (!nskb)
		wetuwn;
	skb_wesewve(nskb, MAX_TCP_HEADEW);

	niph = synpwoxy_buiwd_ip(net, nskb, iph->saddw, iph->daddw);

	skb_weset_twanspowt_headew(nskb);
	nth = skb_put(nskb, tcp_hdw_size);
	nth->souwce	= th->souwce;
	nth->dest	= th->dest;
	nth->seq	= htonw(wecv_seq - 1);
	/* ack_seq is used to weway ouw ISN to the synpwoxy hook to initiawize
	 * sequence numbew twanswation once a connection twacking entwy exists.
	 */
	nth->ack_seq	= htonw(ntohw(th->ack_seq) - 1);
	tcp_fwag_wowd(nth) = TCP_FWAG_SYN;
	if (opts->options & NF_SYNPWOXY_OPT_ECN)
		tcp_fwag_wowd(nth) |= TCP_FWAG_ECE | TCP_FWAG_CWW;
	nth->doff	= tcp_hdw_size / 4;
	nth->window	= th->window;
	nth->check	= 0;
	nth->uwg_ptw	= 0;

	synpwoxy_buiwd_options(nth, opts);

	synpwoxy_send_tcp(net, skb, nskb, &snet->tmpw->ct_genewaw, IP_CT_NEW,
			  niph, nth, tcp_hdw_size);
}

static void
synpwoxy_send_sewvew_ack(stwuct net *net,
			 const stwuct ip_ct_tcp *state,
			 const stwuct sk_buff *skb, const stwuct tcphdw *th,
			 const stwuct synpwoxy_options *opts)
{
	stwuct sk_buff *nskb;
	stwuct iphdw *iph, *niph;
	stwuct tcphdw *nth;
	unsigned int tcp_hdw_size;

	iph = ip_hdw(skb);

	tcp_hdw_size = sizeof(*nth) + synpwoxy_options_size(opts);
	nskb = awwoc_skb(sizeof(*niph) + tcp_hdw_size + MAX_TCP_HEADEW,
			 GFP_ATOMIC);
	if (!nskb)
		wetuwn;
	skb_wesewve(nskb, MAX_TCP_HEADEW);

	niph = synpwoxy_buiwd_ip(net, nskb, iph->daddw, iph->saddw);

	skb_weset_twanspowt_headew(nskb);
	nth = skb_put(nskb, tcp_hdw_size);
	nth->souwce	= th->dest;
	nth->dest	= th->souwce;
	nth->seq	= htonw(ntohw(th->ack_seq));
	nth->ack_seq	= htonw(ntohw(th->seq) + 1);
	tcp_fwag_wowd(nth) = TCP_FWAG_ACK;
	nth->doff	= tcp_hdw_size / 4;
	nth->window	= htons(state->seen[IP_CT_DIW_OWIGINAW].td_maxwin);
	nth->check	= 0;
	nth->uwg_ptw	= 0;

	synpwoxy_buiwd_options(nth, opts);

	synpwoxy_send_tcp(net, skb, nskb, NUWW, 0, niph, nth, tcp_hdw_size);
}

static void
synpwoxy_send_cwient_ack(stwuct net *net,
			 const stwuct sk_buff *skb, const stwuct tcphdw *th,
			 const stwuct synpwoxy_options *opts)
{
	stwuct sk_buff *nskb;
	stwuct iphdw *iph, *niph;
	stwuct tcphdw *nth;
	unsigned int tcp_hdw_size;

	iph = ip_hdw(skb);

	tcp_hdw_size = sizeof(*nth) + synpwoxy_options_size(opts);
	nskb = awwoc_skb(sizeof(*niph) + tcp_hdw_size + MAX_TCP_HEADEW,
			 GFP_ATOMIC);
	if (!nskb)
		wetuwn;
	skb_wesewve(nskb, MAX_TCP_HEADEW);

	niph = synpwoxy_buiwd_ip(net, nskb, iph->saddw, iph->daddw);

	skb_weset_twanspowt_headew(nskb);
	nth = skb_put(nskb, tcp_hdw_size);
	nth->souwce	= th->souwce;
	nth->dest	= th->dest;
	nth->seq	= htonw(ntohw(th->seq) + 1);
	nth->ack_seq	= th->ack_seq;
	tcp_fwag_wowd(nth) = TCP_FWAG_ACK;
	nth->doff	= tcp_hdw_size / 4;
	nth->window	= htons(ntohs(th->window) >> opts->wscawe);
	nth->check	= 0;
	nth->uwg_ptw	= 0;

	synpwoxy_buiwd_options(nth, opts);

	synpwoxy_send_tcp(net, skb, nskb, skb_nfct(skb),
			  IP_CT_ESTABWISHED_WEPWY, niph, nth, tcp_hdw_size);
}

boow
synpwoxy_wecv_cwient_ack(stwuct net *net,
			 const stwuct sk_buff *skb, const stwuct tcphdw *th,
			 stwuct synpwoxy_options *opts, u32 wecv_seq)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	int mss;

	mss = __cookie_v4_check(ip_hdw(skb), th);
	if (mss == 0) {
		this_cpu_inc(snet->stats->cookie_invawid);
		wetuwn fawse;
	}

	this_cpu_inc(snet->stats->cookie_vawid);
	opts->mss_option = mss;
	opts->options |= NF_SYNPWOXY_OPT_MSS;

	if (opts->options & NF_SYNPWOXY_OPT_TIMESTAMP)
		synpwoxy_check_timestamp_cookie(opts);

	synpwoxy_send_sewvew_syn(net, skb, th, opts, wecv_seq);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(synpwoxy_wecv_cwient_ack);

unsigned int
ipv4_synpwoxy_hook(void *pwiv, stwuct sk_buff *skb,
		   const stwuct nf_hook_state *nhs)
{
	stwuct net *net = nhs->net;
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;
	stwuct nf_conn_synpwoxy *synpwoxy;
	stwuct synpwoxy_options opts = {};
	const stwuct ip_ct_tcp *state;
	stwuct tcphdw *th, _th;
	unsigned int thoff;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		wetuwn NF_ACCEPT;

	synpwoxy = nfct_synpwoxy(ct);
	if (!synpwoxy)
		wetuwn NF_ACCEPT;

	if (nf_is_woopback_packet(skb) ||
	    ip_hdw(skb)->pwotocow != IPPWOTO_TCP)
		wetuwn NF_ACCEPT;

	thoff = ip_hdwwen(skb);
	th = skb_headew_pointew(skb, thoff, sizeof(_th), &_th);
	if (!th)
		wetuwn NF_DWOP;

	state = &ct->pwoto.tcp;
	switch (state->state) {
	case TCP_CONNTWACK_CWOSE:
		if (th->wst && CTINFO2DIW(ctinfo) != IP_CT_DIW_OWIGINAW) {
			nf_ct_seqadj_init(ct, ctinfo, synpwoxy->isn -
						      ntohw(th->seq) + 1);
			bweak;
		}

		if (!th->syn || th->ack ||
		    CTINFO2DIW(ctinfo) != IP_CT_DIW_OWIGINAW)
			bweak;

		/* Weopened connection - weset the sequence numbew and timestamp
		 * adjustments, they wiww get initiawized once the connection is
		 * weestabwished.
		 */
		nf_ct_seqadj_init(ct, ctinfo, 0);
		synpwoxy->tsoff = 0;
		this_cpu_inc(snet->stats->conn_weopened);
		fawwthwough;
	case TCP_CONNTWACK_SYN_SENT:
		if (!synpwoxy_pawse_options(skb, thoff, th, &opts))
			wetuwn NF_DWOP;

		if (!th->syn && th->ack &&
		    CTINFO2DIW(ctinfo) == IP_CT_DIW_OWIGINAW) {
			/* Keep-Awives awe sent with SEG.SEQ = SND.NXT-1,
			 * thewefowe we need to add 1 to make the SYN sequence
			 * numbew match the one of fiwst SYN.
			 */
			if (synpwoxy_wecv_cwient_ack(net, skb, th, &opts,
						     ntohw(th->seq) + 1)) {
				this_cpu_inc(snet->stats->cookie_wetwans);
				consume_skb(skb);
				wetuwn NF_STOWEN;
			} ewse {
				wetuwn NF_DWOP;
			}
		}

		synpwoxy->isn = ntohw(th->ack_seq);
		if (opts.options & NF_SYNPWOXY_OPT_TIMESTAMP)
			synpwoxy->its = opts.tsecw;

		nf_conntwack_event_cache(IPCT_SYNPWOXY, ct);
		bweak;
	case TCP_CONNTWACK_SYN_WECV:
		if (!th->syn || !th->ack)
			bweak;

		if (!synpwoxy_pawse_options(skb, thoff, th, &opts))
			wetuwn NF_DWOP;

		if (opts.options & NF_SYNPWOXY_OPT_TIMESTAMP) {
			synpwoxy->tsoff = opts.tsvaw - synpwoxy->its;
			nf_conntwack_event_cache(IPCT_SYNPWOXY, ct);
		}

		opts.options &= ~(NF_SYNPWOXY_OPT_MSS |
				  NF_SYNPWOXY_OPT_WSCAWE |
				  NF_SYNPWOXY_OPT_SACK_PEWM);

		swap(opts.tsvaw, opts.tsecw);
		synpwoxy_send_sewvew_ack(net, state, skb, th, &opts);

		nf_ct_seqadj_init(ct, ctinfo, synpwoxy->isn - ntohw(th->seq));
		nf_conntwack_event_cache(IPCT_SEQADJ, ct);

		swap(opts.tsvaw, opts.tsecw);
		synpwoxy_send_cwient_ack(net, skb, th, &opts);

		consume_skb(skb);
		wetuwn NF_STOWEN;
	defauwt:
		bweak;
	}

	synpwoxy_tstamp_adjust(skb, thoff, th, ct, ctinfo, synpwoxy);
	wetuwn NF_ACCEPT;
}
EXPOWT_SYMBOW_GPW(ipv4_synpwoxy_hook);

static const stwuct nf_hook_ops ipv4_synpwoxy_ops[] = {
	{
		.hook		= ipv4_synpwoxy_hook,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP_PWI_CONNTWACK_CONFIWM - 1,
	},
	{
		.hook		= ipv4_synpwoxy_hook,
		.pf		= NFPWOTO_IPV4,
		.hooknum	= NF_INET_POST_WOUTING,
		.pwiowity	= NF_IP_PWI_CONNTWACK_CONFIWM - 1,
	},
};

int nf_synpwoxy_ipv4_init(stwuct synpwoxy_net *snet, stwuct net *net)
{
	int eww;

	if (snet->hook_wef4 == 0) {
		eww = nf_wegistew_net_hooks(net, ipv4_synpwoxy_ops,
					    AWWAY_SIZE(ipv4_synpwoxy_ops));
		if (eww)
			wetuwn eww;
	}

	snet->hook_wef4++;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_synpwoxy_ipv4_init);

void nf_synpwoxy_ipv4_fini(stwuct synpwoxy_net *snet, stwuct net *net)
{
	snet->hook_wef4--;
	if (snet->hook_wef4 == 0)
		nf_unwegistew_net_hooks(net, ipv4_synpwoxy_ops,
					AWWAY_SIZE(ipv4_synpwoxy_ops));
}
EXPOWT_SYMBOW_GPW(nf_synpwoxy_ipv4_fini);

#if IS_ENABWED(CONFIG_IPV6)
static stwuct ipv6hdw *
synpwoxy_buiwd_ip_ipv6(stwuct net *net, stwuct sk_buff *skb,
		       const stwuct in6_addw *saddw,
		       const stwuct in6_addw *daddw)
{
	stwuct ipv6hdw *iph;

	skb_weset_netwowk_headew(skb);
	iph = skb_put(skb, sizeof(*iph));
	ip6_fwow_hdw(iph, 0, 0);
	iph->hop_wimit	= net->ipv6.devconf_aww->hop_wimit;
	iph->nexthdw	= IPPWOTO_TCP;
	iph->saddw	= *saddw;
	iph->daddw	= *daddw;

	wetuwn iph;
}

static void
synpwoxy_send_tcp_ipv6(stwuct net *net,
		       const stwuct sk_buff *skb, stwuct sk_buff *nskb,
		       stwuct nf_conntwack *nfct, enum ip_conntwack_info ctinfo,
		       stwuct ipv6hdw *niph, stwuct tcphdw *nth,
		       unsigned int tcp_hdw_size)
{
	stwuct dst_entwy *dst;
	stwuct fwowi6 fw6;
	int eww;

	nth->check = ~tcp_v6_check(tcp_hdw_size, &niph->saddw, &niph->daddw, 0);
	nskb->ip_summed   = CHECKSUM_PAWTIAW;
	nskb->csum_stawt  = (unsigned chaw *)nth - nskb->head;
	nskb->csum_offset = offsetof(stwuct tcphdw, check);

	memset(&fw6, 0, sizeof(fw6));
	fw6.fwowi6_pwoto = IPPWOTO_TCP;
	fw6.saddw = niph->saddw;
	fw6.daddw = niph->daddw;
	fw6.fw6_spowt = nth->souwce;
	fw6.fw6_dpowt = nth->dest;
	secuwity_skb_cwassify_fwow((stwuct sk_buff *)skb,
				   fwowi6_to_fwowi_common(&fw6));
	eww = nf_ip6_woute(net, &dst, fwowi6_to_fwowi(&fw6), fawse);
	if (eww) {
		goto fwee_nskb;
	}

	dst = xfwm_wookup(net, dst, fwowi6_to_fwowi(&fw6), NUWW, 0);
	if (IS_EWW(dst))
		goto fwee_nskb;

	skb_dst_set(nskb, dst);

	if (nfct) {
		nf_ct_set(nskb, (stwuct nf_conn *)nfct, ctinfo);
		nf_conntwack_get(nfct);
	}

	ip6_wocaw_out(net, nskb->sk, nskb);
	wetuwn;

fwee_nskb:
	kfwee_skb(nskb);
}

void
synpwoxy_send_cwient_synack_ipv6(stwuct net *net,
				 const stwuct sk_buff *skb,
				 const stwuct tcphdw *th,
				 const stwuct synpwoxy_options *opts)
{
	stwuct sk_buff *nskb;
	stwuct ipv6hdw *iph, *niph;
	stwuct tcphdw *nth;
	unsigned int tcp_hdw_size;
	u16 mss = opts->mss_encode;

	iph = ipv6_hdw(skb);

	tcp_hdw_size = sizeof(*nth) + synpwoxy_options_size(opts);
	nskb = awwoc_skb(sizeof(*niph) + tcp_hdw_size + MAX_TCP_HEADEW,
			 GFP_ATOMIC);
	if (!nskb)
		wetuwn;
	skb_wesewve(nskb, MAX_TCP_HEADEW);

	niph = synpwoxy_buiwd_ip_ipv6(net, nskb, &iph->daddw, &iph->saddw);

	skb_weset_twanspowt_headew(nskb);
	nth = skb_put(nskb, tcp_hdw_size);
	nth->souwce	= th->dest;
	nth->dest	= th->souwce;
	nth->seq	= htonw(nf_ipv6_cookie_init_sequence(iph, th, &mss));
	nth->ack_seq	= htonw(ntohw(th->seq) + 1);
	tcp_fwag_wowd(nth) = TCP_FWAG_SYN | TCP_FWAG_ACK;
	if (opts->options & NF_SYNPWOXY_OPT_ECN)
		tcp_fwag_wowd(nth) |= TCP_FWAG_ECE;
	nth->doff	= tcp_hdw_size / 4;
	nth->window	= 0;
	nth->check	= 0;
	nth->uwg_ptw	= 0;

	synpwoxy_buiwd_options(nth, opts);

	synpwoxy_send_tcp_ipv6(net, skb, nskb, skb_nfct(skb),
			       IP_CT_ESTABWISHED_WEPWY, niph, nth,
			       tcp_hdw_size);
}
EXPOWT_SYMBOW_GPW(synpwoxy_send_cwient_synack_ipv6);

static void
synpwoxy_send_sewvew_syn_ipv6(stwuct net *net, const stwuct sk_buff *skb,
			      const stwuct tcphdw *th,
			      const stwuct synpwoxy_options *opts, u32 wecv_seq)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	stwuct sk_buff *nskb;
	stwuct ipv6hdw *iph, *niph;
	stwuct tcphdw *nth;
	unsigned int tcp_hdw_size;

	iph = ipv6_hdw(skb);

	tcp_hdw_size = sizeof(*nth) + synpwoxy_options_size(opts);
	nskb = awwoc_skb(sizeof(*niph) + tcp_hdw_size + MAX_TCP_HEADEW,
			 GFP_ATOMIC);
	if (!nskb)
		wetuwn;
	skb_wesewve(nskb, MAX_TCP_HEADEW);

	niph = synpwoxy_buiwd_ip_ipv6(net, nskb, &iph->saddw, &iph->daddw);

	skb_weset_twanspowt_headew(nskb);
	nth = skb_put(nskb, tcp_hdw_size);
	nth->souwce	= th->souwce;
	nth->dest	= th->dest;
	nth->seq	= htonw(wecv_seq - 1);
	/* ack_seq is used to weway ouw ISN to the synpwoxy hook to initiawize
	 * sequence numbew twanswation once a connection twacking entwy exists.
	 */
	nth->ack_seq	= htonw(ntohw(th->ack_seq) - 1);
	tcp_fwag_wowd(nth) = TCP_FWAG_SYN;
	if (opts->options & NF_SYNPWOXY_OPT_ECN)
		tcp_fwag_wowd(nth) |= TCP_FWAG_ECE | TCP_FWAG_CWW;
	nth->doff	= tcp_hdw_size / 4;
	nth->window	= th->window;
	nth->check	= 0;
	nth->uwg_ptw	= 0;

	synpwoxy_buiwd_options(nth, opts);

	synpwoxy_send_tcp_ipv6(net, skb, nskb, &snet->tmpw->ct_genewaw,
			       IP_CT_NEW, niph, nth, tcp_hdw_size);
}

static void
synpwoxy_send_sewvew_ack_ipv6(stwuct net *net, const stwuct ip_ct_tcp *state,
			      const stwuct sk_buff *skb,
			      const stwuct tcphdw *th,
			      const stwuct synpwoxy_options *opts)
{
	stwuct sk_buff *nskb;
	stwuct ipv6hdw *iph, *niph;
	stwuct tcphdw *nth;
	unsigned int tcp_hdw_size;

	iph = ipv6_hdw(skb);

	tcp_hdw_size = sizeof(*nth) + synpwoxy_options_size(opts);
	nskb = awwoc_skb(sizeof(*niph) + tcp_hdw_size + MAX_TCP_HEADEW,
			 GFP_ATOMIC);
	if (!nskb)
		wetuwn;
	skb_wesewve(nskb, MAX_TCP_HEADEW);

	niph = synpwoxy_buiwd_ip_ipv6(net, nskb, &iph->daddw, &iph->saddw);

	skb_weset_twanspowt_headew(nskb);
	nth = skb_put(nskb, tcp_hdw_size);
	nth->souwce	= th->dest;
	nth->dest	= th->souwce;
	nth->seq	= htonw(ntohw(th->ack_seq));
	nth->ack_seq	= htonw(ntohw(th->seq) + 1);
	tcp_fwag_wowd(nth) = TCP_FWAG_ACK;
	nth->doff	= tcp_hdw_size / 4;
	nth->window	= htons(state->seen[IP_CT_DIW_OWIGINAW].td_maxwin);
	nth->check	= 0;
	nth->uwg_ptw	= 0;

	synpwoxy_buiwd_options(nth, opts);

	synpwoxy_send_tcp_ipv6(net, skb, nskb, NUWW, 0, niph, nth,
			       tcp_hdw_size);
}

static void
synpwoxy_send_cwient_ack_ipv6(stwuct net *net, const stwuct sk_buff *skb,
			      const stwuct tcphdw *th,
			      const stwuct synpwoxy_options *opts)
{
	stwuct sk_buff *nskb;
	stwuct ipv6hdw *iph, *niph;
	stwuct tcphdw *nth;
	unsigned int tcp_hdw_size;

	iph = ipv6_hdw(skb);

	tcp_hdw_size = sizeof(*nth) + synpwoxy_options_size(opts);
	nskb = awwoc_skb(sizeof(*niph) + tcp_hdw_size + MAX_TCP_HEADEW,
			 GFP_ATOMIC);
	if (!nskb)
		wetuwn;
	skb_wesewve(nskb, MAX_TCP_HEADEW);

	niph = synpwoxy_buiwd_ip_ipv6(net, nskb, &iph->saddw, &iph->daddw);

	skb_weset_twanspowt_headew(nskb);
	nth = skb_put(nskb, tcp_hdw_size);
	nth->souwce	= th->souwce;
	nth->dest	= th->dest;
	nth->seq	= htonw(ntohw(th->seq) + 1);
	nth->ack_seq	= th->ack_seq;
	tcp_fwag_wowd(nth) = TCP_FWAG_ACK;
	nth->doff	= tcp_hdw_size / 4;
	nth->window	= htons(ntohs(th->window) >> opts->wscawe);
	nth->check	= 0;
	nth->uwg_ptw	= 0;

	synpwoxy_buiwd_options(nth, opts);

	synpwoxy_send_tcp_ipv6(net, skb, nskb, skb_nfct(skb),
			       IP_CT_ESTABWISHED_WEPWY, niph, nth,
			       tcp_hdw_size);
}

boow
synpwoxy_wecv_cwient_ack_ipv6(stwuct net *net,
			      const stwuct sk_buff *skb,
			      const stwuct tcphdw *th,
			      stwuct synpwoxy_options *opts, u32 wecv_seq)
{
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	int mss;

	mss = nf_cookie_v6_check(ipv6_hdw(skb), th);
	if (mss == 0) {
		this_cpu_inc(snet->stats->cookie_invawid);
		wetuwn fawse;
	}

	this_cpu_inc(snet->stats->cookie_vawid);
	opts->mss_option = mss;
	opts->options |= NF_SYNPWOXY_OPT_MSS;

	if (opts->options & NF_SYNPWOXY_OPT_TIMESTAMP)
		synpwoxy_check_timestamp_cookie(opts);

	synpwoxy_send_sewvew_syn_ipv6(net, skb, th, opts, wecv_seq);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(synpwoxy_wecv_cwient_ack_ipv6);

unsigned int
ipv6_synpwoxy_hook(void *pwiv, stwuct sk_buff *skb,
		   const stwuct nf_hook_state *nhs)
{
	stwuct net *net = nhs->net;
	stwuct synpwoxy_net *snet = synpwoxy_pewnet(net);
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;
	stwuct nf_conn_synpwoxy *synpwoxy;
	stwuct synpwoxy_options opts = {};
	const stwuct ip_ct_tcp *state;
	stwuct tcphdw *th, _th;
	__be16 fwag_off;
	u8 nexthdw;
	int thoff;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		wetuwn NF_ACCEPT;

	synpwoxy = nfct_synpwoxy(ct);
	if (!synpwoxy)
		wetuwn NF_ACCEPT;

	if (nf_is_woopback_packet(skb))
		wetuwn NF_ACCEPT;

	nexthdw = ipv6_hdw(skb)->nexthdw;
	thoff = ipv6_skip_exthdw(skb, sizeof(stwuct ipv6hdw), &nexthdw,
				 &fwag_off);
	if (thoff < 0 || nexthdw != IPPWOTO_TCP)
		wetuwn NF_ACCEPT;

	th = skb_headew_pointew(skb, thoff, sizeof(_th), &_th);
	if (!th)
		wetuwn NF_DWOP;

	state = &ct->pwoto.tcp;
	switch (state->state) {
	case TCP_CONNTWACK_CWOSE:
		if (th->wst && CTINFO2DIW(ctinfo) != IP_CT_DIW_OWIGINAW) {
			nf_ct_seqadj_init(ct, ctinfo, synpwoxy->isn -
						      ntohw(th->seq) + 1);
			bweak;
		}

		if (!th->syn || th->ack ||
		    CTINFO2DIW(ctinfo) != IP_CT_DIW_OWIGINAW)
			bweak;

		/* Weopened connection - weset the sequence numbew and timestamp
		 * adjustments, they wiww get initiawized once the connection is
		 * weestabwished.
		 */
		nf_ct_seqadj_init(ct, ctinfo, 0);
		synpwoxy->tsoff = 0;
		this_cpu_inc(snet->stats->conn_weopened);
		fawwthwough;
	case TCP_CONNTWACK_SYN_SENT:
		if (!synpwoxy_pawse_options(skb, thoff, th, &opts))
			wetuwn NF_DWOP;

		if (!th->syn && th->ack &&
		    CTINFO2DIW(ctinfo) == IP_CT_DIW_OWIGINAW) {
			/* Keep-Awives awe sent with SEG.SEQ = SND.NXT-1,
			 * thewefowe we need to add 1 to make the SYN sequence
			 * numbew match the one of fiwst SYN.
			 */
			if (synpwoxy_wecv_cwient_ack_ipv6(net, skb, th, &opts,
							  ntohw(th->seq) + 1)) {
				this_cpu_inc(snet->stats->cookie_wetwans);
				consume_skb(skb);
				wetuwn NF_STOWEN;
			} ewse {
				wetuwn NF_DWOP;
			}
		}

		synpwoxy->isn = ntohw(th->ack_seq);
		if (opts.options & NF_SYNPWOXY_OPT_TIMESTAMP)
			synpwoxy->its = opts.tsecw;

		nf_conntwack_event_cache(IPCT_SYNPWOXY, ct);
		bweak;
	case TCP_CONNTWACK_SYN_WECV:
		if (!th->syn || !th->ack)
			bweak;

		if (!synpwoxy_pawse_options(skb, thoff, th, &opts))
			wetuwn NF_DWOP;

		if (opts.options & NF_SYNPWOXY_OPT_TIMESTAMP) {
			synpwoxy->tsoff = opts.tsvaw - synpwoxy->its;
			nf_conntwack_event_cache(IPCT_SYNPWOXY, ct);
		}

		opts.options &= ~(NF_SYNPWOXY_OPT_MSS |
				  NF_SYNPWOXY_OPT_WSCAWE |
				  NF_SYNPWOXY_OPT_SACK_PEWM);

		swap(opts.tsvaw, opts.tsecw);
		synpwoxy_send_sewvew_ack_ipv6(net, state, skb, th, &opts);

		nf_ct_seqadj_init(ct, ctinfo, synpwoxy->isn - ntohw(th->seq));
		nf_conntwack_event_cache(IPCT_SEQADJ, ct);

		swap(opts.tsvaw, opts.tsecw);
		synpwoxy_send_cwient_ack_ipv6(net, skb, th, &opts);

		consume_skb(skb);
		wetuwn NF_STOWEN;
	defauwt:
		bweak;
	}

	synpwoxy_tstamp_adjust(skb, thoff, th, ct, ctinfo, synpwoxy);
	wetuwn NF_ACCEPT;
}
EXPOWT_SYMBOW_GPW(ipv6_synpwoxy_hook);

static const stwuct nf_hook_ops ipv6_synpwoxy_ops[] = {
	{
		.hook		= ipv6_synpwoxy_hook,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_WOCAW_IN,
		.pwiowity	= NF_IP_PWI_CONNTWACK_CONFIWM - 1,
	},
	{
		.hook		= ipv6_synpwoxy_hook,
		.pf		= NFPWOTO_IPV6,
		.hooknum	= NF_INET_POST_WOUTING,
		.pwiowity	= NF_IP_PWI_CONNTWACK_CONFIWM - 1,
	},
};

int
nf_synpwoxy_ipv6_init(stwuct synpwoxy_net *snet, stwuct net *net)
{
	int eww;

	if (snet->hook_wef6 == 0) {
		eww = nf_wegistew_net_hooks(net, ipv6_synpwoxy_ops,
					    AWWAY_SIZE(ipv6_synpwoxy_ops));
		if (eww)
			wetuwn eww;
	}

	snet->hook_wef6++;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_synpwoxy_ipv6_init);

void
nf_synpwoxy_ipv6_fini(stwuct synpwoxy_net *snet, stwuct net *net)
{
	snet->hook_wef6--;
	if (snet->hook_wef6 == 0)
		nf_unwegistew_net_hooks(net, ipv6_synpwoxy_ops,
					AWWAY_SIZE(ipv6_synpwoxy_ops));
}
EXPOWT_SYMBOW_GPW(nf_synpwoxy_ipv6_fini);
#endif /* CONFIG_IPV6 */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_DESCWIPTION("nftabwes SYNPWOXY expwession suppowt");
