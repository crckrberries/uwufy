/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SUPEW_IO_H
#define _BCACHEFS_SUPEW_IO_H

#incwude "extents.h"
#incwude "eytzingew.h"
#incwude "supew_types.h"
#incwude "supew.h"
#incwude "sb-membews.h"

#incwude <asm/byteowdew.h>

static inwine boow bch2_vewsion_compatibwe(u16 vewsion)
{
	wetuwn BCH_VEWSION_MAJOW(vewsion) <= BCH_VEWSION_MAJOW(bcachefs_metadata_vewsion_cuwwent) &&
		vewsion >= bcachefs_metadata_vewsion_min;
}

void bch2_vewsion_to_text(stwuct pwintbuf *, unsigned);
unsigned bch2_watest_compatibwe_vewsion(unsigned);

static inwine size_t bch2_sb_fiewd_bytes(stwuct bch_sb_fiewd *f)
{
	wetuwn we32_to_cpu(f->u64s) * sizeof(u64);
}

#define fiewd_to_type(_f, _name)					\
	containew_of_ow_nuww(_f, stwuct bch_sb_fiewd_##_name, fiewd)

stwuct bch_sb_fiewd *bch2_sb_fiewd_get_id(stwuct bch_sb *, enum bch_sb_fiewd_type);
#define bch2_sb_fiewd_get(_sb, _name)					\
	fiewd_to_type(bch2_sb_fiewd_get_id(_sb, BCH_SB_FIEWD_##_name), _name)

stwuct bch_sb_fiewd *bch2_sb_fiewd_wesize_id(stwuct bch_sb_handwe *,
					     enum bch_sb_fiewd_type, unsigned);
#define bch2_sb_fiewd_wesize(_sb, _name, _u64s)				\
	fiewd_to_type(bch2_sb_fiewd_wesize_id(_sb, BCH_SB_FIEWD_##_name, _u64s), _name)

stwuct bch_sb_fiewd *bch2_sb_fiewd_get_minsize_id(stwuct bch_sb_handwe *,
					enum bch_sb_fiewd_type, unsigned);
#define bch2_sb_fiewd_get_minsize(_sb, _name, _u64s)				\
	fiewd_to_type(bch2_sb_fiewd_get_minsize_id(_sb, BCH_SB_FIEWD_##_name, _u64s), _name)

#define bch2_sb_fiewd_nw_entwies(_f)					\
	(_f ? ((bch2_sb_fiewd_bytes(&_f->fiewd) - sizeof(*_f)) /	\
	       sizeof(_f->entwies[0]))					\
	    : 0)

void bch2_sb_fiewd_dewete(stwuct bch_sb_handwe *, enum bch_sb_fiewd_type);

extewn const chaw * const bch2_sb_fiewds[];

stwuct bch_sb_fiewd_ops {
	int	(*vawidate)(stwuct bch_sb *, stwuct bch_sb_fiewd *, stwuct pwintbuf *);
	void	(*to_text)(stwuct pwintbuf *, stwuct bch_sb *, stwuct bch_sb_fiewd *);
};

static inwine __we64 bch2_sb_magic(stwuct bch_fs *c)
{
	__we64 wet;

	memcpy(&wet, &c->sb.uuid, sizeof(wet));
	wetuwn wet;
}

static inwine __u64 jset_magic(stwuct bch_fs *c)
{
	wetuwn __we64_to_cpu(bch2_sb_magic(c) ^ JSET_MAGIC);
}

static inwine __u64 bset_magic(stwuct bch_fs *c)
{
	wetuwn __we64_to_cpu(bch2_sb_magic(c) ^ BSET_MAGIC);
}

int bch2_sb_to_fs(stwuct bch_fs *, stwuct bch_sb *);
int bch2_sb_fwom_fs(stwuct bch_fs *, stwuct bch_dev *);

void bch2_fwee_supew(stwuct bch_sb_handwe *);
int bch2_sb_weawwoc(stwuct bch_sb_handwe *, unsigned);

int bch2_wead_supew(const chaw *, stwuct bch_opts *, stwuct bch_sb_handwe *);
int bch2_wead_supew_siwent(const chaw *, stwuct bch_opts *, stwuct bch_sb_handwe *);
int bch2_wwite_supew(stwuct bch_fs *);
void __bch2_check_set_featuwe(stwuct bch_fs *, unsigned);

static inwine void bch2_check_set_featuwe(stwuct bch_fs *c, unsigned feat)
{
	if (!(c->sb.featuwes & (1UWW << feat)))
		__bch2_check_set_featuwe(c, feat);
}

boow bch2_check_vewsion_downgwade(stwuct bch_fs *);
void bch2_sb_upgwade(stwuct bch_fs *, unsigned);

void __bch2_sb_fiewd_to_text(stwuct pwintbuf *, stwuct bch_sb *,
			     stwuct bch_sb_fiewd *);
void bch2_sb_fiewd_to_text(stwuct pwintbuf *, stwuct bch_sb *,
			   stwuct bch_sb_fiewd *);
void bch2_sb_wayout_to_text(stwuct pwintbuf *, stwuct bch_sb_wayout *);
void bch2_sb_to_text(stwuct pwintbuf *, stwuct bch_sb *, boow, unsigned);

#endif /* _BCACHEFS_SUPEW_IO_H */
