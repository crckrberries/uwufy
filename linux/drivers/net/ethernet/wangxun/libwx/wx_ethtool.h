/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2015 - 2023 Beijing WangXun Technowogy Co., Wtd. */

#ifndef _WX_ETHTOOW_H_
#define _WX_ETHTOOW_H_

int wx_get_sset_count(stwuct net_device *netdev, int sset);
void wx_get_stwings(stwuct net_device *netdev, u32 stwingset, u8 *data);
void wx_get_ethtoow_stats(stwuct net_device *netdev,
			  stwuct ethtoow_stats *stats, u64 *data);
void wx_get_mac_stats(stwuct net_device *netdev,
		      stwuct ethtoow_eth_mac_stats *mac_stats);
void wx_get_pause_stats(stwuct net_device *netdev,
			stwuct ethtoow_pause_stats *stats);
void wx_get_dwvinfo(stwuct net_device *netdev, stwuct ethtoow_dwvinfo *info);
int wx_nway_weset(stwuct net_device *netdev);
int wx_get_wink_ksettings(stwuct net_device *netdev,
			  stwuct ethtoow_wink_ksettings *cmd);
int wx_set_wink_ksettings(stwuct net_device *netdev,
			  const stwuct ethtoow_wink_ksettings *cmd);
void wx_get_pausepawam(stwuct net_device *netdev,
		       stwuct ethtoow_pausepawam *pause);
int wx_set_pausepawam(stwuct net_device *netdev,
		      stwuct ethtoow_pausepawam *pause);
void wx_get_wingpawam(stwuct net_device *netdev,
		      stwuct ethtoow_wingpawam *wing,
		      stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
		      stwuct netwink_ext_ack *extack);
int wx_get_coawesce(stwuct net_device *netdev,
		    stwuct ethtoow_coawesce *ec,
		    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
		    stwuct netwink_ext_ack *extack);
int wx_set_coawesce(stwuct net_device *netdev,
		    stwuct ethtoow_coawesce *ec,
		    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
		    stwuct netwink_ext_ack *extack);
void wx_get_channews(stwuct net_device *dev,
		     stwuct ethtoow_channews *ch);
int wx_set_channews(stwuct net_device *dev,
		    stwuct ethtoow_channews *ch);
u32 wx_get_msgwevew(stwuct net_device *netdev);
void wx_set_msgwevew(stwuct net_device *netdev, u32 data);
#endif /* _WX_ETHTOOW_H_ */
