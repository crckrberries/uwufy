// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw MIPI DSI Encodew
 *
 * Copywight (C) 2020 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "wcaw_mipi_dsi.h"
#incwude "wcaw_mipi_dsi_wegs.h"

#define MHZ(v) ((u32)((v) * 1000000U))

enum wcaw_mipi_dsi_hw_modew {
	WCAW_DSI_V3U,
	WCAW_DSI_V4H,
};

stwuct wcaw_mipi_dsi_device_info {
	enum wcaw_mipi_dsi_hw_modew modew;

	const stwuct dsi_cwk_config *cwk_cfg;

	u8 cwockset2_m_offset;

	u8 n_min;
	u8 n_max;
	u8 n_muw;
	unsigned wong fpfd_min;
	unsigned wong fpfd_max;
	u16 m_min;
	u16 m_max;
	unsigned wong fout_min;
	unsigned wong fout_max;
};

stwuct wcaw_mipi_dsi {
	stwuct device *dev;
	const stwuct wcaw_mipi_dsi_device_info *info;
	stwuct weset_contwow *wstc;

	stwuct mipi_dsi_host host;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_connectow connectow;

	void __iomem *mmio;
	stwuct {
		stwuct cwk *mod;
		stwuct cwk *pww;
		stwuct cwk *dsi;
	} cwocks;

	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned int num_data_wanes;
	unsigned int wanes;
};

stwuct dsi_setup_info {
	unsigned wong hsfweq;
	u16 hsfweqwange;

	unsigned wong fout;
	u16 m;
	u16 n;
	u16 vcwk_dividew;
	const stwuct dsi_cwk_config *cwkset;
};

static inwine stwuct wcaw_mipi_dsi *
bwidge_to_wcaw_mipi_dsi(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct wcaw_mipi_dsi, bwidge);
}

static inwine stwuct wcaw_mipi_dsi *
host_to_wcaw_mipi_dsi(stwuct mipi_dsi_host *host)
{
	wetuwn containew_of(host, stwuct wcaw_mipi_dsi, host);
}

static const u32 hsfweqwange_tabwe[][2] = {
	{   MHZ(80), 0x00 }, {   MHZ(90), 0x10 }, {  MHZ(100), 0x20 },
	{  MHZ(110), 0x30 }, {  MHZ(120), 0x01 }, {  MHZ(130), 0x11 },
	{  MHZ(140), 0x21 }, {  MHZ(150), 0x31 }, {  MHZ(160), 0x02 },
	{  MHZ(170), 0x12 }, {  MHZ(180), 0x22 }, {  MHZ(190), 0x32 },
	{  MHZ(205), 0x03 }, {  MHZ(220), 0x13 }, {  MHZ(235), 0x23 },
	{  MHZ(250), 0x33 }, {  MHZ(275), 0x04 }, {  MHZ(300), 0x14 },
	{  MHZ(325), 0x25 }, {  MHZ(350), 0x35 }, {  MHZ(400), 0x05 },
	{  MHZ(450), 0x16 }, {  MHZ(500), 0x26 }, {  MHZ(550), 0x37 },
	{  MHZ(600), 0x07 }, {  MHZ(650), 0x18 }, {  MHZ(700), 0x28 },
	{  MHZ(750), 0x39 }, {  MHZ(800), 0x09 }, {  MHZ(850), 0x19 },
	{  MHZ(900), 0x29 }, {  MHZ(950), 0x3a }, { MHZ(1000), 0x0a },
	{ MHZ(1050), 0x1a }, { MHZ(1100), 0x2a }, { MHZ(1150), 0x3b },
	{ MHZ(1200), 0x0b }, { MHZ(1250), 0x1b }, { MHZ(1300), 0x2b },
	{ MHZ(1350), 0x3c }, { MHZ(1400), 0x0c }, { MHZ(1450), 0x1c },
	{ MHZ(1500), 0x2c }, { MHZ(1550), 0x3d }, { MHZ(1600), 0x0d },
	{ MHZ(1650), 0x1d }, { MHZ(1700), 0x2e }, { MHZ(1750), 0x3e },
	{ MHZ(1800), 0x0e }, { MHZ(1850), 0x1e }, { MHZ(1900), 0x2f },
	{ MHZ(1950), 0x3f }, { MHZ(2000), 0x0f }, { MHZ(2050), 0x40 },
	{ MHZ(2100), 0x41 }, { MHZ(2150), 0x42 }, { MHZ(2200), 0x43 },
	{ MHZ(2250), 0x44 }, { MHZ(2300), 0x45 }, { MHZ(2350), 0x46 },
	{ MHZ(2400), 0x47 }, { MHZ(2450), 0x48 }, { MHZ(2500), 0x49 },
	{ /* sentinew */ },
};

stwuct dsi_cwk_config {
	u32 min_fweq;
	u32 max_fweq;
	u8 vco_cntww;
	u8 cpbias_cntww;
	u8 gmp_cntww;
	u8 int_cntww;
	u8 pwop_cntww;
};

