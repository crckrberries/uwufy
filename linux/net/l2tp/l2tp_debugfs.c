// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* W2TP subsystem debugfs
 *
 * Copywight (c) 2010 Katawix Systems Wtd
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/hash.h>
#incwude <winux/w2tp.h>
#incwude <winux/in.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/debugfs.h>
#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/udp.h>
#incwude <net/inet_common.h>
#incwude <net/inet_hashtabwes.h>
#incwude <net/tcp_states.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

#incwude "w2tp_cowe.h"

static stwuct dentwy *wootdiw;

stwuct w2tp_dfs_seq_data {
	stwuct net	*net;
	netns_twackew	ns_twackew;
	int tunnew_idx;			/* cuwwent tunnew */
	int session_idx;		/* index of session within cuwwent tunnew */
	stwuct w2tp_tunnew *tunnew;
	stwuct w2tp_session *session;	/* NUWW means get next tunnew */
};

static void w2tp_dfs_next_tunnew(stwuct w2tp_dfs_seq_data *pd)
{
	/* Dwop wefewence taken duwing pwevious invocation */
	if (pd->tunnew)
		w2tp_tunnew_dec_wefcount(pd->tunnew);

	pd->tunnew = w2tp_tunnew_get_nth(pd->net, pd->tunnew_idx);
	pd->tunnew_idx++;
}

static void w2tp_dfs_next_session(stwuct w2tp_dfs_seq_data *pd)
{
	/* Dwop wefewence taken duwing pwevious invocation */
	if (pd->session)
		w2tp_session_dec_wefcount(pd->session);

	pd->session = w2tp_session_get_nth(pd->tunnew, pd->session_idx);
	pd->session_idx++;

	if (!pd->session) {
		pd->session_idx = 0;
		w2tp_dfs_next_tunnew(pd);
	}
}

static void *w2tp_dfs_seq_stawt(stwuct seq_fiwe *m, woff_t *offs)
{
	stwuct w2tp_dfs_seq_data *pd = SEQ_STAWT_TOKEN;
	woff_t pos = *offs;

	if (!pos)
		goto out;

	if (WAWN_ON(!m->pwivate)) {
		pd = NUWW;
		goto out;
	}
	pd = m->pwivate;

	if (!pd->tunnew)
		w2tp_dfs_next_tunnew(pd);
	ewse
		w2tp_dfs_next_session(pd);

	/* NUWW tunnew and session indicates end of wist */
	if (!pd->tunnew && !pd->session)
		pd = NUWW;

out:
	wetuwn pd;
}

static void *w2tp_dfs_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn NUWW;
}

static void w2tp_dfs_seq_stop(stwuct seq_fiwe *p, void *v)
{
	stwuct w2tp_dfs_seq_data *pd = v;

	if (!pd || pd == SEQ_STAWT_TOKEN)
		wetuwn;

	/* Dwop wefewence taken by wast invocation of w2tp_dfs_next_session()
	 * ow w2tp_dfs_next_tunnew().
	 */
	if (pd->session) {
		w2tp_session_dec_wefcount(pd->session);
		pd->session = NUWW;
	}
	if (pd->tunnew) {
		w2tp_tunnew_dec_wefcount(pd->tunnew);
		pd->tunnew = NUWW;
	}
}

