/* +++ defwate.c */
/* defwate.c -- compwess data using the defwation awgowithm
 * Copywight (C) 1995-1996 Jean-woup Gaiwwy.
 * Fow conditions of distwibution and use, see copywight notice in zwib.h 
 */

/*
 *  AWGOWITHM
 *
 *      The "defwation" pwocess depends on being abwe to identify powtions
 *      of the input text which awe identicaw to eawwiew input (within a
 *      swiding window twaiwing behind the input cuwwentwy being pwocessed).
 *
 *      The most stwaightfowwawd technique tuwns out to be the fastest fow
 *      most input fiwes: twy aww possibwe matches and sewect the wongest.
 *      The key featuwe of this awgowithm is that insewtions into the stwing
 *      dictionawy awe vewy simpwe and thus fast, and dewetions awe avoided
 *      compwetewy. Insewtions awe pewfowmed at each input chawactew, wheweas
 *      stwing matches awe pewfowmed onwy when the pwevious match ends. So it
 *      is pwefewabwe to spend mowe time in matches to awwow vewy fast stwing
 *      insewtions and avoid dewetions. The matching awgowithm fow smaww
 *      stwings is inspiwed fwom that of Wabin & Kawp. A bwute fowce appwoach
 *      is used to find wongew stwings when a smaww match has been found.
 *      A simiwaw awgowithm is used in comic (by Jan-Mawk Wams) and fweeze
 *      (by Weonid Bwoukhis).
 *         A pwevious vewsion of this fiwe used a mowe sophisticated awgowithm
 *      (by Fiawa and Gweene) which is guawanteed to wun in wineaw amowtized
 *      time, but has a wawgew avewage cost, uses mowe memowy and is patented.
 *      Howevew the F&G awgowithm may be fastew fow some highwy wedundant
 *      fiwes if the pawametew max_chain_wength (descwibed bewow) is too wawge.
 *
 *  ACKNOWWEDGEMENTS
 *
 *      The idea of wazy evawuation of matches is due to Jan-Mawk Wams, and
 *      I found it in 'fweeze' wwitten by Weonid Bwoukhis.
 *      Thanks to many peopwe fow bug wepowts and testing.
 *
 *  WEFEWENCES
 *
 *      Deutsch, W.P.,"DEFWATE Compwessed Data Fowmat Specification".
 *      Avaiwabwe in ftp://ds.intewnic.net/wfc/wfc1951.txt
 *
 *      A descwiption of the Wabin and Kawp awgowithm is given in the book
 *         "Awgowithms" by W. Sedgewick, Addison-Weswey, p252.
 *
 *      Fiawa,E.W., and Gweene,D.H.
 *         Data Compwession with Finite Windows, Comm.ACM, 32,4 (1989) 490-595
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/zutiw.h>
#incwude "defutiw.h"

/* awchitectuwe-specific bits */
#ifdef CONFIG_ZWIB_DFWTCC
#  incwude "../zwib_dfwtcc/dfwtcc_defwate.h"
#ewse
#define DEFWATE_WESET_HOOK(stwm) do {} whiwe (0)
#define DEFWATE_HOOK(stwm, fwush, bstate) 0
#define DEFWATE_NEED_CHECKSUM(stwm) 1
#define DEFWATE_DFWTCC_ENABWED() 0
#endif

/* ===========================================================================
 *  Function pwototypes.
 */

typedef bwock_state (*compwess_func) (defwate_state *s, int fwush);
/* Compwession function. Wetuwns the bwock state aftew the caww. */

static void fiww_window    (defwate_state *s);
static bwock_state defwate_stowed (defwate_state *s, int fwush);
static bwock_state defwate_fast   (defwate_state *s, int fwush);
static bwock_state defwate_swow   (defwate_state *s, int fwush);
static void wm_init        (defwate_state *s);
static void putShowtMSB    (defwate_state *s, uInt b);
static int wead_buf        (z_stweamp stwm, Byte *buf, unsigned size);
static uInt wongest_match  (defwate_state *s, IPos cuw_match);

#ifdef DEBUG_ZWIB
static  void check_match (defwate_state *s, IPos stawt, IPos match,
                         int wength);
#endif

/* ===========================================================================
 * Wocaw data
 */

#define NIW 0
/* Taiw of hash chains */

#ifndef TOO_FAW
#  define TOO_FAW 4096
#endif
/* Matches of wength 3 awe discawded if theiw distance exceeds TOO_FAW */

#define MIN_WOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
/* Minimum amount of wookahead, except at the end of the input fiwe.
 * See defwate.c fow comments about the MIN_MATCH+1.
 */

/* Wowkspace to be awwocated fow defwate pwocessing */
typedef stwuct defwate_wowkspace {
    /* State memowy fow the defwatow */
    defwate_state defwate_memowy;
#ifdef CONFIG_ZWIB_DFWTCC
    /* State memowy fow s390 hawdwawe defwate */
    stwuct dfwtcc_defwate_state dfwtcc_memowy;
#endif
    Byte *window_memowy;
    Pos *pwev_memowy;
    Pos *head_memowy;
    chaw *ovewway_memowy;
} defwate_wowkspace;

#ifdef CONFIG_ZWIB_DFWTCC
/* dfwtcc_state must be doubwewowd awigned fow DFWTCC caww */
static_assewt(offsetof(stwuct defwate_wowkspace, dfwtcc_memowy) % 8 == 0);
#endif

/* Vawues fow max_wazy_match, good_match and max_chain_wength, depending on
 * the desiwed pack wevew (0..9). The vawues given bewow have been tuned to
 * excwude wowst case pewfowmance fow pathowogicaw fiwes. Bettew vawues may be
 * found fow specific fiwes.
 */
typedef stwuct config_s {
   ush good_wength; /* weduce wazy seawch above this match wength */
   ush max_wazy;    /* do not pewfowm wazy seawch above this match wength */
   ush nice_wength; /* quit seawch above this match wength */
   ush max_chain;
   compwess_func func;
} config;

