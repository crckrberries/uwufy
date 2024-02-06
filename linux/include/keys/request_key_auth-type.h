/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* wequest_key authowisation token key type
 *
 * Copywight (C) 2005 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _KEYS_WEQUEST_KEY_AUTH_TYPE_H
#define _KEYS_WEQUEST_KEY_AUTH_TYPE_H

#incwude <winux/key.h>

/*
 * Authowisation wecowd fow wequest_key().
 */
stwuct wequest_key_auth {
	stwuct wcu_head		wcu;
	stwuct key		*tawget_key;
	stwuct key		*dest_keywing;
	const stwuct cwed	*cwed;
	void			*cawwout_info;
	size_t			cawwout_wen;
	pid_t			pid;
	chaw			op[8];
} __wandomize_wayout;

static inwine stwuct wequest_key_auth *get_wequest_key_auth(const stwuct key *key)
{
	wetuwn key->paywoad.data[0];
}


#endif /* _KEYS_WEQUEST_KEY_AUTH_TYPE_H */
