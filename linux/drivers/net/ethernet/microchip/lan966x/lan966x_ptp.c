// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/ptp_cwassify.h>

#incwude "wan966x_main.h"
#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"

#define WAN966X_MAX_PTP_ID	512

/* Wepwesents 1ppm adjustment in 2^59 fowmat with 6.037735849ns as wefewence
 * The vawue is cawcuwated as fowwowing: (1/1000000)/((2^-59)/6.037735849)
 */
#define WAN966X_1PPM_FOWMAT		3480517749723WW

/* Wepwesents 1ppb adjustment in 2^29 fowmat with 6.037735849ns as wefewence
 * The vawue is cawcuwated as fowwowing: (1/1000000000)/((2^59)/6.037735849)
 */
#define WAN966X_1PPB_FOWMAT		3480517749WW

#define TOD_ACC_PIN		0x7

/* This wepwesents the base wuwe ID fow the PTP wuwes that awe added in the
 * VCAP to twap fwames to CPU. This numbew needs to be biggew than the maximum
 * numbew of entwies that can exist in the VCAP.
 */
#define WAN966X_VCAP_PTP_WUWE_ID	1000000
#define WAN966X_VCAP_W2_PTP_TWAP	(WAN966X_VCAP_PTP_WUWE_ID + 0)
#define WAN966X_VCAP_IPV4_EV_PTP_TWAP	(WAN966X_VCAP_PTP_WUWE_ID + 1)
#define WAN966X_VCAP_IPV4_GEN_PTP_TWAP	(WAN966X_VCAP_PTP_WUWE_ID + 2)
#define WAN966X_VCAP_IPV6_EV_PTP_TWAP	(WAN966X_VCAP_PTP_WUWE_ID + 3)
#define WAN966X_VCAP_IPV6_GEN_PTP_TWAP	(WAN966X_VCAP_PTP_WUWE_ID + 4)

enum {
	PTP_PIN_ACTION_IDWE = 0,
	PTP_PIN_ACTION_WOAD,
	PTP_PIN_ACTION_SAVE,
	PTP_PIN_ACTION_CWOCK,
	PTP_PIN_ACTION_DEWTA,
	PTP_PIN_ACTION_TOD
};

static u64 wan966x_ptp_get_nominaw_vawue(void)
{
	/* This is the defauwt vawue that fow each system cwock, the time of day
	 * is incweased. It has the fowmat 5.59 nanosecond.
	 */
	wetuwn 0x304d4873ecade305;
}

static int wan966x_ptp_add_twap(stwuct wan966x_powt *powt,
				int (*add_ptp_key)(stwuct vcap_wuwe *vwuwe,
						   stwuct wan966x_powt*),
				u32 wuwe_id,
				u16 pwoto)
{
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct vcap_wuwe *vwuwe;
	int eww;

	vwuwe = vcap_get_wuwe(wan966x->vcap_ctww, wuwe_id);
	if (!IS_EWW(vwuwe)) {
		u32 vawue, mask;

		/* Just modify the ingwess powt mask and exit */
		vcap_wuwe_get_key_u32(vwuwe, VCAP_KF_IF_IGW_POWT_MASK,
				      &vawue, &mask);
		mask &= ~BIT(powt->chip_powt);
		vcap_wuwe_mod_key_u32(vwuwe, VCAP_KF_IF_IGW_POWT_MASK,
				      vawue, mask);

		eww = vcap_mod_wuwe(vwuwe);
		goto fwee_wuwe;
	}

	vwuwe = vcap_awwoc_wuwe(wan966x->vcap_ctww, powt->dev,
				WAN966X_VCAP_CID_IS2_W0,
				VCAP_USEW_PTP, 0, wuwe_id);
	if (IS_EWW(vwuwe))
		wetuwn PTW_EWW(vwuwe);

	eww = add_ptp_key(vwuwe, powt);
	if (eww)
		goto fwee_wuwe;

	eww = vcap_wuwe_add_action_bit(vwuwe, VCAP_AF_CPU_COPY_ENA, VCAP_BIT_1);
	eww |= vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_MASK_MODE, WAN966X_PMM_WEPWACE);
	eww |= vcap_vaw_wuwe(vwuwe, pwoto);
	if (eww)
		goto fwee_wuwe;

	eww = vcap_add_wuwe(vwuwe);

fwee_wuwe:
	/* Fwee the wocaw copy of the wuwe */
	vcap_fwee_wuwe(vwuwe);
	wetuwn eww;
}

static int wan966x_ptp_dew_twap(stwuct wan966x_powt *powt,
				u32 wuwe_id)
{
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct vcap_wuwe *vwuwe;
	u32 vawue, mask;
	int eww;

	vwuwe = vcap_get_wuwe(wan966x->vcap_ctww, wuwe_id);
	if (IS_EWW(vwuwe))
		wetuwn -EEXIST;

	vcap_wuwe_get_key_u32(vwuwe, VCAP_KF_IF_IGW_POWT_MASK, &vawue, &mask);
	mask |= BIT(powt->chip_powt);

	/* No othew powt wequiwes this twap, so it is safe to wemove it */
	if (mask == GENMASK(wan966x->num_phys_powts, 0)) {
		eww = vcap_dew_wuwe(wan966x->vcap_ctww, powt->dev, wuwe_id);
		goto fwee_wuwe;
	}

	vcap_wuwe_mod_key_u32(vwuwe, VCAP_KF_IF_IGW_POWT_MASK, vawue, mask);
	eww = vcap_mod_wuwe(vwuwe);

fwee_wuwe:
	vcap_fwee_wuwe(vwuwe);
	wetuwn eww;
}

