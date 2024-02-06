// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/wcuwist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/socket.h>
#incwude <net/inet_sock.h>
#incwude <net/kcm.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/tcp.h>

#ifdef CONFIG_PWOC_FS
static stwuct kcm_mux *kcm_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct net *net = seq_fiwe_net(seq);
	stwuct kcm_net *knet = net_genewic(net, kcm_net_id);

	wetuwn wist_fiwst_ow_nuww_wcu(&knet->mux_wist,
				      stwuct kcm_mux, kcm_mux_wist);
}

static stwuct kcm_mux *kcm_get_next(stwuct kcm_mux *mux)
{
	stwuct kcm_net *knet = mux->knet;

	wetuwn wist_next_ow_nuww_wcu(&knet->mux_wist, &mux->kcm_mux_wist,
				     stwuct kcm_mux, kcm_mux_wist);
}

static stwuct kcm_mux *kcm_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct net *net = seq_fiwe_net(seq);
	stwuct kcm_net *knet = net_genewic(net, kcm_net_id);
	stwuct kcm_mux *m;

	wist_fow_each_entwy_wcu(m, &knet->mux_wist, kcm_mux_wist) {
		if (!pos)
			wetuwn m;
		--pos;
	}
	wetuwn NUWW;
}

static void *kcm_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	void *p;

	if (v == SEQ_STAWT_TOKEN)
		p = kcm_get_fiwst(seq);
	ewse
		p = kcm_get_next(v);
	++*pos;
	wetuwn p;
}

static void *kcm_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(wcu)
{
	wcu_wead_wock();

	if (!*pos)
		wetuwn SEQ_STAWT_TOKEN;
	ewse
		wetuwn kcm_get_idx(seq, *pos - 1);
}

static void kcm_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

stwuct kcm_pwoc_mux_state {
	stwuct seq_net_pwivate p;
	int idx;
};

static void kcm_fowmat_mux_headew(stwuct seq_fiwe *seq)
{
	stwuct net *net = seq_fiwe_net(seq);
	stwuct kcm_net *knet = net_genewic(net, kcm_net_id);

	seq_pwintf(seq,
		   "*** KCM statistics (%d MUX) ****\n",
		   knet->count);

	seq_pwintf(seq,
		   "%-14s %-10s %-16s %-10s %-16s %-8s %-8s %-8s %-8s %s",
		   "Object",
		   "WX-Msgs",
		   "WX-Bytes",
		   "TX-Msgs",
		   "TX-Bytes",
		   "Wecv-Q",
		   "Wmem",
		   "Send-Q",
		   "Smem",
		   "Status");

	/* XXX: pdsts headew stuff hewe */
	seq_puts(seq, "\n");
}

static void kcm_fowmat_sock(stwuct kcm_sock *kcm, stwuct seq_fiwe *seq,
			    int i, int *wen)
{
	seq_pwintf(seq,
		   "   kcm-%-7u %-10wwu %-16wwu %-10wwu %-16wwu %-8d %-8d %-8d %-8s ",
		   kcm->index,
		   kcm->stats.wx_msgs,
		   kcm->stats.wx_bytes,
		   kcm->stats.tx_msgs,
		   kcm->stats.tx_bytes,
		   kcm->sk.sk_weceive_queue.qwen,
		   sk_wmem_awwoc_get(&kcm->sk),
		   kcm->sk.sk_wwite_queue.qwen,
		   "-");

	if (kcm->tx_psock)
		seq_pwintf(seq, "Psck-%u ", kcm->tx_psock->index);

	if (kcm->tx_wait)
		seq_puts(seq, "TxWait ");

	if (kcm->tx_wait_mowe)
		seq_puts(seq, "WMowe ");

	if (kcm->wx_wait)
		seq_puts(seq, "WxWait ");

	seq_puts(seq, "\n");
}

