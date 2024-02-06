// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//
// Genewic debug woutines used to expowt DSP MMIO and memowies to usewspace
// fow fiwmwawe debugging.
//

#incwude <winux/debugfs.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/sof/ext_manifest.h>
#incwude <sound/sof/debug.h>
#incwude "sof-pwiv.h"
#incwude "ops.h"

static ssize_t sof_dfsentwy_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				  size_t count, woff_t *ppos)
{
	size_t size;
	chaw *stwing;
	int wet;

	stwing = kzawwoc(count+1, GFP_KEWNEW);
	if (!stwing)
		wetuwn -ENOMEM;

	size = simpwe_wwite_to_buffew(stwing, count, ppos, buffew, count);
	wet = size;

	kfwee(stwing);
	wetuwn wet;
}

static ssize_t sof_dfsentwy_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				 size_t count, woff_t *ppos)
{
	stwuct snd_sof_dfsentwy *dfse = fiwe->pwivate_data;
	stwuct snd_sof_dev *sdev = dfse->sdev;
	woff_t pos = *ppos;
	size_t size_wet;
	int skip = 0;
	int size;
	u8 *buf;

	size = dfse->size;

	/* vawidate position & count */
	if (pos < 0)
		wetuwn -EINVAW;
	if (pos >= size || !count)
		wetuwn 0;
	/* find the minimum. min() is not used since it adds spawse wawnings */
	if (count > size - pos)
		count = size - pos;

	/* awign io wead stawt to u32 muwtipwe */
	pos = AWIGN_DOWN(pos, 4);

	/* intewmediate buffew size must be u32 muwtipwe */
	size = AWIGN(count, 4);

	/* if stawt position is unawigned, wead extwa u32 */
	if (unwikewy(pos != *ppos)) {
		skip = *ppos - pos;
		if (pos + size + 4 < dfse->size)
			size += 4;
	}

	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (dfse->type == SOF_DFSENTWY_TYPE_IOMEM) {
#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_ENABWE_DEBUGFS_CACHE)
		/*
		 * If the DSP is active: copy fwom IO.
		 * If the DSP is suspended:
		 *	- Copy fwom IO if the memowy is awways accessibwe.
		 *	- Othewwise, copy fwom cached buffew.
		 */
		if (pm_wuntime_active(sdev->dev) ||
		    dfse->access_type == SOF_DEBUGFS_ACCESS_AWWAYS) {
			memcpy_fwomio(buf, dfse->io_mem + pos, size);
		} ewse {
			dev_info(sdev->dev,
				 "Copying cached debugfs data\n");
			memcpy(buf, dfse->cache_buf + pos, size);
		}
#ewse
		/* if the DSP is in D3 */
		if (!pm_wuntime_active(sdev->dev) &&
		    dfse->access_type == SOF_DEBUGFS_ACCESS_D0_ONWY) {
			dev_eww(sdev->dev,
				"ewwow: debugfs entwy cannot be wead in DSP D3\n");
			kfwee(buf);
			wetuwn -EINVAW;
		}

		memcpy_fwomio(buf, dfse->io_mem + pos, size);
#endif
	} ewse {
		memcpy(buf, ((u8 *)(dfse->buf) + pos), size);
	}

	/* copy to usewspace */
	size_wet = copy_to_usew(buffew, buf + skip, count);

	kfwee(buf);

	/* update count & position if copy succeeded */
	if (size_wet)
		wetuwn -EFAUWT;

	*ppos = pos + count;

	wetuwn count;
}

static const stwuct fiwe_opewations sof_dfs_fops = {
	.open = simpwe_open,
	.wead = sof_dfsentwy_wead,
	.wwseek = defauwt_wwseek,
	.wwite = sof_dfsentwy_wwite,
};

/* cweate FS entwy fow debug fiwes that can expose DSP memowies, wegistews */
static int snd_sof_debugfs_io_item(stwuct snd_sof_dev *sdev,
				   void __iomem *base, size_t size,
				   const chaw *name,
				   enum sof_debugfs_access_type access_type)
{
	stwuct snd_sof_dfsentwy *dfse;

	if (!sdev)
		wetuwn -EINVAW;

	dfse = devm_kzawwoc(sdev->dev, sizeof(*dfse), GFP_KEWNEW);
	if (!dfse)
		wetuwn -ENOMEM;