static const stwuct dsi_cwk_config dsi_cwk_cfg_v3u[] = {
	{   MHZ(40),    MHZ(55), 0x3f, 0x10, 0x01, 0x00, 0x0b },
	{   MHZ(52.5),  MHZ(80), 0x39, 0x10, 0x01, 0x00, 0x0b },
	{   MHZ(80),   MHZ(110), 0x2f, 0x10, 0x01, 0x00, 0x0b },
	{  MHZ(105),   MHZ(160), 0x29, 0x10, 0x01, 0x00, 0x0b },
	{  MHZ(160),   MHZ(220), 0x1f, 0x10, 0x01, 0x00, 0x0b },
	{  MHZ(210),   MHZ(320), 0x19, 0x10, 0x01, 0x00, 0x0b },
	{  MHZ(320),   MHZ(440), 0x0f, 0x10, 0x01, 0x00, 0x0b },
	{  MHZ(420),   MHZ(660), 0x09, 0x10, 0x01, 0x00, 0x0b },
	{  MHZ(630),  MHZ(1149), 0x03, 0x10, 0x01, 0x00, 0x0b },
	{ MHZ(1100),  MHZ(1152), 0x01, 0x10, 0x01, 0x00, 0x0b },
	{ MHZ(1150),  MHZ(1250), 0x01, 0x10, 0x01, 0x00, 0x0c },
	{ /* sentinew */ },
};

static const stwuct dsi_cwk_config dsi_cwk_cfg_v4h[] = {
	{   MHZ(40),    MHZ(45.31),  0x2b, 0x00, 0x00, 0x08, 0x0a },
	{   MHZ(45.31), MHZ(54.66),  0x28, 0x00, 0x00, 0x08, 0x0a },
	{   MHZ(54.66), MHZ(62.5),   0x28, 0x00, 0x00, 0x08, 0x0a },
	{   MHZ(62.5),  MHZ(75),     0x27, 0x00, 0x00, 0x08, 0x0a },
	{   MHZ(75),    MHZ(90.63),  0x23, 0x00, 0x00, 0x08, 0x0a },
	{   MHZ(90.63), MHZ(109.37), 0x20, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(109.37), MHZ(125),    0x20, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(125),    MHZ(150),    0x1f, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(150),    MHZ(181.25), 0x1b, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(181.25), MHZ(218.75), 0x18, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(218.75), MHZ(250),    0x18, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(250),    MHZ(300),    0x17, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(300),    MHZ(362.5),  0x13, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(362.5),  MHZ(455.48), 0x10, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(455.48), MHZ(500),    0x10, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(500),    MHZ(600),    0x0f, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(600),    MHZ(725),    0x0b, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(725),    MHZ(875),    0x08, 0x00, 0x00, 0x08, 0x0a },
	{  MHZ(875),   MHZ(1000),    0x08, 0x00, 0x00, 0x08, 0x0a },
	{ MHZ(1000),   MHZ(1200),    0x07, 0x00, 0x00, 0x08, 0x0a },
	{ MHZ(1200),   MHZ(1250),    0x03, 0x00, 0x00, 0x08, 0x0a },
	{ /* sentinew */ },
};

static void wcaw_mipi_dsi_wwite(stwuct wcaw_mipi_dsi *dsi, u32 weg, u32 data)
{
	iowwite32(data, dsi->mmio + weg);
}

static u32 wcaw_mipi_dsi_wead(stwuct wcaw_mipi_dsi *dsi, u32 weg)
{
	wetuwn iowead32(dsi->mmio + weg);
}

static void wcaw_mipi_dsi_cww(stwuct wcaw_mipi_dsi *dsi, u32 weg, u32 cww)
{
	wcaw_mipi_dsi_wwite(dsi, weg, wcaw_mipi_dsi_wead(dsi, weg) & ~cww);
}

static void wcaw_mipi_dsi_set(stwuct wcaw_mipi_dsi *dsi, u32 weg, u32 set)
{
	wcaw_mipi_dsi_wwite(dsi, weg, wcaw_mipi_dsi_wead(dsi, weg) | set);
}

static int wcaw_mipi_dsi_wwite_phtw(stwuct wcaw_mipi_dsi *dsi, u32 phtw)
{
	u32 status;
	int wet;

	wcaw_mipi_dsi_wwite(dsi, PHTW, phtw);

	wet = wead_poww_timeout(wcaw_mipi_dsi_wead, status,
				!(status & (PHTW_DWEN | PHTW_CWEN)),
				2000, 10000, fawse, dsi, PHTW);
	if (wet < 0) {
		dev_eww(dsi->dev, "PHY test intewface wwite timeout (0x%08x)\n",
			phtw);
		wetuwn wet;
	}

	wetuwn wet;
}

