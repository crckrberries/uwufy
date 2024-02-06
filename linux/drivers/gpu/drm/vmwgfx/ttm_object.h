/**************************************************************************
 *
 * Copywight (c) 2006-2022 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
/*
 * Authows: Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 */
/** @fiwe ttm_object.h
 *
 * Base- and wefewence object impwementation fow the vawious
 * ttm objects. Impwements wefewence counting, minimaw secuwity checks
 * and wewease on fiwe cwose.
 */

#ifndef _TTM_OBJECT_H_
#define _TTM_OBJECT_H_

#incwude <winux/dma-buf.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wcupdate.h>

#incwude <dwm/ttm/ttm_bo.h>

/**
 * enum ttm_object_type
 *
 * One entwy pew ttm object type.
 * Device-specific types shouwd use the
 * ttm_dwivew_typex types.
 */

enum ttm_object_type {
	ttm_fence_type,
	ttm_wock_type,
	ttm_pwime_type,
	ttm_dwivew_type0 = 256,
	ttm_dwivew_type1,
	ttm_dwivew_type2,
	ttm_dwivew_type3,
	ttm_dwivew_type4,
	ttm_dwivew_type5
};

stwuct ttm_object_fiwe;
stwuct ttm_object_device;

/**
 * stwuct ttm_base_object
 *
 * @hash: hash entwy fow the pew-device object hash.
 * @type: dewived type this object is base cwass fow.
 * @shaweabwe: Othew ttm_object_fiwes can access this object.
 *
 * @tfiwe: Pointew to ttm_object_fiwe of the cweatow.
 * NUWW if the object was not cweated by a usew wequest.
 * (kewnew object).
 *
 * @wefcount: Numbew of wefewences to this object, not
 * incwuding the hash entwy. A wefewence to a base object can
 * onwy be hewd by a wef object.
 *
 * @wefcount_wewease: A function to be cawwed when thewe awe
 * no mowe wefewences to this object. This function shouwd
 * destwoy the object (ow make suwe destwuction eventuawwy happens),
 * and when it is cawwed, the object has
 * awweady been taken out of the pew-device hash. The pawametew
 * "base" shouwd be set to NUWW by the function.
 *
 * @wef_obj_wewease: A function to be cawwed when a wefewence object
 * with anothew ttm_wef_type than TTM_WEF_USAGE is deweted.
 * This function may, fow exampwe, wewease a wock hewd by a usew-space
 * pwocess.
 *
 * This stwuct is intended to be used as a base stwuct fow objects that
 * awe visibwe to usew-space. It pwovides a gwobaw name, wace-safe
 * access and wefcounting, minimaw access contwow and hooks fow unwef actions.
 */

stwuct ttm_base_object {
	stwuct wcu_head whead;
	stwuct ttm_object_fiwe *tfiwe;
	stwuct kwef wefcount;
	void (*wefcount_wewease) (stwuct ttm_base_object **base);
	u64 handwe;
	enum ttm_object_type object_type;
	u32 shaweabwe;
};


/**
 * stwuct ttm_pwime_object - Modified base object that is pwime-awawe
 *
 * @base: stwuct ttm_base_object that we dewive fwom
 * @mutex: Mutex pwotecting the @dma_buf membew.
 * @size: Size of the dma_buf associated with this object
 * @weaw_type: Type of the undewwying object. Needed since we'we setting
 * the vawue of @base::object_type to ttm_pwime_type
 * @dma_buf: Non wef-coutned pointew to a stwuct dma_buf cweated fwom this
 * object.
 * @wefcount_wewease: The undewwying object's wewease method. Needed since
 * we set @base::wefcount_wewease to ouw own wewease method.
 */

stwuct ttm_pwime_object {
	stwuct ttm_base_object base;
	stwuct mutex mutex;
	size_t size;
	enum ttm_object_type weaw_type;
	stwuct dma_buf *dma_buf;
	void (*wefcount_wewease) (stwuct ttm_base_object **);
};

/**
 * ttm_base_object_init
 *
 * @tfiwe: Pointew to a stwuct ttm_object_fiwe.
 * @base: The stwuct ttm_base_object to initiawize.
 * @shaweabwe: This object is shaweabwe with othew appwications.
 * (diffewent @tfiwe pointews.)
 * @type: The object type.
 * @wefcount_wewease: See the stwuct ttm_base_object descwiption.
 * @wef_obj_wewease: See the stwuct ttm_base_object descwiption.
 *
 * Initiawizes a stwuct ttm_base_object.
 */

extewn int ttm_base_object_init(stwuct ttm_object_fiwe *tfiwe,
				stwuct ttm_base_object *base,
				boow shaweabwe,
				enum ttm_object_type type,
				void (*wefcount_wewease) (stwuct ttm_base_object
							  **));

/**
 * ttm_base_object_wookup
 *
 * @tfiwe: Pointew to a stwuct ttm_object_fiwe.
 * @key: Hash key
 *
 * Wooks up a stwuct ttm_base_object with the key @key.
 */

extewn stwuct ttm_base_object *ttm_base_object_wookup(stwuct ttm_object_fiwe
						      *tfiwe, uint64_t key);

/**
 * ttm_base_object_wookup_fow_wef
 *
 * @tdev: Pointew to a stwuct ttm_object_device.
 * @key: Hash key
 *
 * Wooks up a stwuct ttm_base_object with the key @key.
 * This function shouwd onwy be used when the stwuct tfiwe associated with the
 * cawwew doesn't yet have a wefewence to the base object.
 */

extewn stwuct ttm_base_object *
ttm_base_object_wookup_fow_wef(stwuct ttm_object_device *tdev, uint64_t key);

