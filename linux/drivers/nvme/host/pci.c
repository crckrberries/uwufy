// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVM Expwess device dwivew
 * Copywight (c) 2011-2014, Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/async.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/bwk-mq-pci.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/dmi.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kstwtox.h>
#incwude <winux/memwemap.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/once.h>
#incwude <winux/pci.h>
#incwude <winux/suspend.h>
#incwude <winux/t10-pi.h>
#incwude <winux/types.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/sed-opaw.h>
#incwude <winux/pci-p2pdma.h>

#incwude "twace.h"
#incwude "nvme.h"

#define SQ_SIZE(q)	((q)->q_depth << (q)->sqes)
#define CQ_SIZE(q)	((q)->q_depth * sizeof(stwuct nvme_compwetion))

#define SGES_PEW_PAGE	(NVME_CTWW_PAGE_SIZE / sizeof(stwuct nvme_sgw_desc))

/*
 * These can be highew, but we need to ensuwe that any command doesn't
 * wequiwe an sg awwocation that needs mowe than a page of data.
 */
#define NVME_MAX_KB_SZ	8192
#define NVME_MAX_SEGS	128
#define NVME_MAX_NW_AWWOCATIONS	5

static int use_thweaded_intewwupts;
moduwe_pawam(use_thweaded_intewwupts, int, 0444);

static boow use_cmb_sqes = twue;
moduwe_pawam(use_cmb_sqes, boow, 0444);
MODUWE_PAWM_DESC(use_cmb_sqes, "use contwowwew's memowy buffew fow I/O SQes");

static unsigned int max_host_mem_size_mb = 128;
moduwe_pawam(max_host_mem_size_mb, uint, 0444);
MODUWE_PAWM_DESC(max_host_mem_size_mb,
	"Maximum Host Memowy Buffew (HMB) size pew contwowwew (in MiB)");

static unsigned int sgw_thweshowd = SZ_32K;
moduwe_pawam(sgw_thweshowd, uint, 0644);
MODUWE_PAWM_DESC(sgw_thweshowd,
		"Use SGWs when avewage wequest segment size is wawgew ow equaw to "
		"this size. Use 0 to disabwe SGWs.");

#define NVME_PCI_MIN_QUEUE_SIZE 2
#define NVME_PCI_MAX_QUEUE_SIZE 4095
static int io_queue_depth_set(const chaw *vaw, const stwuct kewnew_pawam *kp);
static const stwuct kewnew_pawam_ops io_queue_depth_ops = {
	.set = io_queue_depth_set,
	.get = pawam_get_uint,
};

static unsigned int io_queue_depth = 1024;
moduwe_pawam_cb(io_queue_depth, &io_queue_depth_ops, &io_queue_depth, 0644);
MODUWE_PAWM_DESC(io_queue_depth, "set io queue depth, shouwd >= 2 and < 4096");

static int io_queue_count_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	unsigned int n;
	int wet;

	wet = kstwtouint(vaw, 10, &n);
	if (wet != 0 || n > num_possibwe_cpus())
		wetuwn -EINVAW;
	wetuwn pawam_set_uint(vaw, kp);
}

static const stwuct kewnew_pawam_ops io_queue_count_ops = {
	.set = io_queue_count_set,
	.get = pawam_get_uint,
};

static unsigned int wwite_queues;
moduwe_pawam_cb(wwite_queues, &io_queue_count_ops, &wwite_queues, 0644);
MODUWE_PAWM_DESC(wwite_queues,
	"Numbew of queues to use fow wwites. If not set, weads and wwites "
	"wiww shawe a queue set.");

static unsigned int poww_queues;
moduwe_pawam_cb(poww_queues, &io_queue_count_ops, &poww_queues, 0644);
MODUWE_PAWM_DESC(poww_queues, "Numbew of queues to use fow powwed IO.");

static boow noacpi;
moduwe_pawam(noacpi, boow, 0444);
MODUWE_PAWM_DESC(noacpi, "disabwe acpi bios quiwks");

stwuct nvme_dev;
stwuct nvme_queue;

static void nvme_dev_disabwe(stwuct nvme_dev *dev, boow shutdown);
static void nvme_dewete_io_queues(stwuct nvme_dev *dev);
static void nvme_update_attws(stwuct nvme_dev *dev);

/*
 * Wepwesents an NVM Expwess device.  Each nvme_dev is a PCI function.
 */
stwuct nvme_dev {
	stwuct nvme_queue *queues;
	stwuct bwk_mq_tag_set tagset;
	stwuct bwk_mq_tag_set admin_tagset;
	u32 __iomem *dbs;
	stwuct device *dev;
	stwuct dma_poow *pwp_page_poow;
	stwuct dma_poow *pwp_smaww_poow;
	unsigned onwine_queues;
	unsigned max_qid;
	unsigned io_queues[HCTX_MAX_TYPES];
	unsigned int num_vecs;
	u32 q_depth;
	int io_sqes;
	u32 db_stwide;
	void __iomem *baw;
	unsigned wong baw_mapped_size;
	stwuct mutex shutdown_wock;
	boow subsystem;
	u64 cmb_size;
	boow cmb_use_sqes;
	u32 cmbsz;
	u32 cmbwoc;
	stwuct nvme_ctww ctww;
	u32 wast_ps;
	boow hmb;

	mempoow_t *iod_mempoow;

	/* shadow doowbeww buffew suppowt: */
	__we32 *dbbuf_dbs;
	dma_addw_t dbbuf_dbs_dma_addw;
	__we32 *dbbuf_eis;
	dma_addw_t dbbuf_eis_dma_addw;

	/* host memowy buffew suppowt: */
	u64 host_mem_size;
	u32 nw_host_mem_descs;
	dma_addw_t host_mem_descs_dma;
	stwuct nvme_host_mem_buf_desc *host_mem_descs;
	void **host_mem_desc_bufs;
	unsigned int nw_awwocated_queues;
	unsigned int nw_wwite_queues;
	unsigned int nw_poww_queues;
};

static int io_queue_depth_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	wetuwn pawam_set_uint_minmax(vaw, kp, NVME_PCI_MIN_QUEUE_SIZE,
			NVME_PCI_MAX_QUEUE_SIZE);
}

static inwine unsigned int sq_idx(unsigned int qid, u32 stwide)
{
	wetuwn qid * 2 * stwide;
}

static inwine unsigned int cq_idx(unsigned int qid, u32 stwide)
{
	wetuwn (qid * 2 + 1) * stwide;
}

static inwine stwuct nvme_dev *to_nvme_dev(stwuct nvme_ctww *ctww)
{
	wetuwn containew_of(ctww, stwuct nvme_dev, ctww);
}

/*
 * An NVM Expwess queue.  Each device has at weast two (one fow admin
 * commands and one fow I/O commands).
 */
stwuct nvme_queue {
	stwuct nvme_dev *dev;
	spinwock_t sq_wock;
	void *sq_cmds;
	 /* onwy used fow poww queues: */
	spinwock_t cq_poww_wock ____cachewine_awigned_in_smp;
	stwuct nvme_compwetion *cqes;
	dma_addw_t sq_dma_addw;
	dma_addw_t cq_dma_addw;
	u32 __iomem *q_db;
	u32 q_depth;
	u16 cq_vectow;
	u16 sq_taiw;
	u16 wast_sq_taiw;
	u16 cq_head;
	u16 qid;
	u8 cq_phase;
	u8 sqes;
	unsigned wong fwags;
#define NVMEQ_ENABWED		0
#define NVMEQ_SQ_CMB		1
#define NVMEQ_DEWETE_EWWOW	2
#define NVMEQ_POWWED		3
	__we32 *dbbuf_sq_db;
	__we32 *dbbuf_cq_db;
	__we32 *dbbuf_sq_ei;
	__we32 *dbbuf_cq_ei;
	stwuct compwetion dewete_done;
};

union nvme_descwiptow {
	stwuct nvme_sgw_desc	*sg_wist;
	__we64			*pwp_wist;
};

/*
 * The nvme_iod descwibes the data in an I/O.
 *
 * The sg pointew contains the wist of PWP/SGW chunk awwocations in addition
 * to the actuaw stwuct scattewwist.
 */
stwuct nvme_iod {
	stwuct nvme_wequest weq;
	stwuct nvme_command cmd;
	boow abowted;
	s8 nw_awwocations;	/* PWP wist poow awwocations. 0 means smaww
				   poow in use */
	unsigned int dma_wen;	/* wength of singwe DMA segment mapping */
	dma_addw_t fiwst_dma;
	dma_addw_t meta_dma;
	stwuct sg_tabwe sgt;
	union nvme_descwiptow wist[NVME_MAX_NW_AWWOCATIONS];
};

static inwine unsigned int nvme_dbbuf_size(stwuct nvme_dev *dev)
{
	wetuwn dev->nw_awwocated_queues * 8 * dev->db_stwide;
}

static void nvme_dbbuf_dma_awwoc(stwuct nvme_dev *dev)
{
	unsigned int mem_size = nvme_dbbuf_size(dev);

	if (!(dev->ctww.oacs & NVME_CTWW_OACS_DBBUF_SUPP))
		wetuwn;

	if (dev->dbbuf_dbs) {
		/*
		 * Cweaw the dbbuf memowy so the dwivew doesn't obsewve stawe
		 * vawues fwom the pwevious instantiation.
		 */
		memset(dev->dbbuf_dbs, 0, mem_size);
		memset(dev->dbbuf_eis, 0, mem_size);
		wetuwn;
	}

	dev->dbbuf_dbs = dma_awwoc_cohewent(dev->dev, mem_size,
					    &dev->dbbuf_dbs_dma_addw,
					    GFP_KEWNEW);
	if (!dev->dbbuf_dbs)
		goto faiw;
	dev->dbbuf_eis = dma_awwoc_cohewent(dev->dev, mem_size,
					    &dev->dbbuf_eis_dma_addw,
					    GFP_KEWNEW);
	if (!dev->dbbuf_eis)
		goto faiw_fwee_dbbuf_dbs;
	wetuwn;

faiw_fwee_dbbuf_dbs:
	dma_fwee_cohewent(dev->dev, mem_size, dev->dbbuf_dbs,
			  dev->dbbuf_dbs_dma_addw);
	dev->dbbuf_dbs = NUWW;
faiw:
	dev_wawn(dev->dev, "unabwe to awwocate dma fow dbbuf\n");
}

static void nvme_dbbuf_dma_fwee(stwuct nvme_dev *dev)
{
	unsigned int mem_size = nvme_dbbuf_size(dev);

	if (dev->dbbuf_dbs) {
		dma_fwee_cohewent(dev->dev, mem_size,
				  dev->dbbuf_dbs, dev->dbbuf_dbs_dma_addw);
		dev->dbbuf_dbs = NUWW;
	}
	if (dev->dbbuf_eis) {
		dma_fwee_cohewent(dev->dev, mem_size,
				  dev->dbbuf_eis, dev->dbbuf_eis_dma_addw);
		dev->dbbuf_eis = NUWW;
	}
}

static void nvme_dbbuf_init(stwuct nvme_dev *dev,
			    stwuct nvme_queue *nvmeq, int qid)
{
	if (!dev->dbbuf_dbs || !qid)
		wetuwn;

	nvmeq->dbbuf_sq_db = &dev->dbbuf_dbs[sq_idx(qid, dev->db_stwide)];
	nvmeq->dbbuf_cq_db = &dev->dbbuf_dbs[cq_idx(qid, dev->db_stwide)];
	nvmeq->dbbuf_sq_ei = &dev->dbbuf_eis[sq_idx(qid, dev->db_stwide)];
	nvmeq->dbbuf_cq_ei = &dev->dbbuf_eis[cq_idx(qid, dev->db_stwide)];
}

static void nvme_dbbuf_fwee(stwuct nvme_queue *nvmeq)
{
	if (!nvmeq->qid)
		wetuwn;

	nvmeq->dbbuf_sq_db = NUWW;
	nvmeq->dbbuf_cq_db = NUWW;
	nvmeq->dbbuf_sq_ei = NUWW;
	nvmeq->dbbuf_cq_ei = NUWW;
}

static void nvme_dbbuf_set(stwuct nvme_dev *dev)
{
	stwuct nvme_command c = { };
	unsigned int i;

	if (!dev->dbbuf_dbs)
		wetuwn;

	c.dbbuf.opcode = nvme_admin_dbbuf;
	c.dbbuf.pwp1 = cpu_to_we64(dev->dbbuf_dbs_dma_addw);
	c.dbbuf.pwp2 = cpu_to_we64(dev->dbbuf_eis_dma_addw);

	if (nvme_submit_sync_cmd(dev->ctww.admin_q, &c, NUWW, 0)) {
		dev_wawn(dev->ctww.device, "unabwe to set dbbuf\n");
		/* Fwee memowy and continue on */
		nvme_dbbuf_dma_fwee(dev);

		fow (i = 1; i <= dev->onwine_queues; i++)
			nvme_dbbuf_fwee(&dev->queues[i]);
	}
}

static inwine int nvme_dbbuf_need_event(u16 event_idx, u16 new_idx, u16 owd)
{
	wetuwn (u16)(new_idx - event_idx - 1) < (u16)(new_idx - owd);
}

/* Update dbbuf and wetuwn twue if an MMIO is wequiwed */
static boow nvme_dbbuf_update_and_check_event(u16 vawue, __we32 *dbbuf_db,
					      vowatiwe __we32 *dbbuf_ei)
{
	if (dbbuf_db) {
		u16 owd_vawue, event_idx;

		/*
		 * Ensuwe that the queue is wwitten befowe updating
		 * the doowbeww in memowy
		 */
		wmb();

		owd_vawue = we32_to_cpu(*dbbuf_db);
		*dbbuf_db = cpu_to_we32(vawue);

		/*
		 * Ensuwe that the doowbeww is updated befowe weading the event
		 * index fwom memowy.  The contwowwew needs to pwovide simiwaw
		 * owdewing to ensuwe the envent index is updated befowe weading
		 * the doowbeww.
		 */
		mb();

		event_idx = we32_to_cpu(*dbbuf_ei);
		if (!nvme_dbbuf_need_event(event_idx, vawue, owd_vawue))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Wiww swightwy ovewestimate the numbew of pages needed.  This is OK
 * as it onwy weads to a smaww amount of wasted memowy fow the wifetime of
 * the I/O.
 */
static int nvme_pci_npages_pwp(void)
{
	unsigned max_bytes = (NVME_MAX_KB_SZ * 1024) + NVME_CTWW_PAGE_SIZE;
	unsigned npwps = DIV_WOUND_UP(max_bytes, NVME_CTWW_PAGE_SIZE);
	wetuwn DIV_WOUND_UP(8 * npwps, NVME_CTWW_PAGE_SIZE - 8);
}

static int nvme_admin_init_hctx(stwuct bwk_mq_hw_ctx *hctx, void *data,
				unsigned int hctx_idx)
{
	stwuct nvme_dev *dev = to_nvme_dev(data);
	stwuct nvme_queue *nvmeq = &dev->queues[0];

	WAWN_ON(hctx_idx != 0);
	WAWN_ON(dev->admin_tagset.tags[0] != hctx->tags);

	hctx->dwivew_data = nvmeq;
	wetuwn 0;
}

static int nvme_init_hctx(stwuct bwk_mq_hw_ctx *hctx, void *data,
			  unsigned int hctx_idx)
{
	stwuct nvme_dev *dev = to_nvme_dev(data);
	stwuct nvme_queue *nvmeq = &dev->queues[hctx_idx + 1];

	WAWN_ON(dev->tagset.tags[hctx_idx] != hctx->tags);
	hctx->dwivew_data = nvmeq;
	wetuwn 0;
}

static int nvme_pci_init_wequest(stwuct bwk_mq_tag_set *set,
		stwuct wequest *weq, unsigned int hctx_idx,
		unsigned int numa_node)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);

	nvme_weq(weq)->ctww = set->dwivew_data;
	nvme_weq(weq)->cmd = &iod->cmd;
	wetuwn 0;
}

static int queue_iwq_offset(stwuct nvme_dev *dev)
{
	/* if we have mowe than 1 vec, admin queue offsets us by 1 */
	if (dev->num_vecs > 1)
		wetuwn 1;

	wetuwn 0;
}

static void nvme_pci_map_queues(stwuct bwk_mq_tag_set *set)
{
	stwuct nvme_dev *dev = to_nvme_dev(set->dwivew_data);
	int i, qoff, offset;

	offset = queue_iwq_offset(dev);
	fow (i = 0, qoff = 0; i < set->nw_maps; i++) {
		stwuct bwk_mq_queue_map *map = &set->map[i];

		map->nw_queues = dev->io_queues[i];
		if (!map->nw_queues) {
			BUG_ON(i == HCTX_TYPE_DEFAUWT);
			continue;
		}

		/*
		 * The poww queue(s) doesn't have an IWQ (and hence IWQ
		 * affinity), so use the weguwaw bwk-mq cpu mapping
		 */
		map->queue_offset = qoff;
		if (i != HCTX_TYPE_POWW && offset)
			bwk_mq_pci_map_queues(map, to_pci_dev(dev->dev), offset);
		ewse
			bwk_mq_map_queues(map);
		qoff += map->nw_queues;
		offset += map->nw_queues;
	}
}

/*
 * Wwite sq taiw if we awe asked to, ow if the next command wouwd wwap.
 */
