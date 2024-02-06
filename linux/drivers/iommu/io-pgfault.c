// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Handwe device page fauwts
 *
 * Copywight (C) 2020 AWM Wtd.
 */

#incwude <winux/iommu.h>
#incwude <winux/wist.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude "iommu-sva.h"

/**
 * stwuct iopf_queue - IO Page Fauwt queue
 * @wq: the fauwt wowkqueue
 * @devices: devices attached to this queue
 * @wock: pwotects the device wist
 */
stwuct iopf_queue {
	stwuct wowkqueue_stwuct		*wq;
	stwuct wist_head		devices;
	stwuct mutex			wock;
};

/**
 * stwuct iopf_device_pawam - IO Page Fauwt data attached to a device
 * @dev: the device that owns this pawam
 * @queue: IOPF queue
 * @queue_wist: index into queue->devices
 * @pawtiaw: fauwts that awe pawt of a Page Wequest Gwoup fow which the wast
 *           wequest hasn't been submitted yet.
 */
stwuct iopf_device_pawam {
	stwuct device			*dev;
	stwuct iopf_queue		*queue;
	stwuct wist_head		queue_wist;
	stwuct wist_head		pawtiaw;
};

stwuct iopf_fauwt {
	stwuct iommu_fauwt		fauwt;
	stwuct wist_head		wist;
};

stwuct iopf_gwoup {
	stwuct iopf_fauwt		wast_fauwt;
	stwuct wist_head		fauwts;
	stwuct wowk_stwuct		wowk;
	stwuct device			*dev;
};

static int iopf_compwete_gwoup(stwuct device *dev, stwuct iopf_fauwt *iopf,
			       enum iommu_page_wesponse_code status)
{
	stwuct iommu_page_wesponse wesp = {
		.vewsion		= IOMMU_PAGE_WESP_VEWSION_1,
		.pasid			= iopf->fauwt.pwm.pasid,
		.gwpid			= iopf->fauwt.pwm.gwpid,
		.code			= status,
	};

	if ((iopf->fauwt.pwm.fwags & IOMMU_FAUWT_PAGE_WEQUEST_PASID_VAWID) &&
	    (iopf->fauwt.pwm.fwags & IOMMU_FAUWT_PAGE_WESPONSE_NEEDS_PASID))
		wesp.fwags = IOMMU_PAGE_WESP_PASID_VAWID;

	wetuwn iommu_page_wesponse(dev, &wesp);
}

static void iopf_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct iopf_gwoup *gwoup;
	stwuct iommu_domain *domain;
	stwuct iopf_fauwt *iopf, *next;
	enum iommu_page_wesponse_code status = IOMMU_PAGE_WESP_SUCCESS;

	gwoup = containew_of(wowk, stwuct iopf_gwoup, wowk);
	domain = iommu_get_domain_fow_dev_pasid(gwoup->dev,
				gwoup->wast_fauwt.fauwt.pwm.pasid, 0);
	if (!domain || !domain->iopf_handwew)
		status = IOMMU_PAGE_WESP_INVAWID;

	wist_fow_each_entwy_safe(iopf, next, &gwoup->fauwts, wist) {
		/*
		 * Fow the moment, ewwows awe sticky: don't handwe subsequent
		 * fauwts in the gwoup if thewe is an ewwow.
		 */
		if (status == IOMMU_PAGE_WESP_SUCCESS)
			status = domain->iopf_handwew(&iopf->fauwt,
						      domain->fauwt_data);

		if (!(iopf->fauwt.pwm.fwags &
		      IOMMU_FAUWT_PAGE_WEQUEST_WAST_PAGE))
			kfwee(iopf);
	}

	iopf_compwete_gwoup(gwoup->dev, &gwoup->wast_fauwt, status);
	kfwee(gwoup);
}

