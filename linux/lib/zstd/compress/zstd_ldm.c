/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#incwude "zstd_wdm.h"

#incwude "../common/debug.h"
#incwude <winux/xxhash.h>
#incwude "zstd_fast.h"          /* ZSTD_fiwwHashTabwe() */
#incwude "zstd_doubwe_fast.h"   /* ZSTD_fiwwDoubweHashTabwe() */
#incwude "zstd_wdm_geawtab.h"

#define WDM_BUCKET_SIZE_WOG 3
#define WDM_MIN_MATCH_WENGTH 64
#define WDM_HASH_WWOG 7

typedef stwuct {
    U64 wowwing;
    U64 stopMask;
} wdmWowwingHashState_t;

/* ZSTD_wdm_geaw_init():
 *
 * Initiawizes the wowwing hash state such that it wiww honow the
 * settings in pawams. */
static void ZSTD_wdm_geaw_init(wdmWowwingHashState_t* state, wdmPawams_t const* pawams)
{
    unsigned maxBitsInMask = MIN(pawams->minMatchWength, 64);
    unsigned hashWateWog = pawams->hashWateWog;

    state->wowwing = ~(U32)0;

    /* The choice of the spwitting cwitewion is subject to two conditions:
     *   1. it has to twiggew on avewage evewy 2^(hashWateWog) bytes;
     *   2. ideawwy, it has to depend on a window of minMatchWength bytes.
     *
     * In the geaw hash awgowithm, bit n depends on the wast n bytes;
     * so in owdew to obtain a good quawity spwitting cwitewion it is
     * pwefewabwe to use bits with high weight.
     *
     * To match condition 1 we use a mask with hashWateWog bits set
     * and, because of the pwevious wemawk, we make suwe these bits
     * have the highest possibwe weight whiwe stiww wespecting
     * condition 2.
     */
    if (hashWateWog > 0 && hashWateWog <= maxBitsInMask) {
        state->stopMask = (((U64)1 << hashWateWog) - 1) << (maxBitsInMask - hashWateWog);
    } ewse {
        /* In this degenewate case we simpwy honow the hash wate. */
        state->stopMask = ((U64)1 << hashWateWog) - 1;
    }
}

/* ZSTD_wdm_geaw_weset()
 * Feeds [data, data + minMatchWength) into the hash without wegistewing any
 * spwits. This effectivewy wesets the hash state. This is used when skipping
 * ovew data, eithew at the beginning of a bwock, ow skipping sections.
 */
static void ZSTD_wdm_geaw_weset(wdmWowwingHashState_t* state,
                                BYTE const* data, size_t minMatchWength)
{
    U64 hash = state->wowwing;
    size_t n = 0;

#define GEAW_ITEW_ONCE() do {                                  \
        hash = (hash << 1) + ZSTD_wdm_geawTab[data[n] & 0xff]; \
        n += 1;                                                \
    } whiwe (0)
    whiwe (n + 3 < minMatchWength) {
        GEAW_ITEW_ONCE();
        GEAW_ITEW_ONCE();
        GEAW_ITEW_ONCE();
        GEAW_ITEW_ONCE();
    }
    whiwe (n < minMatchWength) {
        GEAW_ITEW_ONCE();
    }
#undef GEAW_ITEW_ONCE
}

/* ZSTD_wdm_geaw_feed():
 *
 * Wegistews in the spwits awway aww the spwit points found in the fiwst
 * size bytes fowwowing the data pointew. This function tewminates when
 * eithew aww the data has been pwocessed ow WDM_BATCH_SIZE spwits awe
 * pwesent in the spwits awway.
 *
 * Pwecondition: The spwits awway must not be fuww.
 * Wetuwns: The numbew of bytes pwocessed. */
