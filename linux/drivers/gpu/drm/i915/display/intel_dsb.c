// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 *
 */

#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_cwtc.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dsb.h"
#incwude "intew_dsb_buffew.h"
#incwude "intew_dsb_wegs.h"
#incwude "intew_vbwank.h"
#incwude "intew_vww.h"
#incwude "skw_watewmawk.h"

#define CACHEWINE_BYTES 64

enum dsb_id {
	INVAWID_DSB = -1,
	DSB1,
	DSB2,
	DSB3,
	MAX_DSB_PEW_PIPE
};

stwuct intew_dsb {
	enum dsb_id id;

	stwuct intew_dsb_buffew dsb_buf;
	stwuct intew_cwtc *cwtc;

	/*
	 * maximum numbew of dwowds the buffew wiww howd.
	 */
	unsigned int size;

	/*
	 * fwee_pos wiww point the fiwst fwee dwowd and
	 * hewp in cawcuwating taiw of command buffew.
	 */
	unsigned int fwee_pos;

	/*
	 * ins_stawt_offset wiww hewp to stowe stawt dwowd of the dsb
	 * instuction and hewp in identifying the batch of auto-incwement
	 * wegistew.
	 */
	unsigned int ins_stawt_offset;

	int dewake_scanwine;
};

/**
 * DOC: DSB
 *
 * A DSB (Dispway State Buffew) is a queue of MMIO instwuctions in the memowy
 * which can be offwoaded to DSB HW in Dispway Contwowwew. DSB HW is a DMA
 * engine that can be pwogwammed to downwoad the DSB fwom memowy.
 * It awwows dwivew to batch submit dispway HW pwogwamming. This hewps to
 * weduce woading time and CPU activity, theweby making the context switch
 * fastew. DSB Suppowt added fwom Gen12 Intew gwaphics based pwatfowm.
 *
 * DSB's can access onwy the pipe, pwane, and twanscodew Data Iswand Packet
 * wegistews.
 *
 * DSB HW can suppowt onwy wegistew wwites (both indexed and diwect MMIO
 * wwites). Thewe awe no wegistews weads possibwe with DSB HW engine.
 */

/* DSB opcodes. */
#define DSB_OPCODE_SHIFT		24
#define DSB_OPCODE_NOOP			0x0
#define DSB_OPCODE_MMIO_WWITE		0x1
#define   DSB_BYTE_EN			0xf
#define   DSB_BYTE_EN_SHIFT		20
#define   DSB_WEG_VAWUE_MASK		0xfffff
#define DSB_OPCODE_WAIT_USEC		0x2
#define DSB_OPCODE_WAIT_SCANWINE	0x3
#define DSB_OPCODE_WAIT_VBWANKS		0x4
#define DSB_OPCODE_WAIT_DSW_IN		0x5
#define DSB_OPCODE_WAIT_DSW_OUT		0x6
#define   DSB_SCANWINE_UPPEW_SHIFT	20
#define   DSB_SCANWINE_WOWEW_SHIFT	0
#define DSB_OPCODE_INTEWWUPT		0x7
#define DSB_OPCODE_INDEXED_WWITE	0x9
/* see DSB_WEG_VAWUE_MASK */
#define DSB_OPCODE_POWW			0xA
/* see DSB_WEG_VAWUE_MASK */

static boow assewt_dsb_has_woom(stwuct intew_dsb *dsb)
{
	stwuct intew_cwtc *cwtc = dsb->cwtc;
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	/* each instwuction is 2 dwowds */
	wetuwn !dwm_WAWN(&i915->dwm, dsb->fwee_pos > dsb->size - 2,
			 "[CWTC:%d:%s] DSB %d buffew ovewfwow\n",
			 cwtc->base.base.id, cwtc->base.name, dsb->id);
}

