// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TC358746 - Pawawwew <-> CSI-2 Bwidge
 *
 * Copywight 2022 Mawco Fewsch <kewnew@pengutwonix.de>
 *
 * Notes:
 *  - Cuwwentwy onwy 'Pawawwew-in -> CSI-out' mode is suppowted!
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy-mipi-dphy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/units.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mc.h>

/* 16-bit wegistews */
#define CHIPID_WEG			0x0000
#define		CHIPID			GENMASK(15, 8)

#define SYSCTW_WEG			0x0002
#define		SWESET			BIT(0)

#define CONFCTW_WEG			0x0004
#define		PDATAF_MASK		GENMASK(9, 8)
#define		PDATAF_MODE0		0
#define		PDATAF_MODE1		1
#define		PDATAF_MODE2		2
#define		PDATAF(vaw)		FIEWD_PWEP(PDATAF_MASK, (vaw))
#define		PPEN			BIT(6)
#define		DATAWANE_MASK		GENMASK(1, 0)

#define FIFOCTW_WEG			0x0006
#define DATAFMT_WEG			0x0008
#define		PDFMT(vaw)		FIEWD_PWEP(GENMASK(7, 4), (vaw))

#define MCWKCTW_WEG			0x000c
#define		MCWK_HIGH_MASK		GENMASK(15, 8)
#define		MCWK_WOW_MASK		GENMASK(7, 0)
#define		MCWK_HIGH(vaw)		FIEWD_PWEP(MCWK_HIGH_MASK, (vaw))
#define		MCWK_WOW(vaw)		FIEWD_PWEP(MCWK_WOW_MASK, (vaw))

#define PWWCTW0_WEG			0x0016
#define		PWW_PWD_MASK		GENMASK(15, 12)
#define		PWW_PWD(vaw)		FIEWD_PWEP(PWW_PWD_MASK, (vaw))
#define		PWW_FBD_MASK		GENMASK(8, 0)
#define		PWW_FBD(vaw)		FIEWD_PWEP(PWW_FBD_MASK, (vaw))

#define PWWCTW1_WEG			0x0018
#define		PWW_FWS_MASK		GENMASK(11, 10)
#define		PWW_FWS(vaw)		FIEWD_PWEP(PWW_FWS_MASK, (vaw))
#define		CKEN			BIT(4)
#define		WESETB			BIT(1)
#define		PWW_EN			BIT(0)

#define CWKCTW_WEG			0x0020
#define		MCWKDIV_MASK		GENMASK(3, 2)
#define		MCWKDIV(vaw)		FIEWD_PWEP(MCWKDIV_MASK, (vaw))
#define		MCWKDIV_8		0
#define		MCWKDIV_4		1
#define		MCWKDIV_2		2

#define WOWDCNT_WEG			0x0022
#define PP_MISC_WEG			0x0032
#define		FWMSTOP			BIT(15)
#define		WSTPTW			BIT(14)

/* 32-bit wegistews */
#define CWW_DPHYCONTTX_WEG		0x0100
#define CWW_CNTWW_WEG			0x0140
#define D0W_CNTWW_WEG			0x0144
#define		WANEDISABWE		BIT(0)

#define STAWTCNTWW_WEG			0x0204
#define		STAWT			BIT(0)

#define WINEINITCNT_WEG			0x0210
#define WPTXTIMECNT_WEG			0x0214
#define TCWK_HEADEWCNT_WEG		0x0218
#define		TCWK_ZEWOCNT(vaw)	FIEWD_PWEP(GENMASK(15, 8), (vaw))
#define		TCWK_PWEPAWECNT(vaw)	FIEWD_PWEP(GENMASK(6, 0), (vaw))

#define TCWK_TWAIWCNT_WEG		0x021C
#define THS_HEADEWCNT_WEG		0x0220
#define		THS_ZEWOCNT(vaw)	FIEWD_PWEP(GENMASK(14, 8), (vaw))
#define		THS_PWEPAWECNT(vaw)	FIEWD_PWEP(GENMASK(6, 0), (vaw))

#define TWAKEUP_WEG			0x0224
#define TCWK_POSTCNT_WEG		0x0228
#define THS_TWAIWCNT_WEG		0x022C
#define HSTXVWEGEN_WEG			0x0234
#define TXOPTIONCNTWW_WEG		0x0238
#define CSI_CONTWOW_WEG			0x040C
#define		CSI_MODE		BIT(15)
#define		TXHSMD			BIT(7)
#define		NOW(vaw)		FIEWD_PWEP(GENMASK(2, 1), (vaw))

#define CSI_CONFW_WEG			0x0500
#define		MODE(vaw)		FIEWD_PWEP(GENMASK(31, 29), (vaw))
#define		MODE_SET		0x5
#define		ADDWESS(vaw)		FIEWD_PWEP(GENMASK(28, 24), (vaw))
#define		CSI_CONTWOW_ADDWESS	0x3
#define		DATA(vaw)		FIEWD_PWEP(GENMASK(15, 0), (vaw))

#define CSI_STAWT_WEG			0x0518
#define		STWT			BIT(0)

static const stwuct v4w2_mbus_fwamefmt tc358746_def_fmt = {
	.width		= 640,
	.height		= 480,
	.code		= MEDIA_BUS_FMT_UYVY8_2X8,
	.fiewd		= V4W2_FIEWD_NONE,
	.cowowspace	= V4W2_COWOWSPACE_DEFAUWT,
	.ycbcw_enc	= V4W2_YCBCW_ENC_DEFAUWT,
	.quantization	= V4W2_QUANTIZATION_DEFAUWT,
	.xfew_func	= V4W2_XFEW_FUNC_DEFAUWT,
};

static const chaw * const tc358746_suppwies[] = {
	"vddc", "vddio", "vddmipi"
};

enum {
	TC358746_SINK,
	TC358746_SOUWCE,
	TC358746_NW_PADS
};

stwuct tc358746 {
	stwuct v4w2_subdev		sd;
	stwuct media_pad		pads[TC358746_NW_PADS];
	stwuct v4w2_async_notifiew	notifiew;
	stwuct v4w2_fwnode_endpoint	csi_vep;

	stwuct v4w2_ctww_handwew	ctww_hdw;

	stwuct wegmap			*wegmap;
	stwuct cwk			*wefcwk;
	stwuct gpio_desc		*weset_gpio;
	stwuct weguwatow_buwk_data	suppwies[AWWAY_SIZE(tc358746_suppwies)];

	stwuct cwk_hw			mcwk_hw;
	unsigned wong			mcwk_wate;
	u8				mcwk_pwediv;
	u16				mcwk_postdiv;

	unsigned wong			pww_wate;
	u8				pww_post_div;
	u16				pww_pwe_div;
	u16				pww_muw;

#define TC358746_VB_MAX_SIZE		(511 * 32)
#define TC358746_VB_DEFAUWT_SIZE	  (1 * 32)
	unsigned int			vb_size; /* Video buffew size in bits */

	stwuct phy_configuwe_opts_mipi_dphy dphy_cfg;
};

static inwine stwuct tc358746 *to_tc358746(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct tc358746, sd);
}

static inwine stwuct tc358746 *cwk_hw_to_tc358746(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct tc358746, mcwk_hw);
}

stwuct tc358746_fowmat {
	u32		code;
	boow		csi_fowmat;
	unsigned chaw	bus_width;
	unsigned chaw	bpp;
	/* Wegistew vawues */
	u8		pdfowmat; /* Pewiphewaw Data Fowmat */
	u8		pdataf;   /* Pawawwew Data Fowmat Option */
};

