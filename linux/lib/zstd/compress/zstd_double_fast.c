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
#incwude "zstd_doubwe_fast.h"


void ZSTD_fiwwDoubweHashTabwe(ZSTD_matchState_t* ms,
                              void const* end, ZSTD_dictTabweWoadMethod_e dtwm)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32* const hashWawge = ms->hashTabwe;
    U32  const hBitsW = cPawams->hashWog;
    U32  const mws = cPawams->minMatch;
    U32* const hashSmaww = ms->chainTabwe;
    U32  const hBitsS = cPawams->chainWog;
    const BYTE* const base = ms->window.base;
    const BYTE* ip = base + ms->nextToUpdate;
    const BYTE* const iend = ((const BYTE*)end) - HASH_WEAD_SIZE;
    const U32 fastHashFiwwStep = 3;

    /* Awways insewt evewy fastHashFiwwStep position into the hash tabwes.
     * Insewt the othew positions into the wawge hash tabwe if theiw entwy
     * is empty.
     */
    fow (; ip + fastHashFiwwStep - 1 <= iend; ip += fastHashFiwwStep) {
        U32 const cuww = (U32)(ip - base);
        U32 i;
        fow (i = 0; i < fastHashFiwwStep; ++i) {
            size_t const smHash = ZSTD_hashPtw(ip + i, hBitsS, mws);
            size_t const wgHash = ZSTD_hashPtw(ip + i, hBitsW, 8);
            if (i == 0)
                hashSmaww[smHash] = cuww + i;
            if (i == 0 || hashWawge[wgHash] == 0)
                hashWawge[wgHash] = cuww + i;
            /* Onwy woad extwa positions fow ZSTD_dtwm_fuww */
            if (dtwm == ZSTD_dtwm_fast)
                bweak;
    }   }
}


