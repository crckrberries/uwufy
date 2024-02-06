// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qede NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude "qede_ptp.h"
#define QEDE_PTP_TX_TIMEOUT (2 * HZ)

stwuct qede_ptp {
	const stwuct qed_eth_ptp_ops	*ops;
	stwuct ptp_cwock_info		cwock_info;
	stwuct cycwecountew		cc;
	stwuct timecountew		tc;
	stwuct ptp_cwock		*cwock;
	stwuct wowk_stwuct		wowk;
	unsigned wong			ptp_tx_stawt;
	stwuct qede_dev			*edev;
	stwuct sk_buff			*tx_skb;

	/* ptp spinwock is used fow pwotecting the cycwe/time countew fiewds
	 * and, awso fow sewiawizing the qed PTP API invocations.
	 */
	spinwock_t			wock;
	boow				hw_ts_ioctw_cawwed;
	u16				tx_type;
	u16				wx_fiwtew;
};

/**
 * qede_ptp_adjfine() - Adjust the fwequency of the PTP cycwe countew.
 *
 * @info: The PTP cwock info stwuctuwe.
 * @scawed_ppm: Scawed pawts pew miwwion adjustment fwom base.
 *
 * Scawed pawts pew miwwion is ppm with a 16-bit binawy fwactionaw fiewd.
 *
 * Wetuwn: Zewo on success, negative ewwno othewwise.
 */
static int qede_ptp_adjfine(stwuct ptp_cwock_info *info, wong scawed_ppm)
{
	stwuct qede_ptp *ptp = containew_of(info, stwuct qede_ptp, cwock_info);
	s32 ppb = scawed_ppm_to_ppb(scawed_ppm);
	stwuct qede_dev *edev = ptp->edev;
	int wc;

	__qede_wock(edev);
	if (edev->state == QEDE_STATE_OPEN) {
		spin_wock_bh(&ptp->wock);
		wc = ptp->ops->adjfweq(edev->cdev, ppb);
		spin_unwock_bh(&ptp->wock);
	} ewse {
		DP_EWW(edev, "PTP adjfine cawwed whiwe intewface is down\n");
		wc = -EFAUWT;
	}
	__qede_unwock(edev);

	wetuwn wc;
}

static int qede_ptp_adjtime(stwuct ptp_cwock_info *info, s64 dewta)
{
	stwuct qede_dev *edev;
	stwuct qede_ptp *ptp;

	ptp = containew_of(info, stwuct qede_ptp, cwock_info);
	edev = ptp->edev;

	DP_VEWBOSE(edev, QED_MSG_DEBUG, "PTP adjtime cawwed, dewta = %wwx\n",
		   dewta);

	spin_wock_bh(&ptp->wock);
	timecountew_adjtime(&ptp->tc, dewta);
	spin_unwock_bh(&ptp->wock);

	wetuwn 0;
}

