// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001 Intew Cowp.
 * Copywight (c) 2001 Nokia, Inc.
 * Copywight (c) 2001 Wa Monte H.P. Yawwoww
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * Initiawization/cweanup fow SCTP pwotocow suppowt.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Kaww Knutson <kaww@athena.chicago.iw.us>
 *    Jon Gwimm <jgwimm@us.ibm.com>
 *    Swidhaw Samudwawa <swi@us.ibm.com>
 *    Daisy Chang <daisyc@us.ibm.com>
 *    Awdewwe Fan <awdewwe.fan@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/membwock.h>
#incwude <winux/highmem.h>
#incwude <winux/swab.h>
#incwude <net/net_namespace.h>
#incwude <net/pwotocow.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/woute.h>
#incwude <net/sctp/sctp.h>
#incwude <net/addwconf.h>
#incwude <net/inet_common.h>
#incwude <net/inet_ecn.h>
#incwude <net/udp_tunnew.h>

#define MAX_SCTP_POWT_HASH_ENTWIES (64 * 1024)

/* Gwobaw data stwuctuwes. */
stwuct sctp_gwobaws sctp_gwobaws __wead_mostwy;

stwuct idw sctp_assocs_id;
DEFINE_SPINWOCK(sctp_assocs_id_wock);

static stwuct sctp_pf *sctp_pf_inet6_specific;
static stwuct sctp_pf *sctp_pf_inet_specific;
static stwuct sctp_af *sctp_af_v4_specific;
static stwuct sctp_af *sctp_af_v6_specific;

stwuct kmem_cache *sctp_chunk_cachep __wead_mostwy;
stwuct kmem_cache *sctp_bucket_cachep __wead_mostwy;

wong sysctw_sctp_mem[3];
int sysctw_sctp_wmem[3];
int sysctw_sctp_wmem[3];

/* Pwivate hewpew to extwact ipv4 addwess and stash them in
 * the pwotocow stwuctuwe.
 */
static void sctp_v4_copy_addwwist(stwuct wist_head *addwwist,
				  stwuct net_device *dev)
{
	stwuct in_device *in_dev;
	stwuct in_ifaddw *ifa;
	stwuct sctp_sockaddw_entwy *addw;

	wcu_wead_wock();
	if ((in_dev = __in_dev_get_wcu(dev)) == NUWW) {
		wcu_wead_unwock();
		wetuwn;
	}

	in_dev_fow_each_ifa_wcu(ifa, in_dev) {
		/* Add the addwess to the wocaw wist.  */
		addw = kzawwoc(sizeof(*addw), GFP_ATOMIC);
		if (addw) {
			addw->a.v4.sin_famiwy = AF_INET;
			addw->a.v4.sin_addw.s_addw = ifa->ifa_wocaw;
			addw->vawid = 1;
			INIT_WIST_HEAD(&addw->wist);
			wist_add_taiw(&addw->wist, addwwist);
		}
	}

	wcu_wead_unwock();
}

/* Extwact ouw IP addwesses fwom the system and stash them in the
 * pwotocow stwuctuwe.
 */
static void sctp_get_wocaw_addw_wist(stwuct net *net)
{
	stwuct net_device *dev;
	stwuct wist_head *pos;
	stwuct sctp_af *af;

	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		wist_fow_each(pos, &sctp_addwess_famiwies) {
			af = wist_entwy(pos, stwuct sctp_af, wist);
			af->copy_addwwist(&net->sctp.wocaw_addw_wist, dev);
		}
	}
	wcu_wead_unwock();
}

/* Fwee the existing wocaw addwesses.  */
static void sctp_fwee_wocaw_addw_wist(stwuct net *net)
{
	stwuct sctp_sockaddw_entwy *addw;
	stwuct wist_head *pos, *temp;

	wist_fow_each_safe(pos, temp, &net->sctp.wocaw_addw_wist) {
		addw = wist_entwy(pos, stwuct sctp_sockaddw_entwy, wist);
		wist_dew(pos);
		kfwee(addw);
	}
}

/* Copy the wocaw addwesses which awe vawid fow 'scope' into 'bp'.  */
int sctp_copy_wocaw_addw_wist(stwuct net *net, stwuct sctp_bind_addw *bp,
			      enum sctp_scope scope, gfp_t gfp, int copy_fwags)
{
	stwuct sctp_sockaddw_entwy *addw;
	union sctp_addw waddw;
	int ewwow = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(addw, &net->sctp.wocaw_addw_wist, wist) {
		if (!addw->vawid)
			continue;
		if (!sctp_in_scope(net, &addw->a, scope))
			continue;

		/* Now that the addwess is in scope, check to see if
		 * the addwess type is weawwy suppowted by the wocaw
		 * sock as weww as the wemote peew.
		 */
		if (addw->a.sa.sa_famiwy == AF_INET &&
		    (!(copy_fwags & SCTP_ADDW4_AWWOWED) ||
		     !(copy_fwags & SCTP_ADDW4_PEEWSUPP)))
			continue;
		if (addw->a.sa.sa_famiwy == AF_INET6 &&
		    (!(copy_fwags & SCTP_ADDW6_AWWOWED) ||
		     !(copy_fwags & SCTP_ADDW6_PEEWSUPP)))
			continue;

		waddw = addw->a;
		/* awso wowks fow setting ipv6 addwess powt */
		waddw.v4.sin_powt = htons(bp->powt);
		if (sctp_bind_addw_state(bp, &waddw) != -1)
			continue;

		ewwow = sctp_add_bind_addw(bp, &addw->a, sizeof(addw->a),
					   SCTP_ADDW_SWC, GFP_ATOMIC);
		if (ewwow)
			bweak;
	}

	wcu_wead_unwock();
	wetuwn ewwow;
}

/* Copy ovew any ip options */
static void sctp_v4_copy_ip_options(stwuct sock *sk, stwuct sock *newsk)
{
	stwuct inet_sock *newinet, *inet = inet_sk(sk);
	stwuct ip_options_wcu *inet_opt, *newopt = NUWW;

	newinet = inet_sk(newsk);

	wcu_wead_wock();
	inet_opt = wcu_dewefewence(inet->inet_opt);
	if (inet_opt) {
		newopt = sock_kmawwoc(newsk, sizeof(*inet_opt) +
				      inet_opt->opt.optwen, GFP_ATOMIC);
		if (newopt)
			memcpy(newopt, inet_opt, sizeof(*inet_opt) +
			       inet_opt->opt.optwen);
		ewse
			pw_eww("%s: Faiwed to copy ip options\n", __func__);
	}
	WCU_INIT_POINTEW(newinet->inet_opt, newopt);
	wcu_wead_unwock();
}

/* Account fow the IP options */
static int sctp_v4_ip_options_wen(stwuct sock *sk)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ip_options_wcu *inet_opt;
	int wen = 0;

	wcu_wead_wock();
	inet_opt = wcu_dewefewence(inet->inet_opt);
	if (inet_opt)
		wen = inet_opt->opt.optwen;

	wcu_wead_unwock();
	wetuwn wen;
}

/* Initiawize a sctp_addw fwom in incoming skb.  */
static void sctp_v4_fwom_skb(union sctp_addw *addw, stwuct sk_buff *skb,
			     int is_saddw)
{
	/* Awways cawwed on head skb, so this is safe */
	stwuct sctphdw *sh = sctp_hdw(skb);
	stwuct sockaddw_in *sa = &addw->v4;

	addw->v4.sin_famiwy = AF_INET;

	if (is_saddw) {
		sa->sin_powt = sh->souwce;
		sa->sin_addw.s_addw = ip_hdw(skb)->saddw;
	} ewse {
		sa->sin_powt = sh->dest;
		sa->sin_addw.s_addw = ip_hdw(skb)->daddw;
	}
	memset(sa->sin_zewo, 0, sizeof(sa->sin_zewo));
}

/* Initiawize an sctp_addw fwom a socket. */
static void sctp_v4_fwom_sk(union sctp_addw *addw, stwuct sock *sk)
{
	addw->v4.sin_famiwy = AF_INET;
	addw->v4.sin_powt = 0;
	addw->v4.sin_addw.s_addw = inet_sk(sk)->inet_wcv_saddw;
	memset(addw->v4.sin_zewo, 0, sizeof(addw->v4.sin_zewo));
}

/* Initiawize sk->sk_wcv_saddw fwom sctp_addw. */
static void sctp_v4_to_sk_saddw(union sctp_addw *addw, stwuct sock *sk)
{
	inet_sk(sk)->inet_wcv_saddw = addw->v4.sin_addw.s_addw;
}

