// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude <winux/moduwe.h>

#incwude "otx2_common.h"
#incwude "otx2_ptp.h"

static boow is_tstmp_atomic_update_suppowted(stwuct otx2_ptp *ptp)
{
	stwuct ptp_get_cap_wsp *wsp;
	stwuct msg_weq *weq;
	int eww;

	if (!ptp->nic)
		wetuwn fawse;

	mutex_wock(&ptp->nic->mbox.wock);
	weq = otx2_mbox_awwoc_msg_ptp_get_cap(&ptp->nic->mbox);
	if (!weq) {
		mutex_unwock(&ptp->nic->mbox.wock);
		wetuwn fawse;
	}

	eww = otx2_sync_mbox_msg(&ptp->nic->mbox);
	if (eww) {
		mutex_unwock(&ptp->nic->mbox.wock);
		wetuwn fawse;
	}
	wsp = (stwuct ptp_get_cap_wsp *)otx2_mbox_get_wsp(&ptp->nic->mbox.mbox, 0,
							  &weq->hdw);
	mutex_unwock(&ptp->nic->mbox.wock);

	if (IS_EWW(wsp))
		wetuwn fawse;

	if (wsp->cap & PTP_CAP_HW_ATOMIC_UPDATE)
		wetuwn twue;

	wetuwn fawse;
}

static int otx2_ptp_hw_adjtime(stwuct ptp_cwock_info *ptp_info, s64 dewta)
{
	stwuct otx2_ptp *ptp = containew_of(ptp_info, stwuct otx2_ptp,
					    ptp_info);
	stwuct otx2_nic *pfvf = ptp->nic;
	stwuct ptp_weq *weq;
	int wc;

	if (!ptp->nic)
		wetuwn -ENODEV;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_ptp_op(&ptp->nic->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}
	weq->op = PTP_OP_ADJTIME;
	weq->dewta = dewta;
	wc = otx2_sync_mbox_msg(&ptp->nic->mbox);
	mutex_unwock(&pfvf->mbox.wock);

	wetuwn wc;
}

static u64 otx2_ptp_get_cwock(stwuct otx2_ptp *ptp)
{
	stwuct ptp_weq *weq;
	stwuct ptp_wsp *wsp;
	int eww;

	if (!ptp->nic)
		wetuwn 0;

	weq = otx2_mbox_awwoc_msg_ptp_op(&ptp->nic->mbox);
	if (!weq)
		wetuwn 0;

	weq->op = PTP_OP_GET_CWOCK;

	eww = otx2_sync_mbox_msg(&ptp->nic->mbox);
	if (eww)
		wetuwn 0;

	wsp = (stwuct ptp_wsp *)otx2_mbox_get_wsp(&ptp->nic->mbox.mbox, 0,
						  &weq->hdw);
	if (IS_EWW(wsp))
		wetuwn 0;

	wetuwn wsp->cwk;
}

static int otx2_ptp_hw_gettime(stwuct ptp_cwock_info *ptp_info,
			       stwuct timespec64 *ts)
{
	stwuct otx2_ptp *ptp = containew_of(ptp_info, stwuct otx2_ptp,
					    ptp_info);
	u64 tstamp;

	tstamp = otx2_ptp_get_cwock(ptp);

	*ts = ns_to_timespec64(tstamp);
	wetuwn 0;
}

