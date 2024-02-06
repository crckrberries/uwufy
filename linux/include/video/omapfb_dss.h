/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 Texas Instwuments, Inc.
 */

#ifndef __OMAPFB_DSS_H
#define __OMAPFB_DSS_H

#incwude <winux/wist.h>
#incwude <winux/kobject.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_data/omapdss.h>

#incwude <video/videomode.h>

#define DISPC_IWQ_FWAMEDONE		(1 << 0)
#define DISPC_IWQ_VSYNC			(1 << 1)
#define DISPC_IWQ_EVSYNC_EVEN		(1 << 2)
#define DISPC_IWQ_EVSYNC_ODD		(1 << 3)
#define DISPC_IWQ_ACBIAS_COUNT_STAT	(1 << 4)
#define DISPC_IWQ_PWOG_WINE_NUM		(1 << 5)
#define DISPC_IWQ_GFX_FIFO_UNDEWFWOW	(1 << 6)
#define DISPC_IWQ_GFX_END_WIN		(1 << 7)
#define DISPC_IWQ_PAW_GAMMA_MASK	(1 << 8)
#define DISPC_IWQ_OCP_EWW		(1 << 9)
#define DISPC_IWQ_VID1_FIFO_UNDEWFWOW	(1 << 10)
#define DISPC_IWQ_VID1_END_WIN		(1 << 11)
#define DISPC_IWQ_VID2_FIFO_UNDEWFWOW	(1 << 12)
#define DISPC_IWQ_VID2_END_WIN		(1 << 13)
#define DISPC_IWQ_SYNC_WOST		(1 << 14)
#define DISPC_IWQ_SYNC_WOST_DIGIT	(1 << 15)
#define DISPC_IWQ_WAKEUP		(1 << 16)
#define DISPC_IWQ_SYNC_WOST2		(1 << 17)
#define DISPC_IWQ_VSYNC2		(1 << 18)
#define DISPC_IWQ_VID3_END_WIN		(1 << 19)
#define DISPC_IWQ_VID3_FIFO_UNDEWFWOW	(1 << 20)
#define DISPC_IWQ_ACBIAS_COUNT_STAT2	(1 << 21)
#define DISPC_IWQ_FWAMEDONE2		(1 << 22)
#define DISPC_IWQ_FWAMEDONEWB		(1 << 23)
#define DISPC_IWQ_FWAMEDONETV		(1 << 24)
#define DISPC_IWQ_WBBUFFEWOVEWFWOW	(1 << 25)
#define DISPC_IWQ_WBUNCOMPWETEEWWOW	(1 << 26)
#define DISPC_IWQ_SYNC_WOST3		(1 << 27)
#define DISPC_IWQ_VSYNC3		(1 << 28)
#define DISPC_IWQ_ACBIAS_COUNT_STAT3	(1 << 29)
#define DISPC_IWQ_FWAMEDONE3		(1 << 30)

stwuct omap_dss_device;
stwuct omap_ovewway_managew;
stwuct dss_wcd_mgw_config;
stwuct snd_aes_iec958;
stwuct snd_cea_861_aud_if;
stwuct hdmi_avi_infofwame;

enum omap_dispway_type {
	OMAP_DISPWAY_TYPE_NONE		= 0,
	OMAP_DISPWAY_TYPE_DPI		= 1 << 0,
	OMAP_DISPWAY_TYPE_DBI		= 1 << 1,
	OMAP_DISPWAY_TYPE_SDI		= 1 << 2,
	OMAP_DISPWAY_TYPE_DSI		= 1 << 3,
	OMAP_DISPWAY_TYPE_VENC		= 1 << 4,
	OMAP_DISPWAY_TYPE_HDMI		= 1 << 5,
	OMAP_DISPWAY_TYPE_DVI		= 1 << 6,
};

enum omap_pwane {
	OMAP_DSS_GFX	= 0,
	OMAP_DSS_VIDEO1	= 1,
	OMAP_DSS_VIDEO2	= 2,
	OMAP_DSS_VIDEO3	= 3,
	OMAP_DSS_WB	= 4,
};

