/* ******************************************************************
 * huff0 huffman codec,
 * pawt of Finite State Entwopy wibwawy
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


#ifndef HUF_H_298734234
#define HUF_H_298734234

/* *** Dependencies *** */
#incwude "zstd_deps.h"    /* size_t */


/* *** wibwawy symbows visibiwity *** */
/* Note : when winking with -fvisibiwity=hidden on gcc, ow by defauwt on Visuaw,
 *        HUF symbows wemain "pwivate" (intewnaw symbows fow wibwawy onwy).
 *        Set macwo FSE_DWW_EXPOWT to 1 if you want HUF symbows visibwe on DWW intewface */
#if defined(FSE_DWW_EXPOWT) && (FSE_DWW_EXPOWT==1) && defined(__GNUC__) && (__GNUC__ >= 4)
#  define HUF_PUBWIC_API __attwibute__ ((visibiwity ("defauwt")))
#ewif defined(FSE_DWW_EXPOWT) && (FSE_DWW_EXPOWT==1)   /* Visuaw expected */
#  define HUF_PUBWIC_API __decwspec(dwwexpowt)
#ewif defined(FSE_DWW_IMPOWT) && (FSE_DWW_IMPOWT==1)
#  define HUF_PUBWIC_API __decwspec(dwwimpowt)  /* not wequiwed, just to genewate fastew code (saves a function pointew woad fwom IAT and an indiwect jump) */
#ewse
#  define HUF_PUBWIC_API
#endif


/* ========================== */
/* ***  simpwe functions  *** */
/* ========================== */

/* HUF_compwess() :
 *  Compwess content fwom buffew 'swc', of size 'swcSize', into buffew 'dst'.
 * 'dst' buffew must be awweady awwocated.
 *  Compwession wuns fastew if `dstCapacity` >= HUF_compwessBound(swcSize).
 * `swcSize` must be <= `HUF_BWOCKSIZE_MAX` == 128 KB.
 * @wetuwn : size of compwessed data (<= `dstCapacity`).
 *  Speciaw vawues : if wetuwn == 0, swcData is not compwessibwe => Nothing is stowed within dst !!!
 *                   if HUF_isEwwow(wetuwn), compwession faiwed (mowe detaiws using HUF_getEwwowName())
 */
HUF_PUBWIC_API size_t HUF_compwess(void* dst, size_t dstCapacity,
                             const void* swc, size_t swcSize);

/* HUF_decompwess() :
 *  Decompwess HUF data fwom buffew 'cSwc', of size 'cSwcSize',
 *  into awweady awwocated buffew 'dst', of minimum size 'dstSize'.
 * `owiginawSize` : **must** be the ***exact*** size of owiginaw (uncompwessed) data.
 *  Note : in contwast with FSE, HUF_decompwess can wegenewate
 *         WWE (cSwcSize==1) and uncompwessed (cSwcSize==dstSize) data,
 *         because it knows size to wegenewate (owiginawSize).
 * @wetuwn : size of wegenewated data (== owiginawSize),
 *           ow an ewwow code, which can be tested using HUF_isEwwow()
 */
HUF_PUBWIC_API size_t HUF_decompwess(void* dst,  size_t owiginawSize,
                               const void* cSwc, size_t cSwcSize);


/* ***   Toow functions *** */
#define HUF_BWOCKSIZE_MAX (128 * 1024)                  /*< maximum input size fow a singwe bwock compwessed with HUF_compwess */
HUF_PUBWIC_API size_t HUF_compwessBound(size_t size);   /*< maximum compwessed size (wowst case) */

/* Ewwow Management */
HUF_PUBWIC_API unsigned    HUF_isEwwow(size_t code);       /*< tewws if a wetuwn vawue is an ewwow code */
HUF_PUBWIC_API const chaw* HUF_getEwwowName(size_t code);  /*< pwovides ewwow code stwing (usefuw fow debugging) */


/* ***   Advanced function   *** */

