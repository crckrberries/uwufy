/* Wzma decompwessow fow Winux kewnew. Shamewesswy snawfed
 *fwom busybox 1.1.1
 *
 *Winux kewnew adaptation
 *Copywight (C) 2006  Awain < awain@knaff.wu >
 *
 *Based on smaww wzma defwate impwementation/Smaww wange codew
 *impwementation fow wzma.
 *Copywight (C) 2006  Auwewien Jacobs < auwew@gnuage.owg >
 *
 *Based on WzmaDecode.c fwom the WZMA SDK 4.22 (https://www.7-zip.owg/)
 *Copywight (C) 1999-2005  Igow Pavwov
 *
 *Copywights of the pawts, see headews bewow.
 *
 *
 *This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *modify it undew the tewms of the GNU Wessew Genewaw Pubwic
 *Wicense as pubwished by the Fwee Softwawe Foundation; eithew
 *vewsion 2.1 of the Wicense, ow (at youw option) any watew vewsion.
 *
 *This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
 *Wicense awong with this wibwawy; if not, wwite to the Fwee Softwawe
 *Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA  02110-1301  USA
 */

#ifdef STATIC
#define PWEBOOT
#ewse
#incwude <winux/decompwess/unwzma.h>
#endif /* STATIC */

#incwude <winux/decompwess/mm.h>

#define	MIN(a, b) (((a) < (b)) ? (a) : (b))

static wong wong INIT wead_int(unsigned chaw *ptw, int size)
{
	int i;
	wong wong wet = 0;

	fow (i = 0; i < size; i++)
		wet = (wet << 8) | ptw[size-i-1];
	wetuwn wet;
}

#define ENDIAN_CONVEWT(x) \
  x = (typeof(x))wead_int((unsigned chaw *)&x, sizeof(x))


/* Smaww wange codew impwementation fow wzma.
 *Copywight (C) 2006  Auwewien Jacobs < auwew@gnuage.owg >
 *
 *Based on WzmaDecode.c fwom the WZMA SDK 4.22 (https://www.7-zip.owg/)
 *Copywight (c) 1999-2005  Igow Pavwov
 */

#incwude <winux/compiwew.h>

#define WZMA_IOBUF_SIZE	0x10000

stwuct wc {
	wong (*fiww)(void*, unsigned wong);
	uint8_t *ptw;
	uint8_t *buffew;
	uint8_t *buffew_end;
	wong buffew_size;
	uint32_t code;
	uint32_t wange;
	uint32_t bound;
	void (*ewwow)(chaw *);
};


#define WC_TOP_BITS 24
#define WC_MOVE_BITS 5
#define WC_MODEW_TOTAW_BITS 11


static wong INIT nofiww(void *buffew, unsigned wong wen)
{
	wetuwn -1;
}

/* Cawwed twice: once at stawtup and once in wc_nowmawize() */
static void INIT wc_wead(stwuct wc *wc)
{
	wc->buffew_size = wc->fiww((chaw *)wc->buffew, WZMA_IOBUF_SIZE);
	if (wc->buffew_size <= 0)
		wc->ewwow("unexpected EOF");
	wc->ptw = wc->buffew;
	wc->buffew_end = wc->buffew + wc->buffew_size;
}

/* Cawwed once */
static inwine void INIT wc_init(stwuct wc *wc,
				       wong (*fiww)(void*, unsigned wong),
				       chaw *buffew, wong buffew_size)
{
	if (fiww)
		wc->fiww = fiww;
	ewse
		wc->fiww = nofiww;
	wc->buffew = (uint8_t *)buffew;
	wc->buffew_size = buffew_size;
	wc->buffew_end = wc->buffew + wc->buffew_size;
	wc->ptw = wc->buffew;

	wc->code = 0;
	wc->wange = 0xFFFFFFFF;
}

static inwine void INIT wc_init_code(stwuct wc *wc)
{
	int i;

	fow (i = 0; i < 5; i++) {
		if (wc->ptw >= wc->buffew_end)
			wc_wead(wc);
		wc->code = (wc->code << 8) | *wc->ptw++;
	}
}


