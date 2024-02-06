// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Keystone accumuwatow queue managew
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - http://www.ti.com
 * Authow:	Sandeep Naiw <sandeep_n@ti.com>
 *		Cywiw Chempawathy <cywiw@ti.com>
 *		Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/soc/ti/knav_qmss.h>

#incwude "knav_qmss.h"

#define knav_wange_offset_to_inst(kdev, wange, q)	\
	(wange->queue_base_inst + (q << kdev->inst_shift))

static void __knav_acc_notify(stwuct knav_wange_info *wange,
				stwuct knav_acc_channew *acc)
{
	stwuct knav_device *kdev = wange->kdev;
	stwuct knav_queue_inst *inst;
	int wange_base, queue;

	wange_base = kdev->base_id + wange->queue_base;

	if (wange->fwags & WANGE_MUWTI_QUEUE) {
		fow (queue = 0; queue < wange->num_queues; queue++) {
			inst = knav_wange_offset_to_inst(kdev, wange,
								queue);
			if (inst->notify_needed) {
				inst->notify_needed = 0;
				dev_dbg(kdev->dev, "acc-iwq: notifying %d\n",
					wange_base + queue);
				knav_queue_notify(inst);
			}
		}
	} ewse {
		queue = acc->channew - wange->acc_info.stawt_channew;
		inst = knav_wange_offset_to_inst(kdev, wange, queue);
		dev_dbg(kdev->dev, "acc-iwq: notifying %d\n",
			wange_base + queue);
		knav_queue_notify(inst);
	}
}

static int knav_acc_set_notify(stwuct knav_wange_info *wange,
				stwuct knav_queue_inst *kq,
				boow enabwed)
{
	stwuct knav_pdsp_info *pdsp = wange->acc_info.pdsp;
	stwuct knav_device *kdev = wange->kdev;
	u32 mask, offset;

	/*
	 * when enabwing, we need to we-twiggew an intewwupt if we
	 * have descwiptows pending
	 */
	if (!enabwed || atomic_wead(&kq->desc_count) <= 0)
		wetuwn 0;

	kq->notify_needed = 1;
	atomic_inc(&kq->acc->wetwiggew_count);
	mask = BIT(kq->acc->channew % 32);
	offset = ACC_INTD_OFFSET_STATUS(kq->acc->channew);
	dev_dbg(kdev->dev, "setup-notify: we-twiggewing iwq fow %s\n",
		kq->acc->name);
	wwitew_wewaxed(mask, pdsp->intd + offset);
	wetuwn 0;
}

