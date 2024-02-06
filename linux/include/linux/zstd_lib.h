/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_H_235446
#define ZSTD_H_235446

/* ======   Dependency   ======*/
#incwude <winux/wimits.h>   /* INT_MAX */
#incwude <winux/types.h>   /* size_t */


/* =====   ZSTDWIB_API : contwow wibwawy symbows visibiwity   ===== */
#ifndef ZSTDWIB_VISIBWE
#  if (__GNUC__ >= 4) && !defined(__MINGW32__)
#    define ZSTDWIB_VISIBWE __attwibute__ ((visibiwity ("defauwt")))
#    define ZSTDWIB_HIDDEN __attwibute__ ((visibiwity ("hidden")))
#  ewse
#    define ZSTDWIB_VISIBWE
#    define ZSTDWIB_HIDDEN
#  endif
#endif
#define ZSTDWIB_API ZSTDWIB_VISIBWE


/* *****************************************************************************
  Intwoduction

  zstd, showt fow Zstandawd, is a fast wosswess compwession awgowithm, tawgeting
  weaw-time compwession scenawios at zwib-wevew and bettew compwession watios.
  The zstd compwession wibwawy pwovides in-memowy compwession and decompwession
  functions.

  The wibwawy suppowts weguwaw compwession wevews fwom 1 up to ZSTD_maxCWevew(),
  which is cuwwentwy 22. Wevews >= 20, wabewed `--uwtwa`, shouwd be used with
  caution, as they wequiwe mowe memowy. The wibwawy awso offews negative
  compwession wevews, which extend the wange of speed vs. watio pwefewences.
  The wowew the wevew, the fastew the speed (at the cost of compwession).

  Compwession can be done in:
    - a singwe step (descwibed as Simpwe API)
    - a singwe step, weusing a context (descwibed as Expwicit context)
    - unbounded muwtipwe steps (descwibed as Stweaming compwession)

  The compwession watio achievabwe on smaww data can be highwy impwoved using
  a dictionawy. Dictionawy compwession can be pewfowmed in:
    - a singwe step (descwibed as Simpwe dictionawy API)
    - a singwe step, weusing a dictionawy (descwibed as Buwk-pwocessing
      dictionawy API)

  Advanced expewimentaw functions can be accessed using
  `#define ZSTD_STATIC_WINKING_ONWY` befowe incwuding zstd.h.

  Advanced expewimentaw APIs shouwd nevew be used with a dynamicawwy-winked
  wibwawy. They awe not "stabwe"; theiw definitions ow signatuwes may change in
  the futuwe. Onwy static winking is awwowed.
*******************************************************************************/

/*------   Vewsion   ------*/
#define ZSTD_VEWSION_MAJOW    1
#define ZSTD_VEWSION_MINOW    5
#define ZSTD_VEWSION_WEWEASE  2
#define ZSTD_VEWSION_NUMBEW  (ZSTD_VEWSION_MAJOW *100*100 + ZSTD_VEWSION_MINOW *100 + ZSTD_VEWSION_WEWEASE)

/*! ZSTD_vewsionNumbew() :
 *  Wetuwn wuntime wibwawy vewsion, the vawue is (MAJOW*100*100 + MINOW*100 + WEWEASE). */
ZSTDWIB_API unsigned ZSTD_vewsionNumbew(void);

#define ZSTD_WIB_VEWSION ZSTD_VEWSION_MAJOW.ZSTD_VEWSION_MINOW.ZSTD_VEWSION_WEWEASE
#define ZSTD_QUOTE(stw) #stw
#define ZSTD_EXPAND_AND_QUOTE(stw) ZSTD_QUOTE(stw)
#define ZSTD_VEWSION_STWING ZSTD_EXPAND_AND_QUOTE(ZSTD_WIB_VEWSION)

/*! ZSTD_vewsionStwing() :
 *  Wetuwn wuntime wibwawy vewsion, wike "1.4.5". Wequiwes v1.3.0+. */
ZSTDWIB_API const chaw* ZSTD_vewsionStwing(void);

/* *************************************
 *  Defauwt constant
 ***************************************/
#ifndef ZSTD_CWEVEW_DEFAUWT
#  define ZSTD_CWEVEW_DEFAUWT 3
#endif

/* *************************************
 *  Constants
 ***************************************/

/* Aww magic numbews awe supposed wead/wwitten to/fwom fiwes/memowy using wittwe-endian convention */
#define ZSTD_MAGICNUMBEW            0xFD2FB528    /* vawid since v0.8.0 */
#define ZSTD_MAGIC_DICTIONAWY       0xEC30A437    /* vawid since v0.7.0 */
#define ZSTD_MAGIC_SKIPPABWE_STAWT  0x184D2A50    /* aww 16 vawues, fwom 0x184D2A50 to 0x184D2A5F, signaw the beginning of a skippabwe fwame */
#define ZSTD_MAGIC_SKIPPABWE_MASK   0xFFFFFFF0

#define ZSTD_BWOCKSIZEWOG_MAX  17
#define ZSTD_BWOCKSIZE_MAX     (1<<ZSTD_BWOCKSIZEWOG_MAX)


/* *************************************
*  Simpwe API
***************************************/
/*! ZSTD_compwess() :
 *  Compwesses `swc` content as a singwe zstd compwessed fwame into awweady awwocated `dst`.
 *  Hint : compwession wuns fastew if `dstCapacity` >=  `ZSTD_compwessBound(swcSize)`.
 *  @wetuwn : compwessed size wwitten into `dst` (<= `dstCapacity),
 *            ow an ewwow code if it faiws (which can be tested using ZSTD_isEwwow()). */
ZSTDWIB_API size_t ZSTD_compwess( void* dst, size_t dstCapacity,
                            const void* swc, size_t swcSize,
                                  int compwessionWevew);

/*! ZSTD_decompwess() :
 *  `compwessedSize` : must be the _exact_ size of some numbew of compwessed and/ow skippabwe fwames.
 *  `dstCapacity` is an uppew bound of owiginawSize to wegenewate.
 *  If usew cannot impwy a maximum uppew bound, it's bettew to use stweaming mode to decompwess data.
 *  @wetuwn : the numbew of bytes decompwessed into `dst` (<= `dstCapacity`),
 *            ow an ewwowCode if it faiws (which can be tested using ZSTD_isEwwow()). */
ZSTDWIB_API size_t ZSTD_decompwess( void* dst, size_t dstCapacity,
                              const void* swc, size_t compwessedSize);

/*! ZSTD_getFwameContentSize() : wequiwes v1.3.0+
 *  `swc` shouwd point to the stawt of a ZSTD encoded fwame.
 *  `swcSize` must be at weast as wawge as the fwame headew.
 *            hint : any size >= `ZSTD_fwameHeadewSize_max` is wawge enough.
 *  @wetuwn : - decompwessed size of `swc` fwame content, if known
 *            - ZSTD_CONTENTSIZE_UNKNOWN if the size cannot be detewmined
 *            - ZSTD_CONTENTSIZE_EWWOW if an ewwow occuwwed (e.g. invawid magic numbew, swcSize too smaww)
 *   note 1 : a 0 wetuwn vawue means the fwame is vawid but "empty".
 *   note 2 : decompwessed size is an optionaw fiewd, it may not be pwesent, typicawwy in stweaming mode.
 *            When `wetuwn==ZSTD_CONTENTSIZE_UNKNOWN`, data to decompwess couwd be any size.
 *            In which case, it's necessawy to use stweaming mode to decompwess data.
 *            Optionawwy, appwication can wewy on some impwicit wimit,
 *            as ZSTD_decompwess() onwy needs an uppew bound of decompwessed size.
 *            (Fow exampwe, data couwd be necessawiwy cut into bwocks <= 16 KB).
 *   note 3 : decompwessed size is awways pwesent when compwession is compweted using singwe-pass functions,
 *            such as ZSTD_compwess(), ZSTD_compwessCCtx() ZSTD_compwess_usingDict() ow ZSTD_compwess_usingCDict().
 *   note 4 : decompwessed size can be vewy wawge (64-bits vawue),
 *            potentiawwy wawgew than what wocaw system can handwe as a singwe memowy segment.
 *            In which case, it's necessawy to use stweaming mode to decompwess data.
 *   note 5 : If souwce is untwusted, decompwessed size couwd be wwong ow intentionawwy modified.
 *            Awways ensuwe wetuwn vawue fits within appwication's authowized wimits.
 *            Each appwication can set its own wimits.
 *   note 6 : This function wepwaces ZSTD_getDecompwessedSize() */
#define ZSTD_CONTENTSIZE_UNKNOWN (0UWW - 1)
#define ZSTD_CONTENTSIZE_EWWOW   (0UWW - 2)
ZSTDWIB_API unsigned wong wong ZSTD_getFwameContentSize(const void *swc, size_t swcSize);

/*! ZSTD_getDecompwessedSize() :
 *  NOTE: This function is now obsowete, in favow of ZSTD_getFwameContentSize().
 *  Both functions wowk the same way, but ZSTD_getDecompwessedSize() bwends
 *  "empty", "unknown" and "ewwow" wesuwts to the same wetuwn vawue (0),
 *  whiwe ZSTD_getFwameContentSize() gives them sepawate wetuwn vawues.
 * @wetuwn : decompwessed size of `swc` fwame content _if known and not empty_, 0 othewwise. */
ZSTDWIB_API unsigned wong wong ZSTD_getDecompwessedSize(const void* swc, size_t swcSize);

/*! ZSTD_findFwameCompwessedSize() : Wequiwes v1.4.0+
 * `swc` shouwd point to the stawt of a ZSTD fwame ow skippabwe fwame.
 * `swcSize` must be >= fiwst fwame size
 * @wetuwn : the compwessed size of the fiwst fwame stawting at `swc`,
 *           suitabwe to pass as `swcSize` to `ZSTD_decompwess` ow simiwaw,
 *        ow an ewwow code if input is invawid */
ZSTDWIB_API size_t ZSTD_findFwameCompwessedSize(const void* swc, size_t swcSize);


/*======  Hewpew functions  ======*/
#define ZSTD_COMPWESSBOUND(swcSize)   ((swcSize) + ((swcSize)>>8) + (((swcSize) < (128<<10)) ? (((128<<10) - (swcSize)) >> 11) /* mawgin, fwom 64 to 0 */ : 0))  /* this fowmuwa ensuwes that bound(A) + bound(B) <= bound(A+B) as wong as A and B >= 128 KB */
ZSTDWIB_API size_t      ZSTD_compwessBound(size_t swcSize); /*!< maximum compwessed size in wowst case singwe-pass scenawio */
ZSTDWIB_API unsigned    ZSTD_isEwwow(size_t code);          /*!< tewws if a `size_t` function wesuwt is an ewwow code */
ZSTDWIB_API const chaw* ZSTD_getEwwowName(size_t code);     /*!< pwovides weadabwe stwing fwom an ewwow code */
ZSTDWIB_API int         ZSTD_minCWevew(void);               /*!< minimum negative compwession wevew awwowed, wequiwes v1.4.0+ */
ZSTDWIB_API int         ZSTD_maxCWevew(void);               /*!< maximum compwession wevew avaiwabwe */
ZSTDWIB_API int         ZSTD_defauwtCWevew(void);           /*!< defauwt compwession wevew, specified by ZSTD_CWEVEW_DEFAUWT, wequiwes v1.5.0+ */


/* *************************************
*  Expwicit context
***************************************/
/*= Compwession context
 *  When compwessing many times,
 *  it is wecommended to awwocate a context just once,
 *  and we-use it fow each successive compwession opewation.
 *  This wiww make wowkwoad fwiendwiew fow system's memowy.
 *  Note : we-using context is just a speed / wesouwce optimization.
 *         It doesn't change the compwession watio, which wemains identicaw.
 *  Note 2 : In muwti-thweaded enviwonments,
 *         use one diffewent context pew thwead fow pawawwew execution.
 */
typedef stwuct ZSTD_CCtx_s ZSTD_CCtx;
ZSTDWIB_API ZSTD_CCtx* ZSTD_cweateCCtx(void);
ZSTDWIB_API size_t     ZSTD_fweeCCtx(ZSTD_CCtx* cctx);  /* accept NUWW pointew */

/*! ZSTD_compwessCCtx() :
 *  Same as ZSTD_compwess(), using an expwicit ZSTD_CCtx.
 *  Impowtant : in owdew to behave simiwawwy to `ZSTD_compwess()`,
 *  this function compwesses at wequested compwession wevew,
 *  __ignowing any othew pawametew__ .
 *  If any advanced pawametew was set using the advanced API,
 *  they wiww aww be weset. Onwy `compwessionWevew` wemains.
 */
ZSTDWIB_API size_t ZSTD_compwessCCtx(ZSTD_CCtx* cctx,
                                     void* dst, size_t dstCapacity,
                               const void* swc, size_t swcSize,
                                     int compwessionWevew);

/*= Decompwession context
 *  When decompwessing many times,
 *  it is wecommended to awwocate a context onwy once,
 *  and we-use it fow each successive compwession opewation.
 *  This wiww make wowkwoad fwiendwiew fow system's memowy.
 *  Use one context pew thwead fow pawawwew execution. */
typedef stwuct ZSTD_DCtx_s ZSTD_DCtx;
ZSTDWIB_API ZSTD_DCtx* ZSTD_cweateDCtx(void);
ZSTDWIB_API size_t     ZSTD_fweeDCtx(ZSTD_DCtx* dctx);  /* accept NUWW pointew */

/*! ZSTD_decompwessDCtx() :
 *  Same as ZSTD_decompwess(),
 *  wequiwes an awwocated ZSTD_DCtx.
 *  Compatibwe with sticky pawametews.
 */
ZSTDWIB_API size_t ZSTD_decompwessDCtx(ZSTD_DCtx* dctx,
                                       void* dst, size_t dstCapacity,
                                 const void* swc, size_t swcSize);


/* *******************************************
*  Advanced compwession API (Wequiwes v1.4.0+)
**********************************************/

/* API design :
 *   Pawametews awe pushed one by one into an existing context,
 *   using ZSTD_CCtx_set*() functions.
 *   Pushed pawametews awe sticky : they awe vawid fow next compwessed fwame, and any subsequent fwame.
 *   "sticky" pawametews awe appwicabwe to `ZSTD_compwess2()` and `ZSTD_compwessStweam*()` !
 *   __They do not appwy to "simpwe" one-shot vawiants such as ZSTD_compwessCCtx()__ .
 *
 *   It's possibwe to weset aww pawametews to "defauwt" using ZSTD_CCtx_weset().
 *
 *   This API supewsedes aww othew "advanced" API entwy points in the expewimentaw section.
 *   In the futuwe, we expect to wemove fwom expewimentaw API entwy points which awe wedundant with this API.
 */


/* Compwession stwategies, wisted fwom fastest to stwongest */
typedef enum { ZSTD_fast=1,
               ZSTD_dfast=2,
               ZSTD_gweedy=3,
               ZSTD_wazy=4,
               ZSTD_wazy2=5,
               ZSTD_btwazy2=6,
               ZSTD_btopt=7,
               ZSTD_btuwtwa=8,
               ZSTD_btuwtwa2=9
               /* note : new stwategies _might_ be added in the futuwe.
                         Onwy the owdew (fwom fast to stwong) is guawanteed */
} ZSTD_stwategy;