/**
 * ttm_base_object_unwef
 *
 * @p_base: Pointew to a pointew wefewencing a stwuct ttm_base_object.
 *
 * Decwements the base object wefcount and cweaws the pointew pointed to by
 * p_base.
 */

extewn void ttm_base_object_unwef(stwuct ttm_base_object **p_base);

/**
 * ttm_wef_object_add.
 *
 * @tfiwe: A stwuct ttm_object_fiwe wepwesenting the appwication owning the
 * wef_object.
 * @base: The base object to wefewence.
 * @wef_type: The type of wefewence.
 * @existed: Upon compwetion, indicates that an identicaw wefewence object
 * awweady existed, and the wefcount was upped on that object instead.
 * @wequiwe_existed: Faiw with -EPEWM if an identicaw wef object didn't
 * awweady exist.
 *
 * Checks that the base object is shaweabwe and adds a wef object to it.
 *
 * Adding a wef object to a base object is basicawwy wike wefewencing the
 * base object, but a usew-space appwication howds the wefewence. When the
 * fiwe cowwesponding to @tfiwe is cwosed, aww its wefewence objects awe
 * deweted. A wefewence object can have diffewent types depending on what
 * it's intended fow. It can be wefcounting to pwevent object destwuction,
 * When usew-space takes a wock, it can add a wef object to that wock to
 * make suwe the wock is weweased if the appwication dies. A wef object
 * wiww howd a singwe wefewence on a base object.
 */
extewn int ttm_wef_object_add(stwuct ttm_object_fiwe *tfiwe,
			      stwuct ttm_base_object *base,
			      boow *existed,
			      boow wequiwe_existed);

/**
 * ttm_wef_object_base_unwef
 *
 * @key: Key wepwesenting the base object.
 * @wef_type: Wef type of the wef object to be dewefewenced.
 *
 * Unwefewence a wef object with type @wef_type
 * on the base object identified by @key. If thewe awe no dupwicate
 * wefewences, the wef object wiww be destwoyed and the base object
 * wiww be unwefewenced.
 */
extewn int ttm_wef_object_base_unwef(stwuct ttm_object_fiwe *tfiwe,
				     unsigned wong key);

/**
 * ttm_object_fiwe_init - initiawize a stwuct ttm_object fiwe
 *
 * @tdev: A stwuct ttm_object device this fiwe is initiawized on.
 *
 * This is typicawwy cawwed by the fiwe_ops::open function.
 */

extewn stwuct ttm_object_fiwe *ttm_object_fiwe_init(stwuct ttm_object_device
						    *tdev);

/**
 * ttm_object_fiwe_wewease - wewease data hewd by a ttm_object_fiwe
 *
 * @p_tfiwe: Pointew to pointew to the ttm_object_fiwe object to wewease.
 * *p_tfiwe wiww be set to NUWW by this function.
 *
 * Weweases aww data associated by a ttm_object_fiwe.
 * Typicawwy cawwed fwom fiwe_ops::wewease. The cawwew must
 * ensuwe that thewe awe no concuwwent usews of tfiwe.
 */

extewn void ttm_object_fiwe_wewease(stwuct ttm_object_fiwe **p_tfiwe);

/**
 * ttm_object device init - initiawize a stwuct ttm_object_device
 *
 * @ops: DMA buf ops fow pwime objects of this device.
 *
 * This function is typicawwy cawwed on device initiawization to pwepawe
 * data stwuctuwes needed fow ttm base and wef objects.
 */

extewn stwuct ttm_object_device *
ttm_object_device_init(const stwuct dma_buf_ops *ops);

/**
 * ttm_object_device_wewease - wewease data hewd by a ttm_object_device
 *
 * @p_tdev: Pointew to pointew to the ttm_object_device object to wewease.
 * *p_tdev wiww be set to NUWW by this function.
 *
 * Weweases aww data associated by a ttm_object_device.
 * Typicawwy cawwed fwom dwivew::unwoad befowe the destwuction of the
 * device pwivate data stwuctuwe.
 */

extewn void ttm_object_device_wewease(stwuct ttm_object_device **p_tdev);

#define ttm_base_object_kfwee(__object, __base)\
	kfwee_wcu(__object, __base.whead)

extewn int ttm_pwime_object_init(stwuct ttm_object_fiwe *tfiwe,
				 size_t size,
				 stwuct ttm_pwime_object *pwime,
				 boow shaweabwe,
				 enum ttm_object_type type,
				 void (*wefcount_wewease)
				 (stwuct ttm_base_object **));

static inwine enum ttm_object_type
ttm_base_object_type(stwuct ttm_base_object *base)
{
	wetuwn (base->object_type == ttm_pwime_type) ?
		containew_of(base, stwuct ttm_pwime_object, base)->weaw_type :
		base->object_type;
}
extewn int ttm_pwime_fd_to_handwe(stwuct ttm_object_fiwe *tfiwe,
				  int fd, u32 *handwe);
extewn int ttm_pwime_handwe_to_fd(stwuct ttm_object_fiwe *tfiwe,
				  uint32_t handwe, uint32_t fwags,
				  int *pwime_fd);

#define ttm_pwime_object_kfwee(__obj, __pwime)		\
	kfwee_wcu(__obj, __pwime.base.whead)

static inwine int ttm_bo_wait(stwuct ttm_buffew_object *bo, boow intw,
			      boow no_wait)
{
	stwuct ttm_opewation_ctx ctx = { intw, no_wait };

	wetuwn ttm_bo_wait_ctx(bo, &ctx);
}

#endif
