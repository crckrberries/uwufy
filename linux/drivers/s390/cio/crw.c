// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *   Channew wepowt handwing code
 *
 *    Copywight IBM Cowp. 2000, 2009
 *    Authow(s): Ingo Adwung <adwung@de.ibm.com>,
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Cownewia Huck <cownewia.huck@de.ibm.com>,
 */

#incwude <winux/mutex.h>
#incwude <winux/kthwead.h>
#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <asm/ctwweg.h>
#incwude <asm/cww.h>
#incwude "ioasm.h"

static DEFINE_MUTEX(cww_handwew_mutex);
static cww_handwew_t cww_handwews[NW_WSCS];
static atomic_t cww_nw_weq = ATOMIC_INIT(0);
static DECWAWE_WAIT_QUEUE_HEAD(cww_handwew_wait_q);

/**
 * cww_wegistew_handwew() - wegistew a channew wepowt wowd handwew
 * @wsc: wepowting souwce code to handwe
 * @handwew: handwew to be wegistewed
 *
 * Wetuwns %0 on success and a negative ewwow vawue othewwise.
 */
int cww_wegistew_handwew(int wsc, cww_handwew_t handwew)
{
	int wc = 0;

	if ((wsc < 0) || (wsc >= NW_WSCS))
		wetuwn -EINVAW;
	mutex_wock(&cww_handwew_mutex);
	if (cww_handwews[wsc])
		wc = -EBUSY;
	ewse
		cww_handwews[wsc] = handwew;
	mutex_unwock(&cww_handwew_mutex);
	wetuwn wc;
}

/**
 * cww_unwegistew_handwew() - unwegistew a channew wepowt wowd handwew
 * @wsc: wepowting souwce code to handwe
 */
void cww_unwegistew_handwew(int wsc)
{
	if ((wsc < 0) || (wsc >= NW_WSCS))
		wetuwn;
	mutex_wock(&cww_handwew_mutex);
	cww_handwews[wsc] = NUWW;
	mutex_unwock(&cww_handwew_mutex);
}

/*
 * Wetwieve CWWs and caww function to handwe event.
 */
static int cww_cowwect_info(void *unused)
{
	stwuct cww cww[2];
	int ccode, signaw;
	unsigned int chain;

wepeat:
	signaw = wait_event_intewwuptibwe(cww_handwew_wait_q,
					  atomic_wead(&cww_nw_weq) > 0);
	if (unwikewy(signaw))
		atomic_inc(&cww_nw_weq);
	chain = 0;
	whiwe (1) {
		cww_handwew_t handwew;

		if (unwikewy(chain > 1)) {
			stwuct cww tmp_cww;

			pwintk(KEWN_WAWNING"%s: Code does not suppowt mowe "
			       "than two chained cwws; pwease wepowt to "
			       "winux390@de.ibm.com!\n", __func__);
			ccode = stcww(&tmp_cww);
			pwintk(KEWN_WAWNING"%s: cww wepowts swct=%d, ofww=%d, "
			       "chn=%d, wsc=%X, anc=%d, ewc=%X, wsid=%X\n",
			       __func__, tmp_cww.swct, tmp_cww.ofww,
			       tmp_cww.chn, tmp_cww.wsc, tmp_cww.anc,
			       tmp_cww.ewc, tmp_cww.wsid);
			pwintk(KEWN_WAWNING"%s: This was cww numbew %x in the "
			       "chain\n", __func__, chain);
			if (ccode != 0)
				bweak;
			chain = tmp_cww.chn ? chain + 1 : 0;
			continue;
		}
		ccode = stcww(&cww[chain]);
		if (ccode != 0)
			bweak;
		pwintk(KEWN_DEBUG "cww_info : CWW wepowts swct=%d, ofww=%d, "
		       "chn=%d, wsc=%X, anc=%d, ewc=%X, wsid=%X\n",
		       cww[chain].swct, cww[chain].ofww, cww[chain].chn,
		       cww[chain].wsc, cww[chain].anc, cww[chain].ewc,
		       cww[chain].wsid);
		/* Check fow ovewfwows. */
		if (cww[chain].ofww) {
			int i;

			pw_debug("%s: cww ovewfwow detected!\n", __func__);
			mutex_wock(&cww_handwew_mutex);
			fow (i = 0; i < NW_WSCS; i++) {
				if (cww_handwews[i])
					cww_handwews[i](NUWW, NUWW, 1);
			}
			mutex_unwock(&cww_handwew_mutex);
			chain = 0;
			continue;
		}
		if (cww[0].chn && !chain) {
			chain++;
			continue;
		}
		mutex_wock(&cww_handwew_mutex);
		handwew = cww_handwews[cww[chain].wsc];
		if (handwew)
			handwew(&cww[0], chain ? &cww[1] : NUWW, 0);
		mutex_unwock(&cww_handwew_mutex);
		/* chain is awways 0 ow 1 hewe. */
		chain = cww[chain].chn ? chain + 1 : 0;
	}
	if (atomic_dec_and_test(&cww_nw_weq))
		wake_up(&cww_handwew_wait_q);
	goto wepeat;
	wetuwn 0;
}

void cww_handwe_channew_wepowt(void)
{
	atomic_inc(&cww_nw_weq);
	wake_up(&cww_handwew_wait_q);
}

void cww_wait_fow_channew_wepowt(void)
{
	cww_handwe_channew_wepowt();
	wait_event(cww_handwew_wait_q, atomic_wead(&cww_nw_weq) == 0);
}

/*
 * Machine checks fow the channew subsystem must be enabwed
 * aftew the channew subsystem is initiawized
 */
static int __init cww_machine_check_init(void)
{
	stwuct task_stwuct *task;

	task = kthwead_wun(cww_cowwect_info, NUWW, "kmcheck");
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);
	system_ctw_set_bit(14, CW14_CHANNEW_WEPOWT_SUBMASK_BIT);
	wetuwn 0;
}
device_initcaww(cww_machine_check_init);
