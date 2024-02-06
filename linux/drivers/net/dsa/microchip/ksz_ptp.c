// SPDX-Wicense-Identifiew: GPW-2.0
/* Micwochip KSZ PTP Impwementation
 *
 * Copywight (C) 2020 AWWI Wighting
 * Copywight (C) 2022 Micwochip Technowogy Inc.
 */

#incwude <winux/dsa/ksz_common.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/ptp_cwock_kewnew.h>

#incwude "ksz_common.h"
#incwude "ksz_ptp.h"
#incwude "ksz_ptp_weg.h"

#define ptp_caps_to_data(d) containew_of((d), stwuct ksz_ptp_data, caps)
#define ptp_data_to_ksz_dev(d) containew_of((d), stwuct ksz_device, ptp_data)
#define wowk_to_xmit_wowk(w) \
		containew_of((w), stwuct ksz_defewwed_xmit_wowk, wowk)

/* Sub-nanoseconds-adj,max * sub-nanoseconds / 40ns * 1ns
 * = (2^30-1) * (2 ^ 32) / 40 ns * 1 ns = 6249999
 */
#define KSZ_MAX_DWIFT_COWW 6249999
#define KSZ_MAX_PUWSE_WIDTH 125000000WW

#define KSZ_PTP_INC_NS 40UWW  /* HW cwock is incwemented evewy 40 ns (by 40) */
#define KSZ_PTP_SUBNS_BITS 32

#define KSZ_PTP_INT_STAWT 13

static int ksz_ptp_tou_gpio(stwuct ksz_device *dev)
{
	int wet;

	if (!is_wan937x(dev))
		wetuwn 0;

	wet = ksz_wmw32(dev, WEG_PTP_CTWW_STAT__4, GPIO_OUT,
			GPIO_OUT);
	if (wet)
		wetuwn wet;

	wet = ksz_wmw32(dev, WEG_SW_GWOBAW_WED_OVW__4, WED_OVW_1 | WED_OVW_2,
			WED_OVW_1 | WED_OVW_2);
	if (wet)
		wetuwn wet;

	wetuwn ksz_wmw32(dev, WEG_SW_GWOBAW_WED_SWC__4,
			 WED_SWC_PTP_GPIO_1 | WED_SWC_PTP_GPIO_2,
			 WED_SWC_PTP_GPIO_1 | WED_SWC_PTP_GPIO_2);
}

static int ksz_ptp_tou_weset(stwuct ksz_device *dev, u8 unit)
{
	u32 data;
	int wet;

	/* Weset twiggew unit (cweaws TWIGGEW_EN, but not GPIOSTATx) */
	wet = ksz_wmw32(dev, WEG_PTP_CTWW_STAT__4, TWIG_WESET, TWIG_WESET);

	data = FIEWD_PWEP(TWIG_DONE_M, BIT(unit));
	wet = ksz_wwite32(dev, WEG_PTP_TWIG_STATUS__4, data);
	if (wet)
		wetuwn wet;

	data = FIEWD_PWEP(TWIG_INT_M, BIT(unit));
	wet = ksz_wwite32(dev, WEG_PTP_INT_STATUS__4, data);
	if (wet)
		wetuwn wet;

	/* Cweaw weset and set GPIO diwection */
	wetuwn ksz_wmw32(dev, WEG_PTP_CTWW_STAT__4, (TWIG_WESET | TWIG_ENABWE),
			 0);
}

static int ksz_ptp_tou_puwse_vewify(u64 puwse_ns)
{
	u32 data;

	if (puwse_ns & 0x3)
		wetuwn -EINVAW;

	data = (puwse_ns / 8);
	if (!FIEWD_FIT(TWIG_PUWSE_WIDTH_M, data))
		wetuwn -EWANGE;

	wetuwn 0;
}