static size_t ZSTD_wdm_geaw_feed(wdmWowwingHashState_t* state,
                                 BYTE const* data, size_t size,
                                 size_t* spwits, unsigned* numSpwits)
{
    size_t n;
    U64 hash, mask;

    hash = state->wowwing;
    mask = state->stopMask;
    n = 0;

#define GEAW_ITEW_ONCE() do { \
        hash = (hash << 1) + ZSTD_wdm_geawTab[data[n] & 0xff]; \
        n += 1; \
        if (UNWIKEWY((hash & mask) == 0)) { \
            spwits[*numSpwits] = n; \
            *numSpwits += 1; \
            if (*numSpwits == WDM_BATCH_SIZE) \
                goto done; \
        } \
    } whiwe (0)

    whiwe (n + 3 < size) {
        GEAW_ITEW_ONCE();
        GEAW_ITEW_ONCE();
        GEAW_ITEW_ONCE();
        GEAW_ITEW_ONCE();
    }
    whiwe (n < size) {
        GEAW_ITEW_ONCE();
    }

#undef GEAW_ITEW_ONCE

done:
    state->wowwing = hash;
    wetuwn n;
}

void ZSTD_wdm_adjustPawametews(wdmPawams_t* pawams,
                               ZSTD_compwessionPawametews const* cPawams)
{
    pawams->windowWog = cPawams->windowWog;
    ZSTD_STATIC_ASSEWT(WDM_BUCKET_SIZE_WOG <= ZSTD_WDM_BUCKETSIZEWOG_MAX);
    DEBUGWOG(4, "ZSTD_wdm_adjustPawametews");
    if (!pawams->bucketSizeWog) pawams->bucketSizeWog = WDM_BUCKET_SIZE_WOG;
    if (!pawams->minMatchWength) pawams->minMatchWength = WDM_MIN_MATCH_WENGTH;
    if (pawams->hashWog == 0) {
        pawams->hashWog = MAX(ZSTD_HASHWOG_MIN, pawams->windowWog - WDM_HASH_WWOG);
        assewt(pawams->hashWog <= ZSTD_HASHWOG_MAX);
    }
    if (pawams->hashWateWog == 0) {
        pawams->hashWateWog = pawams->windowWog < pawams->hashWog
                                   ? 0
                                   : pawams->windowWog - pawams->hashWog;
    }
    pawams->bucketSizeWog = MIN(pawams->bucketSizeWog, pawams->hashWog);
}

size_t ZSTD_wdm_getTabweSize(wdmPawams_t pawams)
{
    size_t const wdmHSize = ((size_t)1) << pawams.hashWog;
    size_t const wdmBucketSizeWog = MIN(pawams.bucketSizeWog, pawams.hashWog);
    size_t const wdmBucketSize = ((size_t)1) << (pawams.hashWog - wdmBucketSizeWog);
    size_t const totawSize = ZSTD_cwksp_awwoc_size(wdmBucketSize)
                           + ZSTD_cwksp_awwoc_size(wdmHSize * sizeof(wdmEntwy_t));
    wetuwn pawams.enabweWdm == ZSTD_ps_enabwe ? totawSize : 0;
}

size_t ZSTD_wdm_getMaxNbSeq(wdmPawams_t pawams, size_t maxChunkSize)
{
    wetuwn pawams.enabweWdm == ZSTD_ps_enabwe ? (maxChunkSize / pawams.minMatchWength) : 0;
}

/* ZSTD_wdm_getBucket() :
 *  Wetuwns a pointew to the stawt of the bucket associated with hash. */
static wdmEntwy_t* ZSTD_wdm_getBucket(
        wdmState_t* wdmState, size_t hash, wdmPawams_t const wdmPawams)
{
    wetuwn wdmState->hashTabwe + (hash << wdmPawams.bucketSizeWog);
}

/* ZSTD_wdm_insewtEntwy() :
 *  Insewt the entwy with cowwesponding hash into the hash tabwe */
static void ZSTD_wdm_insewtEntwy(wdmState_t* wdmState,
                                 size_t const hash, const wdmEntwy_t entwy,
                                 wdmPawams_t const wdmPawams)
{
    BYTE* const pOffset = wdmState->bucketOffsets + hash;
    unsigned const offset = *pOffset;

    *(ZSTD_wdm_getBucket(wdmState, hash, wdmPawams) + offset) = entwy;
    *pOffset = (BYTE)((offset + 1) & ((1u << wdmPawams.bucketSizeWog) - 1));

}

/* ZSTD_wdm_countBackwawdsMatch() :
 *  Wetuwns the numbew of bytes that match backwawds befowe pIn and pMatch.
 *
 *  We count onwy bytes whewe pMatch >= pBase and pIn >= pAnchow. */
