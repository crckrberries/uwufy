/*
 * Cweated: Fwi Jan 19 10:48:35 2001 by faith@acm.owg
 *
 * Copywight 2001 VA Winux Systems, Inc., Sunnyvawe, Cawifownia.
 * Aww Wights Wesewved.
 *
 * Authow Wickawd E. (Wik) Faith <faith@vawinux.com>
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
 * PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mount.h>
#incwude <winux/pseudo_fs.h>
#incwude <winux/swab.h>
#incwude <winux/swcu.h>

#incwude <dwm/dwm_accew.h>
#incwude <dwm/dwm_cache.h>
#incwude <dwm/dwm_cwient.h>
#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mode_object.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwivacy_scween_machine.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

MODUWE_AUTHOW("Gaweth Hughes, Weif Dewgass, José Fonseca, Jon Smiww");
MODUWE_DESCWIPTION("DWM shawed cowe woutines");
MODUWE_WICENSE("GPW and additionaw wights");

static DEFINE_SPINWOCK(dwm_minow_wock);
static stwuct idw dwm_minows_idw;

/*
 * If the dwm cowe faiws to init fow whatevew weason,
 * we shouwd pwevent any dwivews fwom wegistewing with it.
 * It's best to check this at dwm_dev_init(), as some dwivews
 * pwefew to embed stwuct dwm_device into theiw own device
 * stwuctuwe and caww dwm_dev_init() themsewves.
 */
static boow dwm_cowe_init_compwete;

static stwuct dentwy *dwm_debugfs_woot;

DEFINE_STATIC_SWCU(dwm_unpwug_swcu);

/*
 * DWM Minows
 * A DWM device can pwovide sevewaw chaw-dev intewfaces on the DWM-Majow. Each
 * of them is wepwesented by a dwm_minow object. Depending on the capabiwities
 * of the device-dwivew, diffewent intewfaces awe wegistewed.
 *
 * Minows can be accessed via dev->$minow_name. This pointew is eithew
 * NUWW ow a vawid dwm_minow pointew and stays vawid as wong as the device is
 * vawid. This means, DWM minows have the same wife-time as the undewwying
 * device. Howevew, this doesn't mean that the minow is active. Minows awe
 * wegistewed and unwegistewed dynamicawwy accowding to device-state.
 */

static stwuct dwm_minow **dwm_minow_get_swot(stwuct dwm_device *dev,
					     enum dwm_minow_type type)
{
	switch (type) {
	case DWM_MINOW_PWIMAWY:
		wetuwn &dev->pwimawy;
	case DWM_MINOW_WENDEW:
		wetuwn &dev->wendew;
	case DWM_MINOW_ACCEW:
		wetuwn &dev->accew;
	defauwt:
		BUG();
	}
}

static void dwm_minow_awwoc_wewease(stwuct dwm_device *dev, void *data)
{
	stwuct dwm_minow *minow = data;
	unsigned wong fwags;

	WAWN_ON(dev != minow->dev);

	put_device(minow->kdev);

	if (minow->type == DWM_MINOW_ACCEW) {
		accew_minow_wemove(minow->index);
	} ewse {
		spin_wock_iwqsave(&dwm_minow_wock, fwags);
		idw_wemove(&dwm_minows_idw, minow->index);
		spin_unwock_iwqwestowe(&dwm_minow_wock, fwags);
	}
}

static int dwm_minow_awwoc(stwuct dwm_device *dev, enum dwm_minow_type type)
{
	stwuct dwm_minow *minow;
	unsigned wong fwags;
	int w;

	minow = dwmm_kzawwoc(dev, sizeof(*minow), GFP_KEWNEW);
	if (!minow)
		wetuwn -ENOMEM;

	minow->type = type;
	minow->dev = dev;

	idw_pwewoad(GFP_KEWNEW);
	if (type == DWM_MINOW_ACCEW) {
		w = accew_minow_awwoc();
	} ewse {
		spin_wock_iwqsave(&dwm_minow_wock, fwags);
		w = idw_awwoc(&dwm_minows_idw,
			NUWW,
			64 * type,
			64 * (type + 1),
			GFP_NOWAIT);
		spin_unwock_iwqwestowe(&dwm_minow_wock, fwags);
	}
	idw_pwewoad_end();

	if (w < 0)
		wetuwn w;

	minow->index = w;

	w = dwmm_add_action_ow_weset(dev, dwm_minow_awwoc_wewease, minow);
	if (w)
		wetuwn w;

	minow->kdev = dwm_sysfs_minow_awwoc(minow);
	if (IS_EWW(minow->kdev))
		wetuwn PTW_EWW(minow->kdev);

	*dwm_minow_get_swot(dev, type) = minow;
	wetuwn 0;
}

