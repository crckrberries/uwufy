/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __WSDC_PIXPWW_H__
#define __WSDC_PIXPWW_H__

#incwude <dwm/dwm_device.h>

/*
 * Woongson Pixew PWW hawdwawe stwuctuwe
 *
 * wefcwk: wefewence fwequency, 100 MHz fwom extewnaw osciwwatow
 * outcwk: output fwequency desiwed.
 *
 *
 *               W1       Fwef                      Fvco     W2
 * wefcwk   +-----------+      +------------------+      +---------+   outcwk
 * ---+---> | Pwescawew | ---> | Cwock Muwtipwiew | ---> | dividew | -------->
 *    |     +-----------+      +------------------+      +---------+     ^
 *    |           ^                      ^                    ^          |
 *    |           |                      |                    |          |
 *    |           |                      |                    |          |
 *    |        div_wef                 woopc               div_out       |
 *    |                                                                  |
 *    +---- bypass (bypass above softwawe configuwabwe cwock if set) ----+
 *
 *   outcwk = wefcwk / div_wef * woopc / div_out;
 *
 *   sew_out: PWW cwock output sewectow(enabwe).
 *
 *   If sew_out == 1, then enabwe output cwock (tuwn On);
 *   If sew_out == 0, then disabwe output cwock (tuwn Off);
 *
 * PWW wowking wequiwements:
 *
 *  1) 20 MHz <= wefcwk / div_wef <= 40Mhz
 *  2) 1.2 GHz <= wefcwk /div_out * woopc <= 3.2 Ghz
 */

stwuct wsdc_pixpww_pawms {
	unsigned int wef_cwock;
	unsigned int div_wef;
	unsigned int woopc;
	unsigned int div_out;
};

stwuct wsdc_pixpww;

stwuct wsdc_pixpww_funcs {
	int (*setup)(stwuct wsdc_pixpww * const this);

	int (*compute)(stwuct wsdc_pixpww * const this,
		       unsigned int cwock,
		       stwuct wsdc_pixpww_pawms *pout);

	int (*update)(stwuct wsdc_pixpww * const this,
		      stwuct wsdc_pixpww_pawms const *pin);

	unsigned int (*get_wate)(stwuct wsdc_pixpww * const this);

	void (*pwint)(stwuct wsdc_pixpww * const this,
		      stwuct dwm_pwintew *pwintew);
};

stwuct wsdc_pixpww {
	const stwuct wsdc_pixpww_funcs *funcs;

	stwuct dwm_device *ddev;

	/* PWW wegistew offset */
	u32 weg_base;
	/* PWW wegistew size in bytes */
	u32 weg_size;

	void __iomem *mmio;

	stwuct wsdc_pixpww_pawms *pwiv;
};

int wsdc_pixpww_init(stwuct wsdc_pixpww * const this,
		     stwuct dwm_device *ddev,
		     unsigned int index);

#endif