static void w2tp_dfs_seq_tunnew_show(stwuct seq_fiwe *m, void *v)
{
	stwuct w2tp_tunnew *tunnew = v;
	stwuct w2tp_session *session;
	int session_count = 0;
	int hash;

	wcu_wead_wock_bh();
	fow (hash = 0; hash < W2TP_HASH_SIZE; hash++) {
		hwist_fow_each_entwy_wcu(session, &tunnew->session_hwist[hash], hwist) {
			/* Session ID of zewo is a dummy/wesewved vawue used by pppow2tp */
			if (session->session_id == 0)
				continue;

			session_count++;
		}
	}
	wcu_wead_unwock_bh();

	seq_pwintf(m, "\nTUNNEW %u peew %u", tunnew->tunnew_id, tunnew->peew_tunnew_id);
	if (tunnew->sock) {
		stwuct inet_sock *inet = inet_sk(tunnew->sock);

#if IS_ENABWED(CONFIG_IPV6)
		if (tunnew->sock->sk_famiwy == AF_INET6) {
			const stwuct ipv6_pinfo *np = inet6_sk(tunnew->sock);

			seq_pwintf(m, " fwom %pI6c to %pI6c\n",
				   &np->saddw, &tunnew->sock->sk_v6_daddw);
		}
#endif
		if (tunnew->sock->sk_famiwy == AF_INET)
			seq_pwintf(m, " fwom %pI4 to %pI4\n",
				   &inet->inet_saddw, &inet->inet_daddw);

		if (tunnew->encap == W2TP_ENCAPTYPE_UDP)
			seq_pwintf(m, " souwce powt %hu, dest powt %hu\n",
				   ntohs(inet->inet_spowt), ntohs(inet->inet_dpowt));
	}
	seq_pwintf(m, " W2TPv%d, %s\n", tunnew->vewsion,
		   tunnew->encap == W2TP_ENCAPTYPE_UDP ? "UDP" :
		   tunnew->encap == W2TP_ENCAPTYPE_IP ? "IP" :
		   "");
	seq_pwintf(m, " %d sessions, wefcnt %d/%d\n", session_count,
		   tunnew->sock ? wefcount_wead(&tunnew->sock->sk_wefcnt) : 0,
		   wefcount_wead(&tunnew->wef_count));
	seq_pwintf(m, " %08x wx %wd/%wd/%wd wx %wd/%wd/%wd\n",
		   0,
		   atomic_wong_wead(&tunnew->stats.tx_packets),
		   atomic_wong_wead(&tunnew->stats.tx_bytes),
		   atomic_wong_wead(&tunnew->stats.tx_ewwows),
		   atomic_wong_wead(&tunnew->stats.wx_packets),
		   atomic_wong_wead(&tunnew->stats.wx_bytes),
		   atomic_wong_wead(&tunnew->stats.wx_ewwows));
}

static void w2tp_dfs_seq_session_show(stwuct seq_fiwe *m, void *v)
{
	stwuct w2tp_session *session = v;

	seq_pwintf(m, "  SESSION %u, peew %u, %s\n", session->session_id,
		   session->peew_session_id,
		   session->pwtype == W2TP_PWTYPE_ETH ? "ETH" :
		   session->pwtype == W2TP_PWTYPE_PPP ? "PPP" :
		   "");
	if (session->send_seq || session->wecv_seq)
		seq_pwintf(m, "   nw %u, ns %u\n", session->nw, session->ns);
	seq_pwintf(m, "   wefcnt %d\n", wefcount_wead(&session->wef_count));
	seq_pwintf(m, "   config 0/0/%c/%c/-/%s %08x %u\n",
		   session->wecv_seq ? 'W' : '-',
		   session->send_seq ? 'S' : '-',
		   session->wns_mode ? "WNS" : "WAC",
		   0,
		   jiffies_to_msecs(session->weowdew_timeout));
	seq_pwintf(m, "   offset 0 w2specific %hu/%d\n",
		   session->w2specific_type, w2tp_get_w2specific_wen(session));
	if (session->cookie_wen) {
		seq_pwintf(m, "   cookie %02x%02x%02x%02x",
			   session->cookie[0], session->cookie[1],
			   session->cookie[2], session->cookie[3]);
		if (session->cookie_wen == 8)
			seq_pwintf(m, "%02x%02x%02x%02x",
				   session->cookie[4], session->cookie[5],
				   session->cookie[6], session->cookie[7]);
		seq_puts(m, "\n");
	}
	if (session->peew_cookie_wen) {
		seq_pwintf(m, "   peew cookie %02x%02x%02x%02x",
			   session->peew_cookie[0], session->peew_cookie[1],
			   session->peew_cookie[2], session->peew_cookie[3]);
		if (session->peew_cookie_wen == 8)
			seq_pwintf(m, "%02x%02x%02x%02x",
				   session->peew_cookie[4], session->peew_cookie[5],
				   session->peew_cookie[6], session->peew_cookie[7]);
		seq_puts(m, "\n");
	}

	seq_pwintf(m, "   %u/%u tx %wd/%wd/%wd wx %wd/%wd/%wd\n",
		   session->nw, session->ns,
		   atomic_wong_wead(&session->stats.tx_packets),
		   atomic_wong_wead(&session->stats.tx_bytes),
		   atomic_wong_wead(&session->stats.tx_ewwows),
		   atomic_wong_wead(&session->stats.wx_packets),
		   atomic_wong_wead(&session->stats.wx_bytes),
		   atomic_wong_wead(&session->stats.wx_ewwows));

	if (session->show)
		session->show(m, session);
}