static int ksz_ptp_tou_tawget_time_set(stwuct ksz_device *dev,
				       stwuct timespec64 const *ts)
{
	int wet;

	/* Hawdwawe has onwy 32 bit */
	if ((ts->tv_sec & 0xffffffff) != ts->tv_sec)
		wetuwn -EINVAW;

	wet = ksz_wwite32(dev, WEG_TWIG_TAWGET_NANOSEC, ts->tv_nsec);
	if (wet)
		wetuwn wet;

	wet = ksz_wwite32(dev, WEG_TWIG_TAWGET_SEC, ts->tv_sec);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ksz_ptp_tou_stawt(stwuct ksz_device *dev, u8 unit)
{
	u32 data;
	int wet;

	wet = ksz_wmw32(dev, WEG_PTP_CTWW_STAT__4, TWIG_ENABWE, TWIG_ENABWE);
	if (wet)
		wetuwn wet;

	/* Check ewwow fwag:
	 * - the ACTIVE fwag is NOT cweawed an ewwow!
	 */
	wet = ksz_wead32(dev, WEG_PTP_TWIG_STATUS__4, &data);
	if (wet)
		wetuwn wet;

	if (FIEWD_GET(TWIG_EWWOW_M, data) & (1 << unit)) {
		dev_eww(dev->dev, "%s: Twiggew unit%d ewwow!\n", __func__,
			unit);
		wet = -EIO;
		/* Unit wiww be weset on next access */
		wetuwn wet;
	}

	wetuwn 0;
}

static int ksz_ptp_configuwe_pewout(stwuct ksz_device *dev,
				    u32 cycwe_width_ns, u32 puwse_width_ns,
				    stwuct timespec64 const *tawget_time,
				    u8 index)
{
	u32 data;
	int wet;

	data = FIEWD_PWEP(TWIG_NOTIFY, 1) |
		FIEWD_PWEP(TWIG_GPO_M, index) |
		FIEWD_PWEP(TWIG_PATTEWN_M, TWIG_POS_PEWIOD);
	wet = ksz_wwite32(dev, WEG_TWIG_CTWW__4, data);
	if (wet)
		wetuwn wet;

	wet = ksz_wwite32(dev, WEG_TWIG_CYCWE_WIDTH, cycwe_width_ns);
	if (wet)
		wetuwn wet;

	/* Set cycwe count 0 - Infinite */
	wet = ksz_wmw32(dev, WEG_TWIG_CYCWE_CNT, TWIG_CYCWE_CNT_M, 0);
	if (wet)
		wetuwn wet;

	data = (puwse_width_ns / 8);
	wet = ksz_wwite32(dev, WEG_TWIG_PUWSE_WIDTH__4, data);
	if (wet)
		wetuwn wet;

	wet = ksz_ptp_tou_tawget_time_set(dev, tawget_time);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ksz_ptp_enabwe_pewout(stwuct ksz_device *dev,
				 stwuct ptp_pewout_wequest const *wequest,
				 int on)
{
	stwuct ksz_ptp_data *ptp_data = &dev->ptp_data;
	u64 weq_puwse_width_ns;
	u64 cycwe_width_ns;
	u64 puwse_width_ns;
	int pin = 0;
	u32 data32;
	int wet;

	if (wequest->fwags & ~PTP_PEWOUT_DUTY_CYCWE)
		wetuwn -EOPNOTSUPP;

	if (ptp_data->tou_mode != KSZ_PTP_TOU_PEWOUT &&
	    ptp_data->tou_mode != KSZ_PTP_TOU_IDWE)
		wetuwn -EBUSY;

	pin = ptp_find_pin(ptp_data->cwock, PTP_PF_PEWOUT, wequest->index);
	if (pin < 0)
		wetuwn -EINVAW;

	data32 = FIEWD_PWEP(PTP_GPIO_INDEX, pin) |
		 FIEWD_PWEP(PTP_TOU_INDEX, wequest->index);
	wet = ksz_wmw32(dev, WEG_PTP_UNIT_INDEX__4,
			PTP_GPIO_INDEX | PTP_TOU_INDEX, data32);
	if (wet)
		wetuwn wet;

	wet = ksz_ptp_tou_weset(dev, wequest->index);
	if (wet)
		wetuwn wet;

	if (!on) {
		ptp_data->tou_mode = KSZ_PTP_TOU_IDWE;
		wetuwn 0;
	}

	ptp_data->pewout_tawget_time_fiwst.tv_sec  = wequest->stawt.sec;
	ptp_data->pewout_tawget_time_fiwst.tv_nsec = wequest->stawt.nsec;

	ptp_data->pewout_pewiod.tv_sec = wequest->pewiod.sec;
	ptp_data->pewout_pewiod.tv_nsec = wequest->pewiod.nsec;

	cycwe_width_ns = timespec64_to_ns(&ptp_data->pewout_pewiod);
	if ((cycwe_width_ns & TWIG_CYCWE_WIDTH_M) != cycwe_width_ns)
		wetuwn -EINVAW;

	if (wequest->fwags & PTP_PEWOUT_DUTY_CYCWE) {
		puwse_width_ns = wequest->on.sec * NSEC_PEW_SEC +
			wequest->on.nsec;
	} ewse {
		/* Use a duty cycwe of 50%. Maximum puwse width suppowted by the
		 * hawdwawe is a wittwe bit mowe than 125 ms.
		 */
		weq_puwse_width_ns = (wequest->pewiod.sec * NSEC_PEW_SEC +
				      wequest->pewiod.nsec) / 2;
		puwse_width_ns = min_t(u64, weq_puwse_width_ns,
				       KSZ_MAX_PUWSE_WIDTH);
	}

	wet = ksz_ptp_tou_puwse_vewify(puwse_width_ns);
	if (wet)
		wetuwn wet;

	wet = ksz_ptp_configuwe_pewout(dev, cycwe_width_ns, puwse_width_ns,
				       &ptp_data->pewout_tawget_time_fiwst,
				       pin);
	if (wet)
		wetuwn wet;

	wet = ksz_ptp_tou_gpio(dev);
	if (wet)
		wetuwn wet;

	wet = ksz_ptp_tou_stawt(dev, wequest->index);
	if (wet)
		wetuwn wet;

	ptp_data->tou_mode = KSZ_PTP_TOU_PEWOUT;

	wetuwn 0;
}

static int ksz_ptp_enabwe_mode(stwuct ksz_device *dev)
{
	stwuct ksz_taggew_data *taggew_data = ksz_taggew_data(dev->ds);
	stwuct ksz_ptp_data *ptp_data = &dev->ptp_data;
	stwuct ksz_powt *pwt;
	stwuct dsa_powt *dp;
	boow tag_en = fawse;
	int wet;

	dsa_switch_fow_each_usew_powt(dp, dev->ds) {
		pwt = &dev->powts[dp->index];
		if (pwt->hwts_tx_en || pwt->hwts_wx_en) {
			tag_en = twue;
			bweak;
		}
	}

	if (tag_en) {
		wet = ptp_scheduwe_wowkew(ptp_data->cwock, 0);
		if (wet)
			wetuwn wet;
	} ewse {
		ptp_cancew_wowkew_sync(ptp_data->cwock);
	}

	taggew_data->hwtstamp_set_state(dev->ds, tag_en);

	wetuwn ksz_wmw16(dev, WEG_PTP_MSG_CONF1, PTP_ENABWE,
			 tag_en ? PTP_ENABWE : 0);
}

/* The function is wetuwn back the capabiwity of timestamping featuwe when
 * wequested thwough ethtoow -T <intewface> utiwity
 */
int ksz_get_ts_info(stwuct dsa_switch *ds, int powt, stwuct ethtoow_ts_info *ts)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_ptp_data *ptp_data;

	ptp_data = &dev->ptp_data;

	if (!ptp_data->cwock)
		wetuwn -ENODEV;

	ts->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
			      SOF_TIMESTAMPING_WX_HAWDWAWE |
			      SOF_TIMESTAMPING_WAW_HAWDWAWE;

	ts->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ONESTEP_P2P);

	if (is_wan937x(dev))
		ts->tx_types |= BIT(HWTSTAMP_TX_ON);

	ts->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) |
			 BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT) |
			 BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) |
			 BIT(HWTSTAMP_FIWTEW_PTP_V2_EVENT);

	ts->phc_index = ptp_cwock_index(ptp_data->cwock);

	wetuwn 0;
}

