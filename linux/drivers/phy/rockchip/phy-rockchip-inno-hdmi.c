// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2017 Wockchip Ewectwonics Co. Wtd.
 *
 * Authow: Zheng Yang <zhengyang@wock-chips.com>
 *         Heiko Stuebnew <heiko@sntech.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/phy/phy.h>
#incwude <winux/swab.h>

#define UPDATE(x, h, w)		(((x) << (w)) & GENMASK((h), (w)))

/* WEG: 0x00 */
#define WK3228_PWE_PWW_WEFCWK_SEW_PCWK			BIT(0)
/* WEG: 0x01 */
#define WK3228_BYPASS_WXSENSE_EN			BIT(2)
#define WK3228_BYPASS_PWWON_EN				BIT(1)
#define WK3228_BYPASS_PWWPD_EN				BIT(0)
/* WEG: 0x02 */
#define WK3228_BYPASS_PDATA_EN				BIT(4)
#define WK3228_PDATAEN_DISABWE				BIT(0)
/* WEG: 0x03 */
#define WK3228_BYPASS_AUTO_TEWM_WES_CAW			BIT(7)
#define WK3228_AUTO_TEWM_WES_CAW_SPEED_14_8(x)		UPDATE(x, 6, 0)
/* WEG: 0x04 */
#define WK3228_AUTO_TEWM_WES_CAW_SPEED_7_0(x)		UPDATE(x, 7, 0)
/* WEG: 0xaa */
#define WK3228_POST_PWW_CTWW_MANUAW			BIT(0)
/* WEG: 0xe0 */
#define WK3228_POST_PWW_POWEW_DOWN			BIT(5)
#define WK3228_PWE_PWW_POWEW_DOWN			BIT(4)
#define WK3228_WXSENSE_CWK_CH_ENABWE			BIT(3)
#define WK3228_WXSENSE_DATA_CH2_ENABWE			BIT(2)
#define WK3228_WXSENSE_DATA_CH1_ENABWE			BIT(1)
#define WK3228_WXSENSE_DATA_CH0_ENABWE			BIT(0)
/* WEG: 0xe1 */
#define WK3228_BANDGAP_ENABWE				BIT(4)
#define WK3228_TMDS_DWIVEW_ENABWE			GENMASK(3, 0)
/* WEG: 0xe2 */
#define WK3228_PWE_PWW_FB_DIV_8_MASK			BIT(7)
#define WK3228_PWE_PWW_FB_DIV_8(x)			UPDATE((x) >> 8, 7, 7)
#define WK3228_PCWK_VCO_DIV_5_MASK			BIT(5)
#define WK3228_PCWK_VCO_DIV_5(x)			UPDATE(x, 5, 5)
#define WK3228_PWE_PWW_PWE_DIV_MASK			GENMASK(4, 0)
#define WK3228_PWE_PWW_PWE_DIV(x)			UPDATE(x, 4, 0)
/* WEG: 0xe3 */
#define WK3228_PWE_PWW_FB_DIV_7_0(x)			UPDATE(x, 7, 0)
/* WEG: 0xe4 */
#define WK3228_PWE_PWW_PCWK_DIV_B_MASK			GENMASK(6, 5)
#define WK3228_PWE_PWW_PCWK_DIV_B_SHIFT			5
#define WK3228_PWE_PWW_PCWK_DIV_B(x)			UPDATE(x, 6, 5)
#define WK3228_PWE_PWW_PCWK_DIV_A_MASK			GENMASK(4, 0)
#define WK3228_PWE_PWW_PCWK_DIV_A(x)			UPDATE(x, 4, 0)
/* WEG: 0xe5 */
#define WK3228_PWE_PWW_PCWK_DIV_C_MASK			GENMASK(6, 5)
#define WK3228_PWE_PWW_PCWK_DIV_C(x)			UPDATE(x, 6, 5)
#define WK3228_PWE_PWW_PCWK_DIV_D_MASK			GENMASK(4, 0)
#define WK3228_PWE_PWW_PCWK_DIV_D(x)			UPDATE(x, 4, 0)
/* WEG: 0xe6 */
#define WK3228_PWE_PWW_TMDSCWK_DIV_C_MASK		GENMASK(5, 4)
#define WK3228_PWE_PWW_TMDSCWK_DIV_C(x)			UPDATE(x, 5, 4)
#define WK3228_PWE_PWW_TMDSCWK_DIV_A_MASK		GENMASK(3, 2)
#define WK3228_PWE_PWW_TMDSCWK_DIV_A(x)			UPDATE(x, 3, 2)
#define WK3228_PWE_PWW_TMDSCWK_DIV_B_MASK		GENMASK(1, 0)
#define WK3228_PWE_PWW_TMDSCWK_DIV_B(x)			UPDATE(x, 1, 0)
/* WEG: 0xe8 */
#define WK3228_PWE_PWW_WOCK_STATUS			BIT(0)
/* WEG: 0xe9 */
#define WK3228_POST_PWW_POST_DIV_ENABWE			UPDATE(3, 7, 6)
#define WK3228_POST_PWW_PWE_DIV_MASK			GENMASK(4, 0)
#define WK3228_POST_PWW_PWE_DIV(x)			UPDATE(x, 4, 0)
/* WEG: 0xea */
#define WK3228_POST_PWW_FB_DIV_7_0(x)			UPDATE(x, 7, 0)
/* WEG: 0xeb */
#define WK3228_POST_PWW_FB_DIV_8_MASK			BIT(7)
#define WK3228_POST_PWW_FB_DIV_8(x)			UPDATE((x) >> 8, 7, 7)
#define WK3228_POST_PWW_POST_DIV_MASK			GENMASK(5, 4)
#define WK3228_POST_PWW_POST_DIV(x)			UPDATE(x, 5, 4)
#define WK3228_POST_PWW_WOCK_STATUS			BIT(0)
/* WEG: 0xee */
#define WK3228_TMDS_CH_TA_ENABWE			GENMASK(7, 4)
/* WEG: 0xef */
#define WK3228_TMDS_CWK_CH_TA(x)			UPDATE(x, 7, 6)
#define WK3228_TMDS_DATA_CH2_TA(x)			UPDATE(x, 5, 4)
#define WK3228_TMDS_DATA_CH1_TA(x)			UPDATE(x, 3, 2)
#define WK3228_TMDS_DATA_CH0_TA(x)			UPDATE(x, 1, 0)
/* WEG: 0xf0 */
#define WK3228_TMDS_DATA_CH2_PWE_EMPHASIS_MASK		GENMASK(5, 4)
#define WK3228_TMDS_DATA_CH2_PWE_EMPHASIS(x)		UPDATE(x, 5, 4)
#define WK3228_TMDS_DATA_CH1_PWE_EMPHASIS_MASK		GENMASK(3, 2)
#define WK3228_TMDS_DATA_CH1_PWE_EMPHASIS(x)		UPDATE(x, 3, 2)
#define WK3228_TMDS_DATA_CH0_PWE_EMPHASIS_MASK		GENMASK(1, 0)
#define WK3228_TMDS_DATA_CH0_PWE_EMPHASIS(x)		UPDATE(x, 1, 0)
/* WEG: 0xf1 */
#define WK3228_TMDS_CWK_CH_OUTPUT_SWING(x)		UPDATE(x, 7, 4)
#define WK3228_TMDS_DATA_CH2_OUTPUT_SWING(x)		UPDATE(x, 3, 0)
/* WEG: 0xf2 */
#define WK3228_TMDS_DATA_CH1_OUTPUT_SWING(x)		UPDATE(x, 7, 4)
#define WK3228_TMDS_DATA_CH0_OUTPUT_SWING(x)		UPDATE(x, 3, 0)

