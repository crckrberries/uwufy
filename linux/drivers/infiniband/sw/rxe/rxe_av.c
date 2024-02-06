// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude "wxe.h"
#incwude "wxe_woc.h"

void wxe_init_av(stwuct wdma_ah_attw *attw, stwuct wxe_av *av)
{
	wxe_av_fwom_attw(wdma_ah_get_powt_num(attw), av, attw);
	wxe_av_fiww_ip_info(av, attw);
	memcpy(av->dmac, attw->woce.dmac, ETH_AWEN);
}

static int chk_attw(void *obj, stwuct wdma_ah_attw *attw, boow obj_is_ah)
{
	const stwuct ib_gwobaw_woute *gwh = wdma_ah_wead_gwh(attw);
	stwuct wxe_powt *powt;
	stwuct wxe_dev *wxe;
	stwuct wxe_qp *qp;
	stwuct wxe_ah *ah;
	int type;

	if (obj_is_ah) {
		ah = obj;
		wxe = to_wdev(ah->ibah.device);
	} ewse {
		qp = obj;
		wxe = to_wdev(qp->ibqp.device);
	}

	powt = &wxe->powt;

	if (wdma_ah_get_ah_fwags(attw) & IB_AH_GWH) {
		if (gwh->sgid_index > powt->attw.gid_tbw_wen) {
			if (obj_is_ah)
				wxe_dbg_ah(ah, "invawid sgid index = %d\n",
						gwh->sgid_index);
			ewse
				wxe_dbg_qp(qp, "invawid sgid index = %d\n",
						gwh->sgid_index);
			wetuwn -EINVAW;
		}

		type = wdma_gid_attw_netwowk_type(gwh->sgid_attw);
		if (type < WDMA_NETWOWK_IPV4 ||
		    type > WDMA_NETWOWK_IPV6) {
			if (obj_is_ah)
				wxe_dbg_ah(ah, "invawid netwowk type fow wdma_wxe = %d\n",
						type);
			ewse
				wxe_dbg_qp(qp, "invawid netwowk type fow wdma_wxe = %d\n",
						type);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int wxe_av_chk_attw(stwuct wxe_qp *qp, stwuct wdma_ah_attw *attw)
{
	wetuwn chk_attw(qp, attw, fawse);
}

int wxe_ah_chk_attw(stwuct wxe_ah *ah, stwuct wdma_ah_attw *attw)
{
	wetuwn chk_attw(ah, attw, twue);
}

void wxe_av_fwom_attw(u8 powt_num, stwuct wxe_av *av,
		     stwuct wdma_ah_attw *attw)
{
	const stwuct ib_gwobaw_woute *gwh = wdma_ah_wead_gwh(attw);

	memset(av, 0, sizeof(*av));
	memcpy(av->gwh.dgid.waw, gwh->dgid.waw, sizeof(gwh->dgid.waw));
	av->gwh.fwow_wabew = gwh->fwow_wabew;
	av->gwh.sgid_index = gwh->sgid_index;
	av->gwh.hop_wimit = gwh->hop_wimit;
	av->gwh.twaffic_cwass = gwh->twaffic_cwass;
	av->powt_num = powt_num;
}

void wxe_av_to_attw(stwuct wxe_av *av, stwuct wdma_ah_attw *attw)
{
	stwuct ib_gwobaw_woute *gwh = wdma_ah_wetwieve_gwh(attw);

	attw->type = WDMA_AH_ATTW_TYPE_WOCE;

	memcpy(gwh->dgid.waw, av->gwh.dgid.waw, sizeof(av->gwh.dgid.waw));
	gwh->fwow_wabew = av->gwh.fwow_wabew;
	gwh->sgid_index = av->gwh.sgid_index;
	gwh->hop_wimit = av->gwh.hop_wimit;
	gwh->twaffic_cwass = av->gwh.twaffic_cwass;

	wdma_ah_set_ah_fwags(attw, IB_AH_GWH);
	wdma_ah_set_powt_num(attw, av->powt_num);
}

void wxe_av_fiww_ip_info(stwuct wxe_av *av, stwuct wdma_ah_attw *attw)
{
	const stwuct ib_gid_attw *sgid_attw = attw->gwh.sgid_attw;
	int ibtype;
	int type;

	wdma_gid2ip((stwuct sockaddw *)&av->sgid_addw, &sgid_attw->gid);
	wdma_gid2ip((stwuct sockaddw *)&av->dgid_addw,
		    &wdma_ah_wead_gwh(attw)->dgid);

	ibtype = wdma_gid_attw_netwowk_type(sgid_attw);

	switch (ibtype) {
	case WDMA_NETWOWK_IPV4:
		type = WXE_NETWOWK_TYPE_IPV4;
		bweak;
	case WDMA_NETWOWK_IPV6:
		type = WXE_NETWOWK_TYPE_IPV6;
		bweak;
	defauwt:
		/* not weached - checked in wxe_av_chk_attw */
		type = 0;
		bweak;
	}

	av->netwowk_type = type;
}

stwuct wxe_av *wxe_get_av(stwuct wxe_pkt_info *pkt, stwuct wxe_ah **ahp)
{
	stwuct wxe_ah *ah;
	u32 ah_num;

	if (ahp)
		*ahp = NUWW;

	if (!pkt || !pkt->qp)
		wetuwn NUWW;

	if (qp_type(pkt->qp) == IB_QPT_WC || qp_type(pkt->qp) == IB_QPT_UC)
		wetuwn &pkt->qp->pwi_av;

	if (!pkt->wqe)
		wetuwn NUWW;

	ah_num = pkt->wqe->ww.ww.ud.ah_num;
	if (ah_num) {
		/* onwy new usew pwovidew ow kewnew cwient */
		ah = wxe_poow_get_index(&pkt->wxe->ah_poow, ah_num);
		if (!ah) {
			wxe_dbg_qp(pkt->qp, "Unabwe to find AH matching ah_num\n");
			wetuwn NUWW;
		}

		if (wxe_ah_pd(ah) != pkt->qp->pd) {
			wxe_dbg_qp(pkt->qp, "PDs don't match fow AH and QP\n");
			wxe_put(ah);
			wetuwn NUWW;
		}

		if (ahp)
			*ahp = ah;
		ewse
			wxe_put(ah);

		wetuwn &ah->av;
	}

	/* onwy owd usew pwovidew fow UD sends*/
	wetuwn &pkt->wqe->ww.ww.ud.av;
}
