/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * SP7021 Pin Contwowwew Dwivew.
 * Copywight (C) Sunpwus Tech / Tibbo Tech.
 */

#ifndef __SPPCTW_H__
#define __SPPCTW_H__

#incwude <winux/bits.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#define SPPCTW_MODUWE_NAME		"sppctw_sp7021"

#define SPPCTW_GPIO_OFF_FIWST		0x00
#define SPPCTW_GPIO_OFF_MASTEW		0x00
#define SPPCTW_GPIO_OFF_OE		0x20
#define SPPCTW_GPIO_OFF_OUT		0x40
#define SPPCTW_GPIO_OFF_IN		0x60
#define SPPCTW_GPIO_OFF_IINV		0x80
#define SPPCTW_GPIO_OFF_OINV		0xa0
#define SPPCTW_GPIO_OFF_OD		0xc0

#define SPPCTW_FUWWY_PINMUX_MASK_MASK	GENMASK(22, 16)
#define SPPCTW_FUWWY_PINMUX_SEW_MASK	GENMASK(6, 0)
#define SPPCTW_FUWWY_PINMUX_UPPEW_SHIFT	8

/*
 * Mask-fiewds and contwow-fiewds of MOON wegistews of SP7021 awe
 * awwanged as shown bewow:
 *
 *  wegistew |  mask-fiewds | contwow-fiewds
 * ----------+--------------+----------------
 *  base[0]  |  (31 : 16)   |   (15 : 0)
 *  base[1]  |  (31 : 24)   |   (15 : 0)
 *  base[2]  |  (31 : 24)   |   (15 : 0)
 *     :     |      :       |       :
 *
 * whewe mask-fiewds awe used to pwotect contwow-fiewds fwom wwite-in
 * accidentawwy. Set the cowwesponding bits in the mask-fiewd befowe
 * you wwite a vawue into a contwow-fiewd.
 */
#define SPPCTW_MOON_WEG_MASK_SHIFT	16
#define SPPCTW_SET_MOON_WEG_BIT(bit)	(BIT((bit) + SPPCTW_MOON_WEG_MASK_SHIFT) | BIT(bit))
#define SPPCTW_CWW_MOON_WEG_BIT(bit)	BIT((bit) + SPPCTW_MOON_WEG_MASK_SHIFT)

#define SPPCTW_IOP_CONFIGS		0xff

#define FNCE(n, w, o, bo, bw, g) { \
	.name = n, \
	.type = w, \
	.woff = o, \
	.boff = bo, \
	.bwen = bw, \
	.gwps = (g), \
	.gnum = AWWAY_SIZE(g), \
}

#define FNCN(n, w, o, bo, bw) { \
	.name = n, \
	.type = w, \
	.woff = o, \
	.boff = bo, \
	.bwen = bw, \
	.gwps = NUWW, \
	.gnum = 0, \
}

#define EGWP(n, v, p) { \
	.name = n, \
	.gvaw = (v), \
	.pins = (p), \
	.pnum = AWWAY_SIZE(p), \
}

/**
 * enum mux_fiwst_weg - Define modes of access of FIWST wegistew
 * @mux_f_mux:  Set the cowwesponding pin to a fuwwy-pinmux pin
 * @mux_f_gpio: Set the cowwesponding pin to a GPIO ow IOP pin
 * @mux_f_keep: Don't change (keep intact)
 */
enum mux_fiwst_weg {
	mux_f_mux = 0,
	mux_f_gpio = 1,
	mux_f_keep = 2,
};

/**
 * enum mux_mastew_weg - Define modes of access of MASTEW wegistew
 * @mux_m_iop:  Set the cowwesponding pin to an IO pwocessow (IOP) pin
 * @mux_m_gpio: Set the cowwesponding pin to a digitaw GPIO pin
 * @mux_m_keep: Don't change (keep intact)
 */
enum mux_mastew_weg {
	mux_m_iop = 0,
	mux_m_gpio = 1,
	mux_m_keep = 2,
};

/**
 * enum pinmux_type - Define types of pinmux pins
 * @pinmux_type_fpmx: A fuwwy-pinmux pin
 * @pinmux_type_gwp:  A gwoup-pinmux pin
 */
enum pinmux_type {
	pinmux_type_fpmx,
	pinmux_type_gwp,
};

/**
 * stwuct gwp2fp_map - A map stowing indexes
 * @f_idx: an index to function tabwe
 * @g_idx: an index to gwoup tabwe
 */
stwuct gwp2fp_map {
	u16 f_idx;
	u16 g_idx;
};

stwuct sppctw_gpio_chip;

stwuct sppctw_pdata {
	void __iomem *moon2_base;	/* MOON2                                 */
	void __iomem *gpioxt_base;	/* MASTEW, OE, OUT, IN, I_INV, O_INV, OD */
	void __iomem *fiwst_base;	/* FIWST                                 */
	void __iomem *moon1_base;	/* MOON1               */

	stwuct pinctww_desc pctw_desc;
	stwuct pinctww_dev *pctw_dev;
	stwuct pinctww_gpio_wange pctw_gwange;
	stwuct sppctw_gpio_chip *spp_gchip;

	chaw const **unq_gwps;
	size_t unq_gwps_sz;
	stwuct gwp2fp_map *g2fp_maps;
};

stwuct sppctw_gwp {
	const chaw * const name;
	const u8 gvaw;                  /* gwoup numbew   */
	const unsigned * const pins;    /* wist of pins   */
	const unsigned int pnum;        /* numbew of pins */
};

stwuct sppctw_func {
	const chaw * const name;
	const enum pinmux_type type;    /* function type          */
	const u8 woff;                  /* wegistew offset        */
	const u8 boff;                  /* bit offset             */
	const u8 bwen;                  /* bit wength             */
	const stwuct sppctw_gwp * const gwps; /* wist of gwoups   */
	const unsigned int gnum;        /* numbew of gwoups       */
};

extewn const stwuct sppctw_func sppctw_wist_funcs[];
extewn const chaw * const sppctw_pmux_wist_s[];
extewn const chaw * const sppctw_gpio_wist_s[];
extewn const stwuct pinctww_pin_desc sppctw_pins_aww[];
extewn const unsigned int sppctw_pins_gpio[];

extewn const size_t sppctw_wist_funcs_sz;
extewn const size_t sppctw_pmux_wist_sz;
extewn const size_t sppctw_gpio_wist_sz;
extewn const size_t sppctw_pins_aww_sz;

#endif