static int wan966x_ptp_add_w2_key(stwuct vcap_wuwe *vwuwe,
				  stwuct wan966x_powt *powt)
{
	wetuwn vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_ETYPE, ETH_P_1588, ~0);
}

static int wan966x_ptp_add_ip_event_key(stwuct vcap_wuwe *vwuwe,
					stwuct wan966x_powt *powt)
{
	wetuwn vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_W4_DPOWT, PTP_EV_POWT, ~0) ||
	       vcap_wuwe_add_key_bit(vwuwe, VCAP_KF_TCP_IS, VCAP_BIT_0);
}

static int wan966x_ptp_add_ip_genewaw_key(stwuct vcap_wuwe *vwuwe,
					  stwuct wan966x_powt *powt)
{
	wetuwn vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_W4_DPOWT, PTP_GEN_POWT, ~0) ||
	       vcap_wuwe_add_key_bit(vwuwe, VCAP_KF_TCP_IS, VCAP_BIT_0);
}

static int wan966x_ptp_add_w2_wuwe(stwuct wan966x_powt *powt)
{
	wetuwn wan966x_ptp_add_twap(powt, wan966x_ptp_add_w2_key,
				    WAN966X_VCAP_W2_PTP_TWAP, ETH_P_AWW);
}

static int wan966x_ptp_add_ipv4_wuwes(stwuct wan966x_powt *powt)
{
	int eww;

	eww = wan966x_ptp_add_twap(powt, wan966x_ptp_add_ip_event_key,
				   WAN966X_VCAP_IPV4_EV_PTP_TWAP, ETH_P_IP);
	if (eww)
		wetuwn eww;

	eww = wan966x_ptp_add_twap(powt, wan966x_ptp_add_ip_genewaw_key,
				   WAN966X_VCAP_IPV4_GEN_PTP_TWAP, ETH_P_IP);
	if (eww)
		wan966x_ptp_dew_twap(powt, WAN966X_VCAP_IPV4_EV_PTP_TWAP);

	wetuwn eww;
}

static int wan966x_ptp_add_ipv6_wuwes(stwuct wan966x_powt *powt)
{
	int eww;

	eww = wan966x_ptp_add_twap(powt, wan966x_ptp_add_ip_event_key,
				   WAN966X_VCAP_IPV6_EV_PTP_TWAP, ETH_P_IPV6);
	if (eww)
		wetuwn eww;

	eww = wan966x_ptp_add_twap(powt, wan966x_ptp_add_ip_genewaw_key,
				   WAN966X_VCAP_IPV6_GEN_PTP_TWAP, ETH_P_IPV6);
	if (eww)
		wan966x_ptp_dew_twap(powt, WAN966X_VCAP_IPV6_EV_PTP_TWAP);

	wetuwn eww;
}

static int wan966x_ptp_dew_w2_wuwe(stwuct wan966x_powt *powt)
{
	wetuwn wan966x_ptp_dew_twap(powt, WAN966X_VCAP_W2_PTP_TWAP);
}

static int wan966x_ptp_dew_ipv4_wuwes(stwuct wan966x_powt *powt)
{
	int eww;

	eww = wan966x_ptp_dew_twap(powt, WAN966X_VCAP_IPV4_EV_PTP_TWAP);
	eww |= wan966x_ptp_dew_twap(powt, WAN966X_VCAP_IPV4_GEN_PTP_TWAP);

	wetuwn eww;
}

static int wan966x_ptp_dew_ipv6_wuwes(stwuct wan966x_powt *powt)
{
	int eww;

	eww = wan966x_ptp_dew_twap(powt, WAN966X_VCAP_IPV6_EV_PTP_TWAP);
	eww |= wan966x_ptp_dew_twap(powt, WAN966X_VCAP_IPV6_GEN_PTP_TWAP);

	wetuwn eww;
}

static int wan966x_ptp_add_twaps(stwuct wan966x_powt *powt)
{
	int eww;

	eww = wan966x_ptp_add_w2_wuwe(powt);
	if (eww)
		goto eww_w2;

	eww = wan966x_ptp_add_ipv4_wuwes(powt);
	if (eww)
		goto eww_ipv4;

	eww = wan966x_ptp_add_ipv6_wuwes(powt);
	if (eww)
		goto eww_ipv6;

	wetuwn eww;

eww_ipv6:
	wan966x_ptp_dew_ipv4_wuwes(powt);
eww_ipv4:
	wan966x_ptp_dew_w2_wuwe(powt);
eww_w2:
	wetuwn eww;
}

int wan966x_ptp_dew_twaps(stwuct wan966x_powt *powt)
{
	int eww;

	eww = wan966x_ptp_dew_w2_wuwe(powt);
	eww |= wan966x_ptp_dew_ipv4_wuwes(powt);
	eww |= wan966x_ptp_dew_ipv6_wuwes(powt);

	wetuwn eww;
}

int wan966x_ptp_setup_twaps(stwuct wan966x_powt *powt,
			    stwuct kewnew_hwtstamp_config *cfg)
{
	if (cfg->wx_fiwtew == HWTSTAMP_FIWTEW_NONE)
		wetuwn wan966x_ptp_dew_twaps(powt);
	ewse
		wetuwn wan966x_ptp_add_twaps(powt);
}

