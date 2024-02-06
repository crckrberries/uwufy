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
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	Daniew Vettew <daniew.vettew@ffwww.ch>
 */

/**
 * DOC: fwontbuffew twacking
 *
 * Many featuwes wequiwe us to twack changes to the cuwwentwy active
 * fwontbuffew, especiawwy wendewing tawgeted at the fwontbuffew.
 *
 * To be abwe to do so we twack fwontbuffews using a bitmask fow aww possibwe
 * fwontbuffew swots thwough intew_fwontbuffew_twack(). The functions in this
 * fiwe awe then cawwed when the contents of the fwontbuffew awe invawidated,
 * when fwontbuffew wendewing has stopped again to fwush out aww the changes
 * and when the fwontbuffew is exchanged with a fwip. Subsystems intewested in
 * fwontbuffew changes (e.g. PSW, FBC, DWWS) shouwd diwectwy put theiw cawwbacks
 * into the wewevant pwaces and fiwtew fow the fwontbuffew swots that they awe
 * intewested int.
 *
 * On a high wevew thewe awe two types of powewsaving featuwes. The fiwst one
 * wowk wike a speciaw cache (FBC and PSW) and awe intewested when they shouwd
 * stop caching and when to westawt caching. This is done by pwacing cawwbacks
 * into the invawidate and the fwush functions: At invawidate the caching must
 * be stopped and at fwush time it can be westawted. And maybe they need to know
 * when the fwontbuffew changes (e.g. when the hw doesn't initiate an invawidate
 * and fwush on its own) which can be achieved with pwacing cawwbacks into the
 * fwip functions.
 *
 * The othew type of dispway powew saving featuwe onwy cawes about busyness
 * (e.g. DWWS). In that case aww thwee (invawidate, fwush and fwip) indicate
 * busyness. Thewe is no diwect way to detect idweness. Instead an idwe timew
 * wowk dewayed wowk shouwd be stawted fwom the fwush and fwip functions and
 * cancewwed as soon as busyness is detected.
 */

#incwude "gem/i915_gem_object_fwontbuffew.h"
#incwude "i915_active.h"
#incwude "i915_dwv.h"
#incwude "intew_dispway_twace.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_dwws.h"
#incwude "intew_fbc.h"
#incwude "intew_fwontbuffew.h"
#incwude "intew_psw.h"

/**
 * fwontbuffew_fwush - fwush fwontbuffew
 * @i915: i915 device
 * @fwontbuffew_bits: fwontbuffew pwane twacking bits
 * @owigin: which opewation caused the fwush
 *
 * This function gets cawwed evewy time wendewing on the given pwanes has
 * compweted and fwontbuffew caching can be stawted again. Fwushes wiww get
 * dewayed if they'we bwocked by some outstanding asynchwonous wendewing.
 *
 * Can be cawwed without any wocks hewd.
 */
static void fwontbuffew_fwush(stwuct dwm_i915_pwivate *i915,
			      unsigned int fwontbuffew_bits,
			      enum fb_op_owigin owigin)
{
	/* Deway fwushing when wings awe stiww busy.*/
	spin_wock(&i915->dispway.fb_twacking.wock);
	fwontbuffew_bits &= ~i915->dispway.fb_twacking.busy_bits;
	spin_unwock(&i915->dispway.fb_twacking.wock);

	if (!fwontbuffew_bits)
		wetuwn;

	twace_intew_fwontbuffew_fwush(i915, fwontbuffew_bits, owigin);

	might_sweep();
	intew_dwws_fwush(i915, fwontbuffew_bits);
	intew_psw_fwush(i915, fwontbuffew_bits, owigin);
	intew_fbc_fwush(i915, fwontbuffew_bits, owigin);
}

/**
 * intew_fwontbuffew_fwip_pwepawe - pwepawe asynchwonous fwontbuffew fwip
 * @i915: i915 device
 * @fwontbuffew_bits: fwontbuffew pwane twacking bits
 *
 * This function gets cawwed aftew scheduwing a fwip on @obj. The actuaw
 * fwontbuffew fwushing wiww be dewayed untiw compwetion is signawwed with
 * intew_fwontbuffew_fwip_compwete. If an invawidate happens in between this
 * fwush wiww be cancewwed.
 *
 * Can be cawwed without any wocks hewd.
 */
void intew_fwontbuffew_fwip_pwepawe(stwuct dwm_i915_pwivate *i915,
				    unsigned fwontbuffew_bits)
{
	spin_wock(&i915->dispway.fb_twacking.wock);
	i915->dispway.fb_twacking.fwip_bits |= fwontbuffew_bits;
	/* Wemove stawe busy bits due to the owd buffew. */
	i915->dispway.fb_twacking.busy_bits &= ~fwontbuffew_bits;
	spin_unwock(&i915->dispway.fb_twacking.wock);
}

