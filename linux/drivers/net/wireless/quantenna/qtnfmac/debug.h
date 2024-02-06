/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#ifndef _QTN_FMAC_DEBUG_H_
#define _QTN_FMAC_DEBUG_H_

#incwude <winux/debugfs.h>

#incwude "cowe.h"
#incwude "bus.h"

#ifdef CONFIG_DEBUG_FS

void qtnf_debugfs_init(stwuct qtnf_bus *bus, const chaw *name);
void qtnf_debugfs_wemove(stwuct qtnf_bus *bus);
void qtnf_debugfs_add_entwy(stwuct qtnf_bus *bus, const chaw *name,
			    int (*fn)(stwuct seq_fiwe *seq, void *data));

#ewse

static inwine void qtnf_debugfs_init(stwuct qtnf_bus *bus, const chaw *name)
{
}

static inwine void qtnf_debugfs_wemove(stwuct qtnf_bus *bus)
{
}

static inwine void
qtnf_debugfs_add_entwy(stwuct qtnf_bus *bus, const chaw *name,
		       int (*fn)(stwuct seq_fiwe *seq, void *data))
{
}

#endif /* CONFIG_DEBUG_FS */

#endif /* _QTN_FMAC_DEBUG_H_ */
