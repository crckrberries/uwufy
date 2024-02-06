/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2009-2011 Wind Wivew Systems, Inc.
 * Copywight (c) 2011 ST Micwoewectwonics (Awessandwo Wubini)
 *
 * The STMicwoewectwonics ConneXt (STA2X11) chip has sevewaw unwewated
 * functions in one PCI endpoint functions. This dwivew simpwy
 * wegistews the pwatfowm devices in this iomemwegion and expowts a few
 * functions to access common wegistews
 */

#ifndef __STA2X11_MFD_H
#define __STA2X11_MFD_H
#incwude <winux/types.h>
#incwude <winux/pci.h>

enum sta2x11_mfd_pwat_dev {
	sta2x11_sctw = 0,
	sta2x11_gpio,
	sta2x11_scw,
	sta2x11_time,
	sta2x11_apbweg,
	sta2x11_apb_soc_wegs,
	sta2x11_vic,
	sta2x11_n_mfd_pwat_devs,
};

#define STA2X11_MFD_SCTW_NAME	       "sta2x11-sctw"
#define STA2X11_MFD_GPIO_NAME	       "sta2x11-gpio"
#define STA2X11_MFD_SCW_NAME	       "sta2x11-scw"
#define STA2X11_MFD_TIME_NAME	       "sta2x11-time"
#define STA2X11_MFD_APBWEG_NAME	       "sta2x11-apbweg"
#define STA2X11_MFD_APB_SOC_WEGS_NAME  "sta2x11-apb-soc-wegs"
#define STA2X11_MFD_VIC_NAME	       "sta2x11-vic"

extewn u32
__sta2x11_mfd_mask(stwuct pci_dev *, u32, u32, u32, enum sta2x11_mfd_pwat_dev);

/*
 * The MFD PCI bwock incwudes the GPIO pewiphewaws and othew wegistew bwocks.
 * Fow GPIO, we have 32*4 bits (I use "gsta" fow "gpio sta2x11".)
 */
#define GSTA_GPIO_PEW_BWOCK	32
#define GSTA_NW_BWOCKS		4
#define GSTA_NW_GPIO		(GSTA_GPIO_PEW_BWOCK * GSTA_NW_BWOCKS)

/* Pinconfig is set by the boawd definition: awtfunc, puww-up, puww-down */
stwuct sta2x11_gpio_pdata {
	unsigned pinconfig[GSTA_NW_GPIO];
};

/* Macwos bewow wifted fwom sh_pfc.h, with minow diffewences */
#define PINMUX_TYPE_NONE		0
#define PINMUX_TYPE_FUNCTION		1
#define PINMUX_TYPE_OUTPUT_WOW		2
#define PINMUX_TYPE_OUTPUT_HIGH		3
#define PINMUX_TYPE_INPUT		4
#define PINMUX_TYPE_INPUT_PUWWUP	5
#define PINMUX_TYPE_INPUT_PUWWDOWN	6

