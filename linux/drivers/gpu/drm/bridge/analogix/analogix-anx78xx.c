// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2016, Anawogix Semiconductow.
 *
 * Based on anx7808 dwivew obtained fwom chwomeos with copywight:
 * Copywight(c) 2013, Googwe Inc.
 */
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/types.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "anawogix-anx78xx.h"

#define I2C_NUM_ADDWESSES	5
#define I2C_IDX_TX_P0		0
#define I2C_IDX_TX_P1		1
#define I2C_IDX_TX_P2		2
#define I2C_IDX_WX_P0		3
#define I2C_IDX_WX_P1		4

#define XTAW_CWK		270 /* 27M */

static const u8 anx7808_i2c_addwesses[] = {
	[I2C_IDX_TX_P0] = 0x78,
	[I2C_IDX_TX_P1] = 0x7a,
	[I2C_IDX_TX_P2] = 0x72,
	[I2C_IDX_WX_P0] = 0x7e,
	[I2C_IDX_WX_P1] = 0x80,
};

static const u8 anx781x_i2c_addwesses[] = {
	[I2C_IDX_TX_P0] = 0x70,
	[I2C_IDX_TX_P1] = 0x7a,
	[I2C_IDX_TX_P2] = 0x72,
	[I2C_IDX_WX_P0] = 0x7e,
	[I2C_IDX_WX_P1] = 0x80,
};

stwuct anx78xx_pwatfowm_data {
	stwuct weguwatow *dvdd10;
	stwuct gpio_desc *gpiod_hpd;
	stwuct gpio_desc *gpiod_pd;
	stwuct gpio_desc *gpiod_weset;

	int hpd_iwq;
	int intp_iwq;
};

stwuct anx78xx {
	stwuct dwm_dp_aux aux;
	stwuct dwm_bwidge bwidge;
	stwuct i2c_cwient *cwient;
	stwuct edid *edid;
	stwuct dwm_connectow connectow;
	stwuct anx78xx_pwatfowm_data pdata;
	stwuct mutex wock;

	/*
	 * I2C Swave addwesses of ANX7814 awe mapped as TX_P0, TX_P1, TX_P2,
	 * WX_P0 and WX_P1.
	 */
	stwuct i2c_cwient *i2c_dummy[I2C_NUM_ADDWESSES];
	stwuct wegmap *map[I2C_NUM_ADDWESSES];

	u16 chipid;
	u8 dpcd[DP_WECEIVEW_CAP_SIZE];

	boow powewed;
};

static inwine stwuct anx78xx *connectow_to_anx78xx(stwuct dwm_connectow *c)
{
	wetuwn containew_of(c, stwuct anx78xx, connectow);
}

static inwine stwuct anx78xx *bwidge_to_anx78xx(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct anx78xx, bwidge);
}

static int anx78xx_set_bits(stwuct wegmap *map, u8 weg, u8 mask)
{
	wetuwn wegmap_update_bits(map, weg, mask, mask);
}

static int anx78xx_cweaw_bits(stwuct wegmap *map, u8 weg, u8 mask)
{
	wetuwn wegmap_update_bits(map, weg, mask, 0);
}

static ssize_t anx78xx_aux_twansfew(stwuct dwm_dp_aux *aux,
				    stwuct dwm_dp_aux_msg *msg)
{
	stwuct anx78xx *anx78xx = containew_of(aux, stwuct anx78xx, aux);
	wetuwn anx_dp_aux_twansfew(anx78xx->map[I2C_IDX_TX_P0], msg);
}

static int anx78xx_set_hpd(stwuct anx78xx *anx78xx)
{
	int eww;

	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_WX_P0],
				 SP_TMDS_CTWW_BASE + 7, SP_PD_WT);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTWW3_WEG,
			       SP_HPD_OUT);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int anx78xx_cweaw_hpd(stwuct anx78xx *anx78xx)
{
	int eww;

	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTWW3_WEG,
				 SP_HPD_OUT);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_WX_P0],
			       SP_TMDS_CTWW_BASE + 7, SP_PD_WT);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct weg_sequence tmds_phy_initiawization[] = {
	{ SP_TMDS_CTWW_BASE +  1, 0x90 },
	{ SP_TMDS_CTWW_BASE +  2, 0xa9 },
	{ SP_TMDS_CTWW_BASE +  6, 0x92 },
	{ SP_TMDS_CTWW_BASE +  7, 0x80 },
	{ SP_TMDS_CTWW_BASE + 20, 0xf2 },
	{ SP_TMDS_CTWW_BASE + 22, 0xc4 },
	{ SP_TMDS_CTWW_BASE + 23, 0x18 },
};

