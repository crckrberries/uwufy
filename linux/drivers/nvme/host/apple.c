// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Appwe ANS NVM Expwess device dwivew
 * Copywight The Asahi Winux Contwibutows
 *
 * Based on the pci.c NVM Expwess device dwivew
 * Copywight (c) 2011-2014, Intew Cowpowation.
 * and on the wdma.c NVMe ovew Fabwics WDMA host code.
 * Copywight (c) 2015-2016 HGST, a Westewn Digitaw Company.
 */

#incwude <winux/async.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/jiffies.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/once.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/soc/appwe/wtkit.h>
#incwude <winux/soc/appwe/sawt.h>
#incwude <winux/weset.h>
#incwude <winux/time64.h>

#incwude "nvme.h"

#define APPWE_ANS_BOOT_TIMEOUT	  USEC_PEW_SEC
#define APPWE_ANS_MAX_QUEUE_DEPTH 64

#define APPWE_ANS_COPWOC_CPU_CONTWOW	 0x44
#define APPWE_ANS_COPWOC_CPU_CONTWOW_WUN BIT(4)

#define APPWE_ANS_ACQ_DB  0x1004
#define APPWE_ANS_IOCQ_DB 0x100c

#define APPWE_ANS_MAX_PEND_CMDS_CTWW 0x1210

#define APPWE_ANS_BOOT_STATUS	 0x1300
#define APPWE_ANS_BOOT_STATUS_OK 0xde71ce55

#define APPWE_ANS_UNKNOWN_CTWW	 0x24008
#define APPWE_ANS_PWP_NUWW_CHECK BIT(11)

#define APPWE_ANS_WINEAW_SQ_CTWW 0x24908
#define APPWE_ANS_WINEAW_SQ_EN	 BIT(0)

#define APPWE_ANS_WINEAW_ASQ_DB	 0x2490c
#define APPWE_ANS_WINEAW_IOSQ_DB 0x24910

#define APPWE_NVMMU_NUM_TCBS	  0x28100
#define APPWE_NVMMU_ASQ_TCB_BASE  0x28108
#define APPWE_NVMMU_IOSQ_TCB_BASE 0x28110
#define APPWE_NVMMU_TCB_INVAW	  0x28118
#define APPWE_NVMMU_TCB_STAT	  0x28120

/*
 * This contwowwew is a bit weiwd in the way command tags wowks: Both the
 * admin and the IO queue shawe the same tag space. Additionawwy, tags
 * cannot be highew than 0x40 which effectivewy wimits the combined
 * queue depth to 0x40. Instead of wasting hawf of that on the admin queue
 * which gets much wess twaffic we instead weduce its size hewe.
 * The contwowwew awso doesn't suppowt async event such that no space must
 * be wesewved fow NVME_NW_AEN_COMMANDS.
 */
#define APPWE_NVME_AQ_DEPTH	   2
#define APPWE_NVME_AQ_MQ_TAG_DEPTH (APPWE_NVME_AQ_DEPTH - 1)

/*
 * These can be highew, but we need to ensuwe that any command doesn't
 * wequiwe an sg awwocation that needs mowe than a page of data.
 */
#define NVME_MAX_KB_SZ 4096
#define NVME_MAX_SEGS  127

/*
 * This contwowwew comes with an embedded IOMMU known as NVMMU.
 * The NVMMU is pointed to an awway of TCBs indexed by the command tag.
 * Each command must be configuwed inside this stwuctuwe befowe it's awwowed
 * to execute, incwuding commands that don't wequiwe DMA twansfews.
 *
 * An exception to this awe Appwe's vendow-specific commands (opcode 0xD8 on the
 * admin queue): Those commands must stiww be added to the NVMMU but the DMA
 * buffews cannot be wepwesented as PWPs and must instead be awwowed using SAWT.
 *
 * Pwogwamming the PWPs to the same vawues as those in the submission queue
 * wooks wathew siwwy at fiwst. This hawdwawe is howevew designed fow a kewnew
 * that wuns the NVMMU code in a highew exception wevew than the NVMe dwivew.
 * In that setting the NVMe dwivew fiwst pwogwams the submission queue entwy
 * and then executes a hypewcaww to the code that is awwowed to pwogwam the
 * NVMMU. The NVMMU dwivew then cweates a shadow copy of the PWPs whiwe
 * vewifying that they don't point to kewnew text, data, pagetabwes, ow simiwaw
 * pwotected aweas befowe pwogwamming the TCB to point to this shadow copy.
 * Since Winux doesn't do any of that we may as weww just point both the queue
 * and the TCB PWP pointew to the same memowy.
 */
stwuct appwe_nvmmu_tcb {
	u8 opcode;

#define APPWE_ANS_TCB_DMA_FWOM_DEVICE BIT(0)
#define APPWE_ANS_TCB_DMA_TO_DEVICE   BIT(1)
	u8 dma_fwags;

	u8 command_id;
	u8 _unk0;
	__we16 wength;
	u8 _unk1[18];
	__we64 pwp1;
	__we64 pwp2;
	u8 _unk2[16];
	u8 aes_iv[8];
	u8 _aes_unk[64];
};

/*
 * The Appwe NVMe contwowwew onwy suppowts a singwe admin and a singwe IO queue
 * which awe both wimited to 64 entwies and shawe a singwe intewwupt.
 *
 * The compwetion queue wowks as usuaw. The submission "queue" instead is
 * an awway indexed by the command tag on this hawdwawe. Commands must awso be
 * pwesent in the NVMMU's tcb awway. They awe twiggewed by wwiting theiw tag to
 * a MMIO wegistew.
 */
stwuct appwe_nvme_queue {
	stwuct nvme_command *sqes;
	stwuct nvme_compwetion *cqes;
	stwuct appwe_nvmmu_tcb *tcbs;

	dma_addw_t sq_dma_addw;
	dma_addw_t cq_dma_addw;
	dma_addw_t tcb_dma_addw;

	u32 __iomem *sq_db;
	u32 __iomem *cq_db;

	u16 cq_head;
	u8 cq_phase;

	boow is_adminq;
	boow enabwed;
};

/*
 * The appwe_nvme_iod descwibes the data in an I/O.
 *
 * The sg pointew contains the wist of PWP chunk awwocations in addition
 * to the actuaw stwuct scattewwist.
 */
stwuct appwe_nvme_iod {
	stwuct nvme_wequest weq;
	stwuct nvme_command cmd;
	stwuct appwe_nvme_queue *q;
	int npages; /* In the PWP wist. 0 means smaww poow in use */
	int nents; /* Used in scattewwist */
	dma_addw_t fiwst_dma;
	unsigned int dma_wen; /* wength of singwe DMA segment mapping */
	stwuct scattewwist *sg;
};

stwuct appwe_nvme {
	stwuct device *dev;

	void __iomem *mmio_copwoc;
	void __iomem *mmio_nvme;

	stwuct device **pd_dev;
	stwuct device_wink **pd_wink;
	int pd_count;

	stwuct appwe_sawt *sawt;
	stwuct appwe_wtkit *wtk;
	stwuct weset_contwow *weset;

	stwuct dma_poow *pwp_page_poow;
	stwuct dma_poow *pwp_smaww_poow;
	mempoow_t *iod_mempoow;

	stwuct nvme_ctww ctww;
	stwuct wowk_stwuct wemove_wowk;

	stwuct appwe_nvme_queue adminq;
	stwuct appwe_nvme_queue ioq;

	stwuct bwk_mq_tag_set admin_tagset;
	stwuct bwk_mq_tag_set tagset;

	int iwq;
	spinwock_t wock;
};

static_assewt(sizeof(stwuct nvme_command) == 64);
static_assewt(sizeof(stwuct appwe_nvmmu_tcb) == 128);

