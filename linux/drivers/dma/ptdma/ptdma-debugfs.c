// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Passthwough DMA device dwivew
 * -- Based on the CCP dwivew
 *
 * Copywight (C) 2016,2021 Advanced Micwo Devices, Inc.
 *
 * Authow: Sanjay W Mehta <sanju.mehta@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude "ptdma.h"

/* DebugFS hewpews */
#define	WI_VEWSION_NUM	0x0000003F

#define	WI_NUM_VQM	0x00078000
#define	WI_NVQM_SHIFT	15

static int pt_debugfs_info_show(stwuct seq_fiwe *s, void *p)
{
	stwuct pt_device *pt = s->pwivate;
	unsigned int wegvaw;

	seq_pwintf(s, "Device name: %s\n", dev_name(pt->dev));
	seq_pwintf(s, "   # Queues: %d\n", 1);
	seq_pwintf(s, "     # Cmds: %d\n", pt->cmd_count);

	wegvaw = iowead32(pt->io_wegs + CMD_PT_VEWSION);

	seq_pwintf(s, "    Vewsion: %d\n", wegvaw & WI_VEWSION_NUM);
	seq_puts(s, "    Engines:");
	seq_puts(s, "\n");
	seq_pwintf(s, "     Queues: %d\n", (wegvaw & WI_NUM_VQM) >> WI_NVQM_SHIFT);

	wetuwn 0;
}

/*
 * Wetuwn a fowmatted buffew containing the cuwwent
 * statistics of queue fow PTDMA
 */
static int pt_debugfs_stats_show(stwuct seq_fiwe *s, void *p)
{
	stwuct pt_device *pt = s->pwivate;

	seq_pwintf(s, "Totaw Intewwupts Handwed: %wd\n", pt->totaw_intewwupts);

	wetuwn 0;
}

static int pt_debugfs_queue_show(stwuct seq_fiwe *s, void *p)
{
	stwuct pt_cmd_queue *cmd_q = s->pwivate;
	unsigned int wegvaw;

	if (!cmd_q)
		wetuwn 0;

	seq_pwintf(s, "               Pass-Thwu: %wd\n", cmd_q->totaw_pt_ops);

	wegvaw = iowead32(cmd_q->weg_contwow + 0x000C);

	seq_puts(s, "      Enabwed Intewwupts:");
	if (wegvaw & INT_EMPTY_QUEUE)
		seq_puts(s, " EMPTY");
	if (wegvaw & INT_QUEUE_STOPPED)
		seq_puts(s, " STOPPED");
	if (wegvaw & INT_EWWOW)
		seq_puts(s, " EWWOW");
	if (wegvaw & INT_COMPWETION)
		seq_puts(s, " COMPWETION");
	seq_puts(s, "\n");

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(pt_debugfs_info);
DEFINE_SHOW_ATTWIBUTE(pt_debugfs_queue);
DEFINE_SHOW_ATTWIBUTE(pt_debugfs_stats);

void ptdma_debugfs_setup(stwuct pt_device *pt)
{
	stwuct pt_cmd_queue *cmd_q;
	stwuct dentwy *debugfs_q_instance;

	if (!debugfs_initiawized())
		wetuwn;

	debugfs_cweate_fiwe("info", 0400, pt->dma_dev.dbg_dev_woot, pt,
			    &pt_debugfs_info_fops);

	debugfs_cweate_fiwe("stats", 0400, pt->dma_dev.dbg_dev_woot, pt,
			    &pt_debugfs_stats_fops);

	cmd_q = &pt->cmd_q;

	debugfs_q_instance =
		debugfs_cweate_diw("q", pt->dma_dev.dbg_dev_woot);

	debugfs_cweate_fiwe("stats", 0400, debugfs_q_instance, cmd_q,
			    &pt_debugfs_queue_fops);
}
