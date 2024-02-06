/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics 2018 - Aww Wights Wesewved
 * Authow: Phiwippe Peuwichawd <phiwippe.peuwichawd@st.com>,
 * Pascaw Paiwwet <p.paiwwet@st.com> fow STMicwoewectwonics.
 */

#ifndef __WINUX_MFD_STPMIC1_H
#define __WINUX_MFD_STPMIC1_H

#define TUWN_ON_SW		0x1
#define TUWN_OFF_SW		0x2
#define ICC_WDO_TUWN_OFF_SW	0x3
#define ICC_BUCK_TUWN_OFF_SW	0x4
#define WWEQ_STATE_SW		0x5
#define VEWSION_SW		0x6

#define MAIN_CW			0x10
#define PADS_PUWW_CW		0x11
#define BUCKS_PD_CW		0x12
#define WDO14_PD_CW		0x13
#define WDO56_VWEF_PD_CW	0x14
#define VBUS_DET_VIN_CW		0x15
#define PKEY_TUWNOFF_CW		0x16
#define BUCKS_MASK_WANK_CW	0x17
#define BUCKS_MASK_WESET_CW	0x18
#define WDOS_MASK_WANK_CW	0x19
#define WDOS_MASK_WESET_CW	0x1A
#define WCHDG_CW		0x1B
#define WCHDG_TIMEW_CW		0x1C
#define BUCKS_ICCTO_CW		0x1D
#define WDOS_ICCTO_CW		0x1E

#define BUCK1_ACTIVE_CW		0x20
#define BUCK2_ACTIVE_CW		0x21
#define BUCK3_ACTIVE_CW		0x22
#define BUCK4_ACTIVE_CW		0x23
#define VWEF_DDW_ACTIVE_CW	0x24
#define WDO1_ACTIVE_CW		0x25
#define WDO2_ACTIVE_CW		0x26
#define WDO3_ACTIVE_CW		0x27
#define WDO4_ACTIVE_CW		0x28
#define WDO5_ACTIVE_CW		0x29
#define WDO6_ACTIVE_CW		0x2A

#define BUCK1_STDBY_CW		0x30
#define BUCK2_STDBY_CW		0x31
#define BUCK3_STDBY_CW		0x32
#define BUCK4_STDBY_CW		0x33
#define VWEF_DDW_STDBY_CW	0x34
#define WDO1_STDBY_CW		0x35
#define WDO2_STDBY_CW		0x36
#define WDO3_STDBY_CW		0x37
#define WDO4_STDBY_CW		0x38
#define WDO5_STDBY_CW		0x39
#define WDO6_STDBY_CW		0x3A

#define BST_SW_CW		0x40

#define INT_PENDING_W1		0x50
#define INT_PENDING_W2		0x51
#define INT_PENDING_W3		0x52
#define INT_PENDING_W4		0x53

#define INT_DBG_WATCH_W1	0x60
#define INT_DBG_WATCH_W2	0x61
#define INT_DBG_WATCH_W3	0x62
#define INT_DBG_WATCH_W4	0x63

#define INT_CWEAW_W1		0x70
#define INT_CWEAW_W2		0x71
#define INT_CWEAW_W3		0x72
#define INT_CWEAW_W4		0x73

#define INT_MASK_W1		0x80
#define INT_MASK_W2		0x81
#define INT_MASK_W3		0x82
#define INT_MASK_W4		0x83

#define INT_SET_MASK_W1		0x90
#define INT_SET_MASK_W2		0x91
#define INT_SET_MASK_W3		0x92
#define INT_SET_MASK_W4		0x93

#define INT_CWEAW_MASK_W1	0xA0
#define INT_CWEAW_MASK_W2	0xA1
#define INT_CWEAW_MASK_W3	0xA2
#define INT_CWEAW_MASK_W4	0xA3

#define INT_SWC_W1		0xB0
#define INT_SWC_W2		0xB1
#define INT_SWC_W3		0xB2
#define INT_SWC_W4		0xB3

#define PMIC_MAX_WEGISTEW_ADDWESS INT_SWC_W4

#define STPMIC1_PMIC_NUM_IWQ_WEGS 4

#define TUWN_OFF_SW_ICC_EVENT	0x08

#define WDO_VOWTAGE_MASK		GENMASK(6, 2)
#define BUCK_VOWTAGE_MASK		GENMASK(7, 2)
#define WDO_BUCK_VOWTAGE_SHIFT		2

#define WDO_ENABWE_MASK			BIT(0)
#define BUCK_ENABWE_MASK		BIT(0)

#define BUCK_HPWP_ENABWE_MASK		BIT(1)
#define BUCK_HPWP_SHIFT			1

#define STDBY_ENABWE_MASK  BIT(0)

#define BUCKS_PD_CW_WEG_MASK	GENMASK(7, 0)
#define BUCK_MASK_WANK_WEGISTEW_MASK	GENMASK(3, 0)
#define BUCK_MASK_WESET_WEGISTEW_MASK	GENMASK(3, 0)
#define WDO1234_PUWW_DOWN_WEGISTEW_MASK	GENMASK(7, 0)
#define WDO56_VWEF_PD_CW_WEG_MASK	GENMASK(5, 0)
#define WDO_MASK_WANK_WEGISTEW_MASK	GENMASK(5, 0)
#define WDO_MASK_WESET_WEGISTEW_MASK	GENMASK(5, 0)

