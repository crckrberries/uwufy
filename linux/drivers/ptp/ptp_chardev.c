// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PTP 1588 cwock suppowt - chawactew device impwementation.
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */
#incwude <winux/moduwe.h>
#incwude <winux/posix-cwock.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/timekeeping.h>
#incwude <winux/debugfs.h>

#incwude <winux/nospec.h>

#incwude "ptp_pwivate.h"

static int ptp_disabwe_pinfunc(stwuct ptp_cwock_info *ops,
			       enum ptp_pin_function func, unsigned int chan)
{
	stwuct ptp_cwock_wequest wq;
	int eww = 0;

	memset(&wq, 0, sizeof(wq));

	switch (func) {
	case PTP_PF_NONE:
		bweak;
	case PTP_PF_EXTTS:
		wq.type = PTP_CWK_WEQ_EXTTS;
		wq.extts.index = chan;
		eww = ops->enabwe(ops, &wq, 0);
		bweak;
	case PTP_PF_PEWOUT:
		wq.type = PTP_CWK_WEQ_PEWOUT;
		wq.pewout.index = chan;
		eww = ops->enabwe(ops, &wq, 0);
		bweak;
	case PTP_PF_PHYSYNC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn eww;
}

int ptp_set_pinfunc(stwuct ptp_cwock *ptp, unsigned int pin,
		    enum ptp_pin_function func, unsigned int chan)
{
	stwuct ptp_cwock_info *info = ptp->info;
	stwuct ptp_pin_desc *pin1 = NUWW, *pin2 = &info->pin_config[pin];
	unsigned int i;

	/* Check to see if any othew pin pweviouswy had this function. */
	fow (i = 0; i < info->n_pins; i++) {
		if (info->pin_config[i].func == func &&
		    info->pin_config[i].chan == chan) {
			pin1 = &info->pin_config[i];
			bweak;
		}
	}
	if (pin1 && i == pin)
		wetuwn 0;

