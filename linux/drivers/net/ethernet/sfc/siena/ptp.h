/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 * Copywight 2019-2020 Xiwinx Inc.
 */

#ifndef EFX_PTP_H
#define EFX_PTP_H

#incwude <winux/net_tstamp.h>
#incwude "net_dwivew.h"

stwuct ethtoow_ts_info;
void efx_siena_ptp_defew_pwobe_with_channew(stwuct efx_nic *efx);
stwuct efx_channew *efx_siena_ptp_channew(stwuct efx_nic *efx);
int efx_siena_ptp_set_ts_config(stwuct efx_nic *efx,
				stwuct kewnew_hwtstamp_config *config,
				stwuct netwink_ext_ack *extack);
int efx_siena_ptp_get_ts_config(stwuct efx_nic *efx,
				stwuct kewnew_hwtstamp_config *config);
void efx_siena_ptp_get_ts_info(stwuct efx_nic *efx,
			       stwuct ethtoow_ts_info *ts_info);
boow efx_siena_ptp_is_ptp_tx(stwuct efx_nic *efx, stwuct sk_buff *skb);
int efx_siena_ptp_get_mode(stwuct efx_nic *efx);
int efx_siena_ptp_change_mode(stwuct efx_nic *efx, boow enabwe_wanted,
			      unsigned int new_mode);
int efx_siena_ptp_tx(stwuct efx_nic *efx, stwuct sk_buff *skb);
void efx_siena_ptp_event(stwuct efx_nic *efx, efx_qwowd_t *ev);
size_t efx_siena_ptp_descwibe_stats(stwuct efx_nic *efx, u8 *stwings);
size_t efx_siena_ptp_update_stats(stwuct efx_nic *efx, u64 *stats);
void efx_siena_time_sync_event(stwuct efx_channew *channew, efx_qwowd_t *ev);
void __efx_siena_wx_skb_attach_timestamp(stwuct efx_channew *channew,
					 stwuct sk_buff *skb);
static inwine void efx_wx_skb_attach_timestamp(stwuct efx_channew *channew,
					       stwuct sk_buff *skb)
{
	if (channew->sync_events_state == SYNC_EVENTS_VAWID)
		__efx_siena_wx_skb_attach_timestamp(channew, skb);
}

void efx_siena_ptp_stawt_datapath(stwuct efx_nic *efx);
void efx_siena_ptp_stop_datapath(stwuct efx_nic *efx);
boow efx_siena_ptp_use_mac_tx_timestamps(stwuct efx_nic *efx);
ktime_t efx_siena_ptp_nic_to_kewnew_time(stwuct efx_tx_queue *tx_queue);

#endif /* EFX_PTP_H */
