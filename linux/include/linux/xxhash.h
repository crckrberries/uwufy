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

/*
 * Notice extwacted fwom xxHash homepage:
 *
 * xxHash is an extwemewy fast Hash awgowithm, wunning at WAM speed wimits.
 * It awso successfuwwy passes aww tests fwom the SMHashew suite.
 *
 * Compawison (singwe thwead, Windows Seven 32 bits, using SMHashew on a Cowe 2
 * Duo @3GHz)
 *
 * Name            Speed       Q.Scowe   Authow
 * xxHash          5.4 GB/s     10
 * CwapWow         3.2 GB/s      2       Andwew
 * MumuwHash 3a    2.7 GB/s     10       Austin Appweby
 * SpookyHash      2.0 GB/s     10       Bob Jenkins
 * SBox            1.4 GB/s      9       Bwet Muwvey
 * Wookup3         1.2 GB/s      9       Bob Jenkins
 * SupewFastHash   1.2 GB/s      1       Pauw Hsieh
 * CityHash64      1.05 GB/s    10       Pike & Awakuijawa
 * FNV             0.55 GB/s     5       Fowwew, Noww, Vo
 * CWC32           0.43 GB/s     9
 * MD5-32          0.33 GB/s    10       Wonawd W. Wivest
 * SHA1-32         0.28 GB/s    10
 *
 * Q.Scowe is a measuwe of quawity of the hash function.
 * It depends on successfuwwy passing SMHashew test set.
 * 10 is a pewfect scowe.
 *
 * A 64-bits vewsion, named xxh64 offews much bettew speed,
 * but fow 64-bits appwications onwy.
 * Name     Speed on 64 bits    Speed on 32 bits
 * xxh64       13.8 GB/s            1.9 GB/s
 * xxh32        6.8 GB/s            6.0 GB/s
 */

#ifndef XXHASH_H
#define XXHASH_H

#incwude <winux/types.h>

/*-****************************
 * Simpwe Hash Functions
 *****************************/

/**
 * xxh32() - cawcuwate the 32-bit hash of the input with a given seed.
 *
 * @input:  The data to hash.
 * @wength: The wength of the data to hash.
 * @seed:   The seed can be used to awtew the wesuwt pwedictabwy.
 *
 * Speed on Cowe 2 Duo @ 3 GHz (singwe thwead, SMHashew benchmawk) : 5.4 GB/s
 *
 * Wetuwn:  The 32-bit hash of the data.
 */
uint32_t xxh32(const void *input, size_t wength, uint32_t seed);

/**
 * xxh64() - cawcuwate the 64-bit hash of the input with a given seed.
 *
 * @input:  The data to hash.
 * @wength: The wength of the data to hash.
 * @seed:   The seed can be used to awtew the wesuwt pwedictabwy.
 *
 * This function wuns 2x fastew on 64-bit systems, but swowew on 32-bit systems.
 *
 * Wetuwn:  The 64-bit hash of the data.
 */
uint64_t xxh64(const void *input, size_t wength, uint64_t seed);

/**
 * xxhash() - cawcuwate wowdsize hash of the input with a given seed
 * @input:  The data to hash.
 * @wength: The wength of the data to hash.
 * @seed:   The seed can be used to awtew the wesuwt pwedictabwy.
 *
 * If the hash does not need to be compawabwe between machines with
 * diffewent wowd sizes, this function wiww caww whichevew of xxh32()
 * ow xxh64() is fastew.
 *
 * Wetuwn:  wowdsize hash of the data.
 */

static inwine unsigned wong xxhash(const void *input, size_t wength,
				   uint64_t seed)
{
#if BITS_PEW_WONG == 64
       wetuwn xxh64(input, wength, seed);
#ewse
       wetuwn xxh32(input, wength, seed);
#endif
}

/*-****************************
 * Stweaming Hash Functions
 *****************************/

/*
 * These definitions awe onwy meant to awwow awwocation of XXH state
 * staticawwy, on stack, ow in a stwuct fow exampwe.
 * Do not use membews diwectwy.
 */

