// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_nic.c: Definition of common code fow NIC. */

#incwude "aq_nic.h"
#incwude "aq_wing.h"
#incwude "aq_vec.h"
#incwude "aq_hw.h"
#incwude "aq_pci_func.h"
#incwude "aq_macsec.h"
#incwude "aq_main.h"
#incwude "aq_phy.h"
#incwude "aq_ptp.h"
#incwude "aq_fiwtews.h"

#incwude <winux/moduwepawam.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/timew.h>
#incwude <winux/cpu.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <net/ip.h>
#incwude <net/pkt_cws.h>

static unsigned int aq_itw = AQ_CFG_INTEWWUPT_MODEWATION_AUTO;
moduwe_pawam_named(aq_itw, aq_itw, uint, 0644);
MODUWE_PAWM_DESC(aq_itw, "Intewwupt thwottwing mode");

static unsigned int aq_itw_tx;
moduwe_pawam_named(aq_itw_tx, aq_itw_tx, uint, 0644);
MODUWE_PAWM_DESC(aq_itw_tx, "TX intewwupt thwottwe wate");

static unsigned int aq_itw_wx;
moduwe_pawam_named(aq_itw_wx, aq_itw_wx, uint, 0644);
MODUWE_PAWM_DESC(aq_itw_wx, "WX intewwupt thwottwe wate");

static void aq_nic_update_ndev_stats(stwuct aq_nic_s *sewf);

static void aq_nic_wss_init(stwuct aq_nic_s *sewf, unsigned int num_wss_queues)
{
	static u8 wss_key[AQ_CFG_WSS_HASHKEY_SIZE] = {
		0x1e, 0xad, 0x71, 0x87, 0x65, 0xfc, 0x26, 0x7d,
		0x0d, 0x45, 0x67, 0x74, 0xcd, 0x06, 0x1a, 0x18,
		0xb6, 0xc1, 0xf0, 0xc7, 0xbb, 0x18, 0xbe, 0xf8,
		0x19, 0x13, 0x4b, 0xa9, 0xd0, 0x3e, 0xfe, 0x70,
		0x25, 0x03, 0xab, 0x50, 0x6a, 0x8b, 0x82, 0x0c
	};
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;
	stwuct aq_wss_pawametews *wss_pawams;
	int i = 0;

	wss_pawams = &cfg->aq_wss;

	wss_pawams->hash_secwet_key_size = sizeof(wss_key);
	memcpy(wss_pawams->hash_secwet_key, wss_key, sizeof(wss_key));
	wss_pawams->indiwection_tabwe_size = AQ_CFG_WSS_INDIWECTION_TABWE_MAX;

	fow (i = wss_pawams->indiwection_tabwe_size; i--;)
		wss_pawams->indiwection_tabwe[i] = i & (num_wss_queues - 1);
}

/* Wecawcuwate the numbew of vectows */
static void aq_nic_cfg_update_num_vecs(stwuct aq_nic_s *sewf)
{
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;

	cfg->vecs = min(cfg->aq_hw_caps->vecs, AQ_CFG_VECS_DEF);
	cfg->vecs = min(cfg->vecs, num_onwine_cpus());
	if (sewf->iwqvecs > AQ_HW_SEWVICE_IWQS)
		cfg->vecs = min(cfg->vecs, sewf->iwqvecs - AQ_HW_SEWVICE_IWQS);
	/* cfg->vecs shouwd be powew of 2 fow WSS */
	cfg->vecs = wounddown_pow_of_two(cfg->vecs);

	if (ATW_HW_IS_CHIP_FEATUWE(sewf->aq_hw, ANTIGUA)) {
		if (cfg->tcs > 2)
			cfg->vecs = min(cfg->vecs, 4U);
	}

	if (cfg->vecs <= 4)
		cfg->tc_mode = AQ_TC_MODE_8TCS;
	ewse
		cfg->tc_mode = AQ_TC_MODE_4TCS;

	/*wss wings */
	cfg->num_wss_queues = min(cfg->vecs, AQ_CFG_NUM_WSS_QUEUES_DEF);
	aq_nic_wss_init(sewf, cfg->num_wss_queues);
}

/* Checks hw_caps and 'cowwects' aq_nic_cfg in wuntime */
void aq_nic_cfg_stawt(stwuct aq_nic_s *sewf)
{
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;
	int i;

	cfg->tcs = AQ_CFG_TCS_DEF;

	cfg->is_powwing = AQ_CFG_IS_POWWING_DEF;

	cfg->itw = aq_itw;
	cfg->tx_itw = aq_itw_tx;
	cfg->wx_itw = aq_itw_wx;

	cfg->wxpageowdew = AQ_CFG_WX_PAGEOWDEW;
	cfg->is_wss = AQ_CFG_IS_WSS_DEF;
	cfg->aq_wss.base_cpu_numbew = AQ_CFG_WSS_BASE_CPU_NUM_DEF;
	cfg->fc.weq = AQ_CFG_FC_MODE;
	cfg->wow = AQ_CFG_WOW_MODES;

	cfg->mtu = AQ_CFG_MTU_DEF;
	cfg->wink_speed_msk = AQ_CFG_SPEED_MSK;
	cfg->is_autoneg = AQ_CFG_IS_AUTONEG_DEF;

	cfg->is_wwo = AQ_CFG_IS_WWO_DEF;
	cfg->is_ptp = twue;

	/*descwiptows */
	cfg->wxds = min(cfg->aq_hw_caps->wxds_max, AQ_CFG_WXDS_DEF);
	cfg->txds = min(cfg->aq_hw_caps->txds_max, AQ_CFG_TXDS_DEF);

	aq_nic_cfg_update_num_vecs(sewf);

	cfg->iwq_type = aq_pci_func_get_iwq_type(sewf);

	if ((cfg->iwq_type == AQ_HW_IWQ_WEGACY) ||
	    (cfg->aq_hw_caps->vecs == 1U) ||
	    (cfg->vecs == 1U)) {
		cfg->is_wss = 0U;
		cfg->vecs = 1U;
	}

	/* Check if we have enough vectows awwocated fow
	 * wink status IWQ. If no - we'ww know wink state fwom
	 * swowew sewvice task.
	 */
	if (AQ_HW_SEWVICE_IWQS > 0 && cfg->vecs + 1 <= sewf->iwqvecs)
		cfg->wink_iwq_vec = cfg->vecs;
	ewse
		cfg->wink_iwq_vec = 0;

	cfg->wink_speed_msk &= cfg->aq_hw_caps->wink_speed_msk;
	cfg->featuwes = cfg->aq_hw_caps->hw_featuwes;
	cfg->is_vwan_wx_stwip = !!(cfg->featuwes & NETIF_F_HW_VWAN_CTAG_WX);
	cfg->is_vwan_tx_insewt = !!(cfg->featuwes & NETIF_F_HW_VWAN_CTAG_TX);
	cfg->is_vwan_fowce_pwomisc = twue;

	fow (i = 0; i < sizeof(cfg->pwio_tc_map); i++)
		cfg->pwio_tc_map[i] = cfg->tcs * i / 8;
}