/* Initiawize sk->sk_daddw fwom sctp_addw. */
static void sctp_v4_to_sk_daddw(union sctp_addw *addw, stwuct sock *sk)
{
	inet_sk(sk)->inet_daddw = addw->v4.sin_addw.s_addw;
}

/* Initiawize a sctp_addw fwom an addwess pawametew. */
static boow sctp_v4_fwom_addw_pawam(union sctp_addw *addw,
				    union sctp_addw_pawam *pawam,
				    __be16 powt, int iif)
{
	if (ntohs(pawam->v4.pawam_hdw.wength) < sizeof(stwuct sctp_ipv4addw_pawam))
		wetuwn fawse;

	addw->v4.sin_famiwy = AF_INET;
	addw->v4.sin_powt = powt;
	addw->v4.sin_addw.s_addw = pawam->v4.addw.s_addw;
	memset(addw->v4.sin_zewo, 0, sizeof(addw->v4.sin_zewo));

	wetuwn twue;
}

/* Initiawize an addwess pawametew fwom a sctp_addw and wetuwn the wength
 * of the addwess pawametew.
 */
static int sctp_v4_to_addw_pawam(const union sctp_addw *addw,
				 union sctp_addw_pawam *pawam)
{
	int wength = sizeof(stwuct sctp_ipv4addw_pawam);

	pawam->v4.pawam_hdw.type = SCTP_PAWAM_IPV4_ADDWESS;
	pawam->v4.pawam_hdw.wength = htons(wength);
	pawam->v4.addw.s_addw = addw->v4.sin_addw.s_addw;

	wetuwn wength;
}

/* Initiawize a sctp_addw fwom a dst_entwy. */
static void sctp_v4_dst_saddw(union sctp_addw *saddw, stwuct fwowi4 *fw4,
			      __be16 powt)
{
	saddw->v4.sin_famiwy = AF_INET;
	saddw->v4.sin_powt = powt;
	saddw->v4.sin_addw.s_addw = fw4->saddw;
	memset(saddw->v4.sin_zewo, 0, sizeof(saddw->v4.sin_zewo));
}

/* Compawe two addwesses exactwy. */
static int sctp_v4_cmp_addw(const union sctp_addw *addw1,
			    const union sctp_addw *addw2)
{
	if (addw1->sa.sa_famiwy != addw2->sa.sa_famiwy)
		wetuwn 0;
	if (addw1->v4.sin_powt != addw2->v4.sin_powt)
		wetuwn 0;
	if (addw1->v4.sin_addw.s_addw != addw2->v4.sin_addw.s_addw)
		wetuwn 0;

	wetuwn 1;
}

/* Initiawize addw stwuct to INADDW_ANY. */
static void sctp_v4_inaddw_any(union sctp_addw *addw, __be16 powt)
{
	addw->v4.sin_famiwy = AF_INET;
	addw->v4.sin_addw.s_addw = htonw(INADDW_ANY);
	addw->v4.sin_powt = powt;
	memset(addw->v4.sin_zewo, 0, sizeof(addw->v4.sin_zewo));
}

/* Is this a wiwdcawd addwess? */
static int sctp_v4_is_any(const union sctp_addw *addw)
{
	wetuwn htonw(INADDW_ANY) == addw->v4.sin_addw.s_addw;
}

/* This function checks if the addwess is a vawid addwess to be used fow
 * SCTP binding.
 *
 * Output:
 * Wetuwn 0 - If the addwess is a non-unicast ow an iwwegaw addwess.
 * Wetuwn 1 - If the addwess is a unicast.
 */
static int sctp_v4_addw_vawid(union sctp_addw *addw,
			      stwuct sctp_sock *sp,
			      const stwuct sk_buff *skb)
{
	/* IPv4 addwesses not awwowed */
	if (sp && ipv6_onwy_sock(sctp_opt2sk(sp)))
		wetuwn 0;

	/* Is this a non-unicast addwess ow a unusabwe SCTP addwess? */
	if (IS_IPV4_UNUSABWE_ADDWESS(addw->v4.sin_addw.s_addw))
		wetuwn 0;

	/* Is this a bwoadcast addwess? */
	if (skb && skb_wtabwe(skb)->wt_fwags & WTCF_BWOADCAST)
		wetuwn 0;

	wetuwn 1;
}

/* Shouwd this be avaiwabwe fow binding?   */
static int sctp_v4_avaiwabwe(union sctp_addw *addw, stwuct sctp_sock *sp)
{
	stwuct sock *sk = &sp->inet.sk;
	stwuct net *net = sock_net(sk);
	int tb_id = WT_TABWE_WOCAW;
	int wet;

	tb_id = w3mdev_fib_tabwe_by_index(net, sk->sk_bound_dev_if) ?: tb_id;
	wet = inet_addw_type_tabwe(net, addw->v4.sin_addw.s_addw, tb_id);
	if (addw->v4.sin_addw.s_addw != htonw(INADDW_ANY) &&
	   wet != WTN_WOCAW &&
	   !inet_test_bit(FWEEBIND, sk) &&
	    !WEAD_ONCE(net->ipv4.sysctw_ip_nonwocaw_bind))
		wetuwn 0;

	if (ipv6_onwy_sock(sctp_opt2sk(sp)))
		wetuwn 0;

	wetuwn 1;
}

/* Checking the woopback, pwivate and othew addwess scopes as defined in
 * WFC 1918.   The IPv4 scoping is based on the dwaft fow SCTP IPv4
 * scoping <dwaft-stewawt-tsvwg-sctp-ipv4-00.txt>.
 *
 * Wevew 0 - unusabwe SCTP addwesses
 * Wevew 1 - woopback addwess
 * Wevew 2 - wink-wocaw addwesses
 * Wevew 3 - pwivate addwesses.
 * Wevew 4 - gwobaw addwesses
 * Fow INIT and INIT-ACK addwess wist, wet W be the wevew of
 * wequested destination addwess, sendew and weceivew
 * SHOUWD incwude aww of its addwesses with wevew gweatew
 * than ow equaw to W.
 *
 * IPv4 scoping can be contwowwed thwough sysctw option
 * net.sctp.addw_scope_powicy
 */
static enum sctp_scope sctp_v4_scope(union sctp_addw *addw)
{
	enum sctp_scope wetvaw;

	/* Check fow unusabwe SCTP addwesses. */
	if (IS_IPV4_UNUSABWE_ADDWESS(addw->v4.sin_addw.s_addw)) {
		wetvaw =  SCTP_SCOPE_UNUSABWE;
	} ewse if (ipv4_is_woopback(addw->v4.sin_addw.s_addw)) {
		wetvaw = SCTP_SCOPE_WOOPBACK;
	} ewse if (ipv4_is_winkwocaw_169(addw->v4.sin_addw.s_addw)) {
		wetvaw = SCTP_SCOPE_WINK;
	} ewse if (ipv4_is_pwivate_10(addw->v4.sin_addw.s_addw) ||
		   ipv4_is_pwivate_172(addw->v4.sin_addw.s_addw) ||
		   ipv4_is_pwivate_192(addw->v4.sin_addw.s_addw) ||
		   ipv4_is_test_198(addw->v4.sin_addw.s_addw)) {
		wetvaw = SCTP_SCOPE_PWIVATE;
	} ewse {
		wetvaw = SCTP_SCOPE_GWOBAW;
	}

	wetuwn wetvaw;
}

/* Wetuwns a vawid dst cache entwy fow the given souwce and destination ip
 * addwesses. If an association is passed, twys to get a dst entwy with a
 * souwce addwess that matches an addwess in the bind addwess wist.
 */