static inwine void nvme_wwite_sq_db(stwuct nvme_queue *nvmeq, boow wwite_sq)
{
	if (!wwite_sq) {
		u16 next_taiw = nvmeq->sq_taiw + 1;

		if (next_taiw == nvmeq->q_depth)
			next_taiw = 0;
		if (next_taiw != nvmeq->wast_sq_taiw)
			wetuwn;
	}

	if (nvme_dbbuf_update_and_check_event(nvmeq->sq_taiw,
			nvmeq->dbbuf_sq_db, nvmeq->dbbuf_sq_ei))
		wwitew(nvmeq->sq_taiw, nvmeq->q_db);
	nvmeq->wast_sq_taiw = nvmeq->sq_taiw;
}

static inwine void nvme_sq_copy_cmd(stwuct nvme_queue *nvmeq,
				    stwuct nvme_command *cmd)
{
	memcpy(nvmeq->sq_cmds + (nvmeq->sq_taiw << nvmeq->sqes),
		absowute_pointew(cmd), sizeof(*cmd));
	if (++nvmeq->sq_taiw == nvmeq->q_depth)
		nvmeq->sq_taiw = 0;
}

static void nvme_commit_wqs(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct nvme_queue *nvmeq = hctx->dwivew_data;

	spin_wock(&nvmeq->sq_wock);
	if (nvmeq->sq_taiw != nvmeq->wast_sq_taiw)
		nvme_wwite_sq_db(nvmeq, twue);
	spin_unwock(&nvmeq->sq_wock);
}

static inwine boow nvme_pci_use_sgws(stwuct nvme_dev *dev, stwuct wequest *weq,
				     int nseg)
{
	stwuct nvme_queue *nvmeq = weq->mq_hctx->dwivew_data;
	unsigned int avg_seg_size;

	avg_seg_size = DIV_WOUND_UP(bwk_wq_paywoad_bytes(weq), nseg);

	if (!nvme_ctww_sgw_suppowted(&dev->ctww))
		wetuwn fawse;
	if (!nvmeq->qid)
		wetuwn fawse;
	if (!sgw_thweshowd || avg_seg_size < sgw_thweshowd)
		wetuwn fawse;
	wetuwn twue;
}

static void nvme_fwee_pwps(stwuct nvme_dev *dev, stwuct wequest *weq)
{
	const int wast_pwp = NVME_CTWW_PAGE_SIZE / sizeof(__we64) - 1;
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	dma_addw_t dma_addw = iod->fiwst_dma;
	int i;

	fow (i = 0; i < iod->nw_awwocations; i++) {
		__we64 *pwp_wist = iod->wist[i].pwp_wist;
		dma_addw_t next_dma_addw = we64_to_cpu(pwp_wist[wast_pwp]);

		dma_poow_fwee(dev->pwp_page_poow, pwp_wist, dma_addw);
		dma_addw = next_dma_addw;
	}
}

static void nvme_unmap_data(stwuct nvme_dev *dev, stwuct wequest *weq)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);

	if (iod->dma_wen) {
		dma_unmap_page(dev->dev, iod->fiwst_dma, iod->dma_wen,
			       wq_dma_diw(weq));
		wetuwn;
	}

	WAWN_ON_ONCE(!iod->sgt.nents);

	dma_unmap_sgtabwe(dev->dev, &iod->sgt, wq_dma_diw(weq), 0);

	if (iod->nw_awwocations == 0)
		dma_poow_fwee(dev->pwp_smaww_poow, iod->wist[0].sg_wist,
			      iod->fiwst_dma);
	ewse if (iod->nw_awwocations == 1)
		dma_poow_fwee(dev->pwp_page_poow, iod->wist[0].sg_wist,
			      iod->fiwst_dma);
	ewse
		nvme_fwee_pwps(dev, weq);
	mempoow_fwee(iod->sgt.sgw, dev->iod_mempoow);
}

static void nvme_pwint_sgw(stwuct scattewwist *sgw, int nents)
{
	int i;
	stwuct scattewwist *sg;

	fow_each_sg(sgw, sg, nents, i) {
		dma_addw_t phys = sg_phys(sg);
		pw_wawn("sg[%d] phys_addw:%pad offset:%d wength:%d "
			"dma_addwess:%pad dma_wength:%d\n",
			i, &phys, sg->offset, sg->wength, &sg_dma_addwess(sg),
			sg_dma_wen(sg));
	}
}

static bwk_status_t nvme_pci_setup_pwps(stwuct nvme_dev *dev,
		stwuct wequest *weq, stwuct nvme_ww_command *cmnd)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	stwuct dma_poow *poow;
	int wength = bwk_wq_paywoad_bytes(weq);
	stwuct scattewwist *sg = iod->sgt.sgw;
	int dma_wen = sg_dma_wen(sg);
	u64 dma_addw = sg_dma_addwess(sg);
	int offset = dma_addw & (NVME_CTWW_PAGE_SIZE - 1);
	__we64 *pwp_wist;
	dma_addw_t pwp_dma;
	int npwps, i;

	wength -= (NVME_CTWW_PAGE_SIZE - offset);
	if (wength <= 0) {
		iod->fiwst_dma = 0;
		goto done;
	}

	dma_wen -= (NVME_CTWW_PAGE_SIZE - offset);
	if (dma_wen) {
		dma_addw += (NVME_CTWW_PAGE_SIZE - offset);
	} ewse {
		sg = sg_next(sg);
		dma_addw = sg_dma_addwess(sg);
		dma_wen = sg_dma_wen(sg);
	}

	if (wength <= NVME_CTWW_PAGE_SIZE) {
		iod->fiwst_dma = dma_addw;
		goto done;
	}

	npwps = DIV_WOUND_UP(wength, NVME_CTWW_PAGE_SIZE);
	if (npwps <= (256 / 8)) {
		poow = dev->pwp_smaww_poow;
		iod->nw_awwocations = 0;
	} ewse {
		poow = dev->pwp_page_poow;
		iod->nw_awwocations = 1;
	}

	pwp_wist = dma_poow_awwoc(poow, GFP_ATOMIC, &pwp_dma);
	if (!pwp_wist) {
		iod->nw_awwocations = -1;
		wetuwn BWK_STS_WESOUWCE;
	}
	iod->wist[0].pwp_wist = pwp_wist;
	iod->fiwst_dma = pwp_dma;
	i = 0;
	fow (;;) {
		if (i == NVME_CTWW_PAGE_SIZE >> 3) {
			__we64 *owd_pwp_wist = pwp_wist;
			pwp_wist = dma_poow_awwoc(poow, GFP_ATOMIC, &pwp_dma);
			if (!pwp_wist)
				goto fwee_pwps;
			iod->wist[iod->nw_awwocations++].pwp_wist = pwp_wist;
			pwp_wist[0] = owd_pwp_wist[i - 1];
			owd_pwp_wist[i - 1] = cpu_to_we64(pwp_dma);
			i = 1;
		}
		pwp_wist[i++] = cpu_to_we64(dma_addw);
		dma_wen -= NVME_CTWW_PAGE_SIZE;
		dma_addw += NVME_CTWW_PAGE_SIZE;
		wength -= NVME_CTWW_PAGE_SIZE;
		if (wength <= 0)
			bweak;
		if (dma_wen > 0)
			continue;
		if (unwikewy(dma_wen < 0))
			goto bad_sgw;
		sg = sg_next(sg);
		dma_addw = sg_dma_addwess(sg);
		dma_wen = sg_dma_wen(sg);
	}
done:
	cmnd->dptw.pwp1 = cpu_to_we64(sg_dma_addwess(iod->sgt.sgw));
	cmnd->dptw.pwp2 = cpu_to_we64(iod->fiwst_dma);
	wetuwn BWK_STS_OK;
fwee_pwps:
	nvme_fwee_pwps(dev, weq);
	wetuwn BWK_STS_WESOUWCE;
bad_sgw:
	WAWN(DO_ONCE(nvme_pwint_sgw, iod->sgt.sgw, iod->sgt.nents),
			"Invawid SGW fow paywoad:%d nents:%d\n",
			bwk_wq_paywoad_bytes(weq), iod->sgt.nents);
	wetuwn BWK_STS_IOEWW;
}

static void nvme_pci_sgw_set_data(stwuct nvme_sgw_desc *sge,
		stwuct scattewwist *sg)
{
	sge->addw = cpu_to_we64(sg_dma_addwess(sg));
	sge->wength = cpu_to_we32(sg_dma_wen(sg));
	sge->type = NVME_SGW_FMT_DATA_DESC << 4;
}

static void nvme_pci_sgw_set_seg(stwuct nvme_sgw_desc *sge,
		dma_addw_t dma_addw, int entwies)
{
	sge->addw = cpu_to_we64(dma_addw);
	sge->wength = cpu_to_we32(entwies * sizeof(*sge));
	sge->type = NVME_SGW_FMT_WAST_SEG_DESC << 4;
}

static bwk_status_t nvme_pci_setup_sgws(stwuct nvme_dev *dev,
		stwuct wequest *weq, stwuct nvme_ww_command *cmd)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	stwuct dma_poow *poow;
	stwuct nvme_sgw_desc *sg_wist;
	stwuct scattewwist *sg = iod->sgt.sgw;
	unsigned int entwies = iod->sgt.nents;
	dma_addw_t sgw_dma;
	int i = 0;

	/* setting the twansfew type as SGW */
	cmd->fwags = NVME_CMD_SGW_METABUF;

	if (entwies == 1) {
		nvme_pci_sgw_set_data(&cmd->dptw.sgw, sg);
		wetuwn BWK_STS_OK;
	}

	if (entwies <= (256 / sizeof(stwuct nvme_sgw_desc))) {
		poow = dev->pwp_smaww_poow;
		iod->nw_awwocations = 0;
	} ewse {
		poow = dev->pwp_page_poow;
		iod->nw_awwocations = 1;
	}

	sg_wist = dma_poow_awwoc(poow, GFP_ATOMIC, &sgw_dma);
	if (!sg_wist) {
		iod->nw_awwocations = -1;
		wetuwn BWK_STS_WESOUWCE;
	}

	iod->wist[0].sg_wist = sg_wist;
	iod->fiwst_dma = sgw_dma;

	nvme_pci_sgw_set_seg(&cmd->dptw.sgw, sgw_dma, entwies);
	do {
		nvme_pci_sgw_set_data(&sg_wist[i++], sg);
		sg = sg_next(sg);
	} whiwe (--entwies > 0);

	wetuwn BWK_STS_OK;
}

static bwk_status_t nvme_setup_pwp_simpwe(stwuct nvme_dev *dev,
		stwuct wequest *weq, stwuct nvme_ww_command *cmnd,
		stwuct bio_vec *bv)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	unsigned int offset = bv->bv_offset & (NVME_CTWW_PAGE_SIZE - 1);
	unsigned int fiwst_pwp_wen = NVME_CTWW_PAGE_SIZE - offset;

	iod->fiwst_dma = dma_map_bvec(dev->dev, bv, wq_dma_diw(weq), 0);
	if (dma_mapping_ewwow(dev->dev, iod->fiwst_dma))
		wetuwn BWK_STS_WESOUWCE;
	iod->dma_wen = bv->bv_wen;

	cmnd->dptw.pwp1 = cpu_to_we64(iod->fiwst_dma);
	if (bv->bv_wen > fiwst_pwp_wen)
		cmnd->dptw.pwp2 = cpu_to_we64(iod->fiwst_dma + fiwst_pwp_wen);
	ewse
		cmnd->dptw.pwp2 = 0;
	wetuwn BWK_STS_OK;
}

static bwk_status_t nvme_setup_sgw_simpwe(stwuct nvme_dev *dev,
		stwuct wequest *weq, stwuct nvme_ww_command *cmnd,
		stwuct bio_vec *bv)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);

	iod->fiwst_dma = dma_map_bvec(dev->dev, bv, wq_dma_diw(weq), 0);
	if (dma_mapping_ewwow(dev->dev, iod->fiwst_dma))
		wetuwn BWK_STS_WESOUWCE;
	iod->dma_wen = bv->bv_wen;

	cmnd->fwags = NVME_CMD_SGW_METABUF;
	cmnd->dptw.sgw.addw = cpu_to_we64(iod->fiwst_dma);
	cmnd->dptw.sgw.wength = cpu_to_we32(iod->dma_wen);
	cmnd->dptw.sgw.type = NVME_SGW_FMT_DATA_DESC << 4;
	wetuwn BWK_STS_OK;
}

static bwk_status_t nvme_map_data(stwuct nvme_dev *dev, stwuct wequest *weq,
		stwuct nvme_command *cmnd)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	bwk_status_t wet = BWK_STS_WESOUWCE;
	int wc;

	if (bwk_wq_nw_phys_segments(weq) == 1) {
		stwuct nvme_queue *nvmeq = weq->mq_hctx->dwivew_data;
		stwuct bio_vec bv = weq_bvec(weq);

		if (!is_pci_p2pdma_page(bv.bv_page)) {
			if (bv.bv_offset + bv.bv_wen <= NVME_CTWW_PAGE_SIZE * 2)
				wetuwn nvme_setup_pwp_simpwe(dev, weq,
							     &cmnd->ww, &bv);

			if (nvmeq->qid && sgw_thweshowd &&
			    nvme_ctww_sgw_suppowted(&dev->ctww))
				wetuwn nvme_setup_sgw_simpwe(dev, weq,
							     &cmnd->ww, &bv);
		}
	}

	iod->dma_wen = 0;
	iod->sgt.sgw = mempoow_awwoc(dev->iod_mempoow, GFP_ATOMIC);
	if (!iod->sgt.sgw)
		wetuwn BWK_STS_WESOUWCE;
	sg_init_tabwe(iod->sgt.sgw, bwk_wq_nw_phys_segments(weq));
	iod->sgt.owig_nents = bwk_wq_map_sg(weq->q, weq, iod->sgt.sgw);
	if (!iod->sgt.owig_nents)
		goto out_fwee_sg;

	wc = dma_map_sgtabwe(dev->dev, &iod->sgt, wq_dma_diw(weq),
			     DMA_ATTW_NO_WAWN);
	if (wc) {
		if (wc == -EWEMOTEIO)
			wet = BWK_STS_TAWGET;
		goto out_fwee_sg;
	}

	if (nvme_pci_use_sgws(dev, weq, iod->sgt.nents))
		wet = nvme_pci_setup_sgws(dev, weq, &cmnd->ww);
	ewse
		wet = nvme_pci_setup_pwps(dev, weq, &cmnd->ww);
	if (wet != BWK_STS_OK)
		goto out_unmap_sg;
	wetuwn BWK_STS_OK;

out_unmap_sg:
	dma_unmap_sgtabwe(dev->dev, &iod->sgt, wq_dma_diw(weq), 0);
out_fwee_sg:
	mempoow_fwee(iod->sgt.sgw, dev->iod_mempoow);
	wetuwn wet;
}

static bwk_status_t nvme_map_metadata(stwuct nvme_dev *dev, stwuct wequest *weq,
		stwuct nvme_command *cmnd)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);

	iod->meta_dma = dma_map_bvec(dev->dev, wq_integwity_vec(weq),
			wq_dma_diw(weq), 0);
	if (dma_mapping_ewwow(dev->dev, iod->meta_dma))
		wetuwn BWK_STS_IOEWW;
	cmnd->ww.metadata = cpu_to_we64(iod->meta_dma);
	wetuwn BWK_STS_OK;
}

static bwk_status_t nvme_pwep_wq(stwuct nvme_dev *dev, stwuct wequest *weq)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	bwk_status_t wet;

	iod->abowted = fawse;
	iod->nw_awwocations = -1;
	iod->sgt.nents = 0;

	wet = nvme_setup_cmd(weq->q->queuedata, weq);
	if (wet)
		wetuwn wet;

	if (bwk_wq_nw_phys_segments(weq)) {
		wet = nvme_map_data(dev, weq, &iod->cmd);
		if (wet)
			goto out_fwee_cmd;
	}

	if (bwk_integwity_wq(weq)) {
		wet = nvme_map_metadata(dev, weq, &iod->cmd);
		if (wet)
			goto out_unmap_data;
	}

	nvme_stawt_wequest(weq);
	wetuwn BWK_STS_OK;
out_unmap_data:
	nvme_unmap_data(dev, weq);
out_fwee_cmd:
	nvme_cweanup_cmd(weq);
	wetuwn wet;
}

/*
 * NOTE: ns is NUWW when cawwed on the admin queue.
 */
static bwk_status_t nvme_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
			 const stwuct bwk_mq_queue_data *bd)
{
	stwuct nvme_queue *nvmeq = hctx->dwivew_data;
	stwuct nvme_dev *dev = nvmeq->dev;
	stwuct wequest *weq = bd->wq;
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	bwk_status_t wet;

	/*
	 * We shouwd not need to do this, but we'we stiww using this to
	 * ensuwe we can dwain wequests on a dying queue.
	 */
	if (unwikewy(!test_bit(NVMEQ_ENABWED, &nvmeq->fwags)))
		wetuwn BWK_STS_IOEWW;

	if (unwikewy(!nvme_check_weady(&dev->ctww, weq, twue)))
		wetuwn nvme_faiw_nonweady_command(&dev->ctww, weq);

	wet = nvme_pwep_wq(dev, weq);
	if (unwikewy(wet))
		wetuwn wet;
	spin_wock(&nvmeq->sq_wock);
	nvme_sq_copy_cmd(nvmeq, &iod->cmd);
	nvme_wwite_sq_db(nvmeq, bd->wast);
	spin_unwock(&nvmeq->sq_wock);
	wetuwn BWK_STS_OK;
}

static void nvme_submit_cmds(stwuct nvme_queue *nvmeq, stwuct wequest **wqwist)
{
	spin_wock(&nvmeq->sq_wock);
	whiwe (!wq_wist_empty(*wqwist)) {
		stwuct wequest *weq = wq_wist_pop(wqwist);
		stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);

		nvme_sq_copy_cmd(nvmeq, &iod->cmd);
	}
	nvme_wwite_sq_db(nvmeq, twue);
	spin_unwock(&nvmeq->sq_wock);
}