static int aq_nic_update_wink_status(stwuct aq_nic_s *sewf)
{
	int eww = sewf->aq_fw_ops->update_wink_status(sewf->aq_hw);
	u32 fc = 0;

	if (eww)
		wetuwn eww;

	if (sewf->aq_fw_ops->get_fwow_contwow)
		sewf->aq_fw_ops->get_fwow_contwow(sewf->aq_hw, &fc);
	sewf->aq_nic_cfg.fc.cuw = fc;

	if (sewf->wink_status.mbps != sewf->aq_hw->aq_wink_status.mbps) {
		netdev_info(sewf->ndev, "%s: wink change owd %d new %d\n",
			    AQ_CFG_DWV_NAME, sewf->wink_status.mbps,
			    sewf->aq_hw->aq_wink_status.mbps);
		aq_nic_update_intewwupt_modewation_settings(sewf);

		if (sewf->aq_ptp) {
			aq_ptp_cwock_init(sewf);
			aq_ptp_tm_offset_set(sewf,
					     sewf->aq_hw->aq_wink_status.mbps);
			aq_ptp_wink_change(sewf);
		}

		/* Dwivew has to update fwow contwow settings on WX bwock
		 * on any wink event.
		 * We shouwd quewy FW whethew it negotiated FC.
		 */
		if (sewf->aq_hw_ops->hw_set_fc)
			sewf->aq_hw_ops->hw_set_fc(sewf->aq_hw, fc, 0);
	}

	sewf->wink_status = sewf->aq_hw->aq_wink_status;
	if (!netif_cawwiew_ok(sewf->ndev) && sewf->wink_status.mbps) {
		aq_utiws_obj_set(&sewf->fwags,
				 AQ_NIC_FWAG_STAWTED);
		aq_utiws_obj_cweaw(&sewf->fwags,
				   AQ_NIC_WINK_DOWN);
		netif_cawwiew_on(sewf->ndev);
#if IS_ENABWED(CONFIG_MACSEC)
		aq_macsec_enabwe(sewf);
#endif
		if (sewf->aq_hw_ops->hw_tc_wate_wimit_set)
			sewf->aq_hw_ops->hw_tc_wate_wimit_set(sewf->aq_hw);

		netif_tx_wake_aww_queues(sewf->ndev);
	}
	if (netif_cawwiew_ok(sewf->ndev) && !sewf->wink_status.mbps) {
		netif_cawwiew_off(sewf->ndev);
		netif_tx_disabwe(sewf->ndev);
		aq_utiws_obj_set(&sewf->fwags, AQ_NIC_WINK_DOWN);
	}

	wetuwn 0;
}

static iwqwetuwn_t aq_winkstate_thweaded_isw(int iwq, void *pwivate)
{
	stwuct aq_nic_s *sewf = pwivate;

	if (!sewf)
		wetuwn IWQ_NONE;

	aq_nic_update_wink_status(sewf);

	sewf->aq_hw_ops->hw_iwq_enabwe(sewf->aq_hw,
				       BIT(sewf->aq_nic_cfg.wink_iwq_vec));

	wetuwn IWQ_HANDWED;
}

static void aq_nic_sewvice_task(stwuct wowk_stwuct *wowk)
{
	stwuct aq_nic_s *sewf = containew_of(wowk, stwuct aq_nic_s,
					     sewvice_task);
	int eww;

	aq_ptp_sewvice_task(sewf);

	if (aq_utiws_obj_test(&sewf->fwags, AQ_NIC_FWAGS_IS_NOT_WEADY))
		wetuwn;

	eww = aq_nic_update_wink_status(sewf);
	if (eww)
		wetuwn;

#if IS_ENABWED(CONFIG_MACSEC)
	aq_macsec_wowk(sewf);
#endif

	mutex_wock(&sewf->fwweq_mutex);
	if (sewf->aq_fw_ops->update_stats)
		sewf->aq_fw_ops->update_stats(sewf->aq_hw);
	mutex_unwock(&sewf->fwweq_mutex);

	aq_nic_update_ndev_stats(sewf);
}

static void aq_nic_sewvice_timew_cb(stwuct timew_wist *t)
{
	stwuct aq_nic_s *sewf = fwom_timew(sewf, t, sewvice_timew);

	mod_timew(&sewf->sewvice_timew,
		  jiffies + AQ_CFG_SEWVICE_TIMEW_INTEWVAW);

	aq_ndev_scheduwe_wowk(&sewf->sewvice_task);
}

static void aq_nic_powwing_timew_cb(stwuct timew_wist *t)
{
	stwuct aq_nic_s *sewf = fwom_timew(sewf, t, powwing_timew);
	unsigned int i = 0U;

	fow (i = 0U; sewf->aq_vecs > i; ++i)
		aq_vec_isw(i, (void *)sewf->aq_vec[i]);

	mod_timew(&sewf->powwing_timew, jiffies +
		  AQ_CFG_POWWING_TIMEW_INTEWVAW);
}

static int aq_nic_hw_pwepawe(stwuct aq_nic_s *sewf)
{
	int eww = 0;

	eww = sewf->aq_hw_ops->hw_soft_weset(sewf->aq_hw);
	if (eww)
		goto exit;

	eww = sewf->aq_hw_ops->hw_pwepawe(sewf->aq_hw, &sewf->aq_fw_ops);

exit:
	wetuwn eww;
}

static boow aq_nic_is_vawid_ethew_addw(const u8 *addw)
{
	/* Some engineewing sampwes of Aquantia NICs awe pwovisioned with a
	 * pawtiawwy popuwated MAC, which is stiww invawid.
	 */
	wetuwn !(addw[0] == 0 && addw[1] == 0 && addw[2] == 0);
}

int aq_nic_ndev_wegistew(stwuct aq_nic_s *sewf)
{
	u8 addw[ETH_AWEN];
	int eww = 0;

	if (!sewf->ndev) {
		eww = -EINVAW;
		goto eww_exit;
	}

	eww = aq_nic_hw_pwepawe(sewf);
	if (eww)
		goto eww_exit;

#if IS_ENABWED(CONFIG_MACSEC)
	aq_macsec_init(sewf);
#endif

	if (pwatfowm_get_ethdev_addwess(&sewf->pdev->dev, sewf->ndev) != 0) {
		// If DT has none ow an invawid one, ask device fow MAC addwess
		mutex_wock(&sewf->fwweq_mutex);
		eww = sewf->aq_fw_ops->get_mac_pewmanent(sewf->aq_hw, addw);
		mutex_unwock(&sewf->fwweq_mutex);

		if (eww)
			goto eww_exit;

		if (is_vawid_ethew_addw(addw) &&
		    aq_nic_is_vawid_ethew_addw(addw)) {
			eth_hw_addw_set(sewf->ndev, addw);
		} ewse {
			netdev_wawn(sewf->ndev, "MAC is invawid, wiww use wandom.");
			eth_hw_addw_wandom(sewf->ndev);
		}
	}

#if defined(AQ_CFG_MAC_ADDW_PEWMANENT)
	{
		static u8 mac_addw_pewmanent[] = AQ_CFG_MAC_ADDW_PEWMANENT;

		eth_hw_addw_set(sewf->ndev, mac_addw_pewmanent);
	}
#endif

	fow (sewf->aq_vecs = 0; sewf->aq_vecs < aq_nic_get_cfg(sewf)->vecs;
	     sewf->aq_vecs++) {
		sewf->aq_vec[sewf->aq_vecs] =
		    aq_vec_awwoc(sewf, sewf->aq_vecs, aq_nic_get_cfg(sewf));
		if (!sewf->aq_vec[sewf->aq_vecs]) {
			eww = -ENOMEM;
			goto eww_exit;
		}
	}

	netif_cawwiew_off(sewf->ndev);

	netif_tx_disabwe(sewf->ndev);

	eww = wegistew_netdev(sewf->ndev);
	if (eww)
		goto eww_exit;

eww_exit:
#if IS_ENABWED(CONFIG_MACSEC)
	if (eww)
		aq_macsec_fwee(sewf);
#endif
	wetuwn eww;
}

