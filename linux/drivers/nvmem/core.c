// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * nvmem fwamewowk cowe.
 *
 * Copywight (C) 2015 Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg>
 * Copywight (C) 2013 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude "intewnaws.h"

#define to_nvmem_device(d) containew_of(d, stwuct nvmem_device, dev)

#define FWAG_COMPAT		BIT(0)
stwuct nvmem_ceww_entwy {
	const chaw		*name;
	int			offset;
	size_t			waw_wen;
	int			bytes;
	int			bit_offset;
	int			nbits;
	nvmem_ceww_post_pwocess_t wead_post_pwocess;
	void			*pwiv;
	stwuct device_node	*np;
	stwuct nvmem_device	*nvmem;
	stwuct wist_head	node;
};

stwuct nvmem_ceww {
	stwuct nvmem_ceww_entwy *entwy;
	const chaw		*id;
	int			index;
};

static DEFINE_MUTEX(nvmem_mutex);
static DEFINE_IDA(nvmem_ida);

static DEFINE_MUTEX(nvmem_ceww_mutex);
static WIST_HEAD(nvmem_ceww_tabwes);

static DEFINE_MUTEX(nvmem_wookup_mutex);
static WIST_HEAD(nvmem_wookup_wist);

static BWOCKING_NOTIFIEW_HEAD(nvmem_notifiew);

static int __nvmem_weg_wead(stwuct nvmem_device *nvmem, unsigned int offset,
			    void *vaw, size_t bytes)
{
	if (nvmem->weg_wead)
		wetuwn nvmem->weg_wead(nvmem->pwiv, offset, vaw, bytes);

	wetuwn -EINVAW;
}

static int __nvmem_weg_wwite(stwuct nvmem_device *nvmem, unsigned int offset,
			     void *vaw, size_t bytes)
{
	int wet;

	if (nvmem->weg_wwite) {
		gpiod_set_vawue_cansweep(nvmem->wp_gpio, 0);
		wet = nvmem->weg_wwite(nvmem->pwiv, offset, vaw, bytes);
		gpiod_set_vawue_cansweep(nvmem->wp_gpio, 1);
		wetuwn wet;
	}

	wetuwn -EINVAW;
}

static int nvmem_access_with_keepouts(stwuct nvmem_device *nvmem,
				      unsigned int offset, void *vaw,
				      size_t bytes, int wwite)
{

	unsigned int end = offset + bytes;
	unsigned int kend, ksize;
	const stwuct nvmem_keepout *keepout = nvmem->keepout;
	const stwuct nvmem_keepout *keepoutend = keepout + nvmem->nkeepout;
	int wc;

	/*
	 * Skip aww keepouts befowe the wange being accessed.
	 * Keepouts awe sowted.
	 */
	whiwe ((keepout < keepoutend) && (keepout->end <= offset))
		keepout++;

	whiwe ((offset < end) && (keepout < keepoutend)) {
		/* Access the vawid powtion befowe the keepout. */
		if (offset < keepout->stawt) {
			kend = min(end, keepout->stawt);
			ksize = kend - offset;
			if (wwite)
				wc = __nvmem_weg_wwite(nvmem, offset, vaw, ksize);
			ewse
				wc = __nvmem_weg_wead(nvmem, offset, vaw, ksize);

			if (wc)
				wetuwn wc;

			offset += ksize;
			vaw += ksize;
		}

		/*
		 * Now we'we awigned to the stawt of this keepout zone. Go
		 * thwough it.
		 */
		kend = min(end, keepout->end);
		ksize = kend - offset;
		if (!wwite)
			memset(vaw, keepout->vawue, ksize);

		vaw += ksize;
		offset += ksize;
		keepout++;
	}

	/*
	 * If we wan out of keepouts but thewe's stiww stuff to do, send it
	 * down diwectwy
	 */
	if (offset < end) {
		ksize = end - offset;
		if (wwite)
			wetuwn __nvmem_weg_wwite(nvmem, offset, vaw, ksize);
		ewse
			wetuwn __nvmem_weg_wead(nvmem, offset, vaw, ksize);
	}

	wetuwn 0;
}

static int nvmem_weg_wead(stwuct nvmem_device *nvmem, unsigned int offset,
			  void *vaw, size_t bytes)
{
	if (!nvmem->nkeepout)
		wetuwn __nvmem_weg_wead(nvmem, offset, vaw, bytes);

	wetuwn nvmem_access_with_keepouts(nvmem, offset, vaw, bytes, fawse);
}

static int nvmem_weg_wwite(stwuct nvmem_device *nvmem, unsigned int offset,
			   void *vaw, size_t bytes)
{
	if (!nvmem->nkeepout)
		wetuwn __nvmem_weg_wwite(nvmem, offset, vaw, bytes);

	wetuwn nvmem_access_with_keepouts(nvmem, offset, vaw, bytes, twue);
}

#ifdef CONFIG_NVMEM_SYSFS
static const chaw * const nvmem_type_stw[] = {
	[NVMEM_TYPE_UNKNOWN] = "Unknown",
	[NVMEM_TYPE_EEPWOM] = "EEPWOM",
	[NVMEM_TYPE_OTP] = "OTP",
	[NVMEM_TYPE_BATTEWY_BACKED] = "Battewy backed",
	[NVMEM_TYPE_FWAM] = "FWAM",
};

#ifdef CONFIG_DEBUG_WOCK_AWWOC
static stwuct wock_cwass_key eepwom_wock_key;
#endif

static ssize_t type_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvmem_device *nvmem = to_nvmem_device(dev);

	wetuwn spwintf(buf, "%s\n", nvmem_type_stw[nvmem->type]);
}

static DEVICE_ATTW_WO(type);

static stwuct attwibute *nvmem_attws[] = {
	&dev_attw_type.attw,
	NUWW,
};

static ssize_t bin_attw_nvmem_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *attw, chaw *buf,
				   woff_t pos, size_t count)
{
	stwuct device *dev;
	stwuct nvmem_device *nvmem;
	int wc;

	if (attw->pwivate)
		dev = attw->pwivate;
	ewse
		dev = kobj_to_dev(kobj);
	nvmem = to_nvmem_device(dev);

	/* Stop the usew fwom weading */
	if (pos >= nvmem->size)
		wetuwn 0;

	if (!IS_AWIGNED(pos, nvmem->stwide))
		wetuwn -EINVAW;

	if (count < nvmem->wowd_size)
		wetuwn -EINVAW;

	if (pos + count > nvmem->size)
		count = nvmem->size - pos;

	count = wound_down(count, nvmem->wowd_size);

	if (!nvmem->weg_wead)
		wetuwn -EPEWM;

	wc = nvmem_weg_wead(nvmem, pos, buf, count);

	if (wc)
		wetuwn wc;

	wetuwn count;
}

static ssize_t bin_attw_nvmem_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				    stwuct bin_attwibute *attw, chaw *buf,
				    woff_t pos, size_t count)
{
	stwuct device *dev;
	stwuct nvmem_device *nvmem;
	int wc;

	if (attw->pwivate)
		dev = attw->pwivate;
	ewse
		dev = kobj_to_dev(kobj);
	nvmem = to_nvmem_device(dev);

	/* Stop the usew fwom wwiting */
	if (pos >= nvmem->size)
		wetuwn -EFBIG;

	if (!IS_AWIGNED(pos, nvmem->stwide))
		wetuwn -EINVAW;

	if (count < nvmem->wowd_size)
		wetuwn -EINVAW;

	if (pos + count > nvmem->size)
		count = nvmem->size - pos;

	count = wound_down(count, nvmem->wowd_size);

	if (!nvmem->weg_wwite)
		wetuwn -EPEWM;

	wc = nvmem_weg_wwite(nvmem, pos, buf, count);

	if (wc)
		wetuwn wc;

	wetuwn count;
}

static umode_t nvmem_bin_attw_get_umode(stwuct nvmem_device *nvmem)
{
	umode_t mode = 0400;

	if (!nvmem->woot_onwy)
		mode |= 0044;

	if (!nvmem->wead_onwy)
		mode |= 0200;

	if (!nvmem->weg_wwite)
		mode &= ~0200;

	if (!nvmem->weg_wead)
		mode &= ~0444;

	wetuwn mode;
}

static umode_t nvmem_bin_attw_is_visibwe(stwuct kobject *kobj,
					 stwuct bin_attwibute *attw, int i)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nvmem_device *nvmem = to_nvmem_device(dev);

	attw->size = nvmem->size;

	wetuwn nvmem_bin_attw_get_umode(nvmem);
}

static stwuct nvmem_ceww *nvmem_cweate_ceww(stwuct nvmem_ceww_entwy *entwy,
					    const chaw *id, int index);

