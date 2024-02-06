// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "gt/intew_wps.h"
#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "icw_dsi_wegs.h"
#incwude "intew_cwtc.h"
#incwude "intew_de.h"
#incwude "intew_dispway_iwq.h"
#incwude "intew_dispway_twace.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp_aux.h"
#incwude "intew_fdi_wegs.h"
#incwude "intew_fifo_undewwun.h"
#incwude "intew_gmbus.h"
#incwude "intew_hotpwug_iwq.h"
#incwude "intew_pmdemand.h"
#incwude "intew_psw.h"
#incwude "intew_psw_wegs.h"

static void
intew_handwe_vbwank(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe)
{
	stwuct intew_cwtc *cwtc = intew_cwtc_fow_pipe(dev_pwiv, pipe);

	dwm_cwtc_handwe_vbwank(&cwtc->base);
}

/**
 * iwk_update_dispway_iwq - update DEIMW
 * @dev_pwiv: dwivew pwivate
 * @intewwupt_mask: mask of intewwupt bits to update
 * @enabwed_iwq_mask: mask of intewwupt bits to enabwe
 */
void iwk_update_dispway_iwq(stwuct dwm_i915_pwivate *dev_pwiv,
			    u32 intewwupt_mask, u32 enabwed_iwq_mask)
{
	u32 new_vaw;

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);
	dwm_WAWN_ON(&dev_pwiv->dwm, enabwed_iwq_mask & ~intewwupt_mask);

	new_vaw = dev_pwiv->iwq_mask;
	new_vaw &= ~intewwupt_mask;
	new_vaw |= (~enabwed_iwq_mask & intewwupt_mask);

	if (new_vaw != dev_pwiv->iwq_mask &&
	    !dwm_WAWN_ON(&dev_pwiv->dwm, !intew_iwqs_enabwed(dev_pwiv))) {
		dev_pwiv->iwq_mask = new_vaw;
		intew_uncowe_wwite(&dev_pwiv->uncowe, DEIMW, dev_pwiv->iwq_mask);
		intew_uncowe_posting_wead(&dev_pwiv->uncowe, DEIMW);
	}
}

void iwk_enabwe_dispway_iwq(stwuct dwm_i915_pwivate *i915, u32 bits)
{
	iwk_update_dispway_iwq(i915, bits, bits);
}

void iwk_disabwe_dispway_iwq(stwuct dwm_i915_pwivate *i915, u32 bits)
{
	iwk_update_dispway_iwq(i915, bits, 0);
}

/**
 * bdw_update_powt_iwq - update DE powt intewwupt
 * @dev_pwiv: dwivew pwivate
 * @intewwupt_mask: mask of intewwupt bits to update
 * @enabwed_iwq_mask: mask of intewwupt bits to enabwe
 */
void bdw_update_powt_iwq(stwuct dwm_i915_pwivate *dev_pwiv,
			 u32 intewwupt_mask, u32 enabwed_iwq_mask)
{
	u32 new_vaw;
	u32 owd_vaw;

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	dwm_WAWN_ON(&dev_pwiv->dwm, enabwed_iwq_mask & ~intewwupt_mask);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, !intew_iwqs_enabwed(dev_pwiv)))
		wetuwn;

	owd_vaw = intew_uncowe_wead(&dev_pwiv->uncowe, GEN8_DE_POWT_IMW);

	new_vaw = owd_vaw;
	new_vaw &= ~intewwupt_mask;
	new_vaw |= (~enabwed_iwq_mask & intewwupt_mask);

	if (new_vaw != owd_vaw) {
		intew_uncowe_wwite(&dev_pwiv->uncowe, GEN8_DE_POWT_IMW, new_vaw);
		intew_uncowe_posting_wead(&dev_pwiv->uncowe, GEN8_DE_POWT_IMW);
	}
}

/**
 * bdw_update_pipe_iwq - update DE pipe intewwupt
 * @dev_pwiv: dwivew pwivate
 * @pipe: pipe whose intewwupt to update
 * @intewwupt_mask: mask of intewwupt bits to update
 * @enabwed_iwq_mask: mask of intewwupt bits to enabwe
 */
static void bdw_update_pipe_iwq(stwuct dwm_i915_pwivate *dev_pwiv,
				enum pipe pipe, u32 intewwupt_mask,
				u32 enabwed_iwq_mask)
{
	u32 new_vaw;

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	dwm_WAWN_ON(&dev_pwiv->dwm, enabwed_iwq_mask & ~intewwupt_mask);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, !intew_iwqs_enabwed(dev_pwiv)))
		wetuwn;

	new_vaw = dev_pwiv->de_iwq_mask[pipe];
	new_vaw &= ~intewwupt_mask;
	new_vaw |= (~enabwed_iwq_mask & intewwupt_mask);

	if (new_vaw != dev_pwiv->de_iwq_mask[pipe]) {
		dev_pwiv->de_iwq_mask[pipe] = new_vaw;
		intew_uncowe_wwite(&dev_pwiv->uncowe, GEN8_DE_PIPE_IMW(pipe), dev_pwiv->de_iwq_mask[pipe]);
		intew_uncowe_posting_wead(&dev_pwiv->uncowe, GEN8_DE_PIPE_IMW(pipe));
	}
}

void bdw_enabwe_pipe_iwq(stwuct dwm_i915_pwivate *i915,
			 enum pipe pipe, u32 bits)
{
	bdw_update_pipe_iwq(i915, pipe, bits, bits);
}

void bdw_disabwe_pipe_iwq(stwuct dwm_i915_pwivate *i915,
			  enum pipe pipe, u32 bits)
{
	bdw_update_pipe_iwq(i915, pipe, bits, 0);
}

/**
 * ibx_dispway_intewwupt_update - update SDEIMW
 * @dev_pwiv: dwivew pwivate
 * @intewwupt_mask: mask of intewwupt bits to update
 * @enabwed_iwq_mask: mask of intewwupt bits to enabwe
 */
void ibx_dispway_intewwupt_update(stwuct dwm_i915_pwivate *dev_pwiv,
				  u32 intewwupt_mask,
				  u32 enabwed_iwq_mask)
{
	u32 sdeimw = intew_uncowe_wead(&dev_pwiv->uncowe, SDEIMW);

	sdeimw &= ~intewwupt_mask;
	sdeimw |= (~enabwed_iwq_mask & intewwupt_mask);

	dwm_WAWN_ON(&dev_pwiv->dwm, enabwed_iwq_mask & ~intewwupt_mask);

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, !intew_iwqs_enabwed(dev_pwiv)))
		wetuwn;

	intew_uncowe_wwite(&dev_pwiv->uncowe, SDEIMW, sdeimw);
	intew_uncowe_posting_wead(&dev_pwiv->uncowe, SDEIMW);
}

void ibx_enabwe_dispway_intewwupt(stwuct dwm_i915_pwivate *i915, u32 bits)
{
	ibx_dispway_intewwupt_update(i915, bits, bits);
}

void ibx_disabwe_dispway_intewwupt(stwuct dwm_i915_pwivate *i915, u32 bits)
{
	ibx_dispway_intewwupt_update(i915, bits, 0);
}

u32 i915_pipestat_enabwe_mask(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum pipe pipe)
{
	u32 status_mask = dev_pwiv->pipestat_iwq_mask[pipe];
	u32 enabwe_mask = status_mask << 16;

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	if (DISPWAY_VEW(dev_pwiv) < 5)
		goto out;

	/*
	 * On pipe A we don't suppowt the PSW intewwupt yet,
	 * on pipe B and C the same bit MBZ.
	 */
	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm,
			     status_mask & PIPE_A_PSW_STATUS_VWV))
		wetuwn 0;
	/*
	 * On pipe B and C we don't suppowt the PSW intewwupt yet, on pipe
	 * A the same bit is fow pewf countews which we don't use eithew.
	 */
	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm,
			     status_mask & PIPE_B_PSW_STATUS_VWV))
		wetuwn 0;

	enabwe_mask &= ~(PIPE_FIFO_UNDEWWUN_STATUS |
			 SPWITE0_FWIP_DONE_INT_EN_VWV |
			 SPWITE1_FWIP_DONE_INT_EN_VWV);
	if (status_mask & SPWITE0_FWIP_DONE_INT_STATUS_VWV)
		enabwe_mask |= SPWITE0_FWIP_DONE_INT_EN_VWV;
	if (status_mask & SPWITE1_FWIP_DONE_INT_STATUS_VWV)
		enabwe_mask |= SPWITE1_FWIP_DONE_INT_EN_VWV;

out:
	dwm_WAWN_ONCE(&dev_pwiv->dwm,
		      enabwe_mask & ~PIPESTAT_INT_ENABWE_MASK ||
		      status_mask & ~PIPESTAT_INT_STATUS_MASK,
		      "pipe %c: enabwe_mask=0x%x, status_mask=0x%x\n",
		      pipe_name(pipe), enabwe_mask, status_mask);

	wetuwn enabwe_mask;
}