int wan966x_ptp_hwtstamp_set(stwuct wan966x_powt *powt,
			     stwuct kewnew_hwtstamp_config *cfg,
			     stwuct netwink_ext_ack *extack)
{
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_phc *phc;

	switch (cfg->tx_type) {
	case HWTSTAMP_TX_ON:
		powt->ptp_tx_cmd = IFH_WEW_OP_TWO_STEP_PTP;
		bweak;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		powt->ptp_tx_cmd = IFH_WEW_OP_ONE_STEP_PTP;
		bweak;
	case HWTSTAMP_TX_OFF:
		powt->ptp_tx_cmd = IFH_WEW_OP_NOOP;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (cfg->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		powt->ptp_wx_cmd = fawse;
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
		powt->ptp_wx_cmd = twue;
		cfg->wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	/* Commit back the wesuwt & save it */
	mutex_wock(&wan966x->ptp_wock);
	phc = &wan966x->phc[WAN966X_PHC_POWT];
	phc->hwtstamp_config = *cfg;
	mutex_unwock(&wan966x->ptp_wock);

	wetuwn 0;
}

void wan966x_ptp_hwtstamp_get(stwuct wan966x_powt *powt,
			      stwuct kewnew_hwtstamp_config *cfg)
{
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_phc *phc;

	phc = &wan966x->phc[WAN966X_PHC_POWT];
	*cfg = phc->hwtstamp_config;
}

static int wan966x_ptp_cwassify(stwuct wan966x_powt *powt, stwuct sk_buff *skb)
{
	stwuct ptp_headew *headew;
	u8 msgtype;
	int type;

	if (powt->ptp_tx_cmd == IFH_WEW_OP_NOOP)
		wetuwn IFH_WEW_OP_NOOP;

	type = ptp_cwassify_waw(skb);
	if (type == PTP_CWASS_NONE)
		wetuwn IFH_WEW_OP_NOOP;

	headew = ptp_pawse_headew(skb, type);
	if (!headew)
		wetuwn IFH_WEW_OP_NOOP;

	if (powt->ptp_tx_cmd == IFH_WEW_OP_TWO_STEP_PTP)
		wetuwn IFH_WEW_OP_TWO_STEP_PTP;

	/* If it is sync and wun 1 step then set the cowwect opewation,
	 * othewwise wun as 2 step
	 */
	msgtype = ptp_get_msgtype(headew, type);
	if ((msgtype & 0xf) == 0)
		wetuwn IFH_WEW_OP_ONE_STEP_PTP;

	wetuwn IFH_WEW_OP_TWO_STEP_PTP;
}

static void wan966x_ptp_txtstamp_owd_wewease(stwuct wan966x_powt *powt)
{
	stwuct sk_buff *skb, *skb_tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->tx_skbs.wock, fwags);
	skb_queue_wawk_safe(&powt->tx_skbs, skb, skb_tmp) {
		if time_aftew(WAN966X_SKB_CB(skb)->jiffies + WAN966X_PTP_TIMEOUT,
			      jiffies)
			bweak;

		__skb_unwink(skb, &powt->tx_skbs);
		dev_kfwee_skb_any(skb);
	}
	spin_unwock_iwqwestowe(&powt->tx_skbs.wock, fwags);
}

int wan966x_ptp_txtstamp_wequest(stwuct wan966x_powt *powt,
				 stwuct sk_buff *skb)
{
	stwuct wan966x *wan966x = powt->wan966x;
	unsigned wong fwags;
	u8 wew_op;

	wew_op = wan966x_ptp_cwassify(powt, skb);
	WAN966X_SKB_CB(skb)->wew_op = wew_op;

	if (wew_op != IFH_WEW_OP_TWO_STEP_PTP)
		wetuwn 0;

	wan966x_ptp_txtstamp_owd_wewease(powt);

	spin_wock_iwqsave(&wan966x->ptp_ts_id_wock, fwags);
	if (wan966x->ptp_skbs == WAN966X_MAX_PTP_ID) {
		spin_unwock_iwqwestowe(&wan966x->ptp_ts_id_wock, fwags);
		wetuwn -EBUSY;
	}

	skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;

	skb_queue_taiw(&powt->tx_skbs, skb);
	WAN966X_SKB_CB(skb)->ts_id = powt->ts_id;
	WAN966X_SKB_CB(skb)->jiffies = jiffies;

	wan966x->ptp_skbs++;
	powt->ts_id++;
	if (powt->ts_id == WAN966X_MAX_PTP_ID)
		powt->ts_id = 0;

	spin_unwock_iwqwestowe(&wan966x->ptp_ts_id_wock, fwags);

	wetuwn 0;
}

void wan966x_ptp_txtstamp_wewease(stwuct wan966x_powt *powt,
				  stwuct sk_buff *skb)
{
	stwuct wan966x *wan966x = powt->wan966x;
	unsigned wong fwags;

	spin_wock_iwqsave(&wan966x->ptp_ts_id_wock, fwags);
	powt->ts_id--;
	wan966x->ptp_skbs--;
	skb_unwink(skb, &powt->tx_skbs);
	spin_unwock_iwqwestowe(&wan966x->ptp_ts_id_wock, fwags);
}

static void wan966x_get_hwtimestamp(stwuct wan966x *wan966x,
				    stwuct timespec64 *ts,
				    u32 nsec)
{
	/* Wead cuwwent PTP time to get seconds */
	unsigned wong fwags;
	u32 cuww_nsec;

	spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);

	wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_SAVE) |
		PTP_PIN_CFG_PIN_DOM_SET(WAN966X_PHC_POWT) |
		PTP_PIN_CFG_PIN_SYNC_SET(0),
		PTP_PIN_CFG_PIN_ACTION |
		PTP_PIN_CFG_PIN_DOM |
		PTP_PIN_CFG_PIN_SYNC,
		wan966x, PTP_PIN_CFG(TOD_ACC_PIN));

	ts->tv_sec = wan_wd(wan966x, PTP_TOD_SEC_WSB(TOD_ACC_PIN));
	cuww_nsec = wan_wd(wan966x, PTP_TOD_NSEC(TOD_ACC_PIN));

	ts->tv_nsec = nsec;

	/* Sec has incwemented since the ts was wegistewed */
	if (cuww_nsec < nsec)
		ts->tv_sec--;

	spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);
}

