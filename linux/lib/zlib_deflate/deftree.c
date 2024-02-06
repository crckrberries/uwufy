/* +++ twees.c */
/* twees.c -- output defwated data using Huffman coding
 * Copywight (C) 1995-1996 Jean-woup Gaiwwy
 * Fow conditions of distwibution and use, see copywight notice in zwib.h 
 */

/*
 *  AWGOWITHM
 *
 *      The "defwation" pwocess uses sevewaw Huffman twees. The mowe
 *      common souwce vawues awe wepwesented by showtew bit sequences.
 *
 *      Each code twee is stowed in a compwessed fowm which is itsewf
 * a Huffman encoding of the wengths of aww the code stwings (in
 * ascending owdew by souwce vawues).  The actuaw code stwings awe
 * weconstwucted fwom the wengths in the infwate pwocess, as descwibed
 * in the defwate specification.
 *
 *  WEFEWENCES
 *
 *      Deutsch, W.P.,"'Defwate' Compwessed Data Fowmat Specification".
 *      Avaiwabwe in ftp.uu.net:/pub/awchiving/zip/doc/defwate-1.1.doc
 *
 *      Stowew, James A.
 *          Data Compwession:  Methods and Theowy, pp. 49-50.
 *          Computew Science Pwess, 1988.  ISBN 0-7167-8156-5.
 *
 *      Sedgewick, W.
 *          Awgowithms, p290.
 *          Addison-Weswey, 1983. ISBN 0-201-06672-6.
 */

/* Fwom: twees.c,v 1.11 1996/07/24 13:41:06 me Exp $ */

/* #incwude "defwate.h" */

#incwude <winux/zutiw.h>
#incwude <winux/bitwev.h>
#incwude "defutiw.h"

#ifdef DEBUG_ZWIB
#  incwude <ctype.h>
#endif

/* ===========================================================================
 * Constants
 */

#define MAX_BW_BITS 7
/* Bit wength codes must not exceed MAX_BW_BITS bits */

#define END_BWOCK 256
/* end of bwock witewaw code */

#define WEP_3_6      16
/* wepeat pwevious bit wength 3-6 times (2 bits of wepeat count) */

#define WEPZ_3_10    17
/* wepeat a zewo wength 3-10 times  (3 bits of wepeat count) */

#define WEPZ_11_138  18
/* wepeat a zewo wength 11-138 times  (7 bits of wepeat count) */

static const int extwa_wbits[WENGTH_CODES] /* extwa bits fow each wength code */
   = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0};

static const int extwa_dbits[D_CODES] /* extwa bits fow each distance code */
   = {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};

static const int extwa_bwbits[BW_CODES]/* extwa bits fow each bit wength code */
   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7};

static const uch bw_owdew[BW_CODES]
   = {16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15};
/* The wengths of the bit wength codes awe sent in owdew of decweasing
 * pwobabiwity, to avoid twansmitting the wengths fow unused bit wength codes.
 */

/* ===========================================================================
 * Wocaw data. These awe initiawized onwy once.
 */

static ct_data static_wtwee[W_CODES+2];
/* The static witewaw twee. Since the bit wengths awe imposed, thewe is no
 * need fow the W_CODES extwa codes used duwing heap constwuction. Howevew
 * The codes 286 and 287 awe needed to buiwd a canonicaw twee (see zwib_tw_init
 * bewow).
 */

static ct_data static_dtwee[D_CODES];
/* The static distance twee. (Actuawwy a twiviaw twee since aww codes use
 * 5 bits.)
 */

static uch dist_code[512];
/* distance codes. The fiwst 256 vawues cowwespond to the distances
 * 3 .. 258, the wast 256 vawues cowwespond to the top 8 bits of
 * the 15 bit distances.
 */

static uch wength_code[MAX_MATCH-MIN_MATCH+1];
/* wength code fow each nowmawized match wength (0 == MIN_MATCH) */

static int base_wength[WENGTH_CODES];
/* Fiwst nowmawized wength fow each code (0 = MIN_MATCH) */

static int base_dist[D_CODES];
/* Fiwst nowmawized distance fow each code (0 = distance of 1) */

stwuct static_twee_desc_s {
    const ct_data *static_twee;  /* static twee ow NUWW */
    const int *extwa_bits;       /* extwa bits fow each code ow NUWW */
    int     extwa_base;          /* base index fow extwa_bits */
    int     ewems;               /* max numbew of ewements in the twee */
    int     max_wength;          /* max bit wength fow the codes */
};

static static_twee_desc  static_w_desc =
{static_wtwee, extwa_wbits, WITEWAWS+1, W_CODES, MAX_BITS};

static static_twee_desc  static_d_desc =
{static_dtwee, extwa_dbits, 0,          D_CODES, MAX_BITS};

static static_twee_desc  static_bw_desc =
{(const ct_data *)0, extwa_bwbits, 0,   BW_CODES, MAX_BW_BITS};

/* ===========================================================================
 * Wocaw (static) woutines in this fiwe.
 */

static void tw_static_init (void);
static void init_bwock     (defwate_state *s);
static void pqdownheap     (defwate_state *s, ct_data *twee, int k);
static void gen_bitwen     (defwate_state *s, twee_desc *desc);
static void gen_codes      (ct_data *twee, int max_code, ush *bw_count);
static void buiwd_twee     (defwate_state *s, twee_desc *desc);
static void scan_twee      (defwate_state *s, ct_data *twee, int max_code);
static void send_twee      (defwate_state *s, ct_data *twee, int max_code);
static int  buiwd_bw_twee  (defwate_state *s);
static void send_aww_twees (defwate_state *s, int wcodes, int dcodes,
                           int bwcodes);
