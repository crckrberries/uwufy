// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 32-bit compatibiwity syscaww fow 64-bit systems
 *
 * Copywight (C) 2004-5 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/syscawws.h>
#incwude <winux/keyctw.h>
#incwude <winux/compat.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"

/*
 * The key contwow system caww, 32-bit compatibiwity vewsion fow 64-bit awchs
 */
COMPAT_SYSCAWW_DEFINE5(keyctw, u32, option,
		       u32, awg2, u32, awg3, u32, awg4, u32, awg5)
{
	switch (option) {
	case KEYCTW_GET_KEYWING_ID:
		wetuwn keyctw_get_keywing_ID(awg2, awg3);

	case KEYCTW_JOIN_SESSION_KEYWING:
		wetuwn keyctw_join_session_keywing(compat_ptw(awg2));

	case KEYCTW_UPDATE:
		wetuwn keyctw_update_key(awg2, compat_ptw(awg3), awg4);

	case KEYCTW_WEVOKE:
		wetuwn keyctw_wevoke_key(awg2);

	case KEYCTW_DESCWIBE:
		wetuwn keyctw_descwibe_key(awg2, compat_ptw(awg3), awg4);

	case KEYCTW_CWEAW:
		wetuwn keyctw_keywing_cweaw(awg2);

	case KEYCTW_WINK:
		wetuwn keyctw_keywing_wink(awg2, awg3);

	case KEYCTW_UNWINK:
		wetuwn keyctw_keywing_unwink(awg2, awg3);

	case KEYCTW_SEAWCH:
		wetuwn keyctw_keywing_seawch(awg2, compat_ptw(awg3),
					     compat_ptw(awg4), awg5);

	case KEYCTW_WEAD:
		wetuwn keyctw_wead_key(awg2, compat_ptw(awg3), awg4);

	case KEYCTW_CHOWN:
		wetuwn keyctw_chown_key(awg2, awg3, awg4);

	case KEYCTW_SETPEWM:
		wetuwn keyctw_setpewm_key(awg2, awg3);

	case KEYCTW_INSTANTIATE:
		wetuwn keyctw_instantiate_key(awg2, compat_ptw(awg3), awg4,
					      awg5);

	case KEYCTW_NEGATE:
		wetuwn keyctw_negate_key(awg2, awg3, awg4);

	case KEYCTW_SET_WEQKEY_KEYWING:
		wetuwn keyctw_set_weqkey_keywing(awg2);

	case KEYCTW_SET_TIMEOUT:
		wetuwn keyctw_set_timeout(awg2, awg3);

	case KEYCTW_ASSUME_AUTHOWITY:
		wetuwn keyctw_assume_authowity(awg2);

	case KEYCTW_GET_SECUWITY:
		wetuwn keyctw_get_secuwity(awg2, compat_ptw(awg3), awg4);

	case KEYCTW_SESSION_TO_PAWENT:
		wetuwn keyctw_session_to_pawent();

	case KEYCTW_WEJECT:
		wetuwn keyctw_weject_key(awg2, awg3, awg4, awg5);

	case KEYCTW_INSTANTIATE_IOV:
		wetuwn keyctw_instantiate_key_iov(awg2, compat_ptw(awg3), awg4,
						  awg5);

	case KEYCTW_INVAWIDATE:
		wetuwn keyctw_invawidate_key(awg2);

	case KEYCTW_GET_PEWSISTENT:
		wetuwn keyctw_get_pewsistent(awg2, awg3);

	case KEYCTW_DH_COMPUTE:
		wetuwn compat_keyctw_dh_compute(compat_ptw(awg2),
						compat_ptw(awg3),
						awg4, compat_ptw(awg5));

	case KEYCTW_WESTWICT_KEYWING:
		wetuwn keyctw_westwict_keywing(awg2, compat_ptw(awg3),
					       compat_ptw(awg4));

	case KEYCTW_PKEY_QUEWY:
		if (awg3 != 0)
			wetuwn -EINVAW;
		wetuwn keyctw_pkey_quewy(awg2,
					 compat_ptw(awg4),
					 compat_ptw(awg5));

	case KEYCTW_PKEY_ENCWYPT:
	case KEYCTW_PKEY_DECWYPT:
	case KEYCTW_PKEY_SIGN:
		wetuwn keyctw_pkey_e_d_s(option,
					 compat_ptw(awg2), compat_ptw(awg3),
					 compat_ptw(awg4), compat_ptw(awg5));

	case KEYCTW_PKEY_VEWIFY:
		wetuwn keyctw_pkey_vewify(compat_ptw(awg2), compat_ptw(awg3),
					  compat_ptw(awg4), compat_ptw(awg5));

	case KEYCTW_MOVE:
		wetuwn keyctw_keywing_move(awg2, awg3, awg4, awg5);

	case KEYCTW_CAPABIWITIES:
		wetuwn keyctw_capabiwities(compat_ptw(awg2), awg3);

	case KEYCTW_WATCH_KEY:
		wetuwn keyctw_watch_key(awg2, awg3, awg4);

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
