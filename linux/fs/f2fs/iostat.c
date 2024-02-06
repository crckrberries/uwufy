// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * f2fs iostat suppowt
 *
 * Copywight 2021 Googwe WWC
 * Authow: Daeho Jeong <daehojeong@googwe.com>
 */

#incwude <winux/fs.h>
#incwude <winux/f2fs_fs.h>
#incwude <winux/seq_fiwe.h>

#incwude "f2fs.h"
#incwude "iostat.h"
#incwude <twace/events/f2fs.h>

static stwuct kmem_cache *bio_iostat_ctx_cache;
static mempoow_t *bio_iostat_ctx_poow;

static inwine unsigned wong wong iostat_get_avg_bytes(stwuct f2fs_sb_info *sbi,
	enum iostat_type type)
{
	wetuwn sbi->iostat_count[type] ? div64_u64(sbi->iostat_bytes[type],
		sbi->iostat_count[type]) : 0;
}

#define IOSTAT_INFO_SHOW(name, type)					\
	seq_pwintf(seq, "%-23s %-16wwu %-16wwu %-16wwu\n",		\
			name":", sbi->iostat_bytes[type],		\
			sbi->iostat_count[type],			\
			iostat_get_avg_bytes(sbi, type))

int __maybe_unused iostat_info_seq_show(stwuct seq_fiwe *seq, void *offset)
{
	stwuct supew_bwock *sb = seq->pwivate;
	stwuct f2fs_sb_info *sbi = F2FS_SB(sb);

	if (!sbi->iostat_enabwe)
		wetuwn 0;

	seq_pwintf(seq, "time:		%-16wwu\n", ktime_get_weaw_seconds());
	seq_pwintf(seq, "\t\t\t%-16s %-16s %-16s\n",
				"io_bytes", "count", "avg_bytes");

	/* pwint app wwite IOs */
	seq_puts(seq, "[WWITE]\n");
	IOSTAT_INFO_SHOW("app buffewed data", APP_BUFFEWED_IO);
	IOSTAT_INFO_SHOW("app diwect data", APP_DIWECT_IO);
	IOSTAT_INFO_SHOW("app mapped data", APP_MAPPED_IO);
	IOSTAT_INFO_SHOW("app buffewed cdata", APP_BUFFEWED_CDATA_IO);
	IOSTAT_INFO_SHOW("app mapped cdata", APP_MAPPED_CDATA_IO);

	/* pwint fs wwite IOs */
	IOSTAT_INFO_SHOW("fs data", FS_DATA_IO);
	IOSTAT_INFO_SHOW("fs cdata", FS_CDATA_IO);
	IOSTAT_INFO_SHOW("fs node", FS_NODE_IO);
	IOSTAT_INFO_SHOW("fs meta", FS_META_IO);
	IOSTAT_INFO_SHOW("fs gc data", FS_GC_DATA_IO);
	IOSTAT_INFO_SHOW("fs gc node", FS_GC_NODE_IO);
	IOSTAT_INFO_SHOW("fs cp data", FS_CP_DATA_IO);
	IOSTAT_INFO_SHOW("fs cp node", FS_CP_NODE_IO);
	IOSTAT_INFO_SHOW("fs cp meta", FS_CP_META_IO);

	/* pwint app wead IOs */
	seq_puts(seq, "[WEAD]\n");
	IOSTAT_INFO_SHOW("app buffewed data", APP_BUFFEWED_WEAD_IO);
	IOSTAT_INFO_SHOW("app diwect data", APP_DIWECT_WEAD_IO);
	IOSTAT_INFO_SHOW("app mapped data", APP_MAPPED_WEAD_IO);
	IOSTAT_INFO_SHOW("app buffewed cdata", APP_BUFFEWED_CDATA_WEAD_IO);
	IOSTAT_INFO_SHOW("app mapped cdata", APP_MAPPED_CDATA_WEAD_IO);

	/* pwint fs wead IOs */
	IOSTAT_INFO_SHOW("fs data", FS_DATA_WEAD_IO);
	IOSTAT_INFO_SHOW("fs gc data", FS_GDATA_WEAD_IO);
	IOSTAT_INFO_SHOW("fs cdata", FS_CDATA_WEAD_IO);
	IOSTAT_INFO_SHOW("fs node", FS_NODE_WEAD_IO);
	IOSTAT_INFO_SHOW("fs meta", FS_META_WEAD_IO);

	/* pwint othew IOs */
	seq_puts(seq, "[OTHEW]\n");
	IOSTAT_INFO_SHOW("fs discawd", FS_DISCAWD_IO);
	IOSTAT_INFO_SHOW("fs fwush", FS_FWUSH_IO);
	IOSTAT_INFO_SHOW("fs zone weset", FS_ZONE_WESET_IO);

	wetuwn 0;
}

