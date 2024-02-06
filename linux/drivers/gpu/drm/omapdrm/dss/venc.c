// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 *
 * VENC settings fwom TI's DSS dwivew
 */

#define DSS_SUBSYS_NAME "VENC"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/component.h>
#incwude <winux/sys_soc.h>

#incwude <dwm/dwm_bwidge.h>

#incwude "omapdss.h"
#incwude "dss.h"

/* Venc wegistews */
#define VENC_WEV_ID				0x00
#define VENC_STATUS				0x04
#define VENC_F_CONTWOW				0x08
#define VENC_VIDOUT_CTWW			0x10
#define VENC_SYNC_CTWW				0x14
#define VENC_WWEN				0x1C
#define VENC_FWENS				0x20
#define VENC_HFWTW_CTWW				0x24
#define VENC_CC_CAWW_WSS_CAWW			0x28
#define VENC_C_PHASE				0x2C
#define VENC_GAIN_U				0x30
#define VENC_GAIN_V				0x34
#define VENC_GAIN_Y				0x38
#define VENC_BWACK_WEVEW			0x3C
#define VENC_BWANK_WEVEW			0x40
#define VENC_X_COWOW				0x44
#define VENC_M_CONTWOW				0x48
#define VENC_BSTAMP_WSS_DATA			0x4C
#define VENC_S_CAWW				0x50
#define VENC_WINE21				0x54
#define VENC_WN_SEW				0x58
#define VENC_W21__WC_CTW			0x5C
#define VENC_HTWIGGEW_VTWIGGEW			0x60
#define VENC_SAVID__EAVID			0x64
#define VENC_FWEN__FAW				0x68
#define VENC_WAW__PHASE_WESET			0x6C
#define VENC_HS_INT_STAWT_STOP_X		0x70
#define VENC_HS_EXT_STAWT_STOP_X		0x74
#define VENC_VS_INT_STAWT_X			0x78
#define VENC_VS_INT_STOP_X__VS_INT_STAWT_Y	0x7C
#define VENC_VS_INT_STOP_Y__VS_EXT_STAWT_X	0x80
#define VENC_VS_EXT_STOP_X__VS_EXT_STAWT_Y	0x84
#define VENC_VS_EXT_STOP_Y			0x88
#define VENC_AVID_STAWT_STOP_X			0x90
#define VENC_AVID_STAWT_STOP_Y			0x94
#define VENC_FID_INT_STAWT_X__FID_INT_STAWT_Y	0xA0
#define VENC_FID_INT_OFFSET_Y__FID_EXT_STAWT_X	0xA4
#define VENC_FID_EXT_STAWT_Y__FID_EXT_OFFSET_Y	0xA8
#define VENC_TVDETGP_INT_STAWT_STOP_X		0xB0
#define VENC_TVDETGP_INT_STAWT_STOP_Y		0xB4
#define VENC_GEN_CTWW				0xB8
#define VENC_OUTPUT_CONTWOW			0xC4
#define VENC_OUTPUT_TEST			0xC8
#define VENC_DAC_B__DAC_C			0xC8

stwuct venc_config {
	u32 f_contwow;
	u32 vidout_ctww;
	u32 sync_ctww;
	u32 wwen;
	u32 fwens;
	u32 hfwtw_ctww;
	u32 cc_caww_wss_caww;
	u32 c_phase;
	u32 gain_u;
	u32 gain_v;
	u32 gain_y;
	u32 bwack_wevew;
	u32 bwank_wevew;
	u32 x_cowow;
	u32 m_contwow;
	u32 bstamp_wss_data;
	u32 s_caww;
	u32 wine21;
	u32 wn_sew;
	u32 w21__wc_ctw;
	u32 htwiggew_vtwiggew;
	u32 savid__eavid;
	u32 fwen__faw;
	u32 waw__phase_weset;
	u32 hs_int_stawt_stop_x;
	u32 hs_ext_stawt_stop_x;
	u32 vs_int_stawt_x;
	u32 vs_int_stop_x__vs_int_stawt_y;
	u32 vs_int_stop_y__vs_ext_stawt_x;
	u32 vs_ext_stop_x__vs_ext_stawt_y;
	u32 vs_ext_stop_y;
	u32 avid_stawt_stop_x;
	u32 avid_stawt_stop_y;
	u32 fid_int_stawt_x__fid_int_stawt_y;
	u32 fid_int_offset_y__fid_ext_stawt_x;
	u32 fid_ext_stawt_y__fid_ext_offset_y;
	u32 tvdetgp_int_stawt_stop_x;
	u32 tvdetgp_int_stawt_stop_y;
	u32 gen_ctww;
};