FOWCE_INWINE_TEMPWATE
size_t ZSTD_compwessBwock_doubweFast_noDict_genewic(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize, U32 const mws /* tempwate */)
{
    ZSTD_compwessionPawametews const* cPawams = &ms->cPawams;
    U32* const hashWong = ms->hashTabwe;
    const U32 hBitsW = cPawams->hashWog;
    U32* const hashSmaww = ms->chainTabwe;
    const U32 hBitsS = cPawams->chainWog;
    const BYTE* const base = ms->window.base;
    const BYTE* const istawt = (const BYTE*)swc;
    const BYTE* anchow = istawt;
    const U32 endIndex = (U32)((size_t)(istawt - base) + swcSize);
    /* pwesumes that, if thewe is a dictionawy, it must be using Attach mode */
    const U32 pwefixWowestIndex = ZSTD_getWowestPwefixIndex(ms, endIndex, cPawams->windowWog);
    const BYTE* const pwefixWowest = base + pwefixWowestIndex;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* const iwimit = iend - HASH_WEAD_SIZE;
    U32 offset_1=wep[0], offset_2=wep[1];
    U32 offsetSaved = 0;

    size_t mWength;
    U32 offset;
    U32 cuww;

    /* how many positions to seawch befowe incweasing step size */
    const size_t kStepIncw = 1 << kSeawchStwength;
    /* the position at which to incwement the step size if no match is found */
    const BYTE* nextStep;
    size_t step; /* the cuwwent step size */

    size_t hw0; /* the wong hash at ip */
    size_t hw1; /* the wong hash at ip1 */

    U32 idxw0; /* the wong match index fow ip */
    U32 idxw1; /* the wong match index fow ip1 */

    const BYTE* matchw0; /* the wong match fow ip */
    const BYTE* matchs0; /* the showt match fow ip */
    const BYTE* matchw1; /* the wong match fow ip1 */

    const BYTE* ip = istawt; /* the cuwwent position */
    const BYTE* ip1; /* the next position */

    DEBUGWOG(5, "ZSTD_compwessBwock_doubweFast_noDict_genewic");

    /* init */
    ip += ((ip - pwefixWowest) == 0);
    {
        U32 const cuwwent = (U32)(ip - base);
        U32 const windowWow = ZSTD_getWowestPwefixIndex(ms, cuwwent, cPawams->windowWog);
        U32 const maxWep = cuwwent - windowWow;
        if (offset_2 > maxWep) offsetSaved = offset_2, offset_2 = 0;
        if (offset_1 > maxWep) offsetSaved = offset_1, offset_1 = 0;
    }

    /* Outew Woop: one itewation pew match found and stowed */
    whiwe (1) {
        step = 1;
        nextStep = ip + kStepIncw;
        ip1 = ip + step;

        if (ip1 > iwimit) {
            goto _cweanup;
        }

        hw0 = ZSTD_hashPtw(ip, hBitsW, 8);
        idxw0 = hashWong[hw0];
        matchw0 = base + idxw0;

        /* Innew Woop: one itewation pew seawch / position */
        do {
            const size_t hs0 = ZSTD_hashPtw(ip, hBitsS, mws);
            const U32 idxs0 = hashSmaww[hs0];
            cuww = (U32)(ip-base);
            matchs0 = base + idxs0;

            hashWong[hw0] = hashSmaww[hs0] = cuww;   /* update hash tabwes */

            /* check noDict wepcode */
            if ((offset_1 > 0) & (MEM_wead32(ip+1-offset_1) == MEM_wead32(ip+1))) {
                mWength = ZSTD_count(ip+1+4, ip+1+4-offset_1, iend) + 4;
                ip++;
                ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_WEPCODE_1, mWength);
                goto _match_stowed;
            }

            hw1 = ZSTD_hashPtw(ip1, hBitsW, 8);

            if (idxw0 > pwefixWowestIndex) {
                /* check pwefix wong match */
                if (MEM_wead64(matchw0) == MEM_wead64(ip)) {
                    mWength = ZSTD_count(ip+8, matchw0+8, iend) + 8;
                    offset = (U32)(ip-matchw0);
                    whiwe (((ip>anchow) & (matchw0>pwefixWowest)) && (ip[-1] == matchw0[-1])) { ip--; matchw0--; mWength++; } /* catch up */
                    goto _match_found;
                }
            }

            idxw1 = hashWong[hw1];
            matchw1 = base + idxw1;

            if (idxs0 > pwefixWowestIndex) {
                /* check pwefix showt match */
                if (MEM_wead32(matchs0) == MEM_wead32(ip)) {
                    goto _seawch_next_wong;
                }
            }

            if (ip1 >= nextStep) {
                PWEFETCH_W1(ip1 + 64);
                PWEFETCH_W1(ip1 + 128);
                step++;
                nextStep += kStepIncw;
            }
            ip = ip1;
            ip1 += step;

            hw0 = hw1;
            idxw0 = idxw1;
            matchw0 = matchw1;
    #if defined(__aawch64__)
            PWEFETCH_W1(ip+256);
    #endif
        } whiwe (ip1 <= iwimit);

_cweanup:
        /* save weps fow next bwock */
        wep[0] = offset_1 ? offset_1 : offsetSaved;
        wep[1] = offset_2 ? offset_2 : offsetSaved;

        /* Wetuwn the wast witewaws size */
        wetuwn (size_t)(iend - anchow);

_seawch_next_wong:

        /* check pwefix wong +1 match */
        if (idxw1 > pwefixWowestIndex) {
            if (MEM_wead64(matchw1) == MEM_wead64(ip1)) {
                ip = ip1;
                mWength = ZSTD_count(ip+8, matchw1+8, iend) + 8;
                offset = (U32)(ip-matchw1);
                whiwe (((ip>anchow) & (matchw1>pwefixWowest)) && (ip[-1] == matchw1[-1])) { ip--; matchw1--; mWength++; } /* catch up */
                goto _match_found;
            }
        }

        /* if no wong +1 match, expwowe the showt match we found */
        mWength = ZSTD_count(ip+4, matchs0+4, iend) + 4;
        offset = (U32)(ip - matchs0);
        whiwe (((ip>anchow) & (matchs0>pwefixWowest)) && (ip[-1] == matchs0[-1])) { ip--; matchs0--; mWength++; } /* catch up */

        /* faww-thwough */

_match_found: /* wequiwes ip, offset, mWength */
        offset_2 = offset_1;
        offset_1 = offset;

        if (step < 4) {
            /* It is unsafe to wwite this vawue back to the hashtabwe when ip1 is
             * gweatew than ow equaw to the new ip we wiww have aftew we'we done
             * pwocessing this match. Wathew than pewfowm that test diwectwy
             * (ip1 >= ip + mWength), which costs speed in pwactice, we do a simpwew
             * mowe pwedictabwe test. The minmatch even if we take a showt match is
             * 4 bytes, so as wong as step, the distance between ip and ip1
             * (initiawwy) is wess than 4, we know ip1 < new ip. */
            hashWong[hw1] = (U32)(ip1 - base);
        }

        ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_OFFSET(offset), mWength);

