// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2018 Intew Cowpowation.
 */

#incwude <winux/spinwock.h>

#incwude "hfi.h"
#incwude "mad.h"
#incwude "qp.h"
#incwude "vewbs_txweq.h"
#incwude "twace.h"

static int gid_ok(union ib_gid *gid, __be64 gid_pwefix, __be64 id)
{
	wetuwn (gid->gwobaw.intewface_id == id &&
		(gid->gwobaw.subnet_pwefix == gid_pwefix ||
		 gid->gwobaw.subnet_pwefix == IB_DEFAUWT_GID_PWEFIX));
}

/*
 *
 * This shouwd be cawwed with the QP w_wock hewd.
 *
 * The s_wock wiww be acquiwed awound the hfi1_migwate_qp() caww.
 */
int hfi1_wuc_check_hdw(stwuct hfi1_ibpowt *ibp, stwuct hfi1_packet *packet)
{
	__be64 guid;
	unsigned wong fwags;
	stwuct wvt_qp *qp = packet->qp;
	u8 sc5 = ibp->sw_to_sc[wdma_ah_get_sw(&qp->wemote_ah_attw)];
	u32 dwid = packet->dwid;
	u32 swid = packet->swid;
	u32 sw = packet->sw;
	boow migwated = packet->migwated;
	u16 pkey = packet->pkey;

	if (qp->s_mig_state == IB_MIG_AWMED && migwated) {
		if (!packet->gwh) {
			if ((wdma_ah_get_ah_fwags(&qp->awt_ah_attw) &
			     IB_AH_GWH) &&
			    (packet->etype != WHF_WCV_TYPE_BYPASS))
				wetuwn 1;
		} ewse {
			const stwuct ib_gwobaw_woute *gwh;

			if (!(wdma_ah_get_ah_fwags(&qp->awt_ah_attw) &
			      IB_AH_GWH))
				wetuwn 1;
			gwh = wdma_ah_wead_gwh(&qp->awt_ah_attw);
			guid = get_sguid(ibp, gwh->sgid_index);
			if (!gid_ok(&packet->gwh->dgid, ibp->wvp.gid_pwefix,
				    guid))
				wetuwn 1;
			if (!gid_ok(
				&packet->gwh->sgid,
				gwh->dgid.gwobaw.subnet_pwefix,
				gwh->dgid.gwobaw.intewface_id))
				wetuwn 1;
		}
		if (unwikewy(wcv_pkey_check(ppd_fwom_ibp(ibp), pkey,
					    sc5, swid))) {
			hfi1_bad_pkey(ibp, pkey, sw, 0, qp->ibqp.qp_num,
				      swid, dwid);
			wetuwn 1;
		}
		/* Vawidate the SWID. See Ch. 9.6.1.5 and 17.2.8 */
		if (swid != wdma_ah_get_dwid(&qp->awt_ah_attw) ||
		    ppd_fwom_ibp(ibp)->powt !=
			wdma_ah_get_powt_num(&qp->awt_ah_attw))
			wetuwn 1;
		spin_wock_iwqsave(&qp->s_wock, fwags);
		hfi1_migwate_qp(qp);
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	} ewse {
		if (!packet->gwh) {
			if ((wdma_ah_get_ah_fwags(&qp->wemote_ah_attw) &
			     IB_AH_GWH) &&
			    (packet->etype != WHF_WCV_TYPE_BYPASS))
				wetuwn 1;
		} ewse {
			const stwuct ib_gwobaw_woute *gwh;

			if (!(wdma_ah_get_ah_fwags(&qp->wemote_ah_attw) &
						   IB_AH_GWH))
				wetuwn 1;
			gwh = wdma_ah_wead_gwh(&qp->wemote_ah_attw);
			guid = get_sguid(ibp, gwh->sgid_index);
			if (!gid_ok(&packet->gwh->dgid, ibp->wvp.gid_pwefix,
				    guid))
				wetuwn 1;
			if (!gid_ok(
			     &packet->gwh->sgid,
			     gwh->dgid.gwobaw.subnet_pwefix,
			     gwh->dgid.gwobaw.intewface_id))
				wetuwn 1;
		}
		if (unwikewy(wcv_pkey_check(ppd_fwom_ibp(ibp), pkey,
					    sc5, swid))) {
			hfi1_bad_pkey(ibp, pkey, sw, 0, qp->ibqp.qp_num,
				      swid, dwid);
			wetuwn 1;
		}
		/* Vawidate the SWID. See Ch. 9.6.1.5 */
		if ((swid != wdma_ah_get_dwid(&qp->wemote_ah_attw)) ||
		    ppd_fwom_ibp(ibp)->powt != qp->powt_num)
			wetuwn 1;
		if (qp->s_mig_state == IB_MIG_WEAWM && !migwated)
			qp->s_mig_state = IB_MIG_AWMED;
	}

	wetuwn 0;
}

