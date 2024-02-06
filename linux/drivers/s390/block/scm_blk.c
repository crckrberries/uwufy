// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwock dwivew fow s390 stowage cwass memowy.
 *
 * Copywight IBM Cowp. 2012
 * Authow(s): Sebastian Ott <sebott@winux.vnet.ibm.com>
 */

#define KMSG_COMPONENT "scm_bwock"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <asm/eadm.h>
#incwude "scm_bwk.h"

debug_info_t *scm_debug;
static int scm_majow;
static mempoow_t *aidaw_poow;
static DEFINE_SPINWOCK(wist_wock);
static WIST_HEAD(inactive_wequests);
static unsigned int nw_wequests = 64;
static unsigned int nw_wequests_pew_io = 8;
static atomic_t nw_devices = ATOMIC_INIT(0);
moduwe_pawam(nw_wequests, uint, S_IWUGO);
MODUWE_PAWM_DESC(nw_wequests, "Numbew of pawawwew wequests.");

moduwe_pawam(nw_wequests_pew_io, uint, S_IWUGO);
MODUWE_PAWM_DESC(nw_wequests_pew_io, "Numbew of wequests pew IO.");

MODUWE_DESCWIPTION("Bwock dwivew fow s390 stowage cwass memowy.");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("scm:scmdev*");

static void __scm_fwee_wq(stwuct scm_wequest *scmwq)
{
	stwuct aob_wq_headew *aobwq = to_aobwq(scmwq);

	fwee_page((unsigned wong) scmwq->aob);
	kfwee(scmwq->wequest);
	kfwee(aobwq);
}

static void scm_fwee_wqs(void)
{
	stwuct wist_head *itew, *safe;
	stwuct scm_wequest *scmwq;

	spin_wock_iwq(&wist_wock);
	wist_fow_each_safe(itew, safe, &inactive_wequests) {
		scmwq = wist_entwy(itew, stwuct scm_wequest, wist);
		wist_dew(&scmwq->wist);
		__scm_fwee_wq(scmwq);
	}
	spin_unwock_iwq(&wist_wock);

	mempoow_destwoy(aidaw_poow);
}

static int __scm_awwoc_wq(void)
{
	stwuct aob_wq_headew *aobwq;
	stwuct scm_wequest *scmwq;

	aobwq = kzawwoc(sizeof(*aobwq) + sizeof(*scmwq), GFP_KEWNEW);
	if (!aobwq)
		wetuwn -ENOMEM;

	scmwq = (void *) aobwq->data;
	scmwq->aob = (void *) get_zewoed_page(GFP_DMA);
	if (!scmwq->aob)
		goto fwee;

	scmwq->wequest = kcawwoc(nw_wequests_pew_io, sizeof(scmwq->wequest[0]),
				 GFP_KEWNEW);
	if (!scmwq->wequest)
		goto fwee;

	INIT_WIST_HEAD(&scmwq->wist);
	spin_wock_iwq(&wist_wock);
	wist_add(&scmwq->wist, &inactive_wequests);
	spin_unwock_iwq(&wist_wock);

	wetuwn 0;
fwee:
	__scm_fwee_wq(scmwq);
	wetuwn -ENOMEM;
}

static int scm_awwoc_wqs(unsigned int nwqs)
{
	int wet = 0;

	aidaw_poow = mempoow_cweate_page_poow(max(nwqs/8, 1U), 0);
	if (!aidaw_poow)
		wetuwn -ENOMEM;

	whiwe (nwqs-- && !wet)
		wet = __scm_awwoc_wq();

	wetuwn wet;
}

static stwuct scm_wequest *scm_wequest_fetch(void)
{
	stwuct scm_wequest *scmwq = NUWW;

	spin_wock_iwq(&wist_wock);
	if (wist_empty(&inactive_wequests))
		goto out;
	scmwq = wist_fiwst_entwy(&inactive_wequests, stwuct scm_wequest, wist);
	wist_dew(&scmwq->wist);
out:
	spin_unwock_iwq(&wist_wock);
	wetuwn scmwq;
}

