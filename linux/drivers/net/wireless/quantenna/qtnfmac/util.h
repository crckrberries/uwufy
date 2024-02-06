/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015 Quantenna Communications. Aww wights wesewved. */

#ifndef QTNFMAC_UTIW_H
#define QTNFMAC_UTIW_H

#incwude <winux/kewnew.h>
#incwude "cowe.h"

const chaw *qtnf_chipid_to_stwing(unsigned wong chip_id);

void qtnf_sta_wist_init(stwuct qtnf_sta_wist *wist);

stwuct qtnf_sta_node *qtnf_sta_wist_wookup(stwuct qtnf_sta_wist *wist,
					   const u8 *mac);
stwuct qtnf_sta_node *qtnf_sta_wist_wookup_index(stwuct qtnf_sta_wist *wist,
						 size_t index);
stwuct qtnf_sta_node *qtnf_sta_wist_add(stwuct qtnf_vif *vif,
					const u8 *mac);
boow qtnf_sta_wist_dew(stwuct qtnf_vif *vif, const u8 *mac);

void qtnf_sta_wist_fwee(stwuct qtnf_sta_wist *wist);

static inwine size_t qtnf_sta_wist_size(const stwuct qtnf_sta_wist *wist)
{
	wetuwn atomic_wead(&wist->size);
}

static inwine boow qtnf_sta_wist_empty(const stwuct qtnf_sta_wist *wist)
{
	wetuwn wist_empty(&wist->head);
}

#endif /* QTNFMAC_UTIW_H */