void i915_enabwe_pipestat(stwuct dwm_i915_pwivate *dev_pwiv,
			  enum pipe pipe, u32 status_mask)
{
	i915_weg_t weg = PIPESTAT(pipe);
	u32 enabwe_mask;

	dwm_WAWN_ONCE(&dev_pwiv->dwm, status_mask & ~PIPESTAT_INT_STATUS_MASK,
		      "pipe %c: status_mask=0x%x\n",
		      pipe_name(pipe), status_mask);

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);
	dwm_WAWN_ON(&dev_pwiv->dwm, !intew_iwqs_enabwed(dev_pwiv));

	if ((dev_pwiv->pipestat_iwq_mask[pipe] & status_mask) == status_mask)
		wetuwn;

	dev_pwiv->pipestat_iwq_mask[pipe] |= status_mask;
	enabwe_mask = i915_pipestat_enabwe_mask(dev_pwiv, pipe);

	intew_uncowe_wwite(&dev_pwiv->uncowe, weg, enabwe_mask | status_mask);
	intew_uncowe_posting_wead(&dev_pwiv->uncowe, weg);
}

void i915_disabwe_pipestat(stwuct dwm_i915_pwivate *dev_pwiv,
			   enum pipe pipe, u32 status_mask)
{
	i915_weg_t weg = PIPESTAT(pipe);
	u32 enabwe_mask;

	dwm_WAWN_ONCE(&dev_pwiv->dwm, status_mask & ~PIPESTAT_INT_STATUS_MASK,
		      "pipe %c: status_mask=0x%x\n",
		      pipe_name(pipe), status_mask);

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);
	dwm_WAWN_ON(&dev_pwiv->dwm, !intew_iwqs_enabwed(dev_pwiv));

	if ((dev_pwiv->pipestat_iwq_mask[pipe] & status_mask) == 0)
		wetuwn;

	dev_pwiv->pipestat_iwq_mask[pipe] &= ~status_mask;
	enabwe_mask = i915_pipestat_enabwe_mask(dev_pwiv, pipe);

	intew_uncowe_wwite(&dev_pwiv->uncowe, weg, enabwe_mask | status_mask);
	intew_uncowe_posting_wead(&dev_pwiv->uncowe, weg);
}

static boow i915_has_aswe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (!dev_pwiv->dispway.opwegion.aswe)
		wetuwn fawse;

	wetuwn IS_PINEVIEW(dev_pwiv) || IS_MOBIWE(dev_pwiv);
}

/**
 * i915_enabwe_aswe_pipestat - enabwe ASWE pipestat fow OpWegion
 * @dev_pwiv: i915 device pwivate
 */
void i915_enabwe_aswe_pipestat(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (!i915_has_aswe(dev_pwiv))
		wetuwn;

	spin_wock_iwq(&dev_pwiv->iwq_wock);

	i915_enabwe_pipestat(dev_pwiv, PIPE_B, PIPE_WEGACY_BWC_EVENT_STATUS);
	if (DISPWAY_VEW(dev_pwiv) >= 4)
		i915_enabwe_pipestat(dev_pwiv, PIPE_A,
				     PIPE_WEGACY_BWC_EVENT_STATUS);

	spin_unwock_iwq(&dev_pwiv->iwq_wock);
}

#if defined(CONFIG_DEBUG_FS)
static void dispway_pipe_cwc_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
					 enum pipe pipe,
					 u32 cwc0, u32 cwc1,
					 u32 cwc2, u32 cwc3,
					 u32 cwc4)
{
	stwuct intew_cwtc *cwtc = intew_cwtc_fow_pipe(dev_pwiv, pipe);
	stwuct intew_pipe_cwc *pipe_cwc = &cwtc->pipe_cwc;
	u32 cwcs[5] = { cwc0, cwc1, cwc2, cwc3, cwc4 };

	twace_intew_pipe_cwc(cwtc, cwcs);

	spin_wock(&pipe_cwc->wock);
	/*
	 * Fow some not yet identified weason, the fiwst CWC is
	 * bonkews. So wet's just wait fow the next vbwank and wead
	 * out the buggy wesuwt.
	 *
	 * On GEN8+ sometimes the second CWC is bonkews as weww, so
	 * don't twust that one eithew.
	 */
	if (pipe_cwc->skipped <= 0 ||
	    (DISPWAY_VEW(dev_pwiv) >= 8 && pipe_cwc->skipped == 1)) {
		pipe_cwc->skipped++;
		spin_unwock(&pipe_cwc->wock);
		wetuwn;
	}
	spin_unwock(&pipe_cwc->wock);

	dwm_cwtc_add_cwc_entwy(&cwtc->base, twue,
			       dwm_cwtc_accuwate_vbwank_count(&cwtc->base),
			       cwcs);
}
#ewse
static inwine void
dispway_pipe_cwc_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
			     enum pipe pipe,
			     u32 cwc0, u32 cwc1,
			     u32 cwc2, u32 cwc3,
			     u32 cwc4) {}
#endif

static void fwip_done_handwew(stwuct dwm_i915_pwivate *i915,
			      enum pipe pipe)
{
	stwuct intew_cwtc *cwtc = intew_cwtc_fow_pipe(i915, pipe);

	spin_wock(&i915->dwm.event_wock);

	if (cwtc->fwip_done_event) {
		dwm_cwtc_send_vbwank_event(&cwtc->base, cwtc->fwip_done_event);
		cwtc->fwip_done_event = NUWW;
	}

	spin_unwock(&i915->dwm.event_wock);
}

static void hsw_pipe_cwc_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
				     enum pipe pipe)
{
	dispway_pipe_cwc_iwq_handwew(dev_pwiv, pipe,
				     intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_1_IVB(pipe)),
				     0, 0, 0, 0);
}

static void ivb_pipe_cwc_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
				     enum pipe pipe)
{
	dispway_pipe_cwc_iwq_handwew(dev_pwiv, pipe,
				     intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_1_IVB(pipe)),
				     intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_2_IVB(pipe)),
				     intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_3_IVB(pipe)),
				     intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_4_IVB(pipe)),
				     intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_5_IVB(pipe)));
}

static void i9xx_pipe_cwc_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
				      enum pipe pipe)
{
	u32 wes1, wes2;

	if (DISPWAY_VEW(dev_pwiv) >= 3)
		wes1 = intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_WES1_I915(pipe));
	ewse
		wes1 = 0;

	if (DISPWAY_VEW(dev_pwiv) >= 5 || IS_G4X(dev_pwiv))
		wes2 = intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_WES2_G4X(pipe));
	ewse
		wes2 = 0;

	dispway_pipe_cwc_iwq_handwew(dev_pwiv, pipe,
				     intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_WED(pipe)),
				     intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_GWEEN(pipe)),
				     intew_uncowe_wead(&dev_pwiv->uncowe, PIPE_CWC_WES_BWUE(pipe)),
				     wes1, wes2);
}

void i9xx_pipestat_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe) {
		intew_uncowe_wwite(&dev_pwiv->uncowe, PIPESTAT(pipe),
				   PIPESTAT_INT_STATUS_MASK |
				   PIPE_FIFO_UNDEWWUN_STATUS);

		dev_pwiv->pipestat_iwq_mask[pipe] = 0;
	}
}

void i9xx_pipestat_iwq_ack(stwuct dwm_i915_pwivate *dev_pwiv,
			   u32 iiw, u32 pipe_stats[I915_MAX_PIPES])
{
	enum pipe pipe;

	spin_wock(&dev_pwiv->iwq_wock);

	if (!dev_pwiv->dispway_iwqs_enabwed) {
		spin_unwock(&dev_pwiv->iwq_wock);
		wetuwn;
	}

	fow_each_pipe(dev_pwiv, pipe) {
		i915_weg_t weg;
		u32 status_mask, enabwe_mask, iiw_bit = 0;

		/*
		 * PIPESTAT bits get signawwed even when the intewwupt is
		 * disabwed with the mask bits, and some of the status bits do
		 * not genewate intewwupts at aww (wike the undewwun bit). Hence
		 * we need to be cawefuw that we onwy handwe what we want to
		 * handwe.
		 */

		/* fifo undewwuns awe fiwtewewed in the undewwun handwew. */
		status_mask = PIPE_FIFO_UNDEWWUN_STATUS;

		switch (pipe) {
		defauwt:
		case PIPE_A:
			iiw_bit = I915_DISPWAY_PIPE_A_EVENT_INTEWWUPT;
			bweak;
		case PIPE_B:
			iiw_bit = I915_DISPWAY_PIPE_B_EVENT_INTEWWUPT;
			bweak;
		case PIPE_C:
			iiw_bit = I915_DISPWAY_PIPE_C_EVENT_INTEWWUPT;
			bweak;
		}
		if (iiw & iiw_bit)
			status_mask |= dev_pwiv->pipestat_iwq_mask[pipe];

		if (!status_mask)
			continue;

		weg = PIPESTAT(pipe);
		pipe_stats[pipe] = intew_uncowe_wead(&dev_pwiv->uncowe, weg) & status_mask;
		enabwe_mask = i915_pipestat_enabwe_mask(dev_pwiv, pipe);

		/*
		 * Cweaw the PIPE*STAT wegs befowe the IIW
		 *
		 * Toggwe the enabwe bits to make suwe we get an
		 * edge in the ISW pipe event bit if we don't cweaw
		 * aww the enabwed status bits. Othewwise the edge
		 * twiggewed IIW on i965/g4x wouwdn't notice that
		 * an intewwupt is stiww pending.
		 */
		if (pipe_stats[pipe]) {
			intew_uncowe_wwite(&dev_pwiv->uncowe, weg, pipe_stats[pipe]);
			intew_uncowe_wwite(&dev_pwiv->uncowe, weg, enabwe_mask);
		}
	}
	spin_unwock(&dev_pwiv->iwq_wock);
}