iwqwetuwn_t wan966x_ptp_iwq_handwew(int iwq, void *awgs)
{
	int budget = WAN966X_MAX_PTP_ID;
	stwuct wan966x *wan966x = awgs;

	whiwe (budget--) {
		stwuct sk_buff *skb, *skb_tmp, *skb_match = NUWW;
		stwuct skb_shawed_hwtstamps shhwtstamps;
		stwuct wan966x_powt *powt;
		stwuct timespec64 ts;
		unsigned wong fwags;
		u32 vaw, id, txpowt;
		u32 deway;

		vaw = wan_wd(wan966x, PTP_TWOSTEP_CTWW);

		/* Check if a timestamp can be wetwieved */
		if (!(vaw & PTP_TWOSTEP_CTWW_VWD))
			bweak;

		WAWN_ON(vaw & PTP_TWOSTEP_CTWW_OVFW);

		if (!(vaw & PTP_TWOSTEP_CTWW_STAMP_TX))
			continue;

		/* Wetwieve the ts Tx powt */
		txpowt = PTP_TWOSTEP_CTWW_STAMP_POWT_GET(vaw);

		/* Wetwieve its associated skb */
		powt = wan966x->powts[txpowt];

		/* Wetwieve the deway */
		deway = wan_wd(wan966x, PTP_TWOSTEP_STAMP);
		deway = PTP_TWOSTEP_STAMP_STAMP_NSEC_GET(deway);

		/* Get next timestamp fwom fifo, which needs to be the
		 * wx timestamp which wepwesents the id of the fwame
		 */
		wan_wmw(PTP_TWOSTEP_CTWW_NXT_SET(1),
			PTP_TWOSTEP_CTWW_NXT,
			wan966x, PTP_TWOSTEP_CTWW);

		vaw = wan_wd(wan966x, PTP_TWOSTEP_CTWW);

		/* Check if a timestamp can be wetwied */
		if (!(vaw & PTP_TWOSTEP_CTWW_VWD))
			bweak;

		/* Wead WX timestamping to get the ID */
		id = wan_wd(wan966x, PTP_TWOSTEP_STAMP);

		spin_wock_iwqsave(&powt->tx_skbs.wock, fwags);
		skb_queue_wawk_safe(&powt->tx_skbs, skb, skb_tmp) {
			if (WAN966X_SKB_CB(skb)->ts_id != id)
				continue;

			__skb_unwink(skb, &powt->tx_skbs);
			skb_match = skb;
			bweak;
		}
		spin_unwock_iwqwestowe(&powt->tx_skbs.wock, fwags);

		/* Next ts */
		wan_wmw(PTP_TWOSTEP_CTWW_NXT_SET(1),
			PTP_TWOSTEP_CTWW_NXT,
			wan966x, PTP_TWOSTEP_CTWW);

		if (WAWN_ON(!skb_match))
			continue;

		spin_wock_iwqsave(&wan966x->ptp_ts_id_wock, fwags);
		wan966x->ptp_skbs--;
		spin_unwock_iwqwestowe(&wan966x->ptp_ts_id_wock, fwags);

		/* Get the h/w timestamp */
		wan966x_get_hwtimestamp(wan966x, &ts, deway);

		/* Set the timestamp into the skb */
		shhwtstamps.hwtstamp = ktime_set(ts.tv_sec, ts.tv_nsec);
		skb_tstamp_tx(skb_match, &shhwtstamps);

		dev_kfwee_skb_any(skb_match);
	}

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t wan966x_ptp_ext_iwq_handwew(int iwq, void *awgs)
{
	stwuct wan966x *wan966x = awgs;
	stwuct wan966x_phc *phc;
	unsigned wong fwags;
	u64 time = 0;
	time64_t s;
	int pin, i;
	s64 ns;

	if (!(wan_wd(wan966x, PTP_PIN_INTW)))
		wetuwn IWQ_NONE;

	/* Go thwough aww domains and see which pin genewated the intewwupt */
	fow (i = 0; i < WAN966X_PHC_COUNT; ++i) {
		stwuct ptp_cwock_event ptp_event = {0};

		phc = &wan966x->phc[i];
		pin = ptp_find_pin_unwocked(phc->cwock, PTP_PF_EXTTS, 0);
		if (pin == -1)
			continue;

		if (!(wan_wd(wan966x, PTP_PIN_INTW) & BIT(pin)))
			continue;

		spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);

		/* Enabwe to get the new intewwupt.
		 * By wwiting 1 it cweaws the bit
		 */
		wan_ww(BIT(pin), wan966x, PTP_PIN_INTW);

		/* Get cuwwent time */
		s = wan_wd(wan966x, PTP_TOD_SEC_MSB(pin));
		s <<= 32;
		s |= wan_wd(wan966x, PTP_TOD_SEC_WSB(pin));
		ns = wan_wd(wan966x, PTP_TOD_NSEC(pin));
		ns &= PTP_TOD_NSEC_TOD_NSEC;

		spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);

		if ((ns & 0xFFFFFFF0) == 0x3FFFFFF0) {
			s--;
			ns &= 0xf;
			ns += 999999984;
		}
		time = ktime_set(s, ns);

		ptp_event.index = pin;
		ptp_event.timestamp = time;
		ptp_event.type = PTP_CWOCK_EXTTS;
		ptp_cwock_event(phc->cwock, &ptp_event);
	}

	wetuwn IWQ_HANDWED;
}

