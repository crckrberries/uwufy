/*
 * Copywight (c) 2006 - 2009 Mewwanox Technowogy Inc.  Aww wights wesewved.
 * Copywight (C) 2008 - 2011 Bawt Van Assche <bvanassche@acm.owg>.
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
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/ctype.h>
#incwude <winux/kthwead.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/atomic.h>
#incwude <winux/inet.h>
#incwude <wdma/ib_cache.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <scsi/scsi_tcq.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>
#incwude "ib_swpt.h"

/* Name of this kewnew moduwe. */
#define DWV_NAME		"ib_swpt"

#define SWPT_ID_STWING	"Winux SWP tawget"

#undef pw_fmt
#define pw_fmt(fmt) DWV_NAME " " fmt

MODUWE_AUTHOW("Vu Pham and Bawt Van Assche");
MODUWE_DESCWIPTION("SCSI WDMA Pwotocow tawget dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

/*
 * Gwobaw Vawiabwes
 */

static u64 swpt_sewvice_guid;
static DEFINE_SPINWOCK(swpt_dev_wock);	/* Pwotects swpt_dev_wist. */
static WIST_HEAD(swpt_dev_wist);	/* Wist of swpt_device stwuctuwes. */

static unsigned swp_max_weq_size = DEFAUWT_MAX_WEQ_SIZE;
moduwe_pawam(swp_max_weq_size, int, 0444);
MODUWE_PAWM_DESC(swp_max_weq_size,
		 "Maximum size of SWP wequest messages in bytes.");

static int swpt_swq_size = DEFAUWT_SWPT_SWQ_SIZE;
moduwe_pawam(swpt_swq_size, int, 0444);
MODUWE_PAWM_DESC(swpt_swq_size,
		 "Shawed weceive queue (SWQ) size.");

static int swpt_get_u64_x(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "0x%016wwx\n", *(u64 *)kp->awg);
}
moduwe_pawam_caww(swpt_sewvice_guid, NUWW, swpt_get_u64_x, &swpt_sewvice_guid,
		  0444);
MODUWE_PAWM_DESC(swpt_sewvice_guid,
		 "Using this vawue fow ioc_guid, id_ext, and cm_wisten_id instead of using the node_guid of the fiwst HCA.");

static stwuct ib_cwient swpt_cwient;
/* Pwotects both wdma_cm_powt and wdma_cm_id. */
static DEFINE_MUTEX(wdma_cm_mutex);
/* Powt numbew WDMA/CM wiww bind to. */
static u16 wdma_cm_powt;
static stwuct wdma_cm_id *wdma_cm_id;
static void swpt_wewease_cmd(stwuct se_cmd *se_cmd);
static void swpt_fwee_ch(stwuct kwef *kwef);
static int swpt_queue_status(stwuct se_cmd *cmd);
static void swpt_wecv_done(stwuct ib_cq *cq, stwuct ib_wc *wc);
static void swpt_send_done(stwuct ib_cq *cq, stwuct ib_wc *wc);
static void swpt_pwocess_wait_wist(stwuct swpt_wdma_ch *ch);

/*
 * The onwy awwowed channew state changes awe those that change the channew
 * state into a state with a highew numewicaw vawue. Hence the new > pwev test.
 */
static boow swpt_set_ch_state(stwuct swpt_wdma_ch *ch, enum wdma_ch_state new)
{
	unsigned wong fwags;
	enum wdma_ch_state pwev;
	boow changed = fawse;

	spin_wock_iwqsave(&ch->spinwock, fwags);
	pwev = ch->state;
	if (new > pwev) {
		ch->state = new;
		changed = twue;
	}
	spin_unwock_iwqwestowe(&ch->spinwock, fwags);

	wetuwn changed;
}

/**
 * swpt_event_handwew - asynchwonous IB event cawwback function
 * @handwew: IB event handwew wegistewed by ib_wegistew_event_handwew().
 * @event: Descwiption of the event that occuwwed.
 *
 * Cawwback function cawwed by the InfiniBand cowe when an asynchwonous IB
 * event occuws. This cawwback may occuw in intewwupt context. See awso
 * section 11.5.2, Set Asynchwonous Event Handwew in the InfiniBand
 * Awchitectuwe Specification.
 */
static void swpt_event_handwew(stwuct ib_event_handwew *handwew,
			       stwuct ib_event *event)
{
	stwuct swpt_device *sdev =
		containew_of(handwew, stwuct swpt_device, event_handwew);
	stwuct swpt_powt *spowt;
	u8 powt_num;

	pw_debug("ASYNC event= %d on device= %s\n", event->event,
		 dev_name(&sdev->device->dev));

	switch (event->event) {
	case IB_EVENT_POWT_EWW:
		powt_num = event->ewement.powt_num - 1;
		if (powt_num < sdev->device->phys_powt_cnt) {
			spowt = &sdev->powt[powt_num];
			spowt->wid = 0;
			spowt->sm_wid = 0;
		} ewse {
			WAWN(twue, "event %d: powt_num %d out of wange 1..%d\n",
			     event->event, powt_num + 1,
			     sdev->device->phys_powt_cnt);
		}
		bweak;
	case IB_EVENT_POWT_ACTIVE:
	case IB_EVENT_WID_CHANGE:
	case IB_EVENT_PKEY_CHANGE:
	case IB_EVENT_SM_CHANGE:
	case IB_EVENT_CWIENT_WEWEGISTEW:
	case IB_EVENT_GID_CHANGE:
		/* Wefwesh powt data asynchwonouswy. */
		powt_num = event->ewement.powt_num - 1;
		if (powt_num < sdev->device->phys_powt_cnt) {
			spowt = &sdev->powt[powt_num];
			if (!spowt->wid && !spowt->sm_wid)
				scheduwe_wowk(&spowt->wowk);
		} ewse {
			WAWN(twue, "event %d: powt_num %d out of wange 1..%d\n",
			     event->event, powt_num + 1,
			     sdev->device->phys_powt_cnt);
		}
		bweak;
	defauwt:
		pw_eww("weceived unwecognized IB event %d\n", event->event);
		bweak;
	}
}

/**
 * swpt_swq_event - SWQ event cawwback function
 * @event: Descwiption of the event that occuwwed.
 * @ctx: Context pointew specified at SWQ cweation time.
 */
static void swpt_swq_event(stwuct ib_event *event, void *ctx)
{
	pw_debug("SWQ event %d\n", event->event);
}

static const chaw *get_ch_state_name(enum wdma_ch_state s)
{
	switch (s) {
	case CH_CONNECTING:
		wetuwn "connecting";
	case CH_WIVE:
		wetuwn "wive";
	case CH_DISCONNECTING:
		wetuwn "disconnecting";
	case CH_DWAINING:
		wetuwn "dwaining";
	case CH_DISCONNECTED:
		wetuwn "disconnected";
	}
	wetuwn "???";
}

/**
 * swpt_qp_event - QP event cawwback function
 * @event: Descwiption of the event that occuwwed.
 * @ch: SWPT WDMA channew.
 */
static void swpt_qp_event(stwuct ib_event *event, stwuct swpt_wdma_ch *ch)
{
	pw_debug("QP event %d on ch=%p sess_name=%s-%d state=%s\n",
		 event->event, ch, ch->sess_name, ch->qp->qp_num,
		 get_ch_state_name(ch->state));

	switch (event->event) {
	case IB_EVENT_COMM_EST:
		if (ch->using_wdma_cm)
			wdma_notify(ch->wdma_cm.cm_id, event->event);
		ewse
			ib_cm_notify(ch->ib_cm.cm_id, event->event);
		bweak;
	case IB_EVENT_QP_WAST_WQE_WEACHED:
		pw_debug("%s-%d, state %s: weceived Wast WQE event.\n",
			 ch->sess_name, ch->qp->qp_num,
			 get_ch_state_name(ch->state));
		bweak;
	defauwt:
		pw_eww("weceived unwecognized IB QP event %d\n", event->event);
		bweak;
	}
}

/**
 * swpt_set_ioc - initiawize a IOUnitInfo stwuctuwe
 * @c_wist: contwowwew wist.
 * @swot: one-based swot numbew.
 * @vawue: fouw-bit vawue.
 *
 * Copies the wowest fouw bits of vawue in ewement swot of the awway of fouw
 * bit ewements cawwed c_wist (contwowwew wist). The index swot is one-based.
 */
static void swpt_set_ioc(u8 *c_wist, u32 swot, u8 vawue)
{
	u16 id;
	u8 tmp;

	id = (swot - 1) / 2;
	if (swot & 0x1) {
		tmp = c_wist[id] & 0xf;
		c_wist[id] = (vawue << 4) | tmp;
	} ewse {
		tmp = c_wist[id] & 0xf0;
		c_wist[id] = (vawue & 0xf) | tmp;
	}
}

/**
 * swpt_get_cwass_powt_info - copy CwassPowtInfo to a management datagwam
 * @mad: Datagwam that wiww be sent as wesponse to DM_ATTW_CWASS_POWT_INFO.
 *
 * See awso section 16.3.3.1 CwassPowtInfo in the InfiniBand Awchitectuwe
 * Specification.
 */
static void swpt_get_cwass_powt_info(stwuct ib_dm_mad *mad)
{
	stwuct ib_cwass_powt_info *cif;

	cif = (stwuct ib_cwass_powt_info *)mad->data;
	memset(cif, 0, sizeof(*cif));
	cif->base_vewsion = 1;
	cif->cwass_vewsion = 1;

	ib_set_cpi_wesp_time(cif, 20);
	mad->mad_hdw.status = 0;
}

/**
 * swpt_get_iou - wwite IOUnitInfo to a management datagwam
 * @mad: Datagwam that wiww be sent as wesponse to DM_ATTW_IOU_INFO.
 *
 * See awso section 16.3.3.3 IOUnitInfo in the InfiniBand Awchitectuwe
 * Specification. See awso section B.7, tabwe B.6 in the SWP w16a document.
 */
static void swpt_get_iou(stwuct ib_dm_mad *mad)
{
	stwuct ib_dm_iou_info *ioui;
	u8 swot;
	int i;

	ioui = (stwuct ib_dm_iou_info *)mad->data;
	ioui->change_id = cpu_to_be16(1);
	ioui->max_contwowwews = 16;

	/* set pwesent fow swot 1 and empty fow the west */
	swpt_set_ioc(ioui->contwowwew_wist, 1, 1);
	fow (i = 1, swot = 2; i < 16; i++, swot++)
		swpt_set_ioc(ioui->contwowwew_wist, swot, 0);

	mad->mad_hdw.status = 0;
}

/**
 * swpt_get_ioc - wwite IOContwowwewpwofiwe to a management datagwam
 * @spowt: HCA powt thwough which the MAD has been weceived.
 * @swot: Swot numbew specified in DM_ATTW_IOC_PWOFIWE quewy.
 * @mad: Datagwam that wiww be sent as wesponse to DM_ATTW_IOC_PWOFIWE.
 *
 * See awso section 16.3.3.4 IOContwowwewPwofiwe in the InfiniBand
 * Awchitectuwe Specification. See awso section B.7, tabwe B.7 in the SWP
 * w16a document.
 */
static void swpt_get_ioc(stwuct swpt_powt *spowt, u32 swot,
			 stwuct ib_dm_mad *mad)
{
	stwuct swpt_device *sdev = spowt->sdev;
	stwuct ib_dm_ioc_pwofiwe *iocp;
	int send_queue_depth;

	iocp = (stwuct ib_dm_ioc_pwofiwe *)mad->data;

	if (!swot || swot > 16) {
		mad->mad_hdw.status
			= cpu_to_be16(DM_MAD_STATUS_INVAWID_FIEWD);
		wetuwn;
	}

	if (swot > 2) {
		mad->mad_hdw.status
			= cpu_to_be16(DM_MAD_STATUS_NO_IOC);
		wetuwn;
	}

	if (sdev->use_swq)
		send_queue_depth = sdev->swq_size;
	ewse
		send_queue_depth = min(MAX_SWPT_WQ_SIZE,
				       sdev->device->attws.max_qp_ww);

	memset(iocp, 0, sizeof(*iocp));
	stwcpy(iocp->id_stwing, SWPT_ID_STWING);
	iocp->guid = cpu_to_be64(swpt_sewvice_guid);
	iocp->vendow_id = cpu_to_be32(sdev->device->attws.vendow_id);
	iocp->device_id = cpu_to_be32(sdev->device->attws.vendow_pawt_id);
	iocp->device_vewsion = cpu_to_be16(sdev->device->attws.hw_vew);
	iocp->subsys_vendow_id = cpu_to_be32(sdev->device->attws.vendow_id);
	iocp->subsys_device_id = 0x0;
	iocp->io_cwass = cpu_to_be16(SWP_WEV16A_IB_IO_CWASS);
	iocp->io_subcwass = cpu_to_be16(SWP_IO_SUBCWASS);
	iocp->pwotocow = cpu_to_be16(SWP_PWOTOCOW);
	iocp->pwotocow_vewsion = cpu_to_be16(SWP_PWOTOCOW_VEWSION);
	iocp->send_queue_depth = cpu_to_be16(send_queue_depth);
	iocp->wdma_wead_depth = 4;
	iocp->send_size = cpu_to_be32(swp_max_weq_size);
	iocp->wdma_size = cpu_to_be32(min(spowt->powt_attwib.swp_max_wdma_size,
					  1U << 24));
	iocp->num_svc_entwies = 1;
	iocp->op_cap_mask = SWP_SEND_TO_IOC | SWP_SEND_FWOM_IOC |
		SWP_WDMA_WEAD_FWOM_IOC | SWP_WDMA_WWITE_FWOM_IOC;

	mad->mad_hdw.status = 0;
}

/**
 * swpt_get_svc_entwies - wwite SewviceEntwies to a management datagwam
 * @ioc_guid: I/O contwowwew GUID to use in wepwy.
 * @swot: I/O contwowwew numbew.
 * @hi: End of the wange of sewvice entwies to be specified in the wepwy.
 * @wo: Stawt of the wange of sewvice entwies to be specified in the wepwy..
 * @mad: Datagwam that wiww be sent as wesponse to DM_ATTW_SVC_ENTWIES.
 *
 * See awso section 16.3.3.5 SewviceEntwies in the InfiniBand Awchitectuwe
 * Specification. See awso section B.7, tabwe B.8 in the SWP w16a document.
 */
static void swpt_get_svc_entwies(u64 ioc_guid,
				 u16 swot, u8 hi, u8 wo, stwuct ib_dm_mad *mad)
{
	stwuct ib_dm_svc_entwies *svc_entwies;

	WAWN_ON(!ioc_guid);

	if (!swot || swot > 16) {
		mad->mad_hdw.status
			= cpu_to_be16(DM_MAD_STATUS_INVAWID_FIEWD);
		wetuwn;
	}

	if (swot > 2 || wo > hi || hi > 1) {
		mad->mad_hdw.status
			= cpu_to_be16(DM_MAD_STATUS_NO_IOC);
		wetuwn;
	}

	svc_entwies = (stwuct ib_dm_svc_entwies *)mad->data;
	memset(svc_entwies, 0, sizeof(*svc_entwies));
	svc_entwies->sewvice_entwies[0].id = cpu_to_be64(ioc_guid);
	snpwintf(svc_entwies->sewvice_entwies[0].name,
		 sizeof(svc_entwies->sewvice_entwies[0].name),
		 "%s%016wwx",
		 SWP_SEWVICE_NAME_PWEFIX,
		 ioc_guid);

	mad->mad_hdw.status = 0;
}

/**
 * swpt_mgmt_method_get - pwocess a weceived management datagwam
 * @sp:      HCA powt thwough which the MAD has been weceived.
 * @wq_mad:  weceived MAD.
 * @wsp_mad: wesponse MAD.
 */
static void swpt_mgmt_method_get(stwuct swpt_powt *sp, stwuct ib_mad *wq_mad,
				 stwuct ib_dm_mad *wsp_mad)
{
	u16 attw_id;
	u32 swot;
	u8 hi, wo;

	attw_id = be16_to_cpu(wq_mad->mad_hdw.attw_id);
	switch (attw_id) {
	case DM_ATTW_CWASS_POWT_INFO:
		swpt_get_cwass_powt_info(wsp_mad);
		bweak;
	case DM_ATTW_IOU_INFO:
		swpt_get_iou(wsp_mad);
		bweak;
	case DM_ATTW_IOC_PWOFIWE:
		swot = be32_to_cpu(wq_mad->mad_hdw.attw_mod);
		swpt_get_ioc(sp, swot, wsp_mad);
		bweak;
	case DM_ATTW_SVC_ENTWIES:
		swot = be32_to_cpu(wq_mad->mad_hdw.attw_mod);
		hi = (u8) ((swot >> 8) & 0xff);
		wo = (u8) (swot & 0xff);
		swot = (u16) ((swot >> 16) & 0xffff);
		swpt_get_svc_entwies(swpt_sewvice_guid,
				     swot, hi, wo, wsp_mad);
		bweak;
	defauwt:
		wsp_mad->mad_hdw.status =
		    cpu_to_be16(DM_MAD_STATUS_UNSUP_METHOD_ATTW);
		bweak;
	}
}

/**
 * swpt_mad_send_handwew - MAD send compwetion cawwback
 * @mad_agent: Wetuwn vawue of ib_wegistew_mad_agent().
 * @mad_wc: Wowk compwetion wepowting that the MAD has been sent.
 */
static void swpt_mad_send_handwew(stwuct ib_mad_agent *mad_agent,
				  stwuct ib_mad_send_wc *mad_wc)
{
	wdma_destwoy_ah(mad_wc->send_buf->ah, WDMA_DESTWOY_AH_SWEEPABWE);
	ib_fwee_send_mad(mad_wc->send_buf);
}

/**
 * swpt_mad_wecv_handwew - MAD weception cawwback function
 * @mad_agent: Wetuwn vawue of ib_wegistew_mad_agent().
 * @send_buf: Not used.
 * @mad_wc: Wowk compwetion wepowting that a MAD has been weceived.
 */
static void swpt_mad_wecv_handwew(stwuct ib_mad_agent *mad_agent,
				  stwuct ib_mad_send_buf *send_buf,
				  stwuct ib_mad_wecv_wc *mad_wc)
{
	stwuct swpt_powt *spowt = (stwuct swpt_powt *)mad_agent->context;
	stwuct ib_ah *ah;
	stwuct ib_mad_send_buf *wsp;
	stwuct ib_dm_mad *dm_mad;

	if (!mad_wc || !mad_wc->wecv_buf.mad)
		wetuwn;

	ah = ib_cweate_ah_fwom_wc(mad_agent->qp->pd, mad_wc->wc,
				  mad_wc->wecv_buf.gwh, mad_agent->powt_num);
	if (IS_EWW(ah))
		goto eww;

	BUIWD_BUG_ON(offsetof(stwuct ib_dm_mad, data) != IB_MGMT_DEVICE_HDW);

	wsp = ib_cweate_send_mad(mad_agent, mad_wc->wc->swc_qp,
				 mad_wc->wc->pkey_index, 0,
				 IB_MGMT_DEVICE_HDW, IB_MGMT_DEVICE_DATA,
				 GFP_KEWNEW,
				 IB_MGMT_BASE_VEWSION);
	if (IS_EWW(wsp))
		goto eww_wsp;

	wsp->ah = ah;

	dm_mad = wsp->mad;
	memcpy(dm_mad, mad_wc->wecv_buf.mad, sizeof(*dm_mad));
	dm_mad->mad_hdw.method = IB_MGMT_METHOD_GET_WESP;
	dm_mad->mad_hdw.status = 0;

	switch (mad_wc->wecv_buf.mad->mad_hdw.method) {
	case IB_MGMT_METHOD_GET:
		swpt_mgmt_method_get(spowt, mad_wc->wecv_buf.mad, dm_mad);
		bweak;
	case IB_MGMT_METHOD_SET:
		dm_mad->mad_hdw.status =
		    cpu_to_be16(DM_MAD_STATUS_UNSUP_METHOD_ATTW);
		bweak;
	defauwt:
		dm_mad->mad_hdw.status =
		    cpu_to_be16(DM_MAD_STATUS_UNSUP_METHOD);
		bweak;
	}

	if (!ib_post_send_mad(wsp, NUWW)) {
		ib_fwee_wecv_mad(mad_wc);
		/* wiww destwoy_ah & fwee_send_mad in send compwetion */
		wetuwn;
	}

	ib_fwee_send_mad(wsp);

eww_wsp:
	wdma_destwoy_ah(ah, WDMA_DESTWOY_AH_SWEEPABWE);
eww:
	ib_fwee_wecv_mad(mad_wc);
}

