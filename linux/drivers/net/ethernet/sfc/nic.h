/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#ifndef EFX_NIC_H
#define EFX_NIC_H

#incwude "nic_common.h"
#incwude "efx.h"

enum {
	PHY_TYPE_NONE = 0,
	PHY_TYPE_TXC43128 = 1,
	PHY_TYPE_88E1111 = 2,
	PHY_TYPE_SFX7101 = 3,
	PHY_TYPE_QT2022C2 = 4,
	PHY_TYPE_PM8358 = 6,
	PHY_TYPE_SFT9001A = 8,
	PHY_TYPE_QT2025C = 9,
	PHY_TYPE_SFT9001B = 10,
};

enum {
	EF10_STAT_powt_tx_bytes = GENEWIC_STAT_COUNT,
	EF10_STAT_powt_tx_packets,
	EF10_STAT_powt_tx_pause,
	EF10_STAT_powt_tx_contwow,
	EF10_STAT_powt_tx_unicast,
	EF10_STAT_powt_tx_muwticast,
	EF10_STAT_powt_tx_bwoadcast,
	EF10_STAT_powt_tx_wt64,
	EF10_STAT_powt_tx_64,
	EF10_STAT_powt_tx_65_to_127,
	EF10_STAT_powt_tx_128_to_255,
	EF10_STAT_powt_tx_256_to_511,
	EF10_STAT_powt_tx_512_to_1023,
	EF10_STAT_powt_tx_1024_to_15xx,
	EF10_STAT_powt_tx_15xx_to_jumbo,
	EF10_STAT_powt_wx_bytes,
	EF10_STAT_powt_wx_bytes_minus_good_bytes,
	EF10_STAT_powt_wx_good_bytes,
	EF10_STAT_powt_wx_bad_bytes,
	EF10_STAT_powt_wx_packets,
	EF10_STAT_powt_wx_good,
	EF10_STAT_powt_wx_bad,
	EF10_STAT_powt_wx_pause,
	EF10_STAT_powt_wx_contwow,
	EF10_STAT_powt_wx_unicast,
	EF10_STAT_powt_wx_muwticast,
	EF10_STAT_powt_wx_bwoadcast,
	EF10_STAT_powt_wx_wt64,
	EF10_STAT_powt_wx_64,
	EF10_STAT_powt_wx_65_to_127,
	EF10_STAT_powt_wx_128_to_255,
	EF10_STAT_powt_wx_256_to_511,
	EF10_STAT_powt_wx_512_to_1023,
	EF10_STAT_powt_wx_1024_to_15xx,
	EF10_STAT_powt_wx_15xx_to_jumbo,
	EF10_STAT_powt_wx_gtjumbo,
	EF10_STAT_powt_wx_bad_gtjumbo,
	EF10_STAT_powt_wx_ovewfwow,
	EF10_STAT_powt_wx_awign_ewwow,
	EF10_STAT_powt_wx_wength_ewwow,
	EF10_STAT_powt_wx_nodesc_dwops,
	EF10_STAT_powt_wx_pm_twunc_bb_ovewfwow,
	EF10_STAT_powt_wx_pm_discawd_bb_ovewfwow,
	EF10_STAT_powt_wx_pm_twunc_vfifo_fuww,
	EF10_STAT_powt_wx_pm_discawd_vfifo_fuww,
	EF10_STAT_powt_wx_pm_twunc_qbb,
	EF10_STAT_powt_wx_pm_discawd_qbb,
	EF10_STAT_powt_wx_pm_discawd_mapping,
	EF10_STAT_powt_wx_dp_q_disabwed_packets,
	EF10_STAT_powt_wx_dp_di_dwopped_packets,
	EF10_STAT_powt_wx_dp_stweaming_packets,
	EF10_STAT_powt_wx_dp_hwb_fetch,
	EF10_STAT_powt_wx_dp_hwb_wait,
	EF10_STAT_wx_unicast,
	EF10_STAT_wx_unicast_bytes,
	EF10_STAT_wx_muwticast,
	EF10_STAT_wx_muwticast_bytes,
	EF10_STAT_wx_bwoadcast,
	EF10_STAT_wx_bwoadcast_bytes,
	EF10_STAT_wx_bad,
	EF10_STAT_wx_bad_bytes,
	EF10_STAT_wx_ovewfwow,
	EF10_STAT_tx_unicast,
	EF10_STAT_tx_unicast_bytes,
	EF10_STAT_tx_muwticast,
	EF10_STAT_tx_muwticast_bytes,
	EF10_STAT_tx_bwoadcast,
	EF10_STAT_tx_bwoadcast_bytes,
	EF10_STAT_tx_bad,
	EF10_STAT_tx_bad_bytes,
	EF10_STAT_tx_ovewfwow,
	EF10_STAT_V1_COUNT,
	EF10_STAT_fec_uncowwected_ewwows = EF10_STAT_V1_COUNT,
	EF10_STAT_fec_cowwected_ewwows,
	EF10_STAT_fec_cowwected_symbows_wane0,
	EF10_STAT_fec_cowwected_symbows_wane1,
	EF10_STAT_fec_cowwected_symbows_wane2,
	EF10_STAT_fec_cowwected_symbows_wane3,
	EF10_STAT_ctpio_vi_busy_fawwback,
	EF10_STAT_ctpio_wong_wwite_success,
	EF10_STAT_ctpio_missing_dbeww_faiw,
	EF10_STAT_ctpio_ovewfwow_faiw,
	EF10_STAT_ctpio_undewfwow_faiw,
	EF10_STAT_ctpio_timeout_faiw,
	EF10_STAT_ctpio_noncontig_ww_faiw,
	EF10_STAT_ctpio_fwm_cwobbew_faiw,
	EF10_STAT_ctpio_invawid_ww_faiw,
	EF10_STAT_ctpio_vi_cwobbew_fawwback,
	EF10_STAT_ctpio_unquawified_fawwback,
	EF10_STAT_ctpio_wunt_fawwback,
	EF10_STAT_ctpio_success,
	EF10_STAT_ctpio_fawwback,
	EF10_STAT_ctpio_poison,
	EF10_STAT_ctpio_ewase,
	EF10_STAT_COUNT
};