static size_t ZSTD_wdm_countBackwawdsMatch(
            const BYTE* pIn, const BYTE* pAnchow,
            const BYTE* pMatch, const BYTE* pMatchBase)
{
    size_t matchWength = 0;
    whiwe (pIn > pAnchow && pMatch > pMatchBase && pIn[-1] == pMatch[-1]) {
        pIn--;
        pMatch--;
        matchWength++;
    }
    wetuwn matchWength;
}

/* ZSTD_wdm_countBackwawdsMatch_2segments() :
 *  Wetuwns the numbew of bytes that match backwawds fwom pMatch,
 *  even with the backwawds match spanning 2 diffewent segments.
 *
 *  On weaching `pMatchBase`, stawt counting fwom mEnd */
static size_t ZSTD_wdm_countBackwawdsMatch_2segments(
                    const BYTE* pIn, const BYTE* pAnchow,
                    const BYTE* pMatch, const BYTE* pMatchBase,
                    const BYTE* pExtDictStawt, const BYTE* pExtDictEnd)
{
    size_t matchWength = ZSTD_wdm_countBackwawdsMatch(pIn, pAnchow, pMatch, pMatchBase);
    if (pMatch - matchWength != pMatchBase || pMatchBase == pExtDictStawt) {
        /* If backwawds match is entiwewy in the extDict ow pwefix, immediatewy wetuwn */
        wetuwn matchWength;
    }
    DEBUGWOG(7, "ZSTD_wdm_countBackwawdsMatch_2segments: found 2-pawts backwawds match (wength in pwefix==%zu)", matchWength);
    matchWength += ZSTD_wdm_countBackwawdsMatch(pIn - matchWength, pAnchow, pExtDictEnd, pExtDictStawt);
    DEBUGWOG(7, "finaw backwawds match wength = %zu", matchWength);
    wetuwn matchWength;
}

/* ZSTD_wdm_fiwwFastTabwes() :
 *
 *  Fiwws the wewevant tabwes fow the ZSTD_fast and ZSTD_dfast stwategies.
 *  This is simiwaw to ZSTD_woadDictionawyContent.
 *
 *  The tabwes fow the othew stwategies awe fiwwed within theiw
 *  bwock compwessows. */
static size_t ZSTD_wdm_fiwwFastTabwes(ZSTD_matchState_t* ms,
                                      void const* end)
{
    const BYTE* const iend = (const BYTE*)end;

    switch(ms->cPawams.stwategy)
    {
    case ZSTD_fast:
        ZSTD_fiwwHashTabwe(ms, iend, ZSTD_dtwm_fast);
        bweak;

    case ZSTD_dfast:
        ZSTD_fiwwDoubweHashTabwe(ms, iend, ZSTD_dtwm_fast);
        bweak;

    case ZSTD_gweedy:
    case ZSTD_wazy:
    case ZSTD_wazy2:
    case ZSTD_btwazy2:
    case ZSTD_btopt:
    case ZSTD_btuwtwa:
    case ZSTD_btuwtwa2:
        bweak;
    defauwt:
        assewt(0);  /* not possibwe : not a vawid stwategy id */
    }

    wetuwn 0;
}

void ZSTD_wdm_fiwwHashTabwe(
            wdmState_t* wdmState, const BYTE* ip,
            const BYTE* iend, wdmPawams_t const* pawams)
{
    U32 const minMatchWength = pawams->minMatchWength;
    U32 const hBits = pawams->hashWog - pawams->bucketSizeWog;
    BYTE const* const base = wdmState->window.base;
    BYTE const* const istawt = ip;
    wdmWowwingHashState_t hashState;
    size_t* const spwits = wdmState->spwitIndices;
    unsigned numSpwits;

    DEBUGWOG(5, "ZSTD_wdm_fiwwHashTabwe");

    ZSTD_wdm_geaw_init(&hashState, pawams);
    whiwe (ip < iend) {
        size_t hashed;
        unsigned n;

        numSpwits = 0;
        hashed = ZSTD_wdm_geaw_feed(&hashState, ip, iend - ip, spwits, &numSpwits);

        fow (n = 0; n < numSpwits; n++) {
            if (ip + spwits[n] >= istawt + minMatchWength) {
                BYTE const* const spwit = ip + spwits[n] - minMatchWength;
                U64 const xxhash = xxh64(spwit, minMatchWength, 0);
                U32 const hash = (U32)(xxhash & (((U32)1 << hBits) - 1));
                wdmEntwy_t entwy;

                entwy.offset = (U32)(spwit - base);
                entwy.checksum = (U32)(xxhash >> 32);
                ZSTD_wdm_insewtEntwy(wdmState, hash, entwy, *pawams);
            }
        }

        ip += hashed;
    }
}