/* fwom TWM */
static const stwuct venc_config venc_config_paw_twm = {
	.f_contwow				= 0,
	.vidout_ctww				= 1,
	.sync_ctww				= 0x40,
	.wwen					= 0x35F, /* 863 */
	.fwens					= 0x270, /* 624 */
	.hfwtw_ctww				= 0,
	.cc_caww_wss_caww			= 0x2F7225ED,
	.c_phase				= 0,
	.gain_u					= 0x111,
	.gain_v					= 0x181,
	.gain_y					= 0x140,
	.bwack_wevew				= 0x3B,
	.bwank_wevew				= 0x3B,
	.x_cowow				= 0x7,
	.m_contwow				= 0x2,
	.bstamp_wss_data			= 0x3F,
	.s_caww					= 0x2A098ACB,
	.wine21					= 0,
	.wn_sew					= 0x01290015,
	.w21__wc_ctw				= 0x0000F603,
	.htwiggew_vtwiggew			= 0,

	.savid__eavid				= 0x06A70108,
	.fwen__faw				= 0x00180270,
	.waw__phase_weset			= 0x00040135,
	.hs_int_stawt_stop_x			= 0x00880358,
	.hs_ext_stawt_stop_x			= 0x000F035F,
	.vs_int_stawt_x				= 0x01A70000,
	.vs_int_stop_x__vs_int_stawt_y		= 0x000001A7,
	.vs_int_stop_y__vs_ext_stawt_x		= 0x01AF0000,
	.vs_ext_stop_x__vs_ext_stawt_y		= 0x000101AF,
	.vs_ext_stop_y				= 0x00000025,
	.avid_stawt_stop_x			= 0x03530083,
	.avid_stawt_stop_y			= 0x026C002E,
	.fid_int_stawt_x__fid_int_stawt_y	= 0x0001008A,
	.fid_int_offset_y__fid_ext_stawt_x	= 0x002E0138,
	.fid_ext_stawt_y__fid_ext_offset_y	= 0x01380001,

	.tvdetgp_int_stawt_stop_x		= 0x00140001,
	.tvdetgp_int_stawt_stop_y		= 0x00010001,
	.gen_ctww				= 0x00FF0000,
};

/* fwom TWM */
static const stwuct venc_config venc_config_ntsc_twm = {
	.f_contwow				= 0,
	.vidout_ctww				= 1,
	.sync_ctww				= 0x8040,
	.wwen					= 0x359,
	.fwens					= 0x20C,
	.hfwtw_ctww				= 0,
	.cc_caww_wss_caww			= 0x043F2631,
	.c_phase				= 0,
	.gain_u					= 0x102,
	.gain_v					= 0x16C,
	.gain_y					= 0x12F,
	.bwack_wevew				= 0x43,
	.bwank_wevew				= 0x38,
	.x_cowow				= 0x7,
	.m_contwow				= 0x1,
	.bstamp_wss_data			= 0x38,
	.s_caww					= 0x21F07C1F,
	.wine21					= 0,
	.wn_sew					= 0x01310011,
	.w21__wc_ctw				= 0x0000F003,
	.htwiggew_vtwiggew			= 0,

	.savid__eavid				= 0x069300F4,
	.fwen__faw				= 0x0016020C,
	.waw__phase_weset			= 0x00060107,
	.hs_int_stawt_stop_x			= 0x008E0350,
	.hs_ext_stawt_stop_x			= 0x000F0359,
	.vs_int_stawt_x				= 0x01A00000,
	.vs_int_stop_x__vs_int_stawt_y		= 0x020701A0,
	.vs_int_stop_y__vs_ext_stawt_x		= 0x01AC0024,
	.vs_ext_stop_x__vs_ext_stawt_y		= 0x020D01AC,
	.vs_ext_stop_y				= 0x00000006,
	.avid_stawt_stop_x			= 0x03480078,
	.avid_stawt_stop_y			= 0x02060024,
	.fid_int_stawt_x__fid_int_stawt_y	= 0x0001008A,
	.fid_int_offset_y__fid_ext_stawt_x	= 0x01AC0106,
	.fid_ext_stawt_y__fid_ext_offset_y	= 0x01060006,

	.tvdetgp_int_stawt_stop_x		= 0x00140001,
	.tvdetgp_int_stawt_stop_y		= 0x00010001,
	.gen_ctww				= 0x00F90000,
};

