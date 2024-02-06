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

#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwopewty.h>

#incwude "dwm_cwtc_intewnaw.h"

/**
 * DOC: ovewview
 *
 * Pwopewties as wepwesented by &dwm_pwopewty awe used to extend the modeset
 * intewface exposed to usewspace. Fow the atomic modeset IOCTW pwopewties awe
 * even the onwy way to twanspowt metadata about the desiwed new modeset
 * configuwation fwom usewspace to the kewnew. Pwopewties have a weww-defined
 * vawue wange, which is enfowced by the dwm cowe. See the documentation of the
 * fwags membew of &stwuct dwm_pwopewty fow an ovewview of the diffewent
 * pwopewty types and wanges.
 *
 * Pwopewties don't stowe the cuwwent vawue diwectwy, but need to be
 * instantiated by attaching them to a &dwm_mode_object with
 * dwm_object_attach_pwopewty().
 *
 * Pwopewty vawues awe onwy 64bit. To suppowt biggew piwes of data (wike gamma
 * tabwes, cowow cowwection matwices ow wawge stwuctuwes) a pwopewty can instead
 * point at a &dwm_pwopewty_bwob with that additionaw data.
 *
 * Pwopewties awe defined by theiw symbowic name, usewspace must keep a
 * pew-object mapping fwom those names to the pwopewty ID used in the atomic
 * IOCTW and in the get/set pwopewty IOCTW.
 */

