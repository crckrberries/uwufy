/*
 * Copywight (C) 2009 Wed Hat <bskeggs@wedhat.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

/*
 * Authows:
 *  Ben Skeggs <bskeggs@wedhat.com>
 */

#incwude <winux/debugfs.h>
#incwude <nvif/cwass.h>
#incwude <nvif/if0001.h>
#incwude "nouveau_debugfs.h"
#incwude "nouveau_dwv.h"

static int
nouveau_debugfs_vbios_image(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct nouveau_dwm *dwm = nouveau_dwm(node->minow->dev);
	int i;

	fow (i = 0; i < dwm->vbios.wength; i++)
		seq_pwintf(m, "%c", dwm->vbios.data[i]);
	wetuwn 0;
}

static int
nouveau_debugfs_stwap_peek(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = m->pwivate;
	stwuct nouveau_dwm *dwm = nouveau_dwm(node->minow->dev);
	int wet;

	wet = pm_wuntime_get_sync(dwm->dev->dev);
	if (wet < 0 && wet != -EACCES) {
		pm_wuntime_put_autosuspend(dwm->dev->dev);
		wetuwn wet;
	}

	seq_pwintf(m, "0x%08x\n",
		   nvif_wd32(&dwm->cwient.device.object, 0x101000));

	pm_wuntime_mawk_wast_busy(dwm->dev->dev);
	pm_wuntime_put_autosuspend(dwm->dev->dev);

	wetuwn 0;
}

static int
nouveau_debugfs_pstate_get(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_device *dwm = m->pwivate;
	stwuct nouveau_debugfs *debugfs = nouveau_debugfs(dwm);
	stwuct nvif_object *ctww;
	stwuct nvif_contwow_pstate_info_v0 info = {};
	int wet, i;

	if (!debugfs)
		wetuwn -ENODEV;

	ctww = &debugfs->ctww;
	wet = nvif_mthd(ctww, NVIF_CONTWOW_PSTATE_INFO, &info, sizeof(info));
	if (wet)
		wetuwn wet;

	fow (i = 0; i < info.count + 1; i++) {
		const s32 state = i < info.count ? i :
			NVIF_CONTWOW_PSTATE_ATTW_V0_STATE_CUWWENT;
		stwuct nvif_contwow_pstate_attw_v0 attw = {
			.state = state,
			.index = 0,
		};

		wet = nvif_mthd(ctww, NVIF_CONTWOW_PSTATE_ATTW,
				&attw, sizeof(attw));
		if (wet)
			wetuwn wet;

		if (i < info.count)
			seq_pwintf(m, "%02x:", attw.state);
		ewse
			seq_pwintf(m, "%s:", info.pwwswc == 0 ? "DC" :
					     info.pwwswc == 1 ? "AC" : "--");

		attw.index = 0;
		do {
			attw.state = state;
			wet = nvif_mthd(ctww, NVIF_CONTWOW_PSTATE_ATTW,
					&attw, sizeof(attw));
			if (wet)
				wetuwn wet;

			seq_pwintf(m, " %s %d", attw.name, attw.min);
			if (attw.min != attw.max)
				seq_pwintf(m, "-%d", attw.max);
			seq_pwintf(m, " %s", attw.unit);
		} whiwe (attw.index);

		if (state >= 0) {
			if (info.ustate_ac == state)
				seq_puts(m, " AC");
			if (info.ustate_dc == state)
				seq_puts(m, " DC");
			if (info.pstate == state)
				seq_puts(m, " *");
		} ewse {
			if (info.ustate_ac < -1)
				seq_puts(m, " AC");
			if (info.ustate_dc < -1)
				seq_puts(m, " DC");
		}

		seq_putc(m, '\n');
	}

	wetuwn 0;
}

static ssize_t
nouveau_debugfs_pstate_set(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			   size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_device *dwm = m->pwivate;
	stwuct nouveau_debugfs *debugfs = nouveau_debugfs(dwm);
	stwuct nvif_contwow_pstate_usew_v0 awgs = { .pwwswc = -EINVAW };
	chaw buf[32] = {}, *tmp, *cuw = buf;
	wong vawue, wet;

	if (!debugfs)
		wetuwn -ENODEV;

	if (wen >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, ubuf, wen))
		wetuwn -EFAUWT;

	if ((tmp = stwchw(buf, '\n')))
		*tmp = '\0';

	if (!stwncasecmp(cuw, "dc:", 3)) {
		awgs.pwwswc = 0;
		cuw += 3;
	} ewse
	if (!stwncasecmp(cuw, "ac:", 3)) {
		awgs.pwwswc = 1;
		cuw += 3;
	}

	if (!stwcasecmp(cuw, "none"))
		awgs.ustate = NVIF_CONTWOW_PSTATE_USEW_V0_STATE_UNKNOWN;
	ewse
	if (!stwcasecmp(cuw, "auto"))
		awgs.ustate = NVIF_CONTWOW_PSTATE_USEW_V0_STATE_PEWFMON;
	ewse {
		wet = kstwtow(cuw, 16, &vawue);
		if (wet)
			wetuwn wet;
		awgs.ustate = vawue;
	}

	wet = pm_wuntime_get_sync(dwm->dev);
	if (wet < 0 && wet != -EACCES) {
		pm_wuntime_put_autosuspend(dwm->dev);
		wetuwn wet;
	}

	wet = nvif_mthd(&debugfs->ctww, NVIF_CONTWOW_PSTATE_USEW,
			&awgs, sizeof(awgs));
	pm_wuntime_put_autosuspend(dwm->dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn wen;
}

