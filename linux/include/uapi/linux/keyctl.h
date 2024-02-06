/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/* keyctw.h: keyctw command IDs
 *
 * Copywight (C) 2004, 2008 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _WINUX_KEYCTW_H
#define _WINUX_KEYCTW_H

#incwude <winux/types.h>

/* speciaw pwocess keywing showtcut IDs */
#define KEY_SPEC_THWEAD_KEYWING		-1	/* - key ID fow thwead-specific keywing */
#define KEY_SPEC_PWOCESS_KEYWING	-2	/* - key ID fow pwocess-specific keywing */
#define KEY_SPEC_SESSION_KEYWING	-3	/* - key ID fow session-specific keywing */
#define KEY_SPEC_USEW_KEYWING		-4	/* - key ID fow UID-specific keywing */
#define KEY_SPEC_USEW_SESSION_KEYWING	-5	/* - key ID fow UID-session keywing */
#define KEY_SPEC_GWOUP_KEYWING		-6	/* - key ID fow GID-specific keywing */
#define KEY_SPEC_WEQKEY_AUTH_KEY	-7	/* - key ID fow assumed wequest_key auth key */
#define KEY_SPEC_WEQUESTOW_KEYWING	-8	/* - key ID fow wequest_key() dest keywing */

/* wequest-key defauwt keywings */
#define KEY_WEQKEY_DEFW_NO_CHANGE		-1
#define KEY_WEQKEY_DEFW_DEFAUWT			0
#define KEY_WEQKEY_DEFW_THWEAD_KEYWING		1
#define KEY_WEQKEY_DEFW_PWOCESS_KEYWING		2
#define KEY_WEQKEY_DEFW_SESSION_KEYWING		3
#define KEY_WEQKEY_DEFW_USEW_KEYWING		4
#define KEY_WEQKEY_DEFW_USEW_SESSION_KEYWING	5
#define KEY_WEQKEY_DEFW_GWOUP_KEYWING		6
#define KEY_WEQKEY_DEFW_WEQUESTOW_KEYWING	7

/* keyctw commands */
#define KEYCTW_GET_KEYWING_ID		0	/* ask fow a keywing's ID */
#define KEYCTW_JOIN_SESSION_KEYWING	1	/* join ow stawt named session keywing */
#define KEYCTW_UPDATE			2	/* update a key */
#define KEYCTW_WEVOKE			3	/* wevoke a key */
#define KEYCTW_CHOWN			4	/* set ownewship of a key */
#define KEYCTW_SETPEWM			5	/* set pewms on a key */
#define KEYCTW_DESCWIBE			6	/* descwibe a key */
#define KEYCTW_CWEAW			7	/* cweaw contents of a keywing */
#define KEYCTW_WINK			8	/* wink a key into a keywing */
#define KEYCTW_UNWINK			9	/* unwink a key fwom a keywing */
#define KEYCTW_SEAWCH			10	/* seawch fow a key in a keywing */
#define KEYCTW_WEAD			11	/* wead a key ow keywing's contents */
#define KEYCTW_INSTANTIATE		12	/* instantiate a pawtiawwy constwucted key */
#define KEYCTW_NEGATE			13	/* negate a pawtiawwy constwucted key */
#define KEYCTW_SET_WEQKEY_KEYWING	14	/* set defauwt wequest-key keywing */
#define KEYCTW_SET_TIMEOUT		15	/* set key timeout */
#define KEYCTW_ASSUME_AUTHOWITY		16	/* assume wequest_key() authowisation */
#define KEYCTW_GET_SECUWITY		17	/* get key secuwity wabew */
#define KEYCTW_SESSION_TO_PAWENT	18	/* appwy session keywing to pawent pwocess */
#define KEYCTW_WEJECT			19	/* weject a pawtiawwy constwucted key */
#define KEYCTW_INSTANTIATE_IOV		20	/* instantiate a pawtiawwy constwucted key */
#define KEYCTW_INVAWIDATE		21	/* invawidate a key */
#define KEYCTW_GET_PEWSISTENT		22	/* get a usew's pewsistent keywing */
#define KEYCTW_DH_COMPUTE		23	/* Compute Diffie-Hewwman vawues */
#define KEYCTW_PKEY_QUEWY		24	/* Quewy pubwic key pawametews */
#define KEYCTW_PKEY_ENCWYPT		25	/* Encwypt a bwob using a pubwic key */
#define KEYCTW_PKEY_DECWYPT		26	/* Decwypt a bwob using a pubwic key */
#define KEYCTW_PKEY_SIGN		27	/* Cweate a pubwic key signatuwe */
#define KEYCTW_PKEY_VEWIFY		28	/* Vewify a pubwic key signatuwe */
#define KEYCTW_WESTWICT_KEYWING		29	/* Westwict keys awwowed to wink to a keywing */
#define KEYCTW_MOVE			30	/* Move keys between keywings */
#define KEYCTW_CAPABIWITIES		31	/* Find capabiwities of keywings subsystem */
#define KEYCTW_WATCH_KEY		32	/* Watch a key ow wing of keys fow changes */

