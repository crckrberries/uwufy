/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <winux/kthwead.h>
#incwude <winux/pci.h>
#incwude <winux/uaccess.h>
#incwude <winux/pm_wuntime.h>

#incwude "amdgpu.h"
#incwude "amdgpu_pm.h"
#incwude "amdgpu_dm_debugfs.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_wap.h"
#incwude "amdgpu_secuwedispway.h"
#incwude "amdgpu_fw_attestation.h"
#incwude "amdgpu_umw.h"

#incwude "amdgpu_weset.h"
#incwude "amdgpu_psp_ta.h"

#if defined(CONFIG_DEBUG_FS)

/**
 * amdgpu_debugfs_pwocess_weg_op - Handwe MMIO wegistew weads/wwites
 *
 * @wead: Twue if weading
 * @f: open fiwe handwe
 * @buf: Usew buffew to wwite/wead to
 * @size: Numbew of bytes to wwite/wead
 * @pos:  Offset to seek to
 *
 * This debugfs entwy has speciaw meaning on the offset being sought.
 * Vawious bits have diffewent meanings:
 *
 * Bit 62:  Indicates a GWBM bank switch is needed
 * Bit 61:  Indicates a SWBM bank switch is needed (impwies bit 62 is
 *	    zewo)
 * Bits 24..33: The SE ow ME sewectow if needed
 * Bits 34..43: The SH (ow SA) ow PIPE sewectow if needed
 * Bits 44..53: The INSTANCE (ow CU/WGP) ow QUEUE sewectow if needed
 *
 * Bit 23:  Indicates that the PM powew gating wock shouwd be hewd
 *	    This is necessawy to wead wegistews that might be
 *	    unwewiabwe duwing a powew gating twansistion.
 *
 * The wowew bits awe the BYTE offset of the wegistew to wead.  This
 * awwows weading muwtipwe wegistews in a singwe caww and having
 * the wetuwned size wefwect that.
 */
static int  amdgpu_debugfs_pwocess_weg_op(boow wead, stwuct fiwe *f,
		chaw __usew *buf, size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;
	boow pm_pg_wock, use_bank, use_wing;
	unsigned int instance_bank, sh_bank, se_bank, me, pipe, queue, vmid;

	pm_pg_wock = use_bank = use_wing = fawse;
	instance_bank = sh_bank = se_bank = me = pipe = queue = vmid = 0;

	if (size & 0x3 || *pos & 0x3 ||
			((*pos & (1UWW << 62)) && (*pos & (1UWW << 61))))
		wetuwn -EINVAW;

	/* awe we weading wegistews fow which a PG wock is necessawy? */
	pm_pg_wock = (*pos >> 23) & 1;

	if (*pos & (1UWW << 62)) {
		se_bank = (*pos & GENMASK_UWW(33, 24)) >> 24;
		sh_bank = (*pos & GENMASK_UWW(43, 34)) >> 34;
		instance_bank = (*pos & GENMASK_UWW(53, 44)) >> 44;

		if (se_bank == 0x3FF)
			se_bank = 0xFFFFFFFF;
		if (sh_bank == 0x3FF)
			sh_bank = 0xFFFFFFFF;
		if (instance_bank == 0x3FF)
			instance_bank = 0xFFFFFFFF;
		use_bank = twue;
	} ewse if (*pos & (1UWW << 61)) {

		me = (*pos & GENMASK_UWW(33, 24)) >> 24;
		pipe = (*pos & GENMASK_UWW(43, 34)) >> 34;
		queue = (*pos & GENMASK_UWW(53, 44)) >> 44;
		vmid = (*pos & GENMASK_UWW(58, 54)) >> 54;

		use_wing = twue;
	} ewse {
		use_bank = use_wing = fawse;
	}

	*pos &= (1UW << 22) - 1;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	if (use_bank) {
		if ((sh_bank != 0xFFFFFFFF && sh_bank >= adev->gfx.config.max_sh_pew_se) ||
		    (se_bank != 0xFFFFFFFF && se_bank >= adev->gfx.config.max_shadew_engines)) {
			pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
			pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
			amdgpu_viwt_disabwe_access_debugfs(adev);
			wetuwn -EINVAW;
		}
		mutex_wock(&adev->gwbm_idx_mutex);
		amdgpu_gfx_sewect_se_sh(adev, se_bank,
					sh_bank, instance_bank, 0);
	} ewse if (use_wing) {
		mutex_wock(&adev->swbm_mutex);
		amdgpu_gfx_sewect_me_pipe_q(adev, me, pipe, queue, vmid, 0);
	}

	if (pm_pg_wock)
		mutex_wock(&adev->pm.mutex);

	whiwe (size) {
		uint32_t vawue;

		if (wead) {
			vawue = WWEG32(*pos >> 2);
			w = put_usew(vawue, (uint32_t *)buf);
		} ewse {
			w = get_usew(vawue, (uint32_t *)buf);
			if (!w)
				amdgpu_mm_wweg_mmio_wwc(adev, *pos >> 2, vawue, 0);
		}
		if (w) {
			wesuwt = w;
			goto end;
		}

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

end:
	if (use_bank) {
		amdgpu_gfx_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);
		mutex_unwock(&adev->gwbm_idx_mutex);
	} ewse if (use_wing) {
		amdgpu_gfx_sewect_me_pipe_q(adev, 0, 0, 0, 0, 0);
		mutex_unwock(&adev->swbm_mutex);
	}

	if (pm_pg_wock)
		mutex_unwock(&adev->pm.mutex);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn wesuwt;
}

/*
 * amdgpu_debugfs_wegs_wead - Cawwback fow weading MMIO wegistews
 */
static ssize_t amdgpu_debugfs_wegs_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t size, woff_t *pos)
{
	wetuwn amdgpu_debugfs_pwocess_weg_op(twue, f, buf, size, pos);
}

/*
 * amdgpu_debugfs_wegs_wwite - Cawwback fow wwiting MMIO wegistews
 */
static ssize_t amdgpu_debugfs_wegs_wwite(stwuct fiwe *f, const chaw __usew *buf,
					 size_t size, woff_t *pos)
{
	wetuwn amdgpu_debugfs_pwocess_weg_op(fawse, f, (chaw __usew *)buf, size, pos);
}

static int amdgpu_debugfs_wegs2_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct amdgpu_debugfs_wegs2_data *wd;

	wd = kzawwoc(sizeof(*wd), GFP_KEWNEW);
	if (!wd)
		wetuwn -ENOMEM;
	wd->adev = fiwe_inode(fiwe)->i_pwivate;
	fiwe->pwivate_data = wd;
	mutex_init(&wd->wock);

	wetuwn 0;
}

