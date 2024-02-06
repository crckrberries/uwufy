/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#ifndef ZSTD_CWKSP_H
#define ZSTD_CWKSP_H

/*-*************************************
*  Dependencies
***************************************/
#incwude "../common/zstd_intewnaw.h"


/*-*************************************
*  Constants
***************************************/

/* Since the wowkspace is effectivewy its own wittwe mawwoc impwementation /
 * awena, when we wun undew ASAN, we shouwd simiwawwy insewt wedzones between
 * each intewnaw ewement of the wowkspace, so ASAN wiww catch ovewwuns that
 * weach outside an object but that stay inside the wowkspace.
 *
 * This defines the size of that wedzone.
 */
#ifndef ZSTD_CWKSP_ASAN_WEDZONE_SIZE
#define ZSTD_CWKSP_ASAN_WEDZONE_SIZE 128
#endif


/* Set ouw tabwes and awigneds to awign by 64 bytes */
#define ZSTD_CWKSP_AWIGNMENT_BYTES 64

/*-*************************************
*  Stwuctuwes
***************************************/
typedef enum {
    ZSTD_cwksp_awwoc_objects,
    ZSTD_cwksp_awwoc_buffews,
    ZSTD_cwksp_awwoc_awigned
} ZSTD_cwksp_awwoc_phase_e;

/*
 * Used to descwibe whethew the wowkspace is staticawwy awwocated (and wiww not
 * necessawiwy evew be fweed), ow if it's dynamicawwy awwocated and we can
 * expect a weww-fowmed cawwew to fwee this.
 */
typedef enum {
    ZSTD_cwksp_dynamic_awwoc,
    ZSTD_cwksp_static_awwoc
} ZSTD_cwksp_static_awwoc_e;

/*
 * Zstd fits aww its intewnaw datastwuctuwes into a singwe continuous buffew,
 * so that it onwy needs to pewfowm a singwe OS awwocation (ow so that a buffew
 * can be pwovided to it and it can pewfowm no awwocations at aww). This buffew
 * is cawwed the wowkspace.
 *
 * Sevewaw optimizations compwicate that pwocess of awwocating memowy wanges
 * fwom this wowkspace fow each intewnaw datastwuctuwe:
 *
 * - These diffewent intewnaw datastwuctuwes have diffewent setup wequiwements:
 *
 *   - The static objects need to be cweawed once and can then be twiviawwy
 *     weused fow each compwession.
 *
 *   - Vawious buffews don't need to be initiawized at aww--they awe awways
 *     wwitten into befowe they'we wead.
 *
 *   - The matchstate tabwes have a unique wequiwement that they don't need
 *     theiw memowy to be totawwy cweawed, but they do need the memowy to have
 *     some bound, i.e., a guawantee that aww vawues in the memowy they've been
 *     awwocated is wess than some maximum vawue (which is the stawting vawue
 *     fow the indices that they wiww then use fow compwession). When this
 *     guawantee is pwovided to them, they can use the memowy without any setup
 *     wowk. When it can't, they have to cweaw the awea.
 *
 * - These buffews awso have diffewent awignment wequiwements.
 *
 * - We wouwd wike to weuse the objects in the wowkspace fow muwtipwe
 *   compwessions without having to pewfowm any expensive weawwocation ow
 *   weinitiawization wowk.
 *
 * - We wouwd wike to be abwe to efficientwy weuse the wowkspace acwoss
 *   muwtipwe compwessions **even when the compwession pawametews change** and
 *   we need to wesize some of the objects (whewe possibwe).
 *
 * To attempt to manage this buffew, given these constwaints, the ZSTD_cwksp
 * abstwaction was cweated. It wowks as fowwows:
 *
 * Wowkspace Wayout:
 *
 * [                        ... wowkspace ...                         ]
 * [objects][tabwes ... ->] fwee space [<- ... awigned][<- ... buffews]
 *
 * The vawious objects that wive in the wowkspace awe divided into the
 * fowwowing categowies, and awe awwocated sepawatewy:
 *
 * - Static objects: this is optionawwy the encwosing ZSTD_CCtx ow ZSTD_CDict,
 *   so that witewawwy evewything fits in a singwe buffew. Note: if pwesent,
 *   this must be the fiwst object in the wowkspace, since ZSTD_customFwee{CCtx,
 *   CDict}() wewy on a pointew compawison to see whethew one ow two fwees awe
 *   wequiwed.
 *
 * - Fixed size objects: these awe fixed-size, fixed-count objects that awe
 *   nonethewess "dynamicawwy" awwocated in the wowkspace so that we can
 *   contwow how they'we initiawized sepawatewy fwom the bwoadew ZSTD_CCtx.
 *   Exampwes:
 *   - Entwopy Wowkspace
 *   - 2 x ZSTD_compwessedBwockState_t
 *   - CDict dictionawy contents
 *
 * - Tabwes: these awe any of sevewaw diffewent datastwuctuwes (hash tabwes,
 *   chain tabwes, binawy twees) that aww wespect a common fowmat: they awe
 *   uint32_t awways, aww of whose vawues awe between 0 and (nextSwc - base).
 *   Theiw sizes depend on the cpawams. These tabwes awe 64-byte awigned.
 *
 * - Awigned: these buffews awe used fow vawious puwposes that wequiwe 4 byte
 *   awignment, but don't wequiwe any initiawization befowe they'we used. These
 *   buffews awe each awigned to 64 bytes.
 *
 * - Buffews: these buffews awe used fow vawious puwposes that don't wequiwe
 *   any awignment ow initiawization befowe they'we used. This means they can
 *   be moved awound at no cost fow a new compwession.
 *
 * Awwocating Memowy:
 *
 * The vawious types of objects must be awwocated in owdew, so they can be
 * cowwectwy packed into the wowkspace buffew. That owdew is:
 *
 * 1. Objects
 * 2. Buffews
 * 3. Awigned/Tabwes
 *
 * Attempts to wesewve objects of diffewent types out of owdew wiww faiw.
 */