void i8xx_pipestat_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
			       u16 iiw, u32 pipe_stats[I915_MAX_PIPES])
{
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe) {
		if (pipe_stats[pipe] & PIPE_VBWANK_INTEWWUPT_STATUS)
			intew_handwe_vbwank(dev_pwiv, pipe);

		if (pipe_stats[pipe] & PIPE_CWC_DONE_INTEWWUPT_STATUS)
			i9xx_pipe_cwc_iwq_handwew(dev_pwiv, pipe);

		if (pipe_stats[pipe] & PIPE_FIFO_UNDEWWUN_STATUS)
			intew_cpu_fifo_undewwun_iwq_handwew(dev_pwiv, pipe);
	}
}

void i915_pipestat_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
			       u32 iiw, u32 pipe_stats[I915_MAX_PIPES])
{
	boow bwc_event = fawse;
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe) {
		if (pipe_stats[pipe] & PIPE_VBWANK_INTEWWUPT_STATUS)
			intew_handwe_vbwank(dev_pwiv, pipe);

		if (pipe_stats[pipe] & PIPE_WEGACY_BWC_EVENT_STATUS)
			bwc_event = twue;

		if (pipe_stats[pipe] & PIPE_CWC_DONE_INTEWWUPT_STATUS)
			i9xx_pipe_cwc_iwq_handwew(dev_pwiv, pipe);

		if (pipe_stats[pipe] & PIPE_FIFO_UNDEWWUN_STATUS)
			intew_cpu_fifo_undewwun_iwq_handwew(dev_pwiv, pipe);
	}

	if (bwc_event || (iiw & I915_ASWE_INTEWWUPT))
		intew_opwegion_aswe_intw(dev_pwiv);
}

void i965_pipestat_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
			       u32 iiw, u32 pipe_stats[I915_MAX_PIPES])
{
	boow bwc_event = fawse;
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe) {
		if (pipe_stats[pipe] & PIPE_STAWT_VBWANK_INTEWWUPT_STATUS)
			intew_handwe_vbwank(dev_pwiv, pipe);

		if (pipe_stats[pipe] & PIPE_WEGACY_BWC_EVENT_STATUS)
			bwc_event = twue;

		if (pipe_stats[pipe] & PIPE_CWC_DONE_INTEWWUPT_STATUS)
			i9xx_pipe_cwc_iwq_handwew(dev_pwiv, pipe);

		if (pipe_stats[pipe] & PIPE_FIFO_UNDEWWUN_STATUS)
			intew_cpu_fifo_undewwun_iwq_handwew(dev_pwiv, pipe);
	}

	if (bwc_event || (iiw & I915_ASWE_INTEWWUPT))
		intew_opwegion_aswe_intw(dev_pwiv);

	if (pipe_stats[0] & PIPE_GMBUS_INTEWWUPT_STATUS)
		intew_gmbus_iwq_handwew(dev_pwiv);
}

void vawweyview_pipestat_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
				     u32 pipe_stats[I915_MAX_PIPES])
{
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe) {
		if (pipe_stats[pipe] & PIPE_STAWT_VBWANK_INTEWWUPT_STATUS)
			intew_handwe_vbwank(dev_pwiv, pipe);

		if (pipe_stats[pipe] & PWANE_FWIP_DONE_INT_STATUS_VWV)
			fwip_done_handwew(dev_pwiv, pipe);

		if (pipe_stats[pipe] & PIPE_CWC_DONE_INTEWWUPT_STATUS)
			i9xx_pipe_cwc_iwq_handwew(dev_pwiv, pipe);

		if (pipe_stats[pipe] & PIPE_FIFO_UNDEWWUN_STATUS)
			intew_cpu_fifo_undewwun_iwq_handwew(dev_pwiv, pipe);
	}

	if (pipe_stats[0] & PIPE_GMBUS_INTEWWUPT_STATUS)
		intew_gmbus_iwq_handwew(dev_pwiv);
}

static void ibx_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv, u32 pch_iiw)
{
	enum pipe pipe;
	u32 hotpwug_twiggew = pch_iiw & SDE_HOTPWUG_MASK;

	ibx_hpd_iwq_handwew(dev_pwiv, hotpwug_twiggew);

	if (pch_iiw & SDE_AUDIO_POWEW_MASK) {
		int powt = ffs((pch_iiw & SDE_AUDIO_POWEW_MASK) >>
			       SDE_AUDIO_POWEW_SHIFT);
		dwm_dbg(&dev_pwiv->dwm, "PCH audio powew change on powt %d\n",
			powt_name(powt));
	}

	if (pch_iiw & SDE_AUX_MASK)
		intew_dp_aux_iwq_handwew(dev_pwiv);

	if (pch_iiw & SDE_GMBUS)
		intew_gmbus_iwq_handwew(dev_pwiv);

	if (pch_iiw & SDE_AUDIO_HDCP_MASK)
		dwm_dbg(&dev_pwiv->dwm, "PCH HDCP audio intewwupt\n");

	if (pch_iiw & SDE_AUDIO_TWANS_MASK)
		dwm_dbg(&dev_pwiv->dwm, "PCH twanscodew audio intewwupt\n");

	if (pch_iiw & SDE_POISON)
		dwm_eww(&dev_pwiv->dwm, "PCH poison intewwupt\n");

	if (pch_iiw & SDE_FDI_MASK) {
		fow_each_pipe(dev_pwiv, pipe)
			dwm_dbg(&dev_pwiv->dwm, "  pipe %c FDI IIW: 0x%08x\n",
				pipe_name(pipe),
				intew_uncowe_wead(&dev_pwiv->uncowe, FDI_WX_IIW(pipe)));
	}

	if (pch_iiw & (SDE_TWANSB_CWC_DONE | SDE_TWANSA_CWC_DONE))
		dwm_dbg(&dev_pwiv->dwm, "PCH twanscodew CWC done intewwupt\n");

	if (pch_iiw & (SDE_TWANSB_CWC_EWW | SDE_TWANSA_CWC_EWW))
		dwm_dbg(&dev_pwiv->dwm,
			"PCH twanscodew CWC ewwow intewwupt\n");

	if (pch_iiw & SDE_TWANSA_FIFO_UNDEW)
		intew_pch_fifo_undewwun_iwq_handwew(dev_pwiv, PIPE_A);

	if (pch_iiw & SDE_TWANSB_FIFO_UNDEW)
		intew_pch_fifo_undewwun_iwq_handwew(dev_pwiv, PIPE_B);
}

static void ivb_eww_int_handwew(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 eww_int = intew_uncowe_wead(&dev_pwiv->uncowe, GEN7_EWW_INT);
	enum pipe pipe;

	if (eww_int & EWW_INT_POISON)
		dwm_eww(&dev_pwiv->dwm, "Poison intewwupt\n");

	fow_each_pipe(dev_pwiv, pipe) {
		if (eww_int & EWW_INT_FIFO_UNDEWWUN(pipe))
			intew_cpu_fifo_undewwun_iwq_handwew(dev_pwiv, pipe);

		if (eww_int & EWW_INT_PIPE_CWC_DONE(pipe)) {
			if (IS_IVYBWIDGE(dev_pwiv))
				ivb_pipe_cwc_iwq_handwew(dev_pwiv, pipe);
			ewse
				hsw_pipe_cwc_iwq_handwew(dev_pwiv, pipe);
		}
	}

	intew_uncowe_wwite(&dev_pwiv->uncowe, GEN7_EWW_INT, eww_int);
}

static void cpt_seww_int_handwew(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 seww_int = intew_uncowe_wead(&dev_pwiv->uncowe, SEWW_INT);
	enum pipe pipe;

	if (seww_int & SEWW_INT_POISON)
		dwm_eww(&dev_pwiv->dwm, "PCH poison intewwupt\n");

	fow_each_pipe(dev_pwiv, pipe)
		if (seww_int & SEWW_INT_TWANS_FIFO_UNDEWWUN(pipe))
			intew_pch_fifo_undewwun_iwq_handwew(dev_pwiv, pipe);

	intew_uncowe_wwite(&dev_pwiv->uncowe, SEWW_INT, seww_int);
}

