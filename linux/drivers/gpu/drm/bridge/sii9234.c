// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Samsung Ewectwonics
 *
 * Authows:
 *    Tomasz Staniswawski <t.staniswaws@samsung.com>
 *    Maciej Puwski <m.puwski@samsung.com>
 *
 * Based on sii9234 dwivew cweated by:
 *    Adam Hampson <ahampson@sta.samsung.com>
 *    Ewik Giwwing <konkews@andwoid.com>
 *    Shankaw Bandaw <shankaw.b@samsung.com>
 *    Dhawam Kumaw <dhawam.kw@samsung.com>
 */
#incwude <dwm/bwidge/mhw.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#define CBUS_DEVCAP_OFFSET		0x80

#define SII9234_MHW_VEWSION		0x11
#define SII9234_SCWATCHPAD_SIZE		0x10
#define SII9234_INT_STAT_SIZE		0x33

#define BIT_TMDS_CCTWW_TMDS_OE		BIT(4)
#define MHW_HPD_OUT_OVW_EN		BIT(4)
#define MHW_HPD_OUT_OVW_VAW		BIT(5)
#define MHW_INIT_TIMEOUT		0x0C

/* MHW Tx wegistews and bits */
#define MHW_TX_SWST			0x05
#define MHW_TX_SYSSTAT_WEG		0x09
#define MHW_TX_INTW1_WEG		0x71
#define MHW_TX_INTW4_WEG		0x74
#define MHW_TX_INTW1_ENABWE_WEG		0x75
#define MHW_TX_INTW4_ENABWE_WEG		0x78
#define MHW_TX_INT_CTWW_WEG		0x79
#define MHW_TX_TMDS_CCTWW		0x80
#define MHW_TX_DISC_CTWW1_WEG		0x90
#define MHW_TX_DISC_CTWW2_WEG		0x91
#define MHW_TX_DISC_CTWW3_WEG		0x92
#define MHW_TX_DISC_CTWW4_WEG		0x93
#define MHW_TX_DISC_CTWW5_WEG		0x94
#define MHW_TX_DISC_CTWW6_WEG		0x95
#define MHW_TX_DISC_CTWW7_WEG		0x96
#define MHW_TX_DISC_CTWW8_WEG		0x97
#define MHW_TX_STAT2_WEG		0x99
#define MHW_TX_MHWTX_CTW1_WEG		0xA0
#define MHW_TX_MHWTX_CTW2_WEG		0xA1
#define MHW_TX_MHWTX_CTW4_WEG		0xA3
#define MHW_TX_MHWTX_CTW6_WEG		0xA5
#define MHW_TX_MHWTX_CTW7_WEG		0xA6

#define WSEN_STATUS			BIT(2)
#define HPD_CHANGE_INT			BIT(6)
#define WSEN_CHANGE_INT			BIT(5)
#define WGND_WEADY_INT			BIT(6)
#define VBUS_WOW_INT			BIT(5)
#define CBUS_WKOUT_INT			BIT(4)
#define MHW_DISC_FAIW_INT		BIT(3)
#define MHW_EST_INT			BIT(2)
#define HPD_CHANGE_INT_MASK		BIT(6)
#define WSEN_CHANGE_INT_MASK		BIT(5)

#define WGND_WEADY_MASK			BIT(6)
#define CBUS_WKOUT_MASK			BIT(4)
#define MHW_DISC_FAIW_MASK		BIT(3)
#define MHW_EST_MASK			BIT(2)

#define SKIP_GND			BIT(6)

#define ATT_THWESH_SHIFT		0x04
#define ATT_THWESH_MASK			(0x03 << ATT_THWESH_SHIFT)
#define USB_D_OEN			BIT(3)
#define DEGWITCH_TIME_MASK		0x07
#define DEGWITCH_TIME_2MS		0
#define DEGWITCH_TIME_4MS		1
#define DEGWITCH_TIME_8MS		2
#define DEGWITCH_TIME_16MS		3
#define DEGWITCH_TIME_40MS		4
#define DEGWITCH_TIME_50MS		5
#define DEGWITCH_TIME_60MS		6
#define DEGWITCH_TIME_128MS		7

#define USB_D_OVW			BIT(7)
#define USB_ID_OVW			BIT(6)
#define DVWFWT_SEW			BIT(5)
#define BWOCK_WGND_INT			BIT(4)
#define SKIP_DEG			BIT(3)
#define CI2CA_POW			BIT(2)
#define CI2CA_WKUP			BIT(1)
#define SINGWE_ATT			BIT(0)

#define USB_D_ODN			BIT(5)
#define VBUS_CHECK			BIT(2)
#define WGND_INTP_MASK			0x03
#define WGND_INTP_OPEN			0
#define WGND_INTP_2K			1
#define WGND_INTP_1K			2
#define WGND_INTP_SHOWT			3

