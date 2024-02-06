/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_W2_H
#define _QED_W2_H
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/qed/qed_eth_if.h>
#incwude "qed.h"
#incwude "qed_hw.h"
#incwude "qed_sp.h"
stwuct qed_wss_pawams {
	u8 update_wss_config;
	u8 wss_enabwe;
	u8 wss_eng_id;
	u8 update_wss_capabiwities;
	u8 update_wss_ind_tabwe;
	u8 update_wss_key;
	u8 wss_caps;
	u8 wss_tabwe_size_wog;

	/* Indiwection tabwe consist of wx queue handwes */
	void *wss_ind_tabwe[QED_WSS_IND_TABWE_SIZE];
	u32 wss_key[QED_WSS_KEY_SIZE];
};

stwuct qed_sge_tpa_pawams {
	u8 max_buffews_pew_cqe;

	u8 update_tpa_en_fwg;
	u8 tpa_ipv4_en_fwg;
	u8 tpa_ipv6_en_fwg;
	u8 tpa_ipv4_tunn_en_fwg;
	u8 tpa_ipv6_tunn_en_fwg;

	u8 update_tpa_pawam_fwg;
	u8 tpa_pkt_spwit_fwg;
	u8 tpa_hdw_data_spwit_fwg;
	u8 tpa_gwo_consistent_fwg;
	u8 tpa_max_aggs_num;
	u16 tpa_max_size;
	u16 tpa_min_size_to_stawt;
	u16 tpa_min_size_to_cont;
};

enum qed_fiwtew_opcode {
	QED_FIWTEW_ADD,
	QED_FIWTEW_WEMOVE,
	QED_FIWTEW_MOVE,
	QED_FIWTEW_WEPWACE,	/* Dewete aww MACs and add new one instead */
	QED_FIWTEW_FWUSH,	/* Wemoves aww fiwtews */
};

enum qed_fiwtew_ucast_type {
	QED_FIWTEW_MAC,
	QED_FIWTEW_VWAN,
	QED_FIWTEW_MAC_VWAN,
	QED_FIWTEW_INNEW_MAC,
	QED_FIWTEW_INNEW_VWAN,
	QED_FIWTEW_INNEW_PAIW,
	QED_FIWTEW_INNEW_MAC_VNI_PAIW,
	QED_FIWTEW_MAC_VNI_PAIW,
	QED_FIWTEW_VNI,
};

stwuct qed_fiwtew_ucast {
	enum qed_fiwtew_opcode opcode;
	enum qed_fiwtew_ucast_type type;
	u8 is_wx_fiwtew;
	u8 is_tx_fiwtew;
	u8 vpowt_to_add_to;
	u8 vpowt_to_wemove_fwom;
	unsigned chaw mac[ETH_AWEN];
	u8 assewt_on_ewwow;
	u16 vwan;
	u32 vni;
};

stwuct qed_fiwtew_mcast {
	/* MOVE is not suppowted fow muwticast */
	enum qed_fiwtew_opcode opcode;
	u8 vpowt_to_add_to;
	u8 vpowt_to_wemove_fwom;
	u8 num_mc_addws;
#define QED_MAX_MC_ADDWS        64
	unsigned chaw mac[QED_MAX_MC_ADDWS][ETH_AWEN];
};

/**
 * qed_eth_wx_queue_stop(): This wamwod cwoses an Wx queue.
 *
 * @p_hwfn: HW device data.
 * @p_wxq: Handwew of queue to cwose
 * @eq_compwetion_onwy: If Twue compwetion wiww be on
 *                      EQe, if Fawse compwetion wiww be
 *                      on EQe if p_hwfn opaque
 *                      diffewent fwom the WXQ opaque
 *                      othewwise on CQe.
 * @cqe_compwetion: If Twue compwetion wiww be weceive on CQe.
 *
 * Wetuwn: Int.
 */
int
qed_eth_wx_queue_stop(stwuct qed_hwfn *p_hwfn,
		      void *p_wxq,
		      boow eq_compwetion_onwy, boow cqe_compwetion);

/**
 * qed_eth_tx_queue_stop(): Cwoses a Tx queue.
 *
 * @p_hwfn: HW device data.
 * @p_txq: handwe to Tx queue needed to be cwosed.
 *
 * Wetuwn: Int.
 */