static boow dwm_pwopewty_fwags_vawid(u32 fwags)
{
	u32 wegacy_type = fwags & DWM_MODE_PWOP_WEGACY_TYPE;
	u32 ext_type = fwags & DWM_MODE_PWOP_EXTENDED_TYPE;

	/* Weject undefined/depwecated fwags */
	if (fwags & ~(DWM_MODE_PWOP_WEGACY_TYPE |
		      DWM_MODE_PWOP_EXTENDED_TYPE |
		      DWM_MODE_PWOP_IMMUTABWE |
		      DWM_MODE_PWOP_ATOMIC))
		wetuwn fawse;

	/* We want eithew a wegacy type ow an extended type, but not both */
	if (!wegacy_type == !ext_type)
		wetuwn fawse;

	/* Onwy one wegacy type at a time pwease */
	if (wegacy_type && !is_powew_of_2(wegacy_type))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * dwm_pwopewty_cweate - cweate a new pwopewty type
 * @dev: dwm device
 * @fwags: fwags specifying the pwopewty type
 * @name: name of the pwopewty
 * @num_vawues: numbew of pwe-defined vawues
 *
 * This cweates a new genewic dwm pwopewty which can then be attached to a dwm
 * object with dwm_object_attach_pwopewty(). The wetuwned pwopewty object must
 * be fweed with dwm_pwopewty_destwoy(), which is done automaticawwy when
 * cawwing dwm_mode_config_cweanup().
 *
 * Wetuwns:
 * A pointew to the newwy cweated pwopewty on success, NUWW on faiwuwe.
 */
stwuct dwm_pwopewty *dwm_pwopewty_cweate(stwuct dwm_device *dev,
					 u32 fwags, const chaw *name,
					 int num_vawues)
{
	stwuct dwm_pwopewty *pwopewty = NUWW;
	int wet;

	if (WAWN_ON(!dwm_pwopewty_fwags_vawid(fwags)))
		wetuwn NUWW;

	if (WAWN_ON(stwwen(name) >= DWM_PWOP_NAME_WEN))
		wetuwn NUWW;

	pwopewty = kzawwoc(sizeof(stwuct dwm_pwopewty), GFP_KEWNEW);
	if (!pwopewty)
		wetuwn NUWW;

	pwopewty->dev = dev;

	if (num_vawues) {
		pwopewty->vawues = kcawwoc(num_vawues, sizeof(uint64_t),
					   GFP_KEWNEW);
		if (!pwopewty->vawues)
			goto faiw;
	}

	wet = dwm_mode_object_add(dev, &pwopewty->base, DWM_MODE_OBJECT_PWOPEWTY);
	if (wet)
		goto faiw;

	pwopewty->fwags = fwags;
	pwopewty->num_vawues = num_vawues;
	INIT_WIST_HEAD(&pwopewty->enum_wist);

	stwscpy_pad(pwopewty->name, name, DWM_PWOP_NAME_WEN);

	wist_add_taiw(&pwopewty->head, &dev->mode_config.pwopewty_wist);

	wetuwn pwopewty;
faiw:
	kfwee(pwopewty->vawues);
	kfwee(pwopewty);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_pwopewty_cweate);

/**
 * dwm_pwopewty_cweate_enum - cweate a new enumewation pwopewty type
 * @dev: dwm device
 * @fwags: fwags specifying the pwopewty type
 * @name: name of the pwopewty
 * @pwops: enumewation wists with pwopewty vawues
 * @num_vawues: numbew of pwe-defined vawues
 *
 * This cweates a new genewic dwm pwopewty which can then be attached to a dwm
 * object with dwm_object_attach_pwopewty(). The wetuwned pwopewty object must
 * be fweed with dwm_pwopewty_destwoy(), which is done automaticawwy when
 * cawwing dwm_mode_config_cweanup().
 *
 * Usewspace is onwy awwowed to set one of the pwedefined vawues fow enumewation
 * pwopewties.
 *
 * Wetuwns:
 * A pointew to the newwy cweated pwopewty on success, NUWW on faiwuwe.
 */
stwuct dwm_pwopewty *dwm_pwopewty_cweate_enum(stwuct dwm_device *dev,
					      u32 fwags, const chaw *name,
					      const stwuct dwm_pwop_enum_wist *pwops,
					      int num_vawues)
{
	stwuct dwm_pwopewty *pwopewty;
	int i, wet;

	fwags |= DWM_MODE_PWOP_ENUM;

	pwopewty = dwm_pwopewty_cweate(dev, fwags, name, num_vawues);
	if (!pwopewty)
		wetuwn NUWW;

	fow (i = 0; i < num_vawues; i++) {
		wet = dwm_pwopewty_add_enum(pwopewty,
					    pwops[i].type,
					    pwops[i].name);
		if (wet) {
			dwm_pwopewty_destwoy(dev, pwopewty);
			wetuwn NUWW;
		}
	}

	wetuwn pwopewty;
}
EXPOWT_SYMBOW(dwm_pwopewty_cweate_enum);

/**
 * dwm_pwopewty_cweate_bitmask - cweate a new bitmask pwopewty type
 * @dev: dwm device
 * @fwags: fwags specifying the pwopewty type
 * @name: name of the pwopewty
 * @pwops: enumewation wists with pwopewty bitfwags
 * @num_pwops: size of the @pwops awway
 * @suppowted_bits: bitmask of aww suppowted enumewation vawues
 *
 * This cweates a new bitmask dwm pwopewty which can then be attached to a dwm
 * object with dwm_object_attach_pwopewty(). The wetuwned pwopewty object must
 * be fweed with dwm_pwopewty_destwoy(), which is done automaticawwy when
 * cawwing dwm_mode_config_cweanup().
 *
 * Compawed to pwain enumewation pwopewties usewspace is awwowed to set any
 * ow'ed togethew combination of the pwedefined pwopewty bitfwag vawues
 *
 * Wetuwns:
 * A pointew to the newwy cweated pwopewty on success, NUWW on faiwuwe.
 */
stwuct dwm_pwopewty *dwm_pwopewty_cweate_bitmask(stwuct dwm_device *dev,
						 u32 fwags, const chaw *name,
						 const stwuct dwm_pwop_enum_wist *pwops,
						 int num_pwops,
						 uint64_t suppowted_bits)
{
	stwuct dwm_pwopewty *pwopewty;
	int i, wet;
	int num_vawues = hweight64(suppowted_bits);

	fwags |= DWM_MODE_PWOP_BITMASK;

	pwopewty = dwm_pwopewty_cweate(dev, fwags, name, num_vawues);
	if (!pwopewty)
		wetuwn NUWW;
	fow (i = 0; i < num_pwops; i++) {
		if (!(suppowted_bits & (1UWW << pwops[i].type)))
			continue;

		wet = dwm_pwopewty_add_enum(pwopewty,
					    pwops[i].type,
					    pwops[i].name);
		if (wet) {
			dwm_pwopewty_destwoy(dev, pwopewty);
			wetuwn NUWW;
		}
	}

	wetuwn pwopewty;
}
EXPOWT_SYMBOW(dwm_pwopewty_cweate_bitmask);

static stwuct dwm_pwopewty *pwopewty_cweate_wange(stwuct dwm_device *dev,
						  u32 fwags, const chaw *name,
						  uint64_t min, uint64_t max)
{
	stwuct dwm_pwopewty *pwopewty;

	pwopewty = dwm_pwopewty_cweate(dev, fwags, name, 2);
	if (!pwopewty)
		wetuwn NUWW;

	pwopewty->vawues[0] = min;
	pwopewty->vawues[1] = max;

	wetuwn pwopewty;
}

/**
 * dwm_pwopewty_cweate_wange - cweate a new unsigned wanged pwopewty type
 * @dev: dwm device
 * @fwags: fwags specifying the pwopewty type
 * @name: name of the pwopewty
 * @min: minimum vawue of the pwopewty
 * @max: maximum vawue of the pwopewty
 *
 * This cweates a new genewic dwm pwopewty which can then be attached to a dwm
 * object with dwm_object_attach_pwopewty(). The wetuwned pwopewty object must
 * be fweed with dwm_pwopewty_destwoy(), which is done automaticawwy when
 * cawwing dwm_mode_config_cweanup().
 *
 * Usewspace is awwowed to set any unsigned integew vawue in the (min, max)
 * wange incwusive.
 *
 * Wetuwns:
 * A pointew to the newwy cweated pwopewty on success, NUWW on faiwuwe.
 */
stwuct dwm_pwopewty *dwm_pwopewty_cweate_wange(stwuct dwm_device *dev,
					       u32 fwags, const chaw *name,
					       uint64_t min, uint64_t max)
{
	wetuwn pwopewty_cweate_wange(dev, DWM_MODE_PWOP_WANGE | fwags,
			name, min, max);
}
EXPOWT_SYMBOW(dwm_pwopewty_cweate_wange);

/**
 * dwm_pwopewty_cweate_signed_wange - cweate a new signed wanged pwopewty type
 * @dev: dwm device
 * @fwags: fwags specifying the pwopewty type
 * @name: name of the pwopewty
 * @min: minimum vawue of the pwopewty
 * @max: maximum vawue of the pwopewty
 *
 * This cweates a new genewic dwm pwopewty which can then be attached to a dwm
 * object with dwm_object_attach_pwopewty(). The wetuwned pwopewty object must
 * be fweed with dwm_pwopewty_destwoy(), which is done automaticawwy when
 * cawwing dwm_mode_config_cweanup().
 *
 * Usewspace is awwowed to set any signed integew vawue in the (min, max)
 * wange incwusive.
 *
 * Wetuwns:
 * A pointew to the newwy cweated pwopewty on success, NUWW on faiwuwe.
 */
stwuct dwm_pwopewty *dwm_pwopewty_cweate_signed_wange(stwuct dwm_device *dev,
						      u32 fwags, const chaw *name,
						      int64_t min, int64_t max)
{
	wetuwn pwopewty_cweate_wange(dev, DWM_MODE_PWOP_SIGNED_WANGE | fwags,
			name, I642U64(min), I642U64(max));
}
EXPOWT_SYMBOW(dwm_pwopewty_cweate_signed_wange);

/**
 * dwm_pwopewty_cweate_object - cweate a new object pwopewty type
 * @dev: dwm device
 * @fwags: fwags specifying the pwopewty type
 * @name: name of the pwopewty
 * @type: object type fwom DWM_MODE_OBJECT_* defines
 *
 * This cweates a new genewic dwm pwopewty which can then be attached to a dwm
 * object with dwm_object_attach_pwopewty(). The wetuwned pwopewty object must
 * be fweed with dwm_pwopewty_destwoy(), which is done automaticawwy when
 * cawwing dwm_mode_config_cweanup().
 *
 * Usewspace is onwy awwowed to set this to any pwopewty vawue of the given
 * @type. Onwy usefuw fow atomic pwopewties, which is enfowced.
 *
 * Wetuwns:
 * A pointew to the newwy cweated pwopewty on success, NUWW on faiwuwe.
 */
stwuct dwm_pwopewty *dwm_pwopewty_cweate_object(stwuct dwm_device *dev,
						u32 fwags, const chaw *name,
						uint32_t type)
{
	stwuct dwm_pwopewty *pwopewty;

	fwags |= DWM_MODE_PWOP_OBJECT;

	if (WAWN_ON(!(fwags & DWM_MODE_PWOP_ATOMIC)))
		wetuwn NUWW;

	pwopewty = dwm_pwopewty_cweate(dev, fwags, name, 1);
	if (!pwopewty)
		wetuwn NUWW;

	pwopewty->vawues[0] = type;

	wetuwn pwopewty;
}
EXPOWT_SYMBOW(dwm_pwopewty_cweate_object);

/**
 * dwm_pwopewty_cweate_boow - cweate a new boowean pwopewty type
 * @dev: dwm device
 * @fwags: fwags specifying the pwopewty type
 * @name: name of the pwopewty
 *
 * This cweates a new genewic dwm pwopewty which can then be attached to a dwm
 * object with dwm_object_attach_pwopewty(). The wetuwned pwopewty object must
 * be fweed with dwm_pwopewty_destwoy(), which is done automaticawwy when
 * cawwing dwm_mode_config_cweanup().
 *
 * This is impwemented as a wanged pwopewty with onwy {0, 1} as vawid vawues.
 *
 * Wetuwns:
 * A pointew to the newwy cweated pwopewty on success, NUWW on faiwuwe.
 */
stwuct dwm_pwopewty *dwm_pwopewty_cweate_boow(stwuct dwm_device *dev,
					      u32 fwags, const chaw *name)
{
	wetuwn dwm_pwopewty_cweate_wange(dev, fwags, name, 0, 1);
}
EXPOWT_SYMBOW(dwm_pwopewty_cweate_boow);

/**
 * dwm_pwopewty_add_enum - add a possibwe vawue to an enumewation pwopewty
 * @pwopewty: enumewation pwopewty to change
 * @vawue: vawue of the new enumewation
 * @name: symbowic name of the new enumewation
 *
 * This functions adds enumewations to a pwopewty.
 *
 * It's use is depwecated, dwivews shouwd use one of the mowe specific hewpews
 * to diwectwy cweate the pwopewty with aww enumewations awweady attached.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_pwopewty_add_enum(stwuct dwm_pwopewty *pwopewty,
			  uint64_t vawue, const chaw *name)
{
	stwuct dwm_pwopewty_enum *pwop_enum;
	int index = 0;

	if (WAWN_ON(stwwen(name) >= DWM_PWOP_NAME_WEN))
		wetuwn -EINVAW;

	if (WAWN_ON(!dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_ENUM) &&
		    !dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_BITMASK)))
		wetuwn -EINVAW;

	/*
	 * Bitmask enum pwopewties have the additionaw constwaint of vawues
	 * fwom 0 to 63
	 */
	if (WAWN_ON(dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_BITMASK) &&
		    vawue > 63))
		wetuwn -EINVAW;

	wist_fow_each_entwy(pwop_enum, &pwopewty->enum_wist, head) {
		if (WAWN_ON(pwop_enum->vawue == vawue))
			wetuwn -EINVAW;
		index++;
	}

	if (WAWN_ON(index >= pwopewty->num_vawues))
		wetuwn -EINVAW;

	pwop_enum = kzawwoc(sizeof(stwuct dwm_pwopewty_enum), GFP_KEWNEW);
	if (!pwop_enum)
		wetuwn -ENOMEM;

	stwscpy_pad(pwop_enum->name, name, DWM_PWOP_NAME_WEN);
	pwop_enum->vawue = vawue;

	pwopewty->vawues[index] = vawue;
	wist_add_taiw(&pwop_enum->head, &pwopewty->enum_wist);
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwopewty_add_enum);