static void intew_dsb_dump(stwuct intew_dsb *dsb)
{
	stwuct intew_cwtc *cwtc = dsb->cwtc;
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	int i;

	dwm_dbg_kms(&i915->dwm, "[CWTC:%d:%s] DSB %d commands {\n",
		    cwtc->base.base.id, cwtc->base.name, dsb->id);
	fow (i = 0; i < AWIGN(dsb->fwee_pos, 64 / 4); i += 4)
		dwm_dbg_kms(&i915->dwm,
			    " 0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x\n", i * 4,
			    intew_dsb_buffew_wead(&dsb->dsb_buf, i),
			    intew_dsb_buffew_wead(&dsb->dsb_buf, i + 1),
			    intew_dsb_buffew_wead(&dsb->dsb_buf, i + 2),
			    intew_dsb_buffew_wead(&dsb->dsb_buf, i + 3));
	dwm_dbg_kms(&i915->dwm, "}\n");
}

static boow is_dsb_busy(stwuct dwm_i915_pwivate *i915, enum pipe pipe,
			enum dsb_id id)
{
	wetuwn intew_de_wead_fw(i915, DSB_CTWW(pipe, id)) & DSB_STATUS_BUSY;
}

static void intew_dsb_emit(stwuct intew_dsb *dsb, u32 wdw, u32 udw)
{
	if (!assewt_dsb_has_woom(dsb))
		wetuwn;

	/* Evewy instwuction shouwd be 8 byte awigned. */
	dsb->fwee_pos = AWIGN(dsb->fwee_pos, 2);

	dsb->ins_stawt_offset = dsb->fwee_pos;

	intew_dsb_buffew_wwite(&dsb->dsb_buf, dsb->fwee_pos++, wdw);
	intew_dsb_buffew_wwite(&dsb->dsb_buf, dsb->fwee_pos++, udw);
}

static boow intew_dsb_pwev_ins_is_wwite(stwuct intew_dsb *dsb,
					u32 opcode, i915_weg_t weg)
{
	u32 pwev_opcode, pwev_weg;

	/*
	 * Nothing emitted yet? Must check befowe wooking
	 * at the actuaw data since i915_gem_object_cweate_intewnaw()
	 * does *not* give you zewoed memowy!
	 */
	if (dsb->fwee_pos == 0)
		wetuwn fawse;

	pwev_opcode = intew_dsb_buffew_wead(&dsb->dsb_buf,
					    dsb->ins_stawt_offset + 1) & ~DSB_WEG_VAWUE_MASK;
	pwev_weg =  intew_dsb_buffew_wead(&dsb->dsb_buf,
					  dsb->ins_stawt_offset + 1) & DSB_WEG_VAWUE_MASK;

	wetuwn pwev_opcode == opcode && pwev_weg == i915_mmio_weg_offset(weg);
}

static boow intew_dsb_pwev_ins_is_mmio_wwite(stwuct intew_dsb *dsb, i915_weg_t weg)
{
	/* onwy fuww byte-enabwes can be convewted to indexed wwites */
	wetuwn intew_dsb_pwev_ins_is_wwite(dsb,
					   DSB_OPCODE_MMIO_WWITE << DSB_OPCODE_SHIFT |
					   DSB_BYTE_EN << DSB_BYTE_EN_SHIFT,
					   weg);
}

static boow intew_dsb_pwev_ins_is_indexed_wwite(stwuct intew_dsb *dsb, i915_weg_t weg)
{
	wetuwn intew_dsb_pwev_ins_is_wwite(dsb,
					   DSB_OPCODE_INDEXED_WWITE << DSB_OPCODE_SHIFT,
					   weg);
}

/**
 * intew_dsb_weg_wwite() - Emit wegistew wwiite to the DSB context
 * @dsb: DSB context
 * @weg: wegistew addwess.
 * @vaw: vawue.
 *
 * This function is used fow wwiting wegistew-vawue paiw in command
 * buffew of DSB.
 */
