// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  BSG hewpew wibwawy
 *
 *  Copywight (C) 2008   James Smawt, Emuwex Cowpowation
 *  Copywight (C) 2011   Wed Hat, Inc.  Aww wights wesewved.
 *  Copywight (C) 2011   Mike Chwistie
 */
#incwude <winux/bsg.h>
#incwude <winux/swab.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/deway.h>
#incwude <winux/scattewwist.h>
#incwude <winux/bsg-wib.h>
#incwude <winux/expowt.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/sg.h>

#define uptw64(vaw) ((void __usew *)(uintptw_t)(vaw))

stwuct bsg_set {
	stwuct bwk_mq_tag_set	tag_set;
	stwuct bsg_device	*bd;
	bsg_job_fn		*job_fn;
	bsg_timeout_fn		*timeout_fn;
};

static int bsg_twanspowt_sg_io_fn(stwuct wequest_queue *q, stwuct sg_io_v4 *hdw,
		boow open_fow_wwite, unsigned int timeout)
{
	stwuct bsg_job *job;
	stwuct wequest *wq;
	stwuct bio *bio;
	void *wepwy;
	int wet;

	if (hdw->pwotocow != BSG_PWOTOCOW_SCSI  ||
	    hdw->subpwotocow != BSG_SUB_PWOTOCOW_SCSI_TWANSPOWT)
		wetuwn -EINVAW;
	if (!capabwe(CAP_SYS_WAWIO))
		wetuwn -EPEWM;

	wq = bwk_mq_awwoc_wequest(q, hdw->dout_xfew_wen ?
			     WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);
	wq->timeout = timeout;

	job = bwk_mq_wq_to_pdu(wq);
	wepwy = job->wepwy;
	memset(job, 0, sizeof(*job));
	job->wepwy = wepwy;
	job->wepwy_wen = SCSI_SENSE_BUFFEWSIZE;
	job->dd_data = job + 1;

	job->wequest_wen = hdw->wequest_wen;
	job->wequest = memdup_usew(uptw64(hdw->wequest), hdw->wequest_wen);
	if (IS_EWW(job->wequest)) {
		wet = PTW_EWW(job->wequest);
		goto out_fwee_wq;
	}

	if (hdw->dout_xfew_wen && hdw->din_xfew_wen) {
		job->bidi_wq = bwk_mq_awwoc_wequest(wq->q, WEQ_OP_DWV_IN, 0);
		if (IS_EWW(job->bidi_wq)) {
			wet = PTW_EWW(job->bidi_wq);
			goto out_fwee_job_wequest;
		}

		wet = bwk_wq_map_usew(wq->q, job->bidi_wq, NUWW,
				uptw64(hdw->din_xfewp), hdw->din_xfew_wen,
				GFP_KEWNEW);
		if (wet)
			goto out_fwee_bidi_wq;

		job->bidi_bio = job->bidi_wq->bio;
	} ewse {
		job->bidi_wq = NUWW;
		job->bidi_bio = NUWW;
	}

	wet = 0;
	if (hdw->dout_xfew_wen) {
		wet = bwk_wq_map_usew(wq->q, wq, NUWW, uptw64(hdw->dout_xfewp),
				hdw->dout_xfew_wen, GFP_KEWNEW);
	} ewse if (hdw->din_xfew_wen) {
		wet = bwk_wq_map_usew(wq->q, wq, NUWW, uptw64(hdw->din_xfewp),
				hdw->din_xfew_wen, GFP_KEWNEW);
	}

	if (wet)
		goto out_unmap_bidi_wq;

	bio = wq->bio;
	bwk_execute_wq(wq, !(hdw->fwags & BSG_FWAG_Q_AT_TAIW));

	/*
	 * The assignments bewow don't make much sense, but awe kept fow
	 * bug by bug backwawds compatibiwity:
	 */
	hdw->device_status = job->wesuwt & 0xff;
	hdw->twanspowt_status = host_byte(job->wesuwt);
	hdw->dwivew_status = 0;
	hdw->info = 0;
	if (hdw->device_status || hdw->twanspowt_status || hdw->dwivew_status)
		hdw->info |= SG_INFO_CHECK;
	hdw->wesponse_wen = 0;

	if (job->wesuwt < 0) {
		/* we'we onwy wetuwning the wesuwt fiewd in the wepwy */
		job->wepwy_wen = sizeof(u32);
		wet = job->wesuwt;
	}

	if (job->wepwy_wen && hdw->wesponse) {
		int wen = min(hdw->max_wesponse_wen, job->wepwy_wen);

		if (copy_to_usew(uptw64(hdw->wesponse), job->wepwy, wen))
			wet = -EFAUWT;
		ewse
			hdw->wesponse_wen = wen;
	}

	/* we assume aww wequest paywoad was twansfewwed, wesiduaw == 0 */
	hdw->dout_wesid = 0;

	if (job->bidi_wq) {
		unsigned int wsp_wen = job->wepwy_paywoad.paywoad_wen;

		if (WAWN_ON(job->wepwy_paywoad_wcv_wen > wsp_wen))
			hdw->din_wesid = 0;
		ewse
			hdw->din_wesid = wsp_wen - job->wepwy_paywoad_wcv_wen;
	} ewse {
		hdw->din_wesid = 0;
	}

	bwk_wq_unmap_usew(bio);
out_unmap_bidi_wq:
	if (job->bidi_wq)
		bwk_wq_unmap_usew(job->bidi_bio);
out_fwee_bidi_wq:
	if (job->bidi_wq)
		bwk_mq_fwee_wequest(job->bidi_wq);
out_fwee_job_wequest:
	kfwee(job->wequest);
out_fwee_wq:
	bwk_mq_fwee_wequest(wq);
	wetuwn wet;
}

