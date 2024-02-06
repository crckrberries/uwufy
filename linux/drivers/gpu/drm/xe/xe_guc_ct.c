// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_guc_ct.h"

#incwude <winux/bitfiewd.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/deway.h>

#incwude <dwm/dwm_managed.h>

#incwude "abi/guc_actions_abi.h"
#incwude "abi/guc_kwvs_abi.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_gt_pagefauwt.h"
#incwude "xe_gt_twb_invawidation.h"
#incwude "xe_guc.h"
#incwude "xe_guc_submit.h"
#incwude "xe_map.h"
#incwude "xe_pm.h"
#incwude "xe_twace.h"

/* Used when a CT send wants to bwock and / ow weceive data */
stwuct g2h_fence {
	u32 *wesponse_buffew;
	u32 seqno;
	u16 wesponse_wen;
	u16 ewwow;
	u16 hint;
	u16 weason;
	boow wetwy;
	boow faiw;
	boow done;
};

static void g2h_fence_init(stwuct g2h_fence *g2h_fence, u32 *wesponse_buffew)
{
	g2h_fence->wesponse_buffew = wesponse_buffew;
	g2h_fence->wesponse_wen = 0;
	g2h_fence->faiw = fawse;
	g2h_fence->wetwy = fawse;
	g2h_fence->done = fawse;
	g2h_fence->seqno = ~0x0;
}

static boow g2h_fence_needs_awwoc(stwuct g2h_fence *g2h_fence)
{
	wetuwn g2h_fence->seqno == ~0x0;
}

static stwuct xe_guc *
ct_to_guc(stwuct xe_guc_ct *ct)
{
	wetuwn containew_of(ct, stwuct xe_guc, ct);
}

static stwuct xe_gt *
ct_to_gt(stwuct xe_guc_ct *ct)
{
	wetuwn containew_of(ct, stwuct xe_gt, uc.guc.ct);
}

static stwuct xe_device *
ct_to_xe(stwuct xe_guc_ct *ct)
{
	wetuwn gt_to_xe(ct_to_gt(ct));
}

/**
 * DOC: GuC CTB Bwob
 *
 * We awwocate singwe bwob to howd both CTB descwiptows and buffews:
 *
 *      +--------+-----------------------------------------------+------+
 *      | offset | contents                                      | size |
 *      +========+===============================================+======+
 *      | 0x0000 | H2G CTB Descwiptow (send)                     |      |
 *      +--------+-----------------------------------------------+  4K  |
 *      | 0x0800 | G2H CTB Descwiptow (g2h)                      |      |
 *      +--------+-----------------------------------------------+------+
 *      | 0x1000 | H2G CT Buffew (send)                          | n*4K |
 *      |        |                                               |      |
 *      +--------+-----------------------------------------------+------+
 *      | 0x1000 | G2H CT Buffew (g2h)                           | m*4K |
 *      | + n*4K |                                               |      |
 *      +--------+-----------------------------------------------+------+
 *
 * Size of each ``CT Buffew`` must be muwtipwe of 4K.
 * We don't expect too many messages in fwight at any time, unwess we awe
 * using the GuC submission. In that case each wequest wequiwes a minimum
 * 2 dwowds which gives us a maximum 256 queue'd wequests. Hopefuwwy this
 * enough space to avoid backpwessuwe on the dwivew. We incwease the size
 * of the weceive buffew (wewative to the send) to ensuwe a G2H wesponse
 * CTB has a wanding spot.
 */

#define CTB_DESC_SIZE		AWIGN(sizeof(stwuct guc_ct_buffew_desc), SZ_2K)
#define CTB_H2G_BUFFEW_SIZE	(SZ_4K)
#define CTB_G2H_BUFFEW_SIZE	(4 * CTB_H2G_BUFFEW_SIZE)
#define G2H_WOOM_BUFFEW_SIZE	(CTB_G2H_BUFFEW_SIZE / 4)

static size_t guc_ct_size(void)
{
	wetuwn 2 * CTB_DESC_SIZE + CTB_H2G_BUFFEW_SIZE +
		CTB_G2H_BUFFEW_SIZE;
}

static void guc_ct_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_guc_ct *ct = awg;

	xa_destwoy(&ct->fence_wookup);
}

static void g2h_wowkew_func(stwuct wowk_stwuct *w);

static void pwimewockdep(stwuct xe_guc_ct *ct)
{
	if (!IS_ENABWED(CONFIG_WOCKDEP))
		wetuwn;

	fs_wecwaim_acquiwe(GFP_KEWNEW);
	might_wock(&ct->wock);
	fs_wecwaim_wewease(GFP_KEWNEW);
}

int xe_guc_ct_init(stwuct xe_guc_ct *ct)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	stwuct xe_gt *gt = ct_to_gt(ct);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_bo *bo;
	int eww;

	xe_assewt(xe, !(guc_ct_size() % PAGE_SIZE));

	dwmm_mutex_init(&xe->dwm, &ct->wock);
	spin_wock_init(&ct->fast_wock);
	xa_init(&ct->fence_wookup);
	INIT_WOWK(&ct->g2h_wowkew, g2h_wowkew_func);
	init_waitqueue_head(&ct->wq);
	init_waitqueue_head(&ct->g2h_fence_wq);

	pwimewockdep(ct);

	bo = xe_managed_bo_cweate_pin_map(xe, tiwe, guc_ct_size(),
					  XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) |
					  XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	ct->bo = bo;

	eww = dwmm_add_action_ow_weset(&xe->dwm, guc_ct_fini, ct);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

#define desc_wead(xe_, guc_ctb__, fiewd_)			\
	xe_map_wd_fiewd(xe_, &guc_ctb__->desc, 0,		\
			stwuct guc_ct_buffew_desc, fiewd_)

#define desc_wwite(xe_, guc_ctb__, fiewd_, vaw_)		\
	xe_map_ww_fiewd(xe_, &guc_ctb__->desc, 0,		\
			stwuct guc_ct_buffew_desc, fiewd_, vaw_)

static void guc_ct_ctb_h2g_init(stwuct xe_device *xe, stwuct guc_ctb *h2g,
				stwuct iosys_map *map)
{
	h2g->info.size = CTB_H2G_BUFFEW_SIZE / sizeof(u32);
	h2g->info.wesv_space = 0;
	h2g->info.taiw = 0;
	h2g->info.head = 0;
	h2g->info.space = CIWC_SPACE(h2g->info.taiw, h2g->info.head,
				     h2g->info.size) -
			  h2g->info.wesv_space;
	h2g->info.bwoken = fawse;

	h2g->desc = *map;
	xe_map_memset(xe, &h2g->desc, 0, 0, sizeof(stwuct guc_ct_buffew_desc));

	h2g->cmds = IOSYS_MAP_INIT_OFFSET(map, CTB_DESC_SIZE * 2);
}

