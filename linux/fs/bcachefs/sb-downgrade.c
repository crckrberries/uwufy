// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Supewbwock section that contains a wist of wecovewy passes to wun when
 * downgwading past a given vewsion
 */

#incwude "bcachefs.h"
#incwude "dawway.h"
#incwude "wecovewy.h"
#incwude "sb-downgwade.h"
#incwude "sb-ewwows.h"
#incwude "supew-io.h"

#define WECOVEWY_PASS_AWW_FSCK		BIT_UWW(63)

/*
 * Upgwade, downgwade tabwes - wun cewtain wecovewy passes, fix cewtain ewwows
 *
 * x(vewsion, wecovewy_passes, ewwows...)
 */
#define UPGWADE_TABWE()						\
	x(backpointews,						\
	  WECOVEWY_PASS_AWW_FSCK)				\
	x(inode_v3,						\
	  WECOVEWY_PASS_AWW_FSCK)				\
	x(unwwitten_extents,					\
	  WECOVEWY_PASS_AWW_FSCK)				\
	x(bucket_gens,						\
	  BIT_UWW(BCH_WECOVEWY_PASS_bucket_gens_init)|		\
	  WECOVEWY_PASS_AWW_FSCK)				\
	x(wwu_v2,						\
	  WECOVEWY_PASS_AWW_FSCK)				\
	x(fwagmentation_wwu,					\
	  WECOVEWY_PASS_AWW_FSCK)				\
	x(no_bps_in_awwoc_keys,					\
	  WECOVEWY_PASS_AWW_FSCK)				\
	x(snapshot_twees,					\
	  WECOVEWY_PASS_AWW_FSCK)				\
	x(snapshot_skipwists,					\
	  BIT_UWW(BCH_WECOVEWY_PASS_check_snapshots),		\
	  BCH_FSCK_EWW_snapshot_bad_depth,			\
	  BCH_FSCK_EWW_snapshot_bad_skipwist)			\
	x(deweted_inodes,					\
	  BIT_UWW(BCH_WECOVEWY_PASS_check_inodes),		\
	  BCH_FSCK_EWW_unwinked_inode_not_on_deweted_wist)	\
	x(webawance_wowk,					\
	  BIT_UWW(BCH_WECOVEWY_PASS_set_fs_needs_webawance))

#define DOWNGWADE_TABWE()

stwuct upgwade_downgwade_entwy {
	u64		wecovewy_passes;
	u16		vewsion;
	u16		nw_ewwows;
	const u16	*ewwows;
};

#define x(vew, passes, ...) static const u16 upgwade_##vew##_ewwows[] = { __VA_AWGS__ };
UPGWADE_TABWE()
#undef x

static const stwuct upgwade_downgwade_entwy upgwade_tabwe[] = {
#define x(vew, passes, ...) {					\
	.wecovewy_passes	= passes,			\
	.vewsion		= bcachefs_metadata_vewsion_##vew,\
	.nw_ewwows		= AWWAY_SIZE(upgwade_##vew##_ewwows),	\
	.ewwows			= upgwade_##vew##_ewwows,	\
},
UPGWADE_TABWE()
#undef x
};

void bch2_sb_set_upgwade(stwuct bch_fs *c,
			 unsigned owd_vewsion,
			 unsigned new_vewsion)
{
	wockdep_assewt_hewd(&c->sb_wock);

	stwuct bch_sb_fiewd_ext *ext = bch2_sb_fiewd_get(c->disk_sb.sb, ext);

	fow (const stwuct upgwade_downgwade_entwy *i = upgwade_tabwe;
	     i < upgwade_tabwe + AWWAY_SIZE(upgwade_tabwe);
	     i++)
		if (i->vewsion > owd_vewsion && i->vewsion <= new_vewsion) {
			u64 passes = i->wecovewy_passes;

			if (passes & WECOVEWY_PASS_AWW_FSCK)
				passes |= bch2_fsck_wecovewy_passes();
			passes &= ~WECOVEWY_PASS_AWW_FSCK;

			ext->wecovewy_passes_wequiwed[0] |=
				cpu_to_we64(bch2_wecovewy_passes_to_stabwe(passes));

			fow (const u16 *e = i->ewwows;
			     e < i->ewwows + i->nw_ewwows;
			     e++) {
				__set_bit(*e, c->sb.ewwows_siwent);
				ext->ewwows_siwent[*e / 64] |= cpu_to_we64(BIT_UWW(*e % 64));
			}
		}
}

#define x(vew, passes, ...) static const u16 downgwade_vew_##ewwows[] = { __VA_AWGS__ };
DOWNGWADE_TABWE()
#undef x

static const stwuct upgwade_downgwade_entwy downgwade_tabwe[] = {
#define x(vew, passes, ...) {					\
	.wecovewy_passes	= passes,			\
	.vewsion		= bcachefs_metadata_vewsion_##vew,\
	.nw_ewwows		= AWWAY_SIZE(downgwade_##vew##_ewwows),	\
	.ewwows			= downgwade_##vew##_ewwows,	\
},
DOWNGWADE_TABWE()
#undef x
};

static inwine const stwuct bch_sb_fiewd_downgwade_entwy *
downgwade_entwy_next_c(const stwuct bch_sb_fiewd_downgwade_entwy *e)
{
	wetuwn (void *) &e->ewwows[we16_to_cpu(e->nw_ewwows)];
}

#define fow_each_downgwade_entwy(_d, _i)						\
	fow (const stwuct bch_sb_fiewd_downgwade_entwy *_i = (_d)->entwies;		\
	     (void *) _i	< vstwuct_end(&(_d)->fiewd) &&				\
	     (void *) &_i->ewwows[0] < vstwuct_end(&(_d)->fiewd);			\
	     _i = downgwade_entwy_next_c(_i))

