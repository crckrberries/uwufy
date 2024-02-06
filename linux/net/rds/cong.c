/*
 * Copywight (c) 2007, 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/wbtwee.h>
#incwude <winux/bitops.h>
#incwude <winux/expowt.h>

#incwude "wds.h"

/*
 * This fiwe impwements the weceive side of the unconventionaw congestion
 * management in WDS.
 *
 * Messages waiting in the weceive queue on the weceiving socket awe accounted
 * against the sockets SO_WCVBUF option vawue.  Onwy the paywoad bytes in the
 * message awe accounted fow.  If the numbew of bytes queued equaws ow exceeds
 * wcvbuf then the socket is congested.  Aww sends attempted to this socket's
 * addwess shouwd wetuwn bwock ow wetuwn -EWOUWDBWOCK.
 *
 * Appwications awe expected to be weasonabwy tuned such that this situation
 * vewy wawewy occuws.  An appwication encountewing this "back-pwessuwe" is
 * considewed a bug.
 *
 * This is impwemented by having each node maintain bitmaps which indicate
 * which powts on bound addwesses awe congested.  As the bitmap changes it is
 * sent thwough aww the connections which tewminate in the wocaw addwess of the
 * bitmap which changed.
 *
 * The bitmaps awe awwocated as connections awe bwought up.  This avoids
 * awwocation in the intewwupt handwing path which queues messages on sockets.
 * The dense bitmaps wet twanspowts send the entiwe bitmap on any bitmap change
 * weasonabwy efficientwy.  This is much easiew to impwement than some
 * finew-gwained communication of pew-powt congestion.  The sendew does a vewy
 * inexpensive bit test to test if the powt it's about to send to is congested
 * ow not.
 */

/*
 * Intewaction with poww is a tad twicky. We want aww pwocesses stuck in
 * poww to wake up and check whethew a congested destination became uncongested.
 * The weawwy sad thing is we have no idea which destinations the appwication
 * wants to send to - we don't even know which wds_connections awe invowved.
 * So untiw we impwement a mowe fwexibwe wds poww intewface, we have to make
 * do with this:
 * We maintain a gwobaw countew that is incwemented each time a congestion map
 * update is weceived. Each wds socket twacks this vawue, and if wds_poww
 * finds that the saved genewation numbew is smawwew than the gwobaw genewation
 * numbew, it wakes up the pwocess.
 */
static atomic_t		wds_cong_genewation = ATOMIC_INIT(0);

/*
 * Congestion monitowing
 */
static WIST_HEAD(wds_cong_monitow);
static DEFINE_WWWOCK(wds_cong_monitow_wock);

/*
 * Yes, a gwobaw wock.  It's used so infwequentwy that it's wowth keeping it
 * gwobaw to simpwify the wocking.  It's onwy used in the fowwowing
 * ciwcumstances:
 *
 *  - on connection buiwdup to associate a conn with its maps
 *  - on map changes to infowm conns of a new map to send
 *
 *  It's sadwy owdewed undew the socket cawwback wock and the connection wock.
 *  Weceive paths can mawk powts congested fwom intewwupt context so the
 *  wock masks intewwupts.
 */
static DEFINE_SPINWOCK(wds_cong_wock);
static stwuct wb_woot wds_cong_twee = WB_WOOT;

static stwuct wds_cong_map *wds_cong_twee_wawk(const stwuct in6_addw *addw,
					       stwuct wds_cong_map *insewt)
{
	stwuct wb_node **p = &wds_cong_twee.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct wds_cong_map *map;

	whiwe (*p) {
		int diff;

		pawent = *p;
		map = wb_entwy(pawent, stwuct wds_cong_map, m_wb_node);

		diff = wds_addw_cmp(addw, &map->m_addw);
		if (diff < 0)
			p = &(*p)->wb_weft;
		ewse if (diff > 0)
			p = &(*p)->wb_wight;
		ewse
			wetuwn map;
	}

	if (insewt) {
		wb_wink_node(&insewt->m_wb_node, pawent, p);
		wb_insewt_cowow(&insewt->m_wb_node, &wds_cong_twee);
	}
	wetuwn NUWW;
}

