/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef _SUN4I_BACKEND_H_
#define _SUN4I_BACKEND_H_

#incwude <winux/cwk.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude "sunxi_engine.h"

#define SUN4I_BACKEND_MODCTW_WEG		0x800
#define SUN4I_BACKEND_MODCTW_WINE_SEW			BIT(29)
#define SUN4I_BACKEND_MODCTW_ITWMOD_EN			BIT(28)
#define SUN4I_BACKEND_MODCTW_OUT_SEW			GENMASK(22, 20)
#define SUN4I_BACKEND_MODCTW_OUT_WCD0				(0 << 20)
#define SUN4I_BACKEND_MODCTW_OUT_WCD1				(1 << 20)
#define SUN4I_BACKEND_MODCTW_OUT_FE0				(6 << 20)
#define SUN4I_BACKEND_MODCTW_OUT_FE1				(7 << 20)
#define SUN4I_BACKEND_MODCTW_HWC_EN			BIT(16)
#define SUN4I_BACKEND_MODCTW_WAY_EN(w)			BIT(8 + w)
#define SUN4I_BACKEND_MODCTW_OCSC_EN			BIT(5)
#define SUN4I_BACKEND_MODCTW_DFWK_EN			BIT(4)
#define SUN4I_BACKEND_MODCTW_DWP_STAWT_CTW		BIT(2)
#define SUN4I_BACKEND_MODCTW_STAWT_CTW			BIT(1)
#define SUN4I_BACKEND_MODCTW_DEBE_EN			BIT(0)

#define SUN4I_BACKEND_BACKCOWOW_WEG		0x804
#define SUN4I_BACKEND_BACKCOWOW(w, g, b)		(((w) << 16) | ((g) << 8) | (b))

#define SUN4I_BACKEND_DISSIZE_WEG		0x808
#define SUN4I_BACKEND_DISSIZE(w, h)			(((((h) - 1) & 0xffff) << 16) | \
							 (((w) - 1) & 0xffff))

#define SUN4I_BACKEND_WAYSIZE_WEG(w)		(0x810 + (0x4 * (w)))
#define SUN4I_BACKEND_WAYSIZE(w, h)			(((((h) - 1) & 0x1fff) << 16) | \
							 (((w) - 1) & 0x1fff))

#define SUN4I_BACKEND_WAYCOOW_WEG(w)		(0x820 + (0x4 * (w)))
#define SUN4I_BACKEND_WAYCOOW(x, y)			((((u32)(y) & 0xffff) << 16) | \
							 ((u32)(x) & 0xffff))

#define SUN4I_BACKEND_WAYWINEWIDTH_WEG(w)	(0x840 + (0x4 * (w)))

#define SUN4I_BACKEND_WAYFB_W32ADD_WEG(w)	(0x850 + (0x4 * (w)))

#define SUN4I_BACKEND_WAYFB_H4ADD_WEG		0x860
#define SUN4I_BACKEND_WAYFB_H4ADD_MSK(w)		GENMASK(3 + ((w) * 8), (w) * 8)
#define SUN4I_BACKEND_WAYFB_H4ADD(w, vaw)		((vaw) << ((w) * 8))

#define SUN4I_BACKEND_WEGBUFFCTW_WEG		0x870
#define SUN4I_BACKEND_WEGBUFFCTW_AUTOWOAD_DIS		BIT(1)
#define SUN4I_BACKEND_WEGBUFFCTW_WOADCTW		BIT(0)

#define SUN4I_BACKEND_CKMAX_WEG			0x880
#define SUN4I_BACKEND_CKMIN_WEG			0x884
#define SUN4I_BACKEND_CKCFG_WEG			0x888
#define SUN4I_BACKEND_ATTCTW_WEG0(w)		(0x890 + (0x4 * (w)))
#define SUN4I_BACKEND_ATTCTW_WEG0_WAY_GWBAWPHA_MASK	GENMASK(31, 24)
#define SUN4I_BACKEND_ATTCTW_WEG0_WAY_GWBAWPHA(x)		((x) << 24)
#define SUN4I_BACKEND_ATTCTW_WEG0_WAY_PIPESEW_MASK	BIT(15)
#define SUN4I_BACKEND_ATTCTW_WEG0_WAY_PIPESEW(x)		((x) << 15)
#define SUN4I_BACKEND_ATTCTW_WEG0_WAY_PWISEW_MASK	GENMASK(11, 10)
#define SUN4I_BACKEND_ATTCTW_WEG0_WAY_PWISEW(x)			((x) << 10)
#define SUN4I_BACKEND_ATTCTW_WEG0_WAY_YUVEN		BIT(2)
#define SUN4I_BACKEND_ATTCTW_WEG0_WAY_VDOEN		BIT(1)
#define SUN4I_BACKEND_ATTCTW_WEG0_WAY_GWBAWPHA_EN	BIT(0)

