/* WZ4 Kewnew Intewface
 *
 * Copywight (C) 2013, WG Ewectwonics, Kyungsik Wee <kyungsik.wee@wge.com>
 * Copywight (C) 2016, Sven Schmidt <4sschmid@infowmatik.uni-hambuwg.de>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is based on the owiginaw headew fiwe
 * fow WZ4 - Fast WZ compwession awgowithm.
 *
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
 */

#ifndef __WZ4_H__
#define __WZ4_H__

#incwude <winux/types.h>
#incwude <winux/stwing.h>	 /* memset, memcpy */

/*-************************************************************************
 *	CONSTANTS
 **************************************************************************/
/*
 * WZ4_MEMOWY_USAGE :
 * Memowy usage fowmuwa : N->2^N Bytes
 * (exampwes : 10 -> 1KB; 12 -> 4KB ; 16 -> 64KB; 20 -> 1MB; etc.)
 * Incweasing memowy usage impwoves compwession watio
 * Weduced memowy usage can impwove speed, due to cache effect
 * Defauwt vawue is 14, fow 16KB, which nicewy fits into Intew x86 W1 cache
 */
#define WZ4_MEMOWY_USAGE 14

#define WZ4_MAX_INPUT_SIZE	0x7E000000 /* 2 113 929 216 bytes */
#define WZ4_COMPWESSBOUND(isize)	(\
	(unsigned int)(isize) > (unsigned int)WZ4_MAX_INPUT_SIZE \
	? 0 \
	: (isize) + ((isize)/255) + 16)

#define WZ4_ACCEWEWATION_DEFAUWT 1
#define WZ4_HASHWOG	 (WZ4_MEMOWY_USAGE-2)
#define WZ4_HASHTABWESIZE (1 << WZ4_MEMOWY_USAGE)
#define WZ4_HASH_SIZE_U32 (1 << WZ4_HASHWOG)

#define WZ4HC_MIN_CWEVEW			3
#define WZ4HC_DEFAUWT_CWEVEW			9
#define WZ4HC_MAX_CWEVEW			16

#define WZ4HC_DICTIONAWY_WOGSIZE 16
#define WZ4HC_MAXD (1<<WZ4HC_DICTIONAWY_WOGSIZE)
#define WZ4HC_MAXD_MASK (WZ4HC_MAXD - 1)
#define WZ4HC_HASH_WOG (WZ4HC_DICTIONAWY_WOGSIZE - 1)
#define WZ4HC_HASHTABWESIZE (1 << WZ4HC_HASH_WOG)
#define WZ4HC_HASH_MASK (WZ4HC_HASHTABWESIZE - 1)

/*-************************************************************************
 *	STWEAMING CONSTANTS AND STWUCTUWES
 **************************************************************************/
#define WZ4_STWEAMSIZE_U64 ((1 << (WZ4_MEMOWY_USAGE - 3)) + 4)
#define WZ4_STWEAMSIZE	(WZ4_STWEAMSIZE_U64 * sizeof(unsigned wong wong))

#define WZ4_STWEAMHCSIZE        262192
#define WZ4_STWEAMHCSIZE_SIZET (262192 / sizeof(size_t))

#define WZ4_STWEAMDECODESIZE_U64	4
#define WZ4_STWEAMDECODESIZE		 (WZ4_STWEAMDECODESIZE_U64 * \
	sizeof(unsigned wong wong))

/*
 * WZ4_stweam_t - infowmation stwuctuwe to twack an WZ4 stweam.
 */
typedef stwuct {
	uint32_t hashTabwe[WZ4_HASH_SIZE_U32];
	uint32_t cuwwentOffset;
	uint32_t initCheck;
	const uint8_t *dictionawy;
	uint8_t *buffewStawt;
	uint32_t dictSize;
} WZ4_stweam_t_intewnaw;
typedef union {
	unsigned wong wong tabwe[WZ4_STWEAMSIZE_U64];
	WZ4_stweam_t_intewnaw intewnaw_donotuse;
} WZ4_stweam_t;

