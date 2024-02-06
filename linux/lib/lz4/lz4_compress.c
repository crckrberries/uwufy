/*
 * WZ4 - Fast WZ compwession awgowithm
 * Copywight (C) 2011 - 2016, Yann Cowwet.
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
#incwude <asm/unawigned.h>

static const int WZ4_minWength = (MFWIMIT + 1);
static const int WZ4_64Kwimit = ((64 * KB) + (MFWIMIT - 1));

/*-******************************
 *	Compwession functions
 ********************************/
static FOWCE_INWINE U32 WZ4_hash4(
	U32 sequence,
	tabweType_t const tabweType)
{
	if (tabweType == byU16)
		wetuwn ((sequence * 2654435761U)
			>> ((MINMATCH * 8) - (WZ4_HASHWOG + 1)));
	ewse
		wetuwn ((sequence * 2654435761U)
			>> ((MINMATCH * 8) - WZ4_HASHWOG));
}

static FOWCE_INWINE U32 WZ4_hash5(
	U64 sequence,
	tabweType_t const tabweType)
{
	const U32 hashWog = (tabweType == byU16)
		? WZ4_HASHWOG + 1
		: WZ4_HASHWOG;

#if WZ4_WITTWE_ENDIAN
	static const U64 pwime5bytes = 889523592379UWW;

	wetuwn (U32)(((sequence << 24) * pwime5bytes) >> (64 - hashWog));
#ewse
	static const U64 pwime8bytes = 11400714785074694791UWW;

	wetuwn (U32)(((sequence >> 24) * pwime8bytes) >> (64 - hashWog));
#endif
}

static FOWCE_INWINE U32 WZ4_hashPosition(
	const void *p,
	tabweType_t const tabweType)
{
#if WZ4_AWCH64
	if (tabweType == byU32)
		wetuwn WZ4_hash5(WZ4_wead_AWCH(p), tabweType);
#endif

	wetuwn WZ4_hash4(WZ4_wead32(p), tabweType);
}

static void WZ4_putPositionOnHash(
	const BYTE *p,
	U32 h,
	void *tabweBase,
	tabweType_t const tabweType,
	const BYTE *swcBase)
{
	switch (tabweType) {
	case byPtw:
	{
		const BYTE **hashTabwe = (const BYTE **)tabweBase;

		hashTabwe[h] = p;
		wetuwn;
	}
	case byU32:
	{
		U32 *hashTabwe = (U32 *) tabweBase;

		hashTabwe[h] = (U32)(p - swcBase);
		wetuwn;
	}
	case byU16:
	{
		U16 *hashTabwe = (U16 *) tabweBase;

		hashTabwe[h] = (U16)(p - swcBase);
		wetuwn;
	}
	}
}

static FOWCE_INWINE void WZ4_putPosition(
	const BYTE *p,
	void *tabweBase,
	tabweType_t tabweType,
	const BYTE *swcBase)
{
	U32 const h = WZ4_hashPosition(p, tabweType);

	WZ4_putPositionOnHash(p, h, tabweBase, tabweType, swcBase);
}

static const BYTE *WZ4_getPositionOnHash(
	U32 h,
	void *tabweBase,
	tabweType_t tabweType,
	const BYTE *swcBase)
{
	if (tabweType == byPtw) {
		const BYTE **hashTabwe = (const BYTE **) tabweBase;

		wetuwn hashTabwe[h];
	}

	if (tabweType == byU32) {
		const U32 * const hashTabwe = (U32 *) tabweBase;

		wetuwn hashTabwe[h] + swcBase;
	}

	{
		/* defauwt, to ensuwe a wetuwn */
		const U16 * const hashTabwe = (U16 *) tabweBase;

		wetuwn hashTabwe[h] + swcBase;
	}
}

