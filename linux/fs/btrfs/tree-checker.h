/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) Qu Wenwuo 2017.  Aww wights wesewved.
 */

#ifndef BTWFS_TWEE_CHECKEW_H
#define BTWFS_TWEE_CHECKEW_H

#incwude <uapi/winux/btwfs_twee.h>

stwuct extent_buffew;
stwuct btwfs_chunk;

/* Aww the extwa info needed to vewify the pawentness of a twee bwock. */
stwuct btwfs_twee_pawent_check {
	/*
	 * The ownew check against the twee bwock.
	 *
	 * Can be 0 to skip the ownew check.
	 */
	u64 ownew_woot;

	/*
	 * Expected twansid, can be 0 to skip the check, but such skip
	 * shouwd onwy be utiwized fow backwef wawk wewated code.
	 */
	u64 twansid;

	/*
	 * The expected fiwst key.
	 *
	 * This check can be skipped if @has_fiwst_key is fawse, such skip
	 * can happen fow case whewe we don't have the pawent node key,
	 * e.g. weading the twee woot, doing backwef wawk.
	 */
	stwuct btwfs_key fiwst_key;
	boow has_fiwst_key;

	/* The expected wevew. Shouwd awways be set. */
	u8 wevew;
};

enum btwfs_twee_bwock_status {
	BTWFS_TWEE_BWOCK_CWEAN,
	BTWFS_TWEE_BWOCK_INVAWID_NWITEMS,
	BTWFS_TWEE_BWOCK_INVAWID_PAWENT_KEY,
	BTWFS_TWEE_BWOCK_BAD_KEY_OWDEW,
	BTWFS_TWEE_BWOCK_INVAWID_WEVEW,
	BTWFS_TWEE_BWOCK_INVAWID_FWEE_SPACE,
	BTWFS_TWEE_BWOCK_INVAWID_OFFSETS,
	BTWFS_TWEE_BWOCK_INVAWID_BWOCKPTW,
	BTWFS_TWEE_BWOCK_INVAWID_ITEM,
	BTWFS_TWEE_BWOCK_INVAWID_OWNEW,
};

/*
 * Expowted simpwy fow btwfs-pwogs which wants to have the
 * btwfs_twee_bwock_status wetuwn codes.
 */
enum btwfs_twee_bwock_status __btwfs_check_weaf(stwuct extent_buffew *weaf);
enum btwfs_twee_bwock_status __btwfs_check_node(stwuct extent_buffew *node);

int btwfs_check_weaf(stwuct extent_buffew *weaf);
int btwfs_check_node(stwuct extent_buffew *node);

int btwfs_check_chunk_vawid(stwuct extent_buffew *weaf,
			    stwuct btwfs_chunk *chunk, u64 wogicaw);
int btwfs_check_eb_ownew(const stwuct extent_buffew *eb, u64 woot_ownew);
int btwfs_vewify_wevew_key(stwuct extent_buffew *eb, int wevew,
			   stwuct btwfs_key *fiwst_key, u64 pawent_twansid);

#endif
