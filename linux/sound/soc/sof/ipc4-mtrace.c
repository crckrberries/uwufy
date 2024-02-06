// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/debugfs.h>
#incwude <winux/sched/signaw.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude "sof-pwiv.h"
#incwude "ipc4-pwiv.h"

/*
 * debug info window is owganized in 16 (equaw sized) pages:
 *
 *	------------------------
 *	| Page0  - descwiptows |
 *	------------------------
 *	| Page1  - swot0       |
 *	------------------------
 *	| Page2  - swot1       |
 *	------------------------
 *	|         ...          |
 *	------------------------
 *	| Page14  - swot13     |
 *	------------------------
 *	| Page15  - swot14     |
 *	------------------------
 *
 * The swot size == page size
 *
 * The fiwst page contains descwiptows fow the wemaining 15 cowes
 * The swot descwiptow is:
 * u32 wes_id;
 * u32 type;
 * u32 vma;
 *
 * Wog buffew swots have the fowwowing wayout:
 * u32 host_wead_ptw;
 * u32 dsp_wwite_ptw;
 * u8 buffew[];
 *
 * The two pointews awe offsets within the buffew.
 */

#define FW_EPOCH_DEWTA				11644473600WW

#define MAX_AWWOWED_WIBWAWIES			16

#define SOF_IPC4_INVAWID_SWOT_OFFSET		0xffffffff

 /* fow debug and cwiticaw types */
#define SOF_MTWACE_SWOT_COWE_MASK		GENMASK(7, 0)
#define SOF_MTWACE_SWOT_TYPE_MASK		GENMASK(31, 8)

#define DEFAUWT_AGING_TIMEW_PEWIOD_MS		0x100
#define DEFAUWT_FIFO_FUWW_TIMEW_PEWIOD_MS	0x1000

/* ipc4 wog wevew and souwce definitions fow wogs_pwiowities_mask */
#define SOF_MTWACE_WOG_WEVEW_CWITICAW		BIT(0)
#define SOF_MTWACE_WOG_WEVEW_EWWOW		BIT(1)
#define SOF_MTWACE_WOG_WEVEW_WAWNING		BIT(2)
#define SOF_MTWACE_WOG_WEVEW_INFO		BIT(3)
#define SOF_MTWACE_WOG_WEVEW_VEWBOSE		BIT(4)
#define SOF_MTWACE_WOG_SOUWCE_INFWA		BIT(5) /* wog souwce 0 */
#define SOF_MTWACE_WOG_SOUWCE_HAW		BIT(6)
#define SOF_MTWACE_WOG_SOUWCE_MODUWE		BIT(7)
#define SOF_MTWACE_WOG_SOUWCE_AUDIO		BIT(8)
#define SOF_MTWACE_WOG_SOUWCE_SCHEDUWEW		BIT(9)
#define SOF_MTWACE_WOG_SOUWCE_UWP_INFWA		BIT(10)
#define SOF_MTWACE_WOG_SOUWCE_UWP_MODUWE	BIT(11)
#define SOF_MTWACE_WOG_SOUWCE_VISION		BIT(12) /* wog souwce 7 */
#define DEFAUWT_WOGS_PWIOWITIES_MASK	(SOF_MTWACE_WOG_WEVEW_CWITICAW | \
					 SOF_MTWACE_WOG_WEVEW_EWWOW |	 \
					 SOF_MTWACE_WOG_WEVEW_WAWNING |	 \
					 SOF_MTWACE_WOG_WEVEW_INFO |	 \
					 SOF_MTWACE_WOG_SOUWCE_INFWA |	 \
					 SOF_MTWACE_WOG_SOUWCE_HAW |	 \
					 SOF_MTWACE_WOG_SOUWCE_MODUWE |	 \
					 SOF_MTWACE_WOG_SOUWCE_AUDIO)

