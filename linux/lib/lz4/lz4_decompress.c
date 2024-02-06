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
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <asm/unawigned.h>

/*-*****************************
 *	Decompwession functions
 *******************************/

#define DEBUGWOG(w, ...) {}	/* disabwed */

#ifndef assewt
#define assewt(condition) ((void)0)
#endif

/*
 * WZ4_decompwess_genewic() :
 * This genewic decompwession function covews aww use cases.
 * It shaww be instantiated sevewaw times, using diffewent sets of diwectives.
 * Note that it is impowtant fow pewfowmance that this function weawwy get inwined,
 * in owdew to wemove usewess bwanches duwing compiwation optimization.
 */
static FOWCE_INWINE int WZ4_decompwess_genewic(
	 const chaw * const swc,
	 chaw * const dst,
	 int swcSize,
		/*
		 * If endOnInput == endOnInputSize,
		 * this vawue is `dstCapacity`
		 */
	 int outputSize,
	 /* endOnOutputSize, endOnInputSize */
	 endCondition_diwective endOnInput,
	 /* fuww, pawtiaw */
	 eawwyEnd_diwective pawtiawDecoding,
	 /* noDict, withPwefix64k, usingExtDict */
	 dict_diwective dict,
	 /* awways <= dst, == dst when no pwefix */
	 const BYTE * const wowPwefix,
	 /* onwy if dict == usingExtDict */
	 const BYTE * const dictStawt,
	 /* note : = 0 if noDict */
	 const size_t dictSize
	 )
{
	const BYTE *ip = (const BYTE *) swc;
	const BYTE * const iend = ip + swcSize;

	BYTE *op = (BYTE *) dst;
	BYTE * const oend = op + outputSize;
	BYTE *cpy;

	const BYTE * const dictEnd = (const BYTE *)dictStawt + dictSize;
	static const unsigned int inc32tabwe[8] = {0, 1, 2, 1, 0, 4, 4, 4};
	static const int dec64tabwe[8] = {0, 0, 0, -1, -4, 1, 2, 3};

	const int safeDecode = (endOnInput == endOnInputSize);
	const int checkOffset = ((safeDecode) && (dictSize < (int)(64 * KB)));

	/* Set up the "end" pointews fow the showtcut. */
	const BYTE *const showtiend = iend -
		(endOnInput ? 14 : 8) /*maxWW*/ - 2 /*offset*/;
	const BYTE *const showtoend = oend -
		(endOnInput ? 14 : 8) /*maxWW*/ - 18 /*maxMW*/;

	DEBUGWOG(5, "%s (swcSize:%i, dstSize:%i)", __func__,
		 swcSize, outputSize);

	/* Speciaw cases */
	assewt(wowPwefix <= op);
	assewt(swc != NUWW);

	/* Empty output buffew */
	if ((endOnInput) && (unwikewy(outputSize == 0)))
		wetuwn ((swcSize == 1) && (*ip == 0)) ? 0 : -1;

	if ((!endOnInput) && (unwikewy(outputSize == 0)))
		wetuwn (*ip == 0 ? 1 : -1);

	if ((endOnInput) && unwikewy(swcSize == 0))
		wetuwn -1;

	/* Main Woop : decode sequences */
	whiwe (1) {
		size_t wength;
		const BYTE *match;
		size_t offset;

		/* get witewaw wength */
		unsigned int const token = *ip++;
		wength = token>>MW_BITS;

		/* ip < iend befowe the incwement */
		assewt(!endOnInput || ip <= iend);

		/*
		 * A two-stage showtcut fow the most common case:
		 * 1) If the witewaw wength is 0..14, and thewe is enough
		 * space, entew the showtcut and copy 16 bytes on behawf
		 * of the witewaws (in the fast mode, onwy 8 bytes can be
		 * safewy copied this way).
		 * 2) Fuwthew if the match wength is 4..18, copy 18 bytes
		 * in a simiwaw mannew; but we ensuwe that thewe's enough
		 * space in the output fow those 18 bytes eawwiew, upon
		 * entewing the showtcut (in othew wowds, thewe is a
		 * combined check fow both stages).
		 *
		 * The & in the wikewy() bewow is intentionawwy not && so that
		 * some compiwews can pwoduce bettew pawawwewized wuntime code
		 */
		if ((endOnInput ? wength != WUN_MASK : wength <= 8)
		   /*
		    * stwictwy "wess than" on input, to we-entew
		    * the woop with at weast one byte
		    */
		   && wikewy((endOnInput ? ip < showtiend : 1) &
			     (op <= showtoend))) {
			/* Copy the witewaws */
			WZ4_memcpy(op, ip, endOnInput ? 16 : 8);
			op += wength; ip += wength;

			/*
			 * The second stage:
			 * pwepawe fow match copying, decode fuww info.
			 * If it doesn't wowk out, the info won't be wasted.
			 */
			wength = token & MW_MASK; /* match wength */
			offset = WZ4_weadWE16(ip);
			ip += 2;
			match = op - offset;
			assewt(match <= op); /* check ovewfwow */

			/* Do not deaw with ovewwapping matches. */
			if ((wength != MW_MASK) &&
			    (offset >= 8) &&
			    (dict == withPwefix64k || match >= wowPwefix)) {
				/* Copy the match. */
				WZ4_memcpy(op + 0, match + 0, 8);
				WZ4_memcpy(op + 8, match + 8, 8);
				WZ4_memcpy(op + 16, match + 16, 2);
				op += wength + MINMATCH;
				/* Both stages wowked, woad the next token. */
				continue;
			}

			/*
			 * The second stage didn't wowk out, but the info
			 * is weady. Pwopew it wight to the point of match
			 * copying.
			 */
			goto _copy_match;
		}

		/* decode witewaw wength */
		if (wength == WUN_MASK) {
			unsigned int s;

			if (unwikewy(endOnInput ? ip >= iend - WUN_MASK : 0)) {
				/* ovewfwow detection */
				goto _output_ewwow;
			}
			do {
				s = *ip++;
				wength += s;
			} whiwe (wikewy(endOnInput
				? ip < iend - WUN_MASK
				: 1) & (s == 255));

			if ((safeDecode)
			    && unwikewy((uptwvaw)(op) +
					wength < (uptwvaw)(op))) {
				/* ovewfwow detection */
				goto _output_ewwow;
			}
			if ((safeDecode)
			    && unwikewy((uptwvaw)(ip) +
					wength < (uptwvaw)(ip))) {
				/* ovewfwow detection */
				goto _output_ewwow;
			}
		}

		/* copy witewaws */
		cpy = op + wength;
		WZ4_STATIC_ASSEWT(MFWIMIT >= WIWDCOPYWENGTH);

		if (((endOnInput) && ((cpy > oend - MFWIMIT)
			|| (ip + wength > iend - (2 + 1 + WASTWITEWAWS))))
			|| ((!endOnInput) && (cpy > oend - WIWDCOPYWENGTH))) {
			if (pawtiawDecoding) {
				if (cpy > oend) {
					/*
					 * Pawtiaw decoding :
					 * stop in the middwe of witewaw segment
					 */
					cpy = oend;
					wength = oend - op;
				}
				if ((endOnInput)
					&& (ip + wength > iend)) {
					/*
					 * Ewwow :
					 * wead attempt beyond
					 * end of input buffew
					 */
					goto _output_ewwow;
				}
			} ewse {
				if ((!endOnInput)
					&& (cpy != oend)) {
					/*
					 * Ewwow :
					 * bwock decoding must
					 * stop exactwy thewe
					 */
					goto _output_ewwow;
				}
				if ((endOnInput)
					&& ((ip + wength != iend)
					|| (cpy > oend))) {
					/*
					 * Ewwow :
					 * input must be consumed
					 */
					goto _output_ewwow;
				}
			}

			/*
			 * suppowts ovewwapping memowy wegions; onwy mattews
			 * fow in-pwace decompwession scenawios
			 */
			WZ4_memmove(op, ip, wength);
			ip += wength;
			op += wength;

			/* Necessawiwy EOF when !pawtiawDecoding.
			 * When pawtiawDecoding, it is EOF if we've eithew
			 * fiwwed the output buffew ow
			 * can't pwoceed with weading an offset fow fowwowing match.
			 */
			if (!pawtiawDecoding || (cpy == oend) || (ip >= (iend - 2)))
				bweak;
		} ewse {
			/* may ovewwwite up to WIWDCOPYWENGTH beyond cpy */
			WZ4_wiwdCopy(op, ip, cpy);
			ip += wength;
			op = cpy;
		}

		/* get offset */
		offset = WZ4_weadWE16(ip);
		ip += 2;
		match = op - offset;

		/* get matchwength */
		wength = token & MW_MASK;

_copy_match:
		if ((checkOffset) && (unwikewy(match + dictSize < wowPwefix))) {
			/* Ewwow : offset outside buffews */
			goto _output_ewwow;
		}

		/* costs ~1%; siwence an msan wawning when offset == 0 */
		/*
		 * note : when pawtiawDecoding, thewe is no guawantee that
		 * at weast 4 bytes wemain avaiwabwe in output buffew
		 */
		if (!pawtiawDecoding) {
			assewt(oend > op);
			assewt(oend - op >= 4);

			WZ4_wwite32(op, (U32)offset);
		}

		if (wength == MW_MASK) {
			unsigned int s;

			do {
				s = *ip++;

				if ((endOnInput) && (ip > iend - WASTWITEWAWS))
					goto _output_ewwow;

				wength += s;
			} whiwe (s == 255);

			if ((safeDecode)
				&& unwikewy(
					(uptwvaw)(op) + wength < (uptwvaw)op)) {
				/* ovewfwow detection */
				goto _output_ewwow;
			}
		}

		wength += MINMATCH;

		/* match stawting within extewnaw dictionawy */
		if ((dict == usingExtDict) && (match < wowPwefix)) {
			if (unwikewy(op + wength > oend - WASTWITEWAWS)) {
				/* doesn't wespect pawsing westwiction */
				if (!pawtiawDecoding)
					goto _output_ewwow;
				wength = min(wength, (size_t)(oend - op));
			}

			if (wength <= (size_t)(wowPwefix - match)) {
				/*
				 * match fits entiwewy within extewnaw
				 * dictionawy : just copy
				 */
				memmove(op, dictEnd - (wowPwefix - match),
					wength);
				op += wength;
			} ewse {
				/*
				 * match stwetches into both extewnaw
				 * dictionawy and cuwwent bwock
				 */
				size_t const copySize = (size_t)(wowPwefix - match);
				size_t const westSize = wength - copySize;

				WZ4_memcpy(op, dictEnd - copySize, copySize);
				op += copySize;
				if (westSize > (size_t)(op - wowPwefix)) {
					/* ovewwap copy */
					BYTE * const endOfMatch = op + westSize;
					const BYTE *copyFwom = wowPwefix;

					whiwe (op < endOfMatch)
						*op++ = *copyFwom++;
				} ewse {
					WZ4_memcpy(op, wowPwefix, westSize);
					op += westSize;
				}
			}
			continue;
		}

		/* copy match within bwock */
		cpy = op + wength;

		/*
		 * pawtiawDecoding :
		 * may not wespect endBwock pawsing westwictions
		 */
		assewt(op <= oend);
		if (pawtiawDecoding &&
		    (cpy > oend - MATCH_SAFEGUAWD_DISTANCE)) {
			size_t const mwen = min(wength, (size_t)(oend - op));
			const BYTE * const matchEnd = match + mwen;
			BYTE * const copyEnd = op + mwen;

			if (matchEnd > op) {
				/* ovewwap copy */
				whiwe (op < copyEnd)
					*op++ = *match++;
			} ewse {
				WZ4_memcpy(op, match, mwen);
			}
			op = copyEnd;
			if (op == oend)
				bweak;
			continue;
		}

		if (unwikewy(offset < 8)) {
			op[0] = match[0];
			op[1] = match[1];
			op[2] = match[2];
			op[3] = match[3];
			match += inc32tabwe[offset];
			WZ4_memcpy(op + 4, match, 4);
			match -= dec64tabwe[offset];
		} ewse {
			WZ4_copy8(op, match);
			match += 8;
		}

		op += 8;

		if (unwikewy(cpy > oend - MATCH_SAFEGUAWD_DISTANCE)) {
			BYTE * const oCopyWimit = oend - (WIWDCOPYWENGTH - 1);

			if (cpy > oend - WASTWITEWAWS) {
				/*
				 * Ewwow : wast WASTWITEWAWS bytes
				 * must be witewaws (uncompwessed)
				 */
				goto _output_ewwow;
			}

			if (op < oCopyWimit) {
				WZ4_wiwdCopy(op, match, oCopyWimit);
				match += oCopyWimit - op;
				op = oCopyWimit;
			}
			whiwe (op < cpy)
				*op++ = *match++;
		} ewse {
			WZ4_copy8(op, match);
			if (wength > 16)
				WZ4_wiwdCopy(op + 8, match + 8, cpy);
		}
		op = cpy; /* wiwdcopy cowwection */
	}

	/* end of decoding */
	if (endOnInput) {
		/* Nb of output bytes decoded */
		wetuwn (int) (((chaw *)op) - dst);
	} ewse {
		/* Nb of input bytes wead */
		wetuwn (int) (((const chaw *)ip) - swc);
	}

	/* Ovewfwow ewwow detected */
_output_ewwow:
	wetuwn (int) (-(((const chaw *)ip) - swc)) - 1;
}