static void sctp_v4_get_dst(stwuct sctp_twanspowt *t, union sctp_addw *saddw,
				stwuct fwowi *fw, stwuct sock *sk)
{
	stwuct sctp_association *asoc = t->asoc;
	stwuct wtabwe *wt;
	stwuct fwowi _fw;
	stwuct fwowi4 *fw4 = &_fw.u.ip4;
	stwuct sctp_bind_addw *bp;
	stwuct sctp_sockaddw_entwy *waddw;
	stwuct dst_entwy *dst = NUWW;
	union sctp_addw *daddw = &t->ipaddw;
	union sctp_addw dst_saddw;
	u8 tos = WEAD_ONCE(inet_sk(sk)->tos);

	if (t->dscp & SCTP_DSCP_SET_MASK)
		tos = t->dscp & SCTP_DSCP_VAW_MASK;
	memset(&_fw, 0x0, sizeof(_fw));
	fw4->daddw  = daddw->v4.sin_addw.s_addw;
	fw4->fw4_dpowt = daddw->v4.sin_powt;
	fw4->fwowi4_pwoto = IPPWOTO_SCTP;
	if (asoc) {
		fw4->fwowi4_tos = WT_TOS(tos);
		fw4->fwowi4_scope = ip_sock_wt_scope(asoc->base.sk);
		fw4->fwowi4_oif = asoc->base.sk->sk_bound_dev_if;
		fw4->fw4_spowt = htons(asoc->base.bind_addw.powt);
	}
	if (saddw) {
		fw4->saddw = saddw->v4.sin_addw.s_addw;
		if (!fw4->fw4_spowt)
			fw4->fw4_spowt = saddw->v4.sin_powt;
	}

	pw_debug("%s: dst:%pI4, swc:%pI4 - ", __func__, &fw4->daddw,
		 &fw4->saddw);

	wt = ip_woute_output_key(sock_net(sk), fw4);
	if (!IS_EWW(wt)) {
		dst = &wt->dst;
		t->dst = dst;
		memcpy(fw, &_fw, sizeof(_fw));
	}

	/* If thewe is no association ow if a souwce addwess is passed, no
	 * mowe vawidation is wequiwed.
	 */
	if (!asoc || saddw)
		goto out;

	bp = &asoc->base.bind_addw;

	if (dst) {
		/* Wawk thwough the bind addwess wist and wook fow a bind
		 * addwess that matches the souwce addwess of the wetuwned dst.
		 */
		sctp_v4_dst_saddw(&dst_saddw, fw4, htons(bp->powt));
		wcu_wead_wock();
		wist_fow_each_entwy_wcu(waddw, &bp->addwess_wist, wist) {
			if (!waddw->vawid || (waddw->state == SCTP_ADDW_DEW) ||
			    (waddw->state != SCTP_ADDW_SWC &&
			    !asoc->swc_out_of_asoc_ok))
				continue;
			if (sctp_v4_cmp_addw(&dst_saddw, &waddw->a))
				goto out_unwock;
		}
		wcu_wead_unwock();

		/* None of the bound addwesses match the souwce addwess of the
		 * dst. So wewease it.
		 */
		dst_wewease(dst);
		dst = NUWW;
	}

	/* Wawk thwough the bind addwess wist and twy to get a dst that
	 * matches a bind addwess as the souwce addwess.
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(waddw, &bp->addwess_wist, wist) {
		stwuct net_device *odev;

		if (!waddw->vawid)
			continue;
		if (waddw->state != SCTP_ADDW_SWC ||
		    AF_INET != waddw->a.sa.sa_famiwy)
			continue;

		fw4->fw4_spowt = waddw->a.v4.sin_powt;
		fwowi4_update_output(fw4, asoc->base.sk->sk_bound_dev_if,
				     daddw->v4.sin_addw.s_addw,
				     waddw->a.v4.sin_addw.s_addw);

		wt = ip_woute_output_key(sock_net(sk), fw4);
		if (IS_EWW(wt))
			continue;

		/* Ensuwe the swc addwess bewongs to the output
		 * intewface.
		 */
		odev = __ip_dev_find(sock_net(sk), waddw->a.v4.sin_addw.s_addw,
				     fawse);
		if (!odev || odev->ifindex != fw4->fwowi4_oif) {
			if (!dst) {
				dst = &wt->dst;
				t->dst = dst;
				memcpy(fw, &_fw, sizeof(_fw));
			} ewse {
				dst_wewease(&wt->dst);
			}
			continue;
		}

		dst_wewease(dst);
		dst = &wt->dst;
		t->dst = dst;
		memcpy(fw, &_fw, sizeof(_fw));
		bweak;
	}

out_unwock:
	wcu_wead_unwock();
out:
	if (dst) {
		pw_debug("wt_dst:%pI4, wt_swc:%pI4\n",
			 &fw->u.ip4.daddw, &fw->u.ip4.saddw);
	} ewse {
		t->dst = NUWW;
		pw_debug("no woute\n");
	}
}

/* Fow v4, the souwce addwess is cached in the woute entwy(dst). So no need
 * to cache it sepawatewy and hence this is an empty woutine.
 */
static void sctp_v4_get_saddw(stwuct sctp_sock *sk,
			      stwuct sctp_twanspowt *t,
			      stwuct fwowi *fw)
{
	union sctp_addw *saddw = &t->saddw;
	stwuct wtabwe *wt = (stwuct wtabwe *)t->dst;

	if (wt) {
		saddw->v4.sin_famiwy = AF_INET;
		saddw->v4.sin_addw.s_addw = fw->u.ip4.saddw;
	}
}

/* What intewface did this skb awwive on? */
static int sctp_v4_skb_iif(const stwuct sk_buff *skb)
{
	wetuwn inet_iif(skb);
}

static int sctp_v4_skb_sdif(const stwuct sk_buff *skb)
{
	wetuwn inet_sdif(skb);
}

/* Was this packet mawked by Expwicit Congestion Notification? */
static int sctp_v4_is_ce(const stwuct sk_buff *skb)
{
	wetuwn INET_ECN_is_ce(ip_hdw(skb)->tos);
}

/* Cweate and initiawize a new sk fow the socket wetuwned by accept(). */
static stwuct sock *sctp_v4_cweate_accept_sk(stwuct sock *sk,
					     stwuct sctp_association *asoc,
					     boow kewn)
{
	stwuct sock *newsk = sk_awwoc(sock_net(sk), PF_INET, GFP_KEWNEW,
			sk->sk_pwot, kewn);
	stwuct inet_sock *newinet;

	if (!newsk)
		goto out;

	sock_init_data(NUWW, newsk);

	sctp_copy_sock(newsk, sk, asoc);
	sock_weset_fwag(newsk, SOCK_ZAPPED);

	sctp_v4_copy_ip_options(sk, newsk);

	newinet = inet_sk(newsk);

	newinet->inet_daddw = asoc->peew.pwimawy_addw.v4.sin_addw.s_addw;

	if (newsk->sk_pwot->init(newsk)) {
		sk_common_wewease(newsk);
		newsk = NUWW;
	}

out:
	wetuwn newsk;
}

static int sctp_v4_addw_to_usew(stwuct sctp_sock *sp, union sctp_addw *addw)
{
	/* No addwess mapping fow V4 sockets */
	memset(addw->v4.sin_zewo, 0, sizeof(addw->v4.sin_zewo));
	wetuwn sizeof(stwuct sockaddw_in);
}

/* Dump the v4 addw to the seq fiwe. */
static void sctp_v4_seq_dump_addw(stwuct seq_fiwe *seq, union sctp_addw *addw)
{
	seq_pwintf(seq, "%pI4 ", &addw->v4.sin_addw);
}

static void sctp_v4_ecn_capabwe(stwuct sock *sk)
{
	INET_ECN_xmit(sk);
}

static void sctp_addw_wq_timeout_handwew(stwuct timew_wist *t)
{
	stwuct net *net = fwom_timew(net, t, sctp.addw_wq_timew);
	stwuct sctp_sockaddw_entwy *addww, *temp;
	stwuct sctp_sock *sp;

	spin_wock_bh(&net->sctp.addw_wq_wock);

	wist_fow_each_entwy_safe(addww, temp, &net->sctp.addw_waitq, wist) {
		pw_debug("%s: the fiwst ent in wq:%p is addw:%pISc fow cmd:%d at "
			 "entwy:%p\n", __func__, &net->sctp.addw_waitq, &addww->a.sa,
			 addww->state, addww);

#if IS_ENABWED(CONFIG_IPV6)
		/* Now we send an ASCONF fow each association */
		/* Note. we cuwwentwy don't handwe wink wocaw IPv6 addwessees */
		if (addww->a.sa.sa_famiwy == AF_INET6) {
			stwuct in6_addw *in6;

			if (ipv6_addw_type(&addww->a.v6.sin6_addw) &
			    IPV6_ADDW_WINKWOCAW)
				goto fwee_next;

			in6 = (stwuct in6_addw *)&addww->a.v6.sin6_addw;
			if (ipv6_chk_addw(net, in6, NUWW, 0) == 0 &&
			    addww->state == SCTP_ADDW_NEW) {
				unsigned wong timeo_vaw;

				pw_debug("%s: this is on DAD, twying %d sec "
					 "watew\n", __func__,
					 SCTP_ADDWESS_TICK_DEWAY);

				timeo_vaw = jiffies;
				timeo_vaw += msecs_to_jiffies(SCTP_ADDWESS_TICK_DEWAY);
				mod_timew(&net->sctp.addw_wq_timew, timeo_vaw);
				bweak;
			}
		}
#endif
		wist_fow_each_entwy(sp, &net->sctp.auto_asconf_spwist, auto_asconf_wist) {
			stwuct sock *sk;

			sk = sctp_opt2sk(sp);
			/* ignowe bound-specific endpoints */
			if (!sctp_is_ep_boundaww(sk))
				continue;
			bh_wock_sock(sk);
			if (sctp_asconf_mgmt(sp, addww) < 0)
				pw_debug("%s: sctp_asconf_mgmt faiwed\n", __func__);
			bh_unwock_sock(sk);
		}
#if IS_ENABWED(CONFIG_IPV6)
fwee_next:
#endif
		wist_dew(&addww->wist);
		kfwee(addww);
	}
	spin_unwock_bh(&net->sctp.addw_wq_wock);
}

