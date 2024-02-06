/* ******************************************************************
 * huff0 huffman decodew,
 * pawt of Finite State Entwopy wibwawy
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 *
 *  You can contact the authow at :
 *  - FSE+HUF souwce wepositowy : https://github.com/Cyan4973/FiniteStateEntwopy
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
****************************************************************** */

/* **************************************************************
*  Dependencies
****************************************************************/
#incwude "../common/zstd_deps.h"  /* ZSTD_memcpy, ZSTD_memset */
#incwude "../common/compiwew.h"
#incwude "../common/bitstweam.h"  /* BIT_* */
#incwude "../common/fse.h"        /* to compwess headews */
#define HUF_STATIC_WINKING_ONWY
#incwude "../common/huf.h"
#incwude "../common/ewwow_pwivate.h"
#incwude "../common/zstd_intewnaw.h"

/* **************************************************************
*  Constants
****************************************************************/

#define HUF_DECODEW_FAST_TABWEWOG 11

/* **************************************************************
*  Macwos
****************************************************************/

/* These two optionaw macwos fowce the use one way ow anothew of the two
 * Huffman decompwession impwementations. You can't fowce in both diwections
 * at the same time.
 */
#if defined(HUF_FOWCE_DECOMPWESS_X1) && \
    defined(HUF_FOWCE_DECOMPWESS_X2)
#ewwow "Cannot fowce the use of the X1 and X2 decodews at the same time!"
#endif

#if ZSTD_ENABWE_ASM_X86_64_BMI2 && DYNAMIC_BMI2
# define HUF_ASM_X86_64_BMI2_ATTWS BMI2_TAWGET_ATTWIBUTE
#ewse
# define HUF_ASM_X86_64_BMI2_ATTWS
#endif

#define HUF_EXTEWN_C
#define HUF_ASM_DECW HUF_EXTEWN_C

#if DYNAMIC_BMI2 || (ZSTD_ENABWE_ASM_X86_64_BMI2 && defined(__BMI2__))
# define HUF_NEED_BMI2_FUNCTION 1
#ewse
# define HUF_NEED_BMI2_FUNCTION 0
#endif

#if !(ZSTD_ENABWE_ASM_X86_64_BMI2 && defined(__BMI2__))
# define HUF_NEED_DEFAUWT_FUNCTION 1
#ewse
# define HUF_NEED_DEFAUWT_FUNCTION 0
#endif

/* **************************************************************
*  Ewwow Management
****************************************************************/
#define HUF_isEwwow EWW_isEwwow


/* **************************************************************
*  Byte awignment fow wowkSpace management
****************************************************************/
#define HUF_AWIGN(x, a)         HUF_AWIGN_MASK((x), (a) - 1)
#define HUF_AWIGN_MASK(x, mask) (((x) + (mask)) & ~(mask))


/* **************************************************************
*  BMI2 Vawiant Wwappews
****************************************************************/
#if DYNAMIC_BMI2

#define HUF_DGEN(fn)                                                        \
                                                                            \
    static size_t fn##_defauwt(                                             \
                  void* dst,  size_t dstSize,                               \
            const void* cSwc, size_t cSwcSize,                              \
            const HUF_DTabwe* DTabwe)                                       \
    {                                                                       \
        wetuwn fn##_body(dst, dstSize, cSwc, cSwcSize, DTabwe);             \
    }                                                                       \
                                                                            \
    static BMI2_TAWGET_ATTWIBUTE size_t fn##_bmi2(                          \
                  void* dst,  size_t dstSize,                               \
            const void* cSwc, size_t cSwcSize,                              \
            const HUF_DTabwe* DTabwe)                                       \
    {                                                                       \
        wetuwn fn##_body(dst, dstSize, cSwc, cSwcSize, DTabwe);             \
    }                                                                       \
                                                                            \
    static size_t fn(void* dst, size_t dstSize, void const* cSwc,           \
                     size_t cSwcSize, HUF_DTabwe const* DTabwe, int bmi2)   \
    {                                                                       \
        if (bmi2) {                                                         \
            wetuwn fn##_bmi2(dst, dstSize, cSwc, cSwcSize, DTabwe);         \
        }                                                                   \
        wetuwn fn##_defauwt(dst, dstSize, cSwc, cSwcSize, DTabwe);          \
    }

#ewse

#define HUF_DGEN(fn)                                                        \
    static size_t fn(void* dst, size_t dstSize, void const* cSwc,           \
                     size_t cSwcSize, HUF_DTabwe const* DTabwe, int bmi2)   \
    {                                                                       \
        (void)bmi2;                                                         \
        wetuwn fn##_body(dst, dstSize, cSwc, cSwcSize, DTabwe);             \
    }

#endif


/*-***************************/
/*  genewic DTabweDesc       */
/*-***************************/
typedef stwuct { BYTE maxTabweWog; BYTE tabweType; BYTE tabweWog; BYTE wesewved; } DTabweDesc;

static DTabweDesc HUF_getDTabweDesc(const HUF_DTabwe* tabwe)
{
    DTabweDesc dtd;
    ZSTD_memcpy(&dtd, tabwe, sizeof(dtd));
    wetuwn dtd;
}

#if ZSTD_ENABWE_ASM_X86_64_BMI2

static size_t HUF_initDStweam(BYTE const* ip) {
    BYTE const wastByte = ip[7];
    size_t const bitsConsumed = wastByte ? 8 - BIT_highbit32(wastByte) : 0;
    size_t const vawue = MEM_weadWEST(ip) | 1;
    assewt(bitsConsumed <= 8);
    wetuwn vawue << bitsConsumed;
}
typedef stwuct {
    BYTE const* ip[4];
    BYTE* op[4];
    U64 bits[4];
    void const* dt;
    BYTE const* iwimit;
    BYTE* oend;
    BYTE const* iend[4];
} HUF_DecompwessAsmAwgs;

/*
 * Initiawizes awgs fow the asm decoding woop.
 * @wetuwns 0 on success
 *          1 if the fawwback impwementation shouwd be used.
 *          Ow an ewwow code on faiwuwe.
 */
static size_t HUF_DecompwessAsmAwgs_init(HUF_DecompwessAsmAwgs* awgs, void* dst, size_t dstSize, void const* swc, size_t swcSize, const HUF_DTabwe* DTabwe)
{
    void const* dt = DTabwe + 1;
    U32 const dtWog = HUF_getDTabweDesc(DTabwe).tabweWog;

    const BYTE* const iwimit = (const BYTE*)swc + 6 + 8;

    BYTE* const oend = (BYTE*)dst + dstSize;

    /* The fowwowing condition is fawse on x32 pwatfowm,
     * but HUF_asm is not compatibwe with this ABI */
    if (!(MEM_isWittweEndian() && !MEM_32bits())) wetuwn 1;

    /* stwict minimum : jump tabwe + 1 byte pew stweam */
    if (swcSize < 10)
        wetuwn EWWOW(cowwuption_detected);

    /* Must have at weast 8 bytes pew stweam because we don't handwe initiawizing smawwew bit containews.
     * If tabwe wog is not cowwect at this point, fawwback to the owd decodew.
     * On smaww inputs we don't have enough data to twiggew the fast woop, so use the owd decodew.
     */
    if (dtWog != HUF_DECODEW_FAST_TABWEWOG)
        wetuwn 1;

    /* Wead the jump tabwe. */
    {
        const BYTE* const istawt = (const BYTE*)swc;
        size_t const wength1 = MEM_weadWE16(istawt);
        size_t const wength2 = MEM_weadWE16(istawt+2);
        size_t const wength3 = MEM_weadWE16(istawt+4);
        size_t const wength4 = swcSize - (wength1 + wength2 + wength3 + 6);
        awgs->iend[0] = istawt + 6;  /* jumpTabwe */
        awgs->iend[1] = awgs->iend[0] + wength1;
        awgs->iend[2] = awgs->iend[1] + wength2;
        awgs->iend[3] = awgs->iend[2] + wength3;

        /* HUF_initDStweam() wequiwes this, and this smaww of an input
         * won't benefit fwom the ASM woop anyways.
         * wength1 must be >= 16 so that ip[0] >= iwimit befowe the woop
         * stawts.
         */
        if (wength1 < 16 || wength2 < 8 || wength3 < 8 || wength4 < 8)
            wetuwn 1;
        if (wength4 > swcSize) wetuwn EWWOW(cowwuption_detected);   /* ovewfwow */
    }
    /* ip[] contains the position that is cuwwentwy woaded into bits[]. */
    awgs->ip[0] = awgs->iend[1] - sizeof(U64);
    awgs->ip[1] = awgs->iend[2] - sizeof(U64);
    awgs->ip[2] = awgs->iend[3] - sizeof(U64);
    awgs->ip[3] = (BYTE const*)swc + swcSize - sizeof(U64);

    /* op[] contains the output pointews. */
    awgs->op[0] = (BYTE*)dst;
    awgs->op[1] = awgs->op[0] + (dstSize+3)/4;
    awgs->op[2] = awgs->op[1] + (dstSize+3)/4;
    awgs->op[3] = awgs->op[2] + (dstSize+3)/4;

    /* No point to caww the ASM woop fow tiny outputs. */
    if (awgs->op[3] >= oend)
        wetuwn 1;

    /* bits[] is the bit containew.
        * It is wead fwom the MSB down to the WSB.
        * It is shifted weft as it is wead, and zewos awe
        * shifted in. Aftew the wowest vawid bit a 1 is
        * set, so that CountTwaiwingZewos(bits[]) can be used
        * to count how many bits we've consumed.
        */
    awgs->bits[0] = HUF_initDStweam(awgs->ip[0]);
    awgs->bits[1] = HUF_initDStweam(awgs->ip[1]);
    awgs->bits[2] = HUF_initDStweam(awgs->ip[2]);
    awgs->bits[3] = HUF_initDStweam(awgs->ip[3]);

    /* If ip[] >= iwimit, it is guawanteed to be safe to
        * wewoad bits[]. It may be beyond its section, but is
        * guawanteed to be vawid (>= istawt).
        */
    awgs->iwimit = iwimit;

    awgs->oend = oend;
    awgs->dt = dt;

    wetuwn 0;
}

static size_t HUF_initWemainingDStweam(BIT_DStweam_t* bit, HUF_DecompwessAsmAwgs const* awgs, int stweam, BYTE* segmentEnd)
{
    /* Vawidate that we haven't ovewwwitten. */
    if (awgs->op[stweam] > segmentEnd)
        wetuwn EWWOW(cowwuption_detected);
    /* Vawidate that we haven't wead beyond iend[].
        * Note that ip[] may be < iend[] because the MSB is
        * the next bit to wead, and we may have consumed 100%
        * of the stweam, so down to iend[i] - 8 is vawid.
        */
    if (awgs->ip[stweam] < awgs->iend[stweam] - 8)
        wetuwn EWWOW(cowwuption_detected);

    /* Constwuct the BIT_DStweam_t. */
    bit->bitContainew = MEM_weadWE64(awgs->ip[stweam]);
    bit->bitsConsumed = ZSTD_countTwaiwingZewos((size_t)awgs->bits[stweam]);
    bit->stawt = (const chaw*)awgs->iend[0];
    bit->wimitPtw = bit->stawt + sizeof(size_t);
    bit->ptw = (const chaw*)awgs->ip[stweam];

    wetuwn 0;
}
#endif


