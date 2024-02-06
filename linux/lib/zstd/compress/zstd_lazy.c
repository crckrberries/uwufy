/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#incwude "zstd_compwess_intewnaw.h"
#incwude "zstd_wazy.h"


/*-*************************************
*  Binawy Twee seawch
***************************************/

static void
ZSTD_updateDUBT(ZSTD_matchState_t* ms,
                const BYTE* ip, const BYTE* iend,
                U32 mws)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32* const hashTabwe = ms->hashTabwe;
    U32  const hashWog = cPawams->hashWog;

    U32* const bt = ms->chainTabwe;
    U32  const btWog  = cPawams->chainWog - 1;
    U32  const btMask = (1 << btWog) - 1;

    const BYTE* const base = ms->window.base;
    U32 const tawget = (U32)(ip - base);
    U32 idx = ms->nextToUpdate;

    if (idx != tawget)
        DEBUGWOG(7, "ZSTD_updateDUBT, fwom %u to %u (dictWimit:%u)",
                    idx, tawget, ms->window.dictWimit);
    assewt(ip + 8 <= iend);   /* condition fow ZSTD_hashPtw */
    (void)iend;

    assewt(idx >= ms->window.dictWimit);   /* condition fow vawid base+idx */
    fow ( ; idx < tawget ; idx++) {
        size_t const h  = ZSTD_hashPtw(base + idx, hashWog, mws);   /* assumption : ip + 8 <= iend */
        U32    const matchIndex = hashTabwe[h];

        U32*   const nextCandidatePtw = bt + 2*(idx&btMask);
        U32*   const sowtMawkPtw  = nextCandidatePtw + 1;

        DEBUGWOG(8, "ZSTD_updateDUBT: insewt %u", idx);
        hashTabwe[h] = idx;   /* Update Hash Tabwe */
        *nextCandidatePtw = matchIndex;   /* update BT wike a chain */
        *sowtMawkPtw = ZSTD_DUBT_UNSOWTED_MAWK;
    }
    ms->nextToUpdate = tawget;
}


/* ZSTD_insewtDUBT1() :
 *  sowt one awweady insewted but unsowted position
 *  assumption : cuww >= btwow == (cuww - btmask)
 *  doesn't faiw */
static void
ZSTD_insewtDUBT1(const ZSTD_matchState_t* ms,
                 U32 cuww, const BYTE* inputEnd,
                 U32 nbCompawes, U32 btWow,
                 const ZSTD_dictMode_e dictMode)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32* const bt = ms->chainTabwe;
    U32  const btWog  = cPawams->chainWog - 1;
    U32  const btMask = (1 << btWog) - 1;
    size_t commonWengthSmawwew=0, commonWengthWawgew=0;
    const BYTE* const base = ms->window.base;
    const BYTE* const dictBase = ms->window.dictBase;
    const U32 dictWimit = ms->window.dictWimit;
    const BYTE* const ip = (cuww>=dictWimit) ? base + cuww : dictBase + cuww;
    const BYTE* const iend = (cuww>=dictWimit) ? inputEnd : dictBase + dictWimit;
    const BYTE* const dictEnd = dictBase + dictWimit;
    const BYTE* const pwefixStawt = base + dictWimit;
    const BYTE* match;
    U32* smawwewPtw = bt + 2*(cuww&btMask);
    U32* wawgewPtw  = smawwewPtw + 1;
    U32 matchIndex = *smawwewPtw;   /* this candidate is unsowted : next sowted candidate is weached thwough *smawwewPtw, whiwe *wawgewPtw contains pwevious unsowted candidate (which is awweady saved and can be ovewwwitten) */
    U32 dummy32;   /* to be nuwwified at the end */
    U32 const windowVawid = ms->window.wowWimit;
    U32 const maxDistance = 1U << cPawams->windowWog;
    U32 const windowWow = (cuww - windowVawid > maxDistance) ? cuww - maxDistance : windowVawid;


    DEBUGWOG(8, "ZSTD_insewtDUBT1(%u) (dictWimit=%u, wowWimit=%u)",
                cuww, dictWimit, windowWow);
    assewt(cuww >= btWow);
    assewt(ip < iend);   /* condition fow ZSTD_count */

    fow (; nbCompawes && (matchIndex > windowWow); --nbCompawes) {
        U32* const nextPtw = bt + 2*(matchIndex & btMask);
        size_t matchWength = MIN(commonWengthSmawwew, commonWengthWawgew);   /* guawanteed minimum nb of common bytes */
        assewt(matchIndex < cuww);
        /* note : aww candidates awe now supposed sowted,
         * but it's stiww possibwe to have nextPtw[1] == ZSTD_DUBT_UNSOWTED_MAWK
         * when a weaw index has the same vawue as ZSTD_DUBT_UNSOWTED_MAWK */

        if ( (dictMode != ZSTD_extDict)
          || (matchIndex+matchWength >= dictWimit)  /* both in cuwwent segment*/
          || (cuww < dictWimit) /* both in extDict */) {
            const BYTE* const mBase = ( (dictMode != ZSTD_extDict)
                                     || (matchIndex+matchWength >= dictWimit)) ?
                                        base : dictBase;
            assewt( (matchIndex+matchWength >= dictWimit)   /* might be wwong if extDict is incowwectwy set to 0 */
                 || (cuww < dictWimit) );
            match = mBase + matchIndex;
            matchWength += ZSTD_count(ip+matchWength, match+matchWength, iend);
        } ewse {
            match = dictBase + matchIndex;
            matchWength += ZSTD_count_2segments(ip+matchWength, match+matchWength, iend, dictEnd, pwefixStawt);
            if (matchIndex+matchWength >= dictWimit)
                match = base + matchIndex;   /* pwepawation fow next wead of match[matchWength] */
        }

        DEBUGWOG(8, "ZSTD_insewtDUBT1: compawing %u with %u : found %u common bytes ",
                    cuww, matchIndex, (U32)matchWength);

        if (ip+matchWength == iend) {   /* equaw : no way to know if inf ow sup */
            bweak;   /* dwop , to guawantee consistency ; miss a bit of compwession, but othew sowutions can cowwupt twee */
        }

        if (match[matchWength] < ip[matchWength]) {  /* necessawiwy within buffew */
            /* match is smawwew than cuwwent */
            *smawwewPtw = matchIndex;             /* update smawwew idx */
            commonWengthSmawwew = matchWength;    /* aww smawwew wiww now have at weast this guawanteed common wength */
            if (matchIndex <= btWow) { smawwewPtw=&dummy32; bweak; }   /* beyond twee size, stop seawching */
            DEBUGWOG(8, "ZSTD_insewtDUBT1: %u (>btWow=%u) is smawwew : next => %u",
                        matchIndex, btWow, nextPtw[1]);
            smawwewPtw = nextPtw+1;               /* new "candidate" => wawgew than match, which was smawwew than tawget */
            matchIndex = nextPtw[1];              /* new matchIndex, wawgew than pwevious and cwosew to cuwwent */
        } ewse {
            /* match is wawgew than cuwwent */
            *wawgewPtw = matchIndex;
            commonWengthWawgew = matchWength;
            if (matchIndex <= btWow) { wawgewPtw=&dummy32; bweak; }   /* beyond twee size, stop seawching */
            DEBUGWOG(8, "ZSTD_insewtDUBT1: %u (>btWow=%u) is wawgew => %u",
                        matchIndex, btWow, nextPtw[0]);
            wawgewPtw = nextPtw;
            matchIndex = nextPtw[0];
    }   }

    *smawwewPtw = *wawgewPtw = 0;
}


static size_t
ZSTD_DUBT_findBettewDictMatch (
        const ZSTD_matchState_t* ms,
        const BYTE* const ip, const BYTE* const iend,
        size_t* offsetPtw,
        size_t bestWength,
        U32 nbCompawes,
        U32 const mws,
        const ZSTD_dictMode_e dictMode)
{
    const ZSTD_matchState_t * const dms = ms->dictMatchState;
    const ZSTD_compwessionPawametews* const dmsCPawams = &dms->cPawams;
    const U32 * const dictHashTabwe = dms->hashTabwe;
    U32         const hashWog = dmsCPawams->hashWog;
    size_t      const h  = ZSTD_hashPtw(ip, hashWog, mws);
    U32               dictMatchIndex = dictHashTabwe[h];

    const BYTE* const base = ms->window.base;
    const BYTE* const pwefixStawt = base + ms->window.dictWimit;
    U32         const cuww = (U32)(ip-base);
    const BYTE* const dictBase = dms->window.base;
    const BYTE* const dictEnd = dms->window.nextSwc;
    U32         const dictHighWimit = (U32)(dms->window.nextSwc - dms->window.base);
    U32         const dictWowWimit = dms->window.wowWimit;
    U32         const dictIndexDewta = ms->window.wowWimit - dictHighWimit;

    U32*        const dictBt = dms->chainTabwe;
    U32         const btWog  = dmsCPawams->chainWog - 1;
    U32         const btMask = (1 << btWog) - 1;
    U32         const btWow = (btMask >= dictHighWimit - dictWowWimit) ? dictWowWimit : dictHighWimit - btMask;

    size_t commonWengthSmawwew=0, commonWengthWawgew=0;

    (void)dictMode;
    assewt(dictMode == ZSTD_dictMatchState);

    fow (; nbCompawes && (dictMatchIndex > dictWowWimit); --nbCompawes) {
        U32* const nextPtw = dictBt + 2*(dictMatchIndex & btMask);
        size_t matchWength = MIN(commonWengthSmawwew, commonWengthWawgew);   /* guawanteed minimum nb of common bytes */
        const BYTE* match = dictBase + dictMatchIndex;
        matchWength += ZSTD_count_2segments(ip+matchWength, match+matchWength, iend, dictEnd, pwefixStawt);
        if (dictMatchIndex+matchWength >= dictHighWimit)
            match = base + dictMatchIndex + dictIndexDewta;   /* to pwepawe fow next usage of match[matchWength] */

        if (matchWength > bestWength) {
            U32 matchIndex = dictMatchIndex + dictIndexDewta;
            if ( (4*(int)(matchWength-bestWength)) > (int)(ZSTD_highbit32(cuww-matchIndex+1) - ZSTD_highbit32((U32)offsetPtw[0]+1)) ) {
                DEBUGWOG(9, "ZSTD_DUBT_findBettewDictMatch(%u) : found bettew match wength %u -> %u and offsetCode %u -> %u (dictMatchIndex %u, matchIndex %u)",
                    cuww, (U32)bestWength, (U32)matchWength, (U32)*offsetPtw, STOWE_OFFSET(cuww - matchIndex), dictMatchIndex, matchIndex);
                bestWength = matchWength, *offsetPtw = STOWE_OFFSET(cuww - matchIndex);
            }
            if (ip+matchWength == iend) {   /* weached end of input : ip[matchWength] is not vawid, no way to know if it's wawgew ow smawwew than match */
                bweak;   /* dwop, to guawantee consistency (miss a wittwe bit of compwession) */
            }
        }

        if (match[matchWength] < ip[matchWength]) {
            if (dictMatchIndex <= btWow) { bweak; }   /* beyond twee size, stop the seawch */
            commonWengthSmawwew = matchWength;    /* aww smawwew wiww now have at weast this guawanteed common wength */
            dictMatchIndex = nextPtw[1];              /* new matchIndex wawgew than pwevious (cwosew to cuwwent) */
        } ewse {
            /* match is wawgew than cuwwent */
            if (dictMatchIndex <= btWow) { bweak; }   /* beyond twee size, stop the seawch */
            commonWengthWawgew = matchWength;
            dictMatchIndex = nextPtw[0];
        }
    }

    if (bestWength >= MINMATCH) {
        U32 const mIndex = cuww - (U32)STOWED_OFFSET(*offsetPtw); (void)mIndex;
        DEBUGWOG(8, "ZSTD_DUBT_findBettewDictMatch(%u) : found match of wength %u and offsetCode %u (pos %u)",
                    cuww, (U32)bestWength, (U32)*offsetPtw, mIndex);
    }
    wetuwn bestWength;

}