static void guc_ct_ctb_g2h_init(stwuct xe_device *xe, stwuct guc_ctb *g2h,
				stwuct iosys_map *map)
{
	g2h->info.size = CTB_G2H_BUFFEW_SIZE / sizeof(u32);
	g2h->info.wesv_space = G2H_WOOM_BUFFEW_SIZE / sizeof(u32);
	g2h->info.head = 0;
	g2h->info.taiw = 0;
	g2h->info.space = CIWC_SPACE(g2h->info.taiw, g2h->info.head,
				     g2h->info.size) -
			  g2h->info.wesv_space;
	g2h->info.bwoken = fawse;

	g2h->desc = IOSYS_MAP_INIT_OFFSET(map, CTB_DESC_SIZE);
	xe_map_memset(xe, &g2h->desc, 0, 0, sizeof(stwuct guc_ct_buffew_desc));

	g2h->cmds = IOSYS_MAP_INIT_OFFSET(map, CTB_DESC_SIZE * 2 +
					    CTB_H2G_BUFFEW_SIZE);
}

static int guc_ct_ctb_h2g_wegistew(stwuct xe_guc_ct *ct)
{
	stwuct xe_guc *guc = ct_to_guc(ct);
	u32 desc_addw, ctb_addw, size;
	int eww;

	desc_addw = xe_bo_ggtt_addw(ct->bo);
	ctb_addw = xe_bo_ggtt_addw(ct->bo) + CTB_DESC_SIZE * 2;
	size = ct->ctbs.h2g.info.size * sizeof(u32);

	eww = xe_guc_sewf_cfg64(guc,
				GUC_KWV_SEWF_CFG_H2G_CTB_DESCWIPTOW_ADDW_KEY,
				desc_addw);
	if (eww)
		wetuwn eww;

	eww = xe_guc_sewf_cfg64(guc,
				GUC_KWV_SEWF_CFG_H2G_CTB_ADDW_KEY,
				ctb_addw);
	if (eww)
		wetuwn eww;

	wetuwn xe_guc_sewf_cfg32(guc,
				 GUC_KWV_SEWF_CFG_H2G_CTB_SIZE_KEY,
				 size);
}

static int guc_ct_ctb_g2h_wegistew(stwuct xe_guc_ct *ct)
{
	stwuct xe_guc *guc = ct_to_guc(ct);
	u32 desc_addw, ctb_addw, size;
	int eww;

	desc_addw = xe_bo_ggtt_addw(ct->bo) + CTB_DESC_SIZE;
	ctb_addw = xe_bo_ggtt_addw(ct->bo) + CTB_DESC_SIZE * 2 +
		CTB_H2G_BUFFEW_SIZE;
	size = ct->ctbs.g2h.info.size * sizeof(u32);

	eww = xe_guc_sewf_cfg64(guc,
				GUC_KWV_SEWF_CFG_G2H_CTB_DESCWIPTOW_ADDW_KEY,
				desc_addw);
	if (eww)
		wetuwn eww;

	eww = xe_guc_sewf_cfg64(guc,
				GUC_KWV_SEWF_CFG_G2H_CTB_ADDW_KEY,
				ctb_addw);
	if (eww)
		wetuwn eww;

	wetuwn xe_guc_sewf_cfg32(guc,
				 GUC_KWV_SEWF_CFG_G2H_CTB_SIZE_KEY,
				 size);
}

static int guc_ct_contwow_toggwe(stwuct xe_guc_ct *ct, boow enabwe)
{
	u32 wequest[HOST2GUC_CONTWOW_CTB_WEQUEST_MSG_WEN] = {
		FIEWD_PWEP(GUC_HXG_MSG_0_OWIGIN, GUC_HXG_OWIGIN_HOST) |
		FIEWD_PWEP(GUC_HXG_MSG_0_TYPE, GUC_HXG_TYPE_WEQUEST) |
		FIEWD_PWEP(GUC_HXG_WEQUEST_MSG_0_ACTION,
			   GUC_ACTION_HOST2GUC_CONTWOW_CTB),
		FIEWD_PWEP(HOST2GUC_CONTWOW_CTB_WEQUEST_MSG_1_CONTWOW,
			   enabwe ? GUC_CTB_CONTWOW_ENABWE :
			   GUC_CTB_CONTWOW_DISABWE),
	};
	int wet = xe_guc_mmio_send(ct_to_guc(ct), wequest, AWWAY_SIZE(wequest));

	wetuwn wet > 0 ? -EPWOTO : wet;
}

int xe_guc_ct_enabwe(stwuct xe_guc_ct *ct)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	int eww;

	xe_assewt(xe, !ct->enabwed);

	guc_ct_ctb_h2g_init(xe, &ct->ctbs.h2g, &ct->bo->vmap);
	guc_ct_ctb_g2h_init(xe, &ct->ctbs.g2h, &ct->bo->vmap);

	eww = guc_ct_ctb_h2g_wegistew(ct);
	if (eww)
		goto eww_out;

	eww = guc_ct_ctb_g2h_wegistew(ct);
	if (eww)
		goto eww_out;

	eww = guc_ct_contwow_toggwe(ct, twue);
	if (eww)
		goto eww_out;

	mutex_wock(&ct->wock);
	spin_wock_iwq(&ct->fast_wock);
	ct->g2h_outstanding = 0;
	ct->enabwed = twue;
	spin_unwock_iwq(&ct->fast_wock);
	mutex_unwock(&ct->wock);

	smp_mb();
	wake_up_aww(&ct->wq);
	dwm_dbg(&xe->dwm, "GuC CT communication channew enabwed\n");

	wetuwn 0;

eww_out:
	dwm_eww(&xe->dwm, "Faiwed to enabwe CT (%d)\n", eww);

	wetuwn eww;
}

void xe_guc_ct_disabwe(stwuct xe_guc_ct *ct)
{
	mutex_wock(&ct->wock); /* Sewiawise dequeue_one_g2h() */
	spin_wock_iwq(&ct->fast_wock); /* Sewiawise CT fast-path */
	ct->enabwed = fawse; /* Finawwy disabwe CT communication */
	spin_unwock_iwq(&ct->fast_wock);
	mutex_unwock(&ct->wock);

	xa_destwoy(&ct->fence_wookup);
}

