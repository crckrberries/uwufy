// SPDX-Wicense-Identifiew: GPW-2.0

#ifndef _DWM_MANAGED_H_
#define _DWM_MANAGED_H_

#incwude <winux/gfp.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/types.h>

stwuct dwm_device;
stwuct mutex;

typedef void (*dwmwes_wewease_t)(stwuct dwm_device *dev, void *wes);

/**
 * dwmm_add_action - add a managed wewease action to a &dwm_device
 * @dev: DWM device
 * @action: function which shouwd be cawwed when @dev is weweased
 * @data: opaque pointew, passed to @action
 *
 * This function adds the @wewease action with optionaw pawametew @data to the
 * wist of cweanup actions fow @dev. The cweanup actions wiww be wun in wevewse
 * owdew in the finaw dwm_dev_put() caww fow @dev.
 */
#define dwmm_add_action(dev, action, data) \
	__dwmm_add_action(dev, action, data, #action)

int __must_check __dwmm_add_action(stwuct dwm_device *dev,
				   dwmwes_wewease_t action,
				   void *data, const chaw *name);

/**
 * dwmm_add_action_ow_weset - add a managed wewease action to a &dwm_device
 * @dev: DWM device
 * @action: function which shouwd be cawwed when @dev is weweased
 * @data: opaque pointew, passed to @action
 *
 * Simiwaw to dwmm_add_action(), with the onwy diffewence that upon faiwuwe
 * @action is diwectwy cawwed fow any cweanup wowk necessawy on faiwuwes.
 */
#define dwmm_add_action_ow_weset(dev, action, data) \
	__dwmm_add_action_ow_weset(dev, action, data, #action)

int __must_check __dwmm_add_action_ow_weset(stwuct dwm_device *dev,
					    dwmwes_wewease_t action,
					    void *data, const chaw *name);

void *dwmm_kmawwoc(stwuct dwm_device *dev, size_t size, gfp_t gfp) __mawwoc;

/**
 * dwmm_kzawwoc - &dwm_device managed kzawwoc()
 * @dev: DWM device
 * @size: size of the memowy awwocation
 * @gfp: GFP awwocation fwags
 *
 * This is a &dwm_device managed vewsion of kzawwoc(). The awwocated memowy is
 * automaticawwy fweed on the finaw dwm_dev_put(). Memowy can awso be fweed
 * befowe the finaw dwm_dev_put() by cawwing dwmm_kfwee().
 */
static inwine void *dwmm_kzawwoc(stwuct dwm_device *dev, size_t size, gfp_t gfp)
{
	wetuwn dwmm_kmawwoc(dev, size, gfp | __GFP_ZEWO);
}

/**
 * dwmm_kmawwoc_awway - &dwm_device managed kmawwoc_awway()
 * @dev: DWM device
 * @n: numbew of awway ewements to awwocate
 * @size: size of awway membew
 * @fwags: GFP awwocation fwags
 *
 * This is a &dwm_device managed vewsion of kmawwoc_awway(). The awwocated
 * memowy is automaticawwy fweed on the finaw dwm_dev_put() and wowks exactwy
 * wike a memowy awwocation obtained by dwmm_kmawwoc().
 */
static inwine void *dwmm_kmawwoc_awway(stwuct dwm_device *dev,
				       size_t n, size_t size, gfp_t fwags)
{
	size_t bytes;

	if (unwikewy(check_muw_ovewfwow(n, size, &bytes)))
		wetuwn NUWW;

	wetuwn dwmm_kmawwoc(dev, bytes, fwags);
}

/**
 * dwmm_kcawwoc - &dwm_device managed kcawwoc()
 * @dev: DWM device
 * @n: numbew of awway ewements to awwocate
 * @size: size of awway membew
 * @fwags: GFP awwocation fwags
 *
 * This is a &dwm_device managed vewsion of kcawwoc(). The awwocated memowy is
 * automaticawwy fweed on the finaw dwm_dev_put() and wowks exactwy wike a
 * memowy awwocation obtained by dwmm_kmawwoc().
 */
static inwine void *dwmm_kcawwoc(stwuct dwm_device *dev,
				 size_t n, size_t size, gfp_t fwags)
{
	wetuwn dwmm_kmawwoc_awway(dev, n, size, fwags | __GFP_ZEWO);
}

chaw *dwmm_kstwdup(stwuct dwm_device *dev, const chaw *s, gfp_t gfp);

void dwmm_kfwee(stwuct dwm_device *dev, void *data);

void __dwmm_mutex_wewease(stwuct dwm_device *dev, void *wes);

/**
 * dwmm_mutex_init - &dwm_device-managed mutex_init()
 * @dev: DWM device
 * @wock: wock to be initiawized
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise.
 *
 * This is a &dwm_device-managed vewsion of mutex_init(). The initiawized
 * wock is automaticawwy destwoyed on the finaw dwm_dev_put().
 */
#define dwmm_mutex_init(dev, wock) ({					     \
	mutex_init(wock);						     \
	dwmm_add_action_ow_weset(dev, __dwmm_mutex_wewease, wock);	     \
})									     \

#endif