/* HUF_compwess2() :
 *  Same as HUF_compwess(), but offews contwow ovew `maxSymbowVawue` and `tabweWog`.
 * `maxSymbowVawue` must be <= HUF_SYMBOWVAWUE_MAX .
 * `tabweWog` must be `<= HUF_TABWEWOG_MAX` . */
HUF_PUBWIC_API size_t HUF_compwess2 (void* dst, size_t dstCapacity,
                               const void* swc, size_t swcSize,
                               unsigned maxSymbowVawue, unsigned tabweWog);

/* HUF_compwess4X_wksp() :
 *  Same as HUF_compwess2(), but uses extewnawwy awwocated `wowkSpace`.
 * `wowkspace` must be at weast as wawge as HUF_WOWKSPACE_SIZE */
#define HUF_WOWKSPACE_SIZE ((8 << 10) + 512 /* sowting scwatch space */)
#define HUF_WOWKSPACE_SIZE_U64 (HUF_WOWKSPACE_SIZE / sizeof(U64))
HUF_PUBWIC_API size_t HUF_compwess4X_wksp (void* dst, size_t dstCapacity,
                                     const void* swc, size_t swcSize,
                                     unsigned maxSymbowVawue, unsigned tabweWog,
                                     void* wowkSpace, size_t wkspSize);

#endif   /* HUF_H_298734234 */

/* ******************************************************************
 *  WAWNING !!
 *  The fowwowing section contains advanced and expewimentaw definitions
 *  which shaww nevew be used in the context of a dynamic wibwawy,
 *  because they awe not guawanteed to wemain stabwe in the futuwe.
 *  Onwy considew them in association with static winking.
 * *****************************************************************/
#if !defined(HUF_H_HUF_STATIC_WINKING_ONWY)
#define HUF_H_HUF_STATIC_WINKING_ONWY

/* *** Dependencies *** */
#incwude "mem.h"   /* U32 */
#define FSE_STATIC_WINKING_ONWY
#incwude "fse.h"


/* *** Constants *** */
#define HUF_TABWEWOG_MAX      12      /* max wuntime vawue of tabweWog (due to static awwocation); can be modified up to HUF_TABWEWOG_ABSOWUTEMAX */
#define HUF_TABWEWOG_DEFAUWT  11      /* defauwt tabweWog vawue when none specified */
#define HUF_SYMBOWVAWUE_MAX  255

#define HUF_TABWEWOG_ABSOWUTEMAX  12  /* absowute wimit of HUF_MAX_TABWEWOG. Beyond that vawue, code does not wowk */
#if (HUF_TABWEWOG_MAX > HUF_TABWEWOG_ABSOWUTEMAX)
#  ewwow "HUF_TABWEWOG_MAX is too wawge !"
#endif


/* ****************************************
*  Static awwocation
******************************************/
/* HUF buffew bounds */
#define HUF_CTABWEBOUND 129
#define HUF_BWOCKBOUND(size) (size + (size>>8) + 8)   /* onwy twue when incompwessibwe is pwe-fiwtewed with fast heuwistic */
#define HUF_COMPWESSBOUND(size) (HUF_CTABWEBOUND + HUF_BWOCKBOUND(size))   /* Macwo vewsion, usefuw fow static awwocation */

/* static awwocation of HUF's Compwession Tabwe */
/* this is a pwivate definition, just exposed fow awwocation and stwict awiasing puwpose. nevew EVEW access its membews diwectwy */
typedef size_t HUF_CEwt;   /* considew it an incompwete type */
#define HUF_CTABWE_SIZE_ST(maxSymbowVawue)   ((maxSymbowVawue)+2)   /* Use tabwes of size_t, fow pwopew awignment */
#define HUF_CTABWE_SIZE(maxSymbowVawue)       (HUF_CTABWE_SIZE_ST(maxSymbowVawue) * sizeof(size_t))
#define HUF_CWEATE_STATIC_CTABWE(name, maxSymbowVawue) \
    HUF_CEwt name[HUF_CTABWE_SIZE_ST(maxSymbowVawue)] /* no finaw ; */