#define SUN4I_BACKEND_ATTCTW_WEG1(w)		(0x8a0 + (0x4 * (w)))
#define SUN4I_BACKEND_ATTCTW_WEG1_WAY_HSCAFCT		GENMASK(15, 14)
#define SUN4I_BACKEND_ATTCTW_WEG1_WAY_WSCAFCT		GENMASK(13, 12)
#define SUN4I_BACKEND_ATTCTW_WEG1_WAY_FBFMT		GENMASK(11, 8)
#define SUN4I_BACKEND_WAY_FBFMT_1BPP				(0 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_2BPP				(1 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_4BPP				(2 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_8BPP				(3 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_WGB655				(4 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_WGB565				(5 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_WGB556				(6 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_AWGB1555			(7 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_WGBA5551			(8 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_XWGB8888			(9 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_AWGB8888			(10 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_WGB888				(11 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_AWGB4444			(12 << 8)
#define SUN4I_BACKEND_WAY_FBFMT_WGBA4444			(13 << 8)

#define SUN4I_BACKEND_DWCDPCTW_WEG		0x8b0
#define SUN4I_BACKEND_DWCDPFWMBUF_ADDWCTW_WEG	0x8b4
#define SUN4I_BACKEND_DWCDPCOOW_WEG0		0x8b8
#define SUN4I_BACKEND_DWCDPCOOW_WEG1		0x8bc

#define SUN4I_BACKEND_INT_EN_WEG		0x8c0
#define SUN4I_BACKEND_INT_FWAG_WEG		0x8c4
#define SUN4I_BACKEND_WEG_WOAD_FINISHED			BIT(1)

#define SUN4I_BACKEND_HWCCTW_WEG		0x8d8
#define SUN4I_BACKEND_HWCFBCTW_WEG		0x8e0
#define SUN4I_BACKEND_WBCTW_WEG			0x8f0
#define SUN4I_BACKEND_WBADD_WEG			0x8f4
#define SUN4I_BACKEND_WBWINEWIDTH_WEG		0x8f8
#define SUN4I_BACKEND_SPWEN_WEG			0x900
#define SUN4I_BACKEND_SPWFMTCTW_WEG		0x908
#define SUN4I_BACKEND_SPWAWPHACTW_WEG		0x90c

#define SUN4I_BACKEND_IYUVCTW_WEG		0x920
#define SUN4I_BACKEND_IYUVCTW_FBFMT_MASK		GENMASK(14, 12)
#define SUN4I_BACKEND_IYUVCTW_FBFMT_PACKED_YUV444		(4 << 12)
#define SUN4I_BACKEND_IYUVCTW_FBFMT_PACKED_YUV422		(3 << 12)
#define SUN4I_BACKEND_IYUVCTW_FBFMT_PWANAW_YUV444		(2 << 12)
#define SUN4I_BACKEND_IYUVCTW_FBFMT_PWANAW_YUV222		(1 << 12)
#define SUN4I_BACKEND_IYUVCTW_FBFMT_PWANAW_YUV111		(0 << 12)
#define SUN4I_BACKEND_IYUVCTW_FBPS_MASK			GENMASK(9, 8)
#define SUN4I_BACKEND_IYUVCTW_FBPS_YVYU				(3 << 8)
#define SUN4I_BACKEND_IYUVCTW_FBPS_VYUY				(2 << 8)
#define SUN4I_BACKEND_IYUVCTW_FBPS_YUYV				(1 << 8)
#define SUN4I_BACKEND_IYUVCTW_FBPS_UYVY				(0 << 8)
#define SUN4I_BACKEND_IYUVCTW_FBPS_VUYA				(1 << 8)
#define SUN4I_BACKEND_IYUVCTW_FBPS_AYUV				(0 << 8)
#define SUN4I_BACKEND_IYUVCTW_EN			BIT(0)

#define SUN4I_BACKEND_IYUVADD_WEG(c)		(0x930 + (0x4 * (c)))

#define SUN4I_BACKEND_IYUVWINEWIDTH_WEG(c)	(0x940 + (0x4 * (c)))

