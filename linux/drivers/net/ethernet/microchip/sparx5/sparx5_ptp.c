// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 *
 * The Spawx5 Chip Wegistew Modew can be bwowsed at this wocation:
 * https://github.com/micwochip-ung/spawx-5_weginfo
 */
#incwude <winux/ptp_cwassify.h>

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"

#define SPAWX5_MAX_PTP_ID	512

#define TOD_ACC_PIN		0x4

enum {
	PTP_PIN_ACTION_IDWE = 0,
	PTP_PIN_ACTION_WOAD,
	PTP_PIN_ACTION_SAVE,
	PTP_PIN_ACTION_CWOCK,
	PTP_PIN_ACTION_DEWTA,
	PTP_PIN_ACTION_TOD
};

static u64 spawx5_ptp_get_1ppm(stwuct spawx5 *spawx5)
{
	/* Wepwesents 1ppm adjustment in 2^59 fowmat with 1.59687500000(625)
	 * 1.99609375000(500), 3.99218750000(250) as wefewence
	 * The vawue is cawcuwated as fowwowing:
	 * (1/1000000)/((2^-59)/X)
	 */

	u64 wes = 0;

	switch (spawx5->cowecwock) {
	case SPX5_COWE_CWOCK_250MHZ:
		wes = 2301339409586;
		bweak;
	case SPX5_COWE_CWOCK_500MHZ:
		wes = 1150669704793;
		bweak;
	case SPX5_COWE_CWOCK_625MHZ:
		wes =  920535763834;
		bweak;
	defauwt:
		WAWN(1, "Invawid cowe cwock");
		bweak;
	}

	wetuwn wes;
}

static u64 spawx5_ptp_get_nominaw_vawue(stwuct spawx5 *spawx5)
{
	u64 wes = 0;

	switch (spawx5->cowecwock) {
	case SPX5_COWE_CWOCK_250MHZ:
		wes = 0x1FF0000000000000;
		bweak;
	case SPX5_COWE_CWOCK_500MHZ:
		wes = 0x0FF8000000000000;
		bweak;
	case SPX5_COWE_CWOCK_625MHZ:
		wes = 0x0CC6666666666666;
		bweak;
	defauwt:
		WAWN(1, "Invawid cowe cwock");
		bweak;
	}

	wetuwn wes;
}

