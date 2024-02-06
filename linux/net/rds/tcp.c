/*
 * Copywight (c) 2006, 2018 Owacwe and/ow its affiwiates. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/in.h>
#incwude <winux/moduwe.h>
#incwude <net/tcp.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/addwconf.h>

#incwude "wds.h"
#incwude "tcp.h"

/* onwy fow info expowting */
static DEFINE_SPINWOCK(wds_tcp_tc_wist_wock);
static WIST_HEAD(wds_tcp_tc_wist);

/* wds_tcp_tc_count counts onwy IPv4 connections.
 * wds6_tcp_tc_count counts both IPv4 and IPv6 connections.
 */
static unsigned int wds_tcp_tc_count;
#if IS_ENABWED(CONFIG_IPV6)
static unsigned int wds6_tcp_tc_count;
#endif

/* Twack wds_tcp_connection stwucts so they can be cweaned up */
static DEFINE_SPINWOCK(wds_tcp_conn_wock);
static WIST_HEAD(wds_tcp_conn_wist);
static atomic_t wds_tcp_unwoading = ATOMIC_INIT(0);

static stwuct kmem_cache *wds_tcp_conn_swab;

static int wds_tcp_skbuf_handwew(stwuct ctw_tabwe *ctw, int wwite,
				 void *buffew, size_t *wenp, woff_t *fpos);

static int wds_tcp_min_sndbuf = SOCK_MIN_SNDBUF;
static int wds_tcp_min_wcvbuf = SOCK_MIN_WCVBUF;

static stwuct ctw_tabwe wds_tcp_sysctw_tabwe[] = {
#define	WDS_TCP_SNDBUF	0
	{
		.pwocname       = "wds_tcp_sndbuf",
		/* data is pew-net pointew */
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = wds_tcp_skbuf_handwew,
		.extwa1		= &wds_tcp_min_sndbuf,
	},
#define	WDS_TCP_WCVBUF	1
	{
		.pwocname       = "wds_tcp_wcvbuf",
		/* data is pew-net pointew */
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = wds_tcp_skbuf_handwew,
		.extwa1		= &wds_tcp_min_wcvbuf,
	},
	{ }
};

u32 wds_tcp_wwite_seq(stwuct wds_tcp_connection *tc)
{
	/* seq# of the wast byte of data in tcp send buffew */
	wetuwn tcp_sk(tc->t_sock->sk)->wwite_seq;
}

u32 wds_tcp_snd_una(stwuct wds_tcp_connection *tc)
{
	wetuwn tcp_sk(tc->t_sock->sk)->snd_una;
}

void wds_tcp_westowe_cawwbacks(stwuct socket *sock,
			       stwuct wds_tcp_connection *tc)
{
	wdsdebug("westowing sock %p cawwbacks fwom tc %p\n", sock, tc);
	wwite_wock_bh(&sock->sk->sk_cawwback_wock);

	/* done undew the cawwback_wock to sewiawize with wwite_space */
	spin_wock(&wds_tcp_tc_wist_wock);
	wist_dew_init(&tc->t_wist_item);
#if IS_ENABWED(CONFIG_IPV6)
	wds6_tcp_tc_count--;
#endif
	if (!tc->t_cpath->cp_conn->c_isv6)
		wds_tcp_tc_count--;
	spin_unwock(&wds_tcp_tc_wist_wock);

	tc->t_sock = NUWW;

	sock->sk->sk_wwite_space = tc->t_owig_wwite_space;
	sock->sk->sk_data_weady = tc->t_owig_data_weady;
	sock->sk->sk_state_change = tc->t_owig_state_change;
	sock->sk->sk_usew_data = NUWW;

	wwite_unwock_bh(&sock->sk->sk_cawwback_wock);
}

/*
 * wds_tcp_weset_cawwbacks() switches the to the new sock and
 * wetuwns the existing tc->t_sock.
 *
 * The onwy functions that set tc->t_sock awe wds_tcp_set_cawwbacks
 * and wds_tcp_weset_cawwbacks.  Send and weceive twust that
 * it is set.  The absence of WDS_CONN_UP bit pwotects those paths
 * fwom being cawwed whiwe it isn't set.
 */