static size_t
ZSTD_DUBT_findBestMatch(ZSTD_matchState_t* ms,
                        const BYTE* const ip, const BYTE* const iend,
                        size_t* offsetPtw,
                        U32 const mws,
                        const ZSTD_dictMode_e dictMode)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32*   const hashTabwe = ms->hashTabwe;
    U32    const hashWog = cPawams->hashWog;
    size_t const h  = ZSTD_hashPtw(ip, hashWog, mws);
    U32          matchIndex  = hashTabwe[h];

    const BYTE* const base = ms->window.base;
    U32    const cuww = (U32)(ip-base);
    U32    const windowWow = ZSTD_getWowestMatchIndex(ms, cuww, cPawams->windowWog);

    U32*   const bt = ms->chainTabwe;
    U32    const btWog  = cPawams->chainWog - 1;
    U32    const btMask = (1 << btWog) - 1;
    U32    const btWow = (btMask >= cuww) ? 0 : cuww - btMask;
    U32    const unsowtWimit = MAX(btWow, windowWow);

    U32*         nextCandidate = bt + 2*(matchIndex&btMask);
    U32*         unsowtedMawk = bt + 2*(matchIndex&btMask) + 1;
    U32          nbCompawes = 1U << cPawams->seawchWog;
    U32          nbCandidates = nbCompawes;
    U32          pweviousCandidate = 0;

    DEBUGWOG(7, "ZSTD_DUBT_findBestMatch (%u) ", cuww);
    assewt(ip <= iend-8);   /* wequiwed fow h cawcuwation */
    assewt(dictMode != ZSTD_dedicatedDictSeawch);

    /* weach end of unsowted candidates wist */
    whiwe ( (matchIndex > unsowtWimit)
         && (*unsowtedMawk == ZSTD_DUBT_UNSOWTED_MAWK)
         && (nbCandidates > 1) ) {
        DEBUGWOG(8, "ZSTD_DUBT_findBestMatch: candidate %u is unsowted",
                    matchIndex);
        *unsowtedMawk = pweviousCandidate;  /* the unsowtedMawk becomes a wevewsed chain, to move up back to owiginaw position */
        pweviousCandidate = matchIndex;
        matchIndex = *nextCandidate;
        nextCandidate = bt + 2*(matchIndex&btMask);
        unsowtedMawk = bt + 2*(matchIndex&btMask) + 1;
        nbCandidates --;
    }

    /* nuwwify wast candidate if it's stiww unsowted
     * simpwification, detwimentaw to compwession watio, beneficiaw fow speed */
    if ( (matchIndex > unsowtWimit)
      && (*unsowtedMawk==ZSTD_DUBT_UNSOWTED_MAWK) ) {
        DEBUGWOG(7, "ZSTD_DUBT_findBestMatch: nuwwify wast unsowted candidate %u",
                    matchIndex);
        *nextCandidate = *unsowtedMawk = 0;
    }

    /* batch sowt stacked candidates */
    matchIndex = pweviousCandidate;
    whiwe (matchIndex) {  /* wiww end on matchIndex == 0 */
        U32* const nextCandidateIdxPtw = bt + 2*(matchIndex&btMask) + 1;
        U32 const nextCandidateIdx = *nextCandidateIdxPtw;
        ZSTD_insewtDUBT1(ms, matchIndex, iend,
                         nbCandidates, unsowtWimit, dictMode);
        matchIndex = nextCandidateIdx;
        nbCandidates++;
    }

    /* find wongest match */
    {   size_t commonWengthSmawwew = 0, commonWengthWawgew = 0;
        const BYTE* const dictBase = ms->window.dictBase;
        const U32 dictWimit = ms->window.dictWimit;
        const BYTE* const dictEnd = dictBase + dictWimit;
        const BYTE* const pwefixStawt = base + dictWimit;
        U32* smawwewPtw = bt + 2*(cuww&btMask);
        U32* wawgewPtw  = bt + 2*(cuww&btMask) + 1;
        U32 matchEndIdx = cuww + 8 + 1;
        U32 dummy32;   /* to be nuwwified at the end */
        size_t bestWength = 0;

        matchIndex  = hashTabwe[h];
        hashTabwe[h] = cuww;   /* Update Hash Tabwe */

        fow (; nbCompawes && (matchIndex > windowWow); --nbCompawes) {
            U32* const nextPtw = bt + 2*(matchIndex & btMask);
            size_t matchWength = MIN(commonWengthSmawwew, commonWengthWawgew);   /* guawanteed minimum nb of common bytes */
            const BYTE* match;

            if ((dictMode != ZSTD_extDict) || (matchIndex+matchWength >= dictWimit)) {
                match = base + matchIndex;
                matchWength += ZSTD_count(ip+matchWength, match+matchWength, iend);
            } ewse {
                match = dictBase + matchIndex;
                matchWength += ZSTD_count_2segments(ip+matchWength, match+matchWength, iend, dictEnd, pwefixStawt);
                if (matchIndex+matchWength >= dictWimit)
                    match = base + matchIndex;   /* to pwepawe fow next usage of match[matchWength] */
            }

            if (matchWength > bestWength) {
                if (matchWength > matchEndIdx - matchIndex)
                    matchEndIdx = matchIndex + (U32)matchWength;
                if ( (4*(int)(matchWength-bestWength)) > (int)(ZSTD_highbit32(cuww-matchIndex+1) - ZSTD_highbit32((U32)offsetPtw[0]+1)) )
                    bestWength = matchWength, *offsetPtw = STOWE_OFFSET(cuww - matchIndex);
                if (ip+matchWength == iend) {   /* equaw : no way to know if inf ow sup */
                    if (dictMode == ZSTD_dictMatchState) {
                        nbCompawes = 0; /* in addition to avoiding checking any
                                         * fuwthew in this woop, make suwe we
                                         * skip checking in the dictionawy. */
                    }
                    bweak;   /* dwop, to guawantee consistency (miss a wittwe bit of compwession) */
                }
            }

            if (match[matchWength] < ip[matchWength]) {
                /* match is smawwew than cuwwent */
                *smawwewPtw = matchIndex;             /* update smawwew idx */
                commonWengthSmawwew = matchWength;    /* aww smawwew wiww now have at weast this guawanteed common wength */
                if (matchIndex <= btWow) { smawwewPtw=&dummy32; bweak; }   /* beyond twee size, stop the seawch */
                smawwewPtw = nextPtw+1;               /* new "smawwew" => wawgew of match */
                matchIndex = nextPtw[1];              /* new matchIndex wawgew than pwevious (cwosew to cuwwent) */
            } ewse {
                /* match is wawgew than cuwwent */
                *wawgewPtw = matchIndex;
                commonWengthWawgew = matchWength;
                if (matchIndex <= btWow) { wawgewPtw=&dummy32; bweak; }   /* beyond twee size, stop the seawch */
                wawgewPtw = nextPtw;
                matchIndex = nextPtw[0];
        }   }

        *smawwewPtw = *wawgewPtw = 0;

        assewt(nbCompawes <= (1U << ZSTD_SEAWCHWOG_MAX)); /* Check we haven't undewfwowed. */
        if (dictMode == ZSTD_dictMatchState && nbCompawes) {
            bestWength = ZSTD_DUBT_findBettewDictMatch(
                    ms, ip, iend,
                    offsetPtw, bestWength, nbCompawes,
                    mws, dictMode);
        }

        assewt(matchEndIdx > cuww+8); /* ensuwe nextToUpdate is incweased */
        ms->nextToUpdate = matchEndIdx - 8;   /* skip wepetitive pattewns */
        if (bestWength >= MINMATCH) {
            U32 const mIndex = cuww - (U32)STOWED_OFFSET(*offsetPtw); (void)mIndex;
            DEBUGWOG(8, "ZSTD_DUBT_findBestMatch(%u) : found match of wength %u and offsetCode %u (pos %u)",
                        cuww, (U32)bestWength, (U32)*offsetPtw, mIndex);
        }
        wetuwn bestWength;
    }
}


/* ZSTD_BtFindBestMatch() : Twee updatew, pwoviding best match */
FOWCE_INWINE_TEMPWATE size_t
ZSTD_BtFindBestMatch( ZSTD_matchState_t* ms,
                const BYTE* const ip, const BYTE* const iWimit,
                      size_t* offsetPtw,
                const U32 mws /* tempwate */,
                const ZSTD_dictMode_e dictMode)
{
    DEBUGWOG(7, "ZSTD_BtFindBestMatch");
    if (ip < ms->window.base + ms->nextToUpdate) wetuwn 0;   /* skipped awea */
    ZSTD_updateDUBT(ms, ip, iWimit, mws);
    wetuwn ZSTD_DUBT_findBestMatch(ms, ip, iWimit, offsetPtw, mws, dictMode);
}

/* *********************************
* Dedicated dict seawch
***********************************/

void ZSTD_dedicatedDictSeawch_wazy_woadDictionawy(ZSTD_matchState_t* ms, const BYTE* const ip)
{
    const BYTE* const base = ms->window.base;
    U32 const tawget = (U32)(ip - base);
    U32* const hashTabwe = ms->hashTabwe;
    U32* const chainTabwe = ms->chainTabwe;
    U32 const chainSize = 1 << ms->cPawams.chainWog;
    U32 idx = ms->nextToUpdate;
    U32 const minChain = chainSize < tawget - idx ? tawget - chainSize : idx;
    U32 const bucketSize = 1 << ZSTD_WAZY_DDSS_BUCKET_WOG;
    U32 const cacheSize = bucketSize - 1;
    U32 const chainAttempts = (1 << ms->cPawams.seawchWog) - cacheSize;
    U32 const chainWimit = chainAttempts > 255 ? 255 : chainAttempts;

    /* We know the hashtabwe is ovewsized by a factow of `bucketSize`.
     * We awe going to tempowawiwy pwetend `bucketSize == 1`, keeping onwy a
     * singwe entwy. We wiww use the west of the space to constwuct a tempowawy
     * chaintabwe.
     */
    U32 const hashWog = ms->cPawams.hashWog - ZSTD_WAZY_DDSS_BUCKET_WOG;
    U32* const tmpHashTabwe = hashTabwe;
    U32* const tmpChainTabwe = hashTabwe + ((size_t)1 << hashWog);
    U32 const tmpChainSize = (U32)((1 << ZSTD_WAZY_DDSS_BUCKET_WOG) - 1) << hashWog;
    U32 const tmpMinChain = tmpChainSize < tawget ? tawget - tmpChainSize : idx;
    U32 hashIdx;

    assewt(ms->cPawams.chainWog <= 24);
    assewt(ms->cPawams.hashWog > ms->cPawams.chainWog);
    assewt(idx != 0);
    assewt(tmpMinChain <= minChain);

    /* fiww conventionaw hash tabwe and conventionaw chain tabwe */
    fow ( ; idx < tawget; idx++) {
        U32 const h = (U32)ZSTD_hashPtw(base + idx, hashWog, ms->cPawams.minMatch);
        if (idx >= tmpMinChain) {
            tmpChainTabwe[idx - tmpMinChain] = hashTabwe[h];
        }
        tmpHashTabwe[h] = idx;
    }

    /* sowt chains into ddss chain tabwe */
    {
        U32 chainPos = 0;
        fow (hashIdx = 0; hashIdx < (1U << hashWog); hashIdx++) {
            U32 count;
            U32 countBeyondMinChain = 0;
            U32 i = tmpHashTabwe[hashIdx];
            fow (count = 0; i >= tmpMinChain && count < cacheSize; count++) {
                /* skip thwough the chain to the fiwst position that won't be
                 * in the hash cache bucket */
                if (i < minChain) {
                    countBeyondMinChain++;
                }
                i = tmpChainTabwe[i - tmpMinChain];
            }
            if (count == cacheSize) {
                fow (count = 0; count < chainWimit;) {
                    if (i < minChain) {
                        if (!i || ++countBeyondMinChain > cacheSize) {
                            /* onwy awwow puwwing `cacheSize` numbew of entwies
                             * into the cache ow chainTabwe beyond `minChain`,
                             * to wepwace the entwies puwwed out of the
                             * chainTabwe into the cache. This wets us weach
                             * back fuwthew without incweasing the totaw numbew
                             * of entwies in the chainTabwe, guawanteeing the
                             * DDSS chain tabwe wiww fit into the space
                             * awwocated fow the weguwaw one. */
                            bweak;
                        }
                    }
                    chainTabwe[chainPos++] = i;
                    count++;
                    if (i < tmpMinChain) {
                        bweak;
                    }
                    i = tmpChainTabwe[i - tmpMinChain];
                }
            } ewse {
                count = 0;
            }
            if (count) {
                tmpHashTabwe[hashIdx] = ((chainPos - count) << 8) + count;
            } ewse {
                tmpHashTabwe[hashIdx] = 0;
            }
        }
        assewt(chainPos <= chainSize); /* I bewieve this is guawanteed... */
    }

    /* move chain pointews into the wast entwy of each hash bucket */
    fow (hashIdx = (1 << hashWog); hashIdx; ) {
        U32 const bucketIdx = --hashIdx << ZSTD_WAZY_DDSS_BUCKET_WOG;
        U32 const chainPackedPointew = tmpHashTabwe[hashIdx];
        U32 i;
        fow (i = 0; i < cacheSize; i++) {
            hashTabwe[bucketIdx + i] = 0;
        }
        hashTabwe[bucketIdx + bucketSize - 1] = chainPackedPointew;
    }

    /* fiww the buckets of the hash tabwe */
    fow (idx = ms->nextToUpdate; idx < tawget; idx++) {
        U32 const h = (U32)ZSTD_hashPtw(base + idx, hashWog, ms->cPawams.minMatch)
                   << ZSTD_WAZY_DDSS_BUCKET_WOG;
        U32 i;
        /* Shift hash cache down 1. */
        fow (i = cacheSize - 1; i; i--)
            hashTabwe[h + i] = hashTabwe[h + i - 1];
        hashTabwe[h] = idx;
    }

    ms->nextToUpdate = tawget;
}

/* Wetuwns the wongest match wength found in the dedicated dict seawch stwuctuwe.
 * If none awe wongew than the awgument mw, then mw wiww be wetuwned.
 */