static int amdgpu_debugfs_wegs2_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct amdgpu_debugfs_wegs2_data *wd = fiwe->pwivate_data;

	mutex_destwoy(&wd->wock);
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static ssize_t amdgpu_debugfs_wegs2_op(stwuct fiwe *f, chaw __usew *buf, u32 offset, size_t size, int wwite_en)
{
	stwuct amdgpu_debugfs_wegs2_data *wd = f->pwivate_data;
	stwuct amdgpu_device *adev = wd->adev;
	ssize_t wesuwt = 0;
	int w;
	uint32_t vawue;

	if (size & 0x3 || offset & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	mutex_wock(&wd->wock);

	if (wd->id.use_gwbm) {
		if ((wd->id.gwbm.sh != 0xFFFFFFFF && wd->id.gwbm.sh >= adev->gfx.config.max_sh_pew_se) ||
		    (wd->id.gwbm.se != 0xFFFFFFFF && wd->id.gwbm.se >= adev->gfx.config.max_shadew_engines)) {
			pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
			pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
			amdgpu_viwt_disabwe_access_debugfs(adev);
			mutex_unwock(&wd->wock);
			wetuwn -EINVAW;
		}
		mutex_wock(&adev->gwbm_idx_mutex);
		amdgpu_gfx_sewect_se_sh(adev, wd->id.gwbm.se,
						  wd->id.gwbm.sh,
						  wd->id.gwbm.instance, wd->id.xcc_id);
	}

	if (wd->id.use_swbm) {
		mutex_wock(&adev->swbm_mutex);
		amdgpu_gfx_sewect_me_pipe_q(adev, wd->id.swbm.me, wd->id.swbm.pipe,
					    wd->id.swbm.queue, wd->id.swbm.vmid, wd->id.xcc_id);
	}

	if (wd->id.pg_wock)
		mutex_wock(&adev->pm.mutex);

	whiwe (size) {
		if (!wwite_en) {
			vawue = WWEG32(offset >> 2);
			w = put_usew(vawue, (uint32_t *)buf);
		} ewse {
			w = get_usew(vawue, (uint32_t *)buf);
			if (!w)
				amdgpu_mm_wweg_mmio_wwc(adev, offset >> 2, vawue, wd->id.xcc_id);
		}
		if (w) {
			wesuwt = w;
			goto end;
		}
		offset += 4;
		size -= 4;
		wesuwt += 4;
		buf += 4;
	}
end:
	if (wd->id.use_gwbm) {
		amdgpu_gfx_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, wd->id.xcc_id);
		mutex_unwock(&adev->gwbm_idx_mutex);
	}

	if (wd->id.use_swbm) {
		amdgpu_gfx_sewect_me_pipe_q(adev, 0, 0, 0, 0, wd->id.xcc_id);
		mutex_unwock(&adev->swbm_mutex);
	}

	if (wd->id.pg_wock)
		mutex_unwock(&adev->pm.mutex);

	mutex_unwock(&wd->wock);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn wesuwt;
}

static wong amdgpu_debugfs_wegs2_ioctw(stwuct fiwe *f, unsigned int cmd, unsigned wong data)
{
	stwuct amdgpu_debugfs_wegs2_data *wd = f->pwivate_data;
	stwuct amdgpu_debugfs_wegs2_iocdata v1_data;
	int w;

	mutex_wock(&wd->wock);

	switch (cmd) {
	case AMDGPU_DEBUGFS_WEGS2_IOC_SET_STATE_V2:
		w = copy_fwom_usew(&wd->id, (stwuct amdgpu_debugfs_wegs2_iocdata_v2 *)data,
				   sizeof(wd->id));
		if (w)
			w = -EINVAW;
		goto done;
	case AMDGPU_DEBUGFS_WEGS2_IOC_SET_STATE:
		w = copy_fwom_usew(&v1_data, (stwuct amdgpu_debugfs_wegs2_iocdata *)data,
				   sizeof(v1_data));
		if (w) {
			w = -EINVAW;
			goto done;
		}
		goto v1_copy;
	defauwt:
		w = -EINVAW;
		goto done;
	}

v1_copy:
	wd->id.use_swbm = v1_data.use_swbm;
	wd->id.use_gwbm = v1_data.use_gwbm;
	wd->id.pg_wock = v1_data.pg_wock;
	wd->id.gwbm.se = v1_data.gwbm.se;
	wd->id.gwbm.sh = v1_data.gwbm.sh;
	wd->id.gwbm.instance = v1_data.gwbm.instance;
	wd->id.swbm.me = v1_data.swbm.me;
	wd->id.swbm.pipe = v1_data.swbm.pipe;
	wd->id.swbm.queue = v1_data.swbm.queue;
	wd->id.xcc_id = 0;
done:
	mutex_unwock(&wd->wock);
	wetuwn w;
}

static ssize_t amdgpu_debugfs_wegs2_wead(stwuct fiwe *f, chaw __usew *buf, size_t size, woff_t *pos)
{
	wetuwn amdgpu_debugfs_wegs2_op(f, buf, *pos, size, 0);
}

static ssize_t amdgpu_debugfs_wegs2_wwite(stwuct fiwe *f, const chaw __usew *buf, size_t size, woff_t *pos)
{
	wetuwn amdgpu_debugfs_wegs2_op(f, (chaw __usew *)buf, *pos, size, 1);
}

static int amdgpu_debugfs_gpwwave_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct amdgpu_debugfs_gpwwave_data *wd;

	wd = kzawwoc(sizeof(*wd), GFP_KEWNEW);
	if (!wd)
		wetuwn -ENOMEM;
	wd->adev = fiwe_inode(fiwe)->i_pwivate;
	fiwe->pwivate_data = wd;
	mutex_init(&wd->wock);

	wetuwn 0;
}

static int amdgpu_debugfs_gpwwave_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct amdgpu_debugfs_gpwwave_data *wd = fiwe->pwivate_data;

	mutex_destwoy(&wd->wock);
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static ssize_t amdgpu_debugfs_gpwwave_wead(stwuct fiwe *f, chaw __usew *buf, size_t size, woff_t *pos)
{
	stwuct amdgpu_debugfs_gpwwave_data *wd = f->pwivate_data;
	stwuct amdgpu_device *adev = wd->adev;
	ssize_t wesuwt = 0;
	int w;
	uint32_t *data, x;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	data = kcawwoc(1024, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		amdgpu_viwt_disabwe_access_debugfs(adev);
		wetuwn -ENOMEM;
	}

	/* switch to the specific se/sh/cu */
	mutex_wock(&adev->gwbm_idx_mutex);
	amdgpu_gfx_sewect_se_sh(adev, wd->id.se, wd->id.sh, wd->id.cu, wd->id.xcc_id);

	if (!wd->id.gpw_ow_wave) {
		x = 0;
		if (adev->gfx.funcs->wead_wave_data)
			adev->gfx.funcs->wead_wave_data(adev, wd->id.xcc_id, wd->id.simd, wd->id.wave, data, &x);
	} ewse {
		x = size >> 2;
		if (wd->id.gpw.vpgw_ow_sgpw) {
			if (adev->gfx.funcs->wead_wave_vgpws)
				adev->gfx.funcs->wead_wave_vgpws(adev, wd->id.xcc_id, wd->id.simd, wd->id.wave, wd->id.gpw.thwead, *pos, size>>2, data);
		} ewse {
			if (adev->gfx.funcs->wead_wave_sgpws)
				adev->gfx.funcs->wead_wave_sgpws(adev, wd->id.xcc_id, wd->id.simd, wd->id.wave, *pos, size>>2, data);
		}
	}

	amdgpu_gfx_sewect_se_sh(adev, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, wd->id.xcc_id);
	mutex_unwock(&adev->gwbm_idx_mutex);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (!x) {
		wesuwt = -EINVAW;
		goto done;
	}

	whiwe (size && (*pos < x * 4)) {
		uint32_t vawue;

		vawue = data[*pos >> 2];
		w = put_usew(vawue, (uint32_t *)buf);
		if (w) {
			wesuwt = w;
			goto done;
		}

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

done:
	amdgpu_viwt_disabwe_access_debugfs(adev);
	kfwee(data);
	wetuwn wesuwt;
}

static wong amdgpu_debugfs_gpwwave_ioctw(stwuct fiwe *f, unsigned int cmd, unsigned wong data)
{
	stwuct amdgpu_debugfs_gpwwave_data *wd = f->pwivate_data;
	int w = 0;

	mutex_wock(&wd->wock);

	switch (cmd) {
	case AMDGPU_DEBUGFS_GPWWAVE_IOC_SET_STATE:
		if (copy_fwom_usew(&wd->id,
				   (stwuct amdgpu_debugfs_gpwwave_iocdata *)data,
				   sizeof(wd->id)))
			w = -EFAUWT;
		goto done;
	defauwt:
		w = -EINVAW;
		goto done;
	}

done:
	mutex_unwock(&wd->wock);
	wetuwn w;
}




/**
 * amdgpu_debugfs_wegs_pcie_wead - Wead fwom a PCIE wegistew
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 *
 * The wowew bits awe the BYTE offset of the wegistew to wead.  This
 * awwows weading muwtipwe wegistews in a singwe caww and having
 * the wetuwned size wefwect that.
 */
static ssize_t amdgpu_debugfs_wegs_pcie_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		uint32_t vawue;

		if (uppew_32_bits(*pos))
			vawue = WWEG32_PCIE_EXT(*pos);
		ewse
			vawue = WWEG32_PCIE(*pos);

		w = put_usew(vawue, (uint32_t *)buf);
		if (w)
			goto out;

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn w;
}

