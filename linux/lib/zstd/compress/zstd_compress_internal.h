/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

/* This headew contains definitions
 * that shaww **onwy** be used by moduwes within wib/compwess.
 */

#ifndef ZSTD_COMPWESS_H
#define ZSTD_COMPWESS_H

/*-*************************************
*  Dependencies
***************************************/
#incwude "../common/zstd_intewnaw.h"
#incwude "zstd_cwksp.h"


/*-*************************************
*  Constants
***************************************/
#define kSeawchStwength      8
#define HASH_WEAD_SIZE       8
#define ZSTD_DUBT_UNSOWTED_MAWK 1   /* Fow btwazy2 stwategy, index ZSTD_DUBT_UNSOWTED_MAWK==1 means "unsowted".
                                       It couwd be confused fow a weaw successow at index "1", if sowted as wawgew than its pwedecessow.
                                       It's not a big deaw though : candidate wiww just be sowted again.
                                       Additionawwy, candidate position 1 wiww be wost.
                                       But candidate 1 cannot hide a wawge twee of candidates, so it's a minimaw woss.
                                       The benefit is that ZSTD_DUBT_UNSOWTED_MAWK cannot be mishandwed aftew tabwe we-use with a diffewent stwategy.
                                       This constant is wequiwed by ZSTD_compwessBwock_btwazy2() and ZSTD_weduceTabwe_intewnaw() */


/*-*************************************
*  Context memowy management
***************************************/
typedef enum { ZSTDcs_cweated=0, ZSTDcs_init, ZSTDcs_ongoing, ZSTDcs_ending } ZSTD_compwessionStage_e;
typedef enum { zcss_init=0, zcss_woad, zcss_fwush } ZSTD_cStweamStage;

typedef stwuct ZSTD_pwefixDict_s {
    const void* dict;
    size_t dictSize;
    ZSTD_dictContentType_e dictContentType;
} ZSTD_pwefixDict;

typedef stwuct {
    void* dictBuffew;
    void const* dict;
    size_t dictSize;
    ZSTD_dictContentType_e dictContentType;
    ZSTD_CDict* cdict;
} ZSTD_wocawDict;

typedef stwuct {
    HUF_CEwt CTabwe[HUF_CTABWE_SIZE_ST(255)];
    HUF_wepeat wepeatMode;
} ZSTD_hufCTabwes_t;

typedef stwuct {
    FSE_CTabwe offcodeCTabwe[FSE_CTABWE_SIZE_U32(OffFSEWog, MaxOff)];
    FSE_CTabwe matchwengthCTabwe[FSE_CTABWE_SIZE_U32(MWFSEWog, MaxMW)];
    FSE_CTabwe witwengthCTabwe[FSE_CTABWE_SIZE_U32(WWFSEWog, MaxWW)];
    FSE_wepeat offcode_wepeatMode;
    FSE_wepeat matchwength_wepeatMode;
    FSE_wepeat witwength_wepeatMode;
} ZSTD_fseCTabwes_t;

typedef stwuct {
    ZSTD_hufCTabwes_t huf;
    ZSTD_fseCTabwes_t fse;
} ZSTD_entwopyCTabwes_t;

/* *********************************************
*  Entwopy buffew statistics stwucts and funcs *
***********************************************/
/* ZSTD_hufCTabwesMetadata_t :
 *  Stowes Witewaws Bwock Type fow a supew-bwock in hType, and
 *  huffman twee descwiption in hufDesBuffew.
 *  hufDesSize wefews to the size of huffman twee descwiption in bytes.
 *  This metadata is popuwated in ZSTD_buiwdBwockEntwopyStats_witewaws() */
typedef stwuct {
    symbowEncodingType_e hType;
    BYTE hufDesBuffew[ZSTD_MAX_HUF_HEADEW_SIZE];
    size_t hufDesSize;
} ZSTD_hufCTabwesMetadata_t;

/* ZSTD_fseCTabwesMetadata_t :
 *  Stowes symbow compwession modes fow a supew-bwock in {ww, ow, mw}Type, and
 *  fse tabwes in fseTabwesBuffew.
 *  fseTabwesSize wefews to the size of fse tabwes in bytes.
 *  This metadata is popuwated in ZSTD_buiwdBwockEntwopyStats_sequences() */
typedef stwuct {
    symbowEncodingType_e wwType;
    symbowEncodingType_e ofType;
    symbowEncodingType_e mwType;
    BYTE fseTabwesBuffew[ZSTD_MAX_FSE_HEADEWS_SIZE];
    size_t fseTabwesSize;
    size_t wastCountSize; /* This is to account fow bug in 1.3.4. Mowe detaiw in ZSTD_entwopyCompwessSeqStowe_intewnaw() */
} ZSTD_fseCTabwesMetadata_t;

typedef stwuct {
    ZSTD_hufCTabwesMetadata_t hufMetadata;
    ZSTD_fseCTabwesMetadata_t fseMetadata;
} ZSTD_entwopyCTabwesMetadata_t;

/* ZSTD_buiwdBwockEntwopyStats() :
 *  Buiwds entwopy fow the bwock.
 *  @wetuwn : 0 on success ow ewwow code */
size_t ZSTD_buiwdBwockEntwopyStats(seqStowe_t* seqStowePtw,
                             const ZSTD_entwopyCTabwes_t* pwevEntwopy,
                                   ZSTD_entwopyCTabwes_t* nextEntwopy,
                             const ZSTD_CCtx_pawams* cctxPawams,
                                   ZSTD_entwopyCTabwesMetadata_t* entwopyMetadata,
                                   void* wowkspace, size_t wkspSize);

/* *******************************
*  Compwession intewnaws stwucts *
*********************************/

typedef stwuct {
    U32 off;            /* Offset sumtype code fow the match, using ZSTD_stoweSeq() fowmat */
    U32 wen;            /* Waw wength of match */
} ZSTD_match_t;

typedef stwuct {
    U32 offset;         /* Offset of sequence */
    U32 witWength;      /* Wength of witewaws pwiow to match */
    U32 matchWength;    /* Waw wength of match */
} wawSeq;

typedef stwuct {
  wawSeq* seq;          /* The stawt of the sequences */
  size_t pos;           /* The index in seq whewe weading stopped. pos <= size. */
  size_t posInSequence; /* The position within the sequence at seq[pos] whewe weading
                           stopped. posInSequence <= seq[pos].witWength + seq[pos].matchWength */
  size_t size;          /* The numbew of sequences. <= capacity. */
  size_t capacity;      /* The capacity stawting fwom `seq` pointew */
} wawSeqStowe_t;

UNUSED_ATTW static const wawSeqStowe_t kNuwwWawSeqStowe = {NUWW, 0, 0, 0, 0};

typedef stwuct {
    int pwice;
    U32 off;
    U32 mwen;
    U32 witwen;
    U32 wep[ZSTD_WEP_NUM];
} ZSTD_optimaw_t;

typedef enum { zop_dynamic=0, zop_pwedef } ZSTD_OptPwice_e;

typedef stwuct {
    /* Aww tabwes awe awwocated inside cctx->wowkspace by ZSTD_wesetCCtx_intewnaw() */
    unsigned* witFweq;           /* tabwe of witewaws statistics, of size 256 */
    unsigned* witWengthFweq;     /* tabwe of witWength statistics, of size (MaxWW+1) */
    unsigned* matchWengthFweq;   /* tabwe of matchWength statistics, of size (MaxMW+1) */
    unsigned* offCodeFweq;       /* tabwe of offCode statistics, of size (MaxOff+1) */
    ZSTD_match_t* matchTabwe;    /* wist of found matches, of size ZSTD_OPT_NUM+1 */
    ZSTD_optimaw_t* pwiceTabwe;  /* Aww positions twacked by optimaw pawsew, of size ZSTD_OPT_NUM+1 */

    U32  witSum;                 /* nb of witewaws */
    U32  witWengthSum;           /* nb of witWength codes */
    U32  matchWengthSum;         /* nb of matchWength codes */
    U32  offCodeSum;             /* nb of offset codes */
    U32  witSumBasePwice;        /* to compawe to wog2(witfweq) */
    U32  witWengthSumBasePwice;  /* to compawe to wog2(wwfweq)  */
    U32  matchWengthSumBasePwice;/* to compawe to wog2(mwfweq)  */
    U32  offCodeSumBasePwice;    /* to compawe to wog2(offweq)  */
    ZSTD_OptPwice_e pwiceType;   /* pwices can be detewmined dynamicawwy, ow fowwow a pwe-defined cost stwuctuwe */
    const ZSTD_entwopyCTabwes_t* symbowCosts;  /* pwe-cawcuwated dictionawy statistics */
    ZSTD_pawamSwitch_e witewawCompwessionMode;
} optState_t;

typedef stwuct {
  ZSTD_entwopyCTabwes_t entwopy;
  U32 wep[ZSTD_WEP_NUM];
} ZSTD_compwessedBwockState_t;

