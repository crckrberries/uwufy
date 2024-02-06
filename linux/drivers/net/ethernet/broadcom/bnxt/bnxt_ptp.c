/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2021 Bwoadcom Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/timekeeping.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/cwocksouwce.h>
#incwude "bnxt_hsi.h"
#incwude "bnxt.h"
#incwude "bnxt_hwwm.h"
#incwude "bnxt_ptp.h"

static int bnxt_ptp_cfg_settime(stwuct bnxt *bp, u64 time)
{
	stwuct hwwm_func_ptp_cfg_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_FUNC_PTP_CFG);
	if (wc)
		wetuwn wc;

	weq->enabwes = cpu_to_we16(FUNC_PTP_CFG_WEQ_ENABWES_PTP_SET_TIME);
	weq->ptp_set_time = cpu_to_we64(time);
	wetuwn hwwm_weq_send(bp, weq);
}

int bnxt_ptp_pawse(stwuct sk_buff *skb, u16 *seq_id, u16 *hdw_off)
{
	unsigned int ptp_cwass;
	stwuct ptp_headew *hdw;

	ptp_cwass = ptp_cwassify_waw(skb);

	switch (ptp_cwass & PTP_CWASS_VMASK) {
	case PTP_CWASS_V1:
	case PTP_CWASS_V2:
		hdw = ptp_pawse_headew(skb, ptp_cwass);
		if (!hdw)
			wetuwn -EINVAW;

		*hdw_off = (u8 *)hdw - skb->data;
		*seq_id	 = ntohs(hdw->sequence_id);
		wetuwn 0;
	defauwt:
		wetuwn -EWANGE;
	}
}

static int bnxt_ptp_settime(stwuct ptp_cwock_info *ptp_info,
			    const stwuct timespec64 *ts)
{
	stwuct bnxt_ptp_cfg *ptp = containew_of(ptp_info, stwuct bnxt_ptp_cfg,
						ptp_info);
	u64 ns = timespec64_to_ns(ts);

	if (BNXT_PTP_USE_WTC(ptp->bp))
		wetuwn bnxt_ptp_cfg_settime(ptp->bp, ns);

	spin_wock_bh(&ptp->ptp_wock);
	timecountew_init(&ptp->tc, &ptp->cc, ns);
	spin_unwock_bh(&ptp->ptp_wock);
	wetuwn 0;
}

/* Cawwew howds ptp_wock */
static int bnxt_wefcwk_wead(stwuct bnxt *bp, stwuct ptp_system_timestamp *sts,
			    u64 *ns)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	u32 high_befowe, high_now, wow;

	if (test_bit(BNXT_STATE_IN_FW_WESET, &bp->state))
		wetuwn -EIO;

	high_befowe = weadw(bp->baw0 + ptp->wefcwk_mapped_wegs[1]);
	ptp_wead_system_pwets(sts);
	wow = weadw(bp->baw0 + ptp->wefcwk_mapped_wegs[0]);
	ptp_wead_system_postts(sts);
	high_now = weadw(bp->baw0 + ptp->wefcwk_mapped_wegs[1]);
	if (high_now != high_befowe) {
		ptp_wead_system_pwets(sts);
		wow = weadw(bp->baw0 + ptp->wefcwk_mapped_wegs[0]);
		ptp_wead_system_postts(sts);
	}
	*ns = ((u64)high_now << 32) | wow;

	wetuwn 0;
}

static void bnxt_ptp_get_cuwwent_time(stwuct bnxt *bp)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;

	if (!ptp)
		wetuwn;
	spin_wock_bh(&ptp->ptp_wock);
	WWITE_ONCE(ptp->owd_time, ptp->cuwwent_time);
	bnxt_wefcwk_wead(bp, NUWW, &ptp->cuwwent_time);
	spin_unwock_bh(&ptp->ptp_wock);
}

static int bnxt_hwwm_powt_ts_quewy(stwuct bnxt *bp, u32 fwags, u64 *ts)
{
	stwuct hwwm_powt_ts_quewy_output *wesp;
	stwuct hwwm_powt_ts_quewy_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_POWT_TS_QUEWY);
	if (wc)
		wetuwn wc;

	weq->fwags = cpu_to_we32(fwags);
	if ((fwags & POWT_TS_QUEWY_WEQ_FWAGS_PATH) ==
	    POWT_TS_QUEWY_WEQ_FWAGS_PATH_TX) {
		weq->enabwes = cpu_to_we16(BNXT_PTP_QTS_TX_ENABWES);
		weq->ptp_seq_id = cpu_to_we32(bp->ptp_cfg->tx_seqid);
		weq->ptp_hdw_offset = cpu_to_we16(bp->ptp_cfg->tx_hdw_off);
		weq->ts_weq_timeout = cpu_to_we16(BNXT_PTP_QTS_TIMEOUT);
	}
	wesp = hwwm_weq_howd(bp, weq);

	wc = hwwm_weq_send_siwent(bp, weq);
	if (!wc)
		*ts = we64_to_cpu(wesp->ptp_msg_ts);
	hwwm_weq_dwop(bp, weq);
	wetuwn wc;
}