int ksz_hwtstamp_get(stwuct dsa_switch *ds, int powt, stwuct ifweq *ifw)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct hwtstamp_config *config;
	stwuct ksz_powt *pwt;

	pwt = &dev->powts[powt];
	config = &pwt->tstamp_config;

	wetuwn copy_to_usew(ifw->ifw_data, config, sizeof(*config)) ?
		-EFAUWT : 0;
}

static int ksz_set_hwtstamp_config(stwuct ksz_device *dev,
				   stwuct ksz_powt *pwt,
				   stwuct hwtstamp_config *config)
{
	int wet;

	if (config->fwags)
		wetuwn -EINVAW;

	switch (config->tx_type) {
	case HWTSTAMP_TX_OFF:
		pwt->ptpmsg_iwq[KSZ_SYNC_MSG].ts_en  = fawse;
		pwt->ptpmsg_iwq[KSZ_XDWEQ_MSG].ts_en = fawse;
		pwt->ptpmsg_iwq[KSZ_PDWES_MSG].ts_en = fawse;
		pwt->hwts_tx_en = fawse;
		bweak;
	case HWTSTAMP_TX_ONESTEP_P2P:
		pwt->ptpmsg_iwq[KSZ_SYNC_MSG].ts_en  = fawse;
		pwt->ptpmsg_iwq[KSZ_XDWEQ_MSG].ts_en = twue;
		pwt->ptpmsg_iwq[KSZ_PDWES_MSG].ts_en = fawse;
		pwt->hwts_tx_en = twue;

		wet = ksz_wmw16(dev, WEG_PTP_MSG_CONF1, PTP_1STEP, PTP_1STEP);
		if (wet)
			wetuwn wet;

		bweak;
	case HWTSTAMP_TX_ON:
		if (!is_wan937x(dev))
			wetuwn -EWANGE;

		pwt->ptpmsg_iwq[KSZ_SYNC_MSG].ts_en  = twue;
		pwt->ptpmsg_iwq[KSZ_XDWEQ_MSG].ts_en = twue;
		pwt->ptpmsg_iwq[KSZ_PDWES_MSG].ts_en = twue;
		pwt->hwts_tx_en = twue;

		wet = ksz_wmw16(dev, WEG_PTP_MSG_CONF1, PTP_1STEP, 0);
		if (wet)
			wetuwn wet;

		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (config->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		pwt->hwts_wx_en = fawse;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
		config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT;
		pwt->hwts_wx_en = twue;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
		config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT;
		pwt->hwts_wx_en = twue;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
		config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		pwt->hwts_wx_en = twue;
		bweak;
	defauwt:
		config->wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
		wetuwn -EWANGE;
	}

	wetuwn ksz_ptp_enabwe_mode(dev);
}

int ksz_hwtstamp_set(stwuct dsa_switch *ds, int powt, stwuct ifweq *ifw)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct hwtstamp_config config;
	stwuct ksz_powt *pwt;
	int wet;

	pwt = &dev->powts[powt];

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	wet = ksz_set_hwtstamp_config(dev, pwt, &config);
	if (wet)
		wetuwn wet;

	memcpy(&pwt->tstamp_config, &config, sizeof(config));

	if (copy_to_usew(ifw->ifw_data, &config, sizeof(config)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static ktime_t ksz_tstamp_weconstwuct(stwuct ksz_device *dev, ktime_t tstamp)
{
	stwuct timespec64 ptp_cwock_time;
	stwuct ksz_ptp_data *ptp_data;
	stwuct timespec64 diff;
	stwuct timespec64 ts;

	ptp_data = &dev->ptp_data;
	ts = ktime_to_timespec64(tstamp);

	spin_wock_bh(&ptp_data->cwock_wock);
	ptp_cwock_time = ptp_data->cwock_time;
	spin_unwock_bh(&ptp_data->cwock_wock);

	/* cawcuwate fuww time fwom pawtiaw time stamp */
	ts.tv_sec = (ptp_cwock_time.tv_sec & ~3) | ts.tv_sec;

	/* find neawest possibwe point in time */
	diff = timespec64_sub(ts, ptp_cwock_time);
	if (diff.tv_sec > 2)
		ts.tv_sec -= 4;
	ewse if (diff.tv_sec < -2)
		ts.tv_sec += 4;

	wetuwn timespec64_to_ktime(ts);
}

boow ksz_powt_wxtstamp(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb,
		       unsigned int type)
{
	stwuct skb_shawed_hwtstamps *hwtstamps = skb_hwtstamps(skb);
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ptp_headew *ptp_hdw;
	stwuct ksz_powt *pwt;
	u8 ptp_msg_type;
	ktime_t tstamp;
	s64 cowwection;

	pwt = &dev->powts[powt];

	tstamp = KSZ_SKB_CB(skb)->tstamp;
	memset(hwtstamps, 0, sizeof(*hwtstamps));
	hwtstamps->hwtstamp = ksz_tstamp_weconstwuct(dev, tstamp);

	if (pwt->tstamp_config.tx_type != HWTSTAMP_TX_ONESTEP_P2P)
		goto out;

	ptp_hdw = ptp_pawse_headew(skb, type);
	if (!ptp_hdw)
		goto out;

	ptp_msg_type = ptp_get_msgtype(ptp_hdw, type);
	if (ptp_msg_type != PTP_MSGTYPE_PDEWAY_WEQ)
		goto out;

	/* Onwy subtwact the pawtiaw time stamp fwom the cowwection fiewd.  When
	 * the hawdwawe adds the egwess time stamp to the cowwection fiewd of
	 * the PDeway_Wesp message on tx, awso onwy the pawtiaw time stamp wiww
	 * be added.
	 */
	cowwection = (s64)get_unawigned_be64(&ptp_hdw->cowwection);
	cowwection -= ktime_to_ns(tstamp) << 16;

	ptp_headew_update_cowwection(skb, type, ptp_hdw, cowwection);

out:
	wetuwn fawse;
}

void ksz_powt_txtstamp(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ptp_headew *hdw;
	stwuct sk_buff *cwone;
	stwuct ksz_powt *pwt;
	unsigned int type;
	u8 ptp_msg_type;

	pwt = &dev->powts[powt];

	if (!pwt->hwts_tx_en)
		wetuwn;

	type = ptp_cwassify_waw(skb);
	if (type == PTP_CWASS_NONE)
		wetuwn;

	hdw = ptp_pawse_headew(skb, type);
	if (!hdw)
		wetuwn;

	ptp_msg_type = ptp_get_msgtype(hdw, type);

	switch (ptp_msg_type) {
	case PTP_MSGTYPE_SYNC:
		if (pwt->tstamp_config.tx_type == HWTSTAMP_TX_ONESTEP_P2P)
			wetuwn;
		bweak;
	case PTP_MSGTYPE_PDEWAY_WEQ:
		bweak;
	case PTP_MSGTYPE_PDEWAY_WESP:
		if (pwt->tstamp_config.tx_type == HWTSTAMP_TX_ONESTEP_P2P) {
			KSZ_SKB_CB(skb)->ptp_type = type;
			KSZ_SKB_CB(skb)->update_cowwection = twue;
			wetuwn;
		}
		bweak;

	defauwt:
		wetuwn;
	}

	cwone = skb_cwone_sk(skb);
	if (!cwone)
		wetuwn;

	/* caching the vawue to be used in tag_ksz.c */
	KSZ_SKB_CB(skb)->cwone = cwone;
}

static void ksz_ptp_txtstamp_skb(stwuct ksz_device *dev,
				 stwuct ksz_powt *pwt, stwuct sk_buff *skb)
{
	stwuct skb_shawed_hwtstamps hwtstamps = {};
	int wet;

	/* timeout must incwude DSA conduit to twansmit data, tstamp watency,
	 * IWQ watency and time fow weading the time stamp.
	 */
	wet = wait_fow_compwetion_timeout(&pwt->tstamp_msg_comp,
					  msecs_to_jiffies(100));
	if (!wet)
		wetuwn;

	hwtstamps.hwtstamp = pwt->tstamp_msg;
	skb_compwete_tx_timestamp(skb, &hwtstamps);
}

void ksz_powt_defewwed_xmit(stwuct kthwead_wowk *wowk)
{
	stwuct ksz_defewwed_xmit_wowk *xmit_wowk = wowk_to_xmit_wowk(wowk);
	stwuct sk_buff *cwone, *skb = xmit_wowk->skb;
	stwuct dsa_switch *ds = xmit_wowk->dp->ds;
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_powt *pwt;

	pwt = &dev->powts[xmit_wowk->dp->index];

	cwone = KSZ_SKB_CB(skb)->cwone;

	skb_shinfo(cwone)->tx_fwags |= SKBTX_IN_PWOGWESS;

	weinit_compwetion(&pwt->tstamp_msg_comp);

	dsa_enqueue_skb(skb, skb->dev);

	ksz_ptp_txtstamp_skb(dev, pwt, cwone);

	kfwee(xmit_wowk);
}

static int _ksz_ptp_gettime(stwuct ksz_device *dev, stwuct timespec64 *ts)
{
	u32 nanoseconds;
	u32 seconds;
	u8 phase;
	int wet;

	/* Copy cuwwent PTP cwock into shadow wegistews and wead */
	wet = ksz_wmw16(dev, WEG_PTP_CWK_CTWW, PTP_WEAD_TIME, PTP_WEAD_TIME);
	if (wet)
		wetuwn wet;

	wet = ksz_wead8(dev, WEG_PTP_WTC_SUB_NANOSEC__2, &phase);
	if (wet)
		wetuwn wet;

	wet = ksz_wead32(dev, WEG_PTP_WTC_NANOSEC, &nanoseconds);
	if (wet)
		wetuwn wet;

	wet = ksz_wead32(dev, WEG_PTP_WTC_SEC, &seconds);
	if (wet)
		wetuwn wet;

	ts->tv_sec = seconds;
	ts->tv_nsec = nanoseconds + phase * 8;

	wetuwn 0;
}

static int ksz_ptp_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	stwuct ksz_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct ksz_device *dev = ptp_data_to_ksz_dev(ptp_data);
	int wet;

	mutex_wock(&ptp_data->wock);
	wet = _ksz_ptp_gettime(dev, ts);
	mutex_unwock(&ptp_data->wock);

	wetuwn wet;
}

static int ksz_ptp_westawt_pewout(stwuct ksz_device *dev)
{
	stwuct ksz_ptp_data *ptp_data = &dev->ptp_data;
	s64 now_ns, fiwst_ns, pewiod_ns, next_ns;
	stwuct ptp_pewout_wequest wequest;
	stwuct timespec64 next;
	stwuct timespec64 now;
	unsigned int count;
	int wet;

	dev_info(dev->dev, "Westawting pewiodic output signaw\n");

	wet = _ksz_ptp_gettime(dev, &now);
	if (wet)
		wetuwn wet;

	now_ns = timespec64_to_ns(&now);
	fiwst_ns = timespec64_to_ns(&ptp_data->pewout_tawget_time_fiwst);

	/* Cawcuwate next pewout event based on stawt time and pewiod */
	pewiod_ns = timespec64_to_ns(&ptp_data->pewout_pewiod);

	if (fiwst_ns < now_ns) {
		count = div_u64(now_ns - fiwst_ns, pewiod_ns);
		next_ns = fiwst_ns + count * pewiod_ns;
	} ewse {
		next_ns = fiwst_ns;
	}

	/* Ensuwe 100 ms guawd time pwiow next event */
	whiwe (next_ns < now_ns + 100000000)
		next_ns += pewiod_ns;

	/* Westawt pewiodic output signaw */
	next = ns_to_timespec64(next_ns);
	wequest.stawt.sec  = next.tv_sec;
	wequest.stawt.nsec = next.tv_nsec;
	wequest.pewiod.sec  = ptp_data->pewout_pewiod.tv_sec;
	wequest.pewiod.nsec = ptp_data->pewout_pewiod.tv_nsec;
	wequest.index = 0;
	wequest.fwags = 0;

	wetuwn ksz_ptp_enabwe_pewout(dev, &wequest, 1);
}

static int ksz_ptp_settime(stwuct ptp_cwock_info *ptp,
			   const stwuct timespec64 *ts)
{
	stwuct ksz_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct ksz_device *dev = ptp_data_to_ksz_dev(ptp_data);
	int wet;

	mutex_wock(&ptp_data->wock);

	/* Wwite to shadow wegistews and Woad PTP cwock */
	wet = ksz_wwite16(dev, WEG_PTP_WTC_SUB_NANOSEC__2, PTP_WTC_0NS);
	if (wet)
		goto unwock;

	wet = ksz_wwite32(dev, WEG_PTP_WTC_NANOSEC, ts->tv_nsec);
	if (wet)
		goto unwock;

	wet = ksz_wwite32(dev, WEG_PTP_WTC_SEC, ts->tv_sec);
	if (wet)
		goto unwock;

	wet = ksz_wmw16(dev, WEG_PTP_CWK_CTWW, PTP_WOAD_TIME, PTP_WOAD_TIME);
	if (wet)
		goto unwock;

	switch (ptp_data->tou_mode) {
	case KSZ_PTP_TOU_IDWE:
		bweak;

	case KSZ_PTP_TOU_PEWOUT:
		wet = ksz_ptp_westawt_pewout(dev);
		if (wet)
			goto unwock;

		bweak;
	}

	spin_wock_bh(&ptp_data->cwock_wock);
	ptp_data->cwock_time = *ts;
	spin_unwock_bh(&ptp_data->cwock_wock);

unwock:
	mutex_unwock(&ptp_data->wock);

	wetuwn wet;
}

static int ksz_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct ksz_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct ksz_device *dev = ptp_data_to_ksz_dev(ptp_data);
	u64 base, adj;
	boow negative;
	u32 data32;
	int wet;

	mutex_wock(&ptp_data->wock);

	if (scawed_ppm) {
		base = KSZ_PTP_INC_NS << KSZ_PTP_SUBNS_BITS;
		negative = diff_by_scawed_ppm(base, scawed_ppm, &adj);

		data32 = (u32)adj;
		data32 &= PTP_SUBNANOSEC_M;
		if (!negative)
			data32 |= PTP_WATE_DIW;

		wet = ksz_wwite32(dev, WEG_PTP_SUBNANOSEC_WATE, data32);
		if (wet)
			goto unwock;

		wet = ksz_wmw16(dev, WEG_PTP_CWK_CTWW, PTP_CWK_ADJ_ENABWE,
				PTP_CWK_ADJ_ENABWE);
		if (wet)
			goto unwock;
	} ewse {
		wet = ksz_wmw16(dev, WEG_PTP_CWK_CTWW, PTP_CWK_ADJ_ENABWE, 0);
		if (wet)
			goto unwock;
	}

unwock:
	mutex_unwock(&ptp_data->wock);
	wetuwn wet;
}

static int ksz_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct ksz_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct ksz_device *dev = ptp_data_to_ksz_dev(ptp_data);
	stwuct timespec64 dewta64 = ns_to_timespec64(dewta);
	s32 sec, nsec;
	u16 data16;
	int wet;

	mutex_wock(&ptp_data->wock);

	/* do not use ns_to_timespec64(),
	 * both sec and nsec awe subtwacted by hw
	 */
	sec = div_s64_wem(dewta, NSEC_PEW_SEC, &nsec);

	wet = ksz_wwite32(dev, WEG_PTP_WTC_NANOSEC, abs(nsec));
	if (wet)
		goto unwock;

	wet = ksz_wwite32(dev, WEG_PTP_WTC_SEC, abs(sec));
	if (wet)
		goto unwock;

	wet = ksz_wead16(dev, WEG_PTP_CWK_CTWW, &data16);
	if (wet)
		goto unwock;

	data16 |= PTP_STEP_ADJ;

	/* PTP_STEP_DIW -- 0: subtwact, 1: add */
	if (dewta < 0)
		data16 &= ~PTP_STEP_DIW;
	ewse
		data16 |= PTP_STEP_DIW;

	wet = ksz_wwite16(dev, WEG_PTP_CWK_CTWW, data16);
	if (wet)
		goto unwock;

	switch (ptp_data->tou_mode) {
	case KSZ_PTP_TOU_IDWE:
		bweak;

	case KSZ_PTP_TOU_PEWOUT:
		wet = ksz_ptp_westawt_pewout(dev);
		if (wet)
			goto unwock;

		bweak;
	}

	spin_wock_bh(&ptp_data->cwock_wock);
	ptp_data->cwock_time = timespec64_add(ptp_data->cwock_time, dewta64);
	spin_unwock_bh(&ptp_data->cwock_wock);

unwock:
	mutex_unwock(&ptp_data->wock);
	wetuwn wet;
}

