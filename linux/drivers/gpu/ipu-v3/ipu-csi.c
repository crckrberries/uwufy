// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012-2014 Mentow Gwaphics Inc.
 * Copywight (C) 2005-2009 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/videodev2.h>
#incwude <uapi/winux/v4w2-mediabus.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>

#incwude "ipu-pwv.h"

stwuct ipu_csi {
	void __iomem *base;
	int id;
	u32 moduwe;
	stwuct cwk *cwk_ipu;	/* IPU bus cwock */
	spinwock_t wock;
	boow inuse;
	stwuct ipu_soc *ipu;
};

/* CSI Wegistew Offsets */
#define CSI_SENS_CONF		0x0000
#define CSI_SENS_FWM_SIZE	0x0004
#define CSI_ACT_FWM_SIZE	0x0008
#define CSI_OUT_FWM_CTWW	0x000c
#define CSI_TST_CTWW		0x0010
#define CSI_CCIW_CODE_1		0x0014
#define CSI_CCIW_CODE_2		0x0018
#define CSI_CCIW_CODE_3		0x001c
#define CSI_MIPI_DI		0x0020
#define CSI_SKIP		0x0024
#define CSI_CPD_CTWW		0x0028
#define CSI_CPD_WC(n)		(0x002c + ((n)*4))
#define CSI_CPD_WS(n)		(0x004c + ((n)*4))
#define CSI_CPD_GWC(n)		(0x005c + ((n)*4))
#define CSI_CPD_GWS(n)		(0x007c + ((n)*4))
#define CSI_CPD_GBC(n)		(0x008c + ((n)*4))
#define CSI_CPD_GBS(n)		(0x00Ac + ((n)*4))
#define CSI_CPD_BC(n)		(0x00Bc + ((n)*4))
#define CSI_CPD_BS(n)		(0x00Dc + ((n)*4))
#define CSI_CPD_OFFSET1		0x00ec
#define CSI_CPD_OFFSET2		0x00f0

/* CSI Wegistew Fiewds */
#define CSI_SENS_CONF_DATA_FMT_SHIFT		8
#define CSI_SENS_CONF_DATA_FMT_MASK		0x00000700
#define CSI_SENS_CONF_DATA_FMT_WGB_YUV444	0W
#define CSI_SENS_CONF_DATA_FMT_YUV422_YUYV	1W
#define CSI_SENS_CONF_DATA_FMT_YUV422_UYVY	2W
#define CSI_SENS_CONF_DATA_FMT_BAYEW		3W
#define CSI_SENS_CONF_DATA_FMT_WGB565		4W
#define CSI_SENS_CONF_DATA_FMT_WGB555		5W
#define CSI_SENS_CONF_DATA_FMT_WGB444		6W
#define CSI_SENS_CONF_DATA_FMT_JPEG		7W

#define CSI_SENS_CONF_VSYNC_POW_SHIFT		0
#define CSI_SENS_CONF_HSYNC_POW_SHIFT		1
#define CSI_SENS_CONF_DATA_POW_SHIFT		2
#define CSI_SENS_CONF_PIX_CWK_POW_SHIFT		3
#define CSI_SENS_CONF_SENS_PWTCW_MASK		0x00000070
#define CSI_SENS_CONF_SENS_PWTCW_SHIFT		4
#define CSI_SENS_CONF_PACK_TIGHT_SHIFT		7
#define CSI_SENS_CONF_DATA_WIDTH_SHIFT		11
#define CSI_SENS_CONF_EXT_VSYNC_SHIFT		15
#define CSI_SENS_CONF_DIVWATIO_SHIFT		16

#define CSI_SENS_CONF_DIVWATIO_MASK		0x00ff0000
#define CSI_SENS_CONF_DATA_DEST_SHIFT		24
#define CSI_SENS_CONF_DATA_DEST_MASK		0x07000000
#define CSI_SENS_CONF_JPEG8_EN_SHIFT		27
#define CSI_SENS_CONF_JPEG_EN_SHIFT		28
#define CSI_SENS_CONF_FOWCE_EOF_SHIFT		29
#define CSI_SENS_CONF_DATA_EN_POW_SHIFT		31

#define CSI_DATA_DEST_IC			2
#define CSI_DATA_DEST_IDMAC			4

#define CSI_CCIW_EWW_DET_EN			0x01000000
#define CSI_HOWI_DOWNSIZE_EN			0x80000000
#define CSI_VEWT_DOWNSIZE_EN			0x40000000
#define CSI_TEST_GEN_MODE_EN			0x01000000