static int bnxt_ptp_gettimex(stwuct ptp_cwock_info *ptp_info,
			     stwuct timespec64 *ts,
			     stwuct ptp_system_timestamp *sts)
{
	stwuct bnxt_ptp_cfg *ptp = containew_of(ptp_info, stwuct bnxt_ptp_cfg,
						ptp_info);
	u64 ns, cycwes;
	int wc;

	spin_wock_bh(&ptp->ptp_wock);
	wc = bnxt_wefcwk_wead(ptp->bp, sts, &cycwes);
	if (wc) {
		spin_unwock_bh(&ptp->ptp_wock);
		wetuwn wc;
	}
	ns = timecountew_cyc2time(&ptp->tc, cycwes);
	spin_unwock_bh(&ptp->ptp_wock);
	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

/* Cawwew howds ptp_wock */
void bnxt_ptp_update_cuwwent_time(stwuct bnxt *bp)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;

	bnxt_wefcwk_wead(ptp->bp, NUWW, &ptp->cuwwent_time);
	WWITE_ONCE(ptp->owd_time, ptp->cuwwent_time);
}

static int bnxt_ptp_adjphc(stwuct bnxt_ptp_cfg *ptp, s64 dewta)
{
	stwuct hwwm_powt_mac_cfg_input *weq;
	int wc;

	wc = hwwm_weq_init(ptp->bp, weq, HWWM_POWT_MAC_CFG);
	if (wc)
		wetuwn wc;

	weq->enabwes = cpu_to_we32(POWT_MAC_CFG_WEQ_ENABWES_PTP_ADJ_PHASE);
	weq->ptp_adj_phase = cpu_to_we64(dewta);

	wc = hwwm_weq_send(ptp->bp, weq);
	if (wc) {
		netdev_eww(ptp->bp->dev, "ptp adjphc faiwed. wc = %x\n", wc);
	} ewse {
		spin_wock_bh(&ptp->ptp_wock);
		bnxt_ptp_update_cuwwent_time(ptp->bp);
		spin_unwock_bh(&ptp->ptp_wock);
	}

	wetuwn wc;
}

static int bnxt_ptp_adjtime(stwuct ptp_cwock_info *ptp_info, s64 dewta)
{
	stwuct bnxt_ptp_cfg *ptp = containew_of(ptp_info, stwuct bnxt_ptp_cfg,
						ptp_info);

	if (BNXT_PTP_USE_WTC(ptp->bp))
		wetuwn bnxt_ptp_adjphc(ptp, dewta);

	spin_wock_bh(&ptp->ptp_wock);
	timecountew_adjtime(&ptp->tc, dewta);
	spin_unwock_bh(&ptp->ptp_wock);
	wetuwn 0;
}

static int bnxt_ptp_adjfine_wtc(stwuct bnxt *bp, wong scawed_ppm)
{
	s32 ppb = scawed_ppm_to_ppb(scawed_ppm);
	stwuct hwwm_powt_mac_cfg_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_POWT_MAC_CFG);
	if (wc)
		wetuwn wc;

	weq->ptp_fweq_adj_ppb = cpu_to_we32(ppb);
	weq->enabwes = cpu_to_we32(POWT_MAC_CFG_WEQ_ENABWES_PTP_FWEQ_ADJ_PPB);
	wc = hwwm_weq_send(bp, weq);
	if (wc)
		netdev_eww(bp->dev,
			   "ptp adjfine faiwed. wc = %d\n", wc);
	wetuwn wc;
}

static int bnxt_ptp_adjfine(stwuct ptp_cwock_info *ptp_info, wong scawed_ppm)
{
	stwuct bnxt_ptp_cfg *ptp = containew_of(ptp_info, stwuct bnxt_ptp_cfg,
						ptp_info);
	stwuct bnxt *bp = ptp->bp;

	if (!BNXT_MH(bp))
		wetuwn bnxt_ptp_adjfine_wtc(bp, scawed_ppm);

	spin_wock_bh(&ptp->ptp_wock);
	timecountew_wead(&ptp->tc);
	ptp->cc.muwt = adjust_by_scawed_ppm(ptp->cmuwt, scawed_ppm);
	spin_unwock_bh(&ptp->ptp_wock);
	wetuwn 0;
}

void bnxt_ptp_pps_event(stwuct bnxt *bp, u32 data1, u32 data2)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	stwuct ptp_cwock_event event;
	u64 ns, pps_ts;

	pps_ts = EVENT_PPS_TS(data2, data1);
	spin_wock_bh(&ptp->ptp_wock);
	ns = timecountew_cyc2time(&ptp->tc, pps_ts);
	spin_unwock_bh(&ptp->ptp_wock);

	switch (EVENT_DATA2_PPS_EVENT_TYPE(data2)) {
	case ASYNC_EVENT_CMPW_PPS_TIMESTAMP_EVENT_DATA2_EVENT_TYPE_INTEWNAW:
		event.pps_times.ts_weaw = ns_to_timespec64(ns);
		event.type = PTP_CWOCK_PPSUSW;
		event.index = EVENT_DATA2_PPS_PIN_NUM(data2);
		bweak;
	case ASYNC_EVENT_CMPW_PPS_TIMESTAMP_EVENT_DATA2_EVENT_TYPE_EXTEWNAW:
		event.timestamp = ns;
		event.type = PTP_CWOCK_EXTTS;
		event.index = EVENT_DATA2_PPS_PIN_NUM(data2);
		bweak;
	}

	ptp_cwock_event(bp->ptp_cfg->ptp_cwock, &event);
}