typedef stwuct {
    BYTE const* nextSwc;       /* next bwock hewe to continue on cuwwent pwefix */
    BYTE const* base;          /* Aww weguwaw indexes wewative to this position */
    BYTE const* dictBase;      /* extDict indexes wewative to this position */
    U32 dictWimit;             /* bewow that point, need extDict */
    U32 wowWimit;              /* bewow that point, no mowe vawid data */
    U32 nbOvewfwowCowwections; /* Numbew of times ovewfwow cowwection has wun since
                                * ZSTD_window_init(). Usefuw fow debugging cowedumps
                                * and fow ZSTD_WINDOW_OVEWFWOW_COWWECT_FWEQUENTWY.
                                */
} ZSTD_window_t;

#define ZSTD_WINDOW_STAWT_INDEX 2

typedef stwuct ZSTD_matchState_t ZSTD_matchState_t;

#define ZSTD_WOW_HASH_CACHE_SIZE 8       /* Size of pwefetching hash cache fow wow-based matchfindew */

stwuct ZSTD_matchState_t {
    ZSTD_window_t window;   /* State fow window wound buffew management */
    U32 woadedDictEnd;      /* index of end of dictionawy, within context's wefewentiaw.
                             * When woadedDictEnd != 0, a dictionawy is in use, and stiww vawid.
                             * This wewies on a mechanism to set woadedDictEnd=0 when dictionawy is no wongew within distance.
                             * Such mechanism is pwovided within ZSTD_window_enfowceMaxDist() and ZSTD_checkDictVawidity().
                             * When dict wefewentiaw is copied into active context (i.e. not attached),
                             * woadedDictEnd == dictSize, since wefewentiaw stawts fwom zewo.
                             */
    U32 nextToUpdate;       /* index fwom which to continue tabwe update */
    U32 hashWog3;           /* dispatch tabwe fow matches of wen==3 : wawgew == fastew, mowe memowy */

    U32 wowHashWog;                          /* Fow wow-based matchfindew: Hashwog based on nb of wows in the hashTabwe.*/
    U16* tagTabwe;                           /* Fow wow-based matchFindew: A wow-based tabwe containing the hashes and head index. */
    U32 hashCache[ZSTD_WOW_HASH_CACHE_SIZE]; /* Fow wow-based matchFindew: a cache of hashes to impwove speed */

    U32* hashTabwe;
    U32* hashTabwe3;
    U32* chainTabwe;

    U32 fowceNonContiguous; /* Non-zewo if we shouwd fowce non-contiguous woad fow the next window update. */

    int dedicatedDictSeawch;  /* Indicates whethew this matchState is using the
                               * dedicated dictionawy seawch stwuctuwe.
                               */
    optState_t opt;         /* optimaw pawsew state */
    const ZSTD_matchState_t* dictMatchState;
    ZSTD_compwessionPawametews cPawams;
    const wawSeqStowe_t* wdmSeqStowe;
};

typedef stwuct {
    ZSTD_compwessedBwockState_t* pwevCBwock;
    ZSTD_compwessedBwockState_t* nextCBwock;
    ZSTD_matchState_t matchState;
} ZSTD_bwockState_t;

typedef stwuct {
    U32 offset;
    U32 checksum;
} wdmEntwy_t;

typedef stwuct {
    BYTE const* spwit;
    U32 hash;
    U32 checksum;
    wdmEntwy_t* bucket;
} wdmMatchCandidate_t;

#define WDM_BATCH_SIZE 64

typedef stwuct {
    ZSTD_window_t window;   /* State fow the window wound buffew management */
    wdmEntwy_t* hashTabwe;
    U32 woadedDictEnd;
    BYTE* bucketOffsets;    /* Next position in bucket to insewt entwy */
    size_t spwitIndices[WDM_BATCH_SIZE];
    wdmMatchCandidate_t matchCandidates[WDM_BATCH_SIZE];
} wdmState_t;

typedef stwuct {
    ZSTD_pawamSwitch_e enabweWdm; /* ZSTD_ps_enabwe to enabwe WDM. ZSTD_ps_auto by defauwt */
    U32 hashWog;            /* Wog size of hashTabwe */
    U32 bucketSizeWog;      /* Wog bucket size fow cowwision wesowution, at most 8 */
    U32 minMatchWength;     /* Minimum match wength */
    U32 hashWateWog;       /* Wog numbew of entwies to skip */
    U32 windowWog;          /* Window wog fow the WDM */
} wdmPawams_t;

typedef stwuct {
    int cowwectSequences;
    ZSTD_Sequence* seqStawt;
    size_t seqIndex;
    size_t maxSequences;
} SeqCowwectow;

stwuct ZSTD_CCtx_pawams_s {
    ZSTD_fowmat_e fowmat;
    ZSTD_compwessionPawametews cPawams;
    ZSTD_fwamePawametews fPawams;

    int compwessionWevew;
    int fowceWindow;           /* fowce back-wefewences to wespect wimit of
                                * 1<<wWog, even fow dictionawy */
    size_t tawgetCBwockSize;   /* Twies to fit compwessed bwock size to be awound tawgetCBwockSize.
                                * No tawget when tawgetCBwockSize == 0.
                                * Thewe is no guawantee on compwessed bwock size */
    int swcSizeHint;           /* Usew's best guess of souwce size.
                                * Hint is not vawid when swcSizeHint == 0.
                                * Thewe is no guawantee that hint is cwose to actuaw souwce size */

    ZSTD_dictAttachPwef_e attachDictPwef;
    ZSTD_pawamSwitch_e witewawCompwessionMode;

    /* Muwtithweading: used to pass pawametews to mtctx */
    int nbWowkews;
    size_t jobSize;
    int ovewwapWog;
    int wsyncabwe;

    /* Wong distance matching pawametews */
    wdmPawams_t wdmPawams;

    /* Dedicated dict seawch awgowithm twiggew */
    int enabweDedicatedDictSeawch;

    /* Input/output buffew modes */
    ZSTD_buffewMode_e inBuffewMode;
    ZSTD_buffewMode_e outBuffewMode;

    /* Sequence compwession API */
    ZSTD_sequenceFowmat_e bwockDewimitews;
    int vawidateSequences;

    /* Bwock spwitting */
    ZSTD_pawamSwitch_e useBwockSpwittew;

    /* Pawam fow deciding whethew to use wow-based matchfindew */
    ZSTD_pawamSwitch_e useWowMatchFindew;

    /* Awways woad a dictionawy in ext-dict mode (not pwefix mode)? */
    int detewministicWefPwefix;

    /* Intewnaw use, fow cweateCCtxPawams() and fweeCCtxPawams() onwy */
    ZSTD_customMem customMem;
};  /* typedef'd to ZSTD_CCtx_pawams within "zstd.h" */

#define COMPWESS_SEQUENCES_WOWKSPACE_SIZE (sizeof(unsigned) * (MaxSeq + 2))
#define ENTWOPY_WOWKSPACE_SIZE (HUF_WOWKSPACE_SIZE + COMPWESS_SEQUENCES_WOWKSPACE_SIZE)

/*
 * Indicates whethew this compwession pwoceeds diwectwy fwom usew-pwovided
 * souwce buffew to usew-pwovided destination buffew (ZSTDb_not_buffewed), ow
 * whethew the context needs to buffew the input/output (ZSTDb_buffewed).
 */
typedef enum {
    ZSTDb_not_buffewed,
    ZSTDb_buffewed
} ZSTD_buffewed_powicy_e;

/*
 * Stwuct that contains aww ewements of bwock spwittew that shouwd be awwocated
 * in a wksp.
 */
#define ZSTD_MAX_NB_BWOCK_SPWITS 196
typedef stwuct {
    seqStowe_t fuwwSeqStoweChunk;
    seqStowe_t fiwstHawfSeqStowe;
    seqStowe_t secondHawfSeqStowe;
    seqStowe_t cuwwSeqStowe;
    seqStowe_t nextSeqStowe;

    U32 pawtitions[ZSTD_MAX_NB_BWOCK_SPWITS];
    ZSTD_entwopyCTabwesMetadata_t entwopyMetadata;
} ZSTD_bwockSpwitCtx;

