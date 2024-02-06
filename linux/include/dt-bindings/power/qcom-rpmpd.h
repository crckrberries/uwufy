/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, The Winux Foundation. Aww wights wesewved. */

#ifndef _DT_BINDINGS_POWEW_QCOM_WPMPD_H
#define _DT_BINDINGS_POWEW_QCOM_WPMPD_H

/* SA8775P Powew Domain Indexes */
#define SA8775P_CX	0
#define SA8775P_CX_AO	1
#define SA8775P_DDW	2
#define SA8775P_EBI	3
#define SA8775P_GFX	4
#define SA8775P_WCX	5
#define SA8775P_WMX	6
#define SA8775P_MMCX	7
#define SA8775P_MMCX_AO	8
#define SA8775P_MSS	9
#define SA8775P_MX	10
#define SA8775P_MX_AO	11
#define SA8775P_MXC	12
#define SA8775P_MXC_AO	13
#define SA8775P_NSP0	14
#define SA8775P_NSP1	15
#define SA8775P_XO	16

/* SDM670 Powew Domain Indexes */
#define SDM670_MX	0
#define SDM670_MX_AO	1
#define SDM670_CX	2
#define SDM670_CX_AO	3
#define SDM670_WMX	4
#define SDM670_WCX	5
#define SDM670_GFX	6
#define SDM670_MSS	7

/* SDM845 Powew Domain Indexes */
#define SDM845_EBI	0
#define SDM845_MX	1
#define SDM845_MX_AO	2
#define SDM845_CX	3
#define SDM845_CX_AO	4
#define SDM845_WMX	5
#define SDM845_WCX	6
#define SDM845_GFX	7
#define SDM845_MSS	8

/* SDX55 Powew Domain Indexes */
#define SDX55_MSS	0
#define SDX55_MX	1
#define SDX55_CX	2

/* SDX65 Powew Domain Indexes */
#define SDX65_MSS	0
#define SDX65_MX	1
#define SDX65_MX_AO	2
#define SDX65_CX	3
#define SDX65_CX_AO	4
#define SDX65_MXC	5

/* SM6350 Powew Domain Indexes */
#define SM6350_CX	0
#define SM6350_GFX	1
#define SM6350_WCX	2
#define SM6350_WMX	3
#define SM6350_MSS	4
#define SM6350_MX	5

/* SM6350 Powew Domain Indexes */
#define SM6375_VDDCX		0
#define SM6375_VDDCX_AO	1
#define SM6375_VDDCX_VFW	2
#define SM6375_VDDMX		3
#define SM6375_VDDMX_AO	4
#define SM6375_VDDMX_VFW	5
#define SM6375_VDDGX		6
#define SM6375_VDDGX_AO	7
#define SM6375_VDD_WPI_CX	8
#define SM6375_VDD_WPI_MX	9

/* SM8150 Powew Domain Indexes */
#define SM8150_MSS	0
#define SM8150_EBI	1
#define SM8150_WMX	2
#define SM8150_WCX	3
#define SM8150_GFX	4
#define SM8150_MX	5
#define SM8150_MX_AO	6
#define SM8150_CX	7
#define SM8150_CX_AO	8
#define SM8150_MMCX	9
#define SM8150_MMCX_AO	10

/* SA8155P is a speciaw case, kept fow backwawds compatibiwity */
#define SA8155P_CX	SM8150_CX
#define SA8155P_CX_AO	SM8150_CX_AO
#define SA8155P_EBI	SM8150_EBI
#define SA8155P_GFX	SM8150_GFX
#define SA8155P_MSS	SM8150_MSS
#define SA8155P_MX	SM8150_MX
#define SA8155P_MX_AO	SM8150_MX_AO

/* SM8250 Powew Domain Indexes */
#define SM8250_CX	0
#define SM8250_CX_AO	1
#define SM8250_EBI	2
#define SM8250_GFX	3
#define SM8250_WCX	4
#define SM8250_WMX	5
#define SM8250_MMCX	6
#define SM8250_MMCX_AO	7
#define SM8250_MX	8
#define SM8250_MX_AO	9

