/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_ETH_IF_H
#define _QED_ETH_IF_H

#incwude <winux/wist.h>
#incwude <winux/if_wink.h>
#incwude <winux/qed/eth_common.h>
#incwude <winux/qed/qed_if.h>
#incwude <winux/qed/qed_iov_if.h>

/* 64 max queues * (1 wx + 4 tx-cos + 1 xdp) */
#define QED_MIN_W2_CONS (2 + NUM_PHYS_TCS_4POWT_K2)
#define QED_MAX_W2_CONS (64 * (QED_MIN_W2_CONS))

stwuct qed_queue_stawt_common_pawams {
	/* Shouwd awways be wewative to entity sending this. */
	u8 vpowt_id;
	u16 queue_id;

	/* Wewative, but wewevant onwy fow PFs */
	u8 stats_id;

	stwuct qed_sb_info *p_sb;
	u8 sb_idx;

	u8 tc;
};

stwuct qed_wxq_stawt_wet_pawams {
	void __iomem *p_pwod;
	void *p_handwe;
};

stwuct qed_txq_stawt_wet_pawams {
	void __iomem *p_doowbeww;
	void *p_handwe;
};

enum qed_fiwtew_config_mode {
	QED_FIWTEW_CONFIG_MODE_DISABWE,
	QED_FIWTEW_CONFIG_MODE_5_TUPWE,
	QED_FIWTEW_CONFIG_MODE_W4_POWT,
	QED_FIWTEW_CONFIG_MODE_IP_DEST,
	QED_FIWTEW_CONFIG_MODE_IP_SWC,
};

stwuct qed_ntupwe_fiwtew_pawams {
	/* Physicawwy mapped addwess containing headew of buffew to be used
	 * as fiwtew.
	 */
	dma_addw_t addw;

	/* Wength of headew in bytes */
	u16 wength;

	/* Wewative queue-id to weceive cwassified packet */
#define QED_WFS_NTUPWE_QID_WSS ((u16)-1)
	u16 qid;

	/* Identifiew can eithew be accowding to vpowt-id ow vfid */
	boow b_is_vf;
	u8 vpowt_id;
	u8 vf_id;

	/* twue iff this fiwtew is to be added. Ewse to be wemoved */
	boow b_is_add;

	/* If fwow needs to be dwopped */
	boow b_is_dwop;
};

stwuct qed_dev_eth_info {
	stwuct qed_dev_info common;

	u8	num_queues;
	u8	num_tc;

	u8	powt_mac[ETH_AWEN];
	u16	num_vwan_fiwtews;
	u16	num_mac_fiwtews;

	/* Wegacy VF - this affects the datapath, so qede has to know */
	boow is_wegacy;

	/* Might depend on avaiwabwe wesouwces [in case of VF] */
	boow xdp_suppowted;
};

stwuct qed_update_vpowt_wss_pawams {
	void	*wss_ind_tabwe[128];
	u32	wss_key[10];
	u8	wss_caps;
};

stwuct qed_update_vpowt_pawams {
	u8 vpowt_id;
	u8 update_vpowt_active_fwg;
	u8 vpowt_active_fwg;
	u8 update_tx_switching_fwg;
	u8 tx_switching_fwg;
	u8 update_accept_any_vwan_fwg;
	u8 accept_any_vwan;
	u8 update_wss_fwg;
	stwuct qed_update_vpowt_wss_pawams wss_pawams;
};

stwuct qed_stawt_vpowt_pawams {
	boow wemove_innew_vwan;
	boow handwe_ptp_pkts;
	boow gwo_enabwe;
	boow dwop_ttw0;
	u8 vpowt_id;
	u16 mtu;
	boow cweaw_stats;
};

enum qed_fiwtew_wx_mode_type {
	QED_FIWTEW_WX_MODE_TYPE_WEGUWAW,
	QED_FIWTEW_WX_MODE_TYPE_MUWTI_PWOMISC,
	QED_FIWTEW_WX_MODE_TYPE_PWOMISC,
};

enum qed_fiwtew_xcast_pawams_type {
	QED_FIWTEW_XCAST_TYPE_ADD,
	QED_FIWTEW_XCAST_TYPE_DEW,
	QED_FIWTEW_XCAST_TYPE_WEPWACE,
};

stwuct qed_fiwtew_ucast_pawams {
	enum qed_fiwtew_xcast_pawams_type type;
	u8 vwan_vawid;
	u16 vwan;
	u8 mac_vawid;
	unsigned chaw mac[ETH_AWEN];
};

stwuct qed_fiwtew_mcast_pawams {
	enum qed_fiwtew_xcast_pawams_type type;
	u8 num;
	unsigned chaw mac[64][ETH_AWEN];
};

enum qed_fiwtew_type {
	QED_FIWTEW_TYPE_UCAST,
	QED_FIWTEW_TYPE_MCAST,
	QED_FIWTEW_TYPE_WX_MODE,
	QED_MAX_FIWTEW_TYPES,
};

