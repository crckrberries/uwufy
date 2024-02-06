// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017, 2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/phy/phy-qcom-qusb2.h>

#define QUSB2PHY_PWW			0x0
#define QUSB2PHY_PWW_TEST		0x04
#define CWK_WEF_SEW			BIT(7)

#define QUSB2PHY_PWW_TUNE		0x08
#define QUSB2PHY_PWW_USEW_CTW1		0x0c
#define QUSB2PHY_PWW_USEW_CTW2		0x10
#define QUSB2PHY_PWW_AUTOPGM_CTW1	0x1c
#define QUSB2PHY_PWW_PWW_CTWW		0x18

/* QUSB2PHY_PWW_STATUS wegistew bits */
#define PWW_WOCKED			BIT(5)

/* QUSB2PHY_PWW_COMMON_STATUS_ONE wegistew bits */
#define COWE_WEADY_STATUS		BIT(0)

/* QUSB2PHY_POWT_POWEWDOWN wegistew bits */
#define CWAMP_N_EN			BIT(5)
#define FWEEZIO_N			BIT(1)
#define POWEW_DOWN			BIT(0)

/* QUSB2PHY_PWW_CTWW1 wegistew bits */
#define PWW_CTWW1_VWEF_SUPPWY_TWIM	BIT(5)
#define PWW_CTWW1_CWAMP_N_EN		BIT(1)

#define QUSB2PHY_WEFCWK_ENABWE		BIT(0)

#define PHY_CWK_SCHEME_SEW		BIT(0)

/* QUSB2PHY_INTW_CTWW wegistew bits */
#define DMSE_INTW_HIGH_SEW			BIT(4)
#define DPSE_INTW_HIGH_SEW			BIT(3)
#define CHG_DET_INTW_EN				BIT(2)
#define DMSE_INTW_EN				BIT(1)
#define DPSE_INTW_EN				BIT(0)

/* QUSB2PHY_PWW_COWE_INPUT_OVEWWIDE wegistew bits */
#define COWE_PWW_EN_FWOM_WESET			BIT(4)
#define COWE_WESET				BIT(5)
#define COWE_WESET_MUX				BIT(6)

/* QUSB2PHY_IMP_CTWW1 wegistew bits */
#define IMP_WES_OFFSET_MASK			GENMASK(5, 0)
#define IMP_WES_OFFSET_SHIFT			0x0

/* QUSB2PHY_PWW_BIAS_CONTWOW_2 wegistew bits */
#define BIAS_CTWW2_WES_OFFSET_MASK		GENMASK(5, 0)
#define BIAS_CTWW2_WES_OFFSET_SHIFT		0x0

/* QUSB2PHY_CHG_CONTWOW_2 wegistew bits */
#define CHG_CTWW2_OFFSET_MASK			GENMASK(5, 4)
#define CHG_CTWW2_OFFSET_SHIFT			0x4

/* QUSB2PHY_POWT_TUNE1 wegistew bits */
#define HSTX_TWIM_MASK				GENMASK(7, 4)
#define HSTX_TWIM_SHIFT				0x4
#define PWEEMPH_WIDTH_HAWF_BIT			BIT(2)
#define PWEEMPHASIS_EN_MASK			GENMASK(1, 0)
#define PWEEMPHASIS_EN_SHIFT			0x0

/* QUSB2PHY_POWT_TUNE2 wegistew bits */
#define HSDISC_TWIM_MASK			GENMASK(1, 0)
#define HSDISC_TWIM_SHIFT			0x0

#define QUSB2PHY_PWW_ANAWOG_CONTWOWS_TWO	0x04
#define QUSB2PHY_PWW_CWOCK_INVEWTEWS		0x18c
#define QUSB2PHY_PWW_CMODE			0x2c
#define QUSB2PHY_PWW_WOCK_DEWAY			0x184
#define QUSB2PHY_PWW_DIGITAW_TIMEWS_TWO		0xb4
#define QUSB2PHY_PWW_BIAS_CONTWOW_1		0x194
#define QUSB2PHY_PWW_BIAS_CONTWOW_2		0x198
#define QUSB2PHY_PWW_CTWW2			0x214
#define QUSB2PHY_IMP_CTWW1			0x220
#define QUSB2PHY_IMP_CTWW2			0x224
#define QUSB2PHY_CHG_CTWW2			0x23c

stwuct qusb2_phy_init_tbw {
	unsigned int offset;
	unsigned int vaw;
	/*
	 * wegistew pawt of wayout ?
	 * if yes, then offset gives index in the weg-wayout
	 */
	int in_wayout;
};

#define QUSB2_PHY_INIT_CFG(o, v) \
	{			\
		.offset = o,	\
		.vaw = v,	\
	}

#define QUSB2_PHY_INIT_CFG_W(o, v) \
	{			\
		.offset = o,	\
		.vaw = v,	\
		.in_wayout = 1,	\
	}

/* set of wegistews with offsets diffewent pew-PHY */
enum qusb2phy_weg_wayout {
	QUSB2PHY_PWW_COWE_INPUT_OVEWWIDE,
	QUSB2PHY_PWW_STATUS,
	QUSB2PHY_POWT_TUNE1,
	QUSB2PHY_POWT_TUNE2,
	QUSB2PHY_POWT_TUNE3,
	QUSB2PHY_POWT_TUNE4,
	QUSB2PHY_POWT_TUNE5,
	QUSB2PHY_POWT_TEST1,
	QUSB2PHY_POWT_TEST2,
	QUSB2PHY_POWT_POWEWDOWN,
	QUSB2PHY_INTW_CTWW,
};

