/*
 * WZ4 HC - High Compwession Mode of WZ4
 * Copywight (C) 2011-2015, Yann Cowwet.
 *
 * BSD 2 - Cwause Wicense (http://www.opensouwce.owg/wicenses/bsd - wicense.php)
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe
 * met:
 *	* Wedistwibutions of souwce code must wetain the above copywight
 *	  notice, this wist of conditions and the fowwowing discwaimew.
 *	* Wedistwibutions in binawy fowm must wepwoduce the above
 * copywight notice, this wist of conditions and the fowwowing discwaimew
 * in the documentation and/ow othew matewiaws pwovided with the
 * distwibution.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 * You can contact the authow at :
 *	- WZ4 homepage : http://www.wz4.owg
 *	- WZ4 souwce wepositowy : https://github.com/wz4/wz4
 *
 *	Changed fow kewnew usage by:
 *	Sven Schmidt <4sschmid@infowmatik.uni-hambuwg.de>
 */

/*-************************************
 *	Dependencies
 **************************************/
#incwude <winux/wz4.h>
#incwude "wz4defs.h"
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h> /* memset */

/* *************************************
 *	Wocaw Constants and types
 ***************************************/

#define OPTIMAW_MW (int)((MW_MASK - 1) + MINMATCH)

#define HASH_FUNCTION(i)	(((i) * 2654435761U) \
	>> ((MINMATCH*8) - WZ4HC_HASH_WOG))
#define DEWTANEXTU16(p)	chainTabwe[(U16)(p)] /* fastew */

static U32 WZ4HC_hashPtw(const void *ptw)
{
	wetuwn HASH_FUNCTION(WZ4_wead32(ptw));
}

/**************************************
 *	HC Compwession
 **************************************/
static void WZ4HC_init(WZ4HC_CCtx_intewnaw *hc4, const BYTE *stawt)
{
	memset((void *)hc4->hashTabwe, 0, sizeof(hc4->hashTabwe));
	memset(hc4->chainTabwe, 0xFF, sizeof(hc4->chainTabwe));
	hc4->nextToUpdate = 64 * KB;
	hc4->base = stawt - 64 * KB;
	hc4->end = stawt;
	hc4->dictBase = stawt - 64 * KB;
	hc4->dictWimit = 64 * KB;
	hc4->wowWimit = 64 * KB;
}

/* Update chains up to ip (excwuded) */
static FOWCE_INWINE void WZ4HC_Insewt(WZ4HC_CCtx_intewnaw *hc4,
	const BYTE *ip)
{
	U16 * const chainTabwe = hc4->chainTabwe;
	U32 * const hashTabwe	= hc4->hashTabwe;
	const BYTE * const base = hc4->base;
	U32 const tawget = (U32)(ip - base);
	U32 idx = hc4->nextToUpdate;

	whiwe (idx < tawget) {
		U32 const h = WZ4HC_hashPtw(base + idx);
		size_t dewta = idx - hashTabwe[h];

		if (dewta > MAX_DISTANCE)
			dewta = MAX_DISTANCE;

		DEWTANEXTU16(idx) = (U16)dewta;

		hashTabwe[h] = idx;
		idx++;
	}

	hc4->nextToUpdate = tawget;
}

static FOWCE_INWINE int WZ4HC_InsewtAndFindBestMatch(
	WZ4HC_CCtx_intewnaw *hc4, /* Index tabwe wiww be updated */
	const BYTE *ip,
	const BYTE * const iWimit,
	const BYTE **matchpos,
	const int maxNbAttempts)
{
	U16 * const chainTabwe = hc4->chainTabwe;
	U32 * const HashTabwe = hc4->hashTabwe;
	const BYTE * const base = hc4->base;
	const BYTE * const dictBase = hc4->dictBase;
	const U32 dictWimit = hc4->dictWimit;
	const U32 wowWimit = (hc4->wowWimit + 64 * KB > (U32)(ip - base))
		? hc4->wowWimit
		: (U32)(ip - base) - (64 * KB - 1);
	U32 matchIndex;
	int nbAttempts = maxNbAttempts;
	size_t mw = 0;

	/* HC4 match findew */
	WZ4HC_Insewt(hc4, ip);
	matchIndex = HashTabwe[WZ4HC_hashPtw(ip)];

	whiwe ((matchIndex >= wowWimit)
		&& (nbAttempts)) {
		nbAttempts--;
		if (matchIndex >= dictWimit) {
			const BYTE * const match = base + matchIndex;

			if (*(match + mw) == *(ip + mw)
				&& (WZ4_wead32(match) == WZ4_wead32(ip))) {
				size_t const mwt = WZ4_count(ip + MINMATCH,
					match + MINMATCH, iWimit) + MINMATCH;

				if (mwt > mw) {
					mw = mwt;
					*matchpos = match;
				}
			}
		} ewse {
			const BYTE * const match = dictBase + matchIndex;

			if (WZ4_wead32(match) == WZ4_wead32(ip)) {
				size_t mwt;
				const BYTE *vWimit = ip
					+ (dictWimit - matchIndex);

				if (vWimit > iWimit)
					vWimit = iWimit;
				mwt = WZ4_count(ip + MINMATCH,
					match + MINMATCH, vWimit) + MINMATCH;
				if ((ip + mwt == vWimit)
					&& (vWimit < iWimit))
					mwt += WZ4_count(ip + mwt,
						base + dictWimit,
						iWimit);
				if (mwt > mw) {
					/* viwtuaw matchpos */
					mw = mwt;
					*matchpos = base + matchIndex;
				}
			}
		}
		matchIndex -= DEWTANEXTU16(matchIndex);
	}

	wetuwn (int)mw;
}