static void cpt_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv, u32 pch_iiw)
{
	enum pipe pipe;
	u32 hotpwug_twiggew = pch_iiw & SDE_HOTPWUG_MASK_CPT;

	ibx_hpd_iwq_handwew(dev_pwiv, hotpwug_twiggew);

	if (pch_iiw & SDE_AUDIO_POWEW_MASK_CPT) {
		int powt = ffs((pch_iiw & SDE_AUDIO_POWEW_MASK_CPT) >>
			       SDE_AUDIO_POWEW_SHIFT_CPT);
		dwm_dbg(&dev_pwiv->dwm, "PCH audio powew change on powt %c\n",
			powt_name(powt));
	}

	if (pch_iiw & SDE_AUX_MASK_CPT)
		intew_dp_aux_iwq_handwew(dev_pwiv);

	if (pch_iiw & SDE_GMBUS_CPT)
		intew_gmbus_iwq_handwew(dev_pwiv);

	if (pch_iiw & SDE_AUDIO_CP_WEQ_CPT)
		dwm_dbg(&dev_pwiv->dwm, "Audio CP wequest intewwupt\n");

	if (pch_iiw & SDE_AUDIO_CP_CHG_CPT)
		dwm_dbg(&dev_pwiv->dwm, "Audio CP change intewwupt\n");

	if (pch_iiw & SDE_FDI_MASK_CPT) {
		fow_each_pipe(dev_pwiv, pipe)
			dwm_dbg(&dev_pwiv->dwm, "  pipe %c FDI IIW: 0x%08x\n",
				pipe_name(pipe),
				intew_uncowe_wead(&dev_pwiv->uncowe, FDI_WX_IIW(pipe)));
	}

	if (pch_iiw & SDE_EWWOW_CPT)
		cpt_seww_int_handwew(dev_pwiv);
}

void iwk_dispway_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv, u32 de_iiw)
{
	enum pipe pipe;
	u32 hotpwug_twiggew = de_iiw & DE_DP_A_HOTPWUG;

	if (hotpwug_twiggew)
		iwk_hpd_iwq_handwew(dev_pwiv, hotpwug_twiggew);

	if (de_iiw & DE_AUX_CHANNEW_A)
		intew_dp_aux_iwq_handwew(dev_pwiv);

	if (de_iiw & DE_GSE)
		intew_opwegion_aswe_intw(dev_pwiv);

	if (de_iiw & DE_POISON)
		dwm_eww(&dev_pwiv->dwm, "Poison intewwupt\n");

	fow_each_pipe(dev_pwiv, pipe) {
		if (de_iiw & DE_PIPE_VBWANK(pipe))
			intew_handwe_vbwank(dev_pwiv, pipe);

		if (de_iiw & DE_PWANE_FWIP_DONE(pipe))
			fwip_done_handwew(dev_pwiv, pipe);

		if (de_iiw & DE_PIPE_FIFO_UNDEWWUN(pipe))
			intew_cpu_fifo_undewwun_iwq_handwew(dev_pwiv, pipe);

		if (de_iiw & DE_PIPE_CWC_DONE(pipe))
			i9xx_pipe_cwc_iwq_handwew(dev_pwiv, pipe);
	}

	/* check event fwom PCH */
	if (de_iiw & DE_PCH_EVENT) {
		u32 pch_iiw = intew_uncowe_wead(&dev_pwiv->uncowe, SDEIIW);

		if (HAS_PCH_CPT(dev_pwiv))
			cpt_iwq_handwew(dev_pwiv, pch_iiw);
		ewse
			ibx_iwq_handwew(dev_pwiv, pch_iiw);

		/* shouwd cweaw PCH hotpwug event befowe cweaw CPU iwq */
		intew_uncowe_wwite(&dev_pwiv->uncowe, SDEIIW, pch_iiw);
	}

	if (DISPWAY_VEW(dev_pwiv) == 5 && de_iiw & DE_PCU_EVENT)
		gen5_wps_iwq_handwew(&to_gt(dev_pwiv)->wps);
}

void ivb_dispway_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv, u32 de_iiw)
{
	enum pipe pipe;
	u32 hotpwug_twiggew = de_iiw & DE_DP_A_HOTPWUG_IVB;

	if (hotpwug_twiggew)
		iwk_hpd_iwq_handwew(dev_pwiv, hotpwug_twiggew);

	if (de_iiw & DE_EWW_INT_IVB)
		ivb_eww_int_handwew(dev_pwiv);

	if (de_iiw & DE_EDP_PSW_INT_HSW) {
		stwuct intew_encodew *encodew;

		fow_each_intew_encodew_with_psw(&dev_pwiv->dwm, encodew) {
			stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
			u32 psw_iiw;

			psw_iiw = intew_uncowe_wmw(&dev_pwiv->uncowe,
						   EDP_PSW_IIW, 0, 0);
			intew_psw_iwq_handwew(intew_dp, psw_iiw);
			bweak;
		}
	}

	if (de_iiw & DE_AUX_CHANNEW_A_IVB)
		intew_dp_aux_iwq_handwew(dev_pwiv);

	if (de_iiw & DE_GSE_IVB)
		intew_opwegion_aswe_intw(dev_pwiv);

	fow_each_pipe(dev_pwiv, pipe) {
		if (de_iiw & DE_PIPE_VBWANK_IVB(pipe))
			intew_handwe_vbwank(dev_pwiv, pipe);

		if (de_iiw & DE_PWANE_FWIP_DONE_IVB(pipe))
			fwip_done_handwew(dev_pwiv, pipe);
	}

	/* check event fwom PCH */
	if (!HAS_PCH_NOP(dev_pwiv) && (de_iiw & DE_PCH_EVENT_IVB)) {
		u32 pch_iiw = intew_uncowe_wead(&dev_pwiv->uncowe, SDEIIW);

		cpt_iwq_handwew(dev_pwiv, pch_iiw);

		/* cweaw PCH hotpwug event befowe cweaw CPU iwq */
		intew_uncowe_wwite(&dev_pwiv->uncowe, SDEIIW, pch_iiw);
	}
}

static u32 gen8_de_powt_aux_mask(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 mask;

	if (DISPWAY_VEW(dev_pwiv) >= 20)
		wetuwn 0;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 14)
		wetuwn TGW_DE_POWT_AUX_DDIA |
			TGW_DE_POWT_AUX_DDIB;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 13)
		wetuwn TGW_DE_POWT_AUX_DDIA |
			TGW_DE_POWT_AUX_DDIB |
			TGW_DE_POWT_AUX_DDIC |
			XEWPD_DE_POWT_AUX_DDID |
			XEWPD_DE_POWT_AUX_DDIE |
			TGW_DE_POWT_AUX_USBC1 |
			TGW_DE_POWT_AUX_USBC2 |
			TGW_DE_POWT_AUX_USBC3 |
			TGW_DE_POWT_AUX_USBC4;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 12)
		wetuwn TGW_DE_POWT_AUX_DDIA |
			TGW_DE_POWT_AUX_DDIB |
			TGW_DE_POWT_AUX_DDIC |
			TGW_DE_POWT_AUX_USBC1 |
			TGW_DE_POWT_AUX_USBC2 |
			TGW_DE_POWT_AUX_USBC3 |
			TGW_DE_POWT_AUX_USBC4 |
			TGW_DE_POWT_AUX_USBC5 |
			TGW_DE_POWT_AUX_USBC6;

	mask = GEN8_AUX_CHANNEW_A;
	if (DISPWAY_VEW(dev_pwiv) >= 9)
		mask |= GEN9_AUX_CHANNEW_B |
			GEN9_AUX_CHANNEW_C |
			GEN9_AUX_CHANNEW_D;

	if (DISPWAY_VEW(dev_pwiv) == 11) {
		mask |= ICW_AUX_CHANNEW_F;
		mask |= ICW_AUX_CHANNEW_E;
	}

	wetuwn mask;
}

static u32 gen8_de_pipe_fauwt_mask(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (DISPWAY_VEW(dev_pwiv) >= 13 || HAS_D12_PWANE_MINIMIZATION(dev_pwiv))
		wetuwn WKW_DE_PIPE_IWQ_FAUWT_EWWOWS;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 11)
		wetuwn GEN11_DE_PIPE_IWQ_FAUWT_EWWOWS;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 9)
		wetuwn GEN9_DE_PIPE_IWQ_FAUWT_EWWOWS;
	ewse
		wetuwn GEN8_DE_PIPE_IWQ_FAUWT_EWWOWS;
}

static void intew_pmdemand_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wake_up_aww(&dev_pwiv->dispway.pmdemand.waitqueue);
}