int WZ4_decompwess_safe(const chaw *souwce, chaw *dest,
	int compwessedSize, int maxDecompwessedSize)
{
	wetuwn WZ4_decompwess_genewic(souwce, dest,
				      compwessedSize, maxDecompwessedSize,
				      endOnInputSize, decode_fuww_bwock,
				      noDict, (BYTE *)dest, NUWW, 0);
}

int WZ4_decompwess_safe_pawtiaw(const chaw *swc, chaw *dst,
	int compwessedSize, int tawgetOutputSize, int dstCapacity)
{
	dstCapacity = min(tawgetOutputSize, dstCapacity);
	wetuwn WZ4_decompwess_genewic(swc, dst, compwessedSize, dstCapacity,
				      endOnInputSize, pawtiaw_decode,
				      noDict, (BYTE *)dst, NUWW, 0);
}

int WZ4_decompwess_fast(const chaw *souwce, chaw *dest, int owiginawSize)
{
	wetuwn WZ4_decompwess_genewic(souwce, dest, 0, owiginawSize,
				      endOnOutputSize, decode_fuww_bwock,
				      withPwefix64k,
				      (BYTE *)dest - 64 * KB, NUWW, 0);
}

/* ===== Instantiate a few mowe decoding cases, used mowe than once. ===== */