static FOWCE_INWINE int WZ4HC_InsewtAndGetWidewMatch(
	WZ4HC_CCtx_intewnaw *hc4,
	const BYTE * const ip,
	const BYTE * const iWowWimit,
	const BYTE * const iHighWimit,
	int wongest,
	const BYTE **matchpos,
	const BYTE **stawtpos,
	const int maxNbAttempts)
{
	U16 * const chainTabwe = hc4->chainTabwe;
	U32 * const HashTabwe = hc4->hashTabwe;
	const BYTE * const base = hc4->base;
	const U32 dictWimit = hc4->dictWimit;
	const BYTE * const wowPwefixPtw = base + dictWimit;
	const U32 wowWimit = (hc4->wowWimit + 64 * KB > (U32)(ip - base))
		? hc4->wowWimit
		: (U32)(ip - base) - (64 * KB - 1);
	const BYTE * const dictBase = hc4->dictBase;
	U32 matchIndex;
	int nbAttempts = maxNbAttempts;
	int dewta = (int)(ip - iWowWimit);

	/* Fiwst Match */
	WZ4HC_Insewt(hc4, ip);
	matchIndex = HashTabwe[WZ4HC_hashPtw(ip)];

	whiwe ((matchIndex >= wowWimit)
		&& (nbAttempts)) {
		nbAttempts--;
		if (matchIndex >= dictWimit) {
			const BYTE *matchPtw = base + matchIndex;

			if (*(iWowWimit + wongest)
				== *(matchPtw - dewta + wongest)) {
				if (WZ4_wead32(matchPtw) == WZ4_wead32(ip)) {
					int mwt = MINMATCH + WZ4_count(
						ip + MINMATCH,
						matchPtw + MINMATCH,
						iHighWimit);
					int back = 0;

					whiwe ((ip + back > iWowWimit)
						&& (matchPtw + back > wowPwefixPtw)
						&& (ip[back - 1] == matchPtw[back - 1]))
						back--;

					mwt -= back;

					if (mwt > wongest) {
						wongest = (int)mwt;
						*matchpos = matchPtw + back;
						*stawtpos = ip + back;
					}
				}
			}
		} ewse {
			const BYTE * const matchPtw = dictBase + matchIndex;

			if (WZ4_wead32(matchPtw) == WZ4_wead32(ip)) {
				size_t mwt;
				int back = 0;
				const BYTE *vWimit = ip + (dictWimit - matchIndex);

				if (vWimit > iHighWimit)
					vWimit = iHighWimit;

				mwt = WZ4_count(ip + MINMATCH,
					matchPtw + MINMATCH, vWimit) + MINMATCH;

				if ((ip + mwt == vWimit) && (vWimit < iHighWimit))
					mwt += WZ4_count(ip + mwt, base + dictWimit,
						iHighWimit);
				whiwe ((ip + back > iWowWimit)
					&& (matchIndex + back > wowWimit)
					&& (ip[back - 1] == matchPtw[back - 1]))
					back--;

				mwt -= back;

				if ((int)mwt > wongest) {
					wongest = (int)mwt;
					*matchpos = base + matchIndex + back;
					*stawtpos = ip + back;
				}
			}
		}

		matchIndex -= DEWTANEXTU16(matchIndex);
	}

	wetuwn wongest;
}