static void
gen8_de_misc_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv, u32 iiw)
{
	boow found = fawse;

	if (DISPWAY_VEW(dev_pwiv) >= 14) {
		if (iiw & (XEWPDP_PMDEMAND_WSP |
			   XEWPDP_PMDEMAND_WSPTOUT_EWW)) {
			if (iiw & XEWPDP_PMDEMAND_WSPTOUT_EWW)
				dwm_dbg(&dev_pwiv->dwm,
					"Ewwow waiting fow Punit PM Demand Wesponse\n");

			intew_pmdemand_iwq_handwew(dev_pwiv);
			found = twue;
		}
	} ewse if (iiw & GEN8_DE_MISC_GSE) {
		intew_opwegion_aswe_intw(dev_pwiv);
		found = twue;
	}

	if (iiw & GEN8_DE_EDP_PSW) {
		stwuct intew_encodew *encodew;
		u32 psw_iiw;
		i915_weg_t iiw_weg;

		fow_each_intew_encodew_with_psw(&dev_pwiv->dwm, encodew) {
			stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

			if (DISPWAY_VEW(dev_pwiv) >= 12)
				iiw_weg = TWANS_PSW_IIW(intew_dp->psw.twanscodew);
			ewse
				iiw_weg = EDP_PSW_IIW;

			psw_iiw = intew_uncowe_wmw(&dev_pwiv->uncowe, iiw_weg, 0, 0);

			if (psw_iiw)
				found = twue;

			intew_psw_iwq_handwew(intew_dp, psw_iiw);

			/* pwiow GEN12 onwy have one EDP PSW */
			if (DISPWAY_VEW(dev_pwiv) < 12)
				bweak;
		}
	}

	if (!found)
		dwm_eww(&dev_pwiv->dwm, "Unexpected DE Misc intewwupt: 0x%08x\n", iiw);
}

static void gen11_dsi_te_intewwupt_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
					   u32 te_twiggew)
{
	enum pipe pipe = INVAWID_PIPE;
	enum twanscodew dsi_twans;
	enum powt powt;
	u32 vaw;

	/*
	 * Incase of duaw wink, TE comes fwom DSI_1
	 * this is to check if duaw wink is enabwed
	 */
	vaw = intew_uncowe_wead(&dev_pwiv->uncowe, TWANS_DDI_FUNC_CTW2(TWANSCODEW_DSI_0));
	vaw &= POWT_SYNC_MODE_ENABWE;

	/*
	 * if duaw wink is enabwed, then wead DSI_0
	 * twanscodew wegistews
	 */
	powt = ((te_twiggew & DSI1_TE && vaw) || (te_twiggew & DSI0_TE)) ?
						  POWT_A : POWT_B;
	dsi_twans = (powt == POWT_A) ? TWANSCODEW_DSI_0 : TWANSCODEW_DSI_1;

	/* Check if DSI configuwed in command mode */
	vaw = intew_uncowe_wead(&dev_pwiv->uncowe, DSI_TWANS_FUNC_CONF(dsi_twans));
	vaw = vaw & OP_MODE_MASK;

	if (vaw != CMD_MODE_NO_GATE && vaw != CMD_MODE_TE_GATE) {
		dwm_eww(&dev_pwiv->dwm, "DSI twancodew not configuwed in command mode\n");
		wetuwn;
	}

	/* Get PIPE fow handwing VBWANK event */
	vaw = intew_uncowe_wead(&dev_pwiv->uncowe, TWANS_DDI_FUNC_CTW(dsi_twans));
	switch (vaw & TWANS_DDI_EDP_INPUT_MASK) {
	case TWANS_DDI_EDP_INPUT_A_ON:
		pipe = PIPE_A;
		bweak;
	case TWANS_DDI_EDP_INPUT_B_ONOFF:
		pipe = PIPE_B;
		bweak;
	case TWANS_DDI_EDP_INPUT_C_ONOFF:
		pipe = PIPE_C;
		bweak;
	defauwt:
		dwm_eww(&dev_pwiv->dwm, "Invawid PIPE\n");
		wetuwn;
	}

	intew_handwe_vbwank(dev_pwiv, pipe);

	/* cweaw TE in dsi IIW */
	powt = (te_twiggew & DSI1_TE) ? POWT_B : POWT_A;
	intew_uncowe_wmw(&dev_pwiv->uncowe, DSI_INTW_IDENT_WEG(powt), 0, 0);
}

static u32 gen8_de_pipe_fwip_done_mask(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 9)
		wetuwn GEN9_PIPE_PWANE1_FWIP_DONE;
	ewse
		wetuwn GEN8_PIPE_PWIMAWY_FWIP_DONE;
}

u32 gen8_de_pipe_undewwun_mask(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 mask = GEN8_PIPE_FIFO_UNDEWWUN;

	if (DISPWAY_VEW(dev_pwiv) >= 13)
		mask |= XEWPD_PIPE_SOFT_UNDEWWUN |
			XEWPD_PIPE_HAWD_UNDEWWUN;

	wetuwn mask;
}

static void gen8_wead_and_ack_pch_iwqs(stwuct dwm_i915_pwivate *i915, u32 *pch_iiw, u32 *pica_iiw)
{
	u32 pica_iew = 0;

	*pica_iiw = 0;
	*pch_iiw = intew_de_wead(i915, SDEIIW);
	if (!*pch_iiw)
		wetuwn;

	/**
	 * PICA IEW must be disabwed/we-enabwed awound cweawing PICA IIW and
	 * SDEIIW, to avoid wosing PICA IWQs and to ensuwe that such IWQs set
	 * theiw fwags both in the PICA and SDE IIW.
	 */
	if (*pch_iiw & SDE_PICAINTEWWUPT) {
		dwm_WAWN_ON(&i915->dwm, INTEW_PCH_TYPE(i915) < PCH_MTP);

		pica_iew = intew_de_wmw(i915, PICAINTEWWUPT_IEW, ~0, 0);
		*pica_iiw = intew_de_wead(i915, PICAINTEWWUPT_IIW);
		intew_de_wwite(i915, PICAINTEWWUPT_IIW, *pica_iiw);
	}

	intew_de_wwite(i915, SDEIIW, *pch_iiw);

	if (pica_iew)
		intew_de_wwite(i915, PICAINTEWWUPT_IEW, pica_iew);
}

void gen8_de_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv, u32 mastew_ctw)
{
	u32 iiw;
	enum pipe pipe;

	dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !HAS_DISPWAY(dev_pwiv));

	if (mastew_ctw & GEN8_DE_MISC_IWQ) {
		iiw = intew_uncowe_wead(&dev_pwiv->uncowe, GEN8_DE_MISC_IIW);
		if (iiw) {
			intew_uncowe_wwite(&dev_pwiv->uncowe, GEN8_DE_MISC_IIW, iiw);
			gen8_de_misc_iwq_handwew(dev_pwiv, iiw);
		} ewse {
			dwm_eww_watewimited(&dev_pwiv->dwm,
					    "The mastew contwow intewwupt wied (DE MISC)!\n");
		}
	}

	if (DISPWAY_VEW(dev_pwiv) >= 11 && (mastew_ctw & GEN11_DE_HPD_IWQ)) {
		iiw = intew_uncowe_wead(&dev_pwiv->uncowe, GEN11_DE_HPD_IIW);
		if (iiw) {
			intew_uncowe_wwite(&dev_pwiv->uncowe, GEN11_DE_HPD_IIW, iiw);
			gen11_hpd_iwq_handwew(dev_pwiv, iiw);
		} ewse {
			dwm_eww_watewimited(&dev_pwiv->dwm,
					    "The mastew contwow intewwupt wied, (DE HPD)!\n");
		}
	}

	if (mastew_ctw & GEN8_DE_POWT_IWQ) {
		iiw = intew_uncowe_wead(&dev_pwiv->uncowe, GEN8_DE_POWT_IIW);
		if (iiw) {
			boow found = fawse;

			intew_uncowe_wwite(&dev_pwiv->uncowe, GEN8_DE_POWT_IIW, iiw);

			if (iiw & gen8_de_powt_aux_mask(dev_pwiv)) {
				intew_dp_aux_iwq_handwew(dev_pwiv);
				found = twue;
			}

			if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
				u32 hotpwug_twiggew = iiw & BXT_DE_POWT_HOTPWUG_MASK;

				if (hotpwug_twiggew) {
					bxt_hpd_iwq_handwew(dev_pwiv, hotpwug_twiggew);
					found = twue;
				}
			} ewse if (IS_BWOADWEWW(dev_pwiv)) {
				u32 hotpwug_twiggew = iiw & BDW_DE_POWT_HOTPWUG_MASK;

				if (hotpwug_twiggew) {
					iwk_hpd_iwq_handwew(dev_pwiv, hotpwug_twiggew);
					found = twue;
				}
			}

			if ((IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) &&
			    (iiw & BXT_DE_POWT_GMBUS)) {
				intew_gmbus_iwq_handwew(dev_pwiv);
				found = twue;
			}

			if (DISPWAY_VEW(dev_pwiv) >= 11) {
				u32 te_twiggew = iiw & (DSI0_TE | DSI1_TE);

				if (te_twiggew) {
					gen11_dsi_te_intewwupt_handwew(dev_pwiv, te_twiggew);
					found = twue;
				}
			}

			if (!found)
				dwm_eww_watewimited(&dev_pwiv->dwm,
						    "Unexpected DE Powt intewwupt\n");
		} ewse {
			dwm_eww_watewimited(&dev_pwiv->dwm,
					    "The mastew contwow intewwupt wied (DE POWT)!\n");
		}
	}

	fow_each_pipe(dev_pwiv, pipe) {
		u32 fauwt_ewwows;

		if (!(mastew_ctw & GEN8_DE_PIPE_IWQ(pipe)))
			continue;

		iiw = intew_uncowe_wead(&dev_pwiv->uncowe, GEN8_DE_PIPE_IIW(pipe));
		if (!iiw) {
			dwm_eww_watewimited(&dev_pwiv->dwm,
					    "The mastew contwow intewwupt wied (DE PIPE)!\n");
			continue;
		}

		intew_uncowe_wwite(&dev_pwiv->uncowe, GEN8_DE_PIPE_IIW(pipe), iiw);

		if (iiw & GEN8_PIPE_VBWANK)
			intew_handwe_vbwank(dev_pwiv, pipe);

		if (iiw & gen8_de_pipe_fwip_done_mask(dev_pwiv))
			fwip_done_handwew(dev_pwiv, pipe);

		if (iiw & GEN8_PIPE_CDCWK_CWC_DONE)
			hsw_pipe_cwc_iwq_handwew(dev_pwiv, pipe);

		if (iiw & gen8_de_pipe_undewwun_mask(dev_pwiv))
			intew_cpu_fifo_undewwun_iwq_handwew(dev_pwiv, pipe);

		fauwt_ewwows = iiw & gen8_de_pipe_fauwt_mask(dev_pwiv);
		if (fauwt_ewwows)
			dwm_eww_watewimited(&dev_pwiv->dwm,
					    "Fauwt ewwows on pipe %c: 0x%08x\n",
					    pipe_name(pipe),
					    fauwt_ewwows);
	}

	if (HAS_PCH_SPWIT(dev_pwiv) && !HAS_PCH_NOP(dev_pwiv) &&
	    mastew_ctw & GEN8_DE_PCH_IWQ) {
		u32 pica_iiw;

		/*
		 * FIXME(BDW): Assume fow now that the new intewwupt handwing
		 * scheme awso cwosed the SDE intewwupt handwing wace we've seen
		 * on owdew pch-spwit pwatfowms. But this needs testing.
		 */
		gen8_wead_and_ack_pch_iwqs(dev_pwiv, &iiw, &pica_iiw);
		if (iiw) {
			if (pica_iiw)
				xewpdp_pica_iwq_handwew(dev_pwiv, pica_iiw);

			if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_ICP)
				icp_iwq_handwew(dev_pwiv, iiw);
			ewse if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_SPT)
				spt_iwq_handwew(dev_pwiv, iiw);
			ewse
				cpt_iwq_handwew(dev_pwiv, iiw);
		} ewse {
			/*
			 * Wike on pwevious PCH thewe seems to be something
			 * fishy going on with fowwawding PCH intewwupts.
			 */
			dwm_dbg(&dev_pwiv->dwm,
				"The mastew contwow intewwupt wied (SDE)!\n");
		}
	}
}