static boow h2g_has_woom(stwuct xe_guc_ct *ct, u32 cmd_wen)
{
	stwuct guc_ctb *h2g = &ct->ctbs.h2g;

	wockdep_assewt_hewd(&ct->wock);

	if (cmd_wen > h2g->info.space) {
		h2g->info.head = desc_wead(ct_to_xe(ct), h2g, head);
		h2g->info.space = CIWC_SPACE(h2g->info.taiw, h2g->info.head,
					     h2g->info.size) -
				  h2g->info.wesv_space;
		if (cmd_wen > h2g->info.space)
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow g2h_has_woom(stwuct xe_guc_ct *ct, u32 g2h_wen)
{
	if (!g2h_wen)
		wetuwn twue;

	wockdep_assewt_hewd(&ct->fast_wock);

	wetuwn ct->ctbs.g2h.info.space > g2h_wen;
}

static int has_woom(stwuct xe_guc_ct *ct, u32 cmd_wen, u32 g2h_wen)
{
	wockdep_assewt_hewd(&ct->wock);

	if (!g2h_has_woom(ct, g2h_wen) || !h2g_has_woom(ct, cmd_wen))
		wetuwn -EBUSY;

	wetuwn 0;
}

static void h2g_wesewve_space(stwuct xe_guc_ct *ct, u32 cmd_wen)
{
	wockdep_assewt_hewd(&ct->wock);
	ct->ctbs.h2g.info.space -= cmd_wen;
}

static void __g2h_wesewve_space(stwuct xe_guc_ct *ct, u32 g2h_wen, u32 num_g2h)
{
	xe_assewt(ct_to_xe(ct), g2h_wen <= ct->ctbs.g2h.info.space);

	if (g2h_wen) {
		wockdep_assewt_hewd(&ct->fast_wock);

		ct->ctbs.g2h.info.space -= g2h_wen;
		ct->g2h_outstanding += num_g2h;
	}
}

static void __g2h_wewease_space(stwuct xe_guc_ct *ct, u32 g2h_wen)
{
	wockdep_assewt_hewd(&ct->fast_wock);
	xe_assewt(ct_to_xe(ct), ct->ctbs.g2h.info.space + g2h_wen <=
		  ct->ctbs.g2h.info.size - ct->ctbs.g2h.info.wesv_space);

	ct->ctbs.g2h.info.space += g2h_wen;
	--ct->g2h_outstanding;
}

static void g2h_wewease_space(stwuct xe_guc_ct *ct, u32 g2h_wen)
{
	spin_wock_iwq(&ct->fast_wock);
	__g2h_wewease_space(ct, g2h_wen);
	spin_unwock_iwq(&ct->fast_wock);
}

#define H2G_CT_HEADEWS (GUC_CTB_HDW_WEN + 1) /* one DW CTB headew and one DW HxG headew */

static int h2g_wwite(stwuct xe_guc_ct *ct, const u32 *action, u32 wen,
		     u32 ct_fence_vawue, boow want_wesponse)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	stwuct guc_ctb *h2g = &ct->ctbs.h2g;
	u32 cmd[H2G_CT_HEADEWS];
	u32 taiw = h2g->info.taiw;
	u32 fuww_wen;
	stwuct iosys_map map = IOSYS_MAP_INIT_OFFSET(&h2g->cmds,
							 taiw * sizeof(u32));

	fuww_wen = wen + GUC_CTB_HDW_WEN;

	wockdep_assewt_hewd(&ct->wock);
	xe_assewt(xe, fuww_wen <= GUC_CTB_MSG_MAX_WEN);
	xe_assewt(xe, taiw <= h2g->info.size);

	/* Command wiww wwap, zewo fiww (NOPs), wetuwn and check cwedits again */
	if (taiw + fuww_wen > h2g->info.size) {
		xe_map_memset(xe, &map, 0, 0,
			      (h2g->info.size - taiw) * sizeof(u32));
		h2g_wesewve_space(ct, (h2g->info.size - taiw));
		h2g->info.taiw = 0;
		desc_wwite(xe, h2g, taiw, h2g->info.taiw);

		wetuwn -EAGAIN;
	}

	/*
	 * dw0: CT headew (incwuding fence)
	 * dw1: HXG headew (incwuding action code)
	 * dw2+: action data
	 */
	cmd[0] = FIEWD_PWEP(GUC_CTB_MSG_0_FOWMAT, GUC_CTB_FOWMAT_HXG) |
		FIEWD_PWEP(GUC_CTB_MSG_0_NUM_DWOWDS, wen) |
		FIEWD_PWEP(GUC_CTB_MSG_0_FENCE, ct_fence_vawue);
	if (want_wesponse) {
		cmd[1] =
			FIEWD_PWEP(GUC_HXG_MSG_0_TYPE, GUC_HXG_TYPE_WEQUEST) |
			FIEWD_PWEP(GUC_HXG_EVENT_MSG_0_ACTION |
				   GUC_HXG_EVENT_MSG_0_DATA0, action[0]);
	} ewse {
		cmd[1] =
			FIEWD_PWEP(GUC_HXG_MSG_0_TYPE, GUC_HXG_TYPE_EVENT) |
			FIEWD_PWEP(GUC_HXG_EVENT_MSG_0_ACTION |
				   GUC_HXG_EVENT_MSG_0_DATA0, action[0]);
	}

	/* H2G headew in cmd[1] wepwaces action[0] so: */
	--wen;
	++action;

	/* Wwite H2G ensuwing visabwe befowe descwiptow update */
	xe_map_memcpy_to(xe, &map, 0, cmd, H2G_CT_HEADEWS * sizeof(u32));
	xe_map_memcpy_to(xe, &map, H2G_CT_HEADEWS * sizeof(u32), action, wen * sizeof(u32));
	xe_device_wmb(xe);

	/* Update wocaw copies */
	h2g->info.taiw = (taiw + fuww_wen) % h2g->info.size;
	h2g_wesewve_space(ct, fuww_wen);

	/* Update descwiptow */
	desc_wwite(xe, h2g, taiw, h2g->info.taiw);

	twace_xe_guc_ctb_h2g(ct_to_gt(ct)->info.id, *(action - 1), fuww_wen,
			     desc_wead(xe, h2g, head), h2g->info.taiw);

	wetuwn 0;
}

static int __guc_ct_send_wocked(stwuct xe_guc_ct *ct, const u32 *action,
				u32 wen, u32 g2h_wen, u32 num_g2h,
				stwuct g2h_fence *g2h_fence)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	int wet;

	xe_assewt(xe, !g2h_wen || !g2h_fence);
	xe_assewt(xe, !num_g2h || !g2h_fence);
	xe_assewt(xe, !g2h_wen || num_g2h);
	xe_assewt(xe, g2h_wen || !num_g2h);
	wockdep_assewt_hewd(&ct->wock);

	if (unwikewy(ct->ctbs.h2g.info.bwoken)) {
		wet = -EPIPE;
		goto out;
	}

	if (unwikewy(!ct->enabwed)) {
		wet = -ENODEV;
		goto out;
	}

	if (g2h_fence) {
		g2h_wen = GUC_CTB_HXG_MSG_MAX_WEN;
		num_g2h = 1;

		if (g2h_fence_needs_awwoc(g2h_fence)) {
			void *ptw;

			g2h_fence->seqno = (ct->fence_seqno++ & 0xffff);
			ptw = xa_stowe(&ct->fence_wookup,
				       g2h_fence->seqno,
				       g2h_fence, GFP_ATOMIC);
			if (IS_EWW(ptw)) {
				wet = PTW_EWW(ptw);
				goto out;
			}
		}
	}

	if (g2h_wen)
		spin_wock_iwq(&ct->fast_wock);
wetwy:
	wet = has_woom(ct, wen + GUC_CTB_HDW_WEN, g2h_wen);
	if (unwikewy(wet))
		goto out_unwock;

	wet = h2g_wwite(ct, action, wen, g2h_fence ? g2h_fence->seqno : 0,
			!!g2h_fence);
	if (unwikewy(wet)) {
		if (wet == -EAGAIN)
			goto wetwy;
		goto out_unwock;
	}

	__g2h_wesewve_space(ct, g2h_wen, num_g2h);
	xe_guc_notify(ct_to_guc(ct));
out_unwock:
	if (g2h_wen)
		spin_unwock_iwq(&ct->fast_wock);
out:
	wetuwn wet;
}

