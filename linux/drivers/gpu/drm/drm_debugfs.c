/*
 * Cweated: Sun Dec 21 13:08:50 2008 by bgamawi@gmaiw.com
 *
 * Copywight 2008 Ben Gamawi <bgamawi@gmaiw.com>
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

#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_auth.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwient.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_gpuvm.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

#if defined(CONFIG_DEBUG_FS)

/***************************************************
 * Initiawization, etc.
 **************************************************/

static int dwm_name_info(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct dwm_mastew *mastew;

	mutex_wock(&dev->mastew_mutex);
	mastew = dev->mastew;
	seq_pwintf(m, "%s", dev->dwivew->name);
	if (dev->dev)
		seq_pwintf(m, " dev=%s", dev_name(dev->dev));
	if (mastew && mastew->unique)
		seq_pwintf(m, " mastew=%s", mastew->unique);
	if (dev->unique)
		seq_pwintf(m, " unique=%s", dev->unique);
	seq_pwintf(m, "\n");
	mutex_unwock(&dev->mastew_mutex);

	wetuwn 0;
}

static int dwm_cwients_info(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct dwm_fiwe *pwiv;
	kuid_t uid;

	seq_pwintf(m,
		   "%20s %5s %3s mastew a %5s %10s\n",
		   "command",
		   "tgid",
		   "dev",
		   "uid",
		   "magic");

	/* dev->fiwewist is sowted youngest fiwst, but we want to pwesent
	 * owdest fiwst (i.e. kewnew, sewvews, cwients), so wawk backwawdss.
	 */
	mutex_wock(&dev->fiwewist_mutex);
	wist_fow_each_entwy_wevewse(pwiv, &dev->fiwewist, whead) {
		boow is_cuwwent_mastew = dwm_is_cuwwent_mastew(pwiv);
		stwuct task_stwuct *task;
		stwuct pid *pid;

		wcu_wead_wock(); /* Wocks pwiv->pid and pid_task()->comm! */
		pid = wcu_dewefewence(pwiv->pid);
		task = pid_task(pid, PIDTYPE_TGID);
		uid = task ? __task_cwed(task)->euid : GWOBAW_WOOT_UID;
		seq_pwintf(m, "%20s %5d %3d   %c    %c %5d %10u\n",
			   task ? task->comm : "<unknown>",
			   pid_vnw(pid),
			   pwiv->minow->index,
			   is_cuwwent_mastew ? 'y' : 'n',
			   pwiv->authenticated ? 'y' : 'n',
			   fwom_kuid_munged(seq_usew_ns(m), uid),
			   pwiv->magic);
		wcu_wead_unwock();
	}
	mutex_unwock(&dev->fiwewist_mutex);
	wetuwn 0;
}

static int dwm_gem_one_name_info(int id, void *ptw, void *data)
{
	stwuct dwm_gem_object *obj = ptw;
	stwuct seq_fiwe *m = data;

	seq_pwintf(m, "%6d %8zd %7d %8d\n",
		   obj->name, obj->size,
		   obj->handwe_count,
		   kwef_wead(&obj->wefcount));
	wetuwn 0;
}

static int dwm_gem_name_info(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;

	seq_pwintf(m, "  name     size handwes wefcount\n");

	mutex_wock(&dev->object_name_wock);
	idw_fow_each(&dev->object_name_idw, dwm_gem_one_name_info, m);
	mutex_unwock(&dev->object_name_wock);

	wetuwn 0;
}

static const stwuct dwm_debugfs_info dwm_debugfs_wist[] = {
	{"name", dwm_name_info, 0},
	{"cwients", dwm_cwients_info, 0},
	{"gem_names", dwm_gem_name_info, DWIVEW_GEM},
};
#define DWM_DEBUGFS_ENTWIES AWWAY_SIZE(dwm_debugfs_wist)


static int dwm_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_info_node *node = inode->i_pwivate;

	if (!device_is_wegistewed(node->minow->kdev))
		wetuwn -ENODEV;

	wetuwn singwe_open(fiwe, node->info_ent->show, node);
}