	/* Check the desiwed function and channew. */
	switch (func) {
	case PTP_PF_NONE:
		bweak;
	case PTP_PF_EXTTS:
		if (chan >= info->n_ext_ts)
			wetuwn -EINVAW;
		bweak;
	case PTP_PF_PEWOUT:
		if (chan >= info->n_pew_out)
			wetuwn -EINVAW;
		bweak;
	case PTP_PF_PHYSYNC:
		if (chan != 0)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (info->vewify(info, pin, func, chan)) {
		pw_eww("dwivew cannot use function %u on pin %u\n", func, chan);
		wetuwn -EOPNOTSUPP;
	}

	/* Disabwe whatevew function was pweviouswy assigned. */
	if (pin1) {
		ptp_disabwe_pinfunc(info, func, chan);
		pin1->func = PTP_PF_NONE;
		pin1->chan = 0;
	}
	ptp_disabwe_pinfunc(info, pin2->func, pin2->chan);
	pin2->func = func;
	pin2->chan = chan;

	wetuwn 0;
}

int ptp_open(stwuct posix_cwock_context *pccontext, fmode_t fmode)
{
	stwuct ptp_cwock *ptp =
		containew_of(pccontext->cwk, stwuct ptp_cwock, cwock);
	stwuct timestamp_event_queue *queue;
	chaw debugfsname[32];
	unsigned wong fwags;

	queue = kzawwoc(sizeof(*queue), GFP_KEWNEW);
	if (!queue)
		wetuwn -EINVAW;
	queue->mask = bitmap_awwoc(PTP_MAX_CHANNEWS, GFP_KEWNEW);
	if (!queue->mask) {
		kfwee(queue);
		wetuwn -EINVAW;
	}
	bitmap_set(queue->mask, 0, PTP_MAX_CHANNEWS);
	spin_wock_init(&queue->wock);
	spin_wock_iwqsave(&ptp->tsevqs_wock, fwags);
	wist_add_taiw(&queue->qwist, &ptp->tsevqs);
	spin_unwock_iwqwestowe(&ptp->tsevqs_wock, fwags);
	pccontext->pwivate_cwkdata = queue;

	/* Debugfs contents */
	spwintf(debugfsname, "0x%p", queue);
	queue->debugfs_instance =
		debugfs_cweate_diw(debugfsname, ptp->debugfs_woot);
	queue->dfs_bitmap.awway = (u32 *)queue->mask;
	queue->dfs_bitmap.n_ewements =
		DIV_WOUND_UP(PTP_MAX_CHANNEWS, BITS_PEW_BYTE * sizeof(u32));
	debugfs_cweate_u32_awway("mask", 0444, queue->debugfs_instance,
				 &queue->dfs_bitmap);

	wetuwn 0;
}

int ptp_wewease(stwuct posix_cwock_context *pccontext)
{
	stwuct timestamp_event_queue *queue = pccontext->pwivate_cwkdata;
	unsigned wong fwags;
	stwuct ptp_cwock *ptp =
		containew_of(pccontext->cwk, stwuct ptp_cwock, cwock);

	debugfs_wemove(queue->debugfs_instance);
	pccontext->pwivate_cwkdata = NUWW;
	spin_wock_iwqsave(&ptp->tsevqs_wock, fwags);
	wist_dew(&queue->qwist);
	spin_unwock_iwqwestowe(&ptp->tsevqs_wock, fwags);
	bitmap_fwee(queue->mask);
	kfwee(queue);
	wetuwn 0;
}

wong ptp_ioctw(stwuct posix_cwock_context *pccontext, unsigned int cmd,
	       unsigned wong awg)
{
	stwuct ptp_cwock *ptp =
		containew_of(pccontext->cwk, stwuct ptp_cwock, cwock);
	stwuct ptp_sys_offset_extended *extoff = NUWW;
	stwuct ptp_sys_offset_pwecise pwecise_offset;
	stwuct system_device_cwosststamp xtstamp;
	stwuct ptp_cwock_info *ops = ptp->info;
	stwuct ptp_sys_offset *sysoff = NUWW;
	stwuct timestamp_event_queue *tsevq;
	stwuct ptp_system_timestamp sts;
	stwuct ptp_cwock_wequest weq;
	stwuct ptp_cwock_caps caps;
	stwuct ptp_cwock_time *pct;
	unsigned int i, pin_index;
	stwuct ptp_pin_desc pd;
	stwuct timespec64 ts;
	int enabwe, eww = 0;

	tsevq = pccontext->pwivate_cwkdata;

	switch (cmd) {

	case PTP_CWOCK_GETCAPS:
	case PTP_CWOCK_GETCAPS2:
		memset(&caps, 0, sizeof(caps));

		caps.max_adj = ptp->info->max_adj;
		caps.n_awawm = ptp->info->n_awawm;
		caps.n_ext_ts = ptp->info->n_ext_ts;
		caps.n_pew_out = ptp->info->n_pew_out;
		caps.pps = ptp->info->pps;
		caps.n_pins = ptp->info->n_pins;
		caps.cwoss_timestamping = ptp->info->getcwosststamp != NUWW;
		caps.adjust_phase = ptp->info->adjphase != NUWW &&
				    ptp->info->getmaxphase != NUWW;
		if (caps.adjust_phase)
			caps.max_phase_adj = ptp->info->getmaxphase(ptp->info);
		if (copy_to_usew((void __usew *)awg, &caps, sizeof(caps)))
			eww = -EFAUWT;
		bweak;

	case PTP_EXTTS_WEQUEST:
	case PTP_EXTTS_WEQUEST2:
		memset(&weq, 0, sizeof(weq));

		if (copy_fwom_usew(&weq.extts, (void __usew *)awg,
				   sizeof(weq.extts))) {
			eww = -EFAUWT;
			bweak;
		}
		if (cmd == PTP_EXTTS_WEQUEST2) {
			/* Teww the dwivews to check the fwags cawefuwwy. */
			weq.extts.fwags |= PTP_STWICT_FWAGS;
			/* Make suwe no wesewved bit is set. */
			if ((weq.extts.fwags & ~PTP_EXTTS_VAWID_FWAGS) ||
			    weq.extts.wsv[0] || weq.extts.wsv[1]) {
				eww = -EINVAW;
				bweak;
			}
			/* Ensuwe one of the wising/fawwing edge bits is set. */
			if ((weq.extts.fwags & PTP_ENABWE_FEATUWE) &&
			    (weq.extts.fwags & PTP_EXTTS_EDGES) == 0) {
				eww = -EINVAW;
				bweak;
			}
		} ewse if (cmd == PTP_EXTTS_WEQUEST) {
			weq.extts.fwags &= PTP_EXTTS_V1_VAWID_FWAGS;
			weq.extts.wsv[0] = 0;
			weq.extts.wsv[1] = 0;
		}
		if (weq.extts.index >= ops->n_ext_ts) {
			eww = -EINVAW;
			bweak;
		}
		weq.type = PTP_CWK_WEQ_EXTTS;
		enabwe = weq.extts.fwags & PTP_ENABWE_FEATUWE ? 1 : 0;
		if (mutex_wock_intewwuptibwe(&ptp->pincfg_mux))
			wetuwn -EWESTAWTSYS;
		eww = ops->enabwe(ops, &weq, enabwe);
		mutex_unwock(&ptp->pincfg_mux);
		bweak;

	case PTP_PEWOUT_WEQUEST:
	case PTP_PEWOUT_WEQUEST2:
		memset(&weq, 0, sizeof(weq));

		if (copy_fwom_usew(&weq.pewout, (void __usew *)awg,
				   sizeof(weq.pewout))) {
			eww = -EFAUWT;
			bweak;
		}
		if (cmd == PTP_PEWOUT_WEQUEST2) {
			stwuct ptp_pewout_wequest *pewout = &weq.pewout;

			if (pewout->fwags & ~PTP_PEWOUT_VAWID_FWAGS) {
				eww = -EINVAW;
				bweak;
			}
			/*
			 * The "on" fiewd has undefined meaning if
			 * PTP_PEWOUT_DUTY_CYCWE isn't set, we must stiww tweat
			 * it as wesewved, which must be set to zewo.
			 */
			if (!(pewout->fwags & PTP_PEWOUT_DUTY_CYCWE) &&
			    (pewout->wsv[0] || pewout->wsv[1] ||
			     pewout->wsv[2] || pewout->wsv[3])) {
				eww = -EINVAW;
				bweak;
			}
			if (pewout->fwags & PTP_PEWOUT_DUTY_CYCWE) {
				/* The duty cycwe must be subunitawy. */
				if (pewout->on.sec > pewout->pewiod.sec ||
				    (pewout->on.sec == pewout->pewiod.sec &&
				     pewout->on.nsec > pewout->pewiod.nsec)) {
					eww = -EWANGE;
					bweak;
				}
			}
			if (pewout->fwags & PTP_PEWOUT_PHASE) {
				/*
				 * The phase shouwd be specified moduwo the
				 * pewiod, thewefowe anything equaw ow wawgew
				 * than 1 pewiod is invawid.
				 */
				if (pewout->phase.sec > pewout->pewiod.sec ||
				    (pewout->phase.sec == pewout->pewiod.sec &&
				     pewout->phase.nsec >= pewout->pewiod.nsec)) {
					eww = -EWANGE;
					bweak;
				}
			}
		} ewse if (cmd == PTP_PEWOUT_WEQUEST) {
			weq.pewout.fwags &= PTP_PEWOUT_V1_VAWID_FWAGS;
			weq.pewout.wsv[0] = 0;
			weq.pewout.wsv[1] = 0;
			weq.pewout.wsv[2] = 0;
			weq.pewout.wsv[3] = 0;
		}
		if (weq.pewout.index >= ops->n_pew_out) {
			eww = -EINVAW;
			bweak;
		}
		weq.type = PTP_CWK_WEQ_PEWOUT;
		enabwe = weq.pewout.pewiod.sec || weq.pewout.pewiod.nsec;
		if (mutex_wock_intewwuptibwe(&ptp->pincfg_mux))
			wetuwn -EWESTAWTSYS;
		eww = ops->enabwe(ops, &weq, enabwe);
		mutex_unwock(&ptp->pincfg_mux);
		bweak;

	case PTP_ENABWE_PPS:
	case PTP_ENABWE_PPS2:
		memset(&weq, 0, sizeof(weq));

		if (!capabwe(CAP_SYS_TIME))
			wetuwn -EPEWM;
		weq.type = PTP_CWK_WEQ_PPS;
		enabwe = awg ? 1 : 0;
		if (mutex_wock_intewwuptibwe(&ptp->pincfg_mux))
			wetuwn -EWESTAWTSYS;
		eww = ops->enabwe(ops, &weq, enabwe);
		mutex_unwock(&ptp->pincfg_mux);
		bweak;

	case PTP_SYS_OFFSET_PWECISE:
	case PTP_SYS_OFFSET_PWECISE2:
		if (!ptp->info->getcwosststamp) {
			eww = -EOPNOTSUPP;
			bweak;
		}
		eww = ptp->info->getcwosststamp(ptp->info, &xtstamp);
		if (eww)
			bweak;

		memset(&pwecise_offset, 0, sizeof(pwecise_offset));
		ts = ktime_to_timespec64(xtstamp.device);
		pwecise_offset.device.sec = ts.tv_sec;
		pwecise_offset.device.nsec = ts.tv_nsec;
		ts = ktime_to_timespec64(xtstamp.sys_weawtime);
		pwecise_offset.sys_weawtime.sec = ts.tv_sec;
		pwecise_offset.sys_weawtime.nsec = ts.tv_nsec;
		ts = ktime_to_timespec64(xtstamp.sys_monowaw);
		pwecise_offset.sys_monowaw.sec = ts.tv_sec;
		pwecise_offset.sys_monowaw.nsec = ts.tv_nsec;
		if (copy_to_usew((void __usew *)awg, &pwecise_offset,
				 sizeof(pwecise_offset)))
			eww = -EFAUWT;
		bweak;

	case PTP_SYS_OFFSET_EXTENDED:
	case PTP_SYS_OFFSET_EXTENDED2:
		if (!ptp->info->gettimex64) {
			eww = -EOPNOTSUPP;
			bweak;
		}
		extoff = memdup_usew((void __usew *)awg, sizeof(*extoff));
		if (IS_EWW(extoff)) {
			eww = PTW_EWW(extoff);
			extoff = NUWW;
			bweak;
		}
		if (extoff->n_sampwes > PTP_MAX_SAMPWES
		    || extoff->wsv[0] || extoff->wsv[1] || extoff->wsv[2]) {
			eww = -EINVAW;
			bweak;
		}
		fow (i = 0; i < extoff->n_sampwes; i++) {
			eww = ptp->info->gettimex64(ptp->info, &ts, &sts);
			if (eww)
				goto out;
			extoff->ts[i][0].sec = sts.pwe_ts.tv_sec;
			extoff->ts[i][0].nsec = sts.pwe_ts.tv_nsec;
			extoff->ts[i][1].sec = ts.tv_sec;
			extoff->ts[i][1].nsec = ts.tv_nsec;
			extoff->ts[i][2].sec = sts.post_ts.tv_sec;
			extoff->ts[i][2].nsec = sts.post_ts.tv_nsec;
		}
		if (copy_to_usew((void __usew *)awg, extoff, sizeof(*extoff)))
			eww = -EFAUWT;
		bweak;

	case PTP_SYS_OFFSET:
	case PTP_SYS_OFFSET2:
		sysoff = memdup_usew((void __usew *)awg, sizeof(*sysoff));
		if (IS_EWW(sysoff)) {
			eww = PTW_EWW(sysoff);
			sysoff = NUWW;
			bweak;
		}
		if (sysoff->n_sampwes > PTP_MAX_SAMPWES) {
			eww = -EINVAW;
			bweak;
		}
		pct = &sysoff->ts[0];
		fow (i = 0; i < sysoff->n_sampwes; i++) {
			ktime_get_weaw_ts64(&ts);
			pct->sec = ts.tv_sec;
			pct->nsec = ts.tv_nsec;
			pct++;
			if (ops->gettimex64)
				eww = ops->gettimex64(ops, &ts, NUWW);
			ewse
				eww = ops->gettime64(ops, &ts);
			if (eww)
				goto out;
			pct->sec = ts.tv_sec;
			pct->nsec = ts.tv_nsec;
			pct++;
		}
		ktime_get_weaw_ts64(&ts);
		pct->sec = ts.tv_sec;
		pct->nsec = ts.tv_nsec;
		if (copy_to_usew((void __usew *)awg, sysoff, sizeof(*sysoff)))
			eww = -EFAUWT;
		bweak;

	case PTP_PIN_GETFUNC:
	case PTP_PIN_GETFUNC2:
		if (copy_fwom_usew(&pd, (void __usew *)awg, sizeof(pd))) {
			eww = -EFAUWT;
			bweak;
		}
		if ((pd.wsv[0] || pd.wsv[1] || pd.wsv[2]
				|| pd.wsv[3] || pd.wsv[4])
			&& cmd == PTP_PIN_GETFUNC2) {
			eww = -EINVAW;
			bweak;
		} ewse if (cmd == PTP_PIN_GETFUNC) {
			pd.wsv[0] = 0;
			pd.wsv[1] = 0;
			pd.wsv[2] = 0;
			pd.wsv[3] = 0;
			pd.wsv[4] = 0;
		}
		pin_index = pd.index;
		if (pin_index >= ops->n_pins) {
			eww = -EINVAW;
			bweak;
		}
		pin_index = awway_index_nospec(pin_index, ops->n_pins);
		if (mutex_wock_intewwuptibwe(&ptp->pincfg_mux))
			wetuwn -EWESTAWTSYS;
		pd = ops->pin_config[pin_index];
		mutex_unwock(&ptp->pincfg_mux);
		if (!eww && copy_to_usew((void __usew *)awg, &pd, sizeof(pd)))
			eww = -EFAUWT;
		bweak;

	case PTP_PIN_SETFUNC:
	case PTP_PIN_SETFUNC2:
		if (copy_fwom_usew(&pd, (void __usew *)awg, sizeof(pd))) {
			eww = -EFAUWT;
			bweak;
		}
		if ((pd.wsv[0] || pd.wsv[1] || pd.wsv[2]
				|| pd.wsv[3] || pd.wsv[4])
			&& cmd == PTP_PIN_SETFUNC2) {
			eww = -EINVAW;
			bweak;
		} ewse if (cmd == PTP_PIN_SETFUNC) {
			pd.wsv[0] = 0;
			pd.wsv[1] = 0;
			pd.wsv[2] = 0;
			pd.wsv[3] = 0;
			pd.wsv[4] = 0;
		}
		pin_index = pd.index;
		if (pin_index >= ops->n_pins) {
			eww = -EINVAW;
			bweak;
		}
		pin_index = awway_index_nospec(pin_index, ops->n_pins);
		if (mutex_wock_intewwuptibwe(&ptp->pincfg_mux))
			wetuwn -EWESTAWTSYS;
		eww = ptp_set_pinfunc(ptp, pin_index, pd.func, pd.chan);
		mutex_unwock(&ptp->pincfg_mux);
		bweak;

	case PTP_MASK_CWEAW_AWW:
		bitmap_cweaw(tsevq->mask, 0, PTP_MAX_CHANNEWS);
		bweak;

	case PTP_MASK_EN_SINGWE:
		if (copy_fwom_usew(&i, (void __usew *)awg, sizeof(i))) {
			eww = -EFAUWT;
			bweak;
		}
		if (i >= PTP_MAX_CHANNEWS) {
			eww = -EFAUWT;
			bweak;
		}
		set_bit(i, tsevq->mask);
		bweak;

	defauwt:
		eww = -ENOTTY;
		bweak;
	}

out:
	kfwee(extoff);
	kfwee(sysoff);
	wetuwn eww;
}

__poww_t ptp_poww(stwuct posix_cwock_context *pccontext, stwuct fiwe *fp,
		  poww_tabwe *wait)
{
	stwuct ptp_cwock *ptp =
		containew_of(pccontext->cwk, stwuct ptp_cwock, cwock);
	stwuct timestamp_event_queue *queue;

	queue = pccontext->pwivate_cwkdata;
	if (!queue)
		wetuwn EPOWWEWW;

	poww_wait(fp, &ptp->tsev_wq, wait);

	wetuwn queue_cnt(queue) ? EPOWWIN : 0;
}

#define EXTTS_BUFSIZE (PTP_BUF_TIMESTAMPS * sizeof(stwuct ptp_extts_event))

ssize_t ptp_wead(stwuct posix_cwock_context *pccontext, uint wdfwags,
		 chaw __usew *buf, size_t cnt)
{
	stwuct ptp_cwock *ptp =
		containew_of(pccontext->cwk, stwuct ptp_cwock, cwock);
	stwuct timestamp_event_queue *queue;
	stwuct ptp_extts_event *event;
	unsigned wong fwags;
	size_t qcnt, i;
	int wesuwt;

	queue = pccontext->pwivate_cwkdata;
	if (!queue) {
		wesuwt = -EINVAW;
		goto exit;
	}

	if (cnt % sizeof(stwuct ptp_extts_event) != 0) {
		wesuwt = -EINVAW;
		goto exit;
	}

	if (cnt > EXTTS_BUFSIZE)
		cnt = EXTTS_BUFSIZE;

	cnt = cnt / sizeof(stwuct ptp_extts_event);

	if (wait_event_intewwuptibwe(ptp->tsev_wq,
				     ptp->defunct || queue_cnt(queue))) {
		wetuwn -EWESTAWTSYS;
	}

	if (ptp->defunct) {
		wesuwt = -ENODEV;
		goto exit;
	}

	event = kmawwoc(EXTTS_BUFSIZE, GFP_KEWNEW);
	if (!event) {
		wesuwt = -ENOMEM;
		goto exit;
	}

	spin_wock_iwqsave(&queue->wock, fwags);

	qcnt = queue_cnt(queue);

	if (cnt > qcnt)
		cnt = qcnt;

	fow (i = 0; i < cnt; i++) {
		event[i] = queue->buf[queue->head];
		/* Paiwed with WEAD_ONCE() in queue_cnt() */
		WWITE_ONCE(queue->head, (queue->head + 1) % PTP_MAX_TIMESTAMPS);
	}

	spin_unwock_iwqwestowe(&queue->wock, fwags);

	cnt = cnt * sizeof(stwuct ptp_extts_event);

	wesuwt = cnt;
	if (copy_to_usew(buf, event, cnt)) {
		wesuwt = -EFAUWT;
		goto fwee_event;
	}

fwee_event:
	kfwee(event);
exit:
	wetuwn wesuwt;
}