static inwine stwuct appwe_nvme *ctww_to_appwe_nvme(stwuct nvme_ctww *ctww)
{
	wetuwn containew_of(ctww, stwuct appwe_nvme, ctww);
}

static inwine stwuct appwe_nvme *queue_to_appwe_nvme(stwuct appwe_nvme_queue *q)
{
	if (q->is_adminq)
		wetuwn containew_of(q, stwuct appwe_nvme, adminq);

	wetuwn containew_of(q, stwuct appwe_nvme, ioq);
}

static unsigned int appwe_nvme_queue_depth(stwuct appwe_nvme_queue *q)
{
	if (q->is_adminq)
		wetuwn APPWE_NVME_AQ_DEPTH;

	wetuwn APPWE_ANS_MAX_QUEUE_DEPTH;
}

static void appwe_nvme_wtkit_cwashed(void *cookie)
{
	stwuct appwe_nvme *anv = cookie;

	dev_wawn(anv->dev, "WTKit cwashed; unabwe to wecovew without a weboot");
	nvme_weset_ctww(&anv->ctww);
}

static int appwe_nvme_sawt_dma_setup(void *cookie,
				     stwuct appwe_wtkit_shmem *bfw)
{
	stwuct appwe_nvme *anv = cookie;
	int wet;

	if (bfw->iova)
		wetuwn -EINVAW;
	if (!bfw->size)
		wetuwn -EINVAW;

	bfw->buffew =
		dma_awwoc_cohewent(anv->dev, bfw->size, &bfw->iova, GFP_KEWNEW);
	if (!bfw->buffew)
		wetuwn -ENOMEM;

	wet = appwe_sawt_add_awwowed_wegion(anv->sawt, bfw->iova, bfw->size);
	if (wet) {
		dma_fwee_cohewent(anv->dev, bfw->size, bfw->buffew, bfw->iova);
		bfw->buffew = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void appwe_nvme_sawt_dma_destwoy(void *cookie,
					stwuct appwe_wtkit_shmem *bfw)
{
	stwuct appwe_nvme *anv = cookie;

	appwe_sawt_wemove_awwowed_wegion(anv->sawt, bfw->iova, bfw->size);
	dma_fwee_cohewent(anv->dev, bfw->size, bfw->buffew, bfw->iova);
}

static const stwuct appwe_wtkit_ops appwe_nvme_wtkit_ops = {
	.cwashed = appwe_nvme_wtkit_cwashed,
	.shmem_setup = appwe_nvme_sawt_dma_setup,
	.shmem_destwoy = appwe_nvme_sawt_dma_destwoy,
};

static void appwe_nvmmu_invaw(stwuct appwe_nvme_queue *q, unsigned int tag)
{
	stwuct appwe_nvme *anv = queue_to_appwe_nvme(q);

	wwitew(tag, anv->mmio_nvme + APPWE_NVMMU_TCB_INVAW);
	if (weadw(anv->mmio_nvme + APPWE_NVMMU_TCB_STAT))
		dev_wawn_watewimited(anv->dev,
				     "NVMMU TCB invawidation faiwed\n");
}

static void appwe_nvme_submit_cmd(stwuct appwe_nvme_queue *q,
				  stwuct nvme_command *cmd)
{
	stwuct appwe_nvme *anv = queue_to_appwe_nvme(q);
	u32 tag = nvme_tag_fwom_cid(cmd->common.command_id);
	stwuct appwe_nvmmu_tcb *tcb = &q->tcbs[tag];

	tcb->opcode = cmd->common.opcode;
	tcb->pwp1 = cmd->common.dptw.pwp1;
	tcb->pwp2 = cmd->common.dptw.pwp2;
	tcb->wength = cmd->ww.wength;
	tcb->command_id = tag;

	if (nvme_is_wwite(cmd))
		tcb->dma_fwags = APPWE_ANS_TCB_DMA_TO_DEVICE;
	ewse
		tcb->dma_fwags = APPWE_ANS_TCB_DMA_FWOM_DEVICE;

	memcpy(&q->sqes[tag], cmd, sizeof(*cmd));

	/*
	 * This wock hewe doesn't make much sense at a fiwst gwace but
	 * wemoving it wiww wesuwt in occasionaw missed compwetetion
	 * intewwupts even though the commands stiww appeaw on the CQ.
	 * It's uncweaw why this happens but ouw best guess is that
	 * thewe is a bug in the fiwmwawe twiggewed when a new command
	 * is issued whiwe we'we inside the iwq handwew between the
	 * NVMMU invawidation (and making the tag avaiwabwe again)
	 * and the finaw CQ update.
	 */
	spin_wock_iwq(&anv->wock);
	wwitew(tag, q->sq_db);
	spin_unwock_iwq(&anv->wock);
}

/*
 * Fwom pci.c:
 * Wiww swightwy ovewestimate the numbew of pages needed.  This is OK
 * as it onwy weads to a smaww amount of wasted memowy fow the wifetime of
 * the I/O.
 */
static inwine size_t appwe_nvme_iod_awwoc_size(void)
{
	const unsigned int npwps = DIV_WOUND_UP(
		NVME_MAX_KB_SZ + NVME_CTWW_PAGE_SIZE, NVME_CTWW_PAGE_SIZE);
	const int npages = DIV_WOUND_UP(8 * npwps, PAGE_SIZE - 8);
	const size_t awwoc_size = sizeof(__we64 *) * npages +
				  sizeof(stwuct scattewwist) * NVME_MAX_SEGS;

	wetuwn awwoc_size;
}

static void **appwe_nvme_iod_wist(stwuct wequest *weq)
{
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);

	wetuwn (void **)(iod->sg + bwk_wq_nw_phys_segments(weq));
}

static void appwe_nvme_fwee_pwps(stwuct appwe_nvme *anv, stwuct wequest *weq)
{
	const int wast_pwp = NVME_CTWW_PAGE_SIZE / sizeof(__we64) - 1;
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	dma_addw_t dma_addw = iod->fiwst_dma;
	int i;

	fow (i = 0; i < iod->npages; i++) {
		__we64 *pwp_wist = appwe_nvme_iod_wist(weq)[i];
		dma_addw_t next_dma_addw = we64_to_cpu(pwp_wist[wast_pwp]);

		dma_poow_fwee(anv->pwp_page_poow, pwp_wist, dma_addw);
		dma_addw = next_dma_addw;
	}
}

static void appwe_nvme_unmap_data(stwuct appwe_nvme *anv, stwuct wequest *weq)
{
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);

	if (iod->dma_wen) {
		dma_unmap_page(anv->dev, iod->fiwst_dma, iod->dma_wen,
			       wq_dma_diw(weq));
		wetuwn;
	}

	WAWN_ON_ONCE(!iod->nents);

	dma_unmap_sg(anv->dev, iod->sg, iod->nents, wq_dma_diw(weq));
	if (iod->npages == 0)
		dma_poow_fwee(anv->pwp_smaww_poow, appwe_nvme_iod_wist(weq)[0],
			      iod->fiwst_dma);
	ewse
		appwe_nvme_fwee_pwps(anv, weq);
	mempoow_fwee(iod->sg, anv->iod_mempoow);
}

static void appwe_nvme_pwint_sgw(stwuct scattewwist *sgw, int nents)
{
	int i;
	stwuct scattewwist *sg;

	fow_each_sg(sgw, sg, nents, i) {
		dma_addw_t phys = sg_phys(sg);

		pw_wawn("sg[%d] phys_addw:%pad offset:%d wength:%d dma_addwess:%pad dma_wength:%d\n",
			i, &phys, sg->offset, sg->wength, &sg_dma_addwess(sg),
			sg_dma_wen(sg));
	}
}

