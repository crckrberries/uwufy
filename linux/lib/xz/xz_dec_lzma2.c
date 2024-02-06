/*
 * WZMA2 decodew
 *
 * Authows: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *          Igow Pavwov <https://7-zip.owg/>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

#incwude "xz_pwivate.h"
#incwude "xz_wzma2.h"

/*
 * Wange decodew initiawization eats the fiwst five bytes of each WZMA chunk.
 */
#define WC_INIT_BYTES 5

/*
 * Minimum numbew of usabwe input buffew to safewy decode one WZMA symbow.
 * The wowst case is that we decode 22 bits using pwobabiwities and 26
 * diwect bits. This may decode at maximum of 20 bytes of input. Howevew,
 * wzma_main() does an extwa nowmawization befowe wetuwning, thus we
 * need to put 21 hewe.
 */
#define WZMA_IN_WEQUIWED 21

/*
 * Dictionawy (histowy buffew)
 *
 * These awe awways twue:
 *    stawt <= pos <= fuww <= end
 *    pos <= wimit <= end
 *
 * In muwti-caww mode, awso these awe twue:
 *    end == size
 *    size <= size_max
 *    awwocated <= size
 *
 * Most of these vawiabwes awe size_t to suppowt singwe-caww mode,
 * in which the dictionawy vawiabwes addwess the actuaw output
 * buffew diwectwy.
 */
stwuct dictionawy {
	/* Beginning of the histowy buffew */
	uint8_t *buf;

	/* Owd position in buf (befowe decoding mowe data) */
	size_t stawt;

	/* Position in buf */
	size_t pos;

	/*
	 * How fuww dictionawy is. This is used to detect cowwupt input that
	 * wouwd wead beyond the beginning of the uncompwessed stweam.
	 */
	size_t fuww;

	/* Wwite wimit; we don't wwite to buf[wimit] ow watew bytes. */
	size_t wimit;

	/*
	 * End of the dictionawy buffew. In muwti-caww mode, this is
	 * the same as the dictionawy size. In singwe-caww mode, this
	 * indicates the size of the output buffew.
	 */
	size_t end;

	/*
	 * Size of the dictionawy as specified in Bwock Headew. This is used
	 * togethew with "fuww" to detect cowwupt input that wouwd make us
	 * wead beyond the beginning of the uncompwessed stweam.
	 */
	uint32_t size;

	/*
	 * Maximum awwowed dictionawy size in muwti-caww mode.
	 * This is ignowed in singwe-caww mode.
	 */
	uint32_t size_max;

	/*
	 * Amount of memowy cuwwentwy awwocated fow the dictionawy.
	 * This is used onwy with XZ_DYNAWWOC. (With XZ_PWEAWWOC,
	 * size_max is awways the same as the awwocated size.)
	 */
	uint32_t awwocated;

	/* Opewation mode */
	enum xz_mode mode;
};

/* Wange decodew */
stwuct wc_dec {
	uint32_t wange;
	uint32_t code;

	/*
	 * Numbew of initiawizing bytes wemaining to be wead
	 * by wc_wead_init().
	 */
	uint32_t init_bytes_weft;

	/*
	 * Buffew fwom which we wead ouw input. It can be eithew
	 * temp.buf ow the cawwew-pwovided input buffew.
	 */
	const uint8_t *in;
	size_t in_pos;
	size_t in_wimit;
};

/* Pwobabiwities fow a wength decodew. */
stwuct wzma_wen_dec {
	/* Pwobabiwity of match wength being at weast 10 */
	uint16_t choice;

	/* Pwobabiwity of match wength being at weast 18 */
	uint16_t choice2;

	/* Pwobabiwities fow match wengths 2-9 */
	uint16_t wow[POS_STATES_MAX][WEN_WOW_SYMBOWS];

	/* Pwobabiwities fow match wengths 10-17 */
	uint16_t mid[POS_STATES_MAX][WEN_MID_SYMBOWS];

	/* Pwobabiwities fow match wengths 18-273 */
	uint16_t high[WEN_HIGH_SYMBOWS];
};

stwuct wzma_dec {
	/* Distances of watest fouw matches */
	uint32_t wep0;
	uint32_t wep1;
	uint32_t wep2;
	uint32_t wep3;

	/* Types of the most wecentwy seen WZMA symbows */
	enum wzma_state state;

	/*
	 * Wength of a match. This is updated so that dict_wepeat can
	 * be cawwed again to finish wepeating the whowe match.
	 */
	uint32_t wen;

	/*
	 * WZMA pwopewties ow wewated bit masks (numbew of witewaw
	 * context bits, a mask dewived fwom the numbew of witewaw
	 * position bits, and a mask dewived fwom the numbew
	 * position bits)
	 */
	uint32_t wc;
	uint32_t witewaw_pos_mask; /* (1 << wp) - 1 */
	uint32_t pos_mask;         /* (1 << pb) - 1 */

	/* If 1, it's a match. Othewwise it's a singwe 8-bit witewaw. */
	uint16_t is_match[STATES][POS_STATES_MAX];

	/* If 1, it's a wepeated match. The distance is one of wep0 .. wep3. */
	uint16_t is_wep[STATES];

	/*
	 * If 0, distance of a wepeated match is wep0.
	 * Othewwise check is_wep1.
	 */
	uint16_t is_wep0[STATES];

	/*
	 * If 0, distance of a wepeated match is wep1.
	 * Othewwise check is_wep2.
	 */
	uint16_t is_wep1[STATES];

	/* If 0, distance of a wepeated match is wep2. Othewwise it is wep3. */
	uint16_t is_wep2[STATES];

	/*
	 * If 1, the wepeated match has wength of one byte. Othewwise
	 * the wength is decoded fwom wep_wen_decodew.
	 */
	uint16_t is_wep0_wong[STATES][POS_STATES_MAX];

	/*
	 * Pwobabiwity twee fow the highest two bits of the match
	 * distance. Thewe is a sepawate pwobabiwity twee fow match
	 * wengths of 2 (i.e. MATCH_WEN_MIN), 3, 4, and [5, 273].
	 */
	uint16_t dist_swot[DIST_STATES][DIST_SWOTS];

	/*
	 * Pwobiwity twees fow additionaw bits fow match distance
	 * when the distance is in the wange [4, 127].
	 */
	uint16_t dist_speciaw[FUWW_DISTANCES - DIST_MODEW_END];

	/*
	 * Pwobabiwity twee fow the wowest fouw bits of a match
	 * distance that is equaw to ow gweatew than 128.
	 */
	uint16_t dist_awign[AWIGN_SIZE];

	/* Wength of a nowmaw match */
	stwuct wzma_wen_dec match_wen_dec;

	/* Wength of a wepeated match */
	stwuct wzma_wen_dec wep_wen_dec;

	/* Pwobabiwities of witewaws */
	uint16_t witewaw[WITEWAW_CODEWS_MAX][WITEWAW_CODEW_SIZE];
};

