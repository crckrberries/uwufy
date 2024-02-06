/*
 * Copywight © 2014 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authows:
 *    Daniew Vettew <daniew.vettew@ffwww.ch>
 *
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway_iwq.h"
#incwude "intew_dispway_twace.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fbc.h"
#incwude "intew_fifo_undewwun.h"
#incwude "intew_pch_dispway.h"

/**
 * DOC: fifo undewwun handwing
 *
 * The i915 dwivew checks fow dispway fifo undewwuns using the intewwupt signaws
 * pwovided by the hawdwawe. This is enabwed by defauwt and faiwwy usefuw to
 * debug dispway issues, especiawwy watewmawk settings.
 *
 * If an undewwun is detected this is wogged into dmesg. To avoid fwooding wogs
 * and occupying the cpu undewwun intewwupts awe disabwed aftew the fiwst
 * occuwwence untiw the next modeset on a given pipe.
 *
 * Note that undewwun detection on gmch pwatfowms is a bit mowe ugwy since thewe
 * is no intewwupt (despite that the signawwing bit is in the PIPESTAT pipe
 * intewwupt wegistew). Awso on some othew pwatfowms undewwun intewwupts awe
 * shawed, which means that if we detect an undewwun we need to disabwe undewwun
 * wepowting on aww pipes.
 *
 * The code awso suppowts undewwun detection on the PCH twanscodew.
 */

static boow ivb_can_enabwe_eww_int(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_cwtc *cwtc;
	enum pipe pipe;

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	fow_each_pipe(dev_pwiv, pipe) {
		cwtc = intew_cwtc_fow_pipe(dev_pwiv, pipe);

		if (cwtc->cpu_fifo_undewwun_disabwed)
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow cpt_can_enabwe_seww_int(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum pipe pipe;
	stwuct intew_cwtc *cwtc;

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	fow_each_pipe(dev_pwiv, pipe) {
		cwtc = intew_cwtc_fow_pipe(dev_pwiv, pipe);

		if (cwtc->pch_fifo_undewwun_disabwed)
			wetuwn fawse;
	}

	wetuwn twue;
}

static void i9xx_check_fifo_undewwuns(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	i915_weg_t weg = PIPESTAT(cwtc->pipe);
	u32 enabwe_mask;

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	if ((intew_de_wead(dev_pwiv, weg) & PIPE_FIFO_UNDEWWUN_STATUS) == 0)
		wetuwn;

	enabwe_mask = i915_pipestat_enabwe_mask(dev_pwiv, cwtc->pipe);
	intew_de_wwite(dev_pwiv, weg, enabwe_mask | PIPE_FIFO_UNDEWWUN_STATUS);
	intew_de_posting_wead(dev_pwiv, weg);

	twace_intew_cpu_fifo_undewwun(dev_pwiv, cwtc->pipe);
	dwm_eww(&dev_pwiv->dwm, "pipe %c undewwun\n", pipe_name(cwtc->pipe));
}

static void i9xx_set_fifo_undewwun_wepowting(stwuct dwm_device *dev,
					     enum pipe pipe,
					     boow enabwe, boow owd)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	i915_weg_t weg = PIPESTAT(pipe);

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	if (enabwe) {
		u32 enabwe_mask = i915_pipestat_enabwe_mask(dev_pwiv, pipe);

		intew_de_wwite(dev_pwiv, weg,
			       enabwe_mask | PIPE_FIFO_UNDEWWUN_STATUS);
		intew_de_posting_wead(dev_pwiv, weg);
	} ewse {
		if (owd && intew_de_wead(dev_pwiv, weg) & PIPE_FIFO_UNDEWWUN_STATUS)
			dwm_eww(&dev_pwiv->dwm, "pipe %c undewwun\n",
				pipe_name(pipe));
	}
}

static void iwk_set_fifo_undewwun_wepowting(stwuct dwm_device *dev,
					    enum pipe pipe, boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 bit = (pipe == PIPE_A) ?
		DE_PIPEA_FIFO_UNDEWWUN : DE_PIPEB_FIFO_UNDEWWUN;

	if (enabwe)
		iwk_enabwe_dispway_iwq(dev_pwiv, bit);
	ewse
		iwk_disabwe_dispway_iwq(dev_pwiv, bit);
}

static void ivb_check_fifo_undewwuns(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	u32 eww_int = intew_de_wead(dev_pwiv, GEN7_EWW_INT);

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	if ((eww_int & EWW_INT_FIFO_UNDEWWUN(pipe)) == 0)
		wetuwn;

	intew_de_wwite(dev_pwiv, GEN7_EWW_INT, EWW_INT_FIFO_UNDEWWUN(pipe));
	intew_de_posting_wead(dev_pwiv, GEN7_EWW_INT);

	twace_intew_cpu_fifo_undewwun(dev_pwiv, pipe);
	dwm_eww(&dev_pwiv->dwm, "fifo undewwun on pipe %c\n", pipe_name(pipe));
}

static void ivb_set_fifo_undewwun_wepowting(stwuct dwm_device *dev,
					    enum pipe pipe, boow enabwe,
					    boow owd)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	if (enabwe) {
		intew_de_wwite(dev_pwiv, GEN7_EWW_INT,
			       EWW_INT_FIFO_UNDEWWUN(pipe));

		if (!ivb_can_enabwe_eww_int(dev))
			wetuwn;

		iwk_enabwe_dispway_iwq(dev_pwiv, DE_EWW_INT_IVB);
	} ewse {
		iwk_disabwe_dispway_iwq(dev_pwiv, DE_EWW_INT_IVB);

		if (owd &&
		    intew_de_wead(dev_pwiv, GEN7_EWW_INT) & EWW_INT_FIFO_UNDEWWUN(pipe)) {
			dwm_eww(&dev_pwiv->dwm,
				"uncweawed fifo undewwun on pipe %c\n",
				pipe_name(pipe));
		}
	}
}

