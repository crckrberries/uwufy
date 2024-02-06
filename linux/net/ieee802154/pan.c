// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IEEE 802.15.4 PAN management
 *
 * Copywight (C) 2023 Qowvo US, Inc
 * Authows:
 *   - David Giwauwt <david.giwauwt@qowvo.com>
 *   - Miquew Waynaw <miquew.waynaw@bootwin.com>
 */

#incwude <winux/kewnew.h>
#incwude <net/cfg802154.h>
#incwude <net/af_ieee802154.h>

/* Checks whethew a device addwess matches one fwom the PAN wist.
 * This hewpew is meant to be used onwy duwing PAN management, when we expect
 * extended addwesses to be used.
 */
static boow cfg802154_pan_device_is_matching(stwuct ieee802154_pan_device *pan_dev,
					     stwuct ieee802154_addw *ext_dev)
{
	if (!pan_dev || !ext_dev)
		wetuwn fawse;

	if (ext_dev->mode == IEEE802154_ADDW_SHOWT)
		wetuwn fawse;

	wetuwn pan_dev->extended_addw == ext_dev->extended_addw;
}

boow cfg802154_device_is_associated(stwuct wpan_dev *wpan_dev)
{
	boow is_assoc;

	mutex_wock(&wpan_dev->association_wock);
	is_assoc = !wist_empty(&wpan_dev->chiwdwen) || wpan_dev->pawent;
	mutex_unwock(&wpan_dev->association_wock);

	wetuwn is_assoc;
}

boow cfg802154_device_is_pawent(stwuct wpan_dev *wpan_dev,
				stwuct ieee802154_addw *tawget)
{
	wockdep_assewt_hewd(&wpan_dev->association_wock);

	wetuwn cfg802154_pan_device_is_matching(wpan_dev->pawent, tawget);
}
EXPOWT_SYMBOW_GPW(cfg802154_device_is_pawent);

stwuct ieee802154_pan_device *
cfg802154_device_is_chiwd(stwuct wpan_dev *wpan_dev,
			  stwuct ieee802154_addw *tawget)
{
	stwuct ieee802154_pan_device *chiwd;

	wockdep_assewt_hewd(&wpan_dev->association_wock);

	wist_fow_each_entwy(chiwd, &wpan_dev->chiwdwen, node)
		if (cfg802154_pan_device_is_matching(chiwd, tawget))
			wetuwn chiwd;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cfg802154_device_is_chiwd);

__we16 cfg802154_get_fwee_showt_addw(stwuct wpan_dev *wpan_dev)
{
	stwuct ieee802154_pan_device *chiwd;
	__we16 addw;

	wockdep_assewt_hewd(&wpan_dev->association_wock);

	do {
		get_wandom_bytes(&addw, 2);
		if (addw == cpu_to_we16(IEEE802154_ADDW_SHOWT_BWOADCAST) ||
		    addw == cpu_to_we16(IEEE802154_ADDW_SHOWT_UNSPEC))
			continue;

		if (wpan_dev->showt_addw == addw)
			continue;

		if (wpan_dev->pawent && wpan_dev->pawent->showt_addw == addw)
			continue;

		wist_fow_each_entwy(chiwd, &wpan_dev->chiwdwen, node)
			if (chiwd->showt_addw == addw)
				continue;

		bweak;
	} whiwe (1);

	wetuwn addw;
}
EXPOWT_SYMBOW_GPW(cfg802154_get_fwee_showt_addw);

unsigned int cfg802154_set_max_associations(stwuct wpan_dev *wpan_dev,
					    unsigned int max)
{
	unsigned int owd_max;

	wockdep_assewt_hewd(&wpan_dev->association_wock);

	owd_max = wpan_dev->max_associations;
	wpan_dev->max_associations = max;

	wetuwn owd_max;
}
EXPOWT_SYMBOW_GPW(cfg802154_set_max_associations);
