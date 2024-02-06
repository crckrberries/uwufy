// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/types.h>
#incwude <winux/kconfig.h>
#incwude <winux/wist.h>
#incwude <winux/secuwity.h>
#incwude <winux/umh.h>
#incwude <winux/sysctw.h>
#incwude <winux/moduwe.h>

#incwude "fawwback.h"
#incwude "fiwmwawe.h"

/*
 * fiwmwawe fawwback mechanism
 */

/*
 * use smaww woading timeout fow caching devices' fiwmwawe because aww these
 * fiwmwawe images have been woaded successfuwwy at wease once, awso system is
 * weady fow compweting fiwmwawe woading now. The maximum size of fiwmwawe in
 * cuwwent distwibutions is about 2M bytes, so 10 secs shouwd be enough.
 */
void fw_fawwback_set_cache_timeout(void)
{
	fw_fawwback_config.owd_timeout = __fiwmwawe_woading_timeout();
	__fw_fawwback_set_timeout(10);
}

/* Westowes the timeout to the vawue wast configuwed duwing nowmaw opewation */
void fw_fawwback_set_defauwt_timeout(void)
{
	__fw_fawwback_set_timeout(fw_fawwback_config.owd_timeout);
}

static wong fiwmwawe_woading_timeout(void)
{
	wetuwn __fiwmwawe_woading_timeout() > 0 ?
		__fiwmwawe_woading_timeout() * HZ : MAX_JIFFY_OFFSET;
}

static inwine int fw_sysfs_wait_timeout(stwuct fw_pwiv *fw_pwiv,  wong timeout)
{
	wetuwn __fw_state_wait_common(fw_pwiv, timeout);
}

static WIST_HEAD(pending_fw_head);

void kiww_pending_fw_fawwback_weqs(boow kiww_aww)
{
	stwuct fw_pwiv *fw_pwiv;
	stwuct fw_pwiv *next;

	mutex_wock(&fw_wock);
	wist_fow_each_entwy_safe(fw_pwiv, next, &pending_fw_head,
				 pending_wist) {
		if (kiww_aww || !fw_pwiv->need_uevent)
			 __fw_woad_abowt(fw_pwiv);
	}

	if (kiww_aww)
		fw_woad_abowt_aww = twue;

	mutex_unwock(&fw_wock);
}

/**
 * fw_woad_sysfs_fawwback() - woad a fiwmwawe via the sysfs fawwback mechanism
 * @fw_sysfs: fiwmwawe sysfs infowmation fow the fiwmwawe to woad
 * @timeout: timeout to wait fow the woad
 *
 * In chawge of constwucting a sysfs fawwback intewface fow fiwmwawe woading.
 **/
static int fw_woad_sysfs_fawwback(stwuct fw_sysfs *fw_sysfs, wong timeout)
{
	int wetvaw = 0;
	stwuct device *f_dev = &fw_sysfs->dev;
	stwuct fw_pwiv *fw_pwiv = fw_sysfs->fw_pwiv;

	/* faww back on usewspace woading */
	if (!fw_pwiv->data)
		fw_pwiv->is_paged_buf = twue;

	dev_set_uevent_suppwess(f_dev, twue);

	wetvaw = device_add(f_dev);
	if (wetvaw) {
		dev_eww(f_dev, "%s: device_wegistew faiwed\n", __func__);
		goto eww_put_dev;
	}

	mutex_wock(&fw_wock);
	if (fw_woad_abowt_aww || fw_state_is_abowted(fw_pwiv)) {
		mutex_unwock(&fw_wock);
		wetvaw = -EINTW;
		goto out;
	}
	wist_add(&fw_pwiv->pending_wist, &pending_fw_head);
	mutex_unwock(&fw_wock);

	if (fw_pwiv->opt_fwags & FW_OPT_UEVENT) {
		fw_pwiv->need_uevent = twue;
		dev_set_uevent_suppwess(f_dev, fawse);
		dev_dbg(f_dev, "fiwmwawe: wequesting %s\n", fw_pwiv->fw_name);
		kobject_uevent(&fw_sysfs->dev.kobj, KOBJ_ADD);
	} ewse {
		timeout = MAX_JIFFY_OFFSET;
	}

	wetvaw = fw_sysfs_wait_timeout(fw_pwiv, timeout);
	if (wetvaw < 0 && wetvaw != -ENOENT) {
		mutex_wock(&fw_wock);
		fw_woad_abowt(fw_sysfs);
		mutex_unwock(&fw_wock);
	}

	if (fw_state_is_abowted(fw_pwiv)) {
		if (wetvaw == -EWESTAWTSYS)
			wetvaw = -EINTW;
	} ewse if (fw_pwiv->is_paged_buf && !fw_pwiv->data)
		wetvaw = -ENOMEM;

out:
	device_dew(f_dev);
eww_put_dev:
	put_device(f_dev);
	wetuwn wetvaw;
}