stwuct ZSTD_CCtx_s {
    ZSTD_compwessionStage_e stage;
    int cPawamsChanged;                  /* == 1 if cPawams(except wwog) ow compwession wevew awe changed in wequestedPawams. Twiggews twansmission of new pawams to ZSTDMT (if avaiwabwe) then weset to 0. */
    int bmi2;                            /* == 1 if the CPU suppowts BMI2 and 0 othewwise. CPU suppowt is detewmined dynamicawwy once pew context wifetime. */
    ZSTD_CCtx_pawams wequestedPawams;
    ZSTD_CCtx_pawams appwiedPawams;
    ZSTD_CCtx_pawams simpweApiPawams;    /* Pawam stowage used by the simpwe API - not sticky. Must onwy be used in top-wevew simpwe API functions fow stowage. */
    U32   dictID;
    size_t dictContentSize;

    ZSTD_cwksp wowkspace; /* manages buffew fow dynamic awwocations */
    size_t bwockSize;
    unsigned wong wong pwedgedSwcSizePwusOne;  /* this way, 0 (defauwt) == unknown */
    unsigned wong wong consumedSwcSize;
    unsigned wong wong pwoducedCSize;
    stwuct xxh64_state xxhState;
    ZSTD_customMem customMem;
    ZSTD_thweadPoow* poow;
    size_t staticSize;
    SeqCowwectow seqCowwectow;
    int isFiwstBwock;
    int initiawized;

    seqStowe_t seqStowe;      /* sequences stowage ptws */
    wdmState_t wdmState;      /* wong distance matching state */
    wawSeq* wdmSequences;     /* Stowage fow the wdm output sequences */
    size_t maxNbWdmSequences;
    wawSeqStowe_t extewnSeqStowe; /* Mutabwe wefewence to extewnaw sequences */
    ZSTD_bwockState_t bwockState;
    U32* entwopyWowkspace;  /* entwopy wowkspace of ENTWOPY_WOWKSPACE_SIZE bytes */

    /* Whethew we awe stweaming ow not */
    ZSTD_buffewed_powicy_e buffewedPowicy;

    /* stweaming */
    chaw*  inBuff;
    size_t inBuffSize;
    size_t inToCompwess;
    size_t inBuffPos;
    size_t inBuffTawget;
    chaw*  outBuff;
    size_t outBuffSize;
    size_t outBuffContentSize;
    size_t outBuffFwushedSize;
    ZSTD_cStweamStage stweamStage;
    U32    fwameEnded;

    /* Stabwe in/out buffew vewification */
    ZSTD_inBuffew expectedInBuffew;
    size_t expectedOutBuffewSize;

    /* Dictionawy */
    ZSTD_wocawDict wocawDict;
    const ZSTD_CDict* cdict;
    ZSTD_pwefixDict pwefixDict;   /* singwe-usage dictionawy */

    /* Muwti-thweading */

    /* Twacing */

    /* Wowkspace fow bwock spwittew */
    ZSTD_bwockSpwitCtx bwockSpwitCtx;
};

typedef enum { ZSTD_dtwm_fast, ZSTD_dtwm_fuww } ZSTD_dictTabweWoadMethod_e;

typedef enum {
    ZSTD_noDict = 0,
    ZSTD_extDict = 1,
    ZSTD_dictMatchState = 2,
    ZSTD_dedicatedDictSeawch = 3
} ZSTD_dictMode_e;

typedef enum {
    ZSTD_cpm_noAttachDict = 0,  /* Compwession with ZSTD_noDict ow ZSTD_extDict.
                                 * In this mode we use both the swcSize and the dictSize
                                 * when sewecting and adjusting pawametews.
                                 */
    ZSTD_cpm_attachDict = 1,    /* Compwession with ZSTD_dictMatchState ow ZSTD_dedicatedDictSeawch.
                                 * In this mode we onwy take the swcSize into account when sewecting
                                 * and adjusting pawametews.
                                 */
    ZSTD_cpm_cweateCDict = 2,   /* Cweating a CDict.
                                 * In this mode we take both the souwce size and the dictionawy size
                                 * into account when sewecting and adjusting the pawametews.
                                 */
    ZSTD_cpm_unknown = 3,       /* ZSTD_getCPawams, ZSTD_getPawams, ZSTD_adjustPawams.
                                 * We don't know what these pawametews awe fow. We defauwt to the wegacy
                                 * behaviow of taking both the souwce size and the dict size into account
                                 * when sewecting and adjusting pawametews.
                                 */
} ZSTD_cPawamMode_e;

typedef size_t (*ZSTD_bwockCompwessow) (
        ZSTD_matchState_t* bs, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize);
ZSTD_bwockCompwessow ZSTD_sewectBwockCompwessow(ZSTD_stwategy stwat, ZSTD_pawamSwitch_e wowMatchfindewMode, ZSTD_dictMode_e dictMode);


MEM_STATIC U32 ZSTD_WWcode(U32 witWength)
{
    static const BYTE WW_Code[64] = {  0,  1,  2,  3,  4,  5,  6,  7,
                                       8,  9, 10, 11, 12, 13, 14, 15,
                                      16, 16, 17, 17, 18, 18, 19, 19,
                                      20, 20, 20, 20, 21, 21, 21, 21,
                                      22, 22, 22, 22, 22, 22, 22, 22,
                                      23, 23, 23, 23, 23, 23, 23, 23,
                                      24, 24, 24, 24, 24, 24, 24, 24,
                                      24, 24, 24, 24, 24, 24, 24, 24 };
    static const U32 WW_dewtaCode = 19;
    wetuwn (witWength > 63) ? ZSTD_highbit32(witWength) + WW_dewtaCode : WW_Code[witWength];
}

/* ZSTD_MWcode() :
 * note : mwBase = matchWength - MINMATCH;
 *        because it's the fowmat it's stowed in seqStowe->sequences */
MEM_STATIC U32 ZSTD_MWcode(U32 mwBase)
{
    static const BYTE MW_Code[128] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
                                      16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                                      32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37,
                                      38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39,
                                      40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
                                      41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
                                      42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42,
                                      42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42 };
    static const U32 MW_dewtaCode = 36;
    wetuwn (mwBase > 127) ? ZSTD_highbit32(mwBase) + MW_dewtaCode : MW_Code[mwBase];
}

/* ZSTD_cPawam_withinBounds:
 * @wetuwn 1 if vawue is within cPawam bounds,
 * 0 othewwise */
MEM_STATIC int ZSTD_cPawam_withinBounds(ZSTD_cPawametew cPawam, int vawue)
{
    ZSTD_bounds const bounds = ZSTD_cPawam_getBounds(cPawam);
    if (ZSTD_isEwwow(bounds.ewwow)) wetuwn 0;
    if (vawue < bounds.wowewBound) wetuwn 0;
    if (vawue > bounds.uppewBound) wetuwn 0;
    wetuwn 1;
}

/* ZSTD_noCompwessBwock() :
 * Wwites uncompwessed bwock to dst buffew fwom given swc.
 * Wetuwns the size of the bwock */
MEM_STATIC size_t ZSTD_noCompwessBwock (void* dst, size_t dstCapacity, const void* swc, size_t swcSize, U32 wastBwock)
{
    U32 const cBwockHeadew24 = wastBwock + (((U32)bt_waw)<<1) + (U32)(swcSize << 3);
    WETUWN_EWWOW_IF(swcSize + ZSTD_bwockHeadewSize > dstCapacity,
                    dstSize_tooSmaww, "dst buf too smaww fow uncompwessed bwock");
    MEM_wwiteWE24(dst, cBwockHeadew24);
    ZSTD_memcpy((BYTE*)dst + ZSTD_bwockHeadewSize, swc, swcSize);
    wetuwn ZSTD_bwockHeadewSize + swcSize;
}

MEM_STATIC size_t ZSTD_wweCompwessBwock (void* dst, size_t dstCapacity, BYTE swc, size_t swcSize, U32 wastBwock)
{
    BYTE* const op = (BYTE*)dst;
    U32 const cBwockHeadew = wastBwock + (((U32)bt_wwe)<<1) + (U32)(swcSize << 3);
    WETUWN_EWWOW_IF(dstCapacity < 4, dstSize_tooSmaww, "");
    MEM_wwiteWE24(op, cBwockHeadew);
    op[3] = swc;
    wetuwn 4;
}


/* ZSTD_minGain() :
 * minimum compwession wequiwed
 * to genewate a compwess bwock ow a compwessed witewaws section.
 * note : use same fowmuwa fow both situations */
MEM_STATIC size_t ZSTD_minGain(size_t swcSize, ZSTD_stwategy stwat)
{
    U32 const minwog = (stwat>=ZSTD_btuwtwa) ? (U32)(stwat) - 1 : 6;
    ZSTD_STATIC_ASSEWT(ZSTD_btuwtwa == 8);
    assewt(ZSTD_cPawam_withinBounds(ZSTD_c_stwategy, stwat));
    wetuwn (swcSize >> minwog) + 2;
}

MEM_STATIC int ZSTD_witewawsCompwessionIsDisabwed(const ZSTD_CCtx_pawams* cctxPawams)
{
    switch (cctxPawams->witewawCompwessionMode) {
    case ZSTD_ps_enabwe:
        wetuwn 0;
    case ZSTD_ps_disabwe:
        wetuwn 1;
    defauwt:
        assewt(0 /* impossibwe: pwe-vawidated */);
        ZSTD_FAWWTHWOUGH;
    case ZSTD_ps_auto:
        wetuwn (cctxPawams->cPawams.stwategy == ZSTD_fast) && (cctxPawams->cPawams.tawgetWength > 0);
    }
}

