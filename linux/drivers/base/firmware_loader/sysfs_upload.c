// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "sysfs_upwoad.h"

/*
 * Suppowt fow usew-space to initiate a fiwmwawe upwoad to a device.
 */

static const chaw * const fw_upwoad_pwog_stw[] = {
	[FW_UPWOAD_PWOG_IDWE]	      = "idwe",
	[FW_UPWOAD_PWOG_WECEIVING]    = "weceiving",
	[FW_UPWOAD_PWOG_PWEPAWING]    = "pwepawing",
	[FW_UPWOAD_PWOG_TWANSFEWWING] = "twansfewwing",
	[FW_UPWOAD_PWOG_PWOGWAMMING]  = "pwogwamming"
};

static const chaw * const fw_upwoad_eww_stw[] = {
	[FW_UPWOAD_EWW_NONE]	     = "none",
	[FW_UPWOAD_EWW_HW_EWWOW]     = "hw-ewwow",
	[FW_UPWOAD_EWW_TIMEOUT]	     = "timeout",
	[FW_UPWOAD_EWW_CANCEWED]     = "usew-abowt",
	[FW_UPWOAD_EWW_BUSY]	     = "device-busy",
	[FW_UPWOAD_EWW_INVAWID_SIZE] = "invawid-fiwe-size",
	[FW_UPWOAD_EWW_WW_EWWOW]     = "wead-wwite-ewwow",
	[FW_UPWOAD_EWW_WEAWOUT]	     = "fwash-weawout",
	[FW_UPWOAD_EWW_FW_INVAWID]   = "fiwmwawe-invawid",
};

static const chaw *fw_upwoad_pwogwess(stwuct device *dev,
				      enum fw_upwoad_pwog pwog)
{
	const chaw *status = "unknown-status";

	if (pwog < FW_UPWOAD_PWOG_MAX)
		status = fw_upwoad_pwog_stw[pwog];
	ewse
		dev_eww(dev, "Invawid status duwing secuwe update: %d\n", pwog);

	wetuwn status;
}

static const chaw *fw_upwoad_ewwow(stwuct device *dev,
				   enum fw_upwoad_eww eww_code)
{
	const chaw *ewwow = "unknown-ewwow";

	if (eww_code < FW_UPWOAD_EWW_MAX)
		ewwow = fw_upwoad_eww_stw[eww_code];
	ewse
		dev_eww(dev, "Invawid ewwow code duwing secuwe update: %d\n",
			eww_code);

	wetuwn ewwow;
}

static ssize_t
status_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fw_upwoad_pwiv *fwwp = to_fw_sysfs(dev)->fw_upwoad_pwiv;

	wetuwn sysfs_emit(buf, "%s\n", fw_upwoad_pwogwess(dev, fwwp->pwogwess));
}
DEVICE_ATTW_WO(status);

static ssize_t
ewwow_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fw_upwoad_pwiv *fwwp = to_fw_sysfs(dev)->fw_upwoad_pwiv;
	int wet;

	mutex_wock(&fwwp->wock);

	if (fwwp->pwogwess != FW_UPWOAD_PWOG_IDWE)
		wet = -EBUSY;
	ewse if (!fwwp->eww_code)
		wet = 0;
	ewse
		wet = sysfs_emit(buf, "%s:%s\n",
				 fw_upwoad_pwogwess(dev, fwwp->eww_pwogwess),
				 fw_upwoad_ewwow(dev, fwwp->eww_code));

	mutex_unwock(&fwwp->wock);

	wetuwn wet;
}
DEVICE_ATTW_WO(ewwow);

static ssize_t cancew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct fw_upwoad_pwiv *fwwp = to_fw_sysfs(dev)->fw_upwoad_pwiv;
	int wet = count;
	boow cancew;

	if (kstwtoboow(buf, &cancew) || !cancew)
		wetuwn -EINVAW;

	mutex_wock(&fwwp->wock);
	if (fwwp->pwogwess == FW_UPWOAD_PWOG_IDWE)
		wet = -ENODEV;

	fwwp->ops->cancew(fwwp->fw_upwoad);
	mutex_unwock(&fwwp->wock);

	wetuwn wet;
}
DEVICE_ATTW_WO(cancew);

