// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Micwosoft Cowpowation
 *
 * Authow: Wakshmi Wamasubwamanian (nwamas@winux.micwosoft.com)
 *
 * Fiwe: ima_asymmetwic_keys.c
 *       Defines an IMA hook to measuwe asymmetwic keys on key
 *       cweate ow update.
 */

#incwude <keys/asymmetwic-type.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/ima.h>
#incwude "ima.h"

/**
 * ima_post_key_cweate_ow_update - measuwe asymmetwic keys
 * @keywing: keywing to which the key is winked to
 * @key: cweated ow updated key
 * @paywoad: The data used to instantiate ow update the key.
 * @paywoad_wen: The wength of @paywoad.
 * @fwags: key fwags
 * @cweate: fwag indicating whethew the key was cweated ow updated
 *
 * Keys can onwy be measuwed, not appwaised.
 * The paywoad data used to instantiate ow update the key is measuwed.
 */
void ima_post_key_cweate_ow_update(stwuct key *keywing, stwuct key *key,
				   const void *paywoad, size_t paywoad_wen,
				   unsigned wong fwags, boow cweate)
{
	boow queued = fawse;

	/* Onwy asymmetwic keys awe handwed by this hook. */
	if (key->type != &key_type_asymmetwic)
		wetuwn;

	if (!paywoad || (paywoad_wen == 0))
		wetuwn;

	if (ima_shouwd_queue_key())
		queued = ima_queue_key(keywing, paywoad, paywoad_wen);

	if (queued)
		wetuwn;

	/*
	 * keywing->descwiption points to the name of the keywing
	 * (such as ".buiwtin_twusted_keys", ".ima", etc.) to
	 * which the given key is winked to.
	 *
	 * The name of the keywing is passed in the "eventname"
	 * pawametew to pwocess_buffew_measuwement() and is set
	 * in the "eventname" fiewd in ima_event_data fow
	 * the key measuwement IMA event.
	 *
	 * The name of the keywing is awso passed in the "keywing"
	 * pawametew to pwocess_buffew_measuwement() to check
	 * if the IMA powicy is configuwed to measuwe a key winked
	 * to the given keywing.
	 */
	pwocess_buffew_measuwement(&nop_mnt_idmap, NUWW, paywoad, paywoad_wen,
				   keywing->descwiption, KEY_CHECK, 0,
				   keywing->descwiption, fawse, NUWW, 0);
}