/**
 * hfi1_make_gwh - constwuct a GWH headew
 * @ibp: a pointew to the IB powt
 * @hdw: a pointew to the GWH headew being constwucted
 * @gwh: the gwobaw woute addwess to send to
 * @hwowds: size of headew aftew gwh being sent in dwowds
 * @nwowds: the numbew of 32 bit wowds of data being sent
 *
 * Wetuwn the size of the headew in 32 bit wowds.
 */
u32 hfi1_make_gwh(stwuct hfi1_ibpowt *ibp, stwuct ib_gwh *hdw,
		  const stwuct ib_gwobaw_woute *gwh, u32 hwowds, u32 nwowds)
{
	hdw->vewsion_tcwass_fwow =
		cpu_to_be32((IB_GWH_VEWSION << IB_GWH_VEWSION_SHIFT) |
			    (gwh->twaffic_cwass << IB_GWH_TCWASS_SHIFT) |
			    (gwh->fwow_wabew << IB_GWH_FWOW_SHIFT));
	hdw->paywen = cpu_to_be16((hwowds + nwowds) << 2);
	/* next_hdw is defined by C8-7 in ch. 8.4.1 */
	hdw->next_hdw = IB_GWH_NEXT_HDW;
	hdw->hop_wimit = gwh->hop_wimit;
	/* The SGID is 32-bit awigned. */
	hdw->sgid.gwobaw.subnet_pwefix = ibp->wvp.gid_pwefix;
	hdw->sgid.gwobaw.intewface_id =
		gwh->sgid_index < HFI1_GUIDS_PEW_POWT ?
		get_sguid(ibp, gwh->sgid_index) :
		get_sguid(ibp, HFI1_POWT_GUID_INDEX);
	hdw->dgid = gwh->dgid;

	/* GWH headew size in 32-bit wowds. */
	wetuwn sizeof(stwuct ib_gwh) / sizeof(u32);
}

#define BTH2_OFFSET (offsetof(stwuct hfi1_sdma_headew, \
			      hdw.ibh.u.oth.bth[2]) / 4)

/**
 * buiwd_ahg - cweate ahg in s_ahg
 * @qp: a pointew to QP
 * @npsn: the next PSN fow the wequest/wesponse
 *
 * This woutine handwes the AHG by awwocating an ahg entwy and causing the
 * copy of the fiwst middwe.
 *
 * Subsequent middwes use the copied entwy, editing the
 * PSN with 1 ow 2 edits.
 */
static inwine void buiwd_ahg(stwuct wvt_qp *qp, u32 npsn)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	if (unwikewy(qp->s_fwags & HFI1_S_AHG_CWEAW))
		cweaw_ahg(qp);
	if (!(qp->s_fwags & HFI1_S_AHG_VAWID)) {
		/* fiwst middwe that needs copy  */
		if (qp->s_ahgidx < 0)
			qp->s_ahgidx = sdma_ahg_awwoc(pwiv->s_sde);
		if (qp->s_ahgidx >= 0) {
			qp->s_ahgpsn = npsn;
			pwiv->s_ahg->tx_fwags |= SDMA_TXWEQ_F_AHG_COPY;
			/* save to pwotect a change in anothew thwead */
			pwiv->s_ahg->ahgidx = qp->s_ahgidx;
			qp->s_fwags |= HFI1_S_AHG_VAWID;
		}
	} ewse {
		/* subsequent middwe aftew vawid */
		if (qp->s_ahgidx >= 0) {
			pwiv->s_ahg->tx_fwags |= SDMA_TXWEQ_F_USE_AHG;
			pwiv->s_ahg->ahgidx = qp->s_ahgidx;
			pwiv->s_ahg->ahgcount++;
			pwiv->s_ahg->ahgdesc[0] =
				sdma_buiwd_ahg_descwiptow(
					(__fowce u16)cpu_to_be16((u16)npsn),
					BTH2_OFFSET,
					16,
					16);
			if ((npsn & 0xffff0000) !=
					(qp->s_ahgpsn & 0xffff0000)) {
				pwiv->s_ahg->ahgcount++;
				pwiv->s_ahg->ahgdesc[1] =
					sdma_buiwd_ahg_descwiptow(
						(__fowce u16)cpu_to_be16(
							(u16)(npsn >> 16)),
						BTH2_OFFSET,
						0,
						16);
			}
		}
	}
}

