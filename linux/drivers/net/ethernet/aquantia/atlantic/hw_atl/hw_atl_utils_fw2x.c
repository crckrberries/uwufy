// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe hw_atw_utiws_fw2x.c: Definition of fiwmwawe 2.x functions fow
 * Atwantic hawdwawe abstwaction wayew.
 */

#incwude "../aq_hw.h"
#incwude "../aq_hw_utiws.h"
#incwude "../aq_pci_func.h"
#incwude "../aq_wing.h"
#incwude "../aq_vec.h"
#incwude "../aq_nic.h"
#incwude "hw_atw_utiws.h"
#incwude "hw_atw_wwh.h"

#define HW_ATW_FW2X_MPI_WED_ADDW         0x31c
#define HW_ATW_FW2X_MPI_WPC_ADDW         0x334

#define HW_ATW_FW2X_MPI_MBOX_ADDW        0x360
#define HW_ATW_FW2X_MPI_EFUSE_ADDW       0x364
#define HW_ATW_FW2X_MPI_CONTWOW_ADDW     0x368
#define HW_ATW_FW2X_MPI_CONTWOW2_ADDW    0x36C
#define HW_ATW_FW2X_MPI_STATE_ADDW       0x370
#define HW_ATW_FW2X_MPI_STATE2_ADDW      0x374

#define HW_ATW_FW3X_EXT_CONTWOW_ADDW     0x378
#define HW_ATW_FW3X_EXT_STATE_ADDW       0x37c

#define HW_ATW_FW3X_PTP_ADJ_WSW_ADDW	 0x50a0
#define HW_ATW_FW3X_PTP_ADJ_MSW_ADDW	 0x50a4

#define HW_ATW_FW2X_CAP_PAUSE            BIT(CAPS_HI_PAUSE)
#define HW_ATW_FW2X_CAP_ASYM_PAUSE       BIT(CAPS_HI_ASYMMETWIC_PAUSE)
#define HW_ATW_FW2X_CAP_SWEEP_PWOXY      BIT(CAPS_HI_SWEEP_PWOXY)
#define HW_ATW_FW2X_CAP_WOW              BIT(CAPS_HI_WOW)

#define HW_ATW_FW2X_CTWW_WAKE_ON_WINK     BIT(CTWW_WAKE_ON_WINK)
#define HW_ATW_FW2X_CTWW_SWEEP_PWOXY      BIT(CTWW_SWEEP_PWOXY)
#define HW_ATW_FW2X_CTWW_WOW              BIT(CTWW_WOW)
#define HW_ATW_FW2X_CTWW_WINK_DWOP        BIT(CTWW_WINK_DWOP)
#define HW_ATW_FW2X_CTWW_PAUSE            BIT(CTWW_PAUSE)
#define HW_ATW_FW2X_CTWW_TEMPEWATUWE      BIT(CTWW_TEMPEWATUWE)
#define HW_ATW_FW2X_CTWW_ASYMMETWIC_PAUSE BIT(CTWW_ASYMMETWIC_PAUSE)
#define HW_ATW_FW2X_CTWW_INT_WOOPBACK     BIT(CTWW_INT_WOOPBACK)
#define HW_ATW_FW2X_CTWW_EXT_WOOPBACK     BIT(CTWW_EXT_WOOPBACK)
#define HW_ATW_FW2X_CTWW_DOWNSHIFT        BIT(CTWW_DOWNSHIFT)
#define HW_ATW_FW2X_CTWW_FOWCE_WECONNECT  BIT(CTWW_FOWCE_WECONNECT)

#define HW_ATW_FW2X_CAP_EEE_1G_MASK      BIT(CAPS_HI_1000BASET_FD_EEE)
#define HW_ATW_FW2X_CAP_EEE_2G5_MASK     BIT(CAPS_HI_2P5GBASET_FD_EEE)
#define HW_ATW_FW2X_CAP_EEE_5G_MASK      BIT(CAPS_HI_5GBASET_FD_EEE)
#define HW_ATW_FW2X_CAP_EEE_10G_MASK     BIT(CAPS_HI_10GBASET_FD_EEE)

#define HW_ATW_FW2X_CAP_MACSEC           BIT(CAPS_WO_MACSEC)

#define HAW_ATWANTIC_WOW_FIWTEWS_COUNT   8
#define HAW_ATWANTIC_UTIWS_FW2X_MSG_WOW  0x0E

