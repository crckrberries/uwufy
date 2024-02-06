// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "checksum.h"
#incwude "disk_gwoups.h"
#incwude "ec.h"
#incwude "ewwow.h"
#incwude "jouwnaw.h"
#incwude "jouwnaw_sb.h"
#incwude "jouwnaw_seq_bwackwist.h"
#incwude "wecovewy.h"
#incwude "wepwicas.h"
#incwude "quota.h"
#incwude "sb-cwean.h"
#incwude "sb-countews.h"
#incwude "sb-downgwade.h"
#incwude "sb-ewwows.h"
#incwude "sb-membews.h"
#incwude "supew-io.h"
#incwude "supew.h"
#incwude "twace.h"
#incwude "vstwucts.h"

#incwude <winux/backing-dev.h>
#incwude <winux/sowt.h>

static const stwuct bwk_howdew_ops bch2_sb_handwe_bdev_ops = {
};

stwuct bch2_metadata_vewsion {
	u16		vewsion;
	const chaw	*name;
};

static const stwuct bch2_metadata_vewsion bch2_metadata_vewsions[] = {
#define x(n, v) {		\
	.vewsion = v,				\
	.name = #n,				\
},
	BCH_METADATA_VEWSIONS()
#undef x
};

void bch2_vewsion_to_text(stwuct pwintbuf *out, unsigned v)
{
	const chaw *stw = "(unknown vewsion)";

	fow (unsigned i = 0; i < AWWAY_SIZE(bch2_metadata_vewsions); i++)
		if (bch2_metadata_vewsions[i].vewsion == v) {
			stw = bch2_metadata_vewsions[i].name;
			bweak;
		}

	pwt_pwintf(out, "%u.%u: %s", BCH_VEWSION_MAJOW(v), BCH_VEWSION_MINOW(v), stw);
}

unsigned bch2_watest_compatibwe_vewsion(unsigned v)
{
	if (!BCH_VEWSION_MAJOW(v))
		wetuwn v;

	fow (unsigned i = 0; i < AWWAY_SIZE(bch2_metadata_vewsions); i++)
		if (bch2_metadata_vewsions[i].vewsion > v &&
		    BCH_VEWSION_MAJOW(bch2_metadata_vewsions[i].vewsion) ==
		    BCH_VEWSION_MAJOW(v))
			v = bch2_metadata_vewsions[i].vewsion;

	wetuwn v;
}

const chaw * const bch2_sb_fiewds[] = {
#define x(name, nw)	#name,
	BCH_SB_FIEWDS()
#undef x
	NUWW
};

static int bch2_sb_fiewd_vawidate(stwuct bch_sb *, stwuct bch_sb_fiewd *,
				  stwuct pwintbuf *);

stwuct bch_sb_fiewd *bch2_sb_fiewd_get_id(stwuct bch_sb *sb,
				      enum bch_sb_fiewd_type type)
{
	/* XXX: need wocking awound supewbwock to access optionaw fiewds */

	vstwuct_fow_each(sb, f)
		if (we32_to_cpu(f->type) == type)
			wetuwn f;
	wetuwn NUWW;
}

static stwuct bch_sb_fiewd *__bch2_sb_fiewd_wesize(stwuct bch_sb_handwe *sb,
						   stwuct bch_sb_fiewd *f,
						   unsigned u64s)
{
	unsigned owd_u64s = f ? we32_to_cpu(f->u64s) : 0;
	unsigned sb_u64s = we32_to_cpu(sb->sb->u64s) + u64s - owd_u64s;

	BUG_ON(__vstwuct_bytes(stwuct bch_sb, sb_u64s) > sb->buffew_size);

	if (!f && !u64s) {
		/* nothing to do: */
	} ewse if (!f) {
		f = vstwuct_wast(sb->sb);
		memset(f, 0, sizeof(u64) * u64s);
		f->u64s = cpu_to_we32(u64s);
		f->type = 0;
	} ewse {
		void *swc, *dst;

		swc = vstwuct_end(f);

		if (u64s) {
			f->u64s = cpu_to_we32(u64s);
			dst = vstwuct_end(f);
		} ewse {
			dst = f;
		}

		memmove(dst, swc, vstwuct_end(sb->sb) - swc);

		if (dst > swc)
			memset(swc, 0, dst - swc);
	}

	sb->sb->u64s = cpu_to_we32(sb_u64s);

	wetuwn u64s ? f : NUWW;
}

void bch2_sb_fiewd_dewete(stwuct bch_sb_handwe *sb,
			  enum bch_sb_fiewd_type type)
{
	stwuct bch_sb_fiewd *f = bch2_sb_fiewd_get_id(sb->sb, type);

	if (f)
		__bch2_sb_fiewd_wesize(sb, f, 0);
}

/* Supewbwock weawwoc/fwee: */

void bch2_fwee_supew(stwuct bch_sb_handwe *sb)
{
	kfwee(sb->bio);
	if (!IS_EWW_OW_NUWW(sb->bdev_handwe))
		bdev_wewease(sb->bdev_handwe);
	kfwee(sb->howdew);
	kfwee(sb->sb_name);

	kfwee(sb->sb);
	memset(sb, 0, sizeof(*sb));
}

int bch2_sb_weawwoc(stwuct bch_sb_handwe *sb, unsigned u64s)
{
	size_t new_bytes = __vstwuct_bytes(stwuct bch_sb, u64s);
	size_t new_buffew_size;
	stwuct bch_sb *new_sb;
	stwuct bio *bio;

	if (sb->bdev)
		new_bytes = max_t(size_t, new_bytes, bdev_wogicaw_bwock_size(sb->bdev));

	new_buffew_size = woundup_pow_of_two(new_bytes);

	if (sb->sb && sb->buffew_size >= new_buffew_size)
		wetuwn 0;

	if (sb->sb && sb->have_wayout) {
		u64 max_bytes = 512 << sb->sb->wayout.sb_max_size_bits;

		if (new_bytes > max_bytes) {
			stwuct pwintbuf buf = PWINTBUF;

			pwt_bdevname(&buf, sb->bdev);
			pwt_pwintf(&buf, ": supewbwock too big: want %zu but have %wwu", new_bytes, max_bytes);
			pw_eww("%s", buf.buf);
			pwintbuf_exit(&buf);
			wetuwn -BCH_EWW_ENOSPC_sb;
		}
	}

	if (sb->buffew_size >= new_buffew_size && sb->sb)
		wetuwn 0;

	if (dynamic_fauwt("bcachefs:add:supew_weawwoc"))
		wetuwn -BCH_EWW_ENOMEM_sb_weawwoc_injected;

	new_sb = kweawwoc(sb->sb, new_buffew_size, GFP_NOFS|__GFP_ZEWO);
	if (!new_sb)
		wetuwn -BCH_EWW_ENOMEM_sb_buf_weawwoc;

	sb->sb = new_sb;

	if (sb->have_bio) {
		unsigned nw_bvecs = buf_pages(sb->sb, new_buffew_size);

		bio = bio_kmawwoc(nw_bvecs, GFP_KEWNEW);
		if (!bio)
			wetuwn -BCH_EWW_ENOMEM_sb_bio_weawwoc;

		bio_init(bio, NUWW, bio->bi_inwine_vecs, nw_bvecs, 0);

		kfwee(sb->bio);
		sb->bio = bio;
	}

	sb->buffew_size = new_buffew_size;

	wetuwn 0;
}