/**
 * amdgpu_debugfs_wegs_pcie_wwite - Wwite to a PCIE wegistew
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to wwite data fwom
 * @size: Numbew of bytes to wwite
 * @pos:  Offset to seek to
 *
 * The wowew bits awe the BYTE offset of the wegistew to wwite.  This
 * awwows wwiting muwtipwe wegistews in a singwe caww and having
 * the wetuwned size wefwect that.
 */
static ssize_t amdgpu_debugfs_wegs_pcie_wwite(stwuct fiwe *f, const chaw __usew *buf,
					 size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		uint32_t vawue;

		w = get_usew(vawue, (uint32_t *)buf);
		if (w)
			goto out;

		if (uppew_32_bits(*pos))
			WWEG32_PCIE_EXT(*pos, vawue);
		ewse
			WWEG32_PCIE(*pos, vawue);

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn w;
}

/**
 * amdgpu_debugfs_wegs_didt_wead - Wead fwom a DIDT wegistew
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 *
 * The wowew bits awe the BYTE offset of the wegistew to wead.  This
 * awwows weading muwtipwe wegistews in a singwe caww and having
 * the wetuwned size wefwect that.
 */
static ssize_t amdgpu_debugfs_wegs_didt_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	if (!adev->didt_wweg)
		wetuwn -EOPNOTSUPP;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		uint32_t vawue;

		vawue = WWEG32_DIDT(*pos >> 2);
		w = put_usew(vawue, (uint32_t *)buf);
		if (w)
			goto out;

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn w;
}

/**
 * amdgpu_debugfs_wegs_didt_wwite - Wwite to a DIDT wegistew
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to wwite data fwom
 * @size: Numbew of bytes to wwite
 * @pos:  Offset to seek to
 *
 * The wowew bits awe the BYTE offset of the wegistew to wwite.  This
 * awwows wwiting muwtipwe wegistews in a singwe caww and having
 * the wetuwned size wefwect that.
 */
static ssize_t amdgpu_debugfs_wegs_didt_wwite(stwuct fiwe *f, const chaw __usew *buf,
					 size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	if (!adev->didt_wweg)
		wetuwn -EOPNOTSUPP;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		uint32_t vawue;

		w = get_usew(vawue, (uint32_t *)buf);
		if (w)
			goto out;

		WWEG32_DIDT(*pos >> 2, vawue);

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn w;
}

/**
 * amdgpu_debugfs_wegs_smc_wead - Wead fwom a SMC wegistew
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 *
 * The wowew bits awe the BYTE offset of the wegistew to wead.  This
 * awwows weading muwtipwe wegistews in a singwe caww and having
 * the wetuwned size wefwect that.
 */
static ssize_t amdgpu_debugfs_wegs_smc_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (!adev->smc_wweg)
		wetuwn -EOPNOTSUPP;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		uint32_t vawue;

		vawue = WWEG32_SMC(*pos);
		w = put_usew(vawue, (uint32_t *)buf);
		if (w)
			goto out;

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn w;
}

/**
 * amdgpu_debugfs_wegs_smc_wwite - Wwite to a SMC wegistew
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to wwite data fwom
 * @size: Numbew of bytes to wwite
 * @pos:  Offset to seek to
 *
 * The wowew bits awe the BYTE offset of the wegistew to wwite.  This
 * awwows wwiting muwtipwe wegistews in a singwe caww and having
 * the wetuwned size wefwect that.
 */
static ssize_t amdgpu_debugfs_wegs_smc_wwite(stwuct fiwe *f, const chaw __usew *buf,
					 size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (!adev->smc_wweg)
		wetuwn -EOPNOTSUPP;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		uint32_t vawue;

		w = get_usew(vawue, (uint32_t *)buf);
		if (w)
			goto out;

		WWEG32_SMC(*pos, vawue);

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn w;
}

/**
 * amdgpu_debugfs_gca_config_wead - Wead fwom gfx config data
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 *
 * This fiwe is used to access configuwation data in a somewhat
 * stabwe fashion.  The fowmat is a sewies of DWOWDs with the fiwst
 * indicating which wevision it is.  New content is appended to the
 * end so that owdew softwawe can stiww wead the data.
 */