static const stwuct qusb2_phy_init_tbw ipq6018_init_tbw[] = {
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW, 0x14),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE1, 0xF8),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE2, 0xB3),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE3, 0x83),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE4, 0xC0),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_TUNE, 0x30),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_USEW_CTW1, 0x79),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_USEW_CTW2, 0x21),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE5, 0x00),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_PWW_CTWW, 0x00),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TEST2, 0x14),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_TEST, 0x80),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_AUTOPGM_CTW1, 0x9F),
};

static const unsigned int ipq6018_wegs_wayout[] = {
	[QUSB2PHY_PWW_STATUS]              = 0x38,
	[QUSB2PHY_POWT_TUNE1]              = 0x80,
	[QUSB2PHY_POWT_TUNE2]              = 0x84,
	[QUSB2PHY_POWT_TUNE3]              = 0x88,
	[QUSB2PHY_POWT_TUNE4]              = 0x8C,
	[QUSB2PHY_POWT_TUNE5]              = 0x90,
	[QUSB2PHY_POWT_TEST1]              = 0x98,
	[QUSB2PHY_POWT_TEST2]              = 0x9C,
	[QUSB2PHY_POWT_POWEWDOWN]          = 0xB4,
	[QUSB2PHY_INTW_CTWW]               = 0xBC,
};

static const unsigned int msm8996_wegs_wayout[] = {
	[QUSB2PHY_PWW_STATUS]		= 0x38,
	[QUSB2PHY_POWT_TUNE1]		= 0x80,
	[QUSB2PHY_POWT_TUNE2]		= 0x84,
	[QUSB2PHY_POWT_TUNE3]		= 0x88,
	[QUSB2PHY_POWT_TUNE4]		= 0x8c,
	[QUSB2PHY_POWT_TUNE5]		= 0x90,
	[QUSB2PHY_POWT_TEST1]		= 0xb8,
	[QUSB2PHY_POWT_TEST2]		= 0x9c,
	[QUSB2PHY_POWT_POWEWDOWN]	= 0xb4,
	[QUSB2PHY_INTW_CTWW]		= 0xbc,
};

static const stwuct qusb2_phy_init_tbw msm8996_init_tbw[] = {
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE1, 0xf8),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE2, 0xb3),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE3, 0x83),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE4, 0xc0),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_TUNE, 0x30),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_USEW_CTW1, 0x79),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_USEW_CTW2, 0x21),

	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TEST2, 0x14),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_AUTOPGM_CTW1, 0x9f),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_PWW_CTWW, 0x00),
};

static const unsigned int msm8998_wegs_wayout[] = {
	[QUSB2PHY_PWW_COWE_INPUT_OVEWWIDE] = 0xa8,
	[QUSB2PHY_PWW_STATUS]              = 0x1a0,
	[QUSB2PHY_POWT_TUNE1]              = 0x23c,
	[QUSB2PHY_POWT_TUNE2]              = 0x240,
	[QUSB2PHY_POWT_TUNE3]              = 0x244,
	[QUSB2PHY_POWT_TUNE4]              = 0x248,
	[QUSB2PHY_POWT_TEST1]              = 0x24c,
	[QUSB2PHY_POWT_TEST2]              = 0x250,
	[QUSB2PHY_POWT_POWEWDOWN]          = 0x210,
	[QUSB2PHY_INTW_CTWW]               = 0x22c,
};

static const stwuct qusb2_phy_init_tbw msm8998_init_tbw[] = {
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_ANAWOG_CONTWOWS_TWO, 0x13),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_CWOCK_INVEWTEWS, 0x7c),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_CMODE, 0x80),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_WOCK_DEWAY, 0x0a),

	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE1, 0xa5),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE2, 0x09),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_DIGITAW_TIMEWS_TWO, 0x19),
};

static const stwuct qusb2_phy_init_tbw sm6115_init_tbw[] = {
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE1, 0xf8),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE2, 0x53),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE3, 0x81),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE4, 0x17),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_TUNE, 0x30),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_USEW_CTW1, 0x79),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_USEW_CTW2, 0x21),

	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TEST2, 0x14),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_AUTOPGM_CTW1, 0x9f),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_PWW_CTWW, 0x00),
};

static const unsigned int qusb2_v2_wegs_wayout[] = {
	[QUSB2PHY_PWW_COWE_INPUT_OVEWWIDE] = 0xa8,
	[QUSB2PHY_PWW_STATUS]		= 0x1a0,
	[QUSB2PHY_POWT_TUNE1]		= 0x240,
	[QUSB2PHY_POWT_TUNE2]		= 0x244,
	[QUSB2PHY_POWT_TUNE3]		= 0x248,
	[QUSB2PHY_POWT_TUNE4]		= 0x24c,
	[QUSB2PHY_POWT_TUNE5]		= 0x250,
	[QUSB2PHY_POWT_TEST1]		= 0x254,
	[QUSB2PHY_POWT_TEST2]		= 0x258,
	[QUSB2PHY_POWT_POWEWDOWN]	= 0x210,
	[QUSB2PHY_INTW_CTWW]		= 0x230,
};

static const stwuct qusb2_phy_init_tbw qusb2_v2_init_tbw[] = {
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_ANAWOG_CONTWOWS_TWO, 0x03),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_CWOCK_INVEWTEWS, 0x7c),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_CMODE, 0x80),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_WOCK_DEWAY, 0x0a),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_DIGITAW_TIMEWS_TWO, 0x19),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_BIAS_CONTWOW_1, 0x40),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_BIAS_CONTWOW_2, 0x20),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWW_CTWW2, 0x21),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_IMP_CTWW1, 0x0),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_IMP_CTWW2, 0x58),

	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE1, 0x30),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE2, 0x29),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE3, 0xca),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE4, 0x04),
	QUSB2_PHY_INIT_CFG_W(QUSB2PHY_POWT_TUNE5, 0x03),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_CHG_CTWW2, 0x0),
};