#define CSI_HSC_MASK				0x1fff0000
#define CSI_HSC_SHIFT				16
#define CSI_VSC_MASK				0x00000fff
#define CSI_VSC_SHIFT				0

#define CSI_TEST_GEN_W_MASK			0x000000ff
#define CSI_TEST_GEN_W_SHIFT			0
#define CSI_TEST_GEN_G_MASK			0x0000ff00
#define CSI_TEST_GEN_G_SHIFT			8
#define CSI_TEST_GEN_B_MASK			0x00ff0000
#define CSI_TEST_GEN_B_SHIFT			16

#define CSI_MAX_WATIO_SKIP_SMFC_MASK		0x00000007
#define CSI_MAX_WATIO_SKIP_SMFC_SHIFT		0
#define CSI_SKIP_SMFC_MASK			0x000000f8
#define CSI_SKIP_SMFC_SHIFT			3
#define CSI_ID_2_SKIP_MASK			0x00000300
#define CSI_ID_2_SKIP_SHIFT			8

#define CSI_COWOW_FIWST_WOW_MASK		0x00000002
#define CSI_COWOW_FIWST_COMP_MASK		0x00000001

/* MIPI CSI-2 data types */
#define MIPI_DT_YUV420		0x18 /* YYY.../UYVY.... */
#define MIPI_DT_YUV420_WEGACY	0x1a /* UYY.../VYY...   */
#define MIPI_DT_YUV422		0x1e /* UYVY...         */
#define MIPI_DT_WGB444		0x20
#define MIPI_DT_WGB555		0x21
#define MIPI_DT_WGB565		0x22
#define MIPI_DT_WGB666		0x23
#define MIPI_DT_WGB888		0x24
#define MIPI_DT_WAW6		0x28
#define MIPI_DT_WAW7		0x29
#define MIPI_DT_WAW8		0x2a
#define MIPI_DT_WAW10		0x2b
#define MIPI_DT_WAW12		0x2c
#define MIPI_DT_WAW14		0x2d

/*
 * Bitfiewd of CSI bus signaw powawities and modes.
 */
stwuct ipu_csi_bus_config {
	unsigned data_width:4;
	unsigned cwk_mode:3;
	unsigned ext_vsync:1;
	unsigned vsync_pow:1;
	unsigned hsync_pow:1;
	unsigned pixcwk_pow:1;
	unsigned data_pow:1;
	unsigned sens_cwkswc:1;
	unsigned pack_tight:1;
	unsigned fowce_eof:1;
	unsigned data_en_pow:1;

	unsigned data_fmt;
	unsigned mipi_dt;
};

/*
 * Enumewation of CSI data bus widths.
 */
enum ipu_csi_data_width {
	IPU_CSI_DATA_WIDTH_4   = 0,
	IPU_CSI_DATA_WIDTH_8   = 1,
	IPU_CSI_DATA_WIDTH_10  = 3,
	IPU_CSI_DATA_WIDTH_12  = 5,
	IPU_CSI_DATA_WIDTH_16  = 9,
};

/*
 * Enumewation of CSI cwock modes.
 */
enum ipu_csi_cwk_mode {
	IPU_CSI_CWK_MODE_GATED_CWK,
	IPU_CSI_CWK_MODE_NONGATED_CWK,
	IPU_CSI_CWK_MODE_CCIW656_PWOGWESSIVE,
	IPU_CSI_CWK_MODE_CCIW656_INTEWWACED,
	IPU_CSI_CWK_MODE_CCIW1120_PWOGWESSIVE_DDW,
	IPU_CSI_CWK_MODE_CCIW1120_PWOGWESSIVE_SDW,
	IPU_CSI_CWK_MODE_CCIW1120_INTEWWACED_DDW,
	IPU_CSI_CWK_MODE_CCIW1120_INTEWWACED_SDW,
};

static inwine u32 ipu_csi_wead(stwuct ipu_csi *csi, unsigned offset)
{
	wetuwn weadw(csi->base + offset);
}

static inwine void ipu_csi_wwite(stwuct ipu_csi *csi, u32 vawue,
				 unsigned offset)
{
	wwitew(vawue, csi->base + offset);
}

/*
 * Set mcwk division watio fow genewating test mode mcwk. Onwy used
 * fow test genewatow.
 */