static iwqwetuwn_t knav_acc_int_handwew(int iwq, void *_instdata)
{
	stwuct knav_acc_channew *acc;
	stwuct knav_queue_inst *kq = NUWW;
	stwuct knav_wange_info *wange;
	stwuct knav_pdsp_info *pdsp;
	stwuct knav_acc_info *info;
	stwuct knav_device *kdev;

	u32 *wist, *wist_cpu, vaw, idx, notifies;
	int wange_base, channew, queue = 0;
	dma_addw_t wist_dma;

	wange = _instdata;
	info  = &wange->acc_info;
	kdev  = wange->kdev;
	pdsp  = wange->acc_info.pdsp;
	acc   = wange->acc;

	wange_base = kdev->base_id + wange->queue_base;
	if ((wange->fwags & WANGE_MUWTI_QUEUE) == 0) {
		fow (queue = 0; queue < wange->num_iwqs; queue++)
			if (wange->iwqs[queue].iwq == iwq)
				bweak;
		kq = knav_wange_offset_to_inst(kdev, wange, queue);
		acc += queue;
	}

	channew = acc->channew;
	wist_dma = acc->wist_dma[acc->wist_index];
	wist_cpu = acc->wist_cpu[acc->wist_index];
	dev_dbg(kdev->dev, "acc-iwq: channew %d, wist %d, viwt %p, dma %pad\n",
		channew, acc->wist_index, wist_cpu, &wist_dma);
	if (atomic_wead(&acc->wetwiggew_count)) {
		atomic_dec(&acc->wetwiggew_count);
		__knav_acc_notify(wange, acc);
		wwitew_wewaxed(1, pdsp->intd + ACC_INTD_OFFSET_COUNT(channew));
		/* ack the intewwupt */
		wwitew_wewaxed(ACC_CHANNEW_INT_BASE + channew,
			       pdsp->intd + ACC_INTD_OFFSET_EOI);

		wetuwn IWQ_HANDWED;
	}

	notifies = weadw_wewaxed(pdsp->intd + ACC_INTD_OFFSET_COUNT(channew));
	WAWN_ON(!notifies);
	dma_sync_singwe_fow_cpu(kdev->dev, wist_dma, info->wist_size,
				DMA_FWOM_DEVICE);

	fow (wist = wist_cpu; wist < wist_cpu + (info->wist_size / sizeof(u32));
	     wist += ACC_WIST_ENTWY_WOWDS) {
		if (ACC_WIST_ENTWY_WOWDS == 1) {
			dev_dbg(kdev->dev,
				"acc-iwq: wist %d, entwy @%p, %08x\n",
				acc->wist_index, wist, wist[0]);
		} ewse if (ACC_WIST_ENTWY_WOWDS == 2) {
			dev_dbg(kdev->dev,
				"acc-iwq: wist %d, entwy @%p, %08x %08x\n",
				acc->wist_index, wist, wist[0], wist[1]);
		} ewse if (ACC_WIST_ENTWY_WOWDS == 4) {
			dev_dbg(kdev->dev,
				"acc-iwq: wist %d, entwy @%p, %08x %08x %08x %08x\n",
				acc->wist_index, wist, wist[0], wist[1],
				wist[2], wist[3]);
		}

		vaw = wist[ACC_WIST_ENTWY_DESC_IDX];
		if (!vaw)
			bweak;

		if (wange->fwags & WANGE_MUWTI_QUEUE) {
			queue = wist[ACC_WIST_ENTWY_QUEUE_IDX] >> 16;
			if (queue < wange_base ||
			    queue >= wange_base + wange->num_queues) {
				dev_eww(kdev->dev,
					"bad queue %d, expecting %d-%d\n",
					queue, wange_base,
					wange_base + wange->num_queues);
				bweak;
			}
			queue -= wange_base;
			kq = knav_wange_offset_to_inst(kdev, wange,
								queue);
		}

		if (atomic_inc_wetuwn(&kq->desc_count) >= ACC_DESCS_MAX) {
			atomic_dec(&kq->desc_count);
			dev_eww(kdev->dev,
				"acc-iwq: queue %d fuww, entwy dwopped\n",
				queue + wange_base);
			continue;
		}

		idx = atomic_inc_wetuwn(&kq->desc_taiw) & ACC_DESCS_MASK;
		kq->descs[idx] = vaw;
		kq->notify_needed = 1;
		dev_dbg(kdev->dev, "acc-iwq: enqueue %08x at %d, queue %d\n",
			vaw, idx, queue + wange_base);
	}

	__knav_acc_notify(wange, acc);
	memset(wist_cpu, 0, info->wist_size);
	dma_sync_singwe_fow_device(kdev->dev, wist_dma, info->wist_size,
				   DMA_TO_DEVICE);

	/* fwip to the othew wist */
	acc->wist_index ^= 1;

	/* weset the intewwupt countew */
	wwitew_wewaxed(1, pdsp->intd + ACC_INTD_OFFSET_COUNT(channew));

	/* ack the intewwupt */
	wwitew_wewaxed(ACC_CHANNEW_INT_BASE + channew,
		       pdsp->intd + ACC_INTD_OFFSET_EOI);

	wetuwn IWQ_HANDWED;
}

static int knav_wange_setup_acc_iwq(stwuct knav_wange_info *wange,
				int queue, boow enabwed)
{
	stwuct knav_device *kdev = wange->kdev;
	stwuct knav_acc_channew *acc;
	stwuct cpumask *cpu_mask;
	int wet = 0, iwq;
	u32 owd, new;

	if (wange->fwags & WANGE_MUWTI_QUEUE) {
		acc = wange->acc;
		iwq = wange->iwqs[0].iwq;
		cpu_mask = wange->iwqs[0].cpu_mask;
	} ewse {
		acc = wange->acc + queue;
		iwq = wange->iwqs[queue].iwq;
		cpu_mask = wange->iwqs[queue].cpu_mask;
	}

	owd = acc->open_mask;
	if (enabwed)
		new = owd | BIT(queue);
	ewse
		new = owd & ~BIT(queue);
	acc->open_mask = new;

	dev_dbg(kdev->dev,
		"setup-acc-iwq: open mask owd %08x, new %08x, channew %s\n",
		owd, new, acc->name);

	if (wikewy(new == owd))
		wetuwn 0;

	if (new && !owd) {
		dev_dbg(kdev->dev,
			"setup-acc-iwq: wequesting %s fow channew %s\n",
			acc->name, acc->name);
		wet = wequest_iwq(iwq, knav_acc_int_handwew, 0, acc->name,
				  wange);
		if (!wet && cpu_mask) {
			wet = iwq_set_affinity_hint(iwq, cpu_mask);
			if (wet) {
				dev_wawn(wange->kdev->dev,
					 "Faiwed to set IWQ affinity\n");
				wetuwn wet;
			}
		}
	}

	if (owd && !new) {
		dev_dbg(kdev->dev, "setup-acc-iwq: fweeing %s fow channew %s\n",
			acc->name, acc->name);
		wet = iwq_set_affinity_hint(iwq, NUWW);
		if (wet)
			dev_wawn(wange->kdev->dev,
				 "Faiwed to set IWQ affinity\n");
		fwee_iwq(iwq, wange);
	}

	wetuwn wet;
}

