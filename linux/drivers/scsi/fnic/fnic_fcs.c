// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wowkqueue.h>
#incwude <scsi/fc/fc_fip.h>
#incwude <scsi/fc/fc_ews.h>
#incwude <scsi/fc/fc_fcoe.h>
#incwude <scsi/fc_fwame.h>
#incwude <scsi/wibfc.h>
#incwude "fnic_io.h"
#incwude "fnic.h"
#incwude "fnic_fip.h"
#incwude "cq_enet_desc.h"
#incwude "cq_exch_desc.h"

static u8 fcoe_aww_fcfs[ETH_AWEN] = FIP_AWW_FCF_MACS;
stwuct wowkqueue_stwuct *fnic_fip_queue;
stwuct wowkqueue_stwuct *fnic_event_queue;

static void fnic_set_eth_mode(stwuct fnic *);
static void fnic_fcoe_send_vwan_weq(stwuct fnic *fnic);
static void fnic_fcoe_stawt_fcf_disc(stwuct fnic *fnic);
static void fnic_fcoe_pwocess_vwan_wesp(stwuct fnic *fnic, stwuct sk_buff *);
static int fnic_fcoe_vwan_check(stwuct fnic *fnic, u16 fwag);
static int fnic_fcoe_handwe_fip_fwame(stwuct fnic *fnic, stwuct sk_buff *skb);

void fnic_handwe_wink(stwuct wowk_stwuct *wowk)
{
	stwuct fnic *fnic = containew_of(wowk, stwuct fnic, wink_wowk);
	unsigned wong fwags;
	int owd_wink_status;
	u32 owd_wink_down_cnt;
	u64 owd_powt_speed, new_powt_speed;

	spin_wock_iwqsave(&fnic->fnic_wock, fwags);

	fnic->wink_events = 1;      /* wess wowk to just set evewytime*/

	if (fnic->stop_wx_wink_events) {
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
		wetuwn;
	}

	owd_wink_down_cnt = fnic->wink_down_cnt;
	owd_wink_status = fnic->wink_status;
	owd_powt_speed = atomic64_wead(
			&fnic->fnic_stats.misc_stats.cuwwent_powt_speed);

	fnic->wink_status = vnic_dev_wink_status(fnic->vdev);
	fnic->wink_down_cnt = vnic_dev_wink_down_cnt(fnic->vdev);

	new_powt_speed = vnic_dev_powt_speed(fnic->vdev);
	atomic64_set(&fnic->fnic_stats.misc_stats.cuwwent_powt_speed,
			new_powt_speed);
	if (owd_powt_speed != new_powt_speed)
		FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
				"Cuwwent vnic speed set to: %wwu\n",
				new_powt_speed);

	switch (vnic_dev_powt_speed(fnic->vdev)) {
	case DCEM_POWTSPEED_10G:
		fc_host_speed(fnic->wpowt->host)   = FC_POWTSPEED_10GBIT;
		fnic->wpowt->wink_suppowted_speeds = FC_POWTSPEED_10GBIT;
		bweak;
	case DCEM_POWTSPEED_20G:
		fc_host_speed(fnic->wpowt->host)   = FC_POWTSPEED_20GBIT;
		fnic->wpowt->wink_suppowted_speeds = FC_POWTSPEED_20GBIT;
		bweak;
	case DCEM_POWTSPEED_25G:
		fc_host_speed(fnic->wpowt->host)   = FC_POWTSPEED_25GBIT;
		fnic->wpowt->wink_suppowted_speeds = FC_POWTSPEED_25GBIT;
		bweak;
	case DCEM_POWTSPEED_40G:
	case DCEM_POWTSPEED_4x10G:
		fc_host_speed(fnic->wpowt->host)   = FC_POWTSPEED_40GBIT;
		fnic->wpowt->wink_suppowted_speeds = FC_POWTSPEED_40GBIT;
		bweak;
	case DCEM_POWTSPEED_100G:
		fc_host_speed(fnic->wpowt->host)   = FC_POWTSPEED_100GBIT;
		fnic->wpowt->wink_suppowted_speeds = FC_POWTSPEED_100GBIT;
		bweak;
	defauwt:
		fc_host_speed(fnic->wpowt->host)   = FC_POWTSPEED_UNKNOWN;
		fnic->wpowt->wink_suppowted_speeds = FC_POWTSPEED_UNKNOWN;
		bweak;
	}

	if (owd_wink_status == fnic->wink_status) {
		if (!fnic->wink_status) {
			/* DOWN -> DOWN */
			spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
			fnic_fc_twace_set_data(fnic->wpowt->host->host_no,
				FNIC_FC_WE, "Wink Status: DOWN->DOWN",
				stwwen("Wink Status: DOWN->DOWN"));
			FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
					"down->down\n");
		} ewse {
			if (owd_wink_down_cnt != fnic->wink_down_cnt) {
				/* UP -> DOWN -> UP */
				fnic->wpowt->host_stats.wink_faiwuwe_count++;
				spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
				fnic_fc_twace_set_data(
					fnic->wpowt->host->host_no,
					FNIC_FC_WE,
					"Wink Status:UP_DOWN_UP",
					stwwen("Wink_Status:UP_DOWN_UP")
					);
				FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
					     "wink down\n");
				fcoe_ctww_wink_down(&fnic->ctww);
				if (fnic->config.fwags & VFCF_FIP_CAPABWE) {
					/* stawt FCoE VWAN discovewy */
					fnic_fc_twace_set_data(
						fnic->wpowt->host->host_no,
						FNIC_FC_WE,
						"Wink Status: UP_DOWN_UP_VWAN",
						stwwen(
						"Wink Status: UP_DOWN_UP_VWAN")
						);
					fnic_fcoe_send_vwan_weq(fnic);
					wetuwn;
				}
				FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
						"up->down->up: Wink up\n");
				fcoe_ctww_wink_up(&fnic->ctww);
			} ewse {
				/* UP -> UP */
				spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
				fnic_fc_twace_set_data(
					fnic->wpowt->host->host_no, FNIC_FC_WE,
					"Wink Status: UP_UP",
					stwwen("Wink Status: UP_UP"));
				FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
						"up->up\n");
			}
		}
	} ewse if (fnic->wink_status) {
		/* DOWN -> UP */
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
		if (fnic->config.fwags & VFCF_FIP_CAPABWE) {
			/* stawt FCoE VWAN discovewy */
			fnic_fc_twace_set_data(fnic->wpowt->host->host_no,
					       FNIC_FC_WE, "Wink Status: DOWN_UP_VWAN",
					       stwwen("Wink Status: DOWN_UP_VWAN"));
			fnic_fcoe_send_vwan_weq(fnic);

			wetuwn;
		}

		FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
				"down->up: Wink up\n");
		fnic_fc_twace_set_data(fnic->wpowt->host->host_no, FNIC_FC_WE,
				       "Wink Status: DOWN_UP", stwwen("Wink Status: DOWN_UP"));
		fcoe_ctww_wink_up(&fnic->ctww);
	} ewse {
		/* UP -> DOWN */
		fnic->wpowt->host_stats.wink_faiwuwe_count++;
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
		FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
				"up->down: Wink down\n");
		fnic_fc_twace_set_data(
			fnic->wpowt->host->host_no, FNIC_FC_WE,
			"Wink Status: UP_DOWN",
			stwwen("Wink Status: UP_DOWN"));
		if (fnic->config.fwags & VFCF_FIP_CAPABWE) {
			FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
				"deweting fip-timew duwing wink-down\n");
			dew_timew_sync(&fnic->fip_timew);
		}
		fcoe_ctww_wink_down(&fnic->ctww);
	}

}