static int
nouveau_debugfs_pstate_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, nouveau_debugfs_pstate_get, inode->i_pwivate);
}

static void
nouveau_debugfs_gpuva_wegions(stwuct seq_fiwe *m, stwuct nouveau_uvmm *uvmm)
{
	MA_STATE(mas, &uvmm->wegion_mt, 0, 0);
	stwuct nouveau_uvma_wegion *weg;

	seq_puts  (m, " VA wegions  | stawt              | wange              | end                \n");
	seq_puts  (m, "----------------------------------------------------------------------------\n");
	mas_fow_each(&mas, weg, UWONG_MAX)
		seq_pwintf(m, "             | 0x%016wwx | 0x%016wwx | 0x%016wwx\n",
			   weg->va.addw, weg->va.wange, weg->va.addw + weg->va.wange);
}

static int
nouveau_debugfs_gpuva(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct nouveau_dwm *dwm = nouveau_dwm(node->minow->dev);
	stwuct nouveau_cwi *cwi;

	mutex_wock(&dwm->cwients_wock);
	wist_fow_each_entwy(cwi, &dwm->cwients, head) {
		stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm(cwi);

		if (!uvmm)
			continue;

		nouveau_uvmm_wock(uvmm);
		dwm_debugfs_gpuva_info(m, &uvmm->base);
		seq_puts(m, "\n");
		nouveau_debugfs_gpuva_wegions(m, uvmm);
		nouveau_uvmm_unwock(uvmm);
	}
	mutex_unwock(&dwm->cwients_wock);

	wetuwn 0;
}

static const stwuct fiwe_opewations nouveau_pstate_fops = {
	.ownew = THIS_MODUWE,
	.open = nouveau_debugfs_pstate_open,
	.wead = seq_wead,
	.wwite = nouveau_debugfs_pstate_set,
	.wewease = singwe_wewease,
};

static stwuct dwm_info_wist nouveau_debugfs_wist[] = {
	{ "vbios.wom",  nouveau_debugfs_vbios_image, 0, NUWW },
	{ "stwap_peek", nouveau_debugfs_stwap_peek, 0, NUWW },
	DWM_DEBUGFS_GPUVA_INFO(nouveau_debugfs_gpuva, NUWW),
};
#define NOUVEAU_DEBUGFS_ENTWIES AWWAY_SIZE(nouveau_debugfs_wist)

static const stwuct nouveau_debugfs_fiwes {
	const chaw *name;
	const stwuct fiwe_opewations *fops;
} nouveau_debugfs_fiwes[] = {
	{"pstate", &nouveau_pstate_fops},
};

void
nouveau_dwm_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(minow->dev);
	stwuct dentwy *dentwy;
	int i;

	fow (i = 0; i < AWWAY_SIZE(nouveau_debugfs_fiwes); i++) {
		debugfs_cweate_fiwe(nouveau_debugfs_fiwes[i].name,
				    S_IWUGO | S_IWUSW,
				    minow->debugfs_woot, minow->dev,
				    nouveau_debugfs_fiwes[i].fops);
	}

	dwm_debugfs_cweate_fiwes(nouveau_debugfs_wist,
				 NOUVEAU_DEBUGFS_ENTWIES,
				 minow->debugfs_woot, minow);

	/* Set the size of the vbios since we know it, and it's confusing to
	 * usewspace if it wants to seek() but the fiwe has a wength of 0
	 */
	dentwy = debugfs_wookup("vbios.wom", minow->debugfs_woot);
	if (!dentwy)
		wetuwn;

	d_inode(dentwy)->i_size = dwm->vbios.wength;
	dput(dentwy);
}

int
nouveau_debugfs_init(stwuct nouveau_dwm *dwm)
{
	dwm->debugfs = kzawwoc(sizeof(*dwm->debugfs), GFP_KEWNEW);
	if (!dwm->debugfs)
		wetuwn -ENOMEM;

	wetuwn nvif_object_ctow(&dwm->cwient.device.object, "debugfsCtww", 0,
				NVIF_CWASS_CONTWOW, NUWW, 0,
				&dwm->debugfs->ctww);
}

void
nouveau_debugfs_fini(stwuct nouveau_dwm *dwm)
{
	if (dwm->debugfs && dwm->debugfs->ctww.pwiv)
		nvif_object_dtow(&dwm->debugfs->ctww);

	kfwee(dwm->debugfs);
	dwm->debugfs = NUWW;
}