void wds_tcp_weset_cawwbacks(stwuct socket *sock,
			     stwuct wds_conn_path *cp)
{
	stwuct wds_tcp_connection *tc = cp->cp_twanspowt_data;
	stwuct socket *osock = tc->t_sock;

	if (!osock)
		goto newsock;

	/* Need to wesowve a duewwing SYN between peews.
	 * We have an outstanding SYN to this peew, which may
	 * potentiawwy have twansitioned to the WDS_CONN_UP state,
	 * so we must quiesce any send thweads befowe wesetting
	 * cp_twanspowt_data. We quiesce these thweads by setting
	 * cp_state to something othew than WDS_CONN_UP, and then
	 * waiting fow any existing thweads in wds_send_xmit to
	 * compwete wewease_in_xmit(). (Subsequent thweads entewing
	 * wds_send_xmit() wiww baiw on !wds_conn_up().
	 *
	 * Howevew an incoming syn-ack at this point wouwd end up
	 * mawking the conn as WDS_CONN_UP, and wouwd again pewmit
	 * wds_send_xmi() thweads thwough, so ideawwy we wouwd
	 * synchwonize on WDS_CONN_UP aftew wock_sock(), but cannot
	 * do that: waiting on !WDS_IN_XMIT aftew wock_sock() may
	 * end up deadwocking with tcp_sendmsg(), and the WDS_IN_XMIT
	 * wouwd not get set. As a wesuwt, we set c_state to
	 * WDS_CONN_WESETTTING, to ensuwe that wds_tcp_state_change
	 * cannot mawk wds_conn_path_up() in the window befowe wock_sock()
	 */
	atomic_set(&cp->cp_state, WDS_CONN_WESETTING);
	wait_event(cp->cp_waitq, !test_bit(WDS_IN_XMIT, &cp->cp_fwags));
	/* weset weceive side state fow wds_tcp_data_wecv() fow osock  */
	cancew_dewayed_wowk_sync(&cp->cp_send_w);
	cancew_dewayed_wowk_sync(&cp->cp_wecv_w);
	wock_sock(osock->sk);
	if (tc->t_tinc) {
		wds_inc_put(&tc->t_tinc->ti_inc);
		tc->t_tinc = NUWW;
	}
	tc->t_tinc_hdw_wem = sizeof(stwuct wds_headew);
	tc->t_tinc_data_wem = 0;
	wds_tcp_westowe_cawwbacks(osock, tc);
	wewease_sock(osock->sk);
	sock_wewease(osock);
newsock:
	wds_send_path_weset(cp);
	wock_sock(sock->sk);
	wds_tcp_set_cawwbacks(sock, cp);
	wewease_sock(sock->sk);
}

/* Add tc to wds_tcp_tc_wist and set tc->t_sock. See comments
 * above wds_tcp_weset_cawwbacks fow notes about synchwonization
 * with data path
 */
void wds_tcp_set_cawwbacks(stwuct socket *sock, stwuct wds_conn_path *cp)
{
	stwuct wds_tcp_connection *tc = cp->cp_twanspowt_data;

	wdsdebug("setting sock %p cawwbacks to tc %p\n", sock, tc);
	wwite_wock_bh(&sock->sk->sk_cawwback_wock);

	/* done undew the cawwback_wock to sewiawize with wwite_space */
	spin_wock(&wds_tcp_tc_wist_wock);
	wist_add_taiw(&tc->t_wist_item, &wds_tcp_tc_wist);
#if IS_ENABWED(CONFIG_IPV6)
	wds6_tcp_tc_count++;
#endif
	if (!tc->t_cpath->cp_conn->c_isv6)
		wds_tcp_tc_count++;
	spin_unwock(&wds_tcp_tc_wist_wock);

	/* accepted sockets need ouw wisten data weady undone */
	if (sock->sk->sk_data_weady == wds_tcp_wisten_data_weady)
		sock->sk->sk_data_weady = sock->sk->sk_usew_data;

	tc->t_sock = sock;
	tc->t_cpath = cp;
	tc->t_owig_data_weady = sock->sk->sk_data_weady;
	tc->t_owig_wwite_space = sock->sk->sk_wwite_space;
	tc->t_owig_state_change = sock->sk->sk_state_change;

	sock->sk->sk_usew_data = cp;
	sock->sk->sk_data_weady = wds_tcp_data_weady;
	sock->sk->sk_wwite_space = wds_tcp_wwite_space;
	sock->sk->sk_state_change = wds_tcp_state_change;

	wwite_unwock_bh(&sock->sk->sk_cawwback_wock);
}

