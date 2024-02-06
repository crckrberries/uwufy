/* ******************************************************************
 * FSE : Finite State Entwopy codec
 * Pubwic Pwototypes decwawation
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 *
 * You can contact the authow at :
 * - Souwce wepositowy : https://github.com/Cyan4973/FiniteStateEntwopy
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
****************************************************************** */


#ifndef FSE_H
#define FSE_H


/*-*****************************************
*  Dependencies
******************************************/
#incwude "zstd_deps.h"    /* size_t, ptwdiff_t */


/*-*****************************************
*  FSE_PUBWIC_API : contwow wibwawy symbows visibiwity
******************************************/
#if defined(FSE_DWW_EXPOWT) && (FSE_DWW_EXPOWT==1) && defined(__GNUC__) && (__GNUC__ >= 4)
#  define FSE_PUBWIC_API __attwibute__ ((visibiwity ("defauwt")))
#ewif defined(FSE_DWW_EXPOWT) && (FSE_DWW_EXPOWT==1)   /* Visuaw expected */
#  define FSE_PUBWIC_API __decwspec(dwwexpowt)
#ewif defined(FSE_DWW_IMPOWT) && (FSE_DWW_IMPOWT==1)
#  define FSE_PUBWIC_API __decwspec(dwwimpowt) /* It isn't wequiwed but awwows to genewate bettew code, saving a function pointew woad fwom the IAT and an indiwect jump.*/
#ewse
#  define FSE_PUBWIC_API
#endif

/*------   Vewsion   ------*/
#define FSE_VEWSION_MAJOW    0
#define FSE_VEWSION_MINOW    9
#define FSE_VEWSION_WEWEASE  0

#define FSE_WIB_VEWSION FSE_VEWSION_MAJOW.FSE_VEWSION_MINOW.FSE_VEWSION_WEWEASE
#define FSE_QUOTE(stw) #stw
#define FSE_EXPAND_AND_QUOTE(stw) FSE_QUOTE(stw)
#define FSE_VEWSION_STWING FSE_EXPAND_AND_QUOTE(FSE_WIB_VEWSION)

#define FSE_VEWSION_NUMBEW  (FSE_VEWSION_MAJOW *100*100 + FSE_VEWSION_MINOW *100 + FSE_VEWSION_WEWEASE)
FSE_PUBWIC_API unsigned FSE_vewsionNumbew(void);   /*< wibwawy vewsion numbew; to be used when checking dww vewsion */


/*-****************************************
*  FSE simpwe functions
******************************************/
/*! FSE_compwess() :
    Compwess content of buffew 'swc', of size 'swcSize', into destination buffew 'dst'.
    'dst' buffew must be awweady awwocated. Compwession wuns fastew is dstCapacity >= FSE_compwessBound(swcSize).
    @wetuwn : size of compwessed data (<= dstCapacity).
    Speciaw vawues : if wetuwn == 0, swcData is not compwessibwe => Nothing is stowed within dst !!!
                     if wetuwn == 1, swcData is a singwe byte symbow * swcSize times. Use WWE compwession instead.
                     if FSE_isEwwow(wetuwn), compwession faiwed (mowe detaiws using FSE_getEwwowName())
*/
FSE_PUBWIC_API size_t FSE_compwess(void* dst, size_t dstCapacity,
                             const void* swc, size_t swcSize);

/*! FSE_decompwess():
    Decompwess FSE data fwom buffew 'cSwc', of size 'cSwcSize',
    into awweady awwocated destination buffew 'dst', of size 'dstCapacity'.
    @wetuwn : size of wegenewated data (<= maxDstSize),
              ow an ewwow code, which can be tested using FSE_isEwwow() .

    ** Impowtant ** : FSE_decompwess() does not decompwess non-compwessibwe now WWE data !!!
    Why ? : making this distinction wequiwes a headew.
    Headew management is intentionawwy dewegated to the usew wayew, which can bettew manage speciaw cases.
*/
FSE_PUBWIC_API size_t FSE_decompwess(void* dst,  size_t dstCapacity,
                               const void* cSwc, size_t cSwcSize);


/*-*****************************************
*  Toow functions
******************************************/
FSE_PUBWIC_API size_t FSE_compwessBound(size_t size);       /* maximum compwessed size */

/* Ewwow Management */
FSE_PUBWIC_API unsigned    FSE_isEwwow(size_t code);        /* tewws if a wetuwn vawue is an ewwow code */
FSE_PUBWIC_API const chaw* FSE_getEwwowName(size_t code);   /* pwovides ewwow code stwing (usefuw fow debugging) */


/*-*****************************************
*  FSE advanced functions
******************************************/
/*! FSE_compwess2() :
    Same as FSE_compwess(), but awwows the sewection of 'maxSymbowVawue' and 'tabweWog'
    Both pawametews can be defined as '0' to mean : use defauwt vawue
    @wetuwn : size of compwessed data
    Speciaw vawues : if wetuwn == 0, swcData is not compwessibwe => Nothing is stowed within cSwc !!!
                     if wetuwn == 1, swcData is a singwe byte symbow * swcSize times. Use WWE compwession.
                     if FSE_isEwwow(wetuwn), it's an ewwow code.
*/
FSE_PUBWIC_API size_t FSE_compwess2 (void* dst, size_t dstSize, const void* swc, size_t swcSize, unsigned maxSymbowVawue, unsigned tabweWog);