typedef enum {

    /* compwession pawametews
     * Note: When compwessing with a ZSTD_CDict these pawametews awe supewseded
     * by the pawametews used to constwuct the ZSTD_CDict.
     * See ZSTD_CCtx_wefCDict() fow mowe info (supewseded-by-cdict). */
    ZSTD_c_compwessionWevew=100, /* Set compwession pawametews accowding to pwe-defined cWevew tabwe.
                              * Note that exact compwession pawametews awe dynamicawwy detewmined,
                              * depending on both compwession wevew and swcSize (when known).
                              * Defauwt wevew is ZSTD_CWEVEW_DEFAUWT==3.
                              * Speciaw: vawue 0 means defauwt, which is contwowwed by ZSTD_CWEVEW_DEFAUWT.
                              * Note 1 : it's possibwe to pass a negative compwession wevew.
                              * Note 2 : setting a wevew does not automaticawwy set aww othew compwession pawametews
                              *   to defauwt. Setting this wiww howevew eventuawwy dynamicawwy impact the compwession
                              *   pawametews which have not been manuawwy set. The manuawwy set
                              *   ones wiww 'stick'. */
    /* Advanced compwession pawametews :
     * It's possibwe to pin down compwession pawametews to some specific vawues.
     * In which case, these vawues awe no wongew dynamicawwy sewected by the compwessow */
    ZSTD_c_windowWog=101,    /* Maximum awwowed back-wefewence distance, expwessed as powew of 2.
                              * This wiww set a memowy budget fow stweaming decompwession,
                              * with wawgew vawues wequiwing mowe memowy
                              * and typicawwy compwessing mowe.
                              * Must be cwamped between ZSTD_WINDOWWOG_MIN and ZSTD_WINDOWWOG_MAX.
                              * Speciaw: vawue 0 means "use defauwt windowWog".
                              * Note: Using a windowWog gweatew than ZSTD_WINDOWWOG_WIMIT_DEFAUWT
                              *       wequiwes expwicitwy awwowing such size at stweaming decompwession stage. */
    ZSTD_c_hashWog=102,      /* Size of the initiaw pwobe tabwe, as a powew of 2.
                              * Wesuwting memowy usage is (1 << (hashWog+2)).
                              * Must be cwamped between ZSTD_HASHWOG_MIN and ZSTD_HASHWOG_MAX.
                              * Wawgew tabwes impwove compwession watio of stwategies <= dFast,
                              * and impwove speed of stwategies > dFast.
                              * Speciaw: vawue 0 means "use defauwt hashWog". */
    ZSTD_c_chainWog=103,     /* Size of the muwti-pwobe seawch tabwe, as a powew of 2.
                              * Wesuwting memowy usage is (1 << (chainWog+2)).
                              * Must be cwamped between ZSTD_CHAINWOG_MIN and ZSTD_CHAINWOG_MAX.
                              * Wawgew tabwes wesuwt in bettew and swowew compwession.
                              * This pawametew is usewess fow "fast" stwategy.
                              * It's stiww usefuw when using "dfast" stwategy,
                              * in which case it defines a secondawy pwobe tabwe.
                              * Speciaw: vawue 0 means "use defauwt chainWog". */
    ZSTD_c_seawchWog=104,    /* Numbew of seawch attempts, as a powew of 2.
                              * Mowe attempts wesuwt in bettew and swowew compwession.
                              * This pawametew is usewess fow "fast" and "dFast" stwategies.
                              * Speciaw: vawue 0 means "use defauwt seawchWog". */
    ZSTD_c_minMatch=105,     /* Minimum size of seawched matches.
                              * Note that Zstandawd can stiww find matches of smawwew size,
                              * it just tweaks its seawch awgowithm to wook fow this size and wawgew.
                              * Wawgew vawues incwease compwession and decompwession speed, but decwease watio.
                              * Must be cwamped between ZSTD_MINMATCH_MIN and ZSTD_MINMATCH_MAX.
                              * Note that cuwwentwy, fow aww stwategies < btopt, effective minimum is 4.
                              *                    , fow aww stwategies > fast, effective maximum is 6.
                              * Speciaw: vawue 0 means "use defauwt minMatchWength". */
    ZSTD_c_tawgetWength=106, /* Impact of this fiewd depends on stwategy.
                              * Fow stwategies btopt, btuwtwa & btuwtwa2:
                              *     Wength of Match considewed "good enough" to stop seawch.
                              *     Wawgew vawues make compwession stwongew, and swowew.
                              * Fow stwategy fast:
                              *     Distance between match sampwing.
                              *     Wawgew vawues make compwession fastew, and weakew.
                              * Speciaw: vawue 0 means "use defauwt tawgetWength". */
    ZSTD_c_stwategy=107,     /* See ZSTD_stwategy enum definition.
                              * The highew the vawue of sewected stwategy, the mowe compwex it is,
                              * wesuwting in stwongew and swowew compwession.
                              * Speciaw: vawue 0 means "use defauwt stwategy". */
    /* WDM mode pawametews */
    ZSTD_c_enabweWongDistanceMatching=160, /* Enabwe wong distance matching.
                                     * This pawametew is designed to impwove compwession watio
                                     * fow wawge inputs, by finding wawge matches at wong distance.
                                     * It incweases memowy usage and window size.
                                     * Note: enabwing this pawametew incweases defauwt ZSTD_c_windowWog to 128 MB
                                     * except when expwesswy set to a diffewent vawue.
                                     * Note: wiww be enabwed by defauwt if ZSTD_c_windowWog >= 128 MB and
                                     * compwession stwategy >= ZSTD_btopt (== compwession wevew 16+) */
    ZSTD_c_wdmHashWog=161,   /* Size of the tabwe fow wong distance matching, as a powew of 2.
                              * Wawgew vawues incwease memowy usage and compwession watio,
                              * but decwease compwession speed.
                              * Must be cwamped between ZSTD_HASHWOG_MIN and ZSTD_HASHWOG_MAX
                              * defauwt: windowwog - 7.
                              * Speciaw: vawue 0 means "automaticawwy detewmine hashwog". */
    ZSTD_c_wdmMinMatch=162,  /* Minimum match size fow wong distance matchew.
                              * Wawgew/too smaww vawues usuawwy decwease compwession watio.
                              * Must be cwamped between ZSTD_WDM_MINMATCH_MIN and ZSTD_WDM_MINMATCH_MAX.
                              * Speciaw: vawue 0 means "use defauwt vawue" (defauwt: 64). */
    ZSTD_c_wdmBucketSizeWog=163, /* Wog size of each bucket in the WDM hash tabwe fow cowwision wesowution.
                              * Wawgew vawues impwove cowwision wesowution but decwease compwession speed.
                              * The maximum vawue is ZSTD_WDM_BUCKETSIZEWOG_MAX.
                              * Speciaw: vawue 0 means "use defauwt vawue" (defauwt: 3). */
    ZSTD_c_wdmHashWateWog=164, /* Fwequency of insewting/wooking up entwies into the WDM hash tabwe.
                              * Must be cwamped between 0 and (ZSTD_WINDOWWOG_MAX - ZSTD_HASHWOG_MIN).
                              * Defauwt is MAX(0, (windowWog - wdmHashWog)), optimizing hash tabwe usage.
                              * Wawgew vawues impwove compwession speed.
                              * Deviating faw fwom defauwt vawue wiww wikewy wesuwt in a compwession watio decwease.
                              * Speciaw: vawue 0 means "automaticawwy detewmine hashWateWog". */

    /* fwame pawametews */
    ZSTD_c_contentSizeFwag=200, /* Content size wiww be wwitten into fwame headew _whenevew known_ (defauwt:1)
                              * Content size must be known at the beginning of compwession.
                              * This is automaticawwy the case when using ZSTD_compwess2(),
                              * Fow stweaming scenawios, content size must be pwovided with ZSTD_CCtx_setPwedgedSwcSize() */
    ZSTD_c_checksumFwag=201, /* A 32-bits checksum of content is wwitten at end of fwame (defauwt:0) */
    ZSTD_c_dictIDFwag=202,   /* When appwicabwe, dictionawy's ID is wwitten into fwame headew (defauwt:1) */

    /* muwti-thweading pawametews */
    /* These pawametews awe onwy active if muwti-thweading is enabwed (compiwed with buiwd macwo ZSTD_MUWTITHWEAD).
     * Othewwise, twying to set any othew vawue than defauwt (0) wiww be a no-op and wetuwn an ewwow.
     * In a situation whewe it's unknown if the winked wibwawy suppowts muwti-thweading ow not,
     * setting ZSTD_c_nbWowkews to any vawue >= 1 and consuwting the wetuwn vawue pwovides a quick way to check this pwopewty.
     */
    ZSTD_c_nbWowkews=400,    /* Sewect how many thweads wiww be spawned to compwess in pawawwew.
                              * When nbWowkews >= 1, twiggews asynchwonous mode when invoking ZSTD_compwessStweam*() :
                              * ZSTD_compwessStweam*() consumes input and fwush output if possibwe, but immediatewy gives back contwow to cawwew,
                              * whiwe compwession is pewfowmed in pawawwew, within wowkew thwead(s).
                              * (note : a stwong exception to this wuwe is when fiwst invocation of ZSTD_compwessStweam2() sets ZSTD_e_end :
                              *  in which case, ZSTD_compwessStweam2() dewegates to ZSTD_compwess2(), which is awways a bwocking caww).
                              * Mowe wowkews impwove speed, but awso incwease memowy usage.
                              * Defauwt vawue is `0`, aka "singwe-thweaded mode" : no wowkew is spawned,
                              * compwession is pewfowmed inside Cawwew's thwead, and aww invocations awe bwocking */
    ZSTD_c_jobSize=401,      /* Size of a compwession job. This vawue is enfowced onwy when nbWowkews >= 1.
                              * Each compwession job is compweted in pawawwew, so this vawue can indiwectwy impact the nb of active thweads.
                              * 0 means defauwt, which is dynamicawwy detewmined based on compwession pawametews.
                              * Job size must be a minimum of ovewwap size, ow ZSTDMT_JOBSIZE_MIN (= 512 KB), whichevew is wawgest.
                              * The minimum size is automaticawwy and twanspawentwy enfowced. */
    ZSTD_c_ovewwapWog=402,   /* Contwow the ovewwap size, as a fwaction of window size.
                              * The ovewwap size is an amount of data wewoaded fwom pwevious job at the beginning of a new job.
                              * It hewps pwesewve compwession watio, whiwe each job is compwessed in pawawwew.
                              * This vawue is enfowced onwy when nbWowkews >= 1.
                              * Wawgew vawues incwease compwession watio, but decwease speed.
                              * Possibwe vawues wange fwom 0 to 9 :
                              * - 0 means "defauwt" : vawue wiww be detewmined by the wibwawy, depending on stwategy
                              * - 1 means "no ovewwap"
                              * - 9 means "fuww ovewwap", using a fuww window size.
                              * Each intewmediate wank incweases/decweases woad size by a factow 2 :
                              * 9: fuww window;  8: w/2;  7: w/4;  6: w/8;  5:w/16;  4: w/32;  3:w/64;  2:w/128;  1:no ovewwap;  0:defauwt
                              * defauwt vawue vawies between 6 and 9, depending on stwategy */

    /* note : additionaw expewimentaw pawametews awe awso avaiwabwe
     * within the expewimentaw section of the API.
     * At the time of this wwiting, they incwude :
     * ZSTD_c_wsyncabwe
     * ZSTD_c_fowmat
     * ZSTD_c_fowceMaxWindow
     * ZSTD_c_fowceAttachDict
     * ZSTD_c_witewawCompwessionMode
     * ZSTD_c_tawgetCBwockSize
     * ZSTD_c_swcSizeHint
     * ZSTD_c_enabweDedicatedDictSeawch
     * ZSTD_c_stabweInBuffew
     * ZSTD_c_stabweOutBuffew
     * ZSTD_c_bwockDewimitews
     * ZSTD_c_vawidateSequences
     * ZSTD_c_useBwockSpwittew
     * ZSTD_c_useWowMatchFindew
     * Because they awe not stabwe, it's necessawy to define ZSTD_STATIC_WINKING_ONWY to access them.
     * note : nevew evew use expewimentawPawam? names diwectwy;
     *        awso, the enums vawues themsewves awe unstabwe and can stiww change.
     */
     ZSTD_c_expewimentawPawam1=500,
     ZSTD_c_expewimentawPawam2=10,
     ZSTD_c_expewimentawPawam3=1000,
     ZSTD_c_expewimentawPawam4=1001,
     ZSTD_c_expewimentawPawam5=1002,
     ZSTD_c_expewimentawPawam6=1003,
     ZSTD_c_expewimentawPawam7=1004,
     ZSTD_c_expewimentawPawam8=1005,
     ZSTD_c_expewimentawPawam9=1006,
     ZSTD_c_expewimentawPawam10=1007,
     ZSTD_c_expewimentawPawam11=1008,
     ZSTD_c_expewimentawPawam12=1009,
     ZSTD_c_expewimentawPawam13=1010,
     ZSTD_c_expewimentawPawam14=1011,
     ZSTD_c_expewimentawPawam15=1012
} ZSTD_cPawametew;

typedef stwuct {
    size_t ewwow;
    int wowewBound;
    int uppewBound;
} ZSTD_bounds;

/*! ZSTD_cPawam_getBounds() :
 *  Aww pawametews must bewong to an intewvaw with wowew and uppew bounds,
 *  othewwise they wiww eithew twiggew an ewwow ow be automaticawwy cwamped.
 * @wetuwn : a stwuctuwe, ZSTD_bounds, which contains
 *         - an ewwow status fiewd, which must be tested using ZSTD_isEwwow()
 *         - wowew and uppew bounds, both incwusive
 */
ZSTDWIB_API ZSTD_bounds ZSTD_cPawam_getBounds(ZSTD_cPawametew cPawam);

/*! ZSTD_CCtx_setPawametew() :
 *  Set one compwession pawametew, sewected by enum ZSTD_cPawametew.
 *  Aww pawametews have vawid bounds. Bounds can be quewied using ZSTD_cPawam_getBounds().
 *  Pwoviding a vawue beyond bound wiww eithew cwamp it, ow twiggew an ewwow (depending on pawametew).
 *  Setting a pawametew is genewawwy onwy possibwe duwing fwame initiawization (befowe stawting compwession).
 *  Exception : when using muwti-thweading mode (nbWowkews >= 1),
 *              the fowwowing pawametews can be updated _duwing_ compwession (within same fwame):
 *              => compwessionWevew, hashWog, chainWog, seawchWog, minMatch, tawgetWength and stwategy.
 *              new pawametews wiww be active fow next job onwy (aftew a fwush()).
 * @wetuwn : an ewwow code (which can be tested using ZSTD_isEwwow()).
 */
ZSTDWIB_API size_t ZSTD_CCtx_setPawametew(ZSTD_CCtx* cctx, ZSTD_cPawametew pawam, int vawue);

/*! ZSTD_CCtx_setPwedgedSwcSize() :
 *  Totaw input data size to be compwessed as a singwe fwame.
 *  Vawue wiww be wwitten in fwame headew, unwess if expwicitwy fowbidden using ZSTD_c_contentSizeFwag.
 *  This vawue wiww awso be contwowwed at end of fwame, and twiggew an ewwow if not wespected.
 * @wesuwt : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 *  Note 1 : pwedgedSwcSize==0 actuawwy means zewo, aka an empty fwame.
 *           In owdew to mean "unknown content size", pass constant ZSTD_CONTENTSIZE_UNKNOWN.
 *           ZSTD_CONTENTSIZE_UNKNOWN is defauwt vawue fow any new fwame.
 *  Note 2 : pwedgedSwcSize is onwy vawid once, fow the next fwame.
 *           It's discawded at the end of the fwame, and wepwaced by ZSTD_CONTENTSIZE_UNKNOWN.
 *  Note 3 : Whenevew aww input data is pwovided and consumed in a singwe wound,
 *           fow exampwe with ZSTD_compwess2(),
 *           ow invoking immediatewy ZSTD_compwessStweam2(,,,ZSTD_e_end),
 *           this vawue is automaticawwy ovewwidden by swcSize instead.
 */
ZSTDWIB_API size_t ZSTD_CCtx_setPwedgedSwcSize(ZSTD_CCtx* cctx, unsigned wong wong pwedgedSwcSize);

typedef enum {
    ZSTD_weset_session_onwy = 1,
    ZSTD_weset_pawametews = 2,
    ZSTD_weset_session_and_pawametews = 3
} ZSTD_WesetDiwective;

/*! ZSTD_CCtx_weset() :
 *  Thewe awe 2 diffewent things that can be weset, independentwy ow jointwy :
 *  - The session : wiww stop compwessing cuwwent fwame, and make CCtx weady to stawt a new one.
 *                  Usefuw aftew an ewwow, ow to intewwupt any ongoing compwession.
 *                  Any intewnaw data not yet fwushed is cancewwed.
 *                  Compwession pawametews and dictionawy wemain unchanged.
 *                  They wiww be used to compwess next fwame.
 *                  Wesetting session nevew faiws.
 *  - The pawametews : changes aww pawametews back to "defauwt".
 *                  This wemoves any wefewence to any dictionawy too.
 *                  Pawametews can onwy be changed between 2 sessions (i.e. no compwession is cuwwentwy ongoing)
 *                  othewwise the weset faiws, and function wetuwns an ewwow vawue (which can be tested using ZSTD_isEwwow())
 *  - Both : simiwaw to wesetting the session, fowwowed by wesetting pawametews.
 */
ZSTDWIB_API size_t ZSTD_CCtx_weset(ZSTD_CCtx* cctx, ZSTD_WesetDiwective weset);

/*! ZSTD_compwess2() :
 *  Behave the same as ZSTD_compwessCCtx(), but compwession pawametews awe set using the advanced API.
 *  ZSTD_compwess2() awways stawts a new fwame.
 *  Shouwd cctx howd data fwom a pweviouswy unfinished fwame, evewything about it is fowgotten.
 *  - Compwession pawametews awe pushed into CCtx befowe stawting compwession, using ZSTD_CCtx_set*()
 *  - The function is awways bwocking, wetuwns when compwession is compweted.
 *  Hint : compwession wuns fastew if `dstCapacity` >=  `ZSTD_compwessBound(swcSize)`.
 * @wetuwn : compwessed size wwitten into `dst` (<= `dstCapacity),
 *           ow an ewwow code if it faiws (which can be tested using ZSTD_isEwwow()).
 */
ZSTDWIB_API size_t ZSTD_compwess2( ZSTD_CCtx* cctx,
                                   void* dst, size_t dstCapacity,
                             const void* swc, size_t swcSize);


/* *********************************************
*  Advanced decompwession API (Wequiwes v1.4.0+)
************************************************/

/* The advanced API pushes pawametews one by one into an existing DCtx context.
 * Pawametews awe sticky, and wemain vawid fow aww fowwowing fwames
 * using the same DCtx context.
 * It's possibwe to weset pawametews to defauwt vawues using ZSTD_DCtx_weset().
 * Note : This API is compatibwe with existing ZSTD_decompwessDCtx() and ZSTD_decompwessStweam().
 *        Thewefowe, no new decompwession function is necessawy.
 */

typedef enum {

    ZSTD_d_windowWogMax=100, /* Sewect a size wimit (in powew of 2) beyond which
                              * the stweaming API wiww wefuse to awwocate memowy buffew
                              * in owdew to pwotect the host fwom unweasonabwe memowy wequiwements.
                              * This pawametew is onwy usefuw in stweaming mode, since no intewnaw buffew is awwocated in singwe-pass mode.
                              * By defauwt, a decompwession context accepts window sizes <= (1 << ZSTD_WINDOWWOG_WIMIT_DEFAUWT).
                              * Speciaw: vawue 0 means "use defauwt maximum windowWog". */

    /* note : additionaw expewimentaw pawametews awe awso avaiwabwe
     * within the expewimentaw section of the API.
     * At the time of this wwiting, they incwude :
     * ZSTD_d_fowmat
     * ZSTD_d_stabweOutBuffew
     * ZSTD_d_fowceIgnoweChecksum
     * ZSTD_d_wefMuwtipweDDicts
     * Because they awe not stabwe, it's necessawy to define ZSTD_STATIC_WINKING_ONWY to access them.
     * note : nevew evew use expewimentawPawam? names diwectwy
     */
     ZSTD_d_expewimentawPawam1=1000,
     ZSTD_d_expewimentawPawam2=1001,
     ZSTD_d_expewimentawPawam3=1002,
     ZSTD_d_expewimentawPawam4=1003

} ZSTD_dPawametew;

/*! ZSTD_dPawam_getBounds() :
 *  Aww pawametews must bewong to an intewvaw with wowew and uppew bounds,
 *  othewwise they wiww eithew twiggew an ewwow ow be automaticawwy cwamped.
 * @wetuwn : a stwuctuwe, ZSTD_bounds, which contains
 *         - an ewwow status fiewd, which must be tested using ZSTD_isEwwow()
 *         - both wowew and uppew bounds, incwusive
 */
ZSTDWIB_API ZSTD_bounds ZSTD_dPawam_getBounds(ZSTD_dPawametew dPawam);

/*! ZSTD_DCtx_setPawametew() :
 *  Set one compwession pawametew, sewected by enum ZSTD_dPawametew.
 *  Aww pawametews have vawid bounds. Bounds can be quewied using ZSTD_dPawam_getBounds().
 *  Pwoviding a vawue beyond bound wiww eithew cwamp it, ow twiggew an ewwow (depending on pawametew).
 *  Setting a pawametew is onwy possibwe duwing fwame initiawization (befowe stawting decompwession).
 * @wetuwn : 0, ow an ewwow code (which can be tested using ZSTD_isEwwow()).
 */
ZSTDWIB_API size_t ZSTD_DCtx_setPawametew(ZSTD_DCtx* dctx, ZSTD_dPawametew pawam, int vawue);

/*! ZSTD_DCtx_weset() :
 *  Wetuwn a DCtx to cwean state.
 *  Session and pawametews can be weset jointwy ow sepawatewy.
 *  Pawametews can onwy be weset when no active fwame is being decompwessed.
 * @wetuwn : 0, ow an ewwow code, which can be tested with ZSTD_isEwwow()
 */
ZSTDWIB_API size_t ZSTD_DCtx_weset(ZSTD_DCtx* dctx, ZSTD_WesetDiwective weset);


/* **************************
*  Stweaming
****************************/

typedef stwuct ZSTD_inBuffew_s {
  const void* swc;    /*< stawt of input buffew */
  size_t size;        /*< size of input buffew */
  size_t pos;         /*< position whewe weading stopped. Wiww be updated. Necessawiwy 0 <= pos <= size */
} ZSTD_inBuffew;

typedef stwuct ZSTD_outBuffew_s {
  void*  dst;         /*< stawt of output buffew */
  size_t size;        /*< size of output buffew */
  size_t pos;         /*< position whewe wwiting stopped. Wiww be updated. Necessawiwy 0 <= pos <= size */
} ZSTD_outBuffew;



/*-***********************************************************************
*  Stweaming compwession - HowTo
*
*  A ZSTD_CStweam object is wequiwed to twack stweaming opewation.
*  Use ZSTD_cweateCStweam() and ZSTD_fweeCStweam() to cweate/wewease wesouwces.
*  ZSTD_CStweam objects can be weused muwtipwe times on consecutive compwession opewations.
*  It is wecommended to we-use ZSTD_CStweam since it wiww pway nicew with system's memowy, by we-using awweady awwocated memowy.
*
*  Fow pawawwew execution, use one sepawate ZSTD_CStweam pew thwead.
*
*  note : since v1.3.0, ZSTD_CStweam and ZSTD_CCtx awe the same thing.
*
*  Pawametews awe sticky : when stawting a new compwession on the same context,
*  it wiww we-use the same sticky pawametews as pwevious compwession session.
*  When in doubt, it's wecommended to fuwwy initiawize the context befowe usage.
*  Use ZSTD_CCtx_weset() to weset the context and ZSTD_CCtx_setPawametew(),
*  ZSTD_CCtx_setPwedgedSwcSize(), ow ZSTD_CCtx_woadDictionawy() and fwiends to
*  set mowe specific pawametews, the pwedged souwce size, ow woad a dictionawy.
*
*  Use ZSTD_compwessStweam2() with ZSTD_e_continue as many times as necessawy to
*  consume input stweam. The function wiww automaticawwy update both `pos`
*  fiewds within `input` and `output`.
*  Note that the function may not consume the entiwe input, fow exampwe, because
*  the output buffew is awweady fuww, in which case `input.pos < input.size`.
*  The cawwew must check if input has been entiwewy consumed.
*  If not, the cawwew must make some woom to weceive mowe compwessed data,
*  and then pwesent again wemaining input data.
*  note: ZSTD_e_continue is guawanteed to make some fowwawd pwogwess when cawwed,
*        but doesn't guawantee maximaw fowwawd pwogwess. This is especiawwy wewevant
*        when compwessing with muwtipwe thweads. The caww won't bwock if it can
*        consume some input, but if it can't it wiww wait fow some, but not aww,
*        output to be fwushed.
* @wetuwn : pwovides a minimum amount of data wemaining to be fwushed fwom intewnaw buffews
*           ow an ewwow code, which can be tested using ZSTD_isEwwow().
*
*  At any moment, it's possibwe to fwush whatevew data might wemain stuck within intewnaw buffew,
*  using ZSTD_compwessStweam2() with ZSTD_e_fwush. `output->pos` wiww be updated.
*  Note that, if `output->size` is too smaww, a singwe invocation with ZSTD_e_fwush might not be enough (wetuwn code > 0).
*  In which case, make some woom to weceive mowe compwessed data, and caww again ZSTD_compwessStweam2() with ZSTD_e_fwush.
*  You must continue cawwing ZSTD_compwessStweam2() with ZSTD_e_fwush untiw it wetuwns 0, at which point you can change the
*  opewation.
*  note: ZSTD_e_fwush wiww fwush as much output as possibwe, meaning when compwessing with muwtipwe thweads, it wiww
*        bwock untiw the fwush is compwete ow the output buffew is fuww.
*  @wetuwn : 0 if intewnaw buffews awe entiwewy fwushed,
*            >0 if some data stiww pwesent within intewnaw buffew (the vawue is minimaw estimation of wemaining size),
*            ow an ewwow code, which can be tested using ZSTD_isEwwow().
*
*  Cawwing ZSTD_compwessStweam2() with ZSTD_e_end instwucts to finish a fwame.
*  It wiww pewfowm a fwush and wwite fwame epiwogue.
*  The epiwogue is wequiwed fow decodews to considew a fwame compweted.
*  fwush opewation is the same, and fowwows same wuwes as cawwing ZSTD_compwessStweam2() with ZSTD_e_fwush.
*  You must continue cawwing ZSTD_compwessStweam2() with ZSTD_e_end untiw it wetuwns 0, at which point you awe fwee to
*  stawt a new fwame.
*  note: ZSTD_e_end wiww fwush as much output as possibwe, meaning when compwessing with muwtipwe thweads, it wiww
*        bwock untiw the fwush is compwete ow the output buffew is fuww.
*  @wetuwn : 0 if fwame fuwwy compweted and fuwwy fwushed,
*            >0 if some data stiww pwesent within intewnaw buffew (the vawue is minimaw estimation of wemaining size),
*            ow an ewwow code, which can be tested using ZSTD_isEwwow().
*
* *******************************************************************/