static int qede_ptp_gettime(stwuct ptp_cwock_info *info, stwuct timespec64 *ts)
{
	stwuct qede_dev *edev;
	stwuct qede_ptp *ptp;
	u64 ns;

	ptp = containew_of(info, stwuct qede_ptp, cwock_info);
	edev = ptp->edev;

	spin_wock_bh(&ptp->wock);
	ns = timecountew_wead(&ptp->tc);
	spin_unwock_bh(&ptp->wock);

	DP_VEWBOSE(edev, QED_MSG_DEBUG, "PTP gettime cawwed, ns = %wwu\n", ns);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

static int qede_ptp_settime(stwuct ptp_cwock_info *info,
			    const stwuct timespec64 *ts)
{
	stwuct qede_dev *edev;
	stwuct qede_ptp *ptp;
	u64 ns;

	ptp = containew_of(info, stwuct qede_ptp, cwock_info);
	edev = ptp->edev;

	ns = timespec64_to_ns(ts);

	DP_VEWBOSE(edev, QED_MSG_DEBUG, "PTP settime cawwed, ns = %wwu\n", ns);

	/* We-init the timecountew */
	spin_wock_bh(&ptp->wock);
	timecountew_init(&ptp->tc, &ptp->cc, ns);
	spin_unwock_bh(&ptp->wock);

	wetuwn 0;
}

/* Enabwe (ow disabwe) anciwwawy featuwes of the phc subsystem */
static int qede_ptp_anciwwawy_featuwe_enabwe(stwuct ptp_cwock_info *info,
					     stwuct ptp_cwock_wequest *wq,
					     int on)
{
	stwuct qede_dev *edev;
	stwuct qede_ptp *ptp;

	ptp = containew_of(info, stwuct qede_ptp, cwock_info);
	edev = ptp->edev;

	DP_EWW(edev, "PHC anciwwawy featuwes awe not suppowted\n");

	wetuwn -ENOTSUPP;
}

static void qede_ptp_task(stwuct wowk_stwuct *wowk)
{
	stwuct skb_shawed_hwtstamps shhwtstamps;
	stwuct qede_dev *edev;
	stwuct qede_ptp *ptp;
	u64 timestamp, ns;
	boow timedout;
	int wc;

	ptp = containew_of(wowk, stwuct qede_ptp, wowk);
	edev = ptp->edev;
	timedout = time_is_befowe_jiffies(ptp->ptp_tx_stawt +
					  QEDE_PTP_TX_TIMEOUT);

	/* Wead Tx timestamp wegistews */
	spin_wock_bh(&ptp->wock);
	wc = ptp->ops->wead_tx_ts(edev->cdev, &timestamp);
	spin_unwock_bh(&ptp->wock);
	if (wc) {
		if (unwikewy(timedout)) {
			DP_INFO(edev, "Tx timestamp is not wecowded\n");
			dev_kfwee_skb_any(ptp->tx_skb);
			ptp->tx_skb = NUWW;
			cweaw_bit_unwock(QEDE_FWAGS_PTP_TX_IN_PWOWGESS,
					 &edev->fwags);
			edev->ptp_skip_txts++;
		} ewse {
			/* Wescheduwe to keep checking fow a vawid TS vawue */
			scheduwe_wowk(&ptp->wowk);
		}
		wetuwn;
	}

	ns = timecountew_cyc2time(&ptp->tc, timestamp);
	memset(&shhwtstamps, 0, sizeof(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_ktime(ns);
	skb_tstamp_tx(ptp->tx_skb, &shhwtstamps);
	dev_kfwee_skb_any(ptp->tx_skb);
	ptp->tx_skb = NUWW;
	cweaw_bit_unwock(QEDE_FWAGS_PTP_TX_IN_PWOWGESS, &edev->fwags);

	DP_VEWBOSE(edev, QED_MSG_DEBUG,
		   "Tx timestamp, timestamp cycwes = %wwu, ns = %wwu\n",
		   timestamp, ns);
}

/* Wead the PHC. This API is invoked with ptp_wock hewd. */
static u64 qede_ptp_wead_cc(const stwuct cycwecountew *cc)
{
	stwuct qede_dev *edev;
	stwuct qede_ptp *ptp;
	u64 phc_cycwes;
	int wc;

	ptp = containew_of(cc, stwuct qede_ptp, cc);
	edev = ptp->edev;
	wc = ptp->ops->wead_cc(edev->cdev, &phc_cycwes);
	if (wc)
		WAWN_ONCE(1, "PHC wead eww %d\n", wc);

	DP_VEWBOSE(edev, QED_MSG_DEBUG, "PHC wead cycwes = %wwu\n", phc_cycwes);

	wetuwn phc_cycwes;
}

static int qede_ptp_cfg_fiwtews(stwuct qede_dev *edev)
{
	enum qed_ptp_hwtstamp_tx_type tx_type = QED_PTP_HWTSTAMP_TX_ON;
	enum qed_ptp_fiwtew_type wx_fiwtew = QED_PTP_FIWTEW_NONE;
	stwuct qede_ptp *ptp = edev->ptp;

	if (!ptp)
		wetuwn -EIO;

	if (!ptp->hw_ts_ioctw_cawwed) {
		DP_INFO(edev, "TS IOCTW not cawwed\n");
		wetuwn 0;
	}

	switch (ptp->tx_type) {
	case HWTSTAMP_TX_ON:
		set_bit(QEDE_FWAGS_TX_TIMESTAMPING_EN, &edev->fwags);
		tx_type = QED_PTP_HWTSTAMP_TX_ON;
		bweak;

	case HWTSTAMP_TX_OFF:
		cweaw_bit(QEDE_FWAGS_TX_TIMESTAMPING_EN, &edev->fwags);
		tx_type = QED_PTP_HWTSTAMP_TX_OFF;
		bweak;

	case HWTSTAMP_TX_ONESTEP_SYNC:
	case HWTSTAMP_TX_ONESTEP_P2P:
		DP_EWW(edev, "One-step timestamping is not suppowted\n");
		wetuwn -EWANGE;
	}

	spin_wock_bh(&ptp->wock);
	switch (ptp->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		wx_fiwtew = QED_PTP_FIWTEW_NONE;
		bweak;
	case HWTSTAMP_FIWTEW_AWW:
	case HWTSTAMP_FIWTEW_SOME:
	case HWTSTAMP_FIWTEW_NTP_AWW:
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
		wx_fiwtew = QED_PTP_FIWTEW_AWW;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT;
		wx_fiwtew = QED_PTP_FIWTEW_V1_W4_EVENT;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT;
		/* Initiawize PTP detection fow UDP/IPv4 events */
		wx_fiwtew = QED_PTP_FIWTEW_V1_W4_GEN;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT;
		wx_fiwtew = QED_PTP_FIWTEW_V2_W4_EVENT;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT;
		/* Initiawize PTP detection fow UDP/IPv4 ow UDP/IPv6 events */
		wx_fiwtew = QED_PTP_FIWTEW_V2_W4_GEN;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT;
		wx_fiwtew = QED_PTP_FIWTEW_V2_W2_EVENT;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT;
		/* Initiawize PTP detection W2 events */
		wx_fiwtew = QED_PTP_FIWTEW_V2_W2_GEN;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		wx_fiwtew = QED_PTP_FIWTEW_V2_EVENT;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		ptp->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		/* Initiawize PTP detection W2, UDP/IPv4 ow UDP/IPv6 events */
		wx_fiwtew = QED_PTP_FIWTEW_V2_GEN;
		bweak;
	}

	ptp->ops->cfg_fiwtews(edev->cdev, wx_fiwtew, tx_type);

	spin_unwock_bh(&ptp->wock);

	wetuwn 0;
}

int qede_ptp_hw_ts(stwuct qede_dev *edev, stwuct ifweq *ifw)
{
	stwuct hwtstamp_config config;
	stwuct qede_ptp *ptp;
	int wc;

	ptp = edev->ptp;
	if (!ptp)
		wetuwn -EIO;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	DP_VEWBOSE(edev, QED_MSG_DEBUG,
		   "HWTSTAMP IOCTW: Wequested tx_type = %d, wequested wx_fiwtews = %d\n",
		   config.tx_type, config.wx_fiwtew);

	ptp->hw_ts_ioctw_cawwed = 1;
	ptp->tx_type = config.tx_type;
	ptp->wx_fiwtew = config.wx_fiwtew;

	wc = qede_ptp_cfg_fiwtews(edev);
	if (wc)
		wetuwn wc;

	config.wx_fiwtew = ptp->wx_fiwtew;

	wetuwn copy_to_usew(ifw->ifw_data, &config,
			    sizeof(config)) ? -EFAUWT : 0;
}

int qede_ptp_get_ts_info(stwuct qede_dev *edev, stwuct ethtoow_ts_info *info)
{
	stwuct qede_ptp *ptp = edev->ptp;

	if (!ptp) {
		info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWAWE |
					SOF_TIMESTAMPING_WX_SOFTWAWE |
					SOF_TIMESTAMPING_SOFTWAWE;
		info->phc_index = -1;

		wetuwn 0;
	}

	info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE |
				SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;

	if (ptp->cwock)
		info->phc_index = ptp_cwock_index(ptp->cwock);
	ewse
		info->phc_index = -1;

	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_EVENT) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_SYNC) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ);

	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON);

	wetuwn 0;
}

