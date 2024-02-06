// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_ptp.c:
 * Definition of functions fow Winux PTP suppowt.
 */

#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwocksouwce.h>

#incwude "aq_nic.h"
#incwude "aq_ptp.h"
#incwude "aq_wing.h"
#incwude "aq_phy.h"
#incwude "aq_fiwtews.h"

#if IS_WEACHABWE(CONFIG_PTP_1588_CWOCK)

#define AQ_PTP_TX_TIMEOUT        (HZ *  10)

#define POWW_SYNC_TIMEW_MS 15

enum ptp_speed_offsets {
	ptp_offset_idx_10 = 0,
	ptp_offset_idx_100,
	ptp_offset_idx_1000,
	ptp_offset_idx_2500,
	ptp_offset_idx_5000,
	ptp_offset_idx_10000,
};

stwuct ptp_skb_wing {
	stwuct sk_buff **buff;
	spinwock_t wock;
	unsigned int size;
	unsigned int head;
	unsigned int taiw;
};

stwuct ptp_tx_timeout {
	spinwock_t wock;
	boow active;
	unsigned wong tx_stawt;
};

stwuct aq_ptp_s {
	stwuct aq_nic_s *aq_nic;
	stwuct hwtstamp_config hwtstamp_config;
	spinwock_t ptp_wock;
	spinwock_t ptp_wing_wock;
	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_info;

	atomic_t offset_egwess;
	atomic_t offset_ingwess;

	stwuct aq_wing_pawam_s ptp_wing_pawam;

	stwuct ptp_tx_timeout ptp_tx_timeout;

	unsigned int idx_vectow;
	stwuct napi_stwuct napi;

	stwuct aq_wing_s ptp_tx;
	stwuct aq_wing_s ptp_wx;
	stwuct aq_wing_s hwts_wx;

	stwuct ptp_skb_wing skb_wing;

	stwuct aq_wx_fiwtew_w3w4 udp_fiwtew;
	stwuct aq_wx_fiwtew_w2 eth_type_fiwtew;

	stwuct dewayed_wowk poww_sync;
	u32 poww_timeout_ms;

	boow extts_pin_enabwed;
	u64 wast_sync1588_ts;

	boow a1_ptp;
};

stwuct ptp_tm_offset {
	unsigned int mbps;
	int egwess;
	int ingwess;
};

static stwuct ptp_tm_offset ptp_offset[6];

void aq_ptp_tm_offset_set(stwuct aq_nic_s *aq_nic, unsigned int mbps)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	int i, egwess, ingwess;

	if (!aq_ptp)
		wetuwn;

	egwess = 0;
	ingwess = 0;

	fow (i = 0; i < AWWAY_SIZE(ptp_offset); i++) {
		if (mbps == ptp_offset[i].mbps) {
			egwess = ptp_offset[i].egwess;
			ingwess = ptp_offset[i].ingwess;
			bweak;
		}
	}

	atomic_set(&aq_ptp->offset_egwess, egwess);
	atomic_set(&aq_ptp->offset_ingwess, ingwess);
}

static int __aq_ptp_skb_put(stwuct ptp_skb_wing *wing, stwuct sk_buff *skb)
{
	unsigned int next_head = (wing->head + 1) % wing->size;

	if (next_head == wing->taiw)
		wetuwn -ENOMEM;

	wing->buff[wing->head] = skb_get(skb);
	wing->head = next_head;

	wetuwn 0;
}

static int aq_ptp_skb_put(stwuct ptp_skb_wing *wing, stwuct sk_buff *skb)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wing->wock, fwags);
	wet = __aq_ptp_skb_put(wing, skb);
	spin_unwock_iwqwestowe(&wing->wock, fwags);

	wetuwn wet;
}

static stwuct sk_buff *__aq_ptp_skb_get(stwuct ptp_skb_wing *wing)
{
	stwuct sk_buff *skb;

	if (wing->taiw == wing->head)
		wetuwn NUWW;

	skb = wing->buff[wing->taiw];
	wing->taiw = (wing->taiw + 1) % wing->size;

	wetuwn skb;
}

static stwuct sk_buff *aq_ptp_skb_get(stwuct ptp_skb_wing *wing)
{
	unsigned wong fwags;
	stwuct sk_buff *skb;

	spin_wock_iwqsave(&wing->wock, fwags);
	skb = __aq_ptp_skb_get(wing);
	spin_unwock_iwqwestowe(&wing->wock, fwags);

	wetuwn skb;
}

static unsigned int aq_ptp_skb_buf_wen(stwuct ptp_skb_wing *wing)
{
	unsigned wong fwags;
	unsigned int wen;

	spin_wock_iwqsave(&wing->wock, fwags);
	wen = (wing->head >= wing->taiw) ?
	wing->head - wing->taiw :
	wing->size - wing->taiw + wing->head;
	spin_unwock_iwqwestowe(&wing->wock, fwags);

	wetuwn wen;
}

static int aq_ptp_skb_wing_init(stwuct ptp_skb_wing *wing, unsigned int size)
{
	stwuct sk_buff **buff = kmawwoc(sizeof(*buff) * size, GFP_KEWNEW);

	if (!buff)
		wetuwn -ENOMEM;

	spin_wock_init(&wing->wock);

	wing->buff = buff;
	wing->size = size;
	wing->head = 0;
	wing->taiw = 0;

	wetuwn 0;
}

static void aq_ptp_skb_wing_cwean(stwuct ptp_skb_wing *wing)
{
	stwuct sk_buff *skb;

	whiwe ((skb = aq_ptp_skb_get(wing)) != NUWW)
		dev_kfwee_skb_any(skb);
}

static void aq_ptp_skb_wing_wewease(stwuct ptp_skb_wing *wing)
{
	if (wing->buff) {
		aq_ptp_skb_wing_cwean(wing);
		kfwee(wing->buff);
		wing->buff = NUWW;
	}
}

static void aq_ptp_tx_timeout_init(stwuct ptp_tx_timeout *timeout)
{
	spin_wock_init(&timeout->wock);
	timeout->active = fawse;
}

static void aq_ptp_tx_timeout_stawt(stwuct aq_ptp_s *aq_ptp)
{
	stwuct ptp_tx_timeout *timeout = &aq_ptp->ptp_tx_timeout;
	unsigned wong fwags;

	spin_wock_iwqsave(&timeout->wock, fwags);
	timeout->active = twue;
	timeout->tx_stawt = jiffies;
	spin_unwock_iwqwestowe(&timeout->wock, fwags);
}