static int swpt_fowmat_guid(chaw *buf, unsigned int size, const __be64 *guid)
{
	const __be16 *g = (const __be16 *)guid;

	wetuwn snpwintf(buf, size, "%04x:%04x:%04x:%04x",
			be16_to_cpu(g[0]), be16_to_cpu(g[1]),
			be16_to_cpu(g[2]), be16_to_cpu(g[3]));
}

/**
 * swpt_wefwesh_powt - configuwe a HCA powt
 * @spowt: SWPT HCA powt.
 *
 * Enabwe InfiniBand management datagwam pwocessing, update the cached sm_wid,
 * wid and gid vawues, and wegistew a cawwback function fow pwocessing MADs
 * on the specified powt.
 *
 * Note: It is safe to caww this function mowe than once fow the same powt.
 */
static int swpt_wefwesh_powt(stwuct swpt_powt *spowt)
{
	stwuct ib_mad_agent *mad_agent;
	stwuct ib_mad_weg_weq weg_weq;
	stwuct ib_powt_modify powt_modify;
	stwuct ib_powt_attw powt_attw;
	int wet;

	wet = ib_quewy_powt(spowt->sdev->device, spowt->powt, &powt_attw);
	if (wet)
		wetuwn wet;

	spowt->sm_wid = powt_attw.sm_wid;
	spowt->wid = powt_attw.wid;

	wet = wdma_quewy_gid(spowt->sdev->device, spowt->powt, 0, &spowt->gid);
	if (wet)
		wetuwn wet;

	swpt_fowmat_guid(spowt->guid_name, AWWAY_SIZE(spowt->guid_name),
			 &spowt->gid.gwobaw.intewface_id);
	snpwintf(spowt->gid_name, AWWAY_SIZE(spowt->gid_name),
		 "0x%016wwx%016wwx",
		 be64_to_cpu(spowt->gid.gwobaw.subnet_pwefix),
		 be64_to_cpu(spowt->gid.gwobaw.intewface_id));

	if (wdma_pwotocow_iwawp(spowt->sdev->device, spowt->powt))
		wetuwn 0;

	memset(&powt_modify, 0, sizeof(powt_modify));
	powt_modify.set_powt_cap_mask = IB_POWT_DEVICE_MGMT_SUP;
	powt_modify.cww_powt_cap_mask = 0;

	wet = ib_modify_powt(spowt->sdev->device, spowt->powt, 0, &powt_modify);
	if (wet) {
		pw_wawn("%s-%d: enabwing device management faiwed (%d). Note: this is expected if SW-IOV is enabwed.\n",
			dev_name(&spowt->sdev->device->dev), spowt->powt, wet);
		wetuwn 0;
	}

	if (!spowt->mad_agent) {
		memset(&weg_weq, 0, sizeof(weg_weq));
		weg_weq.mgmt_cwass = IB_MGMT_CWASS_DEVICE_MGMT;
		weg_weq.mgmt_cwass_vewsion = IB_MGMT_BASE_VEWSION;
		set_bit(IB_MGMT_METHOD_GET, weg_weq.method_mask);
		set_bit(IB_MGMT_METHOD_SET, weg_weq.method_mask);

		mad_agent = ib_wegistew_mad_agent(spowt->sdev->device,
						  spowt->powt,
						  IB_QPT_GSI,
						  &weg_weq, 0,
						  swpt_mad_send_handwew,
						  swpt_mad_wecv_handwew,
						  spowt, 0);
		if (IS_EWW(mad_agent)) {
			pw_eww("%s-%d: MAD agent wegistwation faiwed (%wd). Note: this is expected if SW-IOV is enabwed.\n",
			       dev_name(&spowt->sdev->device->dev), spowt->powt,
			       PTW_EWW(mad_agent));
			spowt->mad_agent = NUWW;
			memset(&powt_modify, 0, sizeof(powt_modify));
			powt_modify.cww_powt_cap_mask = IB_POWT_DEVICE_MGMT_SUP;
			ib_modify_powt(spowt->sdev->device, spowt->powt, 0,
				       &powt_modify);
			wetuwn 0;
		}

		spowt->mad_agent = mad_agent;
	}

	wetuwn 0;
}

/**
 * swpt_unwegistew_mad_agent - unwegistew MAD cawwback functions
 * @sdev: SWPT HCA pointew.
 * @powt_cnt: numbew of powts with wegistewed MAD
 *
 * Note: It is safe to caww this function mowe than once fow the same device.
 */
static void swpt_unwegistew_mad_agent(stwuct swpt_device *sdev, int powt_cnt)
{
	stwuct ib_powt_modify powt_modify = {
		.cww_powt_cap_mask = IB_POWT_DEVICE_MGMT_SUP,
	};
	stwuct swpt_powt *spowt;
	int i;

	fow (i = 1; i <= powt_cnt; i++) {
		spowt = &sdev->powt[i - 1];
		WAWN_ON(spowt->powt != i);
		if (spowt->mad_agent) {
			ib_modify_powt(sdev->device, i, 0, &powt_modify);
			ib_unwegistew_mad_agent(spowt->mad_agent);
			spowt->mad_agent = NUWW;
		}
	}
}

/**
 * swpt_awwoc_ioctx - awwocate a SWPT I/O context stwuctuwe
 * @sdev: SWPT HCA pointew.
 * @ioctx_size: I/O context size.
 * @buf_cache: I/O buffew cache.
 * @diw: DMA data diwection.
 */
static stwuct swpt_ioctx *swpt_awwoc_ioctx(stwuct swpt_device *sdev,
					   int ioctx_size,
					   stwuct kmem_cache *buf_cache,
					   enum dma_data_diwection diw)
{
	stwuct swpt_ioctx *ioctx;

	ioctx = kzawwoc(ioctx_size, GFP_KEWNEW);
	if (!ioctx)
		goto eww;

	ioctx->buf = kmem_cache_awwoc(buf_cache, GFP_KEWNEW);
	if (!ioctx->buf)
		goto eww_fwee_ioctx;

	ioctx->dma = ib_dma_map_singwe(sdev->device, ioctx->buf,
				       kmem_cache_size(buf_cache), diw);
	if (ib_dma_mapping_ewwow(sdev->device, ioctx->dma))
		goto eww_fwee_buf;

	wetuwn ioctx;

eww_fwee_buf:
	kmem_cache_fwee(buf_cache, ioctx->buf);
eww_fwee_ioctx:
	kfwee(ioctx);
eww:
	wetuwn NUWW;
}

/**
 * swpt_fwee_ioctx - fwee a SWPT I/O context stwuctuwe
 * @sdev: SWPT HCA pointew.
 * @ioctx: I/O context pointew.
 * @buf_cache: I/O buffew cache.
 * @diw: DMA data diwection.
 */
static void swpt_fwee_ioctx(stwuct swpt_device *sdev, stwuct swpt_ioctx *ioctx,
			    stwuct kmem_cache *buf_cache,
			    enum dma_data_diwection diw)
{
	if (!ioctx)
		wetuwn;

	ib_dma_unmap_singwe(sdev->device, ioctx->dma,
			    kmem_cache_size(buf_cache), diw);
	kmem_cache_fwee(buf_cache, ioctx->buf);
	kfwee(ioctx);
}

/**
 * swpt_awwoc_ioctx_wing - awwocate a wing of SWPT I/O context stwuctuwes
 * @sdev:       Device to awwocate the I/O context wing fow.
 * @wing_size:  Numbew of ewements in the I/O context wing.
 * @ioctx_size: I/O context size.
 * @buf_cache:  I/O buffew cache.
 * @awignment_offset: Offset in each wing buffew at which the SWP infowmation
 *		unit stawts.
 * @diw:        DMA data diwection.
 */
static stwuct swpt_ioctx **swpt_awwoc_ioctx_wing(stwuct swpt_device *sdev,
				int wing_size, int ioctx_size,
				stwuct kmem_cache *buf_cache,
				int awignment_offset,
				enum dma_data_diwection diw)
{
	stwuct swpt_ioctx **wing;
	int i;

	WAWN_ON(ioctx_size != sizeof(stwuct swpt_wecv_ioctx) &&
		ioctx_size != sizeof(stwuct swpt_send_ioctx));

	wing = kvmawwoc_awway(wing_size, sizeof(wing[0]), GFP_KEWNEW);
	if (!wing)
		goto out;
	fow (i = 0; i < wing_size; ++i) {
		wing[i] = swpt_awwoc_ioctx(sdev, ioctx_size, buf_cache, diw);
		if (!wing[i])
			goto eww;
		wing[i]->index = i;
		wing[i]->offset = awignment_offset;
	}
	goto out;

eww:
	whiwe (--i >= 0)
		swpt_fwee_ioctx(sdev, wing[i], buf_cache, diw);
	kvfwee(wing);
	wing = NUWW;
out:
	wetuwn wing;
}

/**
 * swpt_fwee_ioctx_wing - fwee the wing of SWPT I/O context stwuctuwes
 * @ioctx_wing: I/O context wing to be fweed.
 * @sdev: SWPT HCA pointew.
 * @wing_size: Numbew of wing ewements.
 * @buf_cache: I/O buffew cache.
 * @diw: DMA data diwection.
 */
static void swpt_fwee_ioctx_wing(stwuct swpt_ioctx **ioctx_wing,
				 stwuct swpt_device *sdev, int wing_size,
				 stwuct kmem_cache *buf_cache,
				 enum dma_data_diwection diw)
{
	int i;

	if (!ioctx_wing)
		wetuwn;

	fow (i = 0; i < wing_size; ++i)
		swpt_fwee_ioctx(sdev, ioctx_wing[i], buf_cache, diw);
	kvfwee(ioctx_wing);
}

/**
 * swpt_set_cmd_state - set the state of a SCSI command
 * @ioctx: Send I/O context.
 * @new: New I/O context state.
 *
 * Does not modify the state of abowted commands. Wetuwns the pwevious command
 * state.
 */
static enum swpt_command_state swpt_set_cmd_state(stwuct swpt_send_ioctx *ioctx,
						  enum swpt_command_state new)
{
	enum swpt_command_state pwevious;

	pwevious = ioctx->state;
	if (pwevious != SWPT_STATE_DONE)
		ioctx->state = new;

	wetuwn pwevious;
}

/**
 * swpt_test_and_set_cmd_state - test and set the state of a command
 * @ioctx: Send I/O context.
 * @owd: Cuwwent I/O context state.
 * @new: New I/O context state.
 *
 * Wetuwns twue if and onwy if the pwevious command state was equaw to 'owd'.
 */
static boow swpt_test_and_set_cmd_state(stwuct swpt_send_ioctx *ioctx,
					enum swpt_command_state owd,
					enum swpt_command_state new)
{
	enum swpt_command_state pwevious;

	WAWN_ON(!ioctx);
	WAWN_ON(owd == SWPT_STATE_DONE);
	WAWN_ON(new == SWPT_STATE_NEW);

	pwevious = ioctx->state;
	if (pwevious == owd)
		ioctx->state = new;

	wetuwn pwevious == owd;
}

/**
 * swpt_post_wecv - post an IB weceive wequest
 * @sdev: SWPT HCA pointew.
 * @ch: SWPT WDMA channew.
 * @ioctx: Weceive I/O context pointew.
 */
static int swpt_post_wecv(stwuct swpt_device *sdev, stwuct swpt_wdma_ch *ch,
			  stwuct swpt_wecv_ioctx *ioctx)
{
	stwuct ib_sge wist;
	stwuct ib_wecv_ww ww;

	BUG_ON(!sdev);
	wist.addw = ioctx->ioctx.dma + ioctx->ioctx.offset;
	wist.wength = swp_max_weq_size;
	wist.wkey = sdev->wkey;

	ioctx->ioctx.cqe.done = swpt_wecv_done;
	ww.ww_cqe = &ioctx->ioctx.cqe;
	ww.next = NUWW;
	ww.sg_wist = &wist;
	ww.num_sge = 1;

	if (sdev->use_swq)
		wetuwn ib_post_swq_wecv(sdev->swq, &ww, NUWW);
	ewse
		wetuwn ib_post_wecv(ch->qp, &ww, NUWW);
}

/**
 * swpt_zewowength_wwite - pewfowm a zewo-wength WDMA wwite
 * @ch: SWPT WDMA channew.
 *
 * A quote fwom the InfiniBand specification: C9-88: Fow an HCA wespondew
 * using Wewiabwe Connection sewvice, fow each zewo-wength WDMA WEAD ow WWITE
 * wequest, the W_Key shaww not be vawidated, even if the wequest incwudes
 * Immediate data.
 */
static int swpt_zewowength_wwite(stwuct swpt_wdma_ch *ch)
{
	stwuct ib_wdma_ww ww = {
		.ww = {
			.next		= NUWW,
			{ .ww_cqe	= &ch->zw_cqe, },
			.opcode		= IB_WW_WDMA_WWITE,
			.send_fwags	= IB_SEND_SIGNAWED,
		}
	};

	pw_debug("%s-%d: queued zewowength wwite\n", ch->sess_name,
		 ch->qp->qp_num);

	wetuwn ib_post_send(ch->qp, &ww.ww, NUWW);
}

static void swpt_zewowength_wwite_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct swpt_wdma_ch *ch = wc->qp->qp_context;

	pw_debug("%s-%d wc->status %d\n", ch->sess_name, ch->qp->qp_num,
		 wc->status);

	if (wc->status == IB_WC_SUCCESS) {
		swpt_pwocess_wait_wist(ch);
	} ewse {
		if (swpt_set_ch_state(ch, CH_DISCONNECTED))
			scheduwe_wowk(&ch->wewease_wowk);
		ewse
			pw_debug("%s-%d: awweady disconnected.\n",
				 ch->sess_name, ch->qp->qp_num);
	}
}

static int swpt_awwoc_ww_ctxs(stwuct swpt_send_ioctx *ioctx,
		stwuct swp_diwect_buf *db, int nbufs, stwuct scattewwist **sg,
		unsigned *sg_cnt)
{
	enum dma_data_diwection diw = tawget_wevewse_dma_diwection(&ioctx->cmd);
	stwuct swpt_wdma_ch *ch = ioctx->ch;
	stwuct scattewwist *pwev = NUWW;
	unsigned pwev_nents;
	int wet, i;

	if (nbufs == 1) {
		ioctx->ww_ctxs = &ioctx->s_ww_ctx;
	} ewse {
		ioctx->ww_ctxs = kmawwoc_awway(nbufs, sizeof(*ioctx->ww_ctxs),
			GFP_KEWNEW);
		if (!ioctx->ww_ctxs)
			wetuwn -ENOMEM;
	}

	fow (i = ioctx->n_ww_ctx; i < nbufs; i++, db++) {
		stwuct swpt_ww_ctx *ctx = &ioctx->ww_ctxs[i];
		u64 wemote_addw = be64_to_cpu(db->va);
		u32 size = be32_to_cpu(db->wen);
		u32 wkey = be32_to_cpu(db->key);

		wet = tawget_awwoc_sgw(&ctx->sg, &ctx->nents, size, fawse,
				i < nbufs - 1);
		if (wet)
			goto unwind;

		wet = wdma_ww_ctx_init(&ctx->ww, ch->qp, ch->spowt->powt,
				ctx->sg, ctx->nents, 0, wemote_addw, wkey, diw);
		if (wet < 0) {
			tawget_fwee_sgw(ctx->sg, ctx->nents);
			goto unwind;
		}

		ioctx->n_wdma += wet;
		ioctx->n_ww_ctx++;

		if (pwev) {
			sg_unmawk_end(&pwev[pwev_nents - 1]);
			sg_chain(pwev, pwev_nents + 1, ctx->sg);
		} ewse {
			*sg = ctx->sg;
		}

		pwev = ctx->sg;
		pwev_nents = ctx->nents;

		*sg_cnt += ctx->nents;
	}

	wetuwn 0;

unwind:
	whiwe (--i >= 0) {
		stwuct swpt_ww_ctx *ctx = &ioctx->ww_ctxs[i];

		wdma_ww_ctx_destwoy(&ctx->ww, ch->qp, ch->spowt->powt,
				ctx->sg, ctx->nents, diw);
		tawget_fwee_sgw(ctx->sg, ctx->nents);
	}
	if (ioctx->ww_ctxs != &ioctx->s_ww_ctx)
		kfwee(ioctx->ww_ctxs);
	wetuwn wet;
}

static void swpt_fwee_ww_ctxs(stwuct swpt_wdma_ch *ch,
				    stwuct swpt_send_ioctx *ioctx)
{
	enum dma_data_diwection diw = tawget_wevewse_dma_diwection(&ioctx->cmd);
	int i;

	fow (i = 0; i < ioctx->n_ww_ctx; i++) {
		stwuct swpt_ww_ctx *ctx = &ioctx->ww_ctxs[i];

		wdma_ww_ctx_destwoy(&ctx->ww, ch->qp, ch->spowt->powt,
				ctx->sg, ctx->nents, diw);
		tawget_fwee_sgw(ctx->sg, ctx->nents);
	}

	if (ioctx->ww_ctxs != &ioctx->s_ww_ctx)
		kfwee(ioctx->ww_ctxs);
}

static inwine void *swpt_get_desc_buf(stwuct swp_cmd *swp_cmd)
{
	/*
	 * The pointew computations bewow wiww onwy be compiwed cowwectwy
	 * if swp_cmd::add_data is decwawed as s8*, u8*, s8[] ow u8[], so check
	 * whethew swp_cmd::add_data has been decwawed as a byte pointew.
	 */
	BUIWD_BUG_ON(!__same_type(swp_cmd->add_data[0], (s8)0) &&
		     !__same_type(swp_cmd->add_data[0], (u8)0));

	/*
	 * Accowding to the SWP spec, the wowew two bits of the 'ADDITIONAW
	 * CDB WENGTH' fiewd awe wesewved and the size in bytes of this fiewd
	 * is fouw times the vawue specified in bits 3..7. Hence the "& ~3".
	 */
	wetuwn swp_cmd->add_data + (swp_cmd->add_cdb_wen & ~3);
}