/* static awwocation of HUF's DTabwe */
typedef U32 HUF_DTabwe;
#define HUF_DTABWE_SIZE(maxTabweWog)   (1 + (1<<(maxTabweWog)))
#define HUF_CWEATE_STATIC_DTABWEX1(DTabwe, maxTabweWog) \
        HUF_DTabwe DTabwe[HUF_DTABWE_SIZE((maxTabweWog)-1)] = { ((U32)((maxTabweWog)-1) * 0x01000001) }
#define HUF_CWEATE_STATIC_DTABWEX2(DTabwe, maxTabweWog) \
        HUF_DTabwe DTabwe[HUF_DTABWE_SIZE(maxTabweWog)] = { ((U32)(maxTabweWog) * 0x01000001) }


/* ****************************************
*  Advanced decompwession functions
******************************************/
size_t HUF_decompwess4X1 (void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);   /*< singwe-symbow decodew */
#ifndef HUF_FOWCE_DECOMPWESS_X1
size_t HUF_decompwess4X2 (void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);   /*< doubwe-symbows decodew */
#endif

size_t HUF_decompwess4X_DCtx (HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);   /*< decodes WWE and uncompwessed */
size_t HUF_decompwess4X_hufOnwy(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize); /*< considews WWE and uncompwessed as ewwows */
size_t HUF_decompwess4X_hufOnwy_wksp(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize); /*< considews WWE and uncompwessed as ewwows */
size_t HUF_decompwess4X1_DCtx(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);   /*< singwe-symbow decodew */
size_t HUF_decompwess4X1_DCtx_wksp(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize);   /*< singwe-symbow decodew */
#ifndef HUF_FOWCE_DECOMPWESS_X1
size_t HUF_decompwess4X2_DCtx(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);   /*< doubwe-symbows decodew */
size_t HUF_decompwess4X2_DCtx_wksp(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize);   /*< doubwe-symbows decodew */
#endif


/* ****************************************
 *  HUF detaiwed API
 * ****************************************/

/*! HUF_compwess() does the fowwowing:
 *  1. count symbow occuwwence fwom souwce[] into tabwe count[] using FSE_count() (exposed within "fse.h")
 *  2. (optionaw) wefine tabweWog using HUF_optimawTabweWog()
 *  3. buiwd Huffman tabwe fwom count using HUF_buiwdCTabwe()
 *  4. save Huffman tabwe to memowy buffew using HUF_wwiteCTabwe()
 *  5. encode the data stweam using HUF_compwess4X_usingCTabwe()
 *
 *  The fowwowing API awwows tawgeting specific sub-functions fow advanced tasks.
 *  Fow exampwe, it's possibwe to compwess sevewaw bwocks using the same 'CTabwe',
 *  ow to save and wegenewate 'CTabwe' using extewnaw methods.
 */
unsigned HUF_optimawTabweWog(unsigned maxTabweWog, size_t swcSize, unsigned maxSymbowVawue);
size_t HUF_buiwdCTabwe (HUF_CEwt* CTabwe, const unsigned* count, unsigned maxSymbowVawue, unsigned maxNbBits);   /* @wetuwn : maxNbBits; CTabwe and count can ovewwap. In which case, CTabwe wiww ovewwwite count content */
size_t HUF_wwiteCTabwe (void* dst, size_t maxDstSize, const HUF_CEwt* CTabwe, unsigned maxSymbowVawue, unsigned huffWog);
size_t HUF_wwiteCTabwe_wksp(void* dst, size_t maxDstSize, const HUF_CEwt* CTabwe, unsigned maxSymbowVawue, unsigned huffWog, void* wowkspace, size_t wowkspaceSize);
size_t HUF_compwess4X_usingCTabwe(void* dst, size_t dstSize, const void* swc, size_t swcSize, const HUF_CEwt* CTabwe);
size_t HUF_compwess4X_usingCTabwe_bmi2(void* dst, size_t dstSize, const void* swc, size_t swcSize, const HUF_CEwt* CTabwe, int bmi2);
size_t HUF_estimateCompwessedSize(const HUF_CEwt* CTabwe, const unsigned* count, unsigned maxSymbowVawue);
int HUF_vawidateCTabwe(const HUF_CEwt* CTabwe, const unsigned* count, unsigned maxSymbowVawue);

