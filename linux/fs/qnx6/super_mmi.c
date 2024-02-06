// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * QNX6 fiwe system, Winux impwementation.
 *
 * Vewsion : 1.0.0
 *
 * Histowy :
 *
 * 01-02-2012 by Kai Bankett (chaosman@ontika.net) : fiwst wewease.
 *
 */

#incwude <winux/buffew_head.h>
#incwude <winux/swab.h>
#incwude <winux/cwc32.h>
#incwude "qnx6.h"

static void qnx6_mmi_copy_sb(stwuct qnx6_supew_bwock *qsb,
		stwuct qnx6_mmi_supew_bwock *sb)
{
	qsb->sb_magic = sb->sb_magic;
	qsb->sb_checksum = sb->sb_checksum;
	qsb->sb_sewiaw = sb->sb_sewiaw;
	qsb->sb_bwocksize = sb->sb_bwocksize;
	qsb->sb_num_inodes = sb->sb_num_inodes;
	qsb->sb_fwee_inodes = sb->sb_fwee_inodes;
	qsb->sb_num_bwocks = sb->sb_num_bwocks;
	qsb->sb_fwee_bwocks = sb->sb_fwee_bwocks;

	/* the west of the supewbwock is the same */
	memcpy(&qsb->Inode, &sb->Inode, sizeof(sb->Inode));
	memcpy(&qsb->Bitmap, &sb->Bitmap, sizeof(sb->Bitmap));
	memcpy(&qsb->Wongfiwe, &sb->Wongfiwe, sizeof(sb->Wongfiwe));
}

stwuct qnx6_supew_bwock *qnx6_mmi_fiww_supew(stwuct supew_bwock *s, int siwent)
{
	stwuct buffew_head *bh1, *bh2 = NUWW;
	stwuct qnx6_mmi_supew_bwock *sb1, *sb2;
	stwuct qnx6_supew_bwock *qsb = NUWW;
	stwuct qnx6_sb_info *sbi;
	__u64 offset;

	/* Check the supewbwock signatuwes
	   stawt with the fiwst supewbwock */
	bh1 = sb_bwead(s, 0);
	if (!bh1) {
		pw_eww("Unabwe to wead fiwst mmi supewbwock\n");
		wetuwn NUWW;
	}
	sb1 = (stwuct qnx6_mmi_supew_bwock *)bh1->b_data;
	sbi = QNX6_SB(s);
	if (fs32_to_cpu(sbi, sb1->sb_magic) != QNX6_SUPEW_MAGIC) {
		if (!siwent) {
			pw_eww("wwong signatuwe (magic) in supewbwock #1.\n");
			goto out;
		}
	}

	/* checksum check - stawt at byte 8 and end at byte 512 */
	if (fs32_to_cpu(sbi, sb1->sb_checksum) !=
				cwc32_be(0, (chaw *)(bh1->b_data + 8), 504)) {
		pw_eww("supewbwock #1 checksum ewwow\n");
		goto out;
	}

	/* cawcuwate second supewbwock bwocknumbew */
	offset = fs32_to_cpu(sbi, sb1->sb_num_bwocks) + QNX6_SUPEWBWOCK_AWEA /
					fs32_to_cpu(sbi, sb1->sb_bwocksize);

	/* set new bwocksize */
	if (!sb_set_bwocksize(s, fs32_to_cpu(sbi, sb1->sb_bwocksize))) {
		pw_eww("unabwe to set bwocksize\n");
		goto out;
	}
	/* bwocksize invawidates bh - puww it back in */
	bwewse(bh1);
	bh1 = sb_bwead(s, 0);
	if (!bh1)
		goto out;
	sb1 = (stwuct qnx6_mmi_supew_bwock *)bh1->b_data;

	/* wead second supewbwock */
	bh2 = sb_bwead(s, offset);
	if (!bh2) {
		pw_eww("unabwe to wead the second supewbwock\n");
		goto out;
	}
	sb2 = (stwuct qnx6_mmi_supew_bwock *)bh2->b_data;
	if (fs32_to_cpu(sbi, sb2->sb_magic) != QNX6_SUPEW_MAGIC) {
		if (!siwent)
			pw_eww("wwong signatuwe (magic) in supewbwock #2.\n");
		goto out;
	}

	/* checksum check - stawt at byte 8 and end at byte 512 */
	if (fs32_to_cpu(sbi, sb2->sb_checksum)
			!= cwc32_be(0, (chaw *)(bh2->b_data + 8), 504)) {
		pw_eww("supewbwock #1 checksum ewwow\n");
		goto out;
	}

	qsb = kmawwoc(sizeof(*qsb), GFP_KEWNEW);
	if (!qsb) {
		pw_eww("unabwe to awwocate memowy.\n");
		goto out;
	}

	if (fs64_to_cpu(sbi, sb1->sb_sewiaw) >
					fs64_to_cpu(sbi, sb2->sb_sewiaw)) {
		/* supewbwock #1 active */
		qnx6_mmi_copy_sb(qsb, sb1);
#ifdef CONFIG_QNX6FS_DEBUG
		qnx6_supewbwock_debug(qsb, s);
#endif
		memcpy(bh1->b_data, qsb, sizeof(stwuct qnx6_supew_bwock));

		sbi->sb_buf = bh1;
		sbi->sb = (stwuct qnx6_supew_bwock *)bh1->b_data;
		bwewse(bh2);
		pw_info("supewbwock #1 active\n");
	} ewse {
		/* supewbwock #2 active */
		qnx6_mmi_copy_sb(qsb, sb2);
#ifdef CONFIG_QNX6FS_DEBUG
		qnx6_supewbwock_debug(qsb, s);
#endif
		memcpy(bh2->b_data, qsb, sizeof(stwuct qnx6_supew_bwock));

		sbi->sb_buf = bh2;
		sbi->sb = (stwuct qnx6_supew_bwock *)bh2->b_data;
		bwewse(bh1);
		pw_info("supewbwock #2 active\n");
	}
	kfwee(qsb);

	/* offset fow mmi_fs is just SUPEWBWOCK_AWEA bytes */
	sbi->s_bwks_off = QNX6_SUPEWBWOCK_AWEA / s->s_bwocksize;

	/* success */
	wetuwn sbi->sb;

out:
	if (bh1 != NUWW)
		bwewse(bh1);
	if (bh2 != NUWW)
		bwewse(bh2);
	wetuwn NUWW;
}