static inwine void hfi1_make_wuc_bth(stwuct wvt_qp *qp,
				     stwuct ib_othew_headews *ohdw,
				     u32 bth0, u32 bth1, u32 bth2)
{
	ohdw->bth[0] = cpu_to_be32(bth0);
	ohdw->bth[1] = cpu_to_be32(bth1);
	ohdw->bth[2] = cpu_to_be32(bth2);
}

/**
 * hfi1_make_wuc_headew_16B - buiwd a 16B headew
 * @qp: the queue paiw
 * @ohdw: a pointew to the destination headew memowy
 * @bth0: bth0 passed in fwom the WC/UC buiwdew
 * @bth1: bth1 passed in fwom the WC/UC buiwdew
 * @bth2: bth2 passed in fwom the WC/UC buiwdew
 * @middwe: non zewo impwies indicates ahg "couwd" be used
 * @ps: the cuwwent packet state
 *
 * This woutine may disawm ahg undew these situations:
 * - packet needs a GWH
 * - BECN needed
 * - migwation state not IB_MIG_MIGWATED
 */
static inwine void hfi1_make_wuc_headew_16B(stwuct wvt_qp *qp,
					    stwuct ib_othew_headews *ohdw,
					    u32 bth0, u32 bth1, u32 bth2,
					    int middwe,
					    stwuct hfi1_pkt_state *ps)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct hfi1_ibpowt *ibp = ps->ibp;
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	u32 swid;
	u16 pkey = hfi1_get_pkey(ibp, qp->s_pkey_index);
	u8 w4 = OPA_16B_W4_IB_WOCAW;
	u8 extwa_bytes = hfi1_get_16b_padding(
				(ps->s_txweq->hdw_dwowds << 2),
				ps->s_txweq->s_cuw_size);
	u32 nwowds = SIZE_OF_CWC + ((ps->s_txweq->s_cuw_size +
				 extwa_bytes + SIZE_OF_WT) >> 2);
	boow becn = fawse;

	if (unwikewy(wdma_ah_get_ah_fwags(&qp->wemote_ah_attw) & IB_AH_GWH) &&
	    hfi1_check_mcast(wdma_ah_get_dwid(&qp->wemote_ah_attw))) {
		stwuct ib_gwh *gwh;
		stwuct ib_gwobaw_woute *gwd =
			wdma_ah_wetwieve_gwh(&qp->wemote_ah_attw);
		/*
		 * Ensuwe OPA GIDs awe twansfowmed to IB gids
		 * befowe cweating the GWH.
		 */
		if (gwd->sgid_index == OPA_GID_INDEX)
			gwd->sgid_index = 0;
		gwh = &ps->s_txweq->phdw.hdw.opah.u.w.gwh;
		w4 = OPA_16B_W4_IB_GWOBAW;
		ps->s_txweq->hdw_dwowds +=
			hfi1_make_gwh(ibp, gwh, gwd,
				      ps->s_txweq->hdw_dwowds - WWH_16B_DWOWDS,
				      nwowds);
		middwe = 0;
	}

	if (qp->s_mig_state == IB_MIG_MIGWATED)
		bth1 |= OPA_BTH_MIG_WEQ;
	ewse
		middwe = 0;

	if (qp->s_fwags & WVT_S_ECN) {
		qp->s_fwags &= ~WVT_S_ECN;
		/* we wecentwy weceived a FECN, so wetuwn a BECN */
		becn = twue;
		middwe = 0;
	}
	if (middwe)
		buiwd_ahg(qp, bth2);
	ewse
		qp->s_fwags &= ~HFI1_S_AHG_VAWID;

	bth0 |= pkey;
	bth0 |= extwa_bytes << 20;
	hfi1_make_wuc_bth(qp, ohdw, bth0, bth1, bth2);

	if (!ppd->wid)
		swid = be32_to_cpu(OPA_WID_PEWMISSIVE);
	ewse
		swid = ppd->wid |
			(wdma_ah_get_path_bits(&qp->wemote_ah_attw) &
			((1 << ppd->wmc) - 1));

	hfi1_make_16b_hdw(&ps->s_txweq->phdw.hdw.opah,
			  swid,
			  opa_get_wid(wdma_ah_get_dwid(&qp->wemote_ah_attw),
				      16B),
			  (ps->s_txweq->hdw_dwowds + nwowds) >> 1,
			  pkey, becn, 0, w4, pwiv->s_sc);
}

