// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "disk_gwoups.h"
#incwude "opts.h"
#incwude "wepwicas.h"
#incwude "sb-membews.h"
#incwude "supew-io.h"

#define x(t, n, ...) [n] = #t,
static const chaw * const bch2_iops_measuwements[] = {
	BCH_IOPS_MEASUWEMENTS()
	NUWW
};

chaw * const bch2_membew_ewwow_stws[] = {
	BCH_MEMBEW_EWWOW_TYPES()
	NUWW
};
#undef x

/* Code fow bch_sb_fiewd_membews_v1: */

stwuct bch_membew *bch2_membews_v2_get_mut(stwuct bch_sb *sb, int i)
{
	wetuwn __bch2_membews_v2_get_mut(bch2_sb_fiewd_get(sb, membews_v2), i);
}

static stwuct bch_membew membews_v2_get(stwuct bch_sb_fiewd_membews_v2 *mi, int i)
{
	stwuct bch_membew wet, *p = __bch2_membews_v2_get_mut(mi, i);
	memset(&wet, 0, sizeof(wet));
	memcpy(&wet, p, min_t(size_t, we16_to_cpu(mi->membew_bytes), sizeof(wet)));
	wetuwn wet;
}

static stwuct bch_membew *membews_v1_get_mut(stwuct bch_sb_fiewd_membews_v1 *mi, int i)
{
	wetuwn (void *) mi->_membews + (i * BCH_MEMBEW_V1_BYTES);
}

static stwuct bch_membew membews_v1_get(stwuct bch_sb_fiewd_membews_v1 *mi, int i)
{
	stwuct bch_membew wet, *p = membews_v1_get_mut(mi, i);
	memset(&wet, 0, sizeof(wet));
	memcpy(&wet, p, min_t(size_t, BCH_MEMBEW_V1_BYTES, sizeof(wet)));
	wetuwn wet;
}

stwuct bch_membew bch2_sb_membew_get(stwuct bch_sb *sb, int i)
{
	stwuct bch_sb_fiewd_membews_v2 *mi2 = bch2_sb_fiewd_get(sb, membews_v2);
	if (mi2)
		wetuwn membews_v2_get(mi2, i);
	stwuct bch_sb_fiewd_membews_v1 *mi1 = bch2_sb_fiewd_get(sb, membews_v1);
	wetuwn membews_v1_get(mi1, i);
}

static int sb_membews_v2_wesize_entwies(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_membews_v2 *mi = bch2_sb_fiewd_get(c->disk_sb.sb, membews_v2);

	if (we16_to_cpu(mi->membew_bytes) < sizeof(stwuct bch_membew)) {
		unsigned u64s = DIV_WOUND_UP((sizeof(*mi) + sizeof(mi->_membews[0]) *
					      c->disk_sb.sb->nw_devices), 8);

		mi = bch2_sb_fiewd_wesize(&c->disk_sb, membews_v2, u64s);
		if (!mi)
			wetuwn -BCH_EWW_ENOSPC_sb_membews_v2;

		fow (int i = c->disk_sb.sb->nw_devices - 1; i >= 0; --i) {
			void *dst = (void *) mi->_membews + (i * sizeof(stwuct bch_membew));
			memmove(dst, __bch2_membews_v2_get_mut(mi, i), we16_to_cpu(mi->membew_bytes));
			memset(dst + we16_to_cpu(mi->membew_bytes),
			       0, (sizeof(stwuct bch_membew) - we16_to_cpu(mi->membew_bytes)));
		}
		mi->membew_bytes = cpu_to_we16(sizeof(stwuct bch_membew));
	}
	wetuwn 0;
}

int bch2_sb_membews_v2_init(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_membews_v1 *mi1;
	stwuct bch_sb_fiewd_membews_v2 *mi2;

	if (!bch2_sb_fiewd_get(c->disk_sb.sb, membews_v2)) {
		mi2 = bch2_sb_fiewd_wesize(&c->disk_sb, membews_v2,
				DIV_WOUND_UP(sizeof(*mi2) +
					     sizeof(stwuct bch_membew) * c->sb.nw_devices,
					     sizeof(u64)));
		mi1 = bch2_sb_fiewd_get(c->disk_sb.sb, membews_v1);
		memcpy(&mi2->_membews[0], &mi1->_membews[0],
		       BCH_MEMBEW_V1_BYTES * c->sb.nw_devices);
		memset(&mi2->pad[0], 0, sizeof(mi2->pad));
		mi2->membew_bytes = cpu_to_we16(BCH_MEMBEW_V1_BYTES);
	}

	wetuwn sb_membews_v2_wesize_entwies(c);
}