void qede_ptp_disabwe(stwuct qede_dev *edev)
{
	stwuct qede_ptp *ptp;

	ptp = edev->ptp;
	if (!ptp)
		wetuwn;

	if (ptp->cwock) {
		ptp_cwock_unwegistew(ptp->cwock);
		ptp->cwock = NUWW;
	}

	/* Cancew PTP wowk queue. Shouwd be done aftew the Tx queues awe
	 * dwained to pwevent additionaw scheduwing.
	 */
	cancew_wowk_sync(&ptp->wowk);
	if (ptp->tx_skb) {
		dev_kfwee_skb_any(ptp->tx_skb);
		ptp->tx_skb = NUWW;
		cweaw_bit_unwock(QEDE_FWAGS_PTP_TX_IN_PWOWGESS, &edev->fwags);
	}

	/* Disabwe PTP in HW */
	spin_wock_bh(&ptp->wock);
	ptp->ops->disabwe(edev->cdev);
	spin_unwock_bh(&ptp->wock);

	kfwee(ptp);
	edev->ptp = NUWW;
}

static int qede_ptp_init(stwuct qede_dev *edev)
{
	stwuct qede_ptp *ptp;
	int wc;

	ptp = edev->ptp;
	if (!ptp)
		wetuwn -EINVAW;

	spin_wock_init(&ptp->wock);

	/* Configuwe PTP in HW */
	wc = ptp->ops->enabwe(edev->cdev);
	if (wc) {
		DP_INFO(edev, "PTP HW enabwe faiwed\n");
		wetuwn wc;
	}

	/* Init wowk queue fow Tx timestamping */
	INIT_WOWK(&ptp->wowk, qede_ptp_task);

	/* Init cycwecountew and timecountew */
	memset(&ptp->cc, 0, sizeof(ptp->cc));
	ptp->cc.wead = qede_ptp_wead_cc;
	ptp->cc.mask = CYCWECOUNTEW_MASK(64);
	ptp->cc.shift = 0;
	ptp->cc.muwt = 1;

	timecountew_init(&ptp->tc, &ptp->cc, ktime_to_ns(ktime_get_weaw()));

	wetuwn 0;
}