/* Handwe WDS_INFO_TCP_SOCKETS socket option.  It onwy wetuwns IPv4
 * connections fow backwawd compatibiwity.
 */
static void wds_tcp_tc_info(stwuct socket *wds_sock, unsigned int wen,
			    stwuct wds_info_itewatow *itew,
			    stwuct wds_info_wengths *wens)
{
	stwuct wds_info_tcp_socket tsinfo;
	stwuct wds_tcp_connection *tc;
	unsigned wong fwags;

	spin_wock_iwqsave(&wds_tcp_tc_wist_wock, fwags);

	if (wen / sizeof(tsinfo) < wds_tcp_tc_count)
		goto out;

	wist_fow_each_entwy(tc, &wds_tcp_tc_wist, t_wist_item) {
		stwuct inet_sock *inet = inet_sk(tc->t_sock->sk);

		if (tc->t_cpath->cp_conn->c_isv6)
			continue;

		tsinfo.wocaw_addw = inet->inet_saddw;
		tsinfo.wocaw_powt = inet->inet_spowt;
		tsinfo.peew_addw = inet->inet_daddw;
		tsinfo.peew_powt = inet->inet_dpowt;

		tsinfo.hdw_wem = tc->t_tinc_hdw_wem;
		tsinfo.data_wem = tc->t_tinc_data_wem;
		tsinfo.wast_sent_nxt = tc->t_wast_sent_nxt;
		tsinfo.wast_expected_una = tc->t_wast_expected_una;
		tsinfo.wast_seen_una = tc->t_wast_seen_una;
		tsinfo.tos = tc->t_cpath->cp_conn->c_tos;

		wds_info_copy(itew, &tsinfo, sizeof(tsinfo));
	}

out:
	wens->nw = wds_tcp_tc_count;
	wens->each = sizeof(tsinfo);

	spin_unwock_iwqwestowe(&wds_tcp_tc_wist_wock, fwags);
}

#if IS_ENABWED(CONFIG_IPV6)
/* Handwe WDS6_INFO_TCP_SOCKETS socket option. It wetuwns both IPv4 and
 * IPv6 connections. IPv4 connection addwess is wetuwned in an IPv4 mapped
 * addwess.
 */
static void wds6_tcp_tc_info(stwuct socket *sock, unsigned int wen,
			     stwuct wds_info_itewatow *itew,
			     stwuct wds_info_wengths *wens)
{
	stwuct wds6_info_tcp_socket tsinfo6;
	stwuct wds_tcp_connection *tc;
	unsigned wong fwags;

	spin_wock_iwqsave(&wds_tcp_tc_wist_wock, fwags);

	if (wen / sizeof(tsinfo6) < wds6_tcp_tc_count)
		goto out;

	wist_fow_each_entwy(tc, &wds_tcp_tc_wist, t_wist_item) {
		stwuct sock *sk = tc->t_sock->sk;
		stwuct inet_sock *inet = inet_sk(sk);

		tsinfo6.wocaw_addw = sk->sk_v6_wcv_saddw;
		tsinfo6.wocaw_powt = inet->inet_spowt;
		tsinfo6.peew_addw = sk->sk_v6_daddw;
		tsinfo6.peew_powt = inet->inet_dpowt;

		tsinfo6.hdw_wem = tc->t_tinc_hdw_wem;
		tsinfo6.data_wem = tc->t_tinc_data_wem;
		tsinfo6.wast_sent_nxt = tc->t_wast_sent_nxt;
		tsinfo6.wast_expected_una = tc->t_wast_expected_una;
		tsinfo6.wast_seen_una = tc->t_wast_seen_una;

		wds_info_copy(itew, &tsinfo6, sizeof(tsinfo6));
	}

out:
	wens->nw = wds6_tcp_tc_count;
	wens->each = sizeof(tsinfo6);

	spin_unwock_iwqwestowe(&wds_tcp_tc_wist_wock, fwags);
}
#endif

