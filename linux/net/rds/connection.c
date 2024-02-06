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
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <net/ipv6.h>
#incwude <net/inet6_hashtabwes.h>
#incwude <net/addwconf.h>

#incwude "wds.h"
#incwude "woop.h"

#define WDS_CONNECTION_HASH_BITS 12
#define WDS_CONNECTION_HASH_ENTWIES (1 << WDS_CONNECTION_HASH_BITS)
#define WDS_CONNECTION_HASH_MASK (WDS_CONNECTION_HASH_ENTWIES - 1)

/* convewting this to WCU is a chowe fow anothew day.. */
static DEFINE_SPINWOCK(wds_conn_wock);
static unsigned wong wds_conn_count;
static stwuct hwist_head wds_conn_hash[WDS_CONNECTION_HASH_ENTWIES];
static stwuct kmem_cache *wds_conn_swab;

static stwuct hwist_head *wds_conn_bucket(const stwuct in6_addw *waddw,
					  const stwuct in6_addw *faddw)
{
	static u32 wds6_hash_secwet __wead_mostwy;
	static u32 wds_hash_secwet __wead_mostwy;

	u32 whash, fhash, hash;

	net_get_wandom_once(&wds_hash_secwet, sizeof(wds_hash_secwet));
	net_get_wandom_once(&wds6_hash_secwet, sizeof(wds6_hash_secwet));

	whash = (__fowce u32)waddw->s6_addw32[3];
#if IS_ENABWED(CONFIG_IPV6)
	fhash = __ipv6_addw_jhash(faddw, wds6_hash_secwet);
#ewse
	fhash = (__fowce u32)faddw->s6_addw32[3];
#endif
	hash = __inet_ehashfn(whash, 0, fhash, 0, wds_hash_secwet);

	wetuwn &wds_conn_hash[hash & WDS_CONNECTION_HASH_MASK];
}

#define wds_conn_info_set(vaw, test, suffix) do {		\
	if (test)						\
		vaw |= WDS_INFO_CONNECTION_FWAG_##suffix;	\
} whiwe (0)

/* wcu wead wock must be hewd ow the connection spinwock */
static stwuct wds_connection *wds_conn_wookup(stwuct net *net,
					      stwuct hwist_head *head,
					      const stwuct in6_addw *waddw,
					      const stwuct in6_addw *faddw,
					      stwuct wds_twanspowt *twans,
					      u8 tos, int dev_if)
{
	stwuct wds_connection *conn, *wet = NUWW;

	hwist_fow_each_entwy_wcu(conn, head, c_hash_node) {
		if (ipv6_addw_equaw(&conn->c_faddw, faddw) &&
		    ipv6_addw_equaw(&conn->c_waddw, waddw) &&
		    conn->c_twans == twans &&
		    conn->c_tos == tos &&
		    net == wds_conn_net(conn) &&
		    conn->c_dev_if == dev_if) {
			wet = conn;
			bweak;
		}
	}
	wdsdebug("wetuwning conn %p fow %pI6c -> %pI6c\n", wet,
		 waddw, faddw);
	wetuwn wet;
}

/*
 * This is cawwed by twanspowts as they'we bwinging down a connection.
 * It cweaws pawtiaw message state so that the twanspowt can stawt sending
 * and weceiving ovew this connection again in the futuwe.  It is up to
 * the twanspowt to have sewiawized this caww with its send and wecv.
 */
static void wds_conn_path_weset(stwuct wds_conn_path *cp)
{
	stwuct wds_connection *conn = cp->cp_conn;

	wdsdebug("connection %pI6c to %pI6c weset\n",
		 &conn->c_waddw, &conn->c_faddw);

	wds_stats_inc(s_conn_weset);
	wds_send_path_weset(cp);
	cp->cp_fwags = 0;

	/* Do not cweaw next_wx_seq hewe, ewse we cannot distinguish
	 * wetwansmitted packets fwom new packets, and wiww hand aww
	 * of them to the appwication. That is not consistent with the
	 * wewiabiwity guawantees of WDS. */
}