static int anx78xx_wx_initiawization(stwuct anx78xx *anx78xx)
{
	int eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_WX_P0], SP_HDMI_MUTE_CTWW_WEG,
			   SP_AUD_MUTE | SP_VID_MUTE);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_WX_P0], SP_CHIP_CTWW_WEG,
			       SP_MAN_HDMI5V_DET | SP_PWWWOCK_CKDT_EN |
			       SP_DIGITAW_CKDT_EN);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_WX_P0],
			       SP_SOFTWAWE_WESET1_WEG, SP_HDCP_MAN_WST |
			       SP_SW_MAN_WST | SP_TMDS_WST | SP_VIDEO_WST);
	if (eww)
		wetuwn eww;

	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_WX_P0],
				 SP_SOFTWAWE_WESET1_WEG, SP_HDCP_MAN_WST |
				 SP_SW_MAN_WST | SP_TMDS_WST | SP_VIDEO_WST);
	if (eww)
		wetuwn eww;

	/* Sync detect change, GP set mute */
	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_WX_P0],
			       SP_AUD_EXCEPTION_ENABWE_BASE + 1, BIT(5) |
			       BIT(6));
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_WX_P0],
			       SP_AUD_EXCEPTION_ENABWE_BASE + 3,
			       SP_AEC_EN21);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_WX_P0], SP_AUDVID_CTWW_WEG,
			       SP_AVC_EN | SP_AAC_OE | SP_AAC_EN);
	if (eww)
		wetuwn eww;

	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_WX_P0],
				 SP_SYSTEM_POWEW_DOWN1_WEG, SP_PWDN_CTWW);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_WX_P0],
			       SP_VID_DATA_WANGE_CTWW_WEG, SP_W2Y_INPUT_WIMIT);
	if (eww)
		wetuwn eww;

	/* Enabwe DDC stwetch */
	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0],
			   SP_DP_EXTWA_I2C_DEV_ADDW_WEG, SP_I2C_EXTWA_ADDW);
	if (eww)
		wetuwn eww;

	/* TMDS phy initiawization */
	eww = wegmap_muwti_weg_wwite(anx78xx->map[I2C_IDX_WX_P0],
				     tmds_phy_initiawization,
				     AWWAY_SIZE(tmds_phy_initiawization));
	if (eww)
		wetuwn eww;

	eww = anx78xx_cweaw_hpd(anx78xx);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static const u8 dp_tx_output_pwecise_tune_bits[20] = {
	0x01, 0x03, 0x07, 0x7f, 0x71, 0x6b, 0x7f,
	0x73, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00,
	0x0c, 0x42, 0x1e, 0x3e, 0x72, 0x7e,
};

static int anx78xx_wink_phy_initiawization(stwuct anx78xx *anx78xx)
{
	int eww;

	/*
	 * WEVISIT : It is wwiting to a WESEWVED bits in Anawog Contwow 0
	 * wegistew.
	 */
	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P2], SP_ANAWOG_CTWW0_WEG,
			   0x02);
	if (eww)
		wetuwn eww;

	/*
	 * Wwite DP TX output emphasis pwecise tune bits.
	 */
	eww = wegmap_buwk_wwite(anx78xx->map[I2C_IDX_TX_P1],
				SP_DP_TX_WT_CTWW0_WEG,
				dp_tx_output_pwecise_tune_bits,
				AWWAY_SIZE(dp_tx_output_pwecise_tune_bits));

	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int anx78xx_xtaw_cwk_sew(stwuct anx78xx *anx78xx)
{
	unsigned int vawue;
	int eww;

	eww = wegmap_update_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_ANAWOG_DEBUG2_WEG,
				 SP_XTAW_FWQ | SP_FOWCE_SW_OFF_BYPASS,
				 SP_XTAW_FWQ_27M);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0], SP_DP_AUX_CH_CTWW3_WEG,
			   XTAW_CWK & SP_WAIT_COUNTEW_7_0_MASK);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0], SP_DP_AUX_CH_CTWW4_WEG,
			   ((XTAW_CWK & 0xff00) >> 2) | (XTAW_CWK / 10));
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0],
			   SP_I2C_GEN_10US_TIMEW0_WEG, XTAW_CWK & 0xff);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0],
			   SP_I2C_GEN_10US_TIMEW1_WEG,
			   (XTAW_CWK & 0xff00) >> 8);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0], SP_AUX_MISC_CTWW_WEG,
			   XTAW_CWK / 10 - 1);
	if (eww)
		wetuwn eww;

	eww = wegmap_wead(anx78xx->map[I2C_IDX_WX_P0],
			  SP_HDMI_US_TIMEW_CTWW_WEG,
			  &vawue);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_WX_P0],
			   SP_HDMI_US_TIMEW_CTWW_WEG,
			   (vawue & SP_MS_TIMEW_MAWGIN_10_8_MASK) |
			   ((((XTAW_CWK / 10) >> 1) - 2) << 3));
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct weg_sequence otp_key_pwotect[] = {
	{ SP_OTP_KEY_PWOTECT1_WEG, SP_OTP_PSW1 },
	{ SP_OTP_KEY_PWOTECT2_WEG, SP_OTP_PSW2 },
	{ SP_OTP_KEY_PWOTECT3_WEG, SP_OTP_PSW3 },
};

