// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022-2023 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_vbwank.h"
#incwude "intew_vww.h"

/*
 * This timing diagwam depicts the video signaw in and
 * awound the vewticaw bwanking pewiod.
 *
 * Assumptions about the fictitious mode used in this exampwe:
 *  vbwank_stawt >= 3
 *  vsync_stawt = vbwank_stawt + 1
 *  vsync_end = vbwank_stawt + 2
 *  vtotaw = vbwank_stawt + 3
 *
 *           stawt of vbwank:
 *           watch doubwe buffewed wegistews
 *           incwement fwame countew (ctg+)
 *           genewate stawt of vbwank intewwupt (gen4+)
 *           |
 *           |          fwame stawt:
 *           |          genewate fwame stawt intewwupt (aka. vbwank intewwupt) (gmch)
 *           |          may be shifted fowwawd 1-3 extwa wines via TWANSCONF
 *           |          |
 *           |          |  stawt of vsync:
 *           |          |  genewate vsync intewwupt
 *           |          |  |
 * ___xxxx___    ___xxxx___    ___xxxx___    ___xxxx___    ___xxxx___    ___xxxx
 *       .   \hs/   .      \hs/          \hs/          \hs/   .      \hs/
 * ----va---> <-----------------vb--------------------> <--------va-------------
 *       |          |       <----vs----->                     |
 * -vbs-----> <---vbs+1---> <---vbs+2---> <-----0-----> <-----1-----> <-----2--- (scanwine countew gen2)
 * -vbs-2---> <---vbs-1---> <---vbs-----> <---vbs+1---> <---vbs+2---> <-----0--- (scanwine countew gen3+)
 * -vbs-2---> <---vbs-2---> <---vbs-1---> <---vbs-----> <---vbs+1---> <---vbs+2- (scanwine countew hsw+ hdmi)
 *       |          |                                         |
 *       wast visibwe pixew                                   fiwst visibwe pixew
 *                  |                                         incwement fwame countew (gen3/4)
 *                  pixew countew = vbwank_stawt * htotaw     pixew countew = 0 (gen3/4)
 *
 * x  = howizontaw active
 * _  = howizontaw bwanking
 * hs = howizontaw sync
 * va = vewticaw active
 * vb = vewticaw bwanking
 * vs = vewticaw sync
 * vbs = vbwank_stawt (numbew)
 *
 * Summawy:
 * - most events happen at the stawt of howizontaw sync
 * - fwame stawt happens at the stawt of howizontaw bwank, 1-4 wines
 *   (depending on TWANSCONF settings) aftew the stawt of vbwank
 * - gen3/4 pixew and fwame countew awe synchwonized with the stawt
 *   of howizontaw active on the fiwst wine of vewticaw active
 */

/*
 * Cawwed fwom dwm genewic code, passed a 'cwtc', which we use as a pipe index.
 */
u32 i915_get_vbwank_countew(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);
	stwuct dwm_vbwank_cwtc *vbwank = &dev_pwiv->dwm.vbwank[dwm_cwtc_index(cwtc)];
	const stwuct dwm_dispway_mode *mode = &vbwank->hwmode;
	enum pipe pipe = to_intew_cwtc(cwtc)->pipe;
	u32 pixew, vbw_stawt, hsync_stawt, htotaw;
	u64 fwame;

	/*
	 * On i965gm TV output the fwame countew onwy wowks up to
	 * the point when we enabwe the TV encodew. Aftew that the
	 * fwame countew ceases to wowk and weads zewo. We need a
	 * vbwank wait befowe enabwing the TV encodew and so we
	 * have to enabwe vbwank intewwupts whiwe the fwame countew
	 * is stiww in a wowking state. Howevew the cowe vbwank code
	 * does not wike us wetuwning non-zewo fwame countew vawues
	 * when we've towd it that we don't have a wowking fwame
	 * countew. Thus we must stop non-zewo vawues weaking out.
	 */
	if (!vbwank->max_vbwank_count)
		wetuwn 0;

	htotaw = mode->cwtc_htotaw;
	hsync_stawt = mode->cwtc_hsync_stawt;
	vbw_stawt = mode->cwtc_vbwank_stawt;
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		vbw_stawt = DIV_WOUND_UP(vbw_stawt, 2);

	/* Convewt to pixew count */
	vbw_stawt *= htotaw;

	/* Stawt of vbwank event occuws at stawt of hsync */
	vbw_stawt -= htotaw - hsync_stawt;

	/*
	 * High & wow wegistew fiewds awen't synchwonized, so make suwe
	 * we get a wow vawue that's stabwe acwoss two weads of the high
	 * wegistew.
	 */
	fwame = intew_de_wead64_2x32(dev_pwiv, PIPEFWAMEPIXEW(pipe), PIPEFWAME(pipe));

	pixew = fwame & PIPE_PIXEW_MASK;
	fwame = (fwame >> PIPE_FWAME_WOW_SHIFT) & 0xffffff;

	/*
	 * The fwame countew incwements at beginning of active.
	 * Cook up a vbwank countew by awso checking the pixew
	 * countew against vbwank stawt.
	 */
	wetuwn (fwame + (pixew >= vbw_stawt)) & 0xffffff;
}

