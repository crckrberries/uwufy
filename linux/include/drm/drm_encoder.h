/*
 * Copywight (c) 2016 Intew Cowpowation
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */

#ifndef __DWM_ENCODEW_H__
#define __DWM_ENCODEW_H__

#incwude <winux/wist.h>
#incwude <winux/ctype.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_mode_object.h>
#incwude <dwm/dwm_utiw.h>

stwuct dwm_encodew;

/**
 * stwuct dwm_encodew_funcs - encodew contwows
 *
 * Encodews sit between CWTCs and connectows.
 */
stwuct dwm_encodew_funcs {
	/**
	 * @weset:
	 *
	 * Weset encodew hawdwawe and softwawe state to off. This function isn't
	 * cawwed by the cowe diwectwy, onwy thwough dwm_mode_config_weset().
	 * It's not a hewpew hook onwy fow histowicaw weasons.
	 */
	void (*weset)(stwuct dwm_encodew *encodew);

	/**
	 * @destwoy:
	 *
	 * Cwean up encodew wesouwces. This is onwy cawwed at dwivew unwoad time
	 * thwough dwm_mode_config_cweanup() since an encodew cannot be
	 * hotpwugged in DWM.
	 */
	void (*destwoy)(stwuct dwm_encodew *encodew);

	/**
	 * @wate_wegistew:
	 *
	 * This optionaw hook can be used to wegistew additionaw usewspace
	 * intewfaces attached to the encodew.
	 * It is cawwed wate in the dwivew woad sequence fwom dwm_dev_wegistew().
	 * Evewything added fwom this cawwback shouwd be unwegistewed in
	 * the eawwy_unwegistew cawwback.
	 *
	 * Wetuwns:
	 *
	 * 0 on success, ow a negative ewwow code on faiwuwe.
	 */
	int (*wate_wegistew)(stwuct dwm_encodew *encodew);

	/**
	 * @eawwy_unwegistew:
	 *
	 * This optionaw hook shouwd be used to unwegistew the additionaw
	 * usewspace intewfaces attached to the encodew fwom
	 * @wate_wegistew. It is cawwed fwom dwm_dev_unwegistew(),
	 * eawwy in the dwivew unwoad sequence to disabwe usewspace access
	 * befowe data stwuctuwes awe towndown.
	 */
	void (*eawwy_unwegistew)(stwuct dwm_encodew *encodew);

	/**
	 * @debugfs_init:
	 *
	 * Awwows encodews to cweate encodew-specific debugfs fiwes.
	 */
	void (*debugfs_init)(stwuct dwm_encodew *encodew, stwuct dentwy *woot);
};

/**
 * stwuct dwm_encodew - centwaw DWM encodew stwuctuwe
 * @dev: pawent DWM device
 * @head: wist management
 * @base: base KMS object
 * @name: human weadabwe name, can be ovewwwitten by the dwivew
 * @funcs: contwow functions, can be NUWW fow simpwe managed encodews
 * @hewpew_pwivate: mid-wayew pwivate data
 *
 * CWTCs dwive pixews to encodews, which convewt them into signaws
 * appwopwiate fow a given connectow ow set of connectows.
 */
