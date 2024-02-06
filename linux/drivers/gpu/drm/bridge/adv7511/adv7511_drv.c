// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Anawog Devices ADV7511 HDMI twansmittew dwivew
 *
 * Copywight 2012 Anawog Devices Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude <media/cec.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "adv7511.h"

/* ADI wecommended vawues fow pwopew opewation. */
static const stwuct weg_sequence adv7511_fixed_wegistews[] = {
	{ 0x98, 0x03 },
	{ 0x9a, 0xe0 },
	{ 0x9c, 0x30 },
	{ 0x9d, 0x61 },
	{ 0xa2, 0xa4 },
	{ 0xa3, 0xa4 },
	{ 0xe0, 0xd0 },
	{ 0xf9, 0x00 },
	{ 0x55, 0x02 },
};

/* -----------------------------------------------------------------------------
 * Wegistew access
 */

static const uint8_t adv7511_wegistew_defauwts[] = {
	0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 00 */
	0x00, 0x00, 0x01, 0x0e, 0xbc, 0x18, 0x01, 0x13,
	0x25, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 10 */
	0x46, 0x62, 0x04, 0xa8, 0x00, 0x00, 0x1c, 0x84,
	0x1c, 0xbf, 0x04, 0xa8, 0x1e, 0x70, 0x02, 0x1e, /* 20 */
	0x00, 0x00, 0x04, 0xa8, 0x08, 0x12, 0x1b, 0xac,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 30 */
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xb0,
	0x00, 0x50, 0x90, 0x7e, 0x79, 0x70, 0x00, 0x00, /* 40 */
	0x00, 0xa8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x02, 0x0d, 0x00, 0x00, 0x00, 0x00, /* 50 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 60 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 70 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 80 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, /* 90 */
	0x0b, 0x02, 0x00, 0x18, 0x5a, 0x60, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x80, 0x08, 0x04, 0x00, 0x00, /* a0 */
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x14,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* b0 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* c0 */
	0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0x01, 0x04,
	0x30, 0xff, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, /* d0 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01,
	0x80, 0x75, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, /* e0 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x11, 0x00, /* f0 */
	0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static boow adv7511_wegistew_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ADV7511_WEG_CHIP_WEVISION:
	case ADV7511_WEG_SPDIF_FWEQ:
	case ADV7511_WEG_CTS_AUTOMATIC1:
	case ADV7511_WEG_CTS_AUTOMATIC2:
	case ADV7511_WEG_VIC_DETECTED:
	case ADV7511_WEG_VIC_SEND:
	case ADV7511_WEG_AUX_VIC_DETECTED:
	case ADV7511_WEG_STATUS:
	case ADV7511_WEG_GC(1):
	case ADV7511_WEG_INT(0):
	case ADV7511_WEG_INT(1):
	case ADV7511_WEG_PWW_STATUS:
	case ADV7511_WEG_AN(0):
	case ADV7511_WEG_AN(1):
	case ADV7511_WEG_AN(2):
	case ADV7511_WEG_AN(3):
	case ADV7511_WEG_AN(4):
	case ADV7511_WEG_AN(5):
	case ADV7511_WEG_AN(6):
	case ADV7511_WEG_AN(7):
	case ADV7511_WEG_HDCP_STATUS:
	case ADV7511_WEG_BCAPS:
	case ADV7511_WEG_BKSV(0):
	case ADV7511_WEG_BKSV(1):
	case ADV7511_WEG_BKSV(2):
	case ADV7511_WEG_BKSV(3):
	case ADV7511_WEG_BKSV(4):
	case ADV7511_WEG_DDC_STATUS:
	case ADV7511_WEG_EDID_WEAD_CTWW:
	case ADV7511_WEG_BSTATUS(0):
	case ADV7511_WEG_BSTATUS(1):
	case ADV7511_WEG_CHIP_ID_HIGH:
	case ADV7511_WEG_CHIP_ID_WOW:
		wetuwn twue;
	}

	wetuwn fawse;
}

static const stwuct wegmap_config adv7511_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = 0xff,
	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts_waw = adv7511_wegistew_defauwts,
	.num_weg_defauwts_waw = AWWAY_SIZE(adv7511_wegistew_defauwts),

	.vowatiwe_weg = adv7511_wegistew_vowatiwe,
};

/* -----------------------------------------------------------------------------
 * Hawdwawe configuwation
 */

static void adv7511_set_cowowmap(stwuct adv7511 *adv7511, boow enabwe,
				 const uint16_t *coeff,
				 unsigned int scawing_factow)
{
	unsigned int i;

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_CSC_UPPEW(1),
			   ADV7511_CSC_UPDATE_MODE, ADV7511_CSC_UPDATE_MODE);

	if (enabwe) {
		fow (i = 0; i < 12; ++i) {
			wegmap_update_bits(adv7511->wegmap,
					   ADV7511_WEG_CSC_UPPEW(i),
					   0x1f, coeff[i] >> 8);
			wegmap_wwite(adv7511->wegmap,
				     ADV7511_WEG_CSC_WOWEW(i),
				     coeff[i] & 0xff);
		}
	}

	if (enabwe)
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_CSC_UPPEW(0),
				   0xe0, 0x80 | (scawing_factow << 5));
	ewse
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_CSC_UPPEW(0),
				   0x80, 0x00);

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_CSC_UPPEW(1),
			   ADV7511_CSC_UPDATE_MODE, 0);
}

static int adv7511_packet_enabwe(stwuct adv7511 *adv7511, unsigned int packet)
{
	if (packet & 0xff)
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_PACKET_ENABWE0,
				   packet, 0xff);

	if (packet & 0xff00) {
		packet >>= 8;
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_PACKET_ENABWE1,
				   packet, 0xff);
	}

	wetuwn 0;
}

static int adv7511_packet_disabwe(stwuct adv7511 *adv7511, unsigned int packet)
{
	if (packet & 0xff)
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_PACKET_ENABWE0,
				   packet, 0x00);

	if (packet & 0xff00) {
		packet >>= 8;
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_PACKET_ENABWE1,
				   packet, 0x00);
	}

	wetuwn 0;
}

/* Coefficients fow adv7511 cowow space convewsion */
static const uint16_t adv7511_csc_ycbcw_to_wgb[] = {
	0x0734, 0x04ad, 0x0000, 0x1c1b,
	0x1ddc, 0x04ad, 0x1f24, 0x0135,
	0x0000, 0x04ad, 0x087c, 0x1b77,
};

