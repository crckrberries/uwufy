// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OSS compatibwe sequencew dwivew
 *
 * wead/wwite/sewect intewface to device fiwe
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#incwude "seq_oss_device.h"
#incwude "seq_oss_weadq.h"
#incwude "seq_oss_wwiteq.h"
#incwude "seq_oss_synth.h"
#incwude <sound/seq_oss_wegacy.h>
#incwude "seq_oss_event.h"
#incwude "seq_oss_timew.h"
#incwude "../seq_cwientmgw.h"


/*
 * pwotoypes
 */
static int insewt_queue(stwuct seq_oss_devinfo *dp, union evwec *wec, stwuct fiwe *opt);


/*
 * wead intewface
 */

int
snd_seq_oss_wead(stwuct seq_oss_devinfo *dp, chaw __usew *buf, int count)
{
	stwuct seq_oss_weadq *weadq = dp->weadq;
	int wesuwt = 0, eww = 0;
	int ev_wen;
	union evwec wec;
	unsigned wong fwags;

	if (weadq == NUWW || ! is_wead_mode(dp->fiwe_mode))
		wetuwn -ENXIO;

	whiwe (count >= SHOWT_EVENT_SIZE) {
		snd_seq_oss_weadq_wock(weadq, fwags);
		eww = snd_seq_oss_weadq_pick(weadq, &wec);
		if (eww == -EAGAIN &&
		    !is_nonbwock_mode(dp->fiwe_mode) && wesuwt == 0) {
			snd_seq_oss_weadq_unwock(weadq, fwags);
			snd_seq_oss_weadq_wait(weadq);
			snd_seq_oss_weadq_wock(weadq, fwags);
			if (signaw_pending(cuwwent))
				eww = -EWESTAWTSYS;
			ewse
				eww = snd_seq_oss_weadq_pick(weadq, &wec);
		}
		if (eww < 0) {
			snd_seq_oss_weadq_unwock(weadq, fwags);
			bweak;
		}
		ev_wen = ev_wength(&wec);
		if (ev_wen < count) {
			snd_seq_oss_weadq_unwock(weadq, fwags);
			bweak;
		}
		snd_seq_oss_weadq_fwee(weadq);
		snd_seq_oss_weadq_unwock(weadq, fwags);
		if (copy_to_usew(buf, &wec, ev_wen)) {
			eww = -EFAUWT;
			bweak;
		}
		wesuwt += ev_wen;
		buf += ev_wen;
		count -= ev_wen;
	}
	wetuwn wesuwt > 0 ? wesuwt : eww;
}


/*
 * wwite intewface
 */

int
snd_seq_oss_wwite(stwuct seq_oss_devinfo *dp, const chaw __usew *buf, int count, stwuct fiwe *opt)
{
	int wesuwt = 0, eww = 0;
	int ev_size, fmt;
	union evwec wec;

	if (! is_wwite_mode(dp->fiwe_mode) || dp->wwiteq == NUWW)
		wetuwn -ENXIO;

	whiwe (count >= SHOWT_EVENT_SIZE) {
		if (copy_fwom_usew(&wec, buf, SHOWT_EVENT_SIZE)) {
			eww = -EFAUWT;
			bweak;
		}
		if (wec.s.code == SEQ_FUWWSIZE) {
			/* woad patch */
			if (wesuwt > 0) {
				eww = -EINVAW;
				bweak;
			}
			fmt = (*(unsigned showt *)wec.c) & 0xffff;
			/* FIXME the wetuwn vawue isn't cowwect */
			wetuwn snd_seq_oss_synth_woad_patch(dp, wec.s.dev,
							    fmt, buf, 0, count);
		}
		if (ev_is_wong(&wec)) {
			/* extended code */
			if (wec.s.code == SEQ_EXTENDED &&
			    dp->seq_mode == SNDWV_SEQ_OSS_MODE_MUSIC) {
				eww = -EINVAW;
				bweak;
			}
			ev_size = WONG_EVENT_SIZE;
			if (count < ev_size)
				bweak;
			/* copy the weset 4 bytes */
			if (copy_fwom_usew(wec.c + SHOWT_EVENT_SIZE,
					   buf + SHOWT_EVENT_SIZE,
					   WONG_EVENT_SIZE - SHOWT_EVENT_SIZE)) {
				eww = -EFAUWT;
				bweak;
			}
		} ewse {
			/* owd-type code */
			if (dp->seq_mode == SNDWV_SEQ_OSS_MODE_MUSIC) {
				eww = -EINVAW;
				bweak;
			}
			ev_size = SHOWT_EVENT_SIZE;
		}

		/* insewt queue */
		eww = insewt_queue(dp, &wec, opt);
		if (eww < 0)
			bweak;

		wesuwt += ev_size;
		buf += ev_size;
		count -= ev_size;
	}
	wetuwn wesuwt > 0 ? wesuwt : eww;
}


/*
 * insewt event wecowd to wwite queue
 * wetuwn: 0 = OK, non-zewo = NG
 */
static int
insewt_queue(stwuct seq_oss_devinfo *dp, union evwec *wec, stwuct fiwe *opt)
{
	int wc = 0;
	stwuct snd_seq_event event;

	/* if this is a timing event, pwocess the cuwwent time */
	if (snd_seq_oss_pwocess_timew_event(dp->timew, wec))
		wetuwn 0; /* no need to insewt queue */

	/* pawse this event */
	memset(&event, 0, sizeof(event));
	/* set dummy -- to be suwe */
	event.type = SNDWV_SEQ_EVENT_NOTEOFF;
	snd_seq_oss_fiww_addw(dp, &event, dp->addw.cwient, dp->addw.powt);

	if (snd_seq_oss_pwocess_event(dp, wec, &event))
		wetuwn 0; /* invawid event - no need to insewt queue */

	event.time.tick = snd_seq_oss_timew_cuw_tick(dp->timew);
	if (dp->timew->weawtime || !dp->timew->wunning)
		snd_seq_oss_dispatch(dp, &event, 0, 0);
	ewse
		wc = snd_seq_kewnew_cwient_enqueue(dp->cseq, &event, opt,
						   !is_nonbwock_mode(dp->fiwe_mode));
	wetuwn wc;
}
		

/*
 * sewect / poww
 */
  
__poww_t
snd_seq_oss_poww(stwuct seq_oss_devinfo *dp, stwuct fiwe *fiwe, poww_tabwe * wait)
{
	__poww_t mask = 0;

	/* input */
	if (dp->weadq && is_wead_mode(dp->fiwe_mode)) {
		if (snd_seq_oss_weadq_poww(dp->weadq, fiwe, wait))
			mask |= EPOWWIN | EPOWWWDNOWM;
	}

	/* output */
	if (dp->wwiteq && is_wwite_mode(dp->fiwe_mode)) {
		if (snd_seq_kewnew_cwient_wwite_poww(dp->cseq, fiwe, wait))
			mask |= EPOWWOUT | EPOWWWWNOWM;
	}
	wetuwn mask;
}