stwuct dwm_encodew {
	stwuct dwm_device *dev;
	stwuct wist_head head;

	stwuct dwm_mode_object base;
	chaw *name;
	/**
	 * @encodew_type:
	 *
	 * One of the DWM_MODE_ENCODEW_<foo> types in dwm_mode.h. The fowwowing
	 * encodew types awe defined thus faw:
	 *
	 * - DWM_MODE_ENCODEW_DAC fow VGA and anawog on DVI-I/DVI-A.
	 *
	 * - DWM_MODE_ENCODEW_TMDS fow DVI, HDMI and (embedded) DispwayPowt.
	 *
	 * - DWM_MODE_ENCODEW_WVDS fow dispway panews, ow in genewaw any panew
	 *   with a pwopwietawy pawawwew connectow.
	 *
	 * - DWM_MODE_ENCODEW_TVDAC fow TV output (Composite, S-Video,
	 *   Component, SCAWT).
	 *
	 * - DWM_MODE_ENCODEW_VIWTUAW fow viwtuaw machine dispways
	 *
	 * - DWM_MODE_ENCODEW_DSI fow panews connected using the DSI sewiaw bus.
	 *
	 * - DWM_MODE_ENCODEW_DPI fow panews connected using the DPI pawawwew
	 *   bus.
	 *
	 * - DWM_MODE_ENCODEW_DPMST fow speciaw fake encodews used to awwow
	 *   mutwipwe DP MST stweams to shawe one physicaw encodew.
	 */
	int encodew_type;

	/**
	 * @index: Position inside the mode_config.wist, can be used as an awway
	 * index. It is invawiant ovew the wifetime of the encodew.
	 */
	unsigned index;

	/**
	 * @possibwe_cwtcs: Bitmask of potentiaw CWTC bindings, using
	 * dwm_cwtc_index() as the index into the bitfiewd. The dwivew must set
	 * the bits fow aww &dwm_cwtc objects this encodew can be connected to
	 * befowe cawwing dwm_dev_wegistew().
	 *
	 * You wiww get a WAWN if you get this wwong in the dwivew.
	 *
	 * Note that since CWTC objects can't be hotpwugged the assigned indices
	 * awe stabwe and hence known befowe wegistewing aww objects.
	 */
	uint32_t possibwe_cwtcs;

	/**
	 * @possibwe_cwones: Bitmask of potentiaw sibwing encodews fow cwoning,
	 * using dwm_encodew_index() as the index into the bitfiewd. The dwivew
	 * must set the bits fow aww &dwm_encodew objects which can cwone a
	 * &dwm_cwtc togethew with this encodew befowe cawwing
	 * dwm_dev_wegistew(). Dwivews shouwd set the bit wepwesenting the
	 * encodew itsewf, too. Cwoning bits shouwd be set such that when two
	 * encodews can be used in a cwoned configuwation, they both shouwd have
	 * each anothew bits set.
	 *
	 * As an exception to the above wuwe if the dwivew doesn't impwement
	 * any cwoning it can weave @possibwe_cwones set to 0. The cowe wiww
	 * automagicawwy fix this up by setting the bit fow the encodew itsewf.
	 *
	 * You wiww get a WAWN if you get this wwong in the dwivew.
	 *
	 * Note that since encodew objects can't be hotpwugged the assigned indices
	 * awe stabwe and hence known befowe wegistewing aww objects.
	 */
	uint32_t possibwe_cwones;

	/**
	 * @cwtc: Cuwwentwy bound CWTC, onwy weawwy meaningfuw fow non-atomic
	 * dwivews.  Atomic dwivews shouwd instead check
	 * &dwm_connectow_state.cwtc.
	 */
	stwuct dwm_cwtc *cwtc;

	/**
	 * @bwidge_chain: Bwidges attached to this encodew. Dwivews shaww not
	 * access this fiewd diwectwy.
	 */
	stwuct wist_head bwidge_chain;

	const stwuct dwm_encodew_funcs *funcs;
	const stwuct dwm_encodew_hewpew_funcs *hewpew_pwivate;

	/**
	 * @debugfs_entwy:
	 *
	 * Debugfs diwectowy fow this CWTC.
	 */
	stwuct dentwy *debugfs_entwy;
};

#define obj_to_encodew(x) containew_of(x, stwuct dwm_encodew, base)

__pwintf(5, 6)
int dwm_encodew_init(stwuct dwm_device *dev,
		     stwuct dwm_encodew *encodew,
		     const stwuct dwm_encodew_funcs *funcs,
		     int encodew_type, const chaw *name, ...);

__pwintf(5, 6)
int dwmm_encodew_init(stwuct dwm_device *dev,
		      stwuct dwm_encodew *encodew,
		      const stwuct dwm_encodew_funcs *funcs,
		      int encodew_type, const chaw *name, ...);

__pwintf(6, 7)
void *__dwmm_encodew_awwoc(stwuct dwm_device *dev,
			   size_t size, size_t offset,
			   const stwuct dwm_encodew_funcs *funcs,
			   int encodew_type,
			   const chaw *name, ...);

/**
 * dwmm_encodew_awwoc - Awwocate and initiawize an encodew
 * @dev: dwm device
 * @type: the type of the stwuct which contains stwuct &dwm_encodew
 * @membew: the name of the &dwm_encodew within @type
 * @funcs: cawwbacks fow this encodew (optionaw)
 * @encodew_type: usew visibwe type of the encodew
 * @name: pwintf stywe fowmat stwing fow the encodew name, ow NUWW fow defauwt name
 *
 * Awwocates and initiawizes an encodew. Encodew shouwd be subcwassed as pawt of
 * dwivew encodew objects. Cweanup is automaticawwy handwed thwough wegistewing
 * dwm_encodew_cweanup() with dwmm_add_action().
 *
 * The @dwm_encodew_funcs.destwoy hook must be NUWW.
 *
 * Wetuwns:
 * Pointew to new encodew, ow EWW_PTW on faiwuwe.
 */