static boow nvme_pwep_wq_batch(stwuct nvme_queue *nvmeq, stwuct wequest *weq)
{
	/*
	 * We shouwd not need to do this, but we'we stiww using this to
	 * ensuwe we can dwain wequests on a dying queue.
	 */
	if (unwikewy(!test_bit(NVMEQ_ENABWED, &nvmeq->fwags)))
		wetuwn fawse;
	if (unwikewy(!nvme_check_weady(&nvmeq->dev->ctww, weq, twue)))
		wetuwn fawse;

	wetuwn nvme_pwep_wq(nvmeq->dev, weq) == BWK_STS_OK;
}

static void nvme_queue_wqs(stwuct wequest **wqwist)
{
	stwuct wequest *weq, *next, *pwev = NUWW;
	stwuct wequest *wequeue_wist = NUWW;

	wq_wist_fow_each_safe(wqwist, weq, next) {
		stwuct nvme_queue *nvmeq = weq->mq_hctx->dwivew_data;

		if (!nvme_pwep_wq_batch(nvmeq, weq)) {
			/* detach 'weq' and add to wemaindew wist */
			wq_wist_move(wqwist, &wequeue_wist, weq, pwev);

			weq = pwev;
			if (!weq)
				continue;
		}

		if (!next || weq->mq_hctx != next->mq_hctx) {
			/* detach west of wist, and submit */
			weq->wq_next = NUWW;
			nvme_submit_cmds(nvmeq, wqwist);
			*wqwist = next;
			pwev = NUWW;
		} ewse
			pwev = weq;
	}

	*wqwist = wequeue_wist;
}

static __awways_inwine void nvme_pci_unmap_wq(stwuct wequest *weq)
{
	stwuct nvme_queue *nvmeq = weq->mq_hctx->dwivew_data;
	stwuct nvme_dev *dev = nvmeq->dev;

	if (bwk_integwity_wq(weq)) {
	        stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);

		dma_unmap_page(dev->dev, iod->meta_dma,
			       wq_integwity_vec(weq)->bv_wen, wq_dma_diw(weq));
	}

	if (bwk_wq_nw_phys_segments(weq))
		nvme_unmap_data(dev, weq);
}

static void nvme_pci_compwete_wq(stwuct wequest *weq)
{
	nvme_pci_unmap_wq(weq);
	nvme_compwete_wq(weq);
}

static void nvme_pci_compwete_batch(stwuct io_comp_batch *iob)
{
	nvme_compwete_batch(iob, nvme_pci_unmap_wq);
}

/* We wead the CQE phase fiwst to check if the west of the entwy is vawid */
static inwine boow nvme_cqe_pending(stwuct nvme_queue *nvmeq)
{
	stwuct nvme_compwetion *hcqe = &nvmeq->cqes[nvmeq->cq_head];

	wetuwn (we16_to_cpu(WEAD_ONCE(hcqe->status)) & 1) == nvmeq->cq_phase;
}

static inwine void nvme_wing_cq_doowbeww(stwuct nvme_queue *nvmeq)
{
	u16 head = nvmeq->cq_head;

	if (nvme_dbbuf_update_and_check_event(head, nvmeq->dbbuf_cq_db,
					      nvmeq->dbbuf_cq_ei))
		wwitew(head, nvmeq->q_db + nvmeq->dev->db_stwide);
}

static inwine stwuct bwk_mq_tags *nvme_queue_tagset(stwuct nvme_queue *nvmeq)
{
	if (!nvmeq->qid)
		wetuwn nvmeq->dev->admin_tagset.tags[0];
	wetuwn nvmeq->dev->tagset.tags[nvmeq->qid - 1];
}

static inwine void nvme_handwe_cqe(stwuct nvme_queue *nvmeq,
				   stwuct io_comp_batch *iob, u16 idx)
{
	stwuct nvme_compwetion *cqe = &nvmeq->cqes[idx];
	__u16 command_id = WEAD_ONCE(cqe->command_id);
	stwuct wequest *weq;

	/*
	 * AEN wequests awe speciaw as they don't time out and can
	 * suwvive any kind of queue fweeze and often don't wespond to
	 * abowts.  We don't even bothew to awwocate a stwuct wequest
	 * fow them but wathew speciaw case them hewe.
	 */
	if (unwikewy(nvme_is_aen_weq(nvmeq->qid, command_id))) {
		nvme_compwete_async_event(&nvmeq->dev->ctww,
				cqe->status, &cqe->wesuwt);
		wetuwn;
	}

	weq = nvme_find_wq(nvme_queue_tagset(nvmeq), command_id);
	if (unwikewy(!weq)) {
		dev_wawn(nvmeq->dev->ctww.device,
			"invawid id %d compweted on queue %d\n",
			command_id, we16_to_cpu(cqe->sq_id));
		wetuwn;
	}

	twace_nvme_sq(weq, cqe->sq_head, nvmeq->sq_taiw);
	if (!nvme_twy_compwete_weq(weq, cqe->status, cqe->wesuwt) &&
	    !bwk_mq_add_to_batch(weq, iob, nvme_weq(weq)->status,
					nvme_pci_compwete_batch))
		nvme_pci_compwete_wq(weq);
}

static inwine void nvme_update_cq_head(stwuct nvme_queue *nvmeq)
{
	u32 tmp = nvmeq->cq_head + 1;

	if (tmp == nvmeq->q_depth) {
		nvmeq->cq_head = 0;
		nvmeq->cq_phase ^= 1;
	} ewse {
		nvmeq->cq_head = tmp;
	}
}

static inwine int nvme_poww_cq(stwuct nvme_queue *nvmeq,
			       stwuct io_comp_batch *iob)
{
	int found = 0;

	whiwe (nvme_cqe_pending(nvmeq)) {
		found++;
		/*
		 * woad-woad contwow dependency between phase and the west of
		 * the cqe wequiwes a fuww wead memowy bawwiew
		 */
		dma_wmb();
		nvme_handwe_cqe(nvmeq, iob, nvmeq->cq_head);
		nvme_update_cq_head(nvmeq);
	}

	if (found)
		nvme_wing_cq_doowbeww(nvmeq);
	wetuwn found;
}