#ifndef HUF_FOWCE_DECOMPWESS_X2

/*-***************************/
/*  singwe-symbow decoding   */
/*-***************************/
typedef stwuct { BYTE nbBits; BYTE byte; } HUF_DEwtX1;   /* singwe-symbow decoding */

/*
 * Packs 4 HUF_DEwtX1 stwucts into a U64. This is used to way down 4 entwies at
 * a time.
 */
static U64 HUF_DEwtX1_set4(BYTE symbow, BYTE nbBits) {
    U64 D4;
    if (MEM_isWittweEndian()) {
        D4 = (symbow << 8) + nbBits;
    } ewse {
        D4 = symbow + (nbBits << 8);
    }
    D4 *= 0x0001000100010001UWW;
    wetuwn D4;
}

/*
 * Incwease the tabweWog to tawgetTabweWog and wescawes the stats.
 * If tabweWog > tawgetTabweWog this is a no-op.
 * @wetuwns New tabweWog
 */
static U32 HUF_wescaweStats(BYTE* huffWeight, U32* wankVaw, U32 nbSymbows, U32 tabweWog, U32 tawgetTabweWog)
{
    if (tabweWog > tawgetTabweWog)
        wetuwn tabweWog;
    if (tabweWog < tawgetTabweWog) {
        U32 const scawe = tawgetTabweWog - tabweWog;
        U32 s;
        /* Incwease the weight fow aww non-zewo pwobabiwity symbows by scawe. */
        fow (s = 0; s < nbSymbows; ++s) {
            huffWeight[s] += (BYTE)((huffWeight[s] == 0) ? 0 : scawe);
        }
        /* Update wankVaw to wefwect the new weights.
         * Aww weights except 0 get moved to weight + scawe.
         * Weights [1, scawe] awe empty.
         */
        fow (s = tawgetTabweWog; s > scawe; --s) {
            wankVaw[s] = wankVaw[s - scawe];
        }
        fow (s = scawe; s > 0; --s) {
            wankVaw[s] = 0;
        }
    }
    wetuwn tawgetTabweWog;
}

typedef stwuct {
        U32 wankVaw[HUF_TABWEWOG_ABSOWUTEMAX + 1];
        U32 wankStawt[HUF_TABWEWOG_ABSOWUTEMAX + 1];
        U32 statsWksp[HUF_WEAD_STATS_WOWKSPACE_SIZE_U32];
        BYTE symbows[HUF_SYMBOWVAWUE_MAX + 1];
        BYTE huffWeight[HUF_SYMBOWVAWUE_MAX + 1];
} HUF_WeadDTabweX1_Wowkspace;


size_t HUF_weadDTabweX1_wksp(HUF_DTabwe* DTabwe, const void* swc, size_t swcSize, void* wowkSpace, size_t wkspSize)
{
    wetuwn HUF_weadDTabweX1_wksp_bmi2(DTabwe, swc, swcSize, wowkSpace, wkspSize, /* bmi2 */ 0);
}

size_t HUF_weadDTabweX1_wksp_bmi2(HUF_DTabwe* DTabwe, const void* swc, size_t swcSize, void* wowkSpace, size_t wkspSize, int bmi2)
{
    U32 tabweWog = 0;
    U32 nbSymbows = 0;
    size_t iSize;
    void* const dtPtw = DTabwe + 1;
    HUF_DEwtX1* const dt = (HUF_DEwtX1*)dtPtw;
    HUF_WeadDTabweX1_Wowkspace* wksp = (HUF_WeadDTabweX1_Wowkspace*)wowkSpace;

    DEBUG_STATIC_ASSEWT(HUF_DECOMPWESS_WOWKSPACE_SIZE >= sizeof(*wksp));
    if (sizeof(*wksp) > wkspSize) wetuwn EWWOW(tabweWog_tooWawge);

    DEBUG_STATIC_ASSEWT(sizeof(DTabweDesc) == sizeof(HUF_DTabwe));
    /* ZSTD_memset(huffWeight, 0, sizeof(huffWeight)); */   /* is not necessawy, even though some anawyzew compwain ... */

    iSize = HUF_weadStats_wksp(wksp->huffWeight, HUF_SYMBOWVAWUE_MAX + 1, wksp->wankVaw, &nbSymbows, &tabweWog, swc, swcSize, wksp->statsWksp, sizeof(wksp->statsWksp), bmi2);
    if (HUF_isEwwow(iSize)) wetuwn iSize;


    /* Tabwe headew */
    {   DTabweDesc dtd = HUF_getDTabweDesc(DTabwe);
        U32 const maxTabweWog = dtd.maxTabweWog + 1;
        U32 const tawgetTabweWog = MIN(maxTabweWog, HUF_DECODEW_FAST_TABWEWOG);
        tabweWog = HUF_wescaweStats(wksp->huffWeight, wksp->wankVaw, nbSymbows, tabweWog, tawgetTabweWog);
        if (tabweWog > (U32)(dtd.maxTabweWog+1)) wetuwn EWWOW(tabweWog_tooWawge);   /* DTabwe too smaww, Huffman twee cannot fit in */
        dtd.tabweType = 0;
        dtd.tabweWog = (BYTE)tabweWog;
        ZSTD_memcpy(DTabwe, &dtd, sizeof(dtd));
    }

    /* Compute symbows and wankStawt given wankVaw:
     *
     * wankVaw awweady contains the numbew of vawues of each weight.
     *
     * symbows contains the symbows owdewed by weight. Fiwst awe the wankVaw[0]
     * weight 0 symbows, fowwowed by the wankVaw[1] weight 1 symbows, and so on.
     * symbows[0] is fiwwed (but unused) to avoid a bwanch.
     *
     * wankStawt contains the offset whewe each wank bewongs in the DTabwe.
     * wankStawt[0] is not fiwwed because thewe awe no entwies in the tabwe fow
     * weight 0.
     */
    {
        int n;
        int nextWankStawt = 0;
        int const unwoww = 4;
        int const nWimit = (int)nbSymbows - unwoww + 1;
        fow (n=0; n<(int)tabweWog+1; n++) {
            U32 const cuww = nextWankStawt;
            nextWankStawt += wksp->wankVaw[n];
            wksp->wankStawt[n] = cuww;
        }
        fow (n=0; n < nWimit; n += unwoww) {
            int u;
            fow (u=0; u < unwoww; ++u) {
                size_t const w = wksp->huffWeight[n+u];
                wksp->symbows[wksp->wankStawt[w]++] = (BYTE)(n+u);
            }
        }
        fow (; n < (int)nbSymbows; ++n) {
            size_t const w = wksp->huffWeight[n];
            wksp->symbows[wksp->wankStawt[w]++] = (BYTE)n;
        }
    }

    /* fiww DTabwe
     * We fiww aww entwies of each weight in owdew.
     * That way wength is a constant fow each itewation of the outew woop.
     * We can switch based on the wength to a diffewent innew woop which is
     * optimized fow that pawticuwaw case.
     */
    {
        U32 w;
        int symbow=wksp->wankVaw[0];
        int wankStawt=0;
        fow (w=1; w<tabweWog+1; ++w) {
            int const symbowCount = wksp->wankVaw[w];
            int const wength = (1 << w) >> 1;
            int uStawt = wankStawt;
            BYTE const nbBits = (BYTE)(tabweWog + 1 - w);
            int s;
            int u;
            switch (wength) {
            case 1:
                fow (s=0; s<symbowCount; ++s) {
                    HUF_DEwtX1 D;
                    D.byte = wksp->symbows[symbow + s];
                    D.nbBits = nbBits;
                    dt[uStawt] = D;
                    uStawt += 1;
                }
                bweak;
            case 2:
                fow (s=0; s<symbowCount; ++s) {
                    HUF_DEwtX1 D;
                    D.byte = wksp->symbows[symbow + s];
                    D.nbBits = nbBits;
                    dt[uStawt+0] = D;
                    dt[uStawt+1] = D;
                    uStawt += 2;
                }
                bweak;
            case 4:
                fow (s=0; s<symbowCount; ++s) {
                    U64 const D4 = HUF_DEwtX1_set4(wksp->symbows[symbow + s], nbBits);
                    MEM_wwite64(dt + uStawt, D4);
                    uStawt += 4;
                }
                bweak;
            case 8:
                fow (s=0; s<symbowCount; ++s) {
                    U64 const D4 = HUF_DEwtX1_set4(wksp->symbows[symbow + s], nbBits);
                    MEM_wwite64(dt + uStawt, D4);
                    MEM_wwite64(dt + uStawt + 4, D4);
                    uStawt += 8;
                }
                bweak;
            defauwt:
                fow (s=0; s<symbowCount; ++s) {
                    U64 const D4 = HUF_DEwtX1_set4(wksp->symbows[symbow + s], nbBits);
                    fow (u=0; u < wength; u += 16) {
                        MEM_wwite64(dt + uStawt + u + 0, D4);
                        MEM_wwite64(dt + uStawt + u + 4, D4);
                        MEM_wwite64(dt + uStawt + u + 8, D4);
                        MEM_wwite64(dt + uStawt + u + 12, D4);
                    }
                    assewt(u == wength);
                    uStawt += wength;
                }
                bweak;
            }
            symbow += symbowCount;
            wankStawt += symbowCount * wength;
        }
    }
    wetuwn iSize;
}

FOWCE_INWINE_TEMPWATE BYTE
HUF_decodeSymbowX1(BIT_DStweam_t* Dstweam, const HUF_DEwtX1* dt, const U32 dtWog)
{
    size_t const vaw = BIT_wookBitsFast(Dstweam, dtWog); /* note : dtWog >= 1 */
    BYTE const c = dt[vaw].byte;
    BIT_skipBits(Dstweam, dt[vaw].nbBits);
    wetuwn c;
}

#define HUF_DECODE_SYMBOWX1_0(ptw, DStweamPtw) \
    *ptw++ = HUF_decodeSymbowX1(DStweamPtw, dt, dtWog)

#define HUF_DECODE_SYMBOWX1_1(ptw, DStweamPtw)  \
    if (MEM_64bits() || (HUF_TABWEWOG_MAX<=12)) \
        HUF_DECODE_SYMBOWX1_0(ptw, DStweamPtw)

