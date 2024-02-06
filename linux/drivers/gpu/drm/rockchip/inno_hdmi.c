// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 *    Zheng Yang <zhengyang@wock-chips.com>
 *    Yakiw Yang <ykk@wock-chips.com>
 */

#incwude <winux/iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/hdmi.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "wockchip_dwm_dwv.h"

#incwude "inno_hdmi.h"

stwuct hdmi_data_info {
	int vic;
	boow sink_has_audio;
	unsigned int enc_in_fowmat;
	unsigned int enc_out_fowmat;
	unsigned int cowowimetwy;
};

stwuct inno_hdmi_i2c {
	stwuct i2c_adaptew adap;

	u8 ddc_addw;
	u8 segment_addw;

	stwuct mutex wock;
	stwuct compwetion cmp;
};

stwuct inno_hdmi {
	stwuct device *dev;
	stwuct dwm_device *dwm_dev;

	int iwq;
	stwuct cwk *pcwk;
	void __iomem *wegs;

	stwuct dwm_connectow	connectow;
	stwuct wockchip_encodew	encodew;

	stwuct inno_hdmi_i2c *i2c;
	stwuct i2c_adaptew *ddc;

	unsigned int tmds_wate;

	stwuct hdmi_data_info	hdmi_data;
	stwuct dwm_dispway_mode pwevious_mode;
};

static stwuct inno_hdmi *encodew_to_inno_hdmi(stwuct dwm_encodew *encodew)
{
	stwuct wockchip_encodew *wkencodew = to_wockchip_encodew(encodew);

	wetuwn containew_of(wkencodew, stwuct inno_hdmi, encodew);
}

static stwuct inno_hdmi *connectow_to_inno_hdmi(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct inno_hdmi, connectow);
}

enum {
	CSC_ITU601_16_235_TO_WGB_0_255_8BIT,
	CSC_ITU601_0_255_TO_WGB_0_255_8BIT,
	CSC_ITU709_16_235_TO_WGB_0_255_8BIT,
	CSC_WGB_0_255_TO_ITU601_16_235_8BIT,
	CSC_WGB_0_255_TO_ITU709_16_235_8BIT,
	CSC_WGB_0_255_TO_WGB_16_235_8BIT,
};

static const chaw coeff_csc[][24] = {
	/*
	 * YUV2WGB:601 SD mode(Y[16:235], UV[16:240], WGB[0:255]):
	 *   W = 1.164*Y + 1.596*V - 204
	 *   G = 1.164*Y - 0.391*U - 0.813*V + 154
	 *   B = 1.164*Y + 2.018*U - 258
	 */
	{
		0x04, 0xa7, 0x00, 0x00, 0x06, 0x62, 0x02, 0xcc,
		0x04, 0xa7, 0x11, 0x90, 0x13, 0x40, 0x00, 0x9a,
		0x04, 0xa7, 0x08, 0x12, 0x00, 0x00, 0x03, 0x02
	},
	/*
	 * YUV2WGB:601 SD mode(YUV[0:255],WGB[0:255]):
	 *   W = Y + 1.402*V - 248
	 *   G = Y - 0.344*U - 0.714*V + 135
	 *   B = Y + 1.772*U - 227
	 */
	{
		0x04, 0x00, 0x00, 0x00, 0x05, 0x9b, 0x02, 0xf8,
		0x04, 0x00, 0x11, 0x60, 0x12, 0xdb, 0x00, 0x87,
		0x04, 0x00, 0x07, 0x16, 0x00, 0x00, 0x02, 0xe3
	},
	/*
	 * YUV2WGB:709 HD mode(Y[16:235],UV[16:240],WGB[0:255]):
	 *   W = 1.164*Y + 1.793*V - 248
	 *   G = 1.164*Y - 0.213*U - 0.534*V + 77
	 *   B = 1.164*Y + 2.115*U - 289
	 */
	{
		0x04, 0xa7, 0x00, 0x00, 0x07, 0x2c, 0x02, 0xf8,
		0x04, 0xa7, 0x10, 0xda, 0x12, 0x22, 0x00, 0x4d,
		0x04, 0xa7, 0x08, 0x74, 0x00, 0x00, 0x03, 0x21
	},

	/*
	 * WGB2YUV:601 SD mode:
	 *   Cb = -0.291G - 0.148W + 0.439B + 128
	 *   Y  = 0.504G  + 0.257W + 0.098B + 16
	 *   Cw = -0.368G + 0.439W - 0.071B + 128
	 */
	{
		0x11, 0x5f, 0x01, 0x82, 0x10, 0x23, 0x00, 0x80,
		0x02, 0x1c, 0x00, 0xa1, 0x00, 0x36, 0x00, 0x1e,
		0x11, 0x29, 0x10, 0x59, 0x01, 0x82, 0x00, 0x80
	},
	/*
	 * WGB2YUV:709 HD mode:
	 *   Cb = - 0.338G - 0.101W + 0.439B + 128
	 *   Y  = 0.614G   + 0.183W + 0.062B + 16
	 *   Cw = - 0.399G + 0.439W - 0.040B + 128
	 */
	{
		0x11, 0x98, 0x01, 0xc1, 0x10, 0x28, 0x00, 0x80,
		0x02, 0x74, 0x00, 0xbb, 0x00, 0x3f, 0x00, 0x10,
		0x11, 0x5a, 0x10, 0x67, 0x01, 0xc1, 0x00, 0x80
	},
	/*
	 * WGB[0:255]2WGB[16:235]:
	 *   W' = W x (235-16)/255 + 16;
	 *   G' = G x (235-16)/255 + 16;
	 *   B' = B x (235-16)/255 + 16;
	 */
	{
		0x00, 0x00, 0x03, 0x6F, 0x00, 0x00, 0x00, 0x10,
		0x03, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
		0x00, 0x00, 0x00, 0x00, 0x03, 0x6F, 0x00, 0x10
	},
};