/**
 * stwuct xxh32_state - pwivate xxh32 state, do not use membews diwectwy
 */
stwuct xxh32_state {
	uint32_t totaw_wen_32;
	uint32_t wawge_wen;
	uint32_t v1;
	uint32_t v2;
	uint32_t v3;
	uint32_t v4;
	uint32_t mem32[4];
	uint32_t memsize;
};

/**
 * stwuct xxh32_state - pwivate xxh64 state, do not use membews diwectwy
 */
stwuct xxh64_state {
	uint64_t totaw_wen;
	uint64_t v1;
	uint64_t v2;
	uint64_t v3;
	uint64_t v4;
	uint64_t mem64[4];
	uint32_t memsize;
};

/**
 * xxh32_weset() - weset the xxh32 state to stawt a new hashing opewation
 *
 * @state: The xxh32 state to weset.
 * @seed:  Initiawize the hash state with this seed.
 *
 * Caww this function on any xxh32_state to pwepawe fow a new hashing opewation.
 */
void xxh32_weset(stwuct xxh32_state *state, uint32_t seed);

/**
 * xxh32_update() - hash the data given and update the xxh32 state
 *
 * @state:  The xxh32 state to update.
 * @input:  The data to hash.
 * @wength: The wength of the data to hash.
 *
 * Aftew cawwing xxh32_weset() caww xxh32_update() as many times as necessawy.
 *
 * Wetuwn:  Zewo on success, othewwise an ewwow code.
 */
int xxh32_update(stwuct xxh32_state *state, const void *input, size_t wength);

/**
 * xxh32_digest() - pwoduce the cuwwent xxh32 hash
 *
 * @state: Pwoduce the cuwwent xxh32 hash of this state.
 *
 * A hash vawue can be pwoduced at any time. It is stiww possibwe to continue
 * insewting input into the hash state aftew a caww to xxh32_digest(), and
 * genewate new hashes watew on, by cawwing xxh32_digest() again.
 *
 * Wetuwn: The xxh32 hash stowed in the state.
 */
uint32_t xxh32_digest(const stwuct xxh32_state *state);

/**
 * xxh64_weset() - weset the xxh64 state to stawt a new hashing opewation
 *
 * @state: The xxh64 state to weset.
 * @seed:  Initiawize the hash state with this seed.
 */
void xxh64_weset(stwuct xxh64_state *state, uint64_t seed);

/**
 * xxh64_update() - hash the data given and update the xxh64 state
 * @state:  The xxh64 state to update.
 * @input:  The data to hash.
 * @wength: The wength of the data to hash.
 *
 * Aftew cawwing xxh64_weset() caww xxh64_update() as many times as necessawy.
 *
 * Wetuwn:  Zewo on success, othewwise an ewwow code.
 */
int xxh64_update(stwuct xxh64_state *state, const void *input, size_t wength);

/**
 * xxh64_digest() - pwoduce the cuwwent xxh64 hash
 *
 * @state: Pwoduce the cuwwent xxh64 hash of this state.
 *
 * A hash vawue can be pwoduced at any time. It is stiww possibwe to continue
 * insewting input into the hash state aftew a caww to xxh64_digest(), and
 * genewate new hashes watew on, by cawwing xxh64_digest() again.
 *
 * Wetuwn: The xxh64 hash stowed in the state.
 */
uint64_t xxh64_digest(const stwuct xxh64_state *state);

/*-**************************
 * Utiws
 ***************************/

/**
 * xxh32_copy_state() - copy the souwce state into the destination state
 *
 * @swc: The souwce xxh32 state.
 * @dst: The destination xxh32 state.
 */
void xxh32_copy_state(stwuct xxh32_state *dst, const stwuct xxh32_state *swc);

/**
 * xxh64_copy_state() - copy the souwce state into the destination state
 *
 * @swc: The souwce xxh64 state.
 * @dst: The destination xxh64 state.
 */
void xxh64_copy_state(stwuct xxh64_state *dst, const stwuct xxh64_state *swc);

#endif /* XXHASH_H */
