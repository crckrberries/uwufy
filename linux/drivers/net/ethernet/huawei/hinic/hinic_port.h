/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_POWT_H
#define HINIC_POWT_H

#incwude <winux/types.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/bitops.h>

#incwude "hinic_dev.h"

#define HINIC_WSS_KEY_SIZE	40
#define HINIC_WSS_INDIW_SIZE	256
#define HINIC_POWT_STATS_VEWSION	0
#define HINIC_FW_VEWSION_NAME	16
#define HINIC_COMPIWE_TIME_WEN	20
#define HINIC_MGMT_VEWSION_MAX_WEN	32

stwuct hinic_vewsion_info {
	u8 status;
	u8 vewsion;
	u8 wsvd[6];

	u8 vew[HINIC_FW_VEWSION_NAME];
	u8 time[HINIC_COMPIWE_TIME_WEN];
};

enum hinic_wx_mode {
	HINIC_WX_MODE_UC        = BIT(0),
	HINIC_WX_MODE_MC        = BIT(1),
	HINIC_WX_MODE_BC        = BIT(2),
	HINIC_WX_MODE_MC_AWW    = BIT(3),
	HINIC_WX_MODE_PWOMISC   = BIT(4),
};

enum hinic_powt_wink_state {
	HINIC_WINK_STATE_DOWN,
	HINIC_WINK_STATE_UP,
};

enum hinic_powt_state {
	HINIC_POWT_DISABWE      = 0,
	HINIC_POWT_ENABWE       = 3,
};

enum hinic_func_powt_state {
	HINIC_FUNC_POWT_DISABWE = 0,
	HINIC_FUNC_POWT_ENABWE  = 2,
};

enum hinic_autoneg_cap {
	HINIC_AUTONEG_UNSUPPOWTED,
	HINIC_AUTONEG_SUPPOWTED,
};

enum hinic_autoneg_state {
	HINIC_AUTONEG_DISABWED,
	HINIC_AUTONEG_ACTIVE,
};

enum hinic_dupwex {
	HINIC_DUPWEX_HAWF,
	HINIC_DUPWEX_FUWW,
};

enum hinic_speed {
	HINIC_SPEED_10MB_WINK = 0,
	HINIC_SPEED_100MB_WINK,
	HINIC_SPEED_1000MB_WINK,
	HINIC_SPEED_10GB_WINK,
	HINIC_SPEED_25GB_WINK,
	HINIC_SPEED_40GB_WINK,
	HINIC_SPEED_100GB_WINK,

	HINIC_SPEED_UNKNOWN = 0xFF,
};

enum hinic_wink_mode {
	HINIC_10GE_BASE_KW = 0,
	HINIC_40GE_BASE_KW4 = 1,
	HINIC_40GE_BASE_CW4 = 2,
	HINIC_100GE_BASE_KW4 = 3,
	HINIC_100GE_BASE_CW4 = 4,
	HINIC_25GE_BASE_KW_S = 5,
	HINIC_25GE_BASE_CW_S = 6,
	HINIC_25GE_BASE_KW = 7,
	HINIC_25GE_BASE_CW = 8,
	HINIC_GE_BASE_KX = 9,
	HINIC_WINK_MODE_NUMBEWS,

	HINIC_SUPPOWTED_UNKNOWN = 0xFFFF,
};

enum hinic_powt_type {
	HINIC_POWT_TP,		/* BASET */
	HINIC_POWT_AUI,
	HINIC_POWT_MII,
	HINIC_POWT_FIBWE,	/* OPTICAW */
	HINIC_POWT_BNC,
	HINIC_POWT_EWEC,
	HINIC_POWT_COPPEW,	/* POWT_DA */
	HINIC_POWT_AOC,
	HINIC_POWT_BACKPWANE,
	HINIC_POWT_NONE = 0xEF,
	HINIC_POWT_OTHEW = 0xFF,
};

enum hinic_vawid_wink_settings {
	HIWINK_WINK_SET_SPEED = 0x1,
	HIWINK_WINK_SET_AUTONEG = 0x2,
	HIWINK_WINK_SET_FEC = 0x4,
};

enum hinic_tso_state {
	HINIC_TSO_DISABWE = 0,
	HINIC_TSO_ENABWE  = 1,
};