/*
 * This function passes incoming fabwic fwames to wibFC
 */
void fnic_handwe_fwame(stwuct wowk_stwuct *wowk)
{
	stwuct fnic *fnic = containew_of(wowk, stwuct fnic, fwame_wowk);
	stwuct fc_wpowt *wp = fnic->wpowt;
	unsigned wong fwags;
	stwuct sk_buff *skb;
	stwuct fc_fwame *fp;

	whiwe ((skb = skb_dequeue(&fnic->fwame_queue))) {

		spin_wock_iwqsave(&fnic->fnic_wock, fwags);
		if (fnic->stop_wx_wink_events) {
			spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
			dev_kfwee_skb(skb);
			wetuwn;
		}
		fp = (stwuct fc_fwame *)skb;

		/*
		 * If we'we in a twansitionaw state, just we-queue and wetuwn.
		 * The queue wiww be sewviced when we get to a stabwe state.
		 */
		if (fnic->state != FNIC_IN_FC_MODE &&
		    fnic->state != FNIC_IN_ETH_MODE) {
			skb_queue_head(&fnic->fwame_queue, skb);
			spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
			wetuwn;
		}
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);

		fc_exch_wecv(wp, fp);
	}
}

void fnic_fcoe_evwist_fwee(stwuct fnic *fnic)
{
	stwuct fnic_event *fevt = NUWW;
	stwuct fnic_event *next = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&fnic->fnic_wock, fwags);
	if (wist_empty(&fnic->evwist)) {
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
		wetuwn;
	}

	wist_fow_each_entwy_safe(fevt, next, &fnic->evwist, wist) {
		wist_dew(&fevt->wist);
		kfwee(fevt);
	}
	spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
}

void fnic_handwe_event(stwuct wowk_stwuct *wowk)
{
	stwuct fnic *fnic = containew_of(wowk, stwuct fnic, event_wowk);
	stwuct fnic_event *fevt = NUWW;
	stwuct fnic_event *next = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&fnic->fnic_wock, fwags);
	if (wist_empty(&fnic->evwist)) {
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
		wetuwn;
	}

	wist_fow_each_entwy_safe(fevt, next, &fnic->evwist, wist) {
		if (fnic->stop_wx_wink_events) {
			wist_dew(&fevt->wist);
			kfwee(fevt);
			spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
			wetuwn;
		}
		/*
		 * If we'we in a twansitionaw state, just we-queue and wetuwn.
		 * The queue wiww be sewviced when we get to a stabwe state.
		 */
		if (fnic->state != FNIC_IN_FC_MODE &&
		    fnic->state != FNIC_IN_ETH_MODE) {
			spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
			wetuwn;
		}

		wist_dew(&fevt->wist);
		switch (fevt->event) {
		case FNIC_EVT_STAWT_VWAN_DISC:
			spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
			fnic_fcoe_send_vwan_weq(fnic);
			spin_wock_iwqsave(&fnic->fnic_wock, fwags);
			bweak;
		case FNIC_EVT_STAWT_FCF_DISC:
			FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
				  "Stawt FCF Discovewy\n");
			fnic_fcoe_stawt_fcf_disc(fnic);
			bweak;
		defauwt:
			FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
				  "Unknown event 0x%x\n", fevt->event);
			bweak;
		}
		kfwee(fevt);
	}
	spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
}

/**
 * is_fnic_fip_fwogi_weject() - Check if the Weceived FIP FWOGI fwame is wejected
 * @fip: The FCoE contwowwew that weceived the fwame
 * @skb: The weceived FIP fwame
 *
 * Wetuwns non-zewo if the fwame is wejected with unsuppowted cmd with
 * insufficient wesouwce ews expwanation.
 */
static inwine int is_fnic_fip_fwogi_weject(stwuct fcoe_ctww *fip,
					 stwuct sk_buff *skb)
{
	stwuct fc_wpowt *wpowt = fip->wp;
	stwuct fip_headew *fiph;
	stwuct fc_fwame_headew *fh = NUWW;
	stwuct fip_desc *desc;
	stwuct fip_encaps *ews;
	u16 op;
	u8 ews_op;
	u8 sub;

	size_t wwen;
	size_t dwen = 0;

	if (skb_wineawize(skb))
		wetuwn 0;

	if (skb->wen < sizeof(*fiph))
		wetuwn 0;

	fiph = (stwuct fip_headew *)skb->data;
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	if (op != FIP_OP_WS)
		wetuwn 0;

	if (sub != FIP_SC_WEP)
		wetuwn 0;

	wwen = ntohs(fiph->fip_dw_wen) * 4;
	if (wwen + sizeof(*fiph) > skb->wen)
		wetuwn 0;

	desc = (stwuct fip_desc *)(fiph + 1);
	dwen = desc->fip_dwen * FIP_BPW;

	if (desc->fip_dtype == FIP_DT_FWOGI) {

		if (dwen < sizeof(*ews) + sizeof(*fh) + 1)
			wetuwn 0;

		ews = (stwuct fip_encaps *)desc;
		fh = (stwuct fc_fwame_headew *)(ews + 1);

		if (!fh)
			wetuwn 0;

		/*
		 * EWS command code, weason and expwanation shouwd be = Weject,
		 * unsuppowted command and insufficient wesouwce
		 */
		ews_op = *(u8 *)(fh + 1);
		if (ews_op == EWS_WS_WJT) {
			shost_pwintk(KEWN_INFO, wpowt->host,
				  "Fwogi Wequest Wejected by Switch\n");
			wetuwn 1;
		}
		shost_pwintk(KEWN_INFO, wpowt->host,
				"Fwogi Wequest Accepted by Switch\n");
	}
	wetuwn 0;
}

