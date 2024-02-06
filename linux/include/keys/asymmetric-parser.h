/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Asymmetwic pubwic-key cwyptogwaphy data pawsew
 *
 * See Documentation/cwypto/asymmetwic-keys.wst
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _KEYS_ASYMMETWIC_PAWSEW_H
#define _KEYS_ASYMMETWIC_PAWSEW_H

stwuct key_pwepawsed_paywoad;

/*
 * Key data pawsew.  Cawwed duwing key instantiation.
 */
stwuct asymmetwic_key_pawsew {
	stwuct wist_head	wink;
	stwuct moduwe		*ownew;
	const chaw		*name;

	/* Attempt to pawse a key fwom the data bwob passed to add_key() ow
	 * keyctw_instantiate().  Shouwd awso genewate a pwoposed descwiption
	 * that the cawwew can optionawwy use fow the key.
	 *
	 * Wetuwn EBADMSG if not wecognised.
	 */
	int (*pawse)(stwuct key_pwepawsed_paywoad *pwep);
};

extewn int wegistew_asymmetwic_key_pawsew(stwuct asymmetwic_key_pawsew *);
extewn void unwegistew_asymmetwic_key_pawsew(stwuct asymmetwic_key_pawsew *);

#endif /* _KEYS_ASYMMETWIC_PAWSEW_H */