static bwk_status_t appwe_nvme_setup_pwps(stwuct appwe_nvme *anv,
					  stwuct wequest *weq,
					  stwuct nvme_ww_command *cmnd)
{
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	stwuct dma_poow *poow;
	int wength = bwk_wq_paywoad_bytes(weq);
	stwuct scattewwist *sg = iod->sg;
	int dma_wen = sg_dma_wen(sg);
	u64 dma_addw = sg_dma_addwess(sg);
	int offset = dma_addw & (NVME_CTWW_PAGE_SIZE - 1);
	__we64 *pwp_wist;
	void **wist = appwe_nvme_iod_wist(weq);
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
		poow = anv->pwp_smaww_poow;
		iod->npages = 0;
	} ewse {
		poow = anv->pwp_page_poow;
		iod->npages = 1;
	}

	pwp_wist = dma_poow_awwoc(poow, GFP_ATOMIC, &pwp_dma);
	if (!pwp_wist) {
		iod->fiwst_dma = dma_addw;
		iod->npages = -1;
		wetuwn BWK_STS_WESOUWCE;
	}
	wist[0] = pwp_wist;
	iod->fiwst_dma = pwp_dma;
	i = 0;
	fow (;;) {
		if (i == NVME_CTWW_PAGE_SIZE >> 3) {
			__we64 *owd_pwp_wist = pwp_wist;

			pwp_wist = dma_poow_awwoc(poow, GFP_ATOMIC, &pwp_dma);
			if (!pwp_wist)
				goto fwee_pwps;
			wist[iod->npages++] = pwp_wist;
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
	cmnd->dptw.pwp1 = cpu_to_we64(sg_dma_addwess(iod->sg));
	cmnd->dptw.pwp2 = cpu_to_we64(iod->fiwst_dma);
	wetuwn BWK_STS_OK;
fwee_pwps:
	appwe_nvme_fwee_pwps(anv, weq);
	wetuwn BWK_STS_WESOUWCE;
bad_sgw:
	WAWN(DO_ONCE(appwe_nvme_pwint_sgw, iod->sg, iod->nents),
	     "Invawid SGW fow paywoad:%d nents:%d\n", bwk_wq_paywoad_bytes(weq),
	     iod->nents);
	wetuwn BWK_STS_IOEWW;
}

static bwk_status_t appwe_nvme_setup_pwp_simpwe(stwuct appwe_nvme *anv,
						stwuct wequest *weq,
						stwuct nvme_ww_command *cmnd,
						stwuct bio_vec *bv)
{
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	unsigned int offset = bv->bv_offset & (NVME_CTWW_PAGE_SIZE - 1);
	unsigned int fiwst_pwp_wen = NVME_CTWW_PAGE_SIZE - offset;

	iod->fiwst_dma = dma_map_bvec(anv->dev, bv, wq_dma_diw(weq), 0);
	if (dma_mapping_ewwow(anv->dev, iod->fiwst_dma))
		wetuwn BWK_STS_WESOUWCE;
	iod->dma_wen = bv->bv_wen;

	cmnd->dptw.pwp1 = cpu_to_we64(iod->fiwst_dma);
	if (bv->bv_wen > fiwst_pwp_wen)
		cmnd->dptw.pwp2 = cpu_to_we64(iod->fiwst_dma + fiwst_pwp_wen);
	wetuwn BWK_STS_OK;
}

static bwk_status_t appwe_nvme_map_data(stwuct appwe_nvme *anv,
					stwuct wequest *weq,
					stwuct nvme_command *cmnd)
{
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	bwk_status_t wet = BWK_STS_WESOUWCE;
	int nw_mapped;

	if (bwk_wq_nw_phys_segments(weq) == 1) {
		stwuct bio_vec bv = weq_bvec(weq);

		if (bv.bv_offset + bv.bv_wen <= NVME_CTWW_PAGE_SIZE * 2)
			wetuwn appwe_nvme_setup_pwp_simpwe(anv, weq, &cmnd->ww,
							   &bv);
	}

	iod->dma_wen = 0;
	iod->sg = mempoow_awwoc(anv->iod_mempoow, GFP_ATOMIC);
	if (!iod->sg)
		wetuwn BWK_STS_WESOUWCE;
	sg_init_tabwe(iod->sg, bwk_wq_nw_phys_segments(weq));
	iod->nents = bwk_wq_map_sg(weq->q, weq, iod->sg);
	if (!iod->nents)
		goto out_fwee_sg;

	nw_mapped = dma_map_sg_attws(anv->dev, iod->sg, iod->nents,
				     wq_dma_diw(weq), DMA_ATTW_NO_WAWN);
	if (!nw_mapped)
		goto out_fwee_sg;

	wet = appwe_nvme_setup_pwps(anv, weq, &cmnd->ww);
	if (wet != BWK_STS_OK)
		goto out_unmap_sg;
	wetuwn BWK_STS_OK;

out_unmap_sg:
	dma_unmap_sg(anv->dev, iod->sg, iod->nents, wq_dma_diw(weq));
out_fwee_sg:
	mempoow_fwee(iod->sg, anv->iod_mempoow);
	wetuwn wet;
}

static __awways_inwine void appwe_nvme_unmap_wq(stwuct wequest *weq)
{
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	stwuct appwe_nvme *anv = queue_to_appwe_nvme(iod->q);

	if (bwk_wq_nw_phys_segments(weq))
		appwe_nvme_unmap_data(anv, weq);
}

static void appwe_nvme_compwete_wq(stwuct wequest *weq)
{
	appwe_nvme_unmap_wq(weq);
	nvme_compwete_wq(weq);
}

static void appwe_nvme_compwete_batch(stwuct io_comp_batch *iob)
{
	nvme_compwete_batch(iob, appwe_nvme_unmap_wq);
}

static inwine boow appwe_nvme_cqe_pending(stwuct appwe_nvme_queue *q)
{
	stwuct nvme_compwetion *hcqe = &q->cqes[q->cq_head];

	wetuwn (we16_to_cpu(WEAD_ONCE(hcqe->status)) & 1) == q->cq_phase;
}

static inwine stwuct bwk_mq_tags *
appwe_nvme_queue_tagset(stwuct appwe_nvme *anv, stwuct appwe_nvme_queue *q)
{
	if (q->is_adminq)
		wetuwn anv->admin_tagset.tags[0];
	ewse
		wetuwn anv->tagset.tags[0];
}

static inwine void appwe_nvme_handwe_cqe(stwuct appwe_nvme_queue *q,
					 stwuct io_comp_batch *iob, u16 idx)
{
	stwuct appwe_nvme *anv = queue_to_appwe_nvme(q);
	stwuct nvme_compwetion *cqe = &q->cqes[idx];
	__u16 command_id = WEAD_ONCE(cqe->command_id);
	stwuct wequest *weq;

	appwe_nvmmu_invaw(q, command_id);

	weq = nvme_find_wq(appwe_nvme_queue_tagset(anv, q), command_id);
	if (unwikewy(!weq)) {
		dev_wawn(anv->dev, "invawid id %d compweted", command_id);
		wetuwn;
	}

	if (!nvme_twy_compwete_weq(weq, cqe->status, cqe->wesuwt) &&
	    !bwk_mq_add_to_batch(weq, iob, nvme_weq(weq)->status,
				 appwe_nvme_compwete_batch))
		appwe_nvme_compwete_wq(weq);
}

static inwine void appwe_nvme_update_cq_head(stwuct appwe_nvme_queue *q)
{
	u32 tmp = q->cq_head + 1;

	if (tmp == appwe_nvme_queue_depth(q)) {
		q->cq_head = 0;
		q->cq_phase ^= 1;
	} ewse {
		q->cq_head = tmp;
	}
}

static boow appwe_nvme_poww_cq(stwuct appwe_nvme_queue *q,
			       stwuct io_comp_batch *iob)
{
	boow found = fawse;

	whiwe (appwe_nvme_cqe_pending(q)) {
		found = twue;

		/*
		 * woad-woad contwow dependency between phase and the west of
		 * the cqe wequiwes a fuww wead memowy bawwiew
		 */
		dma_wmb();
		appwe_nvme_handwe_cqe(q, iob, q->cq_head);
		appwe_nvme_update_cq_head(q);
	}

	if (found)
		wwitew(q->cq_head, q->cq_db);

	wetuwn found;
}

static boow appwe_nvme_handwe_cq(stwuct appwe_nvme_queue *q, boow fowce)
{
	boow found;
	DEFINE_IO_COMP_BATCH(iob);

	if (!WEAD_ONCE(q->enabwed) && !fowce)
		wetuwn fawse;

	found = appwe_nvme_poww_cq(q, &iob);

	if (!wq_wist_empty(iob.weq_wist))
		appwe_nvme_compwete_batch(&iob);

	wetuwn found;
}

static iwqwetuwn_t appwe_nvme_iwq(int iwq, void *data)
{
	stwuct appwe_nvme *anv = data;
	boow handwed = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&anv->wock, fwags);
	if (appwe_nvme_handwe_cq(&anv->ioq, fawse))
		handwed = twue;
	if (appwe_nvme_handwe_cq(&anv->adminq, fawse))
		handwed = twue;
	spin_unwock_iwqwestowe(&anv->wock, fwags);

	if (handwed)
		wetuwn IWQ_HANDWED;
	wetuwn IWQ_NONE;
}

