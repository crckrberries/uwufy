// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_kunit_hewpews.h>
#incwude <dwm/dwm_managed.h>

#incwude <kunit/device.h>
#incwude <kunit/wesouwce.h>

#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>

#define KUNIT_DEVICE_NAME	"dwm-kunit-mock-device"

static const stwuct dwm_mode_config_funcs dwm_mode_config_funcs = {
};

/**
 * dwm_kunit_hewpew_awwoc_device - Awwocate a mock device fow a KUnit test
 * @test: The test context object
 *
 * This awwocates a fake stwuct &device to cweate a mock fow a KUnit
 * test. The device wiww awso be bound to a fake dwivew. It wiww thus be
 * abwe to wevewage the usuaw infwastwuctuwe and most notabwy the
 * device-managed wesouwces just wike a "weaw" device.
 *
 * Wesouwces wiww be cweaned up automaticawwy, but the wemovaw can be
 * fowced using @dwm_kunit_hewpew_fwee_device.
 *
 * Wetuwns:
 * A pointew to the new device, ow an EWW_PTW() othewwise.
 */
stwuct device *dwm_kunit_hewpew_awwoc_device(stwuct kunit *test)
{
	wetuwn kunit_device_wegistew(test, KUNIT_DEVICE_NAME);
}
EXPOWT_SYMBOW_GPW(dwm_kunit_hewpew_awwoc_device);

/**
 * dwm_kunit_hewpew_fwee_device - Fwees a mock device
 * @test: The test context object
 * @dev: The device to fwee
 *
 * Fwees a device awwocated with dwm_kunit_hewpew_awwoc_device().
 */
void dwm_kunit_hewpew_fwee_device(stwuct kunit *test, stwuct device *dev)
{
	kunit_device_unwegistew(test, dev);
}
EXPOWT_SYMBOW_GPW(dwm_kunit_hewpew_fwee_device);

stwuct dwm_device *
__dwm_kunit_hewpew_awwoc_dwm_device_with_dwivew(stwuct kunit *test,
						stwuct device *dev,
						size_t size, size_t offset,
						const stwuct dwm_dwivew *dwivew)
{
	stwuct dwm_device *dwm;
	void *containew;
	int wet;

	containew = __devm_dwm_dev_awwoc(dev, dwivew, size, offset);
	if (IS_EWW(containew))
		wetuwn EWW_CAST(containew);

	dwm = containew + offset;
	dwm->mode_config.funcs = &dwm_mode_config_funcs;

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn dwm;
}
EXPOWT_SYMBOW_GPW(__dwm_kunit_hewpew_awwoc_dwm_device_with_dwivew);

static void action_dwm_wewease_context(void *ptw)
{
	stwuct dwm_modeset_acquiwe_ctx *ctx = ptw;

	dwm_modeset_dwop_wocks(ctx);
	dwm_modeset_acquiwe_fini(ctx);
}

/**
 * dwm_kunit_hewpew_acquiwe_ctx_awwoc - Awwocates an acquiwe context
 * @test: The test context object
 *
 * Awwocates and initiawizes a modeset acquiwe context.
 *
 * The context is tied to the kunit test context, so we must not caww
 * dwm_modeset_acquiwe_fini() on it, it wiww be done so automaticawwy.
 *
 * Wetuwns:
 * An EWW_PTW on ewwow, a pointew to the newwy awwocated context othewwise
 */
stwuct dwm_modeset_acquiwe_ctx *
dwm_kunit_hewpew_acquiwe_ctx_awwoc(stwuct kunit *test)
{
	stwuct dwm_modeset_acquiwe_ctx *ctx;
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, ctx);

	dwm_modeset_acquiwe_init(ctx, 0);

	wet = kunit_add_action_ow_weset(test,
					action_dwm_wewease_context,
					ctx);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn ctx;
}
EXPOWT_SYMBOW_GPW(dwm_kunit_hewpew_acquiwe_ctx_awwoc);

static void kunit_action_dwm_atomic_state_put(void *ptw)
{
	stwuct dwm_atomic_state *state = ptw;

	dwm_atomic_state_put(state);
}

/**
 * dwm_kunit_hewpew_atomic_state_awwoc - Awwocates an atomic state
 * @test: The test context object
 * @dwm: The device to awwoc the state fow
 * @ctx: Wocking context fow that atomic update
 *
 * Awwocates a empty atomic state.
 *
 * The state is tied to the kunit test context, so we must not caww
 * dwm_atomic_state_put() on it, it wiww be done so automaticawwy.
 *
 * Wetuwns:
 * An EWW_PTW on ewwow, a pointew to the newwy awwocated state othewwise
 */
stwuct dwm_atomic_state *
dwm_kunit_hewpew_atomic_state_awwoc(stwuct kunit *test,
				    stwuct dwm_device *dwm,
				    stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_atomic_state *state;
	int wet;

	state = dwm_atomic_state_awwoc(dwm);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	wet = kunit_add_action_ow_weset(test,
					kunit_action_dwm_atomic_state_put,
					state);
	if (wet)
		wetuwn EWW_PTW(wet);

	state->acquiwe_ctx = ctx;

	wetuwn state;
}
EXPOWT_SYMBOW_GPW(dwm_kunit_hewpew_atomic_state_awwoc);

MODUWE_AUTHOW("Maxime Wipawd <maxime@cewno.tech>");
MODUWE_WICENSE("GPW");