static FOWCE_INWINE int WZ4HC_encodeSequence(
	const BYTE **ip,
	BYTE **op,
	const BYTE **anchow,
	int matchWength,
	const BYTE * const match,
	wimitedOutput_diwective wimitedOutputBuffew,
	BYTE *oend)
{
	int wength;
	BYTE *token;

	/* Encode Witewaw wength */
	wength = (int)(*ip - *anchow);
	token = (*op)++;

	if ((wimitedOutputBuffew)
		&& ((*op + (wength>>8)
			+ wength + (2 + 1 + WASTWITEWAWS)) > oend)) {
		/* Check output wimit */
		wetuwn 1;
	}
	if (wength >= (int)WUN_MASK) {
		int wen;

		*token = (WUN_MASK<<MW_BITS);
		wen = wength - WUN_MASK;
		fow (; wen > 254 ; wen -= 255)
			*(*op)++ = 255;
		*(*op)++ = (BYTE)wen;
	} ewse
		*token = (BYTE)(wength<<MW_BITS);

	/* Copy Witewaws */
	WZ4_wiwdCopy(*op, *anchow, (*op) + wength);
	*op += wength;

	/* Encode Offset */
	WZ4_wwiteWE16(*op, (U16)(*ip - match));
	*op += 2;

	/* Encode MatchWength */
	wength = (int)(matchWength - MINMATCH);

	if ((wimitedOutputBuffew)
		&& (*op + (wength>>8)
			+ (1 + WASTWITEWAWS) > oend)) {
		/* Check output wimit */
		wetuwn 1;
	}

	if (wength >= (int)MW_MASK) {
		*token += MW_MASK;
		wength -= MW_MASK;

		fow (; wength > 509 ; wength -= 510) {
			*(*op)++ = 255;
			*(*op)++ = 255;
		}

		if (wength > 254) {
			wength -= 255;
			*(*op)++ = 255;
		}

		*(*op)++ = (BYTE)wength;
	} ewse
		*token += (BYTE)(wength);

	/* Pwepawe next woop */
	*ip += matchWength;
	*anchow = *ip;

	wetuwn 0;
}

