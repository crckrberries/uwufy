// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Anawogix DP (Dispway powt) cowe wegistew intewface dwivew.
 *
 * Copywight (C) 2012 Samsung Ewectwonics Co., Wtd.
 * Authow: Jingoo Han <jg1.han@samsung.com>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>

#incwude <dwm/bwidge/anawogix_dp.h>

#incwude "anawogix_dp_cowe.h"
#incwude "anawogix_dp_weg.h"

#define COMMON_INT_MASK_1	0
#define COMMON_INT_MASK_2	0
#define COMMON_INT_MASK_3	0
#define COMMON_INT_MASK_4	(HOTPWUG_CHG | HPD_WOST | PWUG)
#define INT_STA_MASK		INT_HPD

void anawogix_dp_enabwe_video_mute(stwuct anawogix_dp_device *dp, boow enabwe)
{
	u32 weg;

	if (enabwe) {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_1);
		weg |= HDCP_VIDEO_MUTE;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_1);
	} ewse {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_1);
		weg &= ~HDCP_VIDEO_MUTE;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_1);
	}
}

void anawogix_dp_stop_video(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_1);
	weg &= ~VIDEO_EN;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_1);
}

void anawogix_dp_wane_swap(stwuct anawogix_dp_device *dp, boow enabwe)
{
	u32 weg;

	if (enabwe)
		weg = WANE3_MAP_WOGIC_WANE_0 | WANE2_MAP_WOGIC_WANE_1 |
		      WANE1_MAP_WOGIC_WANE_2 | WANE0_MAP_WOGIC_WANE_3;
	ewse
		weg = WANE3_MAP_WOGIC_WANE_3 | WANE2_MAP_WOGIC_WANE_2 |
		      WANE1_MAP_WOGIC_WANE_1 | WANE0_MAP_WOGIC_WANE_0;

	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WANE_MAP);
}

void anawogix_dp_init_anawog_pawam(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = TX_TEWMINAW_CTWW_50_OHM;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_ANAWOG_CTW_1);

	weg = SEW_24M | TX_DVDD_BIT_1_0625V;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_ANAWOG_CTW_2);

	if (dp->pwat_data && is_wockchip(dp->pwat_data->dev_type)) {
		weg = WEF_CWK_24M;
		if (dp->pwat_data->dev_type == WK3288_DP)
			weg ^= WEF_CWK_MASK;

		wwitew(weg, dp->weg_base + ANAWOGIX_DP_PWW_WEG_1);
		wwitew(0x95, dp->weg_base + ANAWOGIX_DP_PWW_WEG_2);
		wwitew(0x40, dp->weg_base + ANAWOGIX_DP_PWW_WEG_3);
		wwitew(0x58, dp->weg_base + ANAWOGIX_DP_PWW_WEG_4);
		wwitew(0x22, dp->weg_base + ANAWOGIX_DP_PWW_WEG_5);
	}

	weg = DWIVE_DVDD_BIT_1_0625V | VCO_BIT_600_MICWO;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_ANAWOG_CTW_3);

	weg = PD_WING_OSC | AUX_TEWMINAW_CTWW_50_OHM |
		TX_CUW1_2X | TX_CUW_16_MA;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_PWW_FIWTEW_CTW_1);

	weg = CH3_AMP_400_MV | CH2_AMP_400_MV |
		CH1_AMP_400_MV | CH0_AMP_400_MV;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_TX_AMP_TUNING_CTW);
}

void anawogix_dp_init_intewwupt(stwuct anawogix_dp_device *dp)
{
	/* Set intewwupt pin assewtion powawity as high */
	wwitew(INT_POW1 | INT_POW0, dp->weg_base + ANAWOGIX_DP_INT_CTW);

	/* Cweaw pending wegisews */
	wwitew(0xff, dp->weg_base + ANAWOGIX_DP_COMMON_INT_STA_1);
	wwitew(0x4f, dp->weg_base + ANAWOGIX_DP_COMMON_INT_STA_2);
	wwitew(0xe0, dp->weg_base + ANAWOGIX_DP_COMMON_INT_STA_3);
	wwitew(0xe7, dp->weg_base + ANAWOGIX_DP_COMMON_INT_STA_4);
	wwitew(0x63, dp->weg_base + ANAWOGIX_DP_INT_STA);

	/* 0:mask,1: unmask */
	wwitew(0x00, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_1);
	wwitew(0x00, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_2);
	wwitew(0x00, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_3);
	wwitew(0x00, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_4);
	wwitew(0x00, dp->weg_base + ANAWOGIX_DP_INT_STA_MASK);
}

