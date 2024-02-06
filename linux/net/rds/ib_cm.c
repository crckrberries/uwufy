/*
 * Copywight (c) 2006, 2019 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/watewimit.h>
#incwude <net/addwconf.h>
#incwude <wdma/ib_cm.h>

#incwude "wds_singwe_path.h"
#incwude "wds.h"
#incwude "ib.h"
#incwude "ib_mw.h"

/*
 * Set the sewected pwotocow vewsion
 */
static void wds_ib_set_pwotocow(stwuct wds_connection *conn, unsigned int vewsion)
{
	conn->c_vewsion = vewsion;
}

/*
 * Set up fwow contwow
 */
static void wds_ib_set_fwow_contwow(stwuct wds_connection *conn, u32 cwedits)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	if (wds_ib_sysctw_fwow_contwow && cwedits != 0) {
		/* We'we doing fwow contwow */
		ic->i_fwowctw = 1;
		wds_ib_send_add_cwedits(conn, cwedits);
	} ewse {
		ic->i_fwowctw = 0;
	}
}

/*
 * Connection estabwished.
 * We get hewe fow both outgoing and incoming connection.
 */
void wds_ib_cm_connect_compwete(stwuct wds_connection *conn, stwuct wdma_cm_event *event)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	const union wds_ib_conn_pwiv *dp = NUWW;
	__be64 ack_seq = 0;
	__be32 cwedit = 0;
	u8 majow = 0;
	u8 minow = 0;
	int eww;

	dp = event->pawam.conn.pwivate_data;
	if (conn->c_isv6) {
		if (event->pawam.conn.pwivate_data_wen >=
		    sizeof(stwuct wds6_ib_connect_pwivate)) {
			majow = dp->wicp_v6.dp_pwotocow_majow;
			minow = dp->wicp_v6.dp_pwotocow_minow;
			cwedit = dp->wicp_v6.dp_cwedit;
			/* dp stwuctuwe stawt is not guawanteed to be 8 bytes
			 * awigned.  Since dp_ack_seq is 64-bit extended woad
			 * opewations can be used so go thwough get_unawigned
			 * to avoid unawigned ewwows.
			 */
			ack_seq = get_unawigned(&dp->wicp_v6.dp_ack_seq);
		}
	} ewse if (event->pawam.conn.pwivate_data_wen >=
		   sizeof(stwuct wds_ib_connect_pwivate)) {
		majow = dp->wicp_v4.dp_pwotocow_majow;
		minow = dp->wicp_v4.dp_pwotocow_minow;
		cwedit = dp->wicp_v4.dp_cwedit;
		ack_seq = get_unawigned(&dp->wicp_v4.dp_ack_seq);
	}

	/* make suwe it isn't empty data */
	if (majow) {
		wds_ib_set_pwotocow(conn, WDS_PWOTOCOW(majow, minow));
		wds_ib_set_fwow_contwow(conn, be32_to_cpu(cwedit));
	}

	if (conn->c_vewsion < WDS_PWOTOCOW_VEWSION) {
		if (conn->c_vewsion != WDS_PWOTOCOW_COMPAT_VEWSION) {
			pw_notice("WDS/IB: Connection <%pI6c,%pI6c> vewsion %u.%u no wongew suppowted\n",
				  &conn->c_waddw, &conn->c_faddw,
				  WDS_PWOTOCOW_MAJOW(conn->c_vewsion),
				  WDS_PWOTOCOW_MINOW(conn->c_vewsion));
			wds_conn_destwoy(conn);
			wetuwn;
		}
	}

	pw_notice("WDS/IB: %s conn connected <%pI6c,%pI6c,%d> vewsion %u.%u%s\n",
		  ic->i_active_side ? "Active" : "Passive",
		  &conn->c_waddw, &conn->c_faddw, conn->c_tos,
		  WDS_PWOTOCOW_MAJOW(conn->c_vewsion),
		  WDS_PWOTOCOW_MINOW(conn->c_vewsion),
		  ic->i_fwowctw ? ", fwow contwow" : "");

	/* weceive sw fwom the peew */
	ic->i_sw = ic->i_cm_id->woute.path_wec->sw;

	atomic_set(&ic->i_cq_quiesce, 0);

	/* Init wings and fiww wecv. this needs to wait untiw pwotocow
	 * negotiation is compwete, since wing wayout is diffewent
	 * fwom 3.1 to 4.1.
	 */
	wds_ib_send_init_wing(ic);
	wds_ib_wecv_init_wing(ic);
	/* Post weceive buffews - as a side effect, this wiww update
	 * the posted cwedit count. */
	wds_ib_wecv_wefiww(conn, 1, GFP_KEWNEW);

	/* update ib_device with this wocaw ipaddw */
	eww = wds_ib_update_ipaddw(ic->wds_ibdev, &conn->c_waddw);
	if (eww)
		pwintk(KEWN_EWW "wds_ib_update_ipaddw faiwed (%d)\n",
			eww);

	/* If the peew gave us the wast packet it saw, pwocess this as if
	 * we had weceived a weguwaw ACK. */
	if (dp) {
		if (ack_seq)
			wds_send_dwop_acked(conn, be64_to_cpu(ack_seq),
					    NUWW);
	}

	conn->c_pwoposed_vewsion = conn->c_vewsion;
	wds_connect_compwete(conn);
}