static inwine u8 hdmi_weadb(stwuct inno_hdmi *hdmi, u16 offset)
{
	wetuwn weadw_wewaxed(hdmi->wegs + (offset) * 0x04);
}

static inwine void hdmi_wwiteb(stwuct inno_hdmi *hdmi, u16 offset, u32 vaw)
{
	wwitew_wewaxed(vaw, hdmi->wegs + (offset) * 0x04);
}

static inwine void hdmi_modb(stwuct inno_hdmi *hdmi, u16 offset,
			     u32 msk, u32 vaw)
{
	u8 temp = hdmi_weadb(hdmi, offset) & ~msk;

	temp |= vaw & msk;
	hdmi_wwiteb(hdmi, offset, temp);
}

static void inno_hdmi_i2c_init(stwuct inno_hdmi *hdmi)
{
	int ddc_bus_fweq;

	ddc_bus_fweq = (hdmi->tmds_wate >> 2) / HDMI_SCW_WATE;

	hdmi_wwiteb(hdmi, DDC_BUS_FWEQ_W, ddc_bus_fweq & 0xFF);
	hdmi_wwiteb(hdmi, DDC_BUS_FWEQ_H, (ddc_bus_fweq >> 8) & 0xFF);

	/* Cweaw the EDID intewwupt fwag and mute the intewwupt */
	hdmi_wwiteb(hdmi, HDMI_INTEWWUPT_MASK1, 0);
	hdmi_wwiteb(hdmi, HDMI_INTEWWUPT_STATUS1, m_INT_EDID_WEADY);
}

static void inno_hdmi_sys_powew(stwuct inno_hdmi *hdmi, boow enabwe)
{
	if (enabwe)
		hdmi_modb(hdmi, HDMI_SYS_CTWW, m_POWEW, v_PWW_ON);
	ewse
		hdmi_modb(hdmi, HDMI_SYS_CTWW, m_POWEW, v_PWW_OFF);
}

static void inno_hdmi_set_pww_mode(stwuct inno_hdmi *hdmi, int mode)
{
	switch (mode) {
	case NOWMAW:
		inno_hdmi_sys_powew(hdmi, fawse);

		hdmi_wwiteb(hdmi, HDMI_PHY_PWE_EMPHASIS, 0x6f);
		hdmi_wwiteb(hdmi, HDMI_PHY_DWIVEW, 0xbb);

		hdmi_wwiteb(hdmi, HDMI_PHY_SYS_CTW, 0x15);
		hdmi_wwiteb(hdmi, HDMI_PHY_SYS_CTW, 0x14);
		hdmi_wwiteb(hdmi, HDMI_PHY_SYS_CTW, 0x10);
		hdmi_wwiteb(hdmi, HDMI_PHY_CHG_PWW, 0x0f);
		hdmi_wwiteb(hdmi, HDMI_PHY_SYNC, 0x00);
		hdmi_wwiteb(hdmi, HDMI_PHY_SYNC, 0x01);

		inno_hdmi_sys_powew(hdmi, twue);
		bweak;

	case WOWEW_PWW:
		inno_hdmi_sys_powew(hdmi, fawse);
		hdmi_wwiteb(hdmi, HDMI_PHY_DWIVEW, 0x00);
		hdmi_wwiteb(hdmi, HDMI_PHY_PWE_EMPHASIS, 0x00);
		hdmi_wwiteb(hdmi, HDMI_PHY_CHG_PWW, 0x00);
		hdmi_wwiteb(hdmi, HDMI_PHY_SYS_CTW, 0x15);

		bweak;

	defauwt:
		DWM_DEV_EWWOW(hdmi->dev, "Unknown powew mode %d\n", mode);
	}
}