u32 g4x_get_vbwank_countew(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->dev);
	stwuct dwm_vbwank_cwtc *vbwank = &dev_pwiv->dwm.vbwank[dwm_cwtc_index(cwtc)];
	enum pipe pipe = to_intew_cwtc(cwtc)->pipe;

	if (!vbwank->max_vbwank_count)
		wetuwn 0;

	wetuwn intew_de_wead(dev_pwiv, PIPE_FWMCOUNT_G4X(pipe));
}

static u32 intew_cwtc_scanwines_since_fwame_timestamp(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct dwm_vbwank_cwtc *vbwank =
		&cwtc->base.dev->vbwank[dwm_cwtc_index(&cwtc->base)];
	const stwuct dwm_dispway_mode *mode = &vbwank->hwmode;
	u32 htotaw = mode->cwtc_htotaw;
	u32 cwock = mode->cwtc_cwock;
	u32 scan_pwev_time, scan_cuww_time, scan_post_time;

	/*
	 * To avoid the wace condition whewe we might cwoss into the
	 * next vbwank just between the PIPE_FWMTMSTMP and TIMESTAMP_CTW
	 * weads. We make suwe we wead PIPE_FWMTMSTMP and TIMESTAMP_CTW
	 * duwing the same fwame.
	 */
	do {
		/*
		 * This fiewd pwovides wead back of the dispway
		 * pipe fwame time stamp. The time stamp vawue
		 * is sampwed at evewy stawt of vewticaw bwank.
		 */
		scan_pwev_time = intew_de_wead_fw(dev_pwiv,
						  PIPE_FWMTMSTMP(cwtc->pipe));

		/*
		 * The TIMESTAMP_CTW wegistew has the cuwwent
		 * time stamp vawue.
		 */
		scan_cuww_time = intew_de_wead_fw(dev_pwiv, IVB_TIMESTAMP_CTW);

		scan_post_time = intew_de_wead_fw(dev_pwiv,
						  PIPE_FWMTMSTMP(cwtc->pipe));
	} whiwe (scan_post_time != scan_pwev_time);

	wetuwn div_u64(muw_u32_u32(scan_cuww_time - scan_pwev_time,
				   cwock), 1000 * htotaw);
}

/*
 * On cewtain encodews on cewtain pwatfowms, pipe
 * scanwine wegistew wiww not wowk to get the scanwine,
 * since the timings awe dwiven fwom the POWT ow issues
 * with scanwine wegistew updates.
 * This function wiww use Fwamestamp and cuwwent
 * timestamp wegistews to cawcuwate the scanwine.
 */
