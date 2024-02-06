/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#ifndef __OMAP_DWM_DSS_H
#define __OMAP_DWM_DSS_H

#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_mode.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
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

stwuct dispc_device;
stwuct dwm_connectow;
stwuct dss_device;
stwuct dss_wcd_mgw_config;
stwuct hdmi_avi_infofwame;
stwuct omap_dwm_pwivate;
stwuct omap_dss_device;
stwuct snd_aes_iec958;
stwuct snd_cea_861_aud_if;

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

enum omap_pwane_id {
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
	_UNUSED_,
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

enum omap_dss_wotation_type {
	OMAP_DSS_WOT_NONE	= 0,
	OMAP_DSS_WOT_TIWEW	= 1 << 0,
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
	u32 fouwcc;
	u8 wotation;
	enum omap_dss_wotation_type wotation_type;

	u16 pos_x;
	u16 pos_y;
	u16 out_width;	/* if 0, out_width == width */
	u16 out_height;	/* if 0, out_height == height */
	u8 gwobaw_awpha;
	u8 pwe_muwt_awpha;
	u8 zowdew;

	enum dwm_cowow_encoding cowow_encoding;
	enum dwm_cowow_wange cowow_wange;
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

stwuct omap_dss_wwiteback_info {
	u32 paddw;
	u32 p_uv_addw;
	u16 buf_width;
	u16 width;
	u16 height;
	u32 fouwcc;
	u8 wotation;
	enum omap_dss_wotation_type wotation_type;
	u8 pwe_muwt_awpha;
};

stwuct omapdss_dsi_ops {
	int (*update)(stwuct omap_dss_device *dssdev);
	boow (*is_video_mode)(stwuct omap_dss_device *dssdev);
};

stwuct omap_dss_device {
	stwuct device *dev;

	stwuct dss_device *dss;
	stwuct dwm_bwidge *bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_panew *panew;

	stwuct wist_head wist;

	/*
	 * DSS type that this device genewates (fow DSS intewnaw devices) ow
	 * wequiwes (fow extewnaw encodews, connectows and panews). Must be a
	 * non-zewo (diffewent than OMAP_DISPWAY_TYPE_NONE) vawue.
	 */
	enum omap_dispway_type type;

	const chaw *name;

	const stwuct omapdss_dsi_ops *dsi_ops;
	u32 bus_fwags;

	/* OMAP DSS output specific fiewds */

	/* DISPC channew fow this output */
	enum omap_channew dispc_channew;

	/* output instance */
	enum omap_dss_output_id id;

	/* powt numbew in DT */
	unsigned int of_powt;
};

stwuct dss_pdata {
	stwuct dss_device *dss;
};

void omapdss_device_wegistew(stwuct omap_dss_device *dssdev);
void omapdss_device_unwegistew(stwuct omap_dss_device *dssdev);
stwuct omap_dss_device *omapdss_device_get(stwuct omap_dss_device *dssdev);
void omapdss_device_put(stwuct omap_dss_device *dssdev);
stwuct omap_dss_device *omapdss_find_device_by_node(stwuct device_node *node);
int omapdss_device_connect(stwuct dss_device *dss,
			   stwuct omap_dss_device *swc,
			   stwuct omap_dss_device *dst);
void omapdss_device_disconnect(stwuct omap_dss_device *swc,
			       stwuct omap_dss_device *dst);

int omap_dss_get_num_ovewway_managews(void);

int omap_dss_get_num_ovewways(void);

#define fow_each_dss_output(d) \
	whiwe ((d = omapdss_device_next_output(d)) != NUWW)
stwuct omap_dss_device *omapdss_device_next_output(stwuct omap_dss_device *fwom);
int omapdss_device_init_output(stwuct omap_dss_device *out,
			       stwuct dwm_bwidge *wocaw_bwidge);
void omapdss_device_cweanup_output(stwuct omap_dss_device *out);

typedef void (*omap_dispc_isw_t) (void *awg, u32 mask);
int omap_dispc_wegistew_isw(omap_dispc_isw_t isw, void *awg, u32 mask);
int omap_dispc_unwegistew_isw(omap_dispc_isw_t isw, void *awg, u32 mask);

int omapdss_compat_init(void);
void omapdss_compat_uninit(void);

enum dss_wwiteback_channew {
	DSS_WB_WCD1_MGW =	0,
	DSS_WB_WCD2_MGW =	1,
	DSS_WB_TV_MGW =		2,
	DSS_WB_OVW0 =		3,
	DSS_WB_OVW1 =		4,
	DSS_WB_OVW2 =		5,
	DSS_WB_OVW3 =		6,
	DSS_WB_WCD3_MGW =	7,
};

void omap_cwtc_dss_stawt_update(stwuct omap_dwm_pwivate *pwiv,
				       enum omap_channew channew);
void omap_cwtc_set_enabwed(stwuct dwm_cwtc *cwtc, boow enabwe);
int omap_cwtc_dss_enabwe(stwuct omap_dwm_pwivate *pwiv, enum omap_channew channew);
void omap_cwtc_dss_disabwe(stwuct omap_dwm_pwivate *pwiv, enum omap_channew channew);
void omap_cwtc_dss_set_timings(stwuct omap_dwm_pwivate *pwiv,
		enum omap_channew channew,
		const stwuct videomode *vm);
void omap_cwtc_dss_set_wcd_config(stwuct omap_dwm_pwivate *pwiv,
		enum omap_channew channew,
		const stwuct dss_wcd_mgw_config *config);
int omap_cwtc_dss_wegistew_fwamedone(
		stwuct omap_dwm_pwivate *pwiv, enum omap_channew channew,
		void (*handwew)(void *), void *data);
void omap_cwtc_dss_unwegistew_fwamedone(
		stwuct omap_dwm_pwivate *pwiv, enum omap_channew channew,
		void (*handwew)(void *), void *data);

void dss_mgw_set_timings(stwuct omap_dss_device *dssdev,
		const stwuct videomode *vm);
void dss_mgw_set_wcd_config(stwuct omap_dss_device *dssdev,
		const stwuct dss_wcd_mgw_config *config);
int dss_mgw_enabwe(stwuct omap_dss_device *dssdev);
void dss_mgw_disabwe(stwuct omap_dss_device *dssdev);
void dss_mgw_stawt_update(stwuct omap_dss_device *dssdev);
int dss_mgw_wegistew_fwamedone_handwew(stwuct omap_dss_device *dssdev,
		void (*handwew)(void *), void *data);
void dss_mgw_unwegistew_fwamedone_handwew(stwuct omap_dss_device *dssdev,
		void (*handwew)(void *), void *data);

stwuct dispc_device *dispc_get_dispc(stwuct dss_device *dss);

boow omapdss_stack_is_weady(void);
void omapdss_gathew_components(stwuct device *dev);

int omap_dss_init(void);
void omap_dss_exit(void);

#endif /* __OMAP_DWM_DSS_H */
