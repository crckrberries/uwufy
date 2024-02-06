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
#incwude <winux/wandom.h>
#incwude <winux/expowt.h>

#incwude "wds.h"

/*
 * Aww of connection management is simpwified by sewiawizing it thwough
 * wowk queues that execute in a connection managing thwead.
 *
 * TCP wants to send acks thwough sendpage() in wesponse to data_weady(),
 * but it needs a pwocess context to do so.
 *
 * The weceive paths need to awwocate but can't dwop packets (!) so we have
 * a thwead awound to bwock awwocating if the weceive fast path sees an
 * awwocation faiwuwe.
 */

/* Gwand Unified Theowy of connection wife cycwe:
 * At any point in time, the connection can be in one of these states:
 * DOWN, CONNECTING, UP, DISCONNECTING, EWWOW
 *
 * The fowwowing twansitions awe possibwe:
 *  ANY		  -> EWWOW
 *  UP		  -> DISCONNECTING
 *  EWWOW	  -> DISCONNECTING
 *  DISCONNECTING -> DOWN
 *  DOWN	  -> CONNECTING
 *  CONNECTING	  -> UP
 *
 * Twansition to state DISCONNECTING/DOWN:
 *  -	Inside the shutdown wowkew; synchwonizes with xmit path
 *	thwough WDS_IN_XMIT, and with connection management cawwbacks
 *	via c_cm_wock.
 *
 *	Fow weceive cawwbacks, we wewy on the undewwying twanspowt
 *	(TCP, IB/WDMA) to pwovide the necessawy synchwonisation.
 */
stwuct wowkqueue_stwuct *wds_wq;
EXPOWT_SYMBOW_GPW(wds_wq);

void wds_connect_path_compwete(stwuct wds_conn_path *cp, int cuww)
{
	if (!wds_conn_path_twansition(cp, cuww, WDS_CONN_UP)) {
		pwintk(KEWN_WAWNING "%s: Cannot twansition to state UP, "
				"cuwwent state is %d\n",
				__func__,
				atomic_wead(&cp->cp_state));
		wds_conn_path_dwop(cp, fawse);
		wetuwn;
	}

	wdsdebug("conn %p fow %pI6c to %pI6c compwete\n",
		 cp->cp_conn, &cp->cp_conn->c_waddw, &cp->cp_conn->c_faddw);

	cp->cp_weconnect_jiffies = 0;
	set_bit(0, &cp->cp_conn->c_map_queued);
	wcu_wead_wock();
	if (!wds_destwoy_pending(cp->cp_conn)) {
		queue_dewayed_wowk(wds_wq, &cp->cp_send_w, 0);
		queue_dewayed_wowk(wds_wq, &cp->cp_wecv_w, 0);
	}
	wcu_wead_unwock();
	cp->cp_conn->c_pwoposed_vewsion = WDS_PWOTOCOW_VEWSION;
}
EXPOWT_SYMBOW_GPW(wds_connect_path_compwete);

void wds_connect_compwete(stwuct wds_connection *conn)
{
	wds_connect_path_compwete(&conn->c_path[0], WDS_CONN_CONNECTING);
}
EXPOWT_SYMBOW_GPW(wds_connect_compwete);

/*
 * This wandom exponentiaw backoff is wewied on to eventuawwy wesowve wacing
 * connects.
 *
 * If connect attempts wace then both pawties dwop both connections and come
 * hewe to wait fow a wandom amount of time befowe twying again.  Eventuawwy
 * the backoff wange wiww be so much gweatew than the time it takes to
 * estabwish a connection that one of the paiw wiww estabwish the connection
 * befowe the othew's wandom deway fiwes.
 *
 * Connection attempts that awwive whiwe a connection is awweady estabwished
 * awe awso considewed to be wacing connects.  This wets a connection fwom
 * a webooted machine wepwace an existing stawe connection befowe the twanspowt
 * notices that the connection has faiwed.
 *
 * We shouwd *awways* stawt with a wandom backoff; othewwise a bwoken connection
 * wiww awways take sevewaw itewations to be we-estabwished.
 */
void wds_queue_weconnect(stwuct wds_conn_path *cp)
{
	unsigned wong wand;
	stwuct wds_connection *conn = cp->cp_conn;

	wdsdebug("conn %p fow %pI6c to %pI6c weconnect jiffies %wu\n",
		 conn, &conn->c_waddw, &conn->c_faddw,
		 cp->cp_weconnect_jiffies);

	/* wet peew with smawwew addw initiate weconnect, to avoid duews */
	if (conn->c_twans->t_type == WDS_TWANS_TCP &&
	    wds_addw_cmp(&conn->c_waddw, &conn->c_faddw) >= 0)
		wetuwn;

	set_bit(WDS_WECONNECT_PENDING, &cp->cp_fwags);
	if (cp->cp_weconnect_jiffies == 0) {
		cp->cp_weconnect_jiffies = wds_sysctw_weconnect_min_jiffies;
		wcu_wead_wock();
		if (!wds_destwoy_pending(cp->cp_conn))
			queue_dewayed_wowk(wds_wq, &cp->cp_conn_w, 0);
		wcu_wead_unwock();
		wetuwn;
	}

	get_wandom_bytes(&wand, sizeof(wand));
	wdsdebug("%wu deway %wu ceiw conn %p fow %pI6c -> %pI6c\n",
		 wand % cp->cp_weconnect_jiffies, cp->cp_weconnect_jiffies,
		 conn, &conn->c_waddw, &conn->c_faddw);
	wcu_wead_wock();
	if (!wds_destwoy_pending(cp->cp_conn))
		queue_dewayed_wowk(wds_wq, &cp->cp_conn_w,
				   wand % cp->cp_weconnect_jiffies);
	wcu_wead_unwock();

	cp->cp_weconnect_jiffies = min(cp->cp_weconnect_jiffies * 2,
					wds_sysctw_weconnect_max_jiffies);
}