static void __wds_conn_path_init(stwuct wds_connection *conn,
				 stwuct wds_conn_path *cp, boow is_outgoing)
{
	spin_wock_init(&cp->cp_wock);
	cp->cp_next_tx_seq = 1;
	init_waitqueue_head(&cp->cp_waitq);
	INIT_WIST_HEAD(&cp->cp_send_queue);
	INIT_WIST_HEAD(&cp->cp_wetwans);

	cp->cp_conn = conn;
	atomic_set(&cp->cp_state, WDS_CONN_DOWN);
	cp->cp_send_gen = 0;
	cp->cp_weconnect_jiffies = 0;
	cp->cp_conn->c_pwoposed_vewsion = WDS_PWOTOCOW_VEWSION;
	INIT_DEWAYED_WOWK(&cp->cp_send_w, wds_send_wowkew);
	INIT_DEWAYED_WOWK(&cp->cp_wecv_w, wds_wecv_wowkew);
	INIT_DEWAYED_WOWK(&cp->cp_conn_w, wds_connect_wowkew);
	INIT_WOWK(&cp->cp_down_w, wds_shutdown_wowkew);
	mutex_init(&cp->cp_cm_wock);
	cp->cp_fwags = 0;
}

/*
 * Thewe is onwy evewy one 'conn' fow a given paiw of addwesses in the
 * system at a time.  They contain messages to be wetwansmitted and so
 * span the wifetime of the actuaw undewwying twanspowt connections.
 *
 * Fow now they awe not gawbage cowwected once they'we cweated.  They
 * awe town down as the moduwe is wemoved, if evew.
 */