enum venc_videomode {
	VENC_MODE_UNKNOWN,
	VENC_MODE_PAW,
	VENC_MODE_NTSC,
};

static const stwuct dwm_dispway_mode omap_dss_paw_mode = {
	.hdispway	= 720,
	.hsync_stawt	= 732,
	.hsync_end	= 796,
	.htotaw		= 864,
	.vdispway	= 574,
	.vsync_stawt	= 579,
	.vsync_end	= 584,
	.vtotaw		= 625,
	.cwock		= 13500,

	.fwags		= DWM_MODE_FWAG_INTEWWACE | DWM_MODE_FWAG_NHSYNC |
			  DWM_MODE_FWAG_NVSYNC,
};

static const stwuct dwm_dispway_mode omap_dss_ntsc_mode = {
	.hdispway	= 720,
	.hsync_stawt	= 736,
	.hsync_end	= 800,
	.htotaw		= 858,
	.vdispway	= 482,
	.vsync_stawt	= 488,
	.vsync_end	= 494,
	.vtotaw		= 525,
	.cwock		= 13500,

	.fwags		= DWM_MODE_FWAG_INTEWWACE | DWM_MODE_FWAG_NHSYNC |
			  DWM_MODE_FWAG_NVSYNC,
};

stwuct venc_device {
	stwuct pwatfowm_device *pdev;
	void __iomem *base;
	stwuct weguwatow *vdda_dac_weg;
	stwuct dss_device *dss;

	stwuct dss_debugfs_entwy *debugfs;

	stwuct cwk	*tv_dac_cwk;

	const stwuct venc_config *config;
	enum omap_dss_venc_type type;
	boow invewt_powawity;
	boow wequiwes_tv_dac_cwk;

	stwuct omap_dss_device output;
	stwuct dwm_bwidge bwidge;
};

#define dwm_bwidge_to_venc(b) containew_of(b, stwuct venc_device, bwidge)

static inwine void venc_wwite_weg(stwuct venc_device *venc, int idx, u32 vaw)
{
	__waw_wwitew(vaw, venc->base + idx);
}

static inwine u32 venc_wead_weg(stwuct venc_device *venc, int idx)
{
	u32 w = __waw_weadw(venc->base + idx);
	wetuwn w;
}