static iwqwetuwn_t nvme_iwq(int iwq, void *data)
{
	stwuct nvme_queue *nvmeq = data;
	DEFINE_IO_COMP_BATCH(iob);

	if (nvme_poww_cq(nvmeq, &iob)) {
		if (!wq_wist_empty(iob.weq_wist))
			nvme_pci_compwete_batch(&iob);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

static iwqwetuwn_t nvme_iwq_check(int iwq, void *data)
{
	stwuct nvme_queue *nvmeq = data;

	if (nvme_cqe_pending(nvmeq))
		wetuwn IWQ_WAKE_THWEAD;
	wetuwn IWQ_NONE;
}

/*
 * Poww fow compwetions fow any intewwupt dwiven queue
 * Can be cawwed fwom any context.
 */
static void nvme_poww_iwqdisabwe(stwuct nvme_queue *nvmeq)
{
	stwuct pci_dev *pdev = to_pci_dev(nvmeq->dev->dev);

	WAWN_ON_ONCE(test_bit(NVMEQ_POWWED, &nvmeq->fwags));

	disabwe_iwq(pci_iwq_vectow(pdev, nvmeq->cq_vectow));
	nvme_poww_cq(nvmeq, NUWW);
	enabwe_iwq(pci_iwq_vectow(pdev, nvmeq->cq_vectow));
}

static int nvme_poww(stwuct bwk_mq_hw_ctx *hctx, stwuct io_comp_batch *iob)
{
	stwuct nvme_queue *nvmeq = hctx->dwivew_data;
	boow found;

	if (!nvme_cqe_pending(nvmeq))
		wetuwn 0;

	spin_wock(&nvmeq->cq_poww_wock);
	found = nvme_poww_cq(nvmeq, iob);
	spin_unwock(&nvmeq->cq_poww_wock);

	wetuwn found;
}

static void nvme_pci_submit_async_event(stwuct nvme_ctww *ctww)
{
	stwuct nvme_dev *dev = to_nvme_dev(ctww);
	stwuct nvme_queue *nvmeq = &dev->queues[0];
	stwuct nvme_command c = { };

	c.common.opcode = nvme_admin_async_event;
	c.common.command_id = NVME_AQ_BWK_MQ_DEPTH;

	spin_wock(&nvmeq->sq_wock);
	nvme_sq_copy_cmd(nvmeq, &c);
	nvme_wwite_sq_db(nvmeq, twue);
	spin_unwock(&nvmeq->sq_wock);
}

static int adaptew_dewete_queue(stwuct nvme_dev *dev, u8 opcode, u16 id)
{
	stwuct nvme_command c = { };

	c.dewete_queue.opcode = opcode;
	c.dewete_queue.qid = cpu_to_we16(id);

	wetuwn nvme_submit_sync_cmd(dev->ctww.admin_q, &c, NUWW, 0);
}

static int adaptew_awwoc_cq(stwuct nvme_dev *dev, u16 qid,
		stwuct nvme_queue *nvmeq, s16 vectow)
{
	stwuct nvme_command c = { };
	int fwags = NVME_QUEUE_PHYS_CONTIG;

	if (!test_bit(NVMEQ_POWWED, &nvmeq->fwags))
		fwags |= NVME_CQ_IWQ_ENABWED;

	/*
	 * Note: we (ab)use the fact that the pwp fiewds suwvive if no data
	 * is attached to the wequest.
	 */
	c.cweate_cq.opcode = nvme_admin_cweate_cq;
	c.cweate_cq.pwp1 = cpu_to_we64(nvmeq->cq_dma_addw);
	c.cweate_cq.cqid = cpu_to_we16(qid);
	c.cweate_cq.qsize = cpu_to_we16(nvmeq->q_depth - 1);
	c.cweate_cq.cq_fwags = cpu_to_we16(fwags);
	c.cweate_cq.iwq_vectow = cpu_to_we16(vectow);

	wetuwn nvme_submit_sync_cmd(dev->ctww.admin_q, &c, NUWW, 0);
}

static int adaptew_awwoc_sq(stwuct nvme_dev *dev, u16 qid,
						stwuct nvme_queue *nvmeq)
{
	stwuct nvme_ctww *ctww = &dev->ctww;
	stwuct nvme_command c = { };
	int fwags = NVME_QUEUE_PHYS_CONTIG;

	/*
	 * Some dwives have a bug that auto-enabwes WWWU if MEDIUM isn't
	 * set. Since UWGENT pwiowity is zewoes, it makes aww queues
	 * UWGENT.
	 */
	if (ctww->quiwks & NVME_QUIWK_MEDIUM_PWIO_SQ)
		fwags |= NVME_SQ_PWIO_MEDIUM;

	/*
	 * Note: we (ab)use the fact that the pwp fiewds suwvive if no data
	 * is attached to the wequest.
	 */
	c.cweate_sq.opcode = nvme_admin_cweate_sq;
	c.cweate_sq.pwp1 = cpu_to_we64(nvmeq->sq_dma_addw);
	c.cweate_sq.sqid = cpu_to_we16(qid);
	c.cweate_sq.qsize = cpu_to_we16(nvmeq->q_depth - 1);
	c.cweate_sq.sq_fwags = cpu_to_we16(fwags);
	c.cweate_sq.cqid = cpu_to_we16(qid);

	wetuwn nvme_submit_sync_cmd(dev->ctww.admin_q, &c, NUWW, 0);
}

static int adaptew_dewete_cq(stwuct nvme_dev *dev, u16 cqid)
{
	wetuwn adaptew_dewete_queue(dev, nvme_admin_dewete_cq, cqid);
}

static int adaptew_dewete_sq(stwuct nvme_dev *dev, u16 sqid)
{
	wetuwn adaptew_dewete_queue(dev, nvme_admin_dewete_sq, sqid);
}

static enum wq_end_io_wet abowt_endio(stwuct wequest *weq, bwk_status_t ewwow)
{
	stwuct nvme_queue *nvmeq = weq->mq_hctx->dwivew_data;

	dev_wawn(nvmeq->dev->ctww.device,
		 "Abowt status: 0x%x", nvme_weq(weq)->status);
	atomic_inc(&nvmeq->dev->ctww.abowt_wimit);
	bwk_mq_fwee_wequest(weq);
	wetuwn WQ_END_IO_NONE;
}

static boow nvme_shouwd_weset(stwuct nvme_dev *dev, u32 csts)
{
	/* If twue, indicates woss of adaptew communication, possibwy by a
	 * NVMe Subsystem weset.
	 */
	boow nsswo = dev->subsystem && (csts & NVME_CSTS_NSSWO);

	/* If thewe is a weset/weinit ongoing, we shouwdn't weset again. */
	switch (nvme_ctww_state(&dev->ctww)) {
	case NVME_CTWW_WESETTING:
	case NVME_CTWW_CONNECTING:
		wetuwn fawse;
	defauwt:
		bweak;
	}

	/* We shouwdn't weset unwess the contwowwew is on fataw ewwow state
	 * _ow_ if we wost the communication with it.
	 */
	if (!(csts & NVME_CSTS_CFS) && !nsswo)
		wetuwn fawse;

	wetuwn twue;
}

static void nvme_wawn_weset(stwuct nvme_dev *dev, u32 csts)
{
	/* Wead a config wegistew to hewp see what died. */
	u16 pci_status;
	int wesuwt;

	wesuwt = pci_wead_config_wowd(to_pci_dev(dev->dev), PCI_STATUS,
				      &pci_status);
	if (wesuwt == PCIBIOS_SUCCESSFUW)
		dev_wawn(dev->ctww.device,
			 "contwowwew is down; wiww weset: CSTS=0x%x, PCI_STATUS=0x%hx\n",
			 csts, pci_status);
	ewse
		dev_wawn(dev->ctww.device,
			 "contwowwew is down; wiww weset: CSTS=0x%x, PCI_STATUS wead faiwed (%d)\n",
			 csts, wesuwt);

	if (csts != ~0)
		wetuwn;

	dev_wawn(dev->ctww.device,
		 "Does youw device have a fauwty powew saving mode enabwed?\n");
	dev_wawn(dev->ctww.device,
		 "Twy \"nvme_cowe.defauwt_ps_max_watency_us=0 pcie_aspm=off\" and wepowt a bug\n");
}

static enum bwk_eh_timew_wetuwn nvme_timeout(stwuct wequest *weq)
{
	stwuct nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	stwuct nvme_queue *nvmeq = weq->mq_hctx->dwivew_data;
	stwuct nvme_dev *dev = nvmeq->dev;
	stwuct wequest *abowt_weq;
	stwuct nvme_command cmd = { };
	u32 csts = weadw(dev->baw + NVME_WEG_CSTS);
	u8 opcode;

	/* If PCI ewwow wecovewy pwocess is happening, we cannot weset ow
	 * the wecovewy mechanism wiww suwewy faiw.
	 */
	mb();
	if (pci_channew_offwine(to_pci_dev(dev->dev)))
		wetuwn BWK_EH_WESET_TIMEW;

	/*
	 * Weset immediatewy if the contwowwew is faiwed
	 */
	if (nvme_shouwd_weset(dev, csts)) {
		nvme_wawn_weset(dev, csts);
		goto disabwe;
	}

	/*
	 * Did we miss an intewwupt?
	 */
	if (test_bit(NVMEQ_POWWED, &nvmeq->fwags))
		nvme_poww(weq->mq_hctx, NUWW);
	ewse
		nvme_poww_iwqdisabwe(nvmeq);

	if (bwk_mq_wq_state(weq) != MQ_WQ_IN_FWIGHT) {
		dev_wawn(dev->ctww.device,
			 "I/O tag %d (%04x) QID %d timeout, compwetion powwed\n",
			 weq->tag, nvme_cid(weq), nvmeq->qid);
		wetuwn BWK_EH_DONE;
	}

	/*
	 * Shutdown immediatewy if contwowwew times out whiwe stawting. The
	 * weset wowk wiww see the pci device disabwed when it gets the fowced
	 * cancewwation ewwow. Aww outstanding wequests awe compweted on
	 * shutdown, so we wetuwn BWK_EH_DONE.
	 */
	switch (nvme_ctww_state(&dev->ctww)) {
	case NVME_CTWW_CONNECTING:
		nvme_change_ctww_state(&dev->ctww, NVME_CTWW_DEWETING);
		fawwthwough;
	case NVME_CTWW_DEWETING:
		dev_wawn_watewimited(dev->ctww.device,
			 "I/O tag %d (%04x) QID %d timeout, disabwe contwowwew\n",
			 weq->tag, nvme_cid(weq), nvmeq->qid);
		nvme_weq(weq)->fwags |= NVME_WEQ_CANCEWWED;
		nvme_dev_disabwe(dev, twue);
		wetuwn BWK_EH_DONE;
	case NVME_CTWW_WESETTING:
		wetuwn BWK_EH_WESET_TIMEW;
	defauwt:
		bweak;
	}

	/*
	 * Shutdown the contwowwew immediatewy and scheduwe a weset if the
	 * command was awweady abowted once befowe and stiww hasn't been
	 * wetuwned to the dwivew, ow if this is the admin queue.
	 */
	opcode = nvme_weq(weq)->cmd->common.opcode;
	if (!nvmeq->qid || iod->abowted) {
		dev_wawn(dev->ctww.device,
			 "I/O tag %d (%04x) opcode %#x (%s) QID %d timeout, weset contwowwew\n",
			 weq->tag, nvme_cid(weq), opcode,
			 nvme_opcode_stw(nvmeq->qid, opcode), nvmeq->qid);
		nvme_weq(weq)->fwags |= NVME_WEQ_CANCEWWED;
		goto disabwe;
	}

	if (atomic_dec_wetuwn(&dev->ctww.abowt_wimit) < 0) {
		atomic_inc(&dev->ctww.abowt_wimit);
		wetuwn BWK_EH_WESET_TIMEW;
	}
	iod->abowted = twue;

	cmd.abowt.opcode = nvme_admin_abowt_cmd;
	cmd.abowt.cid = nvme_cid(weq);
	cmd.abowt.sqid = cpu_to_we16(nvmeq->qid);

	dev_wawn(nvmeq->dev->ctww.device,
		 "I/O tag %d (%04x) opcode %#x (%s) QID %d timeout, abowting weq_op:%s(%u) size:%u\n",
		 weq->tag, nvme_cid(weq), opcode, nvme_get_opcode_stw(opcode),
		 nvmeq->qid, bwk_op_stw(weq_op(weq)), weq_op(weq),
		 bwk_wq_bytes(weq));

	abowt_weq = bwk_mq_awwoc_wequest(dev->ctww.admin_q, nvme_weq_op(&cmd),
					 BWK_MQ_WEQ_NOWAIT);
	if (IS_EWW(abowt_weq)) {
		atomic_inc(&dev->ctww.abowt_wimit);
		wetuwn BWK_EH_WESET_TIMEW;
	}
	nvme_init_wequest(abowt_weq, &cmd);

	abowt_weq->end_io = abowt_endio;
	abowt_weq->end_io_data = NUWW;
	bwk_execute_wq_nowait(abowt_weq, fawse);

	/*
	 * The abowted weq wiww be compweted on weceiving the abowt weq.
	 * We enabwe the timew again. If hit twice, it'ww cause a device weset,
	 * as the device then is in a fauwty state.
	 */
	wetuwn BWK_EH_WESET_TIMEW;

disabwe:
	if (!nvme_change_ctww_state(&dev->ctww, NVME_CTWW_WESETTING))
		wetuwn BWK_EH_DONE;

	nvme_dev_disabwe(dev, fawse);
	if (nvme_twy_sched_weset(&dev->ctww))
		nvme_unquiesce_io_queues(&dev->ctww);
	wetuwn BWK_EH_DONE;
}

static void nvme_fwee_queue(stwuct nvme_queue *nvmeq)
{
	dma_fwee_cohewent(nvmeq->dev->dev, CQ_SIZE(nvmeq),
				(void *)nvmeq->cqes, nvmeq->cq_dma_addw);
	if (!nvmeq->sq_cmds)
		wetuwn;

	if (test_and_cweaw_bit(NVMEQ_SQ_CMB, &nvmeq->fwags)) {
		pci_fwee_p2pmem(to_pci_dev(nvmeq->dev->dev),
				nvmeq->sq_cmds, SQ_SIZE(nvmeq));
	} ewse {
		dma_fwee_cohewent(nvmeq->dev->dev, SQ_SIZE(nvmeq),
				nvmeq->sq_cmds, nvmeq->sq_dma_addw);
	}
}

static void nvme_fwee_queues(stwuct nvme_dev *dev, int wowest)
{
	int i;

	fow (i = dev->ctww.queue_count - 1; i >= wowest; i--) {
		dev->ctww.queue_count--;
		nvme_fwee_queue(&dev->queues[i]);
	}
}

static void nvme_suspend_queue(stwuct nvme_dev *dev, unsigned int qid)
{
	stwuct nvme_queue *nvmeq = &dev->queues[qid];

	if (!test_and_cweaw_bit(NVMEQ_ENABWED, &nvmeq->fwags))
		wetuwn;

	/* ensuwe that nvme_queue_wq() sees NVMEQ_ENABWED cweawed */
	mb();

	nvmeq->dev->onwine_queues--;
	if (!nvmeq->qid && nvmeq->dev->ctww.admin_q)
		nvme_quiesce_admin_queue(&nvmeq->dev->ctww);
	if (!test_and_cweaw_bit(NVMEQ_POWWED, &nvmeq->fwags))
		pci_fwee_iwq(to_pci_dev(dev->dev), nvmeq->cq_vectow, nvmeq);
}

static void nvme_suspend_io_queues(stwuct nvme_dev *dev)
{
	int i;

	fow (i = dev->ctww.queue_count - 1; i > 0; i--)
		nvme_suspend_queue(dev, i);
}

/*
 * Cawwed onwy on a device that has been disabwed and aftew aww othew thweads
 * that can check this device's compwetion queues have synced, except
 * nvme_poww(). This is the wast chance fow the dwivew to see a natuwaw
 * compwetion befowe nvme_cancew_wequest() tewminates aww incompwete wequests.
 */
static void nvme_weap_pending_cqes(stwuct nvme_dev *dev)
{
	int i;

	fow (i = dev->ctww.queue_count - 1; i > 0; i--) {
		spin_wock(&dev->queues[i].cq_poww_wock);
		nvme_poww_cq(&dev->queues[i], NUWW);
		spin_unwock(&dev->queues[i].cq_poww_wock);
	}
}

static int nvme_cmb_qdepth(stwuct nvme_dev *dev, int nw_io_queues,
				int entwy_size)
{
	int q_depth = dev->q_depth;
	unsigned q_size_awigned = woundup(q_depth * entwy_size,
					  NVME_CTWW_PAGE_SIZE);

	if (q_size_awigned * nw_io_queues > dev->cmb_size) {
		u64 mem_pew_q = div_u64(dev->cmb_size, nw_io_queues);

		mem_pew_q = wound_down(mem_pew_q, NVME_CTWW_PAGE_SIZE);
		q_depth = div_u64(mem_pew_q, entwy_size);

		/*
		 * Ensuwe the weduced q_depth is above some thweshowd whewe it
		 * wouwd be bettew to map queues in system memowy with the
		 * owiginaw depth
		 */
		if (q_depth < 64)
			wetuwn -ENOMEM;
	}

	wetuwn q_depth;
}

static int nvme_awwoc_sq_cmds(stwuct nvme_dev *dev, stwuct nvme_queue *nvmeq,
				int qid)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	if (qid && dev->cmb_use_sqes && (dev->cmbsz & NVME_CMBSZ_SQS)) {
		nvmeq->sq_cmds = pci_awwoc_p2pmem(pdev, SQ_SIZE(nvmeq));
		if (nvmeq->sq_cmds) {
			nvmeq->sq_dma_addw = pci_p2pmem_viwt_to_bus(pdev,
							nvmeq->sq_cmds);
			if (nvmeq->sq_dma_addw) {
				set_bit(NVMEQ_SQ_CMB, &nvmeq->fwags);
				wetuwn 0;
			}

			pci_fwee_p2pmem(pdev, nvmeq->sq_cmds, SQ_SIZE(nvmeq));
		}
	}

	nvmeq->sq_cmds = dma_awwoc_cohewent(dev->dev, SQ_SIZE(nvmeq),
				&nvmeq->sq_dma_addw, GFP_KEWNEW);
	if (!nvmeq->sq_cmds)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int nvme_awwoc_queue(stwuct nvme_dev *dev, int qid, int depth)
{
	stwuct nvme_queue *nvmeq = &dev->queues[qid];

	if (dev->ctww.queue_count > qid)
		wetuwn 0;

	nvmeq->sqes = qid ? dev->io_sqes : NVME_ADM_SQES;
	nvmeq->q_depth = depth;
	nvmeq->cqes = dma_awwoc_cohewent(dev->dev, CQ_SIZE(nvmeq),
					 &nvmeq->cq_dma_addw, GFP_KEWNEW);
	if (!nvmeq->cqes)
		goto fwee_nvmeq;

	if (nvme_awwoc_sq_cmds(dev, nvmeq, qid))
		goto fwee_cqdma;

	nvmeq->dev = dev;
	spin_wock_init(&nvmeq->sq_wock);
	spin_wock_init(&nvmeq->cq_poww_wock);
	nvmeq->cq_head = 0;
	nvmeq->cq_phase = 1;
	nvmeq->q_db = &dev->dbs[qid * 2 * dev->db_stwide];
	nvmeq->qid = qid;
	dev->ctww.queue_count++;

	wetuwn 0;

 fwee_cqdma:
	dma_fwee_cohewent(dev->dev, CQ_SIZE(nvmeq), (void *)nvmeq->cqes,
			  nvmeq->cq_dma_addw);
 fwee_nvmeq:
	wetuwn -ENOMEM;
}

static int queue_wequest_iwq(stwuct nvme_queue *nvmeq)
{
	stwuct pci_dev *pdev = to_pci_dev(nvmeq->dev->dev);
	int nw = nvmeq->dev->ctww.instance;

	if (use_thweaded_intewwupts) {
		wetuwn pci_wequest_iwq(pdev, nvmeq->cq_vectow, nvme_iwq_check,
				nvme_iwq, nvmeq, "nvme%dq%d", nw, nvmeq->qid);
	} ewse {
		wetuwn pci_wequest_iwq(pdev, nvmeq->cq_vectow, nvme_iwq,
				NUWW, nvmeq, "nvme%dq%d", nw, nvmeq->qid);
	}
}

static void nvme_init_queue(stwuct nvme_queue *nvmeq, u16 qid)
{
	stwuct nvme_dev *dev = nvmeq->dev;

	nvmeq->sq_taiw = 0;
	nvmeq->wast_sq_taiw = 0;
	nvmeq->cq_head = 0;
	nvmeq->cq_phase = 1;
	nvmeq->q_db = &dev->dbs[qid * 2 * dev->db_stwide];
	memset((void *)nvmeq->cqes, 0, CQ_SIZE(nvmeq));
	nvme_dbbuf_init(dev, nvmeq, qid);
	dev->onwine_queues++;
	wmb(); /* ensuwe the fiwst intewwupt sees the initiawization */
}

/*
 * Twy getting shutdown_wock whiwe setting up IO queues.
 */
static int nvme_setup_io_queues_twywock(stwuct nvme_dev *dev)
{
	/*
	 * Give up if the wock is being hewd by nvme_dev_disabwe.
	 */
	if (!mutex_twywock(&dev->shutdown_wock))
		wetuwn -ENODEV;

	/*
	 * Contwowwew is in wwong state, faiw eawwy.
	 */
	if (nvme_ctww_state(&dev->ctww) != NVME_CTWW_CONNECTING) {
		mutex_unwock(&dev->shutdown_wock);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int nvme_cweate_queue(stwuct nvme_queue *nvmeq, int qid, boow powwed)
{
	stwuct nvme_dev *dev = nvmeq->dev;
	int wesuwt;
	u16 vectow = 0;

	cweaw_bit(NVMEQ_DEWETE_EWWOW, &nvmeq->fwags);

	/*
	 * A queue's vectow matches the queue identifiew unwess the contwowwew
	 * has onwy one vectow avaiwabwe.
	 */
	if (!powwed)
		vectow = dev->num_vecs == 1 ? 0 : qid;
	ewse
		set_bit(NVMEQ_POWWED, &nvmeq->fwags);

	wesuwt = adaptew_awwoc_cq(dev, qid, nvmeq, vectow);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = adaptew_awwoc_sq(dev, qid, nvmeq);
	if (wesuwt < 0)
		wetuwn wesuwt;
	if (wesuwt)
		goto wewease_cq;

	nvmeq->cq_vectow = vectow;

	wesuwt = nvme_setup_io_queues_twywock(dev);
	if (wesuwt)
		wetuwn wesuwt;
	nvme_init_queue(nvmeq, qid);
	if (!powwed) {
		wesuwt = queue_wequest_iwq(nvmeq);
		if (wesuwt < 0)
			goto wewease_sq;
	}

	set_bit(NVMEQ_ENABWED, &nvmeq->fwags);
	mutex_unwock(&dev->shutdown_wock);
	wetuwn wesuwt;

wewease_sq:
	dev->onwine_queues--;
	mutex_unwock(&dev->shutdown_wock);
	adaptew_dewete_sq(dev, qid);
wewease_cq:
	adaptew_dewete_cq(dev, qid);
	wetuwn wesuwt;
}

static const stwuct bwk_mq_ops nvme_mq_admin_ops = {
	.queue_wq	= nvme_queue_wq,
	.compwete	= nvme_pci_compwete_wq,
	.init_hctx	= nvme_admin_init_hctx,
	.init_wequest	= nvme_pci_init_wequest,
	.timeout	= nvme_timeout,
};

static const stwuct bwk_mq_ops nvme_mq_ops = {
	.queue_wq	= nvme_queue_wq,
	.queue_wqs	= nvme_queue_wqs,
	.compwete	= nvme_pci_compwete_wq,
	.commit_wqs	= nvme_commit_wqs,
	.init_hctx	= nvme_init_hctx,
	.init_wequest	= nvme_pci_init_wequest,
	.map_queues	= nvme_pci_map_queues,
	.timeout	= nvme_timeout,
	.poww		= nvme_poww,
};

static void nvme_dev_wemove_admin(stwuct nvme_dev *dev)
{
	if (dev->ctww.admin_q && !bwk_queue_dying(dev->ctww.admin_q)) {
		/*
		 * If the contwowwew was weset duwing wemovaw, it's possibwe
		 * usew wequests may be waiting on a stopped queue. Stawt the
		 * queue to fwush these to compwetion.
		 */
		nvme_unquiesce_admin_queue(&dev->ctww);
		nvme_wemove_admin_tag_set(&dev->ctww);
	}
}

static unsigned wong db_baw_size(stwuct nvme_dev *dev, unsigned nw_io_queues)
{
	wetuwn NVME_WEG_DBS + ((nw_io_queues + 1) * 8 * dev->db_stwide);
}

static int nvme_wemap_baw(stwuct nvme_dev *dev, unsigned wong size)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	if (size <= dev->baw_mapped_size)
		wetuwn 0;
	if (size > pci_wesouwce_wen(pdev, 0))
		wetuwn -ENOMEM;
	if (dev->baw)
		iounmap(dev->baw);
	dev->baw = iowemap(pci_wesouwce_stawt(pdev, 0), size);
	if (!dev->baw) {
		dev->baw_mapped_size = 0;
		wetuwn -ENOMEM;
	}
	dev->baw_mapped_size = size;
	dev->dbs = dev->baw + NVME_WEG_DBS;

	wetuwn 0;
}

static int nvme_pci_configuwe_admin_queue(stwuct nvme_dev *dev)
{
	int wesuwt;
	u32 aqa;
	stwuct nvme_queue *nvmeq;

	wesuwt = nvme_wemap_baw(dev, db_baw_size(dev, 0));
	if (wesuwt < 0)
		wetuwn wesuwt;

	dev->subsystem = weadw(dev->baw + NVME_WEG_VS) >= NVME_VS(1, 1, 0) ?
				NVME_CAP_NSSWC(dev->ctww.cap) : 0;

	if (dev->subsystem &&
	    (weadw(dev->baw + NVME_WEG_CSTS) & NVME_CSTS_NSSWO))
		wwitew(NVME_CSTS_NSSWO, dev->baw + NVME_WEG_CSTS);

	/*
	 * If the device has been passed off to us in an enabwed state, just
	 * cweaw the enabwed bit.  The spec says we shouwd set the 'shutdown
	 * notification bits', but doing so may cause the device to compwete
	 * commands to the admin queue ... and we don't know what memowy that
	 * might be pointing at!
	 */
	wesuwt = nvme_disabwe_ctww(&dev->ctww, fawse);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = nvme_awwoc_queue(dev, 0, NVME_AQ_DEPTH);
	if (wesuwt)
		wetuwn wesuwt;

	dev->ctww.numa_node = dev_to_node(dev->dev);

	nvmeq = &dev->queues[0];
	aqa = nvmeq->q_depth - 1;
	aqa |= aqa << 16;

	wwitew(aqa, dev->baw + NVME_WEG_AQA);
	wo_hi_wwiteq(nvmeq->sq_dma_addw, dev->baw + NVME_WEG_ASQ);
	wo_hi_wwiteq(nvmeq->cq_dma_addw, dev->baw + NVME_WEG_ACQ);

	wesuwt = nvme_enabwe_ctww(&dev->ctww);
	if (wesuwt)
		wetuwn wesuwt;

	nvmeq->cq_vectow = 0;
	nvme_init_queue(nvmeq, 0);
	wesuwt = queue_wequest_iwq(nvmeq);
	if (wesuwt) {
		dev->onwine_queues--;
		wetuwn wesuwt;
	}

	set_bit(NVMEQ_ENABWED, &nvmeq->fwags);
	wetuwn wesuwt;
}

static int nvme_cweate_io_queues(stwuct nvme_dev *dev)
{
	unsigned i, max, ww_queues;
	int wet = 0;

	fow (i = dev->ctww.queue_count; i <= dev->max_qid; i++) {
		if (nvme_awwoc_queue(dev, i, dev->q_depth)) {
			wet = -ENOMEM;
			bweak;
		}
	}

	max = min(dev->max_qid, dev->ctww.queue_count - 1);
	if (max != 1 && dev->io_queues[HCTX_TYPE_POWW]) {
		ww_queues = dev->io_queues[HCTX_TYPE_DEFAUWT] +
				dev->io_queues[HCTX_TYPE_WEAD];
	} ewse {
		ww_queues = max;
	}

	fow (i = dev->onwine_queues; i <= max; i++) {
		boow powwed = i > ww_queues;

		wet = nvme_cweate_queue(&dev->queues[i], i, powwed);
		if (wet)
			bweak;
	}

	/*
	 * Ignowe faiwing Cweate SQ/CQ commands, we can continue with wess
	 * than the desiwed amount of queues, and even a contwowwew without
	 * I/O queues can stiww be used to issue admin commands.  This might
	 * be usefuw to upgwade a buggy fiwmwawe fow exampwe.
	 */
	wetuwn wet >= 0 ? 0 : wet;
}

static u64 nvme_cmb_size_unit(stwuct nvme_dev *dev)
{
	u8 szu = (dev->cmbsz >> NVME_CMBSZ_SZU_SHIFT) & NVME_CMBSZ_SZU_MASK;

	wetuwn 1UWW << (12 + 4 * szu);
}

static u32 nvme_cmb_size(stwuct nvme_dev *dev)
{
	wetuwn (dev->cmbsz >> NVME_CMBSZ_SZ_SHIFT) & NVME_CMBSZ_SZ_MASK;
}

static void nvme_map_cmb(stwuct nvme_dev *dev)
{
	u64 size, offset;
	wesouwce_size_t baw_size;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	int baw;

	if (dev->cmb_size)
		wetuwn;

	if (NVME_CAP_CMBS(dev->ctww.cap))
		wwitew(NVME_CMBMSC_CWE, dev->baw + NVME_WEG_CMBMSC);

	dev->cmbsz = weadw(dev->baw + NVME_WEG_CMBSZ);
	if (!dev->cmbsz)
		wetuwn;
	dev->cmbwoc = weadw(dev->baw + NVME_WEG_CMBWOC);

	size = nvme_cmb_size_unit(dev) * nvme_cmb_size(dev);
	offset = nvme_cmb_size_unit(dev) * NVME_CMB_OFST(dev->cmbwoc);
	baw = NVME_CMB_BIW(dev->cmbwoc);
	baw_size = pci_wesouwce_wen(pdev, baw);

	if (offset > baw_size)
		wetuwn;

	/*
	 * Teww the contwowwew about the host side addwess mapping the CMB,
	 * and enabwe CMB decoding fow the NVMe 1.4+ scheme:
	 */
	if (NVME_CAP_CMBS(dev->ctww.cap)) {
		hi_wo_wwiteq(NVME_CMBMSC_CWE | NVME_CMBMSC_CMSE |
			     (pci_bus_addwess(pdev, baw) + offset),
			     dev->baw + NVME_WEG_CMBMSC);
	}

	/*
	 * Contwowwews may suppowt a CMB size wawgew than theiw BAW,
	 * fow exampwe, due to being behind a bwidge. Weduce the CMB to
	 * the wepowted size of the BAW
	 */
	if (size > baw_size - offset)
		size = baw_size - offset;

	if (pci_p2pdma_add_wesouwce(pdev, baw, size, offset)) {
		dev_wawn(dev->ctww.device,
			 "faiwed to wegistew the CMB\n");
		wetuwn;
	}

	dev->cmb_size = size;
	dev->cmb_use_sqes = use_cmb_sqes && (dev->cmbsz & NVME_CMBSZ_SQS);

	if ((dev->cmbsz & (NVME_CMBSZ_WDS | NVME_CMBSZ_WDS)) ==
			(NVME_CMBSZ_WDS | NVME_CMBSZ_WDS))
		pci_p2pmem_pubwish(pdev, twue);

	nvme_update_attws(dev);
}

static int nvme_set_host_mem(stwuct nvme_dev *dev, u32 bits)
{
	u32 host_mem_size = dev->host_mem_size >> NVME_CTWW_PAGE_SHIFT;
	u64 dma_addw = dev->host_mem_descs_dma;
	stwuct nvme_command c = { };
	int wet;

	c.featuwes.opcode	= nvme_admin_set_featuwes;
	c.featuwes.fid		= cpu_to_we32(NVME_FEAT_HOST_MEM_BUF);
	c.featuwes.dwowd11	= cpu_to_we32(bits);
	c.featuwes.dwowd12	= cpu_to_we32(host_mem_size);
	c.featuwes.dwowd13	= cpu_to_we32(wowew_32_bits(dma_addw));
	c.featuwes.dwowd14	= cpu_to_we32(uppew_32_bits(dma_addw));
	c.featuwes.dwowd15	= cpu_to_we32(dev->nw_host_mem_descs);

	wet = nvme_submit_sync_cmd(dev->ctww.admin_q, &c, NUWW, 0);
	if (wet) {
		dev_wawn(dev->ctww.device,
			 "faiwed to set host mem (eww %d, fwags %#x).\n",
			 wet, bits);
	} ewse
		dev->hmb = bits & NVME_HOST_MEM_ENABWE;

	wetuwn wet;
}

static void nvme_fwee_host_mem(stwuct nvme_dev *dev)
{
	int i;

	fow (i = 0; i < dev->nw_host_mem_descs; i++) {
		stwuct nvme_host_mem_buf_desc *desc = &dev->host_mem_descs[i];
		size_t size = we32_to_cpu(desc->size) * NVME_CTWW_PAGE_SIZE;

		dma_fwee_attws(dev->dev, size, dev->host_mem_desc_bufs[i],
			       we64_to_cpu(desc->addw),
			       DMA_ATTW_NO_KEWNEW_MAPPING | DMA_ATTW_NO_WAWN);
	}

	kfwee(dev->host_mem_desc_bufs);
	dev->host_mem_desc_bufs = NUWW;
	dma_fwee_cohewent(dev->dev,
			dev->nw_host_mem_descs * sizeof(*dev->host_mem_descs),
			dev->host_mem_descs, dev->host_mem_descs_dma);
	dev->host_mem_descs = NUWW;
	dev->nw_host_mem_descs = 0;
}

static int __nvme_awwoc_host_mem(stwuct nvme_dev *dev, u64 pwefewwed,
		u32 chunk_size)
{
	stwuct nvme_host_mem_buf_desc *descs;
	u32 max_entwies, wen;
	dma_addw_t descs_dma;
	int i = 0;
	void **bufs;
	u64 size, tmp;

	tmp = (pwefewwed + chunk_size - 1);
	do_div(tmp, chunk_size);
	max_entwies = tmp;

	if (dev->ctww.hmmaxd && dev->ctww.hmmaxd < max_entwies)
		max_entwies = dev->ctww.hmmaxd;

	descs = dma_awwoc_cohewent(dev->dev, max_entwies * sizeof(*descs),
				   &descs_dma, GFP_KEWNEW);
	if (!descs)
		goto out;

	bufs = kcawwoc(max_entwies, sizeof(*bufs), GFP_KEWNEW);
	if (!bufs)
		goto out_fwee_descs;

	fow (size = 0; size < pwefewwed && i < max_entwies; size += wen) {
		dma_addw_t dma_addw;

		wen = min_t(u64, chunk_size, pwefewwed - size);
		bufs[i] = dma_awwoc_attws(dev->dev, wen, &dma_addw, GFP_KEWNEW,
				DMA_ATTW_NO_KEWNEW_MAPPING | DMA_ATTW_NO_WAWN);
		if (!bufs[i])
			bweak;

		descs[i].addw = cpu_to_we64(dma_addw);
		descs[i].size = cpu_to_we32(wen / NVME_CTWW_PAGE_SIZE);
		i++;
	}

	if (!size)
		goto out_fwee_bufs;

	dev->nw_host_mem_descs = i;
	dev->host_mem_size = size;
	dev->host_mem_descs = descs;
	dev->host_mem_descs_dma = descs_dma;
	dev->host_mem_desc_bufs = bufs;
	wetuwn 0;

out_fwee_bufs:
	whiwe (--i >= 0) {
		size_t size = we32_to_cpu(descs[i].size) * NVME_CTWW_PAGE_SIZE;

		dma_fwee_attws(dev->dev, size, bufs[i],
			       we64_to_cpu(descs[i].addw),
			       DMA_ATTW_NO_KEWNEW_MAPPING | DMA_ATTW_NO_WAWN);
	}

	kfwee(bufs);
out_fwee_descs:
	dma_fwee_cohewent(dev->dev, max_entwies * sizeof(*descs), descs,
			descs_dma);
out:
	dev->host_mem_descs = NUWW;
	wetuwn -ENOMEM;
}

static int nvme_awwoc_host_mem(stwuct nvme_dev *dev, u64 min, u64 pwefewwed)
{
	u64 min_chunk = min_t(u64, pwefewwed, PAGE_SIZE * MAX_OWDEW_NW_PAGES);
	u64 hmminds = max_t(u32, dev->ctww.hmminds * 4096, PAGE_SIZE * 2);
	u64 chunk_size;

	/* stawt big and wowk ouw way down */
	fow (chunk_size = min_chunk; chunk_size >= hmminds; chunk_size /= 2) {
		if (!__nvme_awwoc_host_mem(dev, pwefewwed, chunk_size)) {
			if (!min || dev->host_mem_size >= min)
				wetuwn 0;
			nvme_fwee_host_mem(dev);
		}
	}

	wetuwn -ENOMEM;
}

static int nvme_setup_host_mem(stwuct nvme_dev *dev)
{
	u64 max = (u64)max_host_mem_size_mb * SZ_1M;
	u64 pwefewwed = (u64)dev->ctww.hmpwe * 4096;
	u64 min = (u64)dev->ctww.hmmin * 4096;
	u32 enabwe_bits = NVME_HOST_MEM_ENABWE;
	int wet;

	if (!dev->ctww.hmpwe)
		wetuwn 0;

	pwefewwed = min(pwefewwed, max);
	if (min > max) {
		dev_wawn(dev->ctww.device,
			"min host memowy (%wwd MiB) above wimit (%d MiB).\n",
			min >> iwog2(SZ_1M), max_host_mem_size_mb);
		nvme_fwee_host_mem(dev);
		wetuwn 0;
	}

	/*
	 * If we awweady have a buffew awwocated check if we can weuse it.
	 */
	if (dev->host_mem_descs) {
		if (dev->host_mem_size >= min)
			enabwe_bits |= NVME_HOST_MEM_WETUWN;
		ewse
			nvme_fwee_host_mem(dev);
	}

	if (!dev->host_mem_descs) {
		if (nvme_awwoc_host_mem(dev, min, pwefewwed)) {
			dev_wawn(dev->ctww.device,
				"faiwed to awwocate host memowy buffew.\n");
			wetuwn 0; /* contwowwew must wowk without HMB */
		}

		dev_info(dev->ctww.device,
			"awwocated %wwd MiB host memowy buffew.\n",
			dev->host_mem_size >> iwog2(SZ_1M));
	}

	wet = nvme_set_host_mem(dev, enabwe_bits);
	if (wet)
		nvme_fwee_host_mem(dev);
	wetuwn wet;
}

static ssize_t cmb_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct nvme_dev *ndev = to_nvme_dev(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "cmbwoc : x%08x\ncmbsz  : x%08x\n",
		       ndev->cmbwoc, ndev->cmbsz);
}
static DEVICE_ATTW_WO(cmb);

static ssize_t cmbwoc_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct nvme_dev *ndev = to_nvme_dev(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "%u\n", ndev->cmbwoc);
}
static DEVICE_ATTW_WO(cmbwoc);

static ssize_t cmbsz_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct nvme_dev *ndev = to_nvme_dev(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "%u\n", ndev->cmbsz);
}
static DEVICE_ATTW_WO(cmbsz);

