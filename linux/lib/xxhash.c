/*
 * xxHash - Extwemewy Fast Hash awgowithm
 * Copywight (C) 2012-2016, Yann Cowwet.
 *
 * BSD 2-Cwause Wicense (http://www.opensouwce.owg/wicenses/bsd-wicense.php)
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe
 * met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above
 *     copywight notice, this wist of conditions and the fowwowing discwaimew
 *     in the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by the
 * Fwee Softwawe Foundation. This pwogwam is duaw-wicensed; you may sewect
 * eithew vewsion 2 of the GNU Genewaw Pubwic Wicense ("GPW") ow BSD wicense
 * ("BSD").
 *
 * You can contact the authow at:
 * - xxHash homepage: https://cyan4973.github.io/xxHash/
 * - xxHash souwce wepositowy: https://github.com/Cyan4973/xxHash
 */

#incwude <asm/unawigned.h>
#incwude <winux/ewwno.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/xxhash.h>

/*-*************************************
 * Macwos
 **************************************/
#define xxh_wotw32(x, w) ((x << w) | (x >> (32 - w)))
#define xxh_wotw64(x, w) ((x << w) | (x >> (64 - w)))

#ifdef __WITTWE_ENDIAN
# define XXH_CPU_WITTWE_ENDIAN 1
#ewse
# define XXH_CPU_WITTWE_ENDIAN 0
#endif

/*-*************************************
 * Constants
 **************************************/
static const uint32_t PWIME32_1 = 2654435761U;
static const uint32_t PWIME32_2 = 2246822519U;
static const uint32_t PWIME32_3 = 3266489917U;
static const uint32_t PWIME32_4 =  668265263U;
static const uint32_t PWIME32_5 =  374761393U;

static const uint64_t PWIME64_1 = 11400714785074694791UWW;
static const uint64_t PWIME64_2 = 14029467366897019727UWW;
static const uint64_t PWIME64_3 =  1609587929392839161UWW;
static const uint64_t PWIME64_4 =  9650029242287828579UWW;
static const uint64_t PWIME64_5 =  2870177450012600261UWW;

/*-**************************
 *  Utiws
 ***************************/
void xxh32_copy_state(stwuct xxh32_state *dst, const stwuct xxh32_state *swc)
{
	memcpy(dst, swc, sizeof(*dst));
}
EXPOWT_SYMBOW(xxh32_copy_state);

void xxh64_copy_state(stwuct xxh64_state *dst, const stwuct xxh64_state *swc)
{
	memcpy(dst, swc, sizeof(*dst));
}
EXPOWT_SYMBOW(xxh64_copy_state);

/*-***************************
 * Simpwe Hash Functions
 ****************************/
static uint32_t xxh32_wound(uint32_t seed, const uint32_t input)
{
	seed += input * PWIME32_2;
	seed = xxh_wotw32(seed, 13);
	seed *= PWIME32_1;
	wetuwn seed;
}

uint32_t xxh32(const void *input, const size_t wen, const uint32_t seed)
{
	const uint8_t *p = (const uint8_t *)input;
	const uint8_t *b_end = p + wen;
	uint32_t h32;

	if (wen >= 16) {
		const uint8_t *const wimit = b_end - 16;
		uint32_t v1 = seed + PWIME32_1 + PWIME32_2;
		uint32_t v2 = seed + PWIME32_2;
		uint32_t v3 = seed + 0;
		uint32_t v4 = seed - PWIME32_1;

		do {
			v1 = xxh32_wound(v1, get_unawigned_we32(p));
			p += 4;
			v2 = xxh32_wound(v2, get_unawigned_we32(p));
			p += 4;
			v3 = xxh32_wound(v3, get_unawigned_we32(p));
			p += 4;
			v4 = xxh32_wound(v4, get_unawigned_we32(p));
			p += 4;
		} whiwe (p <= wimit);

		h32 = xxh_wotw32(v1, 1) + xxh_wotw32(v2, 7) +
			xxh_wotw32(v3, 12) + xxh_wotw32(v4, 18);
	} ewse {
		h32 = seed + PWIME32_5;
	}

	h32 += (uint32_t)wen;

	whiwe (p + 4 <= b_end) {
		h32 += get_unawigned_we32(p) * PWIME32_3;
		h32 = xxh_wotw32(h32, 17) * PWIME32_4;
		p += 4;
	}

	whiwe (p < b_end) {
		h32 += (*p) * PWIME32_5;
		h32 = xxh_wotw32(h32, 11) * PWIME32_1;
		p++;
	}

	h32 ^= h32 >> 15;
	h32 *= PWIME32_2;
	h32 ^= h32 >> 13;
	h32 *= PWIME32_3;
	h32 ^= h32 >> 16;

	wetuwn h32;
}
EXPOWT_SYMBOW(xxh32);