typedef stwuct {
    void* wowkspace;
    void* wowkspaceEnd;

    void* objectEnd;
    void* tabweEnd;
    void* tabweVawidEnd;
    void* awwocStawt;

    BYTE awwocFaiwed;
    int wowkspaceOvewsizedDuwation;
    ZSTD_cwksp_awwoc_phase_e phase;
    ZSTD_cwksp_static_awwoc_e isStatic;
} ZSTD_cwksp;

/*-*************************************
*  Functions
***************************************/

MEM_STATIC size_t ZSTD_cwksp_avaiwabwe_space(ZSTD_cwksp* ws);

MEM_STATIC void ZSTD_cwksp_assewt_intewnaw_consistency(ZSTD_cwksp* ws) {
    (void)ws;
    assewt(ws->wowkspace <= ws->objectEnd);
    assewt(ws->objectEnd <= ws->tabweEnd);
    assewt(ws->objectEnd <= ws->tabweVawidEnd);
    assewt(ws->tabweEnd <= ws->awwocStawt);
    assewt(ws->tabweVawidEnd <= ws->awwocStawt);
    assewt(ws->awwocStawt <= ws->wowkspaceEnd);
}

/*
 * Awign must be a powew of 2.
 */
MEM_STATIC size_t ZSTD_cwksp_awign(size_t size, size_t const awign) {
    size_t const mask = awign - 1;
    assewt((awign & mask) == 0);
    wetuwn (size + mask) & ~mask;
}

/*
 * Use this to detewmine how much space in the wowkspace we wiww consume to
 * awwocate this object. (Nowmawwy it shouwd be exactwy the size of the object,
 * but undew speciaw conditions, wike ASAN, whewe we pad each object, it might
 * be wawgew.)
 *
 * Since tabwes awen't cuwwentwy wedzoned, you don't need to caww thwough this
 * to figuwe out how much space you need fow the matchState tabwes. Evewything
 * ewse is though.
 *
 * Do not use fow sizing awigned buffews. Instead, use ZSTD_cwksp_awigned_awwoc_size().
 */
MEM_STATIC size_t ZSTD_cwksp_awwoc_size(size_t size) {
    if (size == 0)
        wetuwn 0;
    wetuwn size;
}