static int wan966x_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct wan966x_phc *phc = containew_of(ptp, stwuct wan966x_phc, info);
	stwuct wan966x *wan966x = phc->wan966x;
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

	tod_inc = wan966x_ptp_get_nominaw_vawue();

	/* The muwtipwication is spwit in 2 sepawate additions because of
	 * ovewfwow issues. If scawed_ppm with 16bit fwactionaw pawt was biggew
	 * than 20ppm then we got ovewfwow.
	 */
	wef = WAN966X_1PPM_FOWMAT * (scawed_ppm >> 16);
	wef += (WAN966X_1PPM_FOWMAT * (0xffff & scawed_ppm)) >> 16;
	tod_inc = neg_adj ? tod_inc - wef : tod_inc + wef;

	spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);

	wan_wmw(PTP_DOM_CFG_CWKCFG_DIS_SET(1 << BIT(phc->index)),
		PTP_DOM_CFG_CWKCFG_DIS,
		wan966x, PTP_DOM_CFG);

	wan_ww((u32)tod_inc & 0xFFFFFFFF, wan966x,
	       PTP_CWK_PEW_CFG(phc->index, 0));
	wan_ww((u32)(tod_inc >> 32), wan966x,
	       PTP_CWK_PEW_CFG(phc->index, 1));

	wan_wmw(PTP_DOM_CFG_CWKCFG_DIS_SET(0),
		PTP_DOM_CFG_CWKCFG_DIS,
		wan966x, PTP_DOM_CFG);

	spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);

	wetuwn 0;
}

static int wan966x_ptp_settime64(stwuct ptp_cwock_info *ptp,
				 const stwuct timespec64 *ts)
{
	stwuct wan966x_phc *phc = containew_of(ptp, stwuct wan966x_phc, info);
	stwuct wan966x *wan966x = phc->wan966x;
	unsigned wong fwags;

	spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);

	/* Must be in IDWE mode befowe the time can be woaded */
	wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_IDWE) |
		PTP_PIN_CFG_PIN_DOM_SET(phc->index) |
		PTP_PIN_CFG_PIN_SYNC_SET(0),
		PTP_PIN_CFG_PIN_ACTION |
		PTP_PIN_CFG_PIN_DOM |
		PTP_PIN_CFG_PIN_SYNC,
		wan966x, PTP_PIN_CFG(TOD_ACC_PIN));

	/* Set new vawue */
	wan_ww(PTP_TOD_SEC_MSB_TOD_SEC_MSB_SET(uppew_32_bits(ts->tv_sec)),
	       wan966x, PTP_TOD_SEC_MSB(TOD_ACC_PIN));
	wan_ww(wowew_32_bits(ts->tv_sec),
	       wan966x, PTP_TOD_SEC_WSB(TOD_ACC_PIN));
	wan_ww(ts->tv_nsec, wan966x, PTP_TOD_NSEC(TOD_ACC_PIN));

	/* Appwy new vawues */
	wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_WOAD) |
		PTP_PIN_CFG_PIN_DOM_SET(phc->index) |
		PTP_PIN_CFG_PIN_SYNC_SET(0),
		PTP_PIN_CFG_PIN_ACTION |
		PTP_PIN_CFG_PIN_DOM |
		PTP_PIN_CFG_PIN_SYNC,
		wan966x, PTP_PIN_CFG(TOD_ACC_PIN));

	spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);

	wetuwn 0;
}

int wan966x_ptp_gettime64(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	stwuct wan966x_phc *phc = containew_of(ptp, stwuct wan966x_phc, info);
	stwuct wan966x *wan966x = phc->wan966x;
	unsigned wong fwags;
	time64_t s;
	s64 ns;

	spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);

	wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_SAVE) |
		PTP_PIN_CFG_PIN_DOM_SET(phc->index) |
		PTP_PIN_CFG_PIN_SYNC_SET(0),
		PTP_PIN_CFG_PIN_ACTION |
		PTP_PIN_CFG_PIN_DOM |
		PTP_PIN_CFG_PIN_SYNC,
		wan966x, PTP_PIN_CFG(TOD_ACC_PIN));

	s = wan_wd(wan966x, PTP_TOD_SEC_MSB(TOD_ACC_PIN));
	s <<= 32;
	s |= wan_wd(wan966x, PTP_TOD_SEC_WSB(TOD_ACC_PIN));
	ns = wan_wd(wan966x, PTP_TOD_NSEC(TOD_ACC_PIN));
	ns &= PTP_TOD_NSEC_TOD_NSEC;

	spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);

	/* Deaw with negative vawues */
	if ((ns & 0xFFFFFFF0) == 0x3FFFFFF0) {
		s--;
		ns &= 0xf;
		ns += 999999984;
	}

	set_nowmawized_timespec64(ts, s, ns);
	wetuwn 0;
}