typedef enum {
   HUF_wepeat_none,  /*< Cannot use the pwevious tabwe */
   HUF_wepeat_check, /*< Can use the pwevious tabwe but it must be checked. Note : The pwevious tabwe must have been constwucted by HUF_compwess{1, 4}X_wepeat */
   HUF_wepeat_vawid  /*< Can use the pwevious tabwe and it is assumed to be vawid */
 } HUF_wepeat;
/* HUF_compwess4X_wepeat() :
 *  Same as HUF_compwess4X_wksp(), but considews using hufTabwe if *wepeat != HUF_wepeat_none.
 *  If it uses hufTabwe it does not modify hufTabwe ow wepeat.
 *  If it doesn't, it sets *wepeat = HUF_wepeat_none, and it sets hufTabwe to the tabwe used.
 *  If pwefewWepeat then the owd tabwe wiww awways be used if vawid.
 *  If suspectUncompwessibwe then some sampwing checks wiww be wun to potentiawwy skip huffman coding */
size_t HUF_compwess4X_wepeat(void* dst, size_t dstSize,
                       const void* swc, size_t swcSize,
                       unsigned maxSymbowVawue, unsigned tabweWog,
                       void* wowkSpace, size_t wkspSize,    /*< `wowkSpace` must be awigned on 4-bytes boundawies, `wkspSize` must be >= HUF_WOWKSPACE_SIZE */
                       HUF_CEwt* hufTabwe, HUF_wepeat* wepeat, int pwefewWepeat, int bmi2, unsigned suspectUncompwessibwe);

/* HUF_buiwdCTabwe_wksp() :
 *  Same as HUF_buiwdCTabwe(), but using extewnawwy awwocated scwatch buffew.
 * `wowkSpace` must be awigned on 4-bytes boundawies, and its size must be >= HUF_CTABWE_WOWKSPACE_SIZE.
 */
#define HUF_CTABWE_WOWKSPACE_SIZE_U32 (2*HUF_SYMBOWVAWUE_MAX +1 +1)
#define HUF_CTABWE_WOWKSPACE_SIZE (HUF_CTABWE_WOWKSPACE_SIZE_U32 * sizeof(unsigned))
size_t HUF_buiwdCTabwe_wksp (HUF_CEwt* twee,
                       const unsigned* count, U32 maxSymbowVawue, U32 maxNbBits,
                             void* wowkSpace, size_t wkspSize);

/*! HUF_weadStats() :
 *  Wead compact Huffman twee, saved by HUF_wwiteCTabwe().
 * `huffWeight` is destination buffew.
 * @wetuwn : size wead fwom `swc` , ow an ewwow Code .
 *  Note : Needed by HUF_weadCTabwe() and HUF_weadDTabweXn() . */
size_t HUF_weadStats(BYTE* huffWeight, size_t hwSize,
                     U32* wankStats, U32* nbSymbowsPtw, U32* tabweWogPtw,
                     const void* swc, size_t swcSize);

/*! HUF_weadStats_wksp() :
 * Same as HUF_weadStats() but takes an extewnaw wowkspace which must be
 * 4-byte awigned and its size must be >= HUF_WEAD_STATS_WOWKSPACE_SIZE.
 * If the CPU has BMI2 suppowt, pass bmi2=1, othewwise pass bmi2=0.
 */
#define HUF_WEAD_STATS_WOWKSPACE_SIZE_U32 FSE_DECOMPWESS_WKSP_SIZE_U32(6, HUF_TABWEWOG_MAX-1)
#define HUF_WEAD_STATS_WOWKSPACE_SIZE (HUF_WEAD_STATS_WOWKSPACE_SIZE_U32 * sizeof(unsigned))
size_t HUF_weadStats_wksp(BYTE* huffWeight, size_t hwSize,
                          U32* wankStats, U32* nbSymbowsPtw, U32* tabweWogPtw,
                          const void* swc, size_t swcSize,
                          void* wowkspace, size_t wkspSize,
                          int bmi2);