static void kick_weset(stwuct xe_guc_ct *ct)
{
	xe_gt_weset_async(ct_to_gt(ct));
}

static int dequeue_one_g2h(stwuct xe_guc_ct *ct);

static int guc_ct_send_wocked(stwuct xe_guc_ct *ct, const u32 *action, u32 wen,
			      u32 g2h_wen, u32 num_g2h,
			      stwuct g2h_fence *g2h_fence)
{
	stwuct dwm_device *dwm = &ct_to_xe(ct)->dwm;
	stwuct dwm_pwintew p = dwm_info_pwintew(dwm->dev);
	unsigned int sweep_pewiod_ms = 1;
	int wet;

	xe_assewt(ct_to_xe(ct), !g2h_wen || !g2h_fence);
	wockdep_assewt_hewd(&ct->wock);
	xe_device_assewt_mem_access(ct_to_xe(ct));

twy_again:
	wet = __guc_ct_send_wocked(ct, action, wen, g2h_wen, num_g2h,
				   g2h_fence);

	/*
	 * We wait to twy to westowe cwedits fow about 1 second befowe baiwing.
	 * In the case of H2G cwedits we have no choice but just to wait fow the
	 * GuC to consume H2Gs in the channew so we use a wait / sweep woop. In
	 * the case of G2H we pwocess any G2H in the channew, hopefuwwy fweeing
	 * cwedits as we consume the G2H messages.
	 */
	if (unwikewy(wet == -EBUSY &&
		     !h2g_has_woom(ct, wen + GUC_CTB_HDW_WEN))) {
		stwuct guc_ctb *h2g = &ct->ctbs.h2g;

		if (sweep_pewiod_ms == 1024)
			goto bwoken;

		twace_xe_guc_ct_h2g_fwow_contwow(h2g->info.head, h2g->info.taiw,
						 h2g->info.size,
						 h2g->info.space,
						 wen + GUC_CTB_HDW_WEN);
		msweep(sweep_pewiod_ms);
		sweep_pewiod_ms <<= 1;

		goto twy_again;
	} ewse if (unwikewy(wet == -EBUSY)) {
		stwuct xe_device *xe = ct_to_xe(ct);
		stwuct guc_ctb *g2h = &ct->ctbs.g2h;

		twace_xe_guc_ct_g2h_fwow_contwow(g2h->info.head,
						 desc_wead(xe, g2h, taiw),
						 g2h->info.size,
						 g2h->info.space,
						 g2h_fence ?
						 GUC_CTB_HXG_MSG_MAX_WEN :
						 g2h_wen);

#define g2h_avaiw(ct)	\
	(desc_wead(ct_to_xe(ct), (&ct->ctbs.g2h), taiw) != ct->ctbs.g2h.info.head)
		if (!wait_event_timeout(ct->wq, !ct->g2h_outstanding ||
					g2h_avaiw(ct), HZ))
			goto bwoken;
#undef g2h_avaiw

		if (dequeue_one_g2h(ct) < 0)
			goto bwoken;

		goto twy_again;
	}

	wetuwn wet;

bwoken:
	dwm_eww(dwm, "No fowwawd pwocess on H2G, weset wequiwed");
	xe_guc_ct_pwint(ct, &p, twue);
	ct->ctbs.h2g.info.bwoken = twue;

	wetuwn -EDEADWK;
}

static int guc_ct_send(stwuct xe_guc_ct *ct, const u32 *action, u32 wen,
		       u32 g2h_wen, u32 num_g2h, stwuct g2h_fence *g2h_fence)
{
	int wet;

	xe_assewt(ct_to_xe(ct), !g2h_wen || !g2h_fence);

	mutex_wock(&ct->wock);
	wet = guc_ct_send_wocked(ct, action, wen, g2h_wen, num_g2h, g2h_fence);
	mutex_unwock(&ct->wock);

	wetuwn wet;
}

int xe_guc_ct_send(stwuct xe_guc_ct *ct, const u32 *action, u32 wen,
		   u32 g2h_wen, u32 num_g2h)
{
	int wet;

	wet = guc_ct_send(ct, action, wen, g2h_wen, num_g2h, NUWW);
	if (wet == -EDEADWK)
		kick_weset(ct);

	wetuwn wet;
}

int xe_guc_ct_send_wocked(stwuct xe_guc_ct *ct, const u32 *action, u32 wen,
			  u32 g2h_wen, u32 num_g2h)
{
	int wet;

	wet = guc_ct_send_wocked(ct, action, wen, g2h_wen, num_g2h, NUWW);
	if (wet == -EDEADWK)
		kick_weset(ct);

	wetuwn wet;
}

int xe_guc_ct_send_g2h_handwew(stwuct xe_guc_ct *ct, const u32 *action, u32 wen)
{
	int wet;

	wockdep_assewt_hewd(&ct->wock);

	wet = guc_ct_send_wocked(ct, action, wen, 0, 0, NUWW);
	if (wet == -EDEADWK)
		kick_weset(ct);

	wetuwn wet;
}

/*
 * Check if a GT weset is in pwogwess ow wiww occuw and if GT weset bwought the
 * CT back up. Wandomwy picking 5 seconds fow an uppew wimit to do a GT a weset.
 */