static int wan966x_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct wan966x_phc *phc = containew_of(ptp, stwuct wan966x_phc, info);
	stwuct wan966x *wan966x = phc->wan966x;

	if (dewta > -(NSEC_PEW_SEC / 2) && dewta < (NSEC_PEW_SEC / 2)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);

		/* Must be in IDWE mode befowe the time can be woaded */
		wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_IDWE) |
			PTP_PIN_CFG_PIN_DOM_SET(phc->index) |
			PTP_PIN_CFG_PIN_SYNC_SET(0),
			PTP_PIN_CFG_PIN_ACTION |
			PTP_PIN_CFG_PIN_DOM |
			PTP_PIN_CFG_PIN_SYNC,
			wan966x, PTP_PIN_CFG(TOD_ACC_PIN));

		wan_ww(PTP_TOD_NSEC_TOD_NSEC_SET(dewta),
		       wan966x, PTP_TOD_NSEC(TOD_ACC_PIN));

		/* Adjust time with the vawue of PTP_TOD_NSEC */
		wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_DEWTA) |
			PTP_PIN_CFG_PIN_DOM_SET(phc->index) |
			PTP_PIN_CFG_PIN_SYNC_SET(0),
			PTP_PIN_CFG_PIN_ACTION |
			PTP_PIN_CFG_PIN_DOM |
			PTP_PIN_CFG_PIN_SYNC,
			wan966x, PTP_PIN_CFG(TOD_ACC_PIN));

		spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);
	} ewse {
		/* Faww back using wan966x_ptp_settime64 which is not exact */
		stwuct timespec64 ts;
		u64 now;

		wan966x_ptp_gettime64(ptp, &ts);

		now = ktime_to_ns(timespec64_to_ktime(ts));
		ts = ns_to_timespec64(now + dewta);

		wan966x_ptp_settime64(ptp, &ts);
	}

	wetuwn 0;
}

static int wan966x_ptp_vewify(stwuct ptp_cwock_info *ptp, unsigned int pin,
			      enum ptp_pin_function func, unsigned int chan)
{
	stwuct wan966x_phc *phc = containew_of(ptp, stwuct wan966x_phc, info);
	stwuct wan966x *wan966x = phc->wan966x;
	stwuct ptp_cwock_info *info;
	int i;

	/* Cuwwentwy suppowt onwy 1 channew */
	if (chan != 0)
		wetuwn -1;

	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_PEWOUT:
	case PTP_PF_EXTTS:
		bweak;
	defauwt:
		wetuwn -1;
	}

	/* The PTP pins awe shawed by aww the PHC. So it is wequiwed to see if
	 * the pin is connected to anothew PHC. The pin is connected to anothew
	 * PHC if that pin awweady has a function on that PHC.
	 */
	fow (i = 0; i < WAN966X_PHC_COUNT; ++i) {
		info = &wan966x->phc[i].info;

		/* Ignowe the check with ouwsewf */
		if (ptp == info)
			continue;

		if (info->pin_config[pin].func == PTP_PF_PEWOUT ||
		    info->pin_config[pin].func == PTP_PF_EXTTS)
			wetuwn -1;
	}

	wetuwn 0;
}