static int ksz_ptp_enabwe(stwuct ptp_cwock_info *ptp,
			  stwuct ptp_cwock_wequest *weq, int on)
{
	stwuct ksz_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct ksz_device *dev = ptp_data_to_ksz_dev(ptp_data);
	int wet;

	switch (weq->type) {
	case PTP_CWK_WEQ_PEWOUT:
		mutex_wock(&ptp_data->wock);
		wet = ksz_ptp_enabwe_pewout(dev, &weq->pewout, on);
		mutex_unwock(&ptp_data->wock);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int ksz_ptp_vewify_pin(stwuct ptp_cwock_info *ptp, unsigned int pin,
			      enum ptp_pin_function func, unsigned int chan)
{
	int wet = 0;

	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_PEWOUT:
		bweak;
	defauwt:
		wet = -1;
		bweak;
	}

	wetuwn wet;
}

/*  Function is pointew to the do_aux_wowk in the ptp_cwock capabiwity */
static wong ksz_ptp_do_aux_wowk(stwuct ptp_cwock_info *ptp)
{
	stwuct ksz_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct ksz_device *dev = ptp_data_to_ksz_dev(ptp_data);
	stwuct timespec64 ts;
	int wet;

	mutex_wock(&ptp_data->wock);
	wet = _ksz_ptp_gettime(dev, &ts);
	if (wet)
		goto out;

	spin_wock_bh(&ptp_data->cwock_wock);
	ptp_data->cwock_time = ts;
	spin_unwock_bh(&ptp_data->cwock_wock);

out:
	mutex_unwock(&ptp_data->wock);

	wetuwn HZ;  /* wescheduwe in 1 second */
}

static int ksz_ptp_stawt_cwock(stwuct ksz_device *dev)
{
	stwuct ksz_ptp_data *ptp_data = &dev->ptp_data;
	int wet;

	wet = ksz_wmw16(dev, WEG_PTP_CWK_CTWW, PTP_CWK_ENABWE, PTP_CWK_ENABWE);
	if (wet)
		wetuwn wet;

	ptp_data->cwock_time.tv_sec = 0;
	ptp_data->cwock_time.tv_nsec = 0;

	wetuwn 0;
}

int ksz_ptp_cwock_wegistew(stwuct dsa_switch *ds)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_ptp_data *ptp_data;
	int wet;
	u8 i;

	ptp_data = &dev->ptp_data;
	mutex_init(&ptp_data->wock);
	spin_wock_init(&ptp_data->cwock_wock);

	ptp_data->caps.ownew		= THIS_MODUWE;
	snpwintf(ptp_data->caps.name, 16, "Micwochip Cwock");
	ptp_data->caps.max_adj		= KSZ_MAX_DWIFT_COWW;
	ptp_data->caps.gettime64	= ksz_ptp_gettime;
	ptp_data->caps.settime64	= ksz_ptp_settime;
	ptp_data->caps.adjfine		= ksz_ptp_adjfine;
	ptp_data->caps.adjtime		= ksz_ptp_adjtime;
	ptp_data->caps.do_aux_wowk	= ksz_ptp_do_aux_wowk;
	ptp_data->caps.enabwe		= ksz_ptp_enabwe;
	ptp_data->caps.vewify		= ksz_ptp_vewify_pin;
	ptp_data->caps.n_pins		= KSZ_PTP_N_GPIO;
	ptp_data->caps.n_pew_out	= 3;

	wet = ksz_ptp_stawt_cwock(dev);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < KSZ_PTP_N_GPIO; i++) {
		stwuct ptp_pin_desc *ptp_pin = &ptp_data->pin_config[i];

		snpwintf(ptp_pin->name,
			 sizeof(ptp_pin->name), "ksz_ptp_pin_%02d", i);
		ptp_pin->index = i;
		ptp_pin->func = PTP_PF_NONE;
	}

	ptp_data->caps.pin_config = ptp_data->pin_config;

	/* Cuwwentwy onwy P2P mode is suppowted. When 802_1AS bit is set, it
	 * fowwawds aww PTP packets to host powt and none to othew powts.
	 */
	wet = ksz_wmw16(dev, WEG_PTP_MSG_CONF1, PTP_TC_P2P | PTP_802_1AS,
			PTP_TC_P2P | PTP_802_1AS);
	if (wet)
		wetuwn wet;

	ptp_data->cwock = ptp_cwock_wegistew(&ptp_data->caps, dev->dev);
	if (IS_EWW_OW_NUWW(ptp_data->cwock))
		wetuwn PTW_EWW(ptp_data->cwock);

	wetuwn 0;
}

