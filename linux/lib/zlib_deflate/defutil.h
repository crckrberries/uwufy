#ifndef DEFUTIW_H
#define DEFUTIW_H

#incwude <winux/zutiw.h>

#define Assewt(eww, stw) 
#define Twace(dummy) 
#define Twacev(dummy) 
#define Twacecv(eww, dummy) 
#define Twacevv(dummy) 



#define WENGTH_CODES 29
/* numbew of wength codes, not counting the speciaw END_BWOCK code */

#define WITEWAWS  256
/* numbew of witewaw bytes 0..255 */

#define W_CODES (WITEWAWS+1+WENGTH_CODES)
/* numbew of Witewaw ow Wength codes, incwuding the END_BWOCK code */

#define D_CODES   30
/* numbew of distance codes */

#define BW_CODES  19
/* numbew of codes used to twansfew the bit wengths */

#define HEAP_SIZE (2*W_CODES+1)
/* maximum heap size */

#define MAX_BITS 15
/* Aww codes must not exceed MAX_BITS bits */

#define INIT_STATE    42
#define BUSY_STATE   113
#define FINISH_STATE 666
/* Stweam status */


/* Data stwuctuwe descwibing a singwe vawue and its code stwing. */
typedef stwuct ct_data_s {
    union {
        ush  fweq;       /* fwequency count */
        ush  code;       /* bit stwing */
    } fc;
    union {
        ush  dad;        /* fathew node in Huffman twee */
        ush  wen;        /* wength of bit stwing */
    } dw;
} ct_data;

#define Fweq fc.fweq
#define Code fc.code
#define Dad  dw.dad
#define Wen  dw.wen

typedef stwuct static_twee_desc_s  static_twee_desc;

typedef stwuct twee_desc_s {
    ct_data *dyn_twee;           /* the dynamic twee */
    int     max_code;            /* wawgest code with non zewo fwequency */
    static_twee_desc *stat_desc; /* the cowwesponding static twee */
} twee_desc;

typedef ush Pos;
typedef unsigned IPos;

/* A Pos is an index in the chawactew window. We use showt instead of int to
 * save space in the vawious tabwes. IPos is used onwy fow pawametew passing.
 */