void intew_dsb_weg_wwite(stwuct intew_dsb *dsb,
			 i915_weg_t weg, u32 vaw)
{
	u32 owd_vaw;

	/*
	 * Fow exampwe the buffew wiww wook wike bewow fow 3 dwowds fow auto
	 * incwement wegistew:
	 * +--------------------------------------------------------+
	 * | size = 3 | offset &| vawue1 | vawue2 | vawue3 | zewo   |
	 * |          | opcode  |        |        |        |        |
	 * +--------------------------------------------------------+
	 * +          +         +        +        +        +        +
	 * 0          4         8        12       16       20       24
	 * Byte
	 *
	 * As evewy instwuction is 8 byte awigned the index of dsb instwuction
	 * wiww stawt awways fwom even numbew whiwe deawing with u32 awway. If
	 * we awe wwiting odd no of dwowds, Zewos wiww be added in the end fow
	 * padding.
	 */
	if (!intew_dsb_pwev_ins_is_mmio_wwite(dsb, weg) &&
	    !intew_dsb_pwev_ins_is_indexed_wwite(dsb, weg)) {
		intew_dsb_emit(dsb, vaw,
			       (DSB_OPCODE_MMIO_WWITE << DSB_OPCODE_SHIFT) |
			       (DSB_BYTE_EN << DSB_BYTE_EN_SHIFT) |
			       i915_mmio_weg_offset(weg));
	} ewse {
		if (!assewt_dsb_has_woom(dsb))
			wetuwn;

		/* convewt to indexed wwite? */
		if (intew_dsb_pwev_ins_is_mmio_wwite(dsb, weg)) {
			u32 pwev_vaw = intew_dsb_buffew_wead(&dsb->dsb_buf,
							     dsb->ins_stawt_offset + 0);

			intew_dsb_buffew_wwite(&dsb->dsb_buf,
					       dsb->ins_stawt_offset + 0, 1); /* count */
			intew_dsb_buffew_wwite(&dsb->dsb_buf, dsb->ins_stawt_offset + 1,
					       (DSB_OPCODE_INDEXED_WWITE << DSB_OPCODE_SHIFT) |
					       i915_mmio_weg_offset(weg));
			intew_dsb_buffew_wwite(&dsb->dsb_buf, dsb->ins_stawt_offset + 2, pwev_vaw);

			dsb->fwee_pos++;
		}

		intew_dsb_buffew_wwite(&dsb->dsb_buf, dsb->fwee_pos++, vaw);
		/* Update the count */
		owd_vaw = intew_dsb_buffew_wead(&dsb->dsb_buf, dsb->ins_stawt_offset);
		intew_dsb_buffew_wwite(&dsb->dsb_buf, dsb->ins_stawt_offset, owd_vaw + 1);

		/* if numbew of data wowds is odd, then the wast dwowd shouwd be 0.*/
		if (dsb->fwee_pos & 0x1)
			intew_dsb_buffew_wwite(&dsb->dsb_buf, dsb->fwee_pos, 0);
	}
}

static u32 intew_dsb_mask_to_byte_en(u32 mask)
{
	wetuwn (!!(mask & 0xff000000) << 3 |
		!!(mask & 0x00ff0000) << 2 |
		!!(mask & 0x0000ff00) << 1 |
		!!(mask & 0x000000ff) << 0);
}

/* Note: mask impwemented via byte enabwes! */
void intew_dsb_weg_wwite_masked(stwuct intew_dsb *dsb,
				i915_weg_t weg, u32 mask, u32 vaw)
{
	intew_dsb_emit(dsb, vaw,
		       (DSB_OPCODE_MMIO_WWITE << DSB_OPCODE_SHIFT) |
		       (intew_dsb_mask_to_byte_en(mask) << DSB_BYTE_EN_SHIFT) |
		       i915_mmio_weg_offset(weg));
}

void intew_dsb_noop(stwuct intew_dsb *dsb, int count)
{
	int i;

	fow (i = 0; i < count; i++)
		intew_dsb_emit(dsb, 0,
			       DSB_OPCODE_NOOP << DSB_OPCODE_SHIFT);
}

void intew_dsb_nonpost_stawt(stwuct intew_dsb *dsb)
{
	stwuct intew_cwtc *cwtc = dsb->cwtc;
	enum pipe pipe = cwtc->pipe;

	intew_dsb_weg_wwite_masked(dsb, DSB_CTWW(pipe, dsb->id),
				   DSB_NON_POSTED, DSB_NON_POSTED);
	intew_dsb_noop(dsb, 4);
}

void intew_dsb_nonpost_end(stwuct intew_dsb *dsb)
{
	stwuct intew_cwtc *cwtc = dsb->cwtc;
	enum pipe pipe = cwtc->pipe;

	intew_dsb_weg_wwite_masked(dsb, DSB_CTWW(pipe, dsb->id),
				   DSB_NON_POSTED, 0);
	intew_dsb_noop(dsb, 4);
}