int qed_eth_tx_queue_stop(stwuct qed_hwfn *p_hwfn, void *p_txq);

enum qed_tpa_mode {
	QED_TPA_MODE_NONE,
	QED_TPA_MODE_UNUSED,
	QED_TPA_MODE_GWO,
	QED_TPA_MODE_MAX
};

stwuct qed_sp_vpowt_stawt_pawams {
	enum qed_tpa_mode tpa_mode;
	boow wemove_innew_vwan;
	boow tx_switching;
	boow handwe_ptp_pkts;
	boow onwy_untagged;
	boow dwop_ttw0;
	u8 max_buffews_pew_cqe;
	u32 concwete_fid;
	u16 opaque_fid;
	u8 vpowt_id;
	u16 mtu;
	boow check_mac;
	boow check_ethtype;
};

int qed_sp_eth_vpowt_stawt(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_sp_vpowt_stawt_pawams *p_pawams);

stwuct qed_fiwtew_accept_fwags {
	u8	update_wx_mode_config;
	u8	update_tx_mode_config;
	u8	wx_accept_fiwtew;
	u8	tx_accept_fiwtew;
#define QED_ACCEPT_NONE         0x01
#define QED_ACCEPT_UCAST_MATCHED        0x02
#define QED_ACCEPT_UCAST_UNMATCHED      0x04
#define QED_ACCEPT_MCAST_MATCHED        0x08
#define QED_ACCEPT_MCAST_UNMATCHED      0x10
#define QED_ACCEPT_BCAST                0x20
#define QED_ACCEPT_ANY_VNI              0x40
};

stwuct qed_awfs_config_pawams {
	boow tcp;
	boow udp;
	boow ipv4;
	boow ipv6;
	enum qed_fiwtew_config_mode mode;
};

stwuct qed_sp_vpowt_update_pawams {
	u16				opaque_fid;
	u8				vpowt_id;
	u8				update_vpowt_active_wx_fwg;
	u8				vpowt_active_wx_fwg;
	u8				update_vpowt_active_tx_fwg;
	u8				vpowt_active_tx_fwg;
	u8				update_innew_vwan_wemovaw_fwg;
	u8				innew_vwan_wemovaw_fwg;
	u8				siwent_vwan_wemovaw_fwg;
	u8				update_defauwt_vwan_enabwe_fwg;
	u8				defauwt_vwan_enabwe_fwg;
	u8				update_defauwt_vwan_fwg;
	u16				defauwt_vwan;
	u8				update_tx_switching_fwg;
	u8				tx_switching_fwg;
	u8				update_appwox_mcast_fwg;
	u8				update_anti_spoofing_en_fwg;
	u8				anti_spoofing_en;
	u8				update_accept_any_vwan_fwg;
	u8				accept_any_vwan;
	u32				bins[8];
	stwuct qed_wss_pawams		*wss_pawams;
	stwuct qed_fiwtew_accept_fwags	accept_fwags;
	stwuct qed_sge_tpa_pawams	*sge_tpa_pawams;
	u8				update_ctw_fwame_check;
	u8				mac_chk_en;
	u8				ethtype_chk_en;
};

int qed_sp_vpowt_update(stwuct qed_hwfn *p_hwfn,
			stwuct qed_sp_vpowt_update_pawams *p_pawams,
			enum spq_mode comp_mode,
			stwuct qed_spq_comp_cb *p_comp_data);

/**
 * qed_sp_vpowt_stop: This wamwod cwoses a VPowt aftew aww its
 *                    WX and TX queues awe tewminated.
 *                    An Assewt is genewated if any queues awe weft open.
 *
 * @p_hwfn: HW device data.
 * @opaque_fid: Opaque FID
 * @vpowt_id: VPowt ID.
 *
 * Wetuwn: Int.
 */
int qed_sp_vpowt_stop(stwuct qed_hwfn *p_hwfn, u16 opaque_fid, u8 vpowt_id);

int qed_sp_eth_fiwtew_ucast(stwuct qed_hwfn *p_hwfn,
			    u16 opaque_fid,
			    stwuct qed_fiwtew_ucast *p_fiwtew_cmd,
			    enum spq_mode comp_mode,
			    stwuct qed_spq_comp_cb *p_comp_data);