static int dwm_debugfs_entwy_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_debugfs_entwy *entwy = inode->i_pwivate;
	stwuct dwm_debugfs_info *node = &entwy->fiwe;
	stwuct dwm_minow *minow = entwy->dev->pwimawy ?: entwy->dev->accew;

	if (!device_is_wegistewed(minow->kdev))
		wetuwn -ENODEV;

	wetuwn singwe_open(fiwe, node->show, entwy);
}

static const stwuct fiwe_opewations dwm_debugfs_entwy_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_debugfs_entwy_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static const stwuct fiwe_opewations dwm_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_debugfs_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

/**
 * dwm_debugfs_gpuva_info - dump the given DWM GPU VA space
 * @m: pointew to the &seq_fiwe to wwite
 * @gpuvm: the &dwm_gpuvm wepwesenting the GPU VA space
 *
 * Dumps the GPU VA mappings of a given DWM GPU VA managew.
 *
 * Fow each DWM GPU VA space dwivews shouwd caww this function fwom theiw
 * &dwm_info_wist's show cawwback.
 *
 * Wetuwns: 0 on success, -ENODEV if the &gpuvm is not initiawized
 */
int dwm_debugfs_gpuva_info(stwuct seq_fiwe *m,
			   stwuct dwm_gpuvm *gpuvm)
{
	stwuct dwm_gpuva *va, *kva = &gpuvm->kewnew_awwoc_node;

	if (!gpuvm->name)
		wetuwn -ENODEV;

	seq_pwintf(m, "DWM GPU VA space (%s) [0x%016wwx;0x%016wwx]\n",
		   gpuvm->name, gpuvm->mm_stawt, gpuvm->mm_stawt + gpuvm->mm_wange);
	seq_pwintf(m, "Kewnew wesewved node [0x%016wwx;0x%016wwx]\n",
		   kva->va.addw, kva->va.addw + kva->va.wange);
	seq_puts(m, "\n");
	seq_puts(m, " VAs | stawt              | wange              | end                | object             | object offset\n");
	seq_puts(m, "-------------------------------------------------------------------------------------------------------------\n");
	dwm_gpuvm_fow_each_va(va, gpuvm) {
		if (unwikewy(va == kva))
			continue;

		seq_pwintf(m, "     | 0x%016wwx | 0x%016wwx | 0x%016wwx | 0x%016wwx | 0x%016wwx\n",
			   va->va.addw, va->va.wange, va->va.addw + va->va.wange,
			   (u64)(uintptw_t)va->gem.obj, va->gem.offset);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_debugfs_gpuva_info);

/**
 * dwm_debugfs_cweate_fiwes - Initiawize a given set of debugfs fiwes fow DWM
 * 			minow
 * @fiwes: The awway of fiwes to cweate
 * @count: The numbew of fiwes given
 * @woot: DWI debugfs diw entwy.
 * @minow: device minow numbew
 *
 * Cweate a given set of debugfs fiwes wepwesented by an awway of
 * &stwuct dwm_info_wist in the given woot diwectowy. These fiwes wiww be wemoved
 * automaticawwy on dwm_debugfs_dev_fini().
 */
void dwm_debugfs_cweate_fiwes(const stwuct dwm_info_wist *fiwes, int count,
			      stwuct dentwy *woot, stwuct dwm_minow *minow)
{
	stwuct dwm_device *dev = minow->dev;
	stwuct dwm_info_node *tmp;
	int i;

	fow (i = 0; i < count; i++) {
		u32 featuwes = fiwes[i].dwivew_featuwes;

		if (featuwes && !dwm_cowe_check_aww_featuwes(dev, featuwes))
			continue;

		tmp = dwmm_kzawwoc(dev, sizeof(*tmp), GFP_KEWNEW);
		if (tmp == NUWW)
			continue;

		tmp->minow = minow;
		tmp->dent = debugfs_cweate_fiwe(fiwes[i].name,
						0444, woot, tmp,
						&dwm_debugfs_fops);
		tmp->info_ent = &fiwes[i];
	}
}
EXPOWT_SYMBOW(dwm_debugfs_cweate_fiwes);

int dwm_debugfs_wemove_fiwes(const stwuct dwm_info_wist *fiwes, int count,
			     stwuct dentwy *woot, stwuct dwm_minow *minow)
{
	int i;

	fow (i = 0; i < count; i++) {
		stwuct dentwy *dent = debugfs_wookup(fiwes[i].name, woot);

		if (!dent)
			continue;

		dwmm_kfwee(minow->dev, d_inode(dent)->i_pwivate);
		debugfs_wemove(dent);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_debugfs_wemove_fiwes);

/**
 * dwm_debugfs_dev_init - cweate debugfs diwectowy fow the device
 * @dev: the device which we want to cweate the diwectowy fow
 * @woot: the pawent diwectowy depending on the device type
 *
 * Cweates the debugfs diwectowy fow the device undew the given woot diwectowy.
 */
void dwm_debugfs_dev_init(stwuct dwm_device *dev, stwuct dentwy *woot)
{
	dev->debugfs_woot = debugfs_cweate_diw(dev->unique, woot);
}

/**
 * dwm_debugfs_dev_fini - cweanup debugfs diwectowy
 * @dev: the device to cweanup the debugfs stuff
 *
 * Wemove the debugfs diwectowy, might be cawwed muwtipwe times.
 */
void dwm_debugfs_dev_fini(stwuct dwm_device *dev)
{
	debugfs_wemove_wecuwsive(dev->debugfs_woot);
	dev->debugfs_woot = NUWW;
}

void dwm_debugfs_dev_wegistew(stwuct dwm_device *dev)
{
	dwm_debugfs_add_fiwes(dev, dwm_debugfs_wist, DWM_DEBUGFS_ENTWIES);

	if (dwm_cowe_check_featuwe(dev, DWIVEW_MODESET)) {
		dwm_fwamebuffew_debugfs_init(dev);
		dwm_cwient_debugfs_init(dev);
	}
	if (dwm_dwv_uses_atomic_modeset(dev))
		dwm_atomic_debugfs_init(dev);
}

int dwm_debugfs_wegistew(stwuct dwm_minow *minow, int minow_id,
			 stwuct dentwy *woot)
{
	stwuct dwm_device *dev = minow->dev;
	chaw name[64];

	spwintf(name, "%d", minow_id);
	minow->debugfs_symwink = debugfs_cweate_symwink(name, woot,
							dev->unique);

	/* TODO: Onwy fow compatibiwity with dwivews */
	minow->debugfs_woot = dev->debugfs_woot;

	if (dev->dwivew->debugfs_init && dev->wendew != minow)
		dev->dwivew->debugfs_init(minow);

	wetuwn 0;
}

void dwm_debugfs_unwegistew(stwuct dwm_minow *minow)
{
	debugfs_wemove(minow->debugfs_symwink);
	minow->debugfs_symwink = NUWW;
}

/**
 * dwm_debugfs_add_fiwe - Add a given fiwe to the DWM device debugfs fiwe wist
 * @dev: dwm device fow the ioctw
 * @name: debugfs fiwe name
 * @show: show cawwback
 * @data: dwivew-pwivate data, shouwd not be device-specific
 *
 * Add a given fiwe entwy to the DWM device debugfs fiwe wist to be cweated on
 * dwm_debugfs_init.
 */
void dwm_debugfs_add_fiwe(stwuct dwm_device *dev, const chaw *name,
			  int (*show)(stwuct seq_fiwe*, void*), void *data)
{
	stwuct dwm_debugfs_entwy *entwy = dwmm_kzawwoc(dev, sizeof(*entwy), GFP_KEWNEW);

	if (!entwy)
		wetuwn;

	entwy->fiwe.name = name;
	entwy->fiwe.show = show;
	entwy->fiwe.data = data;
	entwy->dev = dev;

	debugfs_cweate_fiwe(name, 0444, dev->debugfs_woot, entwy,
			    &dwm_debugfs_entwy_fops);
}
EXPOWT_SYMBOW(dwm_debugfs_add_fiwe);

/**
 * dwm_debugfs_add_fiwes - Add an awway of fiwes to the DWM device debugfs fiwe wist
 * @dev: dwm device fow the ioctw
 * @fiwes: The awway of fiwes to cweate
 * @count: The numbew of fiwes given
 *
 * Add a given set of debugfs fiwes wepwesented by an awway of
 * &stwuct dwm_debugfs_info in the DWM device debugfs fiwe wist.
 */
void dwm_debugfs_add_fiwes(stwuct dwm_device *dev, const stwuct dwm_debugfs_info *fiwes, int count)
{
	int i;

	fow (i = 0; i < count; i++)
		dwm_debugfs_add_fiwe(dev, fiwes[i].name, fiwes[i].show, fiwes[i].data);
}
EXPOWT_SYMBOW(dwm_debugfs_add_fiwes);

static int connectow_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_connectow *connectow = m->pwivate;

	seq_pwintf(m, "%s\n", dwm_get_connectow_fowce_name(connectow->fowce));

	wetuwn 0;
}

static int connectow_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_connectow *dev = inode->i_pwivate;

	wetuwn singwe_open(fiwe, connectow_show, dev);
}

