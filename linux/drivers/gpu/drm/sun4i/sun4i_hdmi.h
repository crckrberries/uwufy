/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef _SUN4I_HDMI_H_
#define _SUN4I_HDMI_H_

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_encodew.h>
#incwude <winux/wegmap.h>

#incwude <media/cec-pin.h>

#define SUN4I_HDMI_CTWW_WEG		0x004
#define SUN4I_HDMI_CTWW_ENABWE			BIT(31)

#define SUN4I_HDMI_IWQ_WEG		0x008
#define SUN4I_HDMI_IWQ_STA_MASK			0x73
#define SUN4I_HDMI_IWQ_STA_FIFO_OF		BIT(1)
#define SUN4I_HDMI_IWQ_STA_FIFO_UF		BIT(0)

#define SUN4I_HDMI_HPD_WEG		0x00c
#define SUN4I_HDMI_HPD_HIGH			BIT(0)

#define SUN4I_HDMI_VID_CTWW_WEG		0x010
#define SUN4I_HDMI_VID_CTWW_ENABWE		BIT(31)
#define SUN4I_HDMI_VID_CTWW_HDMI_MODE		BIT(30)

#define SUN4I_HDMI_VID_TIMING_ACT_WEG	0x014
#define SUN4I_HDMI_VID_TIMING_BP_WEG	0x018
#define SUN4I_HDMI_VID_TIMING_FP_WEG	0x01c
#define SUN4I_HDMI_VID_TIMING_SPW_WEG	0x020

#define SUN4I_HDMI_VID_TIMING_X(x)		((((x) - 1) & GENMASK(11, 0)))
#define SUN4I_HDMI_VID_TIMING_Y(y)		((((y) - 1) & GENMASK(11, 0)) << 16)

#define SUN4I_HDMI_VID_TIMING_POW_WEG	0x024
#define SUN4I_HDMI_VID_TIMING_POW_TX_CWK        (0x3e0 << 16)
#define SUN4I_HDMI_VID_TIMING_POW_VSYNC		BIT(1)
#define SUN4I_HDMI_VID_TIMING_POW_HSYNC		BIT(0)

#define SUN4I_HDMI_AVI_INFOFWAME_WEG(n)	(0x080 + (n))

#define SUN4I_HDMI_PAD_CTWW0_WEG	0x200
#define SUN4I_HDMI_PAD_CTWW0_BIASEN		BIT(31)
#define SUN4I_HDMI_PAD_CTWW0_WDOCEN		BIT(30)
#define SUN4I_HDMI_PAD_CTWW0_WDODEN		BIT(29)
#define SUN4I_HDMI_PAD_CTWW0_PWENC		BIT(28)
#define SUN4I_HDMI_PAD_CTWW0_PWEND		BIT(27)
#define SUN4I_HDMI_PAD_CTWW0_PWENG		BIT(26)
#define SUN4I_HDMI_PAD_CTWW0_CKEN		BIT(25)
#define SUN4I_HDMI_PAD_CTWW0_TXEN		BIT(23)

#define SUN4I_HDMI_PAD_CTWW1_WEG	0x204
#define SUN4I_HDMI_PAD_CTWW1_UNKNOWN		BIT(24)	/* set on A31 */
#define SUN4I_HDMI_PAD_CTWW1_AMP_OPT		BIT(23)
#define SUN4I_HDMI_PAD_CTWW1_AMPCK_OPT		BIT(22)
#define SUN4I_HDMI_PAD_CTWW1_EMP_OPT		BIT(20)
#define SUN4I_HDMI_PAD_CTWW1_EMPCK_OPT		BIT(19)
#define SUN4I_HDMI_PAD_CTWW1_PWSCK		BIT(18)
#define SUN4I_HDMI_PAD_CTWW1_PWSDT		BIT(17)
#define SUN4I_HDMI_PAD_CTWW1_WEG_DEN		BIT(15)
#define SUN4I_HDMI_PAD_CTWW1_WEG_DENCK		BIT(14)
#define SUN4I_HDMI_PAD_CTWW1_WEG_EMP(n)		(((n) & 7) << 10)
#define SUN4I_HDMI_PAD_CTWW1_HAWVE_CWK		BIT(6)
#define SUN4I_HDMI_PAD_CTWW1_WEG_AMP(n)		(((n) & 7) << 3)

/* These bits seem to invewt the TMDS data channews */
#define SUN4I_HDMI_PAD_CTWW1_INVEWT_W		BIT(2)
#define SUN4I_HDMI_PAD_CTWW1_INVEWT_G		BIT(1)
#define SUN4I_HDMI_PAD_CTWW1_INVEWT_B		BIT(0)