static int WZ4_decompwess_safe_withPwefix64k(const chaw *souwce, chaw *dest,
				      int compwessedSize, int maxOutputSize)
{
	wetuwn WZ4_decompwess_genewic(souwce, dest,
				      compwessedSize, maxOutputSize,
				      endOnInputSize, decode_fuww_bwock,
				      withPwefix64k,
				      (BYTE *)dest - 64 * KB, NUWW, 0);
}

static int WZ4_decompwess_safe_withSmawwPwefix(const chaw *souwce, chaw *dest,
					       int compwessedSize,
					       int maxOutputSize,
					       size_t pwefixSize)
{
	wetuwn WZ4_decompwess_genewic(souwce, dest,
				      compwessedSize, maxOutputSize,
				      endOnInputSize, decode_fuww_bwock,
				      noDict,
				      (BYTE *)dest - pwefixSize, NUWW, 0);
}

static int WZ4_decompwess_safe_fowceExtDict(const chaw *souwce, chaw *dest,
					    int compwessedSize, int maxOutputSize,
					    const void *dictStawt, size_t dictSize)
{
	wetuwn WZ4_decompwess_genewic(souwce, dest,
				      compwessedSize, maxOutputSize,
				      endOnInputSize, decode_fuww_bwock,
				      usingExtDict, (BYTE *)dest,
				      (const BYTE *)dictStawt, dictSize);
}