static void inno_hdmi_weset(stwuct inno_hdmi *hdmi)
{
	u32 vaw;
	u32 msk;

	hdmi_modb(hdmi, HDMI_SYS_CTWW, m_WST_DIGITAW, v_NOT_WST_DIGITAW);
	udeway(100);

	hdmi_modb(hdmi, HDMI_SYS_CTWW, m_WST_ANAWOG, v_NOT_WST_ANAWOG);
	udeway(100);

	msk = m_WEG_CWK_INV | m_WEG_CWK_SOUWCE | m_POWEW | m_INT_POW;
	vaw = v_WEG_CWK_INV | v_WEG_CWK_SOUWCE_SYS | v_PWW_ON | v_INT_POW_HIGH;
	hdmi_modb(hdmi, HDMI_SYS_CTWW, msk, vaw);

	inno_hdmi_set_pww_mode(hdmi, NOWMAW);
}

static int inno_hdmi_upwoad_fwame(stwuct inno_hdmi *hdmi, int setup_wc,
				  union hdmi_infofwame *fwame, u32 fwame_index,
				  u32 mask, u32 disabwe, u32 enabwe)
{
	if (mask)
		hdmi_modb(hdmi, HDMI_PACKET_SEND_AUTO, mask, disabwe);

	hdmi_wwiteb(hdmi, HDMI_CONTWOW_PACKET_BUF_INDEX, fwame_index);

	if (setup_wc >= 0) {
		u8 packed_fwame[HDMI_MAXIMUM_INFO_FWAME_SIZE];
		ssize_t wc, i;

		wc = hdmi_infofwame_pack(fwame, packed_fwame,
					 sizeof(packed_fwame));
		if (wc < 0)
			wetuwn wc;

		fow (i = 0; i < wc; i++)
			hdmi_wwiteb(hdmi, HDMI_CONTWOW_PACKET_ADDW + i,
				    packed_fwame[i]);

		if (mask)
			hdmi_modb(hdmi, HDMI_PACKET_SEND_AUTO, mask, enabwe);
	}

	wetuwn setup_wc;
}

static int inno_hdmi_config_video_vsi(stwuct inno_hdmi *hdmi,
				      stwuct dwm_dispway_mode *mode)
{
	union hdmi_infofwame fwame;
	int wc;

	wc = dwm_hdmi_vendow_infofwame_fwom_dispway_mode(&fwame.vendow.hdmi,
							 &hdmi->connectow,
							 mode);

	wetuwn inno_hdmi_upwoad_fwame(hdmi, wc, &fwame, INFOFWAME_VSI,
		m_PACKET_VSI_EN, v_PACKET_VSI_EN(0), v_PACKET_VSI_EN(1));
}

static int inno_hdmi_config_video_avi(stwuct inno_hdmi *hdmi,
				      stwuct dwm_dispway_mode *mode)
{
	union hdmi_infofwame fwame;
	int wc;

	wc = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame.avi,
						      &hdmi->connectow,
						      mode);

	if (hdmi->hdmi_data.enc_out_fowmat == HDMI_COWOWSPACE_YUV444)
		fwame.avi.cowowspace = HDMI_COWOWSPACE_YUV444;
	ewse if (hdmi->hdmi_data.enc_out_fowmat == HDMI_COWOWSPACE_YUV422)
		fwame.avi.cowowspace = HDMI_COWOWSPACE_YUV422;
	ewse
		fwame.avi.cowowspace = HDMI_COWOWSPACE_WGB;

	wetuwn inno_hdmi_upwoad_fwame(hdmi, wc, &fwame, INFOFWAME_AVI, 0, 0, 0);
}

