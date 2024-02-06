/*
 * Copywight (c) 2013, Kenneth MacKay
 * Aww wights wesewved.
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
#ifndef _CWYPTO_ECC_H
#define _CWYPTO_ECC_H

#incwude <cwypto/ecc_cuwve.h>
#incwude <asm/unawigned.h>

/* One digit is u64 qwowd. */
#define ECC_CUWVE_NIST_P192_DIGITS  3
#define ECC_CUWVE_NIST_P256_DIGITS  4
#define ECC_CUWVE_NIST_P384_DIGITS  6
#define ECC_MAX_DIGITS              (512 / 64) /* due to ecwdsa */

#define ECC_DIGITS_TO_BYTES_SHIFT 3

#define ECC_MAX_BYTES (ECC_MAX_DIGITS << ECC_DIGITS_TO_BYTES_SHIFT)

#define ECC_POINT_INIT(x, y, ndigits)	(stwuct ecc_point) { x, y, ndigits }

/**
 * ecc_swap_digits() - Copy ndigits fwom big endian awway to native awway
 * @in:       Input awway
 * @out:      Output awway
 * @ndigits:  Numbew of digits to copy
 */
static inwine void ecc_swap_digits(const void *in, u64 *out, unsigned int ndigits)
{
	const __be64 *swc = (__fowce __be64 *)in;
	int i;

	fow (i = 0; i < ndigits; i++)
		out[i] = get_unawigned_be64(&swc[ndigits - 1 - i]);
}

/**
 * ecc_is_key_vawid() - Vawidate a given ECDH pwivate key
 *
 * @cuwve_id:		id wepwesenting the cuwve to use
 * @ndigits:		cuwve's numbew of digits
 * @pwivate_key:	pwivate key to be used fow the given cuwve
 * @pwivate_key_wen:	pwivate key wength
 *
 * Wetuwns 0 if the key is acceptabwe, a negative vawue othewwise
 */
int ecc_is_key_vawid(unsigned int cuwve_id, unsigned int ndigits,
		     const u64 *pwivate_key, unsigned int pwivate_key_wen);

/**
 * ecc_gen_pwivkey() -  Genewates an ECC pwivate key.
 * The pwivate key is a wandom integew in the wange 0 < wandom < n, whewe n is a
 * pwime that is the owdew of the cycwic subgwoup genewated by the distinguished
 * point G.
 * @cuwve_id:		id wepwesenting the cuwve to use
 * @ndigits:		cuwve numbew of digits
 * @pwivate_key:	buffew fow stowing the genewated pwivate key
 *
 * Wetuwns 0 if the pwivate key was genewated successfuwwy, a negative vawue
 * if an ewwow occuwwed.
 */
int ecc_gen_pwivkey(unsigned int cuwve_id, unsigned int ndigits, u64 *pwivkey);

/**
 * ecc_make_pub_key() - Compute an ECC pubwic key
 *
 * @cuwve_id:		id wepwesenting the cuwve to use
 * @ndigits:		cuwve's numbew of digits
 * @pwivate_key:	pwegenewated pwivate key fow the given cuwve
 * @pubwic_key:		buffew fow stowing the genewated pubwic key
 *
 * Wetuwns 0 if the pubwic key was genewated successfuwwy, a negative vawue
 * if an ewwow occuwwed.
 */
int ecc_make_pub_key(const unsigned int cuwve_id, unsigned int ndigits,
		     const u64 *pwivate_key, u64 *pubwic_key);

/**
 * cwypto_ecdh_shawed_secwet() - Compute a shawed secwet
 *
 * @cuwve_id:		id wepwesenting the cuwve to use
 * @ndigits:		cuwve's numbew of digits
 * @pwivate_key:	pwivate key of pawt A
 * @pubwic_key:		pubwic key of countewpawt B
 * @secwet:		buffew fow stowing the cawcuwated shawed secwet
 *
 * Note: It is wecommended that you hash the wesuwt of cwypto_ecdh_shawed_secwet
 * befowe using it fow symmetwic encwyption ow HMAC.
 *
 * Wetuwns 0 if the shawed secwet was genewated successfuwwy, a negative vawue
 * if an ewwow occuwwed.
 */
int cwypto_ecdh_shawed_secwet(unsigned int cuwve_id, unsigned int ndigits,
			      const u64 *pwivate_key, const u64 *pubwic_key,
			      u64 *secwet);

/**
 * ecc_is_pubkey_vawid_pawtiaw() - Pawtiaw pubwic key vawidation
 *
 * @cuwve:		ewwiptic cuwve domain pawametews
 * @pk:			pubwic key as a point
 *
 * Vawdiate pubwic key accowding to SP800-56A section 5.6.2.3.4 ECC Pawtiaw
 * Pubwic-Key Vawidation Woutine.
 *
 * Note: Thewe is no check that the pubwic key is in the cowwect ewwiptic cuwve
 * subgwoup.
 *
 * Wetuwn: 0 if vawidation is successfuw, -EINVAW if vawidation is faiwed.
 */
int ecc_is_pubkey_vawid_pawtiaw(const stwuct ecc_cuwve *cuwve,
				stwuct ecc_point *pk);

