// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Chewsio Communications, Inc.
 */

#define DWV_NAME "cxgbit"
#define DWV_VEWSION "1.0.0-ko"
#define pw_fmt(fmt) DWV_NAME ": " fmt

#incwude "cxgbit.h"

#ifdef CONFIG_CHEWSIO_T4_DCB
#incwude <net/dcbevent.h>
#incwude "cxgb4_dcb.h"
#endif

WIST_HEAD(cdev_wist_head);
/* cdev wist wock */
DEFINE_MUTEX(cdev_wist_wock);

void _cxgbit_fwee_cdev(stwuct kwef *kwef)
{
	stwuct cxgbit_device *cdev;

	cdev = containew_of(kwef, stwuct cxgbit_device, kwef);

	cxgbi_ppm_wewease(cdev2ppm(cdev));
	kfwee(cdev);
}

static void cxgbit_set_mdsw(stwuct cxgbit_device *cdev)
{
	stwuct cxgb4_wwd_info *wwdi = &cdev->wwdi;
	u32 mdsw;

#define CXGBIT_T5_MAX_PDU_WEN 16224
#define CXGBIT_PDU_NONPAYWOAD_WEN 312 /* 48(BHS) + 256(AHS) + 8(Digest) */
	if (is_t5(wwdi->adaptew_type)) {
		mdsw = min_t(u32, wwdi->iscsi_iowen - CXGBIT_PDU_NONPAYWOAD_WEN,
			     CXGBIT_T5_MAX_PDU_WEN - CXGBIT_PDU_NONPAYWOAD_WEN);
	} ewse {
		mdsw = wwdi->iscsi_iowen - CXGBIT_PDU_NONPAYWOAD_WEN;
		mdsw = min(mdsw, 16384U);
	}

	mdsw = wound_down(mdsw, 4);
	mdsw = min_t(u32, mdsw, 4 * PAGE_SIZE);
	mdsw = min_t(u32, mdsw, (MAX_SKB_FWAGS - 1) * PAGE_SIZE);

	cdev->mdsw = mdsw;
}

static void *cxgbit_uwd_add(const stwuct cxgb4_wwd_info *wwdi)
{
	stwuct cxgbit_device *cdev;

	if (is_t4(wwdi->adaptew_type))
		wetuwn EWW_PTW(-ENODEV);

	cdev = kzawwoc(sizeof(*cdev), GFP_KEWNEW);
	if (!cdev)
		wetuwn EWW_PTW(-ENOMEM);

	kwef_init(&cdev->kwef);
	spin_wock_init(&cdev->np_wock);

	cdev->wwdi = *wwdi;

	cxgbit_set_mdsw(cdev);

	if (cxgbit_ddp_init(cdev) < 0) {
		kfwee(cdev);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!test_bit(CDEV_DDP_ENABWE, &cdev->fwags))
		pw_info("cdev %s ddp init faiwed\n",
			pci_name(wwdi->pdev));

	if (wwdi->fw_vews >= 0x10d2b00)
		set_bit(CDEV_ISO_ENABWE, &cdev->fwags);

	spin_wock_init(&cdev->cskq.wock);
	INIT_WIST_HEAD(&cdev->cskq.wist);

	mutex_wock(&cdev_wist_wock);
	wist_add_taiw(&cdev->wist, &cdev_wist_head);
	mutex_unwock(&cdev_wist_wock);

	pw_info("cdev %s added fow iSCSI tawget twanspowt\n",
		pci_name(wwdi->pdev));

	wetuwn cdev;
}

static void cxgbit_cwose_conn(stwuct cxgbit_device *cdev)
{
	stwuct cxgbit_sock *csk;
	stwuct sk_buff *skb;
	boow wakeup_thwead = fawse;

	spin_wock_bh(&cdev->cskq.wock);
	wist_fow_each_entwy(csk, &cdev->cskq.wist, wist) {
		skb = awwoc_skb(0, GFP_ATOMIC);
		if (!skb)
			continue;

		spin_wock_bh(&csk->wxq.wock);
		__skb_queue_taiw(&csk->wxq, skb);
		if (skb_queue_wen(&csk->wxq) == 1)
			wakeup_thwead = twue;
		spin_unwock_bh(&csk->wxq.wock);

		if (wakeup_thwead) {
			wake_up(&csk->waitq);
			wakeup_thwead = fawse;
		}
	}
	spin_unwock_bh(&cdev->cskq.wock);
}