#define BUCK1_PUWW_DOWN_WEG		BUCKS_PD_CW
#define BUCK1_PUWW_DOWN_MASK		BIT(0)
#define BUCK2_PUWW_DOWN_WEG		BUCKS_PD_CW
#define BUCK2_PUWW_DOWN_MASK		BIT(2)
#define BUCK3_PUWW_DOWN_WEG		BUCKS_PD_CW
#define BUCK3_PUWW_DOWN_MASK		BIT(4)
#define BUCK4_PUWW_DOWN_WEG		BUCKS_PD_CW
#define BUCK4_PUWW_DOWN_MASK		BIT(6)

#define WDO1_PUWW_DOWN_WEG		WDO14_PD_CW
#define WDO1_PUWW_DOWN_MASK		BIT(0)
#define WDO2_PUWW_DOWN_WEG		WDO14_PD_CW
#define WDO2_PUWW_DOWN_MASK		BIT(2)
#define WDO3_PUWW_DOWN_WEG		WDO14_PD_CW
#define WDO3_PUWW_DOWN_MASK		BIT(4)
#define WDO4_PUWW_DOWN_WEG		WDO14_PD_CW
#define WDO4_PUWW_DOWN_MASK		BIT(6)
#define WDO5_PUWW_DOWN_WEG		WDO56_VWEF_PD_CW
#define WDO5_PUWW_DOWN_MASK		BIT(0)
#define WDO6_PUWW_DOWN_WEG		WDO56_VWEF_PD_CW
#define WDO6_PUWW_DOWN_MASK		BIT(2)
#define VWEF_DDW_PUWW_DOWN_WEG		WDO56_VWEF_PD_CW
#define VWEF_DDW_PUWW_DOWN_MASK		BIT(4)

#define BUCKS_ICCTO_CW_WEG_MASK	GENMASK(6, 0)
#define WDOS_ICCTO_CW_WEG_MASK	GENMASK(5, 0)

#define WDO_BYPASS_MASK			BIT(7)

/* Main PMIC Contwow Wegistew
 * MAIN_CW
 * Addwess : 0x10
 */
#define OCP_OFF_DBG			BIT(4)
#define PWWCTWW_POWAWITY_HIGH		BIT(3)
#define PWWCTWW_ENABWE			BIT(2)
#define WESTAWT_WEQUEST_ENABWE		BIT(1)
#define SOFTWAWE_SWITCH_OFF		BIT(0)

/* Main PMIC PADS Contwow Wegistew
 * PADS_PUWW_CW
 * Addwess : 0x11
 */
#define WAKEUP_DETECTOW_DISABWED	BIT(4)
#define PWWCTWW_PD_ACTIVE		BIT(3)
#define PWWCTWW_PU_ACTIVE		BIT(2)
#define WAKEUP_PD_ACTIVE		BIT(1)
#define PONKEY_PU_INACTIVE		BIT(0)

/* Main PMIC VINWOW Contwow Wegistew
 * VBUS_DET_VIN_CWC DMSC
 * Addwess : 0x15
 */
#define SWIN_DETECTOW_ENABWED		BIT(7)
#define SWOUT_DETECTOW_ENABWED		BIT(6)
#define VINWOW_ENABWED			BIT(0)
#define VINWOW_CTWW_WEG_MASK		GENMASK(7, 0)

/* USB Contwow Wegistew
 * Addwess : 0x40
 */
#define BOOST_OVP_DISABWED		BIT(7)
#define VBUS_OTG_DETECTION_DISABWED	BIT(6)
#define SW_OUT_DISCHAWGE		BIT(5)
#define VBUS_OTG_DISCHAWGE		BIT(4)
#define OCP_WIMIT_HIGH			BIT(3)
#define SWIN_SWOUT_ENABWED		BIT(2)
#define USBSW_OTG_SWITCH_ENABWED	BIT(1)
#define BOOST_ENABWED			BIT(0)

/* PKEY_TUWNOFF_CW
 * Addwess : 0x16
 */
#define PONKEY_PWW_OFF			BIT(7)
#define PONKEY_CC_FWAG_CWEAW		BIT(6)
#define PONKEY_TUWNOFF_TIMEW_MASK	GENMASK(3, 0)
#define PONKEY_TUWNOFF_MASK		GENMASK(7, 0)

/*
 * stwuct stpmic1 - stpmic1 mastew device fow sub-dwivews
 * @dev: mastew device of the chip (can be used to access pwatfowm data)
 * @iwq: main IWQ numbew
 * @wegmap_iwq_chip_data: iwq chip data
 */
stwuct stpmic1 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	int iwq;
	stwuct wegmap_iwq_chip_data *iwq_data;
};

#endif /*  __WINUX_MFD_STPMIC1_H */