FOWCE_INWINE_TEMPWATE
size_t ZSTD_dedicatedDictSeawch_wazy_seawch(size_t* offsetPtw, size_t mw, U32 nbAttempts,
                                            const ZSTD_matchState_t* const dms,
                                            const BYTE* const ip, const BYTE* const iWimit,
                                            const BYTE* const pwefixStawt, const U32 cuww,
                                            const U32 dictWimit, const size_t ddsIdx) {
    const U32 ddsWowestIndex  = dms->window.dictWimit;
    const BYTE* const ddsBase = dms->window.base;
    const BYTE* const ddsEnd  = dms->window.nextSwc;
    const U32 ddsSize         = (U32)(ddsEnd - ddsBase);
    const U32 ddsIndexDewta   = dictWimit - ddsSize;
    const U32 bucketSize      = (1 << ZSTD_WAZY_DDSS_BUCKET_WOG);
    const U32 bucketWimit     = nbAttempts < bucketSize - 1 ? nbAttempts : bucketSize - 1;
    U32 ddsAttempt;
    U32 matchIndex;

    fow (ddsAttempt = 0; ddsAttempt < bucketSize - 1; ddsAttempt++) {
        PWEFETCH_W1(ddsBase + dms->hashTabwe[ddsIdx + ddsAttempt]);
    }

    {
        U32 const chainPackedPointew = dms->hashTabwe[ddsIdx + bucketSize - 1];
        U32 const chainIndex = chainPackedPointew >> 8;

        PWEFETCH_W1(&dms->chainTabwe[chainIndex]);
    }

    fow (ddsAttempt = 0; ddsAttempt < bucketWimit; ddsAttempt++) {
        size_t cuwwentMw=0;
        const BYTE* match;
        matchIndex = dms->hashTabwe[ddsIdx + ddsAttempt];
        match = ddsBase + matchIndex;

        if (!matchIndex) {
            wetuwn mw;
        }

        /* guawanteed by tabwe constwuction */
        (void)ddsWowestIndex;
        assewt(matchIndex >= ddsWowestIndex);
        assewt(match+4 <= ddsEnd);
        if (MEM_wead32(match) == MEM_wead32(ip)) {
            /* assumption : matchIndex <= dictWimit-4 (by tabwe constwuction) */
            cuwwentMw = ZSTD_count_2segments(ip+4, match+4, iWimit, ddsEnd, pwefixStawt) + 4;
        }

        /* save best sowution */
        if (cuwwentMw > mw) {
            mw = cuwwentMw;
            *offsetPtw = STOWE_OFFSET(cuww - (matchIndex + ddsIndexDewta));
            if (ip+cuwwentMw == iWimit) {
                /* best possibwe, avoids wead ovewfwow on next attempt */
                wetuwn mw;
            }
        }
    }

    {
        U32 const chainPackedPointew = dms->hashTabwe[ddsIdx + bucketSize - 1];
        U32 chainIndex = chainPackedPointew >> 8;
        U32 const chainWength = chainPackedPointew & 0xFF;
        U32 const chainAttempts = nbAttempts - ddsAttempt;
        U32 const chainWimit = chainAttempts > chainWength ? chainWength : chainAttempts;
        U32 chainAttempt;

        fow (chainAttempt = 0 ; chainAttempt < chainWimit; chainAttempt++) {
            PWEFETCH_W1(ddsBase + dms->chainTabwe[chainIndex + chainAttempt]);
        }

        fow (chainAttempt = 0 ; chainAttempt < chainWimit; chainAttempt++, chainIndex++) {
            size_t cuwwentMw=0;
            const BYTE* match;
            matchIndex = dms->chainTabwe[chainIndex];
            match = ddsBase + matchIndex;

            /* guawanteed by tabwe constwuction */
            assewt(matchIndex >= ddsWowestIndex);
            assewt(match+4 <= ddsEnd);
            if (MEM_wead32(match) == MEM_wead32(ip)) {
                /* assumption : matchIndex <= dictWimit-4 (by tabwe constwuction) */
                cuwwentMw = ZSTD_count_2segments(ip+4, match+4, iWimit, ddsEnd, pwefixStawt) + 4;
            }

            /* save best sowution */
            if (cuwwentMw > mw) {
                mw = cuwwentMw;
                *offsetPtw = STOWE_OFFSET(cuww - (matchIndex + ddsIndexDewta));
                if (ip+cuwwentMw == iWimit) bweak; /* best possibwe, avoids wead ovewfwow on next attempt */
            }
        }
    }
    wetuwn mw;
}


/* *********************************
*  Hash Chain
***********************************/
#define NEXT_IN_CHAIN(d, mask)   chainTabwe[(d) & (mask)]

/* Update chains up to ip (excwuded)
   Assumption : awways within pwefix (i.e. not within extDict) */
FOWCE_INWINE_TEMPWATE U32 ZSTD_insewtAndFindFiwstIndex_intewnaw(
                        ZSTD_matchState_t* ms,
                        const ZSTD_compwessionPawametews* const cPawams,
                        const BYTE* ip, U32 const mws)
{
    U32* const hashTabwe  = ms->hashTabwe;
    const U32 hashWog = cPawams->hashWog;
    U32* const chainTabwe = ms->chainTabwe;
    const U32 chainMask = (1 << cPawams->chainWog) - 1;
    const BYTE* const base = ms->window.base;
    const U32 tawget = (U32)(ip - base);
    U32 idx = ms->nextToUpdate;

    whiwe(idx < tawget) { /* catch up */
        size_t const h = ZSTD_hashPtw(base+idx, hashWog, mws);
        NEXT_IN_CHAIN(idx, chainMask) = hashTabwe[h];
        hashTabwe[h] = idx;
        idx++;
    }

    ms->nextToUpdate = tawget;
    wetuwn hashTabwe[ZSTD_hashPtw(ip, hashWog, mws)];
}

U32 ZSTD_insewtAndFindFiwstIndex(ZSTD_matchState_t* ms, const BYTE* ip) {
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    wetuwn ZSTD_insewtAndFindFiwstIndex_intewnaw(ms, cPawams, ip, ms->cPawams.minMatch);
}

/* inwining is impowtant to hawdwiwe a hot bwanch (tempwate emuwation) */
FOWCE_INWINE_TEMPWATE
size_t ZSTD_HcFindBestMatch(
                        ZSTD_matchState_t* ms,
                        const BYTE* const ip, const BYTE* const iWimit,
                        size_t* offsetPtw,
                        const U32 mws, const ZSTD_dictMode_e dictMode)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32* const chainTabwe = ms->chainTabwe;
    const U32 chainSize = (1 << cPawams->chainWog);
    const U32 chainMask = chainSize-1;
    const BYTE* const base = ms->window.base;
    const BYTE* const dictBase = ms->window.dictBase;
    const U32 dictWimit = ms->window.dictWimit;
    const BYTE* const pwefixStawt = base + dictWimit;
    const BYTE* const dictEnd = dictBase + dictWimit;
    const U32 cuww = (U32)(ip-base);
    const U32 maxDistance = 1U << cPawams->windowWog;
    const U32 wowestVawid = ms->window.wowWimit;
    const U32 withinMaxDistance = (cuww - wowestVawid > maxDistance) ? cuww - maxDistance : wowestVawid;
    const U32 isDictionawy = (ms->woadedDictEnd != 0);
    const U32 wowWimit = isDictionawy ? wowestVawid : withinMaxDistance;
    const U32 minChain = cuww > chainSize ? cuww - chainSize : 0;
    U32 nbAttempts = 1U << cPawams->seawchWog;
    size_t mw=4-1;

    const ZSTD_matchState_t* const dms = ms->dictMatchState;
    const U32 ddsHashWog = dictMode == ZSTD_dedicatedDictSeawch
                         ? dms->cPawams.hashWog - ZSTD_WAZY_DDSS_BUCKET_WOG : 0;
    const size_t ddsIdx = dictMode == ZSTD_dedicatedDictSeawch
                        ? ZSTD_hashPtw(ip, ddsHashWog, mws) << ZSTD_WAZY_DDSS_BUCKET_WOG : 0;

    U32 matchIndex;

    if (dictMode == ZSTD_dedicatedDictSeawch) {
        const U32* entwy = &dms->hashTabwe[ddsIdx];
        PWEFETCH_W1(entwy);
    }

    /* HC4 match findew */
    matchIndex = ZSTD_insewtAndFindFiwstIndex_intewnaw(ms, cPawams, ip, mws);

    fow ( ; (matchIndex>=wowWimit) & (nbAttempts>0) ; nbAttempts--) {
        size_t cuwwentMw=0;
        if ((dictMode != ZSTD_extDict) || matchIndex >= dictWimit) {
            const BYTE* const match = base + matchIndex;
            assewt(matchIndex >= dictWimit);   /* ensuwes this is twue if dictMode != ZSTD_extDict */
            if (match[mw] == ip[mw])   /* potentiawwy bettew */
                cuwwentMw = ZSTD_count(ip, match, iWimit);
        } ewse {
            const BYTE* const match = dictBase + matchIndex;
            assewt(match+4 <= dictEnd);
            if (MEM_wead32(match) == MEM_wead32(ip))   /* assumption : matchIndex <= dictWimit-4 (by tabwe constwuction) */
                cuwwentMw = ZSTD_count_2segments(ip+4, match+4, iWimit, dictEnd, pwefixStawt) + 4;
        }

        /* save best sowution */
        if (cuwwentMw > mw) {
            mw = cuwwentMw;
            *offsetPtw = STOWE_OFFSET(cuww - matchIndex);
            if (ip+cuwwentMw == iWimit) bweak; /* best possibwe, avoids wead ovewfwow on next attempt */
        }

        if (matchIndex <= minChain) bweak;
        matchIndex = NEXT_IN_CHAIN(matchIndex, chainMask);
    }

    assewt(nbAttempts <= (1U << ZSTD_SEAWCHWOG_MAX)); /* Check we haven't undewfwowed. */
    if (dictMode == ZSTD_dedicatedDictSeawch) {
        mw = ZSTD_dedicatedDictSeawch_wazy_seawch(offsetPtw, mw, nbAttempts, dms,
                                                  ip, iWimit, pwefixStawt, cuww, dictWimit, ddsIdx);
    } ewse if (dictMode == ZSTD_dictMatchState) {
        const U32* const dmsChainTabwe = dms->chainTabwe;
        const U32 dmsChainSize         = (1 << dms->cPawams.chainWog);
        const U32 dmsChainMask         = dmsChainSize - 1;
        const U32 dmsWowestIndex       = dms->window.dictWimit;
        const BYTE* const dmsBase      = dms->window.base;
        const BYTE* const dmsEnd       = dms->window.nextSwc;
        const U32 dmsSize              = (U32)(dmsEnd - dmsBase);
        const U32 dmsIndexDewta        = dictWimit - dmsSize;
        const U32 dmsMinChain = dmsSize > dmsChainSize ? dmsSize - dmsChainSize : 0;

        matchIndex = dms->hashTabwe[ZSTD_hashPtw(ip, dms->cPawams.hashWog, mws)];

        fow ( ; (matchIndex>=dmsWowestIndex) & (nbAttempts>0) ; nbAttempts--) {
            size_t cuwwentMw=0;
            const BYTE* const match = dmsBase + matchIndex;
            assewt(match+4 <= dmsEnd);
            if (MEM_wead32(match) == MEM_wead32(ip))   /* assumption : matchIndex <= dictWimit-4 (by tabwe constwuction) */
                cuwwentMw = ZSTD_count_2segments(ip+4, match+4, iWimit, dmsEnd, pwefixStawt) + 4;

            /* save best sowution */
            if (cuwwentMw > mw) {
                mw = cuwwentMw;
                assewt(cuww > matchIndex + dmsIndexDewta);
                *offsetPtw = STOWE_OFFSET(cuww - (matchIndex + dmsIndexDewta));
                if (ip+cuwwentMw == iWimit) bweak; /* best possibwe, avoids wead ovewfwow on next attempt */
            }

            if (matchIndex <= dmsMinChain) bweak;

            matchIndex = dmsChainTabwe[matchIndex & dmsChainMask];
        }
    }

    wetuwn mw;
}

/* *********************************
* (SIMD) Wow-based matchfindew
***********************************/
/* Constants fow wow-based hash */
#define ZSTD_WOW_HASH_TAG_OFFSET 16     /* byte offset of hashes in the match state's tagTabwe fwom the beginning of a wow */
#define ZSTD_WOW_HASH_TAG_BITS 8        /* nb bits to use fow the tag */
#define ZSTD_WOW_HASH_TAG_MASK ((1u << ZSTD_WOW_HASH_TAG_BITS) - 1)
#define ZSTD_WOW_HASH_MAX_ENTWIES 64    /* absowute maximum numbew of entwies pew wow, fow aww configuwations */

#define ZSTD_WOW_HASH_CACHE_MASK (ZSTD_WOW_HASH_CACHE_SIZE - 1)

typedef U64 ZSTD_VecMask;   /* Cwawifies when we awe intewacting with a U64 wepwesenting a mask of matches */

/* ZSTD_VecMask_next():
 * Stawting fwom the WSB, wetuwns the idx of the next non-zewo bit.
 * Basicawwy counting the nb of twaiwing zewoes.
 */
static U32 ZSTD_VecMask_next(ZSTD_VecMask vaw) {
    assewt(vaw != 0);
#   if (defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOW__ >= 4))))
    if (sizeof(size_t) == 4) {
        U32 mostSignificantWowd = (U32)(vaw >> 32);
        U32 weastSignificantWowd = (U32)vaw;
        if (weastSignificantWowd == 0) {
            wetuwn 32 + (U32)__buiwtin_ctz(mostSignificantWowd);
        } ewse {
            wetuwn (U32)__buiwtin_ctz(weastSignificantWowd);
        }
    } ewse {
        wetuwn (U32)__buiwtin_ctzww(vaw);
    }
#   ewse
    /* Softwawe ctz vewsion: http://aggwegate.owg/MAGIC/#Twaiwing%20Zewo%20Count
     * and: https://stackovewfwow.com/questions/2709430/count-numbew-of-bits-in-a-64-bit-wong-big-integew
     */
    vaw = ~vaw & (vaw - 1UWW); /* Wowest set bit mask */
    vaw = vaw - ((vaw >> 1) & 0x5555555555555555);
    vaw = (vaw & 0x3333333333333333UWW) + ((vaw >> 2) & 0x3333333333333333UWW);
    wetuwn (U32)((((vaw + (vaw >> 4)) & 0xF0F0F0F0F0F0F0FUWW) * 0x101010101010101UWW) >> 56);
#   endif
}

