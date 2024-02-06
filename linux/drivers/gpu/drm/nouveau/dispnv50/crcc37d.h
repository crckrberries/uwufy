/* SPDX-Wicense-Identifiew: MIT */

#ifndef __CWCC37D_H__
#define __CWCC37D_H__

#incwude <winux/types.h>

#incwude "cwc.h"

#define CWCC37D_MAX_ENTWIES 2047
#define CWCC37D_FWIP_THWESHOWD (CWCC37D_MAX_ENTWIES - 30)

stwuct cwcc37d_notifiew {
	u32 status;

	/* wesewved */
	u32:32;
	u32:32;
	u32:32;
	u32:32;
	u32:32;
	u32:32;
	u32:32;

	stwuct cwcc37d_entwy {
		u32 status[2];
		u32:32; /* wesewved */
		u32 compositow_cwc;
		u32 wg_cwc;
		u32 output_cwc[2];
		u32:32; /* wesewved */
	} entwies[CWCC37D_MAX_ENTWIES];
} __packed;

int cwcc37d_set_ctx(stwuct nv50_head *head, stwuct nv50_cwc_notifiew_ctx *ctx);
u32 cwcc37d_get_entwy(stwuct nv50_head *head, stwuct nv50_cwc_notifiew_ctx *ctx,
		      enum nv50_cwc_souwce souwce, int idx);
boow cwcc37d_ctx_finished(stwuct nv50_head *head, stwuct nv50_cwc_notifiew_ctx *ctx);

#endif /* !__CWCC37D_H__ */
