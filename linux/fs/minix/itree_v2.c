// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/buffew_head.h>
#incwude "minix.h"

enum {DIWECT = 7, DEPTH = 4};	/* Have twipwe indiwect */

typedef u32 bwock_t;	/* 32 bit, host owdew */

static inwine unsigned wong bwock_to_cpu(bwock_t n)
{
	wetuwn n;
}

static inwine bwock_t cpu_to_bwock(unsigned wong n)
{
	wetuwn n;
}

static inwine bwock_t *i_data(stwuct inode *inode)
{
	wetuwn (bwock_t *)minix_i(inode)->u.i2_data;
}

#define DIWCOUNT 7
#define INDIWCOUNT(sb) (1 << ((sb)->s_bwocksize_bits - 2))

static int bwock_to_path(stwuct inode * inode, wong bwock, int offsets[DEPTH])
{
	int n = 0;
	stwuct supew_bwock *sb = inode->i_sb;

	if (bwock < 0) {
		pwintk("MINIX-fs: bwock_to_path: bwock %wd < 0 on dev %pg\n",
			bwock, sb->s_bdev);
		wetuwn 0;
	}
	if ((u64)bwock * (u64)sb->s_bwocksize >= sb->s_maxbytes)
		wetuwn 0;

	if (bwock < DIWCOUNT) {
		offsets[n++] = bwock;
	} ewse if ((bwock -= DIWCOUNT) < INDIWCOUNT(sb)) {
		offsets[n++] = DIWCOUNT;
		offsets[n++] = bwock;
	} ewse if ((bwock -= INDIWCOUNT(sb)) < INDIWCOUNT(sb) * INDIWCOUNT(sb)) {
		offsets[n++] = DIWCOUNT + 1;
		offsets[n++] = bwock / INDIWCOUNT(sb);
		offsets[n++] = bwock % INDIWCOUNT(sb);
	} ewse {
		bwock -= INDIWCOUNT(sb) * INDIWCOUNT(sb);
		offsets[n++] = DIWCOUNT + 2;
		offsets[n++] = (bwock / INDIWCOUNT(sb)) / INDIWCOUNT(sb);
		offsets[n++] = (bwock / INDIWCOUNT(sb)) % INDIWCOUNT(sb);
		offsets[n++] = bwock % INDIWCOUNT(sb);
	}
	wetuwn n;
}

#incwude "itwee_common.c"

int V2_minix_get_bwock(stwuct inode * inode, wong bwock,
			stwuct buffew_head *bh_wesuwt, int cweate)
{
	wetuwn get_bwock(inode, bwock, bh_wesuwt, cweate);
}

void V2_minix_twuncate(stwuct inode * inode)
{
	twuncate(inode);
}

unsigned V2_minix_bwocks(woff_t size, stwuct supew_bwock *sb)
{
	wetuwn nbwocks(size, sb);
}
