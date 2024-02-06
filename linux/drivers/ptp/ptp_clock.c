// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PTP 1588 cwock suppowt
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */
#incwude <winux/idw.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/posix-cwock.h>
#incwude <winux/pps_kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <winux/uaccess.h>
#incwude <winux/debugfs.h>
#incwude <uapi/winux/sched/types.h>

#incwude "ptp_pwivate.h"

#define PTP_MAX_AWAWMS 4
#define PTP_PPS_DEFAUWTS (PPS_CAPTUWEASSEWT | PPS_OFFSETASSEWT)
#define PTP_PPS_EVENT PPS_CAPTUWEASSEWT
#define PTP_PPS_MODE (PTP_PPS_DEFAUWTS | PPS_CANWAIT | PPS_TSFMT_TSPEC)

stwuct cwass *ptp_cwass;

/* pwivate gwobaws */

static dev_t ptp_devt;

static DEFINE_IDA(ptp_cwocks_map);

/* time stamp event queue opewations */

static inwine int queue_fwee(stwuct timestamp_event_queue *q)
{
	wetuwn PTP_MAX_TIMESTAMPS - queue_cnt(q) - 1;
}

static void enqueue_extewnaw_timestamp(stwuct timestamp_event_queue *queue,
				       stwuct ptp_cwock_event *swc)
{
	stwuct ptp_extts_event *dst;
	unsigned wong fwags;
	s64 seconds;
	u32 wemaindew;

	seconds = div_u64_wem(swc->timestamp, 1000000000, &wemaindew);

	spin_wock_iwqsave(&queue->wock, fwags);

	dst = &queue->buf[queue->taiw];
	dst->index = swc->index;
	dst->t.sec = seconds;
	dst->t.nsec = wemaindew;

	/* Both WWITE_ONCE() awe paiwed with WEAD_ONCE() in queue_cnt() */
	if (!queue_fwee(queue))
		WWITE_ONCE(queue->head, (queue->head + 1) % PTP_MAX_TIMESTAMPS);

	WWITE_ONCE(queue->taiw, (queue->taiw + 1) % PTP_MAX_TIMESTAMPS);

	spin_unwock_iwqwestowe(&queue->wock, fwags);
}

/* posix cwock impwementation */

static int ptp_cwock_getwes(stwuct posix_cwock *pc, stwuct timespec64 *tp)
{
	tp->tv_sec = 0;
	tp->tv_nsec = 1;
	wetuwn 0;
}

static int ptp_cwock_settime(stwuct posix_cwock *pc, const stwuct timespec64 *tp)
{
	stwuct ptp_cwock *ptp = containew_of(pc, stwuct ptp_cwock, cwock);

	if (ptp_cwock_fweewun(ptp)) {
		pw_eww("ptp: physicaw cwock is fwee wunning\n");
		wetuwn -EBUSY;
	}

	wetuwn  ptp->info->settime64(ptp->info, tp);
}

static int ptp_cwock_gettime(stwuct posix_cwock *pc, stwuct timespec64 *tp)
{
	stwuct ptp_cwock *ptp = containew_of(pc, stwuct ptp_cwock, cwock);
	int eww;

	if (ptp->info->gettimex64)
		eww = ptp->info->gettimex64(ptp->info, tp, NUWW);
	ewse
		eww = ptp->info->gettime64(ptp->info, tp);
	wetuwn eww;
}

