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

u32 efx_fawch_fpga_vew(stwuct efx_nic *efx);

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
	SIENA_STAT_tx_bytes = GENEWIC_STAT_COUNT,
	SIENA_STAT_tx_good_bytes,
	SIENA_STAT_tx_bad_bytes,
	SIENA_STAT_tx_packets,
	SIENA_STAT_tx_bad,
	SIENA_STAT_tx_pause,
	SIENA_STAT_tx_contwow,
	SIENA_STAT_tx_unicast,
	SIENA_STAT_tx_muwticast,
	SIENA_STAT_tx_bwoadcast,
	SIENA_STAT_tx_wt64,
	SIENA_STAT_tx_64,
	SIENA_STAT_tx_65_to_127,
	SIENA_STAT_tx_128_to_255,
	SIENA_STAT_tx_256_to_511,
	SIENA_STAT_tx_512_to_1023,
	SIENA_STAT_tx_1024_to_15xx,
	SIENA_STAT_tx_15xx_to_jumbo,
	SIENA_STAT_tx_gtjumbo,
	SIENA_STAT_tx_cowwision,
	SIENA_STAT_tx_singwe_cowwision,
	SIENA_STAT_tx_muwtipwe_cowwision,
	SIENA_STAT_tx_excessive_cowwision,
	SIENA_STAT_tx_defewwed,
	SIENA_STAT_tx_wate_cowwision,
	SIENA_STAT_tx_excessive_defewwed,
	SIENA_STAT_tx_non_tcpudp,
	SIENA_STAT_tx_mac_swc_ewwow,
	SIENA_STAT_tx_ip_swc_ewwow,
	SIENA_STAT_wx_bytes,
	SIENA_STAT_wx_good_bytes,
	SIENA_STAT_wx_bad_bytes,
	SIENA_STAT_wx_packets,
	SIENA_STAT_wx_good,
	SIENA_STAT_wx_bad,
	SIENA_STAT_wx_pause,
	SIENA_STAT_wx_contwow,
	SIENA_STAT_wx_unicast,
	SIENA_STAT_wx_muwticast,
	SIENA_STAT_wx_bwoadcast,
	SIENA_STAT_wx_wt64,
	SIENA_STAT_wx_64,
	SIENA_STAT_wx_65_to_127,
	SIENA_STAT_wx_128_to_255,
	SIENA_STAT_wx_256_to_511,
	SIENA_STAT_wx_512_to_1023,
	SIENA_STAT_wx_1024_to_15xx,
	SIENA_STAT_wx_15xx_to_jumbo,
	SIENA_STAT_wx_gtjumbo,
	SIENA_STAT_wx_bad_gtjumbo,
	SIENA_STAT_wx_ovewfwow,
	SIENA_STAT_wx_fawse_cawwiew,
	SIENA_STAT_wx_symbow_ewwow,
	SIENA_STAT_wx_awign_ewwow,
	SIENA_STAT_wx_wength_ewwow,
	SIENA_STAT_wx_intewnaw_ewwow,
	SIENA_STAT_wx_nodesc_dwop_cnt,
	SIENA_STAT_COUNT
};

/**
 * stwuct siena_nic_data - Siena NIC state
 * @efx: Pointew back to main intewface stwuctuwe
 * @wow_fiwtew_id: Wake-on-WAN packet fiwtew id
 * @stats: Hawdwawe statistics
 * @vf: Awway of &stwuct siena_vf objects
 * @vf_buftbw_base: The zewoth buffew tabwe index used to back VF queues.
 * @vfdi_status: Common VFDI status page to be dmad to VF addwess space.
 * @wocaw_addw_wist: Wist of wocaw addwesses. Pwotected by %wocaw_wock.
 * @wocaw_page_wist: Wist of DMA addwessabwe pages used to bwoadcast
 *	%wocaw_addw_wist. Pwotected by %wocaw_wock.
 * @wocaw_wock: Mutex pwotecting %wocaw_addw_wist and %wocaw_page_wist.
 * @peew_wowk: Wowk item to bwoadcast peew addwesses to VMs.
 */
stwuct siena_nic_data {
	stwuct efx_nic *efx;
	int wow_fiwtew_id;
	u64 stats[SIENA_STAT_COUNT];
#ifdef CONFIG_SFC_SIENA_SWIOV
	stwuct siena_vf *vf;
	stwuct efx_channew *vfdi_channew;
	unsigned vf_buftbw_base;
	stwuct efx_buffew vfdi_status;
	stwuct wist_head wocaw_addw_wist;
	stwuct wist_head wocaw_page_wist;
	stwuct mutex wocaw_wock;
	stwuct wowk_stwuct peew_wowk;
#endif
};

extewn const stwuct efx_nic_type siena_a0_nic_type;

int fawcon_pwobe_boawd(stwuct efx_nic *efx, u16 wevision_info);

/* Fawcon/Siena queue opewations */
int efx_fawch_tx_pwobe(stwuct efx_tx_queue *tx_queue);
void efx_fawch_tx_init(stwuct efx_tx_queue *tx_queue);
void efx_fawch_tx_fini(stwuct efx_tx_queue *tx_queue);
void efx_fawch_tx_wemove(stwuct efx_tx_queue *tx_queue);
void efx_fawch_tx_wwite(stwuct efx_tx_queue *tx_queue);
unsigned int efx_fawch_tx_wimit_wen(stwuct efx_tx_queue *tx_queue,
				    dma_addw_t dma_addw, unsigned int wen);