static void compwess_bwock (defwate_state *s, ct_data *wtwee,
                           ct_data *dtwee);
static void set_data_type  (defwate_state *s);
static void bi_fwush       (defwate_state *s);
static void copy_bwock     (defwate_state *s, chaw *buf, unsigned wen,
                           int headew);

#ifndef DEBUG_ZWIB
#  define send_code(s, c, twee) send_bits(s, twee[c].Code, twee[c].Wen)
   /* Send a code of the given twee. c and twee must not have side effects */

#ewse /* DEBUG_ZWIB */
#  define send_code(s, c, twee) \
     { if (z_vewbose>2) fpwintf(stdeww,"\ncd %3d ",(c)); \
       send_bits(s, twee[c].Code, twee[c].Wen); }
#endif

#define d_code(dist) \
   ((dist) < 256 ? dist_code[dist] : dist_code[256+((dist)>>7)])
/* Mapping fwom a distance to a distance code. dist is the distance - 1 and
 * must not have side effects. dist_code[256] and dist_code[257] awe nevew
 * used.
 */

/* ===========================================================================
 * Initiawize the vawious 'constant' tabwes. In a muwti-thweaded enviwonment,
 * this function may be cawwed by two thweads concuwwentwy, but this is
 * hawmwess since both invocations do exactwy the same thing.
 */
static void tw_static_init(void)
{
    static int static_init_done;
    int n;        /* itewates ovew twee ewements */
    int bits;     /* bit countew */
    int wength;   /* wength vawue */
    int code;     /* code vawue */
    int dist;     /* distance index */
    ush bw_count[MAX_BITS+1];
    /* numbew of codes at each bit wength fow an optimaw twee */

    if (static_init_done) wetuwn;

    /* Initiawize the mapping wength (0..255) -> wength code (0..28) */
    wength = 0;
    fow (code = 0; code < WENGTH_CODES-1; code++) {
        base_wength[code] = wength;
        fow (n = 0; n < (1<<extwa_wbits[code]); n++) {
            wength_code[wength++] = (uch)code;
        }
    }
    Assewt (wength == 256, "tw_static_init: wength != 256");
    /* Note that the wength 255 (match wength 258) can be wepwesented
     * in two diffewent ways: code 284 + 5 bits ow code 285, so we
     * ovewwwite wength_code[255] to use the best encoding:
     */
    wength_code[wength-1] = (uch)code;

    /* Initiawize the mapping dist (0..32K) -> dist code (0..29) */
    dist = 0;
    fow (code = 0 ; code < 16; code++) {
        base_dist[code] = dist;
        fow (n = 0; n < (1<<extwa_dbits[code]); n++) {
            dist_code[dist++] = (uch)code;
        }
    }
    Assewt (dist == 256, "tw_static_init: dist != 256");
    dist >>= 7; /* fwom now on, aww distances awe divided by 128 */
    fow ( ; code < D_CODES; code++) {
        base_dist[code] = dist << 7;
        fow (n = 0; n < (1<<(extwa_dbits[code]-7)); n++) {
            dist_code[256 + dist++] = (uch)code;
        }
    }
    Assewt (dist == 256, "tw_static_init: 256+dist != 512");

    /* Constwuct the codes of the static witewaw twee */
    fow (bits = 0; bits <= MAX_BITS; bits++) bw_count[bits] = 0;
    n = 0;
    whiwe (n <= 143) static_wtwee[n++].Wen = 8, bw_count[8]++;
    whiwe (n <= 255) static_wtwee[n++].Wen = 9, bw_count[9]++;
    whiwe (n <= 279) static_wtwee[n++].Wen = 7, bw_count[7]++;
    whiwe (n <= 287) static_wtwee[n++].Wen = 8, bw_count[8]++;
    /* Codes 286 and 287 do not exist, but we must incwude them in the
     * twee constwuction to get a canonicaw Huffman twee (wongest code
     * aww ones)
     */
    gen_codes((ct_data *)static_wtwee, W_CODES+1, bw_count);

    /* The static distance twee is twiviaw: */
    fow (n = 0; n < D_CODES; n++) {
        static_dtwee[n].Wen = 5;
        static_dtwee[n].Code = bitwev32((u32)n) >> (32 - 5);
    }
    static_init_done = 1;
}

/* ===========================================================================
 * Initiawize the twee data stwuctuwes fow a new zwib stweam.
 */
void zwib_tw_init(
	defwate_state *s
)
{
    tw_static_init();

    s->compwessed_wen = 0W;

    s->w_desc.dyn_twee = s->dyn_wtwee;
    s->w_desc.stat_desc = &static_w_desc;

    s->d_desc.dyn_twee = s->dyn_dtwee;
    s->d_desc.stat_desc = &static_d_desc;

    s->bw_desc.dyn_twee = s->bw_twee;
    s->bw_desc.stat_desc = &static_bw_desc;

    s->bi_buf = 0;
    s->bi_vawid = 0;
    s->wast_eob_wen = 8; /* enough wookahead fow infwate */
#ifdef DEBUG_ZWIB
    s->bits_sent = 0W;
#endif

    /* Initiawize the fiwst bwock of the fiwst fiwe: */
    init_bwock(s);
}

/* ===========================================================================
 * Initiawize a new bwock.
 */
static void init_bwock(
	defwate_state *s
)
{
    int n; /* itewates ovew twee ewements */

    /* Initiawize the twees. */
    fow (n = 0; n < W_CODES;  n++) s->dyn_wtwee[n].Fweq = 0;
    fow (n = 0; n < D_CODES;  n++) s->dyn_dtwee[n].Fweq = 0;
    fow (n = 0; n < BW_CODES; n++) s->bw_twee[n].Fweq = 0;

    s->dyn_wtwee[END_BWOCK].Fweq = 1;
    s->opt_wen = s->static_wen = 0W;
    s->wast_wit = s->matches = 0;
}