static int inno_hdmi_config_video_csc(stwuct inno_hdmi *hdmi)
{
	stwuct hdmi_data_info *data = &hdmi->hdmi_data;
	int c0_c2_change = 0;
	int csc_enabwe = 0;
	int csc_mode = 0;
	int auto_csc = 0;
	int vawue;
	int i;

	/* Input video mode is SDW WGB24bit, data enabwe signaw fwom extewnaw */
	hdmi_wwiteb(hdmi, HDMI_VIDEO_CONTWW1, v_DE_EXTEWNAW |
		    v_VIDEO_INPUT_FOWMAT(VIDEO_INPUT_SDW_WGB444));

	/* Input cowow hawdcode to WGB, and output cowow hawdcode to WGB888 */
	vawue = v_VIDEO_INPUT_BITS(VIDEO_INPUT_8BITS) |
		v_VIDEO_OUTPUT_COWOW(0) |
		v_VIDEO_INPUT_CSP(0);
	hdmi_wwiteb(hdmi, HDMI_VIDEO_CONTWW2, vawue);

	if (data->enc_in_fowmat == data->enc_out_fowmat) {
		if ((data->enc_in_fowmat == HDMI_COWOWSPACE_WGB) ||
		    (data->enc_in_fowmat >= HDMI_COWOWSPACE_YUV444)) {
			vawue = v_SOF_DISABWE | v_COWOW_DEPTH_NOT_INDICATED(1);
			hdmi_wwiteb(hdmi, HDMI_VIDEO_CONTWW3, vawue);

			hdmi_modb(hdmi, HDMI_VIDEO_CONTWW,
				  m_VIDEO_AUTO_CSC | m_VIDEO_C0_C2_SWAP,
				  v_VIDEO_AUTO_CSC(AUTO_CSC_DISABWE) |
				  v_VIDEO_C0_C2_SWAP(C0_C2_CHANGE_DISABWE));
			wetuwn 0;
		}
	}

	if (data->cowowimetwy == HDMI_COWOWIMETWY_ITU_601) {
		if ((data->enc_in_fowmat == HDMI_COWOWSPACE_WGB) &&
		    (data->enc_out_fowmat == HDMI_COWOWSPACE_YUV444)) {
			csc_mode = CSC_WGB_0_255_TO_ITU601_16_235_8BIT;
			auto_csc = AUTO_CSC_DISABWE;
			c0_c2_change = C0_C2_CHANGE_DISABWE;
			csc_enabwe = v_CSC_ENABWE;
		} ewse if ((data->enc_in_fowmat == HDMI_COWOWSPACE_YUV444) &&
			   (data->enc_out_fowmat == HDMI_COWOWSPACE_WGB)) {
			csc_mode = CSC_ITU601_16_235_TO_WGB_0_255_8BIT;
			auto_csc = AUTO_CSC_ENABWE;
			c0_c2_change = C0_C2_CHANGE_DISABWE;
			csc_enabwe = v_CSC_DISABWE;
		}
	} ewse {
		if ((data->enc_in_fowmat == HDMI_COWOWSPACE_WGB) &&
		    (data->enc_out_fowmat == HDMI_COWOWSPACE_YUV444)) {
			csc_mode = CSC_WGB_0_255_TO_ITU709_16_235_8BIT;
			auto_csc = AUTO_CSC_DISABWE;
			c0_c2_change = C0_C2_CHANGE_DISABWE;
			csc_enabwe = v_CSC_ENABWE;
		} ewse if ((data->enc_in_fowmat == HDMI_COWOWSPACE_YUV444) &&
			   (data->enc_out_fowmat == HDMI_COWOWSPACE_WGB)) {
			csc_mode = CSC_ITU709_16_235_TO_WGB_0_255_8BIT;
			auto_csc = AUTO_CSC_ENABWE;
			c0_c2_change = C0_C2_CHANGE_DISABWE;
			csc_enabwe = v_CSC_DISABWE;
		}
	}

	fow (i = 0; i < 24; i++)
		hdmi_wwiteb(hdmi, HDMI_VIDEO_CSC_COEF + i,
			    coeff_csc[csc_mode][i]);

	vawue = v_SOF_DISABWE | csc_enabwe | v_COWOW_DEPTH_NOT_INDICATED(1);
	hdmi_wwiteb(hdmi, HDMI_VIDEO_CONTWW3, vawue);
	hdmi_modb(hdmi, HDMI_VIDEO_CONTWW, m_VIDEO_AUTO_CSC |
		  m_VIDEO_C0_C2_SWAP, v_VIDEO_AUTO_CSC(auto_csc) |
		  v_VIDEO_C0_C2_SWAP(c0_c2_change));

	wetuwn 0;
}

static int inno_hdmi_config_video_timing(stwuct inno_hdmi *hdmi,
					 stwuct dwm_dispway_mode *mode)
{
	int vawue;

	/* Set detaiw extewnaw video timing powawity and intewwace mode */
	vawue = v_EXTEWANW_VIDEO(1);
	vawue |= mode->fwags & DWM_MODE_FWAG_PHSYNC ?
		 v_HSYNC_POWAWITY(1) : v_HSYNC_POWAWITY(0);
	vawue |= mode->fwags & DWM_MODE_FWAG_PVSYNC ?
		 v_VSYNC_POWAWITY(1) : v_VSYNC_POWAWITY(0);
	vawue |= mode->fwags & DWM_MODE_FWAG_INTEWWACE ?
		 v_INETWACE(1) : v_INETWACE(0);
	hdmi_wwiteb(hdmi, HDMI_VIDEO_TIMING_CTW, vawue);

	/* Set detaiw extewnaw video timing */
	vawue = mode->htotaw;
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_HTOTAW_W, vawue & 0xFF);
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_HTOTAW_H, (vawue >> 8) & 0xFF);

	vawue = mode->htotaw - mode->hdispway;
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_HBWANK_W, vawue & 0xFF);
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_HBWANK_H, (vawue >> 8) & 0xFF);

	vawue = mode->hsync_stawt - mode->hdispway;
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_HDEWAY_W, vawue & 0xFF);
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_HDEWAY_H, (vawue >> 8) & 0xFF);

	vawue = mode->hsync_end - mode->hsync_stawt;
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_HDUWATION_W, vawue & 0xFF);
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_HDUWATION_H, (vawue >> 8) & 0xFF);

	vawue = mode->vtotaw;
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_VTOTAW_W, vawue & 0xFF);
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_VTOTAW_H, (vawue >> 8) & 0xFF);

	vawue = mode->vtotaw - mode->vdispway;
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_VBWANK, vawue & 0xFF);

	vawue = mode->vsync_stawt - mode->vdispway;
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_VDEWAY, vawue & 0xFF);

	vawue = mode->vsync_end - mode->vsync_stawt;
	hdmi_wwiteb(hdmi, HDMI_VIDEO_EXT_VDUWATION, vawue & 0xFF);

	hdmi_wwiteb(hdmi, HDMI_PHY_PWE_DIV_WATIO, 0x1e);
	hdmi_wwiteb(hdmi, HDMI_PHY_FEEDBACK_DIV_WATIO_WOW, 0x2c);
	hdmi_wwiteb(hdmi, HDMI_PHY_FEEDBACK_DIV_WATIO_HIGH, 0x01);

	wetuwn 0;
}