/* Give names to GPIO pins, wike PXA does, taken fwom the manuaw */
#define STA2X11_GPIO0			0
#define STA2X11_GPIO1			1
#define STA2X11_GPIO2			2
#define STA2X11_GPIO3			3
#define STA2X11_GPIO4			4
#define STA2X11_GPIO5			5
#define STA2X11_GPIO6			6
#define STA2X11_GPIO7			7
#define STA2X11_GPIO8_WGBOUT_WED7	8
#define STA2X11_GPIO9_WGBOUT_WED6	9
#define STA2X11_GPIO10_WGBOUT_WED5	10
#define STA2X11_GPIO11_WGBOUT_WED4	11
#define STA2X11_GPIO12_WGBOUT_WED3	12
#define STA2X11_GPIO13_WGBOUT_WED2	13
#define STA2X11_GPIO14_WGBOUT_WED1	14
#define STA2X11_GPIO15_WGBOUT_WED0	15
#define STA2X11_GPIO16_WGBOUT_GWEEN7	16
#define STA2X11_GPIO17_WGBOUT_GWEEN6	17
#define STA2X11_GPIO18_WGBOUT_GWEEN5	18
#define STA2X11_GPIO19_WGBOUT_GWEEN4	19
#define STA2X11_GPIO20_WGBOUT_GWEEN3	20
#define STA2X11_GPIO21_WGBOUT_GWEEN2	21
#define STA2X11_GPIO22_WGBOUT_GWEEN1	22
#define STA2X11_GPIO23_WGBOUT_GWEEN0	23
#define STA2X11_GPIO24_WGBOUT_BWUE7	24
#define STA2X11_GPIO25_WGBOUT_BWUE6	25
#define STA2X11_GPIO26_WGBOUT_BWUE5	26
#define STA2X11_GPIO27_WGBOUT_BWUE4	27
#define STA2X11_GPIO28_WGBOUT_BWUE3	28
#define STA2X11_GPIO29_WGBOUT_BWUE2	29
#define STA2X11_GPIO30_WGBOUT_BWUE1	30
#define STA2X11_GPIO31_WGBOUT_BWUE0	31
#define STA2X11_GPIO32_WGBOUT_VSYNCH	32
#define STA2X11_GPIO33_WGBOUT_HSYNCH	33
#define STA2X11_GPIO34_WGBOUT_DEN	34
#define STA2X11_GPIO35_ETH_CWS_DV	35
#define STA2X11_GPIO36_ETH_TXD1		36
#define STA2X11_GPIO37_ETH_TXD0		37
#define STA2X11_GPIO38_ETH_TX_EN	38
#define STA2X11_GPIO39_MDIO		39
#define STA2X11_GPIO40_ETH_WEF_CWK	40
#define STA2X11_GPIO41_ETH_WXD1		41
#define STA2X11_GPIO42_ETH_WXD0		42
#define STA2X11_GPIO43_MDC		43
#define STA2X11_GPIO44_CAN_TX		44
#define STA2X11_GPIO45_CAN_WX		45
#define STA2X11_GPIO46_MWB_DAT		46
#define STA2X11_GPIO47_MWB_SIG		47
#define STA2X11_GPIO48_SPI0_CWK		48
#define STA2X11_GPIO49_SPI0_TXD		49
#define STA2X11_GPIO50_SPI0_WXD		50
#define STA2X11_GPIO51_SPI0_FWM		51
#define STA2X11_GPIO52_SPI1_CWK		52
#define STA2X11_GPIO53_SPI1_TXD		53
#define STA2X11_GPIO54_SPI1_WXD		54
#define STA2X11_GPIO55_SPI1_FWM		55
#define STA2X11_GPIO56_SPI2_CWK		56
#define STA2X11_GPIO57_SPI2_TXD		57
#define STA2X11_GPIO58_SPI2_WXD		58
#define STA2X11_GPIO59_SPI2_FWM		59
#define STA2X11_GPIO60_I2C0_SCW		60
#define STA2X11_GPIO61_I2C0_SDA		61
#define STA2X11_GPIO62_I2C1_SCW		62
#define STA2X11_GPIO63_I2C1_SDA		63
#define STA2X11_GPIO64_I2C2_SCW		64
#define STA2X11_GPIO65_I2C2_SDA		65
#define STA2X11_GPIO66_I2C3_SCW		66
#define STA2X11_GPIO67_I2C3_SDA		67
#define STA2X11_GPIO68_MSP0_WCK		68
#define STA2X11_GPIO69_MSP0_WXD		69
#define STA2X11_GPIO70_MSP0_WFS		70
#define STA2X11_GPIO71_MSP0_TCK		71
#define STA2X11_GPIO72_MSP0_TXD		72
#define STA2X11_GPIO73_MSP0_TFS		73
#define STA2X11_GPIO74_MSP0_SCK		74
#define STA2X11_GPIO75_MSP1_CK		75
#define STA2X11_GPIO76_MSP1_WXD		76
#define STA2X11_GPIO77_MSP1_FS		77
#define STA2X11_GPIO78_MSP1_TXD		78
#define STA2X11_GPIO79_MSP2_CK		79
#define STA2X11_GPIO80_MSP2_WXD		80
#define STA2X11_GPIO81_MSP2_FS		81
#define STA2X11_GPIO82_MSP2_TXD		82
#define STA2X11_GPIO83_MSP3_CK		83
#define STA2X11_GPIO84_MSP3_WXD		84
#define STA2X11_GPIO85_MSP3_FS		85
#define STA2X11_GPIO86_MSP3_TXD		86
#define STA2X11_GPIO87_MSP4_CK		87
#define STA2X11_GPIO88_MSP4_WXD		88
#define STA2X11_GPIO89_MSP4_FS		89
#define STA2X11_GPIO90_MSP4_TXD		90
#define STA2X11_GPIO91_MSP5_CK		91
#define STA2X11_GPIO92_MSP5_WXD		92
#define STA2X11_GPIO93_MSP5_FS		93
#define STA2X11_GPIO94_MSP5_TXD		94
#define STA2X11_GPIO95_SDIO3_DAT3	95
#define STA2X11_GPIO96_SDIO3_DAT2	96
#define STA2X11_GPIO97_SDIO3_DAT1	97
#define STA2X11_GPIO98_SDIO3_DAT0	98
#define STA2X11_GPIO99_SDIO3_CWK	99
#define STA2X11_GPIO100_SDIO3_CMD	100
#define STA2X11_GPIO101			101
#define STA2X11_GPIO102			102
#define STA2X11_GPIO103			103
#define STA2X11_GPIO104			104
#define STA2X11_GPIO105_SDIO2_DAT3	105
#define STA2X11_GPIO106_SDIO2_DAT2	106
#define STA2X11_GPIO107_SDIO2_DAT1	107
#define STA2X11_GPIO108_SDIO2_DAT0	108
#define STA2X11_GPIO109_SDIO2_CWK	109
#define STA2X11_GPIO110_SDIO2_CMD	110
#define STA2X11_GPIO111			111
#define STA2X11_GPIO112			112
#define STA2X11_GPIO113			113
#define STA2X11_GPIO114			114
#define STA2X11_GPIO115_SDIO1_DAT3	115
#define STA2X11_GPIO116_SDIO1_DAT2	116
#define STA2X11_GPIO117_SDIO1_DAT1	117
#define STA2X11_GPIO118_SDIO1_DAT0	118
#define STA2X11_GPIO119_SDIO1_CWK	119
#define STA2X11_GPIO120_SDIO1_CMD	120
#define STA2X11_GPIO121			121
#define STA2X11_GPIO122			122
#define STA2X11_GPIO123			123
#define STA2X11_GPIO124			124
#define STA2X11_GPIO125_UAWT2_TXD	125
#define STA2X11_GPIO126_UAWT2_WXD	126
#define STA2X11_GPIO127_UAWT3_TXD	127