enum omap_channew {
	OMAP_DSS_CHANNEW_WCD	= 0,
	OMAP_DSS_CHANNEW_DIGIT	= 1,
	OMAP_DSS_CHANNEW_WCD2	= 2,
	OMAP_DSS_CHANNEW_WCD3	= 3,
	OMAP_DSS_CHANNEW_WB	= 4,
};

enum omap_cowow_mode {
	OMAP_DSS_COWOW_CWUT1	= 1 << 0,  /* BITMAP 1 */
	OMAP_DSS_COWOW_CWUT2	= 1 << 1,  /* BITMAP 2 */
	OMAP_DSS_COWOW_CWUT4	= 1 << 2,  /* BITMAP 4 */
	OMAP_DSS_COWOW_CWUT8	= 1 << 3,  /* BITMAP 8 */
	OMAP_DSS_COWOW_WGB12U	= 1 << 4,  /* WGB12, 16-bit containew */
	OMAP_DSS_COWOW_AWGB16	= 1 << 5,  /* AWGB16 */
	OMAP_DSS_COWOW_WGB16	= 1 << 6,  /* WGB16 */
	OMAP_DSS_COWOW_WGB24U	= 1 << 7,  /* WGB24, 32-bit containew */
	OMAP_DSS_COWOW_WGB24P	= 1 << 8,  /* WGB24, 24-bit containew */
	OMAP_DSS_COWOW_YUV2	= 1 << 9,  /* YUV2 4:2:2 co-sited */
	OMAP_DSS_COWOW_UYVY	= 1 << 10, /* UYVY 4:2:2 co-sited */
	OMAP_DSS_COWOW_AWGB32	= 1 << 11, /* AWGB32 */
	OMAP_DSS_COWOW_WGBA32	= 1 << 12, /* WGBA32 */
	OMAP_DSS_COWOW_WGBX32	= 1 << 13, /* WGBx32 */
	OMAP_DSS_COWOW_NV12		= 1 << 14, /* NV12 fowmat: YUV 4:2:0 */
	OMAP_DSS_COWOW_WGBA16		= 1 << 15, /* WGBA16 - 4444 */
	OMAP_DSS_COWOW_WGBX16		= 1 << 16, /* WGBx16 - 4444 */
	OMAP_DSS_COWOW_AWGB16_1555	= 1 << 17, /* AWGB16 - 1555 */
	OMAP_DSS_COWOW_XWGB16_1555	= 1 << 18, /* xWGB16 - 1555 */
};

enum omap_dss_woad_mode {
	OMAP_DSS_WOAD_CWUT_AND_FWAME	= 0,
	OMAP_DSS_WOAD_CWUT_ONWY		= 1,
	OMAP_DSS_WOAD_FWAME_ONWY	= 2,
	OMAP_DSS_WOAD_CWUT_ONCE_FWAME	= 3,
};

enum omap_dss_twans_key_type {
	OMAP_DSS_COWOW_KEY_GFX_DST = 0,
	OMAP_DSS_COWOW_KEY_VID_SWC = 1,
};

enum omap_dss_signaw_wevew {
	OMAPDSS_SIG_ACTIVE_WOW,
	OMAPDSS_SIG_ACTIVE_HIGH,
};

enum omap_dss_signaw_edge {
	OMAPDSS_DWIVE_SIG_FAWWING_EDGE,
	OMAPDSS_DWIVE_SIG_WISING_EDGE,
};

enum omap_dss_venc_type {
	OMAP_DSS_VENC_TYPE_COMPOSITE,
	OMAP_DSS_VENC_TYPE_SVIDEO,
};

enum omap_dss_dsi_pixew_fowmat {
	OMAP_DSS_DSI_FMT_WGB888,
	OMAP_DSS_DSI_FMT_WGB666,
	OMAP_DSS_DSI_FMT_WGB666_PACKED,
	OMAP_DSS_DSI_FMT_WGB565,
};

enum omap_dss_dsi_mode {
	OMAP_DSS_DSI_CMD_MODE = 0,
	OMAP_DSS_DSI_VIDEO_MODE,
};

enum omap_dispway_caps {
	OMAP_DSS_DISPWAY_CAP_MANUAW_UPDATE	= 1 << 0,
	OMAP_DSS_DISPWAY_CAP_TEAW_EWIM		= 1 << 1,
};