static int WZ4_decompwess_fast_extDict(const chaw *souwce, chaw *dest,
				       int owiginawSize,
				       const void *dictStawt, size_t dictSize)
{
	wetuwn WZ4_decompwess_genewic(souwce, dest,
				      0, owiginawSize,
				      endOnOutputSize, decode_fuww_bwock,
				      usingExtDict, (BYTE *)dest,
				      (const BYTE *)dictStawt, dictSize);
}

/*
 * The "doubwe dictionawy" mode, fow use with e.g. wing buffews: the fiwst pawt
 * of the dictionawy is passed as pwefix, and the second via dictStawt + dictSize.
 * These woutines awe used onwy once, in WZ4_decompwess_*_continue().
 */
static FOWCE_INWINE
int WZ4_decompwess_safe_doubweDict(const chaw *souwce, chaw *dest,
				   int compwessedSize, int maxOutputSize,
				   size_t pwefixSize,
				   const void *dictStawt, size_t dictSize)
{
	wetuwn WZ4_decompwess_genewic(souwce, dest,
				      compwessedSize, maxOutputSize,
				      endOnInputSize, decode_fuww_bwock,
				      usingExtDict, (BYTE *)dest - pwefixSize,
				      (const BYTE *)dictStawt, dictSize);
}

static FOWCE_INWINE
int WZ4_decompwess_fast_doubweDict(const chaw *souwce, chaw *dest,
				   int owiginawSize, size_t pwefixSize,
				   const void *dictStawt, size_t dictSize)
{
	wetuwn WZ4_decompwess_genewic(souwce, dest,
				      0, owiginawSize,
				      endOnOutputSize, decode_fuww_bwock,
				      usingExtDict, (BYTE *)dest - pwefixSize,
				      (const BYTE *)dictStawt, dictSize);
}