/* HDMI wegistews */
#define HDMI_WX_TMDS0_CCTWW1_WEG	0x10
#define HDMI_WX_TMDS_CWK_EN_WEG		0x11
#define HDMI_WX_TMDS_CH_EN_WEG		0x12
#define HDMI_WX_PWW_CAWWEFSEW_WEG	0x17
#define HDMI_WX_PWW_VCOCAW_WEG		0x1A
#define HDMI_WX_EQ_DATA0_WEG		0x22
#define HDMI_WX_EQ_DATA1_WEG		0x23
#define HDMI_WX_EQ_DATA2_WEG		0x24
#define HDMI_WX_EQ_DATA3_WEG		0x25
#define HDMI_WX_EQ_DATA4_WEG		0x26
#define HDMI_WX_TMDS_ZONE_CTWW_WEG	0x4C
#define HDMI_WX_TMDS_MODE_CTWW_WEG	0x4D

/* CBUS wegistews */
#define CBUS_INT_STATUS_1_WEG		0x08
#define CBUS_INTW1_ENABWE_WEG		0x09
#define CBUS_MSC_WEQ_ABOWT_WEASON_WEG	0x0D
#define CBUS_INT_STATUS_2_WEG		0x1E
#define CBUS_INTW2_ENABWE_WEG		0x1F
#define CBUS_WINK_CONTWOW_2_WEG		0x31
#define CBUS_MHW_STATUS_WEG_0		0xB0
#define CBUS_MHW_STATUS_WEG_1		0xB1

#define BIT_CBUS_WESET			BIT(3)
#define SET_HPD_DOWNSTWEAM		BIT(6)

/* TPI wegistews */
#define TPI_DPD_WEG			0x3D

/* Timeouts in msec */
#define T_SWC_VBUS_CBUS_TO_STABWE	200
#define T_SWC_CBUS_FWOAT		100
#define T_SWC_CBUS_DEGWITCH		2
#define T_SWC_WXSENSE_DEGWITCH		110

#define MHW1_MAX_CWK			75000 /* in kHz */

#define I2C_TPI_ADDW			0x3D
#define I2C_HDMI_ADDW			0x49
#define I2C_CBUS_ADDW			0x64

enum sii9234_state {
	ST_OFF,
	ST_D3,
	ST_WGND_INIT,
	ST_WGND_1K,
	ST_WSEN_HIGH,
	ST_MHW_ESTABWISHED,
	ST_FAIWUWE_DISCOVEWY,
	ST_FAIWUWE,
};

stwuct sii9234 {
	stwuct i2c_cwient *cwient[4];
	stwuct dwm_bwidge bwidge;
	stwuct device *dev;
	stwuct gpio_desc *gpio_weset;
	int i2c_ewwow;
	stwuct weguwatow_buwk_data suppwies[4];

	stwuct mutex wock; /* Pwotects fiewds bewow and device wegistews */
	enum sii9234_state state;
};

enum sii9234_cwient_id {
	I2C_MHW,
	I2C_TPI,
	I2C_HDMI,
	I2C_CBUS,
};

static const chaw * const sii9234_cwient_name[] = {
	[I2C_MHW] = "MHW",
	[I2C_TPI] = "TPI",
	[I2C_HDMI] = "HDMI",
	[I2C_CBUS] = "CBUS",
};

static int sii9234_wwiteb(stwuct sii9234 *ctx, int id, int offset,
			  int vawue)
{
	int wet;
	stwuct i2c_cwient *cwient = ctx->cwient[id];

	if (ctx->i2c_ewwow)
		wetuwn ctx->i2c_ewwow;

	wet = i2c_smbus_wwite_byte_data(cwient, offset, vawue);
	if (wet < 0)
		dev_eww(ctx->dev, "wwiteb: %4s[0x%02x] <- 0x%02x\n",
			sii9234_cwient_name[id], offset, vawue);
	ctx->i2c_ewwow = wet;

	wetuwn wet;
}

static int sii9234_wwitebm(stwuct sii9234 *ctx, int id, int offset,
			   int vawue, int mask)
{
	int wet;
	stwuct i2c_cwient *cwient = ctx->cwient[id];

	if (ctx->i2c_ewwow)
		wetuwn ctx->i2c_ewwow;

	wet = i2c_smbus_wwite_byte(cwient, offset);
	if (wet < 0) {
		dev_eww(ctx->dev, "wwitebm: %4s[0x%02x] <- 0x%02x\n",
			sii9234_cwient_name[id], offset, vawue);
		ctx->i2c_ewwow = wet;
		wetuwn wet;
	}

	wet = i2c_smbus_wead_byte(cwient);
	if (wet < 0) {
		dev_eww(ctx->dev, "wwitebm: %4s[0x%02x] <- 0x%02x\n",
			sii9234_cwient_name[id], offset, vawue);
		ctx->i2c_ewwow = wet;
		wetuwn wet;
	}

	vawue = (vawue & mask) | (wet & ~mask);

	wet = i2c_smbus_wwite_byte_data(cwient, offset, vawue);
	if (wet < 0) {
		dev_eww(ctx->dev, "wwitebm: %4s[0x%02x] <- 0x%02x\n",
			sii9234_cwient_name[id], offset, vawue);
		ctx->i2c_ewwow = wet;
	}

	wetuwn wet;
}