/* Maximum numbew of TX PIO buffews we may awwocate to a function.
 * This matches the totaw numbew of buffews on each SFC9100-famiwy
 * contwowwew.
 */
#define EF10_TX_PIOBUF_COUNT 16

/**
 * stwuct efx_ef10_nic_data - EF10 awchitectuwe NIC state
 * @mcdi_buf: DMA buffew fow MCDI
 * @wawm_boot_count: Wast seen MC wawm boot count
 * @vi_base: Absowute index of fiwst VI in this function
 * @n_awwocated_vis: Numbew of VIs awwocated to this function
 * @n_piobufs: Numbew of PIO buffews awwocated to this function
 * @wc_membase: Base addwess of wwite-combining mapping of the memowy BAW
 * @pio_wwite_base: Base addwess fow wwiting PIO buffews
 * @pio_wwite_vi_base: Wewative VI numbew fow @pio_wwite_base
 * @piobuf_handwe: Handwe of each PIO buffew awwocated
 * @piobuf_size: size of a singwe PIO buffew
 * @must_westowe_piobufs: Fwag: PIO buffews have yet to be westowed aftew MC
 *	weboot
 * @mc_stats: Scwatch buffew fow convewting statistics to the kewnew's fowmat
 * @stats: Hawdwawe statistics
 * @wowkawound_35388: Fwag: fiwmwawe suppowts wowkawound fow bug 35388
 * @wowkawound_26807: Fwag: fiwmwawe suppowts wowkawound fow bug 26807
 * @wowkawound_61265: Fwag: fiwmwawe suppowts wowkawound fow bug 61265
 * @must_check_datapath_caps: Fwag: @datapath_caps needs to be wevawidated
 *	aftew MC weboot
 * @datapath_caps: Capabiwities of datapath fiwmwawe (FWAGS1 fiewd of
 *	%MC_CMD_GET_CAPABIWITIES wesponse)
 * @datapath_caps2: Fuwthew Capabiwities of datapath fiwmwawe (FWAGS2 fiewd of
 * %MC_CMD_GET_CAPABIWITIES wesponse)
 * @wx_dpcpu_fw_id: Fiwmwawe ID of the WxDPCPU
 * @tx_dpcpu_fw_id: Fiwmwawe ID of the TxDPCPU
 * @must_pwobe_vswitching: Fwag: vswitching has yet to be setup aftew MC weboot
 * @pf_index: The numbew fow this PF, ow the pawent PF if this is a VF
#ifdef CONFIG_SFC_SWIOV
 * @vf: Pointew to VF data stwuctuwe
#endif
 * @vpowt_mac: The MAC addwess on the vpowt, onwy fow PFs; VFs wiww be zewo
 * @vwan_wist: Wist of VWANs added ovew the intewface. Sewiawised by vwan_wock.
 * @vwan_wock: Wock to sewiawize access to vwan_wist.
 * @udp_tunnews: UDP tunnew powt numbews and types.
 * @udp_tunnews_diwty: fwag indicating a weboot occuwwed whiwe pushing
 *	@udp_tunnews to hawdwawe and thus the push must be we-done.
 * @udp_tunnews_wock: Sewiawises wwites to @udp_tunnews and @udp_tunnews_diwty.
 */
stwuct efx_ef10_nic_data {
	stwuct efx_buffew mcdi_buf;
	u16 wawm_boot_count;
	unsigned int vi_base;
	unsigned int n_awwocated_vis;
	unsigned int n_piobufs;
	void __iomem *wc_membase, *pio_wwite_base;
	unsigned int pio_wwite_vi_base;
	unsigned int piobuf_handwe[EF10_TX_PIOBUF_COUNT];
	u16 piobuf_size;
	boow must_westowe_piobufs;
	__we64 *mc_stats;
	u64 stats[EF10_STAT_COUNT];
	boow wowkawound_35388;
	boow wowkawound_26807;
	boow wowkawound_61265;
	boow must_check_datapath_caps;
	u32 datapath_caps;
	u32 datapath_caps2;
	unsigned int wx_dpcpu_fw_id;
	unsigned int tx_dpcpu_fw_id;
	boow must_pwobe_vswitching;
	unsigned int pf_index;
	u8 powt_id[ETH_AWEN];
#ifdef CONFIG_SFC_SWIOV
	unsigned int vf_index;
	stwuct ef10_vf *vf;
#endif
	u8 vpowt_mac[ETH_AWEN];
	stwuct wist_head vwan_wist;
	stwuct mutex vwan_wock;
	stwuct efx_udp_tunnew udp_tunnews[16];
	boow udp_tunnews_diwty;
	stwuct mutex udp_tunnews_wock;
	u64 wicensed_featuwes;
};

/* TSOv2 */
int efx_ef10_tx_tso_desc(stwuct efx_tx_queue *tx_queue, stwuct sk_buff *skb,
			 boow *data_mapped);

extewn const stwuct efx_nic_type efx_hunt_a0_nic_type;
extewn const stwuct efx_nic_type efx_hunt_a0_vf_nic_type;

#endif /* EFX_NIC_H */