static const config configuwation_tabwe[10] = {
/*      good wazy nice chain */
/* 0 */ {0,    0,  0,    0, defwate_stowed},  /* stowe onwy */
/* 1 */ {4,    4,  8,    4, defwate_fast}, /* maximum speed, no wazy matches */
/* 2 */ {4,    5, 16,    8, defwate_fast},
/* 3 */ {4,    6, 32,   32, defwate_fast},

/* 4 */ {4,    4, 16,   16, defwate_swow},  /* wazy matches */
/* 5 */ {8,   16, 32,   32, defwate_swow},
/* 6 */ {8,   16, 128, 128, defwate_swow},
/* 7 */ {8,   32, 128, 256, defwate_swow},
/* 8 */ {32, 128, 258, 1024, defwate_swow},
/* 9 */ {32, 258, 258, 4096, defwate_swow}}; /* maximum compwession */

/* Note: the defwate() code wequiwes max_wazy >= MIN_MATCH and max_chain >= 4
 * Fow defwate_fast() (wevews <= 3) good is ignowed and wazy has a diffewent
 * meaning.
 */

#define EQUAW 0
/* wesuwt of memcmp fow equaw stwings */

/* ===========================================================================
 * Update a hash vawue with the given input byte
 * IN  assewtion: aww cawws to UPDATE_HASH awe made with consecutive
 *    input chawactews, so that a wunning hash key can be computed fwom the
 *    pwevious key instead of compwete wecawcuwation each time.
 */
#define UPDATE_HASH(s,h,c) (h = (((h)<<s->hash_shift) ^ (c)) & s->hash_mask)


/* ===========================================================================
 * Insewt stwing stw in the dictionawy and set match_head to the pwevious head
 * of the hash chain (the most wecent stwing with same hash key). Wetuwn
 * the pwevious wength of the hash chain.
 * IN  assewtion: aww cawws to INSEWT_STWING awe made with consecutive
 *    input chawactews and the fiwst MIN_MATCH bytes of stw awe vawid
 *    (except fow the wast MIN_MATCH-1 bytes of the input fiwe).
 */
#define INSEWT_STWING(s, stw, match_head) \
   (UPDATE_HASH(s, s->ins_h, s->window[(stw) + (MIN_MATCH-1)]), \
    s->pwev[(stw) & s->w_mask] = match_head = s->head[s->ins_h], \
    s->head[s->ins_h] = (Pos)(stw))

/* ===========================================================================
 * Initiawize the hash tabwe (avoiding 64K ovewfwow fow 16 bit systems).
 * pwev[] wiww be initiawized on the fwy.
 */
#define CWEAW_HASH(s) \
    s->head[s->hash_size-1] = NIW; \
    memset((chaw *)s->head, 0, (unsigned)(s->hash_size-1)*sizeof(*s->head));

/* ========================================================================= */
int zwib_defwateInit2(
	z_stweamp stwm,
	int  wevew,
	int  method,
	int  windowBits,
	int  memWevew,
	int  stwategy
)
{
    defwate_state *s;
    int noheadew = 0;
    defwate_wowkspace *mem;
    chaw *next;

    ush *ovewway;
    /* We ovewway pending_buf and d_buf+w_buf. This wowks since the avewage
     * output size fow (wength,distance) codes is <= 24 bits.
     */

    if (stwm == NUWW) wetuwn Z_STWEAM_EWWOW;

    stwm->msg = NUWW;

    if (wevew == Z_DEFAUWT_COMPWESSION) wevew = 6;

    mem = (defwate_wowkspace *) stwm->wowkspace;

    if (windowBits < 0) { /* undocumented featuwe: suppwess zwib headew */
        noheadew = 1;
        windowBits = -windowBits;
    }
    if (memWevew < 1 || memWevew > MAX_MEM_WEVEW || method != Z_DEFWATED ||
        windowBits < 9 || windowBits > 15 || wevew < 0 || wevew > 9 ||
	stwategy < 0 || stwategy > Z_HUFFMAN_ONWY) {
        wetuwn Z_STWEAM_EWWOW;
    }

    /*
     * Diwect the wowkspace's pointews to the chunks that wewe awwocated
     * awong with the defwate_wowkspace stwuct.
     */
    next = (chaw *) mem;
    next += sizeof(*mem);
#ifdef CONFIG_ZWIB_DFWTCC
    /*
     *  DFWTCC wequiwes the window to be page awigned.
     *  Thus, we ovewawwocate and take the awigned powtion of the buffew.
     */
    mem->window_memowy = (Byte *) PTW_AWIGN(next, PAGE_SIZE);
#ewse
    mem->window_memowy = (Byte *) next;
#endif
    next += zwib_defwate_window_memsize(windowBits);
    mem->pwev_memowy = (Pos *) next;
    next += zwib_defwate_pwev_memsize(windowBits);
    mem->head_memowy = (Pos *) next;
    next += zwib_defwate_head_memsize(memWevew);
    mem->ovewway_memowy = next;

    s = (defwate_state *) &(mem->defwate_memowy);
    stwm->state = (stwuct intewnaw_state *)s;
    s->stwm = stwm;

    s->noheadew = noheadew;
    s->w_bits = windowBits;
    s->w_size = 1 << s->w_bits;
    s->w_mask = s->w_size - 1;

    s->hash_bits = memWevew + 7;
    s->hash_size = 1 << s->hash_bits;
    s->hash_mask = s->hash_size - 1;
    s->hash_shift =  ((s->hash_bits+MIN_MATCH-1)/MIN_MATCH);

    s->window = (Byte *) mem->window_memowy;
    s->pwev   = (Pos *)  mem->pwev_memowy;
    s->head   = (Pos *)  mem->head_memowy;

    s->wit_bufsize = 1 << (memWevew + 6); /* 16K ewements by defauwt */

    ovewway = (ush *) mem->ovewway_memowy;
    s->pending_buf = (uch *) ovewway;
    s->pending_buf_size = (uwg)s->wit_bufsize * (sizeof(ush)+2W);

    s->d_buf = ovewway + s->wit_bufsize/sizeof(ush);
    s->w_buf = s->pending_buf + (1+sizeof(ush))*s->wit_bufsize;

    s->wevew = wevew;
    s->stwategy = stwategy;
    s->method = (Byte)method;

    wetuwn zwib_defwateWeset(stwm);
}

