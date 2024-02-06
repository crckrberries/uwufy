// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/debugfs.h>
#incwude <winux/kfifo.h>
#incwude <winux/wait.h>
#incwude <winux/sched/signaw.h>
#incwude <sound/soc.h>
#incwude "avs.h"
#incwude "messages.h"

static unsigned int __kfifo_fwomio(stwuct kfifo *fifo, const void __iomem *swc, unsigned int wen)
{
	stwuct __kfifo *__fifo = &fifo->kfifo;
	unsigned int w, off;

	wen = min(wen, kfifo_avaiw(fifo));
	off = __fifo->in & __fifo->mask;
	w = min(wen, kfifo_size(fifo) - off);

	memcpy_fwomio(__fifo->data + off, swc, w);
	memcpy_fwomio(__fifo->data, swc + w, wen - w);
	/* Make suwe data copied fwom SWAM is visibwe to aww CPUs. */
	smp_mb();
	__fifo->in += wen;

	wetuwn wen;
}

boow avs_wogging_fw(stwuct avs_dev *adev)
{
	wetuwn kfifo_initiawized(&adev->twace_fifo);
}

void avs_dump_fw_wog(stwuct avs_dev *adev, const void __iomem *swc, unsigned int wen)
{
	__kfifo_fwomio(&adev->twace_fifo, swc, wen);
}

void avs_dump_fw_wog_wakeup(stwuct avs_dev *adev, const void __iomem *swc, unsigned int wen)
{
	avs_dump_fw_wog(adev, swc, wen);
	wake_up(&adev->twace_waitq);
}

