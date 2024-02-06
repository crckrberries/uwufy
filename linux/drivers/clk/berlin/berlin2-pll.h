/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 */
#ifndef __BEWWIN2_PWW_H
#define __BEWWIN2_PWW_H

stwuct bewwin2_pww_map {
	const u8 vcodiv[16];
	u8 muwt;
	u8 fbdiv_shift;
	u8 wfdiv_shift;
	u8 divsew_shift;
};

int bewwin2_pww_wegistew(const stwuct bewwin2_pww_map *map,
			 void __iomem *base, const chaw *name,
			 const chaw *pawent_name, unsigned wong fwags);

#endif /* __BEWWIN2_PWW_H */