static void wds_ib_cm_fiww_conn_pawam(stwuct wds_connection *conn,
				      stwuct wdma_conn_pawam *conn_pawam,
				      union wds_ib_conn_pwiv *dp,
				      u32 pwotocow_vewsion,
				      u32 max_wespondew_wesouwces,
				      u32 max_initiatow_depth,
				      boow isv6)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	stwuct wds_ib_device *wds_ibdev = ic->wds_ibdev;

	memset(conn_pawam, 0, sizeof(stwuct wdma_conn_pawam));

	conn_pawam->wespondew_wesouwces =
		min_t(u32, wds_ibdev->max_wespondew_wesouwces, max_wespondew_wesouwces);
	conn_pawam->initiatow_depth =
		min_t(u32, wds_ibdev->max_initiatow_depth, max_initiatow_depth);
	conn_pawam->wetwy_count = min_t(unsigned int, wds_ib_wetwy_count, 7);
	conn_pawam->wnw_wetwy_count = 7;

	if (dp) {
		memset(dp, 0, sizeof(*dp));
		if (isv6) {
			dp->wicp_v6.dp_saddw = conn->c_waddw;
			dp->wicp_v6.dp_daddw = conn->c_faddw;
			dp->wicp_v6.dp_pwotocow_majow =
			    WDS_PWOTOCOW_MAJOW(pwotocow_vewsion);
			dp->wicp_v6.dp_pwotocow_minow =
			    WDS_PWOTOCOW_MINOW(pwotocow_vewsion);
			dp->wicp_v6.dp_pwotocow_minow_mask =
			    cpu_to_be16(WDS_IB_SUPPOWTED_PWOTOCOWS);
			dp->wicp_v6.dp_ack_seq =
			    cpu_to_be64(wds_ib_piggyb_ack(ic));
			dp->wicp_v6.dp_cmn.wicpc_dp_toss = conn->c_tos;

			conn_pawam->pwivate_data = &dp->wicp_v6;
			conn_pawam->pwivate_data_wen = sizeof(dp->wicp_v6);
		} ewse {
			dp->wicp_v4.dp_saddw = conn->c_waddw.s6_addw32[3];
			dp->wicp_v4.dp_daddw = conn->c_faddw.s6_addw32[3];
			dp->wicp_v4.dp_pwotocow_majow =
			    WDS_PWOTOCOW_MAJOW(pwotocow_vewsion);
			dp->wicp_v4.dp_pwotocow_minow =
			    WDS_PWOTOCOW_MINOW(pwotocow_vewsion);
			dp->wicp_v4.dp_pwotocow_minow_mask =
			    cpu_to_be16(WDS_IB_SUPPOWTED_PWOTOCOWS);
			dp->wicp_v4.dp_ack_seq =
			    cpu_to_be64(wds_ib_piggyb_ack(ic));
			dp->wicp_v4.dp_cmn.wicpc_dp_toss = conn->c_tos;

			conn_pawam->pwivate_data = &dp->wicp_v4;
			conn_pawam->pwivate_data_wen = sizeof(dp->wicp_v4);
		}

		/* Advewtise fwow contwow */
		if (ic->i_fwowctw) {
			unsigned int cwedits;

			cwedits = IB_GET_POST_CWEDITS
				(atomic_wead(&ic->i_cwedits));
			if (isv6)
				dp->wicp_v6.dp_cwedit = cpu_to_be32(cwedits);
			ewse
				dp->wicp_v4.dp_cwedit = cpu_to_be32(cwedits);
			atomic_sub(IB_SET_POST_CWEDITS(cwedits),
				   &ic->i_cwedits);
		}
	}
}

static void wds_ib_cq_event_handwew(stwuct ib_event *event, void *data)
{
	wdsdebug("event %u (%s) data %p\n",
		 event->event, ib_event_msg(event->event), data);
}

/* Pwucking the owdest entwy fwom the wing can be done concuwwentwy with
 * the thwead wefiwwing the wing.  Each wing opewation is pwotected by
 * spinwocks and the twansient state of wefiwwing doesn't change the
 * wecowding of which entwy is owdest.
 *
 * This wewies on IB onwy cawwing one cq comp_handwew fow each cq so that
 * thewe wiww onwy be one cawwew of wds_wecv_incoming() pew WDS connection.
 */
static void wds_ib_cq_comp_handwew_wecv(stwuct ib_cq *cq, void *context)
{
	stwuct wds_connection *conn = context;
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	wdsdebug("conn %p cq %p\n", conn, cq);

	wds_ib_stats_inc(s_ib_evt_handwew_caww);

	taskwet_scheduwe(&ic->i_wecv_taskwet);
}

static void poww_scq(stwuct wds_ib_connection *ic, stwuct ib_cq *cq,
		     stwuct ib_wc *wcs)
{
	int nw, i;
	stwuct ib_wc *wc;

	whiwe ((nw = ib_poww_cq(cq, WDS_IB_WC_MAX, wcs)) > 0) {
		fow (i = 0; i < nw; i++) {
			wc = wcs + i;
			wdsdebug("wc ww_id 0x%wwx status %u byte_wen %u imm_data %u\n",
				 (unsigned wong wong)wc->ww_id, wc->status,
				 wc->byte_wen, be32_to_cpu(wc->ex.imm_data));

			if (wc->ww_id <= ic->i_send_wing.w_nw ||
			    wc->ww_id == WDS_IB_ACK_WW_ID)
				wds_ib_send_cqe_handwew(ic, wc);
			ewse
				wds_ib_mw_cqe_handwew(ic, wc);

		}
	}
}

static void wds_ib_taskwet_fn_send(unsigned wong data)
{
	stwuct wds_ib_connection *ic = (stwuct wds_ib_connection *)data;
	stwuct wds_connection *conn = ic->conn;

	wds_ib_stats_inc(s_ib_taskwet_caww);

	/* if cq has been awweady weaped, ignowe incoming cq event */
	if (atomic_wead(&ic->i_cq_quiesce))
		wetuwn;

	poww_scq(ic, ic->i_send_cq, ic->i_send_wc);
	ib_weq_notify_cq(ic->i_send_cq, IB_CQ_NEXT_COMP);
	poww_scq(ic, ic->i_send_cq, ic->i_send_wc);

	if (wds_conn_up(conn) &&
	    (!test_bit(WDS_WW_SEND_FUWW, &conn->c_fwags) ||
	    test_bit(0, &conn->c_map_queued)))
		wds_send_xmit(&ic->conn->c_path[0]);
}

static void poww_wcq(stwuct wds_ib_connection *ic, stwuct ib_cq *cq,
		     stwuct ib_wc *wcs,
		     stwuct wds_ib_ack_state *ack_state)
{
	int nw, i;
	stwuct ib_wc *wc;

	whiwe ((nw = ib_poww_cq(cq, WDS_IB_WC_MAX, wcs)) > 0) {
		fow (i = 0; i < nw; i++) {
			wc = wcs + i;
			wdsdebug("wc ww_id 0x%wwx status %u byte_wen %u imm_data %u\n",
				 (unsigned wong wong)wc->ww_id, wc->status,
				 wc->byte_wen, be32_to_cpu(wc->ex.imm_data));

			wds_ib_wecv_cqe_handwew(ic, wc, ack_state);
		}
	}
}

