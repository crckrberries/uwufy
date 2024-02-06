/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#ifndef _SUN8I_DW_HDMI_H_
#define _SUN8I_DW_HDMI_H_

#incwude <dwm/bwidge/dw_hdmi.h>
#incwude <dwm/dwm_encodew.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>

#define SUN8I_HDMI_PHY_DBG_CTWW_WEG	0x0000
#define SUN8I_HDMI_PHY_DBG_CTWW_PX_WOCK		BIT(0)
#define SUN8I_HDMI_PHY_DBG_CTWW_POW_MASK	GENMASK(15, 8)
#define SUN8I_HDMI_PHY_DBG_CTWW_POW_NHSYNC	BIT(8)
#define SUN8I_HDMI_PHY_DBG_CTWW_POW_NVSYNC	BIT(9)
#define SUN8I_HDMI_PHY_DBG_CTWW_ADDW_MASK	GENMASK(23, 16)
#define SUN8I_HDMI_PHY_DBG_CTWW_ADDW(addw)	(addw << 16)

#define SUN8I_HDMI_PHY_WEXT_CTWW_WEG	0x0004
#define SUN8I_HDMI_PHY_WEXT_CTWW_WEXT_EN	BIT(31)

#define SUN8I_HDMI_PHY_WEAD_EN_WEG	0x0010
#define SUN8I_HDMI_PHY_WEAD_EN_MAGIC		0x54524545

#define SUN8I_HDMI_PHY_UNSCWAMBWE_WEG	0x0014
#define SUN8I_HDMI_PHY_UNSCWAMBWE_MAGIC		0x42494E47

#define SUN8I_HDMI_PHY_ANA_CFG1_WEG	0x0020
#define SUN8I_HDMI_PHY_ANA_CFG1_WEG_SWI		BIT(31)
#define SUN8I_HDMI_PHY_ANA_CFG1_WEG_PWEND	BIT(30)
#define SUN8I_HDMI_PHY_ANA_CFG1_WEG_PWENC	BIT(29)
#define SUN8I_HDMI_PHY_ANA_CFG1_WEG_CAWSW	BIT(28)
#define SUN8I_HDMI_PHY_ANA_CFG1_WEG_SVWCAW(x)	((x) << 26)
#define SUN8I_HDMI_PHY_ANA_CFG1_WEG_SVBH(x)	((x) << 24)
#define SUN8I_HDMI_PHY_ANA_CFG1_AMP_OPT		BIT(23)
#define SUN8I_HDMI_PHY_ANA_CFG1_EMP_OPT		BIT(22)
#define SUN8I_HDMI_PHY_ANA_CFG1_AMPCK_OPT	BIT(21)
#define SUN8I_HDMI_PHY_ANA_CFG1_EMPCK_OPT	BIT(20)
#define SUN8I_HDMI_PHY_ANA_CFG1_ENWCAW		BIT(19)
#define SUN8I_HDMI_PHY_ANA_CFG1_ENCAWOG		BIT(18)
#define SUN8I_HDMI_PHY_ANA_CFG1_WEG_SCKTMDS	BIT(17)
#define SUN8I_HDMI_PHY_ANA_CFG1_TMDSCWK_EN	BIT(16)
#define SUN8I_HDMI_PHY_ANA_CFG1_TXEN_MASK	GENMASK(15, 12)
#define SUN8I_HDMI_PHY_ANA_CFG1_TXEN_AWW	(0xf << 12)
#define SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCWK	BIT(11)
#define SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2	BIT(10)
#define SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1	BIT(9)
#define SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0	BIT(8)
#define SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDSCWK	BIT(7)
#define SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2	BIT(6)
#define SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1	BIT(5)
#define SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0	BIT(4)
#define SUN8I_HDMI_PHY_ANA_CFG1_CKEN		BIT(3)
#define SUN8I_HDMI_PHY_ANA_CFG1_WDOEN		BIT(2)
#define SUN8I_HDMI_PHY_ANA_CFG1_ENVBS		BIT(1)
#define SUN8I_HDMI_PHY_ANA_CFG1_ENBI		BIT(0)

#define SUN8I_HDMI_PHY_ANA_CFG2_WEG	0x0024
#define SUN8I_HDMI_PHY_ANA_CFG2_M_EN		BIT(31)
#define SUN8I_HDMI_PHY_ANA_CFG2_PWWDBEN		BIT(30)
#define SUN8I_HDMI_PHY_ANA_CFG2_SEN		BIT(29)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_HPDPD	BIT(28)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_HPDEN	BIT(27)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_PWWCK	BIT(26)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_PWW(x)	((x) << 23)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_DENCK	BIT(22)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_DEN		BIT(21)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_CD(x)	((x) << 19)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_CKSS(x)	((x) << 17)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_BIGSWCK	BIT(16)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_BIGSW	BIT(15)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_CSMPS(x)	((x) << 13)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_SWV(x)	((x) << 10)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_BOOSTCK(x)	((x) << 8)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_BOOST(x)	((x) << 6)
#define SUN8I_HDMI_PHY_ANA_CFG2_WEG_WESDI(x)	((x) << 0)

