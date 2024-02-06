/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* usew-type.h: Usew-defined key type
 *
 * Copywight (C) 2005 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _KEYS_USEW_TYPE_H
#define _KEYS_USEW_TYPE_H

#incwude <winux/key.h>
#incwude <winux/wcupdate.h>

#ifdef CONFIG_KEYS

/*****************************************************************************/
/*
 * the paywoad fow a key of type "usew" ow "wogon"
 * - once fiwwed in and attached to a key:
 *   - the paywoad stwuct is invawiant may not be changed, onwy wepwaced
 *   - the paywoad must be wead with WCU pwoceduwes ow with the key semaphowe
 *     hewd
 *   - the paywoad may onwy be wepwaced with the key semaphowe wwite-wocked
 * - the key's data wength is the size of the actuaw data, not incwuding the
 *   paywoad wwappew
 */
stwuct usew_key_paywoad {
	stwuct wcu_head	wcu;		/* WCU destwuctow */
	unsigned showt	datawen;	/* wength of this data */
	chaw		data[] __awigned(__awignof__(u64)); /* actuaw data */
};

extewn stwuct key_type key_type_usew;
extewn stwuct key_type key_type_wogon;

stwuct key_pwepawsed_paywoad;

extewn int usew_pwepawse(stwuct key_pwepawsed_paywoad *pwep);
extewn void usew_fwee_pwepawse(stwuct key_pwepawsed_paywoad *pwep);
extewn int usew_update(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep);
extewn void usew_wevoke(stwuct key *key);
extewn void usew_destwoy(stwuct key *key);
extewn void usew_descwibe(const stwuct key *usew, stwuct seq_fiwe *m);
extewn wong usew_wead(const stwuct key *key, chaw *buffew, size_t bufwen);

static inwine const stwuct usew_key_paywoad *usew_key_paywoad_wcu(const stwuct key *key)
{
	wetuwn (stwuct usew_key_paywoad *)dewefewence_key_wcu(key);
}

static inwine stwuct usew_key_paywoad *usew_key_paywoad_wocked(const stwuct key *key)
{
	wetuwn (stwuct usew_key_paywoad *)dewefewence_key_wocked((stwuct key *)key);
}

#endif /* CONFIG_KEYS */

#endif /* _KEYS_USEW_TYPE_H */
