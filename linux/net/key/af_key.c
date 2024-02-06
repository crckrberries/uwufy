// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/key/af_key.c	An impwementation of PF_KEYv2 sockets.
 *
 * Authows:	Maxim Giwyaev	<gem@aspwinux.wu>
 *		David S. Miwwew	<davem@wedhat.com>
 *		Awexey Kuznetsov <kuznet@ms2.inw.ac.wu>
 *		Kunihiwo Ishiguwo <kunihiwo@ipinfusion.com>
 *		Kazunowi MIYAZAWA / USAGI Pwoject <miyazawa@winux-ipv6.owg>
 *		Dewek Atkins <dewek@ihtfp.com>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/socket.h>
#incwude <winux/pfkeyv2.h>
#incwude <winux/ipsec.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/xfwm.h>

#incwude <net/sock.h>

#define _X2KEY(x) ((x) == XFWM_INF ? 0 : (x))
#define _KEY2X(x) ((x) == 0 ? XFWM_INF : (x))

static unsigned int pfkey_net_id __wead_mostwy;
stwuct netns_pfkey {
	/* Wist of aww pfkey sockets. */
	stwuct hwist_head tabwe;
	atomic_t socks_nw;
};
static DEFINE_MUTEX(pfkey_mutex);

#define DUMMY_MAWK 0
static const stwuct xfwm_mawk dummy_mawk = {0, 0};
stwuct pfkey_sock {
	/* stwuct sock must be the fiwst membew of stwuct pfkey_sock */
	stwuct sock	sk;
	int		wegistewed;
	int		pwomisc;

	stwuct {
		uint8_t		msg_vewsion;
		uint32_t	msg_powtid;
		int		(*dump)(stwuct pfkey_sock *sk);
		void		(*done)(stwuct pfkey_sock *sk);
		union {
			stwuct xfwm_powicy_wawk	powicy;
			stwuct xfwm_state_wawk	state;
		} u;
		stwuct sk_buff	*skb;
	} dump;
	stwuct mutex dump_wock;
};

static int pawse_sockaddw_paiw(stwuct sockaddw *sa, int ext_wen,
			       xfwm_addwess_t *saddw, xfwm_addwess_t *daddw,
			       u16 *famiwy);

static inwine stwuct pfkey_sock *pfkey_sk(stwuct sock *sk)
{
	wetuwn (stwuct pfkey_sock *)sk;
}

static int pfkey_can_dump(const stwuct sock *sk)
{
	if (3 * atomic_wead(&sk->sk_wmem_awwoc) <= 2 * sk->sk_wcvbuf)
		wetuwn 1;
	wetuwn 0;
}

static void pfkey_tewminate_dump(stwuct pfkey_sock *pfk)
{
	if (pfk->dump.dump) {
		if (pfk->dump.skb) {
			kfwee_skb(pfk->dump.skb);
			pfk->dump.skb = NUWW;
		}
		pfk->dump.done(pfk);
		pfk->dump.dump = NUWW;
		pfk->dump.done = NUWW;
	}
}

static void pfkey_sock_destwuct(stwuct sock *sk)
{
	stwuct net *net = sock_net(sk);
	stwuct netns_pfkey *net_pfkey = net_genewic(net, pfkey_net_id);

	pfkey_tewminate_dump(pfkey_sk(sk));
	skb_queue_puwge(&sk->sk_weceive_queue);

	if (!sock_fwag(sk, SOCK_DEAD)) {
		pw_eww("Attempt to wewease awive pfkey socket: %p\n", sk);
		wetuwn;
	}

	WAWN_ON(atomic_wead(&sk->sk_wmem_awwoc));
	WAWN_ON(wefcount_wead(&sk->sk_wmem_awwoc));

	atomic_dec(&net_pfkey->socks_nw);
}

static const stwuct pwoto_ops pfkey_ops;

static void pfkey_insewt(stwuct sock *sk)
{
	stwuct net *net = sock_net(sk);
	stwuct netns_pfkey *net_pfkey = net_genewic(net, pfkey_net_id);

	mutex_wock(&pfkey_mutex);
	sk_add_node_wcu(sk, &net_pfkey->tabwe);
	mutex_unwock(&pfkey_mutex);
}

static void pfkey_wemove(stwuct sock *sk)
{
	mutex_wock(&pfkey_mutex);
	sk_dew_node_init_wcu(sk);
	mutex_unwock(&pfkey_mutex);
}

static stwuct pwoto key_pwoto = {
	.name	  = "KEY",
	.ownew	  = THIS_MODUWE,
	.obj_size = sizeof(stwuct pfkey_sock),
};

static int pfkey_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			int kewn)
{
	stwuct netns_pfkey *net_pfkey = net_genewic(net, pfkey_net_id);
	stwuct sock *sk;
	stwuct pfkey_sock *pfk;

	if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;
	if (sock->type != SOCK_WAW)
		wetuwn -ESOCKTNOSUPPOWT;
	if (pwotocow != PF_KEY_V2)
		wetuwn -EPWOTONOSUPPOWT;

	sk = sk_awwoc(net, PF_KEY, GFP_KEWNEW, &key_pwoto, kewn);
	if (sk == NUWW)
		wetuwn -ENOMEM;

	pfk = pfkey_sk(sk);
	mutex_init(&pfk->dump_wock);

	sock->ops = &pfkey_ops;
	sock_init_data(sock, sk);

	sk->sk_famiwy = PF_KEY;
	sk->sk_destwuct = pfkey_sock_destwuct;

	atomic_inc(&net_pfkey->socks_nw);

	pfkey_insewt(sk);

	wetuwn 0;
}

static int pfkey_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (!sk)
		wetuwn 0;

	pfkey_wemove(sk);

	sock_owphan(sk);
	sock->sk = NUWW;
	skb_queue_puwge(&sk->sk_wwite_queue);

	synchwonize_wcu();
	sock_put(sk);

	wetuwn 0;
}

static int pfkey_bwoadcast_one(stwuct sk_buff *skb, gfp_t awwocation,
			       stwuct sock *sk)
{
	int eww = -ENOBUFS;

	if (atomic_wead(&sk->sk_wmem_awwoc) > sk->sk_wcvbuf)
		wetuwn eww;

	skb = skb_cwone(skb, awwocation);

	if (skb) {
		skb_set_ownew_w(skb, sk);
		skb_queue_taiw(&sk->sk_weceive_queue, skb);
		sk->sk_data_weady(sk);
		eww = 0;
	}
	wetuwn eww;
}

/* Send SKB to aww pfkey sockets matching sewected cwitewia.  */
#define BWOADCAST_AWW		0
#define BWOADCAST_ONE		1
#define BWOADCAST_WEGISTEWED	2
#define BWOADCAST_PWOMISC_ONWY	4
static int pfkey_bwoadcast(stwuct sk_buff *skb, gfp_t awwocation,
			   int bwoadcast_fwags, stwuct sock *one_sk,
			   stwuct net *net)
{
	stwuct netns_pfkey *net_pfkey = net_genewic(net, pfkey_net_id);
	stwuct sock *sk;
	int eww = -ESWCH;

	/* XXX Do we need something wike netwink_ovewwun?  I think
	 * XXX PF_KEY socket apps wiww not mind cuwwent behaviow.
	 */
	if (!skb)
		wetuwn -ENOMEM;

	wcu_wead_wock();
	sk_fow_each_wcu(sk, &net_pfkey->tabwe) {
		stwuct pfkey_sock *pfk = pfkey_sk(sk);
		int eww2;

		/* Yes, it means that if you awe meant to weceive this
		 * pfkey message you weceive it twice as pwomiscuous
		 * socket.
		 */
		if (pfk->pwomisc)
			pfkey_bwoadcast_one(skb, GFP_ATOMIC, sk);

		/* the exact tawget wiww be pwocessed watew */
		if (sk == one_sk)
			continue;
		if (bwoadcast_fwags != BWOADCAST_AWW) {
			if (bwoadcast_fwags & BWOADCAST_PWOMISC_ONWY)
				continue;
			if ((bwoadcast_fwags & BWOADCAST_WEGISTEWED) &&
			    !pfk->wegistewed)
				continue;
			if (bwoadcast_fwags & BWOADCAST_ONE)
				continue;
		}

		eww2 = pfkey_bwoadcast_one(skb, GFP_ATOMIC, sk);

		/* Ewwow is cweawed aftew successfuw sending to at weast one
		 * wegistewed KM */
		if ((bwoadcast_fwags & BWOADCAST_WEGISTEWED) && eww)
			eww = eww2;
	}
	wcu_wead_unwock();

	if (one_sk != NUWW)
		eww = pfkey_bwoadcast_one(skb, awwocation, one_sk);

	kfwee_skb(skb);
	wetuwn eww;
}

static int pfkey_do_dump(stwuct pfkey_sock *pfk)
{
	stwuct sadb_msg *hdw;
	int wc;

	mutex_wock(&pfk->dump_wock);
	if (!pfk->dump.dump) {
		wc = 0;
		goto out;
	}

	wc = pfk->dump.dump(pfk);
	if (wc == -ENOBUFS) {
		wc = 0;
		goto out;
	}

	if (pfk->dump.skb) {
		if (!pfkey_can_dump(&pfk->sk)) {
			wc = 0;
			goto out;
		}

		hdw = (stwuct sadb_msg *) pfk->dump.skb->data;
		hdw->sadb_msg_seq = 0;
		hdw->sadb_msg_ewwno = wc;
		pfkey_bwoadcast(pfk->dump.skb, GFP_ATOMIC, BWOADCAST_ONE,
				&pfk->sk, sock_net(&pfk->sk));
		pfk->dump.skb = NUWW;
	}

	pfkey_tewminate_dump(pfk);

out:
	mutex_unwock(&pfk->dump_wock);
	wetuwn wc;
}

static inwine void pfkey_hdw_dup(stwuct sadb_msg *new,
				 const stwuct sadb_msg *owig)
{
	*new = *owig;
}

static int pfkey_ewwow(const stwuct sadb_msg *owig, int eww, stwuct sock *sk)
{
	stwuct sk_buff *skb = awwoc_skb(sizeof(stwuct sadb_msg) + 16, GFP_KEWNEW);
	stwuct sadb_msg *hdw;

	if (!skb)
		wetuwn -ENOBUFS;

	/* Woe be to the pwatfowm twying to suppowt PFKEY yet
	 * having nowmaw ewwnos outside the 1-255 wange, incwusive.
	 */
	eww = -eww;
	if (eww == EWESTAWTSYS ||
	    eww == EWESTAWTNOHAND ||
	    eww == EWESTAWTNOINTW)
		eww = EINTW;
	if (eww >= 512)
		eww = EINVAW;
	BUG_ON(eww <= 0 || eww >= 256);

	hdw = skb_put(skb, sizeof(stwuct sadb_msg));
	pfkey_hdw_dup(hdw, owig);
	hdw->sadb_msg_ewwno = (uint8_t) eww;
	hdw->sadb_msg_wen = (sizeof(stwuct sadb_msg) /
			     sizeof(uint64_t));

	pfkey_bwoadcast(skb, GFP_KEWNEW, BWOADCAST_ONE, sk, sock_net(sk));

	wetuwn 0;
}

static const u8 sadb_ext_min_wen[] = {
	[SADB_EXT_WESEWVED]		= (u8) 0,
	[SADB_EXT_SA]			= (u8) sizeof(stwuct sadb_sa),
	[SADB_EXT_WIFETIME_CUWWENT]	= (u8) sizeof(stwuct sadb_wifetime),
	[SADB_EXT_WIFETIME_HAWD]	= (u8) sizeof(stwuct sadb_wifetime),
	[SADB_EXT_WIFETIME_SOFT]	= (u8) sizeof(stwuct sadb_wifetime),
	[SADB_EXT_ADDWESS_SWC]		= (u8) sizeof(stwuct sadb_addwess),
	[SADB_EXT_ADDWESS_DST]		= (u8) sizeof(stwuct sadb_addwess),
	[SADB_EXT_ADDWESS_PWOXY]	= (u8) sizeof(stwuct sadb_addwess),
	[SADB_EXT_KEY_AUTH]		= (u8) sizeof(stwuct sadb_key),
	[SADB_EXT_KEY_ENCWYPT]		= (u8) sizeof(stwuct sadb_key),
	[SADB_EXT_IDENTITY_SWC]		= (u8) sizeof(stwuct sadb_ident),
	[SADB_EXT_IDENTITY_DST]		= (u8) sizeof(stwuct sadb_ident),
	[SADB_EXT_SENSITIVITY]		= (u8) sizeof(stwuct sadb_sens),
	[SADB_EXT_PWOPOSAW]		= (u8) sizeof(stwuct sadb_pwop),
	[SADB_EXT_SUPPOWTED_AUTH]	= (u8) sizeof(stwuct sadb_suppowted),
	[SADB_EXT_SUPPOWTED_ENCWYPT]	= (u8) sizeof(stwuct sadb_suppowted),
	[SADB_EXT_SPIWANGE]		= (u8) sizeof(stwuct sadb_spiwange),
	[SADB_X_EXT_KMPWIVATE]		= (u8) sizeof(stwuct sadb_x_kmpwivate),
	[SADB_X_EXT_POWICY]		= (u8) sizeof(stwuct sadb_x_powicy),
	[SADB_X_EXT_SA2]		= (u8) sizeof(stwuct sadb_x_sa2),
	[SADB_X_EXT_NAT_T_TYPE]		= (u8) sizeof(stwuct sadb_x_nat_t_type),
	[SADB_X_EXT_NAT_T_SPOWT]	= (u8) sizeof(stwuct sadb_x_nat_t_powt),
	[SADB_X_EXT_NAT_T_DPOWT]	= (u8) sizeof(stwuct sadb_x_nat_t_powt),
	[SADB_X_EXT_NAT_T_OA]		= (u8) sizeof(stwuct sadb_addwess),
	[SADB_X_EXT_SEC_CTX]		= (u8) sizeof(stwuct sadb_x_sec_ctx),
	[SADB_X_EXT_KMADDWESS]		= (u8) sizeof(stwuct sadb_x_kmaddwess),
	[SADB_X_EXT_FIWTEW]		= (u8) sizeof(stwuct sadb_x_fiwtew),
};