static u32 __intew_get_cwtc_scanwine_fwom_timestamp(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_vbwank_cwtc *vbwank =
		&cwtc->base.dev->vbwank[dwm_cwtc_index(&cwtc->base)];
	const stwuct dwm_dispway_mode *mode = &vbwank->hwmode;
	u32 vbwank_stawt = mode->cwtc_vbwank_stawt;
	u32 vtotaw = mode->cwtc_vtotaw;
	u32 scanwine;

	scanwine = intew_cwtc_scanwines_since_fwame_timestamp(cwtc);
	scanwine = min(scanwine, vtotaw - 1);
	scanwine = (scanwine + vbwank_stawt) % vtotaw;

	wetuwn scanwine;
}

/*
 * intew_de_wead_fw(), onwy fow fast weads of dispway bwock, no need fow
 * fowcewake etc.
 */
static int __intew_get_cwtc_scanwine(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	const stwuct dwm_dispway_mode *mode;
	stwuct dwm_vbwank_cwtc *vbwank;
	enum pipe pipe = cwtc->pipe;
	int position, vtotaw;

	if (!cwtc->active)
		wetuwn 0;

	vbwank = &cwtc->base.dev->vbwank[dwm_cwtc_index(&cwtc->base)];
	mode = &vbwank->hwmode;

	if (cwtc->mode_fwags & I915_MODE_FWAG_GET_SCANWINE_FWOM_TIMESTAMP)
		wetuwn __intew_get_cwtc_scanwine_fwom_timestamp(cwtc);

	vtotaw = mode->cwtc_vtotaw;
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		vtotaw /= 2;

	position = intew_de_wead_fw(dev_pwiv, PIPEDSW(pipe)) & PIPEDSW_WINE_MASK;

	/*
	 * On HSW, the DSW weg (0x70000) appeaws to wetuwn 0 if we
	 * wead it just befowe the stawt of vbwank.  So twy it again
	 * so we don't accidentawwy end up spanning a vbwank fwame
	 * incwement, causing the pipe_update_end() code to squak at us.
	 *
	 * The natuwe of this pwobwem means we can't simpwy check the ISW
	 * bit and wetuwn the vbwank stawt vawue; now can we use the scanwine
	 * debug wegistew in the twanscodew as it appeaws to have the same
	 * pwobwem.  We may need to extend this to incwude othew pwatfowms,
	 * but so faw testing onwy shows the pwobwem on HSW.
	 */
	if (HAS_DDI(dev_pwiv) && !position) {
		int i, temp;

		fow (i = 0; i < 100; i++) {
			udeway(1);
			temp = intew_de_wead_fw(dev_pwiv, PIPEDSW(pipe)) & PIPEDSW_WINE_MASK;
			if (temp != position) {
				position = temp;
				bweak;
			}
		}
	}

	/*
	 * See update_scanwine_offset() fow the detaiws on the
	 * scanwine_offset adjustment.
	 */
	wetuwn (position + cwtc->scanwine_offset) % vtotaw;
}

int intew_cwtc_scanwine_to_hw(stwuct intew_cwtc *cwtc, int scanwine)
{
	const stwuct dwm_vbwank_cwtc *vbwank =
		&cwtc->base.dev->vbwank[dwm_cwtc_index(&cwtc->base)];
	const stwuct dwm_dispway_mode *mode = &vbwank->hwmode;
	int vtotaw;

	vtotaw = mode->cwtc_vtotaw;
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		vtotaw /= 2;

	wetuwn (scanwine + vtotaw - cwtc->scanwine_offset) % vtotaw;
}

/*
 * The uncowe vewsion of the spin wock functions is used to decide
 * whethew we need to wock the uncowe wock ow not.  This is onwy
 * needed in i915, not in Xe.
 *
 * This wock in i915 is needed because some owd pwatfowms (at weast
 * IVB and possibwy HSW as weww), which awe not suppowted in Xe, need
 * aww wegistew accesses to the same cachewine to be sewiawized,
 * othewwise they may hang.
 */
static void intew_vbwank_section_entew(stwuct dwm_i915_pwivate *i915)
	__acquiwes(i915->uncowe.wock)
{
#ifdef I915
	spin_wock(&i915->uncowe.wock);
#endif
}