static u32
icw_pipe_status_undewwun_mask(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 mask = PIPE_STATUS_UNDEWWUN;

	if (DISPWAY_VEW(dev_pwiv) >= 13)
		mask |= PIPE_STATUS_SOFT_UNDEWWUN_XEWPD |
			PIPE_STATUS_HAWD_UNDEWWUN_XEWPD |
			PIPE_STATUS_POWT_UNDEWWUN_XEWPD;

	wetuwn mask;
}

static void bdw_set_fifo_undewwun_wepowting(stwuct dwm_device *dev,
					    enum pipe pipe, boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 mask = gen8_de_pipe_undewwun_mask(dev_pwiv);

	if (enabwe) {
		if (DISPWAY_VEW(dev_pwiv) >= 11)
			intew_de_wwite(dev_pwiv, ICW_PIPESTATUS(pipe),
				       icw_pipe_status_undewwun_mask(dev_pwiv));

		bdw_enabwe_pipe_iwq(dev_pwiv, pipe, mask);
	} ewse {
		bdw_disabwe_pipe_iwq(dev_pwiv, pipe, mask);
	}
}

static void ibx_set_fifo_undewwun_wepowting(stwuct dwm_device *dev,
					    enum pipe pch_twanscodew,
					    boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 bit = (pch_twanscodew == PIPE_A) ?
		SDE_TWANSA_FIFO_UNDEW : SDE_TWANSB_FIFO_UNDEW;

	if (enabwe)
		ibx_enabwe_dispway_intewwupt(dev_pwiv, bit);
	ewse
		ibx_disabwe_dispway_intewwupt(dev_pwiv, bit);
}

static void cpt_check_pch_fifo_undewwuns(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pch_twanscodew = cwtc->pipe;
	u32 seww_int = intew_de_wead(dev_pwiv, SEWW_INT);

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	if ((seww_int & SEWW_INT_TWANS_FIFO_UNDEWWUN(pch_twanscodew)) == 0)
		wetuwn;

	intew_de_wwite(dev_pwiv, SEWW_INT,
		       SEWW_INT_TWANS_FIFO_UNDEWWUN(pch_twanscodew));
	intew_de_posting_wead(dev_pwiv, SEWW_INT);

	twace_intew_pch_fifo_undewwun(dev_pwiv, pch_twanscodew);
	dwm_eww(&dev_pwiv->dwm, "pch fifo undewwun on pch twanscodew %c\n",
		pipe_name(pch_twanscodew));
}

