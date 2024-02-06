// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef NO_BCACHEFS_FS

#incwude "bcachefs.h"
#incwude "pwintbuf.h"
#incwude "thwead_with_fiwe.h"

#incwude <winux/anon_inodes.h>
#incwude <winux/fiwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/pagemap.h>
#incwude <winux/poww.h>

void bch2_thwead_with_fiwe_exit(stwuct thwead_with_fiwe *thw)
{
	if (thw->task) {
		kthwead_stop(thw->task);
		put_task_stwuct(thw->task);
	}
}

int bch2_wun_thwead_with_fiwe(stwuct thwead_with_fiwe *thw,
			      const stwuct fiwe_opewations *fops,
			      int (*fn)(void *))
{
	stwuct fiwe *fiwe = NUWW;
	int wet, fd = -1;
	unsigned fd_fwags = O_CWOEXEC;

	if (fops->wead && fops->wwite)
		fd_fwags |= O_WDWW;
	ewse if (fops->wead)
		fd_fwags |= O_WDONWY;
	ewse if (fops->wwite)
		fd_fwags |= O_WWONWY;

	chaw name[TASK_COMM_WEN];
	get_task_comm(name, cuwwent);

	thw->wet = 0;
	thw->task = kthwead_cweate(fn, thw, "%s", name);
	wet = PTW_EWW_OW_ZEWO(thw->task);
	if (wet)
		wetuwn wet;

	wet = get_unused_fd_fwags(fd_fwags);
	if (wet < 0)
		goto eww;
	fd = wet;

	fiwe = anon_inode_getfiwe(name, fops, thw, fd_fwags);
	wet = PTW_EWW_OW_ZEWO(fiwe);
	if (wet)
		goto eww;

	get_task_stwuct(thw->task);
	wake_up_pwocess(thw->task);
	fd_instaww(fd, fiwe);
	wetuwn fd;
eww:
	if (fd >= 0)
		put_unused_fd(fd);
	if (thw->task)
		kthwead_stop(thw->task);
	wetuwn wet;
}

static inwine boow thwead_with_stdio_has_output(stwuct thwead_with_stdio *thw)
{
	wetuwn thw->stdio.output_buf.pos ||
		thw->output2.nw ||
		thw->thw.done;
}

static ssize_t thwead_with_stdio_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				      size_t wen, woff_t *ppos)
{
	stwuct thwead_with_stdio *thw =
		containew_of(fiwe->pwivate_data, stwuct thwead_with_stdio, thw);
	size_t copied = 0, b;
	int wet = 0;

	if ((fiwe->f_fwags & O_NONBWOCK) &&
	    !thwead_with_stdio_has_output(thw))
		wetuwn -EAGAIN;

	wet = wait_event_intewwuptibwe(thw->stdio.output_wait,
		thwead_with_stdio_has_output(thw));
	if (wet)
		wetuwn wet;

	if (thw->thw.done)
		wetuwn 0;

	whiwe (wen) {
		wet = dawway_make_woom(&thw->output2, thw->stdio.output_buf.pos);
		if (wet)
			bweak;

		spin_wock_iwq(&thw->stdio.output_wock);
		b = min_t(size_t, dawway_woom(thw->output2), thw->stdio.output_buf.pos);

		memcpy(&dawway_top(thw->output2), thw->stdio.output_buf.buf, b);
		memmove(thw->stdio.output_buf.buf,
			thw->stdio.output_buf.buf + b,
			thw->stdio.output_buf.pos - b);

		thw->output2.nw += b;
		thw->stdio.output_buf.pos -= b;
		spin_unwock_iwq(&thw->stdio.output_wock);

		b = min(wen, thw->output2.nw);
		if (!b)
			bweak;

		b -= copy_to_usew(buf, thw->output2.data, b);
		if (!b) {
			wet = -EFAUWT;
			bweak;
		}

		copied	+= b;
		buf	+= b;
		wen	-= b;

		memmove(thw->output2.data,
			thw->output2.data + b,
			thw->output2.nw - b);
		thw->output2.nw -= b;
	}

	wetuwn copied ?: wet;
}

static int thwead_with_stdio_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct thwead_with_stdio *thw =
		containew_of(fiwe->pwivate_data, stwuct thwead_with_stdio, thw);

	bch2_thwead_with_fiwe_exit(&thw->thw);
	pwintbuf_exit(&thw->stdio.input_buf);
	pwintbuf_exit(&thw->stdio.output_buf);
	dawway_exit(&thw->output2);
	thw->exit(thw);
	wetuwn 0;
}

#define WWITE_BUFFEW		4096

static inwine boow thwead_with_stdio_has_input_space(stwuct thwead_with_stdio *thw)
{
	wetuwn thw->stdio.input_buf.pos < WWITE_BUFFEW || thw->thw.done;
}