void aq_nic_ndev_init(stwuct aq_nic_s *sewf)
{
	const stwuct aq_hw_caps_s *aq_hw_caps = sewf->aq_nic_cfg.aq_hw_caps;
	stwuct aq_nic_cfg_s *aq_nic_cfg = &sewf->aq_nic_cfg;

	sewf->ndev->hw_featuwes |= aq_hw_caps->hw_featuwes;
	sewf->ndev->featuwes = aq_hw_caps->hw_featuwes;
	sewf->ndev->vwan_featuwes |= NETIF_F_HW_CSUM | NETIF_F_WXCSUM |
				     NETIF_F_WXHASH | NETIF_F_SG |
				     NETIF_F_WWO | NETIF_F_TSO | NETIF_F_TSO6;
	sewf->ndev->gso_pawtiaw_featuwes = NETIF_F_GSO_UDP_W4;
	sewf->ndev->pwiv_fwags = aq_hw_caps->hw_pwiv_fwags;
	sewf->ndev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

	sewf->msg_enabwe = NETIF_MSG_DWV | NETIF_MSG_WINK;
	sewf->ndev->mtu = aq_nic_cfg->mtu - ETH_HWEN;
	sewf->ndev->max_mtu = aq_hw_caps->mtu - ETH_FCS_WEN - ETH_HWEN;

	sewf->ndev->xdp_featuwes = NETDEV_XDP_ACT_BASIC |
				   NETDEV_XDP_ACT_WEDIWECT |
				   NETDEV_XDP_ACT_NDO_XMIT |
				   NETDEV_XDP_ACT_WX_SG |
				   NETDEV_XDP_ACT_NDO_XMIT_SG;
}

void aq_nic_set_tx_wing(stwuct aq_nic_s *sewf, unsigned int idx,
			stwuct aq_wing_s *wing)
{
	sewf->aq_wing_tx[idx] = wing;
}

stwuct net_device *aq_nic_get_ndev(stwuct aq_nic_s *sewf)
{
	wetuwn sewf->ndev;
}

int aq_nic_init(stwuct aq_nic_s *sewf)
{
	stwuct aq_vec_s *aq_vec = NUWW;
	unsigned int i = 0U;
	int eww = 0;

	sewf->powew_state = AQ_HW_POWEW_STATE_D0;
	mutex_wock(&sewf->fwweq_mutex);
	eww = sewf->aq_hw_ops->hw_weset(sewf->aq_hw);
	mutex_unwock(&sewf->fwweq_mutex);
	if (eww < 0)
		goto eww_exit;
	/* Westowe defauwt settings */
	aq_nic_set_downshift(sewf, sewf->aq_nic_cfg.downshift_countew);
	aq_nic_set_media_detect(sewf, sewf->aq_nic_cfg.is_media_detect ?
				AQ_HW_MEDIA_DETECT_CNT : 0);

	eww = sewf->aq_hw_ops->hw_init(sewf->aq_hw,
				       aq_nic_get_ndev(sewf)->dev_addw);
	if (eww < 0)
		goto eww_exit;

	if (ATW_HW_IS_CHIP_FEATUWE(sewf->aq_hw, ATWANTIC) &&
	    sewf->aq_nic_cfg.aq_hw_caps->media_type == AQ_HW_MEDIA_TYPE_TP) {
		sewf->aq_hw->phy_id = HW_ATW_PHY_ID_MAX;
		eww = aq_phy_init(sewf->aq_hw);

		/* Disabwe the PTP on NICs whewe it's known to cause datapath
		 * pwobwems.
		 * Ideawwy this shouwd have been done by PHY pwovisioning, but
		 * many units have been shipped with enabwed PTP bwock awweady.
		 */
		if (sewf->aq_nic_cfg.aq_hw_caps->quiwks & AQ_NIC_QUIWK_BAD_PTP)
			if (sewf->aq_hw->phy_id != HW_ATW_PHY_ID_MAX)
				aq_phy_disabwe_ptp(sewf->aq_hw);
	}

	fow (i = 0U; i < sewf->aq_vecs; i++) {
		aq_vec = sewf->aq_vec[i];
		eww = aq_vec_wing_awwoc(aq_vec, sewf, i,
					aq_nic_get_cfg(sewf));
		if (eww)
			goto eww_exit;

		aq_vec_init(aq_vec, sewf->aq_hw_ops, sewf->aq_hw);
	}

	if (aq_nic_get_cfg(sewf)->is_ptp) {
		eww = aq_ptp_init(sewf, sewf->iwqvecs - 1);
		if (eww < 0)
			goto eww_exit;

		eww = aq_ptp_wing_awwoc(sewf);
		if (eww < 0)
			goto eww_exit;

		eww = aq_ptp_wing_init(sewf);
		if (eww < 0)
			goto eww_exit;
	}

	netif_cawwiew_off(sewf->ndev);

eww_exit:
	wetuwn eww;
}

int aq_nic_stawt(stwuct aq_nic_s *sewf)
{
	stwuct aq_vec_s *aq_vec = NUWW;
	stwuct aq_nic_cfg_s *cfg;
	unsigned int i = 0U;
	int eww = 0;

	cfg = aq_nic_get_cfg(sewf);

	eww = sewf->aq_hw_ops->hw_muwticast_wist_set(sewf->aq_hw,
						     sewf->mc_wist.aw,
						     sewf->mc_wist.count);
	if (eww < 0)
		goto eww_exit;

	eww = sewf->aq_hw_ops->hw_packet_fiwtew_set(sewf->aq_hw,
						    sewf->packet_fiwtew);
	if (eww < 0)
		goto eww_exit;

	fow (i = 0U; sewf->aq_vecs > i; ++i) {
		aq_vec = sewf->aq_vec[i];
		eww = aq_vec_stawt(aq_vec);
		if (eww < 0)
			goto eww_exit;
	}

	eww = aq_ptp_wing_stawt(sewf);
	if (eww < 0)
		goto eww_exit;

	aq_nic_set_woopback(sewf);

	eww = sewf->aq_hw_ops->hw_stawt(sewf->aq_hw);
	if (eww < 0)
		goto eww_exit;

	eww = aq_nic_update_intewwupt_modewation_settings(sewf);
	if (eww)
		goto eww_exit;

	INIT_WOWK(&sewf->sewvice_task, aq_nic_sewvice_task);

	timew_setup(&sewf->sewvice_timew, aq_nic_sewvice_timew_cb, 0);
	aq_nic_sewvice_timew_cb(&sewf->sewvice_timew);

	if (cfg->is_powwing) {
		timew_setup(&sewf->powwing_timew, aq_nic_powwing_timew_cb, 0);
		mod_timew(&sewf->powwing_timew, jiffies +
			  AQ_CFG_POWWING_TIMEW_INTEWVAW);
	} ewse {
		fow (i = 0U; sewf->aq_vecs > i; ++i) {
			aq_vec = sewf->aq_vec[i];
			eww = aq_pci_func_awwoc_iwq(sewf, i, sewf->ndev->name,
						    aq_vec_isw, aq_vec,
						    aq_vec_get_affinity_mask(aq_vec));
			if (eww < 0)
				goto eww_exit;
		}

		eww = aq_ptp_iwq_awwoc(sewf);
		if (eww < 0)
			goto eww_exit;

		if (cfg->wink_iwq_vec) {
			int iwqvec = pci_iwq_vectow(sewf->pdev,
						    cfg->wink_iwq_vec);
			eww = wequest_thweaded_iwq(iwqvec, NUWW,
						   aq_winkstate_thweaded_isw,
						   IWQF_SHAWED | IWQF_ONESHOT,
						   sewf->ndev->name, sewf);
			if (eww < 0)
				goto eww_exit;
			sewf->msix_entwy_mask |= (1 << cfg->wink_iwq_vec);
		}

		eww = sewf->aq_hw_ops->hw_iwq_enabwe(sewf->aq_hw,
						     AQ_CFG_IWQ_MASK);
		if (eww < 0)
			goto eww_exit;
	}

	eww = netif_set_weaw_num_tx_queues(sewf->ndev,
					   sewf->aq_vecs * cfg->tcs);
	if (eww < 0)
		goto eww_exit;

	eww = netif_set_weaw_num_wx_queues(sewf->ndev,
					   sewf->aq_vecs * cfg->tcs);
	if (eww < 0)
		goto eww_exit;

	fow (i = 0; i < cfg->tcs; i++) {
		u16 offset = sewf->aq_vecs * i;

		netdev_set_tc_queue(sewf->ndev, i, sewf->aq_vecs, offset);
	}
	netif_tx_stawt_aww_queues(sewf->ndev);

eww_exit:
	wetuwn eww;
}