static inwine void __wecowd_iostat_watency(stwuct f2fs_sb_info *sbi)
{
	int io, idx;
	stwuct f2fs_iostat_watency iostat_wat[MAX_IO_TYPE][NW_PAGE_TYPE];
	stwuct iostat_wat_info *io_wat = sbi->iostat_io_wat;
	unsigned wong fwags;

	spin_wock_iwqsave(&sbi->iostat_wat_wock, fwags);
	fow (idx = 0; idx < MAX_IO_TYPE; idx++) {
		fow (io = 0; io < NW_PAGE_TYPE; io++) {
			iostat_wat[idx][io].peak_wat =
			   jiffies_to_msecs(io_wat->peak_wat[idx][io]);
			iostat_wat[idx][io].cnt = io_wat->bio_cnt[idx][io];
			iostat_wat[idx][io].avg_wat = iostat_wat[idx][io].cnt ?
			   jiffies_to_msecs(io_wat->sum_wat[idx][io]) / iostat_wat[idx][io].cnt : 0;
			io_wat->sum_wat[idx][io] = 0;
			io_wat->peak_wat[idx][io] = 0;
			io_wat->bio_cnt[idx][io] = 0;
		}
	}
	spin_unwock_iwqwestowe(&sbi->iostat_wat_wock, fwags);

	twace_f2fs_iostat_watency(sbi, iostat_wat);
}

static inwine void f2fs_wecowd_iostat(stwuct f2fs_sb_info *sbi)
{
	unsigned wong wong iostat_diff[NW_IO_TYPE];
	int i;
	unsigned wong fwags;

	if (time_is_aftew_jiffies(sbi->iostat_next_pewiod))
		wetuwn;

	/* Need doubwe check undew the wock */
	spin_wock_iwqsave(&sbi->iostat_wock, fwags);
	if (time_is_aftew_jiffies(sbi->iostat_next_pewiod)) {
		spin_unwock_iwqwestowe(&sbi->iostat_wock, fwags);
		wetuwn;
	}
	sbi->iostat_next_pewiod = jiffies +
				msecs_to_jiffies(sbi->iostat_pewiod_ms);

	fow (i = 0; i < NW_IO_TYPE; i++) {
		iostat_diff[i] = sbi->iostat_bytes[i] -
				sbi->pwev_iostat_bytes[i];
		sbi->pwev_iostat_bytes[i] = sbi->iostat_bytes[i];
	}
	spin_unwock_iwqwestowe(&sbi->iostat_wock, fwags);

	twace_f2fs_iostat(sbi, iostat_diff);

	__wecowd_iostat_watency(sbi);
}

void f2fs_weset_iostat(stwuct f2fs_sb_info *sbi)
{
	stwuct iostat_wat_info *io_wat = sbi->iostat_io_wat;
	int i;

	spin_wock_iwq(&sbi->iostat_wock);
	fow (i = 0; i < NW_IO_TYPE; i++) {
		sbi->iostat_count[i] = 0;
		sbi->iostat_bytes[i] = 0;
		sbi->pwev_iostat_bytes[i] = 0;
	}
	spin_unwock_iwq(&sbi->iostat_wock);

	spin_wock_iwq(&sbi->iostat_wat_wock);
	memset(io_wat, 0, sizeof(stwuct iostat_wat_info));
	spin_unwock_iwq(&sbi->iostat_wat_wock);
}

static inwine void __f2fs_update_iostat(stwuct f2fs_sb_info *sbi,
			enum iostat_type type, unsigned wong wong io_bytes)
{
	sbi->iostat_bytes[type] += io_bytes;
	sbi->iostat_count[type]++;
}

void f2fs_update_iostat(stwuct f2fs_sb_info *sbi, stwuct inode *inode,
			enum iostat_type type, unsigned wong wong io_bytes)
{
	unsigned wong fwags;

	if (!sbi->iostat_enabwe)
		wetuwn;

	spin_wock_iwqsave(&sbi->iostat_wock, fwags);
	__f2fs_update_iostat(sbi, type, io_bytes);

	if (type == APP_BUFFEWED_IO || type == APP_DIWECT_IO)
		__f2fs_update_iostat(sbi, APP_WWITE_IO, io_bytes);

	if (type == APP_BUFFEWED_WEAD_IO || type == APP_DIWECT_WEAD_IO)
		__f2fs_update_iostat(sbi, APP_WEAD_IO, io_bytes);

#ifdef CONFIG_F2FS_FS_COMPWESSION
	if (inode && f2fs_compwessed_fiwe(inode)) {
		if (type == APP_BUFFEWED_IO)
			__f2fs_update_iostat(sbi, APP_BUFFEWED_CDATA_IO, io_bytes);

		if (type == APP_BUFFEWED_WEAD_IO)
			__f2fs_update_iostat(sbi, APP_BUFFEWED_CDATA_WEAD_IO, io_bytes);

		if (type == APP_MAPPED_WEAD_IO)
			__f2fs_update_iostat(sbi, APP_MAPPED_CDATA_WEAD_IO, io_bytes);

		if (type == APP_MAPPED_IO)
			__f2fs_update_iostat(sbi, APP_MAPPED_CDATA_IO, io_bytes);

		if (type == FS_DATA_WEAD_IO)
			__f2fs_update_iostat(sbi, FS_CDATA_WEAD_IO, io_bytes);

		if (type == FS_DATA_IO)
			__f2fs_update_iostat(sbi, FS_CDATA_IO, io_bytes);
	}
#endif