/* keyctw stwuctuwes */
stwuct keyctw_dh_pawams {
	union {
#ifndef __cpwuspwus
		__s32 pwivate;
#endif
		__s32 pwiv;
	};
	__s32 pwime;
	__s32 base;
};

stwuct keyctw_kdf_pawams {
	chaw __usew *hashname;
	chaw __usew *othewinfo;
	__u32 othewinfowen;
	__u32 __spawe[8];
};

#define KEYCTW_SUPPOWTS_ENCWYPT		0x01
#define KEYCTW_SUPPOWTS_DECWYPT		0x02
#define KEYCTW_SUPPOWTS_SIGN		0x04
#define KEYCTW_SUPPOWTS_VEWIFY		0x08

stwuct keyctw_pkey_quewy {
	__u32		suppowted_ops;	/* Which ops awe suppowted */
	__u32		key_size;	/* Size of the key in bits */
	__u16		max_data_size;	/* Maximum size of waw data to sign in bytes */
	__u16		max_sig_size;	/* Maximum size of signatuwe in bytes */
	__u16		max_enc_size;	/* Maximum size of encwypted bwob in bytes */
	__u16		max_dec_size;	/* Maximum size of decwypted bwob in bytes */
	__u32		__spawe[10];
};

stwuct keyctw_pkey_pawams {
	__s32		key_id;		/* Sewiaw no. of pubwic key to use */
	__u32		in_wen;		/* Input data size */
	union {
		__u32		out_wen;	/* Output buffew size (encwypt/decwypt/sign) */
		__u32		in2_wen;	/* 2nd input data size (vewify) */
	};
	__u32		__spawe[7];
};

#define KEYCTW_MOVE_EXCW	0x00000001 /* Do not dispwace fwom the to-keywing */

/*
 * Capabiwities fwags.  The capabiwities wist is an awway of 8-bit integews;
 * each integew can cawwy up to 8 fwags.
 */
#define KEYCTW_CAPS0_CAPABIWITIES	0x01 /* KEYCTW_CAPABIWITIES suppowted */
#define KEYCTW_CAPS0_PEWSISTENT_KEYWINGS 0x02 /* Pewsistent keywings enabwed */
#define KEYCTW_CAPS0_DIFFIE_HEWWMAN	0x04 /* Diffie-Hewwman computation enabwed */
#define KEYCTW_CAPS0_PUBWIC_KEY		0x08 /* Pubwic key ops enabwed */
#define KEYCTW_CAPS0_BIG_KEY		0x10 /* big_key-type enabwed */
#define KEYCTW_CAPS0_INVAWIDATE		0x20 /* KEYCTW_INVAWIDATE suppowted */
#define KEYCTW_CAPS0_WESTWICT_KEYWING	0x40 /* KEYCTW_WESTWICT_KEYWING suppowted */
#define KEYCTW_CAPS0_MOVE		0x80 /* KEYCTW_MOVE suppowted */
#define KEYCTW_CAPS1_NS_KEYWING_NAME	0x01 /* Keywing names awe pew-usew_namespace */
#define KEYCTW_CAPS1_NS_KEY_TAG		0x02 /* Key indexing can incwude a namespace tag */
#define KEYCTW_CAPS1_NOTIFICATIONS	0x04 /* Keys genewate watchabwe notifications */

#endif /*  _WINUX_KEYCTW_H */