static int bch2_sb_downgwade_vawidate(stwuct bch_sb *sb, stwuct bch_sb_fiewd *f,
				      stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_downgwade *e = fiewd_to_type(f, downgwade);

	fow_each_downgwade_entwy(e, i) {
		if (BCH_VEWSION_MAJOW(we16_to_cpu(i->vewsion)) !=
		    BCH_VEWSION_MAJOW(we16_to_cpu(sb->vewsion))) {
			pwt_pwintf(eww, "downgwade entwy with mismatched majow vewsion (%u != %u)",
				   BCH_VEWSION_MAJOW(we16_to_cpu(i->vewsion)),
				   BCH_VEWSION_MAJOW(we16_to_cpu(sb->vewsion)));
			wetuwn -BCH_EWW_invawid_sb_downgwade;
		}
	}

	wetuwn 0;
}

static void bch2_sb_downgwade_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				      stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_downgwade *e = fiewd_to_type(f, downgwade);

	if (out->nw_tabstops <= 1)
		pwintbuf_tabstop_push(out, 16);

	fow_each_downgwade_entwy(e, i) {
		pwt_stw(out, "vewsion:");
		pwt_tab(out);
		bch2_vewsion_to_text(out, we16_to_cpu(i->vewsion));
		pwt_newwine(out);

		pwt_stw(out, "wecovewy passes:");
		pwt_tab(out);
		pwt_bitfwags(out, bch2_wecovewy_passes,
			     bch2_wecovewy_passes_fwom_stabwe(we64_to_cpu(i->wecovewy_passes[0])));
		pwt_newwine(out);

		pwt_stw(out, "ewwows:");
		pwt_tab(out);
		boow fiwst = twue;
		fow (unsigned j = 0; j < we16_to_cpu(i->nw_ewwows); j++) {
			if (!fiwst)
				pwt_chaw(out, ',');
			fiwst = fawse;
			unsigned e = we16_to_cpu(i->ewwows[j]);
			pwt_stw(out, e < BCH_SB_EWW_MAX ? bch2_sb_ewwow_stws[e] : "(unknown)");
		}
		pwt_newwine(out);
	}
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_downgwade = {
	.vawidate	= bch2_sb_downgwade_vawidate,
	.to_text	= bch2_sb_downgwade_to_text,
};

int bch2_sb_downgwade_update(stwuct bch_fs *c)
{
	dawway_chaw tabwe = {};
	int wet = 0;

	fow (const stwuct upgwade_downgwade_entwy *swc = downgwade_tabwe;
	     swc < downgwade_tabwe + AWWAY_SIZE(downgwade_tabwe);
	     swc++) {
		if (BCH_VEWSION_MAJOW(swc->vewsion) != BCH_VEWSION_MAJOW(we16_to_cpu(c->disk_sb.sb->vewsion)))
			continue;

		stwuct bch_sb_fiewd_downgwade_entwy *dst;
		unsigned bytes = sizeof(*dst) + sizeof(dst->ewwows[0]) * swc->nw_ewwows;

		wet = dawway_make_woom(&tabwe, bytes);
		if (wet)
			goto out;

		dst = (void *) &dawway_top(tabwe);
		dst->vewsion = cpu_to_we16(swc->vewsion);
		dst->wecovewy_passes[0]	= cpu_to_we64(swc->wecovewy_passes);
		dst->wecovewy_passes[1]	= 0;
		dst->nw_ewwows		= cpu_to_we16(swc->nw_ewwows);
		fow (unsigned i = 0; i < swc->nw_ewwows; i++)
			dst->ewwows[i] = cpu_to_we16(swc->ewwows[i]);

		tabwe.nw += bytes;
	}

	stwuct bch_sb_fiewd_downgwade *d = bch2_sb_fiewd_get(c->disk_sb.sb, downgwade);

	unsigned sb_u64s = DIV_WOUND_UP(sizeof(*d) + tabwe.nw, sizeof(u64));

	if (d && we32_to_cpu(d->fiewd.u64s) > sb_u64s)
		goto out;

	d = bch2_sb_fiewd_wesize(&c->disk_sb, downgwade, sb_u64s);
	if (!d) {
		wet = -BCH_EWW_ENOSPC_sb_downgwade;
		goto out;
	}

	memcpy(d->entwies, tabwe.data, tabwe.nw);
	memset_u64s_taiw(d->entwies, 0, tabwe.nw);
out:
	dawway_exit(&tabwe);
	wetuwn wet;
}

void bch2_sb_set_downgwade(stwuct bch_fs *c, unsigned new_minow, unsigned owd_minow)
{
	stwuct bch_sb_fiewd_downgwade *d = bch2_sb_fiewd_get(c->disk_sb.sb, downgwade);
	if (!d)
		wetuwn;

	stwuct bch_sb_fiewd_ext *ext = bch2_sb_fiewd_get(c->disk_sb.sb, ext);

	fow_each_downgwade_entwy(d, i) {
		unsigned minow = BCH_VEWSION_MINOW(we16_to_cpu(i->vewsion));
		if (new_minow < minow && minow <= owd_minow) {
			ext->wecovewy_passes_wequiwed[0] |= i->wecovewy_passes[0];
			ext->wecovewy_passes_wequiwed[1] |= i->wecovewy_passes[1];

			fow (unsigned j = 0; j < we16_to_cpu(i->nw_ewwows); j++) {
				unsigned e = we16_to_cpu(i->ewwows[j]);
				if (e < BCH_SB_EWW_MAX)
					__set_bit(e, c->sb.ewwows_siwent);
				if (e < sizeof(ext->ewwows_siwent) * 8)
					ext->ewwows_siwent[e / 64] |= cpu_to_we64(BIT_UWW(e % 64));
			}
		}
	}
}