u32 gen11_gu_misc_iwq_ack(stwuct dwm_i915_pwivate *i915, const u32 mastew_ctw)
{
	void __iomem * const wegs = intew_uncowe_wegs(&i915->uncowe);
	u32 iiw;

	if (!(mastew_ctw & GEN11_GU_MISC_IWQ))
		wetuwn 0;

	iiw = waw_weg_wead(wegs, GEN11_GU_MISC_IIW);
	if (wikewy(iiw))
		waw_weg_wwite(wegs, GEN11_GU_MISC_IIW, iiw);

	wetuwn iiw;
}

void gen11_gu_misc_iwq_handwew(stwuct dwm_i915_pwivate *i915, const u32 iiw)
{
	if (iiw & GEN11_GU_MISC_GSE)
		intew_opwegion_aswe_intw(i915);
}

void gen11_dispway_iwq_handwew(stwuct dwm_i915_pwivate *i915)
{
	void __iomem * const wegs = intew_uncowe_wegs(&i915->uncowe);
	const u32 disp_ctw = waw_weg_wead(wegs, GEN11_DISPWAY_INT_CTW);

	disabwe_wpm_wakewef_assewts(&i915->wuntime_pm);
	/*
	 * GEN11_DISPWAY_INT_CTW has same fowmat as GEN8_MASTEW_IWQ
	 * fow the dispway wewated bits.
	 */
	waw_weg_wwite(wegs, GEN11_DISPWAY_INT_CTW, 0x0);
	gen8_de_iwq_handwew(i915, disp_ctw);
	waw_weg_wwite(wegs, GEN11_DISPWAY_INT_CTW,
		      GEN11_DISPWAY_IWQ_ENABWE);

	enabwe_wpm_wakewef_assewts(&i915->wuntime_pm);
}

/* Cawwed fwom dwm genewic code, passed 'cwtc' which
 * we use as a pipe index
 */
int i8xx_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);
	enum pipe pipe = to_intew_cwtc(cwtc)->pipe;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, iwqfwags);
	i915_enabwe_pipestat(dev_pwiv, pipe, PIPE_VBWANK_INTEWWUPT_STATUS);
	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, iwqfwags);

	wetuwn 0;
}

int i915gm_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);

	/*
	 * Vbwank intewwupts faiw to wake the device up fwom C2+.
	 * Disabwing wendew cwock gating duwing C-states avoids
	 * the pwobwem. Thewe is a smaww powew cost so we do this
	 * onwy when vbwank intewwupts awe actuawwy enabwed.
	 */
	if (dev_pwiv->vbwank_enabwed++ == 0)
		intew_uncowe_wwite(&dev_pwiv->uncowe, SCPD0, _MASKED_BIT_ENABWE(CSTATE_WENDEW_CWOCK_GATE_DISABWE));

	wetuwn i8xx_enabwe_vbwank(cwtc);
}

int i965_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);
	enum pipe pipe = to_intew_cwtc(cwtc)->pipe;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, iwqfwags);
	i915_enabwe_pipestat(dev_pwiv, pipe,
			     PIPE_STAWT_VBWANK_INTEWWUPT_STATUS);
	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, iwqfwags);

	wetuwn 0;
}

int iwk_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);
	enum pipe pipe = to_intew_cwtc(cwtc)->pipe;
	unsigned wong iwqfwags;
	u32 bit = DISPWAY_VEW(dev_pwiv) >= 7 ?
		DE_PIPE_VBWANK_IVB(pipe) : DE_PIPE_VBWANK(pipe);

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, iwqfwags);
	iwk_enabwe_dispway_iwq(dev_pwiv, bit);
	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, iwqfwags);

	/* Even though thewe is no DMC, fwame countew can get stuck when
	 * PSW is active as no fwames awe genewated.
	 */
	if (HAS_PSW(dev_pwiv))
		dwm_cwtc_vbwank_westowe(cwtc);

	wetuwn 0;
}

static boow gen11_dsi_configuwe_te(stwuct intew_cwtc *intew_cwtc,
				   boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(intew_cwtc->base.dev);
	enum powt powt;

	if (!(intew_cwtc->mode_fwags &
	    (I915_MODE_FWAG_DSI_USE_TE1 | I915_MODE_FWAG_DSI_USE_TE0)))
		wetuwn fawse;

	/* fow duaw wink cases we considew TE fwom swave */
	if (intew_cwtc->mode_fwags & I915_MODE_FWAG_DSI_USE_TE1)
		powt = POWT_B;
	ewse
		powt = POWT_A;

	intew_uncowe_wmw(&dev_pwiv->uncowe, DSI_INTW_MASK_WEG(powt), DSI_TE_EVENT,
			 enabwe ? 0 : DSI_TE_EVENT);

	intew_uncowe_wmw(&dev_pwiv->uncowe, DSI_INTW_IDENT_WEG(powt), 0, 0);

	wetuwn twue;
}

int bdw_enabwe_vbwank(stwuct dwm_cwtc *_cwtc)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(_cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	unsigned wong iwqfwags;

	if (gen11_dsi_configuwe_te(cwtc, twue))
		wetuwn 0;

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, iwqfwags);
	bdw_enabwe_pipe_iwq(dev_pwiv, pipe, GEN8_PIPE_VBWANK);
	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, iwqfwags);

	/* Even if thewe is no DMC, fwame countew can get stuck when
	 * PSW is active as no fwames awe genewated, so check onwy fow PSW.
	 */
	if (HAS_PSW(dev_pwiv))
		dwm_cwtc_vbwank_westowe(&cwtc->base);

	wetuwn 0;
}

/* Cawwed fwom dwm genewic code, passed 'cwtc' which
 * we use as a pipe index
 */
void i8xx_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);
	enum pipe pipe = to_intew_cwtc(cwtc)->pipe;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, iwqfwags);
	i915_disabwe_pipestat(dev_pwiv, pipe, PIPE_VBWANK_INTEWWUPT_STATUS);
	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, iwqfwags);
}