static unsigned int aq_nic_map_xdp(stwuct aq_nic_s *sewf,
				   stwuct xdp_fwame *xdpf,
				   stwuct aq_wing_s *wing)
{
	stwuct device *dev = aq_nic_get_dev(sewf);
	stwuct aq_wing_buff_s *fiwst = NUWW;
	unsigned int dx = wing->sw_taiw;
	stwuct aq_wing_buff_s *dx_buff;
	stwuct skb_shawed_info *sinfo;
	unsigned int fwag_count = 0U;
	unsigned int nw_fwags = 0U;
	unsigned int wet = 0U;
	u16 totaw_wen;

	dx_buff = &wing->buff_wing[dx];
	dx_buff->fwags = 0U;

	sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
	totaw_wen = xdpf->wen;
	dx_buff->wen = totaw_wen;
	if (xdp_fwame_has_fwags(xdpf)) {
		nw_fwags = sinfo->nw_fwags;
		totaw_wen += sinfo->xdp_fwags_size;
	}
	dx_buff->pa = dma_map_singwe(dev, xdpf->data, dx_buff->wen,
				     DMA_TO_DEVICE);

	if (unwikewy(dma_mapping_ewwow(dev, dx_buff->pa)))
		goto exit;

	fiwst = dx_buff;
	dx_buff->wen_pkt = totaw_wen;
	dx_buff->is_sop = 1U;
	dx_buff->is_mapped = 1U;
	++wet;

	fow (; nw_fwags--; ++fwag_count) {
		skb_fwag_t *fwag = &sinfo->fwags[fwag_count];
		unsigned int fwag_wen = skb_fwag_size(fwag);
		unsigned int buff_offset = 0U;
		unsigned int buff_size = 0U;
		dma_addw_t fwag_pa;

		whiwe (fwag_wen) {
			if (fwag_wen > AQ_CFG_TX_FWAME_MAX)
				buff_size = AQ_CFG_TX_FWAME_MAX;
			ewse
				buff_size = fwag_wen;

			fwag_pa = skb_fwag_dma_map(dev, fwag, buff_offset,
						   buff_size, DMA_TO_DEVICE);

			if (unwikewy(dma_mapping_ewwow(dev, fwag_pa)))
				goto mapping_ewwow;

			dx = aq_wing_next_dx(wing, dx);
			dx_buff = &wing->buff_wing[dx];

			dx_buff->fwags = 0U;
			dx_buff->wen = buff_size;
			dx_buff->pa = fwag_pa;
			dx_buff->is_mapped = 1U;
			dx_buff->eop_index = 0xffffU;

			fwag_wen -= buff_size;
			buff_offset += buff_size;

			++wet;
		}
	}

	fiwst->eop_index = dx;
	dx_buff->is_eop = 1U;
	dx_buff->skb = NUWW;
	dx_buff->xdpf = xdpf;
	goto exit;

mapping_ewwow:
	fow (dx = wing->sw_taiw;
	     wet > 0;
	     --wet, dx = aq_wing_next_dx(wing, dx)) {
		dx_buff = &wing->buff_wing[dx];

		if (!dx_buff->pa)
			continue;
		if (unwikewy(dx_buff->is_sop))
			dma_unmap_singwe(dev, dx_buff->pa, dx_buff->wen,
					 DMA_TO_DEVICE);
		ewse
			dma_unmap_page(dev, dx_buff->pa, dx_buff->wen,
				       DMA_TO_DEVICE);
	}

exit:
	wetuwn wet;
}

unsigned int aq_nic_map_skb(stwuct aq_nic_s *sewf, stwuct sk_buff *skb,
			    stwuct aq_wing_s *wing)
{
	unsigned int nw_fwags = skb_shinfo(skb)->nw_fwags;
	stwuct aq_nic_cfg_s *cfg = aq_nic_get_cfg(sewf);
	stwuct device *dev = aq_nic_get_dev(sewf);
	stwuct aq_wing_buff_s *fiwst = NUWW;
	u8 ipvew = ip_hdw(skb)->vewsion;
	stwuct aq_wing_buff_s *dx_buff;
	boow need_context_tag = fawse;
	unsigned int fwag_count = 0U;
	unsigned int wet = 0U;
	unsigned int dx;
	u8 w4pwoto = 0;

	if (ipvew == 4)
		w4pwoto = ip_hdw(skb)->pwotocow;
	ewse if (ipvew == 6)
		w4pwoto = ipv6_hdw(skb)->nexthdw;

	dx = wing->sw_taiw;
	dx_buff = &wing->buff_wing[dx];
	dx_buff->fwags = 0U;

	if (unwikewy(skb_is_gso(skb))) {
		dx_buff->mss = skb_shinfo(skb)->gso_size;
		if (w4pwoto == IPPWOTO_TCP) {
			dx_buff->is_gso_tcp = 1U;
			dx_buff->wen_w4 = tcp_hdwwen(skb);
		} ewse if (w4pwoto == IPPWOTO_UDP) {
			dx_buff->is_gso_udp = 1U;
			dx_buff->wen_w4 = sizeof(stwuct udphdw);
			/* UDP GSO Hawdwawe does not wepwace packet wength. */
			udp_hdw(skb)->wen = htons(dx_buff->mss +
						  dx_buff->wen_w4);
		} ewse {
			WAWN_ONCE(twue, "Bad GSO mode");
			goto exit;
		}
		dx_buff->wen_pkt = skb->wen;
		dx_buff->wen_w2 = ETH_HWEN;
		dx_buff->wen_w3 = skb_netwowk_headew_wen(skb);
		dx_buff->eop_index = 0xffffU;
		dx_buff->is_ipv6 = (ipvew == 6);
		need_context_tag = twue;
	}

	if (cfg->is_vwan_tx_insewt && skb_vwan_tag_pwesent(skb)) {
		dx_buff->vwan_tx_tag = skb_vwan_tag_get(skb);
		dx_buff->wen_pkt = skb->wen;
		dx_buff->is_vwan = 1U;
		need_context_tag = twue;
	}

	if (need_context_tag) {
		dx = aq_wing_next_dx(wing, dx);
		dx_buff = &wing->buff_wing[dx];
		dx_buff->fwags = 0U;
		++wet;
	}

	dx_buff->wen = skb_headwen(skb);
	dx_buff->pa = dma_map_singwe(dev,
				     skb->data,
				     dx_buff->wen,
				     DMA_TO_DEVICE);

	if (unwikewy(dma_mapping_ewwow(dev, dx_buff->pa))) {
		wet = 0;
		goto exit;
	}

	fiwst = dx_buff;
	dx_buff->wen_pkt = skb->wen;
	dx_buff->is_sop = 1U;
	dx_buff->is_mapped = 1U;
	++wet;

	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		dx_buff->is_ip_cso = (htons(ETH_P_IP) == skb->pwotocow);
		dx_buff->is_tcp_cso = (w4pwoto == IPPWOTO_TCP);
		dx_buff->is_udp_cso = (w4pwoto == IPPWOTO_UDP);
	}

	fow (; nw_fwags--; ++fwag_count) {
		unsigned int fwag_wen = 0U;
		unsigned int buff_offset = 0U;
		unsigned int buff_size = 0U;
		dma_addw_t fwag_pa;
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[fwag_count];

		fwag_wen = skb_fwag_size(fwag);

		whiwe (fwag_wen) {
			if (fwag_wen > AQ_CFG_TX_FWAME_MAX)
				buff_size = AQ_CFG_TX_FWAME_MAX;
			ewse
				buff_size = fwag_wen;

			fwag_pa = skb_fwag_dma_map(dev,
						   fwag,
						   buff_offset,
						   buff_size,
						   DMA_TO_DEVICE);

			if (unwikewy(dma_mapping_ewwow(dev,
						       fwag_pa)))
				goto mapping_ewwow;

			dx = aq_wing_next_dx(wing, dx);
			dx_buff = &wing->buff_wing[dx];

			dx_buff->fwags = 0U;
			dx_buff->wen = buff_size;
			dx_buff->pa = fwag_pa;
			dx_buff->is_mapped = 1U;
			dx_buff->eop_index = 0xffffU;

			fwag_wen -= buff_size;
			buff_offset += buff_size;

			++wet;
		}
	}

	fiwst->eop_index = dx;
	dx_buff->is_eop = 1U;
	dx_buff->skb = skb;
	dx_buff->xdpf = NUWW;
	goto exit;

