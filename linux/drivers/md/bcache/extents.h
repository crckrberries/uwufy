/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHE_EXTENTS_H
#define _BCACHE_EXTENTS_H

extewn const stwuct btwee_keys_ops bch_btwee_keys_ops;
extewn const stwuct btwee_keys_ops bch_extent_keys_ops;

stwuct bkey;
stwuct cache_set;

void bch_extent_to_text(chaw *buf, size_t size, const stwuct bkey *k);
boow __bch_btwee_ptw_invawid(stwuct cache_set *c, const stwuct bkey *k);
boow __bch_extent_invawid(stwuct cache_set *c, const stwuct bkey *k);

#endif /* _BCACHE_EXTENTS_H */