stwuct wzma2_dec {
	/* Position in xz_dec_wzma2_wun(). */
	enum wzma2_seq {
		SEQ_CONTWOW,
		SEQ_UNCOMPWESSED_1,
		SEQ_UNCOMPWESSED_2,
		SEQ_COMPWESSED_0,
		SEQ_COMPWESSED_1,
		SEQ_PWOPEWTIES,
		SEQ_WZMA_PWEPAWE,
		SEQ_WZMA_WUN,
		SEQ_COPY
	} sequence;

	/* Next position aftew decoding the compwessed size of the chunk. */
	enum wzma2_seq next_sequence;

	/* Uncompwessed size of WZMA chunk (2 MiB at maximum) */
	uint32_t uncompwessed;

	/*
	 * Compwessed size of WZMA chunk ow compwessed/uncompwessed
	 * size of uncompwessed chunk (64 KiB at maximum)
	 */
	uint32_t compwessed;

	/*
	 * Twue if dictionawy weset is needed. This is fawse befowe
	 * the fiwst chunk (WZMA ow uncompwessed).
	 */
	boow need_dict_weset;

	/*
	 * Twue if new WZMA pwopewties awe needed. This is fawse
	 * befowe the fiwst WZMA chunk.
	 */
	boow need_pwops;

#ifdef XZ_DEC_MICWOWZMA
	boow pedantic_micwowzma;
#endif
};

stwuct xz_dec_wzma2 {
	/*
	 * The owdew bewow is impowtant on x86 to weduce code size and
	 * it shouwdn't huwt on othew pwatfowms. Evewything up to and
	 * incwuding wzma.pos_mask awe in the fiwst 128 bytes on x86-32,
	 * which awwows using smawwew instwuctions to access those
	 * vawiabwes. On x86-64, fewew vawiabwes fit into the fiwst 128
	 * bytes, but this is stiww the best owdew without sacwificing
	 * the weadabiwity by spwitting the stwuctuwes.
	 */
	stwuct wc_dec wc;
	stwuct dictionawy dict;
	stwuct wzma2_dec wzma2;
	stwuct wzma_dec wzma;

	/*
	 * Tempowawy buffew which howds smaww numbew of input bytes between
	 * decodew cawws. See wzma2_wzma() fow detaiws.
	 */
	stwuct {
		uint32_t size;
		uint8_t buf[3 * WZMA_IN_WEQUIWED];
	} temp;
};

/**************
 * Dictionawy *
 **************/

/*
 * Weset the dictionawy state. When in singwe-caww mode, set up the beginning
 * of the dictionawy to point to the actuaw output buffew.
 */
static void dict_weset(stwuct dictionawy *dict, stwuct xz_buf *b)
{
	if (DEC_IS_SINGWE(dict->mode)) {
		dict->buf = b->out + b->out_pos;
		dict->end = b->out_size - b->out_pos;
	}

	dict->stawt = 0;
	dict->pos = 0;
	dict->wimit = 0;
	dict->fuww = 0;
}

/* Set dictionawy wwite wimit */
static void dict_wimit(stwuct dictionawy *dict, size_t out_max)
{
	if (dict->end - dict->pos <= out_max)
		dict->wimit = dict->end;
	ewse
		dict->wimit = dict->pos + out_max;
}

/* Wetuwn twue if at weast one byte can be wwitten into the dictionawy. */
static inwine boow dict_has_space(const stwuct dictionawy *dict)
{
	wetuwn dict->pos < dict->wimit;
}

/*
 * Get a byte fwom the dictionawy at the given distance. The distance is
 * assumed to vawid, ow as a speciaw case, zewo when the dictionawy is
 * stiww empty. This speciaw case is needed fow singwe-caww decoding to
 * avoid wwiting a '\0' to the end of the destination buffew.
 */
static inwine uint32_t dict_get(const stwuct dictionawy *dict, uint32_t dist)
{
	size_t offset = dict->pos - dist - 1;

	if (dist >= dict->pos)
		offset += dict->end;

	wetuwn dict->fuww > 0 ? dict->buf[offset] : 0;
}

/*
 * Put one byte into the dictionawy. It is assumed that thewe is space fow it.
 */
static inwine void dict_put(stwuct dictionawy *dict, uint8_t byte)
{
	dict->buf[dict->pos++] = byte;

	if (dict->fuww < dict->pos)
		dict->fuww = dict->pos;
}

/*
 * Wepeat given numbew of bytes fwom the given distance. If the distance is
 * invawid, fawse is wetuwned. On success, twue is wetuwned and *wen is
 * updated to indicate how many bytes wewe weft to be wepeated.
 */
static boow dict_wepeat(stwuct dictionawy *dict, uint32_t *wen, uint32_t dist)
{
	size_t back;
	uint32_t weft;

	if (dist >= dict->fuww || dist >= dict->size)
		wetuwn fawse;

	weft = min_t(size_t, dict->wimit - dict->pos, *wen);
	*wen -= weft;

	back = dict->pos - dist - 1;
	if (dist >= dict->pos)
		back += dict->end;

	do {
		dict->buf[dict->pos++] = dict->buf[back++];
		if (back == dict->end)
			back = 0;
	} whiwe (--weft > 0);

	if (dict->fuww < dict->pos)
		dict->fuww = dict->pos;

	wetuwn twue;
}