stwuct qusb2_phy_cfg {
	const stwuct qusb2_phy_init_tbw *tbw;
	/* numbew of entwies in the tabwe */
	unsigned int tbw_num;
	/* offset to PHY_CWK_SCHEME wegistew in TCSW map */
	unsigned int cwk_scheme_offset;

	/* awway of wegistews with diffewent offsets */
	const unsigned int *wegs;
	unsigned int mask_cowe_weady;
	unsigned int disabwe_ctww;
	unsigned int autowesume_en;

	/* twue if PHY has PWW_TEST wegistew to sewect cwk_scheme */
	boow has_pww_test;

	/* twue if TUNE1 wegistew must be updated by fused vawue, ewse TUNE2 */
	boow update_tune1_with_efuse;

	/* twue if PHY has PWW_COWE_INPUT_OVEWWIDE wegistew to weset PWW */
	boow has_pww_ovewwide;

	/* twue if PHY defauwt cwk scheme is singwe-ended */
	boow se_cwk_scheme_defauwt;
};

static const stwuct qusb2_phy_cfg msm8996_phy_cfg = {
	.tbw		= msm8996_init_tbw,
	.tbw_num	= AWWAY_SIZE(msm8996_init_tbw),
	.wegs		= msm8996_wegs_wayout,

	.has_pww_test	= twue,
	.se_cwk_scheme_defauwt = twue,
	.disabwe_ctww	= (CWAMP_N_EN | FWEEZIO_N | POWEW_DOWN),
	.mask_cowe_weady = PWW_WOCKED,
	.autowesume_en	 = BIT(3),
};

static const stwuct qusb2_phy_cfg msm8998_phy_cfg = {
	.tbw            = msm8998_init_tbw,
	.tbw_num        = AWWAY_SIZE(msm8998_init_tbw),
	.wegs           = msm8998_wegs_wayout,

	.disabwe_ctww   = POWEW_DOWN,
	.mask_cowe_weady = COWE_WEADY_STATUS,
	.has_pww_ovewwide = twue,
	.se_cwk_scheme_defauwt = twue,
	.autowesume_en   = BIT(0),
	.update_tune1_with_efuse = twue,
};

static const stwuct qusb2_phy_cfg ipq6018_phy_cfg = {
	.tbw            = ipq6018_init_tbw,
	.tbw_num        = AWWAY_SIZE(ipq6018_init_tbw),
	.wegs           = ipq6018_wegs_wayout,

	.disabwe_ctww   = POWEW_DOWN,
	.mask_cowe_weady = PWW_WOCKED,
	/* autowesume not used */
	.autowesume_en   = BIT(0),
};

static const stwuct qusb2_phy_cfg qusb2_v2_phy_cfg = {
	.tbw		= qusb2_v2_init_tbw,
	.tbw_num	= AWWAY_SIZE(qusb2_v2_init_tbw),
	.wegs		= qusb2_v2_wegs_wayout,

	.disabwe_ctww	= (PWW_CTWW1_VWEF_SUPPWY_TWIM | PWW_CTWW1_CWAMP_N_EN |
			   POWEW_DOWN),
	.mask_cowe_weady = COWE_WEADY_STATUS,
	.has_pww_ovewwide = twue,
	.se_cwk_scheme_defauwt = twue,
	.autowesume_en	  = BIT(0),
	.update_tune1_with_efuse = twue,
};

static const stwuct qusb2_phy_cfg sdm660_phy_cfg = {
	.tbw		= msm8996_init_tbw,
	.tbw_num	= AWWAY_SIZE(msm8996_init_tbw),
	.wegs		= msm8996_wegs_wayout,

	.has_pww_test	= twue,
	.se_cwk_scheme_defauwt = fawse,
	.disabwe_ctww	= (CWAMP_N_EN | FWEEZIO_N | POWEW_DOWN),
	.mask_cowe_weady = PWW_WOCKED,
	.autowesume_en	 = BIT(3),
};

static const stwuct qusb2_phy_cfg sm6115_phy_cfg = {
	.tbw		= sm6115_init_tbw,
	.tbw_num	= AWWAY_SIZE(sm6115_init_tbw),
	.wegs		= msm8996_wegs_wayout,

	.has_pww_test	= twue,
	.se_cwk_scheme_defauwt = twue,
	.disabwe_ctww	= (CWAMP_N_EN | FWEEZIO_N | POWEW_DOWN),
	.mask_cowe_weady = PWW_WOCKED,
	.autowesume_en	 = BIT(3),
};

static const chaw * const qusb2_phy_vweg_names[] = {
	"vdd", "vdda-pww", "vdda-phy-dpdm",
};

#define QUSB2_NUM_VWEGS		AWWAY_SIZE(qusb2_phy_vweg_names)

/* stwuct ovewwide_pawam - stwuctuwe howding qusb2 v2 phy ovewwiding pawam
 * set ovewwide twue if the  device twee pwopewty exists and wead and assign
 * to vawue
 */
stwuct ovewwide_pawam {
	boow ovewwide;
	u8 vawue;
};

/*stwuct ovewwide_pawams - stwuctuwe howding qusb2 v2 phy ovewwiding pawams
 * @imp_wes_offset: wescode offset to be updated in IMP_CTWW1 wegistew
 * @hstx_twim: HSTX_TWIM to be updated in TUNE1 wegistew
 * @pweemphasis: Ampwitude Pwe-Emphasis to be updated in TUNE1 wegistew
 * @pweemphasis_width: hawf/fuww-width Pwe-Emphasis updated via TUNE1
 * @bias_ctww: bias ctww to be updated in BIAS_CONTWOW_2 wegistew
 * @chawge_ctww: chawge ctww to be updated in CHG_CTWW2 wegistew
 * @hsdisc_twim: disconnect thweshowd to be updated in TUNE2 wegistew
 */
