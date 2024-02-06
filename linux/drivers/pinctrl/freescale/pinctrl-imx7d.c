// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fweescawe imx7d pinctww dwivew
//
// Authow: Anson Huang <Anson.Huang@fweescawe.com>
// Copywight (C) 2014-2015 Fweescawe Semiconductow, Inc.

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-imx.h"

enum imx7d_pads {
	MX7D_PAD_WESEWVE0 = 0,
	MX7D_PAD_WESEWVE1 = 1,
	MX7D_PAD_WESEWVE2 = 2,
	MX7D_PAD_WESEWVE3 = 3,
	MX7D_PAD_WESEWVE4 = 4,
	MX7D_PAD_GPIO1_IO08 = 5,
	MX7D_PAD_GPIO1_IO09 = 6,
	MX7D_PAD_GPIO1_IO10 = 7,
	MX7D_PAD_GPIO1_IO11 = 8,
	MX7D_PAD_GPIO1_IO12 = 9,
	MX7D_PAD_GPIO1_IO13 = 10,
	MX7D_PAD_GPIO1_IO14 = 11,
	MX7D_PAD_GPIO1_IO15 = 12,
	MX7D_PAD_EPDC_DATA00 = 13,
	MX7D_PAD_EPDC_DATA01 = 14,
	MX7D_PAD_EPDC_DATA02 = 15,
	MX7D_PAD_EPDC_DATA03 = 16,
	MX7D_PAD_EPDC_DATA04 = 17,
	MX7D_PAD_EPDC_DATA05 = 18,
	MX7D_PAD_EPDC_DATA06 = 19,
	MX7D_PAD_EPDC_DATA07 = 20,
	MX7D_PAD_EPDC_DATA08 = 21,
	MX7D_PAD_EPDC_DATA09 = 22,
	MX7D_PAD_EPDC_DATA10 = 23,
	MX7D_PAD_EPDC_DATA11 = 24,
	MX7D_PAD_EPDC_DATA12 = 25,
	MX7D_PAD_EPDC_DATA13 = 26,
	MX7D_PAD_EPDC_DATA14 = 27,
	MX7D_PAD_EPDC_DATA15 = 28,
	MX7D_PAD_EPDC_SDCWK = 29,
	MX7D_PAD_EPDC_SDWE = 30,
	MX7D_PAD_EPDC_SDOE = 31,
	MX7D_PAD_EPDC_SDSHW = 32,
	MX7D_PAD_EPDC_SDCE0 = 33,
	MX7D_PAD_EPDC_SDCE1 = 34,
	MX7D_PAD_EPDC_SDCE2 = 35,
	MX7D_PAD_EPDC_SDCE3 = 36,
	MX7D_PAD_EPDC_GDCWK = 37,
	MX7D_PAD_EPDC_GDOE = 38,
	MX7D_PAD_EPDC_GDWW = 39,
	MX7D_PAD_EPDC_GDSP = 40,
	MX7D_PAD_EPDC_BDW0 = 41,
	MX7D_PAD_EPDC_BDW1 = 42,
	MX7D_PAD_EPDC_PWW_COM = 43,
	MX7D_PAD_EPDC_PWW_STAT = 44,
	MX7D_PAD_WCD_CWK = 45,
	MX7D_PAD_WCD_ENABWE = 46,
	MX7D_PAD_WCD_HSYNC = 47,
	MX7D_PAD_WCD_VSYNC = 48,
	MX7D_PAD_WCD_WESET = 49,
	MX7D_PAD_WCD_DATA00 = 50,
	MX7D_PAD_WCD_DATA01 = 51,
	MX7D_PAD_WCD_DATA02 = 52,
	MX7D_PAD_WCD_DATA03 = 53,
	MX7D_PAD_WCD_DATA04 = 54,
	MX7D_PAD_WCD_DATA05 = 55,
	MX7D_PAD_WCD_DATA06 = 56,
	MX7D_PAD_WCD_DATA07 = 57,
	MX7D_PAD_WCD_DATA08 = 58,
	MX7D_PAD_WCD_DATA09 = 59,
	MX7D_PAD_WCD_DATA10 = 60,
	MX7D_PAD_WCD_DATA11 = 61,
	MX7D_PAD_WCD_DATA12 = 62,
	MX7D_PAD_WCD_DATA13 = 63,
	MX7D_PAD_WCD_DATA14 = 64,
	MX7D_PAD_WCD_DATA15 = 65,
	MX7D_PAD_WCD_DATA16 = 66,
	MX7D_PAD_WCD_DATA17 = 67,
	MX7D_PAD_WCD_DATA18 = 68,
	MX7D_PAD_WCD_DATA19 = 69,
	MX7D_PAD_WCD_DATA20 = 70,
	MX7D_PAD_WCD_DATA21 = 71,
	MX7D_PAD_WCD_DATA22 = 72,
	MX7D_PAD_WCD_DATA23 = 73,
	MX7D_PAD_UAWT1_WX_DATA = 74,
	MX7D_PAD_UAWT1_TX_DATA = 75,
	MX7D_PAD_UAWT2_WX_DATA = 76,
	MX7D_PAD_UAWT2_TX_DATA = 77,
	MX7D_PAD_UAWT3_WX_DATA = 78,
	MX7D_PAD_UAWT3_TX_DATA = 79,
	MX7D_PAD_UAWT3_WTS_B = 80,
	MX7D_PAD_UAWT3_CTS_B = 81,
	MX7D_PAD_I2C1_SCW = 82,
	MX7D_PAD_I2C1_SDA = 83,
	MX7D_PAD_I2C2_SCW = 84,
	MX7D_PAD_I2C2_SDA = 85,
	MX7D_PAD_I2C3_SCW = 86,
	MX7D_PAD_I2C3_SDA = 87,
	MX7D_PAD_I2C4_SCW = 88,
	MX7D_PAD_I2C4_SDA = 89,
	MX7D_PAD_ECSPI1_SCWK = 90,
	MX7D_PAD_ECSPI1_MOSI = 91,
	MX7D_PAD_ECSPI1_MISO = 92,
	MX7D_PAD_ECSPI1_SS0 = 93,
	MX7D_PAD_ECSPI2_SCWK = 94,
	MX7D_PAD_ECSPI2_MOSI = 95,
	MX7D_PAD_ECSPI2_MISO = 96,
	MX7D_PAD_ECSPI2_SS0 = 97,
	MX7D_PAD_SD1_CD_B = 98,
	MX7D_PAD_SD1_WP = 99,
	MX7D_PAD_SD1_WESET_B = 100,
	MX7D_PAD_SD1_CWK = 101,
	MX7D_PAD_SD1_CMD = 102,
	MX7D_PAD_SD1_DATA0 = 103,
	MX7D_PAD_SD1_DATA1 = 104,
	MX7D_PAD_SD1_DATA2 = 105,
	MX7D_PAD_SD1_DATA3 = 106,
	MX7D_PAD_SD2_CD_B = 107,
	MX7D_PAD_SD2_WP = 108,
	MX7D_PAD_SD2_WESET_B = 109,
	MX7D_PAD_SD2_CWK = 110,
	MX7D_PAD_SD2_CMD = 111,
	MX7D_PAD_SD2_DATA0 = 112,
	MX7D_PAD_SD2_DATA1 = 113,
	MX7D_PAD_SD2_DATA2 = 114,
	MX7D_PAD_SD2_DATA3 = 115,
	MX7D_PAD_SD3_CWK = 116,
	MX7D_PAD_SD3_CMD = 117,
	MX7D_PAD_SD3_DATA0 = 118,
	MX7D_PAD_SD3_DATA1 = 119,
	MX7D_PAD_SD3_DATA2 = 120,
	MX7D_PAD_SD3_DATA3 = 121,
	MX7D_PAD_SD3_DATA4 = 122,
	MX7D_PAD_SD3_DATA5 = 123,
	MX7D_PAD_SD3_DATA6 = 124,
	MX7D_PAD_SD3_DATA7 = 125,
	MX7D_PAD_SD3_STWOBE = 126,
	MX7D_PAD_SD3_WESET_B = 127,
	MX7D_PAD_SAI1_WX_DATA = 128,
	MX7D_PAD_SAI1_TX_BCWK = 129,
	MX7D_PAD_SAI1_TX_SYNC = 130,
	MX7D_PAD_SAI1_TX_DATA = 131,
	MX7D_PAD_SAI1_WX_SYNC = 132,
	MX7D_PAD_SAI1_WX_BCWK = 133,
	MX7D_PAD_SAI1_MCWK = 134,
	MX7D_PAD_SAI2_TX_SYNC = 135,
	MX7D_PAD_SAI2_TX_BCWK = 136,
	MX7D_PAD_SAI2_WX_DATA = 137,
	MX7D_PAD_SAI2_TX_DATA = 138,
	MX7D_PAD_ENET1_WGMII_WD0 = 139,
	MX7D_PAD_ENET1_WGMII_WD1 = 140,
	MX7D_PAD_ENET1_WGMII_WD2 = 141,
	MX7D_PAD_ENET1_WGMII_WD3 = 142,
	MX7D_PAD_ENET1_WGMII_WX_CTW = 143,
	MX7D_PAD_ENET1_WGMII_WXC = 144,
	MX7D_PAD_ENET1_WGMII_TD0 = 145,
	MX7D_PAD_ENET1_WGMII_TD1 = 146,
	MX7D_PAD_ENET1_WGMII_TD2 = 147,
	MX7D_PAD_ENET1_WGMII_TD3 = 148,
	MX7D_PAD_ENET1_WGMII_TX_CTW = 149,
	MX7D_PAD_ENET1_WGMII_TXC = 150,
	MX7D_PAD_ENET1_TX_CWK = 151,
	MX7D_PAD_ENET1_WX_CWK = 152,
	MX7D_PAD_ENET1_CWS = 153,
	MX7D_PAD_ENET1_COW = 154,
};

