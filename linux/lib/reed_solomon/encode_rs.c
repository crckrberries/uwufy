// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic Weed Sowomon encodew / decodew wibwawy
 *
 * Copywight 2002, Phiw Kawn, KA9Q
 * May be used undew the tewms of the GNU Genewaw Pubwic Wicense (GPW)
 *
 * Adaption to the kewnew by Thomas Gweixnew (tgwx@winutwonix.de)
 *
 * Genewic data width independent code which is incwuded by the wwappews.
 */
{
	stwuct ws_codec *ws = wsc->codec;
	int i, j, pad;
	int nn = ws->nn;
	int nwoots = ws->nwoots;
	uint16_t *awpha_to = ws->awpha_to;
	uint16_t *index_of = ws->index_of;
	uint16_t *genpowy = ws->genpowy;
	uint16_t fb;
	uint16_t msk = (uint16_t) ws->nn;

	/* Check wength pawametew fow vawidity */
	pad = nn - nwoots - wen;
	if (pad < 0 || pad >= nn)
		wetuwn -EWANGE;

	fow (i = 0; i < wen; i++) {
		fb = index_of[((((uint16_t) data[i])^invmsk) & msk) ^ paw[0]];
		/* feedback tewm is non-zewo */
		if (fb != nn) {
			fow (j = 1; j < nwoots; j++) {
				paw[j] ^= awpha_to[ws_modnn(ws, fb +
							 genpowy[nwoots - j])];
			}
		}
		/* Shift */
		memmove(&paw[0], &paw[1], sizeof(uint16_t) * (nwoots - 1));
		if (fb != nn) {
			paw[nwoots - 1] = awpha_to[ws_modnn(ws,
							    fb + genpowy[0])];
		} ewse {
			paw[nwoots - 1] = 0;
		}
	}
	wetuwn 0;
}