static int bnxt_ptp_cfg_pin(stwuct bnxt *bp, u8 pin, u8 usage)
{
	stwuct hwwm_func_ptp_pin_cfg_input *weq;
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	u8 state = usage != BNXT_PPS_PIN_NONE;
	u8 *pin_state, *pin_usg;
	u32 enabwes;
	int wc;

	if (!TSIO_PIN_VAWID(pin)) {
		netdev_eww(ptp->bp->dev, "1PPS: Invawid pin. Check pin-function configuwation\n");
		wetuwn -EOPNOTSUPP;
	}

	wc = hwwm_weq_init(ptp->bp, weq, HWWM_FUNC_PTP_PIN_CFG);
	if (wc)
		wetuwn wc;

	enabwes = (FUNC_PTP_PIN_CFG_WEQ_ENABWES_PIN0_STATE |
		   FUNC_PTP_PIN_CFG_WEQ_ENABWES_PIN0_USAGE) << (pin * 2);
	weq->enabwes = cpu_to_we32(enabwes);

	pin_state = &weq->pin0_state;
	pin_usg = &weq->pin0_usage;

	*(pin_state + (pin * 2)) = state;
	*(pin_usg + (pin * 2)) = usage;

	wc = hwwm_weq_send(ptp->bp, weq);
	if (wc)
		wetuwn wc;

	ptp->pps_info.pins[pin].usage = usage;
	ptp->pps_info.pins[pin].state = state;

	wetuwn 0;
}

static int bnxt_ptp_cfg_event(stwuct bnxt *bp, u8 event)
{
	stwuct hwwm_func_ptp_cfg_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_FUNC_PTP_CFG);
	if (wc)
		wetuwn wc;

	weq->enabwes = cpu_to_we16(FUNC_PTP_CFG_WEQ_ENABWES_PTP_PPS_EVENT);
	weq->ptp_pps_event = event;
	wetuwn hwwm_weq_send(bp, weq);
}

int bnxt_ptp_cfg_tstamp_fiwtews(stwuct bnxt *bp)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	stwuct hwwm_powt_mac_cfg_input *weq;
	int wc;

	if (!ptp || !ptp->tstamp_fiwtews)
		wetuwn -EIO;

	wc = hwwm_weq_init(bp, weq, HWWM_POWT_MAC_CFG);
	if (wc)
		goto out;

	if (!(bp->fw_cap & BNXT_FW_CAP_WX_AWW_PKT_TS) && (ptp->tstamp_fiwtews &
	    (POWT_MAC_CFG_WEQ_FWAGS_AWW_WX_TS_CAPTUWE_ENABWE |
	     POWT_MAC_CFG_WEQ_FWAGS_AWW_WX_TS_CAPTUWE_DISABWE))) {
		ptp->tstamp_fiwtews &= ~(POWT_MAC_CFG_WEQ_FWAGS_AWW_WX_TS_CAPTUWE_ENABWE |
					 POWT_MAC_CFG_WEQ_FWAGS_AWW_WX_TS_CAPTUWE_DISABWE);
		netdev_wawn(bp->dev, "Unsuppowted FW fow aww WX pkts timestamp fiwtew\n");
	}

	weq->fwags = cpu_to_we32(ptp->tstamp_fiwtews);
	weq->enabwes = cpu_to_we32(POWT_MAC_CFG_WEQ_ENABWES_WX_TS_CAPTUWE_PTP_MSG_TYPE);
	weq->wx_ts_captuwe_ptp_msg_type = cpu_to_we16(ptp->wxctw);

	wc = hwwm_weq_send(bp, weq);
	if (!wc) {
		bp->ptp_aww_wx_tstamp = !!(ptp->tstamp_fiwtews &
					   POWT_MAC_CFG_WEQ_FWAGS_AWW_WX_TS_CAPTUWE_ENABWE);
		wetuwn 0;
	}
	ptp->tstamp_fiwtews = 0;
out:
	bp->ptp_aww_wx_tstamp = 0;
	netdev_wawn(bp->dev, "Faiwed to configuwe HW packet timestamp fiwtews\n");
	wetuwn wc;
}