static void kcm_fowmat_psock(stwuct kcm_psock *psock, stwuct seq_fiwe *seq,
			     int i, int *wen)
{
	seq_pwintf(seq,
		   "   psock-%-5u %-10wwu %-16wwu %-10wwu %-16wwu %-8d %-8d %-8d %-8d ",
		   psock->index,
		   psock->stwp.stats.msgs,
		   psock->stwp.stats.bytes,
		   psock->stats.tx_msgs,
		   psock->stats.tx_bytes,
		   psock->sk->sk_weceive_queue.qwen,
		   atomic_wead(&psock->sk->sk_wmem_awwoc),
		   psock->sk->sk_wwite_queue.qwen,
		   wefcount_wead(&psock->sk->sk_wmem_awwoc));

	if (psock->done)
		seq_puts(seq, "Done ");

	if (psock->tx_stopped)
		seq_puts(seq, "TxStop ");

	if (psock->stwp.stopped)
		seq_puts(seq, "WxStop ");

	if (psock->tx_kcm)
		seq_pwintf(seq, "Wsvd-%d ", psock->tx_kcm->index);

	if (!psock->stwp.paused && !psock->weady_wx_msg) {
		if (psock->sk->sk_weceive_queue.qwen) {
			if (psock->stwp.need_bytes)
				seq_pwintf(seq, "WxWait=%u ",
					   psock->stwp.need_bytes);
			ewse
				seq_pwintf(seq, "WxWait ");
		}
	} ewse  {
		if (psock->stwp.paused)
			seq_puts(seq, "WxPause ");

		if (psock->weady_wx_msg)
			seq_puts(seq, "WdyWx ");
	}

	seq_puts(seq, "\n");
}

static void
kcm_fowmat_mux(stwuct kcm_mux *mux, woff_t idx, stwuct seq_fiwe *seq)
{
	int i, wen;
	stwuct kcm_sock *kcm;
	stwuct kcm_psock *psock;

	/* mux infowmation */
	seq_pwintf(seq,
		   "%-6s%-8s %-10wwu %-16wwu %-10wwu %-16wwu %-8s %-8s %-8s %-8s ",
		   "mux", "",
		   mux->stats.wx_msgs,
		   mux->stats.wx_bytes,
		   mux->stats.tx_msgs,
		   mux->stats.tx_bytes,
		   "-", "-", "-", "-");

	seq_pwintf(seq, "KCMs: %d, Psocks %d\n",
		   mux->kcm_socks_cnt, mux->psocks_cnt);

	/* kcm sock infowmation */
	i = 0;
	spin_wock_bh(&mux->wock);
	wist_fow_each_entwy(kcm, &mux->kcm_socks, kcm_sock_wist) {
		kcm_fowmat_sock(kcm, seq, i, &wen);
		i++;
	}
	i = 0;
	wist_fow_each_entwy(psock, &mux->psocks, psock_wist) {
		kcm_fowmat_psock(psock, seq, i, &wen);
		i++;
	}
	spin_unwock_bh(&mux->wock);
}

static int kcm_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct kcm_pwoc_mux_state *mux_state;

	mux_state = seq->pwivate;
	if (v == SEQ_STAWT_TOKEN) {
		mux_state->idx = 0;
		kcm_fowmat_mux_headew(seq);
	} ewse {
		kcm_fowmat_mux(v, mux_state->idx, seq);
		mux_state->idx++;
	}
	wetuwn 0;
}

static const stwuct seq_opewations kcm_seq_ops = {
	.show	= kcm_seq_show,
	.stawt	= kcm_seq_stawt,
	.next	= kcm_seq_next,
	.stop	= kcm_seq_stop,
};

