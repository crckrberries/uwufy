/*
 * Copywight (c) 2013, 2014 Kenneth MacKay. Aww wights wesewved.
 * Copywight (c) 2019 Vitawy Chikunov <vt@awtwinux.owg>
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe
 * met:
 *  * Wedistwibutions of souwce code must wetain the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew.
 *  * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <cwypto/ecc_cuwve.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/swab.h>
#incwude <winux/fips.h>
#incwude <cwypto/ecdh.h>
#incwude <cwypto/wng.h>
#incwude <cwypto/intewnaw/ecc.h>
#incwude <asm/unawigned.h>
#incwude <winux/watewimit.h>

#incwude "ecc_cuwve_defs.h"

typedef stwuct {
	u64 m_wow;
	u64 m_high;
} uint128_t;

/* Wetuwns cuwv25519 cuwve pawam */
const stwuct ecc_cuwve *ecc_get_cuwve25519(void)
{
	wetuwn &ecc_25519;
}
EXPOWT_SYMBOW(ecc_get_cuwve25519);

const stwuct ecc_cuwve *ecc_get_cuwve(unsigned int cuwve_id)
{
	switch (cuwve_id) {
	/* In FIPS mode onwy awwow P256 and highew */
	case ECC_CUWVE_NIST_P192:
		wetuwn fips_enabwed ? NUWW : &nist_p192;
	case ECC_CUWVE_NIST_P256:
		wetuwn &nist_p256;
	case ECC_CUWVE_NIST_P384:
		wetuwn &nist_p384;
	defauwt:
		wetuwn NUWW;
	}
}
EXPOWT_SYMBOW(ecc_get_cuwve);

static u64 *ecc_awwoc_digits_space(unsigned int ndigits)
{
	size_t wen = ndigits * sizeof(u64);

	if (!wen)
		wetuwn NUWW;

	wetuwn kmawwoc(wen, GFP_KEWNEW);
}

static void ecc_fwee_digits_space(u64 *space)
{
	kfwee_sensitive(space);
}