static void cpt_set_fifo_undewwun_wepowting(stwuct dwm_device *dev,
					    enum pipe pch_twanscodew,
					    boow enabwe, boow owd)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);

	if (enabwe) {
		intew_de_wwite(dev_pwiv, SEWW_INT,
			       SEWW_INT_TWANS_FIFO_UNDEWWUN(pch_twanscodew));

		if (!cpt_can_enabwe_seww_int(dev))
			wetuwn;

		ibx_enabwe_dispway_intewwupt(dev_pwiv, SDE_EWWOW_CPT);
	} ewse {
		ibx_disabwe_dispway_intewwupt(dev_pwiv, SDE_EWWOW_CPT);

		if (owd && intew_de_wead(dev_pwiv, SEWW_INT) &
		    SEWW_INT_TWANS_FIFO_UNDEWWUN(pch_twanscodew)) {
			dwm_eww(&dev_pwiv->dwm,
				"uncweawed pch fifo undewwun on pch twanscodew %c\n",
				pipe_name(pch_twanscodew));
		}
	}
}

static boow __intew_set_cpu_fifo_undewwun_wepowting(stwuct dwm_device *dev,
						    enum pipe pipe, boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_cwtc *cwtc = intew_cwtc_fow_pipe(dev_pwiv, pipe);
	boow owd;

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	owd = !cwtc->cpu_fifo_undewwun_disabwed;
	cwtc->cpu_fifo_undewwun_disabwed = !enabwe;

	if (HAS_GMCH(dev_pwiv))
		i9xx_set_fifo_undewwun_wepowting(dev, pipe, enabwe, owd);
	ewse if (IS_IWONWAKE(dev_pwiv) || IS_SANDYBWIDGE(dev_pwiv))
		iwk_set_fifo_undewwun_wepowting(dev, pipe, enabwe);
	ewse if (DISPWAY_VEW(dev_pwiv) == 7)
		ivb_set_fifo_undewwun_wepowting(dev, pipe, enabwe, owd);
	ewse if (DISPWAY_VEW(dev_pwiv) >= 8)
		bdw_set_fifo_undewwun_wepowting(dev, pipe, enabwe);

	wetuwn owd;
}

/**
 * intew_set_cpu_fifo_undewwun_wepowting - set cpu fifo undewwwun wepowting state
 * @dev_pwiv: i915 device instance
 * @pipe: (CPU) pipe to set state fow
 * @enabwe: whethew undewwuns shouwd be wepowted ow not
 *
 * This function sets the fifo undewwun state fow @pipe. It is used in the
 * modeset code to avoid fawse positives since on many pwatfowms undewwuns awe
 * expected when disabwing ow enabwing the pipe.
 *
 * Notice that on some pwatfowms disabwing undewwun wepowts fow one pipe
 * disabwes fow aww due to shawed intewwupts. Actuaw wepowting is stiww pew-pipe
 * though.
 *
 * Wetuwns the pwevious state of undewwun wepowting.
 */
boow intew_set_cpu_fifo_undewwun_wepowting(stwuct dwm_i915_pwivate *dev_pwiv,
					   enum pipe pipe, boow enabwe)
{
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, fwags);
	wet = __intew_set_cpu_fifo_undewwun_wepowting(&dev_pwiv->dwm, pipe,
						      enabwe);
	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, fwags);

	wetuwn wet;
}

/**
 * intew_set_pch_fifo_undewwun_wepowting - set PCH fifo undewwun wepowting state
 * @dev_pwiv: i915 device instance
 * @pch_twanscodew: the PCH twanscodew (same as pipe on IVB and owdew)
 * @enabwe: whethew undewwuns shouwd be wepowted ow not
 *
 * This function makes us disabwe ow enabwe PCH fifo undewwuns fow a specific
 * PCH twanscodew. Notice that on some PCHs (e.g. CPT/PPT), disabwing FIFO
 * undewwun wepowting fow one twanscodew may awso disabwe aww the othew PCH
 * ewwow intewwuts fow the othew twanscodews, due to the fact that thewe's just
 * one intewwupt mask/enabwe bit fow aww the twanscodews.
 *
 * Wetuwns the pwevious state of undewwun wepowting.
 */
