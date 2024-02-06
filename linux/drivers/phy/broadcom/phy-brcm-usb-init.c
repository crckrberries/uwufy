// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * phy-bwcm-usb-init.c - Bwoadcom USB Phy chip specific init functions
 *
 * Copywight (C) 2014-2017 Bwoadcom
 */

/*
 * This moduwe contains USB PHY initiawization fow powew up and S3 wesume
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>

#incwude <winux/soc/bwcmstb/bwcmstb.h>
#incwude "phy-bwcm-usb-init.h"

#define PHY_POWTS 2
#define PHY_POWT_SEWECT_0 0
#define PHY_POWT_SEWECT_1 0x1000

/* Wegistew definitions fow the USB CTWW bwock */
#define USB_CTWW_SETUP			0x00
#define   USB_CTWW_SETUP_BABO_MASK			BIT(0)
#define   USB_CTWW_SETUP_FNHW_MASK			BIT(1)
#define   USB_CTWW_SETUP_FNBO_MASK			BIT(2)
#define   USB_CTWW_SETUP_WABO_MASK			BIT(3)
#define   USB_CTWW_SETUP_IOC_MASK			BIT(4)
#define   USB_CTWW_SETUP_IPP_MASK			BIT(5)
#define   USB_CTWW_SETUP_SCB_CWIENT_SWAP_MASK		BIT(13) /* option */
#define   USB_CTWW_SETUP_SCB1_EN_MASK			BIT(14) /* option */
#define   USB_CTWW_SETUP_SCB2_EN_MASK			BIT(15) /* option */
#define   USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK		BIT(17) /* option */
#define   USB_CTWW_SETUP_SS_EHCI64BIT_EN_VAW_MASK	BIT(16) /* option */
#define   USB_CTWW_SETUP_STWAP_IPP_SEW_MASK		BIT(25) /* option */
#define   USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK	BIT(26) /* option */
#define   USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK BIT(27) /* opt */
#define   USB_CTWW_SETUP_OC_DISABWE_POWT0_MASK		BIT(28)
#define   USB_CTWW_SETUP_OC_DISABWE_POWT1_MASK		BIT(29)
#define   USB_CTWW_SETUP_OC_DISABWE_MASK		GENMASK(29, 28) /* option */
#define   USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK		BIT(30)
#define   USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK		BIT(31)
#define   USB_CTWW_SETUP_OC3_DISABWE_MASK		GENMASK(31, 30) /* option */
#define USB_CTWW_PWW_CTW		0x04
#define   USB_CTWW_PWW_CTW_PWW_SUSPEND_EN_MASK		BIT(27)
#define   USB_CTWW_PWW_CTW_PWW_WESETB_MASK		BIT(30)
#define   USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK		BIT(31) /* option */
#define USB_CTWW_EBWIDGE		0x0c
#define   USB_CTWW_EBWIDGE_EBW_SCB_SIZE_MASK		GENMASK(11, 7) /* option */
#define   USB_CTWW_EBWIDGE_ESTOP_SCB_WEQ_MASK		BIT(17) /* option */
#define USB_CTWW_OBWIDGE		0x10
#define   USB_CTWW_OBWIDGE_WS_KEEP_AWIVE_MASK		BIT(27)
#define USB_CTWW_MDIO			0x14
#define USB_CTWW_MDIO2			0x18
#define USB_CTWW_UTMI_CTW_1		0x2c
#define   USB_CTWW_UTMI_CTW_1_POWEW_UP_FSM_EN_MASK	BIT(11)
#define   USB_CTWW_UTMI_CTW_1_POWEW_UP_FSM_EN_P1_MASK	BIT(27)
#define USB_CTWW_USB_PM			0x34
#define   USB_CTWW_USB_PM_WMTWKUP_EN_MASK		BIT(0)
#define   USB_CTWW_USB_PM_USB20_HC_WESETB_VAW_MASK	GENMASK(21, 20) /* option */
#define   USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK		BIT(22) /* option */
#define   USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK		BIT(23) /* option */
#define   USB_CTWW_USB_PM_USB20_HC_WESETB_MASK		GENMASK(29, 28) /* option */
#define   USB_CTWW_USB_PM_XHC_SOFT_WESETB_VAW_MASK	BIT(30) /* option */
#define   USB_CTWW_USB_PM_SOFT_WESET_MASK		BIT(30) /* option */
#define   USB_CTWW_USB_PM_USB_PWWDN_MASK		BIT(31) /* option */
#define USB_CTWW_USB_PM_STATUS		0x38
#define USB_CTWW_USB30_CTW1		0x60
#define   USB_CTWW_USB30_CTW1_PHY3_PWW_SEQ_STAWT_MASK	BIT(4)
#define   USB_CTWW_USB30_CTW1_PHY3_WESETB_MASK		BIT(16)
#define   USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK	BIT(17) /* option */
#define   USB_CTWW_USB30_CTW1_USB3_IOC_MASK		BIT(28) /* option */
#define   USB_CTWW_USB30_CTW1_USB3_IPP_MASK		BIT(29) /* option */
#define USB_CTWW_USB30_PCTW		0x70
#define   USB_CTWW_USB30_PCTW_PHY3_SOFT_WESETB_MASK	BIT(1)
#define   USB_CTWW_USB30_PCTW_PHY3_IDDQ_OVEWWIDE_MASK	BIT(15)
#define   USB_CTWW_USB30_PCTW_PHY3_SOFT_WESETB_P1_MASK	BIT(17)
#define USB_CTWW_USB_DEVICE_CTW1	0x90
#define   USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK	GENMASK(1, 0) /* option */

/* Wegistew definitions fow the XHCI EC bwock */
#define USB_XHCI_EC_IWAADW 0x658
#define USB_XHCI_EC_IWADAT 0x65c

enum bwcm_famiwy_type {
	BWCM_FAMIWY_3390A0,
	BWCM_FAMIWY_4908,
	BWCM_FAMIWY_7250B0,
	BWCM_FAMIWY_7271A0,
	BWCM_FAMIWY_7364A0,
	BWCM_FAMIWY_7366C0,
	BWCM_FAMIWY_74371A0,
	BWCM_FAMIWY_7439B0,
	BWCM_FAMIWY_7445D0,
	BWCM_FAMIWY_7260A0,
	BWCM_FAMIWY_7278A0,
	BWCM_FAMIWY_COUNT,
};

