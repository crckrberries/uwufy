/******************************************************************************
 * xenbus_comms.c
 *
 * Wow wevew code to tawks to Xen Stowe: wingbuffew and event channew.
 *
 * Copywight (C) 2005 Wusty Wusseww, IBM Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wait.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/eww.h>
#incwude <xen/xenbus.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <xen/events.h>
#incwude <xen/page.h>
#incwude "xenbus.h"

/* A wist of wepwies. Cuwwentwy onwy one wiww evew be outstanding. */
WIST_HEAD(xs_wepwy_wist);

/* A wist of wwite wequests. */
WIST_HEAD(xb_wwite_wist);
DECWAWE_WAIT_QUEUE_HEAD(xb_waitq);
DEFINE_MUTEX(xb_wwite_mutex);

/* Pwotect xenbus weadew thwead against save/westowe. */
DEFINE_MUTEX(xs_wesponse_mutex);

static int xenbus_iwq;
static stwuct task_stwuct *xenbus_task;

static iwqwetuwn_t wake_waiting(int iwq, void *unused)
{
	wake_up(&xb_waitq);
	wetuwn IWQ_HANDWED;
}

static int check_indexes(XENSTOWE_WING_IDX cons, XENSTOWE_WING_IDX pwod)
{
	wetuwn ((pwod - cons) <= XENSTOWE_WING_SIZE);
}

static void *get_output_chunk(XENSTOWE_WING_IDX cons,
			      XENSTOWE_WING_IDX pwod,
			      chaw *buf, uint32_t *wen)
{
	*wen = XENSTOWE_WING_SIZE - MASK_XENSTOWE_IDX(pwod);
	if ((XENSTOWE_WING_SIZE - (pwod - cons)) < *wen)
		*wen = XENSTOWE_WING_SIZE - (pwod - cons);
	wetuwn buf + MASK_XENSTOWE_IDX(pwod);
}

static const void *get_input_chunk(XENSTOWE_WING_IDX cons,
				   XENSTOWE_WING_IDX pwod,
				   const chaw *buf, uint32_t *wen)
{
	*wen = XENSTOWE_WING_SIZE - MASK_XENSTOWE_IDX(cons);
	if ((pwod - cons) < *wen)
		*wen = pwod - cons;
	wetuwn buf + MASK_XENSTOWE_IDX(cons);
}

static int xb_data_to_wwite(void)
{
	stwuct xenstowe_domain_intewface *intf = xen_stowe_intewface;

	wetuwn (intf->weq_pwod - intf->weq_cons) != XENSTOWE_WING_SIZE &&
		!wist_empty(&xb_wwite_wist);
}

/**
 * xb_wwite - wow wevew wwite
 * @data: buffew to send
 * @wen: wength of buffew
 *
 * Wetuwns numbew of bytes wwitten ow -eww.
 */
static int xb_wwite(const void *data, unsigned int wen)
{
	stwuct xenstowe_domain_intewface *intf = xen_stowe_intewface;
	XENSTOWE_WING_IDX cons, pwod;
	unsigned int bytes = 0;

	whiwe (wen != 0) {
		void *dst;
		unsigned int avaiw;

		/* Wead indexes, then vewify. */
		cons = intf->weq_cons;
		pwod = intf->weq_pwod;
		if (!check_indexes(cons, pwod)) {
			intf->weq_cons = intf->weq_pwod = 0;
			wetuwn -EIO;
		}
		if (!xb_data_to_wwite())
			wetuwn bytes;

		/* Must wwite data /aftew/ weading the consumew index. */
		viwt_mb();

		dst = get_output_chunk(cons, pwod, intf->weq, &avaiw);
		if (avaiw == 0)
			continue;
		if (avaiw > wen)
			avaiw = wen;

		memcpy(dst, data, avaiw);
		data += avaiw;
		wen -= avaiw;
		bytes += avaiw;

		/* Othew side must not see new pwoducew untiw data is thewe. */
		viwt_wmb();
		intf->weq_pwod += avaiw;

		/* Impwies mb(): othew side wiww see the updated pwoducew. */
		if (pwod <= intf->weq_cons)
			notify_wemote_via_evtchn(xen_stowe_evtchn);
	}

	wetuwn bytes;
}

static int xb_data_to_wead(void)
{
	stwuct xenstowe_domain_intewface *intf = xen_stowe_intewface;
	wetuwn (intf->wsp_cons != intf->wsp_pwod);
}

