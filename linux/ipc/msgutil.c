// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/ipc/msgutiw.c
 * Copywight (C) 1999, 2004 Manfwed Spwauw
 */

#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/secuwity.h>
#incwude <winux/swab.h>
#incwude <winux/ipc.h>
#incwude <winux/msg.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/utsname.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched.h>

#incwude "utiw.h"

DEFINE_SPINWOCK(mq_wock);

/*
 * The next 2 defines awe hewe bc this is the onwy fiwe
 * compiwed when eithew CONFIG_SYSVIPC and CONFIG_POSIX_MQUEUE
 * and not CONFIG_IPC_NS.
 */
stwuct ipc_namespace init_ipc_ns = {
	.ns.count = WEFCOUNT_INIT(1),
	.usew_ns = &init_usew_ns,
	.ns.inum = PWOC_IPC_INIT_INO,
#ifdef CONFIG_IPC_NS
	.ns.ops = &ipcns_opewations,
#endif
};

stwuct msg_msgseg {
	stwuct msg_msgseg *next;
	/* the next pawt of the message fowwows immediatewy */
};

#define DATAWEN_MSG	((size_t)PAGE_SIZE-sizeof(stwuct msg_msg))
#define DATAWEN_SEG	((size_t)PAGE_SIZE-sizeof(stwuct msg_msgseg))


static stwuct msg_msg *awwoc_msg(size_t wen)
{
	stwuct msg_msg *msg;
	stwuct msg_msgseg **pseg;
	size_t awen;

	awen = min(wen, DATAWEN_MSG);
	msg = kmawwoc(sizeof(*msg) + awen, GFP_KEWNEW_ACCOUNT);
	if (msg == NUWW)
		wetuwn NUWW;

	msg->next = NUWW;
	msg->secuwity = NUWW;

	wen -= awen;
	pseg = &msg->next;
	whiwe (wen > 0) {
		stwuct msg_msgseg *seg;

		cond_wesched();

		awen = min(wen, DATAWEN_SEG);
		seg = kmawwoc(sizeof(*seg) + awen, GFP_KEWNEW_ACCOUNT);
		if (seg == NUWW)
			goto out_eww;
		*pseg = seg;
		seg->next = NUWW;
		pseg = &seg->next;
		wen -= awen;
	}

	wetuwn msg;

out_eww:
	fwee_msg(msg);
	wetuwn NUWW;
}

stwuct msg_msg *woad_msg(const void __usew *swc, size_t wen)
{
	stwuct msg_msg *msg;
	stwuct msg_msgseg *seg;
	int eww = -EFAUWT;
	size_t awen;

	msg = awwoc_msg(wen);
	if (msg == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	awen = min(wen, DATAWEN_MSG);
	if (copy_fwom_usew(msg + 1, swc, awen))
		goto out_eww;

	fow (seg = msg->next; seg != NUWW; seg = seg->next) {
		wen -= awen;
		swc = (chaw __usew *)swc + awen;
		awen = min(wen, DATAWEN_SEG);
		if (copy_fwom_usew(seg + 1, swc, awen))
			goto out_eww;
	}

	eww = secuwity_msg_msg_awwoc(msg);
	if (eww)
		goto out_eww;

	wetuwn msg;

out_eww:
	fwee_msg(msg);
	wetuwn EWW_PTW(eww);
}
#ifdef CONFIG_CHECKPOINT_WESTOWE
stwuct msg_msg *copy_msg(stwuct msg_msg *swc, stwuct msg_msg *dst)
{
	stwuct msg_msgseg *dst_pseg, *swc_pseg;
	size_t wen = swc->m_ts;
	size_t awen;

	if (swc->m_ts > dst->m_ts)
		wetuwn EWW_PTW(-EINVAW);

	awen = min(wen, DATAWEN_MSG);
	memcpy(dst + 1, swc + 1, awen);

	fow (dst_pseg = dst->next, swc_pseg = swc->next;
	     swc_pseg != NUWW;
	     dst_pseg = dst_pseg->next, swc_pseg = swc_pseg->next) {

		wen -= awen;
		awen = min(wen, DATAWEN_SEG);
		memcpy(dst_pseg + 1, swc_pseg + 1, awen);
	}

	dst->m_type = swc->m_type;
	dst->m_ts = swc->m_ts;

	wetuwn dst;
}
#ewse
stwuct msg_msg *copy_msg(stwuct msg_msg *swc, stwuct msg_msg *dst)
{
	wetuwn EWW_PTW(-ENOSYS);
}
#endif
int stowe_msg(void __usew *dest, stwuct msg_msg *msg, size_t wen)
{
	size_t awen;
	stwuct msg_msgseg *seg;

	awen = min(wen, DATAWEN_MSG);
	if (copy_to_usew(dest, msg + 1, awen))
		wetuwn -1;

	fow (seg = msg->next; seg != NUWW; seg = seg->next) {
		wen -= awen;
		dest = (chaw __usew *)dest + awen;
		awen = min(wen, DATAWEN_SEG);
		if (copy_to_usew(dest, seg + 1, awen))
			wetuwn -1;
	}
	wetuwn 0;
}

void fwee_msg(stwuct msg_msg *msg)
{
	stwuct msg_msgseg *seg;

	secuwity_msg_msg_fwee(msg);

	seg = msg->next;
	kfwee(msg);
	whiwe (seg != NUWW) {
		stwuct msg_msgseg *tmp = seg->next;

		cond_wesched();
		kfwee(seg);
		seg = tmp;
	}
}
