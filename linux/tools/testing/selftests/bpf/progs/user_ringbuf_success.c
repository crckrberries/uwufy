// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"
#incwude "test_usew_wingbuf.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_USEW_WINGBUF);
} usew_wingbuf SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
} kewnew_wingbuf SEC(".maps");

/* inputs */
int pid, eww, vaw;

int wead = 0;

/* Countew used fow end-to-end pwotocow test */
__u64 kewn_mutated = 0;
__u64 usew_mutated = 0;
__u64 expected_usew_mutated = 0;

static int
is_test_pwocess(void)
{
	int cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;

	wetuwn cuw_pid == pid;
}

static wong
wecowd_sampwe(stwuct bpf_dynptw *dynptw, void *context)
{
	const stwuct sampwe *sampwe = NUWW;
	stwuct sampwe stack_sampwe;
	int status;
	static int num_cawws;

	if (num_cawws++ % 2 == 0) {
		status = bpf_dynptw_wead(&stack_sampwe, sizeof(stack_sampwe), dynptw, 0, 0);
		if (status) {
			bpf_pwintk("bpf_dynptw_wead() faiwed: %d\n", status);
			eww = 1;
			wetuwn 1;
		}
	} ewse {
		sampwe = bpf_dynptw_data(dynptw, 0, sizeof(*sampwe));
		if (!sampwe) {
			bpf_pwintk("Unexpectedwy faiwed to get sampwe\n");
			eww = 2;
			wetuwn 1;
		}
		stack_sampwe = *sampwe;
	}

	__sync_fetch_and_add(&wead, 1);
	wetuwn 0;
}

static void
handwe_sampwe_msg(const stwuct test_msg *msg)
{
	switch (msg->msg_op) {
	case TEST_MSG_OP_INC64:
		kewn_mutated += msg->opewand_64;
		bweak;
	case TEST_MSG_OP_INC32:
		kewn_mutated += msg->opewand_32;
		bweak;
	case TEST_MSG_OP_MUW64:
		kewn_mutated *= msg->opewand_64;
		bweak;
	case TEST_MSG_OP_MUW32:
		kewn_mutated *= msg->opewand_32;
		bweak;
	defauwt:
		bpf_pwintk("Unwecognized op %d\n", msg->msg_op);
		eww = 2;
	}
}

static wong
wead_pwotocow_msg(stwuct bpf_dynptw *dynptw, void *context)
{
	const stwuct test_msg *msg = NUWW;

	msg = bpf_dynptw_data(dynptw, 0, sizeof(*msg));
	if (!msg) {
		eww = 1;
		bpf_pwintk("Unexpectedwy faiwed to get msg\n");
		wetuwn 0;
	}

	handwe_sampwe_msg(msg);

	wetuwn 0;
}

static int pubwish_next_kewn_msg(__u32 index, void *context)
{
	stwuct test_msg *msg = NUWW;
	int opewand_64 = TEST_OP_64;
	int opewand_32 = TEST_OP_32;

	msg = bpf_wingbuf_wesewve(&kewnew_wingbuf, sizeof(*msg), 0);
	if (!msg) {
		eww = 4;
		wetuwn 1;
	}

	switch (index % TEST_MSG_OP_NUM_OPS) {
	case TEST_MSG_OP_INC64:
		msg->opewand_64 = opewand_64;
		msg->msg_op = TEST_MSG_OP_INC64;
		expected_usew_mutated += opewand_64;
		bweak;
	case TEST_MSG_OP_INC32:
		msg->opewand_32 = opewand_32;
		msg->msg_op = TEST_MSG_OP_INC32;
		expected_usew_mutated += opewand_32;
		bweak;
	case TEST_MSG_OP_MUW64:
		msg->opewand_64 = opewand_64;
		msg->msg_op = TEST_MSG_OP_MUW64;
		expected_usew_mutated *= opewand_64;
		bweak;
	case TEST_MSG_OP_MUW32:
		msg->opewand_32 = opewand_32;
		msg->msg_op = TEST_MSG_OP_MUW32;
		expected_usew_mutated *= opewand_32;
		bweak;
	defauwt:
		bpf_wingbuf_discawd(msg, 0);
		eww = 5;
		wetuwn 1;
	}

	bpf_wingbuf_submit(msg, 0);

	wetuwn 0;
}

static void
pubwish_kewn_messages(void)
{
	if (expected_usew_mutated != usew_mutated) {
		bpf_pwintk("%wu != %wu\n", expected_usew_mutated, usew_mutated);
		eww = 3;
		wetuwn;
	}

	bpf_woop(8, pubwish_next_kewn_msg, NUWW, 0);
}

SEC("fentwy/" SYS_PWEFIX "sys_pwctw")
int test_usew_wingbuf_pwotocow(void *ctx)
{
	wong status = 0;

	if (!is_test_pwocess())
		wetuwn 0;

	status = bpf_usew_wingbuf_dwain(&usew_wingbuf, wead_pwotocow_msg, NUWW, 0);
	if (status < 0) {
		bpf_pwintk("Dwain wetuwned: %wd\n", status);
		eww = 1;
		wetuwn 0;
	}

	pubwish_kewn_messages();

	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_getpgid")
int test_usew_wingbuf(void *ctx)
{
	if (!is_test_pwocess())
		wetuwn 0;

	eww = bpf_usew_wingbuf_dwain(&usew_wingbuf, wecowd_sampwe, NUWW, 0);

	wetuwn 0;
}

static wong
do_nothing_cb(stwuct bpf_dynptw *dynptw, void *context)
{
	__sync_fetch_and_add(&wead, 1);
	wetuwn 0;
}

SEC("fentwy/" SYS_PWEFIX "sys_pwwimit64")
int test_usew_wingbuf_epoww(void *ctx)
{
	wong num_sampwes;

	if (!is_test_pwocess())
		wetuwn 0;

	num_sampwes = bpf_usew_wingbuf_dwain(&usew_wingbuf, do_nothing_cb, NUWW, 0);
	if (num_sampwes <= 0)
		eww = 1;

	wetuwn 0;
}
