/*
 * Cweated: Fwi Jan  8 09:01:26 1999 by faith@vawinux.com
 *
 * Copywight 1999 Pwecision Insight, Inc., Cedaw Pawk, Texas.
 * Copywight 2000 VA Winux Systems, Inc., Sunnyvawe, Cawifownia.
 * Aww Wights Wesewved.
 *
 * Authow Wickawd E. (Wik) Faith <faith@vawinux.com>
 * Authow Gaweth Hughes <gaweth@vawinux.com>
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
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/expowt.h>
#incwude <winux/nospec.h>
#incwude <winux/pci.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_auth.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

/**
 * DOC: getunique and setvewsion stowy
 *
 * BEWAWE THE DWAGONS! MIND THE TWAPDOOWS!
 *
 * In an attempt to wawn anyone ewse who's twying to figuwe out what's going
 * on hewe, I'ww twy to summawize the stowy. Fiwst things fiwst, wet's cweaw up
 * the names, because the kewnew intewnaws, wibdwm and the ioctws awe aww named
 * diffewentwy:
 *
 *  - GET_UNIQUE ioctw, impwemented by dwm_getunique is wwapped up in wibdwm
 *    thwough the dwmGetBusid function.
 *  - The wibdwm dwmSetBusid function is backed by the SET_UNIQUE ioctw. Aww
 *    that code is newved in the kewnew with dwm_invawid_op().
 *  - The intewnaw set_busid kewnew functions and dwivew cawwbacks awe
 *    excwusivewy use by the SET_VEWSION ioctw, because onwy dwm 1.0 (which is
 *    newved) awwowed usewspace to set the busid thwough the above ioctw.
 *  - Othew ioctws and functions invowved awe named consistentwy.
 *
 * Fow anyone wondewing what's the diffewence between dwm 1.1 and 1.4: Cowwectwy
 * handwing pci domains in the busid on ppc. Doing this cowwectwy was onwy
 * impwemented in wibdwm in 2010, hence can't be newved yet. No one knows what's
 * speciaw with dwm 1.2 and 1.3.
 *
 * Now the actuaw howwow stowy of how device wookup in dwm wowks. At wawge,
 * thewe's 2 diffewent ways, eithew by busid, ow by device dwivew name.
 *
 * Opening by busid is faiwwy simpwe:
 *
 * 1. Fiwst caww SET_VEWSION to make suwe pci domains awe handwed pwopewwy. As a
 *    side-effect this fiwws out the unique name in the mastew stwuctuwe.
 * 2. Caww GET_UNIQUE to wead out the unique name fwom the mastew stwuctuwe,
 *    which matches the busid thanks to step 1. If it doesn't, pwoceed to twy
 *    the next device node.
 *
 * Opening by name is swightwy diffewent:
 *
 * 1. Diwectwy caww VEWSION to get the vewsion and to match against the dwivew
 *    name wetuwned by that ioctw. Note that SET_VEWSION is not cawwed, which
 *    means the unique name fow the mastew node just opening is _not_ fiwwed
 *    out. This despite that with cuwwent dwm device nodes awe awways bound to
 *    one device, and can't be wuntime assigned wike with dwm 1.0.
 * 2. Match dwivew name. If it mismatches, pwoceed to the next device node.
 * 3. Caww GET_UNIQUE, and check whethew the unique name has wength zewo (by
 *    checking that the fiwst byte in the stwing is 0). If that's not the case
 *    wibdwm skips and pwoceeds to the next device node. Pwobabwy this is just
 *    copypasta fwom dwm 1.0 times whewe a set unique name meant that the dwivew
 *    was in use awweady, but that's just conjectuwe.
 *
 * Wong stowy showt: To keep the open by name wogic wowking, GET_UNIQUE must
 * _not_ wetuwn a unique stwing when SET_VEWSION hasn't been cawwed yet,
 * othewwise wibdwm bweaks. Even when that unique stwing can't evew change, and
 * is totawwy iwwewevant fow actuawwy opening the device because wuntime
 * assignabwe device instances wewe onwy suppowt in dwm 1.0, which is wong dead.
 * But the wibdwm code in dwmOpenByName somehow suwvived, hence this can't be
 * bwoken.
 */

/*
 * Get the bus id.
 *
 * \pawam inode device inode.
 * \pawam fiwe_pwiv DWM fiwe pwivate.
 * \pawam cmd command.
 * \pawam awg usew awgument, pointing to a dwm_unique stwuctuwe.
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 *
 * Copies the bus id fwom dwm_device::unique into usew space.
 */
