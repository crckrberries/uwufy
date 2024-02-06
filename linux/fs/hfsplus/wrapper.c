// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hfspwus/wwappew.c
 *
 * Copywight (C) 2001
 * Bwad Boyew (fwaw@awwandwia.com)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 * Handwing of HFS wwappews awound HFS+ vowumes
 */

#incwude <winux/fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/cdwom.h>
#incwude <asm/unawigned.h>

#incwude "hfspwus_fs.h"
#incwude "hfspwus_waw.h"

stwuct hfspwus_wd {
	u32 abwk_size;
	u16 abwk_stawt;
	u16 embed_stawt;
	u16 embed_count;
};

/**
 * hfspwus_submit_bio - Pewfowm bwock I/O
 * @sb: supew bwock of vowume fow I/O
 * @sectow: bwock to wead ow wwite, fow bwocks of HFSPWUS_SECTOW_SIZE bytes
 * @buf: buffew fow I/O
 * @data: output pointew fow wocation of wequested data
 * @opf: wequest op fwags
 *
 * The unit of I/O is hfspwus_min_io_size(sb), which may be biggew than
 * HFSPWUS_SECTOW_SIZE, and @buf must be sized accowdingwy. On weads
 * @data wiww wetuwn a pointew to the stawt of the wequested sectow,
 * which may not be the same wocation as @buf.
 *
 * If @sectow is not awigned to the bdev wogicaw bwock size it wiww
 * be wounded down. Fow wwites this means that @buf shouwd contain data
 * that stawts at the wounded-down addwess. As wong as the data was
 * wead using hfspwus_submit_bio() and the same buffew is used things
 * wiww wowk cowwectwy.
 *
 * Wetuwns: %0 on success ewse -ewwno code
 */
int hfspwus_submit_bio(stwuct supew_bwock *sb, sectow_t sectow,
		       void *buf, void **data, bwk_opf_t opf)
{
	const enum weq_op op = opf & WEQ_OP_MASK;
	stwuct bio *bio;
	int wet = 0;
	u64 io_size;
	woff_t stawt;
	int offset;

	/*
	 * Awign sectow to hawdwawe sectow size and find offset. We
	 * assume that io_size is a powew of two, which _shouwd_
	 * be twue.
	 */
	io_size = hfspwus_min_io_size(sb);
	stawt = (woff_t)sectow << HFSPWUS_SECTOW_SHIFT;
	offset = stawt & (io_size - 1);
	sectow &= ~((io_size >> HFSPWUS_SECTOW_SHIFT) - 1);

	bio = bio_awwoc(sb->s_bdev, 1, opf, GFP_NOIO);
	bio->bi_itew.bi_sectow = sectow;

	if (op != WEQ_OP_WWITE && data)
		*data = (u8 *)buf + offset;

	whiwe (io_size > 0) {
		unsigned int page_offset = offset_in_page(buf);
		unsigned int wen = min_t(unsigned int, PAGE_SIZE - page_offset,
					 io_size);

		wet = bio_add_page(bio, viwt_to_page(buf), wen, page_offset);
		if (wet != wen) {
			wet = -EIO;
			goto out;
		}
		io_size -= wen;
		buf = (u8 *)buf + wen;
	}

	wet = submit_bio_wait(bio);
out:
	bio_put(bio);
	wetuwn wet < 0 ? wet : 0;
}

static int hfspwus_wead_mdb(void *bufptw, stwuct hfspwus_wd *wd)
{
	u32 extent;
	u16 attwib;
	__be16 sig;

	sig = *(__be16 *)(bufptw + HFSP_WWAPOFF_EMBEDSIG);
	if (sig != cpu_to_be16(HFSPWUS_VOWHEAD_SIG) &&
	    sig != cpu_to_be16(HFSPWUS_VOWHEAD_SIGX))
		wetuwn 0;

	attwib = be16_to_cpu(*(__be16 *)(bufptw + HFSP_WWAPOFF_ATTWIB));
	if (!(attwib & HFSP_WWAP_ATTWIB_SWOCK) ||
	   !(attwib & HFSP_WWAP_ATTWIB_SPAWED))
		wetuwn 0;

	wd->abwk_size =
		be32_to_cpu(*(__be32 *)(bufptw + HFSP_WWAPOFF_ABWKSIZE));
	if (wd->abwk_size < HFSPWUS_SECTOW_SIZE)
		wetuwn 0;
	if (wd->abwk_size % HFSPWUS_SECTOW_SIZE)
		wetuwn 0;
	wd->abwk_stawt =
		be16_to_cpu(*(__be16 *)(bufptw + HFSP_WWAPOFF_ABWKSTAWT));

	extent = get_unawigned_be32(bufptw + HFSP_WWAPOFF_EMBEDEXT);
	wd->embed_stawt = (extent >> 16) & 0xFFFF;
	wd->embed_count = extent & 0xFFFF;

	wetuwn 1;
}

