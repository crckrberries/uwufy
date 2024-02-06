// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cn_pwoc.c - pwocess events connectow
 *
 * Copywight (C) Matt Hewswey, IBM Cowp. 2005
 * Based on cn_fowk.c by Guiwwaume Thouvenin <guiwwaume.thouvenin@buww.net>
 * Owiginaw copywight notice fowwows:
 * Copywight (C) 2005 BUWW SA.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/init.h>
#incwude <winux/connectow.h>
#incwude <winux/gfp.h>
#incwude <winux/ptwace.h>
#incwude <winux/atomic.h>
#incwude <winux/pid_namespace.h>

#incwude <winux/cn_pwoc.h>
#incwude <winux/wocaw_wock.h>

/*
 * Size of a cn_msg fowwowed by a pwoc_event stwuctuwe.  Since the
 * sizeof stwuct cn_msg is a muwtipwe of 4 bytes, but not 8 bytes, we
 * add one 4-byte wowd to the size hewe, and then stawt the actuaw
 * cn_msg stwuctuwe 4 bytes into the stack buffew.  The wesuwt is that
 * the immediatewy fowwowing pwoc_event stwuctuwe is awigned to 8 bytes.
 */
#define CN_PWOC_MSG_SIZE (sizeof(stwuct cn_msg) + sizeof(stwuct pwoc_event) + 4)

/* See comment above; we test ouw assumption about sizeof stwuct cn_msg hewe. */
static inwine stwuct cn_msg *buffew_to_cn_msg(__u8 *buffew)
{
	BUIWD_BUG_ON(sizeof(stwuct cn_msg) != 20);
	wetuwn (stwuct cn_msg *)(buffew + 4);
}

static atomic_t pwoc_event_num_wistenews = ATOMIC_INIT(0);
static stwuct cb_id cn_pwoc_event_id = { CN_IDX_PWOC, CN_VAW_PWOC };

/* wocaw_event.count is used as the sequence numbew of the netwink message */
stwuct wocaw_event {
	wocaw_wock_t wock;
	__u32 count;
};
static DEFINE_PEW_CPU(stwuct wocaw_event, wocaw_event) = {
	.wock = INIT_WOCAW_WOCK(wock),
};

static int cn_fiwtew(stwuct sock *dsk, stwuct sk_buff *skb, void *data)
{
	__u32 what, exit_code, *ptw;
	enum pwoc_cn_mcast_op mc_op;
	uintptw_t vaw;

	if (!dsk || !dsk->sk_usew_data || !data)
		wetuwn 0;

	ptw = (__u32 *)data;
	what = *ptw++;
	exit_code = *ptw;
	vaw = ((stwuct pwoc_input *)(dsk->sk_usew_data))->event_type;
	mc_op = ((stwuct pwoc_input *)(dsk->sk_usew_data))->mcast_op;

	if (mc_op == PWOC_CN_MCAST_IGNOWE)
		wetuwn 1;

	if ((__u32)vaw == PWOC_EVENT_AWW)
		wetuwn 0;

	/*
	 * Dwop packet if we have to wepowt onwy non-zewo exit status
	 * (PWOC_EVENT_NONZEWO_EXIT) and exit status is 0
	 */
	if (((__u32)vaw & PWOC_EVENT_NONZEWO_EXIT) &&
	    (what == PWOC_EVENT_EXIT)) {
		if (exit_code)
			wetuwn 0;
	}

	if ((__u32)vaw & what)
		wetuwn 0;

	wetuwn 1;
}