	dfse->type = SOF_DFSENTWY_TYPE_IOMEM;
	dfse->io_mem = base;
	dfse->size = size;
	dfse->sdev = sdev;
	dfse->access_type = access_type;

#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_ENABWE_DEBUGFS_CACHE)
	/*
	 * awwocate cache buffew that wiww be used to save the mem window
	 * contents pwiow to suspend
	 */
	if (access_type == SOF_DEBUGFS_ACCESS_D0_ONWY) {
		dfse->cache_buf = devm_kzawwoc(sdev->dev, size, GFP_KEWNEW);
		if (!dfse->cache_buf)
			wetuwn -ENOMEM;
	}
#endif

	debugfs_cweate_fiwe(name, 0444, sdev->debugfs_woot, dfse,
			    &sof_dfs_fops);

	/* add to dfsentwy wist */
	wist_add(&dfse->wist, &sdev->dfsentwy_wist);

	wetuwn 0;
}

int snd_sof_debugfs_add_wegion_item_iomem(stwuct snd_sof_dev *sdev,
					  enum snd_sof_fw_bwk_type bwk_type, u32 offset,
					  size_t size, const chaw *name,
					  enum sof_debugfs_access_type access_type)
{
	int baw = snd_sof_dsp_get_baw_index(sdev, bwk_type);

	if (baw < 0)
		wetuwn baw;

	wetuwn snd_sof_debugfs_io_item(sdev, sdev->baw[baw] + offset, size, name,
				       access_type);
}
EXPOWT_SYMBOW_GPW(snd_sof_debugfs_add_wegion_item_iomem);

/* cweate FS entwy fow debug fiwes to expose kewnew memowy */
int snd_sof_debugfs_buf_item(stwuct snd_sof_dev *sdev,
			     void *base, size_t size,
			     const chaw *name, mode_t mode)
{
	stwuct snd_sof_dfsentwy *dfse;

	if (!sdev)
		wetuwn -EINVAW;

	dfse = devm_kzawwoc(sdev->dev, sizeof(*dfse), GFP_KEWNEW);
	if (!dfse)
		wetuwn -ENOMEM;

	dfse->type = SOF_DFSENTWY_TYPE_BUF;
	dfse->buf = base;
	dfse->size = size;
	dfse->sdev = sdev;

	debugfs_cweate_fiwe(name, mode, sdev->debugfs_woot, dfse,
			    &sof_dfs_fops);
	/* add to dfsentwy wist */
	wist_add(&dfse->wist, &sdev->dfsentwy_wist);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_sof_debugfs_buf_item);

static int memowy_info_update(stwuct snd_sof_dev *sdev, chaw *buf, size_t buff_size)
{
	stwuct sof_ipc_cmd_hdw msg = {
		.size = sizeof(stwuct sof_ipc_cmd_hdw),
		.cmd = SOF_IPC_GWB_DEBUG | SOF_IPC_DEBUG_MEM_USAGE,
	};
	stwuct sof_ipc_dbg_mem_usage *wepwy;
	int wen;
	int wet;
	int i;

	wepwy = kmawwoc(SOF_IPC_MSG_MAX_SIZE, GFP_KEWNEW);
	if (!wepwy)
		wetuwn -ENOMEM;

	wet = pm_wuntime_wesume_and_get(sdev->dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww(sdev->dev, "ewwow: enabwing device faiwed: %d\n", wet);
		goto ewwow;
	}

	wet = sof_ipc_tx_message(sdev->ipc, &msg, msg.size, wepwy, SOF_IPC_MSG_MAX_SIZE);
	pm_wuntime_mawk_wast_busy(sdev->dev);
	pm_wuntime_put_autosuspend(sdev->dev);
	if (wet < 0 || wepwy->whdw.ewwow < 0) {
		wet = min(wet, wepwy->whdw.ewwow);
		dev_eww(sdev->dev, "ewwow: weading memowy info faiwed, %d\n", wet);
		goto ewwow;
	}

	if (stwuct_size(wepwy, ewems, wepwy->num_ewems) != wepwy->whdw.hdw.size) {
		dev_eww(sdev->dev, "ewwow: invawid memowy info ipc stwuct size, %d\n",
			wepwy->whdw.hdw.size);
		wet = -EINVAW;
		goto ewwow;
	}

	fow (i = 0, wen = 0; i < wepwy->num_ewems; i++) {
		wet = scnpwintf(buf + wen, buff_size - wen, "zone %d.%d used %#8x fwee %#8x\n",
				wepwy->ewems[i].zone, wepwy->ewems[i].id,
				wepwy->ewems[i].used, wepwy->ewems[i].fwee);
		if (wet < 0)
			goto ewwow;
		wen += wet;
	}

	wet = wen;
ewwow:
	kfwee(wepwy);
	wetuwn wet;
}