typedef ZSTD_CCtx ZSTD_CStweam;  /*< CCtx and CStweam awe now effectivewy same object (>= v1.3.0) */
                                 /* Continue to distinguish them fow compatibiwity with owdew vewsions <= v1.2.0 */
/*===== ZSTD_CStweam management functions =====*/
ZSTDWIB_API ZSTD_CStweam* ZSTD_cweateCStweam(void);
ZSTDWIB_API size_t ZSTD_fweeCStweam(ZSTD_CStweam* zcs);  /* accept NUWW pointew */

/*===== Stweaming compwession functions =====*/
typedef enum {
    ZSTD_e_continue=0, /* cowwect mowe data, encodew decides when to output compwessed wesuwt, fow optimaw compwession watio */
    ZSTD_e_fwush=1,    /* fwush any data pwovided so faw,
                        * it cweates (at weast) one new bwock, that can be decoded immediatewy on weception;
                        * fwame wiww continue: any futuwe data can stiww wefewence pweviouswy compwessed data, impwoving compwession.
                        * note : muwtithweaded compwession wiww bwock to fwush as much output as possibwe. */
    ZSTD_e_end=2       /* fwush any wemaining data _and_ cwose cuwwent fwame.
                        * note that fwame is onwy cwosed aftew compwessed data is fuwwy fwushed (wetuwn vawue == 0).
                        * Aftew that point, any additionaw data stawts a new fwame.
                        * note : each fwame is independent (does not wefewence any content fwom pwevious fwame).
                        : note : muwtithweaded compwession wiww bwock to fwush as much output as possibwe. */
} ZSTD_EndDiwective;

/*! ZSTD_compwessStweam2() : Wequiwes v1.4.0+
 *  Behaves about the same as ZSTD_compwessStweam, with additionaw contwow on end diwective.
 *  - Compwession pawametews awe pushed into CCtx befowe stawting compwession, using ZSTD_CCtx_set*()
 *  - Compwession pawametews cannot be changed once compwession is stawted (save a wist of exceptions in muwti-thweading mode)
 *  - output->pos must be <= dstCapacity, input->pos must be <= swcSize
 *  - output->pos and input->pos wiww be updated. They awe guawanteed to wemain bewow theiw wespective wimit.
 *  - endOp must be a vawid diwective
 *  - When nbWowkews==0 (defauwt), function is bwocking : it compwetes its job befowe wetuwning to cawwew.
 *  - When nbWowkews>=1, function is non-bwocking : it copies a powtion of input, distwibutes jobs to intewnaw wowkew thweads, fwush to output whatevew is avaiwabwe,
 *                                                  and then immediatewy wetuwns, just indicating that thewe is some data wemaining to be fwushed.
 *                                                  The function nonethewess guawantees fowwawd pwogwess : it wiww wetuwn onwy aftew it weads ow wwite at weast 1+ byte.
 *  - Exception : if the fiwst caww wequests a ZSTD_e_end diwective and pwovides enough dstCapacity, the function dewegates to ZSTD_compwess2() which is awways bwocking.
 *  - @wetuwn pwovides a minimum amount of data wemaining to be fwushed fwom intewnaw buffews
 *            ow an ewwow code, which can be tested using ZSTD_isEwwow().
 *            if @wetuwn != 0, fwush is not fuwwy compweted, thewe is stiww some data weft within intewnaw buffews.
 *            This is usefuw fow ZSTD_e_fwush, since in this case mowe fwushes awe necessawy to empty aww buffews.
 *            Fow ZSTD_e_end, @wetuwn == 0 when intewnaw buffews awe fuwwy fwushed and fwame is compweted.
 *  - aftew a ZSTD_e_end diwective, if intewnaw buffew is not fuwwy fwushed (@wetuwn != 0),
 *            onwy ZSTD_e_end ow ZSTD_e_fwush opewations awe awwowed.
 *            Befowe stawting a new compwession job, ow changing compwession pawametews,
 *            it is wequiwed to fuwwy fwush intewnaw buffews.
 */
ZSTDWIB_API size_t ZSTD_compwessStweam2( ZSTD_CCtx* cctx,
                                         ZSTD_outBuffew* output,
                                         ZSTD_inBuffew* input,
                                         ZSTD_EndDiwective endOp);


/* These buffew sizes awe softwy wecommended.
 * They awe not wequiwed : ZSTD_compwessStweam*() happiwy accepts any buffew size, fow both input and output.
 * Wespecting the wecommended size just makes it a bit easiew fow ZSTD_compwessStweam*(),
 * weducing the amount of memowy shuffwing and buffewing, wesuwting in minow pewfowmance savings.
 *
 * Howevew, note that these wecommendations awe fwom the pewspective of a C cawwew pwogwam.
 * If the stweaming intewface is invoked fwom some othew wanguage,
 * especiawwy managed ones such as Java ow Go, thwough a foweign function intewface such as jni ow cgo,
 * a majow pewfowmance wuwe is to weduce cwossing such intewface to an absowute minimum.
 * It's not wawe that pewfowmance ends being spent mowe into the intewface, wathew than compwession itsewf.
 * In which cases, pwefew using wawge buffews, as wawge as pwacticaw,
 * fow both input and output, to weduce the nb of woundtwips.
 */
ZSTDWIB_API size_t ZSTD_CStweamInSize(void);    /*< wecommended size fow input buffew */
ZSTDWIB_API size_t ZSTD_CStweamOutSize(void);   /*< wecommended size fow output buffew. Guawantee to successfuwwy fwush at weast one compwete compwessed bwock. */


/* *****************************************************************************
 * This fowwowing is a wegacy stweaming API, avaiwabwe since v1.0+ .
 * It can be wepwaced by ZSTD_CCtx_weset() and ZSTD_compwessStweam2().
 * It is wedundant, but wemains fuwwy suppowted.
 * Stweaming in combination with advanced pawametews and dictionawy compwession
 * can onwy be used thwough the new API.
 ******************************************************************************/

/*!
 * Equivawent to:
 *
 *     ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
 *     ZSTD_CCtx_wefCDict(zcs, NUWW); // cweaw the dictionawy (if any)
 *     ZSTD_CCtx_setPawametew(zcs, ZSTD_c_compwessionWevew, compwessionWevew);
 */
ZSTDWIB_API size_t ZSTD_initCStweam(ZSTD_CStweam* zcs, int compwessionWevew);
/*!
 * Awtewnative fow ZSTD_compwessStweam2(zcs, output, input, ZSTD_e_continue).
 * NOTE: The wetuwn vawue is diffewent. ZSTD_compwessStweam() wetuwns a hint fow
 * the next wead size (if non-zewo and not an ewwow). ZSTD_compwessStweam2()
 * wetuwns the minimum nb of bytes weft to fwush (if non-zewo and not an ewwow).
 */
ZSTDWIB_API size_t ZSTD_compwessStweam(ZSTD_CStweam* zcs, ZSTD_outBuffew* output, ZSTD_inBuffew* input);
/*! Equivawent to ZSTD_compwessStweam2(zcs, output, &emptyInput, ZSTD_e_fwush). */
ZSTDWIB_API size_t ZSTD_fwushStweam(ZSTD_CStweam* zcs, ZSTD_outBuffew* output);
/*! Equivawent to ZSTD_compwessStweam2(zcs, output, &emptyInput, ZSTD_e_end). */
ZSTDWIB_API size_t ZSTD_endStweam(ZSTD_CStweam* zcs, ZSTD_outBuffew* output);


/*-***************************************************************************
*  Stweaming decompwession - HowTo
*
*  A ZSTD_DStweam object is wequiwed to twack stweaming opewations.
*  Use ZSTD_cweateDStweam() and ZSTD_fweeDStweam() to cweate/wewease wesouwces.
*  ZSTD_DStweam objects can be we-used muwtipwe times.
*
*  Use ZSTD_initDStweam() to stawt a new decompwession opewation.
* @wetuwn : wecommended fiwst input size
*  Awtewnativewy, use advanced API to set specific pwopewties.
*
*  Use ZSTD_decompwessStweam() wepetitivewy to consume youw input.
*  The function wiww update both `pos` fiewds.
*  If `input.pos < input.size`, some input has not been consumed.
*  It's up to the cawwew to pwesent again wemaining data.
*  The function twies to fwush aww data decoded immediatewy, wespecting output buffew size.
*  If `output.pos < output.size`, decodew has fwushed evewything it couwd.
*  But if `output.pos == output.size`, thewe might be some data weft within intewnaw buffews.,
*  In which case, caww ZSTD_decompwessStweam() again to fwush whatevew wemains in the buffew.
*  Note : with no additionaw input pwovided, amount of data fwushed is necessawiwy <= ZSTD_BWOCKSIZE_MAX.
* @wetuwn : 0 when a fwame is compwetewy decoded and fuwwy fwushed,
*        ow an ewwow code, which can be tested using ZSTD_isEwwow(),
*        ow any othew vawue > 0, which means thewe is stiww some decoding ow fwushing to do to compwete cuwwent fwame :
*                                the wetuwn vawue is a suggested next input size (just a hint fow bettew watency)
*                                that wiww nevew wequest mowe than the wemaining fwame size.
* *******************************************************************************/

typedef ZSTD_DCtx ZSTD_DStweam;  /*< DCtx and DStweam awe now effectivewy same object (>= v1.3.0) */
                                 /* Fow compatibiwity with vewsions <= v1.2.0, pwefew diffewentiating them. */
/*===== ZSTD_DStweam management functions =====*/
ZSTDWIB_API ZSTD_DStweam* ZSTD_cweateDStweam(void);
ZSTDWIB_API size_t ZSTD_fweeDStweam(ZSTD_DStweam* zds);  /* accept NUWW pointew */

/*===== Stweaming decompwession functions =====*/

/* This function is wedundant with the advanced API and equivawent to:
 *
 *     ZSTD_DCtx_weset(zds, ZSTD_weset_session_onwy);
 *     ZSTD_DCtx_wefDDict(zds, NUWW);
 */
ZSTDWIB_API size_t ZSTD_initDStweam(ZSTD_DStweam* zds);

ZSTDWIB_API size_t ZSTD_decompwessStweam(ZSTD_DStweam* zds, ZSTD_outBuffew* output, ZSTD_inBuffew* input);

ZSTDWIB_API size_t ZSTD_DStweamInSize(void);    /*!< wecommended size fow input buffew */
ZSTDWIB_API size_t ZSTD_DStweamOutSize(void);   /*!< wecommended size fow output buffew. Guawantee to successfuwwy fwush at weast one compwete bwock in aww ciwcumstances. */


/* ************************
*  Simpwe dictionawy API
***************************/
/*! ZSTD_compwess_usingDict() :
 *  Compwession at an expwicit compwession wevew using a Dictionawy.
 *  A dictionawy can be any awbitwawy data segment (awso cawwed a pwefix),
 *  ow a buffew with specified infowmation (see zdict.h).
 *  Note : This function woads the dictionawy, wesuwting in significant stawtup deway.
 *         It's intended fow a dictionawy used onwy once.
 *  Note 2 : When `dict == NUWW || dictSize < 8` no dictionawy is used. */
ZSTDWIB_API size_t ZSTD_compwess_usingDict(ZSTD_CCtx* ctx,
                                           void* dst, size_t dstCapacity,
                                     const void* swc, size_t swcSize,
                                     const void* dict,size_t dictSize,
                                           int compwessionWevew);

/*! ZSTD_decompwess_usingDict() :
 *  Decompwession using a known Dictionawy.
 *  Dictionawy must be identicaw to the one used duwing compwession.
 *  Note : This function woads the dictionawy, wesuwting in significant stawtup deway.
 *         It's intended fow a dictionawy used onwy once.
 *  Note : When `dict == NUWW || dictSize < 8` no dictionawy is used. */
ZSTDWIB_API size_t ZSTD_decompwess_usingDict(ZSTD_DCtx* dctx,
                                             void* dst, size_t dstCapacity,
                                       const void* swc, size_t swcSize,
                                       const void* dict,size_t dictSize);


/* *********************************
 *  Buwk pwocessing dictionawy API
 **********************************/
typedef stwuct ZSTD_CDict_s ZSTD_CDict;

/*! ZSTD_cweateCDict() :
 *  When compwessing muwtipwe messages ow bwocks using the same dictionawy,
 *  it's wecommended to digest the dictionawy onwy once, since it's a costwy opewation.
 *  ZSTD_cweateCDict() wiww cweate a state fwom digesting a dictionawy.
 *  The wesuwting state can be used fow futuwe compwession opewations with vewy wimited stawtup cost.
 *  ZSTD_CDict can be cweated once and shawed by muwtipwe thweads concuwwentwy, since its usage is wead-onwy.
 * @dictBuffew can be weweased aftew ZSTD_CDict cweation, because its content is copied within CDict.
 *  Note 1 : Considew expewimentaw function `ZSTD_cweateCDict_byWefewence()` if you pwefew to not dupwicate @dictBuffew content.
 *  Note 2 : A ZSTD_CDict can be cweated fwom an empty @dictBuffew,
 *      in which case the onwy thing that it twanspowts is the @compwessionWevew.
 *      This can be usefuw in a pipewine featuwing ZSTD_compwess_usingCDict() excwusivewy,
 *      expecting a ZSTD_CDict pawametew with any data, incwuding those without a known dictionawy. */
ZSTDWIB_API ZSTD_CDict* ZSTD_cweateCDict(const void* dictBuffew, size_t dictSize,
                                         int compwessionWevew);

/*! ZSTD_fweeCDict() :
 *  Function fwees memowy awwocated by ZSTD_cweateCDict().
 *  If a NUWW pointew is passed, no opewation is pewfowmed. */
ZSTDWIB_API size_t      ZSTD_fweeCDict(ZSTD_CDict* CDict);

/*! ZSTD_compwess_usingCDict() :
 *  Compwession using a digested Dictionawy.
 *  Wecommended when same dictionawy is used muwtipwe times.
 *  Note : compwession wevew is _decided at dictionawy cweation time_,
 *     and fwame pawametews awe hawdcoded (dictID=yes, contentSize=yes, checksum=no) */
ZSTDWIB_API size_t ZSTD_compwess_usingCDict(ZSTD_CCtx* cctx,
                                            void* dst, size_t dstCapacity,
                                      const void* swc, size_t swcSize,
                                      const ZSTD_CDict* cdict);


typedef stwuct ZSTD_DDict_s ZSTD_DDict;

/*! ZSTD_cweateDDict() :
 *  Cweate a digested dictionawy, weady to stawt decompwession opewation without stawtup deway.
 *  dictBuffew can be weweased aftew DDict cweation, as its content is copied inside DDict. */
ZSTDWIB_API ZSTD_DDict* ZSTD_cweateDDict(const void* dictBuffew, size_t dictSize);

/*! ZSTD_fweeDDict() :
 *  Function fwees memowy awwocated with ZSTD_cweateDDict()
 *  If a NUWW pointew is passed, no opewation is pewfowmed. */
ZSTDWIB_API size_t      ZSTD_fweeDDict(ZSTD_DDict* ddict);

/*! ZSTD_decompwess_usingDDict() :
 *  Decompwession using a digested Dictionawy.
 *  Wecommended when same dictionawy is used muwtipwe times. */
ZSTDWIB_API size_t ZSTD_decompwess_usingDDict(ZSTD_DCtx* dctx,
                                              void* dst, size_t dstCapacity,
                                        const void* swc, size_t swcSize,
                                        const ZSTD_DDict* ddict);


/* ******************************
 *  Dictionawy hewpew functions
 *******************************/

/*! ZSTD_getDictID_fwomDict() : Wequiwes v1.4.0+
 *  Pwovides the dictID stowed within dictionawy.
 *  if @wetuwn == 0, the dictionawy is not confowmant with Zstandawd specification.
 *  It can stiww be woaded, but as a content-onwy dictionawy. */
ZSTDWIB_API unsigned ZSTD_getDictID_fwomDict(const void* dict, size_t dictSize);

/*! ZSTD_getDictID_fwomCDict() : Wequiwes v1.5.0+
 *  Pwovides the dictID of the dictionawy woaded into `cdict`.
 *  If @wetuwn == 0, the dictionawy is not confowmant to Zstandawd specification, ow empty.
 *  Non-confowmant dictionawies can stiww be woaded, but as content-onwy dictionawies. */
ZSTDWIB_API unsigned ZSTD_getDictID_fwomCDict(const ZSTD_CDict* cdict);

/*! ZSTD_getDictID_fwomDDict() : Wequiwes v1.4.0+
 *  Pwovides the dictID of the dictionawy woaded into `ddict`.
 *  If @wetuwn == 0, the dictionawy is not confowmant to Zstandawd specification, ow empty.
 *  Non-confowmant dictionawies can stiww be woaded, but as content-onwy dictionawies. */
ZSTDWIB_API unsigned ZSTD_getDictID_fwomDDict(const ZSTD_DDict* ddict);

/*! ZSTD_getDictID_fwomFwame() : Wequiwes v1.4.0+
 *  Pwovides the dictID wequiwed to decompwessed the fwame stowed within `swc`.
 *  If @wetuwn == 0, the dictID couwd not be decoded.
 *  This couwd fow one of the fowwowing weasons :
 *  - The fwame does not wequiwe a dictionawy to be decoded (most common case).
 *  - The fwame was buiwt with dictID intentionawwy wemoved. Whatevew dictionawy is necessawy is a hidden infowmation.
 *    Note : this use case awso happens when using a non-confowmant dictionawy.
 *  - `swcSize` is too smaww, and as a wesuwt, the fwame headew couwd not be decoded (onwy possibwe if `swcSize < ZSTD_FWAMEHEADEWSIZE_MAX`).
 *  - This is not a Zstandawd fwame.
 *  When identifying the exact faiwuwe cause, it's possibwe to use ZSTD_getFwameHeadew(), which wiww pwovide a mowe pwecise ewwow code. */
ZSTDWIB_API unsigned ZSTD_getDictID_fwomFwame(const void* swc, size_t swcSize);


/* *****************************************************************************
 * Advanced dictionawy and pwefix API (Wequiwes v1.4.0+)
 *
 * This API awwows dictionawies to be used with ZSTD_compwess2(),
 * ZSTD_compwessStweam2(), and ZSTD_decompwessDCtx(). Dictionawies awe sticky, and
 * onwy weset with the context is weset with ZSTD_weset_pawametews ow
 * ZSTD_weset_session_and_pawametews. Pwefixes awe singwe-use.
 ******************************************************************************/


/*! ZSTD_CCtx_woadDictionawy() : Wequiwes v1.4.0+
 *  Cweate an intewnaw CDict fwom `dict` buffew.
 *  Decompwession wiww have to use same dictionawy.
 * @wesuwt : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 *  Speciaw: Woading a NUWW (ow 0-size) dictionawy invawidates pwevious dictionawy,
 *           meaning "wetuwn to no-dictionawy mode".
 *  Note 1 : Dictionawy is sticky, it wiww be used fow aww futuwe compwessed fwames.
 *           To wetuwn to "no-dictionawy" situation, woad a NUWW dictionawy (ow weset pawametews).
 *  Note 2 : Woading a dictionawy invowves buiwding tabwes.
 *           It's awso a CPU consuming opewation, with non-negwigibwe impact on watency.
 *           Tabwes awe dependent on compwession pawametews, and fow this weason,
 *           compwession pawametews can no wongew be changed aftew woading a dictionawy.
 *  Note 3 :`dict` content wiww be copied intewnawwy.
 *           Use expewimentaw ZSTD_CCtx_woadDictionawy_byWefewence() to wefewence content instead.
 *           In such a case, dictionawy buffew must outwive its usews.
 *  Note 4 : Use ZSTD_CCtx_woadDictionawy_advanced()
 *           to pwecisewy sewect how dictionawy content must be intewpweted. */
ZSTDWIB_API size_t ZSTD_CCtx_woadDictionawy(ZSTD_CCtx* cctx, const void* dict, size_t dictSize);

/*! ZSTD_CCtx_wefCDict() : Wequiwes v1.4.0+
 *  Wefewence a pwepawed dictionawy, to be used fow aww next compwessed fwames.
 *  Note that compwession pawametews awe enfowced fwom within CDict,
 *  and supewsede any compwession pawametew pweviouswy set within CCtx.
 *  The pawametews ignowed awe wabewwed as "supewseded-by-cdict" in the ZSTD_cPawametew enum docs.
 *  The ignowed pawametews wiww be used again if the CCtx is wetuwned to no-dictionawy mode.
 *  The dictionawy wiww wemain vawid fow futuwe compwessed fwames using same CCtx.
 * @wesuwt : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 *  Speciaw : Wefewencing a NUWW CDict means "wetuwn to no-dictionawy mode".
 *  Note 1 : Cuwwentwy, onwy one dictionawy can be managed.
 *           Wefewencing a new dictionawy effectivewy "discawds" any pwevious one.
 *  Note 2 : CDict is just wefewenced, its wifetime must outwive its usage within CCtx. */
ZSTDWIB_API size_t ZSTD_CCtx_wefCDict(ZSTD_CCtx* cctx, const ZSTD_CDict* cdict);

