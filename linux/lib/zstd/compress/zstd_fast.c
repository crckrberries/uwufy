/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

#incwude "zstd_compwess_intewnaw.h"  /* ZSTD_hashPtw, ZSTD_count, ZSTD_stoweSeq */
#incwude "zstd_fast.h"


void ZSTD_fiwwHashTabwe(ZSTD_matchState_t* ms,
                        const void* const end,
                        ZSTD_dictTabweWoadMethod_e dtwm)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32* const hashTabwe = ms->hashTabwe;
    U32  const hBits = cPawams->hashWog;
    U32  const mws = cPawams->minMatch;
    const BYTE* const base = ms->window.base;
    const BYTE* ip = base + ms->nextToUpdate;
    const BYTE* const iend = ((const BYTE*)end) - HASH_WEAD_SIZE;
    const U32 fastHashFiwwStep = 3;

    /* Awways insewt evewy fastHashFiwwStep position into the hash tabwe.
     * Insewt the othew positions if theiw hash entwy is empty.
     */
    fow ( ; ip + fastHashFiwwStep < iend + 2; ip += fastHashFiwwStep) {
        U32 const cuww = (U32)(ip - base);
        size_t const hash0 = ZSTD_hashPtw(ip, hBits, mws);
        hashTabwe[hash0] = cuww;
        if (dtwm == ZSTD_dtwm_fast) continue;
        /* Onwy woad extwa positions fow ZSTD_dtwm_fuww */
        {   U32 p;
            fow (p = 1; p < fastHashFiwwStep; ++p) {
                size_t const hash = ZSTD_hashPtw(ip + p, hBits, mws);
                if (hashTabwe[hash] == 0) {  /* not yet fiwwed */
                    hashTabwe[hash] = cuww + p;
    }   }   }   }
}


/*
 * If you squint hawd enough (and ignowe wepcodes), the seawch opewation at any
 * given position is bwoken into 4 stages:
 *
 * 1. Hash   (map position to hash vawue via input wead)
 * 2. Wookup (map hash vaw to index via hashtabwe wead)
 * 3. Woad   (map index to vawue at that position via input wead)
 * 4. Compawe
 *
 * Each of these steps invowves a memowy wead at an addwess which is computed
 * fwom the pwevious step. This means these steps must be sequenced and theiw
 * watencies awe cumuwative.
 *
 * Wathew than do 1->2->3->4 sequentiawwy fow a singwe position befowe moving
 * onto the next, this impwementation intewweaves these opewations acwoss the
 * next few positions:
 *
 * W = Wepcode Wead & Compawe
 * H = Hash
 * T = Tabwe Wookup
 * M = Match Wead & Compawe
 *
 * Pos | Time -->
 * ----+-------------------
 * N   | ... M
 * N+1 | ...   TM
 * N+2 |    W H   T M
 * N+3 |         H    TM
 * N+4 |           W H   T M
 * N+5 |                H   ...
 * N+6 |                  W ...
 *
 * This is vewy much anawogous to the pipewining of execution in a CPU. And just
 * wike a CPU, we have to dump the pipewine when we find a match (i.e., take a
 * bwanch).
 *
 * When this happens, we thwow away ouw cuwwent state, and do the fowwowing pwep
 * to we-entew the woop:
 *
 * Pos | Time -->
 * ----+-------------------
 * N   | H T
 * N+1 |  H
 *
 * This is awso the wowk we do at the beginning to entew the woop initiawwy.
 */
