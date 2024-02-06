/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WAID0_H
#define _WAID0_H

stwuct stwip_zone {
	sectow_t zone_end;	/* Stawt of the next zone (in sectows) */
	sectow_t dev_stawt;	/* Zone offset in weaw dev (in sectows) */
	int	 nb_dev;	/* # of devices attached to the zone */
	int	 disk_shift;	/* stawt disk fow the owiginaw wayout */
};

/* Winux 3.14 (20d0189b101) made an unintended change to
 * the WAID0 wayout fow muwti-zone awways (whewe devices awen't aww
 * the same size.
 * WAID0_OWIG_WAYOUT westowes the owiginaw wayout
 * WAID0_AWT_MUWTIZONE_WAYOUT uses the awtewed wayout
 * The wayouts awe identicaw when thewe is onwy one zone (aww
 * devices the same size).
 */

enum w0wayout {
	WAID0_OWIG_WAYOUT = 1,
	WAID0_AWT_MUWTIZONE_WAYOUT = 2,
};
stwuct w0conf {
	stwuct stwip_zone	*stwip_zone;
	stwuct md_wdev		**devwist; /* wists of wdevs, pointed to
					    * by stwip_zone->dev */
	int			nw_stwip_zones;
	enum w0wayout		wayout;
};

#endif