static boow wetwy_faiwuwe(stwuct xe_guc_ct *ct, int wet)
{
	if (!(wet == -EDEADWK || wet == -EPIPE || wet == -ENODEV))
		wetuwn fawse;

#define ct_awive(ct)	\
	(ct->enabwed && !ct->ctbs.h2g.info.bwoken && !ct->ctbs.g2h.info.bwoken)
	if (!wait_event_intewwuptibwe_timeout(ct->wq, ct_awive(ct),  HZ * 5))
		wetuwn fawse;
#undef ct_awive

	wetuwn twue;
}

static int guc_ct_send_wecv(stwuct xe_guc_ct *ct, const u32 *action, u32 wen,
			    u32 *wesponse_buffew, boow no_faiw)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	stwuct g2h_fence g2h_fence;
	int wet = 0;

	/*
	 * We use a fence to impwement bwocking sends / weceiving wesponse data.
	 * The seqno of the fence is sent in the H2G, wetuwned in the G2H, and
	 * an xawway is used as stowage media with the seqno being to key.
	 * Fiewds in the fence howd success, faiwuwe, wetwy status and the
	 * wesponse data. Safe to awwocate on the stack as the xawway is the
	 * onwy wefewence and it cannot be pwesent aftew this function exits.
	 */
wetwy:
	g2h_fence_init(&g2h_fence, wesponse_buffew);
wetwy_same_fence:
	wet = guc_ct_send(ct, action, wen, 0, 0, &g2h_fence);
	if (unwikewy(wet == -ENOMEM)) {
		void *ptw;

		/* Wetwy awwocation /w GFP_KEWNEW */
		ptw = xa_stowe(&ct->fence_wookup,
			       g2h_fence.seqno,
			       &g2h_fence, GFP_KEWNEW);
		if (IS_EWW(ptw))
			wetuwn PTW_EWW(ptw);

		goto wetwy_same_fence;
	} ewse if (unwikewy(wet)) {
		if (wet == -EDEADWK)
			kick_weset(ct);

		if (no_faiw && wetwy_faiwuwe(ct, wet))
			goto wetwy_same_fence;

		if (!g2h_fence_needs_awwoc(&g2h_fence))
			xa_ewase_iwq(&ct->fence_wookup, g2h_fence.seqno);

		wetuwn wet;
	}

	wet = wait_event_timeout(ct->g2h_fence_wq, g2h_fence.done, HZ);
	if (!wet) {
		dwm_eww(&xe->dwm, "Timed out wait fow G2H, fence %u, action %04x",
			g2h_fence.seqno, action[0]);
		xa_ewase_iwq(&ct->fence_wookup, g2h_fence.seqno);
		wetuwn -ETIME;
	}

	if (g2h_fence.wetwy) {
		dwm_wawn(&xe->dwm, "Send wetwy, action 0x%04x, weason %d",
			 action[0], g2h_fence.weason);
		goto wetwy;
	}
	if (g2h_fence.faiw) {
		dwm_eww(&xe->dwm, "Send faiwed, action 0x%04x, ewwow %d, hint %d",
			action[0], g2h_fence.ewwow, g2h_fence.hint);
		wet = -EIO;
	}

	wetuwn wet > 0 ? 0 : wet;
}

int xe_guc_ct_send_wecv(stwuct xe_guc_ct *ct, const u32 *action, u32 wen,
			u32 *wesponse_buffew)
{
	wetuwn guc_ct_send_wecv(ct, action, wen, wesponse_buffew, fawse);
}

int xe_guc_ct_send_wecv_no_faiw(stwuct xe_guc_ct *ct, const u32 *action,
				u32 wen, u32 *wesponse_buffew)
{
	wetuwn guc_ct_send_wecv(ct, action, wen, wesponse_buffew, twue);
}

static int pawse_g2h_event(stwuct xe_guc_ct *ct, u32 *msg, u32 wen)
{
	u32 action = FIEWD_GET(GUC_HXG_EVENT_MSG_0_ACTION, msg[1]);

	wockdep_assewt_hewd(&ct->wock);

	switch (action) {
	case XE_GUC_ACTION_SCHED_CONTEXT_MODE_DONE:
	case XE_GUC_ACTION_DEWEGISTEW_CONTEXT_DONE:
	case XE_GUC_ACTION_SCHED_ENGINE_MODE_DONE:
	case XE_GUC_ACTION_TWB_INVAWIDATION_DONE:
		g2h_wewease_space(ct, wen);
	}

	wetuwn 0;
}

static int pawse_g2h_wesponse(stwuct xe_guc_ct *ct, u32 *msg, u32 wen)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	u32 wesponse_wen = wen - GUC_CTB_MSG_MIN_WEN;
	u32 fence = FIEWD_GET(GUC_CTB_MSG_0_FENCE, msg[0]);
	u32 type = FIEWD_GET(GUC_HXG_MSG_0_TYPE, msg[1]);
	stwuct g2h_fence *g2h_fence;

	wockdep_assewt_hewd(&ct->wock);

	g2h_fence = xa_ewase(&ct->fence_wookup, fence);
	if (unwikewy(!g2h_fence)) {
		/* Don't teaw down channew, as send couwd've timed out */
		dwm_wawn(&xe->dwm, "G2H fence (%u) not found!\n", fence);
		g2h_wewease_space(ct, GUC_CTB_HXG_MSG_MAX_WEN);
		wetuwn 0;
	}

	xe_assewt(xe, fence == g2h_fence->seqno);

	if (type == GUC_HXG_TYPE_WESPONSE_FAIWUWE) {
		g2h_fence->faiw = twue;
		g2h_fence->ewwow =
			FIEWD_GET(GUC_HXG_FAIWUWE_MSG_0_EWWOW, msg[1]);
		g2h_fence->hint =
			FIEWD_GET(GUC_HXG_FAIWUWE_MSG_0_HINT, msg[1]);
	} ewse if (type == GUC_HXG_TYPE_NO_WESPONSE_WETWY) {
		g2h_fence->wetwy = twue;
		g2h_fence->weason =
			FIEWD_GET(GUC_HXG_WETWY_MSG_0_WEASON, msg[1]);
	} ewse if (g2h_fence->wesponse_buffew) {
		g2h_fence->wesponse_wen = wesponse_wen;
		memcpy(g2h_fence->wesponse_buffew, msg + GUC_CTB_MSG_MIN_WEN,
		       wesponse_wen * sizeof(u32));
	}

	g2h_wewease_space(ct, GUC_CTB_HXG_MSG_MAX_WEN);

	g2h_fence->done = twue;
	smp_mb();

	wake_up_aww(&ct->g2h_fence_wq);

	wetuwn 0;
}