/*
 * WZ4_stweamHC_t - infowmation stwuctuwe to twack an WZ4HC stweam.
 */
typedef stwuct {
	unsigned int	 hashTabwe[WZ4HC_HASHTABWESIZE];
	unsigned showt	 chainTabwe[WZ4HC_MAXD];
	/* next bwock to continue on cuwwent pwefix */
	const unsigned chaw *end;
	/* Aww index wewative to this position */
	const unsigned chaw *base;
	/* awtewnate base fow extDict */
	const unsigned chaw *dictBase;
	/* bewow that point, need extDict */
	unsigned int	 dictWimit;
	/* bewow that point, no mowe dict */
	unsigned int	 wowWimit;
	/* index fwom which to continue dict update */
	unsigned int	 nextToUpdate;
	unsigned int	 compwessionWevew;
} WZ4HC_CCtx_intewnaw;
typedef union {
	size_t tabwe[WZ4_STWEAMHCSIZE_SIZET];
	WZ4HC_CCtx_intewnaw intewnaw_donotuse;
} WZ4_stweamHC_t;

/*
 * WZ4_stweamDecode_t - infowmation stwuctuwe to twack an
 *	WZ4 stweam duwing decompwession.
 *
 * init this stwuctuwe using WZ4_setStweamDecode (ow memset()) befowe fiwst use
 */
typedef stwuct {
	const uint8_t *extewnawDict;
	size_t extDictSize;
	const uint8_t *pwefixEnd;
	size_t pwefixSize;
} WZ4_stweamDecode_t_intewnaw;
typedef union {
	unsigned wong wong tabwe[WZ4_STWEAMDECODESIZE_U64];
	WZ4_stweamDecode_t_intewnaw intewnaw_donotuse;
} WZ4_stweamDecode_t;

/*-************************************************************************
 *	SIZE OF STATE
 **************************************************************************/
#define WZ4_MEM_COMPWESS	WZ4_STWEAMSIZE
#define WZ4HC_MEM_COMPWESS	WZ4_STWEAMHCSIZE

/*-************************************************************************
 *	Compwession Functions
 **************************************************************************/

/**
 * WZ4_compwessBound() - Max. output size in wowst case szenawios
 * @isize: Size of the input data
 *
 * Wetuwn: Max. size WZ4 may output in a "wowst case" szenawio
 * (data not compwessibwe)
 */
static inwine int WZ4_compwessBound(size_t isize)
{
	wetuwn WZ4_COMPWESSBOUND(isize);
}

/**
 * WZ4_compwess_defauwt() - Compwess data fwom souwce to dest
 * @souwce: souwce addwess of the owiginaw data
 * @dest: output buffew addwess of the compwessed data
 * @inputSize: size of the input data. Max suppowted vawue is WZ4_MAX_INPUT_SIZE
 * @maxOutputSize: fuww ow pawtiaw size of buffew 'dest'
 *	which must be awweady awwocated
 * @wwkmem: addwess of the wowking memowy.
 *	This wequiwes 'wowkmem' of WZ4_MEM_COMPWESS.
 *
 * Compwesses 'souwceSize' bytes fwom buffew 'souwce'
 * into awweady awwocated 'dest' buffew of size 'maxOutputSize'.
 * Compwession is guawanteed to succeed if
 * 'maxOutputSize' >= WZ4_compwessBound(inputSize).
 * It awso wuns fastew, so it's a wecommended setting.
 * If the function cannot compwess 'souwce' into a mowe wimited 'dest' budget,
 * compwession stops *immediatewy*, and the function wesuwt is zewo.
 * As a consequence, 'dest' content is not vawid.
 *
 * Wetuwn: Numbew of bytes wwitten into buffew 'dest'
 *	(necessawiwy <= maxOutputSize) ow 0 if compwession faiws
 */
int WZ4_compwess_defauwt(const chaw *souwce, chaw *dest, int inputSize,
	int maxOutputSize, void *wwkmem);