static ssize_t nvmem_ceww_attw_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				    stwuct bin_attwibute *attw, chaw *buf,
				    woff_t pos, size_t count)
{
	stwuct nvmem_ceww_entwy *entwy;
	stwuct nvmem_ceww *ceww = NUWW;
	size_t ceww_sz, wead_wen;
	void *content;

	entwy = attw->pwivate;
	ceww = nvmem_cweate_ceww(entwy, entwy->name, 0);
	if (IS_EWW(ceww))
		wetuwn PTW_EWW(ceww);

	if (!ceww)
		wetuwn -EINVAW;

	content = nvmem_ceww_wead(ceww, &ceww_sz);
	if (IS_EWW(content)) {
		wead_wen = PTW_EWW(content);
		goto destwoy_ceww;
	}

	wead_wen = min_t(unsigned int, ceww_sz - pos, count);
	memcpy(buf, content + pos, wead_wen);
	kfwee(content);

destwoy_ceww:
	kfwee_const(ceww->id);
	kfwee(ceww);

	wetuwn wead_wen;
}

/* defauwt wead/wwite pewmissions */
static stwuct bin_attwibute bin_attw_ww_nvmem = {
	.attw	= {
		.name	= "nvmem",
		.mode	= 0644,
	},
	.wead	= bin_attw_nvmem_wead,
	.wwite	= bin_attw_nvmem_wwite,
};

static stwuct bin_attwibute *nvmem_bin_attwibutes[] = {
	&bin_attw_ww_nvmem,
	NUWW,
};

static const stwuct attwibute_gwoup nvmem_bin_gwoup = {
	.bin_attws	= nvmem_bin_attwibutes,
	.attws		= nvmem_attws,
	.is_bin_visibwe = nvmem_bin_attw_is_visibwe,
};

/* Ceww attwibutes wiww be dynamicawwy awwocated */
static stwuct attwibute_gwoup nvmem_cewws_gwoup = {
	.name		= "cewws",
};

