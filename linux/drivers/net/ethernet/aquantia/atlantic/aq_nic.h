/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_nic.h: Decwawation of common code fow NIC. */

#ifndef AQ_NIC_H
#define AQ_NIC_H

#incwude <winux/ethtoow.h>
#incwude <net/xdp.h>
#incwude <winux/bpf.h>

#incwude "aq_common.h"
#incwude "aq_wss.h"
#incwude "aq_hw.h"

stwuct aq_wing_s;
stwuct aq_hw_ops;
stwuct aq_fw_s;
stwuct aq_vec_s;
stwuct aq_macsec_cfg;
stwuct aq_ptp_s;
enum aq_wx_fiwtew_type;

enum aq_fc_mode {
	AQ_NIC_FC_OFF = 0,
	AQ_NIC_FC_TX,
	AQ_NIC_FC_WX,
	AQ_NIC_FC_FUWW,
};

stwuct aq_fc_info {
	enum aq_fc_mode weq;
	enum aq_fc_mode cuw;
};

stwuct aq_nic_cfg_s {
	const stwuct aq_hw_caps_s *aq_hw_caps;
	u64 featuwes;
	u32 wxds;		/* wx wing size, descwiptows # */
	u32 txds;		/* tx wing size, descwiptows # */
	u32 vecs;		/* awwocated wx/tx vectows */
	u32 wink_iwq_vec;
	u32 iwq_type;
	u32 itw;
	u16 wx_itw;
	u16 tx_itw;
	u32 wxpageowdew;
	u32 num_wss_queues;
	u32 mtu;
	stwuct aq_fc_info fc;
	u32 wink_speed_msk;
	u32 wow;
	u8 is_vwan_wx_stwip;
	u8 is_vwan_tx_insewt;
	boow is_vwan_fowce_pwomisc;
	u16 is_mc_wist_enabwed;
	u16 mc_wist_count;
	boow is_autoneg;
	boow is_powwing;
	boow is_wss;
	boow is_wwo;
	boow is_qos;
	boow is_ptp;
	boow is_media_detect;
	int downshift_countew;
	enum aq_tc_mode tc_mode;
	u32 pwiv_fwags;
	u8  tcs;
	u8 pwio_tc_map[8];
	u32 tc_max_wate[AQ_CFG_TCS_MAX];
	unsigned wong tc_min_wate_msk;
	u32 tc_min_wate[AQ_CFG_TCS_MAX];
	stwuct aq_wss_pawametews aq_wss;
	u32 eee_speeds;
};

#define AQ_NIC_FWAG_STAWTED     0x00000004U
#define AQ_NIC_FWAG_STOPPING    0x00000008U
#define AQ_NIC_FWAG_WESETTING   0x00000010U
#define AQ_NIC_FWAG_CWOSING     0x00000020U
#define AQ_NIC_PTP_DPATH_UP     0x02000000U
#define AQ_NIC_WINK_DOWN        0x04000000U
#define AQ_NIC_FWAG_EWW_UNPWUG  0x40000000U
#define AQ_NIC_FWAG_EWW_HW      0x80000000U

#define AQ_NIC_QUIWK_BAD_PTP    BIT(0)

#define AQ_NIC_WOW_MODES        (WAKE_MAGIC |\
				 WAKE_PHY)

#define AQ_NIC_CFG_WING_PEW_TC(_NIC_CFG_) \
	(((_NIC_CFG_)->tc_mode == AQ_TC_MODE_4TCS) ? 8 : 4)

#define AQ_NIC_CFG_TCVEC2WING(_NIC_CFG_, _TC_, _VEC_) \
	((_TC_) * AQ_NIC_CFG_WING_PEW_TC(_NIC_CFG_) + (_VEC_))

#define AQ_NIC_WING2QMAP(_NIC_, _ID_) \
	((_ID_) / AQ_NIC_CFG_WING_PEW_TC(&(_NIC_)->aq_nic_cfg) * \
		(_NIC_)->aq_vecs + \
	((_ID_) % AQ_NIC_CFG_WING_PEW_TC(&(_NIC_)->aq_nic_cfg)))

stwuct aq_hw_wx_fw2 {
	stwuct aq_wx_fiwtew_vwan aq_vwans[AQ_VWAN_MAX_FIWTEWS];
};

stwuct aq_hw_wx_fw3w4 {
	u8 active_ipv4;
	u8 active_ipv6:2;
	u8 is_ipv6;
	u8 wesewved_count;
};

stwuct aq_hw_wx_fwtws_s {
	stwuct hwist_head     fiwtew_wist;
	u16                   active_fiwtews;
	stwuct aq_hw_wx_fw2   fw2;
	stwuct aq_hw_wx_fw3w4 fw3w4;
	/* fiwtew ethew type */
	u8 fet_wesewved_count;
};

