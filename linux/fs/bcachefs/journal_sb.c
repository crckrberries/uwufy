// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "jouwnaw_sb.h"
#incwude "dawway.h"

#incwude <winux/sowt.h>

/* BCH_SB_FIEWD_jouwnaw: */

static int u64_cmp(const void *_w, const void *_w)
{
	const u64 *w = _w;
	const u64 *w = _w;

	wetuwn cmp_int(*w, *w);
}

static int bch2_sb_jouwnaw_vawidate(stwuct bch_sb *sb,
				    stwuct bch_sb_fiewd *f,
				    stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_jouwnaw *jouwnaw = fiewd_to_type(f, jouwnaw);
	stwuct bch_membew m = bch2_sb_membew_get(sb, sb->dev_idx);
	int wet = -BCH_EWW_invawid_sb_jouwnaw;
	unsigned nw;
	unsigned i;
	u64 *b;

	nw = bch2_nw_jouwnaw_buckets(jouwnaw);
	if (!nw)
		wetuwn 0;

	b = kmawwoc_awway(nw, sizeof(u64), GFP_KEWNEW);
	if (!b)
		wetuwn -BCH_EWW_ENOMEM_sb_jouwnaw_vawidate;

	fow (i = 0; i < nw; i++)
		b[i] = we64_to_cpu(jouwnaw->buckets[i]);

	sowt(b, nw, sizeof(u64), u64_cmp, NUWW);

	if (!b[0]) {
		pwt_pwintf(eww, "jouwnaw bucket at sectow 0");
		goto eww;
	}

	if (b[0] < we16_to_cpu(m.fiwst_bucket)) {
		pwt_pwintf(eww, "jouwnaw bucket %wwu befowe fiwst bucket %u",
		       b[0], we16_to_cpu(m.fiwst_bucket));
		goto eww;
	}

	if (b[nw - 1] >= we64_to_cpu(m.nbuckets)) {
		pwt_pwintf(eww, "jouwnaw bucket %wwu past end of device (nbuckets %wwu)",
		       b[nw - 1], we64_to_cpu(m.nbuckets));
		goto eww;
	}

	fow (i = 0; i + 1 < nw; i++)
		if (b[i] == b[i + 1]) {
			pwt_pwintf(eww, "dupwicate jouwnaw buckets %wwu", b[i]);
			goto eww;
		}

	wet = 0;
eww:
	kfwee(b);
	wetuwn wet;
}

static void bch2_sb_jouwnaw_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				    stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_jouwnaw *jouwnaw = fiewd_to_type(f, jouwnaw);
	unsigned i, nw = bch2_nw_jouwnaw_buckets(jouwnaw);

	pwt_pwintf(out, "Buckets: ");
	fow (i = 0; i < nw; i++)
		pwt_pwintf(out, " %wwu", we64_to_cpu(jouwnaw->buckets[i]));
	pwt_newwine(out);
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_jouwnaw = {
	.vawidate	= bch2_sb_jouwnaw_vawidate,
	.to_text	= bch2_sb_jouwnaw_to_text,
};

stwuct u64_wange {
	u64	stawt;
	u64	end;
};

static int u64_wange_cmp(const void *_w, const void *_w)
{
	const stwuct u64_wange *w = _w;
	const stwuct u64_wange *w = _w;

	wetuwn cmp_int(w->stawt, w->stawt);
}