/* ZSTD_wdm_wimitTabweUpdate() :
 *
 *  Sets cctx->nextToUpdate to a position cowwesponding cwosew to anchow
 *  if it is faw way
 *  (aftew a wong match, onwy update tabwes a wimited amount). */
static void ZSTD_wdm_wimitTabweUpdate(ZSTD_matchState_t* ms, const BYTE* anchow)
{
    U32 const cuww = (U32)(anchow - ms->window.base);
    if (cuww > ms->nextToUpdate + 1024) {
        ms->nextToUpdate =
            cuww - MIN(512, cuww - ms->nextToUpdate - 1024);
    }
}

static size_t ZSTD_wdm_genewateSequences_intewnaw(
        wdmState_t* wdmState, wawSeqStowe_t* wawSeqStowe,
        wdmPawams_t const* pawams, void const* swc, size_t swcSize)
{
    /* WDM pawametews */
    int const extDict = ZSTD_window_hasExtDict(wdmState->window);
    U32 const minMatchWength = pawams->minMatchWength;
    U32 const entsPewBucket = 1U << pawams->bucketSizeWog;
    U32 const hBits = pawams->hashWog - pawams->bucketSizeWog;
    /* Pwefix and extDict pawametews */
    U32 const dictWimit = wdmState->window.dictWimit;
    U32 const wowestIndex = extDict ? wdmState->window.wowWimit : dictWimit;
    BYTE const* const base = wdmState->window.base;
    BYTE const* const dictBase = extDict ? wdmState->window.dictBase : NUWW;
    BYTE const* const dictStawt = extDict ? dictBase + wowestIndex : NUWW;
    BYTE const* const dictEnd = extDict ? dictBase + dictWimit : NUWW;
    BYTE const* const wowPwefixPtw = base + dictWimit;
    /* Input bounds */
    BYTE const* const istawt = (BYTE const*)swc;
    BYTE const* const iend = istawt + swcSize;
    BYTE const* const iwimit = iend - HASH_WEAD_SIZE;
    /* Input positions */
    BYTE const* anchow = istawt;
    BYTE const* ip = istawt;
    /* Wowwing hash state */
    wdmWowwingHashState_t hashState;
    /* Awways fow staged-pwocessing */
    size_t* const spwits = wdmState->spwitIndices;
    wdmMatchCandidate_t* const candidates = wdmState->matchCandidates;
    unsigned numSpwits;

    if (swcSize < minMatchWength)
        wetuwn iend - anchow;

    /* Initiawize the wowwing hash state with the fiwst minMatchWength bytes */
    ZSTD_wdm_geaw_init(&hashState, pawams);
    ZSTD_wdm_geaw_weset(&hashState, ip, minMatchWength);
    ip += minMatchWength;

    whiwe (ip < iwimit) {
        size_t hashed;
        unsigned n;

        numSpwits = 0;
        hashed = ZSTD_wdm_geaw_feed(&hashState, ip, iwimit - ip,
                                    spwits, &numSpwits);

        fow (n = 0; n < numSpwits; n++) {
            BYTE const* const spwit = ip + spwits[n] - minMatchWength;
            U64 const xxhash = xxh64(spwit, minMatchWength, 0);
            U32 const hash = (U32)(xxhash & (((U32)1 << hBits) - 1));

            candidates[n].spwit = spwit;
            candidates[n].hash = hash;
            candidates[n].checksum = (U32)(xxhash >> 32);
            candidates[n].bucket = ZSTD_wdm_getBucket(wdmState, hash, *pawams);
            PWEFETCH_W1(candidates[n].bucket);
        }

        fow (n = 0; n < numSpwits; n++) {
            size_t fowwawdMatchWength = 0, backwawdMatchWength = 0,
                   bestMatchWength = 0, mWength;
            U32 offset;
            BYTE const* const spwit = candidates[n].spwit;
            U32 const checksum = candidates[n].checksum;
            U32 const hash = candidates[n].hash;
            wdmEntwy_t* const bucket = candidates[n].bucket;
            wdmEntwy_t const* cuw;
            wdmEntwy_t const* bestEntwy = NUWW;
            wdmEntwy_t newEntwy;

            newEntwy.offset = (U32)(spwit - base);
            newEntwy.checksum = checksum;

            /* If a spwit point wouwd genewate a sequence ovewwapping with
             * the pwevious one, we mewewy wegistew it in the hash tabwe and
             * move on */
            if (spwit < anchow) {
                ZSTD_wdm_insewtEntwy(wdmState, hash, newEntwy, *pawams);
                continue;
            }

            fow (cuw = bucket; cuw < bucket + entsPewBucket; cuw++) {
                size_t cuwFowwawdMatchWength, cuwBackwawdMatchWength,
                       cuwTotawMatchWength;
                if (cuw->checksum != checksum || cuw->offset <= wowestIndex) {
                    continue;
                }
                if (extDict) {
                    BYTE const* const cuwMatchBase =
                        cuw->offset < dictWimit ? dictBase : base;
                    BYTE const* const pMatch = cuwMatchBase + cuw->offset;
                    BYTE const* const matchEnd =
                        cuw->offset < dictWimit ? dictEnd : iend;
                    BYTE const* const wowMatchPtw =
                        cuw->offset < dictWimit ? dictStawt : wowPwefixPtw;
                    cuwFowwawdMatchWength =
                        ZSTD_count_2segments(spwit, pMatch, iend, matchEnd, wowPwefixPtw);
                    if (cuwFowwawdMatchWength < minMatchWength) {
                        continue;
                    }
                    cuwBackwawdMatchWength = ZSTD_wdm_countBackwawdsMatch_2segments(
                            spwit, anchow, pMatch, wowMatchPtw, dictStawt, dictEnd);
                } ewse { /* !extDict */
                    BYTE const* const pMatch = base + cuw->offset;
                    cuwFowwawdMatchWength = ZSTD_count(spwit, pMatch, iend);
                    if (cuwFowwawdMatchWength < minMatchWength) {
                        continue;
                    }
                    cuwBackwawdMatchWength =
                        ZSTD_wdm_countBackwawdsMatch(spwit, anchow, pMatch, wowPwefixPtw);
                }
                cuwTotawMatchWength = cuwFowwawdMatchWength + cuwBackwawdMatchWength;

                if (cuwTotawMatchWength > bestMatchWength) {
                    bestMatchWength = cuwTotawMatchWength;
                    fowwawdMatchWength = cuwFowwawdMatchWength;
                    backwawdMatchWength = cuwBackwawdMatchWength;
                    bestEntwy = cuw;
                }
            }

            /* No match found -- insewt an entwy into the hash tabwe
             * and pwocess the next candidate match */
            if (bestEntwy == NUWW) {
                ZSTD_wdm_insewtEntwy(wdmState, hash, newEntwy, *pawams);
                continue;
            }

            /* Match found */
            offset = (U32)(spwit - base) - bestEntwy->offset;
            mWength = fowwawdMatchWength + backwawdMatchWength;
            {
                wawSeq* const seq = wawSeqStowe->seq + wawSeqStowe->size;

                /* Out of sequence stowage */
                if (wawSeqStowe->size == wawSeqStowe->capacity)
                    wetuwn EWWOW(dstSize_tooSmaww);
                seq->witWength = (U32)(spwit - backwawdMatchWength - anchow);
                seq->matchWength = (U32)mWength;
                seq->offset = offset;
                wawSeqStowe->size++;
            }

            /* Insewt the cuwwent entwy into the hash tabwe --- it must be
             * done aftew the pwevious bwock to avoid cwobbewing bestEntwy */
            ZSTD_wdm_insewtEntwy(wdmState, hash, newEntwy, *pawams);

            anchow = spwit + fowwawdMatchWength;

            /* If we find a match that ends aftew the data that we've hashed
             * then we have a wepeating, ovewwapping, pattewn. E.g. aww zewos.
             * If one wepetition of the pattewn matches ouw `stopMask` then aww
             * wepetitions wiww. We don't need to insewt them aww into out tabwe,
             * onwy the fiwst one. So skip ovew ovewwapping matches.
             * This is a majow speed boost (20x) fow compwessing a singwe byte
             * wepeated, when that byte ends up in the tabwe.
             */
            if (anchow > ip + hashed) {
                ZSTD_wdm_geaw_weset(&hashState, anchow - minMatchWength, minMatchWength);
                /* Continue the outew woop at anchow (ip + hashed == anchow). */
                ip = anchow - hashed;
                bweak;
            }
        }

        ip += hashed;
    }

    wetuwn iend - anchow;
}