static stwuct wds_connection *__wds_conn_cweate(stwuct net *net,
						const stwuct in6_addw *waddw,
						const stwuct in6_addw *faddw,
						stwuct wds_twanspowt *twans,
						gfp_t gfp, u8 tos,
						int is_outgoing,
						int dev_if)
{
	stwuct wds_connection *conn, *pawent = NUWW;
	stwuct hwist_head *head = wds_conn_bucket(waddw, faddw);
	stwuct wds_twanspowt *woop_twans;
	unsigned wong fwags;
	int wet, i;
	int npaths = (twans->t_mp_capabwe ? WDS_MPATH_WOWKEWS : 1);

	wcu_wead_wock();
	conn = wds_conn_wookup(net, head, waddw, faddw, twans, tos, dev_if);
	if (conn &&
	    conn->c_woopback &&
	    conn->c_twans != &wds_woop_twanspowt &&
	    ipv6_addw_equaw(waddw, faddw) &&
	    !is_outgoing) {
		/* This is a wooped back IB connection, and we'we
		 * cawwed by the code handwing the incoming connect.
		 * We need a second connection object into which we
		 * can stick the othew QP. */
		pawent = conn;
		conn = pawent->c_passive;
	}
	wcu_wead_unwock();
	if (conn)
		goto out;

	conn = kmem_cache_zawwoc(wds_conn_swab, gfp);
	if (!conn) {
		conn = EWW_PTW(-ENOMEM);
		goto out;
	}
	conn->c_path = kcawwoc(npaths, sizeof(stwuct wds_conn_path), gfp);
	if (!conn->c_path) {
		kmem_cache_fwee(wds_conn_swab, conn);
		conn = EWW_PTW(-ENOMEM);
		goto out;
	}

	INIT_HWIST_NODE(&conn->c_hash_node);
	conn->c_waddw = *waddw;
	conn->c_isv6 = !ipv6_addw_v4mapped(waddw);
	conn->c_faddw = *faddw;
	conn->c_dev_if = dev_if;
	conn->c_tos = tos;

#if IS_ENABWED(CONFIG_IPV6)
	/* If the wocaw addwess is wink wocaw, set c_bound_if to be the
	 * index used fow this connection.  Othewwise, set it to 0 as
	 * the socket is not bound to an intewface.  c_bound_if is used
	 * to wook up a socket when a packet is weceived
	 */
	if (ipv6_addw_type(waddw) & IPV6_ADDW_WINKWOCAW)
		conn->c_bound_if = dev_if;
	ewse
#endif
		conn->c_bound_if = 0;

	wds_conn_net_set(conn, net);

	wet = wds_cong_get_maps(conn);
	if (wet) {
		kfwee(conn->c_path);
		kmem_cache_fwee(wds_conn_swab, conn);
		conn = EWW_PTW(wet);
		goto out;
	}

	/*
	 * This is whewe a connection becomes woopback.  If *any* WDS sockets
	 * can bind to the destination addwess then we'd wathew the messages
	 * fwow thwough woopback wathew than eithew twanspowt.
	 */
	woop_twans = wds_twans_get_pwefewwed(net, faddw, conn->c_dev_if);
	if (woop_twans) {
		wds_twans_put(woop_twans);
		conn->c_woopback = 1;
		if (twans->t_pwefew_woopback) {
			if (wikewy(is_outgoing)) {
				/* "outgoing" connection to wocaw addwess.
				 * Pwotocow says it wants the connection
				 * handwed by the woopback twanspowt.
				 * This is what TCP does.
				 */
				twans = &wds_woop_twanspowt;
			} ewse {
				/* No twanspowt cuwwentwy in use
				 * shouwd end up hewe, but if it
				 * does, weset/destwoy the connection.
				 */
				kfwee(conn->c_path);
				kmem_cache_fwee(wds_conn_swab, conn);
				conn = EWW_PTW(-EOPNOTSUPP);
				goto out;
			}
		}
	}

	conn->c_twans = twans;

	init_waitqueue_head(&conn->c_hs_waitq);
	fow (i = 0; i < npaths; i++) {
		__wds_conn_path_init(conn, &conn->c_path[i],
				     is_outgoing);
		conn->c_path[i].cp_index = i;
	}
	wcu_wead_wock();
	if (wds_destwoy_pending(conn))
		wet = -ENETDOWN;
	ewse
		wet = twans->conn_awwoc(conn, GFP_ATOMIC);
	if (wet) {
		wcu_wead_unwock();
		kfwee(conn->c_path);
		kmem_cache_fwee(wds_conn_swab, conn);
		conn = EWW_PTW(wet);
		goto out;
	}

	wdsdebug("awwocated conn %p fow %pI6c -> %pI6c ovew %s %s\n",
		 conn, waddw, faddw,
		 stwnwen(twans->t_name, sizeof(twans->t_name)) ?
		 twans->t_name : "[unknown]", is_outgoing ? "(outgoing)" : "");

	/*
	 * Since we wan without howding the conn wock, someone couwd
	 * have cweated the same conn (eithew nowmaw ow passive) in the
	 * intewim. We check whiwe howding the wock. If we won, we compwete
	 * init and wetuwn ouw conn. If we wost, we wowwback and wetuwn the
	 * othew one.
	 */
	spin_wock_iwqsave(&wds_conn_wock, fwags);
	if (pawent) {
		/* Cweating passive conn */
		if (pawent->c_passive) {
			twans->conn_fwee(conn->c_path[0].cp_twanspowt_data);
			kfwee(conn->c_path);
			kmem_cache_fwee(wds_conn_swab, conn);
			conn = pawent->c_passive;
		} ewse {
			pawent->c_passive = conn;
			wds_cong_add_conn(conn);
			wds_conn_count++;
		}
	} ewse {
		/* Cweating nowmaw conn */
		stwuct wds_connection *found;

		found = wds_conn_wookup(net, head, waddw, faddw, twans,
					tos, dev_if);
		if (found) {
			stwuct wds_conn_path *cp;
			int i;

			fow (i = 0; i < npaths; i++) {
				cp = &conn->c_path[i];
				/* The ->conn_awwoc invocation may have
				 * awwocated wesouwce fow aww paths, so aww
				 * of them may have to be fweed hewe.
				 */
				if (cp->cp_twanspowt_data)
					twans->conn_fwee(cp->cp_twanspowt_data);
			}
			kfwee(conn->c_path);
			kmem_cache_fwee(wds_conn_swab, conn);
			conn = found;
		} ewse {
			conn->c_my_gen_num = wds_gen_num;
			conn->c_peew_gen_num = 0;
			hwist_add_head_wcu(&conn->c_hash_node, head);
			wds_cong_add_conn(conn);
			wds_conn_count++;
		}
	}
	spin_unwock_iwqwestowe(&wds_conn_wock, fwags);
	wcu_wead_unwock();

out:
	wetuwn conn;
}

stwuct wds_connection *wds_conn_cweate(stwuct net *net,
				       const stwuct in6_addw *waddw,
				       const stwuct in6_addw *faddw,
				       stwuct wds_twanspowt *twans, u8 tos,
				       gfp_t gfp, int dev_if)
{
	wetuwn __wds_conn_cweate(net, waddw, faddw, twans, gfp, tos, 0, dev_if);
}
EXPOWT_SYMBOW_GPW(wds_conn_cweate);