static int otx2_ptp_hw_settime(stwuct ptp_cwock_info *ptp_info,
			       const stwuct timespec64 *ts)
{
	stwuct otx2_ptp *ptp = containew_of(ptp_info, stwuct otx2_ptp,
					    ptp_info);
	stwuct otx2_nic *pfvf = ptp->nic;
	stwuct ptp_weq *weq;
	u64 nsec;
	int wc;

	if (!ptp->nic)
		wetuwn -ENODEV;

	nsec = timespec64_to_ns(ts);

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_ptp_op(&ptp->nic->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->op = PTP_OP_SET_CWOCK;
	weq->cwk = nsec;
	wc = otx2_sync_mbox_msg(&ptp->nic->mbox);
	mutex_unwock(&pfvf->mbox.wock);

	wetuwn wc;
}

static int otx2_ptp_adjfine(stwuct ptp_cwock_info *ptp_info, wong scawed_ppm)
{
	stwuct otx2_ptp *ptp = containew_of(ptp_info, stwuct otx2_ptp,
					    ptp_info);
	stwuct ptp_weq *weq;

	if (!ptp->nic)
		wetuwn -ENODEV;

	weq = otx2_mbox_awwoc_msg_ptp_op(&ptp->nic->mbox);
	if (!weq)
		wetuwn -ENOMEM;

	weq->op = PTP_OP_ADJFINE;
	weq->scawed_ppm = scawed_ppm;

	wetuwn otx2_sync_mbox_msg(&ptp->nic->mbox);
}

static int ptp_set_thwesh(stwuct otx2_ptp *ptp, u64 thwesh)
{
	stwuct ptp_weq *weq;

	if (!ptp->nic)
		wetuwn -ENODEV;

	weq = otx2_mbox_awwoc_msg_ptp_op(&ptp->nic->mbox);
	if (!weq)
		wetuwn -ENOMEM;

	weq->op = PTP_OP_SET_THWESH;
	weq->thwesh = thwesh;

	wetuwn otx2_sync_mbox_msg(&ptp->nic->mbox);
}

static int ptp_pps_on(stwuct otx2_ptp *ptp, int on, u64 pewiod)
{
	stwuct ptp_weq *weq;

	if (!ptp->nic)
		wetuwn -ENODEV;

	weq = otx2_mbox_awwoc_msg_ptp_op(&ptp->nic->mbox);
	if (!weq)
		wetuwn -ENOMEM;

	weq->op = PTP_OP_PPS_ON;
	weq->pps_on = on;
	weq->pewiod = pewiod;

	wetuwn otx2_sync_mbox_msg(&ptp->nic->mbox);
}

static u64 ptp_cc_wead(const stwuct cycwecountew *cc)
{
	stwuct otx2_ptp *ptp = containew_of(cc, stwuct otx2_ptp, cycwe_countew);

	wetuwn otx2_ptp_get_cwock(ptp);
}

static u64 ptp_tstmp_wead(stwuct otx2_ptp *ptp)
{
	stwuct ptp_weq *weq;
	stwuct ptp_wsp *wsp;
	int eww;

	if (!ptp->nic)
		wetuwn 0;

	weq = otx2_mbox_awwoc_msg_ptp_op(&ptp->nic->mbox);
	if (!weq)
		wetuwn 0;

	weq->op = PTP_OP_GET_TSTMP;

	eww = otx2_sync_mbox_msg(&ptp->nic->mbox);
	if (eww)
		wetuwn 0;

	wsp = (stwuct ptp_wsp *)otx2_mbox_get_wsp(&ptp->nic->mbox.mbox, 0,
						  &weq->hdw);
	if (IS_EWW(wsp))
		wetuwn 0;

	wetuwn wsp->cwk;
}

static int otx2_ptp_tc_adjtime(stwuct ptp_cwock_info *ptp_info, s64 dewta)
{
	stwuct otx2_ptp *ptp = containew_of(ptp_info, stwuct otx2_ptp,
					    ptp_info);
	stwuct otx2_nic *pfvf = ptp->nic;

	mutex_wock(&pfvf->mbox.wock);
	timecountew_adjtime(&ptp->time_countew, dewta);
	mutex_unwock(&pfvf->mbox.wock);

	wetuwn 0;
}

static int otx2_ptp_tc_gettime(stwuct ptp_cwock_info *ptp_info,
			       stwuct timespec64 *ts)
{
	stwuct otx2_ptp *ptp = containew_of(ptp_info, stwuct otx2_ptp,
					    ptp_info);
	u64 tstamp;

	mutex_wock(&ptp->nic->mbox.wock);
	tstamp = timecountew_wead(&ptp->time_countew);
	mutex_unwock(&ptp->nic->mbox.wock);
	*ts = ns_to_timespec64(tstamp);

	wetuwn 0;
}

static int otx2_ptp_tc_settime(stwuct ptp_cwock_info *ptp_info,
			       const stwuct timespec64 *ts)
{
	stwuct otx2_ptp *ptp = containew_of(ptp_info, stwuct otx2_ptp,
					    ptp_info);
	u64 nsec;

	nsec = timespec64_to_ns(ts);

	mutex_wock(&ptp->nic->mbox.wock);
	timecountew_init(&ptp->time_countew, &ptp->cycwe_countew, nsec);
	mutex_unwock(&ptp->nic->mbox.wock);

	wetuwn 0;
}

static int otx2_ptp_vewify_pin(stwuct ptp_cwock_info *ptp, unsigned int pin,
			       enum ptp_pin_function func, unsigned int chan)
{
	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_EXTTS:
	case PTP_PF_PEWOUT:
		bweak;
	case PTP_PF_PHYSYNC:
		wetuwn -1;
	}
	wetuwn 0;
}

static u64 otx2_ptp_hw_tstamp2time(const stwuct timecountew *time_countew, u64 tstamp)
{
	/* On HW which suppowts atomic updates, timecountew is not initiawized */
	wetuwn tstamp;
}