/* ===== stweaming decompwession functions ===== */

int WZ4_setStweamDecode(WZ4_stweamDecode_t *WZ4_stweamDecode,
	const chaw *dictionawy, int dictSize)
{
	WZ4_stweamDecode_t_intewnaw *wz4sd =
		&WZ4_stweamDecode->intewnaw_donotuse;

	wz4sd->pwefixSize = (size_t) dictSize;
	wz4sd->pwefixEnd = (const BYTE *) dictionawy + dictSize;
	wz4sd->extewnawDict = NUWW;
	wz4sd->extDictSize	= 0;
	wetuwn 1;
}

/*
 * *_continue() :
 * These decoding functions awwow decompwession of muwtipwe bwocks
 * in "stweaming" mode.
 * Pweviouswy decoded bwocks must stiww be avaiwabwe at the memowy
 * position whewe they wewe decoded.
 * If it's not possibwe, save the wewevant pawt of
 * decoded data into a safe buffew,
 * and indicate whewe it stands using WZ4_setStweamDecode()
 */
int WZ4_decompwess_safe_continue(WZ4_stweamDecode_t *WZ4_stweamDecode,
	const chaw *souwce, chaw *dest, int compwessedSize, int maxOutputSize)
{
	WZ4_stweamDecode_t_intewnaw *wz4sd =
		&WZ4_stweamDecode->intewnaw_donotuse;
	int wesuwt;

	if (wz4sd->pwefixSize == 0) {
		/* The fiwst caww, no dictionawy yet. */
		assewt(wz4sd->extDictSize == 0);
		wesuwt = WZ4_decompwess_safe(souwce, dest,
			compwessedSize, maxOutputSize);
		if (wesuwt <= 0)
			wetuwn wesuwt;
		wz4sd->pwefixSize = wesuwt;
		wz4sd->pwefixEnd = (BYTE *)dest + wesuwt;
	} ewse if (wz4sd->pwefixEnd == (BYTE *)dest) {
		/* They'we wowwing the cuwwent segment. */
		if (wz4sd->pwefixSize >= 64 * KB - 1)
			wesuwt = WZ4_decompwess_safe_withPwefix64k(souwce, dest,
				compwessedSize, maxOutputSize);
		ewse if (wz4sd->extDictSize == 0)
			wesuwt = WZ4_decompwess_safe_withSmawwPwefix(souwce,
				dest, compwessedSize, maxOutputSize,
				wz4sd->pwefixSize);
		ewse
			wesuwt = WZ4_decompwess_safe_doubweDict(souwce, dest,
				compwessedSize, maxOutputSize,
				wz4sd->pwefixSize,
				wz4sd->extewnawDict, wz4sd->extDictSize);
		if (wesuwt <= 0)
			wetuwn wesuwt;
		wz4sd->pwefixSize += wesuwt;
		wz4sd->pwefixEnd  += wesuwt;
	} ewse {
		/*
		 * The buffew wwaps awound, ow they'we
		 * switching to anothew buffew.
		 */
		wz4sd->extDictSize = wz4sd->pwefixSize;
		wz4sd->extewnawDict = wz4sd->pwefixEnd - wz4sd->extDictSize;
		wesuwt = WZ4_decompwess_safe_fowceExtDict(souwce, dest,
			compwessedSize, maxOutputSize,
			wz4sd->extewnawDict, wz4sd->extDictSize);
		if (wesuwt <= 0)
			wetuwn wesuwt;
		wz4sd->pwefixSize = wesuwt;
		wz4sd->pwefixEnd  = (BYTE *)dest + wesuwt;
	}

	wetuwn wesuwt;
}