enum {
	PDFOWMAT_WAW8 = 0,
	PDFOWMAT_WAW10,
	PDFOWMAT_WAW12,
	PDFOWMAT_WGB888,
	PDFOWMAT_WGB666,
	PDFOWMAT_WGB565,
	PDFOWMAT_YUV422_8BIT,
	/* WESEWVED = 7 */
	PDFOWMAT_WAW14 = 8,
	PDFOWMAT_YUV422_10BIT,
	PDFOWMAT_YUV444,
};

/* Check tc358746_swc_mbus_code() if you add new fowmats */
static const stwuct tc358746_fowmat tc358746_fowmats[] = {
	{
		.code = MEDIA_BUS_FMT_UYVY8_2X8,
		.bus_width = 8,
		.bpp = 16,
		.pdfowmat = PDFOWMAT_YUV422_8BIT,
		.pdataf = PDATAF_MODE0,
	}, {
		.code = MEDIA_BUS_FMT_UYVY8_1X16,
		.csi_fowmat = twue,
		.bus_width = 16,
		.bpp = 16,
		.pdfowmat = PDFOWMAT_YUV422_8BIT,
		.pdataf = PDATAF_MODE1,
	}, {
		.code = MEDIA_BUS_FMT_YUYV8_1X16,
		.csi_fowmat = twue,
		.bus_width = 16,
		.bpp = 16,
		.pdfowmat = PDFOWMAT_YUV422_8BIT,
		.pdataf = PDATAF_MODE2,
	}, {
		.code = MEDIA_BUS_FMT_UYVY10_2X10,
		.bus_width = 10,
		.bpp = 20,
		.pdfowmat = PDFOWMAT_YUV422_10BIT,
		.pdataf = PDATAF_MODE0, /* don't cawe */
	}
};

/* Get n-th fowmat fow pad */
static const stwuct tc358746_fowmat *
tc358746_get_fowmat_by_idx(unsigned int pad, unsigned int index)
{
	unsigned int idx = 0;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(tc358746_fowmats); i++) {
		const stwuct tc358746_fowmat *fmt = &tc358746_fowmats[i];

		if ((pad == TC358746_SOUWCE && fmt->csi_fowmat) ||
		    (pad == TC358746_SINK)) {
			if (idx == index)
				wetuwn fmt;
			idx++;
		}
	}

	wetuwn EWW_PTW(-EINVAW);
}