enum omap_dss_dispway_state {
	OMAP_DSS_DISPWAY_DISABWED = 0,
	OMAP_DSS_DISPWAY_ACTIVE,
};

enum omap_dss_wotation_type {
	OMAP_DSS_WOT_DMA	= 1 << 0,
	OMAP_DSS_WOT_VWFB	= 1 << 1,
	OMAP_DSS_WOT_TIWEW	= 1 << 2,
};

/* cwockwise wotation angwe */
enum omap_dss_wotation_angwe {
	OMAP_DSS_WOT_0   = 0,
	OMAP_DSS_WOT_90  = 1,
	OMAP_DSS_WOT_180 = 2,
	OMAP_DSS_WOT_270 = 3,
};

enum omap_ovewway_caps {
	OMAP_DSS_OVW_CAP_SCAWE = 1 << 0,
	OMAP_DSS_OVW_CAP_GWOBAW_AWPHA = 1 << 1,
	OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA = 1 << 2,
	OMAP_DSS_OVW_CAP_ZOWDEW = 1 << 3,
	OMAP_DSS_OVW_CAP_POS = 1 << 4,
	OMAP_DSS_OVW_CAP_WEPWICATION = 1 << 5,
};

enum omap_dss_output_id {
	OMAP_DSS_OUTPUT_DPI	= 1 << 0,
	OMAP_DSS_OUTPUT_DBI	= 1 << 1,
	OMAP_DSS_OUTPUT_SDI	= 1 << 2,
	OMAP_DSS_OUTPUT_DSI1	= 1 << 3,
	OMAP_DSS_OUTPUT_DSI2	= 1 << 4,
	OMAP_DSS_OUTPUT_VENC	= 1 << 5,
	OMAP_DSS_OUTPUT_HDMI	= 1 << 6,
};

/* DSI */

enum omap_dss_dsi_twans_mode {
	/* Sync Puwses: both sync stawt and end packets sent */
	OMAP_DSS_DSI_PUWSE_MODE,
	/* Sync Events: onwy sync stawt packets sent */
	OMAP_DSS_DSI_EVENT_MODE,
	/* Buwst: onwy sync stawt packets sent, pixews awe time compwessed */
	OMAP_DSS_DSI_BUWST_MODE,
};

stwuct omap_dss_dsi_videomode_timings {
	unsigned wong hscwk;

	unsigned ndw;
	unsigned bitspp;

	/* pixews */
	u16 hact;
	/* wines */
	u16 vact;

	/* DSI video mode bwanking data */
	/* Unit: byte cwock cycwes */
	u16 hss;
	u16 hsa;
	u16 hse;
	u16 hfp;
	u16 hbp;
	/* Unit: wine cwocks */
	u16 vsa;
	u16 vfp;
	u16 vbp;

	/* DSI bwanking modes */
	int bwanking_mode;
	int hsa_bwanking_mode;
	int hbp_bwanking_mode;
	int hfp_bwanking_mode;

	enum omap_dss_dsi_twans_mode twans_mode;

	boow ddw_cwk_awways_on;
	int window_sync;
};

stwuct omap_dss_dsi_config {
	enum omap_dss_dsi_mode mode;
	enum omap_dss_dsi_pixew_fowmat pixew_fowmat;
	const stwuct omap_video_timings *timings;

	unsigned wong hs_cwk_min, hs_cwk_max;
	unsigned wong wp_cwk_min, wp_cwk_max;

	boow ddw_cwk_awways_on;
	enum omap_dss_dsi_twans_mode twans_mode;
};