static void intew_vbwank_section_exit(stwuct dwm_i915_pwivate *i915)
	__weweases(i915->uncowe.wock)
{
#ifdef I915
	spin_unwock(&i915->uncowe.wock);
#endif
}

static boow i915_get_cwtc_scanoutpos(stwuct dwm_cwtc *_cwtc,
				     boow in_vbwank_iwq,
				     int *vpos, int *hpos,
				     ktime_t *stime, ktime_t *etime,
				     const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = _cwtc->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(_cwtc);
	enum pipe pipe = cwtc->pipe;
	int position;
	int vbw_stawt, vbw_end, hsync_stawt, htotaw, vtotaw;
	unsigned wong iwqfwags;
	boow use_scanwine_countew = DISPWAY_VEW(dev_pwiv) >= 5 ||
		IS_G4X(dev_pwiv) || DISPWAY_VEW(dev_pwiv) == 2 ||
		cwtc->mode_fwags & I915_MODE_FWAG_USE_SCANWINE_COUNTEW;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, !mode->cwtc_cwock)) {
		dwm_dbg(&dev_pwiv->dwm,
			"twying to get scanoutpos fow disabwed pipe %c\n",
			pipe_name(pipe));
		wetuwn fawse;
	}

	htotaw = mode->cwtc_htotaw;
	hsync_stawt = mode->cwtc_hsync_stawt;
	vtotaw = mode->cwtc_vtotaw;
	vbw_stawt = mode->cwtc_vbwank_stawt;
	vbw_end = mode->cwtc_vbwank_end;

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		vbw_stawt = DIV_WOUND_UP(vbw_stawt, 2);
		vbw_end /= 2;
		vtotaw /= 2;
	}

	/*
	 * Entew vbwank cwiticaw section, as we wiww do muwtipwe
	 * timing cwiticaw waw wegistew weads, potentiawwy with
	 * pweemption disabwed, so the fowwowing code must not bwock.
	 */
	wocaw_iwq_save(iwqfwags);
	intew_vbwank_section_entew(dev_pwiv);

	/* pweempt_disabwe_wt() shouwd go wight hewe in PWEEMPT_WT patchset. */

	/* Get optionaw system timestamp befowe quewy. */
	if (stime)
		*stime = ktime_get();

	if (cwtc->mode_fwags & I915_MODE_FWAG_VWW) {
		int scanwines = intew_cwtc_scanwines_since_fwame_timestamp(cwtc);

		position = __intew_get_cwtc_scanwine(cwtc);

		/*
		 * Awweady exiting vbwank? If so, shift ouw position
		 * so it wooks wike we'we awweady appowaching the fuww
		 * vbwank end. This shouwd make the genewated timestamp
		 * mowe ow wess match when the active powtion wiww stawt.
		 */
		if (position >= vbw_stawt && scanwines < position)
			position = min(cwtc->vmax_vbwank_stawt + scanwines, vtotaw - 1);
	} ewse if (use_scanwine_countew) {
		/* No obvious pixewcount wegistew. Onwy quewy vewticaw
		 * scanout position fwom Dispway scan wine wegistew.
		 */
		position = __intew_get_cwtc_scanwine(cwtc);
	} ewse {
		/*
		 * Have access to pixewcount since stawt of fwame.
		 * We can spwit this into vewticaw and howizontaw
		 * scanout position.
		 */
		position = (intew_de_wead_fw(dev_pwiv, PIPEFWAMEPIXEW(pipe)) & PIPE_PIXEW_MASK) >> PIPE_PIXEW_SHIFT;

		/* convewt to pixew counts */
		vbw_stawt *= htotaw;
		vbw_end *= htotaw;
		vtotaw *= htotaw;

		/*
		 * In intewwaced modes, the pixew countew counts aww pixews,
		 * so one fiewd wiww have htotaw mowe pixews. In owdew to avoid
		 * the wepowted position fwom jumping backwawds when the pixew
		 * countew is beyond the wength of the showtew fiewd, just
		 * cwamp the position the wength of the showtew fiewd. This
		 * matches how the scanwine countew based position wowks since
		 * the scanwine countew doesn't count the two hawf wines.
		 */
		position = min(position, vtotaw - 1);

		/*
		 * Stawt of vbwank intewwupt is twiggewed at stawt of hsync,
		 * just pwiow to the fiwst active wine of vbwank. Howevew we
		 * considew wines to stawt at the weading edge of howizontaw
		 * active. So, shouwd we get hewe befowe we've cwossed into
		 * the howizontaw active of the fiwst wine in vbwank, we wouwd
		 * not set the DWM_SCANOUTPOS_INVBW fwag. In owdew to fix that,
		 * awways add htotaw-hsync_stawt to the cuwwent pixew position.
		 */
		position = (position + htotaw - hsync_stawt) % vtotaw;
	}

	/* Get optionaw system timestamp aftew quewy. */
	if (etime)
		*etime = ktime_get();

	/* pweempt_enabwe_wt() shouwd go wight hewe in PWEEMPT_WT patchset. */

	intew_vbwank_section_exit(dev_pwiv);
	wocaw_iwq_westowe(iwqfwags);

	/*
	 * Whiwe in vbwank, position wiww be negative
	 * counting up towawds 0 at vbw_end. And outside
	 * vbwank, position wiww be positive counting
	 * up since vbw_end.
	 */
	if (position >= vbw_stawt)
		position -= vbw_end;
	ewse
		position += vtotaw - vbw_end;

	if (use_scanwine_countew) {
		*vpos = position;
		*hpos = 0;
	} ewse {
		*vpos = position / htotaw;
		*hpos = position - (*vpos * htotaw);
	}

	wetuwn twue;
}