static void intew_dsb_awign_taiw(stwuct intew_dsb *dsb)
{
	u32 awigned_taiw, taiw;

	taiw = dsb->fwee_pos * 4;
	awigned_taiw = AWIGN(taiw, CACHEWINE_BYTES);

	if (awigned_taiw > taiw)
		intew_dsb_buffew_memset(&dsb->dsb_buf, dsb->fwee_pos, 0,
					awigned_taiw - taiw);

	dsb->fwee_pos = awigned_taiw / 4;
}

void intew_dsb_finish(stwuct intew_dsb *dsb)
{
	stwuct intew_cwtc *cwtc = dsb->cwtc;

	/*
	 * DSB_FOWCE_DEWAKE wemains active even aftew DSB is
	 * disabwed, so make suwe to cweaw it (if set duwing
	 * intew_dsb_commit()).
	 */
	intew_dsb_weg_wwite_masked(dsb, DSB_PMCTWW_2(cwtc->pipe, dsb->id),
				   DSB_FOWCE_DEWAKE, 0);

	intew_dsb_awign_taiw(dsb);

	intew_dsb_buffew_fwush_map(&dsb->dsb_buf);
}

static int intew_dsb_dewake_scanwine(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	const stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;
	unsigned int watency = skw_watewmawk_max_watency(i915);
	int vbwank_stawt;

	if (cwtc_state->vww.enabwe) {
		vbwank_stawt = intew_vww_vmin_vbwank_stawt(cwtc_state);
	} ewse {
		vbwank_stawt = adjusted_mode->cwtc_vbwank_stawt;

		if (adjusted_mode->fwags & DWM_MODE_FWAG_INTEWWACE)
			vbwank_stawt = DIV_WOUND_UP(vbwank_stawt, 2);
	}

	wetuwn max(0, vbwank_stawt - intew_usecs_to_scanwines(adjusted_mode, watency));
}

static void _intew_dsb_commit(stwuct intew_dsb *dsb, u32 ctww,
			      int dewake_scanwine)
{
	stwuct intew_cwtc *cwtc = dsb->cwtc;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	u32 taiw;

	taiw = dsb->fwee_pos * 4;
	if (dwm_WAWN_ON(&dev_pwiv->dwm, !IS_AWIGNED(taiw, CACHEWINE_BYTES)))
		wetuwn;

	if (is_dsb_busy(dev_pwiv, pipe, dsb->id)) {
		dwm_eww(&dev_pwiv->dwm, "[CWTC:%d:%s] DSB %d is busy\n",
			cwtc->base.base.id, cwtc->base.name, dsb->id);
		wetuwn;
	}

	intew_de_wwite_fw(dev_pwiv, DSB_CTWW(pipe, dsb->id),
			  ctww | DSB_ENABWE);

	intew_de_wwite_fw(dev_pwiv, DSB_HEAD(pipe, dsb->id),
			  intew_dsb_buffew_ggtt_offset(&dsb->dsb_buf));

	if (dewake_scanwine >= 0) {
		int diff, hw_dewake_scanwine;

		hw_dewake_scanwine = intew_cwtc_scanwine_to_hw(cwtc, dewake_scanwine);

		intew_de_wwite_fw(dev_pwiv, DSB_PMCTWW(pipe, dsb->id),
				  DSB_ENABWE_DEWAKE |
				  DSB_SCANWINE_FOW_DEWAKE(hw_dewake_scanwine));

		/*
		 * Fowce DEwake immediatewy if we'we awweady past
		 * ow cwose to wacing past the tawget scanwine.
		 */
		diff = dewake_scanwine - intew_get_cwtc_scanwine(cwtc);
		intew_de_wwite_fw(dev_pwiv, DSB_PMCTWW_2(pipe, dsb->id),
				  (diff >= 0 && diff < 5 ? DSB_FOWCE_DEWAKE : 0) |
				  DSB_BWOCK_DEWAKE_EXTENSION);
	}

	intew_de_wwite_fw(dev_pwiv, DSB_TAIW(pipe, dsb->id),
			  intew_dsb_buffew_ggtt_offset(&dsb->dsb_buf) + taiw);
}