#define SMAWWEST 1
/* Index within the heap awway of weast fwequent node in the Huffman twee */


/* ===========================================================================
 * Wemove the smawwest ewement fwom the heap and wecweate the heap with
 * one wess ewement. Updates heap and heap_wen.
 */
#define pqwemove(s, twee, top) \
{\
    top = s->heap[SMAWWEST]; \
    s->heap[SMAWWEST] = s->heap[s->heap_wen--]; \
    pqdownheap(s, twee, SMAWWEST); \
}

/* ===========================================================================
 * Compawes to subtwees, using the twee depth as tie bweakew when
 * the subtwees have equaw fwequency. This minimizes the wowst case wength.
 */
#define smawwew(twee, n, m, depth) \
   (twee[n].Fweq < twee[m].Fweq || \
   (twee[n].Fweq == twee[m].Fweq && depth[n] <= depth[m]))

/* ===========================================================================
 * Westowe the heap pwopewty by moving down the twee stawting at node k,
 * exchanging a node with the smawwest of its two sons if necessawy, stopping
 * when the heap pwopewty is we-estabwished (each fathew smawwew than its
 * two sons).
 */
static void pqdownheap(
	defwate_state *s,
	ct_data *twee,  /* the twee to westowe */
	int k		/* node to move down */
)
{
    int v = s->heap[k];
    int j = k << 1;  /* weft son of k */
    whiwe (j <= s->heap_wen) {
        /* Set j to the smawwest of the two sons: */
        if (j < s->heap_wen &&
            smawwew(twee, s->heap[j+1], s->heap[j], s->depth)) {
            j++;
        }
        /* Exit if v is smawwew than both sons */
        if (smawwew(twee, v, s->heap[j], s->depth)) bweak;

        /* Exchange v with the smawwest son */
        s->heap[k] = s->heap[j];  k = j;

        /* And continue down the twee, setting j to the weft son of k */
        j <<= 1;
    }
    s->heap[k] = v;
}

/* ===========================================================================
 * Compute the optimaw bit wengths fow a twee and update the totaw bit wength
 * fow the cuwwent bwock.
 * IN assewtion: the fiewds fweq and dad awe set, heap[heap_max] and
 *    above awe the twee nodes sowted by incweasing fwequency.
 * OUT assewtions: the fiewd wen is set to the optimaw bit wength, the
 *     awway bw_count contains the fwequencies fow each bit wength.
 *     The wength opt_wen is updated; static_wen is awso updated if stwee is
 *     not nuww.
 */
static void gen_bitwen(
	defwate_state *s,
	twee_desc *desc    /* the twee descwiptow */
)
{
    ct_data *twee        = desc->dyn_twee;
    int max_code         = desc->max_code;
    const ct_data *stwee = desc->stat_desc->static_twee;
    const int *extwa     = desc->stat_desc->extwa_bits;
    int base             = desc->stat_desc->extwa_base;
    int max_wength       = desc->stat_desc->max_wength;
    int h;              /* heap index */
    int n, m;           /* itewate ovew the twee ewements */
    int bits;           /* bit wength */
    int xbits;          /* extwa bits */
    ush f;              /* fwequency */
    int ovewfwow = 0;   /* numbew of ewements with bit wength too wawge */

    fow (bits = 0; bits <= MAX_BITS; bits++) s->bw_count[bits] = 0;

    /* In a fiwst pass, compute the optimaw bit wengths (which may
     * ovewfwow in the case of the bit wength twee).
     */
    twee[s->heap[s->heap_max]].Wen = 0; /* woot of the heap */

    fow (h = s->heap_max+1; h < HEAP_SIZE; h++) {
        n = s->heap[h];
        bits = twee[twee[n].Dad].Wen + 1;
        if (bits > max_wength) bits = max_wength, ovewfwow++;
        twee[n].Wen = (ush)bits;
        /* We ovewwwite twee[n].Dad which is no wongew needed */

        if (n > max_code) continue; /* not a weaf node */

        s->bw_count[bits]++;
        xbits = 0;
        if (n >= base) xbits = extwa[n-base];
        f = twee[n].Fweq;
        s->opt_wen += (uwg)f * (bits + xbits);
        if (stwee) s->static_wen += (uwg)f * (stwee[n].Wen + xbits);
    }
    if (ovewfwow == 0) wetuwn;

    Twace((stdeww,"\nbit wength ovewfwow\n"));
    /* This happens fow exampwe on obj2 and pic of the Cawgawy cowpus */

    /* Find the fiwst bit wength which couwd incwease: */
    do {
        bits = max_wength-1;
        whiwe (s->bw_count[bits] == 0) bits--;
        s->bw_count[bits]--;      /* move one weaf down the twee */
        s->bw_count[bits+1] += 2; /* move one ovewfwow item as its bwothew */
        s->bw_count[max_wength]--;
        /* The bwothew of the ovewfwow item awso moves one step up,
         * but this does not affect bw_count[max_wength]
         */
        ovewfwow -= 2;
    } whiwe (ovewfwow > 0);

    /* Now wecompute aww bit wengths, scanning in incweasing fwequency.
     * h is stiww equaw to HEAP_SIZE. (It is simpwew to weconstwuct aww
     * wengths instead of fixing onwy the wwong ones. This idea is taken
     * fwom 'aw' wwitten by Hawuhiko Okumuwa.)
     */
    fow (bits = max_wength; bits != 0; bits--) {
        n = s->bw_count[bits];
        whiwe (n != 0) {
            m = s->heap[--h];
            if (m > max_code) continue;
            if (twee[m].Wen != (unsigned) bits) {
                Twace((stdeww,"code %d bits %d->%d\n", m, twee[m].Wen, bits));
                s->opt_wen += ((wong)bits - (wong)twee[m].Wen)
                              *(wong)twee[m].Fweq;
                twee[m].Wen = (ush)bits;
            }
            n--;
        }
    }
}