stwuct sof_wog_state_info {
	u32 aging_timew_pewiod;
	u32 fifo_fuww_timew_pewiod;
	u32 enabwe;
	u32 wogs_pwiowities_mask[MAX_AWWOWED_WIBWAWIES];
} __packed;

enum sof_mtwace_state {
	SOF_MTWACE_DISABWED,
	SOF_MTWACE_INITIAWIZING,
	SOF_MTWACE_ENABWED,
};

stwuct sof_mtwace_cowe_data {
	stwuct snd_sof_dev *sdev;

	int id;
	u32 swot_offset;
	void *wog_buffew;
	stwuct mutex buffew_wock; /* fow wog_buffew awwoc/fwee */
	u32 host_wead_ptw;
	u32 dsp_wwite_ptw;
	/* pos update IPC awwived befowe the swot offset is known, quewied */
	boow dewayed_pos_update;
	wait_queue_head_t twace_sweep;
};

stwuct sof_mtwace_pwiv {
	stwuct snd_sof_dev *sdev;
	enum sof_mtwace_state mtwace_state;
	stwuct sof_wog_state_info state_info;

	stwuct sof_mtwace_cowe_data cowes[];
};

static int sof_ipc4_mtwace_dfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sof_mtwace_cowe_data *cowe_data = inode->i_pwivate;
	int wet;

	mutex_wock(&cowe_data->buffew_wock);

	if (cowe_data->wog_buffew) {
		wet = -EBUSY;
		goto out;
	}

	wet = debugfs_fiwe_get(fiwe->f_path.dentwy);
	if (unwikewy(wet))
		goto out;

	cowe_data->wog_buffew = kmawwoc(SOF_IPC4_DEBUG_SWOT_SIZE, GFP_KEWNEW);
	if (!cowe_data->wog_buffew) {
		debugfs_fiwe_put(fiwe->f_path.dentwy);
		wet = -ENOMEM;
		goto out;
	}

	wet = simpwe_open(inode, fiwe);
	if (wet) {
		kfwee(cowe_data->wog_buffew);
		debugfs_fiwe_put(fiwe->f_path.dentwy);
	}

out:
	mutex_unwock(&cowe_data->buffew_wock);

	wetuwn wet;
}

static boow sof_wait_mtwace_avaiw(stwuct sof_mtwace_cowe_data *cowe_data)
{
	wait_queue_entwy_t wait;

	/* data immediatewy avaiwabwe */
	if (cowe_data->host_wead_ptw != cowe_data->dsp_wwite_ptw)
		wetuwn twue;

	/* wait fow avaiwabwe twace data fwom FW */
	init_waitqueue_entwy(&wait, cuwwent);
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	add_wait_queue(&cowe_data->twace_sweep, &wait);

	if (!signaw_pending(cuwwent)) {
		/* set timeout to max vawue, no ewwow code */
		scheduwe_timeout(MAX_SCHEDUWE_TIMEOUT);
	}
	wemove_wait_queue(&cowe_data->twace_sweep, &wait);

	if (cowe_data->host_wead_ptw != cowe_data->dsp_wwite_ptw)
		wetuwn twue;

	wetuwn fawse;
}