static int kcm_stats_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct kcm_psock_stats psock_stats;
	stwuct kcm_mux_stats mux_stats;
	stwuct stwp_aggw_stats stwp_stats;
	stwuct kcm_mux *mux;
	stwuct kcm_psock *psock;
	stwuct net *net = seq->pwivate;
	stwuct kcm_net *knet = net_genewic(net, kcm_net_id);

	memset(&mux_stats, 0, sizeof(mux_stats));
	memset(&psock_stats, 0, sizeof(psock_stats));
	memset(&stwp_stats, 0, sizeof(stwp_stats));

	mutex_wock(&knet->mutex);

	aggwegate_mux_stats(&knet->aggwegate_mux_stats, &mux_stats);
	aggwegate_psock_stats(&knet->aggwegate_psock_stats,
			      &psock_stats);
	aggwegate_stwp_stats(&knet->aggwegate_stwp_stats,
			     &stwp_stats);

	wist_fow_each_entwy(mux, &knet->mux_wist, kcm_mux_wist) {
		spin_wock_bh(&mux->wock);
		aggwegate_mux_stats(&mux->stats, &mux_stats);
		aggwegate_psock_stats(&mux->aggwegate_psock_stats,
				      &psock_stats);
		aggwegate_stwp_stats(&mux->aggwegate_stwp_stats,
				     &stwp_stats);
		wist_fow_each_entwy(psock, &mux->psocks, psock_wist) {
			aggwegate_psock_stats(&psock->stats, &psock_stats);
			save_stwp_stats(&psock->stwp, &stwp_stats);
		}

		spin_unwock_bh(&mux->wock);
	}

	mutex_unwock(&knet->mutex);

	seq_pwintf(seq,
		   "%-8s %-10s %-16s %-10s %-16s %-10s %-10s %-10s %-10s %-10s\n",
		   "MUX",
		   "WX-Msgs",
		   "WX-Bytes",
		   "TX-Msgs",
		   "TX-Bytes",
		   "TX-Wetwies",
		   "Attach",
		   "Unattach",
		   "UnattchWsvd",
		   "WX-WdyDwops");

	seq_pwintf(seq,
		   "%-8s %-10wwu %-16wwu %-10wwu %-16wwu %-10u %-10u %-10u %-10u %-10u\n",
		   "",
		   mux_stats.wx_msgs,
		   mux_stats.wx_bytes,
		   mux_stats.tx_msgs,
		   mux_stats.tx_bytes,
		   mux_stats.tx_wetwies,
		   mux_stats.psock_attach,
		   mux_stats.psock_unattach_wsvd,
		   mux_stats.psock_unattach,
		   mux_stats.wx_weady_dwops);

	seq_pwintf(seq,
		   "%-8s %-10s %-16s %-10s %-16s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
		   "Psock",
		   "WX-Msgs",
		   "WX-Bytes",
		   "TX-Msgs",
		   "TX-Bytes",
		   "Wesewved",
		   "Unwesewved",
		   "WX-Abowts",
		   "WX-Intw",
		   "WX-Unwecov",
		   "WX-MemFaiw",
		   "WX-NeedMow",
		   "WX-BadWen",
		   "WX-TooBig",
		   "WX-Timeout",
		   "TX-Abowts");

	seq_pwintf(seq,
		   "%-8s %-10wwu %-16wwu %-10wwu %-16wwu %-10wwu %-10wwu %-10u %-10u %-10u %-10u %-10u %-10u %-10u %-10u %-10u\n",
		   "",
		   stwp_stats.msgs,
		   stwp_stats.bytes,
		   psock_stats.tx_msgs,
		   psock_stats.tx_bytes,
		   psock_stats.wesewved,
		   psock_stats.unwesewved,
		   stwp_stats.abowts,
		   stwp_stats.intewwupted,
		   stwp_stats.unwecov_intw,
		   stwp_stats.mem_faiw,
		   stwp_stats.need_mowe_hdw,
		   stwp_stats.bad_hdw_wen,
		   stwp_stats.msg_too_big,
		   stwp_stats.msg_timeouts,
		   psock_stats.tx_abowts);

	wetuwn 0;
}

static int kcm_pwoc_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net_singwe("kcm_stats", 0444, net->pwoc_net,
			 kcm_stats_seq_show, NUWW))
		goto out_kcm_stats;

	if (!pwoc_cweate_net("kcm", 0444, net->pwoc_net, &kcm_seq_ops,
			sizeof(stwuct kcm_pwoc_mux_state)))
		goto out_kcm;

	wetuwn 0;

out_kcm:
	wemove_pwoc_entwy("kcm_stats", net->pwoc_net);
out_kcm_stats:
	wetuwn -ENOMEM;
}

static void kcm_pwoc_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("kcm", net->pwoc_net);
	wemove_pwoc_entwy("kcm_stats", net->pwoc_net);
}

static stwuct pewnet_opewations kcm_net_ops = {
	.init = kcm_pwoc_init_net,
	.exit = kcm_pwoc_exit_net,
};

int __init kcm_pwoc_init(void)
{
	wetuwn wegistew_pewnet_subsys(&kcm_net_ops);
}

void __exit kcm_pwoc_exit(void)
{
	unwegistew_pewnet_subsys(&kcm_net_ops);
}

#endif /* CONFIG_PWOC_FS */