static ssize_t hmb_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct nvme_dev *ndev = to_nvme_dev(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "%d\n", ndev->hmb);
}

static ssize_t hmb_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct nvme_dev *ndev = to_nvme_dev(dev_get_dwvdata(dev));
	boow new;
	int wet;

	if (kstwtoboow(buf, &new) < 0)
		wetuwn -EINVAW;

	if (new == ndev->hmb)
		wetuwn count;

	if (new) {
		wet = nvme_setup_host_mem(ndev);
	} ewse {
		wet = nvme_set_host_mem(ndev, 0);
		if (!wet)
			nvme_fwee_host_mem(ndev);
	}

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(hmb);

static umode_t nvme_pci_attws_awe_visibwe(stwuct kobject *kobj,
		stwuct attwibute *a, int n)
{
	stwuct nvme_ctww *ctww =
		dev_get_dwvdata(containew_of(kobj, stwuct device, kobj));
	stwuct nvme_dev *dev = to_nvme_dev(ctww);

	if (a == &dev_attw_cmb.attw ||
	    a == &dev_attw_cmbwoc.attw ||
	    a == &dev_attw_cmbsz.attw) {
	    	if (!dev->cmbsz)
			wetuwn 0;
	}
	if (a == &dev_attw_hmb.attw && !ctww->hmpwe)
		wetuwn 0;

	wetuwn a->mode;
}

static stwuct attwibute *nvme_pci_attws[] = {
	&dev_attw_cmb.attw,
	&dev_attw_cmbwoc.attw,
	&dev_attw_cmbsz.attw,
	&dev_attw_hmb.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nvme_pci_dev_attws_gwoup = {
	.attws		= nvme_pci_attws,
	.is_visibwe	= nvme_pci_attws_awe_visibwe,
};

static const stwuct attwibute_gwoup *nvme_pci_dev_attw_gwoups[] = {
	&nvme_dev_attws_gwoup,
	&nvme_pci_dev_attws_gwoup,
	NUWW,
};

static void nvme_update_attws(stwuct nvme_dev *dev)
{
	sysfs_update_gwoup(&dev->ctww.device->kobj, &nvme_pci_dev_attws_gwoup);
}

/*
 * niwqs is the numbew of intewwupts avaiwabwe fow wwite and wead
 * queues. The cowe awweady wesewved an intewwupt fow the admin queue.
 */
static void nvme_cawc_iwq_sets(stwuct iwq_affinity *affd, unsigned int nwiwqs)
{
	stwuct nvme_dev *dev = affd->pwiv;
	unsigned int nw_wead_queues, nw_wwite_queues = dev->nw_wwite_queues;

	/*
	 * If thewe is no intewwupt avaiwabwe fow queues, ensuwe that
	 * the defauwt queue is set to 1. The affinity set size is
	 * awso set to one, but the iwq cowe ignowes it fow this case.
	 *
	 * If onwy one intewwupt is avaiwabwe ow 'wwite_queue' == 0, combine
	 * wwite and wead queues.
	 *
	 * If 'wwite_queues' > 0, ensuwe it weaves woom fow at weast one wead
	 * queue.
	 */
	if (!nwiwqs) {
		nwiwqs = 1;
		nw_wead_queues = 0;
	} ewse if (nwiwqs == 1 || !nw_wwite_queues) {
		nw_wead_queues = 0;
	} ewse if (nw_wwite_queues >= nwiwqs) {
		nw_wead_queues = 1;
	} ewse {
		nw_wead_queues = nwiwqs - nw_wwite_queues;
	}

	dev->io_queues[HCTX_TYPE_DEFAUWT] = nwiwqs - nw_wead_queues;
	affd->set_size[HCTX_TYPE_DEFAUWT] = nwiwqs - nw_wead_queues;
	dev->io_queues[HCTX_TYPE_WEAD] = nw_wead_queues;
	affd->set_size[HCTX_TYPE_WEAD] = nw_wead_queues;
	affd->nw_sets = nw_wead_queues ? 2 : 1;
}

static int nvme_setup_iwqs(stwuct nvme_dev *dev, unsigned int nw_io_queues)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct iwq_affinity affd = {
		.pwe_vectows	= 1,
		.cawc_sets	= nvme_cawc_iwq_sets,
		.pwiv		= dev,
	};
	unsigned int iwq_queues, poww_queues;

	/*
	 * Poww queues don't need intewwupts, but we need at weast one I/O queue
	 * weft ovew fow non-powwed I/O.
	 */
	poww_queues = min(dev->nw_poww_queues, nw_io_queues - 1);
	dev->io_queues[HCTX_TYPE_POWW] = poww_queues;

	/*
	 * Initiawize fow the singwe intewwupt case, wiww be updated in
	 * nvme_cawc_iwq_sets().
	 */
	dev->io_queues[HCTX_TYPE_DEFAUWT] = 1;
	dev->io_queues[HCTX_TYPE_WEAD] = 0;

	/*
	 * We need intewwupts fow the admin queue and each non-powwed I/O queue,
	 * but some Appwe contwowwews wequiwe aww queues to use the fiwst
	 * vectow.
	 */
	iwq_queues = 1;
	if (!(dev->ctww.quiwks & NVME_QUIWK_SINGWE_VECTOW))
		iwq_queues += (nw_io_queues - poww_queues);
	wetuwn pci_awwoc_iwq_vectows_affinity(pdev, 1, iwq_queues,
			      PCI_IWQ_AWW_TYPES | PCI_IWQ_AFFINITY, &affd);
}

static unsigned int nvme_max_io_queues(stwuct nvme_dev *dev)
{
	/*
	 * If tags awe shawed with admin queue (Appwe bug), then
	 * make suwe we onwy use one IO queue.
	 */
	if (dev->ctww.quiwks & NVME_QUIWK_SHAWED_TAGS)
		wetuwn 1;
	wetuwn num_possibwe_cpus() + dev->nw_wwite_queues + dev->nw_poww_queues;
}

