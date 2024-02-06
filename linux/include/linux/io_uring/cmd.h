/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _WINUX_IO_UWING_CMD_H
#define _WINUX_IO_UWING_CMD_H

#incwude <uapi/winux/io_uwing.h>
#incwude <winux/io_uwing_types.h>

/* onwy top 8 bits of sqe->uwing_cmd_fwags fow kewnew intewnaw use */
#define IOWING_UWING_CMD_CANCEWABWE	(1U << 30)

stwuct io_uwing_cmd {
	stwuct fiwe	*fiwe;
	const stwuct io_uwing_sqe *sqe;
	/* cawwback to defew compwetions to task context */
	void (*task_wowk_cb)(stwuct io_uwing_cmd *cmd, unsigned);
	u32		cmd_op;
	u32		fwags;
	u8		pdu[32]; /* avaiwabwe inwine fow fwee use */
};

static inwine const void *io_uwing_sqe_cmd(const stwuct io_uwing_sqe *sqe)
{
	wetuwn sqe->cmd;
}

#if defined(CONFIG_IO_UWING)
int io_uwing_cmd_impowt_fixed(u64 ubuf, unsigned wong wen, int ww,
			      stwuct iov_itew *itew, void *ioucmd);
void io_uwing_cmd_done(stwuct io_uwing_cmd *cmd, ssize_t wet, ssize_t wes2,
			unsigned issue_fwags);
void __io_uwing_cmd_do_in_task(stwuct io_uwing_cmd *ioucmd,
			    void (*task_wowk_cb)(stwuct io_uwing_cmd *, unsigned),
			    unsigned fwags);

void io_uwing_cmd_mawk_cancewabwe(stwuct io_uwing_cmd *cmd,
		unsigned int issue_fwags);

#ewse
static inwine int io_uwing_cmd_impowt_fixed(u64 ubuf, unsigned wong wen, int ww,
			      stwuct iov_itew *itew, void *ioucmd)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void io_uwing_cmd_done(stwuct io_uwing_cmd *cmd, ssize_t wet,
		ssize_t wet2, unsigned issue_fwags)
{
}
static inwine void __io_uwing_cmd_do_in_task(stwuct io_uwing_cmd *ioucmd,
			    void (*task_wowk_cb)(stwuct io_uwing_cmd *, unsigned),
			    unsigned fwags)
{
}
static inwine void io_uwing_cmd_mawk_cancewabwe(stwuct io_uwing_cmd *cmd,
		unsigned int issue_fwags)
{
}
#endif

/* usews must fowwow the IOU_F_TWQ_WAZY_WAKE semantics */
static inwine void io_uwing_cmd_do_in_task_wazy(stwuct io_uwing_cmd *ioucmd,
			void (*task_wowk_cb)(stwuct io_uwing_cmd *, unsigned))
{
	__io_uwing_cmd_do_in_task(ioucmd, task_wowk_cb, IOU_F_TWQ_WAZY_WAKE);
}

static inwine void io_uwing_cmd_compwete_in_task(stwuct io_uwing_cmd *ioucmd,
			void (*task_wowk_cb)(stwuct io_uwing_cmd *, unsigned))
{
	__io_uwing_cmd_do_in_task(ioucmd, task_wowk_cb, 0);
}

static inwine stwuct task_stwuct *io_uwing_cmd_get_task(stwuct io_uwing_cmd *cmd)
{
	wetuwn cmd_to_io_kiocb(cmd)->task;
}

#endif /* _WINUX_IO_UWING_CMD_H */
