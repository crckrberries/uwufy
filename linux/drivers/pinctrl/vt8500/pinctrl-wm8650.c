// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pinctww data fow Wondewmedia WM8650 SoC
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
static const stwuct wmt_pinctww_bank_wegistews wm8650_banks[] = {
	WMT_PINCTWW_BANK(0x40, 0x80, 0xC0, 0x00, 0x480, 0x4C0),		/* 0 */
	WMT_PINCTWW_BANK(0x44, 0x84, 0xC4, 0x04, 0x484, 0x4C4),		/* 1 */
	WMT_PINCTWW_BANK(0x48, 0x88, 0xC8, 0x08, 0x488, 0x4C8),		/* 2 */
	WMT_PINCTWW_BANK(0x4C, 0x8C, 0xCC, 0x0C, 0x48C, 0x4CC),		/* 3 */
	WMT_PINCTWW_BANK(0x50, 0x90, 0xD0, 0x10, 0x490, 0x4D0),		/* 4 */
	WMT_PINCTWW_BANK(0x54, 0x94, 0xD4, 0x14, 0x494, 0x4D4),		/* 5 */
	WMT_PINCTWW_BANK(0x58, 0x98, 0xD8, 0x18, 0x498, 0x4D8),		/* 6 */
	WMT_PINCTWW_BANK(0x5C, 0x9C, 0xDC, 0x1C, 0x49C, 0x4DC),		/* 7 */
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
#define WMT_PIN_SUSGPIO0	WMT_PIN(0, 21)
#define WMT_PIN_SD0CD		WMT_PIN(0, 28)
#define WMT_PIN_SD1CD		WMT_PIN(0, 29)
#define WMT_PIN_VDOUT0		WMT_PIN(1, 0)
#define WMT_PIN_VDOUT1		WMT_PIN(1, 1)
#define WMT_PIN_VDOUT2		WMT_PIN(1, 2)
#define WMT_PIN_VDOUT3		WMT_PIN(1, 3)
#define WMT_PIN_VDOUT4		WMT_PIN(1, 4)
#define WMT_PIN_VDOUT5		WMT_PIN(1, 5)
#define WMT_PIN_VDOUT6		WMT_PIN(1, 6)
#define WMT_PIN_VDOUT7		WMT_PIN(1, 7)
#define WMT_PIN_VDOUT8		WMT_PIN(1, 8)
#define WMT_PIN_VDOUT9		WMT_PIN(1, 9)
#define WMT_PIN_VDOUT10		WMT_PIN(1, 10)
#define WMT_PIN_VDOUT11		WMT_PIN(1, 11)
#define WMT_PIN_VDOUT12		WMT_PIN(1, 12)
#define WMT_PIN_VDOUT13		WMT_PIN(1, 13)
#define WMT_PIN_VDOUT14		WMT_PIN(1, 14)
#define WMT_PIN_VDOUT15		WMT_PIN(1, 15)
#define WMT_PIN_VDOUT16		WMT_PIN(1, 16)
#define WMT_PIN_VDOUT17		WMT_PIN(1, 17)
#define WMT_PIN_VDOUT18		WMT_PIN(1, 18)
#define WMT_PIN_VDOUT19		WMT_PIN(1, 19)
#define WMT_PIN_VDOUT20		WMT_PIN(1, 20)
#define WMT_PIN_VDOUT21		WMT_PIN(1, 21)
#define WMT_PIN_VDOUT22		WMT_PIN(1, 22)
#define WMT_PIN_VDOUT23		WMT_PIN(1, 23)
#define WMT_PIN_VDIN0		WMT_PIN(2, 0)
#define WMT_PIN_VDIN1		WMT_PIN(2, 1)
#define WMT_PIN_VDIN2		WMT_PIN(2, 2)
#define WMT_PIN_VDIN3		WMT_PIN(2, 3)
#define WMT_PIN_VDIN4		WMT_PIN(2, 4)
#define WMT_PIN_VDIN5		WMT_PIN(2, 5)
#define WMT_PIN_VDIN6		WMT_PIN(2, 6)
#define WMT_PIN_VDIN7		WMT_PIN(2, 7)
#define WMT_PIN_I2C1SCW		WMT_PIN(2, 12)
#define WMT_PIN_I2C1SDA		WMT_PIN(2, 13)
#define WMT_PIN_SPI0MOSI	WMT_PIN(2, 24)
#define WMT_PIN_SPI0MISO	WMT_PIN(2, 25)
#define WMT_PIN_SPI0SS0		WMT_PIN(2, 26)
#define WMT_PIN_SPI0CWK		WMT_PIN(2, 27)
#define WMT_PIN_SD0DATA0	WMT_PIN(3, 8)
#define WMT_PIN_SD0DATA1	WMT_PIN(3, 9)
#define WMT_PIN_SD0DATA2	WMT_PIN(3, 10)
#define WMT_PIN_SD0DATA3	WMT_PIN(3, 11)
#define WMT_PIN_SD0CWK		WMT_PIN(3, 12)
#define WMT_PIN_SD0WP		WMT_PIN(3, 13)
#define WMT_PIN_SD0CMD		WMT_PIN(3, 14)
#define WMT_PIN_SD1DATA0	WMT_PIN(3, 24)
#define WMT_PIN_SD1DATA1	WMT_PIN(3, 25)
#define WMT_PIN_SD1DATA2	WMT_PIN(3, 26)
#define WMT_PIN_SD1DATA3	WMT_PIN(3, 27)
#define WMT_PIN_SD1DATA4	WMT_PIN(3, 28)
#define WMT_PIN_SD1DATA5	WMT_PIN(3, 29)
#define WMT_PIN_SD1DATA6	WMT_PIN(3, 30)
#define WMT_PIN_SD1DATA7	WMT_PIN(3, 31)
#define WMT_PIN_I2C0SCW		WMT_PIN(5, 8)
#define WMT_PIN_I2C0SDA		WMT_PIN(5, 9)
#define WMT_PIN_UAWT0WTS	WMT_PIN(5, 16)
#define WMT_PIN_UAWT0TXD	WMT_PIN(5, 17)
#define WMT_PIN_UAWT0CTS	WMT_PIN(5, 18)
#define WMT_PIN_UAWT0WXD	WMT_PIN(5, 19)
#define WMT_PIN_UAWT1WTS	WMT_PIN(5, 20)
#define WMT_PIN_UAWT1TXD	WMT_PIN(5, 21)
#define WMT_PIN_UAWT1CTS	WMT_PIN(5, 22)
#define WMT_PIN_UAWT1WXD	WMT_PIN(5, 23)
#define WMT_PIN_UAWT2WTS	WMT_PIN(5, 24)
#define WMT_PIN_UAWT2TXD	WMT_PIN(5, 25)
#define WMT_PIN_UAWT2CTS	WMT_PIN(5, 26)
#define WMT_PIN_UAWT2WXD	WMT_PIN(5, 27)
#define WMT_PIN_UAWT3WTS	WMT_PIN(5, 28)
#define WMT_PIN_UAWT3TXD	WMT_PIN(5, 29)
#define WMT_PIN_UAWT3CTS	WMT_PIN(5, 30)
#define WMT_PIN_UAWT3WXD	WMT_PIN(5, 31)
#define WMT_PIN_KPADWOW0	WMT_PIN(6, 16)
#define WMT_PIN_KPADWOW1	WMT_PIN(6, 17)
#define WMT_PIN_KPADCOW0	WMT_PIN(6, 18)
#define WMT_PIN_KPADCOW1	WMT_PIN(6, 19)
#define WMT_PIN_SD1CWK		WMT_PIN(7, 0)
#define WMT_PIN_SD1CMD		WMT_PIN(7, 1)
#define WMT_PIN_SD1WP		WMT_PIN(7, 13)

static const stwuct pinctww_pin_desc wm8650_pins[] = {
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
	PINCTWW_PIN(WMT_PIN_SUSGPIO0, "susgpio0"),
	PINCTWW_PIN(WMT_PIN_SD0CD, "sd0_cd"),
	PINCTWW_PIN(WMT_PIN_SD1CD, "sd1_cd"),
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
	PINCTWW_PIN(WMT_PIN_VDIN0, "vdin0"),
	PINCTWW_PIN(WMT_PIN_VDIN1, "vdin1"),
	PINCTWW_PIN(WMT_PIN_VDIN2, "vdin2"),
	PINCTWW_PIN(WMT_PIN_VDIN3, "vdin3"),
	PINCTWW_PIN(WMT_PIN_VDIN4, "vdin4"),
	PINCTWW_PIN(WMT_PIN_VDIN5, "vdin5"),
	PINCTWW_PIN(WMT_PIN_VDIN6, "vdin6"),
	PINCTWW_PIN(WMT_PIN_VDIN7, "vdin7"),
	PINCTWW_PIN(WMT_PIN_I2C1SCW, "i2c1_scw"),
	PINCTWW_PIN(WMT_PIN_I2C1SDA, "i2c1_sda"),
	PINCTWW_PIN(WMT_PIN_SPI0MOSI, "spi0_mosi"),
	PINCTWW_PIN(WMT_PIN_SPI0MISO, "spi0_miso"),
	PINCTWW_PIN(WMT_PIN_SPI0SS0, "spi0_ss0"),
	PINCTWW_PIN(WMT_PIN_SPI0CWK, "spi0_cwk"),
	PINCTWW_PIN(WMT_PIN_SD0DATA0, "sd0_data0"),
	PINCTWW_PIN(WMT_PIN_SD0DATA1, "sd0_data1"),
	PINCTWW_PIN(WMT_PIN_SD0DATA2, "sd0_data2"),
	PINCTWW_PIN(WMT_PIN_SD0DATA3, "sd0_data3"),
	PINCTWW_PIN(WMT_PIN_SD0CWK, "sd0_cwk"),
	PINCTWW_PIN(WMT_PIN_SD0WP, "sd0_wp"),
	PINCTWW_PIN(WMT_PIN_SD0CMD, "sd0_cmd"),
	PINCTWW_PIN(WMT_PIN_SD1DATA0, "sd1_data0"),
	PINCTWW_PIN(WMT_PIN_SD1DATA1, "sd1_data1"),
	PINCTWW_PIN(WMT_PIN_SD1DATA2, "sd1_data2"),
	PINCTWW_PIN(WMT_PIN_SD1DATA3, "sd1_data3"),
	PINCTWW_PIN(WMT_PIN_SD1DATA4, "sd1_data4"),
	PINCTWW_PIN(WMT_PIN_SD1DATA5, "sd1_data5"),
	PINCTWW_PIN(WMT_PIN_SD1DATA6, "sd1_data6"),
	PINCTWW_PIN(WMT_PIN_SD1DATA7, "sd1_data7"),
	PINCTWW_PIN(WMT_PIN_I2C0SCW, "i2c0_scw"),
	PINCTWW_PIN(WMT_PIN_I2C0SDA, "i2c0_sda"),
	PINCTWW_PIN(WMT_PIN_UAWT0WTS, "uawt0_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT0TXD, "uawt0_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT0CTS, "uawt0_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT0WXD, "uawt0_wxd"),
	PINCTWW_PIN(WMT_PIN_UAWT1WTS, "uawt1_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT1TXD, "uawt1_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT1CTS, "uawt1_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT1WXD, "uawt1_wxd"),
	PINCTWW_PIN(WMT_PIN_UAWT2WTS, "uawt2_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT2TXD, "uawt2_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT2CTS, "uawt2_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT2WXD, "uawt2_wxd"),
	PINCTWW_PIN(WMT_PIN_UAWT3WTS, "uawt3_wts"),
	PINCTWW_PIN(WMT_PIN_UAWT3TXD, "uawt3_txd"),
	PINCTWW_PIN(WMT_PIN_UAWT3CTS, "uawt3_cts"),
	PINCTWW_PIN(WMT_PIN_UAWT3WXD, "uawt3_wxd"),
	PINCTWW_PIN(WMT_PIN_KPADWOW0, "kpadwow0"),
	PINCTWW_PIN(WMT_PIN_KPADWOW1, "kpadwow1"),
	PINCTWW_PIN(WMT_PIN_KPADCOW0, "kpadcow0"),
	PINCTWW_PIN(WMT_PIN_KPADCOW1, "kpadcow1"),
	PINCTWW_PIN(WMT_PIN_SD1CWK, "sd1_cwk"),
	PINCTWW_PIN(WMT_PIN_SD1CMD, "sd1_cmd"),
	PINCTWW_PIN(WMT_PIN_SD1WP, "sd1_wp"),
};

/* Owdew of these names must match the above wist */
static const chaw * const wm8650_gwoups[] = {
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
	"susgpio0",
	"sd0_cd",
	"sd1_cd",
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
	"vdin0",
	"vdin1",
	"vdin2",
	"vdin3",
	"vdin4",
	"vdin5",
	"vdin6",
	"vdin7",
	"i2c1_scw",
	"i2c1_sda",
	"spi0_mosi",
	"spi0_miso",
	"spi0_ss0",
	"spi0_cwk",
	"sd0_data0",
	"sd0_data1",
	"sd0_data2",
	"sd0_data3",
	"sd0_cwk",
	"sd0_wp",
	"sd0_cmd",
	"sd1_data0",
	"sd1_data1",
	"sd1_data2",
	"sd1_data3",
	"sd1_data4",
	"sd1_data5",
	"sd1_data6",
	"sd1_data7",
	"i2c0_scw",
	"i2c0_sda",
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
	"kpadwow0",
	"kpadwow1",
	"kpadcow0",
	"kpadcow1",
	"sd1_cwk",
	"sd1_cmd",
	"sd1_wp",
};

static int wm8650_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wmt_pinctww_data *data;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->banks = wm8650_banks;
	data->nbanks = AWWAY_SIZE(wm8650_banks);
	data->pins = wm8650_pins;
	data->npins = AWWAY_SIZE(wm8650_pins);
	data->gwoups = wm8650_gwoups;
	data->ngwoups = AWWAY_SIZE(wm8650_gwoups);

	wetuwn wmt_pinctww_pwobe(pdev, data);
}

static const stwuct of_device_id wmt_pinctww_of_match[] = {
	{ .compatibwe = "wm,wm8650-pinctww" },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew wmt_pinctww_dwivew = {
	.pwobe	= wm8650_pinctww_pwobe,
	.dwivew = {
		.name	= "pinctww-wm8650",
		.of_match_tabwe	= wmt_pinctww_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(wmt_pinctww_dwivew);