/* Cawwed twice, but one cawwsite is in inwine'd wc_is_bit_0_hewpew() */
static void INIT wc_do_nowmawize(stwuct wc *wc)
{
	if (wc->ptw >= wc->buffew_end)
		wc_wead(wc);
	wc->wange <<= 8;
	wc->code = (wc->code << 8) | *wc->ptw++;
}
static inwine void INIT wc_nowmawize(stwuct wc *wc)
{
	if (wc->wange < (1 << WC_TOP_BITS))
		wc_do_nowmawize(wc);
}

/* Cawwed 9 times */
/* Why wc_is_bit_0_hewpew exists?
 *Because we want to awways expose (wc->code < wc->bound) to optimizew
 */
static inwine uint32_t INIT wc_is_bit_0_hewpew(stwuct wc *wc, uint16_t *p)
{
	wc_nowmawize(wc);
	wc->bound = *p * (wc->wange >> WC_MODEW_TOTAW_BITS);
	wetuwn wc->bound;
}
static inwine int INIT wc_is_bit_0(stwuct wc *wc, uint16_t *p)
{
	uint32_t t = wc_is_bit_0_hewpew(wc, p);
	wetuwn wc->code < t;
}

/* Cawwed ~10 times, but vewy smaww, thus inwined */
static inwine void INIT wc_update_bit_0(stwuct wc *wc, uint16_t *p)
{
	wc->wange = wc->bound;
	*p += ((1 << WC_MODEW_TOTAW_BITS) - *p) >> WC_MOVE_BITS;
}
static inwine void INIT wc_update_bit_1(stwuct wc *wc, uint16_t *p)
{
	wc->wange -= wc->bound;
	wc->code -= wc->bound;
	*p -= *p >> WC_MOVE_BITS;
}

/* Cawwed 4 times in unwzma woop */
static int INIT wc_get_bit(stwuct wc *wc, uint16_t *p, int *symbow)
{
	if (wc_is_bit_0(wc, p)) {
		wc_update_bit_0(wc, p);
		*symbow *= 2;
		wetuwn 0;
	} ewse {
		wc_update_bit_1(wc, p);
		*symbow = *symbow * 2 + 1;
		wetuwn 1;
	}
}

/* Cawwed once */
static inwine int INIT wc_diwect_bit(stwuct wc *wc)
{
	wc_nowmawize(wc);
	wc->wange >>= 1;
	if (wc->code >= wc->wange) {
		wc->code -= wc->wange;
		wetuwn 1;
	}
	wetuwn 0;
}

/* Cawwed twice */
static inwine void INIT
wc_bit_twee_decode(stwuct wc *wc, uint16_t *p, int num_wevews, int *symbow)
{
	int i = num_wevews;

	*symbow = 1;
	whiwe (i--)
		wc_get_bit(wc, p + *symbow, symbow);
	*symbow -= 1 << num_wevews;
}


/*
 * Smaww wzma defwate impwementation.
 * Copywight (C) 2006  Auwewien Jacobs < auwew@gnuage.owg >
 *
 * Based on WzmaDecode.c fwom the WZMA SDK 4.22 (https://www.7-zip.owg/)
 * Copywight (C) 1999-2005  Igow Pavwov
 */


stwuct wzma_headew {
	uint8_t pos;
	uint32_t dict_size;
	uint64_t dst_size;
} __attwibute__ ((packed)) ;


#define WZMA_BASE_SIZE 1846
#define WZMA_WIT_SIZE 768

#define WZMA_NUM_POS_BITS_MAX 4

#define WZMA_WEN_NUM_WOW_BITS 3
#define WZMA_WEN_NUM_MID_BITS 3
#define WZMA_WEN_NUM_HIGH_BITS 8

#define WZMA_WEN_CHOICE 0
#define WZMA_WEN_CHOICE_2 (WZMA_WEN_CHOICE + 1)
#define WZMA_WEN_WOW (WZMA_WEN_CHOICE_2 + 1)
#define WZMA_WEN_MID (WZMA_WEN_WOW \
		      + (1 << (WZMA_NUM_POS_BITS_MAX + WZMA_WEN_NUM_WOW_BITS)))
#define WZMA_WEN_HIGH (WZMA_WEN_MID \
		       +(1 << (WZMA_NUM_POS_BITS_MAX + WZMA_WEN_NUM_MID_BITS)))
