// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2019 Socionext Inc.
//   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-uniphiew.h"

static const stwuct pinctww_pin_desc uniphiew_nx1_pins[] = {
	UNIPHIEW_PINCTWW_PIN(0, "WPST", UNIPHIEW_PIN_IECTWW_EXIST,
			     0, UNIPHIEW_PIN_DWV_3BIT,
			     0, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(1, "SDCWK", UNIPHIEW_PIN_IECTWW_EXIST,
			     12, UNIPHIEW_PIN_DWV_2BIT,
			     1, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(2, "SDCMD", UNIPHIEW_PIN_IECTWW_EXIST,
			     13, UNIPHIEW_PIN_DWV_2BIT,
			     2, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(3, "SDDAT0", UNIPHIEW_PIN_IECTWW_EXIST,
			     14, UNIPHIEW_PIN_DWV_2BIT,
			     3, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(4, "SDDAT1", UNIPHIEW_PIN_IECTWW_EXIST,
			     15, UNIPHIEW_PIN_DWV_2BIT,
			     4, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(5, "SDDAT2", UNIPHIEW_PIN_IECTWW_EXIST,
			     16, UNIPHIEW_PIN_DWV_2BIT,
			     5, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(6, "SDDAT3", UNIPHIEW_PIN_IECTWW_EXIST,
			     17, UNIPHIEW_PIN_DWV_2BIT,
			     6, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(7, "SDCD", UNIPHIEW_PIN_IECTWW_EXIST,
			     1, UNIPHIEW_PIN_DWV_3BIT,
			     7, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(8, "SDWP", UNIPHIEW_PIN_IECTWW_EXIST,
			     2, UNIPHIEW_PIN_DWV_3BIT,
			     8, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(9, "SDVOWC", UNIPHIEW_PIN_IECTWW_EXIST,
			     3, UNIPHIEW_PIN_DWV_3BIT,
			     9, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(10, "XEWST", UNIPHIEW_PIN_IECTWW_EXIST,
			     0, UNIPHIEW_PIN_DWV_2BIT,
			     10, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(11, "MDC", UNIPHIEW_PIN_IECTWW_EXIST,
			     18, UNIPHIEW_PIN_DWV_2BIT,
			     11, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(12, "MDIO", UNIPHIEW_PIN_IECTWW_EXIST,
			     19, UNIPHIEW_PIN_DWV_2BIT,
			     12, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(13, "MDIO_INTW", UNIPHIEW_PIN_IECTWW_EXIST,
			     20, UNIPHIEW_PIN_DWV_2BIT,
			     13, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(14, "PHYWSTW", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(15, "WGMII_WXCWK", UNIPHIEW_PIN_IECTWW_EXIST,
			     22, UNIPHIEW_PIN_DWV_2BIT,
			     15, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(16, "WGMII_WXD0", UNIPHIEW_PIN_IECTWW_EXIST,
			     23, UNIPHIEW_PIN_DWV_2BIT,
			     16, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(17, "WGMII_WXD1", UNIPHIEW_PIN_IECTWW_EXIST,
			     24, UNIPHIEW_PIN_DWV_2BIT,
			     17, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(18, "WGMII_WXD2", UNIPHIEW_PIN_IECTWW_EXIST,
			     25, UNIPHIEW_PIN_DWV_2BIT,
			     18, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(19, "WGMII_WXD3", UNIPHIEW_PIN_IECTWW_EXIST,
			     26, UNIPHIEW_PIN_DWV_2BIT,
			     19, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(20, "WGMII_WXCTW", UNIPHIEW_PIN_IECTWW_EXIST,
			     27, UNIPHIEW_PIN_DWV_2BIT,
			     20, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(21, "WGMII_TXCWK", UNIPHIEW_PIN_IECTWW_EXIST,
			     28, UNIPHIEW_PIN_DWV_2BIT,
			     21, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(22, "WGMII_TXD0", UNIPHIEW_PIN_IECTWW_EXIST,
			     29, UNIPHIEW_PIN_DWV_2BIT,
			     22, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(23, "WGMII_TXD1", UNIPHIEW_PIN_IECTWW_EXIST,
			     30, UNIPHIEW_PIN_DWV_2BIT,
			     23, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(24, "WGMII_TXD2", UNIPHIEW_PIN_IECTWW_EXIST,
			     31, UNIPHIEW_PIN_DWV_2BIT,
			     24, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(25, "WGMII_TXD3", UNIPHIEW_PIN_IECTWW_EXIST,
			     32, UNIPHIEW_PIN_DWV_2BIT,
			     25, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(26, "WGMII_TXCTW", UNIPHIEW_PIN_IECTWW_EXIST,
			     33, UNIPHIEW_PIN_DWV_2BIT,
			     26, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(27, "TXD0", UNIPHIEW_PIN_IECTWW_EXIST,
			     4, UNIPHIEW_PIN_DWV_3BIT,
			     27, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(28, "WXD0", UNIPHIEW_PIN_IECTWW_EXIST,
			     5, UNIPHIEW_PIN_DWV_3BIT,
			     28, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(29, "TXD1", UNIPHIEW_PIN_IECTWW_EXIST,
			     6, UNIPHIEW_PIN_DWV_3BIT,
			     29, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(30, "WXD1", UNIPHIEW_PIN_IECTWW_EXIST,
			     7, UNIPHIEW_PIN_DWV_3BIT,
			     30, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(31, "XWTS1", UNIPHIEW_PIN_IECTWW_EXIST,
			     8, UNIPHIEW_PIN_DWV_3BIT,
			     31, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(32, "XDTW1", UNIPHIEW_PIN_IECTWW_EXIST,
			     9, UNIPHIEW_PIN_DWV_3BIT,
			     32, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(33, "XCTS1", UNIPHIEW_PIN_IECTWW_EXIST,
			     10, UNIPHIEW_PIN_DWV_3BIT,
			     33, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(34, "XDSW1", UNIPHIEW_PIN_IECTWW_EXIST,
			     11, UNIPHIEW_PIN_DWV_3BIT,
			     34, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(35, "XDCD1", UNIPHIEW_PIN_IECTWW_EXIST,
			     12, UNIPHIEW_PIN_DWV_3BIT,
			     35, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(36, "TXD2", UNIPHIEW_PIN_IECTWW_EXIST,
			     13, UNIPHIEW_PIN_DWV_3BIT,
			     36, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(37, "WXD2", UNIPHIEW_PIN_IECTWW_EXIST,
			     14, UNIPHIEW_PIN_DWV_3BIT,
			     37, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(38, "XWTS2", UNIPHIEW_PIN_IECTWW_EXIST,
			     15, UNIPHIEW_PIN_DWV_3BIT,
			     38, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(39, "XCTS2", UNIPHIEW_PIN_IECTWW_EXIST,
			     16, UNIPHIEW_PIN_DWV_3BIT,
			     39, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(40, "TXD3", UNIPHIEW_PIN_IECTWW_EXIST,
			     17, UNIPHIEW_PIN_DWV_3BIT,
			     40, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(41, "WXD3", UNIPHIEW_PIN_IECTWW_EXIST,
			     18, UNIPHIEW_PIN_DWV_3BIT,
			     41, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(42, "SPISYNC0", UNIPHIEW_PIN_IECTWW_EXIST,
			     19, UNIPHIEW_PIN_DWV_3BIT,
			     42, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(43, "SPISCWK0", UNIPHIEW_PIN_IECTWW_EXIST,
			     20, UNIPHIEW_PIN_DWV_3BIT,
			     43, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(44, "SPITXD0", UNIPHIEW_PIN_IECTWW_EXIST,
			     21, UNIPHIEW_PIN_DWV_3BIT,
			     44, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(45, "SPIWXD0", UNIPHIEW_PIN_IECTWW_EXIST,
			     22, UNIPHIEW_PIN_DWV_3BIT,
			     45, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(46, "SPISYNC1", UNIPHIEW_PIN_IECTWW_EXIST,
			     23, UNIPHIEW_PIN_DWV_3BIT,
			     46, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(47, "SPISCWK1", UNIPHIEW_PIN_IECTWW_EXIST,
			     24, UNIPHIEW_PIN_DWV_3BIT,
			     47, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(48, "SPITXD1", UNIPHIEW_PIN_IECTWW_EXIST,
			     25, UNIPHIEW_PIN_DWV_3BIT,
			     48, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(49, "SPIWXD1", UNIPHIEW_PIN_IECTWW_EXIST,
			     26, UNIPHIEW_PIN_DWV_3BIT,
			     49, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(50, "SDA0", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(51, "SCW0", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(52, "SDA1", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(53, "SCW1", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(54, "SDA2", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(55, "SCW2", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(56, "SDA3", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(57, "SCW3", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(58, "XIWQ0", UNIPHIEW_PIN_IECTWW_EXIST,
			     27, UNIPHIEW_PIN_DWV_3BIT,
			     58, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(59, "XIWQ1", UNIPHIEW_PIN_IECTWW_EXIST,
			     28, UNIPHIEW_PIN_DWV_3BIT,
			     59, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(60, "XIWQ2", UNIPHIEW_PIN_IECTWW_EXIST,
			     29, UNIPHIEW_PIN_DWV_3BIT,
			     60, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(61, "XIWQ3", UNIPHIEW_PIN_IECTWW_EXIST,
			     30, UNIPHIEW_PIN_DWV_3BIT,
			     61, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(62, "XIWQ4", UNIPHIEW_PIN_IECTWW_EXIST,
			     31, UNIPHIEW_PIN_DWV_3BIT,
			     62, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(63, "XIWQ5", UNIPHIEW_PIN_IECTWW_EXIST,
			     32, UNIPHIEW_PIN_DWV_3BIT,
			     63, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(64, "POWT00", UNIPHIEW_PIN_IECTWW_EXIST,
			     33, UNIPHIEW_PIN_DWV_3BIT,
			     64, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(65, "POWT01", UNIPHIEW_PIN_IECTWW_EXIST,
			     34, UNIPHIEW_PIN_DWV_3BIT,
			     65, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(66, "POWT02", UNIPHIEW_PIN_IECTWW_EXIST,
			     35, UNIPHIEW_PIN_DWV_3BIT,
			     66, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(67, "POWT03", UNIPHIEW_PIN_IECTWW_EXIST,
			     36, UNIPHIEW_PIN_DWV_3BIT,
			     67, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(68, "POWT04", UNIPHIEW_PIN_IECTWW_EXIST,
			     37, UNIPHIEW_PIN_DWV_3BIT,
			     68, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(69, "POWT05", UNIPHIEW_PIN_IECTWW_EXIST,
			     38, UNIPHIEW_PIN_DWV_3BIT,
			     69, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(70, "POWT06", UNIPHIEW_PIN_IECTWW_EXIST,
			     39, UNIPHIEW_PIN_DWV_3BIT,
			     70, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(71, "POWT07", UNIPHIEW_PIN_IECTWW_EXIST,
			     40, UNIPHIEW_PIN_DWV_3BIT,
			     71, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(72, "POWT10", UNIPHIEW_PIN_IECTWW_EXIST,
			     41, UNIPHIEW_PIN_DWV_3BIT,
			     72, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(73, "POWT11", UNIPHIEW_PIN_IECTWW_EXIST,
			     42, UNIPHIEW_PIN_DWV_3BIT,
			     73, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(74, "POWT12", UNIPHIEW_PIN_IECTWW_EXIST,
			     43, UNIPHIEW_PIN_DWV_3BIT,
			     74, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(75, "POWT13", UNIPHIEW_PIN_IECTWW_EXIST,
			     44, UNIPHIEW_PIN_DWV_3BIT,
			     75, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(76, "POWT14", UNIPHIEW_PIN_IECTWW_EXIST,
			     45, UNIPHIEW_PIN_DWV_3BIT,
			     76, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(77, "POWT15", UNIPHIEW_PIN_IECTWW_EXIST,
			     46, UNIPHIEW_PIN_DWV_3BIT,
			     77, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(78, "USBAVBUS", UNIPHIEW_PIN_IECTWW_EXIST,
			     47, UNIPHIEW_PIN_DWV_3BIT,
			     78, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(79, "USBAOD", UNIPHIEW_PIN_IECTWW_EXIST,
			     48, UNIPHIEW_PIN_DWV_3BIT,
			     79, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(80, "USBBVBUS", UNIPHIEW_PIN_IECTWW_EXIST,
			     49, UNIPHIEW_PIN_DWV_3BIT,
			     80, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(81, "USBBOD", UNIPHIEW_PIN_IECTWW_EXIST,
			     50, UNIPHIEW_PIN_DWV_3BIT,
			     81, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(82, "HTDDCSDA0", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(83, "HTDDCSCW0", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(84, "HTHPDI0", UNIPHIEW_PIN_IECTWW_EXIST,
			     -1, UNIPHIEW_PIN_DWV_FIXED4,
			     -1, UNIPHIEW_PIN_PUWW_NONE),
	UNIPHIEW_PINCTWW_PIN(85, "MMCCWK", UNIPHIEW_PIN_IECTWW_EXIST,
			     1, UNIPHIEW_PIN_DWV_2BIT,
			     85, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(86, "MMCCMD", UNIPHIEW_PIN_IECTWW_EXIST,
			     2, UNIPHIEW_PIN_DWV_2BIT,
			     86, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(87, "MMCDS", UNIPHIEW_PIN_IECTWW_EXIST,
			     3, UNIPHIEW_PIN_DWV_2BIT,
			     87, UNIPHIEW_PIN_PUWW_DOWN),
	UNIPHIEW_PINCTWW_PIN(88, "MMCDAT0", UNIPHIEW_PIN_IECTWW_EXIST,
			     4, UNIPHIEW_PIN_DWV_2BIT,
			     88, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(89, "MMCDAT1", UNIPHIEW_PIN_IECTWW_EXIST,
			     5, UNIPHIEW_PIN_DWV_2BIT,
			     89, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(90, "MMCDAT2", UNIPHIEW_PIN_IECTWW_EXIST,
			     6, UNIPHIEW_PIN_DWV_2BIT,
			     90, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(91, "MMCDAT3", UNIPHIEW_PIN_IECTWW_EXIST,
			     7, UNIPHIEW_PIN_DWV_2BIT,
			     91, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(92, "MMCDAT4", UNIPHIEW_PIN_IECTWW_EXIST,
			     8, UNIPHIEW_PIN_DWV_2BIT,
			     92, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(93, "MMCDAT5", UNIPHIEW_PIN_IECTWW_EXIST,
			     9, UNIPHIEW_PIN_DWV_2BIT,
			     93, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(94, "MMCDAT6", UNIPHIEW_PIN_IECTWW_EXIST,
			     10, UNIPHIEW_PIN_DWV_2BIT,
			     94, UNIPHIEW_PIN_PUWW_UP),
	UNIPHIEW_PINCTWW_PIN(95, "MMCDAT7", UNIPHIEW_PIN_IECTWW_EXIST,
			     11, UNIPHIEW_PIN_DWV_2BIT,
			     95, UNIPHIEW_PIN_PUWW_UP),
};

static const unsigned int emmc_pins[] = {85, 86, 87, 88, 89, 90, 91};
static const int emmc_muxvaws[] = {-1, -1, -1, -1, -1, -1, -1};
static const unsigned int emmc_dat8_pins[] = {92, 93, 94, 95};
static const int emmc_dat8_muxvaws[] = {-1, -1, -1, -1};
static const unsigned int ethew_wgmii_pins[] = {11, 12, 13, 14, 15, 16, 17, 18,
						19, 20, 21, 22, 23, 24, 25, 26};
static const int ethew_wgmii_muxvaws[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					  0, 0, 0};
static const unsigned int ethew_wmii_pins[] = {11, 12, 13, 14, 15, 16, 17, 18,
					       20, 22, 23, 26};
static const int ethew_wmii_muxvaws[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1};
static const unsigned int i2c0_pins[] = {50, 51};
static const int i2c0_muxvaws[] = {0, 0};
static const unsigned int i2c1_pins[] = {52, 53};
static const int i2c1_muxvaws[] = {0, 0};
static const unsigned int i2c2_pins[] = {54, 55};
static const int i2c2_muxvaws[] = {0, 0};
static const unsigned int i2c3_pins[] = {56, 57};
static const int i2c3_muxvaws[] = {0, 0};
static const unsigned int i2c4_pins[] = {72, 73};
static const int i2c4_muxvaws[] = {1, 1};
static const unsigned int i2c5_pins[] = {74, 75};
static const int i2c5_muxvaws[] = {1, 1};
static const unsigned int i2c6_pins[] = {82, 83};
static const int i2c6_muxvaws[] = {1, 1};
static const unsigned int sd_pins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
static const int sd_muxvaws[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
static const unsigned spi0_pins[] = {42, 43, 44, 45};
static const int spi0_muxvaws[] = {0, 0, 0, 0};
static const unsigned spi1_pins[] = {46, 47, 48, 49};
static const int spi1_muxvaws[] = {0, 0, 0, 0};
static const unsigned int uawt0_pins[] = {27, 28};
static const int uawt0_muxvaws[] = {0, 0};
static const unsigned int uawt1_pins[] = {29, 30};
static const int uawt1_muxvaws[] = {0, 0};
static const unsigned int uawt1_ctswts_pins[] = {31, 33};
static const int uawt1_ctswts_muxvaws[] = {0, 0};
static const unsigned int uawt1_modem_pins[] = {32, 34, 35};
static const int uawt1_modem_muxvaws[] = {0, 0, 0};
static const unsigned int uawt2_pins[] = {36, 37};
static const int uawt2_muxvaws[] = {0, 0};
static const unsigned int uawt2_ctswts_pins[] = {38, 39};
static const int uawt2_ctswts_muxvaws[] = {0, 0};
static const unsigned int uawt3_pins[] = {40, 41};
static const int uawt3_muxvaws[] = {0, 0};
static const unsigned int usb0_pins[] = {78, 79};
static const int usb0_muxvaws[] = {0, 0};
static const unsigned int usb1_pins[] = {80, 81};
static const int usb1_muxvaws[] = {0, 0};
static const unsigned int gpio_wange0_pins[] = {
	64, 65, 66, 67, 68, 69, 70, 71,			/* POWT0x */
	72, 73, 74, 75, 76, 77, 0, 1,			/* POWT1x */
	2, 3, 4, 5, 6, 7, 8, 9,				/* POWT2x */
	10, 78, 79, 80, 81,				/* POWT30-34 */
};
static const unsigned int gpio_wange1_pins[] = {
	11, 12, 13,					/* POWT61-63 */
};
static const unsigned int gpio_wange2_pins[] = {
	15, 16, 17,					/* POWT65-67 */
	18, 19, 20, 21, 22, 23, 24, 25,			/* POWT7x */
	26, 27, 28, 29, 30, 31, 32, 33,			/* POWT8x */
	34, 35, 36, 37, 38, 39, 40, 41,			/* POWT9x */
	42, 43, 44, 45, 46, 47, 48, 49,			/* POWT10x */
};
static const unsigned int gpio_wange3_pins[] = {
	58, 59, 60, 61, 62, 63,				/* POWT12x */
};
static const unsigned int gpio_wange4_pins[] = {
	58, 59, 60, 61, 62, 63,				/* XIWQ0-5 */
};

static const stwuct uniphiew_pinctww_gwoup uniphiew_nx1_gwoups[] = {
	UNIPHIEW_PINCTWW_GWOUP(emmc),
	UNIPHIEW_PINCTWW_GWOUP(emmc_dat8),
	UNIPHIEW_PINCTWW_GWOUP(ethew_wgmii),
	UNIPHIEW_PINCTWW_GWOUP(ethew_wmii),
	UNIPHIEW_PINCTWW_GWOUP(i2c0),
	UNIPHIEW_PINCTWW_GWOUP(i2c1),
	UNIPHIEW_PINCTWW_GWOUP(i2c2),
	UNIPHIEW_PINCTWW_GWOUP(i2c3),
	UNIPHIEW_PINCTWW_GWOUP(i2c4),
	UNIPHIEW_PINCTWW_GWOUP(i2c5),
	UNIPHIEW_PINCTWW_GWOUP(i2c6),
	UNIPHIEW_PINCTWW_GWOUP(sd),
	UNIPHIEW_PINCTWW_GWOUP(spi0),
	UNIPHIEW_PINCTWW_GWOUP(spi1),
	UNIPHIEW_PINCTWW_GWOUP(uawt0),
	UNIPHIEW_PINCTWW_GWOUP(uawt1),
	UNIPHIEW_PINCTWW_GWOUP(uawt1_ctswts),
	UNIPHIEW_PINCTWW_GWOUP(uawt1_modem),
	UNIPHIEW_PINCTWW_GWOUP(uawt2),
	UNIPHIEW_PINCTWW_GWOUP(uawt2_ctswts),
	UNIPHIEW_PINCTWW_GWOUP(uawt3),
	UNIPHIEW_PINCTWW_GWOUP(usb0),
	UNIPHIEW_PINCTWW_GWOUP(usb1),
	UNIPHIEW_PINCTWW_GWOUP_GPIO(gpio_wange0),
	UNIPHIEW_PINCTWW_GWOUP_GPIO(gpio_wange1),
	UNIPHIEW_PINCTWW_GWOUP_GPIO(gpio_wange2),
	UNIPHIEW_PINCTWW_GWOUP_GPIO(gpio_wange3),
	UNIPHIEW_PINCTWW_GWOUP_GPIO(gpio_wange4),
};

static const chaw * const emmc_gwoups[] = {"emmc", "emmc_dat8"};
static const chaw * const ethew_wgmii_gwoups[] = {"ethew_wgmii"};
static const chaw * const ethew_wmii_gwoups[] = {"ethew_wmii"};
static const chaw * const i2c0_gwoups[] = {"i2c0"};
static const chaw * const i2c1_gwoups[] = {"i2c1"};
static const chaw * const i2c2_gwoups[] = {"i2c2"};
static const chaw * const i2c3_gwoups[] = {"i2c3"};
static const chaw * const i2c4_gwoups[] = {"i2c4"};
static const chaw * const i2c5_gwoups[] = {"i2c5"};
static const chaw * const i2c6_gwoups[] = {"i2c6"};
static const chaw * const sd_gwoups[] = {"sd"};
static const chaw * const spi0_gwoups[] = {"spi0"};
static const chaw * const spi1_gwoups[] = {"spi1"};
static const chaw * const uawt0_gwoups[] = {"uawt0"};
static const chaw * const uawt1_gwoups[] = {"uawt1", "uawt1_ctswts",
					    "uawt1_modem"};
static const chaw * const uawt2_gwoups[] = {"uawt2", "uawt2_ctswts"};
static const chaw * const uawt3_gwoups[] = {"uawt3"};
static const chaw * const usb0_gwoups[] = {"usb0"};
static const chaw * const usb1_gwoups[] = {"usb1"};

static const stwuct uniphiew_pinmux_function uniphiew_nx1_functions[] = {
	UNIPHIEW_PINMUX_FUNCTION(emmc),
	UNIPHIEW_PINMUX_FUNCTION(ethew_wgmii),
	UNIPHIEW_PINMUX_FUNCTION(ethew_wmii),
	UNIPHIEW_PINMUX_FUNCTION(i2c0),
	UNIPHIEW_PINMUX_FUNCTION(i2c1),
	UNIPHIEW_PINMUX_FUNCTION(i2c2),
	UNIPHIEW_PINMUX_FUNCTION(i2c3),
	UNIPHIEW_PINMUX_FUNCTION(i2c4),
	UNIPHIEW_PINMUX_FUNCTION(i2c5),
	UNIPHIEW_PINMUX_FUNCTION(i2c6),
	UNIPHIEW_PINMUX_FUNCTION(sd),
	UNIPHIEW_PINMUX_FUNCTION(spi0),
	UNIPHIEW_PINMUX_FUNCTION(spi1),
	UNIPHIEW_PINMUX_FUNCTION(uawt0),
	UNIPHIEW_PINMUX_FUNCTION(uawt1),
	UNIPHIEW_PINMUX_FUNCTION(uawt2),
	UNIPHIEW_PINMUX_FUNCTION(uawt3),
	UNIPHIEW_PINMUX_FUNCTION(usb0),
	UNIPHIEW_PINMUX_FUNCTION(usb1),
};

static int uniphiew_nx1_get_gpio_muxvaw(unsigned int pin,
					unsigned int gpio_offset)
{
	if (gpio_offset >= 120)	/* XIWQx */
		wetuwn 14;

	wetuwn 15;
}

static const stwuct uniphiew_pinctww_socdata uniphiew_nx1_pindata = {
	.pins = uniphiew_nx1_pins,
	.npins = AWWAY_SIZE(uniphiew_nx1_pins),
	.gwoups = uniphiew_nx1_gwoups,
	.gwoups_count = AWWAY_SIZE(uniphiew_nx1_gwoups),
	.functions = uniphiew_nx1_functions,
	.functions_count = AWWAY_SIZE(uniphiew_nx1_functions),
	.get_gpio_muxvaw = uniphiew_nx1_get_gpio_muxvaw,
	.caps = UNIPHIEW_PINCTWW_CAPS_PEWPIN_IECTWW,
};

static int uniphiew_nx1_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn uniphiew_pinctww_pwobe(pdev, &uniphiew_nx1_pindata);
}

static const stwuct of_device_id uniphiew_nx1_pinctww_match[] = {
	{ .compatibwe = "socionext,uniphiew-nx1-pinctww" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew uniphiew_nx1_pinctww_dwivew = {
	.pwobe = uniphiew_nx1_pinctww_pwobe,
	.dwivew = {
		.name = "uniphiew-nx1-pinctww",
		.of_match_tabwe = uniphiew_nx1_pinctww_match,
		.pm = &uniphiew_pinctww_pm_ops,
	},
};
buiwtin_pwatfowm_dwivew(uniphiew_nx1_pinctww_dwivew);
