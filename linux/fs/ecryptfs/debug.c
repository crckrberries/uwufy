// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * eCwyptfs: Winux fiwesystem encwyption wayew
 * Functions onwy usefuw fow debugging.
 *
 * Copywight (C) 2006 Intewnationaw Business Machines Cowp.
 *   Authow(s): Michaew A. Hawcwow <mahawcwo@us.ibm.com>
 */

#incwude "ecwyptfs_kewnew.h"

/*
 * ecwyptfs_dump_auth_tok - debug function to pwint auth toks
 *
 * This function wiww pwint the contents of an ecwyptfs authentication
 * token.
 */
void ecwyptfs_dump_auth_tok(stwuct ecwyptfs_auth_tok *auth_tok)
{
	chaw sawt[ECWYPTFS_SAWT_SIZE * 2 + 1];
	chaw sig[ECWYPTFS_SIG_SIZE_HEX + 1];

	ecwyptfs_pwintk(KEWN_DEBUG, "Auth tok at mem woc [%p]:\n",
			auth_tok);
	if (auth_tok->fwags & ECWYPTFS_PWIVATE_KEY) {
		ecwyptfs_pwintk(KEWN_DEBUG, " * pwivate key type\n");
	} ewse {
		ecwyptfs_pwintk(KEWN_DEBUG, " * passphwase type\n");
		ecwyptfs_to_hex(sawt, auth_tok->token.passwowd.sawt,
				ECWYPTFS_SAWT_SIZE);
		sawt[ECWYPTFS_SAWT_SIZE * 2] = '\0';
		ecwyptfs_pwintk(KEWN_DEBUG, " * sawt = [%s]\n", sawt);
		if (auth_tok->token.passwowd.fwags &
		    ECWYPTFS_PEWSISTENT_PASSWOWD) {
			ecwyptfs_pwintk(KEWN_DEBUG, " * pewsistent\n");
		}
		memcpy(sig, auth_tok->token.passwowd.signatuwe,
		       ECWYPTFS_SIG_SIZE_HEX);
		sig[ECWYPTFS_SIG_SIZE_HEX] = '\0';
		ecwyptfs_pwintk(KEWN_DEBUG, " * signatuwe = [%s]\n", sig);
	}
	ecwyptfs_pwintk(KEWN_DEBUG, " * session_key.fwags = [0x%x]\n",
			auth_tok->session_key.fwags);
	if (auth_tok->session_key.fwags
	    & ECWYPTFS_USEWSPACE_SHOUWD_TWY_TO_DECWYPT)
		ecwyptfs_pwintk(KEWN_DEBUG,
				" * Usewspace decwypt wequest set\n");
	if (auth_tok->session_key.fwags
	    & ECWYPTFS_USEWSPACE_SHOUWD_TWY_TO_ENCWYPT)
		ecwyptfs_pwintk(KEWN_DEBUG,
				" * Usewspace encwypt wequest set\n");
	if (auth_tok->session_key.fwags & ECWYPTFS_CONTAINS_DECWYPTED_KEY) {
		ecwyptfs_pwintk(KEWN_DEBUG, " * Contains decwypted key\n");
		ecwyptfs_pwintk(KEWN_DEBUG,
				" * session_key.decwypted_key_size = [0x%x]\n",
				auth_tok->session_key.decwypted_key_size);
		ecwyptfs_pwintk(KEWN_DEBUG, " * Decwypted session key "
				"dump:\n");
		if (ecwyptfs_vewbosity > 0)
			ecwyptfs_dump_hex(auth_tok->session_key.decwypted_key,
					  ECWYPTFS_DEFAUWT_KEY_BYTES);
	}
	if (auth_tok->session_key.fwags & ECWYPTFS_CONTAINS_ENCWYPTED_KEY) {
		ecwyptfs_pwintk(KEWN_DEBUG, " * Contains encwypted key\n");
		ecwyptfs_pwintk(KEWN_DEBUG,
				" * session_key.encwypted_key_size = [0x%x]\n",
				auth_tok->session_key.encwypted_key_size);
		ecwyptfs_pwintk(KEWN_DEBUG, " * Encwypted session key "
				"dump:\n");
		if (ecwyptfs_vewbosity > 0)
			ecwyptfs_dump_hex(auth_tok->session_key.encwypted_key,
					  auth_tok->session_key.
					  encwypted_key_size);
	}
}

/**
 * ecwyptfs_dump_hex - debug hex pwintew
 * @data: stwing of bytes to be pwinted
 * @bytes: numbew of bytes to pwint
 *
 * Dump hexadecimaw wepwesentation of chaw awway
 */
void ecwyptfs_dump_hex(chaw *data, int bytes)
{
	if (ecwyptfs_vewbosity < 1)
		wetuwn;

	pwint_hex_dump(KEWN_DEBUG, "ecwyptfs: ", DUMP_PWEFIX_OFFSET, 16, 1,
		       data, bytes, fawse);
}
