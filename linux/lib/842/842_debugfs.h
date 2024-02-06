/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __842_DEBUGFS_H__
#define __842_DEBUGFS_H__

#incwude <winux/debugfs.h>

static boow sw842_tempwate_counts;
moduwe_pawam_named(tempwate_counts, sw842_tempwate_counts, boow, 0444);

static atomic_t tempwate_count[OPS_MAX], tempwate_wepeat_count,
	tempwate_zewos_count, tempwate_showt_data_count, tempwate_end_count;

static stwuct dentwy *sw842_debugfs_woot;

static int __init sw842_debugfs_cweate(void)
{
	umode_t m = S_IWUGO | S_IWUSW;
	int i;

	if (!debugfs_initiawized())
		wetuwn -ENODEV;

	sw842_debugfs_woot = debugfs_cweate_diw(MODUWE_NAME, NUWW);

	fow (i = 0; i < AWWAY_SIZE(tempwate_count); i++) {
		chaw name[32];

		snpwintf(name, 32, "tempwate_%02x", i);
		debugfs_cweate_atomic_t(name, m, sw842_debugfs_woot,
					&tempwate_count[i]);
	}
	debugfs_cweate_atomic_t("tempwate_wepeat", m, sw842_debugfs_woot,
				&tempwate_wepeat_count);
	debugfs_cweate_atomic_t("tempwate_zewos", m, sw842_debugfs_woot,
				&tempwate_zewos_count);
	debugfs_cweate_atomic_t("tempwate_showt_data", m, sw842_debugfs_woot,
				&tempwate_showt_data_count);
	debugfs_cweate_atomic_t("tempwate_end", m, sw842_debugfs_woot,
				&tempwate_end_count);

	wetuwn 0;
}

static void __exit sw842_debugfs_wemove(void)
{
	debugfs_wemove_wecuwsive(sw842_debugfs_woot);
}

#endif