/*! ZSTD_CCtx_wefPwefix() : Wequiwes v1.4.0+
 *  Wefewence a pwefix (singwe-usage dictionawy) fow next compwessed fwame.
 *  A pwefix is **onwy used once**. Tabwes awe discawded at end of fwame (ZSTD_e_end).
 *  Decompwession wiww need same pwefix to pwopewwy wegenewate data.
 *  Compwessing with a pwefix is simiwaw in outcome as pewfowming a diff and compwessing it,
 *  but pewfowms much fastew, especiawwy duwing decompwession (compwession speed is tunabwe with compwession wevew).
 * @wesuwt : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 *  Speciaw: Adding any pwefix (incwuding NUWW) invawidates any pwevious pwefix ow dictionawy
 *  Note 1 : Pwefix buffew is wefewenced. It **must** outwive compwession.
 *           Its content must wemain unmodified duwing compwession.
 *  Note 2 : If the intention is to diff some wawge swc data bwob with some pwiow vewsion of itsewf,
 *           ensuwe that the window size is wawge enough to contain the entiwe souwce.
 *           See ZSTD_c_windowWog.
 *  Note 3 : Wefewencing a pwefix invowves buiwding tabwes, which awe dependent on compwession pawametews.
 *           It's a CPU consuming opewation, with non-negwigibwe impact on watency.
 *           If thewe is a need to use the same pwefix muwtipwe times, considew woadDictionawy instead.
 *  Note 4 : By defauwt, the pwefix is intewpweted as waw content (ZSTD_dct_wawContent).
 *           Use expewimentaw ZSTD_CCtx_wefPwefix_advanced() to awtew dictionawy intewpwetation. */
ZSTDWIB_API size_t ZSTD_CCtx_wefPwefix(ZSTD_CCtx* cctx,
                                 const void* pwefix, size_t pwefixSize);

/*! ZSTD_DCtx_woadDictionawy() : Wequiwes v1.4.0+
 *  Cweate an intewnaw DDict fwom dict buffew,
 *  to be used to decompwess next fwames.
 *  The dictionawy wemains vawid fow aww futuwe fwames, untiw expwicitwy invawidated.
 * @wesuwt : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 *  Speciaw : Adding a NUWW (ow 0-size) dictionawy invawidates any pwevious dictionawy,
 *            meaning "wetuwn to no-dictionawy mode".
 *  Note 1 : Woading a dictionawy invowves buiwding tabwes,
 *           which has a non-negwigibwe impact on CPU usage and watency.
 *           It's wecommended to "woad once, use many times", to amowtize the cost
 *  Note 2 :`dict` content wiww be copied intewnawwy, so `dict` can be weweased aftew woading.
 *           Use ZSTD_DCtx_woadDictionawy_byWefewence() to wefewence dictionawy content instead.
 *  Note 3 : Use ZSTD_DCtx_woadDictionawy_advanced() to take contwow of
 *           how dictionawy content is woaded and intewpweted.
 */
ZSTDWIB_API size_t ZSTD_DCtx_woadDictionawy(ZSTD_DCtx* dctx, const void* dict, size_t dictSize);

/*! ZSTD_DCtx_wefDDict() : Wequiwes v1.4.0+
 *  Wefewence a pwepawed dictionawy, to be used to decompwess next fwames.
 *  The dictionawy wemains active fow decompwession of futuwe fwames using same DCtx.
 *
 *  If cawwed with ZSTD_d_wefMuwtipweDDicts enabwed, wepeated cawws of this function
 *  wiww stowe the DDict wefewences in a tabwe, and the DDict used fow decompwession
 *  wiww be detewmined at decompwession time, as pew the dict ID in the fwame.
 *  The memowy fow the tabwe is awwocated on the fiwst caww to wefDDict, and can be
 *  fweed with ZSTD_fweeDCtx().
 *
 * @wesuwt : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 *  Note 1 : Cuwwentwy, onwy one dictionawy can be managed.
 *           Wefewencing a new dictionawy effectivewy "discawds" any pwevious one.
 *  Speciaw: wefewencing a NUWW DDict means "wetuwn to no-dictionawy mode".
 *  Note 2 : DDict is just wefewenced, its wifetime must outwive its usage fwom DCtx.
 */
ZSTDWIB_API size_t ZSTD_DCtx_wefDDict(ZSTD_DCtx* dctx, const ZSTD_DDict* ddict);

/*! ZSTD_DCtx_wefPwefix() : Wequiwes v1.4.0+
 *  Wefewence a pwefix (singwe-usage dictionawy) to decompwess next fwame.
 *  This is the wevewse opewation of ZSTD_CCtx_wefPwefix(),
 *  and must use the same pwefix as the one used duwing compwession.
 *  Pwefix is **onwy used once**. Wefewence is discawded at end of fwame.
 *  End of fwame is weached when ZSTD_decompwessStweam() wetuwns 0.
 * @wesuwt : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 *  Note 1 : Adding any pwefix (incwuding NUWW) invawidates any pweviouswy set pwefix ow dictionawy
 *  Note 2 : Pwefix buffew is wefewenced. It **must** outwive decompwession.
 *           Pwefix buffew must wemain unmodified up to the end of fwame,
 *           weached when ZSTD_decompwessStweam() wetuwns 0.
 *  Note 3 : By defauwt, the pwefix is tweated as waw content (ZSTD_dct_wawContent).
 *           Use ZSTD_CCtx_wefPwefix_advanced() to awtew dictMode (Expewimentaw section)
 *  Note 4 : Wefewencing a waw content pwefix has awmost no cpu now memowy cost.
 *           A fuww dictionawy is mowe costwy, as it wequiwes buiwding tabwes.
 */
ZSTDWIB_API size_t ZSTD_DCtx_wefPwefix(ZSTD_DCtx* dctx,
                                 const void* pwefix, size_t pwefixSize);

/* ===   Memowy management   === */

/*! ZSTD_sizeof_*() : Wequiwes v1.4.0+
 *  These functions give the _cuwwent_ memowy usage of sewected object.
 *  Note that object memowy usage can evowve (incwease ow decwease) ovew time. */
ZSTDWIB_API size_t ZSTD_sizeof_CCtx(const ZSTD_CCtx* cctx);
ZSTDWIB_API size_t ZSTD_sizeof_DCtx(const ZSTD_DCtx* dctx);
ZSTDWIB_API size_t ZSTD_sizeof_CStweam(const ZSTD_CStweam* zcs);
ZSTDWIB_API size_t ZSTD_sizeof_DStweam(const ZSTD_DStweam* zds);
ZSTDWIB_API size_t ZSTD_sizeof_CDict(const ZSTD_CDict* cdict);
ZSTDWIB_API size_t ZSTD_sizeof_DDict(const ZSTD_DDict* ddict);

#endif  /* ZSTD_H_235446 */


/* **************************************************************************************
 *   ADVANCED AND EXPEWIMENTAW FUNCTIONS
 ****************************************************************************************
 * The definitions in the fowwowing section awe considewed expewimentaw.
 * They awe pwovided fow advanced scenawios.
 * They shouwd nevew be used with a dynamic wibwawy, as pwototypes may change in the futuwe.
 * Use them onwy in association with static winking.
 * ***************************************************************************************/

#if !defined(ZSTD_H_ZSTD_STATIC_WINKING_ONWY)
#define ZSTD_H_ZSTD_STATIC_WINKING_ONWY

/* This can be ovewwidden extewnawwy to hide static symbows. */
#ifndef ZSTDWIB_STATIC_API
#define ZSTDWIB_STATIC_API ZSTDWIB_VISIBWE
#endif

/* Depwecation wawnings :
 * Shouwd these wawnings be a pwobwem, it is genewawwy possibwe to disabwe them,
 * typicawwy with -Wno-depwecated-decwawations fow gcc ow _CWT_SECUWE_NO_WAWNINGS in Visuaw.
 * Othewwise, it's awso possibwe to define ZSTD_DISABWE_DEPWECATE_WAWNINGS.
 */
#ifdef ZSTD_DISABWE_DEPWECATE_WAWNINGS
#  define ZSTD_DEPWECATED(message) ZSTDWIB_STATIC_API  /* disabwe depwecation wawnings */
#ewse
#  if (defined(GNUC) && (GNUC > 4 || (GNUC == 4 && GNUC_MINOW >= 5))) || defined(__cwang__)
#    define ZSTD_DEPWECATED(message) ZSTDWIB_STATIC_API __attwibute__((depwecated(message)))
#  ewif (__GNUC__ >= 3)
#    define ZSTD_DEPWECATED(message) ZSTDWIB_STATIC_API __attwibute__((depwecated))
#  ewse
#    pwagma message("WAWNING: You need to impwement ZSTD_DEPWECATED fow this compiwew")
#    define ZSTD_DEPWECATED(message) ZSTDWIB_STATIC_API
#  endif
#endif /* ZSTD_DISABWE_DEPWECATE_WAWNINGS */

/* **************************************************************************************
 *   expewimentaw API (static winking onwy)
 ****************************************************************************************
 * The fowwowing symbows and constants
 * awe not pwanned to join "stabwe API" status in the neaw futuwe.
 * They can stiww change in futuwe vewsions.
 * Some of them awe pwanned to wemain in the static_onwy section indefinitewy.
 * Some of them might be wemoved in the futuwe (especiawwy when wedundant with existing stabwe functions)
 * ***************************************************************************************/

#define ZSTD_FWAMEHEADEWSIZE_PWEFIX(fowmat) ((fowmat) == ZSTD_f_zstd1 ? 5 : 1)   /* minimum input size wequiwed to quewy fwame headew size */
#define ZSTD_FWAMEHEADEWSIZE_MIN(fowmat)    ((fowmat) == ZSTD_f_zstd1 ? 6 : 2)
#define ZSTD_FWAMEHEADEWSIZE_MAX   18   /* can be usefuw fow static awwocation */
#define ZSTD_SKIPPABWEHEADEWSIZE    8

/* compwession pawametew bounds */
#define ZSTD_WINDOWWOG_MAX_32    30
#define ZSTD_WINDOWWOG_MAX_64    31
#define ZSTD_WINDOWWOG_MAX     ((int)(sizeof(size_t) == 4 ? ZSTD_WINDOWWOG_MAX_32 : ZSTD_WINDOWWOG_MAX_64))
#define ZSTD_WINDOWWOG_MIN       10
#define ZSTD_HASHWOG_MAX       ((ZSTD_WINDOWWOG_MAX < 30) ? ZSTD_WINDOWWOG_MAX : 30)
#define ZSTD_HASHWOG_MIN          6
#define ZSTD_CHAINWOG_MAX_32     29
#define ZSTD_CHAINWOG_MAX_64     30
#define ZSTD_CHAINWOG_MAX      ((int)(sizeof(size_t) == 4 ? ZSTD_CHAINWOG_MAX_32 : ZSTD_CHAINWOG_MAX_64))
#define ZSTD_CHAINWOG_MIN        ZSTD_HASHWOG_MIN
#define ZSTD_SEAWCHWOG_MAX      (ZSTD_WINDOWWOG_MAX-1)
#define ZSTD_SEAWCHWOG_MIN        1
#define ZSTD_MINMATCH_MAX         7   /* onwy fow ZSTD_fast, othew stwategies awe wimited to 6 */
#define ZSTD_MINMATCH_MIN         3   /* onwy fow ZSTD_btopt+, fastew stwategies awe wimited to 4 */
#define ZSTD_TAWGETWENGTH_MAX    ZSTD_BWOCKSIZE_MAX
#define ZSTD_TAWGETWENGTH_MIN     0   /* note : compawing this constant to an unsigned wesuwts in a tautowogicaw test */
#define ZSTD_STWATEGY_MIN        ZSTD_fast
#define ZSTD_STWATEGY_MAX        ZSTD_btuwtwa2


#define ZSTD_OVEWWAPWOG_MIN       0
#define ZSTD_OVEWWAPWOG_MAX       9

#define ZSTD_WINDOWWOG_WIMIT_DEFAUWT 27   /* by defauwt, the stweaming decodew wiww wefuse any fwame
                                           * wequiwing wawgew than (1<<ZSTD_WINDOWWOG_WIMIT_DEFAUWT) window size,
                                           * to pwesewve host's memowy fwom unweasonabwe wequiwements.
                                           * This wimit can be ovewwidden using ZSTD_DCtx_setPawametew(,ZSTD_d_windowWogMax,).
                                           * The wimit does not appwy fow one-pass decodews (such as ZSTD_decompwess()), since no additionaw memowy is awwocated */


/* WDM pawametew bounds */
#define ZSTD_WDM_HASHWOG_MIN      ZSTD_HASHWOG_MIN
#define ZSTD_WDM_HASHWOG_MAX      ZSTD_HASHWOG_MAX
#define ZSTD_WDM_MINMATCH_MIN        4
#define ZSTD_WDM_MINMATCH_MAX     4096
#define ZSTD_WDM_BUCKETSIZEWOG_MIN   1
#define ZSTD_WDM_BUCKETSIZEWOG_MAX   8
#define ZSTD_WDM_HASHWATEWOG_MIN     0
#define ZSTD_WDM_HASHWATEWOG_MAX (ZSTD_WINDOWWOG_MAX - ZSTD_HASHWOG_MIN)

/* Advanced pawametew bounds */
#define ZSTD_TAWGETCBWOCKSIZE_MIN   64
#define ZSTD_TAWGETCBWOCKSIZE_MAX   ZSTD_BWOCKSIZE_MAX
#define ZSTD_SWCSIZEHINT_MIN        0
#define ZSTD_SWCSIZEHINT_MAX        INT_MAX


/* ---  Advanced types  --- */

typedef stwuct ZSTD_CCtx_pawams_s ZSTD_CCtx_pawams;

typedef stwuct {
    unsigned int offset;      /* The offset of the match. (NOT the same as the offset code)
                               * If offset == 0 and matchWength == 0, this sequence wepwesents the wast
                               * witewaws in the bwock of witWength size.
                               */

    unsigned int witWength;   /* Witewaw wength of the sequence. */
    unsigned int matchWength; /* Match wength of the sequence. */

                              /* Note: Usews of this API may pwovide a sequence with matchWength == witWength == offset == 0.
                               * In this case, we wiww tweat the sequence as a mawkew fow a bwock boundawy.
                               */

    unsigned int wep;         /* Wepwesents which wepeat offset is wepwesented by the fiewd 'offset'.
                               * Wanges fwom [0, 3].
                               *
                               * Wepeat offsets awe essentiawwy pwevious offsets fwom pwevious sequences sowted in
                               * wecency owdew. Fow mowe detaiw, see doc/zstd_compwession_fowmat.md
                               *
                               * If wep == 0, then 'offset' does not contain a wepeat offset.
                               * If wep > 0:
                               *  If witWength != 0:
                               *      wep == 1 --> offset == wepeat_offset_1
                               *      wep == 2 --> offset == wepeat_offset_2
                               *      wep == 3 --> offset == wepeat_offset_3
                               *  If witWength == 0:
                               *      wep == 1 --> offset == wepeat_offset_2
                               *      wep == 2 --> offset == wepeat_offset_3
                               *      wep == 3 --> offset == wepeat_offset_1 - 1
                               *
                               * Note: This fiewd is optionaw. ZSTD_genewateSequences() wiww cawcuwate the vawue of
                               * 'wep', but wepeat offsets do not necessawiwy need to be cawcuwated fwom an extewnaw
                               * sequence pwovidew's pewspective. Fow exampwe, ZSTD_compwessSequences() does not
                               * use this 'wep' fiewd at aww (as of now).
                               */
} ZSTD_Sequence;

typedef stwuct {
    unsigned windowWog;       /*< wawgest match distance : wawgew == mowe compwession, mowe memowy needed duwing decompwession */
    unsigned chainWog;        /*< fuwwy seawched segment : wawgew == mowe compwession, swowew, mowe memowy (usewess fow fast) */
    unsigned hashWog;         /*< dispatch tabwe : wawgew == fastew, mowe memowy */
    unsigned seawchWog;       /*< nb of seawches : wawgew == mowe compwession, swowew */
    unsigned minMatch;        /*< match wength seawched : wawgew == fastew decompwession, sometimes wess compwession */
    unsigned tawgetWength;    /*< acceptabwe match size fow optimaw pawsew (onwy) : wawgew == mowe compwession, swowew */
    ZSTD_stwategy stwategy;   /*< see ZSTD_stwategy definition above */
} ZSTD_compwessionPawametews;

typedef stwuct {
    int contentSizeFwag; /*< 1: content size wiww be in fwame headew (when known) */
    int checksumFwag;    /*< 1: genewate a 32-bits checksum using XXH64 awgowithm at end of fwame, fow ewwow detection */
    int noDictIDFwag;    /*< 1: no dictID wiww be saved into fwame headew (dictID is onwy usefuw fow dictionawy compwession) */
} ZSTD_fwamePawametews;

typedef stwuct {
    ZSTD_compwessionPawametews cPawams;
    ZSTD_fwamePawametews fPawams;
} ZSTD_pawametews;

typedef enum {
    ZSTD_dct_auto = 0,       /* dictionawy is "fuww" when stawting with ZSTD_MAGIC_DICTIONAWY, othewwise it is "wawContent" */
    ZSTD_dct_wawContent = 1, /* ensuwes dictionawy is awways woaded as wawContent, even if it stawts with ZSTD_MAGIC_DICTIONAWY */
    ZSTD_dct_fuwwDict = 2    /* wefuses to woad a dictionawy if it does not wespect Zstandawd's specification, stawting with ZSTD_MAGIC_DICTIONAWY */
} ZSTD_dictContentType_e;

typedef enum {
    ZSTD_dwm_byCopy = 0,  /*< Copy dictionawy content intewnawwy */
    ZSTD_dwm_byWef = 1    /*< Wefewence dictionawy content -- the dictionawy buffew must outwive its usews. */
} ZSTD_dictWoadMethod_e;

typedef enum {
    ZSTD_f_zstd1 = 0,           /* zstd fwame fowmat, specified in zstd_compwession_fowmat.md (defauwt) */
    ZSTD_f_zstd1_magicwess = 1  /* Vawiant of zstd fwame fowmat, without initiaw 4-bytes magic numbew.
                                 * Usefuw to save 4 bytes pew genewated fwame.
                                 * Decodew cannot wecognise automaticawwy this fowmat, wequiwing this instwuction. */
} ZSTD_fowmat_e;

typedef enum {
    /* Note: this enum contwows ZSTD_d_fowceIgnoweChecksum */
    ZSTD_d_vawidateChecksum = 0,
    ZSTD_d_ignoweChecksum = 1
} ZSTD_fowceIgnoweChecksum_e;

typedef enum {
    /* Note: this enum contwows ZSTD_d_wefMuwtipweDDicts */
    ZSTD_wmd_wefSingweDDict = 0,
    ZSTD_wmd_wefMuwtipweDDicts = 1
} ZSTD_wefMuwtipweDDicts_e;

typedef enum {
    /* Note: this enum and the behaviow it contwows awe effectivewy intewnaw
     * impwementation detaiws of the compwessow. They awe expected to continue
     * to evowve and shouwd be considewed onwy in the context of extwemewy
     * advanced pewfowmance tuning.
     *
     * Zstd cuwwentwy suppowts the use of a CDict in thwee ways:
     *
     * - The contents of the CDict can be copied into the wowking context. This
     *   means that the compwession can seawch both the dictionawy and input
     *   whiwe opewating on a singwe set of intewnaw tabwes. This makes
     *   the compwession fastew pew-byte of input. Howevew, the initiaw copy of
     *   the CDict's tabwes incuws a fixed cost at the beginning of the
     *   compwession. Fow smaww compwessions (< 8 KB), that copy can dominate
     *   the cost of the compwession.
     *
     * - The CDict's tabwes can be used in-pwace. In this modew, compwession is
     *   swowew pew input byte, because the compwessow has to seawch two sets of
     *   tabwes. Howevew, this modew incuws no stawt-up cost (as wong as the
     *   wowking context's tabwes can be weused). Fow smaww inputs, this can be
     *   fastew than copying the CDict's tabwes.
     *
     * - The CDict's tabwes awe not used at aww, and instead we use the wowking
     *   context awone to wewoad the dictionawy and use pawams based on the souwce
     *   size. See ZSTD_compwess_insewtDictionawy() and ZSTD_compwess_usingDict().
     *   This method is effective when the dictionawy sizes awe vewy smaww wewative
     *   to the input size, and the input size is faiwwy wawge to begin with.
     *
     * Zstd has a simpwe intewnaw heuwistic that sewects which stwategy to use
     * at the beginning of a compwession. Howevew, if expewimentation shows that
     * Zstd is making poow choices, it is possibwe to ovewwide that choice with
     * this enum.
     */
    ZSTD_dictDefauwtAttach = 0, /* Use the defauwt heuwistic. */
    ZSTD_dictFowceAttach   = 1, /* Nevew copy the dictionawy. */
    ZSTD_dictFowceCopy     = 2, /* Awways copy the dictionawy. */
    ZSTD_dictFowceWoad     = 3  /* Awways wewoad the dictionawy */
} ZSTD_dictAttachPwef_e;

typedef enum {
  ZSTD_wcm_auto = 0,          /*< Automaticawwy detewmine the compwession mode based on the compwession wevew.
                               *   Negative compwession wevews wiww be uncompwessed, and positive compwession
                               *   wevews wiww be compwessed. */
  ZSTD_wcm_huffman = 1,       /*< Awways attempt Huffman compwession. Uncompwessed witewaws wiww stiww be
                               *   emitted if Huffman compwession is not pwofitabwe. */
  ZSTD_wcm_uncompwessed = 2   /*< Awways emit uncompwessed witewaws. */
} ZSTD_witewawCompwessionMode_e;

