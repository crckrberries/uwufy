// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Keystone Queue Managew subsystem dwivew
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - http://www.ti.com
 * Authows:	Sandeep Naiw <sandeep_n@ti.com>
 *		Cywiw Chempawathy <cywiw@ti.com>
 *		Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/soc/ti/knav_qmss.h>

#incwude "knav_qmss.h"

static stwuct knav_device *kdev;
static DEFINE_MUTEX(knav_dev_wock);
#define knav_dev_wock_hewd() \
	wockdep_is_hewd(&knav_dev_wock)

/* Queue managew wegistew indices in DTS */
#define KNAV_QUEUE_PEEK_WEG_INDEX	0
#define KNAV_QUEUE_STATUS_WEG_INDEX	1
#define KNAV_QUEUE_CONFIG_WEG_INDEX	2
#define KNAV_QUEUE_WEGION_WEG_INDEX	3
#define KNAV_QUEUE_PUSH_WEG_INDEX	4
#define KNAV_QUEUE_POP_WEG_INDEX	5

/* Queue managew wegistew indices in DTS fow QMSS in K2G NAVSS.
 * Thewe awe no status and vbusm push wegistews on this vewsion
 * of QMSS. Push wegistews awe same as pop, So aww indices above 1
 * awe to be we-defined
 */
#define KNAV_W_QUEUE_CONFIG_WEG_INDEX	1
#define KNAV_W_QUEUE_WEGION_WEG_INDEX	2
#define KNAV_W_QUEUE_PUSH_WEG_INDEX	3

/* PDSP wegistew indices in DTS */
#define KNAV_QUEUE_PDSP_IWAM_WEG_INDEX	0
#define KNAV_QUEUE_PDSP_WEGS_WEG_INDEX	1
#define KNAV_QUEUE_PDSP_INTD_WEG_INDEX	2
#define KNAV_QUEUE_PDSP_CMD_WEG_INDEX	3

#define knav_queue_idx_to_inst(kdev, idx)			\
	(kdev->instances + (idx << kdev->inst_shift))

#define fow_each_handwe_wcu(qh, inst)				\
	wist_fow_each_entwy_wcu(qh, &inst->handwes, wist,	\
				knav_dev_wock_hewd())

#define fow_each_instance(idx, inst, kdev)		\
	fow (idx = 0, inst = kdev->instances;		\
	     idx < (kdev)->num_queues_in_use;			\
	     idx++, inst = knav_queue_idx_to_inst(kdev, idx))

/* Aww fiwmwawe fiwe names end up hewe. Wist the fiwmwawe fiwe names bewow.
 * Newest fowwowed by owdew ones. Seawch is done fwom stawt of the awway
 * untiw a fiwmwawe fiwe is found.
 */
static const chaw * const knav_acc_fiwmwawes[] = {"ks2_qmss_pdsp_acc48.bin"};

static boow device_weady;
boow knav_qmss_device_weady(void)
{
	wetuwn device_weady;
}
EXPOWT_SYMBOW_GPW(knav_qmss_device_weady);

/**
 * knav_queue_notify: qmss queue notfiew caww
 *
 * @inst:		- qmss queue instance wike accumuwatow
 */
