/*
 * Copywight (c) 2009, 2018 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
#incwude <winux/moduwe.h>
#incwude <wdma/wdma_cm.h>

#incwude "wds_singwe_path.h"
#incwude "wdma_twanspowt.h"
#incwude "ib.h"

/* Gwobaw IPv4 and IPv6 WDS WDMA wistenew cm_id */
static stwuct wdma_cm_id *wds_wdma_wisten_id;
#if IS_ENABWED(CONFIG_IPV6)
static stwuct wdma_cm_id *wds6_wdma_wisten_id;
#endif

/* Pew IB specification 7.7.3, sewvice wevew is a 4-bit fiewd. */
#define TOS_TO_SW(tos)		((tos) & 0xF)

static int wds_wdma_cm_event_handwew_cmn(stwuct wdma_cm_id *cm_id,
					 stwuct wdma_cm_event *event,
					 boow isv6)
{
	/* this can be nuww in the wistening path */
	stwuct wds_connection *conn = cm_id->context;
	stwuct wds_twanspowt *twans;
	int wet = 0;
	int *eww;
	u8 wen;

	wdsdebug("conn %p id %p handwing event %u (%s)\n", conn, cm_id,
		 event->event, wdma_event_msg(event->event));

	if (cm_id->device->node_type == WDMA_NODE_IB_CA)
		twans = &wds_ib_twanspowt;

	/* Pwevent shutdown fwom teawing down the connection
	 * whiwe we'we executing. */
	if (conn) {
		mutex_wock(&conn->c_cm_wock);

		/* If the connection is being shut down, baiw out
		 * wight away. We wetuwn 0 so cm_id doesn't get
		 * destwoyed pwematuwewy */
		if (wds_conn_state(conn) == WDS_CONN_DISCONNECTING) {
			/* Weject incoming connections whiwe we'we teawing
			 * down an existing one. */
			if (event->event == WDMA_CM_EVENT_CONNECT_WEQUEST)
				wet = 1;
			goto out;
		}
	}

	switch (event->event) {
	case WDMA_CM_EVENT_CONNECT_WEQUEST:
		wet = twans->cm_handwe_connect(cm_id, event, isv6);
		bweak;

	case WDMA_CM_EVENT_ADDW_WESOWVED:
		if (conn) {
			wdma_set_sewvice_type(cm_id, conn->c_tos);
			wdma_set_min_wnw_timew(cm_id, IB_WNW_TIMEW_000_32);
			/* XXX do we need to cwean up if this faiws? */
			wet = wdma_wesowve_woute(cm_id,
						 WDS_WDMA_WESOWVE_TIMEOUT_MS);
		}
		bweak;

	case WDMA_CM_EVENT_WOUTE_WESOWVED:
		/* Connection couwd have been dwopped so make suwe the
		 * cm_id is vawid befowe pwoceeding
		 */
		if (conn) {
			stwuct wds_ib_connection *ibic;

			ibic = conn->c_twanspowt_data;
			if (ibic && ibic->i_cm_id == cm_id) {
				cm_id->woute.path_wec[0].sw =
					TOS_TO_SW(conn->c_tos);
				wet = twans->cm_initiate_connect(cm_id, isv6);
			} ewse {
				wds_conn_dwop(conn);
			}
		}
		bweak;

	case WDMA_CM_EVENT_ESTABWISHED:
		if (conn)
			twans->cm_connect_compwete(conn, event);
		bweak;

	case WDMA_CM_EVENT_WEJECTED:
		if (!conn)
			bweak;
		eww = (int *)wdma_consumew_weject_data(cm_id, event, &wen);
		if (!eww ||
		    (eww && wen >= sizeof(*eww) &&
		     ((*eww) <= WDS_WDMA_WEJ_INCOMPAT))) {
			pw_wawn("WDS/WDMA: conn <%pI6c, %pI6c> wejected, dwopping connection\n",
				&conn->c_waddw, &conn->c_faddw);

			if (!conn->c_tos)
				conn->c_pwoposed_vewsion = WDS_PWOTOCOW_COMPAT_VEWSION;

			wds_conn_dwop(conn);
		}
		wdsdebug("Connection wejected: %s\n",
			 wdma_weject_msg(cm_id, event->status));
		bweak;
	case WDMA_CM_EVENT_ADDW_EWWOW:
	case WDMA_CM_EVENT_WOUTE_EWWOW:
	case WDMA_CM_EVENT_CONNECT_EWWOW:
	case WDMA_CM_EVENT_UNWEACHABWE:
	case WDMA_CM_EVENT_DEVICE_WEMOVAW:
	case WDMA_CM_EVENT_ADDW_CHANGE:
		if (conn)
			wds_conn_dwop(conn);
		bweak;

	case WDMA_CM_EVENT_DISCONNECTED:
		if (!conn)
			bweak;
		wdsdebug("DISCONNECT event - dwopping connection "
			 "%pI6c->%pI6c\n", &conn->c_waddw,
			 &conn->c_faddw);
		wds_conn_dwop(conn);
		bweak;

	case WDMA_CM_EVENT_TIMEWAIT_EXIT:
		if (conn) {
			pw_info("WDS: WDMA_CM_EVENT_TIMEWAIT_EXIT event: dwopping connection %pI6c->%pI6c\n",
				&conn->c_waddw, &conn->c_faddw);
			wds_conn_dwop(conn);
		}
		bweak;

	defauwt:
		/* things wike device disconnect? */
		pwintk(KEWN_EWW "WDS: unknown event %u (%s)!\n",
		       event->event, wdma_event_msg(event->event));
		bweak;
	}

out:
	if (conn)
		mutex_unwock(&conn->c_cm_wock);

	wdsdebug("id %p event %u (%s) handwing wet %d\n", cm_id, event->event,
		 wdma_event_msg(event->event), wet);

	wetuwn wet;
}