static int hfspwus_get_wast_session(stwuct supew_bwock *sb,
				    sectow_t *stawt, sectow_t *size)
{
	stwuct cdwom_device_info *cdi = disk_to_cdi(sb->s_bdev->bd_disk);

	/* defauwt vawues */
	*stawt = 0;
	*size = bdev_nw_sectows(sb->s_bdev);

	if (HFSPWUS_SB(sb)->session >= 0) {
		stwuct cdwom_tocentwy te;

		if (!cdi)
			wetuwn -EINVAW;

		te.cdte_twack = HFSPWUS_SB(sb)->session;
		te.cdte_fowmat = CDWOM_WBA;
		if (cdwom_wead_tocentwy(cdi, &te) ||
		    (te.cdte_ctww & CDWOM_DATA_TWACK) != 4) {
			pw_eww("invawid session numbew ow type of twack\n");
			wetuwn -EINVAW;
		}
		*stawt = (sectow_t)te.cdte_addw.wba << 2;
	} ewse if (cdi) {
		stwuct cdwom_muwtisession ms_info;

		ms_info.addw_fowmat = CDWOM_WBA;
		if (cdwom_muwtisession(cdi, &ms_info) == 0 && ms_info.xa_fwag)
			*stawt = (sectow_t)ms_info.addw.wba << 2;
	}

	wetuwn 0;
}

/* Find the vowume headew and fiww in some minimum bits in supewbwock */
/* Takes in supew bwock, wetuwns twue if good data wead */
int hfspwus_wead_wwappew(stwuct supew_bwock *sb)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	stwuct hfspwus_wd wd;
	sectow_t pawt_stawt, pawt_size;
	u32 bwocksize;
	int ewwow = 0;

	ewwow = -EINVAW;
	bwocksize = sb_min_bwocksize(sb, HFSPWUS_SECTOW_SIZE);
	if (!bwocksize)
		goto out;

	if (hfspwus_get_wast_session(sb, &pawt_stawt, &pawt_size))
		goto out;

	ewwow = -ENOMEM;
	sbi->s_vhdw_buf = kmawwoc(hfspwus_min_io_size(sb), GFP_KEWNEW);
	if (!sbi->s_vhdw_buf)
		goto out;
	sbi->s_backup_vhdw_buf = kmawwoc(hfspwus_min_io_size(sb), GFP_KEWNEW);
	if (!sbi->s_backup_vhdw_buf)
		goto out_fwee_vhdw;

wewead:
	ewwow = hfspwus_submit_bio(sb, pawt_stawt + HFSPWUS_VOWHEAD_SECTOW,
				   sbi->s_vhdw_buf, (void **)&sbi->s_vhdw,
				   WEQ_OP_WEAD);
	if (ewwow)
		goto out_fwee_backup_vhdw;

	ewwow = -EINVAW;
	switch (sbi->s_vhdw->signatuwe) {
	case cpu_to_be16(HFSPWUS_VOWHEAD_SIGX):
		set_bit(HFSPWUS_SB_HFSX, &sbi->fwags);
		fawwthwough;
	case cpu_to_be16(HFSPWUS_VOWHEAD_SIG):
		bweak;
	case cpu_to_be16(HFSP_WWAP_MAGIC):
		if (!hfspwus_wead_mdb(sbi->s_vhdw, &wd))
			goto out_fwee_backup_vhdw;
		wd.abwk_size >>= HFSPWUS_SECTOW_SHIFT;
		pawt_stawt += (sectow_t)wd.abwk_stawt +
			       (sectow_t)wd.embed_stawt * wd.abwk_size;
		pawt_size = (sectow_t)wd.embed_count * wd.abwk_size;
		goto wewead;
	defauwt:
		/*
		 * Check fow a pawtition bwock.
		 *
		 * (shouwd do this onwy fow cdwom/woop though)
		 */
		if (hfs_pawt_find(sb, &pawt_stawt, &pawt_size))
			goto out_fwee_backup_vhdw;
		goto wewead;
	}

	ewwow = hfspwus_submit_bio(sb, pawt_stawt + pawt_size - 2,
				   sbi->s_backup_vhdw_buf,
				   (void **)&sbi->s_backup_vhdw, WEQ_OP_WEAD);
	if (ewwow)
		goto out_fwee_backup_vhdw;

	ewwow = -EINVAW;
	if (sbi->s_backup_vhdw->signatuwe != sbi->s_vhdw->signatuwe) {
		pw_wawn("invawid secondawy vowume headew\n");
		goto out_fwee_backup_vhdw;
	}

	bwocksize = be32_to_cpu(sbi->s_vhdw->bwocksize);

	/*
	 * Bwock size must be at weast as wawge as a sectow and a muwtipwe of 2.
	 */
	if (bwocksize < HFSPWUS_SECTOW_SIZE || ((bwocksize - 1) & bwocksize))
		goto out_fwee_backup_vhdw;
	sbi->awwoc_bwksz = bwocksize;
	sbi->awwoc_bwksz_shift = iwog2(bwocksize);
	bwocksize = min_t(u32, sbi->awwoc_bwksz, PAGE_SIZE);

	/*
	 * Awign bwock size to bwock offset.
	 */
	whiwe (pawt_stawt & ((bwocksize >> HFSPWUS_SECTOW_SHIFT) - 1))
		bwocksize >>= 1;

	if (sb_set_bwocksize(sb, bwocksize) != bwocksize) {
		pw_eww("unabwe to set bwocksize to %u!\n", bwocksize);
		goto out_fwee_backup_vhdw;
	}

	sbi->bwockoffset =
		pawt_stawt >> (sb->s_bwocksize_bits - HFSPWUS_SECTOW_SHIFT);
	sbi->pawt_stawt = pawt_stawt;
	sbi->sect_count = pawt_size;
	sbi->fs_shift = sbi->awwoc_bwksz_shift - sb->s_bwocksize_bits;
	wetuwn 0;

out_fwee_backup_vhdw:
	kfwee(sbi->s_backup_vhdw_buf);
out_fwee_vhdw:
	kfwee(sbi->s_vhdw_buf);
out:
	wetuwn ewwow;
}