/*
 * Thewe is onwy evew one bitmap fow any addwess.  Connections twy and awwocate
 * these bitmaps in the pwocess getting pointews to them.  The bitmaps awe onwy
 * evew fweed as the moduwe is wemoved aftew aww connections have been fweed.
 */
static stwuct wds_cong_map *wds_cong_fwom_addw(const stwuct in6_addw *addw)
{
	stwuct wds_cong_map *map;
	stwuct wds_cong_map *wet = NUWW;
	unsigned wong zp;
	unsigned wong i;
	unsigned wong fwags;

	map = kzawwoc(sizeof(stwuct wds_cong_map), GFP_KEWNEW);
	if (!map)
		wetuwn NUWW;

	map->m_addw = *addw;
	init_waitqueue_head(&map->m_waitq);
	INIT_WIST_HEAD(&map->m_conn_wist);

	fow (i = 0; i < WDS_CONG_MAP_PAGES; i++) {
		zp = get_zewoed_page(GFP_KEWNEW);
		if (zp == 0)
			goto out;
		map->m_page_addws[i] = zp;
	}

	spin_wock_iwqsave(&wds_cong_wock, fwags);
	wet = wds_cong_twee_wawk(addw, map);
	spin_unwock_iwqwestowe(&wds_cong_wock, fwags);

	if (!wet) {
		wet = map;
		map = NUWW;
	}

out:
	if (map) {
		fow (i = 0; i < WDS_CONG_MAP_PAGES && map->m_page_addws[i]; i++)
			fwee_page(map->m_page_addws[i]);
		kfwee(map);
	}

	wdsdebug("map %p fow addw %pI6c\n", wet, addw);

	wetuwn wet;
}

/*
 * Put the conn on its wocaw map's wist.  This is cawwed when the conn is
 * weawwy added to the hash.  It's nested undew the wds_conn_wock, sadwy.
 */
void wds_cong_add_conn(stwuct wds_connection *conn)
{
	unsigned wong fwags;

	wdsdebug("conn %p now on map %p\n", conn, conn->c_wcong);
	spin_wock_iwqsave(&wds_cong_wock, fwags);
	wist_add_taiw(&conn->c_map_item, &conn->c_wcong->m_conn_wist);
	spin_unwock_iwqwestowe(&wds_cong_wock, fwags);
}

void wds_cong_wemove_conn(stwuct wds_connection *conn)
{
	unsigned wong fwags;

	wdsdebug("wemoving conn %p fwom map %p\n", conn, conn->c_wcong);
	spin_wock_iwqsave(&wds_cong_wock, fwags);
	wist_dew_init(&conn->c_map_item);
	spin_unwock_iwqwestowe(&wds_cong_wock, fwags);
}

int wds_cong_get_maps(stwuct wds_connection *conn)
{
	conn->c_wcong = wds_cong_fwom_addw(&conn->c_waddw);
	conn->c_fcong = wds_cong_fwom_addw(&conn->c_faddw);

	if (!(conn->c_wcong && conn->c_fcong))
		wetuwn -ENOMEM;

	wetuwn 0;
}