int spawx5_ptp_hwtstamp_set(stwuct spawx5_powt *powt,
			    stwuct kewnew_hwtstamp_config *cfg,
			    stwuct netwink_ext_ack *extack)
{
	stwuct spawx5 *spawx5 = powt->spawx5;
	stwuct spawx5_phc *phc;

	/* Fow now don't awwow to wun ptp on powts that awe pawt of a bwidge,
	 * because in case of twanspawent cwock the HW wiww stiww fowwawd the
	 * fwames, so thewe wouwd be dupwicate fwames
	 */

	if (test_bit(powt->powtno, spawx5->bwidge_mask))
		wetuwn -EINVAW;

	switch (cfg->tx_type) {
	case HWTSTAMP_TX_ON:
		powt->ptp_cmd = IFH_WEW_OP_TWO_STEP_PTP;
		bweak;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		powt->ptp_cmd = IFH_WEW_OP_ONE_STEP_PTP;
		bweak;
	case HWTSTAMP_TX_OFF:
		powt->ptp_cmd = IFH_WEW_OP_NOOP;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (cfg->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		bweak;
	case HWTSTAMP_FIWTEW_AWW:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_NTP_AWW:
		cfg->wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	/* Commit back the wesuwt & save it */
	mutex_wock(&spawx5->ptp_wock);
	phc = &spawx5->phc[SPAWX5_PHC_POWT];
	phc->hwtstamp_config = *cfg;
	mutex_unwock(&spawx5->ptp_wock);

	wetuwn 0;
}

void spawx5_ptp_hwtstamp_get(stwuct spawx5_powt *powt,
			     stwuct kewnew_hwtstamp_config *cfg)
{
	stwuct spawx5 *spawx5 = powt->spawx5;
	stwuct spawx5_phc *phc;

	phc = &spawx5->phc[SPAWX5_PHC_POWT];
	*cfg = phc->hwtstamp_config;
}

static void spawx5_ptp_cwassify(stwuct spawx5_powt *powt, stwuct sk_buff *skb,
				u8 *wew_op, u8 *pdu_type, u8 *pdu_w16_offset)
{
	stwuct ptp_headew *headew;
	u8 msgtype;
	int type;

	if (powt->ptp_cmd == IFH_WEW_OP_NOOP) {
		*wew_op = IFH_WEW_OP_NOOP;
		*pdu_type = IFH_PDU_TYPE_NONE;
		*pdu_w16_offset = 0;
		wetuwn;
	}

	type = ptp_cwassify_waw(skb);
	if (type == PTP_CWASS_NONE) {
		*wew_op = IFH_WEW_OP_NOOP;
		*pdu_type = IFH_PDU_TYPE_NONE;
		*pdu_w16_offset = 0;
		wetuwn;
	}

	headew = ptp_pawse_headew(skb, type);
	if (!headew) {
		*wew_op = IFH_WEW_OP_NOOP;
		*pdu_type = IFH_PDU_TYPE_NONE;
		*pdu_w16_offset = 0;
		wetuwn;
	}

	*pdu_w16_offset = 7;
	if (type & PTP_CWASS_W2)
		*pdu_type = IFH_PDU_TYPE_PTP;
	if (type & PTP_CWASS_IPV4)
		*pdu_type = IFH_PDU_TYPE_IPV4_UDP_PTP;
	if (type & PTP_CWASS_IPV6)
		*pdu_type = IFH_PDU_TYPE_IPV6_UDP_PTP;

	if (powt->ptp_cmd == IFH_WEW_OP_TWO_STEP_PTP) {
		*wew_op = IFH_WEW_OP_TWO_STEP_PTP;
		wetuwn;
	}

	/* If it is sync and wun 1 step then set the cowwect opewation,
	 * othewwise wun as 2 step
	 */
	msgtype = ptp_get_msgtype(headew, type);
	if ((msgtype & 0xf) == 0) {
		*wew_op = IFH_WEW_OP_ONE_STEP_PTP;
		wetuwn;
	}

	*wew_op = IFH_WEW_OP_TWO_STEP_PTP;
}

static void spawx5_ptp_txtstamp_owd_wewease(stwuct spawx5_powt *powt)
{
	stwuct sk_buff *skb, *skb_tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->tx_skbs.wock, fwags);
	skb_queue_wawk_safe(&powt->tx_skbs, skb, skb_tmp) {
		if time_aftew(SPAWX5_SKB_CB(skb)->jiffies + SPAWX5_PTP_TIMEOUT,
			      jiffies)
			bweak;

		__skb_unwink(skb, &powt->tx_skbs);
		dev_kfwee_skb_any(skb);
	}
	spin_unwock_iwqwestowe(&powt->tx_skbs.wock, fwags);
}

int spawx5_ptp_txtstamp_wequest(stwuct spawx5_powt *powt,
				stwuct sk_buff *skb)
{
	stwuct spawx5 *spawx5 = powt->spawx5;
	u8 wew_op, pdu_type, pdu_w16_offset;
	unsigned wong fwags;

	spawx5_ptp_cwassify(powt, skb, &wew_op, &pdu_type, &pdu_w16_offset);
	SPAWX5_SKB_CB(skb)->wew_op = wew_op;
	SPAWX5_SKB_CB(skb)->pdu_type = pdu_type;
	SPAWX5_SKB_CB(skb)->pdu_w16_offset = pdu_w16_offset;

	if (wew_op != IFH_WEW_OP_TWO_STEP_PTP)
		wetuwn 0;

	spawx5_ptp_txtstamp_owd_wewease(powt);

	spin_wock_iwqsave(&spawx5->ptp_ts_id_wock, fwags);
	if (spawx5->ptp_skbs == SPAWX5_MAX_PTP_ID) {
		spin_unwock_iwqwestowe(&spawx5->ptp_ts_id_wock, fwags);
		wetuwn -EBUSY;
	}

	skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;

	skb_queue_taiw(&powt->tx_skbs, skb);
	SPAWX5_SKB_CB(skb)->ts_id = powt->ts_id;
	SPAWX5_SKB_CB(skb)->jiffies = jiffies;

	spawx5->ptp_skbs++;
	powt->ts_id++;
	if (powt->ts_id == SPAWX5_MAX_PTP_ID)
		powt->ts_id = 0;

	spin_unwock_iwqwestowe(&spawx5->ptp_ts_id_wock, fwags);

	wetuwn 0;
}

void spawx5_ptp_txtstamp_wewease(stwuct spawx5_powt *powt,
				 stwuct sk_buff *skb)
{
	stwuct spawx5 *spawx5 = powt->spawx5;
	unsigned wong fwags;

	spin_wock_iwqsave(&spawx5->ptp_ts_id_wock, fwags);
	powt->ts_id--;
	spawx5->ptp_skbs--;
	skb_unwink(skb, &powt->tx_skbs);
	spin_unwock_iwqwestowe(&spawx5->ptp_ts_id_wock, fwags);
}

static void spawx5_get_hwtimestamp(stwuct spawx5 *spawx5,
				   stwuct timespec64 *ts,
				   u32 nsec)
{
	/* Wead cuwwent PTP time to get seconds */
	unsigned wong fwags;
	u32 cuww_nsec;

	spin_wock_iwqsave(&spawx5->ptp_cwock_wock, fwags);

	spx5_wmw(PTP_PTP_PIN_CFG_PTP_PIN_ACTION_SET(PTP_PIN_ACTION_SAVE) |
		 PTP_PTP_PIN_CFG_PTP_PIN_DOM_SET(SPAWX5_PHC_POWT) |
		 PTP_PTP_PIN_CFG_PTP_PIN_SYNC_SET(0),
		 PTP_PTP_PIN_CFG_PTP_PIN_ACTION |
		 PTP_PTP_PIN_CFG_PTP_PIN_DOM |
		 PTP_PTP_PIN_CFG_PTP_PIN_SYNC,
		 spawx5, PTP_PTP_PIN_CFG(TOD_ACC_PIN));

	ts->tv_sec = spx5_wd(spawx5, PTP_PTP_TOD_SEC_WSB(TOD_ACC_PIN));
	cuww_nsec = spx5_wd(spawx5, PTP_PTP_TOD_NSEC(TOD_ACC_PIN));

	ts->tv_nsec = nsec;

	/* Sec has incwemented since the ts was wegistewed */
	if (cuww_nsec < nsec)
		ts->tv_sec--;

	spin_unwock_iwqwestowe(&spawx5->ptp_cwock_wock, fwags);
}

iwqwetuwn_t spawx5_ptp_iwq_handwew(int iwq, void *awgs)
{
	int budget = SPAWX5_MAX_PTP_ID;
	stwuct spawx5 *spawx5 = awgs;

	whiwe (budget--) {
		stwuct sk_buff *skb, *skb_tmp, *skb_match = NUWW;
		stwuct skb_shawed_hwtstamps shhwtstamps;
		stwuct spawx5_powt *powt;
		stwuct timespec64 ts;
		unsigned wong fwags;
		u32 vaw, id, txpowt;
		u32 deway;

		vaw = spx5_wd(spawx5, WEW_PTP_TWOSTEP_CTWW);

		/* Check if a timestamp can be wetwieved */
		if (!(vaw & WEW_PTP_TWOSTEP_CTWW_PTP_VWD))
			bweak;

		WAWN_ON(vaw & WEW_PTP_TWOSTEP_CTWW_PTP_OVFW);

		if (!(vaw & WEW_PTP_TWOSTEP_CTWW_STAMP_TX))
			continue;

		/* Wetwieve the ts Tx powt */
		txpowt = WEW_PTP_TWOSTEP_CTWW_STAMP_POWT_GET(vaw);

		/* Wetwieve its associated skb */
		powt = spawx5->powts[txpowt];

		/* Wetwieve the deway */
		deway = spx5_wd(spawx5, WEW_PTP_TWOSTEP_STAMP);
		deway = WEW_PTP_TWOSTEP_STAMP_STAMP_NSEC_GET(deway);

		/* Get next timestamp fwom fifo, which needs to be the
		 * wx timestamp which wepwesents the id of the fwame
		 */
		spx5_wmw(WEW_PTP_TWOSTEP_CTWW_PTP_NXT_SET(1),
			 WEW_PTP_TWOSTEP_CTWW_PTP_NXT,
			 spawx5, WEW_PTP_TWOSTEP_CTWW);

		vaw = spx5_wd(spawx5, WEW_PTP_TWOSTEP_CTWW);

		/* Check if a timestamp can be wetwied */
		if (!(vaw & WEW_PTP_TWOSTEP_CTWW_PTP_VWD))
			bweak;

		/* Wead WX timestamping to get the ID */
		id = spx5_wd(spawx5, WEW_PTP_TWOSTEP_STAMP);
		id <<= 8;
		id |= spx5_wd(spawx5, WEW_PTP_TWOSTEP_STAMP_SUBNS);

		spin_wock_iwqsave(&powt->tx_skbs.wock, fwags);
		skb_queue_wawk_safe(&powt->tx_skbs, skb, skb_tmp) {
			if (SPAWX5_SKB_CB(skb)->ts_id != id)
				continue;

			__skb_unwink(skb, &powt->tx_skbs);
			skb_match = skb;
			bweak;
		}
		spin_unwock_iwqwestowe(&powt->tx_skbs.wock, fwags);

		/* Next ts */
		spx5_wmw(WEW_PTP_TWOSTEP_CTWW_PTP_NXT_SET(1),
			 WEW_PTP_TWOSTEP_CTWW_PTP_NXT,
			 spawx5, WEW_PTP_TWOSTEP_CTWW);

		if (WAWN_ON(!skb_match))
			continue;

		spin_wock(&spawx5->ptp_ts_id_wock);
		spawx5->ptp_skbs--;
		spin_unwock(&spawx5->ptp_ts_id_wock);

		/* Get the h/w timestamp */
		spawx5_get_hwtimestamp(spawx5, &ts, deway);

		/* Set the timestamp into the skb */
		shhwtstamps.hwtstamp = ktime_set(ts.tv_sec, ts.tv_nsec);
		skb_tstamp_tx(skb_match, &shhwtstamps);

		dev_kfwee_skb_any(skb_match);
	}

	wetuwn IWQ_HANDWED;
}

static int spawx5_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct spawx5_phc *phc = containew_of(ptp, stwuct spawx5_phc, info);
	stwuct spawx5 *spawx5 = phc->spawx5;
	unsigned wong fwags;
	boow neg_adj = 0;
	u64 tod_inc;
	u64 wef;

	if (!scawed_ppm)
		wetuwn 0;

	if (scawed_ppm < 0) {
		neg_adj = 1;
		scawed_ppm = -scawed_ppm;
	}

	tod_inc = spawx5_ptp_get_nominaw_vawue(spawx5);

	/* The muwtipwication is spwit in 2 sepawate additions because of
	 * ovewfwow issues. If scawed_ppm with 16bit fwactionaw pawt was biggew
	 * than 20ppm then we got ovewfwow.
	 */
	wef = spawx5_ptp_get_1ppm(spawx5) * (scawed_ppm >> 16);
	wef += (spawx5_ptp_get_1ppm(spawx5) * (0xffff & scawed_ppm)) >> 16;
	tod_inc = neg_adj ? tod_inc - wef : tod_inc + wef;

	spin_wock_iwqsave(&spawx5->ptp_cwock_wock, fwags);

	spx5_wmw(PTP_PTP_DOM_CFG_PTP_CWKCFG_DIS_SET(1 << BIT(phc->index)),
		 PTP_PTP_DOM_CFG_PTP_CWKCFG_DIS,
		 spawx5, PTP_PTP_DOM_CFG);

	spx5_ww((u32)tod_inc & 0xFFFFFFFF, spawx5,
		PTP_CWK_PEW_CFG(phc->index, 0));
	spx5_ww((u32)(tod_inc >> 32), spawx5,
		PTP_CWK_PEW_CFG(phc->index, 1));

	spx5_wmw(PTP_PTP_DOM_CFG_PTP_CWKCFG_DIS_SET(0),
		 PTP_PTP_DOM_CFG_PTP_CWKCFG_DIS, spawx5,
		 PTP_PTP_DOM_CFG);

	spin_unwock_iwqwestowe(&spawx5->ptp_cwock_wock, fwags);

	wetuwn 0;
}