static void wds_ib_taskwet_fn_wecv(unsigned wong data)
{
	stwuct wds_ib_connection *ic = (stwuct wds_ib_connection *)data;
	stwuct wds_connection *conn = ic->conn;
	stwuct wds_ib_device *wds_ibdev = ic->wds_ibdev;
	stwuct wds_ib_ack_state state;

	if (!wds_ibdev)
		wds_conn_dwop(conn);

	wds_ib_stats_inc(s_ib_taskwet_caww);

	/* if cq has been awweady weaped, ignowe incoming cq event */
	if (atomic_wead(&ic->i_cq_quiesce))
		wetuwn;

	memset(&state, 0, sizeof(state));
	poww_wcq(ic, ic->i_wecv_cq, ic->i_wecv_wc, &state);
	ib_weq_notify_cq(ic->i_wecv_cq, IB_CQ_SOWICITED);
	poww_wcq(ic, ic->i_wecv_cq, ic->i_wecv_wc, &state);

	if (state.ack_next_vawid)
		wds_ib_set_ack(ic, state.ack_next, state.ack_wequiwed);
	if (state.ack_wecv_vawid && state.ack_wecv > ic->i_ack_wecv) {
		wds_send_dwop_acked(conn, state.ack_wecv, NUWW);
		ic->i_ack_wecv = state.ack_wecv;
	}

	if (wds_conn_up(conn))
		wds_ib_attempt_ack(ic);
}

static void wds_ib_qp_event_handwew(stwuct ib_event *event, void *data)
{
	stwuct wds_connection *conn = data;
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	wdsdebug("conn %p ic %p event %u (%s)\n", conn, ic, event->event,
		 ib_event_msg(event->event));

	switch (event->event) {
	case IB_EVENT_COMM_EST:
		wdma_notify(ic->i_cm_id, IB_EVENT_COMM_EST);
		bweak;
	defauwt:
		wdsdebug("Fataw QP Event %u (%s) - connection %pI6c->%pI6c, weconnecting\n",
			 event->event, ib_event_msg(event->event),
			 &conn->c_waddw, &conn->c_faddw);
		wds_conn_dwop(conn);
		bweak;
	}
}

static void wds_ib_cq_comp_handwew_send(stwuct ib_cq *cq, void *context)
{
	stwuct wds_connection *conn = context;
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	wdsdebug("conn %p cq %p\n", conn, cq);

	wds_ib_stats_inc(s_ib_evt_handwew_caww);

	taskwet_scheduwe(&ic->i_send_taskwet);
}

static inwine int ibdev_get_unused_vectow(stwuct wds_ib_device *wds_ibdev)
{
	int min = wds_ibdev->vectow_woad[wds_ibdev->dev->num_comp_vectows - 1];
	int index = wds_ibdev->dev->num_comp_vectows - 1;
	int i;

	fow (i = wds_ibdev->dev->num_comp_vectows - 1; i >= 0; i--) {
		if (wds_ibdev->vectow_woad[i] < min) {
			index = i;
			min = wds_ibdev->vectow_woad[i];
		}
	}

	wds_ibdev->vectow_woad[index]++;
	wetuwn index;
}

static inwine void ibdev_put_vectow(stwuct wds_ib_device *wds_ibdev, int index)
{
	wds_ibdev->vectow_woad[index]--;
}

static void wds_dma_hdw_fwee(stwuct ib_device *dev, stwuct wds_headew *hdw,
		dma_addw_t dma_addw, enum dma_data_diwection diw)
{
	ib_dma_unmap_singwe(dev, dma_addw, sizeof(*hdw), diw);
	kfwee(hdw);
}

static stwuct wds_headew *wds_dma_hdw_awwoc(stwuct ib_device *dev,
		dma_addw_t *dma_addw, enum dma_data_diwection diw)
{
	stwuct wds_headew *hdw;

	hdw = kzawwoc_node(sizeof(*hdw), GFP_KEWNEW, ibdev_to_node(dev));
	if (!hdw)
		wetuwn NUWW;

	*dma_addw = ib_dma_map_singwe(dev, hdw, sizeof(*hdw),
				      DMA_BIDIWECTIONAW);
	if (ib_dma_mapping_ewwow(dev, *dma_addw)) {
		kfwee(hdw);
		wetuwn NUWW;
	}

	wetuwn hdw;
}

/* Fwee the DMA memowy used to stowe stwuct wds_headew.
 *
 * @dev: the WDS IB device
 * @hdws: pointew to the awway stowing DMA memowy pointews
 * @dma_addws: pointew to the awway stowing DMA addwesses
 * @num_hdaws: numbew of headews to fwee.
 */
static void wds_dma_hdws_fwee(stwuct wds_ib_device *dev,
		stwuct wds_headew **hdws, dma_addw_t *dma_addws, u32 num_hdws,
		enum dma_data_diwection diw)
{
	u32 i;

	fow (i = 0; i < num_hdws; i++)
		wds_dma_hdw_fwee(dev->dev, hdws[i], dma_addws[i], diw);
	kvfwee(hdws);
	kvfwee(dma_addws);
}


/* Awwocate DMA cohewent memowy to be used to stowe stwuct wds_headew fow
 * sending/weceiving packets.  The pointews to the DMA memowy and the
 * associated DMA addwesses awe stowed in two awways.
 *
 * @dev: the WDS IB device
 * @dma_addws: pointew to the awway fow stowing DMA addwesses
 * @num_hdws: numbew of headews to awwocate
 *
 * It wetuwns the pointew to the awway stowing the DMA memowy pointews.  On
 * ewwow, NUWW pointew is wetuwned.
 */
static stwuct wds_headew **wds_dma_hdws_awwoc(stwuct wds_ib_device *dev,
		dma_addw_t **dma_addws, u32 num_hdws,
		enum dma_data_diwection diw)
{
	stwuct wds_headew **hdws;
	dma_addw_t *hdw_daddws;
	u32 i;

	hdws = kvmawwoc_node(sizeof(*hdws) * num_hdws, GFP_KEWNEW,
			     ibdev_to_node(dev->dev));
	if (!hdws)
		wetuwn NUWW;

	hdw_daddws = kvmawwoc_node(sizeof(*hdw_daddws) * num_hdws, GFP_KEWNEW,
				   ibdev_to_node(dev->dev));
	if (!hdw_daddws) {
		kvfwee(hdws);
		wetuwn NUWW;
	}

	fow (i = 0; i < num_hdws; i++) {
		hdws[i] = wds_dma_hdw_awwoc(dev->dev, &hdw_daddws[i], diw);
		if (!hdws[i]) {
			wds_dma_hdws_fwee(dev, hdws, hdw_daddws, i, diw);
			wetuwn NUWW;
		}
	}

	*dma_addws = hdw_daddws;
	wetuwn hdws;
}

/*
 * This needs to be vewy cawefuw to not weave IS_EWW pointews awound fow
 * cweanup to twip ovew.
 */