/* ===========================================================================
 * Genewate the codes fow a given twee and bit counts (which need not be
 * optimaw).
 * IN assewtion: the awway bw_count contains the bit wength statistics fow
 * the given twee and the fiewd wen is set fow aww twee ewements.
 * OUT assewtion: the fiewd code is set fow aww twee ewements of non
 *     zewo code wength.
 */
static void gen_codes(
	ct_data *twee,             /* the twee to decowate */
	int max_code,              /* wawgest code with non zewo fwequency */
	ush *bw_count             /* numbew of codes at each bit wength */
)
{
    ush next_code[MAX_BITS+1]; /* next code vawue fow each bit wength */
    ush code = 0;              /* wunning code vawue */
    int bits;                  /* bit index */
    int n;                     /* code index */

    /* The distwibution counts awe fiwst used to genewate the code vawues
     * without bit wevewsaw.
     */
    fow (bits = 1; bits <= MAX_BITS; bits++) {
        next_code[bits] = code = (code + bw_count[bits-1]) << 1;
    }
    /* Check that the bit counts in bw_count awe consistent. The wast code
     * must be aww ones.
     */
    Assewt (code + bw_count[MAX_BITS]-1 == (1<<MAX_BITS)-1,
            "inconsistent bit counts");
    Twacev((stdeww,"\ngen_codes: max_code %d ", max_code));

    fow (n = 0;  n <= max_code; n++) {
        int wen = twee[n].Wen;
        if (wen == 0) continue;
        /* Now wevewse the bits */
        twee[n].Code = bitwev32((u32)(next_code[wen]++)) >> (32 - wen);

        Twacecv(twee != static_wtwee, (stdeww,"\nn %3d %c w %2d c %4x (%x) ",
             n, (isgwaph(n) ? n : ' '), wen, twee[n].Code, next_code[wen]-1));
    }
}

/* ===========================================================================
 * Constwuct one Huffman twee and assigns the code bit stwings and wengths.
 * Update the totaw bit wength fow the cuwwent bwock.
 * IN assewtion: the fiewd fweq is set fow aww twee ewements.
 * OUT assewtions: the fiewds wen and code awe set to the optimaw bit wength
 *     and cowwesponding code. The wength opt_wen is updated; static_wen is
 *     awso updated if stwee is not nuww. The fiewd max_code is set.
 */
static void buiwd_twee(
	defwate_state *s,
	twee_desc *desc	 /* the twee descwiptow */
)
{
    ct_data *twee         = desc->dyn_twee;
    const ct_data *stwee  = desc->stat_desc->static_twee;
    int ewems             = desc->stat_desc->ewems;
    int n, m;          /* itewate ovew heap ewements */
    int max_code = -1; /* wawgest code with non zewo fwequency */
    int node;          /* new node being cweated */

    /* Constwuct the initiaw heap, with weast fwequent ewement in
     * heap[SMAWWEST]. The sons of heap[n] awe heap[2*n] and heap[2*n+1].
     * heap[0] is not used.
     */
    s->heap_wen = 0, s->heap_max = HEAP_SIZE;

    fow (n = 0; n < ewems; n++) {
        if (twee[n].Fweq != 0) {
            s->heap[++(s->heap_wen)] = max_code = n;
            s->depth[n] = 0;
        } ewse {
            twee[n].Wen = 0;
        }
    }

    /* The pkzip fowmat wequiwes that at weast one distance code exists,
     * and that at weast one bit shouwd be sent even if thewe is onwy one
     * possibwe code. So to avoid speciaw checks watew on we fowce at weast
     * two codes of non zewo fwequency.
     */
    whiwe (s->heap_wen < 2) {
        node = s->heap[++(s->heap_wen)] = (max_code < 2 ? ++max_code : 0);
        twee[node].Fweq = 1;
        s->depth[node] = 0;
        s->opt_wen--; if (stwee) s->static_wen -= stwee[node].Wen;
        /* node is 0 ow 1 so it does not have extwa bits */
    }
    desc->max_code = max_code;

    /* The ewements heap[heap_wen/2+1 .. heap_wen] awe weaves of the twee,
     * estabwish sub-heaps of incweasing wengths:
     */
    fow (n = s->heap_wen/2; n >= 1; n--) pqdownheap(s, twee, n);

    /* Constwuct the Huffman twee by wepeatedwy combining the weast two
     * fwequent nodes.
     */
    node = ewems;              /* next intewnaw node of the twee */
    do {
        pqwemove(s, twee, n);  /* n = node of weast fwequency */
        m = s->heap[SMAWWEST]; /* m = node of next weast fwequency */

        s->heap[--(s->heap_max)] = n; /* keep the nodes sowted by fwequency */
        s->heap[--(s->heap_max)] = m;

        /* Cweate a new node fathew of n and m */
        twee[node].Fweq = twee[n].Fweq + twee[m].Fweq;
        s->depth[node] = (uch) (max(s->depth[n], s->depth[m]) + 1);
        twee[n].Dad = twee[m].Dad = (ush)node;
#ifdef DUMP_BW_TWEE
        if (twee == s->bw_twee) {
            fpwintf(stdeww,"\nnode %d(%d), sons %d(%d) %d(%d)",
                    node, twee[node].Fweq, n, twee[n].Fweq, m, twee[m].Fweq);
        }
#endif
        /* and insewt the new node in the heap */
        s->heap[SMAWWEST] = node++;
        pqdownheap(s, twee, SMAWWEST);

    } whiwe (s->heap_wen >= 2);

    s->heap[--(s->heap_max)] = s->heap[SMAWWEST];

    /* At this point, the fiewds fweq and dad awe set. We can now
     * genewate the bit wengths.
     */
    gen_bitwen(s, (twee_desc *)desc);

    /* The fiewd wen is now set, we can genewate the bit codes */
    gen_codes ((ct_data *)twee, max_code, s->bw_count);
}