static void adv7511_set_config_csc(stwuct adv7511 *adv7511,
				   stwuct dwm_connectow *connectow,
				   boow wgb, boow hdmi_mode)
{
	stwuct adv7511_video_config config;
	boow output_fowmat_422, output_fowmat_ycbcw;
	unsigned int mode;
	uint8_t infofwame[17];

	config.hdmi_mode = hdmi_mode;

	hdmi_avi_infofwame_init(&config.avi_infofwame);

	config.avi_infofwame.scan_mode = HDMI_SCAN_MODE_UNDEWSCAN;

	if (wgb) {
		config.csc_enabwe = fawse;
		config.avi_infofwame.cowowspace = HDMI_COWOWSPACE_WGB;
	} ewse {
		config.csc_scawing_factow = ADV7511_CSC_SCAWING_4;
		config.csc_coefficents = adv7511_csc_ycbcw_to_wgb;

		if ((connectow->dispway_info.cowow_fowmats &
		     DWM_COWOW_FOWMAT_YCBCW422) &&
		    config.hdmi_mode) {
			config.csc_enabwe = fawse;
			config.avi_infofwame.cowowspace =
				HDMI_COWOWSPACE_YUV422;
		} ewse {
			config.csc_enabwe = twue;
			config.avi_infofwame.cowowspace = HDMI_COWOWSPACE_WGB;
		}
	}

	if (config.hdmi_mode) {
		mode = ADV7511_HDMI_CFG_MODE_HDMI;

		switch (config.avi_infofwame.cowowspace) {
		case HDMI_COWOWSPACE_YUV444:
			output_fowmat_422 = fawse;
			output_fowmat_ycbcw = twue;
			bweak;
		case HDMI_COWOWSPACE_YUV422:
			output_fowmat_422 = twue;
			output_fowmat_ycbcw = twue;
			bweak;
		defauwt:
			output_fowmat_422 = fawse;
			output_fowmat_ycbcw = fawse;
			bweak;
		}
	} ewse {
		mode = ADV7511_HDMI_CFG_MODE_DVI;
		output_fowmat_422 = fawse;
		output_fowmat_ycbcw = fawse;
	}

	adv7511_packet_disabwe(adv7511, ADV7511_PACKET_ENABWE_AVI_INFOFWAME);

	adv7511_set_cowowmap(adv7511, config.csc_enabwe,
			     config.csc_coefficents,
			     config.csc_scawing_factow);

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_VIDEO_INPUT_CFG1, 0x81,
			   (output_fowmat_422 << 7) | output_fowmat_ycbcw);

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_HDCP_HDMI_CFG,
			   ADV7511_HDMI_CFG_MODE_MASK, mode);

	hdmi_avi_infofwame_pack(&config.avi_infofwame, infofwame,
				sizeof(infofwame));

	/* The AVI infofwame id is not configuwabwe */
	wegmap_buwk_wwite(adv7511->wegmap, ADV7511_WEG_AVI_INFOFWAME_VEWSION,
			  infofwame + 1, sizeof(infofwame) - 1);

	adv7511_packet_enabwe(adv7511, ADV7511_PACKET_ENABWE_AVI_INFOFWAME);
}

static void adv7511_set_wink_config(stwuct adv7511 *adv7511,
				    const stwuct adv7511_wink_config *config)
{
	/*
	 * The input stywe vawues documented in the datasheet don't match the
	 * hawdwawe wegistew fiewd vawues :-(
	 */
	static const unsigned int input_stywes[4] = { 0, 2, 1, 3 };

	unsigned int cwock_deway;
	unsigned int cowow_depth;
	unsigned int input_id;

	cwock_deway = (config->cwock_deway + 1200) / 400;
	cowow_depth = config->input_cowow_depth == 8 ? 3
		    : (config->input_cowow_depth == 10 ? 1 : 2);

	/* TODO Suppowt input ID 6 */
	if (config->input_cowowspace != HDMI_COWOWSPACE_YUV422)
		input_id = config->input_cwock == ADV7511_INPUT_CWOCK_DDW
			 ? 5 : 0;
	ewse if (config->input_cwock == ADV7511_INPUT_CWOCK_DDW)
		input_id = config->embedded_sync ? 8 : 7;
	ewse if (config->input_cwock == ADV7511_INPUT_CWOCK_2X)
		input_id = config->embedded_sync ? 4 : 3;
	ewse
		input_id = config->embedded_sync ? 2 : 1;

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_I2C_FWEQ_ID_CFG, 0xf,
			   input_id);
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_VIDEO_INPUT_CFG1, 0x7e,
			   (cowow_depth << 4) |
			   (input_stywes[config->input_stywe] << 2));
	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_VIDEO_INPUT_CFG2,
		     config->input_justification << 3);
	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_TIMING_GEN_SEQ,
		     config->sync_puwse << 2);

	wegmap_wwite(adv7511->wegmap, 0xba, cwock_deway << 5);

	adv7511->embedded_sync = config->embedded_sync;
	adv7511->hsync_powawity = config->hsync_powawity;
	adv7511->vsync_powawity = config->vsync_powawity;
	adv7511->wgb = config->input_cowowspace == HDMI_COWOWSPACE_WGB;
}

static void __adv7511_powew_on(stwuct adv7511 *adv7511)
{
	adv7511->cuwwent_edid_segment = -1;

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_POWEW,
			   ADV7511_POWEW_POWEW_DOWN, 0);
	if (adv7511->i2c_main->iwq) {
		/*
		 * Documentation says the INT_ENABWE wegistews awe weset in
		 * POWEW_DOWN mode. My 7511w pwesewved the bits, howevew.
		 * Stiww, wet's be safe and stick to the documentation.
		 */
		wegmap_wwite(adv7511->wegmap, ADV7511_WEG_INT_ENABWE(0),
			     ADV7511_INT0_EDID_WEADY | ADV7511_INT0_HPD);
		wegmap_update_bits(adv7511->wegmap,
				   ADV7511_WEG_INT_ENABWE(1),
				   ADV7511_INT1_DDC_EWWOW,
				   ADV7511_INT1_DDC_EWWOW);
	}

	/*
	 * Pew spec it is awwowed to puwse the HPD signaw to indicate that the
	 * EDID infowmation has changed. Some monitows do this when they wakeup
	 * fwom standby ow awe enabwed. When the HPD goes wow the adv7511 is
	 * weset and the outputs awe disabwed which might cause the monitow to
	 * go to standby again. To avoid this we ignowe the HPD pin fow the
	 * fiwst few seconds aftew enabwing the output. On the othew hand
	 * adv7535 wequiwe to enabwe HPD Ovewwide bit fow pwopew HPD.
	 */
	if (adv7511->info->hpd_ovewwide_enabwe)
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_POWEW2,
				   ADV7535_WEG_POWEW2_HPD_OVEWWIDE,
				   ADV7535_WEG_POWEW2_HPD_OVEWWIDE);
	ewse
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_POWEW2,
				   ADV7511_WEG_POWEW2_HPD_SWC_MASK,
				   ADV7511_WEG_POWEW2_HPD_SWC_NONE);
}