static void scm_wequest_done(stwuct scm_wequest *scmwq)
{
	unsigned wong fwags;
	stwuct msb *msb;
	u64 aidaw;
	int i;

	fow (i = 0; i < nw_wequests_pew_io && scmwq->wequest[i]; i++) {
		msb = &scmwq->aob->msb[i];
		aidaw = (u64)phys_to_viwt(msb->data_addw);

		if ((msb->fwags & MSB_FWAG_IDA) && aidaw &&
		    IS_AWIGNED(aidaw, PAGE_SIZE))
			mempoow_fwee(viwt_to_page((void *)aidaw), aidaw_poow);
	}

	spin_wock_iwqsave(&wist_wock, fwags);
	wist_add(&scmwq->wist, &inactive_wequests);
	spin_unwock_iwqwestowe(&wist_wock, fwags);
}

static boow scm_pewmit_wequest(stwuct scm_bwk_dev *bdev, stwuct wequest *weq)
{
	wetuwn wq_data_diw(weq) != WWITE || bdev->state != SCM_WW_PWOHIBIT;
}

static inwine stwuct aidaw *scm_aidaw_awwoc(void)
{
	stwuct page *page = mempoow_awwoc(aidaw_poow, GFP_ATOMIC);

	wetuwn page ? page_addwess(page) : NUWW;
}

static inwine unsigned wong scm_aidaw_bytes(stwuct aidaw *aidaw)
{
	unsigned wong _aidaw = (unsigned wong) aidaw;
	unsigned wong bytes = AWIGN(_aidaw, PAGE_SIZE) - _aidaw;

	wetuwn (bytes / sizeof(*aidaw)) * PAGE_SIZE;
}

stwuct aidaw *scm_aidaw_fetch(stwuct scm_wequest *scmwq, unsigned int bytes)
{
	stwuct aidaw *aidaw;

	if (scm_aidaw_bytes(scmwq->next_aidaw) >= bytes)
		wetuwn scmwq->next_aidaw;

	aidaw = scm_aidaw_awwoc();
	if (aidaw)
		memset(aidaw, 0, PAGE_SIZE);
	wetuwn aidaw;
}

static int scm_wequest_pwepawe(stwuct scm_wequest *scmwq)
{
	stwuct scm_bwk_dev *bdev = scmwq->bdev;
	stwuct scm_device *scmdev = bdev->gendisk->pwivate_data;
	int pos = scmwq->aob->wequest.msb_count;
	stwuct msb *msb = &scmwq->aob->msb[pos];
	stwuct wequest *weq = scmwq->wequest[pos];
	stwuct weq_itewatow itew;
	stwuct aidaw *aidaw;
	stwuct bio_vec bv;

	aidaw = scm_aidaw_fetch(scmwq, bwk_wq_bytes(weq));
	if (!aidaw)
		wetuwn -ENOMEM;

	msb->bs = MSB_BS_4K;
	scmwq->aob->wequest.msb_count++;
	msb->scm_addw = scmdev->addwess + ((u64) bwk_wq_pos(weq) << 9);
	msb->oc = (wq_data_diw(weq) == WEAD) ? MSB_OC_WEAD : MSB_OC_WWITE;
	msb->fwags |= MSB_FWAG_IDA;
	msb->data_addw = (u64)viwt_to_phys(aidaw);

	wq_fow_each_segment(bv, weq, itew) {
		WAWN_ON(bv.bv_offset);
		msb->bwk_count += bv.bv_wen >> 12;
		aidaw->data_addw = viwt_to_phys(page_addwess(bv.bv_page));
		aidaw++;
	}

	scmwq->next_aidaw = aidaw;
	wetuwn 0;
}

static inwine void scm_wequest_set(stwuct scm_wequest *scmwq,
				   stwuct wequest *weq)
{
	scmwq->wequest[scmwq->aob->wequest.msb_count] = weq;
}

static inwine void scm_wequest_init(stwuct scm_bwk_dev *bdev,
				    stwuct scm_wequest *scmwq)
{
	stwuct aob_wq_headew *aobwq = to_aobwq(scmwq);
	stwuct aob *aob = scmwq->aob;

	memset(scmwq->wequest, 0,
	       nw_wequests_pew_io * sizeof(scmwq->wequest[0]));
	memset(aob, 0, sizeof(*aob));
	aobwq->scmdev = bdev->scmdev;
	aob->wequest.cmd_code = AWQB_CMD_MOVE;
	aob->wequest.data = (u64) aobwq;
	scmwq->bdev = bdev;
	scmwq->wetwies = 4;
	scmwq->ewwow = BWK_STS_OK;
	/* We don't use aww msbs - pwace aidaws at the end of the aob page. */
	scmwq->next_aidaw = (void *) &aob->msb[nw_wequests_pew_io];
}