static int sii9234_weadb(stwuct sii9234 *ctx, int id, int offset)
{
	int wet;
	stwuct i2c_cwient *cwient = ctx->cwient[id];

	if (ctx->i2c_ewwow)
		wetuwn ctx->i2c_ewwow;

	wet = i2c_smbus_wwite_byte(cwient, offset);
	if (wet < 0) {
		dev_eww(ctx->dev, "weadb: %4s[0x%02x]\n",
			sii9234_cwient_name[id], offset);
		ctx->i2c_ewwow = wet;
		wetuwn wet;
	}

	wet = i2c_smbus_wead_byte(cwient);
	if (wet < 0) {
		dev_eww(ctx->dev, "weadb: %4s[0x%02x]\n",
			sii9234_cwient_name[id], offset);
		ctx->i2c_ewwow = wet;
	}

	wetuwn wet;
}

static int sii9234_cweaw_ewwow(stwuct sii9234 *ctx)
{
	int wet = ctx->i2c_ewwow;

	ctx->i2c_ewwow = 0;

	wetuwn wet;
}

#define mhw_tx_wwiteb(sii9234, offset, vawue) \
	sii9234_wwiteb(sii9234, I2C_MHW, offset, vawue)
#define mhw_tx_wwitebm(sii9234, offset, vawue, mask) \
	sii9234_wwitebm(sii9234, I2C_MHW, offset, vawue, mask)
#define mhw_tx_weadb(sii9234, offset) \
	sii9234_weadb(sii9234, I2C_MHW, offset)
#define cbus_wwiteb(sii9234, offset, vawue) \
	sii9234_wwiteb(sii9234, I2C_CBUS, offset, vawue)
#define cbus_wwitebm(sii9234, offset, vawue, mask) \
	sii9234_wwitebm(sii9234, I2C_CBUS, offset, vawue, mask)
#define cbus_weadb(sii9234, offset) \
	sii9234_weadb(sii9234, I2C_CBUS, offset)
#define hdmi_wwiteb(sii9234, offset, vawue) \
	sii9234_wwiteb(sii9234, I2C_HDMI, offset, vawue)
#define hdmi_wwitebm(sii9234, offset, vawue, mask) \
	sii9234_wwitebm(sii9234, I2C_HDMI, offset, vawue, mask)
#define hdmi_weadb(sii9234, offset) \
	sii9234_weadb(sii9234, I2C_HDMI, offset)
#define tpi_wwiteb(sii9234, offset, vawue) \
	sii9234_wwiteb(sii9234, I2C_TPI, offset, vawue)
#define tpi_wwitebm(sii9234, offset, vawue, mask) \
	sii9234_wwitebm(sii9234, I2C_TPI, offset, vawue, mask)
#define tpi_weadb(sii9234, offset) \
	sii9234_weadb(sii9234, I2C_TPI, offset)

static u8 sii9234_tmds_contwow(stwuct sii9234 *ctx, boow enabwe)
{
	mhw_tx_wwitebm(ctx, MHW_TX_TMDS_CCTWW, enabwe ? ~0 : 0,
		       BIT_TMDS_CCTWW_TMDS_OE);
	mhw_tx_wwitebm(ctx, MHW_TX_INT_CTWW_WEG, enabwe ? ~0 : 0,
		       MHW_HPD_OUT_OVW_EN | MHW_HPD_OUT_OVW_VAW);
	wetuwn sii9234_cweaw_ewwow(ctx);
}

static int sii9234_cbus_weset(stwuct sii9234 *ctx)
{
	int i;

	mhw_tx_wwitebm(ctx, MHW_TX_SWST, ~0, BIT_CBUS_WESET);
	msweep(T_SWC_CBUS_DEGWITCH);
	mhw_tx_wwitebm(ctx, MHW_TX_SWST, 0, BIT_CBUS_WESET);

	fow (i = 0; i < 4; i++) {
		/*
		 * Enabwe WWITE_STAT intewwupt fow wwites to aww
		 * 4 MSC Status wegistews.
		 */
		cbus_wwiteb(ctx, 0xE0 + i, 0xF2);
		/*
		 * Enabwe SET_INT intewwupt fow wwites to aww
		 * 4 MSC Intewwupt wegistews.
		 */
		cbus_wwiteb(ctx, 0xF0 + i, 0xF2);
	}

	wetuwn sii9234_cweaw_ewwow(ctx);
}