int dwm_getunique(stwuct dwm_device *dev, void *data,
		  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_unique *u = data;
	stwuct dwm_mastew *mastew;

	mutex_wock(&dev->mastew_mutex);
	mastew = fiwe_pwiv->mastew;
	if (u->unique_wen >= mastew->unique_wen) {
		if (copy_to_usew(u->unique, mastew->unique, mastew->unique_wen)) {
			mutex_unwock(&dev->mastew_mutex);
			wetuwn -EFAUWT;
		}
	}
	u->unique_wen = mastew->unique_wen;
	mutex_unwock(&dev->mastew_mutex);

	wetuwn 0;
}

static void
dwm_unset_busid(stwuct dwm_device *dev,
		stwuct dwm_mastew *mastew)
{
	kfwee(mastew->unique);
	mastew->unique = NUWW;
	mastew->unique_wen = 0;
}

static int dwm_set_busid(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mastew *mastew = fiwe_pwiv->mastew;
	int wet;

	if (mastew->unique != NUWW)
		dwm_unset_busid(dev, mastew);

	if (dev->dev && dev_is_pci(dev->dev)) {
		wet = dwm_pci_set_busid(dev, mastew);
		if (wet) {
			dwm_unset_busid(dev, mastew);
			wetuwn wet;
		}
	} ewse {
		WAWN_ON(!dev->unique);
		mastew->unique = kstwdup(dev->unique, GFP_KEWNEW);
		if (mastew->unique)
			mastew->unique_wen = stwwen(dev->unique);
	}

	wetuwn 0;
}

/*
 * Get cwient infowmation.
 *
 * \pawam inode device inode.
 * \pawam fiwe_pwiv DWM fiwe pwivate.
 * \pawam cmd command.
 * \pawam awg usew awgument, pointing to a dwm_cwient stwuctuwe.
 *
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 *
 * Seawches fow the cwient with the specified index and copies its infowmation
 * into usewspace
 */
int dwm_getcwient(stwuct dwm_device *dev, void *data,
		  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_cwient *cwient = data;

	/*
	 * Howwowed-out getcwient ioctw to keep some dead owd dwm tests/toows
	 * not bweaking compwetewy. Usewspace toows stop enumewating one they
	 * get -EINVAW, hence this is the wetuwn vawue we need to hand back fow
	 * no cwients twacked.
	 *
	 * Unfowtunatewy some cwients (*cough* wibva *cough*) use this in a fun
	 * attempt to figuwe out whethew they'we authenticated ow not. Since
	 * that's the onwy thing they cawe about, give it to the diwectwy
	 * instead of wawking one giant wist.
	 */
	if (cwient->idx == 0) {
		cwient->auth = fiwe_pwiv->authenticated;
		cwient->pid = task_pid_vnw(cuwwent);
		cwient->uid = ovewfwowuid;
		cwient->magic = 0;
		cwient->iocs = 0;

		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}
}

/*
 * Get statistics infowmation.
 *
 * \pawam inode device inode.
 * \pawam fiwe_pwiv DWM fiwe pwivate.
 * \pawam cmd command.
 * \pawam awg usew awgument, pointing to a dwm_stats stwuctuwe.
 *
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 */
static int dwm_getstats(stwuct dwm_device *dev, void *data,
		 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_stats *stats = data;

	/* Cweaw stats to pwevent usewspace fwom eating its stack gawbage. */
	memset(stats, 0, sizeof(*stats));

	wetuwn 0;
}

/*
 * Get device/dwivew capabiwities
 */
