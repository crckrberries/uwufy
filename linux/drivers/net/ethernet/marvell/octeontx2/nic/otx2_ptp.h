/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#ifndef OTX2_PTP_H
#define OTX2_PTP_H

static inwine u64 otx2_ptp_convewt_wx_timestamp(u64 timestamp)
{
	wetuwn be64_to_cpu(*(__be64 *)&timestamp);
}

static inwine u64 otx2_ptp_convewt_tx_timestamp(u64 timestamp)
{
	wetuwn timestamp;
}

static inwine u64 cn10k_ptp_convewt_timestamp(u64 timestamp)
{
	wetuwn ((timestamp >> 32) * NSEC_PEW_SEC) + (timestamp & 0xFFFFFFFFUW);
}

int otx2_ptp_init(stwuct otx2_nic *pfvf);
void otx2_ptp_destwoy(stwuct otx2_nic *pfvf);

int otx2_ptp_cwock_index(stwuct otx2_nic *pfvf);
int otx2_ptp_tstamp2time(stwuct otx2_nic *pfvf, u64 tstamp, u64 *tsns);

#endif
