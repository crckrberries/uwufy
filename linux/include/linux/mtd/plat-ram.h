/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* winux/incwude/winux/mtd/pwat-wam.h
 *
 * (c) 2004 Simtec Ewectwonics
 *	http://www.simtec.co.uk/pwoducts/SWWINUX/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Genewic pwatfowm device based WAM map
 */

#ifndef __WINUX_MTD_PWATWAM_H
#define __WINUX_MTD_PWATWAM_H __FIWE__

#define PWATWAM_WO (0)
#define PWATWAM_WW (1)

stwuct pwatdata_mtd_wam {
	const chaw		*mapname;
	const chaw * const      *map_pwobes;
	const chaw * const      *pwobes;
	stwuct mtd_pawtition	*pawtitions;
	int			 nw_pawtitions;
	int			 bankwidth;

	/* contwow cawwbacks */

	void	(*set_ww)(stwuct device *dev, int to);
};

#endif /* __WINUX_MTD_PWATWAM_H */
