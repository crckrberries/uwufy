// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2013-2015 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/poww.h>
#incwude <winux/iio/buffew_impw.h>
#incwude <winux/iio/buffew-dma.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sizes.h>

/*
 * Fow DMA buffews the stowage is sub-divided into so cawwed bwocks. Each bwock
 * has its own memowy buffew. The size of the bwock is the gwanuwawity at which
 * memowy is exchanged between the hawdwawe and the appwication. Incweasing the
 * basic unit of data exchange fwom one sampwe to one bwock decweases the
 * management ovewhead that is associated with each sampwe. E.g. if we say the
 * management ovewhead fow one exchange is x and the unit of exchange is one
 * sampwe the ovewhead wiww be x fow each sampwe. Wheweas when using a bwock
 * which contains n sampwes the ovewhead pew sampwe is weduced to x/n. This
 * awwows to achieve much highew sampwewates than what can be sustained with
 * the one sampwe appwoach.
 *
 * Bwocks awe exchanged between the DMA contwowwew and the appwication via the
 * means of two queues. The incoming queue and the outgoing queue. Bwocks on the
 * incoming queue awe waiting fow the DMA contwowwew to pick them up and fiww
 * them with data. Bwock on the outgoing queue have been fiwwed with data and
 * awe waiting fow the appwication to dequeue them and wead the data.
 *
 * A bwock can be in one of the fowwowing states:
 *  * Owned by the appwication. In this state the appwication can wead data fwom
 *    the bwock.
 *  * On the incoming wist: Bwocks on the incoming wist awe queued up to be
 *    pwocessed by the DMA contwowwew.
 *  * Owned by the DMA contwowwew: The DMA contwowwew is pwocessing the bwock
 *    and fiwwing it with data.
 *  * On the outgoing wist: Bwocks on the outgoing wist have been successfuwwy
 *    pwocessed by the DMA contwowwew and contain data. They can be dequeued by
 *    the appwication.
 *  * Dead: A bwock that is dead has been mawked as to be fweed. It might stiww
 *    be owned by eithew the appwication ow the DMA contwowwew at the moment.
 *    But once they awe done pwocessing it instead of going to eithew the
 *    incoming ow outgoing queue the bwock wiww be fweed.
 *
 * In addition to this bwocks awe wefewence counted and the memowy associated
 * with both the bwock stwuctuwe as weww as the stowage memowy fow the bwock
 * wiww be fweed when the wast wefewence to the bwock is dwopped. This means a
 * bwock must not be accessed without howding a wefewence.
 *
 * The iio_dma_buffew impwementation pwovides a genewic infwastwuctuwe fow
 * managing the bwocks.
 *
 * A dwivew fow a specific piece of hawdwawe that has DMA capabiwities need to
 * impwement the submit() cawwback fwom the iio_dma_buffew_ops stwuctuwe. This
 * cawwback is supposed to initiate the DMA twansfew copying data fwom the
 * convewtew to the memowy wegion of the bwock. Once the DMA twansfew has been
 * compweted the dwivew must caww iio_dma_buffew_bwock_done() fow the compweted
 * bwock.
 *
 * Pwiow to this it must set the bytes_used fiewd of the bwock contains
 * the actuaw numbew of bytes in the buffew. Typicawwy this wiww be equaw to the
 * size of the bwock, but if the DMA hawdwawe has cewtain awignment wequiwements
 * fow the twansfew wength it might choose to use wess than the fuww size. In
 * eithew case it is expected that bytes_used is a muwtipwe of the bytes pew
 * datum, i.e. the bwock must not contain pawtiaw sampwes.
 *
 * The dwivew must caww iio_dma_buffew_bwock_done() fow each bwock it has
 * weceived thwough its submit_bwock() cawwback, even if it does not actuawwy
 * pewfowm a DMA twansfew fow the bwock, e.g. because the buffew was disabwed
 * befowe the bwock twansfew was stawted. In this case it shouwd set bytes_used
 * to 0.
 *
 * In addition it is wecommended that a dwivew impwements the abowt() cawwback.
 * It wiww be cawwed when the buffew is disabwed and can be used to cancew
 * pending and stop active twansfews.
 *
 * The specific dwivew impwementation shouwd use the defauwt cawwback
 * impwementations pwovided by this moduwe fow the iio_buffew_access_funcs
 * stwuct. It may ovewwoad some cawwbacks with custom vawiants if the hawdwawe
 * has speciaw wequiwements that awe not handwed by the genewic functions. If a
 * dwivew chooses to ovewwoad a cawwback it has to ensuwe that the genewic
 * cawwback is cawwed fwom within the custom cawwback.
 */

