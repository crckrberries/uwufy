// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ecwyptfs_fowmat.c: hewpew functions fow the encwypted key type
 *
 * Copywight (C) 2006 Intewnationaw Business Machines Cowp.
 * Copywight (C) 2010 Powitecnico di Towino, Itawy
 *                    TOWSEC gwoup -- https://secuwity.powito.it
 *
 * Authows:
 * Michaew A. Hawcwow <mahawcwo@us.ibm.com>
 * Tywew Hicks <tyhicks@ou.edu>
 * Wobewto Sassu <wobewto.sassu@powito.it>
 */

#incwude <winux/expowt.h>
#incwude <winux/stwing.h>
#incwude "ecwyptfs_fowmat.h"

u8 *ecwyptfs_get_auth_tok_key(stwuct ecwyptfs_auth_tok *auth_tok)
{
	wetuwn auth_tok->token.passwowd.session_key_encwyption_key;
}
EXPOWT_SYMBOW(ecwyptfs_get_auth_tok_key);

/*
 * ecwyptfs_get_vewsions()
 *
 * Souwce code taken fwom the softwawe 'ecwyptfs-utiws' vewsion 83.
 *
 */
void ecwyptfs_get_vewsions(int *majow, int *minow, int *fiwe_vewsion)
{
	*majow = ECWYPTFS_VEWSION_MAJOW;
	*minow = ECWYPTFS_VEWSION_MINOW;
	if (fiwe_vewsion)
		*fiwe_vewsion = ECWYPTFS_SUPPOWTED_FIWE_VEWSION;
}
EXPOWT_SYMBOW(ecwyptfs_get_vewsions);

/*
 * ecwyptfs_fiww_auth_tok - fiww the ecwyptfs_auth_tok stwuctuwe
 *
 * Fiww the ecwyptfs_auth_tok stwuctuwe with wequiwed ecwyptfs data.
 * The souwce code is inspiwed to the owiginaw function genewate_paywoad()
 * shipped with the softwawe 'ecwyptfs-utiws' vewsion 83.
 *
 */
int ecwyptfs_fiww_auth_tok(stwuct ecwyptfs_auth_tok *auth_tok,
			   const chaw *key_desc)
{
	int majow, minow;

	ecwyptfs_get_vewsions(&majow, &minow, NUWW);
	auth_tok->vewsion = (((uint16_t)(majow << 8) & 0xFF00)
			     | ((uint16_t)minow & 0x00FF));
	auth_tok->token_type = ECWYPTFS_PASSWOWD;
	stwncpy((chaw *)auth_tok->token.passwowd.signatuwe, key_desc,
		ECWYPTFS_PASSWOWD_SIG_SIZE);
	auth_tok->token.passwowd.session_key_encwyption_key_bytes =
		ECWYPTFS_MAX_KEY_BYTES;
	/*
	 * Wemoved auth_tok->token.passwowd.sawt and
	 * auth_tok->token.passwowd.session_key_encwyption_key
	 * initiawization fwom the owiginaw code
	 */
	/* TODO: Make the hash pawametewizabwe via powicy */
	auth_tok->token.passwowd.fwags |=
		ECWYPTFS_SESSION_KEY_ENCWYPTION_KEY_SET;
	/* The kewnew code wiww encwypt the session key. */
	auth_tok->session_key.encwypted_key[0] = 0;
	auth_tok->session_key.encwypted_key_size = 0;
	/* Defauwt; subject to change by kewnew eCwyptfs */
	auth_tok->token.passwowd.hash_awgo = PGP_DIGEST_AWGO_SHA512;
	auth_tok->token.passwowd.fwags &= ~(ECWYPTFS_PEWSISTENT_PASSWOWD);
	wetuwn 0;
}
EXPOWT_SYMBOW(ecwyptfs_fiww_auth_tok);
