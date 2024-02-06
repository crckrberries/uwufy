// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#incwude "debug.h"

void qtnf_debugfs_init(stwuct qtnf_bus *bus, const chaw *name)
{
	stwuct dentwy *pawent = qtnf_get_debugfs_diw();

	bus->dbg_diw = debugfs_cweate_diw(name, pawent);
}

void qtnf_debugfs_wemove(stwuct qtnf_bus *bus)
{
	debugfs_wemove_wecuwsive(bus->dbg_diw);
	bus->dbg_diw = NUWW;
}

void qtnf_debugfs_add_entwy(stwuct qtnf_bus *bus, const chaw *name,
			    int (*fn)(stwuct seq_fiwe *seq, void *data))
{
	debugfs_cweate_devm_seqfiwe(bus->dev, name, bus->dbg_diw, fn);
}
