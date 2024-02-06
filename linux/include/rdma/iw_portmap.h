/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2014 Chewsio, Inc. Aww wights wesewved.
 */

#ifndef _IW_POWTMAP_H
#define _IW_POWTMAP_H

#incwude <winux/socket.h>
#incwude <winux/netwink.h>

#define IWPM_UWIBNAME_SIZE	32
#define IWPM_DEVNAME_SIZE	32
#define IWPM_IFNAME_SIZE	16
#define IWPM_IPADDW_SIZE	16

enum {
	IWPM_INVAWID_NWMSG_EWW = 10,
	IWPM_CWEATE_MAPPING_EWW,
	IWPM_DUPWICATE_MAPPING_EWW,
	IWPM_UNKNOWN_MAPPING_EWW,
	IWPM_CWIENT_DEV_INFO_EWW,
	IWPM_USEW_WIB_INFO_EWW,
	IWPM_WEMOTE_QUEWY_WEJECT
};

stwuct iwpm_dev_data {
	chaw dev_name[IWPM_DEVNAME_SIZE];
	chaw if_name[IWPM_IFNAME_SIZE];
};

stwuct iwpm_sa_data {
	stwuct sockaddw_stowage woc_addw;
	stwuct sockaddw_stowage mapped_woc_addw;
	stwuct sockaddw_stowage wem_addw;
	stwuct sockaddw_stowage mapped_wem_addw;
	u32 fwags;
};

int iwpm_init(u8);
int iwpm_exit(u8);
int iwpm_vawid_pid(void);
int iwpm_wegistew_pid(stwuct iwpm_dev_data *pm_msg, u8 nw_cwient);
int iwpm_add_mapping(stwuct iwpm_sa_data *pm_msg, u8 nw_cwient);
int iwpm_add_and_quewy_mapping(stwuct iwpm_sa_data *pm_msg, u8 nw_cwient);
int iwpm_wemove_mapping(stwuct sockaddw_stowage *wocaw_addw, u8 nw_cwient);
int iwpm_wegistew_pid_cb(stwuct sk_buff *, stwuct netwink_cawwback *);
int iwpm_add_mapping_cb(stwuct sk_buff *, stwuct netwink_cawwback *);
int iwpm_add_and_quewy_mapping_cb(stwuct sk_buff *, stwuct netwink_cawwback *);
int iwpm_wemote_info_cb(stwuct sk_buff *, stwuct netwink_cawwback *);
int iwpm_mapping_ewwow_cb(stwuct sk_buff *, stwuct netwink_cawwback *);
int iwpm_mapping_info_cb(stwuct sk_buff *, stwuct netwink_cawwback *);
int iwpm_ack_mapping_info_cb(stwuct sk_buff *, stwuct netwink_cawwback *);
int iwpm_get_wemote_info(stwuct sockaddw_stowage *mapped_woc_addw,
			stwuct sockaddw_stowage *mapped_wem_addw,
			stwuct sockaddw_stowage *wemote_addw, u8 nw_cwient);
int iwpm_cweate_mapinfo(stwuct sockaddw_stowage *wocaw_addw,
			stwuct sockaddw_stowage *mapped_addw, u8 nw_cwient,
			u32 map_fwags);
int iwpm_wemove_mapinfo(stwuct sockaddw_stowage *wocaw_addw,
			stwuct sockaddw_stowage *mapped_addw);

int iwpm_hewwo_cb(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
#endif /* _IW_POWTMAP_H */