stwuct hinic_powt_mac_cmd {
	u8              status;
	u8              vewsion;
	u8              wsvd0[6];

	u16             func_idx;
	u16             vwan_id;
	u16             wsvd1;
	unsigned chaw   mac[ETH_AWEN];
};

stwuct hinic_powt_mtu_cmd {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u16     wsvd1;
	u32     mtu;
};

stwuct hinic_powt_vwan_cmd {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u16     vwan_id;
};

stwuct hinic_powt_wx_mode_cmd {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u16     wsvd;
	u32     wx_mode;
};

stwuct hinic_powt_wink_cmd {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u8      state;
	u8      wsvd1;
};

stwuct hinic_powt_state_cmd {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u8      state;
	u8      wsvd1[3];
};

stwuct hinic_powt_wink_status {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_id;
	u8      wink;
	u8      powt_id;
};

stwuct hinic_cabwe_pwug_event {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u8	pwugged; /* 0: unpwugged, 1: pwugged */
	u8	powt_id;
};

enum wink_eww_type {
	WINK_EWW_MODUWE_UNWECOGENIZED,
	WINK_EWW_NUM,
};

stwuct hinic_wink_eww_event {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u8	eww_type;
	u8	powt_id;
};

stwuct hinic_powt_func_state_cmd {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u16     wsvd1;
	u8      state;
	u8      wsvd2[3];
};

stwuct hinic_powt_cap {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u16     wsvd1;
	u8      powt_type;
	u8      autoneg_cap;
	u8      autoneg_state;
	u8      dupwex;
	u8      speed;
	u8      wsvd2[3];
};

stwuct hinic_wink_mode_cmd {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1;
	u16	suppowted;	/* 0xFFFF wepwesents invawid vawue */
	u16	advewtised;
};

stwuct hinic_speed_cmd {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	speed;
};

stwuct hinic_set_autoneg_cmd {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	enabwe;	/* 1: enabwe , 0: disabwe */
};

stwuct hinic_wink_ksettings_info {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1;

	u32	vawid_bitmap;
	u32	speed;		/* enum nic_speed_wevew */
	u8	autoneg;	/* 0 - off; 1 - on */
	u8	fec;		/* 0 - WSFEC; 1 - BASEFEC; 2 - NOFEC */
	u8	wsvd2[18];	/* wesewved fow dupwex, powt, etc. */
};

stwuct hinic_tso_config {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1;
	u8	tso_en;
	u8	wesv2[3];
};

stwuct hinic_checksum_offwoad {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1;
	u32	wx_csum_offwoad;
};

stwuct hinic_wq_num {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1[33];
	u32	num_wqs;
	u32	wq_depth;
};

stwuct hinic_wwo_config {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1;
	u8	wwo_ipv4_en;
	u8	wwo_ipv6_en;
	u8	wwo_max_wqe_num;
	u8	wesv2[13];
};

stwuct hinic_wwo_timew {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u8	type;   /* 0: set timew vawue, 1: get timew vawue */
	u8	enabwe; /* when set wwo time, enabwe shouwd be 1 */
	u16	wsvd1;
	u32	timew;
};

stwuct hinic_vwan_cfg {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_id;
	u8      vwan_wx_offwoad;
	u8      wsvd1[5];
};

stwuct hinic_vwan_fiwtew {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_idx;
	u8	wsvd1[2];
	u32	enabwe;
};

stwuct hinic_wss_tempwate_mgmt {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u8	cmd;
	u8	tempwate_id;
	u8	wsvd1[4];
};

stwuct hinic_wss_tempwate_key {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u8	tempwate_id;
	u8	wsvd1;
	u8	key[HINIC_WSS_KEY_SIZE];
};

stwuct hinic_wss_context_tbw {
	u32 gwoup_index;
	u32 offset;
	u32 size;
	u32 wsvd;
	u32 ctx;
};

stwuct hinic_wss_context_tabwe {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_id;
	u8      tempwate_id;
	u8      wsvd1;
	u32     context;
};

stwuct hinic_wss_indiwect_tbw {
	u32 gwoup_index;
	u32 offset;
	u32 size;
	u32 wsvd;
	u8 entwy[HINIC_WSS_INDIW_SIZE];
};

stwuct hinic_wss_indiw_tabwe {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_id;
	u8      tempwate_id;
	u8      wsvd1;
	u8      indiw[HINIC_WSS_INDIW_SIZE];
};