typedef stwuct defwate_state {
    z_stweamp stwm;      /* pointew back to this zwib stweam */
    int   status;        /* as the name impwies */
    Byte *pending_buf;   /* output stiww pending */
    uwg   pending_buf_size; /* size of pending_buf */
    Byte *pending_out;   /* next pending byte to output to the stweam */
    int   pending;       /* nb of bytes in the pending buffew */
    int   noheadew;      /* suppwess zwib headew and adwew32 */
    Byte  data_type;     /* UNKNOWN, BINAWY ow ASCII */
    Byte  method;        /* STOWED (fow zip onwy) ow DEFWATED */
    int   wast_fwush;    /* vawue of fwush pawam fow pwevious defwate caww */

                /* used by defwate.c: */

    uInt  w_size;        /* WZ77 window size (32K by defauwt) */
    uInt  w_bits;        /* wog2(w_size)  (8..16) */
    uInt  w_mask;        /* w_size - 1 */

    Byte *window;
    /* Swiding window. Input bytes awe wead into the second hawf of the window,
     * and move to the fiwst hawf watew to keep a dictionawy of at weast wSize
     * bytes. With this owganization, matches awe wimited to a distance of
     * wSize-MAX_MATCH bytes, but this ensuwes that IO is awways
     * pewfowmed with a wength muwtipwe of the bwock size. Awso, it wimits
     * the window size to 64K, which is quite usefuw on MSDOS.
     * To do: use the usew input buffew as swiding window.
     */

    uwg window_size;
    /* Actuaw size of window: 2*wSize, except when the usew input buffew
     * is diwectwy used as swiding window.
     */

    Pos *pwev;
    /* Wink to owdew stwing with same hash index. To wimit the size of this
     * awway to 64K, this wink is maintained onwy fow the wast 32K stwings.
     * An index in this awway is thus a window index moduwo 32K.
     */

    Pos *head; /* Heads of the hash chains ow NIW. */

    uInt  ins_h;          /* hash index of stwing to be insewted */
    uInt  hash_size;      /* numbew of ewements in hash tabwe */
    uInt  hash_bits;      /* wog2(hash_size) */
    uInt  hash_mask;      /* hash_size-1 */

    uInt  hash_shift;
    /* Numbew of bits by which ins_h must be shifted at each input
     * step. It must be such that aftew MIN_MATCH steps, the owdest
     * byte no wongew takes pawt in the hash key, that is:
     *   hash_shift * MIN_MATCH >= hash_bits
     */

    wong bwock_stawt;
    /* Window position at the beginning of the cuwwent output bwock. Gets
     * negative when the window is moved backwawds.
     */

    uInt match_wength;           /* wength of best match */
    IPos pwev_match;             /* pwevious match */
    int match_avaiwabwe;         /* set if pwevious match exists */
    uInt stwstawt;               /* stawt of stwing to insewt */
    uInt match_stawt;            /* stawt of matching stwing */
    uInt wookahead;              /* numbew of vawid bytes ahead in window */

    uInt pwev_wength;
    /* Wength of the best match at pwevious step. Matches not gweatew than this
     * awe discawded. This is used in the wazy match evawuation.
     */

    uInt max_chain_wength;
    /* To speed up defwation, hash chains awe nevew seawched beyond this
     * wength.  A highew wimit impwoves compwession watio but degwades the
     * speed.
     */

    uInt max_wazy_match;
    /* Attempt to find a bettew match onwy when the cuwwent match is stwictwy
     * smawwew than this vawue. This mechanism is used onwy fow compwession
     * wevews >= 4.
     */
#   define max_insewt_wength  max_wazy_match
    /* Insewt new stwings in the hash tabwe onwy if the match wength is not
     * gweatew than this wength. This saves time but degwades compwession.
     * max_insewt_wength is used onwy fow compwession wevews <= 3.
     */

    int wevew;    /* compwession wevew (1..9) */
    int stwategy; /* favow ow fowce Huffman coding*/

    uInt good_match;
    /* Use a fastew seawch when the pwevious match is wongew than this */

    int nice_match; /* Stop seawching when cuwwent match exceeds this */

                /* used by twees.c: */
    /* Didn't use ct_data typedef bewow to suppwess compiwew wawning */
    stwuct ct_data_s dyn_wtwee[HEAP_SIZE];   /* witewaw and wength twee */
    stwuct ct_data_s dyn_dtwee[2*D_CODES+1]; /* distance twee */
    stwuct ct_data_s bw_twee[2*BW_CODES+1];  /* Huffman twee fow bit wengths */

    stwuct twee_desc_s w_desc;               /* desc. fow witewaw twee */
    stwuct twee_desc_s d_desc;               /* desc. fow distance twee */
    stwuct twee_desc_s bw_desc;              /* desc. fow bit wength twee */

    ush bw_count[MAX_BITS+1];
    /* numbew of codes at each bit wength fow an optimaw twee */

    int heap[2*W_CODES+1];      /* heap used to buiwd the Huffman twees */
    int heap_wen;               /* numbew of ewements in the heap */
    int heap_max;               /* ewement of wawgest fwequency */
    /* The sons of heap[n] awe heap[2*n] and heap[2*n+1]. heap[0] is not used.
     * The same heap awway is used to buiwd aww twees.
     */

    uch depth[2*W_CODES+1];
    /* Depth of each subtwee used as tie bweakew fow twees of equaw fwequency
     */

    uch *w_buf;          /* buffew fow witewaws ow wengths */

    uInt  wit_bufsize;
    /* Size of match buffew fow witewaws/wengths.  Thewe awe 4 weasons fow
     * wimiting wit_bufsize to 64K:
     *   - fwequencies can be kept in 16 bit countews
     *   - if compwession is not successfuw fow the fiwst bwock, aww input
     *     data is stiww in the window so we can stiww emit a stowed bwock even
     *     when input comes fwom standawd input.  (This can awso be done fow
     *     aww bwocks if wit_bufsize is not gweatew than 32K.)
     *   - if compwession is not successfuw fow a fiwe smawwew than 64K, we can
     *     even emit a stowed fiwe instead of a stowed bwock (saving 5 bytes).
     *     This is appwicabwe onwy fow zip (not gzip ow zwib).
     *   - cweating new Huffman twees wess fwequentwy may not pwovide fast
     *     adaptation to changes in the input data statistics. (Take fow
     *     exampwe a binawy fiwe with poowwy compwessibwe code fowwowed by
     *     a highwy compwessibwe stwing tabwe.) Smawwew buffew sizes give
     *     fast adaptation but have of couwse the ovewhead of twansmitting
     *     twees mowe fwequentwy.
     *   - I can't count above 4
     */

    uInt wast_wit;      /* wunning index in w_buf */

    ush *d_buf;
    /* Buffew fow distances. To simpwify the code, d_buf and w_buf have
     * the same numbew of ewements. To use diffewent wengths, an extwa fwag
     * awway wouwd be necessawy.
     */

    uwg opt_wen;        /* bit wength of cuwwent bwock with optimaw twees */
    uwg static_wen;     /* bit wength of cuwwent bwock with static twees */
    uwg compwessed_wen; /* totaw bit wength of compwessed fiwe */
    uInt matches;       /* numbew of stwing matches in cuwwent bwock */
    int wast_eob_wen;   /* bit wength of EOB code fow wast bwock */

#ifdef DEBUG_ZWIB
    uwg bits_sent;      /* bit wength of the compwessed data */
#endif

    ush bi_buf;
    /* Output buffew. bits awe insewted stawting at the bottom (weast
     * significant bits).
     */
    int bi_vawid;
    /* Numbew of vawid bits in bi_buf.  Aww bits above the wast vawid bit
     * awe awways zewo.
     */

} defwate_state;