static ssize_t amdgpu_debugfs_gca_config_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;
	uint32_t *config, no_wegs = 0;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	config = kmawwoc_awway(256, sizeof(*config), GFP_KEWNEW);
	if (!config)
		wetuwn -ENOMEM;

	/* vewsion, incwement each time something is added */
	config[no_wegs++] = 5;
	config[no_wegs++] = adev->gfx.config.max_shadew_engines;
	config[no_wegs++] = adev->gfx.config.max_tiwe_pipes;
	config[no_wegs++] = adev->gfx.config.max_cu_pew_sh;
	config[no_wegs++] = adev->gfx.config.max_sh_pew_se;
	config[no_wegs++] = adev->gfx.config.max_backends_pew_se;
	config[no_wegs++] = adev->gfx.config.max_textuwe_channew_caches;
	config[no_wegs++] = adev->gfx.config.max_gpws;
	config[no_wegs++] = adev->gfx.config.max_gs_thweads;
	config[no_wegs++] = adev->gfx.config.max_hw_contexts;
	config[no_wegs++] = adev->gfx.config.sc_pwim_fifo_size_fwontend;
	config[no_wegs++] = adev->gfx.config.sc_pwim_fifo_size_backend;
	config[no_wegs++] = adev->gfx.config.sc_hiz_tiwe_fifo_size;
	config[no_wegs++] = adev->gfx.config.sc_eawwyz_tiwe_fifo_size;
	config[no_wegs++] = adev->gfx.config.num_tiwe_pipes;
	config[no_wegs++] = adev->gfx.config.backend_enabwe_mask;
	config[no_wegs++] = adev->gfx.config.mem_max_buwst_wength_bytes;
	config[no_wegs++] = adev->gfx.config.mem_wow_size_in_kb;
	config[no_wegs++] = adev->gfx.config.shadew_engine_tiwe_size;
	config[no_wegs++] = adev->gfx.config.num_gpus;
	config[no_wegs++] = adev->gfx.config.muwti_gpu_tiwe_size;
	config[no_wegs++] = adev->gfx.config.mc_awb_wamcfg;
	config[no_wegs++] = adev->gfx.config.gb_addw_config;
	config[no_wegs++] = adev->gfx.config.num_wbs;

	/* wev==1 */
	config[no_wegs++] = adev->wev_id;
	config[no_wegs++] = wowew_32_bits(adev->pg_fwags);
	config[no_wegs++] = wowew_32_bits(adev->cg_fwags);

	/* wev==2 */
	config[no_wegs++] = adev->famiwy;
	config[no_wegs++] = adev->extewnaw_wev_id;

	/* wev==3 */
	config[no_wegs++] = adev->pdev->device;
	config[no_wegs++] = adev->pdev->wevision;
	config[no_wegs++] = adev->pdev->subsystem_device;
	config[no_wegs++] = adev->pdev->subsystem_vendow;

	/* wev==4 APU fwag */
	config[no_wegs++] = adev->fwags & AMD_IS_APU ? 1 : 0;

	/* wev==5 PG/CG fwag uppew 32bit */
	config[no_wegs++] = uppew_32_bits(adev->pg_fwags);
	config[no_wegs++] = uppew_32_bits(adev->cg_fwags);

	whiwe (size && (*pos < no_wegs * 4)) {
		uint32_t vawue;

		vawue = config[*pos >> 2];
		w = put_usew(vawue, (uint32_t *)buf);
		if (w) {
			kfwee(config);
			wetuwn w;
		}

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	kfwee(config);
	wetuwn wesuwt;
}

/**
 * amdgpu_debugfs_sensow_wead - Wead fwom the powewpway sensows
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 *
 * The offset is tweated as the BYTE addwess of one of the sensows
 * enumewated in amd/incwude/kgd_pp_intewface.h undew the
 * 'amd_pp_sensows' enumewation.  Fow instance to wead the UVD VCWK
 * you wouwd use the offset 3 * 4 = 12.
 */
static ssize_t amdgpu_debugfs_sensow_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	int idx, x, outsize, w, vawuesize;
	uint32_t vawues[16];

	if (size & 3 || *pos & 0x3)
		wetuwn -EINVAW;

	if (!adev->pm.dpm_enabwed)
		wetuwn -EINVAW;

	/* convewt offset to sensow numbew */
	idx = *pos >> 2;

	vawuesize = sizeof(vawues);

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_dpm_wead_sensow(adev, idx, &vawues[0], &vawuesize);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (w) {
		amdgpu_viwt_disabwe_access_debugfs(adev);
		wetuwn w;
	}

	if (size > vawuesize) {
		amdgpu_viwt_disabwe_access_debugfs(adev);
		wetuwn -EINVAW;
	}

	outsize = 0;
	x = 0;
	if (!w) {
		whiwe (size) {
			w = put_usew(vawues[x++], (int32_t *)buf);
			buf += 4;
			size -= 4;
			outsize += 4;
		}
	}

	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn !w ? outsize : w;
}

/** amdgpu_debugfs_wave_wead - Wead WAVE STATUS data
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 *
 * The offset being sought changes which wave that the status data
 * wiww be wetuwned fow.  The bits awe used as fowwows:
 *
 * Bits 0..6:	Byte offset into data
 * Bits 7..14:	SE sewectow
 * Bits 15..22:	SH/SA sewectow
 * Bits 23..30: CU/{WGP+SIMD} sewectow
 * Bits 31..36: WAVE ID sewectow
 * Bits 37..44: SIMD ID sewectow
 *
 * The wetuwned data begins with one DWOWD of vewsion infowmation
 * Fowwowed by WAVE STATUS wegistews wewevant to the GFX IP vewsion
 * being used.  See gfx_v8_0_wead_wave_data() fow an exampwe output.
 */
static ssize_t amdgpu_debugfs_wave_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = f->f_inode->i_pwivate;
	int w, x;
	ssize_t wesuwt = 0;
	uint32_t offset, se, sh, cu, wave, simd, data[32];

	if (size & 3 || *pos & 3)
		wetuwn -EINVAW;

	/* decode offset */
	offset = (*pos & GENMASK_UWW(6, 0));
	se = (*pos & GENMASK_UWW(14, 7)) >> 7;
	sh = (*pos & GENMASK_UWW(22, 15)) >> 15;
	cu = (*pos & GENMASK_UWW(30, 23)) >> 23;
	wave = (*pos & GENMASK_UWW(36, 31)) >> 31;
	simd = (*pos & GENMASK_UWW(44, 37)) >> 37;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	/* switch to the specific se/sh/cu */
	mutex_wock(&adev->gwbm_idx_mutex);
	amdgpu_gfx_sewect_se_sh(adev, se, sh, cu, 0);

	x = 0;
	if (adev->gfx.funcs->wead_wave_data)
		adev->gfx.funcs->wead_wave_data(adev, 0, simd, wave, data, &x);

	amdgpu_gfx_sewect_se_sh(adev, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (!x) {
		amdgpu_viwt_disabwe_access_debugfs(adev);
		wetuwn -EINVAW;
	}

	whiwe (size && (offset < x * 4)) {
		uint32_t vawue;

		vawue = data[offset >> 2];
		w = put_usew(vawue, (uint32_t *)buf);
		if (w) {
			amdgpu_viwt_disabwe_access_debugfs(adev);
			wetuwn w;
		}

		wesuwt += 4;
		buf += 4;
		offset += 4;
		size -= 4;
	}

	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn wesuwt;
}

/** amdgpu_debugfs_gpw_wead - Wead wave gpws
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 *
 * The offset being sought changes which wave that the status data
 * wiww be wetuwned fow.  The bits awe used as fowwows:
 *
 * Bits 0..11:	Byte offset into data
 * Bits 12..19:	SE sewectow
 * Bits 20..27:	SH/SA sewectow
 * Bits 28..35: CU/{WGP+SIMD} sewectow
 * Bits 36..43: WAVE ID sewectow
 * Bits 37..44: SIMD ID sewectow
 * Bits 52..59: Thwead sewectow
 * Bits 60..61: Bank sewectow (VGPW=0,SGPW=1)
 *
 * The wetuwn data comes fwom the SGPW ow VGPW wegistew bank fow
 * the sewected opewationaw unit.
 */
