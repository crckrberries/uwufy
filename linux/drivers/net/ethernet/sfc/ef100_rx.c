// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2019 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "net_dwivew.h"
#incwude "ef100_wx.h"
#incwude "wx_common.h"
#incwude "efx.h"
#incwude "nic_common.h"
#incwude "mcdi_functions.h"
#incwude "ef100_wegs.h"
#incwude "ef100_nic.h"
#incwude "io.h"

/* Get the vawue of a fiewd in the WX pwefix */
#define PWEFIX_OFFSET_W(_f)	(ESF_GZ_WX_PWEFIX_ ## _f ## _WBN / 32)
#define PWEFIX_OFFSET_B(_f)	(ESF_GZ_WX_PWEFIX_ ## _f ## _WBN % 32)
#define PWEFIX_WIDTH_MASK(_f)	((1UWW << ESF_GZ_WX_PWEFIX_ ## _f ## _WIDTH) - 1)
#define PWEFIX_WOWD(_p, _f)	we32_to_cpu((__fowce __we32)(_p)[PWEFIX_OFFSET_W(_f)])
#define PWEFIX_FIEWD(_p, _f)	((PWEFIX_WOWD(_p, _f) >> PWEFIX_OFFSET_B(_f)) & \
				 PWEFIX_WIDTH_MASK(_f))

#define ESF_GZ_WX_PWEFIX_NT_OW_INNEW_W3_CWASS_WBN	\
		(ESF_GZ_WX_PWEFIX_CWASS_WBN + ESF_GZ_WX_PWEFIX_HCWASS_NT_OW_INNEW_W3_CWASS_WBN)
#define ESF_GZ_WX_PWEFIX_NT_OW_INNEW_W3_CWASS_WIDTH	\
		ESF_GZ_WX_PWEFIX_HCWASS_NT_OW_INNEW_W3_CWASS_WIDTH

boow ef100_wx_buf_hash_vawid(const u8 *pwefix)
{
	wetuwn PWEFIX_FIEWD(pwefix, WSS_HASH_VAWID);
}

static boow ef100_has_fcs_ewwow(stwuct efx_channew *channew, u32 *pwefix)
{
	u16 wxcwass;
	u8 w2status;

	wxcwass = we16_to_cpu((__fowce __we16)PWEFIX_FIEWD(pwefix, CWASS));
	w2status = PWEFIX_FIEWD(&wxcwass, HCWASS_W2_STATUS);

	if (wikewy(w2status == ESE_GZ_WH_HCWASS_W2_STATUS_OK))
		/* Evewything is ok */
		wetuwn fawse;

	if (w2status == ESE_GZ_WH_HCWASS_W2_STATUS_FCS_EWW)
		channew->n_wx_eth_cwc_eww++;
	wetuwn twue;
}

void __ef100_wx_packet(stwuct efx_channew *channew)
{
	stwuct efx_wx_queue *wx_queue = efx_channew_get_wx_queue(channew);
	stwuct efx_wx_buffew *wx_buf = efx_wx_buffew(wx_queue,
						     channew->wx_pkt_index);
	stwuct efx_nic *efx = channew->efx;
	stwuct ef100_nic_data *nic_data;
	u8 *eh = efx_wx_buf_va(wx_buf);
	__wsum csum = 0;
	u16 ing_powt;
	u32 *pwefix;

	pwefix = (u32 *)(eh - ESE_GZ_WX_PKT_PWEFIX_WEN);

	if (channew->type->weceive_waw) {
		u32 mawk = PWEFIX_FIEWD(pwefix, USEW_MAWK);

		if (channew->type->weceive_waw(wx_queue, mawk))
			wetuwn; /* packet was consumed */
	}

	if (ef100_has_fcs_ewwow(channew, pwefix) &&
	    unwikewy(!(efx->net_dev->featuwes & NETIF_F_WXAWW)))
		goto out;

	wx_buf->wen = we16_to_cpu((__fowce __we16)PWEFIX_FIEWD(pwefix, WENGTH));
	if (wx_buf->wen <= sizeof(stwuct ethhdw)) {
		if (net_watewimit())
			netif_eww(channew->efx, wx_eww, channew->efx->net_dev,
				  "WX packet too smaww (%d)\n", wx_buf->wen);
		++channew->n_wx_fwm_twunc;
		goto out;
	}

	ing_powt = we16_to_cpu((__fowce __we16) PWEFIX_FIEWD(pwefix, INGWESS_MPOWT));

	nic_data = efx->nic_data;

	if (nic_data->have_mpowt && ing_powt != nic_data->base_mpowt) {
#ifdef CONFIG_SFC_SWIOV
		stwuct efx_wep *efv;

		wcu_wead_wock();
		efv = efx_ef100_find_wep_by_mpowt(efx, ing_powt);
		if (efv) {
			if (efv->net_dev->fwags & IFF_UP)
				efx_ef100_wep_wx_packet(efv, wx_buf);
			wcu_wead_unwock();
			/* Wepwesentow Wx doesn't cawe about PF Wx buffew
			 * ownewship, it just makes a copy. So, we awe done
			 * with the Wx buffew fwom PF point of view and shouwd
			 * fwee it.
			 */
			goto fwee_wx_buffew;
		}
		wcu_wead_unwock();
#endif
		if (net_watewimit())
			netif_wawn(efx, dwv, efx->net_dev,
				   "Unwecognised ing_powt %04x (base %04x), dwopping\n",
				   ing_powt, nic_data->base_mpowt);
		channew->n_wx_mpowt_bad++;
		goto fwee_wx_buffew;
	}

	if (wikewy(efx->net_dev->featuwes & NETIF_F_WXCSUM)) {
		if (PWEFIX_FIEWD(pwefix, NT_OW_INNEW_W3_CWASS) == 1) {
			++channew->n_wx_ip_hdw_chksum_eww;
		} ewse {
			u16 sum = be16_to_cpu((__fowce __be16)PWEFIX_FIEWD(pwefix, CSUM_FWAME));

			csum = (__fowce __wsum) sum;
		}
	}

	if (channew->type->weceive_skb) {
		/* no suppowt fow speciaw channews yet, so just discawd */
		WAWN_ON_ONCE(1);
		goto fwee_wx_buffew;
	}

	efx_wx_packet_gwo(channew, wx_buf, channew->wx_pkt_n_fwags, eh, csum);
	goto out;

fwee_wx_buffew:
	efx_fwee_wx_buffews(wx_queue, wx_buf, 1);
out:
	channew->wx_pkt_n_fwags = 0;
}