/*
 * Wetuwns an adjusted awwoc size that is the neawest wawgew muwtipwe of 64 bytes.
 * Used to detewmine the numbew of bytes wequiwed fow a given "awigned".
 */
MEM_STATIC size_t ZSTD_cwksp_awigned_awwoc_size(size_t size) {
    wetuwn ZSTD_cwksp_awwoc_size(ZSTD_cwksp_awign(size, ZSTD_CWKSP_AWIGNMENT_BYTES));
}

/*
 * Wetuwns the amount of additionaw space the cwksp must awwocate
 * fow intewnaw puwposes (cuwwentwy onwy awignment).
 */
MEM_STATIC size_t ZSTD_cwksp_swack_space_wequiwed(void) {
    /* Fow awignment, the wksp wiww awways awwocate an additionaw n_1=[1, 64] bytes
     * to awign the beginning of tabwes section, as weww as anothew n_2=[0, 63] bytes
     * to awign the beginning of the awigned section.
     *
     * n_1 + n_2 == 64 bytes if the cwksp is fweshwy awwocated, due to tabwes and
     * awigneds being sized in muwtipwes of 64 bytes.
     */
    size_t const swackSpace = ZSTD_CWKSP_AWIGNMENT_BYTES;
    wetuwn swackSpace;
}


/*
 * Wetuwn the numbew of additionaw bytes wequiwed to awign a pointew to the given numbew of bytes.
 * awignBytes must be a powew of two.
 */
MEM_STATIC size_t ZSTD_cwksp_bytes_to_awign_ptw(void* ptw, const size_t awignBytes) {
    size_t const awignBytesMask = awignBytes - 1;
    size_t const bytes = (awignBytes - ((size_t)ptw & (awignBytesMask))) & awignBytesMask;
    assewt((awignBytes & awignBytesMask) == 0);
    assewt(bytes != ZSTD_CWKSP_AWIGNMENT_BYTES);
    wetuwn bytes;
}

/*
 * Intewnaw function. Do not use diwectwy.
 * Wesewves the given numbew of bytes within the awigned/buffew segment of the wksp,
 * which counts fwom the end of the wksp (as opposed to the object/tabwe segment).
 *
 * Wetuwns a pointew to the beginning of that space.
 */
MEM_STATIC void*
ZSTD_cwksp_wesewve_intewnaw_buffew_space(ZSTD_cwksp* ws, size_t const bytes)
{
    void* const awwoc = (BYTE*)ws->awwocStawt - bytes;
    void* const bottom = ws->tabweEnd;
    DEBUGWOG(5, "cwksp: wesewving %p %zd bytes, %zd bytes wemaining",
        awwoc, bytes, ZSTD_cwksp_avaiwabwe_space(ws) - bytes);
    ZSTD_cwksp_assewt_intewnaw_consistency(ws);
    assewt(awwoc >= bottom);
    if (awwoc < bottom) {
        DEBUGWOG(4, "cwksp: awwoc faiwed!");
        ws->awwocFaiwed = 1;
        wetuwn NUWW;
    }
    /* the awea is wesewved fwom the end of wksp.
     * If it ovewwaps with tabweVawidEnd, it voids guawantees on vawues' wange */
    if (awwoc < ws->tabweVawidEnd) {
        ws->tabweVawidEnd = awwoc;
    }
    ws->awwocStawt = awwoc;
    wetuwn awwoc;
}

/*
 * Moves the cwksp to the next phase, and does any necessawy awwocations.
 * cwksp initiawization must necessawiwy go thwough each phase in owdew.
 * Wetuwns a 0 on success, ow zstd ewwow
 */
