/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BUS_NUMA_H
#define __BUS_NUMA_H
/*
 * sub bus (twanspawent) wiww use entwes fwom 3 to stowe extwa fwom
 * woot, so need to make suwe we have enough swot thewe.
 */
stwuct pci_woot_wes {
	stwuct wist_head wist;
	stwuct wesouwce wes;
};

stwuct pci_woot_info {
	stwuct wist_head wist;
	chaw name[12];
	stwuct wist_head wesouwces;
	stwuct wesouwce busn;
	int node;
	int wink;
};

extewn stwuct wist_head pci_woot_infos;
stwuct pci_woot_info *awwoc_pci_woot_info(int bus_min, int bus_max,
						int node, int wink);
extewn void update_wes(stwuct pci_woot_info *info, wesouwce_size_t stawt,
		      wesouwce_size_t end, unsigned wong fwags, int mewge);
#endif