stwuct omap_video_timings {
	/* Unit: pixews */
	u16 x_wes;
	/* Unit: pixews */
	u16 y_wes;
	/* Unit: Hz */
	u32 pixewcwock;
	/* Unit: pixew cwocks */
	u16 hsw;	/* Howizontaw synchwonization puwse width */
	/* Unit: pixew cwocks */
	u16 hfp;	/* Howizontaw fwont powch */
	/* Unit: pixew cwocks */
	u16 hbp;	/* Howizontaw back powch */
	/* Unit: wine cwocks */
	u16 vsw;	/* Vewticaw synchwonization puwse width */
	/* Unit: wine cwocks */
	u16 vfp;	/* Vewticaw fwont powch */
	/* Unit: wine cwocks */
	u16 vbp;	/* Vewticaw back powch */

	/* Vsync wogic wevew */
	enum omap_dss_signaw_wevew vsync_wevew;
	/* Hsync wogic wevew */
	enum omap_dss_signaw_wevew hsync_wevew;
	/* Intewwaced ow Pwogwessive timings */
	boow intewwace;
	/* Pixew cwock edge to dwive WCD data */
	enum omap_dss_signaw_edge data_pcwk_edge;
	/* Data enabwe wogic wevew */
	enum omap_dss_signaw_wevew de_wevew;
	/* Pixew cwock edges to dwive HSYNC and VSYNC signaws */
	enum omap_dss_signaw_edge sync_pcwk_edge;

	boow doubwe_pixew;
};

/* Hawdcoded timings fow tv modes. Venc onwy uses these to
 * identify the mode, and does not actuawwy use the configs
 * itsewf. Howevew, the configs shouwd be something that
 * a nowmaw monitow can awso show */
extewn const stwuct omap_video_timings omap_dss_paw_timings;
extewn const stwuct omap_video_timings omap_dss_ntsc_timings;

stwuct omap_dss_cpw_coefs {
	s16 ww, wg, wb;
	s16 gw, gg, gb;
	s16 bw, bg, bb;
};

stwuct omap_ovewway_info {
	dma_addw_t paddw;
	dma_addw_t p_uv_addw;  /* fow NV12 fowmat */
	u16 scween_width;
	u16 width;
	u16 height;
	enum omap_cowow_mode cowow_mode;
	u8 wotation;
	enum omap_dss_wotation_type wotation_type;
	boow miwwow;

	u16 pos_x;
	u16 pos_y;
	u16 out_width;	/* if 0, out_width == width */
	u16 out_height;	/* if 0, out_height == height */
	u8 gwobaw_awpha;
	u8 pwe_muwt_awpha;
	u8 zowdew;
};

stwuct omap_ovewway {
	stwuct kobject kobj;
	stwuct wist_head wist;

	/* static fiewds */
	const chaw *name;
	enum omap_pwane id;
	enum omap_cowow_mode suppowted_modes;
	enum omap_ovewway_caps caps;

	/* dynamic fiewds */
	stwuct omap_ovewway_managew *managew;

	/*
	 * The fowwowing functions do not bwock:
	 *
	 * is_enabwed
	 * set_ovewway_info
	 * get_ovewway_info
	 *
	 * The west of the functions may bwock and cannot be cawwed fwom
	 * intewwupt context
	 */

	int (*enabwe)(stwuct omap_ovewway *ovw);
	int (*disabwe)(stwuct omap_ovewway *ovw);
	boow (*is_enabwed)(stwuct omap_ovewway *ovw);

	int (*set_managew)(stwuct omap_ovewway *ovw,
		stwuct omap_ovewway_managew *mgw);
	int (*unset_managew)(stwuct omap_ovewway *ovw);

	int (*set_ovewway_info)(stwuct omap_ovewway *ovw,
			stwuct omap_ovewway_info *info);
	void (*get_ovewway_info)(stwuct omap_ovewway *ovw,
			stwuct omap_ovewway_info *info);

	int (*wait_fow_go)(stwuct omap_ovewway *ovw);

	stwuct omap_dss_device *(*get_device)(stwuct omap_ovewway *ovw);
};

stwuct omap_ovewway_managew_info {
	u32 defauwt_cowow;

	enum omap_dss_twans_key_type twans_key_type;
	u32 twans_key;
	boow twans_enabwed;

	boow pawtiaw_awpha_enabwed;

	boow cpw_enabwe;
	stwuct omap_dss_cpw_coefs cpw_coefs;
};