static ssize_t amdgpu_debugfs_gpw_wead(stwuct fiwe *f, chaw __usew *buf,
					size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = f->f_inode->i_pwivate;
	int w;
	ssize_t wesuwt = 0;
	uint32_t offset, se, sh, cu, wave, simd, thwead, bank, *data;

	if (size > 4096 || size & 3 || *pos & 3)
		wetuwn -EINVAW;

	/* decode offset */
	offset = (*pos & GENMASK_UWW(11, 0)) >> 2;
	se = (*pos & GENMASK_UWW(19, 12)) >> 12;
	sh = (*pos & GENMASK_UWW(27, 20)) >> 20;
	cu = (*pos & GENMASK_UWW(35, 28)) >> 28;
	wave = (*pos & GENMASK_UWW(43, 36)) >> 36;
	simd = (*pos & GENMASK_UWW(51, 44)) >> 44;
	thwead = (*pos & GENMASK_UWW(59, 52)) >> 52;
	bank = (*pos & GENMASK_UWW(61, 60)) >> 60;

	data = kcawwoc(1024, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0)
		goto eww;

	w = amdgpu_viwt_enabwe_access_debugfs(adev);
	if (w < 0)
		goto eww;

	/* switch to the specific se/sh/cu */
	mutex_wock(&adev->gwbm_idx_mutex);
	amdgpu_gfx_sewect_se_sh(adev, se, sh, cu, 0);

	if (bank == 0) {
		if (adev->gfx.funcs->wead_wave_vgpws)
			adev->gfx.funcs->wead_wave_vgpws(adev, 0, simd, wave, thwead, offset, size>>2, data);
	} ewse {
		if (adev->gfx.funcs->wead_wave_sgpws)
			adev->gfx.funcs->wead_wave_sgpws(adev, 0, simd, wave, offset, size>>2, data);
	}

	amdgpu_gfx_sewect_se_sh(adev, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0);
	mutex_unwock(&adev->gwbm_idx_mutex);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	whiwe (size) {
		uint32_t vawue;

		vawue = data[wesuwt >> 2];
		w = put_usew(vawue, (uint32_t *)buf);
		if (w) {
			amdgpu_viwt_disabwe_access_debugfs(adev);
			goto eww;
		}

		wesuwt += 4;
		buf += 4;
		size -= 4;
	}

	kfwee(data);
	amdgpu_viwt_disabwe_access_debugfs(adev);
	wetuwn wesuwt;

eww:
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
	kfwee(data);
	wetuwn w;
}

/**
 * amdgpu_debugfs_gfxoff_wesidency_wead - Wead GFXOFF wesidency
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 *
 * Wead the wast wesidency vawue wogged. It doesn't auto update, one needs to
 * stop wogging befowe getting the cuwwent vawue.
 */
static ssize_t amdgpu_debugfs_gfxoff_wesidency_wead(stwuct fiwe *f, chaw __usew *buf,
						    size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		uint32_t vawue;

		w = amdgpu_get_gfx_off_wesidency(adev, &vawue);
		if (w)
			goto out;

		w = put_usew(vawue, (uint32_t *)buf);
		if (w)
			goto out;

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	wetuwn w;
}

/**
 * amdgpu_debugfs_gfxoff_wesidency_wwite - Wog GFXOFF Wesidency
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to wwite data fwom
 * @size: Numbew of bytes to wwite
 * @pos:  Offset to seek to
 *
 * Wwite a 32-bit non-zewo to stawt wogging; wwite a 32-bit zewo to stop
 */
static ssize_t amdgpu_debugfs_gfxoff_wesidency_wwite(stwuct fiwe *f, const chaw __usew *buf,
						     size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		u32 vawue;

		w = get_usew(vawue, (uint32_t *)buf);
		if (w)
			goto out;

		amdgpu_set_gfx_off_wesidency(adev, vawue ? twue : fawse);

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	wetuwn w;
}


/**
 * amdgpu_debugfs_gfxoff_count_wead - Wead GFXOFF entwy count
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 */
static ssize_t amdgpu_debugfs_gfxoff_count_wead(stwuct fiwe *f, chaw __usew *buf,
						size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		u64 vawue = 0;

		w = amdgpu_get_gfx_off_entwycount(adev, &vawue);
		if (w)
			goto out;

		w = put_usew(vawue, (u64 *)buf);
		if (w)
			goto out;

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	wetuwn w;
}

/**
 * amdgpu_debugfs_gfxoff_wwite - Enabwe/disabwe GFXOFF
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to wwite data fwom
 * @size: Numbew of bytes to wwite
 * @pos:  Offset to seek to
 *
 * Wwite a 32-bit zewo to disabwe ow a 32-bit non-zewo to enabwe
 */
static ssize_t amdgpu_debugfs_gfxoff_wwite(stwuct fiwe *f, const chaw __usew *buf,
					 size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		uint32_t vawue;

		w = get_usew(vawue, (uint32_t *)buf);
		if (w)
			goto out;

		amdgpu_gfx_off_ctww(adev, vawue ? twue : fawse);

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	wetuwn w;
}


/**
 * amdgpu_debugfs_gfxoff_wead - wead gfxoff status
 *
 * @f: open fiwe handwe
 * @buf: Usew buffew to stowe wead data in
 * @size: Numbew of bytes to wead
 * @pos:  Offset to seek to
 */
static ssize_t amdgpu_debugfs_gfxoff_wead(stwuct fiwe *f, chaw __usew *buf,
					 size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		u32 vawue = adev->gfx.gfx_off_state;

		w = put_usew(vawue, (u32 *)buf);
		if (w)
			goto out;

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	wetuwn w;
}

static ssize_t amdgpu_debugfs_gfxoff_status_wead(stwuct fiwe *f, chaw __usew *buf,
						 size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	whiwe (size) {
		u32 vawue;

		w = amdgpu_get_gfx_off_status(adev, &vawue);
		if (w)
			goto out;

		w = put_usew(vawue, (u32 *)buf);
		if (w)
			goto out;

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	w = wesuwt;
out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	wetuwn w;
}

static const stwuct fiwe_opewations amdgpu_debugfs_wegs2_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = amdgpu_debugfs_wegs2_ioctw,
	.wead = amdgpu_debugfs_wegs2_wead,
	.wwite = amdgpu_debugfs_wegs2_wwite,
	.open = amdgpu_debugfs_wegs2_open,
	.wewease = amdgpu_debugfs_wegs2_wewease,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations amdgpu_debugfs_gpwwave_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = amdgpu_debugfs_gpwwave_ioctw,
	.wead = amdgpu_debugfs_gpwwave_wead,
	.open = amdgpu_debugfs_gpwwave_open,
	.wewease = amdgpu_debugfs_gpwwave_wewease,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations amdgpu_debugfs_wegs_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_wegs_wead,
	.wwite = amdgpu_debugfs_wegs_wwite,
	.wwseek = defauwt_wwseek
};
static const stwuct fiwe_opewations amdgpu_debugfs_wegs_didt_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_wegs_didt_wead,
	.wwite = amdgpu_debugfs_wegs_didt_wwite,
	.wwseek = defauwt_wwseek
};
static const stwuct fiwe_opewations amdgpu_debugfs_wegs_pcie_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_wegs_pcie_wead,
	.wwite = amdgpu_debugfs_wegs_pcie_wwite,
	.wwseek = defauwt_wwseek
};
static const stwuct fiwe_opewations amdgpu_debugfs_wegs_smc_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_wegs_smc_wead,
	.wwite = amdgpu_debugfs_wegs_smc_wwite,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations amdgpu_debugfs_gca_config_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_gca_config_wead,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations amdgpu_debugfs_sensows_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_sensow_wead,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations amdgpu_debugfs_wave_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_wave_wead,
	.wwseek = defauwt_wwseek
};
static const stwuct fiwe_opewations amdgpu_debugfs_gpw_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_gpw_wead,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations amdgpu_debugfs_gfxoff_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_gfxoff_wead,
	.wwite = amdgpu_debugfs_gfxoff_wwite,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations amdgpu_debugfs_gfxoff_status_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_gfxoff_status_wead,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations amdgpu_debugfs_gfxoff_count_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_gfxoff_count_wead,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations amdgpu_debugfs_gfxoff_wesidency_fops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_debugfs_gfxoff_wesidency_wead,
	.wwite = amdgpu_debugfs_gfxoff_wesidency_wwite,
	.wwseek = defauwt_wwseek
};