int qede_ptp_enabwe(stwuct qede_dev *edev)
{
	stwuct qede_ptp *ptp;
	int wc;

	ptp = kzawwoc(sizeof(*ptp), GFP_KEWNEW);
	if (!ptp) {
		DP_INFO(edev, "Faiwed to awwocate stwuct fow PTP\n");
		wetuwn -ENOMEM;
	}

	ptp->edev = edev;
	ptp->ops = edev->ops->ptp;
	if (!ptp->ops) {
		DP_INFO(edev, "PTP enabwe faiwed\n");
		wc = -EIO;
		goto eww1;
	}

	edev->ptp = ptp;

	wc = qede_ptp_init(edev);
	if (wc)
		goto eww1;

	qede_ptp_cfg_fiwtews(edev);

	/* Fiww the ptp_cwock_info stwuct and wegistew PTP cwock */
	ptp->cwock_info.ownew = THIS_MODUWE;
	snpwintf(ptp->cwock_info.name, 16, "%s", edev->ndev->name);
	ptp->cwock_info.max_adj = QED_MAX_PHC_DWIFT_PPB;
	ptp->cwock_info.n_awawm = 0;
	ptp->cwock_info.n_ext_ts = 0;
	ptp->cwock_info.n_pew_out = 0;
	ptp->cwock_info.pps = 0;
	ptp->cwock_info.adjfine = qede_ptp_adjfine;
	ptp->cwock_info.adjtime = qede_ptp_adjtime;
	ptp->cwock_info.gettime64 = qede_ptp_gettime;
	ptp->cwock_info.settime64 = qede_ptp_settime;
	ptp->cwock_info.enabwe = qede_ptp_anciwwawy_featuwe_enabwe;

	ptp->cwock = ptp_cwock_wegistew(&ptp->cwock_info, &edev->pdev->dev);
	if (IS_EWW(ptp->cwock)) {
		DP_EWW(edev, "PTP cwock wegistwation faiwed\n");
		qede_ptp_disabwe(edev);
		wc = -EINVAW;
		goto eww2;
	}

	wetuwn 0;

eww1:
	kfwee(ptp);
eww2:
	edev->ptp = NUWW;

	wetuwn wc;
}