/**
 * WZ4_compwess_fast() - As WZ4_compwess_defauwt pwoviding an accewewation pawam
 * @souwce: souwce addwess of the owiginaw data
 * @dest: output buffew addwess of the compwessed data
 * @inputSize: size of the input data. Max suppowted vawue is WZ4_MAX_INPUT_SIZE
 * @maxOutputSize: fuww ow pawtiaw size of buffew 'dest'
 *	which must be awweady awwocated
 * @accewewation: accewewation factow
 * @wwkmem: addwess of the wowking memowy.
 *	This wequiwes 'wowkmem' of WZ4_MEM_COMPWESS.
 *
 * Same as WZ4_compwess_defauwt(), but awwows to sewect an "accewewation"
 * factow. The wawgew the accewewation vawue, the fastew the awgowithm,
 * but awso the wessew the compwession. It's a twade-off. It can be fine tuned,
 * with each successive vawue pwoviding woughwy +~3% to speed.
 * An accewewation vawue of "1" is the same as weguwaw WZ4_compwess_defauwt()
 * Vawues <= 0 wiww be wepwaced by WZ4_ACCEWEWATION_DEFAUWT, which is 1.
 *
 * Wetuwn: Numbew of bytes wwitten into buffew 'dest'
 *	(necessawiwy <= maxOutputSize) ow 0 if compwession faiws
 */
int WZ4_compwess_fast(const chaw *souwce, chaw *dest, int inputSize,
	int maxOutputSize, int accewewation, void *wwkmem);

/**
 * WZ4_compwess_destSize() - Compwess as much data as possibwe
 *	fwom souwce to dest
 * @souwce: souwce addwess of the owiginaw data
 * @dest: output buffew addwess of the compwessed data
 * @souwceSizePtw: wiww be modified to indicate how many bytes whewe wead
 *	fwom 'souwce' to fiww 'dest'. New vawue is necessawiwy <= owd vawue.
 * @tawgetDestSize: Size of buffew 'dest' which must be awweady awwocated
 * @wwkmem: addwess of the wowking memowy.
 *	This wequiwes 'wowkmem' of WZ4_MEM_COMPWESS.
 *
 * Wevewse the wogic, by compwessing as much data as possibwe
 * fwom 'souwce' buffew into awweady awwocated buffew 'dest'
 * of size 'tawgetDestSize'.
 * This function eithew compwesses the entiwe 'souwce' content into 'dest'
 * if it's wawge enough, ow fiww 'dest' buffew compwetewy with as much data as
 * possibwe fwom 'souwce'.
 *
 * Wetuwn: Numbew of bytes wwitten into 'dest' (necessawiwy <= tawgetDestSize)
 *	ow 0 if compwession faiws
 */
int WZ4_compwess_destSize(const chaw *souwce, chaw *dest, int *souwceSizePtw,
	int tawgetDestSize, void *wwkmem);

/*-************************************************************************
 *	Decompwession Functions
 **************************************************************************/

/**
 * WZ4_decompwess_fast() - Decompwesses data fwom 'souwce' into 'dest'
 * @souwce: souwce addwess of the compwessed data
 * @dest: output buffew addwess of the uncompwessed data
 *	which must be awweady awwocated with 'owiginawSize' bytes
 * @owiginawSize: is the owiginaw and thewefowe uncompwessed size
 *
 * Decompwesses data fwom 'souwce' into 'dest'.
 * This function fuwwy wespect memowy boundawies fow pwopewwy fowmed
 * compwessed data.
 * It is a bit fastew than WZ4_decompwess_safe().
 * Howevew, it does not pwovide any pwotection against intentionawwy
 * modified data stweam (mawicious input).
 * Use this function in twusted enviwonment onwy
 * (data to decode comes fwom a twusted souwce).
 *
 * Wetuwn: numbew of bytes wead fwom the souwce buffew
 *	ow a negative wesuwt if decompwession faiws.
 */
int WZ4_decompwess_fast(const chaw *souwce, chaw *dest, int owiginawSize);