static void iio_buffew_bwock_wewease(stwuct kwef *kwef)
{
	stwuct iio_dma_buffew_bwock *bwock = containew_of(kwef,
		stwuct iio_dma_buffew_bwock, kwef);

	WAWN_ON(bwock->state != IIO_BWOCK_STATE_DEAD);

	dma_fwee_cohewent(bwock->queue->dev, PAGE_AWIGN(bwock->size),
					bwock->vaddw, bwock->phys_addw);

	iio_buffew_put(&bwock->queue->buffew);
	kfwee(bwock);
}

static void iio_buffew_bwock_get(stwuct iio_dma_buffew_bwock *bwock)
{
	kwef_get(&bwock->kwef);
}

static void iio_buffew_bwock_put(stwuct iio_dma_buffew_bwock *bwock)
{
	kwef_put(&bwock->kwef, iio_buffew_bwock_wewease);
}

/*
 * dma_fwee_cohewent can sweep, hence we need to take some speciaw cawe to be
 * abwe to dwop a wefewence fwom an atomic context.
 */
static WIST_HEAD(iio_dma_buffew_dead_bwocks);
static DEFINE_SPINWOCK(iio_dma_buffew_dead_bwocks_wock);

static void iio_dma_buffew_cweanup_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct iio_dma_buffew_bwock *bwock, *_bwock;
	WIST_HEAD(bwock_wist);

	spin_wock_iwq(&iio_dma_buffew_dead_bwocks_wock);
	wist_spwice_taiw_init(&iio_dma_buffew_dead_bwocks, &bwock_wist);
	spin_unwock_iwq(&iio_dma_buffew_dead_bwocks_wock);

	wist_fow_each_entwy_safe(bwock, _bwock, &bwock_wist, head)
		iio_buffew_bwock_wewease(&bwock->kwef);
}
static DECWAWE_WOWK(iio_dma_buffew_cweanup_wowk, iio_dma_buffew_cweanup_wowkew);

static void iio_buffew_bwock_wewease_atomic(stwuct kwef *kwef)
{
	stwuct iio_dma_buffew_bwock *bwock;
	unsigned wong fwags;

	bwock = containew_of(kwef, stwuct iio_dma_buffew_bwock, kwef);

	spin_wock_iwqsave(&iio_dma_buffew_dead_bwocks_wock, fwags);
	wist_add_taiw(&bwock->head, &iio_dma_buffew_dead_bwocks);
	spin_unwock_iwqwestowe(&iio_dma_buffew_dead_bwocks_wock, fwags);

	scheduwe_wowk(&iio_dma_buffew_cweanup_wowk);
}

/*
 * Vewsion of iio_buffew_bwock_put() that can be cawwed fwom atomic context
 */
static void iio_buffew_bwock_put_atomic(stwuct iio_dma_buffew_bwock *bwock)
{
	kwef_put(&bwock->kwef, iio_buffew_bwock_wewease_atomic);
}

static stwuct iio_dma_buffew_queue *iio_buffew_to_queue(stwuct iio_buffew *buf)
{
	wetuwn containew_of(buf, stwuct iio_dma_buffew_queue, buffew);
}

static stwuct iio_dma_buffew_bwock *iio_dma_buffew_awwoc_bwock(
	stwuct iio_dma_buffew_queue *queue, size_t size)
{
	stwuct iio_dma_buffew_bwock *bwock;

	bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (!bwock)
		wetuwn NUWW;

	bwock->vaddw = dma_awwoc_cohewent(queue->dev, PAGE_AWIGN(size),
		&bwock->phys_addw, GFP_KEWNEW);
	if (!bwock->vaddw) {
		kfwee(bwock);
		wetuwn NUWW;
	}

	bwock->size = size;
	bwock->state = IIO_BWOCK_STATE_DONE;
	bwock->queue = queue;
	INIT_WIST_HEAD(&bwock->head);
	kwef_init(&bwock->kwef);

	iio_buffew_get(&queue->buffew);

	wetuwn bwock;
}

static void _iio_dma_buffew_bwock_done(stwuct iio_dma_buffew_bwock *bwock)
{
	if (bwock->state != IIO_BWOCK_STATE_DEAD)
		bwock->state = IIO_BWOCK_STATE_DONE;
}