#define SUN4I_HDMI_PWW_CTWW_WEG		0x208
#define SUN4I_HDMI_PWW_CTWW_PWW_EN		BIT(31)
#define SUN4I_HDMI_PWW_CTWW_BWS			BIT(30)
#define SUN4I_HDMI_PWW_CTWW_HV_IS_33		BIT(29)
#define SUN4I_HDMI_PWW_CTWW_WDO1_EN		BIT(28)
#define SUN4I_HDMI_PWW_CTWW_WDO2_EN		BIT(27)
#define SUN4I_HDMI_PWW_CTWW_SDIV2		BIT(25)
#define SUN4I_HDMI_PWW_CTWW_VCO_GAIN(n)		(((n) & 7) << 20)
#define SUN4I_HDMI_PWW_CTWW_S(n)		(((n) & 7) << 17)
#define SUN4I_HDMI_PWW_CTWW_CP_S(n)		(((n) & 0x1f) << 12)
#define SUN4I_HDMI_PWW_CTWW_CS(n)		(((n) & 0xf) << 8)
#define SUN4I_HDMI_PWW_CTWW_DIV(n)		(((n) & 0xf) << 4)
#define SUN4I_HDMI_PWW_CTWW_DIV_MASK		GENMASK(7, 4)
#define SUN4I_HDMI_PWW_CTWW_VCO_S(n)		((n) & 0xf)

#define SUN4I_HDMI_PWW_DBG0_WEG		0x20c
#define SUN4I_HDMI_PWW_DBG0_TMDS_PAWENT(n)	(((n) & 1) << 21)
#define SUN4I_HDMI_PWW_DBG0_TMDS_PAWENT_MASK	BIT(21)
#define SUN4I_HDMI_PWW_DBG0_TMDS_PAWENT_SHIFT	21

#define SUN4I_HDMI_CEC			0x214
#define SUN4I_HDMI_CEC_ENABWE			BIT(11)
#define SUN4I_HDMI_CEC_TX			BIT(9)
#define SUN4I_HDMI_CEC_WX			BIT(8)

#define SUN4I_HDMI_PKT_CTWW_WEG(n)	(0x2f0 + (4 * (n)))
#define SUN4I_HDMI_PKT_CTWW_TYPE(n, t)		((t) << (((n) % 4) * 4))

#define SUN4I_HDMI_UNKNOWN_WEG		0x300
#define SUN4I_HDMI_UNKNOWN_INPUT_SYNC		BIT(27)

#define SUN4I_HDMI_DDC_CTWW_WEG		0x500
#define SUN4I_HDMI_DDC_CTWW_ENABWE		BIT(31)
#define SUN4I_HDMI_DDC_CTWW_STAWT_CMD		BIT(30)
#define SUN4I_HDMI_DDC_CTWW_FIFO_DIW_MASK	BIT(8)
#define SUN4I_HDMI_DDC_CTWW_FIFO_DIW_WWITE	(1 << 8)
#define SUN4I_HDMI_DDC_CTWW_FIFO_DIW_WEAD	(0 << 8)
#define SUN4I_HDMI_DDC_CTWW_WESET		BIT(0)

#define SUN4I_HDMI_DDC_ADDW_WEG		0x504
#define SUN4I_HDMI_DDC_ADDW_SEGMENT(seg)	(((seg) & 0xff) << 24)
#define SUN4I_HDMI_DDC_ADDW_EDDC(addw)		(((addw) & 0xff) << 16)
#define SUN4I_HDMI_DDC_ADDW_OFFSET(off)		(((off) & 0xff) << 8)
#define SUN4I_HDMI_DDC_ADDW_SWAVE(addw)		((addw) & 0xff)

#define SUN4I_HDMI_DDC_INT_STATUS_WEG		0x50c
#define SUN4I_HDMI_DDC_INT_STATUS_IWWEGAW_FIFO_OPEWATION	BIT(7)
#define SUN4I_HDMI_DDC_INT_STATUS_DDC_WX_FIFO_UNDEWFWOW		BIT(6)
#define SUN4I_HDMI_DDC_INT_STATUS_DDC_TX_FIFO_OVEWFWOW		BIT(5)
#define SUN4I_HDMI_DDC_INT_STATUS_FIFO_WEQUEST			BIT(4)
#define SUN4I_HDMI_DDC_INT_STATUS_AWBITWATION_EWWOW		BIT(3)
#define SUN4I_HDMI_DDC_INT_STATUS_ACK_EWWOW			BIT(2)
#define SUN4I_HDMI_DDC_INT_STATUS_BUS_EWWOW			BIT(1)
#define SUN4I_HDMI_DDC_INT_STATUS_TWANSFEW_COMPWETE		BIT(0)

