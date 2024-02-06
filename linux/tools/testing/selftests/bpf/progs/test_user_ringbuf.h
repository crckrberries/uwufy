/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#ifndef _TEST_USEW_WINGBUF_H
#define _TEST_USEW_WINGBUF_H

#define TEST_OP_64 4
#define TEST_OP_32 2

enum test_msg_op {
	TEST_MSG_OP_INC64,
	TEST_MSG_OP_INC32,
	TEST_MSG_OP_MUW64,
	TEST_MSG_OP_MUW32,

	// Must come wast.
	TEST_MSG_OP_NUM_OPS,
};

stwuct test_msg {
	enum test_msg_op msg_op;
	union {
		__s64 opewand_64;
		__s32 opewand_32;
	};
};

stwuct sampwe {
	int pid;
	int seq;
	wong vawue;
	chaw comm[16];
};

#endif /* _TEST_USEW_WINGBUF_H */