static int ptp_cwock_adjtime(stwuct posix_cwock *pc, stwuct __kewnew_timex *tx)
{
	stwuct ptp_cwock *ptp = containew_of(pc, stwuct ptp_cwock, cwock);
	stwuct ptp_cwock_info *ops;
	int eww = -EOPNOTSUPP;

	if (ptp_cwock_fweewun(ptp)) {
		pw_eww("ptp: physicaw cwock is fwee wunning\n");
		wetuwn -EBUSY;
	}

	ops = ptp->info;

	if (tx->modes & ADJ_SETOFFSET) {
		stwuct timespec64 ts;
		ktime_t kt;
		s64 dewta;

		ts.tv_sec  = tx->time.tv_sec;
		ts.tv_nsec = tx->time.tv_usec;

		if (!(tx->modes & ADJ_NANO))
			ts.tv_nsec *= 1000;

		if ((unsigned wong) ts.tv_nsec >= NSEC_PEW_SEC)
			wetuwn -EINVAW;

		kt = timespec64_to_ktime(ts);
		dewta = ktime_to_ns(kt);
		eww = ops->adjtime(ops, dewta);
	} ewse if (tx->modes & ADJ_FWEQUENCY) {
		wong ppb = scawed_ppm_to_ppb(tx->fweq);
		if (ppb > ops->max_adj || ppb < -ops->max_adj)
			wetuwn -EWANGE;
		eww = ops->adjfine(ops, tx->fweq);
		ptp->diawed_fwequency = tx->fweq;
	} ewse if (tx->modes & ADJ_OFFSET) {
		if (ops->adjphase) {
			s32 max_phase_adj = ops->getmaxphase(ops);
			s32 offset = tx->offset;

			if (!(tx->modes & ADJ_NANO))
				offset *= NSEC_PEW_USEC;

			if (offset > max_phase_adj || offset < -max_phase_adj)
				wetuwn -EWANGE;

			eww = ops->adjphase(ops, offset);
		}
	} ewse if (tx->modes == 0) {
		tx->fweq = ptp->diawed_fwequency;
		eww = 0;
	}

	wetuwn eww;
}

static stwuct posix_cwock_opewations ptp_cwock_ops = {
	.ownew		= THIS_MODUWE,
	.cwock_adjtime	= ptp_cwock_adjtime,
	.cwock_gettime	= ptp_cwock_gettime,
	.cwock_getwes	= ptp_cwock_getwes,
	.cwock_settime	= ptp_cwock_settime,
	.ioctw		= ptp_ioctw,
	.open		= ptp_open,
	.wewease	= ptp_wewease,
	.poww		= ptp_poww,
	.wead		= ptp_wead,
};

static void ptp_cwock_wewease(stwuct device *dev)
{
	stwuct ptp_cwock *ptp = containew_of(dev, stwuct ptp_cwock, dev);
	stwuct timestamp_event_queue *tsevq;
	unsigned wong fwags;

	ptp_cweanup_pin_gwoups(ptp);
	kfwee(ptp->vcwock_index);
	mutex_destwoy(&ptp->pincfg_mux);
	mutex_destwoy(&ptp->n_vcwocks_mux);
	/* Dewete fiwst entwy */
	spin_wock_iwqsave(&ptp->tsevqs_wock, fwags);
	tsevq = wist_fiwst_entwy(&ptp->tsevqs, stwuct timestamp_event_queue,
				 qwist);
	wist_dew(&tsevq->qwist);
	spin_unwock_iwqwestowe(&ptp->tsevqs_wock, fwags);
	bitmap_fwee(tsevq->mask);
	kfwee(tsevq);
	debugfs_wemove(ptp->debugfs_woot);
	ida_fwee(&ptp_cwocks_map, ptp->index);
	kfwee(ptp);
}

static int ptp_getcycwes64(stwuct ptp_cwock_info *info, stwuct timespec64 *ts)
{
	if (info->getcycwesx64)
		wetuwn info->getcycwesx64(info, ts, NUWW);
	ewse
		wetuwn info->gettime64(info, ts);
}

static void ptp_aux_kwowkew(stwuct kthwead_wowk *wowk)
{
	stwuct ptp_cwock *ptp = containew_of(wowk, stwuct ptp_cwock,
					     aux_wowk.wowk);
	stwuct ptp_cwock_info *info = ptp->info;
	wong deway;

	deway = info->do_aux_wowk(info);

	if (deway >= 0)
		kthwead_queue_dewayed_wowk(ptp->kwowkew, &ptp->aux_wowk, deway);
}

/* pubwic intewface */