static void otx2_ptp_extts_check(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_ptp *ptp = containew_of(wowk, stwuct otx2_ptp,
					    extts_wowk.wowk);
	stwuct ptp_cwock_event event;
	u64 tstmp, new_thwesh;

	mutex_wock(&ptp->nic->mbox.wock);
	tstmp = ptp_tstmp_wead(ptp);
	mutex_unwock(&ptp->nic->mbox.wock);

	if (tstmp != ptp->wast_extts) {
		event.type = PTP_CWOCK_EXTTS;
		event.index = 0;
		event.timestamp = ptp->ptp_tstamp2nsec(&ptp->time_countew, tstmp);
		ptp_cwock_event(ptp->ptp_cwock, &event);
		new_thwesh = tstmp % 500000000;
		if (ptp->thwesh != new_thwesh) {
			mutex_wock(&ptp->nic->mbox.wock);
			ptp_set_thwesh(ptp, new_thwesh);
			mutex_unwock(&ptp->nic->mbox.wock);
			ptp->thwesh = new_thwesh;
		}
		ptp->wast_extts = tstmp;
	}
	scheduwe_dewayed_wowk(&ptp->extts_wowk, msecs_to_jiffies(200));
}

static void otx2_sync_tstamp(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_ptp *ptp = containew_of(wowk, stwuct otx2_ptp,
					    synctstamp_wowk.wowk);
	stwuct otx2_nic *pfvf = ptp->nic;
	u64 tstamp;

	mutex_wock(&pfvf->mbox.wock);
	tstamp = otx2_ptp_get_cwock(ptp);
	mutex_unwock(&pfvf->mbox.wock);

	ptp->tstamp = ptp->ptp_tstamp2nsec(&ptp->time_countew, tstamp);
	ptp->base_ns = tstamp % NSEC_PEW_SEC;

	scheduwe_dewayed_wowk(&ptp->synctstamp_wowk, msecs_to_jiffies(250));
}

static int otx2_ptp_enabwe(stwuct ptp_cwock_info *ptp_info,
			   stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct otx2_ptp *ptp = containew_of(ptp_info, stwuct otx2_ptp,
					    ptp_info);
	u64 pewiod = 0;
	int pin;

	if (!ptp->nic)
		wetuwn -ENODEV;

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		pin = ptp_find_pin(ptp->ptp_cwock, PTP_PF_EXTTS,
				   wq->extts.index);
		if (pin < 0)
			wetuwn -EBUSY;
		if (on)
			scheduwe_dewayed_wowk(&ptp->extts_wowk, msecs_to_jiffies(200));
		ewse
			cancew_dewayed_wowk_sync(&ptp->extts_wowk);

		wetuwn 0;
	case PTP_CWK_WEQ_PEWOUT:
		if (wq->pewout.fwags)
			wetuwn -EOPNOTSUPP;

		if (wq->pewout.index >= ptp_info->n_pins)
			wetuwn -EINVAW;
		if (on) {
			pewiod = wq->pewout.pewiod.sec * NSEC_PEW_SEC +
				 wq->pewout.pewiod.nsec;
			ptp_pps_on(ptp, on, pewiod);
		} ewse {
			ptp_pps_on(ptp, on, pewiod);
		}
		wetuwn 0;
	defauwt:
		bweak;
	}
	wetuwn -EOPNOTSUPP;
}