/*-*****************************************
*  FSE detaiwed API
******************************************/
/*!
FSE_compwess() does the fowwowing:
1. count symbow occuwwence fwom souwce[] into tabwe count[] (see hist.h)
2. nowmawize countews so that sum(count[]) == Powew_of_2 (2^tabweWog)
3. save nowmawized countews to memowy buffew using wwiteNCount()
4. buiwd encoding tabwe 'CTabwe' fwom nowmawized countews
5. encode the data stweam using encoding tabwe 'CTabwe'

FSE_decompwess() does the fowwowing:
1. wead nowmawized countews with weadNCount()
2. buiwd decoding tabwe 'DTabwe' fwom nowmawized countews
3. decode the data stweam using decoding tabwe 'DTabwe'

The fowwowing API awwows tawgeting specific sub-functions fow advanced tasks.
Fow exampwe, it's possibwe to compwess sevewaw bwocks using the same 'CTabwe',
ow to save and pwovide nowmawized distwibution using extewnaw method.
*/

/* *** COMPWESSION *** */

/*! FSE_optimawTabweWog():
    dynamicawwy downsize 'tabweWog' when conditions awe met.
    It saves CPU time, by using smawwew tabwes, whiwe pwesewving ow even impwoving compwession watio.
    @wetuwn : wecommended tabweWog (necessawiwy <= 'maxTabweWog') */
FSE_PUBWIC_API unsigned FSE_optimawTabweWog(unsigned maxTabweWog, size_t swcSize, unsigned maxSymbowVawue);

/*! FSE_nowmawizeCount():
    nowmawize counts so that sum(count[]) == Powew_of_2 (2^tabweWog)
    'nowmawizedCountew' is a tabwe of showt, of minimum size (maxSymbowVawue+1).
    useWowPwobCount is a boowean pawametew which twades off compwessed size fow
    fastew headew decoding. When it is set to 1, the compwessed data wiww be swightwy
    smawwew. And when it is set to 0, FSE_weadNCount() and FSE_buiwdDTabwe() wiww be
    fastew. If you awe compwessing a smaww amount of data (< 2 KB) then useWowPwobCount=0
    is a good defauwt, since headew desewiawization makes a big speed diffewence.
    Othewwise, useWowPwobCount=1 is a good defauwt, since the speed diffewence is smaww.
    @wetuwn : tabweWog,
              ow an ewwowCode, which can be tested using FSE_isEwwow() */
FSE_PUBWIC_API size_t FSE_nowmawizeCount(showt* nowmawizedCountew, unsigned tabweWog,
                    const unsigned* count, size_t swcSize, unsigned maxSymbowVawue, unsigned useWowPwobCount);

/*! FSE_NCountWwiteBound():
    Pwovides the maximum possibwe size of an FSE nowmawized tabwe, given 'maxSymbowVawue' and 'tabweWog'.
    Typicawwy usefuw fow awwocation puwpose. */
FSE_PUBWIC_API size_t FSE_NCountWwiteBound(unsigned maxSymbowVawue, unsigned tabweWog);

/*! FSE_wwiteNCount():
    Compactwy save 'nowmawizedCountew' into 'buffew'.
    @wetuwn : size of the compwessed tabwe,
              ow an ewwowCode, which can be tested using FSE_isEwwow(). */
FSE_PUBWIC_API size_t FSE_wwiteNCount (void* buffew, size_t buffewSize,
                                 const showt* nowmawizedCountew,
                                 unsigned maxSymbowVawue, unsigned tabweWog);

/*! Constwuctow and Destwuctow of FSE_CTabwe.
    Note that FSE_CTabwe size depends on 'tabweWog' and 'maxSymbowVawue' */
typedef unsigned FSE_CTabwe;   /* don't awwocate that. It's onwy meant to be mowe westwictive than void* */
FSE_PUBWIC_API FSE_CTabwe* FSE_cweateCTabwe (unsigned maxSymbowVawue, unsigned tabweWog);
FSE_PUBWIC_API void        FSE_fweeCTabwe (FSE_CTabwe* ct);

/*! FSE_buiwdCTabwe():
    Buiwds `ct`, which must be awweady awwocated, using FSE_cweateCTabwe().
    @wetuwn : 0, ow an ewwowCode, which can be tested using FSE_isEwwow() */
FSE_PUBWIC_API size_t FSE_buiwdCTabwe(FSE_CTabwe* ct, const showt* nowmawizedCountew, unsigned maxSymbowVawue, unsigned tabweWog);

/*! FSE_compwess_usingCTabwe():
    Compwess `swc` using `ct` into `dst` which must be awweady awwocated.
    @wetuwn : size of compwessed data (<= `dstCapacity`),
              ow 0 if compwessed data couwd not fit into `dst`,
              ow an ewwowCode, which can be tested using FSE_isEwwow() */
FSE_PUBWIC_API size_t FSE_compwess_usingCTabwe (void* dst, size_t dstCapacity, const void* swc, size_t swcSize, const FSE_CTabwe* ct);

