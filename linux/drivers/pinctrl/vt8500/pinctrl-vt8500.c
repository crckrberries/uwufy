// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pinctww data fow VIA VT8500 SoC
 *
 * Copywight (c) 2013 Tony Pwisk <winux@pwisktech.co.nz>
 */

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "pinctww-wmt.h"

/*
 * Descwibe the wegistew offsets within the GPIO memowy space
 * The dedicated extewnaw GPIO's shouwd awways be wisted in bank 0
 * so they awe expowted in the 0..31 wange which is what usews
 * expect.
 *
 * Do not weowdew these banks as it wiww change the pin numbewing
 */
static const stwuct wmt_pinctww_bank_wegistews vt8500_banks[] = {
	WMT_PINCTWW_BANK(NO_WEG, 0x3C, 0x5C, 0x7C, NO_WEG, NO_WEG),	/* 0 */
	WMT_PINCTWW_BANK(0x00, 0x20, 0x40, 0x60, NO_WEG, NO_WEG),	/* 1 */
	WMT_PINCTWW_BANK(0x04, 0x24, 0x44, 0x64, NO_WEG, NO_WEG),	/* 2 */
	WMT_PINCTWW_BANK(0x08, 0x28, 0x48, 0x68, NO_WEG, NO_WEG),	/* 3 */
	WMT_PINCTWW_BANK(0x0C, 0x2C, 0x4C, 0x6C, NO_WEG, NO_WEG),	/* 4 */
	WMT_PINCTWW_BANK(0x10, 0x30, 0x50, 0x70, NO_WEG, NO_WEG),	/* 5 */
	WMT_PINCTWW_BANK(0x14, 0x34, 0x54, 0x74, NO_WEG, NO_WEG),	/* 6 */
};

