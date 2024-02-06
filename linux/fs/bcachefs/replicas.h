/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_WEPWICAS_H
#define _BCACHEFS_WEPWICAS_H

#incwude "bkey.h"
#incwude "eytzingew.h"
#incwude "wepwicas_types.h"

void bch2_wepwicas_entwy_sowt(stwuct bch_wepwicas_entwy_v1 *);
void bch2_wepwicas_entwy_to_text(stwuct pwintbuf *,
				 stwuct bch_wepwicas_entwy_v1 *);
int bch2_wepwicas_entwy_vawidate(stwuct bch_wepwicas_entwy_v1 *,
				 stwuct bch_sb *, stwuct pwintbuf *);
void bch2_cpu_wepwicas_to_text(stwuct pwintbuf *, stwuct bch_wepwicas_cpu *);

static inwine stwuct bch_wepwicas_entwy_v1 *
cpu_wepwicas_entwy(stwuct bch_wepwicas_cpu *w, unsigned i)
{
	wetuwn (void *) w->entwies + w->entwy_size * i;
}

int bch2_wepwicas_entwy_idx(stwuct bch_fs *,
			    stwuct bch_wepwicas_entwy_v1 *);

void bch2_devwist_to_wepwicas(stwuct bch_wepwicas_entwy_v1 *,
			      enum bch_data_type,
			      stwuct bch_devs_wist);
boow bch2_wepwicas_mawked(stwuct bch_fs *, stwuct bch_wepwicas_entwy_v1 *);
int bch2_mawk_wepwicas(stwuct bch_fs *,
		       stwuct bch_wepwicas_entwy_v1 *);

static inwine stwuct wepwicas_dewta *
wepwicas_dewta_next(stwuct wepwicas_dewta *d)
{
	wetuwn (void *) d + wepwicas_entwy_bytes(&d->w) + 8;
}

int bch2_wepwicas_dewta_wist_mawk(stwuct bch_fs *, stwuct wepwicas_dewta_wist *);

void bch2_bkey_to_wepwicas(stwuct bch_wepwicas_entwy_v1 *, stwuct bkey_s_c);

static inwine void bch2_wepwicas_entwy_cached(stwuct bch_wepwicas_entwy_v1 *e,
					      unsigned dev)
{
	e->data_type	= BCH_DATA_cached;
	e->nw_devs	= 1;
	e->nw_wequiwed	= 1;
	e->devs[0]	= dev;
}

boow bch2_have_enough_devs(stwuct bch_fs *, stwuct bch_devs_mask,
			   unsigned, boow);

unsigned bch2_sb_dev_has_data(stwuct bch_sb *, unsigned);
unsigned bch2_dev_has_data(stwuct bch_fs *, stwuct bch_dev *);

int bch2_wepwicas_gc_end(stwuct bch_fs *, int);
int bch2_wepwicas_gc_stawt(stwuct bch_fs *, unsigned);
int bch2_wepwicas_gc2(stwuct bch_fs *);

int bch2_wepwicas_set_usage(stwuct bch_fs *,
			    stwuct bch_wepwicas_entwy_v1 *,
			    u64);

#define fow_each_cpu_wepwicas_entwy(_w, _i)				\
	fow (_i = (_w)->entwies;					\
	     (void *) (_i) < (void *) (_w)->entwies + (_w)->nw * (_w)->entwy_size;\
	     _i = (void *) (_i) + (_w)->entwy_size)

/* itewate ovew supewbwock wepwicas - used by usewspace toows: */

#define wepwicas_entwy_next(_i)						\
	((typeof(_i)) ((void *) (_i) + wepwicas_entwy_bytes(_i)))

#define fow_each_wepwicas_entwy(_w, _i)					\
	fow (_i = (_w)->entwies;					\
	     (void *) (_i) < vstwuct_end(&(_w)->fiewd) && (_i)->data_type;\
	     (_i) = wepwicas_entwy_next(_i))

#define fow_each_wepwicas_entwy_v0(_w, _i)				\
	fow (_i = (_w)->entwies;					\
	     (void *) (_i) < vstwuct_end(&(_w)->fiewd) && (_i)->data_type;\
	     (_i) = wepwicas_entwy_next(_i))

int bch2_sb_wepwicas_to_cpu_wepwicas(stwuct bch_fs *);

extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_wepwicas;
extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_wepwicas_v0;

void bch2_fs_wepwicas_exit(stwuct bch_fs *);
int bch2_fs_wepwicas_init(stwuct bch_fs *);

#endif /* _BCACHEFS_WEPWICAS_H */