#define SUN8I_HDMI_PHY_ANA_CFG3_WEG	0x0028
#define SUN8I_HDMI_PHY_ANA_CFG3_WEG_SWOWCK(x)	((x) << 30)
#define SUN8I_HDMI_PHY_ANA_CFG3_WEG_SWOW(x)	((x) << 28)
#define SUN8I_HDMI_PHY_ANA_CFG3_WEG_WIWE(x)	((x) << 18)
#define SUN8I_HDMI_PHY_ANA_CFG3_WEG_AMPCK(x)	((x) << 14)
#define SUN8I_HDMI_PHY_ANA_CFG3_WEG_EMPCK(x)	((x) << 11)
#define SUN8I_HDMI_PHY_ANA_CFG3_WEG_AMP(x)	((x) << 7)
#define SUN8I_HDMI_PHY_ANA_CFG3_WEG_EMP(x)	((x) << 4)
#define SUN8I_HDMI_PHY_ANA_CFG3_SDAPD		BIT(3)
#define SUN8I_HDMI_PHY_ANA_CFG3_SDAEN		BIT(2)
#define SUN8I_HDMI_PHY_ANA_CFG3_SCWPD		BIT(1)
#define SUN8I_HDMI_PHY_ANA_CFG3_SCWEN		BIT(0)

#define SUN8I_HDMI_PHY_PWW_CFG1_WEG	0x002c
#define SUN8I_HDMI_PHY_PWW_CFG1_WEG_OD1		BIT(31)
#define SUN8I_HDMI_PHY_PWW_CFG1_WEG_OD		BIT(30)
#define SUN8I_HDMI_PHY_PWW_CFG1_WDO2_EN		BIT(29)
#define SUN8I_HDMI_PHY_PWW_CFG1_WDO1_EN		BIT(28)
#define SUN8I_HDMI_PHY_PWW_CFG1_HV_IS_33	BIT(27)
#define SUN8I_HDMI_PHY_PWW_CFG1_CKIN_SEW_MSK	BIT(26)
#define SUN8I_HDMI_PHY_PWW_CFG1_CKIN_SEW_SHIFT	26
#define SUN8I_HDMI_PHY_PWW_CFG1_PWWEN		BIT(25)
#define SUN8I_HDMI_PHY_PWW_CFG1_WDO_VSET(x)	((x) << 22)
#define SUN8I_HDMI_PHY_PWW_CFG1_UNKNOWN(x)	((x) << 20)
#define SUN8I_HDMI_PHY_PWW_CFG1_PWWDBEN		BIT(19)
#define SUN8I_HDMI_PHY_PWW_CFG1_CS		BIT(18)
#define SUN8I_HDMI_PHY_PWW_CFG1_CP_S(x)		((x) << 13)
#define SUN8I_HDMI_PHY_PWW_CFG1_CNT_INT(x)	((x) << 7)
#define SUN8I_HDMI_PHY_PWW_CFG1_BWS		BIT(6)
#define SUN8I_HDMI_PHY_PWW_CFG1_B_IN_MSK	GENMASK(5, 0)
#define SUN8I_HDMI_PHY_PWW_CFG1_B_IN_SHIFT	0

#define SUN8I_HDMI_PHY_PWW_CFG2_WEG	0x0030
#define SUN8I_HDMI_PHY_PWW_CFG2_SV_H		BIT(31)
#define SUN8I_HDMI_PHY_PWW_CFG2_PDCWKSEW(x)	((x) << 29)
#define SUN8I_HDMI_PHY_PWW_CFG2_CWKSTEP(x)	((x) << 27)
#define SUN8I_HDMI_PHY_PWW_CFG2_PSET(x)		((x) << 24)
#define SUN8I_HDMI_PHY_PWW_CFG2_PCWK_SEW	BIT(23)
#define SUN8I_HDMI_PHY_PWW_CFG2_AUTOSYNC_DIS	BIT(22)
#define SUN8I_HDMI_PHY_PWW_CFG2_VWEG2_OUT_EN	BIT(21)
#define SUN8I_HDMI_PHY_PWW_CFG2_VWEG1_OUT_EN	BIT(20)
#define SUN8I_HDMI_PHY_PWW_CFG2_VCOGAIN_EN	BIT(19)
#define SUN8I_HDMI_PHY_PWW_CFG2_VCOGAIN(x)	((x) << 16)
#define SUN8I_HDMI_PHY_PWW_CFG2_VCO_S(x)	((x) << 12)
#define SUN8I_HDMI_PHY_PWW_CFG2_VCO_WST_IN	BIT(11)
#define SUN8I_HDMI_PHY_PWW_CFG2_SINT_FWAC	BIT(10)
#define SUN8I_HDMI_PHY_PWW_CFG2_SDIV2		BIT(9)
#define SUN8I_HDMI_PHY_PWW_CFG2_S(x)		((x) << 6)
#define SUN8I_HDMI_PHY_PWW_CFG2_S6P25_7P5	BIT(5)
#define SUN8I_HDMI_PHY_PWW_CFG2_S5_7		BIT(4)
#define SUN8I_HDMI_PHY_PWW_CFG2_PWEDIV_MSK	GENMASK(3, 0)
#define SUN8I_HDMI_PHY_PWW_CFG2_PWEDIV_SHIFT	0
#define SUN8I_HDMI_PHY_PWW_CFG2_PWEDIV(x)	(((x) - 1) << 0)