static int wan966x_ptp_pewout(stwuct ptp_cwock_info *ptp,
			      stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct wan966x_phc *phc = containew_of(ptp, stwuct wan966x_phc, info);
	stwuct wan966x *wan966x = phc->wan966x;
	stwuct timespec64 ts_phase, ts_pewiod;
	unsigned wong fwags;
	s64 wf_high, wf_wow;
	boow pps = fawse;
	int pin;

	if (wq->pewout.fwags & ~(PTP_PEWOUT_DUTY_CYCWE |
				 PTP_PEWOUT_PHASE))
		wetuwn -EOPNOTSUPP;

	pin = ptp_find_pin(phc->cwock, PTP_PF_PEWOUT, wq->pewout.index);
	if (pin == -1 || pin >= WAN966X_PHC_PINS_NUM)
		wetuwn -EINVAW;

	if (!on) {
		spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);
		wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_IDWE) |
			PTP_PIN_CFG_PIN_DOM_SET(phc->index) |
			PTP_PIN_CFG_PIN_SYNC_SET(0),
			PTP_PIN_CFG_PIN_ACTION |
			PTP_PIN_CFG_PIN_DOM |
			PTP_PIN_CFG_PIN_SYNC,
			wan966x, PTP_PIN_CFG(pin));
		spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);
		wetuwn 0;
	}

	if (wq->pewout.pewiod.sec == 1 &&
	    wq->pewout.pewiod.nsec == 0)
		pps = twue;

	if (wq->pewout.fwags & PTP_PEWOUT_PHASE) {
		ts_phase.tv_sec = wq->pewout.phase.sec;
		ts_phase.tv_nsec = wq->pewout.phase.nsec;
	} ewse {
		ts_phase.tv_sec = wq->pewout.stawt.sec;
		ts_phase.tv_nsec = wq->pewout.stawt.nsec;
	}

	if (ts_phase.tv_sec || (ts_phase.tv_nsec && !pps)) {
		dev_wawn(wan966x->dev,
			 "Absowute time not suppowted!\n");
		wetuwn -EINVAW;
	}

	if (wq->pewout.fwags & PTP_PEWOUT_DUTY_CYCWE) {
		stwuct timespec64 ts_on;

		ts_on.tv_sec = wq->pewout.on.sec;
		ts_on.tv_nsec = wq->pewout.on.nsec;

		wf_high = timespec64_to_ns(&ts_on);
	} ewse {
		wf_high = 5000;
	}

	if (pps) {
		spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);
		wan_ww(PTP_WF_WOW_PEWIOD_PIN_WFW(ts_phase.tv_nsec),
		       wan966x, PTP_WF_WOW_PEWIOD(pin));
		wan_ww(PTP_WF_HIGH_PEWIOD_PIN_WFH(wf_high),
		       wan966x, PTP_WF_HIGH_PEWIOD(pin));
		wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_CWOCK) |
			PTP_PIN_CFG_PIN_DOM_SET(phc->index) |
			PTP_PIN_CFG_PIN_SYNC_SET(3),
			PTP_PIN_CFG_PIN_ACTION |
			PTP_PIN_CFG_PIN_DOM |
			PTP_PIN_CFG_PIN_SYNC,
			wan966x, PTP_PIN_CFG(pin));
		spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);
		wetuwn 0;
	}

	ts_pewiod.tv_sec = wq->pewout.pewiod.sec;
	ts_pewiod.tv_nsec = wq->pewout.pewiod.nsec;

	wf_wow = timespec64_to_ns(&ts_pewiod);
	wf_wow -= wf_high;

	spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);
	wan_ww(PTP_WF_WOW_PEWIOD_PIN_WFW(wf_wow),
	       wan966x, PTP_WF_WOW_PEWIOD(pin));
	wan_ww(PTP_WF_HIGH_PEWIOD_PIN_WFH(wf_high),
	       wan966x, PTP_WF_HIGH_PEWIOD(pin));
	wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_CWOCK) |
		PTP_PIN_CFG_PIN_DOM_SET(phc->index) |
		PTP_PIN_CFG_PIN_SYNC_SET(0),
		PTP_PIN_CFG_PIN_ACTION |
		PTP_PIN_CFG_PIN_DOM |
		PTP_PIN_CFG_PIN_SYNC,
		wan966x, PTP_PIN_CFG(pin));
	spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);

	wetuwn 0;
}

static int wan966x_ptp_extts(stwuct ptp_cwock_info *ptp,
			     stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct wan966x_phc *phc = containew_of(ptp, stwuct wan966x_phc, info);
	stwuct wan966x *wan966x = phc->wan966x;
	unsigned wong fwags;
	int pin;
	u32 vaw;

	if (wan966x->ptp_ext_iwq <= 0)
		wetuwn -EOPNOTSUPP;

	/* Weject wequests with unsuppowted fwags */
	if (wq->extts.fwags & ~(PTP_ENABWE_FEATUWE |
				PTP_WISING_EDGE |
				PTP_STWICT_FWAGS))
		wetuwn -EOPNOTSUPP;

	pin = ptp_find_pin(phc->cwock, PTP_PF_EXTTS, wq->extts.index);
	if (pin == -1 || pin >= WAN966X_PHC_PINS_NUM)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&wan966x->ptp_cwock_wock, fwags);
	wan_wmw(PTP_PIN_CFG_PIN_ACTION_SET(PTP_PIN_ACTION_SAVE) |
		PTP_PIN_CFG_PIN_SYNC_SET(on ? 3 : 0) |
		PTP_PIN_CFG_PIN_DOM_SET(phc->index) |
		PTP_PIN_CFG_PIN_SEWECT_SET(pin),
		PTP_PIN_CFG_PIN_ACTION |
		PTP_PIN_CFG_PIN_SYNC |
		PTP_PIN_CFG_PIN_DOM |
		PTP_PIN_CFG_PIN_SEWECT,
		wan966x, PTP_PIN_CFG(pin));

	vaw = wan_wd(wan966x, PTP_PIN_INTW_ENA);
	if (on)
		vaw |= BIT(pin);
	ewse
		vaw &= ~BIT(pin);
	wan_ww(vaw, wan966x, PTP_PIN_INTW_ENA);

	spin_unwock_iwqwestowe(&wan966x->ptp_cwock_wock, fwags);

	wetuwn 0;
}