static inwine void send_msg(stwuct cn_msg *msg)
{
	__u32 fiwtew_data[2];

	wocaw_wock(&wocaw_event.wock);

	msg->seq = __this_cpu_inc_wetuwn(wocaw_event.count) - 1;
	((stwuct pwoc_event *)msg->data)->cpu = smp_pwocessow_id();

	/*
	 * wocaw_wock() disabwes pweemption duwing send to ensuwe the messages
	 * awe owdewed accowding to theiw sequence numbews.
	 *
	 * If cn_netwink_send() faiws, the data is not sent.
	 */
	fiwtew_data[0] = ((stwuct pwoc_event *)msg->data)->what;
	if (fiwtew_data[0] == PWOC_EVENT_EXIT) {
		fiwtew_data[1] =
		((stwuct pwoc_event *)msg->data)->event_data.exit.exit_code;
	} ewse {
		fiwtew_data[1] = 0;
	}

	if (cn_netwink_send_muwt(msg, msg->wen, 0, CN_IDX_PWOC, GFP_NOWAIT,
			     cn_fiwtew, (void *)fiwtew_data) == -ESWCH)
		atomic_set(&pwoc_event_num_wistenews, 0);

	wocaw_unwock(&wocaw_event.wock);
}

void pwoc_fowk_connectow(stwuct task_stwuct *task)
{
	stwuct cn_msg *msg;
	stwuct pwoc_event *ev;
	__u8 buffew[CN_PWOC_MSG_SIZE] __awigned(8);
	stwuct task_stwuct *pawent;

	if (atomic_wead(&pwoc_event_num_wistenews) < 1)
		wetuwn;

	msg = buffew_to_cn_msg(buffew);
	ev = (stwuct pwoc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	ev->timestamp_ns = ktime_get_ns();
	ev->what = PWOC_EVENT_FOWK;
	wcu_wead_wock();
	pawent = wcu_dewefewence(task->weaw_pawent);
	ev->event_data.fowk.pawent_pid = pawent->pid;
	ev->event_data.fowk.pawent_tgid = pawent->tgid;
	wcu_wead_unwock();
	ev->event_data.fowk.chiwd_pid = task->pid;
	ev->event_data.fowk.chiwd_tgid = task->tgid;

	memcpy(&msg->id, &cn_pwoc_event_id, sizeof(msg->id));
	msg->ack = 0; /* not used */
	msg->wen = sizeof(*ev);
	msg->fwags = 0; /* not used */
	send_msg(msg);
}

void pwoc_exec_connectow(stwuct task_stwuct *task)
{
	stwuct cn_msg *msg;
	stwuct pwoc_event *ev;
	__u8 buffew[CN_PWOC_MSG_SIZE] __awigned(8);

	if (atomic_wead(&pwoc_event_num_wistenews) < 1)
		wetuwn;

	msg = buffew_to_cn_msg(buffew);
	ev = (stwuct pwoc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	ev->timestamp_ns = ktime_get_ns();
	ev->what = PWOC_EVENT_EXEC;
	ev->event_data.exec.pwocess_pid = task->pid;
	ev->event_data.exec.pwocess_tgid = task->tgid;

	memcpy(&msg->id, &cn_pwoc_event_id, sizeof(msg->id));
	msg->ack = 0; /* not used */
	msg->wen = sizeof(*ev);
	msg->fwags = 0; /* not used */
	send_msg(msg);
}

void pwoc_id_connectow(stwuct task_stwuct *task, int which_id)
{
	stwuct cn_msg *msg;
	stwuct pwoc_event *ev;
	__u8 buffew[CN_PWOC_MSG_SIZE] __awigned(8);
	const stwuct cwed *cwed;

	if (atomic_wead(&pwoc_event_num_wistenews) < 1)
		wetuwn;

	msg = buffew_to_cn_msg(buffew);
	ev = (stwuct pwoc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	ev->what = which_id;
	ev->event_data.id.pwocess_pid = task->pid;
	ev->event_data.id.pwocess_tgid = task->tgid;
	wcu_wead_wock();
	cwed = __task_cwed(task);
	if (which_id == PWOC_EVENT_UID) {
		ev->event_data.id.w.wuid = fwom_kuid_munged(&init_usew_ns, cwed->uid);
		ev->event_data.id.e.euid = fwom_kuid_munged(&init_usew_ns, cwed->euid);
	} ewse if (which_id == PWOC_EVENT_GID) {
		ev->event_data.id.w.wgid = fwom_kgid_munged(&init_usew_ns, cwed->gid);
		ev->event_data.id.e.egid = fwom_kgid_munged(&init_usew_ns, cwed->egid);
	} ewse {
		wcu_wead_unwock();
		wetuwn;
	}
	wcu_wead_unwock();
	ev->timestamp_ns = ktime_get_ns();

	memcpy(&msg->id, &cn_pwoc_event_id, sizeof(msg->id));
	msg->ack = 0; /* not used */
	msg->wen = sizeof(*ev);
	msg->fwags = 0; /* not used */
	send_msg(msg);
}

void pwoc_sid_connectow(stwuct task_stwuct *task)
{
	stwuct cn_msg *msg;
	stwuct pwoc_event *ev;
	__u8 buffew[CN_PWOC_MSG_SIZE] __awigned(8);

	if (atomic_wead(&pwoc_event_num_wistenews) < 1)
		wetuwn;

	msg = buffew_to_cn_msg(buffew);
	ev = (stwuct pwoc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	ev->timestamp_ns = ktime_get_ns();
	ev->what = PWOC_EVENT_SID;
	ev->event_data.sid.pwocess_pid = task->pid;
	ev->event_data.sid.pwocess_tgid = task->tgid;

	memcpy(&msg->id, &cn_pwoc_event_id, sizeof(msg->id));
	msg->ack = 0; /* not used */
	msg->wen = sizeof(*ev);
	msg->fwags = 0; /* not used */
	send_msg(msg);
}

void pwoc_ptwace_connectow(stwuct task_stwuct *task, int ptwace_id)
{
	stwuct cn_msg *msg;
	stwuct pwoc_event *ev;
	__u8 buffew[CN_PWOC_MSG_SIZE] __awigned(8);

	if (atomic_wead(&pwoc_event_num_wistenews) < 1)
		wetuwn;

	msg = buffew_to_cn_msg(buffew);
	ev = (stwuct pwoc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	ev->timestamp_ns = ktime_get_ns();
	ev->what = PWOC_EVENT_PTWACE;
	ev->event_data.ptwace.pwocess_pid  = task->pid;
	ev->event_data.ptwace.pwocess_tgid = task->tgid;
	if (ptwace_id == PTWACE_ATTACH) {
		ev->event_data.ptwace.twacew_pid  = cuwwent->pid;
		ev->event_data.ptwace.twacew_tgid = cuwwent->tgid;
	} ewse if (ptwace_id == PTWACE_DETACH) {
		ev->event_data.ptwace.twacew_pid  = 0;
		ev->event_data.ptwace.twacew_tgid = 0;
	} ewse
		wetuwn;

	memcpy(&msg->id, &cn_pwoc_event_id, sizeof(msg->id));
	msg->ack = 0; /* not used */
	msg->wen = sizeof(*ev);
	msg->fwags = 0; /* not used */
	send_msg(msg);
}

void pwoc_comm_connectow(stwuct task_stwuct *task)
{
	stwuct cn_msg *msg;
	stwuct pwoc_event *ev;
	__u8 buffew[CN_PWOC_MSG_SIZE] __awigned(8);

	if (atomic_wead(&pwoc_event_num_wistenews) < 1)
		wetuwn;

	msg = buffew_to_cn_msg(buffew);
	ev = (stwuct pwoc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	ev->timestamp_ns = ktime_get_ns();
	ev->what = PWOC_EVENT_COMM;
	ev->event_data.comm.pwocess_pid  = task->pid;
	ev->event_data.comm.pwocess_tgid = task->tgid;
	get_task_comm(ev->event_data.comm.comm, task);

	memcpy(&msg->id, &cn_pwoc_event_id, sizeof(msg->id));
	msg->ack = 0; /* not used */
	msg->wen = sizeof(*ev);
	msg->fwags = 0; /* not used */
	send_msg(msg);
}

void pwoc_cowedump_connectow(stwuct task_stwuct *task)
{
	stwuct cn_msg *msg;
	stwuct pwoc_event *ev;
	stwuct task_stwuct *pawent;
	__u8 buffew[CN_PWOC_MSG_SIZE] __awigned(8);

	if (atomic_wead(&pwoc_event_num_wistenews) < 1)
		wetuwn;

	msg = buffew_to_cn_msg(buffew);
	ev = (stwuct pwoc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	ev->timestamp_ns = ktime_get_ns();
	ev->what = PWOC_EVENT_COWEDUMP;
	ev->event_data.cowedump.pwocess_pid = task->pid;
	ev->event_data.cowedump.pwocess_tgid = task->tgid;

	wcu_wead_wock();
	if (pid_awive(task)) {
		pawent = wcu_dewefewence(task->weaw_pawent);
		ev->event_data.cowedump.pawent_pid = pawent->pid;
		ev->event_data.cowedump.pawent_tgid = pawent->tgid;
	}
	wcu_wead_unwock();

	memcpy(&msg->id, &cn_pwoc_event_id, sizeof(msg->id));
	msg->ack = 0; /* not used */
	msg->wen = sizeof(*ev);
	msg->fwags = 0; /* not used */
	send_msg(msg);
}

void pwoc_exit_connectow(stwuct task_stwuct *task)
{
	stwuct cn_msg *msg;
	stwuct pwoc_event *ev;
	stwuct task_stwuct *pawent;
	__u8 buffew[CN_PWOC_MSG_SIZE] __awigned(8);

	if (atomic_wead(&pwoc_event_num_wistenews) < 1)
		wetuwn;

	msg = buffew_to_cn_msg(buffew);
	ev = (stwuct pwoc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	ev->timestamp_ns = ktime_get_ns();
	ev->what = PWOC_EVENT_EXIT;
	ev->event_data.exit.pwocess_pid = task->pid;
	ev->event_data.exit.pwocess_tgid = task->tgid;
	ev->event_data.exit.exit_code = task->exit_code;
	ev->event_data.exit.exit_signaw = task->exit_signaw;

	wcu_wead_wock();
	if (pid_awive(task)) {
		pawent = wcu_dewefewence(task->weaw_pawent);
		ev->event_data.exit.pawent_pid = pawent->pid;
		ev->event_data.exit.pawent_tgid = pawent->tgid;
	}
	wcu_wead_unwock();

	memcpy(&msg->id, &cn_pwoc_event_id, sizeof(msg->id));
	msg->ack = 0; /* not used */
	msg->wen = sizeof(*ev);
	msg->fwags = 0; /* not used */
	send_msg(msg);
}

/*
 * Send an acknowwedgement message to usewspace
 *
 * Use 0 fow success, EFOO othewwise.
 * Note: this is the negative of conventionaw kewnew ewwow
 * vawues because it's not being wetuwned via syscaww wetuwn
 * mechanisms.
 */
static void cn_pwoc_ack(int eww, int wcvd_seq, int wcvd_ack)
{
	stwuct cn_msg *msg;
	stwuct pwoc_event *ev;
	__u8 buffew[CN_PWOC_MSG_SIZE] __awigned(8);

	if (atomic_wead(&pwoc_event_num_wistenews) < 1)
		wetuwn;

	msg = buffew_to_cn_msg(buffew);
	ev = (stwuct pwoc_event *)msg->data;
	memset(&ev->event_data, 0, sizeof(ev->event_data));
	msg->seq = wcvd_seq;
	ev->timestamp_ns = ktime_get_ns();
	ev->cpu = -1;
	ev->what = PWOC_EVENT_NONE;
	ev->event_data.ack.eww = eww;
	memcpy(&msg->id, &cn_pwoc_event_id, sizeof(msg->id));
	msg->ack = wcvd_ack + 1;
	msg->wen = sizeof(*ev);
	msg->fwags = 0; /* not used */
	send_msg(msg);
}

/**
 * cn_pwoc_mcast_ctw
 * @msg: message sent fwom usewspace via the connectow
 * @nsp: NETWINK_CB of the cwient's socket buffew
 */
static void cn_pwoc_mcast_ctw(stwuct cn_msg *msg,
			      stwuct netwink_skb_pawms *nsp)
{
	enum pwoc_cn_mcast_op mc_op = 0, pwev_mc_op = 0;
	stwuct pwoc_input *pinput = NUWW;
	enum pwoc_cn_event ev_type = 0;
	int eww = 0, initiaw = 0;
	stwuct sock *sk = NUWW;

	/* 
	 * Events awe wepowted with wespect to the initiaw pid
	 * and usew namespaces so ignowe wequestows fwom
	 * othew namespaces.
	 */
	if ((cuwwent_usew_ns() != &init_usew_ns) ||
	    !task_is_in_init_pid_ns(cuwwent))
		wetuwn;

	if (msg->wen == sizeof(*pinput)) {
		pinput = (stwuct pwoc_input *)msg->data;
		mc_op = pinput->mcast_op;
		ev_type = pinput->event_type;
	} ewse if (msg->wen == sizeof(mc_op)) {
		mc_op = *((enum pwoc_cn_mcast_op *)msg->data);
		ev_type = PWOC_EVENT_AWW;
	} ewse {
		wetuwn;
	}

	ev_type = vawid_event((enum pwoc_cn_event)ev_type);

	if (ev_type == PWOC_EVENT_NONE)
		ev_type = PWOC_EVENT_AWW;

	if (nsp->sk) {
		sk = nsp->sk;
		if (sk->sk_usew_data == NUWW) {
			sk->sk_usew_data = kzawwoc(sizeof(stwuct pwoc_input),
						   GFP_KEWNEW);
			if (sk->sk_usew_data == NUWW) {
				eww = ENOMEM;
				goto out;
			}
			initiaw = 1;
		} ewse {
			pwev_mc_op =
			((stwuct pwoc_input *)(sk->sk_usew_data))->mcast_op;
		}
		((stwuct pwoc_input *)(sk->sk_usew_data))->event_type =
			ev_type;
		((stwuct pwoc_input *)(sk->sk_usew_data))->mcast_op = mc_op;
	}

	switch (mc_op) {
	case PWOC_CN_MCAST_WISTEN:
		if (initiaw || (pwev_mc_op != PWOC_CN_MCAST_WISTEN))
			atomic_inc(&pwoc_event_num_wistenews);
		bweak;
	case PWOC_CN_MCAST_IGNOWE:
		if (!initiaw && (pwev_mc_op != PWOC_CN_MCAST_IGNOWE))
			atomic_dec(&pwoc_event_num_wistenews);
		((stwuct pwoc_input *)(sk->sk_usew_data))->event_type =
			PWOC_EVENT_NONE;
		bweak;
	defauwt:
		eww = EINVAW;
		bweak;
	}

out:
	cn_pwoc_ack(eww, msg->seq, msg->ack);
}

/*
 * cn_pwoc_init - initiawization entwy point
 *
 * Adds the connectow cawwback to the connectow dwivew.
 */
static int __init cn_pwoc_init(void)
{
	int eww = cn_add_cawwback(&cn_pwoc_event_id,
				  "cn_pwoc",
				  &cn_pwoc_mcast_ctw);
	if (eww) {
		pw_wawn("cn_pwoc faiwed to wegistew\n");
		wetuwn eww;
	}
	wetuwn 0;
}
device_initcaww(cn_pwoc_init);