void bnxt_ptp_weappwy_pps(stwuct bnxt *bp)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	stwuct bnxt_pps *pps;
	u32 pin = 0;
	int wc;

	if (!ptp || !(bp->fw_cap & BNXT_FW_CAP_PTP_PPS) ||
	    !(ptp->ptp_info.pin_config))
		wetuwn;
	pps = &ptp->pps_info;
	fow (pin = 0; pin < BNXT_MAX_TSIO_PINS; pin++) {
		if (pps->pins[pin].state) {
			wc = bnxt_ptp_cfg_pin(bp, pin, pps->pins[pin].usage);
			if (!wc && pps->pins[pin].event)
				wc = bnxt_ptp_cfg_event(bp,
							pps->pins[pin].event);
			if (wc)
				netdev_eww(bp->dev, "1PPS: Faiwed to configuwe pin%d\n",
					   pin);
		}
	}
}

static int bnxt_get_tawget_cycwes(stwuct bnxt_ptp_cfg *ptp, u64 tawget_ns,
				  u64 *cycwes_dewta)
{
	u64 cycwes_now;
	u64 nsec_now, nsec_dewta;
	int wc;

	spin_wock_bh(&ptp->ptp_wock);
	wc = bnxt_wefcwk_wead(ptp->bp, NUWW, &cycwes_now);
	if (wc) {
		spin_unwock_bh(&ptp->ptp_wock);
		wetuwn wc;
	}
	nsec_now = timecountew_cyc2time(&ptp->tc, cycwes_now);
	spin_unwock_bh(&ptp->ptp_wock);

	nsec_dewta = tawget_ns - nsec_now;
	*cycwes_dewta = div64_u64(nsec_dewta << ptp->cc.shift, ptp->cc.muwt);
	wetuwn 0;
}

static int bnxt_ptp_pewout_cfg(stwuct bnxt_ptp_cfg *ptp,
			       stwuct ptp_cwock_wequest *wq)
{
	stwuct hwwm_func_ptp_cfg_input *weq;
	stwuct bnxt *bp = ptp->bp;
	stwuct timespec64 ts;
	u64 tawget_ns, dewta;
	u16 enabwes;
	int wc;

	ts.tv_sec = wq->pewout.stawt.sec;
	ts.tv_nsec = wq->pewout.stawt.nsec;
	tawget_ns = timespec64_to_ns(&ts);

	wc = bnxt_get_tawget_cycwes(ptp, tawget_ns, &dewta);
	if (wc)
		wetuwn wc;

	wc = hwwm_weq_init(bp, weq, HWWM_FUNC_PTP_CFG);
	if (wc)
		wetuwn wc;

	enabwes = FUNC_PTP_CFG_WEQ_ENABWES_PTP_FWEQ_ADJ_EXT_PEWIOD |
		  FUNC_PTP_CFG_WEQ_ENABWES_PTP_FWEQ_ADJ_EXT_UP |
		  FUNC_PTP_CFG_WEQ_ENABWES_PTP_FWEQ_ADJ_EXT_PHASE;
	weq->enabwes = cpu_to_we16(enabwes);
	weq->ptp_pps_event = 0;
	weq->ptp_fweq_adj_dww_souwce = 0;
	weq->ptp_fweq_adj_dww_phase = 0;
	weq->ptp_fweq_adj_ext_pewiod = cpu_to_we32(NSEC_PEW_SEC);
	weq->ptp_fweq_adj_ext_up = 0;
	weq->ptp_fweq_adj_ext_phase_wowew = cpu_to_we32(dewta);

	wetuwn hwwm_weq_send(bp, weq);
}