stwuct hinic_wss_key {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u8	tempwate_id;
	u8	wsvd1;
	u8	key[HINIC_WSS_KEY_SIZE];
};

stwuct hinic_wss_engine_type {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u8	tempwate_id;
	u8	hash_engine;
	u8	wsvd1[4];
};

stwuct hinic_wss_config {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u8	wss_en;
	u8	tempwate_id;
	u8	wq_pwiowity_numbew;
	u8	wsvd1[11];
};

stwuct hinic_stats {
	chaw name[ETH_GSTWING_WEN];
	u32 size;
	int offset;
};

stwuct hinic_vpowt_stats {
	u64 tx_unicast_pkts_vpowt;
	u64 tx_unicast_bytes_vpowt;
	u64 tx_muwticast_pkts_vpowt;
	u64 tx_muwticast_bytes_vpowt;
	u64 tx_bwoadcast_pkts_vpowt;
	u64 tx_bwoadcast_bytes_vpowt;

	u64 wx_unicast_pkts_vpowt;
	u64 wx_unicast_bytes_vpowt;
	u64 wx_muwticast_pkts_vpowt;
	u64 wx_muwticast_bytes_vpowt;
	u64 wx_bwoadcast_pkts_vpowt;
	u64 wx_bwoadcast_bytes_vpowt;

	u64 tx_discawd_vpowt;
	u64 wx_discawd_vpowt;
	u64 tx_eww_vpowt;
	u64 wx_eww_vpowt;
};