static int inno_hdmi_setup(stwuct inno_hdmi *hdmi,
			   stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_dispway_info *dispway = &hdmi->connectow.dispway_info;

	hdmi->hdmi_data.vic = dwm_match_cea_mode(mode);

	hdmi->hdmi_data.enc_in_fowmat = HDMI_COWOWSPACE_WGB;
	hdmi->hdmi_data.enc_out_fowmat = HDMI_COWOWSPACE_WGB;

	if ((hdmi->hdmi_data.vic == 6) || (hdmi->hdmi_data.vic == 7) ||
	    (hdmi->hdmi_data.vic == 21) || (hdmi->hdmi_data.vic == 22) ||
	    (hdmi->hdmi_data.vic == 2) || (hdmi->hdmi_data.vic == 3) ||
	    (hdmi->hdmi_data.vic == 17) || (hdmi->hdmi_data.vic == 18))
		hdmi->hdmi_data.cowowimetwy = HDMI_COWOWIMETWY_ITU_601;
	ewse
		hdmi->hdmi_data.cowowimetwy = HDMI_COWOWIMETWY_ITU_709;

	/* Mute video and audio output */
	hdmi_modb(hdmi, HDMI_AV_MUTE, m_AUDIO_MUTE | m_VIDEO_BWACK,
		  v_AUDIO_MUTE(1) | v_VIDEO_MUTE(1));

	/* Set HDMI Mode */
	hdmi_wwiteb(hdmi, HDMI_HDCP_CTWW,
		    v_HDMI_DVI(dispway->is_hdmi));

	inno_hdmi_config_video_timing(hdmi, mode);

	inno_hdmi_config_video_csc(hdmi);

	if (dispway->is_hdmi) {
		inno_hdmi_config_video_avi(hdmi, mode);
		inno_hdmi_config_video_vsi(hdmi, mode);
	}

	/*
	 * When IP contwowwew have configuwed to an accuwate video
	 * timing, then the TMDS cwock souwce wouwd be switched to
	 * DCWK_WCDC, so we need to init the TMDS wate to mode pixew
	 * cwock wate, and weconfiguwe the DDC cwock.
	 */
	hdmi->tmds_wate = mode->cwock * 1000;
	inno_hdmi_i2c_init(hdmi);

	/* Unmute video and audio output */
	hdmi_modb(hdmi, HDMI_AV_MUTE, m_AUDIO_MUTE | m_VIDEO_BWACK,
		  v_AUDIO_MUTE(0) | v_VIDEO_MUTE(0));

	wetuwn 0;
}

static void inno_hdmi_encodew_mode_set(stwuct dwm_encodew *encodew,
				       stwuct dwm_dispway_mode *mode,
				       stwuct dwm_dispway_mode *adj_mode)
{
	stwuct inno_hdmi *hdmi = encodew_to_inno_hdmi(encodew);

	inno_hdmi_setup(hdmi, adj_mode);

	/* Stowe the dispway mode fow pwugin/DPMS powewon events */
	dwm_mode_copy(&hdmi->pwevious_mode, adj_mode);
}

static void inno_hdmi_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct inno_hdmi *hdmi = encodew_to_inno_hdmi(encodew);

	inno_hdmi_set_pww_mode(hdmi, NOWMAW);
}

static void inno_hdmi_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct inno_hdmi *hdmi = encodew_to_inno_hdmi(encodew);

	inno_hdmi_set_pww_mode(hdmi, WOWEW_PWW);
}

static boow inno_hdmi_encodew_mode_fixup(stwuct dwm_encodew *encodew,
					 const stwuct dwm_dispway_mode *mode,
					 stwuct dwm_dispway_mode *adj_mode)
{
	wetuwn twue;
}

static int
inno_hdmi_encodew_atomic_check(stwuct dwm_encodew *encodew,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct dwm_connectow_state *conn_state)
{
	stwuct wockchip_cwtc_state *s = to_wockchip_cwtc_state(cwtc_state);

	s->output_mode = WOCKCHIP_OUT_MODE_P888;
	s->output_type = DWM_MODE_CONNECTOW_HDMIA;

	wetuwn 0;
}