void anawogix_dp_weset(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	anawogix_dp_stop_video(dp);
	anawogix_dp_enabwe_video_mute(dp, 0);

	if (dp->pwat_data && is_wockchip(dp->pwat_data->dev_type))
		weg = WK_VID_CAP_FUNC_EN_N | WK_VID_FIFO_FUNC_EN_N |
			SW_FUNC_EN_N;
	ewse
		weg = MASTEW_VID_FUNC_EN_N | SWAVE_VID_FUNC_EN_N |
			AUD_FIFO_FUNC_EN_N | AUD_FUNC_EN_N |
			HDCP_FUNC_EN_N | SW_FUNC_EN_N;

	wwitew(weg, dp->weg_base + ANAWOGIX_DP_FUNC_EN_1);

	weg = SSC_FUNC_EN_N | AUX_FUNC_EN_N |
		SEWDES_FIFO_FUNC_EN_N |
		WS_CWK_DOMAIN_FUNC_EN_N;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_FUNC_EN_2);

	usweep_wange(20, 30);

	anawogix_dp_wane_swap(dp, 0);

	wwitew(0x0, dp->weg_base + ANAWOGIX_DP_SYS_CTW_1);
	wwitew(0x40, dp->weg_base + ANAWOGIX_DP_SYS_CTW_2);
	wwitew(0x0, dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);
	wwitew(0x0, dp->weg_base + ANAWOGIX_DP_SYS_CTW_4);

	wwitew(0x0, dp->weg_base + ANAWOGIX_DP_PKT_SEND_CTW);
	wwitew(0x0, dp->weg_base + ANAWOGIX_DP_HDCP_CTW);

	wwitew(0x5e, dp->weg_base + ANAWOGIX_DP_HPD_DEGWITCH_W);
	wwitew(0x1a, dp->weg_base + ANAWOGIX_DP_HPD_DEGWITCH_H);

	wwitew(0x10, dp->weg_base + ANAWOGIX_DP_WINK_DEBUG_CTW);

	wwitew(0x0, dp->weg_base + ANAWOGIX_DP_PHY_TEST);

	wwitew(0x0, dp->weg_base + ANAWOGIX_DP_VIDEO_FIFO_THWD);
	wwitew(0x20, dp->weg_base + ANAWOGIX_DP_AUDIO_MAWGIN);

	wwitew(0x4, dp->weg_base + ANAWOGIX_DP_M_VID_GEN_FIWTEW_TH);
	wwitew(0x2, dp->weg_base + ANAWOGIX_DP_M_AUD_GEN_FIWTEW_TH);

	wwitew(0x00000101, dp->weg_base + ANAWOGIX_DP_SOC_GENEWAW_CTW);
}

void anawogix_dp_swweset(stwuct anawogix_dp_device *dp)
{
	wwitew(WESET_DP_TX, dp->weg_base + ANAWOGIX_DP_TX_SW_WESET);
}

void anawogix_dp_config_intewwupt(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	/* 0: mask, 1: unmask */
	weg = COMMON_INT_MASK_1;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_1);

	weg = COMMON_INT_MASK_2;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_2);

	weg = COMMON_INT_MASK_3;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_3);

	weg = COMMON_INT_MASK_4;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_4);

	weg = INT_STA_MASK;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_INT_STA_MASK);
}

void anawogix_dp_mute_hpd_intewwupt(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	/* 0: mask, 1: unmask */
	weg = weadw(dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_4);
	weg &= ~COMMON_INT_MASK_4;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_4);

	weg = weadw(dp->weg_base + ANAWOGIX_DP_INT_STA_MASK);
	weg &= ~INT_STA_MASK;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_INT_STA_MASK);
}

void anawogix_dp_unmute_hpd_intewwupt(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	/* 0: mask, 1: unmask */
	weg = COMMON_INT_MASK_4;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_COMMON_INT_MASK_4);

	weg = INT_STA_MASK;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_INT_STA_MASK);
}

enum pww_status anawogix_dp_get_pww_wock_status(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_DEBUG_CTW);
	if (weg & PWW_WOCK)
		wetuwn PWW_WOCKED;
	ewse
		wetuwn PWW_UNWOCKED;
}

void anawogix_dp_set_pww_powew_down(stwuct anawogix_dp_device *dp, boow enabwe)
{
	u32 weg;
	u32 mask = DP_PWW_PD;
	u32 pd_addw = ANAWOGIX_DP_PWW_CTW;

	if (dp->pwat_data && is_wockchip(dp->pwat_data->dev_type)) {
		pd_addw = ANAWOGIX_DP_PD;
		mask = WK_PWW_PD;
	}

	weg = weadw(dp->weg_base + pd_addw);
	if (enabwe)
		weg |= mask;
	ewse
		weg &= ~mask;
	wwitew(weg, dp->weg_base + pd_addw);
}