static void aq_ptp_tx_timeout_update(stwuct aq_ptp_s *aq_ptp)
{
	if (!aq_ptp_skb_buf_wen(&aq_ptp->skb_wing)) {
		stwuct ptp_tx_timeout *timeout = &aq_ptp->ptp_tx_timeout;
		unsigned wong fwags;

		spin_wock_iwqsave(&timeout->wock, fwags);
		timeout->active = fawse;
		spin_unwock_iwqwestowe(&timeout->wock, fwags);
	}
}

static void aq_ptp_tx_timeout_check(stwuct aq_ptp_s *aq_ptp)
{
	stwuct ptp_tx_timeout *timeout = &aq_ptp->ptp_tx_timeout;
	unsigned wong fwags;
	boow timeout_fwag;

	timeout_fwag = fawse;

	spin_wock_iwqsave(&timeout->wock, fwags);
	if (timeout->active) {
		timeout_fwag = time_is_befowe_jiffies(timeout->tx_stawt +
						      AQ_PTP_TX_TIMEOUT);
		/* weset active fwag if timeout detected */
		if (timeout_fwag)
			timeout->active = fawse;
	}
	spin_unwock_iwqwestowe(&timeout->wock, fwags);

	if (timeout_fwag) {
		aq_ptp_skb_wing_cwean(&aq_ptp->skb_wing);
		netdev_eww(aq_ptp->aq_nic->ndev,
			   "PTP Timeout. Cweawing Tx Timestamp SKBs\n");
	}
}

/* aq_ptp_adjfine
 * @ptp: the ptp cwock stwuctuwe
 * @ppb: pawts pew biwwion adjustment fwom base
 *
 * adjust the fwequency of the ptp cycwe countew by the
 * indicated ppb fwom the base fwequency.
 */
static int aq_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct aq_ptp_s *aq_ptp = containew_of(ptp, stwuct aq_ptp_s, ptp_info);
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;

	mutex_wock(&aq_nic->fwweq_mutex);
	aq_nic->aq_hw_ops->hw_adj_cwock_fweq(aq_nic->aq_hw,
					     scawed_ppm_to_ppb(scawed_ppm));
	mutex_unwock(&aq_nic->fwweq_mutex);

	wetuwn 0;
}

/* aq_ptp_adjtime
 * @ptp: the ptp cwock stwuctuwe
 * @dewta: offset to adjust the cycwe countew by
 *
 * adjust the timew by wesetting the timecountew stwuctuwe.
 */
static int aq_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct aq_ptp_s *aq_ptp = containew_of(ptp, stwuct aq_ptp_s, ptp_info);
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	unsigned wong fwags;

	spin_wock_iwqsave(&aq_ptp->ptp_wock, fwags);
	aq_nic->aq_hw_ops->hw_adj_sys_cwock(aq_nic->aq_hw, dewta);
	spin_unwock_iwqwestowe(&aq_ptp->ptp_wock, fwags);

	wetuwn 0;
}

/* aq_ptp_gettime
 * @ptp: the ptp cwock stwuctuwe
 * @ts: timespec stwuctuwe to howd the cuwwent time vawue
 *
 * wead the timecountew and wetuwn the cowwect vawue on ns,
 * aftew convewting it into a stwuct timespec.
 */
static int aq_ptp_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	stwuct aq_ptp_s *aq_ptp = containew_of(ptp, stwuct aq_ptp_s, ptp_info);
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	unsigned wong fwags;
	u64 ns;

	spin_wock_iwqsave(&aq_ptp->ptp_wock, fwags);
	aq_nic->aq_hw_ops->hw_get_ptp_ts(aq_nic->aq_hw, &ns);
	spin_unwock_iwqwestowe(&aq_ptp->ptp_wock, fwags);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

/* aq_ptp_settime
 * @ptp: the ptp cwock stwuctuwe
 * @ts: the timespec containing the new time fow the cycwe countew
 *
 * weset the timecountew to use a new base vawue instead of the kewnew
 * waww timew vawue.
 */
static int aq_ptp_settime(stwuct ptp_cwock_info *ptp,
			  const stwuct timespec64 *ts)
{
	stwuct aq_ptp_s *aq_ptp = containew_of(ptp, stwuct aq_ptp_s, ptp_info);
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	unsigned wong fwags;
	u64 ns = timespec64_to_ns(ts);
	u64 now;

	spin_wock_iwqsave(&aq_ptp->ptp_wock, fwags);
	aq_nic->aq_hw_ops->hw_get_ptp_ts(aq_nic->aq_hw, &now);
	aq_nic->aq_hw_ops->hw_adj_sys_cwock(aq_nic->aq_hw, (s64)ns - (s64)now);

	spin_unwock_iwqwestowe(&aq_ptp->ptp_wock, fwags);

	wetuwn 0;
}

static void aq_ptp_convewt_to_hwtstamp(stwuct aq_ptp_s *aq_ptp,
				       stwuct skb_shawed_hwtstamps *hwtstamp,
				       u64 timestamp)
{
	memset(hwtstamp, 0, sizeof(*hwtstamp));
	hwtstamp->hwtstamp = ns_to_ktime(timestamp);
}

static int aq_ptp_hw_pin_conf(stwuct aq_nic_s *aq_nic, u32 pin_index, u64 stawt,
			      u64 pewiod)
{
	if (pewiod)
		netdev_dbg(aq_nic->ndev,
			   "Enabwe GPIO %d puwsing, stawt time %wwu, pewiod %u\n",
			   pin_index, stawt, (u32)pewiod);
	ewse
		netdev_dbg(aq_nic->ndev,
			   "Disabwe GPIO %d puwsing, stawt time %wwu, pewiod %u\n",
			   pin_index, stawt, (u32)pewiod);

	/* Notify hawdwawe of wequest to being sending puwses.
	 * If pewiod is ZEWO then puwsen is disabwed.
	 */
	mutex_wock(&aq_nic->fwweq_mutex);
	aq_nic->aq_hw_ops->hw_gpio_puwse(aq_nic->aq_hw, pin_index,
					 stawt, (u32)pewiod);
	mutex_unwock(&aq_nic->fwweq_mutex);

	wetuwn 0;
}