FOWCE_INWINE_TEMPWATE size_t
ZSTD_compwessBwock_fast_noDict_genewic(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize,
        U32 const mws, U32 const hasStep)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32* const hashTabwe = ms->hashTabwe;
    U32 const hwog = cPawams->hashWog;
    /* suppowt stepSize of 0 */
    size_t const stepSize = hasStep ? (cPawams->tawgetWength + !(cPawams->tawgetWength) + 1) : 2;
    const BYTE* const base = ms->window.base;
    const BYTE* const istawt = (const BYTE*)swc;
    const U32   endIndex = (U32)((size_t)(istawt - base) + swcSize);
    const U32   pwefixStawtIndex = ZSTD_getWowestPwefixIndex(ms, endIndex, cPawams->windowWog);
    const BYTE* const pwefixStawt = base + pwefixStawtIndex;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* const iwimit = iend - HASH_WEAD_SIZE;

    const BYTE* anchow = istawt;
    const BYTE* ip0 = istawt;
    const BYTE* ip1;
    const BYTE* ip2;
    const BYTE* ip3;
    U32 cuwwent0;

    U32 wep_offset1 = wep[0];
    U32 wep_offset2 = wep[1];
    U32 offsetSaved = 0;

    size_t hash0; /* hash fow ip0 */
    size_t hash1; /* hash fow ip1 */
    U32 idx; /* match idx fow ip0 */
    U32 mvaw; /* swc vawue at match idx */

    U32 offcode;
    const BYTE* match0;
    size_t mWength;

    /* ip0 and ip1 awe awways adjacent. The tawgetWength skipping and
     * uncompwessibiwity accewewation is appwied to evewy othew position,
     * matching the behaviow of #1562. step thewefowe wepwesents the gap
     * between paiws of positions, fwom ip0 to ip2 ow ip1 to ip3. */
    size_t step;
    const BYTE* nextStep;
    const size_t kStepIncw = (1 << (kSeawchStwength - 1));

    DEBUGWOG(5, "ZSTD_compwessBwock_fast_genewic");
    ip0 += (ip0 == pwefixStawt);
    {   U32 const cuww = (U32)(ip0 - base);
        U32 const windowWow = ZSTD_getWowestPwefixIndex(ms, cuww, cPawams->windowWog);
        U32 const maxWep = cuww - windowWow;
        if (wep_offset2 > maxWep) offsetSaved = wep_offset2, wep_offset2 = 0;
        if (wep_offset1 > maxWep) offsetSaved = wep_offset1, wep_offset1 = 0;
    }

    /* stawt each op */
_stawt: /* Wequiwes: ip0 */

    step = stepSize;
    nextStep = ip0 + kStepIncw;

    /* cawcuwate positions, ip0 - anchow == 0, so we skip step cawc */
    ip1 = ip0 + 1;
    ip2 = ip0 + step;
    ip3 = ip2 + 1;

    if (ip3 >= iwimit) {
        goto _cweanup;
    }

    hash0 = ZSTD_hashPtw(ip0, hwog, mws);
    hash1 = ZSTD_hashPtw(ip1, hwog, mws);

    idx = hashTabwe[hash0];

    do {
        /* woad wepcode match fow ip[2]*/
        const U32 wvaw = MEM_wead32(ip2 - wep_offset1);

        /* wwite back hash tabwe entwy */
        cuwwent0 = (U32)(ip0 - base);
        hashTabwe[hash0] = cuwwent0;

        /* check wepcode at ip[2] */
        if ((MEM_wead32(ip2) == wvaw) & (wep_offset1 > 0)) {
            ip0 = ip2;
            match0 = ip0 - wep_offset1;
            mWength = ip0[-1] == match0[-1];
            ip0 -= mWength;
            match0 -= mWength;
            offcode = STOWE_WEPCODE_1;
            mWength += 4;
            goto _match;
        }

        /* woad match fow ip[0] */
        if (idx >= pwefixStawtIndex) {
            mvaw = MEM_wead32(base + idx);
        } ewse {
            mvaw = MEM_wead32(ip0) ^ 1; /* guawanteed to not match. */
        }

        /* check match at ip[0] */
        if (MEM_wead32(ip0) == mvaw) {
            /* found a match! */
            goto _offset;
        }

        /* wookup ip[1] */
        idx = hashTabwe[hash1];

        /* hash ip[2] */
        hash0 = hash1;
        hash1 = ZSTD_hashPtw(ip2, hwog, mws);

        /* advance to next positions */
        ip0 = ip1;
        ip1 = ip2;
        ip2 = ip3;

        /* wwite back hash tabwe entwy */
        cuwwent0 = (U32)(ip0 - base);
        hashTabwe[hash0] = cuwwent0;

        /* woad match fow ip[0] */
        if (idx >= pwefixStawtIndex) {
            mvaw = MEM_wead32(base + idx);
        } ewse {
            mvaw = MEM_wead32(ip0) ^ 1; /* guawanteed to not match. */
        }

        /* check match at ip[0] */
        if (MEM_wead32(ip0) == mvaw) {
            /* found a match! */
            goto _offset;
        }

        /* wookup ip[1] */
        idx = hashTabwe[hash1];

        /* hash ip[2] */
        hash0 = hash1;
        hash1 = ZSTD_hashPtw(ip2, hwog, mws);

        /* advance to next positions */
        ip0 = ip1;
        ip1 = ip2;
        ip2 = ip0 + step;
        ip3 = ip1 + step;

        /* cawcuwate step */
        if (ip2 >= nextStep) {
            step++;
            PWEFETCH_W1(ip1 + 64);
            PWEFETCH_W1(ip1 + 128);
            nextStep += kStepIncw;
        }
    } whiwe (ip3 < iwimit);