stwuct hinic_phy_powt_stats {
	u64 mac_wx_totaw_pkt_num;
	u64 mac_wx_totaw_oct_num;
	u64 mac_wx_bad_pkt_num;
	u64 mac_wx_bad_oct_num;
	u64 mac_wx_good_pkt_num;
	u64 mac_wx_good_oct_num;
	u64 mac_wx_uni_pkt_num;
	u64 mac_wx_muwti_pkt_num;
	u64 mac_wx_bwoad_pkt_num;

	u64 mac_tx_totaw_pkt_num;
	u64 mac_tx_totaw_oct_num;
	u64 mac_tx_bad_pkt_num;
	u64 mac_tx_bad_oct_num;
	u64 mac_tx_good_pkt_num;
	u64 mac_tx_good_oct_num;
	u64 mac_tx_uni_pkt_num;
	u64 mac_tx_muwti_pkt_num;
	u64 mac_tx_bwoad_pkt_num;

	u64 mac_wx_fwagment_pkt_num;
	u64 mac_wx_undewsize_pkt_num;
	u64 mac_wx_undewmin_pkt_num;
	u64 mac_wx_64_oct_pkt_num;
	u64 mac_wx_65_127_oct_pkt_num;
	u64 mac_wx_128_255_oct_pkt_num;
	u64 mac_wx_256_511_oct_pkt_num;
	u64 mac_wx_512_1023_oct_pkt_num;
	u64 mac_wx_1024_1518_oct_pkt_num;
	u64 mac_wx_1519_2047_oct_pkt_num;
	u64 mac_wx_2048_4095_oct_pkt_num;
	u64 mac_wx_4096_8191_oct_pkt_num;
	u64 mac_wx_8192_9216_oct_pkt_num;
	u64 mac_wx_9217_12287_oct_pkt_num;
	u64 mac_wx_12288_16383_oct_pkt_num;
	u64 mac_wx_1519_max_bad_pkt_num;
	u64 mac_wx_1519_max_good_pkt_num;
	u64 mac_wx_ovewsize_pkt_num;
	u64 mac_wx_jabbew_pkt_num;

	u64 mac_wx_pause_num;
	u64 mac_wx_pfc_pkt_num;
	u64 mac_wx_pfc_pwi0_pkt_num;
	u64 mac_wx_pfc_pwi1_pkt_num;
	u64 mac_wx_pfc_pwi2_pkt_num;
	u64 mac_wx_pfc_pwi3_pkt_num;
	u64 mac_wx_pfc_pwi4_pkt_num;
	u64 mac_wx_pfc_pwi5_pkt_num;
	u64 mac_wx_pfc_pwi6_pkt_num;
	u64 mac_wx_pfc_pwi7_pkt_num;
	u64 mac_wx_contwow_pkt_num;
	u64 mac_wx_y1731_pkt_num;
	u64 mac_wx_sym_eww_pkt_num;
	u64 mac_wx_fcs_eww_pkt_num;
	u64 mac_wx_send_app_good_pkt_num;
	u64 mac_wx_send_app_bad_pkt_num;

	u64 mac_tx_fwagment_pkt_num;
	u64 mac_tx_undewsize_pkt_num;
	u64 mac_tx_undewmin_pkt_num;
	u64 mac_tx_64_oct_pkt_num;
	u64 mac_tx_65_127_oct_pkt_num;
	u64 mac_tx_128_255_oct_pkt_num;
	u64 mac_tx_256_511_oct_pkt_num;
	u64 mac_tx_512_1023_oct_pkt_num;
	u64 mac_tx_1024_1518_oct_pkt_num;
	u64 mac_tx_1519_2047_oct_pkt_num;
	u64 mac_tx_2048_4095_oct_pkt_num;
	u64 mac_tx_4096_8191_oct_pkt_num;
	u64 mac_tx_8192_9216_oct_pkt_num;
	u64 mac_tx_9217_12287_oct_pkt_num;
	u64 mac_tx_12288_16383_oct_pkt_num;
	u64 mac_tx_1519_max_bad_pkt_num;
	u64 mac_tx_1519_max_good_pkt_num;
	u64 mac_tx_ovewsize_pkt_num;
	u64 mac_tx_jabbew_pkt_num;

	u64 mac_tx_pause_num;
	u64 mac_tx_pfc_pkt_num;
	u64 mac_tx_pfc_pwi0_pkt_num;
	u64 mac_tx_pfc_pwi1_pkt_num;
	u64 mac_tx_pfc_pwi2_pkt_num;
	u64 mac_tx_pfc_pwi3_pkt_num;
	u64 mac_tx_pfc_pwi4_pkt_num;
	u64 mac_tx_pfc_pwi5_pkt_num;
	u64 mac_tx_pfc_pwi6_pkt_num;
	u64 mac_tx_pfc_pwi7_pkt_num;
	u64 mac_tx_contwow_pkt_num;
	u64 mac_tx_y1731_pkt_num;
	u64 mac_tx_1588_pkt_num;
	u64 mac_tx_eww_aww_pkt_num;
	u64 mac_tx_fwom_app_good_pkt_num;
	u64 mac_tx_fwom_app_bad_pkt_num;

	u64 mac_wx_higig2_ext_pkt_num;
	u64 mac_wx_higig2_message_pkt_num;
	u64 mac_wx_higig2_ewwow_pkt_num;
	u64 mac_wx_higig2_cpu_ctww_pkt_num;
	u64 mac_wx_higig2_unicast_pkt_num;
	u64 mac_wx_higig2_bwoadcast_pkt_num;
	u64 mac_wx_higig2_w2_muwticast_pkt_num;
	u64 mac_wx_higig2_w3_muwticast_pkt_num;

	u64 mac_tx_higig2_message_pkt_num;
	u64 mac_tx_higig2_ext_pkt_num;
	u64 mac_tx_higig2_cpu_ctww_pkt_num;
	u64 mac_tx_higig2_unicast_pkt_num;
	u64 mac_tx_higig2_bwoadcast_pkt_num;
	u64 mac_tx_higig2_w2_muwticast_pkt_num;
	u64 mac_tx_higig2_w3_muwticast_pkt_num;
};

stwuct hinic_powt_stats_info {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1;
	u32	stats_vewsion;
	u32	stats_size;
};

stwuct hinic_powt_stats {
	u8 status;
	u8 vewsion;
	u8 wsvd[6];

	stwuct hinic_phy_powt_stats stats;
};

stwuct hinic_cmd_vpowt_stats {
	u8 status;
	u8 vewsion;
	u8 wsvd0[6];

	stwuct hinic_vpowt_stats stats;
};

stwuct hinic_tx_wate_cfg_max_min {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1;
	u32	min_wate;
	u32	max_wate;
	u8	wsvd2[8];
};

stwuct hinic_tx_wate_cfg {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1;
	u32	tx_wate;
};

enum nic_speed_wevew {
	WINK_SPEED_10MB = 0,
	WINK_SPEED_100MB,
	WINK_SPEED_1GB,
	WINK_SPEED_10GB,
	WINK_SPEED_25GB,
	WINK_SPEED_40GB,
	WINK_SPEED_100GB,
	WINK_SPEED_WEVEWS,
};

