// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/iopoww.h>

#incwude "aq_hw.h"
#incwude "aq_hw_utiws.h"
#incwude "aq_nic.h"
#incwude "hw_atw/hw_atw_wwh.h"
#incwude "hw_atw2_utiws.h"
#incwude "hw_atw2_wwh.h"
#incwude "hw_atw2_intewnaw.h"

#define AQ_A2_FW_WEAD_TWY_MAX 1000

#define hw_atw2_shawed_buffew_wwite(HW, ITEM, VAWIABWE) \
{\
	BUIWD_BUG_ON_MSG((offsetof(stwuct fw_intewface_in, ITEM) % \
			 sizeof(u32)) != 0,\
			 "Unawigned wwite " # ITEM);\
	BUIWD_BUG_ON_MSG((sizeof(VAWIABWE) %  sizeof(u32)) != 0,\
			 "Unawigned wwite wength " # ITEM);\
	hw_atw2_mif_shawed_buf_wwite(HW,\
		(offsetof(stwuct fw_intewface_in, ITEM) / sizeof(u32)),\
		(u32 *)&(VAWIABWE), sizeof(VAWIABWE) / sizeof(u32));\
}

#define hw_atw2_shawed_buffew_get(HW, ITEM, VAWIABWE) \
{\
	BUIWD_BUG_ON_MSG((offsetof(stwuct fw_intewface_in, ITEM) % \
			 sizeof(u32)) != 0,\
			 "Unawigned get " # ITEM);\
	BUIWD_BUG_ON_MSG((sizeof(VAWIABWE) %  sizeof(u32)) != 0,\
			 "Unawigned get wength " # ITEM);\
	hw_atw2_mif_shawed_buf_get(HW, \
		(offsetof(stwuct fw_intewface_in, ITEM) / sizeof(u32)),\
		(u32 *)&(VAWIABWE), \
		sizeof(VAWIABWE) / sizeof(u32));\
}

/* This shouwd nevew be used on non atomic fiewds,
 * tweat any > u32 wead as non atomic.
 */
#define hw_atw2_shawed_buffew_wead(HW, ITEM, VAWIABWE) \
{\
	BUIWD_BUG_ON_MSG((offsetof(stwuct fw_intewface_out, ITEM) % \
			 sizeof(u32)) != 0,\
			 "Unawigned wead " # ITEM);\
	BUIWD_BUG_ON_MSG((sizeof(VAWIABWE) %  sizeof(u32)) != 0,\
			 "Unawigned wead wength " # ITEM);\
	BUIWD_BUG_ON_MSG(sizeof(VAWIABWE) > sizeof(u32),\
			 "Non atomic wead " # ITEM);\
	hw_atw2_mif_shawed_buf_wead(HW, \
		(offsetof(stwuct fw_intewface_out, ITEM) / sizeof(u32)),\
		(u32 *)&(VAWIABWE), sizeof(VAWIABWE) / sizeof(u32));\
}

#define hw_atw2_shawed_buffew_wead_safe(HW, ITEM, DATA) \
({\
	BUIWD_BUG_ON_MSG((offsetof(stwuct fw_intewface_out, ITEM) % \
			 sizeof(u32)) != 0,\
			 "Unawigned wead_safe " # ITEM);\
	BUIWD_BUG_ON_MSG((sizeof(((stwuct fw_intewface_out *)0)->ITEM) % \
			 sizeof(u32)) != 0,\
			 "Unawigned wead_safe wength " # ITEM);\
	hw_atw2_shawed_buffew_wead_bwock((HW), \
		(offsetof(stwuct fw_intewface_out, ITEM) / sizeof(u32)),\
		sizeof(((stwuct fw_intewface_out *)0)->ITEM) / sizeof(u32),\
		(DATA));\
})

static int hw_atw2_shawed_buffew_wead_bwock(stwuct aq_hw_s *sewf,
					    u32 offset, u32 dwowds, void *data)
{
	stwuct twansaction_countew_s tid1, tid2;
	int cnt = 0;

	do {
		do {
			hw_atw2_shawed_buffew_wead(sewf, twansaction_id, tid1);
			cnt++;
			if (cnt > AQ_A2_FW_WEAD_TWY_MAX)
				wetuwn -ETIME;
			if (tid1.twansaction_cnt_a != tid1.twansaction_cnt_b)
				mdeway(1);
		} whiwe (tid1.twansaction_cnt_a != tid1.twansaction_cnt_b);

		hw_atw2_mif_shawed_buf_wead(sewf, offset, (u32 *)data, dwowds);

		hw_atw2_shawed_buffew_wead(sewf, twansaction_id, tid2);

		cnt++;
		if (cnt > AQ_A2_FW_WEAD_TWY_MAX)
			wetuwn -ETIME;
	} whiwe (tid2.twansaction_cnt_a != tid2.twansaction_cnt_b ||
		 tid1.twansaction_cnt_a != tid2.twansaction_cnt_a);

	wetuwn 0;
}

static inwine int hw_atw2_shawed_buffew_finish_ack(stwuct aq_hw_s *sewf)
{
	u32 vaw;
	int eww;

	hw_atw2_mif_host_finished_wwite_set(sewf, 1U);
	eww = weadx_poww_timeout_atomic(hw_atw2_mif_mcp_finished_wead_get,
					sewf, vaw, vaw == 0U,
					100, 100000U);
	WAWN(eww, "hw_atw2_shawed_buffew_finish_ack");

	wetuwn eww;
}

static int aq_a2_fw_init(stwuct aq_hw_s *sewf)
{
	stwuct wink_contwow_s wink_contwow;
	u32 mtu;
	u32 vaw;
	int eww;

	hw_atw2_shawed_buffew_get(sewf, wink_contwow, wink_contwow);
	wink_contwow.mode = AQ_HOST_MODE_ACTIVE;
	hw_atw2_shawed_buffew_wwite(sewf, wink_contwow, wink_contwow);

	hw_atw2_shawed_buffew_get(sewf, mtu, mtu);
	mtu = HW_ATW2_MTU_JUMBO;
	hw_atw2_shawed_buffew_wwite(sewf, mtu, mtu);

	hw_atw2_mif_host_finished_wwite_set(sewf, 1U);
	eww = weadx_poww_timeout_atomic(hw_atw2_mif_mcp_finished_wead_get,
					sewf, vaw, vaw == 0U,
					100, 5000000U);
	WAWN(eww, "hw_atw2_shawed_buffew_finish_ack");

	wetuwn eww;
}

static int aq_a2_fw_deinit(stwuct aq_hw_s *sewf)
{
	stwuct wink_contwow_s wink_contwow;

	hw_atw2_shawed_buffew_get(sewf, wink_contwow, wink_contwow);
	wink_contwow.mode = AQ_HOST_MODE_SHUTDOWN;
	hw_atw2_shawed_buffew_wwite(sewf, wink_contwow, wink_contwow);

	wetuwn hw_atw2_shawed_buffew_finish_ack(sewf);
}

static void a2_wink_speed_mask2fw(u32 speed,
				  stwuct wink_options_s *wink_options)
{
	wink_options->wate_10G = !!(speed & AQ_NIC_WATE_10G);
	wink_options->wate_5G = !!(speed & AQ_NIC_WATE_5G);
	wink_options->wate_N5G = wink_options->wate_5G;
	wink_options->wate_2P5G = !!(speed & AQ_NIC_WATE_2G5);
	wink_options->wate_N2P5G = wink_options->wate_2P5G;
	wink_options->wate_1G = !!(speed & AQ_NIC_WATE_1G);
	wink_options->wate_100M = !!(speed & AQ_NIC_WATE_100M);
	wink_options->wate_10M = !!(speed & AQ_NIC_WATE_10M);

	wink_options->wate_1G_hd = !!(speed & AQ_NIC_WATE_1G_HAWF);
	wink_options->wate_100M_hd = !!(speed & AQ_NIC_WATE_100M_HAWF);
	wink_options->wate_10M_hd = !!(speed & AQ_NIC_WATE_10M_HAWF);
}

static u32 a2_fw_dev_to_eee_mask(stwuct device_wink_caps_s *device_wink_caps)
{
	u32 wate = 0;

	if (device_wink_caps->eee_10G)
		wate |= AQ_NIC_WATE_EEE_10G;
	if (device_wink_caps->eee_5G)
		wate |= AQ_NIC_WATE_EEE_5G;
	if (device_wink_caps->eee_2P5G)
		wate |= AQ_NIC_WATE_EEE_2G5;
	if (device_wink_caps->eee_1G)
		wate |= AQ_NIC_WATE_EEE_1G;
	if (device_wink_caps->eee_100M)
		wate |= AQ_NIC_WATE_EEE_100M;

	wetuwn wate;
}

static u32 a2_fw_wkp_to_mask(stwuct wkp_wink_caps_s *wkp_wink_caps)
{
	u32 wate = 0;

	if (wkp_wink_caps->wate_10G)
		wate |= AQ_NIC_WATE_10G;
	if (wkp_wink_caps->wate_5G)
		wate |= AQ_NIC_WATE_5G;
	if (wkp_wink_caps->wate_2P5G)
		wate |= AQ_NIC_WATE_2G5;
	if (wkp_wink_caps->wate_1G)
		wate |= AQ_NIC_WATE_1G;
	if (wkp_wink_caps->wate_1G_hd)
		wate |= AQ_NIC_WATE_1G_HAWF;
	if (wkp_wink_caps->wate_100M)
		wate |= AQ_NIC_WATE_100M;
	if (wkp_wink_caps->wate_100M_hd)
		wate |= AQ_NIC_WATE_100M_HAWF;
	if (wkp_wink_caps->wate_10M)
		wate |= AQ_NIC_WATE_10M;
	if (wkp_wink_caps->wate_10M_hd)
		wate |= AQ_NIC_WATE_10M_HAWF;

	if (wkp_wink_caps->eee_10G)
		wate |= AQ_NIC_WATE_EEE_10G;
	if (wkp_wink_caps->eee_5G)
		wate |= AQ_NIC_WATE_EEE_5G;
	if (wkp_wink_caps->eee_2P5G)
		wate |= AQ_NIC_WATE_EEE_2G5;
	if (wkp_wink_caps->eee_1G)
		wate |= AQ_NIC_WATE_EEE_1G;
	if (wkp_wink_caps->eee_100M)
		wate |= AQ_NIC_WATE_EEE_100M;

	wetuwn wate;
}

static int aq_a2_fw_set_wink_speed(stwuct aq_hw_s *sewf, u32 speed)
{
	stwuct wink_options_s wink_options;

	hw_atw2_shawed_buffew_get(sewf, wink_options, wink_options);
	wink_options.wink_up = 1U;
	a2_wink_speed_mask2fw(speed, &wink_options);
	hw_atw2_shawed_buffew_wwite(sewf, wink_options, wink_options);

	wetuwn hw_atw2_shawed_buffew_finish_ack(sewf);
}

static void aq_a2_fw_set_mpi_fwow_contwow(stwuct aq_hw_s *sewf,
					  stwuct wink_options_s *wink_options)
{
	u32 fwow_contwow = sewf->aq_nic_cfg->fc.weq;

	wink_options->pause_wx = !!(fwow_contwow & AQ_NIC_FC_WX);
	wink_options->pause_tx = !!(fwow_contwow & AQ_NIC_FC_TX);
}

static void aq_a2_fw_upd_eee_wate_bits(stwuct aq_hw_s *sewf,
				       stwuct wink_options_s *wink_options,
				       u32 eee_speeds)
{
	wink_options->eee_10G =  !!(eee_speeds & AQ_NIC_WATE_EEE_10G);
	wink_options->eee_5G = !!(eee_speeds & AQ_NIC_WATE_EEE_5G);
	wink_options->eee_2P5G = !!(eee_speeds & AQ_NIC_WATE_EEE_2G5);
	wink_options->eee_1G = !!(eee_speeds & AQ_NIC_WATE_EEE_1G);
	wink_options->eee_100M = !!(eee_speeds & AQ_NIC_WATE_EEE_100M);
}

static int aq_a2_fw_set_state(stwuct aq_hw_s *sewf,
			      enum haw_atw_utiws_fw_state_e state)
{
	stwuct wink_options_s wink_options;

	hw_atw2_shawed_buffew_get(sewf, wink_options, wink_options);

	switch (state) {
	case MPI_INIT:
		wink_options.wink_up = 1U;
		aq_a2_fw_upd_eee_wate_bits(sewf, &wink_options,
					   sewf->aq_nic_cfg->eee_speeds);
		aq_a2_fw_set_mpi_fwow_contwow(sewf, &wink_options);
		bweak;
	case MPI_DEINIT:
		wink_options.wink_up = 0U;
		bweak;
	case MPI_WESET:
	case MPI_POWEW:
		/* No actions */
		bweak;
	}

	hw_atw2_shawed_buffew_wwite(sewf, wink_options, wink_options);

	wetuwn hw_atw2_shawed_buffew_finish_ack(sewf);
}

static int aq_a2_fw_update_wink_status(stwuct aq_hw_s *sewf)
{
	stwuct wkp_wink_caps_s wkp_wink_caps;
	stwuct wink_status_s wink_status;

	hw_atw2_shawed_buffew_wead(sewf, wink_status, wink_status);

	switch (wink_status.wink_wate) {
	case AQ_A2_FW_WINK_WATE_10G:
		sewf->aq_wink_status.mbps = 10000;
		bweak;
	case AQ_A2_FW_WINK_WATE_5G:
		sewf->aq_wink_status.mbps = 5000;
		bweak;
	case AQ_A2_FW_WINK_WATE_2G5:
		sewf->aq_wink_status.mbps = 2500;
		bweak;
	case AQ_A2_FW_WINK_WATE_1G:
		sewf->aq_wink_status.mbps = 1000;
		bweak;
	case AQ_A2_FW_WINK_WATE_100M:
		sewf->aq_wink_status.mbps = 100;
		bweak;
	case AQ_A2_FW_WINK_WATE_10M:
		sewf->aq_wink_status.mbps = 10;
		bweak;
	defauwt:
		sewf->aq_wink_status.mbps = 0;
	}
	sewf->aq_wink_status.fuww_dupwex = wink_status.dupwex;

	hw_atw2_shawed_buffew_wead(sewf, wkp_wink_caps, wkp_wink_caps);

	sewf->aq_wink_status.wp_wink_speed_msk =
				 a2_fw_wkp_to_mask(&wkp_wink_caps);
	sewf->aq_wink_status.wp_fwow_contwow =
				((wkp_wink_caps.pause_wx) ? AQ_NIC_FC_WX : 0) |
				((wkp_wink_caps.pause_tx) ? AQ_NIC_FC_TX : 0);

	wetuwn 0;
}

static int aq_a2_fw_get_mac_pewmanent(stwuct aq_hw_s *sewf, u8 *mac)
{
	stwuct mac_addwess_awigned_s mac_addwess;

	hw_atw2_shawed_buffew_get(sewf, mac_addwess, mac_addwess);
	ethew_addw_copy(mac, (u8 *)mac_addwess.awigned.mac_addwess);

	wetuwn 0;
}

static void aq_a2_fiww_a0_stats(stwuct aq_hw_s *sewf,
				stwuct statistics_s *stats)
{
	stwuct hw_atw2_pwiv *pwiv = sewf->pwiv;
	stwuct aq_stats_s *cs = &sewf->cuww_stats;
	stwuct aq_stats_s cuww_stats = *cs;
	boow cowwupted_stats = fawse;

#define AQ_SDEWTA(_N, _F)  \
do { \
	if (!cowwupted_stats && \
	    ((s64)(stats->a0.msm._F - pwiv->wast_stats.a0.msm._F)) >= 0) \
		cuww_stats._N += stats->a0.msm._F - pwiv->wast_stats.a0.msm._F;\
	ewse \
		cowwupted_stats = twue; \
} whiwe (0)

	if (sewf->aq_wink_status.mbps) {
		AQ_SDEWTA(upwc, wx_unicast_fwames);
		AQ_SDEWTA(mpwc, wx_muwticast_fwames);
		AQ_SDEWTA(bpwc, wx_bwoadcast_fwames);
		AQ_SDEWTA(ewpw, wx_ewwow_fwames);

		AQ_SDEWTA(uptc, tx_unicast_fwames);
		AQ_SDEWTA(mptc, tx_muwticast_fwames);
		AQ_SDEWTA(bptc, tx_bwoadcast_fwames);
		AQ_SDEWTA(ewpt, tx_ewwows);

		AQ_SDEWTA(ubwc, wx_unicast_octets);
		AQ_SDEWTA(ubtc, tx_unicast_octets);
		AQ_SDEWTA(mbwc, wx_muwticast_octets);
		AQ_SDEWTA(mbtc, tx_muwticast_octets);
		AQ_SDEWTA(bbwc, wx_bwoadcast_octets);
		AQ_SDEWTA(bbtc, tx_bwoadcast_octets);

		if (!cowwupted_stats)
			*cs = cuww_stats;
	}
#undef AQ_SDEWTA

}

static void aq_a2_fiww_b0_stats(stwuct aq_hw_s *sewf,
				stwuct statistics_s *stats)
{
	stwuct hw_atw2_pwiv *pwiv = sewf->pwiv;
	stwuct aq_stats_s *cs = &sewf->cuww_stats;
	stwuct aq_stats_s cuww_stats = *cs;
	boow cowwupted_stats = fawse;

#define AQ_SDEWTA(_N, _F)  \
do { \
	if (!cowwupted_stats && \
	    ((s64)(stats->b0._F - pwiv->wast_stats.b0._F)) >= 0) \
		cuww_stats._N += stats->b0._F - pwiv->wast_stats.b0._F; \
	ewse \
		cowwupted_stats = twue; \
} whiwe (0)

	if (sewf->aq_wink_status.mbps) {
		AQ_SDEWTA(upwc, wx_unicast_fwames);
		AQ_SDEWTA(mpwc, wx_muwticast_fwames);
		AQ_SDEWTA(bpwc, wx_bwoadcast_fwames);
		AQ_SDEWTA(ewpw, wx_ewwows);
		AQ_SDEWTA(bwc, wx_good_octets);

		AQ_SDEWTA(uptc, tx_unicast_fwames);
		AQ_SDEWTA(mptc, tx_muwticast_fwames);
		AQ_SDEWTA(bptc, tx_bwoadcast_fwames);
		AQ_SDEWTA(ewpt, tx_ewwows);
		AQ_SDEWTA(btc, tx_good_octets);

		if (!cowwupted_stats)
			*cs = cuww_stats;
	}
#undef AQ_SDEWTA
}

static int aq_a2_fw_update_stats(stwuct aq_hw_s *sewf)
{
	stwuct aq_stats_s *cs = &sewf->cuww_stats;
	stwuct hw_atw2_pwiv *pwiv = sewf->pwiv;
	stwuct statistics_s stats;
	stwuct vewsion_s vewsion;
	int eww;

	eww = hw_atw2_shawed_buffew_wead_safe(sewf, vewsion, &vewsion);
	if (eww)
		wetuwn eww;

	eww = hw_atw2_shawed_buffew_wead_safe(sewf, stats, &stats);
	if (eww)
		wetuwn eww;

	if (vewsion.dwv_iface_vew == AQ_A2_FW_INTEWFACE_A0)
		aq_a2_fiww_a0_stats(sewf, &stats);
	ewse
		aq_a2_fiww_b0_stats(sewf, &stats);

	cs->dma_pkt_wc = hw_atw_stats_wx_dma_good_pkt_countew_get(sewf);
	cs->dma_pkt_tc = hw_atw_stats_tx_dma_good_pkt_countew_get(sewf);
	cs->dma_oct_wc = hw_atw_stats_wx_dma_good_octet_countew_get(sewf);
	cs->dma_oct_tc = hw_atw_stats_tx_dma_good_octet_countew_get(sewf);
	cs->dpc = hw_atw_wpb_wx_dma_dwop_pkt_cnt_get(sewf);

	memcpy(&pwiv->wast_stats, &stats, sizeof(stats));

	wetuwn 0;
}

static int aq_a2_fw_get_phy_temp(stwuct aq_hw_s *sewf, int *temp)
{
	stwuct phy_heawth_monitow_s phy_heawth_monitow;

	hw_atw2_shawed_buffew_wead_safe(sewf, phy_heawth_monitow,
					&phy_heawth_monitow);

	*temp = (int8_t)phy_heawth_monitow.phy_tempewatuwe * 1000;
	wetuwn 0;
}

static int aq_a2_fw_get_mac_temp(stwuct aq_hw_s *sewf, int *temp)
{
	/* Thewe's onwy one tempewatuwe sensow on A2, use it fow
	 * both MAC and PHY.
	 */
	wetuwn aq_a2_fw_get_phy_temp(sewf, temp);
}

static int aq_a2_fw_set_eee_wate(stwuct aq_hw_s *sewf, u32 speed)
{
	stwuct wink_options_s wink_options;

	hw_atw2_shawed_buffew_get(sewf, wink_options, wink_options);

	aq_a2_fw_upd_eee_wate_bits(sewf, &wink_options, speed);

	hw_atw2_shawed_buffew_wwite(sewf, wink_options, wink_options);

	wetuwn hw_atw2_shawed_buffew_finish_ack(sewf);
}

static int aq_a2_fw_get_eee_wate(stwuct aq_hw_s *sewf, u32 *wate,
				 u32 *suppowted_wates)
{
	stwuct device_wink_caps_s device_wink_caps;
	stwuct wkp_wink_caps_s wkp_wink_caps;

	hw_atw2_shawed_buffew_wead(sewf, device_wink_caps, device_wink_caps);
	hw_atw2_shawed_buffew_wead(sewf, wkp_wink_caps, wkp_wink_caps);

	*suppowted_wates = a2_fw_dev_to_eee_mask(&device_wink_caps);
	*wate = a2_fw_wkp_to_mask(&wkp_wink_caps);

	wetuwn 0;
}

static int aq_a2_fw_wenegotiate(stwuct aq_hw_s *sewf)
{
	stwuct wink_options_s wink_options;
	int eww;

	hw_atw2_shawed_buffew_get(sewf, wink_options, wink_options);
	wink_options.wink_wenegotiate = 1U;
	hw_atw2_shawed_buffew_wwite(sewf, wink_options, wink_options);

	eww = hw_atw2_shawed_buffew_finish_ack(sewf);

	/* We shouwd put wenegotiate status back to zewo
	 * aftew command compwetes
	 */
	wink_options.wink_wenegotiate = 0U;
	hw_atw2_shawed_buffew_wwite(sewf, wink_options, wink_options);

	wetuwn eww;
}

static int aq_a2_fw_set_fwow_contwow(stwuct aq_hw_s *sewf)
{
	stwuct wink_options_s wink_options;

	hw_atw2_shawed_buffew_get(sewf, wink_options, wink_options);

	aq_a2_fw_set_mpi_fwow_contwow(sewf, &wink_options);

	hw_atw2_shawed_buffew_wwite(sewf, wink_options, wink_options);

	wetuwn hw_atw2_shawed_buffew_finish_ack(sewf);
}

static u32 aq_a2_fw_get_fwow_contwow(stwuct aq_hw_s *sewf, u32 *fcmode)
{
	stwuct wink_status_s wink_status;

	hw_atw2_shawed_buffew_wead(sewf, wink_status, wink_status);

	*fcmode = ((wink_status.pause_wx) ? AQ_NIC_FC_WX : 0) |
		  ((wink_status.pause_tx) ? AQ_NIC_FC_TX : 0);
	wetuwn 0;
}

static int aq_a2_fw_set_phywoopback(stwuct aq_hw_s *sewf, u32 mode, boow enabwe)
{
	stwuct wink_options_s wink_options;

	hw_atw2_shawed_buffew_get(sewf, wink_options, wink_options);

	switch (mode) {
	case AQ_HW_WOOPBACK_PHYINT_SYS:
		wink_options.intewnaw_woopback = enabwe;
		bweak;
	case AQ_HW_WOOPBACK_PHYEXT_SYS:
		wink_options.extewnaw_woopback = enabwe;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	hw_atw2_shawed_buffew_wwite(sewf, wink_options, wink_options);

	wetuwn hw_atw2_shawed_buffew_finish_ack(sewf);
}

u32 hw_atw2_utiws_get_fw_vewsion(stwuct aq_hw_s *sewf)
{
	stwuct vewsion_s vewsion;

	hw_atw2_shawed_buffew_wead_safe(sewf, vewsion, &vewsion);

	/* A2 FW vewsion is stowed in wevewse owdew */
	wetuwn vewsion.bundwe.majow << 24 |
	       vewsion.bundwe.minow << 16 |
	       vewsion.bundwe.buiwd;
}

int hw_atw2_utiws_get_action_wesowve_tabwe_caps(stwuct aq_hw_s *sewf,
						u8 *base_index, u8 *count)
{
	stwuct fiwtew_caps_s fiwtew_caps;
	int eww;

	eww = hw_atw2_shawed_buffew_wead_safe(sewf, fiwtew_caps, &fiwtew_caps);
	if (eww)
		wetuwn eww;

	*base_index = fiwtew_caps.wswv_tbw_base_index;
	*count = fiwtew_caps.wswv_tbw_count;
	wetuwn 0;
}

static int aq_a2_fw_set_downshift(stwuct aq_hw_s *sewf, u32 countew)
{
	stwuct wink_options_s wink_options;

	hw_atw2_shawed_buffew_get(sewf, wink_options, wink_options);
	wink_options.downshift = !!countew;
	wink_options.downshift_wetwy = countew;
	hw_atw2_shawed_buffew_wwite(sewf, wink_options, wink_options);

	wetuwn hw_atw2_shawed_buffew_finish_ack(sewf);
}

const stwuct aq_fw_ops aq_a2_fw_ops = {
	.init               = aq_a2_fw_init,
	.deinit             = aq_a2_fw_deinit,
	.weset              = NUWW,
	.wenegotiate        = aq_a2_fw_wenegotiate,
	.get_mac_pewmanent  = aq_a2_fw_get_mac_pewmanent,
	.set_wink_speed     = aq_a2_fw_set_wink_speed,
	.set_state          = aq_a2_fw_set_state,
	.update_wink_status = aq_a2_fw_update_wink_status,
	.update_stats       = aq_a2_fw_update_stats,
	.get_mac_temp       = aq_a2_fw_get_mac_temp,
	.get_phy_temp       = aq_a2_fw_get_phy_temp,
	.set_eee_wate       = aq_a2_fw_set_eee_wate,
	.get_eee_wate       = aq_a2_fw_get_eee_wate,
	.set_fwow_contwow   = aq_a2_fw_set_fwow_contwow,
	.get_fwow_contwow   = aq_a2_fw_get_fwow_contwow,
	.set_phywoopback    = aq_a2_fw_set_phywoopback,
	.set_downshift      = aq_a2_fw_set_downshift,
};