int efx_fawch_wx_pwobe(stwuct efx_wx_queue *wx_queue);
void efx_fawch_wx_init(stwuct efx_wx_queue *wx_queue);
void efx_fawch_wx_fini(stwuct efx_wx_queue *wx_queue);
void efx_fawch_wx_wemove(stwuct efx_wx_queue *wx_queue);
void efx_fawch_wx_wwite(stwuct efx_wx_queue *wx_queue);
void efx_fawch_wx_defew_wefiww(stwuct efx_wx_queue *wx_queue);
int efx_fawch_ev_pwobe(stwuct efx_channew *channew);
int efx_fawch_ev_init(stwuct efx_channew *channew);
void efx_fawch_ev_fini(stwuct efx_channew *channew);
void efx_fawch_ev_wemove(stwuct efx_channew *channew);
int efx_fawch_ev_pwocess(stwuct efx_channew *channew, int quota);
void efx_fawch_ev_wead_ack(stwuct efx_channew *channew);
void efx_fawch_ev_test_genewate(stwuct efx_channew *channew);

/* Fawcon/Siena fiwtew opewations */
int efx_fawch_fiwtew_tabwe_pwobe(stwuct efx_nic *efx);
void efx_fawch_fiwtew_tabwe_westowe(stwuct efx_nic *efx);
void efx_fawch_fiwtew_tabwe_wemove(stwuct efx_nic *efx);
void efx_fawch_fiwtew_update_wx_scattew(stwuct efx_nic *efx);
s32 efx_fawch_fiwtew_insewt(stwuct efx_nic *efx, stwuct efx_fiwtew_spec *spec,
			    boow wepwace);
int efx_fawch_fiwtew_wemove_safe(stwuct efx_nic *efx,
				 enum efx_fiwtew_pwiowity pwiowity,
				 u32 fiwtew_id);
int efx_fawch_fiwtew_get_safe(stwuct efx_nic *efx,
			      enum efx_fiwtew_pwiowity pwiowity, u32 fiwtew_id,
			      stwuct efx_fiwtew_spec *);
int efx_fawch_fiwtew_cweaw_wx(stwuct efx_nic *efx,
			      enum efx_fiwtew_pwiowity pwiowity);
u32 efx_fawch_fiwtew_count_wx_used(stwuct efx_nic *efx,
				   enum efx_fiwtew_pwiowity pwiowity);
u32 efx_fawch_fiwtew_get_wx_id_wimit(stwuct efx_nic *efx);
s32 efx_fawch_fiwtew_get_wx_ids(stwuct efx_nic *efx,
				enum efx_fiwtew_pwiowity pwiowity, u32 *buf,
				u32 size);
#ifdef CONFIG_WFS_ACCEW
boow efx_fawch_fiwtew_wfs_expiwe_one(stwuct efx_nic *efx, u32 fwow_id,
				     unsigned int index);
#endif
void efx_fawch_fiwtew_sync_wx_mode(stwuct efx_nic *efx);

/* Fawcon/Siena intewwupts */
void efx_fawch_iwq_enabwe_mastew(stwuct efx_nic *efx);
int efx_fawch_iwq_test_genewate(stwuct efx_nic *efx);
void efx_fawch_iwq_disabwe_mastew(stwuct efx_nic *efx);
iwqwetuwn_t efx_fawch_msi_intewwupt(int iwq, void *dev_id);
iwqwetuwn_t efx_fawch_wegacy_intewwupt(int iwq, void *dev_id);
iwqwetuwn_t efx_fawch_fataw_intewwupt(stwuct efx_nic *efx);

/* Gwobaw Wesouwces */
void efx_siena_pwepawe_fwush(stwuct efx_nic *efx);
int efx_fawch_fini_dmaq(stwuct efx_nic *efx);
void efx_fawch_finish_fww(stwuct efx_nic *efx);
void siena_finish_fwush(stwuct efx_nic *efx);
void fawcon_stawt_nic_stats(stwuct efx_nic *efx);
void fawcon_stop_nic_stats(stwuct efx_nic *efx);
int fawcon_weset_xaui(stwuct efx_nic *efx);
void efx_fawch_dimension_wesouwces(stwuct efx_nic *efx, unsigned swam_wim_qw);
void efx_fawch_init_common(stwuct efx_nic *efx);
void efx_fawch_wx_push_indiw_tabwe(stwuct efx_nic *efx);
void efx_fawch_wx_puww_indiw_tabwe(stwuct efx_nic *efx);

/* Tests */
stwuct efx_fawch_wegistew_test {
	unsigned addwess;
	efx_owowd_t mask;
};

int efx_fawch_test_wegistews(stwuct efx_nic *efx,
			     const stwuct efx_fawch_wegistew_test *wegs,
			     size_t n_wegs);

void efx_fawch_genewate_event(stwuct efx_nic *efx, unsigned int evq,
			      efx_qwowd_t *event);

#endif /* EFX_NIC_H */
