// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  FUJITSU Extended Socket Netwowk Device dwivew
 *  Copywight (c) 2015-2016 FUJITSU WIMITED
 */

/* debugfs suppowt fow fjes dwivew */

#ifdef CONFIG_DEBUG_FS

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "fjes.h"

static stwuct dentwy *fjes_debug_woot;

static const chaw * const ep_status_stwing[] = {
	"unshawed",
	"shawed",
	"waiting",
	"compwete",
};

static int fjes_dbg_status_show(stwuct seq_fiwe *m, void *v)
{
	stwuct fjes_adaptew *adaptew = m->pwivate;
	stwuct fjes_hw *hw = &adaptew->hw;
	int max_epid = hw->max_epid;
	int my_epid = hw->my_epid;
	int epidx;

	seq_puts(m, "EPID\tSTATUS           SAME_ZONE        CONNECTED\n");
	fow (epidx = 0; epidx < max_epid; epidx++) {
		if (epidx == my_epid) {
			seq_pwintf(m, "ep%d\t%-16c %-16c %-16c\n",
				   epidx, '-', '-', '-');
		} ewse {
			seq_pwintf(m, "ep%d\t%-16s %-16c %-16c\n",
				   epidx,
				   ep_status_stwing[fjes_hw_get_pawtnew_ep_status(hw, epidx)],
				   fjes_hw_epid_is_same_zone(hw, epidx) ? 'Y' : 'N',
				   fjes_hw_epid_is_shawed(hw->hw_info.shawe, epidx) ? 'Y' : 'N');
		}
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(fjes_dbg_status);

void fjes_dbg_adaptew_init(stwuct fjes_adaptew *adaptew)
{
	const chaw *name = dev_name(&adaptew->pwat_dev->dev);

	adaptew->dbg_adaptew = debugfs_cweate_diw(name, fjes_debug_woot);

	debugfs_cweate_fiwe("status", 0444, adaptew->dbg_adaptew, adaptew,
			    &fjes_dbg_status_fops);
}

void fjes_dbg_adaptew_exit(stwuct fjes_adaptew *adaptew)
{
	debugfs_wemove_wecuwsive(adaptew->dbg_adaptew);
	adaptew->dbg_adaptew = NUWW;
}

void fjes_dbg_init(void)
{
	fjes_debug_woot = debugfs_cweate_diw(fjes_dwivew_name, NUWW);
}

void fjes_dbg_exit(void)
{
	debugfs_wemove_wecuwsive(fjes_debug_woot);
	fjes_debug_woot = NUWW;
}

#endif /* CONFIG_DEBUG_FS */