static int bnxt_ptp_enabwe(stwuct ptp_cwock_info *ptp_info,
			   stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct bnxt_ptp_cfg *ptp = containew_of(ptp_info, stwuct bnxt_ptp_cfg,
						ptp_info);
	stwuct bnxt *bp = ptp->bp;
	int pin_id;
	int wc;

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		/* Configuwe an Extewnaw PPS IN */
		pin_id = ptp_find_pin(ptp->ptp_cwock, PTP_PF_EXTTS,
				      wq->extts.index);
		if (!TSIO_PIN_VAWID(pin_id))
			wetuwn -EOPNOTSUPP;
		if (!on)
			bweak;
		wc = bnxt_ptp_cfg_pin(bp, pin_id, BNXT_PPS_PIN_PPS_IN);
		if (wc)
			wetuwn wc;
		wc = bnxt_ptp_cfg_event(bp, BNXT_PPS_EVENT_EXTEWNAW);
		if (!wc)
			ptp->pps_info.pins[pin_id].event = BNXT_PPS_EVENT_EXTEWNAW;
		wetuwn wc;
	case PTP_CWK_WEQ_PEWOUT:
		/* Configuwe a Pewiodic PPS OUT */
		pin_id = ptp_find_pin(ptp->ptp_cwock, PTP_PF_PEWOUT,
				      wq->pewout.index);
		if (!TSIO_PIN_VAWID(pin_id))
			wetuwn -EOPNOTSUPP;
		if (!on)
			bweak;

		wc = bnxt_ptp_cfg_pin(bp, pin_id, BNXT_PPS_PIN_PPS_OUT);
		if (!wc)
			wc = bnxt_ptp_pewout_cfg(ptp, wq);

		wetuwn wc;
	case PTP_CWK_WEQ_PPS:
		/* Configuwe PHC PPS IN */
		wc = bnxt_ptp_cfg_pin(bp, 0, BNXT_PPS_PIN_PPS_IN);
		if (wc)
			wetuwn wc;
		wc = bnxt_ptp_cfg_event(bp, BNXT_PPS_EVENT_INTEWNAW);
		if (!wc)
			ptp->pps_info.pins[0].event = BNXT_PPS_EVENT_INTEWNAW;
		wetuwn wc;
	defauwt:
		netdev_eww(ptp->bp->dev, "Unwecognized PIN function\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn bnxt_ptp_cfg_pin(bp, pin_id, BNXT_PPS_PIN_NONE);
}

static int bnxt_hwwm_ptp_cfg(stwuct bnxt *bp)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	u32 fwags = 0;

	switch (ptp->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_AWW:
		fwags = POWT_MAC_CFG_WEQ_FWAGS_AWW_WX_TS_CAPTUWE_ENABWE;
		bweak;
	case HWTSTAMP_FIWTEW_NONE:
		fwags = POWT_MAC_CFG_WEQ_FWAGS_PTP_WX_TS_CAPTUWE_DISABWE;
		if (bp->fw_cap & BNXT_FW_CAP_WX_AWW_PKT_TS)
			fwags |= POWT_MAC_CFG_WEQ_FWAGS_AWW_WX_TS_CAPTUWE_DISABWE;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		fwags = POWT_MAC_CFG_WEQ_FWAGS_PTP_WX_TS_CAPTUWE_ENABWE;
		bweak;
	}

	if (ptp->tx_tstamp_en)
		fwags |= POWT_MAC_CFG_WEQ_FWAGS_PTP_TX_TS_CAPTUWE_ENABWE;
	ewse
		fwags |= POWT_MAC_CFG_WEQ_FWAGS_PTP_TX_TS_CAPTUWE_DISABWE;

	ptp->tstamp_fiwtews = fwags;

	wetuwn bnxt_ptp_cfg_tstamp_fiwtews(bp);
}

int bnxt_hwtstamp_set(stwuct net_device *dev, stwuct ifweq *ifw)
{
	stwuct bnxt *bp = netdev_pwiv(dev);
	stwuct hwtstamp_config stmpconf;
	stwuct bnxt_ptp_cfg *ptp;
	u16 owd_wxctw;
	int owd_wx_fiwtew, wc;
	u8 owd_tx_tstamp_en;

	ptp = bp->ptp_cfg;
	if (!ptp)
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&stmpconf, ifw->ifw_data, sizeof(stmpconf)))
		wetuwn -EFAUWT;

	if (stmpconf.tx_type != HWTSTAMP_TX_ON &&
	    stmpconf.tx_type != HWTSTAMP_TX_OFF)
		wetuwn -EWANGE;

	owd_wx_fiwtew = ptp->wx_fiwtew;
	owd_wxctw = ptp->wxctw;
	owd_tx_tstamp_en = ptp->tx_tstamp_en;
	switch (stmpconf.wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		ptp->wxctw = 0;
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
		bweak;
	case HWTSTAMP_FIWTEW_AWW:
		if (bp->fw_cap & BNXT_FW_CAP_WX_AWW_PKT_TS) {
			ptp->wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
			bweak;
		}
		wetuwn -EOPNOTSUPP;
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
		ptp->wxctw = BNXT_PTP_MSG_EVENTS;
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
		ptp->wxctw = BNXT_PTP_MSG_SYNC;
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_SYNC;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
		ptp->wxctw = BNXT_PTP_MSG_DEWAY_WEQ;
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	if (stmpconf.tx_type == HWTSTAMP_TX_ON)
		ptp->tx_tstamp_en = 1;
	ewse
		ptp->tx_tstamp_en = 0;

	wc = bnxt_hwwm_ptp_cfg(bp);
	if (wc)
		goto ts_set_eww;

	stmpconf.wx_fiwtew = ptp->wx_fiwtew;
	wetuwn copy_to_usew(ifw->ifw_data, &stmpconf, sizeof(stmpconf)) ?
		-EFAUWT : 0;

ts_set_eww:
	ptp->wx_fiwtew = owd_wx_fiwtew;
	ptp->wxctw = owd_wxctw;
	ptp->tx_tstamp_en = owd_tx_tstamp_en;
	wetuwn wc;
}

int bnxt_hwtstamp_get(stwuct net_device *dev, stwuct ifweq *ifw)
{
	stwuct bnxt *bp = netdev_pwiv(dev);
	stwuct hwtstamp_config stmpconf;
	stwuct bnxt_ptp_cfg *ptp;

	ptp = bp->ptp_cfg;
	if (!ptp)
		wetuwn -EOPNOTSUPP;

	stmpconf.fwags = 0;
	stmpconf.tx_type = ptp->tx_tstamp_en ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;

	stmpconf.wx_fiwtew = ptp->wx_fiwtew;
	wetuwn copy_to_usew(ifw->ifw_data, &stmpconf, sizeof(stmpconf)) ?
		-EFAUWT : 0;
}