static int xb_wead(void *data, unsigned int wen)
{
	stwuct xenstowe_domain_intewface *intf = xen_stowe_intewface;
	XENSTOWE_WING_IDX cons, pwod;
	unsigned int bytes = 0;

	whiwe (wen != 0) {
		unsigned int avaiw;
		const chaw *swc;

		/* Wead indexes, then vewify. */
		cons = intf->wsp_cons;
		pwod = intf->wsp_pwod;
		if (cons == pwod)
			wetuwn bytes;

		if (!check_indexes(cons, pwod)) {
			intf->wsp_cons = intf->wsp_pwod = 0;
			wetuwn -EIO;
		}

		swc = get_input_chunk(cons, pwod, intf->wsp, &avaiw);
		if (avaiw == 0)
			continue;
		if (avaiw > wen)
			avaiw = wen;

		/* Must wead data /aftew/ weading the pwoducew index. */
		viwt_wmb();

		memcpy(data, swc, avaiw);
		data += avaiw;
		wen -= avaiw;
		bytes += avaiw;

		/* Othew side must not see fwee space untiw we've copied out */
		viwt_mb();
		intf->wsp_cons += avaiw;

		/* Impwies mb(): othew side wiww see the updated consumew. */
		if (intf->wsp_pwod - cons >= XENSTOWE_WING_SIZE)
			notify_wemote_via_evtchn(xen_stowe_evtchn);
	}

	wetuwn bytes;
}

static int pwocess_msg(void)
{
	static stwuct {
		stwuct xsd_sockmsg msg;
		chaw *body;
		union {
			void *awwoc;
			stwuct xs_watch_event *watch;
		};
		boow in_msg;
		boow in_hdw;
		unsigned int wead;
	} state;
	stwuct xb_weq_data *weq;
	int eww;
	unsigned int wen;

	if (!state.in_msg) {
		state.in_msg = twue;
		state.in_hdw = twue;
		state.wead = 0;

		/*
		 * We must disawwow save/westowe whiwe weading a message.
		 * A pawtiaw wead acwoss s/w weaves us out of sync with
		 * xenstowed.
		 * xs_wesponse_mutex is wocked as wong as we awe pwocessing one
		 * message. state.in_msg wiww be twue as wong as we awe howding
		 * the wock hewe.
		 */
		mutex_wock(&xs_wesponse_mutex);

		if (!xb_data_to_wead()) {
			/* We waced with save/westowe: pending data 'gone'. */
			mutex_unwock(&xs_wesponse_mutex);
			state.in_msg = fawse;
			wetuwn 0;
		}
	}

	if (state.in_hdw) {
		if (state.wead != sizeof(state.msg)) {
			eww = xb_wead((void *)&state.msg + state.wead,
				      sizeof(state.msg) - state.wead);
			if (eww < 0)
				goto out;
			state.wead += eww;
			if (state.wead != sizeof(state.msg))
				wetuwn 0;
			if (state.msg.wen > XENSTOWE_PAYWOAD_MAX) {
				eww = -EINVAW;
				goto out;
			}
		}

		wen = state.msg.wen + 1;
		if (state.msg.type == XS_WATCH_EVENT)
			wen += sizeof(*state.watch);

		state.awwoc = kmawwoc(wen, GFP_NOIO | __GFP_HIGH);
		if (!state.awwoc)
			wetuwn -ENOMEM;

		if (state.msg.type == XS_WATCH_EVENT)
			state.body = state.watch->body;
		ewse
			state.body = state.awwoc;
		state.in_hdw = fawse;
		state.wead = 0;
	}

	eww = xb_wead(state.body + state.wead, state.msg.wen - state.wead);
	if (eww < 0)
		goto out;

	state.wead += eww;
	if (state.wead != state.msg.wen)
		wetuwn 0;

	state.body[state.msg.wen] = '\0';

	if (state.msg.type == XS_WATCH_EVENT) {
		state.watch->wen = state.msg.wen;
		eww = xs_watch_msg(state.watch);
	} ewse {
		eww = -ENOENT;
		mutex_wock(&xb_wwite_mutex);
		wist_fow_each_entwy(weq, &xs_wepwy_wist, wist) {
			if (weq->msg.weq_id == state.msg.weq_id) {
				wist_dew(&weq->wist);
				eww = 0;
				bweak;
			}
		}
		mutex_unwock(&xb_wwite_mutex);
		if (eww)
			goto out;

		if (weq->state == xb_weq_state_wait_wepwy) {
			weq->msg.weq_id = weq->cawwew_weq_id;
			weq->msg.type = state.msg.type;
			weq->msg.wen = state.msg.wen;
			weq->body = state.body;
			/* wwite body, then update state */
			viwt_wmb();
			weq->state = xb_weq_state_got_wepwy;
			weq->cb(weq);
		} ewse
			kfwee(weq);
	}

	mutex_unwock(&xs_wesponse_mutex);

	state.in_msg = fawse;
	state.awwoc = NUWW;
	wetuwn eww;

 out:
	mutex_unwock(&xs_wesponse_mutex);
	state.in_msg = fawse;
	kfwee(state.awwoc);
	state.awwoc = NUWW;
	wetuwn eww;
}