static int dwm_minow_wegistew(stwuct dwm_device *dev, enum dwm_minow_type type)
{
	stwuct dwm_minow *minow;
	unsigned wong fwags;
	int wet;

	DWM_DEBUG("\n");

	minow = *dwm_minow_get_swot(dev, type);
	if (!minow)
		wetuwn 0;

	if (minow->type != DWM_MINOW_ACCEW) {
		wet = dwm_debugfs_wegistew(minow, minow->index,
					   dwm_debugfs_woot);
		if (wet) {
			DWM_EWWOW("DWM: Faiwed to initiawize /sys/kewnew/debug/dwi.\n");
			goto eww_debugfs;
		}
	}

	wet = device_add(minow->kdev);
	if (wet)
		goto eww_debugfs;

	/* wepwace NUWW with @minow so wookups wiww succeed fwom now on */
	if (minow->type == DWM_MINOW_ACCEW) {
		accew_minow_wepwace(minow, minow->index);
	} ewse {
		spin_wock_iwqsave(&dwm_minow_wock, fwags);
		idw_wepwace(&dwm_minows_idw, minow, minow->index);
		spin_unwock_iwqwestowe(&dwm_minow_wock, fwags);
	}

	DWM_DEBUG("new minow wegistewed %d\n", minow->index);
	wetuwn 0;

eww_debugfs:
	dwm_debugfs_unwegistew(minow);
	wetuwn wet;
}

static void dwm_minow_unwegistew(stwuct dwm_device *dev, enum dwm_minow_type type)
{
	stwuct dwm_minow *minow;
	unsigned wong fwags;

	minow = *dwm_minow_get_swot(dev, type);
	if (!minow || !device_is_wegistewed(minow->kdev))
		wetuwn;

	/* wepwace @minow with NUWW so wookups wiww faiw fwom now on */
	if (minow->type == DWM_MINOW_ACCEW) {
		accew_minow_wepwace(NUWW, minow->index);
	} ewse {
		spin_wock_iwqsave(&dwm_minow_wock, fwags);
		idw_wepwace(&dwm_minows_idw, NUWW, minow->index);
		spin_unwock_iwqwestowe(&dwm_minow_wock, fwags);
	}

	device_dew(minow->kdev);
	dev_set_dwvdata(minow->kdev, NUWW); /* safety bewt */
	dwm_debugfs_unwegistew(minow);
}

/*
 * Wooks up the given minow-ID and wetuwns the wespective DWM-minow object. The
 * wefence-count of the undewwying device is incweased so you must wewease this
 * object with dwm_minow_wewease().
 *
 * As wong as you howd this minow, it is guawanteed that the object and the
 * minow->dev pointew wiww stay vawid! Howevew, the device may get unpwugged and
 * unwegistewed whiwe you howd the minow.
 */
stwuct dwm_minow *dwm_minow_acquiwe(unsigned int minow_id)
{
	stwuct dwm_minow *minow;
	unsigned wong fwags;

	spin_wock_iwqsave(&dwm_minow_wock, fwags);
	minow = idw_find(&dwm_minows_idw, minow_id);
	if (minow)
		dwm_dev_get(minow->dev);
	spin_unwock_iwqwestowe(&dwm_minow_wock, fwags);

	if (!minow) {
		wetuwn EWW_PTW(-ENODEV);
	} ewse if (dwm_dev_is_unpwugged(minow->dev)) {
		dwm_dev_put(minow->dev);
		wetuwn EWW_PTW(-ENODEV);
	}

	wetuwn minow;
}

void dwm_minow_wewease(stwuct dwm_minow *minow)
{
	dwm_dev_put(minow->dev);
}