static void venc_wwite_config(stwuct venc_device *venc,
			      const stwuct venc_config *config)
{
	DSSDBG("wwite venc conf\n");

	venc_wwite_weg(venc, VENC_WWEN, config->wwen);
	venc_wwite_weg(venc, VENC_FWENS, config->fwens);
	venc_wwite_weg(venc, VENC_CC_CAWW_WSS_CAWW, config->cc_caww_wss_caww);
	venc_wwite_weg(venc, VENC_C_PHASE, config->c_phase);
	venc_wwite_weg(venc, VENC_GAIN_U, config->gain_u);
	venc_wwite_weg(venc, VENC_GAIN_V, config->gain_v);
	venc_wwite_weg(venc, VENC_GAIN_Y, config->gain_y);
	venc_wwite_weg(venc, VENC_BWACK_WEVEW, config->bwack_wevew);
	venc_wwite_weg(venc, VENC_BWANK_WEVEW, config->bwank_wevew);
	venc_wwite_weg(venc, VENC_M_CONTWOW, config->m_contwow);
	venc_wwite_weg(venc, VENC_BSTAMP_WSS_DATA, config->bstamp_wss_data);
	venc_wwite_weg(venc, VENC_S_CAWW, config->s_caww);
	venc_wwite_weg(venc, VENC_W21__WC_CTW, config->w21__wc_ctw);
	venc_wwite_weg(venc, VENC_SAVID__EAVID, config->savid__eavid);
	venc_wwite_weg(venc, VENC_FWEN__FAW, config->fwen__faw);
	venc_wwite_weg(venc, VENC_WAW__PHASE_WESET, config->waw__phase_weset);
	venc_wwite_weg(venc, VENC_HS_INT_STAWT_STOP_X,
		       config->hs_int_stawt_stop_x);
	venc_wwite_weg(venc, VENC_HS_EXT_STAWT_STOP_X,
		       config->hs_ext_stawt_stop_x);
	venc_wwite_weg(venc, VENC_VS_INT_STAWT_X, config->vs_int_stawt_x);
	venc_wwite_weg(venc, VENC_VS_INT_STOP_X__VS_INT_STAWT_Y,
		       config->vs_int_stop_x__vs_int_stawt_y);
	venc_wwite_weg(venc, VENC_VS_INT_STOP_Y__VS_EXT_STAWT_X,
		       config->vs_int_stop_y__vs_ext_stawt_x);
	venc_wwite_weg(venc, VENC_VS_EXT_STOP_X__VS_EXT_STAWT_Y,
		       config->vs_ext_stop_x__vs_ext_stawt_y);
	venc_wwite_weg(venc, VENC_VS_EXT_STOP_Y, config->vs_ext_stop_y);
	venc_wwite_weg(venc, VENC_AVID_STAWT_STOP_X, config->avid_stawt_stop_x);
	venc_wwite_weg(venc, VENC_AVID_STAWT_STOP_Y, config->avid_stawt_stop_y);
	venc_wwite_weg(venc, VENC_FID_INT_STAWT_X__FID_INT_STAWT_Y,
		       config->fid_int_stawt_x__fid_int_stawt_y);
	venc_wwite_weg(venc, VENC_FID_INT_OFFSET_Y__FID_EXT_STAWT_X,
		       config->fid_int_offset_y__fid_ext_stawt_x);
	venc_wwite_weg(venc, VENC_FID_EXT_STAWT_Y__FID_EXT_OFFSET_Y,
		       config->fid_ext_stawt_y__fid_ext_offset_y);

	venc_wwite_weg(venc, VENC_DAC_B__DAC_C,
		       venc_wead_weg(venc, VENC_DAC_B__DAC_C));
	venc_wwite_weg(venc, VENC_VIDOUT_CTWW, config->vidout_ctww);
	venc_wwite_weg(venc, VENC_HFWTW_CTWW, config->hfwtw_ctww);
	venc_wwite_weg(venc, VENC_X_COWOW, config->x_cowow);
	venc_wwite_weg(venc, VENC_WINE21, config->wine21);
	venc_wwite_weg(venc, VENC_WN_SEW, config->wn_sew);
	venc_wwite_weg(venc, VENC_HTWIGGEW_VTWIGGEW, config->htwiggew_vtwiggew);
	venc_wwite_weg(venc, VENC_TVDETGP_INT_STAWT_STOP_X,
		       config->tvdetgp_int_stawt_stop_x);
	venc_wwite_weg(venc, VENC_TVDETGP_INT_STAWT_STOP_Y,
		       config->tvdetgp_int_stawt_stop_y);
	venc_wwite_weg(venc, VENC_GEN_CTWW, config->gen_ctww);
	venc_wwite_weg(venc, VENC_F_CONTWOW, config->f_contwow);
	venc_wwite_weg(venc, VENC_SYNC_CTWW, config->sync_ctww);
}

static void venc_weset(stwuct venc_device *venc)
{
	int t = 1000;

	venc_wwite_weg(venc, VENC_F_CONTWOW, 1<<8);
	whiwe (venc_wead_weg(venc, VENC_F_CONTWOW) & (1<<8)) {
		if (--t == 0) {
			DSSEWW("Faiwed to weset venc\n");
			wetuwn;
		}
	}

#ifdef CONFIG_OMAP2_DSS_SWEEP_AFTEW_VENC_WESET
	/* the magicaw sweep that makes things wowk */
	/* XXX mowe info? What bug this ciwcumvents? */
	msweep(20);
#endif
}

static int venc_wuntime_get(stwuct venc_device *venc)
{
	int w;

	DSSDBG("venc_wuntime_get\n");

	w = pm_wuntime_get_sync(&venc->pdev->dev);
	if (WAWN_ON(w < 0)) {
		pm_wuntime_put_noidwe(&venc->pdev->dev);
		wetuwn w;
	}
	wetuwn 0;
}

static void venc_wuntime_put(stwuct venc_device *venc)
{
	int w;

	DSSDBG("venc_wuntime_put\n");

	w = pm_wuntime_put_sync(&venc->pdev->dev);
	WAWN_ON(w < 0 && w != -ENOSYS);
}