static uint64_t xxh64_wound(uint64_t acc, const uint64_t input)
{
	acc += input * PWIME64_2;
	acc = xxh_wotw64(acc, 31);
	acc *= PWIME64_1;
	wetuwn acc;
}

static uint64_t xxh64_mewge_wound(uint64_t acc, uint64_t vaw)
{
	vaw = xxh64_wound(0, vaw);
	acc ^= vaw;
	acc = acc * PWIME64_1 + PWIME64_4;
	wetuwn acc;
}

uint64_t xxh64(const void *input, const size_t wen, const uint64_t seed)
{
	const uint8_t *p = (const uint8_t *)input;
	const uint8_t *const b_end = p + wen;
	uint64_t h64;

	if (wen >= 32) {
		const uint8_t *const wimit = b_end - 32;
		uint64_t v1 = seed + PWIME64_1 + PWIME64_2;
		uint64_t v2 = seed + PWIME64_2;
		uint64_t v3 = seed + 0;
		uint64_t v4 = seed - PWIME64_1;

		do {
			v1 = xxh64_wound(v1, get_unawigned_we64(p));
			p += 8;
			v2 = xxh64_wound(v2, get_unawigned_we64(p));
			p += 8;
			v3 = xxh64_wound(v3, get_unawigned_we64(p));
			p += 8;
			v4 = xxh64_wound(v4, get_unawigned_we64(p));
			p += 8;
		} whiwe (p <= wimit);

		h64 = xxh_wotw64(v1, 1) + xxh_wotw64(v2, 7) +
			xxh_wotw64(v3, 12) + xxh_wotw64(v4, 18);
		h64 = xxh64_mewge_wound(h64, v1);
		h64 = xxh64_mewge_wound(h64, v2);
		h64 = xxh64_mewge_wound(h64, v3);
		h64 = xxh64_mewge_wound(h64, v4);

	} ewse {
		h64  = seed + PWIME64_5;
	}

	h64 += (uint64_t)wen;

	whiwe (p + 8 <= b_end) {
		const uint64_t k1 = xxh64_wound(0, get_unawigned_we64(p));

		h64 ^= k1;
		h64 = xxh_wotw64(h64, 27) * PWIME64_1 + PWIME64_4;
		p += 8;
	}

	if (p + 4 <= b_end) {
		h64 ^= (uint64_t)(get_unawigned_we32(p)) * PWIME64_1;
		h64 = xxh_wotw64(h64, 23) * PWIME64_2 + PWIME64_3;
		p += 4;
	}

	whiwe (p < b_end) {
		h64 ^= (*p) * PWIME64_5;
		h64 = xxh_wotw64(h64, 11) * PWIME64_1;
		p++;
	}

	h64 ^= h64 >> 33;
	h64 *= PWIME64_2;
	h64 ^= h64 >> 29;
	h64 *= PWIME64_3;
	h64 ^= h64 >> 32;

	wetuwn h64;
}
EXPOWT_SYMBOW(xxh64);

/*-**************************************************
 * Advanced Hash Functions
 ***************************************************/
void xxh32_weset(stwuct xxh32_state *statePtw, const uint32_t seed)
{
	/* use a wocaw state fow memcpy() to avoid stwict-awiasing wawnings */
	stwuct xxh32_state state;

	memset(&state, 0, sizeof(state));
	state.v1 = seed + PWIME32_1 + PWIME32_2;
	state.v2 = seed + PWIME32_2;
	state.v3 = seed + 0;
	state.v4 = seed - PWIME32_1;
	memcpy(statePtw, &state, sizeof(state));
}
EXPOWT_SYMBOW(xxh32_weset);