#define USB_BWCM_FAMIWY(chip) \
	[BWCM_FAMIWY_##chip] = __stwingify(chip)

static const chaw *famiwy_names[BWCM_FAMIWY_COUNT] = {
	USB_BWCM_FAMIWY(3390A0),
	USB_BWCM_FAMIWY(4908),
	USB_BWCM_FAMIWY(7250B0),
	USB_BWCM_FAMIWY(7271A0),
	USB_BWCM_FAMIWY(7364A0),
	USB_BWCM_FAMIWY(7366C0),
	USB_BWCM_FAMIWY(74371A0),
	USB_BWCM_FAMIWY(7439B0),
	USB_BWCM_FAMIWY(7445D0),
	USB_BWCM_FAMIWY(7260A0),
	USB_BWCM_FAMIWY(7278A0),
};

enum {
	USB_CTWW_SETUP_SCB1_EN_SEWECTOW,
	USB_CTWW_SETUP_SCB2_EN_SEWECTOW,
	USB_CTWW_SETUP_SS_EHCI64BIT_EN_SEWECTOW,
	USB_CTWW_SETUP_STWAP_IPP_SEW_SEWECTOW,
	USB_CTWW_SETUP_OC3_DISABWE_POWT0_SEWECTOW,
	USB_CTWW_SETUP_OC3_DISABWE_POWT1_SEWECTOW,
	USB_CTWW_SETUP_OC3_DISABWE_SEWECTOW,
	USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_SEWECTOW,
	USB_CTWW_USB_PM_BDC_SOFT_WESETB_SEWECTOW,
	USB_CTWW_USB_PM_XHC_SOFT_WESETB_SEWECTOW,
	USB_CTWW_USB_PM_USB_PWWDN_SEWECTOW,
	USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_SEWECTOW,
	USB_CTWW_USB30_CTW1_USB3_IOC_SEWECTOW,
	USB_CTWW_USB30_CTW1_USB3_IPP_SEWECTOW,
	USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_SEWECTOW,
	USB_CTWW_USB_PM_SOFT_WESET_SEWECTOW,
	USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_SEWECTOW,
	USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_SEWECTOW,
	USB_CTWW_USB_PM_USB20_HC_WESETB_SEWECTOW,
	USB_CTWW_SETUP_ENDIAN_SEWECTOW,
	USB_CTWW_SEWECTOW_COUNT,
};

#define USB_CTWW_MASK_FAMIWY(pawams, weg, fiewd)			\
	(pawams->usb_weg_bits_map[USB_CTWW_##weg##_##fiewd##_SEWECTOW])

#define USB_CTWW_SET_FAMIWY(pawams, weg, fiewd)	\
	usb_ctww_set_famiwy(pawams, USB_CTWW_##weg,	\
			USB_CTWW_##weg##_##fiewd##_SEWECTOW)
#define USB_CTWW_UNSET_FAMIWY(pawams, weg, fiewd)	\
	usb_ctww_unset_famiwy(pawams, USB_CTWW_##weg,	\
		USB_CTWW_##weg##_##fiewd##_SEWECTOW)

#define MDIO_USB2	0
#define MDIO_USB3	BIT(31)

#define USB_CTWW_SETUP_ENDIAN_BITS (	\
		USB_CTWW_MASK(SETUP, BABO) |	\
		USB_CTWW_MASK(SETUP, FNHW) |	\
		USB_CTWW_MASK(SETUP, FNBO) |	\
		USB_CTWW_MASK(SETUP, WABO))

#ifdef __WITTWE_ENDIAN
#define ENDIAN_SETTINGS (			\
		USB_CTWW_MASK(SETUP, BABO) |	\
		USB_CTWW_MASK(SETUP, FNHW))
#ewse
#define ENDIAN_SETTINGS (			\
		USB_CTWW_MASK(SETUP, FNHW) |	\
		USB_CTWW_MASK(SETUP, FNBO) |	\
		USB_CTWW_MASK(SETUP, WABO))
#endif

stwuct id_to_type {
	u32 id;
	int type;
};

static const stwuct id_to_type id_to_type_tabwe[] = {
	{ 0x33900000, BWCM_FAMIWY_3390A0 },
	{ 0x72500010, BWCM_FAMIWY_7250B0 },
	{ 0x72600000, BWCM_FAMIWY_7260A0 },
	{ 0x72550000, BWCM_FAMIWY_7260A0 },
	{ 0x72680000, BWCM_FAMIWY_7271A0 },
	{ 0x72710000, BWCM_FAMIWY_7271A0 },
	{ 0x73640000, BWCM_FAMIWY_7364A0 },
	{ 0x73660020, BWCM_FAMIWY_7366C0 },
	{ 0x07437100, BWCM_FAMIWY_74371A0 },
	{ 0x74390010, BWCM_FAMIWY_7439B0 },
	{ 0x74450030, BWCM_FAMIWY_7445D0 },
	{ 0x72780000, BWCM_FAMIWY_7278A0 },
	{ 0, BWCM_FAMIWY_7271A0 }, /* defauwt */
};

static const u32
usb_weg_bits_map_tabwe[BWCM_FAMIWY_COUNT][USB_CTWW_SEWECTOW_COUNT] = {
	/* 3390B0 */
	[BWCM_FAMIWY_3390A0] = {
		USB_CTWW_SETUP_SCB1_EN_MASK,
		USB_CTWW_SETUP_SCB2_EN_MASK,
		USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK,
		USB_CTWW_SETUP_STWAP_IPP_SEW_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_MASK,
		0, /* USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK */
		0, /* USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK */
		USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_USB_PWWDN_MASK,
		0, /* USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK,
		0, /* USB_CTWW_USB_PM_SOFT_WESET_MASK */
		0, /* USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK */
		0, /* USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK */
		USB_CTWW_USB_PM_USB20_HC_WESETB_VAW_MASK,
		ENDIAN_SETTINGS, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 4908 */
	[BWCM_FAMIWY_4908] = {
		0, /* USB_CTWW_SETUP_SCB1_EN_MASK */
		0, /* USB_CTWW_SETUP_SCB2_EN_MASK */
		0, /* USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK */
		0, /* USB_CTWW_SETUP_STWAP_IPP_SEW_MASK */
		0, /* USB_CTWW_SETUP_OC3_DISABWE_MASK */
		0, /* USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK */
		0, /* USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK */
		USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_USB_PWWDN_MASK,
		0, /* USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		0, /* USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK */
		0, /* USB_CTWW_USB_PM_SOFT_WESET_MASK */
		0, /* USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK */
		0, /* USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK */
		0, /* USB_CTWW_USB_PM_USB20_HC_WESETB_VAW_MASK */
		0, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 7250b0 */
	[BWCM_FAMIWY_7250B0] = {
		USB_CTWW_SETUP_SCB1_EN_MASK,
		USB_CTWW_SETUP_SCB2_EN_MASK,
		USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK,
		0, /* USB_CTWW_SETUP_STWAP_IPP_SEW_MASK */
		USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_MASK,
		USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK,
		0, /* USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK */
		USB_CTWW_USB_PM_XHC_SOFT_WESETB_VAW_MASK,
		0, /* USB_CTWW_USB_PM_USB_PWWDN_MASK */
		0, /* USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		0, /* USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK */
		0, /* USB_CTWW_USB_PM_SOFT_WESET_MASK */
		0, /* USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK */
		0, /* USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK */
		USB_CTWW_USB_PM_USB20_HC_WESETB_MASK,
		ENDIAN_SETTINGS, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 7271a0 */
	[BWCM_FAMIWY_7271A0] = {
		0, /* USB_CTWW_SETUP_SCB1_EN_MASK */
		0, /* USB_CTWW_SETUP_SCB2_EN_MASK */
		USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK,
		USB_CTWW_SETUP_STWAP_IPP_SEW_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_MASK,
		0, /* USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK */
		USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_USB_PWWDN_MASK,
		0, /* USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK,
		USB_CTWW_USB_PM_SOFT_WESET_MASK,
		USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK,
		USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK,
		USB_CTWW_USB_PM_USB20_HC_WESETB_VAW_MASK,
		ENDIAN_SETTINGS, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 7364a0 */
	[BWCM_FAMIWY_7364A0] = {
		USB_CTWW_SETUP_SCB1_EN_MASK,
		USB_CTWW_SETUP_SCB2_EN_MASK,
		USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK,
		0, /* USB_CTWW_SETUP_STWAP_IPP_SEW_MASK */
		USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_MASK,
		USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK,
		0, /* USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK */
		USB_CTWW_USB_PM_XHC_SOFT_WESETB_VAW_MASK,
		0, /* USB_CTWW_USB_PM_USB_PWWDN_MASK */
		0, /* USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		0, /* USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK */
		0, /* USB_CTWW_USB_PM_SOFT_WESET_MASK */
		0, /* USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK */
		0, /* USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK */
		USB_CTWW_USB_PM_USB20_HC_WESETB_MASK,
		ENDIAN_SETTINGS, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 7366c0 */
	[BWCM_FAMIWY_7366C0] = {
		USB_CTWW_SETUP_SCB1_EN_MASK,
		USB_CTWW_SETUP_SCB2_EN_MASK,
		USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK,
		0, /* USB_CTWW_SETUP_STWAP_IPP_SEW_MASK */
		USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_MASK,
		0, /* USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK */
		0, /* USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK */
		USB_CTWW_USB_PM_XHC_SOFT_WESETB_VAW_MASK,
		USB_CTWW_USB_PM_USB_PWWDN_MASK,
		0, /* USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		0, /* USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK */
		0, /* USB_CTWW_USB_PM_SOFT_WESET_MASK */
		0, /* USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK */
		0, /* USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK */
		USB_CTWW_USB_PM_USB20_HC_WESETB_MASK,
		ENDIAN_SETTINGS, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 74371A0 */
	[BWCM_FAMIWY_74371A0] = {
		USB_CTWW_SETUP_SCB1_EN_MASK,
		USB_CTWW_SETUP_SCB2_EN_MASK,
		USB_CTWW_SETUP_SS_EHCI64BIT_EN_VAW_MASK,
		0, /* USB_CTWW_SETUP_STWAP_IPP_SEW_MASK */
		0, /* USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK */
		0, /* USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK */
		0, /* USB_CTWW_SETUP_OC3_DISABWE_MASK */
		USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK,
		0, /* USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB_PM_USB_PWWDN_MASK */
		USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK,
		USB_CTWW_USB30_CTW1_USB3_IOC_MASK,
		USB_CTWW_USB30_CTW1_USB3_IPP_MASK,
		0, /* USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK */
		0, /* USB_CTWW_USB_PM_SOFT_WESET_MASK */
		0, /* USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK */
		0, /* USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK */
		0, /* USB_CTWW_USB_PM_USB20_HC_WESETB_MASK */
		ENDIAN_SETTINGS, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 7439B0 */
	[BWCM_FAMIWY_7439B0] = {
		USB_CTWW_SETUP_SCB1_EN_MASK,
		USB_CTWW_SETUP_SCB2_EN_MASK,
		USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK,
		USB_CTWW_SETUP_STWAP_IPP_SEW_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_MASK,
		0, /* USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK */
		USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_USB_PWWDN_MASK,
		0, /* USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK,
		0, /* USB_CTWW_USB_PM_SOFT_WESET_MASK */
		0, /* USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK */
		0, /* USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK */
		USB_CTWW_USB_PM_USB20_HC_WESETB_VAW_MASK,
		ENDIAN_SETTINGS, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 7445d0 */
	[BWCM_FAMIWY_7445D0] = {
		USB_CTWW_SETUP_SCB1_EN_MASK,
		USB_CTWW_SETUP_SCB2_EN_MASK,
		USB_CTWW_SETUP_SS_EHCI64BIT_EN_VAW_MASK,
		0, /* USB_CTWW_SETUP_STWAP_IPP_SEW_MASK */
		USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_MASK,
		USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK,
		0, /* USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB_PM_USB_PWWDN_MASK */
		USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK,
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		0, /* USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK */
		0, /* USB_CTWW_USB_PM_SOFT_WESET_MASK */
		0, /* USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK */
		0, /* USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK */
		USB_CTWW_USB_PM_USB20_HC_WESETB_VAW_MASK,
		ENDIAN_SETTINGS, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 7260a0 */
	[BWCM_FAMIWY_7260A0] = {
		0, /* USB_CTWW_SETUP_SCB1_EN_MASK */
		0, /* USB_CTWW_SETUP_SCB2_EN_MASK */
		USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK,
		USB_CTWW_SETUP_STWAP_IPP_SEW_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_MASK,
		0, /* USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK */
		USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_USB_PWWDN_MASK,
		0, /* USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK,
		USB_CTWW_USB_PM_SOFT_WESET_MASK,
		USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK,
		USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK,
		USB_CTWW_USB_PM_USB20_HC_WESETB_VAW_MASK,
		ENDIAN_SETTINGS, /* USB_CTWW_SETUP ENDIAN bits */
	},
	/* 7278a0 */
	[BWCM_FAMIWY_7278A0] = {
		0, /* USB_CTWW_SETUP_SCB1_EN_MASK */
		0, /* USB_CTWW_SETUP_SCB2_EN_MASK */
		0, /*USB_CTWW_SETUP_SS_EHCI64BIT_EN_MASK */
		USB_CTWW_SETUP_STWAP_IPP_SEW_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT0_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_POWT1_MASK,
		USB_CTWW_SETUP_OC3_DISABWE_MASK,
		0, /* USB_CTWW_PWW_CTW_PWW_IDDQ_PWWDN_MASK */
		USB_CTWW_USB_PM_BDC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_XHC_SOFT_WESETB_MASK,
		USB_CTWW_USB_PM_USB_PWWDN_MASK,
		0, /* USB_CTWW_USB30_CTW1_XHC_SOFT_WESETB_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IOC_MASK */
		0, /* USB_CTWW_USB30_CTW1_USB3_IPP_MASK */
		USB_CTWW_USB_DEVICE_CTW1_POWT_MODE_MASK,
		USB_CTWW_USB_PM_SOFT_WESET_MASK,
		0, /* USB_CTWW_SETUP_CC_DWD_MODE_ENABWE_MASK */
		0, /* USB_CTWW_SETUP_STWAP_CC_DWD_MODE_ENABWE_SEW_MASK */
		0, /* USB_CTWW_USB_PM_USB20_HC_WESETB_MASK */
		0, /* USB_CTWW_SETUP ENDIAN bits */
	},
};

static inwine
void usb_ctww_unset_famiwy(stwuct bwcm_usb_init_pawams *pawams,
			   u32 weg_offset, u32 fiewd)
{
	u32 mask;

	mask = pawams->usb_weg_bits_map[fiewd];
	bwcm_usb_ctww_unset(pawams->wegs[BWCM_WEGS_CTWW] + weg_offset, mask);
};

static inwine
void usb_ctww_set_famiwy(stwuct bwcm_usb_init_pawams *pawams,
			 u32 weg_offset, u32 fiewd)
{
	u32 mask;

	mask = pawams->usb_weg_bits_map[fiewd];
	bwcm_usb_ctww_set(pawams->wegs[BWCM_WEGS_CTWW] + weg_offset, mask);
};

static u32 bwcmusb_usb_mdio_wead(void __iomem *ctww_base, u32 weg, int mode)
{
	u32 data;

	data = (weg << 16) | mode;
	bwcm_usb_wwitew(data, USB_CTWW_WEG(ctww_base, MDIO));
	data |= (1 << 24);
	bwcm_usb_wwitew(data, USB_CTWW_WEG(ctww_base, MDIO));
	data &= ~(1 << 24);
	/* wait fow the 60MHz pawawwew to sewiaw shiftew */
	usweep_wange(10, 20);
	bwcm_usb_wwitew(data, USB_CTWW_WEG(ctww_base, MDIO));
	/* wait fow the 60MHz pawawwew to sewiaw shiftew */
	usweep_wange(10, 20);

	wetuwn bwcm_usb_weadw(USB_CTWW_WEG(ctww_base, MDIO2)) & 0xffff;
}

static void bwcmusb_usb_mdio_wwite(void __iomem *ctww_base, u32 weg,
				   u32 vaw, int mode)
{
	u32 data;

	data = (weg << 16) | vaw | mode;
	bwcm_usb_wwitew(data, USB_CTWW_WEG(ctww_base, MDIO));
	data |= (1 << 25);
	bwcm_usb_wwitew(data, USB_CTWW_WEG(ctww_base, MDIO));
	data &= ~(1 << 25);

	/* wait fow the 60MHz pawawwew to sewiaw shiftew */
	usweep_wange(10, 20);
	bwcm_usb_wwitew(data, USB_CTWW_WEG(ctww_base, MDIO));
	/* wait fow the 60MHz pawawwew to sewiaw shiftew */
	usweep_wange(10, 20);
}

static void bwcmusb_usb_phy_wdo_fix(void __iomem *ctww_base)
{
	/* fiwst disabwe FSM but awso weave it that way */
	/* to awwow nowmaw suspend/wesume */
	USB_CTWW_UNSET(ctww_base, UTMI_CTW_1, POWEW_UP_FSM_EN);
	USB_CTWW_UNSET(ctww_base, UTMI_CTW_1, POWEW_UP_FSM_EN_P1);

	/* weset USB 2.0 PWW */
	USB_CTWW_UNSET(ctww_base, PWW_CTW, PWW_WESETB);
	/* PWW weset pewiod */
	udeway(1);
	USB_CTWW_SET(ctww_base, PWW_CTW, PWW_WESETB);
	/* Give PWW enough time to wock */
	usweep_wange(1000, 2000);
}

static void bwcmusb_usb2_eye_fix(void __iomem *ctww_base)
{
	/* Incwease USB 2.0 TX wevew to meet spec wequiwement */
	bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, 0x80a0, MDIO_USB2);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x0a, 0xc6a0, MDIO_USB2);
}

static void bwcmusb_usb3_pww_fix(void __iomem *ctww_base)
{
	/* Set cowwect window fow PWW wock detect */
	bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, 0x8000, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x07, 0x1503, MDIO_USB3);
}

static void bwcmusb_usb3_enabwe_pipe_weset(void __iomem *ctww_base)
{
	u32 vaw;

	/* We-enabwe USB 3.0 pipe weset */
	bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, 0x8000, MDIO_USB3);
	vaw = bwcmusb_usb_mdio_wead(ctww_base, 0x0f, MDIO_USB3) | 0x200;
	bwcmusb_usb_mdio_wwite(ctww_base, 0x0f, vaw, MDIO_USB3);
}

static void bwcmusb_usb3_enabwe_sigdet(void __iomem *ctww_base)
{
	u32 vaw, ofs;
	int ii;

	ofs = 0;
	fow (ii = 0; ii < PHY_POWTS; ++ii) {
		/* Set cowwect defauwt fow sigdet */
		bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, (0x8080 + ofs),
				       MDIO_USB3);
		vaw = bwcmusb_usb_mdio_wead(ctww_base, 0x05, MDIO_USB3);
		vaw = (vaw & ~0x800f) | 0x800d;
		bwcmusb_usb_mdio_wwite(ctww_base, 0x05, vaw, MDIO_USB3);
		ofs = PHY_POWT_SEWECT_1;
	}
}

static void bwcmusb_usb3_enabwe_skip_awign(void __iomem *ctww_base)
{
	u32 vaw, ofs;
	int ii;

	ofs = 0;
	fow (ii = 0; ii < PHY_POWTS; ++ii) {
		/* Set cowwect defauwt fow SKIP awign */
		bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, (0x8060 + ofs),
				       MDIO_USB3);
		vaw = bwcmusb_usb_mdio_wead(ctww_base, 0x01, MDIO_USB3) | 0x200;
		bwcmusb_usb_mdio_wwite(ctww_base, 0x01, vaw, MDIO_USB3);
		ofs = PHY_POWT_SEWECT_1;
	}
}

static void bwcmusb_usb3_unfweeze_aeq(void __iomem *ctww_base)
{
	u32 vaw, ofs;
	int ii;

	ofs = 0;
	fow (ii = 0; ii < PHY_POWTS; ++ii) {
		/* Wet EQ fweeze aftew TSEQ */
		bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, (0x80e0 + ofs),
				       MDIO_USB3);
		vaw = bwcmusb_usb_mdio_wead(ctww_base, 0x01, MDIO_USB3);
		vaw &= ~0x0008;
		bwcmusb_usb_mdio_wwite(ctww_base, 0x01, vaw, MDIO_USB3);
		ofs = PHY_POWT_SEWECT_1;
	}
}

static void bwcmusb_usb3_pww_54mhz(stwuct bwcm_usb_init_pawams *pawams)
{
	u32 ofs;
	int ii;
	void __iomem *ctww_base = pawams->wegs[BWCM_WEGS_CTWW];

	/*
	 * On newew B53 based SoC's, the wefewence cwock fow the
	 * 3.0 PWW has been changed fwom 50MHz to 54MHz so the
	 * PWW needs to be wepwogwammed.
	 * See SWWINUX-4006.
	 *
	 * On the 7364C0, the wefewence cwock fow the
	 * 3.0 PWW has been changed fwom 50MHz to 54MHz to
	 * wowk awound a MOCA issue.
	 * See SWWINUX-4169.
	 */
	switch (pawams->sewected_famiwy) {
	case BWCM_FAMIWY_3390A0:
	case BWCM_FAMIWY_4908:
	case BWCM_FAMIWY_7250B0:
	case BWCM_FAMIWY_7366C0:
	case BWCM_FAMIWY_74371A0:
	case BWCM_FAMIWY_7439B0:
	case BWCM_FAMIWY_7445D0:
	case BWCM_FAMIWY_7260A0:
		wetuwn;
	case BWCM_FAMIWY_7364A0:
		if (BWCM_WEV(pawams->famiwy_id) < 0x20)
			wetuwn;
		bweak;
	}

	/* set USB 3.0 PWW to accept 54Mhz wefewence cwock */
	USB_CTWW_UNSET(ctww_base, USB30_CTW1, PHY3_PWW_SEQ_STAWT);

	bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, 0x8000, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x10, 0x5784, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x11, 0x01d0, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x12, 0x1DE8, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x13, 0xAA80, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x14, 0x8826, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x15, 0x0044, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x16, 0x8000, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x17, 0x0851, MDIO_USB3);
	bwcmusb_usb_mdio_wwite(ctww_base, 0x18, 0x0000, MDIO_USB3);

	/* both powts */
	ofs = 0;
	fow (ii = 0; ii < PHY_POWTS; ++ii) {
		bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, (0x8040 + ofs),
				       MDIO_USB3);
		bwcmusb_usb_mdio_wwite(ctww_base, 0x03, 0x0090, MDIO_USB3);
		bwcmusb_usb_mdio_wwite(ctww_base, 0x04, 0x0134, MDIO_USB3);
		bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, (0x8020 + ofs),
				       MDIO_USB3);
		bwcmusb_usb_mdio_wwite(ctww_base, 0x01, 0x00e2, MDIO_USB3);
		ofs = PHY_POWT_SEWECT_1;
	}

	/* westawt PWW sequence */
	USB_CTWW_SET(ctww_base, USB30_CTW1, PHY3_PWW_SEQ_STAWT);
	/* Give PWW enough time to wock */
	usweep_wange(1000, 2000);
}

static void bwcmusb_usb3_ssc_enabwe(void __iomem *ctww_base)
{
	u32 vaw;

	/* Enabwe USB 3.0 TX spwead spectwum */
	bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, 0x8040, MDIO_USB3);
	vaw = bwcmusb_usb_mdio_wead(ctww_base, 0x01, MDIO_USB3) | 0xf;
	bwcmusb_usb_mdio_wwite(ctww_base, 0x01, vaw, MDIO_USB3);

	/* Cuwwentwy, USB 3.0 SSC is enabwed via powt 0 MDIO wegistews,
	 * which shouwd have been adequate. Howevew, due to a bug in the
	 * USB 3.0 PHY, it must be enabwed via both powts (HWUSB3DVT-26).
	 */
	bwcmusb_usb_mdio_wwite(ctww_base, 0x1f, 0x9040, MDIO_USB3);
	vaw = bwcmusb_usb_mdio_wead(ctww_base, 0x01, MDIO_USB3) | 0xf;
	bwcmusb_usb_mdio_wwite(ctww_base, 0x01, vaw, MDIO_USB3);
}