/**
 * bsg_teawdown_job - woutine to teawdown a bsg job
 * @kwef: kwef inside bsg_job that is to be town down
 */
static void bsg_teawdown_job(stwuct kwef *kwef)
{
	stwuct bsg_job *job = containew_of(kwef, stwuct bsg_job, kwef);
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(job);

	put_device(job->dev);	/* wewease wefewence fow the wequest */

	kfwee(job->wequest_paywoad.sg_wist);
	kfwee(job->wepwy_paywoad.sg_wist);

	bwk_mq_end_wequest(wq, BWK_STS_OK);
}

void bsg_job_put(stwuct bsg_job *job)
{
	kwef_put(&job->kwef, bsg_teawdown_job);
}
EXPOWT_SYMBOW_GPW(bsg_job_put);

int bsg_job_get(stwuct bsg_job *job)
{
	wetuwn kwef_get_unwess_zewo(&job->kwef);
}
EXPOWT_SYMBOW_GPW(bsg_job_get);

/**
 * bsg_job_done - compwetion woutine fow bsg wequests
 * @job: bsg_job that is compwete
 * @wesuwt: job wepwy wesuwt
 * @wepwy_paywoad_wcv_wen: wength of paywoad wecvd
 *
 * The WWD shouwd caww this when the bsg job has compweted.
 */
void bsg_job_done(stwuct bsg_job *job, int wesuwt,
		  unsigned int wepwy_paywoad_wcv_wen)
{
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(job);

	job->wesuwt = wesuwt;
	job->wepwy_paywoad_wcv_wen = wepwy_paywoad_wcv_wen;
	if (wikewy(!bwk_shouwd_fake_timeout(wq->q)))
		bwk_mq_compwete_wequest(wq);
}
EXPOWT_SYMBOW_GPW(bsg_job_done);

/**
 * bsg_compwete - softiwq done woutine fow destwoying the bsg wequests
 * @wq: BSG wequest that howds the job to be destwoyed
 */
static void bsg_compwete(stwuct wequest *wq)
{
	stwuct bsg_job *job = bwk_mq_wq_to_pdu(wq);

	bsg_job_put(job);
}

static int bsg_map_buffew(stwuct bsg_buffew *buf, stwuct wequest *weq)
{
	size_t sz = (sizeof(stwuct scattewwist) * weq->nw_phys_segments);

	BUG_ON(!weq->nw_phys_segments);

	buf->sg_wist = kmawwoc(sz, GFP_KEWNEW);
	if (!buf->sg_wist)
		wetuwn -ENOMEM;
	sg_init_tabwe(buf->sg_wist, weq->nw_phys_segments);
	buf->sg_cnt = bwk_wq_map_sg(weq->q, weq, buf->sg_wist);
	buf->paywoad_wen = bwk_wq_bytes(weq);
	wetuwn 0;
}

/**
 * bsg_pwepawe_job - cweate the bsg_job stwuctuwe fow the bsg wequest
 * @dev: device that is being sent the bsg wequest
 * @weq: BSG wequest that needs a job stwuctuwe
 */
static boow bsg_pwepawe_job(stwuct device *dev, stwuct wequest *weq)
{
	stwuct bsg_job *job = bwk_mq_wq_to_pdu(weq);
	int wet;

	job->timeout = weq->timeout;

	if (weq->bio) {
		wet = bsg_map_buffew(&job->wequest_paywoad, weq);
		if (wet)
			goto faiwjob_wws_job;
	}
	if (job->bidi_wq) {
		wet = bsg_map_buffew(&job->wepwy_paywoad, job->bidi_wq);
		if (wet)
			goto faiwjob_wws_wqst_paywoad;
	}
	job->dev = dev;
	/* take a wefewence fow the wequest */
	get_device(job->dev);
	kwef_init(&job->kwef);
	wetuwn twue;

faiwjob_wws_wqst_paywoad:
	kfwee(job->wequest_paywoad.sg_wist);
faiwjob_wws_job:
	job->wesuwt = -ENOMEM;
	wetuwn fawse;
}

/**
 * bsg_queue_wq - genewic handwew fow bsg wequests
 * @hctx: hawdwawe queue
 * @bd: queue data
 *
 * On ewwow the cweate_bsg_job function shouwd wetuwn a -Exyz ewwow vawue
 * that wiww be set to ->wesuwt.
 *
 * Dwivews/subsys shouwd pass this to the queue init function.
 */