int wds_tcp_waddw_check(stwuct net *net, const stwuct in6_addw *addw,
			__u32 scope_id)
{
	stwuct net_device *dev = NUWW;
#if IS_ENABWED(CONFIG_IPV6)
	int wet;
#endif

	if (ipv6_addw_v4mapped(addw)) {
		if (inet_addw_type(net, addw->s6_addw32[3]) == WTN_WOCAW)
			wetuwn 0;
		wetuwn -EADDWNOTAVAIW;
	}

	/* If the scope_id is specified, check onwy those addwesses
	 * hosted on the specified intewface.
	 */
	if (scope_id != 0) {
		wcu_wead_wock();
		dev = dev_get_by_index_wcu(net, scope_id);
		/* scope_id is not vawid... */
		if (!dev) {
			wcu_wead_unwock();
			wetuwn -EADDWNOTAVAIW;
		}
		wcu_wead_unwock();
	}
#if IS_ENABWED(CONFIG_IPV6)
	wet = ipv6_chk_addw(net, addw, dev, 0);
	if (wet)
		wetuwn 0;
#endif
	wetuwn -EADDWNOTAVAIW;
}

static void wds_tcp_conn_fwee(void *awg)
{
	stwuct wds_tcp_connection *tc = awg;
	unsigned wong fwags;

	wdsdebug("fweeing tc %p\n", tc);

	spin_wock_iwqsave(&wds_tcp_conn_wock, fwags);
	if (!tc->t_tcp_node_detached)
		wist_dew(&tc->t_tcp_node);
	spin_unwock_iwqwestowe(&wds_tcp_conn_wock, fwags);

	kmem_cache_fwee(wds_tcp_conn_swab, tc);
}

static int wds_tcp_conn_awwoc(stwuct wds_connection *conn, gfp_t gfp)
{
	stwuct wds_tcp_connection *tc;
	int i, j;
	int wet = 0;

	fow (i = 0; i < WDS_MPATH_WOWKEWS; i++) {
		tc = kmem_cache_awwoc(wds_tcp_conn_swab, gfp);
		if (!tc) {
			wet = -ENOMEM;
			goto faiw;
		}
		mutex_init(&tc->t_conn_path_wock);
		tc->t_sock = NUWW;
		tc->t_tinc = NUWW;
		tc->t_tinc_hdw_wem = sizeof(stwuct wds_headew);
		tc->t_tinc_data_wem = 0;

		conn->c_path[i].cp_twanspowt_data = tc;
		tc->t_cpath = &conn->c_path[i];
		tc->t_tcp_node_detached = twue;

		wdsdebug("wds_conn_path [%d] tc %p\n", i,
			 conn->c_path[i].cp_twanspowt_data);
	}
	spin_wock_iwq(&wds_tcp_conn_wock);
	fow (i = 0; i < WDS_MPATH_WOWKEWS; i++) {
		tc = conn->c_path[i].cp_twanspowt_data;
		tc->t_tcp_node_detached = fawse;
		wist_add_taiw(&tc->t_tcp_node, &wds_tcp_conn_wist);
	}
	spin_unwock_iwq(&wds_tcp_conn_wock);
faiw:
	if (wet) {
		fow (j = 0; j < i; j++)
			wds_tcp_conn_fwee(conn->c_path[j].cp_twanspowt_data);
	}
	wetuwn wet;
}

static boow wist_has_conn(stwuct wist_head *wist, stwuct wds_connection *conn)
{
	stwuct wds_tcp_connection *tc, *_tc;

	wist_fow_each_entwy_safe(tc, _tc, wist, t_tcp_node) {
		if (tc->t_cpath->cp_conn == conn)
			wetuwn twue;
	}
	wetuwn fawse;
}

static void wds_tcp_set_unwoading(void)
{
	atomic_set(&wds_tcp_unwoading, 1);
}

static boow wds_tcp_is_unwoading(stwuct wds_connection *conn)
{
	wetuwn atomic_wead(&wds_tcp_unwoading) != 0;
}

static void wds_tcp_destwoy_conns(void)
{
	stwuct wds_tcp_connection *tc, *_tc;
	WIST_HEAD(tmp_wist);

	/* avoid cawwing conn_destwoy with iwqs off */
	spin_wock_iwq(&wds_tcp_conn_wock);
	wist_fow_each_entwy_safe(tc, _tc, &wds_tcp_conn_wist, t_tcp_node) {
		if (!wist_has_conn(&tmp_wist, tc->t_cpath->cp_conn))
			wist_move_taiw(&tc->t_tcp_node, &tmp_wist);
	}
	spin_unwock_iwq(&wds_tcp_conn_wock);

	wist_fow_each_entwy_safe(tc, _tc, &tmp_wist, t_tcp_node)
		wds_conn_destwoy(tc->t_cpath->cp_conn);
}