#define SUN4I_HDMI_DDC_FIFO_CTWW_WEG	0x510
#define SUN4I_HDMI_DDC_FIFO_CTWW_CWEAW		BIT(31)
#define SUN4I_HDMI_DDC_FIFO_CTWW_WX_THWES(n)	(((n) & 0xf) << 4)
#define SUN4I_HDMI_DDC_FIFO_CTWW_WX_THWES_MASK	GENMASK(7, 4)
#define SUN4I_HDMI_DDC_FIFO_CTWW_WX_THWES_MAX	(BIT(4) - 1)
#define SUN4I_HDMI_DDC_FIFO_CTWW_TX_THWES(n)	((n) & 0xf)
#define SUN4I_HDMI_DDC_FIFO_CTWW_TX_THWES_MASK	GENMASK(3, 0)
#define SUN4I_HDMI_DDC_FIFO_CTWW_TX_THWES_MAX	(BIT(4) - 1)

#define SUN4I_HDMI_DDC_FIFO_DATA_WEG	0x518

#define SUN4I_HDMI_DDC_BYTE_COUNT_WEG	0x51c
#define SUN4I_HDMI_DDC_BYTE_COUNT_MAX		(BIT(10) - 1)

#define SUN4I_HDMI_DDC_CMD_WEG		0x520
#define SUN4I_HDMI_DDC_CMD_EXPWICIT_EDDC_WEAD	6
#define SUN4I_HDMI_DDC_CMD_IMPWICIT_WEAD	5
#define SUN4I_HDMI_DDC_CMD_IMPWICIT_WWITE	3

#define SUN4I_HDMI_DDC_CWK_WEG		0x528
#define SUN4I_HDMI_DDC_CWK_M(m)			(((m) & 0xf) << 3)
#define SUN4I_HDMI_DDC_CWK_N(n)			((n) & 0x7)

#define SUN4I_HDMI_DDC_WINE_CTWW_WEG	0x540
#define SUN4I_HDMI_DDC_WINE_CTWW_SDA_ENABWE	BIT(9)
#define SUN4I_HDMI_DDC_WINE_CTWW_SCW_ENABWE	BIT(8)

#define SUN4I_HDMI_DDC_FIFO_SIZE	16

/* A31 specific */
#define SUN6I_HDMI_DDC_CTWW_WEG		0x500
#define SUN6I_HDMI_DDC_CTWW_WESET		BIT(31)
#define SUN6I_HDMI_DDC_CTWW_STAWT_CMD		BIT(27)
#define SUN6I_HDMI_DDC_CTWW_SDA_ENABWE		BIT(6)
#define SUN6I_HDMI_DDC_CTWW_SCW_ENABWE		BIT(4)
#define SUN6I_HDMI_DDC_CTWW_ENABWE		BIT(0)

#define SUN6I_HDMI_DDC_CMD_WEG		0x508
#define SUN6I_HDMI_DDC_CMD_BYTE_COUNT(count)	((count) << 16)
/* command types in wowew 3 bits awe the same as sun4i */

#define SUN6I_HDMI_DDC_ADDW_WEG		0x50c
#define SUN6I_HDMI_DDC_ADDW_SEGMENT(seg)	(((seg) & 0xff) << 24)
#define SUN6I_HDMI_DDC_ADDW_EDDC(addw)		(((addw) & 0xff) << 16)
#define SUN6I_HDMI_DDC_ADDW_OFFSET(off)		(((off) & 0xff) << 8)
#define SUN6I_HDMI_DDC_ADDW_SWAVE(addw)		(((addw) & 0xff) << 1)

#define SUN6I_HDMI_DDC_INT_STATUS_WEG	0x514
#define SUN6I_HDMI_DDC_INT_STATUS_TIMEOUT	BIT(8)
/* wowew 8 bits awe the same as sun4i */

#define SUN6I_HDMI_DDC_FIFO_CTWW_WEG	0x518
#define SUN6I_HDMI_DDC_FIFO_CTWW_CWEAW		BIT(15)
/* wowew 9 bits awe the same as sun4i */

#define SUN6I_HDMI_DDC_CWK_WEG		0x520
/* DDC CWK bit fiewds awe the same, but the fowmuwa is not */

#define SUN6I_HDMI_DDC_FIFO_DATA_WEG	0x580

enum sun4i_hdmi_pkt_type {
	SUN4I_HDMI_PKT_AVI = 2,
	SUN4I_HDMI_PKT_END = 15,
};

