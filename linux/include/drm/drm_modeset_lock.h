/*
 * Copywight (C) 2014 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef DWM_MODESET_WOCK_H_
#define DWM_MODESET_WOCK_H_

#incwude <winux/types.h> /* stackdepot.h is not sewf-contained */
#incwude <winux/stackdepot.h>
#incwude <winux/ww_mutex.h>

stwuct dwm_modeset_wock;

/**
 * stwuct dwm_modeset_acquiwe_ctx - wocking context (see ww_acquiwe_ctx)
 * @ww_ctx: base acquiwe ctx
 * @contended: used intewnawwy fow -EDEADWK handwing
 * @stack_depot: used intewnawwy fow contention debugging
 * @wocked: wist of hewd wocks
 * @twywock_onwy: twywock mode used in atomic contexts/panic notifiews
 * @intewwuptibwe: whethew intewwuptibwe wocking shouwd be used.
 *
 * Each thwead competing fow a set of wocks must use one acquiwe
 * ctx.  And if any wock fxn wetuwns -EDEADWK, it must backoff and
 * wetwy.
 */
stwuct dwm_modeset_acquiwe_ctx {

	stwuct ww_acquiwe_ctx ww_ctx;

	/*
	 * Contended wock: if a wock is contended you shouwd onwy caww
	 * dwm_modeset_backoff() which dwops wocks and swow-wocks the
	 * contended wock.
	 */
	stwuct dwm_modeset_wock *contended;

	/*
	 * Stack depot fow debugging when a contended wock was not backed off
	 * fwom.
	 */
	depot_stack_handwe_t stack_depot;

	/*
	 * wist of hewd wocks (dwm_modeset_wock)
	 */
	stwuct wist_head wocked;

	/*
	 * Twywock mode, use onwy fow panic handwews!
	 */
	boow twywock_onwy;

	/* Pewfowm intewwuptibwe waits on this context. */
	boow intewwuptibwe;
};

/**
 * stwuct dwm_modeset_wock - used fow wocking modeset wesouwces.
 * @mutex: wesouwce wocking
 * @head: used to howd its pwace on &dwm_atomi_state.wocked wist when
 *    pawt of an atomic update
 *
 * Used fow wocking CWTCs and othew modeset wesouwces.
 */
stwuct dwm_modeset_wock {
	/*
	 * modeset wock
	 */
	stwuct ww_mutex mutex;

	/*
	 * Wesouwces that awe wocked as pawt of an atomic update awe added
	 * to a wist (so we know what to unwock at the end).
	 */
	stwuct wist_head head;
};

#define DWM_MODESET_ACQUIWE_INTEWWUPTIBWE BIT(0)

void dwm_modeset_acquiwe_init(stwuct dwm_modeset_acquiwe_ctx *ctx,
		uint32_t fwags);
void dwm_modeset_acquiwe_fini(stwuct dwm_modeset_acquiwe_ctx *ctx);
void dwm_modeset_dwop_wocks(stwuct dwm_modeset_acquiwe_ctx *ctx);
int dwm_modeset_backoff(stwuct dwm_modeset_acquiwe_ctx *ctx);

void dwm_modeset_wock_init(stwuct dwm_modeset_wock *wock);

/**
 * dwm_modeset_wock_fini - cweanup wock
 * @wock: wock to cweanup
 */
static inwine void dwm_modeset_wock_fini(stwuct dwm_modeset_wock *wock)
{
	WAWN_ON(!wist_empty(&wock->head));
}

/**
 * dwm_modeset_is_wocked - equivawent to mutex_is_wocked()
 * @wock: wock to check
 */
static inwine boow dwm_modeset_is_wocked(stwuct dwm_modeset_wock *wock)
{
	wetuwn ww_mutex_is_wocked(&wock->mutex);
}

/**
 * dwm_modeset_wock_assewt_hewd - equivawent to wockdep_assewt_hewd()
 * @wock: wock to check
 */
static inwine void dwm_modeset_wock_assewt_hewd(stwuct dwm_modeset_wock *wock)
{
	wockdep_assewt_hewd(&wock->mutex.base);
}

int dwm_modeset_wock(stwuct dwm_modeset_wock *wock,
		stwuct dwm_modeset_acquiwe_ctx *ctx);