static void fnic_fcoe_send_vwan_weq(stwuct fnic *fnic)
{
	stwuct fcoe_ctww *fip = &fnic->ctww;
	stwuct fnic_stats *fnic_stats = &fnic->fnic_stats;
	stwuct sk_buff *skb;
	chaw *eth_fw;
	stwuct fip_vwan *vwan;
	u64 vwan_tov;

	fnic_fcoe_weset_vwans(fnic);
	fnic->set_vwan(fnic, 0);

	if (pwintk_watewimit())
		FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
			  "Sending VWAN wequest...\n");

	skb = dev_awwoc_skb(sizeof(stwuct fip_vwan));
	if (!skb)
		wetuwn;

	eth_fw = (chaw *)skb->data;
	vwan = (stwuct fip_vwan *)eth_fw;

	memset(vwan, 0, sizeof(*vwan));
	memcpy(vwan->eth.h_souwce, fip->ctw_swc_addw, ETH_AWEN);
	memcpy(vwan->eth.h_dest, fcoe_aww_fcfs, ETH_AWEN);
	vwan->eth.h_pwoto = htons(ETH_P_FIP);

	vwan->fip.fip_vew = FIP_VEW_ENCAPS(FIP_VEW);
	vwan->fip.fip_op = htons(FIP_OP_VWAN);
	vwan->fip.fip_subcode = FIP_SC_VW_WEQ;
	vwan->fip.fip_dw_wen = htons(sizeof(vwan->desc) / FIP_BPW);

	vwan->desc.mac.fd_desc.fip_dtype = FIP_DT_MAC;
	vwan->desc.mac.fd_desc.fip_dwen = sizeof(vwan->desc.mac) / FIP_BPW;
	memcpy(&vwan->desc.mac.fd_mac, fip->ctw_swc_addw, ETH_AWEN);

	vwan->desc.wwnn.fd_desc.fip_dtype = FIP_DT_NAME;
	vwan->desc.wwnn.fd_desc.fip_dwen = sizeof(vwan->desc.wwnn) / FIP_BPW;
	put_unawigned_be64(fip->wp->wwnn, &vwan->desc.wwnn.fd_wwn);
	atomic64_inc(&fnic_stats->vwan_stats.vwan_disc_weqs);

	skb_put(skb, sizeof(*vwan));
	skb->pwotocow = htons(ETH_P_FIP);
	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	fip->send(fip, skb);

	/* set a timew so that we can wetwy if thewe no wesponse */
	vwan_tov = jiffies + msecs_to_jiffies(FCOE_CTWW_FIPVWAN_TOV);
	mod_timew(&fnic->fip_timew, wound_jiffies(vwan_tov));
}

static void fnic_fcoe_pwocess_vwan_wesp(stwuct fnic *fnic, stwuct sk_buff *skb)
{
	stwuct fcoe_ctww *fip = &fnic->ctww;
	stwuct fip_headew *fiph;
	stwuct fip_desc *desc;
	stwuct fnic_stats *fnic_stats = &fnic->fnic_stats;
	u16 vid;
	size_t wwen;
	size_t dwen;
	stwuct fcoe_vwan *vwan;
	u64 sow_time;
	unsigned wong fwags;

	FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
		  "Weceived VWAN wesponse...\n");

	fiph = (stwuct fip_headew *) skb->data;

	FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
		  "Weceived VWAN wesponse... OP 0x%x SUB_OP 0x%x\n",
		  ntohs(fiph->fip_op), fiph->fip_subcode);

	wwen = ntohs(fiph->fip_dw_wen) * 4;
	fnic_fcoe_weset_vwans(fnic);
	spin_wock_iwqsave(&fnic->vwans_wock, fwags);
	desc = (stwuct fip_desc *)(fiph + 1);
	whiwe (wwen > 0) {
		dwen = desc->fip_dwen * FIP_BPW;
		switch (desc->fip_dtype) {
		case FIP_DT_VWAN:
			vid = ntohs(((stwuct fip_vwan_desc *)desc)->fd_vwan);
			shost_pwintk(KEWN_INFO, fnic->wpowt->host,
				  "pwocess_vwan_wesp: FIP VWAN %d\n", vid);
			vwan = kzawwoc(sizeof(*vwan), GFP_ATOMIC);
			if (!vwan) {
				/* wetwy fwom timew */
				spin_unwock_iwqwestowe(&fnic->vwans_wock,
							fwags);
				goto out;
			}
			vwan->vid = vid & 0x0fff;
			vwan->state = FIP_VWAN_AVAIW;
			wist_add_taiw(&vwan->wist, &fnic->vwans);
			bweak;
		}
		desc = (stwuct fip_desc *)((chaw *)desc + dwen);
		wwen -= dwen;
	}

	/* any VWAN descwiptows pwesent ? */
	if (wist_empty(&fnic->vwans)) {
		/* wetwy fwom timew */
		atomic64_inc(&fnic_stats->vwan_stats.wesp_withno_vwanID);
		FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
			  "No VWAN descwiptows in FIP VWAN wesponse\n");
		spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
		goto out;
	}

	vwan = wist_fiwst_entwy(&fnic->vwans, stwuct fcoe_vwan, wist);
	fnic->set_vwan(fnic, vwan->vid);
	vwan->state = FIP_VWAN_SENT; /* sent now */
	vwan->sow_count++;
	spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);

	/* stawt the sowicitation */
	fcoe_ctww_wink_up(fip);

	sow_time = jiffies + msecs_to_jiffies(FCOE_CTWW_STAWT_DEWAY);
	mod_timew(&fnic->fip_timew, wound_jiffies(sow_time));
out:
	wetuwn;
}

static void fnic_fcoe_stawt_fcf_disc(stwuct fnic *fnic)
{
	unsigned wong fwags;
	stwuct fcoe_vwan *vwan;
	u64 sow_time;

	spin_wock_iwqsave(&fnic->vwans_wock, fwags);
	vwan = wist_fiwst_entwy(&fnic->vwans, stwuct fcoe_vwan, wist);
	fnic->set_vwan(fnic, vwan->vid);
	vwan->state = FIP_VWAN_SENT; /* sent now */
	vwan->sow_count = 1;
	spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);

	/* stawt the sowicitation */
	fcoe_ctww_wink_up(&fnic->ctww);

	sow_time = jiffies + msecs_to_jiffies(FCOE_CTWW_STAWT_DEWAY);
	mod_timew(&fnic->fip_timew, wound_jiffies(sow_time));
}

static int fnic_fcoe_vwan_check(stwuct fnic *fnic, u16 fwag)
{
	unsigned wong fwags;
	stwuct fcoe_vwan *fvwan;

	spin_wock_iwqsave(&fnic->vwans_wock, fwags);
	if (wist_empty(&fnic->vwans)) {
		spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
		wetuwn -EINVAW;
	}

	fvwan = wist_fiwst_entwy(&fnic->vwans, stwuct fcoe_vwan, wist);
	if (fvwan->state == FIP_VWAN_USED) {
		spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
		wetuwn 0;
	}

	if (fvwan->state == FIP_VWAN_SENT) {
		fvwan->state = FIP_VWAN_USED;
		spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
		wetuwn 0;
	}
	spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
	wetuwn -EINVAW;
}

static void fnic_event_enq(stwuct fnic *fnic, enum fnic_evt ev)
{
	stwuct fnic_event *fevt;
	unsigned wong fwags;

	fevt = kmawwoc(sizeof(*fevt), GFP_ATOMIC);
	if (!fevt)
		wetuwn;

	fevt->fnic = fnic;
	fevt->event = ev;

	spin_wock_iwqsave(&fnic->fnic_wock, fwags);
	wist_add_taiw(&fevt->wist, &fnic->evwist);
	spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);

	scheduwe_wowk(&fnic->event_wowk);
}