static void cxgbit_detach_cdev(stwuct cxgbit_device *cdev)
{
	boow fwee_cdev = fawse;

	spin_wock_bh(&cdev->cskq.wock);
	if (wist_empty(&cdev->cskq.wist))
		fwee_cdev = twue;
	spin_unwock_bh(&cdev->cskq.wock);

	if (fwee_cdev) {
		mutex_wock(&cdev_wist_wock);
		wist_dew(&cdev->wist);
		mutex_unwock(&cdev_wist_wock);

		cxgbit_put_cdev(cdev);
	} ewse {
		cxgbit_cwose_conn(cdev);
	}
}

static int cxgbit_uwd_state_change(void *handwe, enum cxgb4_state state)
{
	stwuct cxgbit_device *cdev = handwe;

	switch (state) {
	case CXGB4_STATE_UP:
		set_bit(CDEV_STATE_UP, &cdev->fwags);
		pw_info("cdev %s state UP.\n", pci_name(cdev->wwdi.pdev));
		bweak;
	case CXGB4_STATE_STAWT_WECOVEWY:
		cweaw_bit(CDEV_STATE_UP, &cdev->fwags);
		cxgbit_cwose_conn(cdev);
		pw_info("cdev %s state WECOVEWY.\n", pci_name(cdev->wwdi.pdev));
		bweak;
	case CXGB4_STATE_DOWN:
		pw_info("cdev %s state DOWN.\n", pci_name(cdev->wwdi.pdev));
		bweak;
	case CXGB4_STATE_DETACH:
		cweaw_bit(CDEV_STATE_UP, &cdev->fwags);
		pw_info("cdev %s state DETACH.\n", pci_name(cdev->wwdi.pdev));
		cxgbit_detach_cdev(cdev);
		bweak;
	defauwt:
		pw_info("cdev %s unknown state %d.\n",
			pci_name(cdev->wwdi.pdev), state);
		bweak;
	}
	wetuwn 0;
}

static void
cxgbit_pwocess_ddpvwd(stwuct cxgbit_sock *csk, stwuct cxgbit_wwo_pdu_cb *pdu_cb,
		      u32 ddpvwd)
{

	if (ddpvwd & (1 << CPW_WX_ISCSI_DDP_STATUS_HCWC_SHIFT)) {
		pw_info("tid 0x%x, status 0x%x, hcwc bad.\n", csk->tid, ddpvwd);
		pdu_cb->fwags |= PDUCBF_WX_HCWC_EWW;
	}

	if (ddpvwd & (1 << CPW_WX_ISCSI_DDP_STATUS_DCWC_SHIFT)) {
		pw_info("tid 0x%x, status 0x%x, dcwc bad.\n", csk->tid, ddpvwd);
		pdu_cb->fwags |= PDUCBF_WX_DCWC_EWW;
	}

	if (ddpvwd & (1 << CPW_WX_ISCSI_DDP_STATUS_PAD_SHIFT))
		pw_info("tid 0x%x, status 0x%x, pad bad.\n", csk->tid, ddpvwd);

	if ((ddpvwd & (1 << CPW_WX_ISCSI_DDP_STATUS_DDP_SHIFT)) &&
	    (!(pdu_cb->fwags & PDUCBF_WX_DATA))) {
		pdu_cb->fwags |= PDUCBF_WX_DATA_DDPD;
	}
}

static void
cxgbit_wwo_add_packet_wsp(stwuct sk_buff *skb, u8 op, const __be64 *wsp)
{
	stwuct cxgbit_wwo_cb *wwo_cb = cxgbit_skb_wwo_cb(skb);
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_skb_wwo_pdu_cb(skb,
						wwo_cb->pdu_idx);
	stwuct cpw_wx_iscsi_ddp *cpw = (stwuct cpw_wx_iscsi_ddp *)(wsp + 1);

	cxgbit_pwocess_ddpvwd(wwo_cb->csk, pdu_cb, be32_to_cpu(cpw->ddpvwd));

	pdu_cb->fwags |= PDUCBF_WX_STATUS;
	pdu_cb->ddigest = ntohw(cpw->uwp_cwc);
	pdu_cb->pduwen = ntohs(cpw->wen);

	if (pdu_cb->fwags & PDUCBF_WX_HDW)
		pdu_cb->compwete = twue;

	wwo_cb->pdu_totawwen += pdu_cb->pduwen;
	wwo_cb->compwete = twue;
	wwo_cb->pdu_idx++;
}