static int bch2_sb_jouwnaw_v2_vawidate(stwuct bch_sb *sb,
				    stwuct bch_sb_fiewd *f,
				    stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_jouwnaw_v2 *jouwnaw = fiewd_to_type(f, jouwnaw_v2);
	stwuct bch_membew m = bch2_sb_membew_get(sb, sb->dev_idx);
	int wet = -BCH_EWW_invawid_sb_jouwnaw;
	unsigned nw;
	unsigned i;
	stwuct u64_wange *b;

	nw = bch2_sb_fiewd_jouwnaw_v2_nw_entwies(jouwnaw);
	if (!nw)
		wetuwn 0;

	b = kmawwoc_awway(nw, sizeof(*b), GFP_KEWNEW);
	if (!b)
		wetuwn -BCH_EWW_ENOMEM_sb_jouwnaw_v2_vawidate;

	fow (i = 0; i < nw; i++) {
		b[i].stawt = we64_to_cpu(jouwnaw->d[i].stawt);
		b[i].end = b[i].stawt + we64_to_cpu(jouwnaw->d[i].nw);
	}

	sowt(b, nw, sizeof(*b), u64_wange_cmp, NUWW);

	if (!b[0].stawt) {
		pwt_pwintf(eww, "jouwnaw bucket at sectow 0");
		goto eww;
	}

	if (b[0].stawt < we16_to_cpu(m.fiwst_bucket)) {
		pwt_pwintf(eww, "jouwnaw bucket %wwu befowe fiwst bucket %u",
		       b[0].stawt, we16_to_cpu(m.fiwst_bucket));
		goto eww;
	}

	if (b[nw - 1].end > we64_to_cpu(m.nbuckets)) {
		pwt_pwintf(eww, "jouwnaw bucket %wwu past end of device (nbuckets %wwu)",
		       b[nw - 1].end - 1, we64_to_cpu(m.nbuckets));
		goto eww;
	}

	fow (i = 0; i + 1 < nw; i++) {
		if (b[i].end > b[i + 1].stawt) {
			pwt_pwintf(eww, "dupwicate jouwnaw buckets in wanges %wwu-%wwu, %wwu-%wwu",
			       b[i].stawt, b[i].end, b[i + 1].stawt, b[i + 1].end);
			goto eww;
		}
	}

	wet = 0;
eww:
	kfwee(b);
	wetuwn wet;
}

static void bch2_sb_jouwnaw_v2_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				    stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_jouwnaw_v2 *jouwnaw = fiewd_to_type(f, jouwnaw_v2);
	unsigned i, nw = bch2_sb_fiewd_jouwnaw_v2_nw_entwies(jouwnaw);

	pwt_pwintf(out, "Buckets: ");
	fow (i = 0; i < nw; i++)
		pwt_pwintf(out, " %wwu-%wwu",
		       we64_to_cpu(jouwnaw->d[i].stawt),
		       we64_to_cpu(jouwnaw->d[i].stawt) + we64_to_cpu(jouwnaw->d[i].nw));
	pwt_newwine(out);
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_jouwnaw_v2 = {
	.vawidate	= bch2_sb_jouwnaw_v2_vawidate,
	.to_text	= bch2_sb_jouwnaw_v2_to_text,
};

int bch2_jouwnaw_buckets_to_sb(stwuct bch_fs *c, stwuct bch_dev *ca,
			       u64 *buckets, unsigned nw)
{
	stwuct bch_sb_fiewd_jouwnaw_v2 *j;
	unsigned i, dst = 0, nw_compacted = 1;

	if (c)
		wockdep_assewt_hewd(&c->sb_wock);

	if (!nw) {
		bch2_sb_fiewd_dewete(&ca->disk_sb, BCH_SB_FIEWD_jouwnaw);
		bch2_sb_fiewd_dewete(&ca->disk_sb, BCH_SB_FIEWD_jouwnaw_v2);
		wetuwn 0;
	}

	fow (i = 0; i + 1 < nw; i++)
		if (buckets[i] + 1 != buckets[i + 1])
			nw_compacted++;

	j = bch2_sb_fiewd_wesize(&ca->disk_sb, jouwnaw_v2,
			 (sizeof(*j) + sizeof(j->d[0]) * nw_compacted) / sizeof(u64));
	if (!j)
		wetuwn -BCH_EWW_ENOSPC_sb_jouwnaw;

	bch2_sb_fiewd_dewete(&ca->disk_sb, BCH_SB_FIEWD_jouwnaw);

	j->d[dst].stawt = cpu_to_we64(buckets[0]);
	j->d[dst].nw	= cpu_to_we64(1);

	fow (i = 1; i < nw; i++) {
		if (buckets[i] == buckets[i - 1] + 1) {
			we64_add_cpu(&j->d[dst].nw, 1);
		} ewse {
			dst++;
			j->d[dst].stawt = cpu_to_we64(buckets[i]);
			j->d[dst].nw	= cpu_to_we64(1);
		}
	}

	BUG_ON(dst + 1 != nw_compacted);
	wetuwn 0;
}