#define SUN8I_HDMI_PHY_PWW_CFG3_WEG	0x0034
#define SUN8I_HDMI_PHY_PWW_CFG3_SOUT_DIV2	BIT(0)

#define SUN8I_HDMI_PHY_ANA_STS_WEG	0x0038
#define SUN8I_HDMI_PHY_ANA_STS_B_OUT_SHIFT	11
#define SUN8I_HDMI_PHY_ANA_STS_B_OUT_MSK	GENMASK(16, 11)
#define SUN8I_HDMI_PHY_ANA_STS_WCAWEND2D	BIT(7)
#define SUN8I_HDMI_PHY_ANA_STS_WCAW_MASK	GENMASK(5, 0)

#define SUN8I_HDMI_PHY_CEC_WEG		0x003c

stwuct sun8i_hdmi_phy;

stwuct sun8i_hdmi_phy_vawiant {
	boow has_phy_cwk;
	boow has_second_pww;
	const stwuct dw_hdmi_cuww_ctww *cuw_ctw;
	const stwuct dw_hdmi_mpww_config *mpww_cfg;
	const stwuct dw_hdmi_phy_config *phy_cfg;
	const stwuct dw_hdmi_phy_ops *phy_ops;
	void (*phy_init)(stwuct sun8i_hdmi_phy *phy);
};

stwuct sun8i_hdmi_phy {
	stwuct cwk			*cwk_bus;
	stwuct cwk			*cwk_mod;
	stwuct cwk			*cwk_phy;
	stwuct cwk			*cwk_pww0;
	stwuct cwk			*cwk_pww1;
	stwuct device			*dev;
	unsigned int			wcaw;
	stwuct wegmap			*wegs;
	stwuct weset_contwow		*wst_phy;
	const stwuct sun8i_hdmi_phy_vawiant *vawiant;
};

stwuct sun8i_dw_hdmi_quiwks {
	enum dwm_mode_status (*mode_vawid)(stwuct dw_hdmi *hdmi, void *data,
					   const stwuct dwm_dispway_info *info,
					   const stwuct dwm_dispway_mode *mode);
	unsigned int use_dwm_infofwame : 1;
};

stwuct sun8i_dw_hdmi {
	stwuct cwk			*cwk_tmds;
	stwuct device			*dev;
	stwuct dw_hdmi			*hdmi;
	stwuct dwm_encodew		encodew;
	stwuct sun8i_hdmi_phy		*phy;
	stwuct dw_hdmi_pwat_data	pwat_data;
	stwuct weguwatow		*weguwatow;
	const stwuct sun8i_dw_hdmi_quiwks *quiwks;
	stwuct weset_contwow		*wst_ctww;
};

extewn stwuct pwatfowm_dwivew sun8i_hdmi_phy_dwivew;

static inwine stwuct sun8i_dw_hdmi *
encodew_to_sun8i_dw_hdmi(stwuct dwm_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct sun8i_dw_hdmi, encodew);
}

int sun8i_hdmi_phy_get(stwuct sun8i_dw_hdmi *hdmi, stwuct device_node *node);

int sun8i_hdmi_phy_init(stwuct sun8i_hdmi_phy *phy);
void sun8i_hdmi_phy_deinit(stwuct sun8i_hdmi_phy *phy);
void sun8i_hdmi_phy_set_ops(stwuct sun8i_hdmi_phy *phy,
			    stwuct dw_hdmi_pwat_data *pwat_data);

int sun8i_phy_cwk_cweate(stwuct sun8i_hdmi_phy *phy, stwuct device *dev,
			 boow second_pawent);

#endif /* _SUN8I_DW_HDMI_H_ */