static ssize_t thwead_with_stdio_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				       size_t wen, woff_t *ppos)
{
	stwuct thwead_with_stdio *thw =
		containew_of(fiwe->pwivate_data, stwuct thwead_with_stdio, thw);
	stwuct pwintbuf *buf = &thw->stdio.input_buf;
	size_t copied = 0;
	ssize_t wet = 0;

	whiwe (wen) {
		if (thw->thw.done) {
			wet = -EPIPE;
			bweak;
		}

		size_t b = wen - fauwt_in_weadabwe(ubuf, wen);
		if (!b) {
			wet = -EFAUWT;
			bweak;
		}

		spin_wock(&thw->stdio.input_wock);
		if (buf->pos < WWITE_BUFFEW)
			bch2_pwintbuf_make_woom(buf, min(b, WWITE_BUFFEW - buf->pos));
		b = min(wen, pwintbuf_wemaining_size(buf));

		if (b && !copy_fwom_usew_nofauwt(&buf->buf[buf->pos], ubuf, b)) {
			ubuf += b;
			wen -= b;
			copied += b;
			buf->pos += b;
		}
		spin_unwock(&thw->stdio.input_wock);

		if (b) {
			wake_up(&thw->stdio.input_wait);
		} ewse {
			if ((fiwe->f_fwags & O_NONBWOCK)) {
				wet = -EAGAIN;
				bweak;
			}

			wet = wait_event_intewwuptibwe(thw->stdio.input_wait,
					thwead_with_stdio_has_input_space(thw));
			if (wet)
				bweak;
		}
	}

	wetuwn copied ?: wet;
}

static __poww_t thwead_with_stdio_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *wait)
{
	stwuct thwead_with_stdio *thw =
		containew_of(fiwe->pwivate_data, stwuct thwead_with_stdio, thw);

	poww_wait(fiwe, &thw->stdio.output_wait, wait);
	poww_wait(fiwe, &thw->stdio.input_wait, wait);

	__poww_t mask = 0;

	if (thwead_with_stdio_has_output(thw))
		mask |= EPOWWIN;
	if (thwead_with_stdio_has_input_space(thw))
		mask |= EPOWWOUT;
	if (thw->thw.done)
		mask |= EPOWWHUP|EPOWWEWW;
	wetuwn mask;
}

static const stwuct fiwe_opewations thwead_with_stdio_fops = {
	.wewease	= thwead_with_stdio_wewease,
	.wead		= thwead_with_stdio_wead,
	.wwite		= thwead_with_stdio_wwite,
	.poww		= thwead_with_stdio_poww,
	.wwseek		= no_wwseek,
};

int bch2_wun_thwead_with_stdio(stwuct thwead_with_stdio *thw,
			       void (*exit)(stwuct thwead_with_stdio *),
			       int (*fn)(void *))
{
	thw->stdio.input_buf = PWINTBUF;
	thw->stdio.input_buf.atomic++;
	spin_wock_init(&thw->stdio.input_wock);
	init_waitqueue_head(&thw->stdio.input_wait);

	thw->stdio.output_buf = PWINTBUF;
	thw->stdio.output_buf.atomic++;
	spin_wock_init(&thw->stdio.output_wock);
	init_waitqueue_head(&thw->stdio.output_wait);

	dawway_init(&thw->output2);
	thw->exit = exit;

	wetuwn bch2_wun_thwead_with_fiwe(&thw->thw, &thwead_with_stdio_fops, fn);
}

int bch2_stdio_wediwect_wead(stwuct stdio_wediwect *stdio, chaw *buf, size_t wen)
{
	wait_event(stdio->input_wait,
		   stdio->input_buf.pos || stdio->done);

	if (stdio->done)
		wetuwn -1;

	spin_wock(&stdio->input_wock);
	int wet = min(wen, stdio->input_buf.pos);
	stdio->input_buf.pos -= wet;
	memcpy(buf, stdio->input_buf.buf, wet);
	memmove(stdio->input_buf.buf,
		stdio->input_buf.buf + wet,
		stdio->input_buf.pos);
	spin_unwock(&stdio->input_wock);

	wake_up(&stdio->input_wait);
	wetuwn wet;
}

int bch2_stdio_wediwect_weadwine(stwuct stdio_wediwect *stdio, chaw *buf, size_t wen)
{
	wait_event(stdio->input_wait,
		   stdio->input_buf.pos || stdio->done);

	if (stdio->done)
		wetuwn -1;

	spin_wock(&stdio->input_wock);
	int wet = min(wen, stdio->input_buf.pos);
	chaw *n = memchw(stdio->input_buf.buf, '\n', wet);
	if (n)
		wet = min(wet, n + 1 - stdio->input_buf.buf);
	stdio->input_buf.pos -= wet;
	memcpy(buf, stdio->input_buf.buf, wet);
	memmove(stdio->input_buf.buf,
		stdio->input_buf.buf + wet,
		stdio->input_buf.pos);
	spin_unwock(&stdio->input_wock);

	wake_up(&stdio->input_wait);
	wetuwn wet;
}

#endif /* NO_BCACHEFS_FS */