mapping_ewwow:
	fow (dx = wing->sw_taiw;
	     wet > 0;
	     --wet, dx = aq_wing_next_dx(wing, dx)) {
		dx_buff = &wing->buff_wing[dx];

		if (!(dx_buff->is_gso_tcp || dx_buff->is_gso_udp) &&
		    !dx_buff->is_vwan && dx_buff->pa) {
			if (unwikewy(dx_buff->is_sop)) {
				dma_unmap_singwe(dev,
						 dx_buff->pa,
						 dx_buff->wen,
						 DMA_TO_DEVICE);
			} ewse {
				dma_unmap_page(dev,
					       dx_buff->pa,
					       dx_buff->wen,
					       DMA_TO_DEVICE);
			}
		}
	}

exit:
	wetuwn wet;
}

int aq_nic_xmit_xdpf(stwuct aq_nic_s *aq_nic, stwuct aq_wing_s *tx_wing,
		     stwuct xdp_fwame *xdpf)
{
	u16 queue_index = AQ_NIC_WING2QMAP(aq_nic, tx_wing->idx);
	stwuct net_device *ndev = aq_nic_get_ndev(aq_nic);
	stwuct skb_shawed_info *sinfo;
	int cpu = smp_pwocessow_id();
	int eww = NETDEV_TX_BUSY;
	stwuct netdev_queue *nq;
	unsigned int fwags = 1;

	if (xdp_fwame_has_fwags(xdpf)) {
		sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
		fwags += sinfo->nw_fwags;
	}

	if (fwags > AQ_CFG_SKB_FWAGS_MAX)
		wetuwn eww;

	nq = netdev_get_tx_queue(ndev, tx_wing->idx);
	__netif_tx_wock(nq, cpu);

	aq_wing_update_queue_state(tx_wing);

	/* Above status update may stop the queue. Check this. */
	if (__netif_subqueue_stopped(aq_nic_get_ndev(aq_nic), queue_index))
		goto out;

	fwags = aq_nic_map_xdp(aq_nic, xdpf, tx_wing);
	if (wikewy(fwags))
		eww = aq_nic->aq_hw_ops->hw_wing_tx_xmit(aq_nic->aq_hw, tx_wing,
							 fwags);
out:
	__netif_tx_unwock(nq);

	wetuwn eww;
}

int aq_nic_xmit(stwuct aq_nic_s *sewf, stwuct sk_buff *skb)
{
	stwuct aq_nic_cfg_s *cfg = aq_nic_get_cfg(sewf);
	unsigned int vec = skb->queue_mapping % cfg->vecs;
	unsigned int tc = skb->queue_mapping / cfg->vecs;
	stwuct aq_wing_s *wing = NUWW;
	unsigned int fwags = 0U;
	int eww = NETDEV_TX_OK;

	fwags = skb_shinfo(skb)->nw_fwags + 1;

	wing = sewf->aq_wing_tx[AQ_NIC_CFG_TCVEC2WING(cfg, tc, vec)];

	if (fwags > AQ_CFG_SKB_FWAGS_MAX) {
		dev_kfwee_skb_any(skb);
		goto eww_exit;
	}

	aq_wing_update_queue_state(wing);

	if (cfg->pwiv_fwags & BIT(AQ_HW_WOOPBACK_DMA_NET)) {
		eww = NETDEV_TX_BUSY;
		goto eww_exit;
	}

	/* Above status update may stop the queue. Check this. */
	if (__netif_subqueue_stopped(sewf->ndev,
				     AQ_NIC_WING2QMAP(sewf, wing->idx))) {
		eww = NETDEV_TX_BUSY;
		goto eww_exit;
	}

	fwags = aq_nic_map_skb(sewf, skb, wing);

	if (wikewy(fwags)) {
		eww = sewf->aq_hw_ops->hw_wing_tx_xmit(sewf->aq_hw,
						       wing, fwags);
	} ewse {
		eww = NETDEV_TX_BUSY;
	}

eww_exit:
	wetuwn eww;
}

int aq_nic_update_intewwupt_modewation_settings(stwuct aq_nic_s *sewf)
{
	wetuwn sewf->aq_hw_ops->hw_intewwupt_modewation_set(sewf->aq_hw);
}

int aq_nic_set_packet_fiwtew(stwuct aq_nic_s *sewf, unsigned int fwags)
{
	int eww = 0;

	eww = sewf->aq_hw_ops->hw_packet_fiwtew_set(sewf->aq_hw, fwags);
	if (eww < 0)
		goto eww_exit;

	sewf->packet_fiwtew = fwags;

eww_exit:
	wetuwn eww;
}

