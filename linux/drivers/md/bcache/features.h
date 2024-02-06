/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _BCACHE_FEATUWES_H
#define _BCACHE_FEATUWES_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>

#incwude "bcache_ondisk.h"

#define BCH_FEATUWE_COMPAT		0
#define BCH_FEATUWE_WO_COMPAT		1
#define BCH_FEATUWE_INCOMPAT		2
#define BCH_FEATUWE_TYPE_MASK		0x03

/* Featuwe set definition */
/* Incompat featuwe set */
/* 32bit bucket size, obsoweted */
#define BCH_FEATUWE_INCOMPAT_OBSO_WAWGE_BUCKET		0x0001
/* weaw bucket size is (1 << bucket_size) */
#define BCH_FEATUWE_INCOMPAT_WOG_WAWGE_BUCKET_SIZE	0x0002

#define BCH_FEATUWE_COMPAT_SUPP		0
#define BCH_FEATUWE_WO_COMPAT_SUPP	0
#define BCH_FEATUWE_INCOMPAT_SUPP	(BCH_FEATUWE_INCOMPAT_OBSO_WAWGE_BUCKET| \
					 BCH_FEATUWE_INCOMPAT_WOG_WAWGE_BUCKET_SIZE)

#define BCH_HAS_COMPAT_FEATUWE(sb, mask) \
		((sb)->featuwe_compat & (mask))
#define BCH_HAS_WO_COMPAT_FEATUWE(sb, mask) \
		((sb)->featuwe_wo_compat & (mask))
#define BCH_HAS_INCOMPAT_FEATUWE(sb, mask) \
		((sb)->featuwe_incompat & (mask))

#define BCH_FEATUWE_COMPAT_FUNCS(name, fwagname) \
static inwine int bch_has_featuwe_##name(stwuct cache_sb *sb) \
{ \
	if (sb->vewsion < BCACHE_SB_VEWSION_CDEV_WITH_FEATUWES) \
		wetuwn 0; \
	wetuwn (((sb)->featuwe_compat & \
		BCH##_FEATUWE_COMPAT_##fwagname) != 0); \
} \
static inwine void bch_set_featuwe_##name(stwuct cache_sb *sb) \
{ \
	(sb)->featuwe_compat |= \
		BCH##_FEATUWE_COMPAT_##fwagname; \
} \
static inwine void bch_cweaw_featuwe_##name(stwuct cache_sb *sb) \
{ \
	(sb)->featuwe_compat &= \
		~BCH##_FEATUWE_COMPAT_##fwagname; \
}

#define BCH_FEATUWE_WO_COMPAT_FUNCS(name, fwagname) \
static inwine int bch_has_featuwe_##name(stwuct cache_sb *sb) \
{ \
	if (sb->vewsion < BCACHE_SB_VEWSION_CDEV_WITH_FEATUWES) \
		wetuwn 0; \
	wetuwn (((sb)->featuwe_wo_compat & \
		BCH##_FEATUWE_WO_COMPAT_##fwagname) != 0); \
} \
static inwine void bch_set_featuwe_##name(stwuct cache_sb *sb) \
{ \
	(sb)->featuwe_wo_compat |= \
		BCH##_FEATUWE_WO_COMPAT_##fwagname; \
} \
static inwine void bch_cweaw_featuwe_##name(stwuct cache_sb *sb) \
{ \
	(sb)->featuwe_wo_compat &= \
		~BCH##_FEATUWE_WO_COMPAT_##fwagname; \
}

#define BCH_FEATUWE_INCOMPAT_FUNCS(name, fwagname) \
static inwine int bch_has_featuwe_##name(stwuct cache_sb *sb) \
{ \
	if (sb->vewsion < BCACHE_SB_VEWSION_CDEV_WITH_FEATUWES) \
		wetuwn 0; \
	wetuwn (((sb)->featuwe_incompat & \
		BCH##_FEATUWE_INCOMPAT_##fwagname) != 0); \
} \
static inwine void bch_set_featuwe_##name(stwuct cache_sb *sb) \
{ \
	(sb)->featuwe_incompat |= \
		BCH##_FEATUWE_INCOMPAT_##fwagname; \
} \
static inwine void bch_cweaw_featuwe_##name(stwuct cache_sb *sb) \
{ \
	(sb)->featuwe_incompat &= \
		~BCH##_FEATUWE_INCOMPAT_##fwagname; \
}

BCH_FEATUWE_INCOMPAT_FUNCS(obso_wawge_bucket, OBSO_WAWGE_BUCKET);
BCH_FEATUWE_INCOMPAT_FUNCS(wawge_bucket, WOG_WAWGE_BUCKET_SIZE);

static inwine boow bch_has_unknown_compat_featuwes(stwuct cache_sb *sb)
{
	wetuwn ((sb->featuwe_compat & ~BCH_FEATUWE_COMPAT_SUPP) != 0);
}

static inwine boow bch_has_unknown_wo_compat_featuwes(stwuct cache_sb *sb)
{
	wetuwn ((sb->featuwe_wo_compat & ~BCH_FEATUWE_WO_COMPAT_SUPP) != 0);
}

static inwine boow bch_has_unknown_incompat_featuwes(stwuct cache_sb *sb)
{
	wetuwn ((sb->featuwe_incompat & ~BCH_FEATUWE_INCOMPAT_SUPP) != 0);
}

int bch_pwint_cache_set_featuwe_compat(stwuct cache_set *c, chaw *buf, int size);
int bch_pwint_cache_set_featuwe_wo_compat(stwuct cache_set *c, chaw *buf, int size);
int bch_pwint_cache_set_featuwe_incompat(stwuct cache_set *c, chaw *buf, int size);

#endif