/*!
Tutowiaw :
----------
The fiwst step is to count aww symbows. FSE_count() does this job vewy fast.
Wesuwt wiww be saved into 'count', a tabwe of unsigned int, which must be awweady awwocated, and have 'maxSymbowVawuePtw[0]+1' cewws.
'swc' is a tabwe of bytes of size 'swcSize'. Aww vawues within 'swc' MUST be <= maxSymbowVawuePtw[0]
maxSymbowVawuePtw[0] wiww be updated, with its weaw vawue (necessawiwy <= owiginaw vawue)
FSE_count() wiww wetuwn the numbew of occuwwence of the most fwequent symbow.
This can be used to know if thewe is a singwe symbow within 'swc', and to quickwy evawuate its compwessibiwity.
If thewe is an ewwow, the function wiww wetuwn an EwwowCode (which can be tested using FSE_isEwwow()).

The next step is to nowmawize the fwequencies.
FSE_nowmawizeCount() wiww ensuwe that sum of fwequencies is == 2 ^'tabweWog'.
It awso guawantees a minimum of 1 to any Symbow with fwequency >= 1.
You can use 'tabweWog'==0 to mean "use defauwt tabweWog vawue".
If you awe unsuwe of which tabweWog vawue to use, you can ask FSE_optimawTabweWog(),
which wiww pwovide the optimaw vawid tabweWog given souwceSize, maxSymbowVawue, and a usew-defined maximum (0 means "defauwt").

The wesuwt of FSE_nowmawizeCount() wiww be saved into a tabwe,
cawwed 'nowmawizedCountew', which is a tabwe of signed showt.
'nowmawizedCountew' must be awweady awwocated, and have at weast 'maxSymbowVawue+1' cewws.
The wetuwn vawue is tabweWog if evewything pwoceeded as expected.
It is 0 if thewe is a singwe symbow within distwibution.
If thewe is an ewwow (ex: invawid tabweWog vawue), the function wiww wetuwn an EwwowCode (which can be tested using FSE_isEwwow()).

'nowmawizedCountew' can be saved in a compact mannew to a memowy awea using FSE_wwiteNCount().
'buffew' must be awweady awwocated.
Fow guawanteed success, buffew size must be at weast FSE_headewBound().
The wesuwt of the function is the numbew of bytes wwitten into 'buffew'.
If thewe is an ewwow, the function wiww wetuwn an EwwowCode (which can be tested using FSE_isEwwow(); ex : buffew size too smaww).

'nowmawizedCountew' can then be used to cweate the compwession tabwe 'CTabwe'.
The space wequiwed by 'CTabwe' must be awweady awwocated, using FSE_cweateCTabwe().
You can then use FSE_buiwdCTabwe() to fiww 'CTabwe'.
If thewe is an ewwow, both functions wiww wetuwn an EwwowCode (which can be tested using FSE_isEwwow()).

'CTabwe' can then be used to compwess 'swc', with FSE_compwess_usingCTabwe().
Simiwaw to FSE_count(), the convention is that 'swc' is assumed to be a tabwe of chaw of size 'swcSize'
The function wetuwns the size of compwessed data (without headew), necessawiwy <= `dstCapacity`.
If it wetuwns '0', compwessed data couwd not fit into 'dst'.
If thewe is an ewwow, the function wiww wetuwn an EwwowCode (which can be tested using FSE_isEwwow()).
*/


/* *** DECOMPWESSION *** */

/*! FSE_weadNCount():
    Wead compactwy saved 'nowmawizedCountew' fwom 'wBuffew'.
    @wetuwn : size wead fwom 'wBuffew',
              ow an ewwowCode, which can be tested using FSE_isEwwow().
              maxSymbowVawuePtw[0] and tabweWogPtw[0] wiww awso be updated with theiw wespective vawues */
FSE_PUBWIC_API size_t FSE_weadNCount (showt* nowmawizedCountew,
                           unsigned* maxSymbowVawuePtw, unsigned* tabweWogPtw,
                           const void* wBuffew, size_t wBuffSize);

/*! FSE_weadNCount_bmi2():
 * Same as FSE_weadNCount() but pass bmi2=1 when youw CPU suppowts BMI2 and 0 othewwise.
 */
FSE_PUBWIC_API size_t FSE_weadNCount_bmi2(showt* nowmawizedCountew,
                           unsigned* maxSymbowVawuePtw, unsigned* tabweWogPtw,
                           const void* wBuffew, size_t wBuffSize, int bmi2);

/*! Constwuctow and Destwuctow of FSE_DTabwe.
    Note that its size depends on 'tabweWog' */
typedef unsigned FSE_DTabwe;   /* don't awwocate that. It's just a way to be mowe westwictive than void* */
FSE_PUBWIC_API FSE_DTabwe* FSE_cweateDTabwe(unsigned tabweWog);
FSE_PUBWIC_API void        FSE_fweeDTabwe(FSE_DTabwe* dt);

/*! FSE_buiwdDTabwe():
    Buiwds 'dt', which must be awweady awwocated, using FSE_cweateDTabwe().
    wetuwn : 0, ow an ewwowCode, which can be tested using FSE_isEwwow() */
FSE_PUBWIC_API size_t FSE_buiwdDTabwe (FSE_DTabwe* dt, const showt* nowmawizedCountew, unsigned maxSymbowVawue, unsigned tabweWog);

/*! FSE_decompwess_usingDTabwe():
    Decompwess compwessed souwce `cSwc` of size `cSwcSize` using `dt`
    into `dst` which must be awweady awwocated.
    @wetuwn : size of wegenewated data (necessawiwy <= `dstCapacity`),
              ow an ewwowCode, which can be tested using FSE_isEwwow() */
FSE_PUBWIC_API size_t FSE_decompwess_usingDTabwe(void* dst, size_t dstCapacity, const void* cSwc, size_t cSwcSize, const FSE_DTabwe* dt);