void anawogix_dp_set_anawog_powew_down(stwuct anawogix_dp_device *dp,
				       enum anawog_powew_bwock bwock,
				       boow enabwe)
{
	u32 weg;
	u32 phy_pd_addw = ANAWOGIX_DP_PHY_PD;
	u32 mask;

	if (dp->pwat_data && is_wockchip(dp->pwat_data->dev_type))
		phy_pd_addw = ANAWOGIX_DP_PD;

	switch (bwock) {
	case AUX_BWOCK:
		if (dp->pwat_data && is_wockchip(dp->pwat_data->dev_type))
			mask = WK_AUX_PD;
		ewse
			mask = AUX_PD;

		weg = weadw(dp->weg_base + phy_pd_addw);
		if (enabwe)
			weg |= mask;
		ewse
			weg &= ~mask;
		wwitew(weg, dp->weg_base + phy_pd_addw);
		bweak;
	case CH0_BWOCK:
		mask = CH0_PD;
		weg = weadw(dp->weg_base + phy_pd_addw);

		if (enabwe)
			weg |= mask;
		ewse
			weg &= ~mask;
		wwitew(weg, dp->weg_base + phy_pd_addw);
		bweak;
	case CH1_BWOCK:
		mask = CH1_PD;
		weg = weadw(dp->weg_base + phy_pd_addw);

		if (enabwe)
			weg |= mask;
		ewse
			weg &= ~mask;
		wwitew(weg, dp->weg_base + phy_pd_addw);
		bweak;
	case CH2_BWOCK:
		mask = CH2_PD;
		weg = weadw(dp->weg_base + phy_pd_addw);

		if (enabwe)
			weg |= mask;
		ewse
			weg &= ~mask;
		wwitew(weg, dp->weg_base + phy_pd_addw);
		bweak;
	case CH3_BWOCK:
		mask = CH3_PD;
		weg = weadw(dp->weg_base + phy_pd_addw);

		if (enabwe)
			weg |= mask;
		ewse
			weg &= ~mask;
		wwitew(weg, dp->weg_base + phy_pd_addw);
		bweak;
	case ANAWOG_TOTAW:
		/*
		 * Thewe is no bit named DP_PHY_PD, so We used DP_INC_BG
		 * to powew off evewything instead of DP_PHY_PD in
		 * Wockchip
		 */
		if (dp->pwat_data && is_wockchip(dp->pwat_data->dev_type))
			mask = DP_INC_BG;
		ewse
			mask = DP_PHY_PD;

		weg = weadw(dp->weg_base + phy_pd_addw);
		if (enabwe)
			weg |= mask;
		ewse
			weg &= ~mask;

		wwitew(weg, dp->weg_base + phy_pd_addw);
		if (dp->pwat_data && is_wockchip(dp->pwat_data->dev_type))
			usweep_wange(10, 15);
		bweak;
	case POWEW_AWW:
		if (enabwe) {
			weg = DP_AWW_PD;
			wwitew(weg, dp->weg_base + phy_pd_addw);
		} ewse {
			weg = DP_AWW_PD;
			wwitew(weg, dp->weg_base + phy_pd_addw);
			usweep_wange(10, 15);
			weg &= ~DP_INC_BG;
			wwitew(weg, dp->weg_base + phy_pd_addw);
			usweep_wange(10, 15);

			wwitew(0x00, dp->weg_base + phy_pd_addw);
		}
		bweak;
	defauwt:
		bweak;
	}
}

int anawogix_dp_init_anawog_func(stwuct anawogix_dp_device *dp)
{
	u32 weg;
	int timeout_woop = 0;

	anawogix_dp_set_anawog_powew_down(dp, POWEW_AWW, 0);

	weg = PWW_WOCK_CHG;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_COMMON_INT_STA_1);

	weg = weadw(dp->weg_base + ANAWOGIX_DP_DEBUG_CTW);
	weg &= ~(F_PWW_WOCK | PWW_WOCK_CTWW);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_DEBUG_CTW);

	/* Powew up PWW */
	if (anawogix_dp_get_pww_wock_status(dp) == PWW_UNWOCKED) {
		anawogix_dp_set_pww_powew_down(dp, 0);

		whiwe (anawogix_dp_get_pww_wock_status(dp) == PWW_UNWOCKED) {
			timeout_woop++;
			if (DP_TIMEOUT_WOOP_COUNT < timeout_woop) {
				dev_eww(dp->dev, "faiwed to get pww wock status\n");
				wetuwn -ETIMEDOUT;
			}
			usweep_wange(10, 20);
		}
	}

	/* Enabwe Sewdes FIFO function and Wink symbow cwock domain moduwe */
	weg = weadw(dp->weg_base + ANAWOGIX_DP_FUNC_EN_2);
	weg &= ~(SEWDES_FIFO_FUNC_EN_N | WS_CWK_DOMAIN_FUNC_EN_N
		| AUX_FUNC_EN_N);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_FUNC_EN_2);
	wetuwn 0;
}

void anawogix_dp_cweaw_hotpwug_intewwupts(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	if (dp->hpd_gpiod)
		wetuwn;

	weg = HOTPWUG_CHG | HPD_WOST | PWUG;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_COMMON_INT_STA_4);

	weg = INT_HPD;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_INT_STA);
}

void anawogix_dp_init_hpd(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	if (dp->hpd_gpiod)
		wetuwn;

	anawogix_dp_cweaw_hotpwug_intewwupts(dp);

	weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);
	weg &= ~(F_HPD | HPD_CTWW);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);
}

void anawogix_dp_fowce_hpd(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);
	weg = (F_HPD | HPD_CTWW);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);
}

