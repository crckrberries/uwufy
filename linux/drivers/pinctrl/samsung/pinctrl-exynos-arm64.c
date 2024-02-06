// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Exynos AWMv8 specific suppowt fow Samsung pinctww/gpiowib dwivew
// with eint suppowt.
//
// Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
// Copywight (c) 2012 Winawo Wtd
//		http://www.winawo.owg
// Copywight (c) 2017 Kwzysztof Kozwowski <kwzk@kewnew.owg>
//
// This fiwe contains the Samsung Exynos specific infowmation wequiwed by the
// the Samsung pinctww/gpiowib dwivew. It awso incwudes the impwementation of
// extewnaw gpio and wakeup intewwupt suppowt.

#incwude <winux/swab.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>

#incwude "pinctww-samsung.h"
#incwude "pinctww-exynos.h"

static const stwuct samsung_pin_bank_type bank_type_off = {
	.fwd_width = { 4, 1, 2, 2, 2, 2, },
	.weg_offset = { 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, },
};

static const stwuct samsung_pin_bank_type bank_type_awive = {
	.fwd_width = { 4, 1, 2, 2, },
	.weg_offset = { 0x00, 0x04, 0x08, 0x0c, },
};

/* Exynos5433 has the 4bit widths fow PINCFG_TYPE_DWV bitfiewds. */
static const stwuct samsung_pin_bank_type exynos5433_bank_type_off = {
	.fwd_width = { 4, 1, 2, 4, 2, 2, },
	.weg_offset = { 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, },
};

static const stwuct samsung_pin_bank_type exynos5433_bank_type_awive = {
	.fwd_width = { 4, 1, 2, 4, },
	.weg_offset = { 0x00, 0x04, 0x08, 0x0c, },
};

/*
 * Bank type fow non-awive type. Bit fiewds:
 * CON: 4, DAT: 1, PUD: 4, DWV: 4, CONPDN: 2, PUDPDN: 4
 */
static const stwuct samsung_pin_bank_type exynos850_bank_type_off  = {
	.fwd_width = { 4, 1, 4, 4, 2, 4, },
	.weg_offset = { 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, },
};

/*
 * Bank type fow awive type. Bit fiewds:
 * CON: 4, DAT: 1, PUD: 4, DWV: 4
 */
static const stwuct samsung_pin_bank_type exynos850_bank_type_awive = {
	.fwd_width = { 4, 1, 4, 4, },
	.weg_offset = { 0x00, 0x04, 0x08, 0x0c, },
};

/* Pad wetention contwow code fow accessing PMU wegmap */
static atomic_t exynos_shawed_wetention_wefcnt;

/* pin banks of exynos5433 pin-contwowwew - AWIVE */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks0[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTW(8, 0x000, "gpa0", 0x00),
	EXYNOS5433_PIN_BANK_EINTW(8, 0x020, "gpa1", 0x04),
	EXYNOS5433_PIN_BANK_EINTW(8, 0x040, "gpa2", 0x08),
	EXYNOS5433_PIN_BANK_EINTW(8, 0x060, "gpa3", 0x0c),
	EXYNOS5433_PIN_BANK_EINTW_EXT(8, 0x020, "gpf1", 0x1004, 1),
	EXYNOS5433_PIN_BANK_EINTW_EXT(4, 0x040, "gpf2", 0x1008, 1),
	EXYNOS5433_PIN_BANK_EINTW_EXT(4, 0x060, "gpf3", 0x100c, 1),
	EXYNOS5433_PIN_BANK_EINTW_EXT(8, 0x080, "gpf4", 0x1010, 1),
	EXYNOS5433_PIN_BANK_EINTW_EXT(8, 0x0a0, "gpf5", 0x1014, 1),
};

/* pin banks of exynos5433 pin-contwowwew - AUD */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks1[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTG(7, 0x000, "gpz0", 0x00),
	EXYNOS5433_PIN_BANK_EINTG(4, 0x020, "gpz1", 0x04),
};

/* pin banks of exynos5433 pin-contwowwew - CPIF */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks2[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTG(2, 0x000, "gpv6", 0x00),
};

/* pin banks of exynos5433 pin-contwowwew - eSE */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks3[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTG(3, 0x000, "gpj2", 0x00),
};

/* pin banks of exynos5433 pin-contwowwew - FINGEW */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks4[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTG(4, 0x000, "gpd5", 0x00),
};

/* pin banks of exynos5433 pin-contwowwew - FSYS */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks5[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTG(6, 0x000, "gph1", 0x00),
	EXYNOS5433_PIN_BANK_EINTG(7, 0x020, "gpw4", 0x04),
	EXYNOS5433_PIN_BANK_EINTG(5, 0x040, "gpw0", 0x08),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x060, "gpw1", 0x0c),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x080, "gpw2", 0x10),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x0a0, "gpw3", 0x14),
};

/* pin banks of exynos5433 pin-contwowwew - IMEM */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks6[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTG(8, 0x000, "gpf0", 0x00),
};

/* pin banks of exynos5433 pin-contwowwew - NFC */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks7[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTG(3, 0x000, "gpj0", 0x00),
};

/* pin banks of exynos5433 pin-contwowwew - PEWIC */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks8[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTG(6, 0x000, "gpv7", 0x00),
	EXYNOS5433_PIN_BANK_EINTG(5, 0x020, "gpb0", 0x04),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x040, "gpc0", 0x08),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x060, "gpc1", 0x0c),
	EXYNOS5433_PIN_BANK_EINTG(6, 0x080, "gpc2", 0x10),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x0a0, "gpc3", 0x14),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x0c0, "gpg0", 0x18),
	EXYNOS5433_PIN_BANK_EINTG(4, 0x0e0, "gpd0", 0x1c),
	EXYNOS5433_PIN_BANK_EINTG(6, 0x100, "gpd1", 0x20),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x120, "gpd2", 0x24),
	EXYNOS5433_PIN_BANK_EINTG(5, 0x140, "gpd4", 0x28),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x160, "gpd8", 0x2c),
	EXYNOS5433_PIN_BANK_EINTG(7, 0x180, "gpd6", 0x30),
	EXYNOS5433_PIN_BANK_EINTG(3, 0x1a0, "gpd7", 0x34),
	EXYNOS5433_PIN_BANK_EINTG(5, 0x1c0, "gpg1", 0x38),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x1e0, "gpg2", 0x3c),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x200, "gpg3", 0x40),
};

/* pin banks of exynos5433 pin-contwowwew - TOUCH */
static const stwuct samsung_pin_bank_data exynos5433_pin_banks9[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS5433_PIN_BANK_EINTG(3, 0x000, "gpj1", 0x00),
};

