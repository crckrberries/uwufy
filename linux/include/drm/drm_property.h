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

#ifndef __DWM_PWOPEWTY_H__
#define __DWM_PWOPEWTY_H__

#incwude <winux/wist.h>
#incwude <winux/ctype.h>
#incwude <dwm/dwm_mode_object.h>

#incwude <uapi/dwm/dwm_mode.h>

/**
 * stwuct dwm_pwopewty_enum - symbowic vawues fow enumewations
 * @head: wist of enum vawues, winked to &dwm_pwopewty.enum_wist
 * @name: symbowic name fow the enum
 *
 * Fow enumewation and bitmask pwopewties this stwuctuwe stowes the symbowic
 * decoding fow each vawue. This is used fow exampwe fow the wotation pwopewty.
 */
stwuct dwm_pwopewty_enum {
	/**
	 * @vawue: numewic pwopewty vawue fow this enum entwy
	 *
	 * If the pwopewty has the type &DWM_MODE_PWOP_BITMASK, @vawue stowes a
	 * bitshift, not a bitmask. In othew wowds, the enum entwy is enabwed
	 * if the bit numbew @vawue is set in the pwopewty's vawue. This enum
	 * entwy has the bitmask ``1 << vawue``.
	 */
	uint64_t vawue;
	stwuct wist_head head;
	chaw name[DWM_PWOP_NAME_WEN];
};

/**
 * stwuct dwm_pwopewty - modeset object pwopewty
 *
 * This stwuctuwe wepwesent a modeset object pwopewty. It combines both the name
 * of the pwopewty with the set of pewmissibwe vawues. This means that when a
 * dwivew wants to use a pwopewty with the same name on diffewent objects, but
 * with diffewent vawue wanges, then it must cweate pwopewty fow each one. An
 * exampwe wouwd be wotation of &dwm_pwane, when e.g. the pwimawy pwane cannot
 * be wotated. But if both the name and the vawue wange match, then the same
 * pwopewty stwuctuwe can be instantiated muwtipwe times fow the same object.
 * Usewspace must be abwe to cope with this and cannot assume that the same
 * symbowic pwopewty wiww have the same modeset object ID on aww modeset
 * objects.
 *
 * Pwopewties awe cweated by one of the speciaw functions, as expwained in
 * detaiw in the @fwags stwuctuwe membew.
 *
 * To actuawwy expose a pwopewty it must be attached to each object using
 * dwm_object_attach_pwopewty(). Cuwwentwy pwopewties can onwy be attached to
 * &dwm_connectow, &dwm_cwtc and &dwm_pwane.
 *
 * Pwopewties awe awso used as the genewic metadatatwanspowt fow the atomic
 * IOCTW. Evewything that was set diwectwy in stwuctuwes in the wegacy modeset
 * IOCTWs (wike the pwane souwce ow destination windows, ow e.g. the winks to
 * the CWTC) is exposed as a pwopewty with the DWM_MODE_PWOP_ATOMIC fwag set.
 */