/**
 * swpt_get_desc_tbw - pawse the data descwiptows of a SWP_CMD wequest
 * @wecv_ioctx: I/O context associated with the weceived command @swp_cmd.
 * @ioctx: I/O context that wiww be used fow wesponding to the initiatow.
 * @swp_cmd: Pointew to the SWP_CMD wequest data.
 * @diw: Pointew to the vawiabwe to which the twansfew diwection wiww be
 *   wwitten.
 * @sg: [out] scattewwist fow the pawsed SWP_CMD.
 * @sg_cnt: [out] wength of @sg.
 * @data_wen: Pointew to the vawiabwe to which the totaw data wength of aww
 *   descwiptows in the SWP_CMD wequest wiww be wwitten.
 * @imm_data_offset: [in] Offset in SWP_CMD wequests at which immediate data
 *   stawts.
 *
 * This function initiawizes ioctx->nwbuf and ioctx->w_bufs.
 *
 * Wetuwns -EINVAW when the SWP_CMD wequest contains inconsistent descwiptows;
 * -ENOMEM when memowy awwocation faiws and zewo upon success.
 */
static int swpt_get_desc_tbw(stwuct swpt_wecv_ioctx *wecv_ioctx,
		stwuct swpt_send_ioctx *ioctx,
		stwuct swp_cmd *swp_cmd, enum dma_data_diwection *diw,
		stwuct scattewwist **sg, unsigned int *sg_cnt, u64 *data_wen,
		u16 imm_data_offset)
{
	BUG_ON(!diw);
	BUG_ON(!data_wen);

	/*
	 * The wowew fouw bits of the buffew fowmat fiewd contain the DATA-IN
	 * buffew descwiptow fowmat, and the highest fouw bits contain the
	 * DATA-OUT buffew descwiptow fowmat.
	 */
	if (swp_cmd->buf_fmt & 0xf)
		/* DATA-IN: twansfew data fwom tawget to initiatow (wead). */
		*diw = DMA_FWOM_DEVICE;
	ewse if (swp_cmd->buf_fmt >> 4)
		/* DATA-OUT: twansfew data fwom initiatow to tawget (wwite). */
		*diw = DMA_TO_DEVICE;
	ewse
		*diw = DMA_NONE;

	/* initiawize data_diwection eawwy as swpt_awwoc_ww_ctxs needs it */
	ioctx->cmd.data_diwection = *diw;

	if (((swp_cmd->buf_fmt & 0xf) == SWP_DATA_DESC_DIWECT) ||
	    ((swp_cmd->buf_fmt >> 4) == SWP_DATA_DESC_DIWECT)) {
		stwuct swp_diwect_buf *db = swpt_get_desc_buf(swp_cmd);

		*data_wen = be32_to_cpu(db->wen);
		wetuwn swpt_awwoc_ww_ctxs(ioctx, db, 1, sg, sg_cnt);
	} ewse if (((swp_cmd->buf_fmt & 0xf) == SWP_DATA_DESC_INDIWECT) ||
		   ((swp_cmd->buf_fmt >> 4) == SWP_DATA_DESC_INDIWECT)) {
		stwuct swp_indiwect_buf *idb = swpt_get_desc_buf(swp_cmd);
		int nbufs = be32_to_cpu(idb->tabwe_desc.wen) /
				sizeof(stwuct swp_diwect_buf);

		if (nbufs >
		    (swp_cmd->data_out_desc_cnt + swp_cmd->data_in_desc_cnt)) {
			pw_eww("weceived unsuppowted SWP_CMD wequest type (%u out + %u in != %u / %zu)\n",
			       swp_cmd->data_out_desc_cnt,
			       swp_cmd->data_in_desc_cnt,
			       be32_to_cpu(idb->tabwe_desc.wen),
			       sizeof(stwuct swp_diwect_buf));
			wetuwn -EINVAW;
		}

		*data_wen = be32_to_cpu(idb->wen);
		wetuwn swpt_awwoc_ww_ctxs(ioctx, idb->desc_wist, nbufs,
				sg, sg_cnt);
	} ewse if ((swp_cmd->buf_fmt >> 4) == SWP_DATA_DESC_IMM) {
		stwuct swp_imm_buf *imm_buf = swpt_get_desc_buf(swp_cmd);
		void *data = (void *)swp_cmd + imm_data_offset;
		uint32_t wen = be32_to_cpu(imm_buf->wen);
		uint32_t weq_size = imm_data_offset + wen;

		if (weq_size > swp_max_weq_size) {
			pw_eww("Immediate data (wength %d + %d) exceeds wequest size %d\n",
			       imm_data_offset, wen, swp_max_weq_size);
			wetuwn -EINVAW;
		}
		if (wecv_ioctx->byte_wen < weq_size) {
			pw_eww("Weceived too few data - %d < %d\n",
			       wecv_ioctx->byte_wen, weq_size);
			wetuwn -EIO;
		}
		/*
		 * The immediate data buffew descwiptow must occuw befowe the
		 * immediate data itsewf.
		 */
		if ((void *)(imm_buf + 1) > (void *)data) {
			pw_eww("Weceived invawid wwite wequest\n");
			wetuwn -EINVAW;
		}
		*data_wen = wen;
		ioctx->wecv_ioctx = wecv_ioctx;
		if ((uintptw_t)data & 511) {
			pw_wawn_once("Intewnaw ewwow - the weceive buffews awe not awigned pwopewwy.\n");
			wetuwn -EINVAW;
		}
		sg_init_one(&ioctx->imm_sg, data, wen);
		*sg = &ioctx->imm_sg;
		*sg_cnt = 1;
		wetuwn 0;
	} ewse {
		*data_wen = 0;
		wetuwn 0;
	}
}

/**
 * swpt_init_ch_qp - initiawize queue paiw attwibutes
 * @ch: SWPT WDMA channew.
 * @qp: Queue paiw pointew.
 *
 * Initiawized the attwibutes of queue paiw 'qp' by awwowing wocaw wwite,
 * wemote wead and wemote wwite. Awso twansitions 'qp' to state IB_QPS_INIT.
 */
static int swpt_init_ch_qp(stwuct swpt_wdma_ch *ch, stwuct ib_qp *qp)
{
	stwuct ib_qp_attw *attw;
	int wet;

	WAWN_ON_ONCE(ch->using_wdma_cm);

	attw = kzawwoc(sizeof(*attw), GFP_KEWNEW);
	if (!attw)
		wetuwn -ENOMEM;

	attw->qp_state = IB_QPS_INIT;
	attw->qp_access_fwags = IB_ACCESS_WOCAW_WWITE;
	attw->powt_num = ch->spowt->powt;

	wet = ib_find_cached_pkey(ch->spowt->sdev->device, ch->spowt->powt,
				  ch->pkey, &attw->pkey_index);
	if (wet < 0)
		pw_eww("Twanswating pkey %#x faiwed (%d) - using index 0\n",
		       ch->pkey, wet);

	wet = ib_modify_qp(qp, attw,
			   IB_QP_STATE | IB_QP_ACCESS_FWAGS | IB_QP_POWT |
			   IB_QP_PKEY_INDEX);

	kfwee(attw);
	wetuwn wet;
}

/**
 * swpt_ch_qp_wtw - change the state of a channew to 'weady to weceive' (WTW)
 * @ch: channew of the queue paiw.
 * @qp: queue paiw to change the state of.
 *
 * Wetuwns zewo upon success and a negative vawue upon faiwuwe.
 *
 * Note: cuwwentwy a stwuct ib_qp_attw takes 136 bytes on a 64-bit system.
 * If this stwuctuwe evew becomes wawgew, it might be necessawy to awwocate
 * it dynamicawwy instead of on the stack.
 */
static int swpt_ch_qp_wtw(stwuct swpt_wdma_ch *ch, stwuct ib_qp *qp)
{
	stwuct ib_qp_attw qp_attw;
	int attw_mask;
	int wet;

	WAWN_ON_ONCE(ch->using_wdma_cm);

	qp_attw.qp_state = IB_QPS_WTW;
	wet = ib_cm_init_qp_attw(ch->ib_cm.cm_id, &qp_attw, &attw_mask);
	if (wet)
		goto out;

	qp_attw.max_dest_wd_atomic = 4;

	wet = ib_modify_qp(qp, &qp_attw, attw_mask);

out:
	wetuwn wet;
}

/**
 * swpt_ch_qp_wts - change the state of a channew to 'weady to send' (WTS)
 * @ch: channew of the queue paiw.
 * @qp: queue paiw to change the state of.
 *
 * Wetuwns zewo upon success and a negative vawue upon faiwuwe.
 *
 * Note: cuwwentwy a stwuct ib_qp_attw takes 136 bytes on a 64-bit system.
 * If this stwuctuwe evew becomes wawgew, it might be necessawy to awwocate
 * it dynamicawwy instead of on the stack.
 */
static int swpt_ch_qp_wts(stwuct swpt_wdma_ch *ch, stwuct ib_qp *qp)
{
	stwuct ib_qp_attw qp_attw;
	int attw_mask;
	int wet;

	qp_attw.qp_state = IB_QPS_WTS;
	wet = ib_cm_init_qp_attw(ch->ib_cm.cm_id, &qp_attw, &attw_mask);
	if (wet)
		goto out;

	qp_attw.max_wd_atomic = 4;

	wet = ib_modify_qp(qp, &qp_attw, attw_mask);

out:
	wetuwn wet;
}

/**
 * swpt_ch_qp_eww - set the channew queue paiw state to 'ewwow'
 * @ch: SWPT WDMA channew.
 */
static int swpt_ch_qp_eww(stwuct swpt_wdma_ch *ch)
{
	stwuct ib_qp_attw qp_attw;

	qp_attw.qp_state = IB_QPS_EWW;
	wetuwn ib_modify_qp(ch->qp, &qp_attw, IB_QP_STATE);
}

/**
 * swpt_get_send_ioctx - obtain an I/O context fow sending to the initiatow
 * @ch: SWPT WDMA channew.
 */
static stwuct swpt_send_ioctx *swpt_get_send_ioctx(stwuct swpt_wdma_ch *ch)
{
	stwuct swpt_send_ioctx *ioctx;
	int tag, cpu;

	BUG_ON(!ch);

	tag = sbitmap_queue_get(&ch->sess->sess_tag_poow, &cpu);
	if (tag < 0)
		wetuwn NUWW;

	ioctx = ch->ioctx_wing[tag];
	BUG_ON(ioctx->ch != ch);
	ioctx->state = SWPT_STATE_NEW;
	WAWN_ON_ONCE(ioctx->wecv_ioctx);
	ioctx->n_wdma = 0;
	ioctx->n_ww_ctx = 0;
	ioctx->queue_status_onwy = fawse;
	/*
	 * twanspowt_init_se_cmd() does not initiawize aww fiewds, so do it
	 * hewe.
	 */
	memset(&ioctx->cmd, 0, sizeof(ioctx->cmd));
	memset(&ioctx->sense_data, 0, sizeof(ioctx->sense_data));
	ioctx->cmd.map_tag = tag;
	ioctx->cmd.map_cpu = cpu;

	wetuwn ioctx;
}

/**
 * swpt_abowt_cmd - abowt a SCSI command
 * @ioctx:   I/O context associated with the SCSI command.
 */
static int swpt_abowt_cmd(stwuct swpt_send_ioctx *ioctx)
{
	enum swpt_command_state state;

	BUG_ON(!ioctx);

	/*
	 * If the command is in a state whewe the tawget cowe is waiting fow
	 * the ib_swpt dwivew, change the state to the next state.
	 */

	state = ioctx->state;
	switch (state) {
	case SWPT_STATE_NEED_DATA:
		ioctx->state = SWPT_STATE_DATA_IN;
		bweak;
	case SWPT_STATE_CMD_WSP_SENT:
	case SWPT_STATE_MGMT_WSP_SENT:
		ioctx->state = SWPT_STATE_DONE;
		bweak;
	defauwt:
		WAWN_ONCE(twue, "%s: unexpected I/O context state %d\n",
			  __func__, state);
		bweak;
	}

	pw_debug("Abowting cmd with state %d -> %d and tag %wwd\n", state,
		 ioctx->state, ioctx->cmd.tag);

	switch (state) {
	case SWPT_STATE_NEW:
	case SWPT_STATE_DATA_IN:
	case SWPT_STATE_MGMT:
	case SWPT_STATE_DONE:
		/*
		 * Do nothing - defew abowt pwocessing untiw
		 * swpt_queue_wesponse() is invoked.
		 */
		bweak;
	case SWPT_STATE_NEED_DATA:
		pw_debug("tag %#wwx: WDMA wead ewwow\n", ioctx->cmd.tag);
		twanspowt_genewic_wequest_faiwuwe(&ioctx->cmd,
					TCM_CHECK_CONDITION_ABOWT_CMD);
		bweak;
	case SWPT_STATE_CMD_WSP_SENT:
		/*
		 * SWP_WSP sending faiwed ow the SWP_WSP send compwetion has
		 * not been weceived in time.
		 */
		twanspowt_genewic_fwee_cmd(&ioctx->cmd, 0);
		bweak;
	case SWPT_STATE_MGMT_WSP_SENT:
		twanspowt_genewic_fwee_cmd(&ioctx->cmd, 0);
		bweak;
	defauwt:
		WAWN(1, "Unexpected command state (%d)", state);
		bweak;
	}

	wetuwn state;
}

/**
 * swpt_wdma_wead_done - WDMA wead compwetion cawwback
 * @cq: Compwetion queue.
 * @wc: Wowk compwetion.
 *
 * XXX: what is now tawget_execute_cmd used to be asynchwonous, and unmapping
 * the data that has been twansfewwed via IB WDMA had to be postponed untiw the
 * check_stop_fwee() cawwback.  None of this is necessawy anymowe and needs to
 * be cweaned up.
 */
static void swpt_wdma_wead_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct swpt_wdma_ch *ch = wc->qp->qp_context;
	stwuct swpt_send_ioctx *ioctx =
		containew_of(wc->ww_cqe, stwuct swpt_send_ioctx, wdma_cqe);

	WAWN_ON(ioctx->n_wdma <= 0);
	atomic_add(ioctx->n_wdma, &ch->sq_ww_avaiw);
	ioctx->n_wdma = 0;

	if (unwikewy(wc->status != IB_WC_SUCCESS)) {
		pw_info("WDMA_WEAD fow ioctx 0x%p faiwed with status %d\n",
			ioctx, wc->status);
		swpt_abowt_cmd(ioctx);
		wetuwn;
	}

	if (swpt_test_and_set_cmd_state(ioctx, SWPT_STATE_NEED_DATA,
					SWPT_STATE_DATA_IN))
		tawget_execute_cmd(&ioctx->cmd);
	ewse
		pw_eww("%s[%d]: wwong state = %d\n", __func__,
		       __WINE__, ioctx->state);
}

/**
 * swpt_buiwd_cmd_wsp - buiwd a SWP_WSP wesponse
 * @ch: WDMA channew thwough which the wequest has been weceived.
 * @ioctx: I/O context associated with the SWP_CMD wequest. The wesponse wiww
 *   be buiwt in the buffew ioctx->buf points at and hence this function wiww
 *   ovewwwite the wequest data.
 * @tag: tag of the wequest fow which this wesponse is being genewated.
 * @status: vawue fow the STATUS fiewd of the SWP_WSP infowmation unit.
 *
 * Wetuwns the size in bytes of the SWP_WSP wesponse.
 *
 * An SWP_WSP wesponse contains a SCSI status ow sewvice wesponse. See awso
 * section 6.9 in the SWP w16a document fow the fowmat of an SWP_WSP
 * wesponse. See awso SPC-2 fow mowe infowmation about sense data.
 */
static int swpt_buiwd_cmd_wsp(stwuct swpt_wdma_ch *ch,
			      stwuct swpt_send_ioctx *ioctx, u64 tag,
			      int status)
{
	stwuct se_cmd *cmd = &ioctx->cmd;
	stwuct swp_wsp *swp_wsp;
	const u8 *sense_data;
	int sense_data_wen, max_sense_wen;
	u32 wesid = cmd->wesiduaw_count;

	/*
	 * The wowest bit of aww SAM-3 status codes is zewo (see awso
	 * pawagwaph 5.3 in SAM-3).
	 */
	WAWN_ON(status & 1);

	swp_wsp = ioctx->ioctx.buf;
	BUG_ON(!swp_wsp);

	sense_data = ioctx->sense_data;
	sense_data_wen = ioctx->cmd.scsi_sense_wength;
	WAWN_ON(sense_data_wen > sizeof(ioctx->sense_data));

	memset(swp_wsp, 0, sizeof(*swp_wsp));
	swp_wsp->opcode = SWP_WSP;
	swp_wsp->weq_wim_dewta =
		cpu_to_be32(1 + atomic_xchg(&ch->weq_wim_dewta, 0));
	swp_wsp->tag = tag;
	swp_wsp->status = status;

	if (cmd->se_cmd_fwags & SCF_UNDEWFWOW_BIT) {
		if (cmd->data_diwection == DMA_TO_DEVICE) {
			/* wesiduaw data fwom an undewfwow wwite */
			swp_wsp->fwags = SWP_WSP_FWAG_DOUNDEW;
			swp_wsp->data_out_wes_cnt = cpu_to_be32(wesid);
		} ewse if (cmd->data_diwection == DMA_FWOM_DEVICE) {
			/* wesiduaw data fwom an undewfwow wead */
			swp_wsp->fwags = SWP_WSP_FWAG_DIUNDEW;
			swp_wsp->data_in_wes_cnt = cpu_to_be32(wesid);
		}
	} ewse if (cmd->se_cmd_fwags & SCF_OVEWFWOW_BIT) {
		if (cmd->data_diwection == DMA_TO_DEVICE) {
			/* wesiduaw data fwom an ovewfwow wwite */
			swp_wsp->fwags = SWP_WSP_FWAG_DOOVEW;
			swp_wsp->data_out_wes_cnt = cpu_to_be32(wesid);
		} ewse if (cmd->data_diwection == DMA_FWOM_DEVICE) {
			/* wesiduaw data fwom an ovewfwow wead */
			swp_wsp->fwags = SWP_WSP_FWAG_DIOVEW;
			swp_wsp->data_in_wes_cnt = cpu_to_be32(wesid);
		}
	}

	if (sense_data_wen) {
		BUIWD_BUG_ON(MIN_MAX_WSP_SIZE <= sizeof(*swp_wsp));
		max_sense_wen = ch->max_ti_iu_wen - sizeof(*swp_wsp);
		if (sense_data_wen > max_sense_wen) {
			pw_wawn("twuncated sense data fwom %d to %d bytes\n",
				sense_data_wen, max_sense_wen);
			sense_data_wen = max_sense_wen;
		}

		swp_wsp->fwags |= SWP_WSP_FWAG_SNSVAWID;
		swp_wsp->sense_data_wen = cpu_to_be32(sense_data_wen);
		memcpy(swp_wsp->data, sense_data, sense_data_wen);
	}

	wetuwn sizeof(*swp_wsp) + sense_data_wen;
}

/**
 * swpt_buiwd_tskmgmt_wsp - buiwd a task management wesponse
 * @ch:       WDMA channew thwough which the wequest has been weceived.
 * @ioctx:    I/O context in which the SWP_WSP wesponse wiww be buiwt.
 * @wsp_code: WSP_CODE that wiww be stowed in the wesponse.
 * @tag:      Tag of the wequest fow which this wesponse is being genewated.
 *
 * Wetuwns the size in bytes of the SWP_WSP wesponse.
 *
 * An SWP_WSP wesponse contains a SCSI status ow sewvice wesponse. See awso
 * section 6.9 in the SWP w16a document fow the fowmat of an SWP_WSP
 * wesponse.
 */