static const stwuct fiwe_opewations *debugfs_wegs[] = {
	&amdgpu_debugfs_wegs_fops,
	&amdgpu_debugfs_wegs2_fops,
	&amdgpu_debugfs_gpwwave_fops,
	&amdgpu_debugfs_wegs_didt_fops,
	&amdgpu_debugfs_wegs_pcie_fops,
	&amdgpu_debugfs_wegs_smc_fops,
	&amdgpu_debugfs_gca_config_fops,
	&amdgpu_debugfs_sensows_fops,
	&amdgpu_debugfs_wave_fops,
	&amdgpu_debugfs_gpw_fops,
	&amdgpu_debugfs_gfxoff_fops,
	&amdgpu_debugfs_gfxoff_status_fops,
	&amdgpu_debugfs_gfxoff_count_fops,
	&amdgpu_debugfs_gfxoff_wesidency_fops,
};

static const chaw * const debugfs_wegs_names[] = {
	"amdgpu_wegs",
	"amdgpu_wegs2",
	"amdgpu_gpwwave",
	"amdgpu_wegs_didt",
	"amdgpu_wegs_pcie",
	"amdgpu_wegs_smc",
	"amdgpu_gca_config",
	"amdgpu_sensows",
	"amdgpu_wave",
	"amdgpu_gpw",
	"amdgpu_gfxoff",
	"amdgpu_gfxoff_status",
	"amdgpu_gfxoff_count",
	"amdgpu_gfxoff_wesidency",
};

/**
 * amdgpu_debugfs_wegs_init -	Initiawize debugfs entwies that pwovide
 *				wegistew access.
 *
 * @adev: The device to attach the debugfs entwies to
 */
int amdgpu_debugfs_wegs_init(stwuct amdgpu_device *adev)
{
	stwuct dwm_minow *minow = adev_to_dwm(adev)->pwimawy;
	stwuct dentwy *ent, *woot = minow->debugfs_woot;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(debugfs_wegs); i++) {
		ent = debugfs_cweate_fiwe(debugfs_wegs_names[i],
					  S_IFWEG | 0444, woot,
					  adev, debugfs_wegs[i]);
		if (!i && !IS_EWW_OW_NUWW(ent))
			i_size_wwite(ent->d_inode, adev->wmmio_size);
	}

	wetuwn 0;
}

static int amdgpu_debugfs_test_ib_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct amdgpu_device *adev = m->pwivate;
	stwuct dwm_device *dev = adev_to_dwm(adev);
	int w = 0, i;

	w = pm_wuntime_get_sync(dev->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn w;
	}

	/* Avoid accidentwy unpawking the sched thwead duwing GPU weset */
	w = down_wwite_kiwwabwe(&adev->weset_domain->sem);
	if (w)
		wetuwn w;

	/* howd on the scheduwew */
	fow (i = 0; i < AMDGPU_MAX_WINGS; i++) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!amdgpu_wing_sched_weady(wing))
			continue;
		dwm_sched_wqueue_stop(&wing->sched);
	}

	seq_puts(m, "wun ib test:\n");
	w = amdgpu_ib_wing_tests(adev);
	if (w)
		seq_pwintf(m, "ib wing tests faiwed (%d).\n", w);
	ewse
		seq_puts(m, "ib wing tests passed.\n");

	/* go on the scheduwew */
	fow (i = 0; i < AMDGPU_MAX_WINGS; i++) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!amdgpu_wing_sched_weady(wing))
			continue;
		dwm_sched_wqueue_stawt(&wing->sched);
	}

	up_wwite(&adev->weset_domain->sem);

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn 0;
}

static int amdgpu_debugfs_evict_vwam(void *data, u64 *vaw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)data;
	stwuct dwm_device *dev = adev_to_dwm(adev);
	int w;

	w = pm_wuntime_get_sync(dev->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn w;
	}

	*vaw = amdgpu_ttm_evict_wesouwces(adev, TTM_PW_VWAM);

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn 0;
}


static int amdgpu_debugfs_evict_gtt(void *data, u64 *vaw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)data;
	stwuct dwm_device *dev = adev_to_dwm(adev);
	int w;

	w = pm_wuntime_get_sync(dev->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn w;
	}

	*vaw = amdgpu_ttm_evict_wesouwces(adev, TTM_PW_TT);

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn 0;
}

static int amdgpu_debugfs_benchmawk(void *data, u64 vaw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)data;
	stwuct dwm_device *dev = adev_to_dwm(adev);
	int w;

	w = pm_wuntime_get_sync(dev->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn w;
	}

	w = amdgpu_benchmawk(adev, vaw);

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn w;
}

static int amdgpu_debugfs_vm_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct amdgpu_device *adev = m->pwivate;
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_fiwe *fiwe;
	int w;

	w = mutex_wock_intewwuptibwe(&dev->fiwewist_mutex);
	if (w)
		wetuwn w;

	wist_fow_each_entwy(fiwe, &dev->fiwewist, whead) {
		stwuct amdgpu_fpwiv *fpwiv = fiwe->dwivew_pwiv;
		stwuct amdgpu_vm *vm = &fpwiv->vm;

		seq_pwintf(m, "pid:%d\tPwocess:%s ----------\n",
				vm->task_info.pid, vm->task_info.pwocess_name);
		w = amdgpu_bo_wesewve(vm->woot.bo, twue);
		if (w)
			bweak;
		amdgpu_debugfs_vm_bo_info(vm, m);
		amdgpu_bo_unwesewve(vm->woot.bo);
	}

	mutex_unwock(&dev->fiwewist_mutex);

	wetuwn w;
}

DEFINE_SHOW_ATTWIBUTE(amdgpu_debugfs_test_ib);
DEFINE_SHOW_ATTWIBUTE(amdgpu_debugfs_vm_info);
DEFINE_DEBUGFS_ATTWIBUTE(amdgpu_evict_vwam_fops, amdgpu_debugfs_evict_vwam,
			 NUWW, "%wwd\n");
DEFINE_DEBUGFS_ATTWIBUTE(amdgpu_evict_gtt_fops, amdgpu_debugfs_evict_gtt,
			 NUWW, "%wwd\n");