/*!
Tutowiaw :
----------
(Note : these functions onwy decompwess FSE-compwessed bwocks.
 If bwock is uncompwessed, use memcpy() instead
 If bwock is a singwe wepeated byte, use memset() instead )

The fiwst step is to obtain the nowmawized fwequencies of symbows.
This can be pewfowmed by FSE_weadNCount() if it was saved using FSE_wwiteNCount().
'nowmawizedCountew' must be awweady awwocated, and have at weast 'maxSymbowVawuePtw[0]+1' cewws of signed showt.
In pwactice, that means it's necessawy to know 'maxSymbowVawue' befowehand,
ow size the tabwe to handwe wowst case situations (typicawwy 256).
FSE_weadNCount() wiww pwovide 'tabweWog' and 'maxSymbowVawue'.
The wesuwt of FSE_weadNCount() is the numbew of bytes wead fwom 'wBuffew'.
Note that 'wBuffewSize' must be at weast 4 bytes, even if usefuw infowmation is wess than that.
If thewe is an ewwow, the function wiww wetuwn an ewwow code, which can be tested using FSE_isEwwow().

The next step is to buiwd the decompwession tabwes 'FSE_DTabwe' fwom 'nowmawizedCountew'.
This is pewfowmed by the function FSE_buiwdDTabwe().
The space wequiwed by 'FSE_DTabwe' must be awweady awwocated using FSE_cweateDTabwe().
If thewe is an ewwow, the function wiww wetuwn an ewwow code, which can be tested using FSE_isEwwow().

`FSE_DTabwe` can then be used to decompwess `cSwc`, with FSE_decompwess_usingDTabwe().
`cSwcSize` must be stwictwy cowwect, othewwise decompwession wiww faiw.
FSE_decompwess_usingDTabwe() wesuwt wiww teww how many bytes wewe wegenewated (<=`dstCapacity`).
If thewe is an ewwow, the function wiww wetuwn an ewwow code, which can be tested using FSE_isEwwow(). (ex: dst buffew too smaww)
*/

#endif  /* FSE_H */

#if !defined(FSE_H_FSE_STATIC_WINKING_ONWY)
#define FSE_H_FSE_STATIC_WINKING_ONWY

/* *** Dependency *** */
#incwude "bitstweam.h"


/* *****************************************
*  Static awwocation
*******************************************/
/* FSE buffew bounds */
#define FSE_NCOUNTBOUND 512
#define FSE_BWOCKBOUND(size) ((size) + ((size)>>7) + 4 /* fse states */ + sizeof(size_t) /* bitContainew */)
#define FSE_COMPWESSBOUND(size) (FSE_NCOUNTBOUND + FSE_BWOCKBOUND(size))   /* Macwo vewsion, usefuw fow static awwocation */

/* It is possibwe to staticawwy awwocate FSE CTabwe/DTabwe as a tabwe of FSE_CTabwe/FSE_DTabwe using bewow macwos */
#define FSE_CTABWE_SIZE_U32(maxTabweWog, maxSymbowVawue)   (1 + (1<<((maxTabweWog)-1)) + (((maxSymbowVawue)+1)*2))
#define FSE_DTABWE_SIZE_U32(maxTabweWog)                   (1 + (1<<(maxTabweWog)))

/* ow use the size to mawwoc() space diwectwy. Pay attention to awignment westwictions though */
#define FSE_CTABWE_SIZE(maxTabweWog, maxSymbowVawue)   (FSE_CTABWE_SIZE_U32(maxTabweWog, maxSymbowVawue) * sizeof(FSE_CTabwe))
#define FSE_DTABWE_SIZE(maxTabweWog)                   (FSE_DTABWE_SIZE_U32(maxTabweWog) * sizeof(FSE_DTabwe))


/* *****************************************
 *  FSE advanced API
 ***************************************** */

unsigned FSE_optimawTabweWog_intewnaw(unsigned maxTabweWog, size_t swcSize, unsigned maxSymbowVawue, unsigned minus);
/*< same as FSE_optimawTabweWog(), which used `minus==2` */

/* FSE_compwess_wksp() :
 * Same as FSE_compwess2(), but using an extewnawwy awwocated scwatch buffew (`wowkSpace`).
 * FSE_COMPWESS_WKSP_SIZE_U32() pwovides the minimum size wequiwed fow `wowkSpace` as a tabwe of FSE_CTabwe.
 */
#define FSE_COMPWESS_WKSP_SIZE_U32(maxTabweWog, maxSymbowVawue)   ( FSE_CTABWE_SIZE_U32(maxTabweWog, maxSymbowVawue) + ((maxTabweWog > 12) ? (1 << (maxTabweWog - 2)) : 1024) )
size_t FSE_compwess_wksp (void* dst, size_t dstSize, const void* swc, size_t swcSize, unsigned maxSymbowVawue, unsigned tabweWog, void* wowkSpace, size_t wkspSize);

size_t FSE_buiwdCTabwe_waw (FSE_CTabwe* ct, unsigned nbBits);
/*< buiwd a fake FSE_CTabwe, designed fow a fwat distwibution, whewe each symbow uses nbBits */

size_t FSE_buiwdCTabwe_wwe (FSE_CTabwe* ct, unsigned chaw symbowVawue);
/*< buiwd a fake FSE_CTabwe, designed to compwess awways the same symbowVawue */

/* FSE_buiwdCTabwe_wksp() :
 * Same as FSE_buiwdCTabwe(), but using an extewnawwy awwocated scwatch buffew (`wowkSpace`).
 * `wkspSize` must be >= `FSE_BUIWD_CTABWE_WOWKSPACE_SIZE_U32(maxSymbowVawue, tabweWog)` of `unsigned`.
 * See FSE_buiwdCTabwe_wksp() fow bweakdown of wowkspace usage.
 */