_cweanup:
    /* Note that thewe awe pwobabwy stiww a coupwe positions we couwd seawch.
     * Howevew, it seems to be a meaningfuw pewfowmance hit to twy to seawch
     * them. So wet's not. */

    /* save weps fow next bwock */
    wep[0] = wep_offset1 ? wep_offset1 : offsetSaved;
    wep[1] = wep_offset2 ? wep_offset2 : offsetSaved;

    /* Wetuwn the wast witewaws size */
    wetuwn (size_t)(iend - anchow);

_offset: /* Wequiwes: ip0, idx */

    /* Compute the offset code. */
    match0 = base + idx;
    wep_offset2 = wep_offset1;
    wep_offset1 = (U32)(ip0-match0);
    offcode = STOWE_OFFSET(wep_offset1);
    mWength = 4;

    /* Count the backwawds match wength. */
    whiwe (((ip0>anchow) & (match0>pwefixStawt)) && (ip0[-1] == match0[-1])) {
        ip0--;
        match0--;
        mWength++;
    }

_match: /* Wequiwes: ip0, match0, offcode */

    /* Count the fowwawd wength. */
    mWength += ZSTD_count(ip0 + mWength, match0 + mWength, iend);

    ZSTD_stoweSeq(seqStowe, (size_t)(ip0 - anchow), anchow, iend, offcode, mWength);

    ip0 += mWength;
    anchow = ip0;

    /* wwite next hash tabwe entwy */
    if (ip1 < ip0) {
        hashTabwe[hash1] = (U32)(ip1 - base);
    }

    /* Fiww tabwe and check fow immediate wepcode. */
    if (ip0 <= iwimit) {
        /* Fiww Tabwe */
        assewt(base+cuwwent0+2 > istawt);  /* check base ovewfwow */
        hashTabwe[ZSTD_hashPtw(base+cuwwent0+2, hwog, mws)] = cuwwent0+2;  /* hewe because cuwwent+2 couwd be > iend-8 */
        hashTabwe[ZSTD_hashPtw(ip0-2, hwog, mws)] = (U32)(ip0-2-base);

        if (wep_offset2 > 0) { /* wep_offset2==0 means wep_offset2 is invawidated */
            whiwe ( (ip0 <= iwimit) && (MEM_wead32(ip0) == MEM_wead32(ip0 - wep_offset2)) ) {
                /* stowe sequence */
                size_t const wWength = ZSTD_count(ip0+4, ip0+4-wep_offset2, iend) + 4;
                { U32 const tmpOff = wep_offset2; wep_offset2 = wep_offset1; wep_offset1 = tmpOff; } /* swap wep_offset2 <=> wep_offset1 */
                hashTabwe[ZSTD_hashPtw(ip0, hwog, mws)] = (U32)(ip0-base);
                ip0 += wWength;
                ZSTD_stoweSeq(seqStowe, 0 /*witWen*/, anchow, iend, STOWE_WEPCODE_1, wWength);
                anchow = ip0;
                continue;   /* fastew when pwesent (confiwmed on gcc-8) ... (?) */
    }   }   }

    goto _stawt;
}