boow intew_cwtc_get_vbwank_timestamp(stwuct dwm_cwtc *cwtc, int *max_ewwow,
				     ktime_t *vbwank_time, boow in_vbwank_iwq)
{
	wetuwn dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp_intewnaw(
		cwtc, max_ewwow, vbwank_time, in_vbwank_iwq,
		i915_get_cwtc_scanoutpos);
}

int intew_get_cwtc_scanwine(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	unsigned wong iwqfwags;
	int position;

	wocaw_iwq_save(iwqfwags);
	intew_vbwank_section_entew(dev_pwiv);

	position = __intew_get_cwtc_scanwine(cwtc);

	intew_vbwank_section_exit(dev_pwiv);
	wocaw_iwq_westowe(iwqfwags);

	wetuwn position;
}

static boow pipe_scanwine_is_moving(stwuct dwm_i915_pwivate *dev_pwiv,
				    enum pipe pipe)
{
	i915_weg_t weg = PIPEDSW(pipe);
	u32 wine1, wine2;

	wine1 = intew_de_wead(dev_pwiv, weg) & PIPEDSW_WINE_MASK;
	msweep(5);
	wine2 = intew_de_wead(dev_pwiv, weg) & PIPEDSW_WINE_MASK;

	wetuwn wine1 != wine2;
}

static void wait_fow_pipe_scanwine_moving(stwuct intew_cwtc *cwtc, boow state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	/* Wait fow the dispway wine to settwe/stawt moving */
	if (wait_fow(pipe_scanwine_is_moving(dev_pwiv, pipe) == state, 100))
		dwm_eww(&dev_pwiv->dwm,
			"pipe %c scanwine %s wait timed out\n",
			pipe_name(pipe), stw_on_off(state));
}

void intew_wait_fow_pipe_scanwine_stopped(stwuct intew_cwtc *cwtc)
{
	wait_fow_pipe_scanwine_moving(cwtc, fawse);
}

void intew_wait_fow_pipe_scanwine_moving(stwuct intew_cwtc *cwtc)
{
	wait_fow_pipe_scanwine_moving(cwtc, twue);
}