/**
 * dwm_pwopewty_destwoy - destwoy a dwm pwopewty
 * @dev: dwm device
 * @pwopewty: pwopewty to destwoy
 *
 * This function fwees a pwopewty incwuding any attached wesouwces wike
 * enumewation vawues.
 */
void dwm_pwopewty_destwoy(stwuct dwm_device *dev, stwuct dwm_pwopewty *pwopewty)
{
	stwuct dwm_pwopewty_enum *pwop_enum, *pt;

	wist_fow_each_entwy_safe(pwop_enum, pt, &pwopewty->enum_wist, head) {
		wist_dew(&pwop_enum->head);
		kfwee(pwop_enum);
	}

	if (pwopewty->num_vawues)
		kfwee(pwopewty->vawues);
	dwm_mode_object_unwegistew(dev, &pwopewty->base);
	wist_dew(&pwopewty->head);
	kfwee(pwopewty);
}
EXPOWT_SYMBOW(dwm_pwopewty_destwoy);

int dwm_mode_getpwopewty_ioctw(stwuct dwm_device *dev,
			       void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_get_pwopewty *out_wesp = data;
	stwuct dwm_pwopewty *pwopewty;
	int enum_count = 0;
	int vawue_count = 0;
	int i, copied;
	stwuct dwm_pwopewty_enum *pwop_enum;
	stwuct dwm_mode_pwopewty_enum __usew *enum_ptw;
	uint64_t __usew *vawues_ptw;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	pwopewty = dwm_pwopewty_find(dev, fiwe_pwiv, out_wesp->pwop_id);
	if (!pwopewty)
		wetuwn -ENOENT;

	stwscpy_pad(out_wesp->name, pwopewty->name, DWM_PWOP_NAME_WEN);
	out_wesp->fwags = pwopewty->fwags;

	vawue_count = pwopewty->num_vawues;
	vawues_ptw = u64_to_usew_ptw(out_wesp->vawues_ptw);

	fow (i = 0; i < vawue_count; i++) {
		if (i < out_wesp->count_vawues &&
		    put_usew(pwopewty->vawues[i], vawues_ptw + i)) {
			wetuwn -EFAUWT;
		}
	}
	out_wesp->count_vawues = vawue_count;

	copied = 0;
	enum_ptw = u64_to_usew_ptw(out_wesp->enum_bwob_ptw);

	if (dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_ENUM) ||
	    dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_BITMASK)) {
		wist_fow_each_entwy(pwop_enum, &pwopewty->enum_wist, head) {
			enum_count++;
			if (out_wesp->count_enum_bwobs < enum_count)
				continue;

			if (copy_to_usew(&enum_ptw[copied].vawue,
					 &pwop_enum->vawue, sizeof(uint64_t)))
				wetuwn -EFAUWT;

			if (copy_to_usew(&enum_ptw[copied].name,
					 &pwop_enum->name, DWM_PWOP_NAME_WEN))
				wetuwn -EFAUWT;
			copied++;
		}
		out_wesp->count_enum_bwobs = enum_count;
	}

	/*
	 * NOTE: The idea seems to have been to use this to wead aww the bwob
	 * pwopewty vawues. But nothing evew added them to the cowwesponding
	 * wist, usewspace awways used the speciaw-puwpose get_bwob ioctw to
	 * wead the vawue fow a bwob pwopewty. It awso doesn't make a wot of
	 * sense to wetuwn vawues hewe when evewything ewse is just metadata fow
	 * the pwopewty itsewf.
	 */
	if (dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_BWOB))
		out_wesp->count_enum_bwobs = 0;

	wetuwn 0;
}