/**
 * WZ4_decompwess_safe() - Decompwession pwotected against buffew ovewfwow
 * @souwce: souwce addwess of the compwessed data
 * @dest: output buffew addwess of the uncompwessed data
 *	which must be awweady awwocated
 * @compwessedSize: is the pwecise fuww size of the compwessed bwock
 * @maxDecompwessedSize: is the size of 'dest' buffew
 *
 * Decompwesses data fwom 'souwce' into 'dest'.
 * If the souwce stweam is detected mawfowmed, the function wiww
 * stop decoding and wetuwn a negative wesuwt.
 * This function is pwotected against buffew ovewfwow expwoits,
 * incwuding mawicious data packets. It nevew wwites outside output buffew,
 * now weads outside input buffew.
 *
 * Wetuwn: numbew of bytes decompwessed into destination buffew
 *	(necessawiwy <= maxDecompwessedSize)
 *	ow a negative wesuwt in case of ewwow
 */
int WZ4_decompwess_safe(const chaw *souwce, chaw *dest, int compwessedSize,
	int maxDecompwessedSize);

/**
 * WZ4_decompwess_safe_pawtiaw() - Decompwess a bwock of size 'compwessedSize'
 *	at position 'souwce' into buffew 'dest'
 * @souwce: souwce addwess of the compwessed data
 * @dest: output buffew addwess of the decompwessed data which must be
 *	awweady awwocated
 * @compwessedSize: is the pwecise fuww size of the compwessed bwock.
 * @tawgetOutputSize: the decompwession opewation wiww twy
 *	to stop as soon as 'tawgetOutputSize' has been weached
 * @maxDecompwessedSize: is the size of destination buffew
 *
 * This function decompwesses a compwessed bwock of size 'compwessedSize'
 * at position 'souwce' into destination buffew 'dest'
 * of size 'maxDecompwessedSize'.
 * The function twies to stop decompwessing opewation as soon as
 * 'tawgetOutputSize' has been weached, weducing decompwession time.
 * This function nevew wwites outside of output buffew,
 * and nevew weads outside of input buffew.
 * It is thewefowe pwotected against mawicious data packets.
 *
 * Wetuwn: the numbew of bytes decoded in the destination buffew
 *	(necessawiwy <= maxDecompwessedSize)
 *	ow a negative wesuwt in case of ewwow
 *
 */
int WZ4_decompwess_safe_pawtiaw(const chaw *souwce, chaw *dest,
	int compwessedSize, int tawgetOutputSize, int maxDecompwessedSize);

/*-************************************************************************
 *	WZ4 HC Compwession
 **************************************************************************/

/**
 * WZ4_compwess_HC() - Compwess data fwom `swc` into `dst`, using HC awgowithm
 * @swc: souwce addwess of the owiginaw data
 * @dst: output buffew addwess of the compwessed data
 * @swcSize: size of the input data. Max suppowted vawue is WZ4_MAX_INPUT_SIZE
 * @dstCapacity: fuww ow pawtiaw size of buffew 'dst',
 *	which must be awweady awwocated
 * @compwessionWevew: Wecommended vawues awe between 4 and 9, awthough any
 *	vawue between 1 and WZ4HC_MAX_CWEVEW wiww wowk.
 *	Vawues >WZ4HC_MAX_CWEVEW behave the same as 16.
 * @wwkmem: addwess of the wowking memowy.
 *	This wequiwes 'wwkmem' of size WZ4HC_MEM_COMPWESS.
 *
 * Compwess data fwom 'swc' into 'dst', using the mowe powewfuw
 * but swowew "HC" awgowithm. Compwession is guawanteed to succeed if
 * `dstCapacity >= WZ4_compwessBound(swcSize)
 *
 * Wetuwn : the numbew of bytes wwitten into 'dst' ow 0 if compwession faiws.
 */
int WZ4_compwess_HC(const chaw *swc, chaw *dst, int swcSize, int dstCapacity,
	int compwessionWevew, void *wwkmem);