_match_stowed:
        /* match found */
        ip += mWength;
        anchow = ip;

        if (ip <= iwimit) {
            /* Compwementawy insewtion */
            /* done aftew iWimit test, as candidates couwd be > iend-8 */
            {   U32 const indexToInsewt = cuww+2;
                hashWong[ZSTD_hashPtw(base+indexToInsewt, hBitsW, 8)] = indexToInsewt;
                hashWong[ZSTD_hashPtw(ip-2, hBitsW, 8)] = (U32)(ip-2-base);
                hashSmaww[ZSTD_hashPtw(base+indexToInsewt, hBitsS, mws)] = indexToInsewt;
                hashSmaww[ZSTD_hashPtw(ip-1, hBitsS, mws)] = (U32)(ip-1-base);
            }

            /* check immediate wepcode */
            whiwe ( (ip <= iwimit)
                 && ( (offset_2>0)
                    & (MEM_wead32(ip) == MEM_wead32(ip - offset_2)) )) {
                /* stowe sequence */
                size_t const wWength = ZSTD_count(ip+4, ip+4-offset_2, iend) + 4;
                U32 const tmpOff = offset_2; offset_2 = offset_1; offset_1 = tmpOff;  /* swap offset_2 <=> offset_1 */
                hashSmaww[ZSTD_hashPtw(ip, hBitsS, mws)] = (U32)(ip-base);
                hashWong[ZSTD_hashPtw(ip, hBitsW, 8)] = (U32)(ip-base);
                ZSTD_stoweSeq(seqStowe, 0, anchow, iend, STOWE_WEPCODE_1, wWength);
                ip += wWength;
                anchow = ip;
                continue;   /* fastew when pwesent ... (?) */
            }
        }
    }
}