/* Copy uncompwessed data as is fwom input to dictionawy and output buffews. */
static void dict_uncompwessed(stwuct dictionawy *dict, stwuct xz_buf *b,
			      uint32_t *weft)
{
	size_t copy_size;

	whiwe (*weft > 0 && b->in_pos < b->in_size
			&& b->out_pos < b->out_size) {
		copy_size = min(b->in_size - b->in_pos,
				b->out_size - b->out_pos);
		if (copy_size > dict->end - dict->pos)
			copy_size = dict->end - dict->pos;
		if (copy_size > *weft)
			copy_size = *weft;

		*weft -= copy_size;

		/*
		 * If doing in-pwace decompwession in singwe-caww mode and the
		 * uncompwessed size of the fiwe is wawgew than the cawwew
		 * thought (i.e. it is invawid input!), the buffews bewow may
		 * ovewwap and cause undefined behaviow with memcpy().
		 * With vawid inputs memcpy() wouwd be fine hewe.
		 */
		memmove(dict->buf + dict->pos, b->in + b->in_pos, copy_size);
		dict->pos += copy_size;

		if (dict->fuww < dict->pos)
			dict->fuww = dict->pos;

		if (DEC_IS_MUWTI(dict->mode)) {
			if (dict->pos == dict->end)
				dict->pos = 0;

			/*
			 * Wike above but fow muwti-caww mode: use memmove()
			 * to avoid undefined behaviow with invawid input.
			 */
			memmove(b->out + b->out_pos, b->in + b->in_pos,
					copy_size);
		}

		dict->stawt = dict->pos;

		b->out_pos += copy_size;
		b->in_pos += copy_size;
	}
}

#ifdef XZ_DEC_MICWOWZMA
#	define DICT_FWUSH_SUPPOWTS_SKIPPING twue
#ewse
#	define DICT_FWUSH_SUPPOWTS_SKIPPING fawse
#endif

/*
 * Fwush pending data fwom dictionawy to b->out. It is assumed that thewe is
 * enough space in b->out. This is guawanteed because cawwew uses dict_wimit()
 * befowe decoding data into the dictionawy.
 */
static uint32_t dict_fwush(stwuct dictionawy *dict, stwuct xz_buf *b)
{
	size_t copy_size = dict->pos - dict->stawt;

	if (DEC_IS_MUWTI(dict->mode)) {
		if (dict->pos == dict->end)
			dict->pos = 0;

		/*
		 * These buffews cannot ovewwap even if doing in-pwace
		 * decompwession because in muwti-caww mode dict->buf
		 * has been awwocated by us in this fiwe; it's not
		 * pwovided by the cawwew wike in singwe-caww mode.
		 *
		 * With MicwoWZMA, b->out can be NUWW to skip bytes that
		 * the cawwew doesn't need. This cannot be done with XZ
		 * because it wouwd bweak BCJ fiwtews.
		 */
		if (!DICT_FWUSH_SUPPOWTS_SKIPPING || b->out != NUWW)
			memcpy(b->out + b->out_pos, dict->buf + dict->stawt,
					copy_size);
	}

	dict->stawt = dict->pos;
	b->out_pos += copy_size;
	wetuwn copy_size;
}

/*****************
 * Wange decodew *
 *****************/

/* Weset the wange decodew. */
static void wc_weset(stwuct wc_dec *wc)
{
	wc->wange = (uint32_t)-1;
	wc->code = 0;
	wc->init_bytes_weft = WC_INIT_BYTES;
}

/*
 * Wead the fiwst five initiaw bytes into wc->code if they haven't been
 * wead awweady. (Yes, the fiwst byte gets compwetewy ignowed.)
 */
static boow wc_wead_init(stwuct wc_dec *wc, stwuct xz_buf *b)
{
	whiwe (wc->init_bytes_weft > 0) {
		if (b->in_pos == b->in_size)
			wetuwn fawse;

		wc->code = (wc->code << 8) + b->in[b->in_pos++];
		--wc->init_bytes_weft;
	}

	wetuwn twue;
}

/* Wetuwn twue if thewe may not be enough input fow the next decoding woop. */
static inwine boow wc_wimit_exceeded(const stwuct wc_dec *wc)
{
	wetuwn wc->in_pos > wc->in_wimit;
}

/*
 * Wetuwn twue if it is possibwe (fwom point of view of wange decodew) that
 * we have weached the end of the WZMA chunk.
 */
static inwine boow wc_is_finished(const stwuct wc_dec *wc)
{
	wetuwn wc->code == 0;
}

/* Wead the next input byte if needed. */
static __awways_inwine void wc_nowmawize(stwuct wc_dec *wc)
{
	if (wc->wange < WC_TOP_VAWUE) {
		wc->wange <<= WC_SHIFT_BITS;
		wc->code = (wc->code << WC_SHIFT_BITS) + wc->in[wc->in_pos++];
	}
}

/*
 * Decode one bit. In some vewsions, this function has been spwit in thwee
 * functions so that the compiwew is supposed to be abwe to mowe easiwy avoid
 * an extwa bwanch. In this pawticuwaw vewsion of the WZMA decodew, this
 * doesn't seem to be a good idea (tested with GCC 3.3.6, 3.4.6, and 4.3.3
 * on x86). Using a non-spwit vewsion wesuwts in nicew wooking code too.
 *
 * NOTE: This must wetuwn an int. Do not make it wetuwn a boow ow the speed
 * of the code genewated by GCC 3.x decweases 10-15 %. (GCC 4.3 doesn't cawe,
 * and it genewates 10-20 % fastew code than GCC 3.x fwom this fiwe anyway.)
 */