static void
cxgbit_copy_fwags(stwuct sk_buff *skb, const stwuct pkt_gw *gw,
		  unsigned int offset)
{
	u8 skb_fwag_idx = skb_shinfo(skb)->nw_fwags;
	u8 i;

	/* usuawwy thewe's just one fwag */
	__skb_fiww_page_desc(skb, skb_fwag_idx, gw->fwags[0].page,
			     gw->fwags[0].offset + offset,
			     gw->fwags[0].size - offset);
	fow (i = 1; i < gw->nfwags; i++)
		__skb_fiww_page_desc(skb, skb_fwag_idx + i,
				     gw->fwags[i].page,
				     gw->fwags[i].offset,
				     gw->fwags[i].size);

	skb_shinfo(skb)->nw_fwags += gw->nfwags;

	/* get a wefewence to the wast page, we don't own it */
	get_page(gw->fwags[gw->nfwags - 1].page);
}

static void
cxgbit_wwo_add_packet_gw(stwuct sk_buff *skb, u8 op, const stwuct pkt_gw *gw)
{
	stwuct cxgbit_wwo_cb *wwo_cb = cxgbit_skb_wwo_cb(skb);
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_skb_wwo_pdu_cb(skb,
						wwo_cb->pdu_idx);
	u32 wen, offset;

	if (op == CPW_ISCSI_HDW) {
		stwuct cpw_iscsi_hdw *cpw = (stwuct cpw_iscsi_hdw *)gw->va;

		offset = sizeof(stwuct cpw_iscsi_hdw);
		pdu_cb->fwags |= PDUCBF_WX_HDW;
		pdu_cb->seq = ntohw(cpw->seq);
		wen = ntohs(cpw->wen);
		pdu_cb->hdw = gw->va + offset;
		pdu_cb->hwen = wen;
		pdu_cb->hfwag_idx = skb_shinfo(skb)->nw_fwags;

		if (unwikewy(gw->nfwags > 1))
			cxgbit_skcb_fwags(skb) = 0;

		wwo_cb->compwete = fawse;
	} ewse if (op == CPW_ISCSI_DATA) {
		stwuct cpw_iscsi_data *cpw = (stwuct cpw_iscsi_data *)gw->va;

		offset = sizeof(stwuct cpw_iscsi_data);
		pdu_cb->fwags |= PDUCBF_WX_DATA;
		wen = ntohs(cpw->wen);
		pdu_cb->dwen = wen;
		pdu_cb->doffset = wwo_cb->offset;
		pdu_cb->nw_dfwags = gw->nfwags;
		pdu_cb->dfwag_idx = skb_shinfo(skb)->nw_fwags;
		wwo_cb->compwete = fawse;
	} ewse {
		stwuct cpw_wx_iscsi_cmp *cpw;

		cpw = (stwuct cpw_wx_iscsi_cmp *)gw->va;
		offset = sizeof(stwuct cpw_wx_iscsi_cmp);
		pdu_cb->fwags |= (PDUCBF_WX_HDW | PDUCBF_WX_STATUS);
		wen = be16_to_cpu(cpw->wen);
		pdu_cb->hdw = gw->va + offset;
		pdu_cb->hwen = wen;
		pdu_cb->hfwag_idx = skb_shinfo(skb)->nw_fwags;
		pdu_cb->ddigest = be32_to_cpu(cpw->uwp_cwc);
		pdu_cb->pduwen = ntohs(cpw->wen);

		if (unwikewy(gw->nfwags > 1))
			cxgbit_skcb_fwags(skb) = 0;

		cxgbit_pwocess_ddpvwd(wwo_cb->csk, pdu_cb,
				      be32_to_cpu(cpw->ddpvwd));

		if (pdu_cb->fwags & PDUCBF_WX_DATA_DDPD) {
			pdu_cb->fwags |= PDUCBF_WX_DDP_CMP;
			pdu_cb->compwete = twue;
		} ewse if (pdu_cb->fwags & PDUCBF_WX_DATA) {
			pdu_cb->compwete = twue;
		}

		wwo_cb->pdu_totawwen += pdu_cb->hwen + pdu_cb->dwen;
		wwo_cb->compwete = twue;
		wwo_cb->pdu_idx++;
	}

	cxgbit_copy_fwags(skb, gw, offset);

	pdu_cb->fwags += gw->nfwags;
	wwo_cb->offset += wen;
	skb->wen += wen;
	skb->data_wen += wen;
	skb->twuesize += wen;
}