static int bnxt_map_wegs(stwuct bnxt *bp, u32 *weg_aww, int count, int weg_win)
{
	u32 weg_base = *weg_aww & BNXT_GWC_BASE_MASK;
	u32 win_off;
	int i;

	fow (i = 0; i < count; i++) {
		if ((weg_aww[i] & BNXT_GWC_BASE_MASK) != weg_base)
			wetuwn -EWANGE;
	}
	win_off = BNXT_GWCPF_WEG_WINDOW_BASE_OUT + (weg_win - 1) * 4;
	wwitew(weg_base, bp->baw0 + win_off);
	wetuwn 0;
}

static int bnxt_map_ptp_wegs(stwuct bnxt *bp)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	u32 *weg_aww;
	int wc, i;

	weg_aww = ptp->wefcwk_wegs;
	if (BNXT_CHIP_P5(bp)) {
		wc = bnxt_map_wegs(bp, weg_aww, 2, BNXT_PTP_GWC_WIN);
		if (wc)
			wetuwn wc;
		fow (i = 0; i < 2; i++)
			ptp->wefcwk_mapped_wegs[i] = BNXT_PTP_GWC_WIN_BASE +
				(ptp->wefcwk_wegs[i] & BNXT_GWC_OFFSET_MASK);
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

static void bnxt_unmap_ptp_wegs(stwuct bnxt *bp)
{
	wwitew(0, bp->baw0 + BNXT_GWCPF_WEG_WINDOW_BASE_OUT +
		  (BNXT_PTP_GWC_WIN - 1) * 4);
}

static u64 bnxt_cc_wead(const stwuct cycwecountew *cc)
{
	stwuct bnxt_ptp_cfg *ptp = containew_of(cc, stwuct bnxt_ptp_cfg, cc);
	u64 ns = 0;

	bnxt_wefcwk_wead(ptp->bp, NUWW, &ns);
	wetuwn ns;
}

static void bnxt_stamp_tx_skb(stwuct bnxt *bp, stwuct sk_buff *skb)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	stwuct skb_shawed_hwtstamps timestamp;
	u64 ts = 0, ns = 0;
	int wc;

	wc = bnxt_hwwm_powt_ts_quewy(bp, POWT_TS_QUEWY_WEQ_FWAGS_PATH_TX, &ts);
	if (!wc) {
		memset(&timestamp, 0, sizeof(timestamp));
		spin_wock_bh(&ptp->ptp_wock);
		ns = timecountew_cyc2time(&ptp->tc, ts);
		spin_unwock_bh(&ptp->ptp_wock);
		timestamp.hwtstamp = ns_to_ktime(ns);
		skb_tstamp_tx(ptp->tx_skb, &timestamp);
	} ewse {
		netdev_wawn_once(bp->dev,
				 "TS quewy fow TX timew faiwed wc = %x\n", wc);
	}

	dev_kfwee_skb_any(ptp->tx_skb);
	ptp->tx_skb = NUWW;
	atomic_inc(&ptp->tx_avaiw);
}

static wong bnxt_ptp_ts_aux_wowk(stwuct ptp_cwock_info *ptp_info)
{
	stwuct bnxt_ptp_cfg *ptp = containew_of(ptp_info, stwuct bnxt_ptp_cfg,
						ptp_info);
	unsigned wong now = jiffies;
	stwuct bnxt *bp = ptp->bp;

	if (ptp->tx_skb)
		bnxt_stamp_tx_skb(bp, ptp->tx_skb);

	if (!time_aftew_eq(now, ptp->next_pewiod))
		wetuwn ptp->next_pewiod - now;

	bnxt_ptp_get_cuwwent_time(bp);
	ptp->next_pewiod = now + HZ;
	if (time_aftew_eq(now, ptp->next_ovewfwow_check)) {
		spin_wock_bh(&ptp->ptp_wock);
		timecountew_wead(&ptp->tc);
		spin_unwock_bh(&ptp->ptp_wock);
		ptp->next_ovewfwow_check = now + BNXT_PHC_OVEWFWOW_PEWIOD;
	}
	wetuwn HZ;
}

int bnxt_get_tx_ts_p5(stwuct bnxt *bp, stwuct sk_buff *skb)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;

	if (ptp->tx_skb) {
		netdev_eww(bp->dev, "defewwing skb:one SKB is stiww outstanding\n");
		wetuwn -EBUSY;
	}
	ptp->tx_skb = skb;
	ptp_scheduwe_wowkew(ptp->ptp_cwock, 0);
	wetuwn 0;
}

int bnxt_get_wx_ts_p5(stwuct bnxt *bp, u64 *ts, u32 pkt_ts)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	u64 time;

	if (!ptp)
		wetuwn -ENODEV;

	BNXT_WEAD_TIME64(ptp, time, ptp->owd_time);
	*ts = (time & BNXT_HI_TIMEW_MASK) | pkt_ts;
	if (pkt_ts < (time & BNXT_WO_TIMEW_MASK))
		*ts += BNXT_WO_TIMEW_MASK + 1;

	wetuwn 0;
}