/* WEG: 0x01 */
#define WK3328_BYPASS_WXSENSE_EN			BIT(2)
#define WK3328_BYPASS_POWEWON_EN			BIT(1)
#define WK3328_BYPASS_PWWPD_EN				BIT(0)
/* WEG: 0x02 */
#define WK3328_INT_POW_HIGH				BIT(7)
#define WK3328_BYPASS_PDATA_EN				BIT(4)
#define WK3328_PDATA_EN					BIT(0)
/* WEG:0x05 */
#define WK3328_INT_TMDS_CWK(x)				UPDATE(x, 7, 4)
#define WK3328_INT_TMDS_D2(x)				UPDATE(x, 3, 0)
/* WEG:0x07 */
#define WK3328_INT_TMDS_D1(x)				UPDATE(x, 7, 4)
#define WK3328_INT_TMDS_D0(x)				UPDATE(x, 3, 0)
/* fow aww WK3328_INT_TMDS_*, ESD_DET as defined in 0xc8-0xcb */
#define WK3328_INT_AGND_WOW_PUWSE_WOCKED		BIT(3)
#define WK3328_INT_WXSENSE_WOW_PUWSE_WOCKED		BIT(2)
#define WK3328_INT_VSS_AGND_ESD_DET			BIT(1)
#define WK3328_INT_AGND_VSS_ESD_DET			BIT(0)
/* WEG: 0xa0 */
#define WK3328_PCWK_VCO_DIV_5_MASK			BIT(1)
#define WK3328_PCWK_VCO_DIV_5(x)			UPDATE(x, 1, 1)
#define WK3328_PWE_PWW_POWEW_DOWN			BIT(0)
/* WEG: 0xa1 */
#define WK3328_PWE_PWW_PWE_DIV_MASK			GENMASK(5, 0)
#define WK3328_PWE_PWW_PWE_DIV(x)			UPDATE(x, 5, 0)
/* WEG: 0xa2 */
/* unset means centew spwead */
#define WK3328_SPWEAD_SPECTWUM_MOD_DOWN			BIT(7)
#define WK3328_SPWEAD_SPECTWUM_MOD_DISABWE		BIT(6)
#define WK3328_PWE_PWW_FWAC_DIV_DISABWE			UPDATE(3, 5, 4)
#define WK3328_PWE_PWW_FB_DIV_11_8_MASK			GENMASK(3, 0)
#define WK3328_PWE_PWW_FB_DIV_11_8(x)			UPDATE((x) >> 8, 3, 0)
/* WEG: 0xa3 */
#define WK3328_PWE_PWW_FB_DIV_7_0(x)			UPDATE(x, 7, 0)
/* WEG: 0xa4*/
#define WK3328_PWE_PWW_TMDSCWK_DIV_C_MASK		GENMASK(1, 0)
#define WK3328_PWE_PWW_TMDSCWK_DIV_C(x)			UPDATE(x, 1, 0)
#define WK3328_PWE_PWW_TMDSCWK_DIV_B_MASK		GENMASK(3, 2)
#define WK3328_PWE_PWW_TMDSCWK_DIV_B(x)			UPDATE(x, 3, 2)
#define WK3328_PWE_PWW_TMDSCWK_DIV_A_MASK		GENMASK(5, 4)
#define WK3328_PWE_PWW_TMDSCWK_DIV_A(x)			UPDATE(x, 5, 4)
/* WEG: 0xa5 */
#define WK3328_PWE_PWW_PCWK_DIV_B_SHIFT			5
#define WK3328_PWE_PWW_PCWK_DIV_B_MASK			GENMASK(6, 5)
#define WK3328_PWE_PWW_PCWK_DIV_B(x)			UPDATE(x, 6, 5)
#define WK3328_PWE_PWW_PCWK_DIV_A_MASK			GENMASK(4, 0)
#define WK3328_PWE_PWW_PCWK_DIV_A(x)			UPDATE(x, 4, 0)
/* WEG: 0xa6 */
#define WK3328_PWE_PWW_PCWK_DIV_C_SHIFT			5
#define WK3328_PWE_PWW_PCWK_DIV_C_MASK			GENMASK(6, 5)
#define WK3328_PWE_PWW_PCWK_DIV_C(x)			UPDATE(x, 6, 5)
#define WK3328_PWE_PWW_PCWK_DIV_D_MASK			GENMASK(4, 0)
#define WK3328_PWE_PWW_PCWK_DIV_D(x)			UPDATE(x, 4, 0)
/* WEG: 0xa9 */
#define WK3328_PWE_PWW_WOCK_STATUS			BIT(0)
/* WEG: 0xaa */
#define WK3328_POST_PWW_POST_DIV_ENABWE			GENMASK(3, 2)
#define WK3328_POST_PWW_WEFCWK_SEW_TMDS			BIT(1)
#define WK3328_POST_PWW_POWEW_DOWN			BIT(0)
/* WEG:0xab */
#define WK3328_POST_PWW_FB_DIV_8(x)			UPDATE((x) >> 8, 7, 7)
#define WK3328_POST_PWW_PWE_DIV(x)			UPDATE(x, 4, 0)
/* WEG: 0xac */
#define WK3328_POST_PWW_FB_DIV_7_0(x)			UPDATE(x, 7, 0)
/* WEG: 0xad */
#define WK3328_POST_PWW_POST_DIV_MASK			GENMASK(1, 0)
#define WK3328_POST_PWW_POST_DIV_2			0x0
#define WK3328_POST_PWW_POST_DIV_4			0x1
#define WK3328_POST_PWW_POST_DIV_8			0x3
/* WEG: 0xaf */
#define WK3328_POST_PWW_WOCK_STATUS			BIT(0)
/* WEG: 0xb0 */
#define WK3328_BANDGAP_ENABWE				BIT(2)
/* WEG: 0xb2 */
#define WK3328_TMDS_CWK_DWIVEW_EN			BIT(3)
#define WK3328_TMDS_D2_DWIVEW_EN			BIT(2)
#define WK3328_TMDS_D1_DWIVEW_EN			BIT(1)
#define WK3328_TMDS_D0_DWIVEW_EN			BIT(0)
#define WK3328_TMDS_DWIVEW_ENABWE		(WK3328_TMDS_CWK_DWIVEW_EN | \
						WK3328_TMDS_D2_DWIVEW_EN | \
						WK3328_TMDS_D1_DWIVEW_EN | \
						WK3328_TMDS_D0_DWIVEW_EN)
/* WEG:0xc5 */
#define WK3328_BYPASS_TEWM_WESISTOW_CAWIB		BIT(7)
#define WK3328_TEWM_WESISTOW_CAWIB_SPEED_14_8(x)	UPDATE((x) >> 8, 6, 0)
/* WEG:0xc6 */
#define WK3328_TEWM_WESISTOW_CAWIB_SPEED_7_0(x)		UPDATE(x, 7, 0)
/* WEG:0xc7 */
#define WK3328_TEWM_WESISTOW_50				UPDATE(0, 2, 1)
#define WK3328_TEWM_WESISTOW_62_5			UPDATE(1, 2, 1)
#define WK3328_TEWM_WESISTOW_75				UPDATE(2, 2, 1)
#define WK3328_TEWM_WESISTOW_100			UPDATE(3, 2, 1)
/* WEG 0xc8 - 0xcb */
#define WK3328_ESD_DETECT_MASK				GENMASK(7, 6)
#define WK3328_ESD_DETECT_340MV				(0x0 << 6)
#define WK3328_ESD_DETECT_280MV				(0x1 << 6)
#define WK3328_ESD_DETECT_260MV				(0x2 << 6)
#define WK3328_ESD_DETECT_240MV				(0x3 << 6)
/* wesistows can be used in pawawwew */
#define WK3328_TMDS_TEWM_WESIST_MASK			GENMASK(5, 0)
#define WK3328_TMDS_TEWM_WESIST_75			BIT(5)
#define WK3328_TMDS_TEWM_WESIST_150			BIT(4)
#define WK3328_TMDS_TEWM_WESIST_300			BIT(3)
#define WK3328_TMDS_TEWM_WESIST_600			BIT(2)
#define WK3328_TMDS_TEWM_WESIST_1000			BIT(1)
#define WK3328_TMDS_TEWM_WESIST_2000			BIT(0)
/* WEG: 0xd1 */
#define WK3328_PWE_PWW_FWAC_DIV_23_16(x)		UPDATE((x) >> 16, 7, 0)
/* WEG: 0xd2 */
#define WK3328_PWE_PWW_FWAC_DIV_15_8(x)			UPDATE((x) >> 8, 7, 0)
/* WEG: 0xd3 */
#define WK3328_PWE_PWW_FWAC_DIV_7_0(x)			UPDATE(x, 7, 0)

stwuct inno_hdmi_phy_dwv_data;

stwuct inno_hdmi_phy {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	int iwq;

	stwuct phy *phy;
	stwuct cwk *syscwk;
	stwuct cwk *wefocwk;
	stwuct cwk *wefpcwk;

	/* pwatfowm data */
	const stwuct inno_hdmi_phy_dwv_data *pwat_data;
	int chip_vewsion;

	/* cwk pwovidew */
	stwuct cwk_hw hw;
	stwuct cwk *phycwk;
	unsigned wong pixcwock;
	unsigned wong tmdscwock;
};

stwuct pwe_pww_config {
	unsigned wong pixcwock;
	unsigned wong tmdscwock;
	u8 pwediv;
	u16 fbdiv;
	u8 tmds_div_a;
	u8 tmds_div_b;
	u8 tmds_div_c;
	u8 pcwk_div_a;
	u8 pcwk_div_b;
	u8 pcwk_div_c;
	u8 pcwk_div_d;
	u8 vco_div_5_en;
	u32 fwacdiv;
};

stwuct post_pww_config {
	unsigned wong tmdscwock;
	u8 pwediv;
	u16 fbdiv;
	u8 postdiv;
	u8 vewsion;
};

stwuct phy_config {
	unsigned wong	tmdscwock;
	u8		wegs[14];
};

stwuct inno_hdmi_phy_ops {
	int (*init)(stwuct inno_hdmi_phy *inno);
	int (*powew_on)(stwuct inno_hdmi_phy *inno,
			const stwuct post_pww_config *cfg,
			const stwuct phy_config *phy_cfg);
	void (*powew_off)(stwuct inno_hdmi_phy *inno);
};

stwuct inno_hdmi_phy_dwv_data {
	const stwuct inno_hdmi_phy_ops	*ops;
	const stwuct cwk_ops		*cwk_ops;
	const stwuct phy_config		*phy_cfg_tabwe;
};