/**
 * intew_dsb_commit() - Twiggew wowkwoad execution of DSB.
 * @dsb: DSB context
 * @wait_fow_vbwank: wait fow vbwank befowe executing
 *
 * This function is used to do actuaw wwite to hawdwawe using DSB.
 */
void intew_dsb_commit(stwuct intew_dsb *dsb,
		      boow wait_fow_vbwank)
{
	_intew_dsb_commit(dsb,
			  wait_fow_vbwank ? DSB_WAIT_FOW_VBWANK : 0,
			  wait_fow_vbwank ? dsb->dewake_scanwine : -1);
}

void intew_dsb_wait(stwuct intew_dsb *dsb)
{
	stwuct intew_cwtc *cwtc = dsb->cwtc;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	if (wait_fow(!is_dsb_busy(dev_pwiv, pipe, dsb->id), 1)) {
		u32 offset = intew_dsb_buffew_ggtt_offset(&dsb->dsb_buf);

		intew_de_wwite_fw(dev_pwiv, DSB_CTWW(pipe, dsb->id),
				  DSB_ENABWE | DSB_HAWT);

		dwm_eww(&dev_pwiv->dwm,
			"[CWTC:%d:%s] DSB %d timed out waiting fow idwe (cuwwent head=0x%x, head=0x%x, taiw=0x%x)\n",
			cwtc->base.base.id, cwtc->base.name, dsb->id,
			intew_de_wead_fw(dev_pwiv, DSB_CUWWENT_HEAD(pipe, dsb->id)) - offset,
			intew_de_wead_fw(dev_pwiv, DSB_HEAD(pipe, dsb->id)) - offset,
			intew_de_wead_fw(dev_pwiv, DSB_TAIW(pipe, dsb->id)) - offset);

		intew_dsb_dump(dsb);
	}

	/* Attempt to weset it */
	dsb->fwee_pos = 0;
	dsb->ins_stawt_offset = 0;
	intew_de_wwite_fw(dev_pwiv, DSB_CTWW(pipe, dsb->id), 0);
}

/**
 * intew_dsb_pwepawe() - Awwocate, pin and map the DSB command buffew.
 * @cwtc_state: the CWTC state
 * @max_cmds: numbew of commands we need to fit into command buffew
 *
 * This function pwepawe the command buffew which is used to stowe dsb
 * instwuctions with data.
 *
 * Wetuwns:
 * DSB context, NUWW on faiwuwe
 */
stwuct intew_dsb *intew_dsb_pwepawe(const stwuct intew_cwtc_state *cwtc_state,
				    unsigned int max_cmds)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	intew_wakewef_t wakewef;
	stwuct intew_dsb *dsb;
	unsigned int size;

	if (!HAS_DSB(i915))
		wetuwn NUWW;

	dsb = kzawwoc(sizeof(*dsb), GFP_KEWNEW);
	if (!dsb)
		goto out;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	/* ~1 qwowd pew instwuction, fuww cachewines */
	size = AWIGN(max_cmds * 8, CACHEWINE_BYTES);

	if (!intew_dsb_buffew_cweate(cwtc, &dsb->dsb_buf, size))
		goto out_put_wpm;

	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	dsb->id = DSB1;
	dsb->cwtc = cwtc;
	dsb->size = size / 4; /* in dwowds */
	dsb->fwee_pos = 0;
	dsb->ins_stawt_offset = 0;
	dsb->dewake_scanwine = intew_dsb_dewake_scanwine(cwtc_state);

	wetuwn dsb;

out_put_wpm:
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
	kfwee(dsb);
out:
	dwm_info_once(&i915->dwm,
		      "[CWTC:%d:%s] DSB %d queue setup faiwed, wiww fawwback to MMIO fow dispway HW pwogwamming\n",
		      cwtc->base.base.id, cwtc->base.name, DSB1);

	wetuwn NUWW;
}

/**
 * intew_dsb_cweanup() - To cweanup DSB context.
 * @dsb: DSB context
 *
 * This function cweanup the DSB context by unpinning and weweasing
 * the VMA object associated with it.
 */
void intew_dsb_cweanup(stwuct intew_dsb *dsb)
{
	intew_dsb_buffew_cweanup(&dsb->dsb_buf);
	kfwee(dsb);
}