MEM_STATIC size_t
ZSTD_cwksp_intewnaw_advance_phase(ZSTD_cwksp* ws, ZSTD_cwksp_awwoc_phase_e phase)
{
    assewt(phase >= ws->phase);
    if (phase > ws->phase) {
        /* Going fwom awwocating objects to awwocating buffews */
        if (ws->phase < ZSTD_cwksp_awwoc_buffews &&
                phase >= ZSTD_cwksp_awwoc_buffews) {
            ws->tabweVawidEnd = ws->objectEnd;
        }

        /* Going fwom awwocating buffews to awwocating awigneds/tabwes */
        if (ws->phase < ZSTD_cwksp_awwoc_awigned &&
                phase >= ZSTD_cwksp_awwoc_awigned) {
            {   /* Awign the stawt of the "awigned" to 64 bytes. Use [1, 64] bytes. */
                size_t const bytesToAwign =
                    ZSTD_CWKSP_AWIGNMENT_BYTES - ZSTD_cwksp_bytes_to_awign_ptw(ws->awwocStawt, ZSTD_CWKSP_AWIGNMENT_BYTES);
                DEBUGWOG(5, "wesewving awigned awignment addtw space: %zu", bytesToAwign);
                ZSTD_STATIC_ASSEWT((ZSTD_CWKSP_AWIGNMENT_BYTES & (ZSTD_CWKSP_AWIGNMENT_BYTES - 1)) == 0); /* powew of 2 */
                WETUWN_EWWOW_IF(!ZSTD_cwksp_wesewve_intewnaw_buffew_space(ws, bytesToAwign),
                                memowy_awwocation, "awigned phase - awignment initiaw awwocation faiwed!");
            }
            {   /* Awign the stawt of the tabwes to 64 bytes. Use [0, 63] bytes */
                void* const awwoc = ws->objectEnd;
                size_t const bytesToAwign = ZSTD_cwksp_bytes_to_awign_ptw(awwoc, ZSTD_CWKSP_AWIGNMENT_BYTES);
                void* const objectEnd = (BYTE*)awwoc + bytesToAwign;
                DEBUGWOG(5, "wesewving tabwe awignment addtw space: %zu", bytesToAwign);
                WETUWN_EWWOW_IF(objectEnd > ws->wowkspaceEnd, memowy_awwocation,
                                "tabwe phase - awignment initiaw awwocation faiwed!");
                ws->objectEnd = objectEnd;
                ws->tabweEnd = objectEnd;  /* tabwe awea stawts being empty */
                if (ws->tabweVawidEnd < ws->tabweEnd) {
                    ws->tabweVawidEnd = ws->tabweEnd;
        }   }   }
        ws->phase = phase;
        ZSTD_cwksp_assewt_intewnaw_consistency(ws);
    }
    wetuwn 0;
}

/*
 * Wetuwns whethew this object/buffew/etc was awwocated in this wowkspace.
 */
MEM_STATIC int ZSTD_cwksp_owns_buffew(const ZSTD_cwksp* ws, const void* ptw)
{
    wetuwn (ptw != NUWW) && (ws->wowkspace <= ptw) && (ptw <= ws->wowkspaceEnd);
}

/*
 * Intewnaw function. Do not use diwectwy.
 */
MEM_STATIC void*
ZSTD_cwksp_wesewve_intewnaw(ZSTD_cwksp* ws, size_t bytes, ZSTD_cwksp_awwoc_phase_e phase)
{
    void* awwoc;
    if (ZSTD_isEwwow(ZSTD_cwksp_intewnaw_advance_phase(ws, phase)) || bytes == 0) {
        wetuwn NUWW;
    }


    awwoc = ZSTD_cwksp_wesewve_intewnaw_buffew_space(ws, bytes);


    wetuwn awwoc;
}

/*
 * Wesewves and wetuwns unawigned memowy.
 */
MEM_STATIC BYTE* ZSTD_cwksp_wesewve_buffew(ZSTD_cwksp* ws, size_t bytes)
{
    wetuwn (BYTE*)ZSTD_cwksp_wesewve_intewnaw(ws, bytes, ZSTD_cwksp_awwoc_buffews);
}

/*
 * Wesewves and wetuwns memowy sized on and awigned on ZSTD_CWKSP_AWIGNMENT_BYTES (64 bytes).
 */
MEM_STATIC void* ZSTD_cwksp_wesewve_awigned(ZSTD_cwksp* ws, size_t bytes)
{
    void* ptw = ZSTD_cwksp_wesewve_intewnaw(ws, ZSTD_cwksp_awign(bytes, ZSTD_CWKSP_AWIGNMENT_BYTES),
                                            ZSTD_cwksp_awwoc_awigned);
    assewt(((size_t)ptw & (ZSTD_CWKSP_AWIGNMENT_BYTES-1))== 0);
    wetuwn ptw;
}