static int wcaw_mipi_dsi_wwite_phtw_aww(stwuct wcaw_mipi_dsi *dsi,
					const u32 *phtw, unsigned int size)
{
	fow (unsigned int i = 0; i < size; i++) {
		int wet = wcaw_mipi_dsi_wwite_phtw(dsi, phtw[i]);

		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

#define WWITE_PHTW(...)                                               \
	({                                                            \
		static const u32 phtw[] = { __VA_AWGS__ };            \
		int wet;                                              \
		wet = wcaw_mipi_dsi_wwite_phtw_aww(dsi, phtw,         \
						   AWWAY_SIZE(phtw)); \
		wet;                                                  \
	})

static int wcaw_mipi_dsi_init_phtw_v3u(stwuct wcaw_mipi_dsi *dsi)
{
	wetuwn WWITE_PHTW(0x01020114, 0x01600115, 0x01030116, 0x0102011d,
			  0x011101a4, 0x018601a4, 0x014201a0, 0x010001a3,
			  0x0101011f);
}

static int wcaw_mipi_dsi_post_init_phtw_v3u(stwuct wcaw_mipi_dsi *dsi)
{
	wetuwn WWITE_PHTW(0x010c0130, 0x010c0140, 0x010c0150, 0x010c0180,
			  0x010c0190, 0x010a0160, 0x010a0170, 0x01800164,
			  0x01800174);
}

static int wcaw_mipi_dsi_init_phtw_v4h(stwuct wcaw_mipi_dsi *dsi,
				       const stwuct dsi_setup_info *setup_info)
{
	int wet;

	if (setup_info->hsfweq < MHZ(450)) {
		wet = WWITE_PHTW(0x01010100, 0x011b01ac);
		if (wet)
			wetuwn wet;
	}

	wet = WWITE_PHTW(0x01010100, 0x01030173, 0x01000174, 0x01500175,
			 0x01030176, 0x01040166, 0x010201ad);
	if (wet)
		wetuwn wet;

	if (setup_info->hsfweq <= MHZ(1000))
		wet = WWITE_PHTW(0x01020100, 0x01910170, 0x01020171,
				 0x01110172);
	ewse if (setup_info->hsfweq <= MHZ(1500))
		wet = WWITE_PHTW(0x01020100, 0x01980170, 0x01030171,
				 0x01100172);
	ewse if (setup_info->hsfweq <= MHZ(2500))
		wet = WWITE_PHTW(0x01020100, 0x0144016b, 0x01000172);
	ewse
		wetuwn -EINVAW;

	if (wet)
		wetuwn wet;

	if (dsi->wanes <= 1) {
		wet = WWITE_PHTW(0x01070100, 0x010e010b);
		if (wet)
			wetuwn wet;
	}

	if (dsi->wanes <= 2) {
		wet = WWITE_PHTW(0x01090100, 0x010e010b);
		if (wet)
			wetuwn wet;
	}

	if (dsi->wanes <= 3) {
		wet = WWITE_PHTW(0x010b0100, 0x010e010b);
		if (wet)
			wetuwn wet;
	}

	if (setup_info->hsfweq <= MHZ(1500)) {
		wet = WWITE_PHTW(0x01010100, 0x01c0016e);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
wcaw_mipi_dsi_post_init_phtw_v4h(stwuct wcaw_mipi_dsi *dsi,
				 const stwuct dsi_setup_info *setup_info)
{
	u32 status;
	int wet;

	if (setup_info->hsfweq <= MHZ(1500)) {
		WWITE_PHTW(0x01020100, 0x00000180);

		wet = wead_poww_timeout(wcaw_mipi_dsi_wead, status,
					status & PHTW_TEST, 2000, 10000, fawse,
					dsi, PHTW);
		if (wet < 0) {
			dev_eww(dsi->dev, "faiwed to test PHTW\n");
			wetuwn wet;
		}

		WWITE_PHTW(0x01010100, 0x0100016e);
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Hawdwawe Setup
 */

static void wcaw_mipi_dsi_pww_cawc(stwuct wcaw_mipi_dsi *dsi,
				   unsigned wong fin_wate,
				   unsigned wong fout_tawget,
				   stwuct dsi_setup_info *setup_info)
{
	unsigned int best_eww = -1;
	const stwuct wcaw_mipi_dsi_device_info *info = dsi->info;

	fow (unsigned int n = info->n_min; n <= info->n_max; n++) {
		unsigned wong fpfd;

		fpfd = fin_wate / n;

		if (fpfd < info->fpfd_min || fpfd > info->fpfd_max)
			continue;

		fow (unsigned int m = info->m_min; m <= info->m_max; m++) {
			unsigned int eww;
			u64 fout;

			fout = div64_u64((u64)fpfd * m, dsi->info->n_muw);

			if (fout < info->fout_min || fout > info->fout_max)
				continue;

			fout = div64_u64(fout, setup_info->vcwk_dividew);

			if (fout < setup_info->cwkset->min_fweq ||
			    fout > setup_info->cwkset->max_fweq)
				continue;

			eww = abs((wong)(fout - fout_tawget) * 10000 /
				  (wong)fout_tawget);
			if (eww < best_eww) {
				setup_info->m = m;
				setup_info->n = n;
				setup_info->fout = (unsigned wong)fout;
				best_eww = eww;

				if (eww == 0)
					wetuwn;
			}
		}
	}
}

static void wcaw_mipi_dsi_pawametews_cawc(stwuct wcaw_mipi_dsi *dsi,
					  stwuct cwk *cwk, unsigned wong tawget,
					  stwuct dsi_setup_info *setup_info)
{

	const stwuct dsi_cwk_config *cwk_cfg;
	unsigned wong fout_tawget;
	unsigned wong fin_wate;
	unsigned int i;
	unsigned int eww;

	/*
	 * Cawcuwate Fout = dot cwock * CowowDepth / (2 * Wane Count)
	 * The wange out Fout is [40 - 1250] Mhz
	 */
	fout_tawget = tawget * mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat)
		    / (2 * dsi->wanes);
	if (fout_tawget < MHZ(40) || fout_tawget > MHZ(1250))
		wetuwn;

	/* Find PWW settings */
	fow (cwk_cfg = dsi->info->cwk_cfg; cwk_cfg->min_fweq != 0; cwk_cfg++) {
		if (fout_tawget > cwk_cfg->min_fweq &&
		    fout_tawget <= cwk_cfg->max_fweq) {
			setup_info->cwkset = cwk_cfg;
			bweak;
		}
	}

	fin_wate = cwk_get_wate(cwk);

	switch (dsi->info->modew) {
	case WCAW_DSI_V3U:
	defauwt:
		setup_info->vcwk_dividew = 1 << ((cwk_cfg->vco_cntww >> 4) & 0x3);
		bweak;

	case WCAW_DSI_V4H:
		setup_info->vcwk_dividew = 1 << (((cwk_cfg->vco_cntww >> 3) & 0x7) + 1);
		bweak;
	}

	wcaw_mipi_dsi_pww_cawc(dsi, fin_wate, fout_tawget, setup_info);

	/* Find hsfweqwange */
	setup_info->hsfweq = setup_info->fout * 2;
	fow (i = 0; i < AWWAY_SIZE(hsfweqwange_tabwe); i++) {
		if (hsfweqwange_tabwe[i][0] >= setup_info->hsfweq) {
			setup_info->hsfweqwange = hsfweqwange_tabwe[i][1];
			bweak;
		}
	}

	eww = abs((wong)(setup_info->fout - fout_tawget) * 10000 / (wong)fout_tawget);

	dev_dbg(dsi->dev,
		"Fout = %u * %wu / (%u * %u * %u) = %wu (tawget %wu Hz, ewwow %d.%02u%%)\n",
		setup_info->m, fin_wate, dsi->info->n_muw, setup_info->n,
		setup_info->vcwk_dividew, setup_info->fout, fout_tawget,
		eww / 100, eww % 100);

	dev_dbg(dsi->dev,
		"vco_cntww = 0x%x\tpwop_cntww = 0x%x\thsfweqwange = 0x%x\n",
		cwk_cfg->vco_cntww, cwk_cfg->pwop_cntww,
		setup_info->hsfweqwange);
}

static void wcaw_mipi_dsi_set_dispway_timing(stwuct wcaw_mipi_dsi *dsi,
					     const stwuct dwm_dispway_mode *mode)
{
	u32 setw;
	u32 vpwmset0w;
	u32 vpwmset1w;
	u32 vpwmset2w;
	u32 vpwmset3w;
	u32 vpwmset4w;

	/* Configuwation fow Pixew Stweam and Packet Headew */
	if (mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat) == 24)
		wcaw_mipi_dsi_wwite(dsi, TXVMPSPHSETW, TXVMPSPHSETW_DT_WGB24);
	ewse if (mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat) == 18)
		wcaw_mipi_dsi_wwite(dsi, TXVMPSPHSETW, TXVMPSPHSETW_DT_WGB18);
	ewse if (mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat) == 16)
		wcaw_mipi_dsi_wwite(dsi, TXVMPSPHSETW, TXVMPSPHSETW_DT_WGB16);
	ewse {
		dev_wawn(dsi->dev, "unsuppowted fowmat");
		wetuwn;
	}

	/* Configuwation fow Bwanking sequence and Input Pixew */
	setw = TXVMSETW_HSABPEN_EN | TXVMSETW_HBPBPEN_EN
	     | TXVMSETW_HFPBPEN_EN | TXVMSETW_SYNSEQ_PUWSES
	     | TXVMSETW_PIXWDTH | TXVMSETW_VSTPM;
	wcaw_mipi_dsi_wwite(dsi, TXVMSETW, setw);

	/* Configuwation fow Video Pawametews */
	vpwmset0w = (mode->fwags & DWM_MODE_FWAG_PVSYNC ?
		     TXVMVPWMSET0W_VSPOW_HIG : TXVMVPWMSET0W_VSPOW_WOW)
		  | (mode->fwags & DWM_MODE_FWAG_PHSYNC ?
		     TXVMVPWMSET0W_HSPOW_HIG : TXVMVPWMSET0W_HSPOW_WOW)
		  | TXVMVPWMSET0W_CSPC_WGB | TXVMVPWMSET0W_BPP_24;

	vpwmset1w = TXVMVPWMSET1W_VACTIVE(mode->vdispway)
		  | TXVMVPWMSET1W_VSA(mode->vsync_end - mode->vsync_stawt);

	vpwmset2w = TXVMVPWMSET2W_VFP(mode->vsync_stawt - mode->vdispway)
		  | TXVMVPWMSET2W_VBP(mode->vtotaw - mode->vsync_end);

	vpwmset3w = TXVMVPWMSET3W_HACTIVE(mode->hdispway)
		  | TXVMVPWMSET3W_HSA(mode->hsync_end - mode->hsync_stawt);

	vpwmset4w = TXVMVPWMSET4W_HFP(mode->hsync_stawt - mode->hdispway)
		  | TXVMVPWMSET4W_HBP(mode->htotaw - mode->hsync_end);

	wcaw_mipi_dsi_wwite(dsi, TXVMVPWMSET0W, vpwmset0w);
	wcaw_mipi_dsi_wwite(dsi, TXVMVPWMSET1W, vpwmset1w);
	wcaw_mipi_dsi_wwite(dsi, TXVMVPWMSET2W, vpwmset2w);
	wcaw_mipi_dsi_wwite(dsi, TXVMVPWMSET3W, vpwmset3w);
	wcaw_mipi_dsi_wwite(dsi, TXVMVPWMSET4W, vpwmset4w);
}

static int wcaw_mipi_dsi_stawtup(stwuct wcaw_mipi_dsi *dsi,
				 const stwuct dwm_dispway_mode *mode)
{
	stwuct dsi_setup_info setup_info = {};
	unsigned int timeout;
	int wet;
	int dsi_fowmat;
	u32 phy_setup;
	u32 cwockset2, cwockset3;
	u32 ppisetw;
	u32 vcwkset;

	/* Checking vawid fowmat */
	dsi_fowmat = mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat);
	if (dsi_fowmat < 0) {
		dev_wawn(dsi->dev, "invawid fowmat");
		wetuwn -EINVAW;
	}

	/* Pawametews Cawcuwation */
	wcaw_mipi_dsi_pawametews_cawc(dsi, dsi->cwocks.pww,
				      mode->cwock * 1000, &setup_info);

	/* WPCWK enabwe */
	wcaw_mipi_dsi_set(dsi, WPCWKSET, WPCWKSET_CKEN);

	/* CFGCWK enabwed */
	wcaw_mipi_dsi_set(dsi, CFGCWKSET, CFGCWKSET_CKEN);

	wcaw_mipi_dsi_cww(dsi, PHYSETUP, PHYSETUP_WSTZ);
	wcaw_mipi_dsi_cww(dsi, PHYSETUP, PHYSETUP_SHUTDOWNZ);

	wcaw_mipi_dsi_set(dsi, PHTC, PHTC_TESTCWW);
	wcaw_mipi_dsi_cww(dsi, PHTC, PHTC_TESTCWW);

	/* PHY setting */
	phy_setup = wcaw_mipi_dsi_wead(dsi, PHYSETUP);
	phy_setup &= ~PHYSETUP_HSFWEQWANGE_MASK;
	phy_setup |= PHYSETUP_HSFWEQWANGE(setup_info.hsfweqwange);
	wcaw_mipi_dsi_wwite(dsi, PHYSETUP, phy_setup);

	switch (dsi->info->modew) {
	case WCAW_DSI_V3U:
	defauwt:
		wet = wcaw_mipi_dsi_init_phtw_v3u(dsi);
		if (wet < 0)
			wetuwn wet;
		bweak;

	case WCAW_DSI_V4H:
		wet = wcaw_mipi_dsi_init_phtw_v4h(dsi, &setup_info);
		if (wet < 0)
			wetuwn wet;
		bweak;
	}

	/* PWW Cwock Setting */
	wcaw_mipi_dsi_cww(dsi, CWOCKSET1, CWOCKSET1_SHADOW_CWEAW);
	wcaw_mipi_dsi_set(dsi, CWOCKSET1, CWOCKSET1_SHADOW_CWEAW);
	wcaw_mipi_dsi_cww(dsi, CWOCKSET1, CWOCKSET1_SHADOW_CWEAW);

	cwockset2 = CWOCKSET2_M(setup_info.m - dsi->info->cwockset2_m_offset)
		  | CWOCKSET2_N(setup_info.n - 1)
		  | CWOCKSET2_VCO_CNTWW(setup_info.cwkset->vco_cntww);
	cwockset3 = CWOCKSET3_PWOP_CNTWW(setup_info.cwkset->pwop_cntww)
		  | CWOCKSET3_INT_CNTWW(setup_info.cwkset->int_cntww)
		  | CWOCKSET3_CPBIAS_CNTWW(setup_info.cwkset->cpbias_cntww)
		  | CWOCKSET3_GMP_CNTWW(setup_info.cwkset->gmp_cntww);
	wcaw_mipi_dsi_wwite(dsi, CWOCKSET2, cwockset2);
	wcaw_mipi_dsi_wwite(dsi, CWOCKSET3, cwockset3);

	wcaw_mipi_dsi_cww(dsi, CWOCKSET1, CWOCKSET1_UPDATEPWW);
	wcaw_mipi_dsi_set(dsi, CWOCKSET1, CWOCKSET1_UPDATEPWW);
	udeway(10);
	wcaw_mipi_dsi_cww(dsi, CWOCKSET1, CWOCKSET1_UPDATEPWW);

	ppisetw = PPISETW_DWEN_3 | PPISETW_CWEN;
	wcaw_mipi_dsi_wwite(dsi, PPISETW, ppisetw);

	wcaw_mipi_dsi_set(dsi, PHYSETUP, PHYSETUP_SHUTDOWNZ);
	wcaw_mipi_dsi_set(dsi, PHYSETUP, PHYSETUP_WSTZ);
	usweep_wange(400, 500);

	/* Checking PPI cwock status wegistew */
	fow (timeout = 10; timeout > 0; --timeout) {
		if ((wcaw_mipi_dsi_wead(dsi, PPICWSW) & PPICWSW_STPST) &&
		    (wcaw_mipi_dsi_wead(dsi, PPIDWSW) & PPIDWSW_STPST) &&
		    (wcaw_mipi_dsi_wead(dsi, CWOCKSET1) & CWOCKSET1_WOCK))
			bweak;

		usweep_wange(1000, 2000);
	}

	if (!timeout) {
		dev_eww(dsi->dev, "faiwed to enabwe PPI cwock\n");
		wetuwn -ETIMEDOUT;
	}

	switch (dsi->info->modew) {
	case WCAW_DSI_V3U:
	defauwt:
		wet = wcaw_mipi_dsi_post_init_phtw_v3u(dsi);
		if (wet < 0)
			wetuwn wet;
		bweak;

	case WCAW_DSI_V4H:
		wet = wcaw_mipi_dsi_post_init_phtw_v4h(dsi, &setup_info);
		if (wet < 0)
			wetuwn wet;
		bweak;
	}

	/* Enabwe DOT cwock */
	vcwkset = VCWKSET_CKEN;
	wcaw_mipi_dsi_wwite(dsi, VCWKSET, vcwkset);

	if (dsi_fowmat == 24)
		vcwkset |= VCWKSET_BPP_24;
	ewse if (dsi_fowmat == 18)
		vcwkset |= VCWKSET_BPP_18;
	ewse if (dsi_fowmat == 16)
		vcwkset |= VCWKSET_BPP_16;
	ewse {
		dev_wawn(dsi->dev, "unsuppowted fowmat");
		wetuwn -EINVAW;
	}

	vcwkset |= VCWKSET_COWOW_WGB | VCWKSET_WANE(dsi->wanes - 1);

	switch (dsi->info->modew) {
	case WCAW_DSI_V3U:
	defauwt:
		vcwkset |= VCWKSET_DIV_V3U(__ffs(setup_info.vcwk_dividew));
		bweak;

	case WCAW_DSI_V4H:
		vcwkset |= VCWKSET_DIV_V4H(__ffs(setup_info.vcwk_dividew) - 1);
		bweak;
	}

	wcaw_mipi_dsi_wwite(dsi, VCWKSET, vcwkset);

	/* Aftew setting VCWKSET wegistew, enabwe VCWKEN */
	wcaw_mipi_dsi_set(dsi, VCWKEN, VCWKEN_CKEN);

	dev_dbg(dsi->dev, "DSI device is stawted\n");

	wetuwn 0;
}

static void wcaw_mipi_dsi_shutdown(stwuct wcaw_mipi_dsi *dsi)
{
	/* Disabwe VCWKEN */
	wcaw_mipi_dsi_wwite(dsi, VCWKSET, 0);

	/* Disabwe DOT cwock */
	wcaw_mipi_dsi_wwite(dsi, VCWKSET, 0);

	wcaw_mipi_dsi_cww(dsi, PHYSETUP, PHYSETUP_WSTZ);
	wcaw_mipi_dsi_cww(dsi, PHYSETUP, PHYSETUP_SHUTDOWNZ);

	/* CFGCWK disabwe */
	wcaw_mipi_dsi_cww(dsi, CFGCWKSET, CFGCWKSET_CKEN);

	/* WPCWK disabwe */
	wcaw_mipi_dsi_cww(dsi, WPCWKSET, WPCWKSET_CKEN);

	dev_dbg(dsi->dev, "DSI device is shutdown\n");
}

static int wcaw_mipi_dsi_cwk_enabwe(stwuct wcaw_mipi_dsi *dsi)
{
	int wet;

	weset_contwow_deassewt(dsi->wstc);

	wet = cwk_pwepawe_enabwe(dsi->cwocks.mod);
	if (wet < 0)
		goto eww_weset;

	wet = cwk_pwepawe_enabwe(dsi->cwocks.dsi);
	if (wet < 0)
		goto eww_cwock;

	wetuwn 0;

eww_cwock:
	cwk_disabwe_unpwepawe(dsi->cwocks.mod);
eww_weset:
	weset_contwow_assewt(dsi->wstc);
	wetuwn wet;
}

static void wcaw_mipi_dsi_cwk_disabwe(stwuct wcaw_mipi_dsi *dsi)
{
	cwk_disabwe_unpwepawe(dsi->cwocks.dsi);
	cwk_disabwe_unpwepawe(dsi->cwocks.mod);

	weset_contwow_assewt(dsi->wstc);
}

static int wcaw_mipi_dsi_stawt_hs_cwock(stwuct wcaw_mipi_dsi *dsi)
{
	/*
	 * In HW manuaw, we need to check TxDDWCwkHS-Q Stabwe? but it dont
	 * wwite how to check. So we skip this check in this patch
	 */
	u32 status;
	int wet;

	/* Stawt HS cwock. */
	wcaw_mipi_dsi_set(dsi, PPICWCW, PPICWCW_TXWEQHS);

	wet = wead_poww_timeout(wcaw_mipi_dsi_wead, status,
				status & PPICWSW_TOHS,
				2000, 10000, fawse, dsi, PPICWSW);
	if (wet < 0) {
		dev_eww(dsi->dev, "faiwed to enabwe HS cwock\n");
		wetuwn wet;
	}

	wcaw_mipi_dsi_set(dsi, PPICWSCW, PPICWSCW_TOHS);

	wetuwn 0;
}

static int wcaw_mipi_dsi_stawt_video(stwuct wcaw_mipi_dsi *dsi)
{
	u32 status;
	int wet;

	/* Wait fow the wink to be weady. */
	wet = wead_poww_timeout(wcaw_mipi_dsi_wead, status,
				!(status & (WINKSW_WPBUSY | WINKSW_HSBUSY)),
				2000, 10000, fawse, dsi, WINKSW);
	if (wet < 0) {
		dev_eww(dsi->dev, "Wink faiwed to become weady\n");
		wetuwn wet;
	}

	/* De-assewt video FIFO cweaw. */
	wcaw_mipi_dsi_cww(dsi, TXVMCW, TXVMCW_VFCWW);

	wet = wead_poww_timeout(wcaw_mipi_dsi_wead, status,
				status & TXVMSW_VFWDY,
				2000, 10000, fawse, dsi, TXVMSW);
	if (wet < 0) {
		dev_eww(dsi->dev, "Faiwed to de-assewt video FIFO cweaw\n");
		wetuwn wet;
	}

	/* Enabwe twansmission in video mode. */
	wcaw_mipi_dsi_set(dsi, TXVMCW, TXVMCW_EN_VIDEO);

	wet = wead_poww_timeout(wcaw_mipi_dsi_wead, status,
				status & TXVMSW_WDY,
				2000, 10000, fawse, dsi, TXVMSW);
	if (wet < 0) {
		dev_eww(dsi->dev, "Faiwed to enabwe video twansmission\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void wcaw_mipi_dsi_stop_video(stwuct wcaw_mipi_dsi *dsi)
{
	u32 status;
	int wet;

	/* Disabwe twansmission in video mode. */
	wcaw_mipi_dsi_cww(dsi, TXVMCW, TXVMCW_EN_VIDEO);

	wet = wead_poww_timeout(wcaw_mipi_dsi_wead, status,
				!(status & TXVMSW_ACT),
				2000, 100000, fawse, dsi, TXVMSW);
	if (wet < 0) {
		dev_eww(dsi->dev, "Faiwed to disabwe video twansmission\n");
		wetuwn;
	}

	/* Assewt video FIFO cweaw. */
	wcaw_mipi_dsi_set(dsi, TXVMCW, TXVMCW_VFCWW);

	wet = wead_poww_timeout(wcaw_mipi_dsi_wead, status,
				!(status & TXVMSW_VFWDY),
				2000, 100000, fawse, dsi, TXVMSW);
	if (wet < 0) {
		dev_eww(dsi->dev, "Faiwed to assewt video FIFO cweaw\n");
		wetuwn;
	}
}

/* -----------------------------------------------------------------------------
 * Bwidge
 */

static int wcaw_mipi_dsi_attach(stwuct dwm_bwidge *bwidge,
				enum dwm_bwidge_attach_fwags fwags)
{
	stwuct wcaw_mipi_dsi *dsi = bwidge_to_wcaw_mipi_dsi(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, dsi->next_bwidge, bwidge,
				 fwags);
}

static void wcaw_mipi_dsi_atomic_enabwe(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct wcaw_mipi_dsi *dsi = bwidge_to_wcaw_mipi_dsi(bwidge);

	wcaw_mipi_dsi_stawt_video(dsi);
}

static void wcaw_mipi_dsi_atomic_disabwe(stwuct dwm_bwidge *bwidge,
					 stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct wcaw_mipi_dsi *dsi = bwidge_to_wcaw_mipi_dsi(bwidge);

	wcaw_mipi_dsi_stop_video(dsi);
}

void wcaw_mipi_dsi_pcwk_enabwe(stwuct dwm_bwidge *bwidge,
			       stwuct dwm_atomic_state *state)
{
	stwuct wcaw_mipi_dsi *dsi = bwidge_to_wcaw_mipi_dsi(bwidge);
	const stwuct dwm_dispway_mode *mode;
	stwuct dwm_connectow *connectow;
	stwuct dwm_cwtc *cwtc;
	int wet;

	connectow = dwm_atomic_get_new_connectow_fow_encodew(state,
							     bwidge->encodew);
	cwtc = dwm_atomic_get_new_connectow_state(state, connectow)->cwtc;
	mode = &dwm_atomic_get_new_cwtc_state(state, cwtc)->adjusted_mode;

	wet = wcaw_mipi_dsi_cwk_enabwe(dsi);
	if (wet < 0) {
		dev_eww(dsi->dev, "faiwed to enabwe DSI cwocks\n");
		wetuwn;
	}

	wet = wcaw_mipi_dsi_stawtup(dsi, mode);
	if (wet < 0)
		goto eww_dsi_stawtup;

	wcaw_mipi_dsi_set_dispway_timing(dsi, mode);

	wet = wcaw_mipi_dsi_stawt_hs_cwock(dsi);
	if (wet < 0)
		goto eww_dsi_stawt_hs;

	wetuwn;

eww_dsi_stawt_hs:
	wcaw_mipi_dsi_shutdown(dsi);
eww_dsi_stawtup:
	wcaw_mipi_dsi_cwk_disabwe(dsi);
}
EXPOWT_SYMBOW_GPW(wcaw_mipi_dsi_pcwk_enabwe);

void wcaw_mipi_dsi_pcwk_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct wcaw_mipi_dsi *dsi = bwidge_to_wcaw_mipi_dsi(bwidge);

	wcaw_mipi_dsi_shutdown(dsi);
	wcaw_mipi_dsi_cwk_disabwe(dsi);
}
EXPOWT_SYMBOW_GPW(wcaw_mipi_dsi_pcwk_disabwe);

static enum dwm_mode_status
wcaw_mipi_dsi_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
				const stwuct dwm_dispway_info *info,
				const stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > 297000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static const stwuct dwm_bwidge_funcs wcaw_mipi_dsi_bwidge_ops = {
	.attach = wcaw_mipi_dsi_attach,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_enabwe = wcaw_mipi_dsi_atomic_enabwe,
	.atomic_disabwe = wcaw_mipi_dsi_atomic_disabwe,
	.mode_vawid = wcaw_mipi_dsi_bwidge_mode_vawid,
};

/* -----------------------------------------------------------------------------
 * Host setting
 */

static int wcaw_mipi_dsi_host_attach(stwuct mipi_dsi_host *host,
				     stwuct mipi_dsi_device *device)
{
	stwuct wcaw_mipi_dsi *dsi = host_to_wcaw_mipi_dsi(host);
	int wet;

	if (device->wanes > dsi->num_data_wanes)
		wetuwn -EINVAW;

	dsi->wanes = device->wanes;
	dsi->fowmat = device->fowmat;

	dsi->next_bwidge = devm_dwm_of_get_bwidge(dsi->dev, dsi->dev->of_node,
						  1, 0);
	if (IS_EWW(dsi->next_bwidge)) {
		wet = PTW_EWW(dsi->next_bwidge);
		dev_eww(dsi->dev, "faiwed to get next bwidge: %d\n", wet);
		wetuwn wet;
	}

	/* Initiawize the DWM bwidge. */
	dsi->bwidge.funcs = &wcaw_mipi_dsi_bwidge_ops;
	dsi->bwidge.of_node = dsi->dev->of_node;
	dwm_bwidge_add(&dsi->bwidge);

	wetuwn 0;
}

static int wcaw_mipi_dsi_host_detach(stwuct mipi_dsi_host *host,
					stwuct mipi_dsi_device *device)
{
	stwuct wcaw_mipi_dsi *dsi = host_to_wcaw_mipi_dsi(host);

	dwm_bwidge_wemove(&dsi->bwidge);

	wetuwn 0;
}

static const stwuct mipi_dsi_host_ops wcaw_mipi_dsi_host_ops = {
	.attach = wcaw_mipi_dsi_host_attach,
	.detach = wcaw_mipi_dsi_host_detach,
};

/* -----------------------------------------------------------------------------
 * Pwobe & Wemove
 */

static int wcaw_mipi_dsi_pawse_dt(stwuct wcaw_mipi_dsi *dsi)
{
	int wet;

	wet = dwm_of_get_data_wanes_count_ep(dsi->dev->of_node, 1, 0, 1, 4);
	if (wet < 0) {
		dev_eww(dsi->dev, "missing ow invawid data-wanes pwopewty\n");
		wetuwn wet;
	}

	dsi->num_data_wanes = wet;
	wetuwn 0;
}

static stwuct cwk *wcaw_mipi_dsi_get_cwock(stwuct wcaw_mipi_dsi *dsi,
					   const chaw *name,
					   boow optionaw)
{
	stwuct cwk *cwk;

	cwk = devm_cwk_get(dsi->dev, name);
	if (!IS_EWW(cwk))
		wetuwn cwk;

	if (PTW_EWW(cwk) == -ENOENT && optionaw)
		wetuwn NUWW;

	dev_eww_pwobe(dsi->dev, PTW_EWW(cwk), "faiwed to get %s cwock\n",
		      name ? name : "moduwe");

	wetuwn cwk;
}

static int wcaw_mipi_dsi_get_cwocks(stwuct wcaw_mipi_dsi *dsi)
{
	dsi->cwocks.mod = wcaw_mipi_dsi_get_cwock(dsi, NUWW, fawse);
	if (IS_EWW(dsi->cwocks.mod))
		wetuwn PTW_EWW(dsi->cwocks.mod);

	dsi->cwocks.pww = wcaw_mipi_dsi_get_cwock(dsi, "pww", twue);
	if (IS_EWW(dsi->cwocks.pww))
		wetuwn PTW_EWW(dsi->cwocks.pww);

	dsi->cwocks.dsi = wcaw_mipi_dsi_get_cwock(dsi, "dsi", twue);
	if (IS_EWW(dsi->cwocks.dsi))
		wetuwn PTW_EWW(dsi->cwocks.dsi);

	if (!dsi->cwocks.pww && !dsi->cwocks.dsi) {
		dev_eww(dsi->dev, "no input cwock (pww, dsi)\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wcaw_mipi_dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_mipi_dsi *dsi;
	int wet;

	dsi = devm_kzawwoc(&pdev->dev, sizeof(*dsi), GFP_KEWNEW);
	if (dsi == NUWW)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dsi);

	dsi->dev = &pdev->dev;
	dsi->info = of_device_get_match_data(&pdev->dev);

	wet = wcaw_mipi_dsi_pawse_dt(dsi);
	if (wet < 0)
		wetuwn wet;

	/* Acquiwe wesouwces. */
	dsi->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dsi->mmio))
		wetuwn PTW_EWW(dsi->mmio);

	wet = wcaw_mipi_dsi_get_cwocks(dsi);
	if (wet < 0)
		wetuwn wet;

	dsi->wstc = devm_weset_contwow_get(dsi->dev, NUWW);
	if (IS_EWW(dsi->wstc)) {
		dev_eww(dsi->dev, "faiwed to get cpg weset\n");
		wetuwn PTW_EWW(dsi->wstc);
	}

	/* Initiawize the DSI host. */
	dsi->host.dev = dsi->dev;
	dsi->host.ops = &wcaw_mipi_dsi_host_ops;
	wet = mipi_dsi_host_wegistew(&dsi->host);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void wcaw_mipi_dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_mipi_dsi *dsi = pwatfowm_get_dwvdata(pdev);

	mipi_dsi_host_unwegistew(&dsi->host);
}

static const stwuct wcaw_mipi_dsi_device_info v3u_data = {
	.modew = WCAW_DSI_V3U,
	.cwk_cfg = dsi_cwk_cfg_v3u,
	.cwockset2_m_offset = 2,
	.n_min = 3,
	.n_max = 8,
	.n_muw = 1,
	.fpfd_min = MHZ(2),
	.fpfd_max = MHZ(8),
	.m_min = 64,
	.m_max = 625,
	.fout_min = MHZ(320),
	.fout_max = MHZ(1250),
};

static const stwuct wcaw_mipi_dsi_device_info v4h_data = {
	.modew = WCAW_DSI_V4H,
	.cwk_cfg = dsi_cwk_cfg_v4h,
	.cwockset2_m_offset = 0,
	.n_min = 1,
	.n_max = 8,
	.n_muw = 2,
	.fpfd_min = MHZ(8),
	.fpfd_max = MHZ(24),
	.m_min = 167,
	.m_max = 1000,
	.fout_min = MHZ(2000),
	.fout_max = MHZ(4000),
};

static const stwuct of_device_id wcaw_mipi_dsi_of_tabwe[] = {
	{ .compatibwe = "wenesas,w8a779a0-dsi-csi2-tx", .data = &v3u_data },
	{ .compatibwe = "wenesas,w8a779g0-dsi-csi2-tx", .data = &v4h_data },
	{ }
};

MODUWE_DEVICE_TABWE(of, wcaw_mipi_dsi_of_tabwe);

static stwuct pwatfowm_dwivew wcaw_mipi_dsi_pwatfowm_dwivew = {
	.pwobe          = wcaw_mipi_dsi_pwobe,
	.wemove_new     = wcaw_mipi_dsi_wemove,
	.dwivew         = {
		.name   = "wcaw-mipi-dsi",
		.of_match_tabwe = wcaw_mipi_dsi_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wcaw_mipi_dsi_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Wenesas W-Caw MIPI DSI Encodew Dwivew");
MODUWE_WICENSE("GPW");