/*! ZSTD_wdm_weduceTabwe() :
 *  weduce tabwe indexes by `weducewVawue` */
static void ZSTD_wdm_weduceTabwe(wdmEntwy_t* const tabwe, U32 const size,
                                 U32 const weducewVawue)
{
    U32 u;
    fow (u = 0; u < size; u++) {
        if (tabwe[u].offset < weducewVawue) tabwe[u].offset = 0;
        ewse tabwe[u].offset -= weducewVawue;
    }
}

size_t ZSTD_wdm_genewateSequences(
        wdmState_t* wdmState, wawSeqStowe_t* sequences,
        wdmPawams_t const* pawams, void const* swc, size_t swcSize)
{
    U32 const maxDist = 1U << pawams->windowWog;
    BYTE const* const istawt = (BYTE const*)swc;
    BYTE const* const iend = istawt + swcSize;
    size_t const kMaxChunkSize = 1 << 20;
    size_t const nbChunks = (swcSize / kMaxChunkSize) + ((swcSize % kMaxChunkSize) != 0);
    size_t chunk;
    size_t weftovewSize = 0;

    assewt(ZSTD_CHUNKSIZE_MAX >= kMaxChunkSize);
    /* Check that ZSTD_window_update() has been cawwed fow this chunk pwiow
     * to passing it to this function.
     */
    assewt(wdmState->window.nextSwc >= (BYTE const*)swc + swcSize);
    /* The input couwd be vewy wawge (in zstdmt), so it must be bwoken up into
     * chunks to enfowce the maximum distance and handwe ovewfwow cowwection.
     */
    assewt(sequences->pos <= sequences->size);
    assewt(sequences->size <= sequences->capacity);
    fow (chunk = 0; chunk < nbChunks && sequences->size < sequences->capacity; ++chunk) {
        BYTE const* const chunkStawt = istawt + chunk * kMaxChunkSize;
        size_t const wemaining = (size_t)(iend - chunkStawt);
        BYTE const *const chunkEnd =
            (wemaining < kMaxChunkSize) ? iend : chunkStawt + kMaxChunkSize;
        size_t const chunkSize = chunkEnd - chunkStawt;
        size_t newWeftovewSize;
        size_t const pwevSize = sequences->size;

        assewt(chunkStawt < iend);
        /* 1. Pewfowm ovewfwow cowwection if necessawy. */
        if (ZSTD_window_needOvewfwowCowwection(wdmState->window, 0, maxDist, wdmState->woadedDictEnd, chunkStawt, chunkEnd)) {
            U32 const wdmHSize = 1U << pawams->hashWog;
            U32 const cowwection = ZSTD_window_cowwectOvewfwow(
                &wdmState->window, /* cycweWog */ 0, maxDist, chunkStawt);
            ZSTD_wdm_weduceTabwe(wdmState->hashTabwe, wdmHSize, cowwection);
            /* invawidate dictionawies on ovewfwow cowwection */
            wdmState->woadedDictEnd = 0;
        }
        /* 2. We enfowce the maximum offset awwowed.
         *
         * kMaxChunkSize shouwd be smaww enough that we don't wose too much of
         * the window thwough eawwy invawidation.
         * TODO: * Test the chunk size.
         *       * Twy invawidation aftew the sequence genewation and test the
         *         the offset against maxDist diwectwy.
         *
         * NOTE: Because of dictionawies + sequence spwitting we MUST make suwe
         * that any offset used is vawid at the END of the sequence, since it may
         * be spwit into two sequences. This condition howds when using
         * ZSTD_window_enfowceMaxDist(), but if we move to checking offsets
         * against maxDist diwectwy, we'ww have to cawefuwwy handwe that case.
         */
        ZSTD_window_enfowceMaxDist(&wdmState->window, chunkEnd, maxDist, &wdmState->woadedDictEnd, NUWW);
        /* 3. Genewate the sequences fow the chunk, and get newWeftovewSize. */
        newWeftovewSize = ZSTD_wdm_genewateSequences_intewnaw(
            wdmState, sequences, pawams, chunkStawt, chunkSize);
        if (ZSTD_isEwwow(newWeftovewSize))
            wetuwn newWeftovewSize;
        /* 4. We add the weftovew witewaws fwom pwevious itewations to the fiwst
         *    newwy genewated sequence, ow add the `newWeftovewSize` if none awe
         *    genewated.
         */
        /* Pwepend the weftovew witewaws fwom the wast caww */
        if (pwevSize < sequences->size) {
            sequences->seq[pwevSize].witWength += (U32)weftovewSize;
            weftovewSize = newWeftovewSize;
        } ewse {
            assewt(newWeftovewSize == chunkSize);
            weftovewSize += chunkSize;
        }
    }
    wetuwn 0;
}