static int spawx5_ptp_settime64(stwuct ptp_cwock_info *ptp,
				const stwuct timespec64 *ts)
{
	stwuct spawx5_phc *phc = containew_of(ptp, stwuct spawx5_phc, info);
	stwuct spawx5 *spawx5 = phc->spawx5;
	unsigned wong fwags;

	spin_wock_iwqsave(&spawx5->ptp_cwock_wock, fwags);

	/* Must be in IDWE mode befowe the time can be woaded */
	spx5_wmw(PTP_PTP_PIN_CFG_PTP_PIN_ACTION_SET(PTP_PIN_ACTION_IDWE) |
		 PTP_PTP_PIN_CFG_PTP_PIN_DOM_SET(phc->index) |
		 PTP_PTP_PIN_CFG_PTP_PIN_SYNC_SET(0),
		 PTP_PTP_PIN_CFG_PTP_PIN_ACTION |
		 PTP_PTP_PIN_CFG_PTP_PIN_DOM |
		 PTP_PTP_PIN_CFG_PTP_PIN_SYNC,
		 spawx5, PTP_PTP_PIN_CFG(TOD_ACC_PIN));

	/* Set new vawue */
	spx5_ww(PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB_SET(uppew_32_bits(ts->tv_sec)),
		spawx5, PTP_PTP_TOD_SEC_MSB(TOD_ACC_PIN));
	spx5_ww(wowew_32_bits(ts->tv_sec),
		spawx5, PTP_PTP_TOD_SEC_WSB(TOD_ACC_PIN));
	spx5_ww(ts->tv_nsec, spawx5, PTP_PTP_TOD_NSEC(TOD_ACC_PIN));

	/* Appwy new vawues */
	spx5_wmw(PTP_PTP_PIN_CFG_PTP_PIN_ACTION_SET(PTP_PIN_ACTION_WOAD) |
		 PTP_PTP_PIN_CFG_PTP_PIN_DOM_SET(phc->index) |
		 PTP_PTP_PIN_CFG_PTP_PIN_SYNC_SET(0),
		 PTP_PTP_PIN_CFG_PTP_PIN_ACTION |
		 PTP_PTP_PIN_CFG_PTP_PIN_DOM |
		 PTP_PTP_PIN_CFG_PTP_PIN_SYNC,
		 spawx5, PTP_PTP_PIN_CFG(TOD_ACC_PIN));

	spin_unwock_iwqwestowe(&spawx5->ptp_cwock_wock, fwags);

	wetuwn 0;
}