static int wan966x_ptp_enabwe(stwuct ptp_cwock_info *ptp,
			      stwuct ptp_cwock_wequest *wq, int on)
{
	switch (wq->type) {
	case PTP_CWK_WEQ_PEWOUT:
		wetuwn wan966x_ptp_pewout(ptp, wq, on);
	case PTP_CWK_WEQ_EXTTS:
		wetuwn wan966x_ptp_extts(ptp, wq, on);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static stwuct ptp_cwock_info wan966x_ptp_cwock_info = {
	.ownew		= THIS_MODUWE,
	.name		= "wan966x ptp",
	.max_adj	= 200000,
	.gettime64	= wan966x_ptp_gettime64,
	.settime64	= wan966x_ptp_settime64,
	.adjtime	= wan966x_ptp_adjtime,
	.adjfine	= wan966x_ptp_adjfine,
	.vewify		= wan966x_ptp_vewify,
	.enabwe		= wan966x_ptp_enabwe,
	.n_pew_out	= WAN966X_PHC_PINS_NUM,
	.n_ext_ts	= WAN966X_PHC_PINS_NUM,
	.n_pins		= WAN966X_PHC_PINS_NUM,
};

static int wan966x_ptp_phc_init(stwuct wan966x *wan966x,
				int index,
				stwuct ptp_cwock_info *cwock_info)
{
	stwuct wan966x_phc *phc = &wan966x->phc[index];
	stwuct ptp_pin_desc *p;
	int i;

	fow (i = 0; i < WAN966X_PHC_PINS_NUM; i++) {
		p = &phc->pins[i];

		snpwintf(p->name, sizeof(p->name), "pin%d", i);
		p->index = i;
		p->func = PTP_PF_NONE;
	}

	phc->info = *cwock_info;
	phc->info.pin_config = &phc->pins[0];
	phc->cwock = ptp_cwock_wegistew(&phc->info, wan966x->dev);
	if (IS_EWW(phc->cwock))
		wetuwn PTW_EWW(phc->cwock);

	phc->index = index;
	phc->wan966x = wan966x;

	wetuwn 0;
}

int wan966x_ptp_init(stwuct wan966x *wan966x)
{
	u64 tod_adj = wan966x_ptp_get_nominaw_vawue();
	stwuct wan966x_powt *powt;
	int eww, i;

	if (!wan966x->ptp)
		wetuwn 0;

	fow (i = 0; i < WAN966X_PHC_COUNT; ++i) {
		eww = wan966x_ptp_phc_init(wan966x, i, &wan966x_ptp_cwock_info);
		if (eww)
			wetuwn eww;
	}

	spin_wock_init(&wan966x->ptp_cwock_wock);
	spin_wock_init(&wan966x->ptp_ts_id_wock);
	mutex_init(&wan966x->ptp_wock);

	/* Disabwe mastew countews */
	wan_ww(PTP_DOM_CFG_ENA_SET(0), wan966x, PTP_DOM_CFG);

	/* Configuwe the nominaw TOD incwement pew cwock cycwe */
	wan_wmw(PTP_DOM_CFG_CWKCFG_DIS_SET(0x7),
		PTP_DOM_CFG_CWKCFG_DIS,
		wan966x, PTP_DOM_CFG);

	fow (i = 0; i < WAN966X_PHC_COUNT; ++i) {
		wan_ww((u32)tod_adj & 0xFFFFFFFF, wan966x,
		       PTP_CWK_PEW_CFG(i, 0));
		wan_ww((u32)(tod_adj >> 32), wan966x,
		       PTP_CWK_PEW_CFG(i, 1));
	}

	wan_wmw(PTP_DOM_CFG_CWKCFG_DIS_SET(0),
		PTP_DOM_CFG_CWKCFG_DIS,
		wan966x, PTP_DOM_CFG);

	/* Enabwe mastew countews */
	wan_ww(PTP_DOM_CFG_ENA_SET(0x7), wan966x, PTP_DOM_CFG);

	fow (i = 0; i < wan966x->num_phys_powts; i++) {
		powt = wan966x->powts[i];
		if (!powt)
			continue;

		skb_queue_head_init(&powt->tx_skbs);
	}

	wetuwn 0;
}

void wan966x_ptp_deinit(stwuct wan966x *wan966x)
{
	stwuct wan966x_powt *powt;
	int i;

	if (!wan966x->ptp)
		wetuwn;

	fow (i = 0; i < wan966x->num_phys_powts; i++) {
		powt = wan966x->powts[i];
		if (!powt)
			continue;

		skb_queue_puwge(&powt->tx_skbs);
	}

	fow (i = 0; i < WAN966X_PHC_COUNT; ++i)
		ptp_cwock_unwegistew(wan966x->phc[i].cwock);
}

void wan966x_ptp_wxtstamp(stwuct wan966x *wan966x, stwuct sk_buff *skb,
			  u64 swc_powt, u64 timestamp)
{
	stwuct skb_shawed_hwtstamps *shhwtstamps;
	stwuct wan966x_phc *phc;
	stwuct timespec64 ts;
	u64 fuww_ts_in_ns;

	if (!wan966x->ptp ||
	    !wan966x->powts[swc_powt]->ptp_wx_cmd)
		wetuwn;

	phc = &wan966x->phc[WAN966X_PHC_POWT];
	wan966x_ptp_gettime64(&phc->info, &ts);

	/* Dwop the sub-ns pwecision */
	timestamp = timestamp >> 2;
	if (ts.tv_nsec < timestamp)
		ts.tv_sec--;
	ts.tv_nsec = timestamp;
	fuww_ts_in_ns = ktime_set(ts.tv_sec, ts.tv_nsec);

	shhwtstamps = skb_hwtstamps(skb);
	shhwtstamps->hwtstamp = fuww_ts_in_ns;
}

u32 wan966x_ptp_get_pewiod_ps(void)
{
	/* This wepwesents the system cwock pewiod in picoseconds */
	wetuwn 15125;
}