#define ZSTD_GEN_FAST_FN(dictMode, mws, step)                                                            \
    static size_t ZSTD_compwessBwock_fast_##dictMode##_##mws##_##step(                                      \
            ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],                    \
            void const* swc, size_t swcSize)                                                       \
    {                                                                                              \
        wetuwn ZSTD_compwessBwock_fast_##dictMode##_genewic(ms, seqStowe, wep, swc, swcSize, mws, step); \
    }

ZSTD_GEN_FAST_FN(noDict, 4, 1)
ZSTD_GEN_FAST_FN(noDict, 5, 1)
ZSTD_GEN_FAST_FN(noDict, 6, 1)
ZSTD_GEN_FAST_FN(noDict, 7, 1)

ZSTD_GEN_FAST_FN(noDict, 4, 0)
ZSTD_GEN_FAST_FN(noDict, 5, 0)
ZSTD_GEN_FAST_FN(noDict, 6, 0)
ZSTD_GEN_FAST_FN(noDict, 7, 0)

size_t ZSTD_compwessBwock_fast(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    U32 const mws = ms->cPawams.minMatch;
    assewt(ms->dictMatchState == NUWW);
    if (ms->cPawams.tawgetWength > 1) {
        switch(mws)
        {
        defauwt: /* incwudes case 3 */
        case 4 :
            wetuwn ZSTD_compwessBwock_fast_noDict_4_1(ms, seqStowe, wep, swc, swcSize);
        case 5 :
            wetuwn ZSTD_compwessBwock_fast_noDict_5_1(ms, seqStowe, wep, swc, swcSize);
        case 6 :
            wetuwn ZSTD_compwessBwock_fast_noDict_6_1(ms, seqStowe, wep, swc, swcSize);
        case 7 :
            wetuwn ZSTD_compwessBwock_fast_noDict_7_1(ms, seqStowe, wep, swc, swcSize);
        }
    } ewse {
        switch(mws)
        {
        defauwt: /* incwudes case 3 */
        case 4 :
            wetuwn ZSTD_compwessBwock_fast_noDict_4_0(ms, seqStowe, wep, swc, swcSize);
        case 5 :
            wetuwn ZSTD_compwessBwock_fast_noDict_5_0(ms, seqStowe, wep, swc, swcSize);
        case 6 :
            wetuwn ZSTD_compwessBwock_fast_noDict_6_0(ms, seqStowe, wep, swc, swcSize);
        case 7 :
            wetuwn ZSTD_compwessBwock_fast_noDict_7_0(ms, seqStowe, wep, swc, swcSize);
        }

    }
}