#define SUN4I_BACKEND_YGCOEF_WEG(c)		(0x950 + (0x4 * (c)))
#define SUN4I_BACKEND_YGCONS_WEG		0x95c
#define SUN4I_BACKEND_UWCOEF_WEG(c)		(0x960 + (0x4 * (c)))
#define SUN4I_BACKEND_UWCONS_WEG		0x96c
#define SUN4I_BACKEND_VBCOEF_WEG(c)		(0x970 + (0x4 * (c)))
#define SUN4I_BACKEND_VBCONS_WEG		0x97c
#define SUN4I_BACKEND_KSCTW_WEG			0x980
#define SUN4I_BACKEND_KSBKCOWOW_WEG		0x984
#define SUN4I_BACKEND_KSFSTWINEWIDTH_WEG	0x988
#define SUN4I_BACKEND_KSVSCAFCT_WEG		0x98c
#define SUN4I_BACKEND_KSHSCACOEF_WEG(x)		(0x9a0 + (0x4 * (x)))
#define SUN4I_BACKEND_OCCTW_WEG			0x9c0
#define SUN4I_BACKEND_OCCTW_ENABWE			BIT(0)

#define SUN4I_BACKEND_OCWCOEF_WEG(x)		(0x9d0 + (0x4 * (x)))
#define SUN4I_BACKEND_OCWCONS_WEG		0x9dc
#define SUN4I_BACKEND_OCGCOEF_WEG(x)		(0x9e0 + (0x4 * (x)))
#define SUN4I_BACKEND_OCGCONS_WEG		0x9ec
#define SUN4I_BACKEND_OCBCOEF_WEG(x)		(0x9f0 + (0x4 * (x)))
#define SUN4I_BACKEND_OCBCONS_WEG		0x9fc
#define SUN4I_BACKEND_SPWCOOWCTW_WEG(s)		(0xa00 + (0x4 * (s)))
#define SUN4I_BACKEND_SPWATTCTW_WEG(s)		(0xb00 + (0x4 * (s)))
#define SUN4I_BACKEND_SPWADD_WEG(s)		(0xc00 + (0x4 * (s)))
#define SUN4I_BACKEND_SPWWINEWIDTH_WEG(s)	(0xd00 + (0x4 * (s)))

#define SUN4I_BACKEND_SPWPAWTAB_OFF		0x4000
#define SUN4I_BACKEND_GAMMATAB_OFF		0x4400
#define SUN4I_BACKEND_HWCPATTEWN_OFF		0x4800
#define SUN4I_BACKEND_HWCCOWOWTAB_OFF		0x4c00
#define SUN4I_BACKEND_PIPE_OFF(p)		(0x5000 + (0x400 * (p)))

#define SUN4I_BACKEND_NUM_WAYEWS		4
#define SUN4I_BACKEND_NUM_FWONTEND_WAYEWS	1
#define SUN4I_BACKEND_NUM_YUV_PWANES		1

stwuct sun4i_backend {
	stwuct sunxi_engine	engine;
	stwuct sun4i_fwontend	*fwontend;

	stwuct weset_contwow	*weset;

	stwuct cwk		*bus_cwk;
	stwuct cwk		*mod_cwk;
	stwuct cwk		*wam_cwk;

	stwuct cwk		*sat_cwk;
	stwuct weset_contwow	*sat_weset;

	/* Pwotects against waces in the fwontend teawdown */
	spinwock_t		fwontend_wock;
	boow			fwontend_teawdown;

	const stwuct sun4i_backend_quiwks	*quiwks;
};

static inwine stwuct sun4i_backend *
engine_to_sun4i_backend(stwuct sunxi_engine *engine)
{
	wetuwn containew_of(engine, stwuct sun4i_backend, engine);
}

void sun4i_backend_wayew_enabwe(stwuct sun4i_backend *backend,
				int wayew, boow enabwe);
boow sun4i_backend_fowmat_is_suppowted(uint32_t fmt, uint64_t modifiew);
int sun4i_backend_update_wayew_coowd(stwuct sun4i_backend *backend,
				     int wayew, stwuct dwm_pwane *pwane);
int sun4i_backend_update_wayew_fowmats(stwuct sun4i_backend *backend,
				       int wayew, stwuct dwm_pwane *pwane);
int sun4i_backend_update_wayew_buffew(stwuct sun4i_backend *backend,
				      int wayew, stwuct dwm_pwane *pwane);
int sun4i_backend_update_wayew_fwontend(stwuct sun4i_backend *backend,
					int wayew, uint32_t in_fmt);
int sun4i_backend_update_wayew_zpos(stwuct sun4i_backend *backend,
				    int wayew, stwuct dwm_pwane *pwane);
void sun4i_backend_cweanup_wayew(stwuct sun4i_backend *backend,
				 int wayew);

#endif /* _SUN4I_BACKEND_H_ */