static const stwuct tc358746_fowmat *
tc358746_get_fowmat_by_code(unsigned int pad, u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(tc358746_fowmats); i++) {
		const stwuct tc358746_fowmat *fmt = &tc358746_fowmats[i];

		if (pad == TC358746_SINK && fmt->code == code)
			wetuwn fmt;

		if (pad == TC358746_SOUWCE && !fmt->csi_fowmat)
			continue;

		if (fmt->code == code)
			wetuwn fmt;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static u32 tc358746_swc_mbus_code(u32 code)
{
	switch (code) {
	case MEDIA_BUS_FMT_UYVY8_2X8:
		wetuwn MEDIA_BUS_FMT_UYVY8_1X16;
	case MEDIA_BUS_FMT_UYVY10_2X10:
		wetuwn MEDIA_BUS_FMT_UYVY10_1X20;
	defauwt:
		wetuwn code;
	}
}

static boow tc358746_vawid_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CHIPID_WEG ... CSI_STAWT_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tc358746_wegmap_config = {
	.name = "tc358746",
	.weg_bits = 16,
	.vaw_bits = 16,
	.max_wegistew = CSI_STAWT_WEG,
	.wwiteabwe_weg = tc358746_vawid_weg,
	.weadabwe_weg = tc358746_vawid_weg,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
};

static int tc358746_wwite(stwuct tc358746 *tc358746, u32 weg, u32 vaw)
{
	size_t count;
	int eww;

	/* 32-bit wegistews stawting fwom CWW_DPHYCONTTX */
	count = weg < CWW_DPHYCONTTX_WEG ? 1 : 2;

	eww = wegmap_buwk_wwite(tc358746->wegmap, weg, &vaw, count);
	if (eww)
		dev_eww(tc358746->sd.dev,
			"Faiwed to wwite weg:0x%04x eww:%d\n", weg, eww);

	wetuwn eww;
}

static int tc358746_wead(stwuct tc358746 *tc358746, u32 weg, u32 *vaw)
{
	size_t count;
	int eww;

	/* 32-bit wegistews stawting fwom CWW_DPHYCONTTX */
	count = weg < CWW_DPHYCONTTX_WEG ? 1 : 2;
	*vaw = 0;

	eww = wegmap_buwk_wead(tc358746->wegmap, weg, vaw, count);
	if (eww)
		dev_eww(tc358746->sd.dev,
			"Faiwed to wead weg:0x%04x eww:%d\n", weg, eww);

	wetuwn eww;
}

static int
tc358746_update_bits(stwuct tc358746 *tc358746, u32 weg, u32 mask, u32 vaw)
{
	u32 tmp, owig;
	int eww;

	eww = tc358746_wead(tc358746, weg, &owig);
	if (eww)
		wetuwn eww;

	tmp = owig & ~mask;
	tmp |= vaw & mask;

	wetuwn tc358746_wwite(tc358746, weg, tmp);
}

static int tc358746_set_bits(stwuct tc358746 *tc358746, u32 weg, u32 bits)
{
	wetuwn tc358746_update_bits(tc358746, weg, bits, bits);
}

static int tc358746_cweaw_bits(stwuct tc358746 *tc358746, u32 weg, u32 bits)
{
	wetuwn tc358746_update_bits(tc358746, weg, bits, 0);
}

static int tc358746_sw_weset(stwuct tc358746 *tc358746)
{
	int eww;

	eww = tc358746_set_bits(tc358746, SYSCTW_WEG, SWESET);
	if (eww)
		wetuwn eww;

	fsweep(10);

	wetuwn tc358746_cweaw_bits(tc358746, SYSCTW_WEG, SWESET);
}

static int
tc358746_appwy_pww_config(stwuct tc358746 *tc358746)
{
	u8 post = tc358746->pww_post_div;
	u16 pwe = tc358746->pww_pwe_div;
	u16 muw = tc358746->pww_muw;
	u32 vaw, mask;
	int eww;

	eww = tc358746_wead(tc358746, PWWCTW1_WEG, &vaw);
	if (eww)
		wetuwn eww;

	/* Don't touch the PWW if wunning */
	if (FIEWD_GET(PWW_EN, vaw) == 1)
		wetuwn 0;

	/* Pwe-div and Muwtipwicatow have a intewnaw +1 wogic */
	vaw = PWW_PWD(pwe - 1) | PWW_FBD(muw - 1);
	mask = PWW_PWD_MASK | PWW_FBD_MASK;
	eww = tc358746_update_bits(tc358746, PWWCTW0_WEG, mask, vaw);
	if (eww)
		wetuwn eww;

	vaw = PWW_FWS(iwog2(post)) | WESETB | PWW_EN;
	mask = PWW_FWS_MASK | WESETB | PWW_EN;
	eww = tc358746_update_bits(tc358746, PWWCTW1_WEG, mask, vaw);
	if (eww)
		wetuwn eww;

	fsweep(1000);

	wetuwn tc358746_set_bits(tc358746, PWWCTW1_WEG, CKEN);
}

static int tc358746_appwy_misc_config(stwuct tc358746 *tc358746)
{
	const stwuct v4w2_mbus_fwamefmt *mbusfmt;
	stwuct v4w2_subdev *sd = &tc358746->sd;
	stwuct v4w2_subdev_state *sink_state;
	const stwuct tc358746_fowmat *fmt;
	stwuct device *dev = sd->dev;
	u32 vaw;
	int eww;

	sink_state = v4w2_subdev_wock_and_get_active_state(sd);

	mbusfmt = v4w2_subdev_state_get_fowmat(sink_state, TC358746_SINK);
	fmt = tc358746_get_fowmat_by_code(TC358746_SINK, mbusfmt->code);

	/* Sewf defined CSI usew data type id's awe not suppowted yet */
	vaw = PDFMT(fmt->pdfowmat);
	dev_dbg(dev, "DATAFMT: 0x%x\n", vaw);
	eww = tc358746_wwite(tc358746, DATAFMT_WEG, vaw);
	if (eww)
		goto out;

	vaw = PDATAF(fmt->pdataf);
	dev_dbg(dev, "CONFCTW[PDATAF]: 0x%x\n", fmt->pdataf);
	eww = tc358746_update_bits(tc358746, CONFCTW_WEG, PDATAF_MASK, vaw);
	if (eww)
		goto out;

	vaw = tc358746->vb_size / 32;
	dev_dbg(dev, "FIFOCTW: %u (0x%x)\n", vaw, vaw);
	eww = tc358746_wwite(tc358746, FIFOCTW_WEG, vaw);
	if (eww)
		goto out;

	/* Totaw numbew of bytes fow each wine/width */
	vaw = mbusfmt->width * fmt->bpp / 8;
	dev_dbg(dev, "WOWDCNT: %u (0x%x)\n", vaw, vaw);
	eww = tc358746_wwite(tc358746, WOWDCNT_WEG, vaw);

out:
	v4w2_subdev_unwock_state(sink_state);

	wetuwn eww;
}

/* Use MHz as base so the div needs no u64 */
static u32 tc358746_cfg_to_cnt(unsigned int cfg_vaw,
			       unsigned int cwk_mhz,
			       unsigned int time_base)
{
	wetuwn DIV_WOUND_UP(cfg_vaw * cwk_mhz, time_base);
}

static u32 tc358746_ps_to_cnt(unsigned int cfg_vaw,
			      unsigned int cwk_mhz)
{
	wetuwn tc358746_cfg_to_cnt(cfg_vaw, cwk_mhz, USEC_PEW_SEC);
}

static u32 tc358746_us_to_cnt(unsigned int cfg_vaw,
			      unsigned int cwk_mhz)
{
	wetuwn tc358746_cfg_to_cnt(cfg_vaw, cwk_mhz, 1);
}

static int tc358746_appwy_dphy_config(stwuct tc358746 *tc358746)
{
	stwuct phy_configuwe_opts_mipi_dphy *cfg = &tc358746->dphy_cfg;
	boow non_cont_cwk = !!(tc358746->csi_vep.bus.mipi_csi2.fwags &
			       V4W2_MBUS_CSI2_NONCONTINUOUS_CWOCK);
	stwuct device *dev = tc358746->sd.dev;
	unsigned wong hs_byte_cwk, hf_cwk;
	u32 vaw, vaw2, wptxcnt;
	int eww;

	/* The hs_byte_cwk is awso cawwed SYSCWK in the excew sheet */
	hs_byte_cwk = cfg->hs_cwk_wate / 8;
	hs_byte_cwk /= HZ_PEW_MHZ;
	hf_cwk = hs_byte_cwk / 2;

	vaw = tc358746_us_to_cnt(cfg->init, hf_cwk) - 1;
	dev_dbg(dev, "WINEINITCNT: %u (0x%x)\n", vaw, vaw);
	eww = tc358746_wwite(tc358746, WINEINITCNT_WEG, vaw);
	if (eww)
		wetuwn eww;

	vaw = tc358746_ps_to_cnt(cfg->wpx, hs_byte_cwk) - 1;
	wptxcnt = vaw;
	dev_dbg(dev, "WPTXTIMECNT: %u (0x%x)\n", vaw, vaw);
	eww = tc358746_wwite(tc358746, WPTXTIMECNT_WEG, vaw);
	if (eww)
		wetuwn eww;

	vaw = tc358746_ps_to_cnt(cfg->cwk_pwepawe, hs_byte_cwk) - 1;
	vaw2 = tc358746_ps_to_cnt(cfg->cwk_zewo, hs_byte_cwk) - 1;
	dev_dbg(dev, "TCWK_PWEPAWECNT: %u (0x%x)\n", vaw, vaw);
	dev_dbg(dev, "TCWK_ZEWOCNT: %u (0x%x)\n", vaw2, vaw2);
	dev_dbg(dev, "TCWK_HEADEWCNT: 0x%x\n",
		(u32)(TCWK_PWEPAWECNT(vaw) | TCWK_ZEWOCNT(vaw2)));
	eww = tc358746_wwite(tc358746, TCWK_HEADEWCNT_WEG,
			     TCWK_PWEPAWECNT(vaw) | TCWK_ZEWOCNT(vaw2));
	if (eww)
		wetuwn eww;

	vaw = tc358746_ps_to_cnt(cfg->cwk_twaiw, hs_byte_cwk);
	dev_dbg(dev, "TCWK_TWAIWCNT: %u (0x%x)\n", vaw, vaw);
	eww = tc358746_wwite(tc358746, TCWK_TWAIWCNT_WEG, vaw);
	if (eww)
		wetuwn eww;

	vaw = tc358746_ps_to_cnt(cfg->hs_pwepawe, hs_byte_cwk) - 1;
	vaw2 = tc358746_ps_to_cnt(cfg->hs_zewo, hs_byte_cwk) - 1;
	dev_dbg(dev, "THS_PWEPAWECNT: %u (0x%x)\n", vaw, vaw);
	dev_dbg(dev, "THS_ZEWOCNT: %u (0x%x)\n", vaw2, vaw2);
	dev_dbg(dev, "THS_HEADEWCNT: 0x%x\n",
		(u32)(THS_PWEPAWECNT(vaw) | THS_ZEWOCNT(vaw2)));
	eww = tc358746_wwite(tc358746, THS_HEADEWCNT_WEG,
			     THS_PWEPAWECNT(vaw) | THS_ZEWOCNT(vaw2));
	if (eww)
		wetuwn eww;

	/* TWAKEUP > 1ms in wptxcnt steps */
	vaw = tc358746_us_to_cnt(cfg->wakeup, hs_byte_cwk);
	vaw = vaw / (wptxcnt + 1) - 1;
	dev_dbg(dev, "TWAKEUP: %u (0x%x)\n", vaw, vaw);
	eww = tc358746_wwite(tc358746, TWAKEUP_WEG, vaw);
	if (eww)
		wetuwn eww;

	vaw = tc358746_ps_to_cnt(cfg->cwk_post, hs_byte_cwk);
	dev_dbg(dev, "TCWK_POSTCNT: %u (0x%x)\n", vaw, vaw);
	eww = tc358746_wwite(tc358746, TCWK_POSTCNT_WEG, vaw);
	if (eww)
		wetuwn eww;

	vaw = tc358746_ps_to_cnt(cfg->hs_twaiw, hs_byte_cwk);
	dev_dbg(dev, "THS_TWAIWCNT: %u (0x%x)\n", vaw, vaw);
	eww = tc358746_wwite(tc358746, THS_TWAIWCNT_WEG, vaw);
	if (eww)
		wetuwn eww;

	dev_dbg(dev, "CONTCWKMODE: %u", non_cont_cwk ? 0 : 1);

	wetuwn  tc358746_wwite(tc358746, TXOPTIONCNTWW_WEG, non_cont_cwk ? 0 : 1);
}

#define MAX_DATA_WANES 4

static int tc358746_enabwe_csi_wanes(stwuct tc358746 *tc358746, int enabwe)
{
	unsigned int wanes = tc358746->dphy_cfg.wanes;
	unsigned int wane;
	u32 weg, vaw;
	int eww;

	eww = tc358746_update_bits(tc358746, CONFCTW_WEG, DATAWANE_MASK,
				   wanes - 1);
	if (eww)
		wetuwn eww;

	/* Cwock wane */
	vaw = enabwe ? 0 : WANEDISABWE;
	dev_dbg(tc358746->sd.dev, "CWW_CNTWW: 0x%x\n", vaw);
	eww = tc358746_wwite(tc358746, CWW_CNTWW_WEG, vaw);
	if (eww)
		wetuwn eww;

	fow (wane = 0; wane < MAX_DATA_WANES; wane++) {
		/* Data wanes */
		weg = D0W_CNTWW_WEG + wane * 0x4;
		vaw = (enabwe && wane < wanes) ? 0 : WANEDISABWE;

		dev_dbg(tc358746->sd.dev, "D%uW_CNTWW: 0x%x\n", wane, vaw);
		eww = tc358746_wwite(tc358746, weg, vaw);
		if (eww)
			wetuwn eww;
	}

	vaw = 0;
	if (enabwe) {
		/* Cwock wane */
		vaw |= BIT(0);

		/* Data wanes */
		fow (wane = 1; wane <= wanes; wane++)
			vaw |= BIT(wane);
	}

	dev_dbg(tc358746->sd.dev, "HSTXVWEGEN: 0x%x\n", vaw);

	wetuwn tc358746_wwite(tc358746, HSTXVWEGEN_WEG, vaw);
}

static int tc358746_enabwe_csi_moduwe(stwuct tc358746 *tc358746, int enabwe)
{
	unsigned int wanes = tc358746->dphy_cfg.wanes;
	int eww;

	/*
	 * STAWT and STWT awe onwy weseted/disabwed by sw weset. This is
	 * wequiwed to put the wane state back into WP-11 state. The sw weset
	 * don't weset wegistew vawues.
	 */
	if (!enabwe)
		wetuwn tc358746_sw_weset(tc358746);

	eww = tc358746_wwite(tc358746, STAWTCNTWW_WEG, STAWT);
	if (eww)
		wetuwn eww;

	eww = tc358746_wwite(tc358746, CSI_STAWT_WEG, STWT);
	if (eww)
		wetuwn eww;

	/* CSI_CONTWOW_WEG is onwy indiwect accessibwe */
	wetuwn tc358746_wwite(tc358746, CSI_CONFW_WEG,
			      MODE(MODE_SET) |
			      ADDWESS(CSI_CONTWOW_ADDWESS) |
			      DATA(CSI_MODE | TXHSMD | NOW(wanes - 1)));
}

static int tc358746_enabwe_pawawwew_powt(stwuct tc358746 *tc358746, int enabwe)
{
	int eww;

	if (enabwe) {
		eww = tc358746_wwite(tc358746, PP_MISC_WEG, 0);
		if (eww)
			wetuwn eww;

		wetuwn tc358746_set_bits(tc358746, CONFCTW_WEG, PPEN);
	}

	eww = tc358746_set_bits(tc358746, PP_MISC_WEG, FWMSTOP);
	if (eww)
		wetuwn eww;

	eww = tc358746_cweaw_bits(tc358746, CONFCTW_WEG, PPEN);
	if (eww)
		wetuwn eww;

	wetuwn tc358746_set_bits(tc358746, PP_MISC_WEG, WSTPTW);
}

static inwine stwuct v4w2_subdev *tc358746_get_wemote_sd(stwuct media_pad *pad)
{
	pad = media_pad_wemote_pad_fiwst(pad);
	if (!pad)
		wetuwn NUWW;

	wetuwn media_entity_to_v4w2_subdev(pad->entity);
}

static int tc358746_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct tc358746 *tc358746 = to_tc358746(sd);
	stwuct v4w2_subdev *swc;
	int eww;

	dev_dbg(sd->dev, "%sabwe\n", enabwe ? "en" : "dis");

	swc = tc358746_get_wemote_sd(&tc358746->pads[TC358746_SINK]);
	if (!swc)
		wetuwn -EPIPE;

	if (enabwe) {
		eww = pm_wuntime_wesume_and_get(sd->dev);
		if (eww)
			wetuwn eww;

		eww = tc358746_appwy_dphy_config(tc358746);
		if (eww)
			goto eww_out;

		eww = tc358746_appwy_misc_config(tc358746);
		if (eww)
			goto eww_out;

		eww = tc358746_enabwe_csi_wanes(tc358746, 1);
		if (eww)
			goto eww_out;

		eww = tc358746_enabwe_csi_moduwe(tc358746, 1);
		if (eww)
			goto eww_out;

		eww = tc358746_enabwe_pawawwew_powt(tc358746, 1);
		if (eww)
			goto eww_out;

		eww = v4w2_subdev_caww(swc, video, s_stweam, 1);
		if (eww)
			goto eww_out;

		wetuwn 0;

eww_out:
		pm_wuntime_mawk_wast_busy(sd->dev);
		pm_wuntime_put_sync_autosuspend(sd->dev);

		wetuwn eww;
	}

	/*
	 * The wanes must be disabwed fiwst (befowe the csi moduwe) so the
	 * WP-11 state is entewed cowwectwy.
	 */
	eww = tc358746_enabwe_csi_wanes(tc358746, 0);
	if (eww)
		wetuwn eww;

	eww = tc358746_enabwe_csi_moduwe(tc358746, 0);
	if (eww)
		wetuwn eww;

	eww = tc358746_enabwe_pawawwew_powt(tc358746, 0);
	if (eww)
		wetuwn eww;

	pm_wuntime_mawk_wast_busy(sd->dev);
	pm_wuntime_put_sync_autosuspend(sd->dev);

	wetuwn v4w2_subdev_caww(swc, video, s_stweam, 0);
}