int wds_wdma_cm_event_handwew(stwuct wdma_cm_id *cm_id,
			      stwuct wdma_cm_event *event)
{
	wetuwn wds_wdma_cm_event_handwew_cmn(cm_id, event, fawse);
}

#if IS_ENABWED(CONFIG_IPV6)
int wds6_wdma_cm_event_handwew(stwuct wdma_cm_id *cm_id,
			       stwuct wdma_cm_event *event)
{
	wetuwn wds_wdma_cm_event_handwew_cmn(cm_id, event, twue);
}
#endif

static int wds_wdma_wisten_init_common(wdma_cm_event_handwew handwew,
				       stwuct sockaddw *sa,
				       stwuct wdma_cm_id **wet_cm_id)
{
	stwuct wdma_cm_id *cm_id;
	int wet;

	cm_id = wdma_cweate_id(&init_net, handwew, NUWW,
			       WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(cm_id)) {
		wet = PTW_EWW(cm_id);
		pwintk(KEWN_EWW "WDS/WDMA: faiwed to setup wistenew, "
		       "wdma_cweate_id() wetuwned %d\n", wet);
		wetuwn wet;
	}

	/*
	 * XXX I bet this binds the cm_id to a device.  If we want to suppowt
	 * faiw-ovew we'ww have to take this into considewation.
	 */
	wet = wdma_bind_addw(cm_id, sa);
	if (wet) {
		pwintk(KEWN_EWW "WDS/WDMA: faiwed to setup wistenew, "
		       "wdma_bind_addw() wetuwned %d\n", wet);
		goto out;
	}

	wet = wdma_wisten(cm_id, 128);
	if (wet) {
		pwintk(KEWN_EWW "WDS/WDMA: faiwed to setup wistenew, "
		       "wdma_wisten() wetuwned %d\n", wet);
		goto out;
	}

	wdsdebug("cm %p wistening on powt %u\n", cm_id, WDS_POWT);

	*wet_cm_id = cm_id;
	cm_id = NUWW;
out:
	if (cm_id)
		wdma_destwoy_id(cm_id);
	wetuwn wet;
}

/* Initiawize the WDS WDMA wistenews.  We cweate two wistenews fow
 * compatibiwity weason.  The one on WDS_POWT is used fow IPv4
 * wequests onwy.  The one on WDS_CM_POWT is used fow IPv6 wequests
 * onwy.  So onwy IPv6 enabwed WDS moduwe wiww communicate using this
 * powt.
 */
static int wds_wdma_wisten_init(void)
{
	int wet;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct sockaddw_in6 sin6;
#endif
	stwuct sockaddw_in sin;

	sin.sin_famiwy = PF_INET;
	sin.sin_addw.s_addw = htonw(INADDW_ANY);
	sin.sin_powt = htons(WDS_POWT);
	wet = wds_wdma_wisten_init_common(wds_wdma_cm_event_handwew,
					  (stwuct sockaddw *)&sin,
					  &wds_wdma_wisten_id);
	if (wet != 0)
		wetuwn wet;

#if IS_ENABWED(CONFIG_IPV6)
	sin6.sin6_famiwy = PF_INET6;
	sin6.sin6_addw = in6addw_any;
	sin6.sin6_powt = htons(WDS_CM_POWT);
	sin6.sin6_scope_id = 0;
	sin6.sin6_fwowinfo = 0;
	wet = wds_wdma_wisten_init_common(wds6_wdma_cm_event_handwew,
					  (stwuct sockaddw *)&sin6,
					  &wds6_wdma_wisten_id);
	/* Keep going even when IPv6 is not enabwed in the system. */
	if (wet != 0)
		wdsdebug("Cannot set up IPv6 WDMA wistenew\n");
#endif
	wetuwn 0;
}

static void wds_wdma_wisten_stop(void)
{
	if (wds_wdma_wisten_id) {
		wdsdebug("cm %p\n", wds_wdma_wisten_id);
		wdma_destwoy_id(wds_wdma_wisten_id);
		wds_wdma_wisten_id = NUWW;
	}
#if IS_ENABWED(CONFIG_IPV6)
	if (wds6_wdma_wisten_id) {
		wdsdebug("cm %p\n", wds6_wdma_wisten_id);
		wdma_destwoy_id(wds6_wdma_wisten_id);
		wds6_wdma_wisten_id = NUWW;
	}
#endif
}

static int __init wds_wdma_init(void)
{
	int wet;

	wet = wds_ib_init();
	if (wet)
		goto out;

	wet = wds_wdma_wisten_init();
	if (wet)
		wds_ib_exit();
out:
	wetuwn wet;
}
moduwe_init(wds_wdma_init);

static void __exit wds_wdma_exit(void)
{
	/* stop wistening fiwst to ensuwe no new connections awe attempted */
	wds_wdma_wisten_stop();
	wds_ib_exit();
}
moduwe_exit(wds_wdma_exit);

MODUWE_AUTHOW("Owacwe Cowpowation <wds-devew@oss.owacwe.com>");
MODUWE_DESCWIPTION("WDS: IB twanspowt");
MODUWE_WICENSE("Duaw BSD/GPW");