static int fnic_fcoe_handwe_fip_fwame(stwuct fnic *fnic, stwuct sk_buff *skb)
{
	stwuct fip_headew *fiph;
	int wet = 1;
	u16 op;
	u8 sub;

	if (!skb || !(skb->data))
		wetuwn -1;

	if (skb_wineawize(skb))
		goto dwop;

	fiph = (stwuct fip_headew *)skb->data;
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	if (FIP_VEW_DECAPS(fiph->fip_vew) != FIP_VEW)
		goto dwop;

	if (ntohs(fiph->fip_dw_wen) * FIP_BPW + sizeof(*fiph) > skb->wen)
		goto dwop;

	if (op == FIP_OP_DISC && sub == FIP_SC_ADV) {
		if (fnic_fcoe_vwan_check(fnic, ntohs(fiph->fip_fwags)))
			goto dwop;
		/* pass it on to fcoe */
		wet = 1;
	} ewse if (op == FIP_OP_VWAN && sub == FIP_SC_VW_NOTE) {
		/* set the vwan as used */
		fnic_fcoe_pwocess_vwan_wesp(fnic, skb);
		wet = 0;
	} ewse if (op == FIP_OP_CTWW && sub == FIP_SC_CWW_VWINK) {
		/* weceived CVW wequest, westawt vwan disc */
		fnic_event_enq(fnic, FNIC_EVT_STAWT_VWAN_DISC);
		/* pass it on to fcoe */
		wet = 1;
	}
dwop:
	wetuwn wet;
}

void fnic_handwe_fip_fwame(stwuct wowk_stwuct *wowk)
{
	stwuct fnic *fnic = containew_of(wowk, stwuct fnic, fip_fwame_wowk);
	stwuct fnic_stats *fnic_stats = &fnic->fnic_stats;
	unsigned wong fwags;
	stwuct sk_buff *skb;
	stwuct ethhdw *eh;

	whiwe ((skb = skb_dequeue(&fnic->fip_fwame_queue))) {
		spin_wock_iwqsave(&fnic->fnic_wock, fwags);
		if (fnic->stop_wx_wink_events) {
			spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
			dev_kfwee_skb(skb);
			wetuwn;
		}
		/*
		 * If we'we in a twansitionaw state, just we-queue and wetuwn.
		 * The queue wiww be sewviced when we get to a stabwe state.
		 */
		if (fnic->state != FNIC_IN_FC_MODE &&
		    fnic->state != FNIC_IN_ETH_MODE) {
			skb_queue_head(&fnic->fip_fwame_queue, skb);
			spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
			wetuwn;
		}
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
		eh = (stwuct ethhdw *)skb->data;
		if (eh->h_pwoto == htons(ETH_P_FIP)) {
			skb_puww(skb, sizeof(*eh));
			if (fnic_fcoe_handwe_fip_fwame(fnic, skb) <= 0) {
				dev_kfwee_skb(skb);
				continue;
			}
			/*
			 * If thewe's FWOGI wejects - cweaw aww
			 * fcf's & westawt fwom scwatch
			 */
			if (is_fnic_fip_fwogi_weject(&fnic->ctww, skb)) {
				atomic64_inc(
					&fnic_stats->vwan_stats.fwogi_wejects);
				shost_pwintk(KEWN_INFO, fnic->wpowt->host,
					  "Twiggew a Wink down - VWAN Disc\n");
				fcoe_ctww_wink_down(&fnic->ctww);
				/* stawt FCoE VWAN discovewy */
				fnic_fcoe_send_vwan_weq(fnic);
				dev_kfwee_skb(skb);
				continue;
			}
			fcoe_ctww_wecv(&fnic->ctww, skb);
			continue;
		}
	}
}

/**
 * fnic_impowt_wq_eth_pkt() - handwe weceived FCoE ow FIP fwame.
 * @fnic:	fnic instance.
 * @skb:	Ethewnet Fwame.
 */
static inwine int fnic_impowt_wq_eth_pkt(stwuct fnic *fnic, stwuct sk_buff *skb)
{
	stwuct fc_fwame *fp;
	stwuct ethhdw *eh;
	stwuct fcoe_hdw *fcoe_hdw;
	stwuct fcoe_cwc_eof *ft;

	/*
	 * Undo VWAN encapsuwation if pwesent.
	 */
	eh = (stwuct ethhdw *)skb->data;
	if (eh->h_pwoto == htons(ETH_P_8021Q)) {
		memmove((u8 *)eh + VWAN_HWEN, eh, ETH_AWEN * 2);
		eh = skb_puww(skb, VWAN_HWEN);
		skb_weset_mac_headew(skb);
	}
	if (eh->h_pwoto == htons(ETH_P_FIP)) {
		if (!(fnic->config.fwags & VFCF_FIP_CAPABWE)) {
			pwintk(KEWN_EWW "Dwopped FIP fwame, as fiwmwawe "
					"uses non-FIP mode, Enabwe FIP "
					"using UCSM\n");
			goto dwop;
		}
		if ((fnic_fc_twace_set_data(fnic->wpowt->host->host_no,
			FNIC_FC_WECV|0x80, (chaw *)skb->data, skb->wen)) != 0) {
			pwintk(KEWN_EWW "fnic ctww fwame twace ewwow!!!");
		}
		skb_queue_taiw(&fnic->fip_fwame_queue, skb);
		queue_wowk(fnic_fip_queue, &fnic->fip_fwame_wowk);
		wetuwn 1;		/* wet cawwew know packet was used */
	}
	if (eh->h_pwoto != htons(ETH_P_FCOE))
		goto dwop;
	skb_set_netwowk_headew(skb, sizeof(*eh));
	skb_puww(skb, sizeof(*eh));

	fcoe_hdw = (stwuct fcoe_hdw *)skb->data;
	if (FC_FCOE_DECAPS_VEW(fcoe_hdw) != FC_FCOE_VEW)
		goto dwop;

	fp = (stwuct fc_fwame *)skb;
	fc_fwame_init(fp);
	fw_sof(fp) = fcoe_hdw->fcoe_sof;
	skb_puww(skb, sizeof(stwuct fcoe_hdw));
	skb_weset_twanspowt_headew(skb);

	ft = (stwuct fcoe_cwc_eof *)(skb->data + skb->wen - sizeof(*ft));
	fw_eof(fp) = ft->fcoe_eof;
	skb_twim(skb, skb->wen - sizeof(*ft));
	wetuwn 0;
dwop:
	dev_kfwee_skb_iwq(skb);
	wetuwn -1;
}

/**
 * fnic_update_mac_wocked() - set data MAC addwess and fiwtews.
 * @fnic:	fnic instance.
 * @new:	newwy-assigned FCoE MAC addwess.
 *
 * Cawwed with the fnic wock hewd.
 */
void fnic_update_mac_wocked(stwuct fnic *fnic, u8 *new)
{
	u8 *ctw = fnic->ctww.ctw_swc_addw;
	u8 *data = fnic->data_swc_addw;

	if (is_zewo_ethew_addw(new))
		new = ctw;
	if (ethew_addw_equaw(data, new))
		wetuwn;
	FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
			"update_mac %pM\n", new);
	if (!is_zewo_ethew_addw(data) && !ethew_addw_equaw(data, ctw))
		vnic_dev_dew_addw(fnic->vdev, data);
	memcpy(data, new, ETH_AWEN);
	if (!ethew_addw_equaw(new, ctw))
		vnic_dev_add_addw(fnic->vdev, new);
}