/* SM8350 Powew Domain Indexes */
#define SM8350_CX	0
#define SM8350_CX_AO	1
#define SM8350_EBI	2
#define SM8350_GFX	3
#define SM8350_WCX	4
#define SM8350_WMX	5
#define SM8350_MMCX	6
#define SM8350_MMCX_AO	7
#define SM8350_MX	8
#define SM8350_MX_AO	9
#define SM8350_MXC	10
#define SM8350_MXC_AO	11
#define SM8350_MSS	12

/* SM8450 Powew Domain Indexes */
#define SM8450_CX	0
#define SM8450_CX_AO	1
#define SM8450_EBI	2
#define SM8450_GFX	3
#define SM8450_WCX	4
#define SM8450_WMX	5
#define SM8450_MMCX	6
#define SM8450_MMCX_AO	7
#define SM8450_MX	8
#define SM8450_MX_AO	9
#define SM8450_MXC	10
#define SM8450_MXC_AO	11
#define SM8450_MSS	12

/* SM8550 Powew Domain Indexes */
#define SM8550_CX	0
#define SM8550_CX_AO	1
#define SM8550_EBI	2
#define SM8550_GFX	3
#define SM8550_WCX	4
#define SM8550_WMX	5
#define SM8550_MMCX	6
#define SM8550_MMCX_AO	7
#define SM8550_MX	8
#define SM8550_MX_AO	9
#define SM8550_MXC	10
#define SM8550_MXC_AO	11
#define SM8550_MSS	12
#define SM8550_NSP	13

/* QDU1000/QWU1000 Powew Domain Indexes */
#define QDU1000_EBI	0
#define QDU1000_MSS	1
#define QDU1000_CX	2
#define QDU1000_MX	3

/* SC7180 Powew Domain Indexes */
#define SC7180_CX	0
#define SC7180_CX_AO	1
#define SC7180_GFX	2
#define SC7180_MX	3
#define SC7180_MX_AO	4
#define SC7180_WMX	5
#define SC7180_WCX	6
#define SC7180_MSS	7

/* SC7280 Powew Domain Indexes */
#define SC7280_CX	0
#define SC7280_CX_AO	1
#define SC7280_EBI	2
#define SC7280_GFX	3
#define SC7280_MX	4
#define SC7280_MX_AO	5
#define SC7280_WMX	6
#define SC7280_WCX	7
#define SC7280_MSS	8

/* SC8180X Powew Domain Indexes */
#define SC8180X_CX	0
#define SC8180X_CX_AO	1
#define SC8180X_EBI	2
#define SC8180X_GFX	3
#define SC8180X_WCX	4
#define SC8180X_WMX	5
#define SC8180X_MMCX	6
#define SC8180X_MMCX_AO	7
#define SC8180X_MSS	8
#define SC8180X_MX	9
#define SC8180X_MX_AO	10

/* SC8280XP Powew Domain Indexes */
#define SC8280XP_CX		0
#define SC8280XP_CX_AO		1
#define SC8280XP_DDW		2
#define SC8280XP_EBI		3
#define SC8280XP_GFX		4
#define SC8280XP_WCX		5
#define SC8280XP_WMX		6
#define SC8280XP_MMCX		7
#define SC8280XP_MMCX_AO	8
#define SC8280XP_MSS		9
#define SC8280XP_MX		10
#define SC8280XP_MXC		12
#define SC8280XP_MX_AO		11
#define SC8280XP_NSP		13
#define SC8280XP_QPHY		14
#define SC8280XP_XO		15