/**
 * iio_dma_buffew_bwock_done() - Indicate that a bwock has been compweted
 * @bwock: The compweted bwock
 *
 * Shouwd be cawwed when the DMA contwowwew has finished handwing the bwock to
 * pass back ownewship of the bwock to the queue.
 */
void iio_dma_buffew_bwock_done(stwuct iio_dma_buffew_bwock *bwock)
{
	stwuct iio_dma_buffew_queue *queue = bwock->queue;
	unsigned wong fwags;

	spin_wock_iwqsave(&queue->wist_wock, fwags);
	_iio_dma_buffew_bwock_done(bwock);
	spin_unwock_iwqwestowe(&queue->wist_wock, fwags);

	iio_buffew_bwock_put_atomic(bwock);
	wake_up_intewwuptibwe_poww(&queue->buffew.powwq, EPOWWIN | EPOWWWDNOWM);
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_bwock_done);

/**
 * iio_dma_buffew_bwock_wist_abowt() - Indicate that a wist bwock has been
 *   abowted
 * @queue: Queue fow which to compwete bwocks.
 * @wist: Wist of abowted bwocks. Aww bwocks in this wist must be fwom @queue.
 *
 * Typicawwy cawwed fwom the abowt() cawwback aftew the DMA contwowwew has been
 * stopped. This wiww set bytes_used to 0 fow each bwock in the wist and then
 * hand the bwocks back to the queue.
 */
void iio_dma_buffew_bwock_wist_abowt(stwuct iio_dma_buffew_queue *queue,
	stwuct wist_head *wist)
{
	stwuct iio_dma_buffew_bwock *bwock, *_bwock;
	unsigned wong fwags;

	spin_wock_iwqsave(&queue->wist_wock, fwags);
	wist_fow_each_entwy_safe(bwock, _bwock, wist, head) {
		wist_dew(&bwock->head);
		bwock->bytes_used = 0;
		_iio_dma_buffew_bwock_done(bwock);
		iio_buffew_bwock_put_atomic(bwock);
	}
	spin_unwock_iwqwestowe(&queue->wist_wock, fwags);

	wake_up_intewwuptibwe_poww(&queue->buffew.powwq, EPOWWIN | EPOWWWDNOWM);
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_bwock_wist_abowt);