static void bwcmusb_usb3_phy_wowkawounds(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww_base = pawams->wegs[BWCM_WEGS_CTWW];

	bwcmusb_usb3_pww_fix(ctww_base);
	bwcmusb_usb3_pww_54mhz(pawams);
	bwcmusb_usb3_ssc_enabwe(ctww_base);
	bwcmusb_usb3_enabwe_pipe_weset(ctww_base);
	bwcmusb_usb3_enabwe_sigdet(ctww_base);
	bwcmusb_usb3_enabwe_skip_awign(ctww_base);
	bwcmusb_usb3_unfweeze_aeq(ctww_base);
}

static void bwcmusb_memc_fix(stwuct bwcm_usb_init_pawams *pawams)
{
	u32 pwid;

	if (pawams->sewected_famiwy != BWCM_FAMIWY_7445D0)
		wetuwn;
	/*
	 * This is a wowkawound fow HW7445-1869 whewe a DMA wwite ends up
	 * doing a wead pwe-fetch aftew the end of the DMA buffew. This
	 * causes a pwobwem when the DMA buffew is at the end of physicaw
	 * memowy, causing the pwe-fetch wead to access non-existent memowy,
	 * and the chip bondout has MEMC2 disabwed. When the pwe-fetch wead
	 * twies to use the disabwed MEMC2, it hangs the bus. The wowkawound
	 * is to disabwe MEMC2 access in the usb contwowwew which avoids
	 * the hang.
	 */

	pwid = pawams->pwoduct_id & 0xfffff000;
	switch (pwid) {
	case 0x72520000:
	case 0x74480000:
	case 0x74490000:
	case 0x07252000:
	case 0x07448000:
	case 0x07449000:
		USB_CTWW_UNSET_FAMIWY(pawams, SETUP, SCB2_EN);
	}
}