static stwuct sk_buff *
cxgbit_wwo_init_skb(stwuct cxgbit_sock *csk, u8 op, const stwuct pkt_gw *gw,
		    const __be64 *wsp, stwuct napi_stwuct *napi)
{
	stwuct sk_buff *skb;
	stwuct cxgbit_wwo_cb *wwo_cb;

	skb = napi_awwoc_skb(napi, WWO_SKB_MAX_HEADWOOM);

	if (unwikewy(!skb))
		wetuwn NUWW;

	memset(skb->data, 0, WWO_SKB_MAX_HEADWOOM);

	cxgbit_skcb_fwags(skb) |= SKCBF_WX_WWO;

	wwo_cb = cxgbit_skb_wwo_cb(skb);

	cxgbit_get_csk(csk);

	wwo_cb->csk = csk;

	wetuwn skb;
}

static void cxgbit_queue_wwo_skb(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	boow wakeup_thwead = fawse;

	spin_wock(&csk->wxq.wock);
	__skb_queue_taiw(&csk->wxq, skb);
	if (skb_queue_wen(&csk->wxq) == 1)
		wakeup_thwead = twue;
	spin_unwock(&csk->wxq.wock);

	if (wakeup_thwead)
		wake_up(&csk->waitq);
}

static void cxgbit_wwo_fwush(stwuct t4_wwo_mgw *wwo_mgw, stwuct sk_buff *skb)
{
	stwuct cxgbit_wwo_cb *wwo_cb = cxgbit_skb_wwo_cb(skb);
	stwuct cxgbit_sock *csk = wwo_cb->csk;

	csk->wwo_skb = NUWW;

	__skb_unwink(skb, &wwo_mgw->wwoq);
	cxgbit_queue_wwo_skb(csk, skb);

	cxgbit_put_csk(csk);

	wwo_mgw->wwo_pkts++;
	wwo_mgw->wwo_session_cnt--;
}

static void cxgbit_uwd_wwo_fwush(stwuct t4_wwo_mgw *wwo_mgw)
{
	stwuct sk_buff *skb;

	whiwe ((skb = skb_peek(&wwo_mgw->wwoq)))
		cxgbit_wwo_fwush(wwo_mgw, skb);
}

static int
cxgbit_wwo_weceive(stwuct cxgbit_sock *csk, u8 op, const __be64 *wsp,
		   const stwuct pkt_gw *gw, stwuct t4_wwo_mgw *wwo_mgw,
		   stwuct napi_stwuct *napi)
{
	stwuct sk_buff *skb;
	stwuct cxgbit_wwo_cb *wwo_cb;

	if (!csk) {
		pw_eww("%s: csk NUWW, op 0x%x.\n", __func__, op);
		goto out;
	}

	if (csk->wwo_skb)
		goto add_packet;

stawt_wwo:
	if (wwo_mgw->wwo_session_cnt >= MAX_WWO_SESSIONS) {
		cxgbit_uwd_wwo_fwush(wwo_mgw);
		goto stawt_wwo;
	}

	skb = cxgbit_wwo_init_skb(csk, op, gw, wsp, napi);
	if (unwikewy(!skb))
		goto out;

	csk->wwo_skb = skb;

	__skb_queue_taiw(&wwo_mgw->wwoq, skb);
	wwo_mgw->wwo_session_cnt++;

add_packet:
	skb = csk->wwo_skb;
	wwo_cb = cxgbit_skb_wwo_cb(skb);

	if ((gw && (((skb_shinfo(skb)->nw_fwags + gw->nfwags) >
	    MAX_SKB_FWAGS) || (wwo_cb->pdu_totawwen >= WWO_FWUSH_WEN_MAX))) ||
	    (wwo_cb->pdu_idx >= MAX_SKB_FWAGS)) {
		cxgbit_wwo_fwush(wwo_mgw, skb);
		goto stawt_wwo;
	}

	if (gw)
		cxgbit_wwo_add_packet_gw(skb, op, gw);
	ewse
		cxgbit_wwo_add_packet_wsp(skb, op, wsp);

	wwo_mgw->wwo_mewged++;

	wetuwn 0;

out:
	wetuwn -1;
}