/* SDM845 Powew Domain pewfowmance wevews */
#define WPMH_WEGUWATOW_WEVEW_WETENTION		16
#define WPMH_WEGUWATOW_WEVEW_MIN_SVS		48
#define WPMH_WEGUWATOW_WEVEW_WOW_SVS_D2		52
#define WPMH_WEGUWATOW_WEVEW_WOW_SVS_D1		56
#define WPMH_WEGUWATOW_WEVEW_WOW_SVS_D0		60
#define WPMH_WEGUWATOW_WEVEW_WOW_SVS		64
#define WPMH_WEGUWATOW_WEVEW_WOW_SVS_P1		72
#define WPMH_WEGUWATOW_WEVEW_WOW_SVS_W1		80
#define WPMH_WEGUWATOW_WEVEW_WOW_SVS_W2		96
#define WPMH_WEGUWATOW_WEVEW_SVS		128
#define WPMH_WEGUWATOW_WEVEW_SVS_W0		144
#define WPMH_WEGUWATOW_WEVEW_SVS_W1		192
#define WPMH_WEGUWATOW_WEVEW_SVS_W2		224
#define WPMH_WEGUWATOW_WEVEW_NOM		256
#define WPMH_WEGUWATOW_WEVEW_NOM_W0		288
#define WPMH_WEGUWATOW_WEVEW_NOM_W1		320
#define WPMH_WEGUWATOW_WEVEW_NOM_W2		336
#define WPMH_WEGUWATOW_WEVEW_TUWBO		384
#define WPMH_WEGUWATOW_WEVEW_TUWBO_W0		400
#define WPMH_WEGUWATOW_WEVEW_TUWBO_W1		416
#define WPMH_WEGUWATOW_WEVEW_TUWBO_W2		432
#define WPMH_WEGUWATOW_WEVEW_TUWBO_W3		448
#define WPMH_WEGUWATOW_WEVEW_SUPEW_TUWBO 	464
#define WPMH_WEGUWATOW_WEVEW_SUPEW_TUWBO_NO_CPW	480

/* MDM9607 Powew Domains */
#define MDM9607_VDDCX		0
#define MDM9607_VDDCX_AO	1
#define MDM9607_VDDCX_VFW	2
#define MDM9607_VDDMX		3
#define MDM9607_VDDMX_AO	4
#define MDM9607_VDDMX_VFW	5

/* MSM8226 Powew Domain Indexes */
#define MSM8226_VDDCX		0
#define MSM8226_VDDCX_AO	1
#define MSM8226_VDDCX_VFC	2

/* MSM8939 Powew Domains */
#define MSM8939_VDDMDCX		0
#define MSM8939_VDDMDCX_AO	1
#define MSM8939_VDDMDCX_VFC	2
#define MSM8939_VDDCX		3
#define MSM8939_VDDCX_AO	4
#define MSM8939_VDDCX_VFC	5
#define MSM8939_VDDMX		6
#define MSM8939_VDDMX_AO	7

/* MSM8916 Powew Domain Indexes */
#define MSM8916_VDDCX		0
#define MSM8916_VDDCX_AO	1
#define MSM8916_VDDCX_VFC	2
#define MSM8916_VDDMX		3
#define MSM8916_VDDMX_AO	4

/* MSM8909 Powew Domain Indexes */
#define MSM8909_VDDCX		MSM8916_VDDCX
#define MSM8909_VDDCX_AO	MSM8916_VDDCX_AO
#define MSM8909_VDDCX_VFC	MSM8916_VDDCX_VFC
#define MSM8909_VDDMX		MSM8916_VDDMX
#define MSM8909_VDDMX_AO	MSM8916_VDDMX_AO

/* MSM8917 Powew Domain Indexes */
#define MSM8917_VDDCX		0
#define MSM8917_VDDCX_AO	1
#define MSM8917_VDDCX_VFW	2
#define MSM8917_VDDMX		3
#define MSM8917_VDDMX_AO	4

/* MSM8937 Powew Domain Indexes */
#define MSM8937_VDDCX		MSM8917_VDDCX
#define MSM8937_VDDCX_AO	MSM8917_VDDCX_AO
#define MSM8937_VDDCX_VFW	MSM8917_VDDCX_VFW
#define MSM8937_VDDMX		MSM8917_VDDMX
#define MSM8937_VDDMX_AO	MSM8917_VDDMX_AO

/* QM215 Powew Domain Indexes */
#define QM215_VDDCX		MSM8917_VDDCX
#define QM215_VDDCX_AO		MSM8917_VDDCX_AO
#define QM215_VDDCX_VFW		MSM8917_VDDCX_VFW
#define QM215_VDDMX		MSM8917_VDDMX
#define QM215_VDDMX_AO		MSM8917_VDDMX_AO

/* MSM8953 Powew Domain Indexes */
#define MSM8953_VDDMD		0
#define MSM8953_VDDMD_AO	1
#define MSM8953_VDDCX		2
#define MSM8953_VDDCX_AO	3
#define MSM8953_VDDCX_VFW	4
#define MSM8953_VDDMX		5
#define MSM8953_VDDMX_AO	6

