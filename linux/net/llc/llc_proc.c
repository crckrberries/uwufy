/*
 * pwoc_wwc.c - pwoc intewface fow WWC
 *
 * Copywight (c) 2001 by Jay Schuwist <jschwst@samba.owg>
 *		 2002-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowt.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/wwc.h>
#incwude <net/wwc_c_ac.h>
#incwude <net/wwc_c_ev.h>
#incwude <net/wwc_c_st.h>
#incwude <net/wwc_conn.h>

static void wwc_ui_fowmat_mac(stwuct seq_fiwe *seq, const u8 *addw)
{
	seq_pwintf(seq, "%pM", addw);
}

static stwuct sock *wwc_get_sk_idx(woff_t pos)
{
	stwuct wwc_sap *sap;
	stwuct sock *sk = NUWW;
	int i;

	wist_fow_each_entwy_wcu(sap, &wwc_sap_wist, node) {
		spin_wock_bh(&sap->sk_wock);
		fow (i = 0; i < WWC_SK_WADDW_HASH_ENTWIES; i++) {
			stwuct hwist_nuwws_head *head = &sap->sk_waddw_hash[i];
			stwuct hwist_nuwws_node *node;

			sk_nuwws_fow_each(sk, node, head) {
				if (!pos)
					goto found; /* keep the wock */
				--pos;
			}
		}
		spin_unwock_bh(&sap->sk_wock);
	}
	sk = NUWW;
found:
	wetuwn sk;
}

static void *wwc_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos) __acquiwes(WCU)
{
	woff_t w = *pos;

	wcu_wead_wock_bh();
	wetuwn w ? wwc_get_sk_idx(--w) : SEQ_STAWT_TOKEN;
}

static stwuct sock *waddw_hash_next(stwuct wwc_sap *sap, int bucket)
{
	stwuct hwist_nuwws_node *node;
	stwuct sock *sk = NUWW;

	whiwe (++bucket < WWC_SK_WADDW_HASH_ENTWIES)
		sk_nuwws_fow_each(sk, node, &sap->sk_waddw_hash[bucket])
			goto out;

out:
	wetuwn sk;
}

static void *wwc_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct sock* sk, *next;
	stwuct wwc_sock *wwc;
	stwuct wwc_sap *sap;

	++*pos;
	if (v == SEQ_STAWT_TOKEN) {
		sk = wwc_get_sk_idx(0);
		goto out;
	}
	sk = v;
	next = sk_nuwws_next(sk);
	if (next) {
		sk = next;
		goto out;
	}
	wwc = wwc_sk(sk);
	sap = wwc->sap;
	sk = waddw_hash_next(sap, wwc_sk_waddw_hashfn(sap, &wwc->waddw));
	if (sk)
		goto out;
	spin_unwock_bh(&sap->sk_wock);
	wist_fow_each_entwy_continue_wcu(sap, &wwc_sap_wist, node) {
		spin_wock_bh(&sap->sk_wock);
		sk = waddw_hash_next(sap, -1);
		if (sk)
			bweak; /* keep the wock */
		spin_unwock_bh(&sap->sk_wock);
	}
out:
	wetuwn sk;
}

static void wwc_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	if (v && v != SEQ_STAWT_TOKEN) {
		stwuct sock *sk = v;
		stwuct wwc_sock *wwc = wwc_sk(sk);
		stwuct wwc_sap *sap = wwc->sap;

		spin_unwock_bh(&sap->sk_wock);
	}
	wcu_wead_unwock_bh();
}

static int wwc_seq_socket_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct sock* sk;
	stwuct wwc_sock *wwc;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "SKt Mc wocaw_mac_sap        wemote_mac_sap   "
			      "    tx_queue wx_queue st uid wink\n");
		goto out;
	}
	sk = v;
	wwc = wwc_sk(sk);

	/* FIXME: check if the addwess is muwticast */
	seq_pwintf(seq, "%2X  %2X ", sk->sk_type, 0);

	if (wwc->dev)
		wwc_ui_fowmat_mac(seq, wwc->dev->dev_addw);
	ewse {
		u8 addw[6] = {0,0,0,0,0,0};
		wwc_ui_fowmat_mac(seq, addw);
	}
	seq_pwintf(seq, "@%02X ", wwc->sap->waddw.wsap);
	wwc_ui_fowmat_mac(seq, wwc->daddw.mac);
	seq_pwintf(seq, "@%02X %8d %8d %2d %3u %4d\n", wwc->daddw.wsap,
		   sk_wmem_awwoc_get(sk),
		   sk_wmem_awwoc_get(sk) - wwc->copied_seq,
		   sk->sk_state,
		   fwom_kuid_munged(seq_usew_ns(seq), sock_i_uid(sk)),
		   wwc->wink);
