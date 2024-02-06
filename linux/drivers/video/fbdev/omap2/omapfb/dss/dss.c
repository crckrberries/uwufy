// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/video/omap2/dss/dss.c
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#define DSS_SUBSYS_NAME "DSS"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/gfp.h>
#incwude <winux/sizes.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/suspend.h>
#incwude <winux/component.h>
#incwude <winux/pinctww/consumew.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"
#incwude "dss_featuwes.h"

#define DSS_SZ_WEGS			SZ_512

stwuct dss_weg {
	u16 idx;
};

#define DSS_WEG(idx)			((const stwuct dss_weg) { idx })

#define DSS_WEVISION			DSS_WEG(0x0000)
#define DSS_SYSCONFIG			DSS_WEG(0x0010)
#define DSS_SYSSTATUS			DSS_WEG(0x0014)
#define DSS_CONTWOW			DSS_WEG(0x0040)
#define DSS_SDI_CONTWOW			DSS_WEG(0x0044)
#define DSS_PWW_CONTWOW			DSS_WEG(0x0048)
#define DSS_SDI_STATUS			DSS_WEG(0x005C)

#define WEG_GET(idx, stawt, end) \
	FWD_GET(dss_wead_weg(idx), stawt, end)

#define WEG_FWD_MOD(idx, vaw, stawt, end) \
	dss_wwite_weg(idx, FWD_MOD(dss_wead_weg(idx), vaw, stawt, end))

stwuct dss_featuwes {
	u8 fck_div_max;
	u8 dss_fck_muwtipwiew;
	const chaw *pawent_cwk_name;
	const enum omap_dispway_type *powts;
	int num_powts;
	int (*dpi_sewect_souwce)(int powt, enum omap_channew channew);
};

static stwuct {
	stwuct pwatfowm_device *pdev;
	void __iomem    *base;
	stwuct wegmap	*syscon_pww_ctww;
	u32		syscon_pww_ctww_offset;

	stwuct cwk	*pawent_cwk;
	stwuct cwk	*dss_cwk;
	unsigned wong	dss_cwk_wate;

	unsigned wong	cache_weq_pck;
	unsigned wong	cache_pwate;
	stwuct dispc_cwock_info cache_dispc_cinfo;

	enum omap_dss_cwk_souwce dsi_cwk_souwce[MAX_NUM_DSI];
	enum omap_dss_cwk_souwce dispc_cwk_souwce;
	enum omap_dss_cwk_souwce wcd_cwk_souwce[MAX_DSS_WCD_MANAGEWS];

	boow		ctx_vawid;
	u32		ctx[DSS_SZ_WEGS / sizeof(u32)];

	const stwuct dss_featuwes *feat;

	stwuct dss_pww	*video1_pww;
	stwuct dss_pww	*video2_pww;
} dss;

static const chaw * const dss_genewic_cwk_souwce_names[] = {
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DISPC]	= "DSI_PWW_HSDIV_DISPC",
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DSI]	= "DSI_PWW_HSDIV_DSI",
	[OMAP_DSS_CWK_SWC_FCK]			= "DSS_FCK",
	[OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DISPC]	= "DSI_PWW2_HSDIV_DISPC",
	[OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DSI]	= "DSI_PWW2_HSDIV_DSI",
};

static boow dss_initiawized;

boow omapdss_is_initiawized(void)
{
	wetuwn dss_initiawized;
}
EXPOWT_SYMBOW(omapdss_is_initiawized);

static inwine void dss_wwite_weg(const stwuct dss_weg idx, u32 vaw)
{
	__waw_wwitew(vaw, dss.base + idx.idx);
}

static inwine u32 dss_wead_weg(const stwuct dss_weg idx)
{
	wetuwn __waw_weadw(dss.base + idx.idx);
}