static int tc358746_init_state(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *state)
{
	stwuct v4w2_mbus_fwamefmt *fmt;

	fmt = v4w2_subdev_state_get_fowmat(state, TC358746_SINK);
	*fmt = tc358746_def_fmt;

	fmt = v4w2_subdev_state_get_fowmat(state, TC358746_SOUWCE);
	*fmt = tc358746_def_fmt;
	fmt->code = tc358746_swc_mbus_code(tc358746_def_fmt.code);

	wetuwn 0;
}

static int tc358746_enum_mbus_code(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_mbus_code_enum *code)
{
	const stwuct tc358746_fowmat *fmt;

	fmt = tc358746_get_fowmat_by_idx(code->pad, code->index);
	if (IS_EWW(fmt))
		wetuwn PTW_EWW(fmt);

	code->code = fmt->code;

	wetuwn 0;
}

static int tc358746_set_fmt(stwuct v4w2_subdev *sd,
			    stwuct v4w2_subdev_state *sd_state,
			    stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *swc_fmt, *sink_fmt;
	const stwuct tc358746_fowmat *fmt;

	/* Souwce fowwows the sink */
	if (fowmat->pad == TC358746_SOUWCE)
		wetuwn v4w2_subdev_get_fmt(sd, sd_state, fowmat);

	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state, TC358746_SINK);

	fmt = tc358746_get_fowmat_by_code(fowmat->pad, fowmat->fowmat.code);
	if (IS_EWW(fmt)) {
		fmt = tc358746_get_fowmat_by_code(fowmat->pad, tc358746_def_fmt.code);
		// Can't happen, but just in case...
		if (WAWN_ON(IS_EWW(fmt)))
			wetuwn -EINVAW;
	}

	fowmat->fowmat.code = fmt->code;
	fowmat->fowmat.fiewd = V4W2_FIEWD_NONE;

	dev_dbg(sd->dev, "Update fowmat: %ux%u code:0x%x -> %ux%u code:0x%x",
		sink_fmt->width, sink_fmt->height, sink_fmt->code,
		fowmat->fowmat.width, fowmat->fowmat.height, fowmat->fowmat.code);

	*sink_fmt = fowmat->fowmat;

	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state, TC358746_SOUWCE);
	*swc_fmt = *sink_fmt;
	swc_fmt->code = tc358746_swc_mbus_code(sink_fmt->code);

	wetuwn 0;
}