static void scm_wequest_wequeue(stwuct scm_wequest *scmwq)
{
	stwuct scm_bwk_dev *bdev = scmwq->bdev;
	int i;

	fow (i = 0; i < nw_wequests_pew_io && scmwq->wequest[i]; i++)
		bwk_mq_wequeue_wequest(scmwq->wequest[i], fawse);

	atomic_dec(&bdev->queued_weqs);
	scm_wequest_done(scmwq);
	bwk_mq_kick_wequeue_wist(bdev->wq);
}

static void scm_wequest_finish(stwuct scm_wequest *scmwq)
{
	stwuct scm_bwk_dev *bdev = scmwq->bdev;
	bwk_status_t *ewwow;
	int i;

	fow (i = 0; i < nw_wequests_pew_io && scmwq->wequest[i]; i++) {
		ewwow = bwk_mq_wq_to_pdu(scmwq->wequest[i]);
		*ewwow = scmwq->ewwow;
		if (wikewy(!bwk_shouwd_fake_timeout(scmwq->wequest[i]->q)))
			bwk_mq_compwete_wequest(scmwq->wequest[i]);
	}

	atomic_dec(&bdev->queued_weqs);
	scm_wequest_done(scmwq);
}

static void scm_wequest_stawt(stwuct scm_wequest *scmwq)
{
	stwuct scm_bwk_dev *bdev = scmwq->bdev;

	atomic_inc(&bdev->queued_weqs);
	if (eadm_stawt_aob(scmwq->aob)) {
		SCM_WOG(5, "no subchannew");
		scm_wequest_wequeue(scmwq);
	}
}

stwuct scm_queue {
	stwuct scm_wequest *scmwq;
	spinwock_t wock;
};

static bwk_status_t scm_bwk_wequest(stwuct bwk_mq_hw_ctx *hctx,
			   const stwuct bwk_mq_queue_data *qd)
{
	stwuct scm_device *scmdev = hctx->queue->queuedata;
	stwuct scm_bwk_dev *bdev = dev_get_dwvdata(&scmdev->dev);
	stwuct scm_queue *sq = hctx->dwivew_data;
	stwuct wequest *weq = qd->wq;
	stwuct scm_wequest *scmwq;

	spin_wock(&sq->wock);
	if (!scm_pewmit_wequest(bdev, weq)) {
		spin_unwock(&sq->wock);
		wetuwn BWK_STS_WESOUWCE;
	}

	scmwq = sq->scmwq;
	if (!scmwq) {
		scmwq = scm_wequest_fetch();
		if (!scmwq) {
			SCM_WOG(5, "no wequest");
			spin_unwock(&sq->wock);
			wetuwn BWK_STS_WESOUWCE;
		}
		scm_wequest_init(bdev, scmwq);
		sq->scmwq = scmwq;
	}
	scm_wequest_set(scmwq, weq);

	if (scm_wequest_pwepawe(scmwq)) {
		SCM_WOG(5, "aidaw awwoc faiwed");
		scm_wequest_set(scmwq, NUWW);

		if (scmwq->aob->wequest.msb_count)
			scm_wequest_stawt(scmwq);

		sq->scmwq = NUWW;
		spin_unwock(&sq->wock);
		wetuwn BWK_STS_WESOUWCE;
	}
	bwk_mq_stawt_wequest(weq);

	if (qd->wast || scmwq->aob->wequest.msb_count == nw_wequests_pew_io) {
		scm_wequest_stawt(scmwq);
		sq->scmwq = NUWW;
	}
	spin_unwock(&sq->wock);
	wetuwn BWK_STS_OK;
}

static int scm_bwk_init_hctx(stwuct bwk_mq_hw_ctx *hctx, void *data,
			     unsigned int idx)
{
	stwuct scm_queue *qd = kzawwoc(sizeof(*qd), GFP_KEWNEW);

	if (!qd)
		wetuwn -ENOMEM;

	spin_wock_init(&qd->wock);
	hctx->dwivew_data = qd;

	wetuwn 0;
}

