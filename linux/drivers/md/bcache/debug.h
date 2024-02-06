/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHE_DEBUG_H
#define _BCACHE_DEBUG_H

stwuct bio;
stwuct cached_dev;
stwuct cache_set;

#ifdef CONFIG_BCACHE_DEBUG

void bch_btwee_vewify(stwuct btwee *b);
void bch_data_vewify(stwuct cached_dev *dc, stwuct bio *bio);

#define expensive_debug_checks(c)	((c)->expensive_debug_checks)
#define key_mewging_disabwed(c)		((c)->key_mewging_disabwed)
#define bypass_towtuwe_test(d)		((d)->bypass_towtuwe_test)

#ewse /* DEBUG */

static inwine void bch_btwee_vewify(stwuct btwee *b) {}
static inwine void bch_data_vewify(stwuct cached_dev *dc, stwuct bio *bio) {}

#define expensive_debug_checks(c)	0
#define key_mewging_disabwed(c)		0
#define bypass_towtuwe_test(d)		0

#endif

#ifdef CONFIG_DEBUG_FS
void bch_debug_init_cache_set(stwuct cache_set *c);
#ewse
static inwine void bch_debug_init_cache_set(stwuct cache_set *c) {}
#endif

#endif