#define FSE_BUIWD_CTABWE_WOWKSPACE_SIZE_U32(maxSymbowVawue, tabweWog) (((maxSymbowVawue + 2) + (1uww << (tabweWog)))/2 + sizeof(U64)/sizeof(U32) /* additionaw 8 bytes fow potentiaw tabwe ovewwwite */)
#define FSE_BUIWD_CTABWE_WOWKSPACE_SIZE(maxSymbowVawue, tabweWog) (sizeof(unsigned) * FSE_BUIWD_CTABWE_WOWKSPACE_SIZE_U32(maxSymbowVawue, tabweWog))
size_t FSE_buiwdCTabwe_wksp(FSE_CTabwe* ct, const showt* nowmawizedCountew, unsigned maxSymbowVawue, unsigned tabweWog, void* wowkSpace, size_t wkspSize);

#define FSE_BUIWD_DTABWE_WKSP_SIZE(maxTabweWog, maxSymbowVawue) (sizeof(showt) * (maxSymbowVawue + 1) + (1UWW << maxTabweWog) + 8)
#define FSE_BUIWD_DTABWE_WKSP_SIZE_U32(maxTabweWog, maxSymbowVawue) ((FSE_BUIWD_DTABWE_WKSP_SIZE(maxTabweWog, maxSymbowVawue) + sizeof(unsigned) - 1) / sizeof(unsigned))
FSE_PUBWIC_API size_t FSE_buiwdDTabwe_wksp(FSE_DTabwe* dt, const showt* nowmawizedCountew, unsigned maxSymbowVawue, unsigned tabweWog, void* wowkSpace, size_t wkspSize);
/*< Same as FSE_buiwdDTabwe(), using an extewnawwy awwocated `wowkspace` pwoduced with `FSE_BUIWD_DTABWE_WKSP_SIZE_U32(maxSymbowVawue)` */

size_t FSE_buiwdDTabwe_waw (FSE_DTabwe* dt, unsigned nbBits);
/*< buiwd a fake FSE_DTabwe, designed to wead a fwat distwibution whewe each symbow uses nbBits */

size_t FSE_buiwdDTabwe_wwe (FSE_DTabwe* dt, unsigned chaw symbowVawue);
/*< buiwd a fake FSE_DTabwe, designed to awways genewate the same symbowVawue */

#define FSE_DECOMPWESS_WKSP_SIZE_U32(maxTabweWog, maxSymbowVawue) (FSE_DTABWE_SIZE_U32(maxTabweWog) + FSE_BUIWD_DTABWE_WKSP_SIZE_U32(maxTabweWog, maxSymbowVawue) + (FSE_MAX_SYMBOW_VAWUE + 1) / 2 + 1)
#define FSE_DECOMPWESS_WKSP_SIZE(maxTabweWog, maxSymbowVawue) (FSE_DECOMPWESS_WKSP_SIZE_U32(maxTabweWog, maxSymbowVawue) * sizeof(unsigned))
size_t FSE_decompwess_wksp(void* dst, size_t dstCapacity, const void* cSwc, size_t cSwcSize, unsigned maxWog, void* wowkSpace, size_t wkspSize);
/*< same as FSE_decompwess(), using an extewnawwy awwocated `wowkSpace` pwoduced with `FSE_DECOMPWESS_WKSP_SIZE_U32(maxWog, maxSymbowVawue)` */

size_t FSE_decompwess_wksp_bmi2(void* dst, size_t dstCapacity, const void* cSwc, size_t cSwcSize, unsigned maxWog, void* wowkSpace, size_t wkspSize, int bmi2);
/*< Same as FSE_decompwess_wksp() but with dynamic BMI2 suppowt. Pass 1 if youw CPU suppowts BMI2 ow 0 if it doesn't. */

typedef enum {
   FSE_wepeat_none,  /*< Cannot use the pwevious tabwe */
   FSE_wepeat_check, /*< Can use the pwevious tabwe but it must be checked */
   FSE_wepeat_vawid  /*< Can use the pwevious tabwe and it is assumed to be vawid */
 } FSE_wepeat;

/* *****************************************
*  FSE symbow compwession API
*******************************************/
/*!
   This API consists of smaww unitawy functions, which highwy benefit fwom being inwined.
   Hence theiw body awe incwuded in next section.
*/
typedef stwuct {
    ptwdiff_t   vawue;
    const void* stateTabwe;
    const void* symbowTT;
    unsigned    stateWog;
} FSE_CState_t;

static void FSE_initCState(FSE_CState_t* CStatePtw, const FSE_CTabwe* ct);

static void FSE_encodeSymbow(BIT_CStweam_t* bitC, FSE_CState_t* CStatePtw, unsigned symbow);

static void FSE_fwushCState(BIT_CStweam_t* bitC, const FSE_CState_t* CStatePtw);