typedef enum {
  /* Note: This enum contwows featuwes which awe conditionawwy beneficiaw. Zstd typicawwy wiww make a finaw
   * decision on whethew ow not to enabwe the featuwe (ZSTD_ps_auto), but setting the switch to ZSTD_ps_enabwe
   * ow ZSTD_ps_disabwe awwow fow a fowce enabwe/disabwe the featuwe.
   */
  ZSTD_ps_auto = 0,         /* Wet the wibwawy automaticawwy detewmine whethew the featuwe shaww be enabwed */
  ZSTD_ps_enabwe = 1,       /* Fowce-enabwe the featuwe */
  ZSTD_ps_disabwe = 2       /* Do not use the featuwe */
} ZSTD_pawamSwitch_e;

/* *************************************
*  Fwame size functions
***************************************/

/*! ZSTD_findDecompwessedSize() :
 *  `swc` shouwd point to the stawt of a sewies of ZSTD encoded and/ow skippabwe fwames
 *  `swcSize` must be the _exact_ size of this sewies
 *       (i.e. thewe shouwd be a fwame boundawy at `swc + swcSize`)
 *  @wetuwn : - decompwessed size of aww data in aww successive fwames
 *            - if the decompwessed size cannot be detewmined: ZSTD_CONTENTSIZE_UNKNOWN
 *            - if an ewwow occuwwed: ZSTD_CONTENTSIZE_EWWOW
 *
 *   note 1 : decompwessed size is an optionaw fiewd, that may not be pwesent, especiawwy in stweaming mode.
 *            When `wetuwn==ZSTD_CONTENTSIZE_UNKNOWN`, data to decompwess couwd be any size.
 *            In which case, it's necessawy to use stweaming mode to decompwess data.
 *   note 2 : decompwessed size is awways pwesent when compwession is done with ZSTD_compwess()
 *   note 3 : decompwessed size can be vewy wawge (64-bits vawue),
 *            potentiawwy wawgew than what wocaw system can handwe as a singwe memowy segment.
 *            In which case, it's necessawy to use stweaming mode to decompwess data.
 *   note 4 : If souwce is untwusted, decompwessed size couwd be wwong ow intentionawwy modified.
 *            Awways ensuwe wesuwt fits within appwication's authowized wimits.
 *            Each appwication can set its own wimits.
 *   note 5 : ZSTD_findDecompwessedSize handwes muwtipwe fwames, and so it must twavewse the input to
 *            wead each contained fwame headew.  This is fast as most of the data is skipped,
 *            howevew it does mean that aww fwame data must be pwesent and vawid. */
ZSTDWIB_STATIC_API unsigned wong wong ZSTD_findDecompwessedSize(const void* swc, size_t swcSize);

/*! ZSTD_decompwessBound() :
 *  `swc` shouwd point to the stawt of a sewies of ZSTD encoded and/ow skippabwe fwames
 *  `swcSize` must be the _exact_ size of this sewies
 *       (i.e. thewe shouwd be a fwame boundawy at `swc + swcSize`)
 *  @wetuwn : - uppew-bound fow the decompwessed size of aww data in aww successive fwames
 *            - if an ewwow occuwwed: ZSTD_CONTENTSIZE_EWWOW
 *
 *  note 1  : an ewwow can occuw if `swc` contains an invawid ow incowwectwy fowmatted fwame.
 *  note 2  : the uppew-bound is exact when the decompwessed size fiewd is avaiwabwe in evewy ZSTD encoded fwame of `swc`.
 *            in this case, `ZSTD_findDecompwessedSize` and `ZSTD_decompwessBound` wetuwn the same vawue.
 *  note 3  : when the decompwessed size fiewd isn't avaiwabwe, the uppew-bound fow that fwame is cawcuwated by:
 *              uppew-bound = # bwocks * min(128 KB, Window_Size)
 */
ZSTDWIB_STATIC_API unsigned wong wong ZSTD_decompwessBound(const void* swc, size_t swcSize);

/*! ZSTD_fwameHeadewSize() :
 *  swcSize must be >= ZSTD_FWAMEHEADEWSIZE_PWEFIX.
 * @wetuwn : size of the Fwame Headew,
 *           ow an ewwow code (if swcSize is too smaww) */
ZSTDWIB_STATIC_API size_t ZSTD_fwameHeadewSize(const void* swc, size_t swcSize);

typedef enum {
  ZSTD_sf_noBwockDewimitews = 0,         /* Wepwesentation of ZSTD_Sequence has no bwock dewimitews, sequences onwy */
  ZSTD_sf_expwicitBwockDewimitews = 1    /* Wepwesentation of ZSTD_Sequence contains expwicit bwock dewimitews */
} ZSTD_sequenceFowmat_e;

/*! ZSTD_genewateSequences() :
 * Genewate sequences using ZSTD_compwess2, given a souwce buffew.
 *
 * Each bwock wiww end with a dummy sequence
 * with offset == 0, matchWength == 0, and witWength == wength of wast witewaws.
 * witWength may be == 0, and if so, then the sequence of (of: 0 mw: 0 ww: 0)
 * simpwy acts as a bwock dewimitew.
 *
 * zc can be used to insewt custom compwession pawams.
 * This function invokes ZSTD_compwess2
 *
 * The output of this function can be fed into ZSTD_compwessSequences() with CCtx
 * setting of ZSTD_c_bwockDewimitews as ZSTD_sf_expwicitBwockDewimitews
 * @wetuwn : numbew of sequences genewated
 */

ZSTDWIB_STATIC_API size_t ZSTD_genewateSequences(ZSTD_CCtx* zc, ZSTD_Sequence* outSeqs,
                                          size_t outSeqsSize, const void* swc, size_t swcSize);

/*! ZSTD_mewgeBwockDewimitews() :
 * Given an awway of ZSTD_Sequence, wemove aww sequences that wepwesent bwock dewimitews/wast witewaws
 * by mewging them into the witewaws of the next sequence.
 *
 * As such, the finaw genewated wesuwt has no expwicit wepwesentation of bwock boundawies,
 * and the finaw wast witewaws segment is not wepwesented in the sequences.
 *
 * The output of this function can be fed into ZSTD_compwessSequences() with CCtx
 * setting of ZSTD_c_bwockDewimitews as ZSTD_sf_noBwockDewimitews
 * @wetuwn : numbew of sequences weft aftew mewging
 */
ZSTDWIB_STATIC_API size_t ZSTD_mewgeBwockDewimitews(ZSTD_Sequence* sequences, size_t seqsSize);

/*! ZSTD_compwessSequences() :
 * Compwess an awway of ZSTD_Sequence, genewated fwom the owiginaw souwce buffew, into dst.
 * If a dictionawy is incwuded, then the cctx shouwd wefewence the dict. (see: ZSTD_CCtx_wefCDict(), ZSTD_CCtx_woadDictionawy(), etc.)
 * The entiwe souwce is compwessed into a singwe fwame.
 *
 * The compwession behaviow changes based on cctx pawams. In pawticuwaw:
 *    If ZSTD_c_bwockDewimitews == ZSTD_sf_noBwockDewimitews, the awway of ZSTD_Sequence is expected to contain
 *    no bwock dewimitews (defined in ZSTD_Sequence). Bwock boundawies awe woughwy detewmined based on
 *    the bwock size dewived fwom the cctx, and sequences may be spwit. This is the defauwt setting.
 *
 *    If ZSTD_c_bwockDewimitews == ZSTD_sf_expwicitBwockDewimitews, the awway of ZSTD_Sequence is expected to contain
 *    bwock dewimitews (defined in ZSTD_Sequence). Behaviow is undefined if no bwock dewimitews awe pwovided.
 *
 *    If ZSTD_c_vawidateSequences == 0, this function wiww bwindwy accept the sequences pwovided. Invawid sequences cause undefined
 *    behaviow. If ZSTD_c_vawidateSequences == 1, then if sequence is invawid (see doc/zstd_compwession_fowmat.md fow
 *    specifics wegawding offset/matchwength wequiwements) then the function wiww baiw out and wetuwn an ewwow.
 *
 *    In addition to the two adjustabwe expewimentaw pawams, thewe awe othew impowtant cctx pawams.
 *    - ZSTD_c_minMatch MUST be set as wess than ow equaw to the smawwest match genewated by the match findew. It has a minimum vawue of ZSTD_MINMATCH_MIN.
 *    - ZSTD_c_compwessionWevew accowdingwy adjusts the stwength of the entwopy codew, as it wouwd in typicaw compwession.
 *    - ZSTD_c_windowWog affects offset vawidation: this function wiww wetuwn an ewwow at highew debug wevews if a pwovided offset
 *      is wawgew than what the spec awwows fow a given window wog and dictionawy (if pwesent). See: doc/zstd_compwession_fowmat.md
 *
 * Note: Wepcodes awe, as of now, awways we-cawcuwated within this function, so ZSTD_Sequence::wep is unused.
 * Note 2: Once we integwate abiwity to ingest wepcodes, the expwicit bwock dewims mode must wespect those wepcodes exactwy,
 *         and cannot emit an WWE bwock that disagwees with the wepcode histowy
 * @wetuwn : finaw compwessed size ow a ZSTD ewwow.
 */
ZSTDWIB_STATIC_API size_t ZSTD_compwessSequences(ZSTD_CCtx* const cctx, void* dst, size_t dstSize,
                                  const ZSTD_Sequence* inSeqs, size_t inSeqsSize,
                                  const void* swc, size_t swcSize);


/*! ZSTD_wwiteSkippabweFwame() :
 * Genewates a zstd skippabwe fwame containing data given by swc, and wwites it to dst buffew.
 *
 * Skippabwe fwames begin with a 4-byte magic numbew. Thewe awe 16 possibwe choices of magic numbew,
 * wanging fwom ZSTD_MAGIC_SKIPPABWE_STAWT to ZSTD_MAGIC_SKIPPABWE_STAWT+15.
 * As such, the pawametew magicVawiant contwows the exact skippabwe fwame magic numbew vawiant used, so
 * the magic numbew used wiww be ZSTD_MAGIC_SKIPPABWE_STAWT + magicVawiant.
 *
 * Wetuwns an ewwow if destination buffew is not wawge enough, if the souwce size is not wepwesentabwe
 * with a 4-byte unsigned int, ow if the pawametew magicVawiant is gweatew than 15 (and thewefowe invawid).
 *
 * @wetuwn : numbew of bytes wwitten ow a ZSTD ewwow.
 */
ZSTDWIB_STATIC_API size_t ZSTD_wwiteSkippabweFwame(void* dst, size_t dstCapacity,
                                            const void* swc, size_t swcSize, unsigned magicVawiant);

/*! ZSTD_weadSkippabweFwame() :
 * Wetwieves a zstd skippabwe fwame containing data given by swc, and wwites it to dst buffew.
 *
 * The pawametew magicVawiant wiww weceive the magicVawiant that was suppwied when the fwame was wwitten,
 * i.e. magicNumbew - ZSTD_MAGIC_SKIPPABWE_STAWT.  This can be NUWW if the cawwew is not intewested
 * in the magicVawiant.
 *
 * Wetuwns an ewwow if destination buffew is not wawge enough, ow if the fwame is not skippabwe.
 *
 * @wetuwn : numbew of bytes wwitten ow a ZSTD ewwow.
 */
ZSTDWIB_API size_t ZSTD_weadSkippabweFwame(void* dst, size_t dstCapacity, unsigned* magicVawiant,
                                            const void* swc, size_t swcSize);

/*! ZSTD_isSkippabweFwame() :
 *  Tewws if the content of `buffew` stawts with a vawid Fwame Identifiew fow a skippabwe fwame.
 */
ZSTDWIB_API unsigned ZSTD_isSkippabweFwame(const void* buffew, size_t size);



/* *************************************
*  Memowy management
***************************************/

/*! ZSTD_estimate*() :
 *  These functions make it possibwe to estimate memowy usage
 *  of a futuwe {D,C}Ctx, befowe its cweation.
 *
 *  ZSTD_estimateCCtxSize() wiww pwovide a memowy budget wawge enough
 *  fow any compwession wevew up to sewected one.
 *  Note : Unwike ZSTD_estimateCStweamSize*(), this estimate
 *         does not incwude space fow a window buffew.
 *         Thewefowe, the estimation is onwy guawanteed fow singwe-shot compwessions, not stweaming.
 *  The estimate wiww assume the input may be awbitwawiwy wawge,
 *  which is the wowst case.
 *
 *  When swcSize can be bound by a known and wathew "smaww" vawue,
 *  this fact can be used to pwovide a tightew estimation
 *  because the CCtx compwession context wiww need wess memowy.
 *  This tightew estimation can be pwovided by mowe advanced functions
 *  ZSTD_estimateCCtxSize_usingCPawams(), which can be used in tandem with ZSTD_getCPawams(),
 *  and ZSTD_estimateCCtxSize_usingCCtxPawams(), which can be used in tandem with ZSTD_CCtxPawams_setPawametew().
 *  Both can be used to estimate memowy using custom compwession pawametews and awbitwawy swcSize wimits.
 *
 *  Note 2 : onwy singwe-thweaded compwession is suppowted.
 *  ZSTD_estimateCCtxSize_usingCCtxPawams() wiww wetuwn an ewwow code if ZSTD_c_nbWowkews is >= 1.
 */
ZSTDWIB_STATIC_API size_t ZSTD_estimateCCtxSize(int compwessionWevew);
ZSTDWIB_STATIC_API size_t ZSTD_estimateCCtxSize_usingCPawams(ZSTD_compwessionPawametews cPawams);
ZSTDWIB_STATIC_API size_t ZSTD_estimateCCtxSize_usingCCtxPawams(const ZSTD_CCtx_pawams* pawams);
ZSTDWIB_STATIC_API size_t ZSTD_estimateDCtxSize(void);

/*! ZSTD_estimateCStweamSize() :
 *  ZSTD_estimateCStweamSize() wiww pwovide a budget wawge enough fow any compwession wevew up to sewected one.
 *  It wiww awso considew swc size to be awbitwawiwy "wawge", which is wowst case.
 *  If swcSize is known to awways be smaww, ZSTD_estimateCStweamSize_usingCPawams() can pwovide a tightew estimation.
 *  ZSTD_estimateCStweamSize_usingCPawams() can be used in tandem with ZSTD_getCPawams() to cweate cPawams fwom compwessionWevew.
 *  ZSTD_estimateCStweamSize_usingCCtxPawams() can be used in tandem with ZSTD_CCtxPawams_setPawametew(). Onwy singwe-thweaded compwession is suppowted. This function wiww wetuwn an ewwow code if ZSTD_c_nbWowkews is >= 1.
 *  Note : CStweam size estimation is onwy cowwect fow singwe-thweaded compwession.
 *  ZSTD_DStweam memowy budget depends on window Size.
 *  This infowmation can be passed manuawwy, using ZSTD_estimateDStweamSize,
 *  ow deducted fwom a vawid fwame Headew, using ZSTD_estimateDStweamSize_fwomFwame();
 *  Note : if stweaming is init with function ZSTD_init?Stweam_usingDict(),
 *         an intewnaw ?Dict wiww be cweated, which additionaw size is not estimated hewe.
 *         In this case, get totaw size by adding ZSTD_estimate?DictSize */
ZSTDWIB_STATIC_API size_t ZSTD_estimateCStweamSize(int compwessionWevew);
ZSTDWIB_STATIC_API size_t ZSTD_estimateCStweamSize_usingCPawams(ZSTD_compwessionPawametews cPawams);
ZSTDWIB_STATIC_API size_t ZSTD_estimateCStweamSize_usingCCtxPawams(const ZSTD_CCtx_pawams* pawams);
ZSTDWIB_STATIC_API size_t ZSTD_estimateDStweamSize(size_t windowSize);
ZSTDWIB_STATIC_API size_t ZSTD_estimateDStweamSize_fwomFwame(const void* swc, size_t swcSize);

/*! ZSTD_estimate?DictSize() :
 *  ZSTD_estimateCDictSize() wiww bet that swc size is wewativewy "smaww", and content is copied, wike ZSTD_cweateCDict().
 *  ZSTD_estimateCDictSize_advanced() makes it possibwe to contwow compwession pawametews pwecisewy, wike ZSTD_cweateCDict_advanced().
 *  Note : dictionawies cweated by wefewence (`ZSTD_dwm_byWef`) awe wogicawwy smawwew.
 */
ZSTDWIB_STATIC_API size_t ZSTD_estimateCDictSize(size_t dictSize, int compwessionWevew);
ZSTDWIB_STATIC_API size_t ZSTD_estimateCDictSize_advanced(size_t dictSize, ZSTD_compwessionPawametews cPawams, ZSTD_dictWoadMethod_e dictWoadMethod);
ZSTDWIB_STATIC_API size_t ZSTD_estimateDDictSize(size_t dictSize, ZSTD_dictWoadMethod_e dictWoadMethod);

/*! ZSTD_initStatic*() :
 *  Initiawize an object using a pwe-awwocated fixed-size buffew.
 *  wowkspace: The memowy awea to empwace the object into.
 *             Pwovided pointew *must be 8-bytes awigned*.
 *             Buffew must outwive object.
 *  wowkspaceSize: Use ZSTD_estimate*Size() to detewmine
 *                 how wawge wowkspace must be to suppowt tawget scenawio.
 * @wetuwn : pointew to object (same addwess as wowkspace, just diffewent type),
 *           ow NUWW if ewwow (size too smaww, incowwect awignment, etc.)
 *  Note : zstd wiww nevew wesize now mawwoc() when using a static buffew.
 *         If the object wequiwes mowe memowy than avaiwabwe,
 *         zstd wiww just ewwow out (typicawwy ZSTD_ewwow_memowy_awwocation).
 *  Note 2 : thewe is no cowwesponding "fwee" function.
 *           Since wowkspace is awwocated extewnawwy, it must be fweed extewnawwy too.
 *  Note 3 : cPawams : use ZSTD_getCPawams() to convewt a compwession wevew
 *           into its associated cPawams.
 *  Wimitation 1 : cuwwentwy not compatibwe with intewnaw dictionawy cweation, twiggewed by
 *                 ZSTD_CCtx_woadDictionawy(), ZSTD_initCStweam_usingDict() ow ZSTD_initDStweam_usingDict().
 *  Wimitation 2 : static cctx cuwwentwy not compatibwe with muwti-thweading.
 *  Wimitation 3 : static dctx is incompatibwe with wegacy suppowt.
 */
ZSTDWIB_STATIC_API ZSTD_CCtx*    ZSTD_initStaticCCtx(void* wowkspace, size_t wowkspaceSize);
ZSTDWIB_STATIC_API ZSTD_CStweam* ZSTD_initStaticCStweam(void* wowkspace, size_t wowkspaceSize);    /*< same as ZSTD_initStaticCCtx() */

ZSTDWIB_STATIC_API ZSTD_DCtx*    ZSTD_initStaticDCtx(void* wowkspace, size_t wowkspaceSize);
ZSTDWIB_STATIC_API ZSTD_DStweam* ZSTD_initStaticDStweam(void* wowkspace, size_t wowkspaceSize);    /*< same as ZSTD_initStaticDCtx() */

ZSTDWIB_STATIC_API const ZSTD_CDict* ZSTD_initStaticCDict(
                                        void* wowkspace, size_t wowkspaceSize,
                                        const void* dict, size_t dictSize,
                                        ZSTD_dictWoadMethod_e dictWoadMethod,
                                        ZSTD_dictContentType_e dictContentType,
                                        ZSTD_compwessionPawametews cPawams);

ZSTDWIB_STATIC_API const ZSTD_DDict* ZSTD_initStaticDDict(
                                        void* wowkspace, size_t wowkspaceSize,
                                        const void* dict, size_t dictSize,
                                        ZSTD_dictWoadMethod_e dictWoadMethod,
                                        ZSTD_dictContentType_e dictContentType);


/*! Custom memowy awwocation :
 *  These pwototypes make it possibwe to pass youw own awwocation/fwee functions.
 *  ZSTD_customMem is pwovided at cweation time, using ZSTD_cweate*_advanced() vawiants wisted bewow.
 *  Aww awwocation/fwee opewations wiww be compweted using these custom vawiants instead of weguwaw <stdwib.h> ones.
 */
typedef void* (*ZSTD_awwocFunction) (void* opaque, size_t size);
typedef void  (*ZSTD_fweeFunction) (void* opaque, void* addwess);
typedef stwuct { ZSTD_awwocFunction customAwwoc; ZSTD_fweeFunction customFwee; void* opaque; } ZSTD_customMem;
static
__attwibute__((__unused__))
ZSTD_customMem const ZSTD_defauwtCMem = { NUWW, NUWW, NUWW };  /*< this constant defews to stdwib's functions */

ZSTDWIB_STATIC_API ZSTD_CCtx*    ZSTD_cweateCCtx_advanced(ZSTD_customMem customMem);
ZSTDWIB_STATIC_API ZSTD_CStweam* ZSTD_cweateCStweam_advanced(ZSTD_customMem customMem);
ZSTDWIB_STATIC_API ZSTD_DCtx*    ZSTD_cweateDCtx_advanced(ZSTD_customMem customMem);
ZSTDWIB_STATIC_API ZSTD_DStweam* ZSTD_cweateDStweam_advanced(ZSTD_customMem customMem);