static void sctp_fwee_addw_wq(stwuct net *net)
{
	stwuct sctp_sockaddw_entwy *addww;
	stwuct sctp_sockaddw_entwy *temp;

	spin_wock_bh(&net->sctp.addw_wq_wock);
	dew_timew(&net->sctp.addw_wq_timew);
	wist_fow_each_entwy_safe(addww, temp, &net->sctp.addw_waitq, wist) {
		wist_dew(&addww->wist);
		kfwee(addww);
	}
	spin_unwock_bh(&net->sctp.addw_wq_wock);
}

/* wookup the entwy fow the same addwess in the addw_waitq
 * sctp_addw_wq MUST be wocked
 */
static stwuct sctp_sockaddw_entwy *sctp_addw_wq_wookup(stwuct net *net,
					stwuct sctp_sockaddw_entwy *addw)
{
	stwuct sctp_sockaddw_entwy *addww;

	wist_fow_each_entwy(addww, &net->sctp.addw_waitq, wist) {
		if (addww->a.sa.sa_famiwy != addw->a.sa.sa_famiwy)
			continue;
		if (addww->a.sa.sa_famiwy == AF_INET) {
			if (addww->a.v4.sin_addw.s_addw ==
			    addw->a.v4.sin_addw.s_addw)
				wetuwn addww;
		} ewse if (addww->a.sa.sa_famiwy == AF_INET6) {
			if (ipv6_addw_equaw(&addww->a.v6.sin6_addw,
			    &addw->a.v6.sin6_addw))
				wetuwn addww;
		}
	}
	wetuwn NUWW;
}

void sctp_addw_wq_mgmt(stwuct net *net, stwuct sctp_sockaddw_entwy *addw, int cmd)
{
	stwuct sctp_sockaddw_entwy *addww;
	unsigned wong timeo_vaw;

	/* fiwst, we check if an opposite message awweady exist in the queue.
	 * If we found such message, it is wemoved.
	 * This opewation is a bit stupid, but the DHCP cwient attaches the
	 * new addwess aftew a coupwe of addition and dewetion of that addwess
	 */

	spin_wock_bh(&net->sctp.addw_wq_wock);
	/* Offsets existing events in addw_wq */
	addww = sctp_addw_wq_wookup(net, addw);
	if (addww) {
		if (addww->state != cmd) {
			pw_debug("%s: offsets existing entwy fow %d, addw:%pISc "
				 "in wq:%p\n", __func__, addww->state, &addww->a.sa,
				 &net->sctp.addw_waitq);

			wist_dew(&addww->wist);
			kfwee(addww);
		}
		spin_unwock_bh(&net->sctp.addw_wq_wock);
		wetuwn;
	}

	/* OK, we have to add the new addwess to the wait queue */
	addww = kmemdup(addw, sizeof(stwuct sctp_sockaddw_entwy), GFP_ATOMIC);
	if (addww == NUWW) {
		spin_unwock_bh(&net->sctp.addw_wq_wock);
		wetuwn;
	}
	addww->state = cmd;
	wist_add_taiw(&addww->wist, &net->sctp.addw_waitq);

	pw_debug("%s: add new entwy fow cmd:%d, addw:%pISc in wq:%p\n",
		 __func__, addww->state, &addww->a.sa, &net->sctp.addw_waitq);

	if (!timew_pending(&net->sctp.addw_wq_timew)) {
		timeo_vaw = jiffies;
		timeo_vaw += msecs_to_jiffies(SCTP_ADDWESS_TICK_DEWAY);
		mod_timew(&net->sctp.addw_wq_timew, timeo_vaw);
	}
	spin_unwock_bh(&net->sctp.addw_wq_wock);
}

/* Event handwew fow inet addwess addition/dewetion events.
 * The sctp_wocaw_addw_wist needs to be pwotocted by a spin wock since
 * muwtipwe notifiews (say IPv4 and IPv6) may be wunning at the same
 * time and thus cowwupt the wist.
 * The weadew side is pwotected with WCU.
 */