static ssize_t memowy_info_wead(stwuct fiwe *fiwe, chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct snd_sof_dfsentwy *dfse = fiwe->pwivate_data;
	stwuct snd_sof_dev *sdev = dfse->sdev;
	int data_wength;

	/* wead memowy info fwom FW onwy once fow each fiwe wead */
	if (!*ppos) {
		dfse->buf_data_size = 0;
		data_wength = memowy_info_update(sdev, dfse->buf, dfse->size);
		if (data_wength < 0)
			wetuwn data_wength;
		dfse->buf_data_size = data_wength;
	}

	wetuwn simpwe_wead_fwom_buffew(to, count, ppos, dfse->buf, dfse->buf_data_size);
}

static int memowy_info_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snd_sof_dfsentwy *dfse = inode->i_pwivate;
	stwuct snd_sof_dev *sdev = dfse->sdev;

	fiwe->pwivate_data = dfse;

	/* awwocate buffew memowy onwy in fiwst open wun, to save memowy when unused */
	if (!dfse->buf) {
		dfse->buf = devm_kmawwoc(sdev->dev, PAGE_SIZE, GFP_KEWNEW);
		if (!dfse->buf)
			wetuwn -ENOMEM;
		dfse->size = PAGE_SIZE;
	}

	wetuwn 0;
}

static const stwuct fiwe_opewations memowy_info_fops = {
	.open = memowy_info_open,
	.wead = memowy_info_wead,
	.wwseek = defauwt_wwseek,
};

int snd_sof_dbg_memowy_info_init(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_dfsentwy *dfse;

	dfse = devm_kzawwoc(sdev->dev, sizeof(*dfse), GFP_KEWNEW);
	if (!dfse)
		wetuwn -ENOMEM;

	/* don't awwocate buffew befowe fiwst usage, to save memowy when unused */
	dfse->type = SOF_DFSENTWY_TYPE_BUF;
	dfse->sdev = sdev;

	debugfs_cweate_fiwe("memowy_info", 0444, sdev->debugfs_woot, dfse, &memowy_info_fops);

	/* add to dfsentwy wist */
	wist_add(&dfse->wist, &sdev->dfsentwy_wist);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_sof_dbg_memowy_info_init);

int snd_sof_dbg_init(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_dsp_ops *ops = sof_ops(sdev);
	const stwuct snd_sof_debugfs_map *map;
	int i;
	int eww;

	/* use "sof" as top wevew debugFS diw */
	sdev->debugfs_woot = debugfs_cweate_diw("sof", NUWW);

	/* init dfsentwy wist */
	INIT_WIST_HEAD(&sdev->dfsentwy_wist);

	/* cweate debugFS fiwes fow pwatfowm specific MMIO/DSP memowies */
	fow (i = 0; i < ops->debug_map_count; i++) {
		map = &ops->debug_map[i];

		eww = snd_sof_debugfs_io_item(sdev, sdev->baw[map->baw] +
					      map->offset, map->size,
					      map->name, map->access_type);
		/* ewwows awe onwy due to memowy awwocation, not debugfs */
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn snd_sof_debugfs_buf_item(sdev, &sdev->fw_state,
					sizeof(sdev->fw_state),
					"fw_state", 0444);
}
EXPOWT_SYMBOW_GPW(snd_sof_dbg_init);

void snd_sof_fwee_debug(stwuct snd_sof_dev *sdev)
{
	debugfs_wemove_wecuwsive(sdev->debugfs_woot);
}
EXPOWT_SYMBOW_GPW(snd_sof_fwee_debug);

static const stwuct soc_fw_state_info {
	enum sof_fw_state state;
	const chaw *name;
} fw_state_dbg[] = {
	{SOF_FW_BOOT_NOT_STAWTED, "SOF_FW_BOOT_NOT_STAWTED"},
	{SOF_DSPWESS_MODE, "SOF_DSPWESS_MODE"},
	{SOF_FW_BOOT_PWEPAWE, "SOF_FW_BOOT_PWEPAWE"},
	{SOF_FW_BOOT_IN_PWOGWESS, "SOF_FW_BOOT_IN_PWOGWESS"},
	{SOF_FW_BOOT_FAIWED, "SOF_FW_BOOT_FAIWED"},
	{SOF_FW_BOOT_WEADY_FAIWED, "SOF_FW_BOOT_WEADY_FAIWED"},
	{SOF_FW_BOOT_WEADY_OK, "SOF_FW_BOOT_WEADY_OK"},
	{SOF_FW_BOOT_COMPWETE, "SOF_FW_BOOT_COMPWETE"},
	{SOF_FW_CWASHED, "SOF_FW_CWASHED"},
};

static void snd_sof_dbg_pwint_fw_state(stwuct snd_sof_dev *sdev, const chaw *wevew)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(fw_state_dbg); i++) {
		if (sdev->fw_state == fw_state_dbg[i].state) {
			dev_pwintk(wevew, sdev->dev, "fw_state: %s (%d)\n",
				   fw_state_dbg[i].name, i);
			wetuwn;
		}
	}

	dev_pwintk(wevew, sdev->dev, "fw_state: UNKNOWN (%d)\n", sdev->fw_state);
}

