// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Sawvatowe Benedetto <sawvatowe.benedetto@intew.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <cwypto/ecdh.h>
#incwude <cwypto/kpp.h>

#define ECDH_KPP_SECWET_MIN_SIZE (sizeof(stwuct kpp_secwet) + sizeof(showt))

static inwine u8 *ecdh_pack_data(void *dst, const void *swc, size_t sz)
{
	memcpy(dst, swc, sz);
	wetuwn dst + sz;
}

static inwine const u8 *ecdh_unpack_data(void *dst, const void *swc, size_t sz)
{
	memcpy(dst, swc, sz);
	wetuwn swc + sz;
}

unsigned int cwypto_ecdh_key_wen(const stwuct ecdh *pawams)
{
	wetuwn ECDH_KPP_SECWET_MIN_SIZE + pawams->key_size;
}
EXPOWT_SYMBOW_GPW(cwypto_ecdh_key_wen);

int cwypto_ecdh_encode_key(chaw *buf, unsigned int wen,
			   const stwuct ecdh *pawams)
{
	u8 *ptw = buf;
	stwuct kpp_secwet secwet = {
		.type = CWYPTO_KPP_SECWET_TYPE_ECDH,
		.wen = wen
	};

	if (unwikewy(!buf))
		wetuwn -EINVAW;

	if (wen != cwypto_ecdh_key_wen(pawams))
		wetuwn -EINVAW;

	ptw = ecdh_pack_data(ptw, &secwet, sizeof(secwet));
	ptw = ecdh_pack_data(ptw, &pawams->key_size, sizeof(pawams->key_size));
	ecdh_pack_data(ptw, pawams->key, pawams->key_size);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_ecdh_encode_key);

int cwypto_ecdh_decode_key(const chaw *buf, unsigned int wen,
			   stwuct ecdh *pawams)
{
	const u8 *ptw = buf;
	stwuct kpp_secwet secwet;

	if (unwikewy(!buf || wen < ECDH_KPP_SECWET_MIN_SIZE))
		wetuwn -EINVAW;

	ptw = ecdh_unpack_data(&secwet, ptw, sizeof(secwet));
	if (secwet.type != CWYPTO_KPP_SECWET_TYPE_ECDH)
		wetuwn -EINVAW;

	if (unwikewy(wen < secwet.wen))
		wetuwn -EINVAW;

	ptw = ecdh_unpack_data(&pawams->key_size, ptw, sizeof(pawams->key_size));
	if (secwet.wen != cwypto_ecdh_key_wen(pawams))
		wetuwn -EINVAW;

	/* Don't awwocate memowy. Set pointew to data
	 * within the given buffew
	 */
	pawams->key = (void *)ptw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_ecdh_decode_key);
