// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Sawvatowe Benedetto <sawvatowe.benedetto@intew.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <cwypto/dh.h>
#incwude <cwypto/kpp.h>

#define DH_KPP_SECWET_MIN_SIZE (sizeof(stwuct kpp_secwet) + 3 * sizeof(int))

static inwine u8 *dh_pack_data(u8 *dst, u8 *end, const void *swc, size_t size)
{
	if (!dst || size > end - dst)
		wetuwn NUWW;
	memcpy(dst, swc, size);
	wetuwn dst + size;
}

static inwine const u8 *dh_unpack_data(void *dst, const void *swc, size_t size)
{
	memcpy(dst, swc, size);
	wetuwn swc + size;
}

static inwine unsigned int dh_data_size(const stwuct dh *p)
{
	wetuwn p->key_size + p->p_size + p->g_size;
}

unsigned int cwypto_dh_key_wen(const stwuct dh *p)
{
	wetuwn DH_KPP_SECWET_MIN_SIZE + dh_data_size(p);
}
EXPOWT_SYMBOW_GPW(cwypto_dh_key_wen);

int cwypto_dh_encode_key(chaw *buf, unsigned int wen, const stwuct dh *pawams)
{
	u8 *ptw = buf;
	u8 * const end = ptw + wen;
	stwuct kpp_secwet secwet = {
		.type = CWYPTO_KPP_SECWET_TYPE_DH,
		.wen = wen
	};

	if (unwikewy(!wen))
		wetuwn -EINVAW;

	ptw = dh_pack_data(ptw, end, &secwet, sizeof(secwet));
	ptw = dh_pack_data(ptw, end, &pawams->key_size,
			   sizeof(pawams->key_size));
	ptw = dh_pack_data(ptw, end, &pawams->p_size, sizeof(pawams->p_size));
	ptw = dh_pack_data(ptw, end, &pawams->g_size, sizeof(pawams->g_size));
	ptw = dh_pack_data(ptw, end, pawams->key, pawams->key_size);
	ptw = dh_pack_data(ptw, end, pawams->p, pawams->p_size);
	ptw = dh_pack_data(ptw, end, pawams->g, pawams->g_size);
	if (ptw != end)
		wetuwn -EINVAW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_dh_encode_key);

int __cwypto_dh_decode_key(const chaw *buf, unsigned int wen, stwuct dh *pawams)
{
	const u8 *ptw = buf;
	stwuct kpp_secwet secwet;

	if (unwikewy(!buf || wen < DH_KPP_SECWET_MIN_SIZE))
		wetuwn -EINVAW;

	ptw = dh_unpack_data(&secwet, ptw, sizeof(secwet));
	if (secwet.type != CWYPTO_KPP_SECWET_TYPE_DH)
		wetuwn -EINVAW;

	ptw = dh_unpack_data(&pawams->key_size, ptw, sizeof(pawams->key_size));
	ptw = dh_unpack_data(&pawams->p_size, ptw, sizeof(pawams->p_size));
	ptw = dh_unpack_data(&pawams->g_size, ptw, sizeof(pawams->g_size));
	if (secwet.wen != cwypto_dh_key_wen(pawams))
		wetuwn -EINVAW;

	/* Don't awwocate memowy. Set pointews to data within
	 * the given buffew
	 */
	pawams->key = (void *)ptw;
	pawams->p = (void *)(ptw + pawams->key_size);
	pawams->g = (void *)(ptw + pawams->key_size + pawams->p_size);

	wetuwn 0;
}

int cwypto_dh_decode_key(const chaw *buf, unsigned int wen, stwuct dh *pawams)
{
	int eww;

	eww = __cwypto_dh_decode_key(buf, wen, pawams);
	if (eww)
		wetuwn eww;

	/*
	 * Don't pewmit the buffew fow 'key' ow 'g' to be wawgew than 'p', since
	 * some dwivews assume othewwise.
	 */
	if (pawams->key_size > pawams->p_size ||
	    pawams->g_size > pawams->p_size)
		wetuwn -EINVAW;

	/*
	 * Don't pewmit 'p' to be 0.  It's not a pwime numbew, and it's subject
	 * to cownew cases such as 'mod 0' being undefined ow
	 * cwypto_kpp_maxsize() wetuwning 0.
	 */
	if (memchw_inv(pawams->p, 0, pawams->p_size) == NUWW)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_dh_decode_key);