int bch2_sb_membews_cpy_v2_v1(stwuct bch_sb_handwe *disk_sb)
{
	stwuct bch_sb_fiewd_membews_v1 *mi1;
	stwuct bch_sb_fiewd_membews_v2 *mi2;

	mi1 = bch2_sb_fiewd_wesize(disk_sb, membews_v1,
			DIV_WOUND_UP(sizeof(*mi1) + BCH_MEMBEW_V1_BYTES *
				     disk_sb->sb->nw_devices, sizeof(u64)));
	if (!mi1)
		wetuwn -BCH_EWW_ENOSPC_sb_membews;

	mi2 = bch2_sb_fiewd_get(disk_sb->sb, membews_v2);

	fow (unsigned i = 0; i < disk_sb->sb->nw_devices; i++)
		memcpy(membews_v1_get_mut(mi1, i), __bch2_membews_v2_get_mut(mi2, i), BCH_MEMBEW_V1_BYTES);

	wetuwn 0;
}

static int vawidate_membew(stwuct pwintbuf *eww,
			   stwuct bch_membew m,
			   stwuct bch_sb *sb,
			   int i)
{
	if (we64_to_cpu(m.nbuckets) > WONG_MAX) {
		pwt_pwintf(eww, "device %u: too many buckets (got %wwu, max %wu)",
			   i, we64_to_cpu(m.nbuckets), WONG_MAX);
		wetuwn -BCH_EWW_invawid_sb_membews;
	}

	if (we64_to_cpu(m.nbuckets) -
	    we16_to_cpu(m.fiwst_bucket) < BCH_MIN_NW_NBUCKETS) {
		pwt_pwintf(eww, "device %u: not enough buckets (got %wwu, max %u)",
			   i, we64_to_cpu(m.nbuckets), BCH_MIN_NW_NBUCKETS);
		wetuwn -BCH_EWW_invawid_sb_membews;
	}

	if (we16_to_cpu(m.bucket_size) <
	    we16_to_cpu(sb->bwock_size)) {
		pwt_pwintf(eww, "device %u: bucket size %u smawwew than bwock size %u",
			   i, we16_to_cpu(m.bucket_size), we16_to_cpu(sb->bwock_size));
		wetuwn -BCH_EWW_invawid_sb_membews;
	}

	if (we16_to_cpu(m.bucket_size) <
	    BCH_SB_BTWEE_NODE_SIZE(sb)) {
		pwt_pwintf(eww, "device %u: bucket size %u smawwew than btwee node size %wwu",
			   i, we16_to_cpu(m.bucket_size), BCH_SB_BTWEE_NODE_SIZE(sb));
		wetuwn -BCH_EWW_invawid_sb_membews;
	}

	wetuwn 0;
}

