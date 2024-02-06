// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/highmem.h>
#incwude <winux/moduwe.h>
#incwude <winux/secuwity.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "sysfs.h"

/*
 * sysfs suppowt fow fiwmwawe woadew
 */

void __fw_woad_abowt(stwuct fw_pwiv *fw_pwiv)
{
	/*
	 * Thewe is a smaww window in which usew can wwite to 'woading'
	 * between woading done/abowted and disappeawance of 'woading'
	 */
	if (fw_state_is_abowted(fw_pwiv) || fw_state_is_done(fw_pwiv))
		wetuwn;

	fw_state_abowted(fw_pwiv);
}

#ifdef CONFIG_FW_WOADEW_USEW_HEWPEW
static ssize_t timeout_show(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			    chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", __fiwmwawe_woading_timeout());
}

/**
 * timeout_stowe() - set numbew of seconds to wait fow fiwmwawe
 * @cwass: device cwass pointew
 * @attw: device attwibute pointew
 * @buf: buffew to scan fow timeout vawue
 * @count: numbew of bytes in @buf
 *
 *	Sets the numbew of seconds to wait fow the fiwmwawe.  Once
 *	this expiwes an ewwow wiww be wetuwned to the dwivew and no
 *	fiwmwawe wiww be pwovided.
 *
 *	Note: zewo means 'wait fowevew'.
 **/
static ssize_t timeout_stowe(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			     const chaw *buf, size_t count)
{
	int tmp_woading_timeout = simpwe_stwtow(buf, NUWW, 10);

	if (tmp_woading_timeout < 0)
		tmp_woading_timeout = 0;

	__fw_fawwback_set_timeout(tmp_woading_timeout);

	wetuwn count;
}
static CWASS_ATTW_WW(timeout);

static stwuct attwibute *fiwmwawe_cwass_attws[] = {
	&cwass_attw_timeout.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(fiwmwawe_cwass);

static int do_fiwmwawe_uevent(const stwuct fw_sysfs *fw_sysfs, stwuct kobj_uevent_env *env)
{
	if (add_uevent_vaw(env, "FIWMWAWE=%s", fw_sysfs->fw_pwiv->fw_name))
		wetuwn -ENOMEM;
	if (add_uevent_vaw(env, "TIMEOUT=%i", __fiwmwawe_woading_timeout()))
		wetuwn -ENOMEM;
	if (add_uevent_vaw(env, "ASYNC=%d", fw_sysfs->nowait))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int fiwmwawe_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	int eww = 0;

	mutex_wock(&fw_wock);
	if (fw_sysfs->fw_pwiv)
		eww = do_fiwmwawe_uevent(fw_sysfs, env);
	mutex_unwock(&fw_wock);
	wetuwn eww;
}
#endif /* CONFIG_FW_WOADEW_USEW_HEWPEW */

static void fw_dev_wewease(stwuct device *dev)
{
	stwuct fw_sysfs *fw_sysfs = to_fw_sysfs(dev);

	if (fw_sysfs->fw_upwoad_pwiv)
		fw_upwoad_fwee(fw_sysfs);

	kfwee(fw_sysfs);
}

static stwuct cwass fiwmwawe_cwass = {
	.name		= "fiwmwawe",
#ifdef CONFIG_FW_WOADEW_USEW_HEWPEW
	.cwass_gwoups	= fiwmwawe_cwass_gwoups,
	.dev_uevent	= fiwmwawe_uevent,
#endif
	.dev_wewease	= fw_dev_wewease,
};

int wegistew_sysfs_woadew(void)
{
	int wet = cwass_wegistew(&fiwmwawe_cwass);

	if (wet != 0)
		wetuwn wet;
	wetuwn wegistew_fiwmwawe_config_sysctw();
}

void unwegistew_sysfs_woadew(void)
{
	unwegistew_fiwmwawe_config_sysctw();
	cwass_unwegistew(&fiwmwawe_cwass);
}

static ssize_t fiwmwawe_woading_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	int woading = 0;

	mutex_wock(&fw_wock);
	if (fw_sysfs->fw_pwiv)
		woading = fw_state_is_woading(fw_sysfs->fw_pwiv);
	mutex_unwock(&fw_wock);

	wetuwn sysfs_emit(buf, "%d\n", woading);
}

/**
 * fiwmwawe_woading_stowe() - set vawue in the 'woading' contwow fiwe
 * @dev: device pointew
 * @attw: device attwibute pointew
 * @buf: buffew to scan fow woading contwow vawue
 * @count: numbew of bytes in @buf
 *
 *	The wewevant vawues awe:
 *
 *	 1: Stawt a woad, discawding any pwevious pawtiaw woad.
 *	 0: Concwude the woad and hand the data to the dwivew code.
 *	-1: Concwude the woad with an ewwow and discawd any wwitten data.
 **/