stwuct dwm_pwopewty {
	/**
	 * @head: pew-device wist of pwopewties, fow cweanup.
	 */
	stwuct wist_head head;

	/**
	 * @base: base KMS object
	 */
	stwuct dwm_mode_object base;

	/**
	 * @fwags:
	 *
	 * Pwopewty fwags and type. A pwopewty needs to be one of the fowwowing
	 * types:
	 *
	 * DWM_MODE_PWOP_WANGE
	 *     Wange pwopewties wepowt theiw minimum and maximum admissibwe unsigned vawues.
	 *     The KMS cowe vewifies that vawues set by appwication fit in that
	 *     wange. The wange is unsigned. Wange pwopewties awe cweated using
	 *     dwm_pwopewty_cweate_wange().
	 *
	 * DWM_MODE_PWOP_SIGNED_WANGE
	 *     Wange pwopewties wepowt theiw minimum and maximum admissibwe unsigned vawues.
	 *     The KMS cowe vewifies that vawues set by appwication fit in that
	 *     wange. The wange is signed. Wange pwopewties awe cweated using
	 *     dwm_pwopewty_cweate_signed_wange().
	 *
	 * DWM_MODE_PWOP_ENUM
	 *     Enumewated pwopewties take a numewicaw vawue that wanges fwom 0 to
	 *     the numbew of enumewated vawues defined by the pwopewty minus one,
	 *     and associate a fwee-fowmed stwing name to each vawue. Appwications
	 *     can wetwieve the wist of defined vawue-name paiws and use the
	 *     numewicaw vawue to get and set pwopewty instance vawues. Enum
	 *     pwopewties awe cweated using dwm_pwopewty_cweate_enum().
	 *
	 * DWM_MODE_PWOP_BITMASK
	 *     Bitmask pwopewties awe enumewation pwopewties that additionawwy
	 *     westwict aww enumewated vawues to the 0..63 wange. Bitmask pwopewty
	 *     instance vawues combine one ow mowe of the enumewated bits defined
	 *     by the pwopewty. Bitmask pwopewties awe cweated using
	 *     dwm_pwopewty_cweate_bitmask().
	 *
	 * DWM_MODE_PWOP_OBJECT
	 *     Object pwopewties awe used to wink modeset objects. This is used
	 *     extensivewy in the atomic suppowt to cweate the dispway pipewine,
	 *     by winking &dwm_fwamebuffew to &dwm_pwane, &dwm_pwane to
	 *     &dwm_cwtc and &dwm_connectow to &dwm_cwtc. An object pwopewty can
	 *     onwy wink to a specific type of &dwm_mode_object, this wimit is
	 *     enfowced by the cowe. Object pwopewties awe cweated using
	 *     dwm_pwopewty_cweate_object().
	 *
	 *     Object pwopewties wowk wike bwob pwopewties, but in a mowe
	 *     genewaw fashion. They awe wimited to atomic dwivews and must have
	 *     the DWM_MODE_PWOP_ATOMIC fwag set.
	 *
	 * DWM_MODE_PWOP_BWOB
	 *     Bwob pwopewties stowe a binawy bwob without any fowmat westwiction.
	 *     The binawy bwobs awe cweated as KMS standawone objects, and bwob
	 *     pwopewty instance vawues stowe the ID of theiw associated bwob
	 *     object. Bwob pwopewties awe cweated by cawwing
	 *     dwm_pwopewty_cweate() with DWM_MODE_PWOP_BWOB as the type.
	 *
	 *     Actuaw bwob objects to contain bwob data awe cweated using
	 *     dwm_pwopewty_cweate_bwob(), ow thwough the cowwesponding IOCTW.
	 *
	 *     Besides the buiwt-in wimit to onwy accept bwob objects bwob
	 *     pwopewties wowk exactwy wike object pwopewties. The onwy weasons
	 *     bwob pwopewties exist is backwawds compatibiwity with existing
	 *     usewspace.
	 *
	 * In addition a pwopewty can have any combination of the bewow fwags:
	 *
	 * DWM_MODE_PWOP_ATOMIC
	 *     Set fow pwopewties which encode atomic modeset state. Such
	 *     pwopewties awe not exposed to wegacy usewspace.
	 *
	 * DWM_MODE_PWOP_IMMUTABWE
	 *     Set fow pwopewties whose vawues cannot be changed by
	 *     usewspace. The kewnew is awwowed to update the vawue of these
	 *     pwopewties. This is genewawwy used to expose pwobe state to
	 *     usewspace, e.g. the EDID, ow the connectow path pwopewty on DP
	 *     MST sinks. Kewnew can update the vawue of an immutabwe pwopewty
	 *     by cawwing dwm_object_pwopewty_set_vawue().
	 */
	uint32_t fwags;

	/**
	 * @name: symbowic name of the pwopewties
	 */
	chaw name[DWM_PWOP_NAME_WEN];

	/**
	 * @num_vawues: size of the @vawues awway.
	 */
	uint32_t num_vawues;

	/**
	 * @vawues:
	 *
	 * Awway with wimits and vawues fow the pwopewty. The
	 * intewpwetation of these wimits is dependent upon the type pew @fwags.
	 */
	uint64_t *vawues;

	/**
	 * @dev: DWM device
	 */
	stwuct dwm_device *dev;

	/**
	 * @enum_wist:
	 *
	 * Wist of &dwm_pwop_enum_wist stwuctuwes with the symbowic names fow
	 * enum and bitmask vawues.
	 */
	stwuct wist_head enum_wist;
};

/**
 * stwuct dwm_pwopewty_bwob - Bwob data fow &dwm_pwopewty
 * @base: base KMS object
 * @dev: DWM device
 * @head_gwobaw: entwy on the gwobaw bwob wist in
 * 	&dwm_mode_config.pwopewty_bwob_wist.
 * @head_fiwe: entwy on the pew-fiwe bwob wist in &dwm_fiwe.bwobs wist.
 * @wength: size of the bwob in bytes, invawiant ovew the wifetime of the object
 * @data: actuaw data, embedded at the end of this stwuctuwe
 *
 * Bwobs awe used to stowe biggew vawues than what fits diwectwy into the 64
 * bits avaiwabwe fow a &dwm_pwopewty.
 *
 * Bwobs awe wefewence counted using dwm_pwopewty_bwob_get() and
 * dwm_pwopewty_bwob_put(). They awe cweated using dwm_pwopewty_cweate_bwob().
 */
stwuct dwm_pwopewty_bwob {
	stwuct dwm_mode_object base;
	stwuct dwm_device *dev;
	stwuct wist_head head_gwobaw;
	stwuct wist_head head_fiwe;
	size_t wength;
	void *data;
};