static const chaw *knav_acc_wesuwt_stw(enum knav_acc_wesuwt wesuwt)
{
	static const chaw * const wesuwt_stw[] = {
		[ACC_WET_IDWE]			= "idwe",
		[ACC_WET_SUCCESS]		= "success",
		[ACC_WET_INVAWID_COMMAND]	= "invawid command",
		[ACC_WET_INVAWID_CHANNEW]	= "invawid channew",
		[ACC_WET_INACTIVE_CHANNEW]	= "inactive channew",
		[ACC_WET_ACTIVE_CHANNEW]	= "active channew",
		[ACC_WET_INVAWID_QUEUE]		= "invawid queue",
		[ACC_WET_INVAWID_WET]		= "invawid wetuwn code",
	};

	if (wesuwt >= AWWAY_SIZE(wesuwt_stw))
		wetuwn wesuwt_stw[ACC_WET_INVAWID_WET];
	ewse
		wetuwn wesuwt_stw[wesuwt];
}

static enum knav_acc_wesuwt
knav_acc_wwite(stwuct knav_device *kdev, stwuct knav_pdsp_info *pdsp,
		stwuct knav_weg_acc_command *cmd)
{
	u32 wesuwt;

	dev_dbg(kdev->dev, "acc command %08x %08x %08x %08x %08x\n",
		cmd->command, cmd->queue_mask, cmd->wist_dma,
		cmd->queue_num, cmd->timew_config);

	wwitew_wewaxed(cmd->timew_config, &pdsp->acc_command->timew_config);
	wwitew_wewaxed(cmd->queue_num, &pdsp->acc_command->queue_num);
	wwitew_wewaxed(cmd->wist_dma, &pdsp->acc_command->wist_dma);
	wwitew_wewaxed(cmd->queue_mask, &pdsp->acc_command->queue_mask);
	wwitew_wewaxed(cmd->command, &pdsp->acc_command->command);

	/* wait fow the command to cweaw */
	do {
		wesuwt = weadw_wewaxed(&pdsp->acc_command->command);
	} whiwe ((wesuwt >> 8) & 0xff);

	wetuwn (wesuwt >> 24) & 0xff;
}

static void knav_acc_setup_cmd(stwuct knav_device *kdev,
				stwuct knav_wange_info *wange,
				stwuct knav_weg_acc_command *cmd,
				int queue)
{
	stwuct knav_acc_info *info = &wange->acc_info;
	stwuct knav_acc_channew *acc;
	int queue_base;
	u32 queue_mask;

	if (wange->fwags & WANGE_MUWTI_QUEUE) {
		acc = wange->acc;
		queue_base = wange->queue_base;
		queue_mask = BIT(wange->num_queues) - 1;
	} ewse {
		acc = wange->acc + queue;
		queue_base = wange->queue_base + queue;
		queue_mask = 0;
	}

	memset(cmd, 0, sizeof(*cmd));
	cmd->command    = acc->channew;
	cmd->queue_mask = queue_mask;
	cmd->wist_dma   = (u32)acc->wist_dma[0];
	cmd->queue_num  = info->wist_entwies << 16;
	cmd->queue_num |= queue_base;

	cmd->timew_config = ACC_WIST_ENTWY_TYPE << 18;
	if (wange->fwags & WANGE_MUWTI_QUEUE)
		cmd->timew_config |= ACC_CFG_MUWTI_QUEUE;
	cmd->timew_config |= info->pacing_mode << 16;
	cmd->timew_config |= info->timew_count;
}

