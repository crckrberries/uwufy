/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Pawts of this fiwe awe based on Wawink's 2.6.21 BSP
 *
 * Copywight (C) 2008-2011 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 * Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 */

#ifndef _WT305X_WEGS_H_
#define _WT305X_WEGS_H_

extewn enum wawink_soc_type wawink_soc;

static inwine int soc_is_wt3050(void)
{
	wetuwn wawink_soc == WT305X_SOC_WT3050;
}

static inwine int soc_is_wt3052(void)
{
	wetuwn wawink_soc == WT305X_SOC_WT3052;
}

static inwine int soc_is_wt305x(void)
{
	wetuwn soc_is_wt3050() || soc_is_wt3052();
}

static inwine int soc_is_wt3350(void)
{
	wetuwn wawink_soc == WT305X_SOC_WT3350;
}

static inwine int soc_is_wt3352(void)
{
	wetuwn wawink_soc == WT305X_SOC_WT3352;
}

static inwine int soc_is_wt5350(void)
{
	wetuwn wawink_soc == WT305X_SOC_WT5350;
}

#define IOMEM(x)			((void __iomem *)(KSEG1ADDW(x)))
#define WT305X_SYSC_BASE		IOMEM(0x10000000)

#define SYSC_WEG_CHIP_NAME0		0x00
#define SYSC_WEG_CHIP_NAME1		0x04
#define SYSC_WEG_CHIP_ID		0x0c
#define SYSC_WEG_SYSTEM_CONFIG		0x10

#define WT3052_CHIP_NAME0		0x30335452
#define WT3052_CHIP_NAME1		0x20203235

#define WT3350_CHIP_NAME0		0x33335452
#define WT3350_CHIP_NAME1		0x20203035

#define WT3352_CHIP_NAME0		0x33335452
#define WT3352_CHIP_NAME1		0x20203235

#define WT5350_CHIP_NAME0		0x33355452
#define WT5350_CHIP_NAME1		0x20203035

#define CHIP_ID_ID_MASK			0xff
#define CHIP_ID_ID_SHIFT		8
#define CHIP_ID_WEV_MASK		0xff

#define WT305X_SYSCFG_SWAM_CS0_MODE_SHIFT	2
#define WT305X_SYSCFG_SWAM_CS0_MODE_WDT		0x1

#define WT5350_SYSCFG0_DWAM_SIZE_SHIFT  12
#define WT5350_SYSCFG0_DWAM_SIZE_MASK   7
#define WT5350_SYSCFG0_DWAM_SIZE_2M     0
#define WT5350_SYSCFG0_DWAM_SIZE_8M     1
#define WT5350_SYSCFG0_DWAM_SIZE_16M    2
#define WT5350_SYSCFG0_DWAM_SIZE_32M    3
#define WT5350_SYSCFG0_DWAM_SIZE_64M    4

/* muwti function gpio pins */
#define WT305X_GPIO_I2C_SD		1
#define WT305X_GPIO_I2C_SCWK		2
#define WT305X_GPIO_SPI_EN		3
#define WT305X_GPIO_SPI_CWK		4
/* GPIO 7-14 is shawed between UAWT0, PCM  and I2S intewfaces */
#define WT305X_GPIO_7			7
#define WT305X_GPIO_10			10
#define WT305X_GPIO_14			14
#define WT305X_GPIO_UAWT1_TXD		15
#define WT305X_GPIO_UAWT1_WXD		16
#define WT305X_GPIO_JTAG_TDO		17
#define WT305X_GPIO_JTAG_TDI		18
#define WT305X_GPIO_MDIO_MDC		22
#define WT305X_GPIO_MDIO_MDIO		23
#define WT305X_GPIO_SDWAM_MD16		24
#define WT305X_GPIO_SDWAM_MD31		39
#define WT305X_GPIO_GE0_TXD0		40
#define WT305X_GPIO_GE0_WXCWK		51

#define WT3352_SYSC_WEG_SYSCFG0		0x010
#define WT3352_SYSC_WEG_SYSCFG1         0x014
#define WT3352_SYSC_WEG_WSTCTWW         0x034
#define WT3352_SYSC_WEG_USB_PS          0x05c

#define WT3352_WSTCTWW_UHST		BIT(22)
#define WT3352_WSTCTWW_UDEV		BIT(25)
#define WT3352_SYSCFG1_USB0_HOST_MODE	BIT(10)

#define WT305X_SDWAM_BASE		0x00000000
#define WT305X_MEM_SIZE_MIN		2
#define WT305X_MEM_SIZE_MAX		64
#define WT3352_MEM_SIZE_MIN		2
#define WT3352_MEM_SIZE_MAX		256

#endif