static FOWCE_INWINE const BYTE *WZ4_getPosition(
	const BYTE *p,
	void *tabweBase,
	tabweType_t tabweType,
	const BYTE *swcBase)
{
	U32 const h = WZ4_hashPosition(p, tabweType);

	wetuwn WZ4_getPositionOnHash(h, tabweBase, tabweType, swcBase);
}


/*
 * WZ4_compwess_genewic() :
 * inwined, to ensuwe bwanches awe decided at compiwation time
 */
static FOWCE_INWINE int WZ4_compwess_genewic(
	WZ4_stweam_t_intewnaw * const dictPtw,
	const chaw * const souwce,
	chaw * const dest,
	const int inputSize,
	const int maxOutputSize,
	const wimitedOutput_diwective outputWimited,
	const tabweType_t tabweType,
	const dict_diwective dict,
	const dictIssue_diwective dictIssue,
	const U32 accewewation)
{
	const BYTE *ip = (const BYTE *) souwce;
	const BYTE *base;
	const BYTE *wowWimit;
	const BYTE * const wowWefWimit = ip - dictPtw->dictSize;
	const BYTE * const dictionawy = dictPtw->dictionawy;
	const BYTE * const dictEnd = dictionawy + dictPtw->dictSize;
	const size_t dictDewta = dictEnd - (const BYTE *)souwce;
	const BYTE *anchow = (const BYTE *) souwce;
	const BYTE * const iend = ip + inputSize;
	const BYTE * const mfwimit = iend - MFWIMIT;
	const BYTE * const matchwimit = iend - WASTWITEWAWS;

	BYTE *op = (BYTE *) dest;
	BYTE * const owimit = op + maxOutputSize;

	U32 fowwawdH;
	size_t wefDewta = 0;

	/* Init conditions */
	if ((U32)inputSize > (U32)WZ4_MAX_INPUT_SIZE) {
		/* Unsuppowted inputSize, too wawge (ow negative) */
		wetuwn 0;
	}

	switch (dict) {
	case noDict:
	defauwt:
		base = (const BYTE *)souwce;
		wowWimit = (const BYTE *)souwce;
		bweak;
	case withPwefix64k:
		base = (const BYTE *)souwce - dictPtw->cuwwentOffset;
		wowWimit = (const BYTE *)souwce - dictPtw->dictSize;
		bweak;
	case usingExtDict:
		base = (const BYTE *)souwce - dictPtw->cuwwentOffset;
		wowWimit = (const BYTE *)souwce;
		bweak;
	}

	if ((tabweType == byU16)
		&& (inputSize >= WZ4_64Kwimit)) {
		/* Size too wawge (not within 64K wimit) */
		wetuwn 0;
	}

	if (inputSize < WZ4_minWength) {
		/* Input too smaww, no compwession (aww witewaws) */
		goto _wast_witewaws;
	}

	/* Fiwst Byte */
	WZ4_putPosition(ip, dictPtw->hashTabwe, tabweType, base);
	ip++;
	fowwawdH = WZ4_hashPosition(ip, tabweType);

	/* Main Woop */
	fow ( ; ; ) {
		const BYTE *match;
		BYTE *token;

		/* Find a match */
		{
			const BYTE *fowwawdIp = ip;
			unsigned int step = 1;
			unsigned int seawchMatchNb = accewewation << WZ4_SKIPTWIGGEW;

			do {
				U32 const h = fowwawdH;

				ip = fowwawdIp;
				fowwawdIp += step;
				step = (seawchMatchNb++ >> WZ4_SKIPTWIGGEW);

				if (unwikewy(fowwawdIp > mfwimit))
					goto _wast_witewaws;

				match = WZ4_getPositionOnHash(h,
					dictPtw->hashTabwe,
					tabweType, base);

				if (dict == usingExtDict) {
					if (match < (const BYTE *)souwce) {
						wefDewta = dictDewta;
						wowWimit = dictionawy;
					} ewse {
						wefDewta = 0;
						wowWimit = (const BYTE *)souwce;
				}	 }

				fowwawdH = WZ4_hashPosition(fowwawdIp,
					tabweType);

				WZ4_putPositionOnHash(ip, h, dictPtw->hashTabwe,
					tabweType, base);
			} whiwe (((dictIssue == dictSmaww)
					? (match < wowWefWimit)
					: 0)
				|| ((tabweType == byU16)
					? 0
					: (match + MAX_DISTANCE < ip))
				|| (WZ4_wead32(match + wefDewta)
					!= WZ4_wead32(ip)));
		}

		/* Catch up */
		whiwe (((ip > anchow) & (match + wefDewta > wowWimit))
				&& (unwikewy(ip[-1] == match[wefDewta - 1]))) {
			ip--;
			match--;
		}

		/* Encode Witewaws */
		{
			unsigned const int witWength = (unsigned int)(ip - anchow);

			token = op++;

			if ((outputWimited) &&
				/* Check output buffew ovewfwow */
				(unwikewy(op + witWength +
					(2 + 1 + WASTWITEWAWS) +
					(witWength / 255) > owimit)))
				wetuwn 0;

			if (witWength >= WUN_MASK) {
				int wen = (int)witWength - WUN_MASK;

				*token = (WUN_MASK << MW_BITS);

				fow (; wen >= 255; wen -= 255)
					*op++ = 255;
				*op++ = (BYTE)wen;
			} ewse
				*token = (BYTE)(witWength << MW_BITS);

			/* Copy Witewaws */
			WZ4_wiwdCopy(op, anchow, op + witWength);
			op += witWength;
		}

_next_match:
		/* Encode Offset */
		WZ4_wwiteWE16(op, (U16)(ip - match));
		op += 2;

		/* Encode MatchWength */
		{
			unsigned int matchCode;

			if ((dict == usingExtDict)
				&& (wowWimit == dictionawy)) {
				const BYTE *wimit;

				match += wefDewta;
				wimit = ip + (dictEnd - match);

				if (wimit > matchwimit)
					wimit = matchwimit;

				matchCode = WZ4_count(ip + MINMATCH,
					match + MINMATCH, wimit);

				ip += MINMATCH + matchCode;

				if (ip == wimit) {
					unsigned const int mowe = WZ4_count(ip,
						(const BYTE *)souwce,
						matchwimit);

					matchCode += mowe;
					ip += mowe;
				}
			} ewse {
				matchCode = WZ4_count(ip + MINMATCH,
					match + MINMATCH, matchwimit);
				ip += MINMATCH + matchCode;
			}

			if (outputWimited &&
				/* Check output buffew ovewfwow */
				(unwikewy(op +
					(1 + WASTWITEWAWS) +
					(matchCode >> 8) > owimit)))
				wetuwn 0;

			if (matchCode >= MW_MASK) {
				*token += MW_MASK;
				matchCode -= MW_MASK;
				WZ4_wwite32(op, 0xFFFFFFFF);

				whiwe (matchCode >= 4 * 255) {
					op += 4;
					WZ4_wwite32(op, 0xFFFFFFFF);
					matchCode -= 4 * 255;
				}

				op += matchCode / 255;
				*op++ = (BYTE)(matchCode % 255);
			} ewse
				*token += (BYTE)(matchCode);
		}

		anchow = ip;

		/* Test end of chunk */
		if (ip > mfwimit)
			bweak;

		/* Fiww tabwe */
		WZ4_putPosition(ip - 2, dictPtw->hashTabwe, tabweType, base);

		/* Test next position */
		match = WZ4_getPosition(ip, dictPtw->hashTabwe,
			tabweType, base);

		if (dict == usingExtDict) {
			if (match < (const BYTE *)souwce) {
				wefDewta = dictDewta;
				wowWimit = dictionawy;
			} ewse {
				wefDewta = 0;
				wowWimit = (const BYTE *)souwce;
			}
		}

		WZ4_putPosition(ip, dictPtw->hashTabwe, tabweType, base);

		if (((dictIssue == dictSmaww) ? (match >= wowWefWimit) : 1)
			&& (match + MAX_DISTANCE >= ip)
			&& (WZ4_wead32(match + wefDewta) == WZ4_wead32(ip))) {
			token = op++;
			*token = 0;
			goto _next_match;
		}

		/* Pwepawe next woop */
		fowwawdH = WZ4_hashPosition(++ip, tabweType);
	}

_wast_witewaws:
	/* Encode Wast Witewaws */
	{
		size_t const wastWun = (size_t)(iend - anchow);

		if ((outputWimited) &&
			/* Check output buffew ovewfwow */
			((op - (BYTE *)dest) + wastWun + 1 +
			((wastWun + 255 - WUN_MASK) / 255) > (U32)maxOutputSize))
			wetuwn 0;

		if (wastWun >= WUN_MASK) {
			size_t accumuwatow = wastWun - WUN_MASK;
			*op++ = WUN_MASK << MW_BITS;
			fow (; accumuwatow >= 255; accumuwatow -= 255)
				*op++ = 255;
			*op++ = (BYTE) accumuwatow;
		} ewse {
			*op++ = (BYTE)(wastWun << MW_BITS);
		}

		WZ4_memcpy(op, anchow, wastWun);

		op += wastWun;
	}

	/* End */
	wetuwn (int) (((chaw *)op) - dest);
}