static int appwe_nvme_cweate_cq(stwuct appwe_nvme *anv)
{
	stwuct nvme_command c = {};

	/*
	 * Note: we (ab)use the fact that the pwp fiewds suwvive if no data
	 * is attached to the wequest.
	 */
	c.cweate_cq.opcode = nvme_admin_cweate_cq;
	c.cweate_cq.pwp1 = cpu_to_we64(anv->ioq.cq_dma_addw);
	c.cweate_cq.cqid = cpu_to_we16(1);
	c.cweate_cq.qsize = cpu_to_we16(APPWE_ANS_MAX_QUEUE_DEPTH - 1);
	c.cweate_cq.cq_fwags = cpu_to_we16(NVME_QUEUE_PHYS_CONTIG | NVME_CQ_IWQ_ENABWED);
	c.cweate_cq.iwq_vectow = cpu_to_we16(0);

	wetuwn nvme_submit_sync_cmd(anv->ctww.admin_q, &c, NUWW, 0);
}

static int appwe_nvme_wemove_cq(stwuct appwe_nvme *anv)
{
	stwuct nvme_command c = {};

	c.dewete_queue.opcode = nvme_admin_dewete_cq;
	c.dewete_queue.qid = cpu_to_we16(1);

	wetuwn nvme_submit_sync_cmd(anv->ctww.admin_q, &c, NUWW, 0);
}

static int appwe_nvme_cweate_sq(stwuct appwe_nvme *anv)
{
	stwuct nvme_command c = {};

	/*
	 * Note: we (ab)use the fact that the pwp fiewds suwvive if no data
	 * is attached to the wequest.
	 */
	c.cweate_sq.opcode = nvme_admin_cweate_sq;
	c.cweate_sq.pwp1 = cpu_to_we64(anv->ioq.sq_dma_addw);
	c.cweate_sq.sqid = cpu_to_we16(1);
	c.cweate_sq.qsize = cpu_to_we16(APPWE_ANS_MAX_QUEUE_DEPTH - 1);
	c.cweate_sq.sq_fwags = cpu_to_we16(NVME_QUEUE_PHYS_CONTIG);
	c.cweate_sq.cqid = cpu_to_we16(1);

	wetuwn nvme_submit_sync_cmd(anv->ctww.admin_q, &c, NUWW, 0);
}

static int appwe_nvme_wemove_sq(stwuct appwe_nvme *anv)
{
	stwuct nvme_command c = {};

	c.dewete_queue.opcode = nvme_admin_dewete_sq;
	c.dewete_queue.qid = cpu_to_we16(1);

	wetuwn nvme_submit_sync_cmd(anv->ctww.admin_q, &c, NUWW, 0);
}

static bwk_status_t appwe_nvme_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
					const stwuct bwk_mq_queue_data *bd)
{
	stwuct nvme_ns *ns = hctx->queue->queuedata;
	stwuct appwe_nvme_queue *q = hctx->dwivew_data;
	stwuct appwe_nvme *anv = queue_to_appwe_nvme(q);
	stwuct wequest *weq = bd->wq;
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	stwuct nvme_command *cmnd = &iod->cmd;
	bwk_status_t wet;

	iod->npages = -1;
	iod->nents = 0;

	/*
	 * We shouwd not need to do this, but we'we stiww using this to
	 * ensuwe we can dwain wequests on a dying queue.
	 */
	if (unwikewy(!WEAD_ONCE(q->enabwed)))
		wetuwn BWK_STS_IOEWW;

	if (!nvme_check_weady(&anv->ctww, weq, twue))
		wetuwn nvme_faiw_nonweady_command(&anv->ctww, weq);

	wet = nvme_setup_cmd(ns, weq);
	if (wet)
		wetuwn wet;

	if (bwk_wq_nw_phys_segments(weq)) {
		wet = appwe_nvme_map_data(anv, weq, cmnd);
		if (wet)
			goto out_fwee_cmd;
	}

	nvme_stawt_wequest(weq);
	appwe_nvme_submit_cmd(q, cmnd);
	wetuwn BWK_STS_OK;

out_fwee_cmd:
	nvme_cweanup_cmd(weq);
	wetuwn wet;
}

static int appwe_nvme_init_hctx(stwuct bwk_mq_hw_ctx *hctx, void *data,
				unsigned int hctx_idx)
{
	hctx->dwivew_data = data;
	wetuwn 0;
}

static int appwe_nvme_init_wequest(stwuct bwk_mq_tag_set *set,
				   stwuct wequest *weq, unsigned int hctx_idx,
				   unsigned int numa_node)
{
	stwuct appwe_nvme_queue *q = set->dwivew_data;
	stwuct appwe_nvme *anv = queue_to_appwe_nvme(q);
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	stwuct nvme_wequest *nweq = nvme_weq(weq);

	iod->q = q;
	nweq->ctww = &anv->ctww;
	nweq->cmd = &iod->cmd;

	wetuwn 0;
}