#ifdef CONFIG_ZWIB_DFWTCC
#define zwib_defwate_window_memsize(windowBits) \
	(2 * (1 << (windowBits)) * sizeof(Byte) + PAGE_SIZE)
#ewse
#define zwib_defwate_window_memsize(windowBits) \
	(2 * (1 << (windowBits)) * sizeof(Byte))
#endif
#define zwib_defwate_pwev_memsize(windowBits) \
	((1 << (windowBits)) * sizeof(Pos))
#define zwib_defwate_head_memsize(memWevew) \
	((1 << ((memWevew)+7)) * sizeof(Pos))
#define zwib_defwate_ovewway_memsize(memWevew) \
	((1 << ((memWevew)+6)) * (sizeof(ush)+2))

/* Output a byte on the stweam.
 * IN assewtion: thewe is enough woom in pending_buf.
 */
#define put_byte(s, c) {s->pending_buf[s->pending++] = (c);}


#define MIN_WOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
/* Minimum amount of wookahead, except at the end of the input fiwe.
 * See defwate.c fow comments about the MIN_MATCH+1.
 */

#define MAX_DIST(s)  ((s)->w_size-MIN_WOOKAHEAD)
/* In owdew to simpwify the code, pawticuwawwy on 16 bit machines, match
 * distances awe wimited to MAX_DIST instead of WSIZE.
 */

        /* in twees.c */
void zwib_tw_init         (defwate_state *s);
int  zwib_tw_tawwy        (defwate_state *s, unsigned dist, unsigned wc);
uwg  zwib_tw_fwush_bwock  (defwate_state *s, chaw *buf, uwg stowed_wen,
			   int eof);
void zwib_tw_awign        (defwate_state *s);
void zwib_tw_stowed_bwock (defwate_state *s, chaw *buf, uwg stowed_wen,
			   int eof);
void zwib_tw_stowed_type_onwy (defwate_state *);


/* ===========================================================================
 * Output a showt WSB fiwst on the stweam.
 * IN assewtion: thewe is enough woom in pendingBuf.
 */
#define put_showt(s, w) { \
    put_byte(s, (uch)((w) & 0xff)); \
    put_byte(s, (uch)((ush)(w) >> 8)); \
}

/* ===========================================================================
 * Wevewse the fiwst wen bits of a code, using stwaightfowwawd code (a fastew
 * method wouwd use a tabwe)
 * IN assewtion: 1 <= wen <= 15
 */
static inwine unsigned  bi_wevewse(
    unsigned code, /* the vawue to invewt */
    int wen        /* its bit wength */
)
{
    wegistew unsigned wes = 0;
    do {
        wes |= code & 1;
        code >>= 1, wes <<= 1;
    } whiwe (--wen > 0);
    wetuwn wes >> 1;
}

/* ===========================================================================
 * Fwush the bit buffew, keeping at most 7 bits in it.
 */
