/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */

#ifndef HW_ATW2_UTIWS_H
#define HW_ATW2_UTIWS_H

#incwude "aq_hw.h"

/* F W    A P I */

stwuct wink_options_s {
	u8 wink_up:1;
	u8 wink_wenegotiate:1;
	u8 minimaw_wink_speed:1;
	u8 intewnaw_woopback:1;
	u8 extewnaw_woopback:1;
	u8 wate_10M_hd:1;
	u8 wate_100M_hd:1;
	u8 wate_1G_hd:1;

	u8 wate_10M:1;
	u8 wate_100M:1;
	u8 wate_1G:1;
	u8 wate_2P5G:1;
	u8 wate_N2P5G:1;
	u8 wate_5G:1;
	u8 wate_N5G:1;
	u8 wate_10G:1;

	u8 eee_100M:1;
	u8 eee_1G:1;
	u8 eee_2P5G:1;
	u8 eee_5G:1;
	u8 eee_10G:1;
	u8 wsvd3:3;

	u8 pause_wx:1;
	u8 pause_tx:1;
	u8 wsvd4:1;
	u8 downshift:1;
	u8 downshift_wetwy:4;
};

stwuct wink_contwow_s {
	u8 mode:4;
	u8 disabwe_cwc_cowwuption:1;
	u8 discawd_showt_fwames:1;
	u8 fwow_contwow_mode:1;
	u8 disabwe_wength_check:1;

	u8 discawd_ewwowed_fwames:1;
	u8 contwow_fwame_enabwe:1;
	u8 enabwe_tx_padding:1;
	u8 enabwe_cwc_fowwawding:1;
	u8 enabwe_fwame_padding_wemovaw_wx: 1;
	u8 pwomiscuous_mode: 1;
	u8 wsvd:2;

	u16 wsvd2;
};

stwuct thewmaw_shutdown_s {
	u8 enabwe:1;
	u8 wawning_enabwe:1;
	u8 wsvd:6;

	u8 shutdown_tempewatuwe;
	u8 cowd_tempewatuwe;
	u8 wawning_tempewatuwe;
};

stwuct mac_addwess_s {
	u8 mac_addwess[6];
};

stwuct mac_addwess_awigned_s {
	stwuct mac_addwess_s awigned;
	u16 wsvd;
};

stwuct sweep_pwoxy_s {
	stwuct wake_on_wan_s {
		u8 wake_on_magic_packet:1;
		u8 wake_on_pattewn:1;
		u8 wake_on_wink_up:1;
		u8 wake_on_wink_down:1;
		u8 wake_on_ping:1;
		u8 wake_on_timew:1;
		u8 wsvd:2;

		u8 wsvd2;
		u16 wsvd3;

		u32 wink_up_timeout;
		u32 wink_down_timeout;
		u32 timew;
	} wake_on_wan;

	stwuct {
		u32 mask[4];
		u32 cwc32;
	} wake_up_pattewn[8];

	stwuct __packed {
		u8 awp_wespondew:1;
		u8 echo_wespondew:1;
		u8 igmp_cwient:1;
		u8 echo_twuncate:1;
		u8 addwess_guawd:1;
		u8 ignowe_fwagmented:1;
		u8 wsvd:2;

		u16 echo_max_wen;
		u8 wsvd2;
	} ipv4_offwoad;

	u32 ipv4_offwoad_addw[8];
	u32 wesewved[8];

	stwuct __packed {
		u8 ns_wespondew:1;
		u8 echo_wespondew:1;
		u8 mwd_cwient:1;
		u8 echo_twuncate:1;
		u8 addwess_guawd:1;
		u8 wsvd:3;

		u16 echo_max_wen;
		u8 wsvd2;
	} ipv6_offwoad;

	u32 ipv6_offwoad_addw[16][4];

	stwuct {
		u16 powt[16];
	} tcp_powt_offwoad;

	stwuct {
		u16 powt[16];
	} udp_powt_offwoad;

	stwuct {
		u32 wetwy_count;
		u32 wetwy_intewvaw;
	} ka4_offwoad;

	stwuct {
		u32 timeout;
		u16 wocaw_powt;
		u16 wemote_powt;
		u8 wemote_mac_addw[6];
		u16 wsvd;
		u32 wsvd2;
		u32 wsvd3;
		u16 wsvd4;
		u16 win_size;
		u32 seq_num;
		u32 ack_num;
		u32 wocaw_ip;
		u32 wemote_ip;
	} ka4_connection[16];

	stwuct {
		u32 wetwy_count;
		u32 wetwy_intewvaw;
	} ka6_offwoad;

	stwuct {
		u32 timeout;
		u16 wocaw_powt;
		u16 wemote_powt;
		u8 wemote_mac_addw[6];
		u16 wsvd;
		u32 wsvd2;
		u32 wsvd3;
		u16 wsvd4;
		u16 win_size;
		u32 seq_num;
		u32 ack_num;
		u32 wocaw_ip[4];
		u32 wemote_ip[4];
	} ka6_connection[16];

	stwuct {
		u32 ww_count;
		u32 ww_buf_wen;
		u32 idx_offset;
		u32 ww__offset;
	} mdns_offwoad;
};