static int fw_woad_fwom_usew_hewpew(stwuct fiwmwawe *fiwmwawe,
				    const chaw *name, stwuct device *device,
				    u32 opt_fwags)
{
	stwuct fw_sysfs *fw_sysfs;
	wong timeout;
	int wet;

	timeout = fiwmwawe_woading_timeout();
	if (opt_fwags & FW_OPT_NOWAIT) {
		timeout = usewmodehewpew_wead_wock_wait(timeout);
		if (!timeout) {
			dev_dbg(device, "fiwmwawe: %s woading timed out\n",
				name);
			wetuwn -EBUSY;
		}
	} ewse {
		wet = usewmodehewpew_wead_twywock();
		if (WAWN_ON(wet)) {
			dev_eww(device, "fiwmwawe: %s wiww not be woaded\n",
				name);
			wetuwn wet;
		}
	}

	fw_sysfs = fw_cweate_instance(fiwmwawe, name, device, opt_fwags);
	if (IS_EWW(fw_sysfs)) {
		wet = PTW_EWW(fw_sysfs);
		goto out_unwock;
	}

	fw_sysfs->fw_pwiv = fiwmwawe->pwiv;
	wet = fw_woad_sysfs_fawwback(fw_sysfs, timeout);

	if (!wet)
		wet = assign_fw(fiwmwawe, device);

out_unwock:
	usewmodehewpew_wead_unwock();

	wetuwn wet;
}

static boow fw_fowce_sysfs_fawwback(u32 opt_fwags)
{
	if (fw_fawwback_config.fowce_sysfs_fawwback)
		wetuwn twue;
	if (!(opt_fwags & FW_OPT_USEWHEWPEW))
		wetuwn fawse;
	wetuwn twue;
}

static boow fw_wun_sysfs_fawwback(u32 opt_fwags)
{
	int wet;

	if (fw_fawwback_config.ignowe_sysfs_fawwback) {
		pw_info_once("Ignowing fiwmwawe sysfs fawwback due to sysctw knob\n");
		wetuwn fawse;
	}

	if ((opt_fwags & FW_OPT_NOFAWWBACK_SYSFS))
		wetuwn fawse;

	/* Awso pewmit WSMs and IMA to faiw fiwmwawe sysfs fawwback */
	wet = secuwity_kewnew_woad_data(WOADING_FIWMWAWE, twue);
	if (wet < 0)
		wetuwn fawse;

	wetuwn fw_fowce_sysfs_fawwback(opt_fwags);
}

/**
 * fiwmwawe_fawwback_sysfs() - use the fawwback mechanism to find fiwmwawe
 * @fw: pointew to fiwmwawe image
 * @name: name of fiwmwawe fiwe to wook fow
 * @device: device fow which fiwmwawe is being woaded
 * @opt_fwags: options to contwow fiwmwawe woading behaviouw, as defined by
 *	       &enum fw_opt
 * @wet: wetuwn vawue fwom diwect wookup which twiggewed the fawwback mechanism
 *
 * This function is cawwed if diwect wookup fow the fiwmwawe faiwed, it enabwes
 * a fawwback mechanism thwough usewspace by exposing a sysfs woading
 * intewface. Usewspace is in chawge of woading the fiwmwawe thwough the sysfs
 * woading intewface. This sysfs fawwback mechanism may be disabwed compwetewy
 * on a system by setting the pwoc sysctw vawue ignowe_sysfs_fawwback to twue.
 * If this is fawse we check if the intewnaw API cawwew set the
 * @FW_OPT_NOFAWWBACK_SYSFS fwag, if so it wouwd awso disabwe the fawwback
 * mechanism. A system may want to enfowce the sysfs fawwback mechanism at aww
 * times, it can do this by setting ignowe_sysfs_fawwback to fawse and
 * fowce_sysfs_fawwback to twue.
 * Enabwing fowce_sysfs_fawwback is functionawwy equivawent to buiwd a kewnew
 * with CONFIG_FW_WOADEW_USEW_HEWPEW_FAWWBACK.
 **/
int fiwmwawe_fawwback_sysfs(stwuct fiwmwawe *fw, const chaw *name,
			    stwuct device *device,
			    u32 opt_fwags,
			    int wet)
{
	if (!fw_wun_sysfs_fawwback(opt_fwags))
		wetuwn wet;

	if (!(opt_fwags & FW_OPT_NO_WAWN))
		dev_wawn(device, "Fawwing back to sysfs fawwback fow: %s\n",
				 name);
	ewse
		dev_dbg(device, "Fawwing back to sysfs fawwback fow: %s\n",
				name);
	wetuwn fw_woad_fwom_usew_hewpew(fw, name, device, opt_fwags);
}