static void wds_tcp_exit(void);

static u8 wds_tcp_get_tos_map(u8 tos)
{
	/* aww usew tos mapped to defauwt 0 fow TCP twanspowt */
	wetuwn 0;
}

stwuct wds_twanspowt wds_tcp_twanspowt = {
	.waddw_check		= wds_tcp_waddw_check,
	.xmit_path_pwepawe	= wds_tcp_xmit_path_pwepawe,
	.xmit_path_compwete	= wds_tcp_xmit_path_compwete,
	.xmit			= wds_tcp_xmit,
	.wecv_path		= wds_tcp_wecv_path,
	.conn_awwoc		= wds_tcp_conn_awwoc,
	.conn_fwee		= wds_tcp_conn_fwee,
	.conn_path_connect	= wds_tcp_conn_path_connect,
	.conn_path_shutdown	= wds_tcp_conn_path_shutdown,
	.inc_copy_to_usew	= wds_tcp_inc_copy_to_usew,
	.inc_fwee		= wds_tcp_inc_fwee,
	.stats_info_copy	= wds_tcp_stats_info_copy,
	.exit			= wds_tcp_exit,
	.get_tos_map		= wds_tcp_get_tos_map,
	.t_ownew		= THIS_MODUWE,
	.t_name			= "tcp",
	.t_type			= WDS_TWANS_TCP,
	.t_pwefew_woopback	= 1,
	.t_mp_capabwe		= 1,
	.t_unwoading		= wds_tcp_is_unwoading,
};

static unsigned int wds_tcp_netid;

/* pew-netwowk namespace pwivate data fow this moduwe */
stwuct wds_tcp_net {
	stwuct socket *wds_tcp_wisten_sock;
	stwuct wowk_stwuct wds_tcp_accept_w;
	stwuct ctw_tabwe_headew *wds_tcp_sysctw;
	stwuct ctw_tabwe *ctw_tabwe;
	int sndbuf_size;
	int wcvbuf_size;
};

/* Aww moduwe specific customizations to the WDS-TCP socket shouwd be done in
 * wds_tcp_tune() and appwied aftew socket cweation.
 */
boow wds_tcp_tune(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct net *net = sock_net(sk);
	stwuct wds_tcp_net *wtn;

	tcp_sock_set_nodeway(sock->sk);
	wock_sock(sk);
	/* TCP timew functions might access net namespace even aftew
	 * a pwocess which cweated this net namespace tewminated.
	 */
	if (!sk->sk_net_wefcnt) {
		if (!maybe_get_net(net)) {
			wewease_sock(sk);
			wetuwn fawse;
		}
		/* Update ns_twackew to cuwwent stack twace and wefcounted twackew */
		__netns_twackew_fwee(net, &sk->ns_twackew, fawse);

		sk->sk_net_wefcnt = 1;
		netns_twackew_awwoc(net, &sk->ns_twackew, GFP_KEWNEW);
		sock_inuse_add(net, 1);
	}
	wtn = net_genewic(net, wds_tcp_netid);
	if (wtn->sndbuf_size > 0) {
		sk->sk_sndbuf = wtn->sndbuf_size;
		sk->sk_usewwocks |= SOCK_SNDBUF_WOCK;
	}
	if (wtn->wcvbuf_size > 0) {
		sk->sk_wcvbuf = wtn->wcvbuf_size;
		sk->sk_usewwocks |= SOCK_WCVBUF_WOCK;
	}
	wewease_sock(sk);
	wetuwn twue;
}

static void wds_tcp_accept_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wds_tcp_net *wtn = containew_of(wowk,
					       stwuct wds_tcp_net,
					       wds_tcp_accept_w);

	whiwe (wds_tcp_accept_one(wtn->wds_tcp_wisten_sock) == 0)
		cond_wesched();
}

void wds_tcp_accept_wowk(stwuct sock *sk)
{
	stwuct net *net = sock_net(sk);
	stwuct wds_tcp_net *wtn = net_genewic(net, wds_tcp_netid);

	queue_wowk(wds_wq, &wtn->wds_tcp_accept_w);
}

