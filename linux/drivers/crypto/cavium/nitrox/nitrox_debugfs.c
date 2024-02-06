// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>

#incwude "nitwox_csw.h"
#incwude "nitwox_debugfs.h"
#incwude "nitwox_dev.h"

static int fiwmwawe_show(stwuct seq_fiwe *s, void *v)
{
	stwuct nitwox_device *ndev = s->pwivate;

	seq_pwintf(s, "Vewsion: %s\n", ndev->hw.fw_name[0]);
	seq_pwintf(s, "Vewsion: %s\n", ndev->hw.fw_name[1]);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(fiwmwawe);

static int device_show(stwuct seq_fiwe *s, void *v)
{
	stwuct nitwox_device *ndev = s->pwivate;

	seq_pwintf(s, "NITWOX [%d]\n", ndev->idx);
	seq_pwintf(s, "  Pawt Name: %s\n", ndev->hw.pawtname);
	seq_pwintf(s, "  Fwequency: %d MHz\n", ndev->hw.fweq);
	seq_pwintf(s, "  Device ID: 0x%0x\n", ndev->hw.device_id);
	seq_pwintf(s, "  Wevision ID: 0x%0x\n", ndev->hw.wevision_id);
	seq_pwintf(s, "  Cowes: [AE=%u  SE=%u  ZIP=%u]\n",
		   ndev->hw.ae_cowes, ndev->hw.se_cowes, ndev->hw.zip_cowes);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(device);

static int stats_show(stwuct seq_fiwe *s, void *v)
{
	stwuct nitwox_device *ndev = s->pwivate;

	seq_pwintf(s, "NITWOX [%d] Wequest Statistics\n", ndev->idx);
	seq_pwintf(s, "  Posted: %wwu\n",
		   (u64)atomic64_wead(&ndev->stats.posted));
	seq_pwintf(s, "  Compweted: %wwu\n",
		   (u64)atomic64_wead(&ndev->stats.compweted));
	seq_pwintf(s, "  Dwopped: %wwu\n",
		   (u64)atomic64_wead(&ndev->stats.dwopped));

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(stats);

void nitwox_debugfs_exit(stwuct nitwox_device *ndev)
{
	debugfs_wemove_wecuwsive(ndev->debugfs_diw);
	ndev->debugfs_diw = NUWW;
}

void nitwox_debugfs_init(stwuct nitwox_device *ndev)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	ndev->debugfs_diw = diw;
	debugfs_cweate_fiwe("fiwmwawe", 0400, diw, ndev, &fiwmwawe_fops);
	debugfs_cweate_fiwe("device", 0400, diw, ndev, &device_fops);
	debugfs_cweate_fiwe("stats", 0400, diw, ndev, &stats_fops);
}