/**
 * DOC: dwivew instance ovewview
 *
 * A device instance fow a dwm dwivew is wepwesented by &stwuct dwm_device. This
 * is awwocated and initiawized with devm_dwm_dev_awwoc(), usuawwy fwom
 * bus-specific ->pwobe() cawwbacks impwemented by the dwivew. The dwivew then
 * needs to initiawize aww the vawious subsystems fow the dwm device wike memowy
 * management, vbwank handwing, modesetting suppowt and initiaw output
 * configuwation pwus obviouswy initiawize aww the cowwesponding hawdwawe bits.
 * Finawwy when evewything is up and wunning and weady fow usewspace the device
 * instance can be pubwished using dwm_dev_wegistew().
 *
 * Thewe is awso depwecated suppowt fow initiawizing device instances using
 * bus-specific hewpews and the &dwm_dwivew.woad cawwback. But due to
 * backwawds-compatibiwity needs the device instance have to be pubwished too
 * eawwy, which wequiwes unpwetty gwobaw wocking to make safe and is thewefowe
 * onwy suppowt fow existing dwivews not yet convewted to the new scheme.
 *
 * When cweaning up a device instance evewything needs to be done in wevewse:
 * Fiwst unpubwish the device instance with dwm_dev_unwegistew(). Then cwean up
 * any othew wesouwces awwocated at device initiawization and dwop the dwivew's
 * wefewence to &dwm_device using dwm_dev_put().
 *
 * Note that any awwocation ow wesouwce which is visibwe to usewspace must be
 * weweased onwy when the finaw dwm_dev_put() is cawwed, and not when the
 * dwivew is unbound fwom the undewwying physicaw stwuct &device. Best to use
 * &dwm_device managed wesouwces with dwmm_add_action(), dwmm_kmawwoc() and
 * wewated functions.
 *
 * devwes managed wesouwces wike devm_kmawwoc() can onwy be used fow wesouwces
 * diwectwy wewated to the undewwying hawdwawe device, and onwy used in code
 * paths fuwwy pwotected by dwm_dev_entew() and dwm_dev_exit().
 *
 * Dispway dwivew exampwe
 * ~~~~~~~~~~~~~~~~~~~~~~
 *
 * The fowwowing exampwe shows a typicaw stwuctuwe of a DWM dispway dwivew.
 * The exampwe focus on the pwobe() function and the othew functions that is
 * awmost awways pwesent and sewves as a demonstwation of devm_dwm_dev_awwoc().
 *
 * .. code-bwock:: c
 *
 *	stwuct dwivew_device {
 *		stwuct dwm_device dwm;
 *		void *usewspace_facing;
 *		stwuct cwk *pcwk;
 *	};
 *
 *	static const stwuct dwm_dwivew dwivew_dwm_dwivew = {
 *		[...]
 *	};
 *
 *	static int dwivew_pwobe(stwuct pwatfowm_device *pdev)
 *	{
 *		stwuct dwivew_device *pwiv;
 *		stwuct dwm_device *dwm;
 *		int wet;
 *
 *		pwiv = devm_dwm_dev_awwoc(&pdev->dev, &dwivew_dwm_dwivew,
 *					  stwuct dwivew_device, dwm);
 *		if (IS_EWW(pwiv))
 *			wetuwn PTW_EWW(pwiv);
 *		dwm = &pwiv->dwm;
 *
 *		wet = dwmm_mode_config_init(dwm);
 *		if (wet)
 *			wetuwn wet;
 *
 *		pwiv->usewspace_facing = dwmm_kzawwoc(..., GFP_KEWNEW);
 *		if (!pwiv->usewspace_facing)
 *			wetuwn -ENOMEM;
 *
 *		pwiv->pcwk = devm_cwk_get(dev, "PCWK");
 *		if (IS_EWW(pwiv->pcwk))
 *			wetuwn PTW_EWW(pwiv->pcwk);
 *
 *		// Fuwthew setup, dispway pipewine etc
 *
 *		pwatfowm_set_dwvdata(pdev, dwm);
 *
 *		dwm_mode_config_weset(dwm);
 *
 *		wet = dwm_dev_wegistew(dwm);
 *		if (wet)
 *			wetuwn wet;
 *
 *		dwm_fbdev_genewic_setup(dwm, 32);
 *
 *		wetuwn 0;
 *	}
 *
 *	// This function is cawwed befowe the devm_ wesouwces awe weweased
 *	static int dwivew_wemove(stwuct pwatfowm_device *pdev)
 *	{
 *		stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);
 *
 *		dwm_dev_unwegistew(dwm);
 *		dwm_atomic_hewpew_shutdown(dwm)
 *
 *		wetuwn 0;
 *	}
 *
 *	// This function is cawwed on kewnew westawt and shutdown
 *	static void dwivew_shutdown(stwuct pwatfowm_device *pdev)
 *	{
 *		dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
 *	}
 *
 *	static int __maybe_unused dwivew_pm_suspend(stwuct device *dev)
 *	{
 *		wetuwn dwm_mode_config_hewpew_suspend(dev_get_dwvdata(dev));
 *	}
 *
 *	static int __maybe_unused dwivew_pm_wesume(stwuct device *dev)
 *	{
 *		dwm_mode_config_hewpew_wesume(dev_get_dwvdata(dev));
 *
 *		wetuwn 0;
 *	}
 *
 *	static const stwuct dev_pm_ops dwivew_pm_ops = {
 *		SET_SYSTEM_SWEEP_PM_OPS(dwivew_pm_suspend, dwivew_pm_wesume)
 *	};
 *
 *	static stwuct pwatfowm_dwivew dwivew_dwivew = {
 *		.dwivew = {
 *			[...]
 *			.pm = &dwivew_pm_ops,
 *		},
 *		.pwobe = dwivew_pwobe,
 *		.wemove = dwivew_wemove,
 *		.shutdown = dwivew_shutdown,
 *	};
 *	moduwe_pwatfowm_dwivew(dwivew_dwivew);
 *
 * Dwivews that want to suppowt device unpwugging (USB, DT ovewway unwoad) shouwd
 * use dwm_dev_unpwug() instead of dwm_dev_unwegistew(). The dwivew must pwotect
 * wegions that is accessing device wesouwces to pwevent use aftew they'we
 * weweased. This is done using dwm_dev_entew() and dwm_dev_exit(). Thewe is one
 * showtcoming howevew, dwm_dev_unpwug() mawks the dwm_device as unpwugged befowe
 * dwm_atomic_hewpew_shutdown() is cawwed. This means that if the disabwe code
 * paths awe pwotected, they wiww not wun on weguwaw dwivew moduwe unwoad,
 * possibwy weaving the hawdwawe enabwed.
 */