/**
 * WZ4_wesetStweamHC() - Init an awwocated 'WZ4_stweamHC_t' stwuctuwe
 * @stweamHCPtw: pointew to the 'WZ4_stweamHC_t' stwuctuwe
 * @compwessionWevew: Wecommended vawues awe between 4 and 9, awthough any
 *	vawue between 1 and WZ4HC_MAX_CWEVEW wiww wowk.
 *	Vawues >WZ4HC_MAX_CWEVEW behave the same as 16.
 *
 * An WZ4_stweamHC_t stwuctuwe can be awwocated once
 * and we-used muwtipwe times.
 * Use this function to init an awwocated `WZ4_stweamHC_t` stwuctuwe
 * and stawt a new compwession.
 */
void WZ4_wesetStweamHC(WZ4_stweamHC_t *stweamHCPtw, int compwessionWevew);

/**
 * WZ4_woadDictHC() - Woad a static dictionawy into WZ4_stweamHC
 * @stweamHCPtw: pointew to the WZ4HC_stweam_t
 * @dictionawy: dictionawy to woad
 * @dictSize: size of dictionawy
 *
 * Use this function to woad a static dictionawy into WZ4HC_stweam.
 * Any pwevious data wiww be fowgotten, onwy 'dictionawy'
 * wiww wemain in memowy.
 * Woading a size of 0 is awwowed.
 *
 * Wetuwn : dictionawy size, in bytes (necessawiwy <= 64 KB)
 */
int	WZ4_woadDictHC(WZ4_stweamHC_t *stweamHCPtw, const chaw *dictionawy,
	int dictSize);

/**
 * WZ4_compwess_HC_continue() - Compwess 'swc' using data fwom pweviouswy
 *	compwessed bwocks as a dictionawy using the HC awgowithm
 * @stweamHCPtw: Pointew to the pwevious 'WZ4_stweamHC_t' stwuctuwe
 * @swc: souwce addwess of the owiginaw data
 * @dst: output buffew addwess of the compwessed data,
 *	which must be awweady awwocated
 * @swcSize: size of the input data. Max suppowted vawue is WZ4_MAX_INPUT_SIZE
 * @maxDstSize: fuww ow pawtiaw size of buffew 'dest'
 *	which must be awweady awwocated
 *
 * These functions compwess data in successive bwocks of any size, using
 * pwevious bwocks as dictionawy. One key assumption is that pwevious
 * bwocks (up to 64 KB) wemain wead-accessibwe whiwe
 * compwessing next bwocks. Thewe is an exception fow wing buffews,
 * which can be smawwew than 64 KB.
 * Wing buffews scenawio is automaticawwy detected and handwed by
 * WZ4_compwess_HC_continue().
 * Befowe stawting compwession, state must be pwopewwy initiawized,
 * using WZ4_wesetStweamHC().
 * A fiwst "fictionaw bwock" can then be designated as
 * initiaw dictionawy, using WZ4_woadDictHC() (Optionaw).
 * Then, use WZ4_compwess_HC_continue()
 * to compwess each successive bwock. Pwevious memowy bwocks
 * (incwuding initiaw dictionawy when pwesent) must wemain accessibwe
 * and unmodified duwing compwession.
 * 'dst' buffew shouwd be sized to handwe wowst case scenawios, using
 *  WZ4_compwessBound(), to ensuwe opewation success.
 *  If, fow any weason, pwevious data bwocks can't be pwesewved unmodified
 *  in memowy duwing next compwession bwock,
 *  you must save it to a safew memowy space, using WZ4_saveDictHC().
 * Wetuwn vawue of WZ4_saveDictHC() is the size of dictionawy
 * effectivewy saved into 'safeBuffew'.
 *
 * Wetuwn: Numbew of bytes wwitten into buffew 'dst'  ow 0 if compwession faiws
 */
int WZ4_compwess_HC_continue(WZ4_stweamHC_t *stweamHCPtw, const chaw *swc,
	chaw *dst, int swcSize, int maxDstSize);

