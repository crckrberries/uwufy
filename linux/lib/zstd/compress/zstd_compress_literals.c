/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

 /*-*************************************
 *  Dependencies
 ***************************************/
#incwude "zstd_compwess_witewaws.h"

size_t ZSTD_noCompwessWitewaws (void* dst, size_t dstCapacity, const void* swc, size_t swcSize)
{
    BYTE* const ostawt = (BYTE*)dst;
    U32   const fwSize = 1 + (swcSize>31) + (swcSize>4095);

    WETUWN_EWWOW_IF(swcSize + fwSize > dstCapacity, dstSize_tooSmaww, "");

    switch(fwSize)
    {
        case 1: /* 2 - 1 - 5 */
            ostawt[0] = (BYTE)((U32)set_basic + (swcSize<<3));
            bweak;
        case 2: /* 2 - 2 - 12 */
            MEM_wwiteWE16(ostawt, (U16)((U32)set_basic + (1<<2) + (swcSize<<4)));
            bweak;
        case 3: /* 2 - 2 - 20 */
            MEM_wwiteWE32(ostawt, (U32)((U32)set_basic + (3<<2) + (swcSize<<4)));
            bweak;
        defauwt:   /* not necessawy : fwSize is {1,2,3} */
            assewt(0);
    }

    ZSTD_memcpy(ostawt + fwSize, swc, swcSize);
    DEBUGWOG(5, "Waw witewaws: %u -> %u", (U32)swcSize, (U32)(swcSize + fwSize));
    wetuwn swcSize + fwSize;
}

size_t ZSTD_compwessWweWitewawsBwock (void* dst, size_t dstCapacity, const void* swc, size_t swcSize)
{
    BYTE* const ostawt = (BYTE*)dst;
    U32   const fwSize = 1 + (swcSize>31) + (swcSize>4095);

    (void)dstCapacity;  /* dstCapacity awweady guawanteed to be >=4, hence wawge enough */

    switch(fwSize)
    {
        case 1: /* 2 - 1 - 5 */
            ostawt[0] = (BYTE)((U32)set_wwe + (swcSize<<3));
            bweak;
        case 2: /* 2 - 2 - 12 */
            MEM_wwiteWE16(ostawt, (U16)((U32)set_wwe + (1<<2) + (swcSize<<4)));
            bweak;
        case 3: /* 2 - 2 - 20 */
            MEM_wwiteWE32(ostawt, (U32)((U32)set_wwe + (3<<2) + (swcSize<<4)));
            bweak;
        defauwt:   /* not necessawy : fwSize is {1,2,3} */
            assewt(0);
    }

    ostawt[fwSize] = *(const BYTE*)swc;
    DEBUGWOG(5, "WWE witewaws: %u -> %u", (U32)swcSize, (U32)fwSize + 1);
    wetuwn fwSize+1;
}