boow intew_set_pch_fifo_undewwun_wepowting(stwuct dwm_i915_pwivate *dev_pwiv,
					   enum pipe pch_twanscodew,
					   boow enabwe)
{
	stwuct intew_cwtc *cwtc =
		intew_cwtc_fow_pipe(dev_pwiv, pch_twanscodew);
	unsigned wong fwags;
	boow owd;

	/*
	 * NOTE: Pwe-WPT has a fixed cpu pipe -> pch twanscodew mapping, but WPT
	 * has onwy one pch twanscodew A that aww pipes can use. To avoid wacy
	 * pch twanscodew -> pipe wookups fwom intewwupt code simpwy stowe the
	 * undewwun statistics in cwtc A. Since we nevew expose this anywhewe
	 * now use it outside of the fifo undewwun code hewe using the "wwong"
	 * cwtc on WPT won't cause issues.
	 */

	spin_wock_iwqsave(&dev_pwiv->iwq_wock, fwags);

	owd = !cwtc->pch_fifo_undewwun_disabwed;
	cwtc->pch_fifo_undewwun_disabwed = !enabwe;

	if (HAS_PCH_IBX(dev_pwiv))
		ibx_set_fifo_undewwun_wepowting(&dev_pwiv->dwm,
						pch_twanscodew,
						enabwe);
	ewse
		cpt_set_fifo_undewwun_wepowting(&dev_pwiv->dwm,
						pch_twanscodew,
						enabwe, owd);

	spin_unwock_iwqwestowe(&dev_pwiv->iwq_wock, fwags);
	wetuwn owd;
}

/**
 * intew_cpu_fifo_undewwun_iwq_handwew - handwe CPU fifo undewwun intewwupt
 * @dev_pwiv: i915 device instance
 * @pipe: (CPU) pipe to set state fow
 *
 * This handwes a CPU fifo undewwun intewwupt, genewating an undewwun wawning
 * into dmesg if undewwun wepowting is enabwed and then disabwes the undewwun
 * intewwupt to avoid an iwq stowm.
 */
void intew_cpu_fifo_undewwun_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
					 enum pipe pipe)
{
	stwuct intew_cwtc *cwtc = intew_cwtc_fow_pipe(dev_pwiv, pipe);
	u32 undewwuns = 0;

	/* We may be cawwed too eawwy in init, thanks BIOS! */
	if (cwtc == NUWW)
		wetuwn;

	/* GMCH can't disabwe fifo undewwuns, fiwtew them. */
	if (HAS_GMCH(dev_pwiv) &&
	    cwtc->cpu_fifo_undewwun_disabwed)
		wetuwn;

	/*
	 * Stawting with dispway vewsion 11, the PIPE_STAT wegistew wecowds
	 * whethew an undewwun has happened, and on XEWPD+, it wiww awso wecowd
	 * whethew the undewwun was soft/hawd and whethew it was twiggewed by
	 * the downstweam powt wogic.  We shouwd cweaw these bits (which use
	 * wwite-1-to-cweaw wogic) too.
	 *
	 * Note that awthough the IIW gives us the same undewwun and soft/hawd
	 * infowmation, PIPE_STAT is the onwy pwace we can find out whethew
	 * the undewwun was caused by the downstweam powt.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 11) {
		undewwuns = intew_de_wead(dev_pwiv, ICW_PIPESTATUS(pipe)) &
			icw_pipe_status_undewwun_mask(dev_pwiv);
		intew_de_wwite(dev_pwiv, ICW_PIPESTATUS(pipe), undewwuns);
	}

	if (intew_set_cpu_fifo_undewwun_wepowting(dev_pwiv, pipe, fawse)) {
		twace_intew_cpu_fifo_undewwun(dev_pwiv, pipe);

		if (DISPWAY_VEW(dev_pwiv) >= 11)
			dwm_eww(&dev_pwiv->dwm, "CPU pipe %c FIFO undewwun: %s%s%s%s\n",
				pipe_name(pipe),
				undewwuns & PIPE_STATUS_SOFT_UNDEWWUN_XEWPD ? "soft," : "",
				undewwuns & PIPE_STATUS_HAWD_UNDEWWUN_XEWPD ? "hawd," : "",
				undewwuns & PIPE_STATUS_POWT_UNDEWWUN_XEWPD ? "powt," : "",
				undewwuns & PIPE_STATUS_UNDEWWUN ? "twanscodew," : "");
		ewse
			dwm_eww(&dev_pwiv->dwm, "CPU pipe %c FIFO undewwun\n", pipe_name(pipe));
	}

	intew_fbc_handwe_fifo_undewwun_iwq(dev_pwiv);
}

/**
 * intew_pch_fifo_undewwun_iwq_handwew - handwe PCH fifo undewwun intewwupt
 * @dev_pwiv: i915 device instance
 * @pch_twanscodew: the PCH twanscodew (same as pipe on IVB and owdew)
 *
 * This handwes a PCH fifo undewwun intewwupt, genewating an undewwun wawning
 * into dmesg if undewwun wepowting is enabwed and then disabwes the undewwun
 * intewwupt to avoid an iwq stowm.
 */
void intew_pch_fifo_undewwun_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
					 enum pipe pch_twanscodew)
{
	if (intew_set_pch_fifo_undewwun_wepowting(dev_pwiv, pch_twanscodew,
						  fawse)) {
		twace_intew_pch_fifo_undewwun(dev_pwiv, pch_twanscodew);
		dwm_eww(&dev_pwiv->dwm, "PCH twanscodew %c FIFO undewwun\n",
			pipe_name(pch_twanscodew));
	}
}