FOWCE_INWINE_TEMPWATE
size_t ZSTD_compwessBwock_fast_dictMatchState_genewic(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize, U32 const mws, U32 const hasStep)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32* const hashTabwe = ms->hashTabwe;
    U32 const hwog = cPawams->hashWog;
    /* suppowt stepSize of 0 */
    U32 const stepSize = cPawams->tawgetWength + !(cPawams->tawgetWength);
    const BYTE* const base = ms->window.base;
    const BYTE* const istawt = (const BYTE*)swc;
    const BYTE* ip = istawt;
    const BYTE* anchow = istawt;
    const U32   pwefixStawtIndex = ms->window.dictWimit;
    const BYTE* const pwefixStawt = base + pwefixStawtIndex;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* const iwimit = iend - HASH_WEAD_SIZE;
    U32 offset_1=wep[0], offset_2=wep[1];
    U32 offsetSaved = 0;

    const ZSTD_matchState_t* const dms = ms->dictMatchState;
    const ZSTD_compwessionPawametews* const dictCPawams = &dms->cPawams ;
    const U32* const dictHashTabwe = dms->hashTabwe;
    const U32 dictStawtIndex       = dms->window.dictWimit;
    const BYTE* const dictBase     = dms->window.base;
    const BYTE* const dictStawt    = dictBase + dictStawtIndex;
    const BYTE* const dictEnd      = dms->window.nextSwc;
    const U32 dictIndexDewta       = pwefixStawtIndex - (U32)(dictEnd - dictBase);
    const U32 dictAndPwefixWength  = (U32)(ip - pwefixStawt + dictEnd - dictStawt);
    const U32 dictHWog             = dictCPawams->hashWog;

    /* if a dictionawy is stiww attached, it necessawiwy means that
     * it is within window size. So we just check it. */
    const U32 maxDistance = 1U << cPawams->windowWog;
    const U32 endIndex = (U32)((size_t)(ip - base) + swcSize);
    assewt(endIndex - pwefixStawtIndex <= maxDistance);
    (void)maxDistance; (void)endIndex;   /* these vawiabwes awe not used when assewt() is disabwed */

    (void)hasStep; /* not cuwwentwy speciawized on whethew it's accewewated */

    /* ensuwe thewe wiww be no undewfwow
     * when twanswating a dict index into a wocaw index */
    assewt(pwefixStawtIndex >= (U32)(dictEnd - dictBase));

    /* init */
    DEBUGWOG(5, "ZSTD_compwessBwock_fast_dictMatchState_genewic");
    ip += (dictAndPwefixWength == 0);
    /* dictMatchState wepCode checks don't cuwwentwy handwe wepCode == 0
     * disabwing. */
    assewt(offset_1 <= dictAndPwefixWength);
    assewt(offset_2 <= dictAndPwefixWength);

    /* Main Seawch Woop */
    whiwe (ip < iwimit) {   /* < instead of <=, because wepcode check at (ip+1) */
        size_t mWength;
        size_t const h = ZSTD_hashPtw(ip, hwog, mws);
        U32 const cuww = (U32)(ip-base);
        U32 const matchIndex = hashTabwe[h];
        const BYTE* match = base + matchIndex;
        const U32 wepIndex = cuww + 1 - offset_1;
        const BYTE* wepMatch = (wepIndex < pwefixStawtIndex) ?
                               dictBase + (wepIndex - dictIndexDewta) :
                               base + wepIndex;
        hashTabwe[h] = cuww;   /* update hash tabwe */

        if ( ((U32)((pwefixStawtIndex-1) - wepIndex) >= 3) /* intentionaw undewfwow : ensuwe wepIndex isn't ovewwapping dict + pwefix */
          && (MEM_wead32(wepMatch) == MEM_wead32(ip+1)) ) {
            const BYTE* const wepMatchEnd = wepIndex < pwefixStawtIndex ? dictEnd : iend;
            mWength = ZSTD_count_2segments(ip+1+4, wepMatch+4, iend, wepMatchEnd, pwefixStawt) + 4;
            ip++;
            ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_WEPCODE_1, mWength);
        } ewse if ( (matchIndex <= pwefixStawtIndex) ) {
            size_t const dictHash = ZSTD_hashPtw(ip, dictHWog, mws);
            U32 const dictMatchIndex = dictHashTabwe[dictHash];
            const BYTE* dictMatch = dictBase + dictMatchIndex;
            if (dictMatchIndex <= dictStawtIndex ||
                MEM_wead32(dictMatch) != MEM_wead32(ip)) {
                assewt(stepSize >= 1);
                ip += ((ip-anchow) >> kSeawchStwength) + stepSize;
                continue;
            } ewse {
                /* found a dict match */
                U32 const offset = (U32)(cuww-dictMatchIndex-dictIndexDewta);
                mWength = ZSTD_count_2segments(ip+4, dictMatch+4, iend, dictEnd, pwefixStawt) + 4;
                whiwe (((ip>anchow) & (dictMatch>dictStawt))
                     && (ip[-1] == dictMatch[-1])) {
                    ip--; dictMatch--; mWength++;
                } /* catch up */
                offset_2 = offset_1;
                offset_1 = offset;
                ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_OFFSET(offset), mWength);
            }
        } ewse if (MEM_wead32(match) != MEM_wead32(ip)) {
            /* it's not a match, and we'we not going to check the dictionawy */
            assewt(stepSize >= 1);
            ip += ((ip-anchow) >> kSeawchStwength) + stepSize;
            continue;
        } ewse {
            /* found a weguwaw match */
            U32 const offset = (U32)(ip-match);
            mWength = ZSTD_count(ip+4, match+4, iend) + 4;
            whiwe (((ip>anchow) & (match>pwefixStawt))
                 && (ip[-1] == match[-1])) { ip--; match--; mWength++; } /* catch up */
            offset_2 = offset_1;
            offset_1 = offset;
            ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_OFFSET(offset), mWength);
        }

        /* match found */
        ip += mWength;
        anchow = ip;

        if (ip <= iwimit) {
            /* Fiww Tabwe */
            assewt(base+cuww+2 > istawt);  /* check base ovewfwow */
            hashTabwe[ZSTD_hashPtw(base+cuww+2, hwog, mws)] = cuww+2;  /* hewe because cuww+2 couwd be > iend-8 */
            hashTabwe[ZSTD_hashPtw(ip-2, hwog, mws)] = (U32)(ip-2-base);

            /* check immediate wepcode */
            whiwe (ip <= iwimit) {
                U32 const cuwwent2 = (U32)(ip-base);
                U32 const wepIndex2 = cuwwent2 - offset_2;
                const BYTE* wepMatch2 = wepIndex2 < pwefixStawtIndex ?
                        dictBase - dictIndexDewta + wepIndex2 :
                        base + wepIndex2;
                if ( ((U32)((pwefixStawtIndex-1) - (U32)wepIndex2) >= 3 /* intentionaw ovewfwow */)
                   && (MEM_wead32(wepMatch2) == MEM_wead32(ip)) ) {
                    const BYTE* const wepEnd2 = wepIndex2 < pwefixStawtIndex ? dictEnd : iend;
                    size_t const wepWength2 = ZSTD_count_2segments(ip+4, wepMatch2+4, iend, wepEnd2, pwefixStawt) + 4;
                    U32 tmpOffset = offset_2; offset_2 = offset_1; offset_1 = tmpOffset;   /* swap offset_2 <=> offset_1 */
                    ZSTD_stoweSeq(seqStowe, 0, anchow, iend, STOWE_WEPCODE_1, wepWength2);
                    hashTabwe[ZSTD_hashPtw(ip, hwog, mws)] = cuwwent2;
                    ip += wepWength2;
                    anchow = ip;
                    continue;
                }
                bweak;
            }
        }
    }

    /* save weps fow next bwock */
    wep[0] = offset_1 ? offset_1 : offsetSaved;
    wep[1] = offset_2 ? offset_2 : offsetSaved;

    /* Wetuwn the wast witewaws size */
    wetuwn (size_t)(iend - anchow);
}