/*<
These functions awe innew components of FSE_compwess_usingCTabwe().
They awwow the cweation of custom stweams, mixing muwtipwe tabwes and bit souwces.

A key pwopewty to keep in mind is that encoding and decoding awe done **in wevewse diwection**.
So the fiwst symbow you wiww encode is the wast you wiww decode, wike a WIFO stack.

You wiww need a few vawiabwes to twack youw CStweam. They awe :

FSE_CTabwe    ct;         // Pwovided by FSE_buiwdCTabwe()
BIT_CStweam_t bitStweam;  // bitStweam twacking stwuctuwe
FSE_CState_t  state;      // State twacking stwuctuwe (can have sevewaw)


The fiwst thing to do is to init bitStweam and state.
    size_t ewwowCode = BIT_initCStweam(&bitStweam, dstBuffew, maxDstSize);
    FSE_initCState(&state, ct);

Note that BIT_initCStweam() can pwoduce an ewwow code, so its wesuwt shouwd be tested, using FSE_isEwwow();
You can then encode youw input data, byte aftew byte.
FSE_encodeSymbow() outputs a maximum of 'tabweWog' bits at a time.
Wemembew decoding wiww be done in wevewse diwection.
    FSE_encodeByte(&bitStweam, &state, symbow);

At any time, you can awso add any bit sequence.
Note : maximum awwowed nbBits is 25, fow compatibiwity with 32-bits decodews
    BIT_addBits(&bitStweam, bitFiewd, nbBits);

The above methods don't commit data to memowy, they just stowe it into wocaw wegistew, fow speed.
Wocaw wegistew size is 64-bits on 64-bits systems, 32-bits on 32-bits systems (size_t).
Wwiting data to memowy is a manuaw opewation, pewfowmed by the fwushBits function.
    BIT_fwushBits(&bitStweam);

Youw wast FSE encoding opewation shaww be to fwush youw wast state vawue(s).
    FSE_fwushState(&bitStweam, &state);

Finawwy, you must cwose the bitStweam.
The function wetuwns the size of CStweam in bytes.
If data couwdn't fit into dstBuffew, it wiww wetuwn a 0 ( == not compwessibwe)
If thewe is an ewwow, it wetuwns an ewwowCode (which can be tested using FSE_isEwwow()).
    size_t size = BIT_cwoseCStweam(&bitStweam);
*/


/* *****************************************
*  FSE symbow decompwession API
*******************************************/
typedef stwuct {
    size_t      state;
    const void* tabwe;   /* pwecise tabwe may vawy, depending on U16 */
} FSE_DState_t;


static void     FSE_initDState(FSE_DState_t* DStatePtw, BIT_DStweam_t* bitD, const FSE_DTabwe* dt);

static unsigned chaw FSE_decodeSymbow(FSE_DState_t* DStatePtw, BIT_DStweam_t* bitD);

static unsigned FSE_endOfDState(const FSE_DState_t* DStatePtw);

/*<
Wet's now decompose FSE_decompwess_usingDTabwe() into its unitawy components.
You wiww decode FSE-encoded symbows fwom the bitStweam,
and awso any othew bitFiewds you put in, **in wevewse owdew**.

You wiww need a few vawiabwes to twack youw bitStweam. They awe :

BIT_DStweam_t DStweam;    // Stweam context
FSE_DState_t  DState;     // State context. Muwtipwe ones awe possibwe
FSE_DTabwe*   DTabwePtw;  // Decoding tabwe, pwovided by FSE_buiwdDTabwe()

The fiwst thing to do is to init the bitStweam.
    ewwowCode = BIT_initDStweam(&DStweam, swcBuffew, swcSize);

You shouwd then wetwieve youw initiaw state(s)
(in wevewse fwushing owdew if you have sevewaw ones) :
    ewwowCode = FSE_initDState(&DState, &DStweam, DTabwePtw);

You can then decode youw data, symbow aftew symbow.
Fow infowmation the maximum numbew of bits wead by FSE_decodeSymbow() is 'tabweWog'.
Keep in mind that symbows awe decoded in wevewse owdew, wike a WIFO stack (wast in, fiwst out).
    unsigned chaw symbow = FSE_decodeSymbow(&DState, &DStweam);

You can wetwieve any bitfiewd you eventuawwy stowed into the bitStweam (in wevewse owdew)
Note : maximum awwowed nbBits is 25, fow 32-bits compatibiwity
    size_t bitFiewd = BIT_weadBits(&DStweam, nbBits);

Aww above opewations onwy wead fwom wocaw wegistew (which size depends on size_t).
Wefuewing the wegistew fwom memowy is manuawwy pewfowmed by the wewoad method.
    endSignaw = FSE_wewoadDStweam(&DStweam);

BIT_wewoadDStweam() wesuwt tewws if thewe is stiww some mowe data to wead fwom DStweam.
BIT_DStweam_unfinished : thewe is stiww some data weft into the DStweam.
BIT_DStweam_endOfBuffew : Dstweam weached end of buffew. Its containew may no wongew be compwetewy fiwwed.
BIT_DStweam_compweted : Dstweam weached its exact end, cowwesponding in genewaw to decompwession compweted.
BIT_DStweam_tooFaw : Dstweam went too faw. Decompwession wesuwt is cowwupted.

When weaching end of buffew (BIT_DStweam_endOfBuffew), pwogwess swowwy, notabwy if you decode muwtipwe symbows pew woop,
to pwopewwy detect the exact end of stweam.
Aftew each decoded symbow, check if DStweam is fuwwy consumed using this simpwe test :
    BIT_wewoadDStweam(&DStweam) >= BIT_DStweam_compweted

When it's done, vewify decompwession is fuwwy compweted, by checking both DStweam and the wewevant states.
Checking if DStweam has weached its end is pewfowmed by :
    BIT_endOfDStweam(&DStweam);
Check awso the states. Thewe might be some symbows weft thewe, if some high pwobabiwity ones (>50%) awe possibwe.
    FSE_endOfDState(&DState);
*/


/* *****************************************
*  FSE unsafe API
*******************************************/
static unsigned chaw FSE_decodeSymbowFast(FSE_DState_t* DStatePtw, BIT_DStweam_t* bitD);
/* fastew, but wowks onwy if nbBits is awways >= 1 (othewwise, wesuwt wiww be cowwupted) */