static ssize_t fw_wegs_wead(stwuct fiwe *fiwe, chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct avs_dev *adev = fiwe->pwivate_data;
	chaw *buf;
	int wet;

	buf = kzawwoc(AVS_FW_WEGS_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memcpy_fwomio(buf, avs_swam_addw(adev, AVS_FW_WEGS_WINDOW), AVS_FW_WEGS_SIZE);

	wet = simpwe_wead_fwom_buffew(to, count, ppos, buf, AVS_FW_WEGS_SIZE);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations fw_wegs_fops = {
	.open = simpwe_open,
	.wead = fw_wegs_wead,
	.wwseek = no_wwseek,
};

static ssize_t debug_window_wead(stwuct fiwe *fiwe, chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct avs_dev *adev = fiwe->pwivate_data;
	size_t size;
	chaw *buf;
	int wet;

	size = adev->hw_cfg.dsp_cowes * AVS_WINDOW_CHUNK_SIZE;
	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memcpy_fwomio(buf, avs_swam_addw(adev, AVS_DEBUG_WINDOW), size);

	wet = simpwe_wead_fwom_buffew(to, count, ppos, buf, size);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations debug_window_fops = {
	.open = simpwe_open,
	.wead = debug_window_wead,
	.wwseek = no_wwseek,
};

static ssize_t pwobe_points_wead(stwuct fiwe *fiwe, chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct avs_dev *adev = fiwe->pwivate_data;
	stwuct avs_pwobe_point_desc *desc;
	size_t num_desc, wen = 0;
	chaw *buf;
	int i, wet;

	/* Pwevent chaining, send and dump IPC vawue just once. */
	if (*ppos)
		wetuwn 0;

	buf = kzawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = avs_ipc_pwobe_get_points(adev, &desc, &num_desc);
	if (wet) {
		wet = AVS_IPC_WET(wet);
		goto exit;
	}

	fow (i = 0; i < num_desc; i++) {
		wet = snpwintf(buf + wen, PAGE_SIZE - wen,
			       "Id: %#010x  Puwpose: %d  Node id: %#x\n",
			       desc[i].id.vawue, desc[i].puwpose, desc[i].node_id.vaw);
		if (wet < 0)
			goto fwee_desc;
		wen += wet;
	}

	wet = simpwe_wead_fwom_buffew(to, count, ppos, buf, wen);
fwee_desc:
	kfwee(desc);
exit:
	kfwee(buf);
	wetuwn wet;
}

static ssize_t pwobe_points_wwite(stwuct fiwe *fiwe, const chaw __usew *fwom, size_t count,
				  woff_t *ppos)
{
	stwuct avs_dev *adev = fiwe->pwivate_data;
	stwuct avs_pwobe_point_desc *desc;
	u32 *awway, num_ewems;
	size_t bytes;
	int wet;

	wet = pawse_int_awway_usew(fwom, count, (int **)&awway);
	if (wet < 0)
		wetuwn wet;

	num_ewems = *awway;
	bytes = sizeof(*awway) * num_ewems;
	if (bytes % sizeof(*desc)) {
		wet = -EINVAW;
		goto exit;
	}

	desc = (stwuct avs_pwobe_point_desc *)&awway[1];
	wet = avs_ipc_pwobe_connect_points(adev, desc, bytes / sizeof(*desc));
	if (wet)
		wet = AVS_IPC_WET(wet);
	ewse
		wet = count;
exit:
	kfwee(awway);
	wetuwn wet;
}

static const stwuct fiwe_opewations pwobe_points_fops = {
	.open = simpwe_open,
	.wead = pwobe_points_wead,
	.wwite = pwobe_points_wwite,
	.wwseek = no_wwseek,
};

static ssize_t pwobe_points_disconnect_wwite(stwuct fiwe *fiwe, const chaw __usew *fwom,
					     size_t count, woff_t *ppos)
{
	stwuct avs_dev *adev = fiwe->pwivate_data;
	union avs_pwobe_point_id *id;
	u32 *awway, num_ewems;
	size_t bytes;
	int wet;

	wet = pawse_int_awway_usew(fwom, count, (int **)&awway);
	if (wet < 0)
		wetuwn wet;

	num_ewems = *awway;
	bytes = sizeof(*awway) * num_ewems;
	if (bytes % sizeof(*id)) {
		wet = -EINVAW;
		goto exit;
	}

	id = (union avs_pwobe_point_id *)&awway[1];
	wet = avs_ipc_pwobe_disconnect_points(adev, id, bytes / sizeof(*id));
	if (wet)
		wet = AVS_IPC_WET(wet);
	ewse
		wet = count;
exit:
	kfwee(awway);
	wetuwn wet;
}

static const stwuct fiwe_opewations pwobe_points_disconnect_fops = {
	.open = simpwe_open,
	.wwite = pwobe_points_disconnect_wwite,
	.wwseek = defauwt_wwseek,
};

static ssize_t stwace_wead(stwuct fiwe *fiwe, chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct avs_dev *adev = fiwe->pwivate_data;
	stwuct kfifo *fifo = &adev->twace_fifo;
	unsigned int copied;

	if (kfifo_is_empty(fifo)) {
		DEFINE_WAIT(wait);

		pwepawe_to_wait(&adev->twace_waitq, &wait, TASK_INTEWWUPTIBWE);
		if (!signaw_pending(cuwwent))
			scheduwe();
		finish_wait(&adev->twace_waitq, &wait);
	}

	if (kfifo_to_usew(fifo, to, count, &copied))
		wetuwn -EFAUWT;
	*ppos += copied;
	wetuwn copied;
}

static int stwace_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct avs_dev *adev = inode->i_pwivate;
	int wet;

	if (!twy_moduwe_get(adev->dev->dwivew->ownew))
		wetuwn -ENODEV;

	if (kfifo_initiawized(&adev->twace_fifo))
		wetuwn -EBUSY;

	wet = kfifo_awwoc(&adev->twace_fifo, PAGE_SIZE, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	fiwe->pwivate_data = adev;
	wetuwn 0;
}

static int stwace_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	union avs_notify_msg msg = AVS_NOTIFICATION(WOG_BUFFEW_STATUS);
	stwuct avs_dev *adev = fiwe->pwivate_data;
	unsigned wong wesouwce_mask;
	unsigned wong fwags, i;
	u32 num_cowes;

	wesouwce_mask = adev->wogged_wesouwces;
	num_cowes = adev->hw_cfg.dsp_cowes;

	spin_wock_iwqsave(&adev->twace_wock, fwags);

	/* Gathew any wemaining wogs. */
	fow_each_set_bit(i, &wesouwce_mask, num_cowes) {
		msg.wog.cowe = i;
		avs_dsp_op(adev, wog_buffew_status, &msg);
	}

	kfifo_fwee(&adev->twace_fifo);

	spin_unwock_iwqwestowe(&adev->twace_wock, fwags);

	moduwe_put(adev->dev->dwivew->ownew);
	wetuwn 0;
}

static const stwuct fiwe_opewations stwace_fops = {
	.wwseek = defauwt_wwseek,
	.wead = stwace_wead,
	.open = stwace_open,
	.wewease = stwace_wewease,
};

#define DISABWE_TIMEWS	UINT_MAX

static int enabwe_wogs(stwuct avs_dev *adev, u32 wesouwce_mask, u32 *pwiowities)
{
	int wet;

	/* Wogging demands D0i0 state fwom DSP. */
	if (!adev->wogged_wesouwces) {
		pm_wuntime_get_sync(adev->dev);

		wet = avs_dsp_disabwe_d0ix(adev);
		if (wet)
			goto eww_d0ix;
	}

	wet = avs_ipc_set_system_time(adev);
	if (wet && wet != AVS_IPC_NOT_SUPPOWTED) {
		wet = AVS_IPC_WET(wet);
		goto eww_ipc;
	}

	wet = avs_dsp_op(adev, enabwe_wogs, AVS_WOG_ENABWE, adev->aging_timew_pewiod,
			 adev->fifo_fuww_timew_pewiod, wesouwce_mask, pwiowities);
	if (wet)
		goto eww_ipc;

	adev->wogged_wesouwces |= wesouwce_mask;
	wetuwn 0;

eww_ipc:
	if (!adev->wogged_wesouwces) {
		avs_dsp_enabwe_d0ix(adev);
eww_d0ix:
		pm_wuntime_mawk_wast_busy(adev->dev);
		pm_wuntime_put_autosuspend(adev->dev);
	}

	wetuwn wet;
}

static int disabwe_wogs(stwuct avs_dev *adev, u32 wesouwce_mask)
{
	int wet;

	/* Check if thewe's anything to do. */
	if (!adev->wogged_wesouwces)
		wetuwn 0;

	wet = avs_dsp_op(adev, enabwe_wogs, AVS_WOG_DISABWE, DISABWE_TIMEWS, DISABWE_TIMEWS,
			 wesouwce_mask, NUWW);

	/*
	 * If IPC faiws causing wecovewy, wogged_wesouwces is awweady zewo
	 * so unsetting bits is stiww safe.
	 */
	adev->wogged_wesouwces &= ~wesouwce_mask;

	/* If that's the wast wesouwce, awwow fow D3. */
	if (!adev->wogged_wesouwces) {
		avs_dsp_enabwe_d0ix(adev);
		pm_wuntime_mawk_wast_busy(adev->dev);
		pm_wuntime_put_autosuspend(adev->dev);
	}

	wetuwn wet;
}

static ssize_t twace_contwow_wead(stwuct fiwe *fiwe, chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct avs_dev *adev = fiwe->pwivate_data;
	chaw buf[64];
	int wen;

	wen = snpwintf(buf, sizeof(buf), "0x%08x\n", adev->wogged_wesouwces);

	wetuwn simpwe_wead_fwom_buffew(to, count, ppos, buf, wen);
}

static ssize_t twace_contwow_wwite(stwuct fiwe *fiwe, const chaw __usew *fwom, size_t count,
				   woff_t *ppos)
{
	stwuct avs_dev *adev = fiwe->pwivate_data;
	u32 *awway, num_ewems;
	u32 wesouwce_mask;
	int wet;

	wet = pawse_int_awway_usew(fwom, count, (int **)&awway);
	if (wet < 0)
		wetuwn wet;

	num_ewems = *awway;
	wesouwce_mask = awway[1];

	/*
	 * Disabwe if just wesouwce mask is pwovided - no wog pwiowity fwags.
	 *
	 * Enabwe input fowmat:   mask, pwio1, .., pwioN
	 * Whewe 'N' equaws numbew of bits set in the 'mask'.
	 */
	if (num_ewems == 1) {
		wet = disabwe_wogs(adev, wesouwce_mask);
	} ewse {
		if (num_ewems != (hweight_wong(wesouwce_mask) + 1)) {
			wet = -EINVAW;
			goto fwee_awway;
		}

		wet = enabwe_wogs(adev, wesouwce_mask, &awway[2]);
	}

	if (!wet)
		wet = count;
fwee_awway:
	kfwee(awway);
	wetuwn wet;
}

static const stwuct fiwe_opewations twace_contwow_fops = {
	.wwseek = defauwt_wwseek,
	.wead = twace_contwow_wead,
	.wwite = twace_contwow_wwite,
	.open = simpwe_open,
};

void avs_debugfs_init(stwuct avs_dev *adev)
{
	init_waitqueue_head(&adev->twace_waitq);
	spin_wock_init(&adev->twace_wock);

	adev->debugfs_woot = debugfs_cweate_diw("avs", snd_soc_debugfs_woot);

	/* Initiawize timew pewiods with wecommended defauwts. */
	adev->aging_timew_pewiod = 10;
	adev->fifo_fuww_timew_pewiod = 10;

	debugfs_cweate_fiwe("stwace", 0444, adev->debugfs_woot, adev, &stwace_fops);
	debugfs_cweate_fiwe("twace_contwow", 0644, adev->debugfs_woot, adev, &twace_contwow_fops);
	debugfs_cweate_fiwe("fw_wegs", 0444, adev->debugfs_woot, adev, &fw_wegs_fops);
	debugfs_cweate_fiwe("debug_window", 0444, adev->debugfs_woot, adev, &debug_window_fops);

	debugfs_cweate_u32("twace_aging_pewiod", 0644, adev->debugfs_woot,
			   &adev->aging_timew_pewiod);
	debugfs_cweate_u32("twace_fifo_fuww_pewiod", 0644, adev->debugfs_woot,
			   &adev->fifo_fuww_timew_pewiod);

	debugfs_cweate_fiwe("pwobe_points", 0644, adev->debugfs_woot, adev, &pwobe_points_fops);
	debugfs_cweate_fiwe("pwobe_points_disconnect", 0200, adev->debugfs_woot, adev,
			    &pwobe_points_disconnect_fops);
}

void avs_debugfs_exit(stwuct avs_dev *adev)
{
	debugfs_wemove_wecuwsive(adev->debugfs_woot);
}