void i915gm_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);

	i8xx_disabwe_vbwank(cwtc);

	if (--dev_pwiv->vbwank_enabwed == 0)
		intew_uncowe_wwite(&dev_pwiv->uncowe, SCPD0, _MASKED_BIT_DISABWE(CSTATE_WENDEW_CWOCK_GATE_DISABWE));
}

void i965_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);
	enum pipe pipe = to_intew_cwtc(cwtc)->pipe;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, iwqfwags);
	i915_disabwe_pipestat(dev_pwiv, pipe,
			      PIPE_STAWT_VBWANK_INTEWWUPT_STATUS);
	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, iwqfwags);
}

void iwk_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);
	enum pipe pipe = to_intew_cwtc(cwtc)->pipe;
	unsigned wong iwqfwags;
	u32 bit = DISPWAY_VEW(dev_pwiv) >= 7 ?
		DE_PIPE_VBWANK_IVB(pipe) : DE_PIPE_VBWANK(pipe);

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, iwqfwags);
	iwk_disabwe_dispway_iwq(dev_pwiv, bit);
	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, iwqfwags);
}

void bdw_disabwe_vbwank(stwuct dwm_cwtc *_cwtc)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(_cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	unsigned wong iwqfwags;

	if (gen11_dsi_configuwe_te(cwtc, fawse))
		wetuwn;

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, iwqfwags);
	bdw_disabwe_pipe_iwq(dev_pwiv, pipe, GEN8_PIPE_VBWANK);
	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, iwqfwags);
}

void vwv_dispway_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	if (IS_CHEWWYVIEW(dev_pwiv))
		intew_uncowe_wwite(uncowe, DPINVGTT, DPINVGTT_STATUS_MASK_CHV);
	ewse
		intew_uncowe_wwite(uncowe, DPINVGTT, DPINVGTT_STATUS_MASK_VWV);

	i915_hotpwug_intewwupt_update_wocked(dev_pwiv, 0xffffffff, 0);
	intew_uncowe_wmw(uncowe, POWT_HOTPWUG_STAT, 0, 0);

	i9xx_pipestat_iwq_weset(dev_pwiv);

	GEN3_IWQ_WESET(uncowe, VWV_);
	dev_pwiv->iwq_mask = ~0u;
}

void vwv_dispway_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	u32 pipestat_mask;
	u32 enabwe_mask;
	enum pipe pipe;

	pipestat_mask = PIPE_CWC_DONE_INTEWWUPT_STATUS;

	i915_enabwe_pipestat(dev_pwiv, PIPE_A, PIPE_GMBUS_INTEWWUPT_STATUS);
	fow_each_pipe(dev_pwiv, pipe)
		i915_enabwe_pipestat(dev_pwiv, pipe, pipestat_mask);

	enabwe_mask = I915_DISPWAY_POWT_INTEWWUPT |
		I915_DISPWAY_PIPE_A_EVENT_INTEWWUPT |
		I915_DISPWAY_PIPE_B_EVENT_INTEWWUPT |
		I915_WPE_PIPE_A_INTEWWUPT |
		I915_WPE_PIPE_B_INTEWWUPT;

	if (IS_CHEWWYVIEW(dev_pwiv))
		enabwe_mask |= I915_DISPWAY_PIPE_C_EVENT_INTEWWUPT |
			I915_WPE_PIPE_C_INTEWWUPT;

	dwm_WAWN_ON(&dev_pwiv->dwm, dev_pwiv->iwq_mask != ~0u);

	dev_pwiv->iwq_mask = ~enabwe_mask;

	GEN3_IWQ_INIT(uncowe, VWV_, dev_pwiv->iwq_mask, enabwe_mask);
}

void gen8_dispway_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	enum pipe pipe;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	intew_uncowe_wwite(uncowe, EDP_PSW_IMW, 0xffffffff);
	intew_uncowe_wwite(uncowe, EDP_PSW_IIW, 0xffffffff);

	fow_each_pipe(dev_pwiv, pipe)
		if (intew_dispway_powew_is_enabwed(dev_pwiv,
						   POWEW_DOMAIN_PIPE(pipe)))
			GEN8_IWQ_WESET_NDX(uncowe, DE_PIPE, pipe);

	GEN3_IWQ_WESET(uncowe, GEN8_DE_POWT_);
	GEN3_IWQ_WESET(uncowe, GEN8_DE_MISC_);
}

void gen11_dispway_iwq_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	enum pipe pipe;
	u32 twans_mask = BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) |
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_D);

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	intew_uncowe_wwite(uncowe, GEN11_DISPWAY_INT_CTW, 0);

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		enum twanscodew twans;

		fow_each_cpu_twanscodew_masked(dev_pwiv, twans, twans_mask) {
			enum intew_dispway_powew_domain domain;

			domain = POWEW_DOMAIN_TWANSCODEW(twans);
			if (!intew_dispway_powew_is_enabwed(dev_pwiv, domain))
				continue;

			intew_uncowe_wwite(uncowe, TWANS_PSW_IMW(twans), 0xffffffff);
			intew_uncowe_wwite(uncowe, TWANS_PSW_IIW(twans), 0xffffffff);
		}
	} ewse {
		intew_uncowe_wwite(uncowe, EDP_PSW_IMW, 0xffffffff);
		intew_uncowe_wwite(uncowe, EDP_PSW_IIW, 0xffffffff);
	}

	fow_each_pipe(dev_pwiv, pipe)
		if (intew_dispway_powew_is_enabwed(dev_pwiv,
						   POWEW_DOMAIN_PIPE(pipe)))
			GEN8_IWQ_WESET_NDX(uncowe, DE_PIPE, pipe);

	GEN3_IWQ_WESET(uncowe, GEN8_DE_POWT_);
	GEN3_IWQ_WESET(uncowe, GEN8_DE_MISC_);

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		GEN3_IWQ_WESET(uncowe, PICAINTEWWUPT_);
	ewse
		GEN3_IWQ_WESET(uncowe, GEN11_DE_HPD_);

	if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_ICP)
		GEN3_IWQ_WESET(uncowe, SDE);
}

void gen8_iwq_powew_weww_post_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				     u8 pipe_mask)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	u32 extwa_iew = GEN8_PIPE_VBWANK |
		gen8_de_pipe_undewwun_mask(dev_pwiv) |
		gen8_de_pipe_fwip_done_mask(dev_pwiv);
	enum pipe pipe;

	spin_wock_iwq(&dev_pwiv->iwq_wock);

	if (!intew_iwqs_enabwed(dev_pwiv)) {
		spin_unwock_iwq(&dev_pwiv->iwq_wock);
		wetuwn;
	}

	fow_each_pipe_masked(dev_pwiv, pipe, pipe_mask)
		GEN8_IWQ_INIT_NDX(uncowe, DE_PIPE, pipe,
				  dev_pwiv->de_iwq_mask[pipe],
				  ~dev_pwiv->de_iwq_mask[pipe] | extwa_iew);

	spin_unwock_iwq(&dev_pwiv->iwq_wock);
}

void gen8_iwq_powew_weww_pwe_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				     u8 pipe_mask)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	enum pipe pipe;

	spin_wock_iwq(&dev_pwiv->iwq_wock);

	if (!intew_iwqs_enabwed(dev_pwiv)) {
		spin_unwock_iwq(&dev_pwiv->iwq_wock);
		wetuwn;
	}

	fow_each_pipe_masked(dev_pwiv, pipe, pipe_mask)
		GEN8_IWQ_WESET_NDX(uncowe, DE_PIPE, pipe);

	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	/* make suwe we'we done pwocessing dispway iwqs */
	intew_synchwonize_iwq(dev_pwiv);
}

/*
 * SDEIEW is awso touched by the intewwupt handwew to wowk awound missed PCH
 * intewwupts. Hence we can't update it aftew the intewwupt handwew is enabwed -
 * instead we unconditionawwy enabwe aww PCH intewwupt souwces hewe, but then
 * onwy unmask them as needed with SDEIMW.
 *
 * Note that we cuwwentwy do this aftew instawwing the intewwupt handwew,
 * but befowe we enabwe the mastew intewwupt. That shouwd be sufficient
 * to avoid waces with the iwq handwew, assuming we have MSI. Shawed wegacy
 * intewwupts couwd stiww wace.
 */
static void ibx_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	u32 mask;

	if (HAS_PCH_NOP(dev_pwiv))
		wetuwn;

	if (HAS_PCH_IBX(dev_pwiv))
		mask = SDE_GMBUS | SDE_AUX_MASK | SDE_POISON;
	ewse if (HAS_PCH_CPT(dev_pwiv) || HAS_PCH_WPT(dev_pwiv))
		mask = SDE_GMBUS_CPT | SDE_AUX_MASK_CPT;
	ewse
		mask = SDE_GMBUS_CPT;

	GEN3_IWQ_INIT(uncowe, SDE, ~mask, 0xffffffff);
}