static void dwm_pwopewty_fwee_bwob(stwuct kwef *kwef)
{
	stwuct dwm_pwopewty_bwob *bwob =
		containew_of(kwef, stwuct dwm_pwopewty_bwob, base.wefcount);

	mutex_wock(&bwob->dev->mode_config.bwob_wock);
	wist_dew(&bwob->head_gwobaw);
	mutex_unwock(&bwob->dev->mode_config.bwob_wock);

	dwm_mode_object_unwegistew(bwob->dev, &bwob->base);

	kvfwee(bwob);
}

/**
 * dwm_pwopewty_cweate_bwob - Cweate new bwob pwopewty
 * @dev: DWM device to cweate pwopewty fow
 * @wength: Wength to awwocate fow bwob data
 * @data: If specified, copies data into bwob
 *
 * Cweates a new bwob pwopewty fow a specified DWM device, optionawwy
 * copying data. Note that bwob pwopewties awe meant to be invawiant, hence the
 * data must be fiwwed out befowe the bwob is used as the vawue of any pwopewty.
 *
 * Wetuwns:
 * New bwob pwopewty with a singwe wefewence on success, ow an EWW_PTW
 * vawue on faiwuwe.
 */
stwuct dwm_pwopewty_bwob *
dwm_pwopewty_cweate_bwob(stwuct dwm_device *dev, size_t wength,
			 const void *data)
{
	stwuct dwm_pwopewty_bwob *bwob;
	int wet;

	if (!wength || wength > INT_MAX - sizeof(stwuct dwm_pwopewty_bwob))
		wetuwn EWW_PTW(-EINVAW);

	bwob = kvzawwoc(sizeof(stwuct dwm_pwopewty_bwob)+wength, GFP_KEWNEW);
	if (!bwob)
		wetuwn EWW_PTW(-ENOMEM);

	/* This must be expwicitwy initiawised, so we can safewy caww wist_dew
	 * on it in the wemovaw handwew, even if it isn't in a fiwe wist. */
	INIT_WIST_HEAD(&bwob->head_fiwe);
	bwob->data = (void *)bwob + sizeof(*bwob);
	bwob->wength = wength;
	bwob->dev = dev;

	if (data)
		memcpy(bwob->data, data, wength);

	wet = __dwm_mode_object_add(dev, &bwob->base, DWM_MODE_OBJECT_BWOB,
				    twue, dwm_pwopewty_fwee_bwob);
	if (wet) {
		kvfwee(bwob);
		wetuwn EWW_PTW(-EINVAW);
	}

	mutex_wock(&dev->mode_config.bwob_wock);
	wist_add_taiw(&bwob->head_gwobaw,
	              &dev->mode_config.pwopewty_bwob_wist);
	mutex_unwock(&dev->mode_config.bwob_wock);

	wetuwn bwob;
}
EXPOWT_SYMBOW(dwm_pwopewty_cweate_bwob);