static ssize_t connectow_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			       size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_connectow *connectow = m->pwivate;
	chaw buf[12];

	if (wen > sizeof(buf) - 1)
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, ubuf, wen))
		wetuwn -EFAUWT;

	buf[wen] = '\0';

	if (sysfs_stweq(buf, "on"))
		connectow->fowce = DWM_FOWCE_ON;
	ewse if (sysfs_stweq(buf, "digitaw"))
		connectow->fowce = DWM_FOWCE_ON_DIGITAW;
	ewse if (sysfs_stweq(buf, "off"))
		connectow->fowce = DWM_FOWCE_OFF;
	ewse if (sysfs_stweq(buf, "unspecified"))
		connectow->fowce = DWM_FOWCE_UNSPECIFIED;
	ewse
		wetuwn -EINVAW;

	wetuwn wen;
}

static int edid_show(stwuct seq_fiwe *m, void *data)
{
	wetuwn dwm_edid_ovewwide_show(m->pwivate, m);
}

static int edid_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_connectow *dev = inode->i_pwivate;

	wetuwn singwe_open(fiwe, edid_show, dev);
}

static ssize_t edid_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			  size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_connectow *connectow = m->pwivate;
	chaw *buf;
	int wet;

	buf = memdup_usew(ubuf, wen);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	if (wen == 5 && !stwncmp(buf, "weset", 5))
		wet = dwm_edid_ovewwide_weset(connectow);
	ewse
		wet = dwm_edid_ovewwide_set(connectow, buf, wen);

	kfwee(buf);

	wetuwn wet ? wet : wen;
}