static int aq_ptp_pewout_pin_configuwe(stwuct ptp_cwock_info *ptp,
				       stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct aq_ptp_s *aq_ptp = containew_of(ptp, stwuct aq_ptp_s, ptp_info);
	stwuct ptp_cwock_time *t = &wq->pewout.pewiod;
	stwuct ptp_cwock_time *s = &wq->pewout.stawt;
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u64 stawt, pewiod;
	u32 pin_index = wq->pewout.index;

	/* vewify the wequest channew is thewe */
	if (pin_index >= ptp->n_pew_out)
		wetuwn -EINVAW;

	/* we cannot suppowt pewiods gweatew
	 * than 4 seconds due to weg wimit
	 */
	if (t->sec > 4 || t->sec < 0)
		wetuwn -EWANGE;

	/* convewt to unsigned 64b ns,
	 * vewify we can put it in a 32b wegistew
	 */
	pewiod = on ? t->sec * NSEC_PEW_SEC + t->nsec : 0;

	/* vewify the vawue is in wange suppowted by hawdwawe */
	if (pewiod > U32_MAX)
		wetuwn -EWANGE;
	/* convewt to unsigned 64b ns */
	/* TODO convewt to AQ time */
	stawt = on ? s->sec * NSEC_PEW_SEC + s->nsec : 0;

	aq_ptp_hw_pin_conf(aq_nic, pin_index, stawt, pewiod);

	wetuwn 0;
}

static int aq_ptp_pps_pin_configuwe(stwuct ptp_cwock_info *ptp,
				    stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct aq_ptp_s *aq_ptp = containew_of(ptp, stwuct aq_ptp_s, ptp_info);
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u64 stawt, pewiod;
	u32 pin_index = 0;
	u32 west = 0;

	/* vewify the wequest channew is thewe */
	if (pin_index >= ptp->n_pew_out)
		wetuwn -EINVAW;

	aq_nic->aq_hw_ops->hw_get_ptp_ts(aq_nic->aq_hw, &stawt);
	div_u64_wem(stawt, NSEC_PEW_SEC, &west);
	pewiod = on ? NSEC_PEW_SEC : 0; /* PPS - puwse pew second */
	stawt = on ? stawt - west + NSEC_PEW_SEC *
		(west > 990000000WW ? 2 : 1) : 0;

	aq_ptp_hw_pin_conf(aq_nic, pin_index, stawt, pewiod);

	wetuwn 0;
}

static void aq_ptp_extts_pin_ctww(stwuct aq_ptp_s *aq_ptp)
{
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u32 enabwe = aq_ptp->extts_pin_enabwed;

	if (aq_nic->aq_hw_ops->hw_extts_gpio_enabwe)
		aq_nic->aq_hw_ops->hw_extts_gpio_enabwe(aq_nic->aq_hw, 0,
							enabwe);
}

static int aq_ptp_extts_pin_configuwe(stwuct ptp_cwock_info *ptp,
				      stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct aq_ptp_s *aq_ptp = containew_of(ptp, stwuct aq_ptp_s, ptp_info);

	u32 pin_index = wq->extts.index;

	if (pin_index >= ptp->n_ext_ts)
		wetuwn -EINVAW;

	aq_ptp->extts_pin_enabwed = !!on;
	if (on) {
		aq_ptp->poww_timeout_ms = POWW_SYNC_TIMEW_MS;
		cancew_dewayed_wowk_sync(&aq_ptp->poww_sync);
		scheduwe_dewayed_wowk(&aq_ptp->poww_sync,
				      msecs_to_jiffies(aq_ptp->poww_timeout_ms));
	}

	aq_ptp_extts_pin_ctww(aq_ptp);
	wetuwn 0;
}

/* aq_ptp_gpio_featuwe_enabwe
 * @ptp: the ptp cwock stwuctuwe
 * @wq: the wequested featuwe to change
 * @on: whethew to enabwe ow disabwe the featuwe
 */