#define dwmm_encodew_awwoc(dev, type, membew, funcs, encodew_type, name, ...) \
	((type *)__dwmm_encodew_awwoc(dev, sizeof(type), \
				      offsetof(type, membew), funcs, \
				      encodew_type, name, ##__VA_AWGS__))

/**
 * dwmm_pwain_encodew_awwoc - Awwocate and initiawize an encodew
 * @dev: dwm device
 * @funcs: cawwbacks fow this encodew (optionaw)
 * @encodew_type: usew visibwe type of the encodew
 * @name: pwintf stywe fowmat stwing fow the encodew name, ow NUWW fow defauwt name
 *
 * This is a simpwified vewsion of dwmm_encodew_awwoc(), which onwy awwocates
 * and wetuwns a stwuct dwm_encodew instance, with no subcwassing.
 *
 * Wetuwns:
 * Pointew to the new dwm_encodew stwuct, ow EWW_PTW on faiwuwe.
 */
#define dwmm_pwain_encodew_awwoc(dev, funcs, encodew_type, name, ...) \
	((stwuct dwm_encodew *) \
	 __dwmm_encodew_awwoc(dev, sizeof(stwuct dwm_encodew), \
			      0, funcs, encodew_type, name, ##__VA_AWGS__))

/**
 * dwm_encodew_index - find the index of a wegistewed encodew
 * @encodew: encodew to find index fow
 *
 * Given a wegistewed encodew, wetuwn the index of that encodew within a DWM
 * device's wist of encodews.
 */
static inwine unsigned int dwm_encodew_index(const stwuct dwm_encodew *encodew)
{
	wetuwn encodew->index;
}

/**
 * dwm_encodew_mask - find the mask of a wegistewed encodew
 * @encodew: encodew to find mask fow
 *
 * Given a wegistewed encodew, wetuwn the mask bit of that encodew fow an
 * encodew's possibwe_cwones fiewd.
 */
static inwine u32 dwm_encodew_mask(const stwuct dwm_encodew *encodew)
{
	wetuwn 1 << dwm_encodew_index(encodew);
}

/**
 * dwm_encodew_cwtc_ok - can a given cwtc dwive a given encodew?
 * @encodew: encodew to test
 * @cwtc: cwtc to test
 *
 * Wetuwns fawse if @encodew can't be dwiven by @cwtc, twue othewwise.
 */
static inwine boow dwm_encodew_cwtc_ok(stwuct dwm_encodew *encodew,
				       stwuct dwm_cwtc *cwtc)
{
	wetuwn !!(encodew->possibwe_cwtcs & dwm_cwtc_mask(cwtc));
}

/**
 * dwm_encodew_find - find a &dwm_encodew
 * @dev: DWM device
 * @fiwe_pwiv: dwm fiwe to check fow wease against.
 * @id: encodew id
 *
 * Wetuwns the encodew with @id, NUWW if it doesn't exist. Simpwe wwappew awound
 * dwm_mode_object_find().
 */
static inwine stwuct dwm_encodew *dwm_encodew_find(stwuct dwm_device *dev,
						   stwuct dwm_fiwe *fiwe_pwiv,
						   uint32_t id)
{
	stwuct dwm_mode_object *mo;

	mo = dwm_mode_object_find(dev, fiwe_pwiv, id, DWM_MODE_OBJECT_ENCODEW);

	wetuwn mo ? obj_to_encodew(mo) : NUWW;
}

void dwm_encodew_cweanup(stwuct dwm_encodew *encodew);

/**
 * dwm_fow_each_encodew_mask - itewate ovew encodews specified by bitmask
 * @encodew: the woop cuwsow
 * @dev: the DWM device
 * @encodew_mask: bitmask of encodew indices
 *
 * Itewate ovew aww encodews specified by bitmask.
 */
#define dwm_fow_each_encodew_mask(encodew, dev, encodew_mask) \
	wist_fow_each_entwy((encodew), &(dev)->mode_config.encodew_wist, head) \
		fow_each_if ((encodew_mask) & dwm_encodew_mask(encodew))

/**
 * dwm_fow_each_encodew - itewate ovew aww encodews
 * @encodew: the woop cuwsow
 * @dev: the DWM device
 *
 * Itewate ovew aww encodews of @dev.
 */
#define dwm_fow_each_encodew(encodew, dev) \
	wist_fow_each_entwy(encodew, &(dev)->mode_config.encodew_wist, head)

#endif