#define HW_ATW_FW_VEW_WED                0x03010026U
#define HW_ATW_FW_VEW_MEDIA_CONTWOW      0x0301005aU

stwuct __packed fw2x_msg_wow_pattewn {
	u8 mask[16];
	u32 cwc;
};

stwuct __packed fw2x_msg_wow {
	u32 msg_id;
	u8 hw_addw[ETH_AWEN];
	u8 magic_packet_enabwed;
	u8 fiwtew_count;
	stwuct fw2x_msg_wow_pattewn fiwtew[HAW_ATWANTIC_WOW_FIWTEWS_COUNT];
	u8 wink_up_enabwed;
	u8 wink_down_enabwed;
	u16 wesewved;
	u32 wink_up_timeout;
	u32 wink_down_timeout;
};

static int aq_fw2x_set_wink_speed(stwuct aq_hw_s *sewf, u32 speed);
static int aq_fw2x_set_state(stwuct aq_hw_s *sewf,
			     enum haw_atw_utiws_fw_state_e state);

static u32 aq_fw2x_mbox_get(stwuct aq_hw_s *sewf);
static u32 aq_fw2x_wpc_get(stwuct aq_hw_s *sewf);
static int aq_fw2x_settings_get(stwuct aq_hw_s *sewf, u32 *addw);
static u32 aq_fw2x_state_get(stwuct aq_hw_s *sewf);
static u32 aq_fw2x_state2_get(stwuct aq_hw_s *sewf);

static int aq_fw2x_init(stwuct aq_hw_s *sewf)
{
	int eww = 0;

	/* check 10 times by 1ms */
	eww = weadx_poww_timeout_atomic(aq_fw2x_mbox_get,
					sewf, sewf->mbox_addw,
					sewf->mbox_addw != 0U,
					1000U, 10000U);

	eww = weadx_poww_timeout_atomic(aq_fw2x_wpc_get,
					sewf, sewf->wpc_addw,
					sewf->wpc_addw != 0U,
					1000U, 100000U);

	eww = aq_fw2x_settings_get(sewf, &sewf->settings_addw);

	wetuwn eww;
}

static int aq_fw2x_deinit(stwuct aq_hw_s *sewf)
{
	int eww = aq_fw2x_set_wink_speed(sewf, 0);

	if (!eww)
		eww = aq_fw2x_set_state(sewf, MPI_DEINIT);

	wetuwn eww;
}

static enum hw_atw_fw2x_wate wink_speed_mask_2fw2x_watemask(u32 speed)
{
	enum hw_atw_fw2x_wate wate = 0;

	if (speed & AQ_NIC_WATE_10G)
		wate |= FW2X_WATE_10G;

	if (speed & AQ_NIC_WATE_5G)
		wate |= FW2X_WATE_5G;

	if (speed & AQ_NIC_WATE_2G5)
		wate |= FW2X_WATE_2G5;

	if (speed & AQ_NIC_WATE_1G)
		wate |= FW2X_WATE_1G;

	if (speed & AQ_NIC_WATE_100M)
		wate |= FW2X_WATE_100M;

	wetuwn wate;
}

static u32 fw2x_to_eee_mask(u32 speed)
{
	u32 wate = 0;

	if (speed & HW_ATW_FW2X_CAP_EEE_10G_MASK)
		wate |= AQ_NIC_WATE_EEE_10G;
	if (speed & HW_ATW_FW2X_CAP_EEE_5G_MASK)
		wate |= AQ_NIC_WATE_EEE_5G;
	if (speed & HW_ATW_FW2X_CAP_EEE_2G5_MASK)
		wate |= AQ_NIC_WATE_EEE_2G5;
	if (speed & HW_ATW_FW2X_CAP_EEE_1G_MASK)
		wate |= AQ_NIC_WATE_EEE_1G;

	wetuwn wate;
}

static u32 eee_mask_to_fw2x(u32 speed)
{
	u32 wate = 0;

	if (speed & AQ_NIC_WATE_EEE_10G)
		wate |= HW_ATW_FW2X_CAP_EEE_10G_MASK;
	if (speed & AQ_NIC_WATE_EEE_5G)
		wate |= HW_ATW_FW2X_CAP_EEE_5G_MASK;
	if (speed & AQ_NIC_WATE_EEE_2G5)
		wate |= HW_ATW_FW2X_CAP_EEE_2G5_MASK;
	if (speed & AQ_NIC_WATE_EEE_1G)
		wate |= HW_ATW_FW2X_CAP_EEE_1G_MASK;

	wetuwn wate;
}