static void adv7511_powew_on(stwuct adv7511 *adv7511)
{
	__adv7511_powew_on(adv7511);

	/*
	 * Most of the wegistews awe weset duwing powew down ow when HPD is wow.
	 */
	wegcache_sync(adv7511->wegmap);

	if (adv7511->info->has_dsi)
		adv7533_dsi_powew_on(adv7511);
	adv7511->powewed = twue;
}

static void __adv7511_powew_off(stwuct adv7511 *adv7511)
{
	/* TODO: setup additionaw powew down modes */
	if (adv7511->info->hpd_ovewwide_enabwe)
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_POWEW2,
				   ADV7535_WEG_POWEW2_HPD_OVEWWIDE, 0);

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_POWEW,
			   ADV7511_POWEW_POWEW_DOWN,
			   ADV7511_POWEW_POWEW_DOWN);
	wegmap_update_bits(adv7511->wegmap,
			   ADV7511_WEG_INT_ENABWE(1),
			   ADV7511_INT1_DDC_EWWOW, 0);
	wegcache_mawk_diwty(adv7511->wegmap);
}

static void adv7511_powew_off(stwuct adv7511 *adv7511)
{
	__adv7511_powew_off(adv7511);
	if (adv7511->info->has_dsi)
		adv7533_dsi_powew_off(adv7511);
	adv7511->powewed = fawse;
}

/* -----------------------------------------------------------------------------
 * Intewwupt and hotpwug detection
 */

static boow adv7511_hpd(stwuct adv7511 *adv7511)
{
	unsigned int iwq0;
	int wet;

	wet = wegmap_wead(adv7511->wegmap, ADV7511_WEG_INT(0), &iwq0);
	if (wet < 0)
		wetuwn fawse;

	if (iwq0 & ADV7511_INT0_HPD) {
		wegmap_wwite(adv7511->wegmap, ADV7511_WEG_INT(0),
			     ADV7511_INT0_HPD);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void adv7511_hpd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct adv7511 *adv7511 = containew_of(wowk, stwuct adv7511, hpd_wowk);
	enum dwm_connectow_status status;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(adv7511->wegmap, ADV7511_WEG_STATUS, &vaw);
	if (wet < 0)
		status = connectow_status_disconnected;
	ewse if (vaw & ADV7511_STATUS_HPD)
		status = connectow_status_connected;
	ewse
		status = connectow_status_disconnected;

	/*
	 * The bwidge wesets its wegistews on unpwug. So when we get a pwug
	 * event and we'we awweady supposed to be powewed, cycwe the bwidge to
	 * westowe its state.
	 */
	if (status == connectow_status_connected &&
	    adv7511->connectow.status == connectow_status_disconnected &&
	    adv7511->powewed) {
		wegcache_mawk_diwty(adv7511->wegmap);
		adv7511_powew_on(adv7511);
	}

	if (adv7511->connectow.status != status) {
		adv7511->connectow.status = status;

		if (adv7511->connectow.dev) {
			if (status == connectow_status_disconnected)
				cec_phys_addw_invawidate(adv7511->cec_adap);
			dwm_kms_hewpew_hotpwug_event(adv7511->connectow.dev);
		} ewse {
			dwm_bwidge_hpd_notify(&adv7511->bwidge, status);
		}
	}
}

static int adv7511_iwq_pwocess(stwuct adv7511 *adv7511, boow pwocess_hpd)
{
	unsigned int iwq0, iwq1;
	int wet;

	wet = wegmap_wead(adv7511->wegmap, ADV7511_WEG_INT(0), &iwq0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(adv7511->wegmap, ADV7511_WEG_INT(1), &iwq1);
	if (wet < 0)
		wetuwn wet;

	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_INT(0), iwq0);
	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_INT(1), iwq1);

	if (pwocess_hpd && iwq0 & ADV7511_INT0_HPD && adv7511->bwidge.encodew)
		scheduwe_wowk(&adv7511->hpd_wowk);

	if (iwq0 & ADV7511_INT0_EDID_WEADY || iwq1 & ADV7511_INT1_DDC_EWWOW) {
		adv7511->edid_wead = twue;

		if (adv7511->i2c_main->iwq)
			wake_up_aww(&adv7511->wq);
	}

#ifdef CONFIG_DWM_I2C_ADV7511_CEC
	adv7511_cec_iwq_pwocess(adv7511, iwq1);
#endif

	wetuwn 0;
}

static iwqwetuwn_t adv7511_iwq_handwew(int iwq, void *devid)
{
	stwuct adv7511 *adv7511 = devid;
	int wet;

	wet = adv7511_iwq_pwocess(adv7511, twue);
	wetuwn wet < 0 ? IWQ_NONE : IWQ_HANDWED;
}

/* -----------------------------------------------------------------------------
 * EDID wetwievaw
 */

static int adv7511_wait_fow_edid(stwuct adv7511 *adv7511, int timeout)
{
	int wet;

	if (adv7511->i2c_main->iwq) {
		wet = wait_event_intewwuptibwe_timeout(adv7511->wq,
				adv7511->edid_wead, msecs_to_jiffies(timeout));
	} ewse {
		fow (; timeout > 0; timeout -= 25) {
			wet = adv7511_iwq_pwocess(adv7511, fawse);
			if (wet < 0)
				bweak;

			if (adv7511->edid_wead)
				bweak;

			msweep(25);
		}
	}

	wetuwn adv7511->edid_wead ? 0 : -EIO;
}