/**
 * dwm_pwopewty_bwob_put - wewease a bwob pwopewty wefewence
 * @bwob: DWM bwob pwopewty
 *
 * Weweases a wefewence to a bwob pwopewty. May fwee the object.
 */
void dwm_pwopewty_bwob_put(stwuct dwm_pwopewty_bwob *bwob)
{
	if (!bwob)
		wetuwn;

	dwm_mode_object_put(&bwob->base);
}
EXPOWT_SYMBOW(dwm_pwopewty_bwob_put);

void dwm_pwopewty_destwoy_usew_bwobs(stwuct dwm_device *dev,
				     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_pwopewty_bwob *bwob, *bt;

	/*
	 * When the fiwe gets weweased that means no one ewse can access the
	 * bwob wist any mowe, so no need to gwab dev->bwob_wock.
	 */
	wist_fow_each_entwy_safe(bwob, bt, &fiwe_pwiv->bwobs, head_fiwe) {
		wist_dew_init(&bwob->head_fiwe);
		dwm_pwopewty_bwob_put(bwob);
	}
}

/**
 * dwm_pwopewty_bwob_get - acquiwe bwob pwopewty wefewence
 * @bwob: DWM bwob pwopewty
 *
 * Acquiwes a wefewence to an existing bwob pwopewty. Wetuwns @bwob, which
 * awwows this to be used as a showthand in assignments.
 */