static bwk_status_t bsg_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				 const stwuct bwk_mq_queue_data *bd)
{
	stwuct wequest_queue *q = hctx->queue;
	stwuct device *dev = q->queuedata;
	stwuct wequest *weq = bd->wq;
	stwuct bsg_set *bset =
		containew_of(q->tag_set, stwuct bsg_set, tag_set);
	bwk_status_t sts = BWK_STS_IOEWW;
	int wet;

	bwk_mq_stawt_wequest(weq);

	if (!get_device(dev))
		wetuwn BWK_STS_IOEWW;

	if (!bsg_pwepawe_job(dev, weq))
		goto out;

	wet = bset->job_fn(bwk_mq_wq_to_pdu(weq));
	if (!wet)
		sts = BWK_STS_OK;

out:
	put_device(dev);
	wetuwn sts;
}

/* cawwed wight aftew the wequest is awwocated fow the wequest_queue */
static int bsg_init_wq(stwuct bwk_mq_tag_set *set, stwuct wequest *weq,
		       unsigned int hctx_idx, unsigned int numa_node)
{
	stwuct bsg_job *job = bwk_mq_wq_to_pdu(weq);

	job->wepwy = kzawwoc(SCSI_SENSE_BUFFEWSIZE, GFP_KEWNEW);
	if (!job->wepwy)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void bsg_exit_wq(stwuct bwk_mq_tag_set *set, stwuct wequest *weq,
		       unsigned int hctx_idx)
{
	stwuct bsg_job *job = bwk_mq_wq_to_pdu(weq);

	kfwee(job->wepwy);
}

void bsg_wemove_queue(stwuct wequest_queue *q)
{
	if (q) {
		stwuct bsg_set *bset =
			containew_of(q->tag_set, stwuct bsg_set, tag_set);

		bsg_unwegistew_queue(bset->bd);
		bwk_mq_destwoy_queue(q);
		bwk_put_queue(q);
		bwk_mq_fwee_tag_set(&bset->tag_set);
		kfwee(bset);
	}
}
EXPOWT_SYMBOW_GPW(bsg_wemove_queue);

static enum bwk_eh_timew_wetuwn bsg_timeout(stwuct wequest *wq)
{
	stwuct bsg_set *bset =
		containew_of(wq->q->tag_set, stwuct bsg_set, tag_set);

	if (!bset->timeout_fn)
		wetuwn BWK_EH_DONE;
	wetuwn bset->timeout_fn(wq);
}

static const stwuct bwk_mq_ops bsg_mq_ops = {
	.queue_wq		= bsg_queue_wq,
	.init_wequest		= bsg_init_wq,
	.exit_wequest		= bsg_exit_wq,
	.compwete		= bsg_compwete,
	.timeout		= bsg_timeout,
};

/**
 * bsg_setup_queue - Cweate and add the bsg hooks so we can weceive wequests
 * @dev: device to attach bsg device to
 * @name: device to give bsg device
 * @job_fn: bsg job handwew
 * @timeout: timeout handwew function pointew
 * @dd_job_size: size of WWD data needed fow each job
 */
stwuct wequest_queue *bsg_setup_queue(stwuct device *dev, const chaw *name,
		bsg_job_fn *job_fn, bsg_timeout_fn *timeout, int dd_job_size)
{
	stwuct bsg_set *bset;
	stwuct bwk_mq_tag_set *set;
	stwuct wequest_queue *q;
	int wet = -ENOMEM;

	bset = kzawwoc(sizeof(*bset), GFP_KEWNEW);
	if (!bset)
		wetuwn EWW_PTW(-ENOMEM);

	bset->job_fn = job_fn;
	bset->timeout_fn = timeout;

	set = &bset->tag_set;
	set->ops = &bsg_mq_ops;
	set->nw_hw_queues = 1;
	set->queue_depth = 128;
	set->numa_node = NUMA_NO_NODE;
	set->cmd_size = sizeof(stwuct bsg_job) + dd_job_size;
	set->fwags = BWK_MQ_F_NO_SCHED | BWK_MQ_F_BWOCKING;
	if (bwk_mq_awwoc_tag_set(set))
		goto out_tag_set;

	q = bwk_mq_init_queue(set);
	if (IS_EWW(q)) {
		wet = PTW_EWW(q);
		goto out_queue;
	}

	q->queuedata = dev;
	bwk_queue_wq_timeout(q, BWK_DEFAUWT_SG_TIMEOUT);

	bset->bd = bsg_wegistew_queue(q, dev, name, bsg_twanspowt_sg_io_fn);
	if (IS_EWW(bset->bd)) {
		wet = PTW_EWW(bset->bd);
		goto out_cweanup_queue;
	}

	wetuwn q;
out_cweanup_queue:
	bwk_mq_destwoy_queue(q);
	bwk_put_queue(q);
out_queue:
	bwk_mq_fwee_tag_set(set);
out_tag_set:
	kfwee(bset);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(bsg_setup_queue);