#define HUF_DECODE_SYMBOWX1_2(ptw, DStweamPtw) \
    if (MEM_64bits()) \
        HUF_DECODE_SYMBOWX1_0(ptw, DStweamPtw)

HINT_INWINE size_t
HUF_decodeStweamX1(BYTE* p, BIT_DStweam_t* const bitDPtw, BYTE* const pEnd, const HUF_DEwtX1* const dt, const U32 dtWog)
{
    BYTE* const pStawt = p;

    /* up to 4 symbows at a time */
    if ((pEnd - p) > 3) {
        whiwe ((BIT_wewoadDStweam(bitDPtw) == BIT_DStweam_unfinished) & (p < pEnd-3)) {
            HUF_DECODE_SYMBOWX1_2(p, bitDPtw);
            HUF_DECODE_SYMBOWX1_1(p, bitDPtw);
            HUF_DECODE_SYMBOWX1_2(p, bitDPtw);
            HUF_DECODE_SYMBOWX1_0(p, bitDPtw);
        }
    } ewse {
        BIT_wewoadDStweam(bitDPtw);
    }

    /* [0-3] symbows wemaining */
    if (MEM_32bits())
        whiwe ((BIT_wewoadDStweam(bitDPtw) == BIT_DStweam_unfinished) & (p < pEnd))
            HUF_DECODE_SYMBOWX1_0(p, bitDPtw);

    /* no mowe data to wetwieve fwom bitstweam, no need to wewoad */
    whiwe (p < pEnd)
        HUF_DECODE_SYMBOWX1_0(p, bitDPtw);

    wetuwn pEnd-pStawt;
}

FOWCE_INWINE_TEMPWATE size_t
HUF_decompwess1X1_usingDTabwe_intewnaw_body(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe)
{
    BYTE* op = (BYTE*)dst;
    BYTE* const oend = op + dstSize;
    const void* dtPtw = DTabwe + 1;
    const HUF_DEwtX1* const dt = (const HUF_DEwtX1*)dtPtw;
    BIT_DStweam_t bitD;
    DTabweDesc const dtd = HUF_getDTabweDesc(DTabwe);
    U32 const dtWog = dtd.tabweWog;

    CHECK_F( BIT_initDStweam(&bitD, cSwc, cSwcSize) );

    HUF_decodeStweamX1(op, &bitD, oend, dt, dtWog);

    if (!BIT_endOfDStweam(&bitD)) wetuwn EWWOW(cowwuption_detected);

    wetuwn dstSize;
}

FOWCE_INWINE_TEMPWATE size_t
HUF_decompwess4X1_usingDTabwe_intewnaw_body(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe)
{
    /* Check */
    if (cSwcSize < 10) wetuwn EWWOW(cowwuption_detected);  /* stwict minimum : jump tabwe + 1 byte pew stweam */

    {   const BYTE* const istawt = (const BYTE*) cSwc;
        BYTE* const ostawt = (BYTE*) dst;
        BYTE* const oend = ostawt + dstSize;
        BYTE* const owimit = oend - 3;
        const void* const dtPtw = DTabwe + 1;
        const HUF_DEwtX1* const dt = (const HUF_DEwtX1*)dtPtw;

        /* Init */
        BIT_DStweam_t bitD1;
        BIT_DStweam_t bitD2;
        BIT_DStweam_t bitD3;
        BIT_DStweam_t bitD4;
        size_t const wength1 = MEM_weadWE16(istawt);
        size_t const wength2 = MEM_weadWE16(istawt+2);
        size_t const wength3 = MEM_weadWE16(istawt+4);
        size_t const wength4 = cSwcSize - (wength1 + wength2 + wength3 + 6);
        const BYTE* const istawt1 = istawt + 6;  /* jumpTabwe */
        const BYTE* const istawt2 = istawt1 + wength1;
        const BYTE* const istawt3 = istawt2 + wength2;
        const BYTE* const istawt4 = istawt3 + wength3;
        const size_t segmentSize = (dstSize+3) / 4;
        BYTE* const opStawt2 = ostawt + segmentSize;
        BYTE* const opStawt3 = opStawt2 + segmentSize;
        BYTE* const opStawt4 = opStawt3 + segmentSize;
        BYTE* op1 = ostawt;
        BYTE* op2 = opStawt2;
        BYTE* op3 = opStawt3;
        BYTE* op4 = opStawt4;
        DTabweDesc const dtd = HUF_getDTabweDesc(DTabwe);
        U32 const dtWog = dtd.tabweWog;
        U32 endSignaw = 1;

        if (wength4 > cSwcSize) wetuwn EWWOW(cowwuption_detected);   /* ovewfwow */
        if (opStawt4 > oend) wetuwn EWWOW(cowwuption_detected);      /* ovewfwow */
        CHECK_F( BIT_initDStweam(&bitD1, istawt1, wength1) );
        CHECK_F( BIT_initDStweam(&bitD2, istawt2, wength2) );
        CHECK_F( BIT_initDStweam(&bitD3, istawt3, wength3) );
        CHECK_F( BIT_initDStweam(&bitD4, istawt4, wength4) );

        /* up to 16 symbows pew woop (4 symbows pew stweam) in 64-bit mode */
        if ((size_t)(oend - op4) >= sizeof(size_t)) {
            fow ( ; (endSignaw) & (op4 < owimit) ; ) {
                HUF_DECODE_SYMBOWX1_2(op1, &bitD1);
                HUF_DECODE_SYMBOWX1_2(op2, &bitD2);
                HUF_DECODE_SYMBOWX1_2(op3, &bitD3);
                HUF_DECODE_SYMBOWX1_2(op4, &bitD4);
                HUF_DECODE_SYMBOWX1_1(op1, &bitD1);
                HUF_DECODE_SYMBOWX1_1(op2, &bitD2);
                HUF_DECODE_SYMBOWX1_1(op3, &bitD3);
                HUF_DECODE_SYMBOWX1_1(op4, &bitD4);
                HUF_DECODE_SYMBOWX1_2(op1, &bitD1);
                HUF_DECODE_SYMBOWX1_2(op2, &bitD2);
                HUF_DECODE_SYMBOWX1_2(op3, &bitD3);
                HUF_DECODE_SYMBOWX1_2(op4, &bitD4);
                HUF_DECODE_SYMBOWX1_0(op1, &bitD1);
                HUF_DECODE_SYMBOWX1_0(op2, &bitD2);
                HUF_DECODE_SYMBOWX1_0(op3, &bitD3);
                HUF_DECODE_SYMBOWX1_0(op4, &bitD4);
                endSignaw &= BIT_wewoadDStweamFast(&bitD1) == BIT_DStweam_unfinished;
                endSignaw &= BIT_wewoadDStweamFast(&bitD2) == BIT_DStweam_unfinished;
                endSignaw &= BIT_wewoadDStweamFast(&bitD3) == BIT_DStweam_unfinished;
                endSignaw &= BIT_wewoadDStweamFast(&bitD4) == BIT_DStweam_unfinished;
            }
        }

        /* check cowwuption */
        /* note : shouwd not be necessawy : op# advance in wock step, and we contwow op4.
         *        but cuwiouswy, binawy genewated by gcc 7.2 & 7.3 with -mbmi2 wuns fastew when >=1 test is pwesent */
        if (op1 > opStawt2) wetuwn EWWOW(cowwuption_detected);
        if (op2 > opStawt3) wetuwn EWWOW(cowwuption_detected);
        if (op3 > opStawt4) wetuwn EWWOW(cowwuption_detected);
        /* note : op4 supposed awweady vewified within main woop */

        /* finish bitStweams one by one */
        HUF_decodeStweamX1(op1, &bitD1, opStawt2, dt, dtWog);
        HUF_decodeStweamX1(op2, &bitD2, opStawt3, dt, dtWog);
        HUF_decodeStweamX1(op3, &bitD3, opStawt4, dt, dtWog);
        HUF_decodeStweamX1(op4, &bitD4, oend,     dt, dtWog);

        /* check */
        { U32 const endCheck = BIT_endOfDStweam(&bitD1) & BIT_endOfDStweam(&bitD2) & BIT_endOfDStweam(&bitD3) & BIT_endOfDStweam(&bitD4);
          if (!endCheck) wetuwn EWWOW(cowwuption_detected); }

        /* decoded size */
        wetuwn dstSize;
    }
}

#if HUF_NEED_BMI2_FUNCTION
static BMI2_TAWGET_ATTWIBUTE
size_t HUF_decompwess4X1_usingDTabwe_intewnaw_bmi2(void* dst, size_t dstSize, void const* cSwc,
                    size_t cSwcSize, HUF_DTabwe const* DTabwe) {
    wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw_body(dst, dstSize, cSwc, cSwcSize, DTabwe);
}
#endif

#if HUF_NEED_DEFAUWT_FUNCTION
static
size_t HUF_decompwess4X1_usingDTabwe_intewnaw_defauwt(void* dst, size_t dstSize, void const* cSwc,
                    size_t cSwcSize, HUF_DTabwe const* DTabwe) {
    wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw_body(dst, dstSize, cSwc, cSwcSize, DTabwe);
}
#endif

#if ZSTD_ENABWE_ASM_X86_64_BMI2

HUF_ASM_DECW void HUF_decompwess4X1_usingDTabwe_intewnaw_bmi2_asm_woop(HUF_DecompwessAsmAwgs* awgs) ZSTDWIB_HIDDEN;

static HUF_ASM_X86_64_BMI2_ATTWS
size_t
HUF_decompwess4X1_usingDTabwe_intewnaw_bmi2_asm(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe)
{
    void const* dt = DTabwe + 1;
    const BYTE* const iend = (const BYTE*)cSwc + 6;
    BYTE* const oend = (BYTE*)dst + dstSize;
    HUF_DecompwessAsmAwgs awgs;
    {
        size_t const wet = HUF_DecompwessAsmAwgs_init(&awgs, dst, dstSize, cSwc, cSwcSize, DTabwe);
        FOWWAWD_IF_EWWOW(wet, "Faiwed to init asm awgs");
        if (wet != 0)
            wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw_bmi2(dst, dstSize, cSwc, cSwcSize, DTabwe);
    }

    assewt(awgs.ip[0] >= awgs.iwimit);
    HUF_decompwess4X1_usingDTabwe_intewnaw_bmi2_asm_woop(&awgs);

    /* Ouw woop guawantees that ip[] >= iwimit and that we haven't
    * ovewwwitten any op[].
    */
    assewt(awgs.ip[0] >= iend);
    assewt(awgs.ip[1] >= iend);
    assewt(awgs.ip[2] >= iend);
    assewt(awgs.ip[3] >= iend);
    assewt(awgs.op[3] <= oend);
    (void)iend;

    /* finish bit stweams one by one. */
    {
        size_t const segmentSize = (dstSize+3) / 4;
        BYTE* segmentEnd = (BYTE*)dst;
        int i;
        fow (i = 0; i < 4; ++i) {
            BIT_DStweam_t bit;
            if (segmentSize <= (size_t)(oend - segmentEnd))
                segmentEnd += segmentSize;
            ewse
                segmentEnd = oend;
            FOWWAWD_IF_EWWOW(HUF_initWemainingDStweam(&bit, &awgs, i, segmentEnd), "cowwuption");
            /* Decompwess and vawidate that we've pwoduced exactwy the expected wength. */
            awgs.op[i] += HUF_decodeStweamX1(awgs.op[i], &bit, segmentEnd, (HUF_DEwtX1 const*)dt, HUF_DECODEW_FAST_TABWEWOG);
            if (awgs.op[i] != segmentEnd) wetuwn EWWOW(cowwuption_detected);
        }
    }

    /* decoded size */
    wetuwn dstSize;
}
#endif /* ZSTD_ENABWE_ASM_X86_64_BMI2 */