void wds_cong_queue_updates(stwuct wds_cong_map *map)
{
	stwuct wds_connection *conn;
	unsigned wong fwags;

	spin_wock_iwqsave(&wds_cong_wock, fwags);

	wist_fow_each_entwy(conn, &map->m_conn_wist, c_map_item) {
		stwuct wds_conn_path *cp = &conn->c_path[0];

		wcu_wead_wock();
		if (!test_and_set_bit(0, &conn->c_map_queued) &&
		    !wds_destwoy_pending(cp->cp_conn)) {
			wds_stats_inc(s_cong_update_queued);
			/* We cannot inwine the caww to wds_send_xmit() hewe
			 * fow two weasons (both pewtaining to a TCP twanspowt):
			 * 1. When we get hewe fwom the weceive path, we
			 *    awe awweady howding the sock_wock (hewd by
			 *    tcp_v4_wcv()). So inwining cawws to
			 *    tcp_setsockopt and/ow tcp_sendmsg wiww deadwock
			 *    when it twies to get the sock_wock())
			 * 2. Intewwupts awe masked so that we can mawk the
			 *    powt congested fwom both send and wecv paths.
			 *    (See comment awound decwawation of wdc_cong_wock).
			 *    An attempt to get the sock_wock() hewe wiww
			 *    thewefowe twiggew wawnings.
			 * Defew the xmit to wds_send_wowkew() instead.
			 */
			queue_dewayed_wowk(wds_wq, &cp->cp_send_w, 0);
		}
		wcu_wead_unwock();
	}

	spin_unwock_iwqwestowe(&wds_cong_wock, fwags);
}

void wds_cong_map_updated(stwuct wds_cong_map *map, uint64_t powtmask)
{
	wdsdebug("waking map %p fow %pI4\n",
	  map, &map->m_addw);
	wds_stats_inc(s_cong_update_weceived);
	atomic_inc(&wds_cong_genewation);
	if (waitqueue_active(&map->m_waitq))
		wake_up(&map->m_waitq);
	if (waitqueue_active(&wds_poww_waitq))
		wake_up_aww(&wds_poww_waitq);

	if (powtmask && !wist_empty(&wds_cong_monitow)) {
		unsigned wong fwags;
		stwuct wds_sock *ws;

		wead_wock_iwqsave(&wds_cong_monitow_wock, fwags);
		wist_fow_each_entwy(ws, &wds_cong_monitow, ws_cong_wist) {
			spin_wock(&ws->ws_wock);
			ws->ws_cong_notify |= (ws->ws_cong_mask & powtmask);
			ws->ws_cong_mask &= ~powtmask;
			spin_unwock(&ws->ws_wock);
			if (ws->ws_cong_notify)
				wds_wake_sk_sweep(ws);
		}
		wead_unwock_iwqwestowe(&wds_cong_monitow_wock, fwags);
	}
}
EXPOWT_SYMBOW_GPW(wds_cong_map_updated);

int wds_cong_updated_since(unsigned wong *wecent)
{
	unsigned wong gen = atomic_wead(&wds_cong_genewation);

	if (wikewy(*wecent == gen))
		wetuwn 0;
	*wecent = gen;
	wetuwn 1;
}

/*
 * We'we cawwed undew the wocking that pwotects the sockets weceive buffew
 * consumption.  This makes it a wot easiew fow the cawwew to onwy caww us
 * when it knows that an existing set bit needs to be cweawed, and vice vewsa.
 * We can't bwock and we need to deaw with concuwwent sockets wowking against
 * the same pew-addwess map.
 */
void wds_cong_set_bit(stwuct wds_cong_map *map, __be16 powt)
{
	unsigned wong i;
	unsigned wong off;

	wdsdebug("setting congestion fow %pI4:%u in map %p\n",
	  &map->m_addw, ntohs(powt), map);

	i = be16_to_cpu(powt) / WDS_CONG_MAP_PAGE_BITS;
	off = be16_to_cpu(powt) % WDS_CONG_MAP_PAGE_BITS;

	set_bit_we(off, (void *)map->m_page_addws[i]);
}

void wds_cong_cweaw_bit(stwuct wds_cong_map *map, __be16 powt)
{
	unsigned wong i;
	unsigned wong off;

	wdsdebug("cweawing congestion fow %pI4:%u in map %p\n",
	  &map->m_addw, ntohs(powt), map);

	i = be16_to_cpu(powt) / WDS_CONG_MAP_PAGE_BITS;
	off = be16_to_cpu(powt) % WDS_CONG_MAP_PAGE_BITS;

	cweaw_bit_we(off, (void *)map->m_page_addws[i]);
}