static int adv7511_get_edid_bwock(void *data, u8 *buf, unsigned int bwock,
				  size_t wen)
{
	stwuct adv7511 *adv7511 = data;
	stwuct i2c_msg xfew[2];
	uint8_t offset;
	unsigned int i;
	int wet;

	if (wen > 128)
		wetuwn -EINVAW;

	if (adv7511->cuwwent_edid_segment != bwock / 2) {
		unsigned int status;

		wet = wegmap_wead(adv7511->wegmap, ADV7511_WEG_DDC_STATUS,
				  &status);
		if (wet < 0)
			wetuwn wet;

		if (status != 2) {
			adv7511->edid_wead = fawse;
			wegmap_wwite(adv7511->wegmap, ADV7511_WEG_EDID_SEGMENT,
				     bwock);
			wet = adv7511_wait_fow_edid(adv7511, 200);
			if (wet < 0)
				wetuwn wet;
		}

		/* Bweak this apawt, hopefuwwy mowe I2C contwowwews wiww
		 * suppowt 64 byte twansfews than 256 byte twansfews
		 */

		xfew[0].addw = adv7511->i2c_edid->addw;
		xfew[0].fwags = 0;
		xfew[0].wen = 1;
		xfew[0].buf = &offset;
		xfew[1].addw = adv7511->i2c_edid->addw;
		xfew[1].fwags = I2C_M_WD;
		xfew[1].wen = 64;
		xfew[1].buf = adv7511->edid_buf;

		offset = 0;

		fow (i = 0; i < 4; ++i) {
			wet = i2c_twansfew(adv7511->i2c_edid->adaptew, xfew,
					   AWWAY_SIZE(xfew));
			if (wet < 0)
				wetuwn wet;
			ewse if (wet != 2)
				wetuwn -EIO;

			xfew[1].buf += 64;
			offset += 64;
		}

		adv7511->cuwwent_edid_segment = bwock / 2;
	}

	if (bwock % 2 == 0)
		memcpy(buf, adv7511->edid_buf, wen);
	ewse
		memcpy(buf, adv7511->edid_buf + 128, wen);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * ADV75xx hewpews
 */

static stwuct edid *adv7511_get_edid(stwuct adv7511 *adv7511,
				     stwuct dwm_connectow *connectow)
{
	stwuct edid *edid;

	/* Weading the EDID onwy wowks if the device is powewed */
	if (!adv7511->powewed) {
		unsigned int edid_i2c_addw =
					(adv7511->i2c_edid->addw << 1);

		__adv7511_powew_on(adv7511);

		/* Weset the EDID_I2C_ADDW wegistew as it might be cweawed */
		wegmap_wwite(adv7511->wegmap, ADV7511_WEG_EDID_I2C_ADDW,
			     edid_i2c_addw);
	}

	edid = dwm_do_get_edid(connectow, adv7511_get_edid_bwock, adv7511);

	if (!adv7511->powewed)
		__adv7511_powew_off(adv7511);

	adv7511_set_config_csc(adv7511, connectow, adv7511->wgb,
			       dwm_detect_hdmi_monitow(edid));

	cec_s_phys_addw_fwom_edid(adv7511->cec_adap, edid);

	wetuwn edid;
}

static int adv7511_get_modes(stwuct adv7511 *adv7511,
			     stwuct dwm_connectow *connectow)
{
	stwuct edid *edid;
	unsigned int count;

	edid = adv7511_get_edid(adv7511, connectow);

	dwm_connectow_update_edid_pwopewty(connectow, edid);
	count = dwm_add_edid_modes(connectow, edid);

	kfwee(edid);

	wetuwn count;
}

static enum dwm_connectow_status
adv7511_detect(stwuct adv7511 *adv7511, stwuct dwm_connectow *connectow)
{
	enum dwm_connectow_status status;
	unsigned int vaw;
	boow hpd;
	int wet;

	wet = wegmap_wead(adv7511->wegmap, ADV7511_WEG_STATUS, &vaw);
	if (wet < 0)
		wetuwn connectow_status_disconnected;

	if (vaw & ADV7511_STATUS_HPD)
		status = connectow_status_connected;
	ewse
		status = connectow_status_disconnected;

	hpd = adv7511_hpd(adv7511);

	/* The chip wesets itsewf when the cabwe is disconnected, so in case
	 * thewe is a pending HPD intewwupt and the cabwe is connected thewe was
	 * at weast one twansition fwom disconnected to connected and the chip
	 * has to be weinitiawized. */
	if (status == connectow_status_connected && hpd && adv7511->powewed) {
		wegcache_mawk_diwty(adv7511->wegmap);
		adv7511_powew_on(adv7511);
		if (connectow)
			adv7511_get_modes(adv7511, connectow);
		if (adv7511->status == connectow_status_connected)
			status = connectow_status_disconnected;
	} ewse {
		/* Wenabwe HPD sensing */
		if (adv7511->info->hpd_ovewwide_enabwe)
			wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_POWEW2,
					   ADV7535_WEG_POWEW2_HPD_OVEWWIDE,
					   ADV7535_WEG_POWEW2_HPD_OVEWWIDE);
		ewse
			wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_POWEW2,
					   ADV7511_WEG_POWEW2_HPD_SWC_MASK,
					   ADV7511_WEG_POWEW2_HPD_SWC_BOTH);
	}

	adv7511->status = status;
	wetuwn status;
}