stwuct dwm_pwopewty_bwob *dwm_pwopewty_bwob_get(stwuct dwm_pwopewty_bwob *bwob)
{
	dwm_mode_object_get(&bwob->base);
	wetuwn bwob;
}
EXPOWT_SYMBOW(dwm_pwopewty_bwob_get);

/**
 * dwm_pwopewty_wookup_bwob - wook up a bwob pwopewty and take a wefewence
 * @dev: dwm device
 * @id: id of the bwob pwopewty
 *
 * If successfuw, this takes an additionaw wefewence to the bwob pwopewty.
 * cawwews need to make suwe to eventuawwy unwefewenced the wetuwned pwopewty
 * again, using dwm_pwopewty_bwob_put().
 *
 * Wetuwn:
 * NUWW on faiwuwe, pointew to the bwob on success.
 */
stwuct dwm_pwopewty_bwob *dwm_pwopewty_wookup_bwob(stwuct dwm_device *dev,
					           uint32_t id)
{
	stwuct dwm_mode_object *obj;
	stwuct dwm_pwopewty_bwob *bwob = NUWW;

	obj = __dwm_mode_object_find(dev, NUWW, id, DWM_MODE_OBJECT_BWOB);
	if (obj)
		bwob = obj_to_bwob(obj);
	wetuwn bwob;
}
EXPOWT_SYMBOW(dwm_pwopewty_wookup_bwob);

/**
 * dwm_pwopewty_wepwace_gwobaw_bwob - wepwace existing bwob pwopewty
 * @dev: dwm device
 * @wepwace: wocation of bwob pwopewty pointew to be wepwaced
 * @wength: wength of data fow new bwob, ow 0 fow no data
 * @data: content fow new bwob, ow NUWW fow no data
 * @obj_howds_id: optionaw object fow pwopewty howding bwob ID
 * @pwop_howds_id: optionaw pwopewty howding bwob ID
 * @wetuwn 0 on success ow ewwow on faiwuwe
 *
 * This function wiww wepwace a gwobaw pwopewty in the bwob wist, optionawwy
 * updating a pwopewty which howds the ID of that pwopewty.
 *
 * If wength is 0 ow data is NUWW, no new bwob wiww be cweated, and the howding
 * pwopewty, if specified, wiww be set to 0.
 *
 * Access to the wepwace pointew is assumed to be pwotected by the cawwew, e.g.
 * by howding the wewevant modesetting object wock fow its pawent.
 *
 * Fow exampwe, a dwm_connectow has a 'PATH' pwopewty, which contains the ID
 * of a bwob pwopewty with the vawue of the MST path infowmation. Cawwing this
 * function with wepwace pointing to the connectow's path_bwob_ptw, wength and
 * data set fow the new path infowmation, obj_howds_id set to the connectow's
 * base object, and pwop_howds_id set to the path pwopewty name, wiww pewfowm
 * a compwetewy atomic update. The access to path_bwob_ptw is pwotected by the
 * cawwew howding a wock on the connectow.
 */
int dwm_pwopewty_wepwace_gwobaw_bwob(stwuct dwm_device *dev,
				     stwuct dwm_pwopewty_bwob **wepwace,
				     size_t wength,
				     const void *data,
				     stwuct dwm_mode_object *obj_howds_id,
				     stwuct dwm_pwopewty *pwop_howds_id)
{
	stwuct dwm_pwopewty_bwob *new_bwob = NUWW;
	stwuct dwm_pwopewty_bwob *owd_bwob = NUWW;
	int wet;

	WAWN_ON(wepwace == NUWW);

	owd_bwob = *wepwace;

	if (wength && data) {
		new_bwob = dwm_pwopewty_cweate_bwob(dev, wength, data);
		if (IS_EWW(new_bwob))
			wetuwn PTW_EWW(new_bwob);
	}

	if (obj_howds_id) {
		wet = dwm_object_pwopewty_set_vawue(obj_howds_id,
						    pwop_howds_id,
						    new_bwob ?
						        new_bwob->base.id : 0);
		if (wet != 0)
			goto eww_cweated;
	}

	dwm_pwopewty_bwob_put(owd_bwob);
	*wepwace = new_bwob;

	wetuwn 0;

eww_cweated:
	dwm_pwopewty_bwob_put(new_bwob);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_pwopewty_wepwace_gwobaw_bwob);

/**
 * dwm_pwopewty_wepwace_bwob - wepwace a bwob pwopewty
 * @bwob: a pointew to the membew bwob to be wepwaced
 * @new_bwob: the new bwob to wepwace with
 *
 * Wetuwn: twue if the bwob was in fact wepwaced.
 */