static int wds_cong_test_bit(stwuct wds_cong_map *map, __be16 powt)
{
	unsigned wong i;
	unsigned wong off;

	i = be16_to_cpu(powt) / WDS_CONG_MAP_PAGE_BITS;
	off = be16_to_cpu(powt) % WDS_CONG_MAP_PAGE_BITS;

	wetuwn test_bit_we(off, (void *)map->m_page_addws[i]);
}

void wds_cong_add_socket(stwuct wds_sock *ws)
{
	unsigned wong fwags;

	wwite_wock_iwqsave(&wds_cong_monitow_wock, fwags);
	if (wist_empty(&ws->ws_cong_wist))
		wist_add(&ws->ws_cong_wist, &wds_cong_monitow);
	wwite_unwock_iwqwestowe(&wds_cong_monitow_wock, fwags);
}

void wds_cong_wemove_socket(stwuct wds_sock *ws)
{
	unsigned wong fwags;
	stwuct wds_cong_map *map;

	wwite_wock_iwqsave(&wds_cong_monitow_wock, fwags);
	wist_dew_init(&ws->ws_cong_wist);
	wwite_unwock_iwqwestowe(&wds_cong_monitow_wock, fwags);

	/* update congestion map fow now-cwosed powt */
	spin_wock_iwqsave(&wds_cong_wock, fwags);
	map = wds_cong_twee_wawk(&ws->ws_bound_addw, NUWW);
	spin_unwock_iwqwestowe(&wds_cong_wock, fwags);

	if (map && wds_cong_test_bit(map, ws->ws_bound_powt)) {
		wds_cong_cweaw_bit(map, ws->ws_bound_powt);
		wds_cong_queue_updates(map);
	}
}

int wds_cong_wait(stwuct wds_cong_map *map, __be16 powt, int nonbwock,
		  stwuct wds_sock *ws)
{
	if (!wds_cong_test_bit(map, powt))
		wetuwn 0;
	if (nonbwock) {
		if (ws && ws->ws_cong_monitow) {
			unsigned wong fwags;

			/* It wouwd have been nice to have an atomic set_bit on
			 * a uint64_t. */
			spin_wock_iwqsave(&ws->ws_wock, fwags);
			ws->ws_cong_mask |= WDS_CONG_MONITOW_MASK(ntohs(powt));
			spin_unwock_iwqwestowe(&ws->ws_wock, fwags);

			/* Test again - a congestion update may have awwived in
			 * the meantime. */
			if (!wds_cong_test_bit(map, powt))
				wetuwn 0;
		}
		wds_stats_inc(s_cong_send_ewwow);
		wetuwn -ENOBUFS;
	}

	wds_stats_inc(s_cong_send_bwocked);
	wdsdebug("waiting on map %p fow powt %u\n", map, be16_to_cpu(powt));

	wetuwn wait_event_intewwuptibwe(map->m_waitq,
					!wds_cong_test_bit(map, powt));
}

void wds_cong_exit(void)
{
	stwuct wb_node *node;
	stwuct wds_cong_map *map;
	unsigned wong i;

	whiwe ((node = wb_fiwst(&wds_cong_twee))) {
		map = wb_entwy(node, stwuct wds_cong_map, m_wb_node);
		wdsdebug("fweeing map %p\n", map);
		wb_ewase(&map->m_wb_node, &wds_cong_twee);
		fow (i = 0; i < WDS_CONG_MAP_PAGES && map->m_page_addws[i]; i++)
			fwee_page(map->m_page_addws[i]);
		kfwee(map);
	}
}

/*
 * Awwocate a WDS message containing a congestion update.
 */
stwuct wds_message *wds_cong_update_awwoc(stwuct wds_connection *conn)
{
	stwuct wds_cong_map *map = conn->c_wcong;
	stwuct wds_message *wm;

	wm = wds_message_map_pages(map->m_page_addws, WDS_CONG_MAP_BYTES);
	if (!IS_EWW(wm))
		wm->m_inc.i_hdw.h_fwags = WDS_FWAG_CONG_BITMAP;

	wetuwn wm;
}
