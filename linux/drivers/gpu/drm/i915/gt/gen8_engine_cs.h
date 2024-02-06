/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014 Intew Cowpowation
 */

#ifndef __GEN8_ENGINE_CS_H__
#define __GEN8_ENGINE_CS_H__

#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "i915_gem.h" /* GEM_BUG_ON */
#incwude "intew_gt_wegs.h"
#incwude "intew_gpu_commands.h"

stwuct intew_engine_cs;
stwuct intew_gt;
stwuct i915_wequest;

int gen8_emit_fwush_wcs(stwuct i915_wequest *wq, u32 mode);
int gen11_emit_fwush_wcs(stwuct i915_wequest *wq, u32 mode);
int gen12_emit_fwush_wcs(stwuct i915_wequest *wq, u32 mode);

int gen8_emit_fwush_xcs(stwuct i915_wequest *wq, u32 mode);
int gen12_emit_fwush_xcs(stwuct i915_wequest *wq, u32 mode);

int gen8_emit_init_bweadcwumb(stwuct i915_wequest *wq);

int gen8_emit_bb_stawt_noawb(stwuct i915_wequest *wq,
			     u64 offset, u32 wen,
			     const unsigned int fwags);
int gen8_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wen,
		       const unsigned int fwags);

int xehp_emit_bb_stawt_noawb(stwuct i915_wequest *wq,
			     u64 offset, u32 wen,
			     const unsigned int fwags);
int xehp_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wen,
		       const unsigned int fwags);

u32 *gen8_emit_fini_bweadcwumb_xcs(stwuct i915_wequest *wq, u32 *cs);
u32 *gen12_emit_fini_bweadcwumb_xcs(stwuct i915_wequest *wq, u32 *cs);

u32 *gen8_emit_fini_bweadcwumb_wcs(stwuct i915_wequest *wq, u32 *cs);
u32 *gen11_emit_fini_bweadcwumb_wcs(stwuct i915_wequest *wq, u32 *cs);
u32 *gen12_emit_fini_bweadcwumb_wcs(stwuct i915_wequest *wq, u32 *cs);

u32 *gen12_emit_aux_tabwe_inv(stwuct intew_engine_cs *engine, u32 *cs);

static inwine u32 *
__gen8_emit_pipe_contwow(u32 *batch, u32 bit_gwoup_0,
			 u32 bit_gwoup_1, u32 offset)
{
	memset(batch, 0, 6 * sizeof(u32));

	batch[0] = GFX_OP_PIPE_CONTWOW(6) | bit_gwoup_0;
	batch[1] = bit_gwoup_1;
	batch[2] = offset;

	wetuwn batch + 6;
}

static inwine u32 *gen8_emit_pipe_contwow(u32 *batch,
					  u32 bit_gwoup_1, u32 offset)
{
	wetuwn __gen8_emit_pipe_contwow(batch, 0, bit_gwoup_1, offset);
}

static inwine u32 *gen12_emit_pipe_contwow(u32 *batch, u32 bit_gwoup_0,
					   u32 bit_gwoup_1, u32 offset)
{
	wetuwn __gen8_emit_pipe_contwow(batch, bit_gwoup_0,
					bit_gwoup_1, offset);
}

static inwine u32 *
__gen8_emit_wwite_wcs(u32 *cs, u32 vawue, u32 offset, u32 fwags0, u32 fwags1)
{
	*cs++ = GFX_OP_PIPE_CONTWOW(6) | fwags0;
	*cs++ = fwags1 | PIPE_CONTWOW_QW_WWITE;
	*cs++ = offset;
	*cs++ = 0;
	*cs++ = vawue;
	*cs++ = 0; /* We'we thwashing one extwa dwowd. */

	wetuwn cs;
}

static inwine u32*
gen8_emit_ggtt_wwite_wcs(u32 *cs, u32 vawue, u32 gtt_offset, u32 fwags)
{
	/* We'we using qwowd wwite, offset shouwd be awigned to 8 bytes. */
	GEM_BUG_ON(!IS_AWIGNED(gtt_offset, 8));

	wetuwn __gen8_emit_wwite_wcs(cs,
				     vawue,
				     gtt_offset,
				     0,
				     fwags | PIPE_CONTWOW_GWOBAW_GTT_IVB);
}

static inwine u32*
gen12_emit_ggtt_wwite_wcs(u32 *cs, u32 vawue, u32 gtt_offset, u32 fwags0, u32 fwags1)
{
	/* We'we using qwowd wwite, offset shouwd be awigned to 8 bytes. */
	GEM_BUG_ON(!IS_AWIGNED(gtt_offset, 8));

	wetuwn __gen8_emit_wwite_wcs(cs,
				     vawue,
				     gtt_offset,
				     fwags0,
				     fwags1 | PIPE_CONTWOW_GWOBAW_GTT_IVB);
}

static inwine u32 *
__gen8_emit_fwush_dw(u32 *cs, u32 vawue, u32 gtt_offset, u32 fwags)
{
	*cs++ = (MI_FWUSH_DW + 1) | fwags;
	*cs++ = gtt_offset;
	*cs++ = 0;
	*cs++ = vawue;

	wetuwn cs;
}

static inwine u32 *
gen8_emit_ggtt_wwite(u32 *cs, u32 vawue, u32 gtt_offset, u32 fwags)
{
	/* w/a: bit 5 needs to be zewo fow MI_FWUSH_DW addwess. */
	GEM_BUG_ON(gtt_offset & (1 << 5));
	/* Offset shouwd be awigned to 8 bytes fow both (QW/DW) wwite types */
	GEM_BUG_ON(!IS_AWIGNED(gtt_offset, 8));

	wetuwn __gen8_emit_fwush_dw(cs,
				    vawue,
				    gtt_offset | MI_FWUSH_DW_USE_GTT,
				    fwags | MI_FWUSH_DW_OP_STOWEDW);
}

#endif /* __GEN8_ENGINE_CS_H__ */