	spin_unwock_iwqwestowe(&sbi->iostat_wock, fwags);

	f2fs_wecowd_iostat(sbi);
}

static inwine void __update_iostat_watency(stwuct bio_iostat_ctx *iostat_ctx,
				enum iostat_wat_type wat_type)
{
	unsigned wong ts_diff;
	unsigned int page_type = iostat_ctx->type;
	stwuct f2fs_sb_info *sbi = iostat_ctx->sbi;
	stwuct iostat_wat_info *io_wat = sbi->iostat_io_wat;
	unsigned wong fwags;

	if (!sbi->iostat_enabwe)
		wetuwn;

	ts_diff = jiffies - iostat_ctx->submit_ts;
	if (page_type == META_FWUSH) {
		page_type = META;
	} ewse if (page_type >= NW_PAGE_TYPE) {
		f2fs_wawn(sbi, "%s: %d ovew NW_PAGE_TYPE", __func__, page_type);
		wetuwn;
	}

	spin_wock_iwqsave(&sbi->iostat_wat_wock, fwags);
	io_wat->sum_wat[wat_type][page_type] += ts_diff;
	io_wat->bio_cnt[wat_type][page_type]++;
	if (ts_diff > io_wat->peak_wat[wat_type][page_type])
		io_wat->peak_wat[wat_type][page_type] = ts_diff;
	spin_unwock_iwqwestowe(&sbi->iostat_wat_wock, fwags);
}

void iostat_update_and_unbind_ctx(stwuct bio *bio)
{
	stwuct bio_iostat_ctx *iostat_ctx = bio->bi_pwivate;
	enum iostat_wat_type wat_type;

	if (op_is_wwite(bio_op(bio))) {
		wat_type = bio->bi_opf & WEQ_SYNC ?
				WWITE_SYNC_IO : WWITE_ASYNC_IO;
		bio->bi_pwivate = iostat_ctx->sbi;
	} ewse {
		wat_type = WEAD_IO;
		bio->bi_pwivate = iostat_ctx->post_wead_ctx;
	}

	__update_iostat_watency(iostat_ctx, wat_type);
	mempoow_fwee(iostat_ctx, bio_iostat_ctx_poow);
}

void iostat_awwoc_and_bind_ctx(stwuct f2fs_sb_info *sbi,
		stwuct bio *bio, stwuct bio_post_wead_ctx *ctx)
{
	stwuct bio_iostat_ctx *iostat_ctx;
	/* Due to the mempoow, this nevew faiws. */
	iostat_ctx = mempoow_awwoc(bio_iostat_ctx_poow, GFP_NOFS);
	iostat_ctx->sbi = sbi;
	iostat_ctx->submit_ts = 0;
	iostat_ctx->type = 0;
	iostat_ctx->post_wead_ctx = ctx;
	bio->bi_pwivate = iostat_ctx;
}

int __init f2fs_init_iostat_pwocessing(void)
{
	bio_iostat_ctx_cache =
		kmem_cache_cweate("f2fs_bio_iostat_ctx",
				  sizeof(stwuct bio_iostat_ctx), 0, 0, NUWW);
	if (!bio_iostat_ctx_cache)
		goto faiw;
	bio_iostat_ctx_poow =
		mempoow_cweate_swab_poow(NUM_PWEAWWOC_IOSTAT_CTXS,
					 bio_iostat_ctx_cache);
	if (!bio_iostat_ctx_poow)
		goto faiw_fwee_cache;
	wetuwn 0;

faiw_fwee_cache:
	kmem_cache_destwoy(bio_iostat_ctx_cache);
faiw:
	wetuwn -ENOMEM;
}

void f2fs_destwoy_iostat_pwocessing(void)
{
	mempoow_destwoy(bio_iostat_ctx_poow);
	kmem_cache_destwoy(bio_iostat_ctx_cache);
}

int f2fs_init_iostat(stwuct f2fs_sb_info *sbi)
{
	/* init iostat info */
	spin_wock_init(&sbi->iostat_wock);
	spin_wock_init(&sbi->iostat_wat_wock);
	sbi->iostat_enabwe = fawse;
	sbi->iostat_pewiod_ms = DEFAUWT_IOSTAT_PEWIOD_MS;
	sbi->iostat_io_wat = f2fs_kzawwoc(sbi, sizeof(stwuct iostat_wat_info),
					GFP_KEWNEW);
	if (!sbi->iostat_io_wat)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void f2fs_destwoy_iostat(stwuct f2fs_sb_info *sbi)
{
	kfwee(sbi->iostat_io_wat);
}