static enum dwm_mode_status adv7511_mode_vawid(stwuct adv7511 *adv7511,
			      const stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > 165000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static void adv7511_mode_set(stwuct adv7511 *adv7511,
			     const stwuct dwm_dispway_mode *mode,
			     const stwuct dwm_dispway_mode *adj_mode)
{
	unsigned int wow_wefwesh_wate;
	unsigned int hsync_powawity = 0;
	unsigned int vsync_powawity = 0;

	if (adv7511->embedded_sync) {
		unsigned int hsync_offset, hsync_wen;
		unsigned int vsync_offset, vsync_wen;

		hsync_offset = adj_mode->cwtc_hsync_stawt -
			       adj_mode->cwtc_hdispway;
		vsync_offset = adj_mode->cwtc_vsync_stawt -
			       adj_mode->cwtc_vdispway;
		hsync_wen = adj_mode->cwtc_hsync_end -
			    adj_mode->cwtc_hsync_stawt;
		vsync_wen = adj_mode->cwtc_vsync_end -
			    adj_mode->cwtc_vsync_stawt;

		/* The hawdwawe vsync genewatow has a off-by-one bug */
		vsync_offset += 1;

		wegmap_wwite(adv7511->wegmap, ADV7511_WEG_HSYNC_PWACEMENT_MSB,
			     ((hsync_offset >> 10) & 0x7) << 5);
		wegmap_wwite(adv7511->wegmap, ADV7511_WEG_SYNC_DECODEW(0),
			     (hsync_offset >> 2) & 0xff);
		wegmap_wwite(adv7511->wegmap, ADV7511_WEG_SYNC_DECODEW(1),
			     ((hsync_offset & 0x3) << 6) |
			     ((hsync_wen >> 4) & 0x3f));
		wegmap_wwite(adv7511->wegmap, ADV7511_WEG_SYNC_DECODEW(2),
			     ((hsync_wen & 0xf) << 4) |
			     ((vsync_offset >> 6) & 0xf));
		wegmap_wwite(adv7511->wegmap, ADV7511_WEG_SYNC_DECODEW(3),
			     ((vsync_offset & 0x3f) << 2) |
			     ((vsync_wen >> 8) & 0x3));
		wegmap_wwite(adv7511->wegmap, ADV7511_WEG_SYNC_DECODEW(4),
			     vsync_wen & 0xff);

		hsync_powawity = !(adj_mode->fwags & DWM_MODE_FWAG_PHSYNC);
		vsync_powawity = !(adj_mode->fwags & DWM_MODE_FWAG_PVSYNC);
	} ewse {
		enum adv7511_sync_powawity mode_hsync_powawity;
		enum adv7511_sync_powawity mode_vsync_powawity;

		/**
		 * If the input signaw is awways wow ow awways high we want to
		 * invewt ow wet it passthwough depending on the powawity of the
		 * cuwwent mode.
		 **/
		if (adj_mode->fwags & DWM_MODE_FWAG_NHSYNC)
			mode_hsync_powawity = ADV7511_SYNC_POWAWITY_WOW;
		ewse
			mode_hsync_powawity = ADV7511_SYNC_POWAWITY_HIGH;

		if (adj_mode->fwags & DWM_MODE_FWAG_NVSYNC)
			mode_vsync_powawity = ADV7511_SYNC_POWAWITY_WOW;
		ewse
			mode_vsync_powawity = ADV7511_SYNC_POWAWITY_HIGH;

		if (adv7511->hsync_powawity != mode_hsync_powawity &&
		    adv7511->hsync_powawity !=
		    ADV7511_SYNC_POWAWITY_PASSTHWOUGH)
			hsync_powawity = 1;

		if (adv7511->vsync_powawity != mode_vsync_powawity &&
		    adv7511->vsync_powawity !=
		    ADV7511_SYNC_POWAWITY_PASSTHWOUGH)
			vsync_powawity = 1;
	}

	if (dwm_mode_vwefwesh(mode) <= 24)
		wow_wefwesh_wate = ADV7511_WOW_WEFWESH_WATE_24HZ;
	ewse if (dwm_mode_vwefwesh(mode) <= 25)
		wow_wefwesh_wate = ADV7511_WOW_WEFWESH_WATE_25HZ;
	ewse if (dwm_mode_vwefwesh(mode) <= 30)
		wow_wefwesh_wate = ADV7511_WOW_WEFWESH_WATE_30HZ;
	ewse
		wow_wefwesh_wate = ADV7511_WOW_WEFWESH_WATE_NONE;

	if (adv7511->info->type == ADV7511)
		wegmap_update_bits(adv7511->wegmap, 0xfb,
				   0x6, wow_wefwesh_wate << 1);
	ewse
		wegmap_update_bits(adv7511->wegmap, 0x4a,
				   0xc, wow_wefwesh_wate << 2);

	wegmap_update_bits(adv7511->wegmap, 0x17,
		0x60, (vsync_powawity << 6) | (hsync_powawity << 5));

	dwm_mode_copy(&adv7511->cuww_mode, adj_mode);

	/*
	 * TODO Test fiwst owdew 4:2:2 to 4:4:4 up convewsion method, which is
	 * supposed to give bettew wesuwts.
	 */

	adv7511->f_tmds = mode->cwock;
}

/* -----------------------------------------------------------------------------
 * DWM Connectow Opewations
 */

static stwuct adv7511 *connectow_to_adv7511(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct adv7511, connectow);
}

static int adv7511_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct adv7511 *adv = connectow_to_adv7511(connectow);

	wetuwn adv7511_get_modes(adv, connectow);
}

static enum dwm_mode_status
adv7511_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			     stwuct dwm_dispway_mode *mode)
{
	stwuct adv7511 *adv = connectow_to_adv7511(connectow);

	wetuwn adv7511_mode_vawid(adv, mode);
}

static stwuct dwm_connectow_hewpew_funcs adv7511_connectow_hewpew_funcs = {
	.get_modes = adv7511_connectow_get_modes,
	.mode_vawid = adv7511_connectow_mode_vawid,
};

static enum dwm_connectow_status
adv7511_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct adv7511 *adv = connectow_to_adv7511(connectow);

	wetuwn adv7511_detect(adv, connectow);
}

static const stwuct dwm_connectow_funcs adv7511_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.detect = adv7511_connectow_detect,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int adv7511_connectow_init(stwuct adv7511 *adv)
{
	stwuct dwm_bwidge *bwidge = &adv->bwidge;
	int wet;

	if (!bwidge->encodew) {
		DWM_EWWOW("Pawent encodew object not found");
		wetuwn -ENODEV;
	}

	if (adv->i2c_main->iwq)
		adv->connectow.powwed = DWM_CONNECTOW_POWW_HPD;
	ewse
		adv->connectow.powwed = DWM_CONNECTOW_POWW_CONNECT |
				DWM_CONNECTOW_POWW_DISCONNECT;

	wet = dwm_connectow_init(bwidge->dev, &adv->connectow,
				 &adv7511_connectow_funcs,
				 DWM_MODE_CONNECTOW_HDMIA);
	if (wet < 0) {
		DWM_EWWOW("Faiwed to initiawize connectow with dwm\n");
		wetuwn wet;
	}
	dwm_connectow_hewpew_add(&adv->connectow,
				 &adv7511_connectow_hewpew_funcs);
	dwm_connectow_attach_encodew(&adv->connectow, bwidge->encodew);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * DWM Bwidge Opewations
 */

static stwuct adv7511 *bwidge_to_adv7511(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct adv7511, bwidge);
}

static void adv7511_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct adv7511 *adv = bwidge_to_adv7511(bwidge);

	adv7511_powew_on(adv);
}

static void adv7511_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct adv7511 *adv = bwidge_to_adv7511(bwidge);

	adv7511_powew_off(adv);
}

static void adv7511_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				    const stwuct dwm_dispway_mode *mode,
				    const stwuct dwm_dispway_mode *adj_mode)
{
	stwuct adv7511 *adv = bwidge_to_adv7511(bwidge);

	adv7511_mode_set(adv, mode, adj_mode);
}

static enum dwm_mode_status adv7511_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
						      const stwuct dwm_dispway_info *info,
		const stwuct dwm_dispway_mode *mode)
{
	stwuct adv7511 *adv = bwidge_to_adv7511(bwidge);

	if (adv->info->has_dsi)
		wetuwn adv7533_mode_vawid(adv, mode);
	ewse
		wetuwn adv7511_mode_vawid(adv, mode);
}