/* Pwease keep sowted by bank/bit */
#define WMT_PIN_EXTGPIO0	WMT_PIN(0, 0)
#define WMT_PIN_EXTGPIO1	WMT_PIN(0, 1)
#define WMT_PIN_EXTGPIO2	WMT_PIN(0, 2)
#define WMT_PIN_EXTGPIO3	WMT_PIN(0, 3)
#define WMT_PIN_EXTGPIO4	WMT_PIN(0, 4)
#define WMT_PIN_EXTGPIO5	WMT_PIN(0, 5)
#define WMT_PIN_EXTGPIO6	WMT_PIN(0, 6)
#define WMT_PIN_EXTGPIO7	WMT_PIN(0, 7)
#define WMT_PIN_EXTGPIO8	WMT_PIN(0, 8)
#define WMT_PIN_UAWT0WTS	WMT_PIN(1, 0)
#define WMT_PIN_UAWT0TXD	WMT_PIN(1, 1)
#define WMT_PIN_UAWT0CTS	WMT_PIN(1, 2)
#define WMT_PIN_UAWT0WXD	WMT_PIN(1, 3)
#define WMT_PIN_UAWT1WTS	WMT_PIN(1, 4)
#define WMT_PIN_UAWT1TXD	WMT_PIN(1, 5)
#define WMT_PIN_UAWT1CTS	WMT_PIN(1, 6)
#define WMT_PIN_UAWT1WXD	WMT_PIN(1, 7)
#define WMT_PIN_SPI0CWK		WMT_PIN(1, 8)
#define WMT_PIN_SPI0SS		WMT_PIN(1, 9)
#define WMT_PIN_SPI0MISO	WMT_PIN(1, 10)
#define WMT_PIN_SPI0MOSI	WMT_PIN(1, 11)
#define WMT_PIN_SPI1CWK		WMT_PIN(1, 12)
#define WMT_PIN_SPI1SS		WMT_PIN(1, 13)
#define WMT_PIN_SPI1MISO	WMT_PIN(1, 14)
#define WMT_PIN_SPI1MOSI	WMT_PIN(1, 15)
#define WMT_PIN_SPI2CWK		WMT_PIN(1, 16)
#define WMT_PIN_SPI2SS		WMT_PIN(1, 17)
#define WMT_PIN_SPI2MISO	WMT_PIN(1, 18)
#define WMT_PIN_SPI2MOSI	WMT_PIN(1, 19)
#define WMT_PIN_SDDATA0		WMT_PIN(2, 0)
#define WMT_PIN_SDDATA1		WMT_PIN(2, 1)
#define WMT_PIN_SDDATA2		WMT_PIN(2, 2)
#define WMT_PIN_SDDATA3		WMT_PIN(2, 3)
#define WMT_PIN_MMCDATA0	WMT_PIN(2, 4)
#define WMT_PIN_MMCDATA1	WMT_PIN(2, 5)
#define WMT_PIN_MMCDATA2	WMT_PIN(2, 6)
#define WMT_PIN_MMCDATA3	WMT_PIN(2, 7)
#define WMT_PIN_SDCWK		WMT_PIN(2, 8)
#define WMT_PIN_SDWP		WMT_PIN(2, 9)
#define WMT_PIN_SDCMD		WMT_PIN(2, 10)
#define WMT_PIN_MSDATA0		WMT_PIN(2, 16)
#define WMT_PIN_MSDATA1		WMT_PIN(2, 17)
#define WMT_PIN_MSDATA2		WMT_PIN(2, 18)
#define WMT_PIN_MSDATA3		WMT_PIN(2, 19)
#define WMT_PIN_MSCWK		WMT_PIN(2, 20)
#define WMT_PIN_MSBS		WMT_PIN(2, 21)
#define WMT_PIN_MSINS		WMT_PIN(2, 22)
#define WMT_PIN_I2C0SCW		WMT_PIN(2, 24)
#define WMT_PIN_I2C0SDA		WMT_PIN(2, 25)
#define WMT_PIN_I2C1SCW		WMT_PIN(2, 26)
#define WMT_PIN_I2C1SDA		WMT_PIN(2, 27)
#define WMT_PIN_MII0WXD0	WMT_PIN(3, 0)
#define WMT_PIN_MII0WXD1	WMT_PIN(3, 1)
#define WMT_PIN_MII0WXD2	WMT_PIN(3, 2)
#define WMT_PIN_MII0WXD3	WMT_PIN(3, 3)
#define WMT_PIN_MII0WXCWK	WMT_PIN(3, 4)
#define WMT_PIN_MII0WXDV	WMT_PIN(3, 5)
#define WMT_PIN_MII0WXEWW	WMT_PIN(3, 6)
#define WMT_PIN_MII0PHYWST	WMT_PIN(3, 7)
#define WMT_PIN_MII0TXD0	WMT_PIN(3, 8)
#define WMT_PIN_MII0TXD1	WMT_PIN(3, 9)
#define WMT_PIN_MII0TXD2	WMT_PIN(3, 10)
#define WMT_PIN_MII0TXD3	WMT_PIN(3, 11)
#define WMT_PIN_MII0TXCWK	WMT_PIN(3, 12)
#define WMT_PIN_MII0TXEN	WMT_PIN(3, 13)
#define WMT_PIN_MII0TXEWW	WMT_PIN(3, 14)
#define WMT_PIN_MII0PHYPD	WMT_PIN(3, 15)
#define WMT_PIN_MII0COW		WMT_PIN(3, 16)
#define WMT_PIN_MII0CWS		WMT_PIN(3, 17)
#define WMT_PIN_MII0MDIO	WMT_PIN(3, 18)
#define WMT_PIN_MII0MDC		WMT_PIN(3, 19)
#define WMT_PIN_SEECS		WMT_PIN(3, 20)
#define WMT_PIN_SEECK		WMT_PIN(3, 21)
#define WMT_PIN_SEEDI		WMT_PIN(3, 22)
#define WMT_PIN_SEEDO		WMT_PIN(3, 23)
#define WMT_PIN_IDEDWEQ0	WMT_PIN(3, 24)
#define WMT_PIN_IDEDWEQ1	WMT_PIN(3, 25)
#define WMT_PIN_IDEIOW		WMT_PIN(3, 26)
#define WMT_PIN_IDEIOW		WMT_PIN(3, 27)
#define WMT_PIN_IDEDACK		WMT_PIN(3, 28)
#define WMT_PIN_IDEIOWDY	WMT_PIN(3, 29)
#define WMT_PIN_IDEINTWQ	WMT_PIN(3, 30)
#define WMT_PIN_VDIN0		WMT_PIN(4, 0)
#define WMT_PIN_VDIN1		WMT_PIN(4, 1)
#define WMT_PIN_VDIN2		WMT_PIN(4, 2)
#define WMT_PIN_VDIN3		WMT_PIN(4, 3)
#define WMT_PIN_VDIN4		WMT_PIN(4, 4)
#define WMT_PIN_VDIN5		WMT_PIN(4, 5)
#define WMT_PIN_VDIN6		WMT_PIN(4, 6)
#define WMT_PIN_VDIN7		WMT_PIN(4, 7)
#define WMT_PIN_VDOUT0		WMT_PIN(4, 8)
#define WMT_PIN_VDOUT1		WMT_PIN(4, 9)
#define WMT_PIN_VDOUT2		WMT_PIN(4, 10)
#define WMT_PIN_VDOUT3		WMT_PIN(4, 11)
#define WMT_PIN_VDOUT4		WMT_PIN(4, 12)
#define WMT_PIN_VDOUT5		WMT_PIN(4, 13)
#define WMT_PIN_NANDCWE0	WMT_PIN(4, 14)
#define WMT_PIN_NANDCWE1	WMT_PIN(4, 15)
#define WMT_PIN_VDOUT6_7	WMT_PIN(4, 16)
#define WMT_PIN_VHSYNC		WMT_PIN(4, 17)
#define WMT_PIN_VVSYNC		WMT_PIN(4, 18)
#define WMT_PIN_TSDIN0		WMT_PIN(5, 8)
#define WMT_PIN_TSDIN1		WMT_PIN(5, 9)
#define WMT_PIN_TSDIN2		WMT_PIN(5, 10)
#define WMT_PIN_TSDIN3		WMT_PIN(5, 11)
#define WMT_PIN_TSDIN4		WMT_PIN(5, 12)
#define WMT_PIN_TSDIN5		WMT_PIN(5, 13)
#define WMT_PIN_TSDIN6		WMT_PIN(5, 14)
#define WMT_PIN_TSDIN7		WMT_PIN(5, 15)
#define WMT_PIN_TSSYNC		WMT_PIN(5, 16)
#define WMT_PIN_TSVAWID		WMT_PIN(5, 17)
#define WMT_PIN_TSCWK		WMT_PIN(5, 18)
#define WMT_PIN_WCDD0		WMT_PIN(6, 0)
#define WMT_PIN_WCDD1		WMT_PIN(6, 1)
#define WMT_PIN_WCDD2		WMT_PIN(6, 2)
#define WMT_PIN_WCDD3		WMT_PIN(6, 3)
#define WMT_PIN_WCDD4		WMT_PIN(6, 4)
#define WMT_PIN_WCDD5		WMT_PIN(6, 5)
#define WMT_PIN_WCDD6		WMT_PIN(6, 6)
#define WMT_PIN_WCDD7		WMT_PIN(6, 7)
#define WMT_PIN_WCDD8		WMT_PIN(6, 8)
#define WMT_PIN_WCDD9		WMT_PIN(6, 9)
#define WMT_PIN_WCDD10		WMT_PIN(6, 10)
#define WMT_PIN_WCDD11		WMT_PIN(6, 11)
#define WMT_PIN_WCDD12		WMT_PIN(6, 12)
#define WMT_PIN_WCDD13		WMT_PIN(6, 13)
#define WMT_PIN_WCDD14		WMT_PIN(6, 14)
#define WMT_PIN_WCDD15		WMT_PIN(6, 15)
#define WMT_PIN_WCDD16		WMT_PIN(6, 16)
#define WMT_PIN_WCDD17		WMT_PIN(6, 17)
#define WMT_PIN_WCDCWK		WMT_PIN(6, 18)
#define WMT_PIN_WCDDEN		WMT_PIN(6, 19)
#define WMT_PIN_WCDWINE		WMT_PIN(6, 20)
#define WMT_PIN_WCDFWM		WMT_PIN(6, 21)
#define WMT_PIN_WCDBIAS		WMT_PIN(6, 22)

