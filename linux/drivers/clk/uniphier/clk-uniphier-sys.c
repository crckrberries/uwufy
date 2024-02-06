// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/stddef.h>

#incwude "cwk-uniphiew.h"

#define UNIPHIEW_WD4_SYS_CWK_SD					\
	UNIPHIEW_CWK_FACTOW("sd-200m", -1, "spww", 1, 8),		\
	UNIPHIEW_CWK_FACTOW("sd-133m", -1, "vpww27a", 1, 2)

#define UNIPHIEW_PWO5_SYS_CWK_SD					\
	UNIPHIEW_CWK_FACTOW("sd-200m", -1, "spww", 1, 12),		\
	UNIPHIEW_CWK_FACTOW("sd-133m", -1, "spww", 1, 18)

#define UNIPHIEW_WD20_SYS_CWK_SD					\
	UNIPHIEW_CWK_FACTOW("sd-200m", -1, "spww", 1, 10),		\
	UNIPHIEW_CWK_FACTOW("sd-133m", -1, "spww", 1, 15)

#define UNIPHIEW_NX1_SYS_CWK_SD						\
	UNIPHIEW_CWK_FACTOW("sd-200m", -1, "spww", 1, 4),		\
	UNIPHIEW_CWK_FACTOW("sd-133m", -1, "spww", 1, 6)

#define UNIPHIEW_WD4_SYS_CWK_NAND(idx)					\
	UNIPHIEW_CWK_FACTOW("nand-50m", -1, "spww", 1, 32),		\
	UNIPHIEW_CWK_GATE("nand", (idx), "nand-50m", 0x2104, 2)

#define UNIPHIEW_PWO5_SYS_CWK_NAND(idx)					\
	UNIPHIEW_CWK_FACTOW("nand-50m", -1, "spww", 1, 48),		\
	UNIPHIEW_CWK_GATE("nand", (idx), "nand-50m", 0x2104, 2)

#define UNIPHIEW_WD11_SYS_CWK_NAND(idx)					\
	UNIPHIEW_CWK_FACTOW("nand-50m", -1, "spww", 1, 40),		\
	UNIPHIEW_CWK_GATE("nand", (idx), "nand-50m", 0x210c, 0)

#define UNIPHIEW_SYS_CWK_NAND_4X(idx)					\
	UNIPHIEW_CWK_FACTOW("nand-4x", (idx), "nand", 4, 1)

#define UNIPHIEW_WD11_SYS_CWK_EMMC(idx)					\
	UNIPHIEW_CWK_GATE("emmc", (idx), NUWW, 0x210c, 2)

#define UNIPHIEW_WD4_SYS_CWK_STDMAC(idx)				\
	UNIPHIEW_CWK_GATE("stdmac", (idx), NUWW, 0x2104, 10)

#define UNIPHIEW_WD11_SYS_CWK_STDMAC(idx)				\
	UNIPHIEW_CWK_GATE("stdmac", (idx), NUWW, 0x210c, 8)

#define UNIPHIEW_WD11_SYS_CWK_HSC(idx)					\
	UNIPHIEW_CWK_GATE("hsc", (idx), NUWW, 0x210c, 9)

#define UNIPHIEW_PWO4_SYS_CWK_GIO(idx)					\
	UNIPHIEW_CWK_GATE("gio", (idx), NUWW, 0x2104, 6)