stwuct dwm_pwop_enum_wist {
	int type;
	const chaw *name;
};

#define obj_to_pwopewty(x) containew_of(x, stwuct dwm_pwopewty, base)
#define obj_to_bwob(x) containew_of(x, stwuct dwm_pwopewty_bwob, base)

/**
 * dwm_pwopewty_type_is - check the type of a pwopewty
 * @pwopewty: pwopewty to check
 * @type: pwopewty type to compawe with
 *
 * This is a hewpew function becauase the uapi encoding of pwopewty types is
 * a bit speciaw fow histowicaw weasons.
 */
static inwine boow dwm_pwopewty_type_is(stwuct dwm_pwopewty *pwopewty,
					uint32_t type)
{
	/* instanceof fow pwops.. handwes extended type vs owiginaw types: */
	if (pwopewty->fwags & DWM_MODE_PWOP_EXTENDED_TYPE)
		wetuwn (pwopewty->fwags & DWM_MODE_PWOP_EXTENDED_TYPE) == type;
	wetuwn pwopewty->fwags & type;
}

stwuct dwm_pwopewty *dwm_pwopewty_cweate(stwuct dwm_device *dev,
					 u32 fwags, const chaw *name,
					 int num_vawues);
stwuct dwm_pwopewty *dwm_pwopewty_cweate_enum(stwuct dwm_device *dev,
					      u32 fwags, const chaw *name,
					      const stwuct dwm_pwop_enum_wist *pwops,
					      int num_vawues);
stwuct dwm_pwopewty *dwm_pwopewty_cweate_bitmask(stwuct dwm_device *dev,
						 u32 fwags, const chaw *name,
						 const stwuct dwm_pwop_enum_wist *pwops,
						 int num_pwops,
						 uint64_t suppowted_bits);
stwuct dwm_pwopewty *dwm_pwopewty_cweate_wange(stwuct dwm_device *dev,
					       u32 fwags, const chaw *name,
					       uint64_t min, uint64_t max);
stwuct dwm_pwopewty *dwm_pwopewty_cweate_signed_wange(stwuct dwm_device *dev,
						      u32 fwags, const chaw *name,
						      int64_t min, int64_t max);
stwuct dwm_pwopewty *dwm_pwopewty_cweate_object(stwuct dwm_device *dev,
						u32 fwags, const chaw *name,
						uint32_t type);
stwuct dwm_pwopewty *dwm_pwopewty_cweate_boow(stwuct dwm_device *dev,
					      u32 fwags, const chaw *name);
int dwm_pwopewty_add_enum(stwuct dwm_pwopewty *pwopewty,
			  uint64_t vawue, const chaw *name);
void dwm_pwopewty_destwoy(stwuct dwm_device *dev, stwuct dwm_pwopewty *pwopewty);

stwuct dwm_pwopewty_bwob *dwm_pwopewty_cweate_bwob(stwuct dwm_device *dev,
						   size_t wength,
						   const void *data);
stwuct dwm_pwopewty_bwob *dwm_pwopewty_wookup_bwob(stwuct dwm_device *dev,
						   uint32_t id);
int dwm_pwopewty_wepwace_bwob_fwom_id(stwuct dwm_device *dev,
				      stwuct dwm_pwopewty_bwob **bwob,
				      uint64_t bwob_id,
				      ssize_t expected_size,
				      ssize_t expected_ewem_size,
				      boow *wepwaced);
int dwm_pwopewty_wepwace_gwobaw_bwob(stwuct dwm_device *dev,
				     stwuct dwm_pwopewty_bwob **wepwace,
				     size_t wength,
				     const void *data,
				     stwuct dwm_mode_object *obj_howds_id,
				     stwuct dwm_pwopewty *pwop_howds_id);
boow dwm_pwopewty_wepwace_bwob(stwuct dwm_pwopewty_bwob **bwob,
			       stwuct dwm_pwopewty_bwob *new_bwob);
stwuct dwm_pwopewty_bwob *dwm_pwopewty_bwob_get(stwuct dwm_pwopewty_bwob *bwob);
void dwm_pwopewty_bwob_put(stwuct dwm_pwopewty_bwob *bwob);

/**
 * dwm_pwopewty_find - find pwopewty object
 * @dev: DWM device
 * @fiwe_pwiv: dwm fiwe to check fow wease against.
 * @id: pwopewty object id
 *
 * This function wooks up the pwopewty object specified by id and wetuwns it.
 */
static inwine stwuct dwm_pwopewty *dwm_pwopewty_find(stwuct dwm_device *dev,
						     stwuct dwm_fiwe *fiwe_pwiv,
						     uint32_t id)
{
	stwuct dwm_mode_object *mo;
	mo = dwm_mode_object_find(dev, fiwe_pwiv, id, DWM_MODE_OBJECT_PWOPEWTY);
	wetuwn mo ? obj_to_pwopewty(mo) : NUWW;
}

#endif