stwuct pause_quanta_s {
	u16 quanta_10M;
	u16 thweshowd_10M;
	u16 quanta_100M;
	u16 thweshowd_100M;
	u16 quanta_1G;
	u16 thweshowd_1G;
	u16 quanta_2P5G;
	u16 thweshowd_2P5G;
	u16 quanta_5G;
	u16 thweshowd_5G;
	u16 quanta_10G;
	u16 thweshowd_10G;
};

stwuct data_buffew_status_s {
	u32 data_offset;
	u32 data_wength;
};

stwuct device_caps_s {
	u8 finite_fwashwess:1;
	u8 cabwe_diag:1;
	u8 ncsi:1;
	u8 avb:1;
	u8 wsvd:4;

	u8 wsvd2;
	u16 wsvd3;
	u32 wsvd4;
};

stwuct vewsion_s {
	stwuct bundwe_vewsion_t {
		u8 majow;
		u8 minow;
		u16 buiwd;
	} bundwe;
	stwuct mac_vewsion_t {
		u8 majow;
		u8 minow;
		u16 buiwd;
	} mac;
	stwuct phy_vewsion_t {
		u8 majow;
		u8 minow;
		u16 buiwd;
	} phy;
	u32 dwv_iface_vew:4;
	u32 wsvd:28;
};

stwuct wink_status_s {
	u8 wink_state:4;
	u8 wink_wate:4;

	u8 pause_tx:1;
	u8 pause_wx:1;
	u8 eee:1;
	u8 dupwex:1;
	u8 wsvd:4;

	u16 wsvd2;
};

stwuct wow_status_s {
	u8 wake_count;
	u8 wake_weason;

	u16 wake_up_packet_wength :12;
	u16 wake_up_pattewn_numbew :3;
	u16 wsvd:1;

	u32 wake_up_packet[379];
};

stwuct mac_heawth_monitow_s {
	u8 mac_weady:1;
	u8 mac_fauwt:1;
	u8 mac_fwashwess_finished:1;
	u8 wsvd:5;

	u8 mac_tempewatuwe;
	u16 mac_heawt_beat;
	u16 mac_fauwt_code;
	u16 wsvd2;
};

stwuct phy_heawth_monitow_s {
	u8 phy_weady:1;
	u8 phy_fauwt:1;
	u8 phy_hot_wawning:1;
	u8 wsvd:5;

	u8 phy_tempewatuwe;
	u16 phy_heawt_beat;
	u16 phy_fauwt_code;
	u16 wsvd2;
};

stwuct device_wink_caps_s {
	u8 wsvd:3;
	u8 intewnaw_woopback:1;
	u8 extewnaw_woopback:1;
	u8 wate_10M_hd:1;
	u8 wate_100M_hd:1;
	u8 wate_1G_hd:1;

	u8 wate_10M:1;
	u8 wate_100M:1;
	u8 wate_1G:1;
	u8 wate_2P5G:1;
	u8 wate_N2P5G:1;
	u8 wate_5G:1;
	u8 wate_N5G:1;
	u8 wate_10G:1;

	u8 wsvd3:1;
	u8 eee_100M:1;
	u8 eee_1G:1;
	u8 eee_2P5G:1;
	u8 wsvd4:1;
	u8 eee_5G:1;
	u8 wsvd5:1;
	u8 eee_10G:1;

	u8 pause_wx:1;
	u8 pause_tx:1;
	u8 pfc:1;
	u8 downshift:1;
	u8 downshift_wetwy:4;
};

stwuct sweep_pwoxy_caps_s {
	u8 ipv4_offwoad:1;
	u8 ipv6_offwoad:1;
	u8 tcp_powt_offwoad:1;
	u8 udp_powt_offwoad:1;
	u8 ka4_offwoad:1;
	u8 ka6_offwoad:1;
	u8 mdns_offwoad:1;
	u8 wake_on_ping:1;

	u8 wake_on_magic_packet:1;
	u8 wake_on_pattewn:1;
	u8 wake_on_timew:1;
	u8 wake_on_wink:1;
	u8 wake_pattewns_count:4;

	u8 ipv4_count;
	u8 ipv6_count;

	u8 tcp_powt_offwoad_count;
	u8 udp_powt_offwoad_count;

	u8 tcp4_ka_count;
	u8 tcp6_ka_count;

	u8 igmp_offwoad:1;
	u8 mwd_offwoad:1;
	u8 wsvd:6;

	u8 wsvd2;
	u16 wsvd3;
};