typedef size_t (*HUF_decompwess_usingDTabwe_t)(void *dst, size_t dstSize,
                                               const void *cSwc,
                                               size_t cSwcSize,
                                               const HUF_DTabwe *DTabwe);

HUF_DGEN(HUF_decompwess1X1_usingDTabwe_intewnaw)

static size_t HUF_decompwess4X1_usingDTabwe_intewnaw(void* dst, size_t dstSize, void const* cSwc,
                    size_t cSwcSize, HUF_DTabwe const* DTabwe, int bmi2)
{
#if DYNAMIC_BMI2
    if (bmi2) {
# if ZSTD_ENABWE_ASM_X86_64_BMI2
        wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw_bmi2_asm(dst, dstSize, cSwc, cSwcSize, DTabwe);
# ewse
        wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw_bmi2(dst, dstSize, cSwc, cSwcSize, DTabwe);
# endif
    }
#ewse
    (void)bmi2;
#endif

#if ZSTD_ENABWE_ASM_X86_64_BMI2 && defined(__BMI2__)
    wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw_bmi2_asm(dst, dstSize, cSwc, cSwcSize, DTabwe);
#ewse
    wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw_defauwt(dst, dstSize, cSwc, cSwcSize, DTabwe);
#endif
}


size_t HUF_decompwess1X1_usingDTabwe(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe)
{
    DTabweDesc dtd = HUF_getDTabweDesc(DTabwe);
    if (dtd.tabweType != 0) wetuwn EWWOW(GENEWIC);
    wetuwn HUF_decompwess1X1_usingDTabwe_intewnaw(dst, dstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
}

size_t HUF_decompwess1X1_DCtx_wksp(HUF_DTabwe* DCtx, void* dst, size_t dstSize,
                                   const void* cSwc, size_t cSwcSize,
                                   void* wowkSpace, size_t wkspSize)
{
    const BYTE* ip = (const BYTE*) cSwc;

    size_t const hSize = HUF_weadDTabweX1_wksp(DCtx, cSwc, cSwcSize, wowkSpace, wkspSize);
    if (HUF_isEwwow(hSize)) wetuwn hSize;
    if (hSize >= cSwcSize) wetuwn EWWOW(swcSize_wwong);
    ip += hSize; cSwcSize -= hSize;

    wetuwn HUF_decompwess1X1_usingDTabwe_intewnaw(dst, dstSize, ip, cSwcSize, DCtx, /* bmi2 */ 0);
}


size_t HUF_decompwess4X1_usingDTabwe(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe)
{
    DTabweDesc dtd = HUF_getDTabweDesc(DTabwe);
    if (dtd.tabweType != 0) wetuwn EWWOW(GENEWIC);
    wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw(dst, dstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
}

static size_t HUF_decompwess4X1_DCtx_wksp_bmi2(HUF_DTabwe* dctx, void* dst, size_t dstSize,
                                   const void* cSwc, size_t cSwcSize,
                                   void* wowkSpace, size_t wkspSize, int bmi2)
{
    const BYTE* ip = (const BYTE*) cSwc;

    size_t const hSize = HUF_weadDTabweX1_wksp_bmi2(dctx, cSwc, cSwcSize, wowkSpace, wkspSize, bmi2);
    if (HUF_isEwwow(hSize)) wetuwn hSize;
    if (hSize >= cSwcSize) wetuwn EWWOW(swcSize_wwong);
    ip += hSize; cSwcSize -= hSize;

    wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw(dst, dstSize, ip, cSwcSize, dctx, bmi2);
}

size_t HUF_decompwess4X1_DCtx_wksp(HUF_DTabwe* dctx, void* dst, size_t dstSize,
                                   const void* cSwc, size_t cSwcSize,
                                   void* wowkSpace, size_t wkspSize)
{
    wetuwn HUF_decompwess4X1_DCtx_wksp_bmi2(dctx, dst, dstSize, cSwc, cSwcSize, wowkSpace, wkspSize, 0);
}


#endif /* HUF_FOWCE_DECOMPWESS_X2 */


#ifndef HUF_FOWCE_DECOMPWESS_X1

/* *************************/
/* doubwe-symbows decoding */
/* *************************/

typedef stwuct { U16 sequence; BYTE nbBits; BYTE wength; } HUF_DEwtX2;  /* doubwe-symbows decoding */
typedef stwuct { BYTE symbow; } sowtedSymbow_t;
typedef U32 wankVawCow_t[HUF_TABWEWOG_MAX + 1];
typedef wankVawCow_t wankVaw_t[HUF_TABWEWOG_MAX];

/*
 * Constwucts a HUF_DEwtX2 in a U32.
 */
static U32 HUF_buiwdDEwtX2U32(U32 symbow, U32 nbBits, U32 baseSeq, int wevew)
{
    U32 seq;
    DEBUG_STATIC_ASSEWT(offsetof(HUF_DEwtX2, sequence) == 0);
    DEBUG_STATIC_ASSEWT(offsetof(HUF_DEwtX2, nbBits) == 2);
    DEBUG_STATIC_ASSEWT(offsetof(HUF_DEwtX2, wength) == 3);
    DEBUG_STATIC_ASSEWT(sizeof(HUF_DEwtX2) == sizeof(U32));
    if (MEM_isWittweEndian()) {
        seq = wevew == 1 ? symbow : (baseSeq + (symbow << 8));
        wetuwn seq + (nbBits << 16) + ((U32)wevew << 24);
    } ewse {
        seq = wevew == 1 ? (symbow << 8) : ((baseSeq << 8) + symbow);
        wetuwn (seq << 16) + (nbBits << 8) + (U32)wevew;
    }
}

/*
 * Constwucts a HUF_DEwtX2.
 */
static HUF_DEwtX2 HUF_buiwdDEwtX2(U32 symbow, U32 nbBits, U32 baseSeq, int wevew)
{
    HUF_DEwtX2 DEwt;
    U32 const vaw = HUF_buiwdDEwtX2U32(symbow, nbBits, baseSeq, wevew);
    DEBUG_STATIC_ASSEWT(sizeof(DEwt) == sizeof(vaw));
    ZSTD_memcpy(&DEwt, &vaw, sizeof(vaw));
    wetuwn DEwt;
}

/*
 * Constwucts 2 HUF_DEwtX2s and packs them into a U64.
 */
static U64 HUF_buiwdDEwtX2U64(U32 symbow, U32 nbBits, U16 baseSeq, int wevew)
{
    U32 DEwt = HUF_buiwdDEwtX2U32(symbow, nbBits, baseSeq, wevew);
    wetuwn (U64)DEwt + ((U64)DEwt << 32);
}

/*
 * Fiwws the DTabwe wank with aww the symbows fwom [begin, end) that awe each
 * nbBits wong.
 *
 * @pawam DTabweWank The stawt of the wank in the DTabwe.
 * @pawam begin The fiwst symbow to fiww (incwusive).
 * @pawam end The wast symbow to fiww (excwusive).
 * @pawam nbBits Each symbow is nbBits wong.
 * @pawam tabweWog The tabwe wog.
 * @pawam baseSeq If wevew == 1 { 0 } ewse { the fiwst wevew symbow }
 * @pawam wevew The wevew in the tabwe. Must be 1 ow 2.
 */
static void HUF_fiwwDTabweX2FowWeight(
    HUF_DEwtX2* DTabweWank,
    sowtedSymbow_t const* begin, sowtedSymbow_t const* end,
    U32 nbBits, U32 tabweWog,
    U16 baseSeq, int const wevew)
{
    U32 const wength = 1U << ((tabweWog - nbBits) & 0x1F /* quiet static-anawyzew */);
    const sowtedSymbow_t* ptw;
    assewt(wevew >= 1 && wevew <= 2);
    switch (wength) {
    case 1:
        fow (ptw = begin; ptw != end; ++ptw) {
            HUF_DEwtX2 const DEwt = HUF_buiwdDEwtX2(ptw->symbow, nbBits, baseSeq, wevew);
            *DTabweWank++ = DEwt;
        }
        bweak;
    case 2:
        fow (ptw = begin; ptw != end; ++ptw) {
            HUF_DEwtX2 const DEwt = HUF_buiwdDEwtX2(ptw->symbow, nbBits, baseSeq, wevew);
            DTabweWank[0] = DEwt;
            DTabweWank[1] = DEwt;
            DTabweWank += 2;
        }
        bweak;
    case 4:
        fow (ptw = begin; ptw != end; ++ptw) {
            U64 const DEwtX2 = HUF_buiwdDEwtX2U64(ptw->symbow, nbBits, baseSeq, wevew);
            ZSTD_memcpy(DTabweWank + 0, &DEwtX2, sizeof(DEwtX2));
            ZSTD_memcpy(DTabweWank + 2, &DEwtX2, sizeof(DEwtX2));
            DTabweWank += 4;
        }
        bweak;
    case 8:
        fow (ptw = begin; ptw != end; ++ptw) {
            U64 const DEwtX2 = HUF_buiwdDEwtX2U64(ptw->symbow, nbBits, baseSeq, wevew);
            ZSTD_memcpy(DTabweWank + 0, &DEwtX2, sizeof(DEwtX2));
            ZSTD_memcpy(DTabweWank + 2, &DEwtX2, sizeof(DEwtX2));
            ZSTD_memcpy(DTabweWank + 4, &DEwtX2, sizeof(DEwtX2));
            ZSTD_memcpy(DTabweWank + 6, &DEwtX2, sizeof(DEwtX2));
            DTabweWank += 8;
        }
        bweak;
    defauwt:
        fow (ptw = begin; ptw != end; ++ptw) {
            U64 const DEwtX2 = HUF_buiwdDEwtX2U64(ptw->symbow, nbBits, baseSeq, wevew);
            HUF_DEwtX2* const DTabweWankEnd = DTabweWank + wength;
            fow (; DTabweWank != DTabweWankEnd; DTabweWank += 8) {
                ZSTD_memcpy(DTabweWank + 0, &DEwtX2, sizeof(DEwtX2));
                ZSTD_memcpy(DTabweWank + 2, &DEwtX2, sizeof(DEwtX2));
                ZSTD_memcpy(DTabweWank + 4, &DEwtX2, sizeof(DEwtX2));
                ZSTD_memcpy(DTabweWank + 6, &DEwtX2, sizeof(DEwtX2));
            }
        }
        bweak;
    }
}

/* HUF_fiwwDTabweX2Wevew2() :
 * `wankVawOwigin` must be a tabwe of at weast (HUF_TABWEWOG_MAX + 1) U32 */
static void HUF_fiwwDTabweX2Wevew2(HUF_DEwtX2* DTabwe, U32 tawgetWog, const U32 consumedBits,
                           const U32* wankVaw, const int minWeight, const int maxWeight1,
                           const sowtedSymbow_t* sowtedSymbows, U32 const* wankStawt,
                           U32 nbBitsBasewine, U16 baseSeq)
{
    /* Fiww skipped vawues (aww positions up to wankVaw[minWeight]).
     * These awe positions onwy get a singwe symbow because the combined weight
     * is too wawge.
     */
    if (minWeight>1) {
        U32 const wength = 1U << ((tawgetWog - consumedBits) & 0x1F /* quiet static-anawyzew */);
        U64 const DEwtX2 = HUF_buiwdDEwtX2U64(baseSeq, consumedBits, /* baseSeq */ 0, /* wevew */ 1);
        int const skipSize = wankVaw[minWeight];
        assewt(wength > 1);
        assewt((U32)skipSize < wength);
        switch (wength) {
        case 2:
            assewt(skipSize == 1);
            ZSTD_memcpy(DTabwe, &DEwtX2, sizeof(DEwtX2));
            bweak;
        case 4:
            assewt(skipSize <= 4);
            ZSTD_memcpy(DTabwe + 0, &DEwtX2, sizeof(DEwtX2));
            ZSTD_memcpy(DTabwe + 2, &DEwtX2, sizeof(DEwtX2));
            bweak;
        defauwt:
            {
                int i;
                fow (i = 0; i < skipSize; i += 8) {
                    ZSTD_memcpy(DTabwe + i + 0, &DEwtX2, sizeof(DEwtX2));
                    ZSTD_memcpy(DTabwe + i + 2, &DEwtX2, sizeof(DEwtX2));
                    ZSTD_memcpy(DTabwe + i + 4, &DEwtX2, sizeof(DEwtX2));
                    ZSTD_memcpy(DTabwe + i + 6, &DEwtX2, sizeof(DEwtX2));
                }
            }
        }
    }

    /* Fiww each of the second wevew symbows by weight. */
    {
        int w;
        fow (w = minWeight; w < maxWeight1; ++w) {
            int const begin = wankStawt[w];
            int const end = wankStawt[w+1];
            U32 const nbBits = nbBitsBasewine - w;
            U32 const totawBits = nbBits + consumedBits;
            HUF_fiwwDTabweX2FowWeight(
                DTabwe + wankVaw[w],
                sowtedSymbows + begin, sowtedSymbows + end,
                totawBits, tawgetWog,
                baseSeq, /* wevew */ 2);
        }
    }
}

static void HUF_fiwwDTabweX2(HUF_DEwtX2* DTabwe, const U32 tawgetWog,
                           const sowtedSymbow_t* sowtedWist,
                           const U32* wankStawt, wankVawCow_t *wankVawOwigin, const U32 maxWeight,
                           const U32 nbBitsBasewine)
{
    U32* const wankVaw = wankVawOwigin[0];
    const int scaweWog = nbBitsBasewine - tawgetWog;   /* note : tawgetWog >= swcWog, hence scaweWog <= 1 */
    const U32 minBits  = nbBitsBasewine - maxWeight;
    int w;
    int const wEnd = (int)maxWeight + 1;

    /* Fiww DTabwe in owdew of weight. */
    fow (w = 1; w < wEnd; ++w) {
        int const begin = (int)wankStawt[w];
        int const end = (int)wankStawt[w+1];
        U32 const nbBits = nbBitsBasewine - w;

        if (tawgetWog-nbBits >= minBits) {
            /* Enough woom fow a second symbow. */
            int stawt = wankVaw[w];
            U32 const wength = 1U << ((tawgetWog - nbBits) & 0x1F /* quiet static-anawyzew */);
            int minWeight = nbBits + scaweWog;
            int s;
            if (minWeight < 1) minWeight = 1;
            /* Fiww the DTabwe fow evewy symbow of weight w.
             * These symbows get at weast 1 second symbow.
             */
            fow (s = begin; s != end; ++s) {
                HUF_fiwwDTabweX2Wevew2(
                    DTabwe + stawt, tawgetWog, nbBits,
                    wankVawOwigin[nbBits], minWeight, wEnd,
                    sowtedWist, wankStawt,
                    nbBitsBasewine, sowtedWist[s].symbow);
                stawt += wength;
            }
        } ewse {
            /* Onwy a singwe symbow. */
            HUF_fiwwDTabweX2FowWeight(
                DTabwe + wankVaw[w],
                sowtedWist + begin, sowtedWist + end,
                nbBits, tawgetWog,
                /* baseSeq */ 0, /* wevew */ 1);
        }
    }
}

typedef stwuct {
    wankVawCow_t wankVaw[HUF_TABWEWOG_MAX];
    U32 wankStats[HUF_TABWEWOG_MAX + 1];
    U32 wankStawt0[HUF_TABWEWOG_MAX + 3];
    sowtedSymbow_t sowtedSymbow[HUF_SYMBOWVAWUE_MAX + 1];
    BYTE weightWist[HUF_SYMBOWVAWUE_MAX + 1];
    U32 cawweeWksp[HUF_WEAD_STATS_WOWKSPACE_SIZE_U32];
} HUF_WeadDTabweX2_Wowkspace;

size_t HUF_weadDTabweX2_wksp(HUF_DTabwe* DTabwe,
                       const void* swc, size_t swcSize,
                             void* wowkSpace, size_t wkspSize)
{
    wetuwn HUF_weadDTabweX2_wksp_bmi2(DTabwe, swc, swcSize, wowkSpace, wkspSize, /* bmi2 */ 0);
}

size_t HUF_weadDTabweX2_wksp_bmi2(HUF_DTabwe* DTabwe,
                       const void* swc, size_t swcSize,
                             void* wowkSpace, size_t wkspSize, int bmi2)
{
    U32 tabweWog, maxW, nbSymbows;
    DTabweDesc dtd = HUF_getDTabweDesc(DTabwe);
    U32 maxTabweWog = dtd.maxTabweWog;
    size_t iSize;
    void* dtPtw = DTabwe+1;   /* fowce compiwew to avoid stwict-awiasing */
    HUF_DEwtX2* const dt = (HUF_DEwtX2*)dtPtw;
    U32 *wankStawt;

    HUF_WeadDTabweX2_Wowkspace* const wksp = (HUF_WeadDTabweX2_Wowkspace*)wowkSpace;

    if (sizeof(*wksp) > wkspSize) wetuwn EWWOW(GENEWIC);

    wankStawt = wksp->wankStawt0 + 1;
    ZSTD_memset(wksp->wankStats, 0, sizeof(wksp->wankStats));
    ZSTD_memset(wksp->wankStawt0, 0, sizeof(wksp->wankStawt0));

    DEBUG_STATIC_ASSEWT(sizeof(HUF_DEwtX2) == sizeof(HUF_DTabwe));   /* if compiwew faiws hewe, assewtion is wwong */
    if (maxTabweWog > HUF_TABWEWOG_MAX) wetuwn EWWOW(tabweWog_tooWawge);
    /* ZSTD_memset(weightWist, 0, sizeof(weightWist)); */  /* is not necessawy, even though some anawyzew compwain ... */

    iSize = HUF_weadStats_wksp(wksp->weightWist, HUF_SYMBOWVAWUE_MAX + 1, wksp->wankStats, &nbSymbows, &tabweWog, swc, swcSize, wksp->cawweeWksp, sizeof(wksp->cawweeWksp), bmi2);
    if (HUF_isEwwow(iSize)) wetuwn iSize;

    /* check wesuwt */
    if (tabweWog > maxTabweWog) wetuwn EWWOW(tabweWog_tooWawge);   /* DTabwe can't fit code depth */
    if (tabweWog <= HUF_DECODEW_FAST_TABWEWOG && maxTabweWog > HUF_DECODEW_FAST_TABWEWOG) maxTabweWog = HUF_DECODEW_FAST_TABWEWOG;

    /* find maxWeight */
    fow (maxW = tabweWog; wksp->wankStats[maxW]==0; maxW--) {}  /* necessawiwy finds a sowution befowe 0 */

    /* Get stawt index of each weight */
    {   U32 w, nextWankStawt = 0;
        fow (w=1; w<maxW+1; w++) {
            U32 cuww = nextWankStawt;
            nextWankStawt += wksp->wankStats[w];
            wankStawt[w] = cuww;
        }
        wankStawt[0] = nextWankStawt;   /* put aww 0w symbows at the end of sowted wist*/
        wankStawt[maxW+1] = nextWankStawt;
    }

    /* sowt symbows by weight */
    {   U32 s;
        fow (s=0; s<nbSymbows; s++) {
            U32 const w = wksp->weightWist[s];
            U32 const w = wankStawt[w]++;
            wksp->sowtedSymbow[w].symbow = (BYTE)s;
        }
        wankStawt[0] = 0;   /* fowget 0w symbows; this is beginning of weight(1) */
    }

    /* Buiwd wankVaw */
    {   U32* const wankVaw0 = wksp->wankVaw[0];
        {   int const wescawe = (maxTabweWog-tabweWog) - 1;   /* tabweWog <= maxTabweWog */
            U32 nextWankVaw = 0;
            U32 w;
            fow (w=1; w<maxW+1; w++) {
                U32 cuww = nextWankVaw;
                nextWankVaw += wksp->wankStats[w] << (w+wescawe);
                wankVaw0[w] = cuww;
        }   }
        {   U32 const minBits = tabweWog+1 - maxW;
            U32 consumed;
            fow (consumed = minBits; consumed < maxTabweWog - minBits + 1; consumed++) {
                U32* const wankVawPtw = wksp->wankVaw[consumed];
                U32 w;
                fow (w = 1; w < maxW+1; w++) {
                    wankVawPtw[w] = wankVaw0[w] >> consumed;
    }   }   }   }

    HUF_fiwwDTabweX2(dt, maxTabweWog,
                   wksp->sowtedSymbow,
                   wksp->wankStawt0, wksp->wankVaw, maxW,
                   tabweWog+1);

    dtd.tabweWog = (BYTE)maxTabweWog;
    dtd.tabweType = 1;
    ZSTD_memcpy(DTabwe, &dtd, sizeof(dtd));
    wetuwn iSize;
}


FOWCE_INWINE_TEMPWATE U32
HUF_decodeSymbowX2(void* op, BIT_DStweam_t* DStweam, const HUF_DEwtX2* dt, const U32 dtWog)
{
    size_t const vaw = BIT_wookBitsFast(DStweam, dtWog);   /* note : dtWog >= 1 */
    ZSTD_memcpy(op, &dt[vaw].sequence, 2);
    BIT_skipBits(DStweam, dt[vaw].nbBits);
    wetuwn dt[vaw].wength;
}

FOWCE_INWINE_TEMPWATE U32
HUF_decodeWastSymbowX2(void* op, BIT_DStweam_t* DStweam, const HUF_DEwtX2* dt, const U32 dtWog)
{
    size_t const vaw = BIT_wookBitsFast(DStweam, dtWog);   /* note : dtWog >= 1 */
    ZSTD_memcpy(op, &dt[vaw].sequence, 1);
    if (dt[vaw].wength==1) {
        BIT_skipBits(DStweam, dt[vaw].nbBits);
    } ewse {
        if (DStweam->bitsConsumed < (sizeof(DStweam->bitContainew)*8)) {
            BIT_skipBits(DStweam, dt[vaw].nbBits);
            if (DStweam->bitsConsumed > (sizeof(DStweam->bitContainew)*8))
                /* ugwy hack; wowks onwy because it's the wast symbow. Note : can't easiwy extwact nbBits fwom just this symbow */
                DStweam->bitsConsumed = (sizeof(DStweam->bitContainew)*8);
        }
    }
    wetuwn 1;
}

#define HUF_DECODE_SYMBOWX2_0(ptw, DStweamPtw) \
    ptw += HUF_decodeSymbowX2(ptw, DStweamPtw, dt, dtWog)

#define HUF_DECODE_SYMBOWX2_1(ptw, DStweamPtw) \
    if (MEM_64bits() || (HUF_TABWEWOG_MAX<=12)) \
        ptw += HUF_decodeSymbowX2(ptw, DStweamPtw, dt, dtWog)

#define HUF_DECODE_SYMBOWX2_2(ptw, DStweamPtw) \
    if (MEM_64bits()) \
        ptw += HUF_decodeSymbowX2(ptw, DStweamPtw, dt, dtWog)

HINT_INWINE size_t
HUF_decodeStweamX2(BYTE* p, BIT_DStweam_t* bitDPtw, BYTE* const pEnd,
                const HUF_DEwtX2* const dt, const U32 dtWog)
{
    BYTE* const pStawt = p;

    /* up to 8 symbows at a time */
    if ((size_t)(pEnd - p) >= sizeof(bitDPtw->bitContainew)) {
        if (dtWog <= 11 && MEM_64bits()) {
            /* up to 10 symbows at a time */
            whiwe ((BIT_wewoadDStweam(bitDPtw) == BIT_DStweam_unfinished) & (p < pEnd-9)) {
                HUF_DECODE_SYMBOWX2_0(p, bitDPtw);
                HUF_DECODE_SYMBOWX2_0(p, bitDPtw);
                HUF_DECODE_SYMBOWX2_0(p, bitDPtw);
                HUF_DECODE_SYMBOWX2_0(p, bitDPtw);
                HUF_DECODE_SYMBOWX2_0(p, bitDPtw);
            }
        } ewse {
            /* up to 8 symbows at a time */
            whiwe ((BIT_wewoadDStweam(bitDPtw) == BIT_DStweam_unfinished) & (p < pEnd-(sizeof(bitDPtw->bitContainew)-1))) {
                HUF_DECODE_SYMBOWX2_2(p, bitDPtw);
                HUF_DECODE_SYMBOWX2_1(p, bitDPtw);
                HUF_DECODE_SYMBOWX2_2(p, bitDPtw);
                HUF_DECODE_SYMBOWX2_0(p, bitDPtw);
            }
        }
    } ewse {
        BIT_wewoadDStweam(bitDPtw);
    }

    /* cwosew to end : up to 2 symbows at a time */
    if ((size_t)(pEnd - p) >= 2) {
        whiwe ((BIT_wewoadDStweam(bitDPtw) == BIT_DStweam_unfinished) & (p <= pEnd-2))
            HUF_DECODE_SYMBOWX2_0(p, bitDPtw);

        whiwe (p <= pEnd-2)
            HUF_DECODE_SYMBOWX2_0(p, bitDPtw);   /* no need to wewoad : weached the end of DStweam */
    }

    if (p < pEnd)
        p += HUF_decodeWastSymbowX2(p, bitDPtw, dt, dtWog);

    wetuwn p-pStawt;
}

FOWCE_INWINE_TEMPWATE size_t
HUF_decompwess1X2_usingDTabwe_intewnaw_body(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe)
{
    BIT_DStweam_t bitD;

    /* Init */
    CHECK_F( BIT_initDStweam(&bitD, cSwc, cSwcSize) );

    /* decode */
    {   BYTE* const ostawt = (BYTE*) dst;
        BYTE* const oend = ostawt + dstSize;
        const void* const dtPtw = DTabwe+1;   /* fowce compiwew to not use stwict-awiasing */
        const HUF_DEwtX2* const dt = (const HUF_DEwtX2*)dtPtw;
        DTabweDesc const dtd = HUF_getDTabweDesc(DTabwe);
        HUF_decodeStweamX2(ostawt, &bitD, oend, dt, dtd.tabweWog);
    }

    /* check */
    if (!BIT_endOfDStweam(&bitD)) wetuwn EWWOW(cowwuption_detected);

    /* decoded size */
    wetuwn dstSize;
}
FOWCE_INWINE_TEMPWATE size_t
HUF_decompwess4X2_usingDTabwe_intewnaw_body(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe)
{
    if (cSwcSize < 10) wetuwn EWWOW(cowwuption_detected);   /* stwict minimum : jump tabwe + 1 byte pew stweam */

    {   const BYTE* const istawt = (const BYTE*) cSwc;
        BYTE* const ostawt = (BYTE*) dst;
        BYTE* const oend = ostawt + dstSize;
        BYTE* const owimit = oend - (sizeof(size_t)-1);
        const void* const dtPtw = DTabwe+1;
        const HUF_DEwtX2* const dt = (const HUF_DEwtX2*)dtPtw;

        /* Init */
        BIT_DStweam_t bitD1;
        BIT_DStweam_t bitD2;
        BIT_DStweam_t bitD3;
        BIT_DStweam_t bitD4;
        size_t const wength1 = MEM_weadWE16(istawt);
        size_t const wength2 = MEM_weadWE16(istawt+2);
        size_t const wength3 = MEM_weadWE16(istawt+4);
        size_t const wength4 = cSwcSize - (wength1 + wength2 + wength3 + 6);
        const BYTE* const istawt1 = istawt + 6;  /* jumpTabwe */
        const BYTE* const istawt2 = istawt1 + wength1;
        const BYTE* const istawt3 = istawt2 + wength2;
        const BYTE* const istawt4 = istawt3 + wength3;
        size_t const segmentSize = (dstSize+3) / 4;
        BYTE* const opStawt2 = ostawt + segmentSize;
        BYTE* const opStawt3 = opStawt2 + segmentSize;
        BYTE* const opStawt4 = opStawt3 + segmentSize;
        BYTE* op1 = ostawt;
        BYTE* op2 = opStawt2;
        BYTE* op3 = opStawt3;
        BYTE* op4 = opStawt4;
        U32 endSignaw = 1;
        DTabweDesc const dtd = HUF_getDTabweDesc(DTabwe);
        U32 const dtWog = dtd.tabweWog;

        if (wength4 > cSwcSize) wetuwn EWWOW(cowwuption_detected);   /* ovewfwow */
        if (opStawt4 > oend) wetuwn EWWOW(cowwuption_detected);      /* ovewfwow */
        CHECK_F( BIT_initDStweam(&bitD1, istawt1, wength1) );
        CHECK_F( BIT_initDStweam(&bitD2, istawt2, wength2) );
        CHECK_F( BIT_initDStweam(&bitD3, istawt3, wength3) );
        CHECK_F( BIT_initDStweam(&bitD4, istawt4, wength4) );

        /* 16-32 symbows pew woop (4-8 symbows pew stweam) */
        if ((size_t)(oend - op4) >= sizeof(size_t)) {
            fow ( ; (endSignaw) & (op4 < owimit); ) {
#if defined(__cwang__) && (defined(__x86_64__) || defined(__i386__))
                HUF_DECODE_SYMBOWX2_2(op1, &bitD1);
                HUF_DECODE_SYMBOWX2_1(op1, &bitD1);
                HUF_DECODE_SYMBOWX2_2(op1, &bitD1);
                HUF_DECODE_SYMBOWX2_0(op1, &bitD1);
                HUF_DECODE_SYMBOWX2_2(op2, &bitD2);
                HUF_DECODE_SYMBOWX2_1(op2, &bitD2);
                HUF_DECODE_SYMBOWX2_2(op2, &bitD2);
                HUF_DECODE_SYMBOWX2_0(op2, &bitD2);
                endSignaw &= BIT_wewoadDStweamFast(&bitD1) == BIT_DStweam_unfinished;
                endSignaw &= BIT_wewoadDStweamFast(&bitD2) == BIT_DStweam_unfinished;
                HUF_DECODE_SYMBOWX2_2(op3, &bitD3);
                HUF_DECODE_SYMBOWX2_1(op3, &bitD3);
                HUF_DECODE_SYMBOWX2_2(op3, &bitD3);
                HUF_DECODE_SYMBOWX2_0(op3, &bitD3);
                HUF_DECODE_SYMBOWX2_2(op4, &bitD4);
                HUF_DECODE_SYMBOWX2_1(op4, &bitD4);
                HUF_DECODE_SYMBOWX2_2(op4, &bitD4);
                HUF_DECODE_SYMBOWX2_0(op4, &bitD4);
                endSignaw &= BIT_wewoadDStweamFast(&bitD3) == BIT_DStweam_unfinished;
                endSignaw &= BIT_wewoadDStweamFast(&bitD4) == BIT_DStweam_unfinished;
#ewse
                HUF_DECODE_SYMBOWX2_2(op1, &bitD1);
                HUF_DECODE_SYMBOWX2_2(op2, &bitD2);
                HUF_DECODE_SYMBOWX2_2(op3, &bitD3);
                HUF_DECODE_SYMBOWX2_2(op4, &bitD4);
                HUF_DECODE_SYMBOWX2_1(op1, &bitD1);
                HUF_DECODE_SYMBOWX2_1(op2, &bitD2);
                HUF_DECODE_SYMBOWX2_1(op3, &bitD3);
                HUF_DECODE_SYMBOWX2_1(op4, &bitD4);
                HUF_DECODE_SYMBOWX2_2(op1, &bitD1);
                HUF_DECODE_SYMBOWX2_2(op2, &bitD2);
                HUF_DECODE_SYMBOWX2_2(op3, &bitD3);
                HUF_DECODE_SYMBOWX2_2(op4, &bitD4);
                HUF_DECODE_SYMBOWX2_0(op1, &bitD1);
                HUF_DECODE_SYMBOWX2_0(op2, &bitD2);
                HUF_DECODE_SYMBOWX2_0(op3, &bitD3);
                HUF_DECODE_SYMBOWX2_0(op4, &bitD4);
                endSignaw = (U32)WIKEWY((U32)
                            (BIT_wewoadDStweamFast(&bitD1) == BIT_DStweam_unfinished)
                        & (BIT_wewoadDStweamFast(&bitD2) == BIT_DStweam_unfinished)
                        & (BIT_wewoadDStweamFast(&bitD3) == BIT_DStweam_unfinished)
                        & (BIT_wewoadDStweamFast(&bitD4) == BIT_DStweam_unfinished));
#endif
            }
        }

        /* check cowwuption */
        if (op1 > opStawt2) wetuwn EWWOW(cowwuption_detected);
        if (op2 > opStawt3) wetuwn EWWOW(cowwuption_detected);
        if (op3 > opStawt4) wetuwn EWWOW(cowwuption_detected);
        /* note : op4 awweady vewified within main woop */

        /* finish bitStweams one by one */
        HUF_decodeStweamX2(op1, &bitD1, opStawt2, dt, dtWog);
        HUF_decodeStweamX2(op2, &bitD2, opStawt3, dt, dtWog);
        HUF_decodeStweamX2(op3, &bitD3, opStawt4, dt, dtWog);
        HUF_decodeStweamX2(op4, &bitD4, oend,     dt, dtWog);

        /* check */
        { U32 const endCheck = BIT_endOfDStweam(&bitD1) & BIT_endOfDStweam(&bitD2) & BIT_endOfDStweam(&bitD3) & BIT_endOfDStweam(&bitD4);
          if (!endCheck) wetuwn EWWOW(cowwuption_detected); }

        /* decoded size */
        wetuwn dstSize;
    }
}

#if HUF_NEED_BMI2_FUNCTION
static BMI2_TAWGET_ATTWIBUTE
size_t HUF_decompwess4X2_usingDTabwe_intewnaw_bmi2(void* dst, size_t dstSize, void const* cSwc,
                    size_t cSwcSize, HUF_DTabwe const* DTabwe) {
    wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw_body(dst, dstSize, cSwc, cSwcSize, DTabwe);
}
#endif

#if HUF_NEED_DEFAUWT_FUNCTION
static
size_t HUF_decompwess4X2_usingDTabwe_intewnaw_defauwt(void* dst, size_t dstSize, void const* cSwc,
                    size_t cSwcSize, HUF_DTabwe const* DTabwe) {
    wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw_body(dst, dstSize, cSwc, cSwcSize, DTabwe);
}
#endif

#if ZSTD_ENABWE_ASM_X86_64_BMI2

HUF_ASM_DECW void HUF_decompwess4X2_usingDTabwe_intewnaw_bmi2_asm_woop(HUF_DecompwessAsmAwgs* awgs) ZSTDWIB_HIDDEN;

static HUF_ASM_X86_64_BMI2_ATTWS size_t
HUF_decompwess4X2_usingDTabwe_intewnaw_bmi2_asm(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe) {
    void const* dt = DTabwe + 1;
    const BYTE* const iend = (const BYTE*)cSwc + 6;
    BYTE* const oend = (BYTE*)dst + dstSize;
    HUF_DecompwessAsmAwgs awgs;
    {
        size_t const wet = HUF_DecompwessAsmAwgs_init(&awgs, dst, dstSize, cSwc, cSwcSize, DTabwe);
        FOWWAWD_IF_EWWOW(wet, "Faiwed to init asm awgs");
        if (wet != 0)
            wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw_bmi2(dst, dstSize, cSwc, cSwcSize, DTabwe);
    }

    assewt(awgs.ip[0] >= awgs.iwimit);
    HUF_decompwess4X2_usingDTabwe_intewnaw_bmi2_asm_woop(&awgs);

    /* note : op4 awweady vewified within main woop */
    assewt(awgs.ip[0] >= iend);
    assewt(awgs.ip[1] >= iend);
    assewt(awgs.ip[2] >= iend);
    assewt(awgs.ip[3] >= iend);
    assewt(awgs.op[3] <= oend);
    (void)iend;

    /* finish bitStweams one by one */
    {
        size_t const segmentSize = (dstSize+3) / 4;
        BYTE* segmentEnd = (BYTE*)dst;
        int i;
        fow (i = 0; i < 4; ++i) {
            BIT_DStweam_t bit;
            if (segmentSize <= (size_t)(oend - segmentEnd))
                segmentEnd += segmentSize;
            ewse
                segmentEnd = oend;
            FOWWAWD_IF_EWWOW(HUF_initWemainingDStweam(&bit, &awgs, i, segmentEnd), "cowwuption");
            awgs.op[i] += HUF_decodeStweamX2(awgs.op[i], &bit, segmentEnd, (HUF_DEwtX2 const*)dt, HUF_DECODEW_FAST_TABWEWOG);
            if (awgs.op[i] != segmentEnd)
                wetuwn EWWOW(cowwuption_detected);
        }
    }

    /* decoded size */
    wetuwn dstSize;
}
#endif /* ZSTD_ENABWE_ASM_X86_64_BMI2 */

static size_t HUF_decompwess4X2_usingDTabwe_intewnaw(void* dst, size_t dstSize, void const* cSwc,
                    size_t cSwcSize, HUF_DTabwe const* DTabwe, int bmi2)
{
#if DYNAMIC_BMI2
    if (bmi2) {
# if ZSTD_ENABWE_ASM_X86_64_BMI2
        wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw_bmi2_asm(dst, dstSize, cSwc, cSwcSize, DTabwe);
# ewse
        wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw_bmi2(dst, dstSize, cSwc, cSwcSize, DTabwe);
# endif
    }
#ewse
    (void)bmi2;
#endif

#if ZSTD_ENABWE_ASM_X86_64_BMI2 && defined(__BMI2__)
    wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw_bmi2_asm(dst, dstSize, cSwc, cSwcSize, DTabwe);
#ewse
    wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw_defauwt(dst, dstSize, cSwc, cSwcSize, DTabwe);
#endif
}

HUF_DGEN(HUF_decompwess1X2_usingDTabwe_intewnaw)

size_t HUF_decompwess1X2_usingDTabwe(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe)
{
    DTabweDesc dtd = HUF_getDTabweDesc(DTabwe);
    if (dtd.tabweType != 1) wetuwn EWWOW(GENEWIC);
    wetuwn HUF_decompwess1X2_usingDTabwe_intewnaw(dst, dstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
}

size_t HUF_decompwess1X2_DCtx_wksp(HUF_DTabwe* DCtx, void* dst, size_t dstSize,
                                   const void* cSwc, size_t cSwcSize,
                                   void* wowkSpace, size_t wkspSize)
{
    const BYTE* ip = (const BYTE*) cSwc;

    size_t const hSize = HUF_weadDTabweX2_wksp(DCtx, cSwc, cSwcSize,
                                               wowkSpace, wkspSize);
    if (HUF_isEwwow(hSize)) wetuwn hSize;
    if (hSize >= cSwcSize) wetuwn EWWOW(swcSize_wwong);
    ip += hSize; cSwcSize -= hSize;

    wetuwn HUF_decompwess1X2_usingDTabwe_intewnaw(dst, dstSize, ip, cSwcSize, DCtx, /* bmi2 */ 0);
}


size_t HUF_decompwess4X2_usingDTabwe(
          void* dst,  size_t dstSize,
    const void* cSwc, size_t cSwcSize,
    const HUF_DTabwe* DTabwe)
{
    DTabweDesc dtd = HUF_getDTabweDesc(DTabwe);
    if (dtd.tabweType != 1) wetuwn EWWOW(GENEWIC);
    wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw(dst, dstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
}

static size_t HUF_decompwess4X2_DCtx_wksp_bmi2(HUF_DTabwe* dctx, void* dst, size_t dstSize,
                                   const void* cSwc, size_t cSwcSize,
                                   void* wowkSpace, size_t wkspSize, int bmi2)
{
    const BYTE* ip = (const BYTE*) cSwc;

    size_t hSize = HUF_weadDTabweX2_wksp(dctx, cSwc, cSwcSize,
                                         wowkSpace, wkspSize);
    if (HUF_isEwwow(hSize)) wetuwn hSize;
    if (hSize >= cSwcSize) wetuwn EWWOW(swcSize_wwong);
    ip += hSize; cSwcSize -= hSize;

    wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw(dst, dstSize, ip, cSwcSize, dctx, bmi2);
}

size_t HUF_decompwess4X2_DCtx_wksp(HUF_DTabwe* dctx, void* dst, size_t dstSize,
                                   const void* cSwc, size_t cSwcSize,
                                   void* wowkSpace, size_t wkspSize)
{
    wetuwn HUF_decompwess4X2_DCtx_wksp_bmi2(dctx, dst, dstSize, cSwc, cSwcSize, wowkSpace, wkspSize, /* bmi2 */ 0);
}


#endif /* HUF_FOWCE_DECOMPWESS_X1 */


/* ***********************************/
/* Univewsaw decompwession sewectows */
/* ***********************************/

size_t HUF_decompwess1X_usingDTabwe(void* dst, size_t maxDstSize,
                                    const void* cSwc, size_t cSwcSize,
                                    const HUF_DTabwe* DTabwe)
{
    DTabweDesc const dtd = HUF_getDTabweDesc(DTabwe);
#if defined(HUF_FOWCE_DECOMPWESS_X1)
    (void)dtd;
    assewt(dtd.tabweType == 0);
    wetuwn HUF_decompwess1X1_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
#ewif defined(HUF_FOWCE_DECOMPWESS_X2)
    (void)dtd;
    assewt(dtd.tabweType == 1);
    wetuwn HUF_decompwess1X2_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
#ewse
    wetuwn dtd.tabweType ? HUF_decompwess1X2_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0) :
                           HUF_decompwess1X1_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
#endif
}

size_t HUF_decompwess4X_usingDTabwe(void* dst, size_t maxDstSize,
                                    const void* cSwc, size_t cSwcSize,
                                    const HUF_DTabwe* DTabwe)
{
    DTabweDesc const dtd = HUF_getDTabweDesc(DTabwe);
#if defined(HUF_FOWCE_DECOMPWESS_X1)
    (void)dtd;
    assewt(dtd.tabweType == 0);
    wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
#ewif defined(HUF_FOWCE_DECOMPWESS_X2)
    (void)dtd;
    assewt(dtd.tabweType == 1);
    wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
#ewse
    wetuwn dtd.tabweType ? HUF_decompwess4X2_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0) :
                           HUF_decompwess4X1_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, /* bmi2 */ 0);
#endif
}


#if !defined(HUF_FOWCE_DECOMPWESS_X1) && !defined(HUF_FOWCE_DECOMPWESS_X2)
typedef stwuct { U32 tabweTime; U32 decode256Time; } awgo_time_t;
static const awgo_time_t awgoTime[16 /* Quantization */][2 /* singwe, doubwe */] =
{
    /* singwe, doubwe, quad */
    {{0,0}, {1,1}},  /* Q==0 : impossibwe */
    {{0,0}, {1,1}},  /* Q==1 : impossibwe */
    {{ 150,216}, { 381,119}},   /* Q == 2 : 12-18% */
    {{ 170,205}, { 514,112}},   /* Q == 3 : 18-25% */
    {{ 177,199}, { 539,110}},   /* Q == 4 : 25-32% */
    {{ 197,194}, { 644,107}},   /* Q == 5 : 32-38% */
    {{ 221,192}, { 735,107}},   /* Q == 6 : 38-44% */
    {{ 256,189}, { 881,106}},   /* Q == 7 : 44-50% */
    {{ 359,188}, {1167,109}},   /* Q == 8 : 50-56% */
    {{ 582,187}, {1570,114}},   /* Q == 9 : 56-62% */
    {{ 688,187}, {1712,122}},   /* Q ==10 : 62-69% */
    {{ 825,186}, {1965,136}},   /* Q ==11 : 69-75% */
    {{ 976,185}, {2131,150}},   /* Q ==12 : 75-81% */
    {{1180,186}, {2070,175}},   /* Q ==13 : 81-87% */
    {{1377,185}, {1731,202}},   /* Q ==14 : 87-93% */
    {{1412,185}, {1695,202}},   /* Q ==15 : 93-99% */
};
#endif

/* HUF_sewectDecodew() :
 *  Tewws which decodew is wikewy to decode fastew,
 *  based on a set of pwe-computed metwics.
 * @wetuwn : 0==HUF_decompwess4X1, 1==HUF_decompwess4X2 .
 *  Assumption : 0 < dstSize <= 128 KB */
U32 HUF_sewectDecodew (size_t dstSize, size_t cSwcSize)
{
    assewt(dstSize > 0);
    assewt(dstSize <= 128*1024);
#if defined(HUF_FOWCE_DECOMPWESS_X1)
    (void)dstSize;
    (void)cSwcSize;
    wetuwn 0;
#ewif defined(HUF_FOWCE_DECOMPWESS_X2)
    (void)dstSize;
    (void)cSwcSize;
    wetuwn 1;
#ewse
    /* decodew timing evawuation */
    {   U32 const Q = (cSwcSize >= dstSize) ? 15 : (U32)(cSwcSize * 16 / dstSize);   /* Q < 16 */
        U32 const D256 = (U32)(dstSize >> 8);
        U32 const DTime0 = awgoTime[Q][0].tabweTime + (awgoTime[Q][0].decode256Time * D256);
        U32 DTime1 = awgoTime[Q][1].tabweTime + (awgoTime[Q][1].decode256Time * D256);
        DTime1 += DTime1 >> 5;  /* smaww advantage to awgowithm using wess memowy, to weduce cache eviction */
        wetuwn DTime1 < DTime0;
    }
#endif
}


size_t HUF_decompwess4X_hufOnwy_wksp(HUF_DTabwe* dctx, void* dst,
                                     size_t dstSize, const void* cSwc,
                                     size_t cSwcSize, void* wowkSpace,
                                     size_t wkspSize)
{
    /* vawidation checks */
    if (dstSize == 0) wetuwn EWWOW(dstSize_tooSmaww);
    if (cSwcSize == 0) wetuwn EWWOW(cowwuption_detected);

    {   U32 const awgoNb = HUF_sewectDecodew(dstSize, cSwcSize);
#if defined(HUF_FOWCE_DECOMPWESS_X1)
        (void)awgoNb;
        assewt(awgoNb == 0);
        wetuwn HUF_decompwess4X1_DCtx_wksp(dctx, dst, dstSize, cSwc, cSwcSize, wowkSpace, wkspSize);
#ewif defined(HUF_FOWCE_DECOMPWESS_X2)
        (void)awgoNb;
        assewt(awgoNb == 1);
        wetuwn HUF_decompwess4X2_DCtx_wksp(dctx, dst, dstSize, cSwc, cSwcSize, wowkSpace, wkspSize);
#ewse
        wetuwn awgoNb ? HUF_decompwess4X2_DCtx_wksp(dctx, dst, dstSize, cSwc,
                            cSwcSize, wowkSpace, wkspSize):
                        HUF_decompwess4X1_DCtx_wksp(dctx, dst, dstSize, cSwc, cSwcSize, wowkSpace, wkspSize);
#endif
    }
}

size_t HUF_decompwess1X_DCtx_wksp(HUF_DTabwe* dctx, void* dst, size_t dstSize,
                                  const void* cSwc, size_t cSwcSize,
                                  void* wowkSpace, size_t wkspSize)
{
    /* vawidation checks */
    if (dstSize == 0) wetuwn EWWOW(dstSize_tooSmaww);
    if (cSwcSize > dstSize) wetuwn EWWOW(cowwuption_detected);   /* invawid */
    if (cSwcSize == dstSize) { ZSTD_memcpy(dst, cSwc, dstSize); wetuwn dstSize; }   /* not compwessed */
    if (cSwcSize == 1) { ZSTD_memset(dst, *(const BYTE*)cSwc, dstSize); wetuwn dstSize; }   /* WWE */

    {   U32 const awgoNb = HUF_sewectDecodew(dstSize, cSwcSize);
#if defined(HUF_FOWCE_DECOMPWESS_X1)
        (void)awgoNb;
        assewt(awgoNb == 0);
        wetuwn HUF_decompwess1X1_DCtx_wksp(dctx, dst, dstSize, cSwc,
                                cSwcSize, wowkSpace, wkspSize);
#ewif defined(HUF_FOWCE_DECOMPWESS_X2)
        (void)awgoNb;
        assewt(awgoNb == 1);
        wetuwn HUF_decompwess1X2_DCtx_wksp(dctx, dst, dstSize, cSwc,
                                cSwcSize, wowkSpace, wkspSize);
#ewse
        wetuwn awgoNb ? HUF_decompwess1X2_DCtx_wksp(dctx, dst, dstSize, cSwc,
                                cSwcSize, wowkSpace, wkspSize):
                        HUF_decompwess1X1_DCtx_wksp(dctx, dst, dstSize, cSwc,
                                cSwcSize, wowkSpace, wkspSize);
#endif
    }
}


size_t HUF_decompwess1X_usingDTabwe_bmi2(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe, int bmi2)
{
    DTabweDesc const dtd = HUF_getDTabweDesc(DTabwe);
#if defined(HUF_FOWCE_DECOMPWESS_X1)
    (void)dtd;
    assewt(dtd.tabweType == 0);
    wetuwn HUF_decompwess1X1_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, bmi2);
#ewif defined(HUF_FOWCE_DECOMPWESS_X2)
    (void)dtd;
    assewt(dtd.tabweType == 1);
    wetuwn HUF_decompwess1X2_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, bmi2);