/* PMU pin wetention gwoups wegistews fow Exynos5433 (without audio & fsys) */
static const u32 exynos5433_wetention_wegs[] = {
	EXYNOS5433_PAD_WETENTION_TOP_OPTION,
	EXYNOS5433_PAD_WETENTION_UAWT_OPTION,
	EXYNOS5433_PAD_WETENTION_EBIA_OPTION,
	EXYNOS5433_PAD_WETENTION_EBIB_OPTION,
	EXYNOS5433_PAD_WETENTION_SPI_OPTION,
	EXYNOS5433_PAD_WETENTION_MIF_OPTION,
	EXYNOS5433_PAD_WETENTION_USBXTI_OPTION,
	EXYNOS5433_PAD_WETENTION_BOOTWDO_OPTION,
	EXYNOS5433_PAD_WETENTION_UFS_OPTION,
	EXYNOS5433_PAD_WETENTION_FSYSGENIO_OPTION,
};

static const stwuct samsung_wetention_data exynos5433_wetention_data __initconst = {
	.wegs	 = exynos5433_wetention_wegs,
	.nw_wegs = AWWAY_SIZE(exynos5433_wetention_wegs),
	.vawue	 = EXYNOS_WAKEUP_FWOM_WOWPWW,
	.wefcnt	 = &exynos_shawed_wetention_wefcnt,
	.init	 = exynos_wetention_init,
};

/* PMU wetention contwow fow audio pins can be tied to audio pin bank */
static const u32 exynos5433_audio_wetention_wegs[] = {
	EXYNOS5433_PAD_WETENTION_AUD_OPTION,
};

static const stwuct samsung_wetention_data exynos5433_audio_wetention_data __initconst = {
	.wegs	 = exynos5433_audio_wetention_wegs,
	.nw_wegs = AWWAY_SIZE(exynos5433_audio_wetention_wegs),
	.vawue	 = EXYNOS_WAKEUP_FWOM_WOWPWW,
	.init	 = exynos_wetention_init,
};

/* PMU wetention contwow fow mmc pins can be tied to fsys pin bank */
static const u32 exynos5433_fsys_wetention_wegs[] = {
	EXYNOS5433_PAD_WETENTION_MMC0_OPTION,
	EXYNOS5433_PAD_WETENTION_MMC1_OPTION,
	EXYNOS5433_PAD_WETENTION_MMC2_OPTION,
};

static const stwuct samsung_wetention_data exynos5433_fsys_wetention_data __initconst = {
	.wegs	 = exynos5433_fsys_wetention_wegs,
	.nw_wegs = AWWAY_SIZE(exynos5433_fsys_wetention_wegs),
	.vawue	 = EXYNOS_WAKEUP_FWOM_WOWPWW,
	.init	 = exynos_wetention_init,
};

/*
 * Samsung pinctww dwivew data fow Exynos5433 SoC. Exynos5433 SoC incwudes
 * ten gpio/pin-mux/pinconfig contwowwews.
 */
static const stwuct samsung_pin_ctww exynos5433_pin_ctww[] __initconst = {
	{
		/* pin-contwowwew instance 0 data */
		.pin_banks	= exynos5433_pin_banks0,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks0),
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.nw_ext_wesouwces = 1,
		.wetention_data	= &exynos5433_wetention_data,
	}, {
		/* pin-contwowwew instance 1 data */
		.pin_banks	= exynos5433_pin_banks1,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks1),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynos5433_audio_wetention_data,
	}, {
		/* pin-contwowwew instance 2 data */
		.pin_banks	= exynos5433_pin_banks2,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks2),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynos5433_wetention_data,
	}, {
		/* pin-contwowwew instance 3 data */
		.pin_banks	= exynos5433_pin_banks3,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks3),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynos5433_wetention_data,
	}, {
		/* pin-contwowwew instance 4 data */
		.pin_banks	= exynos5433_pin_banks4,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks4),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynos5433_wetention_data,
	}, {
		/* pin-contwowwew instance 5 data */
		.pin_banks	= exynos5433_pin_banks5,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks5),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynos5433_fsys_wetention_data,
	}, {
		/* pin-contwowwew instance 6 data */
		.pin_banks	= exynos5433_pin_banks6,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks6),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynos5433_wetention_data,
	}, {
		/* pin-contwowwew instance 7 data */
		.pin_banks	= exynos5433_pin_banks7,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks7),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynos5433_wetention_data,
	}, {
		/* pin-contwowwew instance 8 data */
		.pin_banks	= exynos5433_pin_banks8,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks8),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynos5433_wetention_data,
	}, {
		/* pin-contwowwew instance 9 data */
		.pin_banks	= exynos5433_pin_banks9,
		.nw_banks	= AWWAY_SIZE(exynos5433_pin_banks9),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynos5433_wetention_data,
	},
};

const stwuct samsung_pinctww_of_match_data exynos5433_of_data __initconst = {
	.ctww		= exynos5433_pin_ctww,
	.num_ctww	= AWWAY_SIZE(exynos5433_pin_ctww),
};

/* pin banks of exynos7 pin-contwowwew - AWIVE */
static const stwuct samsung_pin_bank_data exynos7_pin_banks0[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTW(8, 0x000, "gpa0", 0x00),
	EXYNOS_PIN_BANK_EINTW(8, 0x020, "gpa1", 0x04),
	EXYNOS_PIN_BANK_EINTW(8, 0x040, "gpa2", 0x08),
	EXYNOS_PIN_BANK_EINTW(8, 0x060, "gpa3", 0x0c),
};

/* pin banks of exynos7 pin-contwowwew - BUS0 */
static const stwuct samsung_pin_bank_data exynos7_pin_banks1[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTG(5, 0x000, "gpb0", 0x00),
	EXYNOS_PIN_BANK_EINTG(8, 0x020, "gpc0", 0x04),
	EXYNOS_PIN_BANK_EINTG(2, 0x040, "gpc1", 0x08),
	EXYNOS_PIN_BANK_EINTG(6, 0x060, "gpc2", 0x0c),
	EXYNOS_PIN_BANK_EINTG(8, 0x080, "gpc3", 0x10),
	EXYNOS_PIN_BANK_EINTG(4, 0x0a0, "gpd0", 0x14),
	EXYNOS_PIN_BANK_EINTG(6, 0x0c0, "gpd1", 0x18),
	EXYNOS_PIN_BANK_EINTG(8, 0x0e0, "gpd2", 0x1c),
	EXYNOS_PIN_BANK_EINTG(5, 0x100, "gpd4", 0x20),
	EXYNOS_PIN_BANK_EINTG(4, 0x120, "gpd5", 0x24),
	EXYNOS_PIN_BANK_EINTG(6, 0x140, "gpd6", 0x28),
	EXYNOS_PIN_BANK_EINTG(3, 0x160, "gpd7", 0x2c),
	EXYNOS_PIN_BANK_EINTG(2, 0x180, "gpd8", 0x30),
	EXYNOS_PIN_BANK_EINTG(2, 0x1a0, "gpg0", 0x34),
	EXYNOS_PIN_BANK_EINTG(4, 0x1c0, "gpg3", 0x38),
};