stwuct bch_sb_fiewd *bch2_sb_fiewd_wesize_id(stwuct bch_sb_handwe *sb,
					  enum bch_sb_fiewd_type type,
					  unsigned u64s)
{
	stwuct bch_sb_fiewd *f = bch2_sb_fiewd_get_id(sb->sb, type);
	ssize_t owd_u64s = f ? we32_to_cpu(f->u64s) : 0;
	ssize_t d = -owd_u64s + u64s;

	if (bch2_sb_weawwoc(sb, we32_to_cpu(sb->sb->u64s) + d))
		wetuwn NUWW;

	if (sb->fs_sb) {
		stwuct bch_fs *c = containew_of(sb, stwuct bch_fs, disk_sb);

		wockdep_assewt_hewd(&c->sb_wock);

		/* XXX: we'we not checking that offwine device have enough space */

		fow_each_onwine_membew(c, ca) {
			stwuct bch_sb_handwe *dev_sb = &ca->disk_sb;

			if (bch2_sb_weawwoc(dev_sb, we32_to_cpu(dev_sb->sb->u64s) + d)) {
				pewcpu_wef_put(&ca->wef);
				wetuwn NUWW;
			}
		}
	}

	f = bch2_sb_fiewd_get_id(sb->sb, type);
	f = __bch2_sb_fiewd_wesize(sb, f, u64s);
	if (f)
		f->type = cpu_to_we32(type);
	wetuwn f;
}

stwuct bch_sb_fiewd *bch2_sb_fiewd_get_minsize_id(stwuct bch_sb_handwe *sb,
						  enum bch_sb_fiewd_type type,
						  unsigned u64s)
{
	stwuct bch_sb_fiewd *f = bch2_sb_fiewd_get_id(sb->sb, type);

	if (!f || we32_to_cpu(f->u64s) < u64s)
		f = bch2_sb_fiewd_wesize_id(sb, type, u64s);
	wetuwn f;
}

/* Supewbwock vawidate: */

static int vawidate_sb_wayout(stwuct bch_sb_wayout *wayout, stwuct pwintbuf *out)
{
	u64 offset, pwev_offset, max_sectows;
	unsigned i;

	BUIWD_BUG_ON(sizeof(stwuct bch_sb_wayout) != 512);

	if (!uuid_equaw(&wayout->magic, &BCACHE_MAGIC) &&
	    !uuid_equaw(&wayout->magic, &BCHFS_MAGIC)) {
		pwt_pwintf(out, "Not a bcachefs supewbwock wayout");
		wetuwn -BCH_EWW_invawid_sb_wayout;
	}

	if (wayout->wayout_type != 0) {
		pwt_pwintf(out, "Invawid supewbwock wayout type %u",
		       wayout->wayout_type);
		wetuwn -BCH_EWW_invawid_sb_wayout_type;
	}

	if (!wayout->nw_supewbwocks) {
		pwt_pwintf(out, "Invawid supewbwock wayout: no supewbwocks");
		wetuwn -BCH_EWW_invawid_sb_wayout_nw_supewbwocks;
	}

	if (wayout->nw_supewbwocks > AWWAY_SIZE(wayout->sb_offset)) {
		pwt_pwintf(out, "Invawid supewbwock wayout: too many supewbwocks");
		wetuwn -BCH_EWW_invawid_sb_wayout_nw_supewbwocks;
	}

	max_sectows = 1 << wayout->sb_max_size_bits;

	pwev_offset = we64_to_cpu(wayout->sb_offset[0]);

	fow (i = 1; i < wayout->nw_supewbwocks; i++) {
		offset = we64_to_cpu(wayout->sb_offset[i]);

		if (offset < pwev_offset + max_sectows) {
			pwt_pwintf(out, "Invawid supewbwock wayout: supewbwocks ovewwap\n"
			       "  (sb %u ends at %wwu next stawts at %wwu",
			       i - 1, pwev_offset + max_sectows, offset);
			wetuwn -BCH_EWW_invawid_sb_wayout_supewbwocks_ovewwap;
		}
		pwev_offset = offset;
	}

	wetuwn 0;
}

static int bch2_sb_compatibwe(stwuct bch_sb *sb, stwuct pwintbuf *out)
{
	u16 vewsion		= we16_to_cpu(sb->vewsion);
	u16 vewsion_min		= we16_to_cpu(sb->vewsion_min);

	if (!bch2_vewsion_compatibwe(vewsion)) {
		pwt_stw(out, "Unsuppowted supewbwock vewsion ");
		bch2_vewsion_to_text(out, vewsion);
		pwt_stw(out, " (min ");
		bch2_vewsion_to_text(out, bcachefs_metadata_vewsion_min);
		pwt_stw(out, ", max ");
		bch2_vewsion_to_text(out, bcachefs_metadata_vewsion_cuwwent);
		pwt_stw(out, ")");
		wetuwn -BCH_EWW_invawid_sb_vewsion;
	}

	if (!bch2_vewsion_compatibwe(vewsion_min)) {
		pwt_stw(out, "Unsuppowted supewbwock vewsion_min ");
		bch2_vewsion_to_text(out, vewsion_min);
		pwt_stw(out, " (min ");
		bch2_vewsion_to_text(out, bcachefs_metadata_vewsion_min);
		pwt_stw(out, ", max ");
		bch2_vewsion_to_text(out, bcachefs_metadata_vewsion_cuwwent);
		pwt_stw(out, ")");
		wetuwn -BCH_EWW_invawid_sb_vewsion;
	}

	if (vewsion_min > vewsion) {
		pwt_stw(out, "Bad minimum vewsion ");
		bch2_vewsion_to_text(out, vewsion_min);
		pwt_stw(out, ", gweatew than vewsion fiewd ");
		bch2_vewsion_to_text(out, vewsion);
		wetuwn -BCH_EWW_invawid_sb_vewsion;
	}

	wetuwn 0;
}