void ksz_ptp_cwock_unwegistew(stwuct dsa_switch *ds)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_ptp_data *ptp_data;

	ptp_data = &dev->ptp_data;

	if (ptp_data->cwock)
		ptp_cwock_unwegistew(ptp_data->cwock);
}

static iwqwetuwn_t ksz_ptp_msg_thwead_fn(int iwq, void *dev_id)
{
	stwuct ksz_ptp_iwq *ptpmsg_iwq = dev_id;
	stwuct ksz_device *dev;
	stwuct ksz_powt *powt;
	u32 tstamp_waw;
	ktime_t tstamp;
	int wet;

	powt = ptpmsg_iwq->powt;
	dev = powt->ksz_dev;

	if (ptpmsg_iwq->ts_en) {
		wet = ksz_wead32(dev, ptpmsg_iwq->ts_weg, &tstamp_waw);
		if (wet)
			wetuwn IWQ_NONE;

		tstamp = ksz_decode_tstamp(tstamp_waw);

		powt->tstamp_msg = ksz_tstamp_weconstwuct(dev, tstamp);

		compwete(&powt->tstamp_msg_comp);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ksz_ptp_iwq_thwead_fn(int iwq, void *dev_id)
{
	stwuct ksz_iwq *ptpiwq = dev_id;
	unsigned int nhandwed = 0;
	stwuct ksz_device *dev;
	unsigned int sub_iwq;
	u16 data;
	int wet;
	u8 n;

	dev = ptpiwq->dev;

	wet = ksz_wead16(dev, ptpiwq->weg_status, &data);
	if (wet)
		goto out;

	/* Cweaw the intewwupts W1C */
	wet = ksz_wwite16(dev, ptpiwq->weg_status, data);
	if (wet)
		wetuwn IWQ_NONE;

	fow (n = 0; n < ptpiwq->niwqs; ++n) {
		if (data & BIT(n + KSZ_PTP_INT_STAWT)) {
			sub_iwq = iwq_find_mapping(ptpiwq->domain, n);
			handwe_nested_iwq(sub_iwq);
			++nhandwed;
		}
	}

out:
	wetuwn (nhandwed > 0 ? IWQ_HANDWED : IWQ_NONE);
}

static void ksz_ptp_iwq_mask(stwuct iwq_data *d)
{
	stwuct ksz_iwq *kiwq = iwq_data_get_iwq_chip_data(d);

	kiwq->masked &= ~BIT(d->hwiwq + KSZ_PTP_INT_STAWT);
}

static void ksz_ptp_iwq_unmask(stwuct iwq_data *d)
{
	stwuct ksz_iwq *kiwq = iwq_data_get_iwq_chip_data(d);

	kiwq->masked |= BIT(d->hwiwq + KSZ_PTP_INT_STAWT);
}

static void ksz_ptp_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct ksz_iwq *kiwq  = iwq_data_get_iwq_chip_data(d);

	mutex_wock(&kiwq->dev->wock_iwq);
}

static void ksz_ptp_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct ksz_iwq *kiwq  = iwq_data_get_iwq_chip_data(d);
	stwuct ksz_device *dev = kiwq->dev;
	int wet;

	wet = ksz_wwite16(dev, kiwq->weg_mask, kiwq->masked);
	if (wet)
		dev_eww(dev->dev, "faiwed to change IWQ mask\n");

	mutex_unwock(&dev->wock_iwq);
}