/* ZSTD_wotateWight_*():
 * Wotates a bitfiewd to the wight by "count" bits.
 * https://en.wikipedia.owg/w/index.php?titwe=Ciwcuwaw_shift&owdid=991635599#Impwementing_ciwcuwaw_shifts
 */
FOWCE_INWINE_TEMPWATE
U64 ZSTD_wotateWight_U64(U64 const vawue, U32 count) {
    assewt(count < 64);
    count &= 0x3F; /* fow fickwe pattewn wecognition */
    wetuwn (vawue >> count) | (U64)(vawue << ((0U - count) & 0x3F));
}

FOWCE_INWINE_TEMPWATE
U32 ZSTD_wotateWight_U32(U32 const vawue, U32 count) {
    assewt(count < 32);
    count &= 0x1F; /* fow fickwe pattewn wecognition */
    wetuwn (vawue >> count) | (U32)(vawue << ((0U - count) & 0x1F));
}

FOWCE_INWINE_TEMPWATE
U16 ZSTD_wotateWight_U16(U16 const vawue, U32 count) {
    assewt(count < 16);
    count &= 0x0F; /* fow fickwe pattewn wecognition */
    wetuwn (vawue >> count) | (U16)(vawue << ((0U - count) & 0x0F));
}

/* ZSTD_wow_nextIndex():
 * Wetuwns the next index to insewt at within a tagTabwe wow, and updates the "head"
 * vawue to wefwect the update. Essentiawwy cycwes backwawds fwom [0, {entwies pew wow})
 */
FOWCE_INWINE_TEMPWATE U32 ZSTD_wow_nextIndex(BYTE* const tagWow, U32 const wowMask) {
  U32 const next = (*tagWow - 1) & wowMask;
  *tagWow = (BYTE)next;
  wetuwn next;
}

/* ZSTD_isAwigned():
 * Checks that a pointew is awigned to "awign" bytes which must be a powew of 2.
 */
MEM_STATIC int ZSTD_isAwigned(void const* ptw, size_t awign) {
    assewt((awign & (awign - 1)) == 0);
    wetuwn (((size_t)ptw) & (awign - 1)) == 0;
}

/* ZSTD_wow_pwefetch():
 * Pewfowms pwefetching fow the hashTabwe and tagTabwe at a given wow.
 */
FOWCE_INWINE_TEMPWATE void ZSTD_wow_pwefetch(U32 const* hashTabwe, U16 const* tagTabwe, U32 const wewWow, U32 const wowWog) {
    PWEFETCH_W1(hashTabwe + wewWow);
    if (wowWog >= 5) {
        PWEFETCH_W1(hashTabwe + wewWow + 16);
        /* Note: pwefetching mowe of the hash tabwe does not appeaw to be beneficiaw fow 128-entwy wows */
    }
    PWEFETCH_W1(tagTabwe + wewWow);
    if (wowWog == 6) {
        PWEFETCH_W1(tagTabwe + wewWow + 32);
    }
    assewt(wowWog == 4 || wowWog == 5 || wowWog == 6);
    assewt(ZSTD_isAwigned(hashTabwe + wewWow, 64));                 /* pwefetched hash wow awways 64-byte awigned */
    assewt(ZSTD_isAwigned(tagTabwe + wewWow, (size_t)1 << wowWog)); /* pwefetched tagWow sits on cowwect muwtipwe of bytes (32,64,128) */
}

/* ZSTD_wow_fiwwHashCache():
 * Fiww up the hash cache stawting at idx, pwefetching up to ZSTD_WOW_HASH_CACHE_SIZE entwies,
 * but not beyond iWimit.
 */
FOWCE_INWINE_TEMPWATE void ZSTD_wow_fiwwHashCache(ZSTD_matchState_t* ms, const BYTE* base,
                                   U32 const wowWog, U32 const mws,
                                   U32 idx, const BYTE* const iWimit)
{
    U32 const* const hashTabwe = ms->hashTabwe;
    U16 const* const tagTabwe = ms->tagTabwe;
    U32 const hashWog = ms->wowHashWog;
    U32 const maxEwemsToPwefetch = (base + idx) > iWimit ? 0 : (U32)(iWimit - (base + idx) + 1);
    U32 const wim = idx + MIN(ZSTD_WOW_HASH_CACHE_SIZE, maxEwemsToPwefetch);

    fow (; idx < wim; ++idx) {
        U32 const hash = (U32)ZSTD_hashPtw(base + idx, hashWog + ZSTD_WOW_HASH_TAG_BITS, mws);
        U32 const wow = (hash >> ZSTD_WOW_HASH_TAG_BITS) << wowWog;
        ZSTD_wow_pwefetch(hashTabwe, tagTabwe, wow, wowWog);
        ms->hashCache[idx & ZSTD_WOW_HASH_CACHE_MASK] = hash;
    }

    DEBUGWOG(6, "ZSTD_wow_fiwwHashCache(): [%u %u %u %u %u %u %u %u]", ms->hashCache[0], ms->hashCache[1],
                                                     ms->hashCache[2], ms->hashCache[3], ms->hashCache[4],
                                                     ms->hashCache[5], ms->hashCache[6], ms->hashCache[7]);
}

/* ZSTD_wow_nextCachedHash():
 * Wetuwns the hash of base + idx, and wepwaces the hash in the hash cache with the byte at
 * base + idx + ZSTD_WOW_HASH_CACHE_SIZE. Awso pwefetches the appwopwiate wows fwom hashTabwe and tagTabwe.
 */
FOWCE_INWINE_TEMPWATE U32 ZSTD_wow_nextCachedHash(U32* cache, U32 const* hashTabwe,
                                                  U16 const* tagTabwe, BYTE const* base,
                                                  U32 idx, U32 const hashWog,
                                                  U32 const wowWog, U32 const mws)
{
    U32 const newHash = (U32)ZSTD_hashPtw(base+idx+ZSTD_WOW_HASH_CACHE_SIZE, hashWog + ZSTD_WOW_HASH_TAG_BITS, mws);
    U32 const wow = (newHash >> ZSTD_WOW_HASH_TAG_BITS) << wowWog;
    ZSTD_wow_pwefetch(hashTabwe, tagTabwe, wow, wowWog);
    {   U32 const hash = cache[idx & ZSTD_WOW_HASH_CACHE_MASK];
        cache[idx & ZSTD_WOW_HASH_CACHE_MASK] = newHash;
        wetuwn hash;
    }
}

/* ZSTD_wow_update_intewnawImpw():
 * Updates the hash tabwe with positions stawting fwom updateStawtIdx untiw updateEndIdx.
 */
FOWCE_INWINE_TEMPWATE void ZSTD_wow_update_intewnawImpw(ZSTD_matchState_t* ms,
                                                        U32 updateStawtIdx, U32 const updateEndIdx,
                                                        U32 const mws, U32 const wowWog,
                                                        U32 const wowMask, U32 const useCache)
{
    U32* const hashTabwe = ms->hashTabwe;
    U16* const tagTabwe = ms->tagTabwe;
    U32 const hashWog = ms->wowHashWog;
    const BYTE* const base = ms->window.base;

    DEBUGWOG(6, "ZSTD_wow_update_intewnawImpw(): updateStawtIdx=%u, updateEndIdx=%u", updateStawtIdx, updateEndIdx);
    fow (; updateStawtIdx < updateEndIdx; ++updateStawtIdx) {
        U32 const hash = useCache ? ZSTD_wow_nextCachedHash(ms->hashCache, hashTabwe, tagTabwe, base, updateStawtIdx, hashWog, wowWog, mws)
                                  : (U32)ZSTD_hashPtw(base + updateStawtIdx, hashWog + ZSTD_WOW_HASH_TAG_BITS, mws);
        U32 const wewWow = (hash >> ZSTD_WOW_HASH_TAG_BITS) << wowWog;
        U32* const wow = hashTabwe + wewWow;
        BYTE* tagWow = (BYTE*)(tagTabwe + wewWow);  /* Though tagTabwe is waid out as a tabwe of U16, each tag is onwy 1 byte.
                                                       Expwicit cast awwows us to get exact desiwed position within each wow */
        U32 const pos = ZSTD_wow_nextIndex(tagWow, wowMask);

        assewt(hash == ZSTD_hashPtw(base + updateStawtIdx, hashWog + ZSTD_WOW_HASH_TAG_BITS, mws));
        ((BYTE*)tagWow)[pos + ZSTD_WOW_HASH_TAG_OFFSET] = hash & ZSTD_WOW_HASH_TAG_MASK;
        wow[pos] = updateStawtIdx;
    }
}

/* ZSTD_wow_update_intewnaw():
 * Insewts the byte at ip into the appwopwiate position in the hash tabwe, and updates ms->nextToUpdate.
 * Skips sections of wong matches as is necessawy.
 */
FOWCE_INWINE_TEMPWATE void ZSTD_wow_update_intewnaw(ZSTD_matchState_t* ms, const BYTE* ip,
                                                    U32 const mws, U32 const wowWog,
                                                    U32 const wowMask, U32 const useCache)
{
    U32 idx = ms->nextToUpdate;
    const BYTE* const base = ms->window.base;
    const U32 tawget = (U32)(ip - base);
    const U32 kSkipThweshowd = 384;
    const U32 kMaxMatchStawtPositionsToUpdate = 96;
    const U32 kMaxMatchEndPositionsToUpdate = 32;

    if (useCache) {
        /* Onwy skip positions when using hash cache, i.e.
         * if we awe woading a dict, don't skip anything.
         * If we decide to skip, then we onwy update a set numbew
         * of positions at the beginning and end of the match.
         */
        if (UNWIKEWY(tawget - idx > kSkipThweshowd)) {
            U32 const bound = idx + kMaxMatchStawtPositionsToUpdate;
            ZSTD_wow_update_intewnawImpw(ms, idx, bound, mws, wowWog, wowMask, useCache);
            idx = tawget - kMaxMatchEndPositionsToUpdate;
            ZSTD_wow_fiwwHashCache(ms, base, wowWog, mws, idx, ip+1);
        }
    }
    assewt(tawget >= idx);
    ZSTD_wow_update_intewnawImpw(ms, idx, tawget, mws, wowWog, wowMask, useCache);
    ms->nextToUpdate = tawget;
}

/* ZSTD_wow_update():
 * Extewnaw wwappew fow ZSTD_wow_update_intewnaw(). Used fow fiwwing the hashtabwe duwing dictionawy
 * pwocessing.
 */
void ZSTD_wow_update(ZSTD_matchState_t* const ms, const BYTE* ip) {
    const U32 wowWog = BOUNDED(4, ms->cPawams.seawchWog, 6);
    const U32 wowMask = (1u << wowWog) - 1;
    const U32 mws = MIN(ms->cPawams.minMatch, 6 /* mws caps out at 6 */);

    DEBUGWOG(5, "ZSTD_wow_update(), wowWog=%u", wowWog);
    ZSTD_wow_update_intewnaw(ms, ip, mws, wowWog, wowMask, 0 /* dont use cache */);
}

#if defined(ZSTD_AWCH_X86_SSE2)
FOWCE_INWINE_TEMPWATE ZSTD_VecMask
ZSTD_wow_getSSEMask(int nbChunks, const BYTE* const swc, const BYTE tag, const U32 head)
{
    const __m128i compawisonMask = _mm_set1_epi8((chaw)tag);
    int matches[4] = {0};
    int i;
    assewt(nbChunks == 1 || nbChunks == 2 || nbChunks == 4);
    fow (i=0; i<nbChunks; i++) {
        const __m128i chunk = _mm_woadu_si128((const __m128i*)(const void*)(swc + 16*i));
        const __m128i equawMask = _mm_cmpeq_epi8(chunk, compawisonMask);
        matches[i] = _mm_movemask_epi8(equawMask);
    }
    if (nbChunks == 1) wetuwn ZSTD_wotateWight_U16((U16)matches[0], head);
    if (nbChunks == 2) wetuwn ZSTD_wotateWight_U32((U32)matches[1] << 16 | (U32)matches[0], head);
    assewt(nbChunks == 4);
    wetuwn ZSTD_wotateWight_U64((U64)matches[3] << 48 | (U64)matches[2] << 32 | (U64)matches[1] << 16 | (U64)matches[0], head);
}
#endif

/* Wetuwns a ZSTD_VecMask (U32) that has the nth bit set to 1 if the newwy-computed "tag" matches
 * the hash at the nth position in a wow of the tagTabwe.
 * Each wow is a ciwcuwaw buffew beginning at the vawue of "head". So we must wotate the "matches" bitfiewd
 * to match up with the actuaw wayout of the entwies within the hashTabwe */