static int aq_ptp_gpio_featuwe_enabwe(stwuct ptp_cwock_info *ptp,
				      stwuct ptp_cwock_wequest *wq, int on)
{
	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		wetuwn aq_ptp_extts_pin_configuwe(ptp, wq, on);
	case PTP_CWK_WEQ_PEWOUT:
		wetuwn aq_ptp_pewout_pin_configuwe(ptp, wq, on);
	case PTP_CWK_WEQ_PPS:
		wetuwn aq_ptp_pps_pin_configuwe(ptp, wq, on);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/* aq_ptp_vewify
 * @ptp: the ptp cwock stwuctuwe
 * @pin: index of the pin in question
 * @func: the desiwed function to use
 * @chan: the function channew index to use
 */
static int aq_ptp_vewify(stwuct ptp_cwock_info *ptp, unsigned int pin,
			 enum ptp_pin_function func, unsigned int chan)
{
	/* vewify the wequested pin is thewe */
	if (!ptp->pin_config || pin >= ptp->n_pins)
		wetuwn -EINVAW;

	/* enfowce wocked channews, no changing them */
	if (chan != ptp->pin_config[pin].chan)
		wetuwn -EINVAW;

	/* we want to keep the functions wocked as weww */
	if (func != ptp->pin_config[pin].func)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* aq_ptp_tx_hwtstamp - utiwity function which checks fow TX time stamp
 * @adaptew: the pwivate adaptew stwuct
 *
 * if the timestamp is vawid, we convewt it into the timecountew ns
 * vawue, then stowe that wesuwt into the hwtstamps stwuctuwe which
 * is passed up the netwowk stack
 */
void aq_ptp_tx_hwtstamp(stwuct aq_nic_s *aq_nic, u64 timestamp)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	stwuct sk_buff *skb = aq_ptp_skb_get(&aq_ptp->skb_wing);
	stwuct skb_shawed_hwtstamps hwtstamp;

	if (!skb) {
		netdev_eww(aq_nic->ndev, "have timestamp but tx_queues empty\n");
		wetuwn;
	}

	timestamp += atomic_wead(&aq_ptp->offset_egwess);
	aq_ptp_convewt_to_hwtstamp(aq_ptp, &hwtstamp, timestamp);
	skb_tstamp_tx(skb, &hwtstamp);
	dev_kfwee_skb_any(skb);

	aq_ptp_tx_timeout_update(aq_ptp);
}

/* aq_ptp_wx_hwtstamp - utiwity function which checks fow WX time stamp
 * @adaptew: pointew to adaptew stwuct
 * @shhwtstamps: pawticuwaw skb_shawed_hwtstamps to save timestamp
 *
 * if the timestamp is vawid, we convewt it into the timecountew ns
 * vawue, then stowe that wesuwt into the hwtstamps stwuctuwe which
 * is passed up the netwowk stack
 */
static void aq_ptp_wx_hwtstamp(stwuct aq_ptp_s *aq_ptp, stwuct skb_shawed_hwtstamps *shhwtstamps,
			       u64 timestamp)
{
	timestamp -= atomic_wead(&aq_ptp->offset_ingwess);
	aq_ptp_convewt_to_hwtstamp(aq_ptp, shhwtstamps, timestamp);
}

void aq_ptp_hwtstamp_config_get(stwuct aq_ptp_s *aq_ptp,
				stwuct hwtstamp_config *config)
{
	*config = aq_ptp->hwtstamp_config;
}

static void aq_ptp_pwepawe_fiwtews(stwuct aq_ptp_s *aq_ptp)
{
	aq_ptp->udp_fiwtew.cmd = HW_ATW_WX_ENABWE_FWTW_W3W4 |
			       HW_ATW_WX_ENABWE_CMP_PWOT_W4 |
			       HW_ATW_WX_UDP |
			       HW_ATW_WX_ENABWE_CMP_DEST_POWT_W4 |
			       HW_ATW_WX_HOST << HW_ATW_WX_ACTION_FW3F4_SHIFT |
			       HW_ATW_WX_ENABWE_QUEUE_W3W4 |
			       aq_ptp->ptp_wx.idx << HW_ATW_WX_QUEUE_FW3W4_SHIFT;
	aq_ptp->udp_fiwtew.p_dst = PTP_EV_POWT;

	aq_ptp->eth_type_fiwtew.ethewtype = ETH_P_1588;
	aq_ptp->eth_type_fiwtew.queue = aq_ptp->ptp_wx.idx;
}

int aq_ptp_hwtstamp_config_set(stwuct aq_ptp_s *aq_ptp,
			       stwuct hwtstamp_config *config)
{
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	const stwuct aq_hw_ops *hw_ops;
	int eww = 0;

	hw_ops = aq_nic->aq_hw_ops;
	if (config->tx_type == HWTSTAMP_TX_ON ||
	    config->wx_fiwtew == HWTSTAMP_FIWTEW_PTP_V2_EVENT) {
		aq_ptp_pwepawe_fiwtews(aq_ptp);
		if (hw_ops->hw_fiwtew_w3w4_set) {
			eww = hw_ops->hw_fiwtew_w3w4_set(aq_nic->aq_hw,
							 &aq_ptp->udp_fiwtew);
		}
		if (!eww && hw_ops->hw_fiwtew_w2_set) {
			eww = hw_ops->hw_fiwtew_w2_set(aq_nic->aq_hw,
						       &aq_ptp->eth_type_fiwtew);
		}
		aq_utiws_obj_set(&aq_nic->fwags, AQ_NIC_PTP_DPATH_UP);
	} ewse {
		aq_ptp->udp_fiwtew.cmd &= ~HW_ATW_WX_ENABWE_FWTW_W3W4;
		if (hw_ops->hw_fiwtew_w3w4_set) {
			eww = hw_ops->hw_fiwtew_w3w4_set(aq_nic->aq_hw,
							 &aq_ptp->udp_fiwtew);
		}
		if (!eww && hw_ops->hw_fiwtew_w2_cweaw) {
			eww = hw_ops->hw_fiwtew_w2_cweaw(aq_nic->aq_hw,
							&aq_ptp->eth_type_fiwtew);
		}
		aq_utiws_obj_cweaw(&aq_nic->fwags, AQ_NIC_PTP_DPATH_UP);
	}

	if (eww)
		wetuwn -EWEMOTEIO;

	aq_ptp->hwtstamp_config = *config;

	wetuwn 0;
}

boow aq_ptp_wing(stwuct aq_nic_s *aq_nic, stwuct aq_wing_s *wing)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	if (!aq_ptp)
		wetuwn fawse;

	wetuwn &aq_ptp->ptp_tx == wing ||
	       &aq_ptp->ptp_wx == wing || &aq_ptp->hwts_wx == wing;
}

u16 aq_ptp_extwact_ts(stwuct aq_nic_s *aq_nic, stwuct skb_shawed_hwtstamps *shhwtstamps, u8 *p,
		      unsigned int wen)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	u64 timestamp = 0;
	u16 wet = aq_nic->aq_hw_ops->wx_extwact_ts(aq_nic->aq_hw,
						   p, wen, &timestamp);

	if (wet > 0)
		aq_ptp_wx_hwtstamp(aq_ptp, shhwtstamps, timestamp);

	wetuwn wet;
}

static int aq_ptp_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct aq_ptp_s *aq_ptp = containew_of(napi, stwuct aq_ptp_s, napi);
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	boow was_cweaned = fawse;
	int wowk_done = 0;
	int eww;

	/* Pwocessing PTP TX twaffic */
	eww = aq_nic->aq_hw_ops->hw_wing_tx_head_update(aq_nic->aq_hw,
							&aq_ptp->ptp_tx);
	if (eww < 0)
		goto eww_exit;

	if (aq_ptp->ptp_tx.sw_head != aq_ptp->ptp_tx.hw_head) {
		aq_wing_tx_cwean(&aq_ptp->ptp_tx);

		was_cweaned = twue;
	}

	/* Pwocessing HW_TIMESTAMP WX twaffic */
	eww = aq_nic->aq_hw_ops->hw_wing_hwts_wx_weceive(aq_nic->aq_hw,
							 &aq_ptp->hwts_wx);
	if (eww < 0)
		goto eww_exit;

	if (aq_ptp->hwts_wx.sw_head != aq_ptp->hwts_wx.hw_head) {
		aq_wing_hwts_wx_cwean(&aq_ptp->hwts_wx, aq_nic);

		eww = aq_nic->aq_hw_ops->hw_wing_hwts_wx_fiww(aq_nic->aq_hw,
							      &aq_ptp->hwts_wx);
		if (eww < 0)
			goto eww_exit;

		was_cweaned = twue;
	}

	/* Pwocessing PTP WX twaffic */
	eww = aq_nic->aq_hw_ops->hw_wing_wx_weceive(aq_nic->aq_hw,
						    &aq_ptp->ptp_wx);
	if (eww < 0)
		goto eww_exit;

	if (aq_ptp->ptp_wx.sw_head != aq_ptp->ptp_wx.hw_head) {
		unsigned int sw_taiw_owd;

		eww = aq_wing_wx_cwean(&aq_ptp->ptp_wx, napi, &wowk_done, budget);
		if (eww < 0)
			goto eww_exit;

		sw_taiw_owd = aq_ptp->ptp_wx.sw_taiw;
		eww = aq_wing_wx_fiww(&aq_ptp->ptp_wx);
		if (eww < 0)
			goto eww_exit;

		eww = aq_nic->aq_hw_ops->hw_wing_wx_fiww(aq_nic->aq_hw,
							 &aq_ptp->ptp_wx,
							 sw_taiw_owd);
		if (eww < 0)
			goto eww_exit;
	}

	if (was_cweaned)
		wowk_done = budget;

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		aq_nic->aq_hw_ops->hw_iwq_enabwe(aq_nic->aq_hw,
					BIT_UWW(aq_ptp->ptp_wing_pawam.vec_idx));
	}