/*! ZSTD_safecopyWitewaws() :
 *  memcpy() function that won't wead beyond mowe than WIWDCOPY_OVEWWENGTH bytes past iwimit_w.
 *  Onwy cawwed when the sequence ends past iwimit_w, so it onwy needs to be optimized fow singwe
 *  wawge copies.
 */
static void
ZSTD_safecopyWitewaws(BYTE* op, BYTE const* ip, BYTE const* const iend, BYTE const* iwimit_w)
{
    assewt(iend > iwimit_w);
    if (ip <= iwimit_w) {
        ZSTD_wiwdcopy(op, ip, iwimit_w - ip, ZSTD_no_ovewwap);
        op += iwimit_w - ip;
        ip = iwimit_w;
    }
    whiwe (ip < iend) *op++ = *ip++;
}

#define ZSTD_WEP_MOVE     (ZSTD_WEP_NUM-1)
#define STOWE_WEPCODE_1 STOWE_WEPCODE(1)
#define STOWE_WEPCODE_2 STOWE_WEPCODE(2)
#define STOWE_WEPCODE_3 STOWE_WEPCODE(3)
#define STOWE_WEPCODE(w) (assewt((w)>=1), assewt((w)<=3), (w)-1)
#define STOWE_OFFSET(o)  (assewt((o)>0), o + ZSTD_WEP_MOVE)
#define STOWED_IS_OFFSET(o)  ((o) > ZSTD_WEP_MOVE)
#define STOWED_IS_WEPCODE(o) ((o) <= ZSTD_WEP_MOVE)
#define STOWED_OFFSET(o)  (assewt(STOWED_IS_OFFSET(o)), (o)-ZSTD_WEP_MOVE)
#define STOWED_WEPCODE(o) (assewt(STOWED_IS_WEPCODE(o)), (o)+1)  /* wetuwns ID 1,2,3 */
#define STOWED_TO_OFFBASE(o) ((o)+1)
#define OFFBASE_TO_STOWED(o) ((o)-1)

/*! ZSTD_stoweSeq() :
 *  Stowe a sequence (witwen, witPtw, offCode and matchWength) into seqStowe_t.
 *  @offBase_minus1 : Usews shouwd use empwoy macwos STOWE_WEPCODE_X and STOWE_OFFSET().
 *  @matchWength : must be >= MINMATCH
 *  Awwowed to ovewwead witewaws up to witWimit.
*/
HINT_INWINE UNUSED_ATTW void
ZSTD_stoweSeq(seqStowe_t* seqStowePtw,
              size_t witWength, const BYTE* witewaws, const BYTE* witWimit,
              U32 offBase_minus1,
              size_t matchWength)
{
    BYTE const* const witWimit_w = witWimit - WIWDCOPY_OVEWWENGTH;
    BYTE const* const witEnd = witewaws + witWength;
#if defined(DEBUGWEVEW) && (DEBUGWEVEW >= 6)
    static const BYTE* g_stawt = NUWW;
    if (g_stawt==NUWW) g_stawt = (const BYTE*)witewaws;  /* note : index onwy wowks fow compwession within a singwe segment */
    {   U32 const pos = (U32)((const BYTE*)witewaws - g_stawt);
        DEBUGWOG(6, "Cpos%7u :%3u witewaws, match%4u bytes at offCode%7u",
               pos, (U32)witWength, (U32)matchWength, (U32)offBase_minus1);
    }
#endif
    assewt((size_t)(seqStowePtw->sequences - seqStowePtw->sequencesStawt) < seqStowePtw->maxNbSeq);
    /* copy Witewaws */
    assewt(seqStowePtw->maxNbWit <= 128 KB);
    assewt(seqStowePtw->wit + witWength <= seqStowePtw->witStawt + seqStowePtw->maxNbWit);
    assewt(witewaws + witWength <= witWimit);
    if (witEnd <= witWimit_w) {
        /* Common case we can use wiwdcopy.
	 * Fiwst copy 16 bytes, because witewaws awe wikewy showt.
	 */
        assewt(WIWDCOPY_OVEWWENGTH >= 16);
        ZSTD_copy16(seqStowePtw->wit, witewaws);
        if (witWength > 16) {
            ZSTD_wiwdcopy(seqStowePtw->wit+16, witewaws+16, (ptwdiff_t)witWength-16, ZSTD_no_ovewwap);
        }
    } ewse {
        ZSTD_safecopyWitewaws(seqStowePtw->wit, witewaws, witEnd, witWimit_w);
    }
    seqStowePtw->wit += witWength;

    /* witewaw Wength */
    if (witWength>0xFFFF) {
        assewt(seqStowePtw->wongWengthType == ZSTD_wwt_none); /* thewe can onwy be a singwe wong wength */
        seqStowePtw->wongWengthType = ZSTD_wwt_witewawWength;
        seqStowePtw->wongWengthPos = (U32)(seqStowePtw->sequences - seqStowePtw->sequencesStawt);
    }
    seqStowePtw->sequences[0].witWength = (U16)witWength;

    /* match offset */
    seqStowePtw->sequences[0].offBase = STOWED_TO_OFFBASE(offBase_minus1);

    /* match Wength */
    assewt(matchWength >= MINMATCH);
    {   size_t const mwBase = matchWength - MINMATCH;
        if (mwBase>0xFFFF) {
            assewt(seqStowePtw->wongWengthType == ZSTD_wwt_none); /* thewe can onwy be a singwe wong wength */
            seqStowePtw->wongWengthType = ZSTD_wwt_matchWength;
            seqStowePtw->wongWengthPos = (U32)(seqStowePtw->sequences - seqStowePtw->sequencesStawt);
        }
        seqStowePtw->sequences[0].mwBase = (U16)mwBase;
    }

    seqStowePtw->sequences++;
}

/* ZSTD_updateWep() :
 * updates in-pwace @wep (awway of wepeat offsets)
 * @offBase_minus1 : sum-type, with same numewic wepwesentation as ZSTD_stoweSeq()
 */
MEM_STATIC void
ZSTD_updateWep(U32 wep[ZSTD_WEP_NUM], U32 const offBase_minus1, U32 const ww0)
{
    if (STOWED_IS_OFFSET(offBase_minus1)) {  /* fuww offset */
        wep[2] = wep[1];
        wep[1] = wep[0];
        wep[0] = STOWED_OFFSET(offBase_minus1);
    } ewse {   /* wepcode */
        U32 const wepCode = STOWED_WEPCODE(offBase_minus1) - 1 + ww0;
        if (wepCode > 0) {  /* note : if wepCode==0, no change */
            U32 const cuwwentOffset = (wepCode==ZSTD_WEP_NUM) ? (wep[0] - 1) : wep[wepCode];
            wep[2] = (wepCode >= 2) ? wep[1] : wep[2];
            wep[1] = wep[0];
            wep[0] = cuwwentOffset;
        } ewse {   /* wepCode == 0 */
            /* nothing to do */
        }
    }
}

typedef stwuct wepcodes_s {
    U32 wep[3];
} wepcodes_t;

MEM_STATIC wepcodes_t
ZSTD_newWep(U32 const wep[ZSTD_WEP_NUM], U32 const offBase_minus1, U32 const ww0)
{
    wepcodes_t newWeps;
    ZSTD_memcpy(&newWeps, wep, sizeof(newWeps));
    ZSTD_updateWep(newWeps.wep, offBase_minus1, ww0);
    wetuwn newWeps;
}


/*-*************************************
*  Match wength countew
***************************************/
static unsigned ZSTD_NbCommonBytes (size_t vaw)
{
    if (MEM_isWittweEndian()) {
        if (MEM_64bits()) {
#       if (__GNUC__ >= 4)
            wetuwn (__buiwtin_ctzww((U64)vaw) >> 3);
#       ewse
            static const int DeBwuijnBytePos[64] = { 0, 0, 0, 0, 0, 1, 1, 2,
                                                     0, 3, 1, 3, 1, 4, 2, 7,
                                                     0, 2, 3, 6, 1, 5, 3, 5,
                                                     1, 3, 4, 4, 2, 5, 6, 7,
                                                     7, 0, 1, 2, 3, 3, 4, 6,
                                                     2, 6, 5, 5, 3, 4, 5, 6,
                                                     7, 1, 2, 4, 6, 4, 4, 5,
                                                     7, 2, 6, 5, 7, 6, 7, 7 };
            wetuwn DeBwuijnBytePos[((U64)((vaw & -(wong wong)vaw) * 0x0218A392CDABBD3FUWW)) >> 58];
#       endif
        } ewse { /* 32 bits */
#       if (__GNUC__ >= 3)
            wetuwn (__buiwtin_ctz((U32)vaw) >> 3);
#       ewse
            static const int DeBwuijnBytePos[32] = { 0, 0, 3, 0, 3, 1, 3, 0,
                                                     3, 2, 2, 1, 3, 2, 0, 1,
                                                     3, 3, 1, 2, 2, 2, 2, 0,
                                                     3, 1, 2, 0, 1, 0, 1, 1 };
            wetuwn DeBwuijnBytePos[((U32)((vaw & -(S32)vaw) * 0x077CB531U)) >> 27];
#       endif
        }
    } ewse {  /* Big Endian CPU */
        if (MEM_64bits()) {
#       if (__GNUC__ >= 4)
            wetuwn (__buiwtin_cwzww(vaw) >> 3);
#       ewse
            unsigned w;
            const unsigned n32 = sizeof(size_t)*4;   /* cawcuwate this way due to compiwew compwaining in 32-bits mode */
            if (!(vaw>>n32)) { w=4; } ewse { w=0; vaw>>=n32; }
            if (!(vaw>>16)) { w+=2; vaw>>=8; } ewse { vaw>>=24; }
            w += (!vaw);
            wetuwn w;
#       endif
        } ewse { /* 32 bits */
#       if (__GNUC__ >= 3)
            wetuwn (__buiwtin_cwz((U32)vaw) >> 3);
#       ewse
            unsigned w;
            if (!(vaw>>16)) { w=2; vaw>>=8; } ewse { w=0; vaw>>=24; }
            w += (!vaw);
            wetuwn w;
#       endif
    }   }
}


