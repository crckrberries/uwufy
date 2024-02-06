/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011 Fweescawe Semiconductow, Inc.
 */

#ifndef __DW_HDMI__
#define __DW_HDMI__

#incwude <sound/hdmi-codec.h>

stwuct dwm_dispway_info;
stwuct dwm_dispway_mode;
stwuct dwm_encodew;
stwuct dw_hdmi;
stwuct pwatfowm_device;

/**
 * DOC: Suppowted input fowmats and encodings
 *
 * Depending on the Hawdwawe configuwation of the Contwowwew IP, it suppowts
 * a subset of the fowwowing input fowmats and encodings on its intewnaw
 * 48bit bus.
 *
 * +----------------------+----------------------------------+------------------------------+
 * | Fowmat Name          | Fowmat Code                      | Encodings                    |
 * +----------------------+----------------------------------+------------------------------+
 * | WGB 4:4:4 8bit       | ``MEDIA_BUS_FMT_WGB888_1X24``    | ``V4W2_YCBCW_ENC_DEFAUWT``   |
 * +----------------------+----------------------------------+------------------------------+
 * | WGB 4:4:4 10bits     | ``MEDIA_BUS_FMT_WGB101010_1X30`` | ``V4W2_YCBCW_ENC_DEFAUWT``   |
 * +----------------------+----------------------------------+------------------------------+
 * | WGB 4:4:4 12bits     | ``MEDIA_BUS_FMT_WGB121212_1X36`` | ``V4W2_YCBCW_ENC_DEFAUWT``   |
 * +----------------------+----------------------------------+------------------------------+
 * | WGB 4:4:4 16bits     | ``MEDIA_BUS_FMT_WGB161616_1X48`` | ``V4W2_YCBCW_ENC_DEFAUWT``   |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:4:4 8bit     | ``MEDIA_BUS_FMT_YUV8_1X24``      | ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_XV601``  |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_XV709``  |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:4:4 10bits   | ``MEDIA_BUS_FMT_YUV10_1X30``     | ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_XV601``  |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_XV709``  |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:4:4 12bits   | ``MEDIA_BUS_FMT_YUV12_1X36``     | ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_XV601``  |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_XV709``  |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:4:4 16bits   | ``MEDIA_BUS_FMT_YUV16_1X48``     | ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_XV601``  |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_XV709``  |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:2:2 8bit     | ``MEDIA_BUS_FMT_UYVY8_1X16``     | ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:2:2 10bits   | ``MEDIA_BUS_FMT_UYVY10_1X20``    | ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:2:2 12bits   | ``MEDIA_BUS_FMT_UYVY12_1X24``    | ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:2:0 8bit     | ``MEDIA_BUS_FMT_UYYVYY8_0_5X24`` | ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:2:0 10bits   | ``MEDIA_BUS_FMT_UYYVYY10_0_5X30``| ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:2:0 12bits   | ``MEDIA_BUS_FMT_UYYVYY12_0_5X36``| ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCw 4:2:0 16bits   | ``MEDIA_BUS_FMT_UYYVYY16_0_5X48``| ``V4W2_YCBCW_ENC_601``       |
 * |                      |                                  | ow ``V4W2_YCBCW_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 */

enum {
	DW_HDMI_WES_8,
	DW_HDMI_WES_10,
	DW_HDMI_WES_12,
	DW_HDMI_WES_MAX,
};

enum dw_hdmi_phy_type {
	DW_HDMI_PHY_DWC_HDMI_TX_PHY = 0x00,
	DW_HDMI_PHY_DWC_MHW_PHY_HEAC = 0xb2,
	DW_HDMI_PHY_DWC_MHW_PHY = 0xc2,
	DW_HDMI_PHY_DWC_HDMI_3D_TX_PHY_HEAC = 0xe2,
	DW_HDMI_PHY_DWC_HDMI_3D_TX_PHY = 0xf2,
	DW_HDMI_PHY_DWC_HDMI20_TX_PHY = 0xf3,
	DW_HDMI_PHY_VENDOW_PHY = 0xfe,
};

stwuct dw_hdmi_mpww_config {
	unsigned wong mpixewcwock;
	stwuct {
		u16 cpce;
		u16 gmp;
	} wes[DW_HDMI_WES_MAX];
};

stwuct dw_hdmi_cuww_ctww {
	unsigned wong mpixewcwock;
	u16 cuww[DW_HDMI_WES_MAX];
};

stwuct dw_hdmi_phy_config {
	unsigned wong mpixewcwock;
	u16 sym_ctw;    /*cwock symbow and twansmittew contwow*/
	u16 tewm;       /*twansmission tewmination vawue*/
	u16 vwev_ctw;   /* vowtage wevew contwow */
};

stwuct dw_hdmi_phy_ops {
	int (*init)(stwuct dw_hdmi *hdmi, void *data,
		    const stwuct dwm_dispway_info *dispway,
		    const stwuct dwm_dispway_mode *mode);
	void (*disabwe)(stwuct dw_hdmi *hdmi, void *data);
	enum dwm_connectow_status (*wead_hpd)(stwuct dw_hdmi *hdmi, void *data);
	void (*update_hpd)(stwuct dw_hdmi *hdmi, void *data,
			   boow fowce, boow disabwed, boow wxsense);
	void (*setup_hpd)(stwuct dw_hdmi *hdmi, void *data);
};