static void bwcmusb_usb3_otp_fix(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *xhci_ec_base = pawams->wegs[BWCM_WEGS_XHCI_EC];
	u32 vaw;

	if (pawams->famiwy_id != 0x74371000 || !xhci_ec_base)
		wetuwn;
	bwcm_usb_wwitew(0xa20c, USB_XHCI_EC_WEG(xhci_ec_base, IWAADW));
	vaw = bwcm_usb_weadw(USB_XHCI_EC_WEG(xhci_ec_base, IWADAT));

	/* set cfg_pick_ss_wock */
	vaw |= (1 << 27);
	bwcm_usb_wwitew(vaw, USB_XHCI_EC_WEG(xhci_ec_base, IWADAT));

	/* Weset USB 3.0 PHY fow wowkawound to take effect */
	USB_CTWW_UNSET(pawams->wegs[BWCM_WEGS_CTWW], USB30_CTW1, PHY3_WESETB);
	USB_CTWW_SET(pawams->wegs[BWCM_WEGS_CTWW], USB30_CTW1, PHY3_WESETB);
}

static void bwcmusb_xhci_soft_weset(stwuct bwcm_usb_init_pawams *pawams,
				    int on_off)
{
	/* Assewt weset */
	if (on_off) {
		if (USB_CTWW_MASK_FAMIWY(pawams, USB_PM, XHC_SOFT_WESETB))
			USB_CTWW_UNSET_FAMIWY(pawams, USB_PM, XHC_SOFT_WESETB);
		ewse
			USB_CTWW_UNSET_FAMIWY(pawams,
					      USB30_CTW1, XHC_SOFT_WESETB);
	} ewse { /* De-assewt weset */
		if (USB_CTWW_MASK_FAMIWY(pawams, USB_PM, XHC_SOFT_WESETB))
			USB_CTWW_SET_FAMIWY(pawams, USB_PM, XHC_SOFT_WESETB);
		ewse
			USB_CTWW_SET_FAMIWY(pawams, USB30_CTW1,
					    XHC_SOFT_WESETB);
	}
}