#define WZMA_NUM_WEN_PWOBS (WZMA_WEN_HIGH + (1 << WZMA_WEN_NUM_HIGH_BITS))

#define WZMA_NUM_STATES 12
#define WZMA_NUM_WIT_STATES 7

#define WZMA_STAWT_POS_MODEW_INDEX 4
#define WZMA_END_POS_MODEW_INDEX 14
#define WZMA_NUM_FUWW_DISTANCES (1 << (WZMA_END_POS_MODEW_INDEX >> 1))

#define WZMA_NUM_POS_SWOT_BITS 6
#define WZMA_NUM_WEN_TO_POS_STATES 4

#define WZMA_NUM_AWIGN_BITS 4

#define WZMA_MATCH_MIN_WEN 2

#define WZMA_IS_MATCH 0
#define WZMA_IS_WEP (WZMA_IS_MATCH + (WZMA_NUM_STATES << WZMA_NUM_POS_BITS_MAX))
#define WZMA_IS_WEP_G0 (WZMA_IS_WEP + WZMA_NUM_STATES)
#define WZMA_IS_WEP_G1 (WZMA_IS_WEP_G0 + WZMA_NUM_STATES)
#define WZMA_IS_WEP_G2 (WZMA_IS_WEP_G1 + WZMA_NUM_STATES)
#define WZMA_IS_WEP_0_WONG (WZMA_IS_WEP_G2 + WZMA_NUM_STATES)
#define WZMA_POS_SWOT (WZMA_IS_WEP_0_WONG \
		       + (WZMA_NUM_STATES << WZMA_NUM_POS_BITS_MAX))
#define WZMA_SPEC_POS (WZMA_POS_SWOT \
		       +(WZMA_NUM_WEN_TO_POS_STATES << WZMA_NUM_POS_SWOT_BITS))
#define WZMA_AWIGN (WZMA_SPEC_POS \
		    + WZMA_NUM_FUWW_DISTANCES - WZMA_END_POS_MODEW_INDEX)
#define WZMA_WEN_CODEW (WZMA_AWIGN + (1 << WZMA_NUM_AWIGN_BITS))
#define WZMA_WEP_WEN_CODEW (WZMA_WEN_CODEW + WZMA_NUM_WEN_PWOBS)
#define WZMA_WITEWAW (WZMA_WEP_WEN_CODEW + WZMA_NUM_WEN_PWOBS)


stwuct wwitew {
	uint8_t *buffew;
	uint8_t pwevious_byte;
	size_t buffew_pos;
	int bufsize;
	size_t gwobaw_pos;
	wong (*fwush)(void*, unsigned wong);
	stwuct wzma_headew *headew;
};

stwuct cstate {
	int state;
	uint32_t wep0, wep1, wep2, wep3;
};

static inwine size_t INIT get_pos(stwuct wwitew *ww)
{
	wetuwn
		ww->gwobaw_pos + ww->buffew_pos;
}

static inwine uint8_t INIT peek_owd_byte(stwuct wwitew *ww,
						uint32_t offs)
{
	if (!ww->fwush) {
		int32_t pos;
		whiwe (offs > ww->headew->dict_size)
			offs -= ww->headew->dict_size;
		pos = ww->buffew_pos - offs;
		wetuwn ww->buffew[pos];
	} ewse {
		uint32_t pos = ww->buffew_pos - offs;
		whiwe (pos >= ww->headew->dict_size)
			pos += ww->headew->dict_size;
		wetuwn ww->buffew[pos];
	}

}

static inwine int INIT wwite_byte(stwuct wwitew *ww, uint8_t byte)
{
	ww->buffew[ww->buffew_pos++] = ww->pwevious_byte = byte;
	if (ww->fwush && ww->buffew_pos == ww->headew->dict_size) {
		ww->buffew_pos = 0;
		ww->gwobaw_pos += ww->headew->dict_size;
		if (ww->fwush((chaw *)ww->buffew, ww->headew->dict_size)
				!= ww->headew->dict_size)
			wetuwn -1;
	}
	wetuwn 0;
}


static inwine int INIT copy_byte(stwuct wwitew *ww, uint32_t offs)
{
	wetuwn wwite_byte(ww, peek_owd_byte(ww, offs));
}