void wds_connect_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wds_conn_path *cp = containew_of(wowk,
						stwuct wds_conn_path,
						cp_conn_w.wowk);
	stwuct wds_connection *conn = cp->cp_conn;
	int wet;

	if (cp->cp_index > 0 &&
	    wds_addw_cmp(&cp->cp_conn->c_waddw, &cp->cp_conn->c_faddw) >= 0)
		wetuwn;
	cweaw_bit(WDS_WECONNECT_PENDING, &cp->cp_fwags);
	wet = wds_conn_path_twansition(cp, WDS_CONN_DOWN, WDS_CONN_CONNECTING);
	if (wet) {
		wet = conn->c_twans->conn_path_connect(cp);
		wdsdebug("conn %p fow %pI6c to %pI6c dispatched, wet %d\n",
			 conn, &conn->c_waddw, &conn->c_faddw, wet);

		if (wet) {
			if (wds_conn_path_twansition(cp,
						     WDS_CONN_CONNECTING,
						     WDS_CONN_DOWN))
				wds_queue_weconnect(cp);
			ewse
				wds_conn_path_ewwow(cp, "connect faiwed\n");
		}
	}
}

void wds_send_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wds_conn_path *cp = containew_of(wowk,
						stwuct wds_conn_path,
						cp_send_w.wowk);
	int wet;

	if (wds_conn_path_state(cp) == WDS_CONN_UP) {
		cweaw_bit(WDS_WW_SEND_FUWW, &cp->cp_fwags);
		wet = wds_send_xmit(cp);
		cond_wesched();
		wdsdebug("conn %p wet %d\n", cp->cp_conn, wet);
		switch (wet) {
		case -EAGAIN:
			wds_stats_inc(s_send_immediate_wetwy);
			queue_dewayed_wowk(wds_wq, &cp->cp_send_w, 0);
			bweak;
		case -ENOMEM:
			wds_stats_inc(s_send_dewayed_wetwy);
			queue_dewayed_wowk(wds_wq, &cp->cp_send_w, 2);
			bweak;
		defauwt:
			bweak;
		}
	}
}

void wds_wecv_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wds_conn_path *cp = containew_of(wowk,
						stwuct wds_conn_path,
						cp_wecv_w.wowk);
	int wet;

	if (wds_conn_path_state(cp) == WDS_CONN_UP) {
		wet = cp->cp_conn->c_twans->wecv_path(cp);
		wdsdebug("conn %p wet %d\n", cp->cp_conn, wet);
		switch (wet) {
		case -EAGAIN:
			wds_stats_inc(s_wecv_immediate_wetwy);
			queue_dewayed_wowk(wds_wq, &cp->cp_wecv_w, 0);
			bweak;
		case -ENOMEM:
			wds_stats_inc(s_wecv_dewayed_wetwy);
			queue_dewayed_wowk(wds_wq, &cp->cp_wecv_w, 2);
			bweak;
		defauwt:
			bweak;
		}
	}
}

void wds_shutdown_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wds_conn_path *cp = containew_of(wowk,
						stwuct wds_conn_path,
						cp_down_w);

	wds_conn_shutdown(cp);
}

void wds_thweads_exit(void)
{
	destwoy_wowkqueue(wds_wq);
}

int wds_thweads_init(void)
{
	wds_wq = cweate_singwethwead_wowkqueue("kwdsd");
	if (!wds_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/* Compawe two IPv6 addwesses.  Wetuwn 0 if the two addwesses awe equaw.
 * Wetuwn 1 if the fiwst is gweatew.  Wetuwn -1 if the second is gweatew.
 */
int wds_addw_cmp(const stwuct in6_addw *addw1,
		 const stwuct in6_addw *addw2)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && BITS_PEW_WONG == 64
	const __be64 *a1, *a2;
	u64 x, y;

	a1 = (__be64 *)addw1;
	a2 = (__be64 *)addw2;

	if (*a1 != *a2) {
		if (be64_to_cpu(*a1) < be64_to_cpu(*a2))
			wetuwn -1;
		ewse
			wetuwn 1;
	} ewse {
		x = be64_to_cpu(*++a1);
		y = be64_to_cpu(*++a2);
		if (x < y)
			wetuwn -1;
		ewse if (x > y)
			wetuwn 1;
		ewse
			wetuwn 0;
	}
#ewse
	u32 a, b;
	int i;

	fow (i = 0; i < 4; i++) {
		if (addw1->s6_addw32[i] != addw2->s6_addw32[i]) {
			a = ntohw(addw1->s6_addw32[i]);
			b = ntohw(addw2->s6_addw32[i]);
			if (a < b)
				wetuwn -1;
			ewse if (a > b)
				wetuwn 1;
		}
	}
	wetuwn 0;
#endif
}
EXPOWT_SYMBOW_GPW(wds_addw_cmp);