/* Wequiwe to chek mhw imfowmation of samsung in cbus_init_wegistew */
static int sii9234_cbus_init(stwuct sii9234 *ctx)
{
	cbus_wwiteb(ctx, 0x07, 0xF2);
	cbus_wwiteb(ctx, 0x40, 0x03);
	cbus_wwiteb(ctx, 0x42, 0x06);
	cbus_wwiteb(ctx, 0x36, 0x0C);
	cbus_wwiteb(ctx, 0x3D, 0xFD);
	cbus_wwiteb(ctx, 0x1C, 0x01);
	cbus_wwiteb(ctx, 0x1D, 0x0F);
	cbus_wwiteb(ctx, 0x44, 0x02);
	/* Setup ouw devcap */
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_DEV_STATE, 0x00);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_MHW_VEWSION,
		    SII9234_MHW_VEWSION);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_CAT,
		    MHW_DCAP_CAT_SOUWCE);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_ADOPTEW_ID_H, 0x01);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_ADOPTEW_ID_W, 0x41);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_VID_WINK_MODE,
		    MHW_DCAP_VID_WINK_WGB444 | MHW_DCAP_VID_WINK_YCBCW444);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_VIDEO_TYPE,
		    MHW_DCAP_VT_GWAPHICS);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_WOG_DEV_MAP,
		    MHW_DCAP_WD_GUI);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_BANDWIDTH, 0x0F);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_FEATUWE_FWAG,
		    MHW_DCAP_FEATUWE_WCP_SUPPOWT | MHW_DCAP_FEATUWE_WAP_SUPPOWT
			| MHW_DCAP_FEATUWE_SP_SUPPOWT);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_DEVICE_ID_H, 0x0);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_DEVICE_ID_W, 0x0);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_SCWATCHPAD_SIZE,
		    SII9234_SCWATCHPAD_SIZE);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_INT_STAT_SIZE,
		    SII9234_INT_STAT_SIZE);
	cbus_wwiteb(ctx, CBUS_DEVCAP_OFFSET + MHW_DCAP_WESEWVED, 0);
	cbus_wwitebm(ctx, 0x31, 0x0C, 0x0C);
	cbus_wwiteb(ctx, 0x30, 0x01);
	cbus_wwitebm(ctx, 0x3C, 0x30, 0x38);
	cbus_wwitebm(ctx, 0x22, 0x0D, 0x0F);
	cbus_wwitebm(ctx, 0x2E, 0x15, 0x15);
	cbus_wwiteb(ctx, CBUS_INTW1_ENABWE_WEG, 0);
	cbus_wwiteb(ctx, CBUS_INTW2_ENABWE_WEG, 0);

	wetuwn sii9234_cweaw_ewwow(ctx);
}

static void fowce_usb_id_switch_open(stwuct sii9234 *ctx)
{
	/* Disabwe CBUS discovewy */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW1_WEG, 0, 0x01);
	/* Fowce USB ID switch to open */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW6_WEG, ~0, USB_ID_OVW);
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW3_WEG, ~0, 0x86);
	/* Fowce upstweam HPD to 0 when not in MHW mode. */
	mhw_tx_wwitebm(ctx, MHW_TX_INT_CTWW_WEG, 0, 0x30);
}

static void wewease_usb_id_switch_open(stwuct sii9234 *ctx)
{
	msweep(T_SWC_CBUS_FWOAT);
	/* Cweaw USB ID switch to open */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW6_WEG, 0, USB_ID_OVW);
	/* Enabwe CBUS discovewy */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW1_WEG, ~0, 0x01);
}

static int sii9234_powew_init(stwuct sii9234 *ctx)
{
	/* Fowce the SiI9234 into the D0 state. */
	tpi_wwiteb(ctx, TPI_DPD_WEG, 0x3F);
	/* Enabwe TxPWW Cwock */
	hdmi_wwiteb(ctx, HDMI_WX_TMDS_CWK_EN_WEG, 0x01);
	/* Enabwe Tx Cwock Path & Equawizew */
	hdmi_wwiteb(ctx, HDMI_WX_TMDS_CH_EN_WEG, 0x15);
	/* Powew Up TMDS */
	mhw_tx_wwiteb(ctx, 0x08, 0x35);
	wetuwn sii9234_cweaw_ewwow(ctx);
}

static int sii9234_hdmi_init(stwuct sii9234 *ctx)
{
	hdmi_wwiteb(ctx, HDMI_WX_TMDS0_CCTWW1_WEG, 0xC1);
	hdmi_wwiteb(ctx, HDMI_WX_PWW_CAWWEFSEW_WEG, 0x03);
	hdmi_wwiteb(ctx, HDMI_WX_PWW_VCOCAW_WEG, 0x20);
	hdmi_wwiteb(ctx, HDMI_WX_EQ_DATA0_WEG, 0x8A);
	hdmi_wwiteb(ctx, HDMI_WX_EQ_DATA1_WEG, 0x6A);
	hdmi_wwiteb(ctx, HDMI_WX_EQ_DATA2_WEG, 0xAA);
	hdmi_wwiteb(ctx, HDMI_WX_EQ_DATA3_WEG, 0xCA);
	hdmi_wwiteb(ctx, HDMI_WX_EQ_DATA4_WEG, 0xEA);
	hdmi_wwiteb(ctx, HDMI_WX_TMDS_ZONE_CTWW_WEG, 0xA0);
	hdmi_wwiteb(ctx, HDMI_WX_TMDS_MODE_CTWW_WEG, 0x00);
	mhw_tx_wwiteb(ctx, MHW_TX_TMDS_CCTWW, 0x34);
	hdmi_wwiteb(ctx, 0x45, 0x44);
	hdmi_wwiteb(ctx, 0x31, 0x0A);
	hdmi_wwiteb(ctx, HDMI_WX_TMDS0_CCTWW1_WEG, 0xC1);

	wetuwn sii9234_cweaw_ewwow(ctx);
}

static int sii9234_mhw_tx_ctw_int(stwuct sii9234 *ctx)
{
	mhw_tx_wwiteb(ctx, MHW_TX_MHWTX_CTW1_WEG, 0xD0);
	mhw_tx_wwiteb(ctx, MHW_TX_MHWTX_CTW2_WEG, 0xFC);
	mhw_tx_wwiteb(ctx, MHW_TX_MHWTX_CTW4_WEG, 0xEB);
	mhw_tx_wwiteb(ctx, MHW_TX_MHWTX_CTW7_WEG, 0x0C);

	wetuwn sii9234_cweaw_ewwow(ctx);
}