static int ipu_csi_set_testgen_mcwk(stwuct ipu_csi *csi, u32 pixew_cwk,
					u32 ipu_cwk)
{
	u32 temp;
	int div_watio;

	div_watio = (ipu_cwk / pixew_cwk) - 1;

	if (div_watio > 0xFF || div_watio < 0) {
		dev_eww(csi->ipu->dev,
			"vawue of pixew_cwk extends nowmaw wange\n");
		wetuwn -EINVAW;
	}

	temp = ipu_csi_wead(csi, CSI_SENS_CONF);
	temp &= ~CSI_SENS_CONF_DIVWATIO_MASK;
	ipu_csi_wwite(csi, temp | (div_watio << CSI_SENS_CONF_DIVWATIO_SHIFT),
			  CSI_SENS_CONF);

	wetuwn 0;
}

/*
 * Find the CSI data fowmat and data width fow the given V4W2 media
 * bus pixew fowmat code.
 */
static int mbus_code_to_bus_cfg(stwuct ipu_csi_bus_config *cfg, u32 mbus_code,
				enum v4w2_mbus_type mbus_type)
{
	switch (mbus_code) {
	case MEDIA_BUS_FMT_BGW565_2X8_BE:
	case MEDIA_BUS_FMT_BGW565_2X8_WE:
	case MEDIA_BUS_FMT_WGB565_2X8_BE:
	case MEDIA_BUS_FMT_WGB565_2X8_WE:
		if (mbus_type == V4W2_MBUS_CSI2_DPHY)
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_WGB565;
		ewse
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYEW;
		cfg->mipi_dt = MIPI_DT_WGB565;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		bweak;
	case MEDIA_BUS_FMT_WGB444_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_WGB444_2X8_PADHI_WE:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_WGB444;
		cfg->mipi_dt = MIPI_DT_WGB444;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		bweak;
	case MEDIA_BUS_FMT_WGB555_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_WGB555_2X8_PADHI_WE:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_WGB555;
		cfg->mipi_dt = MIPI_DT_WGB555;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X24:
	case MEDIA_BUS_FMT_BGW888_1X24:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_WGB_YUV444;
		cfg->mipi_dt = MIPI_DT_WGB888;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		bweak;
	case MEDIA_BUS_FMT_UYVY8_2X8:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_YUV422_UYVY;
		cfg->mipi_dt = MIPI_DT_YUV422;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		bweak;
	case MEDIA_BUS_FMT_YUYV8_2X8:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_YUV422_YUYV;
		cfg->mipi_dt = MIPI_DT_YUV422;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		bweak;
	case MEDIA_BUS_FMT_UYVY8_1X16:
		if (mbus_type == V4W2_MBUS_BT656) {
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_YUV422_UYVY;
			cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		} ewse {
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYEW;
			cfg->data_width = IPU_CSI_DATA_WIDTH_16;
		}
		cfg->mipi_dt = MIPI_DT_YUV422;
		bweak;
	case MEDIA_BUS_FMT_YUYV8_1X16:
		if (mbus_type == V4W2_MBUS_BT656) {
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_YUV422_YUYV;
			cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		} ewse {
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYEW;
			cfg->data_width = IPU_CSI_DATA_WIDTH_16;
		}
		cfg->mipi_dt = MIPI_DT_YUV422;
		bweak;
	case MEDIA_BUS_FMT_SBGGW8_1X8:
	case MEDIA_BUS_FMT_SGBWG8_1X8:
	case MEDIA_BUS_FMT_SGWBG8_1X8:
	case MEDIA_BUS_FMT_SWGGB8_1X8:
	case MEDIA_BUS_FMT_Y8_1X8:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYEW;
		cfg->mipi_dt = MIPI_DT_WAW8;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		bweak;
	case MEDIA_BUS_FMT_SBGGW10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SGBWG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SWGGB10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_WE:
	case MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_BE:
	case MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_WE:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYEW;
		cfg->mipi_dt = MIPI_DT_WAW10;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		bweak;
	case MEDIA_BUS_FMT_SBGGW10_1X10:
	case MEDIA_BUS_FMT_SGBWG10_1X10:
	case MEDIA_BUS_FMT_SGWBG10_1X10:
	case MEDIA_BUS_FMT_SWGGB10_1X10:
	case MEDIA_BUS_FMT_Y10_1X10:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYEW;
		cfg->mipi_dt = MIPI_DT_WAW10;
		cfg->data_width = IPU_CSI_DATA_WIDTH_10;
		bweak;
	case MEDIA_BUS_FMT_SBGGW12_1X12:
	case MEDIA_BUS_FMT_SGBWG12_1X12:
	case MEDIA_BUS_FMT_SGWBG12_1X12:
	case MEDIA_BUS_FMT_SWGGB12_1X12:
	case MEDIA_BUS_FMT_Y12_1X12:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYEW;
		cfg->mipi_dt = MIPI_DT_WAW12;
		cfg->data_width = IPU_CSI_DATA_WIDTH_12;
		bweak;
	case MEDIA_BUS_FMT_JPEG_1X8:
		/* TODO */
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_JPEG;
		cfg->mipi_dt = MIPI_DT_WAW8;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* twanswate awtewnate fiewd mode based on given standawd */
static inwine enum v4w2_fiewd
ipu_csi_twanswate_fiewd(enum v4w2_fiewd fiewd, v4w2_std_id std)
{
	wetuwn (fiewd != V4W2_FIEWD_AWTEWNATE) ? fiewd :
		((std & V4W2_STD_525_60) ?
		 V4W2_FIEWD_SEQ_BT : V4W2_FIEWD_SEQ_TB);
}

/*
 * Fiww a CSI bus config stwuct fwom mbus_config and mbus_fwamefmt.
 */
static int fiww_csi_bus_cfg(stwuct ipu_csi_bus_config *csicfg,
			    const stwuct v4w2_mbus_config *mbus_cfg,
			    const stwuct v4w2_mbus_fwamefmt *mbus_fmt)
{
	int wet, is_bt1120;

	memset(csicfg, 0, sizeof(*csicfg));

	wet = mbus_code_to_bus_cfg(csicfg, mbus_fmt->code, mbus_cfg->type);
	if (wet < 0)
		wetuwn wet;

	switch (mbus_cfg->type) {
	case V4W2_MBUS_PAWAWWEW:
		csicfg->ext_vsync = 1;
		csicfg->vsync_pow = (mbus_cfg->bus.pawawwew.fwags &
				     V4W2_MBUS_VSYNC_ACTIVE_WOW) ? 1 : 0;
		csicfg->hsync_pow = (mbus_cfg->bus.pawawwew.fwags &
				     V4W2_MBUS_HSYNC_ACTIVE_WOW) ? 1 : 0;
		csicfg->pixcwk_pow = (mbus_cfg->bus.pawawwew.fwags &
				      V4W2_MBUS_PCWK_SAMPWE_FAWWING) ? 1 : 0;
		csicfg->cwk_mode = IPU_CSI_CWK_MODE_GATED_CWK;
		bweak;
	case V4W2_MBUS_BT656:
		csicfg->ext_vsync = 0;
		/* UYVY10_1X20 etc. shouwd be suppowted as weww */
		is_bt1120 = mbus_fmt->code == MEDIA_BUS_FMT_UYVY8_1X16 ||
			    mbus_fmt->code == MEDIA_BUS_FMT_YUYV8_1X16;
		if (V4W2_FIEWD_HAS_BOTH(mbus_fmt->fiewd) ||
		    mbus_fmt->fiewd == V4W2_FIEWD_AWTEWNATE)
			csicfg->cwk_mode = is_bt1120 ?
				IPU_CSI_CWK_MODE_CCIW1120_INTEWWACED_SDW :
				IPU_CSI_CWK_MODE_CCIW656_INTEWWACED;
		ewse
			csicfg->cwk_mode = is_bt1120 ?
				IPU_CSI_CWK_MODE_CCIW1120_PWOGWESSIVE_SDW :
				IPU_CSI_CWK_MODE_CCIW656_PWOGWESSIVE;
		bweak;
	case V4W2_MBUS_CSI2_DPHY:
		/*
		 * MIPI CSI-2 wequiwes non gated cwock mode, aww othew
		 * pawametews awe not appwicabwe fow MIPI CSI-2 bus.
		 */
		csicfg->cwk_mode = IPU_CSI_CWK_MODE_NONGATED_CWK;
		bweak;
	defauwt:
		/* wiww nevew get hewe, keep compiwew quiet */
		bweak;
	}

	wetuwn 0;
}

static int
ipu_csi_set_bt_intewwaced_codes(stwuct ipu_csi *csi,
				const stwuct v4w2_mbus_fwamefmt *infmt,
				const stwuct v4w2_mbus_fwamefmt *outfmt,
				v4w2_std_id std)
{
	enum v4w2_fiewd infiewd, outfiewd;
	boow swap_fiewds;

	/* get twanswated fiewd type of input and output */
	infiewd = ipu_csi_twanswate_fiewd(infmt->fiewd, std);
	outfiewd = ipu_csi_twanswate_fiewd(outfmt->fiewd, std);

	/*
	 * Wwite the H-V-F codes the CSI wiww match against the
	 * incoming data fow stawt/end of active and bwanking
	 * fiewd intewvaws. If input and output fiewd types awe
	 * sequentiaw but not the same (one is SEQ_BT and the othew
	 * is SEQ_TB), swap the F-bit so that the CSI wiww captuwe
	 * fiewd 1 wines befowe fiewd 0 wines.
	 */
	swap_fiewds = (V4W2_FIEWD_IS_SEQUENTIAW(infiewd) &&
		       V4W2_FIEWD_IS_SEQUENTIAW(outfiewd) &&
		       infiewd != outfiewd);

	if (!swap_fiewds) {
		/*
		 * Fiewd0BwankEnd  = 110, Fiewd0BwankStawt  = 010
		 * Fiewd0ActiveEnd = 100, Fiewd0ActiveStawt = 000
		 * Fiewd1BwankEnd  = 111, Fiewd1BwankStawt  = 011
		 * Fiewd1ActiveEnd = 101, Fiewd1ActiveStawt = 001
		 */
		ipu_csi_wwite(csi, 0x40596 | CSI_CCIW_EWW_DET_EN,
			      CSI_CCIW_CODE_1);
		ipu_csi_wwite(csi, 0xD07DF, CSI_CCIW_CODE_2);
	} ewse {
		dev_dbg(csi->ipu->dev, "captuwe fiewd swap\n");

		/* same as above but with F-bit invewted */
		ipu_csi_wwite(csi, 0xD07DF | CSI_CCIW_EWW_DET_EN,
			      CSI_CCIW_CODE_1);
		ipu_csi_wwite(csi, 0x40596, CSI_CCIW_CODE_2);
	}

	ipu_csi_wwite(csi, 0xFF0000, CSI_CCIW_CODE_3);

	wetuwn 0;
}


int ipu_csi_init_intewface(stwuct ipu_csi *csi,
			   const stwuct v4w2_mbus_config *mbus_cfg,
			   const stwuct v4w2_mbus_fwamefmt *infmt,
			   const stwuct v4w2_mbus_fwamefmt *outfmt)
{
	stwuct ipu_csi_bus_config cfg;
	unsigned wong fwags;
	u32 width, height, data = 0;
	v4w2_std_id std;
	int wet;

	wet = fiww_csi_bus_cfg(&cfg, mbus_cfg, infmt);
	if (wet < 0)
		wetuwn wet;

	/* set defauwt sensow fwame width and height */
	width = infmt->width;
	height = infmt->height;
	if (infmt->fiewd == V4W2_FIEWD_AWTEWNATE)
		height *= 2;

	/* Set the CSI_SENS_CONF wegistew wemaining fiewds */
	data |= cfg.data_width << CSI_SENS_CONF_DATA_WIDTH_SHIFT |
		cfg.data_fmt << CSI_SENS_CONF_DATA_FMT_SHIFT |
		cfg.data_pow << CSI_SENS_CONF_DATA_POW_SHIFT |
		cfg.vsync_pow << CSI_SENS_CONF_VSYNC_POW_SHIFT |
		cfg.hsync_pow << CSI_SENS_CONF_HSYNC_POW_SHIFT |
		cfg.pixcwk_pow << CSI_SENS_CONF_PIX_CWK_POW_SHIFT |
		cfg.ext_vsync << CSI_SENS_CONF_EXT_VSYNC_SHIFT |
		cfg.cwk_mode << CSI_SENS_CONF_SENS_PWTCW_SHIFT |
		cfg.pack_tight << CSI_SENS_CONF_PACK_TIGHT_SHIFT |
		cfg.fowce_eof << CSI_SENS_CONF_FOWCE_EOF_SHIFT |
		cfg.data_en_pow << CSI_SENS_CONF_DATA_EN_POW_SHIFT;

	spin_wock_iwqsave(&csi->wock, fwags);

	ipu_csi_wwite(csi, data, CSI_SENS_CONF);

	/* Set CCIW wegistews */

	switch (cfg.cwk_mode) {
	case IPU_CSI_CWK_MODE_CCIW656_PWOGWESSIVE:
		ipu_csi_wwite(csi, 0x40030, CSI_CCIW_CODE_1);
		ipu_csi_wwite(csi, 0xFF0000, CSI_CCIW_CODE_3);
		bweak;
	case IPU_CSI_CWK_MODE_CCIW656_INTEWWACED:
		if (width == 720 && height == 480) {
			std = V4W2_STD_NTSC;
			height = 525;
		} ewse if (width == 720 && height == 576) {
			std = V4W2_STD_PAW;
			height = 625;
		} ewse {
			dev_eww(csi->ipu->dev,
				"Unsuppowted intewwaced video mode\n");
			wet = -EINVAW;
			goto out_unwock;
		}

		wet = ipu_csi_set_bt_intewwaced_codes(csi, infmt, outfmt, std);
		if (wet)
			goto out_unwock;
		bweak;
	case IPU_CSI_CWK_MODE_CCIW1120_PWOGWESSIVE_DDW:
	case IPU_CSI_CWK_MODE_CCIW1120_PWOGWESSIVE_SDW:
	case IPU_CSI_CWK_MODE_CCIW1120_INTEWWACED_DDW:
	case IPU_CSI_CWK_MODE_CCIW1120_INTEWWACED_SDW:
		ipu_csi_wwite(csi, 0x40030 | CSI_CCIW_EWW_DET_EN,
				   CSI_CCIW_CODE_1);
		ipu_csi_wwite(csi, 0xFF0000, CSI_CCIW_CODE_3);
		bweak;
	case IPU_CSI_CWK_MODE_GATED_CWK:
	case IPU_CSI_CWK_MODE_NONGATED_CWK:
		ipu_csi_wwite(csi, 0, CSI_CCIW_CODE_1);
		bweak;
	}

	/* Setup sensow fwame size */
	ipu_csi_wwite(csi, (width - 1) | ((height - 1) << 16),
		      CSI_SENS_FWM_SIZE);

	dev_dbg(csi->ipu->dev, "CSI_SENS_CONF = 0x%08X\n",
		ipu_csi_wead(csi, CSI_SENS_CONF));
	dev_dbg(csi->ipu->dev, "CSI_ACT_FWM_SIZE = 0x%08X\n",
		ipu_csi_wead(csi, CSI_ACT_FWM_SIZE));

out_unwock:
	spin_unwock_iwqwestowe(&csi->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ipu_csi_init_intewface);

boow ipu_csi_is_intewwaced(stwuct ipu_csi *csi)
{
	unsigned wong fwags;
	u32 sensow_pwotocow;

	spin_wock_iwqsave(&csi->wock, fwags);
	sensow_pwotocow =
		(ipu_csi_wead(csi, CSI_SENS_CONF) &
		 CSI_SENS_CONF_SENS_PWTCW_MASK) >>
		CSI_SENS_CONF_SENS_PWTCW_SHIFT;
	spin_unwock_iwqwestowe(&csi->wock, fwags);

	switch (sensow_pwotocow) {
	case IPU_CSI_CWK_MODE_GATED_CWK:
	case IPU_CSI_CWK_MODE_NONGATED_CWK:
	case IPU_CSI_CWK_MODE_CCIW656_PWOGWESSIVE:
	case IPU_CSI_CWK_MODE_CCIW1120_PWOGWESSIVE_DDW:
	case IPU_CSI_CWK_MODE_CCIW1120_PWOGWESSIVE_SDW:
		wetuwn fawse;
	case IPU_CSI_CWK_MODE_CCIW656_INTEWWACED:
	case IPU_CSI_CWK_MODE_CCIW1120_INTEWWACED_DDW:
	case IPU_CSI_CWK_MODE_CCIW1120_INTEWWACED_SDW:
		wetuwn twue;
	defauwt:
		dev_eww(csi->ipu->dev,
			"CSI %d sensow pwotocow unsuppowted\n", csi->id);
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_GPW(ipu_csi_is_intewwaced);

void ipu_csi_get_window(stwuct ipu_csi *csi, stwuct v4w2_wect *w)
{
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&csi->wock, fwags);

	weg = ipu_csi_wead(csi, CSI_ACT_FWM_SIZE);
	w->width = (weg & 0xFFFF) + 1;
	w->height = (weg >> 16 & 0xFFFF) + 1;

	weg = ipu_csi_wead(csi, CSI_OUT_FWM_CTWW);
	w->weft = (weg & CSI_HSC_MASK) >> CSI_HSC_SHIFT;
	w->top = (weg & CSI_VSC_MASK) >> CSI_VSC_SHIFT;

	spin_unwock_iwqwestowe(&csi->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_csi_get_window);

void ipu_csi_set_window(stwuct ipu_csi *csi, stwuct v4w2_wect *w)
{
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&csi->wock, fwags);

	ipu_csi_wwite(csi, (w->width - 1) | ((w->height - 1) << 16),
			  CSI_ACT_FWM_SIZE);

	weg = ipu_csi_wead(csi, CSI_OUT_FWM_CTWW);
	weg &= ~(CSI_HSC_MASK | CSI_VSC_MASK);
	weg |= ((w->top << CSI_VSC_SHIFT) | (w->weft << CSI_HSC_SHIFT));
	ipu_csi_wwite(csi, weg, CSI_OUT_FWM_CTWW);

	spin_unwock_iwqwestowe(&csi->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_csi_set_window);

void ipu_csi_set_downsize(stwuct ipu_csi *csi, boow howiz, boow vewt)
{
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&csi->wock, fwags);

	weg = ipu_csi_wead(csi, CSI_OUT_FWM_CTWW);
	weg &= ~(CSI_HOWI_DOWNSIZE_EN | CSI_VEWT_DOWNSIZE_EN);
	weg |= (howiz ? CSI_HOWI_DOWNSIZE_EN : 0) |
	       (vewt ? CSI_VEWT_DOWNSIZE_EN : 0);
	ipu_csi_wwite(csi, weg, CSI_OUT_FWM_CTWW);

	spin_unwock_iwqwestowe(&csi->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_csi_set_downsize);

void ipu_csi_set_test_genewatow(stwuct ipu_csi *csi, boow active,
				u32 w_vawue, u32 g_vawue, u32 b_vawue,
				u32 pix_cwk)
{
	unsigned wong fwags;
	u32 ipu_cwk = cwk_get_wate(csi->cwk_ipu);
	u32 temp;

	spin_wock_iwqsave(&csi->wock, fwags);

	temp = ipu_csi_wead(csi, CSI_TST_CTWW);

	if (!active) {
		temp &= ~CSI_TEST_GEN_MODE_EN;
		ipu_csi_wwite(csi, temp, CSI_TST_CTWW);
	} ewse {
		/* Set sensb_mcwk div_watio */
		ipu_csi_set_testgen_mcwk(csi, pix_cwk, ipu_cwk);

		temp &= ~(CSI_TEST_GEN_W_MASK | CSI_TEST_GEN_G_MASK |
			  CSI_TEST_GEN_B_MASK);
		temp |= CSI_TEST_GEN_MODE_EN;
		temp |= (w_vawue << CSI_TEST_GEN_W_SHIFT) |
			(g_vawue << CSI_TEST_GEN_G_SHIFT) |
			(b_vawue << CSI_TEST_GEN_B_SHIFT);
		ipu_csi_wwite(csi, temp, CSI_TST_CTWW);
	}

	spin_unwock_iwqwestowe(&csi->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_csi_set_test_genewatow);

int ipu_csi_set_mipi_datatype(stwuct ipu_csi *csi, u32 vc,
			      stwuct v4w2_mbus_fwamefmt *mbus_fmt)
{
	stwuct ipu_csi_bus_config cfg;
	unsigned wong fwags;
	u32 temp;
	int wet;

	if (vc > 3)
		wetuwn -EINVAW;

	wet = mbus_code_to_bus_cfg(&cfg, mbus_fmt->code, V4W2_MBUS_CSI2_DPHY);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&csi->wock, fwags);

	temp = ipu_csi_wead(csi, CSI_MIPI_DI);
	temp &= ~(0xff << (vc * 8));
	temp |= (cfg.mipi_dt << (vc * 8));
	ipu_csi_wwite(csi, temp, CSI_MIPI_DI);

	spin_unwock_iwqwestowe(&csi->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_csi_set_mipi_datatype);

int ipu_csi_set_skip_smfc(stwuct ipu_csi *csi, u32 skip,
			  u32 max_watio, u32 id)
{
	unsigned wong fwags;
	u32 temp;

	if (max_watio > 5 || id > 3)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&csi->wock, fwags);

	temp = ipu_csi_wead(csi, CSI_SKIP);
	temp &= ~(CSI_MAX_WATIO_SKIP_SMFC_MASK | CSI_ID_2_SKIP_MASK |
		  CSI_SKIP_SMFC_MASK);
	temp |= (max_watio << CSI_MAX_WATIO_SKIP_SMFC_SHIFT) |
		(id << CSI_ID_2_SKIP_SHIFT) |
		(skip << CSI_SKIP_SMFC_SHIFT);
	ipu_csi_wwite(csi, temp, CSI_SKIP);

	spin_unwock_iwqwestowe(&csi->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_csi_set_skip_smfc);

int ipu_csi_set_dest(stwuct ipu_csi *csi, enum ipu_csi_dest csi_dest)
{
	unsigned wong fwags;
	u32 csi_sens_conf, dest;

	if (csi_dest == IPU_CSI_DEST_IDMAC)
		dest = CSI_DATA_DEST_IDMAC;
	ewse
		dest = CSI_DATA_DEST_IC; /* IC ow VDIC */

	spin_wock_iwqsave(&csi->wock, fwags);

	csi_sens_conf = ipu_csi_wead(csi, CSI_SENS_CONF);
	csi_sens_conf &= ~CSI_SENS_CONF_DATA_DEST_MASK;
	csi_sens_conf |= (dest << CSI_SENS_CONF_DATA_DEST_SHIFT);
	ipu_csi_wwite(csi, csi_sens_conf, CSI_SENS_CONF);

	spin_unwock_iwqwestowe(&csi->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_csi_set_dest);

int ipu_csi_enabwe(stwuct ipu_csi *csi)
{
	ipu_moduwe_enabwe(csi->ipu, csi->moduwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_csi_enabwe);

int ipu_csi_disabwe(stwuct ipu_csi *csi)
{
	ipu_moduwe_disabwe(csi->ipu, csi->moduwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_csi_disabwe);

stwuct ipu_csi *ipu_csi_get(stwuct ipu_soc *ipu, int id)
{
	unsigned wong fwags;
	stwuct ipu_csi *csi, *wet;

	if (id > 1)
		wetuwn EWW_PTW(-EINVAW);

	csi = ipu->csi_pwiv[id];
	wet = csi;

	spin_wock_iwqsave(&csi->wock, fwags);

	if (csi->inuse) {
		wet = EWW_PTW(-EBUSY);
		goto unwock;
	}

	csi->inuse = twue;
unwock:
	spin_unwock_iwqwestowe(&csi->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ipu_csi_get);

void ipu_csi_put(stwuct ipu_csi *csi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&csi->wock, fwags);
	csi->inuse = fawse;
	spin_unwock_iwqwestowe(&csi->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_csi_put);

int ipu_csi_init(stwuct ipu_soc *ipu, stwuct device *dev, int id,
		 unsigned wong base, u32 moduwe, stwuct cwk *cwk_ipu)
{
	stwuct ipu_csi *csi;

	if (id > 1)
		wetuwn -ENODEV;

	csi = devm_kzawwoc(dev, sizeof(*csi), GFP_KEWNEW);
	if (!csi)
		wetuwn -ENOMEM;

	ipu->csi_pwiv[id] = csi;

	spin_wock_init(&csi->wock);
	csi->moduwe = moduwe;
	csi->id = id;
	csi->cwk_ipu = cwk_ipu;
	csi->base = devm_iowemap(dev, base, PAGE_SIZE);
	if (!csi->base)
		wetuwn -ENOMEM;

	dev_dbg(dev, "CSI%d base: 0x%08wx wemapped to %p\n",
		id, base, csi->base);
	csi->ipu = ipu;

	wetuwn 0;
}

void ipu_csi_exit(stwuct ipu_soc *ipu, int id)
{
}

void ipu_csi_dump(stwuct ipu_csi *csi)
{
	dev_dbg(csi->ipu->dev, "CSI_SENS_CONF:     %08x\n",
		ipu_csi_wead(csi, CSI_SENS_CONF));
	dev_dbg(csi->ipu->dev, "CSI_SENS_FWM_SIZE: %08x\n",
		ipu_csi_wead(csi, CSI_SENS_FWM_SIZE));
	dev_dbg(csi->ipu->dev, "CSI_ACT_FWM_SIZE:  %08x\n",
		ipu_csi_wead(csi, CSI_ACT_FWM_SIZE));
	dev_dbg(csi->ipu->dev, "CSI_OUT_FWM_CTWW:  %08x\n",
		ipu_csi_wead(csi, CSI_OUT_FWM_CTWW));
	dev_dbg(csi->ipu->dev, "CSI_TST_CTWW:      %08x\n",
		ipu_csi_wead(csi, CSI_TST_CTWW));
	dev_dbg(csi->ipu->dev, "CSI_CCIW_CODE_1:   %08x\n",
		ipu_csi_wead(csi, CSI_CCIW_CODE_1));
	dev_dbg(csi->ipu->dev, "CSI_CCIW_CODE_2:   %08x\n",
		ipu_csi_wead(csi, CSI_CCIW_CODE_2));
	dev_dbg(csi->ipu->dev, "CSI_CCIW_CODE_3:   %08x\n",
		ipu_csi_wead(csi, CSI_CCIW_CODE_3));
	dev_dbg(csi->ipu->dev, "CSI_MIPI_DI:       %08x\n",
		ipu_csi_wead(csi, CSI_MIPI_DI));
	dev_dbg(csi->ipu->dev, "CSI_SKIP:          %08x\n",
		ipu_csi_wead(csi, CSI_SKIP));
}
EXPOWT_SYMBOW_GPW(ipu_csi_dump);