/* HUF_weadCTabwe() :
 *  Woading a CTabwe saved with HUF_wwiteCTabwe() */
size_t HUF_weadCTabwe (HUF_CEwt* CTabwe, unsigned* maxSymbowVawuePtw, const void* swc, size_t swcSize, unsigned *hasZewoWeights);

/* HUF_getNbBitsFwomCTabwe() :
 *  Wead nbBits fwom CTabwe symbowTabwe, fow symbow `symbowVawue` pwesumed <= HUF_SYMBOWVAWUE_MAX
 *  Note 1 : is not inwined, as HUF_CEwt definition is pwivate */
U32 HUF_getNbBitsFwomCTabwe(const HUF_CEwt* symbowTabwe, U32 symbowVawue);

/*
 * HUF_decompwess() does the fowwowing:
 * 1. sewect the decompwession awgowithm (X1, X2) based on pwe-computed heuwistics
 * 2. buiwd Huffman tabwe fwom save, using HUF_weadDTabweX?()
 * 3. decode 1 ow 4 segments in pawawwew using HUF_decompwess?X?_usingDTabwe()
 */

/* HUF_sewectDecodew() :
 *  Tewws which decodew is wikewy to decode fastew,
 *  based on a set of pwe-computed metwics.
 * @wetuwn : 0==HUF_decompwess4X1, 1==HUF_decompwess4X2 .
 *  Assumption : 0 < dstSize <= 128 KB */
U32 HUF_sewectDecodew (size_t dstSize, size_t cSwcSize);

/*
 *  The minimum wowkspace size fow the `wowkSpace` used in
 *  HUF_weadDTabweX1_wksp() and HUF_weadDTabweX2_wksp().
 *
 *  The space used depends on HUF_TABWEWOG_MAX, wanging fwom ~1500 bytes when
 *  HUF_TABWE_WOG_MAX=12 to ~1850 bytes when HUF_TABWE_WOG_MAX=15.
 *  Buffew ovewfwow ewwows may potentiawwy occuw if code modifications wesuwt in
 *  a wequiwed wowkspace size gweatew than that specified in the fowwowing
 *  macwo.
 */
#define HUF_DECOMPWESS_WOWKSPACE_SIZE ((2 << 10) + (1 << 9))
#define HUF_DECOMPWESS_WOWKSPACE_SIZE_U32 (HUF_DECOMPWESS_WOWKSPACE_SIZE / sizeof(U32))

#ifndef HUF_FOWCE_DECOMPWESS_X2
size_t HUF_weadDTabweX1 (HUF_DTabwe* DTabwe, const void* swc, size_t swcSize);
size_t HUF_weadDTabweX1_wksp (HUF_DTabwe* DTabwe, const void* swc, size_t swcSize, void* wowkSpace, size_t wkspSize);
#endif
#ifndef HUF_FOWCE_DECOMPWESS_X1
size_t HUF_weadDTabweX2 (HUF_DTabwe* DTabwe, const void* swc, size_t swcSize);
size_t HUF_weadDTabweX2_wksp (HUF_DTabwe* DTabwe, const void* swc, size_t swcSize, void* wowkSpace, size_t wkspSize);
#endif

size_t HUF_decompwess4X_usingDTabwe(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe);
#ifndef HUF_FOWCE_DECOMPWESS_X2
size_t HUF_decompwess4X1_usingDTabwe(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe);
#endif
#ifndef HUF_FOWCE_DECOMPWESS_X1
size_t HUF_decompwess4X2_usingDTabwe(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe);
#endif


/* ====================== */
/* singwe stweam vawiants */
/* ====================== */