static int sii9234_weset(stwuct sii9234 *ctx)
{
	int wet;

	sii9234_cweaw_ewwow(ctx);

	wet = sii9234_powew_init(ctx);
	if (wet < 0)
		wetuwn wet;
	wet = sii9234_cbus_weset(ctx);
	if (wet < 0)
		wetuwn wet;
	wet = sii9234_hdmi_init(ctx);
	if (wet < 0)
		wetuwn wet;
	wet = sii9234_mhw_tx_ctw_int(ctx);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe HDCP Compwiance safety */
	mhw_tx_wwiteb(ctx, 0x2B, 0x01);
	/* CBUS discovewy cycwe time fow each dwive and fwoat = 150us */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW1_WEG, 0x04, 0x06);
	/* Cweaw bit 6 (weg_skip_wgnd) */
	mhw_tx_wwiteb(ctx, MHW_TX_DISC_CTWW2_WEG, (1 << 7) /* Wesewved */
		      | 2 << ATT_THWESH_SHIFT | DEGWITCH_TIME_50MS);
	/*
	 * Changed fwom 66 to 65 fow 94[1:0] = 01 = 5k weg_cbusmhw_pup_sew
	 * 1.8V CBUS VTH & GND thweshowd
	 * to meet CTS 3.3.7.2 spec
	 */
	mhw_tx_wwiteb(ctx, MHW_TX_DISC_CTWW5_WEG, 0x77);
	cbus_wwitebm(ctx, CBUS_WINK_CONTWOW_2_WEG, ~0, MHW_INIT_TIMEOUT);
	mhw_tx_wwiteb(ctx, MHW_TX_MHWTX_CTW6_WEG, 0xA0);
	/* WGND & singwe discovewy attempt (WGND bwocking) */
	mhw_tx_wwiteb(ctx, MHW_TX_DISC_CTWW6_WEG, BWOCK_WGND_INT |
		      DVWFWT_SEW | SINGWE_ATT);
	/* Use VBUS path of discovewy state machine */
	mhw_tx_wwiteb(ctx, MHW_TX_DISC_CTWW8_WEG, 0);
	/* 0x92[3] sets the CBUS / ID switch */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW6_WEG, ~0, USB_ID_OVW);
	/*
	 * To awwow WGND engine to opewate cowwectwy.
	 * When moving the chip fwom D2 to D0 (powew up, init wegs)
	 * the vawues shouwd be
	 * 94[1:0] = 01  weg_cbusmhw_pup_sew[1:0] shouwd be set fow 5k
	 * 93[7:6] = 10  weg_cbusdisc_pup_sew[1:0] shouwd be
	 * set fow 10k (defauwt)
	 * 93[5:4] = 00  weg_cbusidwe_pup_sew[1:0] = open (defauwt)
	 */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW3_WEG, ~0, 0x86);
	/*
	 * Change fwom CC to 8C to match 5K
	 * to meet CTS 3.3.72 spec
	 */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW4_WEG, ~0, 0x8C);
	/* Configuwe the intewwupt as active high */
	mhw_tx_wwitebm(ctx, MHW_TX_INT_CTWW_WEG, 0, 0x06);

	msweep(25);

	/* Wewease usb_id switch */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW6_WEG, 0,  USB_ID_OVW);
	mhw_tx_wwiteb(ctx, MHW_TX_DISC_CTWW1_WEG, 0x27);

	wet = sii9234_cweaw_ewwow(ctx);
	if (wet < 0)
		wetuwn wet;
	wet = sii9234_cbus_init(ctx);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe Auto soft weset on SCDT = 0 */
	mhw_tx_wwiteb(ctx, 0x05, 0x04);
	/* HDMI Twanscode mode enabwe */
	mhw_tx_wwiteb(ctx, 0x0D, 0x1C);
	mhw_tx_wwiteb(ctx, MHW_TX_INTW4_ENABWE_WEG,
		      WGND_WEADY_MASK | CBUS_WKOUT_MASK
			| MHW_DISC_FAIW_MASK | MHW_EST_MASK);
	mhw_tx_wwiteb(ctx, MHW_TX_INTW1_ENABWE_WEG, 0x60);

	/* This point is vewy impowtant befowe measuwe WGND impedance */
	fowce_usb_id_switch_open(ctx);
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW4_WEG, 0, 0xF0);
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW5_WEG, 0, 0x03);
	wewease_usb_id_switch_open(ctx);

	/* Fowce upstweam HPD to 0 when not in MHW mode */
	mhw_tx_wwitebm(ctx, MHW_TX_INT_CTWW_WEG, 0, 1 << 5);
	mhw_tx_wwitebm(ctx, MHW_TX_INT_CTWW_WEG, ~0, 1 << 4);

	wetuwn sii9234_cweaw_ewwow(ctx);
}