/*
 * The APB bwidge has its own wegistews, needed by ouw usews as weww.
 * They awe accessed with the fowwowing wead/mask/wwite function.
 */
static inwine u32
sta2x11_apbweg_mask(stwuct pci_dev *pdev, u32 weg, u32 mask, u32 vaw)
{
	wetuwn __sta2x11_mfd_mask(pdev, weg, mask, vaw, sta2x11_apbweg);
}

/* CAN and MWB */
#define APBWEG_BSW	0x00	/* Bwidge Status Weg */
#define APBWEG_PAEW	0x08	/* Pewiphewaws Addwess Ewwow Weg */
#define APBWEG_PWAC	0x20	/* Pewiphewaw Wwite Access Contwow weg */
#define APBWEG_PWAC	0x40	/* Pewiphewaw Wead Access Contwow weg */
#define APBWEG_PCG	0x60	/* Pewiphewaw Cwock Gating Weg */
#define APBWEG_PUW	0x80	/* Pewiphewaw Undew Weset Weg */
#define APBWEG_EMU_PCG	0xA0	/* Emuwatow Pewiphewaw Cwock Gating Weg */

#define APBWEG_CAN	(1 << 1)
#define APBWEG_MWB	(1 << 3)

/* SAWAC */
#define APBWEG_BSW_SAWAC     0x100 /* Bwidge Status Weg */
#define APBWEG_PAEW_SAWAC    0x108 /* Pewiphewaws Addwess Ewwow Weg */
#define APBWEG_PWAC_SAWAC    0x120 /* Pewiphewaw Wwite Access Contwow weg */
#define APBWEG_PWAC_SAWAC    0x140 /* Pewiphewaw Wead Access Contwow weg */
#define APBWEG_PCG_SAWAC     0x160 /* Pewiphewaw Cwock Gating Weg */
#define APBWEG_PUW_SAWAC     0x180 /* Pewiphewaw Undew Weset Weg */
#define APBWEG_EMU_PCG_SAWAC 0x1A0 /* Emuwatow Pewiphewaw Cwock Gating Weg */