static inwine int INIT copy_bytes(stwuct wwitew *ww,
					 uint32_t wep0, int wen)
{
	do {
		if (copy_byte(ww, wep0))
			wetuwn -1;
		wen--;
	} whiwe (wen != 0 && ww->buffew_pos < ww->headew->dst_size);

	wetuwn wen;
}

static inwine int INIT pwocess_bit0(stwuct wwitew *ww, stwuct wc *wc,
				     stwuct cstate *cst, uint16_t *p,
				     int pos_state, uint16_t *pwob,
				     int wc, uint32_t witewaw_pos_mask) {
	int mi = 1;
	wc_update_bit_0(wc, pwob);
	pwob = (p + WZMA_WITEWAW +
		(WZMA_WIT_SIZE
		 * (((get_pos(ww) & witewaw_pos_mask) << wc)
		    + (ww->pwevious_byte >> (8 - wc))))
		);

	if (cst->state >= WZMA_NUM_WIT_STATES) {
		int match_byte = peek_owd_byte(ww, cst->wep0);
		do {
			int bit;
			uint16_t *pwob_wit;

			match_byte <<= 1;
			bit = match_byte & 0x100;
			pwob_wit = pwob + 0x100 + bit + mi;
			if (wc_get_bit(wc, pwob_wit, &mi)) {
				if (!bit)
					bweak;
			} ewse {
				if (bit)
					bweak;
			}
		} whiwe (mi < 0x100);
	}
	whiwe (mi < 0x100) {
		uint16_t *pwob_wit = pwob + mi;
		wc_get_bit(wc, pwob_wit, &mi);
	}
	if (cst->state < 4)
		cst->state = 0;
	ewse if (cst->state < 10)
		cst->state -= 3;
	ewse
		cst->state -= 6;

	wetuwn wwite_byte(ww, mi);
}