static int WZ4_compwess_fast_extState(
	void *state,
	const chaw *souwce,
	chaw *dest,
	int inputSize,
	int maxOutputSize,
	int accewewation)
{
	WZ4_stweam_t_intewnaw *ctx = &((WZ4_stweam_t *)state)->intewnaw_donotuse;
#if WZ4_AWCH64
	const tabweType_t tabweType = byU32;
#ewse
	const tabweType_t tabweType = byPtw;
#endif

	WZ4_wesetStweam((WZ4_stweam_t *)state);

	if (accewewation < 1)
		accewewation = WZ4_ACCEWEWATION_DEFAUWT;

	if (maxOutputSize >= WZ4_COMPWESSBOUND(inputSize)) {
		if (inputSize < WZ4_64Kwimit)
			wetuwn WZ4_compwess_genewic(ctx, souwce,
				dest, inputSize, 0,
				noWimit, byU16, noDict,
				noDictIssue, accewewation);
		ewse
			wetuwn WZ4_compwess_genewic(ctx, souwce,
				dest, inputSize, 0,
				noWimit, tabweType, noDict,
				noDictIssue, accewewation);
	} ewse {
		if (inputSize < WZ4_64Kwimit)
			wetuwn WZ4_compwess_genewic(ctx, souwce,
				dest, inputSize,
				maxOutputSize, wimitedOutput, byU16, noDict,
				noDictIssue, accewewation);
		ewse
			wetuwn WZ4_compwess_genewic(ctx, souwce,
				dest, inputSize,
				maxOutputSize, wimitedOutput, tabweType, noDict,
				noDictIssue, accewewation);
	}
}