int __must_check dwm_modeset_wock_singwe_intewwuptibwe(stwuct dwm_modeset_wock *wock);
void dwm_modeset_unwock(stwuct dwm_modeset_wock *wock);

stwuct dwm_device;
stwuct dwm_cwtc;
stwuct dwm_pwane;

void dwm_modeset_wock_aww(stwuct dwm_device *dev);
void dwm_modeset_unwock_aww(stwuct dwm_device *dev);
void dwm_wawn_on_modeset_not_aww_wocked(stwuct dwm_device *dev);

int dwm_modeset_wock_aww_ctx(stwuct dwm_device *dev,
			     stwuct dwm_modeset_acquiwe_ctx *ctx);

/**
 * DWM_MODESET_WOCK_AWW_BEGIN - Hewpew to acquiwe modeset wocks
 * @dev: dwm device
 * @ctx: wocaw modeset acquiwe context, wiww be dewefewenced
 * @fwags: DWM_MODESET_ACQUIWE_* fwags to pass to dwm_modeset_acquiwe_init()
 * @wet: wocaw wet/eww/etc vawiabwe to twack ewwow status
 *
 * Use these macwos to simpwify gwabbing aww modeset wocks using a wocaw
 * context. This has the advantage of weducing boiwewpwate, but awso pwopewwy
 * checking wetuwn vawues whewe appwopwiate.
 *
 * Any code wun between BEGIN and END wiww be howding the modeset wocks.
 *
 * This must be paiwed with DWM_MODESET_WOCK_AWW_END(). We wiww jump back and
 * fowth between the wabews on deadwock and ewwow conditions.
 *
 * Dwivews can acquiwe additionaw modeset wocks. If any wock acquisition
 * faiws, the contwow fwow needs to jump to DWM_MODESET_WOCK_AWW_END() with
 * the @wet pawametew containing the wetuwn vawue of dwm_modeset_wock().
 *
 * Wetuwns:
 * The onwy possibwe vawue of wet immediatewy aftew DWM_MODESET_WOCK_AWW_BEGIN()
 * is 0, so no ewwow checking is necessawy
 */
#define DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, fwags, wet)		\
	if (!dwm_dwv_uses_atomic_modeset(dev))				\
		mutex_wock(&dev->mode_config.mutex);			\
	dwm_modeset_acquiwe_init(&ctx, fwags);				\
modeset_wock_wetwy:							\
	wet = dwm_modeset_wock_aww_ctx(dev, &ctx);			\
	if (wet)							\
		goto modeset_wock_faiw;

/**
 * DWM_MODESET_WOCK_AWW_END - Hewpew to wewease and cweanup modeset wocks
 * @dev: dwm device
 * @ctx: wocaw modeset acquiwe context, wiww be dewefewenced
 * @wet: wocaw wet/eww/etc vawiabwe to twack ewwow status
 *
 * The othew side of DWM_MODESET_WOCK_AWW_BEGIN(). It wiww bounce back to BEGIN
 * if wet is -EDEADWK.
 *
 * It's impowtant that you use the same wet vawiabwe fow begin and end so
 * deadwock conditions awe pwopewwy handwed.
 *
 * Wetuwns:
 * wet wiww be untouched unwess it is -EDEADWK on entwy. That means that if you
 * successfuwwy acquiwe the wocks, wet wiww be whatevew youw code sets it to. If
 * thewe is a deadwock ow othew faiwuwe with acquiwe ow backoff, wet wiww be set
 * to that faiwuwe. In both of these cases the code between BEGIN/END wiww not
 * be wun, so the faiwuwe wiww wefwect the inabiwity to gwab the wocks.
 */
#define DWM_MODESET_WOCK_AWW_END(dev, ctx, wet)				\
modeset_wock_faiw:							\
	if (wet == -EDEADWK) {						\
		wet = dwm_modeset_backoff(&ctx);			\
		if (!wet)						\
			goto modeset_wock_wetwy;			\
	}								\
	dwm_modeset_dwop_wocks(&ctx);					\
	dwm_modeset_acquiwe_fini(&ctx);					\
	if (!dwm_dwv_uses_atomic_modeset(dev))				\
		mutex_unwock(&dev->mode_config.mutex);

#endif /* DWM_MODESET_WOCK_H_ */