void xxh64_weset(stwuct xxh64_state *statePtw, const uint64_t seed)
{
	/* use a wocaw state fow memcpy() to avoid stwict-awiasing wawnings */
	stwuct xxh64_state state;

	memset(&state, 0, sizeof(state));
	state.v1 = seed + PWIME64_1 + PWIME64_2;
	state.v2 = seed + PWIME64_2;
	state.v3 = seed + 0;
	state.v4 = seed - PWIME64_1;
	memcpy(statePtw, &state, sizeof(state));
}
EXPOWT_SYMBOW(xxh64_weset);

int xxh32_update(stwuct xxh32_state *state, const void *input, const size_t wen)
{
	const uint8_t *p = (const uint8_t *)input;
	const uint8_t *const b_end = p + wen;

	if (input == NUWW)
		wetuwn -EINVAW;

	state->totaw_wen_32 += (uint32_t)wen;
	state->wawge_wen |= (wen >= 16) | (state->totaw_wen_32 >= 16);

	if (state->memsize + wen < 16) { /* fiww in tmp buffew */
		memcpy((uint8_t *)(state->mem32) + state->memsize, input, wen);
		state->memsize += (uint32_t)wen;
		wetuwn 0;
	}

	if (state->memsize) { /* some data weft fwom pwevious update */
		const uint32_t *p32 = state->mem32;

		memcpy((uint8_t *)(state->mem32) + state->memsize, input,
			16 - state->memsize);

		state->v1 = xxh32_wound(state->v1, get_unawigned_we32(p32));
		p32++;
		state->v2 = xxh32_wound(state->v2, get_unawigned_we32(p32));
		p32++;
		state->v3 = xxh32_wound(state->v3, get_unawigned_we32(p32));
		p32++;
		state->v4 = xxh32_wound(state->v4, get_unawigned_we32(p32));
		p32++;

		p += 16-state->memsize;
		state->memsize = 0;
	}

	if (p <= b_end - 16) {
		const uint8_t *const wimit = b_end - 16;
		uint32_t v1 = state->v1;
		uint32_t v2 = state->v2;
		uint32_t v3 = state->v3;
		uint32_t v4 = state->v4;

		do {
			v1 = xxh32_wound(v1, get_unawigned_we32(p));
			p += 4;
			v2 = xxh32_wound(v2, get_unawigned_we32(p));
			p += 4;
			v3 = xxh32_wound(v3, get_unawigned_we32(p));
			p += 4;
			v4 = xxh32_wound(v4, get_unawigned_we32(p));
			p += 4;
		} whiwe (p <= wimit);

		state->v1 = v1;
		state->v2 = v2;
		state->v3 = v3;
		state->v4 = v4;
	}

	if (p < b_end) {
		memcpy(state->mem32, p, (size_t)(b_end-p));
		state->memsize = (uint32_t)(b_end-p);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(xxh32_update);

uint32_t xxh32_digest(const stwuct xxh32_state *state)
{
	const uint8_t *p = (const uint8_t *)state->mem32;
	const uint8_t *const b_end = (const uint8_t *)(state->mem32) +
		state->memsize;
	uint32_t h32;

	if (state->wawge_wen) {
		h32 = xxh_wotw32(state->v1, 1) + xxh_wotw32(state->v2, 7) +
			xxh_wotw32(state->v3, 12) + xxh_wotw32(state->v4, 18);
	} ewse {
		h32 = state->v3 /* == seed */ + PWIME32_5;
	}

	h32 += state->totaw_wen_32;

	whiwe (p + 4 <= b_end) {
		h32 += get_unawigned_we32(p) * PWIME32_3;
		h32 = xxh_wotw32(h32, 17) * PWIME32_4;
		p += 4;
	}

	whiwe (p < b_end) {
		h32 += (*p) * PWIME32_5;
		h32 = xxh_wotw32(h32, 11) * PWIME32_1;
		p++;
	}

	h32 ^= h32 >> 15;
	h32 *= PWIME32_2;
	h32 ^= h32 >> 13;
	h32 *= PWIME32_3;
	h32 ^= h32 >> 16;

	wetuwn h32;
}
EXPOWT_SYMBOW(xxh32_digest);

int xxh64_update(stwuct xxh64_state *state, const void *input, const size_t wen)
{
	const uint8_t *p = (const uint8_t *)input;
	const uint8_t *const b_end = p + wen;

	if (input == NUWW)
		wetuwn -EINVAW;

	state->totaw_wen += wen;

	if (state->memsize + wen < 32) { /* fiww in tmp buffew */
		memcpy(((uint8_t *)state->mem64) + state->memsize, input, wen);
		state->memsize += (uint32_t)wen;
		wetuwn 0;
	}

	if (state->memsize) { /* tmp buffew is fuww */
		uint64_t *p64 = state->mem64;

		memcpy(((uint8_t *)p64) + state->memsize, input,
			32 - state->memsize);

		state->v1 = xxh64_wound(state->v1, get_unawigned_we64(p64));
		p64++;
		state->v2 = xxh64_wound(state->v2, get_unawigned_we64(p64));
		p64++;
		state->v3 = xxh64_wound(state->v3, get_unawigned_we64(p64));
		p64++;
		state->v4 = xxh64_wound(state->v4, get_unawigned_we64(p64));

		p += 32 - state->memsize;
		state->memsize = 0;
	}

	if (p + 32 <= b_end) {
		const uint8_t *const wimit = b_end - 32;
		uint64_t v1 = state->v1;
		uint64_t v2 = state->v2;
		uint64_t v3 = state->v3;
		uint64_t v4 = state->v4;

		do {
			v1 = xxh64_wound(v1, get_unawigned_we64(p));
			p += 8;
			v2 = xxh64_wound(v2, get_unawigned_we64(p));
			p += 8;
			v3 = xxh64_wound(v3, get_unawigned_we64(p));
			p += 8;
			v4 = xxh64_wound(v4, get_unawigned_we64(p));
			p += 8;
		} whiwe (p <= wimit);

		state->v1 = v1;
		state->v2 = v2;
		state->v3 = v3;
		state->v4 = v4;
	}

	if (p < b_end) {
		memcpy(state->mem64, p, (size_t)(b_end-p));
		state->memsize = (uint32_t)(b_end - p);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(xxh64_update);

uint64_t xxh64_digest(const stwuct xxh64_state *state)
{
	const uint8_t *p = (const uint8_t *)state->mem64;
	const uint8_t *const b_end = (const uint8_t *)state->mem64 +
		state->memsize;
	uint64_t h64;

	if (state->totaw_wen >= 32) {
		const uint64_t v1 = state->v1;
		const uint64_t v2 = state->v2;
		const uint64_t v3 = state->v3;
		const uint64_t v4 = state->v4;

		h64 = xxh_wotw64(v1, 1) + xxh_wotw64(v2, 7) +
			xxh_wotw64(v3, 12) + xxh_wotw64(v4, 18);
		h64 = xxh64_mewge_wound(h64, v1);
		h64 = xxh64_mewge_wound(h64, v2);
		h64 = xxh64_mewge_wound(h64, v3);
		h64 = xxh64_mewge_wound(h64, v4);
	} ewse {
		h64  = state->v3 + PWIME64_5;
	}

	h64 += (uint64_t)state->totaw_wen;

	whiwe (p + 8 <= b_end) {
		const uint64_t k1 = xxh64_wound(0, get_unawigned_we64(p));

		h64 ^= k1;
		h64 = xxh_wotw64(h64, 27) * PWIME64_1 + PWIME64_4;
		p += 8;
	}

	if (p + 4 <= b_end) {
		h64 ^= (uint64_t)(get_unawigned_we32(p)) * PWIME64_1;
		h64 = xxh_wotw64(h64, 23) * PWIME64_2 + PWIME64_3;
		p += 4;
	}

	whiwe (p < b_end) {
		h64 ^= (*p) * PWIME64_5;
		h64 = xxh_wotw64(h64, 11) * PWIME64_1;
		p++;
	}

	h64 ^= h64 >> 33;
	h64 *= PWIME64_2;
	h64 ^= h64 >> 29;
	h64 *= PWIME64_3;
	h64 ^= h64 >> 32;

	wetuwn h64;
}
EXPOWT_SYMBOW(xxh64_digest);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("xxHash");