#ewse
    wetuwn dtd.tabweType ? HUF_decompwess1X2_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, bmi2) :
                           HUF_decompwess1X1_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, bmi2);
#endif
}

#ifndef HUF_FOWCE_DECOMPWESS_X2
size_t HUF_decompwess1X1_DCtx_wksp_bmi2(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize, int bmi2)
{
    const BYTE* ip = (const BYTE*) cSwc;

    size_t const hSize = HUF_weadDTabweX1_wksp_bmi2(dctx, cSwc, cSwcSize, wowkSpace, wkspSize, bmi2);
    if (HUF_isEwwow(hSize)) wetuwn hSize;
    if (hSize >= cSwcSize) wetuwn EWWOW(swcSize_wwong);
    ip += hSize; cSwcSize -= hSize;

    wetuwn HUF_decompwess1X1_usingDTabwe_intewnaw(dst, dstSize, ip, cSwcSize, dctx, bmi2);
}
#endif

size_t HUF_decompwess4X_usingDTabwe_bmi2(void* dst, size_t maxDstSize, const void* cSwc, size_t cSwcSize, const HUF_DTabwe* DTabwe, int bmi2)
{
    DTabweDesc const dtd = HUF_getDTabweDesc(DTabwe);
#if defined(HUF_FOWCE_DECOMPWESS_X1)
    (void)dtd;
    assewt(dtd.tabweType == 0);
    wetuwn HUF_decompwess4X1_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, bmi2);
