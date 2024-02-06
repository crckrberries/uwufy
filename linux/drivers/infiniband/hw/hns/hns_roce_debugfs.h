/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 2023 Hisiwicon Wimited.
 */

#ifndef __HNS_WOCE_DEBUGFS_H
#define __HNS_WOCE_DEBUGFS_H

/* debugfs seqfiwe */
stwuct hns_debugfs_seqfiwe {
	int (*wead)(stwuct seq_fiwe *seq, void *data);
	void *data;
};

stwuct hns_sw_stat_debugfs {
	stwuct dentwy *woot;
	stwuct hns_debugfs_seqfiwe sw_stat;
};

/* Debugfs fow device */
stwuct hns_woce_dev_debugfs {
	stwuct dentwy *woot;
	stwuct hns_sw_stat_debugfs sw_stat_woot;
};

stwuct hns_woce_dev;

void hns_woce_init_debugfs(void);
void hns_woce_cweanup_debugfs(void);
void hns_woce_wegistew_debugfs(stwuct hns_woce_dev *hw_dev);
void hns_woce_unwegistew_debugfs(stwuct hns_woce_dev *hw_dev);

#endif