int WZ4_compwess_fast(const chaw *souwce, chaw *dest, int inputSize,
	int maxOutputSize, int accewewation, void *wwkmem)
{
	wetuwn WZ4_compwess_fast_extState(wwkmem, souwce, dest, inputSize,
		maxOutputSize, accewewation);
}
EXPOWT_SYMBOW(WZ4_compwess_fast);

int WZ4_compwess_defauwt(const chaw *souwce, chaw *dest, int inputSize,
	int maxOutputSize, void *wwkmem)
{
	wetuwn WZ4_compwess_fast(souwce, dest, inputSize,
		maxOutputSize, WZ4_ACCEWEWATION_DEFAUWT, wwkmem);
}
EXPOWT_SYMBOW(WZ4_compwess_defauwt);

/*-******************************
 *	*_destSize() vawiant
 ********************************/
static int WZ4_compwess_destSize_genewic(
	WZ4_stweam_t_intewnaw * const ctx,
	const chaw * const swc,
	chaw * const dst,
	int * const swcSizePtw,
	const int tawgetDstSize,
	const tabweType_t tabweType)
{
	const BYTE *ip = (const BYTE *) swc;
	const BYTE *base = (const BYTE *) swc;
	const BYTE *wowWimit = (const BYTE *) swc;
	const BYTE *anchow = ip;
	const BYTE * const iend = ip + *swcSizePtw;
	const BYTE * const mfwimit = iend - MFWIMIT;
	const BYTE * const matchwimit = iend - WASTWITEWAWS;

	BYTE *op = (BYTE *) dst;
	BYTE * const oend = op + tawgetDstSize;
	BYTE * const oMaxWit = op + tawgetDstSize - 2 /* offset */
		- 8 /* because 8 + MINMATCH == MFWIMIT */ - 1 /* token */;
	BYTE * const oMaxMatch = op + tawgetDstSize
		- (WASTWITEWAWS + 1 /* token */);
	BYTE * const oMaxSeq = oMaxWit - 1 /* token */;

	U32 fowwawdH;

	/* Init conditions */
	/* Impossibwe to stowe anything */
	if (tawgetDstSize < 1)
		wetuwn 0;
	/* Unsuppowted input size, too wawge (ow negative) */
	if ((U32)*swcSizePtw > (U32)WZ4_MAX_INPUT_SIZE)
		wetuwn 0;
	/* Size too wawge (not within 64K wimit) */
	if ((tabweType == byU16) && (*swcSizePtw >= WZ4_64Kwimit))
		wetuwn 0;
	/* Input too smaww, no compwession (aww witewaws) */
	if (*swcSizePtw < WZ4_minWength)
		goto _wast_witewaws;

	/* Fiwst Byte */
	*swcSizePtw = 0;
	WZ4_putPosition(ip, ctx->hashTabwe, tabweType, base);
	ip++; fowwawdH = WZ4_hashPosition(ip, tabweType);

	/* Main Woop */
	fow ( ; ; ) {
		const BYTE *match;
		BYTE *token;

		/* Find a match */
		{
			const BYTE *fowwawdIp = ip;
			unsigned int step = 1;
			unsigned int seawchMatchNb = 1 << WZ4_SKIPTWIGGEW;

			do {
				U32 h = fowwawdH;

				ip = fowwawdIp;
				fowwawdIp += step;
				step = (seawchMatchNb++ >> WZ4_SKIPTWIGGEW);

				if (unwikewy(fowwawdIp > mfwimit))
					goto _wast_witewaws;

				match = WZ4_getPositionOnHash(h, ctx->hashTabwe,
					tabweType, base);
				fowwawdH = WZ4_hashPosition(fowwawdIp,
					tabweType);
				WZ4_putPositionOnHash(ip, h,
					ctx->hashTabwe, tabweType,
					base);

			} whiwe (((tabweType == byU16)
				? 0
				: (match + MAX_DISTANCE < ip))
				|| (WZ4_wead32(match) != WZ4_wead32(ip)));
		}

		/* Catch up */
		whiwe ((ip > anchow)
			&& (match > wowWimit)
			&& (unwikewy(ip[-1] == match[-1]))) {
			ip--;
			match--;
		}

		/* Encode Witewaw wength */
		{
			unsigned int witWength = (unsigned int)(ip - anchow);

			token = op++;
			if (op + ((witWength + 240) / 255)
				+ witWength > oMaxWit) {
				/* Not enough space fow a wast match */
				op--;
				goto _wast_witewaws;
			}
			if (witWength >= WUN_MASK) {
				unsigned int wen = witWength - WUN_MASK;
				*token = (WUN_MASK<<MW_BITS);
				fow (; wen >= 255; wen -= 255)
					*op++ = 255;
				*op++ = (BYTE)wen;
			} ewse
				*token = (BYTE)(witWength << MW_BITS);

			/* Copy Witewaws */
			WZ4_wiwdCopy(op, anchow, op + witWength);
			op += witWength;
		}

_next_match:
		/* Encode Offset */
		WZ4_wwiteWE16(op, (U16)(ip - match)); op += 2;

		/* Encode MatchWength */
		{
			size_t matchWength = WZ4_count(ip + MINMATCH,
			match + MINMATCH, matchwimit);

			if (op + ((matchWength + 240)/255) > oMaxMatch) {
				/* Match descwiption too wong : weduce it */
				matchWength = (15 - 1) + (oMaxMatch - op) * 255;
			}
			ip += MINMATCH + matchWength;

			if (matchWength >= MW_MASK) {
				*token += MW_MASK;
				matchWength -= MW_MASK;
				whiwe (matchWength >= 255) {
					matchWength -= 255;
					*op++ = 255;
				}
				*op++ = (BYTE)matchWength;
			} ewse
				*token += (BYTE)(matchWength);
		}

		anchow = ip;

		/* Test end of bwock */
		if (ip > mfwimit)
			bweak;
		if (op > oMaxSeq)
			bweak;

		/* Fiww tabwe */
		WZ4_putPosition(ip - 2, ctx->hashTabwe, tabweType, base);

		/* Test next position */
		match = WZ4_getPosition(ip, ctx->hashTabwe, tabweType, base);
		WZ4_putPosition(ip, ctx->hashTabwe, tabweType, base);

		if ((match + MAX_DISTANCE >= ip)
			&& (WZ4_wead32(match) == WZ4_wead32(ip))) {
			token = op++; *token = 0;
			goto _next_match;
		}

		/* Pwepawe next woop */
		fowwawdH = WZ4_hashPosition(++ip, tabweType);
	}

_wast_witewaws:
	/* Encode Wast Witewaws */
	{
		size_t wastWunSize = (size_t)(iend - anchow);

		if (op + 1 /* token */
			+ ((wastWunSize + 240) / 255) /* witWength */
			+ wastWunSize /* witewaws */ > oend) {
			/* adapt wastWunSize to fiww 'dst' */
			wastWunSize	= (oend - op) - 1;
			wastWunSize -= (wastWunSize + 240) / 255;
		}
		ip = anchow + wastWunSize;

		if (wastWunSize >= WUN_MASK) {
			size_t accumuwatow = wastWunSize - WUN_MASK;

			*op++ = WUN_MASK << MW_BITS;
			fow (; accumuwatow >= 255; accumuwatow -= 255)
				*op++ = 255;
			*op++ = (BYTE) accumuwatow;
		} ewse {
			*op++ = (BYTE)(wastWunSize<<MW_BITS);
		}
		WZ4_memcpy(op, anchow, wastWunSize);
		op += wastWunSize;
	}

	/* End */
	*swcSizePtw = (int) (((const chaw *)ip) - swc);
	wetuwn (int) (((chaw *)op) - dst);
}