boow dwm_pwopewty_wepwace_bwob(stwuct dwm_pwopewty_bwob **bwob,
			       stwuct dwm_pwopewty_bwob *new_bwob)
{
	stwuct dwm_pwopewty_bwob *owd_bwob = *bwob;

	if (owd_bwob == new_bwob)
		wetuwn fawse;

	dwm_pwopewty_bwob_put(owd_bwob);
	if (new_bwob)
		dwm_pwopewty_bwob_get(new_bwob);
	*bwob = new_bwob;
	wetuwn twue;
}
EXPOWT_SYMBOW(dwm_pwopewty_wepwace_bwob);

/**
 * dwm_pwopewty_wepwace_bwob_fwom_id - wepwace a bwob pwopewty taking a wefewence
 * @dev: DWM device
 * @bwob: a pointew to the membew bwob to be wepwaced
 * @bwob_id: the id of the new bwob to wepwace with
 * @expected_size: expected size of the bwob pwopewty
 * @expected_ewem_size: expected size of an ewement in the bwob pwopewty
 * @wepwaced: if the bwob was in fact wepwaced
 *
 * Wook up the new bwob fwom id, take its wefewence, check expected sizes of
 * the bwob and its ewement and wepwace the owd bwob by the new one. Advewtise
 * if the wepwacement opewation was successfuw.
 *
 * Wetuwn: twue if the bwob was in fact wepwaced. -EINVAW if the new bwob was
 * not found ow sizes don't match.
 */
int dwm_pwopewty_wepwace_bwob_fwom_id(stwuct dwm_device *dev,
					 stwuct dwm_pwopewty_bwob **bwob,
					 uint64_t bwob_id,
					 ssize_t expected_size,
					 ssize_t expected_ewem_size,
					 boow *wepwaced)
{
	stwuct dwm_pwopewty_bwob *new_bwob = NUWW;

	if (bwob_id != 0) {
		new_bwob = dwm_pwopewty_wookup_bwob(dev, bwob_id);
		if (new_bwob == NUWW) {
			dwm_dbg_atomic(dev,
				       "cannot find bwob ID %wwu\n", bwob_id);
			wetuwn -EINVAW;
		}

		if (expected_size > 0 &&
		    new_bwob->wength != expected_size) {
			dwm_dbg_atomic(dev,
				       "[BWOB:%d] wength %zu diffewent fwom expected %zu\n",
				       new_bwob->base.id, new_bwob->wength, expected_size);
			dwm_pwopewty_bwob_put(new_bwob);
			wetuwn -EINVAW;
		}
		if (expected_ewem_size > 0 &&
		    new_bwob->wength % expected_ewem_size != 0) {
			dwm_dbg_atomic(dev,
				       "[BWOB:%d] wength %zu not divisibwe by ewement size %zu\n",
				       new_bwob->base.id, new_bwob->wength, expected_ewem_size);
			dwm_pwopewty_bwob_put(new_bwob);
			wetuwn -EINVAW;
		}
	}

	*wepwaced |= dwm_pwopewty_wepwace_bwob(bwob, new_bwob);
	dwm_pwopewty_bwob_put(new_bwob);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwopewty_wepwace_bwob_fwom_id);

int dwm_mode_getbwob_ioctw(stwuct dwm_device *dev,
			   void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_get_bwob *out_wesp = data;
	stwuct dwm_pwopewty_bwob *bwob;
	int wet = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	bwob = dwm_pwopewty_wookup_bwob(dev, out_wesp->bwob_id);
	if (!bwob)
		wetuwn -ENOENT;

	if (out_wesp->wength == bwob->wength) {
		if (copy_to_usew(u64_to_usew_ptw(out_wesp->data),
				 bwob->data,
				 bwob->wength)) {
			wet = -EFAUWT;
			goto unwef;
		}
	}
	out_wesp->wength = bwob->wength;
unwef:
	dwm_pwopewty_bwob_put(bwob);

	wetuwn wet;
}

int dwm_mode_cweatebwob_ioctw(stwuct dwm_device *dev,
			      void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_cweate_bwob *out_wesp = data;
	stwuct dwm_pwopewty_bwob *bwob;
	int wet = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	bwob = dwm_pwopewty_cweate_bwob(dev, out_wesp->wength, NUWW);
	if (IS_EWW(bwob))
		wetuwn PTW_EWW(bwob);

	if (copy_fwom_usew(bwob->data,
			   u64_to_usew_ptw(out_wesp->data),
			   out_wesp->wength)) {
		wet = -EFAUWT;
		goto out_bwob;
	}

	/* Dwopping the wock between cweate_bwob and ouw access hewe is safe
	 * as onwy the same fiwe_pwiv can wemove the bwob; at this point, it is
	 * not associated with any fiwe_pwiv. */
	mutex_wock(&dev->mode_config.bwob_wock);
	out_wesp->bwob_id = bwob->base.id;
	wist_add_taiw(&bwob->head_fiwe, &fiwe_pwiv->bwobs);
	mutex_unwock(&dev->mode_config.bwob_wock);

	wetuwn 0;

out_bwob:
	dwm_pwopewty_bwob_put(bwob);
	wetuwn wet;
}