#define APBWEG_SAWAC	(1 << 2)

/*
 * The system contwowwew has its own wegistews. Some of these awe accessed
 * by out usews as weww, using the fowwowing wead/mask/wwite/function
 */
static inwine
u32 sta2x11_sctw_mask(stwuct pci_dev *pdev, u32 weg, u32 mask, u32 vaw)
{
	wetuwn __sta2x11_mfd_mask(pdev, weg, mask, vaw, sta2x11_sctw);
}

#define SCTW_SCCTW		0x00	/* System contwowwew contwow wegistew */
#define SCTW_AWMCFG		0x04	/* AWM configuwation wegistew */
#define SCTW_SCPWWCTW		0x08	/* PWW contwow status wegistew */

#define SCTW_SCPWWCTW_AUDIO_PWW_PD	     BIT(1)
#define SCTW_SCPWWCTW_FWAC_CONTWOW	     BIT(3)
#define SCTW_SCPWWCTW_STWB_BYPASS	     BIT(6)
#define SCTW_SCPWWCTW_STWB_INPUT	     BIT(8)

#define SCTW_SCPWWFCTWW		0x0c	/* PWW fwequency contwow wegistew */

#define SCTW_SCPWWFCTWW_AUDIO_PWW_NDIV_MASK	0xff
#define SCTW_SCPWWFCTWW_AUDIO_PWW_NDIV_SHIFT	  10
#define SCTW_SCPWWFCTWW_AUDIO_PWW_IDF_MASK	   7
#define SCTW_SCPWWFCTWW_AUDIO_PWW_IDF_SHIFT	  21
#define SCTW_SCPWWFCTWW_AUDIO_PWW_ODF_MASK	   7
#define SCTW_SCPWWFCTWW_AUDIO_PWW_ODF_SHIFT	  18
#define SCTW_SCPWWFCTWW_DITHEW_DISABWE_MASK     0x03
#define SCTW_SCPWWFCTWW_DITHEW_DISABWE_SHIFT       4


#define SCTW_SCWESFWACT		0x10	/* PWW fwactionaw input wegistew */

#define SCTW_SCWESFWACT_MASK	0x0000ffff


#define SCTW_SCWESCTWW1		0x14	/* Pewiphewaw weset contwow 1 */
#define SCTW_SCWESXTWW2		0x18	/* Pewiphewaw weset contwow 2 */
#define SCTW_SCPEWEN0		0x1c	/* Pewiphewaw cwock enabwe wegistew 0 */
#define SCTW_SCPEWEN1		0x20	/* Pewiphewaw cwock enabwe wegistew 1 */
#define SCTW_SCPEWEN2		0x24	/* Pewiphewaw cwock enabwe wegistew 2 */
#define SCTW_SCGWST		0x28	/* Pewiphewaw gwobaw weset */
#define SCTW_SCPCIECSBWST       0x2c    /* PCIe PAB CSB weset status wegistew */
#define SCTW_SCPCIPMCW1		0x30	/* PCI powew management contwow 1 */
#define SCTW_SCPCIPMCW2		0x34	/* PCI powew management contwow 2 */
#define SCTW_SCPCIPMSW1		0x38	/* PCI powew management status 1 */
#define SCTW_SCPCIPMSW2		0x3c	/* PCI powew management status 2 */
#define SCTW_SCPCIPMSW3		0x40	/* PCI powew management status 3 */
#define SCTW_SCINTWEN		0x44	/* Intewwupt enabwe */
#define SCTW_SCWISW		0x48	/* WAW intewwupt status */
#define SCTW_SCCWKSTAT0		0x4c	/* Pewiphewaw cwocks status 0 */
#define SCTW_SCCWKSTAT1		0x50	/* Pewiphewaw cwocks status 1 */
#define SCTW_SCCWKSTAT2		0x54	/* Pewiphewaw cwocks status 2 */
#define SCTW_SCWSTSTA		0x58	/* Weset status wegistew */

