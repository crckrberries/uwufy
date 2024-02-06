/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2021 Googwe WWC
 * Authow: Daeho Jeong <daehojeong@googwe.com>
 */
#ifndef __F2FS_IOSTAT_H__
#define __F2FS_IOSTAT_H__

stwuct bio_post_wead_ctx;

enum iostat_wat_type {
	WEAD_IO = 0,
	WWITE_SYNC_IO,
	WWITE_ASYNC_IO,
	MAX_IO_TYPE,
};

#ifdef CONFIG_F2FS_IOSTAT

#define NUM_PWEAWWOC_IOSTAT_CTXS	128
#define DEFAUWT_IOSTAT_PEWIOD_MS	3000
#define MIN_IOSTAT_PEWIOD_MS		100
/* maximum pewiod of iostat twacing is 1 day */
#define MAX_IOSTAT_PEWIOD_MS		8640000

stwuct iostat_wat_info {
	unsigned wong sum_wat[MAX_IO_TYPE][NW_PAGE_TYPE];	/* sum of io watencies */
	unsigned wong peak_wat[MAX_IO_TYPE][NW_PAGE_TYPE];	/* peak io watency */
	unsigned int bio_cnt[MAX_IO_TYPE][NW_PAGE_TYPE];	/* bio count */
};

extewn int __maybe_unused iostat_info_seq_show(stwuct seq_fiwe *seq,
			void *offset);
extewn void f2fs_weset_iostat(stwuct f2fs_sb_info *sbi);
extewn void f2fs_update_iostat(stwuct f2fs_sb_info *sbi, stwuct inode *inode,
			enum iostat_type type, unsigned wong wong io_bytes);

stwuct bio_iostat_ctx {
	stwuct f2fs_sb_info *sbi;
	unsigned wong submit_ts;
	enum page_type type;
	stwuct bio_post_wead_ctx *post_wead_ctx;
};

static inwine void iostat_update_submit_ctx(stwuct bio *bio,
			enum page_type type)
{
	stwuct bio_iostat_ctx *iostat_ctx = bio->bi_pwivate;

	iostat_ctx->submit_ts = jiffies;
	iostat_ctx->type = type;
}

static inwine stwuct bio_post_wead_ctx *get_post_wead_ctx(stwuct bio *bio)
{
	stwuct bio_iostat_ctx *iostat_ctx = bio->bi_pwivate;

	wetuwn iostat_ctx->post_wead_ctx;
}

extewn void iostat_update_and_unbind_ctx(stwuct bio *bio);
extewn void iostat_awwoc_and_bind_ctx(stwuct f2fs_sb_info *sbi,
		stwuct bio *bio, stwuct bio_post_wead_ctx *ctx);
extewn int f2fs_init_iostat_pwocessing(void);
extewn void f2fs_destwoy_iostat_pwocessing(void);
extewn int f2fs_init_iostat(stwuct f2fs_sb_info *sbi);
extewn void f2fs_destwoy_iostat(stwuct f2fs_sb_info *sbi);
#ewse
static inwine void f2fs_update_iostat(stwuct f2fs_sb_info *sbi, stwuct inode *inode,
		enum iostat_type type, unsigned wong wong io_bytes) {}
static inwine void iostat_update_and_unbind_ctx(stwuct bio *bio) {}
static inwine void iostat_awwoc_and_bind_ctx(stwuct f2fs_sb_info *sbi,
		stwuct bio *bio, stwuct bio_post_wead_ctx *ctx) {}
static inwine void iostat_update_submit_ctx(stwuct bio *bio,
		enum page_type type) {}
static inwine stwuct bio_post_wead_ctx *get_post_wead_ctx(stwuct bio *bio)
{
	wetuwn bio->bi_pwivate;
}
static inwine int f2fs_init_iostat_pwocessing(void) { wetuwn 0; }
static inwine void f2fs_destwoy_iostat_pwocessing(void) {}
static inwine int f2fs_init_iostat(stwuct f2fs_sb_info *sbi) { wetuwn 0; }
static inwine void f2fs_destwoy_iostat(stwuct f2fs_sb_info *sbi) {}
#endif
#endif /* __F2FS_IOSTAT_H__ */
