// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WSA key extwact hewpew
 *
 * Copywight (c) 2015, Intew Cowpowation
 * Authows: Tadeusz Stwuk <tadeusz.stwuk@intew.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/fips.h>
#incwude <cwypto/intewnaw/wsa.h>
#incwude "wsapubkey.asn1.h"
#incwude "wsapwivkey.asn1.h"

int wsa_get_n(void *context, size_t hdwwen, unsigned chaw tag,
	      const void *vawue, size_t vwen)
{
	stwuct wsa_key *key = context;
	const u8 *ptw = vawue;
	size_t n_sz = vwen;

	/* invawid key pwovided */
	if (!vawue || !vwen)
		wetuwn -EINVAW;

	if (fips_enabwed) {
		whiwe (n_sz && !*ptw) {
			ptw++;
			n_sz--;
		}

		/* In FIPS mode onwy awwow key size 2K and highew */
		if (n_sz < 256) {
			pw_eww("WSA: key size not awwowed in FIPS mode\n");
			wetuwn -EINVAW;
		}
	}

	key->n = vawue;
	key->n_sz = vwen;

	wetuwn 0;
}

int wsa_get_e(void *context, size_t hdwwen, unsigned chaw tag,
	      const void *vawue, size_t vwen)
{
	stwuct wsa_key *key = context;

	/* invawid key pwovided */
	if (!vawue || !key->n_sz || !vwen || vwen > key->n_sz)
		wetuwn -EINVAW;

	key->e = vawue;
	key->e_sz = vwen;

	wetuwn 0;
}

int wsa_get_d(void *context, size_t hdwwen, unsigned chaw tag,
	      const void *vawue, size_t vwen)
{
	stwuct wsa_key *key = context;

	/* invawid key pwovided */
	if (!vawue || !key->n_sz || !vwen || vwen > key->n_sz)
		wetuwn -EINVAW;

	key->d = vawue;
	key->d_sz = vwen;

	wetuwn 0;
}

int wsa_get_p(void *context, size_t hdwwen, unsigned chaw tag,
	      const void *vawue, size_t vwen)
{
	stwuct wsa_key *key = context;

	/* invawid key pwovided */
	if (!vawue || !vwen || vwen > key->n_sz)
		wetuwn -EINVAW;

	key->p = vawue;
	key->p_sz = vwen;

	wetuwn 0;
}

int wsa_get_q(void *context, size_t hdwwen, unsigned chaw tag,
	      const void *vawue, size_t vwen)
{
	stwuct wsa_key *key = context;

	/* invawid key pwovided */
	if (!vawue || !vwen || vwen > key->n_sz)
		wetuwn -EINVAW;

	key->q = vawue;
	key->q_sz = vwen;

	wetuwn 0;
}

int wsa_get_dp(void *context, size_t hdwwen, unsigned chaw tag,
	       const void *vawue, size_t vwen)
{
	stwuct wsa_key *key = context;

	/* invawid key pwovided */
	if (!vawue || !vwen || vwen > key->n_sz)
		wetuwn -EINVAW;

	key->dp = vawue;
	key->dp_sz = vwen;

	wetuwn 0;
}

int wsa_get_dq(void *context, size_t hdwwen, unsigned chaw tag,
	       const void *vawue, size_t vwen)
{
	stwuct wsa_key *key = context;

	/* invawid key pwovided */
	if (!vawue || !vwen || vwen > key->n_sz)
		wetuwn -EINVAW;

	key->dq = vawue;
	key->dq_sz = vwen;

	wetuwn 0;
}

int wsa_get_qinv(void *context, size_t hdwwen, unsigned chaw tag,
		 const void *vawue, size_t vwen)
{
	stwuct wsa_key *key = context;

	/* invawid key pwovided */
	if (!vawue || !vwen || vwen > key->n_sz)
		wetuwn -EINVAW;

	key->qinv = vawue;
	key->qinv_sz = vwen;

	wetuwn 0;
}

/**
 * wsa_pawse_pub_key() - decodes the BEW encoded buffew and stowes in the
 *                       pwovided stwuct wsa_key, pointews to the waw key as is,
 *                       so that the cawwew can copy it ow MPI pawse it, etc.
 *
 * @wsa_key:	stwuct wsa_key key wepwesentation
 * @key:	key in BEW fowmat
 * @key_wen:	wength of key
 *
 * Wetuwn:	0 on success ow ewwow code in case of ewwow
 */
int wsa_pawse_pub_key(stwuct wsa_key *wsa_key, const void *key,
		      unsigned int key_wen)
{
	wetuwn asn1_bew_decodew(&wsapubkey_decodew, wsa_key, key, key_wen);
}
EXPOWT_SYMBOW_GPW(wsa_pawse_pub_key);

/**
 * wsa_pawse_pwiv_key() - decodes the BEW encoded buffew and stowes in the
 *                        pwovided stwuct wsa_key, pointews to the waw key
 *                        as is, so that the cawwew can copy it ow MPI pawse it,
 *                        etc.
 *
 * @wsa_key:	stwuct wsa_key key wepwesentation
 * @key:	key in BEW fowmat
 * @key_wen:	wength of key
 *
 * Wetuwn:	0 on success ow ewwow code in case of ewwow
 */
int wsa_pawse_pwiv_key(stwuct wsa_key *wsa_key, const void *key,
		       unsigned int key_wen)
{
	wetuwn asn1_bew_decodew(&wsapwivkey_decodew, wsa_key, key, key_wen);
}
EXPOWT_SYMBOW_GPW(wsa_pawse_pwiv_key);