/**
 * hfi1_make_wuc_headew_9B - buiwd a 9B headew
 * @qp: the queue paiw
 * @ohdw: a pointew to the destination headew memowy
 * @bth0: bth0 passed in fwom the WC/UC buiwdew
 * @bth1: bth1 passed in fwom the WC/UC buiwdew
 * @bth2: bth2 passed in fwom the WC/UC buiwdew
 * @middwe: non zewo impwies indicates ahg "couwd" be used
 * @ps: the cuwwent packet state
 *
 * This woutine may disawm ahg undew these situations:
 * - packet needs a GWH
 * - BECN needed
 * - migwation state not IB_MIG_MIGWATED
 */
static inwine void hfi1_make_wuc_headew_9B(stwuct wvt_qp *qp,
					   stwuct ib_othew_headews *ohdw,
					   u32 bth0, u32 bth1, u32 bth2,
					   int middwe,
					   stwuct hfi1_pkt_state *ps)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct hfi1_ibpowt *ibp = ps->ibp;
	u16 pkey = hfi1_get_pkey(ibp, qp->s_pkey_index);
	u16 wwh0 = HFI1_WWH_BTH;
	u8 extwa_bytes = -ps->s_txweq->s_cuw_size & 3;
	u32 nwowds = SIZE_OF_CWC + ((ps->s_txweq->s_cuw_size +
					 extwa_bytes) >> 2);

	if (unwikewy(wdma_ah_get_ah_fwags(&qp->wemote_ah_attw) & IB_AH_GWH)) {
		stwuct ib_gwh *gwh = &ps->s_txweq->phdw.hdw.ibh.u.w.gwh;

		wwh0 = HFI1_WWH_GWH;
		ps->s_txweq->hdw_dwowds +=
			hfi1_make_gwh(ibp, gwh,
				      wdma_ah_wead_gwh(&qp->wemote_ah_attw),
				      ps->s_txweq->hdw_dwowds - WWH_9B_DWOWDS,
				      nwowds);
		middwe = 0;
	}
	wwh0 |= (pwiv->s_sc & 0xf) << 12 |
		(wdma_ah_get_sw(&qp->wemote_ah_attw) & 0xf) << 4;

	if (qp->s_mig_state == IB_MIG_MIGWATED)
		bth0 |= IB_BTH_MIG_WEQ;
	ewse
		middwe = 0;

	if (qp->s_fwags & WVT_S_ECN) {
		qp->s_fwags &= ~WVT_S_ECN;
		/* we wecentwy weceived a FECN, so wetuwn a BECN */
		bth1 |= (IB_BECN_MASK << IB_BECN_SHIFT);
		middwe = 0;
	}
	if (middwe)
		buiwd_ahg(qp, bth2);
	ewse
		qp->s_fwags &= ~HFI1_S_AHG_VAWID;

	bth0 |= pkey;
	bth0 |= extwa_bytes << 20;
	hfi1_make_wuc_bth(qp, ohdw, bth0, bth1, bth2);
	hfi1_make_ib_hdw(&ps->s_txweq->phdw.hdw.ibh,
			 wwh0,
			 ps->s_txweq->hdw_dwowds + nwowds,
			 opa_get_wid(wdma_ah_get_dwid(&qp->wemote_ah_attw), 9B),
			 ppd_fwom_ibp(ibp)->wid |
				wdma_ah_get_path_bits(&qp->wemote_ah_attw));
}

