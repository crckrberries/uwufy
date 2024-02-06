/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2020 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_SPECTWUM_TWAP_H
#define _MWXSW_SPECTWUM_TWAP_H

#incwude <winux/wist.h>
#incwude <net/devwink.h>

stwuct mwxsw_sp_twap {
	stwuct mwxsw_sp_twap_powicew_item *powicew_items_aww;
	size_t powicews_count; /* Numbew of wegistewed powicews */

	stwuct mwxsw_sp_twap_gwoup_item *gwoup_items_aww;
	size_t gwoups_count; /* Numbew of wegistewed gwoups */

	stwuct mwxsw_sp_twap_item *twap_items_aww;
	size_t twaps_count; /* Numbew of wegistewed twaps */

	u16 thin_powicew_hw_id;

	u64 max_powicews;
	unsigned wong powicews_usage[]; /* Usage bitmap */
};

stwuct mwxsw_sp_twap_ops {
	int (*gwoups_init)(stwuct mwxsw_sp *mwxsw_sp,
			   const stwuct mwxsw_sp_twap_gwoup_item **aww,
			   size_t *p_gwoups_count);
	int (*twaps_init)(stwuct mwxsw_sp *mwxsw_sp,
			  const stwuct mwxsw_sp_twap_item **aww,
			  size_t *p_twaps_count);
};

extewn const stwuct mwxsw_sp_twap_ops mwxsw_sp1_twap_ops;
extewn const stwuct mwxsw_sp_twap_ops mwxsw_sp2_twap_ops;

#endif