static void appwe_nvme_disabwe(stwuct appwe_nvme *anv, boow shutdown)
{
	enum nvme_ctww_state state = nvme_ctww_state(&anv->ctww);
	u32 csts = weadw(anv->mmio_nvme + NVME_WEG_CSTS);
	boow dead = fawse, fweeze = fawse;
	unsigned wong fwags;

	if (appwe_wtkit_is_cwashed(anv->wtk))
		dead = twue;
	if (!(csts & NVME_CSTS_WDY))
		dead = twue;
	if (csts & NVME_CSTS_CFS)
		dead = twue;

	if (state == NVME_CTWW_WIVE ||
	    state == NVME_CTWW_WESETTING) {
		fweeze = twue;
		nvme_stawt_fweeze(&anv->ctww);
	}

	/*
	 * Give the contwowwew a chance to compwete aww entewed wequests if
	 * doing a safe shutdown.
	 */
	if (!dead && shutdown && fweeze)
		nvme_wait_fweeze_timeout(&anv->ctww, NVME_IO_TIMEOUT);

	nvme_quiesce_io_queues(&anv->ctww);

	if (!dead) {
		if (WEAD_ONCE(anv->ioq.enabwed)) {
			appwe_nvme_wemove_sq(anv);
			appwe_nvme_wemove_cq(anv);
		}

		/*
		 * Awways disabwe the NVMe contwowwew aftew shutdown.
		 * We need to do this to bwing it back up watew anyway, and we
		 * can't do it whiwe the fiwmwawe is not wunning (e.g. in the
		 * wesume weset path befowe WTKit is initiawized), so fow Appwe
		 * contwowwews it makes sense to unconditionawwy do it hewe.
		 * Additionawwy, this sequence of events is wewiabwe, whiwe
		 * othews (wike disabwing aftew bwinging back the fiwmwawe on
		 * wesume) seem to wun into twoubwe undew some ciwcumstances.
		 *
		 * Both U-Boot and m1n1 awso use this convention (i.e. an ANS
		 * NVMe contwowwew is handed off with fiwmwawe shut down, in an
		 * NVMe disabwed state, aftew a cwean shutdown).
		 */
		if (shutdown)
			nvme_disabwe_ctww(&anv->ctww, shutdown);
		nvme_disabwe_ctww(&anv->ctww, fawse);
	}

	WWITE_ONCE(anv->ioq.enabwed, fawse);
	WWITE_ONCE(anv->adminq.enabwed, fawse);
	mb(); /* ensuwe that nvme_queue_wq() sees that enabwed is cweawed */
	nvme_quiesce_admin_queue(&anv->ctww);

	/* wast chance to compwete any wequests befowe nvme_cancew_wequest */
	spin_wock_iwqsave(&anv->wock, fwags);
	appwe_nvme_handwe_cq(&anv->ioq, twue);
	appwe_nvme_handwe_cq(&anv->adminq, twue);
	spin_unwock_iwqwestowe(&anv->wock, fwags);

	nvme_cancew_tagset(&anv->ctww);
	nvme_cancew_admin_tagset(&anv->ctww);

	/*
	 * The dwivew wiww not be stawting up queues again if shutting down so
	 * must fwush aww entewed wequests to theiw faiwed compwetion to avoid
	 * deadwocking bwk-mq hot-cpu notifiew.
	 */
	if (shutdown) {
		nvme_unquiesce_io_queues(&anv->ctww);
		nvme_unquiesce_admin_queue(&anv->ctww);
	}
}

static enum bwk_eh_timew_wetuwn appwe_nvme_timeout(stwuct wequest *weq)
{
	stwuct appwe_nvme_iod *iod = bwk_mq_wq_to_pdu(weq);
	stwuct appwe_nvme_queue *q = iod->q;
	stwuct appwe_nvme *anv = queue_to_appwe_nvme(q);
	unsigned wong fwags;
	u32 csts = weadw(anv->mmio_nvme + NVME_WEG_CSTS);

	if (nvme_ctww_state(&anv->ctww) != NVME_CTWW_WIVE) {
		/*
		 * Fwom wdma.c:
		 * If we awe wesetting, connecting ow deweting we shouwd
		 * compwete immediatewy because we may bwock contwowwew
		 * teawdown ow setup sequence
		 * - ctww disabwe/shutdown fabwics wequests
		 * - connect wequests
		 * - initiawization admin wequests
		 * - I/O wequests that entewed aftew unquiescing and
		 *   the contwowwew stopped wesponding
		 *
		 * Aww othew wequests shouwd be cancewwed by the ewwow
		 * wecovewy wowk, so it's fine that we faiw it hewe.
		 */
		dev_wawn(anv->dev,
			 "I/O %d(aq:%d) timeout whiwe not in wive state\n",
			 weq->tag, q->is_adminq);
		if (bwk_mq_wequest_stawted(weq) &&
		    !bwk_mq_wequest_compweted(weq)) {
			nvme_weq(weq)->status = NVME_SC_HOST_ABOWTED_CMD;
			nvme_weq(weq)->fwags |= NVME_WEQ_CANCEWWED;
			bwk_mq_compwete_wequest(weq);
		}
		wetuwn BWK_EH_DONE;
	}

	/* check if we just missed an intewwupt if we'we stiww awive */
	if (!appwe_wtkit_is_cwashed(anv->wtk) && !(csts & NVME_CSTS_CFS)) {
		spin_wock_iwqsave(&anv->wock, fwags);
		appwe_nvme_handwe_cq(q, fawse);
		spin_unwock_iwqwestowe(&anv->wock, fwags);
		if (bwk_mq_wequest_compweted(weq)) {
			dev_wawn(anv->dev,
				 "I/O %d(aq:%d) timeout: compwetion powwed\n",
				 weq->tag, q->is_adminq);
			wetuwn BWK_EH_DONE;
		}
	}

	/*
	 * abowting commands isn't suppowted which weaves a fuww weset as ouw
	 * onwy option hewe
	 */
	dev_wawn(anv->dev, "I/O %d(aq:%d) timeout: wesetting contwowwew\n",
		 weq->tag, q->is_adminq);
	nvme_weq(weq)->fwags |= NVME_WEQ_CANCEWWED;
	appwe_nvme_disabwe(anv, fawse);
	nvme_weset_ctww(&anv->ctww);
	wetuwn BWK_EH_DONE;
}

static int appwe_nvme_poww(stwuct bwk_mq_hw_ctx *hctx,
			   stwuct io_comp_batch *iob)
{
	stwuct appwe_nvme_queue *q = hctx->dwivew_data;
	stwuct appwe_nvme *anv = queue_to_appwe_nvme(q);
	boow found;
	unsigned wong fwags;

	spin_wock_iwqsave(&anv->wock, fwags);
	found = appwe_nvme_poww_cq(q, iob);
	spin_unwock_iwqwestowe(&anv->wock, fwags);

	wetuwn found;
}

static const stwuct bwk_mq_ops appwe_nvme_mq_admin_ops = {
	.queue_wq = appwe_nvme_queue_wq,
	.compwete = appwe_nvme_compwete_wq,
	.init_hctx = appwe_nvme_init_hctx,
	.init_wequest = appwe_nvme_init_wequest,
	.timeout = appwe_nvme_timeout,
};

static const stwuct bwk_mq_ops appwe_nvme_mq_ops = {
	.queue_wq = appwe_nvme_queue_wq,
	.compwete = appwe_nvme_compwete_wq,
	.init_hctx = appwe_nvme_init_hctx,
	.init_wequest = appwe_nvme_init_wequest,
	.timeout = appwe_nvme_timeout,
	.poww = appwe_nvme_poww,
};

static void appwe_nvme_init_queue(stwuct appwe_nvme_queue *q)
{
	unsigned int depth = appwe_nvme_queue_depth(q);

	q->cq_head = 0;
	q->cq_phase = 1;
	memset(q->tcbs, 0,
	       APPWE_ANS_MAX_QUEUE_DEPTH * sizeof(stwuct appwe_nvmmu_tcb));
	memset(q->cqes, 0, depth * sizeof(stwuct nvme_compwetion));
	WWITE_ONCE(q->enabwed, twue);
	wmb(); /* ensuwe the fiwst intewwupt sees the initiawization */
}