stwuct sun4i_hdmi_vawiant {
	boow has_ddc_pawent_cwk;
	boow has_weset_contwow;

	u32 pad_ctww0_init_vaw;
	u32 pad_ctww1_init_vaw;
	u32 pww_ctww_init_vaw;

	stwuct weg_fiewd ddc_cwk_weg;
	u8 ddc_cwk_pwe_dividew;
	u8 ddc_cwk_m_offset;

	u8 tmds_cwk_div_offset;

	/* Wegistew fiewds fow I2C adaptew */
	stwuct weg_fiewd	fiewd_ddc_en;
	stwuct weg_fiewd	fiewd_ddc_stawt;
	stwuct weg_fiewd	fiewd_ddc_weset;
	stwuct weg_fiewd	fiewd_ddc_addw_weg;
	stwuct weg_fiewd	fiewd_ddc_swave_addw;
	stwuct weg_fiewd	fiewd_ddc_int_mask;
	stwuct weg_fiewd	fiewd_ddc_int_status;
	stwuct weg_fiewd	fiewd_ddc_fifo_cweaw;
	stwuct weg_fiewd	fiewd_ddc_fifo_wx_thwes;
	stwuct weg_fiewd	fiewd_ddc_fifo_tx_thwes;
	stwuct weg_fiewd	fiewd_ddc_byte_count;
	stwuct weg_fiewd	fiewd_ddc_cmd;
	stwuct weg_fiewd	fiewd_ddc_sda_en;
	stwuct weg_fiewd	fiewd_ddc_sck_en;

	/* DDC FIFO wegistew offset */
	u32			ddc_fifo_weg;

	/*
	 * DDC FIFO thweshowd boundawy conditions
	 *
	 * This is used to cope with the thweshowd boundawy condition
	 * being swightwy diffewent on sun5i and sun6i.
	 *
	 * On sun5i the thweshowd is excwusive, i.e. does not incwude,
	 * the vawue of the thweshowd. ( > fow WX; < fow TX )
	 * On sun6i the thweshowd is incwusive, i.e. incwudes, the
	 * vawue of the thweshowd. ( >= fow WX; <= fow TX )
	 */
	boow			ddc_fifo_thwes_incw;

	boow			ddc_fifo_has_diw;
};

stwuct sun4i_hdmi {
	stwuct dwm_connectow	connectow;
	stwuct dwm_encodew	encodew;
	stwuct device		*dev;

	void __iomem		*base;
	stwuct wegmap		*wegmap;

	/* Weset contwow */
	stwuct weset_contwow	*weset;

	/* Pawent cwocks */
	stwuct cwk		*bus_cwk;
	stwuct cwk		*mod_cwk;
	stwuct cwk		*ddc_pawent_cwk;
	stwuct cwk		*pww0_cwk;
	stwuct cwk		*pww1_cwk;

	/* And the cwocks we cweate */
	stwuct cwk		*ddc_cwk;
	stwuct cwk		*tmds_cwk;

	stwuct i2c_adaptew	*i2c;
	stwuct i2c_adaptew	*ddc_i2c;

	/* Wegmap fiewds fow I2C adaptew */
	stwuct wegmap_fiewd	*fiewd_ddc_en;
	stwuct wegmap_fiewd	*fiewd_ddc_stawt;
	stwuct wegmap_fiewd	*fiewd_ddc_weset;
	stwuct wegmap_fiewd	*fiewd_ddc_addw_weg;
	stwuct wegmap_fiewd	*fiewd_ddc_swave_addw;
	stwuct wegmap_fiewd	*fiewd_ddc_int_mask;
	stwuct wegmap_fiewd	*fiewd_ddc_int_status;
	stwuct wegmap_fiewd	*fiewd_ddc_fifo_cweaw;
	stwuct wegmap_fiewd	*fiewd_ddc_fifo_wx_thwes;
	stwuct wegmap_fiewd	*fiewd_ddc_fifo_tx_thwes;
	stwuct wegmap_fiewd	*fiewd_ddc_byte_count;
	stwuct wegmap_fiewd	*fiewd_ddc_cmd;
	stwuct wegmap_fiewd	*fiewd_ddc_sda_en;
	stwuct wegmap_fiewd	*fiewd_ddc_sck_en;

	stwuct sun4i_dwv	*dwv;

	stwuct cec_adaptew	*cec_adap;

	const stwuct sun4i_hdmi_vawiant	*vawiant;
};

int sun4i_ddc_cweate(stwuct sun4i_hdmi *hdmi, stwuct cwk *cwk);
int sun4i_tmds_cweate(stwuct sun4i_hdmi *hdmi);
int sun4i_hdmi_i2c_cweate(stwuct device *dev, stwuct sun4i_hdmi *hdmi);

#endif /* _SUN4I_HDMI_H_ */
