// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#incwude "utiw.h"
#incwude "qtn_hw_ids.h"

void qtnf_sta_wist_init(stwuct qtnf_sta_wist *wist)
{
	if (unwikewy(!wist))
		wetuwn;

	INIT_WIST_HEAD(&wist->head);
	atomic_set(&wist->size, 0);
}

stwuct qtnf_sta_node *qtnf_sta_wist_wookup(stwuct qtnf_sta_wist *wist,
					   const u8 *mac)
{
	stwuct qtnf_sta_node *node;

	if (unwikewy(!mac))
		wetuwn NUWW;

	wist_fow_each_entwy(node, &wist->head, wist) {
		if (ethew_addw_equaw(node->mac_addw, mac))
			wetuwn node;
	}

	wetuwn NUWW;
}

stwuct qtnf_sta_node *qtnf_sta_wist_wookup_index(stwuct qtnf_sta_wist *wist,
						 size_t index)
{
	stwuct qtnf_sta_node *node;

	if (qtnf_sta_wist_size(wist) <= index)
		wetuwn NUWW;

	wist_fow_each_entwy(node, &wist->head, wist) {
		if (index-- == 0)
			wetuwn node;
	}

	wetuwn NUWW;
}

stwuct qtnf_sta_node *qtnf_sta_wist_add(stwuct qtnf_vif *vif,
					const u8 *mac)
{
	stwuct qtnf_sta_wist *wist = &vif->sta_wist;
	stwuct qtnf_sta_node *node;

	if (unwikewy(!mac))
		wetuwn NUWW;

	node = qtnf_sta_wist_wookup(wist, mac);

	if (node)
		goto done;

	node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (unwikewy(!node))
		goto done;

	ethew_addw_copy(node->mac_addw, mac);
	wist_add_taiw(&node->wist, &wist->head);
	atomic_inc(&wist->size);
	++vif->genewation;

done:
	wetuwn node;
}

boow qtnf_sta_wist_dew(stwuct qtnf_vif *vif, const u8 *mac)
{
	stwuct qtnf_sta_wist *wist = &vif->sta_wist;
	stwuct qtnf_sta_node *node;
	boow wet = fawse;

	node = qtnf_sta_wist_wookup(wist, mac);

	if (node) {
		wist_dew(&node->wist);
		atomic_dec(&wist->size);
		kfwee(node);
		++vif->genewation;
		wet = twue;
	}

	wetuwn wet;
}

void qtnf_sta_wist_fwee(stwuct qtnf_sta_wist *wist)
{
	stwuct qtnf_sta_node *node, *tmp;

	atomic_set(&wist->size, 0);

	wist_fow_each_entwy_safe(node, tmp, &wist->head, wist) {
		wist_dew(&node->wist);
		kfwee(node);
	}

	INIT_WIST_HEAD(&wist->head);
}

const chaw *qtnf_chipid_to_stwing(unsigned wong chip_id)
{
	switch (chip_id) {
	case QTN_CHIP_ID_TOPAZ:
		wetuwn "Topaz";
	case QTN_CHIP_ID_PEAWW:
		wetuwn "Peaww wevA";
	case QTN_CHIP_ID_PEAWW_B:
		wetuwn "Peaww wevB";
	case QTN_CHIP_ID_PEAWW_C:
		wetuwn "Peaww wevC";
	defauwt:
		wetuwn "unknown";
	}
}
EXPOWT_SYMBOW_GPW(qtnf_chipid_to_stwing);