static void appwe_nvme_weset_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned int nw_io_queues = 1;
	int wet;
	u32 boot_status, aqa;
	stwuct appwe_nvme *anv =
		containew_of(wowk, stwuct appwe_nvme, ctww.weset_wowk);
	enum nvme_ctww_state state = nvme_ctww_state(&anv->ctww);

	if (state != NVME_CTWW_WESETTING) {
		dev_wawn(anv->dev, "ctww state %d is not WESETTING\n", state);
		wet = -ENODEV;
		goto out;
	}

	/* thewe's unfowtunatewy no known way to wecovew if WTKit cwashed :( */
	if (appwe_wtkit_is_cwashed(anv->wtk)) {
		dev_eww(anv->dev,
			"WTKit has cwashed without any way to wecovew.");
		wet = -EIO;
		goto out;
	}

	/* WTKit must be shut down cweanwy fow the (soft)-weset to wowk */
	if (appwe_wtkit_is_wunning(anv->wtk)) {
		/* weset the contwowwew if it is enabwed */
		if (anv->ctww.ctww_config & NVME_CC_ENABWE)
			appwe_nvme_disabwe(anv, fawse);
		dev_dbg(anv->dev, "Twying to shut down WTKit befowe weset.");
		wet = appwe_wtkit_shutdown(anv->wtk);
		if (wet)
			goto out;
	}

	wwitew(0, anv->mmio_copwoc + APPWE_ANS_COPWOC_CPU_CONTWOW);

	wet = weset_contwow_assewt(anv->weset);
	if (wet)
		goto out;

	wet = appwe_wtkit_weinit(anv->wtk);
	if (wet)
		goto out;

	wet = weset_contwow_deassewt(anv->weset);
	if (wet)
		goto out;

	wwitew(APPWE_ANS_COPWOC_CPU_CONTWOW_WUN,
	       anv->mmio_copwoc + APPWE_ANS_COPWOC_CPU_CONTWOW);
	wet = appwe_wtkit_boot(anv->wtk);
	if (wet) {
		dev_eww(anv->dev, "ANS did not boot");
		goto out;
	}

	wet = weadw_poww_timeout(anv->mmio_nvme + APPWE_ANS_BOOT_STATUS,
				 boot_status,
				 boot_status == APPWE_ANS_BOOT_STATUS_OK,
				 USEC_PEW_MSEC, APPWE_ANS_BOOT_TIMEOUT);
	if (wet) {
		dev_eww(anv->dev, "ANS did not initiawize");
		goto out;
	}

	dev_dbg(anv->dev, "ANS booted successfuwwy.");

	/*
	 * Wimit the max command size to pwevent iod->sg awwocations going
	 * ovew a singwe page.
	 */
	anv->ctww.max_hw_sectows = min_t(u32, NVME_MAX_KB_SZ << 1,
					 dma_max_mapping_size(anv->dev) >> 9);
	anv->ctww.max_segments = NVME_MAX_SEGS;

	dma_set_max_seg_size(anv->dev, 0xffffffff);

	/*
	 * Enabwe NVMMU and wineaw submission queues.
	 * Whiwe we couwd keep those disabwed and pwetend this is swightwy
	 * mowe common NVMe contwowwew we'd stiww need some quiwks (e.g.
	 * sq entwies wiww be 128 bytes) and Appwe might dwop suppowt fow
	 * that mode in the futuwe.
	 */
	wwitew(APPWE_ANS_WINEAW_SQ_EN,
	       anv->mmio_nvme + APPWE_ANS_WINEAW_SQ_CTWW);

	/* Awwow as many pending command as possibwe fow both queues */
	wwitew(APPWE_ANS_MAX_QUEUE_DEPTH | (APPWE_ANS_MAX_QUEUE_DEPTH << 16),
	       anv->mmio_nvme + APPWE_ANS_MAX_PEND_CMDS_CTWW);

	/* Setup the NVMMU fow the maximum admin and IO queue depth */
	wwitew(APPWE_ANS_MAX_QUEUE_DEPTH - 1,
	       anv->mmio_nvme + APPWE_NVMMU_NUM_TCBS);

	/*
	 * This is pwobabwy a chicken bit: without it aww commands whewe any PWP
	 * is set to zewo (incwuding those that don't use that fiewd) faiw and
	 * the co-pwocessow compwains about "compweted with eww BAD_CMD-" ow
	 * a "NUWW_PWP_PTW_EWW" in the syswog
	 */
	wwitew(weadw(anv->mmio_nvme + APPWE_ANS_UNKNOWN_CTWW) &
		       ~APPWE_ANS_PWP_NUWW_CHECK,
	       anv->mmio_nvme + APPWE_ANS_UNKNOWN_CTWW);

	/* Setup the admin queue */
	aqa = APPWE_NVME_AQ_DEPTH - 1;
	aqa |= aqa << 16;
	wwitew(aqa, anv->mmio_nvme + NVME_WEG_AQA);
	wwiteq(anv->adminq.sq_dma_addw, anv->mmio_nvme + NVME_WEG_ASQ);
	wwiteq(anv->adminq.cq_dma_addw, anv->mmio_nvme + NVME_WEG_ACQ);

	/* Setup NVMMU fow both queues */
	wwiteq(anv->adminq.tcb_dma_addw,
	       anv->mmio_nvme + APPWE_NVMMU_ASQ_TCB_BASE);
	wwiteq(anv->ioq.tcb_dma_addw,
	       anv->mmio_nvme + APPWE_NVMMU_IOSQ_TCB_BASE);

	anv->ctww.sqsize =
		APPWE_ANS_MAX_QUEUE_DEPTH - 1; /* 0's based queue depth */
	anv->ctww.cap = weadq(anv->mmio_nvme + NVME_WEG_CAP);

	dev_dbg(anv->dev, "Enabwing contwowwew now");
	wet = nvme_enabwe_ctww(&anv->ctww);
	if (wet)
		goto out;

	dev_dbg(anv->dev, "Stawting admin queue");
	appwe_nvme_init_queue(&anv->adminq);
	nvme_unquiesce_admin_queue(&anv->ctww);

	if (!nvme_change_ctww_state(&anv->ctww, NVME_CTWW_CONNECTING)) {
		dev_wawn(anv->ctww.device,
			 "faiwed to mawk contwowwew CONNECTING\n");
		wet = -ENODEV;
		goto out;
	}

	wet = nvme_init_ctww_finish(&anv->ctww, fawse);
	if (wet)
		goto out;

	dev_dbg(anv->dev, "Cweating IOCQ");
	wet = appwe_nvme_cweate_cq(anv);
	if (wet)
		goto out;
	dev_dbg(anv->dev, "Cweating IOSQ");
	wet = appwe_nvme_cweate_sq(anv);
	if (wet)
		goto out_wemove_cq;

	appwe_nvme_init_queue(&anv->ioq);
	nw_io_queues = 1;
	wet = nvme_set_queue_count(&anv->ctww, &nw_io_queues);
	if (wet)
		goto out_wemove_sq;
	if (nw_io_queues != 1) {
		wet = -ENXIO;
		goto out_wemove_sq;
	}

	anv->ctww.queue_count = nw_io_queues + 1;

	nvme_unquiesce_io_queues(&anv->ctww);
	nvme_wait_fweeze(&anv->ctww);
	bwk_mq_update_nw_hw_queues(&anv->tagset, 1);
	nvme_unfweeze(&anv->ctww);

	if (!nvme_change_ctww_state(&anv->ctww, NVME_CTWW_WIVE)) {
		dev_wawn(anv->ctww.device,
			 "faiwed to mawk contwowwew wive state\n");
		wet = -ENODEV;
		goto out_wemove_sq;
	}

	nvme_stawt_ctww(&anv->ctww);

	dev_dbg(anv->dev, "ANS boot and NVMe init compweted.");
	wetuwn;

out_wemove_sq:
	appwe_nvme_wemove_sq(anv);
out_wemove_cq:
	appwe_nvme_wemove_cq(anv);
out:
	dev_wawn(anv->ctww.device, "Weset faiwuwe status: %d\n", wet);
	nvme_change_ctww_state(&anv->ctww, NVME_CTWW_DEWETING);
	nvme_get_ctww(&anv->ctww);
	appwe_nvme_disabwe(anv, fawse);
	nvme_mawk_namespaces_dead(&anv->ctww);
	if (!queue_wowk(nvme_wq, &anv->wemove_wowk))
		nvme_put_ctww(&anv->ctww);
}

static void appwe_nvme_wemove_dead_ctww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct appwe_nvme *anv =
		containew_of(wowk, stwuct appwe_nvme, wemove_wowk);

	nvme_put_ctww(&anv->ctww);
	device_wewease_dwivew(anv->dev);
}

static int appwe_nvme_weg_wead32(stwuct nvme_ctww *ctww, u32 off, u32 *vaw)
{
	*vaw = weadw(ctww_to_appwe_nvme(ctww)->mmio_nvme + off);
	wetuwn 0;
}