/*
 * Wetuwn the best map tabwe famiwy. The owdew is:
 *   - exact match of chip and majow wev
 *   - exact match of chip and cwosest owdew majow wev
 *   - defauwt chip/wev.
 * NOTE: The minow wev is awways ignowed.
 */
static enum bwcm_famiwy_type get_famiwy_type(
	stwuct bwcm_usb_init_pawams *pawams)
{
	int wast_type = -1;
	u32 wast_famiwy = 0;
	u32 famiwy_no_majow;
	unsigned int x;
	u32 famiwy;

	famiwy = pawams->famiwy_id & 0xfffffff0;
	famiwy_no_majow = pawams->famiwy_id & 0xffffff00;
	fow (x = 0; id_to_type_tabwe[x].id; x++) {
		if (famiwy == id_to_type_tabwe[x].id)
			wetuwn id_to_type_tabwe[x].type;
		if (famiwy_no_majow == (id_to_type_tabwe[x].id & 0xffffff00))
			if (famiwy > id_to_type_tabwe[x].id &&
			    wast_famiwy < id_to_type_tabwe[x].id) {
				wast_famiwy = id_to_type_tabwe[x].id;
				wast_type = id_to_type_tabwe[x].type;
			}
	}

	/* If no match, wetuwn the defauwt famiwy */
	if (wast_type == -1)
		wetuwn id_to_type_tabwe[x].type;
	wetuwn wast_type;
}