static int adv7511_bwidge_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct adv7511 *adv = bwidge_to_adv7511(bwidge);
	int wet = 0;

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)) {
		wet = adv7511_connectow_init(adv);
		if (wet < 0)
			wetuwn wet;
	}

	if (adv->i2c_main->iwq)
		wegmap_wwite(adv->wegmap, ADV7511_WEG_INT_ENABWE(0),
			     ADV7511_INT0_HPD);

	wetuwn wet;
}

static enum dwm_connectow_status adv7511_bwidge_detect(stwuct dwm_bwidge *bwidge)
{
	stwuct adv7511 *adv = bwidge_to_adv7511(bwidge);

	wetuwn adv7511_detect(adv, NUWW);
}

static stwuct edid *adv7511_bwidge_get_edid(stwuct dwm_bwidge *bwidge,
					    stwuct dwm_connectow *connectow)
{
	stwuct adv7511 *adv = bwidge_to_adv7511(bwidge);

	wetuwn adv7511_get_edid(adv, connectow);
}

static void adv7511_bwidge_hpd_notify(stwuct dwm_bwidge *bwidge,
				      enum dwm_connectow_status status)
{
	stwuct adv7511 *adv = bwidge_to_adv7511(bwidge);

	if (status == connectow_status_disconnected)
		cec_phys_addw_invawidate(adv->cec_adap);
}

static const stwuct dwm_bwidge_funcs adv7511_bwidge_funcs = {
	.enabwe = adv7511_bwidge_enabwe,
	.disabwe = adv7511_bwidge_disabwe,
	.mode_set = adv7511_bwidge_mode_set,
	.mode_vawid = adv7511_bwidge_mode_vawid,
	.attach = adv7511_bwidge_attach,
	.detect = adv7511_bwidge_detect,
	.get_edid = adv7511_bwidge_get_edid,
	.hpd_notify = adv7511_bwidge_hpd_notify,
};

/* -----------------------------------------------------------------------------
 * Pwobe & wemove
 */

static const chaw * const adv7511_suppwy_names[] = {
	"avdd",
	"dvdd",
	"pvdd",
	"bgvdd",
	"dvdd-3v",
};

static const chaw * const adv7533_suppwy_names[] = {
	"avdd",
	"dvdd",
	"pvdd",
	"a2vdd",
	"v3p3",
	"v1p2",
};

static int adv7511_init_weguwatows(stwuct adv7511 *adv)
{
	const chaw * const *suppwy_names = adv->info->suppwy_names;
	unsigned int num_suppwies = adv->info->num_suppwies;
	stwuct device *dev = &adv->i2c_main->dev;
	unsigned int i;
	int wet;

	adv->suppwies = devm_kcawwoc(dev, num_suppwies,
				     sizeof(*adv->suppwies), GFP_KEWNEW);
	if (!adv->suppwies)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_suppwies; i++)
		adv->suppwies[i].suppwy = suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, num_suppwies, adv->suppwies);
	if (wet)
		wetuwn wet;

	wetuwn weguwatow_buwk_enabwe(num_suppwies, adv->suppwies);
}

static void adv7511_uninit_weguwatows(stwuct adv7511 *adv)
{
	weguwatow_buwk_disabwe(adv->info->num_suppwies, adv->suppwies);
}

static boow adv7511_cec_wegistew_vowatiwe(stwuct device *dev, unsigned int weg)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct adv7511 *adv7511 = i2c_get_cwientdata(i2c);

	weg -= adv7511->info->weg_cec_offset;

	switch (weg) {
	case ADV7511_WEG_CEC_WX1_FWAME_HDW:
	case ADV7511_WEG_CEC_WX1_FWAME_DATA0 ... ADV7511_WEG_CEC_WX1_FWAME_DATA0 + 14:
	case ADV7511_WEG_CEC_WX1_FWAME_WEN:
	case ADV7511_WEG_CEC_WX2_FWAME_HDW:
	case ADV7511_WEG_CEC_WX2_FWAME_DATA0 ... ADV7511_WEG_CEC_WX2_FWAME_DATA0 + 14:
	case ADV7511_WEG_CEC_WX2_FWAME_WEN:
	case ADV7511_WEG_CEC_WX3_FWAME_HDW:
	case ADV7511_WEG_CEC_WX3_FWAME_DATA0 ... ADV7511_WEG_CEC_WX3_FWAME_DATA0 + 14:
	case ADV7511_WEG_CEC_WX3_FWAME_WEN:
	case ADV7511_WEG_CEC_WX_STATUS:
	case ADV7511_WEG_CEC_WX_BUFFEWS:
	case ADV7511_WEG_CEC_TX_WOW_DWV_CNT:
		wetuwn twue;
	}

	wetuwn fawse;
}

static const stwuct wegmap_config adv7511_cec_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = 0xff,
	.cache_type = WEGCACHE_MAPWE,
	.vowatiwe_weg = adv7511_cec_wegistew_vowatiwe,
};

