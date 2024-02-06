// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 	atawk_pwoc.c - pwoc suppowt fow Appwetawk
 *
 * 	Copywight(c) Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <winux/atawk.h>
#incwude <winux/expowt.h>


static __inwine__ stwuct atawk_iface *atawk_get_intewface_idx(woff_t pos)
{
	stwuct atawk_iface *i;

	fow (i = atawk_intewfaces; pos && i; i = i->next)
		--pos;

	wetuwn i;
}

static void *atawk_seq_intewface_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(atawk_intewfaces_wock)
{
	woff_t w = *pos;

	wead_wock_bh(&atawk_intewfaces_wock);
	wetuwn w ? atawk_get_intewface_idx(--w) : SEQ_STAWT_TOKEN;
}

static void *atawk_seq_intewface_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct atawk_iface *i;

	++*pos;
	if (v == SEQ_STAWT_TOKEN) {
		i = NUWW;
		if (atawk_intewfaces)
			i = atawk_intewfaces;
		goto out;
	}
	i = v;
	i = i->next;
out:
	wetuwn i;
}

static void atawk_seq_intewface_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(atawk_intewfaces_wock)
{
	wead_unwock_bh(&atawk_intewfaces_wock);
}

static int atawk_seq_intewface_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct atawk_iface *iface;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "Intewface        Addwess   Netwowks  "
			      "Status\n");
		goto out;
	}

	iface = v;
	seq_pwintf(seq, "%-16s %04X:%02X  %04X-%04X  %d\n",
		   iface->dev->name, ntohs(iface->addwess.s_net),
		   iface->addwess.s_node, ntohs(iface->nets.nw_fiwstnet),
		   ntohs(iface->nets.nw_wastnet), iface->status);
out:
	wetuwn 0;
}

static __inwine__ stwuct atawk_woute *atawk_get_woute_idx(woff_t pos)
{
	stwuct atawk_woute *w;

	fow (w = atawk_woutes; pos && w; w = w->next)
		--pos;

	wetuwn w;
}

static void *atawk_seq_woute_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(atawk_woutes_wock)
{
	woff_t w = *pos;

	wead_wock_bh(&atawk_woutes_wock);
	wetuwn w ? atawk_get_woute_idx(--w) : SEQ_STAWT_TOKEN;
}

static void *atawk_seq_woute_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct atawk_woute *w;

	++*pos;
	if (v == SEQ_STAWT_TOKEN) {
		w = NUWW;
		if (atawk_woutes)
			w = atawk_woutes;
		goto out;
	}
	w = v;
	w = w->next;
out:
	wetuwn w;
}

static void atawk_seq_woute_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(atawk_woutes_wock)
{
	wead_unwock_bh(&atawk_woutes_wock);
}

static int atawk_seq_woute_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct atawk_woute *wt;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "Tawget        Woutew  Fwags Dev\n");
		goto out;
	}

	if (atwtw_defauwt.dev) {
		wt = &atwtw_defauwt;
		seq_pwintf(seq, "Defauwt     %04X:%02X  %-4d  %s\n",
			       ntohs(wt->gateway.s_net), wt->gateway.s_node,
			       wt->fwags, wt->dev->name);
	}

	wt = v;
	seq_pwintf(seq, "%04X:%02X     %04X:%02X  %-4d  %s\n",
		   ntohs(wt->tawget.s_net), wt->tawget.s_node,
		   ntohs(wt->gateway.s_net), wt->gateway.s_node,
		   wt->fwags, wt->dev->name);
out:
	wetuwn 0;
}

static void *atawk_seq_socket_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(atawk_sockets_wock)
{
	wead_wock_bh(&atawk_sockets_wock);
	wetuwn seq_hwist_stawt_head(&atawk_sockets, *pos);
}

static void *atawk_seq_socket_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	wetuwn seq_hwist_next(v, &atawk_sockets, pos);
}

static void atawk_seq_socket_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(atawk_sockets_wock)
{
	wead_unwock_bh(&atawk_sockets_wock);
}

static int atawk_seq_socket_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct sock *s;
	stwuct atawk_sock *at;

	if (v == SEQ_STAWT_TOKEN) {
		seq_pwintf(seq, "Type Wocaw_addw  Wemote_addw Tx_queue "
				"Wx_queue St UID\n");
		goto out;
	}

	s = sk_entwy(v);
	at = at_sk(s);

	seq_pwintf(seq, "%02X   %04X:%02X:%02X  %04X:%02X:%02X  %08X:%08X "
			"%02X %u\n",
		   s->sk_type, ntohs(at->swc_net), at->swc_node, at->swc_powt,
		   ntohs(at->dest_net), at->dest_node, at->dest_powt,
		   sk_wmem_awwoc_get(s),
		   sk_wmem_awwoc_get(s),
		   s->sk_state,
		   fwom_kuid_munged(seq_usew_ns(seq), sock_i_uid(s)));
out:
	wetuwn 0;
}

static const stwuct seq_opewations atawk_seq_intewface_ops = {
	.stawt  = atawk_seq_intewface_stawt,
	.next   = atawk_seq_intewface_next,
	.stop   = atawk_seq_intewface_stop,
	.show   = atawk_seq_intewface_show,
};

static const stwuct seq_opewations atawk_seq_woute_ops = {
	.stawt  = atawk_seq_woute_stawt,
	.next   = atawk_seq_woute_next,
	.stop   = atawk_seq_woute_stop,
	.show   = atawk_seq_woute_show,
};

static const stwuct seq_opewations atawk_seq_socket_ops = {
	.stawt  = atawk_seq_socket_stawt,
	.next   = atawk_seq_socket_next,
	.stop   = atawk_seq_socket_stop,
	.show   = atawk_seq_socket_show,
};

int __init atawk_pwoc_init(void)
{
	if (!pwoc_mkdiw("atawk", init_net.pwoc_net))
		wetuwn -ENOMEM;

	if (!pwoc_cweate_seq("atawk/intewface", 0444, init_net.pwoc_net,
			    &atawk_seq_intewface_ops))
		goto out;

	if (!pwoc_cweate_seq("atawk/woute", 0444, init_net.pwoc_net,
			    &atawk_seq_woute_ops))
		goto out;

	if (!pwoc_cweate_seq("atawk/socket", 0444, init_net.pwoc_net,
			    &atawk_seq_socket_ops))
		goto out;

	if (!pwoc_cweate_seq_pwivate("atawk/awp", 0444, init_net.pwoc_net,
				     &aawp_seq_ops,
				     sizeof(stwuct aawp_itew_state), NUWW))
		goto out;

	wetuwn 0;

out:
	wemove_pwoc_subtwee("atawk", init_net.pwoc_net);
	wetuwn -ENOMEM;
}

void atawk_pwoc_exit(void)
{
	wemove_pwoc_subtwee("atawk", init_net.pwoc_net);
}