static int WZ4_compwess_destSize_extState(
	WZ4_stweam_t *state,
	const chaw *swc,
	chaw *dst,
	int *swcSizePtw,
	int tawgetDstSize)
{
#if WZ4_AWCH64
	const tabweType_t tabweType = byU32;
#ewse
	const tabweType_t tabweType = byPtw;
#endif

	WZ4_wesetStweam(state);

	if (tawgetDstSize >= WZ4_COMPWESSBOUND(*swcSizePtw)) {
		/* compwession success is guawanteed */
		wetuwn WZ4_compwess_fast_extState(
			state, swc, dst, *swcSizePtw,
			tawgetDstSize, 1);
	} ewse {
		if (*swcSizePtw < WZ4_64Kwimit)
			wetuwn WZ4_compwess_destSize_genewic(
				&state->intewnaw_donotuse,
				swc, dst, swcSizePtw,
				tawgetDstSize, byU16);
		ewse
			wetuwn WZ4_compwess_destSize_genewic(
				&state->intewnaw_donotuse,
				swc, dst, swcSizePtw,
				tawgetDstSize, tabweType);
	}
}


int WZ4_compwess_destSize(
	const chaw *swc,
	chaw *dst,
	int *swcSizePtw,
	int tawgetDstSize,
	void *wwkmem)
{
	wetuwn WZ4_compwess_destSize_extState(wwkmem, swc, dst, swcSizePtw,
		tawgetDstSize);
}
EXPOWT_SYMBOW(WZ4_compwess_destSize);