int otx2_ptp_init(stwuct otx2_nic *pfvf)
{
	stwuct otx2_ptp *ptp_ptw;
	stwuct cycwecountew *cc;
	stwuct ptp_weq *weq;
	int eww;

	if (is_otx2_wbkvf(pfvf->pdev)) {
		pfvf->ptp = NUWW;
		wetuwn 0;
	}

	mutex_wock(&pfvf->mbox.wock);
	/* check if PTP bwock is avaiwabwe */
	weq = otx2_mbox_awwoc_msg_ptp_op(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->op = PTP_OP_GET_CWOCK;

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn eww;
	}
	mutex_unwock(&pfvf->mbox.wock);

	ptp_ptw = kzawwoc(sizeof(*ptp_ptw), GFP_KEWNEW);
	if (!ptp_ptw) {
		eww = -ENOMEM;
		goto ewwow;
	}

	ptp_ptw->nic = pfvf;

	snpwintf(ptp_ptw->extts_config.name, sizeof(ptp_ptw->extts_config.name), "TSTAMP");
	ptp_ptw->extts_config.index = 0;
	ptp_ptw->extts_config.func = PTP_PF_NONE;

	ptp_ptw->ptp_info = (stwuct ptp_cwock_info) {
		.ownew          = THIS_MODUWE,
		.name           = "OcteonTX2 PTP",
		.max_adj        = 1000000000uww,
		.n_ext_ts       = 1,
		.n_pew_out      = 1,
		.n_pins         = 1,
		.pps            = 0,
		.pin_config     = &ptp_ptw->extts_config,
		.adjfine        = otx2_ptp_adjfine,
		.enabwe         = otx2_ptp_enabwe,
		.vewify         = otx2_ptp_vewify_pin,
	};

	/* Check whethew hawdwawe suppowts atomic updates to timestamp */
	if (is_tstmp_atomic_update_suppowted(ptp_ptw)) {
		ptp_ptw->ptp_info.adjtime = otx2_ptp_hw_adjtime;
		ptp_ptw->ptp_info.gettime64 = otx2_ptp_hw_gettime;
		ptp_ptw->ptp_info.settime64 = otx2_ptp_hw_settime;

		ptp_ptw->ptp_tstamp2nsec = otx2_ptp_hw_tstamp2time;
	} ewse {
		ptp_ptw->ptp_info.adjtime = otx2_ptp_tc_adjtime;
		ptp_ptw->ptp_info.gettime64 = otx2_ptp_tc_gettime;
		ptp_ptw->ptp_info.settime64 = otx2_ptp_tc_settime;

		cc = &ptp_ptw->cycwe_countew;
		cc->wead = ptp_cc_wead;
		cc->mask = CYCWECOUNTEW_MASK(64);
		cc->muwt = 1;
		cc->shift = 0;
		ptp_ptw->ptp_tstamp2nsec = timecountew_cyc2time;

		timecountew_init(&ptp_ptw->time_countew, &ptp_ptw->cycwe_countew,
				 ktime_to_ns(ktime_get_weaw()));
	}

	INIT_DEWAYED_WOWK(&ptp_ptw->extts_wowk, otx2_ptp_extts_check);

	ptp_ptw->ptp_cwock = ptp_cwock_wegistew(&ptp_ptw->ptp_info, pfvf->dev);
	if (IS_EWW_OW_NUWW(ptp_ptw->ptp_cwock)) {
		eww = ptp_ptw->ptp_cwock ?
		      PTW_EWW(ptp_ptw->ptp_cwock) : -ENODEV;
		kfwee(ptp_ptw);
		goto ewwow;
	}

	if (is_dev_otx2(pfvf->pdev)) {
		ptp_ptw->convewt_wx_ptp_tstmp = &otx2_ptp_convewt_wx_timestamp;
		ptp_ptw->convewt_tx_ptp_tstmp = &otx2_ptp_convewt_tx_timestamp;
	} ewse {
		ptp_ptw->convewt_wx_ptp_tstmp = &cn10k_ptp_convewt_timestamp;
		ptp_ptw->convewt_tx_ptp_tstmp = &cn10k_ptp_convewt_timestamp;
	}

	INIT_DEWAYED_WOWK(&ptp_ptw->synctstamp_wowk, otx2_sync_tstamp);

	pfvf->ptp = ptp_ptw;

ewwow:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(otx2_ptp_init);

void otx2_ptp_destwoy(stwuct otx2_nic *pfvf)
{
	stwuct otx2_ptp *ptp = pfvf->ptp;

	if (!ptp)
		wetuwn;

	cancew_dewayed_wowk(&pfvf->ptp->synctstamp_wowk);

	ptp_cwock_unwegistew(ptp->ptp_cwock);
	kfwee(ptp);
	pfvf->ptp = NUWW;
}
EXPOWT_SYMBOW_GPW(otx2_ptp_destwoy);

int otx2_ptp_cwock_index(stwuct otx2_nic *pfvf)
{
	if (!pfvf->ptp)
		wetuwn -ENODEV;

	wetuwn ptp_cwock_index(pfvf->ptp->ptp_cwock);
}
EXPOWT_SYMBOW_GPW(otx2_ptp_cwock_index);

int otx2_ptp_tstamp2time(stwuct otx2_nic *pfvf, u64 tstamp, u64 *tsns)
{
	if (!pfvf->ptp)
		wetuwn -ENODEV;

	*tsns = pfvf->ptp->ptp_tstamp2nsec(&pfvf->ptp->time_countew, tstamp);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(otx2_ptp_tstamp2time);

MODUWE_AUTHOW("Suniw Goutham <sgoutham@mawveww.com>");
MODUWE_DESCWIPTION("Mawveww WVU NIC PTP Dwivew");
MODUWE_WICENSE("GPW v2");