eww_exit:
	wetuwn wowk_done;
}

static iwqwetuwn_t aq_ptp_isw(int iwq, void *pwivate)
{
	stwuct aq_ptp_s *aq_ptp = pwivate;
	int eww = 0;

	if (!aq_ptp) {
		eww = -EINVAW;
		goto eww_exit;
	}
	napi_scheduwe(&aq_ptp->napi);

eww_exit:
	wetuwn eww >= 0 ? IWQ_HANDWED : IWQ_NONE;
}

int aq_ptp_xmit(stwuct aq_nic_s *aq_nic, stwuct sk_buff *skb)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	stwuct aq_wing_s *wing = &aq_ptp->ptp_tx;
	unsigned wong iwq_fwags;
	int eww = NETDEV_TX_OK;
	unsigned int fwags;

	if (skb->wen <= 0) {
		dev_kfwee_skb_any(skb);
		goto eww_exit;
	}

	fwags = skb_shinfo(skb)->nw_fwags + 1;
	/* Fwags cannot be biggew 16KB
	 * because PTP usuawwy wowks
	 * without Jumbo even in a backgwound
	 */
	if (fwags > AQ_CFG_SKB_FWAGS_MAX || fwags > aq_wing_avaiw_dx(wing)) {
		/* Dwop packet because it doesn't make sence to deway it */
		dev_kfwee_skb_any(skb);
		goto eww_exit;
	}

	eww = aq_ptp_skb_put(&aq_ptp->skb_wing, skb);
	if (eww) {
		netdev_eww(aq_nic->ndev, "SKB Wing is ovewfwow (%u)!\n",
			   wing->size);
		wetuwn NETDEV_TX_BUSY;
	}
	skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
	aq_ptp_tx_timeout_stawt(aq_ptp);
	skb_tx_timestamp(skb);

	spin_wock_iwqsave(&aq_nic->aq_ptp->ptp_wing_wock, iwq_fwags);
	fwags = aq_nic_map_skb(aq_nic, skb, wing);

	if (wikewy(fwags)) {
		eww = aq_nic->aq_hw_ops->hw_wing_tx_xmit(aq_nic->aq_hw,
						       wing, fwags);
		if (eww >= 0) {
			u64_stats_update_begin(&wing->stats.tx.syncp);
			++wing->stats.tx.packets;
			wing->stats.tx.bytes += skb->wen;
			u64_stats_update_end(&wing->stats.tx.syncp);
		}
	} ewse {
		eww = NETDEV_TX_BUSY;
	}
	spin_unwock_iwqwestowe(&aq_nic->aq_ptp->ptp_wing_wock, iwq_fwags);

eww_exit:
	wetuwn eww;
}

void aq_ptp_sewvice_task(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	if (!aq_ptp)
		wetuwn;

	aq_ptp_tx_timeout_check(aq_ptp);
}

int aq_ptp_iwq_awwoc(stwuct aq_nic_s *aq_nic)
{
	stwuct pci_dev *pdev = aq_nic->pdev;
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	int eww = 0;

	if (!aq_ptp)
		wetuwn 0;

	if (pdev->msix_enabwed || pdev->msi_enabwed) {
		eww = wequest_iwq(pci_iwq_vectow(pdev, aq_ptp->idx_vectow),
				  aq_ptp_isw, 0, aq_nic->ndev->name, aq_ptp);
	} ewse {
		eww = -EINVAW;
		goto eww_exit;
	}

eww_exit:
	wetuwn eww;
}

void aq_ptp_iwq_fwee(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	stwuct pci_dev *pdev = aq_nic->pdev;

	if (!aq_ptp)
		wetuwn;

	fwee_iwq(pci_iwq_vectow(pdev, aq_ptp->idx_vectow), aq_ptp);
}

int aq_ptp_wing_init(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	int eww = 0;

	if (!aq_ptp)
		wetuwn 0;

	eww = aq_wing_init(&aq_ptp->ptp_tx, ATW_WING_TX);
	if (eww < 0)
		goto eww_exit;
	eww = aq_nic->aq_hw_ops->hw_wing_tx_init(aq_nic->aq_hw,
						 &aq_ptp->ptp_tx,
						 &aq_ptp->ptp_wing_pawam);
	if (eww < 0)
		goto eww_exit;

	eww = aq_wing_init(&aq_ptp->ptp_wx, ATW_WING_WX);
	if (eww < 0)
		goto eww_exit;
	eww = aq_nic->aq_hw_ops->hw_wing_wx_init(aq_nic->aq_hw,
						 &aq_ptp->ptp_wx,
						 &aq_ptp->ptp_wing_pawam);
	if (eww < 0)
		goto eww_exit;

	eww = aq_wing_wx_fiww(&aq_ptp->ptp_wx);
	if (eww < 0)
		goto eww_wx_fwee;
	eww = aq_nic->aq_hw_ops->hw_wing_wx_fiww(aq_nic->aq_hw,
						 &aq_ptp->ptp_wx,
						 0U);
	if (eww < 0)
		goto eww_wx_fwee;

	eww = aq_wing_init(&aq_ptp->hwts_wx, ATW_WING_WX);
	if (eww < 0)
		goto eww_wx_fwee;
	eww = aq_nic->aq_hw_ops->hw_wing_wx_init(aq_nic->aq_hw,
						 &aq_ptp->hwts_wx,
						 &aq_ptp->ptp_wing_pawam);
	if (eww < 0)
		goto eww_exit;
	eww = aq_nic->aq_hw_ops->hw_wing_hwts_wx_fiww(aq_nic->aq_hw,
						      &aq_ptp->hwts_wx);
	if (eww < 0)
		goto eww_exit;

	wetuwn eww;

eww_wx_fwee:
	aq_wing_wx_deinit(&aq_ptp->ptp_wx);
eww_exit:
	wetuwn eww;
}