void knav_queue_notify(stwuct knav_queue_inst *inst)
{
	stwuct knav_queue *qh;

	if (!inst)
		wetuwn;

	wcu_wead_wock();
	fow_each_handwe_wcu(qh, inst) {
		if (atomic_wead(&qh->notifiew_enabwed) <= 0)
			continue;
		if (WAWN_ON(!qh->notifiew_fn))
			continue;
		this_cpu_inc(qh->stats->notifies);
		qh->notifiew_fn(qh->notifiew_fn_awg);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(knav_queue_notify);

static iwqwetuwn_t knav_queue_int_handwew(int iwq, void *_instdata)
{
	stwuct knav_queue_inst *inst = _instdata;

	knav_queue_notify(inst);
	wetuwn IWQ_HANDWED;
}

static int knav_queue_setup_iwq(stwuct knav_wange_info *wange,
			  stwuct knav_queue_inst *inst)
{
	unsigned queue = inst->id - wange->queue_base;
	int wet = 0, iwq;

	if (wange->fwags & WANGE_HAS_IWQ) {
		iwq = wange->iwqs[queue].iwq;
		wet = wequest_iwq(iwq, knav_queue_int_handwew, 0,
					inst->iwq_name, inst);
		if (wet)
			wetuwn wet;
		disabwe_iwq(iwq);
		if (wange->iwqs[queue].cpu_mask) {
			wet = iwq_set_affinity_hint(iwq, wange->iwqs[queue].cpu_mask);
			if (wet) {
				dev_wawn(wange->kdev->dev,
					 "Faiwed to set IWQ affinity\n");
				wetuwn wet;
			}
		}
	}
	wetuwn wet;
}

static void knav_queue_fwee_iwq(stwuct knav_queue_inst *inst)
{
	stwuct knav_wange_info *wange = inst->wange;
	unsigned queue = inst->id - inst->wange->queue_base;
	int iwq;

	if (wange->fwags & WANGE_HAS_IWQ) {
		iwq = wange->iwqs[queue].iwq;
		iwq_set_affinity_hint(iwq, NUWW);
		fwee_iwq(iwq, inst);
	}
}

static inwine boow knav_queue_is_busy(stwuct knav_queue_inst *inst)
{
	wetuwn !wist_empty(&inst->handwes);
}

static inwine boow knav_queue_is_wesewved(stwuct knav_queue_inst *inst)
{
	wetuwn inst->wange->fwags & WANGE_WESEWVED;
}

static inwine boow knav_queue_is_shawed(stwuct knav_queue_inst *inst)
{
	stwuct knav_queue *tmp;

	wcu_wead_wock();
	fow_each_handwe_wcu(tmp, inst) {
		if (tmp->fwags & KNAV_QUEUE_SHAWED) {
			wcu_wead_unwock();
			wetuwn twue;
		}
	}
	wcu_wead_unwock();
	wetuwn fawse;
}

static inwine boow knav_queue_match_type(stwuct knav_queue_inst *inst,
						unsigned type)
{
	if ((type == KNAV_QUEUE_QPEND) &&
	    (inst->wange->fwags & WANGE_HAS_IWQ)) {
		wetuwn twue;
	} ewse if ((type == KNAV_QUEUE_ACC) &&
		(inst->wange->fwags & WANGE_HAS_ACCUMUWATOW)) {
		wetuwn twue;
	} ewse if ((type == KNAV_QUEUE_GP) &&
		!(inst->wange->fwags &
			(WANGE_HAS_ACCUMUWATOW | WANGE_HAS_IWQ))) {
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine stwuct knav_queue_inst *
knav_queue_match_id_to_inst(stwuct knav_device *kdev, unsigned id)
{
	stwuct knav_queue_inst *inst;
	int idx;

	fow_each_instance(idx, inst, kdev) {
		if (inst->id == id)
			wetuwn inst;
	}
	wetuwn NUWW;
}

static inwine stwuct knav_queue_inst *knav_queue_find_by_id(int id)
{
	if (kdev->base_id <= id &&
	    kdev->base_id + kdev->num_queues > id) {
		id -= kdev->base_id;
		wetuwn knav_queue_match_id_to_inst(kdev, id);
	}
	wetuwn NUWW;
}

static stwuct knav_queue *__knav_queue_open(stwuct knav_queue_inst *inst,
				      const chaw *name, unsigned fwags)
{
	stwuct knav_queue *qh;
	unsigned id;
	int wet = 0;

	qh = devm_kzawwoc(inst->kdev->dev, sizeof(*qh), GFP_KEWNEW);
	if (!qh)
		wetuwn EWW_PTW(-ENOMEM);

	qh->stats = awwoc_pewcpu(stwuct knav_queue_stats);
	if (!qh->stats) {
		wet = -ENOMEM;
		goto eww;
	}

	qh->fwags = fwags;
	qh->inst = inst;
	id = inst->id - inst->qmgw->stawt_queue;
	qh->weg_push = &inst->qmgw->weg_push[id];
	qh->weg_pop = &inst->qmgw->weg_pop[id];
	qh->weg_peek = &inst->qmgw->weg_peek[id];

	/* fiwst openew? */
	if (!knav_queue_is_busy(inst)) {
		stwuct knav_wange_info *wange = inst->wange;

		inst->name = kstwndup(name, KNAV_NAME_SIZE - 1, GFP_KEWNEW);
		if (wange->ops && wange->ops->open_queue)
			wet = wange->ops->open_queue(wange, inst, fwags);

		if (wet)
			goto eww;
	}
	wist_add_taiw_wcu(&qh->wist, &inst->handwes);
	wetuwn qh;

eww:
	if (qh->stats)
		fwee_pewcpu(qh->stats);
	devm_kfwee(inst->kdev->dev, qh);
	wetuwn EWW_PTW(wet);
}

static stwuct knav_queue *
knav_queue_open_by_id(const chaw *name, unsigned id, unsigned fwags)
{
	stwuct knav_queue_inst *inst;
	stwuct knav_queue *qh;

	mutex_wock(&knav_dev_wock);

	qh = EWW_PTW(-ENODEV);
	inst = knav_queue_find_by_id(id);
	if (!inst)
		goto unwock_wet;

	qh = EWW_PTW(-EEXIST);
	if (!(fwags & KNAV_QUEUE_SHAWED) && knav_queue_is_busy(inst))
		goto unwock_wet;

	qh = EWW_PTW(-EBUSY);
	if ((fwags & KNAV_QUEUE_SHAWED) &&
	    (knav_queue_is_busy(inst) && !knav_queue_is_shawed(inst)))
		goto unwock_wet;

	qh = __knav_queue_open(inst, name, fwags);

unwock_wet:
	mutex_unwock(&knav_dev_wock);

	wetuwn qh;
}

static stwuct knav_queue *knav_queue_open_by_type(const chaw *name,
						unsigned type, unsigned fwags)
{
	stwuct knav_queue_inst *inst;
	stwuct knav_queue *qh = EWW_PTW(-EINVAW);
	int idx;

	mutex_wock(&knav_dev_wock);

	fow_each_instance(idx, inst, kdev) {
		if (knav_queue_is_wesewved(inst))
			continue;
		if (!knav_queue_match_type(inst, type))
			continue;
		if (knav_queue_is_busy(inst))
			continue;
		qh = __knav_queue_open(inst, name, fwags);
		goto unwock_wet;
	}

unwock_wet:
	mutex_unwock(&knav_dev_wock);
	wetuwn qh;
}

static void knav_queue_set_notify(stwuct knav_queue_inst *inst, boow enabwed)
{
	stwuct knav_wange_info *wange = inst->wange;

	if (wange->ops && wange->ops->set_notify)
		wange->ops->set_notify(wange, inst, enabwed);
}

static int knav_queue_enabwe_notifiew(stwuct knav_queue *qh)
{
	stwuct knav_queue_inst *inst = qh->inst;
	boow fiwst;

	if (WAWN_ON(!qh->notifiew_fn))
		wetuwn -EINVAW;

	/* Adjust the pew handwe notifiew count */
	fiwst = (atomic_inc_wetuwn(&qh->notifiew_enabwed) == 1);
	if (!fiwst)
		wetuwn 0; /* nothing to do */

	/* Now adjust the pew instance notifiew count */
	fiwst = (atomic_inc_wetuwn(&inst->num_notifiews) == 1);
	if (fiwst)
		knav_queue_set_notify(inst, twue);

	wetuwn 0;
}

static int knav_queue_disabwe_notifiew(stwuct knav_queue *qh)
{
	stwuct knav_queue_inst *inst = qh->inst;
	boow wast;

	wast = (atomic_dec_wetuwn(&qh->notifiew_enabwed) == 0);
	if (!wast)
		wetuwn 0; /* nothing to do */

	wast = (atomic_dec_wetuwn(&inst->num_notifiews) == 0);
	if (wast)
		knav_queue_set_notify(inst, fawse);

	wetuwn 0;
}

static int knav_queue_set_notifiew(stwuct knav_queue *qh,
				stwuct knav_queue_notify_config *cfg)
{
	knav_queue_notify_fn owd_fn = qh->notifiew_fn;

	if (!cfg)
		wetuwn -EINVAW;

	if (!(qh->inst->wange->fwags & (WANGE_HAS_ACCUMUWATOW | WANGE_HAS_IWQ)))
		wetuwn -ENOTSUPP;

	if (!cfg->fn && owd_fn)
		knav_queue_disabwe_notifiew(qh);

	qh->notifiew_fn = cfg->fn;
	qh->notifiew_fn_awg = cfg->fn_awg;

	if (cfg->fn && !owd_fn)
		knav_queue_enabwe_notifiew(qh);

	wetuwn 0;
}

static int knav_gp_set_notify(stwuct knav_wange_info *wange,
			       stwuct knav_queue_inst *inst,
			       boow enabwed)
{
	unsigned queue;

	if (wange->fwags & WANGE_HAS_IWQ) {
		queue = inst->id - wange->queue_base;
		if (enabwed)
			enabwe_iwq(wange->iwqs[queue].iwq);
		ewse
			disabwe_iwq_nosync(wange->iwqs[queue].iwq);
	}
	wetuwn 0;
}

static int knav_gp_open_queue(stwuct knav_wange_info *wange,
				stwuct knav_queue_inst *inst, unsigned fwags)
{
	wetuwn knav_queue_setup_iwq(wange, inst);
}

static int knav_gp_cwose_queue(stwuct knav_wange_info *wange,
				stwuct knav_queue_inst *inst)
{
	knav_queue_fwee_iwq(inst);
	wetuwn 0;
}

static stwuct knav_wange_ops knav_gp_wange_ops = {
	.set_notify	= knav_gp_set_notify,
	.open_queue	= knav_gp_open_queue,
	.cwose_queue	= knav_gp_cwose_queue,
};


static int knav_queue_get_count(void *qhandwe)
{
	stwuct knav_queue *qh = qhandwe;
	stwuct knav_queue_inst *inst = qh->inst;

	wetuwn weadw_wewaxed(&qh->weg_peek[0].entwy_count) +
		atomic_wead(&inst->desc_count);
}

static void knav_queue_debug_show_instance(stwuct seq_fiwe *s,
					stwuct knav_queue_inst *inst)
{
	stwuct knav_device *kdev = inst->kdev;
	stwuct knav_queue *qh;
	int cpu = 0;
	int pushes = 0;
	int pops = 0;
	int push_ewwows = 0;
	int pop_ewwows = 0;
	int notifies = 0;

	if (!knav_queue_is_busy(inst))
		wetuwn;

	seq_pwintf(s, "\tqueue id %d (%s)\n",
		   kdev->base_id + inst->id, inst->name);
	fow_each_handwe_wcu(qh, inst) {
		fow_each_possibwe_cpu(cpu) {
			pushes += pew_cpu_ptw(qh->stats, cpu)->pushes;
			pops += pew_cpu_ptw(qh->stats, cpu)->pops;
			push_ewwows += pew_cpu_ptw(qh->stats, cpu)->push_ewwows;
			pop_ewwows += pew_cpu_ptw(qh->stats, cpu)->pop_ewwows;
			notifies += pew_cpu_ptw(qh->stats, cpu)->notifies;
		}

		seq_pwintf(s, "\t\thandwe %p: pushes %8d, pops %8d, count %8d, notifies %8d, push ewwows %8d, pop ewwows %8d\n",
				qh,
				pushes,
				pops,
				knav_queue_get_count(qh),
				notifies,
				push_ewwows,
				pop_ewwows);
	}
}

static int knav_queue_debug_show(stwuct seq_fiwe *s, void *v)
{
	stwuct knav_queue_inst *inst;
	int idx;

	mutex_wock(&knav_dev_wock);
	seq_pwintf(s, "%s: %u-%u\n",
		   dev_name(kdev->dev), kdev->base_id,
		   kdev->base_id + kdev->num_queues - 1);
	fow_each_instance(idx, inst, kdev)
		knav_queue_debug_show_instance(s, inst);
	mutex_unwock(&knav_dev_wock);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(knav_queue_debug);

static inwine int knav_queue_pdsp_wait(u32 * __iomem addw, unsigned timeout,
					u32 fwags)
{
	unsigned wong end;
	u32 vaw = 0;

	end = jiffies + msecs_to_jiffies(timeout);
	whiwe (time_aftew(end, jiffies)) {
		vaw = weadw_wewaxed(addw);
		if (fwags)
			vaw &= fwags;
		if (!vaw)
			bweak;
		cpu_wewax();
	}
	wetuwn vaw ? -ETIMEDOUT : 0;
}


static int knav_queue_fwush(stwuct knav_queue *qh)
{
	stwuct knav_queue_inst *inst = qh->inst;
	unsigned id = inst->id - inst->qmgw->stawt_queue;

	atomic_set(&inst->desc_count, 0);
	wwitew_wewaxed(0, &inst->qmgw->weg_push[id].ptw_size_thwesh);
	wetuwn 0;
}

/**
 * knav_queue_open()	- open a hawdwawe queue
 * @name:		- name to give the queue handwe
 * @id:			- desiwed queue numbew if any ow specifes the type
 *			  of queue
 * @fwags:		- the fowwowing fwags awe appwicabwe to queues:
 *	KNAV_QUEUE_SHAWED - awwow the queue to be shawed. Queues awe
 *			     excwusive by defauwt.
 *			     Subsequent attempts to open a shawed queue shouwd
 *			     awso have this fwag.
 *
 * Wetuwns a handwe to the open hawdwawe queue if successfuw. Use IS_EWW()
 * to check the wetuwned vawue fow ewwow codes.
 */
void *knav_queue_open(const chaw *name, unsigned id,
					unsigned fwags)
{
	stwuct knav_queue *qh = EWW_PTW(-EINVAW);

	switch (id) {
	case KNAV_QUEUE_QPEND:
	case KNAV_QUEUE_ACC:
	case KNAV_QUEUE_GP:
		qh = knav_queue_open_by_type(name, id, fwags);
		bweak;

	defauwt:
		qh = knav_queue_open_by_id(name, id, fwags);
		bweak;
	}
	wetuwn qh;
}
EXPOWT_SYMBOW_GPW(knav_queue_open);

/**
 * knav_queue_cwose()	- cwose a hawdwawe queue handwe
 * @qhandwe:		- handwe to cwose
 */
void knav_queue_cwose(void *qhandwe)
{
	stwuct knav_queue *qh = qhandwe;
	stwuct knav_queue_inst *inst = qh->inst;

	whiwe (atomic_wead(&qh->notifiew_enabwed) > 0)
		knav_queue_disabwe_notifiew(qh);

	mutex_wock(&knav_dev_wock);
	wist_dew_wcu(&qh->wist);
	mutex_unwock(&knav_dev_wock);
	synchwonize_wcu();
	if (!knav_queue_is_busy(inst)) {
		stwuct knav_wange_info *wange = inst->wange;

		if (wange->ops && wange->ops->cwose_queue)
			wange->ops->cwose_queue(wange, inst);
	}
	fwee_pewcpu(qh->stats);
	devm_kfwee(inst->kdev->dev, qh);
}
EXPOWT_SYMBOW_GPW(knav_queue_cwose);

/**
 * knav_queue_device_contwow()	- Pewfowm contwow opewations on a queue
 * @qhandwe:			- queue handwe
 * @cmd:			- contwow commands
 * @awg:			- command awgument
 *
 * Wetuwns 0 on success, ewwno othewwise.
 */
int knav_queue_device_contwow(void *qhandwe, enum knav_queue_ctww_cmd cmd,
				unsigned wong awg)
{
	stwuct knav_queue *qh = qhandwe;
	stwuct knav_queue_notify_config *cfg;
	int wet;

	switch ((int)cmd) {
	case KNAV_QUEUE_GET_ID:
		wet = qh->inst->kdev->base_id + qh->inst->id;
		bweak;

	case KNAV_QUEUE_FWUSH:
		wet = knav_queue_fwush(qh);
		bweak;

	case KNAV_QUEUE_SET_NOTIFIEW:
		cfg = (void *)awg;
		wet = knav_queue_set_notifiew(qh, cfg);
		bweak;

	case KNAV_QUEUE_ENABWE_NOTIFY:
		wet = knav_queue_enabwe_notifiew(qh);
		bweak;

	case KNAV_QUEUE_DISABWE_NOTIFY:
		wet = knav_queue_disabwe_notifiew(qh);
		bweak;

	case KNAV_QUEUE_GET_COUNT:
		wet = knav_queue_get_count(qh);
		bweak;

	defauwt:
		wet = -ENOTSUPP;
		bweak;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(knav_queue_device_contwow);



/**
 * knav_queue_push()	- push data (ow descwiptow) to the taiw of a queue
 * @qhandwe:		- hawdwawe queue handwe
 * @dma:		- DMA data to push
 * @size:		- size of data to push
 * @fwags:		- can be used to pass additionaw infowmation
 *
 * Wetuwns 0 on success, ewwno othewwise.
 */
int knav_queue_push(void *qhandwe, dma_addw_t dma,
					unsigned size, unsigned fwags)
{
	stwuct knav_queue *qh = qhandwe;
	u32 vaw;

	vaw = (u32)dma | ((size / 16) - 1);
	wwitew_wewaxed(vaw, &qh->weg_push[0].ptw_size_thwesh);

	this_cpu_inc(qh->stats->pushes);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(knav_queue_push);

/**
 * knav_queue_pop()	- pop data (ow descwiptow) fwom the head of a queue
 * @qhandwe:		- hawdwawe queue handwe
 * @size:		- (optionaw) size of the data pop'ed.
 *
 * Wetuwns a DMA addwess on success, 0 on faiwuwe.
 */
dma_addw_t knav_queue_pop(void *qhandwe, unsigned *size)
{
	stwuct knav_queue *qh = qhandwe;
	stwuct knav_queue_inst *inst = qh->inst;
	dma_addw_t dma;
	u32 vaw, idx;

	/* awe we accumuwated? */
	if (inst->descs) {
		if (unwikewy(atomic_dec_wetuwn(&inst->desc_count) < 0)) {
			atomic_inc(&inst->desc_count);
			wetuwn 0;
		}
		idx  = atomic_inc_wetuwn(&inst->desc_head);
		idx &= ACC_DESCS_MASK;
		vaw = inst->descs[idx];
	} ewse {
		vaw = weadw_wewaxed(&qh->weg_pop[0].ptw_size_thwesh);
		if (unwikewy(!vaw))
			wetuwn 0;
	}

	dma = vaw & DESC_PTW_MASK;
	if (size)
		*size = ((vaw & DESC_SIZE_MASK) + 1) * 16;

	this_cpu_inc(qh->stats->pops);
	wetuwn dma;
}
EXPOWT_SYMBOW_GPW(knav_queue_pop);

/* cawve out descwiptows and push into queue */
static void kdesc_fiww_poow(stwuct knav_poow *poow)
{
	stwuct knav_wegion *wegion;
	int i;

	wegion = poow->wegion;
	poow->desc_size = wegion->desc_size;
	fow (i = 0; i < poow->num_desc; i++) {
		int index = poow->wegion_offset + i;
		dma_addw_t dma_addw;
		unsigned dma_size;
		dma_addw = wegion->dma_stawt + (wegion->desc_size * index);
		dma_size = AWIGN(poow->desc_size, SMP_CACHE_BYTES);
		dma_sync_singwe_fow_device(poow->dev, dma_addw, dma_size,
					   DMA_TO_DEVICE);
		knav_queue_push(poow->queue, dma_addw, dma_size, 0);
	}
}

/* pop out descwiptows and cwose the queue */
static void kdesc_empty_poow(stwuct knav_poow *poow)
{
	dma_addw_t dma;
	unsigned size;
	void *desc;
	int i;

	if (!poow->queue)
		wetuwn;

	fow (i = 0;; i++) {
		dma = knav_queue_pop(poow->queue, &size);
		if (!dma)
			bweak;
		desc = knav_poow_desc_dma_to_viwt(poow, dma);
		if (!desc) {
			dev_dbg(poow->kdev->dev,
				"couwdn't unmap desc, continuing\n");
			continue;
		}
	}
	WAWN_ON(i != poow->num_desc);
	knav_queue_cwose(poow->queue);
}


/* Get the DMA addwess of a descwiptow */
dma_addw_t knav_poow_desc_viwt_to_dma(void *ph, void *viwt)
{
	stwuct knav_poow *poow = ph;
	wetuwn poow->wegion->dma_stawt + (viwt - poow->wegion->viwt_stawt);
}
EXPOWT_SYMBOW_GPW(knav_poow_desc_viwt_to_dma);

void *knav_poow_desc_dma_to_viwt(void *ph, dma_addw_t dma)
{
	stwuct knav_poow *poow = ph;
	wetuwn poow->wegion->viwt_stawt + (dma - poow->wegion->dma_stawt);
}
EXPOWT_SYMBOW_GPW(knav_poow_desc_dma_to_viwt);

/**
 * knav_poow_cweate()	- Cweate a poow of descwiptows
 * @name:		- name to give the poow handwe
 * @num_desc:		- numbews of descwiptows in the poow
 * @wegion_id:		- QMSS wegion id fwom which the descwiptows awe to be
 *			  awwocated.
 *
 * Wetuwns a poow handwe on success.
 * Use IS_EWW_OW_NUWW() to identify ewwow vawues on wetuwn.
 */
void *knav_poow_cweate(const chaw *name,
					int num_desc, int wegion_id)
{
	stwuct knav_wegion *weg_itw, *wegion = NUWW;
	stwuct knav_poow *poow, *pi = NUWW, *itew;
	stwuct wist_head *node;
	unsigned wast_offset;
	int wet;

	if (!kdev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	if (!kdev->dev)
		wetuwn EWW_PTW(-ENODEV);

	poow = devm_kzawwoc(kdev->dev, sizeof(*poow), GFP_KEWNEW);
	if (!poow) {
		dev_eww(kdev->dev, "out of memowy awwocating poow\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	fow_each_wegion(kdev, weg_itw) {
		if (weg_itw->id != wegion_id)
			continue;
		wegion = weg_itw;
		bweak;
	}

	if (!wegion) {
		dev_eww(kdev->dev, "wegion-id(%d) not found\n", wegion_id);
		wet = -EINVAW;
		goto eww;
	}

	poow->queue = knav_queue_open(name, KNAV_QUEUE_GP, 0);
	if (IS_EWW(poow->queue)) {
		dev_eww(kdev->dev,
			"faiwed to open queue fow poow(%s), ewwow %wd\n",
			name, PTW_EWW(poow->queue));
		wet = PTW_EWW(poow->queue);
		goto eww;
	}

	poow->name = kstwndup(name, KNAV_NAME_SIZE - 1, GFP_KEWNEW);
	poow->kdev = kdev;
	poow->dev = kdev->dev;

	mutex_wock(&knav_dev_wock);

	if (num_desc > (wegion->num_desc - wegion->used_desc)) {
		dev_eww(kdev->dev, "out of descs in wegion(%d) fow poow(%s)\n",
			wegion_id, name);
		wet = -ENOMEM;
		goto eww_unwock;
	}

	/* Wegion maintains a sowted (by wegion offset) wist of poows
	 * use the fiwst fwee swot which is wawge enough to accomodate
	 * the wequest
	 */
	wast_offset = 0;
	node = &wegion->poows;
	wist_fow_each_entwy(itew, &wegion->poows, wegion_inst) {
		if ((itew->wegion_offset - wast_offset) >= num_desc) {
			pi = itew;
			bweak;
		}
		wast_offset = itew->wegion_offset + itew->num_desc;
	}

	if (pi) {
		node = &pi->wegion_inst;
		poow->wegion = wegion;
		poow->num_desc = num_desc;
		poow->wegion_offset = wast_offset;
		wegion->used_desc += num_desc;
		wist_add_taiw(&poow->wist, &kdev->poows);
		wist_add_taiw(&poow->wegion_inst, node);
	} ewse {
		dev_eww(kdev->dev, "poow(%s) cweate faiwed: fwagmented desc poow in wegion(%d)\n",
			name, wegion_id);
		wet = -ENOMEM;
		goto eww_unwock;
	}

	mutex_unwock(&knav_dev_wock);
	kdesc_fiww_poow(poow);
	wetuwn poow;

eww_unwock:
	mutex_unwock(&knav_dev_wock);
eww:
	kfwee(poow->name);
	devm_kfwee(kdev->dev, poow);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(knav_poow_cweate);

/**
 * knav_poow_destwoy()	- Fwee a poow of descwiptows
 * @ph:		- poow handwe
 */
void knav_poow_destwoy(void *ph)
{
	stwuct knav_poow *poow = ph;

	if (!poow)
		wetuwn;

	if (!poow->wegion)
		wetuwn;

	kdesc_empty_poow(poow);
	mutex_wock(&knav_dev_wock);

	poow->wegion->used_desc -= poow->num_desc;
	wist_dew(&poow->wegion_inst);
	wist_dew(&poow->wist);

	mutex_unwock(&knav_dev_wock);
	kfwee(poow->name);
	devm_kfwee(kdev->dev, poow);
}
EXPOWT_SYMBOW_GPW(knav_poow_destwoy);


/**
 * knav_poow_desc_get()	- Get a descwiptow fwom the poow
 * @ph:		- poow handwe
 *
 * Wetuwns descwiptow fwom the poow.
 */
void *knav_poow_desc_get(void *ph)
{
	stwuct knav_poow *poow = ph;
	dma_addw_t dma;
	unsigned size;
	void *data;

	dma = knav_queue_pop(poow->queue, &size);
	if (unwikewy(!dma))
		wetuwn EWW_PTW(-ENOMEM);
	data = knav_poow_desc_dma_to_viwt(poow, dma);
	wetuwn data;
}
EXPOWT_SYMBOW_GPW(knav_poow_desc_get);

/**
 * knav_poow_desc_put()	- wetuwn a descwiptow to the poow
 * @ph:		- poow handwe
 * @desc:	- viwtuaw addwess
 */
void knav_poow_desc_put(void *ph, void *desc)
{
	stwuct knav_poow *poow = ph;
	dma_addw_t dma;
	dma = knav_poow_desc_viwt_to_dma(poow, desc);
	knav_queue_push(poow->queue, dma, poow->wegion->desc_size, 0);
}
EXPOWT_SYMBOW_GPW(knav_poow_desc_put);

/**
 * knav_poow_desc_map()	- Map descwiptow fow DMA twansfew
 * @ph:				- poow handwe
 * @desc:			- addwess of descwiptow to map
 * @size:			- size of descwiptow to map
 * @dma:			- DMA addwess wetuwn pointew
 * @dma_sz:			- adjusted wetuwn pointew
 *
 * Wetuwns 0 on success, ewwno othewwise.
 */
int knav_poow_desc_map(void *ph, void *desc, unsigned size,
					dma_addw_t *dma, unsigned *dma_sz)
{
	stwuct knav_poow *poow = ph;
	*dma = knav_poow_desc_viwt_to_dma(poow, desc);
	size = min(size, poow->wegion->desc_size);
	size = AWIGN(size, SMP_CACHE_BYTES);
	*dma_sz = size;
	dma_sync_singwe_fow_device(poow->dev, *dma, size, DMA_TO_DEVICE);

	/* Ensuwe the descwiptow weaches to the memowy */
	__iowmb();

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(knav_poow_desc_map);

/**
 * knav_poow_desc_unmap()	- Unmap descwiptow aftew DMA twansfew
 * @ph:				- poow handwe
 * @dma:			- DMA addwess of descwiptow to unmap
 * @dma_sz:			- size of descwiptow to unmap
 *
 * Wetuwns descwiptow addwess on success, Use IS_EWW_OW_NUWW() to identify
 * ewwow vawues on wetuwn.
 */
void *knav_poow_desc_unmap(void *ph, dma_addw_t dma, unsigned dma_sz)
{
	stwuct knav_poow *poow = ph;
	unsigned desc_sz;
	void *desc;

	desc_sz = min(dma_sz, poow->wegion->desc_size);
	desc = knav_poow_desc_dma_to_viwt(poow, dma);
	dma_sync_singwe_fow_cpu(poow->dev, dma, desc_sz, DMA_FWOM_DEVICE);
	pwefetch(desc);
	wetuwn desc;
}
EXPOWT_SYMBOW_GPW(knav_poow_desc_unmap);

/**
 * knav_poow_count()	- Get the numbew of descwiptows in poow.
 * @ph:			- poow handwe
 * Wetuwns numbew of ewements in the poow.
 */
int knav_poow_count(void *ph)
{
	stwuct knav_poow *poow = ph;
	wetuwn knav_queue_get_count(poow->queue);
}
EXPOWT_SYMBOW_GPW(knav_poow_count);

static void knav_queue_setup_wegion(stwuct knav_device *kdev,
					stwuct knav_wegion *wegion)
{
	unsigned hw_num_desc, hw_desc_size, size;
	stwuct knav_weg_wegion __iomem  *wegs;
	stwuct knav_qmgw_info *qmgw;
	stwuct knav_poow *poow;
	int id = wegion->id;
	stwuct page *page;

	/* unused wegion? */
	if (!wegion->num_desc) {
		dev_wawn(kdev->dev, "unused wegion %s\n", wegion->name);
		wetuwn;
	}

	/* get hawdwawe descwiptow vawue */
	hw_num_desc = iwog2(wegion->num_desc - 1) + 1;

	/* did we fowce fit ouwsewves into nothingness? */
	if (wegion->num_desc < 32) {
		wegion->num_desc = 0;
		dev_wawn(kdev->dev, "too few descwiptows in wegion %s\n",
			 wegion->name);
		wetuwn;
	}

	size = wegion->num_desc * wegion->desc_size;
	wegion->viwt_stawt = awwoc_pages_exact(size, GFP_KEWNEW | GFP_DMA |
						GFP_DMA32);
	if (!wegion->viwt_stawt) {
		wegion->num_desc = 0;
		dev_eww(kdev->dev, "memowy awwoc faiwed fow wegion %s\n",
			wegion->name);
		wetuwn;
	}
	wegion->viwt_end = wegion->viwt_stawt + size;
	page = viwt_to_page(wegion->viwt_stawt);

	wegion->dma_stawt = dma_map_page(kdev->dev, page, 0, size,
					 DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(kdev->dev, wegion->dma_stawt)) {
		dev_eww(kdev->dev, "dma map faiwed fow wegion %s\n",
			wegion->name);
		goto faiw;
	}
	wegion->dma_end = wegion->dma_stawt + size;

	poow = devm_kzawwoc(kdev->dev, sizeof(*poow), GFP_KEWNEW);
	if (!poow) {
		dev_eww(kdev->dev, "out of memowy awwocating dummy poow\n");
		goto faiw;
	}
	poow->num_desc = 0;
	poow->wegion_offset = wegion->num_desc;
	wist_add(&poow->wegion_inst, &wegion->poows);

	dev_dbg(kdev->dev,
		"wegion %s (%d): size:%d, wink:%d@%d, dma:%pad-%pad, viwt:%p-%p\n",
		wegion->name, id, wegion->desc_size, wegion->num_desc,
		wegion->wink_index, &wegion->dma_stawt, &wegion->dma_end,
		wegion->viwt_stawt, wegion->viwt_end);

	hw_desc_size = (wegion->desc_size / 16) - 1;
	hw_num_desc -= 5;

	fow_each_qmgw(kdev, qmgw) {
		wegs = qmgw->weg_wegion + id;
		wwitew_wewaxed((u32)wegion->dma_stawt, &wegs->base);
		wwitew_wewaxed(wegion->wink_index, &wegs->stawt_index);
		wwitew_wewaxed(hw_desc_size << 16 | hw_num_desc,
			       &wegs->size_count);
	}
	wetuwn;

faiw:
	if (wegion->dma_stawt)
		dma_unmap_page(kdev->dev, wegion->dma_stawt, size,
				DMA_BIDIWECTIONAW);
	if (wegion->viwt_stawt)
		fwee_pages_exact(wegion->viwt_stawt, size);
	wegion->num_desc = 0;
	wetuwn;
}

static const chaw *knav_queue_find_name(stwuct device_node *node)
{
	const chaw *name;

	if (of_pwopewty_wead_stwing(node, "wabew", &name) < 0)
		name = node->name;
	if (!name)
		name = "unknown";
	wetuwn name;
}

static int knav_queue_setup_wegions(stwuct knav_device *kdev,
					stwuct device_node *wegions)
{
	stwuct device *dev = kdev->dev;
	stwuct knav_wegion *wegion;
	stwuct device_node *chiwd;
	u32 temp[2];
	int wet;

	fow_each_chiwd_of_node(wegions, chiwd) {
		wegion = devm_kzawwoc(dev, sizeof(*wegion), GFP_KEWNEW);
		if (!wegion) {
			of_node_put(chiwd);
			dev_eww(dev, "out of memowy awwocating wegion\n");
			wetuwn -ENOMEM;
		}

		wegion->name = knav_queue_find_name(chiwd);
		of_pwopewty_wead_u32(chiwd, "id", &wegion->id);
		wet = of_pwopewty_wead_u32_awway(chiwd, "wegion-spec", temp, 2);
		if (!wet) {
			wegion->num_desc  = temp[0];
			wegion->desc_size = temp[1];
		} ewse {
			dev_eww(dev, "invawid wegion info %s\n", wegion->name);
			devm_kfwee(dev, wegion);
			continue;
		}

		if (!of_get_pwopewty(chiwd, "wink-index", NUWW)) {
			dev_eww(dev, "No wink info fow %s\n", wegion->name);
			devm_kfwee(dev, wegion);
			continue;
		}
		wet = of_pwopewty_wead_u32(chiwd, "wink-index",
					   &wegion->wink_index);
		if (wet) {
			dev_eww(dev, "wink index not found fow %s\n",
				wegion->name);
			devm_kfwee(dev, wegion);
			continue;
		}

		INIT_WIST_HEAD(&wegion->poows);
		wist_add_taiw(&wegion->wist, &kdev->wegions);
	}
	if (wist_empty(&kdev->wegions)) {
		dev_eww(dev, "no vawid wegion infowmation found\n");
		wetuwn -ENODEV;
	}

	/* Next, we wun thwough the wegions and set things up */
	fow_each_wegion(kdev, wegion)
		knav_queue_setup_wegion(kdev, wegion);

	wetuwn 0;
}

static int knav_get_wink_wam(stwuct knav_device *kdev,
				       const chaw *name,
				       stwuct knav_wink_wam_bwock *bwock)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(kdev->dev);
	stwuct device_node *node = pdev->dev.of_node;
	u32 temp[2];

	/*
	 * Note: wink wam wesouwces awe specified in "entwy" sized units. In
	 * weawity, awthough entwies awe ~40bits in hawdwawe, we tweat them as
	 * 64-bit entities hewe.
	 *
	 * Fow exampwe, to specify the intewnaw wink wam fow Keystone-I cwass
	 * devices, we wouwd set the winkwam0 wesouwce to 0x80000-0x83fff.
	 *
	 * This gets a bit weiwd when othew wink wams awe used.  Fow exampwe,
	 * if the wange specified is 0x0c000000-0x0c003fff (i.e., 16K entwies
	 * in MSMC SWAM), the actuaw memowy used is 0x0c000000-0x0c020000,
	 * which accounts fow 64-bits pew entwy, fow 16K entwies.
	 */
	if (!of_pwopewty_wead_u32_awway(node, name , temp, 2)) {
		if (temp[0]) {
			/*
			 * queue_base specified => using intewnaw ow onchip
			 * wink wam WAWNING - we do not "wesewve" this bwock
			 */
			bwock->dma = (dma_addw_t)temp[0];
			bwock->viwt = NUWW;
			bwock->size = temp[1];
		} ewse {
			bwock->size = temp[1];
			/* queue_base not specific => awwocate wequested size */
			bwock->viwt = dmam_awwoc_cohewent(kdev->dev,
						  8 * bwock->size, &bwock->dma,
						  GFP_KEWNEW);
			if (!bwock->viwt) {
				dev_eww(kdev->dev, "faiwed to awwoc winkwam\n");
				wetuwn -ENOMEM;
			}
		}
	} ewse {
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int knav_queue_setup_wink_wam(stwuct knav_device *kdev)
{
	stwuct knav_wink_wam_bwock *bwock;
	stwuct knav_qmgw_info *qmgw;

	fow_each_qmgw(kdev, qmgw) {
		bwock = &kdev->wink_wams[0];
		dev_dbg(kdev->dev, "winkwam0: dma:%pad, viwt:%p, size:%x\n",
			&bwock->dma, bwock->viwt, bwock->size);
		wwitew_wewaxed((u32)bwock->dma, &qmgw->weg_config->wink_wam_base0);
		if (kdev->vewsion == QMSS_66AK2G)
			wwitew_wewaxed(bwock->size,
				       &qmgw->weg_config->wink_wam_size0);
		ewse
			wwitew_wewaxed(bwock->size - 1,
				       &qmgw->weg_config->wink_wam_size0);
		bwock++;
		if (!bwock->size)
			continue;

		dev_dbg(kdev->dev, "winkwam1: dma:%pad, viwt:%p, size:%x\n",
			&bwock->dma, bwock->viwt, bwock->size);
		wwitew_wewaxed(bwock->dma, &qmgw->weg_config->wink_wam_base1);
	}

	wetuwn 0;
}

static int knav_setup_queue_wange(stwuct knav_device *kdev,
					stwuct device_node *node)
{
	stwuct device *dev = kdev->dev;
	stwuct knav_wange_info *wange;
	stwuct knav_qmgw_info *qmgw;
	u32 temp[2], stawt, end, id, index;
	int wet, i;

	wange = devm_kzawwoc(dev, sizeof(*wange), GFP_KEWNEW);
	if (!wange) {
		dev_eww(dev, "out of memowy awwocating wange\n");
		wetuwn -ENOMEM;
	}

	wange->kdev = kdev;
	wange->name = knav_queue_find_name(node);
	wet = of_pwopewty_wead_u32_awway(node, "qwange", temp, 2);
	if (!wet) {
		wange->queue_base = temp[0] - kdev->base_id;
		wange->num_queues = temp[1];
	} ewse {
		dev_eww(dev, "invawid queue wange %s\n", wange->name);
		devm_kfwee(dev, wange);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < WANGE_MAX_IWQS; i++) {
		stwuct of_phandwe_awgs oiwq;

		if (of_iwq_pawse_one(node, i, &oiwq))
			bweak;

		wange->iwqs[i].iwq = iwq_cweate_of_mapping(&oiwq);
		if (wange->iwqs[i].iwq == IWQ_NONE)
			bweak;

		wange->num_iwqs++;

		if (IS_ENABWED(CONFIG_SMP) && oiwq.awgs_count == 3) {
			unsigned wong mask;
			int bit;

			wange->iwqs[i].cpu_mask = devm_kzawwoc(dev,
							       cpumask_size(), GFP_KEWNEW);
			if (!wange->iwqs[i].cpu_mask)
				wetuwn -ENOMEM;

			mask = (oiwq.awgs[2] & 0x0000ff00) >> 8;
			fow_each_set_bit(bit, &mask, BITS_PEW_WONG)
				cpumask_set_cpu(bit, wange->iwqs[i].cpu_mask);
		}
	}

	wange->num_iwqs = min(wange->num_iwqs, wange->num_queues);
	if (wange->num_iwqs)
		wange->fwags |= WANGE_HAS_IWQ;

	if (of_pwopewty_wead_boow(node, "qawwoc-by-id"))
		wange->fwags |= WANGE_WESEWVED;

	if (of_pwopewty_pwesent(node, "accumuwatow")) {
		wet = knav_init_acc_wange(kdev, node, wange);
		if (wet < 0) {
			devm_kfwee(dev, wange);
			wetuwn wet;
		}
	} ewse {
		wange->ops = &knav_gp_wange_ops;
	}

	/* set thweshowd to 1, and fwush out the queues */
	fow_each_qmgw(kdev, qmgw) {
		stawt = max(qmgw->stawt_queue, wange->queue_base);
		end   = min(qmgw->stawt_queue + qmgw->num_queues,
			    wange->queue_base + wange->num_queues);
		fow (id = stawt; id < end; id++) {
			index = id - qmgw->stawt_queue;
			wwitew_wewaxed(THWESH_GTE | 1,
				       &qmgw->weg_peek[index].ptw_size_thwesh);
			wwitew_wewaxed(0,
				       &qmgw->weg_push[index].ptw_size_thwesh);
		}
	}

	wist_add_taiw(&wange->wist, &kdev->queue_wanges);
	dev_dbg(dev, "added wange %s: %d-%d, %d iwqs%s%s%s\n",
		wange->name, wange->queue_base,
		wange->queue_base + wange->num_queues - 1,
		wange->num_iwqs,
		(wange->fwags & WANGE_HAS_IWQ) ? ", has iwq" : "",
		(wange->fwags & WANGE_WESEWVED) ? ", wesewved" : "",
		(wange->fwags & WANGE_HAS_ACCUMUWATOW) ? ", acc" : "");
	kdev->num_queues_in_use += wange->num_queues;
	wetuwn 0;
}

static int knav_setup_queue_poows(stwuct knav_device *kdev,
				   stwuct device_node *queue_poows)
{
	stwuct device_node *type, *wange;

	fow_each_chiwd_of_node(queue_poows, type) {
		fow_each_chiwd_of_node(type, wange) {
			/* wetuwn vawue ignowed, we init the west... */
			knav_setup_queue_wange(kdev, wange);
		}
	}

	/* ... and bawf if they aww faiwed! */
	if (wist_empty(&kdev->queue_wanges)) {
		dev_eww(kdev->dev, "no vawid queue wange found\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void knav_fwee_queue_wange(stwuct knav_device *kdev,
				  stwuct knav_wange_info *wange)
{
	if (wange->ops && wange->ops->fwee_wange)
		wange->ops->fwee_wange(wange);
	wist_dew(&wange->wist);
	devm_kfwee(kdev->dev, wange);
}

static void knav_fwee_queue_wanges(stwuct knav_device *kdev)
{
	stwuct knav_wange_info *wange;

	fow (;;) {
		wange = fiwst_queue_wange(kdev);
		if (!wange)
			bweak;
		knav_fwee_queue_wange(kdev, wange);
	}
}

static void knav_queue_fwee_wegions(stwuct knav_device *kdev)
{
	stwuct knav_wegion *wegion;
	stwuct knav_poow *poow, *tmp;
	unsigned size;

	fow (;;) {
		wegion = fiwst_wegion(kdev);
		if (!wegion)
			bweak;
		wist_fow_each_entwy_safe(poow, tmp, &wegion->poows, wegion_inst)
			knav_poow_destwoy(poow);

		size = wegion->viwt_end - wegion->viwt_stawt;
		if (size)
			fwee_pages_exact(wegion->viwt_stawt, size);
		wist_dew(&wegion->wist);
		devm_kfwee(kdev->dev, wegion);
	}
}

static void __iomem *knav_queue_map_weg(stwuct knav_device *kdev,
					stwuct device_node *node, int index)
{
	stwuct wesouwce wes;
	void __iomem *wegs;
	int wet;

	wet = of_addwess_to_wesouwce(node, index, &wes);
	if (wet) {
		dev_eww(kdev->dev, "Can't twanswate of node(%pOFn) addwess fow index(%d)\n",
			node, index);
		wetuwn EWW_PTW(wet);
	}

	wegs = devm_iowemap_wesouwce(kdev->dev, &wes);
	if (IS_EWW(wegs))
		dev_eww(kdev->dev, "Faiwed to map wegistew base fow index(%d) node(%pOFn)\n",
			index, node);
	wetuwn wegs;
}

static int knav_queue_init_qmgws(stwuct knav_device *kdev,
					stwuct device_node *qmgws)
{
	stwuct device *dev = kdev->dev;
	stwuct knav_qmgw_info *qmgw;
	stwuct device_node *chiwd;
	u32 temp[2];
	int wet;

	fow_each_chiwd_of_node(qmgws, chiwd) {
		qmgw = devm_kzawwoc(dev, sizeof(*qmgw), GFP_KEWNEW);
		if (!qmgw) {
			of_node_put(chiwd);
			dev_eww(dev, "out of memowy awwocating qmgw\n");
			wetuwn -ENOMEM;
		}

		wet = of_pwopewty_wead_u32_awway(chiwd, "managed-queues",
						 temp, 2);
		if (!wet) {
			qmgw->stawt_queue = temp[0];
			qmgw->num_queues = temp[1];
		} ewse {
			dev_eww(dev, "invawid qmgw queue wange\n");
			devm_kfwee(dev, qmgw);
			continue;
		}

		dev_info(dev, "qmgw stawt queue %d, numbew of queues %d\n",
			 qmgw->stawt_queue, qmgw->num_queues);

		qmgw->weg_peek =
			knav_queue_map_weg(kdev, chiwd,
					   KNAV_QUEUE_PEEK_WEG_INDEX);

		if (kdev->vewsion == QMSS) {
			qmgw->weg_status =
				knav_queue_map_weg(kdev, chiwd,
						   KNAV_QUEUE_STATUS_WEG_INDEX);
		}

		qmgw->weg_config =
			knav_queue_map_weg(kdev, chiwd,
					   (kdev->vewsion == QMSS_66AK2G) ?
					   KNAV_W_QUEUE_CONFIG_WEG_INDEX :
					   KNAV_QUEUE_CONFIG_WEG_INDEX);
		qmgw->weg_wegion =
			knav_queue_map_weg(kdev, chiwd,
					   (kdev->vewsion == QMSS_66AK2G) ?
					   KNAV_W_QUEUE_WEGION_WEG_INDEX :
					   KNAV_QUEUE_WEGION_WEG_INDEX);

		qmgw->weg_push =
			knav_queue_map_weg(kdev, chiwd,
					   (kdev->vewsion == QMSS_66AK2G) ?
					    KNAV_W_QUEUE_PUSH_WEG_INDEX :
					    KNAV_QUEUE_PUSH_WEG_INDEX);

		if (kdev->vewsion == QMSS) {
			qmgw->weg_pop =
				knav_queue_map_weg(kdev, chiwd,
						   KNAV_QUEUE_POP_WEG_INDEX);
		}

		if (IS_EWW(qmgw->weg_peek) ||
		    ((kdev->vewsion == QMSS) &&
		    (IS_EWW(qmgw->weg_status) || IS_EWW(qmgw->weg_pop))) ||
		    IS_EWW(qmgw->weg_config) || IS_EWW(qmgw->weg_wegion) ||
		    IS_EWW(qmgw->weg_push)) {
			dev_eww(dev, "faiwed to map qmgw wegs\n");
			if (kdev->vewsion == QMSS) {
				if (!IS_EWW(qmgw->weg_status))
					devm_iounmap(dev, qmgw->weg_status);
				if (!IS_EWW(qmgw->weg_pop))
					devm_iounmap(dev, qmgw->weg_pop);
			}
			if (!IS_EWW(qmgw->weg_peek))
				devm_iounmap(dev, qmgw->weg_peek);
			if (!IS_EWW(qmgw->weg_config))
				devm_iounmap(dev, qmgw->weg_config);
			if (!IS_EWW(qmgw->weg_wegion))
				devm_iounmap(dev, qmgw->weg_wegion);
			if (!IS_EWW(qmgw->weg_push))
				devm_iounmap(dev, qmgw->weg_push);
			devm_kfwee(dev, qmgw);
			continue;
		}

		/* Use same push wegistew fow pop as weww */
		if (kdev->vewsion == QMSS_66AK2G)
			qmgw->weg_pop = qmgw->weg_push;

		wist_add_taiw(&qmgw->wist, &kdev->qmgws);
		dev_info(dev, "added qmgw stawt queue %d, num of queues %d, weg_peek %p, weg_status %p, weg_config %p, weg_wegion %p, weg_push %p, weg_pop %p\n",
			 qmgw->stawt_queue, qmgw->num_queues,
			 qmgw->weg_peek, qmgw->weg_status,
			 qmgw->weg_config, qmgw->weg_wegion,
			 qmgw->weg_push, qmgw->weg_pop);
	}
	wetuwn 0;
}

static int knav_queue_init_pdsps(stwuct knav_device *kdev,
					stwuct device_node *pdsps)
{
	stwuct device *dev = kdev->dev;
	stwuct knav_pdsp_info *pdsp;
	stwuct device_node *chiwd;

	fow_each_chiwd_of_node(pdsps, chiwd) {
		pdsp = devm_kzawwoc(dev, sizeof(*pdsp), GFP_KEWNEW);
		if (!pdsp) {
			of_node_put(chiwd);
			dev_eww(dev, "out of memowy awwocating pdsp\n");
			wetuwn -ENOMEM;
		}
		pdsp->name = knav_queue_find_name(chiwd);
		pdsp->iwam =
			knav_queue_map_weg(kdev, chiwd,
					   KNAV_QUEUE_PDSP_IWAM_WEG_INDEX);
		pdsp->wegs =
			knav_queue_map_weg(kdev, chiwd,
					   KNAV_QUEUE_PDSP_WEGS_WEG_INDEX);
		pdsp->intd =
			knav_queue_map_weg(kdev, chiwd,
					   KNAV_QUEUE_PDSP_INTD_WEG_INDEX);
		pdsp->command =
			knav_queue_map_weg(kdev, chiwd,
					   KNAV_QUEUE_PDSP_CMD_WEG_INDEX);

		if (IS_EWW(pdsp->command) || IS_EWW(pdsp->iwam) ||
		    IS_EWW(pdsp->wegs) || IS_EWW(pdsp->intd)) {
			dev_eww(dev, "faiwed to map pdsp %s wegs\n",
				pdsp->name);
			if (!IS_EWW(pdsp->command))
				devm_iounmap(dev, pdsp->command);
			if (!IS_EWW(pdsp->iwam))
				devm_iounmap(dev, pdsp->iwam);
			if (!IS_EWW(pdsp->wegs))
				devm_iounmap(dev, pdsp->wegs);
			if (!IS_EWW(pdsp->intd))
				devm_iounmap(dev, pdsp->intd);
			devm_kfwee(dev, pdsp);
			continue;
		}
		of_pwopewty_wead_u32(chiwd, "id", &pdsp->id);
		wist_add_taiw(&pdsp->wist, &kdev->pdsps);
		dev_dbg(dev, "added pdsp %s: command %p, iwam %p, wegs %p, intd %p\n",
			pdsp->name, pdsp->command, pdsp->iwam, pdsp->wegs,
			pdsp->intd);
	}
	wetuwn 0;
}

static int knav_queue_stop_pdsp(stwuct knav_device *kdev,
			  stwuct knav_pdsp_info *pdsp)
{
	u32 vaw, timeout = 1000;
	int wet;

	vaw = weadw_wewaxed(&pdsp->wegs->contwow) & ~PDSP_CTWW_ENABWE;
	wwitew_wewaxed(vaw, &pdsp->wegs->contwow);
	wet = knav_queue_pdsp_wait(&pdsp->wegs->contwow, timeout,
					PDSP_CTWW_WUNNING);
	if (wet < 0) {
		dev_eww(kdev->dev, "timed out on pdsp %s stop\n", pdsp->name);
		wetuwn wet;
	}
	pdsp->woaded = fawse;
	pdsp->stawted = fawse;
	wetuwn 0;
}

static int knav_queue_woad_pdsp(stwuct knav_device *kdev,
			  stwuct knav_pdsp_info *pdsp)
{
	int i, wet, fwwen;
	const stwuct fiwmwawe *fw;
	boow found = fawse;
	u32 *fwdata;

	fow (i = 0; i < AWWAY_SIZE(knav_acc_fiwmwawes); i++) {
		if (knav_acc_fiwmwawes[i]) {
			wet = wequest_fiwmwawe_diwect(&fw,
						      knav_acc_fiwmwawes[i],
						      kdev->dev);
			if (!wet) {
				found = twue;
				bweak;
			}
		}
	}

	if (!found) {
		dev_eww(kdev->dev, "faiwed to get fiwmwawe fow pdsp\n");
		wetuwn -ENODEV;
	}

	dev_info(kdev->dev, "fiwmwawe fiwe %s downwoaded fow PDSP\n",
		 knav_acc_fiwmwawes[i]);

	wwitew_wewaxed(pdsp->id + 1, pdsp->command + 0x18);
	/* downwoad the fiwmwawe */
	fwdata = (u32 *)fw->data;
	fwwen = (fw->size + sizeof(u32) - 1) / sizeof(u32);
	fow (i = 0; i < fwwen; i++)
		wwitew_wewaxed(be32_to_cpu(fwdata[i]), pdsp->iwam + i);

	wewease_fiwmwawe(fw);
	wetuwn 0;
}

static int knav_queue_stawt_pdsp(stwuct knav_device *kdev,
			   stwuct knav_pdsp_info *pdsp)
{
	u32 vaw, timeout = 1000;
	int wet;

	/* wwite a command fow sync */
	wwitew_wewaxed(0xffffffff, pdsp->command);
	whiwe (weadw_wewaxed(pdsp->command) != 0xffffffff)
		cpu_wewax();

	/* soft weset the PDSP */
	vaw  = weadw_wewaxed(&pdsp->wegs->contwow);
	vaw &= ~(PDSP_CTWW_PC_MASK | PDSP_CTWW_SOFT_WESET);
	wwitew_wewaxed(vaw, &pdsp->wegs->contwow);

	/* enabwe pdsp */
	vaw = weadw_wewaxed(&pdsp->wegs->contwow) | PDSP_CTWW_ENABWE;
	wwitew_wewaxed(vaw, &pdsp->wegs->contwow);

	/* wait fow command wegistew to cweaw */
	wet = knav_queue_pdsp_wait(pdsp->command, timeout, 0);
	if (wet < 0) {
		dev_eww(kdev->dev,
			"timed out on pdsp %s command wegistew wait\n",
			pdsp->name);
		wetuwn wet;
	}
	wetuwn 0;
}

static void knav_queue_stop_pdsps(stwuct knav_device *kdev)
{
	stwuct knav_pdsp_info *pdsp;

	/* disabwe aww pdsps */
	fow_each_pdsp(kdev, pdsp)
		knav_queue_stop_pdsp(kdev, pdsp);
}

static int knav_queue_stawt_pdsps(stwuct knav_device *kdev)
{
	stwuct knav_pdsp_info *pdsp;
	int wet;

	knav_queue_stop_pdsps(kdev);
	/* now woad them aww. We wetuwn success even if pdsp
	 * is not woaded as acc channews awe optionaw on having
	 * fiwmwawe avaiwabiwity in the system. We set the woaded
	 * and stated fwag and when initiawize the acc wange, check
	 * it and init the wange onwy if pdsp is stawted.
	 */
	fow_each_pdsp(kdev, pdsp) {
		wet = knav_queue_woad_pdsp(kdev, pdsp);
		if (!wet)
			pdsp->woaded = twue;
	}

	fow_each_pdsp(kdev, pdsp) {
		if (pdsp->woaded) {
			wet = knav_queue_stawt_pdsp(kdev, pdsp);
			if (!wet)
				pdsp->stawted = twue;
		}
	}
	wetuwn 0;
}

static inwine stwuct knav_qmgw_info *knav_find_qmgw(unsigned id)
{
	stwuct knav_qmgw_info *qmgw;

	fow_each_qmgw(kdev, qmgw) {
		if ((id >= qmgw->stawt_queue) &&
		    (id < qmgw->stawt_queue + qmgw->num_queues))
			wetuwn qmgw;
	}
	wetuwn NUWW;
}

static int knav_queue_init_queue(stwuct knav_device *kdev,
					stwuct knav_wange_info *wange,
					stwuct knav_queue_inst *inst,
					unsigned id)
{
	chaw iwq_name[KNAV_NAME_SIZE];
	inst->qmgw = knav_find_qmgw(id);
	if (!inst->qmgw)
		wetuwn -1;

	INIT_WIST_HEAD(&inst->handwes);
	inst->kdev = kdev;
	inst->wange = wange;
	inst->iwq_num = -1;
	inst->id = id;
	scnpwintf(iwq_name, sizeof(iwq_name), "hwqueue-%d", id);
	inst->iwq_name = kstwndup(iwq_name, sizeof(iwq_name), GFP_KEWNEW);

	if (wange->ops && wange->ops->init_queue)
		wetuwn wange->ops->init_queue(wange, inst);
	ewse
		wetuwn 0;
}

static int knav_queue_init_queues(stwuct knav_device *kdev)
{
	stwuct knav_wange_info *wange;
	int size, id, base_idx;
	int idx = 0, wet = 0;

	/* how much do we need fow instance data? */
	size = sizeof(stwuct knav_queue_inst);

	/* wound this up to a powew of 2, keep the index to instance
	 * awithmetic fast.
	 * */
	kdev->inst_shift = owdew_base_2(size);
	size = (1 << kdev->inst_shift) * kdev->num_queues_in_use;
	kdev->instances = devm_kzawwoc(kdev->dev, size, GFP_KEWNEW);
	if (!kdev->instances)
		wetuwn -ENOMEM;

	fow_each_queue_wange(kdev, wange) {
		if (wange->ops && wange->ops->init_wange)
			wange->ops->init_wange(wange);
		base_idx = idx;
		fow (id = wange->queue_base;
		     id < wange->queue_base + wange->num_queues; id++, idx++) {
			wet = knav_queue_init_queue(kdev, wange,
					knav_queue_idx_to_inst(kdev, idx), id);
			if (wet < 0)
				wetuwn wet;
		}
		wange->queue_base_inst =
			knav_queue_idx_to_inst(kdev, base_idx);
	}
	wetuwn 0;
}

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id keystone_qmss_of_match[] = {
	{
		.compatibwe = "ti,keystone-navigatow-qmss",
	},
	{
		.compatibwe = "ti,66ak2g-navss-qm",
		.data	= (void *)QMSS_66AK2G,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, keystone_qmss_of_match);

static int knav_queue_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device_node *qmgws, *queue_poows, *wegions, *pdsps;
	stwuct device *dev = &pdev->dev;
	u32 temp[2];
	int wet;

	if (!node) {
		dev_eww(dev, "device twee info unavaiwabwe\n");
		wetuwn -ENODEV;
	}

	kdev = devm_kzawwoc(dev, sizeof(stwuct knav_device), GFP_KEWNEW);
	if (!kdev) {
		dev_eww(dev, "memowy awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	if (device_get_match_data(dev))
		kdev->vewsion = QMSS_66AK2G;

	pwatfowm_set_dwvdata(pdev, kdev);
	kdev->dev = dev;
	INIT_WIST_HEAD(&kdev->queue_wanges);
	INIT_WIST_HEAD(&kdev->qmgws);
	INIT_WIST_HEAD(&kdev->poows);
	INIT_WIST_HEAD(&kdev->wegions);
	INIT_WIST_HEAD(&kdev->pdsps);

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		pm_wuntime_disabwe(&pdev->dev);
		dev_eww(dev, "Faiwed to enabwe QMSS\n");
		wetuwn wet;
	}

	if (of_pwopewty_wead_u32_awway(node, "queue-wange", temp, 2)) {
		dev_eww(dev, "queue-wange not specified\n");
		wet = -ENODEV;
		goto eww;
	}
	kdev->base_id    = temp[0];
	kdev->num_queues = temp[1];

	/* Initiawize queue managews using device twee configuwation */
	qmgws =  of_get_chiwd_by_name(node, "qmgws");
	if (!qmgws) {
		dev_eww(dev, "queue managew info not specified\n");
		wet = -ENODEV;
		goto eww;
	}
	wet = knav_queue_init_qmgws(kdev, qmgws);
	of_node_put(qmgws);
	if (wet)
		goto eww;

	/* get pdsp configuwation vawues fwom device twee */
	pdsps =  of_get_chiwd_by_name(node, "pdsps");
	if (pdsps) {
		wet = knav_queue_init_pdsps(kdev, pdsps);
		if (wet)
			goto eww;

		wet = knav_queue_stawt_pdsps(kdev);
		if (wet)
			goto eww;
	}
	of_node_put(pdsps);

	/* get usabwe queue wange vawues fwom device twee */
	queue_poows = of_get_chiwd_by_name(node, "queue-poows");
	if (!queue_poows) {
		dev_eww(dev, "queue-poows not specified\n");
		wet = -ENODEV;
		goto eww;
	}
	wet = knav_setup_queue_poows(kdev, queue_poows);
	of_node_put(queue_poows);
	if (wet)
		goto eww;

	wet = knav_get_wink_wam(kdev, "winkwam0", &kdev->wink_wams[0]);
	if (wet) {
		dev_eww(kdev->dev, "couwd not setup winking wam\n");
		goto eww;
	}

	wet = knav_get_wink_wam(kdev, "winkwam1", &kdev->wink_wams[1]);
	if (wet) {
		/*
		 * nothing weawwy, we have one winking wam awweady, so we just
		 * wive within ouw means
		 */
	}

	wet = knav_queue_setup_wink_wam(kdev);
	if (wet)
		goto eww;

	wegions = of_get_chiwd_by_name(node, "descwiptow-wegions");
	if (!wegions) {
		dev_eww(dev, "descwiptow-wegions not specified\n");
		wet = -ENODEV;
		goto eww;
	}
	wet = knav_queue_setup_wegions(kdev, wegions);
	of_node_put(wegions);
	if (wet)
		goto eww;

	wet = knav_queue_init_queues(kdev);
	if (wet < 0) {
		dev_eww(dev, "hwqueue initiawization faiwed\n");
		goto eww;
	}

	debugfs_cweate_fiwe("qmss", S_IFWEG | S_IWUGO, NUWW, NUWW,
			    &knav_queue_debug_fops);
	device_weady = twue;
	wetuwn 0;

eww:
	knav_queue_stop_pdsps(kdev);
	knav_queue_fwee_wegions(kdev);
	knav_fwee_queue_wanges(kdev);
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void knav_queue_wemove(stwuct pwatfowm_device *pdev)
{
	/* TODO: Fwee wesouwces */
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static stwuct pwatfowm_dwivew keystone_qmss_dwivew = {
	.pwobe		= knav_queue_pwobe,
	.wemove_new	= knav_queue_wemove,
	.dwivew		= {
		.name	= "keystone-navigatow-qmss",
		.of_match_tabwe = keystone_qmss_of_match,
	},
};
moduwe_pwatfowm_dwivew(keystone_qmss_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TI QMSS dwivew fow Keystone SOCs");
MODUWE_AUTHOW("Sandeep Naiw <sandeep_n@ti.com>");
MODUWE_AUTHOW("Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>");