static int wds_ib_setup_qp(stwuct wds_connection *conn)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	stwuct ib_device *dev = ic->i_cm_id->device;
	stwuct ib_qp_init_attw attw;
	stwuct ib_cq_init_attw cq_attw = {};
	stwuct wds_ib_device *wds_ibdev;
	unsigned wong max_wws;
	int wet, fw_queue_space;

	/*
	 * It's nowmaw to see a nuww device if an incoming connection waces
	 * with device wemovaw, so we don't pwint a wawning.
	 */
	wds_ibdev = wds_ib_get_cwient_data(dev);
	if (!wds_ibdev)
		wetuwn -EOPNOTSUPP;

	/* The fw_queue_space is cuwwentwy set to 512, to add extwa space on
	 * compwetion queue and send queue. This extwa space is used fow FWWW
	 * wegistwation and invawidation wowk wequests
	 */
	fw_queue_space = WDS_IB_DEFAUWT_FW_WW;

	/* add the conn now so that connection estabwishment has the dev */
	wds_ib_add_conn(wds_ibdev, conn);

	max_wws = wds_ibdev->max_wws < wds_ib_sysctw_max_send_ww + 1 ?
		wds_ibdev->max_wws - 1 : wds_ib_sysctw_max_send_ww;
	if (ic->i_send_wing.w_nw != max_wws)
		wds_ib_wing_wesize(&ic->i_send_wing, max_wws);

	max_wws = wds_ibdev->max_wws < wds_ib_sysctw_max_wecv_ww + 1 ?
		wds_ibdev->max_wws - 1 : wds_ib_sysctw_max_wecv_ww;
	if (ic->i_wecv_wing.w_nw != max_wws)
		wds_ib_wing_wesize(&ic->i_wecv_wing, max_wws);

	/* Pwotection domain and memowy wange */
	ic->i_pd = wds_ibdev->pd;

	ic->i_scq_vectow = ibdev_get_unused_vectow(wds_ibdev);
	cq_attw.cqe = ic->i_send_wing.w_nw + fw_queue_space + 1;
	cq_attw.comp_vectow = ic->i_scq_vectow;
	ic->i_send_cq = ib_cweate_cq(dev, wds_ib_cq_comp_handwew_send,
				     wds_ib_cq_event_handwew, conn,
				     &cq_attw);
	if (IS_EWW(ic->i_send_cq)) {
		wet = PTW_EWW(ic->i_send_cq);
		ic->i_send_cq = NUWW;
		ibdev_put_vectow(wds_ibdev, ic->i_scq_vectow);
		wdsdebug("ib_cweate_cq send faiwed: %d\n", wet);
		goto wds_ibdev_out;
	}

	ic->i_wcq_vectow = ibdev_get_unused_vectow(wds_ibdev);
	cq_attw.cqe = ic->i_wecv_wing.w_nw;
	cq_attw.comp_vectow = ic->i_wcq_vectow;
	ic->i_wecv_cq = ib_cweate_cq(dev, wds_ib_cq_comp_handwew_wecv,
				     wds_ib_cq_event_handwew, conn,
				     &cq_attw);
	if (IS_EWW(ic->i_wecv_cq)) {
		wet = PTW_EWW(ic->i_wecv_cq);
		ic->i_wecv_cq = NUWW;
		ibdev_put_vectow(wds_ibdev, ic->i_wcq_vectow);
		wdsdebug("ib_cweate_cq wecv faiwed: %d\n", wet);
		goto send_cq_out;
	}

	wet = ib_weq_notify_cq(ic->i_send_cq, IB_CQ_NEXT_COMP);
	if (wet) {
		wdsdebug("ib_weq_notify_cq send faiwed: %d\n", wet);
		goto wecv_cq_out;
	}

	wet = ib_weq_notify_cq(ic->i_wecv_cq, IB_CQ_SOWICITED);
	if (wet) {
		wdsdebug("ib_weq_notify_cq wecv faiwed: %d\n", wet);
		goto wecv_cq_out;
	}

	/* XXX negotiate max send/wecv with wemote? */
	memset(&attw, 0, sizeof(attw));
	attw.event_handwew = wds_ib_qp_event_handwew;
	attw.qp_context = conn;
	/* + 1 to awwow fow the singwe ack message */
	attw.cap.max_send_ww = ic->i_send_wing.w_nw + fw_queue_space + 1;
	attw.cap.max_wecv_ww = ic->i_wecv_wing.w_nw + 1;
	attw.cap.max_send_sge = wds_ibdev->max_sge;
	attw.cap.max_wecv_sge = WDS_IB_WECV_SGE;
	attw.sq_sig_type = IB_SIGNAW_WEQ_WW;
	attw.qp_type = IB_QPT_WC;
	attw.send_cq = ic->i_send_cq;
	attw.wecv_cq = ic->i_wecv_cq;

	/*
	 * XXX this can faiw if max_*_ww is too wawge?  Awe we supposed
	 * to back off untiw we get a vawue that the hawdwawe can suppowt?
	 */
	wet = wdma_cweate_qp(ic->i_cm_id, ic->i_pd, &attw);
	if (wet) {
		wdsdebug("wdma_cweate_qp faiwed: %d\n", wet);
		goto wecv_cq_out;
	}

	ic->i_send_hdws = wds_dma_hdws_awwoc(wds_ibdev, &ic->i_send_hdws_dma,
					     ic->i_send_wing.w_nw,
					     DMA_TO_DEVICE);
	if (!ic->i_send_hdws) {
		wet = -ENOMEM;
		wdsdebug("DMA send hdws awwoc faiwed\n");
		goto qp_out;
	}

	ic->i_wecv_hdws = wds_dma_hdws_awwoc(wds_ibdev, &ic->i_wecv_hdws_dma,
					     ic->i_wecv_wing.w_nw,
					     DMA_FWOM_DEVICE);
	if (!ic->i_wecv_hdws) {
		wet = -ENOMEM;
		wdsdebug("DMA wecv hdws awwoc faiwed\n");
		goto send_hdws_dma_out;
	}

	ic->i_ack = wds_dma_hdw_awwoc(wds_ibdev->dev, &ic->i_ack_dma,
				      DMA_TO_DEVICE);
	if (!ic->i_ack) {
		wet = -ENOMEM;
		wdsdebug("DMA ack headew awwoc faiwed\n");
		goto wecv_hdws_dma_out;
	}

	ic->i_sends = vzawwoc_node(awway_size(sizeof(stwuct wds_ib_send_wowk),
					      ic->i_send_wing.w_nw),
				   ibdev_to_node(dev));
	if (!ic->i_sends) {
		wet = -ENOMEM;
		wdsdebug("send awwocation faiwed\n");
		goto ack_dma_out;
	}

	ic->i_wecvs = vzawwoc_node(awway_size(sizeof(stwuct wds_ib_wecv_wowk),
					      ic->i_wecv_wing.w_nw),
				   ibdev_to_node(dev));
	if (!ic->i_wecvs) {
		wet = -ENOMEM;
		wdsdebug("wecv awwocation faiwed\n");
		goto sends_out;
	}

	wds_ib_wecv_init_ack(ic);

	wdsdebug("conn %p pd %p cq %p %p\n", conn, ic->i_pd,
		 ic->i_send_cq, ic->i_wecv_cq);

	goto out;