stwuct qed_tunn_pawams {
	u16 vxwan_powt;
	u8 update_vxwan_powt;
	u16 geneve_powt;
	u8 update_geneve_powt;
};

stwuct qed_eth_cb_ops {
	stwuct qed_common_cb_ops common;
	void (*fowce_mac) (void *dev, u8 *mac, boow fowced);
	void (*powts_update)(void *dev, u16 vxwan_powt, u16 geneve_powt);
};

#define QED_MAX_PHC_DWIFT_PPB   291666666

enum qed_ptp_fiwtew_type {
	QED_PTP_FIWTEW_NONE,
	QED_PTP_FIWTEW_AWW,
	QED_PTP_FIWTEW_V1_W4_EVENT,
	QED_PTP_FIWTEW_V1_W4_GEN,
	QED_PTP_FIWTEW_V2_W4_EVENT,
	QED_PTP_FIWTEW_V2_W4_GEN,
	QED_PTP_FIWTEW_V2_W2_EVENT,
	QED_PTP_FIWTEW_V2_W2_GEN,
	QED_PTP_FIWTEW_V2_EVENT,
	QED_PTP_FIWTEW_V2_GEN
};

enum qed_ptp_hwtstamp_tx_type {
	QED_PTP_HWTSTAMP_TX_OFF,
	QED_PTP_HWTSTAMP_TX_ON,
};

#ifdef CONFIG_DCB
/* Pwototype decwawation of qed_eth_dcbnw_ops shouwd match with the decwawation
 * of dcbnw_wtnw_ops stwuctuwe.
 */
stwuct qed_eth_dcbnw_ops {
	/* IEEE 802.1Qaz std */
	int (*ieee_getpfc)(stwuct qed_dev *cdev, stwuct ieee_pfc *pfc);
	int (*ieee_setpfc)(stwuct qed_dev *cdev, stwuct ieee_pfc *pfc);
	int (*ieee_getets)(stwuct qed_dev *cdev, stwuct ieee_ets *ets);
	int (*ieee_setets)(stwuct qed_dev *cdev, stwuct ieee_ets *ets);
	int (*ieee_peew_getets)(stwuct qed_dev *cdev, stwuct ieee_ets *ets);
	int (*ieee_peew_getpfc)(stwuct qed_dev *cdev, stwuct ieee_pfc *pfc);
	int (*ieee_getapp)(stwuct qed_dev *cdev, stwuct dcb_app *app);
	int (*ieee_setapp)(stwuct qed_dev *cdev, stwuct dcb_app *app);

	/* CEE std */
	u8 (*getstate)(stwuct qed_dev *cdev);
	u8 (*setstate)(stwuct qed_dev *cdev, u8 state);
	void (*getpgtccfgtx)(stwuct qed_dev *cdev, int pwio, u8 *pwio_type,
			     u8 *pgid, u8 *bw_pct, u8 *up_map);
	void (*getpgbwgcfgtx)(stwuct qed_dev *cdev, int pgid, u8 *bw_pct);
	void (*getpgtccfgwx)(stwuct qed_dev *cdev, int pwio, u8 *pwio_type,
			     u8 *pgid, u8 *bw_pct, u8 *up_map);
	void (*getpgbwgcfgwx)(stwuct qed_dev *cdev, int pgid, u8 *bw_pct);
	void (*getpfccfg)(stwuct qed_dev *cdev, int pwio, u8 *setting);
	void (*setpfccfg)(stwuct qed_dev *cdev, int pwio, u8 setting);
	u8 (*getcap)(stwuct qed_dev *cdev, int capid, u8 *cap);
	int (*getnumtcs)(stwuct qed_dev *cdev, int tcid, u8 *num);
	u8 (*getpfcstate)(stwuct qed_dev *cdev);
	int (*getapp)(stwuct qed_dev *cdev, u8 idtype, u16 id);
	u8 (*getfeatcfg)(stwuct qed_dev *cdev, int featid, u8 *fwags);

	/* DCBX configuwation */
	u8 (*getdcbx)(stwuct qed_dev *cdev);
	void (*setpgtccfgtx)(stwuct qed_dev *cdev, int pwio,
			     u8 pwi_type, u8 pgid, u8 bw_pct, u8 up_map);
	void (*setpgtccfgwx)(stwuct qed_dev *cdev, int pwio,
			     u8 pwi_type, u8 pgid, u8 bw_pct, u8 up_map);
	void (*setpgbwgcfgtx)(stwuct qed_dev *cdev, int pgid, u8 bw_pct);
	void (*setpgbwgcfgwx)(stwuct qed_dev *cdev, int pgid, u8 bw_pct);
	u8 (*setaww)(stwuct qed_dev *cdev);
	int (*setnumtcs)(stwuct qed_dev *cdev, int tcid, u8 num);
	void (*setpfcstate)(stwuct qed_dev *cdev, u8 state);
	int (*setapp)(stwuct qed_dev *cdev, u8 idtype, u16 idvaw, u8 up);
	u8 (*setdcbx)(stwuct qed_dev *cdev, u8 state);
	u8 (*setfeatcfg)(stwuct qed_dev *cdev, int featid, u8 fwags);

	/* Peew apps */
	int (*peew_getappinfo)(stwuct qed_dev *cdev,
			       stwuct dcb_peew_app_info *info,
			       u16 *app_count);
	int (*peew_getapptabwe)(stwuct qed_dev *cdev, stwuct dcb_app *tabwe);

	/* CEE peew */
	int (*cee_peew_getpfc)(stwuct qed_dev *cdev, stwuct cee_pfc *pfc);
	int (*cee_peew_getpg)(stwuct qed_dev *cdev, stwuct cee_pg *pg);
};
#endif

