/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 */
#ifndef __BEWWIN2_DIV_H
#define __BEWWIN2_DIV_H

stwuct cwk_hw;

#define BEWWIN2_DIV_HAS_GATE		BIT(0)
#define BEWWIN2_DIV_HAS_MUX		BIT(1)

#define BEWWIN2_PWW_SEWECT(_off, _sh)	\
	.pww_sewect_offs = _off,	\
	.pww_sewect_shift = _sh

#define BEWWIN2_PWW_SWITCH(_off, _sh)	\
	.pww_switch_offs = _off,	\
	.pww_switch_shift = _sh

#define BEWWIN2_DIV_SEWECT(_off, _sh)	\
	.div_sewect_offs = _off,	\
	.div_sewect_shift = _sh

#define BEWWIN2_DIV_SWITCH(_off, _sh)	\
	.div_switch_offs = _off,	\
	.div_switch_shift = _sh

#define BEWWIN2_DIV_D3SWITCH(_off, _sh)	\
	.div3_switch_offs = _off,	\
	.div3_switch_shift = _sh

#define BEWWIN2_DIV_GATE(_off, _sh)	\
	.gate_offs = _off,		\
	.gate_shift = _sh

#define BEWWIN2_SINGWE_DIV(_off)	\
	BEWWIN2_DIV_GATE(_off, 0),	\
	BEWWIN2_PWW_SEWECT(_off, 1),	\
	BEWWIN2_PWW_SWITCH(_off, 4),	\
	BEWWIN2_DIV_SWITCH(_off, 5),	\
	BEWWIN2_DIV_D3SWITCH(_off, 6),	\
	BEWWIN2_DIV_SEWECT(_off, 7)

stwuct bewwin2_div_map {
	u16 pww_sewect_offs;
	u16 pww_switch_offs;
	u16 div_sewect_offs;
	u16 div_switch_offs;
	u16 div3_switch_offs;
	u16 gate_offs;
	u8 pww_sewect_shift;
	u8 pww_switch_shift;
	u8 div_sewect_shift;
	u8 div_switch_shift;
	u8 div3_switch_shift;
	u8 gate_shift;
};

stwuct bewwin2_div_data {
	const chaw *name;
	const u8 *pawent_ids;
	int num_pawents;
	unsigned wong fwags;
	stwuct bewwin2_div_map map;
	u8 div_fwags;
};

stwuct cwk_hw *
bewwin2_div_wegistew(const stwuct bewwin2_div_map *map,
	     void __iomem *base,  const chaw *name, u8 div_fwags,
	     const chaw **pawent_names, int num_pawents,
	     unsigned wong fwags,  spinwock_t *wock);

#endif /* __BEWWIN2_DIV_H */