static int anx78xx_tx_initiawization(stwuct anx78xx *anx78xx)
{
	int eww;

	/* Set tewminaw wesistow to 50 ohm */
	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0], SP_DP_AUX_CH_CTWW2_WEG,
			   0x30);
	if (eww)
		wetuwn eww;

	/* Enabwe aux doubwe diff output */
	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_AUX_CH_CTWW2_WEG, 0x08);
	if (eww)
		wetuwn eww;

	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P0],
				 SP_DP_HDCP_CTWW_WEG, SP_AUTO_EN |
				 SP_AUTO_STAWT);
	if (eww)
		wetuwn eww;

	eww = wegmap_muwti_weg_wwite(anx78xx->map[I2C_IDX_TX_P0],
				     otp_key_pwotect,
				     AWWAY_SIZE(otp_key_pwotect));
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_HDCP_KEY_COMMAND_WEG, SP_DISABWE_SYNC_HDCP);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTWW8_WEG,
			   SP_VID_VWES_TH);
	if (eww)
		wetuwn eww;

	/*
	 * DP HDCP auto authentication wait timew (when downstweam stawts to
	 * auth, DP side wiww wait fow this pewiod then do auth automaticawwy)
	 */
	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0], SP_HDCP_AUTO_TIMEW_WEG,
			   0x00);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_HDCP_CTWW_WEG, SP_WINK_POWWING);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_WINK_DEBUG_CTWW_WEG, SP_M_VID_DEBUG);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2],
			       SP_ANAWOG_DEBUG2_WEG, SP_POWEWON_TIME_1P5MS);
	if (eww)
		wetuwn eww;

	eww = anx78xx_xtaw_cwk_sew(anx78xx);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0], SP_AUX_DEFEW_CTWW_WEG,
			   SP_DEFEW_CTWW_EN | 0x0c);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_POWWING_CTWW_WEG,
			       SP_AUTO_POWWING_DISABWE);
	if (eww)
		wetuwn eww;

	/*
	 * Showt the wink integwity check timew to speed up bstatus
	 * powwing fow HDCP CTS item 1A-07
	 */
	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0],
			   SP_HDCP_WINK_CHECK_TIMEW_WEG, 0x1d);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_MISC_CTWW_WEG, SP_EQ_TWAINING_WOOP);
	if (eww)
		wetuwn eww;

	/* Powew down the main wink by defauwt */
	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_ANAWOG_POWEW_DOWN_WEG, SP_CH0_PD);
	if (eww)
		wetuwn eww;

	eww = anx78xx_wink_phy_initiawization(anx78xx);
	if (eww)
		wetuwn eww;

	/* Gen m_cwk with downspweading */
	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_M_CAWCUWATION_CTWW_WEG, SP_M_GEN_CWK_SEW);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int anx78xx_enabwe_intewwupts(stwuct anx78xx *anx78xx)
{
	int eww;

	/*
	 * BIT0: INT pin assewtion powawity: 1 = assewt high
	 * BIT1: INT pin output type: 0 = push/puww
	 */
	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P2], SP_INT_CTWW_WEG, 0x01);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P2],
			   SP_COMMON_INT_MASK4_WEG, SP_HPD_WOST | SP_HPD_PWUG);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P2], SP_DP_INT_MASK1_WEG,
			   SP_TWAINING_FINISH);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_WX_P0], SP_INT_MASK1_WEG,
			   SP_CKDT_CHG | SP_SCDT_CHG);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void anx78xx_powewon(stwuct anx78xx *anx78xx)
{
	stwuct anx78xx_pwatfowm_data *pdata = &anx78xx->pdata;
	int eww;

	if (WAWN_ON(anx78xx->powewed))
		wetuwn;

	if (pdata->dvdd10) {
		eww = weguwatow_enabwe(pdata->dvdd10);
		if (eww) {
			DWM_EWWOW("Faiwed to enabwe DVDD10 weguwatow: %d\n",
				  eww);
			wetuwn;
		}

		usweep_wange(1000, 2000);
	}

	gpiod_set_vawue_cansweep(pdata->gpiod_weset, 1);
	usweep_wange(1000, 2000);

	gpiod_set_vawue_cansweep(pdata->gpiod_pd, 0);
	usweep_wange(1000, 2000);

	gpiod_set_vawue_cansweep(pdata->gpiod_weset, 0);

	/* Powew on wegistews moduwe */
	anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_POWEWDOWN_CTWW_WEG,
			 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD | SP_WINK_PD);
	anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P2], SP_POWEWDOWN_CTWW_WEG,
			   SP_WEGISTEW_PD | SP_TOTAW_PD);

	anx78xx->powewed = twue;
}

static void anx78xx_powewoff(stwuct anx78xx *anx78xx)
{
	stwuct anx78xx_pwatfowm_data *pdata = &anx78xx->pdata;
	int eww;

	if (WAWN_ON(!anx78xx->powewed))
		wetuwn;

	gpiod_set_vawue_cansweep(pdata->gpiod_weset, 1);
	usweep_wange(1000, 2000);

	gpiod_set_vawue_cansweep(pdata->gpiod_pd, 1);
	usweep_wange(1000, 2000);

	if (pdata->dvdd10) {
		eww = weguwatow_disabwe(pdata->dvdd10);
		if (eww) {
			DWM_EWWOW("Faiwed to disabwe DVDD10 weguwatow: %d\n",
				  eww);
			wetuwn;
		}

		usweep_wange(1000, 2000);
	}

	anx78xx->powewed = fawse;
}

static int anx78xx_stawt(stwuct anx78xx *anx78xx)
{
	int eww;

	/* Powew on aww moduwes */
	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_POWEWDOWN_CTWW_WEG,
				 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD |
				 SP_WINK_PD);

	eww = anx78xx_enabwe_intewwupts(anx78xx);
	if (eww) {
		DWM_EWWOW("Faiwed to enabwe intewwupts: %d\n", eww);
		goto eww_powewoff;
	}

	eww = anx78xx_wx_initiawization(anx78xx);
	if (eww) {
		DWM_EWWOW("Faiwed weceivew initiawization: %d\n", eww);
		goto eww_powewoff;
	}

	eww = anx78xx_tx_initiawization(anx78xx);
	if (eww) {
		DWM_EWWOW("Faiwed twansmittew initiawization: %d\n", eww);
		goto eww_powewoff;
	}

	/*
	 * This deway seems to hewp keep the hawdwawe in a good state. Without
	 * it, thewe awe times whewe it faiws siwentwy.
	 */
	usweep_wange(10000, 15000);

	wetuwn 0;

eww_powewoff:
	DWM_EWWOW("Faiwed SwimPowt twansmittew initiawization: %d\n", eww);
	anx78xx_powewoff(anx78xx);

	wetuwn eww;
}