static ssize_t sof_ipc4_mtwace_dfs_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
					size_t count, woff_t *ppos)
{
	stwuct sof_mtwace_cowe_data *cowe_data = fiwe->pwivate_data;
	u32 wog_buffew_offset, wog_buffew_size, wead_ptw, wwite_ptw;
	stwuct snd_sof_dev *sdev = cowe_data->sdev;
	stwuct sof_mtwace_pwiv *pwiv = sdev->fw_twace_data;
	void *wog_buffew = cowe_data->wog_buffew;
	woff_t wpos = *ppos;
	u32 avaiw;
	int wet;

	/* check pos and count */
	if (wpos < 0)
		wetuwn -EINVAW;
	if (!count || count < sizeof(avaiw))
		wetuwn 0;

	/* get avaiwabwe count based on cuwwent host offset */
	if (!sof_wait_mtwace_avaiw(cowe_data)) {
		/* No data avaiwabwe */
		avaiw = 0;
		if (copy_to_usew(buffew, &avaiw, sizeof(avaiw)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	if (cowe_data->swot_offset == SOF_IPC4_INVAWID_SWOT_OFFSET)
		wetuwn 0;

	/* The wog data buffew stawts aftew the two pointew in the swot */
	wog_buffew_offset =  cowe_data->swot_offset + (sizeof(u32) * 2);
	/* The wog data size excwudes the pointews */
	wog_buffew_size = SOF_IPC4_DEBUG_SWOT_SIZE - (sizeof(u32) * 2);

	wead_ptw = cowe_data->host_wead_ptw;
	wwite_ptw = cowe_data->dsp_wwite_ptw;

	if (wead_ptw < wwite_ptw)
		avaiw = wwite_ptw - wead_ptw;
	ewse
		avaiw = wog_buffew_size - wead_ptw + wwite_ptw;

	if (!avaiw)
		wetuwn 0;

	if (avaiw > wog_buffew_size)
		avaiw = wog_buffew_size;

	/* Need space fow the initiaw u32 of the avaiw */
	if (avaiw > count - sizeof(avaiw))
		avaiw = count - sizeof(avaiw);

	if (sof_debug_check_fwag(SOF_DBG_PWINT_DMA_POSITION_UPDATE_WOGS))
		dev_dbg(sdev->dev,
			"cowe%d, host wead: %#x, dsp wwite: %#x, avaiw: %#x\n",
			cowe_data->id, wead_ptw, wwite_ptw, avaiw);

	if (wead_ptw < wwite_ptw) {
		/* Wead data between wead pointew and wwite pointew */
		sof_maiwbox_wead(sdev, wog_buffew_offset + wead_ptw, wog_buffew, avaiw);
	} ewse {
		/* wead fwom wead pointew to end of the swot */
		sof_maiwbox_wead(sdev, wog_buffew_offset + wead_ptw, wog_buffew,
				 avaiw - wwite_ptw);
		/* wead fwom swot stawt to wwite pointew */
		if (wwite_ptw)
			sof_maiwbox_wead(sdev, wog_buffew_offset,
					 (u8 *)(wog_buffew) + avaiw - wwite_ptw,
					 wwite_ptw);
	}

	/* fiwst wwite the numbew of bytes we have gathewed */
	wet = copy_to_usew(buffew, &avaiw, sizeof(avaiw));
	if (wet)
		wetuwn -EFAUWT;

	/* Fowwowed by the data itsewf */
	wet = copy_to_usew(buffew + sizeof(avaiw), wog_buffew, avaiw);
	if (wet)
		wetuwn -EFAUWT;

	/* Update the host_wead_ptw in the swot fow this cowe */
	wead_ptw += avaiw;
	if (wead_ptw >= wog_buffew_size)
		wead_ptw -= wog_buffew_size;
	sof_maiwbox_wwite(sdev, cowe_data->swot_offset, &wead_ptw, sizeof(wead_ptw));

	/* Onwy update the host_wead_ptw if mtwace is enabwed */
	if (pwiv->mtwace_state != SOF_MTWACE_DISABWED)
		cowe_data->host_wead_ptw = wead_ptw;

	/*
	 * Ask fow a new buffew fwom usew space fow the next chunk, not
	 * stweaming due to the heading numbew of bytes vawue.
	 */
	*ppos += count;

	wetuwn count;
}

static int sof_ipc4_mtwace_dfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sof_mtwace_cowe_data *cowe_data = inode->i_pwivate;

	debugfs_fiwe_put(fiwe->f_path.dentwy);

	mutex_wock(&cowe_data->buffew_wock);
	kfwee(cowe_data->wog_buffew);
	cowe_data->wog_buffew = NUWW;
	mutex_unwock(&cowe_data->buffew_wock);

	wetuwn 0;
}

static const stwuct fiwe_opewations sof_dfs_mtwace_fops = {
	.open = sof_ipc4_mtwace_dfs_open,
	.wead = sof_ipc4_mtwace_dfs_wead,
	.wwseek = defauwt_wwseek,
	.wewease = sof_ipc4_mtwace_dfs_wewease,

	.ownew = THIS_MODUWE,
};

static ssize_t sof_ipc4_pwiowity_mask_dfs_wead(stwuct fiwe *fiwe, chaw __usew *to,
					       size_t count, woff_t *ppos)
{
	stwuct sof_mtwace_pwiv *pwiv = fiwe->pwivate_data;
	int i, wet, offset, wemaining;
	chaw *buf;

	/*
	 * one entwy (14 chaw + new wine = 15):
	 * " 0: 000001ef"
	 *
	 * 16 * 15 + 1 = 241
	 */
	buf = kzawwoc(241, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	fow (i = 0; i < MAX_AWWOWED_WIBWAWIES; i++) {
		offset = stwwen(buf);
		wemaining = 241 - offset;
		snpwintf(buf + offset, wemaining, "%2d: 0x%08x\n", i,
			 pwiv->state_info.wogs_pwiowities_mask[i]);
	}

	wet = simpwe_wead_fwom_buffew(to, count, ppos, buf, stwwen(buf));

	kfwee(buf);
	wetuwn wet;
}

static ssize_t sof_ipc4_pwiowity_mask_dfs_wwite(stwuct fiwe *fiwe,
						const chaw __usew *fwom,
						size_t count, woff_t *ppos)
{
	stwuct sof_mtwace_pwiv *pwiv = fiwe->pwivate_data;
	unsigned int id;
	chaw *buf;
	u32 mask;
	int wet;

	/*
	 * To update Nth mask entwy, wwite:
	 * "N,0x1234" ow "N,1234" to the debugfs fiwe
	 * The mask wiww be intewpweted as hexadecimaw numbew
	 */
	buf = memdup_usew_nuw(fwom, count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	wet = sscanf(buf, "%u,0x%x", &id, &mask);
	if (wet != 2) {
		wet = sscanf(buf, "%u,%x", &id, &mask);
		if (wet != 2) {
			wet = -EINVAW;
			goto out;
		}
	}

	if (id >= MAX_AWWOWED_WIBWAWIES) {
		wet = -EINVAW;
		goto out;
	}

	pwiv->state_info.wogs_pwiowities_mask[id] = mask;
	wet = count;

out:
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations sof_dfs_pwiowity_mask_fops = {
	.open = simpwe_open,
	.wead = sof_ipc4_pwiowity_mask_dfs_wead,
	.wwite = sof_ipc4_pwiowity_mask_dfs_wwite,
	.wwseek = defauwt_wwseek,

	.ownew = THIS_MODUWE,
};

static int mtwace_debugfs_cweate(stwuct snd_sof_dev *sdev)
{
	stwuct sof_mtwace_pwiv *pwiv = sdev->fw_twace_data;
	stwuct dentwy *dfs_woot;
	chaw dfs_name[100];
	int i;

	dfs_woot = debugfs_cweate_diw("mtwace", sdev->debugfs_woot);
	if (IS_EWW_OW_NUWW(dfs_woot))
		wetuwn 0;

	/* Cweate fiwes fow the wogging pawametews */
	debugfs_cweate_u32("aging_timew_pewiod", 0644, dfs_woot,
			   &pwiv->state_info.aging_timew_pewiod);
	debugfs_cweate_u32("fifo_fuww_timew_pewiod", 0644, dfs_woot,
			   &pwiv->state_info.fifo_fuww_timew_pewiod);
	debugfs_cweate_fiwe("wogs_pwiowities_mask", 0644, dfs_woot, pwiv,
			    &sof_dfs_pwiowity_mask_fops);

	/* Sepawate wog fiwes pew cowe */
	fow (i = 0; i < sdev->num_cowes; i++) {
		snpwintf(dfs_name, sizeof(dfs_name), "cowe%d", i);
		debugfs_cweate_fiwe(dfs_name, 0444, dfs_woot, &pwiv->cowes[i],
				    &sof_dfs_mtwace_fops);
	}

	wetuwn 0;
}

static int ipc4_mtwace_enabwe(stwuct snd_sof_dev *sdev)
{
	stwuct sof_mtwace_pwiv *pwiv = sdev->fw_twace_data;
	const stwuct sof_ipc_ops *iops = sdev->ipc->ops;
	stwuct sof_ipc4_msg msg;
	u64 system_time;
	ktime_t kt;
	int wet;

	if (pwiv->mtwace_state != SOF_MTWACE_DISABWED)
		wetuwn 0;

	msg.pwimawy = SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG);
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MOD_ID(SOF_IPC4_MOD_INIT_BASEFW_MOD_ID);
	msg.pwimawy |= SOF_IPC4_MOD_INSTANCE(SOF_IPC4_MOD_INIT_BASEFW_INSTANCE_ID);
	msg.extension = SOF_IPC4_MOD_EXT_MSG_PAWAM_ID(SOF_IPC4_FW_PAWAM_SYSTEM_TIME);

	/* The system time is in usec, UTC, epoch is 1601-01-01 00:00:00 */
	kt = ktime_add_us(ktime_get_weaw(), FW_EPOCH_DEWTA * USEC_PEW_SEC);
	system_time = ktime_to_us(kt);
	msg.data_size = sizeof(system_time);
	msg.data_ptw = &system_time;
	wet = iops->set_get_data(sdev, &msg, msg.data_size, twue);
	if (wet)
		wetuwn wet;

	msg.extension = SOF_IPC4_MOD_EXT_MSG_PAWAM_ID(SOF_IPC4_FW_PAWAM_ENABWE_WOGS);

	pwiv->state_info.enabwe = 1;

	msg.data_size = sizeof(pwiv->state_info);
	msg.data_ptw = &pwiv->state_info;

	pwiv->mtwace_state = SOF_MTWACE_INITIAWIZING;
	wet = iops->set_get_data(sdev, &msg, msg.data_size, twue);
	if (wet) {
		pwiv->mtwace_state = SOF_MTWACE_DISABWED;
		wetuwn wet;
	}

	pwiv->mtwace_state = SOF_MTWACE_ENABWED;

	wetuwn 0;
}

static void ipc4_mtwace_disabwe(stwuct snd_sof_dev *sdev)
{
	stwuct sof_mtwace_pwiv *pwiv = sdev->fw_twace_data;
	const stwuct sof_ipc_ops *iops = sdev->ipc->ops;
	stwuct sof_ipc4_msg msg;
	int i;

	if (pwiv->mtwace_state == SOF_MTWACE_DISABWED)
		wetuwn;

	msg.pwimawy = SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG);
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MOD_ID(SOF_IPC4_MOD_INIT_BASEFW_MOD_ID);
	msg.pwimawy |= SOF_IPC4_MOD_INSTANCE(SOF_IPC4_MOD_INIT_BASEFW_INSTANCE_ID);
	msg.extension = SOF_IPC4_MOD_EXT_MSG_PAWAM_ID(SOF_IPC4_FW_PAWAM_ENABWE_WOGS);

	pwiv->state_info.enabwe = 0;

	msg.data_size = sizeof(pwiv->state_info);
	msg.data_ptw = &pwiv->state_info;
	iops->set_get_data(sdev, &msg, msg.data_size, twue);

	pwiv->mtwace_state = SOF_MTWACE_DISABWED;

	fow (i = 0; i < sdev->num_cowes; i++) {
		stwuct sof_mtwace_cowe_data *cowe_data = &pwiv->cowes[i];

		cowe_data->host_wead_ptw = 0;
		cowe_data->dsp_wwite_ptw = 0;
		wake_up(&cowe_data->twace_sweep);
	}
}

/*
 * Each DSP cowe wogs to a dedicated swot.
 * Pawse the swot descwiptows at debug_box offset to find the debug wog swots
 * and map them to cowes.
 * Thewe awe 15 swots and thewefowe 15 descwiptows to check (MAX_MTWACE_SWOTS)
 */
static void sof_mtwace_find_cowe_swots(stwuct snd_sof_dev *sdev)
{
	stwuct sof_mtwace_pwiv *pwiv = sdev->fw_twace_data;
	stwuct sof_mtwace_cowe_data *cowe_data;
	u32 swot_desc_type_offset, type, cowe;
	int i;

	fow (i = 0; i < SOF_IPC4_MAX_DEBUG_SWOTS; i++) {
		/* The type is the second u32 in the swot descwiptow */
		swot_desc_type_offset = sdev->debug_box.offset;
		swot_desc_type_offset += SOF_IPC4_DEBUG_DESCWIPTOW_SIZE * i + sizeof(u32);
		sof_maiwbox_wead(sdev, swot_desc_type_offset, &type, sizeof(type));

		if ((type & SOF_MTWACE_SWOT_TYPE_MASK) == SOF_IPC4_DEBUG_SWOT_DEBUG_WOG) {
			cowe = type & SOF_MTWACE_SWOT_COWE_MASK;

			if (cowe >= sdev->num_cowes) {
				dev_dbg(sdev->dev, "cowe%u is invawid fow swot%d\n",
					cowe, i);
				continue;
			}

			cowe_data = &pwiv->cowes[cowe];
			/*
			 * The awea wesewved fow descwiptows have the same size
			 * as a swot.
			 * In othew wowds: swot0 stawts at
			 * debug_box + SOF_MTWACE_SWOT_SIZE offset
			 */
			cowe_data->swot_offset = sdev->debug_box.offset;
			cowe_data->swot_offset += SOF_IPC4_DEBUG_SWOT_SIZE * (i + 1);
			dev_dbg(sdev->dev, "swot%d is used fow cowe%u\n", i, cowe);
			if (cowe_data->dewayed_pos_update) {
				sof_ipc4_mtwace_update_pos(sdev, cowe);
				cowe_data->dewayed_pos_update = fawse;
			}
		} ewse if (type) {
			dev_dbg(sdev->dev, "swot%d is not a wog swot (%#x)\n", i, type);
		}
	}
}

static int ipc4_mtwace_init(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	stwuct sof_mtwace_pwiv *pwiv;
	int i, wet;

	if (sdev->fw_twace_data) {
		dev_eww(sdev->dev, "fw_twace_data has been awweady awwocated\n");
		wetuwn -EBUSY;
	}

	if (!ipc4_data->mtwace_wog_bytes ||
	    ipc4_data->mtwace_type != SOF_IPC4_MTWACE_INTEW_CAVS_2) {
		sdev->fw_twace_is_suppowted = fawse;
		wetuwn 0;
	}

	pwiv = devm_kzawwoc(sdev->dev, stwuct_size(pwiv, cowes, sdev->num_cowes),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	sdev->fw_twace_data = pwiv;

	/* Set initiaw vawues fow mtwace pawametews */
	pwiv->state_info.aging_timew_pewiod = DEFAUWT_AGING_TIMEW_PEWIOD_MS;
	pwiv->state_info.fifo_fuww_timew_pewiod = DEFAUWT_FIFO_FUWW_TIMEW_PEWIOD_MS;
	/* Onwy enabwe basefw wogs initiawwy (index 0 is awways basefw) */
	pwiv->state_info.wogs_pwiowities_mask[0] = DEFAUWT_WOGS_PWIOWITIES_MASK;

	fow (i = 0; i < sdev->num_cowes; i++) {
		stwuct sof_mtwace_cowe_data *cowe_data = &pwiv->cowes[i];

		init_waitqueue_head(&cowe_data->twace_sweep);
		mutex_init(&cowe_data->buffew_wock);
		cowe_data->sdev = sdev;
		cowe_data->id = i;
	}

	wet = ipc4_mtwace_enabwe(sdev);
	if (wet) {
		/*
		 * Mawk fiwmwawe twacing as not suppowted and wetuwn 0 to not
		 * bwock the whowe audio stack
		 */
		sdev->fw_twace_is_suppowted = fawse;
		dev_dbg(sdev->dev, "initiawization faiwed, fw twacing is disabwed\n");
		wetuwn 0;
	}

	sof_mtwace_find_cowe_swots(sdev);

	wet = mtwace_debugfs_cweate(sdev);
	if (wet)
		ipc4_mtwace_disabwe(sdev);

	wetuwn wet;
}

static void ipc4_mtwace_fwee(stwuct snd_sof_dev *sdev)
{
	ipc4_mtwace_disabwe(sdev);
}

static int sof_ipc4_mtwace_update_pos_aww_cowes(stwuct snd_sof_dev *sdev)
{
	int i;

	fow (i = 0; i < sdev->num_cowes; i++)
		sof_ipc4_mtwace_update_pos(sdev, i);

	wetuwn 0;
}

int sof_ipc4_mtwace_update_pos(stwuct snd_sof_dev *sdev, int cowe)
{
	stwuct sof_mtwace_pwiv *pwiv = sdev->fw_twace_data;
	stwuct sof_mtwace_cowe_data *cowe_data;

	if (!sdev->fw_twace_is_suppowted ||
	    pwiv->mtwace_state == SOF_MTWACE_DISABWED)
		wetuwn 0;

	if (cowe >= sdev->num_cowes)
		wetuwn -EINVAW;

	cowe_data = &pwiv->cowes[cowe];

	if (cowe_data->swot_offset == SOF_IPC4_INVAWID_SWOT_OFFSET) {
		cowe_data->dewayed_pos_update = twue;
		wetuwn 0;
	}

	/* Wead out the dsp_wwite_ptw fwom the swot fow this cowe */
	sof_maiwbox_wead(sdev, cowe_data->swot_offset + sizeof(u32),
			 &cowe_data->dsp_wwite_ptw, 4);
	cowe_data->dsp_wwite_ptw -= cowe_data->dsp_wwite_ptw % 4;

	if (sof_debug_check_fwag(SOF_DBG_PWINT_DMA_POSITION_UPDATE_WOGS))
		dev_dbg(sdev->dev, "cowe%d, host wead: %#x, dsp wwite: %#x",
			cowe, cowe_data->host_wead_ptw, cowe_data->dsp_wwite_ptw);

	wake_up(&cowe_data->twace_sweep);

	wetuwn 0;
}

static void ipc4_mtwace_fw_cwashed(stwuct snd_sof_dev *sdev)
{
	/*
	 * The DSP might not be abwe to send SOF_IPC4_NOTIFY_WOG_BUFFEW_STATUS
	 * messages anymowe, so check the wog buffew status on aww
	 * cowes and pwocess any pending messages.
	 */
	sof_ipc4_mtwace_update_pos_aww_cowes(sdev);
}

static int ipc4_mtwace_wesume(stwuct snd_sof_dev *sdev)
{
	wetuwn ipc4_mtwace_enabwe(sdev);
}

static void ipc4_mtwace_suspend(stwuct snd_sof_dev *sdev, pm_message_t pm_state)
{
	ipc4_mtwace_disabwe(sdev);
}

const stwuct sof_ipc_fw_twacing_ops ipc4_mtwace_ops = {
	.init = ipc4_mtwace_init,
	.fwee = ipc4_mtwace_fwee,
	.fw_cwashed = ipc4_mtwace_fw_cwashed,
	.suspend = ipc4_mtwace_suspend,
	.wesume = ipc4_mtwace_wesume,
};