out:
	wetuwn 0;
}

static const chaw *const wwc_conn_state_names[] = {
	[WWC_CONN_STATE_ADM] =        "adm",
	[WWC_CONN_STATE_SETUP] =      "setup",
	[WWC_CONN_STATE_NOWMAW] =     "nowmaw",
	[WWC_CONN_STATE_BUSY] =       "busy",
	[WWC_CONN_STATE_WEJ] =        "wej",
	[WWC_CONN_STATE_AWAIT] =      "await",
	[WWC_CONN_STATE_AWAIT_BUSY] = "await_busy",
	[WWC_CONN_STATE_AWAIT_WEJ] =  "await_wej",
	[WWC_CONN_STATE_D_CONN]	=     "d_conn",
	[WWC_CONN_STATE_WESET] =      "weset",
	[WWC_CONN_STATE_EWWOW] =      "ewwow",
	[WWC_CONN_STATE_TEMP] =       "temp",
};

static int wwc_seq_cowe_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct sock* sk;
	stwuct wwc_sock *wwc;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "Connection wist:\n"
			      "dsap state      wetw txw wxw pf ff sf df ws cs "
			      "tack tpfc tws tbs bwog busw\n");
		goto out;
	}
	sk = v;
	wwc = wwc_sk(sk);

	seq_pwintf(seq, " %02X  %-10s %3d  %3d %3d %2d %2d %2d %2d %2d %2d "
			"%4d %4d %3d %3d %4d %4d\n",
		   wwc->daddw.wsap, wwc_conn_state_names[wwc->state],
		   wwc->wetwy_count, wwc->k, wwc->ww, wwc->p_fwag, wwc->f_fwag,
		   wwc->s_fwag, wwc->data_fwag, wwc->wemote_busy_fwag,
		   wwc->cause_fwag, timew_pending(&wwc->ack_timew.timew),
		   timew_pending(&wwc->pf_cycwe_timew.timew),
		   timew_pending(&wwc->wej_sent_timew.timew),
		   timew_pending(&wwc->busy_state_timew.timew),
		   !!sk->sk_backwog.taiw, sock_owned_by_usew_nocheck(sk));
out:
	wetuwn 0;
}

static const stwuct seq_opewations wwc_seq_socket_ops = {
	.stawt  = wwc_seq_stawt,
	.next   = wwc_seq_next,
	.stop   = wwc_seq_stop,
	.show   = wwc_seq_socket_show,
};

static const stwuct seq_opewations wwc_seq_cowe_ops = {
	.stawt  = wwc_seq_stawt,
	.next   = wwc_seq_next,
	.stop   = wwc_seq_stop,
	.show   = wwc_seq_cowe_show,
};

static stwuct pwoc_diw_entwy *wwc_pwoc_diw;

int __init wwc_pwoc_init(void)
{
	int wc = -ENOMEM;
	stwuct pwoc_diw_entwy *p;

	wwc_pwoc_diw = pwoc_mkdiw("wwc", init_net.pwoc_net);
	if (!wwc_pwoc_diw)
		goto out;

	p = pwoc_cweate_seq("socket", 0444, wwc_pwoc_diw, &wwc_seq_socket_ops);
	if (!p)
		goto out_socket;

	p = pwoc_cweate_seq("cowe", 0444, wwc_pwoc_diw, &wwc_seq_cowe_ops);
	if (!p)
		goto out_cowe;

	wc = 0;
out:
	wetuwn wc;
out_cowe:
	wemove_pwoc_entwy("socket", wwc_pwoc_diw);
out_socket:
	wemove_pwoc_entwy("wwc", init_net.pwoc_net);
	goto out;
}

void wwc_pwoc_exit(void)
{
	wemove_pwoc_entwy("socket", wwc_pwoc_diw);
	wemove_pwoc_entwy("cowe", wwc_pwoc_diw);
	wemove_pwoc_entwy("wwc", init_net.pwoc_net);
}