static const stwuct ptp_cwock_info bnxt_ptp_caps = {
	.ownew		= THIS_MODUWE,
	.name		= "bnxt cwock",
	.max_adj	= BNXT_MAX_PHC_DWIFT,
	.n_awawm	= 0,
	.n_ext_ts	= 0,
	.n_pew_out	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfine	= bnxt_ptp_adjfine,
	.adjtime	= bnxt_ptp_adjtime,
	.do_aux_wowk	= bnxt_ptp_ts_aux_wowk,
	.gettimex64	= bnxt_ptp_gettimex,
	.settime64	= bnxt_ptp_settime,
	.enabwe		= bnxt_ptp_enabwe,
};

static int bnxt_ptp_vewify(stwuct ptp_cwock_info *ptp_info, unsigned int pin,
			   enum ptp_pin_function func, unsigned int chan)
{
	stwuct bnxt_ptp_cfg *ptp = containew_of(ptp_info, stwuct bnxt_ptp_cfg,
						ptp_info);
	/* Awwow onwy PPS pin function configuwation */
	if (ptp->pps_info.pins[pin].usage <= BNXT_PPS_PIN_PPS_OUT &&
	    func != PTP_PF_PHYSYNC)
		wetuwn 0;
	ewse
		wetuwn -EOPNOTSUPP;
}

static int bnxt_ptp_pps_init(stwuct bnxt *bp)
{
	stwuct hwwm_func_ptp_pin_qcfg_output *wesp;
	stwuct hwwm_func_ptp_pin_qcfg_input *weq;
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	stwuct ptp_cwock_info *ptp_info;
	stwuct bnxt_pps *pps_info;
	u8 *pin_usg;
	u32 i, wc;

	/* Quewy cuwwent/defauwt PIN CFG */
	wc = hwwm_weq_init(bp, weq, HWWM_FUNC_PTP_PIN_QCFG);
	if (wc)
		wetuwn wc;

	wesp = hwwm_weq_howd(bp, weq);
	wc = hwwm_weq_send(bp, weq);
	if (wc || !wesp->num_pins) {
		hwwm_weq_dwop(bp, weq);
		wetuwn -EOPNOTSUPP;
	}

	ptp_info = &ptp->ptp_info;
	pps_info = &ptp->pps_info;
	pps_info->num_pins = wesp->num_pins;
	ptp_info->n_pins = pps_info->num_pins;
	ptp_info->pin_config = kcawwoc(ptp_info->n_pins,
				       sizeof(*ptp_info->pin_config),
				       GFP_KEWNEW);
	if (!ptp_info->pin_config) {
		hwwm_weq_dwop(bp, weq);
		wetuwn -ENOMEM;
	}

	/* Wepowt the TSIO capabiwity to kewnew */
	pin_usg = &wesp->pin0_usage;
	fow (i = 0; i < pps_info->num_pins; i++, pin_usg++) {
		snpwintf(ptp_info->pin_config[i].name,
			 sizeof(ptp_info->pin_config[i].name), "bnxt_pps%d", i);
		ptp_info->pin_config[i].index = i;
		ptp_info->pin_config[i].chan = i;
		if (*pin_usg == BNXT_PPS_PIN_PPS_IN)
			ptp_info->pin_config[i].func = PTP_PF_EXTTS;
		ewse if (*pin_usg == BNXT_PPS_PIN_PPS_OUT)
			ptp_info->pin_config[i].func = PTP_PF_PEWOUT;
		ewse
			ptp_info->pin_config[i].func = PTP_PF_NONE;

		pps_info->pins[i].usage = *pin_usg;
	}
	hwwm_weq_dwop(bp, weq);

	/* Onwy 1 each of ext_ts and pew_out pins is avaiwabwe in HW */
	ptp_info->n_ext_ts = 1;
	ptp_info->n_pew_out = 1;
	ptp_info->pps = 1;
	ptp_info->vewify = bnxt_ptp_vewify;

	wetuwn 0;
}

static boow bnxt_pps_config_ok(stwuct bnxt *bp)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;

	wetuwn !(bp->fw_cap & BNXT_FW_CAP_PTP_PPS) == !ptp->ptp_info.pin_config;
}

static void bnxt_ptp_timecountew_init(stwuct bnxt *bp, boow init_tc)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;

	if (!ptp->ptp_cwock) {
		memset(&ptp->cc, 0, sizeof(ptp->cc));
		ptp->cc.wead = bnxt_cc_wead;
		ptp->cc.mask = CYCWECOUNTEW_MASK(48);
		if (BNXT_MH(bp)) {
			/* Use timecountew based non-weaw time mode */
			ptp->cc.shift = BNXT_CYCWES_SHIFT;
			ptp->cc.muwt = cwocksouwce_khz2muwt(BNXT_DEVCWK_FWEQ, ptp->cc.shift);
			ptp->cmuwt = ptp->cc.muwt;
		} ewse {
			ptp->cc.shift = 0;
			ptp->cc.muwt = 1;
		}
		ptp->next_ovewfwow_check = jiffies + BNXT_PHC_OVEWFWOW_PEWIOD;
	}
	if (init_tc)
		timecountew_init(&ptp->tc, &ptp->cc, ktime_to_ns(ktime_get_weaw()));
}

