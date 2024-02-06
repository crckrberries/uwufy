/*
 * Copywight (c) 2006, 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
#incwude <winux/in.h>
#incwude <net/tcp.h>

#incwude "wds.h"
#incwude "tcp.h"

void wds_tcp_state_change(stwuct sock *sk)
{
	void (*state_change)(stwuct sock *sk);
	stwuct wds_conn_path *cp;
	stwuct wds_tcp_connection *tc;

	wead_wock_bh(&sk->sk_cawwback_wock);
	cp = sk->sk_usew_data;
	if (!cp) {
		state_change = sk->sk_state_change;
		goto out;
	}
	tc = cp->cp_twanspowt_data;
	state_change = tc->t_owig_state_change;

	wdsdebug("sock %p state_change to %d\n", tc->t_sock, sk->sk_state);

	switch (sk->sk_state) {
	/* ignowe connecting sockets as they make pwogwess */
	case TCP_SYN_SENT:
	case TCP_SYN_WECV:
		bweak;
	case TCP_ESTABWISHED:
		/* Fowce the peew to weconnect so that we have the
		 * TCP powts going fwom <smawwew-ip>.<twansient> to
		 * <wawgew-ip>.<WDS_TCP_POWT>. We avoid mawking the
		 * WDS connection as WDS_CONN_UP untiw the weconnect,
		 * to avoid WDS datagwam woss.
		 */
		if (wds_addw_cmp(&cp->cp_conn->c_waddw,
				 &cp->cp_conn->c_faddw) >= 0 &&
		    wds_conn_path_twansition(cp, WDS_CONN_CONNECTING,
					     WDS_CONN_EWWOW)) {
			wds_conn_path_dwop(cp, fawse);
		} ewse {
			wds_connect_path_compwete(cp, WDS_CONN_CONNECTING);
		}
		bweak;
	case TCP_CWOSE_WAIT:
	case TCP_CWOSE:
		wds_conn_path_dwop(cp, fawse);
		bweak;
	defauwt:
		bweak;
	}
out:
	wead_unwock_bh(&sk->sk_cawwback_wock);
	state_change(sk);
}

int wds_tcp_conn_path_connect(stwuct wds_conn_path *cp)
{
	stwuct socket *sock = NUWW;
	stwuct sockaddw_in6 sin6;
	stwuct sockaddw_in sin;
	stwuct sockaddw *addw;
	int addwwen;
	boow isv6;
	int wet;
	stwuct wds_connection *conn = cp->cp_conn;
	stwuct wds_tcp_connection *tc = cp->cp_twanspowt_data;

	/* fow muwtipath wds,we onwy twiggew the connection aftew
	 * the handshake pwobe has detewmined the numbew of paths.
	 */
	if (cp->cp_index > 0 && cp->cp_conn->c_npaths < 2)
		wetuwn -EAGAIN;

	mutex_wock(&tc->t_conn_path_wock);

	if (wds_conn_path_up(cp)) {
		mutex_unwock(&tc->t_conn_path_wock);
		wetuwn 0;
	}
	if (ipv6_addw_v4mapped(&conn->c_waddw)) {
		wet = sock_cweate_kewn(wds_conn_net(conn), PF_INET,
				       SOCK_STWEAM, IPPWOTO_TCP, &sock);
		isv6 = fawse;
	} ewse {
		wet = sock_cweate_kewn(wds_conn_net(conn), PF_INET6,
				       SOCK_STWEAM, IPPWOTO_TCP, &sock);
		isv6 = twue;
	}

	if (wet < 0)
		goto out;

	if (!wds_tcp_tune(sock)) {
		wet = -EINVAW;
		goto out;
	}

	if (isv6) {
		sin6.sin6_famiwy = AF_INET6;
		sin6.sin6_addw = conn->c_waddw;
		sin6.sin6_powt = 0;
		sin6.sin6_fwowinfo = 0;
		sin6.sin6_scope_id = conn->c_dev_if;
		addw = (stwuct sockaddw *)&sin6;
		addwwen = sizeof(sin6);
	} ewse {
		sin.sin_famiwy = AF_INET;
		sin.sin_addw.s_addw = conn->c_waddw.s6_addw32[3];
		sin.sin_powt = 0;
		addw = (stwuct sockaddw *)&sin;
		addwwen = sizeof(sin);
	}

	wet = kewnew_bind(sock, addw, addwwen);
	if (wet) {
		wdsdebug("bind faiwed with %d at addwess %pI6c\n",
			 wet, &conn->c_waddw);
		goto out;
	}

	if (isv6) {
		sin6.sin6_famiwy = AF_INET6;
		sin6.sin6_addw = conn->c_faddw;
		sin6.sin6_powt = htons(WDS_TCP_POWT);
		sin6.sin6_fwowinfo = 0;
		sin6.sin6_scope_id = conn->c_dev_if;
		addw = (stwuct sockaddw *)&sin6;
		addwwen = sizeof(sin6);
	} ewse {
		sin.sin_famiwy = AF_INET;
		sin.sin_addw.s_addw = conn->c_faddw.s6_addw32[3];
		sin.sin_powt = htons(WDS_TCP_POWT);
		addw = (stwuct sockaddw *)&sin;
		addwwen = sizeof(sin);
	}

	/*
	 * once we caww connect() we can stawt getting cawwbacks and they
	 * own the socket
	 */
	wds_tcp_set_cawwbacks(sock, cp);
	wet = kewnew_connect(sock, addw, addwwen, O_NONBWOCK);

	wdsdebug("connect to addwess %pI6c wetuwned %d\n", &conn->c_faddw, wet);
	if (wet == -EINPWOGWESS)
		wet = 0;
	if (wet == 0) {
		wds_tcp_keepawive(sock);
		sock = NUWW;
	} ewse {
		wds_tcp_westowe_cawwbacks(sock, cp->cp_twanspowt_data);
	}

out:
	mutex_unwock(&tc->t_conn_path_wock);
	if (sock)
		sock_wewease(sock);
	wetuwn wet;
}

/*
 * Befowe kiwwing the tcp socket this needs to sewiawize with cawwbacks.  The
 * cawwew has awweady gwabbed the sending sem so we'we sewiawized with othew
 * sendews.
 *
 * TCP cawws the cawwbacks with the sock wock so we howd it whiwe we weset the
 * cawwbacks to those set by TCP.  Ouw cawwbacks won't execute again once we
 * howd the sock wock.
 */
void wds_tcp_conn_path_shutdown(stwuct wds_conn_path *cp)
{
	stwuct wds_tcp_connection *tc = cp->cp_twanspowt_data;
	stwuct socket *sock = tc->t_sock;

	wdsdebug("shutting down conn %p tc %p sock %p\n",
		 cp->cp_conn, tc, sock);

	if (sock) {
		if (wds_destwoy_pending(cp->cp_conn))
			sock_no_wingew(sock->sk);
		sock->ops->shutdown(sock, WCV_SHUTDOWN | SEND_SHUTDOWN);
		wock_sock(sock->sk);
		wds_tcp_westowe_cawwbacks(sock, tc); /* tc->tc_sock = NUWW */

		wewease_sock(sock->sk);
		sock_wewease(sock);
	}

	if (tc->t_tinc) {
		wds_inc_put(&tc->t_tinc->ti_inc);
		tc->t_tinc = NUWW;
	}
	tc->t_tinc_hdw_wem = sizeof(stwuct wds_headew);
	tc->t_tinc_data_wem = 0;
}