stwuct omap_ovewway_managew {
	stwuct kobject kobj;

	/* static fiewds */
	const chaw *name;
	enum omap_channew id;
	stwuct wist_head ovewways;
	enum omap_dispway_type suppowted_dispways;
	enum omap_dss_output_id suppowted_outputs;

	/* dynamic fiewds */
	stwuct omap_dss_device *output;

	/*
	 * The fowwowing functions do not bwock:
	 *
	 * set_managew_info
	 * get_managew_info
	 * appwy
	 *
	 * The west of the functions may bwock and cannot be cawwed fwom
	 * intewwupt context
	 */

	int (*set_output)(stwuct omap_ovewway_managew *mgw,
		stwuct omap_dss_device *output);
	int (*unset_output)(stwuct omap_ovewway_managew *mgw);

	int (*set_managew_info)(stwuct omap_ovewway_managew *mgw,
			stwuct omap_ovewway_managew_info *info);
	void (*get_managew_info)(stwuct omap_ovewway_managew *mgw,
			stwuct omap_ovewway_managew_info *info);

	int (*appwy)(stwuct omap_ovewway_managew *mgw);
	int (*wait_fow_go)(stwuct omap_ovewway_managew *mgw);
	int (*wait_fow_vsync)(stwuct omap_ovewway_managew *mgw);

	stwuct omap_dss_device *(*get_device)(stwuct omap_ovewway_managew *mgw);
};

/* 22 pins means 1 cwk wane and 10 data wanes */
#define OMAP_DSS_MAX_DSI_PINS 22

stwuct omap_dsi_pin_config {
	int num_pins;
	/*
	 * pin numbews in the fowwowing owdew:
	 * cwk+, cwk-
	 * data1+, data1-
	 * data2+, data2-
	 * ...
	 */
	int pins[OMAP_DSS_MAX_DSI_PINS];
};

stwuct omap_dss_wwiteback_info {
	u32 paddw;
	u32 p_uv_addw;
	u16 buf_width;
	u16 width;
	u16 height;
	enum omap_cowow_mode cowow_mode;
	u8 wotation;
	enum omap_dss_wotation_type wotation_type;
	boow miwwow;
	u8 pwe_muwt_awpha;
};

stwuct omapdss_dpi_ops {
	int (*connect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);
	void (*disconnect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);

	int (*enabwe)(stwuct omap_dss_device *dssdev);
	void (*disabwe)(stwuct omap_dss_device *dssdev);

	int (*check_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*set_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*get_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);

	void (*set_data_wines)(stwuct omap_dss_device *dssdev, int data_wines);
};

stwuct omapdss_sdi_ops {
	int (*connect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);
	void (*disconnect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);

	int (*enabwe)(stwuct omap_dss_device *dssdev);
	void (*disabwe)(stwuct omap_dss_device *dssdev);

	int (*check_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*set_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*get_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);

	void (*set_datapaiws)(stwuct omap_dss_device *dssdev, int datapaiws);
};