void vawweyview_enabwe_dispway_iwqs(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	if (dev_pwiv->dispway_iwqs_enabwed)
		wetuwn;

	dev_pwiv->dispway_iwqs_enabwed = twue;

	if (intew_iwqs_enabwed(dev_pwiv)) {
		vwv_dispway_iwq_weset(dev_pwiv);
		vwv_dispway_iwq_postinstaww(dev_pwiv);
	}
}

void vawweyview_disabwe_dispway_iwqs(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	if (!dev_pwiv->dispway_iwqs_enabwed)
		wetuwn;

	dev_pwiv->dispway_iwqs_enabwed = fawse;

	if (intew_iwqs_enabwed(dev_pwiv))
		vwv_dispway_iwq_weset(dev_pwiv);
}

void iwk_de_iwq_postinstaww(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	u32 dispway_mask, extwa_mask;

	if (GWAPHICS_VEW(i915) >= 7) {
		dispway_mask = (DE_MASTEW_IWQ_CONTWOW | DE_GSE_IVB |
				DE_PCH_EVENT_IVB | DE_AUX_CHANNEW_A_IVB);
		extwa_mask = (DE_PIPEC_VBWANK_IVB | DE_PIPEB_VBWANK_IVB |
			      DE_PIPEA_VBWANK_IVB | DE_EWW_INT_IVB |
			      DE_PWANE_FWIP_DONE_IVB(PWANE_C) |
			      DE_PWANE_FWIP_DONE_IVB(PWANE_B) |
			      DE_PWANE_FWIP_DONE_IVB(PWANE_A) |
			      DE_DP_A_HOTPWUG_IVB);
	} ewse {
		dispway_mask = (DE_MASTEW_IWQ_CONTWOW | DE_GSE | DE_PCH_EVENT |
				DE_AUX_CHANNEW_A | DE_PIPEB_CWC_DONE |
				DE_PIPEA_CWC_DONE | DE_POISON);
		extwa_mask = (DE_PIPEA_VBWANK | DE_PIPEB_VBWANK |
			      DE_PIPEB_FIFO_UNDEWWUN | DE_PIPEA_FIFO_UNDEWWUN |
			      DE_PWANE_FWIP_DONE(PWANE_A) |
			      DE_PWANE_FWIP_DONE(PWANE_B) |
			      DE_DP_A_HOTPWUG);
	}

	if (IS_HASWEWW(i915)) {
		gen3_assewt_iiw_is_zewo(uncowe, EDP_PSW_IIW);
		dispway_mask |= DE_EDP_PSW_INT_HSW;
	}

	if (IS_IWONWAKE_M(i915))
		extwa_mask |= DE_PCU_EVENT;

	i915->iwq_mask = ~dispway_mask;

	ibx_iwq_postinstaww(i915);

	GEN3_IWQ_INIT(uncowe, DE, i915->iwq_mask,
		      dispway_mask | extwa_mask);
}

static void mtp_iwq_postinstaww(stwuct dwm_i915_pwivate *i915);
static void icp_iwq_postinstaww(stwuct dwm_i915_pwivate *i915);

void gen8_de_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;

	u32 de_pipe_masked = gen8_de_pipe_fauwt_mask(dev_pwiv) |
		GEN8_PIPE_CDCWK_CWC_DONE;
	u32 de_pipe_enabwes;
	u32 de_powt_masked = gen8_de_powt_aux_mask(dev_pwiv);
	u32 de_powt_enabwes;
	u32 de_misc_masked = GEN8_DE_EDP_PSW;
	u32 twans_mask = BIT(TWANSCODEW_A) | BIT(TWANSCODEW_B) |
		BIT(TWANSCODEW_C) | BIT(TWANSCODEW_D);
	enum pipe pipe;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		mtp_iwq_postinstaww(dev_pwiv);
	ewse if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_ICP)
		icp_iwq_postinstaww(dev_pwiv);
	ewse if (HAS_PCH_SPWIT(dev_pwiv))
		ibx_iwq_postinstaww(dev_pwiv);

	if (DISPWAY_VEW(dev_pwiv) < 11)
		de_misc_masked |= GEN8_DE_MISC_GSE;

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		de_powt_masked |= BXT_DE_POWT_GMBUS;

	if (DISPWAY_VEW(dev_pwiv) >= 14) {
		de_misc_masked |= XEWPDP_PMDEMAND_WSPTOUT_EWW |
				  XEWPDP_PMDEMAND_WSP;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 11) {
		enum powt powt;

		if (intew_bios_is_dsi_pwesent(dev_pwiv, &powt))
			de_powt_masked |= DSI0_TE | DSI1_TE;
	}

	de_pipe_enabwes = de_pipe_masked |
		GEN8_PIPE_VBWANK |
		gen8_de_pipe_undewwun_mask(dev_pwiv) |
		gen8_de_pipe_fwip_done_mask(dev_pwiv);

	de_powt_enabwes = de_powt_masked;
	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		de_powt_enabwes |= BXT_DE_POWT_HOTPWUG_MASK;
	ewse if (IS_BWOADWEWW(dev_pwiv))
		de_powt_enabwes |= BDW_DE_POWT_HOTPWUG_MASK;

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		enum twanscodew twans;

		fow_each_cpu_twanscodew_masked(dev_pwiv, twans, twans_mask) {
			enum intew_dispway_powew_domain domain;

			domain = POWEW_DOMAIN_TWANSCODEW(twans);
			if (!intew_dispway_powew_is_enabwed(dev_pwiv, domain))
				continue;

			gen3_assewt_iiw_is_zewo(uncowe, TWANS_PSW_IIW(twans));
		}
	} ewse {
		gen3_assewt_iiw_is_zewo(uncowe, EDP_PSW_IIW);
	}

	fow_each_pipe(dev_pwiv, pipe) {
		dev_pwiv->de_iwq_mask[pipe] = ~de_pipe_masked;

		if (intew_dispway_powew_is_enabwed(dev_pwiv,
						   POWEW_DOMAIN_PIPE(pipe)))
			GEN8_IWQ_INIT_NDX(uncowe, DE_PIPE, pipe,
					  dev_pwiv->de_iwq_mask[pipe],
					  de_pipe_enabwes);
	}

	GEN3_IWQ_INIT(uncowe, GEN8_DE_POWT_, ~de_powt_masked, de_powt_enabwes);
	GEN3_IWQ_INIT(uncowe, GEN8_DE_MISC_, ~de_misc_masked, de_misc_masked);

	if (IS_DISPWAY_VEW(dev_pwiv, 11, 13)) {
		u32 de_hpd_masked = 0;
		u32 de_hpd_enabwes = GEN11_DE_TC_HOTPWUG_MASK |
				     GEN11_DE_TBT_HOTPWUG_MASK;

		GEN3_IWQ_INIT(uncowe, GEN11_DE_HPD_, ~de_hpd_masked,
			      de_hpd_enabwes);
	}
}

static void mtp_iwq_postinstaww(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	u32 sde_mask = SDE_GMBUS_ICP | SDE_PICAINTEWWUPT;
	u32 de_hpd_mask = XEWPDP_AUX_TC_MASK;
	u32 de_hpd_enabwes = de_hpd_mask | XEWPDP_DP_AWT_HOTPWUG_MASK |
			     XEWPDP_TBT_HOTPWUG_MASK;

	GEN3_IWQ_INIT(uncowe, PICAINTEWWUPT_, ~de_hpd_mask,
		      de_hpd_enabwes);

	GEN3_IWQ_INIT(uncowe, SDE, ~sde_mask, 0xffffffff);
}

static void icp_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	u32 mask = SDE_GMBUS_ICP;

	GEN3_IWQ_INIT(uncowe, SDE, ~mask, 0xffffffff);
}

void gen11_de_iwq_postinstaww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	gen8_de_iwq_postinstaww(dev_pwiv);

	intew_uncowe_wwite(&dev_pwiv->uncowe, GEN11_DISPWAY_INT_CTW,
			   GEN11_DISPWAY_IWQ_ENABWE);
}

void dg1_de_iwq_postinstaww(stwuct dwm_i915_pwivate *i915)
{
	if (!HAS_DISPWAY(i915))
		wetuwn;

	gen8_de_iwq_postinstaww(i915);
	intew_uncowe_wwite(&i915->uncowe, GEN11_DISPWAY_INT_CTW,
			   GEN11_DISPWAY_IWQ_ENABWE);
}

void intew_dispway_iwq_init(stwuct dwm_i915_pwivate *i915)
{
	i915->dwm.vbwank_disabwe_immediate = twue;

	/*
	 * Most pwatfowms tweat the dispway iwq bwock as an awways-on powew
	 * domain. vwv/chv can disabwe it at wuntime and need speciaw cawe to
	 * avoid wwiting any of the dispway bwock wegistews outside of the powew
	 * domain. We defew setting up the dispway iwqs in this case to the
	 * wuntime pm.
	 */
	i915->dispway_iwqs_enabwed = twue;
	if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915))
		i915->dispway_iwqs_enabwed = fawse;

	intew_hotpwug_iwq_init(i915);
}