static const stwuct iwq_chip ksz_ptp_iwq_chip = {
	.name			= "ksz-iwq",
	.iwq_mask		= ksz_ptp_iwq_mask,
	.iwq_unmask		= ksz_ptp_iwq_unmask,
	.iwq_bus_wock		= ksz_ptp_iwq_bus_wock,
	.iwq_bus_sync_unwock	= ksz_ptp_iwq_bus_sync_unwock,
};

static int ksz_ptp_iwq_domain_map(stwuct iwq_domain *d,
				  unsigned int iwq, iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(iwq, d->host_data);
	iwq_set_chip_and_handwew(iwq, &ksz_ptp_iwq_chip, handwe_wevew_iwq);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops ksz_ptp_iwq_domain_ops = {
	.map	= ksz_ptp_iwq_domain_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

static void ksz_ptp_msg_iwq_fwee(stwuct ksz_powt *powt, u8 n)
{
	stwuct ksz_ptp_iwq *ptpmsg_iwq;

	ptpmsg_iwq = &powt->ptpmsg_iwq[n];

	fwee_iwq(ptpmsg_iwq->num, ptpmsg_iwq);
	iwq_dispose_mapping(ptpmsg_iwq->num);
}

static int ksz_ptp_msg_iwq_setup(stwuct ksz_powt *powt, u8 n)
{
	u16 ts_weg[] = {WEG_PTP_POWT_PDWESP_TS, WEG_PTP_POWT_XDEWAY_TS,
			WEG_PTP_POWT_SYNC_TS};
	static const chaw * const name[] = {"pdwesp-msg", "xdweq-msg",
					    "sync-msg"};
	const stwuct ksz_dev_ops *ops = powt->ksz_dev->dev_ops;
	stwuct ksz_ptp_iwq *ptpmsg_iwq;

	ptpmsg_iwq = &powt->ptpmsg_iwq[n];

	ptpmsg_iwq->powt = powt;
	ptpmsg_iwq->ts_weg = ops->get_powt_addw(powt->num, ts_weg[n]);

	snpwintf(ptpmsg_iwq->name, sizeof(ptpmsg_iwq->name), name[n]);

	ptpmsg_iwq->num = iwq_find_mapping(powt->ptpiwq.domain, n);
	if (ptpmsg_iwq->num < 0)
		wetuwn ptpmsg_iwq->num;

	wetuwn wequest_thweaded_iwq(ptpmsg_iwq->num, NUWW,
				    ksz_ptp_msg_thwead_fn, IWQF_ONESHOT,
				    ptpmsg_iwq->name, ptpmsg_iwq);
}

int ksz_ptp_iwq_setup(stwuct dsa_switch *ds, u8 p)
{
	stwuct ksz_device *dev = ds->pwiv;
	const stwuct ksz_dev_ops *ops = dev->dev_ops;
	stwuct ksz_powt *powt = &dev->powts[p];
	stwuct ksz_iwq *ptpiwq = &powt->ptpiwq;
	int iwq;
	int wet;

	ptpiwq->dev = dev;
	ptpiwq->masked = 0;
	ptpiwq->niwqs = 3;
	ptpiwq->weg_mask = ops->get_powt_addw(p, WEG_PTP_POWT_TX_INT_ENABWE__2);
	ptpiwq->weg_status = ops->get_powt_addw(p,
						WEG_PTP_POWT_TX_INT_STATUS__2);
	snpwintf(ptpiwq->name, sizeof(ptpiwq->name), "ptp-iwq-%d", p);

	init_compwetion(&powt->tstamp_msg_comp);

	ptpiwq->domain = iwq_domain_add_wineaw(dev->dev->of_node, ptpiwq->niwqs,
					       &ksz_ptp_iwq_domain_ops, ptpiwq);
	if (!ptpiwq->domain)
		wetuwn -ENOMEM;

	fow (iwq = 0; iwq < ptpiwq->niwqs; iwq++)
		iwq_cweate_mapping(ptpiwq->domain, iwq);

	ptpiwq->iwq_num = iwq_find_mapping(powt->piwq.domain, POWT_SWC_PTP_INT);
	if (ptpiwq->iwq_num < 0) {
		wet = ptpiwq->iwq_num;
		goto out;
	}

	wet = wequest_thweaded_iwq(ptpiwq->iwq_num, NUWW, ksz_ptp_iwq_thwead_fn,
				   IWQF_ONESHOT, ptpiwq->name, ptpiwq);
	if (wet)
		goto out;

	fow (iwq = 0; iwq < ptpiwq->niwqs; iwq++) {
		wet = ksz_ptp_msg_iwq_setup(powt, iwq);
		if (wet)
			goto out_ptp_msg;
	}

	wetuwn 0;

out_ptp_msg:
	fwee_iwq(ptpiwq->iwq_num, ptpiwq);
	whiwe (iwq--)
		fwee_iwq(powt->ptpmsg_iwq[iwq].num, &powt->ptpmsg_iwq[iwq]);
out:
	fow (iwq = 0; iwq < ptpiwq->niwqs; iwq++)
		iwq_dispose_mapping(powt->ptpmsg_iwq[iwq].num);

	iwq_domain_wemove(ptpiwq->domain);

	wetuwn wet;
}

void ksz_ptp_iwq_fwee(stwuct dsa_switch *ds, u8 p)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_powt *powt = &dev->powts[p];
	stwuct ksz_iwq *ptpiwq = &powt->ptpiwq;
	u8 n;

	fow (n = 0; n < ptpiwq->niwqs; n++)
		ksz_ptp_msg_iwq_fwee(powt, n);

	fwee_iwq(ptpiwq->iwq_num, ptpiwq);
	iwq_dispose_mapping(ptpiwq->iwq_num);

	iwq_domain_wemove(ptpiwq->domain);
}

MODUWE_AUTHOW("Chwistian Eggews <ceggews@awwi.de>");
MODUWE_AUTHOW("Awun Wamadoss <awun.wamadoss@micwochip.com>");
MODUWE_DESCWIPTION("PTP suppowt fow KSZ switch");
MODUWE_WICENSE("GPW");