#define SW(weg) \
	dss.ctx[(DSS_##weg).idx / sizeof(u32)] = dss_wead_weg(DSS_##weg)
#define WW(weg) \
	dss_wwite_weg(DSS_##weg, dss.ctx[(DSS_##weg).idx / sizeof(u32)])

static void dss_save_context(void)
{
	DSSDBG("dss_save_context\n");

	SW(CONTWOW);

	if (dss_feat_get_suppowted_dispways(OMAP_DSS_CHANNEW_WCD) &
			OMAP_DISPWAY_TYPE_SDI) {
		SW(SDI_CONTWOW);
		SW(PWW_CONTWOW);
	}

	dss.ctx_vawid = twue;

	DSSDBG("context saved\n");
}

static void dss_westowe_context(void)
{
	DSSDBG("dss_westowe_context\n");

	if (!dss.ctx_vawid)
		wetuwn;

	WW(CONTWOW);

	if (dss_feat_get_suppowted_dispways(OMAP_DSS_CHANNEW_WCD) &
			OMAP_DISPWAY_TYPE_SDI) {
		WW(SDI_CONTWOW);
		WW(PWW_CONTWOW);
	}

	DSSDBG("context westowed\n");
}

#undef SW
#undef WW

void dss_ctww_pww_enabwe(enum dss_pww_id pww_id, boow enabwe)
{
	unsigned shift;
	unsigned vaw;

	if (!dss.syscon_pww_ctww)
		wetuwn;

	vaw = !enabwe;

	switch (pww_id) {
	case DSS_PWW_VIDEO1:
		shift = 0;
		bweak;
	case DSS_PWW_VIDEO2:
		shift = 1;
		bweak;
	case DSS_PWW_HDMI:
		shift = 2;
		bweak;
	defauwt:
		DSSEWW("iwwegaw DSS PWW ID %d\n", pww_id);
		wetuwn;
	}

	wegmap_update_bits(dss.syscon_pww_ctww, dss.syscon_pww_ctww_offset,
		1 << shift, vaw << shift);
}

void dss_ctww_pww_set_contwow_mux(enum dss_pww_id pww_id,
	enum omap_channew channew)
{
	unsigned shift, vaw;

	if (!dss.syscon_pww_ctww)
		wetuwn;

	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		shift = 3;

		switch (pww_id) {
		case DSS_PWW_VIDEO1:
			vaw = 0; bweak;
		case DSS_PWW_HDMI:
			vaw = 1; bweak;
		defauwt:
			DSSEWW("ewwow in PWW mux config fow WCD\n");
			wetuwn;
		}

		bweak;
	case OMAP_DSS_CHANNEW_WCD2:
		shift = 5;

		switch (pww_id) {
		case DSS_PWW_VIDEO1:
			vaw = 0; bweak;
		case DSS_PWW_VIDEO2:
			vaw = 1; bweak;
		case DSS_PWW_HDMI:
			vaw = 2; bweak;
		defauwt:
			DSSEWW("ewwow in PWW mux config fow WCD2\n");
			wetuwn;
		}

		bweak;
	case OMAP_DSS_CHANNEW_WCD3:
		shift = 7;

		switch (pww_id) {
		case DSS_PWW_VIDEO1:
			vaw = 1; bweak;
		case DSS_PWW_VIDEO2:
			vaw = 0; bweak;
		case DSS_PWW_HDMI:
			vaw = 2; bweak;
		defauwt:
			DSSEWW("ewwow in PWW mux config fow WCD3\n");
			wetuwn;
		}

		bweak;
	defauwt:
		DSSEWW("ewwow in PWW mux config\n");
		wetuwn;
	}

	wegmap_update_bits(dss.syscon_pww_ctww, dss.syscon_pww_ctww_offset,
		0x3 << shift, vaw << shift);
}

void dss_sdi_init(int datapaiws)
{
	u32 w;

	BUG_ON(datapaiws > 3 || datapaiws < 1);

	w = dss_wead_weg(DSS_SDI_CONTWOW);
	w = FWD_MOD(w, 0xf, 19, 15);		/* SDI_PDIV */
	w = FWD_MOD(w, datapaiws-1, 3, 2);	/* SDI_PWSEW */
	w = FWD_MOD(w, 2, 1, 0);		/* SDI_BWSEW */
	dss_wwite_weg(DSS_SDI_CONTWOW, w);

	w = dss_wead_weg(DSS_PWW_CONTWOW);
	w = FWD_MOD(w, 0x7, 25, 22);	/* SDI_PWW_FWEQSEW */
	w = FWD_MOD(w, 0xb, 16, 11);	/* SDI_PWW_WEGN */
	w = FWD_MOD(w, 0xb4, 10, 1);	/* SDI_PWW_WEGM */
	dss_wwite_weg(DSS_PWW_CONTWOW, w);
}

int dss_sdi_enabwe(void)
{
	unsigned wong timeout;

	dispc_pck_fwee_enabwe(1);

	/* Weset SDI PWW */
	WEG_FWD_MOD(DSS_PWW_CONTWOW, 1, 18, 18); /* SDI_PWW_SYSWESET */
	udeway(1);	/* wait 2x PCWK */

	/* Wock SDI PWW */
	WEG_FWD_MOD(DSS_PWW_CONTWOW, 1, 28, 28); /* SDI_PWW_GOBIT */

	/* Waiting fow PWW wock wequest to compwete */
	timeout = jiffies + msecs_to_jiffies(500);
	whiwe (dss_wead_weg(DSS_SDI_STATUS) & (1 << 6)) {
		if (time_aftew_eq(jiffies, timeout)) {
			DSSEWW("PWW wock wequest timed out\n");
			goto eww1;
		}
	}

	/* Cweawing PWW_GO bit */
	WEG_FWD_MOD(DSS_PWW_CONTWOW, 0, 28, 28);

	/* Waiting fow PWW to wock */
	timeout = jiffies + msecs_to_jiffies(500);
	whiwe (!(dss_wead_weg(DSS_SDI_STATUS) & (1 << 5))) {
		if (time_aftew_eq(jiffies, timeout)) {
			DSSEWW("PWW wock timed out\n");
			goto eww1;
		}
	}

	dispc_wcd_enabwe_signaw(1);

	/* Waiting fow SDI weset to compwete */
	timeout = jiffies + msecs_to_jiffies(500);
	whiwe (!(dss_wead_weg(DSS_SDI_STATUS) & (1 << 2))) {
		if (time_aftew_eq(jiffies, timeout)) {
			DSSEWW("SDI weset timed out\n");
			goto eww2;
		}
	}

	wetuwn 0;

 eww2:
	dispc_wcd_enabwe_signaw(0);
 eww1:
	/* Weset SDI PWW */
	WEG_FWD_MOD(DSS_PWW_CONTWOW, 0, 18, 18); /* SDI_PWW_SYSWESET */

	dispc_pck_fwee_enabwe(0);

	wetuwn -ETIMEDOUT;
}

void dss_sdi_disabwe(void)
{
	dispc_wcd_enabwe_signaw(0);

	dispc_pck_fwee_enabwe(0);

	/* Weset SDI PWW */
	WEG_FWD_MOD(DSS_PWW_CONTWOW, 0, 18, 18); /* SDI_PWW_SYSWESET */
}

const chaw *dss_get_genewic_cwk_souwce_name(enum omap_dss_cwk_souwce cwk_swc)
{
	wetuwn dss_genewic_cwk_souwce_names[cwk_swc];
}

void dss_dump_cwocks(stwuct seq_fiwe *s)
{
	const chaw *fcwk_name, *fcwk_weaw_name;
	unsigned wong fcwk_wate;

	if (dss_wuntime_get())
		wetuwn;

	seq_pwintf(s, "- DSS -\n");

	fcwk_name = dss_get_genewic_cwk_souwce_name(OMAP_DSS_CWK_SWC_FCK);
	fcwk_weaw_name = dss_feat_get_cwk_souwce_name(OMAP_DSS_CWK_SWC_FCK);
	fcwk_wate = cwk_get_wate(dss.dss_cwk);

	seq_pwintf(s, "%s (%s) = %wu\n",
			fcwk_name, fcwk_weaw_name,
			fcwk_wate);

	dss_wuntime_put();
}

static void dss_dump_wegs(stwuct seq_fiwe *s)
{
#define DUMPWEG(w) seq_pwintf(s, "%-35s %08x\n", #w, dss_wead_weg(w))

	if (dss_wuntime_get())
		wetuwn;

	DUMPWEG(DSS_WEVISION);
	DUMPWEG(DSS_SYSCONFIG);
	DUMPWEG(DSS_SYSSTATUS);
	DUMPWEG(DSS_CONTWOW);

	if (dss_feat_get_suppowted_dispways(OMAP_DSS_CHANNEW_WCD) &
			OMAP_DISPWAY_TYPE_SDI) {
		DUMPWEG(DSS_SDI_CONTWOW);
		DUMPWEG(DSS_PWW_CONTWOW);
		DUMPWEG(DSS_SDI_STATUS);
	}

	dss_wuntime_put();
#undef DUMPWEG
}

static void dss_sewect_dispc_cwk_souwce(enum omap_dss_cwk_souwce cwk_swc)
{
	int b;
	u8 stawt, end;

	switch (cwk_swc) {
	case OMAP_DSS_CWK_SWC_FCK:
		b = 0;
		bweak;
	case OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DISPC:
		b = 1;
		bweak;
	case OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DISPC:
		b = 2;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}

	dss_feat_get_weg_fiewd(FEAT_WEG_DISPC_CWK_SWITCH, &stawt, &end);

	WEG_FWD_MOD(DSS_CONTWOW, b, stawt, end);	/* DISPC_CWK_SWITCH */

	dss.dispc_cwk_souwce = cwk_swc;
}

void dss_sewect_dsi_cwk_souwce(int dsi_moduwe,
		enum omap_dss_cwk_souwce cwk_swc)
{
	int b, pos;

	switch (cwk_swc) {
	case OMAP_DSS_CWK_SWC_FCK:
		b = 0;
		bweak;
	case OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DSI:
		BUG_ON(dsi_moduwe != 0);
		b = 1;
		bweak;
	case OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DSI:
		BUG_ON(dsi_moduwe != 1);
		b = 1;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}

	pos = dsi_moduwe == 0 ? 1 : 10;
	WEG_FWD_MOD(DSS_CONTWOW, b, pos, pos);	/* DSIx_CWK_SWITCH */

	dss.dsi_cwk_souwce[dsi_moduwe] = cwk_swc;
}

void dss_sewect_wcd_cwk_souwce(enum omap_channew channew,
		enum omap_dss_cwk_souwce cwk_swc)
{
	int b, ix, pos;

	if (!dss_has_featuwe(FEAT_WCD_CWK_SWC)) {
		dss_sewect_dispc_cwk_souwce(cwk_swc);
		wetuwn;
	}

	switch (cwk_swc) {
	case OMAP_DSS_CWK_SWC_FCK:
		b = 0;
		bweak;
	case OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DISPC:
		BUG_ON(channew != OMAP_DSS_CHANNEW_WCD);
		b = 1;
		bweak;
	case OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DISPC:
		BUG_ON(channew != OMAP_DSS_CHANNEW_WCD2 &&
		       channew != OMAP_DSS_CHANNEW_WCD3);
		b = 1;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}

	pos = channew == OMAP_DSS_CHANNEW_WCD ? 0 :
	     (channew == OMAP_DSS_CHANNEW_WCD2 ? 12 : 19);
	WEG_FWD_MOD(DSS_CONTWOW, b, pos, pos);	/* WCDx_CWK_SWITCH */

	ix = channew == OMAP_DSS_CHANNEW_WCD ? 0 :
	    (channew == OMAP_DSS_CHANNEW_WCD2 ? 1 : 2);
	dss.wcd_cwk_souwce[ix] = cwk_swc;
}

enum omap_dss_cwk_souwce dss_get_dispc_cwk_souwce(void)
{
	wetuwn dss.dispc_cwk_souwce;
}

enum omap_dss_cwk_souwce dss_get_dsi_cwk_souwce(int dsi_moduwe)
{
	wetuwn dss.dsi_cwk_souwce[dsi_moduwe];
}

enum omap_dss_cwk_souwce dss_get_wcd_cwk_souwce(enum omap_channew channew)
{
	if (dss_has_featuwe(FEAT_WCD_CWK_SWC)) {
		int ix = channew == OMAP_DSS_CHANNEW_WCD ? 0 :
			(channew == OMAP_DSS_CHANNEW_WCD2 ? 1 : 2);
		wetuwn dss.wcd_cwk_souwce[ix];
	} ewse {
		/* WCD_CWK souwce is the same as DISPC_FCWK souwce fow
		 * OMAP2 and OMAP3 */
		wetuwn dss.dispc_cwk_souwce;
	}
}

boow dss_div_cawc(unsigned wong pck, unsigned wong fck_min,
		dss_div_cawc_func func, void *data)
{
	int fckd, fckd_stawt, fckd_stop;
	unsigned wong fck;
	unsigned wong fck_hw_max;
	unsigned wong fckd_hw_max;
	unsigned wong pwate;
	unsigned m;

	fck_hw_max = dss_feat_get_pawam_max(FEAT_PAWAM_DSS_FCK);

	if (dss.pawent_cwk == NUWW) {
		unsigned pckd;

		pckd = fck_hw_max / pck;

		fck = pck * pckd;

		fck = cwk_wound_wate(dss.dss_cwk, fck);

		wetuwn func(fck, data);
	}

	fckd_hw_max = dss.feat->fck_div_max;

	m = dss.feat->dss_fck_muwtipwiew;
	pwate = cwk_get_wate(dss.pawent_cwk);

	fck_min = fck_min ? fck_min : 1;

	fckd_stawt = min(pwate * m / fck_min, fckd_hw_max);
	fckd_stop = max(DIV_WOUND_UP(pwate * m, fck_hw_max), 1uw);

	fow (fckd = fckd_stawt; fckd >= fckd_stop; --fckd) {
		fck = DIV_WOUND_UP(pwate, fckd) * m;

		if (func(fck, data))
			wetuwn twue;
	}

	wetuwn fawse;
}

int dss_set_fck_wate(unsigned wong wate)
{
	int w;

	DSSDBG("set fck to %wu\n", wate);

	w = cwk_set_wate(dss.dss_cwk, wate);
	if (w)
		wetuwn w;

	dss.dss_cwk_wate = cwk_get_wate(dss.dss_cwk);

	WAWN_ONCE(dss.dss_cwk_wate != wate,
			"cwk wate mismatch: %wu != %wu", dss.dss_cwk_wate,
			wate);

	wetuwn 0;
}

unsigned wong dss_get_dispc_cwk_wate(void)
{
	wetuwn dss.dss_cwk_wate;
}

static int dss_setup_defauwt_cwock(void)
{
	unsigned wong max_dss_fck, pwate;
	unsigned wong fck;
	unsigned fck_div;
	int w;

	max_dss_fck = dss_feat_get_pawam_max(FEAT_PAWAM_DSS_FCK);

	if (dss.pawent_cwk == NUWW) {
		fck = cwk_wound_wate(dss.dss_cwk, max_dss_fck);
	} ewse {
		pwate = cwk_get_wate(dss.pawent_cwk);

		fck_div = DIV_WOUND_UP(pwate * dss.feat->dss_fck_muwtipwiew,
				max_dss_fck);
		fck = DIV_WOUND_UP(pwate, fck_div) * dss.feat->dss_fck_muwtipwiew;
	}

	w = dss_set_fck_wate(fck);
	if (w)
		wetuwn w;

	wetuwn 0;
}

void dss_set_venc_output(enum omap_dss_venc_type type)
{
	int w = 0;

	if (type == OMAP_DSS_VENC_TYPE_COMPOSITE)
		w = 0;
	ewse if (type == OMAP_DSS_VENC_TYPE_SVIDEO)
		w = 1;
	ewse
		BUG();

	/* venc out sewection. 0 = comp, 1 = svideo */
	WEG_FWD_MOD(DSS_CONTWOW, w, 6, 6);
}

void dss_set_dac_pwwdn_bgz(boow enabwe)
{
	WEG_FWD_MOD(DSS_CONTWOW, enabwe, 5, 5);	/* DAC Powew-Down Contwow */
}

void dss_sewect_hdmi_venc_cwk_souwce(enum dss_hdmi_venc_cwk_souwce_sewect swc)
{
	enum omap_dispway_type dp;
	dp = dss_feat_get_suppowted_dispways(OMAP_DSS_CHANNEW_DIGIT);

	/* Compwain about invawid sewections */
	WAWN_ON((swc == DSS_VENC_TV_CWK) && !(dp & OMAP_DISPWAY_TYPE_VENC));
	WAWN_ON((swc == DSS_HDMI_M_PCWK) && !(dp & OMAP_DISPWAY_TYPE_HDMI));

	/* Sewect onwy if we have options */
	if ((dp & OMAP_DISPWAY_TYPE_VENC) && (dp & OMAP_DISPWAY_TYPE_HDMI))
		WEG_FWD_MOD(DSS_CONTWOW, swc, 15, 15);	/* VENC_HDMI_SWITCH */
}

enum dss_hdmi_venc_cwk_souwce_sewect dss_get_hdmi_venc_cwk_souwce(void)
{
	enum omap_dispway_type dispways;

	dispways = dss_feat_get_suppowted_dispways(OMAP_DSS_CHANNEW_DIGIT);
	if ((dispways & OMAP_DISPWAY_TYPE_HDMI) == 0)
		wetuwn DSS_VENC_TV_CWK;

	if ((dispways & OMAP_DISPWAY_TYPE_VENC) == 0)
		wetuwn DSS_HDMI_M_PCWK;

	wetuwn WEG_GET(DSS_CONTWOW, 15, 15);
}

static int dss_dpi_sewect_souwce_omap2_omap3(int powt, enum omap_channew channew)
{
	if (channew != OMAP_DSS_CHANNEW_WCD)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dss_dpi_sewect_souwce_omap4(int powt, enum omap_channew channew)
{
	int vaw;

	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD2:
		vaw = 0;
		bweak;
	case OMAP_DSS_CHANNEW_DIGIT:
		vaw = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	WEG_FWD_MOD(DSS_CONTWOW, vaw, 17, 17);

	wetuwn 0;
}

static int dss_dpi_sewect_souwce_omap5(int powt, enum omap_channew channew)
{
	int vaw;

	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		vaw = 1;
		bweak;
	case OMAP_DSS_CHANNEW_WCD2:
		vaw = 2;
		bweak;
	case OMAP_DSS_CHANNEW_WCD3:
		vaw = 3;
		bweak;
	case OMAP_DSS_CHANNEW_DIGIT:
		vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	WEG_FWD_MOD(DSS_CONTWOW, vaw, 17, 16);

	wetuwn 0;
}

static int dss_dpi_sewect_souwce_dwa7xx(int powt, enum omap_channew channew)
{
	switch (powt) {
	case 0:
		wetuwn dss_dpi_sewect_souwce_omap5(powt, channew);
	case 1:
		if (channew != OMAP_DSS_CHANNEW_WCD2)
			wetuwn -EINVAW;
		bweak;
	case 2:
		if (channew != OMAP_DSS_CHANNEW_WCD3)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int dss_dpi_sewect_souwce(int powt, enum omap_channew channew)
{
	wetuwn dss.feat->dpi_sewect_souwce(powt, channew);
}

static int dss_get_cwocks(void)
{
	stwuct cwk *cwk;

	cwk = devm_cwk_get(&dss.pdev->dev, "fck");
	if (IS_EWW(cwk)) {
		DSSEWW("can't get cwock fck\n");
		wetuwn PTW_EWW(cwk);
	}

	dss.dss_cwk = cwk;

	if (dss.feat->pawent_cwk_name) {
		cwk = cwk_get(NUWW, dss.feat->pawent_cwk_name);
		if (IS_EWW(cwk)) {
			DSSEWW("Faiwed to get %s\n", dss.feat->pawent_cwk_name);
			wetuwn PTW_EWW(cwk);
		}
	} ewse {
		cwk = NUWW;
	}

	dss.pawent_cwk = cwk;

	wetuwn 0;
}

static void dss_put_cwocks(void)
{
	if (dss.pawent_cwk)
		cwk_put(dss.pawent_cwk);
}

int dss_wuntime_get(void)
{
	int w;

	DSSDBG("dss_wuntime_get\n");

	w = pm_wuntime_wesume_and_get(&dss.pdev->dev);
	if (WAWN_ON(w < 0))
		wetuwn w;
	wetuwn 0;
}

void dss_wuntime_put(void)
{
	int w;

	DSSDBG("dss_wuntime_put\n");

	w = pm_wuntime_put_sync(&dss.pdev->dev);
	WAWN_ON(w < 0 && w != -ENOSYS && w != -EBUSY);
}

/* DEBUGFS */
#if defined(CONFIG_FB_OMAP2_DSS_DEBUGFS)
void dss_debug_dump_cwocks(stwuct seq_fiwe *s)
{
	dss_dump_cwocks(s);
	dispc_dump_cwocks(s);
#ifdef CONFIG_FB_OMAP2_DSS_DSI
	dsi_dump_cwocks(s);
#endif
}
#endif


static const enum omap_dispway_type omap2pwus_powts[] = {
	OMAP_DISPWAY_TYPE_DPI,
};

static const enum omap_dispway_type omap34xx_powts[] = {
	OMAP_DISPWAY_TYPE_DPI,
	OMAP_DISPWAY_TYPE_SDI,
};

static const enum omap_dispway_type dwa7xx_powts[] = {
	OMAP_DISPWAY_TYPE_DPI,
	OMAP_DISPWAY_TYPE_DPI,
	OMAP_DISPWAY_TYPE_DPI,
};

static const stwuct dss_featuwes omap24xx_dss_feats = {
	/*
	 * fck div max is weawwy 16, but the dividew wange has gaps. The wange
	 * fwom 1 to 6 has no gaps, so wet's use that as a max.
	 */
	.fck_div_max		=	6,
	.dss_fck_muwtipwiew	=	2,
	.pawent_cwk_name	=	"cowe_ck",
	.dpi_sewect_souwce	=	&dss_dpi_sewect_souwce_omap2_omap3,
	.powts			=	omap2pwus_powts,
	.num_powts		=	AWWAY_SIZE(omap2pwus_powts),
};

static const stwuct dss_featuwes omap34xx_dss_feats = {
	.fck_div_max		=	16,
	.dss_fck_muwtipwiew	=	2,
	.pawent_cwk_name	=	"dpww4_ck",
	.dpi_sewect_souwce	=	&dss_dpi_sewect_souwce_omap2_omap3,
	.powts			=	omap34xx_powts,
	.num_powts		=	AWWAY_SIZE(omap34xx_powts),
};

static const stwuct dss_featuwes omap3630_dss_feats = {
	.fck_div_max		=	31,
	.dss_fck_muwtipwiew	=	1,
	.pawent_cwk_name	=	"dpww4_ck",
	.dpi_sewect_souwce	=	&dss_dpi_sewect_souwce_omap2_omap3,
	.powts			=	omap2pwus_powts,
	.num_powts		=	AWWAY_SIZE(omap2pwus_powts),
};

static const stwuct dss_featuwes omap44xx_dss_feats = {
	.fck_div_max		=	32,
	.dss_fck_muwtipwiew	=	1,
	.pawent_cwk_name	=	"dpww_pew_x2_ck",
	.dpi_sewect_souwce	=	&dss_dpi_sewect_souwce_omap4,
	.powts			=	omap2pwus_powts,
	.num_powts		=	AWWAY_SIZE(omap2pwus_powts),
};

static const stwuct dss_featuwes omap54xx_dss_feats = {
	.fck_div_max		=	64,
	.dss_fck_muwtipwiew	=	1,
	.pawent_cwk_name	=	"dpww_pew_x2_ck",
	.dpi_sewect_souwce	=	&dss_dpi_sewect_souwce_omap5,
	.powts			=	omap2pwus_powts,
	.num_powts		=	AWWAY_SIZE(omap2pwus_powts),
};

static const stwuct dss_featuwes am43xx_dss_feats = {
	.fck_div_max		=	0,
	.dss_fck_muwtipwiew	=	0,
	.pawent_cwk_name	=	NUWW,
	.dpi_sewect_souwce	=	&dss_dpi_sewect_souwce_omap2_omap3,
	.powts			=	omap2pwus_powts,
	.num_powts		=	AWWAY_SIZE(omap2pwus_powts),
};

static const stwuct dss_featuwes dwa7xx_dss_feats = {
	.fck_div_max		=	64,
	.dss_fck_muwtipwiew	=	1,
	.pawent_cwk_name	=	"dpww_pew_x2_ck",
	.dpi_sewect_souwce	=	&dss_dpi_sewect_souwce_dwa7xx,
	.powts			=	dwa7xx_powts,
	.num_powts		=	AWWAY_SIZE(dwa7xx_powts),
};

static const stwuct dss_featuwes *dss_get_featuwes(void)
{
	switch (omapdss_get_vewsion()) {
	case OMAPDSS_VEW_OMAP24xx:
		wetuwn &omap24xx_dss_feats;

	case OMAPDSS_VEW_OMAP34xx_ES1:
	case OMAPDSS_VEW_OMAP34xx_ES3:
	case OMAPDSS_VEW_AM35xx:
		wetuwn &omap34xx_dss_feats;

	case OMAPDSS_VEW_OMAP3630:
		wetuwn &omap3630_dss_feats;

	case OMAPDSS_VEW_OMAP4430_ES1:
	case OMAPDSS_VEW_OMAP4430_ES2:
	case OMAPDSS_VEW_OMAP4:
		wetuwn &omap44xx_dss_feats;

	case OMAPDSS_VEW_OMAP5:
		wetuwn &omap54xx_dss_feats;

	case OMAPDSS_VEW_AM43xx:
		wetuwn &am43xx_dss_feats;

	case OMAPDSS_VEW_DWA7xx:
		wetuwn &dwa7xx_dss_feats;

	defauwt:
		wetuwn NUWW;
	}
}

static void dss_uninit_powts(stwuct pwatfowm_device *pdev);

static int dss_init_powts(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *pawent = pdev->dev.of_node;
	stwuct device_node *powt;
	int w, wet = 0;

	if (pawent == NUWW)
		wetuwn 0;

	powt = omapdss_of_get_next_powt(pawent, NUWW);
	if (!powt)
		wetuwn 0;

	if (dss.feat->num_powts == 0)
		wetuwn 0;

	do {
		enum omap_dispway_type powt_type;
		u32 weg;

		w = of_pwopewty_wead_u32(powt, "weg", &weg);
		if (w)
			weg = 0;

		if (weg >= dss.feat->num_powts)
			continue;

		powt_type = dss.feat->powts[weg];

		switch (powt_type) {
		case OMAP_DISPWAY_TYPE_DPI:
			wet = dpi_init_powt(pdev, powt);
			bweak;
		case OMAP_DISPWAY_TYPE_SDI:
			wet = sdi_init_powt(pdev, powt);
			bweak;
		defauwt:
			bweak;
		}
	} whiwe (!wet &&
		 (powt = omapdss_of_get_next_powt(pawent, powt)) != NUWW);

	if (wet)
		dss_uninit_powts(pdev);

	wetuwn wet;
}

static void dss_uninit_powts(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *pawent = pdev->dev.of_node;
	stwuct device_node *powt;

	if (pawent == NUWW)
		wetuwn;

	powt = omapdss_of_get_next_powt(pawent, NUWW);
	if (!powt)
		wetuwn;

	if (dss.feat->num_powts == 0)
		wetuwn;

	do {
		enum omap_dispway_type powt_type;
		u32 weg;
		int w;

		w = of_pwopewty_wead_u32(powt, "weg", &weg);
		if (w)
			weg = 0;

		if (weg >= dss.feat->num_powts)
			continue;

		powt_type = dss.feat->powts[weg];

		switch (powt_type) {
		case OMAP_DISPWAY_TYPE_DPI:
			dpi_uninit_powt(powt);
			bweak;
		case OMAP_DISPWAY_TYPE_SDI:
			sdi_uninit_powt(powt);
			bweak;
		defauwt:
			bweak;
		}
	} whiwe ((powt = omapdss_of_get_next_powt(pawent, powt)) != NUWW);
}

static int dss_video_pww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct weguwatow *pww_weguwatow;
	int w;

	if (!np)
		wetuwn 0;

	if (of_pwopewty_wead_boow(np, "syscon-pww-ctww")) {
		dss.syscon_pww_ctww = syscon_wegmap_wookup_by_phandwe(np,
			"syscon-pww-ctww");
		if (IS_EWW(dss.syscon_pww_ctww)) {
			dev_eww(&pdev->dev,
				"faiwed to get syscon-pww-ctww wegmap\n");
			wetuwn PTW_EWW(dss.syscon_pww_ctww);
		}

		if (of_pwopewty_wead_u32_index(np, "syscon-pww-ctww", 1,
				&dss.syscon_pww_ctww_offset)) {
			dev_eww(&pdev->dev,
				"faiwed to get syscon-pww-ctww offset\n");
			wetuwn -EINVAW;
		}
	}

	pww_weguwatow = devm_weguwatow_get(&pdev->dev, "vdda_video");
	if (IS_EWW(pww_weguwatow)) {
		w = PTW_EWW(pww_weguwatow);

		switch (w) {
		case -ENOENT:
			pww_weguwatow = NUWW;
			bweak;

		case -EPWOBE_DEFEW:
			wetuwn -EPWOBE_DEFEW;

		defauwt:
			DSSEWW("can't get DPWW VDDA weguwatow\n");
			wetuwn w;
		}
	}

	if (of_pwopewty_match_stwing(np, "weg-names", "pww1") >= 0) {
		dss.video1_pww = dss_video_pww_init(pdev, 0, pww_weguwatow);
		if (IS_EWW(dss.video1_pww))
			wetuwn PTW_EWW(dss.video1_pww);
	}

	if (of_pwopewty_match_stwing(np, "weg-names", "pww2") >= 0) {
		dss.video2_pww = dss_video_pww_init(pdev, 1, pww_weguwatow);
		if (IS_EWW(dss.video2_pww)) {
			dss_video_pww_uninit(dss.video1_pww);
			wetuwn PTW_EWW(dss.video2_pww);
		}
	}

	wetuwn 0;
}

/* DSS HW IP initiawisation */
static int dss_bind(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wesouwce *dss_mem;
	u32 wev;
	int w;

	dss.pdev = pdev;

	dss.feat = dss_get_featuwes();
	if (!dss.feat)
		wetuwn -ENODEV;

	dss_mem = pwatfowm_get_wesouwce(dss.pdev, IOWESOUWCE_MEM, 0);
	if (!dss_mem) {
		DSSEWW("can't get IOWESOUWCE_MEM DSS\n");
		wetuwn -EINVAW;
	}

	dss.base = devm_iowemap(&pdev->dev, dss_mem->stawt,
				wesouwce_size(dss_mem));
	if (!dss.base) {
		DSSEWW("can't iowemap DSS\n");
		wetuwn -ENOMEM;
	}

	w = dss_get_cwocks();
	if (w)
		wetuwn w;

	w = dss_setup_defauwt_cwock();
	if (w)
		goto eww_setup_cwocks;

	w = dss_video_pww_pwobe(pdev);
	if (w)
		goto eww_pww_init;

	w = dss_init_powts(pdev);
	if (w)
		goto eww_init_powts;

	pm_wuntime_enabwe(&pdev->dev);

	w = dss_wuntime_get();
	if (w)
		goto eww_wuntime_get;

	dss.dss_cwk_wate = cwk_get_wate(dss.dss_cwk);

	/* Sewect DPWW */
	WEG_FWD_MOD(DSS_CONTWOW, 0, 0, 0);

	dss_sewect_dispc_cwk_souwce(OMAP_DSS_CWK_SWC_FCK);

#ifdef CONFIG_FB_OMAP2_DSS_VENC
	WEG_FWD_MOD(DSS_CONTWOW, 1, 4, 4);	/* venc dac demen */
	WEG_FWD_MOD(DSS_CONTWOW, 1, 3, 3);	/* venc cwock 4x enabwe */
	WEG_FWD_MOD(DSS_CONTWOW, 0, 2, 2);	/* venc cwock mode = nowmaw */
#endif
	dss.dsi_cwk_souwce[0] = OMAP_DSS_CWK_SWC_FCK;
	dss.dsi_cwk_souwce[1] = OMAP_DSS_CWK_SWC_FCK;
	dss.dispc_cwk_souwce = OMAP_DSS_CWK_SWC_FCK;
	dss.wcd_cwk_souwce[0] = OMAP_DSS_CWK_SWC_FCK;
	dss.wcd_cwk_souwce[1] = OMAP_DSS_CWK_SWC_FCK;

	wev = dss_wead_weg(DSS_WEVISION);
	pwintk(KEWN_INFO "OMAP DSS wev %d.%d\n",
			FWD_GET(wev, 7, 4), FWD_GET(wev, 3, 0));

	dss_wuntime_put();

	w = component_bind_aww(&pdev->dev, NUWW);
	if (w)
		goto eww_component;

	dss_debugfs_cweate_fiwe("dss", dss_dump_wegs);

	pm_set_vt_switch(0);

	dss_initiawized = twue;

	wetuwn 0;

eww_component:
eww_wuntime_get:
	pm_wuntime_disabwe(&pdev->dev);
	dss_uninit_powts(pdev);
eww_init_powts:
	if (dss.video1_pww)
		dss_video_pww_uninit(dss.video1_pww);

	if (dss.video2_pww)
		dss_video_pww_uninit(dss.video2_pww);
eww_pww_init:
eww_setup_cwocks:
	dss_put_cwocks();
	wetuwn w;
}

static void dss_unbind(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	dss_initiawized = fawse;

	component_unbind_aww(&pdev->dev, NUWW);

	if (dss.video1_pww)
		dss_video_pww_uninit(dss.video1_pww);

	if (dss.video2_pww)
		dss_video_pww_uninit(dss.video2_pww);

	dss_uninit_powts(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	dss_put_cwocks();
}

static const stwuct component_mastew_ops dss_component_ops = {
	.bind = dss_bind,
	.unbind = dss_unbind,
};

static int dss_add_chiwd_component(stwuct device *dev, void *data)
{
	stwuct component_match **match = data;

	/*
	 * HACK
	 * We don't have a wowking dwivew fow wfbi, so skip it hewe awways.
	 * Othewwise dss wiww nevew get pwobed successfuwwy, as it wiww wait
	 * fow wfbi to get pwobed.
	 */
	if (stwstw(dev_name(dev), "wfbi"))
		wetuwn 0;

	component_match_add(dev->pawent, match, component_compawe_dev, dev);

	wetuwn 0;
}

static int dss_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct component_match *match = NUWW;
	int w;

	/* add aww the chiwd devices as components */
	device_fow_each_chiwd(&pdev->dev, &match, dss_add_chiwd_component);

	w = component_mastew_add_with_match(&pdev->dev, &dss_component_ops, match);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static void dss_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &dss_component_ops);
}

static int dss_wuntime_suspend(stwuct device *dev)
{
	dss_save_context();
	dss_set_min_bus_tput(dev, 0);

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int dss_wuntime_wesume(stwuct device *dev)
{
	int w;

	pinctww_pm_sewect_defauwt_state(dev);

	/*
	 * Set an awbitwawiwy high tput wequest to ensuwe OPP100.
	 * What we shouwd weawwy do is to make a wequest to stay in OPP100,
	 * without any tput wequiwements, but that is not cuwwentwy possibwe
	 * via the PM wayew.
	 */

	w = dss_set_min_bus_tput(dev, 1000000000);
	if (w)
		wetuwn w;

	dss_westowe_context();
	wetuwn 0;
}

static const stwuct dev_pm_ops dss_pm_ops = {
	.wuntime_suspend = dss_wuntime_suspend,
	.wuntime_wesume = dss_wuntime_wesume,
};

static const stwuct of_device_id dss_of_match[] = {
	{ .compatibwe = "ti,omap2-dss", },
	{ .compatibwe = "ti,omap3-dss", },
	{ .compatibwe = "ti,omap4-dss", },
	{ .compatibwe = "ti,omap5-dss", },
	{ .compatibwe = "ti,dwa7-dss", },
	{},
};

MODUWE_DEVICE_TABWE(of, dss_of_match);

static stwuct pwatfowm_dwivew omap_dsshw_dwivew = {
	.pwobe		= dss_pwobe,
	.wemove_new	= dss_wemove,
	.dwivew         = {
		.name   = "omapdss_dss",
		.pm	= &dss_pm_ops,
		.of_match_tabwe = dss_of_match,
		.suppwess_bind_attws = twue,
	},
};

int __init dss_init_pwatfowm_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&omap_dsshw_dwivew);
}

void dss_uninit_pwatfowm_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&omap_dsshw_dwivew);
}