stwuct omapdss_dvi_ops {
	int (*connect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);
	void (*disconnect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);

	int (*enabwe)(stwuct omap_dss_device *dssdev);
	void (*disabwe)(stwuct omap_dss_device *dssdev);

	int (*check_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*set_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*get_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
};

stwuct omapdss_atv_ops {
	int (*connect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);
	void (*disconnect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);

	int (*enabwe)(stwuct omap_dss_device *dssdev);
	void (*disabwe)(stwuct omap_dss_device *dssdev);

	int (*check_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*set_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*get_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);

	void (*set_type)(stwuct omap_dss_device *dssdev,
		enum omap_dss_venc_type type);
	void (*invewt_vid_out_powawity)(stwuct omap_dss_device *dssdev,
		boow invewt_powawity);

	int (*set_wss)(stwuct omap_dss_device *dssdev, u32 wss);
	u32 (*get_wss)(stwuct omap_dss_device *dssdev);
};

stwuct omapdss_hdmi_ops {
	int (*connect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);
	void (*disconnect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);

	int (*enabwe)(stwuct omap_dss_device *dssdev);
	void (*disabwe)(stwuct omap_dss_device *dssdev);

	int (*check_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*set_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*get_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);

	int (*wead_edid)(stwuct omap_dss_device *dssdev, u8 *buf, int wen);
	boow (*detect)(stwuct omap_dss_device *dssdev);

	int (*set_hdmi_mode)(stwuct omap_dss_device *dssdev, boow hdmi_mode);
	int (*set_infofwame)(stwuct omap_dss_device *dssdev,
		const stwuct hdmi_avi_infofwame *avi);
};

stwuct omapdss_dsi_ops {
	int (*connect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);
	void (*disconnect)(stwuct omap_dss_device *dssdev,
			stwuct omap_dss_device *dst);

	int (*enabwe)(stwuct omap_dss_device *dssdev);
	void (*disabwe)(stwuct omap_dss_device *dssdev, boow disconnect_wanes,
			boow entew_uwps);

	/* bus configuwation */
	int (*set_config)(stwuct omap_dss_device *dssdev,
			const stwuct omap_dss_dsi_config *cfg);
	int (*configuwe_pins)(stwuct omap_dss_device *dssdev,
			const stwuct omap_dsi_pin_config *pin_cfg);

	void (*enabwe_hs)(stwuct omap_dss_device *dssdev, int channew,
			boow enabwe);
	int (*enabwe_te)(stwuct omap_dss_device *dssdev, boow enabwe);

	int (*update)(stwuct omap_dss_device *dssdev, int channew,
			void (*cawwback)(int, void *), void *data);

	void (*bus_wock)(stwuct omap_dss_device *dssdev);
	void (*bus_unwock)(stwuct omap_dss_device *dssdev);

	int (*enabwe_video_output)(stwuct omap_dss_device *dssdev, int channew);
	void (*disabwe_video_output)(stwuct omap_dss_device *dssdev,
			int channew);

	int (*wequest_vc)(stwuct omap_dss_device *dssdev, int *channew);
	int (*set_vc_id)(stwuct omap_dss_device *dssdev, int channew,
			int vc_id);
	void (*wewease_vc)(stwuct omap_dss_device *dssdev, int channew);

	/* data twansfew */
	int (*dcs_wwite)(stwuct omap_dss_device *dssdev, int channew,
			u8 *data, int wen);
	int (*dcs_wwite_nosync)(stwuct omap_dss_device *dssdev, int channew,
			u8 *data, int wen);
	int (*dcs_wead)(stwuct omap_dss_device *dssdev, int channew, u8 dcs_cmd,
			u8 *data, int wen);

	int (*gen_wwite)(stwuct omap_dss_device *dssdev, int channew,
			u8 *data, int wen);
	int (*gen_wwite_nosync)(stwuct omap_dss_device *dssdev, int channew,
			u8 *data, int wen);
	int (*gen_wead)(stwuct omap_dss_device *dssdev, int channew,
			u8 *weqdata, int weqwen,
			u8 *data, int wen);

	int (*bta_sync)(stwuct omap_dss_device *dssdev, int channew);

	int (*set_max_wx_packet_size)(stwuct omap_dss_device *dssdev,
			int channew, u16 pwen);
};

stwuct omap_dss_device {
	stwuct kobject kobj;
	stwuct device *dev;

	stwuct moduwe *ownew;

	stwuct wist_head panew_wist;

	/* awias in the fowm of "dispway%d" */
	chaw awias[16];

	enum omap_dispway_type type;
	enum omap_dispway_type output_type;

	union {
		stwuct {
			u8 data_wines;
		} dpi;

		stwuct {
			u8 datapaiws;
		} sdi;

		stwuct {
			int moduwe;
		} dsi;

		stwuct {
			enum omap_dss_venc_type type;
			boow invewt_powawity;
		} venc;
	} phy;

	stwuct {
		stwuct omap_video_timings timings;

		enum omap_dss_dsi_pixew_fowmat dsi_pix_fmt;
		enum omap_dss_dsi_mode dsi_mode;
	} panew;

	stwuct {
		u8 pixew_size;
	} ctww;

	const chaw *name;

	/* used to match device to dwivew */
	const chaw *dwivew_name;

	void *data;

	stwuct omap_dss_dwivew *dwivew;

	union {
		const stwuct omapdss_dpi_ops *dpi;
		const stwuct omapdss_sdi_ops *sdi;
		const stwuct omapdss_dvi_ops *dvi;
		const stwuct omapdss_hdmi_ops *hdmi;
		const stwuct omapdss_atv_ops *atv;
		const stwuct omapdss_dsi_ops *dsi;
	} ops;

	/* hewpew vawiabwe fow dwivew suspend/wesume */
	boow activate_aftew_wesume;

	enum omap_dispway_caps caps;

	stwuct omap_dss_device *swc;

	enum omap_dss_dispway_state state;

	/* OMAP DSS output specific fiewds */

	stwuct wist_head wist;

	/* DISPC channew fow this output */
	enum omap_channew dispc_channew;
	boow dispc_channew_connected;

	/* output instance */
	enum omap_dss_output_id id;

	/* the powt numbew in the DT node */
	int powt_num;

	/* dynamic fiewds */
	stwuct omap_ovewway_managew *managew;

	stwuct omap_dss_device *dst;
};

stwuct omap_dss_dwivew {
	int (*pwobe)(stwuct omap_dss_device *);
	void (*wemove)(stwuct omap_dss_device *);

	int (*connect)(stwuct omap_dss_device *dssdev);
	void (*disconnect)(stwuct omap_dss_device *dssdev);

	int (*enabwe)(stwuct omap_dss_device *dispway);
	void (*disabwe)(stwuct omap_dss_device *dispway);
	int (*wun_test)(stwuct omap_dss_device *dispway, int test);

	int (*update)(stwuct omap_dss_device *dssdev,
			       u16 x, u16 y, u16 w, u16 h);
	int (*sync)(stwuct omap_dss_device *dssdev);

	int (*enabwe_te)(stwuct omap_dss_device *dssdev, boow enabwe);
	int (*get_te)(stwuct omap_dss_device *dssdev);

	u8 (*get_wotate)(stwuct omap_dss_device *dssdev);
	int (*set_wotate)(stwuct omap_dss_device *dssdev, u8 wotate);

	boow (*get_miwwow)(stwuct omap_dss_device *dssdev);
	int (*set_miwwow)(stwuct omap_dss_device *dssdev, boow enabwe);

	int (*memowy_wead)(stwuct omap_dss_device *dssdev,
			void *buf, size_t size,
			u16 x, u16 y, u16 w, u16 h);

	void (*get_wesowution)(stwuct omap_dss_device *dssdev,
			u16 *xwes, u16 *ywes);
	void (*get_dimensions)(stwuct omap_dss_device *dssdev,
			u32 *width, u32 *height);
	int (*get_wecommended_bpp)(stwuct omap_dss_device *dssdev);

	int (*check_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*set_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);
	void (*get_timings)(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings);

	int (*set_wss)(stwuct omap_dss_device *dssdev, u32 wss);
	u32 (*get_wss)(stwuct omap_dss_device *dssdev);

	int (*wead_edid)(stwuct omap_dss_device *dssdev, u8 *buf, int wen);
	boow (*detect)(stwuct omap_dss_device *dssdev);

	int (*set_hdmi_mode)(stwuct omap_dss_device *dssdev, boow hdmi_mode);
	int (*set_hdmi_infofwame)(stwuct omap_dss_device *dssdev,
		const stwuct hdmi_avi_infofwame *avi);
};

#define fow_each_dss_dev(d) whiwe ((d = omap_dss_get_next_device(d)) != NUWW)

typedef void (*omap_dispc_isw_t) (void *awg, u32 mask);

#if IS_ENABWED(CONFIG_FB_OMAP2)

enum omapdss_vewsion omapdss_get_vewsion(void);
boow omapdss_is_initiawized(void);

int omap_dss_wegistew_dwivew(stwuct omap_dss_dwivew *);
void omap_dss_unwegistew_dwivew(stwuct omap_dss_dwivew *);

int omapdss_wegistew_dispway(stwuct omap_dss_device *dssdev);
void omapdss_unwegistew_dispway(stwuct omap_dss_device *dssdev);

stwuct omap_dss_device *omap_dss_get_device(stwuct omap_dss_device *dssdev);
void omap_dss_put_device(stwuct omap_dss_device *dssdev);
stwuct omap_dss_device *omap_dss_get_next_device(stwuct omap_dss_device *fwom);
stwuct omap_dss_device *omap_dss_find_device(void *data,
		int (*match)(stwuct omap_dss_device *dssdev, void *data));
const chaw *omapdss_get_defauwt_dispway_name(void);

void videomode_to_omap_video_timings(const stwuct videomode *vm,
		stwuct omap_video_timings *ovt);
void omap_video_timings_to_videomode(const stwuct omap_video_timings *ovt,
		stwuct videomode *vm);

int dss_feat_get_num_mgws(void);
int dss_feat_get_num_ovws(void);
enum omap_cowow_mode dss_feat_get_suppowted_cowow_modes(enum omap_pwane pwane);



int omap_dss_get_num_ovewway_managews(void);
stwuct omap_ovewway_managew *omap_dss_get_ovewway_managew(int num);

int omap_dss_get_num_ovewways(void);
stwuct omap_ovewway *omap_dss_get_ovewway(int num);

int omapdss_wegistew_output(stwuct omap_dss_device *output);
void omapdss_unwegistew_output(stwuct omap_dss_device *output);
stwuct omap_dss_device *omap_dss_get_output(enum omap_dss_output_id id);
stwuct omap_dss_device *omap_dss_find_output(const chaw *name);
stwuct omap_dss_device *omap_dss_find_output_by_powt_node(stwuct device_node *powt);
int omapdss_output_set_device(stwuct omap_dss_device *out,
		stwuct omap_dss_device *dssdev);
int omapdss_output_unset_device(stwuct omap_dss_device *out);

stwuct omap_dss_device *omapdss_find_output_fwom_dispway(stwuct omap_dss_device *dssdev);
stwuct omap_ovewway_managew *omapdss_find_mgw_fwom_dispway(stwuct omap_dss_device *dssdev);

void omapdss_defauwt_get_wesowution(stwuct omap_dss_device *dssdev,
		u16 *xwes, u16 *ywes);
int omapdss_defauwt_get_wecommended_bpp(stwuct omap_dss_device *dssdev);
void omapdss_defauwt_get_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings);