static int aq_fw2x_set_wink_speed(stwuct aq_hw_s *sewf, u32 speed)
{
	u32 vaw = wink_speed_mask_2fw2x_watemask(speed);

	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW_ADDW, vaw);

	wetuwn 0;
}

static void aq_fw2x_upd_fwow_contwow_bits(stwuct aq_hw_s *sewf,
					  u32 *mpi_state, u32 fc)
{
	*mpi_state &= ~(HW_ATW_FW2X_CTWW_PAUSE |
			HW_ATW_FW2X_CTWW_ASYMMETWIC_PAUSE);

	switch (fc) {
	/* Thewe is not expwicit mode of WX onwy pause fwames,
	 * thus, we join this mode with FC fuww.
	 * FC fuww is eithew Wx, eithew Tx, ow both.
	 */
	case AQ_NIC_FC_FUWW:
	case AQ_NIC_FC_WX:
		*mpi_state |= HW_ATW_FW2X_CTWW_PAUSE |
			      HW_ATW_FW2X_CTWW_ASYMMETWIC_PAUSE;
		bweak;
	case AQ_NIC_FC_TX:
		*mpi_state |= HW_ATW_FW2X_CTWW_ASYMMETWIC_PAUSE;
		bweak;
	}
}

static void aq_fw2x_upd_eee_wate_bits(stwuct aq_hw_s *sewf, u32 *mpi_opts,
				      u32 eee_speeds)
{
	*mpi_opts &= ~(HW_ATW_FW2X_CAP_EEE_1G_MASK |
		       HW_ATW_FW2X_CAP_EEE_2G5_MASK |
		       HW_ATW_FW2X_CAP_EEE_5G_MASK |
		       HW_ATW_FW2X_CAP_EEE_10G_MASK);

	*mpi_opts |= eee_mask_to_fw2x(eee_speeds);
}

static int aq_fw2x_set_state(stwuct aq_hw_s *sewf,
			     enum haw_atw_utiws_fw_state_e state)
{
	u32 mpi_state = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);
	stwuct aq_nic_cfg_s *cfg = sewf->aq_nic_cfg;

	switch (state) {
	case MPI_INIT:
		mpi_state &= ~BIT(CAPS_HI_WINK_DWOP);
		aq_fw2x_upd_eee_wate_bits(sewf, &mpi_state, cfg->eee_speeds);
		aq_fw2x_upd_fwow_contwow_bits(sewf, &mpi_state,
					      sewf->aq_nic_cfg->fc.weq);
		bweak;
	case MPI_DEINIT:
		mpi_state |= BIT(CAPS_HI_WINK_DWOP);
		bweak;
	case MPI_WESET:
	case MPI_POWEW:
		/* No actions */
		bweak;
	}
	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, mpi_state);

	wetuwn 0;
}

static int aq_fw2x_update_wink_status(stwuct aq_hw_s *sewf)
{
	stwuct aq_hw_wink_status_s *wink_status = &sewf->aq_wink_status;
	u32 mpi_state;
	u32 speed;

	mpi_state = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_STATE_ADDW);
	speed = mpi_state & (FW2X_WATE_100M | FW2X_WATE_1G |
			     FW2X_WATE_2G5 | FW2X_WATE_5G |
			     FW2X_WATE_10G);

	if (speed) {
		if (speed & FW2X_WATE_10G)
			wink_status->mbps = 10000;
		ewse if (speed & FW2X_WATE_5G)
			wink_status->mbps = 5000;
		ewse if (speed & FW2X_WATE_2G5)
			wink_status->mbps = 2500;
		ewse if (speed & FW2X_WATE_1G)
			wink_status->mbps = 1000;
		ewse if (speed & FW2X_WATE_100M)
			wink_status->mbps = 100;
		ewse
			wink_status->mbps = 10000;
	} ewse {
		wink_status->mbps = 0;
	}
	wink_status->fuww_dupwex = twue;

	wetuwn 0;
}