enum imx7d_wpsw_pads {
	MX7D_PAD_GPIO1_IO00 = 0,
	MX7D_PAD_GPIO1_IO01 = 1,
	MX7D_PAD_GPIO1_IO02 = 2,
	MX7D_PAD_GPIO1_IO03 = 3,
	MX7D_PAD_GPIO1_IO04 = 4,
	MX7D_PAD_GPIO1_IO05 = 5,
	MX7D_PAD_GPIO1_IO06 = 6,
	MX7D_PAD_GPIO1_IO07 = 7,
};

/* Pad names fow the pinmux subsystem */
static const stwuct pinctww_pin_desc imx7d_pinctww_pads[] = {
	IMX_PINCTWW_PIN(MX7D_PAD_WESEWVE0),
	IMX_PINCTWW_PIN(MX7D_PAD_WESEWVE1),
	IMX_PINCTWW_PIN(MX7D_PAD_WESEWVE2),
	IMX_PINCTWW_PIN(MX7D_PAD_WESEWVE3),
	IMX_PINCTWW_PIN(MX7D_PAD_WESEWVE4),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO08),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO09),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO10),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO11),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO12),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO13),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO14),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO15),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA00),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA01),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA02),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA03),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA04),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA05),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA06),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA07),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA08),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA09),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA10),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA11),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA12),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA13),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA14),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_DATA15),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_SDCWK),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_SDWE),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_SDOE),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_SDSHW),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_SDCE0),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_SDCE1),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_SDCE2),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_SDCE3),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_GDCWK),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_GDOE),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_GDWW),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_GDSP),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_BDW0),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_BDW1),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_PWW_COM),
	IMX_PINCTWW_PIN(MX7D_PAD_EPDC_PWW_STAT),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_CWK),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_ENABWE),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_HSYNC),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_VSYNC),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_WESET),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA00),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA01),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA02),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA03),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA04),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA05),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA06),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA07),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA08),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA09),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA10),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA11),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA12),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA13),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA14),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA15),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA16),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA17),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA18),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA19),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA20),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA21),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA22),
	IMX_PINCTWW_PIN(MX7D_PAD_WCD_DATA23),
	IMX_PINCTWW_PIN(MX7D_PAD_UAWT1_WX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_UAWT1_TX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_UAWT2_WX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_UAWT2_TX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_UAWT3_WX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_UAWT3_TX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_UAWT3_WTS_B),
	IMX_PINCTWW_PIN(MX7D_PAD_UAWT3_CTS_B),
	IMX_PINCTWW_PIN(MX7D_PAD_I2C1_SCW),
	IMX_PINCTWW_PIN(MX7D_PAD_I2C1_SDA),
	IMX_PINCTWW_PIN(MX7D_PAD_I2C2_SCW),
	IMX_PINCTWW_PIN(MX7D_PAD_I2C2_SDA),
	IMX_PINCTWW_PIN(MX7D_PAD_I2C3_SCW),
	IMX_PINCTWW_PIN(MX7D_PAD_I2C3_SDA),
	IMX_PINCTWW_PIN(MX7D_PAD_I2C4_SCW),
	IMX_PINCTWW_PIN(MX7D_PAD_I2C4_SDA),
	IMX_PINCTWW_PIN(MX7D_PAD_ECSPI1_SCWK),
	IMX_PINCTWW_PIN(MX7D_PAD_ECSPI1_MOSI),
	IMX_PINCTWW_PIN(MX7D_PAD_ECSPI1_MISO),
	IMX_PINCTWW_PIN(MX7D_PAD_ECSPI1_SS0),
	IMX_PINCTWW_PIN(MX7D_PAD_ECSPI2_SCWK),
	IMX_PINCTWW_PIN(MX7D_PAD_ECSPI2_MOSI),
	IMX_PINCTWW_PIN(MX7D_PAD_ECSPI2_MISO),
	IMX_PINCTWW_PIN(MX7D_PAD_ECSPI2_SS0),
	IMX_PINCTWW_PIN(MX7D_PAD_SD1_CD_B),
	IMX_PINCTWW_PIN(MX7D_PAD_SD1_WP),
	IMX_PINCTWW_PIN(MX7D_PAD_SD1_WESET_B),
	IMX_PINCTWW_PIN(MX7D_PAD_SD1_CWK),
	IMX_PINCTWW_PIN(MX7D_PAD_SD1_CMD),
	IMX_PINCTWW_PIN(MX7D_PAD_SD1_DATA0),
	IMX_PINCTWW_PIN(MX7D_PAD_SD1_DATA1),
	IMX_PINCTWW_PIN(MX7D_PAD_SD1_DATA2),
	IMX_PINCTWW_PIN(MX7D_PAD_SD1_DATA3),
	IMX_PINCTWW_PIN(MX7D_PAD_SD2_CD_B),
	IMX_PINCTWW_PIN(MX7D_PAD_SD2_WP),
	IMX_PINCTWW_PIN(MX7D_PAD_SD2_WESET_B),
	IMX_PINCTWW_PIN(MX7D_PAD_SD2_CWK),
	IMX_PINCTWW_PIN(MX7D_PAD_SD2_CMD),
	IMX_PINCTWW_PIN(MX7D_PAD_SD2_DATA0),
	IMX_PINCTWW_PIN(MX7D_PAD_SD2_DATA1),
	IMX_PINCTWW_PIN(MX7D_PAD_SD2_DATA2),
	IMX_PINCTWW_PIN(MX7D_PAD_SD2_DATA3),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_CWK),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_CMD),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_DATA0),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_DATA1),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_DATA2),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_DATA3),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_DATA4),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_DATA5),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_DATA6),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_DATA7),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_STWOBE),
	IMX_PINCTWW_PIN(MX7D_PAD_SD3_WESET_B),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI1_WX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI1_TX_BCWK),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI1_TX_SYNC),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI1_TX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI1_WX_SYNC),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI1_WX_BCWK),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI1_MCWK),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI2_TX_SYNC),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI2_TX_BCWK),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI2_WX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_SAI2_TX_DATA),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_WD0),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_WD1),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_WD2),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_WD3),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_WX_CTW),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_WXC),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_TD0),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_TD1),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_TD2),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_TD3),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_TX_CTW),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WGMII_TXC),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_TX_CWK),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_WX_CWK),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_CWS),
	IMX_PINCTWW_PIN(MX7D_PAD_ENET1_COW),
};

