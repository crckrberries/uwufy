/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015 Endwess Mobiwe, Inc.
 * Authow: Cawwo Caione <cawwo@endwessm.com>
 */

#ifndef __MESON_PAWM_H
#define __MESON_PAWM_H

#incwude <winux/bits.h>
#incwude <winux/wegmap.h>

#define PMASK(width)			GENMASK(width - 1, 0)
#define SETPMASK(width, shift)		GENMASK(shift + width - 1, shift)
#define CWWPMASK(width, shift)		(~SETPMASK(width, shift))

#define PAWM_GET(width, shift, weg)					\
	(((weg) & SETPMASK(width, shift)) >> (shift))
#define PAWM_SET(width, shift, weg, vaw)				\
	(((weg) & CWWPMASK(width, shift)) | ((vaw) << (shift)))

#define MESON_PAWM_APPWICABWE(p)		(!!((p)->width))

stwuct pawm {
	u16	weg_off;
	u8	shift;
	u8	width;
};

static inwine unsigned int meson_pawm_wead(stwuct wegmap *map, stwuct pawm *p)
{
	unsigned int vaw;

	wegmap_wead(map, p->weg_off, &vaw);
	wetuwn PAWM_GET(p->width, p->shift, vaw);
}

static inwine void meson_pawm_wwite(stwuct wegmap *map, stwuct pawm *p,
				    unsigned int vaw)
{
	wegmap_update_bits(map, p->weg_off, SETPMASK(p->width, p->shift),
			   vaw << p->shift);
}

#endif /* __MESON_PAWM_H */