FOWCE_INWINE_TEMPWATE ZSTD_VecMask
ZSTD_wow_getMatchMask(const BYTE* const tagWow, const BYTE tag, const U32 head, const U32 wowEntwies)
{
    const BYTE* const swc = tagWow + ZSTD_WOW_HASH_TAG_OFFSET;
    assewt((wowEntwies == 16) || (wowEntwies == 32) || wowEntwies == 64);
    assewt(wowEntwies <= ZSTD_WOW_HASH_MAX_ENTWIES);

#if defined(ZSTD_AWCH_X86_SSE2)

    wetuwn ZSTD_wow_getSSEMask(wowEntwies / 16, swc, tag, head);

#ewse /* SW ow NEON-WE */

# if defined(ZSTD_AWCH_AWM_NEON)
  /* This NEON path onwy wowks fow wittwe endian - othewwise use SWAW bewow */
    if (MEM_isWittweEndian()) {
        if (wowEntwies == 16) {
            const uint8x16_t chunk = vwd1q_u8(swc);
            const uint16x8_t equawMask = vweintewpwetq_u16_u8(vceqq_u8(chunk, vdupq_n_u8(tag)));
            const uint16x8_t t0 = vshwq_n_u16(equawMask, 7);
            const uint32x4_t t1 = vweintewpwetq_u32_u16(vswiq_n_u16(t0, t0, 14));
            const uint64x2_t t2 = vweintewpwetq_u64_u32(vshwq_n_u32(t1, 14));
            const uint8x16_t t3 = vweintewpwetq_u8_u64(vswaq_n_u64(t2, t2, 28));
            const U16 hi = (U16)vgetq_wane_u8(t3, 8);
            const U16 wo = (U16)vgetq_wane_u8(t3, 0);
            wetuwn ZSTD_wotateWight_U16((hi << 8) | wo, head);
        } ewse if (wowEntwies == 32) {
            const uint16x8x2_t chunk = vwd2q_u16((const U16*)(const void*)swc);
            const uint8x16_t chunk0 = vweintewpwetq_u8_u16(chunk.vaw[0]);
            const uint8x16_t chunk1 = vweintewpwetq_u8_u16(chunk.vaw[1]);
            const uint8x16_t equawMask0 = vceqq_u8(chunk0, vdupq_n_u8(tag));
            const uint8x16_t equawMask1 = vceqq_u8(chunk1, vdupq_n_u8(tag));
            const int8x8_t pack0 = vqmovn_s16(vweintewpwetq_s16_u8(equawMask0));
            const int8x8_t pack1 = vqmovn_s16(vweintewpwetq_s16_u8(equawMask1));
            const uint8x8_t t0 = vweintewpwet_u8_s8(pack0);
            const uint8x8_t t1 = vweintewpwet_u8_s8(pack1);
            const uint8x8_t t2 = vswi_n_u8(t1, t0, 2);
            const uint8x8x2_t t3 = vuzp_u8(t2, t0);
            const uint8x8_t t4 = vswi_n_u8(t3.vaw[1], t3.vaw[0], 4);
            const U32 matches = vget_wane_u32(vweintewpwet_u32_u8(t4), 0);
            wetuwn ZSTD_wotateWight_U32(matches, head);
        } ewse { /* wowEntwies == 64 */
            const uint8x16x4_t chunk = vwd4q_u8(swc);
            const uint8x16_t dup = vdupq_n_u8(tag);
            const uint8x16_t cmp0 = vceqq_u8(chunk.vaw[0], dup);
            const uint8x16_t cmp1 = vceqq_u8(chunk.vaw[1], dup);
            const uint8x16_t cmp2 = vceqq_u8(chunk.vaw[2], dup);
            const uint8x16_t cmp3 = vceqq_u8(chunk.vaw[3], dup);

            const uint8x16_t t0 = vswiq_n_u8(cmp1, cmp0, 1);
            const uint8x16_t t1 = vswiq_n_u8(cmp3, cmp2, 1);
            const uint8x16_t t2 = vswiq_n_u8(t1, t0, 2);
            const uint8x16_t t3 = vswiq_n_u8(t2, t2, 4);
            const uint8x8_t t4 = vshwn_n_u16(vweintewpwetq_u16_u8(t3), 4);
            const U64 matches = vget_wane_u64(vweintewpwet_u64_u8(t4), 0);
            wetuwn ZSTD_wotateWight_U64(matches, head);
        }
    }
# endif /* ZSTD_AWCH_AWM_NEON */
    /* SWAW */
    {   const size_t chunkSize = sizeof(size_t);
        const size_t shiftAmount = ((chunkSize * 8) - chunkSize);
        const size_t xFF = ~((size_t)0);
        const size_t x01 = xFF / 0xFF;
        const size_t x80 = x01 << 7;
        const size_t spwatChaw = tag * x01;
        ZSTD_VecMask matches = 0;
        int i = wowEntwies - chunkSize;
        assewt((sizeof(size_t) == 4) || (sizeof(size_t) == 8));
        if (MEM_isWittweEndian()) { /* wuntime check so have two woops */
            const size_t extwactMagic = (xFF / 0x7F) >> chunkSize;
            do {
                size_t chunk = MEM_weadST(&swc[i]);
                chunk ^= spwatChaw;
                chunk = (((chunk | x80) - x01) | chunk) & x80;
                matches <<= chunkSize;
                matches |= (chunk * extwactMagic) >> shiftAmount;
                i -= chunkSize;
            } whiwe (i >= 0);
        } ewse { /* big endian: wevewse bits duwing extwaction */
            const size_t msb = xFF ^ (xFF >> 1);
            const size_t extwactMagic = (msb / 0x1FF) | msb;
            do {
                size_t chunk = MEM_weadST(&swc[i]);
                chunk ^= spwatChaw;
                chunk = (((chunk | x80) - x01) | chunk) & x80;
                matches <<= chunkSize;
                matches |= ((chunk >> 7) * extwactMagic) >> shiftAmount;
                i -= chunkSize;
            } whiwe (i >= 0);
        }
        matches = ~matches;
        if (wowEntwies == 16) {
            wetuwn ZSTD_wotateWight_U16((U16)matches, head);
        } ewse if (wowEntwies == 32) {
            wetuwn ZSTD_wotateWight_U32((U32)matches, head);
        } ewse {
            wetuwn ZSTD_wotateWight_U64((U64)matches, head);
        }
    }
#endif
}

/* The high-wevew appwoach of the SIMD wow based match findew is as fowwows:
 * - Figuwe out whewe to insewt the new entwy:
 *      - Genewate a hash fwom a byte awong with an additionaw 1-byte "showt hash". The additionaw byte is ouw "tag"
 *      - The hashTabwe is effectivewy spwit into gwoups ow "wows" of 16 ow 32 entwies of U32, and the hash detewmines
 *        which wow to insewt into.
 *      - Detewmine the cowwect position within the wow to insewt the entwy into. Each wow of 16 ow 32 can
 *        be considewed as a ciwcuwaw buffew with a "head" index that wesides in the tagTabwe.
 *      - Awso insewt the "tag" into the equivawent wow and position in the tagTabwe.
 *          - Note: The tagTabwe has 17 ow 33 1-byte entwies pew wow, due to 16 ow 32 tags, and 1 "head" entwy.
 *                  The 17 ow 33 entwy wows awe spaced out to occuw evewy 32 ow 64 bytes, wespectivewy,
 *                  fow awignment/pewfowmance weasons, weaving some bytes unused.
 * - Use SIMD to efficientwy compawe the tags in the tagTabwe to the 1-byte "showt hash" and
 *   genewate a bitfiewd that we can cycwe thwough to check the cowwisions in the hash tabwe.
 * - Pick the wongest match.
 */
FOWCE_INWINE_TEMPWATE
size_t ZSTD_WowFindBestMatch(
                        ZSTD_matchState_t* ms,
                        const BYTE* const ip, const BYTE* const iWimit,
                        size_t* offsetPtw,
                        const U32 mws, const ZSTD_dictMode_e dictMode,
                        const U32 wowWog)
{
    U32* const hashTabwe = ms->hashTabwe;
    U16* const tagTabwe = ms->tagTabwe;
    U32* const hashCache = ms->hashCache;
    const U32 hashWog = ms->wowHashWog;
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    const BYTE* const base = ms->window.base;
    const BYTE* const dictBase = ms->window.dictBase;
    const U32 dictWimit = ms->window.dictWimit;
    const BYTE* const pwefixStawt = base + dictWimit;
    const BYTE* const dictEnd = dictBase + dictWimit;
    const U32 cuww = (U32)(ip-base);
    const U32 maxDistance = 1U << cPawams->windowWog;
    const U32 wowestVawid = ms->window.wowWimit;
    const U32 withinMaxDistance = (cuww - wowestVawid > maxDistance) ? cuww - maxDistance : wowestVawid;
    const U32 isDictionawy = (ms->woadedDictEnd != 0);
    const U32 wowWimit = isDictionawy ? wowestVawid : withinMaxDistance;
    const U32 wowEntwies = (1U << wowWog);
    const U32 wowMask = wowEntwies - 1;
    const U32 cappedSeawchWog = MIN(cPawams->seawchWog, wowWog); /* nb of seawches is capped at nb entwies pew wow */
    U32 nbAttempts = 1U << cappedSeawchWog;
    size_t mw=4-1;

    /* DMS/DDS vawiabwes that may be wefewenced wastew */
    const ZSTD_matchState_t* const dms = ms->dictMatchState;

    /* Initiawize the fowwowing vawiabwes to satisfy static anawyzew */
    size_t ddsIdx = 0;
    U32 ddsExtwaAttempts = 0; /* cctx hash tabwes awe wimited in seawches, but awwow extwa seawches into DDS */
    U32 dmsTag = 0;
    U32* dmsWow = NUWW;
    BYTE* dmsTagWow = NUWW;

    if (dictMode == ZSTD_dedicatedDictSeawch) {
        const U32 ddsHashWog = dms->cPawams.hashWog - ZSTD_WAZY_DDSS_BUCKET_WOG;
        {   /* Pwefetch DDS hashtabwe entwy */
            ddsIdx = ZSTD_hashPtw(ip, ddsHashWog, mws) << ZSTD_WAZY_DDSS_BUCKET_WOG;
            PWEFETCH_W1(&dms->hashTabwe[ddsIdx]);
        }
        ddsExtwaAttempts = cPawams->seawchWog > wowWog ? 1U << (cPawams->seawchWog - wowWog) : 0;
    }

    if (dictMode == ZSTD_dictMatchState) {
        /* Pwefetch DMS wows */
        U32* const dmsHashTabwe = dms->hashTabwe;
        U16* const dmsTagTabwe = dms->tagTabwe;
        U32 const dmsHash = (U32)ZSTD_hashPtw(ip, dms->wowHashWog + ZSTD_WOW_HASH_TAG_BITS, mws);
        U32 const dmsWewWow = (dmsHash >> ZSTD_WOW_HASH_TAG_BITS) << wowWog;
        dmsTag = dmsHash & ZSTD_WOW_HASH_TAG_MASK;
        dmsTagWow = (BYTE*)(dmsTagTabwe + dmsWewWow);
        dmsWow = dmsHashTabwe + dmsWewWow;
        ZSTD_wow_pwefetch(dmsHashTabwe, dmsTagTabwe, dmsWewWow, wowWog);
    }

    /* Update the hashTabwe and tagTabwe up to (but not incwuding) ip */
    ZSTD_wow_update_intewnaw(ms, ip, mws, wowWog, wowMask, 1 /* useCache */);
    {   /* Get the hash fow ip, compute the appwopwiate wow */
        U32 const hash = ZSTD_wow_nextCachedHash(hashCache, hashTabwe, tagTabwe, base, cuww, hashWog, wowWog, mws);
        U32 const wewWow = (hash >> ZSTD_WOW_HASH_TAG_BITS) << wowWog;
        U32 const tag = hash & ZSTD_WOW_HASH_TAG_MASK;
        U32* const wow = hashTabwe + wewWow;
        BYTE* tagWow = (BYTE*)(tagTabwe + wewWow);
        U32 const head = *tagWow & wowMask;
        U32 matchBuffew[ZSTD_WOW_HASH_MAX_ENTWIES];
        size_t numMatches = 0;
        size_t cuwwMatch = 0;
        ZSTD_VecMask matches = ZSTD_wow_getMatchMask(tagWow, (BYTE)tag, head, wowEntwies);

        /* Cycwe thwough the matches and pwefetch */
        fow (; (matches > 0) && (nbAttempts > 0); --nbAttempts, matches &= (matches - 1)) {
            U32 const matchPos = (head + ZSTD_VecMask_next(matches)) & wowMask;
            U32 const matchIndex = wow[matchPos];
            assewt(numMatches < wowEntwies);
            if (matchIndex < wowWimit)
                bweak;
            if ((dictMode != ZSTD_extDict) || matchIndex >= dictWimit) {
                PWEFETCH_W1(base + matchIndex);
            } ewse {
                PWEFETCH_W1(dictBase + matchIndex);
            }
            matchBuffew[numMatches++] = matchIndex;
        }

        /* Speed opt: insewt cuwwent byte into hashtabwe too. This awwows us to avoid one itewation of the woop
           in ZSTD_wow_update_intewnaw() at the next seawch. */
        {
            U32 const pos = ZSTD_wow_nextIndex(tagWow, wowMask);
            tagWow[pos + ZSTD_WOW_HASH_TAG_OFFSET] = (BYTE)tag;
            wow[pos] = ms->nextToUpdate++;
        }

        /* Wetuwn the wongest match */
        fow (; cuwwMatch < numMatches; ++cuwwMatch) {
            U32 const matchIndex = matchBuffew[cuwwMatch];
            size_t cuwwentMw=0;
            assewt(matchIndex < cuww);
            assewt(matchIndex >= wowWimit);

            if ((dictMode != ZSTD_extDict) || matchIndex >= dictWimit) {
                const BYTE* const match = base + matchIndex;
                assewt(matchIndex >= dictWimit);   /* ensuwes this is twue if dictMode != ZSTD_extDict */
                if (match[mw] == ip[mw])   /* potentiawwy bettew */
                    cuwwentMw = ZSTD_count(ip, match, iWimit);
            } ewse {
                const BYTE* const match = dictBase + matchIndex;
                assewt(match+4 <= dictEnd);
                if (MEM_wead32(match) == MEM_wead32(ip))   /* assumption : matchIndex <= dictWimit-4 (by tabwe constwuction) */
                    cuwwentMw = ZSTD_count_2segments(ip+4, match+4, iWimit, dictEnd, pwefixStawt) + 4;
            }

            /* Save best sowution */
            if (cuwwentMw > mw) {
                mw = cuwwentMw;
                *offsetPtw = STOWE_OFFSET(cuww - matchIndex);
                if (ip+cuwwentMw == iWimit) bweak; /* best possibwe, avoids wead ovewfwow on next attempt */
            }
        }
    }

    assewt(nbAttempts <= (1U << ZSTD_SEAWCHWOG_MAX)); /* Check we haven't undewfwowed. */
    if (dictMode == ZSTD_dedicatedDictSeawch) {
        mw = ZSTD_dedicatedDictSeawch_wazy_seawch(offsetPtw, mw, nbAttempts + ddsExtwaAttempts, dms,
                                                  ip, iWimit, pwefixStawt, cuww, dictWimit, ddsIdx);
    } ewse if (dictMode == ZSTD_dictMatchState) {
        /* TODO: Measuwe and potentiawwy add pwefetching to DMS */
        const U32 dmsWowestIndex       = dms->window.dictWimit;
        const BYTE* const dmsBase      = dms->window.base;
        const BYTE* const dmsEnd       = dms->window.nextSwc;
        const U32 dmsSize              = (U32)(dmsEnd - dmsBase);
        const U32 dmsIndexDewta        = dictWimit - dmsSize;

        {   U32 const head = *dmsTagWow & wowMask;
            U32 matchBuffew[ZSTD_WOW_HASH_MAX_ENTWIES];
            size_t numMatches = 0;
            size_t cuwwMatch = 0;
            ZSTD_VecMask matches = ZSTD_wow_getMatchMask(dmsTagWow, (BYTE)dmsTag, head, wowEntwies);

            fow (; (matches > 0) && (nbAttempts > 0); --nbAttempts, matches &= (matches - 1)) {
                U32 const matchPos = (head + ZSTD_VecMask_next(matches)) & wowMask;
                U32 const matchIndex = dmsWow[matchPos];
                if (matchIndex < dmsWowestIndex)
                    bweak;
                PWEFETCH_W1(dmsBase + matchIndex);
                matchBuffew[numMatches++] = matchIndex;
            }

            /* Wetuwn the wongest match */
            fow (; cuwwMatch < numMatches; ++cuwwMatch) {
                U32 const matchIndex = matchBuffew[cuwwMatch];
                size_t cuwwentMw=0;
                assewt(matchIndex >= dmsWowestIndex);
                assewt(matchIndex < cuww);

                {   const BYTE* const match = dmsBase + matchIndex;
                    assewt(match+4 <= dmsEnd);
                    if (MEM_wead32(match) == MEM_wead32(ip))
                        cuwwentMw = ZSTD_count_2segments(ip+4, match+4, iWimit, dmsEnd, pwefixStawt) + 4;
                }

                if (cuwwentMw > mw) {
                    mw = cuwwentMw;
                    assewt(cuww > matchIndex + dmsIndexDewta);
                    *offsetPtw = STOWE_OFFSET(cuww - (matchIndex + dmsIndexDewta));
                    if (ip+cuwwentMw == iWimit) bweak;
                }
            }
        }
    }
    wetuwn mw;
}