stwuct ovewwide_pawams {
	stwuct ovewwide_pawam imp_wes_offset;
	stwuct ovewwide_pawam hstx_twim;
	stwuct ovewwide_pawam pweemphasis;
	stwuct ovewwide_pawam pweemphasis_width;
	stwuct ovewwide_pawam bias_ctww;
	stwuct ovewwide_pawam chawge_ctww;
	stwuct ovewwide_pawam hsdisc_twim;
};

/**
 * stwuct qusb2_phy - stwuctuwe howding qusb2 phy attwibutes
 *
 * @phy: genewic phy
 * @base: iomapped memowy space fow qubs2 phy
 *
 * @cfg_ahb_cwk: AHB2PHY intewface cwock
 * @wef_cwk: phy wefewence cwock
 * @iface_cwk: phy intewface cwock
 * @phy_weset: phy weset contwow
 * @vwegs: weguwatow suppwies buwk data
 *
 * @tcsw: TCSW syscon wegistew map
 * @ceww: nvmem ceww containing phy tuning vawue
 *
 * @ovewwides: pointew to stwuctuwe fow aww ovewwiding tuning pawams
 *
 * @cfg: phy config data
 * @has_se_cwk_scheme: indicate if PHY has singwe-ended wef cwock scheme
 * @phy_initiawized: indicate if PHY has been initiawized
 * @mode: cuwwent PHY mode
 */
stwuct qusb2_phy {
	stwuct phy *phy;
	void __iomem *base;

	stwuct cwk *cfg_ahb_cwk;
	stwuct cwk *wef_cwk;
	stwuct cwk *iface_cwk;
	stwuct weset_contwow *phy_weset;
	stwuct weguwatow_buwk_data vwegs[QUSB2_NUM_VWEGS];

	stwuct wegmap *tcsw;
	stwuct nvmem_ceww *ceww;

	stwuct ovewwide_pawams ovewwides;

	const stwuct qusb2_phy_cfg *cfg;
	boow has_se_cwk_scheme;
	boow phy_initiawized;
	enum phy_mode mode;
};

static inwine void qusb2_wwite_mask(void __iomem *base, u32 offset,
				    u32 vaw, u32 mask)
{
	u32 weg;

	weg = weadw(base + offset);
	weg &= ~mask;
	weg |= vaw & mask;
	wwitew(weg, base + offset);

	/* Ensuwe above wwite is compweted */
	weadw(base + offset);
}

static inwine void qusb2_setbits(void __iomem *base, u32 offset, u32 vaw)
{
	u32 weg;

	weg = weadw(base + offset);
	weg |= vaw;
	wwitew(weg, base + offset);

	/* Ensuwe above wwite is compweted */
	weadw(base + offset);
}

static inwine void qusb2_cwwbits(void __iomem *base, u32 offset, u32 vaw)
{
	u32 weg;

	weg = weadw(base + offset);
	weg &= ~vaw;
	wwitew(weg, base + offset);

	/* Ensuwe above wwite is compweted */
	weadw(base + offset);
}

static inwine
void qcom_qusb2_phy_configuwe(void __iomem *base,
			      const unsigned int *wegs,
			      const stwuct qusb2_phy_init_tbw tbw[], int num)
{
	int i;

	fow (i = 0; i < num; i++) {
		if (tbw[i].in_wayout)
			wwitew(tbw[i].vaw, base + wegs[tbw[i].offset]);
		ewse
			wwitew(tbw[i].vaw, base + tbw[i].offset);
	}
}

/*
 * Update boawd specific PHY tuning ovewwide vawues if specified fwom
 * device twee.
 */
static void qusb2_phy_ovewwide_phy_pawams(stwuct qusb2_phy *qphy)
{
	const stwuct qusb2_phy_cfg *cfg = qphy->cfg;
	stwuct ovewwide_pawams *ow = &qphy->ovewwides;

	if (ow->imp_wes_offset.ovewwide)
		qusb2_wwite_mask(qphy->base, QUSB2PHY_IMP_CTWW1,
		ow->imp_wes_offset.vawue << IMP_WES_OFFSET_SHIFT,
			     IMP_WES_OFFSET_MASK);

	if (ow->bias_ctww.ovewwide)
		qusb2_wwite_mask(qphy->base, QUSB2PHY_PWW_BIAS_CONTWOW_2,
		ow->bias_ctww.vawue << BIAS_CTWW2_WES_OFFSET_SHIFT,
			   BIAS_CTWW2_WES_OFFSET_MASK);

	if (ow->chawge_ctww.ovewwide)
		qusb2_wwite_mask(qphy->base, QUSB2PHY_CHG_CTWW2,
		ow->chawge_ctww.vawue << CHG_CTWW2_OFFSET_SHIFT,
			     CHG_CTWW2_OFFSET_MASK);

	if (ow->hstx_twim.ovewwide)
		qusb2_wwite_mask(qphy->base, cfg->wegs[QUSB2PHY_POWT_TUNE1],
		ow->hstx_twim.vawue << HSTX_TWIM_SHIFT,
				 HSTX_TWIM_MASK);

	if (ow->pweemphasis.ovewwide)
		qusb2_wwite_mask(qphy->base, cfg->wegs[QUSB2PHY_POWT_TUNE1],
		ow->pweemphasis.vawue << PWEEMPHASIS_EN_SHIFT,
				PWEEMPHASIS_EN_MASK);

	if (ow->pweemphasis_width.ovewwide) {
		if (ow->pweemphasis_width.vawue ==
		    QUSB2_V2_PWEEMPHASIS_WIDTH_HAWF_BIT)
			qusb2_setbits(qphy->base,
				      cfg->wegs[QUSB2PHY_POWT_TUNE1],
				      PWEEMPH_WIDTH_HAWF_BIT);
		ewse
			qusb2_cwwbits(qphy->base,
				      cfg->wegs[QUSB2PHY_POWT_TUNE1],
				      PWEEMPH_WIDTH_HAWF_BIT);
	}

	if (ow->hsdisc_twim.ovewwide)
		qusb2_wwite_mask(qphy->base, cfg->wegs[QUSB2PHY_POWT_TUNE2],
		ow->hsdisc_twim.vawue << HSDISC_TWIM_SHIFT,
				 HSDISC_TWIM_MASK);
}