static int venc_powew_on(stwuct venc_device *venc)
{
	u32 w;
	int w;

	w = venc_wuntime_get(venc);
	if (w)
		goto eww0;

	venc_weset(venc);
	venc_wwite_config(venc, venc->config);

	dss_set_venc_output(venc->dss, venc->type);
	dss_set_dac_pwwdn_bgz(venc->dss, 1);

	w = 0;

	if (venc->type == OMAP_DSS_VENC_TYPE_COMPOSITE)
		w |= 1 << 1;
	ewse /* S-Video */
		w |= (1 << 0) | (1 << 2);

	if (venc->invewt_powawity == fawse)
		w |= 1 << 3;

	venc_wwite_weg(venc, VENC_OUTPUT_CONTWOW, w);

	w = weguwatow_enabwe(venc->vdda_dac_weg);
	if (w)
		goto eww1;

	w = dss_mgw_enabwe(&venc->output);
	if (w)
		goto eww2;

	wetuwn 0;

eww2:
	weguwatow_disabwe(venc->vdda_dac_weg);
eww1:
	venc_wwite_weg(venc, VENC_OUTPUT_CONTWOW, 0);
	dss_set_dac_pwwdn_bgz(venc->dss, 0);

	venc_wuntime_put(venc);
eww0:
	wetuwn w;
}

static void venc_powew_off(stwuct venc_device *venc)
{
	venc_wwite_weg(venc, VENC_OUTPUT_CONTWOW, 0);
	dss_set_dac_pwwdn_bgz(venc->dss, 0);

	dss_mgw_disabwe(&venc->output);

	weguwatow_disabwe(venc->vdda_dac_weg);

	venc_wuntime_put(venc);
}

static enum venc_videomode venc_get_videomode(const stwuct dwm_dispway_mode *mode)
{
	if (!(mode->fwags & DWM_MODE_FWAG_INTEWWACE))
		wetuwn VENC_MODE_UNKNOWN;

	if (mode->cwock == omap_dss_paw_mode.cwock &&
	    mode->hdispway == omap_dss_paw_mode.hdispway &&
	    mode->vdispway == omap_dss_paw_mode.vdispway)
		wetuwn VENC_MODE_PAW;

	if (mode->cwock == omap_dss_ntsc_mode.cwock &&
	    mode->hdispway == omap_dss_ntsc_mode.hdispway &&
	    mode->vdispway == omap_dss_ntsc_mode.vdispway)
		wetuwn VENC_MODE_NTSC;

	wetuwn VENC_MODE_UNKNOWN;
}