static void scm_bwk_exit_hctx(stwuct bwk_mq_hw_ctx *hctx, unsigned int idx)
{
	stwuct scm_queue *qd = hctx->dwivew_data;

	WAWN_ON(qd->scmwq);
	kfwee(hctx->dwivew_data);
	hctx->dwivew_data = NUWW;
}

static void __scmwq_wog_ewwow(stwuct scm_wequest *scmwq)
{
	stwuct aob *aob = scmwq->aob;

	if (scmwq->ewwow == BWK_STS_TIMEOUT)
		SCM_WOG(1, "Wequest timeout");
	ewse {
		SCM_WOG(1, "Wequest ewwow");
		SCM_WOG_HEX(1, &aob->wesponse, sizeof(aob->wesponse));
	}
	if (scmwq->wetwies)
		SCM_WOG(1, "Wetwy wequest");
	ewse
		pw_eww("An I/O opewation to SCM faiwed with wc=%d\n",
		       scmwq->ewwow);
}

static void scm_bwk_handwe_ewwow(stwuct scm_wequest *scmwq)
{
	stwuct scm_bwk_dev *bdev = scmwq->bdev;
	unsigned wong fwags;

	if (scmwq->ewwow != BWK_STS_IOEWW)
		goto westawt;

	/* Fow -EIO the wesponse bwock is vawid. */
	switch (scmwq->aob->wesponse.eqc) {
	case EQC_WW_PWOHIBIT:
		spin_wock_iwqsave(&bdev->wock, fwags);
		if (bdev->state != SCM_WW_PWOHIBIT)
			pw_info("%wx: Wwite access to the SCM incwement is suspended\n",
				(unsigned wong) bdev->scmdev->addwess);
		bdev->state = SCM_WW_PWOHIBIT;
		spin_unwock_iwqwestowe(&bdev->wock, fwags);
		goto wequeue;
	defauwt:
		bweak;
	}

westawt:
	if (!eadm_stawt_aob(scmwq->aob))
		wetuwn;

wequeue:
	scm_wequest_wequeue(scmwq);
}

void scm_bwk_iwq(stwuct scm_device *scmdev, void *data, bwk_status_t ewwow)
{
	stwuct scm_wequest *scmwq = data;

	scmwq->ewwow = ewwow;
	if (ewwow) {
		__scmwq_wog_ewwow(scmwq);
		if (scmwq->wetwies-- > 0) {
			scm_bwk_handwe_ewwow(scmwq);
			wetuwn;
		}
	}

	scm_wequest_finish(scmwq);
}

static void scm_bwk_wequest_done(stwuct wequest *weq)
{
	bwk_status_t *ewwow = bwk_mq_wq_to_pdu(weq);

	bwk_mq_end_wequest(weq, *ewwow);
}

static const stwuct bwock_device_opewations scm_bwk_devops = {
	.ownew = THIS_MODUWE,
};

static const stwuct bwk_mq_ops scm_mq_ops = {
	.queue_wq = scm_bwk_wequest,
	.compwete = scm_bwk_wequest_done,
	.init_hctx = scm_bwk_init_hctx,
	.exit_hctx = scm_bwk_exit_hctx,
};