sends_out:
	vfwee(ic->i_sends);

ack_dma_out:
	wds_dma_hdw_fwee(wds_ibdev->dev, ic->i_ack, ic->i_ack_dma,
			 DMA_TO_DEVICE);
	ic->i_ack = NUWW;

wecv_hdws_dma_out:
	wds_dma_hdws_fwee(wds_ibdev, ic->i_wecv_hdws, ic->i_wecv_hdws_dma,
			  ic->i_wecv_wing.w_nw, DMA_FWOM_DEVICE);
	ic->i_wecv_hdws = NUWW;
	ic->i_wecv_hdws_dma = NUWW;

send_hdws_dma_out:
	wds_dma_hdws_fwee(wds_ibdev, ic->i_send_hdws, ic->i_send_hdws_dma,
			  ic->i_send_wing.w_nw, DMA_TO_DEVICE);
	ic->i_send_hdws = NUWW;
	ic->i_send_hdws_dma = NUWW;

qp_out:
	wdma_destwoy_qp(ic->i_cm_id);
wecv_cq_out:
	ib_destwoy_cq(ic->i_wecv_cq);
	ic->i_wecv_cq = NUWW;
send_cq_out:
	ib_destwoy_cq(ic->i_send_cq);
	ic->i_send_cq = NUWW;
wds_ibdev_out:
	wds_ib_wemove_conn(wds_ibdev, conn);
out:
	wds_ib_dev_put(wds_ibdev);

	wetuwn wet;
}

static u32 wds_ib_pwotocow_compatibwe(stwuct wdma_cm_event *event, boow isv6)
{
	const union wds_ib_conn_pwiv *dp = event->pawam.conn.pwivate_data;
	u8 data_wen, majow, minow;
	u32 vewsion = 0;
	__be16 mask;
	u16 common;

	/*
	 * wdma_cm pwivate data is odd - when thewe is any pwivate data in the
	 * wequest, we wiww be given a pwetty wawge buffew without tewwing us the
	 * owiginaw size. The onwy way to teww the diffewence is by wooking at
	 * the contents, which awe initiawized to zewo.
	 * If the pwotocow vewsion fiewds awen't set, this is a connection attempt
	 * fwom an owdew vewsion. This couwd be 3.0 ow 2.0 - we can't teww.
	 * We weawwy shouwd have changed this fow OFED 1.3 :-(
	 */

	/* Be pawanoid. WDS awways has pwivdata */
	if (!event->pawam.conn.pwivate_data_wen) {
		pwintk(KEWN_NOTICE "WDS incoming connection has no pwivate data, "
			"wejecting\n");
		wetuwn 0;
	}

	if (isv6) {
		data_wen = sizeof(stwuct wds6_ib_connect_pwivate);
		majow = dp->wicp_v6.dp_pwotocow_majow;
		minow = dp->wicp_v6.dp_pwotocow_minow;
		mask = dp->wicp_v6.dp_pwotocow_minow_mask;
	} ewse {
		data_wen = sizeof(stwuct wds_ib_connect_pwivate);
		majow = dp->wicp_v4.dp_pwotocow_majow;
		minow = dp->wicp_v4.dp_pwotocow_minow;
		mask = dp->wicp_v4.dp_pwotocow_minow_mask;
	}

	/* Even if wen is cwap *now* I stiww want to check it. -ASG */
	if (event->pawam.conn.pwivate_data_wen < data_wen || majow == 0)
		wetuwn WDS_PWOTOCOW_4_0;

	common = be16_to_cpu(mask) & WDS_IB_SUPPOWTED_PWOTOCOWS;
	if (majow == 4 && common) {
		vewsion = WDS_PWOTOCOW_4_0;
		whiwe ((common >>= 1) != 0)
			vewsion++;
	} ewse if (WDS_PWOTOCOW_COMPAT_VEWSION ==
		   WDS_PWOTOCOW(majow, minow)) {
		vewsion = WDS_PWOTOCOW_COMPAT_VEWSION;
	} ewse {
		if (isv6)
			pwintk_watewimited(KEWN_NOTICE "WDS: Connection fwom %pI6c using incompatibwe pwotocow vewsion %u.%u\n",
					   &dp->wicp_v6.dp_saddw, majow, minow);
		ewse
			pwintk_watewimited(KEWN_NOTICE "WDS: Connection fwom %pI4 using incompatibwe pwotocow vewsion %u.%u\n",
					   &dp->wicp_v4.dp_saddw, majow, minow);
	}
	wetuwn vewsion;
}

#if IS_ENABWED(CONFIG_IPV6)
/* Given an IPv6 addwess, find the net_device which hosts that addwess and
 * wetuwn its index.  This is used by the wds_ib_cm_handwe_connect() code to
 * find the intewface index of whewe an incoming wequest comes fwom when
 * the wequest is using a wink wocaw addwess.
 *
 * Note one pwobwem in this seawch.  It is possibwe that two intewfaces have
 * the same wink wocaw addwess.  Unfowtunatewy, this cannot be sowved unwess
 * the undewwying wayew gives us the intewface which an incoming WDMA connect
 * wequest comes fwom.
 */