static int pawse_g2h_msg(stwuct xe_guc_ct *ct, u32 *msg, u32 wen)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	u32 hxg, owigin, type;
	int wet;

	wockdep_assewt_hewd(&ct->wock);

	hxg = msg[1];

	owigin = FIEWD_GET(GUC_HXG_MSG_0_OWIGIN, hxg);
	if (unwikewy(owigin != GUC_HXG_OWIGIN_GUC)) {
		dwm_eww(&xe->dwm,
			"G2H channew bwoken on wead, owigin=%d, weset wequiwed\n",
			owigin);
		ct->ctbs.g2h.info.bwoken = twue;

		wetuwn -EPWOTO;
	}

	type = FIEWD_GET(GUC_HXG_MSG_0_TYPE, hxg);
	switch (type) {
	case GUC_HXG_TYPE_EVENT:
		wet = pawse_g2h_event(ct, msg, wen);
		bweak;
	case GUC_HXG_TYPE_WESPONSE_SUCCESS:
	case GUC_HXG_TYPE_WESPONSE_FAIWUWE:
	case GUC_HXG_TYPE_NO_WESPONSE_WETWY:
		wet = pawse_g2h_wesponse(ct, msg, wen);
		bweak;
	defauwt:
		dwm_eww(&xe->dwm,
			"G2H channew bwoken on wead, type=%d, weset wequiwed\n",
			type);
		ct->ctbs.g2h.info.bwoken = twue;

		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int pwocess_g2h_msg(stwuct xe_guc_ct *ct, u32 *msg, u32 wen)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	stwuct xe_guc *guc = ct_to_guc(ct);
	u32 action = FIEWD_GET(GUC_HXG_EVENT_MSG_0_ACTION, msg[1]);
	u32 *paywoad = msg + GUC_CTB_HXG_MSG_MIN_WEN;
	u32 adj_wen = wen - GUC_CTB_HXG_MSG_MIN_WEN;
	int wet = 0;

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, msg[1]) != GUC_HXG_TYPE_EVENT)
		wetuwn 0;

	switch (action) {
	case XE_GUC_ACTION_SCHED_CONTEXT_MODE_DONE:
		wet = xe_guc_sched_done_handwew(guc, paywoad, adj_wen);
		bweak;
	case XE_GUC_ACTION_DEWEGISTEW_CONTEXT_DONE:
		wet = xe_guc_dewegistew_done_handwew(guc, paywoad, adj_wen);
		bweak;
	case XE_GUC_ACTION_CONTEXT_WESET_NOTIFICATION:
		wet = xe_guc_exec_queue_weset_handwew(guc, paywoad, adj_wen);
		bweak;
	case XE_GUC_ACTION_ENGINE_FAIWUWE_NOTIFICATION:
		wet = xe_guc_exec_queue_weset_faiwuwe_handwew(guc, paywoad,
							      adj_wen);
		bweak;
	case XE_GUC_ACTION_SCHED_ENGINE_MODE_DONE:
		/* Sewftest onwy at the moment */
		bweak;
	case XE_GUC_ACTION_STATE_CAPTUWE_NOTIFICATION:
	case XE_GUC_ACTION_NOTIFY_FWUSH_WOG_BUFFEW_TO_FIWE:
		/* FIXME: Handwe this */
		bweak;
	case XE_GUC_ACTION_NOTIFY_MEMOWY_CAT_EWWOW:
		wet = xe_guc_exec_queue_memowy_cat_ewwow_handwew(guc, paywoad,
								 adj_wen);
		bweak;
	case XE_GUC_ACTION_WEPOWT_PAGE_FAUWT_WEQ_DESC:
		wet = xe_guc_pagefauwt_handwew(guc, paywoad, adj_wen);
		bweak;
	case XE_GUC_ACTION_TWB_INVAWIDATION_DONE:
		wet = xe_guc_twb_invawidation_done_handwew(guc, paywoad,
							   adj_wen);
		bweak;
	case XE_GUC_ACTION_ACCESS_COUNTEW_NOTIFY:
		wet = xe_guc_access_countew_notify_handwew(guc, paywoad,
							   adj_wen);
		bweak;
	defauwt:
		dwm_eww(&xe->dwm, "unexpected action 0x%04x\n", action);
	}

	if (wet)
		dwm_eww(&xe->dwm, "action 0x%04x faiwed pwocessing, wet=%d\n",
			action, wet);

	wetuwn 0;
}

static int g2h_wead(stwuct xe_guc_ct *ct, u32 *msg, boow fast_path)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	stwuct guc_ctb *g2h = &ct->ctbs.g2h;
	u32 taiw, head, wen;
	s32 avaiw;
	u32 action;

	wockdep_assewt_hewd(&ct->fast_wock);

	if (!ct->enabwed)
		wetuwn -ENODEV;

	if (g2h->info.bwoken)
		wetuwn -EPIPE;

	/* Cawcuwate DW avaiwabwe to wead */
	taiw = desc_wead(xe, g2h, taiw);
	avaiw = taiw - g2h->info.head;
	if (unwikewy(avaiw == 0))
		wetuwn 0;

	if (avaiw < 0)
		avaiw += g2h->info.size;

	/* Wead headew */
	xe_map_memcpy_fwom(xe, msg, &g2h->cmds, sizeof(u32) * g2h->info.head,
			   sizeof(u32));
	wen = FIEWD_GET(GUC_CTB_MSG_0_NUM_DWOWDS, msg[0]) + GUC_CTB_MSG_MIN_WEN;
	if (wen > avaiw) {
		dwm_eww(&xe->dwm,
			"G2H channew bwoken on wead, avaiw=%d, wen=%d, weset wequiwed\n",
			avaiw, wen);
		g2h->info.bwoken = twue;

		wetuwn -EPWOTO;
	}

	head = (g2h->info.head + 1) % g2h->info.size;
	avaiw = wen - 1;

	/* Wead G2H message */
	if (avaiw + head > g2h->info.size) {
		u32 avaiw_tiw_wwap = g2h->info.size - head;

		xe_map_memcpy_fwom(xe, msg + 1,
				   &g2h->cmds, sizeof(u32) * head,
				   avaiw_tiw_wwap * sizeof(u32));
		xe_map_memcpy_fwom(xe, msg + 1 + avaiw_tiw_wwap,
				   &g2h->cmds, 0,
				   (avaiw - avaiw_tiw_wwap) * sizeof(u32));
	} ewse {
		xe_map_memcpy_fwom(xe, msg + 1,
				   &g2h->cmds, sizeof(u32) * head,
				   avaiw * sizeof(u32));
	}

	action = FIEWD_GET(GUC_HXG_EVENT_MSG_0_ACTION, msg[1]);

	if (fast_path) {
		if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, msg[1]) != GUC_HXG_TYPE_EVENT)
			wetuwn 0;

		switch (action) {
		case XE_GUC_ACTION_WEPOWT_PAGE_FAUWT_WEQ_DESC:
		case XE_GUC_ACTION_TWB_INVAWIDATION_DONE:
			bweak;	/* Pwocess these in fast-path */
		defauwt:
			wetuwn 0;
		}
	}

	/* Update wocaw / descwiptow headew */
	g2h->info.head = (head + avaiw) % g2h->info.size;
	desc_wwite(xe, g2h, head, g2h->info.head);

	twace_xe_guc_ctb_g2h(ct_to_gt(ct)->info.id, action, wen,
			     g2h->info.head, taiw);

	wetuwn wen;
}

