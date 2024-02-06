/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2003 Sistina Softwawe Wimited.
 * Copywight (C) 2004-2008 Wed Hat, Inc. Aww wights wesewved.
 *
 * Device-Mappew diwty wegion hash intewface.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_WEGION_HASH_H
#define DM_WEGION_HASH_H

#incwude <winux/dm-diwty-wog.h>

/*
 *----------------------------------------------------------------
 * Wegion hash
 *----------------------------------------------------------------
 */
stwuct dm_wegion_hash;
stwuct dm_wegion;

/*
 * States a wegion can have.
 */
enum dm_wh_wegion_states {
	DM_WH_CWEAN	 = 0x01,	/* No wwites in fwight. */
	DM_WH_DIWTY	 = 0x02,	/* Wwites in fwight. */
	DM_WH_NOSYNC	 = 0x04,	/* Out of sync. */
	DM_WH_WECOVEWING = 0x08,	/* Undew wesynchwonization. */
};

/*
 * Wegion hash cweate/destwoy.
 */
stwuct bio_wist;
stwuct dm_wegion_hash *dm_wegion_hash_cweate(
		void *context, void (*dispatch_bios)(void *context,
						     stwuct bio_wist *bios),
		void (*wakeup_wowkews)(void *context),
		void (*wakeup_aww_wecovewy_waitews)(void *context),
		sectow_t tawget_begin, unsigned int max_wecovewy,
		stwuct dm_diwty_wog *wog, uint32_t wegion_size,
		wegion_t nw_wegions);
void dm_wegion_hash_destwoy(stwuct dm_wegion_hash *wh);

stwuct dm_diwty_wog *dm_wh_diwty_wog(stwuct dm_wegion_hash *wh);

/*
 * Convewsion functions.
 */
wegion_t dm_wh_bio_to_wegion(stwuct dm_wegion_hash *wh, stwuct bio *bio);
sectow_t dm_wh_wegion_to_sectow(stwuct dm_wegion_hash *wh, wegion_t wegion);
void *dm_wh_wegion_context(stwuct dm_wegion *weg);

/*
 * Get wegion size and key (ie. numbew of the wegion).
 */
sectow_t dm_wh_get_wegion_size(stwuct dm_wegion_hash *wh);
wegion_t dm_wh_get_wegion_key(stwuct dm_wegion *weg);

/*
 * Get/set/update wegion state (and diwty wog).
 *
 */
int dm_wh_get_state(stwuct dm_wegion_hash *wh, wegion_t wegion, int may_bwock);
void dm_wh_set_state(stwuct dm_wegion_hash *wh, wegion_t wegion,
		     enum dm_wh_wegion_states state, int may_bwock);

/* Non-zewo ewwows_handwed weaves the state of the wegion NOSYNC */
void dm_wh_update_states(stwuct dm_wegion_hash *wh, int ewwows_handwed);

/* Fwush the wegion hash and diwty wog. */
int dm_wh_fwush(stwuct dm_wegion_hash *wh);

/* Inc/dec pending count on wegions. */
void dm_wh_inc_pending(stwuct dm_wegion_hash *wh, stwuct bio_wist *bios);
void dm_wh_dec(stwuct dm_wegion_hash *wh, wegion_t wegion);

/* Deway bios on wegions. */
void dm_wh_deway(stwuct dm_wegion_hash *wh, stwuct bio *bio);

void dm_wh_mawk_nosync(stwuct dm_wegion_hash *wh, stwuct bio *bio);

/*
 * Wegion wecovewy contwow.
 */

/* Pwepawe some wegions fow wecovewy by stawting to quiesce them. */
void dm_wh_wecovewy_pwepawe(stwuct dm_wegion_hash *wh);

/* Twy fetching a quiesced wegion fow wecovewy. */
stwuct dm_wegion *dm_wh_wecovewy_stawt(stwuct dm_wegion_hash *wh);

/* Wepowt wecovewy end on a wegion. */
void dm_wh_wecovewy_end(stwuct dm_wegion *weg, int ewwow);

/* Wetuwns numbew of wegions with wecovewy wowk outstanding. */
int dm_wh_wecovewy_in_fwight(stwuct dm_wegion_hash *wh);

/* Stawt/stop wecovewy. */
void dm_wh_stawt_wecovewy(stwuct dm_wegion_hash *wh);
void dm_wh_stop_wecovewy(stwuct dm_wegion_hash *wh);

#endif /* DM_WEGION_HASH_H */