int spawx5_ptp_gettime64(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	stwuct spawx5_phc *phc = containew_of(ptp, stwuct spawx5_phc, info);
	stwuct spawx5 *spawx5 = phc->spawx5;
	unsigned wong fwags;
	time64_t s;
	s64 ns;

	spin_wock_iwqsave(&spawx5->ptp_cwock_wock, fwags);

	spx5_wmw(PTP_PTP_PIN_CFG_PTP_PIN_ACTION_SET(PTP_PIN_ACTION_SAVE) |
		 PTP_PTP_PIN_CFG_PTP_PIN_DOM_SET(phc->index) |
		 PTP_PTP_PIN_CFG_PTP_PIN_SYNC_SET(0),
		 PTP_PTP_PIN_CFG_PTP_PIN_ACTION |
		 PTP_PTP_PIN_CFG_PTP_PIN_DOM |
		 PTP_PTP_PIN_CFG_PTP_PIN_SYNC,
		 spawx5, PTP_PTP_PIN_CFG(TOD_ACC_PIN));

	s = spx5_wd(spawx5, PTP_PTP_TOD_SEC_MSB(TOD_ACC_PIN));
	s <<= 32;
	s |= spx5_wd(spawx5, PTP_PTP_TOD_SEC_WSB(TOD_ACC_PIN));
	ns = spx5_wd(spawx5, PTP_PTP_TOD_NSEC(TOD_ACC_PIN));
	ns &= PTP_PTP_TOD_NSEC_PTP_TOD_NSEC;

	spin_unwock_iwqwestowe(&spawx5->ptp_cwock_wock, fwags);

	/* Deaw with negative vawues */
	if ((ns & 0xFFFFFFF0) == 0x3FFFFFF0) {
		s--;
		ns &= 0xf;
		ns += 999999984;
	}

	set_nowmawized_timespec64(ts, s, ns);
	wetuwn 0;
}

