// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww Awmada XP pinctww dwivew based on mvebu pinctww cowe
 *
 * Copywight (C) 2012 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * This fiwe suppowts the thwee vawiants of Awmada XP SoCs that awe
 * avaiwabwe: mv78230, mv78260 and mv78460. Fwom a pin muxing
 * pewspective, the mv78230 has 49 MPP pins. The mv78260 and mv78460
 * both have 67 MPP pins (mowe GPIOs and addwess wines fow the memowy
 * bus mainwy).
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwopewty.h>
#incwude <winux/bitops.h>

#incwude "pinctww-mvebu.h"

static u32 *mpp_saved_wegs;

enum awmada_xp_vawiant {
	V_MV78230	= BIT(0),
	V_MV78260	= BIT(1),
	V_MV78460	= BIT(2),
	V_MV78230_PWUS	= (V_MV78230 | V_MV78260 | V_MV78460),
	V_MV78260_PWUS	= (V_MV78260 | V_MV78460),
	V_98DX3236	= BIT(3),
	V_98DX3336	= BIT(4),
	V_98DX4251	= BIT(5),
	V_98DX3236_PWUS	= (V_98DX3236 | V_98DX3336 | V_98DX4251),
};

static stwuct mvebu_mpp_mode awmada_xp_mpp_modes[] = {
	MPP_MODE(0,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txcwkout",   V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d0",         V_MV78230_PWUS)),
	MPP_MODE(1,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txd0",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d1",         V_MV78230_PWUS)),
	MPP_MODE(2,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txd1",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d2",         V_MV78230_PWUS)),
	MPP_MODE(3,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txd2",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d3",         V_MV78230_PWUS)),
	MPP_MODE(4,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txd3",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d4",         V_MV78230_PWUS)),
	MPP_MODE(5,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txctw",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d5",         V_MV78230_PWUS)),
	MPP_MODE(6,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxd0",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d6",         V_MV78230_PWUS)),
	MPP_MODE(7,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxd1",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d7",         V_MV78230_PWUS)),
	MPP_MODE(8,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxd2",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d8",         V_MV78230_PWUS)),
	MPP_MODE(9,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxd3",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d9",         V_MV78230_PWUS)),
	MPP_MODE(10,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxctw",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d10",        V_MV78230_PWUS)),
	MPP_MODE(11,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxcwk",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d11",        V_MV78230_PWUS)),
	MPP_MODE(12,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txd4",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "txcwkout",   V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d12",        V_MV78230_PWUS)),
	MPP_MODE(13,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txd5",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "txd0",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "spi1", "mosi",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d13",        V_MV78230_PWUS)),
	MPP_MODE(14,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txd6",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "txd1",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "spi1", "sck",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d14",        V_MV78230_PWUS)),
	MPP_MODE(15,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txd7",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "txd2",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d15",        V_MV78230_PWUS)),
	MPP_MODE(16,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "txcwk",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "txd3",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "spi1", "cs0",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d16",        V_MV78230_PWUS)),
	MPP_MODE(17,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "cow",        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "txctw",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "spi1", "miso",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d17",        V_MV78230_PWUS)),
	MPP_MODE(18,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxeww",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "wxd0",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "ptp", "twig",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d18",        V_MV78230_PWUS)),
	MPP_MODE(19,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "cws",        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "wxd1",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "ptp", "evweq",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d19",        V_MV78230_PWUS)),
	MPP_MODE(20,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxd4",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "wxd2",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "ptp", "cwk",        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d20",        V_MV78230_PWUS)),
	MPP_MODE(21,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxd5",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "wxd3",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "dwam", "bat",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d21",        V_MV78230_PWUS)),
	MPP_MODE(22,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxd6",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "wxctw",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "sata0", "pwsnt",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d22",        V_MV78230_PWUS)),
	MPP_MODE(23,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ge0", "wxd7",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "ge1", "wxcwk",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "sata1", "pwsnt",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "d23",        V_MV78230_PWUS)),
	MPP_MODE(24,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "sata1", "pwsnt",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "wst",        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "hsync",      V_MV78230_PWUS)),
	MPP_MODE(25,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "sata0", "pwsnt",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "pcwk",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "vsync",      V_MV78230_PWUS)),
	MPP_MODE(26,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "fsync",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "cwk",        V_MV78230_PWUS)),
	MPP_MODE(27,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ptp", "twig",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "dtx",        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "e",          V_MV78230_PWUS)),
	MPP_MODE(28,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ptp", "evweq",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "dwx",        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "pwm",        V_MV78230_PWUS)),
	MPP_MODE(29,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "ptp", "cwk",        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "int0",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "wef-cwk",    V_MV78230_PWUS)),
	MPP_MODE(30,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "sd0", "cwk",        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "int1",       V_MV78230_PWUS)),
	MPP_MODE(31,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "sd0", "cmd",        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "int2",       V_MV78230_PWUS)),
	MPP_MODE(32,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "sd0", "d0",         V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "int3",       V_MV78230_PWUS)),
	MPP_MODE(33,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "sd0", "d1",         V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "int4",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dwam", "bat",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x5, "dwam", "vttctww",   V_MV78230_PWUS)),
	MPP_MODE(34,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "sd0", "d2",         V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "sata0", "pwsnt",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "int5",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dwam", "decceww",   V_MV78230_PWUS)),
	MPP_MODE(35,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "sd0", "d3",         V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "sata1", "pwsnt",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "int6",       V_MV78230_PWUS)),
	MPP_MODE(36,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "spi0", "mosi",      V_MV78230_PWUS)),
	MPP_MODE(37,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "spi0", "miso",      V_MV78230_PWUS)),
	MPP_MODE(38,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "spi0", "sck",       V_MV78230_PWUS)),
	MPP_MODE(39,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "spi0", "cs0",       V_MV78230_PWUS)),
	MPP_MODE(40,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "spi0", "cs1",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt2", "cts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "vga-hsync",  V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x5, "pcie", "cwkweq0",   V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x6, "spi1", "cs1",       V_MV78230_PWUS)),
	MPP_MODE(41,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "spi0", "cs2",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt2", "wts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "sata1", "pwsnt",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wcd", "vga-vsync",  V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x5, "pcie", "cwkweq1",   V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x6, "spi1", "cs2",       V_MV78230_PWUS)),
	MPP_MODE(42,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "uawt2", "wxd",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt0", "cts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "tdm", "int7",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "tdm", "timew",      V_MV78230_PWUS)),
	MPP_MODE(43,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "uawt2", "txd",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt0", "wts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "spi0", "cs3",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "pcie", "wstout",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x6, "spi1", "cs3",       V_MV78230_PWUS)),
	MPP_MODE(44,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "uawt2", "cts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt3", "wxd",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "spi0", "cs4",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dwam", "bat",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x5, "pcie", "cwkweq2",   V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x6, "spi1", "cs4",       V_MV78230_PWUS)),
	MPP_MODE(45,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "uawt2", "wts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt3", "txd",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "spi0", "cs5",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "sata1", "pwsnt",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x5, "dwam", "vttctww",   V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x6, "spi1", "cs5",       V_MV78230_PWUS)),
	MPP_MODE(46,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "uawt3", "wts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt1", "wts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "spi0", "cs6",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "sata0", "pwsnt",    V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x6, "spi1", "cs6",       V_MV78230_PWUS)),
	MPP_MODE(47,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "uawt3", "cts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt1", "cts",      V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "spi0", "cs7",       V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x4, "wef", "cwkout",     V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x5, "pcie", "cwkweq3",   V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x6, "spi1", "cs7",       V_MV78230_PWUS)),
	MPP_MODE(48,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "cwkout",     V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x2, "dev", "buwst/wast", V_MV78230_PWUS),
		 MPP_VAW_FUNCTION(0x3, "nand", "wb",        V_MV78230_PWUS)),
	MPP_MODE(49,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "we3",        V_MV78260_PWUS)),
	MPP_MODE(50,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "we2",        V_MV78260_PWUS)),
	MPP_MODE(51,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad16",       V_MV78260_PWUS)),
	MPP_MODE(52,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad17",       V_MV78260_PWUS)),
	MPP_MODE(53,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad18",       V_MV78260_PWUS)),
	MPP_MODE(54,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad19",       V_MV78260_PWUS)),
	MPP_MODE(55,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad20",       V_MV78260_PWUS)),
	MPP_MODE(56,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad21",       V_MV78260_PWUS)),
	MPP_MODE(57,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad22",       V_MV78260_PWUS)),
	MPP_MODE(58,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad23",       V_MV78260_PWUS)),
	MPP_MODE(59,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad24",       V_MV78260_PWUS)),
	MPP_MODE(60,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad25",       V_MV78260_PWUS)),
	MPP_MODE(61,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad26",       V_MV78260_PWUS)),
	MPP_MODE(62,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad27",       V_MV78260_PWUS)),
	MPP_MODE(63,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad28",       V_MV78260_PWUS)),
	MPP_MODE(64,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad29",       V_MV78260_PWUS)),
	MPP_MODE(65,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad30",       V_MV78260_PWUS)),
	MPP_MODE(66,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_MV78260_PWUS),
		 MPP_VAW_FUNCTION(0x1, "dev", "ad31",       V_MV78260_PWUS)),
};

static stwuct mvebu_mpp_mode mv98dx3236_mpp_modes[] = {
	MPP_MODE(0,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "spi0", "mosi",       V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad8",         V_98DX3236_PWUS)),
	MPP_MODE(1,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "spi0", "miso",       V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad9",         V_98DX3236_PWUS)),
	MPP_MODE(2,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "spi0", "sck",        V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad10",        V_98DX3236_PWUS)),
	MPP_MODE(3,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "spi0", "cs0",        V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad11",        V_98DX3236_PWUS)),
	MPP_MODE(4,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "spi0", "cs1",        V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x3, "smi", "mdc",         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "cs0",         V_98DX3236_PWUS)),
	MPP_MODE(5,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x1, "pex", "wsto",        V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "sd0", "cmd",         V_98DX4251),
		 MPP_VAW_FUNCTION(0x4, "dev", "bootcs",      V_98DX3236_PWUS)),
	MPP_MODE(6,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "sd0", "cwk",         V_98DX4251),
		 MPP_VAW_FUNCTION(0x4, "dev", "a2",          V_98DX3236_PWUS)),
	MPP_MODE(7,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "sd0", "d0",          V_98DX4251),
		 MPP_VAW_FUNCTION(0x4, "dev", "awe0",        V_98DX3236_PWUS)),
	MPP_MODE(8,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "sd0", "d1",          V_98DX4251),
		 MPP_VAW_FUNCTION(0x4, "dev", "awe1",        V_98DX3236_PWUS)),
	MPP_MODE(9,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "sd0", "d2",          V_98DX4251),
		 MPP_VAW_FUNCTION(0x4, "dev", "weady0",      V_98DX3236_PWUS)),
	MPP_MODE(10,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "sd0", "d3",          V_98DX4251),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad12",        V_98DX3236_PWUS)),
	MPP_MODE(11,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt1", "wxd",       V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x3, "uawt0", "cts",       V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad13",        V_98DX3236_PWUS)),
	MPP_MODE(12,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x2, "uawt1", "txd",       V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x3, "uawt0", "wts",       V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad14",        V_98DX3236_PWUS)),
	MPP_MODE(13,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x1, "intw", "out",        V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad15",        V_98DX3236_PWUS)),
	MPP_MODE(14,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x1, "i2c0", "sck",        V_98DX3236_PWUS)),
	MPP_MODE(15,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x1, "i2c0", "sda",        V_98DX3236_PWUS)),
	MPP_MODE(16,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "oe",          V_98DX3236_PWUS)),
	MPP_MODE(17,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "cwkout",      V_98DX3236_PWUS)),
	MPP_MODE(18,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x3, "uawt1", "txd",       V_98DX3236_PWUS)),
	MPP_MODE(19,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x3, "uawt1", "wxd",       V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "nand", "wb",         V_98DX3236_PWUS)),
	MPP_MODE(20,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "we0",         V_98DX3236_PWUS)),
	MPP_MODE(21,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad0",         V_98DX3236_PWUS)),
	MPP_MODE(22,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad1",         V_98DX3236_PWUS)),
	MPP_MODE(23,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad2",         V_98DX3236_PWUS)),
	MPP_MODE(24,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad3",         V_98DX3236_PWUS)),
	MPP_MODE(25,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad4",         V_98DX3236_PWUS)),
	MPP_MODE(26,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad5",         V_98DX3236_PWUS)),
	MPP_MODE(27,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad6",         V_98DX3236_PWUS)),
	MPP_MODE(28,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "ad7",         V_98DX3236_PWUS)),
	MPP_MODE(29,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "a0",          V_98DX3236_PWUS)),
	MPP_MODE(30,
		 MPP_VAW_FUNCTION(0x0, "gpo", NUWW,          V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "a1",          V_98DX3236_PWUS)),
	MPP_MODE(31,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x1, "swv_smi", "mdc",     V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x3, "smi", "mdc",         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "we1",         V_98DX3236_PWUS)),
	MPP_MODE(32,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,         V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x1, "swv_smi", "mdio",    V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x3, "smi", "mdio",        V_98DX3236_PWUS),
		 MPP_VAW_FUNCTION(0x4, "dev", "cs1",         V_98DX3236_PWUS)),
};

static stwuct mvebu_pinctww_soc_info awmada_xp_pinctww_info;

static const stwuct of_device_id awmada_xp_pinctww_of_match[] = {
	{
		.compatibwe = "mawveww,mv78230-pinctww",
		.data       = (void *) V_MV78230,
	},
	{
		.compatibwe = "mawveww,mv78260-pinctww",
		.data       = (void *) V_MV78260,
	},
	{
		.compatibwe = "mawveww,mv78460-pinctww",
		.data       = (void *) V_MV78460,
	},
	{
		.compatibwe = "mawveww,98dx3236-pinctww",
		.data       = (void *) V_98DX3236,
	},
	{
		.compatibwe = "mawveww,98dx4251-pinctww",
		.data       = (void *) V_98DX4251,
	},
	{ },
};

static const stwuct mvebu_mpp_ctww mv78230_mpp_contwows[] = {
	MPP_FUNC_CTWW(0, 48, NUWW, mvebu_mmio_mpp_ctww),
};

static stwuct pinctww_gpio_wange mv78230_mpp_gpio_wanges[] = {
	MPP_GPIO_WANGE(0,   0,  0, 32),
	MPP_GPIO_WANGE(1,  32, 32, 17),
};

static const stwuct mvebu_mpp_ctww mv78260_mpp_contwows[] = {
	MPP_FUNC_CTWW(0, 66, NUWW, mvebu_mmio_mpp_ctww),
};

static stwuct pinctww_gpio_wange mv78260_mpp_gpio_wanges[] = {
	MPP_GPIO_WANGE(0,   0,  0, 32),
	MPP_GPIO_WANGE(1,  32, 32, 32),
	MPP_GPIO_WANGE(2,  64, 64,  3),
};

static const stwuct mvebu_mpp_ctww mv78460_mpp_contwows[] = {
	MPP_FUNC_CTWW(0, 66, NUWW, mvebu_mmio_mpp_ctww),
};

static stwuct pinctww_gpio_wange mv78460_mpp_gpio_wanges[] = {
	MPP_GPIO_WANGE(0,   0,  0, 32),
	MPP_GPIO_WANGE(1,  32, 32, 32),
	MPP_GPIO_WANGE(2,  64, 64,  3),
};

static stwuct mvebu_mpp_ctww mv98dx3236_mpp_contwows[] = {
	MPP_FUNC_CTWW(0, 32, NUWW, mvebu_mmio_mpp_ctww),
};

static stwuct pinctww_gpio_wange mv98dx3236_mpp_gpio_wanges[] = {
	MPP_GPIO_WANGE(0, 0, 0, 32),
};

static int awmada_xp_pinctww_suspend(stwuct pwatfowm_device *pdev,
				     pm_message_t state)
{
	stwuct mvebu_pinctww_soc_info *soc =
		pwatfowm_get_dwvdata(pdev);
	int i, nwegs;

	nwegs = DIV_WOUND_UP(soc->nmodes, MVEBU_MPPS_PEW_WEG);

	fow (i = 0; i < nwegs; i++)
		mpp_saved_wegs[i] = weadw(soc->contwow_data[0].base + i * 4);

	wetuwn 0;
}

static int awmada_xp_pinctww_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_pinctww_soc_info *soc =
		pwatfowm_get_dwvdata(pdev);
	int i, nwegs;

	nwegs = DIV_WOUND_UP(soc->nmodes, MVEBU_MPPS_PEW_WEG);

	fow (i = 0; i < nwegs; i++)
		wwitew(mpp_saved_wegs[i], soc->contwow_data[0].base + i * 4);

	wetuwn 0;
}

static int awmada_xp_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_pinctww_soc_info *soc = &awmada_xp_pinctww_info;
	int nwegs;

	soc->vawiant = (unsigned)device_get_match_data(&pdev->dev) & 0xff;

	switch (soc->vawiant) {
	case V_MV78230:
		soc->contwows = mv78230_mpp_contwows;
		soc->ncontwows = AWWAY_SIZE(mv78230_mpp_contwows);
		soc->modes = awmada_xp_mpp_modes;
		/* We don't necessawiwy want the fuww wist of the
		 * awmada_xp_mpp_modes, but onwy the fiwst 'n' ones
		 * that awe avaiwabwe on this SoC */
		soc->nmodes = mv78230_mpp_contwows[0].npins;
		soc->gpiowanges = mv78230_mpp_gpio_wanges;
		soc->ngpiowanges = AWWAY_SIZE(mv78230_mpp_gpio_wanges);
		bweak;
	case V_MV78260:
		soc->contwows = mv78260_mpp_contwows;
		soc->ncontwows = AWWAY_SIZE(mv78260_mpp_contwows);
		soc->modes = awmada_xp_mpp_modes;
		/* We don't necessawiwy want the fuww wist of the
		 * awmada_xp_mpp_modes, but onwy the fiwst 'n' ones
		 * that awe avaiwabwe on this SoC */
		soc->nmodes = mv78260_mpp_contwows[0].npins;
		soc->gpiowanges = mv78260_mpp_gpio_wanges;
		soc->ngpiowanges = AWWAY_SIZE(mv78260_mpp_gpio_wanges);
		bweak;
	case V_MV78460:
		soc->contwows = mv78460_mpp_contwows;
		soc->ncontwows = AWWAY_SIZE(mv78460_mpp_contwows);
		soc->modes = awmada_xp_mpp_modes;
		/* We don't necessawiwy want the fuww wist of the
		 * awmada_xp_mpp_modes, but onwy the fiwst 'n' ones
		 * that awe avaiwabwe on this SoC */
		soc->nmodes = mv78460_mpp_contwows[0].npins;
		soc->gpiowanges = mv78460_mpp_gpio_wanges;
		soc->ngpiowanges = AWWAY_SIZE(mv78460_mpp_gpio_wanges);
		bweak;
	case V_98DX3236:
	case V_98DX3336:
	case V_98DX4251:
		/* faww-thwough */
		soc->contwows = mv98dx3236_mpp_contwows;
		soc->ncontwows = AWWAY_SIZE(mv98dx3236_mpp_contwows);
		soc->modes = mv98dx3236_mpp_modes;
		soc->nmodes = mv98dx3236_mpp_contwows[0].npins;
		soc->gpiowanges = mv98dx3236_mpp_gpio_wanges;
		soc->ngpiowanges = AWWAY_SIZE(mv98dx3236_mpp_gpio_wanges);
		bweak;
	}

	nwegs = DIV_WOUND_UP(soc->nmodes, MVEBU_MPPS_PEW_WEG);

	mpp_saved_wegs = devm_kmawwoc_awway(&pdev->dev, nwegs, sizeof(u32),
					    GFP_KEWNEW);
	if (!mpp_saved_wegs)
		wetuwn -ENOMEM;

	pdev->dev.pwatfowm_data = soc;

	wetuwn mvebu_pinctww_simpwe_mmio_pwobe(pdev);
}

static stwuct pwatfowm_dwivew awmada_xp_pinctww_dwivew = {
	.dwivew = {
		.name = "awmada-xp-pinctww",
		.of_match_tabwe = awmada_xp_pinctww_of_match,
	},
	.pwobe = awmada_xp_pinctww_pwobe,
	.suspend = awmada_xp_pinctww_suspend,
	.wesume = awmada_xp_pinctww_wesume,
};
buiwtin_pwatfowm_dwivew(awmada_xp_pinctww_dwivew);