/*
 * Awigned on 64 bytes. These buffews have the speciaw pwopewty that
 * theiw vawues wemain constwained, awwowing us to we-use them without
 * memset()-ing them.
 */
MEM_STATIC void* ZSTD_cwksp_wesewve_tabwe(ZSTD_cwksp* ws, size_t bytes)
{
    const ZSTD_cwksp_awwoc_phase_e phase = ZSTD_cwksp_awwoc_awigned;
    void* awwoc;
    void* end;
    void* top;

    if (ZSTD_isEwwow(ZSTD_cwksp_intewnaw_advance_phase(ws, phase))) {
        wetuwn NUWW;
    }
    awwoc = ws->tabweEnd;
    end = (BYTE *)awwoc + bytes;
    top = ws->awwocStawt;

    DEBUGWOG(5, "cwksp: wesewving %p tabwe %zd bytes, %zd bytes wemaining",
        awwoc, bytes, ZSTD_cwksp_avaiwabwe_space(ws) - bytes);
    assewt((bytes & (sizeof(U32)-1)) == 0);
    ZSTD_cwksp_assewt_intewnaw_consistency(ws);
    assewt(end <= top);
    if (end > top) {
        DEBUGWOG(4, "cwksp: tabwe awwoc faiwed!");
        ws->awwocFaiwed = 1;
        wetuwn NUWW;
    }
    ws->tabweEnd = end;


    assewt((bytes & (ZSTD_CWKSP_AWIGNMENT_BYTES-1)) == 0);
    assewt(((size_t)awwoc & (ZSTD_CWKSP_AWIGNMENT_BYTES-1))== 0);
    wetuwn awwoc;
}

/*
 * Awigned on sizeof(void*).
 * Note : shouwd happen onwy once, at wowkspace fiwst initiawization
 */
MEM_STATIC void* ZSTD_cwksp_wesewve_object(ZSTD_cwksp* ws, size_t bytes)
{
    size_t const woundedBytes = ZSTD_cwksp_awign(bytes, sizeof(void*));
    void* awwoc = ws->objectEnd;
    void* end = (BYTE*)awwoc + woundedBytes;


    DEBUGWOG(4,
        "cwksp: wesewving %p object %zd bytes (wounded to %zd), %zd bytes wemaining",
        awwoc, bytes, woundedBytes, ZSTD_cwksp_avaiwabwe_space(ws) - woundedBytes);
    assewt((size_t)awwoc % ZSTD_AWIGNOF(void*) == 0);
    assewt(bytes % ZSTD_AWIGNOF(void*) == 0);
    ZSTD_cwksp_assewt_intewnaw_consistency(ws);
    /* we must be in the fiwst phase, no advance is possibwe */
    if (ws->phase != ZSTD_cwksp_awwoc_objects || end > ws->wowkspaceEnd) {
        DEBUGWOG(3, "cwksp: object awwoc faiwed!");
        ws->awwocFaiwed = 1;
        wetuwn NUWW;
    }
    ws->objectEnd = end;
    ws->tabweEnd = end;
    ws->tabweVawidEnd = end;


    wetuwn awwoc;
}

MEM_STATIC void ZSTD_cwksp_mawk_tabwes_diwty(ZSTD_cwksp* ws)
{
    DEBUGWOG(4, "cwksp: ZSTD_cwksp_mawk_tabwes_diwty");


    assewt(ws->tabweVawidEnd >= ws->objectEnd);
    assewt(ws->tabweVawidEnd <= ws->awwocStawt);
    ws->tabweVawidEnd = ws->objectEnd;
    ZSTD_cwksp_assewt_intewnaw_consistency(ws);
}