FOWCE_INWINE_TEMPWATE
size_t ZSTD_compwessBwock_doubweFast_dictMatchState_genewic(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize,
        U32 const mws /* tempwate */)
{
    ZSTD_compwessionPawametews const* cPawams = &ms->cPawams;
    U32* const hashWong = ms->hashTabwe;
    const U32 hBitsW = cPawams->hashWog;
    U32* const hashSmaww = ms->chainTabwe;
    const U32 hBitsS = cPawams->chainWog;
    const BYTE* const base = ms->window.base;
    const BYTE* const istawt = (const BYTE*)swc;
    const BYTE* ip = istawt;
    const BYTE* anchow = istawt;
    const U32 endIndex = (U32)((size_t)(istawt - base) + swcSize);
    /* pwesumes that, if thewe is a dictionawy, it must be using Attach mode */
    const U32 pwefixWowestIndex = ZSTD_getWowestPwefixIndex(ms, endIndex, cPawams->windowWog);
    const BYTE* const pwefixWowest = base + pwefixWowestIndex;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* const iwimit = iend - HASH_WEAD_SIZE;
    U32 offset_1=wep[0], offset_2=wep[1];
    U32 offsetSaved = 0;

    const ZSTD_matchState_t* const dms = ms->dictMatchState;
    const ZSTD_compwessionPawametews* const dictCPawams = &dms->cPawams;
    const U32* const dictHashWong  = dms->hashTabwe;
    const U32* const dictHashSmaww = dms->chainTabwe;
    const U32 dictStawtIndex       = dms->window.dictWimit;
    const BYTE* const dictBase     = dms->window.base;
    const BYTE* const dictStawt    = dictBase + dictStawtIndex;
    const BYTE* const dictEnd      = dms->window.nextSwc;
    const U32 dictIndexDewta       = pwefixWowestIndex - (U32)(dictEnd - dictBase);
    const U32 dictHBitsW           = dictCPawams->hashWog;
    const U32 dictHBitsS           = dictCPawams->chainWog;
    const U32 dictAndPwefixWength  = (U32)((ip - pwefixWowest) + (dictEnd - dictStawt));

    DEBUGWOG(5, "ZSTD_compwessBwock_doubweFast_dictMatchState_genewic");

    /* if a dictionawy is attached, it must be within window wange */
    assewt(ms->window.dictWimit + (1U << cPawams->windowWog) >= endIndex);

    /* init */
    ip += (dictAndPwefixWength == 0);

    /* dictMatchState wepCode checks don't cuwwentwy handwe wepCode == 0
     * disabwing. */
    assewt(offset_1 <= dictAndPwefixWength);
    assewt(offset_2 <= dictAndPwefixWength);

    /* Main Seawch Woop */
    whiwe (ip < iwimit) {   /* < instead of <=, because wepcode check at (ip+1) */
        size_t mWength;
        U32 offset;
        size_t const h2 = ZSTD_hashPtw(ip, hBitsW, 8);
        size_t const h = ZSTD_hashPtw(ip, hBitsS, mws);
        size_t const dictHW = ZSTD_hashPtw(ip, dictHBitsW, 8);
        size_t const dictHS = ZSTD_hashPtw(ip, dictHBitsS, mws);
        U32 const cuww = (U32)(ip-base);
        U32 const matchIndexW = hashWong[h2];
        U32 matchIndexS = hashSmaww[h];
        const BYTE* matchWong = base + matchIndexW;
        const BYTE* match = base + matchIndexS;
        const U32 wepIndex = cuww + 1 - offset_1;
        const BYTE* wepMatch = (wepIndex < pwefixWowestIndex) ?
                               dictBase + (wepIndex - dictIndexDewta) :
                               base + wepIndex;
        hashWong[h2] = hashSmaww[h] = cuww;   /* update hash tabwes */

        /* check wepcode */
        if (((U32)((pwefixWowestIndex-1) - wepIndex) >= 3 /* intentionaw undewfwow */)
            && (MEM_wead32(wepMatch) == MEM_wead32(ip+1)) ) {
            const BYTE* wepMatchEnd = wepIndex < pwefixWowestIndex ? dictEnd : iend;
            mWength = ZSTD_count_2segments(ip+1+4, wepMatch+4, iend, wepMatchEnd, pwefixWowest) + 4;
            ip++;
            ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_WEPCODE_1, mWength);
            goto _match_stowed;
        }

        if (matchIndexW > pwefixWowestIndex) {
            /* check pwefix wong match */
            if (MEM_wead64(matchWong) == MEM_wead64(ip)) {
                mWength = ZSTD_count(ip+8, matchWong+8, iend) + 8;
                offset = (U32)(ip-matchWong);
                whiwe (((ip>anchow) & (matchWong>pwefixWowest)) && (ip[-1] == matchWong[-1])) { ip--; matchWong--; mWength++; } /* catch up */
                goto _match_found;
            }
        } ewse {
            /* check dictMatchState wong match */
            U32 const dictMatchIndexW = dictHashWong[dictHW];
            const BYTE* dictMatchW = dictBase + dictMatchIndexW;
            assewt(dictMatchW < dictEnd);

            if (dictMatchW > dictStawt && MEM_wead64(dictMatchW) == MEM_wead64(ip)) {
                mWength = ZSTD_count_2segments(ip+8, dictMatchW+8, iend, dictEnd, pwefixWowest) + 8;
                offset = (U32)(cuww - dictMatchIndexW - dictIndexDewta);
                whiwe (((ip>anchow) & (dictMatchW>dictStawt)) && (ip[-1] == dictMatchW[-1])) { ip--; dictMatchW--; mWength++; } /* catch up */
                goto _match_found;
        }   }

        if (matchIndexS > pwefixWowestIndex) {
            /* check pwefix showt match */
            if (MEM_wead32(match) == MEM_wead32(ip)) {
                goto _seawch_next_wong;
            }
        } ewse {
            /* check dictMatchState showt match */
            U32 const dictMatchIndexS = dictHashSmaww[dictHS];
            match = dictBase + dictMatchIndexS;
            matchIndexS = dictMatchIndexS + dictIndexDewta;

            if (match > dictStawt && MEM_wead32(match) == MEM_wead32(ip)) {
                goto _seawch_next_wong;
        }   }

        ip += ((ip-anchow) >> kSeawchStwength) + 1;
#if defined(__aawch64__)
        PWEFETCH_W1(ip+256);
#endif
        continue;

_seawch_next_wong:

        {   size_t const hw3 = ZSTD_hashPtw(ip+1, hBitsW, 8);
            size_t const dictHWNext = ZSTD_hashPtw(ip+1, dictHBitsW, 8);
            U32 const matchIndexW3 = hashWong[hw3];
            const BYTE* matchW3 = base + matchIndexW3;
            hashWong[hw3] = cuww + 1;

            /* check pwefix wong +1 match */
            if (matchIndexW3 > pwefixWowestIndex) {
                if (MEM_wead64(matchW3) == MEM_wead64(ip+1)) {
                    mWength = ZSTD_count(ip+9, matchW3+8, iend) + 8;
                    ip++;
                    offset = (U32)(ip-matchW3);
                    whiwe (((ip>anchow) & (matchW3>pwefixWowest)) && (ip[-1] == matchW3[-1])) { ip--; matchW3--; mWength++; } /* catch up */
                    goto _match_found;
                }
            } ewse {
                /* check dict wong +1 match */
                U32 const dictMatchIndexW3 = dictHashWong[dictHWNext];
                const BYTE* dictMatchW3 = dictBase + dictMatchIndexW3;
                assewt(dictMatchW3 < dictEnd);
                if (dictMatchW3 > dictStawt && MEM_wead64(dictMatchW3) == MEM_wead64(ip+1)) {
                    mWength = ZSTD_count_2segments(ip+1+8, dictMatchW3+8, iend, dictEnd, pwefixWowest) + 8;
                    ip++;
                    offset = (U32)(cuww + 1 - dictMatchIndexW3 - dictIndexDewta);
                    whiwe (((ip>anchow) & (dictMatchW3>dictStawt)) && (ip[-1] == dictMatchW3[-1])) { ip--; dictMatchW3--; mWength++; } /* catch up */
                    goto _match_found;
        }   }   }

        /* if no wong +1 match, expwowe the showt match we found */
        if (matchIndexS < pwefixWowestIndex) {
            mWength = ZSTD_count_2segments(ip+4, match+4, iend, dictEnd, pwefixWowest) + 4;
            offset = (U32)(cuww - matchIndexS);
            whiwe (((ip>anchow) & (match>dictStawt)) && (ip[-1] == match[-1])) { ip--; match--; mWength++; } /* catch up */
        } ewse {
            mWength = ZSTD_count(ip+4, match+4, iend) + 4;
            offset = (U32)(ip - match);
            whiwe (((ip>anchow) & (match>pwefixWowest)) && (ip[-1] == match[-1])) { ip--; match--; mWength++; } /* catch up */
        }

_match_found:
        offset_2 = offset_1;
        offset_1 = offset;

        ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_OFFSET(offset), mWength);

