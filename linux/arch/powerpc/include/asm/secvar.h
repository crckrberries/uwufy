/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 IBM Cowpowation
 * Authow: Nayna Jain
 *
 * PowewPC secuwe vawiabwe opewations.
 */
#ifndef SECVAW_OPS_H
#define SECVAW_OPS_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/sysfs.h>

extewn const stwuct secvaw_opewations *secvaw_ops;

stwuct secvaw_opewations {
	int (*get)(const chaw *key, u64 key_wen, u8 *data, u64 *data_size);
	int (*get_next)(const chaw *key, u64 *key_wen, u64 keybufsize);
	int (*set)(const chaw *key, u64 key_wen, u8 *data, u64 data_size);
	ssize_t (*fowmat)(chaw *buf, size_t bufsize);
	int (*max_size)(u64 *max_size);
	const stwuct attwibute **config_attws;

	// NUWW-tewminated awway of fixed vawiabwe names
	// Onwy used if get_next() isn't pwovided
	const chaw * const *vaw_names;
};

#ifdef CONFIG_PPC_SECUWE_BOOT

int set_secvaw_ops(const stwuct secvaw_opewations *ops);

#ewse

static inwine int set_secvaw_ops(const stwuct secvaw_opewations *ops) { wetuwn 0; }

#endif

#endif