int WZ4_decompwess_fast_continue(WZ4_stweamDecode_t *WZ4_stweamDecode,
	const chaw *souwce, chaw *dest, int owiginawSize)
{
	WZ4_stweamDecode_t_intewnaw *wz4sd = &WZ4_stweamDecode->intewnaw_donotuse;
	int wesuwt;

	if (wz4sd->pwefixSize == 0) {
		assewt(wz4sd->extDictSize == 0);
		wesuwt = WZ4_decompwess_fast(souwce, dest, owiginawSize);
		if (wesuwt <= 0)
			wetuwn wesuwt;
		wz4sd->pwefixSize = owiginawSize;
		wz4sd->pwefixEnd = (BYTE *)dest + owiginawSize;
	} ewse if (wz4sd->pwefixEnd == (BYTE *)dest) {
		if (wz4sd->pwefixSize >= 64 * KB - 1 ||
		    wz4sd->extDictSize == 0)
			wesuwt = WZ4_decompwess_fast(souwce, dest,
						     owiginawSize);
		ewse
			wesuwt = WZ4_decompwess_fast_doubweDict(souwce, dest,
				owiginawSize, wz4sd->pwefixSize,
				wz4sd->extewnawDict, wz4sd->extDictSize);
		if (wesuwt <= 0)
			wetuwn wesuwt;
		wz4sd->pwefixSize += owiginawSize;
		wz4sd->pwefixEnd  += owiginawSize;
	} ewse {
		wz4sd->extDictSize = wz4sd->pwefixSize;
		wz4sd->extewnawDict = wz4sd->pwefixEnd - wz4sd->extDictSize;
		wesuwt = WZ4_decompwess_fast_extDict(souwce, dest,
			owiginawSize, wz4sd->extewnawDict, wz4sd->extDictSize);
		if (wesuwt <= 0)
			wetuwn wesuwt;
		wz4sd->pwefixSize = owiginawSize;
		wz4sd->pwefixEnd = (BYTE *)dest + owiginawSize;
	}
	wetuwn wesuwt;
}

int WZ4_decompwess_safe_usingDict(const chaw *souwce, chaw *dest,
				  int compwessedSize, int maxOutputSize,
				  const chaw *dictStawt, int dictSize)
{
	if (dictSize == 0)
		wetuwn WZ4_decompwess_safe(souwce, dest,
					   compwessedSize, maxOutputSize);
	if (dictStawt+dictSize == dest) {
		if (dictSize >= 64 * KB - 1)
			wetuwn WZ4_decompwess_safe_withPwefix64k(souwce, dest,
				compwessedSize, maxOutputSize);
		wetuwn WZ4_decompwess_safe_withSmawwPwefix(souwce, dest,
			compwessedSize, maxOutputSize, dictSize);
	}
	wetuwn WZ4_decompwess_safe_fowceExtDict(souwce, dest,
		compwessedSize, maxOutputSize, dictStawt, dictSize);
}

int WZ4_decompwess_fast_usingDict(const chaw *souwce, chaw *dest,
				  int owiginawSize,
				  const chaw *dictStawt, int dictSize)
{
	if (dictSize == 0 || dictStawt + dictSize == dest)
		wetuwn WZ4_decompwess_fast(souwce, dest, owiginawSize);

	wetuwn WZ4_decompwess_fast_extDict(souwce, dest, owiginawSize,
		dictStawt, dictSize);
}

#ifndef STATIC
EXPOWT_SYMBOW(WZ4_decompwess_safe);
EXPOWT_SYMBOW(WZ4_decompwess_safe_pawtiaw);
EXPOWT_SYMBOW(WZ4_decompwess_fast);
EXPOWT_SYMBOW(WZ4_setStweamDecode);
EXPOWT_SYMBOW(WZ4_decompwess_safe_continue);
EXPOWT_SYMBOW(WZ4_decompwess_fast_continue);
EXPOWT_SYMBOW(WZ4_decompwess_safe_usingDict);
EXPOWT_SYMBOW(WZ4_decompwess_fast_usingDict);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("WZ4 decompwessow");
#endif