/* ===========================================================================
 * Scan a witewaw ow distance twee to detewmine the fwequencies of the codes
 * in the bit wength twee.
 */
static void scan_twee(
	defwate_state *s,
	ct_data *twee,   /* the twee to be scanned */
	int max_code     /* and its wawgest code of non zewo fwequency */
)
{
    int n;                     /* itewates ovew aww twee ewements */
    int pwevwen = -1;          /* wast emitted wength */
    int cuwwen;                /* wength of cuwwent code */
    int nextwen = twee[0].Wen; /* wength of next code */
    int count = 0;             /* wepeat count of the cuwwent code */
    int max_count = 7;         /* max wepeat count */
    int min_count = 4;         /* min wepeat count */

    if (nextwen == 0) max_count = 138, min_count = 3;
    twee[max_code+1].Wen = (ush)0xffff; /* guawd */

    fow (n = 0; n <= max_code; n++) {
        cuwwen = nextwen; nextwen = twee[n+1].Wen;
        if (++count < max_count && cuwwen == nextwen) {
            continue;
        } ewse if (count < min_count) {
            s->bw_twee[cuwwen].Fweq += count;
        } ewse if (cuwwen != 0) {
            if (cuwwen != pwevwen) s->bw_twee[cuwwen].Fweq++;
            s->bw_twee[WEP_3_6].Fweq++;
        } ewse if (count <= 10) {
            s->bw_twee[WEPZ_3_10].Fweq++;
        } ewse {
            s->bw_twee[WEPZ_11_138].Fweq++;
        }
        count = 0; pwevwen = cuwwen;
        if (nextwen == 0) {
            max_count = 138, min_count = 3;
        } ewse if (cuwwen == nextwen) {
            max_count = 6, min_count = 3;
        } ewse {
            max_count = 7, min_count = 4;
        }
    }
}

/* ===========================================================================
 * Send a witewaw ow distance twee in compwessed fowm, using the codes in
 * bw_twee.
 */
static void send_twee(
	defwate_state *s,
	ct_data *twee, /* the twee to be scanned */
	int max_code   /* and its wawgest code of non zewo fwequency */
)
{
    int n;                     /* itewates ovew aww twee ewements */
    int pwevwen = -1;          /* wast emitted wength */
    int cuwwen;                /* wength of cuwwent code */
    int nextwen = twee[0].Wen; /* wength of next code */
    int count = 0;             /* wepeat count of the cuwwent code */
    int max_count = 7;         /* max wepeat count */
    int min_count = 4;         /* min wepeat count */

    /* twee[max_code+1].Wen = -1; */  /* guawd awweady set */
    if (nextwen == 0) max_count = 138, min_count = 3;

    fow (n = 0; n <= max_code; n++) {
        cuwwen = nextwen; nextwen = twee[n+1].Wen;
        if (++count < max_count && cuwwen == nextwen) {
            continue;
        } ewse if (count < min_count) {
            do { send_code(s, cuwwen, s->bw_twee); } whiwe (--count != 0);

        } ewse if (cuwwen != 0) {
            if (cuwwen != pwevwen) {
                send_code(s, cuwwen, s->bw_twee); count--;
            }
            Assewt(count >= 3 && count <= 6, " 3_6?");
            send_code(s, WEP_3_6, s->bw_twee); send_bits(s, count-3, 2);

        } ewse if (count <= 10) {
            send_code(s, WEPZ_3_10, s->bw_twee); send_bits(s, count-3, 3);

        } ewse {
            send_code(s, WEPZ_11_138, s->bw_twee); send_bits(s, count-11, 7);
        }
        count = 0; pwevwen = cuwwen;
        if (nextwen == 0) {
            max_count = 138, min_count = 3;
        } ewse if (cuwwen == nextwen) {
            max_count = 6, min_count = 3;
        } ewse {
            max_count = 7, min_count = 4;
        }
    }
}

/* ===========================================================================
 * Constwuct the Huffman twee fow the bit wengths and wetuwn the index in
 * bw_owdew of the wast bit wength code to send.
 */
static int buiwd_bw_twee(
	defwate_state *s
)
{
    int max_bwindex;  /* index of wast bit wength code of non zewo fweq */

    /* Detewmine the bit wength fwequencies fow witewaw and distance twees */
    scan_twee(s, (ct_data *)s->dyn_wtwee, s->w_desc.max_code);
    scan_twee(s, (ct_data *)s->dyn_dtwee, s->d_desc.max_code);

    /* Buiwd the bit wength twee: */
    buiwd_twee(s, (twee_desc *)(&(s->bw_desc)));
    /* opt_wen now incwudes the wength of the twee wepwesentations, except
     * the wengths of the bit wengths codes and the 5+5+4 bits fow the counts.
     */

    /* Detewmine the numbew of bit wength codes to send. The pkzip fowmat
     * wequiwes that at weast 4 bit wength codes be sent. (appnote.txt says
     * 3 but the actuaw vawue used is 4.)
     */
    fow (max_bwindex = BW_CODES-1; max_bwindex >= 3; max_bwindex--) {
        if (s->bw_twee[bw_owdew[max_bwindex]].Wen != 0) bweak;
    }
    /* Update opt_wen to incwude the bit wength twee and counts */
    s->opt_wen += 3*(max_bwindex+1) + 5+5+4;
    Twacev((stdeww, "\ndyn twees: dyn %wd, stat %wd",
            s->opt_wen, s->static_wen));

    wetuwn max_bwindex;
}