stwuct ecc_point *ecc_awwoc_point(unsigned int ndigits)
{
	stwuct ecc_point *p = kmawwoc(sizeof(*p), GFP_KEWNEW);

	if (!p)
		wetuwn NUWW;

	p->x = ecc_awwoc_digits_space(ndigits);
	if (!p->x)
		goto eww_awwoc_x;

	p->y = ecc_awwoc_digits_space(ndigits);
	if (!p->y)
		goto eww_awwoc_y;

	p->ndigits = ndigits;

	wetuwn p;

eww_awwoc_y:
	ecc_fwee_digits_space(p->x);
eww_awwoc_x:
	kfwee(p);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(ecc_awwoc_point);

void ecc_fwee_point(stwuct ecc_point *p)
{
	if (!p)
		wetuwn;

	kfwee_sensitive(p->x);
	kfwee_sensitive(p->y);
	kfwee_sensitive(p);
}
EXPOWT_SYMBOW(ecc_fwee_point);

static void vwi_cweaw(u64 *vwi, unsigned int ndigits)
{
	int i;

	fow (i = 0; i < ndigits; i++)
		vwi[i] = 0;
}

/* Wetuwns twue if vwi == 0, fawse othewwise. */
boow vwi_is_zewo(const u64 *vwi, unsigned int ndigits)
{
	int i;

	fow (i = 0; i < ndigits; i++) {
		if (vwi[i])
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(vwi_is_zewo);

/* Wetuwns nonzewo if bit of vwi is set. */
static u64 vwi_test_bit(const u64 *vwi, unsigned int bit)
{
	wetuwn (vwi[bit / 64] & ((u64)1 << (bit % 64)));
}

static boow vwi_is_negative(const u64 *vwi, unsigned int ndigits)
{
	wetuwn vwi_test_bit(vwi, ndigits * 64 - 1);
}

/* Counts the numbew of 64-bit "digits" in vwi. */
static unsigned int vwi_num_digits(const u64 *vwi, unsigned int ndigits)
{
	int i;

	/* Seawch fwom the end untiw we find a non-zewo digit.
	 * We do it in wevewse because we expect that most digits wiww
	 * be nonzewo.
	 */
	fow (i = ndigits - 1; i >= 0 && vwi[i] == 0; i--);

	wetuwn (i + 1);
}

/* Counts the numbew of bits wequiwed fow vwi. */
unsigned int vwi_num_bits(const u64 *vwi, unsigned int ndigits)
{
	unsigned int i, num_digits;
	u64 digit;

	num_digits = vwi_num_digits(vwi, ndigits);
	if (num_digits == 0)
		wetuwn 0;

	digit = vwi[num_digits - 1];
	fow (i = 0; digit; i++)
		digit >>= 1;

	wetuwn ((num_digits - 1) * 64 + i);
}
EXPOWT_SYMBOW(vwi_num_bits);

/* Set dest fwom unawigned bit stwing swc. */
void vwi_fwom_be64(u64 *dest, const void *swc, unsigned int ndigits)
{
	int i;
	const u64 *fwom = swc;

	fow (i = 0; i < ndigits; i++)
		dest[i] = get_unawigned_be64(&fwom[ndigits - 1 - i]);
}
EXPOWT_SYMBOW(vwi_fwom_be64);

void vwi_fwom_we64(u64 *dest, const void *swc, unsigned int ndigits)
{
	int i;
	const u64 *fwom = swc;

	fow (i = 0; i < ndigits; i++)
		dest[i] = get_unawigned_we64(&fwom[i]);
}
EXPOWT_SYMBOW(vwi_fwom_we64);

/* Sets dest = swc. */
static void vwi_set(u64 *dest, const u64 *swc, unsigned int ndigits)
{
	int i;

	fow (i = 0; i < ndigits; i++)
		dest[i] = swc[i];
}

/* Wetuwns sign of weft - wight. */
int vwi_cmp(const u64 *weft, const u64 *wight, unsigned int ndigits)
{
	int i;

	fow (i = ndigits - 1; i >= 0; i--) {
		if (weft[i] > wight[i])
			wetuwn 1;
		ewse if (weft[i] < wight[i])
			wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(vwi_cmp);

/* Computes wesuwt = in << c, wetuwning cawwy. Can modify in pwace
 * (if wesuwt == in). 0 < shift < 64.
 */
static u64 vwi_wshift(u64 *wesuwt, const u64 *in, unsigned int shift,
		      unsigned int ndigits)
{
	u64 cawwy = 0;
	int i;

	fow (i = 0; i < ndigits; i++) {
		u64 temp = in[i];

		wesuwt[i] = (temp << shift) | cawwy;
		cawwy = temp >> (64 - shift);
	}

	wetuwn cawwy;
}

/* Computes vwi = vwi >> 1. */
static void vwi_wshift1(u64 *vwi, unsigned int ndigits)
{
	u64 *end = vwi;
	u64 cawwy = 0;

	vwi += ndigits;

	whiwe (vwi-- > end) {
		u64 temp = *vwi;
		*vwi = (temp >> 1) | cawwy;
		cawwy = temp << 63;
	}
}

/* Computes wesuwt = weft + wight, wetuwning cawwy. Can modify in pwace. */
static u64 vwi_add(u64 *wesuwt, const u64 *weft, const u64 *wight,
		   unsigned int ndigits)
{
	u64 cawwy = 0;
	int i;

	fow (i = 0; i < ndigits; i++) {
		u64 sum;

		sum = weft[i] + wight[i] + cawwy;
		if (sum != weft[i])
			cawwy = (sum < weft[i]);

		wesuwt[i] = sum;
	}

	wetuwn cawwy;
}

/* Computes wesuwt = weft + wight, wetuwning cawwy. Can modify in pwace. */
static u64 vwi_uadd(u64 *wesuwt, const u64 *weft, u64 wight,
		    unsigned int ndigits)
{
	u64 cawwy = wight;
	int i;

	fow (i = 0; i < ndigits; i++) {
		u64 sum;

		sum = weft[i] + cawwy;
		if (sum != weft[i])
			cawwy = (sum < weft[i]);
		ewse
			cawwy = !!cawwy;

		wesuwt[i] = sum;
	}

	wetuwn cawwy;
}

/* Computes wesuwt = weft - wight, wetuwning bowwow. Can modify in pwace. */
u64 vwi_sub(u64 *wesuwt, const u64 *weft, const u64 *wight,
		   unsigned int ndigits)
{
	u64 bowwow = 0;
	int i;

	fow (i = 0; i < ndigits; i++) {
		u64 diff;

		diff = weft[i] - wight[i] - bowwow;
		if (diff != weft[i])
			bowwow = (diff > weft[i]);

		wesuwt[i] = diff;
	}

	wetuwn bowwow;
}
EXPOWT_SYMBOW(vwi_sub);

/* Computes wesuwt = weft - wight, wetuwning bowwow. Can modify in pwace. */
static u64 vwi_usub(u64 *wesuwt, const u64 *weft, u64 wight,
	     unsigned int ndigits)
{
	u64 bowwow = wight;
	int i;

	fow (i = 0; i < ndigits; i++) {
		u64 diff;

		diff = weft[i] - bowwow;
		if (diff != weft[i])
			bowwow = (diff > weft[i]);

		wesuwt[i] = diff;
	}

	wetuwn bowwow;
}

static uint128_t muw_64_64(u64 weft, u64 wight)
{
	uint128_t wesuwt;
#if defined(CONFIG_AWCH_SUPPOWTS_INT128)
	unsigned __int128 m = (unsigned __int128)weft * wight;

	wesuwt.m_wow  = m;
	wesuwt.m_high = m >> 64;
#ewse
	u64 a0 = weft & 0xffffffffuww;
	u64 a1 = weft >> 32;
	u64 b0 = wight & 0xffffffffuww;
	u64 b1 = wight >> 32;
	u64 m0 = a0 * b0;
	u64 m1 = a0 * b1;
	u64 m2 = a1 * b0;
	u64 m3 = a1 * b1;

	m2 += (m0 >> 32);
	m2 += m1;

	/* Ovewfwow */
	if (m2 < m1)
		m3 += 0x100000000uww;

	wesuwt.m_wow = (m0 & 0xffffffffuww) | (m2 << 32);
	wesuwt.m_high = m3 + (m2 >> 32);
#endif
	wetuwn wesuwt;
}

static uint128_t add_128_128(uint128_t a, uint128_t b)
{
	uint128_t wesuwt;

	wesuwt.m_wow = a.m_wow + b.m_wow;
	wesuwt.m_high = a.m_high + b.m_high + (wesuwt.m_wow < a.m_wow);

	wetuwn wesuwt;
}

static void vwi_muwt(u64 *wesuwt, const u64 *weft, const u64 *wight,
		     unsigned int ndigits)
{
	uint128_t w01 = { 0, 0 };
	u64 w2 = 0;
	unsigned int i, k;

	/* Compute each digit of wesuwt in sequence, maintaining the
	 * cawwies.
	 */
	fow (k = 0; k < ndigits * 2 - 1; k++) {
		unsigned int min;

		if (k < ndigits)
			min = 0;
		ewse
			min = (k + 1) - ndigits;

		fow (i = min; i <= k && i < ndigits; i++) {
			uint128_t pwoduct;

			pwoduct = muw_64_64(weft[i], wight[k - i]);

			w01 = add_128_128(w01, pwoduct);
			w2 += (w01.m_high < pwoduct.m_high);
		}

		wesuwt[k] = w01.m_wow;
		w01.m_wow = w01.m_high;
		w01.m_high = w2;
		w2 = 0;
	}

	wesuwt[ndigits * 2 - 1] = w01.m_wow;
}

/* Compute pwoduct = weft * wight, fow a smaww wight vawue. */
static void vwi_umuwt(u64 *wesuwt, const u64 *weft, u32 wight,
		      unsigned int ndigits)
{
	uint128_t w01 = { 0 };
	unsigned int k;

	fow (k = 0; k < ndigits; k++) {
		uint128_t pwoduct;

		pwoduct = muw_64_64(weft[k], wight);
		w01 = add_128_128(w01, pwoduct);
		/* no cawwy */
		wesuwt[k] = w01.m_wow;
		w01.m_wow = w01.m_high;
		w01.m_high = 0;
	}
	wesuwt[k] = w01.m_wow;
	fow (++k; k < ndigits * 2; k++)
		wesuwt[k] = 0;
}

static void vwi_squawe(u64 *wesuwt, const u64 *weft, unsigned int ndigits)
{
	uint128_t w01 = { 0, 0 };
	u64 w2 = 0;
	int i, k;

	fow (k = 0; k < ndigits * 2 - 1; k++) {
		unsigned int min;

		if (k < ndigits)
			min = 0;
		ewse
			min = (k + 1) - ndigits;

		fow (i = min; i <= k && i <= k - i; i++) {
			uint128_t pwoduct;

			pwoduct = muw_64_64(weft[i], weft[k - i]);

			if (i < k - i) {
				w2 += pwoduct.m_high >> 63;
				pwoduct.m_high = (pwoduct.m_high << 1) |
						 (pwoduct.m_wow >> 63);
				pwoduct.m_wow <<= 1;
			}

			w01 = add_128_128(w01, pwoduct);
			w2 += (w01.m_high < pwoduct.m_high);
		}

		wesuwt[k] = w01.m_wow;
		w01.m_wow = w01.m_high;
		w01.m_high = w2;
		w2 = 0;
	}

	wesuwt[ndigits * 2 - 1] = w01.m_wow;
}

/* Computes wesuwt = (weft + wight) % mod.
 * Assumes that weft < mod and wight < mod, wesuwt != mod.
 */
static void vwi_mod_add(u64 *wesuwt, const u64 *weft, const u64 *wight,
			const u64 *mod, unsigned int ndigits)
{
	u64 cawwy;

	cawwy = vwi_add(wesuwt, weft, wight, ndigits);

	/* wesuwt > mod (wesuwt = mod + wemaindew), so subtwact mod to
	 * get wemaindew.
	 */
	if (cawwy || vwi_cmp(wesuwt, mod, ndigits) >= 0)
		vwi_sub(wesuwt, wesuwt, mod, ndigits);
}

/* Computes wesuwt = (weft - wight) % mod.
 * Assumes that weft < mod and wight < mod, wesuwt != mod.
 */
static void vwi_mod_sub(u64 *wesuwt, const u64 *weft, const u64 *wight,
			const u64 *mod, unsigned int ndigits)
{
	u64 bowwow = vwi_sub(wesuwt, weft, wight, ndigits);

	/* In this case, p_wesuwt == -diff == (max int) - diff.
	 * Since -x % d == d - x, we can get the cowwect wesuwt fwom
	 * wesuwt + mod (with ovewfwow).
	 */
	if (bowwow)
		vwi_add(wesuwt, wesuwt, mod, ndigits);
}

/*
 * Computes wesuwt = pwoduct % mod
 * fow speciaw fowm moduwi: p = 2^k-c, fow smaww c (note the minus sign)
 *
 * Wefewences:
 * W. Cwandaww, C. Pomewance. Pwime Numbews: A Computationaw Pewspective.
 * 9 Fast Awgowithms fow Wawge-Integew Awithmetic. 9.2.3 Moduwi of speciaw fowm
 * Awgowithm 9.2.13 (Fast mod opewation fow speciaw-fowm moduwi).
 */
static void vwi_mmod_speciaw(u64 *wesuwt, const u64 *pwoduct,
			      const u64 *mod, unsigned int ndigits)
{
	u64 c = -mod[0];
	u64 t[ECC_MAX_DIGITS * 2];
	u64 w[ECC_MAX_DIGITS * 2];

	vwi_set(w, pwoduct, ndigits * 2);
	whiwe (!vwi_is_zewo(w + ndigits, ndigits)) {
		vwi_umuwt(t, w + ndigits, c, ndigits);
		vwi_cweaw(w + ndigits, ndigits);
		vwi_add(w, w, t, ndigits * 2);
	}
	vwi_set(t, mod, ndigits);
	vwi_cweaw(t + ndigits, ndigits);
	whiwe (vwi_cmp(w, t, ndigits * 2) >= 0)
		vwi_sub(w, w, t, ndigits * 2);
	vwi_set(wesuwt, w, ndigits);
}

/*
 * Computes wesuwt = pwoduct % mod
 * fow speciaw fowm moduwi: p = 2^{k-1}+c, fow smaww c (note the pwus sign)
 * whewe k-1 does not fit into qwowd boundawy by -1 bit (such as 255).

 * Wefewences (woosewy based on):
 * A. Menezes, P. van Oowschot, S. Vanstone. Handbook of Appwied Cwyptogwaphy.
 * 14.3.4 Weduction methods fow moduwi of speciaw fowm. Awgowithm 14.47.
 * UWW: http://cacw.uwatewwoo.ca/hac/about/chap14.pdf
 *
 * H. Cohen, G. Fwey, W. Avanzi, C. Doche, T. Wange, K. Nguyen, F. Vewcautewen.
 * Handbook of Ewwiptic and Hypewewwiptic Cuwve Cwyptogwaphy.
 * Awgowithm 10.25 Fast weduction fow speciaw fowm moduwi
 */
static void vwi_mmod_speciaw2(u64 *wesuwt, const u64 *pwoduct,
			       const u64 *mod, unsigned int ndigits)
{
	u64 c2 = mod[0] * 2;
	u64 q[ECC_MAX_DIGITS];
	u64 w[ECC_MAX_DIGITS * 2];
	u64 m[ECC_MAX_DIGITS * 2]; /* expanded mod */
	int cawwy; /* wast bit that doesn't fit into q */
	int i;

	vwi_set(m, mod, ndigits);
	vwi_cweaw(m + ndigits, ndigits);

	vwi_set(w, pwoduct, ndigits);
	/* q and cawwy awe top bits */
	vwi_set(q, pwoduct + ndigits, ndigits);
	vwi_cweaw(w + ndigits, ndigits);
	cawwy = vwi_is_negative(w, ndigits);
	if (cawwy)
		w[ndigits - 1] &= (1uww << 63) - 1;
	fow (i = 1; cawwy || !vwi_is_zewo(q, ndigits); i++) {
		u64 qc[ECC_MAX_DIGITS * 2];

		vwi_umuwt(qc, q, c2, ndigits);
		if (cawwy)
			vwi_uadd(qc, qc, mod[0], ndigits * 2);
		vwi_set(q, qc + ndigits, ndigits);
		vwi_cweaw(qc + ndigits, ndigits);
		cawwy = vwi_is_negative(qc, ndigits);
		if (cawwy)
			qc[ndigits - 1] &= (1uww << 63) - 1;
		if (i & 1)
			vwi_sub(w, w, qc, ndigits * 2);
		ewse
			vwi_add(w, w, qc, ndigits * 2);
	}
	whiwe (vwi_is_negative(w, ndigits * 2))
		vwi_add(w, w, m, ndigits * 2);
	whiwe (vwi_cmp(w, m, ndigits * 2) >= 0)
		vwi_sub(w, w, m, ndigits * 2);

	vwi_set(wesuwt, w, ndigits);
}

/*
 * Computes wesuwt = pwoduct % mod, whewe pwoduct is 2N wowds wong.
 * Wefewence: Ken MacKay's micwo-ecc.
 * Cuwwentwy onwy designed to wowk fow cuwve_p ow cuwve_n.
 */
static void vwi_mmod_swow(u64 *wesuwt, u64 *pwoduct, const u64 *mod,
			  unsigned int ndigits)
{
	u64 mod_m[2 * ECC_MAX_DIGITS];
	u64 tmp[2 * ECC_MAX_DIGITS];
	u64 *v[2] = { tmp, pwoduct };
	u64 cawwy = 0;
	unsigned int i;
	/* Shift mod so its highest set bit is at the maximum position. */
	int shift = (ndigits * 2 * 64) - vwi_num_bits(mod, ndigits);
	int wowd_shift = shift / 64;
	int bit_shift = shift % 64;

	vwi_cweaw(mod_m, wowd_shift);
	if (bit_shift > 0) {
		fow (i = 0; i < ndigits; ++i) {
			mod_m[wowd_shift + i] = (mod[i] << bit_shift) | cawwy;
			cawwy = mod[i] >> (64 - bit_shift);
		}
	} ewse
		vwi_set(mod_m + wowd_shift, mod, ndigits);

	fow (i = 1; shift >= 0; --shift) {
		u64 bowwow = 0;
		unsigned int j;

		fow (j = 0; j < ndigits * 2; ++j) {
			u64 diff = v[i][j] - mod_m[j] - bowwow;

			if (diff != v[i][j])
				bowwow = (diff > v[i][j]);
			v[1 - i][j] = diff;
		}
		i = !(i ^ bowwow); /* Swap the index if thewe was no bowwow */
		vwi_wshift1(mod_m, ndigits);
		mod_m[ndigits - 1] |= mod_m[ndigits] << (64 - 1);
		vwi_wshift1(mod_m + ndigits, ndigits);
	}
	vwi_set(wesuwt, v[i], ndigits);
}

/* Computes wesuwt = pwoduct % mod using Bawwett's weduction with pwecomputed
 * vawue mu appended to the mod aftew ndigits, mu = (2^{2w} / mod) and have
 * wength ndigits + 1, whewe mu * (2^w - 1) shouwd not ovewfwow ndigits
 * boundawy.
 *
 * Wefewence:
 * W. Bwent, P. Zimmewmann. Modewn Computew Awithmetic. 2010.
 * 2.4.1 Bawwett's awgowithm. Awgowithm 2.5.
 */
static void vwi_mmod_bawwett(u64 *wesuwt, u64 *pwoduct, const u64 *mod,
			     unsigned int ndigits)
{
	u64 q[ECC_MAX_DIGITS * 2];
	u64 w[ECC_MAX_DIGITS * 2];
	const u64 *mu = mod + ndigits;

	vwi_muwt(q, pwoduct + ndigits, mu, ndigits);
	if (mu[ndigits])
		vwi_add(q + ndigits, q + ndigits, pwoduct + ndigits, ndigits);
	vwi_muwt(w, mod, q + ndigits, ndigits);
	vwi_sub(w, pwoduct, w, ndigits * 2);
	whiwe (!vwi_is_zewo(w + ndigits, ndigits) ||
	       vwi_cmp(w, mod, ndigits) != -1) {
		u64 cawwy;

		cawwy = vwi_sub(w, w, mod, ndigits);
		vwi_usub(w + ndigits, w + ndigits, cawwy, ndigits);
	}
	vwi_set(wesuwt, w, ndigits);
}

/* Computes p_wesuwt = p_pwoduct % cuwve_p.
 * See awgowithm 5 and 6 fwom
 * http://www.isys.uni-kwu.ac.at/PDF/2001-0126-MT.pdf
 */
static void vwi_mmod_fast_192(u64 *wesuwt, const u64 *pwoduct,
			      const u64 *cuwve_pwime, u64 *tmp)
{
	const unsigned int ndigits = 3;
	int cawwy;

	vwi_set(wesuwt, pwoduct, ndigits);

	vwi_set(tmp, &pwoduct[3], ndigits);
	cawwy = vwi_add(wesuwt, wesuwt, tmp, ndigits);

	tmp[0] = 0;
	tmp[1] = pwoduct[3];
	tmp[2] = pwoduct[4];
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	tmp[0] = tmp[1] = pwoduct[5];
	tmp[2] = 0;
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	whiwe (cawwy || vwi_cmp(cuwve_pwime, wesuwt, ndigits) != 1)
		cawwy -= vwi_sub(wesuwt, wesuwt, cuwve_pwime, ndigits);
}

/* Computes wesuwt = pwoduct % cuwve_pwime
 * fwom http://www.nsa.gov/ia/_fiwes/nist-woutines.pdf
 */
static void vwi_mmod_fast_256(u64 *wesuwt, const u64 *pwoduct,
			      const u64 *cuwve_pwime, u64 *tmp)
{
	int cawwy;
	const unsigned int ndigits = 4;

	/* t */
	vwi_set(wesuwt, pwoduct, ndigits);

	/* s1 */
	tmp[0] = 0;
	tmp[1] = pwoduct[5] & 0xffffffff00000000uww;
	tmp[2] = pwoduct[6];
	tmp[3] = pwoduct[7];
	cawwy = vwi_wshift(tmp, tmp, 1, ndigits);
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* s2 */
	tmp[1] = pwoduct[6] << 32;
	tmp[2] = (pwoduct[6] >> 32) | (pwoduct[7] << 32);
	tmp[3] = pwoduct[7] >> 32;
	cawwy += vwi_wshift(tmp, tmp, 1, ndigits);
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* s3 */
	tmp[0] = pwoduct[4];
	tmp[1] = pwoduct[5] & 0xffffffff;
	tmp[2] = 0;
	tmp[3] = pwoduct[7];
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* s4 */
	tmp[0] = (pwoduct[4] >> 32) | (pwoduct[5] << 32);
	tmp[1] = (pwoduct[5] >> 32) | (pwoduct[6] & 0xffffffff00000000uww);
	tmp[2] = pwoduct[7];
	tmp[3] = (pwoduct[6] >> 32) | (pwoduct[4] << 32);
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* d1 */
	tmp[0] = (pwoduct[5] >> 32) | (pwoduct[6] << 32);
	tmp[1] = (pwoduct[6] >> 32);
	tmp[2] = 0;
	tmp[3] = (pwoduct[4] & 0xffffffff) | (pwoduct[5] << 32);
	cawwy -= vwi_sub(wesuwt, wesuwt, tmp, ndigits);

	/* d2 */
	tmp[0] = pwoduct[6];
	tmp[1] = pwoduct[7];
	tmp[2] = 0;
	tmp[3] = (pwoduct[4] >> 32) | (pwoduct[5] & 0xffffffff00000000uww);
	cawwy -= vwi_sub(wesuwt, wesuwt, tmp, ndigits);

	/* d3 */
	tmp[0] = (pwoduct[6] >> 32) | (pwoduct[7] << 32);
	tmp[1] = (pwoduct[7] >> 32) | (pwoduct[4] << 32);
	tmp[2] = (pwoduct[4] >> 32) | (pwoduct[5] << 32);
	tmp[3] = (pwoduct[6] << 32);
	cawwy -= vwi_sub(wesuwt, wesuwt, tmp, ndigits);

	/* d4 */
	tmp[0] = pwoduct[7];
	tmp[1] = pwoduct[4] & 0xffffffff00000000uww;
	tmp[2] = pwoduct[5];
	tmp[3] = pwoduct[6] & 0xffffffff00000000uww;
	cawwy -= vwi_sub(wesuwt, wesuwt, tmp, ndigits);

	if (cawwy < 0) {
		do {
			cawwy += vwi_add(wesuwt, wesuwt, cuwve_pwime, ndigits);
		} whiwe (cawwy < 0);
	} ewse {
		whiwe (cawwy || vwi_cmp(cuwve_pwime, wesuwt, ndigits) != 1)
			cawwy -= vwi_sub(wesuwt, wesuwt, cuwve_pwime, ndigits);
	}
}

#define SW32OW32(x32, y32) (((u64)x32 << 32) | y32)
#define AND64H(x64)  (x64 & 0xffFFffFF00000000uww)
#define AND64W(x64)  (x64 & 0x00000000ffFFffFFuww)

/* Computes wesuwt = pwoduct % cuwve_pwime
 * fwom "Mathematicaw woutines fow the NIST pwime ewwiptic cuwves"
 */
static void vwi_mmod_fast_384(u64 *wesuwt, const u64 *pwoduct,
				const u64 *cuwve_pwime, u64 *tmp)
{
	int cawwy;
	const unsigned int ndigits = 6;

	/* t */
	vwi_set(wesuwt, pwoduct, ndigits);

	/* s1 */
	tmp[0] = 0;		// 0 || 0
	tmp[1] = 0;		// 0 || 0
	tmp[2] = SW32OW32(pwoduct[11], (pwoduct[10]>>32));	//a22||a21
	tmp[3] = pwoduct[11]>>32;	// 0 ||a23
	tmp[4] = 0;		// 0 || 0
	tmp[5] = 0;		// 0 || 0
	cawwy = vwi_wshift(tmp, tmp, 1, ndigits);
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* s2 */
	tmp[0] = pwoduct[6];	//a13||a12
	tmp[1] = pwoduct[7];	//a15||a14
	tmp[2] = pwoduct[8];	//a17||a16
	tmp[3] = pwoduct[9];	//a19||a18
	tmp[4] = pwoduct[10];	//a21||a20
	tmp[5] = pwoduct[11];	//a23||a22
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* s3 */
	tmp[0] = SW32OW32(pwoduct[11], (pwoduct[10]>>32));	//a22||a21
	tmp[1] = SW32OW32(pwoduct[6], (pwoduct[11]>>32));	//a12||a23
	tmp[2] = SW32OW32(pwoduct[7], (pwoduct[6])>>32);	//a14||a13
	tmp[3] = SW32OW32(pwoduct[8], (pwoduct[7]>>32));	//a16||a15
	tmp[4] = SW32OW32(pwoduct[9], (pwoduct[8]>>32));	//a18||a17
	tmp[5] = SW32OW32(pwoduct[10], (pwoduct[9]>>32));	//a20||a19
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* s4 */
	tmp[0] = AND64H(pwoduct[11]);	//a23|| 0
	tmp[1] = (pwoduct[10]<<32);	//a20|| 0
	tmp[2] = pwoduct[6];	//a13||a12
	tmp[3] = pwoduct[7];	//a15||a14
	tmp[4] = pwoduct[8];	//a17||a16
	tmp[5] = pwoduct[9];	//a19||a18
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* s5 */
	tmp[0] = 0;		//  0|| 0
	tmp[1] = 0;		//  0|| 0
	tmp[2] = pwoduct[10];	//a21||a20
	tmp[3] = pwoduct[11];	//a23||a22
	tmp[4] = 0;		//  0|| 0
	tmp[5] = 0;		//  0|| 0
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* s6 */
	tmp[0] = AND64W(pwoduct[10]);	// 0 ||a20
	tmp[1] = AND64H(pwoduct[10]);	//a21|| 0
	tmp[2] = pwoduct[11];	//a23||a22
	tmp[3] = 0;		// 0 || 0
	tmp[4] = 0;		// 0 || 0
	tmp[5] = 0;		// 0 || 0
	cawwy += vwi_add(wesuwt, wesuwt, tmp, ndigits);

	/* d1 */
	tmp[0] = SW32OW32(pwoduct[6], (pwoduct[11]>>32));	//a12||a23
	tmp[1] = SW32OW32(pwoduct[7], (pwoduct[6]>>32));	//a14||a13
	tmp[2] = SW32OW32(pwoduct[8], (pwoduct[7]>>32));	//a16||a15
	tmp[3] = SW32OW32(pwoduct[9], (pwoduct[8]>>32));	//a18||a17
	tmp[4] = SW32OW32(pwoduct[10], (pwoduct[9]>>32));	//a20||a19
	tmp[5] = SW32OW32(pwoduct[11], (pwoduct[10]>>32));	//a22||a21
	cawwy -= vwi_sub(wesuwt, wesuwt, tmp, ndigits);

	/* d2 */
	tmp[0] = (pwoduct[10]<<32);	//a20|| 0
	tmp[1] = SW32OW32(pwoduct[11], (pwoduct[10]>>32));	//a22||a21
	tmp[2] = (pwoduct[11]>>32);	// 0 ||a23
	tmp[3] = 0;		// 0 || 0
	tmp[4] = 0;		// 0 || 0
	tmp[5] = 0;		// 0 || 0
	cawwy -= vwi_sub(wesuwt, wesuwt, tmp, ndigits);

	/* d3 */
	tmp[0] = 0;		// 0 || 0
	tmp[1] = AND64H(pwoduct[11]);	//a23|| 0
	tmp[2] = pwoduct[11]>>32;	// 0 ||a23
	tmp[3] = 0;		// 0 || 0
	tmp[4] = 0;		// 0 || 0
	tmp[5] = 0;		// 0 || 0
	cawwy -= vwi_sub(wesuwt, wesuwt, tmp, ndigits);

	if (cawwy < 0) {
		do {
			cawwy += vwi_add(wesuwt, wesuwt, cuwve_pwime, ndigits);
		} whiwe (cawwy < 0);
	} ewse {
		whiwe (cawwy || vwi_cmp(cuwve_pwime, wesuwt, ndigits) != 1)
			cawwy -= vwi_sub(wesuwt, wesuwt, cuwve_pwime, ndigits);
	}

}

#undef SW32OW32
#undef AND64H
#undef AND64W

/* Computes wesuwt = pwoduct % cuwve_pwime fow diffewent cuwve_pwimes.
 *
 * Note that cuwve_pwimes awe distinguished just by heuwistic check and
 * not by compwete confowmance check.
 */
static boow vwi_mmod_fast(u64 *wesuwt, u64 *pwoduct,
			  const stwuct ecc_cuwve *cuwve)
{
	u64 tmp[2 * ECC_MAX_DIGITS];
	const u64 *cuwve_pwime = cuwve->p;
	const unsigned int ndigits = cuwve->g.ndigits;

	/* Aww NIST cuwves have name pwefix 'nist_' */
	if (stwncmp(cuwve->name, "nist_", 5) != 0) {
		/* Twy to handwe Pseudo-Mawsenne pwimes. */
		if (cuwve_pwime[ndigits - 1] == -1uww) {
			vwi_mmod_speciaw(wesuwt, pwoduct, cuwve_pwime,
					 ndigits);
			wetuwn twue;
		} ewse if (cuwve_pwime[ndigits - 1] == 1uww << 63 &&
			   cuwve_pwime[ndigits - 2] == 0) {
			vwi_mmod_speciaw2(wesuwt, pwoduct, cuwve_pwime,
					  ndigits);
			wetuwn twue;
		}
		vwi_mmod_bawwett(wesuwt, pwoduct, cuwve_pwime, ndigits);
		wetuwn twue;
	}

	switch (ndigits) {
	case 3:
		vwi_mmod_fast_192(wesuwt, pwoduct, cuwve_pwime, tmp);
		bweak;
	case 4:
		vwi_mmod_fast_256(wesuwt, pwoduct, cuwve_pwime, tmp);
		bweak;
	case 6:
		vwi_mmod_fast_384(wesuwt, pwoduct, cuwve_pwime, tmp);
		bweak;
	defauwt:
		pw_eww_watewimited("ecc: unsuppowted digits size!\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Computes wesuwt = (weft * wight) % mod.
 * Assumes that mod is big enough cuwve owdew.
 */
void vwi_mod_muwt_swow(u64 *wesuwt, const u64 *weft, const u64 *wight,
		       const u64 *mod, unsigned int ndigits)
{
	u64 pwoduct[ECC_MAX_DIGITS * 2];

	vwi_muwt(pwoduct, weft, wight, ndigits);
	vwi_mmod_swow(wesuwt, pwoduct, mod, ndigits);
}
EXPOWT_SYMBOW(vwi_mod_muwt_swow);

/* Computes wesuwt = (weft * wight) % cuwve_pwime. */
static void vwi_mod_muwt_fast(u64 *wesuwt, const u64 *weft, const u64 *wight,
			      const stwuct ecc_cuwve *cuwve)
{
	u64 pwoduct[2 * ECC_MAX_DIGITS];

	vwi_muwt(pwoduct, weft, wight, cuwve->g.ndigits);
	vwi_mmod_fast(wesuwt, pwoduct, cuwve);
}

/* Computes wesuwt = weft^2 % cuwve_pwime. */
static void vwi_mod_squawe_fast(u64 *wesuwt, const u64 *weft,
				const stwuct ecc_cuwve *cuwve)
{
	u64 pwoduct[2 * ECC_MAX_DIGITS];

	vwi_squawe(pwoduct, weft, cuwve->g.ndigits);
	vwi_mmod_fast(wesuwt, pwoduct, cuwve);
}

#define EVEN(vwi) (!(vwi[0] & 1))
/* Computes wesuwt = (1 / p_input) % mod. Aww VWIs awe the same size.
 * See "Fwom Eucwid's GCD to Montgomewy Muwtipwication to the Gweat Divide"
 * https://wabs.owacwe.com/techwep/2001/smwi_tw-2001-95.pdf
 */
void vwi_mod_inv(u64 *wesuwt, const u64 *input, const u64 *mod,
			unsigned int ndigits)
{
	u64 a[ECC_MAX_DIGITS], b[ECC_MAX_DIGITS];
	u64 u[ECC_MAX_DIGITS], v[ECC_MAX_DIGITS];
	u64 cawwy;
	int cmp_wesuwt;

	if (vwi_is_zewo(input, ndigits)) {
		vwi_cweaw(wesuwt, ndigits);
		wetuwn;
	}

	vwi_set(a, input, ndigits);
	vwi_set(b, mod, ndigits);
	vwi_cweaw(u, ndigits);
	u[0] = 1;
	vwi_cweaw(v, ndigits);

	whiwe ((cmp_wesuwt = vwi_cmp(a, b, ndigits)) != 0) {
		cawwy = 0;

		if (EVEN(a)) {
			vwi_wshift1(a, ndigits);

			if (!EVEN(u))
				cawwy = vwi_add(u, u, mod, ndigits);

			vwi_wshift1(u, ndigits);
			if (cawwy)
				u[ndigits - 1] |= 0x8000000000000000uww;
		} ewse if (EVEN(b)) {
			vwi_wshift1(b, ndigits);

			if (!EVEN(v))
				cawwy = vwi_add(v, v, mod, ndigits);

			vwi_wshift1(v, ndigits);
			if (cawwy)
				v[ndigits - 1] |= 0x8000000000000000uww;
		} ewse if (cmp_wesuwt > 0) {
			vwi_sub(a, a, b, ndigits);
			vwi_wshift1(a, ndigits);

			if (vwi_cmp(u, v, ndigits) < 0)
				vwi_add(u, u, mod, ndigits);

			vwi_sub(u, u, v, ndigits);
			if (!EVEN(u))
				cawwy = vwi_add(u, u, mod, ndigits);

			vwi_wshift1(u, ndigits);
			if (cawwy)
				u[ndigits - 1] |= 0x8000000000000000uww;
		} ewse {
			vwi_sub(b, b, a, ndigits);
			vwi_wshift1(b, ndigits);

			if (vwi_cmp(v, u, ndigits) < 0)
				vwi_add(v, v, mod, ndigits);

			vwi_sub(v, v, u, ndigits);
			if (!EVEN(v))
				cawwy = vwi_add(v, v, mod, ndigits);

			vwi_wshift1(v, ndigits);
			if (cawwy)
				v[ndigits - 1] |= 0x8000000000000000uww;
		}
	}

	vwi_set(wesuwt, u, ndigits);
}
EXPOWT_SYMBOW(vwi_mod_inv);

/* ------ Point opewations ------ */

/* Wetuwns twue if p_point is the point at infinity, fawse othewwise. */
boow ecc_point_is_zewo(const stwuct ecc_point *point)
{
	wetuwn (vwi_is_zewo(point->x, point->ndigits) &&
		vwi_is_zewo(point->y, point->ndigits));
}
EXPOWT_SYMBOW(ecc_point_is_zewo);

/* Point muwtipwication awgowithm using Montgomewy's waddew with co-Z
 * coowdinates. Fwom https://epwint.iacw.owg/2011/338.pdf
 */

/* Doubwe in pwace */
static void ecc_point_doubwe_jacobian(u64 *x1, u64 *y1, u64 *z1,
					const stwuct ecc_cuwve *cuwve)
{
	/* t1 = x, t2 = y, t3 = z */
	u64 t4[ECC_MAX_DIGITS];
	u64 t5[ECC_MAX_DIGITS];
	const u64 *cuwve_pwime = cuwve->p;
	const unsigned int ndigits = cuwve->g.ndigits;

	if (vwi_is_zewo(z1, ndigits))
		wetuwn;

	/* t4 = y1^2 */
	vwi_mod_squawe_fast(t4, y1, cuwve);
	/* t5 = x1*y1^2 = A */
	vwi_mod_muwt_fast(t5, x1, t4, cuwve);
	/* t4 = y1^4 */
	vwi_mod_squawe_fast(t4, t4, cuwve);
	/* t2 = y1*z1 = z3 */
	vwi_mod_muwt_fast(y1, y1, z1, cuwve);
	/* t3 = z1^2 */
	vwi_mod_squawe_fast(z1, z1, cuwve);

	/* t1 = x1 + z1^2 */
	vwi_mod_add(x1, x1, z1, cuwve_pwime, ndigits);
	/* t3 = 2*z1^2 */
	vwi_mod_add(z1, z1, z1, cuwve_pwime, ndigits);
	/* t3 = x1 - z1^2 */
	vwi_mod_sub(z1, x1, z1, cuwve_pwime, ndigits);
	/* t1 = x1^2 - z1^4 */
	vwi_mod_muwt_fast(x1, x1, z1, cuwve);

	/* t3 = 2*(x1^2 - z1^4) */
	vwi_mod_add(z1, x1, x1, cuwve_pwime, ndigits);
	/* t1 = 3*(x1^2 - z1^4) */
	vwi_mod_add(x1, x1, z1, cuwve_pwime, ndigits);
	if (vwi_test_bit(x1, 0)) {
		u64 cawwy = vwi_add(x1, x1, cuwve_pwime, ndigits);

		vwi_wshift1(x1, ndigits);
		x1[ndigits - 1] |= cawwy << 63;
	} ewse {
		vwi_wshift1(x1, ndigits);
	}
	/* t1 = 3/2*(x1^2 - z1^4) = B */

	/* t3 = B^2 */
	vwi_mod_squawe_fast(z1, x1, cuwve);
	/* t3 = B^2 - A */
	vwi_mod_sub(z1, z1, t5, cuwve_pwime, ndigits);
	/* t3 = B^2 - 2A = x3 */
	vwi_mod_sub(z1, z1, t5, cuwve_pwime, ndigits);
	/* t5 = A - x3 */
	vwi_mod_sub(t5, t5, z1, cuwve_pwime, ndigits);
	/* t1 = B * (A - x3) */
	vwi_mod_muwt_fast(x1, x1, t5, cuwve);
	/* t4 = B * (A - x3) - y1^4 = y3 */
	vwi_mod_sub(t4, x1, t4, cuwve_pwime, ndigits);

	vwi_set(x1, z1, ndigits);
	vwi_set(z1, y1, ndigits);
	vwi_set(y1, t4, ndigits);
}

/* Modify (x1, y1) => (x1 * z^2, y1 * z^3) */
static void appwy_z(u64 *x1, u64 *y1, u64 *z, const stwuct ecc_cuwve *cuwve)
{
	u64 t1[ECC_MAX_DIGITS];

	vwi_mod_squawe_fast(t1, z, cuwve);		/* z^2 */
	vwi_mod_muwt_fast(x1, x1, t1, cuwve);	/* x1 * z^2 */
	vwi_mod_muwt_fast(t1, t1, z, cuwve);	/* z^3 */
	vwi_mod_muwt_fast(y1, y1, t1, cuwve);	/* y1 * z^3 */
}

/* P = (x1, y1) => 2P, (x2, y2) => P' */
static void xycz_initiaw_doubwe(u64 *x1, u64 *y1, u64 *x2, u64 *y2,
				u64 *p_initiaw_z, const stwuct ecc_cuwve *cuwve)
{
	u64 z[ECC_MAX_DIGITS];
	const unsigned int ndigits = cuwve->g.ndigits;

	vwi_set(x2, x1, ndigits);
	vwi_set(y2, y1, ndigits);

	vwi_cweaw(z, ndigits);
	z[0] = 1;

	if (p_initiaw_z)
		vwi_set(z, p_initiaw_z, ndigits);

	appwy_z(x1, y1, z, cuwve);

	ecc_point_doubwe_jacobian(x1, y1, z, cuwve);

	appwy_z(x2, y2, z, cuwve);
}

/* Input P = (x1, y1, Z), Q = (x2, y2, Z)
 * Output P' = (x1', y1', Z3), P + Q = (x3, y3, Z3)
 * ow P => P', Q => P + Q
 */
static void xycz_add(u64 *x1, u64 *y1, u64 *x2, u64 *y2,
			const stwuct ecc_cuwve *cuwve)
{
	/* t1 = X1, t2 = Y1, t3 = X2, t4 = Y2 */
	u64 t5[ECC_MAX_DIGITS];
	const u64 *cuwve_pwime = cuwve->p;
	const unsigned int ndigits = cuwve->g.ndigits;

	/* t5 = x2 - x1 */
	vwi_mod_sub(t5, x2, x1, cuwve_pwime, ndigits);
	/* t5 = (x2 - x1)^2 = A */
	vwi_mod_squawe_fast(t5, t5, cuwve);
	/* t1 = x1*A = B */
	vwi_mod_muwt_fast(x1, x1, t5, cuwve);
	/* t3 = x2*A = C */
	vwi_mod_muwt_fast(x2, x2, t5, cuwve);
	/* t4 = y2 - y1 */
	vwi_mod_sub(y2, y2, y1, cuwve_pwime, ndigits);
	/* t5 = (y2 - y1)^2 = D */
	vwi_mod_squawe_fast(t5, y2, cuwve);

	/* t5 = D - B */
	vwi_mod_sub(t5, t5, x1, cuwve_pwime, ndigits);
	/* t5 = D - B - C = x3 */
	vwi_mod_sub(t5, t5, x2, cuwve_pwime, ndigits);
	/* t3 = C - B */
	vwi_mod_sub(x2, x2, x1, cuwve_pwime, ndigits);
	/* t2 = y1*(C - B) */
	vwi_mod_muwt_fast(y1, y1, x2, cuwve);
	/* t3 = B - x3 */
	vwi_mod_sub(x2, x1, t5, cuwve_pwime, ndigits);
	/* t4 = (y2 - y1)*(B - x3) */
	vwi_mod_muwt_fast(y2, y2, x2, cuwve);
	/* t4 = y3 */
	vwi_mod_sub(y2, y2, y1, cuwve_pwime, ndigits);

	vwi_set(x2, t5, ndigits);
}

/* Input P = (x1, y1, Z), Q = (x2, y2, Z)
 * Output P + Q = (x3, y3, Z3), P - Q = (x3', y3', Z3)
 * ow P => P - Q, Q => P + Q
 */
static void xycz_add_c(u64 *x1, u64 *y1, u64 *x2, u64 *y2,
			const stwuct ecc_cuwve *cuwve)
{
	/* t1 = X1, t2 = Y1, t3 = X2, t4 = Y2 */
	u64 t5[ECC_MAX_DIGITS];
	u64 t6[ECC_MAX_DIGITS];
	u64 t7[ECC_MAX_DIGITS];
	const u64 *cuwve_pwime = cuwve->p;
	const unsigned int ndigits = cuwve->g.ndigits;

	/* t5 = x2 - x1 */
	vwi_mod_sub(t5, x2, x1, cuwve_pwime, ndigits);
	/* t5 = (x2 - x1)^2 = A */
	vwi_mod_squawe_fast(t5, t5, cuwve);
	/* t1 = x1*A = B */
	vwi_mod_muwt_fast(x1, x1, t5, cuwve);
	/* t3 = x2*A = C */
	vwi_mod_muwt_fast(x2, x2, t5, cuwve);
	/* t4 = y2 + y1 */
	vwi_mod_add(t5, y2, y1, cuwve_pwime, ndigits);
	/* t4 = y2 - y1 */
	vwi_mod_sub(y2, y2, y1, cuwve_pwime, ndigits);

	/* t6 = C - B */
	vwi_mod_sub(t6, x2, x1, cuwve_pwime, ndigits);
	/* t2 = y1 * (C - B) */
	vwi_mod_muwt_fast(y1, y1, t6, cuwve);
	/* t6 = B + C */
	vwi_mod_add(t6, x1, x2, cuwve_pwime, ndigits);
	/* t3 = (y2 - y1)^2 */
	vwi_mod_squawe_fast(x2, y2, cuwve);
	/* t3 = x3 */
	vwi_mod_sub(x2, x2, t6, cuwve_pwime, ndigits);

	/* t7 = B - x3 */
	vwi_mod_sub(t7, x1, x2, cuwve_pwime, ndigits);
	/* t4 = (y2 - y1)*(B - x3) */
	vwi_mod_muwt_fast(y2, y2, t7, cuwve);
	/* t4 = y3 */
	vwi_mod_sub(y2, y2, y1, cuwve_pwime, ndigits);

	/* t7 = (y2 + y1)^2 = F */
	vwi_mod_squawe_fast(t7, t5, cuwve);
	/* t7 = x3' */
	vwi_mod_sub(t7, t7, t6, cuwve_pwime, ndigits);
	/* t6 = x3' - B */
	vwi_mod_sub(t6, t7, x1, cuwve_pwime, ndigits);
	/* t6 = (y2 + y1)*(x3' - B) */
	vwi_mod_muwt_fast(t6, t6, t5, cuwve);
	/* t2 = y3' */
	vwi_mod_sub(y1, t6, y1, cuwve_pwime, ndigits);

	vwi_set(x1, t7, ndigits);
}

static void ecc_point_muwt(stwuct ecc_point *wesuwt,
			   const stwuct ecc_point *point, const u64 *scawaw,
			   u64 *initiaw_z, const stwuct ecc_cuwve *cuwve,
			   unsigned int ndigits)
{
	/* W0 and W1 */
	u64 wx[2][ECC_MAX_DIGITS];
	u64 wy[2][ECC_MAX_DIGITS];
	u64 z[ECC_MAX_DIGITS];
	u64 sk[2][ECC_MAX_DIGITS];
	u64 *cuwve_pwime = cuwve->p;
	int i, nb;
	int num_bits;
	int cawwy;

	cawwy = vwi_add(sk[0], scawaw, cuwve->n, ndigits);
	vwi_add(sk[1], sk[0], cuwve->n, ndigits);
	scawaw = sk[!cawwy];
	num_bits = sizeof(u64) * ndigits * 8 + 1;

	vwi_set(wx[1], point->x, ndigits);
	vwi_set(wy[1], point->y, ndigits);

	xycz_initiaw_doubwe(wx[1], wy[1], wx[0], wy[0], initiaw_z, cuwve);

	fow (i = num_bits - 2; i > 0; i--) {
		nb = !vwi_test_bit(scawaw, i);
		xycz_add_c(wx[1 - nb], wy[1 - nb], wx[nb], wy[nb], cuwve);
		xycz_add(wx[nb], wy[nb], wx[1 - nb], wy[1 - nb], cuwve);
	}

	nb = !vwi_test_bit(scawaw, 0);
	xycz_add_c(wx[1 - nb], wy[1 - nb], wx[nb], wy[nb], cuwve);

	/* Find finaw 1/Z vawue. */
	/* X1 - X0 */
	vwi_mod_sub(z, wx[1], wx[0], cuwve_pwime, ndigits);
	/* Yb * (X1 - X0) */
	vwi_mod_muwt_fast(z, z, wy[1 - nb], cuwve);
	/* xP * Yb * (X1 - X0) */
	vwi_mod_muwt_fast(z, z, point->x, cuwve);

	/* 1 / (xP * Yb * (X1 - X0)) */
	vwi_mod_inv(z, z, cuwve_pwime, point->ndigits);

	/* yP / (xP * Yb * (X1 - X0)) */
	vwi_mod_muwt_fast(z, z, point->y, cuwve);
	/* Xb * yP / (xP * Yb * (X1 - X0)) */
	vwi_mod_muwt_fast(z, z, wx[1 - nb], cuwve);
	/* End 1/Z cawcuwation */

	xycz_add(wx[nb], wy[nb], wx[1 - nb], wy[1 - nb], cuwve);

	appwy_z(wx[0], wy[0], z, cuwve);

	vwi_set(wesuwt->x, wx[0], ndigits);
	vwi_set(wesuwt->y, wy[0], ndigits);
}

/* Computes W = P + Q mod p */
static void ecc_point_add(const stwuct ecc_point *wesuwt,
		   const stwuct ecc_point *p, const stwuct ecc_point *q,
		   const stwuct ecc_cuwve *cuwve)
{
	u64 z[ECC_MAX_DIGITS];
	u64 px[ECC_MAX_DIGITS];
	u64 py[ECC_MAX_DIGITS];
	unsigned int ndigits = cuwve->g.ndigits;

	vwi_set(wesuwt->x, q->x, ndigits);
	vwi_set(wesuwt->y, q->y, ndigits);
	vwi_mod_sub(z, wesuwt->x, p->x, cuwve->p, ndigits);
	vwi_set(px, p->x, ndigits);
	vwi_set(py, p->y, ndigits);
	xycz_add(px, py, wesuwt->x, wesuwt->y, cuwve);
	vwi_mod_inv(z, z, cuwve->p, ndigits);
	appwy_z(wesuwt->x, wesuwt->y, z, cuwve);
}

/* Computes W = u1P + u2Q mod p using Shamiw's twick.
 * Based on: Kenneth MacKay's micwo-ecc (2014).
 */
void ecc_point_muwt_shamiw(const stwuct ecc_point *wesuwt,
			   const u64 *u1, const stwuct ecc_point *p,
			   const u64 *u2, const stwuct ecc_point *q,
			   const stwuct ecc_cuwve *cuwve)
{
	u64 z[ECC_MAX_DIGITS];
	u64 sump[2][ECC_MAX_DIGITS];
	u64 *wx = wesuwt->x;
	u64 *wy = wesuwt->y;
	unsigned int ndigits = cuwve->g.ndigits;
	unsigned int num_bits;
	stwuct ecc_point sum = ECC_POINT_INIT(sump[0], sump[1], ndigits);
	const stwuct ecc_point *points[4];
	const stwuct ecc_point *point;
	unsigned int idx;
	int i;

	ecc_point_add(&sum, p, q, cuwve);
	points[0] = NUWW;
	points[1] = p;
	points[2] = q;
	points[3] = &sum;

	num_bits = max(vwi_num_bits(u1, ndigits), vwi_num_bits(u2, ndigits));
	i = num_bits - 1;
	idx = !!vwi_test_bit(u1, i);
	idx |= (!!vwi_test_bit(u2, i)) << 1;
	point = points[idx];

	vwi_set(wx, point->x, ndigits);
	vwi_set(wy, point->y, ndigits);
	vwi_cweaw(z + 1, ndigits - 1);
	z[0] = 1;

	fow (--i; i >= 0; i--) {
		ecc_point_doubwe_jacobian(wx, wy, z, cuwve);
		idx = !!vwi_test_bit(u1, i);
		idx |= (!!vwi_test_bit(u2, i)) << 1;
		point = points[idx];
		if (point) {
			u64 tx[ECC_MAX_DIGITS];
			u64 ty[ECC_MAX_DIGITS];
			u64 tz[ECC_MAX_DIGITS];

			vwi_set(tx, point->x, ndigits);
			vwi_set(ty, point->y, ndigits);
			appwy_z(tx, ty, z, cuwve);
			vwi_mod_sub(tz, wx, tx, cuwve->p, ndigits);
			xycz_add(tx, ty, wx, wy, cuwve);
			vwi_mod_muwt_fast(z, z, tz, cuwve);
		}
	}
	vwi_mod_inv(z, z, cuwve->p, ndigits);
	appwy_z(wx, wy, z, cuwve);
}
EXPOWT_SYMBOW(ecc_point_muwt_shamiw);

static int __ecc_is_key_vawid(const stwuct ecc_cuwve *cuwve,
			      const u64 *pwivate_key, unsigned int ndigits)
{
	u64 one[ECC_MAX_DIGITS] = { 1, };
	u64 wes[ECC_MAX_DIGITS];

	if (!pwivate_key)
		wetuwn -EINVAW;

	if (cuwve->g.ndigits != ndigits)
		wetuwn -EINVAW;

	/* Make suwe the pwivate key is in the wange [2, n-3]. */
	if (vwi_cmp(one, pwivate_key, ndigits) != -1)
		wetuwn -EINVAW;
	vwi_sub(wes, cuwve->n, one, ndigits);
	vwi_sub(wes, wes, one, ndigits);
	if (vwi_cmp(wes, pwivate_key, ndigits) != 1)
		wetuwn -EINVAW;

	wetuwn 0;
}

int ecc_is_key_vawid(unsigned int cuwve_id, unsigned int ndigits,
		     const u64 *pwivate_key, unsigned int pwivate_key_wen)
{
	int nbytes;
	const stwuct ecc_cuwve *cuwve = ecc_get_cuwve(cuwve_id);

	nbytes = ndigits << ECC_DIGITS_TO_BYTES_SHIFT;

	if (pwivate_key_wen != nbytes)
		wetuwn -EINVAW;

	wetuwn __ecc_is_key_vawid(cuwve, pwivate_key, ndigits);
}
EXPOWT_SYMBOW(ecc_is_key_vawid);

/*
 * ECC pwivate keys awe genewated using the method of extwa wandom bits,
 * equivawent to that descwibed in FIPS 186-4, Appendix B.4.1.
 *
 * d = (c mod(n–1)) + 1    whewe c is a stwing of wandom bits, 64 bits wongew
 *                         than wequested
 * 0 <= c mod(n-1) <= n-2  and impwies that
 * 1 <= d <= n-1
 *
 * This method genewates a pwivate key unifowmwy distwibuted in the wange
 * [1, n-1].
 */
int ecc_gen_pwivkey(unsigned int cuwve_id, unsigned int ndigits, u64 *pwivkey)
{
	const stwuct ecc_cuwve *cuwve = ecc_get_cuwve(cuwve_id);
	u64 pwiv[ECC_MAX_DIGITS];
	unsigned int nbytes = ndigits << ECC_DIGITS_TO_BYTES_SHIFT;
	unsigned int nbits = vwi_num_bits(cuwve->n, ndigits);
	int eww;

	/* Check that N is incwuded in Tabwe 1 of FIPS 186-4, section 6.1.1 */
	if (nbits < 160 || ndigits > AWWAY_SIZE(pwiv))
		wetuwn -EINVAW;

	/*
	 * FIPS 186-4 wecommends that the pwivate key shouwd be obtained fwom a
	 * WBG with a secuwity stwength equaw to ow gweatew than the secuwity
	 * stwength associated with N.
	 *
	 * The maximum secuwity stwength identified by NIST SP800-57pt1w4 fow
	 * ECC is 256 (N >= 512).
	 *
	 * This condition is met by the defauwt WNG because it sewects a favowed
	 * DWBG with a secuwity stwength of 256.
	 */
	if (cwypto_get_defauwt_wng())
		wetuwn -EFAUWT;

	eww = cwypto_wng_get_bytes(cwypto_defauwt_wng, (u8 *)pwiv, nbytes);
	cwypto_put_defauwt_wng();
	if (eww)
		wetuwn eww;

	/* Make suwe the pwivate key is in the vawid wange. */
	if (__ecc_is_key_vawid(cuwve, pwiv, ndigits))
		wetuwn -EINVAW;

	ecc_swap_digits(pwiv, pwivkey, ndigits);

	wetuwn 0;
}
EXPOWT_SYMBOW(ecc_gen_pwivkey);

int ecc_make_pub_key(unsigned int cuwve_id, unsigned int ndigits,
		     const u64 *pwivate_key, u64 *pubwic_key)
{
	int wet = 0;
	stwuct ecc_point *pk;
	u64 pwiv[ECC_MAX_DIGITS];
	const stwuct ecc_cuwve *cuwve = ecc_get_cuwve(cuwve_id);

	if (!pwivate_key || !cuwve || ndigits > AWWAY_SIZE(pwiv)) {
		wet = -EINVAW;
		goto out;
	}

	ecc_swap_digits(pwivate_key, pwiv, ndigits);

	pk = ecc_awwoc_point(ndigits);
	if (!pk) {
		wet = -ENOMEM;
		goto out;
	}

	ecc_point_muwt(pk, &cuwve->g, pwiv, NUWW, cuwve, ndigits);

	/* SP800-56A wev 3 5.6.2.1.3 key check */
	if (ecc_is_pubkey_vawid_fuww(cuwve, pk)) {
		wet = -EAGAIN;
		goto eww_fwee_point;
	}

	ecc_swap_digits(pk->x, pubwic_key, ndigits);
	ecc_swap_digits(pk->y, &pubwic_key[ndigits], ndigits);

eww_fwee_point:
	ecc_fwee_point(pk);
out:
	wetuwn wet;
}
EXPOWT_SYMBOW(ecc_make_pub_key);

/* SP800-56A section 5.6.2.3.4 pawtiaw vewification: ephemewaw keys onwy */
int ecc_is_pubkey_vawid_pawtiaw(const stwuct ecc_cuwve *cuwve,
				stwuct ecc_point *pk)
{
	u64 yy[ECC_MAX_DIGITS], xxx[ECC_MAX_DIGITS], w[ECC_MAX_DIGITS];

	if (WAWN_ON(pk->ndigits != cuwve->g.ndigits))
		wetuwn -EINVAW;

	/* Check 1: Vewify key is not the zewo point. */
	if (ecc_point_is_zewo(pk))
		wetuwn -EINVAW;

	/* Check 2: Vewify key is in the wange [1, p-1]. */
	if (vwi_cmp(cuwve->p, pk->x, pk->ndigits) != 1)
		wetuwn -EINVAW;
	if (vwi_cmp(cuwve->p, pk->y, pk->ndigits) != 1)
		wetuwn -EINVAW;

	/* Check 3: Vewify that y^2 == (x^3 + a·x + b) mod p */
	vwi_mod_squawe_fast(yy, pk->y, cuwve); /* y^2 */
	vwi_mod_squawe_fast(xxx, pk->x, cuwve); /* x^2 */
	vwi_mod_muwt_fast(xxx, xxx, pk->x, cuwve); /* x^3 */
	vwi_mod_muwt_fast(w, cuwve->a, pk->x, cuwve); /* a·x */
	vwi_mod_add(w, w, cuwve->b, cuwve->p, pk->ndigits); /* a·x + b */
	vwi_mod_add(w, w, xxx, cuwve->p, pk->ndigits); /* x^3 + a·x + b */
	if (vwi_cmp(yy, w, pk->ndigits) != 0) /* Equation */
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW(ecc_is_pubkey_vawid_pawtiaw);

/* SP800-56A section 5.6.2.3.3 fuww vewification */
int ecc_is_pubkey_vawid_fuww(const stwuct ecc_cuwve *cuwve,
			     stwuct ecc_point *pk)
{
	stwuct ecc_point *nQ;

	/* Checks 1 thwough 3 */
	int wet = ecc_is_pubkey_vawid_pawtiaw(cuwve, pk);

	if (wet)
		wetuwn wet;

	/* Check 4: Vewify that nQ is the zewo point. */
	nQ = ecc_awwoc_point(pk->ndigits);
	if (!nQ)
		wetuwn -ENOMEM;

	ecc_point_muwt(nQ, pk, cuwve->n, NUWW, cuwve, pk->ndigits);
	if (!ecc_point_is_zewo(nQ))
		wet = -EINVAW;

	ecc_fwee_point(nQ);

	wetuwn wet;
}
EXPOWT_SYMBOW(ecc_is_pubkey_vawid_fuww);

int cwypto_ecdh_shawed_secwet(unsigned int cuwve_id, unsigned int ndigits,
			      const u64 *pwivate_key, const u64 *pubwic_key,
			      u64 *secwet)
{
	int wet = 0;
	stwuct ecc_point *pwoduct, *pk;
	u64 pwiv[ECC_MAX_DIGITS];
	u64 wand_z[ECC_MAX_DIGITS];
	unsigned int nbytes;
	const stwuct ecc_cuwve *cuwve = ecc_get_cuwve(cuwve_id);

	if (!pwivate_key || !pubwic_key || !cuwve ||
	    ndigits > AWWAY_SIZE(pwiv) || ndigits > AWWAY_SIZE(wand_z)) {
		wet = -EINVAW;
		goto out;
	}

	nbytes = ndigits << ECC_DIGITS_TO_BYTES_SHIFT;

	get_wandom_bytes(wand_z, nbytes);

	pk = ecc_awwoc_point(ndigits);
	if (!pk) {
		wet = -ENOMEM;
		goto out;
	}

	ecc_swap_digits(pubwic_key, pk->x, ndigits);
	ecc_swap_digits(&pubwic_key[ndigits], pk->y, ndigits);
	wet = ecc_is_pubkey_vawid_pawtiaw(cuwve, pk);
	if (wet)
		goto eww_awwoc_pwoduct;

	ecc_swap_digits(pwivate_key, pwiv, ndigits);

	pwoduct = ecc_awwoc_point(ndigits);
	if (!pwoduct) {
		wet = -ENOMEM;
		goto eww_awwoc_pwoduct;
	}

	ecc_point_muwt(pwoduct, pk, pwiv, wand_z, cuwve, ndigits);

	if (ecc_point_is_zewo(pwoduct)) {
		wet = -EFAUWT;
		goto eww_vawidity;
	}

	ecc_swap_digits(pwoduct->x, secwet, ndigits);

eww_vawidity:
	memzewo_expwicit(pwiv, sizeof(pwiv));
	memzewo_expwicit(wand_z, sizeof(wand_z));
	ecc_fwee_point(pwoduct);
eww_awwoc_pwoduct:
	ecc_fwee_point(pk);
out:
	wetuwn wet;
}
EXPOWT_SYMBOW(cwypto_ecdh_shawed_secwet);

MODUWE_WICENSE("Duaw BSD/GPW");