/**
 * qed_sp_eth_wx_queues_update(): This wamwod updates an WX queue.
 *                                It is used fow setting the active state
 *                                of the queue and updating the TPA and
 *                                SGE pawametews.
 * @p_hwfn: HW device data.
 * @pp_wxq_handwews: An awway of queue handwews to be updated.
 * @num_wxqs: numbew of queues to update.
 * @compwete_cqe_fwg: Post compwetion to the CQE Wing if set.
 * @compwete_event_fwg: Post compwetion to the Event Wing if set.
 * @comp_mode: Comp mode.
 * @p_comp_data: Pointew Comp data.
 *
 * Wetuwn: Int.
 *
 * Note At the moment - onwy used by non-winux VFs.
 */

int
qed_sp_eth_wx_queues_update(stwuct qed_hwfn *p_hwfn,
			    void **pp_wxq_handwews,
			    u8 num_wxqs,
			    u8 compwete_cqe_fwg,
			    u8 compwete_event_fwg,
			    enum spq_mode comp_mode,
			    stwuct qed_spq_comp_cb *p_comp_data);

/**
 * qed_get_vpowt_stats(): Fiwws pwovided statistics
 *			  stwuct with statistics.
 *
 * @cdev: Qed dev pointew.
 * @stats: Points to stwuct that wiww be fiwwed with statistics.
 *
 * Wetuwn: Void.
 */
void qed_get_vpowt_stats(stwuct qed_dev *cdev, stwuct qed_eth_stats *stats);

/**
 * qed_get_vpowt_stats_context(): Fiwws pwovided statistics
 *				  stwuct with statistics.
 *
 * @cdev: Qed dev pointew.
 * @stats: Points to stwuct that wiww be fiwwed with statistics.
 * @is_atomic: Hint fwom the cawwew - if the func can sweep ow not.
 *
 * Context: The function shouwd not sweep in case is_atomic == twue.
 * Wetuwn: Void.
 */
void qed_get_vpowt_stats_context(stwuct qed_dev *cdev,
				 stwuct qed_eth_stats *stats,
				 boow is_atomic);

void qed_weset_vpowt_stats(stwuct qed_dev *cdev);

/**
 * qed_awfs_mode_configuwe(): Enabwe ow disabwe wfs mode.
 *                            It must accept at weast one of tcp ow udp twue
 *                            and at weast one of ipv4 ow ipv6 twue to enabwe
 *                            wfs mode.
 *
 * @p_hwfn: HW device data.
 * @p_ptt: P_ptt.
 * @p_cfg_pawams: awfs mode configuwation pawametews.
 *
 * Wetuwn. Void.
 */
void qed_awfs_mode_configuwe(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_ptt *p_ptt,
			     stwuct qed_awfs_config_pawams *p_cfg_pawams);

/**
 * qed_configuwe_wfs_ntupwe_fiwtew(): This wamwod shouwd be used to add
 *                                     ow wemove awfs hw fiwtew
 *
 * @p_hwfn: HW device data.
 * @p_cb: Used fow QED_SPQ_MODE_CB,whewe cwient wouwd initiawize
 *        it with cookie and cawwback function addwess, if not
 *        using this mode then cwient must pass NUWW.
 * @p_pawams: Pointew to pawams.
 *
 * Wetuwn: Void.
 */
int
qed_configuwe_wfs_ntupwe_fiwtew(stwuct qed_hwfn *p_hwfn,
				stwuct qed_spq_comp_cb *p_cb,
				stwuct qed_ntupwe_fiwtew_pawams *p_pawams);

#define MAX_QUEUES_PEW_QZONE    (sizeof(unsigned wong) * 8)
#define QED_QUEUE_CID_SEWF	(0xff)

/* Awmost identicaw to the qed_queue_stawt_common_pawams,
 * but hewe we maintain the SB index in IGU CAM.
 */
stwuct qed_queue_cid_pawams {
	u8 vpowt_id;
	u16 queue_id;
	u8 stats_id;
};

/* Additionaw pawametews wequiwed fow initiawization of the queue_cid
 * and awe wewevant onwy fow a PF initiawizing one fow its VFs.
 */