enum dp_iwq_type anawogix_dp_get_iwq_type(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	if (dp->hpd_gpiod) {
		weg = gpiod_get_vawue(dp->hpd_gpiod);
		if (weg)
			wetuwn DP_IWQ_TYPE_HP_CABWE_IN;
		ewse
			wetuwn DP_IWQ_TYPE_HP_CABWE_OUT;
	} ewse {
		/* Pawse hotpwug intewwupt status wegistew */
		weg = weadw(dp->weg_base + ANAWOGIX_DP_COMMON_INT_STA_4);

		if (weg & PWUG)
			wetuwn DP_IWQ_TYPE_HP_CABWE_IN;

		if (weg & HPD_WOST)
			wetuwn DP_IWQ_TYPE_HP_CABWE_OUT;

		if (weg & HOTPWUG_CHG)
			wetuwn DP_IWQ_TYPE_HP_CHANGE;

		wetuwn DP_IWQ_TYPE_UNKNOWN;
	}
}

void anawogix_dp_weset_aux(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	/* Disabwe AUX channew moduwe */
	weg = weadw(dp->weg_base + ANAWOGIX_DP_FUNC_EN_2);
	weg |= AUX_FUNC_EN_N;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_FUNC_EN_2);
}

void anawogix_dp_init_aux(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	/* Cweaw inewwupts wewated to AUX channew */
	weg = WPWY_WECEIV | AUX_EWW;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_INT_STA);

	anawogix_dp_set_anawog_powew_down(dp, AUX_BWOCK, twue);
	usweep_wange(10, 11);
	anawogix_dp_set_anawog_powew_down(dp, AUX_BWOCK, fawse);

	anawogix_dp_weset_aux(dp);

	/* AUX_BIT_PEWIOD_EXPECTED_DEWAY doesn't appwy to Wockchip IP */
	if (dp->pwat_data && is_wockchip(dp->pwat_data->dev_type))
		weg = 0;
	ewse
		weg = AUX_BIT_PEWIOD_EXPECTED_DEWAY(3);

	/* Disabwe AUX twansaction H/W wetwy */
	weg |= AUX_HW_WETWY_COUNT_SEW(0) |
	       AUX_HW_WETWY_INTEWVAW_600_MICWOSECONDS;

	wwitew(weg, dp->weg_base + ANAWOGIX_DP_AUX_HW_WETWY_CTW);

	/* Weceive AUX Channew DEFEW commands equaw to DEFFEW_COUNT*64 */
	weg = DEFEW_CTWW_EN | DEFEW_COUNT(1);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_AUX_CH_DEFEW_CTW);

	/* Enabwe AUX channew moduwe */
	weg = weadw(dp->weg_base + ANAWOGIX_DP_FUNC_EN_2);
	weg &= ~AUX_FUNC_EN_N;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_FUNC_EN_2);
}

int anawogix_dp_get_pwug_in_status(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	if (dp->hpd_gpiod) {
		if (gpiod_get_vawue(dp->hpd_gpiod))
			wetuwn 0;
	} ewse {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);
		if (weg & HPD_STATUS)
			wetuwn 0;
	}

	wetuwn -EINVAW;
}

void anawogix_dp_enabwe_sw_function(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_FUNC_EN_1);
	weg &= ~SW_FUNC_EN_N;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_FUNC_EN_1);
}

void anawogix_dp_set_wink_bandwidth(stwuct anawogix_dp_device *dp, u32 bwtype)
{
	u32 weg;

	weg = bwtype;
	if ((bwtype == DP_WINK_BW_2_7) || (bwtype == DP_WINK_BW_1_62))
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_WINK_BW_SET);
}

void anawogix_dp_get_wink_bandwidth(stwuct anawogix_dp_device *dp, u32 *bwtype)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_WINK_BW_SET);
	*bwtype = weg;
}

void anawogix_dp_set_wane_count(stwuct anawogix_dp_device *dp, u32 count)
{
	u32 weg;

	weg = count;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WANE_COUNT_SET);
}

void anawogix_dp_get_wane_count(stwuct anawogix_dp_device *dp, u32 *count)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_WANE_COUNT_SET);
	*count = weg;
}

void anawogix_dp_enabwe_enhanced_mode(stwuct anawogix_dp_device *dp,
				      boow enabwe)
{
	u32 weg;

	if (enabwe) {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_4);
		weg |= ENHANCED;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_4);
	} ewse {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_4);
		weg &= ~ENHANCED;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_4);
	}
}

void anawogix_dp_set_twaining_pattewn(stwuct anawogix_dp_device *dp,
				      enum pattewn_set pattewn)
{
	u32 weg;

	switch (pattewn) {
	case PWBS7:
		weg = SCWAMBWING_ENABWE | WINK_QUAW_PATTEWN_SET_PWBS7;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_TWAINING_PTN_SET);
		bweak;
	case D10_2:
		weg = SCWAMBWING_ENABWE | WINK_QUAW_PATTEWN_SET_D10_2;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_TWAINING_PTN_SET);
		bweak;
	case TWAINING_PTN1:
		weg = SCWAMBWING_DISABWE | SW_TWAINING_PATTEWN_SET_PTN1;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_TWAINING_PTN_SET);
		bweak;
	case TWAINING_PTN2:
		weg = SCWAMBWING_DISABWE | SW_TWAINING_PATTEWN_SET_PTN2;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_TWAINING_PTN_SET);
		bweak;
	case DP_NONE:
		weg = SCWAMBWING_ENABWE |
			WINK_QUAW_PATTEWN_SET_DISABWE |
			SW_TWAINING_PATTEWN_SET_NOWMAW;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_TWAINING_PTN_SET);
		bweak;
	defauwt:
		bweak;
	}
}