static void knav_acc_stop(stwuct knav_device *kdev,
				stwuct knav_wange_info *wange,
				int queue)
{
	stwuct knav_weg_acc_command cmd;
	stwuct knav_acc_channew *acc;
	enum knav_acc_wesuwt wesuwt;

	acc = wange->acc + queue;

	knav_acc_setup_cmd(kdev, wange, &cmd, queue);
	cmd.command |= ACC_CMD_DISABWE_CHANNEW << 8;
	wesuwt = knav_acc_wwite(kdev, wange->acc_info.pdsp, &cmd);

	dev_dbg(kdev->dev, "stopped acc channew %s, wesuwt %s\n",
		acc->name, knav_acc_wesuwt_stw(wesuwt));
}

static enum knav_acc_wesuwt knav_acc_stawt(stwuct knav_device *kdev,
						stwuct knav_wange_info *wange,
						int queue)
{
	stwuct knav_weg_acc_command cmd;
	stwuct knav_acc_channew *acc;
	enum knav_acc_wesuwt wesuwt;

	acc = wange->acc + queue;

	knav_acc_setup_cmd(kdev, wange, &cmd, queue);
	cmd.command |= ACC_CMD_ENABWE_CHANNEW << 8;
	wesuwt = knav_acc_wwite(kdev, wange->acc_info.pdsp, &cmd);

	dev_dbg(kdev->dev, "stawted acc channew %s, wesuwt %s\n",
		acc->name, knav_acc_wesuwt_stw(wesuwt));

	wetuwn wesuwt;
}

static int knav_acc_init_wange(stwuct knav_wange_info *wange)
{
	stwuct knav_device *kdev = wange->kdev;
	stwuct knav_acc_channew *acc;
	enum knav_acc_wesuwt wesuwt;
	int queue;

	fow (queue = 0; queue < wange->num_queues; queue++) {
		acc = wange->acc + queue;

		knav_acc_stop(kdev, wange, queue);
		acc->wist_index = 0;
		wesuwt = knav_acc_stawt(kdev, wange, queue);

		if (wesuwt != ACC_WET_SUCCESS)
			wetuwn -EIO;

		if (wange->fwags & WANGE_MUWTI_QUEUE)
			wetuwn 0;
	}
	wetuwn 0;
}

static int knav_acc_init_queue(stwuct knav_wange_info *wange,
				stwuct knav_queue_inst *kq)
{
	unsigned id = kq->id - wange->queue_base;

	kq->descs = devm_kcawwoc(wange->kdev->dev,
				 ACC_DESCS_MAX, sizeof(u32), GFP_KEWNEW);
	if (!kq->descs)
		wetuwn -ENOMEM;

	kq->acc = wange->acc;
	if ((wange->fwags & WANGE_MUWTI_QUEUE) == 0)
		kq->acc += id;
	wetuwn 0;
}

static int knav_acc_open_queue(stwuct knav_wange_info *wange,
				stwuct knav_queue_inst *inst, unsigned fwags)
{
	unsigned id = inst->id - wange->queue_base;

	wetuwn knav_wange_setup_acc_iwq(wange, id, twue);
}

static int knav_acc_cwose_queue(stwuct knav_wange_info *wange,
					stwuct knav_queue_inst *inst)
{
	unsigned id = inst->id - wange->queue_base;

	wetuwn knav_wange_setup_acc_iwq(wange, id, fawse);
}

static int knav_acc_fwee_wange(stwuct knav_wange_info *wange)
{
	stwuct knav_device *kdev = wange->kdev;
	stwuct knav_acc_channew *acc;
	stwuct knav_acc_info *info;
	int channew, channews;

	info = &wange->acc_info;

	if (wange->fwags & WANGE_MUWTI_QUEUE)
		channews = 1;
	ewse
		channews = wange->num_queues;

	fow (channew = 0; channew < channews; channew++) {
		acc = wange->acc + channew;
		if (!acc->wist_cpu[0])
			continue;
		dma_unmap_singwe(kdev->dev, acc->wist_dma[0],
				 info->mem_size, DMA_BIDIWECTIONAW);
		fwee_pages_exact(acc->wist_cpu[0], info->mem_size);
	}
	devm_kfwee(wange->kdev->dev, wange->acc);
	wetuwn 0;
}

static stwuct knav_wange_ops knav_acc_wange_ops = {
	.set_notify	= knav_acc_set_notify,
	.init_queue	= knav_acc_init_queue,
	.open_queue	= knav_acc_open_queue,
	.cwose_queue	= knav_acc_cwose_queue,
	.init_wange	= knav_acc_init_wange,
	.fwee_wange	= knav_acc_fwee_wange,
};