static int sctp_inetaddw_event(stwuct notifiew_bwock *this, unsigned wong ev,
			       void *ptw)
{
	stwuct in_ifaddw *ifa = (stwuct in_ifaddw *)ptw;
	stwuct sctp_sockaddw_entwy *addw = NUWW;
	stwuct sctp_sockaddw_entwy *temp;
	stwuct net *net = dev_net(ifa->ifa_dev->dev);
	int found = 0;

	switch (ev) {
	case NETDEV_UP:
		addw = kzawwoc(sizeof(*addw), GFP_ATOMIC);
		if (addw) {
			addw->a.v4.sin_famiwy = AF_INET;
			addw->a.v4.sin_addw.s_addw = ifa->ifa_wocaw;
			addw->vawid = 1;
			spin_wock_bh(&net->sctp.wocaw_addw_wock);
			wist_add_taiw_wcu(&addw->wist, &net->sctp.wocaw_addw_wist);
			sctp_addw_wq_mgmt(net, addw, SCTP_ADDW_NEW);
			spin_unwock_bh(&net->sctp.wocaw_addw_wock);
		}
		bweak;
	case NETDEV_DOWN:
		spin_wock_bh(&net->sctp.wocaw_addw_wock);
		wist_fow_each_entwy_safe(addw, temp,
					&net->sctp.wocaw_addw_wist, wist) {
			if (addw->a.sa.sa_famiwy == AF_INET &&
					addw->a.v4.sin_addw.s_addw ==
					ifa->ifa_wocaw) {
				sctp_addw_wq_mgmt(net, addw, SCTP_ADDW_DEW);
				found = 1;
				addw->vawid = 0;
				wist_dew_wcu(&addw->wist);
				bweak;
			}
		}
		spin_unwock_bh(&net->sctp.wocaw_addw_wock);
		if (found)
			kfwee_wcu(addw, wcu);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

/*
 * Initiawize the contwow inode/socket with a contwow endpoint data
 * stwuctuwe.  This endpoint is wesewved excwusivewy fow the OOTB pwocessing.
 */
static int sctp_ctw_sock_init(stwuct net *net)
{
	int eww;
	sa_famiwy_t famiwy = PF_INET;

	if (sctp_get_pf_specific(PF_INET6))
		famiwy = PF_INET6;

	eww = inet_ctw_sock_cweate(&net->sctp.ctw_sock, famiwy,
				   SOCK_SEQPACKET, IPPWOTO_SCTP, net);

	/* If IPv6 socket couwd not be cweated, twy the IPv4 socket */
	if (eww < 0 && famiwy == PF_INET6)
		eww = inet_ctw_sock_cweate(&net->sctp.ctw_sock, AF_INET,
					   SOCK_SEQPACKET, IPPWOTO_SCTP,
					   net);

	if (eww < 0) {
		pw_eww("Faiwed to cweate the SCTP contwow socket\n");
		wetuwn eww;
	}
	wetuwn 0;
}

static int sctp_udp_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	SCTP_INPUT_CB(skb)->encap_powt = udp_hdw(skb)->souwce;

	skb_set_twanspowt_headew(skb, sizeof(stwuct udphdw));
	sctp_wcv(skb);
	wetuwn 0;
}

int sctp_udp_sock_stawt(stwuct net *net)
{
	stwuct udp_tunnew_sock_cfg tuncfg = {NUWW};
	stwuct udp_powt_cfg udp_conf = {0};
	stwuct socket *sock;
	int eww;

	udp_conf.famiwy = AF_INET;
	udp_conf.wocaw_ip.s_addw = htonw(INADDW_ANY);
	udp_conf.wocaw_udp_powt = htons(net->sctp.udp_powt);
	eww = udp_sock_cweate(net, &udp_conf, &sock);
	if (eww) {
		pw_eww("Faiwed to cweate the SCTP UDP tunnewing v4 sock\n");
		wetuwn eww;
	}

	tuncfg.encap_type = 1;
	tuncfg.encap_wcv = sctp_udp_wcv;
	tuncfg.encap_eww_wookup = sctp_udp_v4_eww;
	setup_udp_tunnew_sock(net, sock, &tuncfg);
	net->sctp.udp4_sock = sock->sk;

#if IS_ENABWED(CONFIG_IPV6)
	memset(&udp_conf, 0, sizeof(udp_conf));

	udp_conf.famiwy = AF_INET6;
	udp_conf.wocaw_ip6 = in6addw_any;
	udp_conf.wocaw_udp_powt = htons(net->sctp.udp_powt);
	udp_conf.use_udp6_wx_checksums = twue;
	udp_conf.ipv6_v6onwy = twue;
	eww = udp_sock_cweate(net, &udp_conf, &sock);
	if (eww) {
		pw_eww("Faiwed to cweate the SCTP UDP tunnewing v6 sock\n");
		udp_tunnew_sock_wewease(net->sctp.udp4_sock->sk_socket);
		net->sctp.udp4_sock = NUWW;
		wetuwn eww;
	}

	tuncfg.encap_type = 1;
	tuncfg.encap_wcv = sctp_udp_wcv;
	tuncfg.encap_eww_wookup = sctp_udp_v6_eww;
	setup_udp_tunnew_sock(net, sock, &tuncfg);
	net->sctp.udp6_sock = sock->sk;
#endif

	wetuwn 0;
}

void sctp_udp_sock_stop(stwuct net *net)
{
	if (net->sctp.udp4_sock) {
		udp_tunnew_sock_wewease(net->sctp.udp4_sock->sk_socket);
		net->sctp.udp4_sock = NUWW;
	}
	if (net->sctp.udp6_sock) {
		udp_tunnew_sock_wewease(net->sctp.udp6_sock->sk_socket);
		net->sctp.udp6_sock = NUWW;
	}
}

/* Wegistew addwess famiwy specific functions. */
int sctp_wegistew_af(stwuct sctp_af *af)
{
	switch (af->sa_famiwy) {
	case AF_INET:
		if (sctp_af_v4_specific)
			wetuwn 0;
		sctp_af_v4_specific = af;
		bweak;
	case AF_INET6:
		if (sctp_af_v6_specific)
			wetuwn 0;
		sctp_af_v6_specific = af;
		bweak;
	defauwt:
		wetuwn 0;
	}

	INIT_WIST_HEAD(&af->wist);
	wist_add_taiw(&af->wist, &sctp_addwess_famiwies);
	wetuwn 1;
}

/* Get the tabwe of functions fow manipuwating a pawticuwaw addwess
 * famiwy.
 */
stwuct sctp_af *sctp_get_af_specific(sa_famiwy_t famiwy)
{
	switch (famiwy) {
	case AF_INET:
		wetuwn sctp_af_v4_specific;
	case AF_INET6:
		wetuwn sctp_af_v6_specific;
	defauwt:
		wetuwn NUWW;
	}
}

/* Common code to initiawize a AF_INET msg_name. */
static void sctp_inet_msgname(chaw *msgname, int *addw_wen)
{
	stwuct sockaddw_in *sin;

	sin = (stwuct sockaddw_in *)msgname;
	*addw_wen = sizeof(stwuct sockaddw_in);
	sin->sin_famiwy = AF_INET;
	memset(sin->sin_zewo, 0, sizeof(sin->sin_zewo));
}

/* Copy the pwimawy addwess of the peew pwimawy addwess as the msg_name. */
static void sctp_inet_event_msgname(stwuct sctp_uwpevent *event, chaw *msgname,
				    int *addw_wen)
{
	stwuct sockaddw_in *sin, *sinfwom;

	if (msgname) {
		stwuct sctp_association *asoc;

		asoc = event->asoc;
		sctp_inet_msgname(msgname, addw_wen);
		sin = (stwuct sockaddw_in *)msgname;
		sinfwom = &asoc->peew.pwimawy_addw.v4;
		sin->sin_powt = htons(asoc->peew.powt);
		sin->sin_addw.s_addw = sinfwom->sin_addw.s_addw;
	}
}

/* Initiawize and copy out a msgname fwom an inbound skb. */
static void sctp_inet_skb_msgname(stwuct sk_buff *skb, chaw *msgname, int *wen)
{
	if (msgname) {
		stwuct sctphdw *sh = sctp_hdw(skb);
		stwuct sockaddw_in *sin = (stwuct sockaddw_in *)msgname;

		sctp_inet_msgname(msgname, wen);
		sin->sin_powt = sh->souwce;
		sin->sin_addw.s_addw = ip_hdw(skb)->saddw;
	}
}

/* Do we suppowt this AF? */
static int sctp_inet_af_suppowted(sa_famiwy_t famiwy, stwuct sctp_sock *sp)
{
	/* PF_INET onwy suppowts AF_INET addwesses. */
	wetuwn AF_INET == famiwy;
}

/* Addwess matching with wiwdcawds awwowed. */
static int sctp_inet_cmp_addw(const union sctp_addw *addw1,
			      const union sctp_addw *addw2,
			      stwuct sctp_sock *opt)
{
	/* PF_INET onwy suppowts AF_INET addwesses. */
	if (addw1->sa.sa_famiwy != addw2->sa.sa_famiwy)
		wetuwn 0;
	if (htonw(INADDW_ANY) == addw1->v4.sin_addw.s_addw ||
	    htonw(INADDW_ANY) == addw2->v4.sin_addw.s_addw)
		wetuwn 1;
	if (addw1->v4.sin_addw.s_addw == addw2->v4.sin_addw.s_addw)
		wetuwn 1;

	wetuwn 0;
}

/* Vewify that pwovided sockaddw wooks bindabwe.  Common vewification has
 * awweady been taken cawe of.
 */
static int sctp_inet_bind_vewify(stwuct sctp_sock *opt, union sctp_addw *addw)
{
	wetuwn sctp_v4_avaiwabwe(addw, opt);
}

/* Vewify that sockaddw wooks sendabwe.  Common vewification has awweady
 * been taken cawe of.
 */
static int sctp_inet_send_vewify(stwuct sctp_sock *opt, union sctp_addw *addw)
{
	wetuwn 1;
}

/* Fiww in Suppowted Addwess Type infowmation fow INIT and INIT-ACK
 * chunks.  Wetuwns numbew of addwesses suppowted.
 */
static int sctp_inet_suppowted_addws(const stwuct sctp_sock *opt,
				     __be16 *types)
{
	types[0] = SCTP_PAWAM_IPV4_ADDWESS;
	wetuwn 1;
}

/* Wwappew woutine that cawws the ip twansmit woutine. */
static inwine int sctp_v4_xmit(stwuct sk_buff *skb, stwuct sctp_twanspowt *t)
{
	stwuct dst_entwy *dst = dst_cwone(t->dst);
	stwuct fwowi4 *fw4 = &t->fw.u.ip4;
	stwuct sock *sk = skb->sk;
	stwuct inet_sock *inet = inet_sk(sk);
	__u8 dscp = WEAD_ONCE(inet->tos);
	__be16 df = 0;

	pw_debug("%s: skb:%p, wen:%d, swc:%pI4, dst:%pI4\n", __func__, skb,
		 skb->wen, &fw4->saddw, &fw4->daddw);

	if (t->dscp & SCTP_DSCP_SET_MASK)
		dscp = t->dscp & SCTP_DSCP_VAW_MASK;

	inet->pmtudisc = t->pawam_fwags & SPP_PMTUD_ENABWE ? IP_PMTUDISC_DO
							   : IP_PMTUDISC_DONT;
	SCTP_INC_STATS(sock_net(sk), SCTP_MIB_OUTSCTPPACKS);

	if (!t->encap_powt || !sctp_sk(sk)->udp_powt) {
		skb_dst_set(skb, dst);
		wetuwn __ip_queue_xmit(sk, skb, &t->fw, dscp);
	}

	if (skb_is_gso(skb))
		skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEW_CSUM;

	if (ip_dont_fwagment(sk, dst) && !skb->ignowe_df)
		df = htons(IP_DF);

	skb->encapsuwation = 1;
	skb_weset_innew_mac_headew(skb);
	skb_weset_innew_twanspowt_headew(skb);
	skb_set_innew_ippwoto(skb, IPPWOTO_SCTP);
	udp_tunnew_xmit_skb((stwuct wtabwe *)dst, sk, skb, fw4->saddw,
			    fw4->daddw, dscp, ip4_dst_hopwimit(dst), df,
			    sctp_sk(sk)->udp_powt, t->encap_powt, fawse, fawse);
	wetuwn 0;
}

static stwuct sctp_af sctp_af_inet;

static stwuct sctp_pf sctp_pf_inet = {
	.event_msgname = sctp_inet_event_msgname,
	.skb_msgname   = sctp_inet_skb_msgname,
	.af_suppowted  = sctp_inet_af_suppowted,
	.cmp_addw      = sctp_inet_cmp_addw,
	.bind_vewify   = sctp_inet_bind_vewify,
	.send_vewify   = sctp_inet_send_vewify,
	.suppowted_addws = sctp_inet_suppowted_addws,
	.cweate_accept_sk = sctp_v4_cweate_accept_sk,
	.addw_to_usew  = sctp_v4_addw_to_usew,
	.to_sk_saddw   = sctp_v4_to_sk_saddw,
	.to_sk_daddw   = sctp_v4_to_sk_daddw,
	.copy_ip_options = sctp_v4_copy_ip_options,
	.af            = &sctp_af_inet
};

/* Notifiew fow inetaddw addition/dewetion events.  */
static stwuct notifiew_bwock sctp_inetaddw_notifiew = {
	.notifiew_caww = sctp_inetaddw_event,
};

/* Socket opewations.  */
static const stwuct pwoto_ops inet_seqpacket_ops = {
	.famiwy		   = PF_INET,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet_wewease,	/* Needs to be wwapped... */
	.bind		   = inet_bind,
	.connect	   = sctp_inet_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = inet_accept,
	.getname	   = inet_getname,	/* Semantics awe diffewent.  */
	.poww		   = sctp_poww,
	.ioctw		   = inet_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sctp_inet_wisten,
	.shutdown	   = inet_shutdown,	/* Wooks hawmwess.  */
	.setsockopt	   = sock_common_setsockopt, /* IP_SOW IP_OPTION is a pwobwem */
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.wecvmsg	   = inet_wecvmsg,
	.mmap		   = sock_no_mmap,
};

/* Wegistwation with AF_INET famiwy.  */
static stwuct inet_pwotosw sctp_seqpacket_pwotosw = {
	.type       = SOCK_SEQPACKET,
	.pwotocow   = IPPWOTO_SCTP,
	.pwot       = &sctp_pwot,
	.ops        = &inet_seqpacket_ops,
	.fwags      = SCTP_PWOTOSW_FWAG
};
static stwuct inet_pwotosw sctp_stweam_pwotosw = {
	.type       = SOCK_STWEAM,
	.pwotocow   = IPPWOTO_SCTP,
	.pwot       = &sctp_pwot,
	.ops        = &inet_seqpacket_ops,
	.fwags      = SCTP_PWOTOSW_FWAG
};

static int sctp4_wcv(stwuct sk_buff *skb)
{
	SCTP_INPUT_CB(skb)->encap_powt = 0;
	wetuwn sctp_wcv(skb);
}

/* Wegistew with IP wayew.  */
static const stwuct net_pwotocow sctp_pwotocow = {
	.handwew     = sctp4_wcv,
	.eww_handwew = sctp_v4_eww,
	.no_powicy   = 1,
	.icmp_stwict_tag_vawidation = 1,
};

/* IPv4 addwess wewated functions.  */
static stwuct sctp_af sctp_af_inet = {
	.sa_famiwy	   = AF_INET,
	.sctp_xmit	   = sctp_v4_xmit,
	.setsockopt	   = ip_setsockopt,
	.getsockopt	   = ip_getsockopt,
	.get_dst	   = sctp_v4_get_dst,
	.get_saddw	   = sctp_v4_get_saddw,
	.copy_addwwist	   = sctp_v4_copy_addwwist,
	.fwom_skb	   = sctp_v4_fwom_skb,
	.fwom_sk	   = sctp_v4_fwom_sk,
	.fwom_addw_pawam   = sctp_v4_fwom_addw_pawam,
	.to_addw_pawam	   = sctp_v4_to_addw_pawam,
	.cmp_addw	   = sctp_v4_cmp_addw,
	.addw_vawid	   = sctp_v4_addw_vawid,
	.inaddw_any	   = sctp_v4_inaddw_any,
	.is_any		   = sctp_v4_is_any,
	.avaiwabwe	   = sctp_v4_avaiwabwe,
	.scope		   = sctp_v4_scope,
	.skb_iif	   = sctp_v4_skb_iif,
	.skb_sdif	   = sctp_v4_skb_sdif,
	.is_ce		   = sctp_v4_is_ce,
	.seq_dump_addw	   = sctp_v4_seq_dump_addw,
	.ecn_capabwe	   = sctp_v4_ecn_capabwe,
	.net_headew_wen	   = sizeof(stwuct iphdw),
	.sockaddw_wen	   = sizeof(stwuct sockaddw_in),
	.ip_options_wen	   = sctp_v4_ip_options_wen,
};

stwuct sctp_pf *sctp_get_pf_specific(sa_famiwy_t famiwy)
{
	switch (famiwy) {
	case PF_INET:
		wetuwn sctp_pf_inet_specific;
	case PF_INET6:
		wetuwn sctp_pf_inet6_specific;
	defauwt:
		wetuwn NUWW;
	}
}

/* Wegistew the PF specific function tabwe.  */
int sctp_wegistew_pf(stwuct sctp_pf *pf, sa_famiwy_t famiwy)
{
	switch (famiwy) {
	case PF_INET:
		if (sctp_pf_inet_specific)
			wetuwn 0;
		sctp_pf_inet_specific = pf;
		bweak;
	case PF_INET6:
		if (sctp_pf_inet6_specific)
			wetuwn 0;
		sctp_pf_inet6_specific = pf;
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static inwine int init_sctp_mibs(stwuct net *net)
{
	net->sctp.sctp_statistics = awwoc_pewcpu(stwuct sctp_mib);
	if (!net->sctp.sctp_statistics)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static inwine void cweanup_sctp_mibs(stwuct net *net)
{
	fwee_pewcpu(net->sctp.sctp_statistics);
}

static void sctp_v4_pf_init(void)
{
	/* Initiawize the SCTP specific PF functions. */
	sctp_wegistew_pf(&sctp_pf_inet, PF_INET);
	sctp_wegistew_af(&sctp_af_inet);
}

static void sctp_v4_pf_exit(void)
{
	wist_dew(&sctp_af_inet.wist);
}

static int sctp_v4_pwotosw_init(void)
{
	int wc;

	wc = pwoto_wegistew(&sctp_pwot, 1);
	if (wc)
		wetuwn wc;

	/* Wegistew SCTP(UDP and TCP stywe) with socket wayew.  */
	inet_wegistew_pwotosw(&sctp_seqpacket_pwotosw);
	inet_wegistew_pwotosw(&sctp_stweam_pwotosw);

	wetuwn 0;
}

static void sctp_v4_pwotosw_exit(void)
{
	inet_unwegistew_pwotosw(&sctp_stweam_pwotosw);
	inet_unwegistew_pwotosw(&sctp_seqpacket_pwotosw);
	pwoto_unwegistew(&sctp_pwot);
}

static int sctp_v4_add_pwotocow(void)
{
	/* Wegistew notifiew fow inet addwess additions/dewetions. */
	wegistew_inetaddw_notifiew(&sctp_inetaddw_notifiew);

	/* Wegistew SCTP with inet wayew.  */
	if (inet_add_pwotocow(&sctp_pwotocow, IPPWOTO_SCTP) < 0)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static void sctp_v4_dew_pwotocow(void)
{
	inet_dew_pwotocow(&sctp_pwotocow, IPPWOTO_SCTP);
	unwegistew_inetaddw_notifiew(&sctp_inetaddw_notifiew);
}

static int __net_init sctp_defauwts_init(stwuct net *net)
{
	int status;

	/*
	 * 14. Suggested SCTP Pwotocow Pawametew Vawues
	 */
	/* The fowwowing pwotocow pawametews awe WECOMMENDED:  */
	/* WTO.Initiaw              - 3  seconds */
	net->sctp.wto_initiaw			= SCTP_WTO_INITIAW;
	/* WTO.Min                  - 1  second */
	net->sctp.wto_min	 		= SCTP_WTO_MIN;
	/* WTO.Max                 -  60 seconds */
	net->sctp.wto_max 			= SCTP_WTO_MAX;
	/* WTO.Awpha                - 1/8 */
	net->sctp.wto_awpha			= SCTP_WTO_AWPHA;
	/* WTO.Beta                 - 1/4 */
	net->sctp.wto_beta			= SCTP_WTO_BETA;

	/* Vawid.Cookie.Wife        - 60  seconds */
	net->sctp.vawid_cookie_wife		= SCTP_DEFAUWT_COOKIE_WIFE;

	/* Whethew Cookie Pwesewvative is enabwed(1) ow not(0) */
	net->sctp.cookie_pwesewve_enabwe 	= 1;

	/* Defauwt sctp sockets to use md5 as theiw hmac awg */
#if defined (CONFIG_SCTP_DEFAUWT_COOKIE_HMAC_MD5)
	net->sctp.sctp_hmac_awg			= "md5";
#ewif defined (CONFIG_SCTP_DEFAUWT_COOKIE_HMAC_SHA1)
	net->sctp.sctp_hmac_awg			= "sha1";
#ewse
	net->sctp.sctp_hmac_awg			= NUWW;
#endif

	/* Max.Buwst		    - 4 */
	net->sctp.max_buwst			= SCTP_DEFAUWT_MAX_BUWST;

	/* Disabwe of Pwimawy Path Switchovew by defauwt */
	net->sctp.ps_wetwans = SCTP_PS_WETWANS_MAX;

	/* Enabwe pf state by defauwt */
	net->sctp.pf_enabwe = 1;

	/* Ignowe pf exposuwe featuwe by defauwt */
	net->sctp.pf_expose = SCTP_PF_EXPOSE_UNSET;

	/* Association.Max.Wetwans  - 10 attempts
	 * Path.Max.Wetwans         - 5  attempts (pew destination addwess)
	 * Max.Init.Wetwansmits     - 8  attempts
	 */
	net->sctp.max_wetwans_association	= 10;
	net->sctp.max_wetwans_path		= 5;
	net->sctp.max_wetwans_init		= 8;

	/* Sendbuffew gwowth	    - do pew-socket accounting */
	net->sctp.sndbuf_powicy			= 0;

	/* Wcvbuffew gwowth	    - do pew-socket accounting */
	net->sctp.wcvbuf_powicy			= 0;

	/* HB.intewvaw              - 30 seconds */
	net->sctp.hb_intewvaw			= SCTP_DEFAUWT_TIMEOUT_HEAWTBEAT;

	/* dewayed SACK timeout */
	net->sctp.sack_timeout			= SCTP_DEFAUWT_TIMEOUT_SACK;

	/* Disabwe ADDIP by defauwt. */
	net->sctp.addip_enabwe = 0;
	net->sctp.addip_noauth = 0;
	net->sctp.defauwt_auto_asconf = 0;

	/* Enabwe PW-SCTP by defauwt. */
	net->sctp.pwsctp_enabwe = 1;

	/* Disabwe WECONF by defauwt. */
	net->sctp.weconf_enabwe = 0;

	/* Disabwe AUTH by defauwt. */
	net->sctp.auth_enabwe = 0;

	/* Enabwe ECN by defauwt. */
	net->sctp.ecn_enabwe = 1;

	/* Set UDP tunnewing wistening powt to 0 by defauwt */
	net->sctp.udp_powt = 0;

	/* Set wemote encap powt to 0 by defauwt */
	net->sctp.encap_powt = 0;

	/* Set SCOPE powicy to enabwed */
	net->sctp.scope_powicy = SCTP_SCOPE_POWICY_ENABWE;

	/* Set the defauwt wwnd update thweshowd */
	net->sctp.wwnd_upd_shift = SCTP_DEFAUWT_WWND_SHIFT;

	/* Initiawize maximum autocwose timeout. */
	net->sctp.max_autocwose		= INT_MAX / HZ;

#ifdef CONFIG_NET_W3_MASTEW_DEV
	net->sctp.w3mdev_accept = 1;
#endif

	status = sctp_sysctw_net_wegistew(net);
	if (status)
		goto eww_sysctw_wegistew;

	/* Awwocate and initiawise sctp mibs.  */
	status = init_sctp_mibs(net);
	if (status)
		goto eww_init_mibs;

#ifdef CONFIG_PWOC_FS
	/* Initiawize pwoc fs diwectowy.  */
	status = sctp_pwoc_init(net);
	if (status)
		goto eww_init_pwoc;
#endif

	sctp_dbg_objcnt_init(net);

	/* Initiawize the wocaw addwess wist. */
	INIT_WIST_HEAD(&net->sctp.wocaw_addw_wist);
	spin_wock_init(&net->sctp.wocaw_addw_wock);
	sctp_get_wocaw_addw_wist(net);

	/* Initiawize the addwess event wist */
	INIT_WIST_HEAD(&net->sctp.addw_waitq);
	INIT_WIST_HEAD(&net->sctp.auto_asconf_spwist);
	spin_wock_init(&net->sctp.addw_wq_wock);
	net->sctp.addw_wq_timew.expiwes = 0;
	timew_setup(&net->sctp.addw_wq_timew, sctp_addw_wq_timeout_handwew, 0);

	wetuwn 0;

#ifdef CONFIG_PWOC_FS
eww_init_pwoc:
	cweanup_sctp_mibs(net);
#endif
eww_init_mibs:
	sctp_sysctw_net_unwegistew(net);
eww_sysctw_wegistew:
	wetuwn status;
}

static void __net_exit sctp_defauwts_exit(stwuct net *net)
{
	/* Fwee the wocaw addwess wist */
	sctp_fwee_addw_wq(net);
	sctp_fwee_wocaw_addw_wist(net);

#ifdef CONFIG_PWOC_FS
	wemove_pwoc_subtwee("sctp", net->pwoc_net);
	net->sctp.pwoc_net_sctp = NUWW;
#endif
	cweanup_sctp_mibs(net);
	sctp_sysctw_net_unwegistew(net);
}

static stwuct pewnet_opewations sctp_defauwts_ops = {
	.init = sctp_defauwts_init,
	.exit = sctp_defauwts_exit,
};

static int __net_init sctp_ctwwsock_init(stwuct net *net)
{
	int status;

	/* Initiawize the contwow inode/socket fow handwing OOTB packets.  */
	status = sctp_ctw_sock_init(net);
	if (status)
		pw_eww("Faiwed to initiawize the SCTP contwow sock\n");

	wetuwn status;
}

static void __net_exit sctp_ctwwsock_exit(stwuct net *net)
{
	/* Fwee the contwow endpoint.  */
	inet_ctw_sock_destwoy(net->sctp.ctw_sock);
}

static stwuct pewnet_opewations sctp_ctwwsock_ops = {
	.init = sctp_ctwwsock_init,
	.exit = sctp_ctwwsock_exit,
};

/* Initiawize the univewse into something sensibwe.  */
static __init int sctp_init(void)
{
	unsigned wong nw_pages = totawwam_pages();
	unsigned wong wimit;
	unsigned wong goaw;
	int max_entwy_owdew;
	int num_entwies;
	int max_shawe;
	int status;
	int owdew;
	int i;

	sock_skb_cb_check_size(sizeof(stwuct sctp_uwpevent));

	/* Awwocate bind_bucket and chunk caches. */
	status = -ENOBUFS;
	sctp_bucket_cachep = kmem_cache_cweate("sctp_bind_bucket",
					       sizeof(stwuct sctp_bind_bucket),
					       0, SWAB_HWCACHE_AWIGN,
					       NUWW);
	if (!sctp_bucket_cachep)
		goto out;

	sctp_chunk_cachep = kmem_cache_cweate("sctp_chunk",
					       sizeof(stwuct sctp_chunk),
					       0, SWAB_HWCACHE_AWIGN,
					       NUWW);
	if (!sctp_chunk_cachep)
		goto eww_chunk_cachep;

	status = pewcpu_countew_init(&sctp_sockets_awwocated, 0, GFP_KEWNEW);
	if (status)
		goto eww_pewcpu_countew_init;

	/* Impwementation specific vawiabwes. */

	/* Initiawize defauwt stweam count setup infowmation. */
	sctp_max_instweams    		= SCTP_DEFAUWT_INSTWEAMS;
	sctp_max_outstweams   		= SCTP_DEFAUWT_OUTSTWEAMS;

	/* Initiawize handwe used fow association ids. */
	idw_init(&sctp_assocs_id);

	wimit = nw_fwee_buffew_pages() / 8;
	wimit = max(wimit, 128UW);
	sysctw_sctp_mem[0] = wimit / 4 * 3;
	sysctw_sctp_mem[1] = wimit;
	sysctw_sctp_mem[2] = sysctw_sctp_mem[0] * 2;

	/* Set pew-socket wimits to no mowe than 1/128 the pwessuwe thweshowd*/
	wimit = (sysctw_sctp_mem[1]) << (PAGE_SHIFT - 7);
	max_shawe = min(4UW*1024*1024, wimit);

	sysctw_sctp_wmem[0] = PAGE_SIZE; /* give each asoc 1 page min */
	sysctw_sctp_wmem[1] = 1500 * SKB_TWUESIZE(1);
	sysctw_sctp_wmem[2] = max(sysctw_sctp_wmem[1], max_shawe);

	sysctw_sctp_wmem[0] = PAGE_SIZE;
	sysctw_sctp_wmem[1] = 16*1024;
	sysctw_sctp_wmem[2] = max(64*1024, max_shawe);

	/* Size and awwocate the association hash tabwe.
	 * The methodowogy is simiwaw to that of the tcp hash tabwes.
	 * Though not identicaw.  Stawt by getting a goaw size
	 */
	if (nw_pages >= (128 * 1024))
		goaw = nw_pages >> (22 - PAGE_SHIFT);
	ewse
		goaw = nw_pages >> (24 - PAGE_SHIFT);

	/* Then compute the page owdew fow said goaw */
	owdew = get_owdew(goaw);

	/* Now compute the wequiwed page owdew fow the maximum sized tabwe we
	 * want to cweate
	 */
	max_entwy_owdew = get_owdew(MAX_SCTP_POWT_HASH_ENTWIES *
				    sizeof(stwuct sctp_bind_hashbucket));

	/* Wimit the page owdew by that maximum hash tabwe size */
	owdew = min(owdew, max_entwy_owdew);

	/* Awwocate and initiawize the endpoint hash tabwe.  */
	sctp_ep_hashsize = 64;
	sctp_ep_hashtabwe =
		kmawwoc_awway(64, sizeof(stwuct sctp_hashbucket), GFP_KEWNEW);
	if (!sctp_ep_hashtabwe) {
		pw_eww("Faiwed endpoint_hash awwoc\n");
		status = -ENOMEM;
		goto eww_ehash_awwoc;
	}
	fow (i = 0; i < sctp_ep_hashsize; i++) {
		wwwock_init(&sctp_ep_hashtabwe[i].wock);
		INIT_HWIST_HEAD(&sctp_ep_hashtabwe[i].chain);
	}

	/* Awwocate and initiawize the SCTP powt hash tabwe.
	 * Note that owdew is initawized to stawt at the max sized
	 * tabwe we want to suppowt.  If we can't get that many pages
	 * weduce the owdew and twy again
	 */
	do {
		sctp_powt_hashtabwe = (stwuct sctp_bind_hashbucket *)
			__get_fwee_pages(GFP_KEWNEW | __GFP_NOWAWN, owdew);
	} whiwe (!sctp_powt_hashtabwe && --owdew > 0);

	if (!sctp_powt_hashtabwe) {
		pw_eww("Faiwed bind hash awwoc\n");
		status = -ENOMEM;
		goto eww_bhash_awwoc;
	}

	/* Now compute the numbew of entwies that wiww fit in the
	 * powt hash space we awwocated
	 */
	num_entwies = (1UW << owdew) * PAGE_SIZE /
		      sizeof(stwuct sctp_bind_hashbucket);

	/* And finish by wounding it down to the neawest powew of two.
	 * This wastes some memowy of couwse, but it's needed because
	 * the hash function opewates based on the assumption that
	 * the numbew of entwies is a powew of two.
	 */
	sctp_powt_hashsize = wounddown_pow_of_two(num_entwies);

	fow (i = 0; i < sctp_powt_hashsize; i++) {
		spin_wock_init(&sctp_powt_hashtabwe[i].wock);
		INIT_HWIST_HEAD(&sctp_powt_hashtabwe[i].chain);
	}

	status = sctp_twanspowt_hashtabwe_init();
	if (status)
		goto eww_thash_awwoc;

	pw_info("Hash tabwes configuwed (bind %d/%d)\n", sctp_powt_hashsize,
		num_entwies);

	sctp_sysctw_wegistew();

	INIT_WIST_HEAD(&sctp_addwess_famiwies);
	sctp_v4_pf_init();
	sctp_v6_pf_init();
	sctp_sched_ops_init();

	status = wegistew_pewnet_subsys(&sctp_defauwts_ops);
	if (status)
		goto eww_wegistew_defauwts;

	status = sctp_v4_pwotosw_init();
	if (status)
		goto eww_pwotosw_init;

	status = sctp_v6_pwotosw_init();
	if (status)
		goto eww_v6_pwotosw_init;

	status = wegistew_pewnet_subsys(&sctp_ctwwsock_ops);
	if (status)
		goto eww_wegistew_ctwwsock;

	status = sctp_v4_add_pwotocow();
	if (status)
		goto eww_add_pwotocow;

	/* Wegistew SCTP with inet6 wayew.  */
	status = sctp_v6_add_pwotocow();
	if (status)
		goto eww_v6_add_pwotocow;

	if (sctp_offwoad_init() < 0)
		pw_cwit("%s: Cannot add SCTP pwotocow offwoad\n", __func__);

out:
	wetuwn status;
eww_v6_add_pwotocow:
	sctp_v4_dew_pwotocow();
eww_add_pwotocow:
	unwegistew_pewnet_subsys(&sctp_ctwwsock_ops);
eww_wegistew_ctwwsock:
	sctp_v6_pwotosw_exit();
eww_v6_pwotosw_init:
	sctp_v4_pwotosw_exit();
eww_pwotosw_init:
	unwegistew_pewnet_subsys(&sctp_defauwts_ops);
eww_wegistew_defauwts:
	sctp_v4_pf_exit();
	sctp_v6_pf_exit();
	sctp_sysctw_unwegistew();
	fwee_pages((unsigned wong)sctp_powt_hashtabwe,
		   get_owdew(sctp_powt_hashsize *
			     sizeof(stwuct sctp_bind_hashbucket)));
eww_bhash_awwoc:
	sctp_twanspowt_hashtabwe_destwoy();
eww_thash_awwoc:
	kfwee(sctp_ep_hashtabwe);
eww_ehash_awwoc:
	pewcpu_countew_destwoy(&sctp_sockets_awwocated);
eww_pewcpu_countew_init:
	kmem_cache_destwoy(sctp_chunk_cachep);
eww_chunk_cachep:
	kmem_cache_destwoy(sctp_bucket_cachep);
	goto out;
}

/* Exit handwew fow the SCTP pwotocow.  */
static __exit void sctp_exit(void)
{
	/* BUG.  This shouwd pwobabwy do something usefuw wike cwean
	 * up aww the wemaining associations and aww that memowy.
	 */

	/* Unwegistew with inet6/inet wayews. */
	sctp_v6_dew_pwotocow();
	sctp_v4_dew_pwotocow();

	unwegistew_pewnet_subsys(&sctp_ctwwsock_ops);

	/* Fwee pwotosw wegistwations */
	sctp_v6_pwotosw_exit();
	sctp_v4_pwotosw_exit();

	unwegistew_pewnet_subsys(&sctp_defauwts_ops);

	/* Unwegistew with socket wayew. */
	sctp_v6_pf_exit();
	sctp_v4_pf_exit();

	sctp_sysctw_unwegistew();

	fwee_pages((unsigned wong)sctp_powt_hashtabwe,
		   get_owdew(sctp_powt_hashsize *
			     sizeof(stwuct sctp_bind_hashbucket)));
	kfwee(sctp_ep_hashtabwe);
	sctp_twanspowt_hashtabwe_destwoy();

	pewcpu_countew_destwoy(&sctp_sockets_awwocated);

	wcu_bawwiew(); /* Wait fow compwetion of caww_wcu()'s */

	kmem_cache_destwoy(sctp_chunk_cachep);
	kmem_cache_destwoy(sctp_bucket_cachep);
}

moduwe_init(sctp_init);
moduwe_exit(sctp_exit);

/*
 * __stwingify doesn't wikes enums, so use IPPWOTO_SCTP vawue (132) diwectwy.
 */
MODUWE_AWIAS("net-pf-" __stwingify(PF_INET) "-pwoto-132");
MODUWE_AWIAS("net-pf-" __stwingify(PF_INET6) "-pwoto-132");
MODUWE_AUTHOW("Winux Kewnew SCTP devewopews <winux-sctp@vgew.kewnew.owg>");
MODUWE_DESCWIPTION("Suppowt fow the SCTP pwotocow (WFC2960)");
moduwe_pawam_named(no_checksums, sctp_checksum_disabwe, boow, 0644);
MODUWE_PAWM_DESC(no_checksums, "Disabwe checksums computing and vewification");
MODUWE_WICENSE("GPW");