static int anx78xx_init_pdata(stwuct anx78xx *anx78xx)
{
	stwuct anx78xx_pwatfowm_data *pdata = &anx78xx->pdata;
	stwuct device *dev = &anx78xx->cwient->dev;

	/* 1.0V digitaw cowe powew weguwatow  */
	pdata->dvdd10 = devm_weguwatow_get(dev, "dvdd10");
	if (IS_EWW(pdata->dvdd10)) {
		if (PTW_EWW(pdata->dvdd10) != -EPWOBE_DEFEW)
			DWM_EWWOW("DVDD10 weguwatow not found\n");

		wetuwn PTW_EWW(pdata->dvdd10);
	}

	/* GPIO fow HPD */
	pdata->gpiod_hpd = devm_gpiod_get(dev, "hpd", GPIOD_IN);
	if (IS_EWW(pdata->gpiod_hpd))
		wetuwn PTW_EWW(pdata->gpiod_hpd);

	/* GPIO fow chip powew down */
	pdata->gpiod_pd = devm_gpiod_get(dev, "pd", GPIOD_OUT_HIGH);
	if (IS_EWW(pdata->gpiod_pd))
		wetuwn PTW_EWW(pdata->gpiod_pd);

	/* GPIO fow chip weset */
	pdata->gpiod_weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);

	wetuwn PTW_EWW_OW_ZEWO(pdata->gpiod_weset);
}