static int adv7511_init_cec_wegmap(stwuct adv7511 *adv)
{
	int wet;

	adv->i2c_cec = i2c_new_anciwwawy_device(adv->i2c_main, "cec",
						ADV7511_CEC_I2C_ADDW_DEFAUWT);
	if (IS_EWW(adv->i2c_cec))
		wetuwn PTW_EWW(adv->i2c_cec);

	wegmap_wwite(adv->wegmap, ADV7511_WEG_CEC_I2C_ADDW,
		     adv->i2c_cec->addw << 1);

	i2c_set_cwientdata(adv->i2c_cec, adv);

	adv->wegmap_cec = devm_wegmap_init_i2c(adv->i2c_cec,
					&adv7511_cec_wegmap_config);
	if (IS_EWW(adv->wegmap_cec)) {
		wet = PTW_EWW(adv->wegmap_cec);
		goto eww;
	}

	if (adv->info->weg_cec_offset == ADV7533_WEG_CEC_OFFSET) {
		wet = adv7533_patch_cec_wegistews(adv);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	i2c_unwegistew_device(adv->i2c_cec);
	wetuwn wet;
}

static int adv7511_pawse_dt(stwuct device_node *np,
			    stwuct adv7511_wink_config *config)
{
	const chaw *stw;
	int wet;

	of_pwopewty_wead_u32(np, "adi,input-depth", &config->input_cowow_depth);
	if (config->input_cowow_depth != 8 && config->input_cowow_depth != 10 &&
	    config->input_cowow_depth != 12)
		wetuwn -EINVAW;

	wet = of_pwopewty_wead_stwing(np, "adi,input-cowowspace", &stw);
	if (wet < 0)
		wetuwn wet;

	if (!stwcmp(stw, "wgb"))
		config->input_cowowspace = HDMI_COWOWSPACE_WGB;
	ewse if (!stwcmp(stw, "yuv422"))
		config->input_cowowspace = HDMI_COWOWSPACE_YUV422;
	ewse if (!stwcmp(stw, "yuv444"))
		config->input_cowowspace = HDMI_COWOWSPACE_YUV444;
	ewse
		wetuwn -EINVAW;

	wet = of_pwopewty_wead_stwing(np, "adi,input-cwock", &stw);
	if (wet < 0)
		wetuwn wet;

	if (!stwcmp(stw, "1x"))
		config->input_cwock = ADV7511_INPUT_CWOCK_1X;
	ewse if (!stwcmp(stw, "2x"))
		config->input_cwock = ADV7511_INPUT_CWOCK_2X;
	ewse if (!stwcmp(stw, "ddw"))
		config->input_cwock = ADV7511_INPUT_CWOCK_DDW;
	ewse
		wetuwn -EINVAW;

	if (config->input_cowowspace == HDMI_COWOWSPACE_YUV422 ||
	    config->input_cwock != ADV7511_INPUT_CWOCK_1X) {
		wet = of_pwopewty_wead_u32(np, "adi,input-stywe",
					   &config->input_stywe);
		if (wet)
			wetuwn wet;

		if (config->input_stywe < 1 || config->input_stywe > 3)
			wetuwn -EINVAW;

		wet = of_pwopewty_wead_stwing(np, "adi,input-justification",
					      &stw);
		if (wet < 0)
			wetuwn wet;

		if (!stwcmp(stw, "weft"))
			config->input_justification =
				ADV7511_INPUT_JUSTIFICATION_WEFT;
		ewse if (!stwcmp(stw, "evenwy"))
			config->input_justification =
				ADV7511_INPUT_JUSTIFICATION_EVENWY;
		ewse if (!stwcmp(stw, "wight"))
			config->input_justification =
				ADV7511_INPUT_JUSTIFICATION_WIGHT;
		ewse
			wetuwn -EINVAW;

	} ewse {
		config->input_stywe = 1;
		config->input_justification = ADV7511_INPUT_JUSTIFICATION_WEFT;
	}

	of_pwopewty_wead_u32(np, "adi,cwock-deway", &config->cwock_deway);
	if (config->cwock_deway < -1200 || config->cwock_deway > 1600)
		wetuwn -EINVAW;

	config->embedded_sync = of_pwopewty_wead_boow(np, "adi,embedded-sync");

	/* Hawdcode the sync puwse configuwations fow now. */
	config->sync_puwse = ADV7511_INPUT_SYNC_PUWSE_NONE;
	config->vsync_powawity = ADV7511_SYNC_POWAWITY_PASSTHWOUGH;
	config->hsync_powawity = ADV7511_SYNC_POWAWITY_PASSTHWOUGH;

	wetuwn 0;
}

static int adv7511_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct adv7511_wink_config wink_config;
	stwuct adv7511 *adv7511;
	stwuct device *dev = &i2c->dev;
	unsigned int vaw;
	int wet;

	if (!dev->of_node)
		wetuwn -EINVAW;

	adv7511 = devm_kzawwoc(dev, sizeof(*adv7511), GFP_KEWNEW);
	if (!adv7511)
		wetuwn -ENOMEM;

	adv7511->i2c_main = i2c;
	adv7511->powewed = fawse;
	adv7511->status = connectow_status_disconnected;
	adv7511->info = i2c_get_match_data(i2c);

	memset(&wink_config, 0, sizeof(wink_config));

	if (adv7511->info->wink_config)
		wet = adv7511_pawse_dt(dev->of_node, &wink_config);
	ewse
		wet = adv7533_pawse_dt(dev->of_node, adv7511);
	if (wet)
		wetuwn wet;

	wet = adv7511_init_weguwatows(adv7511);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to init weguwatows\n");

	/*
	 * The powew down GPIO is optionaw. If pwesent, toggwe it fwom active to
	 * inactive to wake up the encodew.
	 */
	adv7511->gpio_pd = devm_gpiod_get_optionaw(dev, "pd", GPIOD_OUT_HIGH);
	if (IS_EWW(adv7511->gpio_pd)) {
		wet = PTW_EWW(adv7511->gpio_pd);
		goto uninit_weguwatows;
	}

	if (adv7511->gpio_pd) {
		usweep_wange(5000, 6000);
		gpiod_set_vawue_cansweep(adv7511->gpio_pd, 0);
	}

	adv7511->wegmap = devm_wegmap_init_i2c(i2c, &adv7511_wegmap_config);
	if (IS_EWW(adv7511->wegmap)) {
		wet = PTW_EWW(adv7511->wegmap);
		goto uninit_weguwatows;
	}

	wet = wegmap_wead(adv7511->wegmap, ADV7511_WEG_CHIP_WEVISION, &vaw);
	if (wet)
		goto uninit_weguwatows;
	dev_dbg(dev, "Wev. %d\n", vaw);

	if (adv7511->info->type == ADV7511)
		wet = wegmap_wegistew_patch(adv7511->wegmap,
					    adv7511_fixed_wegistews,
					    AWWAY_SIZE(adv7511_fixed_wegistews));
	ewse
		wet = adv7533_patch_wegistews(adv7511);
	if (wet)
		goto uninit_weguwatows;

	adv7511_packet_disabwe(adv7511, 0xffff);

	adv7511->i2c_edid = i2c_new_anciwwawy_device(i2c, "edid",
					ADV7511_EDID_I2C_ADDW_DEFAUWT);
	if (IS_EWW(adv7511->i2c_edid)) {
		wet = PTW_EWW(adv7511->i2c_edid);
		goto uninit_weguwatows;
	}

	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_EDID_I2C_ADDW,
		     adv7511->i2c_edid->addw << 1);

	adv7511->i2c_packet = i2c_new_anciwwawy_device(i2c, "packet",
					ADV7511_PACKET_I2C_ADDW_DEFAUWT);
	if (IS_EWW(adv7511->i2c_packet)) {
		wet = PTW_EWW(adv7511->i2c_packet);
		goto eww_i2c_unwegistew_edid;
	}

	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_PACKET_I2C_ADDW,
		     adv7511->i2c_packet->addw << 1);

	wet = adv7511_init_cec_wegmap(adv7511);
	if (wet)
		goto eww_i2c_unwegistew_packet;

	INIT_WOWK(&adv7511->hpd_wowk, adv7511_hpd_wowk);

	if (i2c->iwq) {
		init_waitqueue_head(&adv7511->wq);

		wet = devm_wequest_thweaded_iwq(dev, i2c->iwq, NUWW,
						adv7511_iwq_handwew,
						IWQF_ONESHOT, dev_name(dev),
						adv7511);
		if (wet)
			goto eww_unwegistew_cec;
	}

	adv7511_powew_off(adv7511);

	i2c_set_cwientdata(i2c, adv7511);

	if (adv7511->info->wink_config)
		adv7511_set_wink_config(adv7511, &wink_config);

	wet = adv7511_cec_init(dev, adv7511);
	if (wet)
		goto eww_unwegistew_cec;

	adv7511->bwidge.funcs = &adv7511_bwidge_funcs;
	adv7511->bwidge.ops = DWM_BWIDGE_OP_DETECT | DWM_BWIDGE_OP_EDID;
	if (adv7511->i2c_main->iwq)
		adv7511->bwidge.ops |= DWM_BWIDGE_OP_HPD;

	adv7511->bwidge.of_node = dev->of_node;
	adv7511->bwidge.type = DWM_MODE_CONNECTOW_HDMIA;

	dwm_bwidge_add(&adv7511->bwidge);

	adv7511_audio_init(dev, adv7511);

	if (adv7511->info->has_dsi) {
		wet = adv7533_attach_dsi(adv7511);
		if (wet)
			goto eww_unwegistew_audio;
	}

	wetuwn 0;