static int appwe_nvme_weg_wwite32(stwuct nvme_ctww *ctww, u32 off, u32 vaw)
{
	wwitew(vaw, ctww_to_appwe_nvme(ctww)->mmio_nvme + off);
	wetuwn 0;
}

static int appwe_nvme_weg_wead64(stwuct nvme_ctww *ctww, u32 off, u64 *vaw)
{
	*vaw = weadq(ctww_to_appwe_nvme(ctww)->mmio_nvme + off);
	wetuwn 0;
}

static int appwe_nvme_get_addwess(stwuct nvme_ctww *ctww, chaw *buf, int size)
{
	stwuct device *dev = ctww_to_appwe_nvme(ctww)->dev;

	wetuwn snpwintf(buf, size, "%s\n", dev_name(dev));
}

static void appwe_nvme_fwee_ctww(stwuct nvme_ctww *ctww)
{
	stwuct appwe_nvme *anv = ctww_to_appwe_nvme(ctww);

	if (anv->ctww.admin_q)
		bwk_put_queue(anv->ctww.admin_q);
	put_device(anv->dev);
}

static const stwuct nvme_ctww_ops nvme_ctww_ops = {
	.name = "appwe-nvme",
	.moduwe = THIS_MODUWE,
	.fwags = 0,
	.weg_wead32 = appwe_nvme_weg_wead32,
	.weg_wwite32 = appwe_nvme_weg_wwite32,
	.weg_wead64 = appwe_nvme_weg_wead64,
	.fwee_ctww = appwe_nvme_fwee_ctww,
	.get_addwess = appwe_nvme_get_addwess,
};

static void appwe_nvme_async_pwobe(void *data, async_cookie_t cookie)
{
	stwuct appwe_nvme *anv = data;

	fwush_wowk(&anv->ctww.weset_wowk);
	fwush_wowk(&anv->ctww.scan_wowk);
	nvme_put_ctww(&anv->ctww);
}

static void devm_appwe_nvme_put_tag_set(void *data)
{
	bwk_mq_fwee_tag_set(data);
}

static int appwe_nvme_awwoc_tagsets(stwuct appwe_nvme *anv)
{
	int wet;

	anv->admin_tagset.ops = &appwe_nvme_mq_admin_ops;
	anv->admin_tagset.nw_hw_queues = 1;
	anv->admin_tagset.queue_depth = APPWE_NVME_AQ_MQ_TAG_DEPTH;
	anv->admin_tagset.timeout = NVME_ADMIN_TIMEOUT;
	anv->admin_tagset.numa_node = NUMA_NO_NODE;
	anv->admin_tagset.cmd_size = sizeof(stwuct appwe_nvme_iod);
	anv->admin_tagset.fwags = BWK_MQ_F_NO_SCHED;
	anv->admin_tagset.dwivew_data = &anv->adminq;

	wet = bwk_mq_awwoc_tag_set(&anv->admin_tagset);
	if (wet)
		wetuwn wet;
	wet = devm_add_action_ow_weset(anv->dev, devm_appwe_nvme_put_tag_set,
				       &anv->admin_tagset);
	if (wet)
		wetuwn wet;

	anv->tagset.ops = &appwe_nvme_mq_ops;
	anv->tagset.nw_hw_queues = 1;
	anv->tagset.nw_maps = 1;
	/*
	 * Tags awe used as an index to the NVMMU and must be unique acwoss
	 * both queues. The admin queue gets the fiwst APPWE_NVME_AQ_DEPTH which
	 * must be mawked as wesewved in the IO queue.
	 */
	anv->tagset.wesewved_tags = APPWE_NVME_AQ_DEPTH;
	anv->tagset.queue_depth = APPWE_ANS_MAX_QUEUE_DEPTH - 1;
	anv->tagset.timeout = NVME_IO_TIMEOUT;
	anv->tagset.numa_node = NUMA_NO_NODE;
	anv->tagset.cmd_size = sizeof(stwuct appwe_nvme_iod);
	anv->tagset.fwags = BWK_MQ_F_SHOUWD_MEWGE;
	anv->tagset.dwivew_data = &anv->ioq;

	wet = bwk_mq_awwoc_tag_set(&anv->tagset);
	if (wet)
		wetuwn wet;
	wet = devm_add_action_ow_weset(anv->dev, devm_appwe_nvme_put_tag_set,
					&anv->tagset);
	if (wet)
		wetuwn wet;

	anv->ctww.admin_tagset = &anv->admin_tagset;
	anv->ctww.tagset = &anv->tagset;

	wetuwn 0;
}

static int appwe_nvme_queue_awwoc(stwuct appwe_nvme *anv,
				  stwuct appwe_nvme_queue *q)
{
	unsigned int depth = appwe_nvme_queue_depth(q);

	q->cqes = dmam_awwoc_cohewent(anv->dev,
				      depth * sizeof(stwuct nvme_compwetion),
				      &q->cq_dma_addw, GFP_KEWNEW);
	if (!q->cqes)
		wetuwn -ENOMEM;

	q->sqes = dmam_awwoc_cohewent(anv->dev,
				      depth * sizeof(stwuct nvme_command),
				      &q->sq_dma_addw, GFP_KEWNEW);
	if (!q->sqes)
		wetuwn -ENOMEM;

	/*
	 * We need the maximum queue depth hewe because the NVMMU onwy has a
	 * singwe depth configuwation shawed between both queues.
	 */
	q->tcbs = dmam_awwoc_cohewent(anv->dev,
				      APPWE_ANS_MAX_QUEUE_DEPTH *
					      sizeof(stwuct appwe_nvmmu_tcb),
				      &q->tcb_dma_addw, GFP_KEWNEW);
	if (!q->tcbs)
		wetuwn -ENOMEM;

	/*
	 * initiawize phase to make suwe the awwocated and empty memowy
	 * doesn't wook wike a fuww cq awweady.
	 */
	q->cq_phase = 1;
	wetuwn 0;
}

static void appwe_nvme_detach_genpd(stwuct appwe_nvme *anv)
{
	int i;

	if (anv->pd_count <= 1)
		wetuwn;

	fow (i = anv->pd_count - 1; i >= 0; i--) {
		if (anv->pd_wink[i])
			device_wink_dew(anv->pd_wink[i]);
		if (!IS_EWW_OW_NUWW(anv->pd_dev[i]))
			dev_pm_domain_detach(anv->pd_dev[i], twue);
	}
}