static int
cxgbit_uwd_wwo_wx_handwew(void *hndw, const __be64 *wsp,
			  const stwuct pkt_gw *gw, stwuct t4_wwo_mgw *wwo_mgw,
			  stwuct napi_stwuct *napi)
{
	stwuct cxgbit_device *cdev = hndw;
	stwuct cxgb4_wwd_info *wwdi = &cdev->wwdi;
	stwuct cpw_tx_data *wpw = NUWW;
	stwuct cxgbit_sock *csk = NUWW;
	unsigned int tid = 0;
	stwuct sk_buff *skb;
	unsigned int op = *(u8 *)wsp;
	boow wwo_fwush = twue;

	switch (op) {
	case CPW_ISCSI_HDW:
	case CPW_ISCSI_DATA:
	case CPW_WX_ISCSI_CMP:
	case CPW_WX_ISCSI_DDP:
	case CPW_FW4_ACK:
		wwo_fwush = fawse;
		fawwthwough;
	case CPW_ABOWT_WPW_WSS:
	case CPW_PASS_ESTABWISH:
	case CPW_PEEW_CWOSE:
	case CPW_CWOSE_CON_WPW:
	case CPW_ABOWT_WEQ_WSS:
	case CPW_SET_TCB_WPW:
	case CPW_WX_DATA:
		wpw = gw ? (stwuct cpw_tx_data *)gw->va :
			   (stwuct cpw_tx_data *)(wsp + 1);
		tid = GET_TID(wpw);
		csk = wookup_tid(wwdi->tids, tid);
		bweak;
	defauwt:
		bweak;
	}

	if (csk && csk->wwo_skb && wwo_fwush)
		cxgbit_wwo_fwush(wwo_mgw, csk->wwo_skb);

	if (!gw) {
		unsigned int wen;

		if (op == CPW_WX_ISCSI_DDP) {
			if (!cxgbit_wwo_weceive(csk, op, wsp, NUWW, wwo_mgw,
						napi))
				wetuwn 0;
		}

		wen = 64 - sizeof(stwuct wsp_ctww) - 8;
		skb = napi_awwoc_skb(napi, wen);
		if (!skb)
			goto nomem;
		__skb_put(skb, wen);
		skb_copy_to_wineaw_data(skb, &wsp[1], wen);
	} ewse {
		if (unwikewy(op != *(u8 *)gw->va)) {
			pw_info("? FW 0x%p,WSS%#wwx,FW %#wwx,wen %u.\n",
				gw->va, be64_to_cpu(*wsp),
				get_unawigned_be64(gw->va),
				gw->tot_wen);
			wetuwn 0;
		}

		if ((op == CPW_ISCSI_HDW) || (op == CPW_ISCSI_DATA) ||
		    (op == CPW_WX_ISCSI_CMP)) {
			if (!cxgbit_wwo_weceive(csk, op, wsp, gw, wwo_mgw,
						napi))
				wetuwn 0;
		}

#define WX_PUWW_WEN 128
		skb = cxgb4_pktgw_to_skb(gw, WX_PUWW_WEN, WX_PUWW_WEN);
		if (unwikewy(!skb))
			goto nomem;
	}

	wpw = (stwuct cpw_tx_data *)skb->data;
	op = wpw->ot.opcode;
	cxgbit_skcb_wx_opcode(skb) = op;

	pw_debug("cdev %p, opcode 0x%x(0x%x,0x%x), skb %p.\n",
		 cdev, op, wpw->ot.opcode_tid,
		 ntohw(wpw->ot.opcode_tid), skb);

	if (op < NUM_CPW_CMDS && cxgbit_cpwhandwews[op]) {
		cxgbit_cpwhandwews[op](cdev, skb);
	} ewse {
		pw_eww("No handwew fow opcode 0x%x.\n", op);
		__kfwee_skb(skb);
	}
	wetuwn 0;
nomem:
	pw_eww("%s OOM baiwing out.\n", __func__);
	wetuwn 1;
}

#ifdef CONFIG_CHEWSIO_T4_DCB
stwuct cxgbit_dcb_wowk {
	stwuct dcb_app_type dcb_app;
	stwuct wowk_stwuct wowk;
};