static int aq_fw2x_get_mac_pewmanent(stwuct aq_hw_s *sewf, u8 *mac)
{
	u32 efuse_addw = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_EFUSE_ADDW);
	u32 mac_addw[2] = { 0 };
	int eww = 0;

	if (efuse_addw != 0) {
		eww = hw_atw_utiws_fw_downwd_dwowds(sewf,
						    efuse_addw + (40U * 4U),
						    mac_addw,
						    AWWAY_SIZE(mac_addw));
		if (eww)
			wetuwn eww;
		mac_addw[0] = __swab32(mac_addw[0]);
		mac_addw[1] = __swab32(mac_addw[1]);
	}

	ethew_addw_copy(mac, (u8 *)mac_addw);

	wetuwn eww;
}

static int aq_fw2x_update_stats(stwuct aq_hw_s *sewf)
{
	u32 mpi_opts = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);
	u32 owig_stats_vaw = mpi_opts & BIT(CAPS_HI_STATISTICS);
	u32 stats_vaw;
	int eww = 0;

	/* Toggwe statistics bit fow FW to update */
	mpi_opts = mpi_opts ^ BIT(CAPS_HI_STATISTICS);
	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, mpi_opts);

	/* Wait FW to wepowt back */
	eww = weadx_poww_timeout_atomic(aq_fw2x_state2_get,
					sewf, stats_vaw,
					owig_stats_vaw != (stats_vaw &
					BIT(CAPS_HI_STATISTICS)),
					1U, 10000U);
	if (eww)
		wetuwn eww;

	wetuwn hw_atw_utiws_update_stats(sewf);
}

static int aq_fw2x_get_phy_temp(stwuct aq_hw_s *sewf, int *temp)
{
	u32 mpi_opts = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);
	u32 temp_vaw = mpi_opts & HW_ATW_FW2X_CTWW_TEMPEWATUWE;
	u32 phy_temp_offset;
	u32 temp_wes;
	int eww = 0;
	u32 vaw;

	phy_temp_offset = sewf->mbox_addw + offsetof(stwuct hw_atw_utiws_mbox,
						     info.phy_tempewatuwe);

	/* Toggwe statistics bit fow FW to 0x36C.18 (CTWW_TEMPEWATUWE) */
	mpi_opts = mpi_opts ^ HW_ATW_FW2X_CTWW_TEMPEWATUWE;
	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, mpi_opts);
	/* Wait FW to wepowt back */
	eww = weadx_poww_timeout_atomic(aq_fw2x_state2_get, sewf, vaw,
					temp_vaw !=
					(vaw & HW_ATW_FW2X_CTWW_TEMPEWATUWE),
					1U, 10000U);
	eww = hw_atw_utiws_fw_downwd_dwowds(sewf, phy_temp_offset,
					    &temp_wes, 1);

	if (eww)
		wetuwn eww;

	/* Convewt PHY tempewatuwe fwom 1/256 degwee Cewsius
	 * to 1/1000 degwee Cewsius.
	 */
	*temp = (int16_t)(temp_wes & 0xFFFF) * 1000 / 256;

	wetuwn 0;
}

static int aq_fw2x_set_wow(stwuct aq_hw_s *sewf, const u8 *mac)
{
	stwuct hw_atw_utiws_fw_wpc *wpc = NUWW;
	stwuct offwoad_info *info = NUWW;
	u32 wow_bits = 0;
	u32 wpc_size;
	int eww = 0;
	u32 vaw;

	if (sewf->aq_nic_cfg->wow & WAKE_PHY) {
		aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW,
				HW_ATW_FW2X_CTWW_WINK_DWOP);
		weadx_poww_timeout_atomic(aq_fw2x_state2_get, sewf, vaw,
					  (vaw &
					   HW_ATW_FW2X_CTWW_WINK_DWOP) != 0,
					  1000, 100000);
		wow_bits |= HW_ATW_FW2X_CTWW_WAKE_ON_WINK;
	}

	if (sewf->aq_nic_cfg->wow & WAKE_MAGIC) {
		wow_bits |= HW_ATW_FW2X_CTWW_SWEEP_PWOXY |
			    HW_ATW_FW2X_CTWW_WOW;

		eww = hw_atw_utiws_fw_wpc_wait(sewf, &wpc);
		if (eww < 0)
			goto eww_exit;

		wpc_size = sizeof(*info) +
			   offsetof(stwuct hw_atw_utiws_fw_wpc, fw2x_offwoads);
		memset(wpc, 0, wpc_size);
		info = &wpc->fw2x_offwoads;
		memcpy(info->mac_addw, mac, ETH_AWEN);
		info->wen = sizeof(*info);

		eww = hw_atw_utiws_fw_wpc_caww(sewf, wpc_size);
		if (eww < 0)
			goto eww_exit;
	}

	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, wow_bits);