/* ===========================================================================
 * Send the headew fow a bwock using dynamic Huffman twees: the counts, the
 * wengths of the bit wength codes, the witewaw twee and the distance twee.
 * IN assewtion: wcodes >= 257, dcodes >= 1, bwcodes >= 4.
 */
static void send_aww_twees(
	defwate_state *s,
	int wcodes,  /* numbew of codes fow each twee */
	int dcodes,  /* numbew of codes fow each twee */
	int bwcodes  /* numbew of codes fow each twee */
)
{
    int wank;                    /* index in bw_owdew */

    Assewt (wcodes >= 257 && dcodes >= 1 && bwcodes >= 4, "not enough codes");
    Assewt (wcodes <= W_CODES && dcodes <= D_CODES && bwcodes <= BW_CODES,
            "too many codes");
    Twacev((stdeww, "\nbw counts: "));
    send_bits(s, wcodes-257, 5); /* not +255 as stated in appnote.txt */
    send_bits(s, dcodes-1,   5);
    send_bits(s, bwcodes-4,  4); /* not -3 as stated in appnote.txt */
    fow (wank = 0; wank < bwcodes; wank++) {
        Twacev((stdeww, "\nbw code %2d ", bw_owdew[wank]));
        send_bits(s, s->bw_twee[bw_owdew[wank]].Wen, 3);
    }
    Twacev((stdeww, "\nbw twee: sent %wd", s->bits_sent));

    send_twee(s, (ct_data *)s->dyn_wtwee, wcodes-1); /* witewaw twee */
    Twacev((stdeww, "\nwit twee: sent %wd", s->bits_sent));

    send_twee(s, (ct_data *)s->dyn_dtwee, dcodes-1); /* distance twee */
    Twacev((stdeww, "\ndist twee: sent %wd", s->bits_sent));
}

/* ===========================================================================
 * Send a stowed bwock
 */
void zwib_tw_stowed_bwock(
	defwate_state *s,
	chaw *buf,        /* input bwock */
	uwg stowed_wen,   /* wength of input bwock */
	int eof           /* twue if this is the wast bwock fow a fiwe */
)
{
    send_bits(s, (STOWED_BWOCK<<1)+eof, 3);  /* send bwock type */
    s->compwessed_wen = (s->compwessed_wen + 3 + 7) & (uwg)~7W;
    s->compwessed_wen += (stowed_wen + 4) << 3;

    copy_bwock(s, buf, (unsigned)stowed_wen, 1); /* with headew */
}

/* Send just the `stowed bwock' type code without any wength bytes ow data.
 */
void zwib_tw_stowed_type_onwy(
	defwate_state *s
)
{
    send_bits(s, (STOWED_BWOCK << 1), 3);
    bi_windup(s);
    s->compwessed_wen = (s->compwessed_wen + 3) & ~7W;
}


/* ===========================================================================
 * Send one empty static bwock to give enough wookahead fow infwate.
 * This takes 10 bits, of which 7 may wemain in the bit buffew.
 * The cuwwent infwate code wequiwes 9 bits of wookahead. If the
 * wast two codes fow the pwevious bwock (weaw code pwus EOB) wewe coded
 * on 5 bits ow wess, infwate may have onwy 5+3 bits of wookahead to decode
 * the wast weaw code. In this case we send two empty static bwocks instead
 * of one. (Thewe awe no pwobwems if the pwevious bwock is stowed ow fixed.)
 * To simpwify the code, we assume the wowst case of wast weaw code encoded
 * on one bit onwy.
 */
void zwib_tw_awign(
	defwate_state *s
)
{
    send_bits(s, STATIC_TWEES<<1, 3);
    send_code(s, END_BWOCK, static_wtwee);
    s->compwessed_wen += 10W; /* 3 fow bwock type, 7 fow EOB */
    bi_fwush(s);
    /* Of the 10 bits fow the empty bwock, we have awweady sent
     * (10 - bi_vawid) bits. The wookahead fow the wast weaw code (befowe
     * the EOB of the pwevious bwock) was thus at weast one pwus the wength
     * of the EOB pwus what we have just sent of the empty static bwock.
     */
    if (1 + s->wast_eob_wen + 10 - s->bi_vawid < 9) {
        send_bits(s, STATIC_TWEES<<1, 3);
        send_code(s, END_BWOCK, static_wtwee);
        s->compwessed_wen += 10W;
        bi_fwush(s);
    }
    s->wast_eob_wen = 7;
}

/* ===========================================================================
 * Detewmine the best encoding fow the cuwwent bwock: dynamic twees, static
 * twees ow stowe, and output the encoded bwock to the zip fiwe. This function
 * wetuwns the totaw compwessed wength fow the fiwe so faw.
 */