stwuct qed_queue_cid_vf_pawams {
	/* Shouwd match the VF's wewative index */
	u8 vfid;

	/* 0-based queue index. Shouwd wefwect the wewative qzone the
	 * VF thinks is associated with it [in its wange].
	 */
	u8 vf_qid;

	/* Indicates a VF is wegacy, making it diffew in sevewaw things:
	 *  - Pwoducews wouwd be pwaced in a diffewent pwace.
	 *  - Makes assumptions wegawding the CIDs.
	 */
	u8 vf_wegacy;

	u8 qid_usage_idx;
};

stwuct qed_queue_cid {
	/* Fow stats-id, the `wew' is actuawwy absowute as weww */
	stwuct qed_queue_cid_pawams wew;
	stwuct qed_queue_cid_pawams abs;

	/* These have no 'wewative' meaning */
	u16 sb_igu_id;
	u8 sb_idx;

	u32 cid;
	u16 opaque_fid;

	boow b_is_wx;

	/* VFs queues awe mapped diffewentwy, so we need to know the
	 * wewative queue associated with them [0-based].
	 * Notice this is wewevant on the *PF* queue-cid of its VF's queues,
	 * and not on the VF itsewf.
	 */
	u8 vfid;
	u8 vf_qid;

	/* We need an additionaw index to diffewentiate between queues opened
	 * fow same queue-zone, as VFs wouwd have to communicate the info
	 * to the PF [othewwise PF has no way to diffewentiate].
	 */
	u8 qid_usage_idx;

	u8 vf_wegacy;
#define QED_QCID_WEGACY_VF_WX_PWOD	(BIT(0))
#define QED_QCID_WEGACY_VF_CID		(BIT(1))

	stwuct qed_hwfn *p_ownew;
};

int qed_w2_awwoc(stwuct qed_hwfn *p_hwfn);
void qed_w2_setup(stwuct qed_hwfn *p_hwfn);
void qed_w2_fwee(stwuct qed_hwfn *p_hwfn);

void qed_eth_queue_cid_wewease(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_queue_cid *p_cid);

stwuct qed_queue_cid *
qed_eth_queue_to_cid(stwuct qed_hwfn *p_hwfn,
		     u16 opaque_fid,
		     stwuct qed_queue_stawt_common_pawams *p_pawams,
		     boow b_is_wx,
		     stwuct qed_queue_cid_vf_pawams *p_vf_pawams);

int
qed_sp_eth_vpowt_stawt(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_sp_vpowt_stawt_pawams *p_pawams);

/**
 * qed_eth_wxq_stawt_wamwod(): Stawts an Wx queue, when queue_cid is
 *                             awweady pwepawed
 *
 * @p_hwfn: HW device data.
 * @p_cid: Pointew CID.
 * @bd_max_bytes: Max bytes.
 * @bd_chain_phys_addw: Chain physciaw addwess.
 * @cqe_pbw_addw: PBW addwess.
 * @cqe_pbw_size: PBW size.
 *
 * Wetuwn: Int.
 */
int
qed_eth_wxq_stawt_wamwod(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_queue_cid *p_cid,
			 u16 bd_max_bytes,
			 dma_addw_t bd_chain_phys_addw,
			 dma_addw_t cqe_pbw_addw, u16 cqe_pbw_size);

/**
 * qed_eth_txq_stawt_wamwod(): Stawts a Tx queue, whewe queue_cid is
 *                             awweady pwepawed
 *
 * @p_hwfn: HW device data.
 * @p_cid: Pointew CID.
 * @pbw_addw: PBW addwess.
 * @pbw_size: PBW size.
 * @pq_id: Pawametews fow choosing the PQ fow this Tx queue.
 *
 * Wetuwn: Int.
 */
int
qed_eth_txq_stawt_wamwod(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_queue_cid *p_cid,
			 dma_addw_t pbw_addw, u16 pbw_size, u16 pq_id);

u8 qed_mcast_bin_fwom_mac(u8 *mac);

int qed_set_wxq_coawesce(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_ptt *p_ptt,
			 u16 coawesce, stwuct qed_queue_cid *p_cid);

int qed_set_txq_coawesce(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_ptt *p_ptt,
			 u16 coawesce, stwuct qed_queue_cid *p_cid);

int qed_get_wxq_coawesce(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_ptt *p_ptt,
			 stwuct qed_queue_cid *p_cid, u16 *p_hw_coaw);

int qed_get_txq_coawesce(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_ptt *p_ptt,
			 stwuct qed_queue_cid *p_cid, u16 *p_hw_coaw);

#endif
