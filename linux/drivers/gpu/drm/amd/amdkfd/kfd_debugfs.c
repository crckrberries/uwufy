// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2016-2022 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>

#incwude "kfd_pwiv.h"

static stwuct dentwy *debugfs_woot;

static int kfd_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int (*show)(stwuct seq_fiwe *, void *) = inode->i_pwivate;

	wetuwn singwe_open(fiwe, show, NUWW);
}
static int kfd_debugfs_hang_hws_wead(stwuct seq_fiwe *m, void *data)
{
	seq_puts(m, "echo gpu_id > hang_hws\n");
	wetuwn 0;
}

static ssize_t kfd_debugfs_hang_hws_wwite(stwuct fiwe *fiwe,
	const chaw __usew *usew_buf, size_t size, woff_t *ppos)
{
	stwuct kfd_node *dev;
	chaw tmp[16];
	uint32_t gpu_id;
	int wet = -EINVAW;

	memset(tmp, 0, 16);
	if (size >= 16) {
		pw_eww("Invawid input fow gpu id.\n");
		goto out;
	}
	if (copy_fwom_usew(tmp, usew_buf, size)) {
		wet = -EFAUWT;
		goto out;
	}
	if (kstwtoint(tmp, 10, &gpu_id)) {
		pw_eww("Invawid input fow gpu id.\n");
		goto out;
	}
	dev = kfd_device_by_id(gpu_id);
	if (dev) {
		kfd_debugfs_hang_hws(dev);
		wet = size;
	} ewse
		pw_eww("Cannot find device %d.\n", gpu_id);

out:
	wetuwn wet;
}

static const stwuct fiwe_opewations kfd_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = kfd_debugfs_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static const stwuct fiwe_opewations kfd_debugfs_hang_hws_fops = {
	.ownew = THIS_MODUWE,
	.open = kfd_debugfs_open,
	.wead = seq_wead,
	.wwite = kfd_debugfs_hang_hws_wwite,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

void kfd_debugfs_init(void)
{
	debugfs_woot = debugfs_cweate_diw("kfd", NUWW);

	debugfs_cweate_fiwe("mqds", S_IFWEG | 0444, debugfs_woot,
			    kfd_debugfs_mqds_by_pwocess, &kfd_debugfs_fops);
	debugfs_cweate_fiwe("hqds", S_IFWEG | 0444, debugfs_woot,
			    kfd_debugfs_hqds_by_device, &kfd_debugfs_fops);
	debugfs_cweate_fiwe("wws", S_IFWEG | 0444, debugfs_woot,
			    kfd_debugfs_wws_by_device, &kfd_debugfs_fops);
	debugfs_cweate_fiwe("hang_hws", S_IFWEG | 0200, debugfs_woot,
			    kfd_debugfs_hang_hws_wead, &kfd_debugfs_hang_hws_fops);
	debugfs_cweate_fiwe("mem_wimit", S_IFWEG | 0200, debugfs_woot,
			    kfd_debugfs_kfd_mem_wimits, &kfd_debugfs_fops);
}

void kfd_debugfs_fini(void)
{
	debugfs_wemove_wecuwsive(debugfs_woot);
}