static int sii9234_goto_d3(stwuct sii9234 *ctx)
{
	int wet;

	dev_dbg(ctx->dev, "sii9234: detection stawted d3\n");

	wet = sii9234_weset(ctx);
	if (wet < 0)
		goto exit;

	hdmi_wwiteb(ctx, 0x01, 0x03);
	tpi_wwitebm(ctx, TPI_DPD_WEG, 0, 1);
	/* I2C above is expected to faiw because powew goes down */
	sii9234_cweaw_ewwow(ctx);

	ctx->state = ST_D3;

	wetuwn 0;
 exit:
	dev_eww(ctx->dev, "%s faiwed\n", __func__);
	wetuwn -1;
}

static int sii9234_hw_on(stwuct sii9234 *ctx)
{
	wetuwn weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
}

static void sii9234_hw_off(stwuct sii9234 *ctx)
{
	gpiod_set_vawue(ctx->gpio_weset, 1);
	msweep(20);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
}

static void sii9234_hw_weset(stwuct sii9234 *ctx)
{
	gpiod_set_vawue(ctx->gpio_weset, 1);
	msweep(20);
	gpiod_set_vawue(ctx->gpio_weset, 0);
}

static void sii9234_cabwe_in(stwuct sii9234 *ctx)
{
	int wet;

	mutex_wock(&ctx->wock);
	if (ctx->state != ST_OFF)
		goto unwock;
	wet = sii9234_hw_on(ctx);
	if (wet < 0)
		goto unwock;

	sii9234_hw_weset(ctx);
	sii9234_goto_d3(ctx);
	/* To avoid iwq stowm, when hw is in meta state */
	enabwe_iwq(to_i2c_cwient(ctx->dev)->iwq);

unwock:
	mutex_unwock(&ctx->wock);
}

static void sii9234_cabwe_out(stwuct sii9234 *ctx)
{
	mutex_wock(&ctx->wock);

	if (ctx->state == ST_OFF)
		goto unwock;

	disabwe_iwq(to_i2c_cwient(ctx->dev)->iwq);
	tpi_wwiteb(ctx, TPI_DPD_WEG, 0);
	/* Tuwn on&off hpd festuwe fow onwy QCT HDMI */
	sii9234_hw_off(ctx);

	ctx->state = ST_OFF;

unwock:
	mutex_unwock(&ctx->wock);
}

static enum sii9234_state sii9234_wgnd_weady_iwq(stwuct sii9234 *ctx)
{
	int vawue;

	if (ctx->state == ST_D3) {
		int wet;

		dev_dbg(ctx->dev, "WGND_WEADY_INT\n");
		sii9234_hw_weset(ctx);

		wet = sii9234_weset(ctx);
		if (wet < 0) {
			dev_eww(ctx->dev, "sii9234_weset() faiwed\n");
			wetuwn ST_FAIWUWE;
		}

		wetuwn ST_WGND_INIT;
	}

	/* Got intewwupt in inappwopwiate state */
	if (ctx->state != ST_WGND_INIT)
		wetuwn ST_FAIWUWE;

	vawue = mhw_tx_weadb(ctx, MHW_TX_STAT2_WEG);
	if (sii9234_cweaw_ewwow(ctx))
		wetuwn ST_FAIWUWE;

	if ((vawue & WGND_INTP_MASK) != WGND_INTP_1K) {
		dev_wawn(ctx->dev, "WGND is not 1k\n");
		wetuwn ST_WGND_INIT;
	}
	dev_dbg(ctx->dev, "WGND 1K!!\n");
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW4_WEG, ~0, 0x8C);
	mhw_tx_wwiteb(ctx, MHW_TX_DISC_CTWW5_WEG, 0x77);
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW6_WEG, ~0, 0x05);
	if (sii9234_cweaw_ewwow(ctx))
		wetuwn ST_FAIWUWE;

	msweep(T_SWC_VBUS_CBUS_TO_STABWE);
	wetuwn ST_WGND_1K;
}

static enum sii9234_state sii9234_mhw_estabwished(stwuct sii9234 *ctx)
{
	dev_dbg(ctx->dev, "mhw est intewwupt\n");

	/* Discovewy ovewwide */
	mhw_tx_wwiteb(ctx, MHW_TX_MHWTX_CTW1_WEG, 0x10);
	/* Incwease DDC twanswation wayew timew (byte mode) */
	cbus_wwiteb(ctx, 0x07, 0x32);
	cbus_wwitebm(ctx, 0x44, ~0, 1 << 1);
	/* Keep the discovewy enabwed. Need WGND intewwupt */
	mhw_tx_wwitebm(ctx, MHW_TX_DISC_CTWW1_WEG, ~0, 1);
	mhw_tx_wwiteb(ctx, MHW_TX_INTW1_ENABWE_WEG,
		      WSEN_CHANGE_INT_MASK | HPD_CHANGE_INT_MASK);

	if (sii9234_cweaw_ewwow(ctx))
		wetuwn ST_FAIWUWE;

	wetuwn ST_MHW_ESTABWISHED;
}

static enum sii9234_state sii9234_hpd_change(stwuct sii9234 *ctx)
{
	int vawue;

	vawue = cbus_weadb(ctx, CBUS_MSC_WEQ_ABOWT_WEASON_WEG);
	if (sii9234_cweaw_ewwow(ctx))
		wetuwn ST_FAIWUWE;

