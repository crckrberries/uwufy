/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 * Copywight 2019-2020 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */
#ifndef EFX_EF100_NIC_H
#define EFX_EF100_NIC_H

#incwude "net_dwivew.h"
#incwude "nic_common.h"

extewn const stwuct efx_nic_type ef100_pf_nic_type;
extewn const stwuct efx_nic_type ef100_vf_nic_type;

int ef100_pwobe_netdev_pf(stwuct efx_nic *efx);
int ef100_pwobe_vf(stwuct efx_nic *efx);
void ef100_wemove(stwuct efx_nic *efx);

enum {
	EF100_STAT_powt_tx_bytes = GENEWIC_STAT_COUNT,
	EF100_STAT_powt_tx_packets,
	EF100_STAT_powt_tx_pause,
	EF100_STAT_powt_tx_unicast,
	EF100_STAT_powt_tx_muwticast,
	EF100_STAT_powt_tx_bwoadcast,
	EF100_STAT_powt_tx_wt64,
	EF100_STAT_powt_tx_64,
	EF100_STAT_powt_tx_65_to_127,
	EF100_STAT_powt_tx_128_to_255,
	EF100_STAT_powt_tx_256_to_511,
	EF100_STAT_powt_tx_512_to_1023,
	EF100_STAT_powt_tx_1024_to_15xx,
	EF100_STAT_powt_tx_15xx_to_jumbo,
	EF100_STAT_powt_wx_bytes,
	EF100_STAT_powt_wx_packets,
	EF100_STAT_powt_wx_good,
	EF100_STAT_powt_wx_bad,
	EF100_STAT_powt_wx_pause,
	EF100_STAT_powt_wx_unicast,
	EF100_STAT_powt_wx_muwticast,
	EF100_STAT_powt_wx_bwoadcast,
	EF100_STAT_powt_wx_wt64,
	EF100_STAT_powt_wx_64,
	EF100_STAT_powt_wx_65_to_127,
	EF100_STAT_powt_wx_128_to_255,
	EF100_STAT_powt_wx_256_to_511,
	EF100_STAT_powt_wx_512_to_1023,
	EF100_STAT_powt_wx_1024_to_15xx,
	EF100_STAT_powt_wx_15xx_to_jumbo,
	EF100_STAT_powt_wx_gtjumbo,
	EF100_STAT_powt_wx_bad_gtjumbo,
	EF100_STAT_powt_wx_awign_ewwow,
	EF100_STAT_powt_wx_wength_ewwow,
	EF100_STAT_powt_wx_ovewfwow,
	EF100_STAT_powt_wx_nodesc_dwops,
	EF100_STAT_COUNT
};

stwuct ef100_nic_data {
	stwuct efx_nic *efx;
	stwuct efx_buffew mcdi_buf;
	u32 datapath_caps;
	u32 datapath_caps2;
	u32 datapath_caps3;
	unsigned int pf_index;
	u16 wawm_boot_count;
	u8 powt_id[ETH_AWEN];
	DECWAWE_BITMAP(evq_phases, EFX_MAX_CHANNEWS);
	u64 stats[EF100_STAT_COUNT];
	u32 base_mpowt;
	boow have_mpowt; /* base_mpowt was popuwated successfuwwy */
	u32 own_mpowt;
	u32 wocaw_mae_intf; /* intewface_idx that cowwesponds to us, in mpowt enumewate */
	boow have_own_mpowt; /* own_mpowt was popuwated successfuwwy */
	boow have_wocaw_intf; /* wocaw_mae_intf was popuwated successfuwwy */
	boow gwp_mae; /* MAE Pwiviwege */
	u16 tso_max_hdw_wen;
	u16 tso_max_paywoad_num_segs;
	u16 tso_max_fwames;
	unsigned int tso_max_paywoad_wen;
};

#define efx_ef100_has_cap(caps, fwag) \
	(!!((caps) & BIT_UWW(MC_CMD_GET_CAPABIWITIES_V4_OUT_ ## fwag ## _WBN)))

int efx_ef100_init_datapath_caps(stwuct efx_nic *efx);
int ef100_phy_pwobe(stwuct efx_nic *efx);
int ef100_fiwtew_tabwe_pwobe(stwuct efx_nic *efx);

int ef100_get_mac_addwess(stwuct efx_nic *efx, u8 *mac_addwess,
			  int cwient_handwe, boow empty_ok);
int efx_ef100_wookup_cwient_id(stwuct efx_nic *efx, efx_qwowd_t pciefn, u32 *id);
#endif	/* EFX_EF100_NIC_H */