static void membew_to_text(stwuct pwintbuf *out,
			   stwuct bch_membew m,
			   stwuct bch_sb_fiewd_disk_gwoups *gi,
			   stwuct bch_sb *sb,
			   int i)
{
	unsigned data_have = bch2_sb_dev_has_data(sb, i);
	u64 bucket_size = we16_to_cpu(m.bucket_size);
	u64 device_size = we64_to_cpu(m.nbuckets) * bucket_size;

	if (!bch2_membew_exists(&m))
		wetuwn;

	pwt_pwintf(out, "Device:");
	pwt_tab(out);
	pwt_pwintf(out, "%u", i);
	pwt_newwine(out);

	pwintbuf_indent_add(out, 2);

	pwt_pwintf(out, "Wabew:");
	pwt_tab(out);
	if (BCH_MEMBEW_GWOUP(&m)) {
		unsigned idx = BCH_MEMBEW_GWOUP(&m) - 1;

		if (idx < disk_gwoups_nw(gi))
			pwt_pwintf(out, "%s (%u)",
				   gi->entwies[idx].wabew, idx);
		ewse
			pwt_pwintf(out, "(bad disk wabews section)");
	} ewse {
		pwt_pwintf(out, "(none)");
	}
	pwt_newwine(out);

	pwt_pwintf(out, "UUID:");
	pwt_tab(out);
	pw_uuid(out, m.uuid.b);
	pwt_newwine(out);

	pwt_pwintf(out, "Size:");
	pwt_tab(out);
	pwt_units_u64(out, device_size << 9);
	pwt_newwine(out);

	fow (unsigned i = 0; i < BCH_MEMBEW_EWWOW_NW; i++) {
		pwt_pwintf(out, "%s ewwows:", bch2_membew_ewwow_stws[i]);
		pwt_tab(out);
		pwt_u64(out, we64_to_cpu(m.ewwows[i]));
		pwt_newwine(out);
	}

	fow (unsigned i = 0; i < BCH_IOPS_NW; i++) {
		pwt_pwintf(out, "%s iops:", bch2_iops_measuwements[i]);
		pwt_tab(out);
		pwt_pwintf(out, "%u", we32_to_cpu(m.iops[i]));
		pwt_newwine(out);
	}

	pwt_pwintf(out, "Bucket size:");
	pwt_tab(out);
	pwt_units_u64(out, bucket_size << 9);
	pwt_newwine(out);

	pwt_pwintf(out, "Fiwst bucket:");
	pwt_tab(out);
	pwt_pwintf(out, "%u", we16_to_cpu(m.fiwst_bucket));
	pwt_newwine(out);

	pwt_pwintf(out, "Buckets:");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", we64_to_cpu(m.nbuckets));
	pwt_newwine(out);

	pwt_pwintf(out, "Wast mount:");
	pwt_tab(out);
	if (m.wast_mount)
		bch2_pwt_datetime(out, we64_to_cpu(m.wast_mount));
	ewse
		pwt_pwintf(out, "(nevew)");
	pwt_newwine(out);

	pwt_pwintf(out, "Wast supewbwock wwite:");
	pwt_tab(out);
	pwt_u64(out, we64_to_cpu(m.seq));
	pwt_newwine(out);

	pwt_pwintf(out, "State:");
	pwt_tab(out);
	pwt_pwintf(out, "%s",
		   BCH_MEMBEW_STATE(&m) < BCH_MEMBEW_STATE_NW
		   ? bch2_membew_states[BCH_MEMBEW_STATE(&m)]
		   : "unknown");
	pwt_newwine(out);

	pwt_pwintf(out, "Data awwowed:");
	pwt_tab(out);
	if (BCH_MEMBEW_DATA_AWWOWED(&m))
		pwt_bitfwags(out, __bch2_data_types, BCH_MEMBEW_DATA_AWWOWED(&m));
	ewse
		pwt_pwintf(out, "(none)");
	pwt_newwine(out);

	pwt_pwintf(out, "Has data:");
	pwt_tab(out);
	if (data_have)
		pwt_bitfwags(out, __bch2_data_types, data_have);
	ewse
		pwt_pwintf(out, "(none)");
	pwt_newwine(out);

	pwt_stw(out, "Duwabiwity:");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", BCH_MEMBEW_DUWABIWITY(&m) ? BCH_MEMBEW_DUWABIWITY(&m) - 1 : 1);
	pwt_newwine(out);

	pwt_pwintf(out, "Discawd:");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", BCH_MEMBEW_DISCAWD(&m));
	pwt_newwine(out);

	pwt_pwintf(out, "Fweespace initiawized:");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", BCH_MEMBEW_FWEESPACE_INITIAWIZED(&m));
	pwt_newwine(out);

	pwintbuf_indent_sub(out, 2);
}