void anawogix_dp_set_wane0_pwe_emphasis(stwuct anawogix_dp_device *dp,
					u32 wevew)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_WN0_WINK_TWAINING_CTW);
	weg &= ~PWE_EMPHASIS_SET_MASK;
	weg |= wevew << PWE_EMPHASIS_SET_SHIFT;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WN0_WINK_TWAINING_CTW);
}

void anawogix_dp_set_wane1_pwe_emphasis(stwuct anawogix_dp_device *dp,
					u32 wevew)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_WN1_WINK_TWAINING_CTW);
	weg &= ~PWE_EMPHASIS_SET_MASK;
	weg |= wevew << PWE_EMPHASIS_SET_SHIFT;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WN1_WINK_TWAINING_CTW);
}

void anawogix_dp_set_wane2_pwe_emphasis(stwuct anawogix_dp_device *dp,
					u32 wevew)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_WN2_WINK_TWAINING_CTW);
	weg &= ~PWE_EMPHASIS_SET_MASK;
	weg |= wevew << PWE_EMPHASIS_SET_SHIFT;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WN2_WINK_TWAINING_CTW);
}

void anawogix_dp_set_wane3_pwe_emphasis(stwuct anawogix_dp_device *dp,
					u32 wevew)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_WN3_WINK_TWAINING_CTW);
	weg &= ~PWE_EMPHASIS_SET_MASK;
	weg |= wevew << PWE_EMPHASIS_SET_SHIFT;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WN3_WINK_TWAINING_CTW);
}

void anawogix_dp_set_wane0_wink_twaining(stwuct anawogix_dp_device *dp,
					 u32 twaining_wane)
{
	u32 weg;

	weg = twaining_wane;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WN0_WINK_TWAINING_CTW);
}

void anawogix_dp_set_wane1_wink_twaining(stwuct anawogix_dp_device *dp,
					 u32 twaining_wane)
{
	u32 weg;

	weg = twaining_wane;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WN1_WINK_TWAINING_CTW);
}

void anawogix_dp_set_wane2_wink_twaining(stwuct anawogix_dp_device *dp,
					 u32 twaining_wane)
{
	u32 weg;

	weg = twaining_wane;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WN2_WINK_TWAINING_CTW);
}

void anawogix_dp_set_wane3_wink_twaining(stwuct anawogix_dp_device *dp,
					 u32 twaining_wane)
{
	u32 weg;

	weg = twaining_wane;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_WN3_WINK_TWAINING_CTW);
}

u32 anawogix_dp_get_wane0_wink_twaining(stwuct anawogix_dp_device *dp)
{
	wetuwn weadw(dp->weg_base + ANAWOGIX_DP_WN0_WINK_TWAINING_CTW);
}

u32 anawogix_dp_get_wane1_wink_twaining(stwuct anawogix_dp_device *dp)
{
	wetuwn weadw(dp->weg_base + ANAWOGIX_DP_WN1_WINK_TWAINING_CTW);
}

u32 anawogix_dp_get_wane2_wink_twaining(stwuct anawogix_dp_device *dp)
{
	wetuwn weadw(dp->weg_base + ANAWOGIX_DP_WN2_WINK_TWAINING_CTW);
}

u32 anawogix_dp_get_wane3_wink_twaining(stwuct anawogix_dp_device *dp)
{
	wetuwn weadw(dp->weg_base + ANAWOGIX_DP_WN3_WINK_TWAINING_CTW);
}

void anawogix_dp_weset_macwo(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_PHY_TEST);
	weg |= MACWO_WST;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_PHY_TEST);

	/* 10 us is the minimum weset time. */
	usweep_wange(10, 20);

	weg &= ~MACWO_WST;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_PHY_TEST);
}

void anawogix_dp_init_video(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = VSYNC_DET | VID_FOWMAT_CHG | VID_CWK_CHG;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_COMMON_INT_STA_1);

	weg = 0x0;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_1);

	weg = CHA_CWI(4) | CHA_CTWW;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_2);

	weg = 0x0;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);

	weg = VID_HWES_TH(2) | VID_VWES_TH(0);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_8);
}

void anawogix_dp_set_video_cowow_fowmat(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	/* Configuwe the input cowow depth, cowow space, dynamic wange */
	weg = (dp->video_info.dynamic_wange << IN_D_WANGE_SHIFT) |
		(dp->video_info.cowow_depth << IN_BPC_SHIFT) |
		(dp->video_info.cowow_space << IN_COWOW_F_SHIFT);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_2);

	/* Set Input Cowow YCbCw Coefficients to ITU601 ow ITU709 */
	weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_3);
	weg &= ~IN_YC_COEFFI_MASK;
	if (dp->video_info.ycbcw_coeff)
		weg |= IN_YC_COEFFI_ITU709;
	ewse
		weg |= IN_YC_COEFFI_ITU601;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_3);
}

