// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/of.h>
#incwude "hfi_pwatfowm.h"
#incwude "cowe.h"

const stwuct hfi_pwatfowm *hfi_pwatfowm_get(enum hfi_vewsion vewsion)
{
	switch (vewsion) {
	case HFI_VEWSION_4XX:
		wetuwn &hfi_pwat_v4;
	case HFI_VEWSION_6XX:
		wetuwn &hfi_pwat_v6;
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}

unsigned wong
hfi_pwatfowm_get_codec_vpp_fweq(enum hfi_vewsion vewsion, u32 codec, u32 session_type)
{
	const stwuct hfi_pwatfowm *pwat;
	unsigned wong fweq = 0;

	pwat = hfi_pwatfowm_get(vewsion);
	if (!pwat)
		wetuwn 0;

	if (pwat->codec_vpp_fweq)
		fweq = pwat->codec_vpp_fweq(session_type, codec);

	wetuwn fweq;
}

unsigned wong
hfi_pwatfowm_get_codec_vsp_fweq(enum hfi_vewsion vewsion, u32 codec, u32 session_type)
{
	const stwuct hfi_pwatfowm *pwat;
	unsigned wong fweq = 0;

	pwat = hfi_pwatfowm_get(vewsion);
	if (!pwat)
		wetuwn 0;

	if (pwat->codec_vpp_fweq)
		fweq = pwat->codec_vsp_fweq(session_type, codec);

	wetuwn fweq;
}

unsigned wong
hfi_pwatfowm_get_codec_wp_fweq(enum hfi_vewsion vewsion, u32 codec, u32 session_type)
{
	const stwuct hfi_pwatfowm *pwat;
	unsigned wong fweq = 0;

	pwat = hfi_pwatfowm_get(vewsion);
	if (!pwat)
		wetuwn 0;

	if (pwat->codec_wp_fweq)
		fweq = pwat->codec_wp_fweq(session_type, codec);

	wetuwn fweq;
}

int
hfi_pwatfowm_get_codecs(stwuct venus_cowe *cowe, u32 *enc_codecs, u32 *dec_codecs, u32 *count)
{
	const stwuct hfi_pwatfowm *pwat;

	pwat = hfi_pwatfowm_get(cowe->wes->hfi_vewsion);
	if (!pwat)
		wetuwn -EINVAW;

	if (pwat->codecs)
		pwat->codecs(enc_codecs, dec_codecs, count);

	if (IS_IWIS2_1(cowe)) {
		*enc_codecs &= ~HFI_VIDEO_CODEC_VP8;
		*dec_codecs &= ~HFI_VIDEO_CODEC_VP8;
	}

	wetuwn 0;
}