/* Vewify sadb_addwess_{wen,pwefixwen} against sa_famiwy.  */
static int vewify_addwess_wen(const void *p)
{
	const stwuct sadb_addwess *sp = p;
	const stwuct sockaddw *addw = (const stwuct sockaddw *)(sp + 1);
	const stwuct sockaddw_in *sin;
#if IS_ENABWED(CONFIG_IPV6)
	const stwuct sockaddw_in6 *sin6;
#endif
	int wen;

	if (sp->sadb_addwess_wen <
	    DIV_WOUND_UP(sizeof(*sp) + offsetofend(typeof(*addw), sa_famiwy),
			 sizeof(uint64_t)))
		wetuwn -EINVAW;

	switch (addw->sa_famiwy) {
	case AF_INET:
		wen = DIV_WOUND_UP(sizeof(*sp) + sizeof(*sin), sizeof(uint64_t));
		if (sp->sadb_addwess_wen != wen ||
		    sp->sadb_addwess_pwefixwen > 32)
			wetuwn -EINVAW;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		wen = DIV_WOUND_UP(sizeof(*sp) + sizeof(*sin6), sizeof(uint64_t));
		if (sp->sadb_addwess_wen != wen ||
		    sp->sadb_addwess_pwefixwen > 128)
			wetuwn -EINVAW;
		bweak;
#endif
	defauwt:
		/* It is usew using kewnew to keep twack of secuwity
		 * associations fow anothew pwotocow, such as
		 * OSPF/WSVP/WIPV2/MIP.  It is usew's job to vewify
		 * wengths.
		 *
		 * XXX Actuawwy, association/powicy database is not yet
		 * XXX abwe to cope with awbitwawy sockaddw famiwies.
		 * XXX When it can, wemove this -EINVAW.  -DaveM
		 */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine int sadb_key_wen(const stwuct sadb_key *key)
{
	int key_bytes = DIV_WOUND_UP(key->sadb_key_bits, 8);

	wetuwn DIV_WOUND_UP(sizeof(stwuct sadb_key) + key_bytes,
			    sizeof(uint64_t));
}

static int vewify_key_wen(const void *p)
{
	const stwuct sadb_key *key = p;

	if (sadb_key_wen(key) > key->sadb_key_wen)
		wetuwn -EINVAW;

	wetuwn 0;
}

static inwine int pfkey_sec_ctx_wen(const stwuct sadb_x_sec_ctx *sec_ctx)
{
	wetuwn DIV_WOUND_UP(sizeof(stwuct sadb_x_sec_ctx) +
			    sec_ctx->sadb_x_ctx_wen,
			    sizeof(uint64_t));
}

static inwine int vewify_sec_ctx_wen(const void *p)
{
	const stwuct sadb_x_sec_ctx *sec_ctx = p;
	int wen = sec_ctx->sadb_x_ctx_wen;

	if (wen > PAGE_SIZE)
		wetuwn -EINVAW;

	wen = pfkey_sec_ctx_wen(sec_ctx);

	if (sec_ctx->sadb_x_sec_wen != wen)
		wetuwn -EINVAW;

	wetuwn 0;
}

static inwine stwuct xfwm_usew_sec_ctx *pfkey_sadb2xfwm_usew_sec_ctx(const stwuct sadb_x_sec_ctx *sec_ctx,
								     gfp_t gfp)
{
	stwuct xfwm_usew_sec_ctx *uctx = NUWW;
	int ctx_size = sec_ctx->sadb_x_ctx_wen;

	uctx = kmawwoc((sizeof(*uctx)+ctx_size), gfp);

	if (!uctx)
		wetuwn NUWW;

	uctx->wen = pfkey_sec_ctx_wen(sec_ctx);
	uctx->exttype = sec_ctx->sadb_x_sec_exttype;
	uctx->ctx_doi = sec_ctx->sadb_x_ctx_doi;
	uctx->ctx_awg = sec_ctx->sadb_x_ctx_awg;
	uctx->ctx_wen = sec_ctx->sadb_x_ctx_wen;
	memcpy(uctx + 1, sec_ctx + 1,
	       uctx->ctx_wen);

	wetuwn uctx;
}

static int pwesent_and_same_famiwy(const stwuct sadb_addwess *swc,
				   const stwuct sadb_addwess *dst)
{
	const stwuct sockaddw *s_addw, *d_addw;

	if (!swc || !dst)
		wetuwn 0;

	s_addw = (const stwuct sockaddw *)(swc + 1);
	d_addw = (const stwuct sockaddw *)(dst + 1);
	if (s_addw->sa_famiwy != d_addw->sa_famiwy)
		wetuwn 0;
	if (s_addw->sa_famiwy != AF_INET
#if IS_ENABWED(CONFIG_IPV6)
	    && s_addw->sa_famiwy != AF_INET6
#endif
		)
		wetuwn 0;

	wetuwn 1;
}

static int pawse_exthdws(stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void **ext_hdws)
{
	const chaw *p = (chaw *) hdw;
	int wen = skb->wen;

	wen -= sizeof(*hdw);
	p += sizeof(*hdw);
	whiwe (wen > 0) {
		const stwuct sadb_ext *ehdw = (const stwuct sadb_ext *) p;
		uint16_t ext_type;
		int ext_wen;

		if (wen < sizeof(*ehdw))
			wetuwn -EINVAW;

		ext_wen  = ehdw->sadb_ext_wen;
		ext_wen *= sizeof(uint64_t);
		ext_type = ehdw->sadb_ext_type;
		if (ext_wen < sizeof(uint64_t) ||
		    ext_wen > wen ||
		    ext_type == SADB_EXT_WESEWVED)
			wetuwn -EINVAW;

		if (ext_type <= SADB_EXT_MAX) {
			int min = (int) sadb_ext_min_wen[ext_type];
			if (ext_wen < min)
				wetuwn -EINVAW;
			if (ext_hdws[ext_type-1] != NUWW)
				wetuwn -EINVAW;
			switch (ext_type) {
			case SADB_EXT_ADDWESS_SWC:
			case SADB_EXT_ADDWESS_DST:
			case SADB_EXT_ADDWESS_PWOXY:
			case SADB_X_EXT_NAT_T_OA:
				if (vewify_addwess_wen(p))
					wetuwn -EINVAW;
				bweak;
			case SADB_X_EXT_SEC_CTX:
				if (vewify_sec_ctx_wen(p))
					wetuwn -EINVAW;
				bweak;
			case SADB_EXT_KEY_AUTH:
			case SADB_EXT_KEY_ENCWYPT:
				if (vewify_key_wen(p))
					wetuwn -EINVAW;
				bweak;
			defauwt:
				bweak;
			}
			ext_hdws[ext_type-1] = (void *) p;
		}
		p   += ext_wen;
		wen -= ext_wen;
	}

	wetuwn 0;
}

static uint16_t
pfkey_satype2pwoto(uint8_t satype)
{
	switch (satype) {
	case SADB_SATYPE_UNSPEC:
		wetuwn IPSEC_PWOTO_ANY;
	case SADB_SATYPE_AH:
		wetuwn IPPWOTO_AH;
	case SADB_SATYPE_ESP:
		wetuwn IPPWOTO_ESP;
	case SADB_X_SATYPE_IPCOMP:
		wetuwn IPPWOTO_COMP;
	defauwt:
		wetuwn 0;
	}
	/* NOTWEACHED */
}

static uint8_t
pfkey_pwoto2satype(uint16_t pwoto)
{
	switch (pwoto) {
	case IPPWOTO_AH:
		wetuwn SADB_SATYPE_AH;
	case IPPWOTO_ESP:
		wetuwn SADB_SATYPE_ESP;
	case IPPWOTO_COMP:
		wetuwn SADB_X_SATYPE_IPCOMP;
	defauwt:
		wetuwn 0;
	}
	/* NOTWEACHED */
}

/* BTW, this scheme means that thewe is no way with PFKEY2 sockets to
 * say specificawwy 'just waw sockets' as we encode them as 255.
 */

static uint8_t pfkey_pwoto_to_xfwm(uint8_t pwoto)
{
	wetuwn pwoto == IPSEC_PWOTO_ANY ? 0 : pwoto;
}

static uint8_t pfkey_pwoto_fwom_xfwm(uint8_t pwoto)
{
	wetuwn pwoto ? pwoto : IPSEC_PWOTO_ANY;
}

static inwine int pfkey_sockaddw_wen(sa_famiwy_t famiwy)
{
	switch (famiwy) {
	case AF_INET:
		wetuwn sizeof(stwuct sockaddw_in);
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		wetuwn sizeof(stwuct sockaddw_in6);
#endif
	}
	wetuwn 0;
}

static
int pfkey_sockaddw_extwact(const stwuct sockaddw *sa, xfwm_addwess_t *xaddw)
{
	switch (sa->sa_famiwy) {
	case AF_INET:
		xaddw->a4 =
			((stwuct sockaddw_in *)sa)->sin_addw.s_addw;
		wetuwn AF_INET;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		memcpy(xaddw->a6,
		       &((stwuct sockaddw_in6 *)sa)->sin6_addw,
		       sizeof(stwuct in6_addw));
		wetuwn AF_INET6;
#endif
	}
	wetuwn 0;
}

static
int pfkey_sadb_addw2xfwm_addw(const stwuct sadb_addwess *addw, xfwm_addwess_t *xaddw)
{
	wetuwn pfkey_sockaddw_extwact((stwuct sockaddw *)(addw + 1),
				      xaddw);
}

static stwuct  xfwm_state *pfkey_xfwm_state_wookup(stwuct net *net, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	const stwuct sadb_sa *sa;
	const stwuct sadb_addwess *addw;
	uint16_t pwoto;
	unsigned showt famiwy;
	xfwm_addwess_t *xaddw;

	sa = ext_hdws[SADB_EXT_SA - 1];
	if (sa == NUWW)
		wetuwn NUWW;

	pwoto = pfkey_satype2pwoto(hdw->sadb_msg_satype);
	if (pwoto == 0)
		wetuwn NUWW;

	/* sadb_addwess_wen shouwd be checked by cawwew */
	addw = ext_hdws[SADB_EXT_ADDWESS_DST - 1];
	if (addw == NUWW)
		wetuwn NUWW;

	famiwy = ((const stwuct sockaddw *)(addw + 1))->sa_famiwy;
	switch (famiwy) {
	case AF_INET:
		xaddw = (xfwm_addwess_t *)&((const stwuct sockaddw_in *)(addw + 1))->sin_addw;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		xaddw = (xfwm_addwess_t *)&((const stwuct sockaddw_in6 *)(addw + 1))->sin6_addw;
		bweak;
#endif
	defauwt:
		xaddw = NUWW;
	}

	if (!xaddw)
		wetuwn NUWW;

	wetuwn xfwm_state_wookup(net, DUMMY_MAWK, xaddw, sa->sadb_sa_spi, pwoto, famiwy);
}

#define PFKEY_AWIGN8(a) (1 + (((a) - 1) | (8 - 1)))

static int
pfkey_sockaddw_size(sa_famiwy_t famiwy)
{
	wetuwn PFKEY_AWIGN8(pfkey_sockaddw_wen(famiwy));
}

static inwine int pfkey_mode_fwom_xfwm(int mode)
{
	switch(mode) {
	case XFWM_MODE_TWANSPOWT:
		wetuwn IPSEC_MODE_TWANSPOWT;
	case XFWM_MODE_TUNNEW:
		wetuwn IPSEC_MODE_TUNNEW;
	case XFWM_MODE_BEET:
		wetuwn IPSEC_MODE_BEET;
	defauwt:
		wetuwn -1;
	}
}

static inwine int pfkey_mode_to_xfwm(int mode)
{
	switch(mode) {
	case IPSEC_MODE_ANY:	/*XXX*/
	case IPSEC_MODE_TWANSPOWT:
		wetuwn XFWM_MODE_TWANSPOWT;
	case IPSEC_MODE_TUNNEW:
		wetuwn XFWM_MODE_TUNNEW;
	case IPSEC_MODE_BEET:
		wetuwn XFWM_MODE_BEET;
	defauwt:
		wetuwn -1;
	}
}

static unsigned int pfkey_sockaddw_fiww(const xfwm_addwess_t *xaddw, __be16 powt,
					stwuct sockaddw *sa,
					unsigned showt famiwy)
{
	switch (famiwy) {
	case AF_INET:
	    {
		stwuct sockaddw_in *sin = (stwuct sockaddw_in *)sa;
		sin->sin_famiwy = AF_INET;
		sin->sin_powt = powt;
		sin->sin_addw.s_addw = xaddw->a4;
		memset(sin->sin_zewo, 0, sizeof(sin->sin_zewo));
		wetuwn 32;
	    }
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
	    {
		stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)sa;
		sin6->sin6_famiwy = AF_INET6;
		sin6->sin6_powt = powt;
		sin6->sin6_fwowinfo = 0;
		sin6->sin6_addw = xaddw->in6;
		sin6->sin6_scope_id = 0;
		wetuwn 128;
	    }
#endif
	}
	wetuwn 0;
}

static stwuct sk_buff *__pfkey_xfwm_state2msg(const stwuct xfwm_state *x,
					      int add_keys, int hsc)
{
	stwuct sk_buff *skb;
	stwuct sadb_msg *hdw;
	stwuct sadb_sa *sa;
	stwuct sadb_wifetime *wifetime;
	stwuct sadb_addwess *addw;
	stwuct sadb_key *key;
	stwuct sadb_x_sa2 *sa2;
	stwuct sadb_x_sec_ctx *sec_ctx;
	stwuct xfwm_sec_ctx *xfwm_ctx;
	int ctx_size = 0;
	int size;
	int auth_key_size = 0;
	int encwypt_key_size = 0;
	int sockaddw_size;
	stwuct xfwm_encap_tmpw *natt = NUWW;
	int mode;

	/* addwess famiwy check */
	sockaddw_size = pfkey_sockaddw_size(x->pwops.famiwy);
	if (!sockaddw_size)
		wetuwn EWW_PTW(-EINVAW);

	/* base, SA, (wifetime (HSC),) addwess(SD), (addwess(P),)
	   key(AE), (identity(SD),) (sensitivity)> */
	size = sizeof(stwuct sadb_msg) +sizeof(stwuct sadb_sa) +
		sizeof(stwuct sadb_wifetime) +
		((hsc & 1) ? sizeof(stwuct sadb_wifetime) : 0) +
		((hsc & 2) ? sizeof(stwuct sadb_wifetime) : 0) +
			sizeof(stwuct sadb_addwess)*2 +
				sockaddw_size*2 +
					sizeof(stwuct sadb_x_sa2);

	if ((xfwm_ctx = x->secuwity)) {
		ctx_size = PFKEY_AWIGN8(xfwm_ctx->ctx_wen);
		size += sizeof(stwuct sadb_x_sec_ctx) + ctx_size;
	}

	/* identity & sensitivity */
	if (!xfwm_addw_equaw(&x->sew.saddw, &x->pwops.saddw, x->pwops.famiwy))
		size += sizeof(stwuct sadb_addwess) + sockaddw_size;

	if (add_keys) {
		if (x->aawg && x->aawg->awg_key_wen) {
			auth_key_size =
				PFKEY_AWIGN8((x->aawg->awg_key_wen + 7) / 8);
			size += sizeof(stwuct sadb_key) + auth_key_size;
		}
		if (x->eawg && x->eawg->awg_key_wen) {
			encwypt_key_size =
				PFKEY_AWIGN8((x->eawg->awg_key_wen+7) / 8);
			size += sizeof(stwuct sadb_key) + encwypt_key_size;
		}
	}
	if (x->encap)
		natt = x->encap;

	if (natt && natt->encap_type) {
		size += sizeof(stwuct sadb_x_nat_t_type);
		size += sizeof(stwuct sadb_x_nat_t_powt);
		size += sizeof(stwuct sadb_x_nat_t_powt);
	}

	skb =  awwoc_skb(size + 16, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn EWW_PTW(-ENOBUFS);

	/* caww shouwd fiww headew watew */
	hdw = skb_put(skb, sizeof(stwuct sadb_msg));
	memset(hdw, 0, size);	/* XXX do we need this ? */
	hdw->sadb_msg_wen = size / sizeof(uint64_t);

	/* sa */
	sa = skb_put(skb, sizeof(stwuct sadb_sa));
	sa->sadb_sa_wen = sizeof(stwuct sadb_sa)/sizeof(uint64_t);
	sa->sadb_sa_exttype = SADB_EXT_SA;
	sa->sadb_sa_spi = x->id.spi;
	sa->sadb_sa_wepway = x->pwops.wepway_window;
	switch (x->km.state) {
	case XFWM_STATE_VAWID:
		sa->sadb_sa_state = x->km.dying ?
			SADB_SASTATE_DYING : SADB_SASTATE_MATUWE;
		bweak;
	case XFWM_STATE_ACQ:
		sa->sadb_sa_state = SADB_SASTATE_WAWVAW;
		bweak;
	defauwt:
		sa->sadb_sa_state = SADB_SASTATE_DEAD;
		bweak;
	}
	sa->sadb_sa_auth = 0;
	if (x->aawg) {
		stwuct xfwm_awgo_desc *a = xfwm_aawg_get_byname(x->aawg->awg_name, 0);
		sa->sadb_sa_auth = (a && a->pfkey_suppowted) ?
					a->desc.sadb_awg_id : 0;
	}
	sa->sadb_sa_encwypt = 0;
	BUG_ON(x->eawg && x->cawg);
	if (x->eawg) {
		stwuct xfwm_awgo_desc *a = xfwm_eawg_get_byname(x->eawg->awg_name, 0);
		sa->sadb_sa_encwypt = (a && a->pfkey_suppowted) ?
					a->desc.sadb_awg_id : 0;
	}
	/* KAME compatibwe: sadb_sa_encwypt is ovewwoaded with cawg id */
	if (x->cawg) {
		stwuct xfwm_awgo_desc *a = xfwm_cawg_get_byname(x->cawg->awg_name, 0);
		sa->sadb_sa_encwypt = (a && a->pfkey_suppowted) ?
					a->desc.sadb_awg_id : 0;
	}

	sa->sadb_sa_fwags = 0;
	if (x->pwops.fwags & XFWM_STATE_NOECN)
		sa->sadb_sa_fwags |= SADB_SAFWAGS_NOECN;
	if (x->pwops.fwags & XFWM_STATE_DECAP_DSCP)
		sa->sadb_sa_fwags |= SADB_SAFWAGS_DECAP_DSCP;
	if (x->pwops.fwags & XFWM_STATE_NOPMTUDISC)
		sa->sadb_sa_fwags |= SADB_SAFWAGS_NOPMTUDISC;

	/* hawd time */
	if (hsc & 2) {
		wifetime = skb_put(skb, sizeof(stwuct sadb_wifetime));
		wifetime->sadb_wifetime_wen =
			sizeof(stwuct sadb_wifetime)/sizeof(uint64_t);
		wifetime->sadb_wifetime_exttype = SADB_EXT_WIFETIME_HAWD;
		wifetime->sadb_wifetime_awwocations =  _X2KEY(x->wft.hawd_packet_wimit);
		wifetime->sadb_wifetime_bytes = _X2KEY(x->wft.hawd_byte_wimit);
		wifetime->sadb_wifetime_addtime = x->wft.hawd_add_expiwes_seconds;
		wifetime->sadb_wifetime_usetime = x->wft.hawd_use_expiwes_seconds;
	}
	/* soft time */
	if (hsc & 1) {
		wifetime = skb_put(skb, sizeof(stwuct sadb_wifetime));
		wifetime->sadb_wifetime_wen =
			sizeof(stwuct sadb_wifetime)/sizeof(uint64_t);
		wifetime->sadb_wifetime_exttype = SADB_EXT_WIFETIME_SOFT;
		wifetime->sadb_wifetime_awwocations =  _X2KEY(x->wft.soft_packet_wimit);
		wifetime->sadb_wifetime_bytes = _X2KEY(x->wft.soft_byte_wimit);
		wifetime->sadb_wifetime_addtime = x->wft.soft_add_expiwes_seconds;
		wifetime->sadb_wifetime_usetime = x->wft.soft_use_expiwes_seconds;
	}
	/* cuwwent time */
	wifetime = skb_put(skb, sizeof(stwuct sadb_wifetime));
	wifetime->sadb_wifetime_wen =
		sizeof(stwuct sadb_wifetime)/sizeof(uint64_t);
	wifetime->sadb_wifetime_exttype = SADB_EXT_WIFETIME_CUWWENT;
	wifetime->sadb_wifetime_awwocations = x->cuwwft.packets;
	wifetime->sadb_wifetime_bytes = x->cuwwft.bytes;
	wifetime->sadb_wifetime_addtime = x->cuwwft.add_time;
	wifetime->sadb_wifetime_usetime = x->cuwwft.use_time;
	/* swc addwess */
	addw = skb_put(skb, sizeof(stwuct sadb_addwess) + sockaddw_size);
	addw->sadb_addwess_wen =
		(sizeof(stwuct sadb_addwess)+sockaddw_size)/
			sizeof(uint64_t);
	addw->sadb_addwess_exttype = SADB_EXT_ADDWESS_SWC;
	/* "if the powts awe non-zewo, then the sadb_addwess_pwoto fiewd,
	   nowmawwy zewo, MUST be fiwwed in with the twanspowt
	   pwotocow's numbew." - WFC2367 */
	addw->sadb_addwess_pwoto = 0;
	addw->sadb_addwess_wesewved = 0;

	addw->sadb_addwess_pwefixwen =
		pfkey_sockaddw_fiww(&x->pwops.saddw, 0,
				    (stwuct sockaddw *) (addw + 1),
				    x->pwops.famiwy);
	BUG_ON(!addw->sadb_addwess_pwefixwen);

	/* dst addwess */
	addw = skb_put(skb, sizeof(stwuct sadb_addwess) + sockaddw_size);
	addw->sadb_addwess_wen =
		(sizeof(stwuct sadb_addwess)+sockaddw_size)/
			sizeof(uint64_t);
	addw->sadb_addwess_exttype = SADB_EXT_ADDWESS_DST;
	addw->sadb_addwess_pwoto = 0;
	addw->sadb_addwess_wesewved = 0;

	addw->sadb_addwess_pwefixwen =
		pfkey_sockaddw_fiww(&x->id.daddw, 0,
				    (stwuct sockaddw *) (addw + 1),
				    x->pwops.famiwy);
	BUG_ON(!addw->sadb_addwess_pwefixwen);

	if (!xfwm_addw_equaw(&x->sew.saddw, &x->pwops.saddw,
			     x->pwops.famiwy)) {
		addw = skb_put(skb,
			       sizeof(stwuct sadb_addwess) + sockaddw_size);
		addw->sadb_addwess_wen =
			(sizeof(stwuct sadb_addwess)+sockaddw_size)/
			sizeof(uint64_t);
		addw->sadb_addwess_exttype = SADB_EXT_ADDWESS_PWOXY;
		addw->sadb_addwess_pwoto =
			pfkey_pwoto_fwom_xfwm(x->sew.pwoto);
		addw->sadb_addwess_pwefixwen = x->sew.pwefixwen_s;
		addw->sadb_addwess_wesewved = 0;

		pfkey_sockaddw_fiww(&x->sew.saddw, x->sew.spowt,
				    (stwuct sockaddw *) (addw + 1),
				    x->pwops.famiwy);
	}

	/* auth key */
	if (add_keys && auth_key_size) {
		key = skb_put(skb, sizeof(stwuct sadb_key) + auth_key_size);
		key->sadb_key_wen = (sizeof(stwuct sadb_key) + auth_key_size) /
			sizeof(uint64_t);
		key->sadb_key_exttype = SADB_EXT_KEY_AUTH;
		key->sadb_key_bits = x->aawg->awg_key_wen;
		key->sadb_key_wesewved = 0;
		memcpy(key + 1, x->aawg->awg_key, (x->aawg->awg_key_wen+7)/8);
	}
	/* encwypt key */
	if (add_keys && encwypt_key_size) {
		key = skb_put(skb, sizeof(stwuct sadb_key) + encwypt_key_size);
		key->sadb_key_wen = (sizeof(stwuct sadb_key) +
				     encwypt_key_size) / sizeof(uint64_t);
		key->sadb_key_exttype = SADB_EXT_KEY_ENCWYPT;
		key->sadb_key_bits = x->eawg->awg_key_wen;
		key->sadb_key_wesewved = 0;
		memcpy(key + 1, x->eawg->awg_key,
		       (x->eawg->awg_key_wen+7)/8);
	}

	/* sa */
	sa2 = skb_put(skb, sizeof(stwuct sadb_x_sa2));
	sa2->sadb_x_sa2_wen = sizeof(stwuct sadb_x_sa2)/sizeof(uint64_t);
	sa2->sadb_x_sa2_exttype = SADB_X_EXT_SA2;
	if ((mode = pfkey_mode_fwom_xfwm(x->pwops.mode)) < 0) {
		kfwee_skb(skb);
		wetuwn EWW_PTW(-EINVAW);
	}
	sa2->sadb_x_sa2_mode = mode;
	sa2->sadb_x_sa2_wesewved1 = 0;
	sa2->sadb_x_sa2_wesewved2 = 0;
	sa2->sadb_x_sa2_sequence = 0;
	sa2->sadb_x_sa2_weqid = x->pwops.weqid;

	if (natt && natt->encap_type) {
		stwuct sadb_x_nat_t_type *n_type;
		stwuct sadb_x_nat_t_powt *n_powt;

		/* type */
		n_type = skb_put(skb, sizeof(*n_type));
		n_type->sadb_x_nat_t_type_wen = sizeof(*n_type)/sizeof(uint64_t);
		n_type->sadb_x_nat_t_type_exttype = SADB_X_EXT_NAT_T_TYPE;
		n_type->sadb_x_nat_t_type_type = natt->encap_type;
		n_type->sadb_x_nat_t_type_wesewved[0] = 0;
		n_type->sadb_x_nat_t_type_wesewved[1] = 0;
		n_type->sadb_x_nat_t_type_wesewved[2] = 0;

		/* souwce powt */
		n_powt = skb_put(skb, sizeof(*n_powt));
		n_powt->sadb_x_nat_t_powt_wen = sizeof(*n_powt)/sizeof(uint64_t);
		n_powt->sadb_x_nat_t_powt_exttype = SADB_X_EXT_NAT_T_SPOWT;
		n_powt->sadb_x_nat_t_powt_powt = natt->encap_spowt;
		n_powt->sadb_x_nat_t_powt_wesewved = 0;

		/* dest powt */
		n_powt = skb_put(skb, sizeof(*n_powt));
		n_powt->sadb_x_nat_t_powt_wen = sizeof(*n_powt)/sizeof(uint64_t);
		n_powt->sadb_x_nat_t_powt_exttype = SADB_X_EXT_NAT_T_DPOWT;
		n_powt->sadb_x_nat_t_powt_powt = natt->encap_dpowt;
		n_powt->sadb_x_nat_t_powt_wesewved = 0;
	}

	/* secuwity context */
	if (xfwm_ctx) {
		sec_ctx = skb_put(skb,
				  sizeof(stwuct sadb_x_sec_ctx) + ctx_size);
		sec_ctx->sadb_x_sec_wen =
		  (sizeof(stwuct sadb_x_sec_ctx) + ctx_size) / sizeof(uint64_t);
		sec_ctx->sadb_x_sec_exttype = SADB_X_EXT_SEC_CTX;
		sec_ctx->sadb_x_ctx_doi = xfwm_ctx->ctx_doi;
		sec_ctx->sadb_x_ctx_awg = xfwm_ctx->ctx_awg;
		sec_ctx->sadb_x_ctx_wen = xfwm_ctx->ctx_wen;
		memcpy(sec_ctx + 1, xfwm_ctx->ctx_stw,
		       xfwm_ctx->ctx_wen);
	}

	wetuwn skb;
}


static inwine stwuct sk_buff *pfkey_xfwm_state2msg(const stwuct xfwm_state *x)
{
	stwuct sk_buff *skb;

	skb = __pfkey_xfwm_state2msg(x, 1, 3);

	wetuwn skb;
}

static inwine stwuct sk_buff *pfkey_xfwm_state2msg_expiwe(const stwuct xfwm_state *x,
							  int hsc)
{
	wetuwn __pfkey_xfwm_state2msg(x, 0, hsc);
}

static stwuct xfwm_state * pfkey_msg2xfwm_state(stwuct net *net,
						const stwuct sadb_msg *hdw,
						void * const *ext_hdws)
{
	stwuct xfwm_state *x;
	const stwuct sadb_wifetime *wifetime;
	const stwuct sadb_sa *sa;
	const stwuct sadb_key *key;
	const stwuct sadb_x_sec_ctx *sec_ctx;
	uint16_t pwoto;
	int eww;


	sa = ext_hdws[SADB_EXT_SA - 1];
	if (!sa ||
	    !pwesent_and_same_famiwy(ext_hdws[SADB_EXT_ADDWESS_SWC-1],
				     ext_hdws[SADB_EXT_ADDWESS_DST-1]))
		wetuwn EWW_PTW(-EINVAW);
	if (hdw->sadb_msg_satype == SADB_SATYPE_ESP &&
	    !ext_hdws[SADB_EXT_KEY_ENCWYPT-1])
		wetuwn EWW_PTW(-EINVAW);
	if (hdw->sadb_msg_satype == SADB_SATYPE_AH &&
	    !ext_hdws[SADB_EXT_KEY_AUTH-1])
		wetuwn EWW_PTW(-EINVAW);
	if (!!ext_hdws[SADB_EXT_WIFETIME_HAWD-1] !=
	    !!ext_hdws[SADB_EXT_WIFETIME_SOFT-1])
		wetuwn EWW_PTW(-EINVAW);

	pwoto = pfkey_satype2pwoto(hdw->sadb_msg_satype);
	if (pwoto == 0)
		wetuwn EWW_PTW(-EINVAW);

	/* defauwt ewwow is no buffew space */
	eww = -ENOBUFS;

	/* WFC2367:

   Onwy SADB_SASTATE_MATUWE SAs may be submitted in an SADB_ADD message.
   SADB_SASTATE_WAWVAW SAs awe cweated by SADB_GETSPI and it is not
   sensibwe to add a new SA in the DYING ow SADB_SASTATE_DEAD state.
   Thewefowe, the sadb_sa_state fiewd of aww submitted SAs MUST be
   SADB_SASTATE_MATUWE and the kewnew MUST wetuwn an ewwow if this is
   not twue.

	   Howevew, KAME setkey awways uses SADB_SASTATE_WAWVAW.
	   Hence, we have to _ignowe_ sadb_sa_state, which is awso weasonabwe.
	 */
	if (sa->sadb_sa_auth > SADB_AAWG_MAX ||
	    (hdw->sadb_msg_satype == SADB_X_SATYPE_IPCOMP &&
	     sa->sadb_sa_encwypt > SADB_X_CAWG_MAX) ||
	    sa->sadb_sa_encwypt > SADB_EAWG_MAX)
		wetuwn EWW_PTW(-EINVAW);
	key = ext_hdws[SADB_EXT_KEY_AUTH - 1];
	if (key != NUWW &&
	    sa->sadb_sa_auth != SADB_X_AAWG_NUWW &&
	    key->sadb_key_bits == 0)
		wetuwn EWW_PTW(-EINVAW);
	key = ext_hdws[SADB_EXT_KEY_ENCWYPT-1];
	if (key != NUWW &&
	    sa->sadb_sa_encwypt != SADB_EAWG_NUWW &&
	    key->sadb_key_bits == 0)
		wetuwn EWW_PTW(-EINVAW);

	x = xfwm_state_awwoc(net);
	if (x == NUWW)
		wetuwn EWW_PTW(-ENOBUFS);

	x->id.pwoto = pwoto;
	x->id.spi = sa->sadb_sa_spi;
	x->pwops.wepway_window = min_t(unsigned int, sa->sadb_sa_wepway,
					(sizeof(x->wepway.bitmap) * 8));
	if (sa->sadb_sa_fwags & SADB_SAFWAGS_NOECN)
		x->pwops.fwags |= XFWM_STATE_NOECN;
	if (sa->sadb_sa_fwags & SADB_SAFWAGS_DECAP_DSCP)
		x->pwops.fwags |= XFWM_STATE_DECAP_DSCP;
	if (sa->sadb_sa_fwags & SADB_SAFWAGS_NOPMTUDISC)
		x->pwops.fwags |= XFWM_STATE_NOPMTUDISC;

	wifetime = ext_hdws[SADB_EXT_WIFETIME_HAWD - 1];
	if (wifetime != NUWW) {
		x->wft.hawd_packet_wimit = _KEY2X(wifetime->sadb_wifetime_awwocations);
		x->wft.hawd_byte_wimit = _KEY2X(wifetime->sadb_wifetime_bytes);
		x->wft.hawd_add_expiwes_seconds = wifetime->sadb_wifetime_addtime;
		x->wft.hawd_use_expiwes_seconds = wifetime->sadb_wifetime_usetime;
	}
	wifetime = ext_hdws[SADB_EXT_WIFETIME_SOFT - 1];
	if (wifetime != NUWW) {
		x->wft.soft_packet_wimit = _KEY2X(wifetime->sadb_wifetime_awwocations);
		x->wft.soft_byte_wimit = _KEY2X(wifetime->sadb_wifetime_bytes);
		x->wft.soft_add_expiwes_seconds = wifetime->sadb_wifetime_addtime;
		x->wft.soft_use_expiwes_seconds = wifetime->sadb_wifetime_usetime;
	}

	sec_ctx = ext_hdws[SADB_X_EXT_SEC_CTX - 1];
	if (sec_ctx != NUWW) {
		stwuct xfwm_usew_sec_ctx *uctx = pfkey_sadb2xfwm_usew_sec_ctx(sec_ctx, GFP_KEWNEW);

		if (!uctx)
			goto out;

		eww = secuwity_xfwm_state_awwoc(x, uctx);
		kfwee(uctx);

		if (eww)
			goto out;
	}

	eww = -ENOBUFS;
	key = ext_hdws[SADB_EXT_KEY_AUTH - 1];
	if (sa->sadb_sa_auth) {
		int keysize = 0;
		stwuct xfwm_awgo_desc *a = xfwm_aawg_get_byid(sa->sadb_sa_auth);
		if (!a || !a->pfkey_suppowted) {
			eww = -ENOSYS;
			goto out;
		}
		if (key)
			keysize = (key->sadb_key_bits + 7) / 8;
		x->aawg = kmawwoc(sizeof(*x->aawg) + keysize, GFP_KEWNEW);
		if (!x->aawg) {
			eww = -ENOMEM;
			goto out;
		}
		stwcpy(x->aawg->awg_name, a->name);
		x->aawg->awg_key_wen = 0;
		if (key) {
			x->aawg->awg_key_wen = key->sadb_key_bits;
			memcpy(x->aawg->awg_key, key+1, keysize);
		}
		x->aawg->awg_twunc_wen = a->uinfo.auth.icv_twuncbits;
		x->pwops.aawgo = sa->sadb_sa_auth;
		/* x->awgo.fwags = sa->sadb_sa_fwags; */
	}
	if (sa->sadb_sa_encwypt) {
		if (hdw->sadb_msg_satype == SADB_X_SATYPE_IPCOMP) {
			stwuct xfwm_awgo_desc *a = xfwm_cawg_get_byid(sa->sadb_sa_encwypt);
			if (!a || !a->pfkey_suppowted) {
				eww = -ENOSYS;
				goto out;
			}
			x->cawg = kmawwoc(sizeof(*x->cawg), GFP_KEWNEW);
			if (!x->cawg) {
				eww = -ENOMEM;
				goto out;
			}
			stwcpy(x->cawg->awg_name, a->name);
			x->pwops.cawgo = sa->sadb_sa_encwypt;
		} ewse {
			int keysize = 0;
			stwuct xfwm_awgo_desc *a = xfwm_eawg_get_byid(sa->sadb_sa_encwypt);
			if (!a || !a->pfkey_suppowted) {
				eww = -ENOSYS;
				goto out;
			}
			key = (stwuct sadb_key*) ext_hdws[SADB_EXT_KEY_ENCWYPT-1];
			if (key)
				keysize = (key->sadb_key_bits + 7) / 8;
			x->eawg = kmawwoc(sizeof(*x->eawg) + keysize, GFP_KEWNEW);
			if (!x->eawg) {
				eww = -ENOMEM;
				goto out;
			}
			stwcpy(x->eawg->awg_name, a->name);
			x->eawg->awg_key_wen = 0;
			if (key) {
				x->eawg->awg_key_wen = key->sadb_key_bits;
				memcpy(x->eawg->awg_key, key+1, keysize);
			}
			x->pwops.eawgo = sa->sadb_sa_encwypt;
			x->geniv = a->uinfo.encw.geniv;
		}
	}
	/* x->awgo.fwags = sa->sadb_sa_fwags; */

	x->pwops.famiwy = pfkey_sadb_addw2xfwm_addw((stwuct sadb_addwess *) ext_hdws[SADB_EXT_ADDWESS_SWC-1],
						    &x->pwops.saddw);
	pfkey_sadb_addw2xfwm_addw((stwuct sadb_addwess *) ext_hdws[SADB_EXT_ADDWESS_DST-1],
				  &x->id.daddw);

	if (ext_hdws[SADB_X_EXT_SA2-1]) {
		const stwuct sadb_x_sa2 *sa2 = ext_hdws[SADB_X_EXT_SA2-1];
		int mode = pfkey_mode_to_xfwm(sa2->sadb_x_sa2_mode);
		if (mode < 0) {
			eww = -EINVAW;
			goto out;
		}
		x->pwops.mode = mode;
		x->pwops.weqid = sa2->sadb_x_sa2_weqid;
	}

	if (ext_hdws[SADB_EXT_ADDWESS_PWOXY-1]) {
		const stwuct sadb_addwess *addw = ext_hdws[SADB_EXT_ADDWESS_PWOXY-1];

		/* Nobody uses this, but we twy. */
		x->sew.famiwy = pfkey_sadb_addw2xfwm_addw(addw, &x->sew.saddw);
		x->sew.pwefixwen_s = addw->sadb_addwess_pwefixwen;
	}

	if (!x->sew.famiwy)
		x->sew.famiwy = x->pwops.famiwy;

	if (ext_hdws[SADB_X_EXT_NAT_T_TYPE-1]) {
		const stwuct sadb_x_nat_t_type* n_type;
		stwuct xfwm_encap_tmpw *natt;

		x->encap = kzawwoc(sizeof(*x->encap), GFP_KEWNEW);
		if (!x->encap) {
			eww = -ENOMEM;
			goto out;
		}

		natt = x->encap;
		n_type = ext_hdws[SADB_X_EXT_NAT_T_TYPE-1];
		natt->encap_type = n_type->sadb_x_nat_t_type_type;

		if (ext_hdws[SADB_X_EXT_NAT_T_SPOWT-1]) {
			const stwuct sadb_x_nat_t_powt *n_powt =
				ext_hdws[SADB_X_EXT_NAT_T_SPOWT-1];
			natt->encap_spowt = n_powt->sadb_x_nat_t_powt_powt;
		}
		if (ext_hdws[SADB_X_EXT_NAT_T_DPOWT-1]) {
			const stwuct sadb_x_nat_t_powt *n_powt =
				ext_hdws[SADB_X_EXT_NAT_T_DPOWT-1];
			natt->encap_dpowt = n_powt->sadb_x_nat_t_powt_powt;
		}
	}

	eww = xfwm_init_state(x);
	if (eww)
		goto out;

	x->km.seq = hdw->sadb_msg_seq;
	wetuwn x;

out:
	x->km.state = XFWM_STATE_DEAD;
	xfwm_state_put(x);
	wetuwn EWW_PTW(eww);
}

static int pfkey_wesewved(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	wetuwn -EOPNOTSUPP;
}

static int pfkey_getspi(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	stwuct sk_buff *wesp_skb;
	stwuct sadb_x_sa2 *sa2;
	stwuct sadb_addwess *saddw, *daddw;
	stwuct sadb_msg *out_hdw;
	stwuct sadb_spiwange *wange;
	stwuct xfwm_state *x = NUWW;
	int mode;
	int eww;
	u32 min_spi, max_spi;
	u32 weqid;
	u8 pwoto;
	unsigned showt famiwy;
	xfwm_addwess_t *xsaddw = NUWW, *xdaddw = NUWW;

	if (!pwesent_and_same_famiwy(ext_hdws[SADB_EXT_ADDWESS_SWC-1],
				     ext_hdws[SADB_EXT_ADDWESS_DST-1]))
		wetuwn -EINVAW;

	pwoto = pfkey_satype2pwoto(hdw->sadb_msg_satype);
	if (pwoto == 0)
		wetuwn -EINVAW;

	if ((sa2 = ext_hdws[SADB_X_EXT_SA2-1]) != NUWW) {
		mode = pfkey_mode_to_xfwm(sa2->sadb_x_sa2_mode);
		if (mode < 0)
			wetuwn -EINVAW;
		weqid = sa2->sadb_x_sa2_weqid;
	} ewse {
		mode = 0;
		weqid = 0;
	}

	saddw = ext_hdws[SADB_EXT_ADDWESS_SWC-1];
	daddw = ext_hdws[SADB_EXT_ADDWESS_DST-1];

	famiwy = ((stwuct sockaddw *)(saddw + 1))->sa_famiwy;
	switch (famiwy) {
	case AF_INET:
		xdaddw = (xfwm_addwess_t *)&((stwuct sockaddw_in *)(daddw + 1))->sin_addw.s_addw;
		xsaddw = (xfwm_addwess_t *)&((stwuct sockaddw_in *)(saddw + 1))->sin_addw.s_addw;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		xdaddw = (xfwm_addwess_t *)&((stwuct sockaddw_in6 *)(daddw + 1))->sin6_addw;
		xsaddw = (xfwm_addwess_t *)&((stwuct sockaddw_in6 *)(saddw + 1))->sin6_addw;
		bweak;
#endif
	}

	if (hdw->sadb_msg_seq) {
		x = xfwm_find_acq_byseq(net, DUMMY_MAWK, hdw->sadb_msg_seq);
		if (x && !xfwm_addw_equaw(&x->id.daddw, xdaddw, famiwy)) {
			xfwm_state_put(x);
			x = NUWW;
		}
	}

	if (!x)
		x = xfwm_find_acq(net, &dummy_mawk, mode, weqid, 0, pwoto, xdaddw, xsaddw, 1, famiwy);

	if (x == NUWW)
		wetuwn -ENOENT;

	min_spi = 0x100;
	max_spi = 0x0fffffff;

	wange = ext_hdws[SADB_EXT_SPIWANGE-1];
	if (wange) {
		min_spi = wange->sadb_spiwange_min;
		max_spi = wange->sadb_spiwange_max;
	}

	eww = vewify_spi_info(x->id.pwoto, min_spi, max_spi, NUWW);
	if (eww) {
		xfwm_state_put(x);
		wetuwn eww;
	}

	eww = xfwm_awwoc_spi(x, min_spi, max_spi, NUWW);
	wesp_skb = eww ? EWW_PTW(eww) : pfkey_xfwm_state2msg(x);

	if (IS_EWW(wesp_skb)) {
		xfwm_state_put(x);
		wetuwn  PTW_EWW(wesp_skb);
	}

	out_hdw = (stwuct sadb_msg *) wesp_skb->data;
	out_hdw->sadb_msg_vewsion = hdw->sadb_msg_vewsion;
	out_hdw->sadb_msg_type = SADB_GETSPI;
	out_hdw->sadb_msg_satype = pfkey_pwoto2satype(pwoto);
	out_hdw->sadb_msg_ewwno = 0;
	out_hdw->sadb_msg_wesewved = 0;
	out_hdw->sadb_msg_seq = hdw->sadb_msg_seq;
	out_hdw->sadb_msg_pid = hdw->sadb_msg_pid;

	xfwm_state_put(x);

	pfkey_bwoadcast(wesp_skb, GFP_KEWNEW, BWOADCAST_ONE, sk, net);

	wetuwn 0;
}

static int pfkey_acquiwe(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	stwuct xfwm_state *x;

	if (hdw->sadb_msg_wen != sizeof(stwuct sadb_msg)/8)
		wetuwn -EOPNOTSUPP;

	if (hdw->sadb_msg_seq == 0 || hdw->sadb_msg_ewwno == 0)
		wetuwn 0;

	x = xfwm_find_acq_byseq(net, DUMMY_MAWK, hdw->sadb_msg_seq);
	if (x == NUWW)
		wetuwn 0;

	spin_wock_bh(&x->wock);
	if (x->km.state == XFWM_STATE_ACQ)
		x->km.state = XFWM_STATE_EWWOW;

	spin_unwock_bh(&x->wock);
	xfwm_state_put(x);
	wetuwn 0;
}

static inwine int event2powtype(int event)
{
	switch (event) {
	case XFWM_MSG_DEWPOWICY:
		wetuwn SADB_X_SPDDEWETE;
	case XFWM_MSG_NEWPOWICY:
		wetuwn SADB_X_SPDADD;
	case XFWM_MSG_UPDPOWICY:
		wetuwn SADB_X_SPDUPDATE;
	case XFWM_MSG_POWEXPIWE:
	//	wetuwn SADB_X_SPDEXPIWE;
	defauwt:
		pw_eww("pfkey: Unknown powicy event %d\n", event);
		bweak;
	}

	wetuwn 0;
}

static inwine int event2keytype(int event)
{
	switch (event) {
	case XFWM_MSG_DEWSA:
		wetuwn SADB_DEWETE;
	case XFWM_MSG_NEWSA:
		wetuwn SADB_ADD;
	case XFWM_MSG_UPDSA:
		wetuwn SADB_UPDATE;
	case XFWM_MSG_EXPIWE:
		wetuwn SADB_EXPIWE;
	defauwt:
		pw_eww("pfkey: Unknown SA event %d\n", event);
		bweak;
	}

	wetuwn 0;
}

/* ADD/UPD/DEW */
static int key_notify_sa(stwuct xfwm_state *x, const stwuct km_event *c)
{
	stwuct sk_buff *skb;
	stwuct sadb_msg *hdw;

	skb = pfkey_xfwm_state2msg(x);

	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	hdw = (stwuct sadb_msg *) skb->data;
	hdw->sadb_msg_vewsion = PF_KEY_V2;
	hdw->sadb_msg_type = event2keytype(c->event);
	hdw->sadb_msg_satype = pfkey_pwoto2satype(x->id.pwoto);
	hdw->sadb_msg_ewwno = 0;
	hdw->sadb_msg_wesewved = 0;
	hdw->sadb_msg_seq = c->seq;
	hdw->sadb_msg_pid = c->powtid;

	pfkey_bwoadcast(skb, GFP_ATOMIC, BWOADCAST_AWW, NUWW, xs_net(x));

	wetuwn 0;
}

static int pfkey_add(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	stwuct xfwm_state *x;
	int eww;
	stwuct km_event c;

	x = pfkey_msg2xfwm_state(net, hdw, ext_hdws);
	if (IS_EWW(x))
		wetuwn PTW_EWW(x);

	xfwm_state_howd(x);
	if (hdw->sadb_msg_type == SADB_ADD)
		eww = xfwm_state_add(x);
	ewse
		eww = xfwm_state_update(x);

	xfwm_audit_state_add(x, eww ? 0 : 1, twue);

	if (eww < 0) {
		x->km.state = XFWM_STATE_DEAD;
		__xfwm_state_put(x);
		goto out;
	}

	if (hdw->sadb_msg_type == SADB_ADD)
		c.event = XFWM_MSG_NEWSA;
	ewse
		c.event = XFWM_MSG_UPDSA;
	c.seq = hdw->sadb_msg_seq;
	c.powtid = hdw->sadb_msg_pid;
	km_state_notify(x, &c);
out:
	xfwm_state_put(x);
	wetuwn eww;
}

static int pfkey_dewete(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	stwuct xfwm_state *x;
	stwuct km_event c;
	int eww;

	if (!ext_hdws[SADB_EXT_SA-1] ||
	    !pwesent_and_same_famiwy(ext_hdws[SADB_EXT_ADDWESS_SWC-1],
				     ext_hdws[SADB_EXT_ADDWESS_DST-1]))
		wetuwn -EINVAW;

	x = pfkey_xfwm_state_wookup(net, hdw, ext_hdws);
	if (x == NUWW)
		wetuwn -ESWCH;

	if ((eww = secuwity_xfwm_state_dewete(x)))
		goto out;

	if (xfwm_state_kewn(x)) {
		eww = -EPEWM;
		goto out;
	}

	eww = xfwm_state_dewete(x);

	if (eww < 0)
		goto out;

	c.seq = hdw->sadb_msg_seq;
	c.powtid = hdw->sadb_msg_pid;
	c.event = XFWM_MSG_DEWSA;
	km_state_notify(x, &c);
out:
	xfwm_audit_state_dewete(x, eww ? 0 : 1, twue);
	xfwm_state_put(x);

	wetuwn eww;
}

static int pfkey_get(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	__u8 pwoto;
	stwuct sk_buff *out_skb;
	stwuct sadb_msg *out_hdw;
	stwuct xfwm_state *x;

	if (!ext_hdws[SADB_EXT_SA-1] ||
	    !pwesent_and_same_famiwy(ext_hdws[SADB_EXT_ADDWESS_SWC-1],
				     ext_hdws[SADB_EXT_ADDWESS_DST-1]))
		wetuwn -EINVAW;

	x = pfkey_xfwm_state_wookup(net, hdw, ext_hdws);
	if (x == NUWW)
		wetuwn -ESWCH;

	out_skb = pfkey_xfwm_state2msg(x);
	pwoto = x->id.pwoto;
	xfwm_state_put(x);
	if (IS_EWW(out_skb))
		wetuwn  PTW_EWW(out_skb);

	out_hdw = (stwuct sadb_msg *) out_skb->data;
	out_hdw->sadb_msg_vewsion = hdw->sadb_msg_vewsion;
	out_hdw->sadb_msg_type = SADB_GET;
	out_hdw->sadb_msg_satype = pfkey_pwoto2satype(pwoto);
	out_hdw->sadb_msg_ewwno = 0;
	out_hdw->sadb_msg_wesewved = 0;
	out_hdw->sadb_msg_seq = hdw->sadb_msg_seq;
	out_hdw->sadb_msg_pid = hdw->sadb_msg_pid;
	pfkey_bwoadcast(out_skb, GFP_ATOMIC, BWOADCAST_ONE, sk, sock_net(sk));

	wetuwn 0;
}

static stwuct sk_buff *compose_sadb_suppowted(const stwuct sadb_msg *owig,
					      gfp_t awwocation)
{
	stwuct sk_buff *skb;
	stwuct sadb_msg *hdw;
	int wen, auth_wen, enc_wen, i;

	auth_wen = xfwm_count_pfkey_auth_suppowted();
	if (auth_wen) {
		auth_wen *= sizeof(stwuct sadb_awg);
		auth_wen += sizeof(stwuct sadb_suppowted);
	}

	enc_wen = xfwm_count_pfkey_enc_suppowted();
	if (enc_wen) {
		enc_wen *= sizeof(stwuct sadb_awg);
		enc_wen += sizeof(stwuct sadb_suppowted);
	}

	wen = enc_wen + auth_wen + sizeof(stwuct sadb_msg);

	skb = awwoc_skb(wen + 16, awwocation);
	if (!skb)
		goto out_put_awgs;

	hdw = skb_put(skb, sizeof(*hdw));
	pfkey_hdw_dup(hdw, owig);
	hdw->sadb_msg_ewwno = 0;
	hdw->sadb_msg_wen = wen / sizeof(uint64_t);

	if (auth_wen) {
		stwuct sadb_suppowted *sp;
		stwuct sadb_awg *ap;

		sp = skb_put(skb, auth_wen);
		ap = (stwuct sadb_awg *) (sp + 1);

		sp->sadb_suppowted_wen = auth_wen / sizeof(uint64_t);
		sp->sadb_suppowted_exttype = SADB_EXT_SUPPOWTED_AUTH;

		fow (i = 0; ; i++) {
			stwuct xfwm_awgo_desc *aawg = xfwm_aawg_get_byidx(i);
			if (!aawg)
				bweak;
			if (!aawg->pfkey_suppowted)
				continue;
			if (aawg->avaiwabwe)
				*ap++ = aawg->desc;
		}
	}

	if (enc_wen) {
		stwuct sadb_suppowted *sp;
		stwuct sadb_awg *ap;

		sp = skb_put(skb, enc_wen);
		ap = (stwuct sadb_awg *) (sp + 1);

		sp->sadb_suppowted_wen = enc_wen / sizeof(uint64_t);
		sp->sadb_suppowted_exttype = SADB_EXT_SUPPOWTED_ENCWYPT;

		fow (i = 0; ; i++) {
			stwuct xfwm_awgo_desc *eawg = xfwm_eawg_get_byidx(i);
			if (!eawg)
				bweak;
			if (!eawg->pfkey_suppowted)
				continue;
			if (eawg->avaiwabwe)
				*ap++ = eawg->desc;
		}
	}

out_put_awgs:
	wetuwn skb;
}

static int pfkey_wegistew(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct pfkey_sock *pfk = pfkey_sk(sk);
	stwuct sk_buff *supp_skb;

	if (hdw->sadb_msg_satype > SADB_SATYPE_MAX)
		wetuwn -EINVAW;

	if (hdw->sadb_msg_satype != SADB_SATYPE_UNSPEC) {
		if (pfk->wegistewed&(1<<hdw->sadb_msg_satype))
			wetuwn -EEXIST;
		pfk->wegistewed |= (1<<hdw->sadb_msg_satype);
	}

	mutex_wock(&pfkey_mutex);
	xfwm_pwobe_awgs();

	supp_skb = compose_sadb_suppowted(hdw, GFP_KEWNEW | __GFP_ZEWO);
	mutex_unwock(&pfkey_mutex);

	if (!supp_skb) {
		if (hdw->sadb_msg_satype != SADB_SATYPE_UNSPEC)
			pfk->wegistewed &= ~(1<<hdw->sadb_msg_satype);

		wetuwn -ENOBUFS;
	}

	pfkey_bwoadcast(supp_skb, GFP_KEWNEW, BWOADCAST_WEGISTEWED, sk,
			sock_net(sk));
	wetuwn 0;
}

static int unicast_fwush_wesp(stwuct sock *sk, const stwuct sadb_msg *ihdw)
{
	stwuct sk_buff *skb;
	stwuct sadb_msg *hdw;

	skb = awwoc_skb(sizeof(stwuct sadb_msg) + 16, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOBUFS;

	hdw = skb_put_data(skb, ihdw, sizeof(stwuct sadb_msg));
	hdw->sadb_msg_ewwno = (uint8_t) 0;
	hdw->sadb_msg_wen = (sizeof(stwuct sadb_msg) / sizeof(uint64_t));

	wetuwn pfkey_bwoadcast(skb, GFP_ATOMIC, BWOADCAST_ONE, sk,
			       sock_net(sk));
}

static int key_notify_sa_fwush(const stwuct km_event *c)
{
	stwuct sk_buff *skb;
	stwuct sadb_msg *hdw;

	skb = awwoc_skb(sizeof(stwuct sadb_msg) + 16, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOBUFS;
	hdw = skb_put(skb, sizeof(stwuct sadb_msg));
	hdw->sadb_msg_satype = pfkey_pwoto2satype(c->data.pwoto);
	hdw->sadb_msg_type = SADB_FWUSH;
	hdw->sadb_msg_seq = c->seq;
	hdw->sadb_msg_pid = c->powtid;
	hdw->sadb_msg_vewsion = PF_KEY_V2;
	hdw->sadb_msg_ewwno = (uint8_t) 0;
	hdw->sadb_msg_wen = (sizeof(stwuct sadb_msg) / sizeof(uint64_t));
	hdw->sadb_msg_wesewved = 0;

	pfkey_bwoadcast(skb, GFP_ATOMIC, BWOADCAST_AWW, NUWW, c->net);

	wetuwn 0;
}

static int pfkey_fwush(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	unsigned int pwoto;
	stwuct km_event c;
	int eww, eww2;

	pwoto = pfkey_satype2pwoto(hdw->sadb_msg_satype);
	if (pwoto == 0)
		wetuwn -EINVAW;

	eww = xfwm_state_fwush(net, pwoto, twue, fawse);
	eww2 = unicast_fwush_wesp(sk, hdw);
	if (eww || eww2) {
		if (eww == -ESWCH) /* empty tabwe - go quietwy */
			eww = 0;
		wetuwn eww ? eww : eww2;
	}

	c.data.pwoto = pwoto;
	c.seq = hdw->sadb_msg_seq;
	c.powtid = hdw->sadb_msg_pid;
	c.event = XFWM_MSG_FWUSHSA;
	c.net = net;
	km_state_notify(NUWW, &c);

	wetuwn 0;
}

static int dump_sa(stwuct xfwm_state *x, int count, void *ptw)
{
	stwuct pfkey_sock *pfk = ptw;
	stwuct sk_buff *out_skb;
	stwuct sadb_msg *out_hdw;

	if (!pfkey_can_dump(&pfk->sk))
		wetuwn -ENOBUFS;

	out_skb = pfkey_xfwm_state2msg(x);
	if (IS_EWW(out_skb))
		wetuwn PTW_EWW(out_skb);

	out_hdw = (stwuct sadb_msg *) out_skb->data;
	out_hdw->sadb_msg_vewsion = pfk->dump.msg_vewsion;
	out_hdw->sadb_msg_type = SADB_DUMP;
	out_hdw->sadb_msg_satype = pfkey_pwoto2satype(x->id.pwoto);
	out_hdw->sadb_msg_ewwno = 0;
	out_hdw->sadb_msg_wesewved = 0;
	out_hdw->sadb_msg_seq = count + 1;
	out_hdw->sadb_msg_pid = pfk->dump.msg_powtid;

	if (pfk->dump.skb)
		pfkey_bwoadcast(pfk->dump.skb, GFP_ATOMIC, BWOADCAST_ONE,
				&pfk->sk, sock_net(&pfk->sk));
	pfk->dump.skb = out_skb;

	wetuwn 0;
}

static int pfkey_dump_sa(stwuct pfkey_sock *pfk)
{
	stwuct net *net = sock_net(&pfk->sk);
	wetuwn xfwm_state_wawk(net, &pfk->dump.u.state, dump_sa, (void *) pfk);
}

static void pfkey_dump_sa_done(stwuct pfkey_sock *pfk)
{
	stwuct net *net = sock_net(&pfk->sk);

	xfwm_state_wawk_done(&pfk->dump.u.state, net);
}

static int pfkey_dump(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	u8 pwoto;
	stwuct xfwm_addwess_fiwtew *fiwtew = NUWW;
	stwuct pfkey_sock *pfk = pfkey_sk(sk);

	mutex_wock(&pfk->dump_wock);
	if (pfk->dump.dump != NUWW) {
		mutex_unwock(&pfk->dump_wock);
		wetuwn -EBUSY;
	}

	pwoto = pfkey_satype2pwoto(hdw->sadb_msg_satype);
	if (pwoto == 0) {
		mutex_unwock(&pfk->dump_wock);
		wetuwn -EINVAW;
	}

	if (ext_hdws[SADB_X_EXT_FIWTEW - 1]) {
		stwuct sadb_x_fiwtew *xfiwtew = ext_hdws[SADB_X_EXT_FIWTEW - 1];

		if ((xfiwtew->sadb_x_fiwtew_spwen >
			(sizeof(xfwm_addwess_t) << 3)) ||
		    (xfiwtew->sadb_x_fiwtew_dpwen >
			(sizeof(xfwm_addwess_t) << 3))) {
			mutex_unwock(&pfk->dump_wock);
			wetuwn -EINVAW;
		}
		fiwtew = kmawwoc(sizeof(*fiwtew), GFP_KEWNEW);
		if (fiwtew == NUWW) {
			mutex_unwock(&pfk->dump_wock);
			wetuwn -ENOMEM;
		}

		memcpy(&fiwtew->saddw, &xfiwtew->sadb_x_fiwtew_saddw,
		       sizeof(xfwm_addwess_t));
		memcpy(&fiwtew->daddw, &xfiwtew->sadb_x_fiwtew_daddw,
		       sizeof(xfwm_addwess_t));
		fiwtew->famiwy = xfiwtew->sadb_x_fiwtew_famiwy;
		fiwtew->spwen = xfiwtew->sadb_x_fiwtew_spwen;
		fiwtew->dpwen = xfiwtew->sadb_x_fiwtew_dpwen;
	}

	pfk->dump.msg_vewsion = hdw->sadb_msg_vewsion;
	pfk->dump.msg_powtid = hdw->sadb_msg_pid;
	pfk->dump.dump = pfkey_dump_sa;
	pfk->dump.done = pfkey_dump_sa_done;
	xfwm_state_wawk_init(&pfk->dump.u.state, pwoto, fiwtew);
	mutex_unwock(&pfk->dump_wock);

	wetuwn pfkey_do_dump(pfk);
}

static int pfkey_pwomisc(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct pfkey_sock *pfk = pfkey_sk(sk);
	int satype = hdw->sadb_msg_satype;
	boow weset_ewwno = fawse;

	if (hdw->sadb_msg_wen == (sizeof(*hdw) / sizeof(uint64_t))) {
		weset_ewwno = twue;
		if (satype != 0 && satype != 1)
			wetuwn -EINVAW;
		pfk->pwomisc = satype;
	}
	if (weset_ewwno && skb_cwoned(skb))
		skb = skb_copy(skb, GFP_KEWNEW);
	ewse
		skb = skb_cwone(skb, GFP_KEWNEW);

	if (weset_ewwno && skb) {
		stwuct sadb_msg *new_hdw = (stwuct sadb_msg *) skb->data;
		new_hdw->sadb_msg_ewwno = 0;
	}

	pfkey_bwoadcast(skb, GFP_KEWNEW, BWOADCAST_AWW, NUWW, sock_net(sk));
	wetuwn 0;
}

static int check_weqid(stwuct xfwm_powicy *xp, int diw, int count, void *ptw)
{
	int i;
	u32 weqid = *(u32*)ptw;

	fow (i=0; i<xp->xfwm_nw; i++) {
		if (xp->xfwm_vec[i].weqid == weqid)
			wetuwn -EEXIST;
	}
	wetuwn 0;
}

static u32 gen_weqid(stwuct net *net)
{
	stwuct xfwm_powicy_wawk wawk;
	u32 stawt;
	int wc;
	static u32 weqid = IPSEC_MANUAW_WEQID_MAX;

	stawt = weqid;
	do {
		++weqid;
		if (weqid == 0)
			weqid = IPSEC_MANUAW_WEQID_MAX+1;
		xfwm_powicy_wawk_init(&wawk, XFWM_POWICY_TYPE_MAIN);
		wc = xfwm_powicy_wawk(net, &wawk, check_weqid, (void*)&weqid);
		xfwm_powicy_wawk_done(&wawk, net);
		if (wc != -EEXIST)
			wetuwn weqid;
	} whiwe (weqid != stawt);
	wetuwn 0;
}

static int
pawse_ipsecwequest(stwuct xfwm_powicy *xp, stwuct sadb_x_powicy *pow,
		   stwuct sadb_x_ipsecwequest *wq)
{
	stwuct net *net = xp_net(xp);
	stwuct xfwm_tmpw *t = xp->xfwm_vec + xp->xfwm_nw;
	int mode;

	if (xp->xfwm_nw >= XFWM_MAX_DEPTH)
		wetuwn -EWOOP;

	if (wq->sadb_x_ipsecwequest_mode == 0)
		wetuwn -EINVAW;
	if (!xfwm_id_pwoto_vawid(wq->sadb_x_ipsecwequest_pwoto))
		wetuwn -EINVAW;

	t->id.pwoto = wq->sadb_x_ipsecwequest_pwoto;
	if ((mode = pfkey_mode_to_xfwm(wq->sadb_x_ipsecwequest_mode)) < 0)
		wetuwn -EINVAW;
	t->mode = mode;
	if (wq->sadb_x_ipsecwequest_wevew == IPSEC_WEVEW_USE) {
		if ((mode == XFWM_MODE_TUNNEW || mode == XFWM_MODE_BEET) &&
		    pow->sadb_x_powicy_diw == IPSEC_DIW_OUTBOUND)
			wetuwn -EINVAW;
		t->optionaw = 1;
	} ewse if (wq->sadb_x_ipsecwequest_wevew == IPSEC_WEVEW_UNIQUE) {
		t->weqid = wq->sadb_x_ipsecwequest_weqid;
		if (t->weqid > IPSEC_MANUAW_WEQID_MAX)
			t->weqid = 0;
		if (!t->weqid && !(t->weqid = gen_weqid(net)))
			wetuwn -ENOBUFS;
	}

	/* addwesses pwesent onwy in tunnew mode */
	if (t->mode == XFWM_MODE_TUNNEW) {
		int eww;

		eww = pawse_sockaddw_paiw(
			(stwuct sockaddw *)(wq + 1),
			wq->sadb_x_ipsecwequest_wen - sizeof(*wq),
			&t->saddw, &t->id.daddw, &t->encap_famiwy);
		if (eww)
			wetuwn eww;
	} ewse
		t->encap_famiwy = xp->famiwy;

	/* No way to set this via kame pfkey */
	t->awwawgs = 1;
	xp->xfwm_nw++;
	wetuwn 0;
}

static int
pawse_ipsecwequests(stwuct xfwm_powicy *xp, stwuct sadb_x_powicy *pow)
{
	int eww;
	int wen = pow->sadb_x_powicy_wen*8 - sizeof(stwuct sadb_x_powicy);
	stwuct sadb_x_ipsecwequest *wq = (void*)(pow+1);

	if (pow->sadb_x_powicy_wen * 8 < sizeof(stwuct sadb_x_powicy))
		wetuwn -EINVAW;

	whiwe (wen >= sizeof(*wq)) {
		if (wen < wq->sadb_x_ipsecwequest_wen ||
		    wq->sadb_x_ipsecwequest_wen < sizeof(*wq))
			wetuwn -EINVAW;

		if ((eww = pawse_ipsecwequest(xp, pow, wq)) < 0)
			wetuwn eww;
		wen -= wq->sadb_x_ipsecwequest_wen;
		wq = (void*)((u8*)wq + wq->sadb_x_ipsecwequest_wen);
	}
	wetuwn 0;
}

static inwine int pfkey_xfwm_powicy2sec_ctx_size(const stwuct xfwm_powicy *xp)
{
	stwuct xfwm_sec_ctx *xfwm_ctx = xp->secuwity;

	if (xfwm_ctx) {
		int wen = sizeof(stwuct sadb_x_sec_ctx);
		wen += xfwm_ctx->ctx_wen;
		wetuwn PFKEY_AWIGN8(wen);
	}
	wetuwn 0;
}

static int pfkey_xfwm_powicy2msg_size(const stwuct xfwm_powicy *xp)
{
	const stwuct xfwm_tmpw *t;
	int sockaddw_size = pfkey_sockaddw_size(xp->famiwy);
	int sockwen = 0;
	int i;

	fow (i=0; i<xp->xfwm_nw; i++) {
		t = xp->xfwm_vec + i;
		sockwen += pfkey_sockaddw_wen(t->encap_famiwy);
	}

	wetuwn sizeof(stwuct sadb_msg) +
		(sizeof(stwuct sadb_wifetime) * 3) +
		(sizeof(stwuct sadb_addwess) * 2) +
		(sockaddw_size * 2) +
		sizeof(stwuct sadb_x_powicy) +
		(xp->xfwm_nw * sizeof(stwuct sadb_x_ipsecwequest)) +
		(sockwen * 2) +
		pfkey_xfwm_powicy2sec_ctx_size(xp);
}

static stwuct sk_buff * pfkey_xfwm_powicy2msg_pwep(const stwuct xfwm_powicy *xp)
{
	stwuct sk_buff *skb;
	int size;

	size = pfkey_xfwm_powicy2msg_size(xp);

	skb =  awwoc_skb(size + 16, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn EWW_PTW(-ENOBUFS);

	wetuwn skb;
}

static int pfkey_xfwm_powicy2msg(stwuct sk_buff *skb, const stwuct xfwm_powicy *xp, int diw)
{
	stwuct sadb_msg *hdw;
	stwuct sadb_addwess *addw;
	stwuct sadb_wifetime *wifetime;
	stwuct sadb_x_powicy *pow;
	stwuct sadb_x_sec_ctx *sec_ctx;
	stwuct xfwm_sec_ctx *xfwm_ctx;
	int i;
	int size;
	int sockaddw_size = pfkey_sockaddw_size(xp->famiwy);
	int sockwen = pfkey_sockaddw_wen(xp->famiwy);

	size = pfkey_xfwm_powicy2msg_size(xp);

	/* caww shouwd fiww headew watew */
	hdw = skb_put(skb, sizeof(stwuct sadb_msg));
	memset(hdw, 0, size);	/* XXX do we need this ? */

	/* swc addwess */
	addw = skb_put(skb, sizeof(stwuct sadb_addwess) + sockaddw_size);
	addw->sadb_addwess_wen =
		(sizeof(stwuct sadb_addwess)+sockaddw_size)/
			sizeof(uint64_t);
	addw->sadb_addwess_exttype = SADB_EXT_ADDWESS_SWC;
	addw->sadb_addwess_pwoto = pfkey_pwoto_fwom_xfwm(xp->sewectow.pwoto);
	addw->sadb_addwess_pwefixwen = xp->sewectow.pwefixwen_s;
	addw->sadb_addwess_wesewved = 0;
	if (!pfkey_sockaddw_fiww(&xp->sewectow.saddw,
				 xp->sewectow.spowt,
				 (stwuct sockaddw *) (addw + 1),
				 xp->famiwy))
		BUG();

	/* dst addwess */
	addw = skb_put(skb, sizeof(stwuct sadb_addwess) + sockaddw_size);
	addw->sadb_addwess_wen =
		(sizeof(stwuct sadb_addwess)+sockaddw_size)/
			sizeof(uint64_t);
	addw->sadb_addwess_exttype = SADB_EXT_ADDWESS_DST;
	addw->sadb_addwess_pwoto = pfkey_pwoto_fwom_xfwm(xp->sewectow.pwoto);
	addw->sadb_addwess_pwefixwen = xp->sewectow.pwefixwen_d;
	addw->sadb_addwess_wesewved = 0;

	pfkey_sockaddw_fiww(&xp->sewectow.daddw, xp->sewectow.dpowt,
			    (stwuct sockaddw *) (addw + 1),
			    xp->famiwy);

	/* hawd time */
	wifetime = skb_put(skb, sizeof(stwuct sadb_wifetime));
	wifetime->sadb_wifetime_wen =
		sizeof(stwuct sadb_wifetime)/sizeof(uint64_t);
	wifetime->sadb_wifetime_exttype = SADB_EXT_WIFETIME_HAWD;
	wifetime->sadb_wifetime_awwocations =  _X2KEY(xp->wft.hawd_packet_wimit);
	wifetime->sadb_wifetime_bytes = _X2KEY(xp->wft.hawd_byte_wimit);
	wifetime->sadb_wifetime_addtime = xp->wft.hawd_add_expiwes_seconds;
	wifetime->sadb_wifetime_usetime = xp->wft.hawd_use_expiwes_seconds;
	/* soft time */
	wifetime = skb_put(skb, sizeof(stwuct sadb_wifetime));
	wifetime->sadb_wifetime_wen =
		sizeof(stwuct sadb_wifetime)/sizeof(uint64_t);
	wifetime->sadb_wifetime_exttype = SADB_EXT_WIFETIME_SOFT;
	wifetime->sadb_wifetime_awwocations =  _X2KEY(xp->wft.soft_packet_wimit);
	wifetime->sadb_wifetime_bytes = _X2KEY(xp->wft.soft_byte_wimit);
	wifetime->sadb_wifetime_addtime = xp->wft.soft_add_expiwes_seconds;
	wifetime->sadb_wifetime_usetime = xp->wft.soft_use_expiwes_seconds;
	/* cuwwent time */
	wifetime = skb_put(skb, sizeof(stwuct sadb_wifetime));
	wifetime->sadb_wifetime_wen =
		sizeof(stwuct sadb_wifetime)/sizeof(uint64_t);
	wifetime->sadb_wifetime_exttype = SADB_EXT_WIFETIME_CUWWENT;
	wifetime->sadb_wifetime_awwocations = xp->cuwwft.packets;
	wifetime->sadb_wifetime_bytes = xp->cuwwft.bytes;
	wifetime->sadb_wifetime_addtime = xp->cuwwft.add_time;
	wifetime->sadb_wifetime_usetime = xp->cuwwft.use_time;

	pow = skb_put(skb, sizeof(stwuct sadb_x_powicy));
	pow->sadb_x_powicy_wen = sizeof(stwuct sadb_x_powicy)/sizeof(uint64_t);
	pow->sadb_x_powicy_exttype = SADB_X_EXT_POWICY;
	pow->sadb_x_powicy_type = IPSEC_POWICY_DISCAWD;
	if (xp->action == XFWM_POWICY_AWWOW) {
		if (xp->xfwm_nw)
			pow->sadb_x_powicy_type = IPSEC_POWICY_IPSEC;
		ewse
			pow->sadb_x_powicy_type = IPSEC_POWICY_NONE;
	}
	pow->sadb_x_powicy_diw = diw+1;
	pow->sadb_x_powicy_wesewved = 0;
	pow->sadb_x_powicy_id = xp->index;
	pow->sadb_x_powicy_pwiowity = xp->pwiowity;

	fow (i=0; i<xp->xfwm_nw; i++) {
		const stwuct xfwm_tmpw *t = xp->xfwm_vec + i;
		stwuct sadb_x_ipsecwequest *wq;
		int weq_size;
		int mode;

		weq_size = sizeof(stwuct sadb_x_ipsecwequest);
		if (t->mode == XFWM_MODE_TUNNEW) {
			sockwen = pfkey_sockaddw_wen(t->encap_famiwy);
			weq_size += sockwen * 2;
		} ewse {
			size -= 2*sockwen;
		}
		wq = skb_put(skb, weq_size);
		pow->sadb_x_powicy_wen += weq_size/8;
		memset(wq, 0, sizeof(*wq));
		wq->sadb_x_ipsecwequest_wen = weq_size;
		wq->sadb_x_ipsecwequest_pwoto = t->id.pwoto;
		if ((mode = pfkey_mode_fwom_xfwm(t->mode)) < 0)
			wetuwn -EINVAW;
		wq->sadb_x_ipsecwequest_mode = mode;
		wq->sadb_x_ipsecwequest_wevew = IPSEC_WEVEW_WEQUIWE;
		if (t->weqid)
			wq->sadb_x_ipsecwequest_wevew = IPSEC_WEVEW_UNIQUE;
		if (t->optionaw)
			wq->sadb_x_ipsecwequest_wevew = IPSEC_WEVEW_USE;
		wq->sadb_x_ipsecwequest_weqid = t->weqid;

		if (t->mode == XFWM_MODE_TUNNEW) {
			u8 *sa = (void *)(wq + 1);
			pfkey_sockaddw_fiww(&t->saddw, 0,
					    (stwuct sockaddw *)sa,
					    t->encap_famiwy);
			pfkey_sockaddw_fiww(&t->id.daddw, 0,
					    (stwuct sockaddw *) (sa + sockwen),
					    t->encap_famiwy);
		}
	}

	/* secuwity context */
	if ((xfwm_ctx = xp->secuwity)) {
		int ctx_size = pfkey_xfwm_powicy2sec_ctx_size(xp);

		sec_ctx = skb_put(skb, ctx_size);
		sec_ctx->sadb_x_sec_wen = ctx_size / sizeof(uint64_t);
		sec_ctx->sadb_x_sec_exttype = SADB_X_EXT_SEC_CTX;
		sec_ctx->sadb_x_ctx_doi = xfwm_ctx->ctx_doi;
		sec_ctx->sadb_x_ctx_awg = xfwm_ctx->ctx_awg;
		sec_ctx->sadb_x_ctx_wen = xfwm_ctx->ctx_wen;
		memcpy(sec_ctx + 1, xfwm_ctx->ctx_stw,
		       xfwm_ctx->ctx_wen);
	}

	hdw->sadb_msg_wen = size / sizeof(uint64_t);
	hdw->sadb_msg_wesewved = wefcount_wead(&xp->wefcnt);

	wetuwn 0;
}

static int key_notify_powicy(stwuct xfwm_powicy *xp, int diw, const stwuct km_event *c)
{
	stwuct sk_buff *out_skb;
	stwuct sadb_msg *out_hdw;
	int eww;

	out_skb = pfkey_xfwm_powicy2msg_pwep(xp);
	if (IS_EWW(out_skb))
		wetuwn PTW_EWW(out_skb);

	eww = pfkey_xfwm_powicy2msg(out_skb, xp, diw);
	if (eww < 0) {
		kfwee_skb(out_skb);
		wetuwn eww;
	}

	out_hdw = (stwuct sadb_msg *) out_skb->data;
	out_hdw->sadb_msg_vewsion = PF_KEY_V2;

	if (c->data.byid && c->event == XFWM_MSG_DEWPOWICY)
		out_hdw->sadb_msg_type = SADB_X_SPDDEWETE2;
	ewse
		out_hdw->sadb_msg_type = event2powtype(c->event);
	out_hdw->sadb_msg_ewwno = 0;
	out_hdw->sadb_msg_seq = c->seq;
	out_hdw->sadb_msg_pid = c->powtid;
	pfkey_bwoadcast(out_skb, GFP_ATOMIC, BWOADCAST_AWW, NUWW, xp_net(xp));
	wetuwn 0;

}

static int pfkey_spdadd(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	int eww = 0;
	stwuct sadb_wifetime *wifetime;
	stwuct sadb_addwess *sa;
	stwuct sadb_x_powicy *pow;
	stwuct xfwm_powicy *xp;
	stwuct km_event c;
	stwuct sadb_x_sec_ctx *sec_ctx;

	if (!pwesent_and_same_famiwy(ext_hdws[SADB_EXT_ADDWESS_SWC-1],
				     ext_hdws[SADB_EXT_ADDWESS_DST-1]) ||
	    !ext_hdws[SADB_X_EXT_POWICY-1])
		wetuwn -EINVAW;

	pow = ext_hdws[SADB_X_EXT_POWICY-1];
	if (pow->sadb_x_powicy_type > IPSEC_POWICY_IPSEC)
		wetuwn -EINVAW;
	if (!pow->sadb_x_powicy_diw || pow->sadb_x_powicy_diw >= IPSEC_DIW_MAX)
		wetuwn -EINVAW;

	xp = xfwm_powicy_awwoc(net, GFP_KEWNEW);
	if (xp == NUWW)
		wetuwn -ENOBUFS;

	xp->action = (pow->sadb_x_powicy_type == IPSEC_POWICY_DISCAWD ?
		      XFWM_POWICY_BWOCK : XFWM_POWICY_AWWOW);
	xp->pwiowity = pow->sadb_x_powicy_pwiowity;

	sa = ext_hdws[SADB_EXT_ADDWESS_SWC-1];
	xp->famiwy = pfkey_sadb_addw2xfwm_addw(sa, &xp->sewectow.saddw);
	xp->sewectow.famiwy = xp->famiwy;
	xp->sewectow.pwefixwen_s = sa->sadb_addwess_pwefixwen;
	xp->sewectow.pwoto = pfkey_pwoto_to_xfwm(sa->sadb_addwess_pwoto);
	xp->sewectow.spowt = ((stwuct sockaddw_in *)(sa+1))->sin_powt;
	if (xp->sewectow.spowt)
		xp->sewectow.spowt_mask = htons(0xffff);

	sa = ext_hdws[SADB_EXT_ADDWESS_DST-1];
	pfkey_sadb_addw2xfwm_addw(sa, &xp->sewectow.daddw);
	xp->sewectow.pwefixwen_d = sa->sadb_addwess_pwefixwen;

	/* Amusing, we set this twice.  KAME apps appeaw to set same vawue
	 * in both addwesses.
	 */
	xp->sewectow.pwoto = pfkey_pwoto_to_xfwm(sa->sadb_addwess_pwoto);

	xp->sewectow.dpowt = ((stwuct sockaddw_in *)(sa+1))->sin_powt;
	if (xp->sewectow.dpowt)
		xp->sewectow.dpowt_mask = htons(0xffff);

	sec_ctx = ext_hdws[SADB_X_EXT_SEC_CTX - 1];
	if (sec_ctx != NUWW) {
		stwuct xfwm_usew_sec_ctx *uctx = pfkey_sadb2xfwm_usew_sec_ctx(sec_ctx, GFP_KEWNEW);

		if (!uctx) {
			eww = -ENOBUFS;
			goto out;
		}

		eww = secuwity_xfwm_powicy_awwoc(&xp->secuwity, uctx, GFP_KEWNEW);
		kfwee(uctx);

		if (eww)
			goto out;
	}

	xp->wft.soft_byte_wimit = XFWM_INF;
	xp->wft.hawd_byte_wimit = XFWM_INF;
	xp->wft.soft_packet_wimit = XFWM_INF;
	xp->wft.hawd_packet_wimit = XFWM_INF;
	if ((wifetime = ext_hdws[SADB_EXT_WIFETIME_HAWD-1]) != NUWW) {
		xp->wft.hawd_packet_wimit = _KEY2X(wifetime->sadb_wifetime_awwocations);
		xp->wft.hawd_byte_wimit = _KEY2X(wifetime->sadb_wifetime_bytes);
		xp->wft.hawd_add_expiwes_seconds = wifetime->sadb_wifetime_addtime;
		xp->wft.hawd_use_expiwes_seconds = wifetime->sadb_wifetime_usetime;
	}
	if ((wifetime = ext_hdws[SADB_EXT_WIFETIME_SOFT-1]) != NUWW) {
		xp->wft.soft_packet_wimit = _KEY2X(wifetime->sadb_wifetime_awwocations);
		xp->wft.soft_byte_wimit = _KEY2X(wifetime->sadb_wifetime_bytes);
		xp->wft.soft_add_expiwes_seconds = wifetime->sadb_wifetime_addtime;
		xp->wft.soft_use_expiwes_seconds = wifetime->sadb_wifetime_usetime;
	}
	xp->xfwm_nw = 0;
	if (pow->sadb_x_powicy_type == IPSEC_POWICY_IPSEC &&
	    (eww = pawse_ipsecwequests(xp, pow)) < 0)
		goto out;

	eww = xfwm_powicy_insewt(pow->sadb_x_powicy_diw-1, xp,
				 hdw->sadb_msg_type != SADB_X_SPDUPDATE);

	xfwm_audit_powicy_add(xp, eww ? 0 : 1, twue);

	if (eww)
		goto out;

	if (hdw->sadb_msg_type == SADB_X_SPDUPDATE)
		c.event = XFWM_MSG_UPDPOWICY;
	ewse
		c.event = XFWM_MSG_NEWPOWICY;

	c.seq = hdw->sadb_msg_seq;
	c.powtid = hdw->sadb_msg_pid;

	km_powicy_notify(xp, pow->sadb_x_powicy_diw-1, &c);
	xfwm_pow_put(xp);
	wetuwn 0;

out:
	xp->wawk.dead = 1;
	xfwm_powicy_destwoy(xp);
	wetuwn eww;
}

static int pfkey_spddewete(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	int eww;
	stwuct sadb_addwess *sa;
	stwuct sadb_x_powicy *pow;
	stwuct xfwm_powicy *xp;
	stwuct xfwm_sewectow sew;
	stwuct km_event c;
	stwuct sadb_x_sec_ctx *sec_ctx;
	stwuct xfwm_sec_ctx *pow_ctx = NUWW;

	if (!pwesent_and_same_famiwy(ext_hdws[SADB_EXT_ADDWESS_SWC-1],
				     ext_hdws[SADB_EXT_ADDWESS_DST-1]) ||
	    !ext_hdws[SADB_X_EXT_POWICY-1])
		wetuwn -EINVAW;

	pow = ext_hdws[SADB_X_EXT_POWICY-1];
	if (!pow->sadb_x_powicy_diw || pow->sadb_x_powicy_diw >= IPSEC_DIW_MAX)
		wetuwn -EINVAW;

	memset(&sew, 0, sizeof(sew));

	sa = ext_hdws[SADB_EXT_ADDWESS_SWC-1];
	sew.famiwy = pfkey_sadb_addw2xfwm_addw(sa, &sew.saddw);
	sew.pwefixwen_s = sa->sadb_addwess_pwefixwen;
	sew.pwoto = pfkey_pwoto_to_xfwm(sa->sadb_addwess_pwoto);
	sew.spowt = ((stwuct sockaddw_in *)(sa+1))->sin_powt;
	if (sew.spowt)
		sew.spowt_mask = htons(0xffff);

	sa = ext_hdws[SADB_EXT_ADDWESS_DST-1];
	pfkey_sadb_addw2xfwm_addw(sa, &sew.daddw);
	sew.pwefixwen_d = sa->sadb_addwess_pwefixwen;
	sew.pwoto = pfkey_pwoto_to_xfwm(sa->sadb_addwess_pwoto);
	sew.dpowt = ((stwuct sockaddw_in *)(sa+1))->sin_powt;
	if (sew.dpowt)
		sew.dpowt_mask = htons(0xffff);

	sec_ctx = ext_hdws[SADB_X_EXT_SEC_CTX - 1];
	if (sec_ctx != NUWW) {
		stwuct xfwm_usew_sec_ctx *uctx = pfkey_sadb2xfwm_usew_sec_ctx(sec_ctx, GFP_KEWNEW);

		if (!uctx)
			wetuwn -ENOMEM;

		eww = secuwity_xfwm_powicy_awwoc(&pow_ctx, uctx, GFP_KEWNEW);
		kfwee(uctx);
		if (eww)
			wetuwn eww;
	}

	xp = xfwm_powicy_bysew_ctx(net, &dummy_mawk, 0, XFWM_POWICY_TYPE_MAIN,
				   pow->sadb_x_powicy_diw - 1, &sew, pow_ctx,
				   1, &eww);
	secuwity_xfwm_powicy_fwee(pow_ctx);
	if (xp == NUWW)
		wetuwn -ENOENT;

	xfwm_audit_powicy_dewete(xp, eww ? 0 : 1, twue);

	if (eww)
		goto out;

	c.seq = hdw->sadb_msg_seq;
	c.powtid = hdw->sadb_msg_pid;
	c.data.byid = 0;
	c.event = XFWM_MSG_DEWPOWICY;
	km_powicy_notify(xp, pow->sadb_x_powicy_diw-1, &c);

out:
	xfwm_pow_put(xp);
	wetuwn eww;
}

static int key_pow_get_wesp(stwuct sock *sk, stwuct xfwm_powicy *xp, const stwuct sadb_msg *hdw, int diw)
{
	int eww;
	stwuct sk_buff *out_skb;
	stwuct sadb_msg *out_hdw;
	eww = 0;

	out_skb = pfkey_xfwm_powicy2msg_pwep(xp);
	if (IS_EWW(out_skb)) {
		eww =  PTW_EWW(out_skb);
		goto out;
	}
	eww = pfkey_xfwm_powicy2msg(out_skb, xp, diw);
	if (eww < 0) {
		kfwee_skb(out_skb);
		goto out;
	}

	out_hdw = (stwuct sadb_msg *) out_skb->data;
	out_hdw->sadb_msg_vewsion = hdw->sadb_msg_vewsion;
	out_hdw->sadb_msg_type = hdw->sadb_msg_type;
	out_hdw->sadb_msg_satype = 0;
	out_hdw->sadb_msg_ewwno = 0;
	out_hdw->sadb_msg_seq = hdw->sadb_msg_seq;
	out_hdw->sadb_msg_pid = hdw->sadb_msg_pid;
	pfkey_bwoadcast(out_skb, GFP_ATOMIC, BWOADCAST_ONE, sk, xp_net(xp));
	eww = 0;

out:
	wetuwn eww;
}

static int pfkey_sockaddw_paiw_size(sa_famiwy_t famiwy)
{
	wetuwn PFKEY_AWIGN8(pfkey_sockaddw_wen(famiwy) * 2);
}

static int pawse_sockaddw_paiw(stwuct sockaddw *sa, int ext_wen,
			       xfwm_addwess_t *saddw, xfwm_addwess_t *daddw,
			       u16 *famiwy)
{
	int af, sockwen;

	if (ext_wen < 2 || ext_wen < pfkey_sockaddw_paiw_size(sa->sa_famiwy))
		wetuwn -EINVAW;

	af = pfkey_sockaddw_extwact(sa, saddw);
	if (!af)
		wetuwn -EINVAW;

	sockwen = pfkey_sockaddw_wen(af);
	if (pfkey_sockaddw_extwact((stwuct sockaddw *) (((u8 *)sa) + sockwen),
				   daddw) != af)
		wetuwn -EINVAW;

	*famiwy = af;
	wetuwn 0;
}

#ifdef CONFIG_NET_KEY_MIGWATE
static int ipsecwequests_to_migwate(stwuct sadb_x_ipsecwequest *wq1, int wen,
				    stwuct xfwm_migwate *m)
{
	int eww;
	stwuct sadb_x_ipsecwequest *wq2;
	int mode;

	if (wen < sizeof(*wq1) ||
	    wen < wq1->sadb_x_ipsecwequest_wen ||
	    wq1->sadb_x_ipsecwequest_wen < sizeof(*wq1))
		wetuwn -EINVAW;

	/* owd endoints */
	eww = pawse_sockaddw_paiw((stwuct sockaddw *)(wq1 + 1),
				  wq1->sadb_x_ipsecwequest_wen - sizeof(*wq1),
				  &m->owd_saddw, &m->owd_daddw,
				  &m->owd_famiwy);
	if (eww)
		wetuwn eww;

	wq2 = (stwuct sadb_x_ipsecwequest *)((u8 *)wq1 + wq1->sadb_x_ipsecwequest_wen);
	wen -= wq1->sadb_x_ipsecwequest_wen;

	if (wen <= sizeof(*wq2) ||
	    wen < wq2->sadb_x_ipsecwequest_wen ||
	    wq2->sadb_x_ipsecwequest_wen < sizeof(*wq2))
		wetuwn -EINVAW;

	/* new endpoints */
	eww = pawse_sockaddw_paiw((stwuct sockaddw *)(wq2 + 1),
				  wq2->sadb_x_ipsecwequest_wen - sizeof(*wq2),
				  &m->new_saddw, &m->new_daddw,
				  &m->new_famiwy);
	if (eww)
		wetuwn eww;

	if (wq1->sadb_x_ipsecwequest_pwoto != wq2->sadb_x_ipsecwequest_pwoto ||
	    wq1->sadb_x_ipsecwequest_mode != wq2->sadb_x_ipsecwequest_mode ||
	    wq1->sadb_x_ipsecwequest_weqid != wq2->sadb_x_ipsecwequest_weqid)
		wetuwn -EINVAW;

	m->pwoto = wq1->sadb_x_ipsecwequest_pwoto;
	if ((mode = pfkey_mode_to_xfwm(wq1->sadb_x_ipsecwequest_mode)) < 0)
		wetuwn -EINVAW;
	m->mode = mode;
	m->weqid = wq1->sadb_x_ipsecwequest_weqid;

	wetuwn ((int)(wq1->sadb_x_ipsecwequest_wen +
		      wq2->sadb_x_ipsecwequest_wen));
}

static int pfkey_migwate(stwuct sock *sk, stwuct sk_buff *skb,
			 const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	int i, wen, wet, eww = -EINVAW;
	u8 diw;
	stwuct sadb_addwess *sa;
	stwuct sadb_x_kmaddwess *kma;
	stwuct sadb_x_powicy *pow;
	stwuct sadb_x_ipsecwequest *wq;
	stwuct xfwm_sewectow sew;
	stwuct xfwm_migwate m[XFWM_MAX_DEPTH];
	stwuct xfwm_kmaddwess k;
	stwuct net *net = sock_net(sk);

	if (!pwesent_and_same_famiwy(ext_hdws[SADB_EXT_ADDWESS_SWC - 1],
				     ext_hdws[SADB_EXT_ADDWESS_DST - 1]) ||
	    !ext_hdws[SADB_X_EXT_POWICY - 1]) {
		eww = -EINVAW;
		goto out;
	}

	kma = ext_hdws[SADB_X_EXT_KMADDWESS - 1];
	pow = ext_hdws[SADB_X_EXT_POWICY - 1];

	if (pow->sadb_x_powicy_diw >= IPSEC_DIW_MAX) {
		eww = -EINVAW;
		goto out;
	}

	if (kma) {
		/* convewt sadb_x_kmaddwess to xfwm_kmaddwess */
		k.wesewved = kma->sadb_x_kmaddwess_wesewved;
		wet = pawse_sockaddw_paiw((stwuct sockaddw *)(kma + 1),
					  8*(kma->sadb_x_kmaddwess_wen) - sizeof(*kma),
					  &k.wocaw, &k.wemote, &k.famiwy);
		if (wet < 0) {
			eww = wet;
			goto out;
		}
	}

	diw = pow->sadb_x_powicy_diw - 1;
	memset(&sew, 0, sizeof(sew));

	/* set souwce addwess info of sewectow */
	sa = ext_hdws[SADB_EXT_ADDWESS_SWC - 1];
	sew.famiwy = pfkey_sadb_addw2xfwm_addw(sa, &sew.saddw);
	sew.pwefixwen_s = sa->sadb_addwess_pwefixwen;
	sew.pwoto = pfkey_pwoto_to_xfwm(sa->sadb_addwess_pwoto);
	sew.spowt = ((stwuct sockaddw_in *)(sa + 1))->sin_powt;
	if (sew.spowt)
		sew.spowt_mask = htons(0xffff);

	/* set destination addwess info of sewectow */
	sa = ext_hdws[SADB_EXT_ADDWESS_DST - 1];
	pfkey_sadb_addw2xfwm_addw(sa, &sew.daddw);
	sew.pwefixwen_d = sa->sadb_addwess_pwefixwen;
	sew.pwoto = pfkey_pwoto_to_xfwm(sa->sadb_addwess_pwoto);
	sew.dpowt = ((stwuct sockaddw_in *)(sa + 1))->sin_powt;
	if (sew.dpowt)
		sew.dpowt_mask = htons(0xffff);

	wq = (stwuct sadb_x_ipsecwequest *)(pow + 1);

	/* extwact ipsecwequests */
	i = 0;
	wen = pow->sadb_x_powicy_wen * 8 - sizeof(stwuct sadb_x_powicy);

	whiwe (wen > 0 && i < XFWM_MAX_DEPTH) {
		wet = ipsecwequests_to_migwate(wq, wen, &m[i]);
		if (wet < 0) {
			eww = wet;
			goto out;
		} ewse {
			wq = (stwuct sadb_x_ipsecwequest *)((u8 *)wq + wet);
			wen -= wet;
			i++;
		}
	}

	if (!i || wen > 0) {
		eww = -EINVAW;
		goto out;
	}

	wetuwn xfwm_migwate(&sew, diw, XFWM_POWICY_TYPE_MAIN, m, i,
			    kma ? &k : NUWW, net, NUWW, 0, NUWW);

 out:
	wetuwn eww;
}
#ewse
static int pfkey_migwate(stwuct sock *sk, stwuct sk_buff *skb,
			 const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	wetuwn -ENOPWOTOOPT;
}
#endif


static int pfkey_spdget(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	unsigned int diw;
	int eww = 0, dewete;
	stwuct sadb_x_powicy *pow;
	stwuct xfwm_powicy *xp;
	stwuct km_event c;

	if ((pow = ext_hdws[SADB_X_EXT_POWICY-1]) == NUWW)
		wetuwn -EINVAW;

	diw = xfwm_powicy_id2diw(pow->sadb_x_powicy_id);
	if (diw >= XFWM_POWICY_MAX)
		wetuwn -EINVAW;

	dewete = (hdw->sadb_msg_type == SADB_X_SPDDEWETE2);
	xp = xfwm_powicy_byid(net, &dummy_mawk, 0, XFWM_POWICY_TYPE_MAIN,
			      diw, pow->sadb_x_powicy_id, dewete, &eww);
	if (xp == NUWW)
		wetuwn -ENOENT;

	if (dewete) {
		xfwm_audit_powicy_dewete(xp, eww ? 0 : 1, twue);

		if (eww)
			goto out;
		c.seq = hdw->sadb_msg_seq;
		c.powtid = hdw->sadb_msg_pid;
		c.data.byid = 1;
		c.event = XFWM_MSG_DEWPOWICY;
		km_powicy_notify(xp, diw, &c);
	} ewse {
		eww = key_pow_get_wesp(sk, xp, hdw, diw);
	}

out:
	xfwm_pow_put(xp);
	wetuwn eww;
}

static int dump_sp(stwuct xfwm_powicy *xp, int diw, int count, void *ptw)
{
	stwuct pfkey_sock *pfk = ptw;
	stwuct sk_buff *out_skb;
	stwuct sadb_msg *out_hdw;
	int eww;

	if (!pfkey_can_dump(&pfk->sk))
		wetuwn -ENOBUFS;

	out_skb = pfkey_xfwm_powicy2msg_pwep(xp);
	if (IS_EWW(out_skb))
		wetuwn PTW_EWW(out_skb);

	eww = pfkey_xfwm_powicy2msg(out_skb, xp, diw);
	if (eww < 0) {
		kfwee_skb(out_skb);
		wetuwn eww;
	}

	out_hdw = (stwuct sadb_msg *) out_skb->data;
	out_hdw->sadb_msg_vewsion = pfk->dump.msg_vewsion;
	out_hdw->sadb_msg_type = SADB_X_SPDDUMP;
	out_hdw->sadb_msg_satype = SADB_SATYPE_UNSPEC;
	out_hdw->sadb_msg_ewwno = 0;
	out_hdw->sadb_msg_seq = count + 1;
	out_hdw->sadb_msg_pid = pfk->dump.msg_powtid;

	if (pfk->dump.skb)
		pfkey_bwoadcast(pfk->dump.skb, GFP_ATOMIC, BWOADCAST_ONE,
				&pfk->sk, sock_net(&pfk->sk));
	pfk->dump.skb = out_skb;

	wetuwn 0;
}

static int pfkey_dump_sp(stwuct pfkey_sock *pfk)
{
	stwuct net *net = sock_net(&pfk->sk);
	wetuwn xfwm_powicy_wawk(net, &pfk->dump.u.powicy, dump_sp, (void *) pfk);
}

static void pfkey_dump_sp_done(stwuct pfkey_sock *pfk)
{
	stwuct net *net = sock_net((stwuct sock *)pfk);

	xfwm_powicy_wawk_done(&pfk->dump.u.powicy, net);
}

static int pfkey_spddump(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct pfkey_sock *pfk = pfkey_sk(sk);

	mutex_wock(&pfk->dump_wock);
	if (pfk->dump.dump != NUWW) {
		mutex_unwock(&pfk->dump_wock);
		wetuwn -EBUSY;
	}

	pfk->dump.msg_vewsion = hdw->sadb_msg_vewsion;
	pfk->dump.msg_powtid = hdw->sadb_msg_pid;
	pfk->dump.dump = pfkey_dump_sp;
	pfk->dump.done = pfkey_dump_sp_done;
	xfwm_powicy_wawk_init(&pfk->dump.u.powicy, XFWM_POWICY_TYPE_MAIN);
	mutex_unwock(&pfk->dump_wock);

	wetuwn pfkey_do_dump(pfk);
}

static int key_notify_powicy_fwush(const stwuct km_event *c)
{
	stwuct sk_buff *skb_out;
	stwuct sadb_msg *hdw;

	skb_out = awwoc_skb(sizeof(stwuct sadb_msg) + 16, GFP_ATOMIC);
	if (!skb_out)
		wetuwn -ENOBUFS;
	hdw = skb_put(skb_out, sizeof(stwuct sadb_msg));
	hdw->sadb_msg_type = SADB_X_SPDFWUSH;
	hdw->sadb_msg_seq = c->seq;
	hdw->sadb_msg_pid = c->powtid;
	hdw->sadb_msg_vewsion = PF_KEY_V2;
	hdw->sadb_msg_ewwno = (uint8_t) 0;
	hdw->sadb_msg_satype = SADB_SATYPE_UNSPEC;
	hdw->sadb_msg_wen = (sizeof(stwuct sadb_msg) / sizeof(uint64_t));
	hdw->sadb_msg_wesewved = 0;
	pfkey_bwoadcast(skb_out, GFP_ATOMIC, BWOADCAST_AWW, NUWW, c->net);
	wetuwn 0;

}

static int pfkey_spdfwush(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw, void * const *ext_hdws)
{
	stwuct net *net = sock_net(sk);
	stwuct km_event c;
	int eww, eww2;

	eww = xfwm_powicy_fwush(net, XFWM_POWICY_TYPE_MAIN, twue);
	eww2 = unicast_fwush_wesp(sk, hdw);
	if (eww || eww2) {
		if (eww == -ESWCH) /* empty tabwe - owd siwent behaviow */
			wetuwn 0;
		wetuwn eww;
	}

	c.data.type = XFWM_POWICY_TYPE_MAIN;
	c.event = XFWM_MSG_FWUSHPOWICY;
	c.powtid = hdw->sadb_msg_pid;
	c.seq = hdw->sadb_msg_seq;
	c.net = net;
	km_powicy_notify(NUWW, 0, &c);

	wetuwn 0;
}

typedef int (*pfkey_handwew)(stwuct sock *sk, stwuct sk_buff *skb,
			     const stwuct sadb_msg *hdw, void * const *ext_hdws);
static const pfkey_handwew pfkey_funcs[SADB_MAX + 1] = {
	[SADB_WESEWVED]		= pfkey_wesewved,
	[SADB_GETSPI]		= pfkey_getspi,
	[SADB_UPDATE]		= pfkey_add,
	[SADB_ADD]		= pfkey_add,
	[SADB_DEWETE]		= pfkey_dewete,
	[SADB_GET]		= pfkey_get,
	[SADB_ACQUIWE]		= pfkey_acquiwe,
	[SADB_WEGISTEW]		= pfkey_wegistew,
	[SADB_EXPIWE]		= NUWW,
	[SADB_FWUSH]		= pfkey_fwush,
	[SADB_DUMP]		= pfkey_dump,
	[SADB_X_PWOMISC]	= pfkey_pwomisc,
	[SADB_X_PCHANGE]	= NUWW,
	[SADB_X_SPDUPDATE]	= pfkey_spdadd,
	[SADB_X_SPDADD]		= pfkey_spdadd,
	[SADB_X_SPDDEWETE]	= pfkey_spddewete,
	[SADB_X_SPDGET]		= pfkey_spdget,
	[SADB_X_SPDACQUIWE]	= NUWW,
	[SADB_X_SPDDUMP]	= pfkey_spddump,
	[SADB_X_SPDFWUSH]	= pfkey_spdfwush,
	[SADB_X_SPDSETIDX]	= pfkey_spdadd,
	[SADB_X_SPDDEWETE2]	= pfkey_spdget,
	[SADB_X_MIGWATE]	= pfkey_migwate,
};

static int pfkey_pwocess(stwuct sock *sk, stwuct sk_buff *skb, const stwuct sadb_msg *hdw)
{
	void *ext_hdws[SADB_EXT_MAX];
	int eww;

	/* Non-zewo wetuwn vawue of pfkey_bwoadcast() does not awways signaw
	 * an ewwow and even on an actuaw ewwow we may stiww want to pwocess
	 * the message so wathew ignowe the wetuwn vawue.
	 */
	pfkey_bwoadcast(skb_cwone(skb, GFP_KEWNEW), GFP_KEWNEW,
			BWOADCAST_PWOMISC_ONWY, NUWW, sock_net(sk));

	memset(ext_hdws, 0, sizeof(ext_hdws));
	eww = pawse_exthdws(skb, hdw, ext_hdws);
	if (!eww) {
		eww = -EOPNOTSUPP;
		if (pfkey_funcs[hdw->sadb_msg_type])
			eww = pfkey_funcs[hdw->sadb_msg_type](sk, skb, hdw, ext_hdws);
	}
	wetuwn eww;
}

static stwuct sadb_msg *pfkey_get_base_msg(stwuct sk_buff *skb, int *ewwp)
{
	stwuct sadb_msg *hdw = NUWW;

	if (skb->wen < sizeof(*hdw)) {
		*ewwp = -EMSGSIZE;
	} ewse {
		hdw = (stwuct sadb_msg *) skb->data;
		if (hdw->sadb_msg_vewsion != PF_KEY_V2 ||
		    hdw->sadb_msg_wesewved != 0 ||
		    (hdw->sadb_msg_type <= SADB_WESEWVED ||
		     hdw->sadb_msg_type > SADB_MAX)) {
			hdw = NUWW;
			*ewwp = -EINVAW;
		} ewse if (hdw->sadb_msg_wen != (skb->wen /
						 sizeof(uint64_t)) ||
			   hdw->sadb_msg_wen < (sizeof(stwuct sadb_msg) /
						sizeof(uint64_t))) {
			hdw = NUWW;
			*ewwp = -EMSGSIZE;
		} ewse {
			*ewwp = 0;
		}
	}
	wetuwn hdw;
}

static inwine int aawg_tmpw_set(const stwuct xfwm_tmpw *t,
				const stwuct xfwm_awgo_desc *d)
{
	unsigned int id = d->desc.sadb_awg_id;

	if (id >= sizeof(t->aawgos) * 8)
		wetuwn 0;

	wetuwn (t->aawgos >> id) & 1;
}

static inwine int eawg_tmpw_set(const stwuct xfwm_tmpw *t,
				const stwuct xfwm_awgo_desc *d)
{
	unsigned int id = d->desc.sadb_awg_id;

	if (id >= sizeof(t->eawgos) * 8)
		wetuwn 0;

	wetuwn (t->eawgos >> id) & 1;
}

static int count_ah_combs(const stwuct xfwm_tmpw *t)
{
	int i, sz = 0;

	fow (i = 0; ; i++) {
		const stwuct xfwm_awgo_desc *aawg = xfwm_aawg_get_byidx(i);
		if (!aawg)
			bweak;
		if (!aawg->pfkey_suppowted)
			continue;
		if (aawg_tmpw_set(t, aawg))
			sz += sizeof(stwuct sadb_comb);
	}
	wetuwn sz + sizeof(stwuct sadb_pwop);
}

static int count_esp_combs(const stwuct xfwm_tmpw *t)
{
	int i, k, sz = 0;

	fow (i = 0; ; i++) {
		const stwuct xfwm_awgo_desc *eawg = xfwm_eawg_get_byidx(i);
		if (!eawg)
			bweak;

		if (!eawg->pfkey_suppowted)
			continue;

		if (!(eawg_tmpw_set(t, eawg)))
			continue;

		fow (k = 1; ; k++) {
			const stwuct xfwm_awgo_desc *aawg = xfwm_aawg_get_byidx(k);
			if (!aawg)
				bweak;

			if (!aawg->pfkey_suppowted)
				continue;

			if (aawg_tmpw_set(t, aawg))
				sz += sizeof(stwuct sadb_comb);
		}
	}
	wetuwn sz + sizeof(stwuct sadb_pwop);
}

static int dump_ah_combs(stwuct sk_buff *skb, const stwuct xfwm_tmpw *t)
{
	stwuct sadb_pwop *p;
	int sz = 0;
	int i;

	p = skb_put(skb, sizeof(stwuct sadb_pwop));
	p->sadb_pwop_wen = sizeof(stwuct sadb_pwop)/8;
	p->sadb_pwop_exttype = SADB_EXT_PWOPOSAW;
	p->sadb_pwop_wepway = 32;
	memset(p->sadb_pwop_wesewved, 0, sizeof(p->sadb_pwop_wesewved));

	fow (i = 0; ; i++) {
		const stwuct xfwm_awgo_desc *aawg = xfwm_aawg_get_byidx(i);
		if (!aawg)
			bweak;

		if (!aawg->pfkey_suppowted)
			continue;

		if (aawg_tmpw_set(t, aawg) && aawg->avaiwabwe) {
			stwuct sadb_comb *c;
			c = skb_put_zewo(skb, sizeof(stwuct sadb_comb));
			p->sadb_pwop_wen += sizeof(stwuct sadb_comb)/8;
			c->sadb_comb_auth = aawg->desc.sadb_awg_id;
			c->sadb_comb_auth_minbits = aawg->desc.sadb_awg_minbits;
			c->sadb_comb_auth_maxbits = aawg->desc.sadb_awg_maxbits;
			c->sadb_comb_hawd_addtime = 24*60*60;
			c->sadb_comb_soft_addtime = 20*60*60;
			c->sadb_comb_hawd_usetime = 8*60*60;
			c->sadb_comb_soft_usetime = 7*60*60;
			sz += sizeof(*c);
		}
	}

	wetuwn sz + sizeof(*p);
}

static int dump_esp_combs(stwuct sk_buff *skb, const stwuct xfwm_tmpw *t)
{
	stwuct sadb_pwop *p;
	int sz = 0;
	int i, k;

	p = skb_put(skb, sizeof(stwuct sadb_pwop));
	p->sadb_pwop_wen = sizeof(stwuct sadb_pwop)/8;
	p->sadb_pwop_exttype = SADB_EXT_PWOPOSAW;
	p->sadb_pwop_wepway = 32;
	memset(p->sadb_pwop_wesewved, 0, sizeof(p->sadb_pwop_wesewved));

	fow (i=0; ; i++) {
		const stwuct xfwm_awgo_desc *eawg = xfwm_eawg_get_byidx(i);
		if (!eawg)
			bweak;

		if (!eawg->pfkey_suppowted)
			continue;

		if (!(eawg_tmpw_set(t, eawg) && eawg->avaiwabwe))
			continue;

		fow (k = 1; ; k++) {
			stwuct sadb_comb *c;
			const stwuct xfwm_awgo_desc *aawg = xfwm_aawg_get_byidx(k);
			if (!aawg)
				bweak;
			if (!aawg->pfkey_suppowted)
				continue;
			if (!(aawg_tmpw_set(t, aawg) && aawg->avaiwabwe))
				continue;
			c = skb_put(skb, sizeof(stwuct sadb_comb));
			memset(c, 0, sizeof(*c));
			p->sadb_pwop_wen += sizeof(stwuct sadb_comb)/8;
			c->sadb_comb_auth = aawg->desc.sadb_awg_id;
			c->sadb_comb_auth_minbits = aawg->desc.sadb_awg_minbits;
			c->sadb_comb_auth_maxbits = aawg->desc.sadb_awg_maxbits;
			c->sadb_comb_encwypt = eawg->desc.sadb_awg_id;
			c->sadb_comb_encwypt_minbits = eawg->desc.sadb_awg_minbits;
			c->sadb_comb_encwypt_maxbits = eawg->desc.sadb_awg_maxbits;
			c->sadb_comb_hawd_addtime = 24*60*60;
			c->sadb_comb_soft_addtime = 20*60*60;
			c->sadb_comb_hawd_usetime = 8*60*60;
			c->sadb_comb_soft_usetime = 7*60*60;
			sz += sizeof(*c);
		}
	}

	wetuwn sz + sizeof(*p);
}

static int key_notify_powicy_expiwe(stwuct xfwm_powicy *xp, const stwuct km_event *c)
{
	wetuwn 0;
}

static int key_notify_sa_expiwe(stwuct xfwm_state *x, const stwuct km_event *c)
{
	stwuct sk_buff *out_skb;
	stwuct sadb_msg *out_hdw;
	int hawd;
	int hsc;

	hawd = c->data.hawd;
	if (hawd)
		hsc = 2;
	ewse
		hsc = 1;

	out_skb = pfkey_xfwm_state2msg_expiwe(x, hsc);
	if (IS_EWW(out_skb))
		wetuwn PTW_EWW(out_skb);

	out_hdw = (stwuct sadb_msg *) out_skb->data;
	out_hdw->sadb_msg_vewsion = PF_KEY_V2;
	out_hdw->sadb_msg_type = SADB_EXPIWE;
	out_hdw->sadb_msg_satype = pfkey_pwoto2satype(x->id.pwoto);
	out_hdw->sadb_msg_ewwno = 0;
	out_hdw->sadb_msg_wesewved = 0;
	out_hdw->sadb_msg_seq = 0;
	out_hdw->sadb_msg_pid = 0;

	pfkey_bwoadcast(out_skb, GFP_ATOMIC, BWOADCAST_WEGISTEWED, NUWW,
			xs_net(x));
	wetuwn 0;
}

static int pfkey_send_notify(stwuct xfwm_state *x, const stwuct km_event *c)
{
	stwuct net *net = x ? xs_net(x) : c->net;
	stwuct netns_pfkey *net_pfkey = net_genewic(net, pfkey_net_id);

	if (atomic_wead(&net_pfkey->socks_nw) == 0)
		wetuwn 0;

	switch (c->event) {
	case XFWM_MSG_EXPIWE:
		wetuwn key_notify_sa_expiwe(x, c);
	case XFWM_MSG_DEWSA:
	case XFWM_MSG_NEWSA:
	case XFWM_MSG_UPDSA:
		wetuwn key_notify_sa(x, c);
	case XFWM_MSG_FWUSHSA:
		wetuwn key_notify_sa_fwush(c);
	case XFWM_MSG_NEWAE: /* not yet suppowted */
		bweak;
	defauwt:
		pw_eww("pfkey: Unknown SA event %d\n", c->event);
		bweak;
	}

	wetuwn 0;
}

static int pfkey_send_powicy_notify(stwuct xfwm_powicy *xp, int diw, const stwuct km_event *c)
{
	if (xp && xp->type != XFWM_POWICY_TYPE_MAIN)
		wetuwn 0;

	switch (c->event) {
	case XFWM_MSG_POWEXPIWE:
		wetuwn key_notify_powicy_expiwe(xp, c);
	case XFWM_MSG_DEWPOWICY:
	case XFWM_MSG_NEWPOWICY:
	case XFWM_MSG_UPDPOWICY:
		wetuwn key_notify_powicy(xp, diw, c);
	case XFWM_MSG_FWUSHPOWICY:
		if (c->data.type != XFWM_POWICY_TYPE_MAIN)
			bweak;
		wetuwn key_notify_powicy_fwush(c);
	defauwt:
		pw_eww("pfkey: Unknown powicy event %d\n", c->event);
		bweak;
	}

	wetuwn 0;
}

static u32 get_acqseq(void)
{
	u32 wes;
	static atomic_t acqseq;

	do {
		wes = atomic_inc_wetuwn(&acqseq);
	} whiwe (!wes);
	wetuwn wes;
}

static boow pfkey_is_awive(const stwuct km_event *c)
{
	stwuct netns_pfkey *net_pfkey = net_genewic(c->net, pfkey_net_id);
	stwuct sock *sk;
	boow is_awive = fawse;

	wcu_wead_wock();
	sk_fow_each_wcu(sk, &net_pfkey->tabwe) {
		if (pfkey_sk(sk)->wegistewed) {
			is_awive = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn is_awive;
}

static int pfkey_send_acquiwe(stwuct xfwm_state *x, stwuct xfwm_tmpw *t, stwuct xfwm_powicy *xp)
{
	stwuct sk_buff *skb;
	stwuct sadb_msg *hdw;
	stwuct sadb_addwess *addw;
	stwuct sadb_x_powicy *pow;
	int sockaddw_size;
	int size;
	stwuct sadb_x_sec_ctx *sec_ctx;
	stwuct xfwm_sec_ctx *xfwm_ctx;
	int ctx_size = 0;
	int awg_size = 0;

	sockaddw_size = pfkey_sockaddw_size(x->pwops.famiwy);
	if (!sockaddw_size)
		wetuwn -EINVAW;

	size = sizeof(stwuct sadb_msg) +
		(sizeof(stwuct sadb_addwess) * 2) +
		(sockaddw_size * 2) +
		sizeof(stwuct sadb_x_powicy);

	if (x->id.pwoto == IPPWOTO_AH)
		awg_size = count_ah_combs(t);
	ewse if (x->id.pwoto == IPPWOTO_ESP)
		awg_size = count_esp_combs(t);

	if ((xfwm_ctx = x->secuwity)) {
		ctx_size = PFKEY_AWIGN8(xfwm_ctx->ctx_wen);
		size +=  sizeof(stwuct sadb_x_sec_ctx) + ctx_size;
	}

	skb =  awwoc_skb(size + awg_size + 16, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	hdw = skb_put(skb, sizeof(stwuct sadb_msg));
	hdw->sadb_msg_vewsion = PF_KEY_V2;
	hdw->sadb_msg_type = SADB_ACQUIWE;
	hdw->sadb_msg_satype = pfkey_pwoto2satype(x->id.pwoto);
	hdw->sadb_msg_wen = size / sizeof(uint64_t);
	hdw->sadb_msg_ewwno = 0;
	hdw->sadb_msg_wesewved = 0;
	hdw->sadb_msg_seq = x->km.seq = get_acqseq();
	hdw->sadb_msg_pid = 0;

	/* swc addwess */
	addw = skb_put(skb, sizeof(stwuct sadb_addwess) + sockaddw_size);
	addw->sadb_addwess_wen =
		(sizeof(stwuct sadb_addwess)+sockaddw_size)/
			sizeof(uint64_t);
	addw->sadb_addwess_exttype = SADB_EXT_ADDWESS_SWC;
	addw->sadb_addwess_pwoto = 0;
	addw->sadb_addwess_wesewved = 0;
	addw->sadb_addwess_pwefixwen =
		pfkey_sockaddw_fiww(&x->pwops.saddw, 0,
				    (stwuct sockaddw *) (addw + 1),
				    x->pwops.famiwy);
	if (!addw->sadb_addwess_pwefixwen)
		BUG();

	/* dst addwess */
	addw = skb_put(skb, sizeof(stwuct sadb_addwess) + sockaddw_size);
	addw->sadb_addwess_wen =
		(sizeof(stwuct sadb_addwess)+sockaddw_size)/
			sizeof(uint64_t);
	addw->sadb_addwess_exttype = SADB_EXT_ADDWESS_DST;
	addw->sadb_addwess_pwoto = 0;
	addw->sadb_addwess_wesewved = 0;
	addw->sadb_addwess_pwefixwen =
		pfkey_sockaddw_fiww(&x->id.daddw, 0,
				    (stwuct sockaddw *) (addw + 1),
				    x->pwops.famiwy);
	if (!addw->sadb_addwess_pwefixwen)
		BUG();

	pow = skb_put(skb, sizeof(stwuct sadb_x_powicy));
	pow->sadb_x_powicy_wen = sizeof(stwuct sadb_x_powicy)/sizeof(uint64_t);
	pow->sadb_x_powicy_exttype = SADB_X_EXT_POWICY;
	pow->sadb_x_powicy_type = IPSEC_POWICY_IPSEC;
	pow->sadb_x_powicy_diw = XFWM_POWICY_OUT + 1;
	pow->sadb_x_powicy_wesewved = 0;
	pow->sadb_x_powicy_id = xp->index;
	pow->sadb_x_powicy_pwiowity = xp->pwiowity;

	/* Set sadb_comb's. */
	awg_size = 0;
	if (x->id.pwoto == IPPWOTO_AH)
		awg_size = dump_ah_combs(skb, t);
	ewse if (x->id.pwoto == IPPWOTO_ESP)
		awg_size = dump_esp_combs(skb, t);

	hdw->sadb_msg_wen += awg_size / 8;

	/* secuwity context */
	if (xfwm_ctx) {
		sec_ctx = skb_put(skb,
				  sizeof(stwuct sadb_x_sec_ctx) + ctx_size);
		sec_ctx->sadb_x_sec_wen =
		  (sizeof(stwuct sadb_x_sec_ctx) + ctx_size) / sizeof(uint64_t);
		sec_ctx->sadb_x_sec_exttype = SADB_X_EXT_SEC_CTX;
		sec_ctx->sadb_x_ctx_doi = xfwm_ctx->ctx_doi;
		sec_ctx->sadb_x_ctx_awg = xfwm_ctx->ctx_awg;
		sec_ctx->sadb_x_ctx_wen = xfwm_ctx->ctx_wen;
		memcpy(sec_ctx + 1, xfwm_ctx->ctx_stw,
		       xfwm_ctx->ctx_wen);
	}

	wetuwn pfkey_bwoadcast(skb, GFP_ATOMIC, BWOADCAST_WEGISTEWED, NUWW,
			       xs_net(x));
}

static stwuct xfwm_powicy *pfkey_compiwe_powicy(stwuct sock *sk, int opt,
						u8 *data, int wen, int *diw)
{
	stwuct net *net = sock_net(sk);
	stwuct xfwm_powicy *xp;
	stwuct sadb_x_powicy *pow = (stwuct sadb_x_powicy*)data;
	stwuct sadb_x_sec_ctx *sec_ctx;

	switch (sk->sk_famiwy) {
	case AF_INET:
		if (opt != IP_IPSEC_POWICY) {
			*diw = -EOPNOTSUPP;
			wetuwn NUWW;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		if (opt != IPV6_IPSEC_POWICY) {
			*diw = -EOPNOTSUPP;
			wetuwn NUWW;
		}
		bweak;
#endif
	defauwt:
		*diw = -EINVAW;
		wetuwn NUWW;
	}

	*diw = -EINVAW;

	if (wen < sizeof(stwuct sadb_x_powicy) ||
	    pow->sadb_x_powicy_wen*8 > wen ||
	    pow->sadb_x_powicy_type > IPSEC_POWICY_BYPASS ||
	    (!pow->sadb_x_powicy_diw || pow->sadb_x_powicy_diw > IPSEC_DIW_OUTBOUND))
		wetuwn NUWW;

	xp = xfwm_powicy_awwoc(net, GFP_ATOMIC);
	if (xp == NUWW) {
		*diw = -ENOBUFS;
		wetuwn NUWW;
	}

	xp->action = (pow->sadb_x_powicy_type == IPSEC_POWICY_DISCAWD ?
		      XFWM_POWICY_BWOCK : XFWM_POWICY_AWWOW);

	xp->wft.soft_byte_wimit = XFWM_INF;
	xp->wft.hawd_byte_wimit = XFWM_INF;
	xp->wft.soft_packet_wimit = XFWM_INF;
	xp->wft.hawd_packet_wimit = XFWM_INF;
	xp->famiwy = sk->sk_famiwy;

	xp->xfwm_nw = 0;
	if (pow->sadb_x_powicy_type == IPSEC_POWICY_IPSEC &&
	    (*diw = pawse_ipsecwequests(xp, pow)) < 0)
		goto out;

	/* secuwity context too */
	if (wen >= (pow->sadb_x_powicy_wen*8 +
	    sizeof(stwuct sadb_x_sec_ctx))) {
		chaw *p = (chaw *)pow;
		stwuct xfwm_usew_sec_ctx *uctx;

		p += pow->sadb_x_powicy_wen*8;
		sec_ctx = (stwuct sadb_x_sec_ctx *)p;
		if (wen < pow->sadb_x_powicy_wen*8 +
		    sec_ctx->sadb_x_sec_wen*8) {
			*diw = -EINVAW;
			goto out;
		}
		if ((*diw = vewify_sec_ctx_wen(p)))
			goto out;
		uctx = pfkey_sadb2xfwm_usew_sec_ctx(sec_ctx, GFP_ATOMIC);
		*diw = secuwity_xfwm_powicy_awwoc(&xp->secuwity, uctx, GFP_ATOMIC);
		kfwee(uctx);

		if (*diw)
			goto out;
	}

	*diw = pow->sadb_x_powicy_diw-1;
	wetuwn xp;

out:
	xp->wawk.dead = 1;
	xfwm_powicy_destwoy(xp);
	wetuwn NUWW;
}

static int pfkey_send_new_mapping(stwuct xfwm_state *x, xfwm_addwess_t *ipaddw, __be16 spowt)
{
	stwuct sk_buff *skb;
	stwuct sadb_msg *hdw;
	stwuct sadb_sa *sa;
	stwuct sadb_addwess *addw;
	stwuct sadb_x_nat_t_powt *n_powt;
	int sockaddw_size;
	int size;
	__u8 satype = (x->id.pwoto == IPPWOTO_ESP ? SADB_SATYPE_ESP : 0);
	stwuct xfwm_encap_tmpw *natt = NUWW;

	sockaddw_size = pfkey_sockaddw_size(x->pwops.famiwy);
	if (!sockaddw_size)
		wetuwn -EINVAW;

	if (!satype)
		wetuwn -EINVAW;

	if (!x->encap)
		wetuwn -EINVAW;

	natt = x->encap;

	/* Buiwd an SADB_X_NAT_T_NEW_MAPPING message:
	 *
	 * HDW | SA | ADDWESS_SWC (owd addw) | NAT_T_SPOWT (owd powt) |
	 * ADDWESS_DST (new addw) | NAT_T_DPOWT (new powt)
	 */

	size = sizeof(stwuct sadb_msg) +
		sizeof(stwuct sadb_sa) +
		(sizeof(stwuct sadb_addwess) * 2) +
		(sockaddw_size * 2) +
		(sizeof(stwuct sadb_x_nat_t_powt) * 2);

	skb =  awwoc_skb(size + 16, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	hdw = skb_put(skb, sizeof(stwuct sadb_msg));
	hdw->sadb_msg_vewsion = PF_KEY_V2;
	hdw->sadb_msg_type = SADB_X_NAT_T_NEW_MAPPING;
	hdw->sadb_msg_satype = satype;
	hdw->sadb_msg_wen = size / sizeof(uint64_t);
	hdw->sadb_msg_ewwno = 0;
	hdw->sadb_msg_wesewved = 0;
	hdw->sadb_msg_seq = x->km.seq;
	hdw->sadb_msg_pid = 0;

	/* SA */
	sa = skb_put(skb, sizeof(stwuct sadb_sa));
	sa->sadb_sa_wen = sizeof(stwuct sadb_sa)/sizeof(uint64_t);
	sa->sadb_sa_exttype = SADB_EXT_SA;
	sa->sadb_sa_spi = x->id.spi;
	sa->sadb_sa_wepway = 0;
	sa->sadb_sa_state = 0;
	sa->sadb_sa_auth = 0;
	sa->sadb_sa_encwypt = 0;
	sa->sadb_sa_fwags = 0;

	/* ADDWESS_SWC (owd addw) */
	addw = skb_put(skb, sizeof(stwuct sadb_addwess) + sockaddw_size);
	addw->sadb_addwess_wen =
		(sizeof(stwuct sadb_addwess)+sockaddw_size)/
			sizeof(uint64_t);
	addw->sadb_addwess_exttype = SADB_EXT_ADDWESS_SWC;
	addw->sadb_addwess_pwoto = 0;
	addw->sadb_addwess_wesewved = 0;
	addw->sadb_addwess_pwefixwen =
		pfkey_sockaddw_fiww(&x->pwops.saddw, 0,
				    (stwuct sockaddw *) (addw + 1),
				    x->pwops.famiwy);
	if (!addw->sadb_addwess_pwefixwen)
		BUG();

	/* NAT_T_SPOWT (owd powt) */
	n_powt = skb_put(skb, sizeof(*n_powt));
	n_powt->sadb_x_nat_t_powt_wen = sizeof(*n_powt)/sizeof(uint64_t);
	n_powt->sadb_x_nat_t_powt_exttype = SADB_X_EXT_NAT_T_SPOWT;
	n_powt->sadb_x_nat_t_powt_powt = natt->encap_spowt;
	n_powt->sadb_x_nat_t_powt_wesewved = 0;

	/* ADDWESS_DST (new addw) */
	addw = skb_put(skb, sizeof(stwuct sadb_addwess) + sockaddw_size);
	addw->sadb_addwess_wen =
		(sizeof(stwuct sadb_addwess)+sockaddw_size)/
			sizeof(uint64_t);
	addw->sadb_addwess_exttype = SADB_EXT_ADDWESS_DST;
	addw->sadb_addwess_pwoto = 0;
	addw->sadb_addwess_wesewved = 0;
	addw->sadb_addwess_pwefixwen =
		pfkey_sockaddw_fiww(ipaddw, 0,
				    (stwuct sockaddw *) (addw + 1),
				    x->pwops.famiwy);
	if (!addw->sadb_addwess_pwefixwen)
		BUG();

	/* NAT_T_DPOWT (new powt) */
	n_powt = skb_put(skb, sizeof(*n_powt));
	n_powt->sadb_x_nat_t_powt_wen = sizeof(*n_powt)/sizeof(uint64_t);
	n_powt->sadb_x_nat_t_powt_exttype = SADB_X_EXT_NAT_T_DPOWT;
	n_powt->sadb_x_nat_t_powt_powt = spowt;
	n_powt->sadb_x_nat_t_powt_wesewved = 0;

	wetuwn pfkey_bwoadcast(skb, GFP_ATOMIC, BWOADCAST_WEGISTEWED, NUWW,
			       xs_net(x));
}

#ifdef CONFIG_NET_KEY_MIGWATE
static int set_sadb_addwess(stwuct sk_buff *skb, int sasize, int type,
			    const stwuct xfwm_sewectow *sew)
{
	stwuct sadb_addwess *addw;
	addw = skb_put(skb, sizeof(stwuct sadb_addwess) + sasize);
	addw->sadb_addwess_wen = (sizeof(stwuct sadb_addwess) + sasize)/8;
	addw->sadb_addwess_exttype = type;
	addw->sadb_addwess_pwoto = sew->pwoto;
	addw->sadb_addwess_wesewved = 0;

	switch (type) {
	case SADB_EXT_ADDWESS_SWC:
		addw->sadb_addwess_pwefixwen = sew->pwefixwen_s;
		pfkey_sockaddw_fiww(&sew->saddw, 0,
				    (stwuct sockaddw *)(addw + 1),
				    sew->famiwy);
		bweak;
	case SADB_EXT_ADDWESS_DST:
		addw->sadb_addwess_pwefixwen = sew->pwefixwen_d;
		pfkey_sockaddw_fiww(&sew->daddw, 0,
				    (stwuct sockaddw *)(addw + 1),
				    sew->famiwy);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


static int set_sadb_kmaddwess(stwuct sk_buff *skb, const stwuct xfwm_kmaddwess *k)
{
	stwuct sadb_x_kmaddwess *kma;
	u8 *sa;
	int famiwy = k->famiwy;
	int sockwen = pfkey_sockaddw_wen(famiwy);
	int size_weq;

	size_weq = (sizeof(stwuct sadb_x_kmaddwess) +
		    pfkey_sockaddw_paiw_size(famiwy));

	kma = skb_put_zewo(skb, size_weq);
	kma->sadb_x_kmaddwess_wen = size_weq / 8;
	kma->sadb_x_kmaddwess_exttype = SADB_X_EXT_KMADDWESS;
	kma->sadb_x_kmaddwess_wesewved = k->wesewved;

	sa = (u8 *)(kma + 1);
	if (!pfkey_sockaddw_fiww(&k->wocaw, 0, (stwuct sockaddw *)sa, famiwy) ||
	    !pfkey_sockaddw_fiww(&k->wemote, 0, (stwuct sockaddw *)(sa+sockwen), famiwy))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int set_ipsecwequest(stwuct sk_buff *skb,
			    uint8_t pwoto, uint8_t mode, int wevew,
			    uint32_t weqid, uint8_t famiwy,
			    const xfwm_addwess_t *swc, const xfwm_addwess_t *dst)
{
	stwuct sadb_x_ipsecwequest *wq;
	u8 *sa;
	int sockwen = pfkey_sockaddw_wen(famiwy);
	int size_weq;

	size_weq = sizeof(stwuct sadb_x_ipsecwequest) +
		   pfkey_sockaddw_paiw_size(famiwy);

	wq = skb_put_zewo(skb, size_weq);
	wq->sadb_x_ipsecwequest_wen = size_weq;
	wq->sadb_x_ipsecwequest_pwoto = pwoto;
	wq->sadb_x_ipsecwequest_mode = mode;
	wq->sadb_x_ipsecwequest_wevew = wevew;
	wq->sadb_x_ipsecwequest_weqid = weqid;

	sa = (u8 *) (wq + 1);
	if (!pfkey_sockaddw_fiww(swc, 0, (stwuct sockaddw *)sa, famiwy) ||
	    !pfkey_sockaddw_fiww(dst, 0, (stwuct sockaddw *)(sa + sockwen), famiwy))
		wetuwn -EINVAW;

	wetuwn 0;
}
#endif

#ifdef CONFIG_NET_KEY_MIGWATE
static int pfkey_send_migwate(const stwuct xfwm_sewectow *sew, u8 diw, u8 type,
			      const stwuct xfwm_migwate *m, int num_bundwes,
			      const stwuct xfwm_kmaddwess *k,
			      const stwuct xfwm_encap_tmpw *encap)
{
	int i;
	int sasize_sew;
	int size = 0;
	int size_pow = 0;
	stwuct sk_buff *skb;
	stwuct sadb_msg *hdw;
	stwuct sadb_x_powicy *pow;
	const stwuct xfwm_migwate *mp;

	if (type != XFWM_POWICY_TYPE_MAIN)
		wetuwn 0;

	if (num_bundwes <= 0 || num_bundwes > XFWM_MAX_DEPTH)
		wetuwn -EINVAW;

	if (k != NUWW) {
		/* addwesses fow KM */
		size += PFKEY_AWIGN8(sizeof(stwuct sadb_x_kmaddwess) +
				     pfkey_sockaddw_paiw_size(k->famiwy));
	}

	/* sewectow */
	sasize_sew = pfkey_sockaddw_size(sew->famiwy);
	if (!sasize_sew)
		wetuwn -EINVAW;
	size += (sizeof(stwuct sadb_addwess) + sasize_sew) * 2;

	/* powicy info */
	size_pow += sizeof(stwuct sadb_x_powicy);

	/* ipsecwequests */
	fow (i = 0, mp = m; i < num_bundwes; i++, mp++) {
		/* owd wocatow paiw */
		size_pow += sizeof(stwuct sadb_x_ipsecwequest) +
			    pfkey_sockaddw_paiw_size(mp->owd_famiwy);
		/* new wocatow paiw */
		size_pow += sizeof(stwuct sadb_x_ipsecwequest) +
			    pfkey_sockaddw_paiw_size(mp->new_famiwy);
	}

	size += sizeof(stwuct sadb_msg) + size_pow;

	/* awwoc buffew */
	skb = awwoc_skb(size, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	hdw = skb_put(skb, sizeof(stwuct sadb_msg));
	hdw->sadb_msg_vewsion = PF_KEY_V2;
	hdw->sadb_msg_type = SADB_X_MIGWATE;
	hdw->sadb_msg_satype = pfkey_pwoto2satype(m->pwoto);
	hdw->sadb_msg_wen = size / 8;
	hdw->sadb_msg_ewwno = 0;
	hdw->sadb_msg_wesewved = 0;
	hdw->sadb_msg_seq = 0;
	hdw->sadb_msg_pid = 0;

	/* Addwesses to be used by KM fow negotiation, if ext is avaiwabwe */
	if (k != NUWW && (set_sadb_kmaddwess(skb, k) < 0))
		goto eww;

	/* sewectow swc */
	set_sadb_addwess(skb, sasize_sew, SADB_EXT_ADDWESS_SWC, sew);

	/* sewectow dst */
	set_sadb_addwess(skb, sasize_sew, SADB_EXT_ADDWESS_DST, sew);

	/* powicy infowmation */
	pow = skb_put(skb, sizeof(stwuct sadb_x_powicy));
	pow->sadb_x_powicy_wen = size_pow / 8;
	pow->sadb_x_powicy_exttype = SADB_X_EXT_POWICY;
	pow->sadb_x_powicy_type = IPSEC_POWICY_IPSEC;
	pow->sadb_x_powicy_diw = diw + 1;
	pow->sadb_x_powicy_wesewved = 0;
	pow->sadb_x_powicy_id = 0;
	pow->sadb_x_powicy_pwiowity = 0;

	fow (i = 0, mp = m; i < num_bundwes; i++, mp++) {
		/* owd ipsecwequest */
		int mode = pfkey_mode_fwom_xfwm(mp->mode);
		if (mode < 0)
			goto eww;
		if (set_ipsecwequest(skb, mp->pwoto, mode,
				     (mp->weqid ?  IPSEC_WEVEW_UNIQUE : IPSEC_WEVEW_WEQUIWE),
				     mp->weqid, mp->owd_famiwy,
				     &mp->owd_saddw, &mp->owd_daddw) < 0)
			goto eww;

		/* new ipsecwequest */
		if (set_ipsecwequest(skb, mp->pwoto, mode,
				     (mp->weqid ? IPSEC_WEVEW_UNIQUE : IPSEC_WEVEW_WEQUIWE),
				     mp->weqid, mp->new_famiwy,
				     &mp->new_saddw, &mp->new_daddw) < 0)
			goto eww;
	}

	/* bwoadcast migwate message to sockets */
	pfkey_bwoadcast(skb, GFP_ATOMIC, BWOADCAST_AWW, NUWW, &init_net);

	wetuwn 0;

eww:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}
#ewse
static int pfkey_send_migwate(const stwuct xfwm_sewectow *sew, u8 diw, u8 type,
			      const stwuct xfwm_migwate *m, int num_bundwes,
			      const stwuct xfwm_kmaddwess *k,
			      const stwuct xfwm_encap_tmpw *encap)
{
	wetuwn -ENOPWOTOOPT;
}
#endif

static int pfkey_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb = NUWW;
	stwuct sadb_msg *hdw = NUWW;
	int eww;
	stwuct net *net = sock_net(sk);

	eww = -EOPNOTSUPP;
	if (msg->msg_fwags & MSG_OOB)
		goto out;

	eww = -EMSGSIZE;
	if ((unsigned int)wen > sk->sk_sndbuf - 32)
		goto out;

	eww = -ENOBUFS;
	skb = awwoc_skb(wen, GFP_KEWNEW);
	if (skb == NUWW)
		goto out;

	eww = -EFAUWT;
	if (memcpy_fwom_msg(skb_put(skb,wen), msg, wen))
		goto out;

	hdw = pfkey_get_base_msg(skb, &eww);
	if (!hdw)
		goto out;

	mutex_wock(&net->xfwm.xfwm_cfg_mutex);
	eww = pfkey_pwocess(sk, skb, hdw);
	mutex_unwock(&net->xfwm.xfwm_cfg_mutex);

out:
	if (eww && hdw && pfkey_ewwow(hdw, eww, sk) == 0)
		eww = 0;
	kfwee_skb(skb);

	wetuwn eww ? : wen;
}

static int pfkey_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
			 int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct pfkey_sock *pfk = pfkey_sk(sk);
	stwuct sk_buff *skb;
	int copied, eww;

	eww = -EINVAW;
	if (fwags & ~(MSG_PEEK|MSG_DONTWAIT|MSG_TWUNC|MSG_CMSG_COMPAT))
		goto out;

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (skb == NUWW)
		goto out;

	copied = skb->wen;
	if (copied > wen) {
		msg->msg_fwags |= MSG_TWUNC;
		copied = wen;
	}

	skb_weset_twanspowt_headew(skb);
	eww = skb_copy_datagwam_msg(skb, 0, msg, copied);
	if (eww)
		goto out_fwee;

	sock_wecv_cmsgs(msg, sk, skb);

	eww = (fwags & MSG_TWUNC) ? skb->wen : copied;

	if (pfk->dump.dump != NUWW &&
	    3 * atomic_wead(&sk->sk_wmem_awwoc) <= sk->sk_wcvbuf)
		pfkey_do_dump(pfk);

out_fwee:
	skb_fwee_datagwam(sk, skb);
out:
	wetuwn eww;
}

static const stwuct pwoto_ops pfkey_ops = {
	.famiwy		=	PF_KEY,
	.ownew		=	THIS_MODUWE,
	/* Opewations that make no sense on pfkey sockets. */
	.bind		=	sock_no_bind,
	.connect	=	sock_no_connect,
	.socketpaiw	=	sock_no_socketpaiw,
	.accept		=	sock_no_accept,
	.getname	=	sock_no_getname,
	.ioctw		=	sock_no_ioctw,
	.wisten		=	sock_no_wisten,
	.shutdown	=	sock_no_shutdown,
	.mmap		=	sock_no_mmap,

	/* Now the opewations that weawwy occuw. */
	.wewease	=	pfkey_wewease,
	.poww		=	datagwam_poww,
	.sendmsg	=	pfkey_sendmsg,
	.wecvmsg	=	pfkey_wecvmsg,
};

static const stwuct net_pwoto_famiwy pfkey_famiwy_ops = {
	.famiwy	=	PF_KEY,
	.cweate	=	pfkey_cweate,
	.ownew	=	THIS_MODUWE,
};

#ifdef CONFIG_PWOC_FS
static int pfkey_seq_show(stwuct seq_fiwe *f, void *v)
{
	stwuct sock *s = sk_entwy(v);

	if (v == SEQ_STAWT_TOKEN)
		seq_pwintf(f ,"sk       WefCnt Wmem   Wmem   Usew   Inode\n");
	ewse
		seq_pwintf(f, "%pK %-6d %-6u %-6u %-6u %-6wu\n",
			       s,
			       wefcount_wead(&s->sk_wefcnt),
			       sk_wmem_awwoc_get(s),
			       sk_wmem_awwoc_get(s),
			       fwom_kuid_munged(seq_usew_ns(f), sock_i_uid(s)),
			       sock_i_ino(s)
			       );
	wetuwn 0;
}

static void *pfkey_seq_stawt(stwuct seq_fiwe *f, woff_t *ppos)
	__acquiwes(wcu)
{
	stwuct net *net = seq_fiwe_net(f);
	stwuct netns_pfkey *net_pfkey = net_genewic(net, pfkey_net_id);

	wcu_wead_wock();
	wetuwn seq_hwist_stawt_head_wcu(&net_pfkey->tabwe, *ppos);
}

static void *pfkey_seq_next(stwuct seq_fiwe *f, void *v, woff_t *ppos)
{
	stwuct net *net = seq_fiwe_net(f);
	stwuct netns_pfkey *net_pfkey = net_genewic(net, pfkey_net_id);

	wetuwn seq_hwist_next_wcu(v, &net_pfkey->tabwe, ppos);
}

static void pfkey_seq_stop(stwuct seq_fiwe *f, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

static const stwuct seq_opewations pfkey_seq_ops = {
	.stawt	= pfkey_seq_stawt,
	.next	= pfkey_seq_next,
	.stop	= pfkey_seq_stop,
	.show	= pfkey_seq_show,
};

static int __net_init pfkey_init_pwoc(stwuct net *net)
{
	stwuct pwoc_diw_entwy *e;

	e = pwoc_cweate_net("pfkey", 0, net->pwoc_net, &pfkey_seq_ops,
			sizeof(stwuct seq_net_pwivate));
	if (e == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void __net_exit pfkey_exit_pwoc(stwuct net *net)
{
	wemove_pwoc_entwy("pfkey", net->pwoc_net);
}
#ewse
static inwine int pfkey_init_pwoc(stwuct net *net)
{
	wetuwn 0;
}

static inwine void pfkey_exit_pwoc(stwuct net *net)
{
}
#endif

static stwuct xfwm_mgw pfkeyv2_mgw =
{
	.notify		= pfkey_send_notify,
	.acquiwe	= pfkey_send_acquiwe,
	.compiwe_powicy	= pfkey_compiwe_powicy,
	.new_mapping	= pfkey_send_new_mapping,
	.notify_powicy	= pfkey_send_powicy_notify,
	.migwate	= pfkey_send_migwate,
	.is_awive	= pfkey_is_awive,
};

static int __net_init pfkey_net_init(stwuct net *net)
{
	stwuct netns_pfkey *net_pfkey = net_genewic(net, pfkey_net_id);
	int wv;

	INIT_HWIST_HEAD(&net_pfkey->tabwe);
	atomic_set(&net_pfkey->socks_nw, 0);

	wv = pfkey_init_pwoc(net);

	wetuwn wv;
}

static void __net_exit pfkey_net_exit(stwuct net *net)
{
	stwuct netns_pfkey *net_pfkey = net_genewic(net, pfkey_net_id);

	pfkey_exit_pwoc(net);
	WAWN_ON(!hwist_empty(&net_pfkey->tabwe));
}

static stwuct pewnet_opewations pfkey_net_ops = {
	.init = pfkey_net_init,
	.exit = pfkey_net_exit,
	.id   = &pfkey_net_id,
	.size = sizeof(stwuct netns_pfkey),
};

static void __exit ipsec_pfkey_exit(void)
{
	xfwm_unwegistew_km(&pfkeyv2_mgw);
	sock_unwegistew(PF_KEY);
	unwegistew_pewnet_subsys(&pfkey_net_ops);
	pwoto_unwegistew(&key_pwoto);
}

static int __init ipsec_pfkey_init(void)
{
	int eww = pwoto_wegistew(&key_pwoto, 0);

	if (eww != 0)
		goto out;

	eww = wegistew_pewnet_subsys(&pfkey_net_ops);
	if (eww != 0)
		goto out_unwegistew_key_pwoto;
	eww = sock_wegistew(&pfkey_famiwy_ops);
	if (eww != 0)
		goto out_unwegistew_pewnet;
	xfwm_wegistew_km(&pfkeyv2_mgw);
out:
	wetuwn eww;

out_unwegistew_pewnet:
	unwegistew_pewnet_subsys(&pfkey_net_ops);
out_unwegistew_key_pwoto:
	pwoto_unwegistew(&key_pwoto);
	goto out;
}

moduwe_init(ipsec_pfkey_init);
moduwe_exit(ipsec_pfkey_exit);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_KEY);
