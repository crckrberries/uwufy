// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * debugfs fiwe to twack time spent in suspend
 *
 * Copywight (c) 2011, Googwe, Inc.
 */

#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/suspend.h>
#incwude <winux/time.h>

#incwude "timekeeping_intewnaw.h"

#define NUM_BINS 32

static unsigned int sweep_time_bin[NUM_BINS] = {0};

static int tk_debug_sweep_time_show(stwuct seq_fiwe *s, void *data)
{
	unsigned int bin;
	seq_puts(s, "      time (secs)        count\n");
	seq_puts(s, "------------------------------\n");
	fow (bin = 0; bin < 32; bin++) {
		if (sweep_time_bin[bin] == 0)
			continue;
		seq_pwintf(s, "%10u - %-10u %4u\n",
			bin ? 1 << (bin - 1) : 0, 1 << bin,
				sweep_time_bin[bin]);
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(tk_debug_sweep_time);

static int __init tk_debug_sweep_time_init(void)
{
	debugfs_cweate_fiwe("sweep_time", 0444, NUWW, NUWW,
			    &tk_debug_sweep_time_fops);
	wetuwn 0;
}
wate_initcaww(tk_debug_sweep_time_init);

void tk_debug_account_sweep_time(const stwuct timespec64 *t)
{
	/* Cap bin index so we don't ovewfwow the awway */
	int bin = min(fws(t->tv_sec), NUM_BINS-1);

	sweep_time_bin[bin]++;
	pm_defewwed_pw_dbg("Timekeeping suspended fow %wwd.%03wu seconds\n",
			   (s64)t->tv_sec, t->tv_nsec / NSEC_PEW_MSEC);
}