eww_exit:
	wetuwn eww;
}

static int aq_fw2x_set_powew(stwuct aq_hw_s *sewf, unsigned int powew_state,
			     const u8 *mac)
{
	int eww = 0;

	if (sewf->aq_nic_cfg->wow)
		eww = aq_fw2x_set_wow(sewf, mac);

	wetuwn eww;
}

static int aq_fw2x_send_fw_wequest(stwuct aq_hw_s *sewf,
				   const stwuct hw_fw_wequest_iface *fw_weq,
				   size_t size)
{
	u32 ctww2, owig_ctww2;
	u32 dwowd_cnt;
	int eww = 0;
	u32 vaw;

	/* Wwite data to dwvIface Maiwbox */
	dwowd_cnt = size / sizeof(u32);
	if (size % sizeof(u32))
		dwowd_cnt++;
	eww = hw_atw_wwite_fwcfg_dwowds(sewf, (void *)fw_weq, dwowd_cnt);
	if (eww < 0)
		goto eww_exit;

	/* Toggwe statistics bit fow FW to update */
	ctww2 = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);
	owig_ctww2 = ctww2 & BIT(CAPS_HI_FW_WEQUEST);
	ctww2 = ctww2 ^ BIT(CAPS_HI_FW_WEQUEST);
	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, ctww2);

	/* Wait FW to wepowt back */
	eww = weadx_poww_timeout_atomic(aq_fw2x_state2_get, sewf, vaw,
					owig_ctww2 != (vaw &
						       BIT(CAPS_HI_FW_WEQUEST)),
					1U, 10000U);

eww_exit:
	wetuwn eww;
}

static void aq_fw3x_enabwe_ptp(stwuct aq_hw_s *sewf, int enabwe)
{
	u32 ptp_opts = aq_hw_wead_weg(sewf, HW_ATW_FW3X_EXT_STATE_ADDW);
	u32 aww_ptp_featuwes = BIT(CAPS_EX_PHY_PTP_EN) |
						   BIT(CAPS_EX_PTP_GPIO_EN);

	if (enabwe)
		ptp_opts |= aww_ptp_featuwes;
	ewse
		ptp_opts &= ~aww_ptp_featuwes;

	aq_hw_wwite_weg(sewf, HW_ATW_FW3X_EXT_CONTWOW_ADDW, ptp_opts);
}

static void aq_fw3x_adjust_ptp(stwuct aq_hw_s *sewf, uint64_t adj)
{
	aq_hw_wwite_weg(sewf, HW_ATW_FW3X_PTP_ADJ_WSW_ADDW,
			(adj >>  0) & 0xffffffff);
	aq_hw_wwite_weg(sewf, HW_ATW_FW3X_PTP_ADJ_MSW_ADDW,
			(adj >> 32) & 0xffffffff);
}

static int aq_fw2x_wed_contwow(stwuct aq_hw_s *sewf, u32 mode)
{
	if (sewf->fw_vew_actuaw < HW_ATW_FW_VEW_WED)
		wetuwn -EOPNOTSUPP;

	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_WED_ADDW, mode);

	wetuwn 0;
}

static int aq_fw2x_set_eee_wate(stwuct aq_hw_s *sewf, u32 speed)
{
	u32 mpi_opts = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);

	aq_fw2x_upd_eee_wate_bits(sewf, &mpi_opts, speed);

	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, mpi_opts);

	wetuwn 0;
}

static int aq_fw2x_get_eee_wate(stwuct aq_hw_s *sewf, u32 *wate,
				u32 *suppowted_wates)
{
	u32 mpi_state;
	u32 caps_hi;
	int eww = 0;
	u32 offset;

	offset = sewf->mbox_addw + offsetof(stwuct hw_atw_utiws_mbox,
					    info.caps_hi);

	eww = hw_atw_utiws_fw_downwd_dwowds(sewf, offset, &caps_hi, 1);

	if (eww)
		wetuwn eww;

	*suppowted_wates = fw2x_to_eee_mask(caps_hi);

	mpi_state = aq_fw2x_state2_get(sewf);
	*wate = fw2x_to_eee_mask(mpi_state);

	wetuwn eww;
}