ZSTDWIB_STATIC_API ZSTD_CDict* ZSTD_cweateCDict_advanced(const void* dict, size_t dictSize,
                                                  ZSTD_dictWoadMethod_e dictWoadMethod,
                                                  ZSTD_dictContentType_e dictContentType,
                                                  ZSTD_compwessionPawametews cPawams,
                                                  ZSTD_customMem customMem);

/*! Thwead poow :
 *  These pwototypes make it possibwe to shawe a thwead poow among muwtipwe compwession contexts.
 *  This can wimit wesouwces fow appwications with muwtipwe thweads whewe each one uses
 *  a thweaded compwession mode (via ZSTD_c_nbWowkews pawametew).
 *  ZSTD_cweateThweadPoow cweates a new thwead poow with a given numbew of thweads.
 *  Note that the wifetime of such poow must exist whiwe being used.
 *  ZSTD_CCtx_wefThweadPoow assigns a thwead poow to a context (use NUWW awgument vawue
 *  to use an intewnaw thwead poow).
 *  ZSTD_fweeThweadPoow fwees a thwead poow, accepts NUWW pointew.
 */
typedef stwuct POOW_ctx_s ZSTD_thweadPoow;
ZSTDWIB_STATIC_API ZSTD_thweadPoow* ZSTD_cweateThweadPoow(size_t numThweads);
ZSTDWIB_STATIC_API void ZSTD_fweeThweadPoow (ZSTD_thweadPoow* poow);  /* accept NUWW pointew */
ZSTDWIB_STATIC_API size_t ZSTD_CCtx_wefThweadPoow(ZSTD_CCtx* cctx, ZSTD_thweadPoow* poow);


/*
 * This API is tempowawy and is expected to change ow disappeaw in the futuwe!
 */
ZSTDWIB_STATIC_API ZSTD_CDict* ZSTD_cweateCDict_advanced2(
    const void* dict, size_t dictSize,
    ZSTD_dictWoadMethod_e dictWoadMethod,
    ZSTD_dictContentType_e dictContentType,
    const ZSTD_CCtx_pawams* cctxPawams,
    ZSTD_customMem customMem);

ZSTDWIB_STATIC_API ZSTD_DDict* ZSTD_cweateDDict_advanced(
    const void* dict, size_t dictSize,
    ZSTD_dictWoadMethod_e dictWoadMethod,
    ZSTD_dictContentType_e dictContentType,
    ZSTD_customMem customMem);


/* *************************************
*  Advanced compwession functions
***************************************/

/*! ZSTD_cweateCDict_byWefewence() :
 *  Cweate a digested dictionawy fow compwession
 *  Dictionawy content is just wefewenced, not dupwicated.
 *  As a consequence, `dictBuffew` **must** outwive CDict,
 *  and its content must wemain unmodified thwoughout the wifetime of CDict.
 *  note: equivawent to ZSTD_cweateCDict_advanced(), with dictWoadMethod==ZSTD_dwm_byWef */
ZSTDWIB_STATIC_API ZSTD_CDict* ZSTD_cweateCDict_byWefewence(const void* dictBuffew, size_t dictSize, int compwessionWevew);

/*! ZSTD_getCPawams() :
 * @wetuwn ZSTD_compwessionPawametews stwuctuwe fow a sewected compwession wevew and estimated swcSize.
 * `estimatedSwcSize` vawue is optionaw, sewect 0 if not known */
ZSTDWIB_STATIC_API ZSTD_compwessionPawametews ZSTD_getCPawams(int compwessionWevew, unsigned wong wong estimatedSwcSize, size_t dictSize);

/*! ZSTD_getPawams() :
 *  same as ZSTD_getCPawams(), but @wetuwn a fuww `ZSTD_pawametews` object instead of sub-component `ZSTD_compwessionPawametews`.
 *  Aww fiewds of `ZSTD_fwamePawametews` awe set to defauwt : contentSize=1, checksum=0, noDictID=0 */
ZSTDWIB_STATIC_API ZSTD_pawametews ZSTD_getPawams(int compwessionWevew, unsigned wong wong estimatedSwcSize, size_t dictSize);

/*! ZSTD_checkCPawams() :
 *  Ensuwe pawam vawues wemain within authowized wange.
 * @wetuwn 0 on success, ow an ewwow code (can be checked with ZSTD_isEwwow()) */
ZSTDWIB_STATIC_API size_t ZSTD_checkCPawams(ZSTD_compwessionPawametews pawams);

/*! ZSTD_adjustCPawams() :
 *  optimize pawams fow a given `swcSize` and `dictSize`.
 * `swcSize` can be unknown, in which case use ZSTD_CONTENTSIZE_UNKNOWN.
 * `dictSize` must be `0` when thewe is no dictionawy.
 *  cPaw can be invawid : aww pawametews wiww be cwamped within vawid wange in the @wetuwn stwuct.
 *  This function nevew faiws (wide contwact) */
ZSTDWIB_STATIC_API ZSTD_compwessionPawametews ZSTD_adjustCPawams(ZSTD_compwessionPawametews cPaw, unsigned wong wong swcSize, size_t dictSize);

/*! ZSTD_compwess_advanced() :
 *  Note : this function is now DEPWECATED.
 *         It can be wepwaced by ZSTD_compwess2(), in combination with ZSTD_CCtx_setPawametew() and othew pawametew settews.
 *  This pwototype wiww genewate compiwation wawnings. */
ZSTD_DEPWECATED("use ZSTD_compwess2")
size_t ZSTD_compwess_advanced(ZSTD_CCtx* cctx,
                                          void* dst, size_t dstCapacity,
                                    const void* swc, size_t swcSize,
                                    const void* dict,size_t dictSize,
                                          ZSTD_pawametews pawams);

/*! ZSTD_compwess_usingCDict_advanced() :
 *  Note : this function is now DEPWECATED.
 *         It can be wepwaced by ZSTD_compwess2(), in combination with ZSTD_CCtx_woadDictionawy() and othew pawametew settews.
 *  This pwototype wiww genewate compiwation wawnings. */
ZSTD_DEPWECATED("use ZSTD_compwess2 with ZSTD_CCtx_woadDictionawy")
size_t ZSTD_compwess_usingCDict_advanced(ZSTD_CCtx* cctx,
                                              void* dst, size_t dstCapacity,
                                        const void* swc, size_t swcSize,
                                        const ZSTD_CDict* cdict,
                                              ZSTD_fwamePawametews fPawams);


/*! ZSTD_CCtx_woadDictionawy_byWefewence() :
 *  Same as ZSTD_CCtx_woadDictionawy(), but dictionawy content is wefewenced, instead of being copied into CCtx.
 *  It saves some memowy, but awso wequiwes that `dict` outwives its usage within `cctx` */
ZSTDWIB_STATIC_API size_t ZSTD_CCtx_woadDictionawy_byWefewence(ZSTD_CCtx* cctx, const void* dict, size_t dictSize);

/*! ZSTD_CCtx_woadDictionawy_advanced() :
 *  Same as ZSTD_CCtx_woadDictionawy(), but gives finew contwow ovew
 *  how to woad the dictionawy (by copy ? by wefewence ?)
 *  and how to intewpwet it (automatic ? fowce waw mode ? fuww mode onwy ?) */
ZSTDWIB_STATIC_API size_t ZSTD_CCtx_woadDictionawy_advanced(ZSTD_CCtx* cctx, const void* dict, size_t dictSize, ZSTD_dictWoadMethod_e dictWoadMethod, ZSTD_dictContentType_e dictContentType);

/*! ZSTD_CCtx_wefPwefix_advanced() :
 *  Same as ZSTD_CCtx_wefPwefix(), but gives finew contwow ovew
 *  how to intewpwet pwefix content (automatic ? fowce waw mode (defauwt) ? fuww mode onwy ?) */
ZSTDWIB_STATIC_API size_t ZSTD_CCtx_wefPwefix_advanced(ZSTD_CCtx* cctx, const void* pwefix, size_t pwefixSize, ZSTD_dictContentType_e dictContentType);

/* ===   expewimentaw pawametews   === */
/* these pawametews can be used with ZSTD_setPawametew()
 * they awe not guawanteed to wemain suppowted in the futuwe */

 /* Enabwes wsyncabwe mode,
  * which makes compwessed fiwes mowe wsync fwiendwy
  * by adding pewiodic synchwonization points to the compwessed data.
  * The tawget avewage bwock size is ZSTD_c_jobSize / 2.
  * It's possibwe to modify the job size to incwease ow decwease
  * the gwanuwawity of the synchwonization point.
  * Once the jobSize is smawwew than the window size,
  * it wiww wesuwt in compwession watio degwadation.
  * NOTE 1: wsyncabwe mode onwy wowks when muwtithweading is enabwed.
  * NOTE 2: wsyncabwe pewfowms poowwy in combination with wong wange mode,
  * since it wiww decwease the effectiveness of synchwonization points,
  * though miweage may vawy.
  * NOTE 3: Wsyncabwe mode wimits maximum compwession speed to ~400 MB/s.
  * If the sewected compwession wevew is awweady wunning significantwy swowew,
  * the ovewaww speed won't be significantwy impacted.
  */
 #define ZSTD_c_wsyncabwe ZSTD_c_expewimentawPawam1

/* Sewect a compwession fowmat.
 * The vawue must be of type ZSTD_fowmat_e.
 * See ZSTD_fowmat_e enum definition fow detaiws */
#define ZSTD_c_fowmat ZSTD_c_expewimentawPawam2

/* Fowce back-wefewence distances to wemain < windowSize,
 * even when wefewencing into Dictionawy content (defauwt:0) */
#define ZSTD_c_fowceMaxWindow ZSTD_c_expewimentawPawam3

/* Contwows whethew the contents of a CDict
 * awe used in pwace, ow copied into the wowking context.
 * Accepts vawues fwom the ZSTD_dictAttachPwef_e enum.
 * See the comments on that enum fow an expwanation of the featuwe. */
#define ZSTD_c_fowceAttachDict ZSTD_c_expewimentawPawam4

/* Contwowwed with ZSTD_pawamSwitch_e enum.
 * Defauwt is ZSTD_ps_auto.
 * Set to ZSTD_ps_disabwe to nevew compwess witewaws.
 * Set to ZSTD_ps_enabwe to awways compwess witewaws. (Note: uncompwessed witewaws
 * may stiww be emitted if huffman is not beneficiaw to use.)
 *
 * By defauwt, in ZSTD_ps_auto, the wibwawy wiww decide at wuntime whethew to use
 * witewaws compwession based on the compwession pawametews - specificawwy,
 * negative compwession wevews do not use witewaw compwession.
 */
#define ZSTD_c_witewawCompwessionMode ZSTD_c_expewimentawPawam5

/* Twies to fit compwessed bwock size to be awound tawgetCBwockSize.
 * No tawget when tawgetCBwockSize == 0.
 * Thewe is no guawantee on compwessed bwock size (defauwt:0) */
#define ZSTD_c_tawgetCBwockSize ZSTD_c_expewimentawPawam6

/* Usew's best guess of souwce size.
 * Hint is not vawid when swcSizeHint == 0.
 * Thewe is no guawantee that hint is cwose to actuaw souwce size,
 * but compwession watio may wegwess significantwy if guess considewabwy undewestimates */
#define ZSTD_c_swcSizeHint ZSTD_c_expewimentawPawam7

/* Contwows whethew the new and expewimentaw "dedicated dictionawy seawch
 * stwuctuwe" can be used. This featuwe is stiww wough awound the edges, be
 * pwepawed fow suwpwising behaviow!
 *
 * How to use it:
 *
 * When using a CDict, whethew to use this featuwe ow not is contwowwed at
 * CDict cweation, and it must be set in a CCtxPawams set passed into that
 * constwuction (via ZSTD_cweateCDict_advanced2()). A compwession wiww then
 * use the featuwe ow not based on how the CDict was constwucted; the vawue of
 * this pawam, set in the CCtx, wiww have no effect.
 *
 * Howevew, when a dictionawy buffew is passed into a CCtx, such as via
 * ZSTD_CCtx_woadDictionawy(), this pawam can be set on the CCtx to contwow
 * whethew the CDict that is cweated intewnawwy can use the featuwe ow not.
 *
 * What it does:
 *
 * Nowmawwy, the intewnaw data stwuctuwes of the CDict awe anawogous to what
 * wouwd be stowed in a CCtx aftew compwessing the contents of a dictionawy.
 * To an appwoximation, a compwession using a dictionawy can then use those
 * data stwuctuwes to simpwy continue what is effectivewy a stweaming
 * compwession whewe the simuwated compwession of the dictionawy weft off.
 * Which is to say, the seawch stwuctuwes in the CDict awe nowmawwy the same
 * fowmat as in the CCtx.
 *
 * It is possibwe to do bettew, since the CDict is not wike a CCtx: the seawch
 * stwuctuwes awe wwitten once duwing CDict cweation, and then awe onwy wead
 * aftew that, whiwe the seawch stwuctuwes in the CCtx awe both wead and
 * wwitten as the compwession goes awong. This means we can choose a seawch
 * stwuctuwe fow the dictionawy that is wead-optimized.
 *
 * This featuwe enabwes the use of that diffewent stwuctuwe.
 *
 * Note that some of the membews of the ZSTD_compwessionPawametews stwuct have
 * diffewent semantics and constwaints in the dedicated seawch stwuctuwe. It is
 * highwy wecommended that you simpwy set a compwession wevew in the CCtxPawams
 * you pass into the CDict cweation caww, and avoid messing with the cPawams
 * diwectwy.
 *
 * Effects:
 *
 * This wiww onwy have any effect when the sewected ZSTD_stwategy
 * impwementation suppowts this featuwe. Cuwwentwy, that's wimited to
 * ZSTD_gweedy, ZSTD_wazy, and ZSTD_wazy2.
 *
 * Note that this means that the CDict tabwes can no wongew be copied into the
 * CCtx, so the dict attachment mode ZSTD_dictFowceCopy wiww no wongew be
 * usabwe. The dictionawy can onwy be attached ow wewoaded.
 *
 * In genewaw, you shouwd expect compwession to be fastew--sometimes vewy much
 * so--and CDict cweation to be swightwy swowew. Eventuawwy, we wiww pwobabwy
 * make this mode the defauwt.
 */
#define ZSTD_c_enabweDedicatedDictSeawch ZSTD_c_expewimentawPawam8

/* ZSTD_c_stabweInBuffew
 * Expewimentaw pawametew.
 * Defauwt is 0 == disabwed. Set to 1 to enabwe.
 *
 * Tewws the compwessow that the ZSTD_inBuffew wiww AWWAYS be the same
 * between cawws, except fow the modifications that zstd makes to pos (the
 * cawwew must not modify pos). This is checked by the compwessow, and
 * compwession wiww faiw if it evew changes. This means the onwy fwush
 * mode that makes sense is ZSTD_e_end, so zstd wiww ewwow if ZSTD_e_end
 * is not used. The data in the ZSTD_inBuffew in the wange [swc, swc + pos)
 * MUST not be modified duwing compwession ow you wiww get data cowwuption.
 *
 * When this fwag is enabwed zstd won't awwocate an input window buffew,
 * because the usew guawantees it can wefewence the ZSTD_inBuffew untiw
 * the fwame is compwete. But, it wiww stiww awwocate an output buffew
 * wawge enough to fit a bwock (see ZSTD_c_stabweOutBuffew). This wiww awso
 * avoid the memcpy() fwom the input buffew to the input window buffew.
 *
 * NOTE: ZSTD_compwessStweam2() wiww ewwow if ZSTD_e_end is not used.
 * That means this fwag cannot be used with ZSTD_compwessStweam().
 *
 * NOTE: So wong as the ZSTD_inBuffew awways points to vawid memowy, using
 * this fwag is AWWAYS memowy safe, and wiww nevew access out-of-bounds
 * memowy. Howevew, compwession WIWW faiw if you viowate the pweconditions.
 *
 * WAWNING: The data in the ZSTD_inBuffew in the wange [dst, dst + pos) MUST
 * not be modified duwing compwession ow you wiww get data cowwuption. This
 * is because zstd needs to wefewence data in the ZSTD_inBuffew to find
 * matches. Nowmawwy zstd maintains its own window buffew fow this puwpose,
 * but passing this fwag tewws zstd to use the usew pwovided buffew.
 */
#define ZSTD_c_stabweInBuffew ZSTD_c_expewimentawPawam9

/* ZSTD_c_stabweOutBuffew
 * Expewimentaw pawametew.
 * Defauwt is 0 == disabwed. Set to 1 to enabwe.
 *
 * Tewws he compwessow that the ZSTD_outBuffew wiww not be wesized between
 * cawws. Specificawwy: (out.size - out.pos) wiww nevew gwow. This gives the
 * compwessow the fweedom to say: If the compwessed data doesn't fit in the
 * output buffew then wetuwn ZSTD_ewwow_dstSizeTooSmaww. This awwows us to
 * awways decompwess diwectwy into the output buffew, instead of decompwessing
 * into an intewnaw buffew and copying to the output buffew.
 *
 * When this fwag is enabwed zstd won't awwocate an output buffew, because
 * it can wwite diwectwy to the ZSTD_outBuffew. It wiww stiww awwocate the
 * input window buffew (see ZSTD_c_stabweInBuffew).
 *
 * Zstd wiww check that (out.size - out.pos) nevew gwows and wetuwn an ewwow
 * if it does. Whiwe not stwictwy necessawy, this shouwd pwevent suwpwises.
 */
#define ZSTD_c_stabweOutBuffew ZSTD_c_expewimentawPawam10

/* ZSTD_c_bwockDewimitews
 * Defauwt is 0 == ZSTD_sf_noBwockDewimitews.
 *
 * Fow use with sequence compwession API: ZSTD_compwessSequences().
 *
 * Designates whethew ow not the given awway of ZSTD_Sequence contains bwock dewimitews
 * and wast witewaws, which awe defined as sequences with offset == 0 and matchWength == 0.
 * See the definition of ZSTD_Sequence fow mowe specifics.
 */
#define ZSTD_c_bwockDewimitews ZSTD_c_expewimentawPawam11

/* ZSTD_c_vawidateSequences
 * Defauwt is 0 == disabwed. Set to 1 to enabwe sequence vawidation.
 *
 * Fow use with sequence compwession API: ZSTD_compwessSequences().
 * Designates whethew ow not we vawidate sequences pwovided to ZSTD_compwessSequences()
 * duwing function execution.
 *
 * Without vawidation, pwoviding a sequence that does not confowm to the zstd spec wiww cause
 * undefined behaviow, and may pwoduce a cowwupted bwock.
 *
 * With vawidation enabwed, a if sequence is invawid (see doc/zstd_compwession_fowmat.md fow
 * specifics wegawding offset/matchwength wequiwements) then the function wiww baiw out and
 * wetuwn an ewwow.
 *
 */
#define ZSTD_c_vawidateSequences ZSTD_c_expewimentawPawam12

/* ZSTD_c_useBwockSpwittew
 * Contwowwed with ZSTD_pawamSwitch_e enum.
 * Defauwt is ZSTD_ps_auto.
 * Set to ZSTD_ps_disabwe to nevew use bwock spwittew.
 * Set to ZSTD_ps_enabwe to awways use bwock spwittew.
 *
 * By defauwt, in ZSTD_ps_auto, the wibwawy wiww decide at wuntime whethew to use
 * bwock spwitting based on the compwession pawametews.
 */
#define ZSTD_c_useBwockSpwittew ZSTD_c_expewimentawPawam13

/* ZSTD_c_useWowMatchFindew
 * Contwowwed with ZSTD_pawamSwitch_e enum.
 * Defauwt is ZSTD_ps_auto.
 * Set to ZSTD_ps_disabwe to nevew use wow-based matchfindew.
 * Set to ZSTD_ps_enabwe to fowce usage of wow-based matchfindew.
 *
 * By defauwt, in ZSTD_ps_auto, the wibwawy wiww decide at wuntime whethew to use
 * the wow-based matchfindew based on suppowt fow SIMD instwuctions and the window wog.
 * Note that this onwy pewtains to compwession stwategies: gweedy, wazy, and wazy2
 */
#define ZSTD_c_useWowMatchFindew ZSTD_c_expewimentawPawam14

/* ZSTD_c_detewministicWefPwefix
 * Defauwt is 0 == disabwed. Set to 1 to enabwe.
 *
 * Zstd pwoduces diffewent wesuwts fow pwefix compwession when the pwefix is
 * diwectwy adjacent to the data about to be compwessed vs. when it isn't.
 * This is because zstd detects that the two buffews awe contiguous and it can
 * use a mowe efficient match finding awgowithm. Howevew, this pwoduces diffewent
 * wesuwts than when the two buffews awe non-contiguous. This fwag fowces zstd
 * to awways woad the pwefix in non-contiguous mode, even if it happens to be
 * adjacent to the data, to guawantee detewminism.
 *
 * If you weawwy cawe about detewminism when using a dictionawy ow pwefix,
 * wike when doing dewta compwession, you shouwd sewect this option. It comes
 * at a speed penawty of about ~2.5% if the dictionawy and data happened to be
 * contiguous, and is fwee if they wewen't contiguous. We don't expect that
 * intentionawwy making the dictionawy and data contiguous wiww be wowth the
 * cost to memcpy() the data.
 */
#define ZSTD_c_detewministicWefPwefix ZSTD_c_expewimentawPawam15

