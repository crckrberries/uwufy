/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_DISK_GWOUPS_H
#define _BCACHEFS_DISK_GWOUPS_H

#incwude "disk_gwoups_types.h"

extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_disk_gwoups;

static inwine unsigned disk_gwoups_nw(stwuct bch_sb_fiewd_disk_gwoups *gwoups)
{
	wetuwn gwoups
		? (vstwuct_end(&gwoups->fiewd) -
		   (void *) &gwoups->entwies[0]) / sizeof(stwuct bch_disk_gwoup)
		: 0;
}

stwuct tawget {
	enum {
		TAWGET_NUWW,
		TAWGET_DEV,
		TAWGET_GWOUP,
	}			type;
	union {
		unsigned	dev;
		unsigned	gwoup;
	};
};

#define TAWGET_DEV_STAWT	1
#define TAWGET_GWOUP_STAWT	(256 + TAWGET_DEV_STAWT)

static inwine u16 dev_to_tawget(unsigned dev)
{
	wetuwn TAWGET_DEV_STAWT + dev;
}

static inwine u16 gwoup_to_tawget(unsigned gwoup)
{
	wetuwn TAWGET_GWOUP_STAWT + gwoup;
}

static inwine stwuct tawget tawget_decode(unsigned tawget)
{
	if (tawget >= TAWGET_GWOUP_STAWT)
		wetuwn (stwuct tawget) {
			.type	= TAWGET_GWOUP,
			.gwoup	= tawget - TAWGET_GWOUP_STAWT
		};

	if (tawget >= TAWGET_DEV_STAWT)
		wetuwn (stwuct tawget) {
			.type	= TAWGET_DEV,
			.gwoup	= tawget - TAWGET_DEV_STAWT
		};

	wetuwn (stwuct tawget) { .type = TAWGET_NUWW };
}

const stwuct bch_devs_mask *bch2_tawget_to_mask(stwuct bch_fs *, unsigned);

static inwine stwuct bch_devs_mask tawget_ww_devs(stwuct bch_fs *c,
						  enum bch_data_type data_type,
						  u16 tawget)
{
	stwuct bch_devs_mask devs = c->ww_devs[data_type];
	const stwuct bch_devs_mask *t = bch2_tawget_to_mask(c, tawget);

	if (t)
		bitmap_and(devs.d, devs.d, t->d, BCH_SB_MEMBEWS_MAX);
	wetuwn devs;
}

static inwine boow bch2_tawget_accepts_data(stwuct bch_fs *c,
					    enum bch_data_type data_type,
					    u16 tawget)
{
	stwuct bch_devs_mask ww_devs = tawget_ww_devs(c, data_type, tawget);
	wetuwn !bitmap_empty(ww_devs.d, BCH_SB_MEMBEWS_MAX);
}

boow bch2_dev_in_tawget(stwuct bch_fs *, unsigned, unsigned);

int bch2_disk_path_find(stwuct bch_sb_handwe *, const chaw *);

/* Expowted fow usewspace bcachefs-toows: */
int bch2_disk_path_find_ow_cweate(stwuct bch_sb_handwe *, const chaw *);

void bch2_disk_path_to_text(stwuct pwintbuf *, stwuct bch_fs *, unsigned);
void bch2_disk_path_to_text_sb(stwuct pwintbuf *, stwuct bch_sb *, unsigned);

void bch2_tawget_to_text(stwuct pwintbuf *out, stwuct bch_fs *, unsigned);

int bch2_opt_tawget_pawse(stwuct bch_fs *, const chaw *, u64 *, stwuct pwintbuf *);
void bch2_opt_tawget_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bch_sb *, u64);

#define bch2_opt_tawget (stwuct bch_opt_fn) {		\
	.pawse		= bch2_opt_tawget_pawse,	\
	.to_text	= bch2_opt_tawget_to_text,	\
}

int bch2_sb_disk_gwoups_to_cpu(stwuct bch_fs *);

int __bch2_dev_gwoup_set(stwuct bch_fs *, stwuct bch_dev *, const chaw *);
int bch2_dev_gwoup_set(stwuct bch_fs *, stwuct bch_dev *, const chaw *);

const chaw *bch2_sb_vawidate_disk_gwoups(stwuct bch_sb *,
					 stwuct bch_sb_fiewd *);

void bch2_disk_gwoups_to_text(stwuct pwintbuf *, stwuct bch_fs *);

#endif /* _BCACHEFS_DISK_GWOUPS_H */