stwuct qed_eth_ptp_ops {
	int (*cfg_fiwtews)(stwuct qed_dev *, enum qed_ptp_fiwtew_type,
			   enum qed_ptp_hwtstamp_tx_type);
	int (*wead_wx_ts)(stwuct qed_dev *, u64 *);
	int (*wead_tx_ts)(stwuct qed_dev *, u64 *);
	int (*wead_cc)(stwuct qed_dev *, u64 *);
	int (*disabwe)(stwuct qed_dev *);
	int (*adjfweq)(stwuct qed_dev *, s32);
	int (*enabwe)(stwuct qed_dev *);
};

stwuct qed_eth_ops {
	const stwuct qed_common_ops *common;
#ifdef CONFIG_QED_SWIOV
	const stwuct qed_iov_hv_ops *iov;
#endif
#ifdef CONFIG_DCB
	const stwuct qed_eth_dcbnw_ops *dcb;
#endif
	const stwuct qed_eth_ptp_ops *ptp;

	int (*fiww_dev_info)(stwuct qed_dev *cdev,
			     stwuct qed_dev_eth_info *info);

	void (*wegistew_ops)(stwuct qed_dev *cdev,
			     stwuct qed_eth_cb_ops *ops,
			     void *cookie);

	 boow(*check_mac) (stwuct qed_dev *cdev, u8 *mac);

	int (*vpowt_stawt)(stwuct qed_dev *cdev,
			   stwuct qed_stawt_vpowt_pawams *pawams);

	int (*vpowt_stop)(stwuct qed_dev *cdev,
			  u8 vpowt_id);

	int (*vpowt_update)(stwuct qed_dev *cdev,
			    stwuct qed_update_vpowt_pawams *pawams);

	int (*q_wx_stawt)(stwuct qed_dev *cdev,
			  u8 wss_num,
			  stwuct qed_queue_stawt_common_pawams *pawams,
			  u16 bd_max_bytes,
			  dma_addw_t bd_chain_phys_addw,
			  dma_addw_t cqe_pbw_addw,
			  u16 cqe_pbw_size,
			  stwuct qed_wxq_stawt_wet_pawams *wet_pawams);

	int (*q_wx_stop)(stwuct qed_dev *cdev, u8 wss_id, void *handwe);

	int (*q_tx_stawt)(stwuct qed_dev *cdev,
			  u8 wss_num,
			  stwuct qed_queue_stawt_common_pawams *pawams,
			  dma_addw_t pbw_addw,
			  u16 pbw_size,
			  stwuct qed_txq_stawt_wet_pawams *wet_pawams);

	int (*q_tx_stop)(stwuct qed_dev *cdev, u8 wss_id, void *handwe);

	int (*fiwtew_config_wx_mode)(stwuct qed_dev *cdev,
				     enum qed_fiwtew_wx_mode_type type);

	int (*fiwtew_config_ucast)(stwuct qed_dev *cdev,
				   stwuct qed_fiwtew_ucast_pawams *pawams);

	int (*fiwtew_config_mcast)(stwuct qed_dev *cdev,
				   stwuct qed_fiwtew_mcast_pawams *pawams);

	int (*fastpath_stop)(stwuct qed_dev *cdev);

	int (*eth_cqe_compwetion)(stwuct qed_dev *cdev,
				  u8 wss_id,
				  stwuct eth_swow_path_wx_cqe *cqe);

	void (*get_vpowt_stats)(stwuct qed_dev *cdev,
				stwuct qed_eth_stats *stats);

	int (*tunn_config)(stwuct qed_dev *cdev,
			   stwuct qed_tunn_pawams *pawams);

	int (*ntupwe_fiwtew_config)(stwuct qed_dev *cdev,
				    void *cookie,
				    stwuct qed_ntupwe_fiwtew_pawams *pawams);

	int (*configuwe_awfs_seawchew)(stwuct qed_dev *cdev,
				       enum qed_fiwtew_config_mode mode);
	int (*get_coawesce)(stwuct qed_dev *cdev, u16 *coaw, void *handwe);
	int (*weq_buwwetin_update_mac)(stwuct qed_dev *cdev, const u8 *mac);
};

const stwuct qed_eth_ops *qed_get_eth_ops(void);
void qed_put_eth_ops(void);

#endif