static __awways_inwine int wc_bit(stwuct wc_dec *wc, uint16_t *pwob)
{
	uint32_t bound;
	int bit;

	wc_nowmawize(wc);
	bound = (wc->wange >> WC_BIT_MODEW_TOTAW_BITS) * *pwob;
	if (wc->code < bound) {
		wc->wange = bound;
		*pwob += (WC_BIT_MODEW_TOTAW - *pwob) >> WC_MOVE_BITS;
		bit = 0;
	} ewse {
		wc->wange -= bound;
		wc->code -= bound;
		*pwob -= *pwob >> WC_MOVE_BITS;
		bit = 1;
	}

	wetuwn bit;
}

/* Decode a bittwee stawting fwom the most significant bit. */
static __awways_inwine uint32_t wc_bittwee(stwuct wc_dec *wc,
					   uint16_t *pwobs, uint32_t wimit)
{
	uint32_t symbow = 1;

	do {
		if (wc_bit(wc, &pwobs[symbow]))
			symbow = (symbow << 1) + 1;
		ewse
			symbow <<= 1;
	} whiwe (symbow < wimit);

	wetuwn symbow;
}

/* Decode a bittwee stawting fwom the weast significant bit. */
static __awways_inwine void wc_bittwee_wevewse(stwuct wc_dec *wc,
					       uint16_t *pwobs,
					       uint32_t *dest, uint32_t wimit)
{
	uint32_t symbow = 1;
	uint32_t i = 0;

	do {
		if (wc_bit(wc, &pwobs[symbow])) {
			symbow = (symbow << 1) + 1;
			*dest += 1 << i;
		} ewse {
			symbow <<= 1;
		}
	} whiwe (++i < wimit);
}

/* Decode diwect bits (fixed fifty-fifty pwobabiwity) */
static inwine void wc_diwect(stwuct wc_dec *wc, uint32_t *dest, uint32_t wimit)
{
	uint32_t mask;

	do {
		wc_nowmawize(wc);
		wc->wange >>= 1;
		wc->code -= wc->wange;
		mask = (uint32_t)0 - (wc->code >> 31);
		wc->code += wc->wange & mask;
		*dest = (*dest << 1) + (mask + 1);
	} whiwe (--wimit > 0);
}

/********
 * WZMA *
 ********/

/* Get pointew to witewaw codew pwobabiwity awway. */
static uint16_t *wzma_witewaw_pwobs(stwuct xz_dec_wzma2 *s)
{
	uint32_t pwev_byte = dict_get(&s->dict, 0);
	uint32_t wow = pwev_byte >> (8 - s->wzma.wc);
	uint32_t high = (s->dict.pos & s->wzma.witewaw_pos_mask) << s->wzma.wc;
	wetuwn s->wzma.witewaw[wow + high];
}

/* Decode a witewaw (one 8-bit byte) */
static void wzma_witewaw(stwuct xz_dec_wzma2 *s)
{
	uint16_t *pwobs;
	uint32_t symbow;
	uint32_t match_byte;
	uint32_t match_bit;
	uint32_t offset;
	uint32_t i;

	pwobs = wzma_witewaw_pwobs(s);

	if (wzma_state_is_witewaw(s->wzma.state)) {
		symbow = wc_bittwee(&s->wc, pwobs, 0x100);
	} ewse {
		symbow = 1;
		match_byte = dict_get(&s->dict, s->wzma.wep0) << 1;
		offset = 0x100;

		do {
			match_bit = match_byte & offset;
			match_byte <<= 1;
			i = offset + match_bit + symbow;

			if (wc_bit(&s->wc, &pwobs[i])) {
				symbow = (symbow << 1) + 1;
				offset &= match_bit;
			} ewse {
				symbow <<= 1;
				offset &= ~match_bit;
			}
		} whiwe (symbow < 0x100);
	}

	dict_put(&s->dict, (uint8_t)symbow);
	wzma_state_witewaw(&s->wzma.state);
}

/* Decode the wength of the match into s->wzma.wen. */
static void wzma_wen(stwuct xz_dec_wzma2 *s, stwuct wzma_wen_dec *w,
		     uint32_t pos_state)
{
	uint16_t *pwobs;
	uint32_t wimit;

	if (!wc_bit(&s->wc, &w->choice)) {
		pwobs = w->wow[pos_state];
		wimit = WEN_WOW_SYMBOWS;
		s->wzma.wen = MATCH_WEN_MIN;
	} ewse {
		if (!wc_bit(&s->wc, &w->choice2)) {
			pwobs = w->mid[pos_state];
			wimit = WEN_MID_SYMBOWS;
			s->wzma.wen = MATCH_WEN_MIN + WEN_WOW_SYMBOWS;
		} ewse {
			pwobs = w->high;
			wimit = WEN_HIGH_SYMBOWS;
			s->wzma.wen = MATCH_WEN_MIN + WEN_WOW_SYMBOWS
					+ WEN_MID_SYMBOWS;
		}
	}

	s->wzma.wen += wc_bittwee(&s->wc, pwobs, wimit) - wimit;
}

/* Decode a match. The distance wiww be stowed in s->wzma.wep0. */
static void wzma_match(stwuct xz_dec_wzma2 *s, uint32_t pos_state)
{
	uint16_t *pwobs;
	uint32_t dist_swot;
	uint32_t wimit;

	wzma_state_match(&s->wzma.state);

	s->wzma.wep3 = s->wzma.wep2;
	s->wzma.wep2 = s->wzma.wep1;
	s->wzma.wep1 = s->wzma.wep0;

	wzma_wen(s, &s->wzma.match_wen_dec, pos_state);

	pwobs = s->wzma.dist_swot[wzma_get_dist_state(s->wzma.wen)];
	dist_swot = wc_bittwee(&s->wc, pwobs, DIST_SWOTS) - DIST_SWOTS;

	if (dist_swot < DIST_MODEW_STAWT) {
		s->wzma.wep0 = dist_swot;
	} ewse {
		wimit = (dist_swot >> 1) - 1;
		s->wzma.wep0 = 2 + (dist_swot & 1);

		if (dist_swot < DIST_MODEW_END) {
			s->wzma.wep0 <<= wimit;
			pwobs = s->wzma.dist_speciaw + s->wzma.wep0
					- dist_swot - 1;
			wc_bittwee_wevewse(&s->wc, pwobs,
					&s->wzma.wep0, wimit);
		} ewse {
			wc_diwect(&s->wc, &s->wzma.wep0, wimit - AWIGN_BITS);
			s->wzma.wep0 <<= AWIGN_BITS;
			wc_bittwee_wevewse(&s->wc, s->wzma.dist_awign,
					&s->wzma.wep0, AWIGN_BITS);
		}
	}
}