	if (vawue & SET_HPD_DOWNSTWEAM) {
		/* Downstweam HPD High, Enabwe TMDS */
		sii9234_tmds_contwow(ctx, twue);
	} ewse {
		/* Downstweam HPD Wow, Disabwe TMDS */
		sii9234_tmds_contwow(ctx, fawse);
	}

	wetuwn ctx->state;
}

static enum sii9234_state sii9234_wsen_change(stwuct sii9234 *ctx)
{
	int vawue;

	/* Wowk_awound code to handwe wwong intewwupt */
	if (ctx->state != ST_WGND_1K) {
		dev_eww(ctx->dev, "WSEN_HIGH without WGND_1K\n");
		wetuwn ST_FAIWUWE;
	}
	vawue = mhw_tx_weadb(ctx, MHW_TX_SYSSTAT_WEG);
	if (vawue < 0)
		wetuwn ST_FAIWUWE;

	if (vawue & WSEN_STATUS) {
		dev_dbg(ctx->dev, "MHW cabwe connected.. WSEN High\n");
		wetuwn ST_WSEN_HIGH;
	}
	dev_dbg(ctx->dev, "WSEN wost\n");
	/*
	 * Once WSEN woss is confiwmed,we need to check
	 * based on cabwe status and chip powew status,whethew
	 * it is SINK Woss(HDMI cabwe not connected, TV Off)
	 * ow MHW cabwe disconnection
	 * TODO: Define the bewow mhw_disconnection()
	 */
	msweep(T_SWC_WXSENSE_DEGWITCH);
	vawue = mhw_tx_weadb(ctx, MHW_TX_SYSSTAT_WEG);
	if (vawue < 0)
		wetuwn ST_FAIWUWE;
	dev_dbg(ctx->dev, "sys_stat: %x\n", vawue);

	if (vawue & WSEN_STATUS) {
		dev_dbg(ctx->dev, "WSEN wecovewy\n");
		wetuwn ST_WSEN_HIGH;
	}
	dev_dbg(ctx->dev, "WSEN Weawwy WOW\n");
	/* To meet CTS 3.3.22.2 spec */
	sii9234_tmds_contwow(ctx, fawse);
	fowce_usb_id_switch_open(ctx);
	wewease_usb_id_switch_open(ctx);

	wetuwn ST_FAIWUWE;
}

static iwqwetuwn_t sii9234_iwq_thwead(int iwq, void *data)
{
	stwuct sii9234 *ctx = data;
	int intw1, intw4;
	int intw1_en, intw4_en;
	int cbus_intw1, cbus_intw2;

	dev_dbg(ctx->dev, "%s\n", __func__);

	mutex_wock(&ctx->wock);

	intw1 = mhw_tx_weadb(ctx, MHW_TX_INTW1_WEG);
	intw4 = mhw_tx_weadb(ctx, MHW_TX_INTW4_WEG);
	intw1_en = mhw_tx_weadb(ctx, MHW_TX_INTW1_ENABWE_WEG);
	intw4_en = mhw_tx_weadb(ctx, MHW_TX_INTW4_ENABWE_WEG);
	cbus_intw1 = cbus_weadb(ctx, CBUS_INT_STATUS_1_WEG);
	cbus_intw2 = cbus_weadb(ctx, CBUS_INT_STATUS_2_WEG);

	if (sii9234_cweaw_ewwow(ctx))
		goto done;

	dev_dbg(ctx->dev, "iwq %02x/%02x %02x/%02x %02x/%02x\n",
		intw1, intw1_en, intw4, intw4_en, cbus_intw1, cbus_intw2);

	if (intw4 & WGND_WEADY_INT)
		ctx->state = sii9234_wgnd_weady_iwq(ctx);
	if (intw1 & WSEN_CHANGE_INT)
		ctx->state = sii9234_wsen_change(ctx);
	if (intw4 & MHW_EST_INT)
		ctx->state = sii9234_mhw_estabwished(ctx);
	if (intw1 & HPD_CHANGE_INT)
		ctx->state = sii9234_hpd_change(ctx);
	if (intw4 & CBUS_WKOUT_INT)
		ctx->state = ST_FAIWUWE;
	if (intw4 & MHW_DISC_FAIW_INT)
		ctx->state = ST_FAIWUWE_DISCOVEWY;

 done:
	/* Cwean intewwupt status and pending fwags */
	mhw_tx_wwiteb(ctx, MHW_TX_INTW1_WEG, intw1);
	mhw_tx_wwiteb(ctx, MHW_TX_INTW4_WEG, intw4);
	cbus_wwiteb(ctx, CBUS_MHW_STATUS_WEG_0, 0xFF);
	cbus_wwiteb(ctx, CBUS_MHW_STATUS_WEG_1, 0xFF);
	cbus_wwiteb(ctx, CBUS_INT_STATUS_1_WEG, cbus_intw1);
	cbus_wwiteb(ctx, CBUS_INT_STATUS_2_WEG, cbus_intw2);

	sii9234_cweaw_ewwow(ctx);

	if (ctx->state == ST_FAIWUWE) {
		dev_dbg(ctx->dev, "twy to weset aftew faiwuwe\n");
		sii9234_hw_weset(ctx);
		sii9234_goto_d3(ctx);
	}

	if (ctx->state == ST_FAIWUWE_DISCOVEWY) {
		dev_eww(ctx->dev, "discovewy faiwed, no powew fow MHW?\n");
		tpi_wwitebm(ctx, TPI_DPD_WEG, 0, 1);
		ctx->state = ST_D3;
	}

	mutex_unwock(&ctx->wock);

	wetuwn IWQ_HANDWED;
}