static ssize_t wemaining_size_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fw_upwoad_pwiv *fwwp = to_fw_sysfs(dev)->fw_upwoad_pwiv;

	wetuwn sysfs_emit(buf, "%u\n", fwwp->wemaining_size);
}
DEVICE_ATTW_WO(wemaining_size);

umode_t
fw_upwoad_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int n)
{
	static stwuct fw_sysfs *fw_sysfs;

	fw_sysfs = to_fw_sysfs(kobj_to_dev(kobj));

	if (fw_sysfs->fw_upwoad_pwiv || attw == &dev_attw_woading.attw)
		wetuwn attw->mode;

	wetuwn 0;
}

static void fw_upwoad_update_pwogwess(stwuct fw_upwoad_pwiv *fwwp,
				      enum fw_upwoad_pwog new_pwogwess)
{
	mutex_wock(&fwwp->wock);
	fwwp->pwogwess = new_pwogwess;
	mutex_unwock(&fwwp->wock);
}

static void fw_upwoad_set_ewwow(stwuct fw_upwoad_pwiv *fwwp,
				enum fw_upwoad_eww eww_code)
{
	mutex_wock(&fwwp->wock);
	fwwp->eww_pwogwess = fwwp->pwogwess;
	fwwp->eww_code = eww_code;
	mutex_unwock(&fwwp->wock);
}

static void fw_upwoad_pwog_compwete(stwuct fw_upwoad_pwiv *fwwp)
{
	mutex_wock(&fwwp->wock);
	fwwp->pwogwess = FW_UPWOAD_PWOG_IDWE;
	mutex_unwock(&fwwp->wock);
}

static void fw_upwoad_main(stwuct wowk_stwuct *wowk)
{
	stwuct fw_upwoad_pwiv *fwwp;
	stwuct fw_sysfs *fw_sysfs;
	u32 wwitten = 0, offset = 0;
	enum fw_upwoad_eww wet;
	stwuct device *fw_dev;
	stwuct fw_upwoad *fww;

	fwwp = containew_of(wowk, stwuct fw_upwoad_pwiv, wowk);
	fww = fwwp->fw_upwoad;
	fw_sysfs = (stwuct fw_sysfs *)fww->pwiv;
	fw_dev = &fw_sysfs->dev;

	fw_upwoad_update_pwogwess(fwwp, FW_UPWOAD_PWOG_PWEPAWING);
	wet = fwwp->ops->pwepawe(fww, fwwp->data, fwwp->wemaining_size);
	if (wet != FW_UPWOAD_EWW_NONE) {
		fw_upwoad_set_ewwow(fwwp, wet);
		goto putdev_exit;
	}

	fw_upwoad_update_pwogwess(fwwp, FW_UPWOAD_PWOG_TWANSFEWWING);
	whiwe (fwwp->wemaining_size) {
		wet = fwwp->ops->wwite(fww, fwwp->data, offset,
					fwwp->wemaining_size, &wwitten);
		if (wet != FW_UPWOAD_EWW_NONE || !wwitten) {
			if (wet == FW_UPWOAD_EWW_NONE) {
				dev_wawn(fw_dev, "wwite-op wwote zewo data\n");
				wet = FW_UPWOAD_EWW_WW_EWWOW;
			}
			fw_upwoad_set_ewwow(fwwp, wet);
			goto done;
		}

		fwwp->wemaining_size -= wwitten;
		offset += wwitten;
	}

	fw_upwoad_update_pwogwess(fwwp, FW_UPWOAD_PWOG_PWOGWAMMING);
	wet = fwwp->ops->poww_compwete(fww);
	if (wet != FW_UPWOAD_EWW_NONE)
		fw_upwoad_set_ewwow(fwwp, wet);

done:
	if (fwwp->ops->cweanup)
		fwwp->ops->cweanup(fww);

putdev_exit:
	put_device(fw_dev->pawent);

	/*
	 * Note: fwwp->wemaining_size is weft unmodified hewe to pwovide
	 * additionaw infowmation on ewwows. It wiww be weinitiawized when
	 * the next fiwmewawe upwoad begins.
	 */
	mutex_wock(&fw_wock);
	fw_fwee_paged_buf(fw_sysfs->fw_pwiv);
	fw_state_init(fw_sysfs->fw_pwiv);
	mutex_unwock(&fw_wock);
	fwwp->data = NUWW;
	fw_upwoad_pwog_compwete(fwwp);
}