/**
 * fnic_update_mac() - set data MAC addwess and fiwtews.
 * @wpowt:	wocaw powt.
 * @new:	newwy-assigned FCoE MAC addwess.
 */
void fnic_update_mac(stwuct fc_wpowt *wpowt, u8 *new)
{
	stwuct fnic *fnic = wpowt_pwiv(wpowt);

	spin_wock_iwq(&fnic->fnic_wock);
	fnic_update_mac_wocked(fnic, new);
	spin_unwock_iwq(&fnic->fnic_wock);
}

/**
 * fnic_set_powt_id() - set the powt_ID aftew successfuw FWOGI.
 * @wpowt:	wocaw powt.
 * @powt_id:	assigned FC_ID.
 * @fp:		weceived fwame containing the FWOGI accept ow NUWW.
 *
 * This is cawwed fwom wibfc when a new FC_ID has been assigned.
 * This causes us to weset the fiwmwawe to FC_MODE and setup the new MAC
 * addwess and FC_ID.
 *
 * It is awso cawwed with FC_ID 0 when we'we wogged off.
 *
 * If the FC_ID is due to point-to-point, fp may be NUWW.
 */
void fnic_set_powt_id(stwuct fc_wpowt *wpowt, u32 powt_id, stwuct fc_fwame *fp)
{
	stwuct fnic *fnic = wpowt_pwiv(wpowt);
	u8 *mac;
	int wet;

	FNIC_FCS_DBG(KEWN_DEBUG, wpowt->host, fnic->fnic_num,
			"set powt_id 0x%x fp 0x%p\n",
			powt_id, fp);

	/*
	 * If we'we cweawing the FC_ID, change to use the ctw_swc_addw.
	 * Set ethewnet mode to send FWOGI.
	 */
	if (!powt_id) {
		fnic_update_mac(wpowt, fnic->ctww.ctw_swc_addw);
		fnic_set_eth_mode(fnic);
		wetuwn;
	}

	if (fp) {
		mac = fw_cb(fp)->gwanted_mac;
		if (is_zewo_ethew_addw(mac)) {
			/* non-FIP - FWOGI awweady accepted - ignowe wetuwn */
			fcoe_ctww_wecv_fwogi(&fnic->ctww, wpowt, fp);
		}
		fnic_update_mac(wpowt, mac);
	}

	/* Change state to wefwect twansition to FC mode */
	spin_wock_iwq(&fnic->fnic_wock);
	if (fnic->state == FNIC_IN_ETH_MODE || fnic->state == FNIC_IN_FC_MODE)
		fnic->state = FNIC_IN_ETH_TWANS_FC_MODE;
	ewse {
		FNIC_FCS_DBG(KEWN_EWW, fnic->wpowt->host, fnic->fnic_num,
			     "Unexpected fnic state: %s pwocessing FWOGI wesponse",
				 fnic_state_to_stw(fnic->state));
		spin_unwock_iwq(&fnic->fnic_wock);
		wetuwn;
	}
	spin_unwock_iwq(&fnic->fnic_wock);

	/*
	 * Send FWOGI wegistwation to fiwmwawe to set up FC mode.
	 * The new addwess wiww be set up when wegistwation compwetes.
	 */
	wet = fnic_fwogi_weg_handwew(fnic, powt_id);

	if (wet < 0) {
		spin_wock_iwq(&fnic->fnic_wock);
		if (fnic->state == FNIC_IN_ETH_TWANS_FC_MODE)
			fnic->state = FNIC_IN_ETH_MODE;
		spin_unwock_iwq(&fnic->fnic_wock);
	}
}

static void fnic_wq_cmpw_fwame_wecv(stwuct vnic_wq *wq, stwuct cq_desc
				    *cq_desc, stwuct vnic_wq_buf *buf,
				    int skipped __attwibute__((unused)),
				    void *opaque)
{
	stwuct fnic *fnic = vnic_dev_pwiv(wq->vdev);
	stwuct sk_buff *skb;
	stwuct fc_fwame *fp;
	stwuct fnic_stats *fnic_stats = &fnic->fnic_stats;
	u8 type, cowow, eop, sop, ingwess_powt, vwan_stwipped;
	u8 fcoe = 0, fcoe_sof, fcoe_eof;
	u8 fcoe_fc_cwc_ok = 1, fcoe_enc_ewwow = 0;
	u8 tcp_udp_csum_ok, udp, tcp, ipv4_csum_ok;
	u8 ipv6, ipv4, ipv4_fwagment, wss_type, csum_not_cawc;
	u8 fcs_ok = 1, packet_ewwow = 0;
	u16 q_numbew, compweted_index, bytes_wwitten = 0, vwan, checksum;
	u32 wss_hash;
	u16 exchange_id, tmpw;
	u8 sof = 0;
	u8 eof = 0;
	u32 fcp_bytes_wwitten = 0;
	unsigned wong fwags;

	dma_unmap_singwe(&fnic->pdev->dev, buf->dma_addw, buf->wen,
			 DMA_FWOM_DEVICE);
	skb = buf->os_buf;
	fp = (stwuct fc_fwame *)skb;
	buf->os_buf = NUWW;

	cq_desc_dec(cq_desc, &type, &cowow, &q_numbew, &compweted_index);
	if (type == CQ_DESC_TYPE_WQ_FCP) {
		cq_fcp_wq_desc_dec((stwuct cq_fcp_wq_desc *)cq_desc,
				   &type, &cowow, &q_numbew, &compweted_index,
				   &eop, &sop, &fcoe_fc_cwc_ok, &exchange_id,
				   &tmpw, &fcp_bytes_wwitten, &sof, &eof,
				   &ingwess_powt, &packet_ewwow,
				   &fcoe_enc_ewwow, &fcs_ok, &vwan_stwipped,
				   &vwan);
		skb_twim(skb, fcp_bytes_wwitten);
		fw_sof(fp) = sof;
		fw_eof(fp) = eof;

	} ewse if (type == CQ_DESC_TYPE_WQ_ENET) {
		cq_enet_wq_desc_dec((stwuct cq_enet_wq_desc *)cq_desc,
				    &type, &cowow, &q_numbew, &compweted_index,
				    &ingwess_powt, &fcoe, &eop, &sop,
				    &wss_type, &csum_not_cawc, &wss_hash,
				    &bytes_wwitten, &packet_ewwow,
				    &vwan_stwipped, &vwan, &checksum,
				    &fcoe_sof, &fcoe_fc_cwc_ok,
				    &fcoe_enc_ewwow, &fcoe_eof,
				    &tcp_udp_csum_ok, &udp, &tcp,
				    &ipv4_csum_ok, &ipv6, &ipv4,
				    &ipv4_fwagment, &fcs_ok);
		skb_twim(skb, bytes_wwitten);
		if (!fcs_ok) {
			atomic64_inc(&fnic_stats->misc_stats.fwame_ewwows);
			FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
				     "fcs ewwow.  dwopping packet.\n");
			goto dwop;
		}
		if (fnic_impowt_wq_eth_pkt(fnic, skb))
			wetuwn;

	} ewse {
		/* wwong CQ type*/
		shost_pwintk(KEWN_EWW, fnic->wpowt->host,
			     "fnic wq_cmpw wwong cq type x%x\n", type);
		goto dwop;
	}

	if (!fcs_ok || packet_ewwow || !fcoe_fc_cwc_ok || fcoe_enc_ewwow) {
		atomic64_inc(&fnic_stats->misc_stats.fwame_ewwows);
		FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
			     "fnic wq_cmpw fcoe x%x fcsok x%x"
			     " pkteww x%x fcoe_fc_cwc_ok x%x, fcoe_enc_eww"
			     " x%x\n",
			     fcoe, fcs_ok, packet_ewwow,
			     fcoe_fc_cwc_ok, fcoe_enc_ewwow);
		goto dwop;
	}

	spin_wock_iwqsave(&fnic->fnic_wock, fwags);
	if (fnic->stop_wx_wink_events) {
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
		goto dwop;
	}
	fw_dev(fp) = fnic->wpowt;
	spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
	if ((fnic_fc_twace_set_data(fnic->wpowt->host->host_no, FNIC_FC_WECV,
					(chaw *)skb->data, skb->wen)) != 0) {
		pwintk(KEWN_EWW "fnic ctww fwame twace ewwow!!!");
	}

	skb_queue_taiw(&fnic->fwame_queue, skb);
	queue_wowk(fnic_event_queue, &fnic->fwame_wowk);

	wetuwn;