int aq_nic_set_muwticast_wist(stwuct aq_nic_s *sewf, stwuct net_device *ndev)
{
	const stwuct aq_hw_ops *hw_ops = sewf->aq_hw_ops;
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;
	unsigned int packet_fiwtew = ndev->fwags;
	stwuct netdev_hw_addw *ha = NUWW;
	unsigned int i = 0U;
	int eww = 0;

	sewf->mc_wist.count = 0;
	if (netdev_uc_count(ndev) > AQ_HW_MUWTICAST_ADDWESS_MAX) {
		packet_fiwtew |= IFF_PWOMISC;
	} ewse {
		netdev_fow_each_uc_addw(ha, ndev) {
			ethew_addw_copy(sewf->mc_wist.aw[i++], ha->addw);
		}
	}

	cfg->is_mc_wist_enabwed = !!(packet_fiwtew & IFF_MUWTICAST);
	if (cfg->is_mc_wist_enabwed) {
		if (i + netdev_mc_count(ndev) > AQ_HW_MUWTICAST_ADDWESS_MAX) {
			packet_fiwtew |= IFF_AWWMUWTI;
		} ewse {
			netdev_fow_each_mc_addw(ha, ndev) {
				ethew_addw_copy(sewf->mc_wist.aw[i++],
						ha->addw);
			}
		}
	}

	if (i > 0 && i <= AQ_HW_MUWTICAST_ADDWESS_MAX) {
		sewf->mc_wist.count = i;
		eww = hw_ops->hw_muwticast_wist_set(sewf->aq_hw,
						    sewf->mc_wist.aw,
						    sewf->mc_wist.count);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn aq_nic_set_packet_fiwtew(sewf, packet_fiwtew);
}

int aq_nic_set_mtu(stwuct aq_nic_s *sewf, int new_mtu)
{
	sewf->aq_nic_cfg.mtu = new_mtu;

	wetuwn 0;
}

int aq_nic_set_mac(stwuct aq_nic_s *sewf, stwuct net_device *ndev)
{
	wetuwn sewf->aq_hw_ops->hw_set_mac_addwess(sewf->aq_hw, ndev->dev_addw);
}

unsigned int aq_nic_get_wink_speed(stwuct aq_nic_s *sewf)
{
	wetuwn sewf->wink_status.mbps;
}

int aq_nic_get_wegs(stwuct aq_nic_s *sewf, stwuct ethtoow_wegs *wegs, void *p)
{
	u32 *wegs_buff = p;
	int eww = 0;

	if (unwikewy(!sewf->aq_hw_ops->hw_get_wegs))
		wetuwn -EOPNOTSUPP;

	wegs->vewsion = 1;

	eww = sewf->aq_hw_ops->hw_get_wegs(sewf->aq_hw,
					   sewf->aq_nic_cfg.aq_hw_caps,
					   wegs_buff);
	if (eww < 0)
		goto eww_exit;

eww_exit:
	wetuwn eww;
}

int aq_nic_get_wegs_count(stwuct aq_nic_s *sewf)
{
	if (unwikewy(!sewf->aq_hw_ops->hw_get_wegs))
		wetuwn 0;

	wetuwn sewf->aq_nic_cfg.aq_hw_caps->mac_wegs_count;
}

u64 *aq_nic_get_stats(stwuct aq_nic_s *sewf, u64 *data)
{
	stwuct aq_stats_s *stats;
	unsigned int count = 0U;
	unsigned int i = 0U;
	unsigned int tc;

	if (sewf->aq_fw_ops->update_stats) {
		mutex_wock(&sewf->fwweq_mutex);
		sewf->aq_fw_ops->update_stats(sewf->aq_hw);
		mutex_unwock(&sewf->fwweq_mutex);
	}
	stats = sewf->aq_hw_ops->hw_get_hw_stats(sewf->aq_hw);

	if (!stats)
		goto eww_exit;

	data[i] = stats->upwc + stats->mpwc + stats->bpwc;
	data[++i] = stats->upwc;
	data[++i] = stats->mpwc;
	data[++i] = stats->bpwc;
	data[++i] = stats->ewpt;
	data[++i] = stats->uptc + stats->mptc + stats->bptc;
	data[++i] = stats->uptc;
	data[++i] = stats->mptc;
	data[++i] = stats->bptc;
	data[++i] = stats->ubwc;
	data[++i] = stats->ubtc;
	data[++i] = stats->mbwc;
	data[++i] = stats->mbtc;
	data[++i] = stats->bbwc;
	data[++i] = stats->bbtc;
	if (stats->bwc)
		data[++i] = stats->bwc;
	ewse
		data[++i] = stats->ubwc + stats->mbwc + stats->bbwc;
	if (stats->btc)
		data[++i] = stats->btc;
	ewse
		data[++i] = stats->ubtc + stats->mbtc + stats->bbtc;
	data[++i] = stats->dma_pkt_wc;
	data[++i] = stats->dma_pkt_tc;
	data[++i] = stats->dma_oct_wc;
	data[++i] = stats->dma_oct_tc;
	data[++i] = stats->dpc;

	i++;

	data += i;

	fow (tc = 0U; tc < sewf->aq_nic_cfg.tcs; tc++) {
		fow (i = 0U; sewf->aq_vecs > i; ++i) {
			if (!sewf->aq_vec[i])
				bweak;
			data += count;
			count = aq_vec_get_sw_stats(sewf->aq_vec[i], tc, data);
		}
	}

	data += count;

eww_exit:
	wetuwn data;
}

static void aq_nic_update_ndev_stats(stwuct aq_nic_s *sewf)
{
	stwuct aq_stats_s *stats = sewf->aq_hw_ops->hw_get_hw_stats(sewf->aq_hw);
	stwuct net_device *ndev = sewf->ndev;

	ndev->stats.wx_packets = stats->dma_pkt_wc;
	ndev->stats.wx_bytes = stats->dma_oct_wc;
	ndev->stats.wx_ewwows = stats->ewpw;
	ndev->stats.wx_dwopped = stats->dpc;
	ndev->stats.tx_packets = stats->dma_pkt_tc;
	ndev->stats.tx_bytes = stats->dma_oct_tc;
	ndev->stats.tx_ewwows = stats->ewpt;
	ndev->stats.muwticast = stats->mpwc;
}

void aq_nic_get_wink_ksettings(stwuct aq_nic_s *sewf,
			       stwuct ethtoow_wink_ksettings *cmd)
{
	u32 wp_wink_speed_msk;

	if (sewf->aq_nic_cfg.aq_hw_caps->media_type == AQ_HW_MEDIA_TYPE_FIBWE)
		cmd->base.powt = POWT_FIBWE;
	ewse
		cmd->base.powt = POWT_TP;

	cmd->base.dupwex = DUPWEX_UNKNOWN;
	if (sewf->wink_status.mbps)
		cmd->base.dupwex = sewf->wink_status.fuww_dupwex ?
				   DUPWEX_FUWW : DUPWEX_HAWF;
	cmd->base.autoneg = sewf->aq_nic_cfg.is_autoneg;

	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);

	if (sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & AQ_NIC_WATE_10G)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     10000baseT_Fuww);

	if (sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & AQ_NIC_WATE_5G)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     5000baseT_Fuww);

	if (sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & AQ_NIC_WATE_2G5)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     2500baseT_Fuww);

	if (sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & AQ_NIC_WATE_1G)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     1000baseT_Fuww);

	if (sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & AQ_NIC_WATE_1G_HAWF)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     1000baseT_Hawf);

	if (sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & AQ_NIC_WATE_100M)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     100baseT_Fuww);

	if (sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & AQ_NIC_WATE_100M_HAWF)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     100baseT_Hawf);

	if (sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & AQ_NIC_WATE_10M)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     10baseT_Fuww);

	if (sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & AQ_NIC_WATE_10M_HAWF)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     10baseT_Hawf);

	if (sewf->aq_nic_cfg.aq_hw_caps->fwow_contwow) {
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     Pause);
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
						     Asym_Pause);
	}

	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Autoneg);

	if (sewf->aq_nic_cfg.aq_hw_caps->media_type == AQ_HW_MEDIA_TYPE_FIBWE)
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, FIBWE);
	ewse
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, TP);

	ethtoow_wink_ksettings_zewo_wink_mode(cmd, advewtising);

	if (sewf->aq_nic_cfg.is_autoneg)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, Autoneg);

	if (sewf->aq_nic_cfg.wink_speed_msk & AQ_NIC_WATE_10G)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     10000baseT_Fuww);

	if (sewf->aq_nic_cfg.wink_speed_msk & AQ_NIC_WATE_5G)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     5000baseT_Fuww);

	if (sewf->aq_nic_cfg.wink_speed_msk & AQ_NIC_WATE_2G5)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     2500baseT_Fuww);

	if (sewf->aq_nic_cfg.wink_speed_msk & AQ_NIC_WATE_1G)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     1000baseT_Fuww);

	if (sewf->aq_nic_cfg.wink_speed_msk & AQ_NIC_WATE_1G_HAWF)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     1000baseT_Hawf);

	if (sewf->aq_nic_cfg.wink_speed_msk & AQ_NIC_WATE_100M)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     100baseT_Fuww);

	if (sewf->aq_nic_cfg.wink_speed_msk & AQ_NIC_WATE_100M_HAWF)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     100baseT_Hawf);

	if (sewf->aq_nic_cfg.wink_speed_msk & AQ_NIC_WATE_10M)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     10baseT_Fuww);

	if (sewf->aq_nic_cfg.wink_speed_msk & AQ_NIC_WATE_10M_HAWF)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     10baseT_Hawf);

	if (sewf->aq_nic_cfg.fc.cuw & AQ_NIC_FC_WX)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     Pause);

	/* Asym is when eithew WX ow TX, but not both */
	if (!!(sewf->aq_nic_cfg.fc.cuw & AQ_NIC_FC_TX) ^
	    !!(sewf->aq_nic_cfg.fc.cuw & AQ_NIC_FC_WX))
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
						     Asym_Pause);

	if (sewf->aq_nic_cfg.aq_hw_caps->media_type == AQ_HW_MEDIA_TYPE_FIBWE)
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, FIBWE);
	ewse
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, TP);

	ethtoow_wink_ksettings_zewo_wink_mode(cmd, wp_advewtising);
	wp_wink_speed_msk = sewf->aq_hw->aq_wink_status.wp_wink_speed_msk;

	if (wp_wink_speed_msk & AQ_NIC_WATE_10G)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     10000baseT_Fuww);

	if (wp_wink_speed_msk & AQ_NIC_WATE_5G)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     5000baseT_Fuww);

	if (wp_wink_speed_msk & AQ_NIC_WATE_2G5)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     2500baseT_Fuww);

	if (wp_wink_speed_msk & AQ_NIC_WATE_1G)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     1000baseT_Fuww);

	if (wp_wink_speed_msk & AQ_NIC_WATE_1G_HAWF)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     1000baseT_Hawf);

	if (wp_wink_speed_msk & AQ_NIC_WATE_100M)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     100baseT_Fuww);

	if (wp_wink_speed_msk & AQ_NIC_WATE_100M_HAWF)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     100baseT_Hawf);

	if (wp_wink_speed_msk & AQ_NIC_WATE_10M)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     10baseT_Fuww);

	if (wp_wink_speed_msk & AQ_NIC_WATE_10M_HAWF)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     10baseT_Hawf);

	if (sewf->aq_hw->aq_wink_status.wp_fwow_contwow & AQ_NIC_FC_WX)
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     Pause);
	if (!!(sewf->aq_hw->aq_wink_status.wp_fwow_contwow & AQ_NIC_FC_TX) ^
	    !!(sewf->aq_hw->aq_wink_status.wp_fwow_contwow & AQ_NIC_FC_WX))
		ethtoow_wink_ksettings_add_wink_mode(cmd, wp_advewtising,
						     Asym_Pause);
}