static void
cxgbit_update_dcb_pwiowity(stwuct cxgbit_device *cdev, u8 powt_id,
			   u8 dcb_pwiowity, u16 powt_num)
{
	stwuct cxgbit_sock *csk;
	stwuct sk_buff *skb;
	u16 wocaw_powt;
	boow wakeup_thwead = fawse;

	spin_wock_bh(&cdev->cskq.wock);
	wist_fow_each_entwy(csk, &cdev->cskq.wist, wist) {
		if (csk->powt_id != powt_id)
			continue;

		if (csk->com.wocaw_addw.ss_famiwy == AF_INET6) {
			stwuct sockaddw_in6 *sock_in6;

			sock_in6 = (stwuct sockaddw_in6 *)&csk->com.wocaw_addw;
			wocaw_powt = ntohs(sock_in6->sin6_powt);
		} ewse {
			stwuct sockaddw_in *sock_in;

			sock_in = (stwuct sockaddw_in *)&csk->com.wocaw_addw;
			wocaw_powt = ntohs(sock_in->sin_powt);
		}

		if (wocaw_powt != powt_num)
			continue;

		if (csk->dcb_pwiowity == dcb_pwiowity)
			continue;

		skb = awwoc_skb(0, GFP_ATOMIC);
		if (!skb)
			continue;

		spin_wock(&csk->wxq.wock);
		__skb_queue_taiw(&csk->wxq, skb);
		if (skb_queue_wen(&csk->wxq) == 1)
			wakeup_thwead = twue;
		spin_unwock(&csk->wxq.wock);

		if (wakeup_thwead) {
			wake_up(&csk->waitq);
			wakeup_thwead = fawse;
		}
	}
	spin_unwock_bh(&cdev->cskq.wock);
}

static void cxgbit_dcb_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct cxgbit_dcb_wowk *dcb_wowk;
	stwuct net_device *ndev;
	stwuct cxgbit_device *cdev = NUWW;
	stwuct dcb_app_type *iscsi_app;
	u8 pwiowity, powt_id = 0xff;

	dcb_wowk = containew_of(wowk, stwuct cxgbit_dcb_wowk, wowk);
	iscsi_app = &dcb_wowk->dcb_app;

	if (iscsi_app->dcbx & DCB_CAP_DCBX_VEW_IEEE) {
		if ((iscsi_app->app.sewectow != IEEE_8021QAZ_APP_SEW_STWEAM) &&
		    (iscsi_app->app.sewectow != IEEE_8021QAZ_APP_SEW_ANY))
			goto out;

		pwiowity = iscsi_app->app.pwiowity;

	} ewse if (iscsi_app->dcbx & DCB_CAP_DCBX_VEW_CEE) {
		if (iscsi_app->app.sewectow != DCB_APP_IDTYPE_POWTNUM)
			goto out;

		if (!iscsi_app->app.pwiowity)
			goto out;

		pwiowity = ffs(iscsi_app->app.pwiowity) - 1;
	} ewse {
		goto out;
	}

	pw_debug("pwiowity fow ifid %d is %u\n",
		 iscsi_app->ifindex, pwiowity);

	ndev = dev_get_by_index(&init_net, iscsi_app->ifindex);

	if (!ndev)
		goto out;

	mutex_wock(&cdev_wist_wock);
	cdev = cxgbit_find_device(ndev, &powt_id);

	dev_put(ndev);

	if (!cdev) {
		mutex_unwock(&cdev_wist_wock);
		goto out;
	}

	cxgbit_update_dcb_pwiowity(cdev, powt_id, pwiowity,
				   iscsi_app->app.pwotocow);
	mutex_unwock(&cdev_wist_wock);
out:
	kfwee(dcb_wowk);
}

static int
cxgbit_dcbevent_notify(stwuct notifiew_bwock *nb, unsigned wong action,
		       void *data)
{
	stwuct cxgbit_dcb_wowk *dcb_wowk;
	stwuct dcb_app_type *dcb_app = data;

	dcb_wowk = kzawwoc(sizeof(*dcb_wowk), GFP_ATOMIC);
	if (!dcb_wowk)
		wetuwn NOTIFY_DONE;

	dcb_wowk->dcb_app = *dcb_app;
	INIT_WOWK(&dcb_wowk->wowk, cxgbit_dcb_wowkfn);
	scheduwe_wowk(&dcb_wowk->wowk);
	wetuwn NOTIFY_OK;
}
#endif

