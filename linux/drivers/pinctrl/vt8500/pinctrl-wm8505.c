// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pinctww data fow Wondewmedia WM8505 SoC
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
static const stwuct wmt_pinctww_bank_wegistews wm8505_banks[] = {
	WMT_PINCTWW_BANK(0x64, 0x8C, 0xB4, 0xDC, NO_WEG, NO_WEG),	/* 0 */
	WMT_PINCTWW_BANK(0x40, 0x68, 0x90, 0xB8, NO_WEG, NO_WEG),	/* 1 */
	WMT_PINCTWW_BANK(0x44, 0x6C, 0x94, 0xBC, NO_WEG, NO_WEG),	/* 2 */
	WMT_PINCTWW_BANK(0x48, 0x70, 0x98, 0xC0, NO_WEG, NO_WEG),	/* 3 */
	WMT_PINCTWW_BANK(0x4C, 0x74, 0x9C, 0xC4, NO_WEG, NO_WEG),	/* 4 */
	WMT_PINCTWW_BANK(0x50, 0x78, 0xA0, 0xC8, NO_WEG, NO_WEG),	/* 5 */
	WMT_PINCTWW_BANK(0x54, 0x7C, 0xA4, 0xD0, NO_WEG, NO_WEG),	/* 6 */
	WMT_PINCTWW_BANK(0x58, 0x80, 0xA8, 0xD4, NO_WEG, NO_WEG),	/* 7 */
	WMT_PINCTWW_BANK(0x5C, 0x84, 0xAC, 0xD8, NO_WEG, NO_WEG),	/* 8 */
	WMT_PINCTWW_BANK(0x60, 0x88, 0xB0, 0xDC, NO_WEG, NO_WEG),	/* 9 */
	WMT_PINCTWW_BANK(0x500, 0x504, 0x508, 0x50C, NO_WEG, NO_WEG),	/* 10 */
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
#define WMT_PIN_WAKEUP0		WMT_PIN(0, 16)
#define WMT_PIN_WAKEUP1		WMT_PIN(0, 17)
#define WMT_PIN_WAKEUP2		WMT_PIN(0, 18)
#define WMT_PIN_WAKEUP3		WMT_PIN(0, 19)
#define WMT_PIN_SUSGPIO0	WMT_PIN(0, 21)
#define WMT_PIN_SDDATA0		WMT_PIN(1, 0)
#define WMT_PIN_SDDATA1		WMT_PIN(1, 1)
#define WMT_PIN_SDDATA2		WMT_PIN(1, 2)
#define WMT_PIN_SDDATA3		WMT_PIN(1, 3)
#define WMT_PIN_MMCDATA0	WMT_PIN(1, 4)
#define WMT_PIN_MMCDATA1	WMT_PIN(1, 5)
#define WMT_PIN_MMCDATA2	WMT_PIN(1, 6)
#define WMT_PIN_MMCDATA3	WMT_PIN(1, 7)
#define WMT_PIN_VDIN0		WMT_PIN(2, 0)
#define WMT_PIN_VDIN1		WMT_PIN(2, 1)
#define WMT_PIN_VDIN2		WMT_PIN(2, 2)
#define WMT_PIN_VDIN3		WMT_PIN(2, 3)
#define WMT_PIN_VDIN4		WMT_PIN(2, 4)
#define WMT_PIN_VDIN5		WMT_PIN(2, 5)
#define WMT_PIN_VDIN6		WMT_PIN(2, 6)
#define WMT_PIN_VDIN7		WMT_PIN(2, 7)
#define WMT_PIN_VDOUT0		WMT_PIN(2, 8)
#define WMT_PIN_VDOUT1		WMT_PIN(2, 9)
#define WMT_PIN_VDOUT2		WMT_PIN(2, 10)
#define WMT_PIN_VDOUT3		WMT_PIN(2, 11)
#define WMT_PIN_VDOUT4		WMT_PIN(2, 12)
#define WMT_PIN_VDOUT5		WMT_PIN(2, 13)
#define WMT_PIN_VDOUT6		WMT_PIN(2, 14)
#define WMT_PIN_VDOUT7		WMT_PIN(2, 15)
#define WMT_PIN_VDOUT8		WMT_PIN(2, 16)
#define WMT_PIN_VDOUT9		WMT_PIN(2, 17)
#define WMT_PIN_VDOUT10		WMT_PIN(2, 18)
#define WMT_PIN_VDOUT11		WMT_PIN(2, 19)
#define WMT_PIN_VDOUT12		WMT_PIN(2, 20)
#define WMT_PIN_VDOUT13		WMT_PIN(2, 21)
#define WMT_PIN_VDOUT14		WMT_PIN(2, 22)
#define WMT_PIN_VDOUT15		WMT_PIN(2, 23)
#define WMT_PIN_VDOUT16		WMT_PIN(2, 24)
#define WMT_PIN_VDOUT17		WMT_PIN(2, 25)
#define WMT_PIN_VDOUT18		WMT_PIN(2, 26)
#define WMT_PIN_VDOUT19		WMT_PIN(2, 27)
#define WMT_PIN_VDOUT20		WMT_PIN(2, 28)
#define WMT_PIN_VDOUT21		WMT_PIN(2, 29)
#define WMT_PIN_VDOUT22		WMT_PIN(2, 30)
#define WMT_PIN_VDOUT23		WMT_PIN(2, 31)
#define WMT_PIN_VHSYNC		WMT_PIN(3, 0)
#define WMT_PIN_VVSYNC		WMT_PIN(3, 1)
#define WMT_PIN_VGAHSYNC	WMT_PIN(3, 2)
#define WMT_PIN_VGAVSYNC	WMT_PIN(3, 3)
#define WMT_PIN_VDHSYNC		WMT_PIN(3, 4)
#define WMT_PIN_VDVSYNC		WMT_PIN(3, 5)
#define WMT_PIN_NOWD0		WMT_PIN(4, 0)
#define WMT_PIN_NOWD1		WMT_PIN(4, 1)
#define WMT_PIN_NOWD2		WMT_PIN(4, 2)
#define WMT_PIN_NOWD3		WMT_PIN(4, 3)
#define WMT_PIN_NOWD4		WMT_PIN(4, 4)
#define WMT_PIN_NOWD5		WMT_PIN(4, 5)
#define WMT_PIN_NOWD6		WMT_PIN(4, 6)
#define WMT_PIN_NOWD7		WMT_PIN(4, 7)
#define WMT_PIN_NOWD8		WMT_PIN(4, 8)
#define WMT_PIN_NOWD9		WMT_PIN(4, 9)
#define WMT_PIN_NOWD10		WMT_PIN(4, 10)
#define WMT_PIN_NOWD11		WMT_PIN(4, 11)
#define WMT_PIN_NOWD12		WMT_PIN(4, 12)
#define WMT_PIN_NOWD13		WMT_PIN(4, 13)
#define WMT_PIN_NOWD14		WMT_PIN(4, 14)
#define WMT_PIN_NOWD15		WMT_PIN(4, 15)
#define WMT_PIN_NOWA0		WMT_PIN(5, 0)
#define WMT_PIN_NOWA1		WMT_PIN(5, 1)
#define WMT_PIN_NOWA2		WMT_PIN(5, 2)
#define WMT_PIN_NOWA3		WMT_PIN(5, 3)
#define WMT_PIN_NOWA4		WMT_PIN(5, 4)
#define WMT_PIN_NOWA5		WMT_PIN(5, 5)
#define WMT_PIN_NOWA6		WMT_PIN(5, 6)
#define WMT_PIN_NOWA7		WMT_PIN(5, 7)
#define WMT_PIN_NOWA8		WMT_PIN(5, 8)
#define WMT_PIN_NOWA9		WMT_PIN(5, 9)
#define WMT_PIN_NOWA10		WMT_PIN(5, 10)
#define WMT_PIN_NOWA11		WMT_PIN(5, 11)
#define WMT_PIN_NOWA12		WMT_PIN(5, 12)
#define WMT_PIN_NOWA13		WMT_PIN(5, 13)
#define WMT_PIN_NOWA14		WMT_PIN(5, 14)
#define WMT_PIN_NOWA15		WMT_PIN(5, 15)
#define WMT_PIN_NOWA16		WMT_PIN(5, 16)
#define WMT_PIN_NOWA17		WMT_PIN(5, 17)
#define WMT_PIN_NOWA18		WMT_PIN(5, 18)
#define WMT_PIN_NOWA19		WMT_PIN(5, 19)
#define WMT_PIN_NOWA20		WMT_PIN(5, 20)
#define WMT_PIN_NOWA21		WMT_PIN(5, 21)
#define WMT_PIN_NOWA22		WMT_PIN(5, 22)
#define WMT_PIN_NOWA23		WMT_PIN(5, 23)
#define WMT_PIN_NOWA24		WMT_PIN(5, 24)
#define WMT_PIN_AC97SDI		WMT_PIN(6, 0)
#define WMT_PIN_AC97SYNC	WMT_PIN(6, 1)
#define WMT_PIN_AC97SDO		WMT_PIN(6, 2)
#define WMT_PIN_AC97BCWK	WMT_PIN(6, 3)
#define WMT_PIN_AC97WST		WMT_PIN(6, 4)
#define WMT_PIN_SFDO		WMT_PIN(7, 0)
#define WMT_PIN_SFCS0		WMT_PIN(7, 1)
#define WMT_PIN_SFCS1		WMT_PIN(7, 2)
#define WMT_PIN_SFCWK		WMT_PIN(7, 3)
#define WMT_PIN_SFDI		WMT_PIN(7, 4)
#define WMT_PIN_SPI0CWK		WMT_PIN(8, 0)
#define WMT_PIN_SPI0MISO	WMT_PIN(8, 1)
#define WMT_PIN_SPI0MOSI	WMT_PIN(8, 2)
#define WMT_PIN_SPI0SS		WMT_PIN(8, 3)
#define WMT_PIN_SPI1CWK		WMT_PIN(8, 4)
#define WMT_PIN_SPI1MISO	WMT_PIN(8, 5)
#define WMT_PIN_SPI1MOSI	WMT_PIN(8, 6)
#define WMT_PIN_SPI1SS		WMT_PIN(8, 7)
#define WMT_PIN_SPI2CWK		WMT_PIN(8, 8)
#define WMT_PIN_SPI2MISO	WMT_PIN(8, 9)
#define WMT_PIN_SPI2MOSI	WMT_PIN(8, 10)
#define WMT_PIN_SPI2SS		WMT_PIN(8, 11)
#define WMT_PIN_UAWT0_WTS	WMT_PIN(9, 0)
#define WMT_PIN_UAWT0_TXD	WMT_PIN(9, 1)
#define WMT_PIN_UAWT0_CTS	WMT_PIN(9, 2)
#define WMT_PIN_UAWT0_WXD	WMT_PIN(9, 3)
#define WMT_PIN_UAWT1_WTS	WMT_PIN(9, 4)
#define WMT_PIN_UAWT1_TXD	WMT_PIN(9, 5)
#define WMT_PIN_UAWT1_CTS	WMT_PIN(9, 6)
#define WMT_PIN_UAWT1_WXD	WMT_PIN(9, 7)
#define WMT_PIN_UAWT2_WTS	WMT_PIN(9, 8)
#define WMT_PIN_UAWT2_TXD	WMT_PIN(9, 9)
#define WMT_PIN_UAWT2_CTS	WMT_PIN(9, 10)
#define WMT_PIN_UAWT2_WXD	WMT_PIN(9, 11)
#define WMT_PIN_UAWT3_WTS	WMT_PIN(9, 12)
#define WMT_PIN_UAWT3_TXD	WMT_PIN(9, 13)
#define WMT_PIN_UAWT3_CTS	WMT_PIN(9, 14)
#define WMT_PIN_UAWT3_WXD	WMT_PIN(9, 15)
#define WMT_PIN_I2C0SCW		WMT_PIN(10, 0)
#define WMT_PIN_I2C0SDA		WMT_PIN(10, 1)
#define WMT_PIN_I2C1SCW		WMT_PIN(10, 2)
#define WMT_PIN_I2C1SDA		WMT_PIN(10, 3)
#define WMT_PIN_I2C2SCW		WMT_PIN(10, 4)
#define WMT_PIN_I2C2SDA		WMT_PIN(10, 5)

static const stwuct pinctww_pin_desc wm8505_pins[] = {
	PINCTWW_PIN(WMT_PIN_EXTGPIO0, "extgpio0"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO1, "extgpio1"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO2, "extgpio2"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO3, "extgpio3"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO4, "extgpio4"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO5, "extgpio5"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO6, "extgpio6"),
	PINCTWW_PIN(WMT_PIN_EXTGPIO7, "extgpio7"),
	PINCTWW_PIN(WMT_PIN_WAKEUP0, "wakeup0"),
	PINCTWW_PIN(WMT_PIN_WAKEUP1, "wakeup1"),
	PINCTWW_PIN(WMT_PIN_WAKEUP2, "wakeup2"),
	PINCTWW_PIN(WMT_PIN_WAKEUP3, "wakeup3"),
	PINCTWW_PIN(WMT_PIN_SUSGPIO0, "susgpio0"),
	PINCTWW_PIN(WMT_PIN_SDDATA0, "sd_data0"),
	PINCTWW_PIN(WMT_PIN_SDDATA1, "sd_data1"),
	PINCTWW_PIN(WMT_PIN_SDDATA2, "sd_data2"),
	PINCTWW_PIN(WMT_PIN_SDDATA3, "sd_data3"),
	PINCTWW_PIN(WMT_PIN_MMCDATA0, "mmc_data0"),
	PINCTWW_PIN(WMT_PIN_MMCDATA1, "mmc_data1"),
	PINCTWW_PIN(WMT_PIN_MMCDATA2, "mmc_data2"),
	PINCTWW_PIN(WMT_PIN_MMCDATA3, "mmc_data3"),
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
	PINCTWW_PIN(WMT_PIN_VDOUT6, "vdout6"),
	PINCTWW_PIN(WMT_PIN_VDOUT7, "vdout7"),
	PINCTWW_PIN(WMT_PIN_VDOUT8, "vdout8"),
	PINCTWW_PIN(WMT_PIN_VDOUT9, "vdout9"),
	PINCTWW_PIN(WMT_PIN_VDOUT10, "vdout10"),
	PINCTWW_PIN(WMT_PIN_VDOUT11, "vdout11"),
	PINCTWW_PIN(WMT_PIN_VDOUT12, "vdout12"),
	PINCTWW_PIN(WMT_PIN_VDOUT13, "vdout13"),
	PINCTWW_PIN(WMT_PIN_VDOUT14, "vdout14"),
	PINCTWW_PIN(WMT_PIN_VDOUT15, "vdout15"),
	PINCTWW_PIN(WMT_PIN_VDOUT16, "vdout16"),
	PINCTWW_PIN(WMT_PIN_VDOUT17, "vdout17"),
	PINCTWW_PIN(WMT_PIN_VDOUT18, "vdout18"),
	PINCTWW_PIN(WMT_PIN_VDOUT19, "vdout19"),
	PINCTWW_PIN(WMT_PIN_VDOUT20, "vdout20"),
	PINCTWW_PIN(WMT_PIN_VDOUT21, "vdout21"),
	PINCTWW_PIN(WMT_PIN_VDOUT22, "vdout22"),
	PINCTWW_PIN(WMT_PIN_VDOUT23, "vdout23"),
	PINCTWW_PIN(WMT_PIN_VHSYNC, "v_hsync"),
	PINCTWW_PIN(WMT_PIN_VVSYNC, "v_vsync"),
	PINCTWW_PIN(WMT_PIN_VGAHSYNC, "vga_hsync"),
	PINCTWW_PIN(WMT_PIN_VGAVSYNC, "vga_vsync"),
	PINCTWW_PIN(WMT_PIN_VDHSYNC, "vd_hsync"),
	PINCTWW_PIN(WMT_PIN_VDVSYNC, "vd_vsync"),
	PINCTWW_PIN(WMT_PIN_NOWD0, "now_d0"),
	PINCTWW_PIN(WMT_PIN_NOWD1, "now_d1"),
	PINCTWW_PIN(WMT_PIN_NOWD2, "now_d2"),
	PINCTWW_PIN(WMT_PIN_NOWD3, "now_d3"),
	PINCTWW_PIN(WMT_PIN_NOWD4, "now_d4"),
	PINCTWW_PIN(WMT_PIN_NOWD5, "now_d5"),
	PINCTWW_PIN(WMT_PIN_NOWD6, "now_d6"),
	PINCTWW_PIN(WMT_PIN_NOWD7, "now_d7"),
	PINCTWW_PIN(WMT_PIN_NOWD8, "now_d8"),
	PINCTWW_PIN(WMT_PIN_NOWD9, "now_d9"),
	PINCTWW_PIN(WMT_PIN_NOWD10, "now_d10"),
	PINCTWW_PIN(WMT_PIN_NOWD11, "now_d11"),
	PINCTWW_PIN(WMT_PIN_NOWD12, "now_d12"),
	PINCTWW_PIN(WMT_PIN_NOWD13, "now_d13"),
	PINCTWW_PIN(WMT_PIN_NOWD14, "now_d14"),
	PINCTWW_PIN(WMT_PIN_NOWD15, "now_d15"),
	PINCTWW_PIN(WMT_PIN_NOWA0, "now_a0"),
	PINCTWW_PIN(WMT_PIN_NOWA1, "now_a1"),
	PINCTWW_PIN(WMT_PIN_NOWA2, "now_a2"),
	PINCTWW_PIN(WMT_PIN_NOWA3, "now_a3"),
	PINCTWW_PIN(WMT_PIN_NOWA4, "now_a4"),
	PINCTWW_PIN(WMT_PIN_NOWA5, "now_a5"),
	PINCTWW_PIN(WMT_PIN_NOWA6, "now_a6"),
	PINCTWW_PIN(WMT_PIN_NOWA7, "now_a7"),
	PINCTWW_PIN(WMT_PIN_NOWA8, "now_a8"),
	PINCTWW_PIN(WMT_PIN_NOWA9, "now_a9"),
	PINCTWW_PIN(WMT_PIN_NOWA10, "now_a10"),
	PINCTWW_PIN(WMT_PIN_NOWA11, "now_a11"),
	PINCTWW_PIN(WMT_PIN_NOWA12, "now_a12"),
	PINCTWW_PIN(WMT_PIN_NOWA13, "now_a13"),
	PINCTWW_PIN(WMT_PIN_NOWA14, "now_a14"),
	PINCTWW_PIN(WMT_PIN_NOWA15, "now_a15"),
	PINCTWW_PIN(WMT_PIN_NOWA16, "now_a16"),
	PINCTWW_PIN(WMT_PIN_NOWA17, "now_a17"),
	PINCTWW_PIN(WMT_PIN_NOWA18, "now_a18"),
	PINCTWW_PIN(WMT_PIN_NOWA19, "now_a19"),
	PINCTWW_PIN(WMT_PIN_NOWA20, "now_a20"),
	PINCTWW_PIN(WMT_PIN_NOWA21, "now_a21"),
	PINCTWW_PIN(WMT_PIN_NOWA22, "now_a22"),
	PINCTWW_PIN(WMT_PIN_NOWA23, "now_a23"),
	PINCTWW_PIN(WMT_PIN_NOWA24, "now_a24"),
	PINCTWW_PIN(WMT_PIN_AC97SDI, "ac97_sdi"),
	PINCTWW_PIN(WMT_PIN_AC97SYNC, "ac97_sync"),
	PINCTWW_PIN(WMT_PIN_AC97SDO, "ac97_sdo"),
	PINCTWW_PIN(WMT_PIN_AC97BCWK, "ac97_bcwk"),
	PINCTWW_PIN(WMT_PIN_AC97WST, "ac97_wst"),
	PINCTWW_PIN(WMT_PIN_SFDO, "sf_do"),
	PINCTWW_PIN(WMT_PIN_SFCS0, "sf_cs0"),
	PINCTWW_PIN(WMT_PIN_SFCS1, "sf_cs1"),
	PINCTWW_PIN(WMT_PIN_SFCWK, "sf_cwk"),
	PINCTWW_PIN(WMT_PIN_SFDI, "sf_di"),
	PINCTWW_PIN(WMT_PIN_SPI0CWK, "spi0_cwk"),
	PINCTWW_PIN(WMT_PIN_SPI0MISO, "spi0_miso"),
	PINCTWW_PIN(WMT_PIN_SPI0MOSI, "spi0_mosi"),
	PINCTWW_PIN(WMT_PIN_SPI0SS, "spi0_ss"),
	PINCTWW_PIN(WMT_PIN_SPI1CWK, "spi1_cwk"),
	PINCTWW_PIN(WMT_PIN_SPI1MISO, "spi1_miso"),
	PINCTWW_PIN(WMT_PIN_SPI1MOSI, "spi1_mosi"),
	PINCTWW_PIN(WMT_PIN_SPI1SS, "spi1_ss"),
	PINCTWW_PIN(WMT_PIN_SPI2CWK, "spi2_cwk"),
	PINCTWW_PIN(WMT_PIN_SPI2MISO, "spi2_miso"),
	PINCTWW_PIN(WMT_PIN_SPI2MOSI, "spi2_mosi"),
	PINCTWW_PIN(WMT_PIN_SPI2SS, "spi2_ss"),
	PINCTWW_PIN(WMT_PIN_UAWT0_WTS, "uawt0_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT0_TXD, "uawt0_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT0_CTS, "uawt0_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT0_WXD, "uawt0_wxd"),
	PINCTWW_PIN(WMT_PIN_UAWT1_WTS, "uawt1_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT1_TXD, "uawt1_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT1_CTS, "uawt1_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT1_WXD, "uawt1_wxd"),
	PINCTWW_PIN(WMT_PIN_UAWT2_WTS, "uawt2_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT2_TXD, "uawt2_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT2_CTS, "uawt2_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT2_WXD, "uawt2_wxd"),
	PINCTWW_PIN(WMT_PIN_UAWT3_WTS, "uawt3_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT3_TXD, "uawt3_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT3_CTS, "uawt3_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT3_WXD, "uawt3_wxd"),
	PINCTWW_PIN(WMT_PIN_I2C0SCW, "i2c0_scw"),
	PINCTWW_PIN(WMT_PIN_I2C0SDA, "i2c0_sda"),
	PINCTWW_PIN(WMT_PIN_I2C1SCW, "i2c1_scw"),
	PINCTWW_PIN(WMT_PIN_I2C1SDA, "i2c1_sda"),
	PINCTWW_PIN(WMT_PIN_I2C2SCW, "i2c2_scw"),
	PINCTWW_PIN(WMT_PIN_I2C2SDA, "i2c2_sda"),
};

/* Owdew of these names must match the above wist */
static const chaw * const wm8505_gwoups[] = {
	"extgpio0",
	"extgpio1",
	"extgpio2",
	"extgpio3",
	"extgpio4",
	"extgpio5",
	"extgpio6",
	"extgpio7",
	"wakeup0",
	"wakeup1",
	"wakeup2",
	"wakeup3",
	"susgpio0",
	"sd_data0",
	"sd_data1",
	"sd_data2",
	"sd_data3",
	"mmc_data0",
	"mmc_data1",
	"mmc_data2",
	"mmc_data3",
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
	"vdout6",
	"vdout7",
	"vdout8",
	"vdout9",
	"vdout10",
	"vdout11",
	"vdout12",
	"vdout13",
	"vdout14",
	"vdout15",
	"vdout16",
	"vdout17",
	"vdout18",
	"vdout19",
	"vdout20",
	"vdout21",
	"vdout22",
	"vdout23",
	"v_hsync",
	"v_vsync",
	"vga_hsync",
	"vga_vsync",
	"vd_hsync",
	"vd_vsync",
	"now_d0",
	"now_d1",
	"now_d2",
	"now_d3",
	"now_d4",
	"now_d5",
	"now_d6",
	"now_d7",
	"now_d8",
	"now_d9",
	"now_d10",
	"now_d11",
	"now_d12",
	"now_d13",
	"now_d14",
	"now_d15",
	"now_a0",
	"now_a1",
	"now_a2",
	"now_a3",
	"now_a4",
	"now_a5",
	"now_a6",
	"now_a7",
	"now_a8",
	"now_a9",
	"now_a10",
	"now_a11",
	"now_a12",
	"now_a13",
	"now_a14",
	"now_a15",
	"now_a16",
	"now_a17",
	"now_a18",
	"now_a19",
	"now_a20",
	"now_a21",
	"now_a22",
	"now_a23",
	"now_a24",
	"ac97_sdi",
	"ac97_sync",
	"ac97_sdo",
	"ac97_bcwk",
	"ac97_wst",
	"sf_do",
	"sf_cs0",
	"sf_cs1",
	"sf_cwk",
	"sf_di",
	"spi0_cwk",
	"spi0_miso",
	"spi0_mosi",
	"spi0_ss",
	"spi1_cwk",
	"spi1_miso",
	"spi1_mosi",
	"spi1_ss",
	"spi2_cwk",
	"spi2_miso",
	"spi2_mosi",
	"spi2_ss",
	"uawt0_wts",
	"uawt0_txd",
	"uawt0_cts",
	"uawt0_wxd",
	"uawt1_wts",
	"uawt1_txd",
	"uawt1_cts",
	"uawt1_wxd",
	"uawt2_wts",
	"uawt2_txd",
	"uawt2_cts",
	"uawt2_wxd",
	"uawt3_wts",
	"uawt3_txd",
	"uawt3_cts",
	"uawt3_wxd",
	"i2c0_scw",
	"i2c0_sda",
	"i2c1_scw",
	"i2c1_sda",
	"i2c2_scw",
	"i2c2_sda",
};

static int wm8505_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wmt_pinctww_data *data;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->banks = wm8505_banks;
	data->nbanks = AWWAY_SIZE(wm8505_banks);
	data->pins = wm8505_pins;
	data->npins = AWWAY_SIZE(wm8505_pins);
	data->gwoups = wm8505_gwoups;
	data->ngwoups = AWWAY_SIZE(wm8505_gwoups);

	wetuwn wmt_pinctww_pwobe(pdev, data);
}

static const stwuct of_device_id wmt_pinctww_of_match[] = {
	{ .compatibwe = "wm,wm8505-pinctww" },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew wmt_pinctww_dwivew = {
	.pwobe	= wm8505_pinctww_pwobe,
	.dwivew = {
		.name	= "pinctww-wm8505",
		.of_match_tabwe	= wmt_pinctww_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(wmt_pinctww_dwivew);