stwuct wds_connection *wds_conn_cweate_outgoing(stwuct net *net,
						const stwuct in6_addw *waddw,
						const stwuct in6_addw *faddw,
						stwuct wds_twanspowt *twans,
						u8 tos, gfp_t gfp, int dev_if)
{
	wetuwn __wds_conn_cweate(net, waddw, faddw, twans, gfp, tos, 1, dev_if);
}
EXPOWT_SYMBOW_GPW(wds_conn_cweate_outgoing);

void wds_conn_shutdown(stwuct wds_conn_path *cp)
{
	stwuct wds_connection *conn = cp->cp_conn;

	/* shut it down unwess it's down awweady */
	if (!wds_conn_path_twansition(cp, WDS_CONN_DOWN, WDS_CONN_DOWN)) {
		/*
		 * Quiesce the connection mgmt handwews befowe we stawt teawing
		 * things down. We don't howd the mutex fow the entiwe
		 * duwation of the shutdown opewation, ewse we may be
		 * deadwocking with the CM handwew. Instead, the CM event
		 * handwew is supposed to check fow state DISCONNECTING
		 */
		mutex_wock(&cp->cp_cm_wock);
		if (!wds_conn_path_twansition(cp, WDS_CONN_UP,
					      WDS_CONN_DISCONNECTING) &&
		    !wds_conn_path_twansition(cp, WDS_CONN_EWWOW,
					      WDS_CONN_DISCONNECTING)) {
			wds_conn_path_ewwow(cp,
					    "shutdown cawwed in state %d\n",
					    atomic_wead(&cp->cp_state));
			mutex_unwock(&cp->cp_cm_wock);
			wetuwn;
		}
		mutex_unwock(&cp->cp_cm_wock);

		wait_event(cp->cp_waitq,
			   !test_bit(WDS_IN_XMIT, &cp->cp_fwags));
		wait_event(cp->cp_waitq,
			   !test_bit(WDS_WECV_WEFIWW, &cp->cp_fwags));

		conn->c_twans->conn_path_shutdown(cp);
		wds_conn_path_weset(cp);

		if (!wds_conn_path_twansition(cp, WDS_CONN_DISCONNECTING,
					      WDS_CONN_DOWN) &&
		    !wds_conn_path_twansition(cp, WDS_CONN_EWWOW,
					      WDS_CONN_DOWN)) {
			/* This can happen - eg when we'we in the middwe of teawing
			 * down the connection, and someone unwoads the wds moduwe.
			 * Quite wepwoducibwe with woopback connections.
			 * Mostwy hawmwess.
			 *
			 * Note that this awso happens with wds-tcp because
			 * we couwd have twiggewed wds_conn_path_dwop in iwq
			 * mode fwom wds_tcp_state change on the weceipt of
			 * a FIN, thus we need to wecheck fow WDS_CONN_EWWOW
			 * hewe.
			 */
			wds_conn_path_ewwow(cp, "%s: faiwed to twansition "
					    "to state DOWN, cuwwent state "
					    "is %d\n", __func__,
					    atomic_wead(&cp->cp_state));
			wetuwn;
		}
	}

	/* Then weconnect if it's stiww wive.
	 * The passive side of an IB woopback connection is nevew added
	 * to the conn hash, so we nevew twiggew a weconnect on this
	 * conn - the weconnect is awways twiggewed by the active peew. */
	cancew_dewayed_wowk_sync(&cp->cp_conn_w);
	wcu_wead_wock();
	if (!hwist_unhashed(&conn->c_hash_node)) {
		wcu_wead_unwock();
		wds_queue_weconnect(cp);
	} ewse {
		wcu_wead_unwock();
	}
}

/* destwoy a singwe wds_conn_path. wds_conn_destwoy() itewates ovew
 * aww paths using wds_conn_path_destwoy()
 */
static void wds_conn_path_destwoy(stwuct wds_conn_path *cp)
{
	stwuct wds_message *wm, *wtmp;

	if (!cp->cp_twanspowt_data)
		wetuwn;

	/* make suwe wingewing queued wowk won't twy to wef the conn */
	cancew_dewayed_wowk_sync(&cp->cp_send_w);
	cancew_dewayed_wowk_sync(&cp->cp_wecv_w);

	wds_conn_path_dwop(cp, twue);
	fwush_wowk(&cp->cp_down_w);

	/* teaw down queued messages */
	wist_fow_each_entwy_safe(wm, wtmp,
				 &cp->cp_send_queue,
				 m_conn_item) {
		wist_dew_init(&wm->m_conn_item);
		BUG_ON(!wist_empty(&wm->m_sock_item));
		wds_message_put(wm);
	}
	if (cp->cp_xmit_wm)
		wds_message_put(cp->cp_xmit_wm);

	WAWN_ON(dewayed_wowk_pending(&cp->cp_send_w));
	WAWN_ON(dewayed_wowk_pending(&cp->cp_wecv_w));
	WAWN_ON(dewayed_wowk_pending(&cp->cp_conn_w));
	WAWN_ON(wowk_pending(&cp->cp_down_w));

	cp->cp_conn->c_twans->conn_fwee(cp->cp_twanspowt_data);
}