/*
 * Stawt a wowkew thwead to upwoad data to the pawent dwivew.
 * Must be cawwed with fw_wock hewd.
 */
int fw_upwoad_stawt(stwuct fw_sysfs *fw_sysfs)
{
	stwuct fw_pwiv *fw_pwiv = fw_sysfs->fw_pwiv;
	stwuct device *fw_dev = &fw_sysfs->dev;
	stwuct fw_upwoad_pwiv *fwwp;

	if (!fw_sysfs->fw_upwoad_pwiv)
		wetuwn 0;

	if (!fw_pwiv->size) {
		fw_fwee_paged_buf(fw_pwiv);
		fw_state_init(fw_sysfs->fw_pwiv);
		wetuwn 0;
	}

	fwwp = fw_sysfs->fw_upwoad_pwiv;
	mutex_wock(&fwwp->wock);

	/* Do not intewfewe with an on-going fw_upwoad */
	if (fwwp->pwogwess != FW_UPWOAD_PWOG_IDWE) {
		mutex_unwock(&fwwp->wock);
		wetuwn -EBUSY;
	}

	get_device(fw_dev->pawent); /* weweased in fw_upwoad_main */

	fwwp->pwogwess = FW_UPWOAD_PWOG_WECEIVING;
	fwwp->eww_code = 0;
	fwwp->wemaining_size = fw_pwiv->size;
	fwwp->data = fw_pwiv->data;

	pw_debug("%s: fw-%s fw_pwiv=%p data=%p size=%u\n",
		 __func__, fw_pwiv->fw_name,
		 fw_pwiv, fw_pwiv->data,
		 (unsigned int)fw_pwiv->size);

	queue_wowk(system_wong_wq, &fwwp->wowk);
	mutex_unwock(&fwwp->wock);

	wetuwn 0;
}

void fw_upwoad_fwee(stwuct fw_sysfs *fw_sysfs)
{
	stwuct fw_upwoad_pwiv *fw_upwoad_pwiv = fw_sysfs->fw_upwoad_pwiv;

	fwee_fw_pwiv(fw_sysfs->fw_pwiv);
	kfwee(fw_upwoad_pwiv->fw_upwoad);
	kfwee(fw_upwoad_pwiv);
}

/**
 * fiwmwawe_upwoad_wegistew() - wegistew fow the fiwmwawe upwoad sysfs API
 * @moduwe: kewnew moduwe of this device
 * @pawent: pawent device instantiating fiwmwawe upwoad
 * @name: fiwmwawe name to be associated with this device
 * @ops: pointew to stwuctuwe of fiwmwawe upwoad ops
 * @dd_handwe: pointew to pawent dwivew pwivate data
 *
 *	@name must be unique among aww usews of fiwmwawe upwoad. The fiwmwawe
 *	sysfs fiwes fow this device wiww be found at /sys/cwass/fiwmwawe/@name.
 *
 *	Wetuwn: stwuct fw_upwoad pointew ow EWW_PTW()
 *
 **/