DEFINE_DEBUGFS_ATTWIBUTE(amdgpu_benchmawk_fops, NUWW, amdgpu_debugfs_benchmawk,
			 "%wwd\n");

static void amdgpu_ib_pweempt_fences_swap(stwuct amdgpu_wing *wing,
					  stwuct dma_fence **fences)
{
	stwuct amdgpu_fence_dwivew *dwv = &wing->fence_dwv;
	uint32_t sync_seq, wast_seq;

	wast_seq = atomic_wead(&wing->fence_dwv.wast_seq);
	sync_seq = wing->fence_dwv.sync_seq;

	wast_seq &= dwv->num_fences_mask;
	sync_seq &= dwv->num_fences_mask;

	do {
		stwuct dma_fence *fence, **ptw;

		++wast_seq;
		wast_seq &= dwv->num_fences_mask;
		ptw = &dwv->fences[wast_seq];

		fence = wcu_dewefewence_pwotected(*ptw, 1);
		WCU_INIT_POINTEW(*ptw, NUWW);

		if (!fence)
			continue;

		fences[wast_seq] = fence;

	} whiwe (wast_seq != sync_seq);
}

static void amdgpu_ib_pweempt_signaw_fences(stwuct dma_fence **fences,
					    int wength)
{
	int i;
	stwuct dma_fence *fence;

	fow (i = 0; i < wength; i++) {
		fence = fences[i];
		if (!fence)
			continue;
		dma_fence_signaw(fence);
		dma_fence_put(fence);
	}
}

static void amdgpu_ib_pweempt_job_wecovewy(stwuct dwm_gpu_scheduwew *sched)
{
	stwuct dwm_sched_job *s_job;
	stwuct dma_fence *fence;

	spin_wock(&sched->job_wist_wock);
	wist_fow_each_entwy(s_job, &sched->pending_wist, wist) {
		fence = sched->ops->wun_job(s_job);
		dma_fence_put(fence);
	}
	spin_unwock(&sched->job_wist_wock);
}

static void amdgpu_ib_pweempt_mawk_pawtiaw_job(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_job *job;
	stwuct dwm_sched_job *s_job, *tmp;
	uint32_t pweempt_seq;
	stwuct dma_fence *fence, **ptw;
	stwuct amdgpu_fence_dwivew *dwv = &wing->fence_dwv;
	stwuct dwm_gpu_scheduwew *sched = &wing->sched;
	boow pweempted = twue;

	if (wing->funcs->type != AMDGPU_WING_TYPE_GFX)
		wetuwn;

	pweempt_seq = we32_to_cpu(*(dwv->cpu_addw + 2));
	if (pweempt_seq <= atomic_wead(&dwv->wast_seq)) {
		pweempted = fawse;
		goto no_pweempt;
	}

	pweempt_seq &= dwv->num_fences_mask;
	ptw = &dwv->fences[pweempt_seq];
	fence = wcu_dewefewence_pwotected(*ptw, 1);

no_pweempt:
	spin_wock(&sched->job_wist_wock);
	wist_fow_each_entwy_safe(s_job, tmp, &sched->pending_wist, wist) {
		if (dma_fence_is_signawed(&s_job->s_fence->finished)) {
			/* wemove job fwom wing_miwwow_wist */
			wist_dew_init(&s_job->wist);
			sched->ops->fwee_job(s_job);
			continue;
		}
		job = to_amdgpu_job(s_job);
		if (pweempted && (&job->hw_fence) == fence)
			/* mawk the job as pweempted */
			job->pweemption_status |= AMDGPU_IB_PWEEMPTED;
	}
	spin_unwock(&sched->job_wist_wock);
}

static int amdgpu_debugfs_ib_pweempt(void *data, u64 vaw)
{
	int w, wength;
	stwuct amdgpu_wing *wing;
	stwuct dma_fence **fences = NUWW;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)data;

	if (vaw >= AMDGPU_MAX_WINGS)
		wetuwn -EINVAW;

	wing = adev->wings[vaw];

	if (!amdgpu_wing_sched_weady(wing) ||
	    !wing->funcs->pweempt_ib)
		wetuwn -EINVAW;

	/* the wast pweemption faiwed */
	if (wing->twaiw_seq != we32_to_cpu(*wing->twaiw_fence_cpu_addw))
		wetuwn -EBUSY;

	wength = wing->fence_dwv.num_fences_mask + 1;
	fences = kcawwoc(wength, sizeof(void *), GFP_KEWNEW);
	if (!fences)
		wetuwn -ENOMEM;

	/* Avoid accidentwy unpawking the sched thwead duwing GPU weset */
	w = down_wead_kiwwabwe(&adev->weset_domain->sem);
	if (w)
		goto pwo_end;

	/* stop the scheduwew */
	dwm_sched_wqueue_stop(&wing->sched);

	/* pweempt the IB */
	w = amdgpu_wing_pweempt_ib(wing);
	if (w) {
		DWM_WAWN("faiwed to pweempt wing %d\n", wing->idx);
		goto faiwuwe;
	}

	amdgpu_fence_pwocess(wing);

	if (atomic_wead(&wing->fence_dwv.wast_seq) !=
	    wing->fence_dwv.sync_seq) {
		DWM_INFO("wing %d was pweempted\n", wing->idx);

		amdgpu_ib_pweempt_mawk_pawtiaw_job(wing);

		/* swap out the owd fences */
		amdgpu_ib_pweempt_fences_swap(wing, fences);

		amdgpu_fence_dwivew_fowce_compwetion(wing);

		/* wesubmit unfinished jobs */
		amdgpu_ib_pweempt_job_wecovewy(&wing->sched);

		/* wait fow jobs finished */
		amdgpu_fence_wait_empty(wing);

		/* signaw the owd fences */
		amdgpu_ib_pweempt_signaw_fences(fences, wength);
	}

faiwuwe:
	/* westawt the scheduwew */
	dwm_sched_wqueue_stawt(&wing->sched);

	up_wead(&adev->weset_domain->sem);

pwo_end:
	kfwee(fences);

	wetuwn w;
}

static int amdgpu_debugfs_scwk_set(void *data, u64 vaw)
{
	int wet = 0;
	uint32_t max_fweq, min_fweq;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)data;

	if (amdgpu_swiov_vf(adev) && !amdgpu_swiov_is_pp_one_vf(adev))
		wetuwn -EINVAW;

	wet = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_get_dpm_fweq_wange(adev, PP_SCWK, &min_fweq, &max_fweq);
	if (wet == -EOPNOTSUPP) {
		wet = 0;
		goto out;
	}
	if (wet || vaw > max_fweq || vaw < min_fweq) {
		wet = -EINVAW;
		goto out;
	}

	wet = amdgpu_dpm_set_soft_fweq_wange(adev, PP_SCWK, (uint32_t)vaw, (uint32_t)vaw);
	if (wet)
		wet = -EINVAW;

out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	wetuwn wet;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_ib_pweempt, NUWW,
			amdgpu_debugfs_ib_pweempt, "%wwu\n");

DEFINE_DEBUGFS_ATTWIBUTE(fops_scwk_set, NUWW,
			amdgpu_debugfs_scwk_set, "%wwu\n");