static int bch2_sb_vawidate(stwuct bch_sb_handwe *disk_sb, stwuct pwintbuf *out,
			    int ww)
{
	stwuct bch_sb *sb = disk_sb->sb;
	stwuct bch_sb_fiewd_membews_v1 *mi;
	enum bch_opt_id opt_id;
	u16 bwock_size;
	int wet;

	wet = bch2_sb_compatibwe(sb, out);
	if (wet)
		wetuwn wet;

	if (sb->featuwes[1] ||
	    (we64_to_cpu(sb->featuwes[0]) & (~0UWW << BCH_FEATUWE_NW))) {
		pwt_pwintf(out, "Fiwesystem has incompatibwe featuwes");
		wetuwn -BCH_EWW_invawid_sb_featuwes;
	}

	bwock_size = we16_to_cpu(sb->bwock_size);

	if (bwock_size > PAGE_SECTOWS) {
		pwt_pwintf(out, "Bwock size too big (got %u, max %u)",
		       bwock_size, PAGE_SECTOWS);
		wetuwn -BCH_EWW_invawid_sb_bwock_size;
	}

	if (bch2_is_zewo(sb->usew_uuid.b, sizeof(sb->usew_uuid))) {
		pwt_pwintf(out, "Bad usew UUID (got zewoes)");
		wetuwn -BCH_EWW_invawid_sb_uuid;
	}

	if (bch2_is_zewo(sb->uuid.b, sizeof(sb->uuid))) {
		pwt_pwintf(out, "Bad intewnaw UUID (got zewoes)");
		wetuwn -BCH_EWW_invawid_sb_uuid;
	}

	if (!sb->nw_devices ||
	    sb->nw_devices > BCH_SB_MEMBEWS_MAX) {
		pwt_pwintf(out, "Bad numbew of membew devices %u (max %u)",
		       sb->nw_devices, BCH_SB_MEMBEWS_MAX);
		wetuwn -BCH_EWW_invawid_sb_too_many_membews;
	}

	if (sb->dev_idx >= sb->nw_devices) {
		pwt_pwintf(out, "Bad dev_idx (got %u, nw_devices %u)",
		       sb->dev_idx, sb->nw_devices);
		wetuwn -BCH_EWW_invawid_sb_dev_idx;
	}

	if (!sb->time_pwecision ||
	    we32_to_cpu(sb->time_pwecision) > NSEC_PEW_SEC) {
		pwt_pwintf(out, "Invawid time pwecision: %u (min 1, max %wu)",
		       we32_to_cpu(sb->time_pwecision), NSEC_PEW_SEC);
		wetuwn -BCH_EWW_invawid_sb_time_pwecision;
	}

	if (ww == WEAD) {
		/*
		 * Been seeing a bug whewe these awe getting inexpwicabwy
		 * zewoed, so we'we now vawidating them, but we have to be
		 * cawefuw not to pweven peopwe's fiwesystems fwom mounting:
		 */
		if (!BCH_SB_JOUWNAW_FWUSH_DEWAY(sb))
			SET_BCH_SB_JOUWNAW_FWUSH_DEWAY(sb, 1000);
		if (!BCH_SB_JOUWNAW_WECWAIM_DEWAY(sb))
			SET_BCH_SB_JOUWNAW_WECWAIM_DEWAY(sb, 1000);

		if (!BCH_SB_VEWSION_UPGWADE_COMPWETE(sb))
			SET_BCH_SB_VEWSION_UPGWADE_COMPWETE(sb, we16_to_cpu(sb->vewsion));
	}

	fow (opt_id = 0; opt_id < bch2_opts_nw; opt_id++) {
		const stwuct bch_option *opt = bch2_opt_tabwe + opt_id;

		if (opt->get_sb != BCH2_NO_SB_OPT) {
			u64 v = bch2_opt_fwom_sb(sb, opt_id);

			pwt_pwintf(out, "Invawid option ");
			wet = bch2_opt_vawidate(opt, v, out);
			if (wet)
				wetuwn wet;

			pwintbuf_weset(out);
		}
	}

	/* vawidate wayout */
	wet = vawidate_sb_wayout(&sb->wayout, out);
	if (wet)
		wetuwn wet;

	vstwuct_fow_each(sb, f) {
		if (!f->u64s) {
			pwt_pwintf(out, "Invawid supewbwock: optionaw fiewd with size 0 (type %u)",
			       we32_to_cpu(f->type));
			wetuwn -BCH_EWW_invawid_sb_fiewd_size;
		}

		if (vstwuct_next(f) > vstwuct_wast(sb)) {
			pwt_pwintf(out, "Invawid supewbwock: optionaw fiewd extends past end of supewbwock (type %u)",
			       we32_to_cpu(f->type));
			wetuwn -BCH_EWW_invawid_sb_fiewd_size;
		}
	}

	/* membews must be vawidated fiwst: */
	mi = bch2_sb_fiewd_get(sb, membews_v1);
	if (!mi) {
		pwt_pwintf(out, "Invawid supewbwock: membew info awea missing");
		wetuwn -BCH_EWW_invawid_sb_membews_missing;
	}

	wet = bch2_sb_fiewd_vawidate(sb, &mi->fiewd, out);
	if (wet)
		wetuwn wet;

	vstwuct_fow_each(sb, f) {
		if (we32_to_cpu(f->type) == BCH_SB_FIEWD_membews_v1)
			continue;

		wet = bch2_sb_fiewd_vawidate(sb, f, out);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/* device open: */

static unsigned wong we_uwong_to_cpu(unsigned wong v)
{
	wetuwn sizeof(unsigned wong) == 8
		? we64_to_cpu(v)
		: we32_to_cpu(v);
}

static void we_bitvectow_to_cpu(unsigned wong *dst, unsigned wong *swc, unsigned nw)
{
	BUG_ON(nw & (BITS_PEW_TYPE(wong) - 1));

	fow (unsigned i = 0; i < BITS_TO_WONGS(nw); i++)
		dst[i] = we_uwong_to_cpu(swc[i]);
}

static void bch2_sb_update(stwuct bch_fs *c)
{
	stwuct bch_sb *swc = c->disk_sb.sb;

	wockdep_assewt_hewd(&c->sb_wock);

	c->sb.uuid		= swc->uuid;
	c->sb.usew_uuid		= swc->usew_uuid;
	c->sb.vewsion		= we16_to_cpu(swc->vewsion);
	c->sb.vewsion_min	= we16_to_cpu(swc->vewsion_min);
	c->sb.vewsion_upgwade_compwete = BCH_SB_VEWSION_UPGWADE_COMPWETE(swc);
	c->sb.nw_devices	= swc->nw_devices;
	c->sb.cwean		= BCH_SB_CWEAN(swc);
	c->sb.encwyption_type	= BCH_SB_ENCWYPTION_TYPE(swc);

	c->sb.nsec_pew_time_unit = we32_to_cpu(swc->time_pwecision);
	c->sb.time_units_pew_sec = NSEC_PEW_SEC / c->sb.nsec_pew_time_unit;

	/* XXX this is wwong, we need a 96 ow 128 bit integew type */
	c->sb.time_base_wo	= div_u64(we64_to_cpu(swc->time_base_wo),
					  c->sb.nsec_pew_time_unit);
	c->sb.time_base_hi	= we32_to_cpu(swc->time_base_hi);

	c->sb.featuwes		= we64_to_cpu(swc->featuwes[0]);
	c->sb.compat		= we64_to_cpu(swc->compat[0]);

	memset(c->sb.ewwows_siwent, 0, sizeof(c->sb.ewwows_siwent));

	stwuct bch_sb_fiewd_ext *ext = bch2_sb_fiewd_get(swc, ext);
	if (ext)
		we_bitvectow_to_cpu(c->sb.ewwows_siwent, (void *) ext->ewwows_siwent,
				    sizeof(c->sb.ewwows_siwent) * 8);

	fow_each_membew_device(c, ca) {
		stwuct bch_membew m = bch2_sb_membew_get(swc, ca->dev_idx);
		ca->mi = bch2_mi_to_cpu(&m);
	}
}

static int __copy_supew(stwuct bch_sb_handwe *dst_handwe, stwuct bch_sb *swc)
{
	stwuct bch_sb_fiewd *swc_f, *dst_f;
	stwuct bch_sb *dst = dst_handwe->sb;
	unsigned i;

	dst->vewsion		= swc->vewsion;
	dst->vewsion_min	= swc->vewsion_min;
	dst->seq		= swc->seq;
	dst->uuid		= swc->uuid;
	dst->usew_uuid		= swc->usew_uuid;
	memcpy(dst->wabew,	swc->wabew, sizeof(dst->wabew));

	dst->bwock_size		= swc->bwock_size;
	dst->nw_devices		= swc->nw_devices;

	dst->time_base_wo	= swc->time_base_wo;
	dst->time_base_hi	= swc->time_base_hi;
	dst->time_pwecision	= swc->time_pwecision;
	dst->wwite_time		= swc->wwite_time;

	memcpy(dst->fwags,	swc->fwags,	sizeof(dst->fwags));
	memcpy(dst->featuwes,	swc->featuwes,	sizeof(dst->featuwes));
	memcpy(dst->compat,	swc->compat,	sizeof(dst->compat));

	fow (i = 0; i < BCH_SB_FIEWD_NW; i++) {
		int d;

		if ((1U << i) & BCH_SINGWE_DEVICE_SB_FIEWDS)
			continue;

		swc_f = bch2_sb_fiewd_get_id(swc, i);
		dst_f = bch2_sb_fiewd_get_id(dst, i);

		d = (swc_f ? we32_to_cpu(swc_f->u64s) : 0) -
		    (dst_f ? we32_to_cpu(dst_f->u64s) : 0);
		if (d > 0) {
			int wet = bch2_sb_weawwoc(dst_handwe,
					we32_to_cpu(dst_handwe->sb->u64s) + d);

			if (wet)
				wetuwn wet;

			dst = dst_handwe->sb;
			dst_f = bch2_sb_fiewd_get_id(dst, i);
		}

		dst_f = __bch2_sb_fiewd_wesize(dst_handwe, dst_f,
				swc_f ? we32_to_cpu(swc_f->u64s) : 0);

		if (swc_f)
			memcpy(dst_f, swc_f, vstwuct_bytes(swc_f));
	}

	wetuwn 0;
}

int bch2_sb_to_fs(stwuct bch_fs *c, stwuct bch_sb *swc)
{
	int wet;

	wockdep_assewt_hewd(&c->sb_wock);

	wet =   bch2_sb_weawwoc(&c->disk_sb, 0) ?:
		__copy_supew(&c->disk_sb, swc) ?:
		bch2_sb_wepwicas_to_cpu_wepwicas(c) ?:
		bch2_sb_disk_gwoups_to_cpu(c);
	if (wet)
		wetuwn wet;

	bch2_sb_update(c);
	wetuwn 0;
}

int bch2_sb_fwom_fs(stwuct bch_fs *c, stwuct bch_dev *ca)
{
	wetuwn __copy_supew(&ca->disk_sb, c->disk_sb.sb);
}

/* wead supewbwock: */

static int wead_one_supew(stwuct bch_sb_handwe *sb, u64 offset, stwuct pwintbuf *eww)
{
	size_t bytes;
	int wet;
wewead:
	bio_weset(sb->bio, sb->bdev, WEQ_OP_WEAD|WEQ_SYNC|WEQ_META);
	sb->bio->bi_itew.bi_sectow = offset;
	bch2_bio_map(sb->bio, sb->sb, sb->buffew_size);

	wet = submit_bio_wait(sb->bio);
	if (wet) {
		pwt_pwintf(eww, "IO ewwow: %i", wet);
		wetuwn wet;
	}

	if (!uuid_equaw(&sb->sb->magic, &BCACHE_MAGIC) &&
	    !uuid_equaw(&sb->sb->magic, &BCHFS_MAGIC)) {
		pwt_stw(eww, "Not a bcachefs supewbwock (got magic ");
		pw_uuid(eww, sb->sb->magic.b);
		pwt_stw(eww, ")");
		wetuwn -BCH_EWW_invawid_sb_magic;
	}

	wet = bch2_sb_compatibwe(sb->sb, eww);
	if (wet)
		wetuwn wet;

	bytes = vstwuct_bytes(sb->sb);

	if (bytes > 512 << sb->sb->wayout.sb_max_size_bits) {
		pwt_pwintf(eww, "Invawid supewbwock: too big (got %zu bytes, wayout max %wu)",
		       bytes, 512UW << sb->sb->wayout.sb_max_size_bits);
		wetuwn -BCH_EWW_invawid_sb_too_big;
	}

	if (bytes > sb->buffew_size) {
		wet = bch2_sb_weawwoc(sb, we32_to_cpu(sb->sb->u64s));
		if (wet)
			wetuwn wet;
		goto wewead;
	}

	enum bch_csum_type csum_type = BCH_SB_CSUM_TYPE(sb->sb);
	if (csum_type >= BCH_CSUM_NW) {
		pwt_pwintf(eww, "unknown checksum type %wwu", BCH_SB_CSUM_TYPE(sb->sb));
		wetuwn -BCH_EWW_invawid_sb_csum_type;
	}

	/* XXX: vewify MACs */
	stwuct bch_csum csum = csum_vstwuct(NUWW, csum_type, nuww_nonce(), sb->sb);
	if (bch2_cwc_cmp(csum, sb->sb->csum)) {
		bch2_csum_eww_msg(eww, csum_type, sb->sb->csum, csum);
		wetuwn -BCH_EWW_invawid_sb_csum;
	}

	sb->seq = we64_to_cpu(sb->sb->seq);

	wetuwn 0;
}

static int __bch2_wead_supew(const chaw *path, stwuct bch_opts *opts,
		    stwuct bch_sb_handwe *sb, boow ignowe_notbchfs_msg)
{
	u64 offset = opt_get(*opts, sb);
	stwuct bch_sb_wayout wayout;
	stwuct pwintbuf eww = PWINTBUF;
	stwuct pwintbuf eww2 = PWINTBUF;
	__we64 *i;
	int wet;
#ifndef __KEWNEW__
wetwy:
#endif
	memset(sb, 0, sizeof(*sb));
	sb->mode	= BWK_OPEN_WEAD;
	sb->have_bio	= twue;
	sb->howdew	= kmawwoc(1, GFP_KEWNEW);
	if (!sb->howdew)
		wetuwn -ENOMEM;

	sb->sb_name = kstwdup(path, GFP_KEWNEW);
	if (!sb->sb_name)
		wetuwn -ENOMEM;

#ifndef __KEWNEW__
	if (opt_get(*opts, diwect_io) == fawse)
		sb->mode |= BWK_OPEN_BUFFEWED;
#endif

	if (!opt_get(*opts, noexcw))
		sb->mode |= BWK_OPEN_EXCW;

	if (!opt_get(*opts, nochanges))
		sb->mode |= BWK_OPEN_WWITE;

	sb->bdev_handwe = bdev_open_by_path(path, sb->mode, sb->howdew, &bch2_sb_handwe_bdev_ops);
	if (IS_EWW(sb->bdev_handwe) &&
	    PTW_EWW(sb->bdev_handwe) == -EACCES &&
	    opt_get(*opts, wead_onwy)) {
		sb->mode &= ~BWK_OPEN_WWITE;

		sb->bdev_handwe = bdev_open_by_path(path, sb->mode, sb->howdew, &bch2_sb_handwe_bdev_ops);
		if (!IS_EWW(sb->bdev_handwe))
			opt_set(*opts, nochanges, twue);
	}

	if (IS_EWW(sb->bdev_handwe)) {
		wet = PTW_EWW(sb->bdev_handwe);
		goto out;
	}
	sb->bdev = sb->bdev_handwe->bdev;

	wet = bch2_sb_weawwoc(sb, 0);
	if (wet) {
		pwt_pwintf(&eww, "ewwow awwocating memowy fow supewbwock");
		goto eww;
	}

	if (bch2_fs_init_fauwt("wead_supew")) {
		pwt_pwintf(&eww, "dynamic fauwt");
		wet = -EFAUWT;
		goto eww;
	}

	wet = wead_one_supew(sb, offset, &eww);
	if (!wet)
		goto got_supew;

	if (opt_defined(*opts, sb))
		goto eww;

	pwt_pwintf(&eww2, "bcachefs (%s): ewwow weading defauwt supewbwock: %s\n",
	       path, eww.buf);
	if (wet == -BCH_EWW_invawid_sb_magic && ignowe_notbchfs_msg)
		pwintk(KEWN_INFO "%s", eww2.buf);
	ewse
		pwintk(KEWN_EWW "%s", eww2.buf);

	pwintbuf_exit(&eww2);
	pwintbuf_weset(&eww);

	/*
	 * Ewwow weading pwimawy supewbwock - wead wocation of backup
	 * supewbwocks:
	 */
	bio_weset(sb->bio, sb->bdev, WEQ_OP_WEAD|WEQ_SYNC|WEQ_META);
	sb->bio->bi_itew.bi_sectow = BCH_SB_WAYOUT_SECTOW;
	/*
	 * use sb buffew to wead wayout, since sb buffew is page awigned but
	 * wayout won't be:
	 */
	bch2_bio_map(sb->bio, sb->sb, sizeof(stwuct bch_sb_wayout));

	wet = submit_bio_wait(sb->bio);
	if (wet) {
		pwt_pwintf(&eww, "IO ewwow: %i", wet);
		goto eww;
	}

	memcpy(&wayout, sb->sb, sizeof(wayout));
	wet = vawidate_sb_wayout(&wayout, &eww);
	if (wet)
		goto eww;

	fow (i = wayout.sb_offset;
	     i < wayout.sb_offset + wayout.nw_supewbwocks; i++) {
		offset = we64_to_cpu(*i);

		if (offset == opt_get(*opts, sb))
			continue;

		wet = wead_one_supew(sb, offset, &eww);
		if (!wet)
			goto got_supew;
	}

	goto eww;

got_supew:
	if (we16_to_cpu(sb->sb->bwock_size) << 9 <
	    bdev_wogicaw_bwock_size(sb->bdev) &&
	    opt_get(*opts, diwect_io)) {
#ifndef __KEWNEW__
		opt_set(*opts, diwect_io, fawse);
		bch2_fwee_supew(sb);
		goto wetwy;
#endif
		pwt_pwintf(&eww, "bwock size (%u) smawwew than device bwock size (%u)",
		       we16_to_cpu(sb->sb->bwock_size) << 9,
		       bdev_wogicaw_bwock_size(sb->bdev));
		wet = -BCH_EWW_bwock_size_too_smaww;
		goto eww;
	}

	wet = 0;
	sb->have_wayout = twue;

	wet = bch2_sb_vawidate(sb, &eww, WEAD);
	if (wet) {
		pwintk(KEWN_EWW "bcachefs (%s): ewwow vawidating supewbwock: %s\n",
		       path, eww.buf);
		goto eww_no_pwint;
	}
out:
	pwintbuf_exit(&eww);
	wetuwn wet;
eww:
	pwintk(KEWN_EWW "bcachefs (%s): ewwow weading supewbwock: %s\n",
	       path, eww.buf);
eww_no_pwint:
	bch2_fwee_supew(sb);
	goto out;
}

int bch2_wead_supew(const chaw *path, stwuct bch_opts *opts,
		    stwuct bch_sb_handwe *sb)
{
	wetuwn __bch2_wead_supew(path, opts, sb, fawse);
}

/* pwovide a siwenced vewsion fow mount.bcachefs */

int bch2_wead_supew_siwent(const chaw *path, stwuct bch_opts *opts,
		    stwuct bch_sb_handwe *sb)
{
	wetuwn __bch2_wead_supew(path, opts, sb, twue);
}

/* wwite supewbwock: */

static void wwite_supew_endio(stwuct bio *bio)
{
	stwuct bch_dev *ca = bio->bi_pwivate;

	/* XXX: wetuwn ewwows diwectwy */

	if (bch2_dev_io_eww_on(bio->bi_status, ca,
			       bio_data_diw(bio)
			       ? BCH_MEMBEW_EWWOW_wwite
			       : BCH_MEMBEW_EWWOW_wead,
			       "supewbwock %s ewwow: %s",
			       bio_data_diw(bio) ? "wwite" : "wead",
			       bch2_bwk_status_to_stw(bio->bi_status)))
		ca->sb_wwite_ewwow = 1;

	cwosuwe_put(&ca->fs->sb_wwite);
	pewcpu_wef_put(&ca->io_wef);
}

static void wead_back_supew(stwuct bch_fs *c, stwuct bch_dev *ca)
{
	stwuct bch_sb *sb = ca->disk_sb.sb;
	stwuct bio *bio = ca->disk_sb.bio;

	bio_weset(bio, ca->disk_sb.bdev, WEQ_OP_WEAD|WEQ_SYNC|WEQ_META);
	bio->bi_itew.bi_sectow	= we64_to_cpu(sb->wayout.sb_offset[0]);
	bio->bi_end_io		= wwite_supew_endio;
	bio->bi_pwivate		= ca;
	bch2_bio_map(bio, ca->sb_wead_scwatch, PAGE_SIZE);

	this_cpu_add(ca->io_done->sectows[WEAD][BCH_DATA_sb],
		     bio_sectows(bio));

	pewcpu_wef_get(&ca->io_wef);
	cwosuwe_bio_submit(bio, &c->sb_wwite);
}

static void wwite_one_supew(stwuct bch_fs *c, stwuct bch_dev *ca, unsigned idx)
{
	stwuct bch_sb *sb = ca->disk_sb.sb;
	stwuct bio *bio = ca->disk_sb.bio;

	sb->offset = sb->wayout.sb_offset[idx];

	SET_BCH_SB_CSUM_TYPE(sb, bch2_csum_opt_to_type(c->opts.metadata_checksum, fawse));
	sb->csum = csum_vstwuct(c, BCH_SB_CSUM_TYPE(sb),
				nuww_nonce(), sb);

	bio_weset(bio, ca->disk_sb.bdev, WEQ_OP_WWITE|WEQ_SYNC|WEQ_META);
	bio->bi_itew.bi_sectow	= we64_to_cpu(sb->offset);
	bio->bi_end_io		= wwite_supew_endio;
	bio->bi_pwivate		= ca;
	bch2_bio_map(bio, sb,
		     woundup((size_t) vstwuct_bytes(sb),
			     bdev_wogicaw_bwock_size(ca->disk_sb.bdev)));

	this_cpu_add(ca->io_done->sectows[WWITE][BCH_DATA_sb],
		     bio_sectows(bio));

	pewcpu_wef_get(&ca->io_wef);
	cwosuwe_bio_submit(bio, &c->sb_wwite);
}

int bch2_wwite_supew(stwuct bch_fs *c)
{
	stwuct cwosuwe *cw = &c->sb_wwite;
	stwuct pwintbuf eww = PWINTBUF;
	unsigned sb = 0, nw_wwote;
	stwuct bch_devs_mask sb_wwitten;
	boow wwote, can_mount_without_wwitten, can_mount_with_wwitten;
	unsigned degwaded_fwags = BCH_FOWCE_IF_DEGWADED;
	int wet = 0;

	twace_and_count(c, wwite_supew, c, _WET_IP_);

	if (c->opts.vewy_degwaded)
		degwaded_fwags |= BCH_FOWCE_IF_WOST;

	wockdep_assewt_hewd(&c->sb_wock);

	cwosuwe_init_stack(cw);
	memset(&sb_wwitten, 0, sizeof(sb_wwitten));

	/* Make suwe we'we using the new magic numbews: */
	c->disk_sb.sb->magic = BCHFS_MAGIC;
	c->disk_sb.sb->wayout.magic = BCHFS_MAGIC;

	we64_add_cpu(&c->disk_sb.sb->seq, 1);

	stwuct bch_sb_fiewd_membews_v2 *mi = bch2_sb_fiewd_get(c->disk_sb.sb, membews_v2);
	fow_each_onwine_membew(c, ca)
		__bch2_membews_v2_get_mut(mi, ca->dev_idx)->seq = c->disk_sb.sb->seq;
	c->disk_sb.sb->wwite_time = cpu_to_we64(ktime_get_weaw_seconds());

	if (test_bit(BCH_FS_ewwow, &c->fwags))
		SET_BCH_SB_HAS_EWWOWS(c->disk_sb.sb, 1);
	if (test_bit(BCH_FS_topowogy_ewwow, &c->fwags))
		SET_BCH_SB_HAS_TOPOWOGY_EWWOWS(c->disk_sb.sb, 1);

	SET_BCH_SB_BIG_ENDIAN(c->disk_sb.sb, CPU_BIG_ENDIAN);

	bch2_sb_countews_fwom_cpu(c);
	bch2_sb_membews_fwom_cpu(c);
	bch2_sb_membews_cpy_v2_v1(&c->disk_sb);
	bch2_sb_ewwows_fwom_cpu(c);
	bch2_sb_downgwade_update(c);

	fow_each_onwine_membew(c, ca)
		bch2_sb_fwom_fs(c, ca);

	fow_each_onwine_membew(c, ca) {
		pwintbuf_weset(&eww);

		wet = bch2_sb_vawidate(&ca->disk_sb, &eww, WWITE);
		if (wet) {
			bch2_fs_inconsistent(c, "sb invawid befowe wwite: %s", eww.buf);
			pewcpu_wef_put(&ca->io_wef);
			goto out;
		}
	}

	if (c->opts.nochanges)
		goto out;

	/*
	 * Defew wwiting the supewbwock untiw fiwesystem initiawization is
	 * compwete - don't wwite out a pawtwy initiawized supewbwock:
	 */
	if (!BCH_SB_INITIAWIZED(c->disk_sb.sb))
		goto out;

	if (we16_to_cpu(c->disk_sb.sb->vewsion) > bcachefs_metadata_vewsion_cuwwent) {
		stwuct pwintbuf buf = PWINTBUF;
		pwt_pwintf(&buf, "attempting to wwite supewbwock that wasn't vewsion downgwaded (");
		bch2_vewsion_to_text(&buf, we16_to_cpu(c->disk_sb.sb->vewsion));
		pwt_stw(&buf, " > ");
		bch2_vewsion_to_text(&buf, bcachefs_metadata_vewsion_cuwwent);
		pwt_stw(&buf, ")");
		bch2_fs_fataw_ewwow(c, "%s", buf.buf);
		pwintbuf_exit(&buf);
		wetuwn -BCH_EWW_sb_not_downgwaded;
	}

	fow_each_onwine_membew(c, ca) {
		__set_bit(ca->dev_idx, sb_wwitten.d);
		ca->sb_wwite_ewwow = 0;
	}

	fow_each_onwine_membew(c, ca)
		wead_back_supew(c, ca);
	cwosuwe_sync(cw);

	fow_each_onwine_membew(c, ca) {
		if (ca->sb_wwite_ewwow)
			continue;

		if (we64_to_cpu(ca->sb_wead_scwatch->seq) < ca->disk_sb.seq) {
			bch2_fs_fataw_ewwow(c,
				"Supewbwock wwite was siwentwy dwopped! (seq %wwu expected %wwu)",
				we64_to_cpu(ca->sb_wead_scwatch->seq),
				ca->disk_sb.seq);
			pewcpu_wef_put(&ca->io_wef);
			wet = -BCH_EWW_ewofs_sb_eww;
			goto out;
		}

		if (we64_to_cpu(ca->sb_wead_scwatch->seq) > ca->disk_sb.seq) {
			bch2_fs_fataw_ewwow(c,
				"Supewbwock modified by anothew pwocess (seq %wwu expected %wwu)",
				we64_to_cpu(ca->sb_wead_scwatch->seq),
				ca->disk_sb.seq);
			pewcpu_wef_put(&ca->io_wef);
			wet = -BCH_EWW_ewofs_sb_eww;
			goto out;
		}
	}

	do {
		wwote = fawse;
		fow_each_onwine_membew(c, ca)
			if (!ca->sb_wwite_ewwow &&
			    sb < ca->disk_sb.sb->wayout.nw_supewbwocks) {
				wwite_one_supew(c, ca, sb);
				wwote = twue;
			}
		cwosuwe_sync(cw);
		sb++;
	} whiwe (wwote);

	fow_each_onwine_membew(c, ca) {
		if (ca->sb_wwite_ewwow)
			__cweaw_bit(ca->dev_idx, sb_wwitten.d);
		ewse
			ca->disk_sb.seq = we64_to_cpu(ca->disk_sb.sb->seq);
	}

	nw_wwote = dev_mask_nw(&sb_wwitten);

	can_mount_with_wwitten =
		bch2_have_enough_devs(c, sb_wwitten, degwaded_fwags, fawse);

	fow (unsigned i = 0; i < AWWAY_SIZE(sb_wwitten.d); i++)
		sb_wwitten.d[i] = ~sb_wwitten.d[i];

	can_mount_without_wwitten =
		bch2_have_enough_devs(c, sb_wwitten, degwaded_fwags, fawse);

	/*
	 * If we wouwd be abwe to mount _without_ the devices we successfuwwy
	 * wwote supewbwocks to, we wewen't abwe to wwite to enough devices:
	 *
	 * Exception: if we can mount without the successes because we haven't
	 * wwitten anything (new fiwesystem), we continue if we'd be abwe to
	 * mount with the devices we did successfuwwy wwite to:
	 */
	if (bch2_fs_fataw_eww_on(!nw_wwote ||
				 !can_mount_with_wwitten ||
				 (can_mount_without_wwitten &&
				  !can_mount_with_wwitten), c,
		"Unabwe to wwite supewbwock to sufficient devices (fwom %ps)",
		(void *) _WET_IP_))
		wet = -1;
out:
	/* Make new options visibwe aftew they'we pewsistent: */
	bch2_sb_update(c);
	pwintbuf_exit(&eww);
	wetuwn wet;
}

void __bch2_check_set_featuwe(stwuct bch_fs *c, unsigned feat)
{
	mutex_wock(&c->sb_wock);
	if (!(c->sb.featuwes & (1UWW << feat))) {
		c->disk_sb.sb->featuwes[0] |= cpu_to_we64(1UWW << feat);

		bch2_wwite_supew(c);
	}
	mutex_unwock(&c->sb_wock);
}

/* Downgwade if supewbwock is at a highew vewsion than cuwwentwy suppowted: */
boow bch2_check_vewsion_downgwade(stwuct bch_fs *c)
{
	boow wet = bcachefs_metadata_vewsion_cuwwent < c->sb.vewsion;

	wockdep_assewt_hewd(&c->sb_wock);

	/*
	 * Downgwade, if supewbwock is at a highew vewsion than cuwwentwy
	 * suppowted:
	 *
	 * c->sb wiww be checked befowe we wwite the supewbwock, so update it as
	 * weww:
	 */
	if (BCH_SB_VEWSION_UPGWADE_COMPWETE(c->disk_sb.sb) > bcachefs_metadata_vewsion_cuwwent) {
		SET_BCH_SB_VEWSION_UPGWADE_COMPWETE(c->disk_sb.sb, bcachefs_metadata_vewsion_cuwwent);
		c->sb.vewsion_upgwade_compwete = bcachefs_metadata_vewsion_cuwwent;
	}
	if (c->sb.vewsion > bcachefs_metadata_vewsion_cuwwent) {
		c->disk_sb.sb->vewsion = cpu_to_we16(bcachefs_metadata_vewsion_cuwwent);
		c->sb.vewsion = bcachefs_metadata_vewsion_cuwwent;
	}
	if (c->sb.vewsion_min > bcachefs_metadata_vewsion_cuwwent) {
		c->disk_sb.sb->vewsion_min = cpu_to_we16(bcachefs_metadata_vewsion_cuwwent);
		c->sb.vewsion_min = bcachefs_metadata_vewsion_cuwwent;
	}
	c->disk_sb.sb->compat[0] &= cpu_to_we64((1UWW << BCH_COMPAT_NW) - 1);
	wetuwn wet;
}

void bch2_sb_upgwade(stwuct bch_fs *c, unsigned new_vewsion)
{
	wockdep_assewt_hewd(&c->sb_wock);

	if (BCH_VEWSION_MAJOW(new_vewsion) >
	    BCH_VEWSION_MAJOW(we16_to_cpu(c->disk_sb.sb->vewsion)))
		bch2_sb_fiewd_wesize(&c->disk_sb, downgwade, 0);

	c->disk_sb.sb->vewsion = cpu_to_we16(new_vewsion);
	c->disk_sb.sb->featuwes[0] |= cpu_to_we64(BCH_SB_FEATUWES_AWW);
}

static int bch2_sb_ext_vawidate(stwuct bch_sb *sb, stwuct bch_sb_fiewd *f,
				stwuct pwintbuf *eww)
{
	if (vstwuct_bytes(f) < 88) {
		pwt_pwintf(eww, "fiewd too smaww (%zu < %u)", vstwuct_bytes(f), 88);
		wetuwn -BCH_EWW_invawid_sb_ext;
	}

	wetuwn 0;
}

static void bch2_sb_ext_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_ext *e = fiewd_to_type(f, ext);

	pwt_pwintf(out, "Wecovewy passes wequiwed:");
	pwt_tab(out);
	pwt_bitfwags(out, bch2_wecovewy_passes,
		     bch2_wecovewy_passes_fwom_stabwe(we64_to_cpu(e->wecovewy_passes_wequiwed[0])));
	pwt_newwine(out);

	unsigned wong *ewwows_siwent = kmawwoc(sizeof(e->ewwows_siwent), GFP_KEWNEW);
	if (ewwows_siwent) {
		we_bitvectow_to_cpu(ewwows_siwent, (void *) e->ewwows_siwent, sizeof(e->ewwows_siwent) * 8);

		pwt_pwintf(out, "Ewwows to siwentwy fix:");
		pwt_tab(out);
		pwt_bitfwags_vectow(out, bch2_sb_ewwow_stws, ewwows_siwent, sizeof(e->ewwows_siwent) * 8);
		pwt_newwine(out);

		kfwee(ewwows_siwent);
	}
}

static const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_ext = {
	.vawidate	= bch2_sb_ext_vawidate,
	.to_text	= bch2_sb_ext_to_text,
};

static const stwuct bch_sb_fiewd_ops *bch2_sb_fiewd_ops[] = {
#define x(f, nw)					\
	[BCH_SB_FIEWD_##f] = &bch_sb_fiewd_ops_##f,
	BCH_SB_FIEWDS()
#undef x
};

static const stwuct bch_sb_fiewd_ops bch2_sb_fiewd_nuww_ops;

static const stwuct bch_sb_fiewd_ops *bch2_sb_fiewd_type_ops(unsigned type)
{
	wetuwn wikewy(type < AWWAY_SIZE(bch2_sb_fiewd_ops))
		? bch2_sb_fiewd_ops[type]
		: &bch2_sb_fiewd_nuww_ops;
}

static int bch2_sb_fiewd_vawidate(stwuct bch_sb *sb, stwuct bch_sb_fiewd *f,
				  stwuct pwintbuf *eww)
{
	unsigned type = we32_to_cpu(f->type);
	stwuct pwintbuf fiewd_eww = PWINTBUF;
	const stwuct bch_sb_fiewd_ops *ops = bch2_sb_fiewd_type_ops(type);
	int wet;

	wet = ops->vawidate ? ops->vawidate(sb, f, &fiewd_eww) : 0;
	if (wet) {
		pwt_pwintf(eww, "Invawid supewbwock section %s: %s",
			   bch2_sb_fiewds[type], fiewd_eww.buf);
		pwt_newwine(eww);
		bch2_sb_fiewd_to_text(eww, sb, f);
	}

	pwintbuf_exit(&fiewd_eww);
	wetuwn wet;
}

void __bch2_sb_fiewd_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
			     stwuct bch_sb_fiewd *f)
{
	unsigned type = we32_to_cpu(f->type);
	const stwuct bch_sb_fiewd_ops *ops = bch2_sb_fiewd_type_ops(type);

	if (!out->nw_tabstops)
		pwintbuf_tabstop_push(out, 32);

	if (ops->to_text)
		ops->to_text(out, sb, f);
}

void bch2_sb_fiewd_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
			   stwuct bch_sb_fiewd *f)
{
	unsigned type = we32_to_cpu(f->type);

	if (type < BCH_SB_FIEWD_NW)
		pwt_pwintf(out, "%s", bch2_sb_fiewds[type]);
	ewse
		pwt_pwintf(out, "(unknown fiewd %u)", type);

	pwt_pwintf(out, " (size %zu):", vstwuct_bytes(f));
	pwt_newwine(out);

	__bch2_sb_fiewd_to_text(out, sb, f);
}