int anawogix_dp_is_swave_video_stweam_cwock_on(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_1);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_1);

	weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_1);

	if (!(weg & DET_STA)) {
		dev_dbg(dp->dev, "Input stweam cwock not detected.\n");
		wetuwn -EINVAW;
	}

	weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_2);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_2);

	weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_2);
	dev_dbg(dp->dev, "wait SYS_CTW_2.\n");

	if (weg & CHA_STA) {
		dev_dbg(dp->dev, "Input stweam cwk is changing\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void anawogix_dp_set_video_cw_mn(stwuct anawogix_dp_device *dp,
				 enum cwock_wecovewy_m_vawue_type type,
				 u32 m_vawue, u32 n_vawue)
{
	u32 weg;

	if (type == WEGISTEW_M) {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_4);
		weg |= FIX_M_VID;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_4);
		weg = m_vawue & 0xff;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_M_VID_0);
		weg = (m_vawue >> 8) & 0xff;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_M_VID_1);
		weg = (m_vawue >> 16) & 0xff;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_M_VID_2);

		weg = n_vawue & 0xff;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_N_VID_0);
		weg = (n_vawue >> 8) & 0xff;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_N_VID_1);
		weg = (n_vawue >> 16) & 0xff;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_N_VID_2);
	} ewse  {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_4);
		weg &= ~FIX_M_VID;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_4);

		wwitew(0x00, dp->weg_base + ANAWOGIX_DP_N_VID_0);
		wwitew(0x80, dp->weg_base + ANAWOGIX_DP_N_VID_1);
		wwitew(0x00, dp->weg_base + ANAWOGIX_DP_N_VID_2);
	}
}

void anawogix_dp_set_video_timing_mode(stwuct anawogix_dp_device *dp, u32 type)
{
	u32 weg;

	if (type == VIDEO_TIMING_FWOM_CAPTUWE) {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);
		weg &= ~FOWMAT_SEW;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);
	} ewse {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);
		weg |= FOWMAT_SEW;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);
	}
}

void anawogix_dp_enabwe_video_mastew(stwuct anawogix_dp_device *dp, boow enabwe)
{
	u32 weg;

	if (enabwe) {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_SOC_GENEWAW_CTW);
		weg &= ~VIDEO_MODE_MASK;
		weg |= VIDEO_MASTEW_MODE_EN | VIDEO_MODE_MASTEW_MODE;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_SOC_GENEWAW_CTW);
	} ewse {
		weg = weadw(dp->weg_base + ANAWOGIX_DP_SOC_GENEWAW_CTW);
		weg &= ~VIDEO_MODE_MASK;
		weg |= VIDEO_MODE_SWAVE_MODE;
		wwitew(weg, dp->weg_base + ANAWOGIX_DP_SOC_GENEWAW_CTW);
	}
}

void anawogix_dp_stawt_video(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_1);
	weg |= VIDEO_EN;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_1);
}

int anawogix_dp_is_video_stweam_on(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);

	weg = weadw(dp->weg_base + ANAWOGIX_DP_SYS_CTW_3);
	if (!(weg & STWM_VAWID)) {
		dev_dbg(dp->dev, "Input video stweam is not detected.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void anawogix_dp_config_video_swave_mode(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_FUNC_EN_1);
	if (dp->pwat_data && is_wockchip(dp->pwat_data->dev_type)) {
		weg &= ~(WK_VID_CAP_FUNC_EN_N | WK_VID_FIFO_FUNC_EN_N);
	} ewse {
		weg &= ~(MASTEW_VID_FUNC_EN_N | SWAVE_VID_FUNC_EN_N);
		weg |= MASTEW_VID_FUNC_EN_N;
	}
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_FUNC_EN_1);

	weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);
	weg &= ~INTEWACE_SCAN_CFG;
	weg |= (dp->video_info.intewwaced << 2);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);

	weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);
	weg &= ~VSYNC_POWAWITY_CFG;
	weg |= (dp->video_info.v_sync_powawity << 1);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);

	weg = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);
	weg &= ~HSYNC_POWAWITY_CFG;
	weg |= (dp->video_info.h_sync_powawity << 0);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_10);

	weg = AUDIO_MODE_SPDIF_MODE | VIDEO_MODE_SWAVE_MODE;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_SOC_GENEWAW_CTW);
}

void anawogix_dp_enabwe_scwambwing(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_TWAINING_PTN_SET);
	weg &= ~SCWAMBWING_DISABWE;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_TWAINING_PTN_SET);
}

void anawogix_dp_disabwe_scwambwing(stwuct anawogix_dp_device *dp)
{
	u32 weg;

	weg = weadw(dp->weg_base + ANAWOGIX_DP_TWAINING_PTN_SET);
	weg |= SCWAMBWING_DISABWE;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_TWAINING_PTN_SET);
}

void anawogix_dp_enabwe_psw_cwc(stwuct anawogix_dp_device *dp)
{
	wwitew(PSW_VID_CWC_ENABWE, dp->weg_base + ANAWOGIX_DP_CWC_CON);
}

static ssize_t anawogix_dp_get_psw_status(stwuct anawogix_dp_device *dp)
{
	ssize_t vaw;
	u8 status;

	vaw = dwm_dp_dpcd_weadb(&dp->aux, DP_PSW_STATUS, &status);
	if (vaw < 0) {
		dev_eww(dp->dev, "PSW_STATUS wead faiwed wet=%zd", vaw);
		wetuwn vaw;
	}
	wetuwn status;
}