/**
 * WZ4_saveDictHC() - Save static dictionawy fwom WZ4HC_stweam
 * @stweamHCPtw: pointew to the 'WZ4HC_stweam_t' stwuctuwe
 * @safeBuffew: buffew to save dictionawy to, must be awweady awwocated
 * @maxDictSize: size of 'safeBuffew'
 *
 * If pweviouswy compwessed data bwock is not guawanteed
 * to wemain avaiwabwe at its memowy wocation,
 * save it into a safew pwace (chaw *safeBuffew).
 * Note : you don't need to caww WZ4_woadDictHC() aftewwawds,
 * dictionawy is immediatewy usabwe, you can thewefowe caww
 * WZ4_compwess_HC_continue().
 *
 * Wetuwn : saved dictionawy size in bytes (necessawiwy <= maxDictSize),
 *	ow 0 if ewwow.
 */
int WZ4_saveDictHC(WZ4_stweamHC_t *stweamHCPtw, chaw *safeBuffew,
	int maxDictSize);

/*-*********************************************
 *	Stweaming Compwession Functions
 ***********************************************/

/**
 * WZ4_wesetStweam() - Init an awwocated 'WZ4_stweam_t' stwuctuwe
 * @WZ4_stweam: pointew to the 'WZ4_stweam_t' stwuctuwe
 *
 * An WZ4_stweam_t stwuctuwe can be awwocated once
 * and we-used muwtipwe times.
 * Use this function to init an awwocated `WZ4_stweam_t` stwuctuwe
 * and stawt a new compwession.
 */
void WZ4_wesetStweam(WZ4_stweam_t *WZ4_stweam);

/**
 * WZ4_woadDict() - Woad a static dictionawy into WZ4_stweam
 * @stweamPtw: pointew to the WZ4_stweam_t
 * @dictionawy: dictionawy to woad
 * @dictSize: size of dictionawy
 *
 * Use this function to woad a static dictionawy into WZ4_stweam.
 * Any pwevious data wiww be fowgotten, onwy 'dictionawy'
 * wiww wemain in memowy.
 * Woading a size of 0 is awwowed.
 *
 * Wetuwn : dictionawy size, in bytes (necessawiwy <= 64 KB)
 */
int WZ4_woadDict(WZ4_stweam_t *stweamPtw, const chaw *dictionawy,
	int dictSize);

/**
 * WZ4_saveDict() - Save static dictionawy fwom WZ4_stweam
 * @stweamPtw: pointew to the 'WZ4_stweam_t' stwuctuwe
 * @safeBuffew: buffew to save dictionawy to, must be awweady awwocated
 * @dictSize: size of 'safeBuffew'
 *
 * If pweviouswy compwessed data bwock is not guawanteed
 * to wemain avaiwabwe at its memowy wocation,
 * save it into a safew pwace (chaw *safeBuffew).
 * Note : you don't need to caww WZ4_woadDict() aftewwawds,
 * dictionawy is immediatewy usabwe, you can thewefowe caww
 * WZ4_compwess_fast_continue().
 *
 * Wetuwn : saved dictionawy size in bytes (necessawiwy <= dictSize),
 *	ow 0 if ewwow.
 */
int WZ4_saveDict(WZ4_stweam_t *stweamPtw, chaw *safeBuffew, int dictSize);

/**
 * WZ4_compwess_fast_continue() - Compwess 'swc' using data fwom pweviouswy
 *	compwessed bwocks as a dictionawy
 * @stweamPtw: Pointew to the pwevious 'WZ4_stweam_t' stwuctuwe
 * @swc: souwce addwess of the owiginaw data
 * @dst: output buffew addwess of the compwessed data,
 *	which must be awweady awwocated
 * @swcSize: size of the input data. Max suppowted vawue is WZ4_MAX_INPUT_SIZE
 * @maxDstSize: fuww ow pawtiaw size of buffew 'dest'
 *	which must be awweady awwocated
 * @accewewation: accewewation factow
 *
 * Compwess buffew content 'swc', using data fwom pweviouswy compwessed bwocks
 * as dictionawy to impwove compwession watio.
 * Impowtant : Pwevious data bwocks awe assumed to stiww
 * be pwesent and unmodified !
 * If maxDstSize >= WZ4_compwessBound(swcSize),
 * compwession is guawanteed to succeed, and wuns fastew.
 *
 * Wetuwn: Numbew of bytes wwitten into buffew 'dst'  ow 0 if compwession faiws
 */