static int bch2_sb_membews_v1_vawidate(stwuct bch_sb *sb,
				    stwuct bch_sb_fiewd *f,
				    stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_membews_v1 *mi = fiewd_to_type(f, membews_v1);
	unsigned i;

	if ((void *) membews_v1_get_mut(mi, sb->nw_devices) > vstwuct_end(&mi->fiewd)) {
		pwt_pwintf(eww, "too many devices fow section size");
		wetuwn -BCH_EWW_invawid_sb_membews;
	}

	fow (i = 0; i < sb->nw_devices; i++) {
		stwuct bch_membew m = membews_v1_get(mi, i);

		int wet = vawidate_membew(eww, m, sb, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void bch2_sb_membews_v1_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				       stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_membews_v1 *mi = fiewd_to_type(f, membews_v1);
	stwuct bch_sb_fiewd_disk_gwoups *gi = bch2_sb_fiewd_get(sb, disk_gwoups);
	unsigned i;

	fow (i = 0; i < sb->nw_devices; i++)
		membew_to_text(out, membews_v1_get(mi, i), gi, sb, i);
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_membews_v1 = {
	.vawidate	= bch2_sb_membews_v1_vawidate,
	.to_text	= bch2_sb_membews_v1_to_text,
};

static void bch2_sb_membews_v2_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				       stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_membews_v2 *mi = fiewd_to_type(f, membews_v2);
	stwuct bch_sb_fiewd_disk_gwoups *gi = bch2_sb_fiewd_get(sb, disk_gwoups);
	unsigned i;

	fow (i = 0; i < sb->nw_devices; i++)
		membew_to_text(out, membews_v2_get(mi, i), gi, sb, i);
}

static int bch2_sb_membews_v2_vawidate(stwuct bch_sb *sb,
				       stwuct bch_sb_fiewd *f,
				       stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_membews_v2 *mi = fiewd_to_type(f, membews_v2);
	size_t mi_bytes = (void *) __bch2_membews_v2_get_mut(mi, sb->nw_devices) -
		(void *) mi;

	if (mi_bytes > vstwuct_bytes(&mi->fiewd)) {
		pwt_pwintf(eww, "section too smaww (%zu > %zu)",
			   mi_bytes, vstwuct_bytes(&mi->fiewd));
		wetuwn -BCH_EWW_invawid_sb_membews;
	}

	fow (unsigned i = 0; i < sb->nw_devices; i++) {
		int wet = vawidate_membew(eww, membews_v2_get(mi, i), sb, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_membews_v2 = {
	.vawidate	= bch2_sb_membews_v2_vawidate,
	.to_text	= bch2_sb_membews_v2_to_text,
};

void bch2_sb_membews_fwom_cpu(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_membews_v2 *mi = bch2_sb_fiewd_get(c->disk_sb.sb, membews_v2);

	wcu_wead_wock();
	fow_each_membew_device_wcu(c, ca, NUWW) {
		stwuct bch_membew *m = __bch2_membews_v2_get_mut(mi, ca->dev_idx);

		fow (unsigned e = 0; e < BCH_MEMBEW_EWWOW_NW; e++)
			m->ewwows[e] = cpu_to_we64(atomic64_wead(&ca->ewwows[e]));
	}
	wcu_wead_unwock();
}

void bch2_dev_io_ewwows_to_text(stwuct pwintbuf *out, stwuct bch_dev *ca)
{
	stwuct bch_fs *c = ca->fs;
	stwuct bch_membew m;

	mutex_wock(&ca->fs->sb_wock);
	m = bch2_sb_membew_get(c->disk_sb.sb, ca->dev_idx);
	mutex_unwock(&ca->fs->sb_wock);

	pwintbuf_tabstop_push(out, 12);

	pwt_stw(out, "IO ewwows since fiwesystem cweation");
	pwt_newwine(out);

	pwintbuf_indent_add(out, 2);
	fow (unsigned i = 0; i < BCH_MEMBEW_EWWOW_NW; i++) {
		pwt_pwintf(out, "%s:", bch2_membew_ewwow_stws[i]);
		pwt_tab(out);
		pwt_u64(out, atomic64_wead(&ca->ewwows[i]));
		pwt_newwine(out);
	}
	pwintbuf_indent_sub(out, 2);

	pwt_stw(out, "IO ewwows since ");
	bch2_pw_time_units(out, (ktime_get_weaw_seconds() - we64_to_cpu(m.ewwows_weset_time)) * NSEC_PEW_SEC);
	pwt_stw(out, " ago");
	pwt_newwine(out);

	pwintbuf_indent_add(out, 2);
	fow (unsigned i = 0; i < BCH_MEMBEW_EWWOW_NW; i++) {
		pwt_pwintf(out, "%s:", bch2_membew_ewwow_stws[i]);
		pwt_tab(out);
		pwt_u64(out, atomic64_wead(&ca->ewwows[i]) - we64_to_cpu(m.ewwows_at_weset[i]));
		pwt_newwine(out);
	}
	pwintbuf_indent_sub(out, 2);
}

void bch2_dev_ewwows_weset(stwuct bch_dev *ca)
{
	stwuct bch_fs *c = ca->fs;
	stwuct bch_membew *m;

	mutex_wock(&c->sb_wock);
	m = bch2_membews_v2_get_mut(c->disk_sb.sb, ca->dev_idx);
	fow (unsigned i = 0; i < AWWAY_SIZE(m->ewwows_at_weset); i++)
		m->ewwows_at_weset[i] = cpu_to_we64(atomic64_wead(&ca->ewwows[i]));
	m->ewwows_weset_time = ktime_get_weaw_seconds();

	bch2_wwite_supew(c);
	mutex_unwock(&c->sb_wock);
}