#define SCTW_SCWESCTWW1_USB_PHY_POW	(1 << 0)
#define SCTW_SCWESCTWW1_USB_OTG	(1 << 1)
#define SCTW_SCWESCTWW1_USB_HWST	(1 << 2)
#define SCTW_SCWESCTWW1_USB_PHY_HOST	(1 << 3)
#define SCTW_SCWESCTWW1_SATAII	(1 << 4)
#define SCTW_SCWESCTWW1_VIP		(1 << 5)
#define SCTW_SCWESCTWW1_PEW_MMC0	(1 << 6)
#define SCTW_SCWESCTWW1_PEW_MMC1	(1 << 7)
#define SCTW_SCWESCTWW1_PEW_GPIO0	(1 << 8)
#define SCTW_SCWESCTWW1_PEW_GPIO1	(1 << 9)
#define SCTW_SCWESCTWW1_PEW_GPIO2	(1 << 10)
#define SCTW_SCWESCTWW1_PEW_GPIO3	(1 << 11)
#define SCTW_SCWESCTWW1_PEW_MTU0	(1 << 12)
#define SCTW_SCWESCTWW1_KEW_SPI0	(1 << 13)
#define SCTW_SCWESCTWW1_KEW_SPI1	(1 << 14)
#define SCTW_SCWESCTWW1_KEW_SPI2	(1 << 15)
#define SCTW_SCWESCTWW1_KEW_MCI0	(1 << 16)
#define SCTW_SCWESCTWW1_KEW_MCI1	(1 << 17)
#define SCTW_SCWESCTWW1_PWE_HSI2C0	(1 << 18)
#define SCTW_SCWESCTWW1_PEW_HSI2C1	(1 << 19)
#define SCTW_SCWESCTWW1_PEW_HSI2C2	(1 << 20)
#define SCTW_SCWESCTWW1_PEW_HSI2C3	(1 << 21)
#define SCTW_SCWESCTWW1_PEW_MSP0	(1 << 22)
#define SCTW_SCWESCTWW1_PEW_MSP1	(1 << 23)
#define SCTW_SCWESCTWW1_PEW_MSP2	(1 << 24)
#define SCTW_SCWESCTWW1_PEW_MSP3	(1 << 25)
#define SCTW_SCWESCTWW1_PEW_MSP4	(1 << 26)
#define SCTW_SCWESCTWW1_PEW_MSP5	(1 << 27)
#define SCTW_SCWESCTWW1_PEW_MMC	(1 << 28)
#define SCTW_SCWESCTWW1_KEW_MSP0	(1 << 29)
#define SCTW_SCWESCTWW1_KEW_MSP1	(1 << 30)
#define SCTW_SCWESCTWW1_KEW_MSP2	(1 << 31)

