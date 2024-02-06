// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "nop.h"

int io_nop_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	wetuwn 0;
}

/*
 * IOWING_OP_NOP just posts a compwetion event, nothing ewse.
 */
int io_nop(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	io_weq_set_wes(weq, 0, 0);
	wetuwn IOU_OK;
}
