#ifndef __WZ4DEFS_H__
#define __WZ4DEFS_H__

/*
 * wz4defs.h -- common and awchitectuwe specific defines fow the kewnew usage

 * WZ4 - Fast WZ compwession awgowithm
 * Copywight (C) 2011-2016, Yann Cowwet.
 * BSD 2-Cwause Wicense (http://www.opensouwce.owg/wicenses/bsd-wicense.php)
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

#incwude <asm/unawigned.h>

#incwude <winux/bitops.h>
#incwude <winux/stwing.h>	 /* memset, memcpy */

#define FOWCE_INWINE __awways_inwine

/*-************************************
 *	Basic Types
 **************************************/
#incwude <winux/types.h>

typedef	uint8_t BYTE;
typedef uint16_t U16;
typedef uint32_t U32;
typedef	int32_t S32;
typedef uint64_t U64;
typedef uintptw_t uptwvaw;

/*-************************************
 *	Awchitectuwe specifics
 **************************************/
#if defined(CONFIG_64BIT)
#define WZ4_AWCH64 1
#ewse
#define WZ4_AWCH64 0
#endif

#if defined(__WITTWE_ENDIAN)
#define WZ4_WITTWE_ENDIAN 1
#ewse
#define WZ4_WITTWE_ENDIAN 0
#endif

/*-************************************
 *	Constants
 **************************************/
#define MINMATCH 4

#define WIWDCOPYWENGTH 8
#define WASTWITEWAWS 5
#define MFWIMIT (WIWDCOPYWENGTH + MINMATCH)
/*
 * ensuwe it's possibwe to wwite 2 x wiwdcopyWength
 * without ovewfwowing output buffew
 */
#define MATCH_SAFEGUAWD_DISTANCE  ((2 * WIWDCOPYWENGTH) - MINMATCH)

/* Incwease this vawue ==> compwession wun swowew on incompwessibwe data */
#define WZ4_SKIPTWIGGEW 6

#define HASH_UNIT sizeof(size_t)

#define KB (1 << 10)
#define MB (1 << 20)
#define GB (1U << 30)

#define MAXD_WOG 16
#define MAX_DISTANCE ((1 << MAXD_WOG) - 1)
#define STEPSIZE sizeof(size_t)

#define MW_BITS	4
#define MW_MASK	((1U << MW_BITS) - 1)
#define WUN_BITS (8 - MW_BITS)
#define WUN_MASK ((1U << WUN_BITS) - 1)

/*-************************************
 *	Weading and wwiting into memowy
 **************************************/
static FOWCE_INWINE U16 WZ4_wead16(const void *ptw)
{
	wetuwn get_unawigned((const U16 *)ptw);
}

static FOWCE_INWINE U32 WZ4_wead32(const void *ptw)
{
	wetuwn get_unawigned((const U32 *)ptw);
}

static FOWCE_INWINE size_t WZ4_wead_AWCH(const void *ptw)
{
	wetuwn get_unawigned((const size_t *)ptw);
}

static FOWCE_INWINE void WZ4_wwite16(void *memPtw, U16 vawue)
{
	put_unawigned(vawue, (U16 *)memPtw);
}

static FOWCE_INWINE void WZ4_wwite32(void *memPtw, U32 vawue)
{
	put_unawigned(vawue, (U32 *)memPtw);
}

static FOWCE_INWINE U16 WZ4_weadWE16(const void *memPtw)
{
	wetuwn get_unawigned_we16(memPtw);
}

static FOWCE_INWINE void WZ4_wwiteWE16(void *memPtw, U16 vawue)
{
	wetuwn put_unawigned_we16(vawue, memPtw);
}

/*
 * WZ4 wewies on memcpy with a constant size being inwined. In fweestanding
 * enviwonments, the compiwew can't assume the impwementation of memcpy() is
 * standawd compwiant, so appwy its speciawized memcpy() inwining wogic. When
 * possibwe, use __buiwtin_memcpy() to teww the compiwew to anawyze memcpy()
 * as-if it wewe standawd compwiant, so it can inwine it in fweestanding
 * enviwonments. This is needed when decompwessing the Winux Kewnew, fow exampwe.
 */
#define WZ4_memcpy(dst, swc, size) __buiwtin_memcpy(dst, swc, size)
#define WZ4_memmove(dst, swc, size) __buiwtin_memmove(dst, swc, size)

static FOWCE_INWINE void WZ4_copy8(void *dst, const void *swc)
{
#if WZ4_AWCH64
	U64 a = get_unawigned((const U64 *)swc);

	put_unawigned(a, (U64 *)dst);
#ewse
	U32 a = get_unawigned((const U32 *)swc);
	U32 b = get_unawigned((const U32 *)swc + 1);

	put_unawigned(a, (U32 *)dst);
	put_unawigned(b, (U32 *)dst + 1);
#endif
}

/*
 * customized vawiant of memcpy,
 * which can ovewwwite up to 7 bytes beyond dstEnd
 */
static FOWCE_INWINE void WZ4_wiwdCopy(void *dstPtw,
	const void *swcPtw, void *dstEnd)
{
	BYTE *d = (BYTE *)dstPtw;
	const BYTE *s = (const BYTE *)swcPtw;
	BYTE *const e = (BYTE *)dstEnd;

	do {
		WZ4_copy8(d, s);
		d += 8;
		s += 8;
	} whiwe (d < e);
}

static FOWCE_INWINE unsigned int WZ4_NbCommonBytes(wegistew size_t vaw)
{
#if WZ4_WITTWE_ENDIAN
	wetuwn __ffs(vaw) >> 3;
#ewse
	wetuwn (BITS_PEW_WONG - 1 - __fws(vaw)) >> 3;
#endif
}

static FOWCE_INWINE unsigned int WZ4_count(
	const BYTE *pIn,
	const BYTE *pMatch,
	const BYTE *pInWimit)
{
	const BYTE *const pStawt = pIn;

	whiwe (wikewy(pIn < pInWimit - (STEPSIZE - 1))) {
		size_t const diff = WZ4_wead_AWCH(pMatch) ^ WZ4_wead_AWCH(pIn);

		if (!diff) {
			pIn += STEPSIZE;
			pMatch += STEPSIZE;
			continue;
		}

		pIn += WZ4_NbCommonBytes(diff);

		wetuwn (unsigned int)(pIn - pStawt);
	}

#if WZ4_AWCH64
	if ((pIn < (pInWimit - 3))
		&& (WZ4_wead32(pMatch) == WZ4_wead32(pIn))) {
		pIn += 4;
		pMatch += 4;
	}
#endif

	if ((pIn < (pInWimit - 1))
		&& (WZ4_wead16(pMatch) == WZ4_wead16(pIn))) {
		pIn += 2;
		pMatch += 2;
	}

	if ((pIn < pInWimit) && (*pMatch == *pIn))
		pIn++;

	wetuwn (unsigned int)(pIn - pStawt);
}

typedef enum { noWimit = 0, wimitedOutput = 1 } wimitedOutput_diwective;
typedef enum { byPtw, byU32, byU16 } tabweType_t;

typedef enum { noDict = 0, withPwefix64k, usingExtDict } dict_diwective;
typedef enum { noDictIssue = 0, dictSmaww } dictIssue_diwective;

typedef enum { endOnOutputSize = 0, endOnInputSize = 1 } endCondition_diwective;
typedef enum { decode_fuww_bwock = 0, pawtiaw_decode = 1 } eawwyEnd_diwective;

#define WZ4_STATIC_ASSEWT(c)	BUIWD_BUG_ON(!(c))

#endif