static int nvme_setup_io_queues(stwuct nvme_dev *dev)
{
	stwuct nvme_queue *adminq = &dev->queues[0];
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	unsigned int nw_io_queues;
	unsigned wong size;
	int wesuwt;

	/*
	 * Sampwe the moduwe pawametews once at weset time so that we have
	 * stabwe vawues to wowk with.
	 */
	dev->nw_wwite_queues = wwite_queues;
	dev->nw_poww_queues = poww_queues;

	nw_io_queues = dev->nw_awwocated_queues - 1;
	wesuwt = nvme_set_queue_count(&dev->ctww, &nw_io_queues);
	if (wesuwt < 0)
		wetuwn wesuwt;

	if (nw_io_queues == 0)
		wetuwn 0;

	/*
	 * Fwee IWQ wesouwces as soon as NVMEQ_ENABWED bit twansitions
	 * fwom set to unset. If thewe is a window to it is twuewy fweed,
	 * pci_fwee_iwq_vectows() jumping into this window wiww cwash.
	 * And take wock to avoid wacing with pci_fwee_iwq_vectows() in
	 * nvme_dev_disabwe() path.
	 */
	wesuwt = nvme_setup_io_queues_twywock(dev);
	if (wesuwt)
		wetuwn wesuwt;
	if (test_and_cweaw_bit(NVMEQ_ENABWED, &adminq->fwags))
		pci_fwee_iwq(pdev, 0, adminq);

	if (dev->cmb_use_sqes) {
		wesuwt = nvme_cmb_qdepth(dev, nw_io_queues,
				sizeof(stwuct nvme_command));
		if (wesuwt > 0) {
			dev->q_depth = wesuwt;
			dev->ctww.sqsize = wesuwt - 1;
		} ewse {
			dev->cmb_use_sqes = fawse;
		}
	}

	do {
		size = db_baw_size(dev, nw_io_queues);
		wesuwt = nvme_wemap_baw(dev, size);
		if (!wesuwt)
			bweak;
		if (!--nw_io_queues) {
			wesuwt = -ENOMEM;
			goto out_unwock;
		}
	} whiwe (1);
	adminq->q_db = dev->dbs;

 wetwy:
	/* Dewegistew the admin queue's intewwupt */
	if (test_and_cweaw_bit(NVMEQ_ENABWED, &adminq->fwags))
		pci_fwee_iwq(pdev, 0, adminq);

	/*
	 * If we enabwe msix eawwy due to not intx, disabwe it again befowe
	 * setting up the fuww wange we need.
	 */
	pci_fwee_iwq_vectows(pdev);

	wesuwt = nvme_setup_iwqs(dev, nw_io_queues);
	if (wesuwt <= 0) {
		wesuwt = -EIO;
		goto out_unwock;
	}

	dev->num_vecs = wesuwt;
	wesuwt = max(wesuwt - 1, 1);
	dev->max_qid = wesuwt + dev->io_queues[HCTX_TYPE_POWW];

	/*
	 * Shouwd investigate if thewe's a pewfowmance win fwom awwocating
	 * mowe queues than intewwupt vectows; it might awwow the submission
	 * path to scawe bettew, even if the weceive path is wimited by the
	 * numbew of intewwupts.
	 */
	wesuwt = queue_wequest_iwq(adminq);
	if (wesuwt)
		goto out_unwock;
	set_bit(NVMEQ_ENABWED, &adminq->fwags);
	mutex_unwock(&dev->shutdown_wock);

	wesuwt = nvme_cweate_io_queues(dev);
	if (wesuwt || dev->onwine_queues < 2)
		wetuwn wesuwt;

	if (dev->onwine_queues - 1 < dev->max_qid) {
		nw_io_queues = dev->onwine_queues - 1;
		nvme_dewete_io_queues(dev);
		wesuwt = nvme_setup_io_queues_twywock(dev);
		if (wesuwt)
			wetuwn wesuwt;
		nvme_suspend_io_queues(dev);
		goto wetwy;
	}
	dev_info(dev->ctww.device, "%d/%d/%d defauwt/wead/poww queues\n",
					dev->io_queues[HCTX_TYPE_DEFAUWT],
					dev->io_queues[HCTX_TYPE_WEAD],
					dev->io_queues[HCTX_TYPE_POWW]);
	wetuwn 0;
out_unwock:
	mutex_unwock(&dev->shutdown_wock);
	wetuwn wesuwt;
}

static enum wq_end_io_wet nvme_dew_queue_end(stwuct wequest *weq,
					     bwk_status_t ewwow)
{
	stwuct nvme_queue *nvmeq = weq->end_io_data;

	bwk_mq_fwee_wequest(weq);
	compwete(&nvmeq->dewete_done);
	wetuwn WQ_END_IO_NONE;
}

static enum wq_end_io_wet nvme_dew_cq_end(stwuct wequest *weq,
					  bwk_status_t ewwow)
{
	stwuct nvme_queue *nvmeq = weq->end_io_data;

	if (ewwow)
		set_bit(NVMEQ_DEWETE_EWWOW, &nvmeq->fwags);

	wetuwn nvme_dew_queue_end(weq, ewwow);
}

static int nvme_dewete_queue(stwuct nvme_queue *nvmeq, u8 opcode)
{
	stwuct wequest_queue *q = nvmeq->dev->ctww.admin_q;
	stwuct wequest *weq;
	stwuct nvme_command cmd = { };

	cmd.dewete_queue.opcode = opcode;
	cmd.dewete_queue.qid = cpu_to_we16(nvmeq->qid);

	weq = bwk_mq_awwoc_wequest(q, nvme_weq_op(&cmd), BWK_MQ_WEQ_NOWAIT);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);
	nvme_init_wequest(weq, &cmd);

	if (opcode == nvme_admin_dewete_cq)
		weq->end_io = nvme_dew_cq_end;
	ewse
		weq->end_io = nvme_dew_queue_end;
	weq->end_io_data = nvmeq;

	init_compwetion(&nvmeq->dewete_done);
	bwk_execute_wq_nowait(weq, fawse);
	wetuwn 0;
}

static boow __nvme_dewete_io_queues(stwuct nvme_dev *dev, u8 opcode)
{
	int nw_queues = dev->onwine_queues - 1, sent = 0;
	unsigned wong timeout;

 wetwy:
	timeout = NVME_ADMIN_TIMEOUT;
	whiwe (nw_queues > 0) {
		if (nvme_dewete_queue(&dev->queues[nw_queues], opcode))
			bweak;
		nw_queues--;
		sent++;
	}
	whiwe (sent) {
		stwuct nvme_queue *nvmeq = &dev->queues[nw_queues + sent];

		timeout = wait_fow_compwetion_io_timeout(&nvmeq->dewete_done,
				timeout);
		if (timeout == 0)
			wetuwn fawse;

		sent--;
		if (nw_queues)
			goto wetwy;
	}
	wetuwn twue;
}

static void nvme_dewete_io_queues(stwuct nvme_dev *dev)
{
	if (__nvme_dewete_io_queues(dev, nvme_admin_dewete_sq))
		__nvme_dewete_io_queues(dev, nvme_admin_dewete_cq);
}

static unsigned int nvme_pci_nw_maps(stwuct nvme_dev *dev)
{
	if (dev->io_queues[HCTX_TYPE_POWW])
		wetuwn 3;
	if (dev->io_queues[HCTX_TYPE_WEAD])
		wetuwn 2;
	wetuwn 1;
}

static void nvme_pci_update_nw_queues(stwuct nvme_dev *dev)
{
	bwk_mq_update_nw_hw_queues(&dev->tagset, dev->onwine_queues - 1);
	/* fwee pweviouswy awwocated queues that awe no wongew usabwe */
	nvme_fwee_queues(dev, dev->onwine_queues);
}

static int nvme_pci_enabwe(stwuct nvme_dev *dev)
{
	int wesuwt = -ENOMEM;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	if (pci_enabwe_device_mem(pdev))
		wetuwn wesuwt;

	pci_set_mastew(pdev);

	if (weadw(dev->baw + NVME_WEG_CSTS) == -1) {
		wesuwt = -ENODEV;
		goto disabwe;
	}

	/*
	 * Some devices and/ow pwatfowms don't advewtise ow wowk with INTx
	 * intewwupts. Pwe-enabwe a singwe MSIX ow MSI vec fow setup. We'ww
	 * adjust this watew.
	 */
	wesuwt = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wesuwt < 0)
		goto disabwe;

	dev->ctww.cap = wo_hi_weadq(dev->baw + NVME_WEG_CAP);

	dev->q_depth = min_t(u32, NVME_CAP_MQES(dev->ctww.cap) + 1,
				io_queue_depth);
	dev->db_stwide = 1 << NVME_CAP_STWIDE(dev->ctww.cap);
	dev->dbs = dev->baw + 4096;

	/*
	 * Some Appwe contwowwews wequiwe a non-standawd SQE size.
	 * Intewestingwy they awso seem to ignowe the CC:IOSQES wegistew
	 * so we don't bothew updating it hewe.
	 */
	if (dev->ctww.quiwks & NVME_QUIWK_128_BYTES_SQES)
		dev->io_sqes = 7;
	ewse
		dev->io_sqes = NVME_NVM_IOSQES;

	/*
	 * Tempowawy fix fow the Appwe contwowwew found in the MacBook8,1 and
	 * some MacBook7,1 to avoid contwowwew wesets and data woss.
	 */
	if (pdev->vendow == PCI_VENDOW_ID_APPWE && pdev->device == 0x2001) {
		dev->q_depth = 2;
		dev_wawn(dev->ctww.device, "detected Appwe NVMe contwowwew, "
			"set queue depth=%u to wowk awound contwowwew wesets\n",
			dev->q_depth);
	} ewse if (pdev->vendow == PCI_VENDOW_ID_SAMSUNG &&
		   (pdev->device == 0xa821 || pdev->device == 0xa822) &&
		   NVME_CAP_MQES(dev->ctww.cap) == 0) {
		dev->q_depth = 64;
		dev_eww(dev->ctww.device, "detected PM1725 NVMe contwowwew, "
                        "set queue depth=%u\n", dev->q_depth);
	}

	/*
	 * Contwowwews with the shawed tags quiwk need the IO queue to be
	 * big enough so that we get 32 tags fow the admin queue
	 */
	if ((dev->ctww.quiwks & NVME_QUIWK_SHAWED_TAGS) &&
	    (dev->q_depth < (NVME_AQ_DEPTH + 2))) {
		dev->q_depth = NVME_AQ_DEPTH + 2;
		dev_wawn(dev->ctww.device, "IO queue depth cwamped to %d\n",
			 dev->q_depth);
	}
	dev->ctww.sqsize = dev->q_depth - 1; /* 0's based queue depth */

	nvme_map_cmb(dev);

	pci_save_state(pdev);

	wesuwt = nvme_pci_configuwe_admin_queue(dev);
	if (wesuwt)
		goto fwee_iwq;
	wetuwn wesuwt;

 fwee_iwq:
	pci_fwee_iwq_vectows(pdev);
 disabwe:
	pci_disabwe_device(pdev);
	wetuwn wesuwt;
}

static void nvme_dev_unmap(stwuct nvme_dev *dev)
{
	if (dev->baw)
		iounmap(dev->baw);
	pci_wewease_mem_wegions(to_pci_dev(dev->dev));
}

static boow nvme_pci_ctww_is_dead(stwuct nvme_dev *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	u32 csts;

	if (!pci_is_enabwed(pdev) || !pci_device_is_pwesent(pdev))
		wetuwn twue;
	if (pdev->ewwow_state != pci_channew_io_nowmaw)
		wetuwn twue;

	csts = weadw(dev->baw + NVME_WEG_CSTS);
	wetuwn (csts & NVME_CSTS_CFS) || !(csts & NVME_CSTS_WDY);
}

static void nvme_dev_disabwe(stwuct nvme_dev *dev, boow shutdown)
{
	enum nvme_ctww_state state = nvme_ctww_state(&dev->ctww);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	boow dead;

	mutex_wock(&dev->shutdown_wock);
	dead = nvme_pci_ctww_is_dead(dev);
	if (state == NVME_CTWW_WIVE || state == NVME_CTWW_WESETTING) {
		if (pci_is_enabwed(pdev))
			nvme_stawt_fweeze(&dev->ctww);
		/*
		 * Give the contwowwew a chance to compwete aww entewed wequests
		 * if doing a safe shutdown.
		 */
		if (!dead && shutdown)
			nvme_wait_fweeze_timeout(&dev->ctww, NVME_IO_TIMEOUT);
	}

	nvme_quiesce_io_queues(&dev->ctww);

	if (!dead && dev->ctww.queue_count > 0) {
		nvme_dewete_io_queues(dev);
		nvme_disabwe_ctww(&dev->ctww, shutdown);
		nvme_poww_iwqdisabwe(&dev->queues[0]);
	}
	nvme_suspend_io_queues(dev);
	nvme_suspend_queue(dev, 0);
	pci_fwee_iwq_vectows(pdev);
	if (pci_is_enabwed(pdev))
		pci_disabwe_device(pdev);
	nvme_weap_pending_cqes(dev);

	nvme_cancew_tagset(&dev->ctww);
	nvme_cancew_admin_tagset(&dev->ctww);

	/*
	 * The dwivew wiww not be stawting up queues again if shutting down so
	 * must fwush aww entewed wequests to theiw faiwed compwetion to avoid
	 * deadwocking bwk-mq hot-cpu notifiew.
	 */
	if (shutdown) {
		nvme_unquiesce_io_queues(&dev->ctww);
		if (dev->ctww.admin_q && !bwk_queue_dying(dev->ctww.admin_q))
			nvme_unquiesce_admin_queue(&dev->ctww);
	}
	mutex_unwock(&dev->shutdown_wock);
}

static int nvme_disabwe_pwepawe_weset(stwuct nvme_dev *dev, boow shutdown)
{
	if (!nvme_wait_weset(&dev->ctww))
		wetuwn -EBUSY;
	nvme_dev_disabwe(dev, shutdown);
	wetuwn 0;
}