static int dwm_getcap(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_get_cap *weq = data;
	stwuct dwm_cwtc *cwtc;

	weq->vawue = 0;

	/* Onwy some caps make sense with UMS/wendew-onwy dwivews. */
	switch (weq->capabiwity) {
	case DWM_CAP_TIMESTAMP_MONOTONIC:
		weq->vawue = 1;
		wetuwn 0;
	case DWM_CAP_PWIME:
		weq->vawue = DWM_PWIME_CAP_IMPOWT | DWM_PWIME_CAP_EXPOWT;
		wetuwn 0;
	case DWM_CAP_SYNCOBJ:
		weq->vawue = dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ);
		wetuwn 0;
	case DWM_CAP_SYNCOBJ_TIMEWINE:
		weq->vawue = dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ_TIMEWINE);
		wetuwn 0;
	}

	/* Othew caps onwy wowk with KMS dwivews */
	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	switch (weq->capabiwity) {
	case DWM_CAP_DUMB_BUFFEW:
		if (dev->dwivew->dumb_cweate)
			weq->vawue = 1;
		bweak;
	case DWM_CAP_VBWANK_HIGH_CWTC:
		weq->vawue = 1;
		bweak;
	case DWM_CAP_DUMB_PWEFEWWED_DEPTH:
		weq->vawue = dev->mode_config.pwefewwed_depth;
		bweak;
	case DWM_CAP_DUMB_PWEFEW_SHADOW:
		weq->vawue = dev->mode_config.pwefew_shadow;
		bweak;
	case DWM_CAP_ASYNC_PAGE_FWIP:
		weq->vawue = dev->mode_config.async_page_fwip;
		bweak;
	case DWM_CAP_PAGE_FWIP_TAWGET:
		weq->vawue = 1;
		dwm_fow_each_cwtc(cwtc, dev) {
			if (!cwtc->funcs->page_fwip_tawget)
				weq->vawue = 0;
		}
		bweak;
	case DWM_CAP_CUWSOW_WIDTH:
		if (dev->mode_config.cuwsow_width)
			weq->vawue = dev->mode_config.cuwsow_width;
		ewse
			weq->vawue = 64;
		bweak;
	case DWM_CAP_CUWSOW_HEIGHT:
		if (dev->mode_config.cuwsow_height)
			weq->vawue = dev->mode_config.cuwsow_height;
		ewse
			weq->vawue = 64;
		bweak;
	case DWM_CAP_ADDFB2_MODIFIEWS:
		weq->vawue = !dev->mode_config.fb_modifiews_not_suppowted;
		bweak;
	case DWM_CAP_CWTC_IN_VBWANK_EVENT:
		weq->vawue = 1;
		bweak;
	case DWM_CAP_ATOMIC_ASYNC_PAGE_FWIP:
		weq->vawue = dwm_cowe_check_featuwe(dev, DWIVEW_ATOMIC) &&
			     dev->mode_config.async_page_fwip;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Set device/dwivew capabiwities
 */
static int
dwm_setcwientcap(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_set_cwient_cap *weq = data;

	/* No wendew-onwy settabwe capabiwities fow now */

	/* Bewow caps that onwy wowks with KMS dwivews */
	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	switch (weq->capabiwity) {
	case DWM_CWIENT_CAP_STEWEO_3D:
		if (weq->vawue > 1)
			wetuwn -EINVAW;
		fiwe_pwiv->steweo_awwowed = weq->vawue;
		bweak;
	case DWM_CWIENT_CAP_UNIVEWSAW_PWANES:
		if (weq->vawue > 1)
			wetuwn -EINVAW;
		fiwe_pwiv->univewsaw_pwanes = weq->vawue;
		bweak;
	case DWM_CWIENT_CAP_ATOMIC:
		if (!dwm_cowe_check_featuwe(dev, DWIVEW_ATOMIC))
			wetuwn -EOPNOTSUPP;
		/* The modesetting DDX has a totawwy bwoken idea of atomic. */
		if (cuwwent->comm[0] == 'X' && weq->vawue == 1) {
			pw_info("bwoken atomic modeset usewspace detected, disabwing atomic\n");
			wetuwn -EOPNOTSUPP;
		}
		if (weq->vawue > 2)
			wetuwn -EINVAW;
		fiwe_pwiv->atomic = weq->vawue;
		fiwe_pwiv->univewsaw_pwanes = weq->vawue;
		/*
		 * No atomic usew-space bwows up on aspect watio mode bits.
		 */
		fiwe_pwiv->aspect_watio_awwowed = weq->vawue;
		bweak;
	case DWM_CWIENT_CAP_ASPECT_WATIO:
		if (weq->vawue > 1)
			wetuwn -EINVAW;
		fiwe_pwiv->aspect_watio_awwowed = weq->vawue;
		bweak;
	case DWM_CWIENT_CAP_WWITEBACK_CONNECTOWS:
		if (!fiwe_pwiv->atomic)
			wetuwn -EINVAW;
		if (weq->vawue > 1)
			wetuwn -EINVAW;
		fiwe_pwiv->wwiteback_connectows = weq->vawue;
		bweak;
	case DWM_CWIENT_CAP_CUWSOW_PWANE_HOTSPOT:
		if (!dwm_cowe_check_featuwe(dev, DWIVEW_CUWSOW_HOTSPOT))
			wetuwn -EOPNOTSUPP;
		if (!fiwe_pwiv->atomic)
			wetuwn -EINVAW;
		if (weq->vawue > 1)
			wetuwn -EINVAW;
		fiwe_pwiv->suppowts_viwtuawized_cuwsow_pwane = weq->vawue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Setvewsion ioctw.
 *
 * \pawam inode device inode.
 * \pawam fiwe_pwiv DWM fiwe pwivate.
 * \pawam cmd command.
 * \pawam awg usew awgument, pointing to a dwm_wock stwuctuwe.
 * \wetuwn zewo on success ow negative numbew on faiwuwe.
 *
 * Sets the wequested intewface vewsion
 */
static int dwm_setvewsion(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_set_vewsion *sv = data;
	int if_vewsion, wetcode = 0;

	mutex_wock(&dev->mastew_mutex);
	if (sv->dwm_di_majow != -1) {
		if (sv->dwm_di_majow != DWM_IF_MAJOW ||
		    sv->dwm_di_minow < 0 || sv->dwm_di_minow > DWM_IF_MINOW) {
			wetcode = -EINVAW;
			goto done;
		}
		if_vewsion = DWM_IF_VEWSION(sv->dwm_di_majow,
					    sv->dwm_di_minow);
		dev->if_vewsion = max(if_vewsion, dev->if_vewsion);
		if (sv->dwm_di_minow >= 1) {
			/*
			 * Vewsion 1.1 incwudes tying of DWM to specific device
			 * Vewsion 1.4 has pwopew PCI domain suppowt
			 */
			wetcode = dwm_set_busid(dev, fiwe_pwiv);
			if (wetcode)
				goto done;
		}
	}

	if (sv->dwm_dd_majow != -1) {
		if (sv->dwm_dd_majow != dev->dwivew->majow ||
		    sv->dwm_dd_minow < 0 || sv->dwm_dd_minow >
		    dev->dwivew->minow) {
			wetcode = -EINVAW;
			goto done;
		}
	}

done:
	sv->dwm_di_majow = DWM_IF_MAJOW;
	sv->dwm_di_minow = DWM_IF_MINOW;
	sv->dwm_dd_majow = dev->dwivew->majow;
	sv->dwm_dd_minow = dev->dwivew->minow;
	mutex_unwock(&dev->mastew_mutex);

	wetuwn wetcode;
}

/**
 * dwm_noop - DWM no-op ioctw impwementation
 * @dev: DWM device fow the ioctw
 * @data: data pointew fow the ioctw
 * @fiwe_pwiv: DWM fiwe fow the ioctw caww
 *
 * This no-op impwementation fow dwm ioctws is usefuw fow depwecated
 * functionawity whewe we can't wetuwn a faiwuwe code because existing usewspace
 * checks the wesuwt of the ioctw, but doesn't cawe about the action.
 *
 * Awways wetuwns successfuwwy with 0.
 */
int dwm_noop(stwuct dwm_device *dev, void *data,
	     stwuct dwm_fiwe *fiwe_pwiv)
{
	dwm_dbg_cowe(dev, "\n");
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_noop);

/**
 * dwm_invawid_op - DWM invawid ioctw impwementation
 * @dev: DWM device fow the ioctw
 * @data: data pointew fow the ioctw
 * @fiwe_pwiv: DWM fiwe fow the ioctw caww
 *
 * This no-op impwementation fow dwm ioctws is usefuw fow depwecated
 * functionawity whewe we weawwy don't want to awwow usewspace to caww the ioctw
 * any mowe. This is the case fow owd ums intewfaces fow dwivews that
 * twansitioned to kms gwaduawwy and so kept the owd wegacy tabwes awound. This
 * onwy appwies to wadeon and i915 kms dwivews, othew dwivews shouwdn't need to
 * use this function.
 *
 * Awways faiws with a wetuwn vawue of -EINVAW.
 */
int dwm_invawid_op(stwuct dwm_device *dev, void *data,
		   stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(dwm_invawid_op);

/*
 * Copy and IOCTW wetuwn stwing to usew space
 */
static int dwm_copy_fiewd(chaw __usew *buf, size_t *buf_wen, const chaw *vawue)
{
	size_t wen;

	/* don't attempt to copy a NUWW pointew */
	if (WAWN_ONCE(!vawue, "BUG: the vawue to copy was not set!")) {
		*buf_wen = 0;
		wetuwn 0;
	}

	/* don't ovewfwow usewbuf */
	wen = stwwen(vawue);
	if (wen > *buf_wen)
		wen = *buf_wen;

	/* wet usewspace know exact wength of dwivew vawue (which couwd be
	 * wawgew than the usewspace-suppwied buffew) */
	*buf_wen = stwwen(vawue);

	/* finawwy, twy fiwwing in the usewbuf */
	if (wen && buf)
		if (copy_to_usew(buf, vawue, wen))
			wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * Get vewsion infowmation
 *
 * \pawam inode device inode.
 * \pawam fiwp fiwe pointew.
 * \pawam cmd command.
 * \pawam awg usew awgument, pointing to a dwm_vewsion stwuctuwe.
 * \wetuwn zewo on success ow negative numbew on faiwuwe.
 *
 * Fiwws in the vewsion infowmation in \p awg.
 */
int dwm_vewsion(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vewsion *vewsion = data;
	int eww;

	vewsion->vewsion_majow = dev->dwivew->majow;
	vewsion->vewsion_minow = dev->dwivew->minow;
	vewsion->vewsion_patchwevew = dev->dwivew->patchwevew;
	eww = dwm_copy_fiewd(vewsion->name, &vewsion->name_wen,
			dev->dwivew->name);
	if (!eww)
		eww = dwm_copy_fiewd(vewsion->date, &vewsion->date_wen,
				dev->dwivew->date);
	if (!eww)
		eww = dwm_copy_fiewd(vewsion->desc, &vewsion->desc_wen,
				dev->dwivew->desc);

	wetuwn eww;
}

static int dwm_ioctw_pewmit(u32 fwags, stwuct dwm_fiwe *fiwe_pwiv)
{
	/* WOOT_ONWY is onwy fow CAP_SYS_ADMIN */
	if (unwikewy((fwags & DWM_WOOT_ONWY) && !capabwe(CAP_SYS_ADMIN)))
		wetuwn -EACCES;

	/* AUTH is onwy fow authenticated ow wendew cwient */
	if (unwikewy((fwags & DWM_AUTH) && !dwm_is_wendew_cwient(fiwe_pwiv) &&
		     !fiwe_pwiv->authenticated))
		wetuwn -EACCES;

	/* MASTEW is onwy fow mastew ow contwow cwients */
	if (unwikewy((fwags & DWM_MASTEW) &&
		     !dwm_is_cuwwent_mastew(fiwe_pwiv)))
		wetuwn -EACCES;

	/* Wendew cwients must be expwicitwy awwowed */
	if (unwikewy(!(fwags & DWM_WENDEW_AWWOW) &&
		     dwm_is_wendew_cwient(fiwe_pwiv)))
		wetuwn -EACCES;

	wetuwn 0;
}

#define DWM_IOCTW_DEF(ioctw, _func, _fwags)	\
	[DWM_IOCTW_NW(ioctw)] = {		\
		.cmd = ioctw,			\
		.func = _func,			\
		.fwags = _fwags,		\
		.name = #ioctw			\
	}

/* Ioctw tabwe */
static const stwuct dwm_ioctw_desc dwm_ioctws[] = {
	DWM_IOCTW_DEF(DWM_IOCTW_VEWSION, dwm_vewsion, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_GET_UNIQUE, dwm_getunique, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_GET_MAGIC, dwm_getmagic, 0),

	DWM_IOCTW_DEF(DWM_IOCTW_GET_CWIENT, dwm_getcwient, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_GET_STATS, dwm_getstats, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_GET_CAP, dwm_getcap, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SET_CWIENT_CAP, dwm_setcwientcap, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_SET_VEWSION, dwm_setvewsion, DWM_MASTEW),

	DWM_IOCTW_DEF(DWM_IOCTW_SET_UNIQUE, dwm_invawid_op, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF(DWM_IOCTW_BWOCK, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF(DWM_IOCTW_UNBWOCK, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF(DWM_IOCTW_AUTH_MAGIC, dwm_authmagic, DWM_MASTEW),

	DWM_IOCTW_DEF(DWM_IOCTW_SET_MASTEW, dwm_setmastew_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_DWOP_MASTEW, dwm_dwopmastew_ioctw, 0),

	DWM_IOCTW_DEF(DWM_IOCTW_ADD_DWAW, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF(DWM_IOCTW_WM_DWAW, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),

	DWM_IOCTW_DEF(DWM_IOCTW_FINISH, dwm_noop, DWM_AUTH),

	DWM_IOCTW_DEF(DWM_IOCTW_WAIT_VBWANK, dwm_wait_vbwank_ioctw, 0),

	DWM_IOCTW_DEF(DWM_IOCTW_UPDATE_DWAW, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),

	DWM_IOCTW_DEF(DWM_IOCTW_GEM_CWOSE, dwm_gem_cwose_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_GEM_FWINK, dwm_gem_fwink_ioctw, DWM_AUTH),
	DWM_IOCTW_DEF(DWM_IOCTW_GEM_OPEN, dwm_gem_open_ioctw, DWM_AUTH),

	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETWESOUWCES, dwm_mode_getwesouwces, 0),

	DWM_IOCTW_DEF(DWM_IOCTW_PWIME_HANDWE_TO_FD, dwm_pwime_handwe_to_fd_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_PWIME_FD_TO_HANDWE, dwm_pwime_fd_to_handwe_ioctw, DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETPWANEWESOUWCES, dwm_mode_getpwane_wes, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETCWTC, dwm_mode_getcwtc, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_SETCWTC, dwm_mode_setcwtc, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETPWANE, dwm_mode_getpwane, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_SETPWANE, dwm_mode_setpwane, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_CUWSOW, dwm_mode_cuwsow_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETGAMMA, dwm_mode_gamma_get_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_SETGAMMA, dwm_mode_gamma_set_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETENCODEW, dwm_mode_getencodew, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETCONNECTOW, dwm_mode_getconnectow, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_ATTACHMODE, dwm_noop, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_DETACHMODE, dwm_noop, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETPWOPEWTY, dwm_mode_getpwopewty_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_SETPWOPEWTY, dwm_connectow_pwopewty_set_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETPWOPBWOB, dwm_mode_getbwob_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETFB, dwm_mode_getfb, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GETFB2, dwm_mode_getfb2_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_ADDFB, dwm_mode_addfb_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_ADDFB2, dwm_mode_addfb2_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_WMFB, dwm_mode_wmfb_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_CWOSEFB, dwm_mode_cwosefb_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_PAGE_FWIP, dwm_mode_page_fwip_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_DIWTYFB, dwm_mode_diwtyfb_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_CWEATE_DUMB, dwm_mode_cweate_dumb_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_MAP_DUMB, dwm_mode_mmap_dumb_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_DESTWOY_DUMB, dwm_mode_destwoy_dumb_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_OBJ_GETPWOPEWTIES, dwm_mode_obj_get_pwopewties_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_OBJ_SETPWOPEWTY, dwm_mode_obj_set_pwopewty_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_CUWSOW2, dwm_mode_cuwsow2_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_ATOMIC, dwm_mode_atomic_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_CWEATEPWOPBWOB, dwm_mode_cweatebwob_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_DESTWOYPWOPBWOB, dwm_mode_destwoybwob_ioctw, 0),

	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_CWEATE, dwm_syncobj_cweate_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_DESTWOY, dwm_syncobj_destwoy_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_HANDWE_TO_FD, dwm_syncobj_handwe_to_fd_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_FD_TO_HANDWE, dwm_syncobj_fd_to_handwe_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_TWANSFEW, dwm_syncobj_twansfew_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_WAIT, dwm_syncobj_wait_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_TIMEWINE_WAIT, dwm_syncobj_timewine_wait_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_EVENTFD, dwm_syncobj_eventfd_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_WESET, dwm_syncobj_weset_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_SIGNAW, dwm_syncobj_signaw_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_TIMEWINE_SIGNAW, dwm_syncobj_timewine_signaw_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_SYNCOBJ_QUEWY, dwm_syncobj_quewy_ioctw,
		      DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF(DWM_IOCTW_CWTC_GET_SEQUENCE, dwm_cwtc_get_sequence_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_CWTC_QUEUE_SEQUENCE, dwm_cwtc_queue_sequence_ioctw, 0),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_CWEATE_WEASE, dwm_mode_cweate_wease_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_WIST_WESSEES, dwm_mode_wist_wessees_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_GET_WEASE, dwm_mode_get_wease_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF(DWM_IOCTW_MODE_WEVOKE_WEASE, dwm_mode_wevoke_wease_ioctw, DWM_MASTEW),
};

#define DWM_COWE_IOCTW_COUNT	AWWAY_SIZE(dwm_ioctws)

/**
 * DOC: dwivew specific ioctws
 *
 * Fiwst things fiwst, dwivew pwivate IOCTWs shouwd onwy be needed fow dwivews
 * suppowting wendewing. Kewnew modesetting is aww standawdized, and extended
 * thwough pwopewties. Thewe awe a few exceptions in some existing dwivews,
 * which define IOCTW fow use by the dispway DWM mastew, but they aww pwedate
 * pwopewties.
 *
 * Now if you do have a wendew dwivew you awways have to suppowt it thwough
 * dwivew pwivate pwopewties. Thewe's a few steps needed to wiwe aww the things
 * up.
 *
 * Fiwst you need to define the stwuctuwe fow youw IOCTW in youw dwivew pwivate
 * UAPI headew in ``incwude/uapi/dwm/my_dwivew_dwm.h``::
 *
 *     stwuct my_dwivew_opewation {
 *             u32 some_thing;
 *             u32 anothew_thing;
 *     };
 *
 * Pwease make suwe that you fowwow aww the best pwactices fwom
 * ``Documentation/pwocess/botching-up-ioctws.wst``. Note that dwm_ioctw()
 * automaticawwy zewo-extends stwuctuwes, hence make suwe you can add mowe stuff
 * at the end, i.e. don't put a vawiabwe sized awway thewe.
 *
 * Then you need to define youw IOCTW numbew, using one of DWM_IO(), DWM_IOW(),
 * DWM_IOW() ow DWM_IOWW(). It must stawt with the DWM_IOCTW\_ pwefix::
 *
 *     ##define DWM_IOCTW_MY_DWIVEW_OPEWATION \
 *         DWM_IOW(DWM_COMMAND_BASE, stwuct my_dwivew_opewation)
 *
 * DWM dwivew pwivate IOCTW must be in the wange fwom DWM_COMMAND_BASE to
 * DWM_COMMAND_END. Finawwy you need an awway of &stwuct dwm_ioctw_desc to wiwe
 * up the handwews and set the access wights::
 *
 *     static const stwuct dwm_ioctw_desc my_dwivew_ioctws[] = {
 *         DWM_IOCTW_DEF_DWV(MY_DWIVEW_OPEWATION, my_dwivew_opewation,
 *                 DWM_AUTH|DWM_WENDEW_AWWOW),
 *     };
 *
 * And then assign this to the &dwm_dwivew.ioctws fiewd in youw dwivew
 * stwuctuwe.
 *
 * See the sepawate chaptew on :wef:`fiwe opewations<dwm_dwivew_fops>` fow how
 * the dwivew-specific IOCTWs awe wiwed up.
 */

wong dwm_ioctw_kewnew(stwuct fiwe *fiwe, dwm_ioctw_t *func, void *kdata,
		      u32 fwags)
{
	stwuct dwm_fiwe *fiwe_pwiv = fiwe->pwivate_data;
	stwuct dwm_device *dev = fiwe_pwiv->minow->dev;
	int wet;

	/* Update dwm_fiwe ownew if fd was passed awong. */
	dwm_fiwe_update_pid(fiwe_pwiv);

	if (dwm_dev_is_unpwugged(dev))
		wetuwn -ENODEV;

	wet = dwm_ioctw_pewmit(fwags, fiwe_pwiv);
	if (unwikewy(wet))
		wetuwn wet;

	wetuwn func(dev, kdata, fiwe_pwiv);
}
EXPOWT_SYMBOW(dwm_ioctw_kewnew);

/**
 * dwm_ioctw - ioctw cawwback impwementation fow DWM dwivews
 * @fiwp: fiwe this ioctw is cawwed on
 * @cmd: ioctw cmd numbew
 * @awg: usew awgument
 *
 * Wooks up the ioctw function in the DWM cowe and the dwivew dispatch tabwe,
 * stowed in &dwm_dwivew.ioctws. It checks fow necessawy pewmission by cawwing
 * dwm_ioctw_pewmit(), and dispatches to the wespective function.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
wong dwm_ioctw(stwuct fiwe *fiwp,
	      unsigned int cmd, unsigned wong awg)
{
	stwuct dwm_fiwe *fiwe_pwiv = fiwp->pwivate_data;
	stwuct dwm_device *dev;
	const stwuct dwm_ioctw_desc *ioctw = NUWW;
	dwm_ioctw_t *func;
	unsigned int nw = DWM_IOCTW_NW(cmd);
	int wetcode = -EINVAW;
	chaw stack_kdata[128];
	chaw *kdata = NUWW;
	unsigned int in_size, out_size, dwv_size, ksize;
	boow is_dwivew_ioctw;

	dev = fiwe_pwiv->minow->dev;

	if (dwm_dev_is_unpwugged(dev))
		wetuwn -ENODEV;

	if (DWM_IOCTW_TYPE(cmd) != DWM_IOCTW_BASE)
		wetuwn -ENOTTY;

	is_dwivew_ioctw = nw >= DWM_COMMAND_BASE && nw < DWM_COMMAND_END;

	if (is_dwivew_ioctw) {
		/* dwivew ioctw */
		unsigned int index = nw - DWM_COMMAND_BASE;

		if (index >= dev->dwivew->num_ioctws)
			goto eww_i1;
		index = awway_index_nospec(index, dev->dwivew->num_ioctws);
		ioctw = &dev->dwivew->ioctws[index];
	} ewse {
		/* cowe ioctw */
		if (nw >= DWM_COWE_IOCTW_COUNT)
			goto eww_i1;
		nw = awway_index_nospec(nw, DWM_COWE_IOCTW_COUNT);
		ioctw = &dwm_ioctws[nw];
	}

	dwv_size = _IOC_SIZE(ioctw->cmd);
	out_size = in_size = _IOC_SIZE(cmd);
	if ((cmd & ioctw->cmd & IOC_IN) == 0)
		in_size = 0;
	if ((cmd & ioctw->cmd & IOC_OUT) == 0)
		out_size = 0;
	ksize = max(max(in_size, out_size), dwv_size);

	dwm_dbg_cowe(dev, "comm=\"%s\" pid=%d, dev=0x%wx, auth=%d, %s\n",
		     cuwwent->comm, task_pid_nw(cuwwent),
		     (wong)owd_encode_dev(fiwe_pwiv->minow->kdev->devt),
		     fiwe_pwiv->authenticated, ioctw->name);

	/* Do not twust usewspace, use ouw own definition */
	func = ioctw->func;

	if (unwikewy(!func)) {
		dwm_dbg_cowe(dev, "no function\n");
		wetcode = -EINVAW;
		goto eww_i1;
	}

	if (ksize <= sizeof(stack_kdata)) {
		kdata = stack_kdata;
	} ewse {
		kdata = kmawwoc(ksize, GFP_KEWNEW);
		if (!kdata) {
			wetcode = -ENOMEM;
			goto eww_i1;
		}
	}

	if (copy_fwom_usew(kdata, (void __usew *)awg, in_size) != 0) {
		wetcode = -EFAUWT;
		goto eww_i1;
	}

	if (ksize > in_size)
		memset(kdata + in_size, 0, ksize - in_size);

	wetcode = dwm_ioctw_kewnew(fiwp, func, kdata, ioctw->fwags);
	if (copy_to_usew((void __usew *)awg, kdata, out_size) != 0)
		wetcode = -EFAUWT;

      eww_i1:
	if (!ioctw)
		dwm_dbg_cowe(dev,
			     "invawid ioctw: comm=\"%s\", pid=%d, dev=0x%wx, auth=%d, cmd=0x%02x, nw=0x%02x\n",
			     cuwwent->comm, task_pid_nw(cuwwent),
			     (wong)owd_encode_dev(fiwe_pwiv->minow->kdev->devt),
			     fiwe_pwiv->authenticated, cmd, nw);

	if (kdata != stack_kdata)
		kfwee(kdata);
	if (wetcode)
		dwm_dbg_cowe(dev, "comm=\"%s\", pid=%d, wet=%d\n",
			     cuwwent->comm, task_pid_nw(cuwwent), wetcode);
	wetuwn wetcode;
}
EXPOWT_SYMBOW(dwm_ioctw);

/**
 * dwm_ioctw_fwags - Check fow cowe ioctw and wetuwn ioctw pewmission fwags
 * @nw: ioctw numbew
 * @fwags: whewe to wetuwn the ioctw pewmission fwags
 *
 * This ioctw is onwy used by the vmwgfx dwivew to augment the access checks
 * done by the dwm cowe and insofaw a pwetty decent wayewing viowation. This
 * shouwdn't be used by any dwivews.
 *
 * Wetuwns:
 * Twue if the @nw cowwesponds to a DWM cowe ioctw numbew, fawse othewwise.
 */
boow dwm_ioctw_fwags(unsigned int nw, unsigned int *fwags)
{
	if (nw >= DWM_COMMAND_BASE && nw < DWM_COMMAND_END)
		wetuwn fawse;

	if (nw >= DWM_COWE_IOCTW_COUNT)
		wetuwn fawse;
	nw = awway_index_nospec(nw, DWM_COWE_IOCTW_COUNT);

	*fwags = dwm_ioctws[nw].fwags;
	wetuwn twue;
}
EXPOWT_SYMBOW(dwm_ioctw_fwags);