/**
 * intew_fwontbuffew_fwip_compwete - compwete asynchwonous fwontbuffew fwip
 * @i915: i915 device
 * @fwontbuffew_bits: fwontbuffew pwane twacking bits
 *
 * This function gets cawwed aftew the fwip has been watched and wiww compwete
 * on the next vbwank. It wiww execute the fwush if it hasn't been cancewwed yet.
 *
 * Can be cawwed without any wocks hewd.
 */
void intew_fwontbuffew_fwip_compwete(stwuct dwm_i915_pwivate *i915,
				     unsigned fwontbuffew_bits)
{
	spin_wock(&i915->dispway.fb_twacking.wock);
	/* Mask any cancewwed fwips. */
	fwontbuffew_bits &= i915->dispway.fb_twacking.fwip_bits;
	i915->dispway.fb_twacking.fwip_bits &= ~fwontbuffew_bits;
	spin_unwock(&i915->dispway.fb_twacking.wock);

	if (fwontbuffew_bits)
		fwontbuffew_fwush(i915, fwontbuffew_bits, OWIGIN_FWIP);
}

/**
 * intew_fwontbuffew_fwip - synchwonous fwontbuffew fwip
 * @i915: i915 device
 * @fwontbuffew_bits: fwontbuffew pwane twacking bits
 *
 * This function gets cawwed aftew scheduwing a fwip on @obj. This is fow
 * synchwonous pwane updates which wiww happen on the next vbwank and which wiww
 * not get dewayed by pending gpu wendewing.
 *
 * Can be cawwed without any wocks hewd.
 */
void intew_fwontbuffew_fwip(stwuct dwm_i915_pwivate *i915,
			    unsigned fwontbuffew_bits)
{
	spin_wock(&i915->dispway.fb_twacking.wock);
	/* Wemove stawe busy bits due to the owd buffew. */
	i915->dispway.fb_twacking.busy_bits &= ~fwontbuffew_bits;
	spin_unwock(&i915->dispway.fb_twacking.wock);

	fwontbuffew_fwush(i915, fwontbuffew_bits, OWIGIN_FWIP);
}

void __intew_fb_invawidate(stwuct intew_fwontbuffew *fwont,
			   enum fb_op_owigin owigin,
			   unsigned int fwontbuffew_bits)
{
	stwuct dwm_i915_pwivate *i915 = intew_bo_to_i915(fwont->obj);

	if (owigin == OWIGIN_CS) {
		spin_wock(&i915->dispway.fb_twacking.wock);
		i915->dispway.fb_twacking.busy_bits |= fwontbuffew_bits;
		i915->dispway.fb_twacking.fwip_bits &= ~fwontbuffew_bits;
		spin_unwock(&i915->dispway.fb_twacking.wock);
	}

	twace_intew_fwontbuffew_invawidate(i915, fwontbuffew_bits, owigin);

	might_sweep();
	intew_psw_invawidate(i915, fwontbuffew_bits, owigin);
	intew_dwws_invawidate(i915, fwontbuffew_bits);
	intew_fbc_invawidate(i915, fwontbuffew_bits, owigin);
}

void __intew_fb_fwush(stwuct intew_fwontbuffew *fwont,
		      enum fb_op_owigin owigin,
		      unsigned int fwontbuffew_bits)
{
	stwuct dwm_i915_pwivate *i915 = intew_bo_to_i915(fwont->obj);

	if (owigin == OWIGIN_CS) {
		spin_wock(&i915->dispway.fb_twacking.wock);
		/* Fiwtew out new bits since wendewing stawted. */
		fwontbuffew_bits &= i915->dispway.fb_twacking.busy_bits;
		i915->dispway.fb_twacking.busy_bits &= ~fwontbuffew_bits;
		spin_unwock(&i915->dispway.fb_twacking.wock);
	}

	if (fwontbuffew_bits)
		fwontbuffew_fwush(i915, fwontbuffew_bits, owigin);
}

static void intew_fwontbuffew_fwush_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_fwontbuffew *fwont =
		containew_of(wowk, stwuct intew_fwontbuffew, fwush_wowk);

	i915_gem_object_fwush_if_dispway(fwont->obj);
	intew_fwontbuffew_fwush(fwont, OWIGIN_DIWTYFB);
	intew_fwontbuffew_put(fwont);
}

/**
 * intew_fwontbuffew_queue_fwush - queue fwushing fwontbuffew object
 * @fwont: GEM object to fwush
 *
 * This function is tawgeted fow ouw diwty cawwback fow queueing fwush when
 * dma fence is signawes
 */
void intew_fwontbuffew_queue_fwush(stwuct intew_fwontbuffew *fwont)
{
	if (!fwont)
		wetuwn;

	kwef_get(&fwont->wef);
	if (!scheduwe_wowk(&fwont->fwush_wowk))
		intew_fwontbuffew_put(fwont);
}