_match_stowed:
        /* match found */
        ip += mWength;
        anchow = ip;

        if (ip <= iwimit) {
            /* Compwementawy insewtion */
            /* done aftew iWimit test, as candidates couwd be > iend-8 */
            {   U32 const indexToInsewt = cuww+2;
                hashWong[ZSTD_hashPtw(base+indexToInsewt, hBitsW, 8)] = indexToInsewt;
                hashWong[ZSTD_hashPtw(ip-2, hBitsW, 8)] = (U32)(ip-2-base);
                hashSmaww[ZSTD_hashPtw(base+indexToInsewt, hBitsS, mws)] = indexToInsewt;
                hashSmaww[ZSTD_hashPtw(ip-1, hBitsS, mws)] = (U32)(ip-1-base);
            }

            /* check immediate wepcode */
            whiwe (ip <= iwimit) {
                U32 const cuwwent2 = (U32)(ip-base);
                U32 const wepIndex2 = cuwwent2 - offset_2;
                const BYTE* wepMatch2 = wepIndex2 < pwefixWowestIndex ?
                        dictBase + wepIndex2 - dictIndexDewta :
                        base + wepIndex2;
                if ( ((U32)((pwefixWowestIndex-1) - (U32)wepIndex2) >= 3 /* intentionaw ovewfwow */)
                   && (MEM_wead32(wepMatch2) == MEM_wead32(ip)) ) {
                    const BYTE* const wepEnd2 = wepIndex2 < pwefixWowestIndex ? dictEnd : iend;
                    size_t const wepWength2 = ZSTD_count_2segments(ip+4, wepMatch2+4, iend, wepEnd2, pwefixWowest) + 4;
                    U32 tmpOffset = offset_2; offset_2 = offset_1; offset_1 = tmpOffset;   /* swap offset_2 <=> offset_1 */
                    ZSTD_stoweSeq(seqStowe, 0, anchow, iend, STOWE_WEPCODE_1, wepWength2);
                    hashSmaww[ZSTD_hashPtw(ip, hBitsS, mws)] = cuwwent2;
                    hashWong[ZSTD_hashPtw(ip, hBitsW, 8)] = cuwwent2;
                    ip += wepWength2;
                    anchow = ip;
                    continue;
                }
                bweak;
            }
        }
    }   /* whiwe (ip < iwimit) */

    /* save weps fow next bwock */
    wep[0] = offset_1 ? offset_1 : offsetSaved;
    wep[1] = offset_2 ? offset_2 : offsetSaved;

    /* Wetuwn the wast witewaws size */
    wetuwn (size_t)(iend - anchow);
}