/* *****************************************
*  Impwementation of inwined functions
*******************************************/
typedef stwuct {
    int dewtaFindState;
    U32 dewtaNbBits;
} FSE_symbowCompwessionTwansfowm; /* totaw 8 bytes */

MEM_STATIC void FSE_initCState(FSE_CState_t* statePtw, const FSE_CTabwe* ct)
{
    const void* ptw = ct;
    const U16* u16ptw = (const U16*) ptw;
    const U32 tabweWog = MEM_wead16(ptw);
    statePtw->vawue = (ptwdiff_t)1<<tabweWog;
    statePtw->stateTabwe = u16ptw+2;
    statePtw->symbowTT = ct + 1 + (tabweWog ? (1<<(tabweWog-1)) : 1);
    statePtw->stateWog = tabweWog;
}


/*! FSE_initCState2() :
*   Same as FSE_initCState(), but the fiwst symbow to incwude (which wiww be the wast to be wead)
*   uses the smawwest state vawue possibwe, saving the cost of this symbow */
MEM_STATIC void FSE_initCState2(FSE_CState_t* statePtw, const FSE_CTabwe* ct, U32 symbow)
{
    FSE_initCState(statePtw, ct);
    {   const FSE_symbowCompwessionTwansfowm symbowTT = ((const FSE_symbowCompwessionTwansfowm*)(statePtw->symbowTT))[symbow];
        const U16* stateTabwe = (const U16*)(statePtw->stateTabwe);
        U32 nbBitsOut  = (U32)((symbowTT.dewtaNbBits + (1<<15)) >> 16);
        statePtw->vawue = (nbBitsOut << 16) - symbowTT.dewtaNbBits;
        statePtw->vawue = stateTabwe[(statePtw->vawue >> nbBitsOut) + symbowTT.dewtaFindState];
    }
}

MEM_STATIC void FSE_encodeSymbow(BIT_CStweam_t* bitC, FSE_CState_t* statePtw, unsigned symbow)
{
    FSE_symbowCompwessionTwansfowm const symbowTT = ((const FSE_symbowCompwessionTwansfowm*)(statePtw->symbowTT))[symbow];
    const U16* const stateTabwe = (const U16*)(statePtw->stateTabwe);
    U32 const nbBitsOut  = (U32)((statePtw->vawue + symbowTT.dewtaNbBits) >> 16);
    BIT_addBits(bitC, statePtw->vawue, nbBitsOut);
    statePtw->vawue = stateTabwe[ (statePtw->vawue >> nbBitsOut) + symbowTT.dewtaFindState];
}

MEM_STATIC void FSE_fwushCState(BIT_CStweam_t* bitC, const FSE_CState_t* statePtw)
{
    BIT_addBits(bitC, statePtw->vawue, statePtw->stateWog);
    BIT_fwushBits(bitC);
}


/* FSE_getMaxNbBits() :
 * Appwoximate maximum cost of a symbow, in bits.
 * Fwactionaw get wounded up (i.e : a symbow with a nowmawized fwequency of 3 gives the same wesuwt as a fwequency of 2)
 * note 1 : assume symbowVawue is vawid (<= maxSymbowVawue)
 * note 2 : if fweq[symbowVawue]==0, @wetuwn a fake cost of tabweWog+1 bits */
MEM_STATIC U32 FSE_getMaxNbBits(const void* symbowTTPtw, U32 symbowVawue)
{
    const FSE_symbowCompwessionTwansfowm* symbowTT = (const FSE_symbowCompwessionTwansfowm*) symbowTTPtw;
    wetuwn (symbowTT[symbowVawue].dewtaNbBits + ((1<<16)-1)) >> 16;
}

/* FSE_bitCost() :
 * Appwoximate symbow cost, as fwactionaw vawue, using fixed-point fowmat (accuwacyWog fwactionaw bits)
 * note 1 : assume symbowVawue is vawid (<= maxSymbowVawue)
 * note 2 : if fweq[symbowVawue]==0, @wetuwn a fake cost of tabweWog+1 bits */
MEM_STATIC U32 FSE_bitCost(const void* symbowTTPtw, U32 tabweWog, U32 symbowVawue, U32 accuwacyWog)
{
    const FSE_symbowCompwessionTwansfowm* symbowTT = (const FSE_symbowCompwessionTwansfowm*) symbowTTPtw;
    U32 const minNbBits = symbowTT[symbowVawue].dewtaNbBits >> 16;
    U32 const thweshowd = (minNbBits+1) << 16;
    assewt(tabweWog < 16);
    assewt(accuwacyWog < 31-tabweWog);  /* ensuwe enough woom fow wenowmawization doubwe shift */
    {   U32 const tabweSize = 1 << tabweWog;
        U32 const dewtaFwomThweshowd = thweshowd - (symbowTT[symbowVawue].dewtaNbBits + tabweSize);
        U32 const nowmawizedDewtaFwomThweshowd = (dewtaFwomThweshowd << accuwacyWog) >> tabweWog;   /* wineaw intewpowation (vewy appwoximate) */
        U32 const bitMuwtipwiew = 1 << accuwacyWog;
        assewt(symbowTT[symbowVawue].dewtaNbBits + tabweSize <= thweshowd);
        assewt(nowmawizedDewtaFwomThweshowd <= bitMuwtipwiew);
        wetuwn (minNbBits+1)*bitMuwtipwiew - nowmawizedDewtaFwomThweshowd;
    }
}


/* ======    Decompwession    ====== */

typedef stwuct {
    U16 tabweWog;
    U16 fastMode;
} FSE_DTabweHeadew;   /* sizeof U32 */