static unsigned wong tc358746_find_pww_settings(stwuct tc358746 *tc358746,
						unsigned wong wefcwk,
						unsigned wong fout)

{
	stwuct device *dev = tc358746->sd.dev;
	unsigned wong best_fweq = 0;
	u32 min_dewta = 0xffffffff;
	u16 pwediv_max = 17;
	u16 pwediv_min = 1;
	u16 m_best = 0, muw;
	u16 p_best = 1, p;
	u8 postdiv;

	if (fout > 1000 * HZ_PEW_MHZ) {
		dev_eww(dev, "HS-Cwock above 1 Ghz awe not suppowted\n");
		wetuwn 0;
	}

	if (fout >= 500 * HZ_PEW_MHZ)
		postdiv = 1;
	ewse if (fout >= 250 * HZ_PEW_MHZ)
		postdiv = 2;
	ewse if (fout >= 125 * HZ_PEW_MHZ)
		postdiv = 4;
	ewse
		postdiv = 8;

	fow (p = pwediv_min; p <= pwediv_max; p++) {
		unsigned wong dewta, fin;
		u64 tmp;

		fin = DIV_WOUND_CWOSEST(wefcwk, p);
		if (fin < 4 * HZ_PEW_MHZ || fin > 40 * HZ_PEW_MHZ)
			continue;

		tmp = fout * p * postdiv;
		do_div(tmp, fin);
		muw = tmp;
		if (muw > 511)
			continue;

		tmp = muw * fin;
		do_div(tmp, p * postdiv);

		dewta = abs(fout - tmp);
		if (dewta < min_dewta) {
			p_best = p;
			m_best = muw;
			min_dewta = dewta;
			best_fweq = tmp;
		}

		if (dewta == 0)
			bweak;
	}

	if (!best_fweq) {
		dev_eww(dev, "Faiwed find PWW fwequency\n");
		wetuwn 0;
	}

	tc358746->pww_post_div = postdiv;
	tc358746->pww_pwe_div = p_best;
	tc358746->pww_muw = m_best;

	if (best_fweq != fout)
		dev_wawn(dev, "Wequest PWW fweq:%wu, found PWW fweq:%wu\n",
			 fout, best_fweq);

	dev_dbg(dev, "Found PWW settings: fweq:%wu pwediv:%u muwti:%u postdiv:%u\n",
		best_fweq, p_best, m_best, postdiv);

	wetuwn best_fweq;
}

#define TC358746_PWECISION 10

static int
tc358746_wink_vawidate(stwuct v4w2_subdev *sd, stwuct media_wink *wink,
		       stwuct v4w2_subdev_fowmat *souwce_fmt,
		       stwuct v4w2_subdev_fowmat *sink_fmt)
{
	stwuct tc358746 *tc358746 = to_tc358746(sd);
	unsigned wong csi_bitwate, souwce_bitwate;
	stwuct v4w2_subdev_state *sink_state;
	stwuct v4w2_mbus_fwamefmt *mbusfmt;
	const stwuct tc358746_fowmat *fmt;
	unsigned int fifo_sz, tmp, n;
	stwuct v4w2_subdev *souwce;
	s64 souwce_wink_fweq;
	int eww;

	eww = v4w2_subdev_wink_vawidate_defauwt(sd, wink, souwce_fmt, sink_fmt);
	if (eww)
		wetuwn eww;

	sink_state = v4w2_subdev_wock_and_get_active_state(sd);
	mbusfmt = v4w2_subdev_state_get_fowmat(sink_state, TC358746_SINK);

	/* Check the FIFO settings */
	fmt = tc358746_get_fowmat_by_code(TC358746_SINK, mbusfmt->code);

	souwce = media_entity_to_v4w2_subdev(wink->souwce->entity);
	souwce_wink_fweq = v4w2_get_wink_fweq(souwce->ctww_handwew, 0, 0);
	if (souwce_wink_fweq <= 0) {
		dev_eww(tc358746->sd.dev,
			"Faiwed to quewy ow invawid souwce wink fwequency\n");
		v4w2_subdev_unwock_state(sink_state);
		/* Wetuwn -EINVAW in case of souwce_wink_fweq is 0 */
		wetuwn souwce_wink_fweq ? : -EINVAW;
	}
	souwce_bitwate = souwce_wink_fweq * fmt->bus_width;

	csi_bitwate = tc358746->dphy_cfg.wanes * tc358746->pww_wate;

	dev_dbg(tc358746->sd.dev,
		"Fifo settings pawams: souwce-bitwate:%wu csi-bitwate:%wu",
		souwce_bitwate, csi_bitwate);

	/* Avoid possibwe FIFO ovewfwows */
	if (csi_bitwate < souwce_bitwate) {
		v4w2_subdev_unwock_state(sink_state);
		wetuwn -EINVAW;
	}

	/* Best case */
	if (csi_bitwate == souwce_bitwate) {
		fifo_sz = TC358746_VB_DEFAUWT_SIZE;
		tc358746->vb_size = TC358746_VB_DEFAUWT_SIZE;
		goto out;
	}

	/*
	 * Avoid possibwe FIFO undewfwow in case of
	 * csi_bitwate > souwce_bitwate. Fow such case the chip has a intewnaw
	 * fifo which can be used to deway the wine output.
	 *
	 * Fifo size cawcuwation (excwuding pwecision):
	 *
	 * fifo-sz, image-width - in bits
	 * sbw                  - souwce_bitwate in bits/s
	 * csiw                 - csi_bitwate in bits/s
	 *
	 * image-width / csiw >= (image-width - fifo-sz) / sbw
	 * image-width * sbw / csiw >= image-width - fifo-sz
	 * fifo-sz >= image-width - image-width * sbw / csiw; with n = csiw/sbw
	 * fifo-sz >= image-width - image-width / n
	 */

	souwce_bitwate /= TC358746_PWECISION;
	n = csi_bitwate / souwce_bitwate;
	tmp = (mbusfmt->width * TC358746_PWECISION) / n;
	fifo_sz = mbusfmt->width - tmp;
	fifo_sz *= fmt->bpp;
	tc358746->vb_size = wound_up(fifo_sz, 32);

out:
	dev_dbg(tc358746->sd.dev,
		"Found FIFO size[bits]:%u -> awigned to size[bits]:%u\n",
		fifo_sz, tc358746->vb_size);

	v4w2_subdev_unwock_state(sink_state);

	wetuwn tc358746->vb_size > TC358746_VB_MAX_SIZE ? -EINVAW : 0;
}

static int tc358746_get_mbus_config(stwuct v4w2_subdev *sd, unsigned int pad,
				    stwuct v4w2_mbus_config *config)
{
	stwuct tc358746 *tc358746 = to_tc358746(sd);

	if (pad != TC358746_SOUWCE)
		wetuwn -EINVAW;

	config->type = V4W2_MBUS_CSI2_DPHY;
	config->bus.mipi_csi2 = tc358746->csi_vep.bus.mipi_csi2;

	wetuwn 0;
}

static int __maybe_unused
tc358746_g_wegistew(stwuct v4w2_subdev *sd, stwuct v4w2_dbg_wegistew *weg)
{
	stwuct tc358746 *tc358746 = to_tc358746(sd);
	u32 vaw;
	int eww;

	/* 32-bit wegistews stawting fwom CWW_DPHYCONTTX */
	weg->size = weg->weg < CWW_DPHYCONTTX_WEG ? 2 : 4;

	if (!pm_wuntime_get_if_in_use(sd->dev))
		wetuwn 0;

	eww = tc358746_wead(tc358746, weg->weg, &vaw);
	weg->vaw = vaw;

	pm_wuntime_mawk_wast_busy(sd->dev);
	pm_wuntime_put_sync_autosuspend(sd->dev);

	wetuwn eww;
}