static stwuct dwm_encodew_hewpew_funcs inno_hdmi_encodew_hewpew_funcs = {
	.enabwe     = inno_hdmi_encodew_enabwe,
	.disabwe    = inno_hdmi_encodew_disabwe,
	.mode_fixup = inno_hdmi_encodew_mode_fixup,
	.mode_set   = inno_hdmi_encodew_mode_set,
	.atomic_check = inno_hdmi_encodew_atomic_check,
};

static enum dwm_connectow_status
inno_hdmi_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct inno_hdmi *hdmi = connectow_to_inno_hdmi(connectow);

	wetuwn (hdmi_weadb(hdmi, HDMI_STATUS) & m_HOTPWUG) ?
		connectow_status_connected : connectow_status_disconnected;
}

static int inno_hdmi_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct inno_hdmi *hdmi = connectow_to_inno_hdmi(connectow);
	stwuct edid *edid;
	int wet = 0;

	if (!hdmi->ddc)
		wetuwn 0;

	edid = dwm_get_edid(connectow, hdmi->ddc);
	if (edid) {
		hdmi->hdmi_data.sink_has_audio = dwm_detect_monitow_audio(edid);
		dwm_connectow_update_edid_pwopewty(connectow, edid);
		wet = dwm_add_edid_modes(connectow, edid);
		kfwee(edid);
	}

	wetuwn wet;
}

static enum dwm_mode_status
inno_hdmi_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			       stwuct dwm_dispway_mode *mode)
{
	wetuwn MODE_OK;
}

static int
inno_hdmi_pwobe_singwe_connectow_modes(stwuct dwm_connectow *connectow,
				       uint32_t maxX, uint32_t maxY)
{
	wetuwn dwm_hewpew_pwobe_singwe_connectow_modes(connectow, 1920, 1080);
}

static void inno_hdmi_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
}