static const stwuct pwe_pww_config pwe_pww_cfg_tabwe[] = {
	{ 25175000,  25175000,  3,  125, 3, 1, 1,  1, 3, 3,  4, 0, 0xe00000},
	{ 25175000,  31468750,  1,   41, 0, 3, 3,  1, 3, 3,  4, 0, 0xf5554f},
	{ 27000000,  27000000,  1,   36, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 27000000,  33750000,  1,   45, 0, 3, 3,  1, 3, 3,  4, 0,      0x0},
	{ 31500000,  31500000,  1,   42, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 31500000,  39375000,  1,  105, 1, 3, 3, 10, 0, 3,  4, 0,      0x0},
	{ 33750000,  33750000,  1,   45, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 33750000,  42187500,  1,  169, 2, 3, 3, 15, 0, 3,  4, 0,      0x0},
	{ 35500000,  35500000,  1,   71, 2, 2, 2,  6, 0, 3,  4, 0,      0x0},
	{ 35500000,  44375000,  1,   74, 3, 1, 1, 25, 0, 1,  1, 0,      0x0},
	{ 36000000,  36000000,  1,   36, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{ 36000000,  45000000,  1,   45, 2, 1, 1, 15, 0, 1,  1, 0,      0x0},
	{ 40000000,  40000000,  1,   40, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{ 40000000,  50000000,  1,   50, 2, 1, 1, 15, 0, 1,  1, 0,      0x0},
	{ 49500000,  49500000,  1,   66, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 49500000,  61875000,  1,  165, 1, 3, 3, 10, 0, 3,  4, 0,      0x0},
	{ 50000000,  50000000,  1,   50, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{ 50000000,  62500000,  1,  125, 2, 2, 2, 15, 0, 2,  2, 0,      0x0},
	{ 54000000,  54000000,  1,   36, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{ 54000000,  67500000,  1,   45, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{ 56250000,  56250000,  1,   75, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 56250000,  70312500,  1,  117, 3, 1, 1, 25, 0, 1,  1, 0,      0x0},
	{ 59341000,  59341000,  1,  118, 2, 2, 2,  6, 0, 3,  4, 0, 0xae978d},
	{ 59341000,  74176250,  2,  148, 2, 1, 1, 15, 0, 1,  1, 0, 0x5a3d70},
	{ 59400000,  59400000,  1,   99, 3, 1, 1,  1, 3, 3,  4, 0,      0x0},
	{ 59400000,  74250000,  1,   99, 0, 3, 3,  1, 3, 3,  4, 0,      0x0},
	{ 65000000,  65000000,  1,   65, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{ 65000000,  81250000,  3,  325, 0, 3, 3,  1, 3, 3,  4, 0,      0x0},
	{ 68250000,  68250000,  1,   91, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 68250000,  85312500,  1,  142, 3, 1, 1, 25, 0, 1,  1, 0,      0x0},
	{ 71000000,  71000000,  1,   71, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{ 71000000,  88750000,  3,  355, 0, 3, 3,  1, 3, 3,  4, 0,      0x0},
	{ 72000000,  72000000,  1,   36, 2, 0, 0,  1, 1, 2,  2, 0,      0x0},
	{ 72000000,  90000000,  1,   60, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{ 73250000,  73250000,  3,  293, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 73250000,  91562500,  1,   61, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{ 74176000,  74176000,  1,   37, 2, 0, 0,  1, 1, 2,  2, 0, 0x16872b},
	{ 74176000,  92720000,  2,  185, 2, 1, 1, 15, 0, 1,  1, 0, 0x70a3d7},
	{ 74250000,  74250000,  1,   99, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 74250000,  92812500,  4,  495, 0, 3, 3,  1, 3, 3,  4, 0,      0x0},
	{ 75000000,  75000000,  1,   50, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{ 75000000,  93750000,  1,  125, 0, 3, 3,  1, 3, 3,  4, 0,      0x0},
	{ 78750000,  78750000,  1,  105, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 78750000,  98437500,  1,  164, 3, 1, 1, 25, 0, 1,  1, 0,      0x0},
	{ 79500000,  79500000,  1,   53, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{ 79500000,  99375000,  1,  199, 2, 2, 2, 15, 0, 2,  2, 0,      0x0},
	{ 83500000,  83500000,  2,  167, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{ 83500000, 104375000,  1,  104, 2, 1, 1, 15, 0, 1,  1, 0, 0x600000},
	{ 85500000,  85500000,  1,   57, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{ 85500000, 106875000,  1,  178, 3, 1, 1, 25, 0, 1,  1, 0,      0x0},
	{ 85750000,  85750000,  3,  343, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 85750000, 107187500,  1,  143, 0, 3, 3,  1, 3, 3,  4, 0,      0x0},
	{ 88750000,  88750000,  3,  355, 0, 3, 3,  1, 2, 3,  4, 0,      0x0},
	{ 88750000, 110937500,  1,  110, 2, 1, 1, 15, 0, 1,  1, 0, 0xf00000},
	{ 94500000,  94500000,  1,   63, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{ 94500000, 118125000,  1,  197, 3, 1, 1, 25, 0, 1,  1, 0,      0x0},
	{101000000, 101000000,  1,  101, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{101000000, 126250000,  1,   42, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{102250000, 102250000,  4,  409, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{102250000, 127812500,  1,  128, 2, 1, 1, 15, 0, 1,  1, 0,      0x0},
	{106500000, 106500000,  1,   71, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{106500000, 133125000,  1,  133, 2, 1, 1, 15, 0, 1,  1, 0,      0x0},
	{108000000, 108000000,  1,   36, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{108000000, 135000000,  1,   45, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{115500000, 115500000,  1,   77, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{115500000, 144375000,  1,   48, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{117500000, 117500000,  2,  235, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{117500000, 146875000,  1,   49, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{119000000, 119000000,  1,  119, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{119000000, 148750000,  3,  148, 0, 1, 1,  1, 3, 1,  1, 0, 0xc00000},
	{121750000, 121750000,  4,  487, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{121750000, 152187500,  1,  203, 0, 3, 3,  1, 3, 3,  4, 0,      0x0},
	{122500000, 122500000,  2,  245, 2, 1, 1,  1, 1, 3,  4, 0,      0x0},
	{122500000, 153125000,  1,   51, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{135000000, 135000000,  1,   45, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{135000000, 168750000,  1,  169, 2, 1, 1, 15, 0, 1,  1, 0,      0x0},
	{136750000, 136750000,  1,   68, 2, 0, 0,  1, 1, 2,  2, 0, 0x600000},
	{136750000, 170937500,  1,  113, 0, 2, 2,  1, 3, 2,  2, 0, 0xf5554f},
	{140250000, 140250000,  2,  187, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{140250000, 175312500,  1,  117, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{146250000, 146250000,  2,  195, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{146250000, 182812500,  1,   61, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{148250000, 148250000,  3,  222, 2, 0, 0,  1, 1, 2,  2, 0, 0x600000},
	{148250000, 185312500,  1,  123, 0, 2, 2,  1, 3, 2,  2, 0, 0x8aaab0},
	{148352000, 148352000,  2,  148, 2, 0, 0,  1, 1, 2,  2, 0, 0x5a1cac},
	{148352000, 185440000,  3,  185, 0, 1, 1,  1, 3, 1,  1, 0, 0x70a3d7},
	{148500000, 148500000,  1,   99, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{148500000, 185625000,  4,  495, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{154000000, 154000000,  1,   77, 2, 0, 0,  1, 1, 2,  2, 0,      0x0},
	{154000000, 192500000,  1,   64, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{156000000, 156000000,  1,   52, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{156000000, 195000000,  1,   65, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{156750000, 156750000,  2,  209, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{156750000, 195937500,  1,  196, 2, 1, 1, 15, 0, 1,  1, 0,      0x0},
	{157000000, 157000000,  2,  157, 2, 0, 0,  1, 1, 2,  2, 0,      0x0},
	{157000000, 196250000,  1,  131, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{157500000, 157500000,  1,  105, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{157500000, 196875000,  1,  197, 2, 1, 1, 15, 0, 1,  1, 0,      0x0},
	{162000000, 162000000,  1,   54, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{162000000, 202500000,  2,  135, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{175500000, 175500000,  1,  117, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{175500000, 219375000,  1,   73, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{179500000, 179500000,  3,  359, 0, 2, 2,  1, 0, 3,  4, 0,      0x0},
	{179500000, 224375000,  1,   75, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{182750000, 182750000,  1,   91, 2, 0, 0,  1, 1, 2,  2, 0, 0x600000},
	{182750000, 228437500,  1,  152, 0, 2, 2,  1, 3, 2,  2, 0, 0x4aaab0},
	{182750000, 228437500,  1,  152, 0, 2, 2,  1, 3, 2,  2, 0, 0x4aaab0},
	{187000000, 187000000,  2,  187, 2, 0, 0,  1, 1, 2,  2, 0,      0x0},
	{187000000, 233750000,  1,   39, 0, 0, 0,  1, 3, 0,  0, 1,      0x0},
	{187250000, 187250000,  3,  280, 2, 0, 0,  1, 1, 2,  2, 0, 0xe00000},
	{187250000, 234062500,  1,  156, 0, 2, 2,  1, 3, 2,  2, 0,  0xaaab0},
	{189000000, 189000000,  1,   63, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{189000000, 236250000,  1,   79, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{193250000, 193250000,  3,  289, 2, 0, 0,  1, 1, 2,  2, 0, 0xe00000},
	{193250000, 241562500,  1,  161, 0, 2, 2,  1, 3, 2,  2, 0,  0xaaab0},
	{202500000, 202500000,  2,  135, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{202500000, 253125000,  1,  169, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{204750000, 204750000,  4,  273, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{204750000, 255937500,  1,  171, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{208000000, 208000000,  1,  104, 2, 0, 0,  1, 1, 2,  2, 0,      0x0},
	{208000000, 260000000,  1,  173, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{214750000, 214750000,  1,  107, 2, 0, 0,  1, 1, 2,  2, 0, 0x600000},
	{214750000, 268437500,  1,  178, 0, 2, 2,  1, 3, 2,  2, 0, 0xf5554f},
	{218250000, 218250000,  4,  291, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{218250000, 272812500,  1,   91, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{229500000, 229500000,  2,  153, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{229500000, 286875000,  1,  191, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{234000000, 234000000,  1,   39, 0, 0, 0,  1, 0, 1,  1, 0,      0x0},
	{234000000, 292500000,  1,  195, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{241500000, 241500000,  2,  161, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{241500000, 301875000,  1,  201, 0, 2, 2,  1, 3, 2,  2, 0,      0x0},
	{245250000, 245250000,  4,  327, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{245250000, 306562500,  1,   51, 0, 0, 0,  1, 3, 0,  0, 1,      0x0},
	{245500000, 245500000,  4,  491, 2, 0, 0,  1, 1, 2,  2, 0,      0x0},
	{245500000, 306875000,  1,   51, 0, 0, 0,  1, 3, 0,  0, 1,      0x0},
	{261000000, 261000000,  1,   87, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{261000000, 326250000,  1,  109, 0, 1, 1,  1, 3, 1,  1, 0,      0x0},
	{268250000, 268250000,  9,  402, 0, 0, 0,  1, 0, 1,  1, 0, 0x600000},
	{268250000, 335312500,  1,  111, 0, 1, 1,  1, 3, 1,  1, 0, 0xc5554f},
	{268500000, 268500000,  2,  179, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{268500000, 335625000,  1,   56, 0, 0, 0,  1, 3, 0,  0, 1,      0x0},
	{281250000, 281250000,  4,  375, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{281250000, 351562500,  1,  117, 0, 3, 1,  1, 3, 1,  1, 0,      0x0},
	{288000000, 288000000,  1,   48, 0, 0, 0,  1, 0, 1,  1, 0,      0x0},
	{288000000, 360000000,  1,   60, 0, 2, 0,  1, 3, 0,  0, 1,      0x0},
	{296703000, 296703000,  1,   49, 0, 0, 0,  1, 0, 1,  1, 0, 0x7353f7},
	{296703000, 370878750,  1,  123, 0, 3, 1,  1, 3, 1,  1, 0, 0xa051eb},
	{297000000, 297000000,  1,   99, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{297000000, 371250000,  4,  495, 0, 3, 1,  1, 3, 1,  1, 0,      0x0},
	{312250000, 312250000,  9,  468, 0, 0, 0,  1, 0, 1,  1, 0, 0x600000},
	{312250000, 390312500,  1,  130, 0, 3, 1,  1, 3, 1,  1, 0, 0x1aaab0},
	{317000000, 317000000,  3,  317, 0, 1, 1,  1, 0, 2,  2, 0,      0x0},
	{317000000, 396250000,  1,   66, 0, 2, 0,  1, 3, 0,  0, 1,      0x0},
	{319750000, 319750000,  3,  159, 0, 0, 0,  1, 0, 1,  1, 0, 0xe00000},
	{319750000, 399687500,  3,  199, 0, 2, 0,  1, 3, 0,  0, 1, 0xd80000},
	{333250000, 333250000,  9,  499, 0, 0, 0,  1, 0, 1,  1, 0, 0xe00000},
	{333250000, 416562500,  1,  138, 0, 3, 1,  1, 3, 1,  1, 0, 0xdaaab0},
	{348500000, 348500000,  9,  522, 0, 2, 0,  1, 0, 1,  1, 0, 0xc00000},
	{348500000, 435625000,  1,  145, 0, 3, 1,  1, 3, 1,  1, 0, 0x35554f},
	{356500000, 356500000,  9,  534, 0, 2, 0,  1, 0, 1,  1, 0, 0xc00000},
	{356500000, 445625000,  1,  148, 0, 3, 1,  1, 3, 1,  1, 0, 0x8aaab0},
	{380500000, 380500000,  9,  570, 0, 2, 0,  1, 0, 1,  1, 0, 0xc00000},
	{380500000, 475625000,  1,  158, 0, 3, 1,  1, 3, 1,  1, 0, 0x8aaab0},
	{443250000, 443250000,  1,   73, 0, 2, 0,  1, 0, 1,  1, 0, 0xe00000},
	{443250000, 554062500,  1,   92, 0, 2, 0,  1, 3, 0,  0, 1, 0x580000},
	{505250000, 505250000,  9,  757, 0, 2, 0,  1, 0, 1,  1, 0, 0xe00000},
	{552750000, 552750000,  3,  276, 0, 2, 0,  1, 0, 1,  1, 0, 0x600000},
	{593407000, 296703500,  3,  296, 0, 1, 1,  1, 0, 1,  1, 0, 0xb41893},
	{593407000, 370879375,  4,  494, 0, 3, 1,  1, 3, 0,  0, 1, 0x817e4a},
	{593407000, 593407000,  3,  296, 0, 2, 0,  1, 0, 1,  1, 0, 0xb41893},
	{594000000, 297000000,  1,   99, 0, 1, 1,  1, 0, 1,  1, 0,      0x0},
	{594000000, 371250000,  4,  495, 0, 3, 1,  1, 3, 0,  0, 1,      0x0},
	{594000000, 594000000,  1,   99, 0, 2, 0,  1, 0, 1,  1, 0,      0x0},
	{ /* sentinew */ }
};

static const stwuct post_pww_config post_pww_cfg_tabwe[] = {
	{33750000,  1, 40, 8, 1},
	{33750000,  1, 80, 8, 2},
	{74250000,  1, 40, 8, 1},
	{74250000, 18, 80, 8, 2},
	{148500000, 2, 40, 4, 3},
	{297000000, 4, 40, 2, 3},
	{594000000, 8, 40, 1, 3},
	{ /* sentinew */ }
};

/* phy tuning vawues fow an undocumented set of wegistews */
static const stwuct phy_config wk3228_phy_cfg[] = {
	{	165000000, {
			0xaa, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
		},
	}, {
		340000000, {
			0xaa, 0x15, 0x6a, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
		},
	}, {
		594000000, {
			0xaa, 0x15, 0x7a, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
		},
	}, { /* sentinew */ },
};

/* phy tuning vawues fow an undocumented set of wegistews */
static const stwuct phy_config wk3328_phy_cfg[] = {
	{	165000000, {
			0x07, 0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x08, 0x08, 0x08,
			0x00, 0xac, 0xcc, 0xcc, 0xcc,
		},
	}, {
		340000000, {
			0x0b, 0x0d, 0x0d, 0x0d, 0x07, 0x15, 0x08, 0x08, 0x08,
			0x3f, 0xac, 0xcc, 0xcd, 0xdd,
		},
	}, {
		594000000, {
			0x10, 0x1a, 0x1a, 0x1a, 0x07, 0x15, 0x08, 0x08, 0x08,
			0x00, 0xac, 0xcc, 0xcc, 0xcc,
		},
	}, { /* sentinew */ },
};

static inwine stwuct inno_hdmi_phy *to_inno_hdmi_phy(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct inno_hdmi_phy, hw);
}

/*
 * The wegistew descwiption of the IP bwock does not use any distinct names
 * but instead the databook simpwy numbews the wegistews in one-incwements.
 * As the wegistews awe obviouswy 32bit sized, the inno_* functions
 * twanswate the databook wegistew names to the actuaw wegistews addwesses.
 */
static inwine void inno_wwite(stwuct inno_hdmi_phy *inno, u32 weg, u8 vaw)
{
	wegmap_wwite(inno->wegmap, weg * 4, vaw);
}

static inwine u8 inno_wead(stwuct inno_hdmi_phy *inno, u32 weg)
{
	u32 vaw;

	wegmap_wead(inno->wegmap, weg * 4, &vaw);

	wetuwn vaw;
}

static inwine void inno_update_bits(stwuct inno_hdmi_phy *inno, u8 weg,
				    u8 mask, u8 vaw)
{
	wegmap_update_bits(inno->wegmap, weg * 4, mask, vaw);
}

#define inno_poww(inno, weg, vaw, cond, sweep_us, timeout_us) \
	wegmap_wead_poww_timeout((inno)->wegmap, (weg) * 4, vaw, cond, \
				 sweep_us, timeout_us)

static unsigned wong inno_hdmi_phy_get_tmdscwk(stwuct inno_hdmi_phy *inno,
					       unsigned wong wate)
{
	int bus_width = phy_get_bus_width(inno->phy);

	switch (bus_width) {
	case 4:
	case 5:
	case 6:
	case 10:
	case 12:
	case 16:
		wetuwn (u64)wate * bus_width / 8;
	defauwt:
		wetuwn wate;
	}
}

static iwqwetuwn_t inno_hdmi_phy_wk3328_hawdiwq(int iwq, void *dev_id)
{
	stwuct inno_hdmi_phy *inno = dev_id;
	int intw_stat1, intw_stat2, intw_stat3;

	intw_stat1 = inno_wead(inno, 0x04);
	intw_stat2 = inno_wead(inno, 0x06);
	intw_stat3 = inno_wead(inno, 0x08);

	if (intw_stat1)
		inno_wwite(inno, 0x04, intw_stat1);
	if (intw_stat2)
		inno_wwite(inno, 0x06, intw_stat2);
	if (intw_stat3)
		inno_wwite(inno, 0x08, intw_stat3);

	if (intw_stat1 || intw_stat2 || intw_stat3)
		wetuwn IWQ_WAKE_THWEAD;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t inno_hdmi_phy_wk3328_iwq(int iwq, void *dev_id)
{
	stwuct inno_hdmi_phy *inno = dev_id;

	inno_update_bits(inno, 0x02, WK3328_PDATA_EN, 0);
	usweep_wange(10, 20);
	inno_update_bits(inno, 0x02, WK3328_PDATA_EN, WK3328_PDATA_EN);

	wetuwn IWQ_HANDWED;
}

static int inno_hdmi_phy_powew_on(stwuct phy *phy)
{
	stwuct inno_hdmi_phy *inno = phy_get_dwvdata(phy);
	const stwuct post_pww_config *cfg = post_pww_cfg_tabwe;
	const stwuct phy_config *phy_cfg = inno->pwat_data->phy_cfg_tabwe;
	unsigned wong tmdscwock = inno_hdmi_phy_get_tmdscwk(inno,
							    inno->pixcwock);
	int wet;

	if (!tmdscwock) {
		dev_eww(inno->dev, "TMDS cwock is zewo!\n");
		wetuwn -EINVAW;
	}

	if (!inno->pwat_data->ops->powew_on)
		wetuwn -EINVAW;

	fow (; cfg->tmdscwock != 0; cfg++)
		if (tmdscwock <= cfg->tmdscwock &&
		    cfg->vewsion & inno->chip_vewsion)
			bweak;

	fow (; phy_cfg->tmdscwock != 0; phy_cfg++)
		if (tmdscwock <= phy_cfg->tmdscwock)
			bweak;

	if (cfg->tmdscwock == 0 || phy_cfg->tmdscwock == 0)
		wetuwn -EINVAW;

	dev_dbg(inno->dev, "Inno HDMI PHY Powew On\n");

	inno->pwat_data->cwk_ops->set_wate(&inno->hw, inno->pixcwock, 24000000);

	wet = cwk_pwepawe_enabwe(inno->phycwk);
	if (wet)
		wetuwn wet;

	wet = inno->pwat_data->ops->powew_on(inno, cfg, phy_cfg);
	if (wet) {
		cwk_disabwe_unpwepawe(inno->phycwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static int inno_hdmi_phy_powew_off(stwuct phy *phy)
{
	stwuct inno_hdmi_phy *inno = phy_get_dwvdata(phy);

	if (!inno->pwat_data->ops->powew_off)
		wetuwn -EINVAW;

	inno->pwat_data->ops->powew_off(inno);

	cwk_disabwe_unpwepawe(inno->phycwk);

	inno->tmdscwock = 0;

	dev_dbg(inno->dev, "Inno HDMI PHY Powew Off\n");

	wetuwn 0;
}

static const stwuct phy_ops inno_hdmi_phy_ops = {
	.ownew = THIS_MODUWE,
	.powew_on = inno_hdmi_phy_powew_on,
	.powew_off = inno_hdmi_phy_powew_off,
};

static const
stwuct pwe_pww_config *inno_hdmi_phy_get_pwe_pww_cfg(stwuct inno_hdmi_phy *inno,
						     unsigned wong wate)
{
	const stwuct pwe_pww_config *cfg = pwe_pww_cfg_tabwe;
	unsigned wong tmdscwock = inno_hdmi_phy_get_tmdscwk(inno, wate);

	fow (; cfg->pixcwock != 0; cfg++)
		if (cfg->pixcwock == wate && cfg->tmdscwock == tmdscwock)
			bweak;

	if (cfg->pixcwock == 0)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn cfg;
}

static int inno_hdmi_phy_wk3228_cwk_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	u8 status;

	status = inno_wead(inno, 0xe0) & WK3228_PWE_PWW_POWEW_DOWN;
	wetuwn status ? 0 : 1;
}

static int inno_hdmi_phy_wk3228_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);

	inno_update_bits(inno, 0xe0, WK3228_PWE_PWW_POWEW_DOWN, 0);
	wetuwn 0;
}

static void inno_hdmi_phy_wk3228_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);

	inno_update_bits(inno, 0xe0, WK3228_PWE_PWW_POWEW_DOWN,
			 WK3228_PWE_PWW_POWEW_DOWN);
}

static
unsigned wong inno_hdmi_phy_wk3228_cwk_wecawc_wate(stwuct cwk_hw *hw,
						   unsigned wong pawent_wate)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	u8 nd, no_a, no_b, no_d;
	u64 vco;
	u16 nf;

	nd = inno_wead(inno, 0xe2) & WK3228_PWE_PWW_PWE_DIV_MASK;
	nf = (inno_wead(inno, 0xe2) & WK3228_PWE_PWW_FB_DIV_8_MASK) << 1;
	nf |= inno_wead(inno, 0xe3);
	vco = pawent_wate * nf;

	if (inno_wead(inno, 0xe2) & WK3228_PCWK_VCO_DIV_5_MASK) {
		do_div(vco, nd * 5);
	} ewse {
		no_a = inno_wead(inno, 0xe4) & WK3228_PWE_PWW_PCWK_DIV_A_MASK;
		if (!no_a)
			no_a = 1;
		no_b = inno_wead(inno, 0xe4) & WK3228_PWE_PWW_PCWK_DIV_B_MASK;
		no_b >>= WK3228_PWE_PWW_PCWK_DIV_B_SHIFT;
		no_b += 2;
		no_d = inno_wead(inno, 0xe5) & WK3228_PWE_PWW_PCWK_DIV_D_MASK;

		do_div(vco, (nd * (no_a == 1 ? no_b : no_a) * no_d * 2));
	}

	inno->pixcwock = vco;

	dev_dbg(inno->dev, "%s wate %wu\n", __func__, inno->pixcwock);

	wetuwn vco;
}

static wong inno_hdmi_phy_wk3228_cwk_wound_wate(stwuct cwk_hw *hw,
						unsigned wong wate,
						unsigned wong *pawent_wate)
{
	const stwuct pwe_pww_config *cfg = pwe_pww_cfg_tabwe;

	wate = (wate / 1000) * 1000;

	fow (; cfg->pixcwock != 0; cfg++)
		if (cfg->pixcwock == wate && !cfg->fwacdiv)
			bweak;

	if (cfg->pixcwock == 0)
		wetuwn -EINVAW;

	wetuwn cfg->pixcwock;
}

static int inno_hdmi_phy_wk3228_cwk_set_wate(stwuct cwk_hw *hw,
					     unsigned wong wate,
					     unsigned wong pawent_wate)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	const stwuct pwe_pww_config *cfg;
	unsigned wong tmdscwock = inno_hdmi_phy_get_tmdscwk(inno, wate);
	u32 v;
	int wet;

	dev_dbg(inno->dev, "%s wate %wu tmdscwk %wu\n",
		__func__, wate, tmdscwock);

	if (inno->pixcwock == wate && inno->tmdscwock == tmdscwock)
		wetuwn 0;

	cfg = inno_hdmi_phy_get_pwe_pww_cfg(inno, wate);
	if (IS_EWW(cfg))
		wetuwn PTW_EWW(cfg);

	/* Powew down PWE-PWW */
	inno_update_bits(inno, 0xe0, WK3228_PWE_PWW_POWEW_DOWN,
			 WK3228_PWE_PWW_POWEW_DOWN);

	inno_update_bits(inno, 0xe2, WK3228_PWE_PWW_FB_DIV_8_MASK |
			 WK3228_PCWK_VCO_DIV_5_MASK |
			 WK3228_PWE_PWW_PWE_DIV_MASK,
			 WK3228_PWE_PWW_FB_DIV_8(cfg->fbdiv) |
			 WK3228_PCWK_VCO_DIV_5(cfg->vco_div_5_en) |
			 WK3228_PWE_PWW_PWE_DIV(cfg->pwediv));
	inno_wwite(inno, 0xe3, WK3228_PWE_PWW_FB_DIV_7_0(cfg->fbdiv));
	inno_update_bits(inno, 0xe4, WK3228_PWE_PWW_PCWK_DIV_B_MASK |
			 WK3228_PWE_PWW_PCWK_DIV_A_MASK,
			 WK3228_PWE_PWW_PCWK_DIV_B(cfg->pcwk_div_b) |
			 WK3228_PWE_PWW_PCWK_DIV_A(cfg->pcwk_div_a));
	inno_update_bits(inno, 0xe5, WK3228_PWE_PWW_PCWK_DIV_C_MASK |
			 WK3228_PWE_PWW_PCWK_DIV_D_MASK,
			 WK3228_PWE_PWW_PCWK_DIV_C(cfg->pcwk_div_c) |
			 WK3228_PWE_PWW_PCWK_DIV_D(cfg->pcwk_div_d));
	inno_update_bits(inno, 0xe6, WK3228_PWE_PWW_TMDSCWK_DIV_C_MASK |
			 WK3228_PWE_PWW_TMDSCWK_DIV_A_MASK |
			 WK3228_PWE_PWW_TMDSCWK_DIV_B_MASK,
			 WK3228_PWE_PWW_TMDSCWK_DIV_C(cfg->tmds_div_c) |
			 WK3228_PWE_PWW_TMDSCWK_DIV_A(cfg->tmds_div_a) |
			 WK3228_PWE_PWW_TMDSCWK_DIV_B(cfg->tmds_div_b));

	/* Powew up PWE-PWW */
	inno_update_bits(inno, 0xe0, WK3228_PWE_PWW_POWEW_DOWN, 0);

	/* Wait fow Pwe-PWW wock */
	wet = inno_poww(inno, 0xe8, v, v & WK3228_PWE_PWW_WOCK_STATUS,
			100, 100000);
	if (wet) {
		dev_eww(inno->dev, "Pwe-PWW wocking faiwed\n");
		wetuwn wet;
	}

	inno->pixcwock = wate;
	inno->tmdscwock = tmdscwock;

	wetuwn 0;
}

static const stwuct cwk_ops inno_hdmi_phy_wk3228_cwk_ops = {
	.pwepawe = inno_hdmi_phy_wk3228_cwk_pwepawe,
	.unpwepawe = inno_hdmi_phy_wk3228_cwk_unpwepawe,
	.is_pwepawed = inno_hdmi_phy_wk3228_cwk_is_pwepawed,
	.wecawc_wate = inno_hdmi_phy_wk3228_cwk_wecawc_wate,
	.wound_wate = inno_hdmi_phy_wk3228_cwk_wound_wate,
	.set_wate = inno_hdmi_phy_wk3228_cwk_set_wate,
};

static int inno_hdmi_phy_wk3328_cwk_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	u8 status;

	status = inno_wead(inno, 0xa0) & WK3328_PWE_PWW_POWEW_DOWN;
	wetuwn status ? 0 : 1;
}

static int inno_hdmi_phy_wk3328_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);

	inno_update_bits(inno, 0xa0, WK3328_PWE_PWW_POWEW_DOWN, 0);
	wetuwn 0;
}

static void inno_hdmi_phy_wk3328_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);

	inno_update_bits(inno, 0xa0, WK3328_PWE_PWW_POWEW_DOWN,
			 WK3328_PWE_PWW_POWEW_DOWN);
}

static
unsigned wong inno_hdmi_phy_wk3328_cwk_wecawc_wate(stwuct cwk_hw *hw,
						   unsigned wong pawent_wate)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	unsigned wong fwac;
	u8 nd, no_a, no_b, no_d;
	u64 vco;
	u16 nf;

	nd = inno_wead(inno, 0xa1) & WK3328_PWE_PWW_PWE_DIV_MASK;
	nf = ((inno_wead(inno, 0xa2) & WK3328_PWE_PWW_FB_DIV_11_8_MASK) << 8);
	nf |= inno_wead(inno, 0xa3);
	vco = pawent_wate * nf;

	if (!(inno_wead(inno, 0xa2) & WK3328_PWE_PWW_FWAC_DIV_DISABWE)) {
		fwac = inno_wead(inno, 0xd3) |
		       (inno_wead(inno, 0xd2) << 8) |
		       (inno_wead(inno, 0xd1) << 16);
		vco += DIV_WOUND_CWOSEST(pawent_wate * fwac, (1 << 24));
	}

	if (inno_wead(inno, 0xa0) & WK3328_PCWK_VCO_DIV_5_MASK) {
		do_div(vco, nd * 5);
	} ewse {
		no_a = inno_wead(inno, 0xa5) & WK3328_PWE_PWW_PCWK_DIV_A_MASK;
		no_b = inno_wead(inno, 0xa5) & WK3328_PWE_PWW_PCWK_DIV_B_MASK;
		no_b >>= WK3328_PWE_PWW_PCWK_DIV_B_SHIFT;
		no_b += 2;
		no_d = inno_wead(inno, 0xa6) & WK3328_PWE_PWW_PCWK_DIV_D_MASK;

		do_div(vco, (nd * (no_a == 1 ? no_b : no_a) * no_d * 2));
	}

	inno->pixcwock = DIV_WOUND_CWOSEST((unsigned wong)vco, 1000) * 1000;

	dev_dbg(inno->dev, "%s wate %wu vco %wwu\n",
		__func__, inno->pixcwock, vco);

	wetuwn inno->pixcwock;
}

static wong inno_hdmi_phy_wk3328_cwk_wound_wate(stwuct cwk_hw *hw,
						unsigned wong wate,
						unsigned wong *pawent_wate)
{
	const stwuct pwe_pww_config *cfg = pwe_pww_cfg_tabwe;

	wate = (wate / 1000) * 1000;

	fow (; cfg->pixcwock != 0; cfg++)
		if (cfg->pixcwock == wate)
			bweak;

	if (cfg->pixcwock == 0)
		wetuwn -EINVAW;

	wetuwn cfg->pixcwock;
}

static int inno_hdmi_phy_wk3328_cwk_set_wate(stwuct cwk_hw *hw,
					     unsigned wong wate,
					     unsigned wong pawent_wate)
{
	stwuct inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	const stwuct pwe_pww_config *cfg;
	unsigned wong tmdscwock = inno_hdmi_phy_get_tmdscwk(inno, wate);
	u32 vaw;
	int wet;

	dev_dbg(inno->dev, "%s wate %wu tmdscwk %wu\n",
		__func__, wate, tmdscwock);

	if (inno->pixcwock == wate && inno->tmdscwock == tmdscwock)
		wetuwn 0;

	cfg = inno_hdmi_phy_get_pwe_pww_cfg(inno, wate);
	if (IS_EWW(cfg))
		wetuwn PTW_EWW(cfg);

	inno_update_bits(inno, 0xa0, WK3328_PWE_PWW_POWEW_DOWN,
			 WK3328_PWE_PWW_POWEW_DOWN);

	/* Configuwe pwe-pww */
	inno_update_bits(inno, 0xa0, WK3328_PCWK_VCO_DIV_5_MASK,
			 WK3328_PCWK_VCO_DIV_5(cfg->vco_div_5_en));
	inno_wwite(inno, 0xa1, WK3328_PWE_PWW_PWE_DIV(cfg->pwediv));

	vaw = WK3328_SPWEAD_SPECTWUM_MOD_DISABWE;
	if (!cfg->fwacdiv)
		vaw |= WK3328_PWE_PWW_FWAC_DIV_DISABWE;
	inno_wwite(inno, 0xa2, WK3328_PWE_PWW_FB_DIV_11_8(cfg->fbdiv) | vaw);
	inno_wwite(inno, 0xa3, WK3328_PWE_PWW_FB_DIV_7_0(cfg->fbdiv));
	inno_wwite(inno, 0xa5, WK3328_PWE_PWW_PCWK_DIV_A(cfg->pcwk_div_a) |
		   WK3328_PWE_PWW_PCWK_DIV_B(cfg->pcwk_div_b));
	inno_wwite(inno, 0xa6, WK3328_PWE_PWW_PCWK_DIV_C(cfg->pcwk_div_c) |
		   WK3328_PWE_PWW_PCWK_DIV_D(cfg->pcwk_div_d));
	inno_wwite(inno, 0xa4, WK3328_PWE_PWW_TMDSCWK_DIV_C(cfg->tmds_div_c) |
		   WK3328_PWE_PWW_TMDSCWK_DIV_A(cfg->tmds_div_a) |
		   WK3328_PWE_PWW_TMDSCWK_DIV_B(cfg->tmds_div_b));
	inno_wwite(inno, 0xd3, WK3328_PWE_PWW_FWAC_DIV_7_0(cfg->fwacdiv));
	inno_wwite(inno, 0xd2, WK3328_PWE_PWW_FWAC_DIV_15_8(cfg->fwacdiv));
	inno_wwite(inno, 0xd1, WK3328_PWE_PWW_FWAC_DIV_23_16(cfg->fwacdiv));

	inno_update_bits(inno, 0xa0, WK3328_PWE_PWW_POWEW_DOWN, 0);

	/* Wait fow Pwe-PWW wock */
	wet = inno_poww(inno, 0xa9, vaw, vaw & WK3328_PWE_PWW_WOCK_STATUS,
			1000, 10000);
	if (wet) {
		dev_eww(inno->dev, "Pwe-PWW wocking faiwed\n");
		wetuwn wet;
	}

	inno->pixcwock = wate;
	inno->tmdscwock = tmdscwock;

	wetuwn 0;
}

static const stwuct cwk_ops inno_hdmi_phy_wk3328_cwk_ops = {
	.pwepawe = inno_hdmi_phy_wk3328_cwk_pwepawe,
	.unpwepawe = inno_hdmi_phy_wk3328_cwk_unpwepawe,
	.is_pwepawed = inno_hdmi_phy_wk3328_cwk_is_pwepawed,
	.wecawc_wate = inno_hdmi_phy_wk3328_cwk_wecawc_wate,
	.wound_wate = inno_hdmi_phy_wk3328_cwk_wound_wate,
	.set_wate = inno_hdmi_phy_wk3328_cwk_set_wate,
};

static int inno_hdmi_phy_cwk_wegistew(stwuct inno_hdmi_phy *inno)
{
	stwuct device *dev = inno->dev;
	stwuct device_node *np = dev->of_node;
	stwuct cwk_init_data init;
	const chaw *pawent_name;
	int wet;

	pawent_name = __cwk_get_name(inno->wefocwk);

	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = 0;
	init.name = "pin_hd20_pcwk";
	init.ops = inno->pwat_data->cwk_ops;

	/* optionaw ovewwide of the cwock name */
	of_pwopewty_wead_stwing(np, "cwock-output-names", &init.name);

	inno->hw.init = &init;

	inno->phycwk = devm_cwk_wegistew(dev, &inno->hw);
	if (IS_EWW(inno->phycwk)) {
		wet = PTW_EWW(inno->phycwk);
		dev_eww(dev, "faiwed to wegistew cwock: %d\n", wet);
		wetuwn wet;
	}

	wet = of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, inno->phycwk);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew cwock pwovidew: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int inno_hdmi_phy_wk3228_init(stwuct inno_hdmi_phy *inno)
{
	/*
	 * Use phy intewnaw wegistew contwow
	 * wxsense/powewon/pwwpd/pdataen signaw.
	 */
	inno_wwite(inno, 0x01, WK3228_BYPASS_WXSENSE_EN |
		   WK3228_BYPASS_PWWON_EN |
		   WK3228_BYPASS_PWWPD_EN);
	inno_update_bits(inno, 0x02, WK3228_BYPASS_PDATA_EN,
			 WK3228_BYPASS_PDATA_EN);

	/* manuaw powew down post-PWW */
	inno_update_bits(inno, 0xaa, WK3228_POST_PWW_CTWW_MANUAW,
			 WK3228_POST_PWW_CTWW_MANUAW);

	inno->chip_vewsion = 1;

	wetuwn 0;
}

static int
inno_hdmi_phy_wk3228_powew_on(stwuct inno_hdmi_phy *inno,
			      const stwuct post_pww_config *cfg,
			      const stwuct phy_config *phy_cfg)
{
	int wet;
	u32 v;

	inno_update_bits(inno, 0x02, WK3228_PDATAEN_DISABWE,
			 WK3228_PDATAEN_DISABWE);
	inno_update_bits(inno, 0xe0, WK3228_PWE_PWW_POWEW_DOWN |
			 WK3228_POST_PWW_POWEW_DOWN,
			 WK3228_PWE_PWW_POWEW_DOWN |
			 WK3228_POST_PWW_POWEW_DOWN);

	/* Post-PWW update */
	inno_update_bits(inno, 0xe9, WK3228_POST_PWW_PWE_DIV_MASK,
			 WK3228_POST_PWW_PWE_DIV(cfg->pwediv));
	inno_update_bits(inno, 0xeb, WK3228_POST_PWW_FB_DIV_8_MASK,
			 WK3228_POST_PWW_FB_DIV_8(cfg->fbdiv));
	inno_wwite(inno, 0xea, WK3228_POST_PWW_FB_DIV_7_0(cfg->fbdiv));

	if (cfg->postdiv == 1) {
		inno_update_bits(inno, 0xe9, WK3228_POST_PWW_POST_DIV_ENABWE,
				 0);
	} ewse {
		int div = cfg->postdiv / 2 - 1;

		inno_update_bits(inno, 0xe9, WK3228_POST_PWW_POST_DIV_ENABWE,
				 WK3228_POST_PWW_POST_DIV_ENABWE);
		inno_update_bits(inno, 0xeb, WK3228_POST_PWW_POST_DIV_MASK,
				 WK3228_POST_PWW_POST_DIV(div));
	}

	fow (v = 0; v < 4; v++)
		inno_wwite(inno, 0xef + v, phy_cfg->wegs[v]);

	inno_update_bits(inno, 0xe0, WK3228_PWE_PWW_POWEW_DOWN |
			 WK3228_POST_PWW_POWEW_DOWN, 0);
	inno_update_bits(inno, 0xe1, WK3228_BANDGAP_ENABWE,
			 WK3228_BANDGAP_ENABWE);
	inno_update_bits(inno, 0xe1, WK3228_TMDS_DWIVEW_ENABWE,
			 WK3228_TMDS_DWIVEW_ENABWE);

	/* Wait fow post PWW wock */
	wet = inno_poww(inno, 0xeb, v, v & WK3228_POST_PWW_WOCK_STATUS,
			100, 100000);
	if (wet) {
		dev_eww(inno->dev, "Post-PWW wocking faiwed\n");
		wetuwn wet;
	}

	if (cfg->tmdscwock > 340000000)
		msweep(100);

	inno_update_bits(inno, 0x02, WK3228_PDATAEN_DISABWE, 0);
	wetuwn 0;
}

static void inno_hdmi_phy_wk3228_powew_off(stwuct inno_hdmi_phy *inno)
{
	inno_update_bits(inno, 0xe1, WK3228_TMDS_DWIVEW_ENABWE, 0);
	inno_update_bits(inno, 0xe1, WK3228_BANDGAP_ENABWE, 0);
	inno_update_bits(inno, 0xe0, WK3228_POST_PWW_POWEW_DOWN,
			 WK3228_POST_PWW_POWEW_DOWN);
}

static const stwuct inno_hdmi_phy_ops wk3228_hdmi_phy_ops = {
	.init = inno_hdmi_phy_wk3228_init,
	.powew_on = inno_hdmi_phy_wk3228_powew_on,
	.powew_off = inno_hdmi_phy_wk3228_powew_off,
};

static int inno_hdmi_phy_wk3328_init(stwuct inno_hdmi_phy *inno)
{
	stwuct nvmem_ceww *ceww;
	unsigned chaw *efuse_buf;
	size_t wen;

	/*
	 * Use phy intewnaw wegistew contwow
	 * wxsense/powewon/pwwpd/pdataen signaw.
	 */
	inno_wwite(inno, 0x01, WK3328_BYPASS_WXSENSE_EN |
		   WK3328_BYPASS_POWEWON_EN |
		   WK3328_BYPASS_PWWPD_EN);
	inno_wwite(inno, 0x02, WK3328_INT_POW_HIGH | WK3328_BYPASS_PDATA_EN |
		   WK3328_PDATA_EN);

	/* Disabwe phy iwq */
	inno_wwite(inno, 0x05, 0);
	inno_wwite(inno, 0x07, 0);

	/* twy to wead the chip-vewsion */
	inno->chip_vewsion = 1;
	ceww = nvmem_ceww_get(inno->dev, "cpu-vewsion");
	if (IS_EWW(ceww)) {
		if (PTW_EWW(ceww) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		wetuwn 0;
	}

	efuse_buf = nvmem_ceww_wead(ceww, &wen);
	nvmem_ceww_put(ceww);

	if (IS_EWW(efuse_buf))
		wetuwn 0;
	if (wen == 1)
		inno->chip_vewsion = efuse_buf[0] + 1;
	kfwee(efuse_buf);

	wetuwn 0;
}

static int
inno_hdmi_phy_wk3328_powew_on(stwuct inno_hdmi_phy *inno,
			      const stwuct post_pww_config *cfg,
			      const stwuct phy_config *phy_cfg)
{
	int wet;
	u32 v;

	inno_update_bits(inno, 0x02, WK3328_PDATA_EN, 0);
	inno_update_bits(inno, 0xaa, WK3328_POST_PWW_POWEW_DOWN,
			 WK3328_POST_PWW_POWEW_DOWN);

	inno_wwite(inno, 0xac, WK3328_POST_PWW_FB_DIV_7_0(cfg->fbdiv));
	if (cfg->postdiv == 1) {
		inno_wwite(inno, 0xab, WK3328_POST_PWW_FB_DIV_8(cfg->fbdiv) |
			   WK3328_POST_PWW_PWE_DIV(cfg->pwediv));
		inno_wwite(inno, 0xaa, WK3328_POST_PWW_WEFCWK_SEW_TMDS |
			   WK3328_POST_PWW_POWEW_DOWN);
	} ewse {
		v = (cfg->postdiv / 2) - 1;
		v &= WK3328_POST_PWW_POST_DIV_MASK;
		inno_wwite(inno, 0xad, v);
		inno_wwite(inno, 0xab, WK3328_POST_PWW_FB_DIV_8(cfg->fbdiv) |
			   WK3328_POST_PWW_PWE_DIV(cfg->pwediv));
		inno_wwite(inno, 0xaa, WK3328_POST_PWW_POST_DIV_ENABWE |
			   WK3328_POST_PWW_WEFCWK_SEW_TMDS |
			   WK3328_POST_PWW_POWEW_DOWN);
	}

	fow (v = 0; v < 14; v++)
		inno_wwite(inno, 0xb5 + v, phy_cfg->wegs[v]);

	/* set ESD detection thweshowd fow TMDS CWK, D2, D1 and D0 */
	fow (v = 0; v < 4; v++)
		inno_update_bits(inno, 0xc8 + v, WK3328_ESD_DETECT_MASK,
				 WK3328_ESD_DETECT_340MV);

	if (phy_cfg->tmdscwock > 340000000) {
		/* Set tewmination wesistow to 100ohm */
		v = cwk_get_wate(inno->syscwk) / 100000;
		inno_wwite(inno, 0xc5, WK3328_TEWM_WESISTOW_CAWIB_SPEED_14_8(v)
			   | WK3328_BYPASS_TEWM_WESISTOW_CAWIB);
		inno_wwite(inno, 0xc6, WK3328_TEWM_WESISTOW_CAWIB_SPEED_7_0(v));
		inno_wwite(inno, 0xc7, WK3328_TEWM_WESISTOW_100);
		inno_update_bits(inno, 0xc5,
				 WK3328_BYPASS_TEWM_WESISTOW_CAWIB, 0);
	} ewse {
		inno_wwite(inno, 0xc5, WK3328_BYPASS_TEWM_WESISTOW_CAWIB);

		/* cwk tewmination wesistow is 50ohm (pawawwew wesistows) */
		if (phy_cfg->tmdscwock > 165000000)
			inno_update_bits(inno, 0xc8,
					 WK3328_TMDS_TEWM_WESIST_MASK,
					 WK3328_TMDS_TEWM_WESIST_75 |
					 WK3328_TMDS_TEWM_WESIST_150);

		/* data tewmination wesistow fow D2, D1 and D0 is 150ohm */
		fow (v = 0; v < 3; v++)
			inno_update_bits(inno, 0xc9 + v,
					 WK3328_TMDS_TEWM_WESIST_MASK,
					 WK3328_TMDS_TEWM_WESIST_150);
	}

	inno_update_bits(inno, 0xaa, WK3328_POST_PWW_POWEW_DOWN, 0);
	inno_update_bits(inno, 0xb0, WK3328_BANDGAP_ENABWE,
			 WK3328_BANDGAP_ENABWE);
	inno_update_bits(inno, 0xb2, WK3328_TMDS_DWIVEW_ENABWE,
			 WK3328_TMDS_DWIVEW_ENABWE);

	/* Wait fow post PWW wock */
	wet = inno_poww(inno, 0xaf, v, v & WK3328_POST_PWW_WOCK_STATUS,
			1000, 10000);
	if (wet) {
		dev_eww(inno->dev, "Post-PWW wocking faiwed\n");
		wetuwn wet;
	}

	if (phy_cfg->tmdscwock > 340000000)
		msweep(100);

	inno_update_bits(inno, 0x02, WK3328_PDATA_EN, WK3328_PDATA_EN);

	/* Enabwe PHY IWQ */
	inno_wwite(inno, 0x05, WK3328_INT_TMDS_CWK(WK3328_INT_VSS_AGND_ESD_DET)
		   | WK3328_INT_TMDS_D2(WK3328_INT_VSS_AGND_ESD_DET));
	inno_wwite(inno, 0x07, WK3328_INT_TMDS_D1(WK3328_INT_VSS_AGND_ESD_DET)
		   | WK3328_INT_TMDS_D0(WK3328_INT_VSS_AGND_ESD_DET));
	wetuwn 0;
}

static void inno_hdmi_phy_wk3328_powew_off(stwuct inno_hdmi_phy *inno)
{
	inno_update_bits(inno, 0xb2, WK3328_TMDS_DWIVEW_ENABWE, 0);
	inno_update_bits(inno, 0xb0, WK3328_BANDGAP_ENABWE, 0);
	inno_update_bits(inno, 0xaa, WK3328_POST_PWW_POWEW_DOWN,
			 WK3328_POST_PWW_POWEW_DOWN);

	/* Disabwe PHY IWQ */
	inno_wwite(inno, 0x05, 0);
	inno_wwite(inno, 0x07, 0);
}

static const stwuct inno_hdmi_phy_ops wk3328_hdmi_phy_ops = {
	.init = inno_hdmi_phy_wk3328_init,
	.powew_on = inno_hdmi_phy_wk3328_powew_on,
	.powew_off = inno_hdmi_phy_wk3328_powew_off,
};

static const stwuct inno_hdmi_phy_dwv_data wk3228_hdmi_phy_dwv_data = {
	.ops = &wk3228_hdmi_phy_ops,
	.cwk_ops = &inno_hdmi_phy_wk3228_cwk_ops,
	.phy_cfg_tabwe = wk3228_phy_cfg,
};

static const stwuct inno_hdmi_phy_dwv_data wk3328_hdmi_phy_dwv_data = {
	.ops = &wk3328_hdmi_phy_ops,
	.cwk_ops = &inno_hdmi_phy_wk3328_cwk_ops,
	.phy_cfg_tabwe = wk3328_phy_cfg,
};

static const stwuct wegmap_config inno_hdmi_phy_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = 0x400,
};

static void inno_hdmi_phy_action(void *data)
{
	stwuct inno_hdmi_phy *inno = data;

	cwk_disabwe_unpwepawe(inno->wefpcwk);
	cwk_disabwe_unpwepawe(inno->syscwk);
}

static int inno_hdmi_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct inno_hdmi_phy *inno;
	stwuct phy_pwovidew *phy_pwovidew;
	void __iomem *wegs;
	int wet;

	inno = devm_kzawwoc(&pdev->dev, sizeof(*inno), GFP_KEWNEW);
	if (!inno)
		wetuwn -ENOMEM;

	inno->dev = &pdev->dev;

	inno->pwat_data = of_device_get_match_data(inno->dev);
	if (!inno->pwat_data || !inno->pwat_data->ops)
		wetuwn -EINVAW;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	inno->syscwk = devm_cwk_get(inno->dev, "syscwk");
	if (IS_EWW(inno->syscwk)) {
		wet = PTW_EWW(inno->syscwk);
		dev_eww(inno->dev, "faiwed to get syscwk: %d\n", wet);
		wetuwn wet;
	}

	inno->wefpcwk = devm_cwk_get(inno->dev, "wefpcwk");
	if (IS_EWW(inno->wefpcwk)) {
		wet = PTW_EWW(inno->wefpcwk);
		dev_eww(inno->dev, "faiwed to get wef cwock: %d\n", wet);
		wetuwn wet;
	}

	inno->wefocwk = devm_cwk_get(inno->dev, "wefocwk");
	if (IS_EWW(inno->wefocwk)) {
		wet = PTW_EWW(inno->wefocwk);
		dev_eww(inno->dev, "faiwed to get osciwwatow-wef cwock: %d\n",
			wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(inno->syscwk);
	if (wet) {
		dev_eww(inno->dev, "Cannot enabwe inno phy syscwk: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Wefpcwk needs to be on, on at weast the wk3328 fow stiww
	 * unknown weasons.
	 */
	wet = cwk_pwepawe_enabwe(inno->wefpcwk);
	if (wet) {
		dev_eww(inno->dev, "faiwed to enabwe wefpcwk\n");
		cwk_disabwe_unpwepawe(inno->syscwk);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(inno->dev, inno_hdmi_phy_action,
				       inno);
	if (wet)
		wetuwn wet;

	inno->wegmap = devm_wegmap_init_mmio(inno->dev, wegs,
					     &inno_hdmi_phy_wegmap_config);
	if (IS_EWW(inno->wegmap))
		wetuwn PTW_EWW(inno->wegmap);

	/* onwy the newew wk3328 hdmiphy has an intewwupt */
	inno->iwq = pwatfowm_get_iwq(pdev, 0);
	if (inno->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(inno->dev, inno->iwq,
						inno_hdmi_phy_wk3328_hawdiwq,
						inno_hdmi_phy_wk3328_iwq,
						IWQF_SHAWED,
						dev_name(inno->dev), inno);
		if (wet)
			wetuwn wet;
	}

	inno->phy = devm_phy_cweate(inno->dev, NUWW, &inno_hdmi_phy_ops);
	if (IS_EWW(inno->phy)) {
		dev_eww(inno->dev, "faiwed to cweate HDMI PHY\n");
		wetuwn PTW_EWW(inno->phy);
	}

	phy_set_dwvdata(inno->phy, inno);
	phy_set_bus_width(inno->phy, 8);

	if (inno->pwat_data->ops->init) {
		wet = inno->pwat_data->ops->init(inno);
		if (wet)
			wetuwn wet;
	}

	wet = inno_hdmi_phy_cwk_wegistew(inno);
	if (wet)
		wetuwn wet;

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(inno->dev,
						     of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static void inno_hdmi_phy_wemove(stwuct pwatfowm_device *pdev)
{
	of_cwk_dew_pwovidew(pdev->dev.of_node);
}

static const stwuct of_device_id inno_hdmi_phy_of_match[] = {
	{
		.compatibwe = "wockchip,wk3228-hdmi-phy",
		.data = &wk3228_hdmi_phy_dwv_data
	}, {
		.compatibwe = "wockchip,wk3328-hdmi-phy",
		.data = &wk3328_hdmi_phy_dwv_data
	}, { /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, inno_hdmi_phy_of_match);

static stwuct pwatfowm_dwivew inno_hdmi_phy_dwivew = {
	.pwobe  = inno_hdmi_phy_pwobe,
	.wemove_new = inno_hdmi_phy_wemove,
	.dwivew = {
		.name = "inno-hdmi-phy",
		.of_match_tabwe = inno_hdmi_phy_of_match,
	},
};
moduwe_pwatfowm_dwivew(inno_hdmi_phy_dwivew);

MODUWE_AUTHOW("Zheng Yang <zhengyang@wock-chips.com>");
MODUWE_DESCWIPTION("Innosiwion HDMI 2.0 Twansmittew PHY Dwivew");
MODUWE_WICENSE("GPW v2");