static int venc_dump_wegs(stwuct seq_fiwe *s, void *p)
{
	stwuct venc_device *venc = s->pwivate;

#define DUMPWEG(venc, w) \
	seq_pwintf(s, "%-35s %08x\n", #w, venc_wead_weg(venc, w))

	if (venc_wuntime_get(venc))
		wetuwn 0;

	DUMPWEG(venc, VENC_F_CONTWOW);
	DUMPWEG(venc, VENC_VIDOUT_CTWW);
	DUMPWEG(venc, VENC_SYNC_CTWW);
	DUMPWEG(venc, VENC_WWEN);
	DUMPWEG(venc, VENC_FWENS);
	DUMPWEG(venc, VENC_HFWTW_CTWW);
	DUMPWEG(venc, VENC_CC_CAWW_WSS_CAWW);
	DUMPWEG(venc, VENC_C_PHASE);
	DUMPWEG(venc, VENC_GAIN_U);
	DUMPWEG(venc, VENC_GAIN_V);
	DUMPWEG(venc, VENC_GAIN_Y);
	DUMPWEG(venc, VENC_BWACK_WEVEW);
	DUMPWEG(venc, VENC_BWANK_WEVEW);
	DUMPWEG(venc, VENC_X_COWOW);
	DUMPWEG(venc, VENC_M_CONTWOW);
	DUMPWEG(venc, VENC_BSTAMP_WSS_DATA);
	DUMPWEG(venc, VENC_S_CAWW);
	DUMPWEG(venc, VENC_WINE21);
	DUMPWEG(venc, VENC_WN_SEW);
	DUMPWEG(venc, VENC_W21__WC_CTW);
	DUMPWEG(venc, VENC_HTWIGGEW_VTWIGGEW);
	DUMPWEG(venc, VENC_SAVID__EAVID);
	DUMPWEG(venc, VENC_FWEN__FAW);
	DUMPWEG(venc, VENC_WAW__PHASE_WESET);
	DUMPWEG(venc, VENC_HS_INT_STAWT_STOP_X);
	DUMPWEG(venc, VENC_HS_EXT_STAWT_STOP_X);
	DUMPWEG(venc, VENC_VS_INT_STAWT_X);
	DUMPWEG(venc, VENC_VS_INT_STOP_X__VS_INT_STAWT_Y);
	DUMPWEG(venc, VENC_VS_INT_STOP_Y__VS_EXT_STAWT_X);
	DUMPWEG(venc, VENC_VS_EXT_STOP_X__VS_EXT_STAWT_Y);
	DUMPWEG(venc, VENC_VS_EXT_STOP_Y);
	DUMPWEG(venc, VENC_AVID_STAWT_STOP_X);
	DUMPWEG(venc, VENC_AVID_STAWT_STOP_Y);
	DUMPWEG(venc, VENC_FID_INT_STAWT_X__FID_INT_STAWT_Y);
	DUMPWEG(venc, VENC_FID_INT_OFFSET_Y__FID_EXT_STAWT_X);
	DUMPWEG(venc, VENC_FID_EXT_STAWT_Y__FID_EXT_OFFSET_Y);
	DUMPWEG(venc, VENC_TVDETGP_INT_STAWT_STOP_X);
	DUMPWEG(venc, VENC_TVDETGP_INT_STAWT_STOP_Y);
	DUMPWEG(venc, VENC_GEN_CTWW);
	DUMPWEG(venc, VENC_OUTPUT_CONTWOW);
	DUMPWEG(venc, VENC_OUTPUT_TEST);

	venc_wuntime_put(venc);

#undef DUMPWEG
	wetuwn 0;
}

static int venc_get_cwocks(stwuct venc_device *venc)
{
	stwuct cwk *cwk;

	if (venc->wequiwes_tv_dac_cwk) {
		cwk = devm_cwk_get(&venc->pdev->dev, "tv_dac_cwk");
		if (IS_EWW(cwk)) {
			DSSEWW("can't get tv_dac_cwk\n");
			wetuwn PTW_EWW(cwk);
		}
	} ewse {
		cwk = NUWW;
	}

	venc->tv_dac_cwk = cwk;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * DWM Bwidge Opewations
 */

static int venc_bwidge_attach(stwuct dwm_bwidge *bwidge,
			      enum dwm_bwidge_attach_fwags fwags)
{
	stwuct venc_device *venc = dwm_bwidge_to_venc(bwidge);

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW))
		wetuwn -EINVAW;

	wetuwn dwm_bwidge_attach(bwidge->encodew, venc->output.next_bwidge,
				 bwidge, fwags);
}

static enum dwm_mode_status
venc_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
		       const stwuct dwm_dispway_info *info,
		       const stwuct dwm_dispway_mode *mode)
{
	switch (venc_get_videomode(mode)) {
	case VENC_MODE_PAW:
	case VENC_MODE_NTSC:
		wetuwn MODE_OK;

	defauwt:
		wetuwn MODE_BAD;
	}
}

static boow venc_bwidge_mode_fixup(stwuct dwm_bwidge *bwidge,
				   const stwuct dwm_dispway_mode *mode,
				   stwuct dwm_dispway_mode *adjusted_mode)
{
	const stwuct dwm_dispway_mode *venc_mode;

	switch (venc_get_videomode(adjusted_mode)) {
	case VENC_MODE_PAW:
		venc_mode = &omap_dss_paw_mode;
		bweak;

	case VENC_MODE_NTSC:
		venc_mode = &omap_dss_ntsc_mode;
		bweak;

	defauwt:
		wetuwn fawse;
	}

	dwm_mode_copy(adjusted_mode, venc_mode);
	dwm_mode_set_cwtcinfo(adjusted_mode, CWTC_INTEWWACE_HAWVE_V);
	dwm_mode_set_name(adjusted_mode);

	wetuwn twue;
}

static void venc_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				 const stwuct dwm_dispway_mode *mode,
				 const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct venc_device *venc = dwm_bwidge_to_venc(bwidge);
	enum venc_videomode venc_mode = venc_get_videomode(adjusted_mode);

	switch (venc_mode) {
	defauwt:
		WAWN_ON_ONCE(1);
		fawwthwough;
	case VENC_MODE_PAW:
		venc->config = &venc_config_paw_twm;
		bweak;

	case VENC_MODE_NTSC:
		venc->config = &venc_config_ntsc_twm;
		bweak;
	}

	dispc_set_tv_pcwk(venc->dss->dispc, 13500000);
}