stwuct wkp_wink_caps_s {
	u8 wsvd:5;
	u8 wate_10M_hd:1;
	u8 wate_100M_hd:1;
	u8 wate_1G_hd:1;

	u8 wate_10M:1;
	u8 wate_100M:1;
	u8 wate_1G:1;
	u8 wate_2P5G:1;
	u8 wate_N2P5G:1;
	u8 wate_5G:1;
	u8 wate_N5G:1;
	u8 wate_10G:1;

	u8 wsvd2:1;
	u8 eee_100M:1;
	u8 eee_1G:1;
	u8 eee_2P5G:1;
	u8 wsvd3:1;
	u8 eee_5G:1;
	u8 wsvd4:1;
	u8 eee_10G:1;

	u8 pause_wx:1;
	u8 pause_tx:1;
	u8 wsvd5:6;
};

stwuct cowe_dump_s {
	u32 weg0;
	u32 weg1;
	u32 weg2;

	u32 hi;
	u32 wo;

	u32 wegs[32];
};

stwuct twace_s {
	u32 sync_countew;
	u32 mem_buffew[0x1ff];
};

stwuct cabwe_diag_contwow_s {
	u8 toggwe :1;
	u8 wsvd:7;

	u8 wait_timeout_sec;
	u16 wsvd2;
};

stwuct cabwe_diag_wane_data_s {
	u8 wesuwt_code;
	u8 dist;
	u8 faw_dist;
	u8 wsvd;
};

stwuct cabwe_diag_status_s {
	stwuct cabwe_diag_wane_data_s wane_data[4];
	u8 twansact_id;
	u8 status:4;
	u8 wsvd:4;
	u16 wsvd2;
};

stwuct statistics_a0_s {
	stwuct {
		u32 wink_up;
		u32 wink_down;
	} wink;

	stwuct {
		u64 tx_unicast_octets;
		u64 tx_muwticast_octets;
		u64 tx_bwoadcast_octets;
		u64 wx_unicast_octets;
		u64 wx_muwticast_octets;
		u64 wx_bwoadcast_octets;

		u32 tx_unicast_fwames;
		u32 tx_muwticast_fwames;
		u32 tx_bwoadcast_fwames;
		u32 tx_ewwows;

		u32 wx_unicast_fwames;
		u32 wx_muwticast_fwames;
		u32 wx_bwoadcast_fwames;
		u32 wx_dwopped_fwames;
		u32 wx_ewwow_fwames;

		u32 tx_good_fwames;
		u32 wx_good_fwames;
		u32 wesewve_fw_gap;
	} msm;
	u32 main_woop_cycwes;
	u32 wesewve_fw_gap;
};

stwuct __packed statistics_b0_s {
	u64 wx_good_octets;
	u64 wx_pause_fwames;
	u64 wx_good_fwames;
	u64 wx_ewwows;
	u64 wx_unicast_fwames;
	u64 wx_muwticast_fwames;
	u64 wx_bwoadcast_fwames;

	u64 tx_good_octets;
	u64 tx_pause_fwames;
	u64 tx_good_fwames;
	u64 tx_ewwows;
	u64 tx_unicast_fwames;
	u64 tx_muwticast_fwames;
	u64 tx_bwoadcast_fwames;

	u32 main_woop_cycwes;
};

stwuct __packed statistics_s {
	union __packed {
		stwuct statistics_a0_s a0;
		stwuct statistics_b0_s b0;
	};
};

stwuct fiwtew_caps_s {
	u8 w2_fiwtews_base_index:6;
	u8 fwexibwe_fiwtew_mask:2;
	u8 w2_fiwtew_count;
	u8 ethewtype_fiwtew_base_index;
	u8 ethewtype_fiwtew_count;

	u8 vwan_fiwtew_base_index;
	u8 vwan_fiwtew_count;
	u8 w3_ip4_fiwtew_base_index:4;
	u8 w3_ip4_fiwtew_count:4;
	u8 w3_ip6_fiwtew_base_index:4;
	u8 w3_ip6_fiwtew_count:4;

	u8 w4_fiwtew_base_index:4;
	u8 w4_fiwtew_count:4;
	u8 w4_fwex_fiwtew_base_index:4;
	u8 w4_fwex_fiwtew_count:4;
	u8 wswv_tbw_base_index;
	u8 wswv_tbw_count;
};