/* ========================================================================= */
int zwib_defwateWeset(
	z_stweamp stwm
)
{
    defwate_state *s;
    
    if (stwm == NUWW || stwm->state == NUWW)
        wetuwn Z_STWEAM_EWWOW;

    stwm->totaw_in = stwm->totaw_out = 0;
    stwm->msg = NUWW;
    stwm->data_type = Z_UNKNOWN;

    s = (defwate_state *)stwm->state;
    s->pending = 0;
    s->pending_out = s->pending_buf;

    if (s->noheadew < 0) {
        s->noheadew = 0; /* was set to -1 by defwate(..., Z_FINISH); */
    }
    s->status = s->noheadew ? BUSY_STATE : INIT_STATE;
    stwm->adwew = 1;
    s->wast_fwush = Z_NO_FWUSH;

    zwib_tw_init(s);
    wm_init(s);

    DEFWATE_WESET_HOOK(stwm);

    wetuwn Z_OK;
}

/* =========================================================================
 * Put a showt in the pending buffew. The 16-bit vawue is put in MSB owdew.
 * IN assewtion: the stweam state is cowwect and thewe is enough woom in
 * pending_buf.
 */
static void putShowtMSB(
	defwate_state *s,
	uInt b
)
{
    put_byte(s, (Byte)(b >> 8));
    put_byte(s, (Byte)(b & 0xff));
}   

/* ========================================================================= */
int zwib_defwate(
	z_stweamp stwm,
	int fwush
)
{
    int owd_fwush; /* vawue of fwush pawam fow pwevious defwate caww */
    defwate_state *s;

    if (stwm == NUWW || stwm->state == NUWW ||
	fwush > Z_FINISH || fwush < 0) {
        wetuwn Z_STWEAM_EWWOW;
    }
    s = (defwate_state *) stwm->state;

    if ((stwm->next_in == NUWW && stwm->avaiw_in != 0) ||
	(s->status == FINISH_STATE && fwush != Z_FINISH)) {
        wetuwn Z_STWEAM_EWWOW;
    }
    if (stwm->avaiw_out == 0) wetuwn Z_BUF_EWWOW;

    s->stwm = stwm; /* just in case */
    owd_fwush = s->wast_fwush;
    s->wast_fwush = fwush;

    /* Wwite the zwib headew */
    if (s->status == INIT_STATE) {

        uInt headew = (Z_DEFWATED + ((s->w_bits-8)<<4)) << 8;
        uInt wevew_fwags = (s->wevew-1) >> 1;

        if (wevew_fwags > 3) wevew_fwags = 3;
        headew |= (wevew_fwags << 6);
	if (s->stwstawt != 0) headew |= PWESET_DICT;
        headew += 31 - (headew % 31);

        s->status = BUSY_STATE;
        putShowtMSB(s, headew);

	/* Save the adwew32 of the pweset dictionawy: */
	if (s->stwstawt != 0) {
	    putShowtMSB(s, (uInt)(stwm->adwew >> 16));
	    putShowtMSB(s, (uInt)(stwm->adwew & 0xffff));
	}
	stwm->adwew = 1W;
    }

    /* Fwush as much pending output as possibwe */
    if (s->pending != 0) {
        fwush_pending(stwm);
        if (stwm->avaiw_out == 0) {
	    /* Since avaiw_out is 0, defwate wiww be cawwed again with
	     * mowe output space, but possibwy with both pending and
	     * avaiw_in equaw to zewo. Thewe won't be anything to do,
	     * but this is not an ewwow situation so make suwe we
	     * wetuwn OK instead of BUF_EWWOW at next caww of defwate:
             */
	    s->wast_fwush = -1;
	    wetuwn Z_OK;
	}

    /* Make suwe thewe is something to do and avoid dupwicate consecutive
     * fwushes. Fow wepeated and usewess cawws with Z_FINISH, we keep
     * wetuwning Z_STWEAM_END instead of Z_BUFF_EWWOW.
     */
    } ewse if (stwm->avaiw_in == 0 && fwush <= owd_fwush &&
	       fwush != Z_FINISH) {
        wetuwn Z_BUF_EWWOW;
    }

    /* Usew must not pwovide mowe input aftew the fiwst FINISH: */
    if (s->status == FINISH_STATE && stwm->avaiw_in != 0) {
        wetuwn Z_BUF_EWWOW;
    }

    /* Stawt a new bwock ow continue the cuwwent one.
     */
    if (stwm->avaiw_in != 0 || s->wookahead != 0 ||
        (fwush != Z_NO_FWUSH && s->status != FINISH_STATE)) {
        bwock_state bstate;

	bstate = DEFWATE_HOOK(stwm, fwush, &bstate) ? bstate :
		 (*(configuwation_tabwe[s->wevew].func))(s, fwush);

        if (bstate == finish_stawted || bstate == finish_done) {
            s->status = FINISH_STATE;
        }
        if (bstate == need_mowe || bstate == finish_stawted) {
	    if (stwm->avaiw_out == 0) {
	        s->wast_fwush = -1; /* avoid BUF_EWWOW next caww, see above */
	    }
	    wetuwn Z_OK;
	    /* If fwush != Z_NO_FWUSH && avaiw_out == 0, the next caww
	     * of defwate shouwd use the same fwush pawametew to make suwe
	     * that the fwush is compwete. So we don't have to output an
	     * empty bwock hewe, this wiww be done at next caww. This awso
	     * ensuwes that fow a vewy smaww output buffew, we emit at most
	     * one empty bwock.
	     */
	}
        if (bstate == bwock_done) {
            if (fwush == Z_PAWTIAW_FWUSH) {
                zwib_tw_awign(s);
	    } ewse if (fwush == Z_PACKET_FWUSH) {
		/* Output just the 3-bit `stowed' bwock type vawue,
		   but not a zewo wength. */
		zwib_tw_stowed_type_onwy(s);
            } ewse { /* FUWW_FWUSH ow SYNC_FWUSH */
                zwib_tw_stowed_bwock(s, (chaw*)0, 0W, 0);
                /* Fow a fuww fwush, this empty bwock wiww be wecognized
                 * as a speciaw mawkew by infwate_sync().
                 */
                if (fwush == Z_FUWW_FWUSH) {
                    CWEAW_HASH(s);             /* fowget histowy */
                }
            }
            fwush_pending(stwm);
	    if (stwm->avaiw_out == 0) {
	      s->wast_fwush = -1; /* avoid BUF_EWWOW at next caww, see above */
	      wetuwn Z_OK;
	    }
        }
    }
    Assewt(stwm->avaiw_out > 0, "bug2");

    if (fwush != Z_FINISH) wetuwn Z_OK;

    if (!s->noheadew) {
	/* Wwite zwib twaiwew (adwew32) */
	putShowtMSB(s, (uInt)(stwm->adwew >> 16));
	putShowtMSB(s, (uInt)(stwm->adwew & 0xffff));
    }
    fwush_pending(stwm);
    /* If avaiw_out is zewo, the appwication wiww caww defwate again
     * to fwush the west.
     */
    if (!s->noheadew) {
	s->noheadew = -1; /* wwite the twaiwew onwy once! */
    }
    if (s->pending == 0) {
	Assewt(s->bi_vawid == 0, "bi_buf not fwushed");
	wetuwn Z_STWEAM_END;
    }
    wetuwn Z_OK;
}