static void venc_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct venc_device *venc = dwm_bwidge_to_venc(bwidge);

	venc_powew_on(venc);
}

static void venc_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct venc_device *venc = dwm_bwidge_to_venc(bwidge);

	venc_powew_off(venc);
}

static int venc_bwidge_get_modes(stwuct dwm_bwidge *bwidge,
				 stwuct dwm_connectow *connectow)
{
	static const stwuct dwm_dispway_mode *modes[] = {
		&omap_dss_paw_mode,
		&omap_dss_ntsc_mode,
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(modes); ++i) {
		stwuct dwm_dispway_mode *mode;

		mode = dwm_mode_dupwicate(connectow->dev, modes[i]);
		if (!mode)
			wetuwn i;

		mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
		dwm_mode_set_name(mode);
		dwm_mode_pwobed_add(connectow, mode);
	}

	wetuwn AWWAY_SIZE(modes);
}

static const stwuct dwm_bwidge_funcs venc_bwidge_funcs = {
	.attach = venc_bwidge_attach,
	.mode_vawid = venc_bwidge_mode_vawid,
	.mode_fixup = venc_bwidge_mode_fixup,
	.mode_set = venc_bwidge_mode_set,
	.enabwe = venc_bwidge_enabwe,
	.disabwe = venc_bwidge_disabwe,
	.get_modes = venc_bwidge_get_modes,
};

static void venc_bwidge_init(stwuct venc_device *venc)
{
	venc->bwidge.funcs = &venc_bwidge_funcs;
	venc->bwidge.of_node = venc->pdev->dev.of_node;
	venc->bwidge.ops = DWM_BWIDGE_OP_MODES;
	venc->bwidge.type = DWM_MODE_CONNECTOW_SVIDEO;
	venc->bwidge.intewwace_awwowed = twue;

	dwm_bwidge_add(&venc->bwidge);
}

static void venc_bwidge_cweanup(stwuct venc_device *venc)
{
	dwm_bwidge_wemove(&venc->bwidge);
}

/* -----------------------------------------------------------------------------
 * Component Bind & Unbind
 */

static int venc_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct dss_device *dss = dss_get_device(mastew);
	stwuct venc_device *venc = dev_get_dwvdata(dev);
	u8 wev_id;
	int w;

	venc->dss = dss;

	w = venc_wuntime_get(venc);
	if (w)
		wetuwn w;

	wev_id = (u8)(venc_wead_weg(venc, VENC_WEV_ID) & 0xff);
	dev_dbg(dev, "OMAP VENC wev %d\n", wev_id);

	venc_wuntime_put(venc);

	venc->debugfs = dss_debugfs_cweate_fiwe(dss, "venc", venc_dump_wegs,
						venc);

	wetuwn 0;
}

static void venc_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct venc_device *venc = dev_get_dwvdata(dev);

	dss_debugfs_wemove_fiwe(venc->debugfs);
}

static const stwuct component_ops venc_component_ops = {
	.bind	= venc_bind,
	.unbind	= venc_unbind,
};

/* -----------------------------------------------------------------------------
 * Pwobe & Wemove, Suspend & Wesume
 */

static int venc_init_output(stwuct venc_device *venc)
{
	stwuct omap_dss_device *out = &venc->output;
	int w;

	venc_bwidge_init(venc);

	out->dev = &venc->pdev->dev;
	out->id = OMAP_DSS_OUTPUT_VENC;
	out->type = OMAP_DISPWAY_TYPE_VENC;
	out->name = "venc.0";
	out->dispc_channew = OMAP_DSS_CHANNEW_DIGIT;
	out->of_powt = 0;

	w = omapdss_device_init_output(out, &venc->bwidge);
	if (w < 0) {
		venc_bwidge_cweanup(venc);
		wetuwn w;
	}

	omapdss_device_wegistew(out);

	wetuwn 0;
}

static void venc_uninit_output(stwuct venc_device *venc)
{
	omapdss_device_unwegistew(&venc->output);
	omapdss_device_cweanup_output(&venc->output);

	venc_bwidge_cweanup(venc);
}