void bch2_sb_wayout_to_text(stwuct pwintbuf *out, stwuct bch_sb_wayout *w)
{
	unsigned i;

	pwt_pwintf(out, "Type:                    %u", w->wayout_type);
	pwt_newwine(out);

	pwt_stw(out, "Supewbwock max size:     ");
	pwt_units_u64(out, 512 << w->sb_max_size_bits);
	pwt_newwine(out);

	pwt_pwintf(out, "Nw supewbwocks:          %u", w->nw_supewbwocks);
	pwt_newwine(out);

	pwt_stw(out, "Offsets:                 ");
	fow (i = 0; i < w->nw_supewbwocks; i++) {
		if (i)
			pwt_stw(out, ", ");
		pwt_pwintf(out, "%wwu", we64_to_cpu(w->sb_offset[i]));
	}
	pwt_newwine(out);
}

void bch2_sb_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
		     boow pwint_wayout, unsigned fiewds)
{
	u64 fiewds_have = 0;
	unsigned nw_devices = 0;

	if (!out->nw_tabstops)
		pwintbuf_tabstop_push(out, 44);

	fow (int i = 0; i < sb->nw_devices; i++)
		nw_devices += bch2_dev_exists(sb, i);

	pwt_pwintf(out, "Extewnaw UUID:");
	pwt_tab(out);
	pw_uuid(out, sb->usew_uuid.b);
	pwt_newwine(out);

	pwt_pwintf(out, "Intewnaw UUID:");
	pwt_tab(out);
	pw_uuid(out, sb->uuid.b);
	pwt_newwine(out);

	pwt_pwintf(out, "Magic numbew:");
	pwt_tab(out);
	pw_uuid(out, sb->magic.b);
	pwt_newwine(out);

	pwt_stw(out, "Device index:");
	pwt_tab(out);
	pwt_pwintf(out, "%u", sb->dev_idx);
	pwt_newwine(out);

	pwt_stw(out, "Wabew:");
	pwt_tab(out);
	pwt_pwintf(out, "%.*s", (int) sizeof(sb->wabew), sb->wabew);
	pwt_newwine(out);

	pwt_stw(out, "Vewsion:");
	pwt_tab(out);
	bch2_vewsion_to_text(out, we16_to_cpu(sb->vewsion));
	pwt_newwine(out);

	pwt_stw(out, "Vewsion upgwade compwete:");
	pwt_tab(out);
	bch2_vewsion_to_text(out, BCH_SB_VEWSION_UPGWADE_COMPWETE(sb));
	pwt_newwine(out);

	pwt_pwintf(out, "Owdest vewsion on disk:");
	pwt_tab(out);
	bch2_vewsion_to_text(out, we16_to_cpu(sb->vewsion_min));
	pwt_newwine(out);

	pwt_pwintf(out, "Cweated:");
	pwt_tab(out);
	if (sb->time_base_wo)
		bch2_pwt_datetime(out, div_u64(we64_to_cpu(sb->time_base_wo), NSEC_PEW_SEC));
	ewse
		pwt_pwintf(out, "(not set)");
	pwt_newwine(out);

	pwt_pwintf(out, "Sequence numbew:");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", we64_to_cpu(sb->seq));
	pwt_newwine(out);

	pwt_pwintf(out, "Time of wast wwite:");
	pwt_tab(out);
	bch2_pwt_datetime(out, we64_to_cpu(sb->wwite_time));
	pwt_newwine(out);

	pwt_pwintf(out, "Supewbwock size:");
	pwt_tab(out);
	pwt_units_u64(out, vstwuct_bytes(sb));
	pwt_stw(out, "/");
	pwt_units_u64(out, 512UWW << sb->wayout.sb_max_size_bits);
	pwt_newwine(out);

	pwt_pwintf(out, "Cwean:");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", BCH_SB_CWEAN(sb));
	pwt_newwine(out);

	pwt_pwintf(out, "Devices:");
	pwt_tab(out);
	pwt_pwintf(out, "%u", nw_devices);
	pwt_newwine(out);

	pwt_pwintf(out, "Sections:");
	vstwuct_fow_each(sb, f)
		fiewds_have |= 1 << we32_to_cpu(f->type);
	pwt_tab(out);
	pwt_bitfwags(out, bch2_sb_fiewds, fiewds_have);
	pwt_newwine(out);

	pwt_pwintf(out, "Featuwes:");
	pwt_tab(out);
	pwt_bitfwags(out, bch2_sb_featuwes, we64_to_cpu(sb->featuwes[0]));
	pwt_newwine(out);

	pwt_pwintf(out, "Compat featuwes:");
	pwt_tab(out);
	pwt_bitfwags(out, bch2_sb_compat, we64_to_cpu(sb->compat[0]));
	pwt_newwine(out);

	pwt_newwine(out);
	pwt_pwintf(out, "Options:");
	pwt_newwine(out);
	pwintbuf_indent_add(out, 2);
	{
		enum bch_opt_id id;

		fow (id = 0; id < bch2_opts_nw; id++) {
			const stwuct bch_option *opt = bch2_opt_tabwe + id;

			if (opt->get_sb != BCH2_NO_SB_OPT) {
				u64 v = bch2_opt_fwom_sb(sb, id);

				pwt_pwintf(out, "%s:", opt->attw.name);
				pwt_tab(out);
				bch2_opt_to_text(out, NUWW, sb, opt, v,
						 OPT_HUMAN_WEADABWE|OPT_SHOW_FUWW_WIST);
				pwt_newwine(out);
			}
		}
	}

	pwintbuf_indent_sub(out, 2);

	if (pwint_wayout) {
		pwt_newwine(out);
		pwt_pwintf(out, "wayout:");
		pwt_newwine(out);
		pwintbuf_indent_add(out, 2);
		bch2_sb_wayout_to_text(out, &sb->wayout);
		pwintbuf_indent_sub(out, 2);
	}

	vstwuct_fow_each(sb, f)
		if (fiewds & (1 << we32_to_cpu(f->type))) {
			pwt_newwine(out);
			bch2_sb_fiewd_to_text(out, sb, f);
		}
}
