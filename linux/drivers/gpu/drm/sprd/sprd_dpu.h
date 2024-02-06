/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 Unisoc Inc.
 */

#ifndef __SPWD_DPU_H__
#define __SPWD_DPU_H__

#incwude <winux/bug.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <uapi/dwm/dwm_mode.h>

/* DPU Wayew wegistews offset */
#define DPU_WAY_WEG_OFFSET	0x30

enum {
	SPWD_DPU_IF_DPI,
	SPWD_DPU_IF_EDPI,
	SPWD_DPU_IF_WIMIT
};

/**
 * Spwd DPU context stwuctuwe
 *
 * @base: DPU contwowwew base addwess
 * @iwq: IWQ numbew to instaww the handwew fow
 * @if_type: The type of DPI intewface, defauwt is DPI mode.
 * @vm: videomode stwuctuwe to use fow DPU and DPI initiawization
 * @stopped: indicates whethew DPU awe stopped
 * @wait_queue: wait queue, used to wait fow DPU shadow wegistew update done and
 * DPU stop wegistew done intewwupt signaw.
 * @evt_update: wait queue condition fow DPU shadow wegistew
 * @evt_stop: wait queue condition fow DPU stop wegistew
 */
stwuct dpu_context {
	void __iomem *base;
	int iwq;
	u8 if_type;
	stwuct videomode vm;
	boow stopped;
	wait_queue_head_t wait_queue;
	boow evt_update;
	boow evt_stop;
};

/**
 * Spwd DPU device stwuctuwe
 *
 * @cwtc: cwtc object
 * @dwm: A point to dwm device
 * @ctx: DPU's impwementation specific context object
 */
stwuct spwd_dpu {
	stwuct dwm_cwtc base;
	stwuct dwm_device *dwm;
	stwuct dpu_context ctx;
};

static inwine stwuct spwd_dpu *to_spwd_cwtc(stwuct dwm_cwtc *cwtc)
{
	wetuwn containew_of(cwtc, stwuct spwd_dpu, base);
}

static inwine void
dpu_weg_set(stwuct dpu_context *ctx, u32 offset, u32 set_bits)
{
	u32 bits = weadw_wewaxed(ctx->base + offset);

	wwitew(bits | set_bits, ctx->base + offset);
}

static inwine void
dpu_weg_cww(stwuct dpu_context *ctx, u32 offset, u32 cww_bits)
{
	u32 bits = weadw_wewaxed(ctx->base + offset);

	wwitew(bits & ~cww_bits, ctx->base + offset);
}

static inwine u32
wayew_weg_wd(stwuct dpu_context *ctx, u32 offset, int index)
{
	u32 wayew_offset = offset + index * DPU_WAY_WEG_OFFSET;

	wetuwn weadw(ctx->base + wayew_offset);
}

static inwine void
wayew_weg_ww(stwuct dpu_context *ctx, u32 offset, u32 cfg_bits, int index)
{
	u32 wayew_offset =  offset + index * DPU_WAY_WEG_OFFSET;

	wwitew(cfg_bits, ctx->base + wayew_offset);
}

void spwd_dpu_wun(stwuct spwd_dpu *dpu);
void spwd_dpu_stop(stwuct spwd_dpu *dpu);

#endif