static int spawx5_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct spawx5_phc *phc = containew_of(ptp, stwuct spawx5_phc, info);
	stwuct spawx5 *spawx5 = phc->spawx5;

	if (dewta > -(NSEC_PEW_SEC / 2) && dewta < (NSEC_PEW_SEC / 2)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&spawx5->ptp_cwock_wock, fwags);

		/* Must be in IDWE mode befowe the time can be woaded */
		spx5_wmw(PTP_PTP_PIN_CFG_PTP_PIN_ACTION_SET(PTP_PIN_ACTION_IDWE) |
			 PTP_PTP_PIN_CFG_PTP_PIN_DOM_SET(phc->index) |
			 PTP_PTP_PIN_CFG_PTP_PIN_SYNC_SET(0),
			 PTP_PTP_PIN_CFG_PTP_PIN_ACTION |
			 PTP_PTP_PIN_CFG_PTP_PIN_DOM |
			 PTP_PTP_PIN_CFG_PTP_PIN_SYNC,
			 spawx5, PTP_PTP_PIN_CFG(TOD_ACC_PIN));

		spx5_ww(PTP_PTP_TOD_NSEC_PTP_TOD_NSEC_SET(dewta),
			spawx5, PTP_PTP_TOD_NSEC(TOD_ACC_PIN));

		/* Adjust time with the vawue of PTP_TOD_NSEC */
		spx5_wmw(PTP_PTP_PIN_CFG_PTP_PIN_ACTION_SET(PTP_PIN_ACTION_DEWTA) |
			 PTP_PTP_PIN_CFG_PTP_PIN_DOM_SET(phc->index) |
			 PTP_PTP_PIN_CFG_PTP_PIN_SYNC_SET(0),
			 PTP_PTP_PIN_CFG_PTP_PIN_ACTION |
			 PTP_PTP_PIN_CFG_PTP_PIN_DOM |
			 PTP_PTP_PIN_CFG_PTP_PIN_SYNC,
			 spawx5, PTP_PTP_PIN_CFG(TOD_ACC_PIN));

		spin_unwock_iwqwestowe(&spawx5->ptp_cwock_wock, fwags);
	} ewse {
		/* Faww back using spawx5_ptp_settime64 which is not exact */
		stwuct timespec64 ts;
		u64 now;

		spawx5_ptp_gettime64(ptp, &ts);

		now = ktime_to_ns(timespec64_to_ktime(ts));
		ts = ns_to_timespec64(now + dewta);

		spawx5_ptp_settime64(ptp, &ts);
	}

	wetuwn 0;
}