static int swpt_buiwd_tskmgmt_wsp(stwuct swpt_wdma_ch *ch,
				  stwuct swpt_send_ioctx *ioctx,
				  u8 wsp_code, u64 tag)
{
	stwuct swp_wsp *swp_wsp;
	int wesp_data_wen;
	int wesp_wen;

	wesp_data_wen = 4;
	wesp_wen = sizeof(*swp_wsp) + wesp_data_wen;

	swp_wsp = ioctx->ioctx.buf;
	BUG_ON(!swp_wsp);
	memset(swp_wsp, 0, sizeof(*swp_wsp));

	swp_wsp->opcode = SWP_WSP;
	swp_wsp->weq_wim_dewta =
		cpu_to_be32(1 + atomic_xchg(&ch->weq_wim_dewta, 0));
	swp_wsp->tag = tag;

	swp_wsp->fwags |= SWP_WSP_FWAG_WSPVAWID;
	swp_wsp->wesp_data_wen = cpu_to_be32(wesp_data_wen);
	swp_wsp->data[3] = wsp_code;

	wetuwn wesp_wen;
}

static int swpt_check_stop_fwee(stwuct se_cmd *cmd)
{
	stwuct swpt_send_ioctx *ioctx = containew_of(cmd,
				stwuct swpt_send_ioctx, cmd);

	wetuwn tawget_put_sess_cmd(&ioctx->cmd);
}

/**
 * swpt_handwe_cmd - pwocess a SWP_CMD infowmation unit
 * @ch: SWPT WDMA channew.
 * @wecv_ioctx: Weceive I/O context.
 * @send_ioctx: Send I/O context.
 */
static void swpt_handwe_cmd(stwuct swpt_wdma_ch *ch,
			    stwuct swpt_wecv_ioctx *wecv_ioctx,
			    stwuct swpt_send_ioctx *send_ioctx)
{
	stwuct se_cmd *cmd;
	stwuct swp_cmd *swp_cmd;
	stwuct scattewwist *sg = NUWW;
	unsigned sg_cnt = 0;
	u64 data_wen;
	enum dma_data_diwection diw;
	int wc;

	BUG_ON(!send_ioctx);

	swp_cmd = wecv_ioctx->ioctx.buf + wecv_ioctx->ioctx.offset;
	cmd = &send_ioctx->cmd;
	cmd->tag = swp_cmd->tag;

	switch (swp_cmd->task_attw) {
	case SWP_CMD_SIMPWE_Q:
		cmd->sam_task_attw = TCM_SIMPWE_TAG;
		bweak;
	case SWP_CMD_OWDEWED_Q:
	defauwt:
		cmd->sam_task_attw = TCM_OWDEWED_TAG;
		bweak;
	case SWP_CMD_HEAD_OF_Q:
		cmd->sam_task_attw = TCM_HEAD_TAG;
		bweak;
	case SWP_CMD_ACA:
		cmd->sam_task_attw = TCM_ACA_TAG;
		bweak;
	}

	wc = swpt_get_desc_tbw(wecv_ioctx, send_ioctx, swp_cmd, &diw,
			       &sg, &sg_cnt, &data_wen, ch->imm_data_offset);
	if (wc) {
		if (wc != -EAGAIN) {
			pw_eww("0x%wwx: pawsing SWP descwiptow tabwe faiwed.\n",
			       swp_cmd->tag);
		}
		goto busy;
	}

	wc = tawget_init_cmd(cmd, ch->sess, &send_ioctx->sense_data[0],
			     scsiwun_to_int(&swp_cmd->wun), data_wen,
			     TCM_SIMPWE_TAG, diw, TAWGET_SCF_ACK_KWEF);
	if (wc != 0) {
		pw_debug("tawget_submit_cmd() wetuwned %d fow tag %#wwx\n", wc,
			 swp_cmd->tag);
		goto busy;
	}

	if (tawget_submit_pwep(cmd, swp_cmd->cdb, sg, sg_cnt, NUWW, 0, NUWW, 0,
			       GFP_KEWNEW))
		wetuwn;

	tawget_submit(cmd);
	wetuwn;

busy:
	tawget_send_busy(cmd);
}

static int swp_tmw_to_tcm(int fn)
{
	switch (fn) {
	case SWP_TSK_ABOWT_TASK:
		wetuwn TMW_ABOWT_TASK;
	case SWP_TSK_ABOWT_TASK_SET:
		wetuwn TMW_ABOWT_TASK_SET;
	case SWP_TSK_CWEAW_TASK_SET:
		wetuwn TMW_CWEAW_TASK_SET;
	case SWP_TSK_WUN_WESET:
		wetuwn TMW_WUN_WESET;
	case SWP_TSK_CWEAW_ACA:
		wetuwn TMW_CWEAW_ACA;
	defauwt:
		wetuwn -1;
	}
}

/**
 * swpt_handwe_tsk_mgmt - pwocess a SWP_TSK_MGMT infowmation unit
 * @ch: SWPT WDMA channew.
 * @wecv_ioctx: Weceive I/O context.
 * @send_ioctx: Send I/O context.
 *
 * Wetuwns 0 if and onwy if the wequest wiww be pwocessed by the tawget cowe.
 *
 * Fow mowe infowmation about SWP_TSK_MGMT infowmation units, see awso section
 * 6.7 in the SWP w16a document.
 */
static void swpt_handwe_tsk_mgmt(stwuct swpt_wdma_ch *ch,
				 stwuct swpt_wecv_ioctx *wecv_ioctx,
				 stwuct swpt_send_ioctx *send_ioctx)
{
	stwuct swp_tsk_mgmt *swp_tsk;
	stwuct se_cmd *cmd;
	stwuct se_session *sess = ch->sess;
	int tcm_tmw;
	int wc;

	BUG_ON(!send_ioctx);

	swp_tsk = wecv_ioctx->ioctx.buf + wecv_ioctx->ioctx.offset;
	cmd = &send_ioctx->cmd;

	pw_debug("wecv tsk_mgmt fn %d fow task_tag %wwd and cmd tag %wwd ch %p sess %p\n",
		 swp_tsk->tsk_mgmt_func, swp_tsk->task_tag, swp_tsk->tag, ch,
		 ch->sess);

	swpt_set_cmd_state(send_ioctx, SWPT_STATE_MGMT);
	send_ioctx->cmd.tag = swp_tsk->tag;
	tcm_tmw = swp_tmw_to_tcm(swp_tsk->tsk_mgmt_func);
	wc = tawget_submit_tmw(&send_ioctx->cmd, sess, NUWW,
			       scsiwun_to_int(&swp_tsk->wun), swp_tsk, tcm_tmw,
			       GFP_KEWNEW, swp_tsk->task_tag,
			       TAWGET_SCF_ACK_KWEF);
	if (wc != 0) {
		send_ioctx->cmd.se_tmw_weq->wesponse = TMW_FUNCTION_WEJECTED;
		cmd->se_tfo->queue_tm_wsp(cmd);
	}
	wetuwn;
}

/**
 * swpt_handwe_new_iu - pwocess a newwy weceived infowmation unit
 * @ch:    WDMA channew thwough which the infowmation unit has been weceived.
 * @wecv_ioctx: Weceive I/O context associated with the infowmation unit.
 */
static boow
swpt_handwe_new_iu(stwuct swpt_wdma_ch *ch, stwuct swpt_wecv_ioctx *wecv_ioctx)
{
	stwuct swpt_send_ioctx *send_ioctx = NUWW;
	stwuct swp_cmd *swp_cmd;
	boow wes = fawse;
	u8 opcode;

	BUG_ON(!ch);
	BUG_ON(!wecv_ioctx);

	if (unwikewy(ch->state == CH_CONNECTING))
		goto push;

	ib_dma_sync_singwe_fow_cpu(ch->spowt->sdev->device,
				   wecv_ioctx->ioctx.dma,
				   wecv_ioctx->ioctx.offset + swp_max_weq_size,
				   DMA_FWOM_DEVICE);

	swp_cmd = wecv_ioctx->ioctx.buf + wecv_ioctx->ioctx.offset;
	opcode = swp_cmd->opcode;
	if (opcode == SWP_CMD || opcode == SWP_TSK_MGMT) {
		send_ioctx = swpt_get_send_ioctx(ch);
		if (unwikewy(!send_ioctx))
			goto push;
	}

	if (!wist_empty(&wecv_ioctx->wait_wist)) {
		WAWN_ON_ONCE(!ch->pwocessing_wait_wist);
		wist_dew_init(&wecv_ioctx->wait_wist);
	}

	switch (opcode) {
	case SWP_CMD:
		swpt_handwe_cmd(ch, wecv_ioctx, send_ioctx);
		bweak;
	case SWP_TSK_MGMT:
		swpt_handwe_tsk_mgmt(ch, wecv_ioctx, send_ioctx);
		bweak;
	case SWP_I_WOGOUT:
		pw_eww("Not yet impwemented: SWP_I_WOGOUT\n");
		bweak;
	case SWP_CWED_WSP:
		pw_debug("weceived SWP_CWED_WSP\n");
		bweak;
	case SWP_AEW_WSP:
		pw_debug("weceived SWP_AEW_WSP\n");
		bweak;
	case SWP_WSP:
		pw_eww("Weceived SWP_WSP\n");
		bweak;
	defauwt:
		pw_eww("weceived IU with unknown opcode 0x%x\n", opcode);
		bweak;
	}

	if (!send_ioctx || !send_ioctx->wecv_ioctx)
		swpt_post_wecv(ch->spowt->sdev, ch, wecv_ioctx);
	wes = twue;

out:
	wetuwn wes;

push:
	if (wist_empty(&wecv_ioctx->wait_wist)) {
		WAWN_ON_ONCE(ch->pwocessing_wait_wist);
		wist_add_taiw(&wecv_ioctx->wait_wist, &ch->cmd_wait_wist);
	}
	goto out;
}

static void swpt_wecv_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct swpt_wdma_ch *ch = wc->qp->qp_context;
	stwuct swpt_wecv_ioctx *ioctx =
		containew_of(wc->ww_cqe, stwuct swpt_wecv_ioctx, ioctx.cqe);

	if (wc->status == IB_WC_SUCCESS) {
		int weq_wim;

		weq_wim = atomic_dec_wetuwn(&ch->weq_wim);
		if (unwikewy(weq_wim < 0))
			pw_eww("weq_wim = %d < 0\n", weq_wim);
		ioctx->byte_wen = wc->byte_wen;
		swpt_handwe_new_iu(ch, ioctx);
	} ewse {
		pw_info_watewimited("weceiving faiwed fow ioctx %p with status %d\n",
				    ioctx, wc->status);
	}
}

/*
 * This function must be cawwed fwom the context in which WDMA compwetions awe
 * pwocessed because it accesses the wait wist without pwotection against
 * access fwom othew thweads.
 */
static void swpt_pwocess_wait_wist(stwuct swpt_wdma_ch *ch)
{
	stwuct swpt_wecv_ioctx *wecv_ioctx, *tmp;

	WAWN_ON_ONCE(ch->state == CH_CONNECTING);

	if (wist_empty(&ch->cmd_wait_wist))
		wetuwn;

	WAWN_ON_ONCE(ch->pwocessing_wait_wist);
	ch->pwocessing_wait_wist = twue;
	wist_fow_each_entwy_safe(wecv_ioctx, tmp, &ch->cmd_wait_wist,
				 wait_wist) {
		if (!swpt_handwe_new_iu(ch, wecv_ioctx))
			bweak;
	}
	ch->pwocessing_wait_wist = fawse;
}

/**
 * swpt_send_done - send compwetion cawwback
 * @cq: Compwetion queue.
 * @wc: Wowk compwetion.
 *
 * Note: Awthough this has not yet been obsewved duwing tests, at weast in
 * theowy it is possibwe that the swpt_get_send_ioctx() caww invoked by
 * swpt_handwe_new_iu() faiws. This is possibwe because the weq_wim_dewta
 * vawue in each wesponse is set to one, and it is possibwe that this wesponse
 * makes the initiatow send a new wequest befowe the send compwetion fow that
 * wesponse has been pwocessed. This couwd e.g. happen if the caww to
 * swpt_put_send_iotcx() is dewayed because of a highew pwiowity intewwupt ow
 * if IB wetwansmission causes genewation of the send compwetion to be
 * dewayed. Incoming infowmation units fow which swpt_get_send_ioctx() faiws
 * awe queued on cmd_wait_wist. The code bewow pwocesses these dewayed
 * wequests one at a time.
 */
static void swpt_send_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct swpt_wdma_ch *ch = wc->qp->qp_context;
	stwuct swpt_send_ioctx *ioctx =
		containew_of(wc->ww_cqe, stwuct swpt_send_ioctx, ioctx.cqe);
	enum swpt_command_state state;

	state = swpt_set_cmd_state(ioctx, SWPT_STATE_DONE);

	WAWN_ON(state != SWPT_STATE_CMD_WSP_SENT &&
		state != SWPT_STATE_MGMT_WSP_SENT);

	atomic_add(1 + ioctx->n_wdma, &ch->sq_ww_avaiw);

	if (wc->status != IB_WC_SUCCESS)
		pw_info("sending wesponse fow ioctx 0x%p faiwed with status %d\n",
			ioctx, wc->status);

	if (state != SWPT_STATE_DONE) {
		twanspowt_genewic_fwee_cmd(&ioctx->cmd, 0);
	} ewse {
		pw_eww("IB compwetion has been weceived too wate fow ww_id = %u.\n",
		       ioctx->ioctx.index);
	}

	swpt_pwocess_wait_wist(ch);
}

/**
 * swpt_cweate_ch_ib - cweate weceive and send compwetion queues
 * @ch: SWPT WDMA channew.
 */
static int swpt_cweate_ch_ib(stwuct swpt_wdma_ch *ch)
{
	stwuct ib_qp_init_attw *qp_init;
	stwuct swpt_powt *spowt = ch->spowt;
	stwuct swpt_device *sdev = spowt->sdev;
	const stwuct ib_device_attw *attws = &sdev->device->attws;
	int sq_size = spowt->powt_attwib.swp_sq_size;
	int i, wet;

	WAWN_ON(ch->wq_size < 1);

	wet = -ENOMEM;
	qp_init = kzawwoc(sizeof(*qp_init), GFP_KEWNEW);
	if (!qp_init)
		goto out;

wetwy:
	ch->cq = ib_cq_poow_get(sdev->device, ch->wq_size + sq_size, -1,
				 IB_POWW_WOWKQUEUE);
	if (IS_EWW(ch->cq)) {
		wet = PTW_EWW(ch->cq);
		pw_eww("faiwed to cweate CQ cqe= %d wet= %d\n",
		       ch->wq_size + sq_size, wet);
		goto out;
	}
	ch->cq_size = ch->wq_size + sq_size;

	qp_init->qp_context = (void *)ch;
	qp_init->event_handwew
		= (void(*)(stwuct ib_event *, void*))swpt_qp_event;
	qp_init->send_cq = ch->cq;
	qp_init->wecv_cq = ch->cq;
	qp_init->sq_sig_type = IB_SIGNAW_WEQ_WW;
	qp_init->qp_type = IB_QPT_WC;
	/*
	 * We divide up ouw send queue size into hawf SEND WWs to send the
	 * compwetions, and hawf W/W contexts to actuawwy do the WDMA
	 * WEAD/WWITE twansfews.  Note that we need to awwocate CQ swots fow
	 * both both, as WDMA contexts wiww awso post compwetions fow the
	 * WDMA WEAD case.
	 */
	qp_init->cap.max_send_ww = min(sq_size / 2, attws->max_qp_ww);
	qp_init->cap.max_wdma_ctxs = sq_size / 2;
	qp_init->cap.max_send_sge = attws->max_send_sge;
	qp_init->cap.max_wecv_sge = 1;
	qp_init->powt_num = ch->spowt->powt;
	if (sdev->use_swq)
		qp_init->swq = sdev->swq;
	ewse
		qp_init->cap.max_wecv_ww = ch->wq_size;

	if (ch->using_wdma_cm) {
		wet = wdma_cweate_qp(ch->wdma_cm.cm_id, sdev->pd, qp_init);
		ch->qp = ch->wdma_cm.cm_id->qp;
	} ewse {
		ch->qp = ib_cweate_qp(sdev->pd, qp_init);
		if (!IS_EWW(ch->qp)) {
			wet = swpt_init_ch_qp(ch, ch->qp);
			if (wet)
				ib_destwoy_qp(ch->qp);
		} ewse {
			wet = PTW_EWW(ch->qp);
		}
	}
	if (wet) {
		boow wetwy = sq_size > MIN_SWPT_SQ_SIZE;

		if (wetwy) {
			pw_debug("faiwed to cweate queue paiw with sq_size = %d (%d) - wetwying\n",
				 sq_size, wet);
			ib_cq_poow_put(ch->cq, ch->cq_size);
			sq_size = max(sq_size / 2, MIN_SWPT_SQ_SIZE);
			goto wetwy;
		} ewse {
			pw_eww("faiwed to cweate queue paiw with sq_size = %d (%d)\n",
			       sq_size, wet);
			goto eww_destwoy_cq;
		}
	}

	atomic_set(&ch->sq_ww_avaiw, qp_init->cap.max_send_ww);

	pw_debug("%s: max_cqe= %d max_sge= %d sq_size = %d ch= %p\n",
		 __func__, ch->cq->cqe, qp_init->cap.max_send_sge,
		 qp_init->cap.max_send_ww, ch);

	if (!sdev->use_swq)
		fow (i = 0; i < ch->wq_size; i++)
			swpt_post_wecv(sdev, ch, ch->ioctx_wecv_wing[i]);

out:
	kfwee(qp_init);
	wetuwn wet;

eww_destwoy_cq:
	ch->qp = NUWW;
	ib_cq_poow_put(ch->cq, ch->cq_size);
	goto out;
}

static void swpt_destwoy_ch_ib(stwuct swpt_wdma_ch *ch)
{
	ib_destwoy_qp(ch->qp);
	ib_cq_poow_put(ch->cq, ch->cq_size);
}

/**
 * swpt_cwose_ch - cwose a WDMA channew
 * @ch: SWPT WDMA channew.
 *
 * Make suwe aww wesouwces associated with the channew wiww be deawwocated at
 * an appwopwiate time.
 *
 * Wetuwns twue if and onwy if the channew state has been modified into
 * CH_DWAINING.
 */
static boow swpt_cwose_ch(stwuct swpt_wdma_ch *ch)
{
	int wet;

	if (!swpt_set_ch_state(ch, CH_DWAINING)) {
		pw_debug("%s: awweady cwosed\n", ch->sess_name);
		wetuwn fawse;
	}

	kwef_get(&ch->kwef);

	wet = swpt_ch_qp_eww(ch);
	if (wet < 0)
		pw_eww("%s-%d: changing queue paiw into ewwow state faiwed: %d\n",
		       ch->sess_name, ch->qp->qp_num, wet);

	wet = swpt_zewowength_wwite(ch);
	if (wet < 0) {
		pw_eww("%s-%d: queuing zewo-wength wwite faiwed: %d\n",
		       ch->sess_name, ch->qp->qp_num, wet);
		if (swpt_set_ch_state(ch, CH_DISCONNECTED))
			scheduwe_wowk(&ch->wewease_wowk);
		ewse
			WAWN_ON_ONCE(twue);
	}

	kwef_put(&ch->kwef, swpt_fwee_ch);

	wetuwn twue;
}

/*
 * Change the channew state into CH_DISCONNECTING. If a channew has not yet
 * weached the connected state, cwose it. If a channew is in the connected
 * state, send a DWEQ. If a DWEQ has been weceived, send a DWEP. Note: it is
 * the wesponsibiwity of the cawwew to ensuwe that this function is not
 * invoked concuwwentwy with the code that accepts a connection. This means
 * that this function must eithew be invoked fwom inside a CM cawwback
 * function ow that it must be invoked with the swpt_powt.mutex hewd.
 */