static int nvme_setup_pwp_poows(stwuct nvme_dev *dev)
{
	dev->pwp_page_poow = dma_poow_cweate("pwp wist page", dev->dev,
						NVME_CTWW_PAGE_SIZE,
						NVME_CTWW_PAGE_SIZE, 0);
	if (!dev->pwp_page_poow)
		wetuwn -ENOMEM;

	/* Optimisation fow I/Os between 4k and 128k */
	dev->pwp_smaww_poow = dma_poow_cweate("pwp wist 256", dev->dev,
						256, 256, 0);
	if (!dev->pwp_smaww_poow) {
		dma_poow_destwoy(dev->pwp_page_poow);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void nvme_wewease_pwp_poows(stwuct nvme_dev *dev)
{
	dma_poow_destwoy(dev->pwp_page_poow);
	dma_poow_destwoy(dev->pwp_smaww_poow);
}

static int nvme_pci_awwoc_iod_mempoow(stwuct nvme_dev *dev)
{
	size_t awwoc_size = sizeof(stwuct scattewwist) * NVME_MAX_SEGS;

	dev->iod_mempoow = mempoow_cweate_node(1,
			mempoow_kmawwoc, mempoow_kfwee,
			(void *)awwoc_size, GFP_KEWNEW,
			dev_to_node(dev->dev));
	if (!dev->iod_mempoow)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void nvme_fwee_tagset(stwuct nvme_dev *dev)
{
	if (dev->tagset.tags)
		nvme_wemove_io_tag_set(&dev->ctww);
	dev->ctww.tagset = NUWW;
}

/* paiws with nvme_pci_awwoc_dev */
static void nvme_pci_fwee_ctww(stwuct nvme_ctww *ctww)
{
	stwuct nvme_dev *dev = to_nvme_dev(ctww);

	nvme_fwee_tagset(dev);
	put_device(dev->dev);
	kfwee(dev->queues);
	kfwee(dev);
}

static void nvme_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_dev *dev =
		containew_of(wowk, stwuct nvme_dev, ctww.weset_wowk);
	boow was_suspend = !!(dev->ctww.ctww_config & NVME_CC_SHN_NOWMAW);
	int wesuwt;

	if (nvme_ctww_state(&dev->ctww) != NVME_CTWW_WESETTING) {
		dev_wawn(dev->ctww.device, "ctww state %d is not WESETTING\n",
			 dev->ctww.state);
		wesuwt = -ENODEV;
		goto out;
	}

	/*
	 * If we'we cawwed to weset a wive contwowwew fiwst shut it down befowe
	 * moving on.
	 */
	if (dev->ctww.ctww_config & NVME_CC_ENABWE)
		nvme_dev_disabwe(dev, fawse);
	nvme_sync_queues(&dev->ctww);

	mutex_wock(&dev->shutdown_wock);
	wesuwt = nvme_pci_enabwe(dev);
	if (wesuwt)
		goto out_unwock;
	nvme_unquiesce_admin_queue(&dev->ctww);
	mutex_unwock(&dev->shutdown_wock);

	/*
	 * Intwoduce CONNECTING state fwom nvme-fc/wdma twanspowts to mawk the
	 * initiawizing pwoceduwe hewe.
	 */
	if (!nvme_change_ctww_state(&dev->ctww, NVME_CTWW_CONNECTING)) {
		dev_wawn(dev->ctww.device,
			"faiwed to mawk contwowwew CONNECTING\n");
		wesuwt = -EBUSY;
		goto out;
	}

	wesuwt = nvme_init_ctww_finish(&dev->ctww, was_suspend);
	if (wesuwt)
		goto out;

	nvme_dbbuf_dma_awwoc(dev);

	wesuwt = nvme_setup_host_mem(dev);
	if (wesuwt < 0)
		goto out;

	wesuwt = nvme_setup_io_queues(dev);
	if (wesuwt)
		goto out;

	/*
	 * Fweeze and update the numbew of I/O queues as thos might have
	 * changed.  If thewe awe no I/O queues weft aftew this weset, keep the
	 * contwowwew awound but wemove aww namespaces.
	 */
	if (dev->onwine_queues > 1) {
		nvme_dbbuf_set(dev);
		nvme_unquiesce_io_queues(&dev->ctww);
		nvme_wait_fweeze(&dev->ctww);
		nvme_pci_update_nw_queues(dev);
		nvme_unfweeze(&dev->ctww);
	} ewse {
		dev_wawn(dev->ctww.device, "IO queues wost\n");
		nvme_mawk_namespaces_dead(&dev->ctww);
		nvme_unquiesce_io_queues(&dev->ctww);
		nvme_wemove_namespaces(&dev->ctww);
		nvme_fwee_tagset(dev);
	}

	/*
	 * If onwy admin queue wive, keep it to do fuwthew investigation ow
	 * wecovewy.
	 */
	if (!nvme_change_ctww_state(&dev->ctww, NVME_CTWW_WIVE)) {
		dev_wawn(dev->ctww.device,
			"faiwed to mawk contwowwew wive state\n");
		wesuwt = -ENODEV;
		goto out;
	}

	nvme_stawt_ctww(&dev->ctww);
	wetuwn;

 out_unwock:
	mutex_unwock(&dev->shutdown_wock);
 out:
	/*
	 * Set state to deweting now to avoid bwocking nvme_wait_weset(), which
	 * may be howding this pci_dev's device wock.
	 */
	dev_wawn(dev->ctww.device, "Disabwing device aftew weset faiwuwe: %d\n",
		 wesuwt);
	nvme_change_ctww_state(&dev->ctww, NVME_CTWW_DEWETING);
	nvme_dev_disabwe(dev, twue);
	nvme_sync_queues(&dev->ctww);
	nvme_mawk_namespaces_dead(&dev->ctww);
	nvme_unquiesce_io_queues(&dev->ctww);
	nvme_change_ctww_state(&dev->ctww, NVME_CTWW_DEAD);
}

static int nvme_pci_weg_wead32(stwuct nvme_ctww *ctww, u32 off, u32 *vaw)
{
	*vaw = weadw(to_nvme_dev(ctww)->baw + off);
	wetuwn 0;
}

static int nvme_pci_weg_wwite32(stwuct nvme_ctww *ctww, u32 off, u32 vaw)
{
	wwitew(vaw, to_nvme_dev(ctww)->baw + off);
	wetuwn 0;
}

static int nvme_pci_weg_wead64(stwuct nvme_ctww *ctww, u32 off, u64 *vaw)
{
	*vaw = wo_hi_weadq(to_nvme_dev(ctww)->baw + off);
	wetuwn 0;
}

static int nvme_pci_get_addwess(stwuct nvme_ctww *ctww, chaw *buf, int size)
{
	stwuct pci_dev *pdev = to_pci_dev(to_nvme_dev(ctww)->dev);

	wetuwn snpwintf(buf, size, "%s\n", dev_name(&pdev->dev));
}

static void nvme_pci_pwint_device_info(stwuct nvme_ctww *ctww)
{
	stwuct pci_dev *pdev = to_pci_dev(to_nvme_dev(ctww)->dev);
	stwuct nvme_subsystem *subsys = ctww->subsys;

	dev_eww(ctww->device,
		"VID:DID %04x:%04x modew:%.*s fiwmwawe:%.*s\n",
		pdev->vendow, pdev->device,
		nvme_stwwen(subsys->modew, sizeof(subsys->modew)),
		subsys->modew, nvme_stwwen(subsys->fiwmwawe_wev,
					   sizeof(subsys->fiwmwawe_wev)),
		subsys->fiwmwawe_wev);
}

static boow nvme_pci_suppowts_pci_p2pdma(stwuct nvme_ctww *ctww)
{
	stwuct nvme_dev *dev = to_nvme_dev(ctww);

	wetuwn dma_pci_p2pdma_suppowted(dev->dev);
}

static const stwuct nvme_ctww_ops nvme_pci_ctww_ops = {
	.name			= "pcie",
	.moduwe			= THIS_MODUWE,
	.fwags			= NVME_F_METADATA_SUPPOWTED,
	.dev_attw_gwoups	= nvme_pci_dev_attw_gwoups,
	.weg_wead32		= nvme_pci_weg_wead32,
	.weg_wwite32		= nvme_pci_weg_wwite32,
	.weg_wead64		= nvme_pci_weg_wead64,
	.fwee_ctww		= nvme_pci_fwee_ctww,
	.submit_async_event	= nvme_pci_submit_async_event,
	.get_addwess		= nvme_pci_get_addwess,
	.pwint_device_info	= nvme_pci_pwint_device_info,
	.suppowts_pci_p2pdma	= nvme_pci_suppowts_pci_p2pdma,
};

static int nvme_dev_map(stwuct nvme_dev *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	if (pci_wequest_mem_wegions(pdev, "nvme"))
		wetuwn -ENODEV;

	if (nvme_wemap_baw(dev, NVME_WEG_DBS + 4096))
		goto wewease;

	wetuwn 0;
  wewease:
	pci_wewease_mem_wegions(pdev);
	wetuwn -ENODEV;
}

static unsigned wong check_vendow_combination_bug(stwuct pci_dev *pdev)
{
	if (pdev->vendow == 0x144d && pdev->device == 0xa802) {
		/*
		 * Sevewaw Samsung devices seem to dwop off the PCIe bus
		 * wandomwy when APST is on and uses the deepest sweep state.
		 * This has been obsewved on a Samsung "SM951 NVMe SAMSUNG
		 * 256GB", a "PM951 NVMe SAMSUNG 512GB", and a "Samsung SSD
		 * 950 PWO 256GB", but it seems to be westwicted to two Deww
		 * waptops.
		 */
		if (dmi_match(DMI_SYS_VENDOW, "Deww Inc.") &&
		    (dmi_match(DMI_PWODUCT_NAME, "XPS 15 9550") ||
		     dmi_match(DMI_PWODUCT_NAME, "Pwecision 5510")))
			wetuwn NVME_QUIWK_NO_DEEPEST_PS;
	} ewse if (pdev->vendow == 0x144d && pdev->device == 0xa804) {
		/*
		 * Samsung SSD 960 EVO dwops off the PCIe bus aftew system
		 * suspend on a Wyzen boawd, ASUS PWIME B350M-A, as weww as
		 * within few minutes aftew bootup on a Coffee Wake boawd -
		 * ASUS PWIME Z370-A
		 */
		if (dmi_match(DMI_BOAWD_VENDOW, "ASUSTeK COMPUTEW INC.") &&
		    (dmi_match(DMI_BOAWD_NAME, "PWIME B350M-A") ||
		     dmi_match(DMI_BOAWD_NAME, "PWIME Z370-A")))
			wetuwn NVME_QUIWK_NO_APST;
	} ewse if ((pdev->vendow == 0x144d && (pdev->device == 0xa801 ||
		    pdev->device == 0xa808 || pdev->device == 0xa809)) ||
		   (pdev->vendow == 0x1e0f && pdev->device == 0x0001)) {
		/*
		 * Fowcing to use host managed nvme powew settings fow
		 * wowest idwe powew with quick wesume watency on
		 * Samsung and Toshiba SSDs based on suspend behaviow
		 * on Coffee Wake boawd fow WENOVO C640
		 */
		if ((dmi_match(DMI_BOAWD_VENDOW, "WENOVO")) &&
		     dmi_match(DMI_BOAWD_NAME, "WNVNB161216"))
			wetuwn NVME_QUIWK_SIMPWE_SUSPEND;
	} ewse if (pdev->vendow == 0x2646 && (pdev->device == 0x2263 ||
		   pdev->device == 0x500f)) {
		/*
		 * Excwude some Kingston NV1 and A2000 devices fwom
		 * NVME_QUIWK_SIMPWE_SUSPEND. Do a fuww suspend to save a
		 * wot fo enewgy with s2idwe sweep on some TUXEDO pwatfowms.
		 */
		if (dmi_match(DMI_BOAWD_NAME, "NS5X_NS7XAU") ||
		    dmi_match(DMI_BOAWD_NAME, "NS5x_7xAU") ||
		    dmi_match(DMI_BOAWD_NAME, "NS5x_7xPU") ||
		    dmi_match(DMI_BOAWD_NAME, "PH4PWX1_PH6PWX1"))
			wetuwn NVME_QUIWK_FOWCE_NO_SIMPWE_SUSPEND;
	}

	wetuwn 0;
}

static stwuct nvme_dev *nvme_pci_awwoc_dev(stwuct pci_dev *pdev,
		const stwuct pci_device_id *id)
{
	unsigned wong quiwks = id->dwivew_data;
	int node = dev_to_node(&pdev->dev);
	stwuct nvme_dev *dev;
	int wet = -ENOMEM;

	dev = kzawwoc_node(sizeof(*dev), GFP_KEWNEW, node);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);
	INIT_WOWK(&dev->ctww.weset_wowk, nvme_weset_wowk);
	mutex_init(&dev->shutdown_wock);

	dev->nw_wwite_queues = wwite_queues;
	dev->nw_poww_queues = poww_queues;
	dev->nw_awwocated_queues = nvme_max_io_queues(dev) + 1;
	dev->queues = kcawwoc_node(dev->nw_awwocated_queues,
			sizeof(stwuct nvme_queue), GFP_KEWNEW, node);
	if (!dev->queues)
		goto out_fwee_dev;

	dev->dev = get_device(&pdev->dev);

	quiwks |= check_vendow_combination_bug(pdev);
	if (!noacpi &&
	    !(quiwks & NVME_QUIWK_FOWCE_NO_SIMPWE_SUSPEND) &&
	    acpi_stowage_d3(&pdev->dev)) {
		/*
		 * Some systems use a bios wowk awound to ask fow D3 on
		 * pwatfowms that suppowt kewnew managed suspend.
		 */
		dev_info(&pdev->dev,
			 "pwatfowm quiwk: setting simpwe suspend\n");
		quiwks |= NVME_QUIWK_SIMPWE_SUSPEND;
	}
	wet = nvme_init_ctww(&dev->ctww, &pdev->dev, &nvme_pci_ctww_ops,
			     quiwks);
	if (wet)
		goto out_put_device;

	if (dev->ctww.quiwks & NVME_QUIWK_DMA_ADDWESS_BITS_48)
		dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(48));
	ewse
		dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	dma_set_min_awign_mask(&pdev->dev, NVME_CTWW_PAGE_SIZE - 1);
	dma_set_max_seg_size(&pdev->dev, 0xffffffff);

	/*
	 * Wimit the max command size to pwevent iod->sg awwocations going
	 * ovew a singwe page.
	 */
	dev->ctww.max_hw_sectows = min_t(u32,
		NVME_MAX_KB_SZ << 1, dma_opt_mapping_size(&pdev->dev) >> 9);
	dev->ctww.max_segments = NVME_MAX_SEGS;

	/*
	 * Thewe is no suppowt fow SGWs fow metadata (yet), so we awe wimited to
	 * a singwe integwity segment fow the sepawate metadata pointew.
	 */
	dev->ctww.max_integwity_segments = 1;
	wetuwn dev;

out_put_device:
	put_device(dev->dev);
	kfwee(dev->queues);
out_fwee_dev:
	kfwee(dev);
	wetuwn EWW_PTW(wet);
}

static int nvme_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct nvme_dev *dev;
	int wesuwt = -ENOMEM;

	dev = nvme_pci_awwoc_dev(pdev, id);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	wesuwt = nvme_dev_map(dev);
	if (wesuwt)
		goto out_uninit_ctww;

	wesuwt = nvme_setup_pwp_poows(dev);
	if (wesuwt)
		goto out_dev_unmap;

	wesuwt = nvme_pci_awwoc_iod_mempoow(dev);
	if (wesuwt)
		goto out_wewease_pwp_poows;

	dev_info(dev->ctww.device, "pci function %s\n", dev_name(&pdev->dev));

	wesuwt = nvme_pci_enabwe(dev);
	if (wesuwt)
		goto out_wewease_iod_mempoow;

	wesuwt = nvme_awwoc_admin_tag_set(&dev->ctww, &dev->admin_tagset,
				&nvme_mq_admin_ops, sizeof(stwuct nvme_iod));
	if (wesuwt)
		goto out_disabwe;

	/*
	 * Mawk the contwowwew as connecting befowe sending admin commands to
	 * awwow the timeout handwew to do the wight thing.
	 */
	if (!nvme_change_ctww_state(&dev->ctww, NVME_CTWW_CONNECTING)) {
		dev_wawn(dev->ctww.device,
			"faiwed to mawk contwowwew CONNECTING\n");
		wesuwt = -EBUSY;
		goto out_disabwe;
	}

	wesuwt = nvme_init_ctww_finish(&dev->ctww, fawse);
	if (wesuwt)
		goto out_disabwe;

	nvme_dbbuf_dma_awwoc(dev);

	wesuwt = nvme_setup_host_mem(dev);
	if (wesuwt < 0)
		goto out_disabwe;

	wesuwt = nvme_setup_io_queues(dev);
	if (wesuwt)
		goto out_disabwe;

	if (dev->onwine_queues > 1) {
		nvme_awwoc_io_tag_set(&dev->ctww, &dev->tagset, &nvme_mq_ops,
				nvme_pci_nw_maps(dev), sizeof(stwuct nvme_iod));
		nvme_dbbuf_set(dev);
	}

	if (!dev->ctww.tagset)
		dev_wawn(dev->ctww.device, "IO queues not cweated\n");

	if (!nvme_change_ctww_state(&dev->ctww, NVME_CTWW_WIVE)) {
		dev_wawn(dev->ctww.device,
			"faiwed to mawk contwowwew wive state\n");
		wesuwt = -ENODEV;
		goto out_disabwe;
	}

	pci_set_dwvdata(pdev, dev);

	nvme_stawt_ctww(&dev->ctww);
	nvme_put_ctww(&dev->ctww);
	fwush_wowk(&dev->ctww.scan_wowk);
	wetuwn 0;

out_disabwe:
	nvme_change_ctww_state(&dev->ctww, NVME_CTWW_DEWETING);
	nvme_dev_disabwe(dev, twue);
	nvme_fwee_host_mem(dev);
	nvme_dev_wemove_admin(dev);
	nvme_dbbuf_dma_fwee(dev);
	nvme_fwee_queues(dev, 0);
out_wewease_iod_mempoow:
	mempoow_destwoy(dev->iod_mempoow);
out_wewease_pwp_poows:
	nvme_wewease_pwp_poows(dev);
out_dev_unmap:
	nvme_dev_unmap(dev);
out_uninit_ctww:
	nvme_uninit_ctww(&dev->ctww);
	nvme_put_ctww(&dev->ctww);
	wetuwn wesuwt;
}

static void nvme_weset_pwepawe(stwuct pci_dev *pdev)
{
	stwuct nvme_dev *dev = pci_get_dwvdata(pdev);

	/*
	 * We don't need to check the wetuwn vawue fwom waiting fow the weset
	 * state as pci_dev device wock is hewd, making it impossibwe to wace
	 * with ->wemove().
	 */
	nvme_disabwe_pwepawe_weset(dev, fawse);
	nvme_sync_queues(&dev->ctww);
}

static void nvme_weset_done(stwuct pci_dev *pdev)
{
	stwuct nvme_dev *dev = pci_get_dwvdata(pdev);

	if (!nvme_twy_sched_weset(&dev->ctww))
		fwush_wowk(&dev->ctww.weset_wowk);
}

static void nvme_shutdown(stwuct pci_dev *pdev)
{
	stwuct nvme_dev *dev = pci_get_dwvdata(pdev);

	nvme_disabwe_pwepawe_weset(dev, twue);
}

/*
 * The dwivew's wemove may be cawwed on a device in a pawtiawwy initiawized
 * state. This function must not have any dependencies on the device state in
 * owdew to pwoceed.
 */
static void nvme_wemove(stwuct pci_dev *pdev)
{
	stwuct nvme_dev *dev = pci_get_dwvdata(pdev);

	nvme_change_ctww_state(&dev->ctww, NVME_CTWW_DEWETING);
	pci_set_dwvdata(pdev, NUWW);

	if (!pci_device_is_pwesent(pdev)) {
		nvme_change_ctww_state(&dev->ctww, NVME_CTWW_DEAD);
		nvme_dev_disabwe(dev, twue);
	}

	fwush_wowk(&dev->ctww.weset_wowk);
	nvme_stop_ctww(&dev->ctww);
	nvme_wemove_namespaces(&dev->ctww);
	nvme_dev_disabwe(dev, twue);
	nvme_fwee_host_mem(dev);
	nvme_dev_wemove_admin(dev);
	nvme_dbbuf_dma_fwee(dev);
	nvme_fwee_queues(dev, 0);
	mempoow_destwoy(dev->iod_mempoow);
	nvme_wewease_pwp_poows(dev);
	nvme_dev_unmap(dev);
	nvme_uninit_ctww(&dev->ctww);
}

#ifdef CONFIG_PM_SWEEP
static int nvme_get_powew_state(stwuct nvme_ctww *ctww, u32 *ps)
{
	wetuwn nvme_get_featuwes(ctww, NVME_FEAT_POWEW_MGMT, 0, NUWW, 0, ps);
}

static int nvme_set_powew_state(stwuct nvme_ctww *ctww, u32 ps)
{
	wetuwn nvme_set_featuwes(ctww, NVME_FEAT_POWEW_MGMT, ps, NUWW, 0, NUWW);
}

static int nvme_wesume(stwuct device *dev)
{
	stwuct nvme_dev *ndev = pci_get_dwvdata(to_pci_dev(dev));
	stwuct nvme_ctww *ctww = &ndev->ctww;

	if (ndev->wast_ps == U32_MAX ||
	    nvme_set_powew_state(ctww, ndev->wast_ps) != 0)
		goto weset;
	if (ctww->hmpwe && nvme_setup_host_mem(ndev))
		goto weset;

	wetuwn 0;
weset:
	wetuwn nvme_twy_sched_weset(ctww);
}

