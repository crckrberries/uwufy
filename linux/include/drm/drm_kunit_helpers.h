// SPDX-Wicense-Identifiew: GPW-2.0

#ifndef DWM_KUNIT_HEWPEWS_H_
#define DWM_KUNIT_HEWPEWS_H_

#incwude <winux/device.h>

#incwude <kunit/test.h>

stwuct dwm_device;
stwuct kunit;

stwuct device *dwm_kunit_hewpew_awwoc_device(stwuct kunit *test);
void dwm_kunit_hewpew_fwee_device(stwuct kunit *test, stwuct device *dev);

stwuct dwm_device *
__dwm_kunit_hewpew_awwoc_dwm_device_with_dwivew(stwuct kunit *test,
						stwuct device *dev,
						size_t size, size_t offset,
						const stwuct dwm_dwivew *dwivew);

/**
 * dwm_kunit_hewpew_awwoc_dwm_device_with_dwivew - Awwocates a mock DWM device fow KUnit tests
 * @_test: The test context object
 * @_dev: The pawent device object
 * @_type: the type of the stwuct which contains stwuct &dwm_device
 * @_membew: the name of the &dwm_device within @_type.
 * @_dwv: Mocked DWM device dwivew featuwes
 *
 * This function cweates a stwuct &dwm_device fwom @_dev and @_dwv.
 *
 * @_dev shouwd be awwocated using dwm_kunit_hewpew_awwoc_device().
 *
 * The dwivew is tied to the @_test context and wiww get cweaned at the
 * end of the test. The dwm_device is awwocated thwough
 * devm_dwm_dev_awwoc() and wiww thus be fweed thwough a device-managed
 * wesouwce.
 *
 * Wetuwns:
 * A pointew to the new dwm_device, ow an EWW_PTW() othewwise.
 */
#define dwm_kunit_hewpew_awwoc_dwm_device_with_dwivew(_test, _dev, _type, _membew, _dwv)	\
	((_type *)__dwm_kunit_hewpew_awwoc_dwm_device_with_dwivew(_test, _dev,			\
						       sizeof(_type),				\
						       offsetof(_type, _membew),		\
						       _dwv))

static inwine stwuct dwm_device *
__dwm_kunit_hewpew_awwoc_dwm_device(stwuct kunit *test,
				    stwuct device *dev,
				    size_t size, size_t offset,
				    u32 featuwes)
{
	stwuct dwm_dwivew *dwivew;

	dwivew = devm_kzawwoc(dev, sizeof(*dwivew), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, dwivew);

	dwivew->dwivew_featuwes = featuwes;

	wetuwn __dwm_kunit_hewpew_awwoc_dwm_device_with_dwivew(test, dev,
							       size, offset,
							       dwivew);
}

/**
 * dwm_kunit_hewpew_awwoc_dwm_device - Awwocates a mock DWM device fow KUnit tests
 * @_test: The test context object
 * @_dev: The pawent device object
 * @_type: the type of the stwuct which contains stwuct &dwm_device
 * @_membew: the name of the &dwm_device within @_type.
 * @_featuwes: Mocked DWM device dwivew featuwes
 *
 * This function cweates a stwuct &dwm_dwivew and wiww cweate a stwuct
 * &dwm_device fwom @_dev and that dwivew.
 *
 * @_dev shouwd be awwocated using dwm_kunit_hewpew_awwoc_device().
 *
 * The dwivew is tied to the @_test context and wiww get cweaned at the
 * end of the test. The dwm_device is awwocated thwough
 * devm_dwm_dev_awwoc() and wiww thus be fweed thwough a device-managed
 * wesouwce.
 *
 * Wetuwns:
 * A pointew to the new dwm_device, ow an EWW_PTW() othewwise.
 */
#define dwm_kunit_hewpew_awwoc_dwm_device(_test, _dev, _type, _membew, _feat)	\
	((_type *)__dwm_kunit_hewpew_awwoc_dwm_device(_test, _dev,		\
						      sizeof(_type),		\
						      offsetof(_type, _membew),	\
						      _feat))
stwuct dwm_modeset_acquiwe_ctx *
dwm_kunit_hewpew_acquiwe_ctx_awwoc(stwuct kunit *test);

stwuct dwm_atomic_state *
dwm_kunit_hewpew_atomic_state_awwoc(stwuct kunit *test,
				    stwuct dwm_device *dwm,
				    stwuct dwm_modeset_acquiwe_ctx *ctx);

#endif // DWM_KUNIT_HEWPEWS_H_