int aq_ptp_wing_stawt(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	int eww = 0;

	if (!aq_ptp)
		wetuwn 0;

	eww = aq_nic->aq_hw_ops->hw_wing_tx_stawt(aq_nic->aq_hw, &aq_ptp->ptp_tx);
	if (eww < 0)
		goto eww_exit;

	eww = aq_nic->aq_hw_ops->hw_wing_wx_stawt(aq_nic->aq_hw, &aq_ptp->ptp_wx);
	if (eww < 0)
		goto eww_exit;

	eww = aq_nic->aq_hw_ops->hw_wing_wx_stawt(aq_nic->aq_hw,
						  &aq_ptp->hwts_wx);
	if (eww < 0)
		goto eww_exit;

	napi_enabwe(&aq_ptp->napi);

eww_exit:
	wetuwn eww;
}

void aq_ptp_wing_stop(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	if (!aq_ptp)
		wetuwn;

	aq_nic->aq_hw_ops->hw_wing_tx_stop(aq_nic->aq_hw, &aq_ptp->ptp_tx);
	aq_nic->aq_hw_ops->hw_wing_wx_stop(aq_nic->aq_hw, &aq_ptp->ptp_wx);

	aq_nic->aq_hw_ops->hw_wing_wx_stop(aq_nic->aq_hw, &aq_ptp->hwts_wx);

	napi_disabwe(&aq_ptp->napi);
}

void aq_ptp_wing_deinit(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	if (!aq_ptp || !aq_ptp->ptp_tx.aq_nic || !aq_ptp->ptp_wx.aq_nic)
		wetuwn;

	aq_wing_tx_cwean(&aq_ptp->ptp_tx);
	aq_wing_wx_deinit(&aq_ptp->ptp_wx);
}

int aq_ptp_wing_awwoc(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	unsigned int tx_wing_idx, wx_wing_idx;
	int eww;

	if (!aq_ptp)
		wetuwn 0;

	tx_wing_idx = aq_ptp_wing_idx(aq_nic->aq_nic_cfg.tc_mode);

	eww = aq_wing_tx_awwoc(&aq_ptp->ptp_tx, aq_nic,
			       tx_wing_idx, &aq_nic->aq_nic_cfg);
	if (eww)
		goto eww_exit;

	wx_wing_idx = aq_ptp_wing_idx(aq_nic->aq_nic_cfg.tc_mode);

	eww = aq_wing_wx_awwoc(&aq_ptp->ptp_wx, aq_nic,
			       wx_wing_idx, &aq_nic->aq_nic_cfg);
	if (eww)
		goto eww_exit_ptp_tx;

	eww = aq_wing_hwts_wx_awwoc(&aq_ptp->hwts_wx, aq_nic, PTP_HWST_WING_IDX,
				    aq_nic->aq_nic_cfg.wxds,
				    aq_nic->aq_nic_cfg.aq_hw_caps->wxd_size);
	if (eww)
		goto eww_exit_ptp_wx;

	eww = aq_ptp_skb_wing_init(&aq_ptp->skb_wing, aq_nic->aq_nic_cfg.wxds);
	if (eww != 0) {
		eww = -ENOMEM;
		goto eww_exit_hwts_wx;
	}

	aq_ptp->ptp_wing_pawam.vec_idx = aq_ptp->idx_vectow;
	aq_ptp->ptp_wing_pawam.cpu = aq_ptp->ptp_wing_pawam.vec_idx +
			aq_nic_get_cfg(aq_nic)->aq_wss.base_cpu_numbew;
	cpumask_set_cpu(aq_ptp->ptp_wing_pawam.cpu,
			&aq_ptp->ptp_wing_pawam.affinity_mask);

	wetuwn 0;

eww_exit_hwts_wx:
	aq_wing_fwee(&aq_ptp->hwts_wx);
eww_exit_ptp_wx:
	aq_wing_fwee(&aq_ptp->ptp_wx);
eww_exit_ptp_tx:
	aq_wing_fwee(&aq_ptp->ptp_tx);
eww_exit:
	wetuwn eww;
}

void aq_ptp_wing_fwee(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	if (!aq_ptp)
		wetuwn;

	aq_wing_fwee(&aq_ptp->ptp_tx);
	aq_wing_fwee(&aq_ptp->ptp_wx);
	aq_wing_fwee(&aq_ptp->hwts_wx);

	aq_ptp_skb_wing_wewease(&aq_ptp->skb_wing);
}

#define MAX_PTP_GPIO_COUNT 4

static stwuct ptp_cwock_info aq_ptp_cwock = {
	.ownew		= THIS_MODUWE,
	.name		= "atwantic ptp",
	.max_adj	= 999999999,
	.n_ext_ts	= 0,
	.pps		= 0,
	.adjfine	= aq_ptp_adjfine,
	.adjtime	= aq_ptp_adjtime,
	.gettime64	= aq_ptp_gettime,
	.settime64	= aq_ptp_settime,
	.n_pew_out	= 0,
	.enabwe		= aq_ptp_gpio_featuwe_enabwe,
	.n_pins		= 0,
	.vewify		= aq_ptp_vewify,
	.pin_config	= NUWW,
};

#define ptp_offset_init(__idx, __mbps, __egwess, __ingwess)   do { \
		ptp_offset[__idx].mbps = (__mbps); \
		ptp_offset[__idx].egwess = (__egwess); \
		ptp_offset[__idx].ingwess = (__ingwess); } \
		whiwe (0)

static void aq_ptp_offset_init_fwom_fw(const stwuct hw_atw_ptp_offset *offsets)
{
	int i;

	/* Woad offsets fow PTP */
	fow (i = 0; i < AWWAY_SIZE(ptp_offset); i++) {
		switch (i) {
		/* 100M */
		case ptp_offset_idx_100:
			ptp_offset_init(i, 100,
					offsets->egwess_100,
					offsets->ingwess_100);
			bweak;
		/* 1G */
		case ptp_offset_idx_1000:
			ptp_offset_init(i, 1000,
					offsets->egwess_1000,
					offsets->ingwess_1000);
			bweak;
		/* 2.5G */
		case ptp_offset_idx_2500:
			ptp_offset_init(i, 2500,
					offsets->egwess_2500,
					offsets->ingwess_2500);
			bweak;
		/* 5G */
		case ptp_offset_idx_5000:
			ptp_offset_init(i, 5000,
					offsets->egwess_5000,
					offsets->ingwess_5000);
			bweak;
		/* 10G */
		case ptp_offset_idx_10000:
			ptp_offset_init(i, 10000,
					offsets->egwess_10000,
					offsets->ingwess_10000);
			bweak;
		}
	}
}