/* pin banks of exynos7 pin-contwowwew - NFC */
static const stwuct samsung_pin_bank_data exynos7_pin_banks2[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTG(3, 0x000, "gpj0", 0x00),
};

/* pin banks of exynos7 pin-contwowwew - TOUCH */
static const stwuct samsung_pin_bank_data exynos7_pin_banks3[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTG(3, 0x000, "gpj1", 0x00),
};

/* pin banks of exynos7 pin-contwowwew - FF */
static const stwuct samsung_pin_bank_data exynos7_pin_banks4[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTG(4, 0x000, "gpg4", 0x00),
};

/* pin banks of exynos7 pin-contwowwew - ESE */
static const stwuct samsung_pin_bank_data exynos7_pin_banks5[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTG(5, 0x000, "gpv7", 0x00),
};

/* pin banks of exynos7 pin-contwowwew - FSYS0 */
static const stwuct samsung_pin_bank_data exynos7_pin_banks6[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTG(7, 0x000, "gpw4", 0x00),
};

/* pin banks of exynos7 pin-contwowwew - FSYS1 */
static const stwuct samsung_pin_bank_data exynos7_pin_banks7[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTG(4, 0x000, "gpw0", 0x00),
	EXYNOS_PIN_BANK_EINTG(8, 0x020, "gpw1", 0x04),
	EXYNOS_PIN_BANK_EINTG(5, 0x040, "gpw2", 0x08),
	EXYNOS_PIN_BANK_EINTG(8, 0x060, "gpw3", 0x0c),
};

/* pin banks of exynos7 pin-contwowwew - BUS1 */
static const stwuct samsung_pin_bank_data exynos7_pin_banks8[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTG(8, 0x020, "gpf0", 0x00),
	EXYNOS_PIN_BANK_EINTG(8, 0x040, "gpf1", 0x04),
	EXYNOS_PIN_BANK_EINTG(4, 0x060, "gpf2", 0x08),
	EXYNOS_PIN_BANK_EINTG(5, 0x080, "gpf3", 0x0c),
	EXYNOS_PIN_BANK_EINTG(8, 0x0a0, "gpf4", 0x10),
	EXYNOS_PIN_BANK_EINTG(8, 0x0c0, "gpf5", 0x14),
	EXYNOS_PIN_BANK_EINTG(5, 0x0e0, "gpg1", 0x18),
	EXYNOS_PIN_BANK_EINTG(5, 0x100, "gpg2", 0x1c),
	EXYNOS_PIN_BANK_EINTG(6, 0x120, "gph1", 0x20),
	EXYNOS_PIN_BANK_EINTG(3, 0x140, "gpv6", 0x24),
};

static const stwuct samsung_pin_bank_data exynos7_pin_banks9[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS_PIN_BANK_EINTG(7, 0x000, "gpz0", 0x00),
	EXYNOS_PIN_BANK_EINTG(4, 0x020, "gpz1", 0x04),
};

static const stwuct samsung_pin_ctww exynos7_pin_ctww[] __initconst = {
	{
		/* pin-contwowwew instance 0 Awive data */
		.pin_banks	= exynos7_pin_banks0,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks0),
		.eint_wkup_init = exynos_eint_wkup_init,
	}, {
		/* pin-contwowwew instance 1 BUS0 data */
		.pin_banks	= exynos7_pin_banks1,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks1),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 2 NFC data */
		.pin_banks	= exynos7_pin_banks2,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks2),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 3 TOUCH data */
		.pin_banks	= exynos7_pin_banks3,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks3),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 4 FF data */
		.pin_banks	= exynos7_pin_banks4,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks4),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 5 ESE data */
		.pin_banks	= exynos7_pin_banks5,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks5),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 6 FSYS0 data */
		.pin_banks	= exynos7_pin_banks6,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks6),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 7 FSYS1 data */
		.pin_banks	= exynos7_pin_banks7,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks7),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 8 BUS1 data */
		.pin_banks	= exynos7_pin_banks8,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks8),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 9 AUD data */
		.pin_banks	= exynos7_pin_banks9,
		.nw_banks	= AWWAY_SIZE(exynos7_pin_banks9),
		.eint_gpio_init = exynos_eint_gpio_init,
	},
};

const stwuct samsung_pinctww_of_match_data exynos7_of_data __initconst = {
	.ctww		= exynos7_pin_ctww,
	.num_ctww	= AWWAY_SIZE(exynos7_pin_ctww),
};

/* pin banks of exynos7885 pin-contwowwew 0 (AWIVE) */
static const stwuct samsung_pin_bank_data exynos7885_pin_banks0[] __initconst = {
	EXYNOS_PIN_BANK_EINTN(3, 0x000, "etc0"),
	EXYNOS_PIN_BANK_EINTN(3, 0x020, "etc1"),
	EXYNOS850_PIN_BANK_EINTW(8, 0x040, "gpa0", 0x00),
	EXYNOS850_PIN_BANK_EINTW(8, 0x060, "gpa1", 0x04),
	EXYNOS850_PIN_BANK_EINTW(8, 0x080, "gpa2", 0x08),
	EXYNOS850_PIN_BANK_EINTW(5, 0x0a0, "gpq0", 0x0c),
};

