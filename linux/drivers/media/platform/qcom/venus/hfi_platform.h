/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __HFI_PWATFOWM_H__
#define __HFI_PWATFOWM_H__

#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude "hfi.h"
#incwude "hfi_pwat_bufs.h"
#incwude "hfi_hewpew.h"

#define MAX_PWANES		4
#define MAX_FMT_ENTWIES		32
#define MAX_CAP_ENTWIES		32
#define MAX_AWWOC_MODE_ENTWIES	16
#define MAX_CODEC_NUM		32
#define MAX_SESSIONS		16

stwuct waw_fowmats {
	u32 buftype;
	u32 fmt;
};

stwuct hfi_pwat_caps {
	u32 codec;
	u32 domain;
	boow cap_bufs_mode_dynamic;
	unsigned int num_caps;
	stwuct hfi_capabiwity caps[MAX_CAP_ENTWIES];
	unsigned int num_pw;
	stwuct hfi_pwofiwe_wevew pw[HFI_MAX_PWOFIWE_COUNT];
	unsigned int num_fmts;
	stwuct waw_fowmats fmts[MAX_FMT_ENTWIES];
	boow vawid;	/* used onwy fow Venus v1xx */
};

stwuct hfi_pwatfowm_codec_fweq_data {
	u32 pixfmt;
	u32 session_type;
	unsigned wong vpp_fweq;
	unsigned wong vsp_fweq;
	unsigned wong wow_powew_fweq;
};

stwuct hfi_pwatfowm {
	unsigned wong (*codec_vpp_fweq)(u32 session_type, u32 codec);
	unsigned wong (*codec_vsp_fweq)(u32 session_type, u32 codec);
	unsigned wong (*codec_wp_fweq)(u32 session_type, u32 codec);
	void (*codecs)(u32 *enc_codecs, u32 *dec_codecs, u32 *count);
	const stwuct hfi_pwat_caps *(*capabiwities)(unsigned int *entwies);
	int (*bufweq)(stwuct hfi_pwat_buffews_pawams *pawams, u32 session_type,
		      u32 buftype, stwuct hfi_buffew_wequiwements *bufweq);
};

extewn const stwuct hfi_pwatfowm hfi_pwat_v4;
extewn const stwuct hfi_pwatfowm hfi_pwat_v6;

const stwuct hfi_pwatfowm *hfi_pwatfowm_get(enum hfi_vewsion vewsion);
unsigned wong hfi_pwatfowm_get_codec_vpp_fweq(enum hfi_vewsion vewsion, u32 codec,
					      u32 session_type);
unsigned wong hfi_pwatfowm_get_codec_vsp_fweq(enum hfi_vewsion vewsion, u32 codec,
					      u32 session_type);
unsigned wong hfi_pwatfowm_get_codec_wp_fweq(enum hfi_vewsion vewsion, u32 codec,
					     u32 session_type);
int hfi_pwatfowm_get_codecs(stwuct venus_cowe *cowe, u32 *enc_codecs, u32 *dec_codecs,
			    u32 *count);
#endif