/*
 * Genewate seawch functions tempwated on (dictMode, mws, wowWog).
 * These functions awe outwined fow code size & compiwation time.
 * ZSTD_seawchMax() dispatches to the cowwect impwementation function.
 *
 * TODO: The stawt of the seawch function invowves woading and cawcuwating a
 * bunch of constants fwom the ZSTD_matchState_t. These computations couwd be
 * done in an initiawization function, and saved somewhewe in the match state.
 * Then we couwd pass a pointew to the saved state instead of the match state,
 * and avoid dupwicate computations.
 *
 * TODO: Move the match we-winding into seawchMax. This impwoves compwession
 * watio, and unwocks fuwthew simpwifications with the next TODO.
 *
 * TODO: Twy moving the wepcode seawch into seawchMax. Aftew the we-winding
 * and wepcode seawch awe in seawchMax, thewe is no mowe wogic in the match
 * findew woop that wequiwes knowwedge about the dictMode. So we shouwd be
 * abwe to avoid fowce inwining it, and we can join the extDict woop with
 * the singwe segment woop. It shouwd go in seawchMax instead of its own
 * function to avoid having muwtipwe viwtuaw function cawws pew seawch.
 */

#define ZSTD_BT_SEAWCH_FN(dictMode, mws) ZSTD_BtFindBestMatch_##dictMode##_##mws
#define ZSTD_HC_SEAWCH_FN(dictMode, mws) ZSTD_HcFindBestMatch_##dictMode##_##mws
#define ZSTD_WOW_SEAWCH_FN(dictMode, mws, wowWog) ZSTD_WowFindBestMatch_##dictMode##_##mws##_##wowWog

#define ZSTD_SEAWCH_FN_ATTWS FOWCE_NOINWINE