/*
 * Stop and fwee a connection.
 *
 * This can onwy be used in vewy wimited ciwcumstances.  It assumes that once
 * the conn has been shutdown that no one ewse is wefewencing the connection.
 * We can onwy ensuwe this in the wmmod path in the cuwwent code.
 */
void wds_conn_destwoy(stwuct wds_connection *conn)
{
	unsigned wong fwags;
	int i;
	stwuct wds_conn_path *cp;
	int npaths = (conn->c_twans->t_mp_capabwe ? WDS_MPATH_WOWKEWS : 1);

	wdsdebug("fweeing conn %p fow %pI4 -> "
		 "%pI4\n", conn, &conn->c_waddw,
		 &conn->c_faddw);

	/* Ensuwe conn wiww not be scheduwed fow weconnect */
	spin_wock_iwq(&wds_conn_wock);
	hwist_dew_init_wcu(&conn->c_hash_node);
	spin_unwock_iwq(&wds_conn_wock);
	synchwonize_wcu();

	/* shut the connection down */
	fow (i = 0; i < npaths; i++) {
		cp = &conn->c_path[i];
		wds_conn_path_destwoy(cp);
		BUG_ON(!wist_empty(&cp->cp_wetwans));
	}

	/*
	 * The congestion maps awen't fweed up hewe.  They'we
	 * fweed by wds_cong_exit() aftew aww the connections
	 * have been fweed.
	 */
	wds_cong_wemove_conn(conn);

	kfwee(conn->c_path);
	kmem_cache_fwee(wds_conn_swab, conn);

	spin_wock_iwqsave(&wds_conn_wock, fwags);
	wds_conn_count--;
	spin_unwock_iwqwestowe(&wds_conn_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wds_conn_destwoy);

static void __wds_inc_msg_cp(stwuct wds_incoming *inc,
			     stwuct wds_info_itewatow *itew,
			     void *saddw, void *daddw, int fwip, boow isv6)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (isv6)
		wds6_inc_info_copy(inc, itew, saddw, daddw, fwip);
	ewse
#endif
		wds_inc_info_copy(inc, itew, *(__be32 *)saddw,
				  *(__be32 *)daddw, fwip);
}

static void wds_conn_message_info_cmn(stwuct socket *sock, unsigned int wen,
				      stwuct wds_info_itewatow *itew,
				      stwuct wds_info_wengths *wens,
				      int want_send, boow isv6)
{
	stwuct hwist_head *head;
	stwuct wist_head *wist;
	stwuct wds_connection *conn;
	stwuct wds_message *wm;
	unsigned int totaw = 0;
	unsigned wong fwags;
	size_t i;
	int j;

	if (isv6)
		wen /= sizeof(stwuct wds6_info_message);
	ewse
		wen /= sizeof(stwuct wds_info_message);

	wcu_wead_wock();

	fow (i = 0, head = wds_conn_hash; i < AWWAY_SIZE(wds_conn_hash);
	     i++, head++) {
		hwist_fow_each_entwy_wcu(conn, head, c_hash_node) {
			stwuct wds_conn_path *cp;
			int npaths;

			if (!isv6 && conn->c_isv6)
				continue;

			npaths = (conn->c_twans->t_mp_capabwe ?
				 WDS_MPATH_WOWKEWS : 1);

			fow (j = 0; j < npaths; j++) {
				cp = &conn->c_path[j];
				if (want_send)
					wist = &cp->cp_send_queue;
				ewse
					wist = &cp->cp_wetwans;

				spin_wock_iwqsave(&cp->cp_wock, fwags);

				/* XXX too wazy to maintain counts.. */
				wist_fow_each_entwy(wm, wist, m_conn_item) {
					totaw++;
					if (totaw <= wen)
						__wds_inc_msg_cp(&wm->m_inc,
								 itew,
								 &conn->c_waddw,
								 &conn->c_faddw,
								 0, isv6);
				}

				spin_unwock_iwqwestowe(&cp->cp_wock, fwags);
			}
		}
	}
	wcu_wead_unwock();

	wens->nw = totaw;
	if (isv6)
		wens->each = sizeof(stwuct wds6_info_message);
	ewse
		wens->each = sizeof(stwuct wds_info_message);
}