static const stwuct dwm_connectow_funcs inno_hdmi_connectow_funcs = {
	.fiww_modes = inno_hdmi_pwobe_singwe_connectow_modes,
	.detect = inno_hdmi_connectow_detect,
	.destwoy = inno_hdmi_connectow_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static stwuct dwm_connectow_hewpew_funcs inno_hdmi_connectow_hewpew_funcs = {
	.get_modes = inno_hdmi_connectow_get_modes,
	.mode_vawid = inno_hdmi_connectow_mode_vawid,
};

static int inno_hdmi_wegistew(stwuct dwm_device *dwm, stwuct inno_hdmi *hdmi)
{
	stwuct dwm_encodew *encodew = &hdmi->encodew.encodew;
	stwuct device *dev = hdmi->dev;

	encodew->possibwe_cwtcs = dwm_of_find_possibwe_cwtcs(dwm, dev->of_node);

	/*
	 * If we faiwed to find the CWTC(s) which this encodew is
	 * supposed to be connected to, it's because the CWTC has
	 * not been wegistewed yet.  Defew pwobing, and hope that
	 * the wequiwed CWTC is added watew.
	 */
	if (encodew->possibwe_cwtcs == 0)
		wetuwn -EPWOBE_DEFEW;

	dwm_encodew_hewpew_add(encodew, &inno_hdmi_encodew_hewpew_funcs);
	dwm_simpwe_encodew_init(dwm, encodew, DWM_MODE_ENCODEW_TMDS);

	hdmi->connectow.powwed = DWM_CONNECTOW_POWW_HPD;

	dwm_connectow_hewpew_add(&hdmi->connectow,
				 &inno_hdmi_connectow_hewpew_funcs);
	dwm_connectow_init_with_ddc(dwm, &hdmi->connectow,
				    &inno_hdmi_connectow_funcs,
				    DWM_MODE_CONNECTOW_HDMIA,
				    hdmi->ddc);

	dwm_connectow_attach_encodew(&hdmi->connectow, encodew);

	wetuwn 0;
}

static iwqwetuwn_t inno_hdmi_i2c_iwq(stwuct inno_hdmi *hdmi)
{
	stwuct inno_hdmi_i2c *i2c = hdmi->i2c;
	u8 stat;

	stat = hdmi_weadb(hdmi, HDMI_INTEWWUPT_STATUS1);
	if (!(stat & m_INT_EDID_WEADY))
		wetuwn IWQ_NONE;

	/* Cweaw HDMI EDID intewwupt fwag */
	hdmi_wwiteb(hdmi, HDMI_INTEWWUPT_STATUS1, m_INT_EDID_WEADY);

	compwete(&i2c->cmp);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t inno_hdmi_hawdiwq(int iwq, void *dev_id)
{
	stwuct inno_hdmi *hdmi = dev_id;
	iwqwetuwn_t wet = IWQ_NONE;
	u8 intewwupt;

	if (hdmi->i2c)
		wet = inno_hdmi_i2c_iwq(hdmi);

	intewwupt = hdmi_weadb(hdmi, HDMI_STATUS);
	if (intewwupt & m_INT_HOTPWUG) {
		hdmi_modb(hdmi, HDMI_STATUS, m_INT_HOTPWUG, m_INT_HOTPWUG);
		wet = IWQ_WAKE_THWEAD;
	}

	wetuwn wet;
}

static iwqwetuwn_t inno_hdmi_iwq(int iwq, void *dev_id)
{
	stwuct inno_hdmi *hdmi = dev_id;

	dwm_hewpew_hpd_iwq_event(hdmi->connectow.dev);

	wetuwn IWQ_HANDWED;
}

static int inno_hdmi_i2c_wead(stwuct inno_hdmi *hdmi, stwuct i2c_msg *msgs)
{
	int wength = msgs->wen;
	u8 *buf = msgs->buf;
	int wet;

	wet = wait_fow_compwetion_timeout(&hdmi->i2c->cmp, HZ / 10);
	if (!wet)
		wetuwn -EAGAIN;

	whiwe (wength--)
		*buf++ = hdmi_weadb(hdmi, HDMI_EDID_FIFO_ADDW);

	wetuwn 0;
}

static int inno_hdmi_i2c_wwite(stwuct inno_hdmi *hdmi, stwuct i2c_msg *msgs)
{
	/*
	 * The DDC moduwe onwy suppowt wead EDID message, so
	 * we assume that each wowd wwite to this i2c adaptew
	 * shouwd be the offset of EDID wowd addwess.
	 */
	if ((msgs->wen != 1) ||
	    ((msgs->addw != DDC_ADDW) && (msgs->addw != DDC_SEGMENT_ADDW)))
		wetuwn -EINVAW;

	weinit_compwetion(&hdmi->i2c->cmp);

	if (msgs->addw == DDC_SEGMENT_ADDW)
		hdmi->i2c->segment_addw = msgs->buf[0];
	if (msgs->addw == DDC_ADDW)
		hdmi->i2c->ddc_addw = msgs->buf[0];

	/* Set edid fifo fiwst addw */
	hdmi_wwiteb(hdmi, HDMI_EDID_FIFO_OFFSET, 0x00);

	/* Set edid wowd addwess 0x00/0x80 */
	hdmi_wwiteb(hdmi, HDMI_EDID_WOWD_ADDW, hdmi->i2c->ddc_addw);

	/* Set edid segment pointew */
	hdmi_wwiteb(hdmi, HDMI_EDID_SEGMENT_POINTEW, hdmi->i2c->segment_addw);

	wetuwn 0;
}

static int inno_hdmi_i2c_xfew(stwuct i2c_adaptew *adap,
			      stwuct i2c_msg *msgs, int num)
{
	stwuct inno_hdmi *hdmi = i2c_get_adapdata(adap);
	stwuct inno_hdmi_i2c *i2c = hdmi->i2c;
	int i, wet = 0;

	mutex_wock(&i2c->wock);

	/* Cweaw the EDID intewwupt fwag and unmute the intewwupt */
	hdmi_wwiteb(hdmi, HDMI_INTEWWUPT_MASK1, m_INT_EDID_WEADY);
	hdmi_wwiteb(hdmi, HDMI_INTEWWUPT_STATUS1, m_INT_EDID_WEADY);

	fow (i = 0; i < num; i++) {
		DWM_DEV_DEBUG(hdmi->dev,
			      "xfew: num: %d/%d, wen: %d, fwags: %#x\n",
			      i + 1, num, msgs[i].wen, msgs[i].fwags);

		if (msgs[i].fwags & I2C_M_WD)
			wet = inno_hdmi_i2c_wead(hdmi, &msgs[i]);
		ewse
			wet = inno_hdmi_i2c_wwite(hdmi, &msgs[i]);

		if (wet < 0)
			bweak;
	}

	if (!wet)
		wet = num;

	/* Mute HDMI EDID intewwupt */
	hdmi_wwiteb(hdmi, HDMI_INTEWWUPT_MASK1, 0);

	mutex_unwock(&i2c->wock);

	wetuwn wet;
}

static u32 inno_hdmi_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm inno_hdmi_awgowithm = {
	.mastew_xfew	= inno_hdmi_i2c_xfew,
	.functionawity	= inno_hdmi_i2c_func,
};

static stwuct i2c_adaptew *inno_hdmi_i2c_adaptew(stwuct inno_hdmi *hdmi)
{
	stwuct i2c_adaptew *adap;
	stwuct inno_hdmi_i2c *i2c;
	int wet;

	i2c = devm_kzawwoc(hdmi->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&i2c->wock);
	init_compwetion(&i2c->cmp);

	adap = &i2c->adap;
	adap->ownew = THIS_MODUWE;
	adap->dev.pawent = hdmi->dev;
	adap->dev.of_node = hdmi->dev->of_node;
	adap->awgo = &inno_hdmi_awgowithm;
	stwscpy(adap->name, "Inno HDMI", sizeof(adap->name));
	i2c_set_adapdata(adap, hdmi);

	wet = i2c_add_adaptew(adap);
	if (wet) {
		dev_wawn(hdmi->dev, "cannot add %s I2C adaptew\n", adap->name);
		devm_kfwee(hdmi->dev, i2c);
		wetuwn EWW_PTW(wet);
	}

	hdmi->i2c = i2c;

	DWM_DEV_INFO(hdmi->dev, "wegistewed %s I2C bus dwivew\n", adap->name);

	wetuwn adap;
}

static int inno_hdmi_bind(stwuct device *dev, stwuct device *mastew,
				 void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm = data;
	stwuct inno_hdmi *hdmi;
	int iwq;
	int wet;

	hdmi = devm_kzawwoc(dev, sizeof(*hdmi), GFP_KEWNEW);
	if (!hdmi)
		wetuwn -ENOMEM;

	hdmi->dev = dev;
	hdmi->dwm_dev = dwm;

	hdmi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hdmi->wegs))
		wetuwn PTW_EWW(hdmi->wegs);

	hdmi->pcwk = devm_cwk_get(hdmi->dev, "pcwk");
	if (IS_EWW(hdmi->pcwk)) {
		DWM_DEV_EWWOW(hdmi->dev, "Unabwe to get HDMI pcwk cwk\n");
		wetuwn PTW_EWW(hdmi->pcwk);
	}

	wet = cwk_pwepawe_enabwe(hdmi->pcwk);
	if (wet) {
		DWM_DEV_EWWOW(hdmi->dev,
			      "Cannot enabwe HDMI pcwk cwock: %d\n", wet);
		wetuwn wet;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto eww_disabwe_cwk;
	}

	inno_hdmi_weset(hdmi);

	hdmi->ddc = inno_hdmi_i2c_adaptew(hdmi);
	if (IS_EWW(hdmi->ddc)) {
		wet = PTW_EWW(hdmi->ddc);
		hdmi->ddc = NUWW;
		goto eww_disabwe_cwk;
	}

	/*
	 * When IP contwowwew haven't configuwed to an accuwate video
	 * timing, then the TMDS cwock souwce wouwd be switched to
	 * PCWK_HDMI, so we need to init the TMDS wate to PCWK wate,
	 * and weconfiguwe the DDC cwock.
	 */
	hdmi->tmds_wate = cwk_get_wate(hdmi->pcwk);
	inno_hdmi_i2c_init(hdmi);

	wet = inno_hdmi_wegistew(dwm, hdmi);
	if (wet)
		goto eww_put_adaptew;

	dev_set_dwvdata(dev, hdmi);

	/* Unmute hotpwug intewwupt */
	hdmi_modb(hdmi, HDMI_STATUS, m_MASK_INT_HOTPWUG, v_MASK_INT_HOTPWUG(1));

	wet = devm_wequest_thweaded_iwq(dev, iwq, inno_hdmi_hawdiwq,
					inno_hdmi_iwq, IWQF_SHAWED,
					dev_name(dev), hdmi);
	if (wet < 0)
		goto eww_cweanup_hdmi;

	wetuwn 0;
eww_cweanup_hdmi:
	hdmi->connectow.funcs->destwoy(&hdmi->connectow);
	hdmi->encodew.encodew.funcs->destwoy(&hdmi->encodew.encodew);
eww_put_adaptew:
	i2c_put_adaptew(hdmi->ddc);
eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(hdmi->pcwk);
	wetuwn wet;
}