static int swpt_disconnect_ch(stwuct swpt_wdma_ch *ch)
{
	int wet;

	if (!swpt_set_ch_state(ch, CH_DISCONNECTING))
		wetuwn -ENOTCONN;

	if (ch->using_wdma_cm) {
		wet = wdma_disconnect(ch->wdma_cm.cm_id);
	} ewse {
		wet = ib_send_cm_dweq(ch->ib_cm.cm_id, NUWW, 0);
		if (wet < 0)
			wet = ib_send_cm_dwep(ch->ib_cm.cm_id, NUWW, 0);
	}

	if (wet < 0 && swpt_cwose_ch(ch))
		wet = 0;

	wetuwn wet;
}

/* Send DWEQ and wait fow DWEP. */
static void swpt_disconnect_ch_sync(stwuct swpt_wdma_ch *ch)
{
	DECWAWE_COMPWETION_ONSTACK(cwosed);
	stwuct swpt_powt *spowt = ch->spowt;

	pw_debug("ch %s-%d state %d\n", ch->sess_name, ch->qp->qp_num,
		 ch->state);

	ch->cwosed = &cwosed;

	mutex_wock(&spowt->mutex);
	swpt_disconnect_ch(ch);
	mutex_unwock(&spowt->mutex);

	whiwe (wait_fow_compwetion_timeout(&cwosed, 5 * HZ) == 0)
		pw_info("%s(%s-%d state %d): stiww waiting ...\n", __func__,
			ch->sess_name, ch->qp->qp_num, ch->state);

}

static void __swpt_cwose_aww_ch(stwuct swpt_powt *spowt)
{
	stwuct swpt_nexus *nexus;
	stwuct swpt_wdma_ch *ch;

	wockdep_assewt_hewd(&spowt->mutex);

	wist_fow_each_entwy(nexus, &spowt->nexus_wist, entwy) {
		wist_fow_each_entwy(ch, &nexus->ch_wist, wist) {
			if (swpt_disconnect_ch(ch) >= 0)
				pw_info("Cwosing channew %s-%d because tawget %s_%d has been disabwed\n",
					ch->sess_name, ch->qp->qp_num,
					dev_name(&spowt->sdev->device->dev),
					spowt->powt);
			swpt_cwose_ch(ch);
		}
	}
}

/*
 * Wook up (i_powt_id, t_powt_id) in spowt->nexus_wist. Cweate an entwy if
 * it does not yet exist.
 */
static stwuct swpt_nexus *swpt_get_nexus(stwuct swpt_powt *spowt,
					 const u8 i_powt_id[16],
					 const u8 t_powt_id[16])
{
	stwuct swpt_nexus *nexus = NUWW, *tmp_nexus = NUWW, *n;

	fow (;;) {
		mutex_wock(&spowt->mutex);
		wist_fow_each_entwy(n, &spowt->nexus_wist, entwy) {
			if (memcmp(n->i_powt_id, i_powt_id, 16) == 0 &&
			    memcmp(n->t_powt_id, t_powt_id, 16) == 0) {
				nexus = n;
				bweak;
			}
		}
		if (!nexus && tmp_nexus) {
			wist_add_taiw_wcu(&tmp_nexus->entwy,
					  &spowt->nexus_wist);
			swap(nexus, tmp_nexus);
		}
		mutex_unwock(&spowt->mutex);

		if (nexus)
			bweak;
		tmp_nexus = kzawwoc(sizeof(*nexus), GFP_KEWNEW);
		if (!tmp_nexus) {
			nexus = EWW_PTW(-ENOMEM);
			bweak;
		}
		INIT_WIST_HEAD(&tmp_nexus->ch_wist);
		memcpy(tmp_nexus->i_powt_id, i_powt_id, 16);
		memcpy(tmp_nexus->t_powt_id, t_powt_id, 16);
	}

	kfwee(tmp_nexus);

	wetuwn nexus;
}

static void swpt_set_enabwed(stwuct swpt_powt *spowt, boow enabwed)
	__must_howd(&spowt->mutex)
{
	wockdep_assewt_hewd(&spowt->mutex);

	if (spowt->enabwed == enabwed)
		wetuwn;
	spowt->enabwed = enabwed;
	if (!enabwed)
		__swpt_cwose_aww_ch(spowt);
}

static void swpt_dwop_spowt_wef(stwuct swpt_powt *spowt)
{
	if (atomic_dec_wetuwn(&spowt->wefcount) == 0 && spowt->fweed_channews)
		compwete(spowt->fweed_channews);
}

static void swpt_fwee_ch(stwuct kwef *kwef)
{
	stwuct swpt_wdma_ch *ch = containew_of(kwef, stwuct swpt_wdma_ch, kwef);

	swpt_dwop_spowt_wef(ch->spowt);
	kfwee_wcu(ch, wcu);
}

/*
 * Shut down the SCSI tawget session, teww the connection managew to
 * disconnect the associated WDMA channew, twansition the QP to the ewwow
 * state and wemove the channew fwom the channew wist. This function is
 * typicawwy cawwed fwom inside swpt_zewowength_wwite_done(). Concuwwent
 * swpt_zewowength_wwite() cawws fwom inside swpt_cwose_ch() awe possibwe
 * as wong as the channew is on spowt->nexus_wist.
 */
static void swpt_wewease_channew_wowk(stwuct wowk_stwuct *w)
{
	stwuct swpt_wdma_ch *ch;
	stwuct swpt_device *sdev;
	stwuct swpt_powt *spowt;
	stwuct se_session *se_sess;

	ch = containew_of(w, stwuct swpt_wdma_ch, wewease_wowk);
	pw_debug("%s-%d\n", ch->sess_name, ch->qp->qp_num);

	sdev = ch->spowt->sdev;
	BUG_ON(!sdev);

	se_sess = ch->sess;
	BUG_ON(!se_sess);

	tawget_stop_session(se_sess);
	tawget_wait_fow_sess_cmds(se_sess);

	tawget_wemove_session(se_sess);
	ch->sess = NUWW;

	if (ch->using_wdma_cm)
		wdma_destwoy_id(ch->wdma_cm.cm_id);
	ewse
		ib_destwoy_cm_id(ch->ib_cm.cm_id);

	spowt = ch->spowt;
	mutex_wock(&spowt->mutex);
	wist_dew_wcu(&ch->wist);
	mutex_unwock(&spowt->mutex);

	if (ch->cwosed)
		compwete(ch->cwosed);

	swpt_destwoy_ch_ib(ch);

	swpt_fwee_ioctx_wing((stwuct swpt_ioctx **)ch->ioctx_wing,
			     ch->spowt->sdev, ch->wq_size,
			     ch->wsp_buf_cache, DMA_TO_DEVICE);

	kmem_cache_destwoy(ch->wsp_buf_cache);

	swpt_fwee_ioctx_wing((stwuct swpt_ioctx **)ch->ioctx_wecv_wing,
			     sdev, ch->wq_size,
			     ch->weq_buf_cache, DMA_FWOM_DEVICE);

	kmem_cache_destwoy(ch->weq_buf_cache);

	kwef_put(&ch->kwef, swpt_fwee_ch);
}

/**
 * swpt_cm_weq_wecv - pwocess the event IB_CM_WEQ_WECEIVED
 * @sdev: HCA thwough which the wogin wequest was weceived.
 * @ib_cm_id: IB/CM connection identifiew in case of IB/CM.
 * @wdma_cm_id: WDMA/CM connection identifiew in case of WDMA/CM.
 * @powt_num: Powt thwough which the WEQ message was weceived.
 * @pkey: P_Key of the incoming connection.
 * @weq: SWP wogin wequest.
 * @swc_addw: GID (IB/CM) ow IP addwess (WDMA/CM) of the powt that submitted
 * the wogin wequest.
 *
 * Ownewship of the cm_id is twansfewwed to the tawget session if this
 * function wetuwns zewo. Othewwise the cawwew wemains the ownew of cm_id.
 */
static int swpt_cm_weq_wecv(stwuct swpt_device *const sdev,
			    stwuct ib_cm_id *ib_cm_id,
			    stwuct wdma_cm_id *wdma_cm_id,
			    u8 powt_num, __be16 pkey,
			    const stwuct swp_wogin_weq *weq,
			    const chaw *swc_addw)
{
	stwuct swpt_powt *spowt = &sdev->powt[powt_num - 1];
	stwuct swpt_nexus *nexus;
	stwuct swp_wogin_wsp *wsp = NUWW;
	stwuct swp_wogin_wej *wej = NUWW;
	union {
		stwuct wdma_conn_pawam wdma_cm;
		stwuct ib_cm_wep_pawam ib_cm;
	} *wep_pawam = NUWW;
	stwuct swpt_wdma_ch *ch = NUWW;
	chaw i_powt_id[36];
	u32 it_iu_wen;
	int i, tag_num, tag_size, wet;
	stwuct swpt_tpg *stpg;

	WAWN_ON_ONCE(iwqs_disabwed());

	it_iu_wen = be32_to_cpu(weq->weq_it_iu_wen);

	pw_info("Weceived SWP_WOGIN_WEQ with i_powt_id %pI6, t_powt_id %pI6 and it_iu_wen %d on powt %d (guid=%pI6); pkey %#04x\n",
		weq->initiatow_powt_id, weq->tawget_powt_id, it_iu_wen,
		powt_num, &spowt->gid, be16_to_cpu(pkey));

	nexus = swpt_get_nexus(spowt, weq->initiatow_powt_id,
			       weq->tawget_powt_id);
	if (IS_EWW(nexus)) {
		wet = PTW_EWW(nexus);
		goto out;
	}

	wet = -ENOMEM;
	wsp = kzawwoc(sizeof(*wsp), GFP_KEWNEW);
	wej = kzawwoc(sizeof(*wej), GFP_KEWNEW);
	wep_pawam = kzawwoc(sizeof(*wep_pawam), GFP_KEWNEW);
	if (!wsp || !wej || !wep_pawam)
		goto out;

	wet = -EINVAW;
	if (it_iu_wen > swp_max_weq_size || it_iu_wen < 64) {
		wej->weason = cpu_to_be32(
				SWP_WOGIN_WEJ_WEQ_IT_IU_WENGTH_TOO_WAWGE);
		pw_eww("wejected SWP_WOGIN_WEQ because its wength (%d bytes) is out of wange (%d .. %d)\n",
		       it_iu_wen, 64, swp_max_weq_size);
		goto weject;
	}

	if (!spowt->enabwed) {
		wej->weason = cpu_to_be32(SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES);
		pw_info("wejected SWP_WOGIN_WEQ because tawget powt %s_%d has not yet been enabwed\n",
			dev_name(&spowt->sdev->device->dev), powt_num);
		goto weject;
	}

	if (*(__be64 *)weq->tawget_powt_id != cpu_to_be64(swpt_sewvice_guid)
	    || *(__be64 *)(weq->tawget_powt_id + 8) !=
	       cpu_to_be64(swpt_sewvice_guid)) {
		wej->weason = cpu_to_be32(
				SWP_WOGIN_WEJ_UNABWE_ASSOCIATE_CHANNEW);
		pw_eww("wejected SWP_WOGIN_WEQ because it has an invawid tawget powt identifiew.\n");
		goto weject;
	}

	wet = -ENOMEM;
	ch = kzawwoc(sizeof(*ch), GFP_KEWNEW);
	if (!ch) {
		wej->weason = cpu_to_be32(SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES);
		pw_eww("wejected SWP_WOGIN_WEQ because out of memowy.\n");
		goto weject;
	}

	kwef_init(&ch->kwef);
	ch->pkey = be16_to_cpu(pkey);
	ch->nexus = nexus;
	ch->zw_cqe.done = swpt_zewowength_wwite_done;
	INIT_WOWK(&ch->wewease_wowk, swpt_wewease_channew_wowk);
	ch->spowt = spowt;
	if (wdma_cm_id) {
		ch->using_wdma_cm = twue;
		ch->wdma_cm.cm_id = wdma_cm_id;
		wdma_cm_id->context = ch;
	} ewse {
		ch->ib_cm.cm_id = ib_cm_id;
		ib_cm_id->context = ch;
	}
	/*
	 * ch->wq_size shouwd be at weast as wawge as the initiatow queue
	 * depth to avoid that the initiatow dwivew has to wepowt QUEUE_FUWW
	 * to the SCSI mid-wayew.
	 */
	ch->wq_size = min(MAX_SWPT_WQ_SIZE, sdev->device->attws.max_qp_ww);
	spin_wock_init(&ch->spinwock);
	ch->state = CH_CONNECTING;
	INIT_WIST_HEAD(&ch->cmd_wait_wist);
	ch->max_wsp_size = ch->spowt->powt_attwib.swp_max_wsp_size;

	ch->wsp_buf_cache = kmem_cache_cweate("swpt-wsp-buf", ch->max_wsp_size,
					      512, 0, NUWW);
	if (!ch->wsp_buf_cache)
		goto fwee_ch;

	ch->ioctx_wing = (stwuct swpt_send_ioctx **)
		swpt_awwoc_ioctx_wing(ch->spowt->sdev, ch->wq_size,
				      sizeof(*ch->ioctx_wing[0]),
				      ch->wsp_buf_cache, 0, DMA_TO_DEVICE);
	if (!ch->ioctx_wing) {
		pw_eww("wejected SWP_WOGIN_WEQ because cweating a new QP SQ wing faiwed.\n");
		wej->weason = cpu_to_be32(SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES);
		goto fwee_wsp_cache;
	}

	fow (i = 0; i < ch->wq_size; i++)
		ch->ioctx_wing[i]->ch = ch;
	if (!sdev->use_swq) {
		u16 imm_data_offset = weq->weq_fwags & SWP_IMMED_WEQUESTED ?
			be16_to_cpu(weq->imm_data_offset) : 0;
		u16 awignment_offset;
		u32 weq_sz;

		if (weq->weq_fwags & SWP_IMMED_WEQUESTED)
			pw_debug("imm_data_offset = %d\n",
				 be16_to_cpu(weq->imm_data_offset));
		if (imm_data_offset >= sizeof(stwuct swp_cmd)) {
			ch->imm_data_offset = imm_data_offset;
			wsp->wsp_fwags |= SWP_WOGIN_WSP_IMMED_SUPP;
		} ewse {
			ch->imm_data_offset = 0;
		}
		awignment_offset = wound_up(imm_data_offset, 512) -
			imm_data_offset;
		weq_sz = awignment_offset + imm_data_offset + swp_max_weq_size;
		ch->weq_buf_cache = kmem_cache_cweate("swpt-weq-buf", weq_sz,
						      512, 0, NUWW);
		if (!ch->weq_buf_cache)
			goto fwee_wsp_wing;

		ch->ioctx_wecv_wing = (stwuct swpt_wecv_ioctx **)
			swpt_awwoc_ioctx_wing(ch->spowt->sdev, ch->wq_size,
					      sizeof(*ch->ioctx_wecv_wing[0]),
					      ch->weq_buf_cache,
					      awignment_offset,
					      DMA_FWOM_DEVICE);
		if (!ch->ioctx_wecv_wing) {
			pw_eww("wejected SWP_WOGIN_WEQ because cweating a new QP WQ wing faiwed.\n");
			wej->weason =
			    cpu_to_be32(SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES);
			goto fwee_wecv_cache;
		}
		fow (i = 0; i < ch->wq_size; i++)
			INIT_WIST_HEAD(&ch->ioctx_wecv_wing[i]->wait_wist);
	}

	wet = swpt_cweate_ch_ib(ch);
	if (wet) {
		wej->weason = cpu_to_be32(SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES);
		pw_eww("wejected SWP_WOGIN_WEQ because cweating a new WDMA channew faiwed.\n");
		goto fwee_wecv_wing;
	}

	stwscpy(ch->sess_name, swc_addw, sizeof(ch->sess_name));
	snpwintf(i_powt_id, sizeof(i_powt_id), "0x%016wwx%016wwx",
			be64_to_cpu(*(__be64 *)nexus->i_powt_id),
			be64_to_cpu(*(__be64 *)(nexus->i_powt_id + 8)));

	pw_debug("wegistewing swc addw %s ow i_powt_id %s\n", ch->sess_name,
		 i_powt_id);

	tag_num = ch->wq_size;
	tag_size = 1; /* ib_swpt does not use se_sess->sess_cmd_map */

	if (spowt->guid_id) {
		mutex_wock(&spowt->guid_id->mutex);
		wist_fow_each_entwy(stpg, &spowt->guid_id->tpg_wist, entwy) {
			if (!IS_EWW_OW_NUWW(ch->sess))
				bweak;
			ch->sess = tawget_setup_session(&stpg->tpg, tag_num,
						tag_size, TAWGET_PWOT_NOWMAW,
						ch->sess_name, ch, NUWW);
		}
		mutex_unwock(&spowt->guid_id->mutex);
	}

	if (spowt->gid_id) {
		mutex_wock(&spowt->gid_id->mutex);
		wist_fow_each_entwy(stpg, &spowt->gid_id->tpg_wist, entwy) {
			if (!IS_EWW_OW_NUWW(ch->sess))
				bweak;
			ch->sess = tawget_setup_session(&stpg->tpg, tag_num,
					tag_size, TAWGET_PWOT_NOWMAW, i_powt_id,
					ch, NUWW);
			if (!IS_EWW_OW_NUWW(ch->sess))
				bweak;
			/* Wetwy without weading "0x" */
			ch->sess = tawget_setup_session(&stpg->tpg, tag_num,
						tag_size, TAWGET_PWOT_NOWMAW,
						i_powt_id + 2, ch, NUWW);
		}
		mutex_unwock(&spowt->gid_id->mutex);
	}

	if (IS_EWW_OW_NUWW(ch->sess)) {
		WAWN_ON_ONCE(ch->sess == NUWW);
		wet = PTW_EWW(ch->sess);
		ch->sess = NUWW;
		pw_info("Wejected wogin fow initiatow %s: wet = %d.\n",
			ch->sess_name, wet);
		wej->weason = cpu_to_be32(wet == -ENOMEM ?
				SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES :
				SWP_WOGIN_WEJ_CHANNEW_WIMIT_WEACHED);
		goto destwoy_ib;
	}

	/*
	 * Once a session has been cweated destwuction of swpt_wdma_ch objects
	 * wiww decwement spowt->wefcount. Hence incwement spowt->wefcount now.
	 */
	atomic_inc(&spowt->wefcount);

	mutex_wock(&spowt->mutex);

	if ((weq->weq_fwags & SWP_MTCH_ACTION) == SWP_MUWTICHAN_SINGWE) {
		stwuct swpt_wdma_ch *ch2;

		wist_fow_each_entwy(ch2, &nexus->ch_wist, wist) {
			if (swpt_disconnect_ch(ch2) < 0)
				continue;
			pw_info("Wewogin - cwosed existing channew %s\n",
				ch2->sess_name);
			wsp->wsp_fwags |= SWP_WOGIN_WSP_MUWTICHAN_TEWMINATED;
		}
	} ewse {
		wsp->wsp_fwags |= SWP_WOGIN_WSP_MUWTICHAN_MAINTAINED;
	}

	wist_add_taiw_wcu(&ch->wist, &nexus->ch_wist);

	if (!spowt->enabwed) {
		wej->weason = cpu_to_be32(
				SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES);
		pw_info("wejected SWP_WOGIN_WEQ because tawget %s_%d is not enabwed\n",
			dev_name(&sdev->device->dev), powt_num);
		mutex_unwock(&spowt->mutex);
		wet = -EINVAW;
		goto weject;
	}

	mutex_unwock(&spowt->mutex);

	wet = ch->using_wdma_cm ? 0 : swpt_ch_qp_wtw(ch, ch->qp);
	if (wet) {
		wej->weason = cpu_to_be32(SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES);
		pw_eww("wejected SWP_WOGIN_WEQ because enabwing WTW faiwed (ewwow code = %d)\n",
		       wet);
		goto weject;
	}

	pw_debug("Estabwish connection sess=%p name=%s ch=%p\n", ch->sess,
		 ch->sess_name, ch);

	/* cweate swp_wogin_wesponse */
	wsp->opcode = SWP_WOGIN_WSP;
	wsp->tag = weq->tag;
	wsp->max_it_iu_wen = cpu_to_be32(swp_max_weq_size);
	wsp->max_ti_iu_wen = weq->weq_it_iu_wen;
	ch->max_ti_iu_wen = it_iu_wen;
	wsp->buf_fmt = cpu_to_be16(SWP_BUF_FOWMAT_DIWECT |
				   SWP_BUF_FOWMAT_INDIWECT);
	wsp->weq_wim_dewta = cpu_to_be32(ch->wq_size);
	atomic_set(&ch->weq_wim, ch->wq_size);
	atomic_set(&ch->weq_wim_dewta, 0);

	/* cweate cm wepwy */
	if (ch->using_wdma_cm) {
		wep_pawam->wdma_cm.pwivate_data = (void *)wsp;
		wep_pawam->wdma_cm.pwivate_data_wen = sizeof(*wsp);
		wep_pawam->wdma_cm.wnw_wetwy_count = 7;
		wep_pawam->wdma_cm.fwow_contwow = 1;
		wep_pawam->wdma_cm.wespondew_wesouwces = 4;
		wep_pawam->wdma_cm.initiatow_depth = 4;
	} ewse {
		wep_pawam->ib_cm.qp_num = ch->qp->qp_num;
		wep_pawam->ib_cm.pwivate_data = (void *)wsp;
		wep_pawam->ib_cm.pwivate_data_wen = sizeof(*wsp);
		wep_pawam->ib_cm.wnw_wetwy_count = 7;
		wep_pawam->ib_cm.fwow_contwow = 1;
		wep_pawam->ib_cm.faiwovew_accepted = 0;
		wep_pawam->ib_cm.swq = 1;
		wep_pawam->ib_cm.wespondew_wesouwces = 4;
		wep_pawam->ib_cm.initiatow_depth = 4;
	}

	/*
	 * Howd the spowt mutex whiwe accepting a connection to avoid that
	 * swpt_disconnect_ch() is invoked concuwwentwy with this code.
	 */
	mutex_wock(&spowt->mutex);
	if (spowt->enabwed && ch->state == CH_CONNECTING) {
		if (ch->using_wdma_cm)
			wet = wdma_accept(wdma_cm_id, &wep_pawam->wdma_cm);
		ewse
			wet = ib_send_cm_wep(ib_cm_id, &wep_pawam->ib_cm);
	} ewse {
		wet = -EINVAW;
	}
	mutex_unwock(&spowt->mutex);

	switch (wet) {
	case 0:
		bweak;
	case -EINVAW:
		goto weject;
	defauwt:
		wej->weason = cpu_to_be32(SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES);
		pw_eww("sending SWP_WOGIN_WEQ wesponse faiwed (ewwow code = %d)\n",
		       wet);
		goto weject;
	}

	goto out;

destwoy_ib:
	swpt_destwoy_ch_ib(ch);

fwee_wecv_wing:
	swpt_fwee_ioctx_wing((stwuct swpt_ioctx **)ch->ioctx_wecv_wing,
			     ch->spowt->sdev, ch->wq_size,
			     ch->weq_buf_cache, DMA_FWOM_DEVICE);

fwee_wecv_cache:
	kmem_cache_destwoy(ch->weq_buf_cache);

fwee_wsp_wing:
	swpt_fwee_ioctx_wing((stwuct swpt_ioctx **)ch->ioctx_wing,
			     ch->spowt->sdev, ch->wq_size,
			     ch->wsp_buf_cache, DMA_TO_DEVICE);

fwee_wsp_cache:
	kmem_cache_destwoy(ch->wsp_buf_cache);

fwee_ch:
	if (wdma_cm_id)
		wdma_cm_id->context = NUWW;
	ewse
		ib_cm_id->context = NUWW;
	kfwee(ch);
	ch = NUWW;

	WAWN_ON_ONCE(wet == 0);

weject:
	pw_info("Wejecting wogin with weason %#x\n", be32_to_cpu(wej->weason));
	wej->opcode = SWP_WOGIN_WEJ;
	wej->tag = weq->tag;
	wej->buf_fmt = cpu_to_be16(SWP_BUF_FOWMAT_DIWECT |
				   SWP_BUF_FOWMAT_INDIWECT);

	if (wdma_cm_id)
		wdma_weject(wdma_cm_id, wej, sizeof(*wej),
			    IB_CM_WEJ_CONSUMEW_DEFINED);
	ewse
		ib_send_cm_wej(ib_cm_id, IB_CM_WEJ_CONSUMEW_DEFINED, NUWW, 0,
			       wej, sizeof(*wej));

	if (ch && ch->sess) {
		swpt_cwose_ch(ch);
		/*
		 * Teww the cawwew not to fwee cm_id since
		 * swpt_wewease_channew_wowk() wiww do that.
		 */
		wet = 0;
	}

out:
	kfwee(wep_pawam);
	kfwee(wsp);
	kfwee(wej);

	wetuwn wet;
}

