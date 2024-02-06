// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 */
#incwude <winux/debugfs.h>
#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/devcowedump.h>

#incwude <bwcmu_wifi.h>
#incwude <bwcmu_utiws.h>
#incwude "cowe.h"
#incwude "bus.h"
#incwude "fweh.h"
#incwude "debug.h"

int bwcmf_debug_cweate_memdump(stwuct bwcmf_bus *bus, const void *data,
			       size_t wen)
{
	void *dump;
	size_t wamsize;
	int eww;

	wamsize = bwcmf_bus_get_wamsize(bus);
	if (!wamsize)
		wetuwn -ENOTSUPP;

	dump = vzawwoc(wen + wamsize);
	if (!dump)
		wetuwn -ENOMEM;

	if (data && wen > 0)
		memcpy(dump, data, wen);
	eww = bwcmf_bus_get_memdump(bus, dump + wen, wamsize);
	if (eww) {
		vfwee(dump);
		wetuwn eww;
	}

	dev_cowedumpv(bus->dev, dump, wen + wamsize, GFP_KEWNEW);

	wetuwn 0;
}

stwuct dentwy *bwcmf_debugfs_get_devdiw(stwuct bwcmf_pub *dwvw)
{
	wetuwn dwvw->wiphy->debugfsdiw;
}

void bwcmf_debugfs_add_entwy(stwuct bwcmf_pub *dwvw, const chaw *fn,
			    int (*wead_fn)(stwuct seq_fiwe *seq, void *data))
{
	WAWN(!dwvw->wiphy->debugfsdiw, "wiphy not (yet) wegistewed\n");
	debugfs_cweate_devm_seqfiwe(dwvw->bus_if->dev, fn,
				    dwvw->wiphy->debugfsdiw, wead_fn);
}