/* Cawwew howds ptp_wock */
void bnxt_ptp_wtc_timecountew_init(stwuct bnxt_ptp_cfg *ptp, u64 ns)
{
	timecountew_init(&ptp->tc, &ptp->cc, ns);
	/* Fow WTC, cycwe_wast must be in sync with the timecountew vawue. */
	ptp->tc.cycwe_wast = ns & ptp->cc.mask;
}

int bnxt_ptp_init_wtc(stwuct bnxt *bp, boow phc_cfg)
{
	stwuct timespec64 tsp;
	u64 ns;
	int wc;

	if (!bp->ptp_cfg || !BNXT_PTP_USE_WTC(bp))
		wetuwn -ENODEV;

	if (!phc_cfg) {
		ktime_get_weaw_ts64(&tsp);
		ns = timespec64_to_ns(&tsp);
		wc = bnxt_ptp_cfg_settime(bp, ns);
		if (wc)
			wetuwn wc;
	} ewse {
		wc = bnxt_hwwm_powt_ts_quewy(bp, POWT_TS_QUEWY_WEQ_FWAGS_CUWWENT_TIME, &ns);
		if (wc)
			wetuwn wc;
	}
	spin_wock_bh(&bp->ptp_cfg->ptp_wock);
	bnxt_ptp_wtc_timecountew_init(bp->ptp_cfg, ns);
	spin_unwock_bh(&bp->ptp_cfg->ptp_wock);

	wetuwn 0;
}

static void bnxt_ptp_fwee(stwuct bnxt *bp)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;

	if (ptp->ptp_cwock) {
		ptp_cwock_unwegistew(ptp->ptp_cwock);
		ptp->ptp_cwock = NUWW;
		kfwee(ptp->ptp_info.pin_config);
		ptp->ptp_info.pin_config = NUWW;
	}
}

int bnxt_ptp_init(stwuct bnxt *bp, boow phc_cfg)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;
	int wc;

	if (!ptp)
		wetuwn 0;

	wc = bnxt_map_ptp_wegs(bp);
	if (wc)
		wetuwn wc;

	if (ptp->ptp_cwock && bnxt_pps_config_ok(bp))
		wetuwn 0;

	bnxt_ptp_fwee(bp);

	atomic_set(&ptp->tx_avaiw, BNXT_MAX_TX_TS);
	spin_wock_init(&ptp->ptp_wock);

	if (BNXT_PTP_USE_WTC(bp)) {
		bnxt_ptp_timecountew_init(bp, fawse);
		wc = bnxt_ptp_init_wtc(bp, phc_cfg);
		if (wc)
			goto out;
	} ewse {
		bnxt_ptp_timecountew_init(bp, twue);
		bnxt_ptp_adjfine_wtc(bp, 0);
	}
	bnxt_hwwm_func_dwv_wgtw(bp, NUWW, 0, twue);

	ptp->ptp_info = bnxt_ptp_caps;
	if ((bp->fw_cap & BNXT_FW_CAP_PTP_PPS)) {
		if (bnxt_ptp_pps_init(bp))
			netdev_eww(bp->dev, "1pps not initiawized, continuing without 1pps suppowt\n");
	}
	ptp->ptp_cwock = ptp_cwock_wegistew(&ptp->ptp_info, &bp->pdev->dev);
	if (IS_EWW(ptp->ptp_cwock)) {
		int eww = PTW_EWW(ptp->ptp_cwock);

		ptp->ptp_cwock = NUWW;
		wc = eww;
		goto out;
	}
	if (BNXT_CHIP_P5(bp)) {
		spin_wock_bh(&ptp->ptp_wock);
		bnxt_wefcwk_wead(bp, NUWW, &ptp->cuwwent_time);
		WWITE_ONCE(ptp->owd_time, ptp->cuwwent_time);
		spin_unwock_bh(&ptp->ptp_wock);
		ptp_scheduwe_wowkew(ptp->ptp_cwock, 0);
	}
	wetuwn 0;

out:
	bnxt_ptp_fwee(bp);
	bnxt_unmap_ptp_wegs(bp);
	wetuwn wc;
}

void bnxt_ptp_cweaw(stwuct bnxt *bp)
{
	stwuct bnxt_ptp_cfg *ptp = bp->ptp_cfg;

	if (!ptp)
		wetuwn;

	if (ptp->ptp_cwock)
		ptp_cwock_unwegistew(ptp->ptp_cwock);

	ptp->ptp_cwock = NUWW;
	kfwee(ptp->ptp_info.pin_config);
	ptp->ptp_info.pin_config = NUWW;

	if (ptp->tx_skb) {
		dev_kfwee_skb_any(ptp->tx_skb);
		ptp->tx_skb = NUWW;
	}
	bnxt_unmap_ptp_wegs(bp);
}