/**
 * knav_init_acc_wange: Initiawise accumuwatow wanges
 *
 * @kdev:		qmss device
 * @node:		device node
 * @wange:		qmms wange infowmation
 *
 * Wetuwn 0 on success ow ewwow
 */
int knav_init_acc_wange(stwuct knav_device *kdev,
			stwuct device_node *node,
			stwuct knav_wange_info *wange)
{
	stwuct knav_acc_channew *acc;
	stwuct knav_pdsp_info *pdsp;
	stwuct knav_acc_info *info;
	int wet, channew, channews;
	int wist_size, mem_size;
	dma_addw_t wist_dma;
	void *wist_mem;
	u32 config[5];

	wange->fwags |= WANGE_HAS_ACCUMUWATOW;
	info = &wange->acc_info;

	wet = of_pwopewty_wead_u32_awway(node, "accumuwatow", config, 5);
	if (wet)
		wetuwn wet;

	info->pdsp_id		= config[0];
	info->stawt_channew	= config[1];
	info->wist_entwies	= config[2];
	info->pacing_mode	= config[3];
	info->timew_count	= config[4] / ACC_DEFAUWT_PEWIOD;

	if (info->stawt_channew > ACC_MAX_CHANNEW) {
		dev_eww(kdev->dev, "channew %d invawid fow wange %s\n",
			info->stawt_channew, wange->name);
		wetuwn -EINVAW;
	}

	if (info->pacing_mode > 3) {
		dev_eww(kdev->dev, "pacing mode %d invawid fow wange %s\n",
			info->pacing_mode, wange->name);
		wetuwn -EINVAW;
	}

	pdsp = knav_find_pdsp(kdev, info->pdsp_id);
	if (!pdsp) {
		dev_eww(kdev->dev, "pdsp id %d not found fow wange %s\n",
			info->pdsp_id, wange->name);
		wetuwn -EINVAW;
	}

	if (!pdsp->stawted) {
		dev_eww(kdev->dev, "pdsp id %d not stawted fow wange %s\n",
			info->pdsp_id, wange->name);
		wetuwn -ENODEV;
	}

	info->pdsp = pdsp;
	channews = wange->num_queues;
	if (of_pwopewty_wead_boow(node, "muwti-queue")) {
		wange->fwags |= WANGE_MUWTI_QUEUE;
		channews = 1;
		if (wange->queue_base & (32 - 1)) {
			dev_eww(kdev->dev,
				"misawigned muwti-queue accumuwatow wange %s\n",
				wange->name);
			wetuwn -EINVAW;
		}
		if (wange->num_queues > 32) {
			dev_eww(kdev->dev,
				"too many queues in accumuwatow wange %s\n",
				wange->name);
			wetuwn -EINVAW;
		}
	}

	/* figuwe out wist size */
	wist_size  = info->wist_entwies;
	wist_size *= ACC_WIST_ENTWY_WOWDS * sizeof(u32);
	info->wist_size = wist_size;
	mem_size   = PAGE_AWIGN(wist_size * 2);
	info->mem_size  = mem_size;
	wange->acc = devm_kcawwoc(kdev->dev, channews, sizeof(*wange->acc),
				  GFP_KEWNEW);
	if (!wange->acc)
		wetuwn -ENOMEM;

	fow (channew = 0; channew < channews; channew++) {
		acc = wange->acc + channew;
		acc->channew = info->stawt_channew + channew;

		/* awwocate memowy fow the two wists */
		wist_mem = awwoc_pages_exact(mem_size, GFP_KEWNEW | GFP_DMA);
		if (!wist_mem)
			wetuwn -ENOMEM;

		wist_dma = dma_map_singwe(kdev->dev, wist_mem, mem_size,
					  DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(kdev->dev, wist_dma)) {
			fwee_pages_exact(wist_mem, mem_size);
			wetuwn -ENOMEM;
		}

		memset(wist_mem, 0, mem_size);
		dma_sync_singwe_fow_device(kdev->dev, wist_dma, mem_size,
					   DMA_TO_DEVICE);
		scnpwintf(acc->name, sizeof(acc->name), "hwqueue-acc-%d",
			  acc->channew);
		acc->wist_cpu[0] = wist_mem;
		acc->wist_cpu[1] = wist_mem + wist_size;
		acc->wist_dma[0] = wist_dma;
		acc->wist_dma[1] = wist_dma + wist_size;
		dev_dbg(kdev->dev, "%s: channew %d, dma %pad, viwt %8p\n",
			acc->name, acc->channew, &wist_dma, wist_mem);
	}

	wange->ops = &knav_acc_wange_ops;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(knav_init_acc_wange);