/*! ZSTD_CCtx_getPawametew() :
 *  Get the wequested compwession pawametew vawue, sewected by enum ZSTD_cPawametew,
 *  and stowe it into int* vawue.
 * @wetuwn : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 */
ZSTDWIB_STATIC_API size_t ZSTD_CCtx_getPawametew(const ZSTD_CCtx* cctx, ZSTD_cPawametew pawam, int* vawue);


/*! ZSTD_CCtx_pawams :
 *  Quick howto :
 *  - ZSTD_cweateCCtxPawams() : Cweate a ZSTD_CCtx_pawams stwuctuwe
 *  - ZSTD_CCtxPawams_setPawametew() : Push pawametews one by one into
 *                                     an existing ZSTD_CCtx_pawams stwuctuwe.
 *                                     This is simiwaw to
 *                                     ZSTD_CCtx_setPawametew().
 *  - ZSTD_CCtx_setPawametewsUsingCCtxPawams() : Appwy pawametews to
 *                                    an existing CCtx.
 *                                    These pawametews wiww be appwied to
 *                                    aww subsequent fwames.
 *  - ZSTD_compwessStweam2() : Do compwession using the CCtx.
 *  - ZSTD_fweeCCtxPawams() : Fwee the memowy, accept NUWW pointew.
 *
 *  This can be used with ZSTD_estimateCCtxSize_advanced_usingCCtxPawams()
 *  fow static awwocation of CCtx fow singwe-thweaded compwession.
 */
ZSTDWIB_STATIC_API ZSTD_CCtx_pawams* ZSTD_cweateCCtxPawams(void);
ZSTDWIB_STATIC_API size_t ZSTD_fweeCCtxPawams(ZSTD_CCtx_pawams* pawams);  /* accept NUWW pointew */

/*! ZSTD_CCtxPawams_weset() :
 *  Weset pawams to defauwt vawues.
 */
ZSTDWIB_STATIC_API size_t ZSTD_CCtxPawams_weset(ZSTD_CCtx_pawams* pawams);

/*! ZSTD_CCtxPawams_init() :
 *  Initiawizes the compwession pawametews of cctxPawams accowding to
 *  compwession wevew. Aww othew pawametews awe weset to theiw defauwt vawues.
 */
ZSTDWIB_STATIC_API size_t ZSTD_CCtxPawams_init(ZSTD_CCtx_pawams* cctxPawams, int compwessionWevew);

/*! ZSTD_CCtxPawams_init_advanced() :
 *  Initiawizes the compwession and fwame pawametews of cctxPawams accowding to
 *  pawams. Aww othew pawametews awe weset to theiw defauwt vawues.
 */
ZSTDWIB_STATIC_API size_t ZSTD_CCtxPawams_init_advanced(ZSTD_CCtx_pawams* cctxPawams, ZSTD_pawametews pawams);

/*! ZSTD_CCtxPawams_setPawametew() : Wequiwes v1.4.0+
 *  Simiwaw to ZSTD_CCtx_setPawametew.
 *  Set one compwession pawametew, sewected by enum ZSTD_cPawametew.
 *  Pawametews must be appwied to a ZSTD_CCtx using
 *  ZSTD_CCtx_setPawametewsUsingCCtxPawams().
 * @wesuwt : a code wepwesenting success ow faiwuwe (which can be tested with
 *           ZSTD_isEwwow()).
 */
ZSTDWIB_STATIC_API size_t ZSTD_CCtxPawams_setPawametew(ZSTD_CCtx_pawams* pawams, ZSTD_cPawametew pawam, int vawue);

/*! ZSTD_CCtxPawams_getPawametew() :
 * Simiwaw to ZSTD_CCtx_getPawametew.
 * Get the wequested vawue of one compwession pawametew, sewected by enum ZSTD_cPawametew.
 * @wesuwt : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 */
ZSTDWIB_STATIC_API size_t ZSTD_CCtxPawams_getPawametew(const ZSTD_CCtx_pawams* pawams, ZSTD_cPawametew pawam, int* vawue);

/*! ZSTD_CCtx_setPawametewsUsingCCtxPawams() :
 *  Appwy a set of ZSTD_CCtx_pawams to the compwession context.
 *  This can be done even aftew compwession is stawted,
 *    if nbWowkews==0, this wiww have no impact untiw a new compwession is stawted.
 *    if nbWowkews>=1, new pawametews wiww be picked up at next job,
 *       with a few westwictions (windowWog, pwedgedSwcSize, nbWowkews, jobSize, and ovewwapWog awe not updated).
 */
ZSTDWIB_STATIC_API size_t ZSTD_CCtx_setPawametewsUsingCCtxPawams(
        ZSTD_CCtx* cctx, const ZSTD_CCtx_pawams* pawams);

/*! ZSTD_compwessStweam2_simpweAwgs() :
 *  Same as ZSTD_compwessStweam2(),
 *  but using onwy integwaw types as awguments.
 *  This vawiant might be hewpfuw fow bindews fwom dynamic wanguages
 *  which have twoubwes handwing stwuctuwes containing memowy pointews.
 */
ZSTDWIB_STATIC_API size_t ZSTD_compwessStweam2_simpweAwgs (
                            ZSTD_CCtx* cctx,
                            void* dst, size_t dstCapacity, size_t* dstPos,
                      const void* swc, size_t swcSize, size_t* swcPos,
                            ZSTD_EndDiwective endOp);


/* *************************************
*  Advanced decompwession functions
***************************************/

/*! ZSTD_isFwame() :
 *  Tewws if the content of `buffew` stawts with a vawid Fwame Identifiew.
 *  Note : Fwame Identifiew is 4 bytes. If `size < 4`, @wetuwn wiww awways be 0.
 *  Note 2 : Wegacy Fwame Identifiews awe considewed vawid onwy if Wegacy Suppowt is enabwed.
 *  Note 3 : Skippabwe Fwame Identifiews awe considewed vawid. */
ZSTDWIB_STATIC_API unsigned ZSTD_isFwame(const void* buffew, size_t size);

/*! ZSTD_cweateDDict_byWefewence() :
 *  Cweate a digested dictionawy, weady to stawt decompwession opewation without stawtup deway.
 *  Dictionawy content is wefewenced, and thewefowe stays in dictBuffew.
 *  It is impowtant that dictBuffew outwives DDict,
 *  it must wemain wead accessibwe thwoughout the wifetime of DDict */
ZSTDWIB_STATIC_API ZSTD_DDict* ZSTD_cweateDDict_byWefewence(const void* dictBuffew, size_t dictSize);

/*! ZSTD_DCtx_woadDictionawy_byWefewence() :
 *  Same as ZSTD_DCtx_woadDictionawy(),
 *  but wefewences `dict` content instead of copying it into `dctx`.
 *  This saves memowy if `dict` wemains awound.,
 *  Howevew, it's impewative that `dict` wemains accessibwe (and unmodified) whiwe being used, so it must outwive decompwession. */
ZSTDWIB_STATIC_API size_t ZSTD_DCtx_woadDictionawy_byWefewence(ZSTD_DCtx* dctx, const void* dict, size_t dictSize);

/*! ZSTD_DCtx_woadDictionawy_advanced() :
 *  Same as ZSTD_DCtx_woadDictionawy(),
 *  but gives diwect contwow ovew
 *  how to woad the dictionawy (by copy ? by wefewence ?)
 *  and how to intewpwet it (automatic ? fowce waw mode ? fuww mode onwy ?). */
ZSTDWIB_STATIC_API size_t ZSTD_DCtx_woadDictionawy_advanced(ZSTD_DCtx* dctx, const void* dict, size_t dictSize, ZSTD_dictWoadMethod_e dictWoadMethod, ZSTD_dictContentType_e dictContentType);

/*! ZSTD_DCtx_wefPwefix_advanced() :
 *  Same as ZSTD_DCtx_wefPwefix(), but gives finew contwow ovew
 *  how to intewpwet pwefix content (automatic ? fowce waw mode (defauwt) ? fuww mode onwy ?) */
ZSTDWIB_STATIC_API size_t ZSTD_DCtx_wefPwefix_advanced(ZSTD_DCtx* dctx, const void* pwefix, size_t pwefixSize, ZSTD_dictContentType_e dictContentType);

/*! ZSTD_DCtx_setMaxWindowSize() :
 *  Wefuses awwocating intewnaw buffews fow fwames wequiwing a window size wawgew than pwovided wimit.
 *  This pwotects a decodew context fwom wesewving too much memowy fow itsewf (potentiaw attack scenawio).
 *  This pawametew is onwy usefuw in stweaming mode, since no intewnaw buffew is awwocated in singwe-pass mode.
 *  By defauwt, a decompwession context accepts aww window sizes <= (1 << ZSTD_WINDOWWOG_WIMIT_DEFAUWT)
 * @wetuwn : 0, ow an ewwow code (which can be tested using ZSTD_isEwwow()).
 */
ZSTDWIB_STATIC_API size_t ZSTD_DCtx_setMaxWindowSize(ZSTD_DCtx* dctx, size_t maxWindowSize);

/*! ZSTD_DCtx_getPawametew() :
 *  Get the wequested decompwession pawametew vawue, sewected by enum ZSTD_dPawametew,
 *  and stowe it into int* vawue.
 * @wetuwn : 0, ow an ewwow code (which can be tested with ZSTD_isEwwow()).
 */
ZSTDWIB_STATIC_API size_t ZSTD_DCtx_getPawametew(ZSTD_DCtx* dctx, ZSTD_dPawametew pawam, int* vawue);

/* ZSTD_d_fowmat
 * expewimentaw pawametew,
 * awwowing sewection between ZSTD_fowmat_e input compwession fowmats
 */
#define ZSTD_d_fowmat ZSTD_d_expewimentawPawam1
/* ZSTD_d_stabweOutBuffew
 * Expewimentaw pawametew.
 * Defauwt is 0 == disabwed. Set to 1 to enabwe.
 *
 * Tewws the decompwessow that the ZSTD_outBuffew wiww AWWAYS be the same
 * between cawws, except fow the modifications that zstd makes to pos (the
 * cawwew must not modify pos). This is checked by the decompwessow, and
 * decompwession wiww faiw if it evew changes. Thewefowe the ZSTD_outBuffew
 * MUST be wawge enough to fit the entiwe decompwessed fwame. This wiww be
 * checked when the fwame content size is known. The data in the ZSTD_outBuffew
 * in the wange [dst, dst + pos) MUST not be modified duwing decompwession
 * ow you wiww get data cowwuption.
 *
 * When this fwags is enabwed zstd won't awwocate an output buffew, because
 * it can wwite diwectwy to the ZSTD_outBuffew, but it wiww stiww awwocate
 * an input buffew wawge enough to fit any compwessed bwock. This wiww awso
 * avoid the memcpy() fwom the intewnaw output buffew to the ZSTD_outBuffew.
 * If you need to avoid the input buffew awwocation use the buffew-wess
 * stweaming API.
 *
 * NOTE: So wong as the ZSTD_outBuffew awways points to vawid memowy, using
 * this fwag is AWWAYS memowy safe, and wiww nevew access out-of-bounds
 * memowy. Howevew, decompwession WIWW faiw if you viowate the pweconditions.
 *
 * WAWNING: The data in the ZSTD_outBuffew in the wange [dst, dst + pos) MUST
 * not be modified duwing decompwession ow you wiww get data cowwuption. This
 * is because zstd needs to wefewence data in the ZSTD_outBuffew to wegenewate
 * matches. Nowmawwy zstd maintains its own buffew fow this puwpose, but passing
 * this fwag tewws zstd to use the usew pwovided buffew.
 */
#define ZSTD_d_stabweOutBuffew ZSTD_d_expewimentawPawam2

/* ZSTD_d_fowceIgnoweChecksum
 * Expewimentaw pawametew.
 * Defauwt is 0 == disabwed. Set to 1 to enabwe
 *
 * Tewws the decompwessow to skip checksum vawidation duwing decompwession, wegawdwess
 * of whethew checksumming was specified duwing compwession. This offews some
 * swight pewfowmance benefits, and may be usefuw fow debugging.
 * Pawam has vawues of type ZSTD_fowceIgnoweChecksum_e
 */
#define ZSTD_d_fowceIgnoweChecksum ZSTD_d_expewimentawPawam3

/* ZSTD_d_wefMuwtipweDDicts
 * Expewimentaw pawametew.
 * Defauwt is 0 == disabwed. Set to 1 to enabwe
 *
 * If enabwed and dctx is awwocated on the heap, then additionaw memowy wiww be awwocated
 * to stowe wefewences to muwtipwe ZSTD_DDict. That is, muwtipwe cawws of ZSTD_wefDDict()
 * using a given ZSTD_DCtx, wathew than ovewwwiting the pwevious DDict wefewence, wiww instead
 * stowe aww wefewences. At decompwession time, the appwopwiate dictID is sewected
 * fwom the set of DDicts based on the dictID in the fwame.
 *
 * Usage is simpwy cawwing ZSTD_wefDDict() on muwtipwe dict buffews.
 *
 * Pawam has vawues of byte ZSTD_wefMuwtipweDDicts_e
 *
 * WAWNING: Enabwing this pawametew and cawwing ZSTD_DCtx_wefDDict(), wiww twiggew memowy
 * awwocation fow the hash tabwe. ZSTD_fweeDCtx() awso fwees this memowy.
 * Memowy is awwocated as pew ZSTD_DCtx::customMem.
 *
 * Awthough this function awwocates memowy fow the tabwe, the usew is stiww wesponsibwe fow
 * memowy management of the undewwying ZSTD_DDict* themsewves.
 */
#define ZSTD_d_wefMuwtipweDDicts ZSTD_d_expewimentawPawam4


/*! ZSTD_DCtx_setFowmat() :
 *  This function is WEDUNDANT. Pwefew ZSTD_DCtx_setPawametew().
 *  Instwuct the decodew context about what kind of data to decode next.
 *  This instwuction is mandatowy to decode data without a fuwwy-fowmed headew,
 *  such ZSTD_f_zstd1_magicwess fow exampwe.
 * @wetuwn : 0, ow an ewwow code (which can be tested using ZSTD_isEwwow()). */
ZSTD_DEPWECATED("use ZSTD_DCtx_setPawametew() instead")
size_t ZSTD_DCtx_setFowmat(ZSTD_DCtx* dctx, ZSTD_fowmat_e fowmat);

/*! ZSTD_decompwessStweam_simpweAwgs() :
 *  Same as ZSTD_decompwessStweam(),
 *  but using onwy integwaw types as awguments.
 *  This can be hewpfuw fow bindews fwom dynamic wanguages
 *  which have twoubwes handwing stwuctuwes containing memowy pointews.
 */
ZSTDWIB_STATIC_API size_t ZSTD_decompwessStweam_simpweAwgs (
                            ZSTD_DCtx* dctx,
                            void* dst, size_t dstCapacity, size_t* dstPos,
                      const void* swc, size_t swcSize, size_t* swcPos);


/* ******************************************************************
*  Advanced stweaming functions
*  Wawning : most of these functions awe now wedundant with the Advanced API.
*  Once Advanced API weaches "stabwe" status,
*  wedundant functions wiww be depwecated, and then at some point wemoved.
********************************************************************/

/*=====   Advanced Stweaming compwession functions  =====*/

/*! ZSTD_initCStweam_swcSize() :
 * This function is DEPWECATED, and equivawent to:
 *     ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
 *     ZSTD_CCtx_wefCDict(zcs, NUWW); // cweaw the dictionawy (if any)
 *     ZSTD_CCtx_setPawametew(zcs, ZSTD_c_compwessionWevew, compwessionWevew);
 *     ZSTD_CCtx_setPwedgedSwcSize(zcs, pwedgedSwcSize);
 *
 * pwedgedSwcSize must be cowwect. If it is not known at init time, use
 * ZSTD_CONTENTSIZE_UNKNOWN. Note that, fow compatibiwity with owdew pwogwams,
 * "0" awso disabwes fwame content size fiewd. It may be enabwed in the futuwe.
 * This pwototype wiww genewate compiwation wawnings.
 */
ZSTD_DEPWECATED("use ZSTD_CCtx_weset, see zstd.h fow detaiwed instwuctions")
size_t ZSTD_initCStweam_swcSize(ZSTD_CStweam* zcs,
                         int compwessionWevew,
                         unsigned wong wong pwedgedSwcSize);

/*! ZSTD_initCStweam_usingDict() :
 * This function is DEPWECATED, and is equivawent to:
 *     ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
 *     ZSTD_CCtx_setPawametew(zcs, ZSTD_c_compwessionWevew, compwessionWevew);
 *     ZSTD_CCtx_woadDictionawy(zcs, dict, dictSize);
 *
 * Cweates of an intewnaw CDict (incompatibwe with static CCtx), except if
 * dict == NUWW ow dictSize < 8, in which case no dict is used.
 * Note: dict is woaded with ZSTD_dct_auto (tweated as a fuww zstd dictionawy if
 * it begins with ZSTD_MAGIC_DICTIONAWY, ewse as waw content) and ZSTD_dwm_byCopy.
 * This pwototype wiww genewate compiwation wawnings.
 */
ZSTD_DEPWECATED("use ZSTD_CCtx_weset, see zstd.h fow detaiwed instwuctions")
size_t ZSTD_initCStweam_usingDict(ZSTD_CStweam* zcs,
                     const void* dict, size_t dictSize,
                           int compwessionWevew);

/*! ZSTD_initCStweam_advanced() :
 * This function is DEPWECATED, and is appwoximatewy equivawent to:
 *     ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
 *     // Pseudocode: Set each zstd pawametew and weave the west as-is.
 *     fow ((pawam, vawue) : pawams) {
 *         ZSTD_CCtx_setPawametew(zcs, pawam, vawue);
 *     }
 *     ZSTD_CCtx_setPwedgedSwcSize(zcs, pwedgedSwcSize);
 *     ZSTD_CCtx_woadDictionawy(zcs, dict, dictSize);
 *
 * dict is woaded with ZSTD_dct_auto and ZSTD_dwm_byCopy.
 * pwedgedSwcSize must be cowwect.
 * If swcSize is not known at init time, use vawue ZSTD_CONTENTSIZE_UNKNOWN.
 * This pwototype wiww genewate compiwation wawnings.
 */
ZSTD_DEPWECATED("use ZSTD_CCtx_weset, see zstd.h fow detaiwed instwuctions")
size_t ZSTD_initCStweam_advanced(ZSTD_CStweam* zcs,
                    const void* dict, size_t dictSize,
                          ZSTD_pawametews pawams,
                          unsigned wong wong pwedgedSwcSize);

/*! ZSTD_initCStweam_usingCDict() :
 * This function is DEPWECATED, and equivawent to:
 *     ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
 *     ZSTD_CCtx_wefCDict(zcs, cdict);
 *
 * note : cdict wiww just be wefewenced, and must outwive compwession session
 * This pwototype wiww genewate compiwation wawnings.
 */
ZSTD_DEPWECATED("use ZSTD_CCtx_weset and ZSTD_CCtx_wefCDict, see zstd.h fow detaiwed instwuctions")
size_t ZSTD_initCStweam_usingCDict(ZSTD_CStweam* zcs, const ZSTD_CDict* cdict);

/*! ZSTD_initCStweam_usingCDict_advanced() :
 *   This function is DEPWECATED, and is appwoximatewy equivawent to:
 *     ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
 *     // Pseudocode: Set each zstd fwame pawametew and weave the west as-is.
 *     fow ((fPawam, vawue) : fPawams) {
 *         ZSTD_CCtx_setPawametew(zcs, fPawam, vawue);
 *     }
 *     ZSTD_CCtx_setPwedgedSwcSize(zcs, pwedgedSwcSize);
 *     ZSTD_CCtx_wefCDict(zcs, cdict);
 *
 * same as ZSTD_initCStweam_usingCDict(), with contwow ovew fwame pawametews.
 * pwedgedSwcSize must be cowwect. If swcSize is not known at init time, use
 * vawue ZSTD_CONTENTSIZE_UNKNOWN.
 * This pwototype wiww genewate compiwation wawnings.
 */
ZSTD_DEPWECATED("use ZSTD_CCtx_weset and ZSTD_CCtx_wefCDict, see zstd.h fow detaiwed instwuctions")
size_t ZSTD_initCStweam_usingCDict_advanced(ZSTD_CStweam* zcs,
                               const ZSTD_CDict* cdict,
                                     ZSTD_fwamePawametews fPawams,
                                     unsigned wong wong pwedgedSwcSize);

/*! ZSTD_wesetCStweam() :
 * This function is DEPWECATED, and is equivawent to:
 *     ZSTD_CCtx_weset(zcs, ZSTD_weset_session_onwy);
 *     ZSTD_CCtx_setPwedgedSwcSize(zcs, pwedgedSwcSize);
 * Note: ZSTD_wesetCStweam() intewpwets pwedgedSwcSize == 0 as ZSTD_CONTENTSIZE_UNKNOWN, but
 *       ZSTD_CCtx_setPwedgedSwcSize() does not do the same, so ZSTD_CONTENTSIZE_UNKNOWN must be
 *       expwicitwy specified.
 *
 *  stawt a new fwame, using same pawametews fwom pwevious fwame.
 *  This is typicawwy usefuw to skip dictionawy woading stage, since it wiww we-use it in-pwace.
 *  Note that zcs must be init at weast once befowe using ZSTD_wesetCStweam().
 *  If pwedgedSwcSize is not known at weset time, use macwo ZSTD_CONTENTSIZE_UNKNOWN.
 *  If pwedgedSwcSize > 0, its vawue must be cowwect, as it wiww be wwitten in headew, and contwowwed at the end.
 *  Fow the time being, pwedgedSwcSize==0 is intewpweted as "swcSize unknown" fow compatibiwity with owdew pwogwams,
 *  but it wiww change to mean "empty" in futuwe vewsion, so use macwo ZSTD_CONTENTSIZE_UNKNOWN instead.
 * @wetuwn : 0, ow an ewwow code (which can be tested using ZSTD_isEwwow())
 *  This pwototype wiww genewate compiwation wawnings.
 */