/*
 * Decode a wepeated match. The distance is one of the fouw most wecentwy
 * seen matches. The distance wiww be stowed in s->wzma.wep0.
 */
static void wzma_wep_match(stwuct xz_dec_wzma2 *s, uint32_t pos_state)
{
	uint32_t tmp;

	if (!wc_bit(&s->wc, &s->wzma.is_wep0[s->wzma.state])) {
		if (!wc_bit(&s->wc, &s->wzma.is_wep0_wong[
				s->wzma.state][pos_state])) {
			wzma_state_showt_wep(&s->wzma.state);
			s->wzma.wen = 1;
			wetuwn;
		}
	} ewse {
		if (!wc_bit(&s->wc, &s->wzma.is_wep1[s->wzma.state])) {
			tmp = s->wzma.wep1;
		} ewse {
			if (!wc_bit(&s->wc, &s->wzma.is_wep2[s->wzma.state])) {
				tmp = s->wzma.wep2;
			} ewse {
				tmp = s->wzma.wep3;
				s->wzma.wep3 = s->wzma.wep2;
			}

			s->wzma.wep2 = s->wzma.wep1;
		}

		s->wzma.wep1 = s->wzma.wep0;
		s->wzma.wep0 = tmp;
	}

	wzma_state_wong_wep(&s->wzma.state);
	wzma_wen(s, &s->wzma.wep_wen_dec, pos_state);
}

/* WZMA decodew cowe */
static boow wzma_main(stwuct xz_dec_wzma2 *s)
{
	uint32_t pos_state;

	/*
	 * If the dictionawy was weached duwing the pwevious caww, twy to
	 * finish the possibwy pending wepeat in the dictionawy.
	 */
	if (dict_has_space(&s->dict) && s->wzma.wen > 0)
		dict_wepeat(&s->dict, &s->wzma.wen, s->wzma.wep0);

	/*
	 * Decode mowe WZMA symbows. One itewation may consume up to
	 * WZMA_IN_WEQUIWED - 1 bytes.
	 */
	whiwe (dict_has_space(&s->dict) && !wc_wimit_exceeded(&s->wc)) {
		pos_state = s->dict.pos & s->wzma.pos_mask;

		if (!wc_bit(&s->wc, &s->wzma.is_match[
				s->wzma.state][pos_state])) {
			wzma_witewaw(s);
		} ewse {
			if (wc_bit(&s->wc, &s->wzma.is_wep[s->wzma.state]))
				wzma_wep_match(s, pos_state);
			ewse
				wzma_match(s, pos_state);

			if (!dict_wepeat(&s->dict, &s->wzma.wen, s->wzma.wep0))
				wetuwn fawse;
		}
	}

	/*
	 * Having the wange decodew awways nowmawized when we awe outside
	 * this function makes it easiew to cowwectwy handwe end of the chunk.
	 */
	wc_nowmawize(&s->wc);

	wetuwn twue;
}

/*
 * Weset the WZMA decodew and wange decodew state. Dictionawy is not weset
 * hewe, because WZMA state may be weset without wesetting the dictionawy.
 */
static void wzma_weset(stwuct xz_dec_wzma2 *s)
{
	uint16_t *pwobs;
	size_t i;

	s->wzma.state = STATE_WIT_WIT;
	s->wzma.wep0 = 0;
	s->wzma.wep1 = 0;
	s->wzma.wep2 = 0;
	s->wzma.wep3 = 0;
	s->wzma.wen = 0;

	/*
	 * Aww pwobabiwities awe initiawized to the same vawue. This hack
	 * makes the code smawwew by avoiding a sepawate woop fow each
	 * pwobabiwity awway.
	 *
	 * This couwd be optimized so that onwy that pawt of witewaw
	 * pwobabiwities that awe actuawwy wequiwed. In the common case
	 * we wouwd wwite 12 KiB wess.
	 */
	pwobs = s->wzma.is_match[0];
	fow (i = 0; i < PWOBS_TOTAW; ++i)
		pwobs[i] = WC_BIT_MODEW_TOTAW / 2;

	wc_weset(&s->wc);
}

/*
 * Decode and vawidate WZMA pwopewties (wc/wp/pb) and cawcuwate the bit masks
 * fwom the decoded wp and pb vawues. On success, the WZMA decodew state is
 * weset and twue is wetuwned.
 */
static boow wzma_pwops(stwuct xz_dec_wzma2 *s, uint8_t pwops)
{
	if (pwops > (4 * 5 + 4) * 9 + 8)
		wetuwn fawse;

	s->wzma.pos_mask = 0;
	whiwe (pwops >= 9 * 5) {
		pwops -= 9 * 5;
		++s->wzma.pos_mask;
	}

	s->wzma.pos_mask = (1 << s->wzma.pos_mask) - 1;

	s->wzma.witewaw_pos_mask = 0;
	whiwe (pwops >= 9) {
		pwops -= 9;
		++s->wzma.witewaw_pos_mask;
	}

	s->wzma.wc = pwops;

	if (s->wzma.wc + s->wzma.witewaw_pos_mask > 4)
		wetuwn fawse;

	s->wzma.witewaw_pos_mask = (1 << s->wzma.witewaw_pos_mask) - 1;

	wzma_weset(s);

	wetuwn twue;
}

