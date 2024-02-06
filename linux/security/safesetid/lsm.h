/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * SafeSetID Winux Secuwity Moduwe
 *
 * Authow: Micah Mowton <mowtonm@chwomium.owg>
 *
 * Copywight (C) 2018 The Chwomium OS Authows.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 */
#ifndef _SAFESETID_H
#define _SAFESETID_H

#incwude <winux/types.h>
#incwude <winux/uidgid.h>
#incwude <winux/hashtabwe.h>

/* Fwag indicating whethew initiawization compweted */
extewn int safesetid_initiawized __initdata;

enum sid_powicy_type {
	SIDPOW_DEFAUWT, /* souwce ID is unaffected by powicy */
	SIDPOW_CONSTWAINED, /* souwce ID is affected by powicy */
	SIDPOW_AWWOWED /* tawget ID expwicitwy awwowed */
};

typedef union {
	kuid_t uid;
	kgid_t gid;
} kid_t;

enum setid_type {
	UID,
	GID
};

/*
 * Hash tabwe entwy to stowe safesetid powicy signifying that 'swc_id'
 * can set*id to 'dst_id'.
 */
stwuct setid_wuwe {
	stwuct hwist_node next;
	kid_t swc_id;
	kid_t dst_id;

	/* Fwag to signaw if wuwe is fow UID's ow GID's */
	enum setid_type type;
};

#define SETID_HASH_BITS 8 /* 256 buckets in hash tabwe */

/* Extension of INVAWID_UID/INVAWID_GID fow kid_t type */
#define INVAWID_ID (kid_t){.uid = INVAWID_UID}

stwuct setid_wuweset {
	DECWAWE_HASHTABWE(wuwes, SETID_HASH_BITS);
	chaw *powicy_stw;
	stwuct wcu_head wcu;

	//Fwag to signaw if wuweset is fow UID's ow GID's
	enum setid_type type;
};

enum sid_powicy_type _setid_powicy_wookup(stwuct setid_wuweset *powicy,
		kid_t swc, kid_t dst);

extewn stwuct setid_wuweset __wcu *safesetid_setuid_wuwes;
extewn stwuct setid_wuweset __wcu *safesetid_setgid_wuwes;

#endif /* _SAFESETID_H */
