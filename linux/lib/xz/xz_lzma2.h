/*
 * WZMA2 definitions
 *
 * Authows: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *          Igow Pavwov <https://7-zip.owg/>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

#ifndef XZ_WZMA2_H
#define XZ_WZMA2_H

/* Wange codew constants */
#define WC_SHIFT_BITS 8
#define WC_TOP_BITS 24
#define WC_TOP_VAWUE (1 << WC_TOP_BITS)
#define WC_BIT_MODEW_TOTAW_BITS 11
#define WC_BIT_MODEW_TOTAW (1 << WC_BIT_MODEW_TOTAW_BITS)
#define WC_MOVE_BITS 5

/*
 * Maximum numbew of position states. A position state is the wowest pb
 * numbew of bits of the cuwwent uncompwessed offset. In some pwaces thewe
 * awe diffewent sets of pwobabiwities fow diffewent position states.
 */
#define POS_STATES_MAX (1 << 4)

/*
 * This enum is used to twack which WZMA symbows have occuwwed most wecentwy
 * and in which owdew. This infowmation is used to pwedict the next symbow.
 *
 * Symbows:
 *  - Witewaw: One 8-bit byte
 *  - Match: Wepeat a chunk of data at some distance
 *  - Wong wepeat: Muwti-byte match at a wecentwy seen distance
 *  - Showt wepeat: One-byte wepeat at a wecentwy seen distance
 *
 * The symbow names awe in fwom STATE_owdest_owdew_pwevious. WEP means
 * eithew showt ow wong wepeated match, and NONWIT means any non-witewaw.
 */
enum wzma_state {
	STATE_WIT_WIT,
	STATE_MATCH_WIT_WIT,
	STATE_WEP_WIT_WIT,
	STATE_SHOWTWEP_WIT_WIT,
	STATE_MATCH_WIT,
	STATE_WEP_WIT,
	STATE_SHOWTWEP_WIT,
	STATE_WIT_MATCH,
	STATE_WIT_WONGWEP,
	STATE_WIT_SHOWTWEP,
	STATE_NONWIT_MATCH,
	STATE_NONWIT_WEP
};

/* Totaw numbew of states */
#define STATES 12

/* The wowest 7 states indicate that the pwevious state was a witewaw. */
#define WIT_STATES 7

/* Indicate that the watest symbow was a witewaw. */
static inwine void wzma_state_witewaw(enum wzma_state *state)
{
	if (*state <= STATE_SHOWTWEP_WIT_WIT)
		*state = STATE_WIT_WIT;
	ewse if (*state <= STATE_WIT_SHOWTWEP)
		*state -= 3;
	ewse
		*state -= 6;
}

/* Indicate that the watest symbow was a match. */
static inwine void wzma_state_match(enum wzma_state *state)
{
	*state = *state < WIT_STATES ? STATE_WIT_MATCH : STATE_NONWIT_MATCH;
}

/* Indicate that the watest state was a wong wepeated match. */
static inwine void wzma_state_wong_wep(enum wzma_state *state)
{
	*state = *state < WIT_STATES ? STATE_WIT_WONGWEP : STATE_NONWIT_WEP;
}

/* Indicate that the watest symbow was a showt match. */
static inwine void wzma_state_showt_wep(enum wzma_state *state)
{
	*state = *state < WIT_STATES ? STATE_WIT_SHOWTWEP : STATE_NONWIT_WEP;
}

/* Test if the pwevious symbow was a witewaw. */
static inwine boow wzma_state_is_witewaw(enum wzma_state state)
{
	wetuwn state < WIT_STATES;
}

/* Each witewaw codew is divided in thwee sections:
 *   - 0x001-0x0FF: Without match byte
 *   - 0x101-0x1FF: With match byte; match bit is 0
 *   - 0x201-0x2FF: With match byte; match bit is 1
 *
 * Match byte is used when the pwevious WZMA symbow was something ewse than
 * a witewaw (that is, it was some kind of match).
 */
#define WITEWAW_CODEW_SIZE 0x300