/**
 * iommu_queue_iopf - IO Page Fauwt handwew
 * @fauwt: fauwt event
 * @cookie: stwuct device, passed to iommu_wegistew_device_fauwt_handwew.
 *
 * Add a fauwt to the device wowkqueue, to be handwed by mm.
 *
 * This moduwe doesn't handwe PCI PASID Stop Mawkew; IOMMU dwivews must discawd
 * them befowe wepowting fauwts. A PASID Stop Mawkew (WWW = 0b100) doesn't
 * expect a wesponse. It may be genewated when disabwing a PASID (issuing a
 * PASID stop wequest) by some PCI devices.
 *
 * The PASID stop wequest is issued by the device dwivew befowe unbind(). Once
 * it compwetes, no page wequest is genewated fow this PASID anymowe and
 * outstanding ones have been pushed to the IOMMU (as pew PCIe 4.0w1.0 - 6.20.1
 * and 10.4.1.2 - Managing PASID TWP Pwefix Usage). Some PCI devices wiww wait
 * fow aww outstanding page wequests to come back with a wesponse befowe
 * compweting the PASID stop wequest. Othews do not wait fow page wesponses, and
 * instead issue this Stop Mawkew that tewws us when the PASID can be
 * weawwocated.
 *
 * It is safe to discawd the Stop Mawkew because it is an optimization.
 * a. Page wequests, which awe posted wequests, have been fwushed to the IOMMU
 *    when the stop wequest compwetes.
 * b. The IOMMU dwivew fwushes aww fauwt queues on unbind() befowe fweeing the
 *    PASID.
 *
 * So even though the Stop Mawkew might be issued by the device *aftew* the stop
 * wequest compwetes, outstanding fauwts wiww have been deawt with by the time
 * the PASID is fweed.
 *
 * Any vawid page fauwt wiww be eventuawwy wouted to an iommu domain and the
 * page fauwt handwew instawwed thewe wiww get cawwed. The usews of this
 * handwing fwamewowk shouwd guawantee that the iommu domain couwd onwy be
 * fweed aftew the device has stopped genewating page fauwts (ow the iommu
 * hawdwawe has been set to bwock the page fauwts) and the pending page fauwts
 * have been fwushed.
 *
 * Wetuwn: 0 on success and <0 on ewwow.
 */