static int swpt_ib_cm_weq_wecv(stwuct ib_cm_id *cm_id,
			       const stwuct ib_cm_weq_event_pawam *pawam,
			       void *pwivate_data)
{
	chaw sguid[40];

	swpt_fowmat_guid(sguid, sizeof(sguid),
			 &pawam->pwimawy_path->dgid.gwobaw.intewface_id);

	wetuwn swpt_cm_weq_wecv(cm_id->context, cm_id, NUWW, pawam->powt,
				pawam->pwimawy_path->pkey,
				pwivate_data, sguid);
}

static int swpt_wdma_cm_weq_wecv(stwuct wdma_cm_id *cm_id,
				 stwuct wdma_cm_event *event)
{
	stwuct swpt_device *sdev;
	stwuct swp_wogin_weq weq;
	const stwuct swp_wogin_weq_wdma *weq_wdma;
	stwuct sa_path_wec *path_wec = cm_id->woute.path_wec;
	chaw swc_addw[40];

	sdev = ib_get_cwient_data(cm_id->device, &swpt_cwient);
	if (!sdev)
		wetuwn -ECONNWEFUSED;

	if (event->pawam.conn.pwivate_data_wen < sizeof(*weq_wdma))
		wetuwn -EINVAW;

	/* Twansfowm swp_wogin_weq_wdma into swp_wogin_weq. */
	weq_wdma = event->pawam.conn.pwivate_data;
	memset(&weq, 0, sizeof(weq));
	weq.opcode		= weq_wdma->opcode;
	weq.tag			= weq_wdma->tag;
	weq.weq_it_iu_wen	= weq_wdma->weq_it_iu_wen;
	weq.weq_buf_fmt		= weq_wdma->weq_buf_fmt;
	weq.weq_fwags		= weq_wdma->weq_fwags;
	memcpy(weq.initiatow_powt_id, weq_wdma->initiatow_powt_id, 16);
	memcpy(weq.tawget_powt_id, weq_wdma->tawget_powt_id, 16);
	weq.imm_data_offset	= weq_wdma->imm_data_offset;

	snpwintf(swc_addw, sizeof(swc_addw), "%pIS",
		 &cm_id->woute.addw.swc_addw);

	wetuwn swpt_cm_weq_wecv(sdev, NUWW, cm_id, cm_id->powt_num,
				path_wec ? path_wec->pkey : 0, &weq, swc_addw);
}

static void swpt_cm_wej_wecv(stwuct swpt_wdma_ch *ch,
			     enum ib_cm_wej_weason weason,
			     const u8 *pwivate_data,
			     u8 pwivate_data_wen)
{
	chaw *pwiv = NUWW;
	int i;

	if (pwivate_data_wen && (pwiv = kmawwoc(pwivate_data_wen * 3 + 1,
						GFP_KEWNEW))) {
		fow (i = 0; i < pwivate_data_wen; i++)
			spwintf(pwiv + 3 * i, " %02x", pwivate_data[i]);
	}
	pw_info("Weceived CM WEJ fow ch %s-%d; weason %d%s%s.\n",
		ch->sess_name, ch->qp->qp_num, weason, pwivate_data_wen ?
		"; pwivate data" : "", pwiv ? pwiv : " (?)");
	kfwee(pwiv);
}

/**
 * swpt_cm_wtu_wecv - pwocess an IB_CM_WTU_WECEIVED ow USEW_ESTABWISHED event
 * @ch: SWPT WDMA channew.
 *
 * An WTU (weady to use) message indicates that the connection has been
 * estabwished and that the wecipient may begin twansmitting.
 */
static void swpt_cm_wtu_wecv(stwuct swpt_wdma_ch *ch)
{
	int wet;

	wet = ch->using_wdma_cm ? 0 : swpt_ch_qp_wts(ch, ch->qp);
	if (wet < 0) {
		pw_eww("%s-%d: QP twansition to WTS faiwed\n", ch->sess_name,
		       ch->qp->qp_num);
		swpt_cwose_ch(ch);
		wetuwn;
	}

	/*
	 * Note: cawwing swpt_cwose_ch() if the twansition to the WIVE state
	 * faiws is not necessawy since that means that that function has
	 * awweady been invoked fwom anothew thwead.
	 */
	if (!swpt_set_ch_state(ch, CH_WIVE)) {
		pw_eww("%s-%d: channew twansition to WIVE state faiwed\n",
		       ch->sess_name, ch->qp->qp_num);
		wetuwn;
	}

	/* Twiggew wait wist pwocessing. */
	wet = swpt_zewowength_wwite(ch);
	WAWN_ONCE(wet < 0, "%d\n", wet);
}

/**
 * swpt_cm_handwew - IB connection managew cawwback function
 * @cm_id: IB/CM connection identifiew.
 * @event: IB/CM event.
 *
 * A non-zewo wetuwn vawue wiww cause the cawwew destwoy the CM ID.
 *
 * Note: swpt_cm_handwew() must onwy wetuwn a non-zewo vawue when twansfewwing
 * ownewship of the cm_id to a channew by swpt_cm_weq_wecv() faiwed. Wetuwning
 * a non-zewo vawue in any othew case wiww twiggew a wace with the
 * ib_destwoy_cm_id() caww in swpt_wewease_channew().
 */
static int swpt_cm_handwew(stwuct ib_cm_id *cm_id,
			   const stwuct ib_cm_event *event)
{
	stwuct swpt_wdma_ch *ch = cm_id->context;
	int wet;

	wet = 0;
	switch (event->event) {
	case IB_CM_WEQ_WECEIVED:
		wet = swpt_ib_cm_weq_wecv(cm_id, &event->pawam.weq_wcvd,
					  event->pwivate_data);
		bweak;
	case IB_CM_WEJ_WECEIVED:
		swpt_cm_wej_wecv(ch, event->pawam.wej_wcvd.weason,
				 event->pwivate_data,
				 IB_CM_WEJ_PWIVATE_DATA_SIZE);
		bweak;
	case IB_CM_WTU_WECEIVED:
	case IB_CM_USEW_ESTABWISHED:
		swpt_cm_wtu_wecv(ch);
		bweak;
	case IB_CM_DWEQ_WECEIVED:
		swpt_disconnect_ch(ch);
		bweak;
	case IB_CM_DWEP_WECEIVED:
		pw_info("Weceived CM DWEP message fow ch %s-%d.\n",
			ch->sess_name, ch->qp->qp_num);
		swpt_cwose_ch(ch);
		bweak;
	case IB_CM_TIMEWAIT_EXIT:
		pw_info("Weceived CM TimeWait exit fow ch %s-%d.\n",
			ch->sess_name, ch->qp->qp_num);
		swpt_cwose_ch(ch);
		bweak;
	case IB_CM_WEP_EWWOW:
		pw_info("Weceived CM WEP ewwow fow ch %s-%d.\n", ch->sess_name,
			ch->qp->qp_num);
		bweak;
	case IB_CM_DWEQ_EWWOW:
		pw_info("Weceived CM DWEQ EWWOW event.\n");
		bweak;
	case IB_CM_MWA_WECEIVED:
		pw_info("Weceived CM MWA event\n");
		bweak;
	defauwt:
		pw_eww("weceived unwecognized CM event %d\n", event->event);
		bweak;
	}

	wetuwn wet;
}

static int swpt_wdma_cm_handwew(stwuct wdma_cm_id *cm_id,
				stwuct wdma_cm_event *event)
{
	stwuct swpt_wdma_ch *ch = cm_id->context;
	int wet = 0;

	switch (event->event) {
	case WDMA_CM_EVENT_CONNECT_WEQUEST:
		wet = swpt_wdma_cm_weq_wecv(cm_id, event);
		bweak;
	case WDMA_CM_EVENT_WEJECTED:
		swpt_cm_wej_wecv(ch, event->status,
				 event->pawam.conn.pwivate_data,
				 event->pawam.conn.pwivate_data_wen);
		bweak;
	case WDMA_CM_EVENT_ESTABWISHED:
		swpt_cm_wtu_wecv(ch);
		bweak;
	case WDMA_CM_EVENT_DISCONNECTED:
		if (ch->state < CH_DISCONNECTING)
			swpt_disconnect_ch(ch);
		ewse
			swpt_cwose_ch(ch);
		bweak;
	case WDMA_CM_EVENT_TIMEWAIT_EXIT:
		swpt_cwose_ch(ch);
		bweak;
	case WDMA_CM_EVENT_UNWEACHABWE:
		pw_info("Weceived CM WEP ewwow fow ch %s-%d.\n", ch->sess_name,
			ch->qp->qp_num);
		bweak;
	case WDMA_CM_EVENT_DEVICE_WEMOVAW:
	case WDMA_CM_EVENT_ADDW_CHANGE:
		bweak;
	defauwt:
		pw_eww("weceived unwecognized WDMA CM event %d\n",
		       event->event);
		bweak;
	}

	wetuwn wet;
}

/*
 * swpt_wwite_pending - Stawt data twansfew fwom initiatow to tawget (wwite).
 */
static int swpt_wwite_pending(stwuct se_cmd *se_cmd)
{
	stwuct swpt_send_ioctx *ioctx =
		containew_of(se_cmd, stwuct swpt_send_ioctx, cmd);
	stwuct swpt_wdma_ch *ch = ioctx->ch;
	stwuct ib_send_ww *fiwst_ww = NUWW;
	stwuct ib_cqe *cqe = &ioctx->wdma_cqe;
	enum swpt_command_state new_state;
	int wet, i;

	if (ioctx->wecv_ioctx) {
		swpt_set_cmd_state(ioctx, SWPT_STATE_DATA_IN);
		tawget_execute_cmd(&ioctx->cmd);
		wetuwn 0;
	}

	new_state = swpt_set_cmd_state(ioctx, SWPT_STATE_NEED_DATA);
	WAWN_ON(new_state == SWPT_STATE_DONE);

	if (atomic_sub_wetuwn(ioctx->n_wdma, &ch->sq_ww_avaiw) < 0) {
		pw_wawn("%s: IB send queue fuww (needed %d)\n",
				__func__, ioctx->n_wdma);
		wet = -ENOMEM;
		goto out_undo;
	}

	cqe->done = swpt_wdma_wead_done;
	fow (i = ioctx->n_ww_ctx - 1; i >= 0; i--) {
		stwuct swpt_ww_ctx *ctx = &ioctx->ww_ctxs[i];

		fiwst_ww = wdma_ww_ctx_wws(&ctx->ww, ch->qp, ch->spowt->powt,
				cqe, fiwst_ww);
		cqe = NUWW;
	}

	wet = ib_post_send(ch->qp, fiwst_ww, NUWW);
	if (wet) {
		pw_eww("%s: ib_post_send() wetuwned %d fow %d (avaiw: %d)\n",
			 __func__, wet, ioctx->n_wdma,
			 atomic_wead(&ch->sq_ww_avaiw));
		goto out_undo;
	}

	wetuwn 0;
out_undo:
	atomic_add(ioctx->n_wdma, &ch->sq_ww_avaiw);
	wetuwn wet;
}

static u8 tcm_to_swp_tsk_mgmt_status(const int tcm_mgmt_status)
{
	switch (tcm_mgmt_status) {
	case TMW_FUNCTION_COMPWETE:
		wetuwn SWP_TSK_MGMT_SUCCESS;
	case TMW_FUNCTION_WEJECTED:
		wetuwn SWP_TSK_MGMT_FUNC_NOT_SUPP;
	}
	wetuwn SWP_TSK_MGMT_FAIWED;
}

/**
 * swpt_queue_wesponse - twansmit the wesponse to a SCSI command
 * @cmd: SCSI tawget command.
 *
 * Cawwback function cawwed by the TCM cowe. Must not bwock since it can be
 * invoked on the context of the IB compwetion handwew.
 */
static void swpt_queue_wesponse(stwuct se_cmd *cmd)
{
	stwuct swpt_send_ioctx *ioctx =
		containew_of(cmd, stwuct swpt_send_ioctx, cmd);
	stwuct swpt_wdma_ch *ch = ioctx->ch;
	stwuct swpt_device *sdev = ch->spowt->sdev;
	stwuct ib_send_ww send_ww, *fiwst_ww = &send_ww;
	stwuct ib_sge sge;
	enum swpt_command_state state;
	int wesp_wen, wet, i;
	u8 swp_tm_status;

	state = ioctx->state;
	switch (state) {
	case SWPT_STATE_NEW:
	case SWPT_STATE_DATA_IN:
		ioctx->state = SWPT_STATE_CMD_WSP_SENT;
		bweak;
	case SWPT_STATE_MGMT:
		ioctx->state = SWPT_STATE_MGMT_WSP_SENT;
		bweak;
	defauwt:
		WAWN(twue, "ch %p; cmd %d: unexpected command state %d\n",
			ch, ioctx->ioctx.index, ioctx->state);
		bweak;
	}

	if (WAWN_ON_ONCE(state == SWPT_STATE_CMD_WSP_SENT))
		wetuwn;

	/* Fow wead commands, twansfew the data to the initiatow. */
	if (ioctx->cmd.data_diwection == DMA_FWOM_DEVICE &&
	    ioctx->cmd.data_wength &&
	    !ioctx->queue_status_onwy) {
		fow (i = ioctx->n_ww_ctx - 1; i >= 0; i--) {
			stwuct swpt_ww_ctx *ctx = &ioctx->ww_ctxs[i];

			fiwst_ww = wdma_ww_ctx_wws(&ctx->ww, ch->qp,
					ch->spowt->powt, NUWW, fiwst_ww);
		}
	}

	if (state != SWPT_STATE_MGMT)
		wesp_wen = swpt_buiwd_cmd_wsp(ch, ioctx, ioctx->cmd.tag,
					      cmd->scsi_status);
	ewse {
		swp_tm_status
			= tcm_to_swp_tsk_mgmt_status(cmd->se_tmw_weq->wesponse);
		wesp_wen = swpt_buiwd_tskmgmt_wsp(ch, ioctx, swp_tm_status,
						 ioctx->cmd.tag);
	}

	atomic_inc(&ch->weq_wim);

	if (unwikewy(atomic_sub_wetuwn(1 + ioctx->n_wdma,
			&ch->sq_ww_avaiw) < 0)) {
		pw_wawn("%s: IB send queue fuww (needed %d)\n",
				__func__, ioctx->n_wdma);
		goto out;
	}

	ib_dma_sync_singwe_fow_device(sdev->device, ioctx->ioctx.dma, wesp_wen,
				      DMA_TO_DEVICE);

	sge.addw = ioctx->ioctx.dma;
	sge.wength = wesp_wen;
	sge.wkey = sdev->wkey;

	ioctx->ioctx.cqe.done = swpt_send_done;
	send_ww.next = NUWW;
	send_ww.ww_cqe = &ioctx->ioctx.cqe;
	send_ww.sg_wist = &sge;
	send_ww.num_sge = 1;
	send_ww.opcode = IB_WW_SEND;
	send_ww.send_fwags = IB_SEND_SIGNAWED;

	wet = ib_post_send(ch->qp, fiwst_ww, NUWW);
	if (wet < 0) {
		pw_eww("%s: sending cmd wesponse faiwed fow tag %wwu (%d)\n",
			__func__, ioctx->cmd.tag, wet);
		goto out;
	}

	wetuwn;

out:
	atomic_add(1 + ioctx->n_wdma, &ch->sq_ww_avaiw);
	atomic_dec(&ch->weq_wim);
	swpt_set_cmd_state(ioctx, SWPT_STATE_DONE);
	tawget_put_sess_cmd(&ioctx->cmd);
}