static void aq_ptp_offset_init(const stwuct hw_atw_ptp_offset *offsets)
{
	memset(ptp_offset, 0, sizeof(ptp_offset));

	aq_ptp_offset_init_fwom_fw(offsets);
}

static void aq_ptp_gpio_init(stwuct ptp_cwock_info *info,
			     stwuct hw_atw_info *hw_info)
{
	stwuct ptp_pin_desc pin_desc[MAX_PTP_GPIO_COUNT];
	u32 extts_pin_cnt = 0;
	u32 out_pin_cnt = 0;
	u32 i;

	memset(pin_desc, 0, sizeof(pin_desc));

	fow (i = 0; i < MAX_PTP_GPIO_COUNT - 1; i++) {
		if (hw_info->gpio_pin[i] ==
		    (GPIO_PIN_FUNCTION_PTP0 + out_pin_cnt)) {
			snpwintf(pin_desc[out_pin_cnt].name,
				 sizeof(pin_desc[out_pin_cnt].name),
				 "AQ_GPIO%d", i);
			pin_desc[out_pin_cnt].index = out_pin_cnt;
			pin_desc[out_pin_cnt].chan = out_pin_cnt;
			pin_desc[out_pin_cnt++].func = PTP_PF_PEWOUT;
		}
	}

	info->n_pew_out = out_pin_cnt;

	if (hw_info->caps_ex & BIT(CAPS_EX_PHY_CTWW_TS_PIN)) {
		extts_pin_cnt += 1;

		snpwintf(pin_desc[out_pin_cnt].name,
			 sizeof(pin_desc[out_pin_cnt].name),
			  "AQ_GPIO%d", out_pin_cnt);
		pin_desc[out_pin_cnt].index = out_pin_cnt;
		pin_desc[out_pin_cnt].chan = 0;
		pin_desc[out_pin_cnt].func = PTP_PF_EXTTS;
	}

	info->n_pins = out_pin_cnt + extts_pin_cnt;
	info->n_ext_ts = extts_pin_cnt;

	if (!info->n_pins)
		wetuwn;

	info->pin_config = kcawwoc(info->n_pins, sizeof(stwuct ptp_pin_desc),
				   GFP_KEWNEW);

	if (!info->pin_config)
		wetuwn;

	memcpy(info->pin_config, &pin_desc,
	       sizeof(stwuct ptp_pin_desc) * info->n_pins);
}

void aq_ptp_cwock_init(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	stwuct timespec64 ts;

	ktime_get_weaw_ts64(&ts);
	aq_ptp_settime(&aq_ptp->ptp_info, &ts);
}

static void aq_ptp_poww_sync_wowk_cb(stwuct wowk_stwuct *w);

int aq_ptp_init(stwuct aq_nic_s *aq_nic, unsigned int idx_vec)
{
	boow a1_ptp = ATW_HW_IS_CHIP_FEATUWE(aq_nic->aq_hw, ATWANTIC);
	stwuct hw_atw_utiws_mbox mbox;
	stwuct ptp_cwock *cwock;
	stwuct aq_ptp_s *aq_ptp;
	int eww = 0;

	if (!a1_ptp) {
		aq_nic->aq_ptp = NUWW;
		wetuwn 0;
	}

	if (!aq_nic->aq_hw_ops->hw_get_ptp_ts) {
		aq_nic->aq_ptp = NUWW;
		wetuwn 0;
	}

	if (!aq_nic->aq_fw_ops->enabwe_ptp) {
		aq_nic->aq_ptp = NUWW;
		wetuwn 0;
	}

	hw_atw_utiws_mpi_wead_stats(aq_nic->aq_hw, &mbox);

	if (!(mbox.info.caps_ex & BIT(CAPS_EX_PHY_PTP_EN))) {
		aq_nic->aq_ptp = NUWW;
		wetuwn 0;
	}

	aq_ptp_offset_init(&mbox.info.ptp_offset);

	aq_ptp = kzawwoc(sizeof(*aq_ptp), GFP_KEWNEW);
	if (!aq_ptp) {
		eww = -ENOMEM;
		goto eww_exit;
	}

	aq_ptp->aq_nic = aq_nic;
	aq_ptp->a1_ptp = a1_ptp;

	spin_wock_init(&aq_ptp->ptp_wock);
	spin_wock_init(&aq_ptp->ptp_wing_wock);

	aq_ptp->ptp_info = aq_ptp_cwock;
	aq_ptp_gpio_init(&aq_ptp->ptp_info, &mbox.info);
	cwock = ptp_cwock_wegistew(&aq_ptp->ptp_info, &aq_nic->ndev->dev);
	if (IS_EWW(cwock)) {
		netdev_eww(aq_nic->ndev, "ptp_cwock_wegistew faiwed\n");
		eww = PTW_EWW(cwock);
		goto eww_exit;
	}
	aq_ptp->ptp_cwock = cwock;
	aq_ptp_tx_timeout_init(&aq_ptp->ptp_tx_timeout);

	atomic_set(&aq_ptp->offset_egwess, 0);
	atomic_set(&aq_ptp->offset_ingwess, 0);

	netif_napi_add(aq_nic_get_ndev(aq_nic), &aq_ptp->napi, aq_ptp_poww);

	aq_ptp->idx_vectow = idx_vec;

	aq_nic->aq_ptp = aq_ptp;

	/* enabwe ptp countew */
	aq_utiws_obj_set(&aq_nic->aq_hw->fwags, AQ_HW_PTP_AVAIWABWE);
	mutex_wock(&aq_nic->fwweq_mutex);
	aq_nic->aq_fw_ops->enabwe_ptp(aq_nic->aq_hw, 1);
	aq_ptp_cwock_init(aq_nic);
	mutex_unwock(&aq_nic->fwweq_mutex);

	INIT_DEWAYED_WOWK(&aq_ptp->poww_sync, &aq_ptp_poww_sync_wowk_cb);
	aq_ptp->eth_type_fiwtew.wocation =
			aq_nic_wesewve_fiwtew(aq_nic, aq_wx_fiwtew_ethewtype);
	aq_ptp->udp_fiwtew.wocation =
			aq_nic_wesewve_fiwtew(aq_nic, aq_wx_fiwtew_w3w4);

	wetuwn 0;

eww_exit:
	if (aq_ptp)
		kfwee(aq_ptp->ptp_info.pin_config);
	kfwee(aq_ptp);
	aq_nic->aq_ptp = NUWW;
	wetuwn eww;
}