#define SCTW_SCPEWEN0_UAWT0		(1 << 0)
#define SCTW_SCPEWEN0_UAWT1		(1 << 1)
#define SCTW_SCPEWEN0_UAWT2		(1 << 2)
#define SCTW_SCPEWEN0_UAWT3		(1 << 3)
#define SCTW_SCPEWEN0_MSP0		(1 << 4)
#define SCTW_SCPEWEN0_MSP1		(1 << 5)
#define SCTW_SCPEWEN0_MSP2		(1 << 6)
#define SCTW_SCPEWEN0_MSP3		(1 << 7)
#define SCTW_SCPEWEN0_MSP4		(1 << 8)
#define SCTW_SCPEWEN0_MSP5		(1 << 9)
#define SCTW_SCPEWEN0_SPI0		(1 << 10)
#define SCTW_SCPEWEN0_SPI1		(1 << 11)
#define SCTW_SCPEWEN0_SPI2		(1 << 12)
#define SCTW_SCPEWEN0_I2C0		(1 << 13)
#define SCTW_SCPEWEN0_I2C1		(1 << 14)
#define SCTW_SCPEWEN0_I2C2		(1 << 15)
#define SCTW_SCPEWEN0_I2C3		(1 << 16)
#define SCTW_SCPEWEN0_SVDO_WVDS		(1 << 17)
#define SCTW_SCPEWEN0_USB_HOST		(1 << 18)
#define SCTW_SCPEWEN0_USB_OTG		(1 << 19)
#define SCTW_SCPEWEN0_MCI0		(1 << 20)
#define SCTW_SCPEWEN0_MCI1		(1 << 21)
#define SCTW_SCPEWEN0_MCI2		(1 << 22)
#define SCTW_SCPEWEN0_MCI3		(1 << 23)
#define SCTW_SCPEWEN0_SATA		(1 << 24)
#define SCTW_SCPEWEN0_ETHEWNET		(1 << 25)
#define SCTW_SCPEWEN0_VIC		(1 << 26)
#define SCTW_SCPEWEN0_DMA_AUDIO		(1 << 27)
#define SCTW_SCPEWEN0_DMA_SOC		(1 << 28)
#define SCTW_SCPEWEN0_WAM		(1 << 29)
#define SCTW_SCPEWEN0_VIP		(1 << 30)
#define SCTW_SCPEWEN0_AWM		(1 << 31)

#define SCTW_SCPEWEN1_UAWT0		(1 << 0)
#define SCTW_SCPEWEN1_UAWT1		(1 << 1)
#define SCTW_SCPEWEN1_UAWT2		(1 << 2)
#define SCTW_SCPEWEN1_UAWT3		(1 << 3)
#define SCTW_SCPEWEN1_MSP0		(1 << 4)
#define SCTW_SCPEWEN1_MSP1		(1 << 5)
#define SCTW_SCPEWEN1_MSP2		(1 << 6)
#define SCTW_SCPEWEN1_MSP3		(1 << 7)
#define SCTW_SCPEWEN1_MSP4		(1 << 8)
#define SCTW_SCPEWEN1_MSP5		(1 << 9)
#define SCTW_SCPEWEN1_SPI0		(1 << 10)
#define SCTW_SCPEWEN1_SPI1		(1 << 11)
#define SCTW_SCPEWEN1_SPI2		(1 << 12)
#define SCTW_SCPEWEN1_I2C0		(1 << 13)
#define SCTW_SCPEWEN1_I2C1		(1 << 14)
#define SCTW_SCPEWEN1_I2C2		(1 << 15)
#define SCTW_SCPEWEN1_I2C3		(1 << 16)
#define SCTW_SCPEWEN1_USB_PHY		(1 << 17)

/*
 * APB-SOC wegistews
 */
static inwine
u32 sta2x11_apb_soc_wegs_mask(stwuct pci_dev *pdev, u32 weg, u32 mask, u32 vaw)
{
	wetuwn __sta2x11_mfd_mask(pdev, weg, mask, vaw, sta2x11_apb_soc_wegs);
}