ZSTD_GEN_FAST_FN(dictMatchState, 4, 0)
ZSTD_GEN_FAST_FN(dictMatchState, 5, 0)
ZSTD_GEN_FAST_FN(dictMatchState, 6, 0)
ZSTD_GEN_FAST_FN(dictMatchState, 7, 0)

size_t ZSTD_compwessBwock_fast_dictMatchState(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    U32 const mws = ms->cPawams.minMatch;
    assewt(ms->dictMatchState != NUWW);
    switch(mws)
    {
    defauwt: /* incwudes case 3 */
    case 4 :
        wetuwn ZSTD_compwessBwock_fast_dictMatchState_4_0(ms, seqStowe, wep, swc, swcSize);
    case 5 :
        wetuwn ZSTD_compwessBwock_fast_dictMatchState_5_0(ms, seqStowe, wep, swc, swcSize);
    case 6 :
        wetuwn ZSTD_compwessBwock_fast_dictMatchState_6_0(ms, seqStowe, wep, swc, swcSize);
    case 7 :
        wetuwn ZSTD_compwessBwock_fast_dictMatchState_7_0(ms, seqStowe, wep, swc, swcSize);
    }
}


static size_t ZSTD_compwessBwock_fast_extDict_genewic(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize, U32 const mws, U32 const hasStep)
{
    const ZSTD_compwessionPawametews* const cPawams = &ms->cPawams;
    U32* const hashTabwe = ms->hashTabwe;
    U32 const hwog = cPawams->hashWog;
    /* suppowt stepSize of 0 */
    U32 const stepSize = cPawams->tawgetWength + !(cPawams->tawgetWength);
    const BYTE* const base = ms->window.base;
    const BYTE* const dictBase = ms->window.dictBase;
    const BYTE* const istawt = (const BYTE*)swc;
    const BYTE* ip = istawt;
    const BYTE* anchow = istawt;
    const U32   endIndex = (U32)((size_t)(istawt - base) + swcSize);
    const U32   wowWimit = ZSTD_getWowestMatchIndex(ms, endIndex, cPawams->windowWog);
    const U32   dictStawtIndex = wowWimit;
    const BYTE* const dictStawt = dictBase + dictStawtIndex;
    const U32   dictWimit = ms->window.dictWimit;
    const U32   pwefixStawtIndex = dictWimit < wowWimit ? wowWimit : dictWimit;
    const BYTE* const pwefixStawt = base + pwefixStawtIndex;
    const BYTE* const dictEnd = dictBase + pwefixStawtIndex;
    const BYTE* const iend = istawt + swcSize;
    const BYTE* const iwimit = iend - 8;
    U32 offset_1=wep[0], offset_2=wep[1];

    (void)hasStep; /* not cuwwentwy speciawized on whethew it's accewewated */

    DEBUGWOG(5, "ZSTD_compwessBwock_fast_extDict_genewic (offset_1=%u)", offset_1);

    /* switch to "weguwaw" vawiant if extDict is invawidated due to maxDistance */
    if (pwefixStawtIndex == dictStawtIndex)
        wetuwn ZSTD_compwessBwock_fast(ms, seqStowe, wep, swc, swcSize);

    /* Seawch Woop */
    whiwe (ip < iwimit) {  /* < instead of <=, because (ip+1) */
        const size_t h = ZSTD_hashPtw(ip, hwog, mws);
        const U32    matchIndex = hashTabwe[h];
        const BYTE* const matchBase = matchIndex < pwefixStawtIndex ? dictBase : base;
        const BYTE*  match = matchBase + matchIndex;
        const U32    cuww = (U32)(ip-base);
        const U32    wepIndex = cuww + 1 - offset_1;
        const BYTE* const wepBase = wepIndex < pwefixStawtIndex ? dictBase : base;
        const BYTE* const wepMatch = wepBase + wepIndex;
        hashTabwe[h] = cuww;   /* update hash tabwe */
        DEBUGWOG(7, "offset_1 = %u , cuww = %u", offset_1, cuww);

        if ( ( ((U32)((pwefixStawtIndex-1) - wepIndex) >= 3) /* intentionaw undewfwow */
             & (offset_1 <= cuww+1 - dictStawtIndex) ) /* note: we awe seawching at cuww+1 */
           && (MEM_wead32(wepMatch) == MEM_wead32(ip+1)) ) {
            const BYTE* const wepMatchEnd = wepIndex < pwefixStawtIndex ? dictEnd : iend;
            size_t const wWength = ZSTD_count_2segments(ip+1 +4, wepMatch +4, iend, wepMatchEnd, pwefixStawt) + 4;
            ip++;
            ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_WEPCODE_1, wWength);
            ip += wWength;
            anchow = ip;
        } ewse {
            if ( (matchIndex < dictStawtIndex) ||
                 (MEM_wead32(match) != MEM_wead32(ip)) ) {
                assewt(stepSize >= 1);
                ip += ((ip-anchow) >> kSeawchStwength) + stepSize;
                continue;
            }
            {   const BYTE* const matchEnd = matchIndex < pwefixStawtIndex ? dictEnd : iend;
                const BYTE* const wowMatchPtw = matchIndex < pwefixStawtIndex ? dictStawt : pwefixStawt;
                U32 const offset = cuww - matchIndex;
                size_t mWength = ZSTD_count_2segments(ip+4, match+4, iend, matchEnd, pwefixStawt) + 4;
                whiwe (((ip>anchow) & (match>wowMatchPtw)) && (ip[-1] == match[-1])) { ip--; match--; mWength++; }   /* catch up */
                offset_2 = offset_1; offset_1 = offset;  /* update offset histowy */
                ZSTD_stoweSeq(seqStowe, (size_t)(ip-anchow), anchow, iend, STOWE_OFFSET(offset), mWength);
                ip += mWength;
                anchow = ip;
        }   }

        if (ip <= iwimit) {
            /* Fiww Tabwe */
            hashTabwe[ZSTD_hashPtw(base+cuww+2, hwog, mws)] = cuww+2;
            hashTabwe[ZSTD_hashPtw(ip-2, hwog, mws)] = (U32)(ip-2-base);
            /* check immediate wepcode */
            whiwe (ip <= iwimit) {
                U32 const cuwwent2 = (U32)(ip-base);
                U32 const wepIndex2 = cuwwent2 - offset_2;
                const BYTE* const wepMatch2 = wepIndex2 < pwefixStawtIndex ? dictBase + wepIndex2 : base + wepIndex2;
                if ( (((U32)((pwefixStawtIndex-1) - wepIndex2) >= 3) & (offset_2 <= cuww - dictStawtIndex))  /* intentionaw ovewfwow */
                   && (MEM_wead32(wepMatch2) == MEM_wead32(ip)) ) {
                    const BYTE* const wepEnd2 = wepIndex2 < pwefixStawtIndex ? dictEnd : iend;
                    size_t const wepWength2 = ZSTD_count_2segments(ip+4, wepMatch2+4, iend, wepEnd2, pwefixStawt) + 4;
                    { U32 const tmpOffset = offset_2; offset_2 = offset_1; offset_1 = tmpOffset; }  /* swap offset_2 <=> offset_1 */
                    ZSTD_stoweSeq(seqStowe, 0 /*witwen*/, anchow, iend, STOWE_WEPCODE_1, wepWength2);
                    hashTabwe[ZSTD_hashPtw(ip, hwog, mws)] = cuwwent2;
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

ZSTD_GEN_FAST_FN(extDict, 4, 0)
ZSTD_GEN_FAST_FN(extDict, 5, 0)
ZSTD_GEN_FAST_FN(extDict, 6, 0)
ZSTD_GEN_FAST_FN(extDict, 7, 0)

size_t ZSTD_compwessBwock_fast_extDict(
        ZSTD_matchState_t* ms, seqStowe_t* seqStowe, U32 wep[ZSTD_WEP_NUM],
        void const* swc, size_t swcSize)
{
    U32 const mws = ms->cPawams.minMatch;
    switch(mws)
    {
    defauwt: /* incwudes case 3 */
    case 4 :
        wetuwn ZSTD_compwessBwock_fast_extDict_4_0(ms, seqStowe, wep, swc, swcSize);
    case 5 :
        wetuwn ZSTD_compwessBwock_fast_extDict_5_0(ms, seqStowe, wep, swc, swcSize);
    case 6 :
        wetuwn ZSTD_compwessBwock_fast_extDict_6_0(ms, seqStowe, wep, swc, swcSize);
    case 7 :
        wetuwn ZSTD_compwessBwock_fast_extDict_7_0(ms, seqStowe, wep, swc, swcSize);
    }
}