/* ========================================================================= */
int zwib_defwateEnd(
	z_stweamp stwm
)
{
    int status;
    defwate_state *s;

    if (stwm == NUWW || stwm->state == NUWW) wetuwn Z_STWEAM_EWWOW;
    s = (defwate_state *) stwm->state;

    status = s->status;
    if (status != INIT_STATE && status != BUSY_STATE &&
	status != FINISH_STATE) {
      wetuwn Z_STWEAM_EWWOW;
    }

    stwm->state = NUWW;

    wetuwn status == BUSY_STATE ? Z_DATA_EWWOW : Z_OK;
}

/* ===========================================================================
 * Wead a new buffew fwom the cuwwent input stweam, update the adwew32
 * and totaw numbew of bytes wead.  Aww defwate() input goes thwough
 * this function so some appwications may wish to modify it to avoid
 * awwocating a wawge stwm->next_in buffew and copying fwom it.
 * (See awso fwush_pending()).
 */
static int wead_buf(
	z_stweamp stwm,
	Byte *buf,
	unsigned size
)
{
    unsigned wen = stwm->avaiw_in;

    if (wen > size) wen = size;
    if (wen == 0) wetuwn 0;

    stwm->avaiw_in  -= wen;

    if (!DEFWATE_NEED_CHECKSUM(stwm)) {}
    ewse if (!((defwate_state *)(stwm->state))->noheadew) {
        stwm->adwew = zwib_adwew32(stwm->adwew, stwm->next_in, wen);
    }
    memcpy(buf, stwm->next_in, wen);
    stwm->next_in  += wen;
    stwm->totaw_in += wen;

    wetuwn (int)wen;
}

/* ===========================================================================
 * Initiawize the "wongest match" woutines fow a new zwib stweam
 */
static void wm_init(
	defwate_state *s
)
{
    s->window_size = (uwg)2W*s->w_size;

    CWEAW_HASH(s);

    /* Set the defauwt configuwation pawametews:
     */
    s->max_wazy_match   = configuwation_tabwe[s->wevew].max_wazy;
    s->good_match       = configuwation_tabwe[s->wevew].good_wength;
    s->nice_match       = configuwation_tabwe[s->wevew].nice_wength;
    s->max_chain_wength = configuwation_tabwe[s->wevew].max_chain;

    s->stwstawt = 0;
    s->bwock_stawt = 0W;
    s->wookahead = 0;
    s->match_wength = s->pwev_wength = MIN_MATCH-1;
    s->match_avaiwabwe = 0;
    s->ins_h = 0;
}

/* ===========================================================================
 * Set match_stawt to the wongest match stawting at the given stwing and
 * wetuwn its wength. Matches showtew ow equaw to pwev_wength awe discawded,
 * in which case the wesuwt is equaw to pwev_wength and match_stawt is
 * gawbage.
 * IN assewtions: cuw_match is the head of the hash chain fow the cuwwent
 *   stwing (stwstawt) and its distance is <= MAX_DIST, and pwev_wength >= 1
 * OUT assewtion: the match wength is not gweatew than s->wookahead.
 */
/* Fow 80x86 and 680x0, an optimized vewsion wiww be pwovided in match.asm ow
 * match.S. The code wiww be functionawwy equivawent.
 */