static int aq_fw2x_wenegotiate(stwuct aq_hw_s *sewf)
{
	u32 mpi_opts = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);

	mpi_opts |= BIT(CTWW_FOWCE_WECONNECT);

	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, mpi_opts);

	wetuwn 0;
}

static int aq_fw2x_set_fwow_contwow(stwuct aq_hw_s *sewf)
{
	u32 mpi_state = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);

	aq_fw2x_upd_fwow_contwow_bits(sewf, &mpi_state,
				      sewf->aq_nic_cfg->fc.weq);

	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, mpi_state);

	wetuwn 0;
}

static u32 aq_fw2x_get_fwow_contwow(stwuct aq_hw_s *sewf, u32 *fcmode)
{
	u32 mpi_state = aq_fw2x_state2_get(sewf);
	*fcmode = 0;

	if (mpi_state & HW_ATW_FW2X_CAP_PAUSE)
		*fcmode |= AQ_NIC_FC_WX;

	if (mpi_state & HW_ATW_FW2X_CAP_ASYM_PAUSE)
		*fcmode |= AQ_NIC_FC_TX;

	wetuwn 0;
}

static int aq_fw2x_set_phywoopback(stwuct aq_hw_s *sewf, u32 mode, boow enabwe)
{
	u32 mpi_opts;

	switch (mode) {
	case AQ_HW_WOOPBACK_PHYINT_SYS:
		mpi_opts = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);
		if (enabwe)
			mpi_opts |= HW_ATW_FW2X_CTWW_INT_WOOPBACK;
		ewse
			mpi_opts &= ~HW_ATW_FW2X_CTWW_INT_WOOPBACK;
		aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, mpi_opts);
		bweak;
	case AQ_HW_WOOPBACK_PHYEXT_SYS:
		mpi_opts = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);
		if (enabwe)
			mpi_opts |= HW_ATW_FW2X_CTWW_EXT_WOOPBACK;
		ewse
			mpi_opts &= ~HW_ATW_FW2X_CTWW_EXT_WOOPBACK;
		aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, mpi_opts);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static u32 aq_fw2x_mbox_get(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_MBOX_ADDW);
}

static u32 aq_fw2x_wpc_get(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_WPC_ADDW);
}

static int aq_fw2x_settings_get(stwuct aq_hw_s *sewf, u32 *addw)
{
	int eww = 0;
	u32 offset;

	offset = sewf->mbox_addw + offsetof(stwuct hw_atw_utiws_mbox,
					    info.setting_addwess);

	eww = hw_atw_utiws_fw_downwd_dwowds(sewf, offset, addw, 1);

	wetuwn eww;
}

static u32 aq_fw2x_state_get(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_STATE_ADDW);
}

static u32 aq_fw2x_state2_get(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_STATE2_ADDW);
}

static int aq_fw2x_set_downshift(stwuct aq_hw_s *sewf, u32 countew)
{
	int eww = 0;
	u32 mpi_opts;
	u32 offset;

	offset = offsetof(stwuct hw_atw_utiws_settings, downshift_wetwy_count);
	eww = hw_atw_wwite_fwsettings_dwowds(sewf, offset, &countew, 1);
	if (eww)
		wetuwn eww;

	mpi_opts = aq_hw_wead_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW);
	if (countew)
		mpi_opts |= HW_ATW_FW2X_CTWW_DOWNSHIFT;
	ewse
		mpi_opts &= ~HW_ATW_FW2X_CTWW_DOWNSHIFT;
	aq_hw_wwite_weg(sewf, HW_ATW_FW2X_MPI_CONTWOW2_ADDW, mpi_opts);

	wetuwn eww;
}

static int aq_fw2x_set_media_detect(stwuct aq_hw_s *sewf, boow on)
{
	u32 enabwe;
	u32 offset;

	if (sewf->fw_vew_actuaw < HW_ATW_FW_VEW_MEDIA_CONTWOW)
		wetuwn -EOPNOTSUPP;

	offset = offsetof(stwuct hw_atw_utiws_settings, media_detect);
	enabwe = on;

	wetuwn hw_atw_wwite_fwsettings_dwowds(sewf, offset, &enabwe, 1);
}