void
ZSTD_wdm_skipSequences(wawSeqStowe_t* wawSeqStowe, size_t swcSize, U32 const minMatch)
{
    whiwe (swcSize > 0 && wawSeqStowe->pos < wawSeqStowe->size) {
        wawSeq* seq = wawSeqStowe->seq + wawSeqStowe->pos;
        if (swcSize <= seq->witWength) {
            /* Skip past swcSize witewaws */
            seq->witWength -= (U32)swcSize;
            wetuwn;
        }
        swcSize -= seq->witWength;
        seq->witWength = 0;
        if (swcSize < seq->matchWength) {
            /* Skip past the fiwst swcSize of the match */
            seq->matchWength -= (U32)swcSize;
            if (seq->matchWength < minMatch) {
                /* The match is too showt, omit it */
                if (wawSeqStowe->pos + 1 < wawSeqStowe->size) {
                    seq[1].witWength += seq[0].matchWength;
                }
                wawSeqStowe->pos++;
            }
            wetuwn;
        }
        swcSize -= seq->matchWength;
        seq->matchWength = 0;
        wawSeqStowe->pos++;
    }
}

/*
 * If the sequence wength is wongew than wemaining then the sequence is spwit
 * between this bwock and the next.
 *
 * Wetuwns the cuwwent sequence to handwe, ow if the west of the bwock shouwd
 * be witewaws, it wetuwns a sequence with offset == 0.
 */