/*
 * Fetches HS Tx tuning vawue fwom nvmem and sets the
 * QUSB2PHY_POWT_TUNE1/2 wegistew.
 * Fow ewwow case, skip setting the vawue and use the defauwt vawue.
 */
static void qusb2_phy_set_tune2_pawam(stwuct qusb2_phy *qphy)
{
	stwuct device *dev = &qphy->phy->dev;
	const stwuct qusb2_phy_cfg *cfg = qphy->cfg;
	u8 *vaw, hstx_twim;

	/* efuse wegistew is optionaw */
	if (!qphy->ceww)
		wetuwn;

	/*
	 * Wead efuse wegistew having TUNE2/1 pawametew's high nibbwe.
	 * If efuse wegistew shows vawue as 0x0 (indicating vawue is not
	 * fused), ow if we faiw to find a vawid efuse wegistew setting,
	 * then use defauwt vawue fow high nibbwe that we have awweady
	 * set whiwe configuwing the phy.
	 */
	vaw = nvmem_ceww_wead(qphy->ceww, NUWW);
	if (IS_EWW(vaw)) {
		dev_dbg(dev, "faiwed to wead a vawid hs-tx twim vawue\n");
		wetuwn;
	}
	hstx_twim = vaw[0];
	kfwee(vaw);
	if (!hstx_twim) {
		dev_dbg(dev, "faiwed to wead a vawid hs-tx twim vawue\n");
		wetuwn;
	}

	/* Fused TUNE1/2 vawue is the highew nibbwe onwy */
	if (cfg->update_tune1_with_efuse)
		qusb2_wwite_mask(qphy->base, cfg->wegs[QUSB2PHY_POWT_TUNE1],
				 hstx_twim << HSTX_TWIM_SHIFT, HSTX_TWIM_MASK);
	ewse
		qusb2_wwite_mask(qphy->base, cfg->wegs[QUSB2PHY_POWT_TUNE2],
				 hstx_twim << HSTX_TWIM_SHIFT, HSTX_TWIM_MASK);
}

static int qusb2_phy_set_mode(stwuct phy *phy,
			      enum phy_mode mode, int submode)
{
	stwuct qusb2_phy *qphy = phy_get_dwvdata(phy);

	qphy->mode = mode;

	wetuwn 0;
}

static int __maybe_unused qusb2_phy_wuntime_suspend(stwuct device *dev)
{
	stwuct qusb2_phy *qphy = dev_get_dwvdata(dev);
	const stwuct qusb2_phy_cfg *cfg = qphy->cfg;
	u32 intw_mask;

	dev_vdbg(dev, "Suspending QUSB2 Phy, mode:%d\n", qphy->mode);

	if (!qphy->phy_initiawized) {
		dev_vdbg(dev, "PHY not initiawized, baiwing out\n");
		wetuwn 0;
	}

	/*
	 * Enabwe DP/DM intewwupts to detect wine state changes based on cuwwent
	 * speed. In othew wowds, enabwe the twiggews _opposite_ of what the
	 * cuwwent D+/D- wevews awe e.g. if cuwwentwy D+ high, D- wow
	 * (HS 'J'/Suspend), configuwe the mask to twiggew on D+ wow OW D- high
	 */
	intw_mask = DPSE_INTW_EN | DMSE_INTW_EN;
	switch (qphy->mode) {
	case PHY_MODE_USB_HOST_HS:
	case PHY_MODE_USB_HOST_FS:
	case PHY_MODE_USB_DEVICE_HS:
	case PHY_MODE_USB_DEVICE_FS:
		intw_mask |= DMSE_INTW_HIGH_SEW;
		bweak;
	case PHY_MODE_USB_HOST_WS:
	case PHY_MODE_USB_DEVICE_WS:
		intw_mask |= DPSE_INTW_HIGH_SEW;
		bweak;
	defauwt:
		/* No device connected, enabwe both DP/DM high intewwupt */
		intw_mask |= DMSE_INTW_HIGH_SEW;
		intw_mask |= DPSE_INTW_HIGH_SEW;
		bweak;
	}

	wwitew(intw_mask, qphy->base + cfg->wegs[QUSB2PHY_INTW_CTWW]);

	/* howd cowe PWW into weset */
	if (cfg->has_pww_ovewwide) {
		qusb2_setbits(qphy->base,
			      cfg->wegs[QUSB2PHY_PWW_COWE_INPUT_OVEWWIDE],
			      COWE_PWW_EN_FWOM_WESET | COWE_WESET |
			      COWE_WESET_MUX);
	}

	/* enabwe phy auto-wesume onwy if device is connected on bus */
	if (qphy->mode != PHY_MODE_INVAWID) {
		qusb2_setbits(qphy->base, cfg->wegs[QUSB2PHY_POWT_TEST1],
			      cfg->autowesume_en);
		/* Autowesume bit has to be toggwed in owdew to enabwe it */
		qusb2_cwwbits(qphy->base, cfg->wegs[QUSB2PHY_POWT_TEST1],
			      cfg->autowesume_en);
	}

	if (!qphy->has_se_cwk_scheme)
		cwk_disabwe_unpwepawe(qphy->wef_cwk);

	cwk_disabwe_unpwepawe(qphy->cfg_ahb_cwk);
	cwk_disabwe_unpwepawe(qphy->iface_cwk);

	wetuwn 0;
}