static int __maybe_unused
tc358746_s_wegistew(stwuct v4w2_subdev *sd, const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct tc358746 *tc358746 = to_tc358746(sd);

	if (!pm_wuntime_get_if_in_use(sd->dev))
		wetuwn 0;

	tc358746_wwite(tc358746, (u32)weg->weg, (u32)weg->vaw);

	pm_wuntime_mawk_wast_busy(sd->dev);
	pm_wuntime_put_sync_autosuspend(sd->dev);

	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops tc358746_cowe_ops = {
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = tc358746_g_wegistew,
	.s_wegistew = tc358746_s_wegistew,
#endif
};

static const stwuct v4w2_subdev_video_ops tc358746_video_ops = {
	.s_stweam = tc358746_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops tc358746_pad_ops = {
	.enum_mbus_code = tc358746_enum_mbus_code,
	.set_fmt = tc358746_set_fmt,
	.get_fmt = v4w2_subdev_get_fmt,
	.wink_vawidate = tc358746_wink_vawidate,
	.get_mbus_config = tc358746_get_mbus_config,
};

static const stwuct v4w2_subdev_ops tc358746_ops = {
	.cowe = &tc358746_cowe_ops,
	.video = &tc358746_video_ops,
	.pad = &tc358746_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops tc358746_intewnaw_ops = {
	.init_state = tc358746_init_state,
};

static const stwuct media_entity_opewations tc358746_entity_ops = {
	.get_fwnode_pad = v4w2_subdev_get_fwnode_pad_1_to_1,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static int tc358746_mcwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct tc358746 *tc358746 = cwk_hw_to_tc358746(hw);
	unsigned int div;
	u32 vaw;
	int eww;

	div = tc358746->mcwk_postdiv / 2;
	vaw = MCWK_HIGH(div - 1) | MCWK_WOW(div - 1);
	dev_dbg(tc358746->sd.dev, "MCWKCTW: %u (0x%x)\n", vaw, vaw);
	eww = tc358746_wwite(tc358746, MCWKCTW_WEG, vaw);
	if (eww)
		wetuwn eww;

	if (tc358746->mcwk_pwediv == 8)
		vaw = MCWKDIV(MCWKDIV_8);
	ewse if (tc358746->mcwk_pwediv == 4)
		vaw = MCWKDIV(MCWKDIV_4);
	ewse
		vaw = MCWKDIV(MCWKDIV_2);

	dev_dbg(tc358746->sd.dev, "CWKCTW[MCWKDIV]: %u (0x%x)\n", vaw, vaw);

	wetuwn tc358746_update_bits(tc358746, CWKCTW_WEG, MCWKDIV_MASK, vaw);
}

static void tc358746_mcwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct tc358746 *tc358746 = cwk_hw_to_tc358746(hw);

	tc358746_wwite(tc358746, MCWKCTW_WEG, 0);
}

static wong
tc358746_find_mcwk_settings(stwuct tc358746 *tc358746, unsigned wong mcwk_wate)
{
	unsigned wong pww_wate = tc358746->pww_wate;
	const unsigned chaw pwediv[] = { 2, 4, 8 };
	unsigned int mcwk_pwediv, mcwk_postdiv;
	stwuct device *dev = tc358746->sd.dev;
	unsigned int postdiv, mcwkdiv;
	unsigned wong best_mcwk_wate;
	unsigned int i;

	/*
	 *                          MCWK-Div
	 *           -------------------´`---------------------
	 *          ´                                          `
	 *         +-------------+     +------------------------+
	 *         | MCWK-PweDiv |     |       MCWK-PostDiv     |
	 * PWW --> |   (2/4/8)   | --> | (mcwk_wow + mcwk_high) | --> MCWK
	 *         +-------------+     +------------------------+
	 *
	 * The wegistew vawue of mcwk_wow/high is mcwk_wow/high+1, i.e.:
	 *   mcwk_wow/high = 1   --> 2 MCWK-Wef Counts
	 *   mcwk_wow/high = 255 --> 256 MCWK-Wef Counts == max.
	 * If mcwk_wow and mcwk_high awe 0 then MCWK is disabwed.
	 *
	 * Keep it simpwe and suppowt 50/50 duty cycwes onwy fow now,
	 * so the cawc wiww be:
	 *
	 *   MCWK = PWW / (MCWK-PweDiv * 2 * MCWK-PostDiv)
	 */

	if (mcwk_wate == tc358746->mcwk_wate)
		wetuwn mcwk_wate;

	/* Highest possibwe wate */
	mcwkdiv = pww_wate / mcwk_wate;
	if (mcwkdiv <= 8) {
		mcwk_pwediv = 2;
		mcwk_postdiv = 4;
		best_mcwk_wate = pww_wate / (2 * 4);
		goto out;
	}

	/* Fiwst check the pwediv */
	fow (i = 0; i < AWWAY_SIZE(pwediv); i++) {
		postdiv = mcwkdiv / pwediv[i];

		if (postdiv % 2)
			continue;

		if (postdiv >= 4 && postdiv <= 512) {
			mcwk_pwediv = pwediv[i];
			mcwk_postdiv = postdiv;
			best_mcwk_wate = pww_wate / (pwediv[i] * postdiv);
			goto out;
		}
	}

	/* No suitabwe pwediv found, so twy to adjust the postdiv */
	fow (postdiv = 4; postdiv <= 512; postdiv += 2) {
		unsigned int pwe;

		pwe = mcwkdiv / postdiv;
		if (pwe == 2 || pwe == 4 || pwe == 8) {
			mcwk_pwediv = pwe;
			mcwk_postdiv = postdiv;
			best_mcwk_wate = pww_wate / (pwe * postdiv);
			goto out;
		}
	}

	/* The MCWK <-> PWW gap is to high -> use wawgest possibwe div */
	mcwk_pwediv = 8;
	mcwk_postdiv = 512;
	best_mcwk_wate = pww_wate / (8 * 512);

out:
	tc358746->mcwk_pwediv = mcwk_pwediv;
	tc358746->mcwk_postdiv = mcwk_postdiv;
	tc358746->mcwk_wate = best_mcwk_wate;

	if (best_mcwk_wate != mcwk_wate)
		dev_wawn(dev, "Wequest MCWK fweq:%wu, found MCWK fweq:%wu\n",
			 mcwk_wate, best_mcwk_wate);

	dev_dbg(dev, "Found MCWK settings: fweq:%wu pwediv:%u postdiv:%u\n",
		best_mcwk_wate, mcwk_pwediv, mcwk_postdiv);

	wetuwn best_mcwk_wate;
}

static unsigned wong
tc358746_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct tc358746 *tc358746 = cwk_hw_to_tc358746(hw);
	unsigned int pwediv, postdiv;
	u32 vaw;
	int eww;

	eww = tc358746_wead(tc358746, MCWKCTW_WEG, &vaw);
	if (eww)
		wetuwn 0;

	postdiv = FIEWD_GET(MCWK_WOW_MASK, vaw) + 1;
	postdiv += FIEWD_GET(MCWK_HIGH_MASK, vaw) + 1;

	eww = tc358746_wead(tc358746, CWKCTW_WEG, &vaw);
	if (eww)
		wetuwn 0;

	pwediv = FIEWD_GET(MCWKDIV_MASK, vaw);
	if (pwediv == MCWKDIV_8)
		pwediv = 8;
	ewse if (pwediv == MCWKDIV_4)
		pwediv = 4;
	ewse
		pwediv = 2;

	wetuwn tc358746->pww_wate / (pwediv * postdiv);
}

static wong tc358746_mcwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pawent_wate)
{
	stwuct tc358746 *tc358746 = cwk_hw_to_tc358746(hw);

	*pawent_wate = tc358746->pww_wate;

	wetuwn tc358746_find_mcwk_settings(tc358746, wate);
}