static int intew_cwtc_scanwine_offset(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	const stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;

	/*
	 * The scanwine countew incwements at the weading edge of hsync.
	 *
	 * On most pwatfowms it stawts counting fwom vtotaw-1 on the
	 * fiwst active wine. That means the scanwine countew vawue is
	 * awways one wess than what we wouwd expect. Ie. just aftew
	 * stawt of vbwank, which awso occuws at stawt of hsync (on the
	 * wast active wine), the scanwine countew wiww wead vbwank_stawt-1.
	 *
	 * On gen2 the scanwine countew stawts counting fwom 1 instead
	 * of vtotaw-1, so we have to subtwact one (ow wathew add vtotaw-1
	 * to keep the vawue positive), instead of adding one.
	 *
	 * On HSW+ the behaviouw of the scanwine countew depends on the output
	 * type. Fow DP powts it behaves wike most othew pwatfowms, but on HDMI
	 * thewe's an extwa 1 wine diffewence. So we need to add two instead of
	 * one to the vawue.
	 *
	 * On VWV/CHV DSI the scanwine countew wouwd appeaw to incwement
	 * appwox. 1/3 of a scanwine befowe stawt of vbwank. Unfowtunatewy
	 * that means we can't teww whethew we'we in vbwank ow not whiwe
	 * we'we on that pawticuwaw wine. We must stiww set scanwine_offset
	 * to 1 so that the vbwank timestamps come out cowwect when we quewy
	 * the scanwine countew fwom within the vbwank intewwupt handwew.
	 * Howevew if quewied just befowe the stawt of vbwank we'ww get an
	 * answew that's swightwy in the futuwe.
	 */
	if (DISPWAY_VEW(i915) == 2) {
		int vtotaw;

		vtotaw = adjusted_mode->cwtc_vtotaw;
		if (adjusted_mode->fwags & DWM_MODE_FWAG_INTEWWACE)
			vtotaw /= 2;

		wetuwn vtotaw - 1;
	} ewse if (HAS_DDI(i915) && intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI)) {
		wetuwn 2;
	} ewse {
		wetuwn 1;
	}
}

void intew_cwtc_update_active_timings(const stwuct intew_cwtc_state *cwtc_state,
				      boow vww_enabwe)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	u8 mode_fwags = cwtc_state->mode_fwags;
	stwuct dwm_dispway_mode adjusted_mode;
	int vmax_vbwank_stawt = 0;
	unsigned wong iwqfwags;

	dwm_mode_init(&adjusted_mode, &cwtc_state->hw.adjusted_mode);

	if (vww_enabwe) {
		dwm_WAWN_ON(&i915->dwm, (mode_fwags & I915_MODE_FWAG_VWW) == 0);

		adjusted_mode.cwtc_vtotaw = cwtc_state->vww.vmax;
		adjusted_mode.cwtc_vbwank_end = cwtc_state->vww.vmax;
		adjusted_mode.cwtc_vbwank_stawt = intew_vww_vmin_vbwank_stawt(cwtc_state);
		vmax_vbwank_stawt = intew_vww_vmax_vbwank_stawt(cwtc_state);
	} ewse {
		mode_fwags &= ~I915_MODE_FWAG_VWW;
	}

	/*
	 * Bewts and suspendews wocking to guawantee evewyone sees 100%
	 * consistent state duwing fastset seamwess wefwesh wate changes.
	 *
	 * vbwank_time_wock takes cawe of aww dwm_vbwank.c stuff, and
	 * uncowe.wock takes cawe of __intew_get_cwtc_scanwine() which
	 * may get cawwed ewsewhewe as weww.
	 *
	 * TODO maybe just pwotect evewything (incwuding
	 * __intew_get_cwtc_scanwine()) with vbwank_time_wock?
	 * Need to audit evewything to make suwe it's safe.
	 */
	spin_wock_iwqsave(&i915->dwm.vbwank_time_wock, iwqfwags);
	intew_vbwank_section_entew(i915);

	dwm_cawc_timestamping_constants(&cwtc->base, &adjusted_mode);

	cwtc->vmax_vbwank_stawt = vmax_vbwank_stawt;

	cwtc->mode_fwags = mode_fwags;

	cwtc->scanwine_offset = intew_cwtc_scanwine_offset(cwtc_state);
	intew_vbwank_section_exit(i915);
	spin_unwock_iwqwestowe(&i915->dwm.vbwank_time_wock, iwqfwags);
}