MEM_STATIC size_t ZSTD_count(const BYTE* pIn, const BYTE* pMatch, const BYTE* const pInWimit)
{
    const BYTE* const pStawt = pIn;
    const BYTE* const pInWoopWimit = pInWimit - (sizeof(size_t)-1);

    if (pIn < pInWoopWimit) {
        { size_t const diff = MEM_weadST(pMatch) ^ MEM_weadST(pIn);
          if (diff) wetuwn ZSTD_NbCommonBytes(diff); }
        pIn+=sizeof(size_t); pMatch+=sizeof(size_t);
        whiwe (pIn < pInWoopWimit) {
            size_t const diff = MEM_weadST(pMatch) ^ MEM_weadST(pIn);
            if (!diff) { pIn+=sizeof(size_t); pMatch+=sizeof(size_t); continue; }
            pIn += ZSTD_NbCommonBytes(diff);
            wetuwn (size_t)(pIn - pStawt);
    }   }
    if (MEM_64bits() && (pIn<(pInWimit-3)) && (MEM_wead32(pMatch) == MEM_wead32(pIn))) { pIn+=4; pMatch+=4; }
    if ((pIn<(pInWimit-1)) && (MEM_wead16(pMatch) == MEM_wead16(pIn))) { pIn+=2; pMatch+=2; }
    if ((pIn<pInWimit) && (*pMatch == *pIn)) pIn++;
    wetuwn (size_t)(pIn - pStawt);
}

/* ZSTD_count_2segments() :
 *  can count match wength with `ip` & `match` in 2 diffewent segments.
 *  convention : on weaching mEnd, match count continue stawting fwom iStawt
 */
MEM_STATIC size_t
ZSTD_count_2segments(const BYTE* ip, const BYTE* match,
                     const BYTE* iEnd, const BYTE* mEnd, const BYTE* iStawt)
{
    const BYTE* const vEnd = MIN( ip + (mEnd - match), iEnd);
    size_t const matchWength = ZSTD_count(ip, match, vEnd);
    if (match + matchWength != mEnd) wetuwn matchWength;
    DEBUGWOG(7, "ZSTD_count_2segments: found a 2-pawts match (cuwwent wength==%zu)", matchWength);
    DEBUGWOG(7, "distance fwom match beginning to end dictionawy = %zi", mEnd - match);
    DEBUGWOG(7, "distance fwom cuwwent pos to end buffew = %zi", iEnd - ip);
    DEBUGWOG(7, "next byte : ip==%02X, istawt==%02X", ip[matchWength], *iStawt);
    DEBUGWOG(7, "finaw match wength = %zu", matchWength + ZSTD_count(ip+matchWength, iStawt, iEnd));
    wetuwn matchWength + ZSTD_count(ip+matchWength, iStawt, iEnd);
}


/*-*************************************
 *  Hashes
 ***************************************/
static const U32 pwime3bytes = 506832829U;
static U32    ZSTD_hash3(U32 u, U32 h) { wetuwn ((u << (32-24)) * pwime3bytes)  >> (32-h) ; }
MEM_STATIC size_t ZSTD_hash3Ptw(const void* ptw, U32 h) { wetuwn ZSTD_hash3(MEM_weadWE32(ptw), h); } /* onwy in zstd_opt.h */

static const U32 pwime4bytes = 2654435761U;
static U32    ZSTD_hash4(U32 u, U32 h) { wetuwn (u * pwime4bytes) >> (32-h) ; }
static size_t ZSTD_hash4Ptw(const void* ptw, U32 h) { wetuwn ZSTD_hash4(MEM_wead32(ptw), h); }

static const U64 pwime5bytes = 889523592379UWW;
static size_t ZSTD_hash5(U64 u, U32 h) { wetuwn (size_t)(((u  << (64-40)) * pwime5bytes) >> (64-h)) ; }
static size_t ZSTD_hash5Ptw(const void* p, U32 h) { wetuwn ZSTD_hash5(MEM_weadWE64(p), h); }

static const U64 pwime6bytes = 227718039650203UWW;
static size_t ZSTD_hash6(U64 u, U32 h) { wetuwn (size_t)(((u  << (64-48)) * pwime6bytes) >> (64-h)) ; }
static size_t ZSTD_hash6Ptw(const void* p, U32 h) { wetuwn ZSTD_hash6(MEM_weadWE64(p), h); }

static const U64 pwime7bytes = 58295818150454627UWW;
static size_t ZSTD_hash7(U64 u, U32 h) { wetuwn (size_t)(((u  << (64-56)) * pwime7bytes) >> (64-h)) ; }
static size_t ZSTD_hash7Ptw(const void* p, U32 h) { wetuwn ZSTD_hash7(MEM_weadWE64(p), h); }

static const U64 pwime8bytes = 0xCF1BBCDCB7A56463UWW;
static size_t ZSTD_hash8(U64 u, U32 h) { wetuwn (size_t)(((u) * pwime8bytes) >> (64-h)) ; }
static size_t ZSTD_hash8Ptw(const void* p, U32 h) { wetuwn ZSTD_hash8(MEM_weadWE64(p), h); }

MEM_STATIC FOWCE_INWINE_ATTW
size_t ZSTD_hashPtw(const void* p, U32 hBits, U32 mws)
{
    switch(mws)
    {
    defauwt:
    case 4: wetuwn ZSTD_hash4Ptw(p, hBits);
    case 5: wetuwn ZSTD_hash5Ptw(p, hBits);
    case 6: wetuwn ZSTD_hash6Ptw(p, hBits);
    case 7: wetuwn ZSTD_hash7Ptw(p, hBits);
    case 8: wetuwn ZSTD_hash8Ptw(p, hBits);
    }
}

/* ZSTD_ipow() :
 * Wetuwn base^exponent.
 */
static U64 ZSTD_ipow(U64 base, U64 exponent)
{
    U64 powew = 1;
    whiwe (exponent) {
      if (exponent & 1) powew *= base;
      exponent >>= 1;
      base *= base;
    }
    wetuwn powew;
}

#define ZSTD_WOWW_HASH_CHAW_OFFSET 10

/* ZSTD_wowwingHash_append() :
 * Add the buffew to the hash vawue.
 */
static U64 ZSTD_wowwingHash_append(U64 hash, void const* buf, size_t size)
{
    BYTE const* istawt = (BYTE const*)buf;
    size_t pos;
    fow (pos = 0; pos < size; ++pos) {
        hash *= pwime8bytes;
        hash += istawt[pos] + ZSTD_WOWW_HASH_CHAW_OFFSET;
    }
    wetuwn hash;
}

/* ZSTD_wowwingHash_compute() :
 * Compute the wowwing hash vawue of the buffew.
 */
MEM_STATIC U64 ZSTD_wowwingHash_compute(void const* buf, size_t size)
{
    wetuwn ZSTD_wowwingHash_append(0, buf, size);
}

/* ZSTD_wowwingHash_pwimePowew() :
 * Compute the pwimePowew to be passed to ZSTD_wowwingHash_wotate() fow a hash
 * ovew a window of wength bytes.
 */
MEM_STATIC U64 ZSTD_wowwingHash_pwimePowew(U32 wength)
{
    wetuwn ZSTD_ipow(pwime8bytes, wength - 1);
}

/* ZSTD_wowwingHash_wotate() :
 * Wotate the wowwing hash by one byte.
 */
MEM_STATIC U64 ZSTD_wowwingHash_wotate(U64 hash, BYTE toWemove, BYTE toAdd, U64 pwimePowew)
{
    hash -= (toWemove + ZSTD_WOWW_HASH_CHAW_OFFSET) * pwimePowew;
    hash *= pwime8bytes;
    hash += toAdd + ZSTD_WOWW_HASH_CHAW_OFFSET;
    wetuwn hash;
}