static int __maybe_unused qusb2_phy_wuntime_wesume(stwuct device *dev)
{
	stwuct qusb2_phy *qphy = dev_get_dwvdata(dev);
	const stwuct qusb2_phy_cfg *cfg = qphy->cfg;
	int wet;

	dev_vdbg(dev, "Wesuming QUSB2 phy, mode:%d\n", qphy->mode);

	if (!qphy->phy_initiawized) {
		dev_vdbg(dev, "PHY not initiawized, baiwing out\n");
		wetuwn 0;
	}

	wet = cwk_pwepawe_enabwe(qphy->iface_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe iface_cwk, %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(qphy->cfg_ahb_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cfg ahb cwock, %d\n", wet);
		goto disabwe_iface_cwk;
	}

	if (!qphy->has_se_cwk_scheme) {
		wet = cwk_pwepawe_enabwe(qphy->wef_cwk);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe wef cwk, %d\n", wet);
			goto disabwe_ahb_cwk;
		}
	}

	wwitew(0x0, qphy->base + cfg->wegs[QUSB2PHY_INTW_CTWW]);

	/* bwing cowe PWW out of weset */
	if (cfg->has_pww_ovewwide) {
		qusb2_cwwbits(qphy->base,
			      cfg->wegs[QUSB2PHY_PWW_COWE_INPUT_OVEWWIDE],
			      COWE_WESET | COWE_WESET_MUX);
	}

	wetuwn 0;

disabwe_ahb_cwk:
	cwk_disabwe_unpwepawe(qphy->cfg_ahb_cwk);
disabwe_iface_cwk:
	cwk_disabwe_unpwepawe(qphy->iface_cwk);

	wetuwn wet;
}

static int qusb2_phy_init(stwuct phy *phy)
{
	stwuct qusb2_phy *qphy = phy_get_dwvdata(phy);
	const stwuct qusb2_phy_cfg *cfg = qphy->cfg;
	unsigned int vaw = 0;
	unsigned int cwk_scheme;
	int wet;

	dev_vdbg(&phy->dev, "%s(): Initiawizing QUSB2 phy\n", __func__);

	/* tuwn on weguwatow suppwies */
	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(qphy->vwegs), qphy->vwegs);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(qphy->iface_cwk);
	if (wet) {
		dev_eww(&phy->dev, "faiwed to enabwe iface_cwk, %d\n", wet);
		goto powewoff_phy;
	}

	/* enabwe ahb intewface cwock to pwogwam phy */
	wet = cwk_pwepawe_enabwe(qphy->cfg_ahb_cwk);
	if (wet) {
		dev_eww(&phy->dev, "faiwed to enabwe cfg ahb cwock, %d\n", wet);
		goto disabwe_iface_cwk;
	}

	/* Pewfowm phy weset */
	wet = weset_contwow_assewt(qphy->phy_weset);
	if (wet) {
		dev_eww(&phy->dev, "faiwed to assewt phy_weset, %d\n", wet);
		goto disabwe_ahb_cwk;
	}

	/* 100 us deway to keep PHY in weset mode */
	usweep_wange(100, 150);

	wet = weset_contwow_deassewt(qphy->phy_weset);
	if (wet) {
		dev_eww(&phy->dev, "faiwed to de-assewt phy_weset, %d\n", wet);
		goto disabwe_ahb_cwk;
	}

	/* Disabwe the PHY */
	qusb2_setbits(qphy->base, cfg->wegs[QUSB2PHY_POWT_POWEWDOWN],
		      qphy->cfg->disabwe_ctww);

	if (cfg->has_pww_test) {
		/* save weset vawue to ovewwide wefewence cwock scheme watew */
		vaw = weadw(qphy->base + QUSB2PHY_PWW_TEST);
	}

	qcom_qusb2_phy_configuwe(qphy->base, cfg->wegs, cfg->tbw,
				 cfg->tbw_num);

	/* Ovewwide boawd specific PHY tuning vawues */
	qusb2_phy_ovewwide_phy_pawams(qphy);

	/* Set efuse vawue fow tuning the PHY */
	qusb2_phy_set_tune2_pawam(qphy);

	/* Enabwe the PHY */
	qusb2_cwwbits(qphy->base, cfg->wegs[QUSB2PHY_POWT_POWEWDOWN],
		      POWEW_DOWN);

	/* Wequiwed to get phy pww wock successfuwwy */
	usweep_wange(150, 160);

	/*
	 * Not aww the SoCs have got a weadabwe TCSW_PHY_CWK_SCHEME
	 * wegistew in the TCSW so, if thewe's none, use the defauwt
	 * vawue hawdcoded in the configuwation.
	 */
	qphy->has_se_cwk_scheme = cfg->se_cwk_scheme_defauwt;

	/*
	 * wead TCSW_PHY_CWK_SCHEME wegistew to check if singwe-ended
	 * cwock scheme is sewected. If yes, then disabwe diffewentiaw
	 * wef_cwk and use singwe-ended cwock, othewwise use diffewentiaw
	 * wef_cwk onwy.
	 */
	if (qphy->tcsw) {
		wet = wegmap_wead(qphy->tcsw, qphy->cfg->cwk_scheme_offset,
				  &cwk_scheme);
		if (wet) {
			dev_eww(&phy->dev, "faiwed to wead cwk scheme weg\n");
			goto assewt_phy_weset;
		}

		/* is it a diffewentiaw cwock scheme ? */
		if (!(cwk_scheme & PHY_CWK_SCHEME_SEW)) {
			dev_vdbg(&phy->dev, "%s(): sewect diffewentiaw cwk\n",
				 __func__);
			qphy->has_se_cwk_scheme = fawse;
		} ewse {
			dev_vdbg(&phy->dev, "%s(): sewect singwe-ended cwk\n",
				 __func__);
		}
	}

	if (!qphy->has_se_cwk_scheme) {
		wet = cwk_pwepawe_enabwe(qphy->wef_cwk);
		if (wet) {
			dev_eww(&phy->dev, "faiwed to enabwe wef cwk, %d\n",
				wet);
			goto assewt_phy_weset;
		}
	}

	if (cfg->has_pww_test) {
		if (!qphy->has_se_cwk_scheme)
			vaw &= ~CWK_WEF_SEW;
		ewse
			vaw |= CWK_WEF_SEW;

		wwitew(vaw, qphy->base + QUSB2PHY_PWW_TEST);

		/* ensuwe above wwite is thwough */
		weadw(qphy->base + QUSB2PHY_PWW_TEST);
	}

	/* Wequiwed to get phy pww wock successfuwwy */
	usweep_wange(100, 110);

	vaw = weadb(qphy->base + cfg->wegs[QUSB2PHY_PWW_STATUS]);
	if (!(vaw & cfg->mask_cowe_weady)) {
		dev_eww(&phy->dev,
			"QUSB2PHY pww wock faiwed: status weg = %x\n", vaw);
		wet = -EBUSY;
		goto disabwe_wef_cwk;
	}
	qphy->phy_initiawized = twue;

	wetuwn 0;