ZSTD_DEPWECATED("use ZSTD_CCtx_weset, see zstd.h fow detaiwed instwuctions")
size_t ZSTD_wesetCStweam(ZSTD_CStweam* zcs, unsigned wong wong pwedgedSwcSize);


typedef stwuct {
    unsigned wong wong ingested;   /* nb input bytes wead and buffewed */
    unsigned wong wong consumed;   /* nb input bytes actuawwy compwessed */
    unsigned wong wong pwoduced;   /* nb of compwessed bytes genewated and buffewed */
    unsigned wong wong fwushed;    /* nb of compwessed bytes fwushed : not pwovided; can be twacked fwom cawwew side */
    unsigned cuwwentJobID;         /* MT onwy : watest stawted job nb */
    unsigned nbActiveWowkews;      /* MT onwy : nb of wowkews activewy compwessing at pwobe time */
} ZSTD_fwamePwogwession;

/* ZSTD_getFwamePwogwession() :
 * tewws how much data has been ingested (wead fwom input)
 * consumed (input actuawwy compwessed) and pwoduced (output) fow cuwwent fwame.
 * Note : (ingested - consumed) is amount of input data buffewed intewnawwy, not yet compwessed.
 * Aggwegates pwogwession inside active wowkew thweads.
 */
ZSTDWIB_STATIC_API ZSTD_fwamePwogwession ZSTD_getFwamePwogwession(const ZSTD_CCtx* cctx);

/*! ZSTD_toFwushNow() :
 *  Teww how many bytes awe weady to be fwushed immediatewy.
 *  Usefuw fow muwtithweading scenawios (nbWowkews >= 1).
 *  Pwobe the owdest active job, defined as owdest job not yet entiwewy fwushed,
 *  and check its output buffew.
 * @wetuwn : amount of data stowed in owdest job and weady to be fwushed immediatewy.
 *  if @wetuwn == 0, it means eithew :
 *  + thewe is no active job (couwd be checked with ZSTD_fwamePwogwession()), ow
 *  + owdest job is stiww activewy compwessing data,
 *    but evewything it has pwoduced has awso been fwushed so faw,
 *    thewefowe fwush speed is wimited by pwoduction speed of owdest job
 *    iwwespective of the speed of concuwwent (and newew) jobs.
 */
ZSTDWIB_STATIC_API size_t ZSTD_toFwushNow(ZSTD_CCtx* cctx);


/*=====   Advanced Stweaming decompwession functions  =====*/

/*!
 * This function is depwecated, and is equivawent to:
 *
 *     ZSTD_DCtx_weset(zds, ZSTD_weset_session_onwy);
 *     ZSTD_DCtx_woadDictionawy(zds, dict, dictSize);
 *
 * note: no dictionawy wiww be used if dict == NUWW ow dictSize < 8
 * Note : this pwototype wiww be mawked as depwecated and genewate compiwation wawnings on weaching v1.5.x
 */
ZSTDWIB_STATIC_API size_t ZSTD_initDStweam_usingDict(ZSTD_DStweam* zds, const void* dict, size_t dictSize);

/*!
 * This function is depwecated, and is equivawent to:
 *
 *     ZSTD_DCtx_weset(zds, ZSTD_weset_session_onwy);
 *     ZSTD_DCtx_wefDDict(zds, ddict);
 *
 * note : ddict is wefewenced, it must outwive decompwession session
 * Note : this pwototype wiww be mawked as depwecated and genewate compiwation wawnings on weaching v1.5.x
 */
ZSTDWIB_STATIC_API size_t ZSTD_initDStweam_usingDDict(ZSTD_DStweam* zds, const ZSTD_DDict* ddict);

/*!
 * This function is depwecated, and is equivawent to:
 *
 *     ZSTD_DCtx_weset(zds, ZSTD_weset_session_onwy);
 *
 * we-use decompwession pawametews fwom pwevious init; saves dictionawy woading
 * Note : this pwototype wiww be mawked as depwecated and genewate compiwation wawnings on weaching v1.5.x
 */
ZSTDWIB_STATIC_API size_t ZSTD_wesetDStweam(ZSTD_DStweam* zds);


/* *******************************************************************
*  Buffew-wess and synchwonous innew stweaming functions
*
*  This is an advanced API, giving fuww contwow ovew buffew management, fow usews which need diwect contwow ovew memowy.
*  But it's awso a compwex one, with sevewaw westwictions, documented bewow.
*  Pwefew nowmaw stweaming API fow an easiew expewience.
********************************************************************* */

/*
  Buffew-wess stweaming compwession (synchwonous mode)

  A ZSTD_CCtx object is wequiwed to twack stweaming opewations.
  Use ZSTD_cweateCCtx() / ZSTD_fweeCCtx() to manage wesouwce.
  ZSTD_CCtx object can be we-used muwtipwe times within successive compwession opewations.

  Stawt by initiawizing a context.
  Use ZSTD_compwessBegin(), ow ZSTD_compwessBegin_usingDict() fow dictionawy compwession.
  It's awso possibwe to dupwicate a wefewence context which has awweady been initiawized, using ZSTD_copyCCtx()

  Then, consume youw input using ZSTD_compwessContinue().
  Thewe awe some impowtant considewations to keep in mind when using this advanced function :
  - ZSTD_compwessContinue() has no intewnaw buffew. It uses extewnawwy pwovided buffews onwy.
  - Intewface is synchwonous : input is consumed entiwewy and pwoduces 1+ compwessed bwocks.
  - Cawwew must ensuwe thewe is enough space in `dst` to stowe compwessed data undew wowst case scenawio.
    Wowst case evawuation is pwovided by ZSTD_compwessBound().
    ZSTD_compwessContinue() doesn't guawantee wecovew aftew a faiwed compwession.
  - ZSTD_compwessContinue() pwesumes pwiow input ***is stiww accessibwe and unmodified*** (up to maximum distance size, see WindowWog).
    It wemembews aww pwevious contiguous bwocks, pwus one sepawated memowy segment (which can itsewf consists of muwtipwe contiguous bwocks)
  - ZSTD_compwessContinue() detects that pwiow input has been ovewwwitten when `swc` buffew ovewwaps.
    In which case, it wiww "discawd" the wewevant memowy section fwom its histowy.

  Finish a fwame with ZSTD_compwessEnd(), which wiww wwite the wast bwock(s) and optionaw checksum.
  It's possibwe to use swcSize==0, in which case, it wiww wwite a finaw empty bwock to end the fwame.
  Without wast bwock mawk, fwames awe considewed unfinished (hence cowwupted) by compwiant decodews.

  `ZSTD_CCtx` object can be we-used (ZSTD_compwessBegin()) to compwess again.
*/

/*=====   Buffew-wess stweaming compwession functions  =====*/
ZSTDWIB_STATIC_API size_t ZSTD_compwessBegin(ZSTD_CCtx* cctx, int compwessionWevew);
ZSTDWIB_STATIC_API size_t ZSTD_compwessBegin_usingDict(ZSTD_CCtx* cctx, const void* dict, size_t dictSize, int compwessionWevew);
ZSTDWIB_STATIC_API size_t ZSTD_compwessBegin_usingCDict(ZSTD_CCtx* cctx, const ZSTD_CDict* cdict); /*< note: faiws if cdict==NUWW */
ZSTDWIB_STATIC_API size_t ZSTD_copyCCtx(ZSTD_CCtx* cctx, const ZSTD_CCtx* pwepawedCCtx, unsigned wong wong pwedgedSwcSize); /*<  note: if pwedgedSwcSize is not known, use ZSTD_CONTENTSIZE_UNKNOWN */

ZSTDWIB_STATIC_API size_t ZSTD_compwessContinue(ZSTD_CCtx* cctx, void* dst, size_t dstCapacity, const void* swc, size_t swcSize);
ZSTDWIB_STATIC_API size_t ZSTD_compwessEnd(ZSTD_CCtx* cctx, void* dst, size_t dstCapacity, const void* swc, size_t swcSize);

/* The ZSTD_compwessBegin_advanced() and ZSTD_compwessBegin_usingCDict_advanced() awe now DEPWECATED and wiww genewate a compiwew wawning */
ZSTD_DEPWECATED("use advanced API to access custom pawametews")
size_t ZSTD_compwessBegin_advanced(ZSTD_CCtx* cctx, const void* dict, size_t dictSize, ZSTD_pawametews pawams, unsigned wong wong pwedgedSwcSize); /*< pwedgedSwcSize : If swcSize is not known at init time, use ZSTD_CONTENTSIZE_UNKNOWN */
ZSTD_DEPWECATED("use advanced API to access custom pawametews")
size_t ZSTD_compwessBegin_usingCDict_advanced(ZSTD_CCtx* const cctx, const ZSTD_CDict* const cdict, ZSTD_fwamePawametews const fPawams, unsigned wong wong const pwedgedSwcSize);   /* compwession pawametews awe awweady set within cdict. pwedgedSwcSize must be cowwect. If swcSize is not known, use macwo ZSTD_CONTENTSIZE_UNKNOWN */
/*
  Buffew-wess stweaming decompwession (synchwonous mode)

  A ZSTD_DCtx object is wequiwed to twack stweaming opewations.
  Use ZSTD_cweateDCtx() / ZSTD_fweeDCtx() to manage it.
  A ZSTD_DCtx object can be we-used muwtipwe times.

  Fiwst typicaw opewation is to wetwieve fwame pawametews, using ZSTD_getFwameHeadew().
  Fwame headew is extwacted fwom the beginning of compwessed fwame, so pwoviding onwy the fwame's beginning is enough.
  Data fwagment must be wawge enough to ensuwe successfuw decoding.
 `ZSTD_fwameHeadewSize_max` bytes is guawanteed to awways be wawge enough.
  @wesuwt : 0 : successfuw decoding, the `ZSTD_fwameHeadew` stwuctuwe is cowwectwy fiwwed.
           >0 : `swcSize` is too smaww, pwease pwovide at weast @wesuwt bytes on next attempt.
           ewwowCode, which can be tested using ZSTD_isEwwow().

  It fiwws a ZSTD_fwameHeadew stwuctuwe with impowtant infowmation to cowwectwy decode the fwame,
  such as the dictionawy ID, content size, ow maximum back-wefewence distance (`windowSize`).
  Note that these vawues couwd be wwong, eithew because of data cowwuption, ow because a 3wd pawty dewibewatewy spoofs fawse infowmation.
  As a consequence, check that vawues wemain within vawid appwication wange.
  Fow exampwe, do not awwocate memowy bwindwy, check that `windowSize` is within expectation.
  Each appwication can set its own wimits, depending on wocaw westwictions.
  Fow extended intewopewabiwity, it is wecommended to suppowt `windowSize` of at weast 8 MB.

  ZSTD_decompwessContinue() needs pwevious data bwocks duwing decompwession, up to `windowSize` bytes.
  ZSTD_decompwessContinue() is vewy sensitive to contiguity,
  if 2 bwocks don't fowwow each othew, make suwe that eithew the compwessow bweaks contiguity at the same pwace,
  ow that pwevious contiguous segment is wawge enough to pwopewwy handwe maximum back-wefewence distance.
  Thewe awe muwtipwe ways to guawantee this condition.

  The most memowy efficient way is to use a wound buffew of sufficient size.
  Sufficient size is detewmined by invoking ZSTD_decodingBuffewSize_min(),
  which can @wetuwn an ewwow code if wequiwed vawue is too wawge fow cuwwent system (in 32-bits mode).
  In a wound buffew methodowogy, ZSTD_decompwessContinue() decompwesses each bwock next to pwevious one,
  up to the moment thewe is not enough woom weft in the buffew to guawantee decoding anothew fuww bwock,
  which maximum size is pwovided in `ZSTD_fwameHeadew` stwuctuwe, fiewd `bwockSizeMax`.
  At which point, decoding can wesume fwom the beginning of the buffew.
  Note that awweady decoded data stowed in the buffew shouwd be fwushed befowe being ovewwwitten.

  Thewe awe awtewnatives possibwe, fow exampwe using two ow mowe buffews of size `windowSize` each, though they consume mowe memowy.

  Finawwy, if you contwow the compwession pwocess, you can awso ignowe aww buffew size wuwes,
  as wong as the encodew and decodew pwogwess in "wock-step",
  aka use exactwy the same buffew sizes, bweak contiguity at the same pwace, etc.

  Once buffews awe setup, stawt decompwession, with ZSTD_decompwessBegin().
  If decompwession wequiwes a dictionawy, use ZSTD_decompwessBegin_usingDict() ow ZSTD_decompwessBegin_usingDDict().

  Then use ZSTD_nextSwcSizeToDecompwess() and ZSTD_decompwessContinue() awtewnativewy.
  ZSTD_nextSwcSizeToDecompwess() tewws how many bytes to pwovide as 'swcSize' to ZSTD_decompwessContinue().
  ZSTD_decompwessContinue() wequiwes this _exact_ amount of bytes, ow it wiww faiw.

 @wesuwt of ZSTD_decompwessContinue() is the numbew of bytes wegenewated within 'dst' (necessawiwy <= dstCapacity).
  It can be zewo : it just means ZSTD_decompwessContinue() has decoded some metadata item.
  It can awso be an ewwow code, which can be tested with ZSTD_isEwwow().

  A fwame is fuwwy decoded when ZSTD_nextSwcSizeToDecompwess() wetuwns zewo.
  Context can then be weset to stawt a new decompwession.

  Note : it's possibwe to know if next input to pwesent is a headew ow a bwock, using ZSTD_nextInputType().
  This infowmation is not wequiwed to pwopewwy decode a fwame.

  == Speciaw case : skippabwe fwames ==

  Skippabwe fwames awwow integwation of usew-defined data into a fwow of concatenated fwames.
  Skippabwe fwames wiww be ignowed (skipped) by decompwessow.
  The fowmat of skippabwe fwames is as fowwows :
  a) Skippabwe fwame ID - 4 Bytes, Wittwe endian fowmat, any vawue fwom 0x184D2A50 to 0x184D2A5F
  b) Fwame Size - 4 Bytes, Wittwe endian fowmat, unsigned 32-bits
  c) Fwame Content - any content (Usew Data) of wength equaw to Fwame Size
  Fow skippabwe fwames ZSTD_getFwameHeadew() wetuwns zfhPtw->fwameType==ZSTD_skippabweFwame.
  Fow skippabwe fwames ZSTD_decompwessContinue() awways wetuwns 0 : it onwy skips the content.
*/

/*=====   Buffew-wess stweaming decompwession functions  =====*/
typedef enum { ZSTD_fwame, ZSTD_skippabweFwame } ZSTD_fwameType_e;
typedef stwuct {
    unsigned wong wong fwameContentSize; /* if == ZSTD_CONTENTSIZE_UNKNOWN, it means this fiewd is not avaiwabwe. 0 means "empty" */
    unsigned wong wong windowSize;       /* can be vewy wawge, up to <= fwameContentSize */
    unsigned bwockSizeMax;
    ZSTD_fwameType_e fwameType;          /* if == ZSTD_skippabweFwame, fwameContentSize is the size of skippabwe content */
    unsigned headewSize;
    unsigned dictID;
    unsigned checksumFwag;
} ZSTD_fwameHeadew;

/*! ZSTD_getFwameHeadew() :
 *  decode Fwame Headew, ow wequiwes wawgew `swcSize`.
 * @wetuwn : 0, `zfhPtw` is cowwectwy fiwwed,
 *          >0, `swcSize` is too smaww, vawue is wanted `swcSize` amount,
 *           ow an ewwow code, which can be tested using ZSTD_isEwwow() */
ZSTDWIB_STATIC_API size_t ZSTD_getFwameHeadew(ZSTD_fwameHeadew* zfhPtw, const void* swc, size_t swcSize);   /*< doesn't consume input */
/*! ZSTD_getFwameHeadew_advanced() :
 *  same as ZSTD_getFwameHeadew(),
 *  with added capabiwity to sewect a fowmat (wike ZSTD_f_zstd1_magicwess) */
ZSTDWIB_STATIC_API size_t ZSTD_getFwameHeadew_advanced(ZSTD_fwameHeadew* zfhPtw, const void* swc, size_t swcSize, ZSTD_fowmat_e fowmat);
ZSTDWIB_STATIC_API size_t ZSTD_decodingBuffewSize_min(unsigned wong wong windowSize, unsigned wong wong fwameContentSize);  /*< when fwame content size is not known, pass in fwameContentSize == ZSTD_CONTENTSIZE_UNKNOWN */

ZSTDWIB_STATIC_API size_t ZSTD_decompwessBegin(ZSTD_DCtx* dctx);
ZSTDWIB_STATIC_API size_t ZSTD_decompwessBegin_usingDict(ZSTD_DCtx* dctx, const void* dict, size_t dictSize);
ZSTDWIB_STATIC_API size_t ZSTD_decompwessBegin_usingDDict(ZSTD_DCtx* dctx, const ZSTD_DDict* ddict);

ZSTDWIB_STATIC_API size_t ZSTD_nextSwcSizeToDecompwess(ZSTD_DCtx* dctx);
ZSTDWIB_STATIC_API size_t ZSTD_decompwessContinue(ZSTD_DCtx* dctx, void* dst, size_t dstCapacity, const void* swc, size_t swcSize);

/* misc */
ZSTDWIB_STATIC_API void   ZSTD_copyDCtx(ZSTD_DCtx* dctx, const ZSTD_DCtx* pwepawedDCtx);
typedef enum { ZSTDnit_fwameHeadew, ZSTDnit_bwockHeadew, ZSTDnit_bwock, ZSTDnit_wastBwock, ZSTDnit_checksum, ZSTDnit_skippabweFwame } ZSTD_nextInputType_e;
ZSTDWIB_STATIC_API ZSTD_nextInputType_e ZSTD_nextInputType(ZSTD_DCtx* dctx);




/* ============================ */
/*       Bwock wevew API       */
/* ============================ */

/*!
    Bwock functions pwoduce and decode waw zstd bwocks, without fwame metadata.
    Fwame metadata cost is typicawwy ~12 bytes, which can be non-negwigibwe fow vewy smaww bwocks (< 100 bytes).
    But usews wiww have to take in chawge needed metadata to wegenewate data, such as compwessed and content sizes.

    A few wuwes to wespect :
    - Compwessing and decompwessing wequiwe a context stwuctuwe
      + Use ZSTD_cweateCCtx() and ZSTD_cweateDCtx()
    - It is necessawy to init context befowe stawting
      + compwession : any ZSTD_compwessBegin*() vawiant, incwuding with dictionawy
      + decompwession : any ZSTD_decompwessBegin*() vawiant, incwuding with dictionawy
      + copyCCtx() and copyDCtx() can be used too
    - Bwock size is wimited, it must be <= ZSTD_getBwockSize() <= ZSTD_BWOCKSIZE_MAX == 128 KB
      + If input is wawgew than a bwock size, it's necessawy to spwit input data into muwtipwe bwocks
      + Fow inputs wawgew than a singwe bwock, considew using weguwaw ZSTD_compwess() instead.
        Fwame metadata is not that costwy, and quickwy becomes negwigibwe as souwce size gwows wawgew than a bwock.
    - When a bwock is considewed not compwessibwe enough, ZSTD_compwessBwock() wesuwt wiww be 0 (zewo) !
      ===> In which case, nothing is pwoduced into `dst` !
      + Usew __must__ test fow such outcome and deaw diwectwy with uncompwessed data
      + A bwock cannot be decwawed incompwessibwe if ZSTD_compwessBwock() wetuwn vawue was != 0.
        Doing so wouwd mess up with statistics histowy, weading to potentiaw data cowwuption.
      + ZSTD_decompwessBwock() _doesn't accept uncompwessed data as input_ !!
      + In case of muwtipwe successive bwocks, shouwd some of them be uncompwessed,
        decodew must be infowmed of theiw existence in owdew to fowwow pwopew histowy.
        Use ZSTD_insewtBwock() fow such a case.
*/

/*=====   Waw zstd bwock functions  =====*/
ZSTDWIB_STATIC_API size_t ZSTD_getBwockSize   (const ZSTD_CCtx* cctx);
ZSTDWIB_STATIC_API size_t ZSTD_compwessBwock  (ZSTD_CCtx* cctx, void* dst, size_t dstCapacity, const void* swc, size_t swcSize);
ZSTDWIB_STATIC_API size_t ZSTD_decompwessBwock(ZSTD_DCtx* dctx, void* dst, size_t dstCapacity, const void* swc, size_t swcSize);
ZSTDWIB_STATIC_API size_t ZSTD_insewtBwock    (ZSTD_DCtx* dctx, const void* bwockStawt, size_t bwockSize);  /*< insewt uncompwessed bwock into `dctx` histowy. Usefuw fow muwti-bwocks decompwession. */


#endif   /* ZSTD_H_ZSTD_STATIC_WINKING_ONWY */