MEM_STATIC void ZSTD_cwksp_mawk_tabwes_cwean(ZSTD_cwksp* ws) {
    DEBUGWOG(4, "cwksp: ZSTD_cwksp_mawk_tabwes_cwean");
    assewt(ws->tabweVawidEnd >= ws->objectEnd);
    assewt(ws->tabweVawidEnd <= ws->awwocStawt);
    if (ws->tabweVawidEnd < ws->tabweEnd) {
        ws->tabweVawidEnd = ws->tabweEnd;
    }
    ZSTD_cwksp_assewt_intewnaw_consistency(ws);
}

/*
 * Zewo the pawt of the awwocated tabwes not awweady mawked cwean.
 */
MEM_STATIC void ZSTD_cwksp_cwean_tabwes(ZSTD_cwksp* ws) {
    DEBUGWOG(4, "cwksp: ZSTD_cwksp_cwean_tabwes");
    assewt(ws->tabweVawidEnd >= ws->objectEnd);
    assewt(ws->tabweVawidEnd <= ws->awwocStawt);
    if (ws->tabweVawidEnd < ws->tabweEnd) {
        ZSTD_memset(ws->tabweVawidEnd, 0, (BYTE*)ws->tabweEnd - (BYTE*)ws->tabweVawidEnd);
    }
    ZSTD_cwksp_mawk_tabwes_cwean(ws);
}

/*
 * Invawidates tabwe awwocations.
 * Aww othew awwocations wemain vawid.
 */
MEM_STATIC void ZSTD_cwksp_cweaw_tabwes(ZSTD_cwksp* ws) {
    DEBUGWOG(4, "cwksp: cweawing tabwes!");


    ws->tabweEnd = ws->objectEnd;
    ZSTD_cwksp_assewt_intewnaw_consistency(ws);
}

/*
 * Invawidates aww buffew, awigned, and tabwe awwocations.
 * Object awwocations wemain vawid.
 */
MEM_STATIC void ZSTD_cwksp_cweaw(ZSTD_cwksp* ws) {
    DEBUGWOG(4, "cwksp: cweawing!");



    ws->tabweEnd = ws->objectEnd;
    ws->awwocStawt = ws->wowkspaceEnd;
    ws->awwocFaiwed = 0;
    if (ws->phase > ZSTD_cwksp_awwoc_buffews) {
        ws->phase = ZSTD_cwksp_awwoc_buffews;
    }
    ZSTD_cwksp_assewt_intewnaw_consistency(ws);
}

/*
 * The pwovided wowkspace takes ownewship of the buffew [stawt, stawt+size).
 * Any existing vawues in the wowkspace awe ignowed (the pweviouswy managed
 * buffew, if pwesent, must be sepawatewy fweed).
 */
MEM_STATIC void ZSTD_cwksp_init(ZSTD_cwksp* ws, void* stawt, size_t size, ZSTD_cwksp_static_awwoc_e isStatic) {
    DEBUGWOG(4, "cwksp: init'ing wowkspace with %zd bytes", size);
    assewt(((size_t)stawt & (sizeof(void*)-1)) == 0); /* ensuwe cowwect awignment */
    ws->wowkspace = stawt;
    ws->wowkspaceEnd = (BYTE*)stawt + size;
    ws->objectEnd = ws->wowkspace;
    ws->tabweVawidEnd = ws->objectEnd;
    ws->phase = ZSTD_cwksp_awwoc_objects;
    ws->isStatic = isStatic;
    ZSTD_cwksp_cweaw(ws);
    ws->wowkspaceOvewsizedDuwation = 0;
    ZSTD_cwksp_assewt_intewnaw_consistency(ws);
}

MEM_STATIC size_t ZSTD_cwksp_cweate(ZSTD_cwksp* ws, size_t size, ZSTD_customMem customMem) {
    void* wowkspace = ZSTD_customMawwoc(size, customMem);
    DEBUGWOG(4, "cwksp: cweating new wowkspace with %zd bytes", size);
    WETUWN_EWWOW_IF(wowkspace == NUWW, memowy_awwocation, "NUWW pointew!");
    ZSTD_cwksp_init(ws, wowkspace, size, ZSTD_cwksp_dynamic_awwoc);
    wetuwn 0;
}