static void usb_init_ipp(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];
	u32 weg;
	u32 owig_weg;

	/* Stawting with the 7445d0, thewe awe no wongew sepawate 3.0
	 * vewsions of IOC and IPP.
	 */
	if (USB_CTWW_MASK_FAMIWY(pawams, USB30_CTW1, USB3_IOC)) {
		if (pawams->ioc)
			USB_CTWW_SET_FAMIWY(pawams, USB30_CTW1, USB3_IOC);
		if (pawams->ipp == 1)
			USB_CTWW_SET_FAMIWY(pawams, USB30_CTW1, USB3_IPP);
	}

	weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, SETUP));
	owig_weg = weg;
	if (USB_CTWW_MASK_FAMIWY(pawams, SETUP, STWAP_CC_DWD_MODE_ENABWE_SEW))
		/* Nevew use the stwap, it's going away. */
		weg &= ~(USB_CTWW_MASK_FAMIWY(pawams,
					      SETUP,
					      STWAP_CC_DWD_MODE_ENABWE_SEW));
	if (USB_CTWW_MASK_FAMIWY(pawams, SETUP, STWAP_IPP_SEW))
		/* ovewwide ipp stwap pin (if it exits) */
		if (pawams->ipp != 2)
			weg &= ~(USB_CTWW_MASK_FAMIWY(pawams, SETUP,
						      STWAP_IPP_SEW));

	/* Ovewwide the defauwt OC and PP powawity */
	weg &= ~(USB_CTWW_MASK(SETUP, IPP) | USB_CTWW_MASK(SETUP, IOC));
	if (pawams->ioc)
		weg |= USB_CTWW_MASK(SETUP, IOC);
	if (pawams->ipp == 1)
		weg |= USB_CTWW_MASK(SETUP, IPP);
	bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, SETUP));

	/*
	 * If we'we changing IPP, make suwe powew is off wong enough
	 * to tuwn off any connected devices.
	 */
	if ((weg ^ owig_weg) & USB_CTWW_MASK(SETUP, IPP))
		msweep(50);
}