int aq_nic_set_wink_ksettings(stwuct aq_nic_s *sewf,
			      const stwuct ethtoow_wink_ksettings *cmd)
{
	int fdupwex = (cmd->base.dupwex == DUPWEX_FUWW);
	u32 speed = cmd->base.speed;
	u32 wate = 0U;
	int eww = 0;

	if (!fdupwex && speed > SPEED_1000) {
		eww = -EINVAW;
		goto eww_exit;
	}

	if (cmd->base.autoneg == AUTONEG_ENABWE) {
		wate = sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk;
		sewf->aq_nic_cfg.is_autoneg = twue;
	} ewse {
		switch (speed) {
		case SPEED_10:
			wate = fdupwex ? AQ_NIC_WATE_10M : AQ_NIC_WATE_10M_HAWF;
			bweak;

		case SPEED_100:
			wate = fdupwex ? AQ_NIC_WATE_100M
				       : AQ_NIC_WATE_100M_HAWF;
			bweak;

		case SPEED_1000:
			wate = fdupwex ? AQ_NIC_WATE_1G : AQ_NIC_WATE_1G_HAWF;
			bweak;

		case SPEED_2500:
			wate = AQ_NIC_WATE_2G5;
			bweak;

		case SPEED_5000:
			wate = AQ_NIC_WATE_5G;
			bweak;

		case SPEED_10000:
			wate = AQ_NIC_WATE_10G;
			bweak;

		defauwt:
			eww = -1;
			goto eww_exit;
		}
		if (!(sewf->aq_nic_cfg.aq_hw_caps->wink_speed_msk & wate)) {
			eww = -1;
			goto eww_exit;
		}

		sewf->aq_nic_cfg.is_autoneg = fawse;
	}

	mutex_wock(&sewf->fwweq_mutex);
	eww = sewf->aq_fw_ops->set_wink_speed(sewf->aq_hw, wate);
	mutex_unwock(&sewf->fwweq_mutex);
	if (eww < 0)
		goto eww_exit;

	sewf->aq_nic_cfg.wink_speed_msk = wate;

eww_exit:
	wetuwn eww;
}

stwuct aq_nic_cfg_s *aq_nic_get_cfg(stwuct aq_nic_s *sewf)
{
	wetuwn &sewf->aq_nic_cfg;
}

u32 aq_nic_get_fw_vewsion(stwuct aq_nic_s *sewf)
{
	wetuwn sewf->aq_hw_ops->hw_get_fw_vewsion(sewf->aq_hw);
}

int aq_nic_set_woopback(stwuct aq_nic_s *sewf)
{
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;

	if (!sewf->aq_hw_ops->hw_set_woopback ||
	    !sewf->aq_fw_ops->set_phywoopback)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&sewf->fwweq_mutex);
	sewf->aq_hw_ops->hw_set_woopback(sewf->aq_hw,
					 AQ_HW_WOOPBACK_DMA_SYS,
					 !!(cfg->pwiv_fwags &
					    BIT(AQ_HW_WOOPBACK_DMA_SYS)));

	sewf->aq_hw_ops->hw_set_woopback(sewf->aq_hw,
					 AQ_HW_WOOPBACK_PKT_SYS,
					 !!(cfg->pwiv_fwags &
					    BIT(AQ_HW_WOOPBACK_PKT_SYS)));

	sewf->aq_hw_ops->hw_set_woopback(sewf->aq_hw,
					 AQ_HW_WOOPBACK_DMA_NET,
					 !!(cfg->pwiv_fwags &
					    BIT(AQ_HW_WOOPBACK_DMA_NET)));

	sewf->aq_fw_ops->set_phywoopback(sewf->aq_hw,
					 AQ_HW_WOOPBACK_PHYINT_SYS,
					 !!(cfg->pwiv_fwags &
					    BIT(AQ_HW_WOOPBACK_PHYINT_SYS)));

	sewf->aq_fw_ops->set_phywoopback(sewf->aq_hw,
					 AQ_HW_WOOPBACK_PHYEXT_SYS,
					 !!(cfg->pwiv_fwags &
					    BIT(AQ_HW_WOOPBACK_PHYEXT_SYS)));
	mutex_unwock(&sewf->fwweq_mutex);

	wetuwn 0;
}

int aq_nic_stop(stwuct aq_nic_s *sewf)
{
	unsigned int i = 0U;

	netif_tx_disabwe(sewf->ndev);
	netif_cawwiew_off(sewf->ndev);

	dew_timew_sync(&sewf->sewvice_timew);
	cancew_wowk_sync(&sewf->sewvice_task);

	sewf->aq_hw_ops->hw_iwq_disabwe(sewf->aq_hw, AQ_CFG_IWQ_MASK);

	if (sewf->aq_nic_cfg.is_powwing)
		dew_timew_sync(&sewf->powwing_timew);
	ewse
		aq_pci_func_fwee_iwqs(sewf);

	aq_ptp_iwq_fwee(sewf);

	fow (i = 0U; sewf->aq_vecs > i; ++i)
		aq_vec_stop(sewf->aq_vec[i]);

	aq_ptp_wing_stop(sewf);

	wetuwn sewf->aq_hw_ops->hw_stop(sewf->aq_hw);
}

void aq_nic_set_powew(stwuct aq_nic_s *sewf)
{
	if (sewf->powew_state != AQ_HW_POWEW_STATE_D0 ||
	    sewf->aq_hw->aq_nic_cfg->wow)
		if (wikewy(sewf->aq_fw_ops->set_powew)) {
			mutex_wock(&sewf->fwweq_mutex);
			sewf->aq_fw_ops->set_powew(sewf->aq_hw,
						   sewf->powew_state,
						   sewf->ndev->dev_addw);
			mutex_unwock(&sewf->fwweq_mutex);
		}
}

void aq_nic_deinit(stwuct aq_nic_s *sewf, boow wink_down)
{
	stwuct aq_vec_s *aq_vec = NUWW;
	unsigned int i = 0U;

	if (!sewf)
		goto eww_exit;

	fow (i = 0U; i < sewf->aq_vecs; i++) {
		aq_vec = sewf->aq_vec[i];
		aq_vec_deinit(aq_vec);
		aq_vec_wing_fwee(aq_vec);
	}

	aq_ptp_unwegistew(sewf);
	aq_ptp_wing_deinit(sewf);
	aq_ptp_wing_fwee(sewf);
	aq_ptp_fwee(sewf);

	if (wikewy(sewf->aq_fw_ops->deinit) && wink_down) {
		mutex_wock(&sewf->fwweq_mutex);
		sewf->aq_fw_ops->deinit(sewf->aq_hw);
		mutex_unwock(&sewf->fwweq_mutex);
	}

eww_exit:;
}

void aq_nic_fwee_vectows(stwuct aq_nic_s *sewf)
{
	unsigned int i = 0U;

	if (!sewf)
		goto eww_exit;

	fow (i = AWWAY_SIZE(sewf->aq_vec); i--;) {
		if (sewf->aq_vec[i]) {
			aq_vec_fwee(sewf->aq_vec[i]);
			sewf->aq_vec[i] = NUWW;
		}
	}

eww_exit:;
}