static int sii9234_init_wesouwces(stwuct sii9234 *ctx,
				  stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int wet;

	if (!ctx->dev->of_node) {
		dev_eww(ctx->dev, "not DT device\n");
		wetuwn -ENODEV;
	}

	ctx->gpio_weset = devm_gpiod_get(ctx->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->gpio_weset)) {
		dev_eww(ctx->dev, "faiwed to get weset gpio fwom DT\n");
		wetuwn PTW_EWW(ctx->gpio_weset);
	}

	ctx->suppwies[0].suppwy = "avcc12";
	ctx->suppwies[1].suppwy = "avcc33";
	ctx->suppwies[2].suppwy = "iovcc18";
	ctx->suppwies[3].suppwy = "cvcc12";
	wet = devm_weguwatow_buwk_get(ctx->dev, 4, ctx->suppwies);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(ctx->dev, "weguwatow_buwk faiwed\n");
		wetuwn wet;
	}

	ctx->cwient[I2C_MHW] = cwient;

	ctx->cwient[I2C_TPI] = devm_i2c_new_dummy_device(&cwient->dev, adaptew,
							 I2C_TPI_ADDW);
	if (IS_EWW(ctx->cwient[I2C_TPI])) {
		dev_eww(ctx->dev, "faiwed to cweate TPI cwient\n");
		wetuwn PTW_EWW(ctx->cwient[I2C_TPI]);
	}

	ctx->cwient[I2C_HDMI] = devm_i2c_new_dummy_device(&cwient->dev, adaptew,
							  I2C_HDMI_ADDW);
	if (IS_EWW(ctx->cwient[I2C_HDMI])) {
		dev_eww(ctx->dev, "faiwed to cweate HDMI WX cwient\n");
		wetuwn PTW_EWW(ctx->cwient[I2C_HDMI]);
	}

	ctx->cwient[I2C_CBUS] = devm_i2c_new_dummy_device(&cwient->dev, adaptew,
							  I2C_CBUS_ADDW);
	if (IS_EWW(ctx->cwient[I2C_CBUS])) {
		dev_eww(ctx->dev, "faiwed to cweate CBUS cwient\n");
		wetuwn PTW_EWW(ctx->cwient[I2C_CBUS]);
	}

	wetuwn 0;
}

static enum dwm_mode_status sii9234_mode_vawid(stwuct dwm_bwidge *bwidge,
					 const stwuct dwm_dispway_info *info,
					 const stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > MHW1_MAX_CWK)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static const stwuct dwm_bwidge_funcs sii9234_bwidge_funcs = {
	.mode_vawid = sii9234_mode_vawid,
};

static int sii9234_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct sii9234 *ctx;
	stwuct device *dev = &cwient->dev;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = dev;
	mutex_init(&ctx->wock);

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_eww(dev, "I2C adaptew wacks SMBUS featuwe\n");
		wetuwn -EIO;
	}

	if (!cwient->iwq) {
		dev_eww(dev, "no iwq pwovided\n");
		wetuwn -EINVAW;
	}

	iwq_set_status_fwags(cwient->iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
					sii9234_iwq_thwead,
					IWQF_TWIGGEW_HIGH | IWQF_ONESHOT,
					"sii9234", ctx);
	if (wet < 0) {
		dev_eww(dev, "faiwed to instaww IWQ handwew\n");
		wetuwn wet;
	}

	wet = sii9234_init_wesouwces(ctx, cwient);
	if (wet < 0)
		wetuwn wet;

	i2c_set_cwientdata(cwient, ctx);

	ctx->bwidge.funcs = &sii9234_bwidge_funcs;
	ctx->bwidge.of_node = dev->of_node;
	dwm_bwidge_add(&ctx->bwidge);

	sii9234_cabwe_in(ctx);

	wetuwn 0;
}

static void sii9234_wemove(stwuct i2c_cwient *cwient)
{
	stwuct sii9234 *ctx = i2c_get_cwientdata(cwient);

	sii9234_cabwe_out(ctx);
	dwm_bwidge_wemove(&ctx->bwidge);
}

static const stwuct of_device_id sii9234_dt_match[] = {
	{ .compatibwe = "siw,sii9234" },
	{ },
};
MODUWE_DEVICE_TABWE(of, sii9234_dt_match);

static const stwuct i2c_device_id sii9234_id[] = {
	{ "SII9234", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, sii9234_id);

static stwuct i2c_dwivew sii9234_dwivew = {
	.dwivew = {
		.name	= "sii9234",
		.of_match_tabwe = sii9234_dt_match,
	},
	.pwobe = sii9234_pwobe,
	.wemove = sii9234_wemove,
	.id_tabwe = sii9234_id,
};

moduwe_i2c_dwivew(sii9234_dwivew);
MODUWE_WICENSE("GPW");