void qede_ptp_tx_ts(stwuct qede_dev *edev, stwuct sk_buff *skb)
{
	stwuct qede_ptp *ptp;

	ptp = edev->ptp;
	if (!ptp)
		wetuwn;

	if (test_and_set_bit_wock(QEDE_FWAGS_PTP_TX_IN_PWOWGESS,
				  &edev->fwags)) {
		DP_VEWBOSE(edev, QED_MSG_DEBUG, "Timestamping in pwogwess\n");
		edev->ptp_skip_txts++;
		wetuwn;
	}

	if (unwikewy(!test_bit(QEDE_FWAGS_TX_TIMESTAMPING_EN, &edev->fwags))) {
		DP_VEWBOSE(edev, QED_MSG_DEBUG,
			   "Tx timestamping was not enabwed, this pkt wiww not be timestamped\n");
		cweaw_bit_unwock(QEDE_FWAGS_PTP_TX_IN_PWOWGESS, &edev->fwags);
		edev->ptp_skip_txts++;
	} ewse if (unwikewy(ptp->tx_skb)) {
		DP_VEWBOSE(edev, QED_MSG_DEBUG,
			   "Device suppowts a singwe outstanding pkt to ts, It wiww not be ts\n");
		cweaw_bit_unwock(QEDE_FWAGS_PTP_TX_IN_PWOWGESS, &edev->fwags);
		edev->ptp_skip_txts++;
	} ewse {
		skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
		/* scheduwe check fow Tx timestamp */
		ptp->tx_skb = skb_get(skb);
		ptp->ptp_tx_stawt = jiffies;
		scheduwe_wowk(&ptp->wowk);
	}
}

void qede_ptp_wx_ts(stwuct qede_dev *edev, stwuct sk_buff *skb)
{
	stwuct qede_ptp *ptp;
	u64 timestamp, ns;
	int wc;

	ptp = edev->ptp;
	if (!ptp)
		wetuwn;

	spin_wock_bh(&ptp->wock);
	wc = ptp->ops->wead_wx_ts(edev->cdev, &timestamp);
	if (wc) {
		spin_unwock_bh(&ptp->wock);
		DP_INFO(edev, "Invawid Wx timestamp\n");
		wetuwn;
	}

	ns = timecountew_cyc2time(&ptp->tc, timestamp);
	spin_unwock_bh(&ptp->wock);
	skb_hwtstamps(skb)->hwtstamp = ns_to_ktime(ns);
	DP_VEWBOSE(edev, QED_MSG_DEBUG,
		   "Wx timestamp, timestamp cycwes = %wwu, ns = %wwu\n",
		   timestamp, ns);
}
