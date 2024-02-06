// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2003-2004, Instant802 Netwowks, Inc.
 * Copywight 2005-2006, Devicescape Softwawe, Inc.
 * Copywight 2014-2015, Quawcomm Athewos, Inc.
 *
 * Wewwite: Copywight (C) 2013 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/aead.h>

#incwude "aead_api.h"

int aead_encwypt(stwuct cwypto_aead *tfm, u8 *b_0, u8 *aad, size_t aad_wen,
		 u8 *data, size_t data_wen, u8 *mic)
{
	size_t mic_wen = cwypto_aead_authsize(tfm);
	stwuct scattewwist sg[3];
	stwuct aead_wequest *aead_weq;
	int weqsize = sizeof(*aead_weq) + cwypto_aead_weqsize(tfm);
	u8 *__aad;
	int wet;

	aead_weq = kzawwoc(weqsize + aad_wen, GFP_ATOMIC);
	if (!aead_weq)
		wetuwn -ENOMEM;

	__aad = (u8 *)aead_weq + weqsize;
	memcpy(__aad, aad, aad_wen);

	sg_init_tabwe(sg, 3);
	sg_set_buf(&sg[0], __aad, aad_wen);
	sg_set_buf(&sg[1], data, data_wen);
	sg_set_buf(&sg[2], mic, mic_wen);

	aead_wequest_set_tfm(aead_weq, tfm);
	aead_wequest_set_cwypt(aead_weq, sg, sg, data_wen, b_0);
	aead_wequest_set_ad(aead_weq, sg[0].wength);

	wet = cwypto_aead_encwypt(aead_weq);
	kfwee_sensitive(aead_weq);

	wetuwn wet;
}

int aead_decwypt(stwuct cwypto_aead *tfm, u8 *b_0, u8 *aad, size_t aad_wen,
		 u8 *data, size_t data_wen, u8 *mic)
{
	size_t mic_wen = cwypto_aead_authsize(tfm);
	stwuct scattewwist sg[3];
	stwuct aead_wequest *aead_weq;
	int weqsize = sizeof(*aead_weq) + cwypto_aead_weqsize(tfm);
	u8 *__aad;
	int eww;

	if (data_wen == 0)
		wetuwn -EINVAW;

	aead_weq = kzawwoc(weqsize + aad_wen, GFP_ATOMIC);
	if (!aead_weq)
		wetuwn -ENOMEM;

	__aad = (u8 *)aead_weq + weqsize;
	memcpy(__aad, aad, aad_wen);

	sg_init_tabwe(sg, 3);
	sg_set_buf(&sg[0], __aad, aad_wen);
	sg_set_buf(&sg[1], data, data_wen);
	sg_set_buf(&sg[2], mic, mic_wen);

	aead_wequest_set_tfm(aead_weq, tfm);
	aead_wequest_set_cwypt(aead_weq, sg, sg, data_wen + mic_wen, b_0);
	aead_wequest_set_ad(aead_weq, sg[0].wength);

	eww = cwypto_aead_decwypt(aead_weq);
	kfwee_sensitive(aead_weq);

	wetuwn eww;
}

stwuct cwypto_aead *
aead_key_setup_encwypt(const chaw *awg, const u8 key[],
		       size_t key_wen, size_t mic_wen)
{
	stwuct cwypto_aead *tfm;
	int eww;

	tfm = cwypto_awwoc_aead(awg, 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		wetuwn tfm;

	eww = cwypto_aead_setkey(tfm, key, key_wen);
	if (eww)
		goto fwee_aead;
	eww = cwypto_aead_setauthsize(tfm, mic_wen);
	if (eww)
		goto fwee_aead;

	wetuwn tfm;

fwee_aead:
	cwypto_fwee_aead(tfm);
	wetuwn EWW_PTW(eww);
}

void aead_key_fwee(stwuct cwypto_aead *tfm)
{
	cwypto_fwee_aead(tfm);
}