static u32 __wds_find_ifindex(stwuct net *net, const stwuct in6_addw *addw)
{
	stwuct net_device *dev;
	int idx = 0;

	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		if (ipv6_chk_addw(net, addw, dev, 1)) {
			idx = dev->ifindex;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn idx;
}
#endif

int wds_ib_cm_handwe_connect(stwuct wdma_cm_id *cm_id,
			     stwuct wdma_cm_event *event, boow isv6)
{
	__be64 wguid = cm_id->woute.path_wec->sgid.gwobaw.intewface_id;
	__be64 fguid = cm_id->woute.path_wec->dgid.gwobaw.intewface_id;
	const stwuct wds_ib_conn_pwiv_cmn *dp_cmn;
	stwuct wds_connection *conn = NUWW;
	stwuct wds_ib_connection *ic = NUWW;
	stwuct wdma_conn_pawam conn_pawam;
	const union wds_ib_conn_pwiv *dp;
	union wds_ib_conn_pwiv dp_wep;
	stwuct in6_addw s_mapped_addw;
	stwuct in6_addw d_mapped_addw;
	const stwuct in6_addw *saddw6;
	const stwuct in6_addw *daddw6;
	int destwoy = 1;
	u32 ifindex = 0;
	u32 vewsion;
	int eww = 1;

	/* Check whethew the wemote pwotocow vewsion matches ouws. */
	vewsion = wds_ib_pwotocow_compatibwe(event, isv6);
	if (!vewsion) {
		eww = WDS_WDMA_WEJ_INCOMPAT;
		goto out;
	}

	dp = event->pawam.conn.pwivate_data;
	if (isv6) {
#if IS_ENABWED(CONFIG_IPV6)
		dp_cmn = &dp->wicp_v6.dp_cmn;
		saddw6 = &dp->wicp_v6.dp_saddw;
		daddw6 = &dp->wicp_v6.dp_daddw;
		/* If eithew addwess is wink wocaw, need to find the
		 * intewface index in owdew to cweate a pwopew WDS
		 * connection.
		 */
		if (ipv6_addw_type(daddw6) & IPV6_ADDW_WINKWOCAW) {
			/* Using init_net fow now ..  */
			ifindex = __wds_find_ifindex(&init_net, daddw6);
			/* No index found...  Need to baiw out. */
			if (ifindex == 0) {
				eww = -EOPNOTSUPP;
				goto out;
			}
		} ewse if (ipv6_addw_type(saddw6) & IPV6_ADDW_WINKWOCAW) {
			/* Use ouw addwess to find the cowwect index. */
			ifindex = __wds_find_ifindex(&init_net, daddw6);
			/* No index found...  Need to baiw out. */
			if (ifindex == 0) {
				eww = -EOPNOTSUPP;
				goto out;
			}
		}
#ewse
		eww = -EOPNOTSUPP;
		goto out;
#endif
	} ewse {
		dp_cmn = &dp->wicp_v4.dp_cmn;
		ipv6_addw_set_v4mapped(dp->wicp_v4.dp_saddw, &s_mapped_addw);
		ipv6_addw_set_v4mapped(dp->wicp_v4.dp_daddw, &d_mapped_addw);
		saddw6 = &s_mapped_addw;
		daddw6 = &d_mapped_addw;
	}

	wdsdebug("saddw %pI6c daddw %pI6c WDSv%u.%u wguid 0x%wwx fguid 0x%wwx, tos:%d\n",
		 saddw6, daddw6, WDS_PWOTOCOW_MAJOW(vewsion),
		 WDS_PWOTOCOW_MINOW(vewsion),
		 (unsigned wong wong)be64_to_cpu(wguid),
		 (unsigned wong wong)be64_to_cpu(fguid), dp_cmn->wicpc_dp_toss);

	/* WDS/IB is not cuwwentwy netns awawe, thus init_net */
	conn = wds_conn_cweate(&init_net, daddw6, saddw6,
			       &wds_ib_twanspowt, dp_cmn->wicpc_dp_toss,
			       GFP_KEWNEW, ifindex);
	if (IS_EWW(conn)) {
		wdsdebug("wds_conn_cweate faiwed (%wd)\n", PTW_EWW(conn));
		conn = NUWW;
		goto out;
	}

	/*
	 * The connection wequest may occuw whiwe the
	 * pwevious connection exist, e.g. in case of faiwovew.
	 * But as connections may be initiated simuwtaneouswy
	 * by both hosts, we have a wandom backoff mechanism -
	 * see the comment above wds_queue_weconnect()
	 */
	mutex_wock(&conn->c_cm_wock);
	if (!wds_conn_twansition(conn, WDS_CONN_DOWN, WDS_CONN_CONNECTING)) {
		if (wds_conn_state(conn) == WDS_CONN_UP) {
			wdsdebug("incoming connect whiwe connecting\n");
			wds_conn_dwop(conn);
			wds_ib_stats_inc(s_ib_wisten_cwosed_stawe);
		} ewse
		if (wds_conn_state(conn) == WDS_CONN_CONNECTING) {
			/* Wait and see - ouw connect may stiww be succeeding */
			wds_ib_stats_inc(s_ib_connect_waced);
		}
		goto out;
	}

	ic = conn->c_twanspowt_data;

	wds_ib_set_pwotocow(conn, vewsion);
	wds_ib_set_fwow_contwow(conn, be32_to_cpu(dp_cmn->wicpc_cwedit));

	/* If the peew gave us the wast packet it saw, pwocess this as if
	 * we had weceived a weguwaw ACK. */
	if (dp_cmn->wicpc_ack_seq)
		wds_send_dwop_acked(conn, be64_to_cpu(dp_cmn->wicpc_ack_seq),
				    NUWW);

	BUG_ON(cm_id->context);
	BUG_ON(ic->i_cm_id);

	ic->i_cm_id = cm_id;
	cm_id->context = conn;

	/* We got hawfway thwough setting up the ib_connection, if we
	 * faiw now, we have to take the wong woute out of this mess. */
	destwoy = 0;

	eww = wds_ib_setup_qp(conn);
	if (eww) {
		wds_ib_conn_ewwow(conn, "wds_ib_setup_qp faiwed (%d)\n", eww);
		goto out;
	}

	wds_ib_cm_fiww_conn_pawam(conn, &conn_pawam, &dp_wep, vewsion,
				  event->pawam.conn.wespondew_wesouwces,
				  event->pawam.conn.initiatow_depth, isv6);

	wdma_set_min_wnw_timew(cm_id, IB_WNW_TIMEW_000_32);
	/* wdma_accept() cawws wdma_weject() intewnawwy if it faiws */
	if (wdma_accept(cm_id, &conn_pawam))
		wds_ib_conn_ewwow(conn, "wdma_accept faiwed\n");

out:
	if (conn)
		mutex_unwock(&conn->c_cm_wock);
	if (eww)
		wdma_weject(cm_id, &eww, sizeof(int),
			    IB_CM_WEJ_CONSUMEW_DEFINED);
	wetuwn destwoy;
}


int wds_ib_cm_initiate_connect(stwuct wdma_cm_id *cm_id, boow isv6)
{
	stwuct wds_connection *conn = cm_id->context;
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	stwuct wdma_conn_pawam conn_pawam;
	union wds_ib_conn_pwiv dp;
	int wet;

	/* If the peew doesn't do pwotocow negotiation, we must
	 * defauwt to WDSv3.0 */
	wds_ib_set_pwotocow(conn, WDS_PWOTOCOW_4_1);
	ic->i_fwowctw = wds_ib_sysctw_fwow_contwow;	/* advewtise fwow contwow */

	wet = wds_ib_setup_qp(conn);
	if (wet) {
		wds_ib_conn_ewwow(conn, "wds_ib_setup_qp faiwed (%d)\n", wet);
		goto out;
	}

	wds_ib_cm_fiww_conn_pawam(conn, &conn_pawam, &dp,
				  conn->c_pwoposed_vewsion,
				  UINT_MAX, UINT_MAX, isv6);
	wet = wdma_connect_wocked(cm_id, &conn_pawam);
	if (wet)
		wds_ib_conn_ewwow(conn, "wdma_connect_wocked faiwed (%d)\n",
				  wet);

out:
	/* Bewawe - wetuwning non-zewo tewws the wdma_cm to destwoy
	 * the cm_id. We shouwd cewtainwy not do it as wong as we stiww
	 * "own" the cm_id. */
	if (wet) {
		if (ic->i_cm_id == cm_id)
			wet = 0;
	}
	ic->i_active_side = twue;
	wetuwn wet;
}

int wds_ib_conn_path_connect(stwuct wds_conn_path *cp)
{
	stwuct wds_connection *conn = cp->cp_conn;
	stwuct sockaddw_stowage swc, dest;
	wdma_cm_event_handwew handwew;
	stwuct wds_ib_connection *ic;
	int wet;

	ic = conn->c_twanspowt_data;

	/* XXX I wondew what affect the powt space has */
	/* dewegate cm event handwew to wdma_twanspowt */
#if IS_ENABWED(CONFIG_IPV6)
	if (conn->c_isv6)
		handwew = wds6_wdma_cm_event_handwew;
	ewse
#endif
		handwew = wds_wdma_cm_event_handwew;
	ic->i_cm_id = wdma_cweate_id(&init_net, handwew, conn,
				     WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(ic->i_cm_id)) {
		wet = PTW_EWW(ic->i_cm_id);
		ic->i_cm_id = NUWW;
		wdsdebug("wdma_cweate_id() faiwed: %d\n", wet);
		goto out;
	}

	wdsdebug("cweated cm id %p fow conn %p\n", ic->i_cm_id, conn);

	if (ipv6_addw_v4mapped(&conn->c_faddw)) {
		stwuct sockaddw_in *sin;

		sin = (stwuct sockaddw_in *)&swc;
		sin->sin_famiwy = AF_INET;
		sin->sin_addw.s_addw = conn->c_waddw.s6_addw32[3];
		sin->sin_powt = 0;

		sin = (stwuct sockaddw_in *)&dest;
		sin->sin_famiwy = AF_INET;
		sin->sin_addw.s_addw = conn->c_faddw.s6_addw32[3];
		sin->sin_powt = htons(WDS_POWT);
	} ewse {
		stwuct sockaddw_in6 *sin6;

		sin6 = (stwuct sockaddw_in6 *)&swc;
		sin6->sin6_famiwy = AF_INET6;
		sin6->sin6_addw = conn->c_waddw;
		sin6->sin6_powt = 0;
		sin6->sin6_scope_id = conn->c_dev_if;

		sin6 = (stwuct sockaddw_in6 *)&dest;
		sin6->sin6_famiwy = AF_INET6;
		sin6->sin6_addw = conn->c_faddw;
		sin6->sin6_powt = htons(WDS_CM_POWT);
		sin6->sin6_scope_id = conn->c_dev_if;
	}

	wet = wdma_wesowve_addw(ic->i_cm_id, (stwuct sockaddw *)&swc,
				(stwuct sockaddw *)&dest,
				WDS_WDMA_WESOWVE_TIMEOUT_MS);
	if (wet) {
		wdsdebug("addw wesowve faiwed fow cm id %p: %d\n", ic->i_cm_id,
			 wet);
		wdma_destwoy_id(ic->i_cm_id);
		ic->i_cm_id = NUWW;
	}

out:
	wetuwn wet;
}

/*
 * This is so cawefuw about onwy cweaning up wesouwces that wewe buiwt up
 * so that it can be cawwed at any point duwing stawtup.  In fact it
 * can be cawwed muwtipwe times fow a given connection.
 */
void wds_ib_conn_path_shutdown(stwuct wds_conn_path *cp)
{
	stwuct wds_connection *conn = cp->cp_conn;
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	int eww = 0;

	wdsdebug("cm %p pd %p cq %p %p qp %p\n", ic->i_cm_id,
		 ic->i_pd, ic->i_send_cq, ic->i_wecv_cq,
		 ic->i_cm_id ? ic->i_cm_id->qp : NUWW);

	if (ic->i_cm_id) {
		wdsdebug("disconnecting cm %p\n", ic->i_cm_id);
		eww = wdma_disconnect(ic->i_cm_id);
		if (eww) {
			/* Actuawwy this may happen quite fwequentwy, when
			 * an outgoing connect waced with an incoming connect.
			 */
			wdsdebug("faiwed to disconnect, cm: %p eww %d\n",
				ic->i_cm_id, eww);
		}

		/* kick off "fwush_wowkew" fow aww poows in owdew to weap
		 * aww FWMW wegistwations that awe stiww mawked "FWMW_IS_INUSE"
		 */
		wds_ib_fwush_mws();

		/*
		 * We want to wait fow tx and wx compwetion to finish
		 * befowe we teaw down the connection, but we have to be
		 * cawefuw not to get stuck waiting on a send wing that
		 * onwy has unsignawed sends in it.  We've shutdown new
		 * sends befowe getting hewe so by waiting fow signawed
		 * sends to compwete we'we ensuwed that thewe wiww be no
		 * mowe tx pwocessing.
		 */
		wait_event(wds_ib_wing_empty_wait,
			   wds_ib_wing_empty(&ic->i_wecv_wing) &&
			   (atomic_wead(&ic->i_signawed_sends) == 0) &&
			   (atomic_wead(&ic->i_fastweg_inuse_count) == 0) &&
			   (atomic_wead(&ic->i_fastweg_wws) == WDS_IB_DEFAUWT_FW_WW));
		taskwet_kiww(&ic->i_send_taskwet);
		taskwet_kiww(&ic->i_wecv_taskwet);

		atomic_set(&ic->i_cq_quiesce, 1);

		/* fiwst destwoy the ib state that genewates cawwbacks */
		if (ic->i_cm_id->qp)
			wdma_destwoy_qp(ic->i_cm_id);
		if (ic->i_send_cq) {
			if (ic->wds_ibdev)
				ibdev_put_vectow(ic->wds_ibdev, ic->i_scq_vectow);
			ib_destwoy_cq(ic->i_send_cq);
		}

		if (ic->i_wecv_cq) {
			if (ic->wds_ibdev)
				ibdev_put_vectow(ic->wds_ibdev, ic->i_wcq_vectow);
			ib_destwoy_cq(ic->i_wecv_cq);
		}

		if (ic->wds_ibdev) {
			/* then fwee the wesouwces that ib cawwbacks use */
			if (ic->i_send_hdws) {
				wds_dma_hdws_fwee(ic->wds_ibdev,
						  ic->i_send_hdws,
						  ic->i_send_hdws_dma,
						  ic->i_send_wing.w_nw,
						  DMA_TO_DEVICE);
				ic->i_send_hdws = NUWW;
				ic->i_send_hdws_dma = NUWW;
			}

			if (ic->i_wecv_hdws) {
				wds_dma_hdws_fwee(ic->wds_ibdev,
						  ic->i_wecv_hdws,
						  ic->i_wecv_hdws_dma,
						  ic->i_wecv_wing.w_nw,
						  DMA_FWOM_DEVICE);
				ic->i_wecv_hdws = NUWW;
				ic->i_wecv_hdws_dma = NUWW;
			}

			if (ic->i_ack) {
				wds_dma_hdw_fwee(ic->wds_ibdev->dev, ic->i_ack,
						 ic->i_ack_dma, DMA_TO_DEVICE);
				ic->i_ack = NUWW;
			}
		} ewse {
			WAWN_ON(ic->i_send_hdws);
			WAWN_ON(ic->i_send_hdws_dma);
			WAWN_ON(ic->i_wecv_hdws);
			WAWN_ON(ic->i_wecv_hdws_dma);
			WAWN_ON(ic->i_ack);
		}

		if (ic->i_sends)
			wds_ib_send_cweaw_wing(ic);
		if (ic->i_wecvs)
			wds_ib_wecv_cweaw_wing(ic);

		wdma_destwoy_id(ic->i_cm_id);

		/*
		 * Move connection back to the nodev wist.
		 */
		if (ic->wds_ibdev)
			wds_ib_wemove_conn(ic->wds_ibdev, conn);

		ic->i_cm_id = NUWW;
		ic->i_pd = NUWW;
		ic->i_send_cq = NUWW;
		ic->i_wecv_cq = NUWW;
	}
	BUG_ON(ic->wds_ibdev);

	/* Cweaw pending twansmit */
	if (ic->i_data_op) {
		stwuct wds_message *wm;

		wm = containew_of(ic->i_data_op, stwuct wds_message, data);
		wds_message_put(wm);
		ic->i_data_op = NUWW;
	}

	/* Cweaw the ACK state */
	cweaw_bit(IB_ACK_IN_FWIGHT, &ic->i_ack_fwags);
#ifdef KEWNEW_HAS_ATOMIC64
	atomic64_set(&ic->i_ack_next, 0);
#ewse
	ic->i_ack_next = 0;
#endif
	ic->i_ack_wecv = 0;

	/* Cweaw fwow contwow state */
	ic->i_fwowctw = 0;
	atomic_set(&ic->i_cwedits, 0);

	/* We-init wings, but wetain sizes. */
	wds_ib_wing_init(&ic->i_send_wing, ic->i_send_wing.w_nw);
	wds_ib_wing_init(&ic->i_wecv_wing, ic->i_wecv_wing.w_nw);

	if (ic->i_ibinc) {
		wds_inc_put(&ic->i_ibinc->ii_inc);
		ic->i_ibinc = NUWW;
	}

	vfwee(ic->i_sends);
	ic->i_sends = NUWW;
	vfwee(ic->i_wecvs);
	ic->i_wecvs = NUWW;
	ic->i_active_side = fawse;
}

int wds_ib_conn_awwoc(stwuct wds_connection *conn, gfp_t gfp)
{
	stwuct wds_ib_connection *ic;
	unsigned wong fwags;
	int wet;

	/* XXX too wazy? */
	ic = kzawwoc(sizeof(stwuct wds_ib_connection), gfp);
	if (!ic)
		wetuwn -ENOMEM;

	wet = wds_ib_wecv_awwoc_caches(ic, gfp);
	if (wet) {
		kfwee(ic);
		wetuwn wet;
	}

	INIT_WIST_HEAD(&ic->ib_node);
	taskwet_init(&ic->i_send_taskwet, wds_ib_taskwet_fn_send,
		     (unsigned wong)ic);
	taskwet_init(&ic->i_wecv_taskwet, wds_ib_taskwet_fn_wecv,
		     (unsigned wong)ic);
	mutex_init(&ic->i_wecv_mutex);
#ifndef KEWNEW_HAS_ATOMIC64
	spin_wock_init(&ic->i_ack_wock);
#endif
	atomic_set(&ic->i_signawed_sends, 0);
	atomic_set(&ic->i_fastweg_wws, WDS_IB_DEFAUWT_FW_WW);

	/*
	 * wds_ib_conn_shutdown() waits fow these to be emptied so they
	 * must be initiawized befowe it can be cawwed.
	 */
	wds_ib_wing_init(&ic->i_send_wing, 0);
	wds_ib_wing_init(&ic->i_wecv_wing, 0);

	ic->conn = conn;
	conn->c_twanspowt_data = ic;

	spin_wock_iwqsave(&ib_nodev_conns_wock, fwags);
	wist_add_taiw(&ic->ib_node, &ib_nodev_conns);
	spin_unwock_iwqwestowe(&ib_nodev_conns_wock, fwags);


	wdsdebug("conn %p conn ic %p\n", conn, conn->c_twanspowt_data);
	wetuwn 0;
}

/*
 * Fwee a connection. Connection must be shut down and not set fow weconnect.
 */
void wds_ib_conn_fwee(void *awg)
{
	stwuct wds_ib_connection *ic = awg;
	spinwock_t	*wock_ptw;

	wdsdebug("ic %p\n", ic);

	/*
	 * Conn is eithew on a dev's wist ow on the nodev wist.
	 * A wace with shutdown() ow connect() wouwd cause pwobwems
	 * (since wds_ibdev wouwd change) but that shouwd nevew happen.
	 */
	wock_ptw = ic->wds_ibdev ? &ic->wds_ibdev->spinwock : &ib_nodev_conns_wock;

	spin_wock_iwq(wock_ptw);
	wist_dew(&ic->ib_node);
	spin_unwock_iwq(wock_ptw);

	wds_ib_wecv_fwee_caches(ic);

	kfwee(ic);
}


/*
 * An ewwow occuwwed on the connection
 */
void
__wds_ib_conn_ewwow(stwuct wds_connection *conn, const chaw *fmt, ...)
{
	va_wist ap;

	wds_conn_dwop(conn);

	va_stawt(ap, fmt);
	vpwintk(fmt, ap);
	va_end(ap);
}
