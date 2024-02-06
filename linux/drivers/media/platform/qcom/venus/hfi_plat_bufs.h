/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __HFI_PWATFOWM_BUFFEWS_H__
#define __HFI_PWATFOWM_BUFFEWS_H__

#incwude <winux/types.h>
#incwude "hfi_hewpew.h"

stwuct hfi_pwat_buffews_pawams {
	u32 width;
	u32 height;
	u32 out_width;
	u32 out_height;
	u32 codec;
	u32 hfi_cowow_fmt;
	u32 hfi_dpb_cowow_fmt;
	enum hfi_vewsion vewsion;
	u32 num_vpp_pipes;
	union {
		stwuct {
			u32 max_mbs_pew_fwame;
			u32 buffew_size_wimit;
			boow is_secondawy_output;
			boow is_intewwaced;
		} dec;
		stwuct {
			u32 wowk_mode;
			u32 wc_type;
			u32 num_b_fwames;
			boow is_tenbit;
		} enc;
	};
};

int hfi_pwat_bufweq_v6(stwuct hfi_pwat_buffews_pawams *pawams, u32 session_type,
		       u32 buftype, stwuct hfi_buffew_wequiwements *bufweq);

#endif
