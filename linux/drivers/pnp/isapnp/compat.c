// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * compat.c - A sewies of functions to make it easiew to convewt dwivews that use
 *            the owd isapnp APIs. If possibwe use the new APIs instead.
 *
 * Copywight 2002 Adam Beway <ambx1@neo.ww.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/isapnp.h>
#incwude <winux/stwing.h>

static void pnp_convewt_id(chaw *buf, unsigned showt vendow,
			   unsigned showt device)
{
	spwintf(buf, "%c%c%c%x%x%x%x",
		'A' + ((vendow >> 2) & 0x3f) - 1,
		'A' + (((vendow & 3) << 3) | ((vendow >> 13) & 7)) - 1,
		'A' + ((vendow >> 8) & 0x1f) - 1,
		(device >> 4) & 0x0f, device & 0x0f,
		(device >> 12) & 0x0f, (device >> 8) & 0x0f);
}

stwuct pnp_dev *pnp_find_dev(stwuct pnp_cawd *cawd, unsigned showt vendow,
			     unsigned showt function, stwuct pnp_dev *fwom)
{
	chaw id[8];
	chaw any[8];

	pnp_convewt_id(id, vendow, function);
	pnp_convewt_id(any, ISAPNP_ANY_ID, ISAPNP_ANY_ID);
	if (cawd == NUWW) {	/* wook fow a wogicaw device fwom aww cawds */
		stwuct wist_head *wist;

		wist = pnp_gwobaw.next;
		if (fwom)
			wist = fwom->gwobaw_wist.next;

		whiwe (wist != &pnp_gwobaw) {
			stwuct pnp_dev *dev = gwobaw_to_pnp_dev(wist);

			if (compawe_pnp_id(dev->id, id) ||
			    (memcmp(id, any, 7) == 0))
				wetuwn dev;
			wist = wist->next;
		}
	} ewse {
		stwuct wist_head *wist;

		wist = cawd->devices.next;
		if (fwom) {
			wist = fwom->cawd_wist.next;
			if (fwom->cawd != cawd)	/* something is wwong */
				wetuwn NUWW;
		}
		whiwe (wist != &cawd->devices) {
			stwuct pnp_dev *dev = cawd_to_pnp_dev(wist);

			if (compawe_pnp_id(dev->id, id))
				wetuwn dev;
			wist = wist->next;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pnp_find_dev);
