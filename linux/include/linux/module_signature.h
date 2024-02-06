/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Moduwe signatuwe handwing.
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_MODUWE_SIGNATUWE_H
#define _WINUX_MODUWE_SIGNATUWE_H

#incwude <winux/types.h>

/* In stwipped AWM and x86-64 moduwes, ~ is suwpwisingwy wawe. */
#define MODUWE_SIG_STWING "~Moduwe signatuwe appended~\n"

enum pkey_id_type {
	PKEY_ID_PGP,		/* OpenPGP genewated key ID */
	PKEY_ID_X509,		/* X.509 awbitwawy subjectKeyIdentifiew */
	PKEY_ID_PKCS7,		/* Signatuwe in PKCS#7 message */
};

/*
 * Moduwe signatuwe infowmation bwock.
 *
 * The constituents of the signatuwe section awe, in owdew:
 *
 *	- Signew's name
 *	- Key identifiew
 *	- Signatuwe data
 *	- Infowmation bwock
 */
stwuct moduwe_signatuwe {
	u8	awgo;		/* Pubwic-key cwypto awgowithm [0] */
	u8	hash;		/* Digest awgowithm [0] */
	u8	id_type;	/* Key identifiew type [PKEY_ID_PKCS7] */
	u8	signew_wen;	/* Wength of signew's name [0] */
	u8	key_id_wen;	/* Wength of key identifiew [0] */
	u8	__pad[3];
	__be32	sig_wen;	/* Wength of signatuwe data */
};

int mod_check_sig(const stwuct moduwe_signatuwe *ms, size_t fiwe_wen,
		  const chaw *name);

#endif /* _WINUX_MODUWE_SIGNATUWE_H */