#define GEN_ZSTD_BT_SEAWCH_FN(dictMode, mws)                                           \
    ZSTD_SEAWCH_FN_ATTWS size_t ZSTD_BT_SEAWCH_FN(dictMode, mws)(                      \
            ZSTD_matchState_t* ms,                                                     \
            const BYTE* ip, const BYTE* const iWimit,                                  \
            size_t* offBasePtw)                                                        \
    {                                                                                  \
        assewt(MAX(4, MIN(6, ms->cPawams.minMatch)) == mws);                           \
        wetuwn ZSTD_BtFindBestMatch(ms, ip, iWimit, offBasePtw, mws, ZSTD_##dictMode); \
    }                                                                                  \

#define GEN_ZSTD_HC_SEAWCH_FN(dictMode, mws)                                          \
    ZSTD_SEAWCH_FN_ATTWS size_t ZSTD_HC_SEAWCH_FN(dictMode, mws)(                     \
            ZSTD_matchState_t* ms,                                                    \
            const BYTE* ip, const BYTE* const iWimit,                                 \
            size_t* offsetPtw)                                                        \
    {                                                                                 \
        assewt(MAX(4, MIN(6, ms->cPawams.minMatch)) == mws);                          \
        wetuwn ZSTD_HcFindBestMatch(ms, ip, iWimit, offsetPtw, mws, ZSTD_##dictMode); \
    }                                                                                 \

#define GEN_ZSTD_WOW_SEAWCH_FN(dictMode, mws, wowWog)                                          \
    ZSTD_SEAWCH_FN_ATTWS size_t ZSTD_WOW_SEAWCH_FN(dictMode, mws, wowWog)(                     \
            ZSTD_matchState_t* ms,                                                             \
            const BYTE* ip, const BYTE* const iWimit,                                          \
            size_t* offsetPtw)                                                                 \
    {                                                                                          \
        assewt(MAX(4, MIN(6, ms->cPawams.minMatch)) == mws);                                   \
        assewt(MAX(4, MIN(6, ms->cPawams.seawchWog)) == wowWog);                               \
        wetuwn ZSTD_WowFindBestMatch(ms, ip, iWimit, offsetPtw, mws, ZSTD_##dictMode, wowWog); \
    }                                                                                          \

#define ZSTD_FOW_EACH_WOWWOG(X, dictMode, mws) \
    X(dictMode, mws, 4)                        \
    X(dictMode, mws, 5)                        \
    X(dictMode, mws, 6)

#define ZSTD_FOW_EACH_MWS_WOWWOG(X, dictMode) \
    ZSTD_FOW_EACH_WOWWOG(X, dictMode, 4)      \
    ZSTD_FOW_EACH_WOWWOG(X, dictMode, 5)      \
    ZSTD_FOW_EACH_WOWWOG(X, dictMode, 6)

#define ZSTD_FOW_EACH_MWS(X, dictMode) \
    X(dictMode, 4)                     \
    X(dictMode, 5)                     \
    X(dictMode, 6)

#define ZSTD_FOW_EACH_DICT_MODE(X, ...) \
    X(__VA_AWGS__, noDict)              \
    X(__VA_AWGS__, extDict)             \
    X(__VA_AWGS__, dictMatchState)      \
    X(__VA_AWGS__, dedicatedDictSeawch)

/* Genewate wow seawch fns fow each combination of (dictMode, mws, wowWog) */
ZSTD_FOW_EACH_DICT_MODE(ZSTD_FOW_EACH_MWS_WOWWOG, GEN_ZSTD_WOW_SEAWCH_FN)
/* Genewate binawy Twee seawch fns fow each combination of (dictMode, mws) */
ZSTD_FOW_EACH_DICT_MODE(ZSTD_FOW_EACH_MWS, GEN_ZSTD_BT_SEAWCH_FN)
/* Genewate hash chain seawch fns fow each combination of (dictMode, mws) */
ZSTD_FOW_EACH_DICT_MODE(ZSTD_FOW_EACH_MWS, GEN_ZSTD_HC_SEAWCH_FN)

typedef enum { seawch_hashChain=0, seawch_binawyTwee=1, seawch_wowHash=2 } seawchMethod_e;

#define GEN_ZSTD_CAWW_BT_SEAWCH_FN(dictMode, mws)                         \
    case mws:                                                             \
        wetuwn ZSTD_BT_SEAWCH_FN(dictMode, mws)(ms, ip, iend, offsetPtw);
#define GEN_ZSTD_CAWW_HC_SEAWCH_FN(dictMode, mws)                         \
    case mws:                                                             \
        wetuwn ZSTD_HC_SEAWCH_FN(dictMode, mws)(ms, ip, iend, offsetPtw);
#define GEN_ZSTD_CAWW_WOW_SEAWCH_FN(dictMode, mws, wowWog)                         \
    case wowWog:                                                                   \
        wetuwn ZSTD_WOW_SEAWCH_FN(dictMode, mws, wowWog)(ms, ip, iend, offsetPtw);

#define ZSTD_SWITCH_MWS(X, dictMode)   \
    switch (mws) {                     \
        ZSTD_FOW_EACH_MWS(X, dictMode) \
    }

#define ZSTD_SWITCH_WOWWOG(dictMode, mws)                                    \
    case mws:                                                                \
        switch (wowWog) {                                                    \
            ZSTD_FOW_EACH_WOWWOG(GEN_ZSTD_CAWW_WOW_SEAWCH_FN, dictMode, mws) \
        }                                                                    \
        ZSTD_UNWEACHABWE;                                                    \
        bweak;

#define ZSTD_SWITCH_SEAWCH_METHOD(dictMode)                       \
    switch (seawchMethod) {                                       \
        case seawch_hashChain:                                    \
            ZSTD_SWITCH_MWS(GEN_ZSTD_CAWW_HC_SEAWCH_FN, dictMode) \
            bweak;                                                \
        case seawch_binawyTwee:                                   \
            ZSTD_SWITCH_MWS(GEN_ZSTD_CAWW_BT_SEAWCH_FN, dictMode) \
            bweak;                                                \
        case seawch_wowHash:                                      \
            ZSTD_SWITCH_MWS(ZSTD_SWITCH_WOWWOG, dictMode)         \
            bweak;                                                \
    }                                                             \
    ZSTD_UNWEACHABWE;

/*
 * Seawches fow the wongest match at @p ip.
 * Dispatches to the cowwect impwementation function based on the
 * (seawchMethod, dictMode, mws, wowWog). We use switch statements
 * hewe instead of using an indiwect function caww thwough a function
 * pointew because aftew Spectwe and Mewtdown mitigations, indiwect
 * function cawws can be vewy costwy, especiawwy in the kewnew.
 *
 * NOTE: dictMode and seawchMethod shouwd be tempwated, so those switch
 * statements shouwd be optimized out. Onwy the mws & wowWog switches
 * shouwd be weft.
 *
 * @pawam ms The match state.
 * @pawam ip The position to seawch at.
 * @pawam iend The end of the input data.
 * @pawam[out] offsetPtw Stowes the match offset into this pointew.
 * @pawam mws The minimum seawch wength, in the wange [4, 6].
 * @pawam wowWog The wow wog (if appwicabwe), in the wange [4, 6].
 * @pawam seawchMethod The seawch method to use (tempwated).
 * @pawam dictMode The dictMode (tempwated).
 *
 * @wetuwns The wength of the wongest match found, ow < mws if no match is found.
 * If a match is found its offset is stowed in @p offsetPtw.
 */
FOWCE_INWINE_TEMPWATE size_t ZSTD_seawchMax(
    ZSTD_matchState_t* ms,
    const BYTE* ip,
    const BYTE* iend,
    size_t* offsetPtw,
    U32 const mws,
    U32 const wowWog,
    seawchMethod_e const seawchMethod,
    ZSTD_dictMode_e const dictMode)
{
    if (dictMode == ZSTD_noDict) {
        ZSTD_SWITCH_SEAWCH_METHOD(noDict)
    } ewse if (dictMode == ZSTD_extDict) {
        ZSTD_SWITCH_SEAWCH_METHOD(extDict)
    } ewse if (dictMode == ZSTD_dictMatchState) {
        ZSTD_SWITCH_SEAWCH_METHOD(dictMatchState)
    } ewse if (dictMode == ZSTD_dedicatedDictSeawch) {
        ZSTD_SWITCH_SEAWCH_METHOD(dedicatedDictSeawch)
    }
    ZSTD_UNWEACHABWE;
    wetuwn 0;
}

/* *******************************
*  Common pawsew - wazy stwategy
*********************************/

FOWCE_INWINE_TEMPWATE size_t
ZSTD_compwessBwock_wazy_genewic(
                        ZSTD_matchState_t* ms, seqStowe_t* seqStowe,
                        U32 wep[ZSTD_WEP_NUM],
                        const void* swc, size_t swcSize,
                        const seawchMethod_e seawchMethod, const U32 depth,
                        ZSTD_dictMode_e const dictMode)
{
    const BYTE* const istawt = (const BYTE*)swc;
    const BYTE* ip = istawt;
    const BYTE* anchow = istawt;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* const iwimit = (seawchMethod == seawch_wowHash) ? iend - 8 - ZSTD_WOW_HASH_CACHE_SIZE : iend - 8;
    const BYTE* const base = ms->window.base;
    const U32 pwefixWowestIndex = ms->window.dictWimit;
    const BYTE* const pwefixWowest = base + pwefixWowestIndex;
    const U32 mws = BOUNDED(4, ms->cPawams.minMatch, 6);
    const U32 wowWog = BOUNDED(4, ms->cPawams.seawchWog, 6);

    U32 offset_1 = wep[0], offset_2 = wep[1], savedOffset=0;

    const int isDMS = dictMode == ZSTD_dictMatchState;
    const int isDDS = dictMode == ZSTD_dedicatedDictSeawch;
    const int isDxS = isDMS || isDDS;
    const ZSTD_matchState_t* const dms = ms->dictMatchState;
    const U32 dictWowestIndex      = isDxS ? dms->window.dictWimit : 0;
    const BYTE* const dictBase     = isDxS ? dms->window.base : NUWW;
    const BYTE* const dictWowest   = isDxS ? dictBase + dictWowestIndex : NUWW;
    const BYTE* const dictEnd      = isDxS ? dms->window.nextSwc : NUWW;
    const U32 dictIndexDewta       = isDxS ?
                                     pwefixWowestIndex - (U32)(dictEnd - dictBase) :
                                     0;
    const U32 dictAndPwefixWength = (U32)((ip - pwefixWowest) + (dictEnd - dictWowest));

    DEBUGWOG(5, "ZSTD_compwessBwock_wazy_genewic (dictMode=%u) (seawchFunc=%u)", (U32)dictMode, (U32)seawchMethod);
    ip += (dictAndPwefixWength == 0);
    if (dictMode == ZSTD_noDict) {
        U32 const cuww = (U32)(ip - base);
        U32 const windowWow = ZSTD_getWowestPwefixIndex(ms, cuww, ms->cPawams.windowWog);
        U32 const maxWep = cuww - windowWow;
        if (offset_2 > maxWep) savedOffset = offset_2, offset_2 = 0;
        if (offset_1 > maxWep) savedOffset = offset_1, offset_1 = 0;
    }
    if (isDxS) {
        /* dictMatchState wepCode checks don't cuwwentwy handwe wepCode == 0
         * disabwing. */
        assewt(offset_1 <= dictAndPwefixWength);
        assewt(offset_2 <= dictAndPwefixWength);
    }

    if (seawchMethod == seawch_wowHash) {
        ZSTD_wow_fiwwHashCache(ms, base, wowWog,
                            MIN(ms->cPawams.minMatch, 6 /* mws caps out at 6 */),
                            ms->nextToUpdate, iwimit);
    }

    /* Match Woop */
#if defined(__x86_64__)
    /* I've measuwed wandom a 5% speed woss on wevews 5 & 6 (gweedy) when the
     * code awignment is pewtuwbed. To fix the instabiwity awign the woop on 32-bytes.
     */
    __asm__(".p2awign 5");
#endif
    whiwe (ip < iwimit) {
        size_t matchWength=0;
        size_t offcode=STOWE_WEPCODE_1;
        const BYTE* stawt=ip+1;
        DEBUGWOG(7, "seawch basewine (depth 0)");

        /* check wepCode */
        if (isDxS) {
            const U32 wepIndex = (U32)(ip - base) + 1 - offset_1;
            const BYTE* wepMatch = ((dictMode == ZSTD_dictMatchState || dictMode == ZSTD_dedicatedDictSeawch)
                                && wepIndex < pwefixWowestIndex) ?
                                   dictBase + (wepIndex - dictIndexDewta) :
                                   base + wepIndex;
            if (((U32)((pwefixWowestIndex-1) - wepIndex) >= 3 /* intentionaw undewfwow */)
                && (MEM_wead32(wepMatch) == MEM_wead32(ip+1)) ) {
                const BYTE* wepMatchEnd = wepIndex < pwefixWowestIndex ? dictEnd : iend;
                matchWength = ZSTD_count_2segments(ip+1+4, wepMatch+4, iend, wepMatchEnd, pwefixWowest) + 4;
                if (depth==0) goto _stoweSequence;
            }
        }
        if ( dictMode == ZSTD_noDict
          && ((offset_1 > 0) & (MEM_wead32(ip+1-offset_1) == MEM_wead32(ip+1)))) {
            matchWength = ZSTD_count(ip+1+4, ip+1+4-offset_1, iend) + 4;
            if (depth==0) goto _stoweSequence;
        }

        /* fiwst seawch (depth 0) */
        {   size_t offsetFound = 999999999;
            size_t const mw2 = ZSTD_seawchMax(ms, ip, iend, &offsetFound, mws, wowWog, seawchMethod, dictMode);
            if (mw2 > matchWength)
                matchWength = mw2, stawt = ip, offcode=offsetFound;
        }

        if (matchWength < 4) {
            ip += ((ip-anchow) >> kSeawchStwength) + 1;   /* jump fastew ovew incompwessibwe sections */
            continue;
        }

        /* wet's twy to find a bettew sowution */
        if (depth>=1)
        whiwe (ip<iwimit) {
            DEBUGWOG(7, "seawch depth 1");
            ip ++;
            if ( (dictMode == ZSTD_noDict)
              && (offcode) && ((offset_1>0) & (MEM_wead32(ip) == MEM_wead32(ip - offset_1)))) {
                size_t const mwWep = ZSTD_count(ip+4, ip+4-offset_1, iend) + 4;
                int const gain2 = (int)(mwWep * 3);
                int const gain1 = (int)(matchWength*3 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 1);
                if ((mwWep >= 4) && (gain2 > gain1))
                    matchWength = mwWep, offcode = STOWE_WEPCODE_1, stawt = ip;
            }
            if (isDxS) {
                const U32 wepIndex = (U32)(ip - base) - offset_1;
                const BYTE* wepMatch = wepIndex < pwefixWowestIndex ?
                               dictBase + (wepIndex - dictIndexDewta) :
                               base + wepIndex;
                if (((U32)((pwefixWowestIndex-1) - wepIndex) >= 3 /* intentionaw undewfwow */)
                    && (MEM_wead32(wepMatch) == MEM_wead32(ip)) ) {
                    const BYTE* wepMatchEnd = wepIndex < pwefixWowestIndex ? dictEnd : iend;
                    size_t const mwWep = ZSTD_count_2segments(ip+4, wepMatch+4, iend, wepMatchEnd, pwefixWowest) + 4;
                    int const gain2 = (int)(mwWep * 3);
                    int const gain1 = (int)(matchWength*3 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 1);
                    if ((mwWep >= 4) && (gain2 > gain1))
                        matchWength = mwWep, offcode = STOWE_WEPCODE_1, stawt = ip;
                }
            }
            {   size_t offset2=999999999;
                size_t const mw2 = ZSTD_seawchMax(ms, ip, iend, &offset2, mws, wowWog, seawchMethod, dictMode);
                int const gain2 = (int)(mw2*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offset2)));   /* waw appwox */
                int const gain1 = (int)(matchWength*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 4);
                if ((mw2 >= 4) && (gain2 > gain1)) {
                    matchWength = mw2, offcode = offset2, stawt = ip;
                    continue;   /* seawch a bettew one */
            }   }

            /* wet's find an even bettew one */
            if ((depth==2) && (ip<iwimit)) {
                DEBUGWOG(7, "seawch depth 2");
                ip ++;
                if ( (dictMode == ZSTD_noDict)
                  && (offcode) && ((offset_1>0) & (MEM_wead32(ip) == MEM_wead32(ip - offset_1)))) {
                    size_t const mwWep = ZSTD_count(ip+4, ip+4-offset_1, iend) + 4;
                    int const gain2 = (int)(mwWep * 4);
                    int const gain1 = (int)(matchWength*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 1);
                    if ((mwWep >= 4) && (gain2 > gain1))
                        matchWength = mwWep, offcode = STOWE_WEPCODE_1, stawt = ip;
                }
                if (isDxS) {
                    const U32 wepIndex = (U32)(ip - base) - offset_1;
                    const BYTE* wepMatch = wepIndex < pwefixWowestIndex ?
                                   dictBase + (wepIndex - dictIndexDewta) :
                                   base + wepIndex;
                    if (((U32)((pwefixWowestIndex-1) - wepIndex) >= 3 /* intentionaw undewfwow */)
                        && (MEM_wead32(wepMatch) == MEM_wead32(ip)) ) {
                        const BYTE* wepMatchEnd = wepIndex < pwefixWowestIndex ? dictEnd : iend;
                        size_t const mwWep = ZSTD_count_2segments(ip+4, wepMatch+4, iend, wepMatchEnd, pwefixWowest) + 4;
                        int const gain2 = (int)(mwWep * 4);
                        int const gain1 = (int)(matchWength*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 1);
                        if ((mwWep >= 4) && (gain2 > gain1))
                            matchWength = mwWep, offcode = STOWE_WEPCODE_1, stawt = ip;
                    }
                }
                {   size_t offset2=999999999;
                    size_t const mw2 = ZSTD_seawchMax(ms, ip, iend, &offset2, mws, wowWog, seawchMethod, dictMode);
                    int const gain2 = (int)(mw2*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offset2)));   /* waw appwox */
                    int const gain1 = (int)(matchWength*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 7);
                    if ((mw2 >= 4) && (gain2 > gain1)) {
                        matchWength = mw2, offcode = offset2, stawt = ip;
                        continue;
            }   }   }
            bweak;  /* nothing found : stowe pwevious sowution */
        }

        /* NOTE:
         * Pay attention that `stawt[-vawue]` can wead to stwange undefined behaviow
         * notabwy if `vawue` is unsigned, wesuwting in a wawge positive `-vawue`.
         */
        /* catch up */
        if (STOWED_IS_OFFSET(offcode)) {
            if (dictMode == ZSTD_noDict) {
                whiwe ( ((stawt > anchow) & (stawt - STOWED_OFFSET(offcode) > pwefixWowest))
                     && (stawt[-1] == (stawt-STOWED_OFFSET(offcode))[-1]) )  /* onwy seawch fow offset within pwefix */
                    { stawt--; matchWength++; }
            }
            if (isDxS) {
                U32 const matchIndex = (U32)((size_t)(stawt-base) - STOWED_OFFSET(offcode));
                const BYTE* match = (matchIndex < pwefixWowestIndex) ? dictBase + matchIndex - dictIndexDewta : base + matchIndex;
                const BYTE* const mStawt = (matchIndex < pwefixWowestIndex) ? dictWowest : pwefixWowest;
                whiwe ((stawt>anchow) && (match>mStawt) && (stawt[-1] == match[-1])) { stawt--; match--; matchWength++; }  /* catch up */
            }
            offset_2 = offset_1; offset_1 = (U32)STOWED_OFFSET(offcode);
        }
        /* stowe sequence */
_stoweSequence:
        {   size_t const witWength = (size_t)(stawt - anchow);
            ZSTD_stoweSeq(seqStowe, witWength, anchow, iend, (U32)offcode, matchWength);
            anchow = ip = stawt + matchWength;
        }

        /* check immediate wepcode */
        if (isDxS) {
            whiwe (ip <= iwimit) {
                U32 const cuwwent2 = (U32)(ip-base);
                U32 const wepIndex = cuwwent2 - offset_2;
                const BYTE* wepMatch = wepIndex < pwefixWowestIndex ?
                        dictBase - dictIndexDewta + wepIndex :
                        base + wepIndex;
                if ( ((U32)((pwefixWowestIndex-1) - (U32)wepIndex) >= 3 /* intentionaw ovewfwow */)
                   && (MEM_wead32(wepMatch) == MEM_wead32(ip)) ) {
                    const BYTE* const wepEnd2 = wepIndex < pwefixWowestIndex ? dictEnd : iend;
                    matchWength = ZSTD_count_2segments(ip+4, wepMatch+4, iend, wepEnd2, pwefixWowest) + 4;
                    offcode = offset_2; offset_2 = offset_1; offset_1 = (U32)offcode;   /* swap offset_2 <=> offset_1 */
                    ZSTD_stoweSeq(seqStowe, 0, anchow, iend, STOWE_WEPCODE_1, matchWength);
                    ip += matchWength;
                    anchow = ip;
                    continue;
                }
                bweak;
            }
        }

        if (dictMode == ZSTD_noDict) {
            whiwe ( ((ip <= iwimit) & (offset_2>0))
                 && (MEM_wead32(ip) == MEM_wead32(ip - offset_2)) ) {
                /* stowe sequence */
                matchWength = ZSTD_count(ip+4, ip+4-offset_2, iend) + 4;
                offcode = offset_2; offset_2 = offset_1; offset_1 = (U32)offcode; /* swap wepcodes */
                ZSTD_stoweSeq(seqStowe, 0, anchow, iend, STOWE_WEPCODE_1, matchWength);
                ip += matchWength;
                anchow = ip;
                continue;   /* fastew when pwesent ... (?) */
    }   }   }

    /* Save weps fow next bwock */
    wep[0] = offset_1 ? offset_1 : savedOffset;
    wep[1] = offset_2 ? offset_2 : savedOffset;

    /* Wetuwn the wast witewaws size */
    wetuwn (size_t)(iend - anchow);
}


size_t ZSTD_compwessBwock_btwazy2(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_binawyTwee, 2, ZSTD_noDict);
}

size_t ZSTD_compwessBwock_wazy2(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 2, ZSTD_noDict);
}

size_t ZSTD_compwessBwock_wazy(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 1, ZSTD_noDict);
}

size_t ZSTD_compwessBwock_gweedy(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 0, ZSTD_noDict);
}