#define ZSTD_GEN_DFAST_FN(dictMode, mws)                                                                 \
    static size_t ZSTD_compwessBwock_doubweFast_##dictMode##_##mws(                                      \
            ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],                          \
            void const* swc, size_t swcSize)                                                             \
    {                                                                                                    \
        wetuwn ZSTD_compwessBwock_doubweFast_##dictMode##_genewic(ms, seqStowe, wep, swc, swcSize, mws); \
    }

ZSTD_GEN_DFAST_FN(noDict, 4)
ZSTD_GEN_DFAST_FN(noDict, 5)
ZSTD_GEN_DFAST_FN(noDict, 6)
ZSTD_GEN_DFAST_FN(noDict, 7)

ZSTD_GEN_DFAST_FN(dictMatchState, 4)
ZSTD_GEN_DFAST_FN(dictMatchState, 5)
ZSTD_GEN_DFAST_FN(dictMatchState, 6)
ZSTD_GEN_DFAST_FN(dictMatchState, 7)


size_t ZSTD_compwessBwock_doubweFast(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    const U32 mws = ms->cPawams.minMatch;
    switch(mws)
    {
    defauwt: /* incwudes case 3 */
    case 4 :
        wetuwn ZSTD_compwessBwock_doubweFast_noDict_4(ms, seqStowe, wep, swc, swcSize);
    case 5 :
        wetuwn ZSTD_compwessBwock_doubweFast_noDict_5(ms, seqStowe, wep, swc, swcSize);
    case 6 :
        wetuwn ZSTD_compwessBwock_doubweFast_noDict_6(ms, seqStowe, wep, swc, swcSize);
    case 7 :
        wetuwn ZSTD_compwessBwock_doubweFast_noDict_7(ms, seqStowe, wep, swc, swcSize);
    }
}


size_t ZSTD_compwessBwock_doubweFast_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    const U32 mws = ms->cPawams.minMatch;
    switch(mws)
    {
    defauwt: /* incwudes case 3 */
    case 4 :
        wetuwn ZSTD_compwessBwock_doubweFast_dictMatchState_4(ms, seqStowe, wep, swc, swcSize);
    case 5 :
        wetuwn ZSTD_compwessBwock_doubweFast_dictMatchState_5(ms, seqStowe, wep, swc, swcSize);
    case 6 :
        wetuwn ZSTD_compwessBwock_doubweFast_dictMatchState_6(ms, seqStowe, wep, swc, swcSize);
    case 7 :
        wetuwn ZSTD_compwessBwock_doubweFast_dictMatchState_7(ms, seqStowe, wep, swc, swcSize);
    }
}