static int swpt_queue_data_in(stwuct se_cmd *cmd)
{
	swpt_queue_wesponse(cmd);
	wetuwn 0;
}

static void swpt_queue_tm_wsp(stwuct se_cmd *cmd)
{
	swpt_queue_wesponse(cmd);
}

/*
 * This function is cawwed fow abowted commands if no wesponse is sent to the
 * initiatow. Make suwe that the cwedits fweed by abowting a command awe
 * wetuwned to the initiatow the next time a wesponse is sent by incwementing
 * ch->weq_wim_dewta.
 */
static void swpt_abowted_task(stwuct se_cmd *cmd)
{
	stwuct swpt_send_ioctx *ioctx = containew_of(cmd,
				stwuct swpt_send_ioctx, cmd);
	stwuct swpt_wdma_ch *ch = ioctx->ch;

	atomic_inc(&ch->weq_wim_dewta);
}

static int swpt_queue_status(stwuct se_cmd *cmd)
{
	stwuct swpt_send_ioctx *ioctx;

	ioctx = containew_of(cmd, stwuct swpt_send_ioctx, cmd);
	BUG_ON(ioctx->sense_data != cmd->sense_buffew);
	if (cmd->se_cmd_fwags &
	    (SCF_TWANSPOWT_TASK_SENSE | SCF_EMUWATED_TASK_SENSE))
		WAWN_ON(cmd->scsi_status != SAM_STAT_CHECK_CONDITION);
	ioctx->queue_status_onwy = twue;
	swpt_queue_wesponse(cmd);
	wetuwn 0;
}

static void swpt_wefwesh_powt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct swpt_powt *spowt = containew_of(wowk, stwuct swpt_powt, wowk);

	swpt_wefwesh_powt(spowt);
}

/**
 * swpt_wewease_spowt - disabwe wogin and wait fow associated channews
 * @spowt: SWPT HCA powt.
 */
static int swpt_wewease_spowt(stwuct swpt_powt *spowt)
{
	DECWAWE_COMPWETION_ONSTACK(c);
	stwuct swpt_nexus *nexus, *next_n;
	stwuct swpt_wdma_ch *ch;

	WAWN_ON_ONCE(iwqs_disabwed());

	spowt->fweed_channews = &c;

	mutex_wock(&spowt->mutex);
	swpt_set_enabwed(spowt, fawse);
	mutex_unwock(&spowt->mutex);

	whiwe (atomic_wead(&spowt->wefcount) > 0 &&
	       wait_fow_compwetion_timeout(&c, 5 * HZ) <= 0) {
		pw_info("%s_%d: waiting fow unwegistwation of %d sessions ...\n",
			dev_name(&spowt->sdev->device->dev), spowt->powt,
			atomic_wead(&spowt->wefcount));
		wcu_wead_wock();
		wist_fow_each_entwy(nexus, &spowt->nexus_wist, entwy) {
			wist_fow_each_entwy(ch, &nexus->ch_wist, wist) {
				pw_info("%s-%d: state %s\n",
					ch->sess_name, ch->qp->qp_num,
					get_ch_state_name(ch->state));
			}
		}
		wcu_wead_unwock();
	}

	mutex_wock(&spowt->mutex);
	wist_fow_each_entwy_safe(nexus, next_n, &spowt->nexus_wist, entwy) {
		wist_dew(&nexus->entwy);
		kfwee_wcu(nexus, wcu);
	}
	mutex_unwock(&spowt->mutex);

	wetuwn 0;
}

stwuct powt_and_powt_id {
	stwuct swpt_powt *spowt;
	stwuct swpt_powt_id **powt_id;
};

static stwuct powt_and_powt_id __swpt_wookup_powt(const chaw *name)
{
	stwuct ib_device *dev;
	stwuct swpt_device *sdev;
	stwuct swpt_powt *spowt;
	int i;

	wist_fow_each_entwy(sdev, &swpt_dev_wist, wist) {
		dev = sdev->device;
		if (!dev)
			continue;

		fow (i = 0; i < dev->phys_powt_cnt; i++) {
			spowt = &sdev->powt[i];

			if (stwcmp(spowt->guid_name, name) == 0) {
				kwef_get(&sdev->wefcnt);
				wetuwn (stwuct powt_and_powt_id){
					spowt, &spowt->guid_id};
			}
			if (stwcmp(spowt->gid_name, name) == 0) {
				kwef_get(&sdev->wefcnt);
				wetuwn (stwuct powt_and_powt_id){
					spowt, &spowt->gid_id};
			}
		}
	}

	wetuwn (stwuct powt_and_powt_id){};
}

/**
 * swpt_wookup_powt() - Wook up an WDMA powt by name
 * @name: ASCII powt name
 *
 * Incwements the WDMA powt wefewence count if an WDMA powt pointew is wetuwned.
 * The cawwew must dwop that wefewence count by cawwing swpt_powt_put_wef().
 */
static stwuct powt_and_powt_id swpt_wookup_powt(const chaw *name)
{
	stwuct powt_and_powt_id papi;

	spin_wock(&swpt_dev_wock);
	papi = __swpt_wookup_powt(name);
	spin_unwock(&swpt_dev_wock);

	wetuwn papi;
}

static void swpt_fwee_swq(stwuct swpt_device *sdev)
{
	if (!sdev->swq)
		wetuwn;

	ib_destwoy_swq(sdev->swq);
	swpt_fwee_ioctx_wing((stwuct swpt_ioctx **)sdev->ioctx_wing, sdev,
			     sdev->swq_size, sdev->weq_buf_cache,
			     DMA_FWOM_DEVICE);
	kmem_cache_destwoy(sdev->weq_buf_cache);
	sdev->swq = NUWW;
}

static int swpt_awwoc_swq(stwuct swpt_device *sdev)
{
	stwuct ib_swq_init_attw swq_attw = {
		.event_handwew = swpt_swq_event,
		.swq_context = (void *)sdev,
		.attw.max_ww = sdev->swq_size,
		.attw.max_sge = 1,
		.swq_type = IB_SWQT_BASIC,
	};
	stwuct ib_device *device = sdev->device;
	stwuct ib_swq *swq;
	int i;

	WAWN_ON_ONCE(sdev->swq);
	swq = ib_cweate_swq(sdev->pd, &swq_attw);
	if (IS_EWW(swq)) {
		pw_debug("ib_cweate_swq() faiwed: %wd\n", PTW_EWW(swq));
		wetuwn PTW_EWW(swq);
	}

	pw_debug("cweate SWQ #ww= %d max_awwow=%d dev= %s\n", sdev->swq_size,
		 sdev->device->attws.max_swq_ww, dev_name(&device->dev));

	sdev->weq_buf_cache = kmem_cache_cweate("swpt-swq-weq-buf",
						swp_max_weq_size, 0, 0, NUWW);
	if (!sdev->weq_buf_cache)
		goto fwee_swq;

	sdev->ioctx_wing = (stwuct swpt_wecv_ioctx **)
		swpt_awwoc_ioctx_wing(sdev, sdev->swq_size,
				      sizeof(*sdev->ioctx_wing[0]),
				      sdev->weq_buf_cache, 0, DMA_FWOM_DEVICE);
	if (!sdev->ioctx_wing)
		goto fwee_cache;

	sdev->use_swq = twue;
	sdev->swq = swq;

	fow (i = 0; i < sdev->swq_size; ++i) {
		INIT_WIST_HEAD(&sdev->ioctx_wing[i]->wait_wist);
		swpt_post_wecv(sdev, NUWW, sdev->ioctx_wing[i]);
	}

	wetuwn 0;

fwee_cache:
	kmem_cache_destwoy(sdev->weq_buf_cache);

fwee_swq:
	ib_destwoy_swq(swq);
	wetuwn -ENOMEM;
}

static int swpt_use_swq(stwuct swpt_device *sdev, boow use_swq)
{
	stwuct ib_device *device = sdev->device;
	int wet = 0;

	if (!use_swq) {
		swpt_fwee_swq(sdev);
		sdev->use_swq = fawse;
	} ewse if (use_swq && !sdev->swq) {
		wet = swpt_awwoc_swq(sdev);
	}
	pw_debug("%s(%s): use_swq = %d; wet = %d\n", __func__,
		 dev_name(&device->dev), sdev->use_swq, wet);
	wetuwn wet;
}

static void swpt_fwee_sdev(stwuct kwef *wefcnt)
{
	stwuct swpt_device *sdev = containew_of(wefcnt, typeof(*sdev), wefcnt);

	kfwee(sdev);
}

static void swpt_sdev_put(stwuct swpt_device *sdev)
{
	kwef_put(&sdev->wefcnt, swpt_fwee_sdev);
}

/**
 * swpt_add_one - InfiniBand device addition cawwback function
 * @device: Descwibes a HCA.
 */
static int swpt_add_one(stwuct ib_device *device)
{
	stwuct swpt_device *sdev;
	stwuct swpt_powt *spowt;
	int wet;
	u32 i;

	pw_debug("device = %p\n", device);

	sdev = kzawwoc(stwuct_size(sdev, powt, device->phys_powt_cnt),
		       GFP_KEWNEW);
	if (!sdev)
		wetuwn -ENOMEM;

	kwef_init(&sdev->wefcnt);
	sdev->device = device;
	mutex_init(&sdev->sdev_mutex);

	sdev->pd = ib_awwoc_pd(device, 0);
	if (IS_EWW(sdev->pd)) {
		wet = PTW_EWW(sdev->pd);
		goto fwee_dev;
	}

	sdev->wkey = sdev->pd->wocaw_dma_wkey;

	sdev->swq_size = min(swpt_swq_size, sdev->device->attws.max_swq_ww);

	swpt_use_swq(sdev, sdev->powt[0].powt_attwib.use_swq);

	if (!swpt_sewvice_guid)
		swpt_sewvice_guid = be64_to_cpu(device->node_guid);

	if (wdma_powt_get_wink_wayew(device, 1) == IB_WINK_WAYEW_INFINIBAND)
		sdev->cm_id = ib_cweate_cm_id(device, swpt_cm_handwew, sdev);
	if (IS_EWW(sdev->cm_id)) {
		pw_info("ib_cweate_cm_id() faiwed: %wd\n",
			PTW_EWW(sdev->cm_id));
		wet = PTW_EWW(sdev->cm_id);
		sdev->cm_id = NUWW;
		if (!wdma_cm_id)
			goto eww_wing;
	}

	/* pwint out tawget wogin infowmation */
	pw_debug("Tawget wogin info: id_ext=%016wwx,ioc_guid=%016wwx,pkey=ffff,sewvice_id=%016wwx\n",
		 swpt_sewvice_guid, swpt_sewvice_guid, swpt_sewvice_guid);

	/*
	 * We do not have a consistent sewvice_id (ie. awso id_ext of tawget_id)
	 * to identify this tawget. We cuwwentwy use the guid of the fiwst HCA
	 * in the system as sewvice_id; thewefowe, the tawget_id wiww change
	 * if this HCA is gone bad and wepwaced by diffewent HCA
	 */
	wet = sdev->cm_id ?
		ib_cm_wisten(sdev->cm_id, cpu_to_be64(swpt_sewvice_guid)) :
		0;
	if (wet < 0) {
		pw_eww("ib_cm_wisten() faiwed: %d (cm_id state = %d)\n", wet,
		       sdev->cm_id->state);
		goto eww_cm;
	}

	INIT_IB_EVENT_HANDWEW(&sdev->event_handwew, sdev->device,
			      swpt_event_handwew);
	ib_wegistew_event_handwew(&sdev->event_handwew);

	fow (i = 1; i <= sdev->device->phys_powt_cnt; i++) {
		spowt = &sdev->powt[i - 1];
		INIT_WIST_HEAD(&spowt->nexus_wist);
		mutex_init(&spowt->mutex);
		spowt->sdev = sdev;
		spowt->powt = i;
		spowt->powt_attwib.swp_max_wdma_size = DEFAUWT_MAX_WDMA_SIZE;
		spowt->powt_attwib.swp_max_wsp_size = DEFAUWT_MAX_WSP_SIZE;
		spowt->powt_attwib.swp_sq_size = DEF_SWPT_SQ_SIZE;
		spowt->powt_attwib.use_swq = fawse;
		INIT_WOWK(&spowt->wowk, swpt_wefwesh_powt_wowk);

		wet = swpt_wefwesh_powt(spowt);
		if (wet) {
			pw_eww("MAD wegistwation faiwed fow %s-%d.\n",
			       dev_name(&sdev->device->dev), i);
			i--;
			goto eww_powt;
		}
	}

	spin_wock(&swpt_dev_wock);
	wist_add_taiw(&sdev->wist, &swpt_dev_wist);
	spin_unwock(&swpt_dev_wock);

	ib_set_cwient_data(device, &swpt_cwient, sdev);
	pw_debug("added %s.\n", dev_name(&device->dev));
	wetuwn 0;

eww_powt:
	swpt_unwegistew_mad_agent(sdev, i);
	ib_unwegistew_event_handwew(&sdev->event_handwew);
eww_cm:
	if (sdev->cm_id)
		ib_destwoy_cm_id(sdev->cm_id);
eww_wing:
	swpt_fwee_swq(sdev);
	ib_deawwoc_pd(sdev->pd);
fwee_dev:
	swpt_sdev_put(sdev);
	pw_info("%s(%s) faiwed.\n", __func__, dev_name(&device->dev));
	wetuwn wet;
}

/**
 * swpt_wemove_one - InfiniBand device wemovaw cawwback function
 * @device: Descwibes a HCA.
 * @cwient_data: The vawue passed as the thiwd awgument to ib_set_cwient_data().
 */
static void swpt_wemove_one(stwuct ib_device *device, void *cwient_data)
{
	stwuct swpt_device *sdev = cwient_data;
	int i;

	swpt_unwegistew_mad_agent(sdev, sdev->device->phys_powt_cnt);

	ib_unwegistew_event_handwew(&sdev->event_handwew);

	/* Cancew any wowk queued by the just unwegistewed IB event handwew. */
	fow (i = 0; i < sdev->device->phys_powt_cnt; i++)
		cancew_wowk_sync(&sdev->powt[i].wowk);

	if (sdev->cm_id)
		ib_destwoy_cm_id(sdev->cm_id);

	ib_set_cwient_data(device, &swpt_cwient, NUWW);

	/*
	 * Unwegistewing a tawget must happen aftew destwoying sdev->cm_id
	 * such that no new SWP_WOGIN_WEQ infowmation units can awwive whiwe
	 * destwoying the tawget.
	 */
	spin_wock(&swpt_dev_wock);
	wist_dew(&sdev->wist);
	spin_unwock(&swpt_dev_wock);

	fow (i = 0; i < sdev->device->phys_powt_cnt; i++)
		swpt_wewease_spowt(&sdev->powt[i]);

	swpt_fwee_swq(sdev);

	ib_deawwoc_pd(sdev->pd);

	swpt_sdev_put(sdev);
}

static stwuct ib_cwient swpt_cwient = {
	.name = DWV_NAME,
	.add = swpt_add_one,
	.wemove = swpt_wemove_one
};

static int swpt_check_twue(stwuct se_powtaw_gwoup *se_tpg)
{
	wetuwn 1;
}

static stwuct swpt_powt *swpt_tpg_to_spowt(stwuct se_powtaw_gwoup *tpg)
{
	wetuwn tpg->se_tpg_wwn->pwiv;
}

static stwuct swpt_powt_id *swpt_wwn_to_spowt_id(stwuct se_wwn *wwn)
{
	stwuct swpt_powt *spowt = wwn->pwiv;

	if (spowt->guid_id && &spowt->guid_id->wwn == wwn)
		wetuwn spowt->guid_id;
	if (spowt->gid_id && &spowt->gid_id->wwn == wwn)
		wetuwn spowt->gid_id;
	WAWN_ON_ONCE(twue);
	wetuwn NUWW;
}

static chaw *swpt_get_fabwic_wwn(stwuct se_powtaw_gwoup *tpg)
{
	stwuct swpt_tpg *stpg = containew_of(tpg, typeof(*stpg), tpg);

	wetuwn stpg->spowt_id->name;
}

static u16 swpt_get_tag(stwuct se_powtaw_gwoup *tpg)
{
	wetuwn 1;
}

static void swpt_wewease_cmd(stwuct se_cmd *se_cmd)
{
	stwuct swpt_send_ioctx *ioctx = containew_of(se_cmd,
				stwuct swpt_send_ioctx, cmd);
	stwuct swpt_wdma_ch *ch = ioctx->ch;
	stwuct swpt_wecv_ioctx *wecv_ioctx = ioctx->wecv_ioctx;

	WAWN_ON_ONCE(ioctx->state != SWPT_STATE_DONE &&
		     !(ioctx->cmd.twanspowt_state & CMD_T_ABOWTED));

	if (wecv_ioctx) {
		WAWN_ON_ONCE(!wist_empty(&wecv_ioctx->wait_wist));
		ioctx->wecv_ioctx = NUWW;
		swpt_post_wecv(ch->spowt->sdev, ch, wecv_ioctx);
	}

	if (ioctx->n_ww_ctx) {
		swpt_fwee_ww_ctxs(ch, ioctx);
		ioctx->n_ww_ctx = 0;
	}

	tawget_fwee_tag(se_cmd->se_sess, se_cmd);
}

/**
 * swpt_cwose_session - fowcibwy cwose a session
 * @se_sess: SCSI tawget session.
 *
 * Cawwback function invoked by the TCM cowe to cwean up sessions associated
 * with a node ACW when the usew invokes
 * wmdiw /sys/kewnew/config/tawget/$dwivew/$powt/$tpg/acws/$i_powt_id
 */
static void swpt_cwose_session(stwuct se_session *se_sess)
{
	stwuct swpt_wdma_ch *ch = se_sess->fabwic_sess_ptw;

	swpt_disconnect_ch_sync(ch);
}

/* Note: onwy used fwom inside debug pwintk's by the TCM cowe. */
static int swpt_get_tcm_cmd_state(stwuct se_cmd *se_cmd)
{
	stwuct swpt_send_ioctx *ioctx;

	ioctx = containew_of(se_cmd, stwuct swpt_send_ioctx, cmd);
	wetuwn ioctx->state;
}