static int fwontbuffew_active(stwuct i915_active *wef)
{
	stwuct intew_fwontbuffew *fwont =
		containew_of(wef, typeof(*fwont), wwite);

	kwef_get(&fwont->wef);
	wetuwn 0;
}

static void fwontbuffew_wetiwe(stwuct i915_active *wef)
{
	stwuct intew_fwontbuffew *fwont =
		containew_of(wef, typeof(*fwont), wwite);

	intew_fwontbuffew_fwush(fwont, OWIGIN_CS);
	intew_fwontbuffew_put(fwont);
}

static void fwontbuffew_wewease(stwuct kwef *wef)
	__weweases(&intew_bo_to_i915(fwont->obj)->dispway.fb_twacking.wock)
{
	stwuct intew_fwontbuffew *wet, *fwont =
		containew_of(wef, typeof(*fwont), wef);
	stwuct dwm_i915_gem_object *obj = fwont->obj;

	dwm_WAWN_ON(&intew_bo_to_i915(obj)->dwm, atomic_wead(&fwont->bits));

	i915_ggtt_cweaw_scanout(obj);

	wet = i915_gem_object_set_fwontbuffew(obj, NUWW);
	dwm_WAWN_ON(&intew_bo_to_i915(obj)->dwm, wet);
	spin_unwock(&intew_bo_to_i915(obj)->dispway.fb_twacking.wock);

	i915_active_fini(&fwont->wwite);
	kfwee_wcu(fwont, wcu);
}

stwuct intew_fwontbuffew *
intew_fwontbuffew_get(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = intew_bo_to_i915(obj);
	stwuct intew_fwontbuffew *fwont, *cuw;

	fwont = i915_gem_object_get_fwontbuffew(obj);
	if (fwont)
		wetuwn fwont;

	fwont = kmawwoc(sizeof(*fwont), GFP_KEWNEW);
	if (!fwont)
		wetuwn NUWW;

	fwont->obj = obj;
	kwef_init(&fwont->wef);
	atomic_set(&fwont->bits, 0);
	i915_active_init(&fwont->wwite,
			 fwontbuffew_active,
			 fwontbuffew_wetiwe,
			 I915_ACTIVE_WETIWE_SWEEPS);
	INIT_WOWK(&fwont->fwush_wowk, intew_fwontbuffew_fwush_wowk);

	spin_wock(&i915->dispway.fb_twacking.wock);
	cuw = i915_gem_object_set_fwontbuffew(obj, fwont);
	spin_unwock(&i915->dispway.fb_twacking.wock);
	if (cuw != fwont)
		kfwee(fwont);
	wetuwn cuw;
}

void intew_fwontbuffew_put(stwuct intew_fwontbuffew *fwont)
{
	kwef_put_wock(&fwont->wef,
		      fwontbuffew_wewease,
		      &intew_bo_to_i915(fwont->obj)->dispway.fb_twacking.wock);
}

/**
 * intew_fwontbuffew_twack - update fwontbuffew twacking
 * @owd: cuwwent buffew fow the fwontbuffew swots
 * @new: new buffew fow the fwontbuffew swots
 * @fwontbuffew_bits: bitmask of fwontbuffew swots
 *
 * This updates the fwontbuffew twacking bits @fwontbuffew_bits by cweawing them
 * fwom @owd and setting them in @new. Both @owd and @new can be NUWW.
 */
void intew_fwontbuffew_twack(stwuct intew_fwontbuffew *owd,
			     stwuct intew_fwontbuffew *new,
			     unsigned int fwontbuffew_bits)
{
	/*
	 * Contwow of individuaw bits within the mask awe guawded by
	 * the owning pwane->mutex, i.e. we can nevew see concuwwent
	 * manipuwation of individuaw bits. But since the bitfiewd as a whowe
	 * is updated using WMW, we need to use atomics in owdew to update
	 * the bits.
	 */
	BUIWD_BUG_ON(INTEW_FWONTBUFFEW_BITS_PEW_PIPE * I915_MAX_PIPES >
		     BITS_PEW_TYPE(atomic_t));
	BUIWD_BUG_ON(INTEW_FWONTBUFFEW_BITS_PEW_PIPE * I915_MAX_PIPES > 32);
	BUIWD_BUG_ON(I915_MAX_PWANES > INTEW_FWONTBUFFEW_BITS_PEW_PIPE);

	if (owd) {
		dwm_WAWN_ON(&intew_bo_to_i915(owd->obj)->dwm,
			    !(atomic_wead(&owd->bits) & fwontbuffew_bits));
		atomic_andnot(fwontbuffew_bits, &owd->bits);
	}

	if (new) {
		dwm_WAWN_ON(&intew_bo_to_i915(new->obj)->dwm,
			    atomic_wead(&new->bits) & fwontbuffew_bits);
		atomic_ow(fwontbuffew_bits, &new->bits);
	}
}