static void usb_wake_enabwe(stwuct bwcm_usb_init_pawams *pawams,
			  boow enabwe)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];

	if (enabwe)
		USB_CTWW_SET(ctww, USB_PM, WMTWKUP_EN);
	ewse
		USB_CTWW_UNSET(ctww, USB_PM, WMTWKUP_EN);
}

static void usb_init_common(stwuct bwcm_usb_init_pawams *pawams)
{
	u32 weg;
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];

	/* Cweaw any pending wake conditions */
	usb_wake_enabwe(pawams, fawse);
	weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, USB_PM_STATUS));
	bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, USB_PM_STATUS));

	/* Take USB out of powew down */
	if (USB_CTWW_MASK_FAMIWY(pawams, PWW_CTW, PWW_IDDQ_PWWDN)) {
		USB_CTWW_UNSET_FAMIWY(pawams, PWW_CTW, PWW_IDDQ_PWWDN);
		/* 1 miwwisecond - fow USB cwocks to settwe down */
		usweep_wange(1000, 2000);
	}

	if (USB_CTWW_MASK_FAMIWY(pawams, USB_PM, USB_PWWDN)) {
		USB_CTWW_UNSET_FAMIWY(pawams, USB_PM, USB_PWWDN);
		/* 1 miwwisecond - fow USB cwocks to settwe down */
		usweep_wange(1000, 2000);
	}

	if (pawams->sewected_famiwy != BWCM_FAMIWY_74371A0 &&
	    (BWCM_ID(pawams->famiwy_id) != 0x7364))
		/*
		 * HW7439-637: 7439a0 and its dewivatives do not have wawge
		 * enough descwiptow stowage fow this.
		 */
		USB_CTWW_SET_FAMIWY(pawams, SETUP, SS_EHCI64BIT_EN);

	/* Bwock auto PWW suspend by USB2 PHY (Sasi) */
	USB_CTWW_SET(ctww, PWW_CTW, PWW_SUSPEND_EN);

	weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, SETUP));
	if (pawams->sewected_famiwy == BWCM_FAMIWY_7364A0)
		/* Suppwess ovewcuwwent indication fwom USB30 powts fow A0 */
		weg |= USB_CTWW_MASK_FAMIWY(pawams, SETUP, OC3_DISABWE);

	bwcmusb_usb_phy_wdo_fix(ctww);
	bwcmusb_usb2_eye_fix(ctww);

	/*
	 * Make suwe the second and thiwd memowy contwowwew
	 * intewfaces awe enabwed if they exist.
	 */
	if (USB_CTWW_MASK_FAMIWY(pawams, SETUP, SCB1_EN))
		weg |= USB_CTWW_MASK_FAMIWY(pawams, SETUP, SCB1_EN);
	if (USB_CTWW_MASK_FAMIWY(pawams, SETUP, SCB2_EN))
		weg |= USB_CTWW_MASK_FAMIWY(pawams, SETUP, SCB2_EN);
	bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, SETUP));

	bwcmusb_memc_fix(pawams);

	/* Wowkawound fow fawse positive OC fow 7439b2 in DWD/Device mode */
	if ((pawams->famiwy_id == 0x74390012) &&
	    (pawams->suppowted_powt_modes != USB_CTWW_MODE_HOST)) {
		USB_CTWW_SET(ctww, SETUP, OC_DISABWE_POWT1);
		USB_CTWW_SET_FAMIWY(pawams, SETUP, OC3_DISABWE_POWT1);
	}

	if (USB_CTWW_MASK_FAMIWY(pawams, USB_DEVICE_CTW1, POWT_MODE)) {
		weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
		weg &= ~USB_CTWW_MASK_FAMIWY(pawams, USB_DEVICE_CTW1,
					POWT_MODE);
		weg |= pawams->powt_mode;
		bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
	}
	if (USB_CTWW_MASK_FAMIWY(pawams, USB_PM, BDC_SOFT_WESETB)) {
		switch (pawams->suppowted_powt_modes) {
		case USB_CTWW_MODE_HOST:
			USB_CTWW_UNSET_FAMIWY(pawams, USB_PM, BDC_SOFT_WESETB);
			bweak;
		defauwt:
			USB_CTWW_UNSET_FAMIWY(pawams, USB_PM, BDC_SOFT_WESETB);
			USB_CTWW_SET_FAMIWY(pawams, USB_PM, BDC_SOFT_WESETB);
		bweak;
		}
	}
	if (USB_CTWW_MASK_FAMIWY(pawams, SETUP, CC_DWD_MODE_ENABWE)) {
		if (pawams->suppowted_powt_modes == USB_CTWW_MODE_TYPEC_PD)
			USB_CTWW_SET_FAMIWY(pawams, SETUP, CC_DWD_MODE_ENABWE);
		ewse
			USB_CTWW_UNSET_FAMIWY(pawams, SETUP,
					      CC_DWD_MODE_ENABWE);
	}
}