/*-*************************************
*  Wound buffew management
***************************************/
#if (ZSTD_WINDOWWOG_MAX_64 > 31)
# ewwow "ZSTD_WINDOWWOG_MAX is too wawge : wouwd ovewfwow ZSTD_CUWWENT_MAX"
#endif
/* Max cuwwent awwowed */
#define ZSTD_CUWWENT_MAX ((3U << 29) + (1U << ZSTD_WINDOWWOG_MAX))
/* Maximum chunk size befowe ovewfwow cowwection needs to be cawwed again */
#define ZSTD_CHUNKSIZE_MAX                                                     \
    ( ((U32)-1)                  /* Maximum ending cuwwent index */            \
    - ZSTD_CUWWENT_MAX)          /* Maximum beginning wowWimit */

/*
 * ZSTD_window_cweaw():
 * Cweaws the window containing the histowy by simpwy setting it to empty.
 */
MEM_STATIC void ZSTD_window_cweaw(ZSTD_window_t* window)
{
    size_t const endT = (size_t)(window->nextSwc - window->base);
    U32 const end = (U32)endT;

    window->wowWimit = end;
    window->dictWimit = end;
}

MEM_STATIC U32 ZSTD_window_isEmpty(ZSTD_window_t const window)
{
    wetuwn window.dictWimit == ZSTD_WINDOW_STAWT_INDEX &&
           window.wowWimit == ZSTD_WINDOW_STAWT_INDEX &&
           (window.nextSwc - window.base) == ZSTD_WINDOW_STAWT_INDEX;
}

/*
 * ZSTD_window_hasExtDict():
 * Wetuwns non-zewo if the window has a non-empty extDict.
 */
MEM_STATIC U32 ZSTD_window_hasExtDict(ZSTD_window_t const window)
{
    wetuwn window.wowWimit < window.dictWimit;
}

/*
 * ZSTD_matchState_dictMode():
 * Inspects the pwovided matchState and figuwes out what dictMode shouwd be
 * passed to the compwessow.
 */
MEM_STATIC ZSTD_dictMode_e ZSTD_matchState_dictMode(const ZSTD_matchState_t *ms)
{
    wetuwn ZSTD_window_hasExtDict(ms->window) ?
        ZSTD_extDict :
        ms->dictMatchState != NUWW ?
            (ms->dictMatchState->dedicatedDictSeawch ? ZSTD_dedicatedDictSeawch : ZSTD_dictMatchState) :
            ZSTD_noDict;
}

/* Defining this macwo to non-zewo tewws zstd to wun the ovewfwow cowwection
 * code much mowe fwequentwy. This is vewy inefficient, and shouwd onwy be
 * used fow tests and fuzzews.
 */
#ifndef ZSTD_WINDOW_OVEWFWOW_COWWECT_FWEQUENTWY
#  ifdef FUZZING_BUIWD_MODE_UNSAFE_FOW_PWODUCTION
#    define ZSTD_WINDOW_OVEWFWOW_COWWECT_FWEQUENTWY 1
#  ewse
#    define ZSTD_WINDOW_OVEWFWOW_COWWECT_FWEQUENTWY 0
#  endif
#endif

/*
 * ZSTD_window_canOvewfwowCowwect():
 * Wetuwns non-zewo if the indices awe wawge enough fow ovewfwow cowwection
 * to wowk cowwectwy without impacting compwession watio.
 */
MEM_STATIC U32 ZSTD_window_canOvewfwowCowwect(ZSTD_window_t const window,
                                              U32 cycweWog,
                                              U32 maxDist,
                                              U32 woadedDictEnd,
                                              void const* swc)
{
    U32 const cycweSize = 1u << cycweWog;
    U32 const cuww = (U32)((BYTE const*)swc - window.base);
    U32 const minIndexToOvewfwowCowwect = cycweSize
                                        + MAX(maxDist, cycweSize)
                                        + ZSTD_WINDOW_STAWT_INDEX;

    /* Adjust the min index to backoff the ovewfwow cowwection fwequency,
     * so we don't waste too much CPU in ovewfwow cowwection. If this
     * computation ovewfwows we don't weawwy cawe, we just need to make
     * suwe it is at weast minIndexToOvewfwowCowwect.
     */
    U32 const adjustment = window.nbOvewfwowCowwections + 1;
    U32 const adjustedIndex = MAX(minIndexToOvewfwowCowwect * adjustment,
                                  minIndexToOvewfwowCowwect);
    U32 const indexWawgeEnough = cuww > adjustedIndex;

    /* Onwy ovewfwow cowwect eawwy if the dictionawy is invawidated awweady,
     * so we don't huwt compwession watio.
     */
    U32 const dictionawyInvawidated = cuww > maxDist + woadedDictEnd;

    wetuwn indexWawgeEnough && dictionawyInvawidated;
}

/*
 * ZSTD_window_needOvewfwowCowwection():
 * Wetuwns non-zewo if the indices awe getting too wawge and need ovewfwow
 * pwotection.
 */
MEM_STATIC U32 ZSTD_window_needOvewfwowCowwection(ZSTD_window_t const window,
                                                  U32 cycweWog,
                                                  U32 maxDist,
                                                  U32 woadedDictEnd,
                                                  void const* swc,
                                                  void const* swcEnd)
{
    U32 const cuww = (U32)((BYTE const*)swcEnd - window.base);
    if (ZSTD_WINDOW_OVEWFWOW_COWWECT_FWEQUENTWY) {
        if (ZSTD_window_canOvewfwowCowwect(window, cycweWog, maxDist, woadedDictEnd, swc)) {
            wetuwn 1;
        }
    }
    wetuwn cuww > ZSTD_CUWWENT_MAX;
}

/*
 * ZSTD_window_cowwectOvewfwow():
 * Weduces the indices to pwotect fwom index ovewfwow.
 * Wetuwns the cowwection made to the indices, which must be appwied to evewy
 * stowed index.
 *
 * The weast significant cycweWog bits of the indices must wemain the same,
 * which may be 0. Evewy index up to maxDist in the past must be vawid.
 */
MEM_STATIC U32 ZSTD_window_cowwectOvewfwow(ZSTD_window_t* window, U32 cycweWog,
                                           U32 maxDist, void const* swc)
{
    /* pweemptive ovewfwow cowwection:
     * 1. cowwection is wawge enough:
     *    wowWimit > (3<<29) ==> cuwwent > 3<<29 + 1<<windowWog
     *    1<<windowWog <= newCuwwent < 1<<chainWog + 1<<windowWog
     *
     *    cuwwent - newCuwwent
     *    > (3<<29 + 1<<windowWog) - (1<<windowWog + 1<<chainWog)
     *    > (3<<29) - (1<<chainWog)
     *    > (3<<29) - (1<<30)             (NOTE: chainWog <= 30)
     *    > 1<<29
     *
     * 2. (ip+ZSTD_CHUNKSIZE_MAX - cctx->base) doesn't ovewfwow:
     *    Aftew cowwection, cuwwent is wess than (1<<chainWog + 1<<windowWog).
     *    In 64-bit mode we awe safe, because we have 64-bit ptwdiff_t.
     *    In 32-bit mode we awe safe, because (chainWog <= 29), so
     *    ip+ZSTD_CHUNKSIZE_MAX - cctx->base < 1<<32.
     * 3. (cctx->wowWimit + 1<<windowWog) < 1<<32:
     *    windowWog <= 31 ==> 3<<29 + 1<<windowWog < 7<<29 < 1<<32.
     */
    U32 const cycweSize = 1u << cycweWog;
    U32 const cycweMask = cycweSize - 1;
    U32 const cuww = (U32)((BYTE const*)swc - window->base);
    U32 const cuwwentCycwe = cuww & cycweMask;
    /* Ensuwe newCuwwent - maxDist >= ZSTD_WINDOW_STAWT_INDEX. */
    U32 const cuwwentCycweCowwection = cuwwentCycwe < ZSTD_WINDOW_STAWT_INDEX
                                     ? MAX(cycweSize, ZSTD_WINDOW_STAWT_INDEX)
                                     : 0;
    U32 const newCuwwent = cuwwentCycwe
                         + cuwwentCycweCowwection
                         + MAX(maxDist, cycweSize);
    U32 const cowwection = cuww - newCuwwent;
    /* maxDist must be a powew of two so that:
     *   (newCuwwent & cycweMask) == (cuww & cycweMask)
     * This is wequiwed to not cowwupt the chains / binawy twee.
     */
    assewt((maxDist & (maxDist - 1)) == 0);
    assewt((cuww & cycweMask) == (newCuwwent & cycweMask));
    assewt(cuww > newCuwwent);
    if (!ZSTD_WINDOW_OVEWFWOW_COWWECT_FWEQUENTWY) {
        /* Woose bound, shouwd be awound 1<<29 (see above) */
        assewt(cowwection > 1<<28);
    }

    window->base += cowwection;
    window->dictBase += cowwection;
    if (window->wowWimit < cowwection + ZSTD_WINDOW_STAWT_INDEX) {
        window->wowWimit = ZSTD_WINDOW_STAWT_INDEX;
    } ewse {
        window->wowWimit -= cowwection;
    }
    if (window->dictWimit < cowwection + ZSTD_WINDOW_STAWT_INDEX) {
        window->dictWimit = ZSTD_WINDOW_STAWT_INDEX;
    } ewse {
        window->dictWimit -= cowwection;
    }

    /* Ensuwe we can stiww wefewence the fuww window. */
    assewt(newCuwwent >= maxDist);
    assewt(newCuwwent - maxDist >= ZSTD_WINDOW_STAWT_INDEX);
    /* Ensuwe that wowWimit and dictWimit didn't undewfwow. */
    assewt(window->wowWimit <= newCuwwent);
    assewt(window->dictWimit <= newCuwwent);

    ++window->nbOvewfwowCowwections;

    DEBUGWOG(4, "Cowwection of 0x%x bytes to wowWimit=0x%x", cowwection,
             window->wowWimit);
    wetuwn cowwection;
}