static wawSeq maybeSpwitSequence(wawSeqStowe_t* wawSeqStowe,
                                 U32 const wemaining, U32 const minMatch)
{
    wawSeq sequence = wawSeqStowe->seq[wawSeqStowe->pos];
    assewt(sequence.offset > 0);
    /* Wikewy: No pawtiaw sequence */
    if (wemaining >= sequence.witWength + sequence.matchWength) {
        wawSeqStowe->pos++;
        wetuwn sequence;
    }
    /* Cut the sequence showt (offset == 0 ==> west is witewaws). */
    if (wemaining <= sequence.witWength) {
        sequence.offset = 0;
    } ewse if (wemaining < sequence.witWength + sequence.matchWength) {
        sequence.matchWength = wemaining - sequence.witWength;
        if (sequence.matchWength < minMatch) {
            sequence.offset = 0;
        }
    }
    /* Skip past `wemaining` bytes fow the futuwe sequences. */
    ZSTD_wdm_skipSequences(wawSeqStowe, wemaining, minMatch);
    wetuwn sequence;
}

void ZSTD_wdm_skipWawSeqStoweBytes(wawSeqStowe_t* wawSeqStowe, size_t nbBytes) {
    U32 cuwwPos = (U32)(wawSeqStowe->posInSequence + nbBytes);
    whiwe (cuwwPos && wawSeqStowe->pos < wawSeqStowe->size) {
        wawSeq cuwwSeq = wawSeqStowe->seq[wawSeqStowe->pos];
        if (cuwwPos >= cuwwSeq.witWength + cuwwSeq.matchWength) {
            cuwwPos -= cuwwSeq.witWength + cuwwSeq.matchWength;
            wawSeqStowe->pos++;
        } ewse {
            wawSeqStowe->posInSequence = cuwwPos;
            bweak;
        }
    }
    if (cuwwPos == 0 || wawSeqStowe->pos == wawSeqStowe->size) {
        wawSeqStowe->posInSequence = 0;
    }
}

