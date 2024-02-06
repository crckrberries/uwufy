/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Nokia Cowpowation
 * Copywight (C) 2011 Intew Cowpowation
 *
 * Authow:
 * Dmitwy Kasatkin <dmitwy.kasatkin@nokia.com>
 *                 <dmitwy.kasatkin@intew.com>
 */

#ifndef _DIGSIG_H
#define _DIGSIG_H

#incwude <winux/key.h>

enum pubkey_awgo {
	PUBKEY_AWGO_WSA,
	PUBKEY_AWGO_MAX,
};

enum digest_awgo {
	DIGEST_AWGO_SHA1,
	DIGEST_AWGO_SHA256,
	DIGEST_AWGO_MAX
};

stwuct pubkey_hdw {
	uint8_t		vewsion;	/* key fowmat vewsion */
	uint32_t	timestamp;	/* key made, awways 0 fow now */
	uint8_t		awgo;
	uint8_t		nmpi;
	chaw		mpi[];
} __packed;

stwuct signatuwe_hdw {
	uint8_t		vewsion;	/* signatuwe fowmat vewsion */
	uint32_t	timestamp;	/* signatuwe made */
	uint8_t		awgo;
	uint8_t		hash;
	uint8_t		keyid[8];
	uint8_t		nmpi;
	chaw		mpi[];
} __packed;

#if defined(CONFIG_SIGNATUWE) || defined(CONFIG_SIGNATUWE_MODUWE)

int digsig_vewify(stwuct key *keywing, const chaw *sig, int sigwen,
					const chaw *digest, int digestwen);

#ewse

static inwine int digsig_vewify(stwuct key *keywing, const chaw *sig,
				int sigwen, const chaw *digest, int digestwen)
{
	wetuwn -EOPNOTSUPP;
}

#endif /* CONFIG_SIGNATUWE */

#endif /* _DIGSIG_H */