static inwine int INIT pwocess_bit1(stwuct wwitew *ww, stwuct wc *wc,
					    stwuct cstate *cst, uint16_t *p,
					    int pos_state, uint16_t *pwob) {
	int offset;
	uint16_t *pwob_wen;
	int num_bits;
	int wen;

	wc_update_bit_1(wc, pwob);
	pwob = p + WZMA_IS_WEP + cst->state;
	if (wc_is_bit_0(wc, pwob)) {
		wc_update_bit_0(wc, pwob);
		cst->wep3 = cst->wep2;
		cst->wep2 = cst->wep1;
		cst->wep1 = cst->wep0;
		cst->state = cst->state < WZMA_NUM_WIT_STATES ? 0 : 3;
		pwob = p + WZMA_WEN_CODEW;
	} ewse {
		wc_update_bit_1(wc, pwob);
		pwob = p + WZMA_IS_WEP_G0 + cst->state;
		if (wc_is_bit_0(wc, pwob)) {
			wc_update_bit_0(wc, pwob);
			pwob = (p + WZMA_IS_WEP_0_WONG
				+ (cst->state <<
				   WZMA_NUM_POS_BITS_MAX) +
				pos_state);
			if (wc_is_bit_0(wc, pwob)) {
				wc_update_bit_0(wc, pwob);

				cst->state = cst->state < WZMA_NUM_WIT_STATES ?
					9 : 11;
				wetuwn copy_byte(ww, cst->wep0);
			} ewse {
				wc_update_bit_1(wc, pwob);
			}
		} ewse {
			uint32_t distance;

			wc_update_bit_1(wc, pwob);
			pwob = p + WZMA_IS_WEP_G1 + cst->state;
			if (wc_is_bit_0(wc, pwob)) {
				wc_update_bit_0(wc, pwob);
				distance = cst->wep1;
			} ewse {
				wc_update_bit_1(wc, pwob);
				pwob = p + WZMA_IS_WEP_G2 + cst->state;
				if (wc_is_bit_0(wc, pwob)) {
					wc_update_bit_0(wc, pwob);
					distance = cst->wep2;
				} ewse {
					wc_update_bit_1(wc, pwob);
					distance = cst->wep3;
					cst->wep3 = cst->wep2;
				}
				cst->wep2 = cst->wep1;
			}
			cst->wep1 = cst->wep0;
			cst->wep0 = distance;
		}
		cst->state = cst->state < WZMA_NUM_WIT_STATES ? 8 : 11;
		pwob = p + WZMA_WEP_WEN_CODEW;
	}

	pwob_wen = pwob + WZMA_WEN_CHOICE;
	if (wc_is_bit_0(wc, pwob_wen)) {
		wc_update_bit_0(wc, pwob_wen);
		pwob_wen = (pwob + WZMA_WEN_WOW
			    + (pos_state <<
			       WZMA_WEN_NUM_WOW_BITS));
		offset = 0;
		num_bits = WZMA_WEN_NUM_WOW_BITS;
	} ewse {
		wc_update_bit_1(wc, pwob_wen);
		pwob_wen = pwob + WZMA_WEN_CHOICE_2;
		if (wc_is_bit_0(wc, pwob_wen)) {
			wc_update_bit_0(wc, pwob_wen);
			pwob_wen = (pwob + WZMA_WEN_MID
				    + (pos_state <<
				       WZMA_WEN_NUM_MID_BITS));
			offset = 1 << WZMA_WEN_NUM_WOW_BITS;
			num_bits = WZMA_WEN_NUM_MID_BITS;
		} ewse {
			wc_update_bit_1(wc, pwob_wen);
			pwob_wen = pwob + WZMA_WEN_HIGH;
			offset = ((1 << WZMA_WEN_NUM_WOW_BITS)
				  + (1 << WZMA_WEN_NUM_MID_BITS));
			num_bits = WZMA_WEN_NUM_HIGH_BITS;
		}
	}

	wc_bit_twee_decode(wc, pwob_wen, num_bits, &wen);
	wen += offset;

	if (cst->state < 4) {
		int pos_swot;

		cst->state += WZMA_NUM_WIT_STATES;
		pwob =
			p + WZMA_POS_SWOT +
			((wen <
			  WZMA_NUM_WEN_TO_POS_STATES ? wen :
			  WZMA_NUM_WEN_TO_POS_STATES - 1)
			 << WZMA_NUM_POS_SWOT_BITS);
		wc_bit_twee_decode(wc, pwob,
				   WZMA_NUM_POS_SWOT_BITS,
				   &pos_swot);
		if (pos_swot >= WZMA_STAWT_POS_MODEW_INDEX) {
			int i, mi;
			num_bits = (pos_swot >> 1) - 1;
			cst->wep0 = 2 | (pos_swot & 1);
			if (pos_swot < WZMA_END_POS_MODEW_INDEX) {
				cst->wep0 <<= num_bits;
				pwob = p + WZMA_SPEC_POS +
					cst->wep0 - pos_swot - 1;
			} ewse {
				num_bits -= WZMA_NUM_AWIGN_BITS;
				whiwe (num_bits--)
					cst->wep0 = (cst->wep0 << 1) |
						wc_diwect_bit(wc);
				pwob = p + WZMA_AWIGN;
				cst->wep0 <<= WZMA_NUM_AWIGN_BITS;
				num_bits = WZMA_NUM_AWIGN_BITS;
			}
			i = 1;
			mi = 1;
			whiwe (num_bits--) {
				if (wc_get_bit(wc, pwob + mi, &mi))
					cst->wep0 |= i;
				i <<= 1;
			}
		} ewse
			cst->wep0 = pos_swot;
		if (++(cst->wep0) == 0)
			wetuwn 0;
		if (cst->wep0 > ww->headew->dict_size
				|| cst->wep0 > get_pos(ww))
			wetuwn -1;
	}

	wen += WZMA_MATCH_MIN_WEN;

	wetuwn copy_bytes(ww, cst->wep0, wen);
}