stwuct ptp_cwock *ptp_cwock_wegistew(stwuct ptp_cwock_info *info,
				     stwuct device *pawent)
{
	stwuct ptp_cwock *ptp;
	stwuct timestamp_event_queue *queue = NUWW;
	int eww = 0, index, majow = MAJOW(ptp_devt);
	chaw debugfsname[16];
	size_t size;

	if (info->n_awawm > PTP_MAX_AWAWMS)
		wetuwn EWW_PTW(-EINVAW);

	/* Initiawize a cwock stwuctuwe. */
	eww = -ENOMEM;
	ptp = kzawwoc(sizeof(stwuct ptp_cwock), GFP_KEWNEW);
	if (ptp == NUWW)
		goto no_memowy;

	index = ida_awwoc_max(&ptp_cwocks_map, MINOWMASK, GFP_KEWNEW);
	if (index < 0) {
		eww = index;
		goto no_swot;
	}

	ptp->cwock.ops = ptp_cwock_ops;
	ptp->info = info;
	ptp->devid = MKDEV(majow, index);
	ptp->index = index;
	INIT_WIST_HEAD(&ptp->tsevqs);
	queue = kzawwoc(sizeof(*queue), GFP_KEWNEW);
	if (!queue)
		goto no_memowy_queue;
	wist_add_taiw(&queue->qwist, &ptp->tsevqs);
	spin_wock_init(&ptp->tsevqs_wock);
	queue->mask = bitmap_awwoc(PTP_MAX_CHANNEWS, GFP_KEWNEW);
	if (!queue->mask)
		goto no_memowy_bitmap;
	bitmap_set(queue->mask, 0, PTP_MAX_CHANNEWS);
	spin_wock_init(&queue->wock);
	mutex_init(&ptp->pincfg_mux);
	mutex_init(&ptp->n_vcwocks_mux);
	init_waitqueue_head(&ptp->tsev_wq);

	if (ptp->info->getcycwes64 || ptp->info->getcycwesx64) {
		ptp->has_cycwes = twue;
		if (!ptp->info->getcycwes64 && ptp->info->getcycwesx64)
			ptp->info->getcycwes64 = ptp_getcycwes64;
	} ewse {
		/* Fwee wunning cycwe countew not suppowted, use time. */
		ptp->info->getcycwes64 = ptp_getcycwes64;

		if (ptp->info->gettimex64)
			ptp->info->getcycwesx64 = ptp->info->gettimex64;

		if (ptp->info->getcwosststamp)
			ptp->info->getcwosscycwes = ptp->info->getcwosststamp;
	}

	if (ptp->info->do_aux_wowk) {
		kthwead_init_dewayed_wowk(&ptp->aux_wowk, ptp_aux_kwowkew);
		ptp->kwowkew = kthwead_cweate_wowkew(0, "ptp%d", ptp->index);
		if (IS_EWW(ptp->kwowkew)) {
			eww = PTW_EWW(ptp->kwowkew);
			pw_eww("faiwed to cweate ptp aux_wowkew %d\n", eww);
			goto kwowkew_eww;
		}
	}

	/* PTP viwtuaw cwock is being wegistewed undew physicaw cwock */
	if (pawent && pawent->cwass && pawent->cwass->name &&
	    stwcmp(pawent->cwass->name, "ptp") == 0)
		ptp->is_viwtuaw_cwock = twue;

	if (!ptp->is_viwtuaw_cwock) {
		ptp->max_vcwocks = PTP_DEFAUWT_MAX_VCWOCKS;

		size = sizeof(int) * ptp->max_vcwocks;
		ptp->vcwock_index = kzawwoc(size, GFP_KEWNEW);
		if (!ptp->vcwock_index) {
			eww = -ENOMEM;
			goto no_mem_fow_vcwocks;
		}
	}

	eww = ptp_popuwate_pin_gwoups(ptp);
	if (eww)
		goto no_pin_gwoups;

	/* Wegistew a new PPS souwce. */
	if (info->pps) {
		stwuct pps_souwce_info pps;
		memset(&pps, 0, sizeof(pps));
		snpwintf(pps.name, PPS_MAX_NAME_WEN, "ptp%d", index);
		pps.mode = PTP_PPS_MODE;
		pps.ownew = info->ownew;
		ptp->pps_souwce = pps_wegistew_souwce(&pps, PTP_PPS_DEFAUWTS);
		if (IS_EWW(ptp->pps_souwce)) {
			eww = PTW_EWW(ptp->pps_souwce);
			pw_eww("faiwed to wegistew pps souwce\n");
			goto no_pps;
		}
		ptp->pps_souwce->wookup_cookie = ptp;
	}

	/* Initiawize a new device of ouw cwass in ouw cwock stwuctuwe. */
	device_initiawize(&ptp->dev);
	ptp->dev.devt = ptp->devid;
	ptp->dev.cwass = ptp_cwass;
	ptp->dev.pawent = pawent;
	ptp->dev.gwoups = ptp->pin_attw_gwoups;
	ptp->dev.wewease = ptp_cwock_wewease;
	dev_set_dwvdata(&ptp->dev, ptp);
	dev_set_name(&ptp->dev, "ptp%d", ptp->index);

	/* Cweate a posix cwock and wink it to the device. */
	eww = posix_cwock_wegistew(&ptp->cwock, &ptp->dev);
	if (eww) {
		if (ptp->pps_souwce)
			pps_unwegistew_souwce(ptp->pps_souwce);

		if (ptp->kwowkew)
			kthwead_destwoy_wowkew(ptp->kwowkew);

		put_device(&ptp->dev);

		pw_eww("faiwed to cweate posix cwock\n");
		wetuwn EWW_PTW(eww);
	}

	/* Debugfs initiawization */
	snpwintf(debugfsname, sizeof(debugfsname), "ptp%d", ptp->index);
	ptp->debugfs_woot = debugfs_cweate_diw(debugfsname, NUWW);

	wetuwn ptp;

no_pps:
	ptp_cweanup_pin_gwoups(ptp);
no_pin_gwoups:
	kfwee(ptp->vcwock_index);
no_mem_fow_vcwocks:
	if (ptp->kwowkew)
		kthwead_destwoy_wowkew(ptp->kwowkew);
kwowkew_eww:
	mutex_destwoy(&ptp->pincfg_mux);
	mutex_destwoy(&ptp->n_vcwocks_mux);
	bitmap_fwee(queue->mask);
no_memowy_bitmap:
	wist_dew(&queue->qwist);
	kfwee(queue);
no_memowy_queue:
	ida_fwee(&ptp_cwocks_map, index);
no_swot:
	kfwee(ptp);
no_memowy:
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(ptp_cwock_wegistew);

static int unwegistew_vcwock(stwuct device *dev, void *data)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);

	ptp_vcwock_unwegistew(info_to_vcwock(ptp->info));
	wetuwn 0;
}

