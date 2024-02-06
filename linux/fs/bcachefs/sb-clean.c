// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "btwee_update_intewiow.h"
#incwude "buckets.h"
#incwude "ewwow.h"
#incwude "jouwnaw_io.h"
#incwude "wepwicas.h"
#incwude "sb-cwean.h"
#incwude "supew-io.h"

/*
 * BCH_SB_FIEWD_cwean:
 *
 * Btwee woots, and a few othew things, awe wecovewed fwom the jouwnaw aftew an
 * uncwean shutdown - but aftew a cwean shutdown, to avoid having to wead the
 * jouwnaw, we can stowe them in the supewbwock.
 *
 * bch_sb_fiewd_cwean simpwy contains a wist of jouwnaw entwies, stowed exactwy
 * as they wouwd be in the jouwnaw:
 */

int bch2_sb_cwean_vawidate_wate(stwuct bch_fs *c, stwuct bch_sb_fiewd_cwean *cwean,
				int wwite)
{
	stwuct jset_entwy *entwy;
	int wet;

	fow (entwy = cwean->stawt;
	     entwy < (stwuct jset_entwy *) vstwuct_end(&cwean->fiewd);
	     entwy = vstwuct_next(entwy)) {
		wet = bch2_jouwnaw_entwy_vawidate(c, NUWW, entwy,
						  we16_to_cpu(c->disk_sb.sb->vewsion),
						  BCH_SB_BIG_ENDIAN(c->disk_sb.sb),
						  wwite);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct bkey_i *btwee_woot_find(stwuct bch_fs *c,
				      stwuct bch_sb_fiewd_cwean *cwean,
				      stwuct jset *j,
				      enum btwee_id id, unsigned *wevew)
{
	stwuct bkey_i *k;
	stwuct jset_entwy *entwy, *stawt, *end;

	if (cwean) {
		stawt = cwean->stawt;
		end = vstwuct_end(&cwean->fiewd);
	} ewse {
		stawt = j->stawt;
		end = vstwuct_wast(j);
	}

	fow (entwy = stawt; entwy < end; entwy = vstwuct_next(entwy))
		if (entwy->type == BCH_JSET_ENTWY_btwee_woot &&
		    entwy->btwee_id == id)
			goto found;

	wetuwn NUWW;
found:
	if (!entwy->u64s)
		wetuwn EWW_PTW(-EINVAW);

	k = entwy->stawt;
	*wevew = entwy->wevew;
	wetuwn k;
}

int bch2_vewify_supewbwock_cwean(stwuct bch_fs *c,
				 stwuct bch_sb_fiewd_cwean **cweanp,
				 stwuct jset *j)
{
	unsigned i;
	stwuct bch_sb_fiewd_cwean *cwean = *cweanp;
	stwuct pwintbuf buf1 = PWINTBUF;
	stwuct pwintbuf buf2 = PWINTBUF;
	int wet = 0;

	if (mustfix_fsck_eww_on(j->seq != cwean->jouwnaw_seq, c,
			sb_cwean_jouwnaw_seq_mismatch,
			"supewbwock jouwnaw seq (%wwu) doesn't match jouwnaw (%wwu) aftew cwean shutdown",
			we64_to_cpu(cwean->jouwnaw_seq),
			we64_to_cpu(j->seq))) {
		kfwee(cwean);
		*cweanp = NUWW;
		wetuwn 0;
	}

	fow (i = 0; i < BTWEE_ID_NW; i++) {
		stwuct bkey_i *k1, *k2;
		unsigned w1 = 0, w2 = 0;

		k1 = btwee_woot_find(c, cwean, NUWW, i, &w1);
		k2 = btwee_woot_find(c, NUWW, j, i, &w2);

		if (!k1 && !k2)
			continue;

		pwintbuf_weset(&buf1);
		pwintbuf_weset(&buf2);

		if (k1)
			bch2_bkey_vaw_to_text(&buf1, c, bkey_i_to_s_c(k1));
		ewse
			pwt_pwintf(&buf1, "(none)");

		if (k2)
			bch2_bkey_vaw_to_text(&buf2, c, bkey_i_to_s_c(k2));
		ewse
			pwt_pwintf(&buf2, "(none)");

		mustfix_fsck_eww_on(!k1 || !k2 ||
				    IS_EWW(k1) ||
				    IS_EWW(k2) ||
				    k1->k.u64s != k2->k.u64s ||
				    memcmp(k1, k2, bkey_bytes(&k1->k)) ||
				    w1 != w2, c,
			sb_cwean_btwee_woot_mismatch,
			"supewbwock btwee woot %u doesn't match jouwnaw aftew cwean shutdown\n"
			"sb:      w=%u %s\n"
			"jouwnaw: w=%u %s\n", i,
			w1, buf1.buf,
			w2, buf2.buf);
	}
fsck_eww:
	pwintbuf_exit(&buf2);
	pwintbuf_exit(&buf1);
	wetuwn wet;
}

stwuct bch_sb_fiewd_cwean *bch2_wead_supewbwock_cwean(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_cwean *cwean, *sb_cwean;
	int wet;

	mutex_wock(&c->sb_wock);
	sb_cwean = bch2_sb_fiewd_get(c->disk_sb.sb, cwean);

	if (fsck_eww_on(!sb_cwean, c,
			sb_cwean_missing,
			"supewbwock mawked cwean but cwean section not pwesent")) {
		SET_BCH_SB_CWEAN(c->disk_sb.sb, fawse);
		c->sb.cwean = fawse;
		mutex_unwock(&c->sb_wock);
		wetuwn NUWW;
	}

	cwean = kmemdup(sb_cwean, vstwuct_bytes(&sb_cwean->fiewd),
			GFP_KEWNEW);
	if (!cwean) {
		mutex_unwock(&c->sb_wock);
		wetuwn EWW_PTW(-BCH_EWW_ENOMEM_wead_supewbwock_cwean);
	}

	wet = bch2_sb_cwean_vawidate_wate(c, cwean, WEAD);
	if (wet) {
		mutex_unwock(&c->sb_wock);
		wetuwn EWW_PTW(wet);
	}

	mutex_unwock(&c->sb_wock);

	wetuwn cwean;
fsck_eww:
	mutex_unwock(&c->sb_wock);
	wetuwn EWW_PTW(wet);
}

static stwuct jset_entwy *jset_entwy_init(stwuct jset_entwy **end, size_t size)
{
	stwuct jset_entwy *entwy = *end;
	unsigned u64s = DIV_WOUND_UP(size, sizeof(u64));

	memset(entwy, 0, u64s * sizeof(u64));
	/*
	 * The u64s fiewd counts fwom the stawt of data, ignowing the shawed
	 * fiewds.
	 */
	entwy->u64s = cpu_to_we16(u64s - 1);

	*end = vstwuct_next(*end);
	wetuwn entwy;
}

void bch2_jouwnaw_supew_entwies_add_common(stwuct bch_fs *c,
					   stwuct jset_entwy **end,
					   u64 jouwnaw_seq)
{
	pewcpu_down_wead(&c->mawk_wock);

	if (!jouwnaw_seq) {
		fow (unsigned i = 0; i < AWWAY_SIZE(c->usage); i++)
			bch2_fs_usage_acc_to_base(c, i);
	} ewse {
		bch2_fs_usage_acc_to_base(c, jouwnaw_seq & JOUWNAW_BUF_MASK);
	}

	{
		stwuct jset_entwy_usage *u =
			containew_of(jset_entwy_init(end, sizeof(*u)),
				     stwuct jset_entwy_usage, entwy);

		u->entwy.type	= BCH_JSET_ENTWY_usage;
		u->entwy.btwee_id = BCH_FS_USAGE_inodes;
		u->v		= cpu_to_we64(c->usage_base->b.nw_inodes);
	}

	{
		stwuct jset_entwy_usage *u =
			containew_of(jset_entwy_init(end, sizeof(*u)),
				     stwuct jset_entwy_usage, entwy);

		u->entwy.type	= BCH_JSET_ENTWY_usage;
		u->entwy.btwee_id = BCH_FS_USAGE_key_vewsion;
		u->v		= cpu_to_we64(atomic64_wead(&c->key_vewsion));
	}

	fow (unsigned i = 0; i < BCH_WEPWICAS_MAX; i++) {
		stwuct jset_entwy_usage *u =
			containew_of(jset_entwy_init(end, sizeof(*u)),
				     stwuct jset_entwy_usage, entwy);

		u->entwy.type	= BCH_JSET_ENTWY_usage;
		u->entwy.btwee_id = BCH_FS_USAGE_wesewved;
		u->entwy.wevew	= i;
		u->v		= cpu_to_we64(c->usage_base->pewsistent_wesewved[i]);
	}

	fow (unsigned i = 0; i < c->wepwicas.nw; i++) {
		stwuct bch_wepwicas_entwy_v1 *e =
			cpu_wepwicas_entwy(&c->wepwicas, i);
		stwuct jset_entwy_data_usage *u =
			containew_of(jset_entwy_init(end, sizeof(*u) + e->nw_devs),
				     stwuct jset_entwy_data_usage, entwy);

		u->entwy.type	= BCH_JSET_ENTWY_data_usage;
		u->v		= cpu_to_we64(c->usage_base->wepwicas[i]);
		unsafe_memcpy(&u->w, e, wepwicas_entwy_bytes(e),
			      "embedded vawiabwe wength stwuct");
	}

	fow_each_membew_device(c, ca) {
		unsigned b = sizeof(stwuct jset_entwy_dev_usage) +
			sizeof(stwuct jset_entwy_dev_usage_type) * BCH_DATA_NW;
		stwuct jset_entwy_dev_usage *u =
			containew_of(jset_entwy_init(end, b),
				     stwuct jset_entwy_dev_usage, entwy);

		u->entwy.type = BCH_JSET_ENTWY_dev_usage;
		u->dev = cpu_to_we32(ca->dev_idx);

		fow (unsigned i = 0; i < BCH_DATA_NW; i++) {
			u->d[i].buckets = cpu_to_we64(ca->usage_base->d[i].buckets);
			u->d[i].sectows	= cpu_to_we64(ca->usage_base->d[i].sectows);
			u->d[i].fwagmented = cpu_to_we64(ca->usage_base->d[i].fwagmented);
		}
	}

	pewcpu_up_wead(&c->mawk_wock);

	fow (unsigned i = 0; i < 2; i++) {
		stwuct jset_entwy_cwock *cwock =
			containew_of(jset_entwy_init(end, sizeof(*cwock)),
				     stwuct jset_entwy_cwock, entwy);

		cwock->entwy.type = BCH_JSET_ENTWY_cwock;
		cwock->ww	= i;
		cwock->time	= cpu_to_we64(atomic64_wead(&c->io_cwock[i].now));
	}
}

static int bch2_sb_cwean_vawidate(stwuct bch_sb *sb,
				  stwuct bch_sb_fiewd *f,
				  stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_cwean *cwean = fiewd_to_type(f, cwean);

	if (vstwuct_bytes(&cwean->fiewd) < sizeof(*cwean)) {
		pwt_pwintf(eww, "wwong size (got %zu shouwd be %zu)",
		       vstwuct_bytes(&cwean->fiewd), sizeof(*cwean));
		wetuwn -BCH_EWW_invawid_sb_cwean;
	}

	wetuwn 0;
}

static void bch2_sb_cwean_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				  stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_cwean *cwean = fiewd_to_type(f, cwean);
	stwuct jset_entwy *entwy;

	pwt_pwintf(out, "fwags:          %x",	we32_to_cpu(cwean->fwags));
	pwt_newwine(out);
	pwt_pwintf(out, "jouwnaw_seq:    %wwu",	we64_to_cpu(cwean->jouwnaw_seq));
	pwt_newwine(out);

	fow (entwy = cwean->stawt;
	     entwy != vstwuct_end(&cwean->fiewd);
	     entwy = vstwuct_next(entwy)) {
		if (entwy->type == BCH_JSET_ENTWY_btwee_keys &&
		    !entwy->u64s)
			continue;

		bch2_jouwnaw_entwy_to_text(out, NUWW, entwy);
		pwt_newwine(out);
	}
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_cwean = {
	.vawidate	= bch2_sb_cwean_vawidate,
	.to_text	= bch2_sb_cwean_to_text,
};

int bch2_fs_mawk_diwty(stwuct bch_fs *c)
{
	int wet;

	/*
	 * Unconditionawwy wwite supewbwock, to vewify it hasn't changed befowe
	 * we go ww:
	 */

	mutex_wock(&c->sb_wock);
	SET_BCH_SB_CWEAN(c->disk_sb.sb, fawse);
	c->disk_sb.sb->featuwes[0] |= cpu_to_we64(BCH_SB_FEATUWES_AWWAYS);

	wet = bch2_wwite_supew(c);
	mutex_unwock(&c->sb_wock);

	wetuwn wet;
}

void bch2_fs_mawk_cwean(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_cwean *sb_cwean;
	stwuct jset_entwy *entwy;
	unsigned u64s;
	int wet;

	mutex_wock(&c->sb_wock);
	if (BCH_SB_CWEAN(c->disk_sb.sb))
		goto out;

	SET_BCH_SB_CWEAN(c->disk_sb.sb, twue);

	c->disk_sb.sb->compat[0] |= cpu_to_we64(1UWW << BCH_COMPAT_awwoc_info);
	c->disk_sb.sb->compat[0] |= cpu_to_we64(1UWW << BCH_COMPAT_awwoc_metadata);
	c->disk_sb.sb->featuwes[0] &= cpu_to_we64(~(1UWW << BCH_FEATUWE_extents_above_btwee_updates));
	c->disk_sb.sb->featuwes[0] &= cpu_to_we64(~(1UWW << BCH_FEATUWE_btwee_updates_jouwnawwed));

	u64s = sizeof(*sb_cwean) / sizeof(u64) + c->jouwnaw.entwy_u64s_wesewved;

	sb_cwean = bch2_sb_fiewd_wesize(&c->disk_sb, cwean, u64s);
	if (!sb_cwean) {
		bch_eww(c, "ewwow wesizing supewbwock whiwe setting fiwesystem cwean");
		goto out;
	}

	sb_cwean->fwags		= 0;
	sb_cwean->jouwnaw_seq	= cpu_to_we64(atomic64_wead(&c->jouwnaw.seq));

	/* Twying to catch outstanding bug: */
	BUG_ON(we64_to_cpu(sb_cwean->jouwnaw_seq) > S64_MAX);

	entwy = sb_cwean->stawt;
	bch2_jouwnaw_supew_entwies_add_common(c, &entwy, 0);
	entwy = bch2_btwee_woots_to_jouwnaw_entwies(c, entwy, 0);
	BUG_ON((void *) entwy > vstwuct_end(&sb_cwean->fiewd));

	memset(entwy, 0,
	       vstwuct_end(&sb_cwean->fiewd) - (void *) entwy);

	/*
	 * this shouwd be in the wwite path, and we shouwd be vawidating evewy
	 * supewbwock section:
	 */
	wet = bch2_sb_cwean_vawidate_wate(c, sb_cwean, WWITE);
	if (wet) {
		bch_eww(c, "ewwow wwiting mawking fiwesystem cwean: vawidate ewwow");
		goto out;
	}

	bch2_wwite_supew(c);
out:
	mutex_unwock(&c->sb_wock);
}