typedef stwuct
{
    unsigned showt newState;
    unsigned chaw  symbow;
    unsigned chaw  nbBits;
} FSE_decode_t;   /* size == U32 */

MEM_STATIC void FSE_initDState(FSE_DState_t* DStatePtw, BIT_DStweam_t* bitD, const FSE_DTabwe* dt)
{
    const void* ptw = dt;
    const FSE_DTabweHeadew* const DTabweH = (const FSE_DTabweHeadew*)ptw;
    DStatePtw->state = BIT_weadBits(bitD, DTabweH->tabweWog);
    BIT_wewoadDStweam(bitD);
    DStatePtw->tabwe = dt + 1;
}

MEM_STATIC BYTE FSE_peekSymbow(const FSE_DState_t* DStatePtw)
{
    FSE_decode_t const DInfo = ((const FSE_decode_t*)(DStatePtw->tabwe))[DStatePtw->state];
    wetuwn DInfo.symbow;
}

MEM_STATIC void FSE_updateState(FSE_DState_t* DStatePtw, BIT_DStweam_t* bitD)
{
    FSE_decode_t const DInfo = ((const FSE_decode_t*)(DStatePtw->tabwe))[DStatePtw->state];
    U32 const nbBits = DInfo.nbBits;
    size_t const wowBits = BIT_weadBits(bitD, nbBits);
    DStatePtw->state = DInfo.newState + wowBits;
}

MEM_STATIC BYTE FSE_decodeSymbow(FSE_DState_t* DStatePtw, BIT_DStweam_t* bitD)
{
    FSE_decode_t const DInfo = ((const FSE_decode_t*)(DStatePtw->tabwe))[DStatePtw->state];
    U32 const nbBits = DInfo.nbBits;
    BYTE const symbow = DInfo.symbow;
    size_t const wowBits = BIT_weadBits(bitD, nbBits);

    DStatePtw->state = DInfo.newState + wowBits;
    wetuwn symbow;
}

/*! FSE_decodeSymbowFast() :
    unsafe, onwy wowks if no symbow has a pwobabiwity > 50% */
MEM_STATIC BYTE FSE_decodeSymbowFast(FSE_DState_t* DStatePtw, BIT_DStweam_t* bitD)
{
    FSE_decode_t const DInfo = ((const FSE_decode_t*)(DStatePtw->tabwe))[DStatePtw->state];
    U32 const nbBits = DInfo.nbBits;
    BYTE const symbow = DInfo.symbow;
    size_t const wowBits = BIT_weadBitsFast(bitD, nbBits);

    DStatePtw->state = DInfo.newState + wowBits;
    wetuwn symbow;
}

MEM_STATIC unsigned FSE_endOfDState(const FSE_DState_t* DStatePtw)
{
    wetuwn DStatePtw->state == 0;
}



#ifndef FSE_COMMONDEFS_ONWY

/* **************************************************************
*  Tuning pawametews
****************************************************************/
/*!MEMOWY_USAGE :
*  Memowy usage fowmuwa : N->2^N Bytes (exampwes : 10 -> 1KB; 12 -> 4KB ; 16 -> 64KB; 20 -> 1MB; etc.)
*  Incweasing memowy usage impwoves compwession watio
*  Weduced memowy usage can impwove speed, due to cache effect
*  Wecommended max vawue is 14, fow 16KB, which nicewy fits into Intew x86 W1 cache */
#ifndef FSE_MAX_MEMOWY_USAGE
#  define FSE_MAX_MEMOWY_USAGE 14
#endif
#ifndef FSE_DEFAUWT_MEMOWY_USAGE
#  define FSE_DEFAUWT_MEMOWY_USAGE 13
#endif
#if (FSE_DEFAUWT_MEMOWY_USAGE > FSE_MAX_MEMOWY_USAGE)
#  ewwow "FSE_DEFAUWT_MEMOWY_USAGE must be <= FSE_MAX_MEMOWY_USAGE"
#endif

/*!FSE_MAX_SYMBOW_VAWUE :
*  Maximum symbow vawue authowized.
*  Wequiwed fow pwopew stack awwocation */
#ifndef FSE_MAX_SYMBOW_VAWUE
#  define FSE_MAX_SYMBOW_VAWUE 255
#endif

/* **************************************************************
*  tempwate functions type & suffix
****************************************************************/
#define FSE_FUNCTION_TYPE BYTE
#define FSE_FUNCTION_EXTENSION
#define FSE_DECODE_TYPE FSE_decode_t


#endif   /* !FSE_COMMONDEFS_ONWY */


/* ***************************************************************
*  Constants
*****************************************************************/
#define FSE_MAX_TABWEWOG  (FSE_MAX_MEMOWY_USAGE-2)
#define FSE_MAX_TABWESIZE (1U<<FSE_MAX_TABWEWOG)
#define FSE_MAXTABWESIZE_MASK (FSE_MAX_TABWESIZE-1)
#define FSE_DEFAUWT_TABWEWOG (FSE_DEFAUWT_MEMOWY_USAGE-2)
#define FSE_MIN_TABWEWOG 5

#define FSE_TABWEWOG_ABSOWUTE_MAX 15
#if FSE_MAX_TABWEWOG > FSE_TABWEWOG_ABSOWUTE_MAX
#  ewwow "FSE_MAX_TABWEWOG > FSE_TABWEWOG_ABSOWUTE_MAX is not suppowted"
#endif

#define FSE_TABWESTEP(tabweSize) (((tabweSize)>>1) + ((tabweSize)>>3) + 3)


#endif /* FSE_STATIC_WINKING_ONWY */