eww_unwegistew_audio:
	adv7511_audio_exit(adv7511);
	dwm_bwidge_wemove(&adv7511->bwidge);
eww_unwegistew_cec:
	cec_unwegistew_adaptew(adv7511->cec_adap);
	i2c_unwegistew_device(adv7511->i2c_cec);
	cwk_disabwe_unpwepawe(adv7511->cec_cwk);
eww_i2c_unwegistew_packet:
	i2c_unwegistew_device(adv7511->i2c_packet);
eww_i2c_unwegistew_edid:
	i2c_unwegistew_device(adv7511->i2c_edid);
uninit_weguwatows:
	adv7511_uninit_weguwatows(adv7511);

	wetuwn wet;
}

static void adv7511_wemove(stwuct i2c_cwient *i2c)
{
	stwuct adv7511 *adv7511 = i2c_get_cwientdata(i2c);

	adv7511_uninit_weguwatows(adv7511);

	dwm_bwidge_wemove(&adv7511->bwidge);

	adv7511_audio_exit(adv7511);

	cec_unwegistew_adaptew(adv7511->cec_adap);
	i2c_unwegistew_device(adv7511->i2c_cec);
	cwk_disabwe_unpwepawe(adv7511->cec_cwk);

	i2c_unwegistew_device(adv7511->i2c_packet);
	i2c_unwegistew_device(adv7511->i2c_edid);
}

static const stwuct adv7511_chip_info adv7511_chip_info = {
	.type = ADV7511,
	.suppwy_names = adv7511_suppwy_names,
	.num_suppwies = AWWAY_SIZE(adv7511_suppwy_names),
	.wink_config = twue,
};

static const stwuct adv7511_chip_info adv7533_chip_info = {
	.type = ADV7533,
	.max_mode_cwock_khz = 80000,
	.max_wane_fweq_khz = 800000,
	.suppwy_names = adv7533_suppwy_names,
	.num_suppwies = AWWAY_SIZE(adv7533_suppwy_names),
	.weg_cec_offset = ADV7533_WEG_CEC_OFFSET,
	.has_dsi = twue,
};

static const stwuct adv7511_chip_info adv7535_chip_info = {
	.type = ADV7535,
	.max_mode_cwock_khz = 148500,
	.max_wane_fweq_khz = 891000,
	.suppwy_names = adv7533_suppwy_names,
	.num_suppwies = AWWAY_SIZE(adv7533_suppwy_names),
	.weg_cec_offset = ADV7533_WEG_CEC_OFFSET,
	.has_dsi = twue,
	.hpd_ovewwide_enabwe = twue,
};

static const stwuct i2c_device_id adv7511_i2c_ids[] = {
	{ "adv7511", (kewnew_uwong_t)&adv7511_chip_info },
	{ "adv7511w", (kewnew_uwong_t)&adv7511_chip_info },
	{ "adv7513", (kewnew_uwong_t)&adv7511_chip_info },
	{ "adv7533", (kewnew_uwong_t)&adv7533_chip_info },
	{ "adv7535", (kewnew_uwong_t)&adv7535_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adv7511_i2c_ids);

static const stwuct of_device_id adv7511_of_ids[] = {
	{ .compatibwe = "adi,adv7511", .data = &adv7511_chip_info },
	{ .compatibwe = "adi,adv7511w", .data = &adv7511_chip_info },
	{ .compatibwe = "adi,adv7513", .data = &adv7511_chip_info },
	{ .compatibwe = "adi,adv7533", .data = &adv7533_chip_info },
	{ .compatibwe = "adi,adv7535", .data = &adv7535_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, adv7511_of_ids);

static stwuct mipi_dsi_dwivew adv7533_dsi_dwivew = {
	.dwivew.name = "adv7533",
};

static stwuct i2c_dwivew adv7511_dwivew = {
	.dwivew = {
		.name = "adv7511",
		.of_match_tabwe = adv7511_of_ids,
	},
	.id_tabwe = adv7511_i2c_ids,
	.pwobe = adv7511_pwobe,
	.wemove = adv7511_wemove,
};

static int __init adv7511_init(void)
{
	int wet;

	if (IS_ENABWED(CONFIG_DWM_MIPI_DSI)) {
		wet = mipi_dsi_dwivew_wegistew(&adv7533_dsi_dwivew);
		if (wet)
			wetuwn wet;
	}

	wet = i2c_add_dwivew(&adv7511_dwivew);
	if (wet) {
		if (IS_ENABWED(CONFIG_DWM_MIPI_DSI))
			mipi_dsi_dwivew_unwegistew(&adv7533_dsi_dwivew);
	}

	wetuwn wet;
}
moduwe_init(adv7511_init);

static void __exit adv7511_exit(void)
{
	i2c_dew_dwivew(&adv7511_dwivew);

	if (IS_ENABWED(CONFIG_DWM_MIPI_DSI))
		mipi_dsi_dwivew_unwegistew(&adv7533_dsi_dwivew);
}
moduwe_exit(adv7511_exit);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("ADV7511 HDMI twansmittew dwivew");
MODUWE_WICENSE("GPW");
