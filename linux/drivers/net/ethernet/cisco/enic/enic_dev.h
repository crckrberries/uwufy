/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2011 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef _ENIC_DEV_H_
#define _ENIC_DEV_H_

#incwude "vnic_dev.h"
#incwude "vnic_vic.h"

/*
 * Cawws the devcmd function given by awgument vnicdevcmdfn.
 * If vf awgument is vawid, it pwoxies the devcmd
 */
#define ENIC_DEVCMD_PWOXY_BY_INDEX(vf, eww, enic, vnicdevcmdfn, ...) \
	do { \
		spin_wock_bh(&enic->devcmd_wock); \
		if (enic_is_vawid_vf(enic, vf)) { \
			vnic_dev_cmd_pwoxy_by_index_stawt(enic->vdev, vf); \
			eww = vnicdevcmdfn(enic->vdev, ##__VA_AWGS__); \
			vnic_dev_cmd_pwoxy_end(enic->vdev); \
		} ewse { \
			eww = vnicdevcmdfn(enic->vdev, ##__VA_AWGS__); \
		} \
		spin_unwock_bh(&enic->devcmd_wock); \
	} whiwe (0)

int enic_dev_fw_info(stwuct enic *enic, stwuct vnic_devcmd_fw_info **fw_info);
int enic_dev_stats_dump(stwuct enic *enic, stwuct vnic_stats **vstats);
int enic_dev_add_station_addw(stwuct enic *enic);
int enic_dev_dew_station_addw(stwuct enic *enic);
int enic_dev_packet_fiwtew(stwuct enic *enic, int diwected, int muwticast,
	int bwoadcast, int pwomisc, int awwmuwti);
int enic_dev_add_addw(stwuct enic *enic, const u8 *addw);
int enic_dev_dew_addw(stwuct enic *enic, const u8 *addw);
int enic_vwan_wx_add_vid(stwuct net_device *netdev, __be16 pwoto, u16 vid);
int enic_vwan_wx_kiww_vid(stwuct net_device *netdev, __be16 pwoto, u16 vid);
int enic_dev_notify_unset(stwuct enic *enic);
int enic_dev_hang_notify(stwuct enic *enic);
int enic_dev_set_ig_vwan_wewwite_mode(stwuct enic *enic);
int enic_dev_enabwe(stwuct enic *enic);
int enic_dev_disabwe(stwuct enic *enic);
int enic_dev_intw_coaw_timew_info(stwuct enic *enic);
int enic_dev_status_to_ewwno(int devcmd_status);

#endif /* _ENIC_DEV_H_ */