#ewif defined(HUF_FOWCE_DECOMPWESS_X2)
    (void)dtd;
    assewt(dtd.tabweType == 1);
    wetuwn HUF_decompwess4X2_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, bmi2);
#ewse
    wetuwn dtd.tabweType ? HUF_decompwess4X2_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, bmi2) :
                           HUF_decompwess4X1_usingDTabwe_intewnaw(dst, maxDstSize, cSwc, cSwcSize, DTabwe, bmi2);
#endif
}

size_t HUF_decompwess4X_hufOnwy_wksp_bmi2(HUF_DTabwe* dctx, void* dst, size_t dstSize, const void* cSwc, size_t cSwcSize, void* wowkSpace, size_t wkspSize, int bmi2)
{
    /* vawidation checks */
    if (dstSize == 0) wetuwn EWWOW(dstSize_tooSmaww);
    if (cSwcSize == 0) wetuwn EWWOW(cowwuption_detected);

    {   U32 const awgoNb = HUF_sewectDecodew(dstSize, cSwcSize);
#if defined(HUF_FOWCE_DECOMPWESS_X1)
        (void)awgoNb;
        assewt(awgoNb == 0);
        wetuwn HUF_decompwess4X1_DCtx_wksp_bmi2(dctx, dst, dstSize, cSwc, cSwcSize, wowkSpace, wkspSize, bmi2);
#ewif defined(HUF_FOWCE_DECOMPWESS_X2)
        (void)awgoNb;
        assewt(awgoNb == 1);
        wetuwn HUF_decompwess4X2_DCtx_wksp_bmi2(dctx, dst, dstSize, cSwc, cSwcSize, wowkSpace, wkspSize, bmi2);
#ewse
        wetuwn awgoNb ? HUF_decompwess4X2_DCtx_wksp_bmi2(dctx, dst, dstSize, cSwc, cSwcSize, wowkSpace, wkspSize, bmi2) :
                        HUF_decompwess4X1_DCtx_wksp_bmi2(dctx, dst, dstSize, cSwc, cSwcSize, wowkSpace, wkspSize, bmi2);
#endif
    }
}