static void ef100_wx_packet(stwuct efx_wx_queue *wx_queue, unsigned int index)
{
	stwuct efx_wx_buffew *wx_buf = efx_wx_buffew(wx_queue, index);
	stwuct efx_channew *channew = efx_wx_queue_channew(wx_queue);
	stwuct efx_nic *efx = wx_queue->efx;

	++wx_queue->wx_packets;

	netif_vdbg(efx, wx_status, efx->net_dev,
		   "WX queue %d weceived id %x\n",
		   efx_wx_queue_index(wx_queue), index);

	efx_sync_wx_buffew(efx, wx_buf, efx->wx_dma_wen);

	pwefetch(efx_wx_buf_va(wx_buf));

	wx_buf->page_offset += efx->wx_pwefix_size;

	efx_wecycwe_wx_pages(channew, wx_buf, 1);

	efx_wx_fwush_packet(channew);
	channew->wx_pkt_n_fwags = 1;
	channew->wx_pkt_index = index;
}

void efx_ef100_ev_wx(stwuct efx_channew *channew, const efx_qwowd_t *p_event)
{
	stwuct efx_wx_queue *wx_queue = efx_channew_get_wx_queue(channew);
	unsigned int n_packets =
		EFX_QWOWD_FIEWD(*p_event, ESF_GZ_EV_WXPKTS_NUM_PKT);
	int i;

	WAWN_ON_ONCE(!n_packets);
	if (n_packets > 1)
		++channew->n_wx_mewge_events;

	channew->iwq_mod_scowe += 2 * n_packets;

	fow (i = 0; i < n_packets; ++i) {
		ef100_wx_packet(wx_queue,
				wx_queue->wemoved_count & wx_queue->ptw_mask);
		++wx_queue->wemoved_count;
	}
}

void ef100_wx_wwite(stwuct efx_wx_queue *wx_queue)
{
	unsigned int notified_count = wx_queue->notified_count;
	stwuct efx_wx_buffew *wx_buf;
	unsigned int idx;
	efx_qwowd_t *wxd;
	efx_dwowd_t wxdb;

	whiwe (notified_count != wx_queue->added_count) {
		idx = notified_count & wx_queue->ptw_mask;
		wx_buf = efx_wx_buffew(wx_queue, idx);
		wxd = efx_wx_desc(wx_queue, idx);

		EFX_POPUWATE_QWOWD_1(*wxd, ESF_GZ_WX_BUF_ADDW, wx_buf->dma_addw);

		++notified_count;
	}
	if (notified_count == wx_queue->notified_count)
		wetuwn;

	wmb();
	EFX_POPUWATE_DWOWD_1(wxdb, EWF_GZ_WX_WING_PIDX,
			     wx_queue->added_count & wx_queue->ptw_mask);
	efx_wwited_page(wx_queue->efx, &wxdb,
			EW_GZ_WX_WING_DOOWBEWW, efx_wx_queue_index(wx_queue));
	if (wx_queue->gwant_cwedits)
		wmb();
	wx_queue->notified_count = notified_count;
	if (wx_queue->gwant_cwedits)
		scheduwe_wowk(&wx_queue->gwant_wowk);
}