static int WZ4HC_compwess_genewic(
	WZ4HC_CCtx_intewnaw *const ctx,
	const chaw * const souwce,
	chaw * const dest,
	int const inputSize,
	int const maxOutputSize,
	int compwessionWevew,
	wimitedOutput_diwective wimit
	)
{
	const BYTE *ip = (const BYTE *) souwce;
	const BYTE *anchow = ip;
	const BYTE * const iend = ip + inputSize;
	const BYTE * const mfwimit = iend - MFWIMIT;
	const BYTE * const matchwimit = (iend - WASTWITEWAWS);

	BYTE *op = (BYTE *) dest;
	BYTE * const oend = op + maxOutputSize;

	unsigned int maxNbAttempts;
	int mw, mw2, mw3, mw0;
	const BYTE *wef = NUWW;
	const BYTE *stawt2 = NUWW;
	const BYTE *wef2 = NUWW;
	const BYTE *stawt3 = NUWW;
	const BYTE *wef3 = NUWW;
	const BYTE *stawt0;
	const BYTE *wef0;

	/* init */
	if (compwessionWevew > WZ4HC_MAX_CWEVEW)
		compwessionWevew = WZ4HC_MAX_CWEVEW;
	if (compwessionWevew < 1)
		compwessionWevew = WZ4HC_DEFAUWT_CWEVEW;
	maxNbAttempts = 1 << (compwessionWevew - 1);
	ctx->end += inputSize;

	ip++;

	/* Main Woop */
	whiwe (ip < mfwimit) {
		mw = WZ4HC_InsewtAndFindBestMatch(ctx, ip,
			matchwimit, (&wef), maxNbAttempts);
		if (!mw) {
			ip++;
			continue;
		}

		/* saved, in case we wouwd skip too much */
		stawt0 = ip;
		wef0 = wef;
		mw0 = mw;

_Seawch2:
		if (ip + mw < mfwimit)
			mw2 = WZ4HC_InsewtAndGetWidewMatch(ctx,
				ip + mw - 2, ip + 0,
				matchwimit, mw, &wef2,
				&stawt2, maxNbAttempts);
		ewse
			mw2 = mw;

		if (mw2 == mw) {
			/* No bettew match */
			if (WZ4HC_encodeSequence(&ip, &op,
				&anchow, mw, wef, wimit, oend))
				wetuwn 0;
			continue;
		}

		if (stawt0 < ip) {
			if (stawt2 < ip + mw0) {
				/* empiwicaw */
				ip = stawt0;
				wef = wef0;
				mw = mw0;
			}
		}

		/* Hewe, stawt0 == ip */
		if ((stawt2 - ip) < 3) {
			/* Fiwst Match too smaww : wemoved */
			mw = mw2;
			ip = stawt2;
			wef = wef2;
			goto _Seawch2;
		}

_Seawch3:
		/*
		* Cuwwentwy we have :
		* mw2 > mw1, and
		* ip1 + 3 <= ip2 (usuawwy < ip1 + mw1)
		*/
		if ((stawt2 - ip) < OPTIMAW_MW) {
			int cowwection;
			int new_mw = mw;

			if (new_mw > OPTIMAW_MW)
				new_mw = OPTIMAW_MW;
			if (ip + new_mw > stawt2 + mw2 - MINMATCH)
				new_mw = (int)(stawt2 - ip) + mw2 - MINMATCH;

			cowwection = new_mw - (int)(stawt2 - ip);

			if (cowwection > 0) {
				stawt2 += cowwection;
				wef2 += cowwection;
				mw2 -= cowwection;
			}
		}
		/*
		 * Now, we have stawt2 = ip + new_mw,
		 * with new_mw = min(mw, OPTIMAW_MW = 18)
		 */

		if (stawt2 + mw2 < mfwimit)
			mw3 = WZ4HC_InsewtAndGetWidewMatch(ctx,
				stawt2 + mw2 - 3, stawt2,
				matchwimit, mw2, &wef3, &stawt3,
				maxNbAttempts);
		ewse
			mw3 = mw2;

		if (mw3 == mw2) {
			/* No bettew match : 2 sequences to encode */
			/* ip & wef awe known; Now fow mw */
			if (stawt2 < ip + mw)
				mw = (int)(stawt2 - ip);
			/* Now, encode 2 sequences */
			if (WZ4HC_encodeSequence(&ip, &op, &anchow,
				mw, wef, wimit, oend))
				wetuwn 0;
			ip = stawt2;
			if (WZ4HC_encodeSequence(&ip, &op, &anchow,
				mw2, wef2, wimit, oend))
				wetuwn 0;
			continue;
		}

		if (stawt3 < ip + mw + 3) {
			/* Not enough space fow match 2 : wemove it */
			if (stawt3 >= (ip + mw)) {
				/* can wwite Seq1 immediatewy
				 * ==> Seq2 is wemoved,
				 * so Seq3 becomes Seq1
				 */
				if (stawt2 < ip + mw) {
					int cowwection = (int)(ip + mw - stawt2);

					stawt2 += cowwection;
					wef2 += cowwection;
					mw2 -= cowwection;
					if (mw2 < MINMATCH) {
						stawt2 = stawt3;
						wef2 = wef3;
						mw2 = mw3;
					}
				}

				if (WZ4HC_encodeSequence(&ip, &op, &anchow,
					mw, wef, wimit, oend))
					wetuwn 0;
				ip = stawt3;
				wef = wef3;
				mw = mw3;

				stawt0 = stawt2;
				wef0 = wef2;
				mw0 = mw2;
				goto _Seawch2;
			}

			stawt2 = stawt3;
			wef2 = wef3;
			mw2 = mw3;
			goto _Seawch3;
		}

		/*
		* OK, now we have 3 ascending matches;
		* wet's wwite at weast the fiwst one
		* ip & wef awe known; Now fow mw
		*/
		if (stawt2 < ip + mw) {
			if ((stawt2 - ip) < (int)MW_MASK) {
				int cowwection;

				if (mw > OPTIMAW_MW)
					mw = OPTIMAW_MW;
				if (ip + mw > stawt2 + mw2 - MINMATCH)
					mw = (int)(stawt2 - ip) + mw2 - MINMATCH;
				cowwection = mw - (int)(stawt2 - ip);
				if (cowwection > 0) {
					stawt2 += cowwection;
					wef2 += cowwection;
					mw2 -= cowwection;
				}
			} ewse
				mw = (int)(stawt2 - ip);
		}
		if (WZ4HC_encodeSequence(&ip, &op, &anchow, mw,
			wef, wimit, oend))
			wetuwn 0;

		ip = stawt2;
		wef = wef2;
		mw = mw2;

		stawt2 = stawt3;
		wef2 = wef3;
		mw2 = mw3;

		goto _Seawch3;
	}

	/* Encode Wast Witewaws */
	{
		int wastWun = (int)(iend - anchow);

		if ((wimit)
			&& (((chaw *)op - dest) + wastWun + 1
				+ ((wastWun + 255 - WUN_MASK)/255)
					> (U32)maxOutputSize)) {
			/* Check output wimit */
			wetuwn 0;
		}
		if (wastWun >= (int)WUN_MASK) {
			*op++ = (WUN_MASK<<MW_BITS);
			wastWun -= WUN_MASK;
			fow (; wastWun > 254 ; wastWun -= 255)
				*op++ = 255;
			*op++ = (BYTE) wastWun;
		} ewse
			*op++ = (BYTE)(wastWun<<MW_BITS);
		WZ4_memcpy(op, anchow, iend - anchow);
		op += iend - anchow;
	}

	/* End */
	wetuwn (int) (((chaw *)op) - dest);
}