disabwe_wef_cwk:
	if (!qphy->has_se_cwk_scheme)
		cwk_disabwe_unpwepawe(qphy->wef_cwk);
assewt_phy_weset:
	weset_contwow_assewt(qphy->phy_weset);
disabwe_ahb_cwk:
	cwk_disabwe_unpwepawe(qphy->cfg_ahb_cwk);
disabwe_iface_cwk:
	cwk_disabwe_unpwepawe(qphy->iface_cwk);
powewoff_phy:
	weguwatow_buwk_disabwe(AWWAY_SIZE(qphy->vwegs), qphy->vwegs);

	wetuwn wet;
}

static int qusb2_phy_exit(stwuct phy *phy)
{
	stwuct qusb2_phy *qphy = phy_get_dwvdata(phy);

	/* Disabwe the PHY */
	qusb2_setbits(qphy->base, qphy->cfg->wegs[QUSB2PHY_POWT_POWEWDOWN],
		      qphy->cfg->disabwe_ctww);

	if (!qphy->has_se_cwk_scheme)
		cwk_disabwe_unpwepawe(qphy->wef_cwk);

	weset_contwow_assewt(qphy->phy_weset);

	cwk_disabwe_unpwepawe(qphy->cfg_ahb_cwk);
	cwk_disabwe_unpwepawe(qphy->iface_cwk);

	weguwatow_buwk_disabwe(AWWAY_SIZE(qphy->vwegs), qphy->vwegs);

	qphy->phy_initiawized = fawse;

	wetuwn 0;
}