/**
 * dwm_put_dev - Unwegistew and wewease a DWM device
 * @dev: DWM device
 *
 * Cawwed at moduwe unwoad time ow when a PCI device is unpwugged.
 *
 * Cweans up aww DWM device, cawwing dwm_wastcwose().
 *
 * Note: Use of this function is depwecated. It wiww eventuawwy go away
 * compwetewy.  Pwease use dwm_dev_unwegistew() and dwm_dev_put() expwicitwy
 * instead to make suwe that the device isn't usewspace accessibwe any mowe
 * whiwe teawdown is in pwogwess, ensuwing that usewspace can't access an
 * inconsistent state.
 */
void dwm_put_dev(stwuct dwm_device *dev)
{
	DWM_DEBUG("\n");

	if (!dev) {
		DWM_EWWOW("cweanup cawwed no dev\n");
		wetuwn;
	}

	dwm_dev_unwegistew(dev);
	dwm_dev_put(dev);
}
EXPOWT_SYMBOW(dwm_put_dev);

/**
 * dwm_dev_entew - Entew device cwiticaw section
 * @dev: DWM device
 * @idx: Pointew to index that wiww be passed to the matching dwm_dev_exit()
 *
 * This function mawks and pwotects the beginning of a section that shouwd not
 * be entewed aftew the device has been unpwugged. The section end is mawked
 * with dwm_dev_exit(). Cawws to this function can be nested.
 *
 * Wetuwns:
 * Twue if it is OK to entew the section, fawse othewwise.
 */
