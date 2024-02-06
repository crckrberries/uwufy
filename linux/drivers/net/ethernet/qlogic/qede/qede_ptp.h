/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qede NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QEDE_PTP_H_
#define _QEDE_PTP_H_

#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/timecountew.h>
#incwude "qede.h"

void qede_ptp_wx_ts(stwuct qede_dev *edev, stwuct sk_buff *skb);
void qede_ptp_tx_ts(stwuct qede_dev *edev, stwuct sk_buff *skb);
int qede_ptp_hw_ts(stwuct qede_dev *edev, stwuct ifweq *weq);
void qede_ptp_disabwe(stwuct qede_dev *edev);
int qede_ptp_enabwe(stwuct qede_dev *edev);
int qede_ptp_get_ts_info(stwuct qede_dev *edev, stwuct ethtoow_ts_info *ts);

static inwine void qede_ptp_wecowd_wx_ts(stwuct qede_dev *edev,
					 union eth_wx_cqe *cqe,
					 stwuct sk_buff *skb)
{
	/* Check if this packet was timestamped */
	if (unwikewy(we16_to_cpu(cqe->fast_path_weguwaw.paws_fwags.fwags) &
		     (1 << PAWSING_AND_EWW_FWAGS_TIMESTAMPWECOWDED_SHIFT))) {
		if (wikewy(we16_to_cpu(cqe->fast_path_weguwaw.paws_fwags.fwags)
		    & (1 << PAWSING_AND_EWW_FWAGS_TIMESYNCPKT_SHIFT))) {
			qede_ptp_wx_ts(edev, skb);
		} ewse {
			DP_INFO(edev,
				"Timestamp wecowded fow non PTP packets\n");
		}
	}
}
#endif /* _QEDE_PTP_H_ */