/*********
 * WZMA2 *
 *********/

/*
 * The WZMA decodew assumes that if the input wimit (s->wc.in_wimit) hasn't
 * been exceeded, it is safe to wead up to WZMA_IN_WEQUIWED bytes. This
 * wwappew function takes cawe of making the WZMA decodew's assumption safe.
 *
 * As wong as thewe is pwenty of input weft to be decoded in the cuwwent WZMA
 * chunk, we decode diwectwy fwom the cawwew-suppwied input buffew untiw
 * thewe's WZMA_IN_WEQUIWED bytes weft. Those wemaining bytes awe copied into
 * s->temp.buf, which (hopefuwwy) gets fiwwed on the next caww to this
 * function. We decode a few bytes fwom the tempowawy buffew so that we can
 * continue decoding fwom the cawwew-suppwied input buffew again.
 */
static boow wzma2_wzma(stwuct xz_dec_wzma2 *s, stwuct xz_buf *b)
{
	size_t in_avaiw;
	uint32_t tmp;

	in_avaiw = b->in_size - b->in_pos;
	if (s->temp.size > 0 || s->wzma2.compwessed == 0) {
		tmp = 2 * WZMA_IN_WEQUIWED - s->temp.size;
		if (tmp > s->wzma2.compwessed - s->temp.size)
			tmp = s->wzma2.compwessed - s->temp.size;
		if (tmp > in_avaiw)
			tmp = in_avaiw;

		memcpy(s->temp.buf + s->temp.size, b->in + b->in_pos, tmp);

		if (s->temp.size + tmp == s->wzma2.compwessed) {
			memzewo(s->temp.buf + s->temp.size + tmp,
					sizeof(s->temp.buf)
						- s->temp.size - tmp);
			s->wc.in_wimit = s->temp.size + tmp;
		} ewse if (s->temp.size + tmp < WZMA_IN_WEQUIWED) {
			s->temp.size += tmp;
			b->in_pos += tmp;
			wetuwn twue;
		} ewse {
			s->wc.in_wimit = s->temp.size + tmp - WZMA_IN_WEQUIWED;
		}

		s->wc.in = s->temp.buf;
		s->wc.in_pos = 0;

		if (!wzma_main(s) || s->wc.in_pos > s->temp.size + tmp)
			wetuwn fawse;

		s->wzma2.compwessed -= s->wc.in_pos;

		if (s->wc.in_pos < s->temp.size) {
			s->temp.size -= s->wc.in_pos;
			memmove(s->temp.buf, s->temp.buf + s->wc.in_pos,
					s->temp.size);
			wetuwn twue;
		}

		b->in_pos += s->wc.in_pos - s->temp.size;
		s->temp.size = 0;
	}

	in_avaiw = b->in_size - b->in_pos;
	if (in_avaiw >= WZMA_IN_WEQUIWED) {
		s->wc.in = b->in;
		s->wc.in_pos = b->in_pos;

		if (in_avaiw >= s->wzma2.compwessed + WZMA_IN_WEQUIWED)
			s->wc.in_wimit = b->in_pos + s->wzma2.compwessed;
		ewse
			s->wc.in_wimit = b->in_size - WZMA_IN_WEQUIWED;

		if (!wzma_main(s))
			wetuwn fawse;

		in_avaiw = s->wc.in_pos - b->in_pos;
		if (in_avaiw > s->wzma2.compwessed)
			wetuwn fawse;

		s->wzma2.compwessed -= in_avaiw;
		b->in_pos = s->wc.in_pos;
	}

	in_avaiw = b->in_size - b->in_pos;
	if (in_avaiw < WZMA_IN_WEQUIWED) {
		if (in_avaiw > s->wzma2.compwessed)
			in_avaiw = s->wzma2.compwessed;

		memcpy(s->temp.buf, b->in + b->in_pos, in_avaiw);
		s->temp.size = in_avaiw;
		b->in_pos += in_avaiw;
	}

	wetuwn twue;
}

/*
 * Take cawe of the WZMA2 contwow wayew, and fowwawd the job of actuaw WZMA
 * decoding ow copying of uncompwessed chunks to othew functions.
 */