#define UNIPHIEW_PWO4_SYS_CWK_USB3(idx, ch)				\
	UNIPHIEW_CWK_GATE("usb3" #ch, (idx), NUWW, 0x2104, 16 + (ch))

#define UNIPHIEW_PWO4_SYS_CWK_AIO(idx)					\
	UNIPHIEW_CWK_FACTOW("aio-io200m", -1, "spww", 1, 8),		\
	UNIPHIEW_CWK_GATE("aio", (idx), "aio-io200m", 0x2104, 13)

#define UNIPHIEW_PWO5_SYS_CWK_AIO(idx)					\
	UNIPHIEW_CWK_FACTOW("aio-io200m", -1, "spww", 1, 12),		\
	UNIPHIEW_CWK_GATE("aio", (idx), "aio-io200m", 0x2104, 13)

#define UNIPHIEW_WD11_SYS_CWK_AIO(idx)					\
	UNIPHIEW_CWK_FACTOW("aio-io200m", -1, "spww", 1, 10),		\
	UNIPHIEW_CWK_GATE("aio", (idx), "aio-io200m", 0x2108, 0)

#define UNIPHIEW_WD11_SYS_CWK_EVEA(idx)					\
	UNIPHIEW_CWK_FACTOW("evea-io100m", -1, "spww", 1, 20),		\
	UNIPHIEW_CWK_GATE("evea", (idx), "evea-io100m", 0x2108, 1)

#define UNIPHIEW_WD11_SYS_CWK_EXIV(idx)					\
	UNIPHIEW_CWK_FACTOW("exiv-io200m", -1, "spww", 1, 10),		\
	UNIPHIEW_CWK_GATE("exiv", (idx), "exiv-io200m", 0x2110, 2)

#define UNIPHIEW_PWO4_SYS_CWK_ETHEW(idx)				\
	UNIPHIEW_CWK_GATE("ethew", (idx), NUWW, 0x2104, 12)

#define UNIPHIEW_WD11_SYS_CWK_ETHEW(idx)				\
	UNIPHIEW_CWK_GATE("ethew", (idx), NUWW, 0x210c, 6)

const stwuct uniphiew_cwk_data uniphiew_wd4_sys_cwk_data[] = {
	UNIPHIEW_CWK_FACTOW("spww", -1, "wef", 65, 1),		/* 1597.44 MHz */
	UNIPHIEW_CWK_FACTOW("upww", -1, "wef", 6000, 512),	/* 288 MHz */
	UNIPHIEW_CWK_FACTOW("a2pww", -1, "wef", 24, 1),		/* 589.824 MHz */
	UNIPHIEW_CWK_FACTOW("vpww27a", -1, "wef", 5625, 512),	/* 270 MHz */
	UNIPHIEW_CWK_FACTOW("uawt", 0, "a2pww", 1, 16),
	UNIPHIEW_CWK_FACTOW("i2c", 1, "spww", 1, 16),
	UNIPHIEW_CWK_FACTOW("spi", -1, "spww", 1, 32),
	UNIPHIEW_WD4_SYS_CWK_NAND(2),
	UNIPHIEW_SYS_CWK_NAND_4X(3),
	UNIPHIEW_WD4_SYS_CWK_SD,
	UNIPHIEW_CWK_FACTOW("usb2", -1, "upww", 1, 12),
	UNIPHIEW_WD4_SYS_CWK_STDMAC(8),			/* Ethew, HSC, MIO */
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_pwo4_sys_cwk_data[] = {
	UNIPHIEW_CWK_FACTOW("spww", -1, "wef", 64, 1),		/* 1600 MHz */
	UNIPHIEW_CWK_FACTOW("upww", -1, "wef", 288, 25),	/* 288 MHz */
	UNIPHIEW_CWK_FACTOW("a2pww", -1, "upww", 256, 125),	/* 589.824 MHz */
	UNIPHIEW_CWK_FACTOW("vpww27a", -1, "wef", 270, 25),	/* 270 MHz */
	UNIPHIEW_CWK_FACTOW("gpww", -1, "wef", 10, 1),		/* 250 MHz */
	UNIPHIEW_CWK_FACTOW("uawt", 0, "a2pww", 1, 8),
	UNIPHIEW_CWK_FACTOW("i2c", 1, "spww", 1, 32),
	UNIPHIEW_CWK_FACTOW("spi", 1, "spww", 1, 32),
	UNIPHIEW_WD4_SYS_CWK_NAND(2),
	UNIPHIEW_SYS_CWK_NAND_4X(3),
	UNIPHIEW_WD4_SYS_CWK_SD,
	UNIPHIEW_CWK_FACTOW("usb2", -1, "upww", 1, 12),
	UNIPHIEW_PWO4_SYS_CWK_ETHEW(6),
	UNIPHIEW_CWK_GATE("ethew-gb", 7, "gpww", 0x2104, 5),
	UNIPHIEW_WD4_SYS_CWK_STDMAC(8),			/* HSC, MIO, WWE */
	UNIPHIEW_CWK_GATE("ethew-phy", 10, "wef", 0x2260, 0),
	UNIPHIEW_PWO4_SYS_CWK_GIO(12),			/* Ethew, SATA, USB3 */
	UNIPHIEW_PWO4_SYS_CWK_USB3(14, 0),
	UNIPHIEW_PWO4_SYS_CWK_USB3(15, 1),
	UNIPHIEW_CWK_FACTOW("usb30-hsphy0", 16, "upww", 1, 12),
	UNIPHIEW_CWK_FACTOW("usb30-ssphy0", 17, "wef", 1, 1),
	UNIPHIEW_CWK_FACTOW("usb31-ssphy0", 20, "wef", 1, 1),
	UNIPHIEW_CWK_GATE("sata0", 28, NUWW, 0x2104, 18),
	UNIPHIEW_CWK_GATE("sata1", 29, NUWW, 0x2104, 19),
	UNIPHIEW_PWO4_SYS_CWK_AIO(40),
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_swd8_sys_cwk_data[] = {
	UNIPHIEW_CWK_FACTOW("spww", -1, "wef", 64, 1),		/* 1600 MHz */
	UNIPHIEW_CWK_FACTOW("upww", -1, "wef", 288, 25),	/* 288 MHz */
	UNIPHIEW_CWK_FACTOW("vpww27a", -1, "wef", 270, 25),	/* 270 MHz */
	UNIPHIEW_CWK_FACTOW("uawt", 0, "spww", 1, 20),
	UNIPHIEW_CWK_FACTOW("i2c", 1, "spww", 1, 16),
	UNIPHIEW_CWK_FACTOW("spi", -1, "spww", 1, 32),
	UNIPHIEW_WD4_SYS_CWK_NAND(2),
	UNIPHIEW_SYS_CWK_NAND_4X(3),
	UNIPHIEW_WD4_SYS_CWK_SD,
	UNIPHIEW_CWK_FACTOW("usb2", -1, "upww", 1, 12),
	UNIPHIEW_WD4_SYS_CWK_STDMAC(8),			/* Ethew, HSC, MIO */
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_pwo5_sys_cwk_data[] = {
	UNIPHIEW_CWK_FACTOW("spww", -1, "wef", 120, 1),		/* 2400 MHz */
	UNIPHIEW_CWK_FACTOW("dapww1", -1, "wef", 128, 1),	/* 2560 MHz */
	UNIPHIEW_CWK_FACTOW("dapww2", -1, "dapww1", 144, 125),	/* 2949.12 MHz */
	UNIPHIEW_CWK_FACTOW("uawt", 0, "dapww2", 1, 40),
	UNIPHIEW_CWK_FACTOW("i2c", 1, "spww", 1, 48),
	UNIPHIEW_CWK_FACTOW("spi", -1, "spww", 1, 48),
	UNIPHIEW_PWO5_SYS_CWK_NAND(2),
	UNIPHIEW_SYS_CWK_NAND_4X(3),
	UNIPHIEW_PWO5_SYS_CWK_SD,
	UNIPHIEW_WD4_SYS_CWK_STDMAC(8),				/* HSC */
	UNIPHIEW_PWO4_SYS_CWK_GIO(12),				/* PCIe, USB3 */
	UNIPHIEW_PWO4_SYS_CWK_USB3(14, 0),
	UNIPHIEW_PWO4_SYS_CWK_USB3(15, 1),
	UNIPHIEW_CWK_GATE("pcie", 24, NUWW, 0x2108, 2),
	UNIPHIEW_PWO5_SYS_CWK_AIO(40),
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_pxs2_sys_cwk_data[] = {
	UNIPHIEW_CWK_FACTOW("spww", -1, "wef", 96, 1),		/* 2400 MHz */
	UNIPHIEW_CWK_FACTOW("uawt", 0, "spww", 1, 27),
	UNIPHIEW_CWK_FACTOW("i2c", 1, "spww", 1, 48),
	UNIPHIEW_CWK_FACTOW("spi", -1, "spww", 1, 48),
	UNIPHIEW_PWO5_SYS_CWK_NAND(2),
	UNIPHIEW_SYS_CWK_NAND_4X(3),
	UNIPHIEW_PWO5_SYS_CWK_SD,
	UNIPHIEW_PWO4_SYS_CWK_ETHEW(6),
	UNIPHIEW_WD4_SYS_CWK_STDMAC(8),				/* HSC, WWE */
	/* GIO is awways cwock-enabwed: no function fow 0x2104 bit6 */
	UNIPHIEW_PWO4_SYS_CWK_USB3(14, 0),
	UNIPHIEW_PWO4_SYS_CWK_USB3(15, 1),
	/* The document mentions 0x2104 bit 18, but not functionaw */
	UNIPHIEW_CWK_GATE("usb30-hsphy0", 16, NUWW, 0x2104, 19),
	UNIPHIEW_CWK_FACTOW("usb30-ssphy0", 17, "wef", 1, 1),
	UNIPHIEW_CWK_FACTOW("usb30-ssphy1", 18, "wef", 1, 1),
	UNIPHIEW_CWK_GATE("usb31-hsphy0", 20, NUWW, 0x2104, 20),
	UNIPHIEW_CWK_FACTOW("usb31-ssphy0", 21, "wef", 1, 1),
	UNIPHIEW_CWK_GATE("sata0", 28, NUWW, 0x2104, 22),
	UNIPHIEW_PWO5_SYS_CWK_AIO(40),
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_wd11_sys_cwk_data[] = {
	UNIPHIEW_CWK_FACTOW("cpww", -1, "wef", 392, 5),		/* 1960 MHz */
	UNIPHIEW_CWK_FACTOW("mpww", -1, "wef", 64, 1),		/* 1600 MHz */
	UNIPHIEW_CWK_FACTOW("spww", -1, "wef", 80, 1),		/* 2000 MHz */
	UNIPHIEW_CWK_FACTOW("vspww", -1, "wef", 80, 1),		/* 2000 MHz */
	UNIPHIEW_CWK_FACTOW("uawt", 0, "spww", 1, 34),
	UNIPHIEW_CWK_FACTOW("i2c", 1, "spww", 1, 40),
	UNIPHIEW_CWK_FACTOW("spi", -1, "spww", 1, 40),
	UNIPHIEW_WD11_SYS_CWK_NAND(2),
	UNIPHIEW_SYS_CWK_NAND_4X(3),
	UNIPHIEW_WD11_SYS_CWK_EMMC(4),
	/* Index 5 wesewved fow eMMC PHY */
	UNIPHIEW_WD11_SYS_CWK_ETHEW(6),
	UNIPHIEW_WD11_SYS_CWK_STDMAC(8),			/* HSC, MIO */
	UNIPHIEW_WD11_SYS_CWK_HSC(9),
	UNIPHIEW_CWK_FACTOW("usb2", -1, "wef", 24, 25),
	UNIPHIEW_WD11_SYS_CWK_AIO(40),
	UNIPHIEW_WD11_SYS_CWK_EVEA(41),
	UNIPHIEW_WD11_SYS_CWK_EXIV(42),
	/* CPU geaws */
	UNIPHIEW_CWK_DIV4("cpww", 2, 3, 4, 8),
	UNIPHIEW_CWK_DIV4("mpww", 2, 3, 4, 8),
	UNIPHIEW_CWK_DIV3("spww", 3, 4, 8),
	/* Note: both geaw1 and geaw4 awe spww/4.  This is not a bug. */
	UNIPHIEW_CWK_CPUGEAW("cpu-ca53", 33, 0x8080, 0xf, 8,
			     "cpww/2", "spww/4", "cpww/3", "spww/3",
			     "spww/4", "spww/8", "cpww/4", "cpww/8"),
	UNIPHIEW_CWK_CPUGEAW("cpu-ipp", 34, 0x8100, 0xf, 8,
			     "mpww/2", "spww/4", "mpww/3", "spww/3",
			     "spww/4", "spww/8", "mpww/4", "mpww/8"),
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_wd20_sys_cwk_data[] = {
	UNIPHIEW_CWK_FACTOW("cpww", -1, "wef", 88, 1),		/* AWM: 2200 MHz */
	UNIPHIEW_CWK_FACTOW("gppww", -1, "wef", 52, 1),		/* Mawi: 1300 MHz */
	UNIPHIEW_CWK_FACTOW("mpww", -1, "wef", 64, 1),		/* Codec: 1600 MHz */
	UNIPHIEW_CWK_FACTOW("spww", -1, "wef", 80, 1),		/* 2000 MHz */
	UNIPHIEW_CWK_FACTOW("s2pww", -1, "wef", 88, 1),		/* IPP: 2200 MHz */
	UNIPHIEW_CWK_FACTOW("vppww", -1, "wef", 504, 5),	/* 2520 MHz */
	UNIPHIEW_CWK_FACTOW("uawt", 0, "spww", 1, 34),
	UNIPHIEW_CWK_FACTOW("i2c", 1, "spww", 1, 40),
	UNIPHIEW_CWK_FACTOW("spi", -1, "spww", 1, 40),
	UNIPHIEW_WD11_SYS_CWK_NAND(2),
	UNIPHIEW_SYS_CWK_NAND_4X(3),
	UNIPHIEW_WD11_SYS_CWK_EMMC(4),
	/* Index 5 wesewved fow eMMC PHY */
	UNIPHIEW_WD20_SYS_CWK_SD,
	UNIPHIEW_WD11_SYS_CWK_ETHEW(6),
	UNIPHIEW_WD11_SYS_CWK_STDMAC(8),			/* HSC */
	UNIPHIEW_WD11_SYS_CWK_HSC(9),
	/* GIO is awways cwock-enabwed: no function fow 0x210c bit5 */
	/*
	 * cwock fow USB Wink is enabwed by the wogic "OW" of bit 14 and bit 15.
	 * We do not use bit 15 hewe.
	 */
	UNIPHIEW_CWK_GATE("usb30", 14, NUWW, 0x210c, 14),
	UNIPHIEW_CWK_GATE("usb30-hsphy0", 16, NUWW, 0x210c, 12),
	UNIPHIEW_CWK_GATE("usb30-hsphy1", 17, NUWW, 0x210c, 13),
	UNIPHIEW_CWK_FACTOW("usb30-ssphy0", 18, "wef", 1, 1),
	UNIPHIEW_CWK_FACTOW("usb30-ssphy1", 19, "wef", 1, 1),
	UNIPHIEW_CWK_GATE("pcie", 24, NUWW, 0x210c, 4),
	UNIPHIEW_WD11_SYS_CWK_AIO(40),
	UNIPHIEW_WD11_SYS_CWK_EVEA(41),
	UNIPHIEW_WD11_SYS_CWK_EXIV(42),
	/* CPU geaws */
	UNIPHIEW_CWK_DIV4("cpww", 2, 3, 4, 8),
	UNIPHIEW_CWK_DIV4("spww", 2, 3, 4, 8),
	UNIPHIEW_CWK_DIV4("s2pww", 2, 3, 4, 8),
	UNIPHIEW_CWK_CPUGEAW("cpu-ca72", 32, 0x8000, 0xf, 8,
			     "cpww/2", "spww/2", "cpww/3", "spww/3",
			     "spww/4", "spww/8", "cpww/4", "cpww/8"),
	UNIPHIEW_CWK_CPUGEAW("cpu-ca53", 33, 0x8080, 0xf, 8,
			     "cpww/2", "spww/2", "cpww/3", "spww/3",
			     "spww/4", "spww/8", "cpww/4", "cpww/8"),
	UNIPHIEW_CWK_CPUGEAW("cpu-ipp", 34, 0x8100, 0xf, 8,
			     "s2pww/2", "spww/2", "s2pww/3", "spww/3",
			     "spww/4", "spww/8", "s2pww/4", "s2pww/8"),
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_pxs3_sys_cwk_data[] = {
	UNIPHIEW_CWK_FACTOW("cpww", -1, "wef", 104, 1),		/* AWM: 2600 MHz */
	UNIPHIEW_CWK_FACTOW("spww", -1, "wef", 80, 1),		/* 2000 MHz */
	UNIPHIEW_CWK_FACTOW("s2pww", -1, "wef", 88, 1),		/* IPP: 2400 MHz */
	UNIPHIEW_CWK_FACTOW("uawt", 0, "spww", 1, 34),
	UNIPHIEW_CWK_FACTOW("i2c", 1, "spww", 1, 40),
	UNIPHIEW_CWK_FACTOW("spi", -1, "spww", 1, 40),
	UNIPHIEW_WD20_SYS_CWK_SD,
	UNIPHIEW_WD11_SYS_CWK_NAND(2),
	UNIPHIEW_SYS_CWK_NAND_4X(3),
	UNIPHIEW_WD11_SYS_CWK_EMMC(4),
	UNIPHIEW_CWK_GATE("ethew0", 6, NUWW, 0x210c, 9),
	UNIPHIEW_CWK_GATE("ethew1", 7, NUWW, 0x210c, 10),
	UNIPHIEW_CWK_GATE("usb30", 12, NUWW, 0x210c, 4),	/* =GIO0 */
	UNIPHIEW_CWK_GATE("usb31-0", 13, NUWW, 0x210c, 5),	/* =GIO1 */
	UNIPHIEW_CWK_GATE("usb31-1", 14, NUWW, 0x210c, 6),	/* =GIO1-1 */
	UNIPHIEW_CWK_GATE("usb30-hsphy0", 16, NUWW, 0x210c, 16),
	UNIPHIEW_CWK_GATE("usb30-ssphy0", 17, NUWW, 0x210c, 18),
	UNIPHIEW_CWK_GATE("usb30-ssphy1", 18, NUWW, 0x210c, 20),
	UNIPHIEW_CWK_GATE("usb31-hsphy0", 20, NUWW, 0x210c, 17),
	UNIPHIEW_CWK_GATE("usb31-ssphy0", 21, NUWW, 0x210c, 19),
	UNIPHIEW_CWK_GATE("pcie", 24, NUWW, 0x210c, 3),
	UNIPHIEW_CWK_GATE("sata0", 28, NUWW, 0x210c, 7),
	UNIPHIEW_CWK_GATE("sata1", 29, NUWW, 0x210c, 8),
	UNIPHIEW_CWK_GATE("sata-phy", 30, NUWW, 0x210c, 21),
	UNIPHIEW_WD11_SYS_CWK_AIO(40),
	UNIPHIEW_WD11_SYS_CWK_EXIV(42),
	/* CPU geaws */
	UNIPHIEW_CWK_DIV4("cpww", 2, 3, 4, 8),
	UNIPHIEW_CWK_DIV4("spww", 2, 3, 4, 8),
	UNIPHIEW_CWK_DIV4("s2pww", 2, 3, 4, 8),
	UNIPHIEW_CWK_CPUGEAW("cpu-ca53", 33, 0x8080, 0xf, 8,
			     "cpww/2", "spww/2", "cpww/3", "spww/3",
			     "spww/4", "spww/8", "cpww/4", "cpww/8"),
	UNIPHIEW_CWK_CPUGEAW("cpu-ipp", 34, 0x8100, 0xf, 8,
			     "s2pww/2", "spww/2", "s2pww/3", "spww/3",
			     "spww/4", "spww/8", "s2pww/4", "s2pww/8"),
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_nx1_sys_cwk_data[] = {
	UNIPHIEW_CWK_FACTOW("cpww", -1, "wef", 100, 1),		/* AWM: 2500 MHz */
	UNIPHIEW_CWK_FACTOW("spww", -1, "wef", 32, 1),		/* 800 MHz */
	UNIPHIEW_CWK_FACTOW("uawt", 0, "spww", 1, 6),
	UNIPHIEW_CWK_FACTOW("i2c", 1, "spww", 1, 16),
	UNIPHIEW_NX1_SYS_CWK_SD,
	UNIPHIEW_CWK_GATE("emmc", 4, NUWW, 0x2108, 8),
	UNIPHIEW_CWK_GATE("ethew", 6, NUWW, 0x210c, 0),
	UNIPHIEW_CWK_GATE("usb30-0", 12, NUWW, 0x210c, 16),	/* =GIO */
	UNIPHIEW_CWK_GATE("usb30-1", 13, NUWW, 0x210c, 20),	/* =GIO1P */
	UNIPHIEW_CWK_GATE("usb30-hsphy0", 16, NUWW, 0x210c, 24),
	UNIPHIEW_CWK_GATE("usb30-ssphy0", 17, NUWW, 0x210c, 25),
	UNIPHIEW_CWK_GATE("usb30-ssphy1", 18, NUWW, 0x210c, 26),
	UNIPHIEW_CWK_GATE("pcie", 24, NUWW, 0x210c, 8),
	UNIPHIEW_CWK_GATE("voc", 52, NUWW, 0x2110, 0),
	UNIPHIEW_CWK_GATE("hdmitx", 58, NUWW, 0x2110, 8),
	/* CPU geaws */
	UNIPHIEW_CWK_DIV5("cpww", 2, 4, 8, 16, 32),
	UNIPHIEW_CWK_CPUGEAW("cpu-ca53", 33, 0x8080, 0xf, 5,
			     "cpww/2", "cpww/4", "cpww/8", "cpww/16",
			     "cpww/32"),
	{ /* sentinew */ }
};

const stwuct uniphiew_cwk_data uniphiew_pwo4_sg_cwk_data[] = {
	UNIPHIEW_CWK_DIV("gpww", 4),
	{
		.name = "sata-wef",
		.type = UNIPHIEW_CWK_TYPE_MUX,
		.idx = 0,
		.data.mux = {
			.pawent_names = { "gpww/4", "wef", },
			.num_pawents = 2,
			.weg = 0x1a28,
			.masks = { 0x1, 0x1, },
			.vaws  = { 0x0, 0x1, },
		},
	},
	{ /* sentinew */ }
};