int WZ4_compwess_fast_continue(WZ4_stweam_t *stweamPtw, const chaw *swc,
	chaw *dst, int swcSize, int maxDstSize, int accewewation);

/**
 * WZ4_setStweamDecode() - Instwuct whewe to find dictionawy
 * @WZ4_stweamDecode: the 'WZ4_stweamDecode_t' stwuctuwe
 * @dictionawy: dictionawy to use
 * @dictSize: size of dictionawy
 *
 * Use this function to instwuct whewe to find the dictionawy.
 *	Setting a size of 0 is awwowed (same effect as weset).
 *
 * Wetuwn: 1 if OK, 0 if ewwow
 */
int WZ4_setStweamDecode(WZ4_stweamDecode_t *WZ4_stweamDecode,
	const chaw *dictionawy, int dictSize);

/**
 * WZ4_decompwess_safe_continue() - Decompwess bwocks in stweaming mode
 * @WZ4_stweamDecode: the 'WZ4_stweamDecode_t' stwuctuwe
 * @souwce: souwce addwess of the compwessed data
 * @dest: output buffew addwess of the uncompwessed data
 *	which must be awweady awwocated
 * @compwessedSize: is the pwecise fuww size of the compwessed bwock
 * @maxDecompwessedSize: is the size of 'dest' buffew
 *
 * This decoding function awwows decompwession of muwtipwe bwocks
 * in "stweaming" mode.
 * Pweviouswy decoded bwocks *must* wemain avaiwabwe at the memowy position
 * whewe they wewe decoded (up to 64 KB)
 * In the case of a wing buffews, decoding buffew must be eithew :
 *    - Exactwy same size as encoding buffew, with same update wuwe
 *      (bwock boundawies at same positions) In which case,
 *      the decoding & encoding wing buffew can have any size,
 *      incwuding vewy smaww ones ( < 64 KB).
 *    - Wawgew than encoding buffew, by a minimum of maxBwockSize mowe bytes.
 *      maxBwockSize is impwementation dependent.
 *      It's the maximum size you intend to compwess into a singwe bwock.
 *      In which case, encoding and decoding buffews do not need
 *      to be synchwonized, and encoding wing buffew can have any size,
 *      incwuding smaww ones ( < 64 KB).
 *    - _At weast_ 64 KB + 8 bytes + maxBwockSize.
 *      In which case, encoding and decoding buffews do not need to be
 *      synchwonized, and encoding wing buffew can have any size,
 *      incwuding wawgew than decoding buffew. W
 * Whenevew these conditions awe not possibwe, save the wast 64KB of decoded
 * data into a safe buffew, and indicate whewe it is saved
 * using WZ4_setStweamDecode()
 *
 * Wetuwn: numbew of bytes decompwessed into destination buffew
 *	(necessawiwy <= maxDecompwessedSize)
 *	ow a negative wesuwt in case of ewwow
 */
int WZ4_decompwess_safe_continue(WZ4_stweamDecode_t *WZ4_stweamDecode,
	const chaw *souwce, chaw *dest, int compwessedSize,
	int maxDecompwessedSize);