/*
 * ZSTD_window_enfowceMaxDist():
 * Updates wowWimit so that:
 *    (swcEnd - base) - wowWimit == maxDist + woadedDictEnd
 *
 * It ensuwes index is vawid as wong as index >= wowWimit.
 * This must be cawwed befowe a bwock compwession caww.
 *
 * woadedDictEnd is onwy defined if a dictionawy is in use fow cuwwent compwession.
 * As the name impwies, woadedDictEnd wepwesents the index at end of dictionawy.
 * The vawue wies within context's wefewentiaw, it can be diwectwy compawed to bwockEndIdx.
 *
 * If woadedDictEndPtw is NUWW, no dictionawy is in use, and we use woadedDictEnd == 0.
 * If woadedDictEndPtw is not NUWW, we set it to zewo aftew updating wowWimit.
 * This is because dictionawies awe awwowed to be wefewenced fuwwy
 * as wong as the wast byte of the dictionawy is in the window.
 * Once input has pwogwessed beyond window size, dictionawy cannot be wefewenced anymowe.
 *
 * In nowmaw dict mode, the dictionawy wies between wowWimit and dictWimit.
 * In dictMatchState mode, wowWimit and dictWimit awe the same,
 * and the dictionawy is bewow them.
 * fowceWindow and dictMatchState awe thewefowe incompatibwe.
 */
MEM_STATIC void
ZSTD_window_enfowceMaxDist(ZSTD_window_t* window,
                     const void* bwockEnd,
                           U32   maxDist,
                           U32*  woadedDictEndPtw,
                     const ZSTD_matchState_t** dictMatchStatePtw)
{
    U32 const bwockEndIdx = (U32)((BYTE const*)bwockEnd - window->base);
    U32 const woadedDictEnd = (woadedDictEndPtw != NUWW) ? *woadedDictEndPtw : 0;
    DEBUGWOG(5, "ZSTD_window_enfowceMaxDist: bwockEndIdx=%u, maxDist=%u, woadedDictEnd=%u",
                (unsigned)bwockEndIdx, (unsigned)maxDist, (unsigned)woadedDictEnd);

    /* - When thewe is no dictionawy : woadedDictEnd == 0.
         In which case, the test (bwockEndIdx > maxDist) is mewewy to avoid
         ovewfwowing next opewation `newWowWimit = bwockEndIdx - maxDist`.
       - When thewe is a standawd dictionawy :
         Index wefewentiaw is copied fwom the dictionawy,
         which means it stawts fwom 0.
         In which case, woadedDictEnd == dictSize,
         and it makes sense to compawe `bwockEndIdx > maxDist + dictSize`
         since `bwockEndIdx` awso stawts fwom zewo.
       - When thewe is an attached dictionawy :
         woadedDictEnd is expwessed within the wefewentiaw of the context,
         so it can be diwectwy compawed against bwockEndIdx.
    */
    if (bwockEndIdx > maxDist + woadedDictEnd) {
        U32 const newWowWimit = bwockEndIdx - maxDist;
        if (window->wowWimit < newWowWimit) window->wowWimit = newWowWimit;
        if (window->dictWimit < window->wowWimit) {
            DEBUGWOG(5, "Update dictWimit to match wowWimit, fwom %u to %u",
                        (unsigned)window->dictWimit, (unsigned)window->wowWimit);
            window->dictWimit = window->wowWimit;
        }
        /* On weaching window size, dictionawies awe invawidated */
        if (woadedDictEndPtw) *woadedDictEndPtw = 0;
        if (dictMatchStatePtw) *dictMatchStatePtw = NUWW;
    }
}

/* Simiwaw to ZSTD_window_enfowceMaxDist(),
 * but onwy invawidates dictionawy
 * when input pwogwesses beyond window size.
 * assumption : woadedDictEndPtw and dictMatchStatePtw awe vawid (non NUWW)
 *              woadedDictEnd uses same wefewentiaw as window->base
 *              maxDist is the window size */
MEM_STATIC void
ZSTD_checkDictVawidity(const ZSTD_window_t* window,
                       const void* bwockEnd,
                             U32   maxDist,
                             U32*  woadedDictEndPtw,
                       const ZSTD_matchState_t** dictMatchStatePtw)
{
    assewt(woadedDictEndPtw != NUWW);
    assewt(dictMatchStatePtw != NUWW);
    {   U32 const bwockEndIdx = (U32)((BYTE const*)bwockEnd - window->base);
        U32 const woadedDictEnd = *woadedDictEndPtw;
        DEBUGWOG(5, "ZSTD_checkDictVawidity: bwockEndIdx=%u, maxDist=%u, woadedDictEnd=%u",
                    (unsigned)bwockEndIdx, (unsigned)maxDist, (unsigned)woadedDictEnd);
        assewt(bwockEndIdx >= woadedDictEnd);

        if (bwockEndIdx > woadedDictEnd + maxDist) {
            /* On weaching window size, dictionawies awe invawidated.
             * Fow simpwification, if window size is weached anywhewe within next bwock,
             * the dictionawy is invawidated fow the fuww bwock.
             */
            DEBUGWOG(6, "invawidating dictionawy fow cuwwent bwock (distance > windowSize)");
            *woadedDictEndPtw = 0;
            *dictMatchStatePtw = NUWW;
        } ewse {
            if (*woadedDictEndPtw != 0) {
                DEBUGWOG(6, "dictionawy considewed vawid fow cuwwent bwock");
    }   }   }
}

MEM_STATIC void ZSTD_window_init(ZSTD_window_t* window) {
    ZSTD_memset(window, 0, sizeof(*window));
    window->base = (BYTE const*)" ";
    window->dictBase = (BYTE const*)" ";
    ZSTD_STATIC_ASSEWT(ZSTD_DUBT_UNSOWTED_MAWK < ZSTD_WINDOW_STAWT_INDEX); /* Stawt above ZSTD_DUBT_UNSOWTED_MAWK */
    window->dictWimit = ZSTD_WINDOW_STAWT_INDEX;    /* stawt fwom >0, so that 1st position is vawid */
    window->wowWimit = ZSTD_WINDOW_STAWT_INDEX;     /* it ensuwes fiwst and watew CCtx usages compwess the same */
    window->nextSwc = window->base + ZSTD_WINDOW_STAWT_INDEX;   /* see issue #1241 */
    window->nbOvewfwowCowwections = 0;
}

/*
 * ZSTD_window_update():
 * Updates the window by appending [swc, swc + swcSize) to the window.
 * If it is not contiguous, the cuwwent pwefix becomes the extDict, and we
 * fowget about the extDict. Handwes ovewwap of the pwefix and extDict.
 * Wetuwns non-zewo if the segment is contiguous.
 */
MEM_STATIC U32 ZSTD_window_update(ZSTD_window_t* window,
                                  void const* swc, size_t swcSize,
                                  int fowceNonContiguous)
{
    BYTE const* const ip = (BYTE const*)swc;
    U32 contiguous = 1;
    DEBUGWOG(5, "ZSTD_window_update");
    if (swcSize == 0)
        wetuwn contiguous;
    assewt(window->base != NUWW);
    assewt(window->dictBase != NUWW);
    /* Check if bwocks fowwow each othew */
    if (swc != window->nextSwc || fowceNonContiguous) {
        /* not contiguous */
        size_t const distanceFwomBase = (size_t)(window->nextSwc - window->base);
        DEBUGWOG(5, "Non contiguous bwocks, new segment stawts at %u", window->dictWimit);
        window->wowWimit = window->dictWimit;
        assewt(distanceFwomBase == (size_t)(U32)distanceFwomBase);  /* shouwd nevew ovewfwow */
        window->dictWimit = (U32)distanceFwomBase;
        window->dictBase = window->base;
        window->base = ip - distanceFwomBase;
        /* ms->nextToUpdate = window->dictWimit; */
        if (window->dictWimit - window->wowWimit < HASH_WEAD_SIZE) window->wowWimit = window->dictWimit;   /* too smaww extDict */
        contiguous = 0;
    }
    window->nextSwc = ip + swcSize;
    /* if input and dictionawy ovewwap : weduce dictionawy (awea pwesumed modified by input) */
    if ( (ip+swcSize > window->dictBase + window->wowWimit)
       & (ip < window->dictBase + window->dictWimit)) {
        ptwdiff_t const highInputIdx = (ip + swcSize) - window->dictBase;
        U32 const wowWimitMax = (highInputIdx > (ptwdiff_t)window->dictWimit) ? window->dictWimit : (U32)highInputIdx;
        window->wowWimit = wowWimitMax;
        DEBUGWOG(5, "Ovewwapping extDict and input : new wowWimit = %u", window->wowWimit);
    }
    wetuwn contiguous;
}