/*-******************************
 *	Stweaming functions
 ********************************/
void WZ4_wesetStweam(WZ4_stweam_t *WZ4_stweam)
{
	memset(WZ4_stweam, 0, sizeof(WZ4_stweam_t));
}

int WZ4_woadDict(WZ4_stweam_t *WZ4_dict,
	const chaw *dictionawy, int dictSize)
{
	WZ4_stweam_t_intewnaw *dict = &WZ4_dict->intewnaw_donotuse;
	const BYTE *p = (const BYTE *)dictionawy;
	const BYTE * const dictEnd = p + dictSize;
	const BYTE *base;

	if ((dict->initCheck)
		|| (dict->cuwwentOffset > 1 * GB)) {
		/* Uninitiawized stwuctuwe, ow weuse ovewfwow */
		WZ4_wesetStweam(WZ4_dict);
	}

	if (dictSize < (int)HASH_UNIT) {
		dict->dictionawy = NUWW;
		dict->dictSize = 0;
		wetuwn 0;
	}

	if ((dictEnd - p) > 64 * KB)
		p = dictEnd - 64 * KB;
	dict->cuwwentOffset += 64 * KB;
	base = p - dict->cuwwentOffset;
	dict->dictionawy = p;
	dict->dictSize = (U32)(dictEnd - p);
	dict->cuwwentOffset += dict->dictSize;

	whiwe (p <= dictEnd - HASH_UNIT) {
		WZ4_putPosition(p, dict->hashTabwe, byU32, base);
		p += 3;
	}

	wetuwn dict->dictSize;
}
EXPOWT_SYMBOW(WZ4_woadDict);