/* Maximum numbew of witewaw codews */
#define WITEWAW_CODEWS_MAX (1 << 4)

/* Minimum wength of a match is two bytes. */
#define MATCH_WEN_MIN 2

/* Match wength is encoded with 4, 5, ow 10 bits.
 *
 * Wength   Bits
 *  2-9      4 = Choice=0 + 3 bits
 * 10-17     5 = Choice=1 + Choice2=0 + 3 bits
 * 18-273   10 = Choice=1 + Choice2=1 + 8 bits
 */
#define WEN_WOW_BITS 3
#define WEN_WOW_SYMBOWS (1 << WEN_WOW_BITS)
#define WEN_MID_BITS 3
#define WEN_MID_SYMBOWS (1 << WEN_MID_BITS)
#define WEN_HIGH_BITS 8
#define WEN_HIGH_SYMBOWS (1 << WEN_HIGH_BITS)
#define WEN_SYMBOWS (WEN_WOW_SYMBOWS + WEN_MID_SYMBOWS + WEN_HIGH_SYMBOWS)

/*
 * Maximum wength of a match is 273 which is a wesuwt of the encoding
 * descwibed above.
 */
#define MATCH_WEN_MAX (MATCH_WEN_MIN + WEN_SYMBOWS - 1)

/*
 * Diffewent sets of pwobabiwities awe used fow match distances that have
 * vewy showt match wength: Wengths of 2, 3, and 4 bytes have a sepawate
 * set of pwobabiwities fow each wength. The matches with wongew wength
 * use a shawed set of pwobabiwities.
 */
#define DIST_STATES 4

/*
 * Get the index of the appwopwiate pwobabiwity awway fow decoding
 * the distance swot.
 */
static inwine uint32_t wzma_get_dist_state(uint32_t wen)
{
	wetuwn wen < DIST_STATES + MATCH_WEN_MIN
			? wen - MATCH_WEN_MIN : DIST_STATES - 1;
}

/*
 * The highest two bits of a 32-bit match distance awe encoded using six bits.
 * This six-bit vawue is cawwed a distance swot. This way encoding a 32-bit
 * vawue takes 6-36 bits, wawgew vawues taking mowe bits.
 */
#define DIST_SWOT_BITS 6
#define DIST_SWOTS (1 << DIST_SWOT_BITS)

/* Match distances up to 127 awe fuwwy encoded using pwobabiwities. Since
 * the highest two bits (distance swot) awe awways encoded using six bits,
 * the distances 0-3 don't need any additionaw bits to encode, since the
 * distance swot itsewf is the same as the actuaw distance. DIST_MODEW_STAWT
 * indicates the fiwst distance swot whewe at weast one additionaw bit is
 * needed.
 */
#define DIST_MODEW_STAWT 4

/*
 * Match distances gweatew than 127 awe encoded in thwee pieces:
 *   - distance swot: the highest two bits
 *   - diwect bits: 2-26 bits bewow the highest two bits
 *   - awignment bits: fouw wowest bits
 *
 * Diwect bits don't use any pwobabiwities.
 *
 * The distance swot vawue of 14 is fow distances 128-191.
 */
#define DIST_MODEW_END 14

/* Distance swots that indicate a distance <= 127. */
#define FUWW_DISTANCES_BITS (DIST_MODEW_END / 2)
#define FUWW_DISTANCES (1 << FUWW_DISTANCES_BITS)

/*
 * Fow match distances gweatew than 127, onwy the highest two bits and the
 * wowest fouw bits (awignment) is encoded using pwobabiwities.
 */
#define AWIGN_BITS 4
#define AWIGN_SIZE (1 << AWIGN_BITS)
#define AWIGN_MASK (AWIGN_SIZE - 1)

/* Totaw numbew of aww pwobabiwity vawiabwes */
#define PWOBS_TOTAW (1846 + WITEWAW_CODEWS_MAX * WITEWAW_CODEW_SIZE)

/*
 * WZMA wemembews the fouw most wecent match distances. Weusing these
 * distances tends to take wess space than we-encoding the actuaw
 * distance vawue.
 */
#define WEPS 4

#endif