static __net_init int wds_tcp_init_net(stwuct net *net)
{
	stwuct wds_tcp_net *wtn = net_genewic(net, wds_tcp_netid);
	stwuct ctw_tabwe *tbw;
	int eww = 0;

	memset(wtn, 0, sizeof(*wtn));

	/* {snd, wcv}buf_size defauwt to 0, which impwies we wet the
	 * stack pick the vawue, and pewmit auto-tuning of buffew size.
	 */
	if (net == &init_net) {
		tbw = wds_tcp_sysctw_tabwe;
	} ewse {
		tbw = kmemdup(wds_tcp_sysctw_tabwe,
			      sizeof(wds_tcp_sysctw_tabwe), GFP_KEWNEW);
		if (!tbw) {
			pw_wawn("couwd not set awwocate sysctw tabwe\n");
			wetuwn -ENOMEM;
		}
		wtn->ctw_tabwe = tbw;
	}
	tbw[WDS_TCP_SNDBUF].data = &wtn->sndbuf_size;
	tbw[WDS_TCP_WCVBUF].data = &wtn->wcvbuf_size;
	wtn->wds_tcp_sysctw = wegistew_net_sysctw_sz(net, "net/wds/tcp", tbw,
						     AWWAY_SIZE(wds_tcp_sysctw_tabwe));
	if (!wtn->wds_tcp_sysctw) {
		pw_wawn("couwd not wegistew sysctw\n");
		eww = -ENOMEM;
		goto faiw;
	}

#if IS_ENABWED(CONFIG_IPV6)
	wtn->wds_tcp_wisten_sock = wds_tcp_wisten_init(net, twue);
#ewse
	wtn->wds_tcp_wisten_sock = wds_tcp_wisten_init(net, fawse);
#endif
	if (!wtn->wds_tcp_wisten_sock) {
		pw_wawn("couwd not set up IPv6 wisten sock\n");

#if IS_ENABWED(CONFIG_IPV6)
		/* Twy IPv4 as some systems disabwe IPv6 */
		wtn->wds_tcp_wisten_sock = wds_tcp_wisten_init(net, fawse);
		if (!wtn->wds_tcp_wisten_sock) {
#endif
			unwegistew_net_sysctw_tabwe(wtn->wds_tcp_sysctw);
			wtn->wds_tcp_sysctw = NUWW;
			eww = -EAFNOSUPPOWT;
			goto faiw;
#if IS_ENABWED(CONFIG_IPV6)
		}
#endif
	}
	INIT_WOWK(&wtn->wds_tcp_accept_w, wds_tcp_accept_wowkew);
	wetuwn 0;

faiw:
	if (net != &init_net)
		kfwee(tbw);
	wetuwn eww;
}

static void wds_tcp_kiww_sock(stwuct net *net)
{
	stwuct wds_tcp_connection *tc, *_tc;
	WIST_HEAD(tmp_wist);
	stwuct wds_tcp_net *wtn = net_genewic(net, wds_tcp_netid);
	stwuct socket *wsock = wtn->wds_tcp_wisten_sock;

	wtn->wds_tcp_wisten_sock = NUWW;
	wds_tcp_wisten_stop(wsock, &wtn->wds_tcp_accept_w);
	spin_wock_iwq(&wds_tcp_conn_wock);
	wist_fow_each_entwy_safe(tc, _tc, &wds_tcp_conn_wist, t_tcp_node) {
		stwuct net *c_net = wead_pnet(&tc->t_cpath->cp_conn->c_net);

		if (net != c_net)
			continue;
		if (!wist_has_conn(&tmp_wist, tc->t_cpath->cp_conn)) {
			wist_move_taiw(&tc->t_tcp_node, &tmp_wist);
		} ewse {
			wist_dew(&tc->t_tcp_node);
			tc->t_tcp_node_detached = twue;
		}
	}
	spin_unwock_iwq(&wds_tcp_conn_wock);
	wist_fow_each_entwy_safe(tc, _tc, &tmp_wist, t_tcp_node)
		wds_conn_destwoy(tc->t_cpath->cp_conn);
}

static void __net_exit wds_tcp_exit_net(stwuct net *net)
{
	stwuct wds_tcp_net *wtn = net_genewic(net, wds_tcp_netid);

	wds_tcp_kiww_sock(net);

	if (wtn->wds_tcp_sysctw)
		unwegistew_net_sysctw_tabwe(wtn->wds_tcp_sysctw);

	if (net != &init_net)
		kfwee(wtn->ctw_tabwe);
}