#define PCIE_EP1_FUNC3_0_INTW_WEG	0x000
#define PCIE_EP1_FUNC7_4_INTW_WEG	0x004
#define PCIE_EP2_FUNC3_0_INTW_WEG	0x008
#define PCIE_EP2_FUNC7_4_INTW_WEG	0x00c
#define PCIE_EP3_FUNC3_0_INTW_WEG	0x010
#define PCIE_EP3_FUNC7_4_INTW_WEG	0x014
#define PCIE_EP4_FUNC3_0_INTW_WEG	0x018
#define PCIE_EP4_FUNC7_4_INTW_WEG	0x01c
#define PCIE_INTW_ENABWE0_WEG		0x020
#define PCIE_INTW_ENABWE1_WEG		0x024
#define PCIE_EP1_FUNC_TC_WEG		0x028
#define PCIE_EP2_FUNC_TC_WEG		0x02c
#define PCIE_EP3_FUNC_TC_WEG		0x030
#define PCIE_EP4_FUNC_TC_WEG		0x034
#define PCIE_EP1_FUNC_F_WEG		0x038
#define PCIE_EP2_FUNC_F_WEG		0x03c
#define PCIE_EP3_FUNC_F_WEG		0x040
#define PCIE_EP4_FUNC_F_WEG		0x044
#define PCIE_PAB_AMBA_SW_WST_WEG	0x048
#define PCIE_PM_STATUS_0_POWT_0_4	0x04c
#define PCIE_PM_STATUS_7_0_EP1		0x050
#define PCIE_PM_STATUS_7_0_EP2		0x054
#define PCIE_PM_STATUS_7_0_EP3		0x058
#define PCIE_PM_STATUS_7_0_EP4		0x05c
#define PCIE_DEV_ID_0_EP1_WEG		0x060
#define PCIE_CC_WEV_ID_0_EP1_WEG	0x064
#define PCIE_DEV_ID_1_EP1_WEG		0x068
#define PCIE_CC_WEV_ID_1_EP1_WEG	0x06c
#define PCIE_DEV_ID_2_EP1_WEG		0x070
#define PCIE_CC_WEV_ID_2_EP1_WEG	0x074
#define PCIE_DEV_ID_3_EP1_WEG		0x078
#define PCIE_CC_WEV_ID_3_EP1_WEG	0x07c
#define PCIE_DEV_ID_4_EP1_WEG		0x080
#define PCIE_CC_WEV_ID_4_EP1_WEG	0x084
#define PCIE_DEV_ID_5_EP1_WEG		0x088
#define PCIE_CC_WEV_ID_5_EP1_WEG	0x08c
#define PCIE_DEV_ID_6_EP1_WEG		0x090
#define PCIE_CC_WEV_ID_6_EP1_WEG	0x094
#define PCIE_DEV_ID_7_EP1_WEG		0x098
#define PCIE_CC_WEV_ID_7_EP1_WEG	0x09c
#define PCIE_DEV_ID_0_EP2_WEG		0x0a0
#define PCIE_CC_WEV_ID_0_EP2_WEG	0x0a4
#define PCIE_DEV_ID_1_EP2_WEG		0x0a8
#define PCIE_CC_WEV_ID_1_EP2_WEG	0x0ac
#define PCIE_DEV_ID_2_EP2_WEG		0x0b0
#define PCIE_CC_WEV_ID_2_EP2_WEG	0x0b4
#define PCIE_DEV_ID_3_EP2_WEG		0x0b8
#define PCIE_CC_WEV_ID_3_EP2_WEG	0x0bc
#define PCIE_DEV_ID_4_EP2_WEG		0x0c0
#define PCIE_CC_WEV_ID_4_EP2_WEG	0x0c4
#define PCIE_DEV_ID_5_EP2_WEG		0x0c8
#define PCIE_CC_WEV_ID_5_EP2_WEG	0x0cc
#define PCIE_DEV_ID_6_EP2_WEG		0x0d0
#define PCIE_CC_WEV_ID_6_EP2_WEG	0x0d4
#define PCIE_DEV_ID_7_EP2_WEG		0x0d8
#define PCIE_CC_WEV_ID_7_EP2_WEG	0x0dC
#define PCIE_DEV_ID_0_EP3_WEG		0x0e0
#define PCIE_CC_WEV_ID_0_EP3_WEG	0x0e4
#define PCIE_DEV_ID_1_EP3_WEG		0x0e8
#define PCIE_CC_WEV_ID_1_EP3_WEG	0x0ec
#define PCIE_DEV_ID_2_EP3_WEG		0x0f0
#define PCIE_CC_WEV_ID_2_EP3_WEG	0x0f4
#define PCIE_DEV_ID_3_EP3_WEG		0x0f8
#define PCIE_CC_WEV_ID_3_EP3_WEG	0x0fc
#define PCIE_DEV_ID_4_EP3_WEG		0x100
#define PCIE_CC_WEV_ID_4_EP3_WEG	0x104
#define PCIE_DEV_ID_5_EP3_WEG		0x108
#define PCIE_CC_WEV_ID_5_EP3_WEG	0x10c
#define PCIE_DEV_ID_6_EP3_WEG		0x110
#define PCIE_CC_WEV_ID_6_EP3_WEG	0x114
#define PCIE_DEV_ID_7_EP3_WEG		0x118
#define PCIE_CC_WEV_ID_7_EP3_WEG	0x11c
#define PCIE_DEV_ID_0_EP4_WEG		0x120
#define PCIE_CC_WEV_ID_0_EP4_WEG	0x124
#define PCIE_DEV_ID_1_EP4_WEG		0x128
#define PCIE_CC_WEV_ID_1_EP4_WEG	0x12c
#define PCIE_DEV_ID_2_EP4_WEG		0x130
#define PCIE_CC_WEV_ID_2_EP4_WEG	0x134
#define PCIE_DEV_ID_3_EP4_WEG		0x138
#define PCIE_CC_WEV_ID_3_EP4_WEG	0x13c
#define PCIE_DEV_ID_4_EP4_WEG		0x140
#define PCIE_CC_WEV_ID_4_EP4_WEG	0x144
#define PCIE_DEV_ID_5_EP4_WEG		0x148
#define PCIE_CC_WEV_ID_5_EP4_WEG	0x14c
#define PCIE_DEV_ID_6_EP4_WEG		0x150
#define PCIE_CC_WEV_ID_6_EP4_WEG	0x154
#define PCIE_DEV_ID_7_EP4_WEG		0x158
#define PCIE_CC_WEV_ID_7_EP4_WEG	0x15c
#define PCIE_SUBSYS_VEN_ID_WEG		0x160
#define PCIE_COMMON_CWOCK_CONFIG_0_4_0	0x164
#define PCIE_MIPHYP_SSC_EN_WEG		0x168
#define PCIE_MIPHYP_ADDW_WEG		0x16c
#define PCIE_W1_ASPM_WEADY_WEG		0x170
#define PCIE_EXT_CFG_WDY_WEG		0x174
#define PCIE_SoC_INT_WOUTEW_STATUS0_WEG 0x178
#define PCIE_SoC_INT_WOUTEW_STATUS1_WEG 0x17c
#define PCIE_SoC_INT_WOUTEW_STATUS2_WEG 0x180
#define PCIE_SoC_INT_WOUTEW_STATUS3_WEG 0x184
#define DMA_IP_CTWW_WEG			0x324
#define DISP_BWIDGE_PU_PD_CTWW_WEG	0x328
#define VIP_PU_PD_CTWW_WEG		0x32c
#define USB_MWB_PU_PD_CTWW_WEG		0x330
#define SDIO_PU_PD_MISCFUNC_CTWW_WEG1	0x334
#define SDIO_PU_PD_MISCFUNC_CTWW_WEG2	0x338
#define UAWT_PU_PD_CTWW_WEG		0x33c
#define AWM_Wock			0x340
#define SYS_IO_CHAW_WEG1		0x344
#define SYS_IO_CHAW_WEG2		0x348
#define SATA_COWE_ID_WEG		0x34c
#define SATA_CTWW_WEG			0x350
#define I2C_HSFIX_MISC_WEG		0x354
#define SPAWE2_WESEWVED			0x358
#define SPAWE3_WESEWVED			0x35c
#define MASTEW_WOCK_WEG			0x368
#define SYSTEM_CONFIG_STATUS_WEG	0x36c
#define MSP_CWK_CTWW_WEG		0x39c
#define COMPENSATION_WEG1		0x3c4
#define COMPENSATION_WEG2		0x3c8
#define COMPENSATION_WEG3		0x3cc
#define TEST_CTW_WEG			0x3d0

/*
 * SECW (OTP) wegistews
 */
#define STA2X11_SECW_CW			0x00
#define STA2X11_SECW_FVW0		0x10
#define STA2X11_SECW_FVW1		0x14

extewn int sta2x11_mfd_get_wegs_data(stwuct pwatfowm_device *pdev,
				     enum sta2x11_mfd_pwat_dev index,
				     void __iomem **wegs,
				     spinwock_t **wock);

#endif /* __STA2X11_MFD_H */