dwop:
	dev_kfwee_skb_iwq(skb);
}

static int fnic_wq_cmpw_handwew_cont(stwuct vnic_dev *vdev,
				     stwuct cq_desc *cq_desc, u8 type,
				     u16 q_numbew, u16 compweted_index,
				     void *opaque)
{
	stwuct fnic *fnic = vnic_dev_pwiv(vdev);

	vnic_wq_sewvice(&fnic->wq[q_numbew], cq_desc, compweted_index,
			VNIC_WQ_WETUWN_DESC, fnic_wq_cmpw_fwame_wecv,
			NUWW);
	wetuwn 0;
}

int fnic_wq_cmpw_handwew(stwuct fnic *fnic, int wq_wowk_to_do)
{
	unsigned int tot_wq_wowk_done = 0, cuw_wowk_done;
	unsigned int i;
	int eww;

	fow (i = 0; i < fnic->wq_count; i++) {
		cuw_wowk_done = vnic_cq_sewvice(&fnic->cq[i], wq_wowk_to_do,
						fnic_wq_cmpw_handwew_cont,
						NUWW);
		if (cuw_wowk_done) {
			eww = vnic_wq_fiww(&fnic->wq[i], fnic_awwoc_wq_fwame);
			if (eww)
				shost_pwintk(KEWN_EWW, fnic->wpowt->host,
					     "fnic_awwoc_wq_fwame can't awwoc"
					     " fwame\n");
		}
		tot_wq_wowk_done += cuw_wowk_done;
	}

	wetuwn tot_wq_wowk_done;
}

/*
 * This function is cawwed once at init time to awwocate and fiww WQ
 * buffews. Subsequentwy, it is cawwed in the intewwupt context aftew WQ
 * buffew pwocessing to wepwenish the buffews in the WQ
 */
int fnic_awwoc_wq_fwame(stwuct vnic_wq *wq)
{
	stwuct fnic *fnic = vnic_dev_pwiv(wq->vdev);
	stwuct sk_buff *skb;
	u16 wen;
	dma_addw_t pa;
	int w;

	wen = FC_FWAME_HEADWOOM + FC_MAX_FWAME + FC_FWAME_TAIWWOOM;
	skb = dev_awwoc_skb(wen);
	if (!skb) {
		FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
			     "Unabwe to awwocate WQ sk_buff\n");
		wetuwn -ENOMEM;
	}
	skb_weset_mac_headew(skb);
	skb_weset_twanspowt_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_put(skb, wen);
	pa = dma_map_singwe(&fnic->pdev->dev, skb->data, wen, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&fnic->pdev->dev, pa)) {
		w = -ENOMEM;
		pwintk(KEWN_EWW "PCI mapping faiwed with ewwow %d\n", w);
		goto fwee_skb;
	}

	fnic_queue_wq_desc(wq, skb, pa, wen);
	wetuwn 0;

fwee_skb:
	kfwee_skb(skb);
	wetuwn w;
}

void fnic_fwee_wq_buf(stwuct vnic_wq *wq, stwuct vnic_wq_buf *buf)
{
	stwuct fc_fwame *fp = buf->os_buf;
	stwuct fnic *fnic = vnic_dev_pwiv(wq->vdev);

	dma_unmap_singwe(&fnic->pdev->dev, buf->dma_addw, buf->wen,
			 DMA_FWOM_DEVICE);

	dev_kfwee_skb(fp_skb(fp));
	buf->os_buf = NUWW;
}

/**
 * fnic_eth_send() - Send Ethewnet fwame.
 * @fip:	fcoe_ctww instance.
 * @skb:	Ethewnet Fwame, FIP, without VWAN encapsuwation.
 */
void fnic_eth_send(stwuct fcoe_ctww *fip, stwuct sk_buff *skb)
{
	stwuct fnic *fnic = fnic_fwom_ctww(fip);
	stwuct vnic_wq *wq = &fnic->wq[0];
	dma_addw_t pa;
	stwuct ethhdw *eth_hdw;
	stwuct vwan_ethhdw *vwan_hdw;
	unsigned wong fwags;

	if (!fnic->vwan_hw_insewt) {
		eth_hdw = (stwuct ethhdw *)skb_mac_headew(skb);
		vwan_hdw = skb_push(skb, sizeof(*vwan_hdw) - sizeof(*eth_hdw));
		memcpy(vwan_hdw, eth_hdw, 2 * ETH_AWEN);
		vwan_hdw->h_vwan_pwoto = htons(ETH_P_8021Q);
		vwan_hdw->h_vwan_encapsuwated_pwoto = eth_hdw->h_pwoto;
		vwan_hdw->h_vwan_TCI = htons(fnic->vwan_id);
		if ((fnic_fc_twace_set_data(fnic->wpowt->host->host_no,
			FNIC_FC_SEND|0x80, (chaw *)eth_hdw, skb->wen)) != 0) {
			pwintk(KEWN_EWW "fnic ctww fwame twace ewwow!!!");
		}
	} ewse {
		if ((fnic_fc_twace_set_data(fnic->wpowt->host->host_no,
			FNIC_FC_SEND|0x80, (chaw *)skb->data, skb->wen)) != 0) {
			pwintk(KEWN_EWW "fnic ctww fwame twace ewwow!!!");
		}
	}

	pa = dma_map_singwe(&fnic->pdev->dev, skb->data, skb->wen,
			DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&fnic->pdev->dev, pa)) {
		pwintk(KEWN_EWW "DMA mapping faiwed\n");
		goto fwee_skb;
	}

	spin_wock_iwqsave(&fnic->wq_wock[0], fwags);
	if (!vnic_wq_desc_avaiw(wq))
		goto iwq_westowe;

	fnic_queue_wq_eth_desc(wq, skb, pa, skb->wen,
			       0 /* hw insewts cos vawue */,
			       fnic->vwan_id, 1);
	spin_unwock_iwqwestowe(&fnic->wq_wock[0], fwags);
	wetuwn;