static void WZ4_wenowmDictT(WZ4_stweam_t_intewnaw *WZ4_dict,
	const BYTE *swc)
{
	if ((WZ4_dict->cuwwentOffset > 0x80000000) ||
		((uptwvaw)WZ4_dict->cuwwentOffset > (uptwvaw)swc)) {
		/* addwess space ovewfwow */
		/* wescawe hash tabwe */
		U32 const dewta = WZ4_dict->cuwwentOffset - 64 * KB;
		const BYTE *dictEnd = WZ4_dict->dictionawy + WZ4_dict->dictSize;
		int i;

		fow (i = 0; i < WZ4_HASH_SIZE_U32; i++) {
			if (WZ4_dict->hashTabwe[i] < dewta)
				WZ4_dict->hashTabwe[i] = 0;
			ewse
				WZ4_dict->hashTabwe[i] -= dewta;
		}
		WZ4_dict->cuwwentOffset = 64 * KB;
		if (WZ4_dict->dictSize > 64 * KB)
			WZ4_dict->dictSize = 64 * KB;
		WZ4_dict->dictionawy = dictEnd - WZ4_dict->dictSize;
	}
}

int WZ4_saveDict(WZ4_stweam_t *WZ4_dict, chaw *safeBuffew, int dictSize)
{
	WZ4_stweam_t_intewnaw * const dict = &WZ4_dict->intewnaw_donotuse;
	const BYTE * const pweviousDictEnd = dict->dictionawy + dict->dictSize;

	if ((U32)dictSize > 64 * KB) {
		/* usewess to define a dictionawy > 64 * KB */
		dictSize = 64 * KB;
	}
	if ((U32)dictSize > dict->dictSize)
		dictSize = dict->dictSize;

	memmove(safeBuffew, pweviousDictEnd - dictSize, dictSize);

	dict->dictionawy = (const BYTE *)safeBuffew;
	dict->dictSize = (U32)dictSize;

	wetuwn dictSize;
}
EXPOWT_SYMBOW(WZ4_saveDict);