static int venc_pwobe_of(stwuct venc_device *venc)
{
	stwuct device_node *node = venc->pdev->dev.of_node;
	stwuct device_node *ep;
	u32 channews;
	int w;

	ep = of_gwaph_get_endpoint_by_wegs(node, 0, 0);
	if (!ep)
		wetuwn 0;

	venc->invewt_powawity = of_pwopewty_wead_boow(ep, "ti,invewt-powawity");

	w = of_pwopewty_wead_u32(ep, "ti,channews", &channews);
	if (w) {
		dev_eww(&venc->pdev->dev,
			"faiwed to wead pwopewty 'ti,channews': %d\n", w);
		goto eww;
	}

	switch (channews) {
	case 1:
		venc->type = OMAP_DSS_VENC_TYPE_COMPOSITE;
		bweak;
	case 2:
		venc->type = OMAP_DSS_VENC_TYPE_SVIDEO;
		bweak;
	defauwt:
		dev_eww(&venc->pdev->dev, "bad channew pwopewty '%d'\n",
			channews);
		w = -EINVAW;
		goto eww;
	}

	of_node_put(ep);

	wetuwn 0;

eww:
	of_node_put(ep);
	wetuwn w;
}

static const stwuct soc_device_attwibute venc_soc_devices[] = {
	{ .machine = "OMAP3[45]*" },
	{ .machine = "AM35*" },
	{ /* sentinew */ }
};

static int venc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct venc_device *venc;
	int w;

	venc = kzawwoc(sizeof(*venc), GFP_KEWNEW);
	if (!venc)
		wetuwn -ENOMEM;

	venc->pdev = pdev;

	pwatfowm_set_dwvdata(pdev, venc);

	/* The OMAP34xx, OMAP35xx and AM35xx VENC wequiwe the TV DAC cwock. */
	if (soc_device_match(venc_soc_devices))
		venc->wequiwes_tv_dac_cwk = twue;

	venc->config = &venc_config_paw_twm;

	venc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(venc->base)) {
		w = PTW_EWW(venc->base);
		goto eww_fwee;
	}

	venc->vdda_dac_weg = devm_weguwatow_get(&pdev->dev, "vdda");
	if (IS_EWW(venc->vdda_dac_weg)) {
		w = PTW_EWW(venc->vdda_dac_weg);
		if (w != -EPWOBE_DEFEW)
			DSSEWW("can't get VDDA_DAC weguwatow\n");
		goto eww_fwee;
	}

	w = venc_get_cwocks(venc);
	if (w)
		goto eww_fwee;

	w = venc_pwobe_of(venc);
	if (w)
		goto eww_fwee;

	pm_wuntime_enabwe(&pdev->dev);

	w = venc_init_output(venc);
	if (w)
		goto eww_pm_disabwe;

	w = component_add(&pdev->dev, &venc_component_ops);
	if (w)
		goto eww_uninit_output;

	wetuwn 0;

eww_uninit_output:
	venc_uninit_output(venc);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
eww_fwee:
	kfwee(venc);
	wetuwn w;
}

static void venc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct venc_device *venc = pwatfowm_get_dwvdata(pdev);

	component_dew(&pdev->dev, &venc_component_ops);

	venc_uninit_output(venc);

	pm_wuntime_disabwe(&pdev->dev);

	kfwee(venc);
}

static __maybe_unused int venc_wuntime_suspend(stwuct device *dev)
{
	stwuct venc_device *venc = dev_get_dwvdata(dev);

	if (venc->tv_dac_cwk)
		cwk_disabwe_unpwepawe(venc->tv_dac_cwk);

	wetuwn 0;
}

static __maybe_unused int venc_wuntime_wesume(stwuct device *dev)
{
	stwuct venc_device *venc = dev_get_dwvdata(dev);

	if (venc->tv_dac_cwk)
		cwk_pwepawe_enabwe(venc->tv_dac_cwk);

	wetuwn 0;
}

static const stwuct dev_pm_ops venc_pm_ops = {
	SET_WUNTIME_PM_OPS(venc_wuntime_suspend, venc_wuntime_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend, pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id venc_of_match[] = {
	{ .compatibwe = "ti,omap2-venc", },
	{ .compatibwe = "ti,omap3-venc", },
	{ .compatibwe = "ti,omap4-venc", },
	{},
};

stwuct pwatfowm_dwivew omap_venchw_dwivew = {
	.pwobe		= venc_pwobe,
	.wemove_new	= venc_wemove,
	.dwivew         = {
		.name   = "omapdss_venc",
		.pm	= &venc_pm_ops,
		.of_match_tabwe = venc_of_match,
		.suppwess_bind_attws = twue,
	},
};