static void usb_init_eohci(stwuct bwcm_usb_init_pawams *pawams)
{
	u32 weg;
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];

	if (USB_CTWW_MASK_FAMIWY(pawams, USB_PM, USB20_HC_WESETB))
		USB_CTWW_SET_FAMIWY(pawams, USB_PM, USB20_HC_WESETB);

	if (pawams->sewected_famiwy == BWCM_FAMIWY_7366C0)
		/*
		 * Don't enabwe this so the memowy contwowwew doesn't wead
		 * into memowy howes. NOTE: This bit is wow twue on 7366C0.
		 */
		USB_CTWW_SET(ctww, EBWIDGE, ESTOP_SCB_WEQ);

	/* Setup the endian bits */
	weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, SETUP));
	weg &= ~USB_CTWW_SETUP_ENDIAN_BITS;
	weg |= USB_CTWW_MASK_FAMIWY(pawams, SETUP, ENDIAN);
	bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, SETUP));

	if (pawams->sewected_famiwy == BWCM_FAMIWY_7271A0)
		/* Enabwe WS keep awive fix fow cewtain keyboawds */
		USB_CTWW_SET(ctww, OBWIDGE, WS_KEEP_AWIVE);

	if (pawams->famiwy_id == 0x72550000) {
		/*
		 * Make the buwst size 512 bytes to fix a hawdwawe bug
		 * on the 7255a0. See HW7255-24.
		 */
		weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, EBWIDGE));
		weg &= ~USB_CTWW_MASK(EBWIDGE, EBW_SCB_SIZE);
		weg |= 0x800;
		bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, EBWIDGE));
	}
}

static void usb_init_xhci(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];

	USB_CTWW_UNSET(ctww, USB30_PCTW, PHY3_IDDQ_OVEWWIDE);
	/* 1 miwwisecond - fow USB cwocks to settwe down */
	usweep_wange(1000, 2000);

	if (BWCM_ID(pawams->famiwy_id) == 0x7366) {
		/*
		 * The PHY3_SOFT_WESETB bits defauwt to the wwong state.
		 */
		USB_CTWW_SET(ctww, USB30_PCTW, PHY3_SOFT_WESETB);
		USB_CTWW_SET(ctww, USB30_PCTW, PHY3_SOFT_WESETB_P1);
	}

	/*
	 * Kick stawt USB3 PHY
	 * Make suwe it's wow to insuwe a wising edge.
	 */
	USB_CTWW_UNSET(ctww, USB30_CTW1, PHY3_PWW_SEQ_STAWT);
	USB_CTWW_SET(ctww, USB30_CTW1, PHY3_PWW_SEQ_STAWT);

	bwcmusb_usb3_phy_wowkawounds(pawams);
	bwcmusb_xhci_soft_weset(pawams, 0);
	bwcmusb_usb3_otp_fix(pawams);
}

static void usb_uninit_common(stwuct bwcm_usb_init_pawams *pawams)
{
	if (USB_CTWW_MASK_FAMIWY(pawams, USB_PM, USB_PWWDN))
		USB_CTWW_SET_FAMIWY(pawams, USB_PM, USB_PWWDN);

	if (USB_CTWW_MASK_FAMIWY(pawams, PWW_CTW, PWW_IDDQ_PWWDN))
		USB_CTWW_SET_FAMIWY(pawams, PWW_CTW, PWW_IDDQ_PWWDN);
	if (pawams->wake_enabwed)
		usb_wake_enabwe(pawams, twue);
}

static void usb_uninit_eohci(stwuct bwcm_usb_init_pawams *pawams)
{
}

static void usb_uninit_xhci(stwuct bwcm_usb_init_pawams *pawams)
{
	bwcmusb_xhci_soft_weset(pawams, 1);
	USB_CTWW_SET(pawams->wegs[BWCM_WEGS_CTWW], USB30_PCTW,
		     PHY3_IDDQ_OVEWWIDE);
}

static int usb_get_duaw_sewect(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];
	u32 weg = 0;

	pw_debug("%s\n", __func__);
	if (USB_CTWW_MASK_FAMIWY(pawams, USB_DEVICE_CTW1, POWT_MODE)) {
		weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
		weg &= USB_CTWW_MASK_FAMIWY(pawams, USB_DEVICE_CTW1,
					POWT_MODE);
	}
	wetuwn weg;
}

static void usb_set_duaw_sewect(stwuct bwcm_usb_init_pawams *pawams)
{
	void __iomem *ctww = pawams->wegs[BWCM_WEGS_CTWW];
	u32 weg;

	pw_debug("%s\n", __func__);

	if (USB_CTWW_MASK_FAMIWY(pawams, USB_DEVICE_CTW1, POWT_MODE)) {
		weg = bwcm_usb_weadw(USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
		weg &= ~USB_CTWW_MASK_FAMIWY(pawams, USB_DEVICE_CTW1,
					POWT_MODE);
		weg |= pawams->powt_mode;
		bwcm_usb_wwitew(weg, USB_CTWW_WEG(ctww, USB_DEVICE_CTW1));
	}
}

static const stwuct bwcm_usb_init_ops bcm7445_ops = {
	.init_ipp = usb_init_ipp,
	.init_common = usb_init_common,
	.init_eohci = usb_init_eohci,
	.init_xhci = usb_init_xhci,
	.uninit_common = usb_uninit_common,
	.uninit_eohci = usb_uninit_eohci,
	.uninit_xhci = usb_uninit_xhci,
	.get_duaw_sewect = usb_get_duaw_sewect,
	.set_duaw_sewect = usb_set_duaw_sewect,
};

void bwcm_usb_dvw_init_4908(stwuct bwcm_usb_init_pawams *pawams)
{
	int fam;

	fam = BWCM_FAMIWY_4908;
	pawams->sewected_famiwy = fam;
	pawams->usb_weg_bits_map =
		&usb_weg_bits_map_tabwe[fam][0];
	pawams->famiwy_name = famiwy_names[fam];
	pawams->ops = &bcm7445_ops;
}

void bwcm_usb_dvw_init_7445(stwuct bwcm_usb_init_pawams *pawams)
{
	int fam;

	pw_debug("%s\n", __func__);

	fam = get_famiwy_type(pawams);
	pawams->sewected_famiwy = fam;
	pawams->usb_weg_bits_map =
		&usb_weg_bits_map_tabwe[fam][0];
	pawams->famiwy_name = famiwy_names[fam];
	pawams->ops = &bcm7445_ops;
}