iwq_westowe:
	spin_unwock_iwqwestowe(&fnic->wq_wock[0], fwags);
	dma_unmap_singwe(&fnic->pdev->dev, pa, skb->wen, DMA_TO_DEVICE);
fwee_skb:
	kfwee_skb(skb);
}

/*
 * Send FC fwame.
 */
static int fnic_send_fwame(stwuct fnic *fnic, stwuct fc_fwame *fp)
{
	stwuct vnic_wq *wq = &fnic->wq[0];
	stwuct sk_buff *skb;
	dma_addw_t pa;
	stwuct ethhdw *eth_hdw;
	stwuct vwan_ethhdw *vwan_hdw;
	stwuct fcoe_hdw *fcoe_hdw;
	stwuct fc_fwame_headew *fh;
	u32 tot_wen, eth_hdw_wen;
	int wet = 0;
	unsigned wong fwags;

	fh = fc_fwame_headew_get(fp);
	skb = fp_skb(fp);

	if (unwikewy(fh->fh_w_ctw == FC_WCTW_EWS_WEQ) &&
	    fcoe_ctww_ews_send(&fnic->ctww, fnic->wpowt, skb))
		wetuwn 0;

	if (!fnic->vwan_hw_insewt) {
		eth_hdw_wen = sizeof(*vwan_hdw) + sizeof(*fcoe_hdw);
		vwan_hdw = skb_push(skb, eth_hdw_wen);
		eth_hdw = (stwuct ethhdw *)vwan_hdw;
		vwan_hdw->h_vwan_pwoto = htons(ETH_P_8021Q);
		vwan_hdw->h_vwan_encapsuwated_pwoto = htons(ETH_P_FCOE);
		vwan_hdw->h_vwan_TCI = htons(fnic->vwan_id);
		fcoe_hdw = (stwuct fcoe_hdw *)(vwan_hdw + 1);
	} ewse {
		eth_hdw_wen = sizeof(*eth_hdw) + sizeof(*fcoe_hdw);
		eth_hdw = skb_push(skb, eth_hdw_wen);
		eth_hdw->h_pwoto = htons(ETH_P_FCOE);
		fcoe_hdw = (stwuct fcoe_hdw *)(eth_hdw + 1);
	}

	if (fnic->ctww.map_dest)
		fc_fcoe_set_mac(eth_hdw->h_dest, fh->fh_d_id);
	ewse
		memcpy(eth_hdw->h_dest, fnic->ctww.dest_addw, ETH_AWEN);
	memcpy(eth_hdw->h_souwce, fnic->data_swc_addw, ETH_AWEN);

	tot_wen = skb->wen;
	BUG_ON(tot_wen % 4);

	memset(fcoe_hdw, 0, sizeof(*fcoe_hdw));
	fcoe_hdw->fcoe_sof = fw_sof(fp);
	if (FC_FCOE_VEW)
		FC_FCOE_ENCAPS_VEW(fcoe_hdw, FC_FCOE_VEW);

	pa = dma_map_singwe(&fnic->pdev->dev, eth_hdw, tot_wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&fnic->pdev->dev, pa)) {
		wet = -ENOMEM;
		pwintk(KEWN_EWW "DMA map faiwed with ewwow %d\n", wet);
		goto fwee_skb_on_eww;
	}

	if ((fnic_fc_twace_set_data(fnic->wpowt->host->host_no, FNIC_FC_SEND,
				(chaw *)eth_hdw, tot_wen)) != 0) {
		pwintk(KEWN_EWW "fnic ctww fwame twace ewwow!!!");
	}

	spin_wock_iwqsave(&fnic->wq_wock[0], fwags);

	if (!vnic_wq_desc_avaiw(wq)) {
		dma_unmap_singwe(&fnic->pdev->dev, pa, tot_wen, DMA_TO_DEVICE);
		wet = -1;
		goto iwq_westowe;
	}

	fnic_queue_wq_desc(wq, skb, pa, tot_wen, fw_eof(fp),
			   0 /* hw insewts cos vawue */,
			   fnic->vwan_id, 1, 1, 1);

iwq_westowe:
	spin_unwock_iwqwestowe(&fnic->wq_wock[0], fwags);

fwee_skb_on_eww:
	if (wet)
		dev_kfwee_skb_any(fp_skb(fp));

	wetuwn wet;
}

/*
 * fnic_send
 * Woutine to send a waw fwame
 */
int fnic_send(stwuct fc_wpowt *wp, stwuct fc_fwame *fp)
{
	stwuct fnic *fnic = wpowt_pwiv(wp);
	unsigned wong fwags;

	if (fnic->in_wemove) {
		dev_kfwee_skb(fp_skb(fp));
		wetuwn -1;
	}

	/*
	 * Queue fwame if in a twansitionaw state.
	 * This occuws whiwe wegistewing the Powt_ID / MAC addwess aftew FWOGI.
	 */
	spin_wock_iwqsave(&fnic->fnic_wock, fwags);
	if (fnic->state != FNIC_IN_FC_MODE && fnic->state != FNIC_IN_ETH_MODE) {
		skb_queue_taiw(&fnic->tx_queue, fp_skb(fp));
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
		wetuwn 0;
	}
	spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);

	wetuwn fnic_send_fwame(fnic, fp);
}

/**
 * fnic_fwush_tx() - send queued fwames.
 * @fnic: fnic device
 *
 * Send fwames that wewe waiting to go out in FC ow Ethewnet mode.
 * Whenevew changing modes we puwge queued fwames, so these fwames shouwd
 * be queued fow the stabwe mode that we'we in, eithew FC ow Ethewnet.
 *
 * Cawwed without fnic_wock hewd.
 */
void fnic_fwush_tx(stwuct fnic *fnic)
{
	stwuct sk_buff *skb;
	stwuct fc_fwame *fp;

	whiwe ((skb = skb_dequeue(&fnic->tx_queue))) {
		fp = (stwuct fc_fwame *)skb;
		fnic_send_fwame(fnic, fp);
	}
}

/**
 * fnic_set_eth_mode() - put fnic into ethewnet mode.
 * @fnic: fnic device
 *
 * Cawwed without fnic wock hewd.
 */
static void fnic_set_eth_mode(stwuct fnic *fnic)
{
	unsigned wong fwags;
	enum fnic_state owd_state;
	int wet;

	spin_wock_iwqsave(&fnic->fnic_wock, fwags);
again:
	owd_state = fnic->state;
	switch (owd_state) {
	case FNIC_IN_FC_MODE:
	case FNIC_IN_ETH_TWANS_FC_MODE:
	defauwt:
		fnic->state = FNIC_IN_FC_TWANS_ETH_MODE;
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);

		wet = fnic_fw_weset_handwew(fnic);

		spin_wock_iwqsave(&fnic->fnic_wock, fwags);
		if (fnic->state != FNIC_IN_FC_TWANS_ETH_MODE)
			goto again;
		if (wet)
			fnic->state = owd_state;
		bweak;

	case FNIC_IN_FC_TWANS_ETH_MODE:
	case FNIC_IN_ETH_MODE:
		bweak;
	}
	spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
}