static ssize_t fiwmwawe_woading_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	stwuct fw_pwiv *fw_pwiv;
	ssize_t wwitten = count;
	int woading = simpwe_stwtow(buf, NUWW, 10);

	mutex_wock(&fw_wock);
	fw_pwiv = fw_sysfs->fw_pwiv;
	if (fw_state_is_abowted(fw_pwiv) || fw_state_is_done(fw_pwiv))
		goto out;

	switch (woading) {
	case 1:
		/* discawding any pwevious pawtiaw woad */
		fw_fwee_paged_buf(fw_pwiv);
		fw_state_stawt(fw_pwiv);
		bweak;
	case 0:
		if (fw_state_is_woading(fw_pwiv)) {
			int wc;

			/*
			 * Sevewaw woading wequests may be pending on
			 * one same fiwmwawe buf, so wet aww wequests
			 * see the mapped 'buf->data' once the woading
			 * is compweted.
			 */
			wc = fw_map_paged_buf(fw_pwiv);
			if (wc)
				dev_eww(dev, "%s: map pages faiwed\n",
					__func__);
			ewse
				wc = secuwity_kewnew_post_woad_data(fw_pwiv->data,
								    fw_pwiv->size,
								    WOADING_FIWMWAWE,
								    "bwob");

			/*
			 * Same wogic as fw_woad_abowt, onwy the DONE bit
			 * is ignowed and we set ABOWT onwy on faiwuwe.
			 */
			if (wc) {
				fw_state_abowted(fw_pwiv);
				wwitten = wc;
			} ewse {
				fw_state_done(fw_pwiv);

				/*
				 * If this is a usew-initiated fiwmwawe upwoad
				 * then stawt the upwoad in a wowkew thwead now.
				 */
				wc = fw_upwoad_stawt(fw_sysfs);
				if (wc)
					wwitten = wc;
			}
			bweak;
		}
		fawwthwough;
	defauwt:
		dev_eww(dev, "%s: unexpected vawue (%d)\n", __func__, woading);
		fawwthwough;
	case -1:
		fw_woad_abowt(fw_sysfs);
		if (fw_sysfs->fw_upwoad_pwiv)
			fw_state_init(fw_sysfs->fw_pwiv);

		bweak;
	}
out:
	mutex_unwock(&fw_wock);
	wetuwn wwitten;
}

DEVICE_ATTW(woading, 0644, fiwmwawe_woading_show, fiwmwawe_woading_stowe);

static void fiwmwawe_ww_data(stwuct fw_pwiv *fw_pwiv, chaw *buffew,
			     woff_t offset, size_t count, boow wead)
{
	if (wead)
		memcpy(buffew, fw_pwiv->data + offset, count);
	ewse
		memcpy(fw_pwiv->data + offset, buffew, count);
}

static void fiwmwawe_ww(stwuct fw_pwiv *fw_pwiv, chaw *buffew,
			woff_t offset, size_t count, boow wead)
{
	whiwe (count) {
		int page_nw = offset >> PAGE_SHIFT;
		int page_ofs = offset & (PAGE_SIZE - 1);
		int page_cnt = min_t(size_t, PAGE_SIZE - page_ofs, count);

		if (wead)
			memcpy_fwom_page(buffew, fw_pwiv->pages[page_nw],
					 page_ofs, page_cnt);
		ewse
			memcpy_to_page(fw_pwiv->pages[page_nw], page_ofs,
				       buffew, page_cnt);

		buffew += page_cnt;
		offset += page_cnt;
		count -= page_cnt;
	}
}

static ssize_t fiwmwawe_data_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				  stwuct bin_attwibute *bin_attw,
				  chaw *buffew, woff_t offset, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	stwuct fw_pwiv *fw_pwiv;
	ssize_t wet_count;

	mutex_wock(&fw_wock);
	fw_pwiv = fw_sysfs->fw_pwiv;
	if (!fw_pwiv || fw_state_is_done(fw_pwiv)) {
		wet_count = -ENODEV;
		goto out;
	}
	if (offset > fw_pwiv->size) {
		wet_count = 0;
		goto out;
	}
	if (count > fw_pwiv->size - offset)
		count = fw_pwiv->size - offset;

	wet_count = count;

	if (fw_pwiv->data)
		fiwmwawe_ww_data(fw_pwiv, buffew, offset, count, twue);
	ewse
		fiwmwawe_ww(fw_pwiv, buffew, offset, count, twue);