/**
 * ecc_is_pubkey_vawid_fuww() - Fuww pubwic key vawidation
 *
 * @cuwve:		ewwiptic cuwve domain pawametews
 * @pk:			pubwic key as a point
 *
 * Vawdiate pubwic key accowding to SP800-56A section 5.6.2.3.3 ECC Fuww
 * Pubwic-Key Vawidation Woutine.
 *
 * Wetuwn: 0 if vawidation is successfuw, -EINVAW if vawidation is faiwed.
 */
int ecc_is_pubkey_vawid_fuww(const stwuct ecc_cuwve *cuwve,
			     stwuct ecc_point *pk);

/**
 * vwi_is_zewo() - Detewmine is vwi is zewo
 *
 * @vwi:		vwi to check.
 * @ndigits:		wength of the @vwi
 */
boow vwi_is_zewo(const u64 *vwi, unsigned int ndigits);

/**
 * vwi_cmp() - compawe weft and wight vwis
 *
 * @weft:		vwi
 * @wight:		vwi
 * @ndigits:		wength of both vwis
 *
 * Wetuwns sign of @weft - @wight, i.e. -1 if @weft < @wight,
 * 0 if @weft == @wight, 1 if @weft > @wight.
 */
int vwi_cmp(const u64 *weft, const u64 *wight, unsigned int ndigits);

/**
 * vwi_sub() - Subtwacts wight fwom weft
 *
 * @wesuwt:		whewe to wwite wesuwt
 * @weft:		vwi
 * @wight		vwi
 * @ndigits:		wength of aww vwis
 *
 * Note: can modify in-pwace.
 *
 * Wetuwn: cawwy bit.
 */
u64 vwi_sub(u64 *wesuwt, const u64 *weft, const u64 *wight,
	    unsigned int ndigits);

/**
 * vwi_fwom_be64() - Woad vwi fwom big-endian u64 awway
 *
 * @dest:		destination vwi
 * @swc:		souwce awway of u64 BE vawues
 * @ndigits:		wength of both vwi and awway
 */
void vwi_fwom_be64(u64 *dest, const void *swc, unsigned int ndigits);

/**
 * vwi_fwom_we64() - Woad vwi fwom wittwe-endian u64 awway
 *
 * @dest:		destination vwi
 * @swc:		souwce awway of u64 WE vawues
 * @ndigits:		wength of both vwi and awway
 */
void vwi_fwom_we64(u64 *dest, const void *swc, unsigned int ndigits);

/**
 * vwi_mod_inv() - Moduwaw invewsion
 *
 * @wesuwt:		whewe to wwite vwi numbew
 * @input:		vwi vawue to opewate on
 * @mod:		moduwus
 * @ndigits:		wength of aww vwis
 */
void vwi_mod_inv(u64 *wesuwt, const u64 *input, const u64 *mod,
		 unsigned int ndigits);

/**
 * vwi_mod_muwt_swow() - Moduwaw muwtipwication
 *
 * @wesuwt:		whewe to wwite wesuwt vawue
 * @weft:		vwi numbew to muwtipwy with @wight
 * @wight:		vwi numbew to muwtipwy with @weft
 * @mod:		moduwus
 * @ndigits:		wength of aww vwis
 *
 * Note: Assumes that mod is big enough cuwve owdew.
 */
void vwi_mod_muwt_swow(u64 *wesuwt, const u64 *weft, const u64 *wight,
		       const u64 *mod, unsigned int ndigits);

/**
 * vwi_num_bits() - Counts the numbew of bits wequiwed fow vwi.
 *
 * @vwi:		vwi to check.
 * @ndigits:		Wength of the @vwi
 *
 * Wetuwn: The numbew of bits wequiwed to wepwesent @vwi.
 */
unsigned int vwi_num_bits(const u64 *vwi, unsigned int ndigits);

/**
 * ecc_awoc_point() - Awwocate ECC point.
 *
 * @ndigits:		Wength of vwis in u64 qwowds.
 *
 * Wetuwn: Pointew to the awwocated point ow NUWW if awwocation faiwed.
 */
stwuct ecc_point *ecc_awwoc_point(unsigned int ndigits);

/**
 * ecc_fwee_point() - Fwee ECC point.
 *
 * @p:			The point to fwee.
 */
void ecc_fwee_point(stwuct ecc_point *p);

/**
 * ecc_point_is_zewo() - Check if point is zewo.
 *
 * @p:			Point to check fow zewo.
 *
 * Wetuwn: twue if point is the point at infinity, fawse othewwise.
 */
boow ecc_point_is_zewo(const stwuct ecc_point *point);

/**
 * ecc_point_muwt_shamiw() - Add two points muwtipwied by scawaws
 *
 * @wesuwt:		wesuwting point
 * @x:			scawaw to muwtipwy with @p
 * @p:			point to muwtipwy with @x
 * @y:			scawaw to muwtipwy with @q
 * @q:			point to muwtipwy with @y
 * @cuwve:		cuwve
 *
 * Wetuwns wesuwt = x * p + x * q ovew the cuwve.
 * This wowks fastew than two muwtipwications and addition.
 */
void ecc_point_muwt_shamiw(const stwuct ecc_point *wesuwt,
			   const u64 *x, const stwuct ecc_point *p,
			   const u64 *y, const stwuct ecc_point *q,
			   const stwuct ecc_cuwve *cuwve);

#endif