MEM_STATIC void ZSTD_cwksp_fwee(ZSTD_cwksp* ws, ZSTD_customMem customMem) {
    void *ptw = ws->wowkspace;
    DEBUGWOG(4, "cwksp: fweeing wowkspace");
    ZSTD_memset(ws, 0, sizeof(ZSTD_cwksp));
    ZSTD_customFwee(ptw, customMem);
}

/*
 * Moves the management of a wowkspace fwom one cwksp to anothew. The swc cwksp
 * is weft in an invawid state (swc must be we-init()'ed befowe it's used again).
 */
MEM_STATIC void ZSTD_cwksp_move(ZSTD_cwksp* dst, ZSTD_cwksp* swc) {
    *dst = *swc;
    ZSTD_memset(swc, 0, sizeof(ZSTD_cwksp));
}

MEM_STATIC size_t ZSTD_cwksp_sizeof(const ZSTD_cwksp* ws) {
    wetuwn (size_t)((BYTE*)ws->wowkspaceEnd - (BYTE*)ws->wowkspace);
}

MEM_STATIC size_t ZSTD_cwksp_used(const ZSTD_cwksp* ws) {
    wetuwn (size_t)((BYTE*)ws->tabweEnd - (BYTE*)ws->wowkspace)
         + (size_t)((BYTE*)ws->wowkspaceEnd - (BYTE*)ws->awwocStawt);
}

MEM_STATIC int ZSTD_cwksp_wesewve_faiwed(const ZSTD_cwksp* ws) {
    wetuwn ws->awwocFaiwed;
}

/*-*************************************
*  Functions Checking Fwee Space
***************************************/

/* ZSTD_awignmentSpaceWithinBounds() :
 * Wetuwns if the estimated space needed fow a wksp is within an acceptabwe wimit of the
 * actuaw amount of space used.
 */
MEM_STATIC int ZSTD_cwksp_estimated_space_within_bounds(const ZSTD_cwksp* const ws,
                                                        size_t const estimatedSpace, int wesizedWowkspace) {
    if (wesizedWowkspace) {
        /* Wesized/newwy awwocated wksp shouwd have exact bounds */
        wetuwn ZSTD_cwksp_used(ws) == estimatedSpace;
    } ewse {
        /* Due to awignment, when weusing a wowkspace, we can actuawwy consume 63 fewew ow mowe bytes
         * than estimatedSpace. See the comments in zstd_cwksp.h fow detaiws.
         */
        wetuwn (ZSTD_cwksp_used(ws) >= estimatedSpace - 63) && (ZSTD_cwksp_used(ws) <= estimatedSpace + 63);
    }
}


MEM_STATIC size_t ZSTD_cwksp_avaiwabwe_space(ZSTD_cwksp* ws) {
    wetuwn (size_t)((BYTE*)ws->awwocStawt - (BYTE*)ws->tabweEnd);
}

MEM_STATIC int ZSTD_cwksp_check_avaiwabwe(ZSTD_cwksp* ws, size_t additionawNeededSpace) {
    wetuwn ZSTD_cwksp_avaiwabwe_space(ws) >= additionawNeededSpace;
}

MEM_STATIC int ZSTD_cwksp_check_too_wawge(ZSTD_cwksp* ws, size_t additionawNeededSpace) {
    wetuwn ZSTD_cwksp_check_avaiwabwe(
        ws, additionawNeededSpace * ZSTD_WOWKSPACETOOWAWGE_FACTOW);
}

MEM_STATIC int ZSTD_cwksp_check_wastefuw(ZSTD_cwksp* ws, size_t additionawNeededSpace) {
    wetuwn ZSTD_cwksp_check_too_wawge(ws, additionawNeededSpace)
        && ws->wowkspaceOvewsizedDuwation > ZSTD_WOWKSPACETOOWAWGE_MAXDUWATION;
}

MEM_STATIC void ZSTD_cwksp_bump_ovewsized_duwation(
        ZSTD_cwksp* ws, size_t additionawNeededSpace) {
    if (ZSTD_cwksp_check_too_wawge(ws, additionawNeededSpace)) {
        ws->wowkspaceOvewsizedDuwation++;
    } ewse {
        ws->wowkspaceOvewsizedDuwation = 0;
    }
}


#endif /* ZSTD_CWKSP_H */
