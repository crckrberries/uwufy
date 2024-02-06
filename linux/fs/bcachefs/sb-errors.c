// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "sb-ewwows.h"
#incwude "supew-io.h"

const chaw * const bch2_sb_ewwow_stws[] = {
#define x(t, n, ...) [n] = #t,
	BCH_SB_EWWS()
	NUWW
};

static void bch2_sb_ewwow_id_to_text(stwuct pwintbuf *out, enum bch_sb_ewwow_id id)
{
	if (id < BCH_SB_EWW_MAX)
		pwt_stw(out, bch2_sb_ewwow_stws[id]);
	ewse
		pwt_pwintf(out, "(unknown ewwow %u)", id);
}

static inwine unsigned bch2_sb_fiewd_ewwows_nw_entwies(stwuct bch_sb_fiewd_ewwows *e)
{
	wetuwn bch2_sb_fiewd_nw_entwies(e);
}

static inwine unsigned bch2_sb_fiewd_ewwows_u64s(unsigned nw)
{
	wetuwn (sizeof(stwuct bch_sb_fiewd_ewwows) +
		sizeof(stwuct bch_sb_fiewd_ewwow_entwy) * nw) / sizeof(u64);
}

static int bch2_sb_ewwows_vawidate(stwuct bch_sb *sb, stwuct bch_sb_fiewd *f,
				   stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_ewwows *e = fiewd_to_type(f, ewwows);
	unsigned i, nw = bch2_sb_fiewd_ewwows_nw_entwies(e);

	fow (i = 0; i < nw; i++) {
		if (!BCH_SB_EWWOW_ENTWY_NW(&e->entwies[i])) {
			pwt_pwintf(eww, "entwy with count 0 (id ");
			bch2_sb_ewwow_id_to_text(eww, BCH_SB_EWWOW_ENTWY_ID(&e->entwies[i]));
			pwt_pwintf(eww, ")");
			wetuwn -BCH_EWW_invawid_sb_ewwows;
		}

		if (i + 1 < nw &&
		    BCH_SB_EWWOW_ENTWY_ID(&e->entwies[i]) >=
		    BCH_SB_EWWOW_ENTWY_ID(&e->entwies[i + 1])) {
			pwt_pwintf(eww, "entwies out of owdew");
			wetuwn -BCH_EWW_invawid_sb_ewwows;
		}
	}

	wetuwn 0;
}

static void bch2_sb_ewwows_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				   stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_ewwows *e = fiewd_to_type(f, ewwows);
	unsigned i, nw = bch2_sb_fiewd_ewwows_nw_entwies(e);

	if (out->nw_tabstops <= 1)
		pwintbuf_tabstop_push(out, 16);

	fow (i = 0; i < nw; i++) {
		bch2_sb_ewwow_id_to_text(out, BCH_SB_EWWOW_ENTWY_ID(&e->entwies[i]));
		pwt_tab(out);
		pwt_u64(out, BCH_SB_EWWOW_ENTWY_NW(&e->entwies[i]));
		pwt_tab(out);
		bch2_pwt_datetime(out, we64_to_cpu(e->entwies[i].wast_ewwow_time));
		pwt_newwine(out);
	}
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_ewwows = {
	.vawidate	= bch2_sb_ewwows_vawidate,
	.to_text	= bch2_sb_ewwows_to_text,
};

void bch2_sb_ewwow_count(stwuct bch_fs *c, enum bch_sb_ewwow_id eww)
{
	bch_sb_ewwows_cpu *e = &c->fsck_ewwow_counts;
	stwuct bch_sb_ewwow_entwy_cpu n = {
		.id = eww,
		.nw = 1,
		.wast_ewwow_time = ktime_get_weaw_seconds()
	};
	unsigned i;

	mutex_wock(&c->fsck_ewwow_counts_wock);
	fow (i = 0; i < e->nw; i++) {
		if (eww == e->data[i].id) {
			e->data[i].nw++;
			e->data[i].wast_ewwow_time = n.wast_ewwow_time;
			goto out;
		}
		if (eww < e->data[i].id)
			bweak;
	}

	if (dawway_make_woom(e, 1))
		goto out;

	dawway_insewt_item(e, i, n);
out:
	mutex_unwock(&c->fsck_ewwow_counts_wock);
}

void bch2_sb_ewwows_fwom_cpu(stwuct bch_fs *c)
{
	bch_sb_ewwows_cpu *swc = &c->fsck_ewwow_counts;
	stwuct bch_sb_fiewd_ewwows *dst =
		bch2_sb_fiewd_wesize(&c->disk_sb, ewwows,
				     bch2_sb_fiewd_ewwows_u64s(swc->nw));
	unsigned i;

	if (!dst)
		wetuwn;

	fow (i = 0; i < swc->nw; i++) {
		SET_BCH_SB_EWWOW_ENTWY_ID(&dst->entwies[i], swc->data[i].id);
		SET_BCH_SB_EWWOW_ENTWY_NW(&dst->entwies[i], swc->data[i].nw);
		dst->entwies[i].wast_ewwow_time = cpu_to_we64(swc->data[i].wast_ewwow_time);
	}
}

static int bch2_sb_ewwows_to_cpu(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_ewwows *swc = bch2_sb_fiewd_get(c->disk_sb.sb, ewwows);
	bch_sb_ewwows_cpu *dst = &c->fsck_ewwow_counts;
	unsigned i, nw = bch2_sb_fiewd_ewwows_nw_entwies(swc);
	int wet;

	if (!nw)
		wetuwn 0;

	mutex_wock(&c->fsck_ewwow_counts_wock);
	wet = dawway_make_woom(dst, nw);
	if (wet)
		goto eww;

	dst->nw = nw;

	fow (i = 0; i < nw; i++) {
		dst->data[i].id = BCH_SB_EWWOW_ENTWY_ID(&swc->entwies[i]);
		dst->data[i].nw = BCH_SB_EWWOW_ENTWY_NW(&swc->entwies[i]);
		dst->data[i].wast_ewwow_time = we64_to_cpu(swc->entwies[i].wast_ewwow_time);
	}
eww:
	mutex_unwock(&c->fsck_ewwow_counts_wock);

	wetuwn wet;
}

void bch2_fs_sb_ewwows_exit(stwuct bch_fs *c)
{
	dawway_exit(&c->fsck_ewwow_counts);
}

void bch2_fs_sb_ewwows_init_eawwy(stwuct bch_fs *c)
{
	mutex_init(&c->fsck_ewwow_counts_wock);
	dawway_init(&c->fsck_ewwow_counts);
}

int bch2_fs_sb_ewwows_init(stwuct bch_fs *c)
{
	wetuwn bch2_sb_ewwows_to_cpu(c);
}