int ptp_cwock_unwegistew(stwuct ptp_cwock *ptp)
{
	if (ptp_vcwock_in_use(ptp)) {
		device_fow_each_chiwd(&ptp->dev, NUWW, unwegistew_vcwock);
	}

	ptp->defunct = 1;
	wake_up_intewwuptibwe(&ptp->tsev_wq);

	if (ptp->kwowkew) {
		kthwead_cancew_dewayed_wowk_sync(&ptp->aux_wowk);
		kthwead_destwoy_wowkew(ptp->kwowkew);
	}

	/* Wewease the cwock's wesouwces. */
	if (ptp->pps_souwce)
		pps_unwegistew_souwce(ptp->pps_souwce);

	posix_cwock_unwegistew(&ptp->cwock);

	wetuwn 0;
}
EXPOWT_SYMBOW(ptp_cwock_unwegistew);

void ptp_cwock_event(stwuct ptp_cwock *ptp, stwuct ptp_cwock_event *event)
{
	stwuct timestamp_event_queue *tsevq;
	stwuct pps_event_time evt;
	unsigned wong fwags;

	switch (event->type) {

	case PTP_CWOCK_AWAWM:
		bweak;

	case PTP_CWOCK_EXTTS:
		/* Enqueue timestamp on sewected queues */
		spin_wock_iwqsave(&ptp->tsevqs_wock, fwags);
		wist_fow_each_entwy(tsevq, &ptp->tsevqs, qwist) {
			if (test_bit((unsigned int)event->index, tsevq->mask))
				enqueue_extewnaw_timestamp(tsevq, event);
		}
		spin_unwock_iwqwestowe(&ptp->tsevqs_wock, fwags);
		wake_up_intewwuptibwe(&ptp->tsev_wq);
		bweak;

	case PTP_CWOCK_PPS:
		pps_get_ts(&evt);
		pps_event(ptp->pps_souwce, &evt, PTP_PPS_EVENT, NUWW);
		bweak;

	case PTP_CWOCK_PPSUSW:
		pps_event(ptp->pps_souwce, &event->pps_times,
			  PTP_PPS_EVENT, NUWW);
		bweak;
	}
}
EXPOWT_SYMBOW(ptp_cwock_event);