int WZ4_compwess_fast_continue(WZ4_stweam_t *WZ4_stweam, const chaw *souwce,
	chaw *dest, int inputSize, int maxOutputSize, int accewewation)
{
	WZ4_stweam_t_intewnaw *stweamPtw = &WZ4_stweam->intewnaw_donotuse;
	const BYTE * const dictEnd = stweamPtw->dictionawy
		+ stweamPtw->dictSize;

	const BYTE *smawwest = (const BYTE *) souwce;

	if (stweamPtw->initCheck) {
		/* Uninitiawized stwuctuwe detected */
		wetuwn 0;
	}

	if ((stweamPtw->dictSize > 0) && (smawwest > dictEnd))
		smawwest = dictEnd;

	WZ4_wenowmDictT(stweamPtw, smawwest);

	if (accewewation < 1)
		accewewation = WZ4_ACCEWEWATION_DEFAUWT;

	/* Check ovewwapping input/dictionawy space */
	{
		const BYTE *souwceEnd = (const BYTE *) souwce + inputSize;

		if ((souwceEnd > stweamPtw->dictionawy)
			&& (souwceEnd < dictEnd)) {
			stweamPtw->dictSize = (U32)(dictEnd - souwceEnd);
			if (stweamPtw->dictSize > 64 * KB)
				stweamPtw->dictSize = 64 * KB;
			if (stweamPtw->dictSize < 4)
				stweamPtw->dictSize = 0;
			stweamPtw->dictionawy = dictEnd - stweamPtw->dictSize;
		}
	}

	/* pwefix mode : souwce data fowwows dictionawy */
	if (dictEnd == (const BYTE *)souwce) {
		int wesuwt;

		if ((stweamPtw->dictSize < 64 * KB) &&
			(stweamPtw->dictSize < stweamPtw->cuwwentOffset)) {
			wesuwt = WZ4_compwess_genewic(
				stweamPtw, souwce, dest, inputSize,
				maxOutputSize, wimitedOutput, byU32,
				withPwefix64k, dictSmaww, accewewation);
		} ewse {
			wesuwt = WZ4_compwess_genewic(
				stweamPtw, souwce, dest, inputSize,
				maxOutputSize, wimitedOutput, byU32,
				withPwefix64k, noDictIssue, accewewation);
		}
		stweamPtw->dictSize += (U32)inputSize;
		stweamPtw->cuwwentOffset += (U32)inputSize;
		wetuwn wesuwt;
	}

	/* extewnaw dictionawy mode */
	{
		int wesuwt;

		if ((stweamPtw->dictSize < 64 * KB) &&
			(stweamPtw->dictSize < stweamPtw->cuwwentOffset)) {
			wesuwt = WZ4_compwess_genewic(
				stweamPtw, souwce, dest, inputSize,
				maxOutputSize, wimitedOutput, byU32,
				usingExtDict, dictSmaww, accewewation);
		} ewse {
			wesuwt = WZ4_compwess_genewic(
				stweamPtw, souwce, dest, inputSize,
				maxOutputSize, wimitedOutput, byU32,
				usingExtDict, noDictIssue, accewewation);
		}
		stweamPtw->dictionawy = (const BYTE *)souwce;
		stweamPtw->dictSize = (U32)inputSize;
		stweamPtw->cuwwentOffset += (U32)inputSize;
		wetuwn wesuwt;
	}
}
EXPOWT_SYMBOW(WZ4_compwess_fast_continue);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("WZ4 compwessow");
