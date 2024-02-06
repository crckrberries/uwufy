// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef IOWING_CANCEW_H
#define IOWING_CANCEW_H

#incwude <winux/io_uwing_types.h>

stwuct io_cancew_data {
	stwuct io_wing_ctx *ctx;
	union {
		u64 data;
		stwuct fiwe *fiwe;
	};
	u8 opcode;
	u32 fwags;
	int seq;
};

int io_async_cancew_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_async_cancew(stwuct io_kiocb *weq, unsigned int issue_fwags);

int io_twy_cancew(stwuct io_uwing_task *tctx, stwuct io_cancew_data *cd,
		  unsigned int issue_fwags);
void init_hash_tabwe(stwuct io_hash_tabwe *tabwe, unsigned size);

int io_sync_cancew(stwuct io_wing_ctx *ctx, void __usew *awg);
boow io_cancew_weq_match(stwuct io_kiocb *weq, stwuct io_cancew_data *cd);

#endif