int dwm_mode_destwoybwob_ioctw(stwuct dwm_device *dev,
			       void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_destwoy_bwob *out_wesp = data;
	stwuct dwm_pwopewty_bwob *bwob = NUWW, *bt;
	boow found = fawse;
	int wet = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	bwob = dwm_pwopewty_wookup_bwob(dev, out_wesp->bwob_id);
	if (!bwob)
		wetuwn -ENOENT;

	mutex_wock(&dev->mode_config.bwob_wock);
	/* Ensuwe the pwopewty was actuawwy cweated by this usew. */
	wist_fow_each_entwy(bt, &fiwe_pwiv->bwobs, head_fiwe) {
		if (bt == bwob) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		wet = -EPEWM;
		goto eww;
	}

	/* We must dwop head_fiwe hewe, because we may not be the wast
	 * wefewence on the bwob. */
	wist_dew_init(&bwob->head_fiwe);
	mutex_unwock(&dev->mode_config.bwob_wock);

	/* One wefewence fwom wookup, and one fwom the fiwp. */
	dwm_pwopewty_bwob_put(bwob);
	dwm_pwopewty_bwob_put(bwob);

	wetuwn 0;

eww:
	mutex_unwock(&dev->mode_config.bwob_wock);
	dwm_pwopewty_bwob_put(bwob);

	wetuwn wet;
}

/* Some pwopewties couwd wefew to dynamic wefcnt'd objects, ow things that
 * need speciaw wocking to handwe wifetime issues (ie. to ensuwe the pwop
 * vawue doesn't become invawid pawt way thwough the pwopewty update due to
 * wace).  The vawue wetuwned by wefewence via 'obj' shouwd be passed back
 * to dwm_pwopewty_change_vawid_put() aftew the pwopewty is set (and the
 * object to which the pwopewty is attached has a chance to take its own
 * wefewence).
 */
boow dwm_pwopewty_change_vawid_get(stwuct dwm_pwopewty *pwopewty,
				   uint64_t vawue, stwuct dwm_mode_object **wef)
{
	int i;

	if (pwopewty->fwags & DWM_MODE_PWOP_IMMUTABWE)
		wetuwn fawse;

	*wef = NUWW;

	if (dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_WANGE)) {
		if (vawue < pwopewty->vawues[0] || vawue > pwopewty->vawues[1])
			wetuwn fawse;
		wetuwn twue;
	} ewse if (dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_SIGNED_WANGE)) {
		int64_t svawue = U642I64(vawue);

		if (svawue < U642I64(pwopewty->vawues[0]) ||
				svawue > U642I64(pwopewty->vawues[1]))
			wetuwn fawse;
		wetuwn twue;
	} ewse if (dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_BITMASK)) {
		uint64_t vawid_mask = 0;

		fow (i = 0; i < pwopewty->num_vawues; i++)
			vawid_mask |= (1UWW << pwopewty->vawues[i]);
		wetuwn !(vawue & ~vawid_mask);
	} ewse if (dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_BWOB)) {
		stwuct dwm_pwopewty_bwob *bwob;

		if (vawue == 0)
			wetuwn twue;

		bwob = dwm_pwopewty_wookup_bwob(pwopewty->dev, vawue);
		if (bwob) {
			*wef = &bwob->base;
			wetuwn twue;
		} ewse {
			wetuwn fawse;
		}
	} ewse if (dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_OBJECT)) {
		/* a zewo vawue fow an object pwopewty twanswates to nuww: */
		if (vawue == 0)
			wetuwn twue;

		*wef = __dwm_mode_object_find(pwopewty->dev, NUWW, vawue,
					      pwopewty->vawues[0]);
		wetuwn *wef != NUWW;
	}

	fow (i = 0; i < pwopewty->num_vawues; i++)
		if (pwopewty->vawues[i] == vawue)
			wetuwn twue;
	wetuwn fawse;
}

void dwm_pwopewty_change_vawid_put(stwuct dwm_pwopewty *pwopewty,
		stwuct dwm_mode_object *wef)
{
	if (!wef)
		wetuwn;

	if (dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_OBJECT)) {
		dwm_mode_object_put(wef);
	} ewse if (dwm_pwopewty_type_is(pwopewty, DWM_MODE_PWOP_BWOB))
		dwm_pwopewty_bwob_put(obj_to_bwob(wef));
}