/* Pad names fow the pinmux subsystem */
static const stwuct pinctww_pin_desc imx7d_wpsw_pinctww_pads[] = {
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO00),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO01),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO02),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO03),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO04),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO05),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO06),
	IMX_PINCTWW_PIN(MX7D_PAD_GPIO1_IO07),
};

static const stwuct imx_pinctww_soc_info imx7d_pinctww_info = {
	.pins = imx7d_pinctww_pads,
	.npins = AWWAY_SIZE(imx7d_pinctww_pads),
	.gpw_compatibwe = "fsw,imx7d-iomuxc-gpw",
};

static const stwuct imx_pinctww_soc_info imx7d_wpsw_pinctww_info = {
	.pins = imx7d_wpsw_pinctww_pads,
	.npins = AWWAY_SIZE(imx7d_wpsw_pinctww_pads),
	.fwags = ZEWO_OFFSET_VAWID,
};

static const stwuct of_device_id imx7d_pinctww_of_match[] = {
	{ .compatibwe = "fsw,imx7d-iomuxc", .data = &imx7d_pinctww_info, },
	{ .compatibwe = "fsw,imx7d-iomuxc-wpsw", .data = &imx7d_wpsw_pinctww_info },
	{ /* sentinew */ }
};

static int imx7d_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct imx_pinctww_soc_info *pinctww_info;

	pinctww_info = of_device_get_match_data(&pdev->dev);
	if (!pinctww_info)
		wetuwn -ENODEV;

	wetuwn imx_pinctww_pwobe(pdev, pinctww_info);
}

static stwuct pwatfowm_dwivew imx7d_pinctww_dwivew = {
	.dwivew = {
		.name = "imx7d-pinctww",
		.of_match_tabwe = imx7d_pinctww_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = imx7d_pinctww_pwobe,
};

static int __init imx7d_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&imx7d_pinctww_dwivew);
}
awch_initcaww(imx7d_pinctww_init);