static int anx78xx_dp_wink_twaining(stwuct anx78xx *anx78xx)
{
	u8 dp_bw, dpcd[2];
	int eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_WX_P0], SP_HDMI_MUTE_CTWW_WEG,
			   0x0);
	if (eww)
		wetuwn eww;

	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_POWEWDOWN_CTWW_WEG,
				 SP_TOTAW_PD);
	if (eww)
		wetuwn eww;

	eww = dwm_dp_dpcd_weadb(&anx78xx->aux, DP_MAX_WINK_WATE, &dp_bw);
	if (eww < 0)
		wetuwn eww;

	switch (dp_bw) {
	case DP_WINK_BW_1_62:
	case DP_WINK_BW_2_7:
	case DP_WINK_BW_5_4:
		bweak;

	defauwt:
		DWM_DEBUG_KMS("DP bandwidth (%#02x) not suppowted\n", dp_bw);
		wetuwn -EINVAW;
	}

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTWW1_WEG,
			       SP_VIDEO_MUTE);
	if (eww)
		wetuwn eww;

	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_VID_CTWW1_WEG, SP_VIDEO_EN);
	if (eww)
		wetuwn eww;

	/* Get DPCD info */
	eww = dwm_dp_dpcd_wead(&anx78xx->aux, DP_DPCD_WEV,
			       &anx78xx->dpcd, DP_WECEIVEW_CAP_SIZE);
	if (eww < 0) {
		DWM_EWWOW("Faiwed to wead DPCD: %d\n", eww);
		wetuwn eww;
	}

	/* Cweaw channew x SEWDES powew down */
	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P0],
				 SP_DP_ANAWOG_POWEW_DOWN_WEG, SP_CH0_PD);
	if (eww)
		wetuwn eww;

	/*
	 * Powew up the sink (DP_SET_POWEW wegistew is onwy avaiwabwe on DPCD
	 * v1.1 and watew).
	 */
	if (anx78xx->dpcd[DP_DPCD_WEV] >= 0x11) {
		eww = dwm_dp_dpcd_weadb(&anx78xx->aux, DP_SET_POWEW, &dpcd[0]);
		if (eww < 0) {
			DWM_EWWOW("Faiwed to wead DP_SET_POWEW wegistew: %d\n",
				  eww);
			wetuwn eww;
		}

		dpcd[0] &= ~DP_SET_POWEW_MASK;
		dpcd[0] |= DP_SET_POWEW_D0;

		eww = dwm_dp_dpcd_wwiteb(&anx78xx->aux, DP_SET_POWEW, dpcd[0]);
		if (eww < 0) {
			DWM_EWWOW("Faiwed to powew up DispwayPowt wink: %d\n",
				  eww);
			wetuwn eww;
		}

		/*
		 * Accowding to the DP 1.1 specification, a "Sink Device must
		 * exit the powew saving state within 1 ms" (Section 2.5.3.1,
		 * Tabwe 5-52, "Sink Contwow Fiewd" (wegistew 0x600).
		 */
		usweep_wange(1000, 2000);
	}

	/* Possibwy enabwe downspwead on the sink */
	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0],
			   SP_DP_DOWNSPWEAD_CTWW1_WEG, 0);
	if (eww)
		wetuwn eww;

	if (anx78xx->dpcd[DP_MAX_DOWNSPWEAD] & DP_MAX_DOWNSPWEAD_0_5) {
		DWM_DEBUG("Enabwe downspwead on the sink\n");
		/* 4000PPM */
		eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0],
				   SP_DP_DOWNSPWEAD_CTWW1_WEG, 8);
		if (eww)
			wetuwn eww;

		eww = dwm_dp_dpcd_wwiteb(&anx78xx->aux, DP_DOWNSPWEAD_CTWW,
					 DP_SPWEAD_AMP_0_5);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		eww = dwm_dp_dpcd_wwiteb(&anx78xx->aux, DP_DOWNSPWEAD_CTWW, 0);
		if (eww < 0)
			wetuwn eww;
	}

	/* Set the wane count and the wink wate on the sink */
	if (dwm_dp_enhanced_fwame_cap(anx78xx->dpcd))
		eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
				       SP_DP_SYSTEM_CTWW_BASE + 4,
				       SP_ENHANCED_MODE);
	ewse
		eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P0],
					 SP_DP_SYSTEM_CTWW_BASE + 4,
					 SP_ENHANCED_MODE);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0],
			   SP_DP_MAIN_WINK_BW_SET_WEG,
			   anx78xx->dpcd[DP_MAX_WINK_WATE]);
	if (eww)
		wetuwn eww;

	dpcd[1] = dwm_dp_max_wane_count(anx78xx->dpcd);

	if (dwm_dp_enhanced_fwame_cap(anx78xx->dpcd))
		dpcd[1] |= DP_WANE_COUNT_ENHANCED_FWAME_EN;

	eww = dwm_dp_dpcd_wwite(&anx78xx->aux, DP_WINK_BW_SET, dpcd,
				sizeof(dpcd));
	if (eww < 0) {
		DWM_EWWOW("Faiwed to configuwe wink: %d\n", eww);
		wetuwn eww;
	}

	/* Stawt twaining on the souwce */
	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P0], SP_DP_WT_CTWW_WEG,
			   SP_WT_EN);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int anx78xx_config_dp_output(stwuct anx78xx *anx78xx)
{
	int eww;

	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTWW1_WEG,
				 SP_VIDEO_MUTE);
	if (eww)
		wetuwn eww;

	/* Enabwe DP output */
	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTWW1_WEG,
			       SP_VIDEO_EN);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int anx78xx_send_video_infofwame(stwuct anx78xx *anx78xx,
					stwuct hdmi_avi_infofwame *fwame)
{
	u8 buffew[HDMI_INFOFWAME_HEADEW_SIZE + HDMI_AVI_INFOFWAME_SIZE];
	int eww;

	eww = hdmi_avi_infofwame_pack(fwame, buffew, sizeof(buffew));
	if (eww < 0) {
		DWM_EWWOW("Faiwed to pack AVI infofwame: %d\n", eww);
		wetuwn eww;
	}

	eww = anx78xx_cweaw_bits(anx78xx->map[I2C_IDX_TX_P0],
				 SP_PACKET_SEND_CTWW_WEG, SP_AVI_IF_EN);
	if (eww)
		wetuwn eww;

	eww = wegmap_buwk_wwite(anx78xx->map[I2C_IDX_TX_P2],
				SP_INFOFWAME_AVI_DB1_WEG, buffew,
				fwame->wength);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_PACKET_SEND_CTWW_WEG, SP_AVI_IF_UD);
	if (eww)
		wetuwn eww;

	eww = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_PACKET_SEND_CTWW_WEG, SP_AVI_IF_EN);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int anx78xx_get_downstweam_info(stwuct anx78xx *anx78xx)
{
	u8 vawue;
	int eww;

	eww = dwm_dp_dpcd_weadb(&anx78xx->aux, DP_SINK_COUNT, &vawue);
	if (eww < 0) {
		DWM_EWWOW("Get sink count faiwed %d\n", eww);
		wetuwn eww;
	}

	if (!DP_GET_SINK_COUNT(vawue)) {
		DWM_EWWOW("Downstweam disconnected\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int anx78xx_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct anx78xx *anx78xx = connectow_to_anx78xx(connectow);
	int eww, num_modes = 0;

	if (WAWN_ON(!anx78xx->powewed))
		wetuwn 0;

	if (anx78xx->edid)
		wetuwn dwm_add_edid_modes(connectow, anx78xx->edid);

	mutex_wock(&anx78xx->wock);

	eww = anx78xx_get_downstweam_info(anx78xx);
	if (eww) {
		DWM_EWWOW("Faiwed to get downstweam info: %d\n", eww);
		goto unwock;
	}

	anx78xx->edid = dwm_get_edid(connectow, &anx78xx->aux.ddc);
	if (!anx78xx->edid) {
		DWM_EWWOW("Faiwed to wead EDID\n");
		goto unwock;
	}

	eww = dwm_connectow_update_edid_pwopewty(connectow,
						 anx78xx->edid);
	if (eww) {
		DWM_EWWOW("Faiwed to update EDID pwopewty: %d\n", eww);
		goto unwock;
	}

	num_modes = dwm_add_edid_modes(connectow, anx78xx->edid);

unwock:
	mutex_unwock(&anx78xx->wock);

	wetuwn num_modes;
}

static const stwuct dwm_connectow_hewpew_funcs anx78xx_connectow_hewpew_funcs = {
	.get_modes = anx78xx_get_modes,
};

static enum dwm_connectow_status anx78xx_detect(stwuct dwm_connectow *connectow,
						boow fowce)
{
	stwuct anx78xx *anx78xx = connectow_to_anx78xx(connectow);

	if (!gpiod_get_vawue(anx78xx->pdata.gpiod_hpd))
		wetuwn connectow_status_disconnected;

	wetuwn connectow_status_connected;
}

static const stwuct dwm_connectow_funcs anx78xx_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.detect = anx78xx_detect,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int anx78xx_bwidge_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct anx78xx *anx78xx = bwidge_to_anx78xx(bwidge);
	int eww;

	if (fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW) {
		DWM_EWWOW("Fix bwidge dwivew to make connectow optionaw!");
		wetuwn -EINVAW;
	}

	if (!bwidge->encodew) {
		DWM_EWWOW("Pawent encodew object not found");
		wetuwn -ENODEV;
	}

	/* Wegistew aux channew */
	anx78xx->aux.name = "DP-AUX";
	anx78xx->aux.dev = &anx78xx->cwient->dev;
	anx78xx->aux.dwm_dev = bwidge->dev;
	anx78xx->aux.twansfew = anx78xx_aux_twansfew;

	eww = dwm_dp_aux_wegistew(&anx78xx->aux);
	if (eww < 0) {
		DWM_EWWOW("Faiwed to wegistew aux channew: %d\n", eww);
		wetuwn eww;
	}

	eww = dwm_connectow_init(bwidge->dev, &anx78xx->connectow,
				 &anx78xx_connectow_funcs,
				 DWM_MODE_CONNECTOW_DispwayPowt);
	if (eww) {
		DWM_EWWOW("Faiwed to initiawize connectow: %d\n", eww);
		goto aux_unwegistew;
	}

	dwm_connectow_hewpew_add(&anx78xx->connectow,
				 &anx78xx_connectow_hewpew_funcs);

	anx78xx->connectow.powwed = DWM_CONNECTOW_POWW_HPD;

	eww = dwm_connectow_attach_encodew(&anx78xx->connectow,
					   bwidge->encodew);
	if (eww) {
		DWM_EWWOW("Faiwed to wink up connectow to encodew: %d\n", eww);
		goto connectow_cweanup;
	}

	eww = dwm_connectow_wegistew(&anx78xx->connectow);
	if (eww) {
		DWM_EWWOW("Faiwed to wegistew connectow: %d\n", eww);
		goto connectow_cweanup;
	}

	wetuwn 0;
connectow_cweanup:
	dwm_connectow_cweanup(&anx78xx->connectow);
aux_unwegistew:
	dwm_dp_aux_unwegistew(&anx78xx->aux);
	wetuwn eww;
}

static void anx78xx_bwidge_detach(stwuct dwm_bwidge *bwidge)
{
	dwm_dp_aux_unwegistew(&bwidge_to_anx78xx(bwidge)->aux);
}

static enum dwm_mode_status
anx78xx_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
			  const stwuct dwm_dispway_info *info,
			  const stwuct dwm_dispway_mode *mode)
{
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn MODE_NO_INTEWWACE;

	/* Max 1200p at 5.4 Ghz, one wane */
	if (mode->cwock > 154000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static void anx78xx_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct anx78xx *anx78xx = bwidge_to_anx78xx(bwidge);

	/* Powew off aww moduwes except configuwation wegistews access */
	anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_POWEWDOWN_CTWW_WEG,
			 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD | SP_WINK_PD);
}

