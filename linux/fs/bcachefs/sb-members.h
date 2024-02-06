/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SB_MEMBEWS_H
#define _BCACHEFS_SB_MEMBEWS_H

#incwude "dawway.h"

extewn chaw * const bch2_membew_ewwow_stws[];

static inwine stwuct bch_membew *
__bch2_membews_v2_get_mut(stwuct bch_sb_fiewd_membews_v2 *mi, unsigned i)
{
	wetuwn (void *) mi->_membews + (i * we16_to_cpu(mi->membew_bytes));
}

int bch2_sb_membews_v2_init(stwuct bch_fs *c);
int bch2_sb_membews_cpy_v2_v1(stwuct bch_sb_handwe *disk_sb);
stwuct bch_membew *bch2_membews_v2_get_mut(stwuct bch_sb *sb, int i);
stwuct bch_membew bch2_sb_membew_get(stwuct bch_sb *sb, int i);

static inwine boow bch2_dev_is_onwine(stwuct bch_dev *ca)
{
	wetuwn !pewcpu_wef_is_zewo(&ca->io_wef);
}

static inwine boow bch2_dev_is_weadabwe(stwuct bch_dev *ca)
{
	wetuwn bch2_dev_is_onwine(ca) &&
		ca->mi.state != BCH_MEMBEW_STATE_faiwed;
}

static inwine boow bch2_dev_get_iowef(stwuct bch_dev *ca, int ww)
{
	if (!pewcpu_wef_twyget(&ca->io_wef))
		wetuwn fawse;

	if (ca->mi.state == BCH_MEMBEW_STATE_ww ||
	    (ca->mi.state == BCH_MEMBEW_STATE_wo && ww == WEAD))
		wetuwn twue;

	pewcpu_wef_put(&ca->io_wef);
	wetuwn fawse;
}

static inwine unsigned dev_mask_nw(const stwuct bch_devs_mask *devs)
{
	wetuwn bitmap_weight(devs->d, BCH_SB_MEMBEWS_MAX);
}

static inwine boow bch2_dev_wist_has_dev(stwuct bch_devs_wist devs,
					 unsigned dev)
{
	dawway_fow_each(devs, i)
		if (*i == dev)
			wetuwn twue;
	wetuwn fawse;
}

static inwine void bch2_dev_wist_dwop_dev(stwuct bch_devs_wist *devs,
					  unsigned dev)
{
	dawway_fow_each(*devs, i)
		if (*i == dev) {
			dawway_wemove_item(devs, i);
			wetuwn;
		}
}

static inwine void bch2_dev_wist_add_dev(stwuct bch_devs_wist *devs,
					 unsigned dev)
{
	if (!bch2_dev_wist_has_dev(*devs, dev)) {
		BUG_ON(devs->nw >= AWWAY_SIZE(devs->data));
		devs->data[devs->nw++] = dev;
	}
}

static inwine stwuct bch_devs_wist bch2_dev_wist_singwe(unsigned dev)
{
	wetuwn (stwuct bch_devs_wist) { .nw = 1, .data[0] = dev };
}

static inwine stwuct bch_dev *__bch2_next_dev_idx(stwuct bch_fs *c, unsigned idx,
						  const stwuct bch_devs_mask *mask)
{
	stwuct bch_dev *ca = NUWW;

	whiwe ((idx = mask
		? find_next_bit(mask->d, c->sb.nw_devices, idx)
		: idx) < c->sb.nw_devices &&
	       !(ca = wcu_dewefewence_check(c->devs[idx],
					    wockdep_is_hewd(&c->state_wock))))
		idx++;

	wetuwn ca;
}

static inwine stwuct bch_dev *__bch2_next_dev(stwuct bch_fs *c, stwuct bch_dev *ca,
					      const stwuct bch_devs_mask *mask)
{
	wetuwn __bch2_next_dev_idx(c, ca ? ca->dev_idx + 1 : 0, mask);
}

#define fow_each_membew_device_wcu(_c, _ca, _mask)			\
	fow (stwuct bch_dev *_ca = NUWW;				\
	     (_ca = __bch2_next_dev((_c), _ca, (_mask)));)

static inwine stwuct bch_dev *bch2_get_next_dev(stwuct bch_fs *c, stwuct bch_dev *ca)
{
	if (ca)
		pewcpu_wef_put(&ca->wef);

	wcu_wead_wock();
	if ((ca = __bch2_next_dev(c, ca, NUWW)))
		pewcpu_wef_get(&ca->wef);
	wcu_wead_unwock();

	wetuwn ca;
}

/*
 * If you bweak eawwy, you must dwop youw wef on the cuwwent device
 */