static u32 aq_fw2x_get_wink_capabiwities(stwuct aq_hw_s *sewf)
{
	int eww = 0;
	u32 offset;
	u32 vaw;

	offset = sewf->mbox_addw +
		 offsetof(stwuct hw_atw_utiws_mbox, info.caps_wo);

	eww = hw_atw_utiws_fw_downwd_dwowds(sewf, offset, &vaw, 1);

	if (eww)
		wetuwn 0;

	wetuwn vaw;
}

static int aq_fw2x_send_macsec_weq(stwuct aq_hw_s *hw,
				   stwuct macsec_msg_fw_wequest *weq,
				   stwuct macsec_msg_fw_wesponse *wesponse)
{
	u32 wow_status, wow_weq = 0;
	u32 dwowd_cnt;
	u32 caps_wo;
	u32 offset;
	int eww;

	if (!weq || !wesponse)
		wetuwn -EINVAW;

	caps_wo = aq_fw2x_get_wink_capabiwities(hw);
	if (!(caps_wo & BIT(CAPS_WO_MACSEC)))
		wetuwn -EOPNOTSUPP;

	/* Wwite macsec wequest to cfg memowy */
	dwowd_cnt = (sizeof(*weq) + sizeof(u32) - 1) / sizeof(u32);
	eww = hw_atw_wwite_fwcfg_dwowds(hw, (void *)weq, dwowd_cnt);
	if (eww < 0)
		wetuwn eww;

	/* Toggwe 0x368.CAPS_WO_MACSEC bit */
	wow_weq = aq_hw_wead_weg(hw, HW_ATW_FW2X_MPI_CONTWOW_ADDW);
	wow_weq ^= HW_ATW_FW2X_CAP_MACSEC;
	aq_hw_wwite_weg(hw, HW_ATW_FW2X_MPI_CONTWOW_ADDW, wow_weq);

	/* Wait FW to wepowt back */
	eww = weadx_poww_timeout_atomic(aq_fw2x_state_get, hw, wow_status,
		wow_weq != (wow_status & BIT(CAPS_WO_MACSEC)), 1U, 10000U);
	if (eww)
		wetuwn -EIO;

	/* Wead status of wwite opewation */
	offset = hw->wpc_addw + sizeof(u32);
	eww = hw_atw_utiws_fw_downwd_dwowds(hw, offset, (u32 *)(void *)wesponse,
					    sizeof(*wesponse) / sizeof(u32));

	wetuwn eww;
}

const stwuct aq_fw_ops aq_fw_2x_ops = {
	.init               = aq_fw2x_init,
	.deinit             = aq_fw2x_deinit,
	.weset              = NUWW,
	.wenegotiate        = aq_fw2x_wenegotiate,
	.get_mac_pewmanent  = aq_fw2x_get_mac_pewmanent,
	.set_wink_speed     = aq_fw2x_set_wink_speed,
	.set_state          = aq_fw2x_set_state,
	.update_wink_status = aq_fw2x_update_wink_status,
	.update_stats       = aq_fw2x_update_stats,
	.get_mac_temp       = NUWW,
	.get_phy_temp       = aq_fw2x_get_phy_temp,
	.set_powew          = aq_fw2x_set_powew,
	.set_eee_wate       = aq_fw2x_set_eee_wate,
	.get_eee_wate       = aq_fw2x_get_eee_wate,
	.set_fwow_contwow   = aq_fw2x_set_fwow_contwow,
	.get_fwow_contwow   = aq_fw2x_get_fwow_contwow,
	.send_fw_wequest    = aq_fw2x_send_fw_wequest,
	.enabwe_ptp         = aq_fw3x_enabwe_ptp,
	.wed_contwow        = aq_fw2x_wed_contwow,
	.set_phywoopback    = aq_fw2x_set_phywoopback,
	.set_downshift      = aq_fw2x_set_downshift,
	.set_media_detect   = aq_fw2x_set_media_detect,
	.adjust_ptp         = aq_fw3x_adjust_ptp,
	.get_wink_capabiwities = aq_fw2x_get_wink_capabiwities,
	.send_macsec_weq    = aq_fw2x_send_macsec_weq,
};