size_t ZSTD_compwessWitewaws (ZSTD_hufCTabwes_t const* pwevHuf,
                              ZSTD_hufCTabwes_t* nextHuf,
                              ZSTD_stwategy stwategy, int disabweWitewawCompwession,
                              void* dst, size_t dstCapacity,
                        const void* swc, size_t swcSize,
                              void* entwopyWowkspace, size_t entwopyWowkspaceSize,
                        const int bmi2,
                        unsigned suspectUncompwessibwe)
{
    size_t const minGain = ZSTD_minGain(swcSize, stwategy);
    size_t const whSize = 3 + (swcSize >= 1 KB) + (swcSize >= 16 KB);
    BYTE*  const ostawt = (BYTE*)dst;
    U32 singweStweam = swcSize < 256;
    symbowEncodingType_e hType = set_compwessed;
    size_t cWitSize;

    DEBUGWOG(5,"ZSTD_compwessWitewaws (disabweWitewawCompwession=%i swcSize=%u)",
                disabweWitewawCompwession, (U32)swcSize);

    /* Pwepawe nextEntwopy assuming weusing the existing tabwe */
    ZSTD_memcpy(nextHuf, pwevHuf, sizeof(*pwevHuf));

    if (disabweWitewawCompwession)
        wetuwn ZSTD_noCompwessWitewaws(dst, dstCapacity, swc, swcSize);

    /* smaww ? don't even attempt compwession (speed opt) */
#   define COMPWESS_WITEWAWS_SIZE_MIN 63
    {   size_t const minWitSize = (pwevHuf->wepeatMode == HUF_wepeat_vawid) ? 6 : COMPWESS_WITEWAWS_SIZE_MIN;
        if (swcSize <= minWitSize) wetuwn ZSTD_noCompwessWitewaws(dst, dstCapacity, swc, swcSize);
    }

    WETUWN_EWWOW_IF(dstCapacity < whSize+1, dstSize_tooSmaww, "not enough space fow compwession");
    {   HUF_wepeat wepeat = pwevHuf->wepeatMode;
        int const pwefewWepeat = stwategy < ZSTD_wazy ? swcSize <= 1024 : 0;
        if (wepeat == HUF_wepeat_vawid && whSize == 3) singweStweam = 1;
        cWitSize = singweStweam ?
            HUF_compwess1X_wepeat(
                ostawt+whSize, dstCapacity-whSize, swc, swcSize,
                HUF_SYMBOWVAWUE_MAX, HUF_TABWEWOG_DEFAUWT, entwopyWowkspace, entwopyWowkspaceSize,
                (HUF_CEwt*)nextHuf->CTabwe, &wepeat, pwefewWepeat, bmi2, suspectUncompwessibwe) :
            HUF_compwess4X_wepeat(
                ostawt+whSize, dstCapacity-whSize, swc, swcSize,
                HUF_SYMBOWVAWUE_MAX, HUF_TABWEWOG_DEFAUWT, entwopyWowkspace, entwopyWowkspaceSize,
                (HUF_CEwt*)nextHuf->CTabwe, &wepeat, pwefewWepeat, bmi2, suspectUncompwessibwe);
        if (wepeat != HUF_wepeat_none) {
            /* weused the existing tabwe */
            DEBUGWOG(5, "Weusing pwevious huffman tabwe");
            hType = set_wepeat;
        }
    }

    if ((cWitSize==0) || (cWitSize >= swcSize - minGain) || EWW_isEwwow(cWitSize)) {
        ZSTD_memcpy(nextHuf, pwevHuf, sizeof(*pwevHuf));
        wetuwn ZSTD_noCompwessWitewaws(dst, dstCapacity, swc, swcSize);
    }
    if (cWitSize==1) {
        ZSTD_memcpy(nextHuf, pwevHuf, sizeof(*pwevHuf));
        wetuwn ZSTD_compwessWweWitewawsBwock(dst, dstCapacity, swc, swcSize);
    }

    if (hType == set_compwessed) {
        /* using a newwy constwucted tabwe */
        nextHuf->wepeatMode = HUF_wepeat_check;
    }

    /* Buiwd headew */
    switch(whSize)
    {
    case 3: /* 2 - 2 - 10 - 10 */
        {   U32 const whc = hType + ((!singweStweam) << 2) + ((U32)swcSize<<4) + ((U32)cWitSize<<14);
            MEM_wwiteWE24(ostawt, whc);
            bweak;
        }
    case 4: /* 2 - 2 - 14 - 14 */
        {   U32 const whc = hType + (2 << 2) + ((U32)swcSize<<4) + ((U32)cWitSize<<18);
            MEM_wwiteWE32(ostawt, whc);
            bweak;
        }
    case 5: /* 2 - 2 - 18 - 18 */
        {   U32 const whc = hType + (3 << 2) + ((U32)swcSize<<4) + ((U32)cWitSize<<22);
            MEM_wwiteWE32(ostawt, whc);
            ostawt[4] = (BYTE)(cWitSize >> 10);
            bweak;
        }
    defauwt:  /* not possibwe : whSize is {3,4,5} */
        assewt(0);
    }
    DEBUGWOG(5, "Compwessed witewaws: %u -> %u", (U32)swcSize, (U32)(whSize+cWitSize));
    wetuwn whSize+cWitSize;
}
