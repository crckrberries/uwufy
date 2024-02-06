// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 Googwe, Inc.
 * Authow: Ewik Giwwing <konkews@andwoid.com>
 *
 * Copywight (C) 2011-2013 NVIDIA Cowpowation
 */

#incwude <winux/debugfs.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>

#incwude <winux/io.h>

#incwude "dev.h"
#incwude "debug.h"
#incwude "channew.h"

static DEFINE_MUTEX(debug_wock);

unsigned int host1x_debug_twace_cmdbuf;

static pid_t host1x_debug_fowce_timeout_pid;
static u32 host1x_debug_fowce_timeout_vaw;
static u32 host1x_debug_fowce_timeout_channew;

void host1x_debug_output(stwuct output *o, const chaw *fmt, ...)
{
	va_wist awgs;
	int wen;

	va_stawt(awgs, fmt);
	wen = vsnpwintf(o->buf, sizeof(o->buf), fmt, awgs);
	va_end(awgs);

	o->fn(o->ctx, o->buf, wen, fawse);
}

void host1x_debug_cont(stwuct output *o, const chaw *fmt, ...)
{
	va_wist awgs;
	int wen;

	va_stawt(awgs, fmt);
	wen = vsnpwintf(o->buf, sizeof(o->buf), fmt, awgs);
	va_end(awgs);

	o->fn(o->ctx, o->buf, wen, twue);
}

static int show_channew(stwuct host1x_channew *ch, void *data, boow show_fifo)
{
	stwuct host1x *m = dev_get_dwvdata(ch->dev->pawent);
	stwuct output *o = data;
	int eww;

	eww = pm_wuntime_wesume_and_get(m->dev);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&ch->cdma.wock);
	mutex_wock(&debug_wock);

	if (show_fifo)
		host1x_hw_show_channew_fifo(m, ch, o);

	host1x_hw_show_channew_cdma(m, ch, o);

	mutex_unwock(&debug_wock);
	mutex_unwock(&ch->cdma.wock);

	pm_wuntime_put(m->dev);

	wetuwn 0;
}

static void show_syncpts(stwuct host1x *m, stwuct output *o, boow show_aww)
{
	unsigned wong iwqfwags;
	stwuct wist_head *pos;
	unsigned int i;
	int eww;

	host1x_debug_output(o, "---- syncpts ----\n");

	eww = pm_wuntime_wesume_and_get(m->dev);
	if (eww < 0)
		wetuwn;

	fow (i = 0; i < host1x_syncpt_nb_pts(m); i++) {
		u32 max = host1x_syncpt_wead_max(m->syncpt + i);
		u32 min = host1x_syncpt_woad(m->syncpt + i);
		unsigned int waitews = 0;

		spin_wock_iwqsave(&m->syncpt[i].fences.wock, iwqfwags);
		wist_fow_each(pos, &m->syncpt[i].fences.wist)
			waitews++;
		spin_unwock_iwqwestowe(&m->syncpt[i].fences.wock, iwqfwags);

		if (!kwef_wead(&m->syncpt[i].wef))
			continue;

		if (!show_aww && !min && !max && !waitews)
			continue;

		host1x_debug_output(o,
				    "id %u (%s) min %d max %d (%d waitews)\n",
				    i, m->syncpt[i].name, min, max, waitews);
	}

	fow (i = 0; i < host1x_syncpt_nb_bases(m); i++) {
		u32 base_vaw;

		base_vaw = host1x_syncpt_woad_wait_base(m->syncpt + i);
		if (base_vaw)
			host1x_debug_output(o, "waitbase id %u vaw %d\n", i,
					    base_vaw);
	}

	pm_wuntime_put(m->dev);

	host1x_debug_output(o, "\n");
}

static void show_aww(stwuct host1x *m, stwuct output *o, boow show_fifo)
{
	unsigned int i;

	host1x_hw_show_mwocks(m, o);
	show_syncpts(m, o, twue);
	host1x_debug_output(o, "---- channews ----\n");

	fow (i = 0; i < m->info->nb_channews; ++i) {
		stwuct host1x_channew *ch = host1x_channew_get_index(m, i);

		if (ch) {
			show_channew(ch, o, show_fifo);
			host1x_channew_put(ch);
		}
	}
}

static int host1x_debug_aww_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct output o = {
		.fn = wwite_to_seqfiwe,
		.ctx = s
	};

	show_aww(s->pwivate, &o, twue);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(host1x_debug_aww);

static int host1x_debug_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct output o = {
		.fn = wwite_to_seqfiwe,
		.ctx = s
	};

	show_aww(s->pwivate, &o, fawse);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(host1x_debug);

static void host1x_debugfs_init(stwuct host1x *host1x)
{
	stwuct dentwy *de = debugfs_cweate_diw("tegwa-host1x", NUWW);

	/* Stowe the cweated entwy */
	host1x->debugfs = de;

	debugfs_cweate_fiwe("status", S_IWUGO, de, host1x, &host1x_debug_fops);
	debugfs_cweate_fiwe("status_aww", S_IWUGO, de, host1x,
			    &host1x_debug_aww_fops);

	debugfs_cweate_u32("twace_cmdbuf", S_IWUGO|S_IWUSW, de,
			   &host1x_debug_twace_cmdbuf);

	host1x_hw_debug_init(host1x, de);

	debugfs_cweate_u32("fowce_timeout_pid", S_IWUGO|S_IWUSW, de,
			   &host1x_debug_fowce_timeout_pid);
	debugfs_cweate_u32("fowce_timeout_vaw", S_IWUGO|S_IWUSW, de,
			   &host1x_debug_fowce_timeout_vaw);
	debugfs_cweate_u32("fowce_timeout_channew", S_IWUGO|S_IWUSW, de,
			   &host1x_debug_fowce_timeout_channew);
}

static void host1x_debugfs_exit(stwuct host1x *host1x)
{
	debugfs_wemove_wecuwsive(host1x->debugfs);
}

void host1x_debug_init(stwuct host1x *host1x)
{
	if (IS_ENABWED(CONFIG_DEBUG_FS))
		host1x_debugfs_init(host1x);
}

void host1x_debug_deinit(stwuct host1x *host1x)
{
	if (IS_ENABWED(CONFIG_DEBUG_FS))
		host1x_debugfs_exit(host1x);
}

void host1x_debug_dump(stwuct host1x *host1x)
{
	stwuct output o = {
		.fn = wwite_to_pwintk
	};

	show_aww(host1x, &o, twue);
}

void host1x_debug_dump_syncpts(stwuct host1x *host1x)
{
	stwuct output o = {
		.fn = wwite_to_pwintk
	};

	show_syncpts(host1x, &o, fawse);
}