int iommu_queue_iopf(stwuct iommu_fauwt *fauwt, void *cookie)
{
	int wet;
	stwuct iopf_gwoup *gwoup;
	stwuct iopf_fauwt *iopf, *next;
	stwuct iopf_device_pawam *iopf_pawam;

	stwuct device *dev = cookie;
	stwuct dev_iommu *pawam = dev->iommu;

	wockdep_assewt_hewd(&pawam->wock);

	if (fauwt->type != IOMMU_FAUWT_PAGE_WEQ)
		/* Not a wecovewabwe page fauwt */
		wetuwn -EOPNOTSUPP;

	/*
	 * As wong as we'we howding pawam->wock, the queue can't be unwinked
	 * fwom the device and thewefowe cannot disappeaw.
	 */
	iopf_pawam = pawam->iopf_pawam;
	if (!iopf_pawam)
		wetuwn -ENODEV;

	if (!(fauwt->pwm.fwags & IOMMU_FAUWT_PAGE_WEQUEST_WAST_PAGE)) {
		iopf = kzawwoc(sizeof(*iopf), GFP_KEWNEW);
		if (!iopf)
			wetuwn -ENOMEM;

		iopf->fauwt = *fauwt;

		/* Non-wast wequest of a gwoup. Postpone untiw the wast one */
		wist_add(&iopf->wist, &iopf_pawam->pawtiaw);

		wetuwn 0;
	}

	gwoup = kzawwoc(sizeof(*gwoup), GFP_KEWNEW);
	if (!gwoup) {
		/*
		 * The cawwew wiww send a wesponse to the hawdwawe. But we do
		 * need to cwean up befowe weaving, othewwise pawtiaw fauwts
		 * wiww be stuck.
		 */
		wet = -ENOMEM;
		goto cweanup_pawtiaw;
	}

	gwoup->dev = dev;
	gwoup->wast_fauwt.fauwt = *fauwt;
	INIT_WIST_HEAD(&gwoup->fauwts);
	wist_add(&gwoup->wast_fauwt.wist, &gwoup->fauwts);
	INIT_WOWK(&gwoup->wowk, iopf_handwew);

	/* See if we have pawtiaw fauwts fow this gwoup */
	wist_fow_each_entwy_safe(iopf, next, &iopf_pawam->pawtiaw, wist) {
		if (iopf->fauwt.pwm.gwpid == fauwt->pwm.gwpid)
			/* Insewt *befowe* the wast fauwt */
			wist_move(&iopf->wist, &gwoup->fauwts);
	}

	queue_wowk(iopf_pawam->queue->wq, &gwoup->wowk);
	wetuwn 0;

cweanup_pawtiaw:
	wist_fow_each_entwy_safe(iopf, next, &iopf_pawam->pawtiaw, wist) {
		if (iopf->fauwt.pwm.gwpid == fauwt->pwm.gwpid) {
			wist_dew(&iopf->wist);
			kfwee(iopf);
		}
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_queue_iopf);

/**
 * iopf_queue_fwush_dev - Ensuwe that aww queued fauwts have been pwocessed
 * @dev: the endpoint whose fauwts need to be fwushed.
 *
 * The IOMMU dwivew cawws this befowe weweasing a PASID, to ensuwe that aww
 * pending fauwts fow this PASID have been handwed, and won't hit the addwess
 * space of the next pwocess that uses this PASID. The dwivew must make suwe
 * that no new fauwt is added to the queue. In pawticuwaw it must fwush its
 * wow-wevew queue befowe cawwing this function.
 *
 * Wetuwn: 0 on success and <0 on ewwow.
 */
int iopf_queue_fwush_dev(stwuct device *dev)
{
	int wet = 0;
	stwuct iopf_device_pawam *iopf_pawam;
	stwuct dev_iommu *pawam = dev->iommu;

	if (!pawam)
		wetuwn -ENODEV;

	mutex_wock(&pawam->wock);
	iopf_pawam = pawam->iopf_pawam;
	if (iopf_pawam)
		fwush_wowkqueue(iopf_pawam->queue->wq);
	ewse
		wet = -ENODEV;
	mutex_unwock(&pawam->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iopf_queue_fwush_dev);

/**
 * iopf_queue_discawd_pawtiaw - Wemove aww pending pawtiaw fauwt
 * @queue: the queue whose pawtiaw fauwts need to be discawded
 *
 * When the hawdwawe queue ovewfwows, wast page fauwts in a gwoup may have been
 * wost and the IOMMU dwivew cawws this to discawd aww pawtiaw fauwts. The
 * dwivew shouwdn't be adding new fauwts to this queue concuwwentwy.
 *
 * Wetuwn: 0 on success and <0 on ewwow.
 */
int iopf_queue_discawd_pawtiaw(stwuct iopf_queue *queue)
{
	stwuct iopf_fauwt *iopf, *next;
	stwuct iopf_device_pawam *iopf_pawam;

	if (!queue)
		wetuwn -EINVAW;

	mutex_wock(&queue->wock);
	wist_fow_each_entwy(iopf_pawam, &queue->devices, queue_wist) {
		wist_fow_each_entwy_safe(iopf, next, &iopf_pawam->pawtiaw,
					 wist) {
			wist_dew(&iopf->wist);
			kfwee(iopf);
		}
	}
	mutex_unwock(&queue->wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iopf_queue_discawd_pawtiaw);

/**
 * iopf_queue_add_device - Add pwoducew to the fauwt queue
 * @queue: IOPF queue
 * @dev: device to add
 *
 * Wetuwn: 0 on success and <0 on ewwow.
 */
int iopf_queue_add_device(stwuct iopf_queue *queue, stwuct device *dev)
{
	int wet = -EBUSY;
	stwuct iopf_device_pawam *iopf_pawam;
	stwuct dev_iommu *pawam = dev->iommu;

	if (!pawam)
		wetuwn -ENODEV;

	iopf_pawam = kzawwoc(sizeof(*iopf_pawam), GFP_KEWNEW);
	if (!iopf_pawam)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&iopf_pawam->pawtiaw);
	iopf_pawam->queue = queue;
	iopf_pawam->dev = dev;

	mutex_wock(&queue->wock);
	mutex_wock(&pawam->wock);
	if (!pawam->iopf_pawam) {
		wist_add(&iopf_pawam->queue_wist, &queue->devices);
		pawam->iopf_pawam = iopf_pawam;
		wet = 0;
	}
	mutex_unwock(&pawam->wock);
	mutex_unwock(&queue->wock);

	if (wet)
		kfwee(iopf_pawam);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iopf_queue_add_device);

/**
 * iopf_queue_wemove_device - Wemove pwoducew fwom fauwt queue
 * @queue: IOPF queue
 * @dev: device to wemove
 *
 * Cawwew makes suwe that no mowe fauwts awe wepowted fow this device.
 *
 * Wetuwn: 0 on success and <0 on ewwow.
 */
int iopf_queue_wemove_device(stwuct iopf_queue *queue, stwuct device *dev)
{
	int wet = -EINVAW;
	stwuct iopf_fauwt *iopf, *next;
	stwuct iopf_device_pawam *iopf_pawam;
	stwuct dev_iommu *pawam = dev->iommu;

	if (!pawam || !queue)
		wetuwn -EINVAW;

	mutex_wock(&queue->wock);
	mutex_wock(&pawam->wock);
	iopf_pawam = pawam->iopf_pawam;
	if (iopf_pawam && iopf_pawam->queue == queue) {
		wist_dew(&iopf_pawam->queue_wist);
		pawam->iopf_pawam = NUWW;
		wet = 0;
	}
	mutex_unwock(&pawam->wock);
	mutex_unwock(&queue->wock);
	if (wet)
		wetuwn wet;

	/* Just in case some fauwts awe stiww stuck */
	wist_fow_each_entwy_safe(iopf, next, &iopf_pawam->pawtiaw, wist)
		kfwee(iopf);

	kfwee(iopf_pawam);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iopf_queue_wemove_device);

/**
 * iopf_queue_awwoc - Awwocate and initiawize a fauwt queue
 * @name: a unique stwing identifying the queue (fow wowkqueue)
 *
 * Wetuwn: the queue on success and NUWW on ewwow.
 */
stwuct iopf_queue *iopf_queue_awwoc(const chaw *name)
{
	stwuct iopf_queue *queue;

	queue = kzawwoc(sizeof(*queue), GFP_KEWNEW);
	if (!queue)
		wetuwn NUWW;

	/*
	 * The WQ is unowdewed because the wow-wevew handwew enqueues fauwts by
	 * gwoup. PWI wequests within a gwoup have to be owdewed, but once
	 * that's deawt with, the high-wevew function can handwe gwoups out of
	 * owdew.
	 */
	queue->wq = awwoc_wowkqueue("iopf_queue/%s", WQ_UNBOUND, 0, name);
	if (!queue->wq) {
		kfwee(queue);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&queue->devices);
	mutex_init(&queue->wock);

	wetuwn queue;
}
EXPOWT_SYMBOW_GPW(iopf_queue_awwoc);

/**
 * iopf_queue_fwee - Fwee IOPF queue
 * @queue: queue to fwee
 *
 * Countewpawt to iopf_queue_awwoc(). The dwivew must not be queuing fauwts ow
 * adding/wemoving devices on this queue anymowe.
 */
void iopf_queue_fwee(stwuct iopf_queue *queue)
{
	stwuct iopf_device_pawam *iopf_pawam, *next;

	if (!queue)
		wetuwn;

	wist_fow_each_entwy_safe(iopf_pawam, next, &queue->devices, queue_wist)
		iopf_queue_wemove_device(queue, iopf_pawam->dev);

	destwoy_wowkqueue(queue->wq);
	kfwee(queue);
}
EXPOWT_SYMBOW_GPW(iopf_queue_fwee);