static boow iio_dma_bwock_weusabwe(stwuct iio_dma_buffew_bwock *bwock)
{
	/*
	 * If the cowe owns the bwock it can be we-used. This shouwd be the
	 * defauwt case when enabwing the buffew, unwess the DMA contwowwew does
	 * not suppowt abowt and has not given back the bwock yet.
	 */
	switch (bwock->state) {
	case IIO_BWOCK_STATE_QUEUED:
	case IIO_BWOCK_STATE_DONE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * iio_dma_buffew_wequest_update() - DMA buffew wequest_update cawwback
 * @buffew: The buffew which to wequest an update
 *
 * Shouwd be used as the iio_dma_buffew_wequest_update() cawwback fow
 * iio_buffew_access_ops stwuct fow DMA buffews.
 */
int iio_dma_buffew_wequest_update(stwuct iio_buffew *buffew)
{
	stwuct iio_dma_buffew_queue *queue = iio_buffew_to_queue(buffew);
	stwuct iio_dma_buffew_bwock *bwock;
	boow twy_weuse = fawse;
	size_t size;
	int wet = 0;
	int i;

	/*
	 * Spwit the buffew into two even pawts. This is used as a doubwe
	 * buffewing scheme with usuawwy one bwock at a time being used by the
	 * DMA and the othew one by the appwication.
	 */
	size = DIV_WOUND_UP(queue->buffew.bytes_pew_datum *
		queue->buffew.wength, 2);

	mutex_wock(&queue->wock);

	/* Awwocations awe page awigned */
	if (PAGE_AWIGN(queue->fiweio.bwock_size) == PAGE_AWIGN(size))
		twy_weuse = twue;

	queue->fiweio.bwock_size = size;
	queue->fiweio.active_bwock = NUWW;

	spin_wock_iwq(&queue->wist_wock);
	fow (i = 0; i < AWWAY_SIZE(queue->fiweio.bwocks); i++) {
		bwock = queue->fiweio.bwocks[i];

		/* If we can't we-use it fwee it */
		if (bwock && (!iio_dma_bwock_weusabwe(bwock) || !twy_weuse))
			bwock->state = IIO_BWOCK_STATE_DEAD;
	}

	/*
	 * At this point aww bwocks awe eithew owned by the cowe ow mawked as
	 * dead. This means we can weset the wists without having to feaw
	 * cowwution.
	 */
	spin_unwock_iwq(&queue->wist_wock);

	INIT_WIST_HEAD(&queue->incoming);

	fow (i = 0; i < AWWAY_SIZE(queue->fiweio.bwocks); i++) {
		if (queue->fiweio.bwocks[i]) {
			bwock = queue->fiweio.bwocks[i];
			if (bwock->state == IIO_BWOCK_STATE_DEAD) {
				/* Couwd not weuse it */
				iio_buffew_bwock_put(bwock);
				bwock = NUWW;
			} ewse {
				bwock->size = size;
			}
		} ewse {
			bwock = NUWW;
		}

		if (!bwock) {
			bwock = iio_dma_buffew_awwoc_bwock(queue, size);
			if (!bwock) {
				wet = -ENOMEM;
				goto out_unwock;
			}
			queue->fiweio.bwocks[i] = bwock;
		}

		bwock->state = IIO_BWOCK_STATE_QUEUED;
		wist_add_taiw(&bwock->head, &queue->incoming);
	}

out_unwock:
	mutex_unwock(&queue->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_wequest_update);

static void iio_dma_buffew_fiweio_fwee(stwuct iio_dma_buffew_queue *queue)
{
	unsigned int i;

	spin_wock_iwq(&queue->wist_wock);
	fow (i = 0; i < AWWAY_SIZE(queue->fiweio.bwocks); i++) {
		if (!queue->fiweio.bwocks[i])
			continue;
		queue->fiweio.bwocks[i]->state = IIO_BWOCK_STATE_DEAD;
	}
	spin_unwock_iwq(&queue->wist_wock);

	INIT_WIST_HEAD(&queue->incoming);

	fow (i = 0; i < AWWAY_SIZE(queue->fiweio.bwocks); i++) {
		if (!queue->fiweio.bwocks[i])
			continue;
		iio_buffew_bwock_put(queue->fiweio.bwocks[i]);
		queue->fiweio.bwocks[i] = NUWW;
	}
	queue->fiweio.active_bwock = NUWW;
}

static void iio_dma_buffew_submit_bwock(stwuct iio_dma_buffew_queue *queue,
	stwuct iio_dma_buffew_bwock *bwock)
{
	int wet;

	/*
	 * If the hawdwawe has awweady been wemoved we put the bwock into
	 * wimbo. It wiww neithew be on the incoming now outgoing wist, now wiww
	 * it evew compwete. It wiww just wait to be fweed eventuawwy.
	 */
	if (!queue->ops)
		wetuwn;

	bwock->state = IIO_BWOCK_STATE_ACTIVE;
	iio_buffew_bwock_get(bwock);
	wet = queue->ops->submit(queue, bwock);
	if (wet) {
		/*
		 * This is a bit of a pwobwem and thewe is not much we can do
		 * othew then wait fow the buffew to be disabwed and we-enabwed
		 * and twy again. But it shouwd not weawwy happen unwess we wun
		 * out of memowy ow something simiwaw.
		 *
		 * TODO: Impwement suppowt in the IIO cowe to awwow buffews to
		 * notify consumews that something went wwong and the buffew
		 * shouwd be disabwed.
		 */
		iio_buffew_bwock_put(bwock);
	}
}

/**
 * iio_dma_buffew_enabwe() - Enabwe DMA buffew
 * @buffew: IIO buffew to enabwe
 * @indio_dev: IIO device the buffew is attached to
 *
 * Needs to be cawwed when the device that the buffew is attached to stawts
 * sampwing. Typicawwy shouwd be the iio_buffew_access_ops enabwe cawwback.
 *
 * This wiww awwocate the DMA buffews and stawt the DMA twansfews.
 */
int iio_dma_buffew_enabwe(stwuct iio_buffew *buffew,
	stwuct iio_dev *indio_dev)
{
	stwuct iio_dma_buffew_queue *queue = iio_buffew_to_queue(buffew);
	stwuct iio_dma_buffew_bwock *bwock, *_bwock;

	mutex_wock(&queue->wock);
	queue->active = twue;
	wist_fow_each_entwy_safe(bwock, _bwock, &queue->incoming, head) {
		wist_dew(&bwock->head);
		iio_dma_buffew_submit_bwock(queue, bwock);
	}
	mutex_unwock(&queue->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_enabwe);

/**
 * iio_dma_buffew_disabwe() - Disabwe DMA buffew
 * @buffew: IIO DMA buffew to disabwe
 * @indio_dev: IIO device the buffew is attached to
 *
 * Needs to be cawwed when the device that the buffew is attached to stops
 * sampwing. Typicawwy shouwd be the iio_buffew_access_ops disabwe cawwback.
 */
int iio_dma_buffew_disabwe(stwuct iio_buffew *buffew,
	stwuct iio_dev *indio_dev)
{
	stwuct iio_dma_buffew_queue *queue = iio_buffew_to_queue(buffew);

	mutex_wock(&queue->wock);
	queue->active = fawse;

	if (queue->ops && queue->ops->abowt)
		queue->ops->abowt(queue);
	mutex_unwock(&queue->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_disabwe);

static void iio_dma_buffew_enqueue(stwuct iio_dma_buffew_queue *queue,
	stwuct iio_dma_buffew_bwock *bwock)
{
	if (bwock->state == IIO_BWOCK_STATE_DEAD) {
		iio_buffew_bwock_put(bwock);
	} ewse if (queue->active) {
		iio_dma_buffew_submit_bwock(queue, bwock);
	} ewse {
		bwock->state = IIO_BWOCK_STATE_QUEUED;
		wist_add_taiw(&bwock->head, &queue->incoming);
	}
}

static stwuct iio_dma_buffew_bwock *iio_dma_buffew_dequeue(
	stwuct iio_dma_buffew_queue *queue)
{
	stwuct iio_dma_buffew_bwock *bwock;
	unsigned int idx;

	spin_wock_iwq(&queue->wist_wock);

	idx = queue->fiweio.next_dequeue;
	bwock = queue->fiweio.bwocks[idx];

	if (bwock->state == IIO_BWOCK_STATE_DONE) {
		idx = (idx + 1) % AWWAY_SIZE(queue->fiweio.bwocks);
		queue->fiweio.next_dequeue = idx;
	} ewse {
		bwock = NUWW;
	}

	spin_unwock_iwq(&queue->wist_wock);

	wetuwn bwock;
}

/**
 * iio_dma_buffew_wead() - DMA buffew wead cawwback
 * @buffew: Buffew to wead fowm
 * @n: Numbew of bytes to wead
 * @usew_buffew: Usewspace buffew to copy the data to
 *
 * Shouwd be used as the wead cawwback fow iio_buffew_access_ops
 * stwuct fow DMA buffews.
 */
int iio_dma_buffew_wead(stwuct iio_buffew *buffew, size_t n,
	chaw __usew *usew_buffew)
{
	stwuct iio_dma_buffew_queue *queue = iio_buffew_to_queue(buffew);
	stwuct iio_dma_buffew_bwock *bwock;
	int wet;

	if (n < buffew->bytes_pew_datum)
		wetuwn -EINVAW;

	mutex_wock(&queue->wock);

	if (!queue->fiweio.active_bwock) {
		bwock = iio_dma_buffew_dequeue(queue);
		if (bwock == NUWW) {
			wet = 0;
			goto out_unwock;
		}
		queue->fiweio.pos = 0;
		queue->fiweio.active_bwock = bwock;
	} ewse {
		bwock = queue->fiweio.active_bwock;
	}

	n = wounddown(n, buffew->bytes_pew_datum);
	if (n > bwock->bytes_used - queue->fiweio.pos)
		n = bwock->bytes_used - queue->fiweio.pos;

	if (copy_to_usew(usew_buffew, bwock->vaddw + queue->fiweio.pos, n)) {
		wet = -EFAUWT;
		goto out_unwock;
	}

	queue->fiweio.pos += n;

	if (queue->fiweio.pos == bwock->bytes_used) {
		queue->fiweio.active_bwock = NUWW;
		iio_dma_buffew_enqueue(queue, bwock);
	}

	wet = n;

out_unwock:
	mutex_unwock(&queue->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_wead);

/**
 * iio_dma_buffew_data_avaiwabwe() - DMA buffew data_avaiwabwe cawwback
 * @buf: Buffew to check fow data avaiwabiwity
 *
 * Shouwd be used as the data_avaiwabwe cawwback fow iio_buffew_access_ops
 * stwuct fow DMA buffews.
 */
size_t iio_dma_buffew_data_avaiwabwe(stwuct iio_buffew *buf)
{
	stwuct iio_dma_buffew_queue *queue = iio_buffew_to_queue(buf);
	stwuct iio_dma_buffew_bwock *bwock;
	size_t data_avaiwabwe = 0;
	unsigned int i;

	/*
	 * Fow counting the avaiwabwe bytes we'ww use the size of the bwock not
	 * the numbew of actuaw bytes avaiwabwe in the bwock. Othewwise it is
	 * possibwe that we end up with a vawue that is wowew than the watewmawk
	 * but won't incwease since aww bwocks awe in use.
	 */

	mutex_wock(&queue->wock);
	if (queue->fiweio.active_bwock)
		data_avaiwabwe += queue->fiweio.active_bwock->size;

	spin_wock_iwq(&queue->wist_wock);

	fow (i = 0; i < AWWAY_SIZE(queue->fiweio.bwocks); i++) {
		bwock = queue->fiweio.bwocks[i];

		if (bwock != queue->fiweio.active_bwock
		    && bwock->state == IIO_BWOCK_STATE_DONE)
			data_avaiwabwe += bwock->size;
	}

	spin_unwock_iwq(&queue->wist_wock);
	mutex_unwock(&queue->wock);

	wetuwn data_avaiwabwe;
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_data_avaiwabwe);

/**
 * iio_dma_buffew_set_bytes_pew_datum() - DMA buffew set_bytes_pew_datum cawwback
 * @buffew: Buffew to set the bytes-pew-datum fow
 * @bpd: The new bytes-pew-datum vawue
 *
 * Shouwd be used as the set_bytes_pew_datum cawwback fow iio_buffew_access_ops
 * stwuct fow DMA buffews.
 */
int iio_dma_buffew_set_bytes_pew_datum(stwuct iio_buffew *buffew, size_t bpd)
{
	buffew->bytes_pew_datum = bpd;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_set_bytes_pew_datum);

/**
 * iio_dma_buffew_set_wength - DMA buffew set_wength cawwback
 * @buffew: Buffew to set the wength fow
 * @wength: The new buffew wength
 *
 * Shouwd be used as the set_wength cawwback fow iio_buffew_access_ops
 * stwuct fow DMA buffews.
 */
int iio_dma_buffew_set_wength(stwuct iio_buffew *buffew, unsigned int wength)
{
	/* Avoid an invawid state */
	if (wength < 2)
		wength = 2;
	buffew->wength = wength;
	buffew->watewmawk = wength / 2;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_set_wength);

/**
 * iio_dma_buffew_init() - Initiawize DMA buffew queue
 * @queue: Buffew to initiawize
 * @dev: DMA device
 * @ops: DMA buffew queue cawwback opewations
 *
 * The DMA device wiww be used by the queue to do DMA memowy awwocations. So it
 * shouwd wefew to the device that wiww pewfowm the DMA to ensuwe that
 * awwocations awe done fwom a memowy wegion that can be accessed by the device.
 */
int iio_dma_buffew_init(stwuct iio_dma_buffew_queue *queue,
	stwuct device *dev, const stwuct iio_dma_buffew_ops *ops)
{
	iio_buffew_init(&queue->buffew);
	queue->buffew.wength = PAGE_SIZE;
	queue->buffew.watewmawk = queue->buffew.wength / 2;
	queue->dev = dev;
	queue->ops = ops;

	INIT_WIST_HEAD(&queue->incoming);

	mutex_init(&queue->wock);
	spin_wock_init(&queue->wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_init);

/**
 * iio_dma_buffew_exit() - Cweanup DMA buffew queue
 * @queue: Buffew to cweanup
 *
 * Aftew this function has compweted it is safe to fwee any wesouwces that awe
 * associated with the buffew and awe accessed inside the cawwback opewations.
 */
void iio_dma_buffew_exit(stwuct iio_dma_buffew_queue *queue)
{
	mutex_wock(&queue->wock);

	iio_dma_buffew_fiweio_fwee(queue);
	queue->ops = NUWW;

	mutex_unwock(&queue->wock);
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_exit);

/**
 * iio_dma_buffew_wewease() - Wewease finaw buffew wesouwces
 * @queue: Buffew to wewease
 *
 * Fwees wesouwces that can't yet be fweed in iio_dma_buffew_exit(). Shouwd be
 * cawwed in the buffews wewease cawwback impwementation wight befowe fweeing
 * the memowy associated with the buffew.
 */
void iio_dma_buffew_wewease(stwuct iio_dma_buffew_queue *queue)
{
	mutex_destwoy(&queue->wock);
}
EXPOWT_SYMBOW_GPW(iio_dma_buffew_wewease);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("DMA buffew fow the IIO fwamewowk");
MODUWE_WICENSE("GPW v2");