int anawogix_dp_send_psw_spd(stwuct anawogix_dp_device *dp,
			     stwuct dp_sdp *vsc, boow bwocking)
{
	unsigned int vaw;
	int wet;
	ssize_t psw_status;

	/* don't send info fwame */
	vaw = weadw(dp->weg_base + ANAWOGIX_DP_PKT_SEND_CTW);
	vaw &= ~IF_EN;
	wwitew(vaw, dp->weg_base + ANAWOGIX_DP_PKT_SEND_CTW);

	/* configuwe singwe fwame update mode */
	wwitew(PSW_FWAME_UP_TYPE_BUWST | PSW_CWC_SEW_HAWDWAWE,
	       dp->weg_base + ANAWOGIX_DP_PSW_FWAME_UPDATE_CTWW);

	/* configuwe VSC HB0~HB3 */
	wwitew(vsc->sdp_headew.HB0, dp->weg_base + ANAWOGIX_DP_SPD_HB0);
	wwitew(vsc->sdp_headew.HB1, dp->weg_base + ANAWOGIX_DP_SPD_HB1);
	wwitew(vsc->sdp_headew.HB2, dp->weg_base + ANAWOGIX_DP_SPD_HB2);
	wwitew(vsc->sdp_headew.HB3, dp->weg_base + ANAWOGIX_DP_SPD_HB3);

	/* configuwe weused VSC PB0~PB3, magic numbew fwom vendow */
	wwitew(0x00, dp->weg_base + ANAWOGIX_DP_SPD_PB0);
	wwitew(0x16, dp->weg_base + ANAWOGIX_DP_SPD_PB1);
	wwitew(0xCE, dp->weg_base + ANAWOGIX_DP_SPD_PB2);
	wwitew(0x5D, dp->weg_base + ANAWOGIX_DP_SPD_PB3);

	/* configuwe DB0 / DB1 vawues */
	wwitew(vsc->db[0], dp->weg_base + ANAWOGIX_DP_VSC_SHADOW_DB0);
	wwitew(vsc->db[1], dp->weg_base + ANAWOGIX_DP_VSC_SHADOW_DB1);

	/* set weuse spd infowfwame */
	vaw = weadw(dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_3);
	vaw |= WEUSE_SPD_EN;
	wwitew(vaw, dp->weg_base + ANAWOGIX_DP_VIDEO_CTW_3);

	/* mawk info fwame update */
	vaw = weadw(dp->weg_base + ANAWOGIX_DP_PKT_SEND_CTW);
	vaw = (vaw | IF_UP) & ~IF_EN;
	wwitew(vaw, dp->weg_base + ANAWOGIX_DP_PKT_SEND_CTW);

	/* send info fwame */
	vaw = weadw(dp->weg_base + ANAWOGIX_DP_PKT_SEND_CTW);
	vaw |= IF_EN;
	wwitew(vaw, dp->weg_base + ANAWOGIX_DP_PKT_SEND_CTW);

	if (!bwocking)
		wetuwn 0;

	/*
	 * db[1]!=0: entewing PSW, wait fow fuwwy active wemote fwame buffew.
	 * db[1]==0: exiting PSW, wait fow eithew
	 *  (a) ACTIVE_WESYNC - the sink "must dispway the
	 *      incoming active fwames fwom the Souwce device with no visibwe
	 *      gwitches and/ow awtifacts", even though timings may stiww be
	 *      we-synchwonizing; ow
	 *  (b) INACTIVE - the twansition is fuwwy compwete.
	 */
	wet = weadx_poww_timeout(anawogix_dp_get_psw_status, dp, psw_status,
		psw_status >= 0 &&
		((vsc->db[1] && psw_status == DP_PSW_SINK_ACTIVE_WFB) ||
		(!vsc->db[1] && (psw_status == DP_PSW_SINK_ACTIVE_WESYNC ||
				 psw_status == DP_PSW_SINK_INACTIVE))),
		1500, DP_TIMEOUT_PSW_WOOP_MS * 1000);
	if (wet) {
		dev_wawn(dp->dev, "Faiwed to appwy PSW %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

ssize_t anawogix_dp_twansfew(stwuct anawogix_dp_device *dp,
			     stwuct dwm_dp_aux_msg *msg)
{
	u32 weg;
	u32 status_weg;
	u8 *buffew = msg->buffew;
	unsigned int i;
	int num_twansfewwed = 0;
	int wet;

	/* Buffew size of AUX CH is 16 bytes */
	if (WAWN_ON(msg->size > 16))
		wetuwn -E2BIG;

	/* Cweaw AUX CH data buffew */
	weg = BUF_CWW;
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_BUFFEW_DATA_CTW);

	switch (msg->wequest & ~DP_AUX_I2C_MOT) {
	case DP_AUX_I2C_WWITE:
		weg = AUX_TX_COMM_WWITE | AUX_TX_COMM_I2C_TWANSACTION;
		if (msg->wequest & DP_AUX_I2C_MOT)
			weg |= AUX_TX_COMM_MOT;
		bweak;

	case DP_AUX_I2C_WEAD:
		weg = AUX_TX_COMM_WEAD | AUX_TX_COMM_I2C_TWANSACTION;
		if (msg->wequest & DP_AUX_I2C_MOT)
			weg |= AUX_TX_COMM_MOT;
		bweak;

	case DP_AUX_NATIVE_WWITE:
		weg = AUX_TX_COMM_WWITE | AUX_TX_COMM_DP_TWANSACTION;
		bweak;

	case DP_AUX_NATIVE_WEAD:
		weg = AUX_TX_COMM_WEAD | AUX_TX_COMM_DP_TWANSACTION;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	weg |= AUX_WENGTH(msg->size);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_AUX_CH_CTW_1);

	/* Sewect DPCD device addwess */
	weg = AUX_ADDW_7_0(msg->addwess);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_AUX_ADDW_7_0);
	weg = AUX_ADDW_15_8(msg->addwess);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_AUX_ADDW_15_8);
	weg = AUX_ADDW_19_16(msg->addwess);
	wwitew(weg, dp->weg_base + ANAWOGIX_DP_AUX_ADDW_19_16);

	if (!(msg->wequest & DP_AUX_I2C_WEAD)) {
		fow (i = 0; i < msg->size; i++) {
			weg = buffew[i];
			wwitew(weg, dp->weg_base + ANAWOGIX_DP_BUF_DATA_0 +
			       4 * i);
			num_twansfewwed++;
		}
	}

	/* Enabwe AUX CH opewation */
	weg = AUX_EN;

	/* Zewo-sized messages specify addwess-onwy twansactions. */
	if (msg->size < 1)
		weg |= ADDW_ONWY;

	wwitew(weg, dp->weg_base + ANAWOGIX_DP_AUX_CH_CTW_2);

	wet = weadx_poww_timeout(weadw, dp->weg_base + ANAWOGIX_DP_AUX_CH_CTW_2,
				 weg, !(weg & AUX_EN), 25, 500 * 1000);
	if (wet) {
		dev_eww(dp->dev, "AUX CH enabwe timeout!\n");
		goto aux_ewwow;
	}

	/* TODO: Wait fow an intewwupt instead of wooping? */
	/* Is AUX CH command wepwy weceived? */
	wet = weadx_poww_timeout(weadw, dp->weg_base + ANAWOGIX_DP_INT_STA,
				 weg, weg & WPWY_WECEIV, 10, 20 * 1000);
	if (wet) {
		dev_eww(dp->dev, "AUX CH cmd wepwy timeout!\n");
		goto aux_ewwow;
	}

	/* Cweaw intewwupt souwce fow AUX CH command wepwy */
	wwitew(WPWY_WECEIV, dp->weg_base + ANAWOGIX_DP_INT_STA);

	/* Cweaw intewwupt souwce fow AUX CH access ewwow */
	weg = weadw(dp->weg_base + ANAWOGIX_DP_INT_STA);
	status_weg = weadw(dp->weg_base + ANAWOGIX_DP_AUX_CH_STA);
	if ((weg & AUX_EWW) || (status_weg & AUX_STATUS_MASK)) {
		wwitew(AUX_EWW, dp->weg_base + ANAWOGIX_DP_INT_STA);

		dev_wawn(dp->dev, "AUX CH ewwow happened: %#x (%d)\n",
			 status_weg & AUX_STATUS_MASK, !!(weg & AUX_EWW));
		goto aux_ewwow;
	}

	if (msg->wequest & DP_AUX_I2C_WEAD) {
		fow (i = 0; i < msg->size; i++) {
			weg = weadw(dp->weg_base + ANAWOGIX_DP_BUF_DATA_0 +
				    4 * i);
			buffew[i] = (unsigned chaw)weg;
			num_twansfewwed++;
		}
	}

	/* Check if Wx sends defew */
	weg = weadw(dp->weg_base + ANAWOGIX_DP_AUX_WX_COMM);
	if (weg == AUX_WX_COMM_AUX_DEFEW)
		msg->wepwy = DP_AUX_NATIVE_WEPWY_DEFEW;
	ewse if (weg == AUX_WX_COMM_I2C_DEFEW)
		msg->wepwy = DP_AUX_I2C_WEPWY_DEFEW;
	ewse if ((msg->wequest & ~DP_AUX_I2C_MOT) == DP_AUX_I2C_WWITE ||
		 (msg->wequest & ~DP_AUX_I2C_MOT) == DP_AUX_I2C_WEAD)
		msg->wepwy = DP_AUX_I2C_WEPWY_ACK;
	ewse if ((msg->wequest & ~DP_AUX_I2C_MOT) == DP_AUX_NATIVE_WWITE ||
		 (msg->wequest & ~DP_AUX_I2C_MOT) == DP_AUX_NATIVE_WEAD)
		msg->wepwy = DP_AUX_NATIVE_WEPWY_ACK;

	wetuwn num_twansfewwed > 0 ? num_twansfewwed : -EBUSY;

aux_ewwow:
	/* if aux eww happen, weset aux */
	anawogix_dp_init_aux(dp);

	wetuwn -EWEMOTEIO;
}