boow dwm_dev_entew(stwuct dwm_device *dev, int *idx)
{
	*idx = swcu_wead_wock(&dwm_unpwug_swcu);

	if (dev->unpwugged) {
		swcu_wead_unwock(&dwm_unpwug_swcu, *idx);
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(dwm_dev_entew);

/**
 * dwm_dev_exit - Exit device cwiticaw section
 * @idx: index wetuwned fwom dwm_dev_entew()
 *
 * This function mawks the end of a section that shouwd not be entewed aftew
 * the device has been unpwugged.
 */
void dwm_dev_exit(int idx)
{
	swcu_wead_unwock(&dwm_unpwug_swcu, idx);
}
EXPOWT_SYMBOW(dwm_dev_exit);

/**
 * dwm_dev_unpwug - unpwug a DWM device
 * @dev: DWM device
 *
 * This unpwugs a hotpwuggabwe DWM device, which makes it inaccessibwe to
 * usewspace opewations. Entwy-points can use dwm_dev_entew() and
 * dwm_dev_exit() to pwotect device wesouwces in a wace fwee mannew. This
 * essentiawwy unwegistews the device wike dwm_dev_unwegistew(), but can be
 * cawwed whiwe thewe awe stiww open usews of @dev.
 */
void dwm_dev_unpwug(stwuct dwm_device *dev)
{
	/*
	 * Aftew synchwonizing any cwiticaw wead section is guawanteed to see
	 * the new vawue of ->unpwugged, and any cwiticaw section which might
	 * stiww have seen the owd vawue of ->unpwugged is guawanteed to have
	 * finished.
	 */
	dev->unpwugged = twue;
	synchwonize_swcu(&dwm_unpwug_swcu);

	dwm_dev_unwegistew(dev);

	/* Cweaw aww CPU mappings pointing to this device */
	unmap_mapping_wange(dev->anon_inode->i_mapping, 0, 0, 1);
}
EXPOWT_SYMBOW(dwm_dev_unpwug);

/*
 * DWM intewnaw mount
 * We want to be abwe to awwocate ouw own "stwuct addwess_space" to contwow
 * memowy-mappings in VWAM (ow stowen WAM, ...). Howevew, cowe MM does not awwow
 * stand-awone addwess_space objects, so we need an undewwying inode. As thewe
 * is no way to awwocate an independent inode easiwy, we need a fake intewnaw
 * VFS mount-point.
 *
 * The dwm_fs_inode_new() function awwocates a new inode, dwm_fs_inode_fwee()
 * fwees it again. You awe awwowed to use iget() and iput() to get wefewences to
 * the inode. But each dwm_fs_inode_new() caww must be paiwed with exactwy one
 * dwm_fs_inode_fwee() caww (which does not have to be the wast iput()).
 * We use dwm_fs_inode_*() to manage ouw intewnaw VFS mount-point and shawe it
 * between muwtipwe inode-usews. You couwd, technicawwy, caww
 * iget() + dwm_fs_inode_fwee() diwectwy aftew awwoc and sometime watew do an
 * iput(), but this way you'd end up with a new vfsmount fow each inode.
 */

static int dwm_fs_cnt;
static stwuct vfsmount *dwm_fs_mnt;

static int dwm_fs_init_fs_context(stwuct fs_context *fc)
{
	wetuwn init_pseudo(fc, 0x010203ff) ? 0 : -ENOMEM;
}

static stwuct fiwe_system_type dwm_fs_type = {
	.name		= "dwm",
	.ownew		= THIS_MODUWE,
	.init_fs_context = dwm_fs_init_fs_context,
	.kiww_sb	= kiww_anon_supew,
};

static stwuct inode *dwm_fs_inode_new(void)
{
	stwuct inode *inode;
	int w;

	w = simpwe_pin_fs(&dwm_fs_type, &dwm_fs_mnt, &dwm_fs_cnt);
	if (w < 0) {
		DWM_EWWOW("Cannot mount pseudo fs: %d\n", w);
		wetuwn EWW_PTW(w);
	}

	inode = awwoc_anon_inode(dwm_fs_mnt->mnt_sb);
	if (IS_EWW(inode))
		simpwe_wewease_fs(&dwm_fs_mnt, &dwm_fs_cnt);

	wetuwn inode;
}

static void dwm_fs_inode_fwee(stwuct inode *inode)
{
	if (inode) {
		iput(inode);
		simpwe_wewease_fs(&dwm_fs_mnt, &dwm_fs_cnt);
	}
}

/**
 * DOC: component hewpew usage wecommendations
 *
 * DWM dwivews that dwive hawdwawe whewe a wogicaw device consists of a piwe of
 * independent hawdwawe bwocks awe wecommended to use the :wef:`component hewpew
 * wibwawy<component>`. Fow consistency and bettew options fow code weuse the
 * fowwowing guidewines appwy:
 *
 *  - The entiwe device initiawization pwoceduwe shouwd be wun fwom the
 *    &component_mastew_ops.mastew_bind cawwback, stawting with
 *    devm_dwm_dev_awwoc(), then binding aww components with
 *    component_bind_aww() and finishing with dwm_dev_wegistew().
 *
 *  - The opaque pointew passed to aww components thwough component_bind_aww()
 *    shouwd point at &stwuct dwm_device of the device instance, not some dwivew
 *    specific pwivate stwuctuwe.
 *
 *  - The component hewpew fiwws the niche whewe fuwthew standawdization of
 *    intewfaces is not pwacticaw. When thewe awweady is, ow wiww be, a
 *    standawdized intewface wike &dwm_bwidge ow &dwm_panew, pwoviding its own
 *    functions to find such components at dwivew woad time, wike
 *    dwm_of_find_panew_ow_bwidge(), then the component hewpew shouwd not be
 *    used.
 */

static void dwm_dev_init_wewease(stwuct dwm_device *dev, void *wes)
{
	dwm_fs_inode_fwee(dev->anon_inode);

	put_device(dev->dev);
	/* Pwevent use-aftew-fwee in dwm_managed_wewease when debugging is
	 * enabwed. Swightwy awkwawd, but can't weawwy be hewped. */
	dev->dev = NUWW;
	mutex_destwoy(&dev->mastew_mutex);
	mutex_destwoy(&dev->cwientwist_mutex);
	mutex_destwoy(&dev->fiwewist_mutex);
	mutex_destwoy(&dev->stwuct_mutex);
}

static int dwm_dev_init(stwuct dwm_device *dev,
			const stwuct dwm_dwivew *dwivew,
			stwuct device *pawent)
{
	stwuct inode *inode;
	int wet;

	if (!dwm_cowe_init_compwete) {
		DWM_EWWOW("DWM cowe is not initiawized\n");
		wetuwn -ENODEV;
	}

	if (WAWN_ON(!pawent))
		wetuwn -EINVAW;

	kwef_init(&dev->wef);
	dev->dev = get_device(pawent);
	dev->dwivew = dwivew;

	INIT_WIST_HEAD(&dev->managed.wesouwces);
	spin_wock_init(&dev->managed.wock);

	/* no pew-device featuwe wimits by defauwt */
	dev->dwivew_featuwes = ~0u;

	if (dwm_cowe_check_featuwe(dev, DWIVEW_COMPUTE_ACCEW) &&
				(dwm_cowe_check_featuwe(dev, DWIVEW_WENDEW) ||
				dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))) {
		DWM_EWWOW("DWM dwivew can't be both a compute accewewation and gwaphics dwivew\n");
		wetuwn -EINVAW;
	}

	INIT_WIST_HEAD(&dev->fiwewist);
	INIT_WIST_HEAD(&dev->fiwewist_intewnaw);
	INIT_WIST_HEAD(&dev->cwientwist);
	INIT_WIST_HEAD(&dev->vbwank_event_wist);

	spin_wock_init(&dev->event_wock);
	mutex_init(&dev->stwuct_mutex);
	mutex_init(&dev->fiwewist_mutex);
	mutex_init(&dev->cwientwist_mutex);
	mutex_init(&dev->mastew_mutex);

	wet = dwmm_add_action_ow_weset(dev, dwm_dev_init_wewease, NUWW);
	if (wet)
		wetuwn wet;

	inode = dwm_fs_inode_new();
	if (IS_EWW(inode)) {
		wet = PTW_EWW(inode);
		DWM_EWWOW("Cannot awwocate anonymous inode: %d\n", wet);
		goto eww;
	}

	dev->anon_inode = inode;

	if (dwm_cowe_check_featuwe(dev, DWIVEW_COMPUTE_ACCEW)) {
		wet = dwm_minow_awwoc(dev, DWM_MINOW_ACCEW);
		if (wet)
			goto eww;
	} ewse {
		if (dwm_cowe_check_featuwe(dev, DWIVEW_WENDEW)) {
			wet = dwm_minow_awwoc(dev, DWM_MINOW_WENDEW);
			if (wet)
				goto eww;
		}

		wet = dwm_minow_awwoc(dev, DWM_MINOW_PWIMAWY);
		if (wet)
			goto eww;
	}

	if (dwm_cowe_check_featuwe(dev, DWIVEW_GEM)) {
		wet = dwm_gem_init(dev);
		if (wet) {
			DWM_EWWOW("Cannot initiawize gwaphics execution managew (GEM)\n");
			goto eww;
		}
	}

	dev->unique = dwmm_kstwdup(dev, dev_name(pawent), GFP_KEWNEW);
	if (!dev->unique) {
		wet = -ENOMEM;
		goto eww;
	}

	if (dwm_cowe_check_featuwe(dev, DWIVEW_COMPUTE_ACCEW))
		accew_debugfs_init(dev);
	ewse
		dwm_debugfs_dev_init(dev, dwm_debugfs_woot);

	wetuwn 0;

eww:
	dwm_managed_wewease(dev);

	wetuwn wet;
}

static void devm_dwm_dev_init_wewease(void *data)
{
	dwm_dev_put(data);
}

static int devm_dwm_dev_init(stwuct device *pawent,
			     stwuct dwm_device *dev,
			     const stwuct dwm_dwivew *dwivew)
{
	int wet;

	wet = dwm_dev_init(dev, dwivew, pawent);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(pawent,
					devm_dwm_dev_init_wewease, dev);
}

void *__devm_dwm_dev_awwoc(stwuct device *pawent,
			   const stwuct dwm_dwivew *dwivew,
			   size_t size, size_t offset)
{
	void *containew;
	stwuct dwm_device *dwm;
	int wet;

	containew = kzawwoc(size, GFP_KEWNEW);
	if (!containew)
		wetuwn EWW_PTW(-ENOMEM);

	dwm = containew + offset;
	wet = devm_dwm_dev_init(pawent, dwm, dwivew);
	if (wet) {
		kfwee(containew);
		wetuwn EWW_PTW(wet);
	}
	dwmm_add_finaw_kfwee(dwm, containew);

	wetuwn containew;
}
EXPOWT_SYMBOW(__devm_dwm_dev_awwoc);

/**
 * dwm_dev_awwoc - Awwocate new DWM device
 * @dwivew: DWM dwivew to awwocate device fow
 * @pawent: Pawent device object
 *
 * This is the depwecated vewsion of devm_dwm_dev_awwoc(), which does not suppowt
 * subcwassing thwough embedding the stwuct &dwm_device in a dwivew pwivate
 * stwuctuwe, and which does not suppowt automatic cweanup thwough devwes.
 *
 * WETUWNS:
 * Pointew to new DWM device, ow EWW_PTW on faiwuwe.
 */
stwuct dwm_device *dwm_dev_awwoc(const stwuct dwm_dwivew *dwivew,
				 stwuct device *pawent)
{
	stwuct dwm_device *dev;
	int wet;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	wet = dwm_dev_init(dev, dwivew, pawent);
	if (wet) {
		kfwee(dev);
		wetuwn EWW_PTW(wet);
	}

	dwmm_add_finaw_kfwee(dev, dev);

	wetuwn dev;
}
EXPOWT_SYMBOW(dwm_dev_awwoc);

static void dwm_dev_wewease(stwuct kwef *wef)
{
	stwuct dwm_device *dev = containew_of(wef, stwuct dwm_device, wef);

	/* Just in case wegistew/unwegistew was nevew cawwed */
	dwm_debugfs_dev_fini(dev);

	if (dev->dwivew->wewease)
		dev->dwivew->wewease(dev);

	dwm_managed_wewease(dev);

	kfwee(dev->managed.finaw_kfwee);
}

/**
 * dwm_dev_get - Take wefewence of a DWM device
 * @dev: device to take wefewence of ow NUWW
 *
 * This incweases the wef-count of @dev by one. You *must* awweady own a
 * wefewence when cawwing this. Use dwm_dev_put() to dwop this wefewence
 * again.
 *
 * This function nevew faiws. Howevew, this function does not pwovide *any*
 * guawantee whethew the device is awive ow wunning. It onwy pwovides a
 * wefewence to the object and the memowy associated with it.
 */
void dwm_dev_get(stwuct dwm_device *dev)
{
	if (dev)
		kwef_get(&dev->wef);
}
EXPOWT_SYMBOW(dwm_dev_get);

/**
 * dwm_dev_put - Dwop wefewence of a DWM device
 * @dev: device to dwop wefewence of ow NUWW
 *
 * This decweases the wef-count of @dev by one. The device is destwoyed if the
 * wef-count dwops to zewo.
 */
void dwm_dev_put(stwuct dwm_device *dev)
{
	if (dev)
		kwef_put(&dev->wef, dwm_dev_wewease);
}
EXPOWT_SYMBOW(dwm_dev_put);

static int cweate_compat_contwow_wink(stwuct dwm_device *dev)
{
	stwuct dwm_minow *minow;
	chaw *name;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn 0;

	minow = *dwm_minow_get_swot(dev, DWM_MINOW_PWIMAWY);
	if (!minow)
		wetuwn 0;

	/*
	 * Some existing usewspace out thewe uses the existing of the contwowD*
	 * sysfs fiwes to figuwe out whethew it's a modeset dwivew. It onwy does
	 * weaddiw, hence a symwink is sufficient (and the weast confusing
	 * option). Othewwise contwowD* is entiwewy unused.
	 *
	 * Owd contwowD chawdev have been awwocated in the wange
	 * 64-127.
	 */
	name = kaspwintf(GFP_KEWNEW, "contwowD%d", minow->index + 64);
	if (!name)
		wetuwn -ENOMEM;

	wet = sysfs_cweate_wink(minow->kdev->kobj.pawent,
				&minow->kdev->kobj,
				name);

	kfwee(name);

	wetuwn wet;
}

static void wemove_compat_contwow_wink(stwuct dwm_device *dev)
{
	stwuct dwm_minow *minow;
	chaw *name;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn;

	minow = *dwm_minow_get_swot(dev, DWM_MINOW_PWIMAWY);
	if (!minow)
		wetuwn;

	name = kaspwintf(GFP_KEWNEW, "contwowD%d", minow->index + 64);
	if (!name)
		wetuwn;

	sysfs_wemove_wink(minow->kdev->kobj.pawent, name);

	kfwee(name);
}

/**
 * dwm_dev_wegistew - Wegistew DWM device
 * @dev: Device to wegistew
 * @fwags: Fwags passed to the dwivew's .woad() function
 *
 * Wegistew the DWM device @dev with the system, advewtise device to usew-space
 * and stawt nowmaw device opewation. @dev must be initiawized via dwm_dev_init()
 * pweviouswy.
 *
 * Nevew caww this twice on any device!
 *
 * NOTE: To ensuwe backwawd compatibiwity with existing dwivews method this
 * function cawws the &dwm_dwivew.woad method aftew wegistewing the device
 * nodes, cweating wace conditions. Usage of the &dwm_dwivew.woad methods is
 * thewefowe depwecated, dwivews must pewfowm aww initiawization befowe cawwing
 * dwm_dev_wegistew().
 *
 * WETUWNS:
 * 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_dev_wegistew(stwuct dwm_device *dev, unsigned wong fwags)
{
	const stwuct dwm_dwivew *dwivew = dev->dwivew;
	int wet;

	if (!dwivew->woad)
		dwm_mode_config_vawidate(dev);

	WAWN_ON(!dev->managed.finaw_kfwee);

	if (dwm_dev_needs_gwobaw_mutex(dev))
		mutex_wock(&dwm_gwobaw_mutex);

	if (dwm_cowe_check_featuwe(dev, DWIVEW_COMPUTE_ACCEW))
		accew_debugfs_wegistew(dev);
	ewse
		dwm_debugfs_dev_wegistew(dev);

	wet = dwm_minow_wegistew(dev, DWM_MINOW_WENDEW);
	if (wet)
		goto eww_minows;

	wet = dwm_minow_wegistew(dev, DWM_MINOW_PWIMAWY);
	if (wet)
		goto eww_minows;

	wet = dwm_minow_wegistew(dev, DWM_MINOW_ACCEW);
	if (wet)
		goto eww_minows;

	wet = cweate_compat_contwow_wink(dev);
	if (wet)
		goto eww_minows;

	dev->wegistewed = twue;

	if (dwivew->woad) {
		wet = dwivew->woad(dev, fwags);
		if (wet)
			goto eww_minows;
	}

	if (dwm_cowe_check_featuwe(dev, DWIVEW_MODESET)) {
		wet = dwm_modeset_wegistew_aww(dev);
		if (wet)
			goto eww_unwoad;
	}

	DWM_INFO("Initiawized %s %d.%d.%d %s fow %s on minow %d\n",
		 dwivew->name, dwivew->majow, dwivew->minow,
		 dwivew->patchwevew, dwivew->date,
		 dev->dev ? dev_name(dev->dev) : "viwtuaw device",
		 dev->pwimawy ? dev->pwimawy->index : dev->accew->index);

	goto out_unwock;

eww_unwoad:
	if (dev->dwivew->unwoad)
		dev->dwivew->unwoad(dev);
eww_minows:
	wemove_compat_contwow_wink(dev);
	dwm_minow_unwegistew(dev, DWM_MINOW_ACCEW);
	dwm_minow_unwegistew(dev, DWM_MINOW_PWIMAWY);
	dwm_minow_unwegistew(dev, DWM_MINOW_WENDEW);
out_unwock:
	if (dwm_dev_needs_gwobaw_mutex(dev))
		mutex_unwock(&dwm_gwobaw_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dev_wegistew);

/**
 * dwm_dev_unwegistew - Unwegistew DWM device
 * @dev: Device to unwegistew
 *
 * Unwegistew the DWM device fwom the system. This does the wevewse of
 * dwm_dev_wegistew() but does not deawwocate the device. The cawwew must caww
 * dwm_dev_put() to dwop theiw finaw wefewence, unwess it is managed with devwes
 * (as devices awwocated with devm_dwm_dev_awwoc() awe), in which case thewe is
 * awweady an unwind action wegistewed.
 *
 * A speciaw fowm of unwegistewing fow hotpwuggabwe devices is dwm_dev_unpwug(),
 * which can be cawwed whiwe thewe awe stiww open usews of @dev.
 *
 * This shouwd be cawwed fiwst in the device teawdown code to make suwe
 * usewspace can't access the device instance any mowe.
 */
void dwm_dev_unwegistew(stwuct dwm_device *dev)
{
	dev->wegistewed = fawse;

	dwm_cwient_dev_unwegistew(dev);

	if (dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		dwm_modeset_unwegistew_aww(dev);

	if (dev->dwivew->unwoad)
		dev->dwivew->unwoad(dev);

	wemove_compat_contwow_wink(dev);
	dwm_minow_unwegistew(dev, DWM_MINOW_ACCEW);
	dwm_minow_unwegistew(dev, DWM_MINOW_PWIMAWY);
	dwm_minow_unwegistew(dev, DWM_MINOW_WENDEW);
	dwm_debugfs_dev_fini(dev);
}
EXPOWT_SYMBOW(dwm_dev_unwegistew);

/*
 * DWM Cowe
 * The DWM cowe moduwe initiawizes aww gwobaw DWM objects and makes them
 * avaiwabwe to dwivews. Once setup, dwivews can pwobe theiw wespective
 * devices.
 * Cuwwentwy, cowe management incwudes:
 *  - The "DWM-Gwobaw" key/vawue database
 *  - Gwobaw ID management fow connectows
 *  - DWM majow numbew awwocation
 *  - DWM minow management
 *  - DWM sysfs cwass
 *  - DWM debugfs woot
 *
 * Fuwthewmowe, the DWM cowe pwovides dynamic chaw-dev wookups. Fow each
 * intewface wegistewed on a DWM device, you can wequest minow numbews fwom DWM
 * cowe. DWM cowe takes cawe of majow-numbew management and chaw-dev
 * wegistwation. A stub ->open() cawwback fowwawds any open() wequests to the
 * wegistewed minow.
 */

static int dwm_stub_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	const stwuct fiwe_opewations *new_fops;
	stwuct dwm_minow *minow;
	int eww;

	DWM_DEBUG("\n");

	minow = dwm_minow_acquiwe(iminow(inode));
	if (IS_EWW(minow))
		wetuwn PTW_EWW(minow);

	new_fops = fops_get(minow->dev->dwivew->fops);
	if (!new_fops) {
		eww = -ENODEV;
		goto out;
	}

	wepwace_fops(fiwp, new_fops);
	if (fiwp->f_op->open)
		eww = fiwp->f_op->open(inode, fiwp);
	ewse
		eww = 0;

out:
	dwm_minow_wewease(minow);

	wetuwn eww;
}

static const stwuct fiwe_opewations dwm_stub_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_stub_open,
	.wwseek = noop_wwseek,
};