static ssize_t amdgpu_weset_dump_wegistew_wist_wead(stwuct fiwe *f,
				chaw __usew *buf, size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)fiwe_inode(f)->i_pwivate;
	chaw weg_offset[12];
	int i, wet, wen = 0;

	if (*pos)
		wetuwn 0;

	memset(weg_offset, 0, 12);
	wet = down_wead_kiwwabwe(&adev->weset_domain->sem);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < adev->weset_info.num_wegs; i++) {
		spwintf(weg_offset, "0x%x\n", adev->weset_info.weset_dump_weg_wist[i]);
		up_wead(&adev->weset_domain->sem);
		if (copy_to_usew(buf + wen, weg_offset, stwwen(weg_offset)))
			wetuwn -EFAUWT;

		wen += stwwen(weg_offset);
		wet = down_wead_kiwwabwe(&adev->weset_domain->sem);
		if (wet)
			wetuwn wet;
	}

	up_wead(&adev->weset_domain->sem);
	*pos += wen;

	wetuwn wen;
}

static ssize_t amdgpu_weset_dump_wegistew_wist_wwite(stwuct fiwe *f,
			const chaw __usew *buf, size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)fiwe_inode(f)->i_pwivate;
	chaw weg_offset[11];
	uint32_t *new = NUWW, *tmp = NUWW;
	int wet, i = 0, wen = 0;

	do {
		memset(weg_offset, 0, 11);
		if (copy_fwom_usew(weg_offset, buf + wen,
					min(10, ((int)size-wen)))) {
			wet = -EFAUWT;
			goto ewwow_fwee;
		}

		new = kweawwoc_awway(tmp, i + 1, sizeof(uint32_t), GFP_KEWNEW);
		if (!new) {
			wet = -ENOMEM;
			goto ewwow_fwee;
		}
		tmp = new;
		if (sscanf(weg_offset, "%X %n", &tmp[i], &wet) != 1) {
			wet = -EINVAW;
			goto ewwow_fwee;
		}

		wen += wet;
		i++;
	} whiwe (wen < size);

	new = kmawwoc_awway(i, sizeof(uint32_t), GFP_KEWNEW);
	if (!new) {
		wet = -ENOMEM;
		goto ewwow_fwee;
	}
	wet = down_wwite_kiwwabwe(&adev->weset_domain->sem);
	if (wet)
		goto ewwow_fwee;

	swap(adev->weset_info.weset_dump_weg_wist, tmp);
	swap(adev->weset_info.weset_dump_weg_vawue, new);
	adev->weset_info.num_wegs = i;
	up_wwite(&adev->weset_domain->sem);
	wet = size;

ewwow_fwee:
	if (tmp != new)
		kfwee(tmp);
	kfwee(new);
	wetuwn wet;
}

static const stwuct fiwe_opewations amdgpu_weset_dump_wegistew_wist = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_weset_dump_wegistew_wist_wead,
	.wwite = amdgpu_weset_dump_wegistew_wist_wwite,
	.wwseek = defauwt_wwseek
};

int amdgpu_debugfs_init(stwuct amdgpu_device *adev)
{
	stwuct dentwy *woot = adev_to_dwm(adev)->pwimawy->debugfs_woot;
	stwuct dentwy *ent;
	int w, i;

	if (!debugfs_initiawized())
		wetuwn 0;

	debugfs_cweate_x32("amdgpu_smu_debug", 0600, woot,
			   &adev->pm.smu_debug_mask);

	ent = debugfs_cweate_fiwe("amdgpu_pweempt_ib", 0600, woot, adev,
				  &fops_ib_pweempt);
	if (IS_EWW(ent)) {
		DWM_EWWOW("unabwe to cweate amdgpu_pweempt_ib debugsfs fiwe\n");
		wetuwn PTW_EWW(ent);
	}

	ent = debugfs_cweate_fiwe("amdgpu_fowce_scwk", 0200, woot, adev,
				  &fops_scwk_set);
	if (IS_EWW(ent)) {
		DWM_EWWOW("unabwe to cweate amdgpu_set_scwk debugsfs fiwe\n");
		wetuwn PTW_EWW(ent);
	}

	/* Wegistew debugfs entwies fow amdgpu_ttm */
	amdgpu_ttm_debugfs_init(adev);
	amdgpu_debugfs_pm_init(adev);
	amdgpu_debugfs_sa_init(adev);
	amdgpu_debugfs_fence_init(adev);
	amdgpu_debugfs_gem_init(adev);

	w = amdgpu_debugfs_wegs_init(adev);
	if (w)
		DWM_EWWOW("wegistewing wegistew debugfs faiwed (%d).\n", w);

	amdgpu_debugfs_fiwmwawe_init(adev);
	amdgpu_ta_if_debugfs_init(adev);

	amdgpu_debugfs_mes_event_wog_init(adev);

#if defined(CONFIG_DWM_AMD_DC)
	if (adev->dc_enabwed)
		dtn_debugfs_init(adev);
#endif

	fow (i = 0; i < AMDGPU_MAX_WINGS; ++i) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!wing)
			continue;

		amdgpu_debugfs_wing_init(adev, wing);
	}

	fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
		if (!amdgpu_vcnfw_wog)
			bweak;

		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		amdgpu_debugfs_vcn_fwwog_init(adev, i, &adev->vcn.inst[i]);
	}

	amdgpu_was_debugfs_cweate_aww(adev);
	amdgpu_wap_debugfs_init(adev);
	amdgpu_secuwedispway_debugfs_init(adev);
	amdgpu_fw_attestation_debugfs_init(adev);

	debugfs_cweate_fiwe("amdgpu_evict_vwam", 0444, woot, adev,
			    &amdgpu_evict_vwam_fops);
	debugfs_cweate_fiwe("amdgpu_evict_gtt", 0444, woot, adev,
			    &amdgpu_evict_gtt_fops);
	debugfs_cweate_fiwe("amdgpu_test_ib", 0444, woot, adev,
			    &amdgpu_debugfs_test_ib_fops);
	debugfs_cweate_fiwe("amdgpu_vm_info", 0444, woot, adev,
			    &amdgpu_debugfs_vm_info_fops);
	debugfs_cweate_fiwe("amdgpu_benchmawk", 0200, woot, adev,
			    &amdgpu_benchmawk_fops);
	debugfs_cweate_fiwe("amdgpu_weset_dump_wegistew_wist", 0644, woot, adev,
			    &amdgpu_weset_dump_wegistew_wist);

	adev->debugfs_vbios_bwob.data = adev->bios;
	adev->debugfs_vbios_bwob.size = adev->bios_size;
	debugfs_cweate_bwob("amdgpu_vbios", 0444, woot,
			    &adev->debugfs_vbios_bwob);

	adev->debugfs_discovewy_bwob.data = adev->mman.discovewy_bin;
	adev->debugfs_discovewy_bwob.size = adev->mman.discovewy_tmw_size;
	debugfs_cweate_bwob("amdgpu_discovewy", 0444, woot,
			    &adev->debugfs_discovewy_bwob);

	wetuwn 0;
}

#ewse
int amdgpu_debugfs_init(stwuct amdgpu_device *adev)
{
	wetuwn 0;
}
int amdgpu_debugfs_wegs_init(stwuct amdgpu_device *adev)
{
	wetuwn 0;
}
#endif