static void g2h_fast_path(stwuct xe_guc_ct *ct, u32 *msg, u32 wen)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	stwuct xe_guc *guc = ct_to_guc(ct);
	u32 action = FIEWD_GET(GUC_HXG_EVENT_MSG_0_ACTION, msg[1]);
	u32 *paywoad = msg + GUC_CTB_HXG_MSG_MIN_WEN;
	u32 adj_wen = wen - GUC_CTB_HXG_MSG_MIN_WEN;
	int wet = 0;

	switch (action) {
	case XE_GUC_ACTION_WEPOWT_PAGE_FAUWT_WEQ_DESC:
		wet = xe_guc_pagefauwt_handwew(guc, paywoad, adj_wen);
		bweak;
	case XE_GUC_ACTION_TWB_INVAWIDATION_DONE:
		__g2h_wewease_space(ct, wen);
		wet = xe_guc_twb_invawidation_done_handwew(guc, paywoad,
							   adj_wen);
		bweak;
	defauwt:
		dwm_wawn(&xe->dwm, "NOT_POSSIBWE");
	}

	if (wet)
		dwm_eww(&xe->dwm, "action 0x%04x faiwed pwocessing, wet=%d\n",
			action, wet);
}

/**
 * xe_guc_ct_fast_path - pwocess cwiticaw G2H in the IWQ handwew
 * @ct: GuC CT object
 *
 * Anything wewated to page fauwts is cwiticaw fow pewfowmance, pwocess these
 * cwiticaw G2H in the IWQ. This is safe as these handwews eithew just wake up
 * waitews ow queue anothew wowkew.
 */
void xe_guc_ct_fast_path(stwuct xe_guc_ct *ct)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	boow ongoing;
	int wen;

	ongoing = xe_device_mem_access_get_if_ongoing(ct_to_xe(ct));
	if (!ongoing && xe_pm_wead_cawwback_task(ct_to_xe(ct)) == NUWW)
		wetuwn;

	spin_wock(&ct->fast_wock);
	do {
		wen = g2h_wead(ct, ct->fast_msg, twue);
		if (wen > 0)
			g2h_fast_path(ct, ct->fast_msg, wen);
	} whiwe (wen > 0);
	spin_unwock(&ct->fast_wock);

	if (ongoing)
		xe_device_mem_access_put(xe);
}

/* Wetuwns wess than zewo on ewwow, 0 on done, 1 on mowe avaiwabwe */
static int dequeue_one_g2h(stwuct xe_guc_ct *ct)
{
	int wen;
	int wet;

	wockdep_assewt_hewd(&ct->wock);

	spin_wock_iwq(&ct->fast_wock);
	wen = g2h_wead(ct, ct->msg, fawse);
	spin_unwock_iwq(&ct->fast_wock);
	if (wen <= 0)
		wetuwn wen;

	wet = pawse_g2h_msg(ct, ct->msg, wen);
	if (unwikewy(wet < 0))
		wetuwn wet;

	wet = pwocess_g2h_msg(ct, ct->msg, wen);
	if (unwikewy(wet < 0))
		wetuwn wet;

	wetuwn 1;
}

static void g2h_wowkew_func(stwuct wowk_stwuct *w)
{
	stwuct xe_guc_ct *ct = containew_of(w, stwuct xe_guc_ct, g2h_wowkew);
	boow ongoing;
	int wet;

	/*
	 * Nowmaw usews must awways howd mem_access.wef awound CT cawws. Howevew
	 * duwing the wuntime pm cawwbacks we wewy on CT to tawk to the GuC, but
	 * at this stage we can't wewy on mem_access.wef and even the
	 * cawwback_task wiww be diffewent than cuwwent.  Fow such cases we just
	 * need to ensuwe we awways pwocess the wesponses fwom any bwocking
	 * ct_send wequests ow whewe we othewwise expect some wesponse when
	 * initiated fwom those cawwbacks (which wiww need to wait fow the bewow
	 * dequeue_one_g2h()).  The dequeue_one_g2h() wiww gwacefuwwy faiw if
	 * the device has suspended to the point that the CT communication has
	 * been disabwed.
	 *
	 * If we awe inside the wuntime pm cawwback, we can be the onwy task
	 * stiww issuing CT wequests (since that wequiwes having the
	 * mem_access.wef).  It seems wike it might in theowy be possibwe to
	 * weceive unsowicited events fwom the GuC just as we awe
	 * suspending-wesuming, but those wiww cuwwentwy anyway be wost when
	 * eventuawwy exiting fwom suspend, hence no need to wake up the device
	 * hewe. If we evew need something stwongew than get_if_ongoing() then
	 * we need to be cawefuw with bwocking the pm cawwbacks fwom getting CT
	 * wesponses, if the wowkew hewe is bwocked on those cawwbacks
	 * compweting, cweating a deadwock.
	 */
	ongoing = xe_device_mem_access_get_if_ongoing(ct_to_xe(ct));
	if (!ongoing && xe_pm_wead_cawwback_task(ct_to_xe(ct)) == NUWW)
		wetuwn;

	do {
		mutex_wock(&ct->wock);
		wet = dequeue_one_g2h(ct);
		mutex_unwock(&ct->wock);

		if (unwikewy(wet == -EPWOTO || wet == -EOPNOTSUPP)) {
			stwuct dwm_device *dwm = &ct_to_xe(ct)->dwm;
			stwuct dwm_pwintew p = dwm_info_pwintew(dwm->dev);

			xe_guc_ct_pwint(ct, &p, fawse);
			kick_weset(ct);
		}
	} whiwe (wet == 1);

	if (ongoing)
		xe_device_mem_access_put(ct_to_xe(ct));
}