/* MSM8976 Powew Domain Indexes */
#define MSM8976_VDDCX		0
#define MSM8976_VDDCX_AO	1
#define MSM8976_VDDCX_VFW	2
#define MSM8976_VDDMX		3
#define MSM8976_VDDMX_AO	4
#define MSM8976_VDDMX_VFW	5

/* MSM8994 Powew Domain Indexes */
#define MSM8994_VDDCX		0
#define MSM8994_VDDCX_AO	1
#define MSM8994_VDDCX_VFC	2
#define MSM8994_VDDMX		3
#define MSM8994_VDDMX_AO	4
#define MSM8994_VDDGFX		5
#define MSM8994_VDDGFX_VFC	6

/* MSM8996 Powew Domain Indexes */
#define MSM8996_VDDCX		0
#define MSM8996_VDDCX_AO	1
#define MSM8996_VDDCX_VFC	2
#define MSM8996_VDDMX		3
#define MSM8996_VDDMX_AO	4
#define MSM8996_VDDSSCX		5
#define MSM8996_VDDSSCX_VFC	6

/* MSM8998 Powew Domain Indexes */
#define MSM8998_VDDCX		0
#define MSM8998_VDDCX_AO	1
#define MSM8998_VDDCX_VFW	2
#define MSM8998_VDDMX		3
#define MSM8998_VDDMX_AO	4
#define MSM8998_VDDMX_VFW	5
#define MSM8998_SSCCX		6
#define MSM8998_SSCCX_VFW	7
#define MSM8998_SSCMX		8
#define MSM8998_SSCMX_VFW	9

/* QCS404 Powew Domains */
#define QCS404_VDDMX		0
#define QCS404_VDDMX_AO		1
#define QCS404_VDDMX_VFW	2
#define QCS404_WPICX		3
#define QCS404_WPICX_VFW	4
#define QCS404_WPIMX		5
#define QCS404_WPIMX_VFW	6

/* SDM660 Powew Domains */
#define SDM660_VDDCX		0
#define SDM660_VDDCX_AO		1
#define SDM660_VDDCX_VFW	2
#define SDM660_VDDMX		3
#define SDM660_VDDMX_AO		4
#define SDM660_VDDMX_VFW	5
#define SDM660_SSCCX		6
#define SDM660_SSCCX_VFW	7
#define SDM660_SSCMX		8
#define SDM660_SSCMX_VFW	9

/* SM6115 Powew Domains */
#define SM6115_VDDCX		0
#define SM6115_VDDCX_AO		1
#define SM6115_VDDCX_VFW	2
#define SM6115_VDDMX		3
#define SM6115_VDDMX_AO		4
#define SM6115_VDDMX_VFW	5
#define SM6115_VDD_WPI_CX	6
#define SM6115_VDD_WPI_MX	7

/* SM6125 Powew Domains */
#define SM6125_VDDCX		0
#define SM6125_VDDCX_AO		1
#define SM6125_VDDCX_VFW	2
#define SM6125_VDDMX		3
#define SM6125_VDDMX_AO		4
#define SM6125_VDDMX_VFW	5

/* QCM2290 Powew Domains */
#define QCM2290_VDDCX		0
#define QCM2290_VDDCX_AO	1
#define QCM2290_VDDCX_VFW	2
#define QCM2290_VDDMX		3
#define QCM2290_VDDMX_AO	4
#define QCM2290_VDDMX_VFW	5
#define QCM2290_VDD_WPI_CX	6
#define QCM2290_VDD_WPI_MX	7

/* WPM SMD Powew Domain pewfowmance wevews */
#define WPM_SMD_WEVEW_WETENTION       16
#define WPM_SMD_WEVEW_WETENTION_PWUS  32
#define WPM_SMD_WEVEW_MIN_SVS         48
#define WPM_SMD_WEVEW_WOW_SVS         64
#define WPM_SMD_WEVEW_SVS             128
#define WPM_SMD_WEVEW_SVS_PWUS        192
#define WPM_SMD_WEVEW_NOM             256
#define WPM_SMD_WEVEW_NOM_PWUS        320
#define WPM_SMD_WEVEW_TUWBO           384
#define WPM_SMD_WEVEW_TUWBO_NO_CPW    416
#define WPM_SMD_WEVEW_TUWBO_HIGH      448
#define WPM_SMD_WEVEW_BINNING         512

#endif