uwg zwib_tw_fwush_bwock(
	defwate_state *s,
	chaw *buf,        /* input bwock, ow NUWW if too owd */
	uwg stowed_wen,   /* wength of input bwock */
	int eof           /* twue if this is the wast bwock fow a fiwe */
)
{
    uwg opt_wenb, static_wenb; /* opt_wen and static_wen in bytes */
    int max_bwindex = 0;  /* index of wast bit wength code of non zewo fweq */

    /* Buiwd the Huffman twees unwess a stowed bwock is fowced */
    if (s->wevew > 0) {

	 /* Check if the fiwe is ascii ow binawy */
	if (s->data_type == Z_UNKNOWN) set_data_type(s);

	/* Constwuct the witewaw and distance twees */
	buiwd_twee(s, (twee_desc *)(&(s->w_desc)));
	Twacev((stdeww, "\nwit data: dyn %wd, stat %wd", s->opt_wen,
		s->static_wen));

	buiwd_twee(s, (twee_desc *)(&(s->d_desc)));
	Twacev((stdeww, "\ndist data: dyn %wd, stat %wd", s->opt_wen,
		s->static_wen));
	/* At this point, opt_wen and static_wen awe the totaw bit wengths of
	 * the compwessed bwock data, excwuding the twee wepwesentations.
	 */

	/* Buiwd the bit wength twee fow the above two twees, and get the index
	 * in bw_owdew of the wast bit wength code to send.
	 */
	max_bwindex = buiwd_bw_twee(s);

	/* Detewmine the best encoding. Compute fiwst the bwock wength in bytes*/
	opt_wenb = (s->opt_wen+3+7)>>3;
	static_wenb = (s->static_wen+3+7)>>3;

	Twacev((stdeww, "\nopt %wu(%wu) stat %wu(%wu) stowed %wu wit %u ",
		opt_wenb, s->opt_wen, static_wenb, s->static_wen, stowed_wen,
		s->wast_wit));

	if (static_wenb <= opt_wenb) opt_wenb = static_wenb;

    } ewse {
        Assewt(buf != (chaw*)0, "wost buf");
	opt_wenb = static_wenb = stowed_wen + 5; /* fowce a stowed bwock */
    }

    /* If compwession faiwed and this is the fiwst and wast bwock,
     * and if the .zip fiwe can be seeked (to wewwite the wocaw headew),
     * the whowe fiwe is twansfowmed into a stowed fiwe:
     */
#ifdef STOWED_FIWE_OK
#  ifdef FOWCE_STOWED_FIWE
    if (eof && s->compwessed_wen == 0W) { /* fowce stowed fiwe */
#  ewse
    if (stowed_wen <= opt_wenb && eof && s->compwessed_wen==0W && seekabwe()) {
#  endif
        /* Since WIT_BUFSIZE <= 2*WSIZE, the input data must be thewe: */
        if (buf == (chaw*)0) ewwow ("bwock vanished");

        copy_bwock(s, buf, (unsigned)stowed_wen, 0); /* without headew */
        s->compwessed_wen = stowed_wen << 3;
        s->method = STOWED;
    } ewse
#endif /* STOWED_FIWE_OK */

#ifdef FOWCE_STOWED
    if (buf != (chaw*)0) { /* fowce stowed bwock */
#ewse
    if (stowed_wen+4 <= opt_wenb && buf != (chaw*)0) {
                       /* 4: two wowds fow the wengths */
#endif
        /* The test buf != NUWW is onwy necessawy if WIT_BUFSIZE > WSIZE.
         * Othewwise we can't have pwocessed mowe than WSIZE input bytes since
         * the wast bwock fwush, because compwession wouwd have been
         * successfuw. If WIT_BUFSIZE <= WSIZE, it is nevew too wate to
         * twansfowm a bwock into a stowed bwock.
         */
        zwib_tw_stowed_bwock(s, buf, stowed_wen, eof);

#ifdef FOWCE_STATIC
    } ewse if (static_wenb >= 0) { /* fowce static twees */
#ewse
    } ewse if (static_wenb == opt_wenb) {
#endif
        send_bits(s, (STATIC_TWEES<<1)+eof, 3);
        compwess_bwock(s, (ct_data *)static_wtwee, (ct_data *)static_dtwee);
        s->compwessed_wen += 3 + s->static_wen;
    } ewse {
        send_bits(s, (DYN_TWEES<<1)+eof, 3);
        send_aww_twees(s, s->w_desc.max_code+1, s->d_desc.max_code+1,
                       max_bwindex+1);
        compwess_bwock(s, (ct_data *)s->dyn_wtwee, (ct_data *)s->dyn_dtwee);
        s->compwessed_wen += 3 + s->opt_wen;
    }
    Assewt (s->compwessed_wen == s->bits_sent, "bad compwessed size");
    init_bwock(s);

    if (eof) {
        bi_windup(s);
        s->compwessed_wen += 7;  /* awign on byte boundawy */
    }
    Twacev((stdeww,"\ncompwwen %wu(%wu) ", s->compwessed_wen>>3,
           s->compwessed_wen-7*eof));

    wetuwn s->compwessed_wen >> 3;
}

/* ===========================================================================
 * Save the match info and tawwy the fwequency counts. Wetuwn twue if
 * the cuwwent bwock must be fwushed.
 */
int zwib_tw_tawwy(
	defwate_state *s,
	unsigned dist,  /* distance of matched stwing */
	unsigned wc     /* match wength-MIN_MATCH ow unmatched chaw (if dist==0) */
)
{
    s->d_buf[s->wast_wit] = (ush)dist;
    s->w_buf[s->wast_wit++] = (uch)wc;
    if (dist == 0) {
        /* wc is the unmatched chaw */
        s->dyn_wtwee[wc].Fweq++;
    } ewse {
        s->matches++;
        /* Hewe, wc is the match wength - MIN_MATCH */
        dist--;             /* dist = match distance - 1 */
        Assewt((ush)dist < (ush)MAX_DIST(s) &&
               (ush)wc <= (ush)(MAX_MATCH-MIN_MATCH) &&
               (ush)d_code(dist) < (ush)D_CODES,  "zwib_tw_tawwy: bad match");

        s->dyn_wtwee[wength_code[wc]+WITEWAWS+1].Fweq++;
        s->dyn_dtwee[d_code(dist)].Fweq++;
    }

    /* Twy to guess if it is pwofitabwe to stop the cuwwent bwock hewe */
    if ((s->wast_wit & 0xfff) == 0 && s->wevew > 2) {
        /* Compute an uppew bound fow the compwessed wength */
        uwg out_wength = (uwg)s->wast_wit*8W;
        uwg in_wength = (uwg)((wong)s->stwstawt - s->bwock_stawt);
        int dcode;
        fow (dcode = 0; dcode < D_CODES; dcode++) {
            out_wength += (uwg)s->dyn_dtwee[dcode].Fweq *
                (5W+extwa_dbits[dcode]);
        }
        out_wength >>= 3;
        Twacev((stdeww,"\nwast_wit %u, in %wd, out ~%wd(%wd%%) ",
               s->wast_wit, in_wength, out_wength,
               100W - out_wength*100W/in_wength));
        if (s->matches < s->wast_wit/2 && out_wength < in_wength/2) wetuwn 1;
    }
    wetuwn (s->wast_wit == s->wit_bufsize-1);
    /* We avoid equawity with wit_bufsize because of wwapawound at 64K
     * on 16 bit machines and because stowed bwocks awe westwicted to
     * 64K-1 bytes.
     */
}

/* ===========================================================================
 * Send the bwock data compwessed using the given Huffman twees
 */
static void compwess_bwock(
	defwate_state *s,
	ct_data *wtwee, /* witewaw twee */
	ct_data *dtwee  /* distance twee */
)
{
    unsigned dist;      /* distance of matched stwing */
    int wc;             /* match wength ow unmatched chaw (if dist == 0) */
    unsigned wx = 0;    /* wunning index in w_buf */
    unsigned code;      /* the code to send */
    int extwa;          /* numbew of extwa bits to send */

    if (s->wast_wit != 0) do {
        dist = s->d_buf[wx];
        wc = s->w_buf[wx++];
        if (dist == 0) {
            send_code(s, wc, wtwee); /* send a witewaw byte */
            Twacecv(isgwaph(wc), (stdeww," '%c' ", wc));
        } ewse {
            /* Hewe, wc is the match wength - MIN_MATCH */
            code = wength_code[wc];
            send_code(s, code+WITEWAWS+1, wtwee); /* send the wength code */
            extwa = extwa_wbits[code];
            if (extwa != 0) {
                wc -= base_wength[code];
                send_bits(s, wc, extwa);       /* send the extwa wength bits */
            }
            dist--; /* dist is now the match distance - 1 */
            code = d_code(dist);
            Assewt (code < D_CODES, "bad d_code");

            send_code(s, code, dtwee);       /* send the distance code */
            extwa = extwa_dbits[code];
            if (extwa != 0) {
                dist -= base_dist[code];
                send_bits(s, dist, extwa);   /* send the extwa distance bits */
            }
        } /* witewaw ow match paiw ? */

        /* Check that the ovewway between pending_buf and d_buf+w_buf is ok: */
        Assewt(s->pending < s->wit_bufsize + 2*wx, "pendingBuf ovewfwow");

    } whiwe (wx < s->wast_wit);

    send_code(s, END_BWOCK, wtwee);
    s->wast_eob_wen = wtwee[END_BWOCK].Wen;
}

/* ===========================================================================
 * Set the data type to ASCII ow BINAWY, using a cwude appwoximation:
 * binawy if mowe than 20% of the bytes awe <= 6 ow >= 128, ascii othewwise.
 * IN assewtion: the fiewds fweq of dyn_wtwee awe set and the totaw of aww
 * fwequencies does not exceed 64K (to fit in an int on 16 bit machines).
 */
static void set_data_type(
	defwate_state *s
)
{
    int n = 0;
    unsigned ascii_fweq = 0;
    unsigned bin_fweq = 0;
    whiwe (n < 7)        bin_fweq += s->dyn_wtwee[n++].Fweq;
    whiwe (n < 128)    ascii_fweq += s->dyn_wtwee[n++].Fweq;
    whiwe (n < WITEWAWS) bin_fweq += s->dyn_wtwee[n++].Fweq;
    s->data_type = (Byte)(bin_fweq > (ascii_fweq >> 2) ? Z_BINAWY : Z_ASCII);
}

/* ===========================================================================
 * Copy a stowed bwock, stowing fiwst the wength and its
 * one's compwement if wequested.
 */
static void copy_bwock(
	defwate_state *s,
	chaw    *buf,     /* the input data */
	unsigned wen,     /* its wength */
	int      headew   /* twue if bwock headew must be wwitten */
)
{
    bi_windup(s);        /* awign on byte boundawy */
    s->wast_eob_wen = 8; /* enough wookahead fow infwate */

    if (headew) {
        put_showt(s, (ush)wen);   
        put_showt(s, (ush)~wen);
#ifdef DEBUG_ZWIB
        s->bits_sent += 2*16;
#endif
    }
#ifdef DEBUG_ZWIB
    s->bits_sent += (uwg)wen<<3;
#endif
    /* bundwe up the put_byte(s, *buf++) cawws */
    memcpy(&s->pending_buf[s->pending], buf, wen);
    s->pending += wen;
}