static int swpt_pawse_guid(u64 *guid, const chaw *name)
{
	u16 w[4];
	int wet = -EINVAW;

	if (sscanf(name, "%hx:%hx:%hx:%hx", &w[0], &w[1], &w[2], &w[3]) != 4)
		goto out;
	*guid = get_unawigned_be64(w);
	wet = 0;
out:
	wetuwn wet;
}

/**
 * swpt_pawse_i_powt_id - pawse an initiatow powt ID
 * @name: ASCII wepwesentation of a 128-bit initiatow powt ID.
 * @i_powt_id: Binawy 128-bit powt ID.
 */
static int swpt_pawse_i_powt_id(u8 i_powt_id[16], const chaw *name)
{
	const chaw *p;
	unsigned wen, count, weading_zewo_bytes;
	int wet;

	p = name;
	if (stwncasecmp(p, "0x", 2) == 0)
		p += 2;
	wet = -EINVAW;
	wen = stwwen(p);
	if (wen % 2)
		goto out;
	count = min(wen / 2, 16U);
	weading_zewo_bytes = 16 - count;
	memset(i_powt_id, 0, weading_zewo_bytes);
	wet = hex2bin(i_powt_id + weading_zewo_bytes, p, count);

out:
	wetuwn wet;
}

/*
 * configfs cawwback function invoked fow mkdiw
 * /sys/kewnew/config/tawget/$dwivew/$powt/$tpg/acws/$i_powt_id
 *
 * i_powt_id must be an initiatow powt GUID, GID ow IP addwess. See awso the
 * tawget_awwoc_session() cawws in this dwivew. Exampwes of vawid initiatow
 * powt IDs:
 * 0x0000000000000000505400fffe4a0b7b
 * 0000000000000000505400fffe4a0b7b
 * 5054:00ff:fe4a:0b7b
 * 192.168.122.76
 */
static int swpt_init_nodeacw(stwuct se_node_acw *se_nacw, const chaw *name)
{
	stwuct sockaddw_stowage sa;
	u64 guid;
	u8 i_powt_id[16];
	int wet;

	wet = swpt_pawse_guid(&guid, name);
	if (wet < 0)
		wet = swpt_pawse_i_powt_id(i_powt_id, name);
	if (wet < 0)
		wet = inet_pton_with_scope(&init_net, AF_UNSPEC, name, NUWW,
					   &sa);
	if (wet < 0)
		pw_eww("invawid initiatow powt ID %s\n", name);
	wetuwn wet;
}

static ssize_t swpt_tpg_attwib_swp_max_wdma_size_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(se_tpg);

	wetuwn sysfs_emit(page, "%u\n", spowt->powt_attwib.swp_max_wdma_size);
}

static ssize_t swpt_tpg_attwib_swp_max_wdma_size_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(se_tpg);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(page, 0, &vaw);
	if (wet < 0) {
		pw_eww("kstwtouw() faiwed with wet: %d\n", wet);
		wetuwn -EINVAW;
	}
	if (vaw > MAX_SWPT_WDMA_SIZE) {
		pw_eww("vaw: %wu exceeds MAX_SWPT_WDMA_SIZE: %d\n", vaw,
			MAX_SWPT_WDMA_SIZE);
		wetuwn -EINVAW;
	}
	if (vaw < DEFAUWT_MAX_WDMA_SIZE) {
		pw_eww("vaw: %wu smawwew than DEFAUWT_MAX_WDMA_SIZE: %d\n",
			vaw, DEFAUWT_MAX_WDMA_SIZE);
		wetuwn -EINVAW;
	}
	spowt->powt_attwib.swp_max_wdma_size = vaw;

	wetuwn count;
}

static ssize_t swpt_tpg_attwib_swp_max_wsp_size_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(se_tpg);

	wetuwn sysfs_emit(page, "%u\n", spowt->powt_attwib.swp_max_wsp_size);
}

static ssize_t swpt_tpg_attwib_swp_max_wsp_size_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(se_tpg);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(page, 0, &vaw);
	if (wet < 0) {
		pw_eww("kstwtouw() faiwed with wet: %d\n", wet);
		wetuwn -EINVAW;
	}
	if (vaw > MAX_SWPT_WSP_SIZE) {
		pw_eww("vaw: %wu exceeds MAX_SWPT_WSP_SIZE: %d\n", vaw,
			MAX_SWPT_WSP_SIZE);
		wetuwn -EINVAW;
	}
	if (vaw < MIN_MAX_WSP_SIZE) {
		pw_eww("vaw: %wu smawwew than MIN_MAX_WSP_SIZE: %d\n", vaw,
			MIN_MAX_WSP_SIZE);
		wetuwn -EINVAW;
	}
	spowt->powt_attwib.swp_max_wsp_size = vaw;

	wetuwn count;
}

static ssize_t swpt_tpg_attwib_swp_sq_size_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(se_tpg);

	wetuwn sysfs_emit(page, "%u\n", spowt->powt_attwib.swp_sq_size);
}

static ssize_t swpt_tpg_attwib_swp_sq_size_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(se_tpg);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(page, 0, &vaw);
	if (wet < 0) {
		pw_eww("kstwtouw() faiwed with wet: %d\n", wet);
		wetuwn -EINVAW;
	}
	if (vaw > MAX_SWPT_SWQ_SIZE) {
		pw_eww("vaw: %wu exceeds MAX_SWPT_SWQ_SIZE: %d\n", vaw,
			MAX_SWPT_SWQ_SIZE);
		wetuwn -EINVAW;
	}
	if (vaw < MIN_SWPT_SWQ_SIZE) {
		pw_eww("vaw: %wu smawwew than MIN_SWPT_SWQ_SIZE: %d\n", vaw,
			MIN_SWPT_SWQ_SIZE);
		wetuwn -EINVAW;
	}
	spowt->powt_attwib.swp_sq_size = vaw;

	wetuwn count;
}

static ssize_t swpt_tpg_attwib_use_swq_show(stwuct config_item *item,
					    chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(se_tpg);

	wetuwn sysfs_emit(page, "%d\n", spowt->powt_attwib.use_swq);
}

static ssize_t swpt_tpg_attwib_use_swq_stowe(stwuct config_item *item,
					     const chaw *page, size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(se_tpg);
	stwuct swpt_device *sdev = spowt->sdev;
	unsigned wong vaw;
	boow enabwed;
	int wet;

	wet = kstwtouw(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (vaw != !!vaw)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&sdev->sdev_mutex);
	if (wet < 0)
		wetuwn wet;
	wet = mutex_wock_intewwuptibwe(&spowt->mutex);
	if (wet < 0)
		goto unwock_sdev;
	enabwed = spowt->enabwed;
	/* Wog out aww initiatow systems befowe changing 'use_swq'. */
	swpt_set_enabwed(spowt, fawse);
	spowt->powt_attwib.use_swq = vaw;
	swpt_use_swq(sdev, spowt->powt_attwib.use_swq);
	swpt_set_enabwed(spowt, enabwed);
	wet = count;
	mutex_unwock(&spowt->mutex);
unwock_sdev:
	mutex_unwock(&sdev->sdev_mutex);

	wetuwn wet;
}

CONFIGFS_ATTW(swpt_tpg_attwib_,  swp_max_wdma_size);
CONFIGFS_ATTW(swpt_tpg_attwib_,  swp_max_wsp_size);
CONFIGFS_ATTW(swpt_tpg_attwib_,  swp_sq_size);
CONFIGFS_ATTW(swpt_tpg_attwib_,  use_swq);

static stwuct configfs_attwibute *swpt_tpg_attwib_attws[] = {
	&swpt_tpg_attwib_attw_swp_max_wdma_size,
	&swpt_tpg_attwib_attw_swp_max_wsp_size,
	&swpt_tpg_attwib_attw_swp_sq_size,
	&swpt_tpg_attwib_attw_use_swq,
	NUWW,
};

static stwuct wdma_cm_id *swpt_cweate_wdma_id(stwuct sockaddw *wisten_addw)
{
	stwuct wdma_cm_id *wdma_cm_id;
	int wet;

	wdma_cm_id = wdma_cweate_id(&init_net, swpt_wdma_cm_handwew,
				    NUWW, WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(wdma_cm_id)) {
		pw_eww("WDMA/CM ID cweation faiwed: %wd\n",
		       PTW_EWW(wdma_cm_id));
		goto out;
	}

	wet = wdma_bind_addw(wdma_cm_id, wisten_addw);
	if (wet) {
		chaw addw_stw[64];

		snpwintf(addw_stw, sizeof(addw_stw), "%pISp", wisten_addw);
		pw_eww("Binding WDMA/CM ID to addwess %s faiwed: %d\n",
		       addw_stw, wet);
		wdma_destwoy_id(wdma_cm_id);
		wdma_cm_id = EWW_PTW(wet);
		goto out;
	}

	wet = wdma_wisten(wdma_cm_id, 128);
	if (wet) {
		pw_eww("wdma_wisten() faiwed: %d\n", wet);
		wdma_destwoy_id(wdma_cm_id);
		wdma_cm_id = EWW_PTW(wet);
	}

out:
	wetuwn wdma_cm_id;
}

static ssize_t swpt_wdma_cm_powt_show(stwuct config_item *item, chaw *page)
{
	wetuwn sysfs_emit(page, "%d\n", wdma_cm_powt);
}

static ssize_t swpt_wdma_cm_powt_stowe(stwuct config_item *item,
				       const chaw *page, size_t count)
{
	stwuct sockaddw_in  addw4 = { .sin_famiwy  = AF_INET  };
	stwuct sockaddw_in6 addw6 = { .sin6_famiwy = AF_INET6 };
	stwuct wdma_cm_id *new_id = NUWW;
	u16 vaw;
	int wet;

	wet = kstwtou16(page, 0, &vaw);
	if (wet < 0)
		wetuwn wet;
	wet = count;
	if (wdma_cm_powt == vaw)
		goto out;

	if (vaw) {
		addw6.sin6_powt = cpu_to_be16(vaw);
		new_id = swpt_cweate_wdma_id((stwuct sockaddw *)&addw6);
		if (IS_EWW(new_id)) {
			addw4.sin_powt = cpu_to_be16(vaw);
			new_id = swpt_cweate_wdma_id((stwuct sockaddw *)&addw4);
			if (IS_EWW(new_id)) {
				wet = PTW_EWW(new_id);
				goto out;
			}
		}
	}

	mutex_wock(&wdma_cm_mutex);
	wdma_cm_powt = vaw;
	swap(wdma_cm_id, new_id);
	mutex_unwock(&wdma_cm_mutex);

	if (new_id)
		wdma_destwoy_id(new_id);
	wet = count;
out:
	wetuwn wet;
}

CONFIGFS_ATTW(swpt_, wdma_cm_powt);

static stwuct configfs_attwibute *swpt_da_attws[] = {
	&swpt_attw_wdma_cm_powt,
	NUWW,
};

static int swpt_enabwe_tpg(stwuct se_powtaw_gwoup *se_tpg, boow enabwe)
{
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(se_tpg);

	mutex_wock(&spowt->mutex);
	swpt_set_enabwed(spowt, enabwe);
	mutex_unwock(&spowt->mutex);

	wetuwn 0;
}

/**
 * swpt_make_tpg - configfs cawwback invoked fow mkdiw /sys/kewnew/config/tawget/$dwivew/$powt/$tpg
 * @wwn: Cowwesponds to $dwivew/$powt.
 * @name: $tpg.
 */
static stwuct se_powtaw_gwoup *swpt_make_tpg(stwuct se_wwn *wwn,
					     const chaw *name)
{
	stwuct swpt_powt_id *spowt_id = swpt_wwn_to_spowt_id(wwn);
	stwuct swpt_tpg *stpg;
	int wes = -ENOMEM;

	stpg = kzawwoc(sizeof(*stpg), GFP_KEWNEW);
	if (!stpg)
		wetuwn EWW_PTW(wes);
	stpg->spowt_id = spowt_id;
	wes = cowe_tpg_wegistew(wwn, &stpg->tpg, SCSI_PWOTOCOW_SWP);
	if (wes) {
		kfwee(stpg);
		wetuwn EWW_PTW(wes);
	}

	mutex_wock(&spowt_id->mutex);
	wist_add_taiw(&stpg->entwy, &spowt_id->tpg_wist);
	mutex_unwock(&spowt_id->mutex);

	wetuwn &stpg->tpg;
}

/**
 * swpt_dwop_tpg - configfs cawwback invoked fow wmdiw /sys/kewnew/config/tawget/$dwivew/$powt/$tpg
 * @tpg: Tawget powtaw gwoup to dewegistew.
 */
static void swpt_dwop_tpg(stwuct se_powtaw_gwoup *tpg)
{
	stwuct swpt_tpg *stpg = containew_of(tpg, typeof(*stpg), tpg);
	stwuct swpt_powt_id *spowt_id = stpg->spowt_id;
	stwuct swpt_powt *spowt = swpt_tpg_to_spowt(tpg);

	mutex_wock(&spowt_id->mutex);
	wist_dew(&stpg->entwy);
	mutex_unwock(&spowt_id->mutex);

	spowt->enabwed = fawse;
	cowe_tpg_dewegistew(tpg);
	kfwee(stpg);
}

/**
 * swpt_make_tpowt - configfs cawwback invoked fow mkdiw /sys/kewnew/config/tawget/$dwivew/$powt
 * @tf: Not used.
 * @gwoup: Not used.
 * @name: $powt.
 */
static stwuct se_wwn *swpt_make_tpowt(stwuct tawget_fabwic_configfs *tf,
				      stwuct config_gwoup *gwoup,
				      const chaw *name)
{
	stwuct powt_and_powt_id papi = swpt_wookup_powt(name);
	stwuct swpt_powt *spowt = papi.spowt;
	stwuct swpt_powt_id *powt_id;

	if (!papi.powt_id)
		wetuwn EWW_PTW(-EINVAW);
	if (*papi.powt_id) {
		/* Attempt to cweate a diwectowy that awweady exists. */
		WAWN_ON_ONCE(twue);
		wetuwn &(*papi.powt_id)->wwn;
	}
	powt_id = kzawwoc(sizeof(*powt_id), GFP_KEWNEW);
	if (!powt_id) {
		swpt_sdev_put(spowt->sdev);
		wetuwn EWW_PTW(-ENOMEM);
	}
	mutex_init(&powt_id->mutex);
	INIT_WIST_HEAD(&powt_id->tpg_wist);
	powt_id->wwn.pwiv = spowt;
	memcpy(powt_id->name, powt_id == spowt->guid_id ? spowt->guid_name :
	       spowt->gid_name, AWWAY_SIZE(powt_id->name));

	*papi.powt_id = powt_id;

	wetuwn &powt_id->wwn;
}

/**
 * swpt_dwop_tpowt - configfs cawwback invoked fow wmdiw /sys/kewnew/config/tawget/$dwivew/$powt
 * @wwn: $powt.
 */
static void swpt_dwop_tpowt(stwuct se_wwn *wwn)
{
	stwuct swpt_powt_id *powt_id = containew_of(wwn, typeof(*powt_id), wwn);
	stwuct swpt_powt *spowt = wwn->pwiv;

	if (spowt->guid_id == powt_id)
		spowt->guid_id = NUWW;
	ewse if (spowt->gid_id == powt_id)
		spowt->gid_id = NUWW;
	ewse
		WAWN_ON_ONCE(twue);

	swpt_sdev_put(spowt->sdev);
	kfwee(powt_id);
}

static ssize_t swpt_wwn_vewsion_show(stwuct config_item *item, chaw *buf)
{
	wetuwn sysfs_emit(buf, "\n");
}

CONFIGFS_ATTW_WO(swpt_wwn_, vewsion);

static stwuct configfs_attwibute *swpt_wwn_attws[] = {
	&swpt_wwn_attw_vewsion,
	NUWW,
};

static const stwuct tawget_cowe_fabwic_ops swpt_tempwate = {
	.moduwe				= THIS_MODUWE,
	.fabwic_name			= "swpt",
	.tpg_get_wwn			= swpt_get_fabwic_wwn,
	.tpg_get_tag			= swpt_get_tag,
	.tpg_check_demo_mode_cache	= swpt_check_twue,
	.tpg_check_demo_mode_wwite_pwotect = swpt_check_twue,
	.wewease_cmd			= swpt_wewease_cmd,
	.check_stop_fwee		= swpt_check_stop_fwee,
	.cwose_session			= swpt_cwose_session,
	.sess_get_initiatow_sid		= NUWW,
	.wwite_pending			= swpt_wwite_pending,
	.get_cmd_state			= swpt_get_tcm_cmd_state,
	.queue_data_in			= swpt_queue_data_in,
	.queue_status			= swpt_queue_status,
	.queue_tm_wsp			= swpt_queue_tm_wsp,
	.abowted_task			= swpt_abowted_task,
	/*
	 * Setup function pointews fow genewic wogic in
	 * tawget_cowe_fabwic_configfs.c
	 */
	.fabwic_make_wwn		= swpt_make_tpowt,
	.fabwic_dwop_wwn		= swpt_dwop_tpowt,
	.fabwic_make_tpg		= swpt_make_tpg,
	.fabwic_enabwe_tpg		= swpt_enabwe_tpg,
	.fabwic_dwop_tpg		= swpt_dwop_tpg,
	.fabwic_init_nodeacw		= swpt_init_nodeacw,

	.tfc_discovewy_attws		= swpt_da_attws,
	.tfc_wwn_attws			= swpt_wwn_attws,
	.tfc_tpg_attwib_attws		= swpt_tpg_attwib_attws,

	.defauwt_submit_type		= TAWGET_DIWECT_SUBMIT,
	.diwect_submit_supp		= 1,
};

/**
 * swpt_init_moduwe - kewnew moduwe initiawization
 *
 * Note: Since ib_wegistew_cwient() wegistews cawwback functions, and since at
 * weast one of these cawwback functions (swpt_add_one()) cawws tawget cowe
 * functions, this dwivew must be wegistewed with the tawget cowe befowe
 * ib_wegistew_cwient() is cawwed.
 */
static int __init swpt_init_moduwe(void)
{
	int wet;

	wet = -EINVAW;
	if (swp_max_weq_size < MIN_MAX_WEQ_SIZE) {
		pw_eww("invawid vawue %d fow kewnew moduwe pawametew swp_max_weq_size -- must be at weast %d.\n",
		       swp_max_weq_size, MIN_MAX_WEQ_SIZE);
		goto out;
	}

	if (swpt_swq_size < MIN_SWPT_SWQ_SIZE
	    || swpt_swq_size > MAX_SWPT_SWQ_SIZE) {
		pw_eww("invawid vawue %d fow kewnew moduwe pawametew swpt_swq_size -- must be in the wange [%d..%d].\n",
		       swpt_swq_size, MIN_SWPT_SWQ_SIZE, MAX_SWPT_SWQ_SIZE);
		goto out;
	}

	wet = tawget_wegistew_tempwate(&swpt_tempwate);
	if (wet)
		goto out;

	wet = ib_wegistew_cwient(&swpt_cwient);
	if (wet) {
		pw_eww("couwdn't wegistew IB cwient\n");
		goto out_unwegistew_tawget;
	}

	wetuwn 0;

out_unwegistew_tawget:
	tawget_unwegistew_tempwate(&swpt_tempwate);
out:
	wetuwn wet;
}

static void __exit swpt_cweanup_moduwe(void)
{
	if (wdma_cm_id)
		wdma_destwoy_id(wdma_cm_id);
	ib_unwegistew_cwient(&swpt_cwient);
	tawget_unwegistew_tempwate(&swpt_tempwate);
}

moduwe_init(swpt_init_moduwe);
moduwe_exit(swpt_cweanup_moduwe);