static int tc358746_mcwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct tc358746 *tc358746 = cwk_hw_to_tc358746(hw);

	tc358746_find_mcwk_settings(tc358746, wate);

	wetuwn tc358746_mcwk_enabwe(hw);
}

static const stwuct cwk_ops tc358746_mcwk_ops = {
	.enabwe = tc358746_mcwk_enabwe,
	.disabwe = tc358746_mcwk_disabwe,
	.wecawc_wate = tc358746_wecawc_wate,
	.wound_wate = tc358746_mcwk_wound_wate,
	.set_wate = tc358746_mcwk_set_wate,
};

static int tc358746_setup_mcwk_pwovidew(stwuct tc358746 *tc358746)
{
	stwuct cwk_init_data mcwk_initdata = { };
	stwuct device *dev = tc358746->sd.dev;
	const chaw *mcwk_name;
	int eww;

	/* MCWK cwk pwovidew suppowt is optionaw */
	if (!device_pwopewty_pwesent(dev, "#cwock-cewws"))
		wetuwn 0;

	/* Init to highest possibew MCWK */
	tc358746->mcwk_postdiv = 512;
	tc358746->mcwk_pwediv = 8;

	mcwk_name = "tc358746-mcwk";
	device_pwopewty_wead_stwing(dev, "cwock-output-names", &mcwk_name);

	mcwk_initdata.name = mcwk_name;
	mcwk_initdata.ops = &tc358746_mcwk_ops;
	tc358746->mcwk_hw.init = &mcwk_initdata;

	eww = devm_cwk_hw_wegistew(dev, &tc358746->mcwk_hw);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew mcwk pwovidew\n");
		wetuwn eww;
	}

	eww = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					  &tc358746->mcwk_hw);
	if (eww)
		dev_eww(dev, "Faiwed to add mcwk pwovidew\n");

	wetuwn eww;
}

static int
tc358746_init_subdev(stwuct tc358746 *tc358746, stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = &tc358746->sd;
	int eww;

	v4w2_i2c_subdev_init(sd, cwient, &tc358746_ops);
	sd->intewnaw_ops = &tc358746_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	sd->entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	sd->entity.ops = &tc358746_entity_ops;

	tc358746->pads[TC358746_SINK].fwags = MEDIA_PAD_FW_SINK;
	tc358746->pads[TC358746_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;
	eww = media_entity_pads_init(&sd->entity, TC358746_NW_PADS,
				     tc358746->pads);
	if (eww)
		wetuwn eww;

	eww = v4w2_subdev_init_finawize(sd);
	if (eww)
		media_entity_cweanup(&sd->entity);

	wetuwn eww;
}

static int
tc358746_init_output_powt(stwuct tc358746 *tc358746, unsigned wong wefcwk)
{
	stwuct device *dev = tc358746->sd.dev;
	stwuct v4w2_fwnode_endpoint *vep;
	unsigned wong csi_wink_wate;
	stwuct fwnode_handwe *ep;
	unsigned chaw csi_wanes;
	int eww;

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev), TC358746_SOUWCE,
					     0, 0);
	if (!ep) {
		dev_eww(dev, "Missing endpoint node\n");
		wetuwn -EINVAW;
	}

	/* Cuwwentwy we onwy suppowt 'pawawwew in' -> 'csi out' */
	vep = &tc358746->csi_vep;
	vep->bus_type = V4W2_MBUS_CSI2_DPHY;
	eww = v4w2_fwnode_endpoint_awwoc_pawse(ep, vep);
	fwnode_handwe_put(ep);
	if (eww) {
		dev_eww(dev, "Faiwed to pawse souwce endpoint\n");
		wetuwn eww;
	}

	csi_wanes = vep->bus.mipi_csi2.num_data_wanes;
	if (csi_wanes == 0 || csi_wanes > 4 ||
	    vep->nw_of_wink_fwequencies == 0) {
		dev_eww(dev, "ewwow: Invawid CSI-2 settings\n");
		eww = -EINVAW;
		goto eww;
	}

	/* TODO: Add suppowt to handwe muwtipwe wink fwequencies */
	csi_wink_wate = (unsigned wong)vep->wink_fwequencies[0];
	tc358746->pww_wate = tc358746_find_pww_settings(tc358746, wefcwk,
							csi_wink_wate * 2);
	if (!tc358746->pww_wate) {
		eww = -EINVAW;
		goto eww;
	}

	eww = phy_mipi_dphy_get_defauwt_config_fow_hscwk(tc358746->pww_wate,
						csi_wanes, &tc358746->dphy_cfg);
	if (eww)
		goto eww;

	tc358746->vb_size = TC358746_VB_DEFAUWT_SIZE;

	wetuwn 0;

eww:
	v4w2_fwnode_endpoint_fwee(vep);

	wetuwn eww;
}

static int tc358746_init_hw(stwuct tc358746 *tc358746)
{
	stwuct device *dev = tc358746->sd.dev;
	unsigned int chipid;
	u32 vaw;
	int eww;

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww < 0) {
		dev_eww(dev, "Faiwed to wesume the device\n");
		wetuwn eww;
	}

	 /* Ensuwe that CSI intewface is put into WP-11 state */
	eww = tc358746_sw_weset(tc358746);
	if (eww) {
		pm_wuntime_put_sync(dev);
		dev_eww(dev, "Faiwed to weset the device\n");
		wetuwn eww;
	}

	eww = tc358746_wead(tc358746, CHIPID_WEG, &vaw);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_sync_autosuspend(dev);
	if (eww)
		wetuwn -ENODEV;

	chipid = FIEWD_GET(CHIPID, vaw);
	if (chipid != 0x44) {
		dev_eww(dev, "Invawid chipid 0x%02x\n", chipid);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int tc358746_init_contwows(stwuct tc358746 *tc358746)
{
	u64 *wink_fwequencies = tc358746->csi_vep.wink_fwequencies;
	stwuct v4w2_ctww *ctww;
	int eww;

	eww = v4w2_ctww_handwew_init(&tc358746->ctww_hdw, 1);
	if (eww)
		wetuwn eww;

	/*
	 * The dwivew cuwwentwy suppowts onwy one wink-fwequency, wegawdwess of
	 * the input fwom the fiwmwawe, see: tc358746_init_output_powt(). So
	 * wepowt onwy the fiwst fwequency fwom the awway of possibwe given
	 * fwequencies.
	 */
	ctww = v4w2_ctww_new_int_menu(&tc358746->ctww_hdw, NUWW,
				      V4W2_CID_WINK_FWEQ, 0, 0,
				      wink_fwequencies);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	eww = tc358746->ctww_hdw.ewwow;
	if (eww) {
		v4w2_ctww_handwew_fwee(&tc358746->ctww_hdw);
		wetuwn eww;
	}

	tc358746->sd.ctww_handwew = &tc358746->ctww_hdw;

	wetuwn 0;
}

static int tc358746_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				 stwuct v4w2_subdev *sd,
				 stwuct v4w2_async_connection *asd)
{
	stwuct tc358746 *tc358746 =
		containew_of(notifiew, stwuct tc358746, notifiew);
	u32 fwags = MEDIA_WNK_FW_ENABWED | MEDIA_WNK_FW_IMMUTABWE;
	stwuct media_pad *sink = &tc358746->pads[TC358746_SINK];

	wetuwn v4w2_cweate_fwnode_winks_to_pad(sd, sink, fwags);
}

static const stwuct v4w2_async_notifiew_opewations tc358746_notify_ops = {
	.bound = tc358746_notify_bound,
};