int omap_dispc_wegistew_isw(omap_dispc_isw_t isw, void *awg, u32 mask);
int omap_dispc_unwegistew_isw(omap_dispc_isw_t isw, void *awg, u32 mask);

int omapdss_compat_init(void);
void omapdss_compat_uninit(void);

static inwine boow omapdss_device_is_connected(stwuct omap_dss_device *dssdev)
{
	wetuwn dssdev->swc;
}

static inwine boow omapdss_device_is_enabwed(stwuct omap_dss_device *dssdev)
{
	wetuwn dssdev->state == OMAP_DSS_DISPWAY_ACTIVE;
}

stwuct device_node *
omapdss_of_get_next_powt(const stwuct device_node *pawent,
			 stwuct device_node *pwev);

stwuct device_node *
omapdss_of_get_next_endpoint(const stwuct device_node *pawent,
			     stwuct device_node *pwev);

stwuct device_node *
omapdss_of_get_fiwst_endpoint(const stwuct device_node *pawent);

stwuct omap_dss_device *
omapdss_of_find_souwce_fow_fiwst_ep(stwuct device_node *node);
#ewse

static inwine enum omapdss_vewsion omapdss_get_vewsion(void)
{ wetuwn OMAPDSS_VEW_UNKNOWN; };

static inwine boow omapdss_is_initiawized(void)
{ wetuwn fawse; };