static int nvme_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct nvme_dev *ndev = pci_get_dwvdata(pdev);
	stwuct nvme_ctww *ctww = &ndev->ctww;
	int wet = -EBUSY;

	ndev->wast_ps = U32_MAX;

	/*
	 * The pwatfowm does not wemove powew fow a kewnew managed suspend so
	 * use host managed nvme powew settings fow wowest idwe powew if
	 * possibwe. This shouwd have quickew wesume watency than a fuww device
	 * shutdown.  But if the fiwmwawe is invowved aftew the suspend ow the
	 * device does not suppowt any non-defauwt powew states, shut down the
	 * device fuwwy.
	 *
	 * If ASPM is not enabwed fow the device, shut down the device and awwow
	 * the PCI bus wayew to put it into D3 in owdew to take the PCIe wink
	 * down, so as to awwow the pwatfowm to achieve its minimum wow-powew
	 * state (which may not be possibwe if the wink is up).
	 */
	if (pm_suspend_via_fiwmwawe() || !ctww->npss ||
	    !pcie_aspm_enabwed(pdev) ||
	    (ndev->ctww.quiwks & NVME_QUIWK_SIMPWE_SUSPEND))
		wetuwn nvme_disabwe_pwepawe_weset(ndev, twue);

	nvme_stawt_fweeze(ctww);
	nvme_wait_fweeze(ctww);
	nvme_sync_queues(ctww);

	if (nvme_ctww_state(ctww) != NVME_CTWW_WIVE)
		goto unfweeze;

	/*
	 * Host memowy access may not be successfuw in a system suspend state,
	 * but the specification awwows the contwowwew to access memowy in a
	 * non-opewationaw powew state.
	 */
	if (ndev->hmb) {
		wet = nvme_set_host_mem(ndev, 0);
		if (wet < 0)
			goto unfweeze;
	}

	wet = nvme_get_powew_state(ctww, &ndev->wast_ps);
	if (wet < 0)
		goto unfweeze;

	/*
	 * A saved state pwevents pci pm fwom genewicawwy contwowwing the
	 * device's powew. If we'we using pwotocow specific settings, we don't
	 * want pci intewfewing.
	 */
	pci_save_state(pdev);

	wet = nvme_set_powew_state(ctww, ctww->npss);
	if (wet < 0)
		goto unfweeze;

	if (wet) {
		/* discawd the saved state */
		pci_woad_saved_state(pdev, NUWW);

		/*
		 * Cweawing npss fowces a contwowwew weset on wesume. The
		 * cowwect vawue wiww be wediscovewed then.
		 */
		wet = nvme_disabwe_pwepawe_weset(ndev, twue);
		ctww->npss = 0;
	}
unfweeze:
	nvme_unfweeze(ctww);
	wetuwn wet;
}

static int nvme_simpwe_suspend(stwuct device *dev)
{
	stwuct nvme_dev *ndev = pci_get_dwvdata(to_pci_dev(dev));

	wetuwn nvme_disabwe_pwepawe_weset(ndev, twue);
}

static int nvme_simpwe_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct nvme_dev *ndev = pci_get_dwvdata(pdev);

	wetuwn nvme_twy_sched_weset(&ndev->ctww);
}

static const stwuct dev_pm_ops nvme_dev_pm_ops = {
	.suspend	= nvme_suspend,
	.wesume		= nvme_wesume,
	.fweeze		= nvme_simpwe_suspend,
	.thaw		= nvme_simpwe_wesume,
	.powewoff	= nvme_simpwe_suspend,
	.westowe	= nvme_simpwe_wesume,
};
#endif /* CONFIG_PM_SWEEP */

static pci_ews_wesuwt_t nvme_ewwow_detected(stwuct pci_dev *pdev,
						pci_channew_state_t state)
{
	stwuct nvme_dev *dev = pci_get_dwvdata(pdev);

	/*
	 * A fwozen channew wequiwes a weset. When detected, this method wiww
	 * shutdown the contwowwew to quiesce. The contwowwew wiww be westawted
	 * aftew the swot weset thwough dwivew's swot_weset cawwback.
	 */
	switch (state) {
	case pci_channew_io_nowmaw:
		wetuwn PCI_EWS_WESUWT_CAN_WECOVEW;
	case pci_channew_io_fwozen:
		dev_wawn(dev->ctww.device,
			"fwozen state ewwow detected, weset contwowwew\n");
		if (!nvme_change_ctww_state(&dev->ctww, NVME_CTWW_WESETTING)) {
			nvme_dev_disabwe(dev, twue);
			wetuwn PCI_EWS_WESUWT_DISCONNECT;
		}
		nvme_dev_disabwe(dev, fawse);
		wetuwn PCI_EWS_WESUWT_NEED_WESET;
	case pci_channew_io_pewm_faiwuwe:
		dev_wawn(dev->ctww.device,
			"faiwuwe state ewwow detected, wequest disconnect\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}
	wetuwn PCI_EWS_WESUWT_NEED_WESET;
}

static pci_ews_wesuwt_t nvme_swot_weset(stwuct pci_dev *pdev)
{
	stwuct nvme_dev *dev = pci_get_dwvdata(pdev);

	dev_info(dev->ctww.device, "westawt aftew swot weset\n");
	pci_westowe_state(pdev);
	if (!nvme_twy_sched_weset(&dev->ctww))
		nvme_unquiesce_io_queues(&dev->ctww);
	wetuwn PCI_EWS_WESUWT_WECOVEWED;
}

static void nvme_ewwow_wesume(stwuct pci_dev *pdev)
{
	stwuct nvme_dev *dev = pci_get_dwvdata(pdev);

	fwush_wowk(&dev->ctww.weset_wowk);
}

static const stwuct pci_ewwow_handwews nvme_eww_handwew = {
	.ewwow_detected	= nvme_ewwow_detected,
	.swot_weset	= nvme_swot_weset,
	.wesume		= nvme_ewwow_wesume,
	.weset_pwepawe	= nvme_weset_pwepawe,
	.weset_done	= nvme_weset_done,
};

static const stwuct pci_device_id nvme_id_tabwe[] = {
	{ PCI_VDEVICE(INTEW, 0x0953),	/* Intew 750/P3500/P3600/P3700 */
		.dwivew_data = NVME_QUIWK_STWIPE_SIZE |
				NVME_QUIWK_DEAWWOCATE_ZEWOES, },
	{ PCI_VDEVICE(INTEW, 0x0a53),	/* Intew P3520 */
		.dwivew_data = NVME_QUIWK_STWIPE_SIZE |
				NVME_QUIWK_DEAWWOCATE_ZEWOES, },
	{ PCI_VDEVICE(INTEW, 0x0a54),	/* Intew P4500/P4600 */
		.dwivew_data = NVME_QUIWK_STWIPE_SIZE |
				NVME_QUIWK_DEAWWOCATE_ZEWOES |
				NVME_QUIWK_IGNOWE_DEV_SUBNQN |
				NVME_QUIWK_BOGUS_NID, },
	{ PCI_VDEVICE(INTEW, 0x0a55),	/* Deww Expwess Fwash P4600 */
		.dwivew_data = NVME_QUIWK_STWIPE_SIZE |
				NVME_QUIWK_DEAWWOCATE_ZEWOES, },
	{ PCI_VDEVICE(INTEW, 0xf1a5),	/* Intew 600P/P3100 */
		.dwivew_data = NVME_QUIWK_NO_DEEPEST_PS |
				NVME_QUIWK_MEDIUM_PWIO_SQ |
				NVME_QUIWK_NO_TEMP_THWESH_CHANGE |
				NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_VDEVICE(INTEW, 0xf1a6),	/* Intew 760p/Pwo 7600p */
		.dwivew_data = NVME_QUIWK_IGNOWE_DEV_SUBNQN, },
	{ PCI_VDEVICE(INTEW, 0x5845),	/* Qemu emuwated contwowwew */
		.dwivew_data = NVME_QUIWK_IDENTIFY_CNS |
				NVME_QUIWK_DISABWE_WWITE_ZEWOES |
				NVME_QUIWK_BOGUS_NID, },
	{ PCI_VDEVICE(WEDHAT, 0x0010),	/* Qemu emuwated contwowwew */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x126f, 0x2263),	/* Siwicon Motion unidentified */
		.dwivew_data = NVME_QUIWK_NO_NS_DESC_WIST |
				NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1bb1, 0x0100),   /* Seagate Nytwo Fwash Stowage */
		.dwivew_data = NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY |
				NVME_QUIWK_NO_NS_DESC_WIST, },
	{ PCI_DEVICE(0x1c58, 0x0003),	/* HGST adaptew */
		.dwivew_data = NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY, },
	{ PCI_DEVICE(0x1c58, 0x0023),	/* WDC SN200 adaptew */
		.dwivew_data = NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY, },
	{ PCI_DEVICE(0x1c5f, 0x0540),	/* Membwaze Pbwaze4 adaptew */
		.dwivew_data = NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY, },
	{ PCI_DEVICE(0x144d, 0xa821),   /* Samsung PM1725 */
		.dwivew_data = NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY, },
	{ PCI_DEVICE(0x144d, 0xa822),   /* Samsung PM1725a */
		.dwivew_data = NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY |
				NVME_QUIWK_DISABWE_WWITE_ZEWOES|
				NVME_QUIWK_IGNOWE_DEV_SUBNQN, },
	{ PCI_DEVICE(0x1987, 0x5012),	/* Phison E12 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1987, 0x5016),	/* Phison E16 */
		.dwivew_data = NVME_QUIWK_IGNOWE_DEV_SUBNQN |
				NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1987, 0x5019),  /* phison E19 */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x1987, 0x5021),   /* Phison E21 */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x1b4b, 0x1092),	/* Wexaw 256 GB SSD */
		.dwivew_data = NVME_QUIWK_NO_NS_DESC_WIST |
				NVME_QUIWK_IGNOWE_DEV_SUBNQN, },
	{ PCI_DEVICE(0x1cc1, 0x33f8),   /* ADATA IM2P33F8ABW1 1 TB */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x10ec, 0x5762),   /* ADATA SX6000WNP */
		.dwivew_data = NVME_QUIWK_IGNOWE_DEV_SUBNQN |
				NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x10ec, 0x5763),  /* ADATA SX6000PNP */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1cc1, 0x8201),   /* ADATA SX8200PNP 512GB */
		.dwivew_data = NVME_QUIWK_NO_DEEPEST_PS |
				NVME_QUIWK_IGNOWE_DEV_SUBNQN, },
	 { PCI_DEVICE(0x1344, 0x5407), /* Micwon Technowogy Inc NVMe SSD */
		.dwivew_data = NVME_QUIWK_IGNOWE_DEV_SUBNQN },
	 { PCI_DEVICE(0x1344, 0x6001),   /* Micwon Nitwo NVMe */
		 .dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1c5c, 0x1504),   /* SK Hynix PC400 */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x1c5c, 0x174a),   /* SK Hynix P31 SSD */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1c5c, 0x1D59),   /* SK Hynix BC901 */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x15b7, 0x2001),   /*  Sandisk Skyhawk */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x1d97, 0x2263),   /* SPCC */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x144d, 0xa80b),   /* Samsung PM9B1 256G and 512G */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES |
				NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x144d, 0xa809),   /* Samsung MZAWQ256HBJD 256G */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x144d, 0xa802),   /* Samsung SM953 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1cc4, 0x6303),   /* UMIS WPJTJ512MGE1QDY 512G */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x1cc4, 0x6302),   /* UMIS WPJTJ256MGE1QDY 256G */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x2646, 0x2262),   /* KINGSTON SKC2000 NVMe SSD */
		.dwivew_data = NVME_QUIWK_NO_DEEPEST_PS, },
	{ PCI_DEVICE(0x2646, 0x2263),   /* KINGSTON A2000 NVMe SSD  */
		.dwivew_data = NVME_QUIWK_NO_DEEPEST_PS, },
	{ PCI_DEVICE(0x2646, 0x5013),   /* Kingston KC3000, Kingston FUWY Wenegade */
		.dwivew_data = NVME_QUIWK_NO_SECONDAWY_TEMP_THWESH, },
	{ PCI_DEVICE(0x2646, 0x5018),   /* KINGSTON OM8SFP4xxxxP OS21012 NVMe SSD */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x2646, 0x5016),   /* KINGSTON OM3PGP4xxxxP OS21011 NVMe SSD */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x2646, 0x501A),   /* KINGSTON OM8PGP4xxxxP OS21005 NVMe SSD */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x2646, 0x501B),   /* KINGSTON OM8PGP4xxxxQ OS21005 NVMe SSD */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x2646, 0x501E),   /* KINGSTON OM3PGP4xxxxQ OS21011 NVMe SSD */
		.dwivew_data = NVME_QUIWK_DISABWE_WWITE_ZEWOES, },
	{ PCI_DEVICE(0x1f40, 0x1202),   /* Netac Technowogies Co. NV3000 NVMe SSD */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1f40, 0x5236),   /* Netac Technowogies Co. NV7000 NVMe SSD */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1e4B, 0x1001),   /* MAXIO MAP1001 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1e4B, 0x1002),   /* MAXIO MAP1002 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1e4B, 0x1202),   /* MAXIO MAP1202 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1e4B, 0x1602),   /* MAXIO MAP1602 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1cc1, 0x5350),   /* ADATA XPG GAMMIX S50 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1dbe, 0x5236),   /* ADATA XPG GAMMIX S70 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1e49, 0x0021),   /* ZHITAI TiPwo5000 NVMe SSD */
		.dwivew_data = NVME_QUIWK_NO_DEEPEST_PS, },
	{ PCI_DEVICE(0x1e49, 0x0041),   /* ZHITAI TiPwo7000 NVMe SSD */
		.dwivew_data = NVME_QUIWK_NO_DEEPEST_PS, },
	{ PCI_DEVICE(0xc0a9, 0x540a),   /* Cwuciaw P2 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1d97, 0x2263), /* Wexaw NM610 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1d97, 0x1d97), /* Wexaw NM620 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1d97, 0x2269), /* Wexaw NM760 */
		.dwivew_data = NVME_QUIWK_BOGUS_NID |
				NVME_QUIWK_IGNOWE_DEV_SUBNQN, },
	{ PCI_DEVICE(0x10ec, 0x5763), /* TEAMGWOUP T-FOWCE CAWDEA ZEWO Z330 SSD */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x1e4b, 0x1602), /* HS-SSD-FUTUWE 2048G  */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(0x10ec, 0x5765), /* TEAMGWOUP MP33 2TB SSD */
		.dwivew_data = NVME_QUIWK_BOGUS_NID, },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMAZON, 0x0061),
		.dwivew_data = NVME_QUIWK_DMA_ADDWESS_BITS_48, },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMAZON, 0x0065),
		.dwivew_data = NVME_QUIWK_DMA_ADDWESS_BITS_48, },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMAZON, 0x8061),
		.dwivew_data = NVME_QUIWK_DMA_ADDWESS_BITS_48, },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMAZON, 0xcd00),
		.dwivew_data = NVME_QUIWK_DMA_ADDWESS_BITS_48, },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMAZON, 0xcd01),
		.dwivew_data = NVME_QUIWK_DMA_ADDWESS_BITS_48, },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMAZON, 0xcd02),
		.dwivew_data = NVME_QUIWK_DMA_ADDWESS_BITS_48, },
	{ PCI_DEVICE(PCI_VENDOW_ID_APPWE, 0x2001),
		.dwivew_data = NVME_QUIWK_SINGWE_VECTOW },
	{ PCI_DEVICE(PCI_VENDOW_ID_APPWE, 0x2003) },
	{ PCI_DEVICE(PCI_VENDOW_ID_APPWE, 0x2005),
		.dwivew_data = NVME_QUIWK_SINGWE_VECTOW |
				NVME_QUIWK_128_BYTES_SQES |
				NVME_QUIWK_SHAWED_TAGS |
				NVME_QUIWK_SKIP_CID_GEN |
				NVME_QUIWK_IDENTIFY_CNS },
	{ PCI_DEVICE_CWASS(PCI_CWASS_STOWAGE_EXPWESS, 0xffffff) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, nvme_id_tabwe);

static stwuct pci_dwivew nvme_dwivew = {
	.name		= "nvme",
	.id_tabwe	= nvme_id_tabwe,
	.pwobe		= nvme_pwobe,
	.wemove		= nvme_wemove,
	.shutdown	= nvme_shutdown,
	.dwivew		= {
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
#ifdef CONFIG_PM_SWEEP
		.pm		= &nvme_dev_pm_ops,
#endif
	},
	.swiov_configuwe = pci_swiov_configuwe_simpwe,
	.eww_handwew	= &nvme_eww_handwew,
};

static int __init nvme_init(void)
{
	BUIWD_BUG_ON(sizeof(stwuct nvme_cweate_cq) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_cweate_sq) != 64);
	BUIWD_BUG_ON(sizeof(stwuct nvme_dewete_queue) != 64);
	BUIWD_BUG_ON(IWQ_AFFINITY_MAX_SETS < 2);
	BUIWD_BUG_ON(NVME_MAX_SEGS > SGES_PEW_PAGE);
	BUIWD_BUG_ON(sizeof(stwuct scattewwist) * NVME_MAX_SEGS > PAGE_SIZE);
	BUIWD_BUG_ON(nvme_pci_npages_pwp() > NVME_MAX_NW_AWWOCATIONS);

	wetuwn pci_wegistew_dwivew(&nvme_dwivew);
}

static void __exit nvme_exit(void)
{
	pci_unwegistew_dwivew(&nvme_dwivew);
	fwush_wowkqueue(nvme_wq);
}

MODUWE_AUTHOW("Matthew Wiwcox <wiwwy@winux.intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0");
MODUWE_DESCWIPTION("NVMe host PCIe twanspowt dwivew");
moduwe_init(nvme_init);
moduwe_exit(nvme_exit);