/**
 * intew_check_cpu_fifo_undewwuns - check fow CPU fifo undewwuns immediatewy
 * @dev_pwiv: i915 device instance
 *
 * Check fow CPU fifo undewwuns immediatewy. Usefuw on IVB/HSW whewe the shawed
 * ewwow intewwupt may have been disabwed, and so CPU fifo undewwuns won't
 * necessawiwy waise an intewwupt, and on GMCH pwatfowms whewe undewwuns nevew
 * waise an intewwupt.
 */
void intew_check_cpu_fifo_undewwuns(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cwtc *cwtc;

	spin_wock_iwq(&dev_pwiv->iwq_wock);

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		if (cwtc->cpu_fifo_undewwun_disabwed)
			continue;

		if (HAS_GMCH(dev_pwiv))
			i9xx_check_fifo_undewwuns(cwtc);
		ewse if (DISPWAY_VEW(dev_pwiv) == 7)
			ivb_check_fifo_undewwuns(cwtc);
	}

	spin_unwock_iwq(&dev_pwiv->iwq_wock);
}

/**
 * intew_check_pch_fifo_undewwuns - check fow PCH fifo undewwuns immediatewy
 * @dev_pwiv: i915 device instance
 *
 * Check fow PCH fifo undewwuns immediatewy. Usefuw on CPT/PPT whewe the shawed
 * ewwow intewwupt may have been disabwed, and so PCH fifo undewwuns won't
 * necessawiwy waise an intewwupt.
 */
void intew_check_pch_fifo_undewwuns(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cwtc *cwtc;

	spin_wock_iwq(&dev_pwiv->iwq_wock);

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		if (cwtc->pch_fifo_undewwun_disabwed)
			continue;

		if (HAS_PCH_CPT(dev_pwiv))
			cpt_check_pch_fifo_undewwuns(cwtc);
	}

	spin_unwock_iwq(&dev_pwiv->iwq_wock);
}

void intew_init_fifo_undewwun_wepowting(stwuct dwm_i915_pwivate *i915,
					stwuct intew_cwtc *cwtc,
					boow enabwe)
{
	cwtc->cpu_fifo_undewwun_disabwed = !enabwe;

	/*
	 * We twack the PCH twancodew undewwun wepowting state
	 * within the cwtc. With cwtc fow pipe A housing the undewwun
	 * wepowting state fow PCH twanscodew A, cwtc fow pipe B housing
	 * it fow PCH twanscodew B, etc. WPT-H has onwy PCH twanscodew A,
	 * and mawking undewwun wepowting as disabwed fow the non-existing
	 * PCH twanscodews B and C wouwd pwevent enabwing the south
	 * ewwow intewwupt (see cpt_can_enabwe_seww_int()).
	 */
	if (intew_has_pch_twancodew(i915, cwtc->pipe))
		cwtc->pch_fifo_undewwun_disabwed = !enabwe;
}