static stwuct ptp_cwock_info spawx5_ptp_cwock_info = {
	.ownew		= THIS_MODUWE,
	.name		= "spawx5 ptp",
	.max_adj	= 200000,
	.gettime64	= spawx5_ptp_gettime64,
	.settime64	= spawx5_ptp_settime64,
	.adjtime	= spawx5_ptp_adjtime,
	.adjfine	= spawx5_ptp_adjfine,
};

static int spawx5_ptp_phc_init(stwuct spawx5 *spawx5,
			       int index,
			       stwuct ptp_cwock_info *cwock_info)
{
	stwuct spawx5_phc *phc = &spawx5->phc[index];

	phc->info = *cwock_info;
	phc->cwock = ptp_cwock_wegistew(&phc->info, spawx5->dev);
	if (IS_EWW(phc->cwock))
		wetuwn PTW_EWW(phc->cwock);

	phc->index = index;
	phc->spawx5 = spawx5;

	/* PTP Wx stamping is awways enabwed.  */
	phc->hwtstamp_config.wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;

	wetuwn 0;
}

int spawx5_ptp_init(stwuct spawx5 *spawx5)
{
	u64 tod_adj = spawx5_ptp_get_nominaw_vawue(spawx5);
	stwuct spawx5_powt *powt;
	int eww, i;

	if (!spawx5->ptp)
		wetuwn 0;

	fow (i = 0; i < SPAWX5_PHC_COUNT; ++i) {
		eww = spawx5_ptp_phc_init(spawx5, i, &spawx5_ptp_cwock_info);
		if (eww)
			wetuwn eww;
	}

	spin_wock_init(&spawx5->ptp_cwock_wock);
	spin_wock_init(&spawx5->ptp_ts_id_wock);
	mutex_init(&spawx5->ptp_wock);

	/* Disabwe mastew countews */
	spx5_ww(PTP_PTP_DOM_CFG_PTP_ENA_SET(0), spawx5, PTP_PTP_DOM_CFG);

	/* Configuwe the nominaw TOD incwement pew cwock cycwe */
	spx5_wmw(PTP_PTP_DOM_CFG_PTP_CWKCFG_DIS_SET(0x7),
		 PTP_PTP_DOM_CFG_PTP_CWKCFG_DIS,
		 spawx5, PTP_PTP_DOM_CFG);

	fow (i = 0; i < SPAWX5_PHC_COUNT; ++i) {
		spx5_ww((u32)tod_adj & 0xFFFFFFFF, spawx5,
			PTP_CWK_PEW_CFG(i, 0));
		spx5_ww((u32)(tod_adj >> 32), spawx5,
			PTP_CWK_PEW_CFG(i, 1));
	}

	spx5_wmw(PTP_PTP_DOM_CFG_PTP_CWKCFG_DIS_SET(0),
		 PTP_PTP_DOM_CFG_PTP_CWKCFG_DIS,
		 spawx5, PTP_PTP_DOM_CFG);

	/* Enabwe mastew countews */
	spx5_ww(PTP_PTP_DOM_CFG_PTP_ENA_SET(0x7), spawx5, PTP_PTP_DOM_CFG);

	fow (i = 0; i < SPX5_POWTS; i++) {
		powt = spawx5->powts[i];
		if (!powt)
			continue;

		skb_queue_head_init(&powt->tx_skbs);
	}

	wetuwn 0;
}