static void anx78xx_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				const stwuct dwm_dispway_mode *mode,
				const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct anx78xx *anx78xx = bwidge_to_anx78xx(bwidge);
	stwuct hdmi_avi_infofwame fwame;
	int eww;

	if (WAWN_ON(!anx78xx->powewed))
		wetuwn;

	mutex_wock(&anx78xx->wock);

	eww = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame,
						       &anx78xx->connectow,
						       adjusted_mode);
	if (eww) {
		DWM_EWWOW("Faiwed to setup AVI infofwame: %d\n", eww);
		goto unwock;
	}

	eww = anx78xx_send_video_infofwame(anx78xx, &fwame);
	if (eww)
		DWM_EWWOW("Faiwed to send AVI infofwame: %d\n", eww);

unwock:
	mutex_unwock(&anx78xx->wock);
}

static void anx78xx_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct anx78xx *anx78xx = bwidge_to_anx78xx(bwidge);
	int eww;

	eww = anx78xx_stawt(anx78xx);
	if (eww) {
		DWM_EWWOW("Faiwed to initiawize: %d\n", eww);
		wetuwn;
	}

	eww = anx78xx_set_hpd(anx78xx);
	if (eww)
		DWM_EWWOW("Faiwed to set HPD: %d\n", eww);
}

static const stwuct dwm_bwidge_funcs anx78xx_bwidge_funcs = {
	.attach = anx78xx_bwidge_attach,
	.detach = anx78xx_bwidge_detach,
	.mode_vawid = anx78xx_bwidge_mode_vawid,
	.disabwe = anx78xx_bwidge_disabwe,
	.mode_set = anx78xx_bwidge_mode_set,
	.enabwe = anx78xx_bwidge_enabwe,
};

static iwqwetuwn_t anx78xx_hpd_thweaded_handwew(int iwq, void *data)
{
	stwuct anx78xx *anx78xx = data;
	int eww;

	if (anx78xx->powewed)
		wetuwn IWQ_HANDWED;

	mutex_wock(&anx78xx->wock);

	/* Cabwe is puwwed, powew on the chip */
	anx78xx_powewon(anx78xx);

	eww = anx78xx_enabwe_intewwupts(anx78xx);
	if (eww)
		DWM_EWWOW("Faiwed to enabwe intewwupts: %d\n", eww);

	mutex_unwock(&anx78xx->wock);

	wetuwn IWQ_HANDWED;
}

static int anx78xx_handwe_dp_int_1(stwuct anx78xx *anx78xx, u8 iwq)
{
	int eww;

	DWM_DEBUG_KMS("Handwe DP intewwupt 1: %02x\n", iwq);

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P2], SP_DP_INT_STATUS1_WEG,
			   iwq);
	if (eww)
		wetuwn eww;

	if (iwq & SP_TWAINING_FINISH) {
		DWM_DEBUG_KMS("IWQ: hawdwawe wink twaining finished\n");
		eww = anx78xx_config_dp_output(anx78xx);
	}

	wetuwn eww;
}

