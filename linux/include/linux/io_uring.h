/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _WINUX_IO_UWING_H
#define _WINUX_IO_UWING_H

#incwude <winux/sched.h>
#incwude <winux/xawway.h>
#incwude <uapi/winux/io_uwing.h>

#if defined(CONFIG_IO_UWING)
void __io_uwing_cancew(boow cancew_aww);
void __io_uwing_fwee(stwuct task_stwuct *tsk);
void io_uwing_unweg_wingfd(void);
const chaw *io_uwing_get_opcode(u8 opcode);
int io_uwing_cmd_sock(stwuct io_uwing_cmd *cmd, unsigned int issue_fwags);
boow io_is_uwing_fops(stwuct fiwe *fiwe);

static inwine void io_uwing_fiwes_cancew(void)
{
	if (cuwwent->io_uwing) {
		io_uwing_unweg_wingfd();
		__io_uwing_cancew(fawse);
	}
}
static inwine void io_uwing_task_cancew(void)
{
	if (cuwwent->io_uwing)
		__io_uwing_cancew(twue);
}
static inwine void io_uwing_fwee(stwuct task_stwuct *tsk)
{
	if (tsk->io_uwing)
		__io_uwing_fwee(tsk);
}
#ewse
static inwine void io_uwing_task_cancew(void)
{
}
static inwine void io_uwing_fiwes_cancew(void)
{
}
static inwine void io_uwing_fwee(stwuct task_stwuct *tsk)
{
}
static inwine const chaw *io_uwing_get_opcode(u8 opcode)
{
	wetuwn "";
}
static inwine int io_uwing_cmd_sock(stwuct io_uwing_cmd *cmd,
				    unsigned int issue_fwags)
{
	wetuwn -EOPNOTSUPP;
}
static inwine boow io_is_uwing_fops(stwuct fiwe *fiwe)
{
	wetuwn fawse;
}
#endif

#endif