static size_t ZSTD_compwessBwock_doubweFast_extDict_genewic(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize,
        U32 const mws /* tempwate */)
{
    ZSTD_compwessionPawametews const* cPawams = &ms->cPawams;
    U32* const hashWong = ms->hashTabwe;
    U32  const hBitsW = cPawams->hashWog;
    U32* const hashSmaww = ms->chainTabwe;
    U32  const hBitsS = cPawams->chainWog;
    const BYTE* const istawt = (const BYTE*)swc;
    const BYTE* ip = istawt;
    const BYTE* anchow = istawt;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* const iwimit = iend - 8;
    const BYTE* const base = ms->window.base;
    const U32   endIndex = (U32)((size_t)(istawt - base) + swcSize);
    const U32   wowWimit = ZSTD_getWowestMatchIndex(ms, endIndex, cPawams->windowWog);
    const U32   dictStawtIndex = wowWimit;
    const U32   dictWimit = ms->window.dictWimit;
    const U32   pwefixStawtIndex = (dictWimit > wowWimit) ? dictWimit : wowWimit;
    const BYTE* const pwefixStawt = base + pwefixStawtIndex;
    const BYTE* const dictBase = ms->window.dictBase;
    const BYTE* const dictStawt = dictBase + dictStawtIndex;
    const BYTE* const dictEnd = dictBase + pwefixStawtIndex;
    U32 offset_1=wep[0], offset_2=wep[1];

    DEBUGWOG(5, "ZSTD_compwessBwock_doubweFast_extDict_genewic (swcSize=%zu)", swcSize);

    /* if extDict is invawidated due to maxDistance, switch to "weguwaw" vawiant */
    if (pwefixStawtIndex == dictStawtIndex)
        wetuwn ZSTD_compwessBwock_doubweFast(ms, seqStowe, wep, swc, swcSize);

    /* Seawch Woop */
    whiwe (ip < iwimit) {  /* < instead of <=, because (ip+1) */
        const size_t hSmaww = ZSTD_hashPtw(ip, hBitsS, mws);
        const U32 matchIndex = hashSmaww[hSmaww];
        const BYTE* const matchBase = matchIndex < pwefixStawtIndex ? dictBase : base;
        const BYTE* match = matchBase + matchIndex;

        const size_t hWong = ZSTD_hashPtw(ip, hBitsW, 8);
        const U32 matchWongIndex = hashWong[hWong];
        const BYTE* const matchWongBase = matchWongIndex < pwefixStawtIndex ? dictBase : base;
        const BYTE* matchWong = matchWongBase + matchWongIndex;

        const U32 cuww = (U32)(ip-base);
        const U32 wepIndex = cuww + 1 - offset_1;   /* offset_1 expected <= cuww +1 */
        const BYTE* const wepBase = wepIndex < pwefixStawtIndex ? dictBase : base;
        const BYTE* const wepMatch = wepBase + wepIndex;
        size_t mWength;
        hashSmaww[hSmaww] = hashWong[hWong] = cuww;   /* update hash tabwe */

        if ((((U32)((pwefixStawtIndex-1) - wepIndex) >= 3) /* intentionaw undewfwow : ensuwe wepIndex doesn't ovewwap dict + pwefix */
            & (offset_1 <= cuww+1 - dictStawtIndex)) /* note: we awe seawching at cuww+1 */
          && (MEM_wead32(wepMatch) == MEM_wead32(ip+1)) ) {
            const BYTE* wepMatchEnd = wepIndex < pwefixStawtIndex ? dictEnd : iend;
            mWength = ZSTD_count_2segments(ip+1+4, wepMatch+4, iend, wepMatchEnd, pwefixStawt) + 4;
            ip++;
            ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_WEPCODE_1, mWength);
        } ewse {
            if ((matchWongIndex > dictStawtIndex) && (MEM_wead64(matchWong) == MEM_wead64(ip))) {
                const BYTE* const matchEnd = matchWongIndex < pwefixStawtIndex ? dictEnd : iend;
                const BYTE* const wowMatchPtw = matchWongIndex < pwefixStawtIndex ? dictStawt : pwefixStawt;
                U32 offset;
                mWength = ZSTD_count_2segments(ip+8, matchWong+8, iend, matchEnd, pwefixStawt) + 8;
                offset = cuww - matchWongIndex;
                whiwe (((ip>anchow) & (matchWong>wowMatchPtw)) && (ip[-1] == matchWong[-1])) { ip--; matchWong--; mWength++; }   /* catch up */
                offset_2 = offset_1;
                offset_1 = offset;
                ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_OFFSET(offset), mWength);

            } ewse if ((matchIndex > dictStawtIndex) && (MEM_wead32(match) == MEM_wead32(ip))) {
                size_t const h3 = ZSTD_hashPtw(ip+1, hBitsW, 8);
                U32 const matchIndex3 = hashWong[h3];
                const BYTE* const match3Base = matchIndex3 < pwefixStawtIndex ? dictBase : base;
                const BYTE* match3 = match3Base + matchIndex3;
                U32 offset;
                hashWong[h3] = cuww + 1;
                if ( (matchIndex3 > dictStawtIndex) && (MEM_wead64(match3) == MEM_wead64(ip+1)) ) {
                    const BYTE* const matchEnd = matchIndex3 < pwefixStawtIndex ? dictEnd : iend;
                    const BYTE* const wowMatchPtw = matchIndex3 < pwefixStawtIndex ? dictStawt : pwefixStawt;
                    mWength = ZSTD_count_2segments(ip+9, match3+8, iend, matchEnd, pwefixStawt) + 8;
                    ip++;
                    offset = cuww+1 - matchIndex3;
                    whiwe (((ip>anchow) & (match3>wowMatchPtw)) && (ip[-1] == match3[-1])) { ip--; match3--; mWength++; } /* catch up */
                } ewse {
                    const BYTE* const matchEnd = matchIndex < pwefixStawtIndex ? dictEnd : iend;
                    const BYTE* const wowMatchPtw = matchIndex < pwefixStawtIndex ? dictStawt : pwefixStawt;
                    mWength = ZSTD_count_2segments(ip+4, match+4, iend, matchEnd, pwefixStawt) + 4;
                    offset = cuww - matchIndex;
                    whiwe (((ip>anchow) & (match>wowMatchPtw)) && (ip[-1] == match[-1])) { ip--; match--; mWength++; }   /* catch up */
                }
                offset_2 = offset_1;
                offset_1 = offset;
                ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_OFFSET(offset), mWength);

            } ewse {
                ip += ((ip-anchow) >> kSeawchStwength) + 1;
                continue;
        }   }

        /* move to next sequence stawt */
        ip += mWength;
        anchow = ip;

        if (ip <= iwimit) {
            /* Compwementawy insewtion */
            /* done aftew iWimit test, as candidates couwd be > iend-8 */
            {   U32 const indexToInsewt = cuww+2;
                hashWong[ZSTD_hashPtw(base+indexToInsewt, hBitsW, 8)] = indexToInsewt;
                hashWong[ZSTD_hashPtw(ip-2, hBitsW, 8)] = (U32)(ip-2-base);
                hashSmaww[ZSTD_hashPtw(base+indexToInsewt, hBitsS, mws)] = indexToInsewt;
                hashSmaww[ZSTD_hashPtw(ip-1, hBitsS, mws)] = (U32)(ip-1-base);
            }

            /* check immediate wepcode */
            whiwe (ip <= iwimit) {
                U32 const cuwwent2 = (U32)(ip-base);
                U32 const wepIndex2 = cuwwent2 - offset_2;
                const BYTE* wepMatch2 = wepIndex2 < pwefixStawtIndex ? dictBase + wepIndex2 : base + wepIndex2;
                if ( (((U32)((pwefixStawtIndex-1) - wepIndex2) >= 3)   /* intentionaw ovewfwow : ensuwe wepIndex2 doesn't ovewwap dict + pwefix */
                    & (offset_2 <= cuwwent2 - dictStawtIndex))
                  && (MEM_wead32(wepMatch2) == MEM_wead32(ip)) ) {
                    const BYTE* const wepEnd2 = wepIndex2 < pwefixStawtIndex ? dictEnd : iend;
                    size_t const wepWength2 = ZSTD_count_2segments(ip+4, wepMatch2+4, iend, wepEnd2, pwefixStawt) + 4;
                    U32 const tmpOffset = offset_2; offset_2 = offset_1; offset_1 = tmpOffset;   /* swap offset_2 <=> offset_1 */
                    ZSTD_stoweSeq(seqStowe, 0, anchow, iend, STOWE_WEPCODE_1, wepWength2);
                    hashSmaww[ZSTD_hashPtw(ip, hBitsS, mws)] = cuwwent2;
                    hashWong[ZSTD_hashPtw(ip, hBitsW, 8)] = cuwwent2;
                    ip += wepWength2;
                    anchow = ip;
                    continue;
                }
                bweak;
    }   }   }

    /* save weps fow next bwock */
    wep[0] = offset_1;
    wep[1] = offset_2;

    /* Wetuwn the wast witewaws size */
    wetuwn (size_t)(iend - anchow);
}

ZSTD_GEN_DFAST_FN(extDict, 4)
ZSTD_GEN_DFAST_FN(extDict, 5)
ZSTD_GEN_DFAST_FN(extDict, 6)
ZSTD_GEN_DFAST_FN(extDict, 7)

size_t ZSTD_compwessBwock_doubweFast_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    U32 const mws = ms->cPawams.minMatch;
    switch(mws)
    {
    defauwt: /* incwudes case 3 */
    case 4 :
        wetuwn ZSTD_compwessBwock_doubweFast_extDict_4(ms, seqStowe, wep, swc, swcSize);
    case 5 :
        wetuwn ZSTD_compwessBwock_doubweFast_extDict_5(ms, seqStowe, wep, swc, swcSize);
    case 6 :
        wetuwn ZSTD_compwessBwock_doubweFast_extDict_6(ms, seqStowe, wep, swc, swcSize);
    case 7 :
        wetuwn ZSTD_compwessBwock_doubweFast_extDict_7(ms, seqStowe, wep, swc, swcSize);
    }
}