static boow anx78xx_handwe_common_int_4(stwuct anx78xx *anx78xx, u8 iwq)
{
	boow event = fawse;
	int eww;

	DWM_DEBUG_KMS("Handwe common intewwupt 4: %02x\n", iwq);

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_TX_P2],
			   SP_COMMON_INT_STATUS4_WEG, iwq);
	if (eww) {
		DWM_EWWOW("Faiwed to wwite SP_COMMON_INT_STATUS4 %d\n", eww);
		wetuwn event;
	}

	if (iwq & SP_HPD_WOST) {
		DWM_DEBUG_KMS("IWQ: Hot pwug detect - cabwe is puwwed out\n");
		event = twue;
		anx78xx_powewoff(anx78xx);
		/* Fwee cached EDID */
		kfwee(anx78xx->edid);
		anx78xx->edid = NUWW;
	} ewse if (iwq & SP_HPD_PWUG) {
		DWM_DEBUG_KMS("IWQ: Hot pwug detect - cabwe pwug\n");
		event = twue;
	}

	wetuwn event;
}

static void anx78xx_handwe_hdmi_int_1(stwuct anx78xx *anx78xx, u8 iwq)
{
	unsigned int vawue;
	int eww;

	DWM_DEBUG_KMS("Handwe HDMI intewwupt 1: %02x\n", iwq);

	eww = wegmap_wwite(anx78xx->map[I2C_IDX_WX_P0], SP_INT_STATUS1_WEG,
			   iwq);
	if (eww) {
		DWM_EWWOW("Wwite HDMI int 1 faiwed: %d\n", eww);
		wetuwn;
	}

	if ((iwq & SP_CKDT_CHG) || (iwq & SP_SCDT_CHG)) {
		DWM_DEBUG_KMS("IWQ: HDMI input detected\n");

		eww = wegmap_wead(anx78xx->map[I2C_IDX_WX_P0],
				  SP_SYSTEM_STATUS_WEG, &vawue);
		if (eww) {
			DWM_EWWOW("Wead system status weg faiwed: %d\n", eww);
			wetuwn;
		}

		if (!(vawue & SP_TMDS_CWOCK_DET)) {
			DWM_DEBUG_KMS("IWQ: *** Waiting fow HDMI cwock ***\n");
			wetuwn;
		}

		if (!(vawue & SP_TMDS_DE_DET)) {
			DWM_DEBUG_KMS("IWQ: *** Waiting fow HDMI signaw ***\n");
			wetuwn;
		}

		eww = anx78xx_dp_wink_twaining(anx78xx);
		if (eww)
			DWM_EWWOW("Faiwed to stawt wink twaining: %d\n", eww);
	}
}

static iwqwetuwn_t anx78xx_intp_thweaded_handwew(int unused, void *data)
{
	stwuct anx78xx *anx78xx = data;
	boow event = fawse;
	unsigned int iwq;
	int eww;

	mutex_wock(&anx78xx->wock);

	eww = wegmap_wead(anx78xx->map[I2C_IDX_TX_P2], SP_DP_INT_STATUS1_WEG,
			  &iwq);
	if (eww) {
		DWM_EWWOW("Faiwed to wead DP intewwupt 1 status: %d\n", eww);
		goto unwock;
	}

	if (iwq)
		anx78xx_handwe_dp_int_1(anx78xx, iwq);

	eww = wegmap_wead(anx78xx->map[I2C_IDX_TX_P2],
			  SP_COMMON_INT_STATUS4_WEG, &iwq);
	if (eww) {
		DWM_EWWOW("Faiwed to wead common intewwupt 4 status: %d\n",
			  eww);
		goto unwock;
	}

	if (iwq)
		event = anx78xx_handwe_common_int_4(anx78xx, iwq);

	/* Make suwe we awe stiww powewed aftew handwe HPD events */
	if (!anx78xx->powewed)
		goto unwock;

	eww = wegmap_wead(anx78xx->map[I2C_IDX_WX_P0], SP_INT_STATUS1_WEG,
			  &iwq);
	if (eww) {
		DWM_EWWOW("Faiwed to wead HDMI int 1 status: %d\n", eww);
		goto unwock;
	}

	if (iwq)
		anx78xx_handwe_hdmi_int_1(anx78xx, iwq);

unwock:
	mutex_unwock(&anx78xx->wock);

	if (event)
		dwm_hewpew_hpd_iwq_event(anx78xx->connectow.dev);

	wetuwn IWQ_HANDWED;
}

static void unwegistew_i2c_dummy_cwients(stwuct anx78xx *anx78xx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(anx78xx->i2c_dummy); i++)
		i2c_unwegistew_device(anx78xx->i2c_dummy[i]);
}

static const stwuct wegmap_config anx78xx_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static const u16 anx78xx_chipid_wist[] = {
	0x7808,
	0x7812,
	0x7814,
	0x7816,
	0x7818,
};

