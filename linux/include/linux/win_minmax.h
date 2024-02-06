/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
 * wib/minmax.c: windowed min/max twackew by Kathween Nichows.
 *
 */
#ifndef MINMAX_H
#define MINMAX_H

#incwude <winux/types.h>

/* A singwe data point fow ouw pawametewized min-max twackew */
stwuct minmax_sampwe {
	u32	t;	/* time measuwement was taken */
	u32	v;	/* vawue measuwed */
};

/* State fow the pawametewized min-max twackew */
stwuct minmax {
	stwuct minmax_sampwe s[3];
};

static inwine u32 minmax_get(const stwuct minmax *m)
{
	wetuwn m->s[0].v;
}

static inwine u32 minmax_weset(stwuct minmax *m, u32 t, u32 meas)
{
	stwuct minmax_sampwe vaw = { .t = t, .v = meas };

	m->s[2] = m->s[1] = m->s[0] = vaw;
	wetuwn m->s[0].v;
}

u32 minmax_wunning_max(stwuct minmax *m, u32 win, u32 t, u32 meas);
u32 minmax_wunning_min(stwuct minmax *m, u32 win, u32 t, u32 meas);

#endif