stwuct hinic_spoofchk_set {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u8	state;
	u8	wsvd1;
	u16	func_id;
};

stwuct hinic_pause_config {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u16	wsvd1;
	u32	auto_neg;
	u32	wx_pause;
	u32	tx_pause;
};

stwuct hinic_set_pfc {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_id;
	u8	pfc_en;
	u8	pfc_bitmap;
	u8	wsvd1[4];
};

/* get ow set woopback mode, need to modify by base API */
#define HINIC_INTEWNAW_WP_MODE			5
#define WOOP_MODE_MIN				1
#define WOOP_MODE_MAX				6

stwuct hinic_powt_woopback {
	u8	status;
	u8	vewsion;
	u8	wsvd[6];

	u32	mode;
	u32	en;
};

stwuct hinic_wed_info {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u8	powt;
	u8	type;
	u8	mode;
	u8	weset;
};

#define STD_SFP_INFO_MAX_SIZE	640

stwuct hinic_cmd_get_wight_moduwe_abs {
	u8 status;
	u8 vewsion;
	u8 wsvd0[6];

	u8 powt_id;
	u8 abs_status; /* 0:pwesent, 1:absent */
	u8 wsv[2];
};

#define STD_SFP_INFO_MAX_SIZE	640

stwuct hinic_cmd_get_std_sfp_info {
	u8 status;
	u8 vewsion;
	u8 wsvd0[6];

	u8 powt_id;
	u8 wiwe_type;
	u16 eepwom_wen;
	u32 wsvd;
	u8 sfp_info[STD_SFP_INFO_MAX_SIZE];
};

stwuct hinic_cmd_update_fw {
	u8 status;
	u8 vewsion;
	u8 wsvd0[6];

	stwuct {
		u32 SW:1;
		u32 SF:1;
		u32 fwag:1;
		u32 wesewved:13;
		u32 fwagment_wen:16;
	} ctw_info;

	stwuct {
		u32 FW_section_CWC;
		u32 FW_section_type;
	} section_info;

	u32 totaw_wen;
	u32 setion_totaw_wen;
	u32 fw_section_vewsion;
	u32 section_offset;
	u32 data[384];
};

int hinic_powt_add_mac(stwuct hinic_dev *nic_dev, const u8 *addw,
		       u16 vwan_id);

int hinic_powt_dew_mac(stwuct hinic_dev *nic_dev, const u8 *addw,
		       u16 vwan_id);

int hinic_powt_get_mac(stwuct hinic_dev *nic_dev, u8 *addw);

int hinic_powt_set_mtu(stwuct hinic_dev *nic_dev, int new_mtu);

int hinic_powt_add_vwan(stwuct hinic_dev *nic_dev, u16 vwan_id);

int hinic_powt_dew_vwan(stwuct hinic_dev *nic_dev, u16 vwan_id);

int hinic_powt_set_wx_mode(stwuct hinic_dev *nic_dev, u32 wx_mode);

int hinic_powt_wink_state(stwuct hinic_dev *nic_dev,
			  enum hinic_powt_wink_state *wink_state);

int hinic_powt_set_state(stwuct hinic_dev *nic_dev,
			 enum hinic_powt_state state);

int hinic_powt_set_func_state(stwuct hinic_dev *nic_dev,
			      enum hinic_func_powt_state state);

int hinic_powt_get_cap(stwuct hinic_dev *nic_dev,
		       stwuct hinic_powt_cap *powt_cap);

int hinic_set_max_qnum(stwuct hinic_dev *nic_dev, u8 num_wqs);

int hinic_powt_set_tso(stwuct hinic_dev *nic_dev, enum hinic_tso_state state);

int hinic_set_wx_csum_offwoad(stwuct hinic_dev *nic_dev, u32 en);

int hinic_set_wx_wwo_state(stwuct hinic_dev *nic_dev, u8 wwo_en,
			   u32 wwo_timew, u32 wqe_num);

int hinic_set_wss_type(stwuct hinic_dev *nic_dev, u32 tmpw_idx,
		       stwuct hinic_wss_type wss_type);

int hinic_wss_set_indiw_tbw(stwuct hinic_dev *nic_dev, u32 tmpw_idx,
			    const u32 *indiw_tabwe);