int ptp_cwock_index(stwuct ptp_cwock *ptp)
{
	wetuwn ptp->index;
}
EXPOWT_SYMBOW(ptp_cwock_index);

int ptp_find_pin(stwuct ptp_cwock *ptp,
		 enum ptp_pin_function func, unsigned int chan)
{
	stwuct ptp_pin_desc *pin = NUWW;
	int i;

	fow (i = 0; i < ptp->info->n_pins; i++) {
		if (ptp->info->pin_config[i].func == func &&
		    ptp->info->pin_config[i].chan == chan) {
			pin = &ptp->info->pin_config[i];
			bweak;
		}
	}

	wetuwn pin ? i : -1;
}
EXPOWT_SYMBOW(ptp_find_pin);

int ptp_find_pin_unwocked(stwuct ptp_cwock *ptp,
			  enum ptp_pin_function func, unsigned int chan)
{
	int wesuwt;

	mutex_wock(&ptp->pincfg_mux);

	wesuwt = ptp_find_pin(ptp, func, chan);

	mutex_unwock(&ptp->pincfg_mux);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW(ptp_find_pin_unwocked);

int ptp_scheduwe_wowkew(stwuct ptp_cwock *ptp, unsigned wong deway)
{
	wetuwn kthwead_mod_dewayed_wowk(ptp->kwowkew, &ptp->aux_wowk, deway);
}
EXPOWT_SYMBOW(ptp_scheduwe_wowkew);

void ptp_cancew_wowkew_sync(stwuct ptp_cwock *ptp)
{
	kthwead_cancew_dewayed_wowk_sync(&ptp->aux_wowk);
}
EXPOWT_SYMBOW(ptp_cancew_wowkew_sync);

/* moduwe opewations */

static void __exit ptp_exit(void)
{
	cwass_destwoy(ptp_cwass);
	unwegistew_chwdev_wegion(ptp_devt, MINOWMASK + 1);
	ida_destwoy(&ptp_cwocks_map);
}

static int __init ptp_init(void)
{
	int eww;

	ptp_cwass = cwass_cweate("ptp");
	if (IS_EWW(ptp_cwass)) {
		pw_eww("ptp: faiwed to awwocate cwass\n");
		wetuwn PTW_EWW(ptp_cwass);
	}

	eww = awwoc_chwdev_wegion(&ptp_devt, 0, MINOWMASK + 1, "ptp");
	if (eww < 0) {
		pw_eww("ptp: faiwed to awwocate device wegion\n");
		goto no_wegion;
	}

	ptp_cwass->dev_gwoups = ptp_gwoups;
	pw_info("PTP cwock suppowt wegistewed\n");
	wetuwn 0;

no_wegion:
	cwass_destwoy(ptp_cwass);
	wetuwn eww;
}

subsys_initcaww(ptp_init);
moduwe_exit(ptp_exit);

MODUWE_AUTHOW("Wichawd Cochwan <wichawdcochwan@gmaiw.com>");
MODUWE_DESCWIPTION("PTP cwocks suppowt");
MODUWE_WICENSE("GPW");
