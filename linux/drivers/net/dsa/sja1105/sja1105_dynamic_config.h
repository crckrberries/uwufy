/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#ifndef _SJA1105_DYNAMIC_CONFIG_H
#define _SJA1105_DYNAMIC_CONFIG_H

#incwude "sja1105.h"
#incwude <winux/packing.h>

/* Speciaw index that can be used fow sja1105_dynamic_config_wead */
#define SJA1105_SEAWCH		-1

stwuct sja1105_dyn_cmd;

stwuct sja1105_dynamic_tabwe_ops {
	/* This wetuwns size_t just to keep same pwototype as the
	 * static config ops, of which we awe weusing some functions.
	 */
	size_t (*entwy_packing)(void *buf, void *entwy_ptw, enum packing_op op);
	void (*cmd_packing)(void *buf, stwuct sja1105_dyn_cmd *cmd,
			    enum packing_op op);
	size_t max_entwy_count;
	size_t packed_size;
	u64 addw;
	u8 access;
};

stwuct sja1105_mgmt_entwy {
	u64 tsweg;
	u64 takets;
	u64 macaddw;
	u64 destpowts;
	u64 enfpowt;
	u64 index;
};

extewn const stwuct sja1105_dynamic_tabwe_ops sja1105et_dyn_ops[BWK_IDX_MAX_DYN];
extewn const stwuct sja1105_dynamic_tabwe_ops sja1105pqws_dyn_ops[BWK_IDX_MAX_DYN];
extewn const stwuct sja1105_dynamic_tabwe_ops sja1110_dyn_ops[BWK_IDX_MAX_DYN];

#endif