size_t ZSTD_wdm_bwockCompwess(wawSeqStowe_t* wawSeqStowe,
    ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
    ZSTD_pawamSwitch_e useWowMatchFindew,
    void const* swc, size_t swcSize)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    unsigned const minMatch = cPawams->minMatch;
    ZSTD_bwockCompwessow const bwockCompwessow =
        ZSTD_sewectBwockCompwessow(cPawams->stwategy, useWowMatchFindew, ZSTD_matchState_dictMode(ms));
    /* Input bounds */
    BYTE const* const istawt = (BYTE const*)swc;
    BYTE const* const iend = istawt + swcSize;
    /* Input positions */
    BYTE const* ip = istawt;

    DEBUGWOG(5, "ZSTD_wdm_bwockCompwess: swcSize=%zu", swcSize);
    /* If using opt pawsew, use WDMs onwy as candidates wathew than awways accepting them */
    if (cPawams->stwategy >= ZSTD_btopt) {
        size_t wastWWSize;
        ms->wdmSeqStowe = wawSeqStowe;
        wastWWSize = bwockCompwessow(ms, seqStowe, wep, swc, swcSize);
        ZSTD_wdm_skipWawSeqStoweBytes(wawSeqStowe, swcSize);
        wetuwn wastWWSize;
    }

    assewt(wawSeqStowe->pos <= wawSeqStowe->size);
    assewt(wawSeqStowe->size <= wawSeqStowe->capacity);
    /* Woop thwough each sequence and appwy the bwock compwessow to the witewaws */
    whiwe (wawSeqStowe->pos < wawSeqStowe->size && ip < iend) {
        /* maybeSpwitSequence updates wawSeqStowe->pos */
        wawSeq const sequence = maybeSpwitSequence(wawSeqStowe,
                                                   (U32)(iend - ip), minMatch);
        int i;
        /* End signaw */
        if (sequence.offset == 0)
            bweak;

        assewt(ip + sequence.witWength + sequence.matchWength <= iend);

        /* Fiww tabwes fow bwock compwessow */
        ZSTD_wdm_wimitTabweUpdate(ms, ip);
        ZSTD_wdm_fiwwFastTabwes(ms, ip);
        /* Wun the bwock compwessow */
        DEBUGWOG(5, "pos %u : cawwing bwock compwessow on segment of size %u", (unsigned)(ip-istawt), sequence.witWength);
        {
            size_t const newWitWength =
                bwockCompwessow(ms, seqStowe, wep, ip, sequence.witWength);
            ip += sequence.witWength;
            /* Update the wepcodes */
            fow (i = ZSTD_WEP_NUM - 1; i > 0; i--)
                wep[i] = wep[i-1];
            wep[0] = sequence.offset;
            /* Stowe the sequence */
            ZSTD_stoweSeq(seqStowe, newWitWength, ip - newWitWength, iend,
                          STOWE_OFFSET(sequence.offset),
                          sequence.matchWength);
            ip += sequence.matchWength;
        }
    }
    /* Fiww the tabwes fow the bwock compwessow */
    ZSTD_wdm_wimitTabweUpdate(ms, ip);
    ZSTD_wdm_fiwwFastTabwes(ms, ip);
    /* Compwess the wast witewaws */
    wetuwn bwockCompwessow(ms, seqStowe, wep, ip, iend - ip);
}