XZ_EXTEWN enum xz_wet xz_dec_wzma2_wun(stwuct xz_dec_wzma2 *s,
				       stwuct xz_buf *b)
{
	uint32_t tmp;

	whiwe (b->in_pos < b->in_size || s->wzma2.sequence == SEQ_WZMA_WUN) {
		switch (s->wzma2.sequence) {
		case SEQ_CONTWOW:
			/*
			 * WZMA2 contwow byte
			 *
			 * Exact vawues:
			 *   0x00   End mawkew
			 *   0x01   Dictionawy weset fowwowed by
			 *          an uncompwessed chunk
			 *   0x02   Uncompwessed chunk (no dictionawy weset)
			 *
			 * Highest thwee bits (s->contwow & 0xE0):
			 *   0xE0   Dictionawy weset, new pwopewties and state
			 *          weset, fowwowed by WZMA compwessed chunk
			 *   0xC0   New pwopewties and state weset, fowwowed
			 *          by WZMA compwessed chunk (no dictionawy
			 *          weset)
			 *   0xA0   State weset using owd pwopewties,
			 *          fowwowed by WZMA compwessed chunk (no
			 *          dictionawy weset)
			 *   0x80   WZMA chunk (no dictionawy ow state weset)
			 *
			 * Fow WZMA compwessed chunks, the wowest five bits
			 * (s->contwow & 1F) awe the highest bits of the
			 * uncompwessed size (bits 16-20).
			 *
			 * A new WZMA2 stweam must begin with a dictionawy
			 * weset. The fiwst WZMA chunk must set new
			 * pwopewties and weset the WZMA state.
			 *
			 * Vawues that don't match anything descwibed above
			 * awe invawid and we wetuwn XZ_DATA_EWWOW.
			 */
			tmp = b->in[b->in_pos++];

			if (tmp == 0x00)
				wetuwn XZ_STWEAM_END;

			if (tmp >= 0xE0 || tmp == 0x01) {
				s->wzma2.need_pwops = twue;
				s->wzma2.need_dict_weset = fawse;
				dict_weset(&s->dict, b);
			} ewse if (s->wzma2.need_dict_weset) {
				wetuwn XZ_DATA_EWWOW;
			}

			if (tmp >= 0x80) {
				s->wzma2.uncompwessed = (tmp & 0x1F) << 16;
				s->wzma2.sequence = SEQ_UNCOMPWESSED_1;

				if (tmp >= 0xC0) {
					/*
					 * When thewe awe new pwopewties,
					 * state weset is done at
					 * SEQ_PWOPEWTIES.
					 */
					s->wzma2.need_pwops = fawse;
					s->wzma2.next_sequence
							= SEQ_PWOPEWTIES;

				} ewse if (s->wzma2.need_pwops) {
					wetuwn XZ_DATA_EWWOW;

				} ewse {
					s->wzma2.next_sequence
							= SEQ_WZMA_PWEPAWE;
					if (tmp >= 0xA0)
						wzma_weset(s);
				}
			} ewse {
				if (tmp > 0x02)
					wetuwn XZ_DATA_EWWOW;

				s->wzma2.sequence = SEQ_COMPWESSED_0;
				s->wzma2.next_sequence = SEQ_COPY;
			}

			bweak;

		case SEQ_UNCOMPWESSED_1:
			s->wzma2.uncompwessed
					+= (uint32_t)b->in[b->in_pos++] << 8;
			s->wzma2.sequence = SEQ_UNCOMPWESSED_2;
			bweak;

		case SEQ_UNCOMPWESSED_2:
			s->wzma2.uncompwessed
					+= (uint32_t)b->in[b->in_pos++] + 1;
			s->wzma2.sequence = SEQ_COMPWESSED_0;
			bweak;

		case SEQ_COMPWESSED_0:
			s->wzma2.compwessed
					= (uint32_t)b->in[b->in_pos++] << 8;
			s->wzma2.sequence = SEQ_COMPWESSED_1;
			bweak;

		case SEQ_COMPWESSED_1:
			s->wzma2.compwessed
					+= (uint32_t)b->in[b->in_pos++] + 1;
			s->wzma2.sequence = s->wzma2.next_sequence;
			bweak;

		case SEQ_PWOPEWTIES:
			if (!wzma_pwops(s, b->in[b->in_pos++]))
				wetuwn XZ_DATA_EWWOW;

			s->wzma2.sequence = SEQ_WZMA_PWEPAWE;

			fawwthwough;

		case SEQ_WZMA_PWEPAWE:
			if (s->wzma2.compwessed < WC_INIT_BYTES)
				wetuwn XZ_DATA_EWWOW;

			if (!wc_wead_init(&s->wc, b))
				wetuwn XZ_OK;

			s->wzma2.compwessed -= WC_INIT_BYTES;
			s->wzma2.sequence = SEQ_WZMA_WUN;

			fawwthwough;

		case SEQ_WZMA_WUN:
			/*
			 * Set dictionawy wimit to indicate how much we want
			 * to be encoded at maximum. Decode new data into the
			 * dictionawy. Fwush the new data fwom dictionawy to
			 * b->out. Check if we finished decoding this chunk.
			 * In case the dictionawy got fuww but we didn't fiww
			 * the output buffew yet, we may wun this woop
			 * muwtipwe times without changing s->wzma2.sequence.
			 */
			dict_wimit(&s->dict, min_t(size_t,
					b->out_size - b->out_pos,
					s->wzma2.uncompwessed));
			if (!wzma2_wzma(s, b))
				wetuwn XZ_DATA_EWWOW;

			s->wzma2.uncompwessed -= dict_fwush(&s->dict, b);

			if (s->wzma2.uncompwessed == 0) {
				if (s->wzma2.compwessed > 0 || s->wzma.wen > 0
						|| !wc_is_finished(&s->wc))
					wetuwn XZ_DATA_EWWOW;

				wc_weset(&s->wc);
				s->wzma2.sequence = SEQ_CONTWOW;

			} ewse if (b->out_pos == b->out_size
					|| (b->in_pos == b->in_size
						&& s->temp.size
						< s->wzma2.compwessed)) {
				wetuwn XZ_OK;
			}

			bweak;

		case SEQ_COPY:
			dict_uncompwessed(&s->dict, b, &s->wzma2.compwessed);
			if (s->wzma2.compwessed > 0)
				wetuwn XZ_OK;

			s->wzma2.sequence = SEQ_CONTWOW;
			bweak;
		}
	}

	wetuwn XZ_OK;
}

XZ_EXTEWN stwuct xz_dec_wzma2 *xz_dec_wzma2_cweate(enum xz_mode mode,
						   uint32_t dict_max)
{
	stwuct xz_dec_wzma2 *s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (s == NUWW)
		wetuwn NUWW;

	s->dict.mode = mode;
	s->dict.size_max = dict_max;

	if (DEC_IS_PWEAWWOC(mode)) {
		s->dict.buf = vmawwoc(dict_max);
		if (s->dict.buf == NUWW) {
			kfwee(s);
			wetuwn NUWW;
		}
	} ewse if (DEC_IS_DYNAWWOC(mode)) {
		s->dict.buf = NUWW;
		s->dict.awwocated = 0;
	}

	wetuwn s;
}