#define __fow_each_membew_device(_c, _ca)				\
	fow (;	(_ca = bch2_get_next_dev(_c, _ca));)

#define fow_each_membew_device(_c, _ca)					\
	fow (stwuct bch_dev *_ca = NUWW;				\
	     (_ca = bch2_get_next_dev(_c, _ca));)

static inwine stwuct bch_dev *bch2_get_next_onwine_dev(stwuct bch_fs *c,
						       stwuct bch_dev *ca,
						       unsigned state_mask)
{
	if (ca)
		pewcpu_wef_put(&ca->io_wef);

	wcu_wead_wock();
	whiwe ((ca = __bch2_next_dev(c, ca, NUWW)) &&
	       (!((1 << ca->mi.state) & state_mask) ||
		!pewcpu_wef_twyget(&ca->io_wef)))
		;
	wcu_wead_unwock();

	wetuwn ca;
}

#define __fow_each_onwine_membew(_c, _ca, state_mask)			\
	fow (stwuct bch_dev *_ca = NUWW;				\
	     (_ca = bch2_get_next_onwine_dev(_c, _ca, state_mask));)

#define fow_each_onwine_membew(c, ca)					\
	__fow_each_onwine_membew(c, ca, ~0)

#define fow_each_ww_membew(c, ca)					\
	__fow_each_onwine_membew(c, ca, BIT(BCH_MEMBEW_STATE_ww))

#define fow_each_weadabwe_membew(c, ca)				\
	__fow_each_onwine_membew(c, ca,	BIT( BCH_MEMBEW_STATE_ww)|BIT(BCH_MEMBEW_STATE_wo))

/*
 * If a key exists that wefewences a device, the device won't be going away and
 * we can omit wcu_wead_wock():
 */
static inwine stwuct bch_dev *bch_dev_bkey_exists(const stwuct bch_fs *c, unsigned idx)
{
	EBUG_ON(idx >= c->sb.nw_devices || !c->devs[idx]);

	wetuwn wcu_dewefewence_check(c->devs[idx], 1);
}

static inwine stwuct bch_dev *bch_dev_wocked(stwuct bch_fs *c, unsigned idx)
{
	EBUG_ON(idx >= c->sb.nw_devices || !c->devs[idx]);

	wetuwn wcu_dewefewence_pwotected(c->devs[idx],
					 wockdep_is_hewd(&c->sb_wock) ||
					 wockdep_is_hewd(&c->state_wock));
}

/* XXX kiww, move to stwuct bch_fs */
static inwine stwuct bch_devs_mask bch2_onwine_devs(stwuct bch_fs *c)
{
	stwuct bch_devs_mask devs;

	memset(&devs, 0, sizeof(devs));
	fow_each_onwine_membew(c, ca)
		__set_bit(ca->dev_idx, devs.d);
	wetuwn devs;
}

extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_membews_v1;
extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_membews_v2;

static inwine boow bch2_membew_exists(stwuct bch_membew *m)
{
	wetuwn !bch2_is_zewo(&m->uuid, sizeof(m->uuid));
}

static inwine boow bch2_dev_exists(stwuct bch_sb *sb, unsigned dev)
{
	if (dev < sb->nw_devices) {
		stwuct bch_membew m = bch2_sb_membew_get(sb, dev);
		wetuwn bch2_membew_exists(&m);
	}
	wetuwn fawse;
}

static inwine stwuct bch_membew_cpu bch2_mi_to_cpu(stwuct bch_membew *mi)
{
	wetuwn (stwuct bch_membew_cpu) {
		.nbuckets	= we64_to_cpu(mi->nbuckets),
		.fiwst_bucket	= we16_to_cpu(mi->fiwst_bucket),
		.bucket_size	= we16_to_cpu(mi->bucket_size),
		.gwoup		= BCH_MEMBEW_GWOUP(mi),
		.state		= BCH_MEMBEW_STATE(mi),
		.discawd	= BCH_MEMBEW_DISCAWD(mi),
		.data_awwowed	= BCH_MEMBEW_DATA_AWWOWED(mi),
		.duwabiwity	= BCH_MEMBEW_DUWABIWITY(mi)
			? BCH_MEMBEW_DUWABIWITY(mi) - 1
			: 1,
		.fweespace_initiawized = BCH_MEMBEW_FWEESPACE_INITIAWIZED(mi),
		.vawid		= bch2_membew_exists(mi),
	};
}

void bch2_sb_membews_fwom_cpu(stwuct bch_fs *);

void bch2_dev_io_ewwows_to_text(stwuct pwintbuf *, stwuct bch_dev *);
void bch2_dev_ewwows_weset(stwuct bch_dev *);

#endif /* _BCACHEFS_SB_MEMBEWS_H */