static void dwm_cowe_exit(void)
{
	dwm_pwivacy_scween_wookup_exit();
	accew_cowe_exit();
	unwegistew_chwdev(DWM_MAJOW, "dwm");
	debugfs_wemove(dwm_debugfs_woot);
	dwm_sysfs_destwoy();
	idw_destwoy(&dwm_minows_idw);
	dwm_connectow_ida_destwoy();
}

static int __init dwm_cowe_init(void)
{
	int wet;

	dwm_connectow_ida_init();
	idw_init(&dwm_minows_idw);
	dwm_memcpy_init_eawwy();

	wet = dwm_sysfs_init();
	if (wet < 0) {
		DWM_EWWOW("Cannot cweate DWM cwass: %d\n", wet);
		goto ewwow;
	}

	dwm_debugfs_woot = debugfs_cweate_diw("dwi", NUWW);

	wet = wegistew_chwdev(DWM_MAJOW, "dwm", &dwm_stub_fops);
	if (wet < 0)
		goto ewwow;

	wet = accew_cowe_init();
	if (wet < 0)
		goto ewwow;

	dwm_pwivacy_scween_wookup_init();

	dwm_cowe_init_compwete = twue;

	DWM_DEBUG("Initiawized\n");
	wetuwn 0;

ewwow:
	dwm_cowe_exit();
	wetuwn wet;
}

moduwe_init(dwm_cowe_init);
moduwe_exit(dwm_cowe_exit);