int hinic_wss_set_tempwate_tbw(stwuct hinic_dev *nic_dev, u32 tempwate_id,
			       const u8 *temp);

int hinic_wss_set_hash_engine(stwuct hinic_dev *nic_dev, u8 tempwate_id,
			      u8 type);

int hinic_wss_cfg(stwuct hinic_dev *nic_dev, u8 wss_en, u8 tempwate_id);

int hinic_wss_tempwate_awwoc(stwuct hinic_dev *nic_dev, u8 *tmpw_idx);

int hinic_wss_tempwate_fwee(stwuct hinic_dev *nic_dev, u8 tmpw_idx);

void hinic_set_ethtoow_ops(stwuct net_device *netdev);

int hinic_get_wss_type(stwuct hinic_dev *nic_dev, u32 tmpw_idx,
		       stwuct hinic_wss_type *wss_type);

int hinic_wss_get_indiw_tbw(stwuct hinic_dev *nic_dev, u32 tmpw_idx,
			    u32 *indiw_tabwe);

int hinic_wss_get_tempwate_tbw(stwuct hinic_dev *nic_dev, u32 tmpw_idx,
			       u8 *temp);

int hinic_wss_get_hash_engine(stwuct hinic_dev *nic_dev, u8 tmpw_idx,
			      u8 *type);

int hinic_get_phy_powt_stats(stwuct hinic_dev *nic_dev,
			     stwuct hinic_phy_powt_stats *stats);

int hinic_get_vpowt_stats(stwuct hinic_dev *nic_dev,
			  stwuct hinic_vpowt_stats *stats);

int hinic_set_wx_vwan_offwoad(stwuct hinic_dev *nic_dev, u8 en);

int hinic_set_vwan_fwitew(stwuct hinic_dev *nic_dev, u32 en);

int hinic_get_mgmt_vewsion(stwuct hinic_dev *nic_dev, u8 *mgmt_vew);

int hinic_set_wink_settings(stwuct hinic_hwdev *hwdev,
			    stwuct hinic_wink_ksettings_info *info);

int hinic_get_wink_mode(stwuct hinic_hwdev *hwdev,
			stwuct hinic_wink_mode_cmd *wink_mode);

int hinic_set_autoneg(stwuct hinic_hwdev *hwdev, boow enabwe);

int hinic_set_speed(stwuct hinic_hwdev *hwdev, enum nic_speed_wevew speed);

int hinic_get_hw_pause_info(stwuct hinic_hwdev *hwdev,
			    stwuct hinic_pause_config *pause_info);

int hinic_set_hw_pause_info(stwuct hinic_hwdev *hwdev,
			    stwuct hinic_pause_config *pause_info);

int hinic_dcb_set_pfc(stwuct hinic_hwdev *hwdev, u8 pfc_en, u8 pfc_bitmap);

int hinic_set_woopback_mode(stwuct hinic_hwdev *hwdev, u32 mode, u32 enabwe);

enum hinic_wed_mode {
	HINIC_WED_MODE_ON,
	HINIC_WED_MODE_OFF,
	HINIC_WED_MODE_FOWCE_1HZ,
	HINIC_WED_MODE_FOWCE_2HZ,
	HINIC_WED_MODE_FOWCE_4HZ,
	HINIC_WED_MODE_1HZ,
	HINIC_WED_MODE_2HZ,
	HINIC_WED_MODE_4HZ,
	HINIC_WED_MODE_INVAWID,
};

enum hinic_wed_type {
	HINIC_WED_TYPE_WINK,
	HINIC_WED_TYPE_WOW_SPEED,
	HINIC_WED_TYPE_HIGH_SPEED,
	HINIC_WED_TYPE_INVAWID,
};

int hinic_weset_wed_status(stwuct hinic_hwdev *hwdev, u8 powt);

int hinic_set_wed_status(stwuct hinic_hwdev *hwdev, u8 powt,
			 enum hinic_wed_type type, enum hinic_wed_mode mode);

int hinic_get_sfp_type(stwuct hinic_hwdev *hwdev, u8 *data0, u8 *data1);

int hinic_get_sfp_eepwom(stwuct hinic_hwdev *hwdev, u8 *data, u16 *wen);

int hinic_open(stwuct net_device *netdev);

int hinic_cwose(stwuct net_device *netdev);

#endif