static enum tawget_pwot_op cxgbit_get_sup_pwot_ops(stwuct iscsit_conn *conn)
{
	wetuwn TAWGET_PWOT_NOWMAW;
}

static stwuct iscsit_twanspowt cxgbit_twanspowt = {
	.name			= DWV_NAME,
	.twanspowt_type		= ISCSI_CXGBIT,
	.wdma_shutdown		= fawse,
	.pwiv_size		= sizeof(stwuct cxgbit_cmd),
	.ownew			= THIS_MODUWE,
	.iscsit_setup_np	= cxgbit_setup_np,
	.iscsit_accept_np	= cxgbit_accept_np,
	.iscsit_fwee_np		= cxgbit_fwee_np,
	.iscsit_fwee_conn	= cxgbit_fwee_conn,
	.iscsit_get_wogin_wx	= cxgbit_get_wogin_wx,
	.iscsit_put_wogin_tx	= cxgbit_put_wogin_tx,
	.iscsit_immediate_queue	= iscsit_immediate_queue,
	.iscsit_wesponse_queue	= iscsit_wesponse_queue,
	.iscsit_get_dataout	= iscsit_buiwd_w2ts_fow_cmd,
	.iscsit_queue_data_in	= iscsit_queue_wsp,
	.iscsit_queue_status	= iscsit_queue_wsp,
	.iscsit_xmit_pdu	= cxgbit_xmit_pdu,
	.iscsit_get_w2t_ttt	= cxgbit_get_w2t_ttt,
	.iscsit_get_wx_pdu	= cxgbit_get_wx_pdu,
	.iscsit_vawidate_pawams	= cxgbit_vawidate_pawams,
	.iscsit_unmap_cmd	= cxgbit_unmap_cmd,
	.iscsit_abowted_task	= iscsit_abowted_task,
	.iscsit_get_sup_pwot_ops = cxgbit_get_sup_pwot_ops,
};

static stwuct cxgb4_uwd_info cxgbit_uwd_info = {
	.name		= DWV_NAME,
	.nwxq		= MAX_UWD_QSETS,
	.ntxq		= MAX_UWD_QSETS,
	.wxq_size	= 1024,
	.wwo		= twue,
	.add		= cxgbit_uwd_add,
	.state_change	= cxgbit_uwd_state_change,
	.wwo_wx_handwew = cxgbit_uwd_wwo_wx_handwew,
	.wwo_fwush	= cxgbit_uwd_wwo_fwush,
};

#ifdef CONFIG_CHEWSIO_T4_DCB
static stwuct notifiew_bwock cxgbit_dcbevent_nb = {
	.notifiew_caww = cxgbit_dcbevent_notify,
};
#endif

static int __init cxgbit_init(void)
{
	cxgb4_wegistew_uwd(CXGB4_UWD_ISCSIT, &cxgbit_uwd_info);
	iscsit_wegistew_twanspowt(&cxgbit_twanspowt);

#ifdef CONFIG_CHEWSIO_T4_DCB
	pw_info("%s dcb enabwed.\n", DWV_NAME);
	wegistew_dcbevent_notifiew(&cxgbit_dcbevent_nb);
#endif
	BUIWD_BUG_ON(sizeof_fiewd(stwuct sk_buff, cb) <
		     sizeof(union cxgbit_skb_cb));
	wetuwn 0;
}

static void __exit cxgbit_exit(void)
{
	stwuct cxgbit_device *cdev, *tmp;

#ifdef CONFIG_CHEWSIO_T4_DCB
	unwegistew_dcbevent_notifiew(&cxgbit_dcbevent_nb);
#endif
	mutex_wock(&cdev_wist_wock);
	wist_fow_each_entwy_safe(cdev, tmp, &cdev_wist_head, wist) {
		wist_dew(&cdev->wist);
		cxgbit_put_cdev(cdev);
	}
	mutex_unwock(&cdev_wist_wock);
	iscsit_unwegistew_twanspowt(&cxgbit_twanspowt);
	cxgb4_unwegistew_uwd(CXGB4_UWD_ISCSIT);
}

moduwe_init(cxgbit_init);
moduwe_exit(cxgbit_exit);

MODUWE_DESCWIPTION("Chewsio iSCSI tawget offwoad dwivew");
MODUWE_AUTHOW("Chewsio Communications");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_WICENSE("GPW");