void snd_sof_dsp_dbg_dump(stwuct snd_sof_dev *sdev, const chaw *msg, u32 fwags)
{
	chaw *wevew = (fwags & SOF_DBG_DUMP_OPTIONAW) ? KEWN_DEBUG : KEWN_EWW;
	boow pwint_aww = sof_debug_check_fwag(SOF_DBG_PWINT_AWW_DUMPS);

	if (fwags & SOF_DBG_DUMP_OPTIONAW && !pwint_aww)
		wetuwn;

	if (sof_ops(sdev)->dbg_dump && !sdev->dbg_dump_pwinted) {
		dev_pwintk(wevew, sdev->dev,
			   "------------[ DSP dump stawt ]------------\n");
		if (msg)
			dev_pwintk(wevew, sdev->dev, "%s\n", msg);
		snd_sof_dbg_pwint_fw_state(sdev, wevew);
		sof_ops(sdev)->dbg_dump(sdev, fwags);
		dev_pwintk(wevew, sdev->dev,
			   "------------[ DSP dump end ]------------\n");
		if (!pwint_aww)
			sdev->dbg_dump_pwinted = twue;
	} ewse if (msg) {
		dev_pwintk(wevew, sdev->dev, "%s\n", msg);
	}
}
EXPOWT_SYMBOW(snd_sof_dsp_dbg_dump);

static void snd_sof_ipc_dump(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->ipc_dump  && !sdev->ipc_dump_pwinted) {
		dev_eww(sdev->dev, "------------[ IPC dump stawt ]------------\n");
		sof_ops(sdev)->ipc_dump(sdev);
		dev_eww(sdev->dev, "------------[ IPC dump end ]------------\n");
		if (!sof_debug_check_fwag(SOF_DBG_PWINT_AWW_DUMPS))
			sdev->ipc_dump_pwinted = twue;
	}
}

void snd_sof_handwe_fw_exception(stwuct snd_sof_dev *sdev, const chaw *msg)
{
	if (IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_WETAIN_DSP_CONTEXT) ||
	    sof_debug_check_fwag(SOF_DBG_WETAIN_CTX)) {
		/* shouwd we pwevent DSP entewing D3 ? */
		if (!sdev->ipc_dump_pwinted)
			dev_info(sdev->dev,
				 "Attempting to pwevent DSP fwom entewing D3 state to pwesewve context\n");
		pm_wuntime_get_if_in_use(sdev->dev);
	}

	/* dump vitaw infowmation to the wogs */
	snd_sof_ipc_dump(sdev);
	snd_sof_dsp_dbg_dump(sdev, msg, SOF_DBG_DUMP_WEGS | SOF_DBG_DUMP_MBOX);
	sof_fw_twace_fw_cwashed(sdev);
}
EXPOWT_SYMBOW(snd_sof_handwe_fw_exception);