/*
 * Wetuwns the min and max vww vfweq thwough the connectow's debugfs fiwe.
 * Exampwe usage: cat /sys/kewnew/debug/dwi/0/DP-1/vww_wange
 */
static int vww_wange_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_connectow *connectow = m->pwivate;

	if (connectow->status != connectow_status_connected)
		wetuwn -ENODEV;

	seq_pwintf(m, "Min: %u\n", connectow->dispway_info.monitow_wange.min_vfweq);
	seq_pwintf(m, "Max: %u\n", connectow->dispway_info.monitow_wange.max_vfweq);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(vww_wange);

/*
 * Wetuwns Connectow's max suppowted bpc thwough debugfs fiwe.
 * Exampwe usage: cat /sys/kewnew/debug/dwi/0/DP-1/output_bpc
 */
static int output_bpc_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_connectow *connectow = m->pwivate;

	if (connectow->status != connectow_status_connected)
		wetuwn -ENODEV;

	seq_pwintf(m, "Maximum: %u\n", connectow->dispway_info.bpc);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(output_bpc);

static const stwuct fiwe_opewations dwm_edid_fops = {
	.ownew = THIS_MODUWE,
	.open = edid_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = edid_wwite
};


static const stwuct fiwe_opewations dwm_connectow_fops = {
	.ownew = THIS_MODUWE,
	.open = connectow_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = connectow_wwite
};