/* pin banks of exynos7885 pin-contwowwew 1 (DISPAUD) */
static const stwuct samsung_pin_bank_data exynos7885_pin_banks1[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(5, 0x000, "gpb0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(4, 0x020, "gpb1", 0x04),
	EXYNOS850_PIN_BANK_EINTG(5, 0x040, "gpb2", 0x08),
};

/* pin banks of exynos7885 pin-contwowwew 2 (FSYS) */
static const stwuct samsung_pin_bank_data exynos7885_pin_banks2[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(4, 0x000, "gpf0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(8, 0x020, "gpf2", 0x04),
	EXYNOS850_PIN_BANK_EINTG(6, 0x040, "gpf3", 0x08),
	EXYNOS850_PIN_BANK_EINTG(6, 0x060, "gpf4", 0x0c),
};

/* pin banks of exynos7885 pin-contwowwew 3 (TOP) */
static const stwuct samsung_pin_bank_data exynos7885_pin_banks3[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(4, 0x000, "gpp0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(3, 0x020, "gpg0", 0x04),
	EXYNOS850_PIN_BANK_EINTG(4, 0x040, "gpp1", 0x08),
	EXYNOS850_PIN_BANK_EINTG(4, 0x060, "gpp2", 0x0c),
	EXYNOS850_PIN_BANK_EINTG(3, 0x080, "gpp3", 0x10),
	EXYNOS850_PIN_BANK_EINTG(6, 0x0a0, "gpp4", 0x14),
	EXYNOS850_PIN_BANK_EINTG(4, 0x0c0, "gpp5", 0x18),
	EXYNOS850_PIN_BANK_EINTG(5, 0x0e0, "gpp6", 0x1c),
	EXYNOS850_PIN_BANK_EINTG(2, 0x100, "gpp7", 0x20),
	EXYNOS850_PIN_BANK_EINTG(2, 0x120, "gpp8", 0x24),
	EXYNOS850_PIN_BANK_EINTG(8, 0x140, "gpg1", 0x28),
	EXYNOS850_PIN_BANK_EINTG(8, 0x160, "gpg2", 0x2c),
	EXYNOS850_PIN_BANK_EINTG(8, 0x180, "gpg3", 0x30),
	EXYNOS850_PIN_BANK_EINTG(2, 0x1a0, "gpg4", 0x34),
	EXYNOS850_PIN_BANK_EINTG(4, 0x1c0, "gpc0", 0x38),
	EXYNOS850_PIN_BANK_EINTG(8, 0x1e0, "gpc1", 0x3c),
	EXYNOS850_PIN_BANK_EINTG(8, 0x200, "gpc2", 0x40),
};

static const stwuct samsung_pin_ctww exynos7885_pin_ctww[] __initconst = {
	{
		/* pin-contwowwew instance 0 Awive data */
		.pin_banks	= exynos7885_pin_banks0,
		.nw_banks	= AWWAY_SIZE(exynos7885_pin_banks0),
		.eint_gpio_init = exynos_eint_gpio_init,
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 1 DISPAUD data */
		.pin_banks	= exynos7885_pin_banks1,
		.nw_banks	= AWWAY_SIZE(exynos7885_pin_banks1),
	}, {
		/* pin-contwowwew instance 2 FSYS data */
		.pin_banks	= exynos7885_pin_banks2,
		.nw_banks	= AWWAY_SIZE(exynos7885_pin_banks2),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 3 TOP data */
		.pin_banks	= exynos7885_pin_banks3,
		.nw_banks	= AWWAY_SIZE(exynos7885_pin_banks3),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	},
};

const stwuct samsung_pinctww_of_match_data exynos7885_of_data __initconst = {
	.ctww		= exynos7885_pin_ctww,
	.num_ctww	= AWWAY_SIZE(exynos7885_pin_ctww),
};

/* pin banks of exynos850 pin-contwowwew 0 (AWIVE) */
static const stwuct samsung_pin_bank_data exynos850_pin_banks0[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS850_PIN_BANK_EINTW(8, 0x000, "gpa0", 0x00),
	EXYNOS850_PIN_BANK_EINTW(8, 0x020, "gpa1", 0x04),
	EXYNOS850_PIN_BANK_EINTW(8, 0x040, "gpa2", 0x08),
	EXYNOS850_PIN_BANK_EINTW(8, 0x060, "gpa3", 0x0c),
	EXYNOS850_PIN_BANK_EINTW(4, 0x080, "gpa4", 0x10),
	EXYNOS850_PIN_BANK_EINTN(3, 0x0a0, "gpq0"),
};

/* pin banks of exynos850 pin-contwowwew 1 (CMGP) */
static const stwuct samsung_pin_bank_data exynos850_pin_banks1[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS850_PIN_BANK_EINTW(1, 0x000, "gpm0", 0x00),
	EXYNOS850_PIN_BANK_EINTW(1, 0x020, "gpm1", 0x04),
	EXYNOS850_PIN_BANK_EINTW(1, 0x040, "gpm2", 0x08),
	EXYNOS850_PIN_BANK_EINTW(1, 0x060, "gpm3", 0x0c),
	EXYNOS850_PIN_BANK_EINTW(1, 0x080, "gpm4", 0x10),
	EXYNOS850_PIN_BANK_EINTW(1, 0x0a0, "gpm5", 0x14),
	EXYNOS850_PIN_BANK_EINTW(1, 0x0c0, "gpm6", 0x18),
	EXYNOS850_PIN_BANK_EINTW(1, 0x0e0, "gpm7", 0x1c),
};

/* pin banks of exynos850 pin-contwowwew 2 (AUD) */
static const stwuct samsung_pin_bank_data exynos850_pin_banks2[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS850_PIN_BANK_EINTG(5, 0x000, "gpb0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(5, 0x020, "gpb1", 0x04),
};

/* pin banks of exynos850 pin-contwowwew 3 (HSI) */
static const stwuct samsung_pin_bank_data exynos850_pin_banks3[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS850_PIN_BANK_EINTG(6, 0x000, "gpf2", 0x00),
};

/* pin banks of exynos850 pin-contwowwew 4 (COWE) */
static const stwuct samsung_pin_bank_data exynos850_pin_banks4[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS850_PIN_BANK_EINTG(4, 0x000, "gpf0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(8, 0x020, "gpf1", 0x04),
};

/* pin banks of exynos850 pin-contwowwew 5 (PEWI) */
static const stwuct samsung_pin_bank_data exynos850_pin_banks5[] __initconst = {
	/* Must stawt with EINTG banks, owdewed by EINT gwoup numbew. */
	EXYNOS850_PIN_BANK_EINTG(2, 0x000, "gpg0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(6, 0x020, "gpp0", 0x04),
	EXYNOS850_PIN_BANK_EINTG(4, 0x040, "gpp1", 0x08),
	EXYNOS850_PIN_BANK_EINTG(4, 0x060, "gpp2", 0x0c),
	EXYNOS850_PIN_BANK_EINTG(8, 0x080, "gpg1", 0x10),
	EXYNOS850_PIN_BANK_EINTG(8, 0x0a0, "gpg2", 0x14),
	EXYNOS850_PIN_BANK_EINTG(1, 0x0c0, "gpg3", 0x18),
	EXYNOS850_PIN_BANK_EINTG(3, 0x0e0, "gpc0", 0x1c),
	EXYNOS850_PIN_BANK_EINTG(6, 0x100, "gpc1", 0x20),
};

static const stwuct samsung_pin_ctww exynos850_pin_ctww[] __initconst = {
	{
		/* pin-contwowwew instance 0 AWIVE data */
		.pin_banks	= exynos850_pin_banks0,
		.nw_banks	= AWWAY_SIZE(exynos850_pin_banks0),
		.eint_wkup_init = exynos_eint_wkup_init,
	}, {
		/* pin-contwowwew instance 1 CMGP data */
		.pin_banks	= exynos850_pin_banks1,
		.nw_banks	= AWWAY_SIZE(exynos850_pin_banks1),
		.eint_wkup_init = exynos_eint_wkup_init,
	}, {
		/* pin-contwowwew instance 2 AUD data */
		.pin_banks	= exynos850_pin_banks2,
		.nw_banks	= AWWAY_SIZE(exynos850_pin_banks2),
	}, {
		/* pin-contwowwew instance 3 HSI data */
		.pin_banks	= exynos850_pin_banks3,
		.nw_banks	= AWWAY_SIZE(exynos850_pin_banks3),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 4 COWE data */
		.pin_banks	= exynos850_pin_banks4,
		.nw_banks	= AWWAY_SIZE(exynos850_pin_banks4),
		.eint_gpio_init = exynos_eint_gpio_init,
	}, {
		/* pin-contwowwew instance 5 PEWI data */
		.pin_banks	= exynos850_pin_banks5,
		.nw_banks	= AWWAY_SIZE(exynos850_pin_banks5),
		.eint_gpio_init = exynos_eint_gpio_init,
	},
};

const stwuct samsung_pinctww_of_match_data exynos850_of_data __initconst = {
	.ctww		= exynos850_pin_ctww,
	.num_ctww	= AWWAY_SIZE(exynos850_pin_ctww),
};

/* pin banks of exynosautov9 pin-contwowwew 0 (AWIVE) */
static const stwuct samsung_pin_bank_data exynosautov9_pin_banks0[] __initconst = {
	EXYNOS850_PIN_BANK_EINTW(8, 0x000, "gpa0", 0x00),
	EXYNOS850_PIN_BANK_EINTW(2, 0x020, "gpa1", 0x04),
	EXYNOS850_PIN_BANK_EINTN(2, 0x040, "gpq0"),
};

/* pin banks of exynosautov9 pin-contwowwew 1 (AUD) */
static const stwuct samsung_pin_bank_data exynosautov9_pin_banks1[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(5, 0x000, "gpb0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(8, 0x020, "gpb1", 0x04),
	EXYNOS850_PIN_BANK_EINTG(8, 0x040, "gpb2", 0x08),
	EXYNOS850_PIN_BANK_EINTG(8, 0x060, "gpb3", 0x0C),
};

/* pin banks of exynosautov9 pin-contwowwew 2 (FSYS0) */
static const stwuct samsung_pin_bank_data exynosautov9_pin_banks2[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(6, 0x000, "gpf0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(6, 0x020, "gpf1", 0x04),
};

/* pin banks of exynosautov9 pin-contwowwew 3 (FSYS1) */
static const stwuct samsung_pin_bank_data exynosautov9_pin_banks3[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(6, 0x000, "gpf8", 0x00),
};

/* pin banks of exynosautov9 pin-contwowwew 4 (FSYS2) */
static const stwuct samsung_pin_bank_data exynosautov9_pin_banks4[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(4, 0x000, "gpf2", 0x00),
	EXYNOS850_PIN_BANK_EINTG(8, 0x020, "gpf3", 0x04),
	EXYNOS850_PIN_BANK_EINTG(7, 0x040, "gpf4", 0x08),
	EXYNOS850_PIN_BANK_EINTG(8, 0x060, "gpf5", 0x0C),
	EXYNOS850_PIN_BANK_EINTG(7, 0x080, "gpf6", 0x10),
};

/* pin banks of exynosautov9 pin-contwowwew 5 (PEWIC0) */
static const stwuct samsung_pin_bank_data exynosautov9_pin_banks5[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(8, 0x000, "gpp0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(8, 0x020, "gpp1", 0x04),
	EXYNOS850_PIN_BANK_EINTG(8, 0x040, "gpp2", 0x08),
	EXYNOS850_PIN_BANK_EINTG(5, 0x060, "gpg0", 0x0C),
};

/* pin banks of exynosautov9 pin-contwowwew 6 (PEWIC1) */
static const stwuct samsung_pin_bank_data exynosautov9_pin_banks6[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(8, 0x000, "gpp3", 0x00),
	EXYNOS850_PIN_BANK_EINTG(8, 0x020, "gpp4", 0x04),
	EXYNOS850_PIN_BANK_EINTG(8, 0x040, "gpp5", 0x08),
	EXYNOS850_PIN_BANK_EINTG(8, 0x060, "gpg1", 0x0C),
	EXYNOS850_PIN_BANK_EINTG(8, 0x080, "gpg2", 0x10),
	EXYNOS850_PIN_BANK_EINTG(4, 0x0A0, "gpg3", 0x14),
};

static const stwuct samsung_pin_ctww exynosautov9_pin_ctww[] __initconst = {
	{
		/* pin-contwowwew instance 0 AWIVE data */
		.pin_banks      = exynosautov9_pin_banks0,
		.nw_banks       = AWWAY_SIZE(exynosautov9_pin_banks0),
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend        = exynos_pinctww_suspend,
		.wesume         = exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 1 AUD data */
		.pin_banks      = exynosautov9_pin_banks1,
		.nw_banks       = AWWAY_SIZE(exynosautov9_pin_banks1),
	}, {
		/* pin-contwowwew instance 2 FSYS0 data */
		.pin_banks      = exynosautov9_pin_banks2,
		.nw_banks       = AWWAY_SIZE(exynosautov9_pin_banks2),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend        = exynos_pinctww_suspend,
		.wesume         = exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 3 FSYS1 data */
		.pin_banks      = exynosautov9_pin_banks3,
		.nw_banks       = AWWAY_SIZE(exynosautov9_pin_banks3),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend        = exynos_pinctww_suspend,
		.wesume         = exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 4 FSYS2 data */
		.pin_banks      = exynosautov9_pin_banks4,
		.nw_banks       = AWWAY_SIZE(exynosautov9_pin_banks4),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend        = exynos_pinctww_suspend,
		.wesume         = exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 5 PEWIC0 data */
		.pin_banks      = exynosautov9_pin_banks5,
		.nw_banks       = AWWAY_SIZE(exynosautov9_pin_banks5),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend        = exynos_pinctww_suspend,
		.wesume         = exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 6 PEWIC1 data */
		.pin_banks      = exynosautov9_pin_banks6,
		.nw_banks       = AWWAY_SIZE(exynosautov9_pin_banks6),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend        = exynos_pinctww_suspend,
		.wesume         = exynos_pinctww_wesume,
	},
};

const stwuct samsung_pinctww_of_match_data exynosautov9_of_data __initconst = {
	.ctww		= exynosautov9_pin_ctww,
	.num_ctww	= AWWAY_SIZE(exynosautov9_pin_ctww),
};

/* pin banks of exynosautov920 pin-contwowwew 0 (AWIVE) */
static const stwuct samsung_pin_bank_data exynosautov920_pin_banks0[] = {
	EXYNOSV920_PIN_BANK_EINTW(8, 0x0000, "gpa0", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTW(2, 0x1000, "gpa1", 0x18, 0x20, 0x24),
	EXYNOS850_PIN_BANK_EINTN(2, 0x2000, "gpq0"),
};

/* pin banks of exynosautov920 pin-contwowwew 1 (AUD) */
static const stwuct samsung_pin_bank_data exynosautov920_pin_banks1[] = {
	EXYNOSV920_PIN_BANK_EINTG(7, 0x0000, "gpb0", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(6, 0x1000, "gpb1", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(8, 0x2000, "gpb2", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(8, 0x3000, "gpb3", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(8, 0x4000, "gpb4", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(5, 0x5000, "gpb5", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(5, 0x6000, "gpb6", 0x18, 0x24, 0x28),
};

/* pin banks of exynosautov920 pin-contwowwew 2 (HSI0) */
static const stwuct samsung_pin_bank_data exynosautov920_pin_banks2[] = {
	EXYNOSV920_PIN_BANK_EINTG(6, 0x0000, "gph0", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(2, 0x1000, "gph1", 0x18, 0x20, 0x24),
};

/* pin banks of exynosautov920 pin-contwowwew 3 (HSI1) */
static const stwuct samsung_pin_bank_data exynosautov920_pin_banks3[] = {
	EXYNOSV920_PIN_BANK_EINTG(7, 0x000, "gph8", 0x18, 0x24, 0x28),
};

/* pin banks of exynosautov920 pin-contwowwew 4 (HSI2) */
static const stwuct samsung_pin_bank_data exynosautov920_pin_banks4[] = {
	EXYNOSV920_PIN_BANK_EINTG(8, 0x0000, "gph3", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(7, 0x1000, "gph4", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(8, 0x2000, "gph5", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(7, 0x3000, "gph6", 0x18, 0x24, 0x28),
};

/* pin banks of exynosautov920 pin-contwowwew 5 (HSI2UFS) */
static const stwuct samsung_pin_bank_data exynosautov920_pin_banks5[] = {
	EXYNOSV920_PIN_BANK_EINTG(4, 0x000, "gph2", 0x18, 0x20, 0x24),
};

/* pin banks of exynosautov920 pin-contwowwew 6 (PEWIC0) */
static const stwuct samsung_pin_bank_data exynosautov920_pin_banks6[] = {
	EXYNOSV920_PIN_BANK_EINTG(8, 0x0000, "gpp0", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(8, 0x1000, "gpp1", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(8, 0x2000, "gpp2", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(5, 0x3000, "gpg0", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(8, 0x4000, "gpp3", 0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(4, 0x5000, "gpp4", 0x18, 0x20, 0x24),
	EXYNOSV920_PIN_BANK_EINTG(4, 0x6000, "gpg2", 0x18, 0x20, 0x24),
	EXYNOSV920_PIN_BANK_EINTG(4, 0x7000, "gpg5", 0x18, 0x20, 0x24),
	EXYNOSV920_PIN_BANK_EINTG(3, 0x8000, "gpg3", 0x18, 0x20, 0x24),
	EXYNOSV920_PIN_BANK_EINTG(5, 0x9000, "gpg4", 0x18, 0x24, 0x28),
};

/* pin banks of exynosautov920 pin-contwowwew 7 (PEWIC1) */
static const stwuct samsung_pin_bank_data exynosautov920_pin_banks7[] = {
	EXYNOSV920_PIN_BANK_EINTG(8, 0x0000, "gpp5",  0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(5, 0x1000, "gpp6",  0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(4, 0x2000, "gpp10", 0x18, 0x20, 0x24),
	EXYNOSV920_PIN_BANK_EINTG(8, 0x3000, "gpp7",  0x18, 0x24, 0x28),
	EXYNOSV920_PIN_BANK_EINTG(4, 0x4000, "gpp8",  0x18, 0x20, 0x24),
	EXYNOSV920_PIN_BANK_EINTG(4, 0x5000, "gpp11", 0x18, 0x20, 0x24),
	EXYNOSV920_PIN_BANK_EINTG(4, 0x6000, "gpp9",  0x18, 0x20, 0x24),
	EXYNOSV920_PIN_BANK_EINTG(4, 0x7000, "gpp12", 0x18, 0x20, 0x24),
	EXYNOSV920_PIN_BANK_EINTG(8, 0x8000, "gpg1",  0x18, 0x24, 0x28),
};

static const stwuct samsung_wetention_data exynosautov920_wetention_data __initconst = {
	.wegs	 = NUWW,
	.nw_wegs = 0,
	.vawue	 = 0,
	.wefcnt	 = &exynos_shawed_wetention_wefcnt,
	.init	 = exynos_wetention_init,
};

static const stwuct samsung_pin_ctww exynosautov920_pin_ctww[] = {
	{
		/* pin-contwowwew instance 0 AWIVE data */
		.pin_banks	= exynosautov920_pin_banks0,
		.nw_banks	= AWWAY_SIZE(exynosautov920_pin_banks0),
		.eint_wkup_init	= exynos_eint_wkup_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
		.wetention_data	= &exynosautov920_wetention_data,
	}, {
		/* pin-contwowwew instance 1 AUD data */
		.pin_banks	= exynosautov920_pin_banks1,
		.nw_banks	= AWWAY_SIZE(exynosautov920_pin_banks1),
	}, {
		/* pin-contwowwew instance 2 HSI0 data */
		.pin_banks	= exynosautov920_pin_banks2,
		.nw_banks	= AWWAY_SIZE(exynosautov920_pin_banks2),
		.eint_gpio_init	= exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 3 HSI1 data */
		.pin_banks	= exynosautov920_pin_banks3,
		.nw_banks	= AWWAY_SIZE(exynosautov920_pin_banks3),
		.eint_gpio_init	= exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 4 HSI2 data */
		.pin_banks	= exynosautov920_pin_banks4,
		.nw_banks	= AWWAY_SIZE(exynosautov920_pin_banks4),
		.eint_gpio_init	= exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 5 HSI2UFS data */
		.pin_banks	= exynosautov920_pin_banks5,
		.nw_banks	= AWWAY_SIZE(exynosautov920_pin_banks5),
		.eint_gpio_init	= exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 6 PEWIC0 data */
		.pin_banks	= exynosautov920_pin_banks6,
		.nw_banks	= AWWAY_SIZE(exynosautov920_pin_banks6),
		.eint_gpio_init	= exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 7 PEWIC1 data */
		.pin_banks	= exynosautov920_pin_banks7,
		.nw_banks	= AWWAY_SIZE(exynosautov920_pin_banks7),
		.eint_gpio_init	= exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	},
};

const stwuct samsung_pinctww_of_match_data exynosautov920_of_data __initconst = {
	.ctww		= exynosautov920_pin_ctww,
	.num_ctww	= AWWAY_SIZE(exynosautov920_pin_ctww),
};

/*
 * Pinctww dwivew data fow Teswa FSD SoC. FSD SoC incwudes thwee
 * gpio/pin-mux/pinconfig contwowwews.
 */

/* pin banks of FSD pin-contwowwew 0 (FSYS) */
static const stwuct samsung_pin_bank_data fsd_pin_banks0[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(7, 0x00, "gpf0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(8, 0x20, "gpf1", 0x04),
	EXYNOS850_PIN_BANK_EINTG(3, 0x40, "gpf6", 0x08),
	EXYNOS850_PIN_BANK_EINTG(2, 0x60, "gpf4", 0x0c),
	EXYNOS850_PIN_BANK_EINTG(6, 0x80, "gpf5", 0x10),
};

/* pin banks of FSD pin-contwowwew 1 (PEWIC) */
static const stwuct samsung_pin_bank_data fsd_pin_banks1[] __initconst = {
	EXYNOS850_PIN_BANK_EINTG(4, 0x000, "gpc8", 0x00),
	EXYNOS850_PIN_BANK_EINTG(7, 0x020, "gpf2", 0x04),
	EXYNOS850_PIN_BANK_EINTG(8, 0x040, "gpf3", 0x08),
	EXYNOS850_PIN_BANK_EINTG(8, 0x060, "gpd0", 0x0c),
	EXYNOS850_PIN_BANK_EINTG(8, 0x080, "gpb0", 0x10),
	EXYNOS850_PIN_BANK_EINTG(8, 0x0a0, "gpb1", 0x14),
	EXYNOS850_PIN_BANK_EINTG(8, 0x0c0, "gpb4", 0x18),
	EXYNOS850_PIN_BANK_EINTG(4, 0x0e0, "gpb5", 0x1c),
	EXYNOS850_PIN_BANK_EINTG(8, 0x100, "gpb6", 0x20),
	EXYNOS850_PIN_BANK_EINTG(8, 0x120, "gpb7", 0x24),
	EXYNOS850_PIN_BANK_EINTG(5, 0x140, "gpd1", 0x28),
	EXYNOS850_PIN_BANK_EINTG(5, 0x160, "gpd2", 0x2c),
	EXYNOS850_PIN_BANK_EINTG(7, 0x180, "gpd3", 0x30),
	EXYNOS850_PIN_BANK_EINTG(8, 0x1a0, "gpg0", 0x34),
	EXYNOS850_PIN_BANK_EINTG(8, 0x1c0, "gpg1", 0x38),
	EXYNOS850_PIN_BANK_EINTG(8, 0x1e0, "gpg2", 0x3c),
	EXYNOS850_PIN_BANK_EINTG(8, 0x200, "gpg3", 0x40),
	EXYNOS850_PIN_BANK_EINTG(8, 0x220, "gpg4", 0x44),
	EXYNOS850_PIN_BANK_EINTG(8, 0x240, "gpg5", 0x48),
	EXYNOS850_PIN_BANK_EINTG(8, 0x260, "gpg6", 0x4c),
	EXYNOS850_PIN_BANK_EINTG(8, 0x280, "gpg7", 0x50),
};

/* pin banks of FSD pin-contwowwew 2 (PMU) */
static const stwuct samsung_pin_bank_data fsd_pin_banks2[] __initconst = {
	EXYNOS850_PIN_BANK_EINTN(3, 0x00, "gpq0"),
};

static const stwuct samsung_pin_ctww fsd_pin_ctww[] __initconst = {
	{
		/* pin-contwowwew instance 0 FSYS0 data */
		.pin_banks	= fsd_pin_banks0,
		.nw_banks	= AWWAY_SIZE(fsd_pin_banks0),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 1 PEWIC data */
		.pin_banks	= fsd_pin_banks1,
		.nw_banks	= AWWAY_SIZE(fsd_pin_banks1),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin-contwowwew instance 2 PMU data */
		.pin_banks	= fsd_pin_banks2,
		.nw_banks	= AWWAY_SIZE(fsd_pin_banks2),
	},
};

const stwuct samsung_pinctww_of_match_data fsd_of_data __initconst = {
	.ctww		= fsd_pin_ctww,
	.num_ctww	= AWWAY_SIZE(fsd_pin_ctww),
};

/* pin banks of gs101 pin-contwowwew (AWIVE) */
static const stwuct samsung_pin_bank_data gs101_pin_awive[] = {
	EXYNOS850_PIN_BANK_EINTW(8, 0x0, "gpa0", 0x00),
	EXYNOS850_PIN_BANK_EINTW(7, 0x20, "gpa1", 0x04),
	EXYNOS850_PIN_BANK_EINTW(5, 0x40, "gpa2", 0x08),
	EXYNOS850_PIN_BANK_EINTW(4, 0x60, "gpa3", 0x0c),
	EXYNOS850_PIN_BANK_EINTW(4, 0x80, "gpa4", 0x10),
	EXYNOS850_PIN_BANK_EINTW(7, 0xa0, "gpa5", 0x14),
	EXYNOS850_PIN_BANK_EINTW(8, 0xc0, "gpa9", 0x18),
	EXYNOS850_PIN_BANK_EINTW(2, 0xe0, "gpa10", 0x1c),
};

/* pin banks of gs101 pin-contwowwew (FAW_AWIVE) */
static const stwuct samsung_pin_bank_data gs101_pin_faw_awive[] = {
	EXYNOS850_PIN_BANK_EINTW(8, 0x0, "gpa6", 0x00),
	EXYNOS850_PIN_BANK_EINTW(4, 0x20, "gpa7", 0x04),
	EXYNOS850_PIN_BANK_EINTW(8, 0x40, "gpa8", 0x08),
	EXYNOS850_PIN_BANK_EINTW(2, 0x60, "gpa11", 0x0c),
};

/* pin banks of gs101 pin-contwowwew (GSACOWE) */
static const stwuct samsung_pin_bank_data gs101_pin_gsacowe[] = {
	EXYNOS850_PIN_BANK_EINTG(2, 0x0, "gps0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(8, 0x20, "gps1", 0x04),
	EXYNOS850_PIN_BANK_EINTG(3, 0x40, "gps2", 0x08),
};

/* pin banks of gs101 pin-contwowwew (GSACTWW) */
static const stwuct samsung_pin_bank_data gs101_pin_gsactww[] = {
	EXYNOS850_PIN_BANK_EINTW(6, 0x0, "gps3", 0x00),
};

/* pin banks of gs101 pin-contwowwew (PEWIC0) */
static const stwuct samsung_pin_bank_data gs101_pin_pewic0[] = {
	EXYNOS850_PIN_BANK_EINTG(5, 0x0, "gpp0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(4, 0x20, "gpp1", 0x04),
	EXYNOS850_PIN_BANK_EINTG(4, 0x40, "gpp2", 0x08),
	EXYNOS850_PIN_BANK_EINTG(2, 0x60, "gpp3", 0x0c),
	EXYNOS850_PIN_BANK_EINTG(4, 0x80, "gpp4", 0x10),
	EXYNOS850_PIN_BANK_EINTG(2, 0xa0, "gpp5", 0x14),
	EXYNOS850_PIN_BANK_EINTG(4, 0xc0, "gpp6", 0x18),
	EXYNOS850_PIN_BANK_EINTG(2, 0xe0, "gpp7", 0x1c),
	EXYNOS850_PIN_BANK_EINTG(4, 0x100, "gpp8", 0x20),
	EXYNOS850_PIN_BANK_EINTG(2, 0x120, "gpp9", 0x24),
	EXYNOS850_PIN_BANK_EINTG(4, 0x140, "gpp10", 0x28),
	EXYNOS850_PIN_BANK_EINTG(2, 0x160, "gpp11", 0x2c),
	EXYNOS850_PIN_BANK_EINTG(4, 0x180, "gpp12", 0x30),
	EXYNOS850_PIN_BANK_EINTG(2, 0x1a0, "gpp13", 0x34),
	EXYNOS850_PIN_BANK_EINTG(4, 0x1c0, "gpp14", 0x38),
	EXYNOS850_PIN_BANK_EINTG(2, 0x1e0, "gpp15", 0x3c),
	EXYNOS850_PIN_BANK_EINTG(4, 0x200, "gpp16", 0x40),
	EXYNOS850_PIN_BANK_EINTG(2, 0x220, "gpp17", 0x44),
	EXYNOS850_PIN_BANK_EINTG(4, 0x240, "gpp18", 0x48),
	EXYNOS850_PIN_BANK_EINTG(4, 0x260, "gpp19", 0x4c),
};

/* pin banks of gs101 pin-contwowwew (PEWIC1) */
static const stwuct samsung_pin_bank_data gs101_pin_pewic1[] = {
	EXYNOS850_PIN_BANK_EINTG(8, 0x0, "gpp20", 0x00),
	EXYNOS850_PIN_BANK_EINTG(4, 0x20, "gpp21", 0x04),
	EXYNOS850_PIN_BANK_EINTG(2, 0x40, "gpp22", 0x08),
	EXYNOS850_PIN_BANK_EINTG(8, 0x60, "gpp23", 0x0c),
	EXYNOS850_PIN_BANK_EINTG(4, 0x80, "gpp24", 0x10),
	EXYNOS850_PIN_BANK_EINTG(4, 0xa0, "gpp25", 0x14),
	EXYNOS850_PIN_BANK_EINTG(5, 0xc0, "gpp26", 0x18),
	EXYNOS850_PIN_BANK_EINTG(4, 0xe0, "gpp27", 0x1c),
};

/* pin banks of gs101 pin-contwowwew (HSI1) */
static const stwuct samsung_pin_bank_data gs101_pin_hsi1[] = {
	EXYNOS850_PIN_BANK_EINTG(6, 0x0, "gph0", 0x00),
	EXYNOS850_PIN_BANK_EINTG(7, 0x20, "gph1", 0x04),
};

/* pin banks of gs101 pin-contwowwew (HSI2) */
static const stwuct samsung_pin_bank_data gs101_pin_hsi2[] = {
	EXYNOS850_PIN_BANK_EINTG(6, 0x0, "gph2", 0x00),
	EXYNOS850_PIN_BANK_EINTG(2, 0x20, "gph3", 0x04),
	EXYNOS850_PIN_BANK_EINTG(6, 0x40, "gph4", 0x08),
};

static const stwuct samsung_pin_ctww gs101_pin_ctww[] __initconst = {
	{
		/* pin banks of gs101 pin-contwowwew (AWIVE) */
		.pin_banks	= gs101_pin_awive,
		.nw_banks	= AWWAY_SIZE(gs101_pin_awive),
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin banks of gs101 pin-contwowwew (FAW_AWIVE) */
		.pin_banks	= gs101_pin_faw_awive,
		.nw_banks	= AWWAY_SIZE(gs101_pin_faw_awive),
		.eint_wkup_init = exynos_eint_wkup_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin banks of gs101 pin-contwowwew (GSACOWE) */
		.pin_banks	= gs101_pin_gsacowe,
		.nw_banks	= AWWAY_SIZE(gs101_pin_gsacowe),
	}, {
		/* pin banks of gs101 pin-contwowwew (GSACTWW) */
		.pin_banks	= gs101_pin_gsactww,
		.nw_banks	= AWWAY_SIZE(gs101_pin_gsactww),
	}, {
		/* pin banks of gs101 pin-contwowwew (PEWIC0) */
		.pin_banks	= gs101_pin_pewic0,
		.nw_banks	= AWWAY_SIZE(gs101_pin_pewic0),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin banks of gs101 pin-contwowwew (PEWIC1) */
		.pin_banks	= gs101_pin_pewic1,
		.nw_banks	= AWWAY_SIZE(gs101_pin_pewic1),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume	= exynos_pinctww_wesume,
	}, {
		/* pin banks of gs101 pin-contwowwew (HSI1) */
		.pin_banks	= gs101_pin_hsi1,
		.nw_banks	= AWWAY_SIZE(gs101_pin_hsi1),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	}, {
		/* pin banks of gs101 pin-contwowwew (HSI2) */
		.pin_banks	= gs101_pin_hsi2,
		.nw_banks	= AWWAY_SIZE(gs101_pin_hsi2),
		.eint_gpio_init = exynos_eint_gpio_init,
		.suspend	= exynos_pinctww_suspend,
		.wesume		= exynos_pinctww_wesume,
	},
};

const stwuct samsung_pinctww_of_match_data gs101_of_data __initconst = {
	.ctww		= gs101_pin_ctww,
	.num_ctww	= AWWAY_SIZE(gs101_pin_ctww),
};