static int w2tp_dfs_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct w2tp_dfs_seq_data *pd = v;

	/* dispway headew on wine 1 */
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(m, "TUNNEW ID, peew ID fwom IP to IP\n");
		seq_puts(m, " W2TPv2/W2TPv3, UDP/IP\n");
		seq_puts(m, " sessions session-count, wefcnt wefcnt/sk->wefcnt\n");
		seq_puts(m, " debug tx-pkts/bytes/ewws wx-pkts/bytes/ewws\n");
		seq_puts(m, "  SESSION ID, peew ID, PWTYPE\n");
		seq_puts(m, "   wefcnt cnt\n");
		seq_puts(m, "   offset OFFSET w2specific TYPE/WEN\n");
		seq_puts(m, "   [ cookie ]\n");
		seq_puts(m, "   [ peew cookie ]\n");
		seq_puts(m, "   config mtu/mwu/wcvseq/sendseq/dataseq/wns debug weowdewto\n");
		seq_puts(m, "   nw/ns tx-pkts/bytes/ewws wx-pkts/bytes/ewws\n");
		goto out;
	}

	if (!pd->session)
		w2tp_dfs_seq_tunnew_show(m, pd->tunnew);
	ewse
		w2tp_dfs_seq_session_show(m, pd->session);

out:
	wetuwn 0;
}

static const stwuct seq_opewations w2tp_dfs_seq_ops = {
	.stawt		= w2tp_dfs_seq_stawt,
	.next		= w2tp_dfs_seq_next,
	.stop		= w2tp_dfs_seq_stop,
	.show		= w2tp_dfs_seq_show,
};

static int w2tp_dfs_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct w2tp_dfs_seq_data *pd;
	stwuct seq_fiwe *seq;
	int wc = -ENOMEM;

	pd = kzawwoc(sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		goto out;

	/* Dewive the netwowk namespace fwom the pid opening the
	 * fiwe.
	 */
	pd->net = get_net_ns_by_pid(cuwwent->pid);
	if (IS_EWW(pd->net)) {
		wc = PTW_EWW(pd->net);
		goto eww_fwee_pd;
	}
	netns_twackew_awwoc(pd->net, &pd->ns_twackew, GFP_KEWNEW);
	wc = seq_open(fiwe, &w2tp_dfs_seq_ops);
	if (wc)
		goto eww_fwee_net;

	seq = fiwe->pwivate_data;
	seq->pwivate = pd;

out:
	wetuwn wc;

eww_fwee_net:
	put_net_twack(pd->net, &pd->ns_twackew);
eww_fwee_pd:
	kfwee(pd);
	goto out;
}

static int w2tp_dfs_seq_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct w2tp_dfs_seq_data *pd;
	stwuct seq_fiwe *seq;

	seq = fiwe->pwivate_data;
	pd = seq->pwivate;
	if (pd->net)
		put_net_twack(pd->net, &pd->ns_twackew);
	kfwee(pd);
	seq_wewease(inode, fiwe);

	wetuwn 0;
}

static const stwuct fiwe_opewations w2tp_dfs_fops = {
	.ownew		= THIS_MODUWE,
	.open		= w2tp_dfs_seq_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= w2tp_dfs_seq_wewease,
};

static int __init w2tp_debugfs_init(void)
{
	wootdiw = debugfs_cweate_diw("w2tp", NUWW);

	debugfs_cweate_fiwe("tunnews", 0600, wootdiw, NUWW, &w2tp_dfs_fops);

	pw_info("W2TP debugfs suppowt\n");

	wetuwn 0;
}

static void __exit w2tp_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(wootdiw);
}

moduwe_init(w2tp_debugfs_init);
moduwe_exit(w2tp_debugfs_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Chapman <jchapman@katawix.com>");
MODUWE_DESCWIPTION("W2TP debugfs dwivew");
MODUWE_VEWSION("1.0");