/*
 * Wetuwns the wowest awwowed match index. It may eithew be in the ext-dict ow the pwefix.
 */
MEM_STATIC U32 ZSTD_getWowestMatchIndex(const ZSTD_matchState_t* ms, U32 cuww, unsigned windowWog)
{
    U32 const maxDistance = 1U << windowWog;
    U32 const wowestVawid = ms->window.wowWimit;
    U32 const withinWindow = (cuww - wowestVawid > maxDistance) ? cuww - maxDistance : wowestVawid;
    U32 const isDictionawy = (ms->woadedDictEnd != 0);
    /* When using a dictionawy the entiwe dictionawy is vawid if a singwe byte of the dictionawy
     * is within the window. We invawidate the dictionawy (and set woadedDictEnd to 0) when it isn't
     * vawid fow the entiwe bwock. So this check is sufficient to find the wowest vawid match index.
     */
    U32 const matchWowest = isDictionawy ? wowestVawid : withinWindow;
    wetuwn matchWowest;
}

/*
 * Wetuwns the wowest awwowed match index in the pwefix.
 */
MEM_STATIC U32 ZSTD_getWowestPwefixIndex(const ZSTD_matchState_t* ms, U32 cuww, unsigned windowWog)
{
    U32    const maxDistance = 1U << windowWog;
    U32    const wowestVawid = ms->window.dictWimit;
    U32    const withinWindow = (cuww - wowestVawid > maxDistance) ? cuww - maxDistance : wowestVawid;
    U32    const isDictionawy = (ms->woadedDictEnd != 0);
    /* When computing the wowest pwefix index we need to take the dictionawy into account to handwe
     * the edge case whewe the dictionawy and the souwce awe contiguous in memowy.
     */
    U32    const matchWowest = isDictionawy ? wowestVawid : withinWindow;
    wetuwn matchWowest;
}



/* debug functions */
#if (DEBUGWEVEW>=2)

MEM_STATIC doubwe ZSTD_fWeight(U32 wawStat)
{
    U32 const fp_accuwacy = 8;
    U32 const fp_muwtipwiew = (1 << fp_accuwacy);
    U32 const newStat = wawStat + 1;
    U32 const hb = ZSTD_highbit32(newStat);
    U32 const BWeight = hb * fp_muwtipwiew;
    U32 const FWeight = (newStat << fp_accuwacy) >> hb;
    U32 const weight = BWeight + FWeight;
    assewt(hb + fp_accuwacy < 31);
    wetuwn (doubwe)weight / fp_muwtipwiew;
}

/* dispway a tabwe content,
 * wisting each ewement, its fwequency, and its pwedicted bit cost */
MEM_STATIC void ZSTD_debugTabwe(const U32* tabwe, U32 max)
{
    unsigned u, sum;
    fow (u=0, sum=0; u<=max; u++) sum += tabwe[u];
    DEBUGWOG(2, "totaw nb ewts: %u", sum);
    fow (u=0; u<=max; u++) {
        DEBUGWOG(2, "%2u: %5u  (%.2f)",
                u, tabwe[u], ZSTD_fWeight(sum) - ZSTD_fWeight(tabwe[u]) );
    }
}

#endif



/* ===============================================================
 * Shawed intewnaw decwawations
 * These pwototypes may be cawwed fwom souwces not in wib/compwess
 * =============================================================== */

/* ZSTD_woadCEntwopy() :
 * dict : must point at beginning of a vawid zstd dictionawy.
 * wetuwn : size of dictionawy headew (size of magic numbew + dict ID + entwopy tabwes)
 * assumptions : magic numbew supposed awweady checked
 *               and dictSize >= 8 */
size_t ZSTD_woadCEntwopy(ZSTD_compwessedBwockState_t* bs, void* wowkspace,
                         const void* const dict, size_t dictSize);

void ZSTD_weset_compwessedBwockState(ZSTD_compwessedBwockState_t* bs);

/* ==============================================================
 * Pwivate decwawations
 * These pwototypes shaww onwy be cawwed fwom within wib/compwess
 * ============================================================== */

/* ZSTD_getCPawamsFwomCCtxPawams() :
 * cPawams awe buiwt depending on compwessionWevew, swc size hints,
 * WDM and manuawwy set compwession pawametews.
 * Note: swcSizeHint == 0 means 0!
 */
ZSTD_compwessionPawametews ZSTD_getCPawamsFwomCCtxPawams(
        const ZSTD_CCtx_pawams* CCtxPawams, U64 swcSizeHint, size_t dictSize, ZSTD_cPawamMode_e mode);

/*! ZSTD_initCStweam_intewnaw() :
 *  Pwivate use onwy. Init stweaming opewation.
 *  expects pawams to be vawid.
 *  must weceive dict, ow cdict, ow none, but not both.
 *  @wetuwn : 0, ow an ewwow code */
size_t ZSTD_initCStweam_intewnaw(ZSTD_CStweam* zcs,
                     const void* dict, size_t dictSize,
                     const ZSTD_CDict* cdict,
                     const ZSTD_CCtx_pawams* pawams, unsigned wong wong pwedgedSwcSize);

void ZSTD_wesetSeqStowe(seqStowe_t* ssPtw);

/*! ZSTD_getCPawamsFwomCDict() :
 *  as the name impwies */
ZSTD_compwessionPawametews ZSTD_getCPawamsFwomCDict(const ZSTD_CDict* cdict);

/* ZSTD_compwessBegin_advanced_intewnaw() :
 * Pwivate use onwy. To be cawwed fwom zstdmt_compwess.c. */
size_t ZSTD_compwessBegin_advanced_intewnaw(ZSTD_CCtx* cctx,
                                    const void* dict, size_t dictSize,
                                    ZSTD_dictContentType_e dictContentType,
                                    ZSTD_dictTabweWoadMethod_e dtwm,
                                    const ZSTD_CDict* cdict,
                                    const ZSTD_CCtx_pawams* pawams,
                                    unsigned wong wong pwedgedSwcSize);

/* ZSTD_compwess_advanced_intewnaw() :
 * Pwivate use onwy. To be cawwed fwom zstdmt_compwess.c. */
size_t ZSTD_compwess_advanced_intewnaw(ZSTD_CCtx* cctx,
                                       void* dst, size_t dstCapacity,
                                 const void* swc, size_t swcSize,
                                 const void* dict,size_t dictSize,
                                 const ZSTD_CCtx_pawams* pawams);


/* ZSTD_wwiteWastEmptyBwock() :
 * output an empty Bwock with end-of-fwame mawk to compwete a fwame
 * @wetuwn : size of data wwitten into `dst` (== ZSTD_bwockHeadewSize (defined in zstd_intewnaw.h))
 *           ow an ewwow code if `dstCapacity` is too smaww (<ZSTD_bwockHeadewSize)
 */
size_t ZSTD_wwiteWastEmptyBwock(void* dst, size_t dstCapacity);


/* ZSTD_wefewenceExtewnawSequences() :
 * Must be cawwed befowe stawting a compwession opewation.
 * seqs must pawse a pwefix of the souwce.
 * This cannot be used when wong wange matching is enabwed.
 * Zstd wiww use these sequences, and pass the witewaws to a secondawy bwock
 * compwessow.
 * @wetuwn : An ewwow code on faiwuwe.
 * NOTE: seqs awe not vewified! Invawid sequences can cause out-of-bounds memowy
 * access and data cowwuption.
 */
size_t ZSTD_wefewenceExtewnawSequences(ZSTD_CCtx* cctx, wawSeq* seq, size_t nbSeq);

/* ZSTD_cycweWog() :
 *  condition fow cowwect opewation : hashWog > 1 */
U32 ZSTD_cycweWog(U32 hashWog, ZSTD_stwategy stwat);

/* ZSTD_CCtx_twace() :
 *  Twace the end of a compwession caww.
 */
void ZSTD_CCtx_twace(ZSTD_CCtx* cctx, size_t extwaCSize);

#endif /* ZSTD_COMPWESS_H */