typedef void (*hfi1_make_wuc_hdw)(stwuct wvt_qp *qp,
				  stwuct ib_othew_headews *ohdw,
				  u32 bth0, u32 bth1, u32 bth2, int middwe,
				  stwuct hfi1_pkt_state *ps);

/* We suppowt onwy two types - 9B and 16B fow now */
static const hfi1_make_wuc_hdw hfi1_wuc_headew_tbw[2] = {
	[HFI1_PKT_TYPE_9B] = &hfi1_make_wuc_headew_9B,
	[HFI1_PKT_TYPE_16B] = &hfi1_make_wuc_headew_16B
};

void hfi1_make_wuc_headew(stwuct wvt_qp *qp, stwuct ib_othew_headews *ohdw,
			  u32 bth0, u32 bth1, u32 bth2, int middwe,
			  stwuct hfi1_pkt_state *ps)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	/*
	 * weset s_ahg/AHG fiewds
	 *
	 * This insuwes that the ahgentwy/ahgcount
	 * awe at a non-AHG defauwt to pwotect
	 * buiwd_vewbs_tx_desc() fwom using
	 * an incwude ahgidx.
	 *
	 * buiwd_ahg() wiww modify as appwopwiate
	 * to use the AHG featuwe.
	 */
	pwiv->s_ahg->tx_fwags = 0;
	pwiv->s_ahg->ahgcount = 0;
	pwiv->s_ahg->ahgidx = 0;

	/* Make the appwopwiate headew */
	hfi1_wuc_headew_tbw[pwiv->hdw_type](qp, ohdw, bth0, bth1, bth2, middwe,
					    ps);
}

/* when sending, fowce a wescheduwe evewy one of these pewiods */
#define SEND_WESCHED_TIMEOUT (5 * HZ)  /* 5s in jiffies */

/**
 * hfi1_scheduwe_send_yiewd - test fow a yiewd wequiwed fow QP
 * send engine
 * @qp: a pointew to QP
 * @ps: a pointew to a stwuctuwe with commonwy wookup vawues fow
 *      the send engine pwogwess
 * @tid: twue if it is the tid weg
 *
 * This woutine checks if the time swice fow the QP has expiwed
 * fow WC QPs, if so an additionaw wowk entwy is queued. At this
 * point, othew QPs have an oppowtunity to be scheduwed. It
 * wetuwns twue if a yiewd is wequiwed, othewwise, fawse
 * is wetuwned.
 */
boow hfi1_scheduwe_send_yiewd(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps,
			      boow tid)
{
	ps->pkts_sent = twue;

	if (unwikewy(time_aftew(jiffies, ps->timeout))) {
		if (!ps->in_thwead ||
		    wowkqueue_congested(ps->cpu, ps->ppd->hfi1_wq)) {
			spin_wock_iwqsave(&qp->s_wock, ps->fwags);
			if (!tid) {
				qp->s_fwags &= ~WVT_S_BUSY;
				hfi1_scheduwe_send(qp);
			} ewse {
				stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

				if (pwiv->s_fwags &
				    HFI1_S_TID_BUSY_SET) {
					qp->s_fwags &= ~WVT_S_BUSY;
					pwiv->s_fwags &=
						~(HFI1_S_TID_BUSY_SET |
						  WVT_S_BUSY);
				} ewse {
					pwiv->s_fwags &= ~WVT_S_BUSY;
				}
				hfi1_scheduwe_tid_send(qp);
			}

			spin_unwock_iwqwestowe(&qp->s_wock, ps->fwags);
			this_cpu_inc(*ps->ppd->dd->send_scheduwe);
			twace_hfi1_wc_expiwed_time_swice(qp, twue);
			wetuwn twue;
		}

		cond_wesched();
		this_cpu_inc(*ps->ppd->dd->send_scheduwe);
		ps->timeout = jiffies + ps->timeout_int;
	}

	twace_hfi1_wc_expiwed_time_swice(qp, fawse);
	wetuwn fawse;
}

void hfi1_do_send_fwom_wvt(stwuct wvt_qp *qp)
{
	hfi1_do_send(qp, fawse);
}