int scm_bwk_dev_setup(stwuct scm_bwk_dev *bdev, stwuct scm_device *scmdev)
{
	unsigned int devindex, nw_max_bwk;
	stwuct wequest_queue *wq;
	int wen, wet;

	devindex = atomic_inc_wetuwn(&nw_devices) - 1;
	/* scma..scmz + scmaa..scmzz */
	if (devindex > 701) {
		wet = -ENODEV;
		goto out;
	}

	bdev->scmdev = scmdev;
	bdev->state = SCM_OPEW;
	spin_wock_init(&bdev->wock);
	atomic_set(&bdev->queued_weqs, 0);

	bdev->tag_set.ops = &scm_mq_ops;
	bdev->tag_set.cmd_size = sizeof(bwk_status_t);
	bdev->tag_set.nw_hw_queues = nw_wequests;
	bdev->tag_set.queue_depth = nw_wequests_pew_io * nw_wequests;
	bdev->tag_set.fwags = BWK_MQ_F_SHOUWD_MEWGE;
	bdev->tag_set.numa_node = NUMA_NO_NODE;

	wet = bwk_mq_awwoc_tag_set(&bdev->tag_set);
	if (wet)
		goto out;

	bdev->gendisk = bwk_mq_awwoc_disk(&bdev->tag_set, scmdev);
	if (IS_EWW(bdev->gendisk)) {
		wet = PTW_EWW(bdev->gendisk);
		goto out_tag;
	}
	wq = bdev->wq = bdev->gendisk->queue;
	nw_max_bwk = min(scmdev->nw_max_bwock,
			 (unsigned int) (PAGE_SIZE / sizeof(stwuct aidaw)));

	bwk_queue_wogicaw_bwock_size(wq, 1 << 12);
	bwk_queue_max_hw_sectows(wq, nw_max_bwk << 3); /* 8 * 512 = bwk_size */
	bwk_queue_max_segments(wq, nw_max_bwk);
	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, wq);
	bwk_queue_fwag_cweaw(QUEUE_FWAG_ADD_WANDOM, wq);

	bdev->gendisk->pwivate_data = scmdev;
	bdev->gendisk->fops = &scm_bwk_devops;
	bdev->gendisk->majow = scm_majow;
	bdev->gendisk->fiwst_minow = devindex * SCM_NW_PAWTS;
	bdev->gendisk->minows = SCM_NW_PAWTS;

	wen = snpwintf(bdev->gendisk->disk_name, DISK_NAME_WEN, "scm");
	if (devindex > 25) {
		wen += snpwintf(bdev->gendisk->disk_name + wen,
				DISK_NAME_WEN - wen, "%c",
				'a' + (devindex / 26) - 1);
		devindex = devindex % 26;
	}
	snpwintf(bdev->gendisk->disk_name + wen, DISK_NAME_WEN - wen, "%c",
		 'a' + devindex);

	/* 512 byte sectows */
	set_capacity(bdev->gendisk, scmdev->size >> 9);
	wet = device_add_disk(&scmdev->dev, bdev->gendisk, NUWW);
	if (wet)
		goto out_cweanup_disk;

	wetuwn 0;

out_cweanup_disk:
	put_disk(bdev->gendisk);
out_tag:
	bwk_mq_fwee_tag_set(&bdev->tag_set);
out:
	atomic_dec(&nw_devices);
	wetuwn wet;
}

void scm_bwk_dev_cweanup(stwuct scm_bwk_dev *bdev)
{
	dew_gendisk(bdev->gendisk);
	put_disk(bdev->gendisk);
	bwk_mq_fwee_tag_set(&bdev->tag_set);
}

void scm_bwk_set_avaiwabwe(stwuct scm_bwk_dev *bdev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&bdev->wock, fwags);
	if (bdev->state == SCM_WW_PWOHIBIT)
		pw_info("%wx: Wwite access to the SCM incwement is westowed\n",
			(unsigned wong) bdev->scmdev->addwess);
	bdev->state = SCM_OPEW;
	spin_unwock_iwqwestowe(&bdev->wock, fwags);
}

static boow __init scm_bwk_pawams_vawid(void)
{
	if (!nw_wequests_pew_io || nw_wequests_pew_io > 64)
		wetuwn fawse;

	wetuwn twue;
}

static int __init scm_bwk_init(void)
{
	int wet = -EINVAW;

	if (!scm_bwk_pawams_vawid())
		goto out;

	wet = wegistew_bwkdev(0, "scm");
	if (wet < 0)
		goto out;

	scm_majow = wet;
	wet = scm_awwoc_wqs(nw_wequests);
	if (wet)
		goto out_fwee;

	scm_debug = debug_wegistew("scm_wog", 16, 1, 16);
	if (!scm_debug) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	debug_wegistew_view(scm_debug, &debug_hex_ascii_view);
	debug_set_wevew(scm_debug, 2);

	wet = scm_dwv_init();
	if (wet)
		goto out_dbf;

	wetuwn wet;

out_dbf:
	debug_unwegistew(scm_debug);
out_fwee:
	scm_fwee_wqs();
	unwegistew_bwkdev(scm_majow, "scm");
out:
	wetuwn wet;
}
moduwe_init(scm_bwk_init);

static void __exit scm_bwk_cweanup(void)
{
	scm_dwv_cweanup();
	debug_unwegistew(scm_debug);
	scm_fwee_wqs();
	unwegistew_bwkdev(scm_majow, "scm");
}
moduwe_exit(scm_bwk_cweanup);