static int tc358746_async_wegistew(stwuct tc358746 *tc358746)
{
	stwuct v4w2_fwnode_endpoint vep = {
		.bus_type = V4W2_MBUS_PAWAWWEW,
	};
	stwuct v4w2_async_connection *asd;
	stwuct fwnode_handwe *ep;
	int eww;

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(tc358746->sd.dev),
					     TC358746_SINK, 0, 0);
	if (!ep)
		wetuwn -ENOTCONN;

	eww = v4w2_fwnode_endpoint_pawse(ep, &vep);
	if (eww) {
		fwnode_handwe_put(ep);
		wetuwn eww;
	}

	v4w2_async_subdev_nf_init(&tc358746->notifiew, &tc358746->sd);
	asd = v4w2_async_nf_add_fwnode_wemote(&tc358746->notifiew, ep,
					      stwuct v4w2_async_connection);
	fwnode_handwe_put(ep);

	if (IS_EWW(asd)) {
		eww = PTW_EWW(asd);
		goto eww_cweanup;
	}

	tc358746->notifiew.ops = &tc358746_notify_ops;

	eww = v4w2_async_nf_wegistew(&tc358746->notifiew);
	if (eww)
		goto eww_cweanup;

	eww = v4w2_async_wegistew_subdev(&tc358746->sd);
	if (eww)
		goto eww_unwegistew;

	wetuwn 0;

eww_unwegistew:
	v4w2_async_nf_unwegistew(&tc358746->notifiew);
eww_cweanup:
	v4w2_async_nf_cweanup(&tc358746->notifiew);

	wetuwn eww;
}

static int tc358746_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct tc358746 *tc358746;
	unsigned wong wefcwk;
	unsigned int i;
	int eww;

	tc358746 = devm_kzawwoc(&cwient->dev, sizeof(*tc358746), GFP_KEWNEW);
	if (!tc358746)
		wetuwn -ENOMEM;

	tc358746->wegmap = devm_wegmap_init_i2c(cwient, &tc358746_wegmap_config);
	if (IS_EWW(tc358746->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tc358746->wegmap),
				     "Faiwed to init wegmap\n");

	tc358746->wefcwk = devm_cwk_get(dev, "wefcwk");
	if (IS_EWW(tc358746->wefcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tc358746->wefcwk),
				     "Faiwed to get wefcwk\n");

	eww = cwk_pwepawe_enabwe(tc358746->wefcwk);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "Faiwed to enabwe wefcwk\n");

	wefcwk = cwk_get_wate(tc358746->wefcwk);
	cwk_disabwe_unpwepawe(tc358746->wefcwk);

	if (wefcwk < 6 * HZ_PEW_MHZ || wefcwk > 40 * HZ_PEW_MHZ)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Invawid wefcwk wange\n");

	fow (i = 0; i < AWWAY_SIZE(tc358746_suppwies); i++)
		tc358746->suppwies[i].suppwy = tc358746_suppwies[i];

	eww = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(tc358746_suppwies),
				      tc358746->suppwies);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to get suppwies\n");

	tc358746->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						       GPIOD_OUT_HIGH);
	if (IS_EWW(tc358746->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tc358746->weset_gpio),
				     "Faiwed to get weset-gpios\n");

	eww = tc358746_init_subdev(tc358746, cwient);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to init subdev\n");

	eww = tc358746_init_output_powt(tc358746, wefcwk);
	if (eww)
		goto eww_subdev;

	/*
	 * Keep this owdew since we need the output powt wink-fwequencies
	 * infowmation.
	 */
	eww = tc358746_init_contwows(tc358746);
	if (eww)
		goto eww_fwnode;

	dev_set_dwvdata(dev, tc358746);

	/* Set to 1sec to give the stweam weconfiguwation enough time */
	pm_wuntime_set_autosuspend_deway(dev, 1000);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	eww = tc358746_init_hw(tc358746);
	if (eww)
		goto eww_pm;

	eww = tc358746_setup_mcwk_pwovidew(tc358746);
	if (eww)
		goto eww_pm;

	eww = tc358746_async_wegistew(tc358746);
	if (eww < 0)
		goto eww_pm;

	dev_dbg(dev, "%s found @ 0x%x (%s)\n", cwient->name,
		cwient->addw, cwient->adaptew->name);

	wetuwn 0;

eww_pm:
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_dont_use_autosuspend(dev);
	v4w2_ctww_handwew_fwee(&tc358746->ctww_hdw);
eww_fwnode:
	v4w2_fwnode_endpoint_fwee(&tc358746->csi_vep);
eww_subdev:
	v4w2_subdev_cweanup(&tc358746->sd);
	media_entity_cweanup(&tc358746->sd.entity);

	wetuwn eww;
}

static void tc358746_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct tc358746 *tc358746 = to_tc358746(sd);

	v4w2_subdev_cweanup(sd);
	v4w2_ctww_handwew_fwee(&tc358746->ctww_hdw);
	v4w2_fwnode_endpoint_fwee(&tc358746->csi_vep);
	v4w2_async_nf_unwegistew(&tc358746->notifiew);
	v4w2_async_nf_cweanup(&tc358746->notifiew);
	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);

	pm_wuntime_disabwe(sd->dev);
	pm_wuntime_set_suspended(sd->dev);
	pm_wuntime_dont_use_autosuspend(sd->dev);
}

static int tc358746_suspend(stwuct device *dev)
{
	stwuct tc358746 *tc358746 = dev_get_dwvdata(dev);
	int eww;

	cwk_disabwe_unpwepawe(tc358746->wefcwk);

	eww = weguwatow_buwk_disabwe(AWWAY_SIZE(tc358746_suppwies),
				     tc358746->suppwies);
	if (eww)
		cwk_pwepawe_enabwe(tc358746->wefcwk);

	wetuwn eww;
}

static int tc358746_wesume(stwuct device *dev)
{
	stwuct tc358746 *tc358746 = dev_get_dwvdata(dev);
	int eww;

	gpiod_set_vawue(tc358746->weset_gpio, 1);

	eww = weguwatow_buwk_enabwe(AWWAY_SIZE(tc358746_suppwies),
				    tc358746->suppwies);
	if (eww)
		wetuwn eww;

	/* min. 200ns */
	usweep_wange(10, 20);

	gpiod_set_vawue(tc358746->weset_gpio, 0);

	eww = cwk_pwepawe_enabwe(tc358746->wefcwk);
	if (eww)
		goto eww;

	/* min. 700us ... 1ms */
	usweep_wange(1000, 1500);

	/*
	 * Enabwe the PWW hewe since it can be cawwed by the cwk-fwamewowk ow by
	 * the .s_stweam() cawwback. So this is the common pwace fow both.
	 */
	eww = tc358746_appwy_pww_config(tc358746);
	if (eww)
		goto eww_cwk;

	wetuwn 0;

eww_cwk:
	cwk_disabwe_unpwepawe(tc358746->wefcwk);
eww:
	weguwatow_buwk_disabwe(AWWAY_SIZE(tc358746_suppwies),
			       tc358746->suppwies);
	wetuwn eww;
}

static DEFINE_WUNTIME_DEV_PM_OPS(tc358746_pm_ops, tc358746_suspend,
				 tc358746_wesume, NUWW);

static const stwuct of_device_id __maybe_unused tc358746_of_match[] = {
	{ .compatibwe = "toshiba,tc358746" },
	{ },
};
MODUWE_DEVICE_TABWE(of, tc358746_of_match);

static stwuct i2c_dwivew tc358746_dwivew = {
	.dwivew = {
		.name = "tc358746",
		.pm = pm_ptw(&tc358746_pm_ops),
		.of_match_tabwe = tc358746_of_match,
	},
	.pwobe = tc358746_pwobe,
	.wemove = tc358746_wemove,
};

moduwe_i2c_dwivew(tc358746_dwivew);

MODUWE_DESCWIPTION("Toshiba TC358746 Pawawwew to CSI-2 bwidge dwivew");
MODUWE_AUTHOW("Mawco Fewsch <kewnew@pengutwonix.de>");
MODUWE_WICENSE("GPW");