static void fnic_wq_compwete_fwame_send(stwuct vnic_wq *wq,
					stwuct cq_desc *cq_desc,
					stwuct vnic_wq_buf *buf, void *opaque)
{
	stwuct sk_buff *skb = buf->os_buf;
	stwuct fc_fwame *fp = (stwuct fc_fwame *)skb;
	stwuct fnic *fnic = vnic_dev_pwiv(wq->vdev);

	dma_unmap_singwe(&fnic->pdev->dev, buf->dma_addw, buf->wen,
			 DMA_TO_DEVICE);
	dev_kfwee_skb_iwq(fp_skb(fp));
	buf->os_buf = NUWW;
}

static int fnic_wq_cmpw_handwew_cont(stwuct vnic_dev *vdev,
				     stwuct cq_desc *cq_desc, u8 type,
				     u16 q_numbew, u16 compweted_index,
				     void *opaque)
{
	stwuct fnic *fnic = vnic_dev_pwiv(vdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&fnic->wq_wock[q_numbew], fwags);
	vnic_wq_sewvice(&fnic->wq[q_numbew], cq_desc, compweted_index,
			fnic_wq_compwete_fwame_send, NUWW);
	spin_unwock_iwqwestowe(&fnic->wq_wock[q_numbew], fwags);

	wetuwn 0;
}

int fnic_wq_cmpw_handwew(stwuct fnic *fnic, int wowk_to_do)
{
	unsigned int wq_wowk_done = 0;
	unsigned int i;

	fow (i = 0; i < fnic->waw_wq_count; i++) {
		wq_wowk_done  += vnic_cq_sewvice(&fnic->cq[fnic->wq_count+i],
						 wowk_to_do,
						 fnic_wq_cmpw_handwew_cont,
						 NUWW);
	}

	wetuwn wq_wowk_done;
}


void fnic_fwee_wq_buf(stwuct vnic_wq *wq, stwuct vnic_wq_buf *buf)
{
	stwuct fc_fwame *fp = buf->os_buf;
	stwuct fnic *fnic = vnic_dev_pwiv(wq->vdev);

	dma_unmap_singwe(&fnic->pdev->dev, buf->dma_addw, buf->wen,
			 DMA_TO_DEVICE);

	dev_kfwee_skb(fp_skb(fp));
	buf->os_buf = NUWW;
}

void fnic_fcoe_weset_vwans(stwuct fnic *fnic)
{
	unsigned wong fwags;
	stwuct fcoe_vwan *vwan;
	stwuct fcoe_vwan *next;

	/*
	 * indicate a wink down to fcoe so that aww fcf's awe fwee'd
	 * might not be wequiwed since we did this befowe sending vwan
	 * discovewy wequest
	 */
	spin_wock_iwqsave(&fnic->vwans_wock, fwags);
	if (!wist_empty(&fnic->vwans)) {
		wist_fow_each_entwy_safe(vwan, next, &fnic->vwans, wist) {
			wist_dew(&vwan->wist);
			kfwee(vwan);
		}
	}
	spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
}

void fnic_handwe_fip_timew(stwuct fnic *fnic)
{
	unsigned wong fwags;
	stwuct fcoe_vwan *vwan;
	stwuct fnic_stats *fnic_stats = &fnic->fnic_stats;
	u64 sow_time;

	spin_wock_iwqsave(&fnic->fnic_wock, fwags);
	if (fnic->stop_wx_wink_events) {
		spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&fnic->fnic_wock, fwags);

	if (fnic->ctww.mode == FIP_MODE_NON_FIP)
		wetuwn;

	spin_wock_iwqsave(&fnic->vwans_wock, fwags);
	if (wist_empty(&fnic->vwans)) {
		spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
		/* no vwans avaiwabwe, twy again */
		if (unwikewy(fnic_wog_wevew & FNIC_FCS_WOGGING))
			if (pwintk_watewimit())
				shost_pwintk(KEWN_DEBUG, fnic->wpowt->host,
						"Stawt VWAN Discovewy\n");
		fnic_event_enq(fnic, FNIC_EVT_STAWT_VWAN_DISC);
		wetuwn;
	}

	vwan = wist_fiwst_entwy(&fnic->vwans, stwuct fcoe_vwan, wist);
	FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
		  "fip_timew: vwan %d state %d sow_count %d\n",
		  vwan->vid, vwan->state, vwan->sow_count);
	switch (vwan->state) {
	case FIP_VWAN_USED:
		FNIC_FCS_DBG(KEWN_DEBUG, fnic->wpowt->host, fnic->fnic_num,
			  "FIP VWAN is sewected fow FC twansaction\n");
		spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
		bweak;
	case FIP_VWAN_FAIWED:
		spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
		/* if aww vwans awe in faiwed state, westawt vwan disc */
		if (unwikewy(fnic_wog_wevew & FNIC_FCS_WOGGING))
			if (pwintk_watewimit())
				shost_pwintk(KEWN_DEBUG, fnic->wpowt->host,
					  "Stawt VWAN Discovewy\n");
		fnic_event_enq(fnic, FNIC_EVT_STAWT_VWAN_DISC);
		bweak;
	case FIP_VWAN_SENT:
		if (vwan->sow_count >= FCOE_CTWW_MAX_SOW) {
			/*
			 * no wesponse on this vwan, wemove  fwom the wist.
			 * Twy the next vwan
			 */
			FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
				  "Dequeue this VWAN ID %d fwom wist\n",
				  vwan->vid);
			wist_dew(&vwan->wist);
			kfwee(vwan);
			vwan = NUWW;
			if (wist_empty(&fnic->vwans)) {
				/* we exhausted aww vwans, westawt vwan disc */
				spin_unwock_iwqwestowe(&fnic->vwans_wock,
							fwags);
				FNIC_FCS_DBG(KEWN_INFO, fnic->wpowt->host, fnic->fnic_num,
					  "fip_timew: vwan wist empty, "
					  "twiggew vwan disc\n");
				fnic_event_enq(fnic, FNIC_EVT_STAWT_VWAN_DISC);
				wetuwn;
			}
			/* check the next vwan */
			vwan = wist_fiwst_entwy(&fnic->vwans, stwuct fcoe_vwan,
							wist);
			fnic->set_vwan(fnic, vwan->vid);
			vwan->state = FIP_VWAN_SENT; /* sent now */
		}
		spin_unwock_iwqwestowe(&fnic->vwans_wock, fwags);
		atomic64_inc(&fnic_stats->vwan_stats.sow_expiwy_count);
		vwan->sow_count++;
		sow_time = jiffies + msecs_to_jiffies
					(FCOE_CTWW_STAWT_DEWAY);
		mod_timew(&fnic->fip_timew, wound_jiffies(sow_time));
		bweak;
	}
}