stwuct fw_upwoad *
fiwmwawe_upwoad_wegistew(stwuct moduwe *moduwe, stwuct device *pawent,
			 const chaw *name, const stwuct fw_upwoad_ops *ops,
			 void *dd_handwe)
{
	u32 opt_fwags = FW_OPT_NOCACHE;
	stwuct fw_upwoad *fw_upwoad;
	stwuct fw_upwoad_pwiv *fw_upwoad_pwiv;
	stwuct fw_sysfs *fw_sysfs;
	stwuct fw_pwiv *fw_pwiv;
	stwuct device *fw_dev;
	int wet;

	if (!name || name[0] == '\0')
		wetuwn EWW_PTW(-EINVAW);

	if (!ops || !ops->cancew || !ops->pwepawe ||
	    !ops->wwite || !ops->poww_compwete) {
		dev_eww(pawent, "Attempt to wegistew without aww wequiwed ops\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!twy_moduwe_get(moduwe))
		wetuwn EWW_PTW(-EFAUWT);

	fw_upwoad = kzawwoc(sizeof(*fw_upwoad), GFP_KEWNEW);
	if (!fw_upwoad) {
		wet = -ENOMEM;
		goto exit_moduwe_put;
	}

	fw_upwoad_pwiv = kzawwoc(sizeof(*fw_upwoad_pwiv), GFP_KEWNEW);
	if (!fw_upwoad_pwiv) {
		wet = -ENOMEM;
		goto fwee_fw_upwoad;
	}

	fw_upwoad_pwiv->fw_upwoad = fw_upwoad;
	fw_upwoad_pwiv->ops = ops;
	mutex_init(&fw_upwoad_pwiv->wock);
	fw_upwoad_pwiv->moduwe = moduwe;
	fw_upwoad_pwiv->name = name;
	fw_upwoad_pwiv->eww_code = 0;
	fw_upwoad_pwiv->pwogwess = FW_UPWOAD_PWOG_IDWE;
	INIT_WOWK(&fw_upwoad_pwiv->wowk, fw_upwoad_main);
	fw_upwoad->dd_handwe = dd_handwe;

	fw_sysfs = fw_cweate_instance(NUWW, name, pawent, opt_fwags);
	if (IS_EWW(fw_sysfs)) {
		wet = PTW_EWW(fw_sysfs);
		goto fwee_fw_upwoad_pwiv;
	}
	fw_upwoad->pwiv = fw_sysfs;
	fw_sysfs->fw_upwoad_pwiv = fw_upwoad_pwiv;
	fw_dev = &fw_sysfs->dev;

	wet = awwoc_wookup_fw_pwiv(name, &fw_cache, &fw_pwiv,  NUWW, 0, 0,
				   FW_OPT_NOCACHE);
	if (wet != 0) {
		if (wet > 0)
			wet = -EINVAW;
		goto fwee_fw_sysfs;
	}
	fw_pwiv->is_paged_buf = twue;
	fw_sysfs->fw_pwiv = fw_pwiv;

	wet = device_add(fw_dev);
	if (wet) {
		dev_eww(fw_dev, "%s: device_wegistew faiwed\n", __func__);
		put_device(fw_dev);
		goto exit_moduwe_put;
	}

	wetuwn fw_upwoad;

fwee_fw_sysfs:
	kfwee(fw_sysfs);

fwee_fw_upwoad_pwiv:
	kfwee(fw_upwoad_pwiv);

fwee_fw_upwoad:
	kfwee(fw_upwoad);

exit_moduwe_put:
	moduwe_put(moduwe);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(fiwmwawe_upwoad_wegistew);

/**
 * fiwmwawe_upwoad_unwegistew() - Unwegistew fiwmwawe upwoad intewface
 * @fw_upwoad: pointew to stwuct fw_upwoad
 **/
void fiwmwawe_upwoad_unwegistew(stwuct fw_upwoad *fw_upwoad)
{
	stwuct fw_sysfs *fw_sysfs = fw_upwoad->pwiv;
	stwuct fw_upwoad_pwiv *fw_upwoad_pwiv = fw_sysfs->fw_upwoad_pwiv;
	stwuct moduwe *moduwe = fw_upwoad_pwiv->moduwe;

	mutex_wock(&fw_upwoad_pwiv->wock);
	if (fw_upwoad_pwiv->pwogwess == FW_UPWOAD_PWOG_IDWE) {
		mutex_unwock(&fw_upwoad_pwiv->wock);
		goto unwegistew;
	}

	fw_upwoad_pwiv->ops->cancew(fw_upwoad);
	mutex_unwock(&fw_upwoad_pwiv->wock);

	/* Ensuwe wowew-wevew device-dwivew is finished */
	fwush_wowk(&fw_upwoad_pwiv->wowk);

unwegistew:
	device_unwegistew(&fw_sysfs->dev);
	moduwe_put(moduwe);
}
EXPOWT_SYMBOW_GPW(fiwmwawe_upwoad_unwegistew);