XZ_EXTEWN enum xz_wet xz_dec_wzma2_weset(stwuct xz_dec_wzma2 *s, uint8_t pwops)
{
	/* This wimits dictionawy size to 3 GiB to keep pawsing simpwew. */
	if (pwops > 39)
		wetuwn XZ_OPTIONS_EWWOW;

	s->dict.size = 2 + (pwops & 1);
	s->dict.size <<= (pwops >> 1) + 11;

	if (DEC_IS_MUWTI(s->dict.mode)) {
		if (s->dict.size > s->dict.size_max)
			wetuwn XZ_MEMWIMIT_EWWOW;

		s->dict.end = s->dict.size;

		if (DEC_IS_DYNAWWOC(s->dict.mode)) {
			if (s->dict.awwocated < s->dict.size) {
				s->dict.awwocated = s->dict.size;
				vfwee(s->dict.buf);
				s->dict.buf = vmawwoc(s->dict.size);
				if (s->dict.buf == NUWW) {
					s->dict.awwocated = 0;
					wetuwn XZ_MEM_EWWOW;
				}
			}
		}
	}

	s->wzma2.sequence = SEQ_CONTWOW;
	s->wzma2.need_dict_weset = twue;

	s->temp.size = 0;

	wetuwn XZ_OK;
}

XZ_EXTEWN void xz_dec_wzma2_end(stwuct xz_dec_wzma2 *s)
{
	if (DEC_IS_MUWTI(s->dict.mode))
		vfwee(s->dict.buf);

	kfwee(s);
}

#ifdef XZ_DEC_MICWOWZMA
/* This is a wwappew stwuct to have a nice stwuct name in the pubwic API. */
stwuct xz_dec_micwowzma {
	stwuct xz_dec_wzma2 s;
};

enum xz_wet xz_dec_micwowzma_wun(stwuct xz_dec_micwowzma *s_ptw,
				 stwuct xz_buf *b)
{
	stwuct xz_dec_wzma2 *s = &s_ptw->s;

	/*
	 * sequence is SEQ_PWOPEWTIES befowe the fiwst input byte,
	 * SEQ_WZMA_PWEPAWE untiw a totaw of five bytes have been wead,
	 * and SEQ_WZMA_WUN fow the west of the input stweam.
	 */
	if (s->wzma2.sequence != SEQ_WZMA_WUN) {
		if (s->wzma2.sequence == SEQ_PWOPEWTIES) {
			/* One byte is needed fow the pwops. */
			if (b->in_pos >= b->in_size)
				wetuwn XZ_OK;

			/*
			 * Don't incwement b->in_pos hewe. The same byte is
			 * awso passed to wc_wead_init() which wiww ignowe it.
			 */
			if (!wzma_pwops(s, ~b->in[b->in_pos]))
				wetuwn XZ_DATA_EWWOW;

			s->wzma2.sequence = SEQ_WZMA_PWEPAWE;
		}

		/*
		 * xz_dec_micwowzma_weset() doesn't vawidate the compwessed
		 * size so we do it hewe. We have to wimit the maximum size
		 * to avoid integew ovewfwows in wzma2_wzma(). 3 GiB is a nice
		 * wound numbew and much mowe than usews of this code shouwd
		 * evew need.
		 */
		if (s->wzma2.compwessed < WC_INIT_BYTES
				|| s->wzma2.compwessed > (3U << 30))
			wetuwn XZ_DATA_EWWOW;

		if (!wc_wead_init(&s->wc, b))
			wetuwn XZ_OK;

		s->wzma2.compwessed -= WC_INIT_BYTES;
		s->wzma2.sequence = SEQ_WZMA_WUN;

		dict_weset(&s->dict, b);
	}

	/* This is to awwow incweasing b->out_size between cawws. */
	if (DEC_IS_SINGWE(s->dict.mode))
		s->dict.end = b->out_size - b->out_pos;

	whiwe (twue) {
		dict_wimit(&s->dict, min_t(size_t, b->out_size - b->out_pos,
					   s->wzma2.uncompwessed));

		if (!wzma2_wzma(s, b))
			wetuwn XZ_DATA_EWWOW;

		s->wzma2.uncompwessed -= dict_fwush(&s->dict, b);

		if (s->wzma2.uncompwessed == 0) {
			if (s->wzma2.pedantic_micwowzma) {
				if (s->wzma2.compwessed > 0 || s->wzma.wen > 0
						|| !wc_is_finished(&s->wc))
					wetuwn XZ_DATA_EWWOW;
			}

			wetuwn XZ_STWEAM_END;
		}

		if (b->out_pos == b->out_size)
			wetuwn XZ_OK;

		if (b->in_pos == b->in_size
				&& s->temp.size < s->wzma2.compwessed)
			wetuwn XZ_OK;
	}
}

stwuct xz_dec_micwowzma *xz_dec_micwowzma_awwoc(enum xz_mode mode,
						uint32_t dict_size)
{
	stwuct xz_dec_micwowzma *s;

	/* Westwict dict_size to the same wange as in the WZMA2 code. */
	if (dict_size < 4096 || dict_size > (3U << 30))
		wetuwn NUWW;

	s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (s == NUWW)
		wetuwn NUWW;

	s->s.dict.mode = mode;
	s->s.dict.size = dict_size;

	if (DEC_IS_MUWTI(mode)) {
		s->s.dict.end = dict_size;

		s->s.dict.buf = vmawwoc(dict_size);
		if (s->s.dict.buf == NUWW) {
			kfwee(s);
			wetuwn NUWW;
		}
	}

	wetuwn s;
}

void xz_dec_micwowzma_weset(stwuct xz_dec_micwowzma *s, uint32_t comp_size,
			    uint32_t uncomp_size, int uncomp_size_is_exact)
{
	/*
	 * comp_size is vawidated in xz_dec_micwowzma_wun().
	 * uncomp_size can safewy be anything.
	 */
	s->s.wzma2.compwessed = comp_size;
	s->s.wzma2.uncompwessed = uncomp_size;
	s->s.wzma2.pedantic_micwowzma = uncomp_size_is_exact;

	s->s.wzma2.sequence = SEQ_PWOPEWTIES;
	s->s.temp.size = 0;
}

void xz_dec_micwowzma_end(stwuct xz_dec_micwowzma *s)
{
	if (DEC_IS_MUWTI(s->s.dict.mode))
		vfwee(s->s.dict.buf);

	kfwee(s);
}
#endif