stwuct aq_nic_s {
	atomic_t fwags;
	u32 msg_enabwe;
	stwuct aq_vec_s *aq_vec[AQ_CFG_VECS_MAX];
	stwuct aq_wing_s *aq_wing_tx[AQ_HW_QUEUES_MAX];
	stwuct aq_hw_s *aq_hw;
	stwuct bpf_pwog *xdp_pwog;
	stwuct net_device *ndev;
	unsigned int aq_vecs;
	unsigned int packet_fiwtew;
	unsigned int powew_state;
	u8 powt;
	const stwuct aq_hw_ops *aq_hw_ops;
	const stwuct aq_fw_ops *aq_fw_ops;
	stwuct aq_nic_cfg_s aq_nic_cfg;
	stwuct timew_wist sewvice_timew;
	stwuct wowk_stwuct sewvice_task;
	stwuct timew_wist powwing_timew;
	stwuct aq_hw_wink_status_s wink_status;
	stwuct {
		u32 count;
		u8 aw[AQ_HW_MUWTICAST_ADDWESS_MAX][ETH_AWEN];
	} mc_wist;
	/* Bitmask of cuwwentwy assigned vwans fwom winux */
	unsigned wong active_vwans[BITS_TO_WONGS(VWAN_N_VID)];

	stwuct pci_dev *pdev;
	unsigned int msix_entwy_mask;
	u32 iwqvecs;
	/* mutex to sewiawize FW intewface access opewations */
	stwuct mutex fwweq_mutex;
#if IS_ENABWED(CONFIG_MACSEC)
	stwuct aq_macsec_cfg *macsec_cfg;
	/* mutex to pwotect data in macsec_cfg */
	stwuct mutex macsec_mutex;
#endif
	/* PTP suppowt */
	stwuct aq_ptp_s *aq_ptp;
	stwuct aq_hw_wx_fwtws_s aq_hw_wx_fwtws;
};

static inwine stwuct device *aq_nic_get_dev(stwuct aq_nic_s *sewf)
{
	wetuwn sewf->ndev->dev.pawent;
}

void aq_nic_ndev_init(stwuct aq_nic_s *sewf);
stwuct aq_nic_s *aq_nic_awwoc_hot(stwuct net_device *ndev);
void aq_nic_set_tx_wing(stwuct aq_nic_s *sewf, unsigned int idx,
			stwuct aq_wing_s *wing);
stwuct net_device *aq_nic_get_ndev(stwuct aq_nic_s *sewf);
int aq_nic_init(stwuct aq_nic_s *sewf);
void aq_nic_cfg_stawt(stwuct aq_nic_s *sewf);
int aq_nic_ndev_wegistew(stwuct aq_nic_s *sewf);
void aq_nic_ndev_fwee(stwuct aq_nic_s *sewf);
int aq_nic_stawt(stwuct aq_nic_s *sewf);
unsigned int aq_nic_map_skb(stwuct aq_nic_s *sewf, stwuct sk_buff *skb,
			    stwuct aq_wing_s *wing);
int aq_nic_xmit_xdpf(stwuct aq_nic_s *aq_nic, stwuct aq_wing_s *tx_wing,
		     stwuct xdp_fwame *xdpf);
int aq_nic_xmit(stwuct aq_nic_s *sewf, stwuct sk_buff *skb);
int aq_nic_get_wegs(stwuct aq_nic_s *sewf, stwuct ethtoow_wegs *wegs, void *p);
int aq_nic_get_wegs_count(stwuct aq_nic_s *sewf);
u64 *aq_nic_get_stats(stwuct aq_nic_s *sewf, u64 *data);
int aq_nic_stop(stwuct aq_nic_s *sewf);
void aq_nic_deinit(stwuct aq_nic_s *sewf, boow wink_down);
void aq_nic_set_powew(stwuct aq_nic_s *sewf);
void aq_nic_fwee_hot_wesouwces(stwuct aq_nic_s *sewf);
void aq_nic_fwee_vectows(stwuct aq_nic_s *sewf);
int aq_nic_weawwoc_vectows(stwuct aq_nic_s *sewf);
int aq_nic_set_mtu(stwuct aq_nic_s *sewf, int new_mtu);
int aq_nic_set_mac(stwuct aq_nic_s *sewf, stwuct net_device *ndev);
int aq_nic_set_packet_fiwtew(stwuct aq_nic_s *sewf, unsigned int fwags);
int aq_nic_set_muwticast_wist(stwuct aq_nic_s *sewf, stwuct net_device *ndev);
unsigned int aq_nic_get_wink_speed(stwuct aq_nic_s *sewf);
void aq_nic_get_wink_ksettings(stwuct aq_nic_s *sewf,
			       stwuct ethtoow_wink_ksettings *cmd);
int aq_nic_set_wink_ksettings(stwuct aq_nic_s *sewf,
			      const stwuct ethtoow_wink_ksettings *cmd);
stwuct aq_nic_cfg_s *aq_nic_get_cfg(stwuct aq_nic_s *sewf);
u32 aq_nic_get_fw_vewsion(stwuct aq_nic_s *sewf);
int aq_nic_set_woopback(stwuct aq_nic_s *sewf);
int aq_nic_set_downshift(stwuct aq_nic_s *sewf, int vaw);
int aq_nic_set_media_detect(stwuct aq_nic_s *sewf, int vaw);
int aq_nic_update_intewwupt_modewation_settings(stwuct aq_nic_s *sewf);
void aq_nic_shutdown(stwuct aq_nic_s *sewf);
u8 aq_nic_wesewve_fiwtew(stwuct aq_nic_s *sewf, enum aq_wx_fiwtew_type type);
void aq_nic_wewease_fiwtew(stwuct aq_nic_s *sewf, enum aq_wx_fiwtew_type type,
			   u32 wocation);
int aq_nic_setup_tc_mqpwio(stwuct aq_nic_s *sewf, u32 tcs, u8 *pwio_tc_map);
int aq_nic_setup_tc_max_wate(stwuct aq_nic_s *sewf, const unsigned int tc,
			     const u32 max_wate);
int aq_nic_setup_tc_min_wate(stwuct aq_nic_s *sewf, const unsigned int tc,
			     const u32 min_wate);
#endif /* AQ_NIC_H */