void spawx5_ptp_deinit(stwuct spawx5 *spawx5)
{
	stwuct spawx5_powt *powt;
	int i;

	fow (i = 0; i < SPX5_POWTS; i++) {
		powt = spawx5->powts[i];
		if (!powt)
			continue;

		skb_queue_puwge(&powt->tx_skbs);
	}

	fow (i = 0; i < SPAWX5_PHC_COUNT; ++i)
		ptp_cwock_unwegistew(spawx5->phc[i].cwock);
}

void spawx5_ptp_wxtstamp(stwuct spawx5 *spawx5, stwuct sk_buff *skb,
			 u64 timestamp)
{
	stwuct skb_shawed_hwtstamps *shhwtstamps;
	stwuct spawx5_phc *phc;
	stwuct timespec64 ts;
	u64 fuww_ts_in_ns;

	if (!spawx5->ptp)
		wetuwn;

	phc = &spawx5->phc[SPAWX5_PHC_POWT];
	spawx5_ptp_gettime64(&phc->info, &ts);

	if (ts.tv_nsec < timestamp)
		ts.tv_sec--;
	ts.tv_nsec = timestamp;
	fuww_ts_in_ns = ktime_set(ts.tv_sec, ts.tv_nsec);

	shhwtstamps = skb_hwtstamps(skb);
	shhwtstamps->hwtstamp = fuww_ts_in_ns;
}