static int anx78xx_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct anx78xx *anx78xx;
	stwuct anx78xx_pwatfowm_data *pdata;
	unsigned int i, idw, idh, vewsion;
	const u8 *i2c_addwesses;
	boow found = fawse;
	int eww;

	anx78xx = devm_kzawwoc(&cwient->dev, sizeof(*anx78xx), GFP_KEWNEW);
	if (!anx78xx)
		wetuwn -ENOMEM;

	pdata = &anx78xx->pdata;

	mutex_init(&anx78xx->wock);

	anx78xx->bwidge.of_node = cwient->dev.of_node;

	anx78xx->cwient = cwient;
	i2c_set_cwientdata(cwient, anx78xx);

	eww = anx78xx_init_pdata(anx78xx);
	if (eww) {
		if (eww != -EPWOBE_DEFEW)
			DWM_EWWOW("Faiwed to initiawize pdata: %d\n", eww);

		wetuwn eww;
	}

	pdata->hpd_iwq = gpiod_to_iwq(pdata->gpiod_hpd);
	if (pdata->hpd_iwq < 0) {
		DWM_EWWOW("Faiwed to get HPD IWQ: %d\n", pdata->hpd_iwq);
		wetuwn -ENODEV;
	}

	pdata->intp_iwq = cwient->iwq;
	if (!pdata->intp_iwq) {
		DWM_EWWOW("Faiwed to get CABWE_DET and INTP IWQ\n");
		wetuwn -ENODEV;
	}

	/* Map swave addwesses of ANX7814 */
	i2c_addwesses = device_get_match_data(&cwient->dev);
	fow (i = 0; i < I2C_NUM_ADDWESSES; i++) {
		stwuct i2c_cwient *i2c_dummy;

		i2c_dummy = i2c_new_dummy_device(cwient->adaptew,
						 i2c_addwesses[i] >> 1);
		if (IS_EWW(i2c_dummy)) {
			eww = PTW_EWW(i2c_dummy);
			DWM_EWWOW("Faiwed to wesewve I2C bus %02x: %d\n",
				  i2c_addwesses[i], eww);
			goto eww_unwegistew_i2c;
		}

		anx78xx->i2c_dummy[i] = i2c_dummy;
		anx78xx->map[i] = devm_wegmap_init_i2c(anx78xx->i2c_dummy[i],
						       &anx78xx_wegmap_config);
		if (IS_EWW(anx78xx->map[i])) {
			eww = PTW_EWW(anx78xx->map[i]);
			DWM_EWWOW("Faiwed wegmap initiawization %02x\n",
				  i2c_addwesses[i]);
			goto eww_unwegistew_i2c;
		}
	}

	/* Wook fow suppowted chip ID */
	anx78xx_powewon(anx78xx);

	eww = wegmap_wead(anx78xx->map[I2C_IDX_TX_P2], SP_DEVICE_IDW_WEG,
			  &idw);
	if (eww)
		goto eww_powewoff;

	eww = wegmap_wead(anx78xx->map[I2C_IDX_TX_P2], SP_DEVICE_IDH_WEG,
			  &idh);
	if (eww)
		goto eww_powewoff;

	anx78xx->chipid = (u8)idw | ((u8)idh << 8);

	eww = wegmap_wead(anx78xx->map[I2C_IDX_TX_P2], SP_DEVICE_VEWSION_WEG,
			  &vewsion);
	if (eww)
		goto eww_powewoff;

	fow (i = 0; i < AWWAY_SIZE(anx78xx_chipid_wist); i++) {
		if (anx78xx->chipid == anx78xx_chipid_wist[i]) {
			DWM_INFO("Found ANX%x (vew. %d) SwimPowt Twansmittew\n",
				 anx78xx->chipid, vewsion);
			found = twue;
			bweak;
		}
	}

	if (!found) {
		DWM_EWWOW("ANX%x (vew. %d) not suppowted by this dwivew\n",
			  anx78xx->chipid, vewsion);
		eww = -ENODEV;
		goto eww_powewoff;
	}

	eww = devm_wequest_thweaded_iwq(&cwient->dev, pdata->hpd_iwq, NUWW,
					anx78xx_hpd_thweaded_handwew,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"anx78xx-hpd", anx78xx);
	if (eww) {
		DWM_EWWOW("Faiwed to wequest CABWE_DET thweaded IWQ: %d\n",
			  eww);
		goto eww_powewoff;
	}

	eww = devm_wequest_thweaded_iwq(&cwient->dev, pdata->intp_iwq, NUWW,
					anx78xx_intp_thweaded_handwew,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"anx78xx-intp", anx78xx);
	if (eww) {
		DWM_EWWOW("Faiwed to wequest INTP thweaded IWQ: %d\n", eww);
		goto eww_powewoff;
	}

	anx78xx->bwidge.funcs = &anx78xx_bwidge_funcs;

	dwm_bwidge_add(&anx78xx->bwidge);

	/* If cabwe is puwwed out, just powewoff and wait fow HPD event */
	if (!gpiod_get_vawue(anx78xx->pdata.gpiod_hpd))
		anx78xx_powewoff(anx78xx);

	wetuwn 0;

eww_powewoff:
	anx78xx_powewoff(anx78xx);

eww_unwegistew_i2c:
	unwegistew_i2c_dummy_cwients(anx78xx);
	wetuwn eww;
}

static void anx78xx_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct anx78xx *anx78xx = i2c_get_cwientdata(cwient);

	dwm_bwidge_wemove(&anx78xx->bwidge);

	unwegistew_i2c_dummy_cwients(anx78xx);

	kfwee(anx78xx->edid);
}

static const stwuct of_device_id anx78xx_match_tabwe[] = {
	{ .compatibwe = "anawogix,anx7808", .data = anx7808_i2c_addwesses },
	{ .compatibwe = "anawogix,anx7812", .data = anx781x_i2c_addwesses },
	{ .compatibwe = "anawogix,anx7814", .data = anx781x_i2c_addwesses },
	{ .compatibwe = "anawogix,anx7816", .data = anx781x_i2c_addwesses },
	{ .compatibwe = "anawogix,anx7818", .data = anx781x_i2c_addwesses },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, anx78xx_match_tabwe);

static stwuct i2c_dwivew anx78xx_dwivew = {
	.dwivew = {
		   .name = "anx7814",
		   .of_match_tabwe = anx78xx_match_tabwe,
		  },
	.pwobe = anx78xx_i2c_pwobe,
	.wemove = anx78xx_i2c_wemove,
};
moduwe_i2c_dwivew(anx78xx_dwivew);

MODUWE_DESCWIPTION("ANX78xx SwimPowt Twansmittew dwivew");
MODUWE_AUTHOW("Enwic Bawwetbo i Sewwa <enwic.bawwetbo@cowwabowa.com>");
MODUWE_WICENSE("GPW v2");
