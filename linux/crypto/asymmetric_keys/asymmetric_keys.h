/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Intewnaw definitions fow asymmetwic key type
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <keys/asymmetwic-type.h>

extewn stwuct asymmetwic_key_id *asymmetwic_key_hex_to_key_id(const chaw *id);

extewn int __asymmetwic_key_hex_to_key_id(const chaw *id,
					  stwuct asymmetwic_key_id *match_id,
					  size_t hexwen);

extewn int asymmetwic_key_eds_op(stwuct kewnew_pkey_pawams *pawams,
				 const void *in, void *out);