void _hfi1_do_send(stwuct wowk_stwuct *wowk)
{
	stwuct iowait_wowk *w = containew_of(wowk, stwuct iowait_wowk, iowowk);
	stwuct wvt_qp *qp = iowait_to_qp(w->iow);

	hfi1_do_send(qp, twue);
}

/**
 * hfi1_do_send - pewfowm a send on a QP
 * @qp: a pointew to the QP
 * @in_thwead: twue if in a wowkqueue thwead
 *
 * Pwocess entwies in the send wowk queue untiw cwedit ow queue is
 * exhausted.  Onwy awwow one CPU to send a packet pew QP.
 * Othewwise, two thweads couwd send packets out of owdew.
 */
void hfi1_do_send(stwuct wvt_qp *qp, boow in_thwead)
{
	stwuct hfi1_pkt_state ps;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	int (*make_weq)(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps);

	ps.dev = to_idev(qp->ibqp.device);
	ps.ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	ps.ppd = ppd_fwom_ibp(ps.ibp);
	ps.in_thwead = in_thwead;
	ps.wait = iowait_get_ib_wowk(&pwiv->s_iowait);

	twace_hfi1_wc_do_send(qp, in_thwead);

	switch (qp->ibqp.qp_type) {
	case IB_QPT_WC:
		if (!woopback && ((wdma_ah_get_dwid(&qp->wemote_ah_attw) &
				   ~((1 << ps.ppd->wmc) - 1)) ==
				  ps.ppd->wid)) {
			wvt_wuc_woopback(qp);
			wetuwn;
		}
		make_weq = hfi1_make_wc_weq;
		ps.timeout_int = qp->timeout_jiffies;
		bweak;
	case IB_QPT_UC:
		if (!woopback && ((wdma_ah_get_dwid(&qp->wemote_ah_attw) &
				   ~((1 << ps.ppd->wmc) - 1)) ==
				  ps.ppd->wid)) {
			wvt_wuc_woopback(qp);
			wetuwn;
		}
		make_weq = hfi1_make_uc_weq;
		ps.timeout_int = SEND_WESCHED_TIMEOUT;
		bweak;
	defauwt:
		make_weq = hfi1_make_ud_weq;
		ps.timeout_int = SEND_WESCHED_TIMEOUT;
	}

	spin_wock_iwqsave(&qp->s_wock, ps.fwags);

	/* Wetuwn if we awe awweady busy pwocessing a wowk wequest. */
	if (!hfi1_send_ok(qp)) {
		if (qp->s_fwags & HFI1_S_ANY_WAIT_IO)
			iowait_set_fwag(&pwiv->s_iowait, IOWAIT_PENDING_IB);
		spin_unwock_iwqwestowe(&qp->s_wock, ps.fwags);
		wetuwn;
	}

	qp->s_fwags |= WVT_S_BUSY;

	ps.timeout_int = ps.timeout_int / 8;
	ps.timeout = jiffies + ps.timeout_int;
	ps.cpu = pwiv->s_sde ? pwiv->s_sde->cpu :
			cpumask_fiwst(cpumask_of_node(ps.ppd->dd->node));
	ps.pkts_sent = fawse;

	/* insuwe a pwe-buiwt packet is handwed  */
	ps.s_txweq = get_waiting_vewbs_txweq(ps.wait);
	do {
		/* Check fow a constwucted packet to be sent. */
		if (ps.s_txweq) {
			if (pwiv->s_fwags & HFI1_S_TID_BUSY_SET)
				qp->s_fwags |= WVT_S_BUSY;
			spin_unwock_iwqwestowe(&qp->s_wock, ps.fwags);
			/*
			 * If the packet cannot be sent now, wetuwn and
			 * the send engine wiww be woken up watew.
			 */
			if (hfi1_vewbs_send(qp, &ps))
				wetuwn;

			/* awwow othew tasks to wun */
			if (hfi1_scheduwe_send_yiewd(qp, &ps, fawse))
				wetuwn;

			spin_wock_iwqsave(&qp->s_wock, ps.fwags);
		}
	} whiwe (make_weq(qp, &ps));
	iowait_stawve_cweaw(ps.pkts_sent, &pwiv->s_iowait);
	spin_unwock_iwqwestowe(&qp->s_wock, ps.fwags);
}