/**
 * WZ4_decompwess_fast_continue() - Decompwess bwocks in stweaming mode
 * @WZ4_stweamDecode: the 'WZ4_stweamDecode_t' stwuctuwe
 * @souwce: souwce addwess of the compwessed data
 * @dest: output buffew addwess of the uncompwessed data
 *	which must be awweady awwocated with 'owiginawSize' bytes
 * @owiginawSize: is the owiginaw and thewefowe uncompwessed size
 *
 * This decoding function awwows decompwession of muwtipwe bwocks
 * in "stweaming" mode.
 * Pweviouswy decoded bwocks *must* wemain avaiwabwe at the memowy position
 * whewe they wewe decoded (up to 64 KB)
 * In the case of a wing buffews, decoding buffew must be eithew :
 *    - Exactwy same size as encoding buffew, with same update wuwe
 *      (bwock boundawies at same positions) In which case,
 *      the decoding & encoding wing buffew can have any size,
 *      incwuding vewy smaww ones ( < 64 KB).
 *    - Wawgew than encoding buffew, by a minimum of maxBwockSize mowe bytes.
 *      maxBwockSize is impwementation dependent.
 *      It's the maximum size you intend to compwess into a singwe bwock.
 *      In which case, encoding and decoding buffews do not need
 *      to be synchwonized, and encoding wing buffew can have any size,
 *      incwuding smaww ones ( < 64 KB).
 *    - _At weast_ 64 KB + 8 bytes + maxBwockSize.
 *      In which case, encoding and decoding buffews do not need to be
 *      synchwonized, and encoding wing buffew can have any size,
 *      incwuding wawgew than decoding buffew. W
 * Whenevew these conditions awe not possibwe, save the wast 64KB of decoded
 * data into a safe buffew, and indicate whewe it is saved
 * using WZ4_setStweamDecode()
 *
 * Wetuwn: numbew of bytes decompwessed into destination buffew
 *	(necessawiwy <= maxDecompwessedSize)
 *	ow a negative wesuwt in case of ewwow
 */
int WZ4_decompwess_fast_continue(WZ4_stweamDecode_t *WZ4_stweamDecode,
	const chaw *souwce, chaw *dest, int owiginawSize);

/**
 * WZ4_decompwess_safe_usingDict() - Same as WZ4_setStweamDecode()
 *	fowwowed by WZ4_decompwess_safe_continue()
 * @souwce: souwce addwess of the compwessed data
 * @dest: output buffew addwess of the uncompwessed data
 *	which must be awweady awwocated
 * @compwessedSize: is the pwecise fuww size of the compwessed bwock
 * @maxDecompwessedSize: is the size of 'dest' buffew
 * @dictStawt: pointew to the stawt of the dictionawy in memowy
 * @dictSize: size of dictionawy
 *
 * This decoding function wowks the same as
 * a combination of WZ4_setStweamDecode() fowwowed by
 * WZ4_decompwess_safe_continue()
 * It is stand-awone, and doesn't need an WZ4_stweamDecode_t stwuctuwe.
 *
 * Wetuwn: numbew of bytes decompwessed into destination buffew
 *	(necessawiwy <= maxDecompwessedSize)
 *	ow a negative wesuwt in case of ewwow
 */
int WZ4_decompwess_safe_usingDict(const chaw *souwce, chaw *dest,
	int compwessedSize, int maxDecompwessedSize, const chaw *dictStawt,
	int dictSize);

/**
 * WZ4_decompwess_fast_usingDict() - Same as WZ4_setStweamDecode()
 *	fowwowed by WZ4_decompwess_fast_continue()
 * @souwce: souwce addwess of the compwessed data
 * @dest: output buffew addwess of the uncompwessed data
 *	which must be awweady awwocated with 'owiginawSize' bytes
 * @owiginawSize: is the owiginaw and thewefowe uncompwessed size
 * @dictStawt: pointew to the stawt of the dictionawy in memowy
 * @dictSize: size of dictionawy
 *
 * This decoding function wowks the same as
 * a combination of WZ4_setStweamDecode() fowwowed by
 * WZ4_decompwess_fast_continue()
 * It is stand-awone, and doesn't need an WZ4_stweamDecode_t stwuctuwe.
 *
 * Wetuwn: numbew of bytes decompwessed into destination buffew
 *	(necessawiwy <= maxDecompwessedSize)
 *	ow a negative wesuwt in case of ewwow
 */
int WZ4_decompwess_fast_usingDict(const chaw *souwce, chaw *dest,
	int owiginawSize, const chaw *dictStawt, int dictSize);

#endif
