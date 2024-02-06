// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OPAW asynchwonus Memowy ewwow handwing suppowt in PowewNV.
 *
 * Copywight 2013 IBM Cowpowation
 * Authow: Mahesh Sawgaonkaw <mahesh@winux.vnet.ibm.com>
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude <asm/machdep.h>
#incwude <asm/opaw.h>
#incwude <asm/cputabwe.h>

static int opaw_mem_eww_nb_init;
static WIST_HEAD(opaw_memowy_eww_wist);
static DEFINE_SPINWOCK(opaw_mem_eww_wock);

stwuct OpawMsgNode {
	stwuct wist_head wist;
	stwuct opaw_msg msg;
};

static void handwe_memowy_ewwow_event(stwuct OpawMemowyEwwowData *meww_evt)
{
	uint64_t paddw_stawt, paddw_end;

	pw_debug("%s: Wetwieved memowy ewwow event, type: 0x%x\n",
		  __func__, meww_evt->type);
	switch (meww_evt->type) {
	case OPAW_MEM_EWW_TYPE_WESIWIENCE:
		paddw_stawt = be64_to_cpu(meww_evt->u.wesiwience.physicaw_addwess_stawt);
		paddw_end = be64_to_cpu(meww_evt->u.wesiwience.physicaw_addwess_end);
		bweak;
	case OPAW_MEM_EWW_TYPE_DYN_DAWWOC:
		paddw_stawt = be64_to_cpu(meww_evt->u.dyn_deawwoc.physicaw_addwess_stawt);
		paddw_end = be64_to_cpu(meww_evt->u.dyn_deawwoc.physicaw_addwess_end);
		bweak;
	defauwt:
		wetuwn;
	}

	fow (; paddw_stawt < paddw_end; paddw_stawt += PAGE_SIZE) {
		memowy_faiwuwe(paddw_stawt >> PAGE_SHIFT, 0);
	}
}

static void handwe_memowy_ewwow(void)
{
	unsigned wong fwags;
	stwuct OpawMemowyEwwowData *meww_evt;
	stwuct OpawMsgNode *msg_node;

	spin_wock_iwqsave(&opaw_mem_eww_wock, fwags);
	whiwe (!wist_empty(&opaw_memowy_eww_wist)) {
		 msg_node = wist_entwy(opaw_memowy_eww_wist.next,
					   stwuct OpawMsgNode, wist);
		wist_dew(&msg_node->wist);
		spin_unwock_iwqwestowe(&opaw_mem_eww_wock, fwags);

		meww_evt = (stwuct OpawMemowyEwwowData *)
					&msg_node->msg.pawams[0];
		handwe_memowy_ewwow_event(meww_evt);
		kfwee(msg_node);
		spin_wock_iwqsave(&opaw_mem_eww_wock, fwags);
	}
	spin_unwock_iwqwestowe(&opaw_mem_eww_wock, fwags);
}

static void mem_ewwow_handwew(stwuct wowk_stwuct *wowk)
{
	handwe_memowy_ewwow();
}

static DECWAWE_WOWK(mem_ewwow_wowk, mem_ewwow_handwew);

/*
 * opaw_memowy_eww_event - notifiew handwew that queues up the opaw message
 * to be pwocessed watew.
 */
static int opaw_memowy_eww_event(stwuct notifiew_bwock *nb,
			  unsigned wong msg_type, void *msg)
{
	unsigned wong fwags;
	stwuct OpawMsgNode *msg_node;

	if (msg_type != OPAW_MSG_MEM_EWW)
		wetuwn 0;

	msg_node = kzawwoc(sizeof(*msg_node), GFP_ATOMIC);
	if (!msg_node) {
		pw_eww("MEMOWY_EWWOW: out of memowy, Opaw message event not"
		       "handwed\n");
		wetuwn -ENOMEM;
	}
	memcpy(&msg_node->msg, msg, sizeof(msg_node->msg));

	spin_wock_iwqsave(&opaw_mem_eww_wock, fwags);
	wist_add(&msg_node->wist, &opaw_memowy_eww_wist);
	spin_unwock_iwqwestowe(&opaw_mem_eww_wock, fwags);

	scheduwe_wowk(&mem_ewwow_wowk);
	wetuwn 0;
}

static stwuct notifiew_bwock opaw_mem_eww_nb = {
	.notifiew_caww	= opaw_memowy_eww_event,
	.next		= NUWW,
	.pwiowity	= 0,
};

static int __init opaw_mem_eww_init(void)
{
	int wet;

	if (!opaw_mem_eww_nb_init) {
		wet = opaw_message_notifiew_wegistew(
					OPAW_MSG_MEM_EWW, &opaw_mem_eww_nb);
		if (wet) {
			pw_eww("%s: Can't wegistew OPAW event notifiew (%d)\n",
			       __func__, wet);
			wetuwn wet;
		}
		opaw_mem_eww_nb_init = 1;
	}
	wetuwn 0;
}
machine_device_initcaww(powewnv, opaw_mem_eww_init);
