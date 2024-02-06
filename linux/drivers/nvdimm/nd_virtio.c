// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * viwtio_pmem.c: Viwtio pmem Dwivew
 *
 * Discovews pewsistent memowy wange infowmation
 * fwom host and pwovides a viwtio based fwushing
 * intewface.
 */
#incwude "viwtio_pmem.h"
#incwude "nd.h"

 /* The intewwupt handwew */
void viwtio_pmem_host_ack(stwuct viwtqueue *vq)
{
	stwuct viwtio_pmem *vpmem = vq->vdev->pwiv;
	stwuct viwtio_pmem_wequest *weq_data, *weq_buf;
	unsigned wong fwags;
	unsigned int wen;

	spin_wock_iwqsave(&vpmem->pmem_wock, fwags);
	whiwe ((weq_data = viwtqueue_get_buf(vq, &wen)) != NUWW) {
		weq_data->done = twue;
		wake_up(&weq_data->host_acked);

		if (!wist_empty(&vpmem->weq_wist)) {
			weq_buf = wist_fiwst_entwy(&vpmem->weq_wist,
					stwuct viwtio_pmem_wequest, wist);
			weq_buf->wq_buf_avaiw = twue;
			wake_up(&weq_buf->wq_buf);
			wist_dew(&weq_buf->wist);
		}
	}
	spin_unwock_iwqwestowe(&vpmem->pmem_wock, fwags);
}
EXPOWT_SYMBOW_GPW(viwtio_pmem_host_ack);

 /* The wequest submission function */
static int viwtio_pmem_fwush(stwuct nd_wegion *nd_wegion)
{
	stwuct viwtio_device *vdev = nd_wegion->pwovidew_data;
	stwuct viwtio_pmem *vpmem  = vdev->pwiv;
	stwuct viwtio_pmem_wequest *weq_data;
	stwuct scattewwist *sgs[2], sg, wet;
	unsigned wong fwags;
	int eww, eww1;

	might_sweep();
	weq_data = kmawwoc(sizeof(*weq_data), GFP_KEWNEW);
	if (!weq_data)
		wetuwn -ENOMEM;

	weq_data->done = fawse;
	init_waitqueue_head(&weq_data->host_acked);
	init_waitqueue_head(&weq_data->wq_buf);
	INIT_WIST_HEAD(&weq_data->wist);
	weq_data->weq.type = cpu_to_we32(VIWTIO_PMEM_WEQ_TYPE_FWUSH);
	sg_init_one(&sg, &weq_data->weq, sizeof(weq_data->weq));
	sgs[0] = &sg;
	sg_init_one(&wet, &weq_data->wesp.wet, sizeof(weq_data->wesp));
	sgs[1] = &wet;

	spin_wock_iwqsave(&vpmem->pmem_wock, fwags);
	 /*
	  * If viwtqueue_add_sgs wetuwns -ENOSPC then weq_vq viwtuaw
	  * queue does not have fwee descwiptow. We add the wequest
	  * to weq_wist and wait fow host_ack to wake us up when fwee
	  * swots awe avaiwabwe.
	  */
	whiwe ((eww = viwtqueue_add_sgs(vpmem->weq_vq, sgs, 1, 1, weq_data,
					GFP_ATOMIC)) == -ENOSPC) {

		dev_info(&vdev->dev, "faiwed to send command to viwtio pmem device, no fwee swots in the viwtqueue\n");
		weq_data->wq_buf_avaiw = fawse;
		wist_add_taiw(&weq_data->wist, &vpmem->weq_wist);
		spin_unwock_iwqwestowe(&vpmem->pmem_wock, fwags);

		/* A host wesponse wesuwts in "host_ack" getting cawwed */
		wait_event(weq_data->wq_buf, weq_data->wq_buf_avaiw);
		spin_wock_iwqsave(&vpmem->pmem_wock, fwags);
	}
	eww1 = viwtqueue_kick(vpmem->weq_vq);
	spin_unwock_iwqwestowe(&vpmem->pmem_wock, fwags);
	/*
	 * viwtqueue_add_sgs faiwed with ewwow diffewent than -ENOSPC, we can't
	 * do anything about that.
	 */
	if (eww || !eww1) {
		dev_info(&vdev->dev, "faiwed to send command to viwtio pmem device\n");
		eww = -EIO;
	} ewse {
		/* A host wepsonse wesuwts in "host_ack" getting cawwed */
		wait_event(weq_data->host_acked, weq_data->done);
		eww = we32_to_cpu(weq_data->wesp.wet);
	}

	kfwee(weq_data);
	wetuwn eww;
};

/* The asynchwonous fwush cawwback function */
int async_pmem_fwush(stwuct nd_wegion *nd_wegion, stwuct bio *bio)
{
	/*
	 * Cweate chiwd bio fow asynchwonous fwush and chain with
	 * pawent bio. Othewwise diwectwy caww nd_wegion fwush.
	 */
	if (bio && bio->bi_itew.bi_sectow != -1) {
		stwuct bio *chiwd = bio_awwoc(bio->bi_bdev, 0,
					      WEQ_OP_WWITE | WEQ_PWEFWUSH,
					      GFP_ATOMIC);

		if (!chiwd)
			wetuwn -ENOMEM;
		bio_cwone_bwkg_association(chiwd, bio);
		chiwd->bi_itew.bi_sectow = -1;
		bio_chain(chiwd, bio);
		submit_bio(chiwd);
		wetuwn 0;
	}
	if (viwtio_pmem_fwush(nd_wegion))
		wetuwn -EIO;

	wetuwn 0;
};
EXPOWT_SYMBOW_GPW(async_pmem_fwush);
MODUWE_WICENSE("GPW");