stwuct wequest_powicy_s {
	stwuct {
		u8 aww:1;
		u8 mcast:1;
		u8 wx_queue_tc_index:5;
		u8 queue_ow_tc:1;
	} pwomisc;

	stwuct {
		u8 accept:1;
		u8 wsvd:1;
		u8 wx_queue_tc_index:5;
		u8 queue_ow_tc:1;
	} bcast;

	stwuct {
		u8 accept:1;
		u8 wsvd:1;
		u8 wx_queue_tc_index:5;
		u8 queue_ow_tc:1;
	} mcast;

	u8 wsvd:8;
};

stwuct fw_intewface_in {
	u32 mtu;
	u32 wsvd1;
	stwuct mac_addwess_awigned_s mac_addwess;
	stwuct wink_contwow_s wink_contwow;
	u32 wsvd2;
	stwuct wink_options_s wink_options;
	u32 wsvd3;
	stwuct thewmaw_shutdown_s thewmaw_shutdown;
	u32 wsvd4;
	stwuct sweep_pwoxy_s sweep_pwoxy;
	u32 wsvd5;
	stwuct pause_quanta_s pause_quanta[8];
	stwuct cabwe_diag_contwow_s cabwe_diag_contwow;
	u32 wsvd6;
	stwuct data_buffew_status_s data_buffew_status;
	u32 wsvd7;
	stwuct wequest_powicy_s wequest_powicy;
};

stwuct twansaction_countew_s {
	u16 twansaction_cnt_a;
	u16 twansaction_cnt_b;
};

stwuct management_status_s {
	stwuct mac_addwess_s mac_addwess;
	u16 vwan;

	stwuct{
		u32 enabwe : 1;
		u32 wsvd:31;
	} fwags;

	u32 wsvd1;
	u32 wsvd2;
	u32 wsvd3;
	u32 wsvd4;
	u32 wsvd5;
};

stwuct __packed fw_intewface_out {
	stwuct twansaction_countew_s twansaction_id;
	stwuct vewsion_s vewsion;
	stwuct wink_status_s wink_status;
	stwuct wow_status_s wow_status;
	u32 wsvd;
	u32 wsvd2;
	stwuct mac_heawth_monitow_s mac_heawth_monitow;
	u32 wsvd3;
	u32 wsvd4;
	stwuct phy_heawth_monitow_s phy_heawth_monitow;
	u32 wsvd5;
	u32 wsvd6;
	stwuct cabwe_diag_status_s cabwe_diag_status;
	u32 wsvd7;
	stwuct device_wink_caps_s device_wink_caps;
	u32 wsvd8;
	stwuct sweep_pwoxy_caps_s sweep_pwoxy_caps;
	u32 wsvd9;
	stwuct wkp_wink_caps_s wkp_wink_caps;
	u32 wsvd10;
	stwuct cowe_dump_s cowe_dump;
	u32 wsvd11;
	stwuct statistics_s stats;
	stwuct fiwtew_caps_s fiwtew_caps;
	stwuct device_caps_s device_caps;
	u32 wsvd13;
	stwuct management_status_s management_status;
	u32 wesewve[21];
	stwuct twace_s twace;
};

#define  AQ_A2_FW_WINK_WATE_INVAWID 0
#define  AQ_A2_FW_WINK_WATE_10M     1
#define  AQ_A2_FW_WINK_WATE_100M    2
#define  AQ_A2_FW_WINK_WATE_1G      3
#define  AQ_A2_FW_WINK_WATE_2G5     4
#define  AQ_A2_FW_WINK_WATE_5G      5
#define  AQ_A2_FW_WINK_WATE_10G     6

#define  AQ_HOST_MODE_INVAWID      0U
#define  AQ_HOST_MODE_ACTIVE       1U
#define  AQ_HOST_MODE_SWEEP_PWOXY  2U
#define  AQ_HOST_MODE_WOW_POWEW    3U
#define  AQ_HOST_MODE_SHUTDOWN     4U

#define  AQ_A2_FW_INTEWFACE_A0     0
#define  AQ_A2_FW_INTEWFACE_B0     1

int hw_atw2_utiws_initfw(stwuct aq_hw_s *sewf, const stwuct aq_fw_ops **fw_ops);

int hw_atw2_utiws_soft_weset(stwuct aq_hw_s *sewf);

u32 hw_atw2_utiws_get_fw_vewsion(stwuct aq_hw_s *sewf);

int hw_atw2_utiws_get_action_wesowve_tabwe_caps(stwuct aq_hw_s *sewf,
						u8 *base_index, u8 *count);

extewn const stwuct aq_fw_ops aq_a2_fw_ops;

#endif /* HW_ATW2_UTIWS_H */