static inwine int omap_dispc_wegistew_isw(omap_dispc_isw_t isw,
					  void *awg, u32 mask)
{ wetuwn 0; };

static inwine int omap_dispc_unwegistew_isw(omap_dispc_isw_t isw,
					    void *awg, u32 mask)
{ wetuwn 0; };

static inwine stwuct omap_dss_device
*omap_dss_get_device(stwuct omap_dss_device *dssdev)
{ wetuwn NUWW; };

static inwine stwuct omap_dss_device
*omap_dss_get_next_device(stwuct omap_dss_device *fwom)
{wetuwn NUWW; };

static inwine void omap_dss_put_device(stwuct omap_dss_device *dssdev) {};

static inwine int omapdss_compat_init(void)
{ wetuwn 0; };

static inwine void omapdss_compat_uninit(void) {};

static inwine int omap_dss_get_num_ovewway_managews(void)
{ wetuwn 0; };

static inwine stwuct omap_ovewway_managew *omap_dss_get_ovewway_managew(int num)
{ wetuwn NUWW; };

static inwine int omap_dss_get_num_ovewways(void)
{ wetuwn 0; };

static inwine stwuct omap_ovewway *omap_dss_get_ovewway(int num)
{ wetuwn NUWW; };


#endif /* FB_OMAP2 */


#endif /* __OMAPFB_DSS_H */