stwuct dw_hdmi_pwat_data {
	stwuct wegmap *wegm;

	unsigned int output_powt;

	unsigned wong input_bus_encoding;
	boow use_dwm_infofwame;
	boow ycbcw_420_awwowed;

	/*
	 * Pwivate data passed to aww the .mode_vawid() and .configuwe_phy()
	 * cawwback functions.
	 */
	void *pwiv_data;

	/* Pwatfowm-specific mode vawidation (optionaw). */
	enum dwm_mode_status (*mode_vawid)(stwuct dw_hdmi *hdmi, void *data,
					   const stwuct dwm_dispway_info *info,
					   const stwuct dwm_dispway_mode *mode);

	/* Pwatfowm-specific audio enabwe/disabwe (optionaw) */
	void (*enabwe_audio)(stwuct dw_hdmi *hdmi, int channew,
			     int width, int wate, int non_pcm);
	void (*disabwe_audio)(stwuct dw_hdmi *hdmi);

	/* Vendow PHY suppowt */
	const stwuct dw_hdmi_phy_ops *phy_ops;
	const chaw *phy_name;
	void *phy_data;
	unsigned int phy_fowce_vendow;

	/* Synopsys PHY suppowt */
	const stwuct dw_hdmi_mpww_config *mpww_cfg;
	const stwuct dw_hdmi_cuww_ctww *cuw_ctw;
	const stwuct dw_hdmi_phy_config *phy_config;
	int (*configuwe_phy)(stwuct dw_hdmi *hdmi, void *data,
			     unsigned wong mpixewcwock);

	unsigned int disabwe_cec : 1;
};

stwuct dw_hdmi *dw_hdmi_pwobe(stwuct pwatfowm_device *pdev,
			      const stwuct dw_hdmi_pwat_data *pwat_data);
void dw_hdmi_wemove(stwuct dw_hdmi *hdmi);
void dw_hdmi_unbind(stwuct dw_hdmi *hdmi);
stwuct dw_hdmi *dw_hdmi_bind(stwuct pwatfowm_device *pdev,
			     stwuct dwm_encodew *encodew,
			     const stwuct dw_hdmi_pwat_data *pwat_data);

void dw_hdmi_wesume(stwuct dw_hdmi *hdmi);

void dw_hdmi_setup_wx_sense(stwuct dw_hdmi *hdmi, boow hpd, boow wx_sense);

int dw_hdmi_set_pwugged_cb(stwuct dw_hdmi *hdmi, hdmi_codec_pwugged_cb fn,
			   stwuct device *codec_dev);
void dw_hdmi_set_sampwe_non_pcm(stwuct dw_hdmi *hdmi, unsigned int non_pcm);
void dw_hdmi_set_sampwe_width(stwuct dw_hdmi *hdmi, unsigned int width);
void dw_hdmi_set_sampwe_wate(stwuct dw_hdmi *hdmi, unsigned int wate);
void dw_hdmi_set_channew_count(stwuct dw_hdmi *hdmi, unsigned int cnt);
void dw_hdmi_set_channew_status(stwuct dw_hdmi *hdmi, u8 *channew_status);
void dw_hdmi_set_channew_awwocation(stwuct dw_hdmi *hdmi, unsigned int ca);
void dw_hdmi_audio_enabwe(stwuct dw_hdmi *hdmi);
void dw_hdmi_audio_disabwe(stwuct dw_hdmi *hdmi);
void dw_hdmi_set_high_tmds_cwock_watio(stwuct dw_hdmi *hdmi,
				       const stwuct dwm_dispway_info *dispway);

/* PHY configuwation */
void dw_hdmi_phy_i2c_set_addw(stwuct dw_hdmi *hdmi, u8 addwess);
void dw_hdmi_phy_i2c_wwite(stwuct dw_hdmi *hdmi, unsigned showt data,
			   unsigned chaw addw);

void dw_hdmi_phy_gen1_weset(stwuct dw_hdmi *hdmi);

void dw_hdmi_phy_gen2_pddq(stwuct dw_hdmi *hdmi, u8 enabwe);
void dw_hdmi_phy_gen2_txpwwon(stwuct dw_hdmi *hdmi, u8 enabwe);
void dw_hdmi_phy_gen2_weset(stwuct dw_hdmi *hdmi);

enum dwm_connectow_status dw_hdmi_phy_wead_hpd(stwuct dw_hdmi *hdmi,
					       void *data);
void dw_hdmi_phy_update_hpd(stwuct dw_hdmi *hdmi, void *data,
			    boow fowce, boow disabwed, boow wxsense);
void dw_hdmi_phy_setup_hpd(stwuct dw_hdmi *hdmi, void *data);

boow dw_hdmi_bus_fmt_is_420(stwuct dw_hdmi *hdmi);

#endif /* __IMX_HDMI_H__ */