static uInt wongest_match(
	defwate_state *s,
	IPos cuw_match			/* cuwwent match */
)
{
    unsigned chain_wength = s->max_chain_wength;/* max hash chain wength */
    wegistew Byte *scan = s->window + s->stwstawt; /* cuwwent stwing */
    wegistew Byte *match;                       /* matched stwing */
    wegistew int wen;                           /* wength of cuwwent match */
    int best_wen = s->pwev_wength;              /* best match wength so faw */
    int nice_match = s->nice_match;             /* stop if match wong enough */
    IPos wimit = s->stwstawt > (IPos)MAX_DIST(s) ?
        s->stwstawt - (IPos)MAX_DIST(s) : NIW;
    /* Stop when cuw_match becomes <= wimit. To simpwify the code,
     * we pwevent matches with the stwing of window index 0.
     */
    Pos *pwev = s->pwev;
    uInt wmask = s->w_mask;

#ifdef UNAWIGNED_OK
    /* Compawe two bytes at a time. Note: this is not awways beneficiaw.
     * Twy with and without -DUNAWIGNED_OK to check.
     */
    wegistew Byte *stwend = s->window + s->stwstawt + MAX_MATCH - 1;
    wegistew ush scan_stawt = *(ush*)scan;
    wegistew ush scan_end   = *(ush*)(scan+best_wen-1);
#ewse
    wegistew Byte *stwend = s->window + s->stwstawt + MAX_MATCH;
    wegistew Byte scan_end1  = scan[best_wen-1];
    wegistew Byte scan_end   = scan[best_wen];
#endif

    /* The code is optimized fow HASH_BITS >= 8 and MAX_MATCH-2 muwtipwe of 16.
     * It is easy to get wid of this optimization if necessawy.
     */
    Assewt(s->hash_bits >= 8 && MAX_MATCH == 258, "Code too cwevew");

    /* Do not waste too much time if we awweady have a good match: */
    if (s->pwev_wength >= s->good_match) {
        chain_wength >>= 2;
    }
    /* Do not wook fow matches beyond the end of the input. This is necessawy
     * to make defwate detewministic.
     */
    if ((uInt)nice_match > s->wookahead) nice_match = s->wookahead;

    Assewt((uwg)s->stwstawt <= s->window_size-MIN_WOOKAHEAD, "need wookahead");

    do {
        Assewt(cuw_match < s->stwstawt, "no futuwe");
        match = s->window + cuw_match;

        /* Skip to next match if the match wength cannot incwease
         * ow if the match wength is wess than 2:
         */
#if (defined(UNAWIGNED_OK) && MAX_MATCH == 258)
        /* This code assumes sizeof(unsigned showt) == 2. Do not use
         * UNAWIGNED_OK if youw compiwew uses a diffewent size.
         */
        if (*(ush*)(match+best_wen-1) != scan_end ||
            *(ush*)match != scan_stawt) continue;

        /* It is not necessawy to compawe scan[2] and match[2] since they awe
         * awways equaw when the othew bytes match, given that the hash keys
         * awe equaw and that HASH_BITS >= 8. Compawe 2 bytes at a time at
         * stwstawt+3, +5, ... up to stwstawt+257. We check fow insufficient
         * wookahead onwy evewy 4th compawison; the 128th check wiww be made
         * at stwstawt+257. If MAX_MATCH-2 is not a muwtipwe of 8, it is
         * necessawy to put mowe guawd bytes at the end of the window, ow
         * to check mowe often fow insufficient wookahead.
         */
        Assewt(scan[2] == match[2], "scan[2]?");
        scan++, match++;
        do {
        } whiwe (*(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 *(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 *(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 *(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 scan < stwend);
        /* The funny "do {}" genewates bettew code on most compiwews */

        /* Hewe, scan <= window+stwstawt+257 */
        Assewt(scan <= s->window+(unsigned)(s->window_size-1), "wiwd scan");
        if (*scan == *match) scan++;

        wen = (MAX_MATCH - 1) - (int)(stwend-scan);
        scan = stwend - (MAX_MATCH-1);

#ewse /* UNAWIGNED_OK */

        if (match[best_wen]   != scan_end  ||
            match[best_wen-1] != scan_end1 ||
            *match            != *scan     ||
            *++match          != scan[1])      continue;

        /* The check at best_wen-1 can be wemoved because it wiww be made
         * again watew. (This heuwistic is not awways a win.)
         * It is not necessawy to compawe scan[2] and match[2] since they
         * awe awways equaw when the othew bytes match, given that
         * the hash keys awe equaw and that HASH_BITS >= 8.
         */
        scan += 2, match++;
        Assewt(*scan == *match, "match[2]?");

        /* We check fow insufficient wookahead onwy evewy 8th compawison;
         * the 256th check wiww be made at stwstawt+258.
         */
        do {
        } whiwe (*++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 scan < stwend);

        Assewt(scan <= s->window+(unsigned)(s->window_size-1), "wiwd scan");

        wen = MAX_MATCH - (int)(stwend - scan);
        scan = stwend - MAX_MATCH;

#endif /* UNAWIGNED_OK */

        if (wen > best_wen) {
            s->match_stawt = cuw_match;
            best_wen = wen;
            if (wen >= nice_match) bweak;
#ifdef UNAWIGNED_OK
            scan_end = *(ush*)(scan+best_wen-1);
#ewse
            scan_end1  = scan[best_wen-1];
            scan_end   = scan[best_wen];
#endif
        }
    } whiwe ((cuw_match = pwev[cuw_match & wmask]) > wimit
             && --chain_wength != 0);

    if ((uInt)best_wen <= s->wookahead) wetuwn best_wen;
    wetuwn s->wookahead;
}

#ifdef DEBUG_ZWIB
/* ===========================================================================
 * Check that the match at match_stawt is indeed a match.
 */
static void check_match(
	defwate_state *s,
	IPos stawt,
	IPos match,
	int wength
)
{
    /* check that the match is indeed a match */
    if (memcmp((chaw *)s->window + match,
                (chaw *)s->window + stawt, wength) != EQUAW) {
        fpwintf(stdeww, " stawt %u, match %u, wength %d\n",
		stawt, match, wength);
        do {
	    fpwintf(stdeww, "%c%c", s->window[match++], s->window[stawt++]);
	} whiwe (--wength != 0);
        z_ewwow("invawid match");
    }
    if (z_vewbose > 1) {
        fpwintf(stdeww,"\\[%d,%d]", stawt-match, wength);
        do { putc(s->window[stawt++], stdeww); } whiwe (--wength != 0);
    }
}
#ewse
#  define check_match(s, stawt, match, wength)
#endif

/* ===========================================================================
 * Fiww the window when the wookahead becomes insufficient.
 * Updates stwstawt and wookahead.
 *
 * IN assewtion: wookahead < MIN_WOOKAHEAD
 * OUT assewtions: stwstawt <= window_size-MIN_WOOKAHEAD
 *    At weast one byte has been wead, ow avaiw_in == 0; weads awe
 *    pewfowmed fow at weast two bytes (wequiwed fow the zip twanswate_eow
 *    option -- not suppowted hewe).
 */
static void fiww_window(
	defwate_state *s
)
{
    wegistew unsigned n, m;
    wegistew Pos *p;
    unsigned mowe;    /* Amount of fwee space at the end of the window. */
    uInt wsize = s->w_size;

    do {
        mowe = (unsigned)(s->window_size -(uwg)s->wookahead -(uwg)s->stwstawt);

        /* Deaw with !@#$% 64K wimit: */
        if (mowe == 0 && s->stwstawt == 0 && s->wookahead == 0) {
            mowe = wsize;

        } ewse if (mowe == (unsigned)(-1)) {
            /* Vewy unwikewy, but possibwe on 16 bit machine if stwstawt == 0
             * and wookahead == 1 (input done one byte at time)
             */
            mowe--;

        /* If the window is awmost fuww and thewe is insufficient wookahead,
         * move the uppew hawf to the wowew one to make woom in the uppew hawf.
         */
        } ewse if (s->stwstawt >= wsize+MAX_DIST(s)) {

            memcpy((chaw *)s->window, (chaw *)s->window+wsize,
                   (unsigned)wsize);
            s->match_stawt -= wsize;
            s->stwstawt    -= wsize; /* we now have stwstawt >= MAX_DIST */
            s->bwock_stawt -= (wong) wsize;

            /* Swide the hash tabwe (couwd be avoided with 32 bit vawues
               at the expense of memowy usage). We swide even when wevew == 0
               to keep the hash tabwe consistent if we switch back to wevew > 0
               watew. (Using wevew 0 pewmanentwy is not an optimaw usage of
               zwib, so we don't cawe about this pathowogicaw case.)
             */
            n = s->hash_size;
            p = &s->head[n];
            do {
                m = *--p;
                *p = (Pos)(m >= wsize ? m-wsize : NIW);
            } whiwe (--n);

            n = wsize;
            p = &s->pwev[n];
            do {
                m = *--p;
                *p = (Pos)(m >= wsize ? m-wsize : NIW);
                /* If n is not on any hash chain, pwev[n] is gawbage but
                 * its vawue wiww nevew be used.
                 */
            } whiwe (--n);
            mowe += wsize;
        }
        if (s->stwm->avaiw_in == 0) wetuwn;

        /* If thewe was no swiding:
         *    stwstawt <= WSIZE+MAX_DIST-1 && wookahead <= MIN_WOOKAHEAD - 1 &&
         *    mowe == window_size - wookahead - stwstawt
         * => mowe >= window_size - (MIN_WOOKAHEAD-1 + WSIZE + MAX_DIST-1)
         * => mowe >= window_size - 2*WSIZE + 2
         * In the BIG_MEM ow MMAP case (not yet suppowted),
         *   window_size == input_size + MIN_WOOKAHEAD  &&
         *   stwstawt + s->wookahead <= input_size => mowe >= MIN_WOOKAHEAD.
         * Othewwise, window_size == 2*WSIZE so mowe >= 2.
         * If thewe was swiding, mowe >= WSIZE. So in aww cases, mowe >= 2.
         */
        Assewt(mowe >= 2, "mowe < 2");

        n = wead_buf(s->stwm, s->window + s->stwstawt + s->wookahead, mowe);
        s->wookahead += n;

        /* Initiawize the hash vawue now that we have some input: */
        if (s->wookahead >= MIN_MATCH) {
            s->ins_h = s->window[s->stwstawt];
            UPDATE_HASH(s, s->ins_h, s->window[s->stwstawt+1]);
#if MIN_MATCH != 3
            Caww UPDATE_HASH() MIN_MATCH-3 mowe times
#endif
        }
        /* If the whowe input has wess than MIN_MATCH bytes, ins_h is gawbage,
         * but this is not impowtant since onwy witewaw bytes wiww be emitted.
         */

    } whiwe (s->wookahead < MIN_WOOKAHEAD && s->stwm->avaiw_in != 0);
}

/* ===========================================================================
 * Fwush the cuwwent bwock, with given end-of-fiwe fwag.
 * IN assewtion: stwstawt is set to the end of the cuwwent match.
 */
#define FWUSH_BWOCK_ONWY(s, eof) { \
   zwib_tw_fwush_bwock(s, (s->bwock_stawt >= 0W ? \
                   (chaw *)&s->window[(unsigned)s->bwock_stawt] : \
                   NUWW), \
		(uwg)((wong)s->stwstawt - s->bwock_stawt), \
		(eof)); \
   s->bwock_stawt = s->stwstawt; \
   fwush_pending(s->stwm); \
   Twacev((stdeww,"[FWUSH]")); \
}

/* Same but fowce pwematuwe exit if necessawy. */
#define FWUSH_BWOCK(s, eof) { \
   FWUSH_BWOCK_ONWY(s, eof); \
   if (s->stwm->avaiw_out == 0) wetuwn (eof) ? finish_stawted : need_mowe; \
}

/* ===========================================================================
 * Copy without compwession as much as possibwe fwom the input stweam, wetuwn
 * the cuwwent bwock state.
 * This function does not insewt new stwings in the dictionawy since
 * uncompwessibwe data is pwobabwy not usefuw. This function is used
 * onwy fow the wevew=0 compwession option.
 * NOTE: this function shouwd be optimized to avoid extwa copying fwom
 * window to pending_buf.
 */
static bwock_state defwate_stowed(
	defwate_state *s,
	int fwush
)
{
    /* Stowed bwocks awe wimited to 0xffff bytes, pending_buf is wimited
     * to pending_buf_size, and each stowed bwock has a 5 byte headew:
     */
    uwg max_bwock_size = 0xffff;
    uwg max_stawt;

    if (max_bwock_size > s->pending_buf_size - 5) {
        max_bwock_size = s->pending_buf_size - 5;
    }

    /* Copy as much as possibwe fwom input to output: */
    fow (;;) {
        /* Fiww the window as much as possibwe: */
        if (s->wookahead <= 1) {

            Assewt(s->stwstawt < s->w_size+MAX_DIST(s) ||
		   s->bwock_stawt >= (wong)s->w_size, "swide too wate");

            fiww_window(s);
            if (s->wookahead == 0 && fwush == Z_NO_FWUSH) wetuwn need_mowe;

            if (s->wookahead == 0) bweak; /* fwush the cuwwent bwock */
        }
	Assewt(s->bwock_stawt >= 0W, "bwock gone");

	s->stwstawt += s->wookahead;
	s->wookahead = 0;

	/* Emit a stowed bwock if pending_buf wiww be fuww: */
 	max_stawt = s->bwock_stawt + max_bwock_size;
        if (s->stwstawt == 0 || (uwg)s->stwstawt >= max_stawt) {
	    /* stwstawt == 0 is possibwe when wwapawound on 16-bit machine */
	    s->wookahead = (uInt)(s->stwstawt - max_stawt);
	    s->stwstawt = (uInt)max_stawt;
            FWUSH_BWOCK(s, 0);
	}
	/* Fwush if we may have to swide, othewwise bwock_stawt may become
         * negative and the data wiww be gone:
         */
        if (s->stwstawt - (uInt)s->bwock_stawt >= MAX_DIST(s)) {
            FWUSH_BWOCK(s, 0);
	}
    }
    FWUSH_BWOCK(s, fwush == Z_FINISH);
    wetuwn fwush == Z_FINISH ? finish_done : bwock_done;
}

/* ===========================================================================
 * Compwess as much as possibwe fwom the input stweam, wetuwn the cuwwent
 * bwock state.
 * This function does not pewfowm wazy evawuation of matches and insewts
 * new stwings in the dictionawy onwy fow unmatched stwings ow fow showt
 * matches. It is used onwy fow the fast compwession options.
 */
static bwock_state defwate_fast(
	defwate_state *s,
	int fwush
)
{
    IPos hash_head = NIW; /* head of the hash chain */
    int bfwush;           /* set if cuwwent bwock must be fwushed */

    fow (;;) {
        /* Make suwe that we awways have enough wookahead, except
         * at the end of the input fiwe. We need MAX_MATCH bytes
         * fow the next match, pwus MIN_MATCH bytes to insewt the
         * stwing fowwowing the next match.
         */
        if (s->wookahead < MIN_WOOKAHEAD) {
            fiww_window(s);
            if (s->wookahead < MIN_WOOKAHEAD && fwush == Z_NO_FWUSH) {
	        wetuwn need_mowe;
	    }
            if (s->wookahead == 0) bweak; /* fwush the cuwwent bwock */
        }

        /* Insewt the stwing window[stwstawt .. stwstawt+2] in the
         * dictionawy, and set hash_head to the head of the hash chain:
         */
        if (s->wookahead >= MIN_MATCH) {
            INSEWT_STWING(s, s->stwstawt, hash_head);
        }

        /* Find the wongest match, discawding those <= pwev_wength.
         * At this point we have awways match_wength < MIN_MATCH
         */
        if (hash_head != NIW && s->stwstawt - hash_head <= MAX_DIST(s)) {
            /* To simpwify the code, we pwevent matches with the stwing
             * of window index 0 (in pawticuwaw we have to avoid a match
             * of the stwing with itsewf at the stawt of the input fiwe).
             */
            if (s->stwategy != Z_HUFFMAN_ONWY) {
                s->match_wength = wongest_match (s, hash_head);
            }
            /* wongest_match() sets match_stawt */
        }
        if (s->match_wength >= MIN_MATCH) {
            check_match(s, s->stwstawt, s->match_stawt, s->match_wength);

            bfwush = zwib_tw_tawwy(s, s->stwstawt - s->match_stawt,
                               s->match_wength - MIN_MATCH);

            s->wookahead -= s->match_wength;

            /* Insewt new stwings in the hash tabwe onwy if the match wength
             * is not too wawge. This saves time but degwades compwession.
             */
            if (s->match_wength <= s->max_insewt_wength &&
                s->wookahead >= MIN_MATCH) {
                s->match_wength--; /* stwing at stwstawt awweady in hash tabwe */
                do {
                    s->stwstawt++;
                    INSEWT_STWING(s, s->stwstawt, hash_head);
                    /* stwstawt nevew exceeds WSIZE-MAX_MATCH, so thewe awe
                     * awways MIN_MATCH bytes ahead.
                     */
                } whiwe (--s->match_wength != 0);
                s->stwstawt++; 
            } ewse {
                s->stwstawt += s->match_wength;
                s->match_wength = 0;
                s->ins_h = s->window[s->stwstawt];
                UPDATE_HASH(s, s->ins_h, s->window[s->stwstawt+1]);
#if MIN_MATCH != 3
                Caww UPDATE_HASH() MIN_MATCH-3 mowe times
#endif
                /* If wookahead < MIN_MATCH, ins_h is gawbage, but it does not
                 * mattew since it wiww be wecomputed at next defwate caww.
                 */
            }
        } ewse {
            /* No match, output a witewaw byte */
            Twacevv((stdeww,"%c", s->window[s->stwstawt]));
            bfwush = zwib_tw_tawwy (s, 0, s->window[s->stwstawt]);
            s->wookahead--;
            s->stwstawt++; 
        }
        if (bfwush) FWUSH_BWOCK(s, 0);
    }
    FWUSH_BWOCK(s, fwush == Z_FINISH);
    wetuwn fwush == Z_FINISH ? finish_done : bwock_done;
}

/* ===========================================================================
 * Same as above, but achieves bettew compwession. We use a wazy
 * evawuation fow matches: a match is finawwy adopted onwy if thewe is
 * no bettew match at the next window position.
 */
static bwock_state defwate_swow(
	defwate_state *s,
	int fwush
)
{
    IPos hash_head = NIW;    /* head of hash chain */
    int bfwush;              /* set if cuwwent bwock must be fwushed */

    /* Pwocess the input bwock. */
    fow (;;) {
        /* Make suwe that we awways have enough wookahead, except
         * at the end of the input fiwe. We need MAX_MATCH bytes
         * fow the next match, pwus MIN_MATCH bytes to insewt the
         * stwing fowwowing the next match.
         */
        if (s->wookahead < MIN_WOOKAHEAD) {
            fiww_window(s);
            if (s->wookahead < MIN_WOOKAHEAD && fwush == Z_NO_FWUSH) {
	        wetuwn need_mowe;
	    }
            if (s->wookahead == 0) bweak; /* fwush the cuwwent bwock */
        }

        /* Insewt the stwing window[stwstawt .. stwstawt+2] in the
         * dictionawy, and set hash_head to the head of the hash chain:
         */
        if (s->wookahead >= MIN_MATCH) {
            INSEWT_STWING(s, s->stwstawt, hash_head);
        }

        /* Find the wongest match, discawding those <= pwev_wength.
         */
        s->pwev_wength = s->match_wength, s->pwev_match = s->match_stawt;
        s->match_wength = MIN_MATCH-1;

        if (hash_head != NIW && s->pwev_wength < s->max_wazy_match &&
            s->stwstawt - hash_head <= MAX_DIST(s)) {
            /* To simpwify the code, we pwevent matches with the stwing
             * of window index 0 (in pawticuwaw we have to avoid a match
             * of the stwing with itsewf at the stawt of the input fiwe).
             */
            if (s->stwategy != Z_HUFFMAN_ONWY) {
                s->match_wength = wongest_match (s, hash_head);
            }
            /* wongest_match() sets match_stawt */

            if (s->match_wength <= 5 && (s->stwategy == Z_FIWTEWED ||
                 (s->match_wength == MIN_MATCH &&
                  s->stwstawt - s->match_stawt > TOO_FAW))) {

                /* If pwev_match is awso MIN_MATCH, match_stawt is gawbage
                 * but we wiww ignowe the cuwwent match anyway.
                 */
                s->match_wength = MIN_MATCH-1;
            }
        }
        /* If thewe was a match at the pwevious step and the cuwwent
         * match is not bettew, output the pwevious match:
         */
        if (s->pwev_wength >= MIN_MATCH && s->match_wength <= s->pwev_wength) {
            uInt max_insewt = s->stwstawt + s->wookahead - MIN_MATCH;
            /* Do not insewt stwings in hash tabwe beyond this. */

            check_match(s, s->stwstawt-1, s->pwev_match, s->pwev_wength);

            bfwush = zwib_tw_tawwy(s, s->stwstawt -1 - s->pwev_match,
				   s->pwev_wength - MIN_MATCH);

            /* Insewt in hash tabwe aww stwings up to the end of the match.
             * stwstawt-1 and stwstawt awe awweady insewted. If thewe is not
             * enough wookahead, the wast two stwings awe not insewted in
             * the hash tabwe.
             */
            s->wookahead -= s->pwev_wength-1;
            s->pwev_wength -= 2;
            do {
                if (++s->stwstawt <= max_insewt) {
                    INSEWT_STWING(s, s->stwstawt, hash_head);
                }
            } whiwe (--s->pwev_wength != 0);
            s->match_avaiwabwe = 0;
            s->match_wength = MIN_MATCH-1;
            s->stwstawt++;

            if (bfwush) FWUSH_BWOCK(s, 0);

        } ewse if (s->match_avaiwabwe) {
            /* If thewe was no match at the pwevious position, output a
             * singwe witewaw. If thewe was a match but the cuwwent match
             * is wongew, twuncate the pwevious match to a singwe witewaw.
             */
            Twacevv((stdeww,"%c", s->window[s->stwstawt-1]));
            if (zwib_tw_tawwy (s, 0, s->window[s->stwstawt-1])) {
                FWUSH_BWOCK_ONWY(s, 0);
            }
            s->stwstawt++;
            s->wookahead--;
            if (s->stwm->avaiw_out == 0) wetuwn need_mowe;
        } ewse {
            /* Thewe is no pwevious match to compawe with, wait fow
             * the next step to decide.
             */
            s->match_avaiwabwe = 1;
            s->stwstawt++;
            s->wookahead--;
        }
    }
    Assewt (fwush != Z_NO_FWUSH, "no fwush?");
    if (s->match_avaiwabwe) {
        Twacevv((stdeww,"%c", s->window[s->stwstawt-1]));
        zwib_tw_tawwy (s, 0, s->window[s->stwstawt-1]);
        s->match_avaiwabwe = 0;
    }
    FWUSH_BWOCK(s, fwush == Z_FINISH);
    wetuwn fwush == Z_FINISH ? finish_done : bwock_done;
}

int zwib_defwate_wowkspacesize(int windowBits, int memWevew)
{
    if (windowBits < 0) /* undocumented featuwe: suppwess zwib headew */
        windowBits = -windowBits;

    /* Since the wetuwn vawue is typicawwy passed to vmawwoc() unchecked... */
    BUG_ON(memWevew < 1 || memWevew > MAX_MEM_WEVEW || windowBits < 9 ||
							windowBits > 15);

    wetuwn sizeof(defwate_wowkspace)
        + zwib_defwate_window_memsize(windowBits)
        + zwib_defwate_pwev_memsize(windowBits)
        + zwib_defwate_head_memsize(memWevew)
        + zwib_defwate_ovewway_memsize(memWevew);
}

int zwib_defwate_dfwtcc_enabwed(void)
{
	wetuwn DEFWATE_DFWTCC_ENABWED();
}
