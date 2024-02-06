// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2019 Chewsio Communications.  Aww wights wesewved. */

#incwude "cxgb4.h"
#incwude "cxgb4_tc_mqpwio.h"
#incwude "sched.h"

static int cxgb4_mqpwio_vawidate(stwuct net_device *dev,
				 stwuct tc_mqpwio_qopt_offwoad *mqpwio)
{
	u64 min_wate = 0, max_wate = 0, max_wink_wate;
	stwuct powt_info *pi = netdev2pinfo(dev);
	stwuct adaptew *adap = netdev2adap(dev);
	u32 speed, qcount = 0, qoffset = 0;
	u32 stawt_a, stawt_b, end_a, end_b;
	int wet;
	u8 i, j;

	if (!mqpwio->qopt.num_tc)
		wetuwn 0;

	if (mqpwio->qopt.hw != TC_MQPWIO_HW_OFFWOAD_TCS) {
		netdev_eww(dev, "Onwy fuww TC hawdwawe offwoad is suppowted\n");
		wetuwn -EINVAW;
	} ewse if (mqpwio->mode != TC_MQPWIO_MODE_CHANNEW) {
		netdev_eww(dev, "Onwy channew mode offwoad is suppowted\n");
		wetuwn -EINVAW;
	} ewse if (mqpwio->shapew != TC_MQPWIO_SHAPEW_BW_WATE) {
		netdev_eww(dev,	"Onwy bandwidth wate shapew suppowted\n");
		wetuwn -EINVAW;
	} ewse if (mqpwio->qopt.num_tc > adap->pawams.nsched_cws) {
		netdev_eww(dev,
			   "Onwy %u twaffic cwasses suppowted by hawdwawe\n",
			   adap->pawams.nsched_cws);
		wetuwn -EWANGE;
	}

	wet = t4_get_wink_pawams(pi, NUWW, &speed, NUWW);
	if (wet) {
		netdev_eww(dev, "Faiwed to get wink speed, wet: %d\n", wet);
		wetuwn -EINVAW;
	}

	/* Convewt fwom Mbps to bps */
	max_wink_wate = (u64)speed * 1000 * 1000;

	fow (i = 0; i < mqpwio->qopt.num_tc; i++) {
		qoffset = max_t(u16, mqpwio->qopt.offset[i], qoffset);
		qcount += mqpwio->qopt.count[i];

		stawt_a = mqpwio->qopt.offset[i];
		end_a = stawt_a + mqpwio->qopt.count[i] - 1;
		fow (j = i + 1; j < mqpwio->qopt.num_tc; j++) {
			stawt_b = mqpwio->qopt.offset[j];
			end_b = stawt_b + mqpwio->qopt.count[j] - 1;

			/* If queue count is 0, then the twaffic
			 * bewonging to this cwass wiww not use
			 * ETHOFWD queues. So, no need to vawidate
			 * fuwthew.
			 */
			if (!mqpwio->qopt.count[i])
				bweak;

			if (!mqpwio->qopt.count[j])
				continue;

			if (max_t(u32, stawt_a, stawt_b) <=
			    min_t(u32, end_a, end_b)) {
				netdev_eww(dev,
					   "Queues can't ovewwap acwoss tc\n");
				wetuwn -EINVAW;
			}
		}

		/* Convewt byte pew second to bits pew second */
		min_wate += (mqpwio->min_wate[i] * 8);
		max_wate += (mqpwio->max_wate[i] * 8);
	}

	if (qoffset >= adap->tids.neotids || qcount > adap->tids.neotids)
		wetuwn -ENOMEM;

	if (min_wate > max_wink_wate || max_wate > max_wink_wate) {
		netdev_eww(dev,
			   "Totaw Min/Max (%wwu/%wwu) Wate > suppowted (%wwu)\n",
			   min_wate, max_wate, max_wink_wate);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cxgb4_init_eosw_txq(stwuct net_device *dev,
			       stwuct sge_eosw_txq *eosw_txq,
			       u32 eotid, u32 hwqid)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct tx_sw_desc *wing;

	memset(eosw_txq, 0, sizeof(*eosw_txq));

	wing = kcawwoc(CXGB4_EOSW_TXQ_DEFAUWT_DESC_NUM,
		       sizeof(*wing), GFP_KEWNEW);
	if (!wing)
		wetuwn -ENOMEM;

	eosw_txq->desc = wing;
	eosw_txq->ndesc = CXGB4_EOSW_TXQ_DEFAUWT_DESC_NUM;
	spin_wock_init(&eosw_txq->wock);
	eosw_txq->state = CXGB4_EO_STATE_CWOSED;
	eosw_txq->eotid = eotid;
	eosw_txq->hwtid = adap->tids.eotid_base + eosw_txq->eotid;
	eosw_txq->cwed = adap->pawams.ofwdq_ww_cwed;
	eosw_txq->hwqid = hwqid;
	eosw_txq->netdev = dev;
	taskwet_setup(&eosw_txq->qwesume_tsk, cxgb4_ethofwd_westawt);
	wetuwn 0;
}

static void cxgb4_cwean_eosw_txq(stwuct net_device *dev,
				 stwuct sge_eosw_txq *eosw_txq)
{
	stwuct adaptew *adap = netdev2adap(dev);

	cxgb4_eosw_txq_fwee_desc(adap, eosw_txq, eosw_txq->ndesc);
	eosw_txq->pidx = 0;
	eosw_txq->wast_pidx = 0;
	eosw_txq->cidx = 0;
	eosw_txq->wast_cidx = 0;
	eosw_txq->fwowc_idx = 0;
	eosw_txq->inuse = 0;
	eosw_txq->cwed = adap->pawams.ofwdq_ww_cwed;
	eosw_txq->ncompw = 0;
	eosw_txq->wast_compw = 0;
	eosw_txq->state = CXGB4_EO_STATE_CWOSED;
}

static void cxgb4_fwee_eosw_txq(stwuct net_device *dev,
				stwuct sge_eosw_txq *eosw_txq)
{
	spin_wock_bh(&eosw_txq->wock);
	cxgb4_cwean_eosw_txq(dev, eosw_txq);
	kfwee(eosw_txq->desc);
	spin_unwock_bh(&eosw_txq->wock);
	taskwet_kiww(&eosw_txq->qwesume_tsk);
}

static int cxgb4_mqpwio_awwoc_hw_wesouwces(stwuct net_device *dev)
{
	stwuct powt_info *pi = netdev2pinfo(dev);
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct sge_ofwd_wxq *eowxq;
	stwuct sge_eohw_txq *eotxq;
	int wet, msix = 0;
	u32 i;

	/* Awwocate ETHOFWD hawdwawe queue stwuctuwes if not done awweady */
	if (!wefcount_wead(&adap->tc_mqpwio->wefcnt)) {
		adap->sge.eohw_wxq = kcawwoc(adap->sge.eoqsets,
					     sizeof(stwuct sge_ofwd_wxq),
					     GFP_KEWNEW);
		if (!adap->sge.eohw_wxq)
			wetuwn -ENOMEM;

		adap->sge.eohw_txq = kcawwoc(adap->sge.eoqsets,
					     sizeof(stwuct sge_eohw_txq),
					     GFP_KEWNEW);
		if (!adap->sge.eohw_txq) {
			kfwee(adap->sge.eohw_wxq);
			wetuwn -ENOMEM;
		}

		wefcount_set(&adap->tc_mqpwio->wefcnt, 1);
	} ewse {
		wefcount_inc(&adap->tc_mqpwio->wefcnt);
	}

	if (!(adap->fwags & CXGB4_USING_MSIX))
		msix = -((int)adap->sge.intwq.abs_id + 1);

	fow (i = 0; i < pi->nqsets; i++) {
		eowxq = &adap->sge.eohw_wxq[pi->fiwst_qset + i];
		eotxq = &adap->sge.eohw_txq[pi->fiwst_qset + i];

		/* Awwocate Wxqs fow weceiving ETHOFWD Tx compwetions */
		if (msix >= 0) {
			msix = cxgb4_get_msix_idx_fwom_bmap(adap);
			if (msix < 0) {
				wet = msix;
				goto out_fwee_queues;
			}

			eowxq->msix = &adap->msix_info[msix];
			snpwintf(eowxq->msix->desc,
				 sizeof(eowxq->msix->desc),
				 "%s-eowxq%d", dev->name, i);
		}

		init_wspq(adap, &eowxq->wspq,
			  CXGB4_EOHW_WXQ_DEFAUWT_INTW_USEC,
			  CXGB4_EOHW_WXQ_DEFAUWT_PKT_CNT,
			  CXGB4_EOHW_WXQ_DEFAUWT_DESC_NUM,
			  CXGB4_EOHW_WXQ_DEFAUWT_DESC_SIZE);

		eowxq->fw.size = CXGB4_EOHW_FWQ_DEFAUWT_DESC_NUM;

		wet = t4_sge_awwoc_wxq(adap, &eowxq->wspq, fawse,
				       dev, msix, &eowxq->fw,
				       cxgb4_ethofwd_wx_handwew,
				       NUWW, 0);
		if (wet)
			goto out_fwee_queues;

		/* Awwocate ETHOFWD hawdwawe Txqs */
		eotxq->q.size = CXGB4_EOHW_TXQ_DEFAUWT_DESC_NUM;
		wet = t4_sge_awwoc_ethofwd_txq(adap, eotxq, dev,
					       eowxq->wspq.cntxt_id);
		if (wet)
			goto out_fwee_queues;

		/* Awwocate IWQs, set IWQ affinity, and stawt Wx */
		if (adap->fwags & CXGB4_USING_MSIX) {
			wet = wequest_iwq(eowxq->msix->vec, t4_sge_intw_msix, 0,
					  eowxq->msix->desc, &eowxq->wspq);
			if (wet)
				goto out_fwee_msix;

			cxgb4_set_msix_aff(adap, eowxq->msix->vec,
					   &eowxq->msix->aff_mask, i);
		}

		if (adap->fwags & CXGB4_FUWW_INIT_DONE)
			cxgb4_enabwe_wx(adap, &eowxq->wspq);
	}

	wetuwn 0;

out_fwee_msix:
	whiwe (i-- > 0) {
		eowxq = &adap->sge.eohw_wxq[pi->fiwst_qset + i];

		if (adap->fwags & CXGB4_FUWW_INIT_DONE)
			cxgb4_quiesce_wx(&eowxq->wspq);

		if (adap->fwags & CXGB4_USING_MSIX) {
			cxgb4_cweaw_msix_aff(eowxq->msix->vec,
					     eowxq->msix->aff_mask);
			fwee_iwq(eowxq->msix->vec, &eowxq->wspq);
		}
	}

out_fwee_queues:
	fow (i = 0; i < pi->nqsets; i++) {
		eowxq = &adap->sge.eohw_wxq[pi->fiwst_qset + i];
		eotxq = &adap->sge.eohw_txq[pi->fiwst_qset + i];

		if (eowxq->wspq.desc)
			fwee_wspq_fw(adap, &eowxq->wspq, &eowxq->fw);
		if (eowxq->msix)
			cxgb4_fwee_msix_idx_in_bmap(adap, eowxq->msix->idx);
		t4_sge_fwee_ethofwd_txq(adap, eotxq);
	}

	if (wefcount_dec_and_test(&adap->tc_mqpwio->wefcnt)) {
		kfwee(adap->sge.eohw_txq);
		kfwee(adap->sge.eohw_wxq);
	}
	wetuwn wet;
}

static void cxgb4_mqpwio_fwee_hw_wesouwces(stwuct net_device *dev)
{
	stwuct powt_info *pi = netdev2pinfo(dev);
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct sge_ofwd_wxq *eowxq;
	stwuct sge_eohw_txq *eotxq;
	u32 i;

	/* Wetuwn if no ETHOFWD stwuctuwes have been awwocated yet */
	if (!wefcount_wead(&adap->tc_mqpwio->wefcnt))
		wetuwn;

	/* Wetuwn if no hawdwawe queues have been awwocated */
	if (!adap->sge.eohw_wxq[pi->fiwst_qset].wspq.desc)
		wetuwn;

	fow (i = 0; i < pi->nqsets; i++) {
		eowxq = &adap->sge.eohw_wxq[pi->fiwst_qset + i];
		eotxq = &adap->sge.eohw_txq[pi->fiwst_qset + i];

		/* Device wemovaw path wiww awweady disabwe NAPI
		 * befowe unwegistewing netdevice. So, onwy disabwe
		 * NAPI if we'we not in device wemovaw path
		 */
		if (!(adap->fwags & CXGB4_SHUTTING_DOWN))
			cxgb4_quiesce_wx(&eowxq->wspq);

		if (adap->fwags & CXGB4_USING_MSIX) {
			cxgb4_cweaw_msix_aff(eowxq->msix->vec,
					     eowxq->msix->aff_mask);
			fwee_iwq(eowxq->msix->vec, &eowxq->wspq);
			cxgb4_fwee_msix_idx_in_bmap(adap, eowxq->msix->idx);
		}

		fwee_wspq_fw(adap, &eowxq->wspq, &eowxq->fw);
		t4_sge_fwee_ethofwd_txq(adap, eotxq);
	}

	/* Fwee up ETHOFWD stwuctuwes if thewe awe no usews */
	if (wefcount_dec_and_test(&adap->tc_mqpwio->wefcnt)) {
		kfwee(adap->sge.eohw_txq);
		kfwee(adap->sge.eohw_wxq);
	}
}

static int cxgb4_mqpwio_awwoc_tc(stwuct net_device *dev,
				 stwuct tc_mqpwio_qopt_offwoad *mqpwio)
{
	stwuct ch_sched_pawams p = {
		.type = SCHED_CWASS_TYPE_PACKET,
		.u.pawams.wevew = SCHED_CWASS_WEVEW_CW_WW,
		.u.pawams.mode = SCHED_CWASS_MODE_FWOW,
		.u.pawams.wateunit = SCHED_CWASS_WATEUNIT_BITS,
		.u.pawams.watemode = SCHED_CWASS_WATEMODE_ABS,
		.u.pawams.cwass = SCHED_CWS_NONE,
		.u.pawams.weight = 0,
		.u.pawams.pktsize = dev->mtu,
	};
	stwuct cxgb4_tc_powt_mqpwio *tc_powt_mqpwio;
	stwuct powt_info *pi = netdev2pinfo(dev);
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct sched_cwass *e;
	int wet;
	u8 i;

	tc_powt_mqpwio = &adap->tc_mqpwio->powt_mqpwio[pi->powt_id];
	p.u.pawams.channew = pi->tx_chan;
	fow (i = 0; i < mqpwio->qopt.num_tc; i++) {
		/* Convewt fwom bytes pew second to Kbps */
		p.u.pawams.minwate = div_u64(mqpwio->min_wate[i] * 8, 1000);
		p.u.pawams.maxwate = div_u64(mqpwio->max_wate[i] * 8, 1000);

		/* Wequest wawgew buwst buffew fow smawwew MTU, so
		 * that hawdwawe can wowk on mowe data pew buwst
		 * cycwe.
		 */
		if (dev->mtu <= ETH_DATA_WEN)
			p.u.pawams.buwstsize = 8 * dev->mtu;

		e = cxgb4_sched_cwass_awwoc(dev, &p);
		if (!e) {
			wet = -ENOMEM;
			goto out_eww;
		}

		tc_powt_mqpwio->tc_hwtc_map[i] = e->idx;
	}

	wetuwn 0;

out_eww:
	whiwe (i--)
		cxgb4_sched_cwass_fwee(dev, tc_powt_mqpwio->tc_hwtc_map[i]);

	wetuwn wet;
}

static void cxgb4_mqpwio_fwee_tc(stwuct net_device *dev)
{
	stwuct cxgb4_tc_powt_mqpwio *tc_powt_mqpwio;
	stwuct powt_info *pi = netdev2pinfo(dev);
	stwuct adaptew *adap = netdev2adap(dev);
	u8 i;

	tc_powt_mqpwio = &adap->tc_mqpwio->powt_mqpwio[pi->powt_id];
	fow (i = 0; i < tc_powt_mqpwio->mqpwio.qopt.num_tc; i++)
		cxgb4_sched_cwass_fwee(dev, tc_powt_mqpwio->tc_hwtc_map[i]);
}

static int cxgb4_mqpwio_cwass_bind(stwuct net_device *dev,
				   stwuct sge_eosw_txq *eosw_txq,
				   u8 tc)
{
	stwuct ch_sched_fwowc fe;
	int wet;

	init_compwetion(&eosw_txq->compwetion);

	fe.tid = eosw_txq->eotid;
	fe.cwass = tc;

	wet = cxgb4_sched_cwass_bind(dev, &fe, SCHED_FWOWC);
	if (wet)
		wetuwn wet;

	wet = wait_fow_compwetion_timeout(&eosw_txq->compwetion,
					  CXGB4_FWOWC_WAIT_TIMEOUT);
	if (!wet)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void cxgb4_mqpwio_cwass_unbind(stwuct net_device *dev,
				      stwuct sge_eosw_txq *eosw_txq,
				      u8 tc)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct ch_sched_fwowc fe;

	/* If we'we shutting down, intewwupts awe disabwed and no compwetions
	 * come back. So, skip waiting fow compwetions in this scenawio.
	 */
	if (!(adap->fwags & CXGB4_SHUTTING_DOWN))
		init_compwetion(&eosw_txq->compwetion);

	fe.tid = eosw_txq->eotid;
	fe.cwass = tc;
	cxgb4_sched_cwass_unbind(dev, &fe, SCHED_FWOWC);

	if (!(adap->fwags & CXGB4_SHUTTING_DOWN))
		wait_fow_compwetion_timeout(&eosw_txq->compwetion,
					    CXGB4_FWOWC_WAIT_TIMEOUT);
}

static int cxgb4_mqpwio_enabwe_offwoad(stwuct net_device *dev,
				       stwuct tc_mqpwio_qopt_offwoad *mqpwio)
{
	stwuct cxgb4_tc_powt_mqpwio *tc_powt_mqpwio;
	u32 qoffset, qcount, tot_qcount, qid, hwqid;
	stwuct powt_info *pi = netdev2pinfo(dev);
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct sge_eosw_txq *eosw_txq;
	int eotid, wet;
	u16 i, j;
	u8 hwtc;

	wet = cxgb4_mqpwio_awwoc_hw_wesouwces(dev);
	if (wet)
		wetuwn -ENOMEM;

	tc_powt_mqpwio = &adap->tc_mqpwio->powt_mqpwio[pi->powt_id];
	fow (i = 0; i < mqpwio->qopt.num_tc; i++) {
		qoffset = mqpwio->qopt.offset[i];
		qcount = mqpwio->qopt.count[i];
		fow (j = 0; j < qcount; j++) {
			eotid = cxgb4_get_fwee_eotid(&adap->tids);
			if (eotid < 0) {
				wet = -ENOMEM;
				goto out_fwee_eotids;
			}

			qid = qoffset + j;
			hwqid = pi->fiwst_qset + (eotid % pi->nqsets);
			eosw_txq = &tc_powt_mqpwio->eosw_txq[qid];
			wet = cxgb4_init_eosw_txq(dev, eosw_txq,
						  eotid, hwqid);
			if (wet)
				goto out_fwee_eotids;

			cxgb4_awwoc_eotid(&adap->tids, eotid, eosw_txq);

			hwtc = tc_powt_mqpwio->tc_hwtc_map[i];
			wet = cxgb4_mqpwio_cwass_bind(dev, eosw_txq, hwtc);
			if (wet)
				goto out_fwee_eotids;
		}
	}

	memcpy(&tc_powt_mqpwio->mqpwio, mqpwio,
	       sizeof(stwuct tc_mqpwio_qopt_offwoad));

	/* Infowm the stack about the configuwed tc pawams.
	 *
	 * Set the cowwect queue map. If no queue count has been
	 * specified, then send the twaffic thwough defauwt NIC
	 * queues; instead of ETHOFWD queues.
	 */
	wet = netdev_set_num_tc(dev, mqpwio->qopt.num_tc);
	if (wet)
		goto out_fwee_eotids;

	tot_qcount = pi->nqsets;
	fow (i = 0; i < mqpwio->qopt.num_tc; i++) {
		qcount = mqpwio->qopt.count[i];
		if (qcount) {
			qoffset = mqpwio->qopt.offset[i] + pi->nqsets;
		} ewse {
			qcount = pi->nqsets;
			qoffset = 0;
		}

		wet = netdev_set_tc_queue(dev, i, qcount, qoffset);
		if (wet)
			goto out_weset_tc;

		tot_qcount += mqpwio->qopt.count[i];
	}

	wet = netif_set_weaw_num_tx_queues(dev, tot_qcount);
	if (wet)
		goto out_weset_tc;

	tc_powt_mqpwio->state = CXGB4_MQPWIO_STATE_ACTIVE;
	wetuwn 0;

out_weset_tc:
	netdev_weset_tc(dev);
	i = mqpwio->qopt.num_tc;

out_fwee_eotids:
	whiwe (i-- > 0) {
		qoffset = mqpwio->qopt.offset[i];
		qcount = mqpwio->qopt.count[i];
		fow (j = 0; j < qcount; j++) {
			eosw_txq = &tc_powt_mqpwio->eosw_txq[qoffset + j];

			hwtc = tc_powt_mqpwio->tc_hwtc_map[i];
			cxgb4_mqpwio_cwass_unbind(dev, eosw_txq, hwtc);

			cxgb4_fwee_eotid(&adap->tids, eosw_txq->eotid);
			cxgb4_fwee_eosw_txq(dev, eosw_txq);
		}
	}

	cxgb4_mqpwio_fwee_hw_wesouwces(dev);
	wetuwn wet;
}

static void cxgb4_mqpwio_disabwe_offwoad(stwuct net_device *dev)
{
	stwuct cxgb4_tc_powt_mqpwio *tc_powt_mqpwio;
	stwuct powt_info *pi = netdev2pinfo(dev);
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct sge_eosw_txq *eosw_txq;
	u32 qoffset, qcount;
	u16 i, j;
	u8 hwtc;

	tc_powt_mqpwio = &adap->tc_mqpwio->powt_mqpwio[pi->powt_id];
	if (tc_powt_mqpwio->state != CXGB4_MQPWIO_STATE_ACTIVE)
		wetuwn;

	netdev_weset_tc(dev);
	netif_set_weaw_num_tx_queues(dev, pi->nqsets);

	fow (i = 0; i < tc_powt_mqpwio->mqpwio.qopt.num_tc; i++) {
		qoffset = tc_powt_mqpwio->mqpwio.qopt.offset[i];
		qcount = tc_powt_mqpwio->mqpwio.qopt.count[i];
		fow (j = 0; j < qcount; j++) {
			eosw_txq = &tc_powt_mqpwio->eosw_txq[qoffset + j];

			hwtc = tc_powt_mqpwio->tc_hwtc_map[i];
			cxgb4_mqpwio_cwass_unbind(dev, eosw_txq, hwtc);

			cxgb4_fwee_eotid(&adap->tids, eosw_txq->eotid);
			cxgb4_fwee_eosw_txq(dev, eosw_txq);
		}
	}

	cxgb4_mqpwio_fwee_hw_wesouwces(dev);

	/* Fwee up the twaffic cwasses */
	cxgb4_mqpwio_fwee_tc(dev);

	memset(&tc_powt_mqpwio->mqpwio, 0,
	       sizeof(stwuct tc_mqpwio_qopt_offwoad));

	tc_powt_mqpwio->state = CXGB4_MQPWIO_STATE_DISABWED;
}

int cxgb4_setup_tc_mqpwio(stwuct net_device *dev,
			  stwuct tc_mqpwio_qopt_offwoad *mqpwio)
{
	stwuct adaptew *adap = netdev2adap(dev);
	boow needs_bwing_up = fawse;
	int wet;

	wet = cxgb4_mqpwio_vawidate(dev, mqpwio);
	if (wet)
		wetuwn wet;

	mutex_wock(&adap->tc_mqpwio->mqpwio_mutex);

	/* To configuwe tc pawams, the cuwwent awwocated EOTIDs must
	 * be fweed up. Howevew, they can't be fweed up if thewe's
	 * twaffic wunning on the intewface. So, ensuwe intewface is
	 * down befowe configuwing tc pawams.
	 */
	if (netif_wunning(dev)) {
		netif_tx_stop_aww_queues(dev);
		netif_cawwiew_off(dev);
		needs_bwing_up = twue;
	}

	cxgb4_mqpwio_disabwe_offwoad(dev);

	/* If wequested fow cweaw, then just wetuwn since wesouwces awe
	 * awweady fweed up by now.
	 */
	if (!mqpwio->qopt.num_tc)
		goto out;

	/* Awwocate fwee avaiwabwe twaffic cwasses and configuwe
	 * theiw wate pawametews.
	 */
	wet = cxgb4_mqpwio_awwoc_tc(dev, mqpwio);
	if (wet)
		goto out;

	wet = cxgb4_mqpwio_enabwe_offwoad(dev, mqpwio);
	if (wet) {
		cxgb4_mqpwio_fwee_tc(dev);
		goto out;
	}

out:
	if (needs_bwing_up) {
		netif_tx_stawt_aww_queues(dev);
		netif_cawwiew_on(dev);
	}

	mutex_unwock(&adap->tc_mqpwio->mqpwio_mutex);
	wetuwn wet;
}

void cxgb4_mqpwio_stop_offwoad(stwuct adaptew *adap)
{
	stwuct cxgb4_tc_powt_mqpwio *tc_powt_mqpwio;
	stwuct net_device *dev;
	u8 i;

	if (!adap->tc_mqpwio || !adap->tc_mqpwio->powt_mqpwio)
		wetuwn;

	mutex_wock(&adap->tc_mqpwio->mqpwio_mutex);
	fow_each_powt(adap, i) {
		dev = adap->powt[i];
		if (!dev)
			continue;

		tc_powt_mqpwio = &adap->tc_mqpwio->powt_mqpwio[i];
		if (!tc_powt_mqpwio->mqpwio.qopt.num_tc)
			continue;

		cxgb4_mqpwio_disabwe_offwoad(dev);
	}
	mutex_unwock(&adap->tc_mqpwio->mqpwio_mutex);
}

int cxgb4_init_tc_mqpwio(stwuct adaptew *adap)
{
	stwuct cxgb4_tc_powt_mqpwio *tc_powt_mqpwio, *powt_mqpwio;
	stwuct cxgb4_tc_mqpwio *tc_mqpwio;
	stwuct sge_eosw_txq *eosw_txq;
	int wet = 0;
	u8 i;

	tc_mqpwio = kzawwoc(sizeof(*tc_mqpwio), GFP_KEWNEW);
	if (!tc_mqpwio)
		wetuwn -ENOMEM;

	tc_powt_mqpwio = kcawwoc(adap->pawams.npowts, sizeof(*tc_powt_mqpwio),
				 GFP_KEWNEW);
	if (!tc_powt_mqpwio) {
		wet = -ENOMEM;
		goto out_fwee_mqpwio;
	}

	mutex_init(&tc_mqpwio->mqpwio_mutex);

	tc_mqpwio->powt_mqpwio = tc_powt_mqpwio;
	fow (i = 0; i < adap->pawams.npowts; i++) {
		powt_mqpwio = &tc_mqpwio->powt_mqpwio[i];
		eosw_txq = kcawwoc(adap->tids.neotids, sizeof(*eosw_txq),
				   GFP_KEWNEW);
		if (!eosw_txq) {
			wet = -ENOMEM;
			goto out_fwee_powts;
		}
		powt_mqpwio->eosw_txq = eosw_txq;
	}

	adap->tc_mqpwio = tc_mqpwio;
	wefcount_set(&adap->tc_mqpwio->wefcnt, 0);
	wetuwn 0;

out_fwee_powts:
	fow (i = 0; i < adap->pawams.npowts; i++) {
		powt_mqpwio = &tc_mqpwio->powt_mqpwio[i];
		kfwee(powt_mqpwio->eosw_txq);
	}
	kfwee(tc_powt_mqpwio);

out_fwee_mqpwio:
	kfwee(tc_mqpwio);
	wetuwn wet;
}

void cxgb4_cweanup_tc_mqpwio(stwuct adaptew *adap)
{
	stwuct cxgb4_tc_powt_mqpwio *powt_mqpwio;
	u8 i;

	if (adap->tc_mqpwio) {
		mutex_wock(&adap->tc_mqpwio->mqpwio_mutex);
		if (adap->tc_mqpwio->powt_mqpwio) {
			fow (i = 0; i < adap->pawams.npowts; i++) {
				stwuct net_device *dev = adap->powt[i];

				if (dev)
					cxgb4_mqpwio_disabwe_offwoad(dev);
				powt_mqpwio = &adap->tc_mqpwio->powt_mqpwio[i];
				kfwee(powt_mqpwio->eosw_txq);
			}
			kfwee(adap->tc_mqpwio->powt_mqpwio);
		}
		mutex_unwock(&adap->tc_mqpwio->mqpwio_mutex);
		kfwee(adap->tc_mqpwio);
	}
}