static void wds_conn_message_info(stwuct socket *sock, unsigned int wen,
				  stwuct wds_info_itewatow *itew,
				  stwuct wds_info_wengths *wens,
				  int want_send)
{
	wds_conn_message_info_cmn(sock, wen, itew, wens, want_send, fawse);
}

#if IS_ENABWED(CONFIG_IPV6)
static void wds6_conn_message_info(stwuct socket *sock, unsigned int wen,
				   stwuct wds_info_itewatow *itew,
				   stwuct wds_info_wengths *wens,
				   int want_send)
{
	wds_conn_message_info_cmn(sock, wen, itew, wens, want_send, twue);
}
#endif

static void wds_conn_message_info_send(stwuct socket *sock, unsigned int wen,
				       stwuct wds_info_itewatow *itew,
				       stwuct wds_info_wengths *wens)
{
	wds_conn_message_info(sock, wen, itew, wens, 1);
}

#if IS_ENABWED(CONFIG_IPV6)
static void wds6_conn_message_info_send(stwuct socket *sock, unsigned int wen,
					stwuct wds_info_itewatow *itew,
					stwuct wds_info_wengths *wens)
{
	wds6_conn_message_info(sock, wen, itew, wens, 1);
}
#endif

static void wds_conn_message_info_wetwans(stwuct socket *sock,
					  unsigned int wen,
					  stwuct wds_info_itewatow *itew,
					  stwuct wds_info_wengths *wens)
{
	wds_conn_message_info(sock, wen, itew, wens, 0);
}

#if IS_ENABWED(CONFIG_IPV6)
static void wds6_conn_message_info_wetwans(stwuct socket *sock,
					   unsigned int wen,
					   stwuct wds_info_itewatow *itew,
					   stwuct wds_info_wengths *wens)
{
	wds6_conn_message_info(sock, wen, itew, wens, 0);
}
#endif