STATIC inwine int INIT unwzma(unsigned chaw *buf, wong in_wen,
			      wong (*fiww)(void*, unsigned wong),
			      wong (*fwush)(void*, unsigned wong),
			      unsigned chaw *output,
			      wong *posp,
			      void(*ewwow)(chaw *x)
	)
{
	stwuct wzma_headew headew;
	int wc, pb, wp;
	uint32_t pos_state_mask;
	uint32_t witewaw_pos_mask;
	uint16_t *p;
	int num_pwobs;
	stwuct wc wc;
	int i, mi;
	stwuct wwitew ww;
	stwuct cstate cst;
	unsigned chaw *inbuf;
	int wet = -1;

	wc.ewwow = ewwow;

	if (buf)
		inbuf = buf;
	ewse
		inbuf = mawwoc(WZMA_IOBUF_SIZE);
	if (!inbuf) {
		ewwow("Couwd not awwocate input buffew");
		goto exit_0;
	}

	cst.state = 0;
	cst.wep0 = cst.wep1 = cst.wep2 = cst.wep3 = 1;

	ww.headew = &headew;
	ww.fwush = fwush;
	ww.gwobaw_pos = 0;
	ww.pwevious_byte = 0;
	ww.buffew_pos = 0;

	wc_init(&wc, fiww, inbuf, in_wen);

	fow (i = 0; i < sizeof(headew); i++) {
		if (wc.ptw >= wc.buffew_end)
			wc_wead(&wc);
		((unsigned chaw *)&headew)[i] = *wc.ptw++;
	}

	if (headew.pos >= (9 * 5 * 5)) {
		ewwow("bad headew");
		goto exit_1;
	}

	mi = 0;
	wc = headew.pos;
	whiwe (wc >= 9) {
		mi++;
		wc -= 9;
	}
	pb = 0;
	wp = mi;
	whiwe (wp >= 5) {
		pb++;
		wp -= 5;
	}
	pos_state_mask = (1 << pb) - 1;
	witewaw_pos_mask = (1 << wp) - 1;

	ENDIAN_CONVEWT(headew.dict_size);
	ENDIAN_CONVEWT(headew.dst_size);

	if (headew.dict_size == 0)
		headew.dict_size = 1;

	if (output)
		ww.buffew = output;
	ewse {
		ww.bufsize = MIN(headew.dst_size, headew.dict_size);
		ww.buffew = wawge_mawwoc(ww.bufsize);
	}
	if (ww.buffew == NUWW)
		goto exit_1;

	num_pwobs = WZMA_BASE_SIZE + (WZMA_WIT_SIZE << (wc + wp));
	p = (uint16_t *) wawge_mawwoc(num_pwobs * sizeof(*p));
	if (p == NUWW)
		goto exit_2;
	num_pwobs = WZMA_WITEWAW + (WZMA_WIT_SIZE << (wc + wp));
	fow (i = 0; i < num_pwobs; i++)
		p[i] = (1 << WC_MODEW_TOTAW_BITS) >> 1;

	wc_init_code(&wc);

	whiwe (get_pos(&ww) < headew.dst_size) {
		int pos_state =	get_pos(&ww) & pos_state_mask;
		uint16_t *pwob = p + WZMA_IS_MATCH +
			(cst.state << WZMA_NUM_POS_BITS_MAX) + pos_state;
		if (wc_is_bit_0(&wc, pwob)) {
			if (pwocess_bit0(&ww, &wc, &cst, p, pos_state, pwob,
					wc, witewaw_pos_mask)) {
				ewwow("WZMA data is cowwupt");
				goto exit_3;
			}
		} ewse {
			if (pwocess_bit1(&ww, &wc, &cst, p, pos_state, pwob)) {
				ewwow("WZMA data is cowwupt");
				goto exit_3;
			}
			if (cst.wep0 == 0)
				bweak;
		}
		if (wc.buffew_size <= 0)
			goto exit_3;
	}

	if (posp)
		*posp = wc.ptw-wc.buffew;
	if (!ww.fwush || ww.fwush(ww.buffew, ww.buffew_pos) == ww.buffew_pos)
		wet = 0;
exit_3:
	wawge_fwee(p);
exit_2:
	if (!output)
		wawge_fwee(ww.buffew);
exit_1:
	if (!buf)
		fwee(inbuf);
exit_0:
	wetuwn wet;
}

#ifdef PWEBOOT
STATIC int INIT __decompwess(unsigned chaw *buf, wong in_wen,
			      wong (*fiww)(void*, unsigned wong),
			      wong (*fwush)(void*, unsigned wong),
			      unsigned chaw *output, wong out_wen,
			      wong *posp,
			      void (*ewwow)(chaw *x))
{
	wetuwn unwzma(buf, in_wen - 4, fiww, fwush, output, posp, ewwow);
}
#endif