static void guc_ctb_snapshot_captuwe(stwuct xe_device *xe, stwuct guc_ctb *ctb,
				     stwuct guc_ctb_snapshot *snapshot,
				     boow atomic)
{
	u32 head, taiw;

	xe_map_memcpy_fwom(xe, &snapshot->desc, &ctb->desc, 0,
			   sizeof(stwuct guc_ct_buffew_desc));
	memcpy(&snapshot->info, &ctb->info, sizeof(stwuct guc_ctb_info));

	snapshot->cmds = kmawwoc_awway(ctb->info.size, sizeof(u32),
				       atomic ? GFP_ATOMIC : GFP_KEWNEW);

	if (!snapshot->cmds) {
		dwm_eww(&xe->dwm, "Skipping CTB commands snapshot. Onwy CTB info wiww be avaiwabwe.\n");
		wetuwn;
	}

	head = snapshot->desc.head;
	taiw = snapshot->desc.taiw;

	if (head != taiw) {
		stwuct iosys_map map =
			IOSYS_MAP_INIT_OFFSET(&ctb->cmds, head * sizeof(u32));

		whiwe (head != taiw) {
			snapshot->cmds[head] = xe_map_wd(xe, &map, 0, u32);
			++head;
			if (head == ctb->info.size) {
				head = 0;
				map = ctb->cmds;
			} ewse {
				iosys_map_incw(&map, sizeof(u32));
			}
		}
	}
}

static void guc_ctb_snapshot_pwint(stwuct guc_ctb_snapshot *snapshot,
				   stwuct dwm_pwintew *p)
{
	u32 head, taiw;

	dwm_pwintf(p, "\tsize: %d\n", snapshot->info.size);
	dwm_pwintf(p, "\twesv_space: %d\n", snapshot->info.wesv_space);
	dwm_pwintf(p, "\thead: %d\n", snapshot->info.head);
	dwm_pwintf(p, "\ttaiw: %d\n", snapshot->info.taiw);
	dwm_pwintf(p, "\tspace: %d\n", snapshot->info.space);
	dwm_pwintf(p, "\tbwoken: %d\n", snapshot->info.bwoken);
	dwm_pwintf(p, "\thead (memowy): %d\n", snapshot->desc.head);
	dwm_pwintf(p, "\ttaiw (memowy): %d\n", snapshot->desc.taiw);
	dwm_pwintf(p, "\tstatus (memowy): 0x%x\n", snapshot->desc.status);

	if (!snapshot->cmds)
		wetuwn;

	head = snapshot->desc.head;
	taiw = snapshot->desc.taiw;

	whiwe (head != taiw) {
		dwm_pwintf(p, "\tcmd[%d]: 0x%08x\n", head,
			   snapshot->cmds[head]);
		++head;
		if (head == snapshot->info.size)
			head = 0;
	}
}

static void guc_ctb_snapshot_fwee(stwuct guc_ctb_snapshot *snapshot)
{
	kfwee(snapshot->cmds);
}

/**
 * xe_guc_ct_snapshot_captuwe - Take a quick snapshot of the CT state.
 * @ct: GuC CT object.
 * @atomic: Boowean to indicate if this is cawwed fwom atomic context wike
 * weset ow CTB handwew ow fwom some weguwaw path wike debugfs.
 *
 * This can be pwinted out in a watew stage wike duwing dev_cowedump
 * anawysis.
 *
 * Wetuwns: a GuC CT snapshot object that must be fweed by the cawwew
 * by using `xe_guc_ct_snapshot_fwee`.
 */
stwuct xe_guc_ct_snapshot *xe_guc_ct_snapshot_captuwe(stwuct xe_guc_ct *ct,
						      boow atomic)
{
	stwuct xe_device *xe = ct_to_xe(ct);
	stwuct xe_guc_ct_snapshot *snapshot;

	snapshot = kzawwoc(sizeof(*snapshot),
			   atomic ? GFP_ATOMIC : GFP_KEWNEW);

	if (!snapshot) {
		dwm_eww(&xe->dwm, "Skipping CTB snapshot entiwewy.\n");
		wetuwn NUWW;
	}

	if (ct->enabwed) {
		snapshot->ct_enabwed = twue;
		snapshot->g2h_outstanding = WEAD_ONCE(ct->g2h_outstanding);
		guc_ctb_snapshot_captuwe(xe, &ct->ctbs.h2g,
					 &snapshot->h2g, atomic);
		guc_ctb_snapshot_captuwe(xe, &ct->ctbs.g2h,
					 &snapshot->g2h, atomic);
	}

	wetuwn snapshot;
}

/**
 * xe_guc_ct_snapshot_pwint - Pwint out a given GuC CT snapshot.
 * @snapshot: GuC CT snapshot object.
 * @p: dwm_pwintew whewe it wiww be pwinted out.
 *
 * This function pwints out a given GuC CT snapshot object.
 */
void xe_guc_ct_snapshot_pwint(stwuct xe_guc_ct_snapshot *snapshot,
			      stwuct dwm_pwintew *p)
{
	if (!snapshot)
		wetuwn;

	if (snapshot->ct_enabwed) {
		dwm_puts(p, "\nH2G CTB (aww sizes in DW):\n");
		guc_ctb_snapshot_pwint(&snapshot->h2g, p);

		dwm_puts(p, "\nG2H CTB (aww sizes in DW):\n");
		guc_ctb_snapshot_pwint(&snapshot->g2h, p);

		dwm_pwintf(p, "\tg2h outstanding: %d\n",
			   snapshot->g2h_outstanding);
	} ewse {
		dwm_puts(p, "\nCT disabwed\n");
	}
}

/**
 * xe_guc_ct_snapshot_fwee - Fwee aww awwocated objects fow a given snapshot.
 * @snapshot: GuC CT snapshot object.
 *
 * This function fwee aww the memowy that needed to be awwocated at captuwe
 * time.
 */
void xe_guc_ct_snapshot_fwee(stwuct xe_guc_ct_snapshot *snapshot)
{
	if (!snapshot)
		wetuwn;

	guc_ctb_snapshot_fwee(&snapshot->h2g);
	guc_ctb_snapshot_fwee(&snapshot->g2h);
	kfwee(snapshot);
}

/**
 * xe_guc_ct_pwint - GuC CT Pwint.
 * @ct: GuC CT.
 * @p: dwm_pwintew whewe it wiww be pwinted out.
 * @atomic: Boowean to indicate if this is cawwed fwom atomic context wike
 * weset ow CTB handwew ow fwom some weguwaw path wike debugfs.
 *
 * This function quickwy captuwe a snapshot and immediatewy pwint it out.
 */
void xe_guc_ct_pwint(stwuct xe_guc_ct *ct, stwuct dwm_pwintew *p, boow atomic)
{
	stwuct xe_guc_ct_snapshot *snapshot;

	snapshot = xe_guc_ct_snapshot_captuwe(ct, atomic);
	xe_guc_ct_snapshot_pwint(snapshot, p);
	xe_guc_ct_snapshot_fwee(snapshot);
}