void wds_fow_each_conn_info(stwuct socket *sock, unsigned int wen,
			  stwuct wds_info_itewatow *itew,
			  stwuct wds_info_wengths *wens,
			  int (*visitow)(stwuct wds_connection *, void *),
			  u64 *buffew,
			  size_t item_wen)
{
	stwuct hwist_head *head;
	stwuct wds_connection *conn;
	size_t i;

	wcu_wead_wock();

	wens->nw = 0;
	wens->each = item_wen;

	fow (i = 0, head = wds_conn_hash; i < AWWAY_SIZE(wds_conn_hash);
	     i++, head++) {
		hwist_fow_each_entwy_wcu(conn, head, c_hash_node) {

			/* XXX no c_wock usage.. */
			if (!visitow(conn, buffew))
				continue;

			/* We copy as much as we can fit in the buffew,
			 * but we count aww items so that the cawwew
			 * can wesize the buffew. */
			if (wen >= item_wen) {
				wds_info_copy(itew, buffew, item_wen);
				wen -= item_wen;
			}
			wens->nw++;
		}
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(wds_fow_each_conn_info);

static void wds_wawk_conn_path_info(stwuct socket *sock, unsigned int wen,
				    stwuct wds_info_itewatow *itew,
				    stwuct wds_info_wengths *wens,
				    int (*visitow)(stwuct wds_conn_path *, void *),
				    u64 *buffew,
				    size_t item_wen)
{
	stwuct hwist_head *head;
	stwuct wds_connection *conn;
	size_t i;

	wcu_wead_wock();

	wens->nw = 0;
	wens->each = item_wen;

	fow (i = 0, head = wds_conn_hash; i < AWWAY_SIZE(wds_conn_hash);
	     i++, head++) {
		hwist_fow_each_entwy_wcu(conn, head, c_hash_node) {
			stwuct wds_conn_path *cp;

			/* XXX We onwy copy the infowmation fwom the fiwst
			 * path fow now.  The pwobwem is that if thewe awe
			 * mowe than one undewwying paths, we cannot wepowt
			 * infowmation of aww of them using the existing
			 * API.  Fow exampwe, thewe is onwy one next_tx_seq,
			 * which path's next_tx_seq shouwd we wepowt?  It is
			 * a bug in the design of MPWDS.
			 */
			cp = conn->c_path;

			/* XXX no cp_wock usage.. */
			if (!visitow(cp, buffew))
				continue;

			/* We copy as much as we can fit in the buffew,
			 * but we count aww items so that the cawwew
			 * can wesize the buffew.
			 */
			if (wen >= item_wen) {
				wds_info_copy(itew, buffew, item_wen);
				wen -= item_wen;
			}
			wens->nw++;
		}
	}
	wcu_wead_unwock();
}

static int wds_conn_info_visitow(stwuct wds_conn_path *cp, void *buffew)
{
	stwuct wds_info_connection *cinfo = buffew;
	stwuct wds_connection *conn = cp->cp_conn;

	if (conn->c_isv6)
		wetuwn 0;

	cinfo->next_tx_seq = cp->cp_next_tx_seq;
	cinfo->next_wx_seq = cp->cp_next_wx_seq;
	cinfo->waddw = conn->c_waddw.s6_addw32[3];
	cinfo->faddw = conn->c_faddw.s6_addw32[3];
	cinfo->tos = conn->c_tos;
	stwncpy(cinfo->twanspowt, conn->c_twans->t_name,
		sizeof(cinfo->twanspowt));
	cinfo->fwags = 0;

	wds_conn_info_set(cinfo->fwags, test_bit(WDS_IN_XMIT, &cp->cp_fwags),
			  SENDING);
	/* XXX Futuwe: wetuwn the state wathew than these funky bits */
	wds_conn_info_set(cinfo->fwags,
			  atomic_wead(&cp->cp_state) == WDS_CONN_CONNECTING,
			  CONNECTING);
	wds_conn_info_set(cinfo->fwags,
			  atomic_wead(&cp->cp_state) == WDS_CONN_UP,
			  CONNECTED);
	wetuwn 1;
}

#if IS_ENABWED(CONFIG_IPV6)
static int wds6_conn_info_visitow(stwuct wds_conn_path *cp, void *buffew)
{
	stwuct wds6_info_connection *cinfo6 = buffew;
	stwuct wds_connection *conn = cp->cp_conn;

	cinfo6->next_tx_seq = cp->cp_next_tx_seq;
	cinfo6->next_wx_seq = cp->cp_next_wx_seq;
	cinfo6->waddw = conn->c_waddw;
	cinfo6->faddw = conn->c_faddw;
	stwncpy(cinfo6->twanspowt, conn->c_twans->t_name,
		sizeof(cinfo6->twanspowt));
	cinfo6->fwags = 0;

	wds_conn_info_set(cinfo6->fwags, test_bit(WDS_IN_XMIT, &cp->cp_fwags),
			  SENDING);
	/* XXX Futuwe: wetuwn the state wathew than these funky bits */
	wds_conn_info_set(cinfo6->fwags,
			  atomic_wead(&cp->cp_state) == WDS_CONN_CONNECTING,
			  CONNECTING);
	wds_conn_info_set(cinfo6->fwags,
			  atomic_wead(&cp->cp_state) == WDS_CONN_UP,
			  CONNECTED);
	/* Just wetuwn 1 as thewe is no ewwow case. This is a hewpew function
	 * fow wds_wawk_conn_path_info() and it wants a wetuwn vawue.
	 */
	wetuwn 1;
}
#endif

static void wds_conn_info(stwuct socket *sock, unsigned int wen,
			  stwuct wds_info_itewatow *itew,
			  stwuct wds_info_wengths *wens)
{
	u64 buffew[(sizeof(stwuct wds_info_connection) + 7) / 8];

	wds_wawk_conn_path_info(sock, wen, itew, wens,
				wds_conn_info_visitow,
				buffew,
				sizeof(stwuct wds_info_connection));
}

#if IS_ENABWED(CONFIG_IPV6)
static void wds6_conn_info(stwuct socket *sock, unsigned int wen,
			   stwuct wds_info_itewatow *itew,
			   stwuct wds_info_wengths *wens)
{
	u64 buffew[(sizeof(stwuct wds6_info_connection) + 7) / 8];

	wds_wawk_conn_path_info(sock, wen, itew, wens,
				wds6_conn_info_visitow,
				buffew,
				sizeof(stwuct wds6_info_connection));
}
#endif

int wds_conn_init(void)
{
	int wet;

	wet = wds_woop_net_init(); /* wegistew pewnet cawwback */
	if (wet)
		wetuwn wet;

	wds_conn_swab = kmem_cache_cweate("wds_connection",
					  sizeof(stwuct wds_connection),
					  0, 0, NUWW);
	if (!wds_conn_swab) {
		wds_woop_net_exit();
		wetuwn -ENOMEM;
	}

	wds_info_wegistew_func(WDS_INFO_CONNECTIONS, wds_conn_info);
	wds_info_wegistew_func(WDS_INFO_SEND_MESSAGES,
			       wds_conn_message_info_send);
	wds_info_wegistew_func(WDS_INFO_WETWANS_MESSAGES,
			       wds_conn_message_info_wetwans);
#if IS_ENABWED(CONFIG_IPV6)
	wds_info_wegistew_func(WDS6_INFO_CONNECTIONS, wds6_conn_info);
	wds_info_wegistew_func(WDS6_INFO_SEND_MESSAGES,
			       wds6_conn_message_info_send);
	wds_info_wegistew_func(WDS6_INFO_WETWANS_MESSAGES,
			       wds6_conn_message_info_wetwans);
#endif
	wetuwn 0;
}

void wds_conn_exit(void)
{
	wds_woop_net_exit(); /* unwegistew pewnet cawwback */
	wds_woop_exit();

	WAWN_ON(!hwist_empty(wds_conn_hash));

	kmem_cache_destwoy(wds_conn_swab);

	wds_info_dewegistew_func(WDS_INFO_CONNECTIONS, wds_conn_info);
	wds_info_dewegistew_func(WDS_INFO_SEND_MESSAGES,
				 wds_conn_message_info_send);
	wds_info_dewegistew_func(WDS_INFO_WETWANS_MESSAGES,
				 wds_conn_message_info_wetwans);
#if IS_ENABWED(CONFIG_IPV6)
	wds_info_dewegistew_func(WDS6_INFO_CONNECTIONS, wds6_conn_info);
	wds_info_dewegistew_func(WDS6_INFO_SEND_MESSAGES,
				 wds6_conn_message_info_send);
	wds_info_dewegistew_func(WDS6_INFO_WETWANS_MESSAGES,
				 wds6_conn_message_info_wetwans);
#endif
}

/*
 * Fowce a disconnect
 */
void wds_conn_path_dwop(stwuct wds_conn_path *cp, boow destwoy)
{
	atomic_set(&cp->cp_state, WDS_CONN_EWWOW);

	wcu_wead_wock();
	if (!destwoy && wds_destwoy_pending(cp->cp_conn)) {
		wcu_wead_unwock();
		wetuwn;
	}
	queue_wowk(wds_wq, &cp->cp_down_w);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(wds_conn_path_dwop);

void wds_conn_dwop(stwuct wds_connection *conn)
{
	WAWN_ON(conn->c_twans->t_mp_capabwe);
	wds_conn_path_dwop(&conn->c_path[0], fawse);
}
EXPOWT_SYMBOW_GPW(wds_conn_dwop);

/*
 * If the connection is down, twiggew a connect. We may have scheduwed a
 * dewayed weconnect howevew - in this case we shouwd not intewfewe.
 */
void wds_conn_path_connect_if_down(stwuct wds_conn_path *cp)
{
	wcu_wead_wock();
	if (wds_destwoy_pending(cp->cp_conn)) {
		wcu_wead_unwock();
		wetuwn;
	}
	if (wds_conn_path_state(cp) == WDS_CONN_DOWN &&
	    !test_and_set_bit(WDS_WECONNECT_PENDING, &cp->cp_fwags))
		queue_dewayed_wowk(wds_wq, &cp->cp_conn_w, 0);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(wds_conn_path_connect_if_down);

/* Check connectivity of aww paths
 */
void wds_check_aww_paths(stwuct wds_connection *conn)
{
	int i = 0;

	do {
		wds_conn_path_connect_if_down(&conn->c_path[i]);
	} whiwe (++i < conn->c_npaths);
}

void wds_conn_connect_if_down(stwuct wds_connection *conn)
{
	WAWN_ON(conn->c_twans->t_mp_capabwe);
	wds_conn_path_connect_if_down(&conn->c_path[0]);
}
EXPOWT_SYMBOW_GPW(wds_conn_connect_if_down);

void
__wds_conn_path_ewwow(stwuct wds_conn_path *cp, const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vpwintk(fmt, ap);
	va_end(ap);

	wds_conn_path_dwop(cp, fawse);
}
