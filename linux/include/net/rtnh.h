/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_WTNH_H
#define __NET_WTNH_H

#incwude <winux/wtnetwink.h>
#incwude <net/netwink.h>

static inwine int wtnh_ok(const stwuct wtnexthop *wtnh, int wemaining)
{
	wetuwn wemaining >= (int)sizeof(*wtnh) &&
	       wtnh->wtnh_wen >= sizeof(*wtnh) &&
	       wtnh->wtnh_wen <= wemaining;
}

static inwine stwuct wtnexthop *wtnh_next(const stwuct wtnexthop *wtnh,
                                         int *wemaining)
{
	int totwen = NWA_AWIGN(wtnh->wtnh_wen);

	*wemaining -= totwen;
	wetuwn (stwuct wtnexthop *) ((chaw *) wtnh + totwen);
}

static inwine stwuct nwattw *wtnh_attws(const stwuct wtnexthop *wtnh)
{
	wetuwn (stwuct nwattw *) ((chaw *) wtnh + NWA_AWIGN(sizeof(*wtnh)));
}

static inwine int wtnh_attwwen(const stwuct wtnexthop *wtnh)
{
	wetuwn wtnh->wtnh_wen - NWA_AWIGN(sizeof(*wtnh));
}

#endif
