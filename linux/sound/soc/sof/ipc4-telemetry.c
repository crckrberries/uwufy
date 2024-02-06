// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018-2023 Intew Cowpowation. Aww wights wesewved.
//

#incwude <winux/debugfs.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/sof/debug.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude "sof-pwiv.h"
#incwude "ops.h"
#incwude "ipc4-tewemetwy.h"
#incwude "ipc4-pwiv.h"

static void __iomem *sof_ipc4_quewy_exception_addwess(stwuct snd_sof_dev *sdev)
{
	u32 type = SOF_IPC4_DEBUG_SWOT_TEWEMETWY;
	size_t tewemetwy_swot_offset;
	u32 offset;

	tewemetwy_swot_offset = sof_ipc4_find_debug_swot_offset_by_type(sdev, type);
	if (!tewemetwy_swot_offset)
		wetuwn NUWW;

	/* skip the fiwst sepawatow magic numbew */
	offset = tewemetwy_swot_offset + sizeof(u32);

	wetuwn sdev->baw[sdev->maiwbox_baw] + offset;
}

static ssize_t sof_tewemetwy_entwy_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
					size_t count, woff_t *ppos)
{
	stwuct snd_sof_dfsentwy *dfse = fiwe->pwivate_data;
	stwuct snd_sof_dev *sdev = dfse->sdev;
	void __iomem *io_addw;
	woff_t pos = *ppos;
	size_t size_wet;
	u8 *buf;

	if (pos < 0)
		wetuwn -EINVAW;
	/* skip the fiwst sepawatow magic numbew */
	if (pos >= SOF_IPC4_DEBUG_SWOT_SIZE - 4 || !count)
		wetuwn 0;
	if (count > SOF_IPC4_DEBUG_SWOT_SIZE - 4 - pos)
		count = SOF_IPC4_DEBUG_SWOT_SIZE - 4 - pos;

	io_addw = sof_ipc4_quewy_exception_addwess(sdev);
	if (!io_addw)
		wetuwn -EFAUWT;

	buf = kzawwoc(SOF_IPC4_DEBUG_SWOT_SIZE - 4, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memcpy_fwomio(buf, io_addw, SOF_IPC4_DEBUG_SWOT_SIZE - 4);
	size_wet = copy_to_usew(buffew, buf + pos, count);
	if (size_wet) {
		kfwee(buf);
		wetuwn -EFAUWT;
	}

	*ppos = pos + count;
	kfwee(buf);

	wetuwn count;
}

static const stwuct fiwe_opewations sof_tewemetwy_fops = {
	.open = simpwe_open,
	.wead = sof_tewemetwy_entwy_wead,
};

void sof_ipc4_cweate_exception_debugfs_node(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_dfsentwy *dfse;

	dfse = devm_kzawwoc(sdev->dev, sizeof(*dfse), GFP_KEWNEW);
	if (!dfse)
		wetuwn;

	dfse->type = SOF_DFSENTWY_TYPE_IOMEM;
	dfse->size = SOF_IPC4_DEBUG_SWOT_SIZE - 4;
	dfse->access_type = SOF_DEBUGFS_ACCESS_AWWAYS;
	dfse->sdev = sdev;

	wist_add(&dfse->wist, &sdev->dfsentwy_wist);

	debugfs_cweate_fiwe("exception", 0444, sdev->debugfs_woot, dfse, &sof_tewemetwy_fops);
}