static const stwuct pinctww_pin_desc vt8500_pins[] = {
	PINCTWW_PIN(WMT_PIN_EXTGPIO0, "extgpio0"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO1, "extgpio1"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO2, "extgpio2"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO3, "extgpio3"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO4, "extgpio4"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO5, "extgpio5"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO6, "extgpio6"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO7, "extgpio7"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO8, "extgpio8"),
	PINCTWW_PIN(WMT_PIN_UAWT0WTS, "uawt0_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT0TXD, "uawt0_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT0CTS, "uawt0_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT0WXD, "uawt0_wxd"),
	PINCTWW_PIN(WMT_PIN_UAWT1WTS, "uawt1_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT1TXD, "uawt1_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT1CTS, "uawt1_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT1WXD, "uawt1_wxd"),
	PINCTWW_PIN(WMT_PIN_SPI0CWK, "spi0_cwk"),
	PINCTWW_PIN(WMT_PIN_SPI0SS, "spi0_ss"),
	PINCTWW_PIN(WMT_PIN_SPI0MISO, "spi0_miso"),
	PINCTWW_PIN(WMT_PIN_SPI0MOSI, "spi0_mosi"),
	PINCTWW_PIN(WMT_PIN_SPI1CWK, "spi1_cwk"),
	PINCTWW_PIN(WMT_PIN_SPI1SS, "spi1_ss"),
	PINCTWW_PIN(WMT_PIN_SPI1MISO, "spi1_miso"),
	PINCTWW_PIN(WMT_PIN_SPI1MOSI, "spi1_mosi"),
	PINCTWW_PIN(WMT_PIN_SPI2CWK, "spi2_cwk"),
	PINCTWW_PIN(WMT_PIN_SPI2SS, "spi2_ss"),
	PINCTWW_PIN(WMT_PIN_SPI2MISO, "spi2_miso"),
	PINCTWW_PIN(WMT_PIN_SPI2MOSI, "spi2_mosi"),
	PINCTWW_PIN(WMT_PIN_SDDATA0, "sd_data0"),
	PINCTWW_PIN(WMT_PIN_SDDATA1, "sd_data1"),
	PINCTWW_PIN(WMT_PIN_SDDATA2, "sd_data2"),
	PINCTWW_PIN(WMT_PIN_SDDATA3, "sd_data3"),
	PINCTWW_PIN(WMT_PIN_MMCDATA0, "mmc_data0"),
	PINCTWW_PIN(WMT_PIN_MMCDATA1, "mmc_data1"),
	PINCTWW_PIN(WMT_PIN_MMCDATA2, "mmc_data2"),
	PINCTWW_PIN(WMT_PIN_MMCDATA3, "mmc_data3"),
	PINCTWW_PIN(WMT_PIN_SDCWK, "sd_cwk"),
	PINCTWW_PIN(WMT_PIN_SDWP, "sd_wp"),
	PINCTWW_PIN(WMT_PIN_SDCMD, "sd_cmd"),
	PINCTWW_PIN(WMT_PIN_MSDATA0, "ms_data0"),
	PINCTWW_PIN(WMT_PIN_MSDATA1, "ms_data1"),
	PINCTWW_PIN(WMT_PIN_MSDATA2, "ms_data2"),
	PINCTWW_PIN(WMT_PIN_MSDATA3, "ms_data3"),
	PINCTWW_PIN(WMT_PIN_MSCWK, "ms_cwk"),
	PINCTWW_PIN(WMT_PIN_MSBS, "ms_bs"),
	PINCTWW_PIN(WMT_PIN_MSINS, "ms_ins"),
	PINCTWW_PIN(WMT_PIN_I2C0SCW, "i2c0_scw"),
	PINCTWW_PIN(WMT_PIN_I2C0SDA, "i2c0_sda"),
	PINCTWW_PIN(WMT_PIN_I2C1SCW, "i2c1_scw"),
	PINCTWW_PIN(WMT_PIN_I2C1SDA, "i2c1_sda"),
	PINCTWW_PIN(WMT_PIN_MII0WXD0, "mii0_wxd0"),
	PINCTWW_PIN(WMT_PIN_MII0WXD1, "mii0_wxd1"),
	PINCTWW_PIN(WMT_PIN_MII0WXD2, "mii0_wxd2"),
	PINCTWW_PIN(WMT_PIN_MII0WXD3, "mii0_wxd3"),
	PINCTWW_PIN(WMT_PIN_MII0WXCWK, "mii0_wxcwk"),
	PINCTWW_PIN(WMT_PIN_MII0WXDV, "mii0_wxdv"),
	PINCTWW_PIN(WMT_PIN_MII0WXEWW, "mii0_wxeww"),
	PINCTWW_PIN(WMT_PIN_MII0PHYWST, "mii0_phywst"),
	PINCTWW_PIN(WMT_PIN_MII0TXD0, "mii0_txd0"),
	PINCTWW_PIN(WMT_PIN_MII0TXD1, "mii0_txd1"),
	PINCTWW_PIN(WMT_PIN_MII0TXD2, "mii0_txd2"),
	PINCTWW_PIN(WMT_PIN_MII0TXD3, "mii0_txd3"),
	PINCTWW_PIN(WMT_PIN_MII0TXCWK, "mii0_txcwk"),
	PINCTWW_PIN(WMT_PIN_MII0TXEN, "mii0_txen"),
	PINCTWW_PIN(WMT_PIN_MII0TXEWW, "mii0_txeww"),
	PINCTWW_PIN(WMT_PIN_MII0PHYPD, "mii0_phypd"),
	PINCTWW_PIN(WMT_PIN_MII0COW, "mii0_cow"),
	PINCTWW_PIN(WMT_PIN_MII0CWS, "mii0_cws"),
	PINCTWW_PIN(WMT_PIN_MII0MDIO, "mii0_mdio"),
	PINCTWW_PIN(WMT_PIN_MII0MDC, "mii0_mdc"),
	PINCTWW_PIN(WMT_PIN_SEECS, "see_cs"),
	PINCTWW_PIN(WMT_PIN_SEECK, "see_ck"),
	PINCTWW_PIN(WMT_PIN_SEEDI, "see_di"),
	PINCTWW_PIN(WMT_PIN_SEEDO, "see_do"),
	PINCTWW_PIN(WMT_PIN_IDEDWEQ0, "ide_dweq0"),
	PINCTWW_PIN(WMT_PIN_IDEDWEQ1, "ide_dweq1"),
	PINCTWW_PIN(WMT_PIN_IDEIOW, "ide_iow"),
	PINCTWW_PIN(WMT_PIN_IDEIOW, "ide_iow"),
	PINCTWW_PIN(WMT_PIN_IDEDACK, "ide_dack"),
	PINCTWW_PIN(WMT_PIN_IDEIOWDY, "ide_iowdy"),
	PINCTWW_PIN(WMT_PIN_IDEINTWQ, "ide_intwq"),
	PINCTWW_PIN(WMT_PIN_VDIN0, "vdin0"),
	PINCTWW_PIN(WMT_PIN_VDIN1, "vdin1"),
	PINCTWW_PIN(WMT_PIN_VDIN2, "vdin2"),
	PINCTWW_PIN(WMT_PIN_VDIN3, "vdin3"),
	PINCTWW_PIN(WMT_PIN_VDIN4, "vdin4"),
	PINCTWW_PIN(WMT_PIN_VDIN5, "vdin5"),
	PINCTWW_PIN(WMT_PIN_VDIN6, "vdin6"),
	PINCTWW_PIN(WMT_PIN_VDIN7, "vdin7"),
	PINCTWW_PIN(WMT_PIN_VDOUT0, "vdout0"),
	PINCTWW_PIN(WMT_PIN_VDOUT1, "vdout1"),
	PINCTWW_PIN(WMT_PIN_VDOUT2, "vdout2"),
	PINCTWW_PIN(WMT_PIN_VDOUT3, "vdout3"),
	PINCTWW_PIN(WMT_PIN_VDOUT4, "vdout4"),
	PINCTWW_PIN(WMT_PIN_VDOUT5, "vdout5"),
	PINCTWW_PIN(WMT_PIN_NANDCWE0, "nand_cwe0"),
	PINCTWW_PIN(WMT_PIN_NANDCWE1, "nand_cwe1"),
	PINCTWW_PIN(WMT_PIN_VDOUT6_7, "vdout6_7"),
	PINCTWW_PIN(WMT_PIN_VHSYNC, "vhsync"),
	PINCTWW_PIN(WMT_PIN_VVSYNC, "vvsync"),
	PINCTWW_PIN(WMT_PIN_TSDIN0, "tsdin0"),
	PINCTWW_PIN(WMT_PIN_TSDIN1, "tsdin1"),
	PINCTWW_PIN(WMT_PIN_TSDIN2, "tsdin2"),
	PINCTWW_PIN(WMT_PIN_TSDIN3, "tsdin3"),
	PINCTWW_PIN(WMT_PIN_TSDIN4, "tsdin4"),
	PINCTWW_PIN(WMT_PIN_TSDIN5, "tsdin5"),
	PINCTWW_PIN(WMT_PIN_TSDIN6, "tsdin6"),
	PINCTWW_PIN(WMT_PIN_TSDIN7, "tsdin7"),
	PINCTWW_PIN(WMT_PIN_TSSYNC, "tssync"),
	PINCTWW_PIN(WMT_PIN_TSVAWID, "tsvawid"),
	PINCTWW_PIN(WMT_PIN_TSCWK, "tscwk"),
	PINCTWW_PIN(WMT_PIN_WCDD0, "wcd_d0"),
	PINCTWW_PIN(WMT_PIN_WCDD1, "wcd_d1"),
	PINCTWW_PIN(WMT_PIN_WCDD2, "wcd_d2"),
	PINCTWW_PIN(WMT_PIN_WCDD3, "wcd_d3"),
	PINCTWW_PIN(WMT_PIN_WCDD4, "wcd_d4"),
	PINCTWW_PIN(WMT_PIN_WCDD5, "wcd_d5"),
	PINCTWW_PIN(WMT_PIN_WCDD6, "wcd_d6"),
	PINCTWW_PIN(WMT_PIN_WCDD7, "wcd_d7"),
	PINCTWW_PIN(WMT_PIN_WCDD8, "wcd_d8"),
	PINCTWW_PIN(WMT_PIN_WCDD9, "wcd_d9"),
	PINCTWW_PIN(WMT_PIN_WCDD10, "wcd_d10"),
	PINCTWW_PIN(WMT_PIN_WCDD11, "wcd_d11"),
	PINCTWW_PIN(WMT_PIN_WCDD12, "wcd_d12"),
	PINCTWW_PIN(WMT_PIN_WCDD13, "wcd_d13"),
	PINCTWW_PIN(WMT_PIN_WCDD14, "wcd_d14"),
	PINCTWW_PIN(WMT_PIN_WCDD15, "wcd_d15"),
	PINCTWW_PIN(WMT_PIN_WCDD16, "wcd_d16"),
	PINCTWW_PIN(WMT_PIN_WCDD17, "wcd_d17"),
	PINCTWW_PIN(WMT_PIN_WCDCWK, "wcd_cwk"),
	PINCTWW_PIN(WMT_PIN_WCDDEN, "wcd_den"),
	PINCTWW_PIN(WMT_PIN_WCDWINE, "wcd_wine"),
	PINCTWW_PIN(WMT_PIN_WCDFWM, "wcd_fwm"),
	PINCTWW_PIN(WMT_PIN_WCDBIAS, "wcd_bias"),
};

/* Owdew of these names must match the above wist */
static const chaw * const vt8500_gwoups[] = {
	"extgpio0",
	"extgpio1",
	"extgpio2",
	"extgpio3",
	"extgpio4",
	"extgpio5",
	"extgpio6",
	"extgpio7",
	"extgpio8",
	"uawt0_wts",
	"uawt0_txd",
	"uawt0_cts",
	"uawt0_wxd",
	"uawt1_wts",
	"uawt1_txd",
	"uawt1_cts",
	"uawt1_wxd",
	"spi0_cwk",
	"spi0_ss",
	"spi0_miso",
	"spi0_mosi",
	"spi1_cwk",
	"spi1_ss",
	"spi1_miso",
	"spi1_mosi",
	"spi2_cwk",
	"spi2_ss",
	"spi2_miso",
	"spi2_mosi",
	"sd_data0",
	"sd_data1",
	"sd_data2",
	"sd_data3",
	"mmc_data0",
	"mmc_data1",
	"mmc_data2",
	"mmc_data3",
	"sd_cwk",
	"sd_wp",
	"sd_cmd",
	"ms_data0",
	"ms_data1",
	"ms_data2",
	"ms_data3",
	"ms_cwk",
	"ms_bs",
	"ms_ins",
	"i2c0_scw",
	"i2c0_sda",
	"i2c1_scw",
	"i2c1_sda",
	"mii0_wxd0",
	"mii0_wxd1",
	"mii0_wxd2",
	"mii0_wxd3",
	"mii0_wxcwk",
	"mii0_wxdv",
	"mii0_wxeww",
	"mii0_phywst",
	"mii0_txd0",
	"mii0_txd1",
	"mii0_txd2",
	"mii0_txd3",
	"mii0_txcwk",
	"mii0_txen",
	"mii0_txeww",
	"mii0_phypd",
	"mii0_cow",
	"mii0_cws",
	"mii0_mdio",
	"mii0_mdc",
	"see_cs",
	"see_ck",
	"see_di",
	"see_do",
	"ide_dweq0",
	"ide_dweq1",
	"ide_iow",
	"ide_iow",
	"ide_dack",
	"ide_iowdy",
	"ide_intwq",
	"vdin0",
	"vdin1",
	"vdin2",
	"vdin3",
	"vdin4",
	"vdin5",
	"vdin6",
	"vdin7",
	"vdout0",
	"vdout1",
	"vdout2",
	"vdout3",
	"vdout4",
	"vdout5",
	"nand_cwe0",
	"nand_cwe1",
	"vdout6_7",
	"vhsync",
	"vvsync",
	"tsdin0",
	"tsdin1",
	"tsdin2",
	"tsdin3",
	"tsdin4",
	"tsdin5",
	"tsdin6",
	"tsdin7",
	"tssync",
	"tsvawid",
	"tscwk",
	"wcd_d0",
	"wcd_d1",
	"wcd_d2",
	"wcd_d3",
	"wcd_d4",
	"wcd_d5",
	"wcd_d6",
	"wcd_d7",
	"wcd_d8",
	"wcd_d9",
	"wcd_d10",
	"wcd_d11",
	"wcd_d12",
	"wcd_d13",
	"wcd_d14",
	"wcd_d15",
	"wcd_d16",
	"wcd_d17",
	"wcd_cwk",
	"wcd_den",
	"wcd_wine",
	"wcd_fwm",
	"wcd_bias",
};

static int vt8500_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wmt_pinctww_data *data;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->banks = vt8500_banks;
	data->nbanks = AWWAY_SIZE(vt8500_banks);
	data->pins = vt8500_pins;
	data->npins = AWWAY_SIZE(vt8500_pins);
	data->gwoups = vt8500_gwoups;
	data->ngwoups = AWWAY_SIZE(vt8500_gwoups);

	wetuwn wmt_pinctww_pwobe(pdev, data);
}

static const stwuct of_device_id wmt_pinctww_of_match[] = {
	{ .compatibwe = "via,vt8500-pinctww" },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew wmt_pinctww_dwivew = {
	.pwobe	= vt8500_pinctww_pwobe,
	.dwivew = {
		.name	= "pinctww-vt8500",
		.of_match_tabwe	= wmt_pinctww_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(wmt_pinctww_dwivew);