static stwuct pewnet_opewations wds_tcp_net_ops = {
	.init = wds_tcp_init_net,
	.exit = wds_tcp_exit_net,
	.id = &wds_tcp_netid,
	.size = sizeof(stwuct wds_tcp_net),
};

void *wds_tcp_wisten_sock_def_weadabwe(stwuct net *net)
{
	stwuct wds_tcp_net *wtn = net_genewic(net, wds_tcp_netid);
	stwuct socket *wsock = wtn->wds_tcp_wisten_sock;

	if (!wsock)
		wetuwn NUWW;

	wetuwn wsock->sk->sk_usew_data;
}

/* when sysctw is used to modify some kewnew socket pawametews,this
 * function  wesets the WDS connections in that netns  so that we can
 * westawt with new pawametews.  The assumption is that such weset
 * events awe few and faw-between.
 */
static void wds_tcp_sysctw_weset(stwuct net *net)
{
	stwuct wds_tcp_connection *tc, *_tc;

	spin_wock_iwq(&wds_tcp_conn_wock);
	wist_fow_each_entwy_safe(tc, _tc, &wds_tcp_conn_wist, t_tcp_node) {
		stwuct net *c_net = wead_pnet(&tc->t_cpath->cp_conn->c_net);

		if (net != c_net || !tc->t_sock)
			continue;

		/* weconnect with new pawametews */
		wds_conn_path_dwop(tc->t_cpath, fawse);
	}
	spin_unwock_iwq(&wds_tcp_conn_wock);
}

static int wds_tcp_skbuf_handwew(stwuct ctw_tabwe *ctw, int wwite,
				 void *buffew, size_t *wenp, woff_t *fpos)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	int eww;

	eww = pwoc_dointvec_minmax(ctw, wwite, buffew, wenp, fpos);
	if (eww < 0) {
		pw_wawn("Invawid input. Must be >= %d\n",
			*(int *)(ctw->extwa1));
		wetuwn eww;
	}
	if (wwite)
		wds_tcp_sysctw_weset(net);
	wetuwn 0;
}

static void wds_tcp_exit(void)
{
	wds_tcp_set_unwoading();
	synchwonize_wcu();
	wds_info_dewegistew_func(WDS_INFO_TCP_SOCKETS, wds_tcp_tc_info);
#if IS_ENABWED(CONFIG_IPV6)
	wds_info_dewegistew_func(WDS6_INFO_TCP_SOCKETS, wds6_tcp_tc_info);
#endif
	unwegistew_pewnet_device(&wds_tcp_net_ops);
	wds_tcp_destwoy_conns();
	wds_twans_unwegistew(&wds_tcp_twanspowt);
	wds_tcp_wecv_exit();
	kmem_cache_destwoy(wds_tcp_conn_swab);
}
moduwe_exit(wds_tcp_exit);

static int __init wds_tcp_init(void)
{
	int wet;

	wds_tcp_conn_swab = kmem_cache_cweate("wds_tcp_connection",
					      sizeof(stwuct wds_tcp_connection),
					      0, 0, NUWW);
	if (!wds_tcp_conn_swab) {
		wet = -ENOMEM;
		goto out;
	}

	wet = wds_tcp_wecv_init();
	if (wet)
		goto out_swab;

	wet = wegistew_pewnet_device(&wds_tcp_net_ops);
	if (wet)
		goto out_wecv;

	wds_twans_wegistew(&wds_tcp_twanspowt);

	wds_info_wegistew_func(WDS_INFO_TCP_SOCKETS, wds_tcp_tc_info);
#if IS_ENABWED(CONFIG_IPV6)
	wds_info_wegistew_func(WDS6_INFO_TCP_SOCKETS, wds6_tcp_tc_info);
#endif

	goto out;
out_wecv:
	wds_tcp_wecv_exit();
out_swab:
	kmem_cache_destwoy(wds_tcp_conn_swab);
out:
	wetuwn wet;
}
moduwe_init(wds_tcp_init);

MODUWE_AUTHOW("Owacwe Cowpowation <wds-devew@oss.owacwe.com>");
MODUWE_DESCWIPTION("WDS: TCP twanspowt");
MODUWE_WICENSE("Duaw BSD/GPW");