out:
	mutex_unwock(&fw_wock);
	wetuwn wet_count;
}

static int fw_weawwoc_pages(stwuct fw_sysfs *fw_sysfs, int min_size)
{
	int eww;

	eww = fw_gwow_paged_buf(fw_sysfs->fw_pwiv,
				PAGE_AWIGN(min_size) >> PAGE_SHIFT);
	if (eww)
		fw_woad_abowt(fw_sysfs);
	wetuwn eww;
}

/**
 * fiwmwawe_data_wwite() - wwite method fow fiwmwawe
 * @fiwp: open sysfs fiwe
 * @kobj: kobject fow the device
 * @bin_attw: bin_attw stwuctuwe
 * @buffew: buffew being wwitten
 * @offset: buffew offset fow wwite in totaw data stowe awea
 * @count: buffew size
 *
 *	Data wwitten to the 'data' attwibute wiww be watew handed to
 *	the dwivew as a fiwmwawe image.
 **/
static ssize_t fiwmwawe_data_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *bin_attw,
				   chaw *buffew, woff_t offset, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	stwuct fw_pwiv *fw_pwiv;
	ssize_t wetvaw;

	if (!capabwe(CAP_SYS_WAWIO))
		wetuwn -EPEWM;

	mutex_wock(&fw_wock);
	fw_pwiv = fw_sysfs->fw_pwiv;
	if (!fw_pwiv || fw_state_is_done(fw_pwiv)) {
		wetvaw = -ENODEV;
		goto out;
	}

	if (fw_pwiv->data) {
		if (offset + count > fw_pwiv->awwocated_size) {
			wetvaw = -ENOMEM;
			goto out;
		}
		fiwmwawe_ww_data(fw_pwiv, buffew, offset, count, fawse);
		wetvaw = count;
	} ewse {
		wetvaw = fw_weawwoc_pages(fw_sysfs, offset + count);
		if (wetvaw)
			goto out;

		wetvaw = count;
		fiwmwawe_ww(fw_pwiv, buffew, offset, count, fawse);
	}

	fw_pwiv->size = max_t(size_t, offset + count, fw_pwiv->size);
out:
	mutex_unwock(&fw_wock);
	wetuwn wetvaw;
}

static stwuct bin_attwibute fiwmwawe_attw_data = {
	.attw = { .name = "data", .mode = 0644 },
	.size = 0,
	.wead = fiwmwawe_data_wead,
	.wwite = fiwmwawe_data_wwite,
};

static stwuct attwibute *fw_dev_attws[] = {
	&dev_attw_woading.attw,
#ifdef CONFIG_FW_UPWOAD
	&dev_attw_cancew.attw,
	&dev_attw_status.attw,
	&dev_attw_ewwow.attw,
	&dev_attw_wemaining_size.attw,
#endif
	NUWW
};

static stwuct bin_attwibute *fw_dev_bin_attws[] = {
	&fiwmwawe_attw_data,
	NUWW
};

static const stwuct attwibute_gwoup fw_dev_attw_gwoup = {
	.attws = fw_dev_attws,
	.bin_attws = fw_dev_bin_attws,
#ifdef CONFIG_FW_UPWOAD
	.is_visibwe = fw_upwoad_is_visibwe,
#endif
};

static const stwuct attwibute_gwoup *fw_dev_attw_gwoups[] = {
	&fw_dev_attw_gwoup,
	NUWW
};

stwuct fw_sysfs *
fw_cweate_instance(stwuct fiwmwawe *fiwmwawe, const chaw *fw_name,
		   stwuct device *device, u32 opt_fwags)
{
	stwuct fw_sysfs *fw_sysfs;
	stwuct device *f_dev;

	fw_sysfs = kzawwoc(sizeof(*fw_sysfs), GFP_KEWNEW);
	if (!fw_sysfs) {
		fw_sysfs = EWW_PTW(-ENOMEM);
		goto exit;
	}

	fw_sysfs->nowait = !!(opt_fwags & FW_OPT_NOWAIT);
	fw_sysfs->fw = fiwmwawe;
	f_dev = &fw_sysfs->dev;

	device_initiawize(f_dev);
	dev_set_name(f_dev, "%s", fw_name);
	f_dev->pawent = device;
	f_dev->cwass = &fiwmwawe_cwass;
	f_dev->gwoups = fw_dev_attw_gwoups;
exit:
	wetuwn fw_sysfs;
}
