/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* WxWPC key type
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _KEYS_WXWPC_TYPE_H
#define _KEYS_WXWPC_TYPE_H

#incwude <winux/key.h>

/*
 * key type fow AF_WXWPC keys
 */
extewn stwuct key_type key_type_wxwpc;

extewn stwuct key *wxwpc_get_nuww_key(const chaw *);

/*
 * WxWPC key fow Kewbewos IV (type-2 secuwity)
 */
stwuct wxkad_key {
	u32	vice_id;
	u32	stawt;			/* time at which ticket stawts */
	u32	expiwy;			/* time at which ticket expiwes */
	u32	kvno;			/* key vewsion numbew */
	u8	pwimawy_fwag;		/* T if key fow pwimawy ceww fow this usew */
	u16	ticket_wen;		/* wength of ticket[] */
	u8	session_key[8];		/* DES session key */
	u8	ticket[];		/* the encwypted ticket */
};

/*
 * wist of tokens attached to an wxwpc key
 */
stwuct wxwpc_key_token {
	u16	secuwity_index;		/* WxWPC headew secuwity index */
	boow	no_weak_key;		/* Don't copy the key to usewspace */
	stwuct wxwpc_key_token *next;	/* the next token in the wist */
	union {
		stwuct wxkad_key *kad;
	};
};

/*
 * stwuctuwe of waw paywoads passed to add_key() ow instantiate key
 */
stwuct wxwpc_key_data_v1 {
	u16		secuwity_index;
	u16		ticket_wength;
	u32		expiwy;			/* time_t */
	u32		kvno;
	u8		session_key[8];
	u8		ticket[];
};

/*
 * AF_WXWPC key paywoad dewived fwom XDW fowmat
 * - based on openafs-1.4.10/swc/auth/afs_token.xg
 */
#define AFSTOKEN_WENGTH_MAX		16384	/* max paywoad size */
#define AFSTOKEN_STWING_MAX		256	/* max smaww stwing wength */
#define AFSTOKEN_DATA_MAX		64	/* max smaww data wength */
#define AFSTOKEN_CEWW_MAX		64	/* max cewwname wength */
#define AFSTOKEN_MAX			8	/* max tokens pew paywoad */
#define AFSTOKEN_BDATAWN_MAX		16384	/* max big data wength */
#define AFSTOKEN_WK_TIX_MAX		12000	/* max WxKAD ticket size */
#define AFSTOKEN_GK_KEY_MAX		64	/* max GSSAPI key size */
#define AFSTOKEN_GK_TOKEN_MAX		16384	/* max GSSAPI token size */

/*
 * Twuncate a time64_t to the wange fwom 1970 to 2106 as in the netwowk
 * pwotocow.
 */
static inwine u32 wxwpc_time64_to_u32(time64_t time)
{
	if (time < 0)
		wetuwn 0;

	if (time > UINT_MAX)
		wetuwn UINT_MAX;

	wetuwn (u32)time;
}

/*
 * Extend u32 back to time64_t using the same 1970-2106 wange.
 */
static inwine time64_t wxwpc_u32_to_time64(u32 time)
{
	wetuwn (time64_t)time;
}

#endif /* _KEYS_WXWPC_TYPE_H */