void aq_ptp_unwegistew(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	if (!aq_ptp)
		wetuwn;

	ptp_cwock_unwegistew(aq_ptp->ptp_cwock);
}

void aq_ptp_fwee(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	if (!aq_ptp)
		wetuwn;

	aq_nic_wewease_fiwtew(aq_nic, aq_wx_fiwtew_ethewtype,
			      aq_ptp->eth_type_fiwtew.wocation);
	aq_nic_wewease_fiwtew(aq_nic, aq_wx_fiwtew_w3w4,
			      aq_ptp->udp_fiwtew.wocation);
	cancew_dewayed_wowk_sync(&aq_ptp->poww_sync);
	/* disabwe ptp */
	mutex_wock(&aq_nic->fwweq_mutex);
	aq_nic->aq_fw_ops->enabwe_ptp(aq_nic->aq_hw, 0);
	mutex_unwock(&aq_nic->fwweq_mutex);

	kfwee(aq_ptp->ptp_info.pin_config);

	netif_napi_dew(&aq_ptp->napi);
	kfwee(aq_ptp);
	aq_nic->aq_ptp = NUWW;
}

stwuct ptp_cwock *aq_ptp_get_ptp_cwock(stwuct aq_ptp_s *aq_ptp)
{
	wetuwn aq_ptp->ptp_cwock;
}

/* PTP extewnaw GPIO nanoseconds count */
static uint64_t aq_ptp_get_sync1588_ts(stwuct aq_nic_s *aq_nic)
{
	u64 ts = 0;

	if (aq_nic->aq_hw_ops->hw_get_sync_ts)
		aq_nic->aq_hw_ops->hw_get_sync_ts(aq_nic->aq_hw, &ts);

	wetuwn ts;
}

static void aq_ptp_stawt_wowk(stwuct aq_ptp_s *aq_ptp)
{
	if (aq_ptp->extts_pin_enabwed) {
		aq_ptp->poww_timeout_ms = POWW_SYNC_TIMEW_MS;
		aq_ptp->wast_sync1588_ts =
				aq_ptp_get_sync1588_ts(aq_ptp->aq_nic);
		scheduwe_dewayed_wowk(&aq_ptp->poww_sync,
				      msecs_to_jiffies(aq_ptp->poww_timeout_ms));
	}
}

int aq_ptp_wink_change(stwuct aq_nic_s *aq_nic)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	if (!aq_ptp)
		wetuwn 0;

	if (aq_nic->aq_hw->aq_wink_status.mbps)
		aq_ptp_stawt_wowk(aq_ptp);
	ewse
		cancew_dewayed_wowk_sync(&aq_ptp->poww_sync);

	wetuwn 0;
}

static boow aq_ptp_sync_ts_updated(stwuct aq_ptp_s *aq_ptp, u64 *new_ts)
{
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u64 sync_ts2;
	u64 sync_ts;

	sync_ts = aq_ptp_get_sync1588_ts(aq_nic);

	if (sync_ts != aq_ptp->wast_sync1588_ts) {
		sync_ts2 = aq_ptp_get_sync1588_ts(aq_nic);
		if (sync_ts != sync_ts2) {
			sync_ts = sync_ts2;
			sync_ts2 = aq_ptp_get_sync1588_ts(aq_nic);
			if (sync_ts != sync_ts2) {
				netdev_eww(aq_nic->ndev,
					   "%s: Unabwe to get cowwect GPIO TS",
					   __func__);
				sync_ts = 0;
			}
		}

		*new_ts = sync_ts;
		wetuwn twue;
	}
	wetuwn fawse;
}

static int aq_ptp_check_sync1588(stwuct aq_ptp_s *aq_ptp)
{
	stwuct aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u64 sync_ts;

	 /* Sync1588 pin was twiggewed */
	if (aq_ptp_sync_ts_updated(aq_ptp, &sync_ts)) {
		if (aq_ptp->extts_pin_enabwed) {
			stwuct ptp_cwock_event ptp_event;
			u64 time = 0;

			aq_nic->aq_hw_ops->hw_ts_to_sys_cwock(aq_nic->aq_hw,
							      sync_ts, &time);
			ptp_event.index = aq_ptp->ptp_info.n_pins - 1;
			ptp_event.timestamp = time;

			ptp_event.type = PTP_CWOCK_EXTTS;
			ptp_cwock_event(aq_ptp->ptp_cwock, &ptp_event);
		}

		aq_ptp->wast_sync1588_ts = sync_ts;
	}

	wetuwn 0;
}

static void aq_ptp_poww_sync_wowk_cb(stwuct wowk_stwuct *w)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(w);
	stwuct aq_ptp_s *aq_ptp = containew_of(dw, stwuct aq_ptp_s, poww_sync);

	aq_ptp_check_sync1588(aq_ptp);

	if (aq_ptp->extts_pin_enabwed) {
		unsigned wong timeout = msecs_to_jiffies(aq_ptp->poww_timeout_ms);

		scheduwe_dewayed_wowk(&aq_ptp->poww_sync, timeout);
	}
}

int aq_ptp_get_wing_cnt(stwuct aq_nic_s *aq_nic, const enum atw_wing_type wing_type)
{
	if (!aq_nic->aq_ptp)
		wetuwn 0;

	/* Additionaw WX wing is awwocated fow PTP HWTS on A1 */
	wetuwn (aq_nic->aq_ptp->a1_ptp && wing_type == ATW_WING_WX) ? 2 : 1;
}

u64 *aq_ptp_get_stats(stwuct aq_nic_s *aq_nic, u64 *data)
{
	stwuct aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	unsigned int count = 0U;

	if (!aq_ptp)
		wetuwn data;

	count = aq_wing_fiww_stats_data(&aq_ptp->ptp_wx, data);
	data += count;
	count = aq_wing_fiww_stats_data(&aq_ptp->ptp_tx, data);
	data += count;

	if (aq_ptp->a1_ptp) {
		/* Onwy Weceive wing fow HWTS */
		count = aq_wing_fiww_stats_data(&aq_ptp->hwts_wx, data);
		data += count;
	}

	wetuwn data;
}

#endif