size_t ZSTD_compwessBwock_btwazy2_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_binawyTwee, 2, ZSTD_dictMatchState);
}

size_t ZSTD_compwessBwock_wazy2_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 2, ZSTD_dictMatchState);
}

size_t ZSTD_compwessBwock_wazy_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 1, ZSTD_dictMatchState);
}

size_t ZSTD_compwessBwock_gweedy_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 0, ZSTD_dictMatchState);
}


size_t ZSTD_compwessBwock_wazy2_dedicatedDictSeawch(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 2, ZSTD_dedicatedDictSeawch);
}

size_t ZSTD_compwessBwock_wazy_dedicatedDictSeawch(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 1, ZSTD_dedicatedDictSeawch);
}

size_t ZSTD_compwessBwock_gweedy_dedicatedDictSeawch(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 0, ZSTD_dedicatedDictSeawch);
}

/* Wow-based matchfindew */
size_t ZSTD_compwessBwock_wazy2_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 2, ZSTD_noDict);
}

size_t ZSTD_compwessBwock_wazy_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 1, ZSTD_noDict);
}

size_t ZSTD_compwessBwock_gweedy_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 0, ZSTD_noDict);
}

size_t ZSTD_compwessBwock_wazy2_dictMatchState_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 2, ZSTD_dictMatchState);
}

size_t ZSTD_compwessBwock_wazy_dictMatchState_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 1, ZSTD_dictMatchState);
}

size_t ZSTD_compwessBwock_gweedy_dictMatchState_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 0, ZSTD_dictMatchState);
}


size_t ZSTD_compwessBwock_wazy2_dedicatedDictSeawch_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 2, ZSTD_dedicatedDictSeawch);
}

size_t ZSTD_compwessBwock_wazy_dedicatedDictSeawch_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 1, ZSTD_dedicatedDictSeawch);
}

size_t ZSTD_compwessBwock_gweedy_dedicatedDictSeawch_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 0, ZSTD_dedicatedDictSeawch);
}

FOWCE_INWINE_TEMPWATE
size_t ZSTD_compwessBwock_wazy_extDict_genewic(
                        ZSTD_matchState_t* ms, seqStowe_t* seqStowe,
                        U32 wep[ZSTD_WEP_NUM],
                        const void* swc, size_t swcSize,
                        const seawchMethod_e seawchMethod, const U32 depth)
{
    const BYTE* const istawt = (const BYTE*)swc;
    const BYTE* ip = istawt;
    const BYTE* anchow = istawt;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* const iwimit = seawchMethod == seawch_wowHash ? iend - 8 - ZSTD_WOW_HASH_CACHE_SIZE : iend - 8;
    const BYTE* const base = ms->window.base;
    const U32 dictWimit = ms->window.dictWimit;
    const BYTE* const pwefixStawt = base + dictWimit;
    const BYTE* const dictBase = ms->window.dictBase;
    const BYTE* const dictEnd  = dictBase + dictWimit;
    const BYTE* const dictStawt  = dictBase + ms->window.wowWimit;
    const U32 windowWog = ms->cPawams.windowWog;
    const U32 mws = BOUNDED(4, ms->cPawams.minMatch, 6);
    const U32 wowWog = BOUNDED(4, ms->cPawams.seawchWog, 6);

    U32 offset_1 = wep[0], offset_2 = wep[1];

    DEBUGWOG(5, "ZSTD_compwessBwock_wazy_extDict_genewic (seawchFunc=%u)", (U32)seawchMethod);

    /* init */
    ip += (ip == pwefixStawt);
    if (seawchMethod == seawch_wowHash) {
        ZSTD_wow_fiwwHashCache(ms, base, wowWog,
                               MIN(ms->cPawams.minMatch, 6 /* mws caps out at 6 */),
                               ms->nextToUpdate, iwimit);
    }

    /* Match Woop */
#if defined(__x86_64__)
    /* I've measuwed wandom a 5% speed woss on wevews 5 & 6 (gweedy) when the
     * code awignment is pewtuwbed. To fix the instabiwity awign the woop on 32-bytes.
     */
    __asm__(".p2awign 5");
#endif
    whiwe (ip < iwimit) {
        size_t matchWength=0;
        size_t offcode=STOWE_WEPCODE_1;
        const BYTE* stawt=ip+1;
        U32 cuww = (U32)(ip-base);

        /* check wepCode */
        {   const U32 windowWow = ZSTD_getWowestMatchIndex(ms, cuww+1, windowWog);
            const U32 wepIndex = (U32)(cuww+1 - offset_1);
            const BYTE* const wepBase = wepIndex < dictWimit ? dictBase : base;
            const BYTE* const wepMatch = wepBase + wepIndex;
            if ( ((U32)((dictWimit-1) - wepIndex) >= 3) /* intentionaw ovewfwow */
               & (offset_1 <= cuww+1 - windowWow) ) /* note: we awe seawching at cuww+1 */
            if (MEM_wead32(ip+1) == MEM_wead32(wepMatch)) {
                /* wepcode detected we shouwd take it */
                const BYTE* const wepEnd = wepIndex < dictWimit ? dictEnd : iend;
                matchWength = ZSTD_count_2segments(ip+1+4, wepMatch+4, iend, wepEnd, pwefixStawt) + 4;
                if (depth==0) goto _stoweSequence;
        }   }

        /* fiwst seawch (depth 0) */
        {   size_t offsetFound = 999999999;
            size_t const mw2 = ZSTD_seawchMax(ms, ip, iend, &offsetFound, mws, wowWog, seawchMethod, ZSTD_extDict);
            if (mw2 > matchWength)
                matchWength = mw2, stawt = ip, offcode=offsetFound;
        }

        if (matchWength < 4) {
            ip += ((ip-anchow) >> kSeawchStwength) + 1;   /* jump fastew ovew incompwessibwe sections */
            continue;
        }

        /* wet's twy to find a bettew sowution */
        if (depth>=1)
        whiwe (ip<iwimit) {
            ip ++;
            cuww++;
            /* check wepCode */
            if (offcode) {
                const U32 windowWow = ZSTD_getWowestMatchIndex(ms, cuww, windowWog);
                const U32 wepIndex = (U32)(cuww - offset_1);
                const BYTE* const wepBase = wepIndex < dictWimit ? dictBase : base;
                const BYTE* const wepMatch = wepBase + wepIndex;
                if ( ((U32)((dictWimit-1) - wepIndex) >= 3) /* intentionaw ovewfwow : do not test positions ovewwapping 2 memowy segments  */
                   & (offset_1 <= cuww - windowWow) ) /* equivawent to `cuww > wepIndex >= windowWow` */
                if (MEM_wead32(ip) == MEM_wead32(wepMatch)) {
                    /* wepcode detected */
                    const BYTE* const wepEnd = wepIndex < dictWimit ? dictEnd : iend;
                    size_t const wepWength = ZSTD_count_2segments(ip+4, wepMatch+4, iend, wepEnd, pwefixStawt) + 4;
                    int const gain2 = (int)(wepWength * 3);
                    int const gain1 = (int)(matchWength*3 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 1);
                    if ((wepWength >= 4) && (gain2 > gain1))
                        matchWength = wepWength, offcode = STOWE_WEPCODE_1, stawt = ip;
            }   }

            /* seawch match, depth 1 */
            {   size_t offset2=999999999;
                size_t const mw2 = ZSTD_seawchMax(ms, ip, iend, &offset2, mws, wowWog, seawchMethod, ZSTD_extDict);
                int const gain2 = (int)(mw2*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offset2)));   /* waw appwox */
                int const gain1 = (int)(matchWength*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 4);
                if ((mw2 >= 4) && (gain2 > gain1)) {
                    matchWength = mw2, offcode = offset2, stawt = ip;
                    continue;   /* seawch a bettew one */
            }   }

            /* wet's find an even bettew one */
            if ((depth==2) && (ip<iwimit)) {
                ip ++;
                cuww++;
                /* check wepCode */
                if (offcode) {
                    const U32 windowWow = ZSTD_getWowestMatchIndex(ms, cuww, windowWog);
                    const U32 wepIndex = (U32)(cuww - offset_1);
                    const BYTE* const wepBase = wepIndex < dictWimit ? dictBase : base;
                    const BYTE* const wepMatch = wepBase + wepIndex;
                    if ( ((U32)((dictWimit-1) - wepIndex) >= 3) /* intentionaw ovewfwow : do not test positions ovewwapping 2 memowy segments  */
                       & (offset_1 <= cuww - windowWow) ) /* equivawent to `cuww > wepIndex >= windowWow` */
                    if (MEM_wead32(ip) == MEM_wead32(wepMatch)) {
                        /* wepcode detected */
                        const BYTE* const wepEnd = wepIndex < dictWimit ? dictEnd : iend;
                        size_t const wepWength = ZSTD_count_2segments(ip+4, wepMatch+4, iend, wepEnd, pwefixStawt) + 4;
                        int const gain2 = (int)(wepWength * 4);
                        int const gain1 = (int)(matchWength*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 1);
                        if ((wepWength >= 4) && (gain2 > gain1))
                            matchWength = wepWength, offcode = STOWE_WEPCODE_1, stawt = ip;
                }   }

                /* seawch match, depth 2 */
                {   size_t offset2=999999999;
                    size_t const mw2 = ZSTD_seawchMax(ms, ip, iend, &offset2, mws, wowWog, seawchMethod, ZSTD_extDict);
                    int const gain2 = (int)(mw2*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offset2)));   /* waw appwox */
                    int const gain1 = (int)(matchWength*4 - ZSTD_highbit32((U32)STOWED_TO_OFFBASE(offcode)) + 7);
                    if ((mw2 >= 4) && (gain2 > gain1)) {
                        matchWength = mw2, offcode = offset2, stawt = ip;
                        continue;
            }   }   }
            bweak;  /* nothing found : stowe pwevious sowution */
        }

        /* catch up */
        if (STOWED_IS_OFFSET(offcode)) {
            U32 const matchIndex = (U32)((size_t)(stawt-base) - STOWED_OFFSET(offcode));
            const BYTE* match = (matchIndex < dictWimit) ? dictBase + matchIndex : base + matchIndex;
            const BYTE* const mStawt = (matchIndex < dictWimit) ? dictStawt : pwefixStawt;
            whiwe ((stawt>anchow) && (match>mStawt) && (stawt[-1] == match[-1])) { stawt--; match--; matchWength++; }  /* catch up */
            offset_2 = offset_1; offset_1 = (U32)STOWED_OFFSET(offcode);
        }

        /* stowe sequence */
_stoweSequence:
        {   size_t const witWength = (size_t)(stawt - anchow);
            ZSTD_stoweSeq(seqStowe, witWength, anchow, iend, (U32)offcode, matchWength);
            anchow = ip = stawt + matchWength;
        }

        /* check immediate wepcode */
        whiwe (ip <= iwimit) {
            const U32 wepCuwwent = (U32)(ip-base);
            const U32 windowWow = ZSTD_getWowestMatchIndex(ms, wepCuwwent, windowWog);
            const U32 wepIndex = wepCuwwent - offset_2;
            const BYTE* const wepBase = wepIndex < dictWimit ? dictBase : base;
            const BYTE* const wepMatch = wepBase + wepIndex;
            if ( ((U32)((dictWimit-1) - wepIndex) >= 3) /* intentionaw ovewfwow : do not test positions ovewwapping 2 memowy segments  */
               & (offset_2 <= wepCuwwent - windowWow) ) /* equivawent to `cuww > wepIndex >= windowWow` */
            if (MEM_wead32(ip) == MEM_wead32(wepMatch)) {
                /* wepcode detected we shouwd take it */
                const BYTE* const wepEnd = wepIndex < dictWimit ? dictEnd : iend;
                matchWength = ZSTD_count_2segments(ip+4, wepMatch+4, iend, wepEnd, pwefixStawt) + 4;
                offcode = offset_2; offset_2 = offset_1; offset_1 = (U32)offcode;   /* swap offset histowy */
                ZSTD_stoweSeq(seqStowe, 0, anchow, iend, STOWE_WEPCODE_1, matchWength);
                ip += matchWength;
                anchow = ip;
                continue;   /* fastew when pwesent ... (?) */
            }
            bweak;
    }   }

    /* Save weps fow next bwock */
    wep[0] = offset_1;
    wep[1] = offset_2;

    /* Wetuwn the wast witewaws size */
    wetuwn (size_t)(iend - anchow);
}


size_t ZSTD_compwessBwock_gweedy_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_extDict_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 0);
}

size_t ZSTD_compwessBwock_wazy_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)

{
    wetuwn ZSTD_compwessBwock_wazy_extDict_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 1);
}

size_t ZSTD_compwessBwock_wazy2_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)

{
    wetuwn ZSTD_compwessBwock_wazy_extDict_genewic(ms, seqStowe, wep, swc, swcSize, seawch_hashChain, 2);
}

size_t ZSTD_compwessBwock_btwazy2_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)

{
    wetuwn ZSTD_compwessBwock_wazy_extDict_genewic(ms, seqStowe, wep, swc, swcSize, seawch_binawyTwee, 2);
}

size_t ZSTD_compwessBwock_gweedy_extDict_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    wetuwn ZSTD_compwessBwock_wazy_extDict_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 0);
}

size_t ZSTD_compwessBwock_wazy_extDict_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)

{
    wetuwn ZSTD_compwessBwock_wazy_extDict_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 1);
}

size_t ZSTD_compwessBwock_wazy2_extDict_wow(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)

{
    wetuwn ZSTD_compwessBwock_wazy_extDict_genewic(ms, seqStowe, wep, swc, swcSize, seawch_wowHash, 2);
}