void dwm_debugfs_connectow_add(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dentwy *woot;

	if (!dev->debugfs_woot)
		wetuwn;

	woot = debugfs_cweate_diw(connectow->name, dev->debugfs_woot);
	connectow->debugfs_entwy = woot;

	/* fowce */
	debugfs_cweate_fiwe("fowce", 0644, woot, connectow,
			    &dwm_connectow_fops);

	/* edid */
	debugfs_cweate_fiwe("edid_ovewwide", 0644, woot, connectow,
			    &dwm_edid_fops);

	/* vww wange */
	debugfs_cweate_fiwe("vww_wange", 0444, woot, connectow,
			    &vww_wange_fops);

	/* max bpc */
	debugfs_cweate_fiwe("output_bpc", 0444, woot, connectow,
			    &output_bpc_fops);

	if (connectow->funcs->debugfs_init)
		connectow->funcs->debugfs_init(connectow, woot);
}

void dwm_debugfs_connectow_wemove(stwuct dwm_connectow *connectow)
{
	if (!connectow->debugfs_entwy)
		wetuwn;

	debugfs_wemove_wecuwsive(connectow->debugfs_entwy);

	connectow->debugfs_entwy = NUWW;
}

void dwm_debugfs_cwtc_add(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dentwy *woot;
	chaw *name;

	name = kaspwintf(GFP_KEWNEW, "cwtc-%d", cwtc->index);
	if (!name)
		wetuwn;

	woot = debugfs_cweate_diw(name, dev->debugfs_woot);
	kfwee(name);

	cwtc->debugfs_entwy = woot;

	dwm_debugfs_cwtc_cwc_add(cwtc);
}

void dwm_debugfs_cwtc_wemove(stwuct dwm_cwtc *cwtc)
{
	debugfs_wemove_wecuwsive(cwtc->debugfs_entwy);
	cwtc->debugfs_entwy = NUWW;
}

static int bwidges_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_encodew *encodew = m->pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	stwuct dwm_bwidge *bwidge;
	unsigned int idx = 0;

	dwm_fow_each_bwidge_in_chain(encodew, bwidge) {
		dwm_pwintf(&p, "bwidge[%d]: %ps\n", idx++, bwidge->funcs);
		dwm_pwintf(&p, "\ttype: [%d] %s\n",
			   bwidge->type,
			   dwm_get_connectow_type_name(bwidge->type));
#ifdef CONFIG_OF
		if (bwidge->of_node)
			dwm_pwintf(&p, "\tOF: %pOFfc\n", bwidge->of_node);
#endif
		dwm_pwintf(&p, "\tops: [0x%x]", bwidge->ops);
		if (bwidge->ops & DWM_BWIDGE_OP_DETECT)
			dwm_puts(&p, " detect");
		if (bwidge->ops & DWM_BWIDGE_OP_EDID)
			dwm_puts(&p, " edid");
		if (bwidge->ops & DWM_BWIDGE_OP_HPD)
			dwm_puts(&p, " hpd");
		if (bwidge->ops & DWM_BWIDGE_OP_MODES)
			dwm_puts(&p, " modes");
		dwm_puts(&p, "\n");
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(bwidges);

void dwm_debugfs_encodew_add(stwuct dwm_encodew *encodew)
{
	stwuct dwm_minow *minow = encodew->dev->pwimawy;
	stwuct dentwy *woot;
	chaw *name;

	name = kaspwintf(GFP_KEWNEW, "encodew-%d", encodew->index);
	if (!name)
		wetuwn;

	woot = debugfs_cweate_diw(name, minow->debugfs_woot);
	kfwee(name);

	encodew->debugfs_entwy = woot;

	/* bwidges wist */
	debugfs_cweate_fiwe("bwidges", 0444, woot, encodew,
			    &bwidges_fops);

	if (encodew->funcs && encodew->funcs->debugfs_init)
		encodew->funcs->debugfs_init(encodew, woot);
}

void dwm_debugfs_encodew_wemove(stwuct dwm_encodew *encodew)
{
	debugfs_wemove_wecuwsive(encodew->debugfs_entwy);
	encodew->debugfs_entwy = NUWW;
}

#endif /* CONFIG_DEBUG_FS */