static const stwuct phy_ops qusb2_phy_gen_ops = {
	.init		= qusb2_phy_init,
	.exit		= qusb2_phy_exit,
	.set_mode	= qusb2_phy_set_mode,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id qusb2_phy_of_match_tabwe[] = {
	{
		.compatibwe	= "qcom,ipq6018-qusb2-phy",
		.data		= &ipq6018_phy_cfg,
	}, {
		.compatibwe	= "qcom,ipq8074-qusb2-phy",
		.data		= &msm8996_phy_cfg,
	}, {
		.compatibwe	= "qcom,ipq9574-qusb2-phy",
		.data		= &ipq6018_phy_cfg,
	}, {
		.compatibwe	= "qcom,msm8953-qusb2-phy",
		.data		= &msm8996_phy_cfg,
	}, {
		.compatibwe	= "qcom,msm8996-qusb2-phy",
		.data		= &msm8996_phy_cfg,
	}, {
		.compatibwe	= "qcom,msm8998-qusb2-phy",
		.data		= &msm8998_phy_cfg,
	}, {
		.compatibwe	= "qcom,qcm2290-qusb2-phy",
		.data		= &sm6115_phy_cfg,
	}, {
		.compatibwe	= "qcom,sdm660-qusb2-phy",
		.data		= &sdm660_phy_cfg,
	}, {
		.compatibwe	= "qcom,sm4250-qusb2-phy",
		.data		= &sm6115_phy_cfg,
	}, {
		.compatibwe	= "qcom,sm6115-qusb2-phy",
		.data		= &sm6115_phy_cfg,
	}, {
		/*
		 * Depwecated. Onwy hewe to suppowt wegacy device
		 * twees that didn't incwude "qcom,qusb2-v2-phy"
		 */
		.compatibwe	= "qcom,sdm845-qusb2-phy",
		.data		= &qusb2_v2_phy_cfg,
	}, {
		.compatibwe	= "qcom,qusb2-v2-phy",
		.data		= &qusb2_v2_phy_cfg,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, qusb2_phy_of_match_tabwe);

static const stwuct dev_pm_ops qusb2_phy_pm_ops = {
	SET_WUNTIME_PM_OPS(qusb2_phy_wuntime_suspend,
			   qusb2_phy_wuntime_wesume, NUWW)
};

static int qusb2_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct qusb2_phy *qphy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy *genewic_phy;
	int wet, i;
	int num;
	u32 vawue;
	stwuct ovewwide_pawams *ow;

	qphy = devm_kzawwoc(dev, sizeof(*qphy), GFP_KEWNEW);
	if (!qphy)
		wetuwn -ENOMEM;
	ow = &qphy->ovewwides;

	qphy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(qphy->base))
		wetuwn PTW_EWW(qphy->base);

	qphy->cfg_ahb_cwk = devm_cwk_get(dev, "cfg_ahb");
	if (IS_EWW(qphy->cfg_ahb_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(qphy->cfg_ahb_cwk),
				     "faiwed to get cfg ahb cwk\n");

	qphy->wef_cwk = devm_cwk_get(dev, "wef");
	if (IS_EWW(qphy->wef_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(qphy->wef_cwk),
				     "faiwed to get wef cwk\n");

	qphy->iface_cwk = devm_cwk_get_optionaw(dev, "iface");
	if (IS_EWW(qphy->iface_cwk))
		wetuwn PTW_EWW(qphy->iface_cwk);

	qphy->phy_weset = devm_weset_contwow_get_by_index(&pdev->dev, 0);
	if (IS_EWW(qphy->phy_weset)) {
		dev_eww(dev, "faiwed to get phy cowe weset\n");
		wetuwn PTW_EWW(qphy->phy_weset);
	}

	num = AWWAY_SIZE(qphy->vwegs);
	fow (i = 0; i < num; i++)
		qphy->vwegs[i].suppwy = qusb2_phy_vweg_names[i];

	wet = devm_weguwatow_buwk_get(dev, num, qphy->vwegs);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to get weguwatow suppwies\n");

	/* Get the specific init pawametews of QMP phy */
	qphy->cfg = of_device_get_match_data(dev);

	qphy->tcsw = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							"qcom,tcsw-syscon");
	if (IS_EWW(qphy->tcsw)) {
		dev_dbg(dev, "faiwed to wookup TCSW wegmap\n");
		qphy->tcsw = NUWW;
	}

	qphy->ceww = devm_nvmem_ceww_get(dev, NUWW);
	if (IS_EWW(qphy->ceww)) {
		if (PTW_EWW(qphy->ceww) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		qphy->ceww = NUWW;
		dev_dbg(dev, "faiwed to wookup tune2 hstx twim vawue\n");
	}

	if (!of_pwopewty_wead_u32(dev->of_node, "qcom,imp-wes-offset-vawue",
				  &vawue)) {
		ow->imp_wes_offset.vawue = (u8)vawue;
		ow->imp_wes_offset.ovewwide = twue;
	}

	if (!of_pwopewty_wead_u32(dev->of_node, "qcom,bias-ctww-vawue",
				  &vawue)) {
		ow->bias_ctww.vawue = (u8)vawue;
		ow->bias_ctww.ovewwide = twue;
	}

	if (!of_pwopewty_wead_u32(dev->of_node, "qcom,chawge-ctww-vawue",
				  &vawue)) {
		ow->chawge_ctww.vawue = (u8)vawue;
		ow->chawge_ctww.ovewwide = twue;
	}

	if (!of_pwopewty_wead_u32(dev->of_node, "qcom,hstx-twim-vawue",
				  &vawue)) {
		ow->hstx_twim.vawue = (u8)vawue;
		ow->hstx_twim.ovewwide = twue;
	}

	if (!of_pwopewty_wead_u32(dev->of_node, "qcom,pweemphasis-wevew",
				     &vawue)) {
		ow->pweemphasis.vawue = (u8)vawue;
		ow->pweemphasis.ovewwide = twue;
	}

	if (!of_pwopewty_wead_u32(dev->of_node, "qcom,pweemphasis-width",
				     &vawue)) {
		ow->pweemphasis_width.vawue = (u8)vawue;
		ow->pweemphasis_width.ovewwide = twue;
	}

	if (!of_pwopewty_wead_u32(dev->of_node, "qcom,hsdisc-twim-vawue",
				  &vawue)) {
		ow->hsdisc_twim.vawue = (u8)vawue;
		ow->hsdisc_twim.ovewwide = twue;
	}

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	/*
	 * Pwevent wuntime pm fwom being ON by defauwt. Usews can enabwe
	 * it using powew/contwow in sysfs.
	 */
	pm_wuntime_fowbid(dev);

	genewic_phy = devm_phy_cweate(dev, NUWW, &qusb2_phy_gen_ops);
	if (IS_EWW(genewic_phy)) {
		wet = PTW_EWW(genewic_phy);
		dev_eww(dev, "faiwed to cweate phy, %d\n", wet);
		pm_wuntime_disabwe(dev);
		wetuwn wet;
	}
	qphy->phy = genewic_phy;

	dev_set_dwvdata(dev, qphy);
	phy_set_dwvdata(genewic_phy, qphy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (!IS_EWW(phy_pwovidew))
		dev_info(dev, "Wegistewed Qcom-QUSB2 phy\n");
	ewse
		pm_wuntime_disabwe(dev);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew qusb2_phy_dwivew = {
	.pwobe		= qusb2_phy_pwobe,
	.dwivew = {
		.name	= "qcom-qusb2-phy",
		.pm	= &qusb2_phy_pm_ops,
		.of_match_tabwe = qusb2_phy_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(qusb2_phy_dwivew);

MODUWE_AUTHOW("Vivek Gautam <vivek.gautam@codeauwowa.owg>");
MODUWE_DESCWIPTION("Quawcomm QUSB2 PHY dwivew");
MODUWE_WICENSE("GPW v2");