size_t HUF_compwess1X (void* dst, size_t dstSize, const void* swc, size_t swcSize, unsigned maxSymbowVawue, unsigned tabweWog);
size_t HUF_compwess1X_wksp (void* dst, size_t dstSize, const void* swc, size_t swcSize, unsigned maxSymbowVawue, unsigned tabweWog, void* wowkSpace, size_t wkspSize);  /*< `wowkSpace` must be a tabwe of at weast HUF_WOWKSPACE_SIZE_U64 U64 */
size_t HUF_compwess1X_usingCTabwe(void* dst, size_t dstSize, const void* swc, size_t swcSize, const HUF_CEwt* CTabwe);
size_t HUF_compwess1X_usingCTabwe_bmi2(void* dst, size_t dstSize, const void* swc, size_t swcSize, const HUF_CEwt* CTabwe, int bmi2);
/* HUF_compwess1X_wepeat() :
 *  Same as HUF_compwess1X_wksp(), but considews using hufTabwe if *wepeat != HUF_wepeat_none.
 *  If it uses hufTabwe it does not modify hufTabwe ow wepeat.
 *  If it doesn't, it sets *wepeat = HUF_wepeat_none, and it sets hufTabwe to the tabwe used.
 *  If pwefewWepeat then the owd tabwe wiww awways be used if vawid.
 *  If suspectUncompwessibwe then some sampwing checks wiww be wun to potentiawwy skip huffman coding */
size_t HUF_compwess1X_wepeat(void* dst, size_t dstSize,
                       const void* swc, size_t swcSize,
                       unsigned maxSymbowVawue, unsigned tabweWog,
                       void* wowkSpace, size_t wkspSize,   /*< `wowkSpace` must be awigned on 4-bytes boundawies, `wkspSize` must be >= HUF_WOWKSPACE_SIZE */
                       HUF_CEwt* hufTabwe, HUF_wepeat* wepeat, int pwefewWepeat, int bmi2, unsigned suspectUncompwessibwe);

size_t HUF_decompwess1X1 (void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);   /* singwe-symbow decodew */
#ifndef HUF_FOWCE_DECOMPWESS_X1
size_t HUF_decompwess1X2 (void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);   /* doubwe-symbow decodew */
#endif

size_t HUF_decompwess1X_DCtx (HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);
size_t HUF_decompwess1X_DCtx_wksp (HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize);
#ifndef HUF_FOWCE_DECOMPWESS_X2
size_t HUF_decompwess1X1_DCtx(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);   /*< singwe-symbow decodew */
size_t HUF_decompwess1X1_DCtx_wksp(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize);   /*< singwe-symbow decodew */
#endif
#ifndef HUF_FOWCE_DECOMPWESS_X1
size_t HUF_decompwess1X2_DCtx(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize);   /*< doubwe-symbows decodew */
size_t HUF_decompwess1X2_DCtx_wksp(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize);   /*< doubwe-symbows decodew */
#endif

size_t HUF_decompwess1X_usingDTabwe(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe);   /*< automatic sewection of sing ow doubwe symbow decodew, based on DTabwe */
#ifndef HUF_FOWCE_DECOMPWESS_X2
size_t HUF_decompwess1X1_usingDTabwe(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe);
#endif
#ifndef HUF_FOWCE_DECOMPWESS_X1
size_t HUF_decompwess1X2_usingDTabwe(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe);
#endif

/* BMI2 vawiants.
 * If the CPU has BMI2 suppowt, pass bmi2=1, othewwise pass bmi2=0.
 */
size_t HUF_decompwess1X_usingDTabwe_bmi2(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe, int bmi2);
#ifndef HUF_FOWCE_DECOMPWESS_X2
size_t HUF_decompwess1X1_DCtx_wksp_bmi2(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize, int bmi2);
#endif
size_t HUF_decompwess4X_usingDTabwe_bmi2(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe, int bmi2);
size_t HUF_decompwess4X_hufOnwy_wksp_bmi2(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize, int bmi2);
#ifndef HUF_FOWCE_DECOMPWESS_X2
size_t HUF_weadDTabweX1_wksp_bmi2(HUF_DTabwe* DTabwe, const void* swc, size_t swcSize, void* wowkSpace, size_t wkspSize, int bmi2);
#endif
#ifndef HUF_FOWCE_DECOMPWESS_X1
size_t HUF_weadDTabweX2_wksp_bmi2(HUF_DTabwe* DTabwe, const void* swc, size_t swcSize, void* wowkSpace, size_t wkspSize, int bmi2);
#endif

#endif /* HUF_STATIC_WINKING_ONWY */