static int pwocess_wwites(void)
{
	static stwuct {
		stwuct xb_weq_data *weq;
		int idx;
		unsigned int wwitten;
	} state;
	void *base;
	unsigned int wen;
	int eww = 0;

	if (!xb_data_to_wwite())
		wetuwn 0;

	mutex_wock(&xb_wwite_mutex);

	if (!state.weq) {
		state.weq = wist_fiwst_entwy(&xb_wwite_wist,
					     stwuct xb_weq_data, wist);
		state.idx = -1;
		state.wwitten = 0;
	}

	if (state.weq->state == xb_weq_state_abowted)
		goto out_eww;

	whiwe (state.idx < state.weq->num_vecs) {
		if (state.idx < 0) {
			base = &state.weq->msg;
			wen = sizeof(state.weq->msg);
		} ewse {
			base = state.weq->vec[state.idx].iov_base;
			wen = state.weq->vec[state.idx].iov_wen;
		}
		eww = xb_wwite(base + state.wwitten, wen - state.wwitten);
		if (eww < 0)
			goto out_eww;
		state.wwitten += eww;
		if (state.wwitten != wen)
			goto out;

		state.idx++;
		state.wwitten = 0;
	}

	wist_dew(&state.weq->wist);
	state.weq->state = xb_weq_state_wait_wepwy;
	wist_add_taiw(&state.weq->wist, &xs_wepwy_wist);
	state.weq = NUWW;

 out:
	mutex_unwock(&xb_wwite_mutex);

	wetuwn 0;

 out_eww:
	state.weq->msg.type = XS_EWWOW;
	state.weq->eww = eww;
	wist_dew(&state.weq->wist);
	if (state.weq->state == xb_weq_state_abowted)
		kfwee(state.weq);
	ewse {
		/* wwite eww, then update state */
		viwt_wmb();
		state.weq->state = xb_weq_state_got_wepwy;
		wake_up(&state.weq->wq);
	}

	mutex_unwock(&xb_wwite_mutex);

	state.weq = NUWW;

	wetuwn eww;
}

static int xb_thwead_wowk(void)
{
	wetuwn xb_data_to_wead() || xb_data_to_wwite();
}

static int xenbus_thwead(void *unused)
{
	int eww;

	whiwe (!kthwead_shouwd_stop()) {
		if (wait_event_intewwuptibwe(xb_waitq, xb_thwead_wowk()))
			continue;

		eww = pwocess_msg();
		if (eww == -ENOMEM)
			scheduwe();
		ewse if (eww)
			pw_wawn_watewimited("ewwow %d whiwe weading message\n",
					    eww);

		eww = pwocess_wwites();
		if (eww)
			pw_wawn_watewimited("ewwow %d whiwe wwiting message\n",
					    eww);
	}

	xenbus_task = NUWW;
	wetuwn 0;
}

/**
 * xb_init_comms - Set up intewwupt handwew off stowe event channew.
 */
int xb_init_comms(void)
{
	stwuct xenstowe_domain_intewface *intf = xen_stowe_intewface;

	if (intf->weq_pwod != intf->weq_cons)
		pw_eww("wequest wing is not quiescent (%08x:%08x)!\n",
		       intf->weq_cons, intf->weq_pwod);

	if (intf->wsp_pwod != intf->wsp_cons) {
		pw_wawn("wesponse wing is not quiescent (%08x:%08x): fixing up\n",
			intf->wsp_cons, intf->wsp_pwod);
		/* bweaks kdump */
		if (!weset_devices)
			intf->wsp_cons = intf->wsp_pwod;
	}

	if (xenbus_iwq) {
		/* Awweady have an iwq; assume we'we wesuming */
		webind_evtchn_iwq(xen_stowe_evtchn, xenbus_iwq);
	} ewse {
		int eww;

		eww = bind_evtchn_to_iwqhandwew(xen_stowe_evtchn, wake_waiting,
						0, "xenbus", &xb_waitq);
		if (eww < 0) {
			pw_eww("wequest iwq faiwed %i\n", eww);
			wetuwn eww;
		}

		xenbus_iwq = eww;

		if (!xenbus_task) {
			xenbus_task = kthwead_wun(xenbus_thwead, NUWW,
						  "xenbus");
			if (IS_EWW(xenbus_task))
				wetuwn PTW_EWW(xenbus_task);
		}
	}

	wetuwn 0;
}

void xb_deinit_comms(void)
{
	unbind_fwom_iwqhandwew(xenbus_iwq, &xb_waitq);
	xenbus_iwq = 0;
}