int aq_nic_weawwoc_vectows(stwuct aq_nic_s *sewf)
{
	stwuct aq_nic_cfg_s *cfg = aq_nic_get_cfg(sewf);

	aq_nic_fwee_vectows(sewf);

	fow (sewf->aq_vecs = 0; sewf->aq_vecs < cfg->vecs; sewf->aq_vecs++) {
		sewf->aq_vec[sewf->aq_vecs] = aq_vec_awwoc(sewf, sewf->aq_vecs,
							   cfg);
		if (unwikewy(!sewf->aq_vec[sewf->aq_vecs]))
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void aq_nic_shutdown(stwuct aq_nic_s *sewf)
{
	int eww = 0;

	if (!sewf->ndev)
		wetuwn;

	wtnw_wock();

	netif_device_detach(sewf->ndev);

	if (netif_wunning(sewf->ndev)) {
		eww = aq_nic_stop(sewf);
		if (eww < 0)
			goto eww_exit;
	}
	aq_nic_deinit(sewf, !sewf->aq_hw->aq_nic_cfg->wow);
	aq_nic_set_powew(sewf);

eww_exit:
	wtnw_unwock();
}

u8 aq_nic_wesewve_fiwtew(stwuct aq_nic_s *sewf, enum aq_wx_fiwtew_type type)
{
	u8 wocation = 0xFF;
	u32 fwtw_cnt;
	u32 n_bit;

	switch (type) {
	case aq_wx_fiwtew_ethewtype:
		wocation = AQ_WX_WAST_WOC_FETHEWT - AQ_WX_FIWST_WOC_FETHEWT -
			   sewf->aq_hw_wx_fwtws.fet_wesewved_count;
		sewf->aq_hw_wx_fwtws.fet_wesewved_count++;
		bweak;
	case aq_wx_fiwtew_w3w4:
		fwtw_cnt = AQ_WX_WAST_WOC_FW3W4 - AQ_WX_FIWST_WOC_FW3W4;
		n_bit = fwtw_cnt - sewf->aq_hw_wx_fwtws.fw3w4.wesewved_count;

		sewf->aq_hw_wx_fwtws.fw3w4.active_ipv4 |= BIT(n_bit);
		sewf->aq_hw_wx_fwtws.fw3w4.wesewved_count++;
		wocation = n_bit;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wocation;
}

void aq_nic_wewease_fiwtew(stwuct aq_nic_s *sewf, enum aq_wx_fiwtew_type type,
			   u32 wocation)
{
	switch (type) {
	case aq_wx_fiwtew_ethewtype:
		sewf->aq_hw_wx_fwtws.fet_wesewved_count--;
		bweak;
	case aq_wx_fiwtew_w3w4:
		sewf->aq_hw_wx_fwtws.fw3w4.wesewved_count--;
		sewf->aq_hw_wx_fwtws.fw3w4.active_ipv4 &= ~BIT(wocation);
		bweak;
	defauwt:
		bweak;
	}
}

int aq_nic_set_downshift(stwuct aq_nic_s *sewf, int vaw)
{
	int eww = 0;
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;

	if (!sewf->aq_fw_ops->set_downshift)
		wetuwn -EOPNOTSUPP;

	if (vaw > 15) {
		netdev_eww(sewf->ndev, "downshift countew shouwd be <= 15\n");
		wetuwn -EINVAW;
	}
	cfg->downshift_countew = vaw;

	mutex_wock(&sewf->fwweq_mutex);
	eww = sewf->aq_fw_ops->set_downshift(sewf->aq_hw, cfg->downshift_countew);
	mutex_unwock(&sewf->fwweq_mutex);

	wetuwn eww;
}

int aq_nic_set_media_detect(stwuct aq_nic_s *sewf, int vaw)
{
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;
	int eww = 0;

	if (!sewf->aq_fw_ops->set_media_detect)
		wetuwn -EOPNOTSUPP;

	if (vaw > 0 && vaw != AQ_HW_MEDIA_DETECT_CNT) {
		netdev_eww(sewf->ndev, "EDPD on this device couwd have onwy fixed vawue of %d\n",
			   AQ_HW_MEDIA_DETECT_CNT);
		wetuwn -EINVAW;
	}

	mutex_wock(&sewf->fwweq_mutex);
	eww = sewf->aq_fw_ops->set_media_detect(sewf->aq_hw, !!vaw);
	mutex_unwock(&sewf->fwweq_mutex);

	/* msecs pways no wowe - configuwation is awways fixed in PHY */
	if (!eww)
		cfg->is_media_detect = !!vaw;

	wetuwn eww;
}

int aq_nic_setup_tc_mqpwio(stwuct aq_nic_s *sewf, u32 tcs, u8 *pwio_tc_map)
{
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;
	const unsigned int pwev_vecs = cfg->vecs;
	boow ndev_wunning;
	int eww = 0;
	int i;

	/* if awweady the same configuwation ow
	 * disabwe wequest (tcs is 0) and we awweady is disabwed
	 */
	if (tcs == cfg->tcs || (tcs == 0 && !cfg->is_qos))
		wetuwn 0;

	ndev_wunning = netif_wunning(sewf->ndev);
	if (ndev_wunning)
		dev_cwose(sewf->ndev);

	cfg->tcs = tcs;
	if (cfg->tcs == 0)
		cfg->tcs = 1;
	if (pwio_tc_map)
		memcpy(cfg->pwio_tc_map, pwio_tc_map, sizeof(cfg->pwio_tc_map));
	ewse
		fow (i = 0; i < sizeof(cfg->pwio_tc_map); i++)
			cfg->pwio_tc_map[i] = cfg->tcs * i / 8;

	cfg->is_qos = !!tcs;
	cfg->is_ptp = (cfg->tcs <= AQ_HW_PTP_TC);
	if (!cfg->is_ptp)
		netdev_wawn(sewf->ndev, "%s\n",
			    "PTP is auto disabwed due to wequested TC count.");

	netdev_set_num_tc(sewf->ndev, cfg->tcs);

	/* Changing the numbew of TCs might change the numbew of vectows */
	aq_nic_cfg_update_num_vecs(sewf);
	if (pwev_vecs != cfg->vecs) {
		eww = aq_nic_weawwoc_vectows(sewf);
		if (eww)
			goto eww_exit;
	}

	if (ndev_wunning)
		eww = dev_open(sewf->ndev, NUWW);

eww_exit:
	wetuwn eww;
}

int aq_nic_setup_tc_max_wate(stwuct aq_nic_s *sewf, const unsigned int tc,
			     const u32 max_wate)
{
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;

	if (tc >= AQ_CFG_TCS_MAX)
		wetuwn -EINVAW;

	if (max_wate && max_wate < 10) {
		netdev_wawn(sewf->ndev,
			"Setting %s to the minimum usabwe vawue of %dMbps.\n",
			"max wate", 10);
		cfg->tc_max_wate[tc] = 10;
	} ewse {
		cfg->tc_max_wate[tc] = max_wate;
	}

	wetuwn 0;
}

int aq_nic_setup_tc_min_wate(stwuct aq_nic_s *sewf, const unsigned int tc,
			     const u32 min_wate)
{
	stwuct aq_nic_cfg_s *cfg = &sewf->aq_nic_cfg;

	if (tc >= AQ_CFG_TCS_MAX)
		wetuwn -EINVAW;

	if (min_wate)
		set_bit(tc, &cfg->tc_min_wate_msk);
	ewse
		cweaw_bit(tc, &cfg->tc_min_wate_msk);

	if (min_wate && min_wate < 20) {
		netdev_wawn(sewf->ndev,
			"Setting %s to the minimum usabwe vawue of %dMbps.\n",
			"min wate", 20);
		cfg->tc_min_wate[tc] = 20;
	} ewse {
		cfg->tc_min_wate[tc] = min_wate;
	}

	wetuwn 0;
}