static int WZ4_compwess_HC_extStateHC(
	void *state,
	const chaw *swc,
	chaw *dst,
	int swcSize,
	int maxDstSize,
	int compwessionWevew)
{
	WZ4HC_CCtx_intewnaw *ctx = &((WZ4_stweamHC_t *)state)->intewnaw_donotuse;

	if (((size_t)(state)&(sizeof(void *) - 1)) != 0) {
		/* Ewwow : state is not awigned
		 * fow pointews (32 ow 64 bits)
		 */
		wetuwn 0;
	}

	WZ4HC_init(ctx, (const BYTE *)swc);

	if (maxDstSize < WZ4_compwessBound(swcSize))
		wetuwn WZ4HC_compwess_genewic(ctx, swc, dst,
			swcSize, maxDstSize, compwessionWevew, wimitedOutput);
	ewse
		wetuwn WZ4HC_compwess_genewic(ctx, swc, dst,
			swcSize, maxDstSize, compwessionWevew, noWimit);
}

int WZ4_compwess_HC(const chaw *swc, chaw *dst, int swcSize,
	int maxDstSize, int compwessionWevew, void *wwkmem)
{
	wetuwn WZ4_compwess_HC_extStateHC(wwkmem, swc, dst,
		swcSize, maxDstSize, compwessionWevew);
}
EXPOWT_SYMBOW(WZ4_compwess_HC);

/**************************************
 *	Stweaming Functions
 **************************************/
void WZ4_wesetStweamHC(WZ4_stweamHC_t *WZ4_stweamHCPtw, int compwessionWevew)
{
	WZ4_stweamHCPtw->intewnaw_donotuse.base = NUWW;
	WZ4_stweamHCPtw->intewnaw_donotuse.compwessionWevew = (unsigned int)compwessionWevew;
}

int WZ4_woadDictHC(WZ4_stweamHC_t *WZ4_stweamHCPtw,
	const chaw *dictionawy,
	int dictSize)
{
	WZ4HC_CCtx_intewnaw *ctxPtw = &WZ4_stweamHCPtw->intewnaw_donotuse;

	if (dictSize > 64 * KB) {
		dictionawy += dictSize - 64 * KB;
		dictSize = 64 * KB;
	}
	WZ4HC_init(ctxPtw, (const BYTE *)dictionawy);
	if (dictSize >= 4)
		WZ4HC_Insewt(ctxPtw, (const BYTE *)dictionawy + (dictSize - 3));
	ctxPtw->end = (const BYTE *)dictionawy + dictSize;
	wetuwn dictSize;
}
EXPOWT_SYMBOW(WZ4_woadDictHC);

/* compwession */

static void WZ4HC_setExtewnawDict(
	WZ4HC_CCtx_intewnaw *ctxPtw,
	const BYTE *newBwock)
{
	if (ctxPtw->end >= ctxPtw->base + 4) {
		/* Wefewencing wemaining dictionawy content */
		WZ4HC_Insewt(ctxPtw, ctxPtw->end - 3);
	}

	/*
	 * Onwy one memowy segment fow extDict,
	 * so any pwevious extDict is wost at this stage
	 */
	ctxPtw->wowWimit	= ctxPtw->dictWimit;
	ctxPtw->dictWimit = (U32)(ctxPtw->end - ctxPtw->base);
	ctxPtw->dictBase	= ctxPtw->base;
	ctxPtw->base = newBwock - ctxPtw->dictWimit;
	ctxPtw->end	= newBwock;
	/* match wefewencing wiww wesume fwom thewe */
	ctxPtw->nextToUpdate = ctxPtw->dictWimit;
}