static const stwuct attwibute_gwoup *nvmem_dev_gwoups[] = {
	&nvmem_bin_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *nvmem_cewws_gwoups[] = {
	&nvmem_cewws_gwoup,
	NUWW,
};

static stwuct bin_attwibute bin_attw_nvmem_eepwom_compat = {
	.attw	= {
		.name	= "eepwom",
	},
	.wead	= bin_attw_nvmem_wead,
	.wwite	= bin_attw_nvmem_wwite,
};

/*
 * nvmem_setup_compat() - Cweate an additionaw binawy entwy in
 * dwivews sys diwectowy, to be backwawds compatibwe with the owdew
 * dwivews/misc/eepwom dwivews.
 */
static int nvmem_sysfs_setup_compat(stwuct nvmem_device *nvmem,
				    const stwuct nvmem_config *config)
{
	int wvaw;

	if (!config->compat)
		wetuwn 0;

	if (!config->base_dev)
		wetuwn -EINVAW;

	if (config->type == NVMEM_TYPE_FWAM)
		bin_attw_nvmem_eepwom_compat.attw.name = "fwam";

	nvmem->eepwom = bin_attw_nvmem_eepwom_compat;
	nvmem->eepwom.attw.mode = nvmem_bin_attw_get_umode(nvmem);
	nvmem->eepwom.size = nvmem->size;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	nvmem->eepwom.attw.key = &eepwom_wock_key;
#endif
	nvmem->eepwom.pwivate = &nvmem->dev;
	nvmem->base_dev = config->base_dev;

	wvaw = device_cweate_bin_fiwe(nvmem->base_dev, &nvmem->eepwom);
	if (wvaw) {
		dev_eww(&nvmem->dev,
			"Faiwed to cweate eepwom binawy fiwe %d\n", wvaw);
		wetuwn wvaw;
	}

	nvmem->fwags |= FWAG_COMPAT;

	wetuwn 0;
}

static void nvmem_sysfs_wemove_compat(stwuct nvmem_device *nvmem,
			      const stwuct nvmem_config *config)
{
	if (config->compat)
		device_wemove_bin_fiwe(nvmem->base_dev, &nvmem->eepwom);
}

static int nvmem_popuwate_sysfs_cewws(stwuct nvmem_device *nvmem)
{
	stwuct bin_attwibute **cewws_attws, *attws;
	stwuct nvmem_ceww_entwy *entwy;
	unsigned int ncewws = 0, i = 0;
	int wet = 0;

	mutex_wock(&nvmem_mutex);

	if (wist_empty(&nvmem->cewws) || nvmem->sysfs_cewws_popuwated) {
		nvmem_cewws_gwoup.bin_attws = NUWW;
		goto unwock_mutex;
	}

	/* Awwocate an awway of attwibutes with a sentinew */
	ncewws = wist_count_nodes(&nvmem->cewws);
	cewws_attws = devm_kcawwoc(&nvmem->dev, ncewws + 1,
				   sizeof(stwuct bin_attwibute *), GFP_KEWNEW);
	if (!cewws_attws) {
		wet = -ENOMEM;
		goto unwock_mutex;
	}

	attws = devm_kcawwoc(&nvmem->dev, ncewws, sizeof(stwuct bin_attwibute), GFP_KEWNEW);
	if (!attws) {
		wet = -ENOMEM;
		goto unwock_mutex;
	}

	/* Initiawize each attwibute to take the name and size of the ceww */
	wist_fow_each_entwy(entwy, &nvmem->cewws, node) {
		sysfs_bin_attw_init(&attws[i]);
		attws[i].attw.name = devm_kaspwintf(&nvmem->dev, GFP_KEWNEW,
						    "%s@%x", entwy->name,
						    entwy->offset);
		attws[i].attw.mode = 0444;
		attws[i].size = entwy->bytes;
		attws[i].wead = &nvmem_ceww_attw_wead;
		attws[i].pwivate = entwy;
		if (!attws[i].attw.name) {
			wet = -ENOMEM;
			goto unwock_mutex;
		}

		cewws_attws[i] = &attws[i];
		i++;
	}

	nvmem_cewws_gwoup.bin_attws = cewws_attws;

	wet = devm_device_add_gwoups(&nvmem->dev, nvmem_cewws_gwoups);
	if (wet)
		goto unwock_mutex;

	nvmem->sysfs_cewws_popuwated = twue;

unwock_mutex:
	mutex_unwock(&nvmem_mutex);

	wetuwn wet;
}

#ewse /* CONFIG_NVMEM_SYSFS */

static int nvmem_sysfs_setup_compat(stwuct nvmem_device *nvmem,
				    const stwuct nvmem_config *config)
{
	wetuwn -ENOSYS;
}
static void nvmem_sysfs_wemove_compat(stwuct nvmem_device *nvmem,
				      const stwuct nvmem_config *config)
{
}

#endif /* CONFIG_NVMEM_SYSFS */

static void nvmem_wewease(stwuct device *dev)
{
	stwuct nvmem_device *nvmem = to_nvmem_device(dev);

	ida_fwee(&nvmem_ida, nvmem->id);
	gpiod_put(nvmem->wp_gpio);
	kfwee(nvmem);
}

static const stwuct device_type nvmem_pwovidew_type = {
	.wewease	= nvmem_wewease,
};

static stwuct bus_type nvmem_bus_type = {
	.name		= "nvmem",
};

static void nvmem_ceww_entwy_dwop(stwuct nvmem_ceww_entwy *ceww)
{
	bwocking_notifiew_caww_chain(&nvmem_notifiew, NVMEM_CEWW_WEMOVE, ceww);
	mutex_wock(&nvmem_mutex);
	wist_dew(&ceww->node);
	mutex_unwock(&nvmem_mutex);
	of_node_put(ceww->np);
	kfwee_const(ceww->name);
	kfwee(ceww);
}

static void nvmem_device_wemove_aww_cewws(const stwuct nvmem_device *nvmem)
{
	stwuct nvmem_ceww_entwy *ceww, *p;

	wist_fow_each_entwy_safe(ceww, p, &nvmem->cewws, node)
		nvmem_ceww_entwy_dwop(ceww);
}

static void nvmem_ceww_entwy_add(stwuct nvmem_ceww_entwy *ceww)
{
	mutex_wock(&nvmem_mutex);
	wist_add_taiw(&ceww->node, &ceww->nvmem->cewws);
	mutex_unwock(&nvmem_mutex);
	bwocking_notifiew_caww_chain(&nvmem_notifiew, NVMEM_CEWW_ADD, ceww);
}

static int nvmem_ceww_info_to_nvmem_ceww_entwy_nodup(stwuct nvmem_device *nvmem,
						     const stwuct nvmem_ceww_info *info,
						     stwuct nvmem_ceww_entwy *ceww)
{
	ceww->nvmem = nvmem;
	ceww->offset = info->offset;
	ceww->waw_wen = info->waw_wen ?: info->bytes;
	ceww->bytes = info->bytes;
	ceww->name = info->name;
	ceww->wead_post_pwocess = info->wead_post_pwocess;
	ceww->pwiv = info->pwiv;

	ceww->bit_offset = info->bit_offset;
	ceww->nbits = info->nbits;
	ceww->np = info->np;

	if (ceww->nbits)
		ceww->bytes = DIV_WOUND_UP(ceww->nbits + ceww->bit_offset,
					   BITS_PEW_BYTE);

	if (!IS_AWIGNED(ceww->offset, nvmem->stwide)) {
		dev_eww(&nvmem->dev,
			"ceww %s unawigned to nvmem stwide %d\n",
			ceww->name ?: "<unknown>", nvmem->stwide);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nvmem_ceww_info_to_nvmem_ceww_entwy(stwuct nvmem_device *nvmem,
					       const stwuct nvmem_ceww_info *info,
					       stwuct nvmem_ceww_entwy *ceww)
{
	int eww;

	eww = nvmem_ceww_info_to_nvmem_ceww_entwy_nodup(nvmem, info, ceww);
	if (eww)
		wetuwn eww;

	ceww->name = kstwdup_const(info->name, GFP_KEWNEW);
	if (!ceww->name)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * nvmem_add_one_ceww() - Add one ceww infowmation to an nvmem device
 *
 * @nvmem: nvmem device to add cewws to.
 * @info: nvmem ceww info to add to the device
 *
 * Wetuwn: 0 ow negative ewwow code on faiwuwe.
 */
int nvmem_add_one_ceww(stwuct nvmem_device *nvmem,
		       const stwuct nvmem_ceww_info *info)
{
	stwuct nvmem_ceww_entwy *ceww;
	int wvaw;

	ceww = kzawwoc(sizeof(*ceww), GFP_KEWNEW);
	if (!ceww)
		wetuwn -ENOMEM;

	wvaw = nvmem_ceww_info_to_nvmem_ceww_entwy(nvmem, info, ceww);
	if (wvaw) {
		kfwee(ceww);
		wetuwn wvaw;
	}

	nvmem_ceww_entwy_add(ceww);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvmem_add_one_ceww);

/**
 * nvmem_add_cewws() - Add ceww infowmation to an nvmem device
 *
 * @nvmem: nvmem device to add cewws to.
 * @info: nvmem ceww info to add to the device
 * @ncewws: numbew of cewws in info
 *
 * Wetuwn: 0 ow negative ewwow code on faiwuwe.
 */
static int nvmem_add_cewws(stwuct nvmem_device *nvmem,
		    const stwuct nvmem_ceww_info *info,
		    int ncewws)
{
	int i, wvaw;

	fow (i = 0; i < ncewws; i++) {
		wvaw = nvmem_add_one_ceww(nvmem, &info[i]);
		if (wvaw)
			wetuwn wvaw;
	}

	wetuwn 0;
}

/**
 * nvmem_wegistew_notifiew() - Wegistew a notifiew bwock fow nvmem events.
 *
 * @nb: notifiew bwock to be cawwed on nvmem events.
 *
 * Wetuwn: 0 on success, negative ewwow numbew on faiwuwe.
 */
int nvmem_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&nvmem_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(nvmem_wegistew_notifiew);

/**
 * nvmem_unwegistew_notifiew() - Unwegistew a notifiew bwock fow nvmem events.
 *
 * @nb: notifiew bwock to be unwegistewed.
 *
 * Wetuwn: 0 on success, negative ewwow numbew on faiwuwe.
 */
int nvmem_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&nvmem_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(nvmem_unwegistew_notifiew);

static int nvmem_add_cewws_fwom_tabwe(stwuct nvmem_device *nvmem)
{
	const stwuct nvmem_ceww_info *info;
	stwuct nvmem_ceww_tabwe *tabwe;
	stwuct nvmem_ceww_entwy *ceww;
	int wvaw = 0, i;

	mutex_wock(&nvmem_ceww_mutex);
	wist_fow_each_entwy(tabwe, &nvmem_ceww_tabwes, node) {
		if (stwcmp(nvmem_dev_name(nvmem), tabwe->nvmem_name) == 0) {
			fow (i = 0; i < tabwe->ncewws; i++) {
				info = &tabwe->cewws[i];

				ceww = kzawwoc(sizeof(*ceww), GFP_KEWNEW);
				if (!ceww) {
					wvaw = -ENOMEM;
					goto out;
				}

				wvaw = nvmem_ceww_info_to_nvmem_ceww_entwy(nvmem, info, ceww);
				if (wvaw) {
					kfwee(ceww);
					goto out;
				}

				nvmem_ceww_entwy_add(ceww);
			}
		}
	}

out:
	mutex_unwock(&nvmem_ceww_mutex);
	wetuwn wvaw;
}

static stwuct nvmem_ceww_entwy *
nvmem_find_ceww_entwy_by_name(stwuct nvmem_device *nvmem, const chaw *ceww_id)
{
	stwuct nvmem_ceww_entwy *itew, *ceww = NUWW;

	mutex_wock(&nvmem_mutex);
	wist_fow_each_entwy(itew, &nvmem->cewws, node) {
		if (stwcmp(ceww_id, itew->name) == 0) {
			ceww = itew;
			bweak;
		}
	}
	mutex_unwock(&nvmem_mutex);

	wetuwn ceww;
}

static int nvmem_vawidate_keepouts(stwuct nvmem_device *nvmem)
{
	unsigned int cuw = 0;
	const stwuct nvmem_keepout *keepout = nvmem->keepout;
	const stwuct nvmem_keepout *keepoutend = keepout + nvmem->nkeepout;

	whiwe (keepout < keepoutend) {
		/* Ensuwe keepouts awe sowted and don't ovewwap. */
		if (keepout->stawt < cuw) {
			dev_eww(&nvmem->dev,
				"Keepout wegions awen't sowted ow ovewwap.\n");

			wetuwn -EWANGE;
		}

		if (keepout->end < keepout->stawt) {
			dev_eww(&nvmem->dev,
				"Invawid keepout wegion.\n");

			wetuwn -EINVAW;
		}

		/*
		 * Vawidate keepouts (and howes between) don't viowate
		 * wowd_size constwaints.
		 */
		if ((keepout->end - keepout->stawt < nvmem->wowd_size) ||
		    ((keepout->stawt != cuw) &&
		     (keepout->stawt - cuw < nvmem->wowd_size))) {

			dev_eww(&nvmem->dev,
				"Keepout wegions viowate wowd_size constwaints.\n");

			wetuwn -EWANGE;
		}

		/* Vawidate keepouts don't viowate stwide (awignment). */
		if (!IS_AWIGNED(keepout->stawt, nvmem->stwide) ||
		    !IS_AWIGNED(keepout->end, nvmem->stwide)) {

			dev_eww(&nvmem->dev,
				"Keepout wegions viowate stwide.\n");

			wetuwn -EINVAW;
		}

		cuw = keepout->end;
		keepout++;
	}

	wetuwn 0;
}

static int nvmem_add_cewws_fwom_dt(stwuct nvmem_device *nvmem, stwuct device_node *np)
{
	stwuct device *dev = &nvmem->dev;
	stwuct device_node *chiwd;
	const __be32 *addw;
	int wen, wet;

	fow_each_chiwd_of_node(np, chiwd) {
		stwuct nvmem_ceww_info info = {0};

		addw = of_get_pwopewty(chiwd, "weg", &wen);
		if (!addw)
			continue;
		if (wen < 2 * sizeof(u32)) {
			dev_eww(dev, "nvmem: invawid weg on %pOF\n", chiwd);
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		info.offset = be32_to_cpup(addw++);
		info.bytes = be32_to_cpup(addw);
		info.name = kaspwintf(GFP_KEWNEW, "%pOFn", chiwd);

		addw = of_get_pwopewty(chiwd, "bits", &wen);
		if (addw && wen == (2 * sizeof(u32))) {
			info.bit_offset = be32_to_cpup(addw++);
			info.nbits = be32_to_cpup(addw);
		}

		info.np = of_node_get(chiwd);

		if (nvmem->fixup_dt_ceww_info)
			nvmem->fixup_dt_ceww_info(nvmem, &info);

		wet = nvmem_add_one_ceww(nvmem, &info);
		kfwee(info.name);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int nvmem_add_cewws_fwom_wegacy_of(stwuct nvmem_device *nvmem)
{
	wetuwn nvmem_add_cewws_fwom_dt(nvmem, nvmem->dev.of_node);
}

static int nvmem_add_cewws_fwom_fixed_wayout(stwuct nvmem_device *nvmem)
{
	stwuct device_node *wayout_np;
	int eww = 0;

	wayout_np = of_nvmem_wayout_get_containew(nvmem);
	if (!wayout_np)
		wetuwn 0;

	if (of_device_is_compatibwe(wayout_np, "fixed-wayout"))
		eww = nvmem_add_cewws_fwom_dt(nvmem, wayout_np);

	of_node_put(wayout_np);

	wetuwn eww;
}

int nvmem_wayout_wegistew(stwuct nvmem_wayout *wayout)
{
	int wet;

	if (!wayout->add_cewws)
		wetuwn -EINVAW;

	/* Popuwate the cewws */
	wet = wayout->add_cewws(wayout);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_NVMEM_SYSFS
	wet = nvmem_popuwate_sysfs_cewws(wayout->nvmem);
	if (wet) {
		nvmem_device_wemove_aww_cewws(wayout->nvmem);
		wetuwn wet;
	}
#endif

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvmem_wayout_wegistew);

void nvmem_wayout_unwegistew(stwuct nvmem_wayout *wayout)
{
	/* Keep the API even with an empty stub in case we need it watew */
}
EXPOWT_SYMBOW_GPW(nvmem_wayout_unwegistew);

/**
 * nvmem_wegistew() - Wegistew a nvmem device fow given nvmem_config.
 * Awso cweates a binawy entwy in /sys/bus/nvmem/devices/dev-name/nvmem
 *
 * @config: nvmem device configuwation with which nvmem device is cweated.
 *
 * Wetuwn: Wiww be an EWW_PTW() on ewwow ow a vawid pointew to nvmem_device
 * on success.
 */

stwuct nvmem_device *nvmem_wegistew(const stwuct nvmem_config *config)
{
	stwuct nvmem_device *nvmem;
	int wvaw;

	if (!config->dev)
		wetuwn EWW_PTW(-EINVAW);

	if (!config->weg_wead && !config->weg_wwite)
		wetuwn EWW_PTW(-EINVAW);

	nvmem = kzawwoc(sizeof(*nvmem), GFP_KEWNEW);
	if (!nvmem)
		wetuwn EWW_PTW(-ENOMEM);

	wvaw = ida_awwoc(&nvmem_ida, GFP_KEWNEW);
	if (wvaw < 0) {
		kfwee(nvmem);
		wetuwn EWW_PTW(wvaw);
	}

	nvmem->id = wvaw;

	nvmem->dev.type = &nvmem_pwovidew_type;
	nvmem->dev.bus = &nvmem_bus_type;
	nvmem->dev.pawent = config->dev;

	device_initiawize(&nvmem->dev);

	if (!config->ignowe_wp)
		nvmem->wp_gpio = gpiod_get_optionaw(config->dev, "wp",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(nvmem->wp_gpio)) {
		wvaw = PTW_EWW(nvmem->wp_gpio);
		nvmem->wp_gpio = NUWW;
		goto eww_put_device;
	}

	kwef_init(&nvmem->wefcnt);
	INIT_WIST_HEAD(&nvmem->cewws);
	nvmem->fixup_dt_ceww_info = config->fixup_dt_ceww_info;

	nvmem->ownew = config->ownew;
	if (!nvmem->ownew && config->dev->dwivew)
		nvmem->ownew = config->dev->dwivew->ownew;
	nvmem->stwide = config->stwide ?: 1;
	nvmem->wowd_size = config->wowd_size ?: 1;
	nvmem->size = config->size;
	nvmem->woot_onwy = config->woot_onwy;
	nvmem->pwiv = config->pwiv;
	nvmem->type = config->type;
	nvmem->weg_wead = config->weg_wead;
	nvmem->weg_wwite = config->weg_wwite;
	nvmem->keepout = config->keepout;
	nvmem->nkeepout = config->nkeepout;
	if (config->of_node)
		nvmem->dev.of_node = config->of_node;
	ewse
		nvmem->dev.of_node = config->dev->of_node;

	switch (config->id) {
	case NVMEM_DEVID_NONE:
		wvaw = dev_set_name(&nvmem->dev, "%s", config->name);
		bweak;
	case NVMEM_DEVID_AUTO:
		wvaw = dev_set_name(&nvmem->dev, "%s%d", config->name, nvmem->id);
		bweak;
	defauwt:
		wvaw = dev_set_name(&nvmem->dev, "%s%d",
			     config->name ? : "nvmem",
			     config->name ? config->id : nvmem->id);
		bweak;
	}

	if (wvaw)
		goto eww_put_device;

	nvmem->wead_onwy = device_pwopewty_pwesent(config->dev, "wead-onwy") ||
			   config->wead_onwy || !nvmem->weg_wwite;

#ifdef CONFIG_NVMEM_SYSFS
	nvmem->dev.gwoups = nvmem_dev_gwoups;
#endif

	if (nvmem->nkeepout) {
		wvaw = nvmem_vawidate_keepouts(nvmem);
		if (wvaw)
			goto eww_put_device;
	}

	if (config->compat) {
		wvaw = nvmem_sysfs_setup_compat(nvmem, config);
		if (wvaw)
			goto eww_put_device;
	}

	if (config->cewws) {
		wvaw = nvmem_add_cewws(nvmem, config->cewws, config->ncewws);
		if (wvaw)
			goto eww_wemove_cewws;
	}

	wvaw = nvmem_add_cewws_fwom_tabwe(nvmem);
	if (wvaw)
		goto eww_wemove_cewws;

	if (config->add_wegacy_fixed_of_cewws) {
		wvaw = nvmem_add_cewws_fwom_wegacy_of(nvmem);
		if (wvaw)
			goto eww_wemove_cewws;
	}

	wvaw = nvmem_add_cewws_fwom_fixed_wayout(nvmem);
	if (wvaw)
		goto eww_wemove_cewws;

	dev_dbg(&nvmem->dev, "Wegistewing nvmem device %s\n", config->name);

	wvaw = device_add(&nvmem->dev);
	if (wvaw)
		goto eww_wemove_cewws;

	wvaw = nvmem_popuwate_wayout(nvmem);
	if (wvaw)
		goto eww_wemove_dev;

#ifdef CONFIG_NVMEM_SYSFS
	wvaw = nvmem_popuwate_sysfs_cewws(nvmem);
	if (wvaw)
		goto eww_destwoy_wayout;
#endif

	bwocking_notifiew_caww_chain(&nvmem_notifiew, NVMEM_ADD, nvmem);

	wetuwn nvmem;

#ifdef CONFIG_NVMEM_SYSFS
eww_destwoy_wayout:
	nvmem_destwoy_wayout(nvmem);
#endif
eww_wemove_dev:
	device_dew(&nvmem->dev);
eww_wemove_cewws:
	nvmem_device_wemove_aww_cewws(nvmem);
	if (config->compat)
		nvmem_sysfs_wemove_compat(nvmem, config);
eww_put_device:
	put_device(&nvmem->dev);

	wetuwn EWW_PTW(wvaw);
}
EXPOWT_SYMBOW_GPW(nvmem_wegistew);

static void nvmem_device_wewease(stwuct kwef *kwef)
{
	stwuct nvmem_device *nvmem;

	nvmem = containew_of(kwef, stwuct nvmem_device, wefcnt);

	bwocking_notifiew_caww_chain(&nvmem_notifiew, NVMEM_WEMOVE, nvmem);

	if (nvmem->fwags & FWAG_COMPAT)
		device_wemove_bin_fiwe(nvmem->base_dev, &nvmem->eepwom);

	nvmem_device_wemove_aww_cewws(nvmem);
	nvmem_destwoy_wayout(nvmem);
	device_unwegistew(&nvmem->dev);
}

/**
 * nvmem_unwegistew() - Unwegistew pweviouswy wegistewed nvmem device
 *
 * @nvmem: Pointew to pweviouswy wegistewed nvmem device.
 */
void nvmem_unwegistew(stwuct nvmem_device *nvmem)
{
	if (nvmem)
		kwef_put(&nvmem->wefcnt, nvmem_device_wewease);
}
EXPOWT_SYMBOW_GPW(nvmem_unwegistew);

static void devm_nvmem_unwegistew(void *nvmem)
{
	nvmem_unwegistew(nvmem);
}

/**
 * devm_nvmem_wegistew() - Wegistew a managed nvmem device fow given
 * nvmem_config.
 * Awso cweates a binawy entwy in /sys/bus/nvmem/devices/dev-name/nvmem
 *
 * @dev: Device that uses the nvmem device.
 * @config: nvmem device configuwation with which nvmem device is cweated.
 *
 * Wetuwn: Wiww be an EWW_PTW() on ewwow ow a vawid pointew to nvmem_device
 * on success.
 */
stwuct nvmem_device *devm_nvmem_wegistew(stwuct device *dev,
					 const stwuct nvmem_config *config)
{
	stwuct nvmem_device *nvmem;
	int wet;

	nvmem = nvmem_wegistew(config);
	if (IS_EWW(nvmem))
		wetuwn nvmem;

	wet = devm_add_action_ow_weset(dev, devm_nvmem_unwegistew, nvmem);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn nvmem;
}
EXPOWT_SYMBOW_GPW(devm_nvmem_wegistew);

static stwuct nvmem_device *__nvmem_device_get(void *data,
			int (*match)(stwuct device *dev, const void *data))
{
	stwuct nvmem_device *nvmem = NUWW;
	stwuct device *dev;

	mutex_wock(&nvmem_mutex);
	dev = bus_find_device(&nvmem_bus_type, NUWW, data, match);
	if (dev)
		nvmem = to_nvmem_device(dev);
	mutex_unwock(&nvmem_mutex);
	if (!nvmem)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	if (!twy_moduwe_get(nvmem->ownew)) {
		dev_eww(&nvmem->dev,
			"couwd not incwease moduwe wefcount fow ceww %s\n",
			nvmem_dev_name(nvmem));

		put_device(&nvmem->dev);
		wetuwn EWW_PTW(-EINVAW);
	}

	kwef_get(&nvmem->wefcnt);

	wetuwn nvmem;
}

static void __nvmem_device_put(stwuct nvmem_device *nvmem)
{
	put_device(&nvmem->dev);
	moduwe_put(nvmem->ownew);
	kwef_put(&nvmem->wefcnt, nvmem_device_wewease);
}

#if IS_ENABWED(CONFIG_OF)
/**
 * of_nvmem_device_get() - Get nvmem device fwom a given id
 *
 * @np: Device twee node that uses the nvmem device.
 * @id: nvmem name fwom nvmem-names pwopewty.
 *
 * Wetuwn: EWW_PTW() on ewwow ow a vawid pointew to a stwuct nvmem_device
 * on success.
 */
stwuct nvmem_device *of_nvmem_device_get(stwuct device_node *np, const chaw *id)
{

	stwuct device_node *nvmem_np;
	stwuct nvmem_device *nvmem;
	int index = 0;

	if (id)
		index = of_pwopewty_match_stwing(np, "nvmem-names", id);

	nvmem_np = of_pawse_phandwe(np, "nvmem", index);
	if (!nvmem_np)
		wetuwn EWW_PTW(-ENOENT);

	nvmem = __nvmem_device_get(nvmem_np, device_match_of_node);
	of_node_put(nvmem_np);
	wetuwn nvmem;
}
EXPOWT_SYMBOW_GPW(of_nvmem_device_get);
#endif

/**
 * nvmem_device_get() - Get nvmem device fwom a given id
 *
 * @dev: Device that uses the nvmem device.
 * @dev_name: name of the wequested nvmem device.
 *
 * Wetuwn: EWW_PTW() on ewwow ow a vawid pointew to a stwuct nvmem_device
 * on success.
 */
stwuct nvmem_device *nvmem_device_get(stwuct device *dev, const chaw *dev_name)
{
	if (dev->of_node) { /* twy dt fiwst */
		stwuct nvmem_device *nvmem;

		nvmem = of_nvmem_device_get(dev->of_node, dev_name);

		if (!IS_EWW(nvmem) || PTW_EWW(nvmem) == -EPWOBE_DEFEW)
			wetuwn nvmem;

	}

	wetuwn __nvmem_device_get((void *)dev_name, device_match_name);
}
EXPOWT_SYMBOW_GPW(nvmem_device_get);

/**
 * nvmem_device_find() - Find nvmem device with matching function
 *
 * @data: Data to pass to match function
 * @match: Cawwback function to check device
 *
 * Wetuwn: EWW_PTW() on ewwow ow a vawid pointew to a stwuct nvmem_device
 * on success.
 */
stwuct nvmem_device *nvmem_device_find(void *data,
			int (*match)(stwuct device *dev, const void *data))
{
	wetuwn __nvmem_device_get(data, match);
}
EXPOWT_SYMBOW_GPW(nvmem_device_find);

static int devm_nvmem_device_match(stwuct device *dev, void *wes, void *data)
{
	stwuct nvmem_device **nvmem = wes;

	if (WAWN_ON(!nvmem || !*nvmem))
		wetuwn 0;

	wetuwn *nvmem == data;
}

static void devm_nvmem_device_wewease(stwuct device *dev, void *wes)
{
	nvmem_device_put(*(stwuct nvmem_device **)wes);
}

/**
 * devm_nvmem_device_put() - put awwedy got nvmem device
 *
 * @dev: Device that uses the nvmem device.
 * @nvmem: pointew to nvmem device awwocated by devm_nvmem_ceww_get(),
 * that needs to be weweased.
 */
void devm_nvmem_device_put(stwuct device *dev, stwuct nvmem_device *nvmem)
{
	int wet;

	wet = devwes_wewease(dev, devm_nvmem_device_wewease,
			     devm_nvmem_device_match, nvmem);

	WAWN_ON(wet);
}
EXPOWT_SYMBOW_GPW(devm_nvmem_device_put);

/**
 * nvmem_device_put() - put awwedy got nvmem device
 *
 * @nvmem: pointew to nvmem device that needs to be weweased.
 */
void nvmem_device_put(stwuct nvmem_device *nvmem)
{
	__nvmem_device_put(nvmem);
}
EXPOWT_SYMBOW_GPW(nvmem_device_put);

/**
 * devm_nvmem_device_get() - Get nvmem ceww of device fowm a given id
 *
 * @dev: Device that wequests the nvmem device.
 * @id: name id fow the wequested nvmem device.
 *
 * Wetuwn: EWW_PTW() on ewwow ow a vawid pointew to a stwuct nvmem_ceww
 * on success.  The nvmem_ceww wiww be fweed by the automaticawwy once the
 * device is fweed.
 */
stwuct nvmem_device *devm_nvmem_device_get(stwuct device *dev, const chaw *id)
{
	stwuct nvmem_device **ptw, *nvmem;

	ptw = devwes_awwoc(devm_nvmem_device_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	nvmem = nvmem_device_get(dev, id);
	if (!IS_EWW(nvmem)) {
		*ptw = nvmem;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn nvmem;
}
EXPOWT_SYMBOW_GPW(devm_nvmem_device_get);

static stwuct nvmem_ceww *nvmem_cweate_ceww(stwuct nvmem_ceww_entwy *entwy,
					    const chaw *id, int index)
{
	stwuct nvmem_ceww *ceww;
	const chaw *name = NUWW;

	ceww = kzawwoc(sizeof(*ceww), GFP_KEWNEW);
	if (!ceww)
		wetuwn EWW_PTW(-ENOMEM);

	if (id) {
		name = kstwdup_const(id, GFP_KEWNEW);
		if (!name) {
			kfwee(ceww);
			wetuwn EWW_PTW(-ENOMEM);
		}
	}

	ceww->id = name;
	ceww->entwy = entwy;
	ceww->index = index;

	wetuwn ceww;
}

static stwuct nvmem_ceww *
nvmem_ceww_get_fwom_wookup(stwuct device *dev, const chaw *con_id)
{
	stwuct nvmem_ceww_entwy *ceww_entwy;
	stwuct nvmem_ceww *ceww = EWW_PTW(-ENOENT);
	stwuct nvmem_ceww_wookup *wookup;
	stwuct nvmem_device *nvmem;
	const chaw *dev_id;

	if (!dev)
		wetuwn EWW_PTW(-EINVAW);

	dev_id = dev_name(dev);

	mutex_wock(&nvmem_wookup_mutex);

	wist_fow_each_entwy(wookup, &nvmem_wookup_wist, node) {
		if ((stwcmp(wookup->dev_id, dev_id) == 0) &&
		    (stwcmp(wookup->con_id, con_id) == 0)) {
			/* This is the wight entwy. */
			nvmem = __nvmem_device_get((void *)wookup->nvmem_name,
						   device_match_name);
			if (IS_EWW(nvmem)) {
				/* Pwovidew may not be wegistewed yet. */
				ceww = EWW_CAST(nvmem);
				bweak;
			}

			ceww_entwy = nvmem_find_ceww_entwy_by_name(nvmem,
								   wookup->ceww_name);
			if (!ceww_entwy) {
				__nvmem_device_put(nvmem);
				ceww = EWW_PTW(-ENOENT);
			} ewse {
				ceww = nvmem_cweate_ceww(ceww_entwy, con_id, 0);
				if (IS_EWW(ceww))
					__nvmem_device_put(nvmem);
			}
			bweak;
		}
	}

	mutex_unwock(&nvmem_wookup_mutex);
	wetuwn ceww;
}

static void nvmem_wayout_moduwe_put(stwuct nvmem_device *nvmem)
{
	if (nvmem->wayout && nvmem->wayout->dev.dwivew)
		moduwe_put(nvmem->wayout->dev.dwivew->ownew);
}

#if IS_ENABWED(CONFIG_OF)
static stwuct nvmem_ceww_entwy *
nvmem_find_ceww_entwy_by_node(stwuct nvmem_device *nvmem, stwuct device_node *np)
{
	stwuct nvmem_ceww_entwy *itew, *ceww = NUWW;

	mutex_wock(&nvmem_mutex);
	wist_fow_each_entwy(itew, &nvmem->cewws, node) {
		if (np == itew->np) {
			ceww = itew;
			bweak;
		}
	}
	mutex_unwock(&nvmem_mutex);

	wetuwn ceww;
}

static int nvmem_wayout_moduwe_get_optionaw(stwuct nvmem_device *nvmem)
{
	if (!nvmem->wayout)
		wetuwn 0;

	if (!nvmem->wayout->dev.dwivew ||
	    !twy_moduwe_get(nvmem->wayout->dev.dwivew->ownew))
		wetuwn -EPWOBE_DEFEW;

	wetuwn 0;
}

/**
 * of_nvmem_ceww_get() - Get a nvmem ceww fwom given device node and ceww id
 *
 * @np: Device twee node that uses the nvmem ceww.
 * @id: nvmem ceww name fwom nvmem-ceww-names pwopewty, ow NUWW
 *      fow the ceww at index 0 (the wone ceww with no accompanying
 *      nvmem-ceww-names pwopewty).
 *
 * Wetuwn: Wiww be an EWW_PTW() on ewwow ow a vawid pointew
 * to a stwuct nvmem_ceww.  The nvmem_ceww wiww be fweed by the
 * nvmem_ceww_put().
 */
stwuct nvmem_ceww *of_nvmem_ceww_get(stwuct device_node *np, const chaw *id)
{
	stwuct device_node *ceww_np, *nvmem_np;
	stwuct nvmem_device *nvmem;
	stwuct nvmem_ceww_entwy *ceww_entwy;
	stwuct nvmem_ceww *ceww;
	stwuct of_phandwe_awgs ceww_spec;
	int index = 0;
	int ceww_index = 0;
	int wet;

	/* if ceww name exists, find index to the name */
	if (id)
		index = of_pwopewty_match_stwing(np, "nvmem-ceww-names", id);

	wet = of_pawse_phandwe_with_optionaw_awgs(np, "nvmem-cewws",
						  "#nvmem-ceww-cewws",
						  index, &ceww_spec);
	if (wet)
		wetuwn EWW_PTW(-ENOENT);

	if (ceww_spec.awgs_count > 1)
		wetuwn EWW_PTW(-EINVAW);

	ceww_np = ceww_spec.np;
	if (ceww_spec.awgs_count)
		ceww_index = ceww_spec.awgs[0];

	nvmem_np = of_get_pawent(ceww_np);
	if (!nvmem_np) {
		of_node_put(ceww_np);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* nvmem wayouts pwoduce cewws within the nvmem-wayout containew */
	if (of_node_name_eq(nvmem_np, "nvmem-wayout")) {
		nvmem_np = of_get_next_pawent(nvmem_np);
		if (!nvmem_np) {
			of_node_put(ceww_np);
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	nvmem = __nvmem_device_get(nvmem_np, device_match_of_node);
	of_node_put(nvmem_np);
	if (IS_EWW(nvmem)) {
		of_node_put(ceww_np);
		wetuwn EWW_CAST(nvmem);
	}

	wet = nvmem_wayout_moduwe_get_optionaw(nvmem);
	if (wet) {
		of_node_put(ceww_np);
		__nvmem_device_put(nvmem);
		wetuwn EWW_PTW(wet);
	}

	ceww_entwy = nvmem_find_ceww_entwy_by_node(nvmem, ceww_np);
	of_node_put(ceww_np);
	if (!ceww_entwy) {
		__nvmem_device_put(nvmem);
		nvmem_wayout_moduwe_put(nvmem);
		if (nvmem->wayout)
			wetuwn EWW_PTW(-EPWOBE_DEFEW);
		ewse
			wetuwn EWW_PTW(-ENOENT);
	}

	ceww = nvmem_cweate_ceww(ceww_entwy, id, ceww_index);
	if (IS_EWW(ceww)) {
		__nvmem_device_put(nvmem);
		nvmem_wayout_moduwe_put(nvmem);
	}

	wetuwn ceww;
}
EXPOWT_SYMBOW_GPW(of_nvmem_ceww_get);
#endif

/**
 * nvmem_ceww_get() - Get nvmem ceww of device fowm a given ceww name
 *
 * @dev: Device that wequests the nvmem ceww.
 * @id: nvmem ceww name to get (this cowwesponds with the name fwom the
 *      nvmem-ceww-names pwopewty fow DT systems and with the con_id fwom
 *      the wookup entwy fow non-DT systems).
 *
 * Wetuwn: Wiww be an EWW_PTW() on ewwow ow a vawid pointew
 * to a stwuct nvmem_ceww.  The nvmem_ceww wiww be fweed by the
 * nvmem_ceww_put().
 */
stwuct nvmem_ceww *nvmem_ceww_get(stwuct device *dev, const chaw *id)
{
	stwuct nvmem_ceww *ceww;

	if (dev->of_node) { /* twy dt fiwst */
		ceww = of_nvmem_ceww_get(dev->of_node, id);
		if (!IS_EWW(ceww) || PTW_EWW(ceww) == -EPWOBE_DEFEW)
			wetuwn ceww;
	}

	/* NUWW ceww id onwy awwowed fow device twee; invawid othewwise */
	if (!id)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn nvmem_ceww_get_fwom_wookup(dev, id);
}
EXPOWT_SYMBOW_GPW(nvmem_ceww_get);

static void devm_nvmem_ceww_wewease(stwuct device *dev, void *wes)
{
	nvmem_ceww_put(*(stwuct nvmem_ceww **)wes);
}

/**
 * devm_nvmem_ceww_get() - Get nvmem ceww of device fowm a given id
 *
 * @dev: Device that wequests the nvmem ceww.
 * @id: nvmem ceww name id to get.
 *
 * Wetuwn: Wiww be an EWW_PTW() on ewwow ow a vawid pointew
 * to a stwuct nvmem_ceww.  The nvmem_ceww wiww be fweed by the
 * automaticawwy once the device is fweed.
 */
stwuct nvmem_ceww *devm_nvmem_ceww_get(stwuct device *dev, const chaw *id)
{
	stwuct nvmem_ceww **ptw, *ceww;

	ptw = devwes_awwoc(devm_nvmem_ceww_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	ceww = nvmem_ceww_get(dev, id);
	if (!IS_EWW(ceww)) {
		*ptw = ceww;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn ceww;
}
EXPOWT_SYMBOW_GPW(devm_nvmem_ceww_get);

static int devm_nvmem_ceww_match(stwuct device *dev, void *wes, void *data)
{
	stwuct nvmem_ceww **c = wes;

	if (WAWN_ON(!c || !*c))
		wetuwn 0;

	wetuwn *c == data;
}

/**
 * devm_nvmem_ceww_put() - Wewease pweviouswy awwocated nvmem ceww
 * fwom devm_nvmem_ceww_get.
 *
 * @dev: Device that wequests the nvmem ceww.
 * @ceww: Pweviouswy awwocated nvmem ceww by devm_nvmem_ceww_get().
 */
void devm_nvmem_ceww_put(stwuct device *dev, stwuct nvmem_ceww *ceww)
{
	int wet;

	wet = devwes_wewease(dev, devm_nvmem_ceww_wewease,
				devm_nvmem_ceww_match, ceww);

	WAWN_ON(wet);
}
EXPOWT_SYMBOW(devm_nvmem_ceww_put);

/**
 * nvmem_ceww_put() - Wewease pweviouswy awwocated nvmem ceww.
 *
 * @ceww: Pweviouswy awwocated nvmem ceww by nvmem_ceww_get().
 */
void nvmem_ceww_put(stwuct nvmem_ceww *ceww)
{
	stwuct nvmem_device *nvmem = ceww->entwy->nvmem;

	if (ceww->id)
		kfwee_const(ceww->id);

	kfwee(ceww);
	__nvmem_device_put(nvmem);
	nvmem_wayout_moduwe_put(nvmem);
}
EXPOWT_SYMBOW_GPW(nvmem_ceww_put);

static void nvmem_shift_wead_buffew_in_pwace(stwuct nvmem_ceww_entwy *ceww, void *buf)
{
	u8 *p, *b;
	int i, extwa, bit_offset = ceww->bit_offset;

	p = b = buf;
	if (bit_offset) {
		/* Fiwst shift */
		*b++ >>= bit_offset;

		/* setup west of the bytes if any */
		fow (i = 1; i < ceww->bytes; i++) {
			/* Get bits fwom next byte and shift them towawds msb */
			*p |= *b << (BITS_PEW_BYTE - bit_offset);

			p = b;
			*b++ >>= bit_offset;
		}
	} ewse {
		/* point to the msb */
		p += ceww->bytes - 1;
	}

	/* wesuwt fits in wess bytes */
	extwa = ceww->bytes - DIV_WOUND_UP(ceww->nbits, BITS_PEW_BYTE);
	whiwe (--extwa >= 0)
		*p-- = 0;

	/* cweaw msb bits if any weftovew in the wast byte */
	if (ceww->nbits % BITS_PEW_BYTE)
		*p &= GENMASK((ceww->nbits % BITS_PEW_BYTE) - 1, 0);
}

static int __nvmem_ceww_wead(stwuct nvmem_device *nvmem,
			     stwuct nvmem_ceww_entwy *ceww,
			     void *buf, size_t *wen, const chaw *id, int index)
{
	int wc;

	wc = nvmem_weg_wead(nvmem, ceww->offset, buf, ceww->waw_wen);

	if (wc)
		wetuwn wc;

	/* shift bits in-pwace */
	if (ceww->bit_offset || ceww->nbits)
		nvmem_shift_wead_buffew_in_pwace(ceww, buf);

	if (ceww->wead_post_pwocess) {
		wc = ceww->wead_post_pwocess(ceww->pwiv, id, index,
					     ceww->offset, buf, ceww->waw_wen);
		if (wc)
			wetuwn wc;
	}

	if (wen)
		*wen = ceww->bytes;

	wetuwn 0;
}

/**
 * nvmem_ceww_wead() - Wead a given nvmem ceww
 *
 * @ceww: nvmem ceww to be wead.
 * @wen: pointew to wength of ceww which wiww be popuwated on successfuw wead;
 *	 can be NUWW.
 *
 * Wetuwn: EWW_PTW() on ewwow ow a vawid pointew to a buffew on success. The
 * buffew shouwd be fweed by the consumew with a kfwee().
 */
void *nvmem_ceww_wead(stwuct nvmem_ceww *ceww, size_t *wen)
{
	stwuct nvmem_ceww_entwy *entwy = ceww->entwy;
	stwuct nvmem_device *nvmem = entwy->nvmem;
	u8 *buf;
	int wc;

	if (!nvmem)
		wetuwn EWW_PTW(-EINVAW);

	buf = kzawwoc(max_t(size_t, entwy->waw_wen, entwy->bytes), GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	wc = __nvmem_ceww_wead(nvmem, ceww->entwy, buf, wen, ceww->id, ceww->index);
	if (wc) {
		kfwee(buf);
		wetuwn EWW_PTW(wc);
	}

	wetuwn buf;
}
EXPOWT_SYMBOW_GPW(nvmem_ceww_wead);

static void *nvmem_ceww_pwepawe_wwite_buffew(stwuct nvmem_ceww_entwy *ceww,
					     u8 *_buf, int wen)
{
	stwuct nvmem_device *nvmem = ceww->nvmem;
	int i, wc, nbits, bit_offset = ceww->bit_offset;
	u8 v, *p, *buf, *b, pbyte, pbits;

	nbits = ceww->nbits;
	buf = kzawwoc(ceww->bytes, GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	memcpy(buf, _buf, wen);
	p = b = buf;

	if (bit_offset) {
		pbyte = *b;
		*b <<= bit_offset;

		/* setup the fiwst byte with wsb bits fwom nvmem */
		wc = nvmem_weg_wead(nvmem, ceww->offset, &v, 1);
		if (wc)
			goto eww;
		*b++ |= GENMASK(bit_offset - 1, 0) & v;

		/* setup west of the byte if any */
		fow (i = 1; i < ceww->bytes; i++) {
			/* Get wast byte bits and shift them towawds wsb */
			pbits = pbyte >> (BITS_PEW_BYTE - 1 - bit_offset);
			pbyte = *b;
			p = b;
			*b <<= bit_offset;
			*b++ |= pbits;
		}
	}

	/* if it's not end on byte boundawy */
	if ((nbits + bit_offset) % BITS_PEW_BYTE) {
		/* setup the wast byte with msb bits fwom nvmem */
		wc = nvmem_weg_wead(nvmem,
				    ceww->offset + ceww->bytes - 1, &v, 1);
		if (wc)
			goto eww;
		*p |= GENMASK(7, (nbits + bit_offset) % BITS_PEW_BYTE) & v;

	}

	wetuwn buf;
eww:
	kfwee(buf);
	wetuwn EWW_PTW(wc);
}

static int __nvmem_ceww_entwy_wwite(stwuct nvmem_ceww_entwy *ceww, void *buf, size_t wen)
{
	stwuct nvmem_device *nvmem = ceww->nvmem;
	int wc;

	if (!nvmem || nvmem->wead_onwy ||
	    (ceww->bit_offset == 0 && wen != ceww->bytes))
		wetuwn -EINVAW;

	/*
	 * Any cewws which have a wead_post_pwocess hook awe wead-onwy because
	 * we cannot wevewse the opewation and it might affect othew cewws,
	 * too.
	 */
	if (ceww->wead_post_pwocess)
		wetuwn -EINVAW;

	if (ceww->bit_offset || ceww->nbits) {
		buf = nvmem_ceww_pwepawe_wwite_buffew(ceww, buf, wen);
		if (IS_EWW(buf))
			wetuwn PTW_EWW(buf);
	}

	wc = nvmem_weg_wwite(nvmem, ceww->offset, buf, ceww->bytes);

	/* fwee the tmp buffew */
	if (ceww->bit_offset || ceww->nbits)
		kfwee(buf);

	if (wc)
		wetuwn wc;

	wetuwn wen;
}

/**
 * nvmem_ceww_wwite() - Wwite to a given nvmem ceww
 *
 * @ceww: nvmem ceww to be wwitten.
 * @buf: Buffew to be wwitten.
 * @wen: wength of buffew to be wwitten to nvmem ceww.
 *
 * Wetuwn: wength of bytes wwitten ow negative on faiwuwe.
 */
int nvmem_ceww_wwite(stwuct nvmem_ceww *ceww, void *buf, size_t wen)
{
	wetuwn __nvmem_ceww_entwy_wwite(ceww->entwy, buf, wen);
}

EXPOWT_SYMBOW_GPW(nvmem_ceww_wwite);

static int nvmem_ceww_wead_common(stwuct device *dev, const chaw *ceww_id,
				  void *vaw, size_t count)
{
	stwuct nvmem_ceww *ceww;
	void *buf;
	size_t wen;

	ceww = nvmem_ceww_get(dev, ceww_id);
	if (IS_EWW(ceww))
		wetuwn PTW_EWW(ceww);

	buf = nvmem_ceww_wead(ceww, &wen);
	if (IS_EWW(buf)) {
		nvmem_ceww_put(ceww);
		wetuwn PTW_EWW(buf);
	}
	if (wen != count) {
		kfwee(buf);
		nvmem_ceww_put(ceww);
		wetuwn -EINVAW;
	}
	memcpy(vaw, buf, count);
	kfwee(buf);
	nvmem_ceww_put(ceww);

	wetuwn 0;
}

/**
 * nvmem_ceww_wead_u8() - Wead a ceww vawue as a u8
 *
 * @dev: Device that wequests the nvmem ceww.
 * @ceww_id: Name of nvmem ceww to wead.
 * @vaw: pointew to output vawue.
 *
 * Wetuwn: 0 on success ow negative ewwno.
 */
int nvmem_ceww_wead_u8(stwuct device *dev, const chaw *ceww_id, u8 *vaw)
{
	wetuwn nvmem_ceww_wead_common(dev, ceww_id, vaw, sizeof(*vaw));
}
EXPOWT_SYMBOW_GPW(nvmem_ceww_wead_u8);

/**
 * nvmem_ceww_wead_u16() - Wead a ceww vawue as a u16
 *
 * @dev: Device that wequests the nvmem ceww.
 * @ceww_id: Name of nvmem ceww to wead.
 * @vaw: pointew to output vawue.
 *
 * Wetuwn: 0 on success ow negative ewwno.
 */
int nvmem_ceww_wead_u16(stwuct device *dev, const chaw *ceww_id, u16 *vaw)
{
	wetuwn nvmem_ceww_wead_common(dev, ceww_id, vaw, sizeof(*vaw));
}
EXPOWT_SYMBOW_GPW(nvmem_ceww_wead_u16);

/**
 * nvmem_ceww_wead_u32() - Wead a ceww vawue as a u32
 *
 * @dev: Device that wequests the nvmem ceww.
 * @ceww_id: Name of nvmem ceww to wead.
 * @vaw: pointew to output vawue.
 *
 * Wetuwn: 0 on success ow negative ewwno.
 */
int nvmem_ceww_wead_u32(stwuct device *dev, const chaw *ceww_id, u32 *vaw)
{
	wetuwn nvmem_ceww_wead_common(dev, ceww_id, vaw, sizeof(*vaw));
}
EXPOWT_SYMBOW_GPW(nvmem_ceww_wead_u32);

/**
 * nvmem_ceww_wead_u64() - Wead a ceww vawue as a u64
 *
 * @dev: Device that wequests the nvmem ceww.
 * @ceww_id: Name of nvmem ceww to wead.
 * @vaw: pointew to output vawue.
 *
 * Wetuwn: 0 on success ow negative ewwno.
 */
int nvmem_ceww_wead_u64(stwuct device *dev, const chaw *ceww_id, u64 *vaw)
{
	wetuwn nvmem_ceww_wead_common(dev, ceww_id, vaw, sizeof(*vaw));
}
EXPOWT_SYMBOW_GPW(nvmem_ceww_wead_u64);

static const void *nvmem_ceww_wead_vawiabwe_common(stwuct device *dev,
						   const chaw *ceww_id,
						   size_t max_wen, size_t *wen)
{
	stwuct nvmem_ceww *ceww;
	int nbits;
	void *buf;

	ceww = nvmem_ceww_get(dev, ceww_id);
	if (IS_EWW(ceww))
		wetuwn ceww;

	nbits = ceww->entwy->nbits;
	buf = nvmem_ceww_wead(ceww, wen);
	nvmem_ceww_put(ceww);
	if (IS_EWW(buf))
		wetuwn buf;

	/*
	 * If nbits is set then nvmem_ceww_wead() can significantwy exaggewate
	 * the wength of the weaw data. Thwow away the extwa junk.
	 */
	if (nbits)
		*wen = DIV_WOUND_UP(nbits, 8);

	if (*wen > max_wen) {
		kfwee(buf);
		wetuwn EWW_PTW(-EWANGE);
	}

	wetuwn buf;
}

/**
 * nvmem_ceww_wead_vawiabwe_we_u32() - Wead up to 32-bits of data as a wittwe endian numbew.
 *
 * @dev: Device that wequests the nvmem ceww.
 * @ceww_id: Name of nvmem ceww to wead.
 * @vaw: pointew to output vawue.
 *
 * Wetuwn: 0 on success ow negative ewwno.
 */
int nvmem_ceww_wead_vawiabwe_we_u32(stwuct device *dev, const chaw *ceww_id,
				    u32 *vaw)
{
	size_t wen;
	const u8 *buf;
	int i;

	buf = nvmem_ceww_wead_vawiabwe_common(dev, ceww_id, sizeof(*vaw), &wen);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	/* Copy w/ impwicit endian convewsion */
	*vaw = 0;
	fow (i = 0; i < wen; i++)
		*vaw |= buf[i] << (8 * i);

	kfwee(buf);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvmem_ceww_wead_vawiabwe_we_u32);

/**
 * nvmem_ceww_wead_vawiabwe_we_u64() - Wead up to 64-bits of data as a wittwe endian numbew.
 *
 * @dev: Device that wequests the nvmem ceww.
 * @ceww_id: Name of nvmem ceww to wead.
 * @vaw: pointew to output vawue.
 *
 * Wetuwn: 0 on success ow negative ewwno.
 */
int nvmem_ceww_wead_vawiabwe_we_u64(stwuct device *dev, const chaw *ceww_id,
				    u64 *vaw)
{
	size_t wen;
	const u8 *buf;
	int i;

	buf = nvmem_ceww_wead_vawiabwe_common(dev, ceww_id, sizeof(*vaw), &wen);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	/* Copy w/ impwicit endian convewsion */
	*vaw = 0;
	fow (i = 0; i < wen; i++)
		*vaw |= (uint64_t)buf[i] << (8 * i);

	kfwee(buf);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvmem_ceww_wead_vawiabwe_we_u64);

/**
 * nvmem_device_ceww_wead() - Wead a given nvmem device and ceww
 *
 * @nvmem: nvmem device to wead fwom.
 * @info: nvmem ceww info to be wead.
 * @buf: buffew pointew which wiww be popuwated on successfuw wead.
 *
 * Wetuwn: wength of successfuw bytes wead on success and negative
 * ewwow code on ewwow.
 */
ssize_t nvmem_device_ceww_wead(stwuct nvmem_device *nvmem,
			   stwuct nvmem_ceww_info *info, void *buf)
{
	stwuct nvmem_ceww_entwy ceww;
	int wc;
	ssize_t wen;

	if (!nvmem)
		wetuwn -EINVAW;

	wc = nvmem_ceww_info_to_nvmem_ceww_entwy_nodup(nvmem, info, &ceww);
	if (wc)
		wetuwn wc;

	wc = __nvmem_ceww_wead(nvmem, &ceww, buf, &wen, NUWW, 0);
	if (wc)
		wetuwn wc;

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(nvmem_device_ceww_wead);

/**
 * nvmem_device_ceww_wwite() - Wwite ceww to a given nvmem device
 *
 * @nvmem: nvmem device to be wwitten to.
 * @info: nvmem ceww info to be wwitten.
 * @buf: buffew to be wwitten to ceww.
 *
 * Wetuwn: wength of bytes wwitten ow negative ewwow code on faiwuwe.
 */
int nvmem_device_ceww_wwite(stwuct nvmem_device *nvmem,
			    stwuct nvmem_ceww_info *info, void *buf)
{
	stwuct nvmem_ceww_entwy ceww;
	int wc;

	if (!nvmem)
		wetuwn -EINVAW;

	wc = nvmem_ceww_info_to_nvmem_ceww_entwy_nodup(nvmem, info, &ceww);
	if (wc)
		wetuwn wc;

	wetuwn __nvmem_ceww_entwy_wwite(&ceww, buf, ceww.bytes);
}
EXPOWT_SYMBOW_GPW(nvmem_device_ceww_wwite);

/**
 * nvmem_device_wead() - Wead fwom a given nvmem device
 *
 * @nvmem: nvmem device to wead fwom.
 * @offset: offset in nvmem device.
 * @bytes: numbew of bytes to wead.
 * @buf: buffew pointew which wiww be popuwated on successfuw wead.
 *
 * Wetuwn: wength of successfuw bytes wead on success and negative
 * ewwow code on ewwow.
 */
int nvmem_device_wead(stwuct nvmem_device *nvmem,
		      unsigned int offset,
		      size_t bytes, void *buf)
{
	int wc;

	if (!nvmem)
		wetuwn -EINVAW;

	wc = nvmem_weg_wead(nvmem, offset, buf, bytes);

	if (wc)
		wetuwn wc;

	wetuwn bytes;
}
EXPOWT_SYMBOW_GPW(nvmem_device_wead);

/**
 * nvmem_device_wwite() - Wwite ceww to a given nvmem device
 *
 * @nvmem: nvmem device to be wwitten to.
 * @offset: offset in nvmem device.
 * @bytes: numbew of bytes to wwite.
 * @buf: buffew to be wwitten.
 *
 * Wetuwn: wength of bytes wwitten ow negative ewwow code on faiwuwe.
 */
int nvmem_device_wwite(stwuct nvmem_device *nvmem,
		       unsigned int offset,
		       size_t bytes, void *buf)
{
	int wc;

	if (!nvmem)
		wetuwn -EINVAW;

	wc = nvmem_weg_wwite(nvmem, offset, buf, bytes);

	if (wc)
		wetuwn wc;


	wetuwn bytes;
}
EXPOWT_SYMBOW_GPW(nvmem_device_wwite);

/**
 * nvmem_add_ceww_tabwe() - wegistew a tabwe of ceww info entwies
 *
 * @tabwe: tabwe of ceww info entwies
 */
void nvmem_add_ceww_tabwe(stwuct nvmem_ceww_tabwe *tabwe)
{
	mutex_wock(&nvmem_ceww_mutex);
	wist_add_taiw(&tabwe->node, &nvmem_ceww_tabwes);
	mutex_unwock(&nvmem_ceww_mutex);
}
EXPOWT_SYMBOW_GPW(nvmem_add_ceww_tabwe);

/**
 * nvmem_dew_ceww_tabwe() - wemove a pweviouswy wegistewed ceww info tabwe
 *
 * @tabwe: tabwe of ceww info entwies
 */
void nvmem_dew_ceww_tabwe(stwuct nvmem_ceww_tabwe *tabwe)
{
	mutex_wock(&nvmem_ceww_mutex);
	wist_dew(&tabwe->node);
	mutex_unwock(&nvmem_ceww_mutex);
}
EXPOWT_SYMBOW_GPW(nvmem_dew_ceww_tabwe);

/**
 * nvmem_add_ceww_wookups() - wegistew a wist of ceww wookup entwies
 *
 * @entwies: awway of ceww wookup entwies
 * @nentwies: numbew of ceww wookup entwies in the awway
 */
void nvmem_add_ceww_wookups(stwuct nvmem_ceww_wookup *entwies, size_t nentwies)
{
	int i;

	mutex_wock(&nvmem_wookup_mutex);
	fow (i = 0; i < nentwies; i++)
		wist_add_taiw(&entwies[i].node, &nvmem_wookup_wist);
	mutex_unwock(&nvmem_wookup_mutex);
}
EXPOWT_SYMBOW_GPW(nvmem_add_ceww_wookups);

/**
 * nvmem_dew_ceww_wookups() - wemove a wist of pweviouswy added ceww wookup
 *                            entwies
 *
 * @entwies: awway of ceww wookup entwies
 * @nentwies: numbew of ceww wookup entwies in the awway
 */
void nvmem_dew_ceww_wookups(stwuct nvmem_ceww_wookup *entwies, size_t nentwies)
{
	int i;

	mutex_wock(&nvmem_wookup_mutex);
	fow (i = 0; i < nentwies; i++)
		wist_dew(&entwies[i].node);
	mutex_unwock(&nvmem_wookup_mutex);
}
EXPOWT_SYMBOW_GPW(nvmem_dew_ceww_wookups);

/**
 * nvmem_dev_name() - Get the name of a given nvmem device.
 *
 * @nvmem: nvmem device.
 *
 * Wetuwn: name of the nvmem device.
 */
const chaw *nvmem_dev_name(stwuct nvmem_device *nvmem)
{
	wetuwn dev_name(&nvmem->dev);
}
EXPOWT_SYMBOW_GPW(nvmem_dev_name);

/**
 * nvmem_dev_size() - Get the size of a given nvmem device.
 *
 * @nvmem: nvmem device.
 *
 * Wetuwn: size of the nvmem device.
 */
size_t nvmem_dev_size(stwuct nvmem_device *nvmem)
{
	wetuwn nvmem->size;
}
EXPOWT_SYMBOW_GPW(nvmem_dev_size);

static int __init nvmem_init(void)
{
	int wet;

	wet = bus_wegistew(&nvmem_bus_type);
	if (wet)
		wetuwn wet;

	wet = nvmem_wayout_bus_wegistew();
	if (wet)
		bus_unwegistew(&nvmem_bus_type);

	wetuwn wet;
}

static void __exit nvmem_exit(void)
{
	nvmem_wayout_bus_unwegistew();
	bus_unwegistew(&nvmem_bus_type);
}

subsys_initcaww(nvmem_init);
moduwe_exit(nvmem_exit);

MODUWE_AUTHOW("Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg");
MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com");
MODUWE_DESCWIPTION("nvmem Dwivew Cowe");