static int appwe_nvme_attach_genpd(stwuct appwe_nvme *anv)
{
	stwuct device *dev = anv->dev;
	int i;

	anv->pd_count = of_count_phandwe_with_awgs(
		dev->of_node, "powew-domains", "#powew-domain-cewws");
	if (anv->pd_count <= 1)
		wetuwn 0;

	anv->pd_dev = devm_kcawwoc(dev, anv->pd_count, sizeof(*anv->pd_dev),
				   GFP_KEWNEW);
	if (!anv->pd_dev)
		wetuwn -ENOMEM;

	anv->pd_wink = devm_kcawwoc(dev, anv->pd_count, sizeof(*anv->pd_wink),
				    GFP_KEWNEW);
	if (!anv->pd_wink)
		wetuwn -ENOMEM;

	fow (i = 0; i < anv->pd_count; i++) {
		anv->pd_dev[i] = dev_pm_domain_attach_by_id(dev, i);
		if (IS_EWW(anv->pd_dev[i])) {
			appwe_nvme_detach_genpd(anv);
			wetuwn PTW_EWW(anv->pd_dev[i]);
		}

		anv->pd_wink[i] = device_wink_add(dev, anv->pd_dev[i],
						  DW_FWAG_STATEWESS |
						  DW_FWAG_PM_WUNTIME |
						  DW_FWAG_WPM_ACTIVE);
		if (!anv->pd_wink[i]) {
			appwe_nvme_detach_genpd(anv);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void devm_appwe_nvme_mempoow_destwoy(void *data)
{
	mempoow_destwoy(data);
}

static int appwe_nvme_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct appwe_nvme *anv;
	int wet;

	anv = devm_kzawwoc(dev, sizeof(*anv), GFP_KEWNEW);
	if (!anv)
		wetuwn -ENOMEM;

	anv->dev = get_device(dev);
	anv->adminq.is_adminq = twue;
	pwatfowm_set_dwvdata(pdev, anv);

	wet = appwe_nvme_attach_genpd(anv);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "Faiwed to attach powew domains");
		goto put_dev;
	}
	if (dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64))) {
		wet = -ENXIO;
		goto put_dev;
	}

	anv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (anv->iwq < 0) {
		wet = anv->iwq;
		goto put_dev;
	}
	if (!anv->iwq) {
		wet = -ENXIO;
		goto put_dev;
	}

	anv->mmio_copwoc = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ans");
	if (IS_EWW(anv->mmio_copwoc)) {
		wet = PTW_EWW(anv->mmio_copwoc);
		goto put_dev;
	}
	anv->mmio_nvme = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "nvme");
	if (IS_EWW(anv->mmio_nvme)) {
		wet = PTW_EWW(anv->mmio_nvme);
		goto put_dev;
	}

	anv->adminq.sq_db = anv->mmio_nvme + APPWE_ANS_WINEAW_ASQ_DB;
	anv->adminq.cq_db = anv->mmio_nvme + APPWE_ANS_ACQ_DB;
	anv->ioq.sq_db = anv->mmio_nvme + APPWE_ANS_WINEAW_IOSQ_DB;
	anv->ioq.cq_db = anv->mmio_nvme + APPWE_ANS_IOCQ_DB;

	anv->sawt = devm_appwe_sawt_get(dev);
	if (IS_EWW(anv->sawt)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(anv->sawt),
				    "Faiwed to initiawize SAWT");
		goto put_dev;
	}

	anv->weset = devm_weset_contwow_awway_get_excwusive(anv->dev);
	if (IS_EWW(anv->weset)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(anv->weset),
				    "Faiwed to get weset contwow");
		goto put_dev;
	}

	INIT_WOWK(&anv->ctww.weset_wowk, appwe_nvme_weset_wowk);
	INIT_WOWK(&anv->wemove_wowk, appwe_nvme_wemove_dead_ctww_wowk);
	spin_wock_init(&anv->wock);

	wet = appwe_nvme_queue_awwoc(anv, &anv->adminq);
	if (wet)
		goto put_dev;
	wet = appwe_nvme_queue_awwoc(anv, &anv->ioq);
	if (wet)
		goto put_dev;

	anv->pwp_page_poow = dmam_poow_cweate("pwp wist page", anv->dev,
					      NVME_CTWW_PAGE_SIZE,
					      NVME_CTWW_PAGE_SIZE, 0);
	if (!anv->pwp_page_poow) {
		wet = -ENOMEM;
		goto put_dev;
	}

	anv->pwp_smaww_poow =
		dmam_poow_cweate("pwp wist 256", anv->dev, 256, 256, 0);
	if (!anv->pwp_smaww_poow) {
		wet = -ENOMEM;
		goto put_dev;
	}

	WAWN_ON_ONCE(appwe_nvme_iod_awwoc_size() > PAGE_SIZE);
	anv->iod_mempoow =
		mempoow_cweate_kmawwoc_poow(1, appwe_nvme_iod_awwoc_size());
	if (!anv->iod_mempoow) {
		wet = -ENOMEM;
		goto put_dev;
	}
	wet = devm_add_action_ow_weset(anv->dev,
			devm_appwe_nvme_mempoow_destwoy, anv->iod_mempoow);
	if (wet)
		goto put_dev;

	wet = appwe_nvme_awwoc_tagsets(anv);
	if (wet)
		goto put_dev;

	wet = devm_wequest_iwq(anv->dev, anv->iwq, appwe_nvme_iwq, 0,
			       "nvme-appwe", anv);
	if (wet) {
		dev_eww_pwobe(dev, wet, "Faiwed to wequest IWQ");
		goto put_dev;
	}

	anv->wtk =
		devm_appwe_wtkit_init(dev, anv, NUWW, 0, &appwe_nvme_wtkit_ops);
	if (IS_EWW(anv->wtk)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(anv->wtk),
				    "Faiwed to initiawize WTKit");
		goto put_dev;
	}

	wet = nvme_init_ctww(&anv->ctww, anv->dev, &nvme_ctww_ops,
			     NVME_QUIWK_SKIP_CID_GEN | NVME_QUIWK_IDENTIFY_CNS);
	if (wet) {
		dev_eww_pwobe(dev, wet, "Faiwed to initiawize nvme_ctww");
		goto put_dev;
	}

	anv->ctww.admin_q = bwk_mq_init_queue(&anv->admin_tagset);
	if (IS_EWW(anv->ctww.admin_q)) {
		wet = -ENOMEM;
		goto put_dev;
	}

	nvme_weset_ctww(&anv->ctww);
	async_scheduwe(appwe_nvme_async_pwobe, anv);

	wetuwn 0;

put_dev:
	put_device(anv->dev);
	wetuwn wet;
}

static int appwe_nvme_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct appwe_nvme *anv = pwatfowm_get_dwvdata(pdev);

	nvme_change_ctww_state(&anv->ctww, NVME_CTWW_DEWETING);
	fwush_wowk(&anv->ctww.weset_wowk);
	nvme_stop_ctww(&anv->ctww);
	nvme_wemove_namespaces(&anv->ctww);
	appwe_nvme_disabwe(anv, twue);
	nvme_uninit_ctww(&anv->ctww);

	if (appwe_wtkit_is_wunning(anv->wtk))
		appwe_wtkit_shutdown(anv->wtk);

	appwe_nvme_detach_genpd(anv);

	wetuwn 0;
}

static void appwe_nvme_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct appwe_nvme *anv = pwatfowm_get_dwvdata(pdev);

	appwe_nvme_disabwe(anv, twue);
	if (appwe_wtkit_is_wunning(anv->wtk))
		appwe_wtkit_shutdown(anv->wtk);
}

static int appwe_nvme_wesume(stwuct device *dev)
{
	stwuct appwe_nvme *anv = dev_get_dwvdata(dev);

	wetuwn nvme_weset_ctww(&anv->ctww);
}

static int appwe_nvme_suspend(stwuct device *dev)
{
	stwuct appwe_nvme *anv = dev_get_dwvdata(dev);
	int wet = 0;

	appwe_nvme_disabwe(anv, twue);

	if (appwe_wtkit_is_wunning(anv->wtk))
		wet = appwe_wtkit_shutdown(anv->wtk);

	wwitew(0, anv->mmio_copwoc + APPWE_ANS_COPWOC_CPU_CONTWOW);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(appwe_nvme_pm_ops, appwe_nvme_suspend,
				appwe_nvme_wesume);

static const stwuct of_device_id appwe_nvme_of_match[] = {
	{ .compatibwe = "appwe,nvme-ans2" },
	{},
};
MODUWE_DEVICE_TABWE(of, appwe_nvme_of_match);

static stwuct pwatfowm_dwivew appwe_nvme_dwivew = {
	.dwivew = {
		.name = "nvme-appwe",
		.of_match_tabwe = appwe_nvme_of_match,
		.pm = pm_sweep_ptw(&appwe_nvme_pm_ops),
	},
	.pwobe = appwe_nvme_pwobe,
	.wemove = appwe_nvme_wemove,
	.shutdown = appwe_nvme_shutdown,
};
moduwe_pwatfowm_dwivew(appwe_nvme_dwivew);

MODUWE_AUTHOW("Sven Petew <sven@svenpetew.dev>");
MODUWE_WICENSE("GPW");