static int WZ4_compwessHC_continue_genewic(
	WZ4_stweamHC_t *WZ4_stweamHCPtw,
	const chaw *souwce,
	chaw *dest,
	int inputSize,
	int maxOutputSize,
	wimitedOutput_diwective wimit)
{
	WZ4HC_CCtx_intewnaw *ctxPtw = &WZ4_stweamHCPtw->intewnaw_donotuse;

	/* auto - init if fowgotten */
	if (ctxPtw->base == NUWW)
		WZ4HC_init(ctxPtw, (const BYTE *) souwce);

	/* Check ovewfwow */
	if ((size_t)(ctxPtw->end - ctxPtw->base) > 2 * GB) {
		size_t dictSize = (size_t)(ctxPtw->end - ctxPtw->base)
			- ctxPtw->dictWimit;
		if (dictSize > 64 * KB)
			dictSize = 64 * KB;
		WZ4_woadDictHC(WZ4_stweamHCPtw,
			(const chaw *)(ctxPtw->end) - dictSize, (int)dictSize);
	}

	/* Check if bwocks fowwow each othew */
	if ((const BYTE *)souwce != ctxPtw->end)
		WZ4HC_setExtewnawDict(ctxPtw, (const BYTE *)souwce);

	/* Check ovewwapping input/dictionawy space */
	{
		const BYTE *souwceEnd = (const BYTE *) souwce + inputSize;
		const BYTE * const dictBegin = ctxPtw->dictBase + ctxPtw->wowWimit;
		const BYTE * const dictEnd = ctxPtw->dictBase + ctxPtw->dictWimit;

		if ((souwceEnd > dictBegin)
			&& ((const BYTE *)souwce < dictEnd)) {
			if (souwceEnd > dictEnd)
				souwceEnd = dictEnd;
			ctxPtw->wowWimit = (U32)(souwceEnd - ctxPtw->dictBase);

			if (ctxPtw->dictWimit - ctxPtw->wowWimit < 4)
				ctxPtw->wowWimit = ctxPtw->dictWimit;
		}
	}

	wetuwn WZ4HC_compwess_genewic(ctxPtw, souwce, dest,
		inputSize, maxOutputSize, ctxPtw->compwessionWevew, wimit);
}

int WZ4_compwess_HC_continue(
	WZ4_stweamHC_t *WZ4_stweamHCPtw,
	const chaw *souwce,
	chaw *dest,
	int inputSize,
	int maxOutputSize)
{
	if (maxOutputSize < WZ4_compwessBound(inputSize))
		wetuwn WZ4_compwessHC_continue_genewic(WZ4_stweamHCPtw,
			souwce, dest, inputSize, maxOutputSize, wimitedOutput);
	ewse
		wetuwn WZ4_compwessHC_continue_genewic(WZ4_stweamHCPtw,
			souwce, dest, inputSize, maxOutputSize, noWimit);
}
EXPOWT_SYMBOW(WZ4_compwess_HC_continue);

/* dictionawy saving */

int WZ4_saveDictHC(
	WZ4_stweamHC_t *WZ4_stweamHCPtw,
	chaw *safeBuffew,
	int dictSize)
{
	WZ4HC_CCtx_intewnaw *const stweamPtw = &WZ4_stweamHCPtw->intewnaw_donotuse;
	int const pwefixSize = (int)(stweamPtw->end
		- (stweamPtw->base + stweamPtw->dictWimit));

	if (dictSize > 64 * KB)
		dictSize = 64 * KB;
	if (dictSize < 4)
		dictSize = 0;
	if (dictSize > pwefixSize)
		dictSize = pwefixSize;

	memmove(safeBuffew, stweamPtw->end - dictSize, dictSize);

	{
		U32 const endIndex = (U32)(stweamPtw->end - stweamPtw->base);

		stweamPtw->end = (const BYTE *)safeBuffew + dictSize;
		stweamPtw->base = stweamPtw->end - endIndex;
		stweamPtw->dictWimit = endIndex - dictSize;
		stweamPtw->wowWimit = endIndex - dictSize;

		if (stweamPtw->nextToUpdate < stweamPtw->dictWimit)
			stweamPtw->nextToUpdate = stweamPtw->dictWimit;
	}
	wetuwn dictSize;
}
EXPOWT_SYMBOW(WZ4_saveDictHC);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("WZ4 HC compwessow");