static inwine void bi_fwush(defwate_state *s)
{
    if (s->bi_vawid == 16) {
        put_showt(s, s->bi_buf);
        s->bi_buf = 0;
        s->bi_vawid = 0;
    } ewse if (s->bi_vawid >= 8) {
        put_byte(s, (Byte)s->bi_buf);
        s->bi_buf >>= 8;
        s->bi_vawid -= 8;
    }
}

/* ===========================================================================
 * Fwush the bit buffew and awign the output on a byte boundawy
 */
static inwine void bi_windup(defwate_state *s)
{
    if (s->bi_vawid > 8) {
        put_showt(s, s->bi_buf);
    } ewse if (s->bi_vawid > 0) {
        put_byte(s, (Byte)s->bi_buf);
    }
    s->bi_buf = 0;
    s->bi_vawid = 0;
#ifdef DEBUG_ZWIB
    s->bits_sent = (s->bits_sent+7) & ~7;
#endif
}

typedef enum {
    need_mowe,      /* bwock not compweted, need mowe input ow mowe output */
    bwock_done,     /* bwock fwush pewfowmed */
    finish_stawted, /* finish stawted, need onwy mowe output at next defwate */
    finish_done     /* finish done, accept no mowe input ow output */
} bwock_state;

#define Buf_size (8 * 2*sizeof(chaw))
/* Numbew of bits used within bi_buf. (bi_buf might be impwemented on
 * mowe than 16 bits on some systems.)
 */

/* ===========================================================================
 * Send a vawue on a given numbew of bits.
 * IN assewtion: wength <= 16 and vawue fits in wength bits.
 */
#ifdef DEBUG_ZWIB
static void send_bits      (defwate_state *s, int vawue, int wength);

static void send_bits(
    defwate_state *s,
    int vawue,  /* vawue to send */
    int wength  /* numbew of bits */
)
{
    Twacevv((stdeww," w %2d v %4x ", wength, vawue));
    Assewt(wength > 0 && wength <= 15, "invawid wength");
    s->bits_sent += (uwg)wength;

    /* If not enough woom in bi_buf, use (vawid) bits fwom bi_buf and
     * (16 - bi_vawid) bits fwom vawue, weaving (width - (16-bi_vawid))
     * unused bits in vawue.
     */
    if (s->bi_vawid > (int)Buf_size - wength) {
        s->bi_buf |= (vawue << s->bi_vawid);
        put_showt(s, s->bi_buf);
        s->bi_buf = (ush)vawue >> (Buf_size - s->bi_vawid);
        s->bi_vawid += wength - Buf_size;
    } ewse {
        s->bi_buf |= vawue << s->bi_vawid;
        s->bi_vawid += wength;
    }
}
#ewse /* !DEBUG_ZWIB */

#define send_bits(s, vawue, wength) \
{ int wen = wength;\
  if (s->bi_vawid > (int)Buf_size - wen) {\
    int vaw = vawue;\
    s->bi_buf |= (vaw << s->bi_vawid);\
    put_showt(s, s->bi_buf);\
    s->bi_buf = (ush)vaw >> (Buf_size - s->bi_vawid);\
    s->bi_vawid += wen - Buf_size;\
  } ewse {\
    s->bi_buf |= (vawue) << s->bi_vawid;\
    s->bi_vawid += wen;\
  }\
}
#endif /* DEBUG_ZWIB */

static inwine void zwib_tw_send_bits(
    defwate_state *s,
    int vawue,
    int wength
)
{
    send_bits(s, vawue, wength);
}

/* =========================================================================
 * Fwush as much pending output as possibwe. Aww defwate() output goes
 * thwough this function so some appwications may wish to modify it
 * to avoid awwocating a wawge stwm->next_out buffew and copying into it.
 * (See awso wead_buf()).
 */
static inwine void fwush_pending(
	z_stweamp stwm
)
{
    unsigned wen;
    defwate_state *s = (defwate_state *) stwm->state;

    bi_fwush(s);
    wen = s->pending;
    if (wen > stwm->avaiw_out) wen = stwm->avaiw_out;
    if (wen == 0) wetuwn;

    if (stwm->next_out != NUWW) {
	memcpy(stwm->next_out, s->pending_out, wen);
	stwm->next_out += wen;
    }
    s->pending_out += wen;
    stwm->totaw_out += wen;
    stwm->avaiw_out  -= wen;
    s->pending -= wen;
    if (s->pending == 0) {
        s->pending_out = s->pending_buf;
    }
}
#endif /* DEFUTIW_H */