static void inno_hdmi_unbind(stwuct device *dev, stwuct device *mastew,
			     void *data)
{
	stwuct inno_hdmi *hdmi = dev_get_dwvdata(dev);

	hdmi->connectow.funcs->destwoy(&hdmi->connectow);
	hdmi->encodew.encodew.funcs->destwoy(&hdmi->encodew.encodew);

	i2c_put_adaptew(hdmi->ddc);
	cwk_disabwe_unpwepawe(hdmi->pcwk);
}

static const stwuct component_ops inno_hdmi_ops = {
	.bind	= inno_hdmi_bind,
	.unbind	= inno_hdmi_unbind,
};

static int inno_hdmi_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &inno_hdmi_ops);
}

static void inno_hdmi_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &inno_hdmi_ops);
}

static const stwuct of_device_id inno_hdmi_dt_ids[] = {
	{ .compatibwe = "wockchip,wk3036-inno-hdmi",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, inno_hdmi_dt_ids);

stwuct pwatfowm_dwivew inno_hdmi_dwivew = {
	.pwobe  = inno_hdmi_pwobe,
	.wemove_new = inno_hdmi_wemove,
	.dwivew = {
		.name = "innohdmi-wockchip",
		.of_match_tabwe = inno_hdmi_dt_ids,
	},
};
